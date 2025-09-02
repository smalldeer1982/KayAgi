#对于problems下的文件进行难度分类
import os
import shutil
import re

# 定义难度映射表，目录名称使用中文
DIFF_MAP = {
    "入门": "入门",
    "普及-": "普及-",
    "普及/提高-": "普及",
    "普及+/提高": "普及+",
    "提高+/省选-": "提高+",
    "省选/NOI-": "省选",
    "NOI/NOI+/CTSC": "NOI",
}

# 输入和输出目录
PROBLEMS_DIR = "problems"  # 原始文件所在目录
OUTPUT_DIR = "sorted_problems"  # 分类后的文件存放目录

# 创建分类目录
os.makedirs(OUTPUT_DIR, exist_ok=True)
for folder in DIFF_MAP.values():
    os.makedirs(os.path.join(OUTPUT_DIR, folder), exist_ok=True)
os.makedirs(os.path.join(OUTPUT_DIR, "未知难度"), exist_ok=True)  # 创建未分类目录

def extract_diff(file_path):
    """从文件中提取 diff 字段的值"""
    with open(file_path, "r", encoding="utf-8") as file:
        content = file.read()
        # 正则匹配 diff 字段
        match = re.search(r"diff:\s*(.+)", content)
        if match:
            return match.group(1).strip()
    return None

def classify_files():
    """分类文件并复制到对应目录"""
    for file_name in os.listdir(PROBLEMS_DIR):
        if file_name.endswith(".md"):  # 仅处理 .md 文件
            file_path = os.path.join(PROBLEMS_DIR, file_name)
            diff_value = extract_diff(file_path)

            # 找到分类目录
            target_folder = DIFF_MAP.get(diff_value, "未知难度")
            target_path = os.path.join(OUTPUT_DIR, target_folder, file_name)

            # 复制文件到目标目录
            shutil.copy(file_path, target_path)
            print(f"文件 {file_name} 已分类到 {target_folder} 文件夹")

if __name__ == "__main__":
    classify_files()
