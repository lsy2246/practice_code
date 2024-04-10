import tkinter as tk
from tkinter import messagebox

# 创建主窗口
root = tk.Tk()
root.withdraw()  # 隐藏主窗口

# 弹出消息框
messagebox.showinfo("标题", "消息内容")

# 弹出警告框
messagebox.showwarning("警告", "警告内容")

# 弹出错误框
messagebox.showerror("错误", "错误内容")

# 弹出询问框
result = messagebox.askquestion("询问", "是否继续？")
if result == 'yes':
    print("用户选择了继续")
else:
    print("用户选择了取消")

# 弹出确认框
result = messagebox.askokcancel("确认", "是否继续？")
if result:
    print("用户选择了继续")
else:
    print("用户选择了取消")

# 弹出是/否框
result = messagebox.askyesno("是/否", "是否继续？")
if result:
    print("用户选择了是")
else:
    print("用户选择了否")

# 弹出重试/取消框
result = messagebox.askretrycancel("重试/取消", "是否继续？")
if result:
    print("用户选择了重试")
else:
    print("用户选择了取消")

# 显示主窗口
root.mainloop()
