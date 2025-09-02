import re

def test_fixed_parsing():
    # 读取文件内容
    file_path = r'D:\ChatgptKay\KayAgi\Cpp\AT\tag_problems_AT\普及-\consolidated_普及-_no_tag.md'
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    print(f'文件总长度: {len(content)} 字符')
    
    # 测试修复后的正则表达式
    print("测试修复后的完整题目ID匹配:")
    pid_pattern = r'pid:\s*([A-Z0-9_]+)'
    matches = re.findall(pid_pattern, content)
    print(f'使用修复后正则找到: {len(matches)} 个匹配')
    if matches:
        print(f'前10个匹配: {matches[:10]}')
        print(f'后10个匹配: {matches[-10:]}')
    
    # 按修复后的逻辑分割
    sections = content.split('---\n')
    print(f'\n分割后段落数: {len(sections)}')

    # 统计有效段落
    valid_problems = []
    for i, section in enumerate(sections):
        section = section.strip()
        if not section:
            continue
        
        # 检查是否包含 pid
        pid_match = re.search(r'pid:\s*([A-Z0-9_]+)', section)
        if pid_match:
            pid = pid_match.group(1)
            
            # 提取标题
            title_match = re.search(r'title:\s*"([^"]+)"', section)
            title = title_match.group(1) if title_match else f"题目{pid}"
            
            valid_problems.append({
                'pid': pid,
                'title': title
            })

    print(f'总共找到 {len(valid_problems)} 个有效题目')
    
    # 显示前10个题目的详细信息
    print("\n前10个题目的详细信息:")
    for i, problem in enumerate(valid_problems[:10]):
        print(f'{i+1}. PID: {problem["pid"]}, 标题: {problem["title"]}')
    
    # 检查题目ID的唯一性
    pid_set = set(p['pid'] for p in valid_problems)
    print(f'\n唯一题目ID数量: {len(pid_set)}')
    if len(pid_set) != len(valid_problems):
        print("警告: 存在重复的题目ID!")
        from collections import Counter
        pid_counts = Counter(p['pid'] for p in valid_problems)
        duplicates = {pid: count for pid, count in pid_counts.items() if count > 1}
        print(f"重复的题目ID: {duplicates}")

if __name__ == "__main__":
    test_fixed_parsing() 