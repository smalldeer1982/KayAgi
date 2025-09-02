import os
import re
from collections import defaultdict, Counter
import yaml
from datetime import datetime

def analyze_at_problems():
    """分析AtCoder问题的tag和难度信息"""
    
    # 难度映射
    DIFF_MAP = {
        "入门": "入门",
        "普及-": "普及-",
        "普及/提高-": "普及",
        "普及+/提高": "普及+",
        "提高+/省选-": "提高+",
        "省选/NOI-": "省选",
        "NOI/NOI+/CTSC": "NOI",
    }
    
    # 设置目录路径
    problems_dir = "Cpp/AT/problems_AT"
    
    # 起始和结束题目
    start_contest = 374
    end_contest = 410
    
    # 存储分析结果
    contest_data = defaultdict(list)  # 按期存储题目信息
    all_tags = []  # 所有tag
    problem_types = ['a', 'b', 'c', 'd', 'e', 'f', 'g']  # 题目类型
    diff_by_type = defaultdict(list)  # 按题目类型统计难度
    tag_by_type = defaultdict(list)  # 按题目类型统计tag
    
    print(f"开始分析 ABC{start_contest} 到 ABC{end_contest} 的题目...")
    
    # 遍历指定范围的比赛
    for contest_num in range(start_contest, end_contest + 1):
        contest_key = f"abc{contest_num}"
        print(f"\n正在处理 {contest_key.upper()}...")
        
        # 遍历每个题目类型
        for problem_type in problem_types:
            filename = f"AT_abc{contest_num}_{problem_type}-"
            
            # 查找匹配的文件
            matching_files = []
            if os.path.exists(problems_dir):
                for file in os.listdir(problems_dir):
                    if file.startswith(filename) and file.endswith('.md'):
                        matching_files.append(file)
            
            if not matching_files:
                print(f"  未找到题目: {contest_key}{problem_type}")
                continue
                
            # 处理找到的文件（通常只有一个）
            for file in matching_files:
                filepath = os.path.join(problems_dir, file)
                try:
                    with open(filepath, 'r', encoding='utf-8') as f:
                        content = f.read()
                    
                    # 解析YAML头部
                    if content.startswith('---'):
                        yaml_end = content.find('---', 3)
                        if yaml_end != -1:
                            yaml_content = content[3:yaml_end].strip()
                            try:
                                metadata = yaml.safe_load(yaml_content)
                                
                                # 提取信息
                                title = metadata.get('title', '未知标题')
                                diff = metadata.get('diff', '未知难度')
                                tags = metadata.get('tag', [])
                                
                                # 标准化难度
                                normalized_diff = DIFF_MAP.get(diff, diff)
                                
                                # 存储题目信息
                                problem_info = {
                                    'type': problem_type,
                                    'title': title,
                                    'diff': diff,
                                    'normalized_diff': normalized_diff,
                                    'tags': tags,
                                    'filename': file
                                }
                                contest_data[contest_key].append(problem_info)
                                
                                # 收集统计数据
                                all_tags.extend(tags)
                                diff_by_type[problem_type].append(normalized_diff)
                                tag_by_type[problem_type].extend(tags)
                                
                                print(f"  {problem_type}: {title} - 难度: {diff} - 标签: {tags}")
                                
                            except yaml.YAMLError as e:
                                print(f"  解析YAML失败: {file} - {e}")
                        else:
                            print(f"  YAML格式错误: {file}")
                    else:
                        print(f"  文件格式错误: {file}")
                        
                except Exception as e:
                    print(f"  读取文件失败: {file} - {e}")
    
    print("\n" + "="*60)
    print("分析结果汇总")
    print("="*60)
    
    # 准备MD文件内容
    md_content = []
    md_content.append("# AtCoder 题目分析报告")
    md_content.append(f"\n**生成时间：** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    md_content.append(f"\n**分析范围：** ABC{start_contest} 到 ABC{end_contest}")
    md_content.append("\n" + "="*60)
    md_content.append("\n## 分析结果汇总")
    md_content.append("="*60)
    
    # 1. 按期列出每题的难度和标签
    print("\n1. 按期题目详情:")
    md_content.append("\n### 1. 按期题目详情")
    
    for contest in sorted(contest_data.keys()):
        print(f"\n{contest.upper()}:")
        md_content.append(f"\n#### {contest.upper()}")
        
        problems = sorted(contest_data[contest], key=lambda x: x['type'])
        for problem in problems:
            tags_str = str(problem['tags']) if problem['tags'] else "[]"
            print(f"  {problem['type']}: {problem['title']}")
            print(f"      难度: {problem['normalized_diff']}")
            print(f"      标签: {tags_str}")
            
            md_content.append(f"- **{problem['type'].upper()}**: {problem['title']}")
            md_content.append(f"  - 难度: {problem['normalized_diff']}")
            md_content.append(f"  - 标签: {tags_str}")
    
    # 2. 统计出现最多的20个tag
    print("\n2. 出现最多的20个标签:")
    md_content.append("\n### 2. 出现最多的20个标签")
    
    tag_counter = Counter(all_tags)
    for i, (tag, count) in enumerate(tag_counter.most_common(20), 1):
        print(f"  {i:2d}. {tag}: {count}次")
        md_content.append(f"{i:2d}. **{tag}**: {count}次")
    
    # 3. 按题目类型统计难度分布和最多的5个tag
    print("\n3. 按题目类型统计:")
    md_content.append("\n### 3. 按题目类型统计")
    
    for problem_type in problem_types:
        if problem_type in diff_by_type:
            print(f"\n题目类型 {problem_type.upper()}:")
            md_content.append(f"\n#### 题目类型 {problem_type.upper()}")
            
            # 难度分布
            diff_counter = Counter(diff_by_type[problem_type])
            print("  难度分布:")
            md_content.append("\n**难度分布:**")
            for diff, count in diff_counter.most_common():
                print(f"    {diff}: {count}次")
                md_content.append(f"- {diff}: {count}次")
            
            # 最多的5个tag
            type_tag_counter = Counter(tag_by_type[problem_type])
            print("  最多的5个标签:")
            md_content.append("\n**最多的5个标签:**")
            for i, (tag, count) in enumerate(type_tag_counter.most_common(5), 1):
                print(f"    {i}. {tag}: {count}次")
                md_content.append(f"{i}. {tag}: {count}次")
    
    # 4. 总体统计
    print(f"\n4. 总体统计:")
    md_content.append("\n### 4. 总体统计")
    
    total_contests = len(contest_data)
    total_problems = sum(len(problems) for problems in contest_data.values())
    total_unique_tags = len(set(all_tags))
    
    print(f"  处理的比赛数: {total_contests}")
    print(f"  处理的题目数: {total_problems}")
    print(f"  不同标签数: {total_unique_tags}")
    print(f"  标签总出现次数: {len(all_tags)}")
    
    md_content.append(f"- **处理的比赛数:** {total_contests}")
    md_content.append(f"- **处理的题目数:** {total_problems}")
    md_content.append(f"- **不同标签数:** {total_unique_tags}")
    md_content.append(f"- **标签总出现次数:** {len(all_tags)}")
    
    # 5. 难度分布总览
    print(f"\n5. 总体难度分布:")
    md_content.append("\n### 5. 总体难度分布")
    
    all_diffs = []
    for problems in contest_data.values():
        for problem in problems:
            all_diffs.append(problem['normalized_diff'])
    
    diff_counter = Counter(all_diffs)
    for diff, count in diff_counter.most_common():
        print(f"  {diff}: {count}次")
        md_content.append(f"- **{diff}**: {count}次")
    
    # 保存到MD文件
    md_file_path = r"D:\ChatgptKay\PageAgi\atcoder分析.md"
    
    # 确保目录存在
    os.makedirs(os.path.dirname(md_file_path), exist_ok=True)
    
    try:
        with open(md_file_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(md_content))
        print(f"\n分析结果已保存到: {md_file_path}")
    except Exception as e:
        print(f"\n保存MD文件失败: {e}")

if __name__ == "__main__":
    analyze_at_problems()