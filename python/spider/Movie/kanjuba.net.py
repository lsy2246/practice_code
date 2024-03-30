from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor  # 多线程/多进程
import requests
import re
import os
import shutil
from lxml import etree



def downloadm3u8(domain, filepath, ts, headers):
    domain = domain.strip("\n")
    ts = ts.strip("\n")
    urlend = domain.split('/')[-1]
    domain = domain.replace(urlend, ts).strip("\n")
    filename = filepath + ts
    print(f"正在下载{ts}")
    with requests.get(domain, headers=headers) as r:
        if r.status_code == 200:
            with open(filename, 'wb') as f:
                f.write(r.content)
            try:
                open(filename, "r")
            except:
                print(f"{ts}下载失败尝试重新下载")
                with requests.get(domain, headers=headers) as r:
                    if r.status_code == 200:
                        with open(filename, 'wb') as f:
                            f.write(r.content)
                try:
                    open(filename, "r")
                except:
                    print(f"{ts}下载失败")
            else:
                print(f"{ts}下载完成")
        else:
            print(f"{r.url}访问失败,错误代码{r.status_code}")


def merge_ts_to_mp4(filepath, title, ts):
    ts = ts.strip("\n")
    with open(f"{title}.mp4", "ab") as video:
        filename = filepath + ts
        with open(f"{filename}", "rb") as tsvido:
            print(f"正在合成{ts},请耐心等待")
            video.write(tsvido.read())


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
                            if ts.startswith("#") or ts.startswith(" ") or ts.startswith("http"):
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
        with ThreadPoolExecutor(max_workers=30) as xc:
            ts = ts.strip("\n")
            for ts in tsfile:
                xc.submit(downloadm3u8, filepath=filepath, domain=domain, ts=ts, headers=headers)

    ##合成视频
    print("开始合成视频")
    with open(f"{filepath}{title}.m3u8", "r") as tsfile:
        ts.strip("\n")
        for ts in tsfile:
            ts = ts.strip("\n")
            if ts != "":
                merge_ts_to_mp4(filepath=filepath, title=title, ts=ts)

    print("下载已经全部完成")
    #shutil.rmtree(f"{filepath}") #开启清除临时文件
    #print("临时文件清理完成")
    print(f'临时文件在"{filepath}"可删除')
    print(f"视频在当前根目录{title}.mp4")


if __name__ == "__main__":
    domain = "https://kanjuba.net/play/112379-0-0.html"

    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36',
        'Referer': "https://kanjuba.net/",
        'Sec-Ch-Ua': '"Google Chrome";v="123", "Not:A-Brand";v="8", "Chromium";v="123"',
        'Sec-Ch-Ua-Platform': '"Windows"'
    }

    getm3u8(domain, headers)
