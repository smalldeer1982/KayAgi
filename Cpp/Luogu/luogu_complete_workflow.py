#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
洛谷题目完整处理流程
整合了下载新题目、分类、标签处理、题解获取的完整流程
"""

import os
import sys
import shutil
import json
import re
import time
import glob
import requests
import gzip
import urllib.request
import bs4 as bs
from datetime import datetime
from tqdm import tqdm

class LuoguWorkflow:
    def __init__(self):
        """初始化工作流程"""
        self.base_dir = "cpp/luogu"
        self.problems_dir = os.path.join(self.base_dir, "problems")
        self.sorted_problems_dir = os.path.join(self.base_dir, "sorted_problems")
        self.tag_problems_dir = os.path.join(self.base_dir, "tag_problems")
        self.solution_dir = os.path.join(self.base_dir, "solution")
        
        # 默认标签列表
        self.default_tags = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,树形 DP,状压 DP,区间 DP,AC 自动机,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,期望,网络流,可持久化线段树,高斯消元,莫队,NOIP 提高组,NOIP 普及组,CSP-S 提高级,CSP-J 入门级,博弈论,树链剖分,排列组合,动态规划优化,双指针 two-pointer,基环树,NOI,单调栈,根号分治,Manacher 算法,凸包,扫描线,随机化,树的直径,莫比乌斯反演,矩阵运算,欧拉函数,中国剩余定理 CRT,双连通分量,斐波那契数列,线性递推,费用流,Tarjan,欧几里德,欧拉回路,动态树 LCT,快速傅里叶变换 FFT,APIO,最小割,斜率优化,后缀数组 SA,快速数论变换 NTT,可持久化,虚树,洛谷原创,各省省选,蓝桥杯国赛,ICPC,蓝桥杯省赛,梦熊比赛,洛谷比赛,NOI 导刊,语言月赛,BCSP-X,扩展欧几里德算法,三分,蓝桥杯青少年组,整除分块,链表,线性 DP,数组,图遍历,不定方程,函数与递归,结构体,鸽笼原理,Catalan 数,IOI,THUPC,集训队互测,cdq 分治,SG 函数,折半搜索 meet in the middle,笛卡尔树,离线处理,线性基,点分治,可并堆,原根,生成函数,快速沃尔什变换 FWT,模拟退火,线性代数,Lucas 定理,向量,K-D Tree,树上启发式合并,整体二分,快速莫比乌斯变换 FMT,Kruskal 重构树,USACO"
        
        # 难度映射表
        self.difficulty_mapping = {
            1: "入门",
            2: "普及-",
            3: "普及/提高-",
            4: "普及+/提高",
            5: "提高+/省选-",
            6: "省选/NOI-",
            7: "NOI/NOI+/CTSC"
        }
        
        # 难度分类映射表
        self.diff_map = {
            "入门": "入门",
            "普及-": "普及-",
            "普及/提高-": "普及",
            "普及+/提高": "普及+",
            "提高+/省选-": "提高+",
            "省选/NOI-": "省选",
            "NOI/NOI+/CTSC": "NOI",
        }

    def step1_download_new_problems(self):
        """步骤1: 下载新题目"""
        print("=== 步骤1: 下载新题目 ===")
        
        # 获取已有的题目列表
        existing_problems = self._get_existing_problems()
        
        # 创建临时文件夹
        temp_dir = self._create_temp_dir()
        
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
            
            # 获取当前日期作为文件夹名
            current_date = datetime.now().strftime("%Y%m%d")
            new_problems_dir = f"{self.base_dir}/problems_{current_date}"
            os.makedirs(new_problems_dir, exist_ok=True)
            
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
                difficulty = self.difficulty_mapping.get(problem["difficulty"], "暂无评定")
                
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
            
            if new_problems_count > 0:
                # 复制新文件到原有problems下
                print("复制新文件到problems目录...")
                os.makedirs(self.problems_dir, exist_ok=True)
                for filename in os.listdir(new_problems_dir):
                    if filename.endswith('.md'):
                        src = os.path.join(new_problems_dir, filename)
                        dst = os.path.join(self.problems_dir, filename)
                        shutil.copy2(src, dst)
                
                print(f"成功复制 {new_problems_count} 个新题目到 {self.problems_dir}")
                
                # 删除临时日期文件夹
                print(f"删除临时文件夹: {new_problems_dir}")
                shutil.rmtree(new_problems_dir)
                
                return new_problems_dir, new_problems_count  # 返回日期文件夹路径用于后续步骤
            else:
                print("没有新题目，删除临时文件夹")
                shutil.rmtree(new_problems_dir)
                return None, 0
                
        finally:
            # 清理临时文件和文件夹
            self._cleanup_temp_files(temp_dir)

    def step2_classify_by_difficulty(self, problems_source_dir=None):
        """步骤2: 按难度分类题目"""
        print("=== 步骤2: 按难度分类题目 ===")
        
        # 如果没有指定源目录，使用默认的problems目录
        if problems_source_dir is None:
            problems_source_dir = self.problems_dir
        
        # 创建分类目录
        os.makedirs(self.sorted_problems_dir, exist_ok=True)
        for folder in self.diff_map.values():
            os.makedirs(os.path.join(self.sorted_problems_dir, folder), exist_ok=True)
        os.makedirs(os.path.join(self.sorted_problems_dir, "未知难度"), exist_ok=True)
        
        classified_count = 0
        for file_name in tqdm(os.listdir(problems_source_dir), desc="分类中"):
            if file_name.endswith(".md"):
                file_path = os.path.join(problems_source_dir, file_name)
                diff_value = self._extract_diff(file_path)
                
                # 找到分类目录
                target_folder = self.diff_map.get(diff_value, "未知难度")
                target_path = os.path.join(self.sorted_problems_dir, target_folder, file_name)
                
                # 复制文件到目标目录
                shutil.copy(file_path, target_path)
                classified_count += 1
        
        print(f"分类完成！共分类 {classified_count} 个文件到 {self.sorted_problems_dir}")

    def step3_process_tags(self, difficulties=None):
        """步骤3: 处理标签分类"""
        print("=== 步骤3: 处理标签分类 ===")
        
        if difficulties is None:
            difficulties = self._get_existing_difficulties()
        
        os.makedirs(self.tag_problems_dir, exist_ok=True)
        
        for difficulty in difficulties:
            target_dir = os.path.join(self.sorted_problems_dir, difficulty)
            if not os.path.exists(target_dir):
                print(f"警告: 目录不存在: {target_dir}")
                continue
            
            print(f"\n处理难度: {difficulty}")
            
            # 遍历每个标签
            for tag in tqdm(self.default_tags.split(','), desc=f"处理 {difficulty} 标签"):
                tag = tag.strip()
                self._consolidate_files_by_tag(target_dir, self.tag_problems_dir, tag)

    def step4_extract_solutions(self, difficulties=None):
        """步骤4: 提取题解"""
        print("=== 步骤4: 提取题解 ===")
        
        if difficulties is None:
            difficulties = self._get_existing_difficulties()
        
        # 获取当前脚本所在目录的路径
        current_dir = os.path.dirname(os.path.abspath(__file__))
        # 获取项目根目录路径（往上三级）
        root_dir = os.path.dirname(os.path.dirname(os.path.dirname(current_dir)))
        
        for difficulty in difficulties:
            print(f"\n处理 {difficulty} 级别的题解...")
            
            # 处理每个标签
            for tag in tqdm(self.default_tags.split(','), desc=f"提取 {difficulty} 题解"):
                tag = tag.strip()
                # 构建完整的文件路径
                file_path = os.path.join(root_dir, "KayAgi/cpp/luogu/tag_problems", difficulty, f"consolidated_{difficulty}_{tag}_list.md")
                
                if os.path.exists(file_path):
                    print(f"处理文件: {file_path}")
                    self._process_problems_for_solutions(file_path, root_dir)
                else:
                    print(f"文件不存在，跳过: {file_path}")

    def run_complete_workflow(self, skip_download=False, skip_classify=False, skip_tags=False, skip_solutions=False):
        """运行完整工作流程"""
        print("=== 洛谷题目完整处理流程开始 ===")
        
        start_time = time.time()
        
        # 步骤1: 下载新题目
        new_problems_dir = None
        new_count = 0
        if not skip_download:
            new_problems_dir, new_count = self.step1_download_new_problems()
        
        # 步骤2: 按难度分类
        if not skip_classify and (new_count > 0 or not skip_download):
            self.step2_classify_by_difficulty()
        
        # 步骤3: 处理标签
        if not skip_tags:
            self.step3_process_tags()
        
        # 步骤4: 提取题解
        if not skip_solutions:
            self.step4_extract_solutions()
        
        end_time = time.time()
        elapsed_time = end_time - start_time
        
        print(f"\n=== 完整流程结束 ===")
        print(f"总耗时: {elapsed_time:.2f} 秒")
        if new_count > 0:
            print(f"新增题目: {new_count} 个")

    # 辅助方法
    def _get_existing_difficulties(self):
        """动态获取已存在的难度分类"""
        difficulties = []
        if os.path.exists(self.sorted_problems_dir):
            for item in os.listdir(self.sorted_problems_dir):
                item_path = os.path.join(self.sorted_problems_dir, item)
                if os.path.isdir(item_path) and item != "未知难度":
                    difficulties.append(item)
        
        # 如果没有找到任何难度分类，使用默认列表
        if not difficulties:
            difficulties = ["入门", "普及-", "普及", "普及+", "提高+", "省选", "NOI"]
            print(f"警告: 未找到已存在的难度分类，使用默认列表: {difficulties}")
        else:
            print(f"找到已存在的难度分类: {difficulties}")
        
        return difficulties

    def _get_existing_problems(self):
        """获取已有的题目列表"""
        existing_problems = set()
        if os.path.exists(self.problems_dir):
            for file in glob.glob(f"{self.problems_dir}/*.md"):
                pid = os.path.basename(file).replace('.md', '')
                existing_problems.add(pid)
        return existing_problems

    def _create_temp_dir(self):
        """创建临时文件夹"""
        temp_dir = "temp_luogu_download"
        if os.path.exists(temp_dir):
            shutil.rmtree(temp_dir)
        os.makedirs(temp_dir)
        return temp_dir

    def _cleanup_temp_files(self, temp_dir):
        """清理临时文件"""
        if os.path.exists(temp_dir):
            shutil.rmtree(temp_dir)
        if os.path.exists("latest.ndjson.gz"):
            os.remove("latest.ndjson.gz")
        if os.path.exists("latest.ndjson"):
            os.remove("latest.ndjson")

    def _extract_diff(self, file_path):
        """从文件中提取 diff 字段的值"""
        with open(file_path, "r", encoding="utf-8") as file:
            content = file.read()
            # 正则匹配 diff 字段
            match = re.search(r"diff:\s*(.+)", content)
            if match:
                return match.group(1).strip()
        return None

    def _extract_tags_and_content(self, file_path):
        """从 Markdown 文件中提取标签(tag)和正文内容，并解析题号"""
        with open(file_path, "r", encoding="utf-8") as file:
            content = file.read()

            # 提取标签，支持 ['动态规划 DP'] 格式
            tag_match = re.search(r"tag:\s*\[(.*?)\]", content)
            if tag_match:
                raw_tags = tag_match.group(1)
                # 拆分时考虑含空格的 tag
                tags = [t.strip().strip("'\"") for t in re.split(r",\s*", raw_tags)]
            else:
                tags = []

            # 提取题号
            title_match = re.search(r"title:\s*\"?(.+?)\"?\n", content)
            pid_match = re.search(r"pid:\s*(.+)", content)

            title = title_match.group(1).strip() if title_match else "未知题号"
            pid = pid_match.group(1).strip() if pid_match else "未知PID"

            return tags, pid, title, content

    def _consolidate_files_by_tag(self, target_dir, output_base_dir, target_tag):
        """按照指定标签（target_tag）检索并拼接 Markdown 文件，并输出题号列表"""
        matched_contents = []
        matched_titles = []

        diff_name = os.path.basename(target_dir)

        for file_name in os.listdir(target_dir):
            if file_name.endswith(".md"):
                file_path = os.path.join(target_dir, file_name)
                tags, pid, title, content = self._extract_tags_and_content(file_path)

                # 允许部分匹配
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

            # 生成题号列表
            list_output_file = os.path.join(output_dir, f"consolidated_{diff_name}_{target_tag}_list.md")
            with open(list_output_file, "w", encoding="utf-8") as list_output:
                list_output.write("# 题号列表\n\n")
                for title in matched_titles:
                    list_output.write(f"- {title}\n")

    # 题解处理相关方法（从 luogu_parser.py 移植）
    def _load_config(self):
        """加载配置文件"""
        config_path = os.path.join(os.path.dirname(__file__), 'luogu_config.json')
        try:
            with open(config_path, 'r', encoding='utf-8') as f:
                return json.load(f)
        except Exception as e:
            print(f"加载配置文件失败: {str(e)}")
            return None

    def _get_headers(self):
        """获取请求头"""
        config = self._load_config()
        if not config:
            raise Exception("无法加载配置文件")
            
        return {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
            'Accept': 'application/json, text/javascript, */*; q=0.01',
            'Accept-Language': 'zh-CN,zh;q=0.9',
            'Accept-Encoding': 'gzip, deflate, br',
            'X-Requested-With': 'XMLHttpRequest',
            'Host': 'www.luogu.com.cn',
            'Connection': 'keep-alive',
            'Referer': 'https://www.luogu.com.cn/problem/',
            'sec-ch-ua': '"Chromium";v="116", "Not)A;Brand";v="24", "Google Chrome";v="116"',
            'sec-ch-ua-mobile': '?0',
            'sec-ch-ua-platform': '"Windows"',
            'Sec-Fetch-Dest': 'empty',
            'Sec-Fetch-Mode': 'cors',
            'Sec-Fetch-Site': 'same-origin',
            'Cookie': config['cookie']
        }

    def _extract_problem_ids(self, file_path: str) -> list:
        """从文件中提取题号"""
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                lines = f.readlines()
            
            # 使用正则表达式匹配题号，只匹配行开头的题号格式（- P/B + 数字）
            pattern = r'^\s*-\s*([BP]\d+)'
            problem_ids = []
            
            for line in lines:
                line = line.strip()
                if line:  # 跳过空行
                    match = re.search(pattern, line)
                    if match:
                        pid = match.group(1)  # 获取第一个捕获组（题号部分）
                        problem_ids.append(pid)
            
            return problem_ids
        except Exception as e:
            print(f"读取文件错误: {str(e)}")
            return []

    def _sanitize_filename(self, filename: str) -> str:
        """清理文件名中的非法字符"""
        illegal_chars = ['/', '\\', ':', '*', '?', '"', '<', '>', '|']
        for char in illegal_chars:
            filename = filename.replace(char, '-')
        return filename

    def _json_parser(self, html: str):
        """解析HTML中的JSON数据"""
        try:
            soup = bs.BeautifulSoup(html, "html.parser")
            script = soup.find('script', id='lentille-context')
            if not script:
                return None
                
            try:
                content = script.string.strip()
                js = json.loads(content)
                return js
            except json.JSONDecodeError as e:
                print(f"JSON解析失败: {str(e)}")
                return None
        except Exception as e:
            print(f"解析过程出现错误: {str(e)}")
            return None

    def _extract_pid_from_filename(self, filename: str) -> str:
        """从文件名中提取题号
        例如：从 'P2024-[NOI2001] 食物链.md' 提取出 'P2024'
        """
        # 使用正则表达式匹配P/B开头后面跟着数字的部分
        match = re.match(r'(P|B)\d+', filename)
        return match.group(0) if match else None

    def _get_existing_problems_in_dir(self, directory: str) -> set:
        """获取目录下所有已存在的题目编号"""
        existing_pids = set()
        try:
            for filename in os.listdir('.'):
                if filename.endswith('.md'):
                    pid = self._extract_pid_from_filename(filename)
                    if pid:
                        existing_pids.add(pid)
        except Exception as e:
            print(f"读取目录出错: {str(e)}")
        return existing_pids

    def _check_problem_exists(self, output_dir: str, pid: str) -> bool:
        """检查题目是否已经解析过"""
        existing_pids = self._get_existing_problems_in_dir(output_dir)
        return pid in existing_pids

    def _process_problems_for_solutions(self, file_path: str, root_dir: str):
        """处理文件中的所有题目并提取题解"""
        original_dir = os.getcwd()
        
        try:
            # 从文件名中提取难度和分类
            filename = os.path.basename(file_path)
            parts = filename.replace('consolidated_', '').replace('_list.md', '').split('_')
            difficulty = parts[0]
            category = parts[1]
            
            # 构建输出目录
            output_dir = os.path.join(root_dir, "KayAgi/cpp/luogu/solution", difficulty, category)
            os.makedirs(output_dir, exist_ok=True)
            
            # 切换到输出目录
            os.chdir(output_dir)
            
            # 获取所有题号
            problem_ids = self._extract_problem_ids(file_path)
            
            # 批次处理变量
            batch_count = 0
            batch_start_time = time.time()
            skipped_count = 0
            
            # 处理每个题目
            for i, pid in enumerate(problem_ids, 1):
                print(f"\n检查第 {i}/{len(problem_ids)} 个题目: {pid}")
                
                # 检查题目是否已存在
                if self._check_problem_exists(output_dir, pid):
                    skipped_count += 1
                    continue
                    
                print(f"开始处理题目: {pid}")
                self._pid_parser(pid)
                batch_count += 1
                
                # 检查是否需要休息
                current_time = time.time()
                time_elapsed = current_time - batch_start_time
                
                if batch_count >= 5 or time_elapsed >= 20:
                    print(f"\n=== 已处理 {batch_count} 题，耗时 {time_elapsed:.2f} 秒 ===")
                    print("休息10秒...")
                    time.sleep(10)
                    batch_count = 0
                    batch_start_time = time.time()
            
            print(f"\n处理完成！")
            print(f"总题目数: {len(problem_ids)}")
            print(f"跳过数量: {skipped_count}")
            print(f"新处理数: {len(problem_ids) - skipped_count}")
                
        except Exception as e:
            print(f"处理过程出错: {str(e)}")
            import traceback
            print(traceback.format_exc())
        finally:
            # 恢复原始目录
            os.chdir(original_dir)

    def _pid_parser(self, pid: str):
        """解析单个题目并获取题解"""
        headers = self._get_headers()
        problem_url = "https://www.luogu.com.cn/problem/"
        solution_url = f"https://www.luogu.com.cn/problem/solution/{pid}"

        try:
            # 获取题目内容
            problem_rsp = requests.get(problem_url + pid, headers=headers)
            
            if problem_rsp.status_code == 429:
                print("请求过于频繁，等待5秒后重试...")
                time.sleep(5)
                return self._pid_parser(pid)
                
            # 使用 json_parser 处理HTML响应
            problem_data = self._json_parser(problem_rsp.text)
            if not problem_data:
                print("题目数据为空")
                return
                
            # 修改数据访问路径
            if "data" not in problem_data or "problem" not in problem_data["data"]:
                print("题目数据格式错误")
                return
                
            problem_js = problem_data["data"]["problem"]
            
            # 从contenu中获取内容
            content = problem_js.get("contenu", {})
            if not content:
                content = problem_js.get("content", {})
                
            # 构建完整的题目数据
            problem_data = {
                "pid": problem_js["pid"],
                "title": problem_js["title"],
                "content": content,
                "samples": problem_js.get("samples", [])
            }
            
            # 获取题解内容
            all_solutions = []
            page = 1
            
            while True:
                current_url = f"{solution_url}?page={page}"
                
                solution_rsp = requests.get(current_url, headers=headers)
                
                solution_data = self._json_parser(solution_rsp.text)
                if not solution_data or "data" not in solution_data:
                    break
                    
                solutions = solution_data["data"].get("solutions", {})
                if not solutions or not solutions.get("result"):
                    break
                    
                # 添加当前页的题解
                current_solutions = solutions["result"]
                all_solutions.extend(current_solutions)
                
                page += 1
                
            # 处理题目和题解，合并到一个文件中
            self._problem_markdown_parser(problem_data, all_solutions)
                
        except Exception as e:
            print(f"题解处理错误: {str(e)}")

    def _problem_markdown_parser(self, problem_js: dict, solutions: list = None):
        """将题目和题解数据转换为Markdown格式"""
        try:
            pid = problem_js["pid"]
            title = problem_js["title"]
            content = problem_js["content"]
            
            # 清理文件名中的非法字符
            safe_title = self._sanitize_filename(title)
            
            # 创建Markdown文件
            with open(f"{pid}-{safe_title}.md", "w", encoding="utf-8") as f:
                # 写入题目部分
                f.write(f"# {title}\n\n")
                
                # 写入背景
                if content.get("background"):
                    f.write("## 题目背景\n\n")
                    f.write(f"{content['background']}\n\n")
                    
                # 写入描述
                if content.get("description"):
                    f.write("## 题目描述\n\n")
                    f.write(f"{content['description']}\n\n")
                    
                # 写入输入格式
                if content.get("inputFormat"):
                    f.write("## 输入格式\n\n")
                    f.write(f"{content['inputFormat']}\n\n")
                    
                # 写入输出格式
                if content.get("outputFormat"):
                    f.write("## 输出格式\n\n")
                    f.write(f"{content['outputFormat']}\n\n")
                    
                # 写入提示
                if content.get("hint"):
                    f.write("## 说明/提示\n\n")
                    f.write(f"{content['hint']}\n\n")
                    
                # 写入样例
                if "samples" in problem_js:
                    for i, sample in enumerate(problem_js["samples"], 1):
                        f.write(f"## 样例 #{i}\n\n")
                        f.write("### 输入\n\n")
                        f.write("```\n")
                        f.write(f"{sample[0]}")
                        f.write("```\n\n")
                        f.write("### 输出\n\n")
                        f.write("```\n")
                        f.write(f"{sample[1]}")
                        f.write("```\n\n")
                
                # 写入题解部分
                if solutions:
                    f.write("# 题解\n\n")
                    # 按点赞数排序题解
                    solutions.sort(key=lambda x: x.get("upvote", 0), reverse=True)
                    
                    # 遍历所有题解
                    for solution in solutions:
                        author = solution.get("author", {}).get("name", "匿名用户")
                        content = solution.get("content", "")
                        upvote = solution.get("upvote", 0)
                        
                        f.write(f"## 作者：{author} (赞：{upvote})\n\n")
                        f.write(f"{content}\n\n")
                        f.write("---\n\n")
                        
        except Exception as e:
            print(f"Markdown转换错误: {str(e)}")


def main():
    """主函数"""
    import argparse
    
    parser = argparse.ArgumentParser(description='洛谷题目完整处理流程')
    parser.add_argument('--skip-download', action='store_true', help='跳过下载新题目')
    parser.add_argument('--skip-classify', action='store_true', help='跳过难度分类')
    parser.add_argument('--skip-tags', action='store_true', help='跳过标签处理')
    parser.add_argument('--skip-solutions', action='store_true', help='跳过题解提取')
    parser.add_argument('--step', type=int, choices=[1, 2, 3, 4], help='只执行指定步骤 (1:下载 2:分类 3:标签 4:题解)')
    
    args = parser.parse_args()
    
    workflow = LuoguWorkflow()
    
    if args.step:
        # 执行指定步骤
        if args.step == 1:
            workflow.step1_download_new_problems()
        elif args.step == 2:
            workflow.step2_classify_by_difficulty()
        elif args.step == 3:
            workflow.step3_process_tags()
        elif args.step == 4:
            workflow.step4_extract_solutions()
    else:
        # 执行完整流程
        workflow.run_complete_workflow(
            skip_download=args.skip_download,
            skip_classify=args.skip_classify,
            skip_tags=args.skip_tags,
            skip_solutions=args.skip_solutions
        )


if __name__ == "__main__":
    main()
