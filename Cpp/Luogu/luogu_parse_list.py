import os
import re
import requests
import json
import urllib.parse
from bs4 import BeautifulSoup

LIST_TXT = r"D:\ChatgptKay\KayAgi\Cpp\Luogu\list.txt"
OUTPUT_MD = r"D:\ChatgptKay\KayAgi\Cpp\Luogu\training_problems.md"
DEBUG_DIR = r"D:\ChatgptKay\KayAgi\Cpp\Luogu\debug"
os.makedirs(DEBUG_DIR, exist_ok=True)

# 从 luogusubmit.py 复制的 Cookie 和请求头
COOKIE = ""

HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36",
    "Cookie": COOKIE,
    "Accept": "application/json, text/javascript, */*; q=0.01",
    "Accept-Language": "zh-CN,zh;q=0.9",
    "Accept-Encoding": "gzip, deflate, br",
    "X-Requested-With": "XMLHttpRequest",
    "Host": "www.luogu.com.cn",
    "Connection": "keep-alive",
    "Referer": "https://www.luogu.com.cn/",
    "sec-ch-ua": '"Chromium";v="116", "Not)A;Brand";v="24", "Google Chrome";v="116"',
    "sec-ch-ua-mobile": "?0",
    "sec-ch-ua-platform": '"Windows"',
    "Sec-Fetch-Dest": "empty",
    "Sec-Fetch-Mode": "cors",
    "Sec-Fetch-Site": "same-origin",
}

def parse_list_line(line):
    # 100 =【入门1】顺序结构
    m = re.match(r"(\d+)\s*=\s*[\【\[](.*?)[\】\]]\s*(.*)", line)
    if not m:
        return None
    num = m.group(1)
    raw_cat = m.group(2)
    sub_cat = m.group(3).strip()
    # 处理大类（去掉数字，只保留汉字）
    main_cat = re.sub(r"\d+", "", raw_cat)
    return num, main_cat, sub_cat

def fetch_training_problems(training_id):
    url = f"https://www.luogu.com.cn/training/{training_id}#problems"
    print(f"请求: {url}")
    
    try:
        response = requests.get(url, headers=HEADERS)
        print(f"状态码: {response.status_code}")
        
        html_file = os.path.join(DEBUG_DIR, f"training_{training_id}.html")
        with open(html_file, "w", encoding="utf-8") as f:
            f.write(response.text)
        print(f"已保存HTML到: {html_file}")
        
        if response.status_code != 200:
            return []
            
        soup = BeautifulSoup(response.text, "html.parser")
        scripts = soup.find_all("script")
        for script in scripts:
            if script.string and "window._feInjection" in script.string:
                match = re.search(r'window\._feInjection\s*=\s*JSON\.parse\(decodeURIComponent\("([^"]+)"\)\)', script.string)
                if match:
                    encoded_json = match.group(1)
                    json_str = urllib.parse.unquote(encoded_json)
                    json_file = os.path.join(DEBUG_DIR, f"training_{training_id}.json")
                    with open(json_file, "w", encoding="utf-8") as f:
                        f.write(json_str)
                    print(f"已保存JSON到: {json_file}")
                    
                    data = json.loads(json_str)
                    problems = []
                    if "currentData" in data:
                        training = data["currentData"].get("training", {})
                        problem_list = training.get("problems", [])
                        for item in problem_list:
                            prob = item.get("problem", {})
                            pid = prob.get("pid", "")
                            title = prob.get("title", "")
                            problems.append((pid, title))
                    return problems
    except Exception as e:
        print(f"请求或解析出错: {e}")
    return []

def main():
    results = []
    with open(LIST_TXT, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line or "=" not in line:
                continue
            parsed = parse_list_line(line)
            if not parsed:
                continue
            num, main_cat, sub_cat = parsed
            print(f"\n处理训练编号 {num}（{main_cat} - {sub_cat}）")
            problems = fetch_training_problems(num)
            for pid, title in problems:
                title = title or "未获取到标题"  # 如果没有标题就用占位符
                results.append(f"{pid} | {title} | {main_cat} | {sub_cat}")

    with open(OUTPUT_MD, "w", encoding="utf-8") as f:
        f.write("# 训练题单题目列表\n\n")
        f.write("题号 | 题目名称 | 大类 | 小类\n")
        f.write("---|---|---|---\n")
        for line in results:
            f.write(line + "\n")
    print(f"已保存结果到: {OUTPUT_MD}")

if __name__ == "__main__":
    main()