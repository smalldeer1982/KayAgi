import json
import urllib.request
import requests
import bs4 as bs
import re
import os
import time


# 难度映射表
difficulty_mapping = {
    1: "入门",
    2: "普及-",
    3: "普及/提高-",
    4: "普及+/提高",
    5: "提高+/省选-",
    6: "省选/NOI-",
    7: "NOI/NOI+/CTSC"
}


def json_parser(html: str):
    try:
        soup = bs.BeautifulSoup(html, "html.parser")
        
        # 首先尝试查找 id 为 lentille-context 的 script 标签
        script = soup.find('script', id='lentille-context')
        
        if script:
            # 提取 script 标签中的 JSON 数据
            json_str = script.string.strip()
            data = json.loads(json_str)
            return data
        else:
            # 尝试查找包含 window._feInjection 的脚本
            scripts = soup.find_all('script')
            for script in scripts:
                if script.string and 'window._feInjection' in script.string:
                    # 提取 JSON 数据
                    json_str = script.string.strip()
                    # 提取 JSON 部分
                    json_start = json_str.find('window._feInjection = JSON.parse(decodeURIComponent("')
                    if json_start != -1:
                        json_start += len('window._feInjection = JSON.parse(decodeURIComponent("')
                        json_end = json_str.find('"))', json_start)
                        if json_end != -1:
                            encoded_json = json_str[json_start:json_end]
                            # 解码 URL 编码的 JSON 字符串
                            decoded_json = urllib.parse.unquote(encoded_json)
                            data = json.loads(decoded_json)
                            return data
            
            return None
    except Exception as e:
        print(f"JSON解析错误: {str(e)}")
        return None

def sanitize_filename(filename):
    """清理文件名，移除非法字符"""
    # 替换Windows文件系统中不允许的字符
    invalid_chars = r'<>:"/\|?*'
    for char in invalid_chars:
        filename = filename.replace(char, '_')
    
    # 替换其他可能导致问题的字符
    filename = filename.replace('\n', ' ').replace('\r', ' ')
    
    # 限制文件名长度
    if len(filename) > 200:
        filename = filename[:197] + '...'
    
    return filename



def parse_problem_list(problem_type="CF", start_page=1, max_pages=None):
    """
    解析题目列表页面，获取题目ID
    
    Args:
        problem_type: 题目类型，如 CF（CodeForces）
        start_page: 起始页码
        max_pages: 最大页数，None表示爬取所有页
    
    Returns:
        题目ID列表
    """
    base_url = f"https://www.luogu.com.cn/problem/list?type={problem_type}"
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
    }
    
    all_problem_ids = []
    current_page = start_page
    
    while True:
        page_url = f"{base_url}&page={current_page}"
        print(f"\n=== 获取第 {current_page} 页题目列表 ===")
        print(f"请求URL: {page_url}")
        
        try:
            response = requests.get(page_url, headers=headers)
            print(f"状态码: {response.status_code}")
            
            # 解析HTML获取题目列表
            soup = bs.BeautifulSoup(response.text, "html.parser")
            
            # 尝试获取JSON数据
            json_data = json_parser(response.text)
            if json_data:
                # 从JSON数据中提取题目信息
                if "currentData" in json_data and "problems" in json_data["currentData"]:
                    problems_data = json_data["currentData"]["problems"]
                    
                    # 提取题目列表
                    for problem in problems_data.get("result", []):
                        problem_id = problem.get("pid", "")
                        if problem_id:
                            all_problem_ids.append(problem_id)
                            print(f"从JSON找到题目ID: {problem_id}")
                    
                    # 检查是否有下一页
                    if len(problems_data.get("result", [])) < 50 or (max_pages and current_page >= max_pages):
                        print("已到达最后一页或达到最大页数限制")
                        break
                    
                    current_page += 1
                    time.sleep(1)  # 避免请求过于频繁
                    continue
            
            # 如果JSON解析失败，尝试从HTML中提取
            problem_items = soup.select('a[href^="/problem/"]')
            page_problem_ids = []
            
            for item in problem_items:
                try:
                    href = item.get('href')
                    if href and '/problem/' in href:
                        problem_id = href.split('/problem/')[1]
                        if problem_id and problem_id not in page_problem_ids:
                            page_problem_ids.append(problem_id)
                            print(f"从HTML找到题目ID: {problem_id}")
                except Exception as e:
                    print(f"处理题目项时出错: {str(e)}")
            
            if page_problem_ids:
                all_problem_ids.extend(page_problem_ids)
            else:
                print("本页未找到题目ID")
                break
            
            # 检查是否有下一页
            next_page = soup.select_one('a.page-link[aria-label="Next"]')
            if not next_page or (max_pages and current_page >= max_pages):
                print("已到达最后一页或达到最大页数限制")
                break
            
            current_page += 1
            time.sleep(1)  # 避免请求过于频繁
            
        except Exception as e:
            print(f"处理第 {current_page} 页时出错: {str(e)}")
            break
    
    # 去重
    all_problem_ids = list(dict.fromkeys(all_problem_ids))
    print(f"\n总共找到 {len(all_problem_ids)} 个题目ID")
    
    return all_problem_ids

def process_problem_list(problem_type="CF", start_page=1, max_pages=None, max_problems=None):
    """
    处理题目列表，获取详细信息
    
    Args:
        problem_type: 题目类型
        start_page: 起始页码
        max_pages: 最大页数
        max_problems: 最大题目数量
    """
    # 创建输出目录
    output_dir = f"problems_{problem_type}"
    os.makedirs(output_dir, exist_ok=True)
    
    # 切换到输出目录
    current_dir = os.getcwd()
    os.chdir(output_dir)
    
    try:
        # 获取题目ID列表
        problem_ids = parse_problem_list(problem_type, start_page, max_pages)
        
        if max_problems:
            problem_ids = problem_ids[:max_problems]
        
        # 批次处理变量
        batch_count = 0  # 当前批次处理的题目数
        batch_start_time = time.time()  # 当前批次开始时间
        
        # 处理每个题目
        for i, pid in enumerate(problem_ids, 1):
            print(f"\n处理第 {i}/{len(problem_ids)} 个题目: {pid}")
            
            try:
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
                print(f"处理题目 {pid} 时出错: {str(e)}")
    
    except Exception as e:
        print(f"处理题目列表时出错: {str(e)}")
    
    finally:
        # 恢复原始目录
        os.chdir(current_dir)

def parse_tag_info(tag_id=None, max_pages=1):
    """
    解析特定标签的题目列表，获取标签信息和题目
    
    Args:
        tag_id: 标签ID，如4表示动态规划
        max_pages: 最大页数
    
    Returns:
        题目列表和标签信息
    """
    if tag_id is None:
        base_url = "https://www.luogu.com.cn/problem/list"
    else:
        base_url = f"https://www.luogu.com.cn/problem/list?tag={tag_id}"
    
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
    }
    
    all_problems = []
    tag_name = f"标签{tag_id}" if tag_id else "全部"
    
    # 创建日志目录
    log_dir = "html_logs"
    os.makedirs(log_dir, exist_ok=True)
    
    for page in range(1, max_pages + 1):
        page_url = f"{base_url}&page={page}" if tag_id else f"{base_url}?page={page}"
        print(f"\n=== 获取标签 {tag_id} 第 {page} 页题目列表 ===")
        print(f"请求URL: {page_url}")
        
        try:
            response = requests.get(page_url, headers=headers)
            print(f"状态码: {response.status_code}")
            
            # 保存原始HTML响应到文件
            html_filename = f"{log_dir}/tag_{tag_id}_page_{page}.html"
            with open(html_filename, "w", encoding="utf-8") as f:
                f.write(response.text)
            print(f"已保存HTML响应到: {html_filename}")
            
            # 解析HTML获取题目列表
            soup = bs.BeautifulSoup(response.text, "html.parser")
            
            # 尝试获取标签名称
            tag_header = soup.select_one('h1.lfe-h1')
            if tag_header:
                header_text = tag_header.text.strip()
                if '：' in header_text:
                    tag_name = header_text.split('：')[1].strip()
                    print(f"找到标签名称: {tag_name}")
            
            # 尝试获取JSON数据
            json_data = json_parser(response.text)
            
            # 保存解析后的JSON数据
            if json_data:
                json_filename = f"{log_dir}/tag_{tag_id}_page_{page}_data.json"
                with open(json_filename, "w", encoding="utf-8") as f:
                    json.dump(json_data, f, indent=4, ensure_ascii=False)
                print(f"已保存JSON数据到: {json_filename}")
            
            if json_data and "currentData" in json_data:
                # 从JSON数据中提取标签信息
                if "tagMap" in json_data["currentData"]:
                    tag_map = json_data["currentData"]["tagMap"]
                    for tag_key, tag_value in tag_map.items():
                        print(f"标签ID: {tag_key}, 标签名称: {tag_value}")
                
                # 从JSON数据中提取题目信息
                if "problems" in json_data["currentData"]:
                    problems_data = json_data["currentData"]["problems"]
                    
                    # 提取题目列表
                    for problem in problems_data.get("result", []):
                        problem_id = problem.get("pid", "")
                        title = problem.get("title", "")
                        difficulty = problem.get("difficulty", 0)
                        
                        if problem_id:
                            problem_info = {
                                "id": problem_id,
                                "title": title,
                                "difficulty": difficulty_mapping.get(difficulty, "未知"),
                                "tags": [tag_name] if tag_id else []
                            }
                            all_problems.append(problem_info)
                            print(f"从JSON找到题目: {problem_id} - {title}")
            
            # 如果JSON解析失败，尝试从HTML中提取
            if not all_problems:
                problem_items = soup.select('.lg-table-row')
                for item in problem_items:
                    try:
                        problem_id = item.select_one('.pid').text.strip()
                        title = item.select_one('.title').text.strip()
                        
                        problem_info = {
                            "id": problem_id,
                            "title": title,
                            "difficulty": "未知",
                            "tags": [tag_name] if tag_id else []
                        }
                        
                        all_problems.append(problem_info)
                        print(f"从HTML找到题目: {problem_id} - {title}")
                    except Exception as e:
                        print(f"处理题目项时出错: {str(e)}")
            
            # 检查是否有下一页
            if page >= max_pages:
                print(f"已达到最大页数限制: {max_pages}")
                break
                
        except Exception as e:
            print(f"处理标签 {tag_id} 第 {page} 页时出错: {str(e)}")
            break
    
    print(f"\n总共找到 {len(all_problems)} 个题目")
    
    # 保存所有题目信息到文件
    with open(f"tag_{tag_id}_problems.json", "w", encoding="utf-8") as f:
        json.dump(all_problems, f, indent=4, ensure_ascii=False)
    
    return all_problems, tag_name

def extract_tag_from_file(file_path, target_tag_id):
    """
    从题目文件中提取标签信息
    
    Args:
        file_path: 题目文件路径
        target_tag_id: 目标标签ID
    
    Returns:
        标签中文名称，未找到则返回None
    """
    try:
        # 需要排除的标签
        excluded_tags = ['USACO', 'O2优化', 'Special Judge', '福建省历届夏令营', '语言月赛', '洛谷月赛', '各省省选', '2015', '江苏', 'NOIP 普及组', 'NOIP 提高组']
        
        # 根据文件扩展名选择不同的解析方法
        if file_path.endswith('.json'):
            # JSON文件解析
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
                problem_data = json.loads(content)
            
            print(f"题目文件内容类型: {type(problem_data)}")
            
            # 打印文件中的标签信息用于调试
            if "tags" in problem_data:
                tags = problem_data["tags"]
                print(f"题目标签: {tags}")
                
                # 查找目标标签ID
                for tag in tags:
                    print(f"检查标签: {tag}")
                    
                    # 处理不同格式的标签数据
                    if isinstance(tag, dict):
                        if "id" in tag and "name" in tag:
                            if str(tag["id"]) == str(target_tag_id):
                                tag_name = tag["name"]
                                # 检查标签名称是否应该被排除
                                if tag_name.isdigit() or (len(tag_name) == 4 and tag_name.isdigit()) or tag_name in excluded_tags:
                                    print(f"标签名称 {tag_name} 被排除")
                                    continue
                                return tag_name
                        elif str(target_tag_id) in tag:
                            tag_name = tag[str(target_tag_id)]
                            # 检查标签名称是否应该被排除
                            if tag_name.isdigit() or (len(tag_name) == 4 and tag_name.isdigit()) or tag_name in excluded_tags:
                                print(f"标签名称 {tag_name} 被排除")
                                continue
                            return tag_name
                    elif isinstance(tag, list) and len(tag) >= 2:
                        # 处理[id, name]格式
                        if str(tag[0]) == str(target_tag_id):
                            tag_name = tag[1]
                            # 检查标签名称是否应该被排除
                            if tag_name.isdigit() or (len(tag_name) == 4 and tag_name.isdigit()) or tag_name in excluded_tags:
                                print(f"标签名称 {tag_name} 被排除")
                                continue
                            return tag_name
            else:
                print(f"题目文件中没有tags字段")
                # 尝试查找其他可能包含标签信息的字段
                for key, value in problem_data.items():
                    if "tag" in key.lower():
                        print(f"找到可能的标签字段: {key} = {value}")
        
        elif file_path.endswith('.md'):
            # Markdown文件解析
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            print(f"MD文件大小: {len(content)} 字节")
            
            # 在Markdown文件中查找标签信息
            # 可能的格式：
            # 1. 标签：字符串, 模拟, ...
            # 2. tags: [字符串, 模拟, ...]
            # 3. 标签: #字符串 #模拟 ...
            # 4. tag: ['模拟']
            
            # 查找标签行
            tag_patterns = [
                r'标签[：:]\s*(.*?)(?:\n|$)',  # 标签：xxx
                r'tags[：:]\s*(.*?)(?:\n|$)',  # tags: xxx
                r'tag[：:]\s*(.*?)(?:\n|$)',   # tag: xxx
                r'标签[：:]\s*#(.*?)(?:\n|$)'   # 标签：#xxx
            ]
            
            tag_line = None
            for pattern in tag_patterns:
                match = re.search(pattern, content, re.IGNORECASE)
                if match:
                    tag_line = match.group(1).strip()
                    print(f"找到标签行: {tag_line}")
                    break
            
            if tag_line:
                # 处理特殊格式：tag: ['模拟']
                if tag_line.startswith('[') and tag_line.endswith(']'):
                    # 提取引号中的内容
                    tags = re.findall(r"'([^']*)'|\"([^\"]*)\"", tag_line)
                    # 合并匹配组
                    tags = [t[0] if t[0] else t[1] for t in tags]
                    print(f"从数组格式提取的标签: {tags}")
                else:
                    # 分割标签
                    tags = []
                    if ',' in tag_line:
                        # 逗号分隔
                        tags = [tag.strip() for tag in tag_line.split(',')]
                    elif '，' in tag_line:
                        # 中文逗号分隔
                        tags = [tag.strip() for tag in tag_line.split('，')]
                    elif '#' in tag_line:
                        # #号分隔
                        tags = [tag.strip() for tag in tag_line.split('#') if tag.strip()]
                    elif ' ' in tag_line:
                        # 空格分隔
                        tags = [tag.strip() for tag in tag_line.split() if tag.strip()]
                    else:
                        # 单个标签
                        tags = [tag_line]
                
                # 过滤掉需要排除的标签
                filtered_tags = []
                for tag in tags:
                    # 排除在排除列表中的标签
                    if tag in excluded_tags:
                        print(f"排除标签(在排除列表中): {tag}")
                        continue
                    # 排除纯数字的标签
                    if tag.isdigit():
                        print(f"排除标签(纯数字): {tag}")
                        continue
                    # 排除4位数字表示年份的标签
                    if len(tag) == 4 and tag.isdigit():
                        print(f"排除标签(4位数字年份): {tag}")
                        continue
                    # 保留其他标签
                    filtered_tags.append(tag)
                
                print(f"原始标签: {tags}")
                print(f"过滤后的标签: {filtered_tags}")
                
                # 如果过滤后没有标签了，返回None
                if not filtered_tags:
                    print("过滤后没有有效标签")
                    return None
                
                # 根据标签ID查找对应的中文名称
                # 这里需要一个标签ID到中文名称的映射表
                # 由于我们正在构建这个映射表，这里可能需要一些预定义的映射
                predefined_tags = {
                    "1": "字符串",
                    "2": "模拟",
                    "3": "搜索",
                    "4": "动态规划",
                    "5": "数学",
                    # 可以添加更多已知的映射
                }
                
                # 检查标签是否匹配目标ID
                if str(target_tag_id) in predefined_tags and predefined_tags[str(target_tag_id)] in filtered_tags:
                    return predefined_tags[str(target_tag_id)]
                
                # 如果没有预定义映射，但标签数量与ID匹配，可以尝试按顺序映射
                if 0 < target_tag_id <= len(filtered_tags):
                    return filtered_tags[target_tag_id - 1]
            
            else:
                print("未在MD文件中找到标签行")
        
        return None
    
    except Exception as e:
        print(f"读取文件 {file_path} 时出错: {str(e)}")
        return None

def extract_tag_from_file_with_debug(file_path, target_tag_id):
    """
    从题目文件中提取标签信息，并输出详细调试信息
    
    Args:
        file_path: 题目文件路径
        target_tag_id: 目标标签ID
    
    Returns:
        标签中文名称，未找到则返回None
    """
    print(f"\n=== 从文件提取标签 {target_tag_id}: {file_path} ===")
    
    try:
        # 需要排除的标签
        excluded_tags = ['USACO', 'O2优化', 'Special Judge', '福建省历届夏令营', '语言月赛', '洛谷月赛', '各省省选', '2015', '江苏', 'NOIP 普及组']
        
        # 根据文件扩展名选择不同的解析方法
        if file_path.endswith('.json'):
            # JSON文件解析
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
                print(f"文件大小: {len(content)} 字节")
                problem_data = json.loads(content)
            
            print(f"文件内容类型: {type(problem_data)}")
            print(f"顶级字段: {list(problem_data.keys())}")
            
            # 打印文件中的标签信息用于调试
            if "tags" in problem_data:
                tags = problem_data["tags"]
                print(f"标签数量: {len(tags)}")
                print(f"标签内容: {tags}")
                
                # 查找目标标签ID
                for i, tag in enumerate(tags):
                    print(f"检查标签 {i+1}: {tag} (类型: {type(tag)})")
                    
                    # 处理不同格式的标签数据
                    if isinstance(tag, dict):
                        print(f"字典标签字段: {list(tag.keys())}")
                        if "id" in tag and "name" in tag:
                            print(f"标准格式标签: id={tag['id']}, name={tag['name']}")
                            if str(tag["id"]) == str(target_tag_id):
                                tag_name = tag["name"]
                                # 检查标签名称是否应该被排除
                                if tag_name.isdigit() or (len(tag_name) == 4 and tag_name.isdigit()) or tag_name in excluded_tags:
                                    print(f"标签名称 {tag_name} 被排除")
                                    continue
                                print(f"找到匹配标签: {tag_name}")
                                return tag_name
                        elif str(target_tag_id) in tag:
                            tag_name = tag[str(target_tag_id)]
                            # 检查标签名称是否应该被排除
                            if tag_name.isdigit() or (len(tag_name) == 4 and tag_name.isdigit()) or tag_name in excluded_tags:
                                print(f"标签名称 {tag_name} 被排除")
                                continue
                            print(f"键值格式标签: {target_tag_id}={tag_name}")
                            return tag_name
                    elif isinstance(tag, list) and len(tag) >= 2:
                        # 处理[id, name]格式
                        print(f"列表格式标签: {tag}")
                        if str(tag[0]) == str(target_tag_id):
                            tag_name = tag[1]
                            # 检查标签名称是否应该被排除
                            if tag_name.isdigit() or (len(tag_name) == 4 and tag_name.isdigit()) or tag_name in excluded_tags:
                                print(f"标签名称 {tag_name} 被排除")
                                continue
                            print(f"找到匹配标签: {tag_name}")
                            return tag_name
                    else:
                        print(f"未知格式标签: {tag}")
            else:
                print(f"题目文件中没有tags字段")
                # 尝试查找其他可能包含标签信息的字段
                for key, value in problem_data.items():
                    if "tag" in key.lower():
                        print(f"找到可能的标签字段: {key} = {value}")
        
        elif file_path.endswith('.md'):
            # Markdown文件解析
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            print(f"MD文件大小: {len(content)} 字节")
            print(f"文件前100个字符: {content[:100]}")
            
            # 在Markdown文件中查找标签信息
            # 可能的格式：
            # 1. 标签：字符串, 模拟, ...
            # 2. tags: [字符串, 模拟, ...]
            # 3. 标签: #字符串 #模拟 ...
            # 4. tag: ['模拟']
            
            # 查找标签行
            tag_patterns = [
                r'标签[：:]\s*(.*?)(?:\n|$)',  # 标签：xxx
                r'tags[：:]\s*(.*?)(?:\n|$)',  # tags: xxx
                r'tag[：:]\s*(.*?)(?:\n|$)',   # tag: xxx
                r'标签[：:]\s*#(.*?)(?:\n|$)'   # 标签：#xxx
            ]
            
            tag_line = None
            for pattern in tag_patterns:
                match = re.search(pattern, content, re.IGNORECASE)
                if match:
                    tag_line = match.group(1).strip()
                    print(f"找到标签行: {tag_line}")
                    break
            
            if tag_line:
                # 处理特殊格式：tag: ['模拟']
                if tag_line.startswith('[') and tag_line.endswith(']'):
                    # 提取引号中的内容
                    tags = re.findall(r"'([^']*)'|\"([^\"]*)\"", tag_line)
                    # 合并匹配组
                    tags = [t[0] if t[0] else t[1] for t in tags]
                    print(f"从数组格式提取的标签: {tags}")
                else:
                    # 分割标签
                    tags = []
                    if ',' in tag_line:
                        # 逗号分隔
                        tags = [tag.strip() for tag in tag_line.split(',')]
                    elif '，' in tag_line:
                        # 中文逗号分隔
                        tags = [tag.strip() for tag in tag_line.split('，')]
                    elif '#' in tag_line:
                        # #号分隔
                        tags = [tag.strip() for tag in tag_line.split('#') if tag.strip()]
                    elif ' ' in tag_line:
                        # 空格分隔
                        tags = [tag.strip() for tag in tag_line.split() if tag.strip()]
                    else:
                        # 单个标签
                        tags = [tag_line]
                
                # 过滤掉需要排除的标签
                filtered_tags = []
                for tag in tags:
                    # 排除在排除列表中的标签
                    if tag in excluded_tags:
                        print(f"排除标签(在排除列表中): {tag}")
                        continue
                    # 排除纯数字的标签
                    if tag.isdigit():
                        print(f"排除标签(纯数字): {tag}")
                        continue
                    # 排除4位数字表示年份的标签
                    if len(tag) == 4 and tag.isdigit():
                        print(f"排除标签(4位数字年份): {tag}")
                        continue
                    # 保留其他标签
                    filtered_tags.append(tag)
                
                print(f"原始标签: {tags}")
                print(f"过滤后的标签: {filtered_tags}")
                
                # 如果过滤后没有标签了，返回None
                if not filtered_tags:
                    print("过滤后没有有效标签")
                    return None
                
                # 根据标签ID查找对应的中文名称
                predefined_tags = {
                    "1": "字符串",
                    "2": "模拟",
                    "3": "搜索",
                    "4": "动态规划",
                    "5": "数学",
                    # 可以添加更多已知的映射
                }
                
                # 检查标签是否匹配目标ID
                if str(target_tag_id) in predefined_tags and predefined_tags[str(target_tag_id)] in filtered_tags:
                    print(f"找到匹配标签: {predefined_tags[str(target_tag_id)]}")
                    return predefined_tags[str(target_tag_id)]
                
                # 如果没有预定义映射，但标签数量与ID匹配，可以尝试按顺序映射
                if 0 < target_tag_id <= len(filtered_tags):
                    print(f"按顺序映射找到标签: {filtered_tags[target_tag_id - 1]}")
                    return filtered_tags[target_tag_id - 1]
                
                print(f"未找到与ID {target_tag_id} 匹配的标签")
            else:
                print("未在MD文件中找到标签行")
                # 尝试打印文件的一部分内容以便调试
                print("文件内容片段:")
                lines = content.split('\n')
                for i, line in enumerate(lines[:20]):  # 打印前20行
                    print(f"{i+1}: {line}")
        
        print(f"未找到标签 {target_tag_id}")
        return None
    
    except Exception as e:
        print(f"读取文件 {file_path} 时出错: {str(e)}")
        return None

def save_tag_mapping(tag_mapping):
    """
    保存标签映射到文件
    
    Args:
        tag_mapping: 标签ID到中文名称的映射表
    """
    # 保存为JSON格式
    with open("tag_mapping_result.json", "w", encoding="utf-8") as f:
        json.dump(tag_mapping, f, indent=4, ensure_ascii=False)
    
    # 保存为文本格式，便于查看
    with open("tag_mapping_result.txt", "w", encoding="utf-8") as f:
        for tag_id, tag_name in sorted(tag_mapping.items(), key=lambda x: int(x[0]) if str(x[0]).isdigit() else 999999):
            f.write(f"{tag_id}={tag_name}\n")
    
    print(f"已保存标签映射，共 {len(tag_mapping)} 个")

def direct_extract_tag_names():
    """
    直接从洛谷网站提取标签名称
    """
    print("尝试直接从洛谷网站提取标签名称...")
    
    # 访问洛谷主页或题目列表页
    url = "https://www.luogu.com.cn/problem/list"
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
    }
    
    try:
        response = requests.get(url, headers=headers)
        print(f"状态码: {response.status_code}")
        
        # 解析JSON数据
        json_data = json_parser(response.text)
        
        if json_data and "currentData" in json_data:
            # 尝试从不同位置提取标签信息
            tag_mapping = {}
            
            # 1. 从tagMap中提取
            if "tagMap" in json_data["currentData"]:
                tag_map = json_data["currentData"]["tagMap"]
                print(f"找到tagMap: {tag_map}")
                
                for tag_id, tag_name in tag_map.items():
                    tag_mapping[int(tag_id)] = tag_name
                    print(f"从tagMap找到标签: {tag_id} -> {tag_name}")
            
            # 2. 从其他可能的位置提取
            for key, value in json_data["currentData"].items():
                if "tag" in key.lower() and isinstance(value, dict):
                    print(f"找到可能的标签数据: {key}")
                    for tag_id, tag_name in value.items():
                        if tag_id.isdigit() and tag_id not in tag_mapping:
                            tag_mapping[int(tag_id)] = tag_name
                            print(f"从{key}找到标签: {tag_id} -> {tag_name}")
            
            # 保存结果
            if tag_mapping:
                save_tag_mapping(tag_mapping)
                print(f"成功提取了 {len(tag_mapping)} 个标签")
                return tag_mapping
            else:
                print("未找到标签信息")
                return {}
        
    except Exception as e:
        print(f"直接提取标签名称时出错: {str(e)}")
        return {}

def check_problems_directory(problems_dir):
    """
    检查problems目录的结构和文件内容
    
    Args:
        problems_dir: 题目文件目录
    """
    print(f"\n=== 检查 {problems_dir} 目录 ===")
    
    if not os.path.exists(problems_dir):
        print(f"错误: {problems_dir} 目录不存在!")
        return
    
    # 统计文件数量
    file_count = 0
    json_count = 0
    
    # 列出目录结构
    for root, dirs, files in os.walk(problems_dir):
        rel_path = os.path.relpath(root, problems_dir)
        if rel_path == '.':
            print(f"根目录: {root}")
        else:
            print(f"子目录: {rel_path}")
        
        # 统计文件
        for file in files:
            file_count += 1
            if file.endswith('.json'):
                json_count += 1
                
                # 检查前几个文件的内容
                if json_count <= 3:
                    file_path = os.path.join(root, file)
                    print(f"\n检查文件: {file_path}")
                    try:
                        with open(file_path, 'r', encoding='utf-8') as f:
                            content = f.read()
                            data = json.loads(content)
                            
                            # 检查文件结构
                            print(f"文件大小: {len(content)} 字节")
                            print(f"顶级字段: {list(data.keys())}")
                            
                            # 检查是否有tags字段
                            if "tags" in data:
                                print(f"标签数量: {len(data['tags'])}")
                                print(f"标签内容: {data['tags']}")
                                
                                # 检查标签格式
                                if len(data['tags']) > 0:
                                    first_tag = data['tags'][0]
                                    print(f"第一个标签类型: {type(first_tag)}")
                                    print(f"第一个标签内容: {first_tag}")
                            else:
                                print("文件中没有tags字段")
                                
                                # 查找可能包含标签的其他字段
                                for key in data.keys():
                                    if "tag" in key.lower():
                                        print(f"可能的标签字段: {key} = {data[key]}")
                    except Exception as e:
                        print(f"读取文件时出错: {str(e)}")
    
    print(f"\n总计: {file_count} 个文件, 其中 {json_count} 个JSON文件")

def build_tag_mapping_sequential(start_tag=1, end_tag=300):
    """
    按顺序构建标签ID到中文名称的映射表
    
    Args:
        start_tag: 起始标签ID
        end_tag: 结束标签ID
    
    Returns:
        标签ID到中文名称的映射表
    """
    tag_mapping = {}
    problems_dir = "problems"  # 存放题目文件的目录
    
    # 确保problems目录存在
    if not os.path.exists(problems_dir):
        print(f"警告: {problems_dir}目录不存在，请确保已爬取题目")
        problems_dir = input("请输入存放题目文件的目录路径: ")
    
    # 按顺序处理标签
    for tag_id in range(start_tag, end_tag + 1):
        # 如果已经找到了这个标签的映射，跳过
        if tag_id in tag_mapping and not tag_mapping[tag_id].startswith("未知标签") and not tag_mapping[tag_id].startswith("错误:"):
            print(f"标签 {tag_id} 已有映射: {tag_mapping[tag_id]}，跳过")
            continue
            
        print(f"\n=== 处理标签ID: {tag_id} ===")
        
        # 获取标签页面
        try:
            # 获取该标签下的题目列表
            page = 1
            found = False
            all_problem_ids = []
            
            # 最多查找5页，每页最多100个题目
            while not found and page <= 5 and len(all_problem_ids) < 100:
                print(f"获取标签 {tag_id} 第 {page} 页题目...")
                
                # 获取该标签下的题目列表
                base_url = f"https://www.luogu.com.cn/problem/list?tag={tag_id}&page={page}"
                headers = {
                    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
                }
                
                response = requests.get(base_url, headers=headers)
                print(f"状态码: {response.status_code}")
                
                # 解析JSON数据
                json_data = json_parser(response.text)
                
                # 保存原始HTML和JSON数据用于调试
                debug_dir = "debug_logs"
                os.makedirs(debug_dir, exist_ok=True)
                
                with open(f"{debug_dir}/tag_{tag_id}_page_{page}.html", "w", encoding="utf-8") as f:
                    f.write(response.text)
                
                if json_data:
                    with open(f"{debug_dir}/tag_{tag_id}_page_{page}.json", "w", encoding="utf-8") as f:
                        json.dump(json_data, f, indent=4, ensure_ascii=False)
                
                # 首先尝试从currentData.tagMap中直接获取标签名称
                if json_data and "currentData" in json_data:
                    if "tagMap" in json_data["currentData"]:
                        tag_map = json_data["currentData"]["tagMap"]
                        print(f"找到tagMap: {tag_map}")
                        
                        if str(tag_id) in tag_map:
                            tag_name = tag_map[str(tag_id)]
                            tag_mapping[tag_id] = tag_name
                            print(f"直接从tagMap找到标签映射: {tag_id} -> {tag_name}")
                            found = True
                            
                            # 保存当前进度
                            save_tag_mapping(tag_mapping)
                            break
                
                # 提取题目ID列表
                if json_data and "currentData" in json_data and "problems" in json_data["currentData"]:
                    problems_data = json_data["currentData"]["problems"]
                    
                    # 提取题目ID列表
                    page_problem_ids = []
                    for problem in problems_data.get("result", []):
                        problem_id = problem.get("pid", "")
                        if problem_id:
                            page_problem_ids.append(problem_id)
                    
                    print(f"第 {page} 页找到 {len(page_problem_ids)} 个题目ID")
                    all_problem_ids.extend(page_problem_ids)
                    
                    # 如果这一页没有题目或者已经收集了足够多的题目，就停止
                    if not page_problem_ids or len(all_problem_ids) >= 100:
                        break
                
                page += 1
                time.sleep(2)  # 避免请求过于频繁
            
            # 如果没有直接从tagMap找到，则尝试从题目文件中提取
            if not found and all_problem_ids:
                print(f"共收集到 {len(all_problem_ids)} 个题目ID，开始从题目文件中提取标签")
                
                # 收集所有可能的标签名称
                tag_candidates = {}
                
                # 遍历题目文件，查找标签信息
                for pid in all_problem_ids:
                    print(f"处理题目: {pid}")
                    # 查找对应的题目文件
                    problem_file = find_problem_file(problems_dir, pid)
                    
                    if problem_file:
                        print(f"找到题目文件: {problem_file}")
                        # 读取题目文件，提取所有标签
                        all_tags = extract_all_tags_from_file(problem_file)
                        
                        if all_tags:
                            print(f"题目 {pid} 的所有标签: {all_tags}")
                            # 统计每个标签出现的次数
                            for tag in all_tags:
                                if tag not in tag_candidates:
                                    tag_candidates[tag] = 0
                                tag_candidates[tag] += 1
                    else:
                        print(f"未找到题目文件: {pid}")
                
                # 找出出现次数最多的标签
                if tag_candidates:
                    # 按出现次数排序
                    sorted_candidates = sorted(tag_candidates.items(), key=lambda x: x[1], reverse=True)
                    
                    # 选择出现次数最多的标签
                    most_common_tag = sorted_candidates[0]
                    tag_name = most_common_tag[0]
                    tag_mapping[tag_id] = tag_name
                    print(f"从题目文件找到最常见标签映射: {tag_id} -> {tag_name} (出现 {most_common_tag[1]} 次)")
                    
                    # 打印前5个最常见的标签供参考
                    print("前5个最常见的标签:")
                    for i, (tag, count) in enumerate(sorted_candidates[:5]):
                        print(f"  {i+1}. {tag}: {count}次")
                    
                    # 保存当前进度
                    save_tag_mapping(tag_mapping)
                    found = True
            
            # 如果没有找到映射，记录为未知
            if not found:
                tag_mapping[tag_id] = f"未知标签{tag_id}"
                print(f"未找到标签 {tag_id} 的映射")
            
        except Exception as e:
            print(f"处理标签 {tag_id} 时出错: {str(e)}")
            tag_mapping[tag_id] = f"错误:{str(e)}"
        
        # 每处理3个标签，保存一次结果
        if tag_id % 3 == 0:
            save_tag_mapping(tag_mapping)
            print(f"已保存当前进度，休息5秒...")
            time.sleep(5)  # 短暂休息
    
    # 最终保存结果
    save_tag_mapping(tag_mapping)
    return tag_mapping

def find_problem_file(problems_dir, problem_id):
    """
    在problems目录中查找指定题目ID的文件
    
    Args:
        problems_dir: 题目文件目录
        problem_id: 题目ID
    
    Returns:
        找到的文件路径，未找到则返回None
    """
    # 首先尝试直接匹配文件名（支持md和json格式）
    direct_matches = [
        os.path.join(problems_dir, f"{problem_id}.md"),
        os.path.join(problems_dir, f"{problem_id}.json"),
        os.path.join(problems_dir, f"problem_{problem_id}.md"),
        os.path.join(problems_dir, f"problem_{problem_id}.json"),
        os.path.join(problems_dir, f"P{problem_id}.md"),
        os.path.join(problems_dir, f"P{problem_id}.json")
    ]
    
    for path in direct_matches:
        if os.path.exists(path):
            return path
    
    # 遍历目录查找匹配的文件
    for root, _, files in os.walk(problems_dir):
        for file in files:
            file_lower = file.lower()
            pid_lower = problem_id.lower()
            
            # 检查文件名是否包含题目ID（支持md和json格式）
            if (pid_lower in file_lower or 
                f"p{pid_lower}" in file_lower or 
                f"_{pid_lower}" in file_lower) and (file.endswith('.json') or file.endswith('.md')):
                return os.path.join(root, file)
    
    return None

def find_problem_file_with_debug(problems_dir, problem_id):
    """
    在problems目录中查找指定题目ID的文件，并输出调试信息
    
    Args:
        problems_dir: 题目文件目录
        problem_id: 题目ID
    
    Returns:
        找到的文件路径，未找到则返回None
    """
    print(f"\n=== 查找题目文件: {problem_id} ===")
    
    # 首先尝试直接匹配文件名（支持md和json格式）
    direct_matches = [
        os.path.join(problems_dir, f"{problem_id}.md"),
        os.path.join(problems_dir, f"{problem_id}.json"),
        os.path.join(problems_dir, f"problem_{problem_id}.md"),
        os.path.join(problems_dir, f"problem_{problem_id}.json"),
        os.path.join(problems_dir, f"P{problem_id}.md"),
        os.path.join(problems_dir, f"P{problem_id}.json")
    ]
    
    for path in direct_matches:
        print(f"尝试直接匹配: {path}")
        if os.path.exists(path):
            print(f"找到匹配文件: {path}")
            return path
    
    # 遍历目录查找匹配的文件
    print("开始遍历目录查找...")
    for root, _, files in os.walk(problems_dir):
        for file in files:
            file_lower = file.lower()
            pid_lower = problem_id.lower()
            
            # 检查文件名是否包含题目ID（支持md和json格式）
            if (pid_lower in file_lower or 
                f"p{pid_lower}" in file_lower or 
                f"_{pid_lower}" in file_lower) and (file.endswith('.json') or file.endswith('.md')):
                path = os.path.join(root, file)
                print(f"找到匹配文件: {path}")
                return path
    
    print(f"未找到题目 {problem_id} 的文件")
    return None

def extract_all_tags_from_file(file_path):
    """
    从题目文件中提取所有标签
    
    Args:
        file_path: 题目文件路径
    
    Returns:
        标签列表，未找到则返回空列表
    """
    try:
        # 根据文件扩展名选择不同的解析方法
        if file_path.endswith('.json'):
            # JSON文件解析
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
                problem_data = json.loads(content)
            
            # 提取标签
            if "tags" in problem_data:
                tags = problem_data["tags"]
                
                # 处理不同格式的标签数据
                extracted_tags = []
                for tag in tags:
                    if isinstance(tag, dict):
                        if "name" in tag:
                            extracted_tags.append(tag["name"])
                    elif isinstance(tag, list) and len(tag) >= 2:
                        extracted_tags.append(tag[1])
                    elif isinstance(tag, str):
                        extracted_tags.append(tag)
                
                return extracted_tags
            
            return []
        
        elif file_path.endswith('.md'):
            # Markdown文件解析
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            # 在Markdown文件中查找标签信息
            tag_patterns = [
                r'标签[：:]\s*(.*?)(?:\n|$)',  # 标签：xxx
                r'tags[：:]\s*(.*?)(?:\n|$)',  # tags: xxx
                r'tag[：:]\s*(.*?)(?:\n|$)',   # tag: xxx
                r'标签[：:]\s*#(.*?)(?:\n|$)'   # 标签：#xxx
            ]
            
            tag_line = None
            for pattern in tag_patterns:
                match = re.search(pattern, content, re.IGNORECASE)
                if match:
                    tag_line = match.group(1).strip()
                    break
            
            if tag_line:
                # 处理特殊格式：tag: ['模拟']
                if tag_line.startswith('[') and tag_line.endswith(']'):
                    # 提取引号中的内容
                    tags = re.findall(r"'([^']*)'|\"([^\"]*)\"", tag_line)
                    # 合并匹配组
                    tags = [t[0] if t[0] else t[1] for t in tags]
                else:
                    # 分割标签
                    tags = []
                    if ',' in tag_line:
                        # 逗号分隔
                        tags = [tag.strip() for tag in tag_line.split(',')]
                    elif '，' in tag_line:
                        # 中文逗号分隔
                        tags = [tag.strip() for tag in tag_line.split('，')]
                    elif '#' in tag_line:
                        # #号分隔
                        tags = [tag.strip() for tag in tag_line.split('#') if tag.strip()]
                    elif ' ' in tag_line:
                        # 空格分隔
                        tags = [tag.strip() for tag in tag_line.split() if tag.strip()]
                    else:
                        # 单个标签
                        tags = [tag_line]
                
                return tags
            
            return []
        
        return []
    
    except Exception as e:
        print(f"读取文件 {file_path} 时出错: {str(e)}")
        return []

if __name__ == "__main__":
    # 检查problems目录
    problems_dir = "problems"
    check_problems_directory(problems_dir)
    
    # 测试查找特定题目
    test_problem_id = "P1001"
    problem_file = find_problem_file_with_debug(problems_dir, test_problem_id)
    
    if problem_file:
        # 测试提取标签
        for tag_id in [1, 2, 3]:
            extract_tag_from_file_with_debug(problem_file, tag_id)
    
    # 首先尝试直接提取标签名称
    tag_mapping = direct_extract_tag_names()
    
    if not tag_mapping:
        print("直接提取失败，尝试从题目文件中提取...")
        # 构建标签映射表，按顺序处理标签1、2、3...
        tag_mapping = build_tag_mapping_sequential(start_tag=301, end_tag=450)
    
    print("标签映射表构建完成")
    
    # 显示部分结果
    print("\n部分标签映射结果:")
    for tag_id, tag_name in sorted(list(tag_mapping.items())[:20], key=lambda x: int(x[0]) if str(x[0]).isdigit() else 999999):
        print(f"{tag_id}={tag_name}")
