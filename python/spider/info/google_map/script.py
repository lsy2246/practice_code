from selenium import webdriver  # 驱动
from selenium.webdriver.common.by import By  # 解析方式
from selenium.webdriver import Keys  # 模拟按键
from selenium.webdriver.common.action_chains import ActionChains
import time
import csv
import datetime
# 开启无头浏览器
from selenium.webdriver.chrome.options import Options


class google_map_script:
    def __init__(self, url, head, frequency):
        self.url = url
        self.head = head
        self.frequency = frequency

    def start(self):
        if self.head:
            driver = webdriver.Chrome()
        else:
            options = Options()
            options.add_argument("--headless")
            options.add_argument("--disable-gpu")
            driver = webdriver.Chrome(options=options)  # 创建浏览器对象
        self.work(driver)

    def work(self, driver):
        driver.get(self.url)
        # 获取当前日期和时间
        now = datetime.datetime.now()
        formatted_date = now.strftime('%Y-%m-%d_%H-%M-%S')  # 格式化日期和时间

        # 指定CSV文件路径，文件名为当前时间
        file_path = f'google_map_{formatted_date}.csv'

        driver.get(self.url)
        time.sleep(3)
        scrollable_element = driver.find_element(By.XPATH,
                                                 '//*[@id="QA0Szd"]/div/div/div[1]/div[2]/div/div[1]/div/div/div[1]/div[1]')

        for i in range(int(self.frequency)):
            scrollable_element.send_keys(Keys.PAGE_DOWN)
            time.sleep(1)

        divs = driver.find_elements(By.XPATH,
                                    '//div/div/div[1]/div[2]/div/div[1]/div/div/div[1]/div[1]/div[not(@class)]')
        for div in divs:
            info_dict = {"店名": "", "地址": "", "电话": "", "网站": "", "Plus Code": "", "星期一": "", "星期二": "",
                         "星期三": "",
                         "星期四": "", "星期五": "", "星期六": "", "星期日": ""}
            info_content = []
            div.click()
            time.sleep(1)
            info_path_1 = "//div/div/div[1]/div[3]/div/div[1]/div/div/div[2]/div[7]"
            info_path_2 = "//div/div/div[1]/div[3]/div/div[1]/div/div/div[2]/div[8]"
            title = driver.find_element(By.XPATH,
                                        '//div/div/div[1]/div[3]/div/div[1]/div/div/div[2]/div[2]/div/div[1]/div[1]/h1').text
            info_dict["店名"] = title
            info_divs = driver.find_element(By.XPATH, info_path_1)

            role_test = info_divs.get_attribute("role")
            if role_test == "presentation":
                info_divs = driver.find_element(By.XPATH, info_path_2)

            a_s = info_divs.find_elements(By.XPATH, './/a')
            button_s = info_divs.find_elements(By.XPATH, './/button')

            for a in a_s:
                a_info = a.get_attribute("aria-label")
                if a is not None:
                    info_content.append(a_info)

            for button in button_s:
                button_info = button.get_attribute("aria-label")
                if button_info is not None:
                    info_content.append(button_info)

            for info in info_content:
                tmp_content = info.split(":", 1)
                if tmp_content[0] in ["地址", "电话", "Plus Code", "网站"]:
                    info_dict[tmp_content[0]] = tmp_content[1].strip()
                tmp_content = info.split("，", 1)
                if tmp_content[0] in ["星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"]:
                    tmp_time = tmp_content[1].split("、", -1)
                    info_dict[tmp_content[0]] = tmp_time[0].strip()

            with open(file_path, mode='a', newline='', encoding='utf-8-sig') as file:
                # CSV写入器
                writer = csv.DictWriter(file, fieldnames=info_dict.keys())

                # 写入CSV标题，仅在文件为空时写入
                if file.tell() == 0:
                    writer.writeheader()

                # 写入数据
                writer.writerow(info_dict)
        driver.quit()

