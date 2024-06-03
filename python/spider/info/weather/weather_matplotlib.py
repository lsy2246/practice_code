import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

_data = {}
file_path = 'weather.xlsx'
_xls = pd.ExcelFile(file_path, engine='openpyxl')
for sheet_name in _xls.sheet_names:
    _area = sheet_name
    if _area not in _data:
        _data[_area] = {}
    _xls_content = pd.read_excel(file_path, _area)
    for _index, _single in _xls_content.iterrows():
        _data_time = _single['日期时间']
        if _data_time not in _data[_area]:
            _data[_area][_data_time] = {'白天温度': [], '夜间温度': []}
        _data_day = _single['白天温度']
        _data_night = _single['夜间温度']
        _data[_area][_data_time]['白天温度'].append(_data_day)
        _data[_area][_data_time]['夜间温度'].append(_data_night)

last_dick = {}
for _area, _date_time in _data.items():
    last_dick[_area] = {"时间": [], "白天": [], "夜间": []}
    for _data_single_time, _data_single in _date_time.items():
        if _data_single_time not in last_dick[_area]['时间']:
            last_dick[_area]['时间'].append(_data_single_time)
        np_day = np.array(_data_single['白天温度']).mean()
        np_night = np.array(_data_single['夜间温度']).mean()
        last_dick[_area]['白天'].append(float(np_day))
        last_dick[_area]['夜间'].append(float(np_night))

_fig, _axes = plt.subplots(nrows=len(last_dick), ncols=1, figsize=(10, 30))
plt.rcParams['font.sans-serif'] = ['SimHei']
if len(last_dick) == 1:
    _axes = [_axes]

for _ax, (_area, _data_info) in zip(_axes, last_dick.items()):
    _data_s = _data_info['时间']
    _day_s = _data_info['白天']
    _night_s = _data_info['夜间']
    _ax.plot(_data_s, _day_s, label='白天', marker='o')
    for _x, _y in zip(_data_s, _day_s):
        _ax.annotate(f'{_y:.1f}°', (_x, _y), xytext=(5, 10), textcoords='offset points', ha='center')
    for _x, _y in zip(_data_s, _night_s):
        _ax.annotate(f'{_y:.1f}°', (_x, _y), xytext=(5, -15), textcoords='offset points', ha='center')

    _ax.plot(_data_s, _night_s, label='夜间', marker='o')
    _ax.set_title(_area)
    _ax.set_yticks(range(0, 45, 5))
    _ax.set_yticklabels([f"{i}°" for i in range(0, 45, 5)])
    _ax.grid(alpha=0.5, linestyle='--')
    _ax.legend()
    _ax.set_xlim([_data_s[0], _data_s[len(_data_s) - 1]])
    _ax.text(_ax.get_xlim()[0], _ax.get_ylim()[1]+0.2, f"最高温度{np.max(_day_s):.1f}°")
    _ax.text(_ax.get_xlim()[0]+0.8, _ax.get_ylim()[1]+0.2, f"最低温度{np.min(_night_s):.1f}°")
    _ax.text(_ax.get_xlim()[0]+1.6, _ax.get_ylim()[1]+0.2, f"平均温度{np.mean(_night_s):.1f}°")

_fig.savefig('weather_matplotlib.svg', bbox_inches='tight', transparent=True)
plt.show()
