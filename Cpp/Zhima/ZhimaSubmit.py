from playwright.sync_api import sync_playwright
import os
import json
import time

# 配置
BASE_URL = "https://www.zhimaoi.cn/org/b3f41b76-6101-444a-9ddf-2aad7ce28b1f/solution?page=2"
LOGIN_URL = "https://www.zhimaoi.cn/auth/login/password"
USERNAME = "xuyunxuan"  # 替换为您的用户名
PASSWORD = "20131116"  # 替换为您的密码
OUTPUT_DIR = "output_zhima"
os.makedirs(OUTPUT_DIR, exist_ok=True)

def login(page):
    print("正在打开登录页面并填写登录信息...")
    page.goto(LOGIN_URL)
    page.fill('input[type="text"]', USERNAME)
    page.fill('input[type="password"]', PASSWORD)
    page.click('button[type="submit"]')

    # 等待登录完成
    page.wait_for_load_state("networkidle")
    if "login" in page.url:
        raise Exception("登录失败，请检查用户名和密码")
    print("登录成功！")

def extract_records(page):
    """
    爬取主页面数据并筛选得分 > 50 的记录
    """
    print("加载目标页面中...")
    page.goto(BASE_URL)

    # 等待表格加载完成且行数据不再显示“加载中”
    print("等待表格内容加载...")
    page.wait_for_function(
        """() => {
            const rows = document.querySelectorAll("table tbody tr");
            if (rows.length === 0) return false;
            return Array.from(rows).every(row => !row.innerText.includes("加载中"));
        }""",
        timeout=10000
    )
    print("表格内容加载完成")

    rows = page.query_selector_all("table tbody tr")
    print(f"找到 {len(rows)} 行数据，开始处理...")

    if len(rows) == 0:
        print("未找到任何数据，结束爬取。")
        return []

    filtered_records = []

    for index, row in enumerate(rows):
        try:
            # 提取问题标题和链接
            title_element = row.query_selector("td:nth-child(3) a")
            if not title_element:
                print(f"第 {index + 1} 行未找到标题链接，跳过。")
                continue

            title = title_element.inner_text().strip()
            problem_link = title_element.get_attribute("href")
            if not problem_link:
                print(f"第 {index + 1} 行未找到问题链接，跳过。")
                continue

            # 提取得分
            score_element = row.query_selector("td:nth-child(6) code")
            if not score_element:
                print(f"第 {index + 1} 行未找到得分信息，跳过。")
                continue

            score = int(score_element.inner_text().strip())
            print(f"标题: {title}, 得分: {score}")

            # 提取评测结果链接
            result_element = row.query_selector("td:nth-child(5) a")
            if result_element:
                submission_link = result_element.get_attribute("href")
                print(f"找到评测结果链接: {submission_link}")
            else:
                submission_link = None
                print("未找到评测结果链接。")

            if score > 50:
                filtered_records.append({
                    "title": title,
                    "score": score,
                    "problem_link": f"https://www.zhimaoi.cn{problem_link}",
                    "submission_link": f"https://www.zhimaoi.cn{submission_link}" if submission_link else None
                })
        except Exception as e:
            print(f"第 {index + 1} 行处理失败: {e}")

    print(f"已筛选出 {len(filtered_records)} 条符合条件的记录")
    return filtered_records

def fetch_problem_info(page, link):
    """
    爬取题目信息
    """
    print(f"正在打开题目页面: {link}")
    page.goto(link)
    try:
        page.wait_for_function(
            """() => {
                const content = document.querySelector('.markdown-body');
                return content && content.innerText.trim().length > 0;
            }""",
            timeout=10000
        )
        problem_content = page.query_selector(".markdown-body").inner_text().strip()
        return problem_content
    except Exception as e:
        print(f"获取题目信息失败: {e}")
        return "未能提取到题目信息"

def fetch_submission_code(page, link):
    """
    爬取评测结果中的完整代码信息
    """
    print(f"正在打开评测结果页面: {link}")
    page.goto(link)
    try:
        # 等待 Monaco Editor 的初步内容加载
        page.wait_for_function(
            """() => {
                const editor = document.querySelector('.monaco-editor .view-lines');
                return editor && editor.textContent.trim().length > 0;
            }""",
            timeout=30000
        )
        print("评测结果页面加载完成，开始滚动提取完整代码内容...")

        # 模拟滚动操作，获取完整代码
        full_code = []
        max_scrolls = 20  # 限制最大滚动次数
        for _ in range(max_scrolls):
            # 提取当前可见代码段
            current_code = page.evaluate(
                """() => {
                    const editor = document.querySelector('.monaco-editor .view-lines');
                    if (!editor) return null;

                    const lines = editor.querySelectorAll('.view-line');
                    return Array.from(lines).map(line => line.innerText).join('\\n');
                }"""
            )
            if current_code and current_code not in full_code:
                full_code.append(current_code)

            # 滚动到下一部分
            scrolled = page.evaluate(
                """() => {
                    const editor = document.querySelector('.monaco-scrollable-element');
                    if (!editor) return false;

                    const beforeScroll = editor.scrollTop;
                    editor.scrollTop += editor.clientHeight;
                    return editor.scrollTop > beforeScroll;
                }"""
            )
            if not scrolled:
                break  # 滚动到末尾时退出
            time.sleep(0.5)  # 短暂等待滚动加载内容

        if full_code:
            print("完整代码提取完成！")
            return "\n".join(full_code).strip()
        else:
            return "未能提取到完整代码内容"
    except Exception as e:
        print(f"获取完整代码信息失败: {e}")
        return "未能提取到完整代码内容"

def main():
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=False)
        page = browser.new_page()

        # 登录
        login(page)

        # 爬取主页面列表数据
        records = extract_records(page)
        if not records:
            print("未找到符合条件的记录，程序结束。")
            return

        print(f"总共找到 {len(records)} 条符合条件的记录，开始处理...")

        for index, record in enumerate(records):
            print(f"正在处理第 {index + 1} 条: {record['title']}")

            try:
                # 获取题目信息
                problem_info = fetch_problem_info(page, record["problem_link"])

                # 获取评测结果中的代码信息
                if record.get("submission_link"):
                    submission_code = fetch_submission_code(page, record["submission_link"])
                else:
                    submission_code = "无评测结果"

                # 保存结果
                result = {
                    "title": record["title"],
                    "score": record["score"],
                    "problem_info": problem_info,
                    "submission_code": submission_code,
                }
                today_date = time.strftime("%Y%m%d")
                output_file = os.path.join(OUTPUT_DIR, f"result_{today_date}_{index + 1}.json")
                with open(output_file, "w", encoding="utf-8") as f:
                    json.dump(result, f, indent=4, ensure_ascii=False)

                print(f"第 {index + 1} 条记录爬取完成，结果已保存到 {output_file}")
            except Exception as e:
                print(f"第 {index + 1} 条记录处理过程中出现错误: {e}")

        browser.close()

if __name__ == "__main__":
    main()
