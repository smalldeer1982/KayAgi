import os
import re
from datetime import datetime

# 配置路径
SUBMITCODE_DIR = r"D:\ChatgptKay\Kayagi\cpp\luogu\submitcode"
PROBLEMS_DIR = r"D:\ChatgptKay\Kayagi\cpp\luogu\problems"
OUTPUT_DIR = r"D:\ChatgptKay\Kayagi\cpp\luogu\submitcode_all"
SUBMIT_FORMAT_MD = r"D:\ChatgptKay\KayAgi\Cpp\Luogu\kaycraft\submit_format.md"
TRAINING_PROBLEMS_MD = r"D:\ChatgptKay\KayAgi\Cpp\Luogu\training_problems.md"

# 确保输出目录存在
os.makedirs(OUTPUT_DIR, exist_ok=True)

def clean_code_content(file_path):
    """读取代码文件内容，并去除空行"""
    with open(file_path, "r", encoding="utf-8") as file:
        lines = file.readlines()
    return "\n".join(line.strip() for line in lines if line.strip())

def read_problem_content(problem_file_path):
    """读取题目文件内容"""
    with open(problem_file_path, "r", encoding="utf-8") as file:
        return file.read()

def get_problem_file(problem_id):
    """根据题号查找对应的题目文件"""
    for file_name in os.listdir(PROBLEMS_DIR):
        if file_name.startswith(problem_id) and file_name.endswith(".md"):
            return os.path.join(PROBLEMS_DIR, file_name)
    return None

def extract_categories_from_training_problems(file_path):
    """从training_problems.md中提取题号和分类信息"""
    pid2category = {}
    
    if not os.path.exists(file_path):
        print(f"警告：{file_path} 不存在，跳过从训练题单中提取分类")
        return pid2category
    
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
        
        # 跳过标题行和分隔线
        for line in lines[3:]:
            parts = line.strip().split("|")
            if len(parts) >= 4:
                pid = parts[0].strip()
                title = parts[1].strip()
                main_cat = parts[2].strip()
                sub_cat = parts[3].strip()
                if pid and main_cat and sub_cat:
                    # 合并大类和小类
                    pid2category[pid] = f"{main_cat}-{sub_cat}"
        
        print(f"从训练题单中提取了 {len(pid2category)} 个题目的分类信息")
    except Exception as e:
        print(f"从训练题单提取分类时出错：{e}")
    
    return pid2category

def extract_pid_category_from_submit_format(md_path):
    """从submit_format.md中提取题号和分类信息"""
    pid2category = {}
    
    if not os.path.exists(md_path):
        print(f"警告：{md_path} 不存在，跳过从提交格式中提取分类")
        return pid2category
    
    try:
        with open(md_path, "r", encoding="utf-8") as f:
            content = f.read()
        # 按分隔符分割
        blocks = re.split(r'\n-{3,}\n', content)
        for block in blocks:
            # 提取题号
            pid_match = re.search(r'[PB]\d{4,6}', block)
            if pid_match:
                pid = pid_match.group(0)
                # 提取分类
                cat_match = re.search(r'\*\*分类：([^\*]+)\*\*', block)
                if cat_match:
                    pid2category[pid] = cat_match.group(1).strip()
        
        print(f"从提交格式中提取了 {len(pid2category)} 个题目的分类信息")
    except Exception as e:
        print(f"从提交格式提取分类时出错：{e}")
    
    return pid2category

def consolidate_submitcode():
    """主逻辑：拼接内容并保存，只保留每题最后一次提交的代码"""
    code_files = {}
    unmatched_files = []
    no_category = []
    total_files = 0

    # 1. 先遍历所有代码文件，找到每个题号最后一次提交的文件
    for file_name in os.listdir(SUBMITCODE_DIR):
        if "-" in file_name:
            problem_id = file_name.split("-")[0]
            submit_time = 0
            try:
                submit_time = int(file_name.split("-")[1].split(".")[0])
            except Exception:
                pass
            # 如果题号没出现过，或当前提交时间更晚，则更新
            if (problem_id not in code_files) or (submit_time > code_files[problem_id][1]):
                code_files[problem_id] = (file_name, submit_time)

    # 2. 预处理分类信息，优先从training_problems.md提取
    pid2category_training = extract_categories_from_training_problems(TRAINING_PROBLEMS_MD)
    pid2category_submit = extract_pid_category_from_submit_format(SUBMIT_FORMAT_MD)
    
    # 合并分类信息，优先使用training_problems.md中的
    pid2category = {**pid2category_submit, **pid2category_training}

    consolidated_content = []
    for problem_id, (file_name, submit_time) in code_files.items():
        code_file_path = os.path.join(SUBMITCODE_DIR, file_name)
        problem_file_path = get_problem_file(problem_id)
        if problem_file_path:
            problem_content = read_problem_content(problem_file_path)
            code_content = clean_code_content(code_file_path)
            # 提取标题
            title_match = re.search(r'^#\s*([^\n]+)', problem_content, re.MULTILINE)
            title = title_match.group(1).strip() if title_match else ""
            # 时间戳转为可读时间
            try:
                submit_time_str = datetime.fromtimestamp(int(submit_time)).strftime("%Y-%m-%d %H:%M:%S")
            except Exception:
                submit_time_str = str(submit_time)
            # 分类信息
            category_line = ""
            if problem_id in pid2category:
                category_line = f"**分类：{pid2category[problem_id]}**\n\n"
            else:
                no_category.append((problem_id, title))
            consolidated_content.append(
                f"## 题目: {problem_id}\n\n"
                f"{category_line}"
                f"**提交时间：{submit_time_str}**\n\n"
                f"{problem_content}\n\n### 代码\n\n```cpp\n{code_content}\n```"
            )
            total_files += 1
        else:
            unmatched_files.append(file_name)

    # 保存拼接内容到文件
    if consolidated_content:
        today = datetime.now().strftime("%Y%m%d")
        output_file = os.path.join(OUTPUT_DIR, f"submitcode_all_{total_files}_{today}.md")
        with open(output_file, "w", encoding="utf-8") as output:
            output.write("\n\n---\n\n".join(consolidated_content))
        print(f"拼接完成，共处理 {total_files} 道题目，结果已保存到: {output_file}")
    else:
        print("没有找到匹配的题目和代码进行拼接。")

    # 保存未匹配的代码文件记录
    if unmatched_files:
        unmatched_file_path = os.path.join(OUTPUT_DIR, f"unmatched_files_{today}.txt")
        with open(unmatched_file_path, "w", encoding="utf-8") as unmatched_file:
            unmatched_file.write("\n".join(unmatched_files))
        print(f"未找到题目的代码文件已记录到: {unmatched_file_path}")

    # 保存没有分类的题号和标题
    if no_category:
        no_category_path = os.path.join(OUTPUT_DIR, f"no_category_{today}.txt")
        with open(no_category_path, "w", encoding="utf-8") as f:
            for pid, title in no_category:
                f.write(f"{pid}\t{title}\n")
        print(f"未提取到分类的题号已记录到: {no_category_path}")
        print(f"未分类题目数量: {len(no_category)}")

if __name__ == "__main__":
    consolidate_submitcode()
