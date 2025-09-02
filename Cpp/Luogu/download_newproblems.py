import requests
import gzip
import shutil
import json
import os
from tqdm import tqdm
from datetime import datetime
import glob

def get_existing_problems():
    """获取已有的题目列表"""
    existing_problems = set()
    problems_dir = "cpp/luogu/problems"
    if os.path.exists(problems_dir):
        for file in glob.glob(f"{problems_dir}/*.md"):
            pid = os.path.basename(file).replace('.md', '')
            existing_problems.add(pid)
    return existing_problems

def create_temp_dir():
    """创建临时文件夹"""
    temp_dir = "temp_luogu_download"
    if os.path.exists(temp_dir):
        shutil.rmtree(temp_dir)
    os.makedirs(temp_dir)
    return temp_dir

def cleanup_temp_files(temp_dir):
    """清理临时文件"""
    if os.path.exists(temp_dir):
        shutil.rmtree(temp_dir)
    if os.path.exists("latest.ndjson.gz"):
        os.remove("latest.ndjson.gz")
    if os.path.exists("latest.ndjson"):
        os.remove("latest.ndjson")

# 创建临时文件夹
temp_dir = create_temp_dir()

try:
    # 下载文件
    url = "https://cdn.luogu.com.cn/problemset-open/latest.ndjson.gz"
    response = requests.get(url, stream=True)

    # 保存压缩文件到临时文件夹
    gz_path = os.path.join(temp_dir, "latest.ndjson.gz")
    with open(gz_path, "wb") as f:
        total_size = int(response.headers.get('content-length', 0))
        with tqdm(total=total_size, unit='B', unit_scale=True, desc='下载中') as bar:
            for data in response.iter_content(chunk_size=1024):
                f.write(data)
                bar.update(len(data))

    # 解压缩文件到临时文件夹
    ndjson_path = os.path.join(temp_dir, "latest.ndjson")
    with gzip.open(gz_path, "rb") as f_in:
        with open(ndjson_path, "wb") as f_out:
            shutil.copyfileobj(f_in, f_out)

    # 难度映射表
    difficulty_mapping = {
        1: "入门",
        2: "普及-",
        3: "普及/提高-",
        4: "普及+/提高",
        5: "提高+/省选-",
        6: "省选/NOI-",
        7: "NOI/NOI+/CTSC"
    }

    # 获取当前日期作为文件夹名
    current_date = datetime.now().strftime("%Y%m%d")
    new_problems_dir = f"cpp/luogu/problems_{current_date}"
    os.makedirs(new_problems_dir, exist_ok=True)

    # 获取已有题目列表
    existing_problems = get_existing_problems()
    new_problems_count = 0

    # 读取 NDJSON 文件
    with open(ndjson_path, "r", encoding="utf-8") as file:
        lines = file.readlines()

    # 处理每一行并生成 Markdown 文件
    for line in tqdm(lines, desc="生成中", unit="题"):
        problem = json.loads(line)
        pid = problem["pid"]
        
        # 检查是否为新题目
        if pid in existing_problems:
            continue
            
        new_problems_count += 1
        title = problem["title"]
        difficulty = difficulty_mapping.get(problem["difficulty"], "暂无评定")
        
        # 添加样例内容
        samples_content = ""
        for index, sample in enumerate(problem.get("samples", [])):
            samples_content += f"### 样例输入 #{index + 1}\n```\n{sample[0]}\n```\n"
            samples_content += f"### 样例输出 #{index + 1}\n```\n{sample[1]}\n```\n"

        # 创建 Markdown 文件的内容
        content = f"""---
title: "{title}"
layout: "post"
diff: {difficulty}
pid: {pid}
tag: {problem['tags']}
---
# {title}
"""

        # 检查并添加每个部分
        if problem.get("background"):
            content += f"## 题目背景\n\n{problem['background']}\n"

        if problem.get("description"):
            content += f"## 题目描述\n\n{problem['description']}\n"

        if problem.get("inputFormat"):
            content += f"## 输入格式\n\n{problem['inputFormat']}\n"

        if problem.get("outputFormat"):
            content += f"## 输出格式\n\n{problem['outputFormat']}\n"

        if samples_content:
            content += f"## 样例\n\n{samples_content}"

        if problem.get("hint"):
            content += f"## 提示\n\n{problem['hint']}\n"

        if problem.get("translation"):
            content += f"## 题目翻译\n\n{problem['translation']}\n"

        # 写入 Markdown 文件到新文件夹
        filename = os.path.join(new_problems_dir, f"{pid}.md")
        with open(filename, "w", encoding="utf-8") as md_file:
            md_file.write(content)

    print(f"处理完成！新增题目数量: {new_problems_count}")
    if new_problems_count == 0:
        print("没有新题目，删除临时文件夹")
        shutil.rmtree(new_problems_dir)

finally:
    # 清理临时文件和文件夹
    cleanup_temp_files(temp_dir)
