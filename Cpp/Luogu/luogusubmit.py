import os
import re
import time
import random
import requests
import json
import logging
from bs4 import BeautifulSoup
from urllib.parse import unquote

# **配置日志**
logging.basicConfig(level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s")

# **常量**
BASE_URL = "https://www.luogu.com.cn"
USER_ID = "1094237"  # 替换成你的用户 ID
OUTPUT_DIR = "cpp/Luogu/submitcode"
os.makedirs(OUTPUT_DIR, exist_ok=True)

# **随机 User-Agent，防止被封**
USER_AGENTS = [
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36",
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36"
]

# **Cookie（必须是有效的）**
COOKIE = "__client_id=eacf9b8b13fc192d9374d4527abf1235c99b952f; _uid=1094237; C3VK=73ad72"

HEADERS = {
    "User-Agent": random.choice(USER_AGENTS),
    "Cookie": COOKIE,
    "Accept": "application/json, text/javascript, */*; q=0.01",
    "Accept-Language": "zh-CN,zh;q=0.9",
    "Accept-Encoding": "gzip, deflate, br",
    "X-Requested-With": "XMLHttpRequest",
    "Host": "www.luogu.com.cn",
    "Connection": "keep-alive",
    "Referer": f"https://www.luogu.com.cn/user/{USER_ID}",
    "sec-ch-ua": '"Chromium";v="116", "Not)A;Brand";v="24", "Google Chrome";v="116"',
    "sec-ch-ua-mobile": "?0",
    "sec-ch-ua-platform": '"Windows"',
    "Sec-Fetch-Dest": "empty",
    "Sec-Fetch-Mode": "cors",
    "Sec-Fetch-Site": "same-origin",
}

# **匹配 JSON 数据的正则**
regex = re.compile(r'"(.*)"')

def get_html_content(url):
    """ 发送请求，获取网页 HTML """
    logging.info(f"请求页面: {url}")
    try:
        response = requests.get(url, headers=HEADERS, timeout=10)
        logging.info(f"HTTP 状态码: {response.status_code}")
        
        if response.status_code == 200:
            return response.text
        elif response.status_code == 403:
            logging.error("请求被拒绝！可能是 IP 被封，请更换代理或检查 Cookie。")
        elif response.status_code == 429:
            logging.error("请求过于频繁！请减少访问频率。")
        else:
            logging.error(f"请求失败，状态码: {response.status_code}")
        
    except requests.RequestException as e:
        logging.error(f"网络错误: {e}")
    
    return ""

def extract_json_text(html):
    """ 从 HTML 提取 JSON 数据，兼容 lentille-context 和 window._feInjection """
    soup = BeautifulSoup(html, "html.parser")
    # 1. 优先查找 id="lentille-context"
    script = soup.find("script", id="lentille-context")
    if script and script.string:
        logging.info("通过 id='lentille-context' 成功提取 JSON 数据")
        return script.string.strip()
    # 2. 查找 window._feInjection
    scripts = soup.find_all("script")
    for script in scripts:
        if script.string and 'window._feInjection' in script.string:
            match = re.search(r'window\._feInjection\s*=\s*JSON\.parse\(decodeURIComponent\("([^"]+)"\)\)', script.string)
            if match:
                encoded_json = match.group(1)
                decoded_json = unquote(encoded_json)
                logging.info("通过 window._feInjection 成功提取 JSON 数据")
                return decoded_json
    logging.warning("JSON 解析失败")
    return None

def get_code_from_json(decoded_json):
    """ 解析 JSON，提取代码 """
    try:
        json_data = json.loads(decoded_json)
        # 兼容 currentData 和 data
        record = None
        if "currentData" in json_data:
            record = json_data.get("currentData", {}).get("record", {})
        elif "data" in json_data:
            record = json_data.get("data", {}).get("record", {})
        if record:
            return record.get("sourceCode", None)
        return None
    except json.JSONDecodeError as e:
        logging.error(f"JSON 解析错误: {e}")
        return None

def save_code_to_file(pid, code_id, language, submit_time, code):
    """ 保存代码到文件 """
    ext_map = {
        27: "cpp", 28: "cpp", 12: "cpp", 4: "cpp", 11: "cpp",
        2: "c",
        25: "py", 7: "py",
        19: "hs",
        15: "rs",
        17: "cs",
    }
    file_ext = ext_map.get(language, "txt")
    file_name = f"{pid}-{submit_time}.{file_ext}"
    file_path = os.path.join(OUTPUT_DIR, file_name)

    with open(file_path, "w", encoding="utf-8") as file:
        file.write(code)
    
    logging.info(f"✅ 代码已保存: {file_path}")

def fetch_records():
    """ 爬取所有记录 """
    page_id = 0
    while True:
        url = f"{BASE_URL}/record/list?user={USER_ID}&page={page_id}"
        html_content = get_html_content(url)

        # 立即保存本页HTML，便于分析
        with open(f"debug_record_list_page{page_id}.html", "w", encoding="utf-8") as f:
            f.write(html_content)

        decoded_json = extract_json_text(html_content)

        if not decoded_json:
            logging.info("没有解析到 JSON，结束爬取")
            break

        # 新增：打印 JSON 片段和类型，便于调试
        logging.debug(f"JSON片段: {str(decoded_json)[:200]}")
        logging.debug(f"JSON类型: {type(decoded_json)}")

        try:
            json_data = json.loads(decoded_json)
            # 兼容 currentData 和 data
            if "currentData" in json_data:
                records = json_data.get("currentData", {}).get("records", {}).get("result", [])
            elif "data" in json_data:
                records = json_data.get("data", {}).get("records", {}).get("result", [])
            else:
                records = []
            logging.info(f"本页记录数: {len(records)}")
        except json.JSONDecodeError as e:
            logging.error(f"解析 JSON 失败，跳过当前页: {e}")
            logging.error(f"出错内容片段: {str(decoded_json)[:200]}")
            continue

        if not records:
            logging.info("没有更多记录，结束爬取")
            break

        for record in records:
            if record.get("score") != record.get("problem", {}).get("fullScore"):
                continue

            pid = record.get("problem", {}).get("pid")
            code_id = record.get("id")
            language = record.get("language", -1)
            submit_time = record.get("submitTime", 0)

            if not pid or not code_id:
                continue

            record_url = f"{BASE_URL}/record/{code_id}"
            record_html = get_html_content(record_url)
            record_json = extract_json_text(record_html)

            if not record_json:
                continue

            code = get_code_from_json(record_json)
            if not code:
                continue

            save_code_to_file(pid, code_id, language, submit_time, code)

            # **增加随机延迟，防止触发反爬**
            delay = random.randint(2, 6)
            logging.info(f"⏳ 延迟 {delay} 秒...")
            time.sleep(delay)

        page_id += 1

if __name__ == "__main__":
    fetch_records()
