import re
import requests

url = "https://www.pearvideo.com/video_1792985"

conID = url.split("_")[1]
videourl = f"https://www.pearvideo.com/videoStatus.jsp?contId={conID}"

header = {"Referer": url,
          "User-Agent":
              "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36"
          }

resp = requests.get(videourl, headers=header)

dic = resp.json()

srcUrl = dic["videoInfo"]["videos"]["srcUrl"]

systemTime = dic["systemTime"]

downloadurl = srcUrl.replace(systemTime,f"cont-{conID}")


url =requests.get(downloadurl, headers=header)

file = open("lsp.mp4","wb+")

file.write(url.content)

file.close()

