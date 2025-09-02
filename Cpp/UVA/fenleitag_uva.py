import os
import re

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

if __name__ == "__main__":

    # 配置路径和目标标签
    TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\sorted_problems_UVA\普及-"  # 指定文件夹路径
    OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\tag_problems_UVA"  # 保存结果的根目录
    TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树"  # 输入需要检索的标签，用逗号分隔
    
    # 遍历每个标签
    for tag in TARGET_TAGS.split(','):
        tag = tag.strip()  # 去除可能的空格
        print(f"\n处理标签: {tag}")
        consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
        combine_all_md_files(OUTPUT_BASE_DIR)

            # 配置路径和目标标签
    TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\sorted_problems_UVA\普及"  # 指定文件夹路径
    OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\tag_problems_UVA"  # 保存结果的根目录
    TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树"  # 输入需要检索的标签，用逗号分隔
    
    # 遍历每个标签
    for tag in TARGET_TAGS.split(','):
        tag = tag.strip()  # 去除可能的空格
        print(f"\n处理标签: {tag}")
        consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
        combine_all_md_files(OUTPUT_BASE_DIR)

            # 配置路径和目标标签
    TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\sorted_problems_UVA\普及+"  # 指定文件夹路径
    OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\tag_problems_UVA"  # 保存结果的根目录
    TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树"  # 输入需要检索的标签，用逗号分隔
    
    # 遍历每个标签
    for tag in TARGET_TAGS.split(','):
        tag = tag.strip()  # 去除可能的空格
        print(f"\n处理标签: {tag}")
        consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
        combine_all_md_files(OUTPUT_BASE_DIR)

            # 配置路径和目标标签
    TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\sorted_problems_UVA\提高+"  # 指定文件夹路径
    OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\tag_problems_UVA"  # 保存结果的根目录
    TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树"  # 输入需要检索的标签，用逗号分隔
    
    # 遍历每个标签
    for tag in TARGET_TAGS.split(','):
        tag = tag.strip()  # 去除可能的空格
        print(f"\n处理标签: {tag}")
        consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
        combine_all_md_files(OUTPUT_BASE_DIR)

    # 配置路径和目标标签
    TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\sorted_problems_UVA\省选"  # 指定文件夹路径
    OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\UVA\tag_problems_UVA"  # 保存结果的根目录
    TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树"  # 输入需要检索的标签，用逗号分隔
    
    # 遍历每个标签
    for tag in TARGET_TAGS.split(','):
        tag = tag.strip()  # 去除可能的空格
        print(f"\n处理标签: {tag}")
        consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
        combine_all_md_files(OUTPUT_BASE_DIR)







