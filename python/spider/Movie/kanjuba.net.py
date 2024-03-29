from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor  # 多线程/多进程
import requests
import re
import os
import shutil
from lxml import etree


def downloadm3u81(domain, filepath, ts, headers):
    domain = ts.rstrip("\n")
    urlend = domain.split('/')[-1]
    domain = domain.replace(urlend, ts)
    urlend = domain.split('/')[-1]
    filename = filepath + urlend
    with requests.get(domain, headers=headers) as r:
        if r.status_code == 200:
            with open(filename, 'wb') as f:
                f.write(r.content)
            try:
                print(f"正在下载{urlend}")
                open(filename, "r")
            except:
                print(f"{urlend}下载失败尝试重新下载")
                try:
                    with open(filename, 'wb') as f:
                        print(f"正在下载{urlend}")
                        f.write(r.content)
                except:
                    print(f"{urlend}下载失败")
            else:
                print(f"{urlend}下载完成")
        else:
            print(f"{domain}访问失败,错误代码{r.status_code}")


def merge_ts_to_mp41(filepath, title):
    with open(f"{filepath}{title}.m3u8", "r") as file:
        with open(f"{title}.mp4", "ab") as video:
            print("正在合成,请耐心等待")
            for name in file:
                name = name.split("/")[-1]
                name = name.strip()  # 去除文件名中的换行符和空白
                name = filepath + name
                with open(name, "rb") as ts:
                    video.write(ts.read())


def merge_ts_to_mp42(filepath, title):
    with open(f"{filepath}{title}.m3u8", "r") as file:
        with open(f"{title}.mp4", "ab") as video:
            print("正在合成,请耐心等待")
            for name in file:
                name = name.strip()  # 去除文件名中的换行符和空白
                name = filepath + name
                print(name)


def downloadm3u82(filepath, domain,ts, headers):
    urlend = domain.split("/")[-1]
    filename = filepath + ts
    domain = domain.replace(urlend, ts)
    with requests.get(domain, headers=headers) as r:
        if r.status_code == 200:
            with open(filename, 'wb') as f:
                print(f"正在下载{urlend}")
                f.write(r.content)
            try:
                open(filename, "r")
            except:
                print(f"{ts}下载失败尝试重新下载")
                try:
                    with open(filename, 'wb') as f:
                        print(f"正在下载{urlend}")
                        f.write(r.content)
                except:
                    print(f"{ts}下载失败")
            else:
                print(f"{ts}下载完成")
        else:
            print(f"{domain}访问失败,错误代码{r.status_code}")

##获取m3u8文件
def getm3u8(domain, headers):
    ##获取m3u8
    orl_obj = re.compile('http.*?.m3u8')
    with requests.get(domain, headers=headers) as html:
        if html.status_code == 200:
            title = etree.HTML(html.text)
            title = title.xpath('/html/body/div/div[2]/div/div[2]/div/div/div/div[1]/div[1]/h2/text()')
            title = title[0]

            if os.name == 'posix':
                filepath = f"tmpMovie/{title}/"
            elif os.name == 'nt':
                filepath = f"tmpMovie\\{title}\\"

            if not os.path.exists("tmpMovie"):
                os.mkdir("tmpMovie")
            if not os.path.exists(filepath):
                os.mkdir(filepath)
            print(f'临时文件夹“{filepath}”创建成功')

            print("开始读取m3u8文件")
            m3u8url1 = orl_obj.findall(html.text)
            domain = m3u8url1[0]

            with requests.get(m3u8url1[0], headers=headers) as m3u8url2:
                m3u8url2 = str(m3u8url2.text)
                m3u8url2 = m3u8url2.split('\n')
                if len(m3u8url2) < 5:
                    if m3u8url2[-1] == "":
                        m3u8url2 = m3u8url2[-2]
                    else:
                        m3u8url2 = m3u8url2[-1]
                    m3u8url2 = m3u8url2.split()
                    substitute = domain.split("/")[-1]


                    domain = domain.replace(substitute, m3u8url2[0])
                    with requests.get(domain, headers=headers) as tss:
                        tss = str(tss.text).split("\n")
                        with open(f"{filepath}{title}.m3u8", "a+") as m3u8file:
                            for ts in tss:
                                if ts.startswith("#") or ts.startswith(" "):
                                    continue
                                else:
                                    m3u8file.write(f"{ts}\n")
                    print("m3u8文件读取完成")
                else:
                    with open(f"{filepath}{title}.m3u8", "a+") as m3u8file:
                        for ts in m3u8url2:
                            if ts.startswith("#") or ts.startswith(" "):
                                continue
                            else:
                                m3u8file.write(f"{ts}\n")
                print("m3u8文件读取完成")
        else:
            print("访问失败")
            exit(1)

    ##下载m3u8
    print(f'开始下载视频"{title}"')
    with open(f"{filepath}{title}.m3u8", "r") as tsfile:
        with ThreadPoolExecutor(max_workers=1) as xc:
            for ts in tsfile:
                if ts.startswith("http"):
                    xc.submit(downloadm3u81, domain=domain, filepath=filepath, ts=ts, headers=headers)
                else:
                    xc.submit(downloadm3u82, filepath=filepath, domain=domain, ts=ts, headers=headers)

    ##合成视频
    print("开始合成视频")
    merge_ts_to_mp42(filepath, title)
    shutil.rmtree("tmpMovie")
    print("下载已经全部完成")
    print(f"文件在当前根目录{title}.mp4")


if __name__ == "__main__":
    domain = "https://kanjuba.net/play/93312-0-9.html"

    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36',
        'Referer': "https://kanjuba.net/",
        'Sec-Ch-Ua': '"Google Chrome";v="123", "Not:A-Brand";v="8", "Chromium";v="123"',
        'Sec-Ch-Ua-Platform': '"Windows"'
    }

    getm3u8(domain, headers)
