from playwright.sync_api import sync_playwright
import os
import re
import time

# 配置
LOGIN_URL = "https://www.zhimaoi.cn/auth/login/password"
USERNAME = "xuyunxuan"  # 替换为您的用户名
PASSWORD = "20131116"  # 替换为您的密码
OUTPUT_DIR = os.path.join("Cpp", "Zhima", "zhima_problems")  # 修改保存路径
os.makedirs(OUTPUT_DIR, exist_ok=True)

# 定义多个题目链接
PROBLEM_URLS = [
    "https://www.zhimaoi.cn/org/b3f41b76-6101-444a-9ddf-2aad7ce28b1f/contest/f7c52296-1116-4adf-a5bf-daad001b329a/problem/53cb8f81-a775-4818-9496-6168e59425f9",
    "https://www.zhimaoi.cn/org/b3f41b76-6101-444a-9ddf-2aad7ce28b1f/contest/f7c52296-1116-4adf-a5bf-daad001b329a/problem/41c96ee9-cf0c-4d50-aee2-1fbbba7f94c3",
    "https://www.zhimaoi.cn/org/b3f41b76-6101-444a-9ddf-2aad7ce28b1f/contest/f7c52296-1116-4adf-a5bf-daad001b329a/problem/847b4e62-3d60-418f-85d6-d5fa50d6b808",
]

def login(page):
    """登录芝麻平台"""
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

def sanitize_filename(filename):
    """处理文件名，移除非法字符"""
    return re.sub(r'[\\/*?:"<>|]', "_", filename)

def fetch_problem_to_md(page, problem_url):
    """获取指定链接的题目并保存为Markdown格式"""
    print(f"正在访问题目链接: {problem_url}")
    page.goto(problem_url)
    
    try:
        # 等待题目内容加载
        page.wait_for_function(
            """() => {
                const content = document.querySelector('.markdown-body');
                return content && content.innerText.trim().length > 0;
            }""",
            timeout=10000
        )
        
        # 提取题目标题 - 改进标题选择器
        # 尝试多种可能的选择器以提高成功率
        title = None
        
        # 方法1: 获取页面 title 标签内容并处理
        page_title = page.title()
        if page_title and " - " in page_title:
            # 通常页面标题格式为 "题目名称 - 芝麻OI"
            title = page_title.split(" - ")[0].strip()
        
        # 方法2: 尝试不同的选择器
        if not title:
            selectors = [
                "h1.text-xl", 
                ".problem-title", 
                "h1", 
                ".problem-header h1", 
                ".problem-name",
                "header h1",
                "main h1"
            ]
            
            for selector in selectors:
                element = page.query_selector(selector)
                if element:
                    title_text = element.inner_text().strip()
                    if title_text:
                        title = title_text
                        break
        
        # 方法3: 使用评估JavaScript获取标题
        if not title:
            title = page.evaluate("""
                () => {
                    // 尝试找到所有标题元素
                    const headers = Array.from(document.querySelectorAll('h1, h2, header strong, .title')); 
                    // 过滤掉空标题
                    const validHeaders = headers.filter(h => h.innerText.trim().length > 0);
                    // 返回第一个非空标题
                    return validHeaders.length > 0 ? validHeaders[0].innerText.trim() : null;
                }
            """)
        
        # 如果还是没找到标题，尝试从URL中提取问题ID作为标题
        if not title:
            match = re.search(r'problem/([^/?]+)', problem_url)
            if match:
                title = f"Problem-{match.group(1)}"
            else:
                title = "未知题目"
        
        print(f"获取到题目标题: {title}")
        
        # 获取题目内容
        problem_content = page.query_selector(".markdown-body").inner_html()
        
        # 将HTML内容转换为Markdown格式
        problem_content = page.evaluate("""(html) => {
            return html
                .replace(/<h1[^>]*>(.*?)<\/h1>/gi, '# $1\\n\\n')
                .replace(/<h2[^>]*>(.*?)<\/h2>/gi, '## $1\\n\\n')
                .replace(/<h3[^>]*>(.*?)<\/h3>/gi, '### $1\\n\\n')
                .replace(/<h4[^>]*>(.*?)<\/h4>/gi, '#### $1\\n\\n')
                .replace(/<h5[^>]*>(.*?)<\/h5>/gi, '##### $1\\n\\n')
                .replace(/<h6[^>]*>(.*?)<\/h6>/gi, '###### $1\\n\\n')
                .replace(/<p[^>]*>(.*?)<\/p>/gi, '$1\\n\\n')
                .replace(/<br\s*\/?>/gi, '\\n')
                .replace(/<ul[^>]*>(.*?)<\/ul>/gis, '$1\\n')
                .replace(/<ol[^>]*>(.*?)<\/ol>/gis, '$1\\n')
                .replace(/<li[^>]*>(.*?)<\/li>/gi, '- $1\\n')
                .replace(/<code[^>]*>(.*?)<\/code>/gi, '`$1`')
                .replace(/<pre[^>]*>(.*?)<\/pre>/gis, '```\\n$1\\n```\\n')
                .replace(/<strong[^>]*>(.*?)<\/strong>/gi, '**$1**')
                .replace(/<em[^>]*>(.*?)<\/em>/gi, '*$1*')
                .replace(/<a[^>]*href="([^"]*)"[^>]*>(.*?)<\/a>/gi, '[$2]($1)')
                .replace(/<[^>]*>/g, '')
                .replace(/&lt;/g, '<')
                .replace(/&gt;/g, '>')
                .replace(/&amp;/g, '&')
                .replace(/&quot;/g, '"')
                .replace(/&apos;/g, "'")
                .trim();
        }""", problem_content)
        
        # 获取问题编号/ID (如果有的话)
        problem_id = ""
        id_match = re.search(r'problem/([^/?]+)', problem_url)
        if id_match:
            problem_id = id_match.group(1)
        
        # 创建Markdown文件 - 加上问题ID前缀以便排序
        if problem_id:
            filename = sanitize_filename(f"{problem_id}_{title}.md")
        else:
            filename = sanitize_filename(f"{title}.md")
            
        filepath = os.path.join(OUTPUT_DIR, filename)
        
        with open(filepath, "w", encoding="utf-8") as f:
            f.write(f"# {title}\n\n")
            f.write(problem_content)
            f.write(f"\n\n---\n来源: {problem_url}")
        
        print(f"成功保存题目: {filepath}")
        return True
    except Exception as e:
        print(f"获取题目详情失败: {e}")
        return False

def main():
    # 确保URL合法
    if not PROBLEM_URLS[0].startswith("https://www.zhimaoi.cn/"):
        print("错误: URL必须是芝麻平台的链接")
        return
    
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=False)  # headless=False 可以看到浏览器操作过程
        context = browser.new_context()
        page = context.new_page()
        
        try:
            # 登录
            login(page)
            
            # 下载所有指定题目
            for url in PROBLEM_URLS:
                print(f"\n正在处理题目: {url}")
                success = fetch_problem_to_md(page, url)
                
                if success:
                    print(f"题目下载成功!")
                else:
                    print(f"题目下载失败。")
                
                # 短暂等待，避免请求过快
                time.sleep(1)
                
        except Exception as e:
            print(f"程序执行过程中出现错误: {e}")
        finally:
            browser.close()

if __name__ == "__main__":
    main() 