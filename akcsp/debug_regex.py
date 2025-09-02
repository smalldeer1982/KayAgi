import re

def debug_regex():
    # 读取文件内容
    file_path = r'D:\ChatgptKay\KayAgi\Cpp\AT\tag_problems_AT\普及-\consolidated_普及-_no_tag.md'
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    # 查找第一个包含 pid: 的行的上下文
    lines = content.split('\n')
    pid_line_found = False
    for i, line in enumerate(lines):
        if 'pid:' in line and not pid_line_found:
            print("找到第一个pid行的上下文:")
            start = max(0, i-2)
            end = min(len(lines), i+3)
            for j in range(start, end):
                marker = " --> " if j == i else "     "
                print(f"{marker}第{j+1}行: {repr(lines[j])}")
            pid_line_found = True
            
            # 测试不同的正则表达式
            test_line = line
            print(f"\n测试行内容: {repr(test_line)}")
            
            patterns = [
                r'pid:\s*([A-Z0-9]+)',
                r'pid:\s*([A-Z0-9_]+)',
                r'pid:\s*(\S+)',
                r'pid:\s*([^\s]+)',
                r'pid:\s*(.*?)(?:\n|$)',
            ]
            
            for pattern in patterns:
                match = re.search(pattern, test_line)
                if match:
                    print(f"正则 {pattern} 匹配: {repr(match.group(1))}")
                else:
                    print(f"正则 {pattern} 无匹配")
            break
    
    # 检查多行匹配
    print("\n检查多行文本块:")
    sections = content.split('---\n')
    print(f"分割后段落数: {len(sections)}")
    
    for i, section in enumerate(sections[:3]):  # 只检查前3个段落
        section = section.strip()
        if not section:
            continue
            
        print(f"\n段落 {i+1} (前200字符):")
        print(repr(section[:200]))
        
        # 在段落中查找pid
        pid_match = re.search(r'pid:\s*([A-Z0-9_]+)', section)
        if pid_match:
            print(f"在段落中找到PID: {repr(pid_match.group(1))}")
        else:
            print("在段落中未找到PID")
            # 查看是否包含pid字符串
            if 'pid:' in section:
                print("段落包含'pid:'字符串，但正则不匹配")
                # 找到pid行
                for line in section.split('\n'):
                    if 'pid:' in line:
                        print(f"包含pid的行: {repr(line)}")

if __name__ == "__main__":
    debug_regex() 