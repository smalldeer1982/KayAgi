import os
import re

CPP_DIR = r"D:\KayCraft\C++\洛谷"
MD_DIR = r"D:\ChatgptKay\KayAgi\Cpp\Luogu\problems"
OUTPUT_DIR = r"D:\ChatgptKay\KayAgi\Cpp\Luogu\kaycraft"
os.makedirs(OUTPUT_DIR, exist_ok=True)

output_md = os.path.join(OUTPUT_DIR, "submit_format.md")
unmatched_txt = os.path.join(OUTPUT_DIR, "unmatched.txt")

def clean_title(title):
    # 去除前缀 [xxx] 或 【xxx】及其后面的空格
    title = re.sub(r"^[\[\【][^\]\】]*[\]\】]\s*", "", title)
    # 去除空格和下划线
    return title.replace(" ", "").replace("_", "").lower()

def get_md_info(md_path):
    """提取md文件的title和pid"""
    with open(md_path, "r", encoding="utf-8") as f:
        lines = f.readlines()
    title = ""
    pid = ""
    for line in lines:
        if line.strip().startswith("#"):
            title = line.strip().lstrip("#").strip()
            break
    pid_match = re.search(r'[PB]\d{4,6}', os.path.basename(md_path))
    if not pid_match:
        for line in lines[:10]:
            pid_match = re.search(r'[PB]\d{4,6}', line)
            if pid_match:
                break
    pid = pid_match.group(0) if pid_match else ""
    return title, pid, "".join(lines)

# 预处理所有md文件，建立多种key到md内容的映射
md_map = {}
md_title_map = {}  # 完整title到内容
for md_file in os.listdir(MD_DIR):
    if md_file.endswith(".md"):
        md_path = os.path.join(MD_DIR, md_file)
        title, pid, content = get_md_info(md_path)
        if title:
            md_map[clean_title(title)] = content
            md_title_map[title] = content
        if pid:
            md_map[pid.lower()] = content

matched = []
unmatched = []

def read_file_auto_encoding(file_path):
    for enc in ("utf-8", "gbk", "ansi"):
        try:
            with open(file_path, "r", encoding=enc) as f:
                return f.read()
        except UnicodeDecodeError:
            continue
    with open(file_path, "rb") as f:
        return f.read().decode("utf-8", errors="ignore")

for root, _, files in os.walk(CPP_DIR):
    for file in files:
        if file.endswith(".cpp"):
            cpp_path = os.path.join(root, file)
            cpp_name = os.path.splitext(file)[0]
            cpp_key = clean_title(cpp_name)
            cpp_content = read_file_auto_encoding(cpp_path)
            md_content = md_map.get(cpp_key)
            # 1. 先用key匹配
            if not md_content:
                # 2. 再用完整title精确匹配
                md_content = md_title_map.get(cpp_name)
            if md_content:
                # 获取一级分类
                category = os.path.relpath(os.path.dirname(cpp_path), CPP_DIR).split(os.sep)[0]
                # 提取题号
                pid_match = re.search(r'[PB]\d{4,6}', md_content)
                pid = pid_match.group(0) if pid_match else ""
                # 插入分类信息到题号后一行
                if pid:
                    md_content_lines = md_content.splitlines()
                    for idx, line in enumerate(md_content_lines):
                        if pid in line:
                            md_content_lines.insert(idx + 1, f"**分类：{category}**")
                            break
                    md_content_with_category = "\n".join(md_content_lines)
                else:
                    md_content_with_category = f"**分类：{category}**\n" + md_content
                matched.append(f"{md_content_with_category}\n\n### 代码\n```cpp\n{cpp_content}\n```\n\n---\n")
            else:
                unmatched.append(f"{cpp_path}")

with open(output_md, "w", encoding="utf-8") as f:
    f.write("\n".join(matched))

with open(unmatched_txt, "w", encoding="utf-8") as f:
    f.write("\n".join(unmatched))

print(f"匹配成功 {len(matched)} 个，未匹配 {len(unmatched)} 个，结果已保存到 {OUTPUT_DIR}")