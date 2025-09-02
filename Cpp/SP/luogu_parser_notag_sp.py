import json
import urllib.request
import requests
import bs4 as bs
import re
import os
import time


def json_parser(html: str):
    try:
        print("\n=== HTML解析详细信息 ===")
        soup = bs.BeautifulSoup(html, "html.parser")
        
        # 查找 id 为 lentille-context 的 script 标签
        script = soup.find('script', id='lentille-context')
        if not script:
            print("未找到 lentille-context script 标签")
            return None
            
        print("找到 lentille-context script")
        
        try:
            # 直接解析JSON内容
            content = script.string.strip()
            js = json.loads(content)
            print("JSON解析成功")
            print("JSON数据结构:", list(js.keys()))
            return js
                
        except json.JSONDecodeError as e:
            print(f"JSON解析失败: {str(e)}")
            print(f"Script内容预览: {content[:200]}")
            return None
            
    except Exception as e:
        print(f"解析过程出现错误: {str(e)}")
        print(f"错误类型: {type(e)}")
        return None

def problem_markdown_parser(problem_js: dict, solutions: list = None):
    """将题目和题解数据转换为Markdown格式"""
    try:
        pid = problem_js["pid"]
        title = problem_js["title"]
        content = problem_js["content"]
        
        # 创建Markdown文件
        with open(f"{pid}-{title}.md", "w", encoding="utf-8") as f:
            # 写入题目部分
            f.write(f"# {title}\n\n")
            
            # 写入背景
            if content.get("background"):
                f.write("## 题目背景\n\n")
                f.write(f"{content['background']}\n\n")
                
            # 写入描述
            if content.get("description"):
                f.write("## 题目描述\n\n")
                f.write(f"{content['description']}\n\n")
                
            # 写入输入格式
            if content.get("inputFormat"):
                f.write("## 输入格式\n\n")
                f.write(f"{content['inputFormat']}\n\n")
                
            # 写入输出格式
            if content.get("outputFormat"):
                f.write("## 输出格式\n\n")
                f.write(f"{content['outputFormat']}\n\n")
                
            # 写入提示
            if content.get("hint"):
                f.write("## 说明/提示\n\n")
                f.write(f"{content['hint']}\n\n")
                
            # 写入样例
            if "samples" in problem_js:
                for i, sample in enumerate(problem_js["samples"], 1):
                    f.write(f"## 样例 #{i}\n\n")
                    f.write("### 输入\n\n")
                    f.write("```\n")
                    f.write(f"{sample[0]}")
                    f.write("```\n\n")
                    f.write("### 输出\n\n")
                    f.write("```\n")
                    f.write(f"{sample[1]}")
                    f.write("```\n\n")
            
            # 写入题解部分
            if solutions:
                f.write("# 题解\n\n")
                # 按点赞数排序题解
                solutions.sort(key=lambda x: x.get("upvote", 0), reverse=True)
                
                # 遍历所有题解
                for solution in solutions:
                    author = solution.get("author", {}).get("name", "匿名用户")
                    content = solution.get("content", "")
                    upvote = solution.get("upvote", 0)
                    
                    f.write(f"## 作者：{author} (赞：{upvote})\n\n")
                    f.write(f"{content}\n\n")
                    f.write("---\n\n")
                    
    except Exception as e:
        print(f"Markdown转换错误: {str(e)}")
        print(f"错误类型: {type(e)}")

def get_all_solutions(pid: str, headers: dict):
    """获取所有页的题解"""
    base_url = f"https://www.luogu.com.cn/problem/solution/{pid}"
    all_solutions = []
    page = 1
    
    while True:
        url = f"{base_url}?page={page}"
        print(f"\n=== 获取第 {page} 页题解 ===")
        print(f"请求URL: {url}")
        
        # 不需要每次请求都延迟，使用批次控制
        solution_rsp = requests.get(url, headers=headers)
        print(f"状态码: {solution_rsp.status_code}")
        
        if solution_rsp.status_code == 429:
            print("请求过于频繁，等待5秒后重试...")
            time.sleep(5)
            continue
            
        # 保存当前页面原始响应
        with open(f"debug_{pid}_solution_page{page}.html", "w", encoding="utf-8") as f:
            f.write(solution_rsp.text)
        
        solution_data = json_parser(solution_rsp.text)
        if not solution_data or "data" not in solution_data:
            print(f"第 {page} 页数据为空或格式错误")
            break
            
        solutions = solution_data["data"].get("solutions", {})
        if not solutions or not solutions.get("result"):
            print(f"第 {page} 页没有题解数据")
            break
            
        # 获取总页数
        total_count = solutions.get("count", 0)
        per_page = solutions.get("perPage", 10)
        total_pages = (total_count + per_page - 1) // per_page
        print(f"总题解数: {total_count}, 每页数量: {per_page}, 总页数: {total_pages}")
        
        # 添加当前页的题解
        all_solutions.extend(solutions["result"])
        
        if page >= total_pages:
            print("已获取所有页的题解")
            break
            
        page += 1
    
    return all_solutions

def solution_markdown_parser(solutions: list, pid: str, title: str):
    """将题解数据转换为Markdown格式"""
    try:
        if not solutions:
            print("没有找到有效的题解数据")
            return
            
        print(f"开始处理 {len(solutions)} 个题解")
        
        # 创建题解文件
        with open(f"{pid}-题解.md", "w", encoding="utf-8") as f:
            f.write(f"# {pid} {title} - 题解\n\n")
            
            # 按点赞数排序题解
            solutions.sort(key=lambda x: x.get("upvote", 0), reverse=True)
            
            # 遍历所有题解
            for solution in solutions:
                author = solution.get("author", {}).get("name", "匿名用户")
                content = solution.get("content", "")
                upvote = solution.get("upvote", 0)
                
                f.write(f"## 作者：{author} (赞：{upvote})\n\n")
                f.write(f"{content}\n\n")
                f.write("---\n\n")
                
    except Exception as e:
        print(f"题解转换错误: {str(e)}")
        print(f"错误类型: {type(e)}")

def pid_parser(pid: str):
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
        'Accept': 'application/json, text/javascript, */*; q=0.01',
        'Accept-Language': 'zh-CN,zh;q=0.9',
        'Accept-Encoding': 'gzip, deflate, br',
        'X-Requested-With': 'XMLHttpRequest',
        'Host': 'www.luogu.com.cn',
        'Connection': 'keep-alive',
        'Referer': f'https://www.luogu.com.cn/problem/{pid}',
        'sec-ch-ua': '"Chromium";v="116", "Not)A;Brand";v="24", "Google Chrome";v="116"',
        'sec-ch-ua-mobile': '?0',
        'sec-ch-ua-platform': '"Windows"',
        'Sec-Fetch-Dest': 'empty',
        'Sec-Fetch-Mode': 'cors',
        'Sec-Fetch-Site': 'same-origin',
        'Cookie': 'cf_clearance=ytIDOSETVJGXEpGNZMf4r_jRl9cKXClQ3Xbm_EOqlC8-1737880548-1.2.1.1-PXJsGuXHZwUeTr62SsgDXxLchdG.BO9wAzLdm3.pkWUe4FIrQ.jur7dPMW5higOSguNu4NwxrYKY6f7PCrAsVzXaQBiRbijGLtlpwTrU_aLA8Y2MOn1n7lO2f_zabIYhNnSb9HK9Q5nuWuLVFxwR5CEUI9hTKm2OuxJAhGKcC9AgmETKGoVlX9bxmwbf.K8iotHVlxLo1DUkDpdgedkyyMGsmMxb_sWK8Zie.s0WXTAyZ6sC0mVMHpRfdiSZBUQ2GNWqlvaSKebp2ptQsPxe0YCZNkpXBj1HUzVVhU63tbNpQBySZUKkqjDWMwyveNd7BDCU7MZjff1TWdp5Cebrqg; __client_id=d2eb73a0a9360e2867bbbee62d5fc4a0759e2623; _uid=1677231'  # 保持原有的Cookie
    }
    problem_url = "https://www.luogu.com.cn/problem/"
    solution_url = f"https://www.luogu.com.cn/problem/solution/{pid}"

    try:
        # 获取题目内容，不需要额外延迟
        problem_rsp = requests.get(problem_url + pid, headers=headers)
        print(f"题目请求状态码: {problem_rsp.status_code}")
        
        # 如果返回429，等待并重试
        if problem_rsp.status_code == 429:
            print("请求过于频繁，等待5秒后重试...")
            time.sleep(5)
            return pid_parser(pid)
            
        # 使用 json_parser 处理HTML响应
        problem_data = json_parser(problem_rsp.text)
        if not problem_data:
            print("题目数据为空")
            return
            
        print("问题数据结构:", list(problem_data.keys()))
        
        # 修改数据访问路径
        if "data" not in problem_data or "problem" not in problem_data["data"]:
            print("题目数据格式错误")
            print(f"数据结构: {problem_data}")
            return
            
        problem_js = problem_data["data"]["problem"]
        
        # 从contenu中获取内容
        content = problem_js.get("contenu", {})
        if not content:
            content = problem_js.get("content", {})  # 尝试备用字段
            
        # 构建完整的题目数据
        problem_data = {
            "pid": problem_js["pid"],
            "title": problem_js["title"],
            "content": content,
            "samples": problem_js.get("samples", [])
        }
        
        problem_markdown_parser(problem_data)
        
        # 获取题解内容
        all_solutions = []
        page = 1
        
        while True:
            current_url = f"{solution_url}?page={page}"
            print(f"\n=== 获取第 {page} 页题解 ===")
            print(f"请求URL: {current_url}")
            
            solution_rsp = requests.get(current_url, headers=headers)
            print(f"题解请求状态码: {solution_rsp.status_code}")
            
            solution_data = json_parser(solution_rsp.text)
            if not solution_data or "data" not in solution_data:
                print(f"第 {page} 页数据为空或格式错误")
                break
                
            solutions = solution_data["data"].get("solutions", {})
            if not solutions or not solutions.get("result"):
                print(f"第 {page} 页没有题解数据")
                break
                
            # 添加当前页的题解
            current_solutions = solutions["result"]
            all_solutions.extend(current_solutions)
            print(f"第 {page} 页找到 {len(current_solutions)} 个题解")
            
            page += 1
            
        if all_solutions:
            print(f"\n总共找到 {len(all_solutions)} 个题解")
            # 处理题目和题解，合并到一个文件中
            problem_markdown_parser(problem_data, all_solutions)
        else:
            print("没有找到任何题解")
            # 只处理题目
            problem_markdown_parser(problem_data)
            
    except Exception as e:
        print(f"题解处理错误: {str(e)}")
        print(f"错误位置: {e.__traceback__.tb_lineno}")


def read_json_file():
    # return json file
    with open("test.json", "r", encoding="utf-8") as f:
        return json.load(f)


def write_json_file(data):
    # write json file
    with open("test.json", "w", encoding="utf-8") as f:
        json.dump(data, f, indent=4)

def extract_problem_ids(file_path: str) -> list:
    """从文件中提取题号"""
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            content = f.read()
            # 使用正则表达式匹配题号
            pattern = r'- (AT_[^\s-]+) -'  # 匹配两个破折号之间的 AT_ 开头的内容
            problem_ids = re.findall(pattern, content)
            return problem_ids
    except Exception as e:
        print(f"读取文件错误: {str(e)}")
        return []

def process_problems(file_path: str):
    """处理文件中的所有题目"""
    # 从文件名中提取难度和分类
    filename = os.path.basename(file_path)
    parts = filename.replace('consolidated_', '').replace('_list.md', '').split('_')
    difficulty = parts[0]  # 普及-
    category = parts[1]    # 动态规划
    
    # 定义根目录和输出目录
    PROJECT_ROOT = r"D:\ChatgptKay\luogu_crawler-main\AT"  # 项目根目录
    OUTPUT_ROOT = os.path.join(PROJECT_ROOT, "solution_AT")  # 输出目录
    
    # 构建输出目录
    output_dir = os.path.join(OUTPUT_ROOT, difficulty, category)
    os.makedirs(output_dir, exist_ok=True)
    
    # 切换到输出目录
    current_dir = os.getcwd()
    os.chdir(output_dir)
    
    try:
        # 获取所有题号
        problem_ids = extract_problem_ids(file_path)
        print(f"找到 {len(problem_ids)} 个题目")
        
        # 批次处理变量
        batch_count = 0  # 当前批次处理的题目数
        batch_start_time = time.time()  # 当前批次开始时间
        
        # 处理每个题目
        for i, pid in enumerate(problem_ids, 1):
            print(f"\n开始处理第 {i}/{len(problem_ids)} 个题目: {pid}")
            pid_parser(pid)
            batch_count += 1
            
            # 检查是否需要休息
            current_time = time.time()
            time_elapsed = current_time - batch_start_time
            
            if batch_count >= 5 or time_elapsed >= 20:
                print(f"\n=== 已处理 {batch_count} 题，耗时 {time_elapsed:.2f} 秒 ===")
                print("休息10秒...")
                time.sleep(10)
                # 重置批次计数
                batch_count = 0
                batch_start_time = time.time()
            
    except Exception as e:
        print(f"处理过程出错: {str(e)}")
    finally:
        # 恢复原始目录
        os.chdir(current_dir)

if __name__ == "__main__":
    # 获取当前脚本所在目录的路径
    current_dir = os.path.dirname(os.path.abspath(__file__))
    # 构建完整的文件路径
    file_path = os.path.join(current_dir, "notag_problems_AT", "普及+", "consolidated_普及+_no_tag_list.md")
    
    print(f"尝试读取文件: {file_path}")
    # 检查文件是否存在
    if os.path.exists(file_path):
        print(f"文件存在")
        problem_ids = extract_problem_ids(file_path)
        print(f"提取到的题号: {problem_ids}")
    else:
        print(f"文件不存在，请检查路径")
    
    process_problems(file_path)
