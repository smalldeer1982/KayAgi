import re
from collections import Counter

def extract_problem_tags(file_path):
    """
    从指定的Markdown文件中提取每个题目的标签信息
    """
    try:
        with open(file_path, "r", encoding="utf-8") as file:
            content = file.read()
            
            # 使用分隔符分割不同题目
            problems = content.split("\n---\n\n")
            
            all_tags = []
            problem_info = []
            no_tag_problems = []  # 存储无标签题目
            
            # 需要排除的标签
            excluded_tags = [
                'USACO', 'O2优化', 'Special Judge', '福建省历届夏令营', '语言月赛', '洛谷月赛', '洛谷原创',
                'COCI', 'NOIP 普及组', '蓝桥杯省赛', 'ICPC', '江苏', '信息与未来', 'NOIP 提高组', 'CCC', 'ROIR',
                '传智杯', '蓝桥杯国赛', '梦熊比赛', '各省省选', '山东', 'PA', 'CSP-X 小学组', '高校校赛', 'NOI 导刊',
                '安徽', '分类讨论', 'CSP-J 入门级', '提交答案', 'XCPC', 'JOI', 'Ad-hoc', 'NOISG', 'CSP-S 提高级',
                'POI', '北京', '陕西', 'Code+', '广东', 'BalticOI', 'NOI Online', 'BCSP-X', '洛谷比赛', 'IOI',
                'NOI', '天津', '交互题', '\ufeff基础算法', '南京', '福建', '小学科创活动', '湖北', '湖南', '河南',
                '集训队互测', '吉林', '逆元', '云南', 'CEOI', '澳门', '济南', '上海', '青岛'
            ]
            
            for problem in problems:
                if not problem.strip():
                    continue
                
                # 提取题目标题
                title_match = re.search(r"title:\s*\"?(.+?)\"?\n", problem)
                title = title_match.group(1).strip() if title_match else "未知题目"
                
                # 提取题目ID
                pid_match = re.search(r"pid:\s*(.+)", problem)
                pid = pid_match.group(1).strip() if pid_match else "未知ID"
                
                # 提取标签
                tag_match = re.search(r"tag:\s*\[(.*?)\]", problem)
                tags = []
                if tag_match:
                    raw_tags = tag_match.group(1)
                    if raw_tags.strip():  # 有非空标签
                        # 提取所有标签
                        all_raw_tags = [t.strip().strip("'\"") for t in re.split(r",\s*", raw_tags)]
                        
                        # 过滤掉需要排除的标签和纯数字标签
                        tags = [tag for tag in all_raw_tags 
                               if tag not in excluded_tags 
                               and not tag.isdigit() 
                               and not (tag.startswith('20') and len(tag) == 4)]
                
                # 如果没有标签或标签为空，加入到无标签列表
                if not tags:
                    no_tag_problems.append(f"- {title} (ID: {pid}) (过滤后无标签)")
                
                # 收集信息
                problem_info.append({
                    "title": title,
                    "pid": pid,
                    "tags": tags
                })
                all_tags.extend(tags)
            
            # 将无标签题目写入文件
            with open("tag_problems/普及-/consolidated_普及-_no_tag_list.md", "w", encoding="utf-8") as f:
                f.write("# 无标签题目列表\n\n")
                f.write("\n".join(sorted(no_tag_problems)))
            
            # 统计标签频率
            tag_counter = Counter(all_tags)
            
            return problem_info, tag_counter
    
    except Exception as e:
        print(f"❌ 错误：处理文件时出错 - {e}")
        return [], Counter()

def print_problem_tags(problem_info):
    """打印每个题目的标签信息"""
    print("\n📝 题目标签信息:")
    print("=" * 80)
    
    empty_tag_problems = []
    for i, problem in enumerate(problem_info, 1):
        print(f"{i}. {problem['title']} (ID: {problem['pid']})")
        if problem['tags']:
            print(f"   标签: {', '.join(problem['tags'])}")
        else:
            status = "空标签 []" if problem['has_empty_tag'] else "无标签"
            print(f"   标签: {status}")
            empty_tag_problems.append(problem)
        print("-" * 80)
    
    # 打印空标签题目汇总
    if empty_tag_problems:
        print("\n⚠️ 空标签题目汇总:")
        print("=" * 80)
        for problem in empty_tag_problems:
            status = "空标签 []" if problem['has_empty_tag'] else "无标签"
            print(f"- {problem['title']} (ID: {problem['pid']}) - {status}")

def print_tag_statistics(tag_counter):
    """打印标签统计信息"""
    if not tag_counter:
        print("\n⚠️ 未找到任何标签")
        return
    
    total_tags = sum(tag_counter.values())
    unique_tags = len(tag_counter)
    
    print(f"\n📊 标签统计 (共{unique_tags}种不同标签，总计{total_tags}个标签)")
    print("=" * 80)
    print("排名  标签名称                 出现次数  占比")
    print("-" * 80)
    
    for rank, (tag, count) in enumerate(tag_counter.most_common(), 1):
        percentage = (count / total_tags) * 100
        print(f"{rank:2d}.   {tag:<22} {count:5d}   {percentage:5.1f}%")

def process_tag_analysis(file_path):
    """处理tag_analysis.txt文件并修正标记"""
    with open(file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()
    
    # 跳过标题行
    header = lines[0]
    corrected_lines = [header]
    
    for line in lines[1:]:
        parts = line.strip().split('\t')
        if len(parts) >= 5:
            pid = parts[0]
            original_tag = parts[1]
            processed_tag = parts[2]
            
            # 如果原始标签和处理后标签都为空，应该标记为"是"
            is_empty = "是" if not original_tag.strip() and not processed_tag.strip() else "否"
            is_original_empty = "是" if not original_tag.strip() else "否"
            
            # 构建修正后的行
            corrected_line = f"{pid}\t{original_tag}\t{processed_tag}\t{is_empty}\t{is_original_empty}\n"
            corrected_lines.append(corrected_line)
    
    # 写回文件
    with open(file_path, 'w', encoding='utf-8') as f:
        f.writelines(corrected_lines)

if __name__ == "__main__":
    # 直接在代码中指定文件路径
    file_path = "tag_problems/普及/consolidated_普及_洛谷月赛.md"
    
    # 提取标签信息
    problem_info, tag_counter = extract_problem_tags(file_path)
    
    if problem_info:
        print(f"\n✅ 成功从文件中提取了{len(problem_info)}个题目的信息")
        
        # 打印每个题目的标签
        print_problem_tags(problem_info)
        
        # 打印标签统计
        print_tag_statistics(tag_counter)
    else:
        print("❌ 未能提取到题目信息")

    tag_analysis_path = "tag_problems/tag_analysis.txt"
    process_tag_analysis(tag_analysis_path)