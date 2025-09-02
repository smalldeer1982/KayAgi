import os
import re
from collections import Counter

def extract_tags_and_content(file_path):
    """
    从 Markdown 文件中提取标签(tag)和正文内容，并解析题号。
    """
    with open(file_path, "r", encoding="utf-8") as file:
        content = file.read()

        # 提取标签，支持 ['动态规划 DP'] 格式
        tag_match = re.search(r"tag:\s*\[(.*?)\]", content)
        if tag_match:
            raw_tags = tag_match.group(1)
            # **拆分时考虑含空格的 tag**
            tags = [t.strip().strip("'\"") for t in re.split(r",\s*", raw_tags)]
        else:
            tags = []

        # 提取题号
        title_match = re.search(r"title:\s*\"?(.+?)\"?\n", content)
        pid_match = re.search(r"pid:\s*(.+)", content)

        title = title_match.group(1).strip() if title_match else "未知题号"
        pid = pid_match.group(1).strip() if pid_match else "未知PID"

        print(f"📜 解析文件: {file_path}")
        print(f"🔍 提取标签: {tags}")
        print(f"🔢 题号: {pid}（{title}）\n")

        return tags, pid, title, content


def consolidate_files_by_tag(target_dir, output_base_dir, target_tag):
    """
    按照指定标签（target_tag）检索并拼接 Markdown 文件，并输出题号列表。
    """
    matched_contents = []
    matched_titles = []

    diff_name = os.path.basename(target_dir)

    for file_name in os.listdir(target_dir):
        if file_name.endswith(".md"):
            file_path = os.path.join(target_dir, file_name)
            tags, pid, title, content = extract_tags_and_content(file_path)

            # ✅ **允许部分匹配**
            if any(target_tag in tag for tag in tags):
                matched_contents.append(content)
                matched_titles.append(f"{pid} - {title}")

    if matched_contents:
        output_dir = os.path.join(output_base_dir, diff_name)
        os.makedirs(output_dir, exist_ok=True)

        # 保存整合的 Markdown 文件
        output_file = os.path.join(output_dir, f"consolidated_{diff_name}_{target_tag}.md")
        with open(output_file, "w", encoding="utf-8") as output:
            for content in matched_contents:
                output.write(content + "\n\n---\n\n")
        print(f"✅ 整合完成: {output_file}")

        # 生成题号列表
        list_output_file = os.path.join(output_dir, f"consolidated_{diff_name}_{target_tag}_list.md")
        with open(list_output_file, "w", encoding="utf-8") as list_output:
            list_output.write("# 题号列表\n\n")
            for title in matched_titles:
                list_output.write(f"- {title}\n")
        print(f"✅ 题号列表已保存: {list_output_file}")
    else:
        print(f"⚠️ 未找到包含标签 '{target_tag}' 的文件。")

def process_tags(tags):
    """处理标签列表，返回格式化的字符串"""
    if not tags:
        return ""
    return ", ".join(tags)  # 只在标签之间添加", "分隔符

def find_files_without_tags(target_dir, output_base_dir):
    """查找没有标签的题目文件，并整合到一个文件中"""
    no_tag_contents = []
    no_tag_titles = []
    analysis_results = []  # 用于存储分析结果
    
    diff_name = os.path.basename(target_dir)
    
    excluded_tags = [
                'USACO', 'O2优化', 'Special Judge', '福建省历届夏令营', '语言月赛', '洛谷月赛', '洛谷原创',
                'COCI', 'NOIP 普及组', '蓝桥杯省赛', 'ICPC', '江苏', '信息与未来', 'NOIP 提高组', 'CCC', 'ROIR',
                '传智杯', '蓝桥杯国赛', '梦熊比赛', '各省省选', '山东', 'PA', 'CSP-X 小学组', '高校校赛', 'NOI 导刊',
                '安徽', '分类讨论', 'CSP-J 入门级', '提交答案', 'XCPC', 'JOI', 'Ad-hoc', 'NOISG', 'CSP-S 提高级',
                'POI', '北京', '陕西', 'Code+', '广东', 'BalticOI', 'NOI Online', 'BCSP-X', '洛谷比赛', 'IOI',
                'NOI', '天津', '交互题', '\ufeff基础算法', '南京', '福建', '小学科创活动', '湖北', '湖南', '河南',
                '集训队互测', '吉林', '逆元', '云南', 'CEOI', '澳门', '济南', '上海', '青岛', 'GESP',
                'JOI（日本）', 'BalticOI（波罗的海）', 'CEOI（中欧）', 'COCI（克罗地亚）', 
                'CCC（加拿大）', 'PA（波兰）', 'POI（波兰）', 'ROIR（俄罗斯）','NOISG（新加坡）'
    ]
    
    for file_name in os.listdir(target_dir):
        if file_name.endswith(".md"):
            file_path = os.path.join(target_dir, file_name)
            with open(file_path, "r", encoding="utf-8") as file:
                content = file.read()
                
                # 提取标签
                tag_match = re.search(r"tag:\s*\[(.*?)\]", content)
                tags = []
                is_empty_tag = False
                
                if tag_match:
                    raw_tags = tag_match.group(1)
                    if raw_tags.strip():  # 有非空标签
                        tags = [t.strip().strip("'\"") for t in re.split(r",\s*", raw_tags)]
                    else:
                        is_empty_tag = True
                
                # 提取题号和标题
                title_match = re.search(r"title:\s*\"?(.+?)\"?\n", content)
                pid_match = re.search(r"pid:\s*(.+)", content)
                
                title = title_match.group(1).strip() if title_match else "未知题号"
                pid = pid_match.group(1).strip() if pid_match else "未知PID"
                
                # 过滤标签
                filtered_tags = [tag for tag in tags 
                               if tag not in excluded_tags 
                               and not tag.isdigit() 
                               and not (tag.startswith('20') and len(tag) == 4)]
                
                # 判断是否为无标签题目
                if not filtered_tags or is_empty_tag:
                    no_tag_contents.append(content)
                    no_tag_titles.append(f"- {pid} - {title}")
                
                # 添加到分析结果
                analysis_results.append({
                    "pid": pid,
                    "original_tags": process_tags(tags),
                    "filtered_tags": process_tags(filtered_tags),
                    "is_empty": "是" if not filtered_tags else "否",
                    "is_original_empty": "是" if is_empty_tag or not tags else "否"
                })
    
    # 写入分析结果
    analysis_file = os.path.join(output_base_dir, "tag_analysis.txt")
    with open(analysis_file, "w", encoding="utf-8") as f:
        f.write("题号\t原始标签\t处理后标签\t是否为空标签\t原始是否为空\n")
        for result in analysis_results:
            f.write(f"{result['pid']}\t{result['original_tags']}\t{result['filtered_tags']}\t{result['is_empty']}\t{result['is_original_empty']}\n")
    
    # 处理无标签题目的输出
    if no_tag_contents:
        output_dir = os.path.join(output_base_dir, diff_name)
        os.makedirs(output_dir, exist_ok=True)
        
        # 保存无标签题目内容
        output_file = os.path.join(output_dir, f"consolidated_{diff_name}_no_tag.md")
        with open(output_file, "w", encoding="utf-8") as output:
            for content in no_tag_contents:
                output.write(content + "\n\n---\n\n")
        print(f"✅ 无标签题目整合完成: {output_file}")
        
        # 保存无标签题目列表
        list_output_file = os.path.join(output_dir, f"consolidated_{diff_name}_no_tag_list.md")
        with open(list_output_file, "w", encoding="utf-8") as list_output:
            list_output.write("# 无标签题目列表\n\n")
            for title in sorted(no_tag_titles):  # 排序题目列表
                list_output.write(f"{title}\n")
        print(f"✅ 无标签题目列表已保存: {list_output_file}")
        print(f"📊 共找到 {len(no_tag_titles)} 个无标签题目")
    else:
        print(f"⚠️ 未找到无标签的题目文件。")

def combine_all_md_files(output_base_dir, combined_file_name="combined.md"):
    """
    将 OUTPUT_BASE_DIR 文件夹中的所有 Markdown 文件合并为一个文件。
    """
    combined_file_path = os.path.join(output_base_dir, combined_file_name)
    os.makedirs(output_base_dir, exist_ok=True)

    with open(combined_file_path, "w", encoding="utf-8") as combined_file:
        for root, _, files in os.walk(output_base_dir):
            for file_name in files:
                if file_name.endswith(".md"):
                    file_path = os.path.join(root, file_name)
                    with open(file_path, "r", encoding="utf-8") as file:
                        combined_file.write(file.read())
                        combined_file.write("\n\n---\n\n")
    print(f"✅ 所有 Markdown 文件已合并到: {combined_file_path}")

def analyze_tag_statistics(target_dir):
    """
    分析目录中所有题目的标签统计信息
    """
    all_tags = []
    
    for file_name in os.listdir(target_dir):
        if file_name.endswith(".md"):
            file_path = os.path.join(target_dir, file_name)
            tags, _, _, _ = extract_tags_and_content(file_path)
            
            # 过滤掉需要排除的标签和纯数字标签
            excluded_tags = [
                'USACO', 'O2优化', 'Special Judge', '福建省历届夏令营', '语言月赛', '洛谷月赛', '洛谷原创',
                'COCI', 'NOIP 普及组', '蓝桥杯省赛', 'ICPC', '江苏', '信息与未来', 'NOIP 提高组', 'CCC', 'ROIR',
                '传智杯', '蓝桥杯国赛', '梦熊比赛', '各省省选', '山东', 'PA', 'CSP-X 小学组', '高校校赛', 'NOI 导刊',
                '安徽', '分类讨论', 'CSP-J 入门级', '提交答案', 'XCPC', 'JOI', 'Ad-hoc', 'NOISG', 'CSP-S 提高级',
                'POI', '北京', '陕西', 'Code+', '广东', 'BalticOI', 'NOI Online', 'BCSP-X', '洛谷比赛', 'IOI',
                'NOI', '天津', '交互题', '\ufeff基础算法', '南京', '福建', '小学科创活动', '湖北', '湖南', '河南',
                '集训队互测', '吉林', '逆元', '云南', 'CEOI', '澳门', '济南', '上海', '青岛', 'GESP',
                'JOI（日本）', 'BalticOI（波罗的海）', 'CEOI（中欧）', 'COCI（克罗地亚）', 
                'CCC（加拿大）', 'PA（波兰）', 'POI（波兰）', 'ROIR（俄罗斯）','NOISG（新加坡）'
            ]
            filtered_tags = [tag for tag in tags 
                           if tag not in excluded_tags 
                           and not tag.isdigit() 
                           and not (tag.startswith('20') and len(tag) == 4)]
            
            all_tags.extend(filtered_tags)
    
    # 统计标签频率
    tag_counter = Counter(all_tags)
    
    if tag_counter:
        total_tags = sum(tag_counter.values())
        unique_tags = len(tag_counter)
        
        print(f"\n📊 标签统计 (共{unique_tags}种不同标签，总计{total_tags}个标签)")
        print("=" * 80)
        print("排名  标签名称                 出现次数  占比")
        print("-" * 80)
        
        for rank, (tag, count) in enumerate(tag_counter.most_common(), 1):
            percentage = (count / total_tags) * 100
            print(f"{rank:2d}.   {tag:<22} {count:5d}   {percentage:5.1f}%")
    else:
        print("\n⚠️ 未找到任何标签")

if __name__ == "__main__":
    # 配置路径
    TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\luogu\sorted_problems\NOI"  # 指定文件夹路径
    OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\luogu\tag_problems"  # 保存结果的根目录
    
    # 查找无标签题目
    find_files_without_tags(TARGET_DIR, OUTPUT_BASE_DIR)
    
    # 可选：分析标签统计
    analyze_tag_statistics(TARGET_DIR)
    
    # 如果需要按特定标签整合，取消下面的注释并指定标签
    # TARGET_TAG = "动态规划"  # 指定目标标签
    # consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, TARGET_TAG)
    
    # 合并所有MD文件
    combine_all_md_files(OUTPUT_BASE_DIR)

 

