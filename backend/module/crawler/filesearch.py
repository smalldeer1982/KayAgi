import os
import re

def extract_title(file_path):
    """从文件名或内容中提取题目名称"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            # 尝试从文件内容的第一行提取标题
            first_line = content.split('\n')[0].strip('# ')
            if first_line:
                return first_line
    except:
        # 如果读取失败，从文件名提取
        base_name = os.path.basename(file_path)
        return os.path.splitext(base_name)[0]
    return None

def extract_problem_info(file_path):
    """提取题目信息，包括题号和标题"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            lines = content.split('\n')
            
            # 尝试从前几行提取题目和题号
            title = None
            problem_id = None
            
            for line in lines[:10]:  # 检查前10行
                # 提取题号
                id_match = re.search(r'[PB]\d{4}|AT\d{4}', line)
                if id_match and not problem_id:
                    problem_id = id_match.group(0)
                
                # 提取标题（非空的第一行，去掉#号）
                if not title and line.strip():
                    title = line.strip('# \t')
            
            return {
                'title': title or os.path.splitext(os.path.basename(file_path))[0],
                'problem_id': problem_id,
                'file_path': file_path,
                'directory': os.path.basename(os.path.dirname(file_path)),
                'content': content[:1000]  # 保存前1000个字符用于内容匹配
            }
    except Exception as e:
        print(f"提取文件信息出错 {file_path}: {str(e)}")
        return None

def search_in_solutions(cpp_file_path, solution_dirs):
    """在题解目录中搜索对应的题目"""
    try:
        cpp_title = os.path.splitext(os.path.basename(cpp_file_path))[0]
        # 提取cpp文件名中的题号
        cpp_problem_id = re.search(r'[PB]\d{4}|AT\d{4}', cpp_title)
        cpp_problem_id = cpp_problem_id.group(0) if cpp_problem_id else None
        
        results = []
        seen_files = set()  # 用于去重
        
        for solution_dir in solution_dirs:
            for root, _, files in os.walk(solution_dir):
                for file in files:
                    if file.endswith('.md'):
                        md_path = os.path.join(root, file)
                        if md_path in seen_files:
                            continue
                            
                        md_info = extract_problem_info(md_path)
                        if not md_info:
                            continue
                            
                        # 多重匹配条件
                        matched = False
                        # 1. 题号匹配
                        if cpp_problem_id and md_info['problem_id'] and \
                           cpp_problem_id.lower() == md_info['problem_id'].lower():
                            matched = True
                        # 2. 标题包含关系
                        elif cpp_title.lower() in md_info['title'].lower() or \
                             md_info['title'].lower() in cpp_title.lower():
                            matched = True
                        # 3. 内容中包含题号或标题
                        elif cpp_title.lower() in md_info['content'].lower():
                            matched = True
                            
                        if matched:
                            seen_files.add(md_path)
                            results.append({
                                'cpp_file': cpp_file_path,
                                'solution_info': md_info
                            })
        
        return results
    except Exception as e:
        print(f"处理文件 {cpp_file_path} 时出错: {str(e)}")
        return []

def main():
    # 设置搜索目录
    cpp_dir = r"D:\KayCraft\C++\未整理"
    solution_dirs = [
        r"D:\ChatgptKay\Luogu-Problem-main\output_zhima_mdfile",
        r"D:\ChatgptKay\Luogu-Problem-main\submitcode_all",
        r"D:\ChatgptKay\Luogu-Problem-main\tag_problems",  
        r"D:\ChatgptKay\luogu_crawler-main\AT\tag_problems_AT",
    ]
    
    # 存储所有搜索结果
    all_results = []
    
    # 遍历C++文件目录
    for root, _, files in os.walk(cpp_dir):
        for file in files:
            if file.endswith(('.cpp', '.c')):
                cpp_path = os.path.join(root, file)
                results = search_in_solutions(cpp_path, solution_dirs)
                if results:
                    all_results.extend(results)
    # 输出结果
    output_file = "d:/ChatgptKay/luogu_crawler-main/search_results.md"
    if all_results:
        os.makedirs(os.path.dirname(output_file), exist_ok=True)
        
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write("# 文件搜索结果\n\n")
            
            # 按源文件分组
            file_groups = {}
            for result in all_results:
                cpp_file = result['cpp_file']
                if cpp_file not in file_groups:
                    file_groups[cpp_file] = []
                file_groups[cpp_file].append(result)
            
            # 输出每个源文件的匹配结果
            for cpp_file, matches in file_groups.items():
                f.write(f"## 源文件\n")
                f.write(f"- {cpp_file}\n\n")
                f.write("### 找到于\n")
                # 去重显示匹配结果
                seen = set()
                for match in matches:
                    info = (match['solution_info']['directory'], 
                           match['solution_info']['file_path'],
                           match['solution_info']['problem_id'])
                    if info not in seen:
                        seen.add(info)
                        f.write(f"- 目录：{info[0]}\n")
                        f.write(f"  文件：{info[1]}\n")
                        if info[2]:
                            f.write(f"  题号：{info[2]}\n")
                f.write("\n---\n\n")
        
        print(f"\n搜索结果已保存到：{output_file}")
    else:
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write("# 文件搜索结果\n\n未找到任何匹配的题目")
        print("\n未找到任何匹配的题目")

if __name__ == "__main__":
    main()