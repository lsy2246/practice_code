import asyncio
import re

import aiohttp
import aiofiles
from bs4 import BeautifulSoup
import os
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor  # 多线程/多进程


async def aiodownload(url):
    if not os.path.exists("xs"):
        os.mkdir("xs")
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as response:
            html = BeautifulSoup(await response.read(), "html.parser")
            title = html.find("h1", class_="wap_none").text
            content = html.find("div", id="chaptercontent").text
            if os.name == 'posix':
                name = "xs\\" + title.split(" ")[0] + ".txt"
            elif os.name == 'nt':
                name = "xs/" + title.split(" ")[0] + ".txt"
            content = content.replace("　　", "\n").replace(
                "请收藏本站：https://www.biqg.cc。笔趣阁手机版：https://m.biqg.cc ", "").replace("『点此报错』『加入书签』",
                                                                                              "")
            async with aiofiles.open(name, "a+") as file:
                await file.write(content)

    print(title, "成功下载")


async def main(urls):
    takes = []
    for url in urls:
        take = asyncio.create_task(aiodownload(url))
        takes.append(take)
    await asyncio.wait(takes)


if __name__ == "__main__":
    urls = []
    for index in range(1, 2):
        url = f"https://www.biqg.cc/book/3670/{index}.html"
        urls.append(url)
    asyncio.run(main(urls=urls))
    print("全部下载完成")

