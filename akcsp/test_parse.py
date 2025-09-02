import re

def test_file_parsing():
    # 读取文件内容
    file_path = r'D:\ChatgptKay\KayAgi\Cpp\AT\tag_problems_AT\普及-\consolidated_普及-_no_tag.md'
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    print(f'文件总长度: {len(content)} 字符')

    # 查找所有包含 pid: 的行
    pid_lines = []
    for line in content.split('\n'):
        if 'pid:' in line:
            pid_lines.append(line.strip())
            if len(pid_lines) <= 10:
                print(f'pid行 {len(pid_lines)}: {line.strip()}')

    print(f'总共找到 {len(pid_lines)} 个pid行')
    
    # 测试修复后的正则表达式
    print("\n测试修复后的正则表达式:")
    pid_pattern = r'pid:\s*([A-Z0-9_]+)'
    matches = re.findall(pid_pattern, content)
    print(f'使用修复后正则找到: {len(matches)} 个匹配')
    if matches:
        print(f'前几个匹配: {matches[:10]}')
    
    # 按修复后的逻辑分割
    sections = content.split('---\n')
    print(f'\n分割后段落数: {len(sections)}')

    # 统计有效段落
    valid_sections = 0
    for i, section in enumerate(sections):
        section = section.strip()
        if not section:
            continue
        
        # 检查是否包含 pid
        pid_match = re.search(r'pid:\s*([A-Z0-9_]+)', section)
        if pid_match:
            valid_sections += 1
            if valid_sections <= 10:  # 显示前10个
                pid = pid_match.group(1)
                print(f'找到题目 {valid_sections}: {pid}')

    print(f'总共找到 {valid_sections} 个有效题目')

if __name__ == "__main__":
    test_file_parsing() 