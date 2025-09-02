import os
import json
import time
import signal
import threading
import shutil
from datetime import datetime
import re
from concurrent.futures import ThreadPoolExecutor
from openai import OpenAI

# 添加一个全局变量来控制程序运行
running = True

def signal_handler(signum, frame):
    """处理 Ctrl+C 信号"""
    global running
    print("\n正在安全停止程序，请稍候...")
    running = False

class AIProcessor:
    def __init__(self, config, difficulty="普及-", cpptype="luogu"):
        """初始化AI处理器
        
        Args:
            config: 配置字典，包含API密钥、URL和模型等信息
            difficulty: 难度等级
            cpptype: 题目类型
        """
        self.api_key = config.get('api_key')
        self.base_url = config.get('base_url')
        self.model = config.get('model')
        self.timeout = config.get('timeout', 1200)
        self.max_retries = config.get('max_retries', 3)
        self.retry_delay = config.get('retry_delay', 5)
        self.difficulty = difficulty
        self.cpptype = cpptype

        self.client = OpenAI(
            api_key=self.api_key,
            base_url=self.base_url,
        )
        
        # 创建日志目录
        self.log_dir = os.path.join(os.path.dirname(__file__), 'logs')
        os.makedirs(self.log_dir, exist_ok=True)

        # 读取提示词模板
        prompt_path = os.path.join(os.path.dirname(__file__), 'prompt_notag.md')
        try:
            with open(prompt_path, 'r', encoding='utf-8') as f:
                self.prompt_template = f.read()
        except Exception as e:
            print(f"读取提示词文件失败: {str(e)}")
            raise
        
        # 初始化分类记录文件 - 根据cpptype和difficulty命名
        self.classification_file = os.path.join(os.path.dirname(__file__), f'algorithm_classification_{cpptype}_{difficulty}.json')
        self.classification_records = {}
        self.pending_records = {}  # 待写入的记录
        self.lock = threading.Lock()  # 添加线程锁
        self.load_classification_records()

    def load_classification_records(self):
        """加载已有的分类记录"""
        try:
            if os.path.exists(self.classification_file):
                with open(self.classification_file, 'r', encoding='utf-8') as f:
                    content = f.read().strip()
                    if content:  # 检查文件是否为空
                        self.classification_records = json.loads(content)
                    else:
                        self.classification_records = {}
                print(f"已加载 {len(self.classification_records)} 个现有分类记录")
            else:
                self.classification_records = {}
                print("未找到现有分类记录文件，将创建新文件")
        except Exception as e:
            print(f"加载分类记录失败: {str(e)}")
            self.classification_records = {}

    def save_classification_records(self, force_save=False):
        """保存分类记录（线程安全）"""
        with self.lock:
            try:
                # 合并待写入的记录
                if self.pending_records:
                    self.classification_records.update(self.pending_records)
                    self.pending_records.clear()
                
                # 确保目录存在
                os.makedirs(os.path.dirname(self.classification_file), exist_ok=True)
                
                # 先写入临时文件，再重命名，避免写入过程中文件损坏
                temp_file = self.classification_file + '.tmp'
                with open(temp_file, 'w', encoding='utf-8') as f:
                    json.dump(self.classification_records, f, ensure_ascii=False, indent=2)
                
                # 重命名临时文件为正式文件
                if os.path.exists(temp_file):
                    if os.path.exists(self.classification_file):
                        os.remove(self.classification_file)
                    os.rename(temp_file, self.classification_file)
                
                print(f"已保存 {len(self.classification_records)} 个分类记录到: {self.classification_file}")
                return True
            except Exception as e:
                print(f"保存分类记录失败: {str(e)}")
                return False

    def move_file_to_algorithm_folder(self, pid, algorithm_classification):
        """将文件移动到对应的算法文件夹
        
        具体操作流程：
        1. 在 cpp/{cpptype}/solution/{difficulty}/no_tag/ 目录下查找以 {pid}- 开头的 .md 文件
        2. 检查目标目录 cpp/{cpptype}/solution/{difficulty}/{algorithm_classification}/ 是否存在
        3. 将找到的文件复制到目标目录（保留原文件）
        4. 如果目标文件已存在则跳过复制
        """
        try:
            # 使用绝对路径
            root_dir = r"D:\ChatgptKay\KayAgi"
            
            # 构建源文件路径
            source_dir = os.path.join(root_dir, "cpp", self.cpptype, "solution_CF", self.difficulty, "no_tag")
            print(f"查找源文件目录: {source_dir}")
            
            # 查找对应的md文件
            source_file = None
            if os.path.exists(source_dir):
                print(f"源目录存在，开始查找文件...")
                for filename in os.listdir(source_dir):
                    if filename.startswith(f"{pid}-") and filename.endswith(".md"):
                        source_file = os.path.join(source_dir, filename)
                        print(f"找到源文件: {filename}")
                        break
            else:
                print(f"源目录不存在: {source_dir}")
            
            if not source_file or not os.path.exists(source_file):
                print(f"警告: 未找到题目 {pid} 的源文件在 {source_dir}")
                return False
            
            # 构建目标文件夹路径
            target_dir = os.path.join(root_dir, "cpp", self.cpptype, "solution_CF", self.difficulty, algorithm_classification)
            print(f"目标目录: {target_dir}")
            
            # 检查目标目录是否存在
            if not os.path.exists(target_dir):
                print(f"警告: 目标目录不存在: {target_dir}")
                return False
            
            # 构建目标文件路径
            filename = os.path.basename(source_file)
            target_file = os.path.join(target_dir, filename)
            
            # 检查目标文件是否已存在
            if os.path.exists(target_file):
                print(f"文件已存在，跳过复制: {target_file}")
                return True
            
            # 复制文件
            shutil.copy2(source_file, target_file)
            print(f"成功复制文件: {pid} -> {algorithm_classification}")
            print(f"  源文件: {source_file}")
            print(f"  目标文件: {target_file}")
            return True
            
        except Exception as e:
            print(f"移动文件失败 {pid}: {str(e)}")
            return False

    def update_moved_status(self, pid, moved=True):
        """更新文件移动状态"""
        with self.lock:
            if pid in self.classification_records:
                self.classification_records[pid]['moved'] = moved
                print(f"已更新 {pid} 的移动状态为: {moved}")
            elif pid in self.pending_records:
                self.pending_records[pid]['moved'] = moved
                print(f"已更新 {pid} 的待写入移动状态为: {moved}")

    def process_file_moves(self):
        """处理文件移动"""
        moved_count = 0
        skipped_count = 0
        
        print("\n=== 开始处理文件移动 ===")
        
        for pid, record in self.classification_records.items():
            if not running:
                break
                
            algorithm_classification = record.get('algorithm_classification', '')
            moved = record.get('moved', False)
            
            # 跳过无算法分类的题目
            if algorithm_classification == "无算法分类":
                continue
                
            # 跳过已经移动过的文件
            if moved:
                skipped_count += 1
                continue
            
            print(f"处理题目 {pid}: {algorithm_classification}")
            
            # 执行文件移动
            if self.move_file_to_algorithm_folder(pid, algorithm_classification):
                self.update_moved_status(pid, True)
                moved_count += 1
                
                # 每移动10个文件保存一次
                if moved_count % 10 == 0:
                    self.save_classification_records()
                    print(f"已移动 {moved_count} 个文件，保存进度...")
        
        # 最终保存
        self.save_classification_records()
        
        print(f"文件移动完成: 移动了 {moved_count} 个文件，跳过了 {skipped_count} 个已移动的文件")
        return moved_count

    def should_skip_classification(self, pid):
        """检查是否应该跳过算法分类
        
        跳过条件：algorithm_classification != "无算法分类"
        重新解析条件：algorithm_classification == "无算法分类" 或者没有记录
        """
        with self.lock:
            # 检查已有记录
            if pid in self.classification_records:
                record = self.classification_records[pid]
                algorithm_classification = record.get('algorithm_classification', '')
                # 只有当算法分类不是"无算法分类"时才跳过
                # 如果是"无算法分类"，则需要重新解析
                if algorithm_classification and algorithm_classification != "无算法分类":
                    print(f"题目 {pid} 已有有效分类 '{algorithm_classification}'，跳过重新解析")
                    return True
                else:
                    print(f"题目 {pid} 分类为 '{algorithm_classification}'，需要重新解析")
                    return False
            
            # 检查待写入记录
            if pid in self.pending_records:
                record = self.pending_records[pid]
                algorithm_classification = record.get('algorithm_classification', '')
                if algorithm_classification and algorithm_classification != "无算法分类":
                    print(f"题目 {pid} 待写入分类 '{algorithm_classification}'，跳过重新解析")
                    return True
                else:
                    print(f"题目 {pid} 待写入分类为 '{algorithm_classification}'，需要重新解析")
                    return False
            
            # 没有任何记录，需要进行分类
            print(f"题目 {pid} 无分类记录，需要进行解析")
            return False

    def get_pending_count(self):
        """获取待写入记录数量"""
        with self.lock:
            return len(self.pending_records)

    def extract_algorithm_classification(self, response_text):
        """从AI响应中提取算法分类"""
        # 查找「算法分类」格式
        pattern = r'【([^】]+)】'
        match = re.search(pattern, response_text)
        if match:
            return match.group(1)
        
        # 如果没找到，尝试查找其他可能的格式
        lines = response_text.split('\n')
        for line in lines[:5]:  # 只检查前5行
            line = line.strip()
            if any(keyword in line for keyword in ['分类', '算法', '标签']):
                # 提取可能的分类词
                algorithm_keywords = [
                    '贪心', '动态规划', '搜索', '二分', '差分', '数学', '分治', '字符串', 
                    '排序', '递推', '递归', '前缀和', '进制', '质数', '深度优先搜索 DFS', 
                    '广度优先搜索 BFS', '模拟', '队列', '位运算', '高精度', '枚举', '组合', 
                    '剪枝', '最短路', '树状数组', '离散化', '构造', '并查集', '概率论', 
                    '组合数学', '线段树', '图论', '分块', '状压', '树形', '素数', '筛法', 
                    '哈希', '背包', '栈', '生成树', '背包 DP', '单调队列', '堆', 
                    '树形数据结构', '拓扑排序', 'ST 表', '逆元', '平衡树', '容斥原理', 
                    '数位 DP', '数论', '线性数据结构', '记忆化搜索', '树的遍历', 
                    '字典树 Trie', '最大公约数 gcd', '二分图', '优先队列', 
                    '最近公共祖先 LCA', 'KMP 算法'
                ]
                for word in algorithm_keywords:
                    if word in line:
                        return word
        
        return "无算法分类"

    def add_classification_record(self, pid, filename, algorithm_classification):
        """添加分类记录到待写入队列（线程安全）"""
        with self.lock:
            self.pending_records[pid] = {
                'pid': pid,
                'filename': filename,
                'algorithm_classification': algorithm_classification,
                'moved': False,
                'timestamp': datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            }
            print(f"已添加分类记录到待写入队列: {pid} -> {algorithm_classification}")

    def classify_problem(self, content, pid, filename):
        """对单个题目进行算法分类"""
        if not running:
            return None
            
        retries = 0
        while retries < self.max_retries:
            try:
                start_time = time.time()
                
                # 添加衔接语
                formatted_content = f"\n\n待处理内容如下：\n\n{content}"
                
                # 准备发送到API的提示词
                if "{{content}}" in self.prompt_template:
                    prompt = self.prompt_template.replace("{{content}}", formatted_content)
                elif "{{CONTENT}}" in self.prompt_template:
                    prompt = self.prompt_template.replace("{{CONTENT}}", formatted_content)
                elif "{content}" in self.prompt_template:
                    prompt = self.prompt_template.replace("{content}", formatted_content)
                elif "[content]" in self.prompt_template:
                    prompt = self.prompt_template.replace("[content]", formatted_content)
                elif "<content>" in self.prompt_template:
                    prompt = self.prompt_template.replace("<content>", formatted_content)
                else:
                    prompt = self.prompt_template + "\n\n待处理内容如下：\n\n" + content
                
                # 构造消息
                messages = [
                    {
                        "role": "system",
                        "content": "你是一位专业的算法分析助理，需要根据题目内容进行精确的算法分类。"
                    },
                    {
                        "role": "user",
                        "content": prompt
                    }
                ]

                print(f"开始分类题目: {pid}")
                
                completion = self.client.chat.completions.create(
                    model=self.model,
                    messages=messages,
                    temperature=0.3,
                    max_tokens=16384
                )
                
                if not completion.choices:
                    raise ValueError("API 响应中没有选项")
                
                response_text = completion.choices[0].message.content
                algorithm_classification = self.extract_algorithm_classification(response_text)
                
                # 添加分类记录到待写入队列
                self.add_classification_record(pid, filename, algorithm_classification)
                
                print(f"题目 {pid} 分类完成: {algorithm_classification}")
                
                # 返回结果
                return {
                    'pid': pid,
                    'filename': filename,
                    'algorithm_classification': algorithm_classification,
                    'moved': False
                }
                
            except Exception as e:
                retries += 1
                print(f"API调用失败 ({retries}/{self.max_retries}): {str(e)}")
                if retries < self.max_retries:
                    print(f"等待 {self.retry_delay} 秒后重试...")
                    time.sleep(self.retry_delay)
                else:
                    print(f"达到最大重试次数，放弃处理题目 {pid}")
                    return None
        
        return None

def load_config(config_path):
    """加载配置文件"""
    try:
        with open(config_path, 'r', encoding='utf-8') as f:
            return json.load(f)
    except Exception as e:
        print(f"读取配置文件出错: {str(e)}")
        raise

def read_no_tag_problems(file_path):
    """读取无标签题目"""
    problems = []
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            
        # 按题目分割
        problem_sections = content.split('---\n')
        
        for section in problem_sections:
            section = section.strip()
            if not section:
                continue
                
            # 提取题号
            pid_match = re.search(r'pid:\s*(\S+)', section)
            if pid_match:
                pid = pid_match.group(1)
                
                # 提取标题
                title_match = re.search(r'title:\s*"([^"]+)"', section)
                title = title_match.group(1) if title_match else f"题目{pid}"
                
                # 构造文件名格式：P1098-[NOIP 2007 提高组] 字符串的展开.md
                filename = f"{pid}-{title}.md"
                
                problems.append({
                    'pid': pid,
                    'title': title,
                    'filename': filename,
                    'content': section
                })
                
    except Exception as e:
        print(f"读取题目文件失败: {str(e)}")
        
    return problems

def process_single_problem(shared_processor, problem):
    """处理单个题目"""
    try:
        if not running:
            return None
        
        pid = problem['pid']
        
        # 检查是否应该跳过分类
        if shared_processor.should_skip_classification(pid):
            print(f"题目 {pid} 已有有效分类，跳过")
            return None
        
        # 进行分类
        result = shared_processor.classify_problem(
            problem['content'], 
            pid, 
            problem['filename']
        )
        
        if result:
            print(f"成功分类题目 {pid}: {result['algorithm_classification']}")
        
        return result
            
    except Exception as e:
        print(f"处理题目出错 {problem['pid']}: {str(e)}")
        return None

def collect_all_tasks(problems, processor):
    """收集所有需要处理的任务"""
    tasks = []
    skipped_count = 0
    
    for problem in problems:
        if not running:
            break
            
        pid = problem['pid']
        if processor.should_skip_classification(pid):
            skipped_count += 1
            continue
        
        tasks.append(problem)
    
    return tasks, skipped_count

def process_all_problems(tasks, config, difficulty, cpptype, max_workers=30, batch_save_size=10):
    """处理所有题目任务"""
    global running
    
    if not tasks:
        print("没有新题目需要处理，任务完成")
        return
    
    # 创建一个共享的处理器实例
    shared_processor = AIProcessor(config, difficulty, cpptype)
    
    # 使用线程池处理题目
    with ThreadPoolExecutor(max_workers=max_workers) as executor:
        futures = []
        try:
            for problem in tasks:
                if not running:
                    break
                future = executor.submit(process_single_problem, shared_processor, problem)
                futures.append(future)
                time.sleep(0.5)  # 添加延迟避免API限制
            
            # 等待所有任务完成并显示进度
            completed = 0
            successful = 0
            total = len(futures)
            
            for future in futures:
                if not running:
                    break
                try:
                    result = future.result(timeout=config.get("timeout", 600))
                    completed += 1
                    if result:
                        successful += 1
                        # 批量保存：每处理成功指定数量就保存一次
                        if successful % batch_save_size == 0:
                            print(f"达到批量保存阈值({batch_save_size})，正在保存...")
                            shared_processor.save_classification_records()
                    
                    # 显示进度和待写入数量
                    pending_count = shared_processor.get_pending_count()
                    print(f"进度: {completed}/{total} (成功: {successful}, 待写入: {pending_count})")
                    
                except Exception as e:
                    completed += 1
                    print(f"任务执行出错: {str(e)}")
                    pending_count = shared_processor.get_pending_count()
                    print(f"进度: {completed}/{total} (成功: {successful}, 待写入: {pending_count})")
                    
        except KeyboardInterrupt:
            print("\n检测到 Ctrl+C，正在停止所有任务...")
            executor.shutdown(wait=False)
            # 即使中断也要保存已完成的结果
            print("正在保存已完成的分类记录...")
            shared_processor.save_classification_records()
            return
    
    # 最终保存所有剩余结果
    print("正在保存最终结果...")
    shared_processor.save_classification_records()
    
    final_count = len(shared_processor.classification_records)
    print(f"\n最终保存了 {final_count} 个分类记录")

def process_algorithm_classification(input_file_path, difficulty, cpptype, max_threads=30, batch_save_size=10):
    """处理算法分类"""
    global running
    
    # 注册信号处理器
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)
    
    # 记录运行开始时间
    start_time = time.strftime("%Y-%m-%d_%H-%M-%S")
    print(f"=== 程序开始运行于: {start_time} ===")
    
    # 加载配置文件
    config_path = os.path.join(os.path.dirname(__file__), 'config_check.json')
    config = load_config(config_path)
    print(f"已加载配置文件: {config_path}")
    print(f"使用模型: {config['model']}")
    print(f"API基础URL: {config['base_url']}")
    print(f"输入文件: {input_file_path}")
    print(f"难度等级: {difficulty}")
    print(f"题目类型: {cpptype}")
    print(f"批量保存大小: {batch_save_size}")
    
    try:
        # 创建处理器实例
        processor = AIProcessor(config, difficulty, cpptype)
        
        # 显示当前已有的分类记录
        existing_count = len(processor.classification_records)
        print(f"当前已有 {existing_count} 个分类记录")
        print(f"分类记录文件: {processor.classification_file}")
        
        # 第一步：处理文件移动
        print("\n=== 第一步：处理文件移动 ===")
        moved_count = processor.process_file_moves()
        
        if not running:
            print("程序被中断")
            return
        
        # 第二步：读取题目数据并进行算法分类
        print("\n=== 第二步：进行算法分类 ===")
        problems = read_no_tag_problems(input_file_path)
        
        if not problems:
            print("未找到题目数据，请检查文件路径")
            return
        
        print(f"找到 {len(problems)} 个无标签题目")
        
        # 收集所有需要处理的任务
        print("\n=== 开始收集需要分类的题目 ===")
        all_tasks, skipped_count = collect_all_tasks(problems, processor)
        
        if skipped_count > 0:
            print(f"已跳过 {skipped_count} 个已有有效分类的题目")
        
        print(f"找到 {len(all_tasks)} 个题目需要重新分类")
        
        if len(all_tasks) == 0:
            print("所有题目都已有有效分类！")
        else:
            # 处理所有题目
            print("\n=== 开始处理算法分类 ===")
            print(f"开始多线程处理题目，使用 {max_threads} 个线程")
            
            process_all_problems(all_tasks, config, difficulty, cpptype, max_threads, batch_save_size)
        
        # 显示最终结果
        final_processor = AIProcessor(config, difficulty, cpptype)
        final_count = len(final_processor.classification_records)
        new_count = final_count - existing_count
        
        print("\n=== 处理完成 ===")
        print(f"文件移动: {moved_count} 个")
        print(f"本次新增分类: {new_count} 个")
        print(f"总分类记录: {final_count} 个")
        print(f"分类记录文件: {final_processor.classification_file}")
        
        # 显示一些分类统计
        if final_processor.classification_records:
            algorithm_stats = {}
            moved_stats = {'已移动': 0, '未移动': 0}
            
            for record in final_processor.classification_records.values():
                algo = record.get('algorithm_classification', '未知')
                algorithm_stats[algo] = algorithm_stats.get(algo, 0) + 1
                
                moved = record.get('moved', False)
                moved_stats['已移动' if moved else '未移动'] += 1
            
            print("\n算法分类统计:")
            for algo, count in sorted(algorithm_stats.items()):
                print(f"  {algo}: {count} 个题目")
            
            print("\n文件移动统计:")
            for status, count in moved_stats.items():
                print(f"  {status}: {count} 个题目")
            
    except KeyboardInterrupt:
        print("\n程序已停止")
    except Exception as e:
        print(f"\n程序执行出错: {str(e)}")

if __name__ == "__main__":
    # ===== 配置参数区域 =====
    
    # 可以根据需要修改难度等级和题目类型
    difficulty = "省选"  # 可选: "普及-", "普及/提高-", "普及+", "提高+/省选-", "省选/NOI-"
    cpptype = "cf"    # 可选: "luogu", "cf", "at", "sp" 等
    
    # 使用绝对路径
    root_dir = r"D:\ChatgptKay\KayAgi"
    
    # 构建输入文件路径
    input_file_path = os.path.join(root_dir, "cpp", cpptype, "tag_problems_CF", difficulty, f"consolidated_{difficulty}_no_tag.md")
    
    # 设置线程数和批量保存大小
    max_threads = 30
    batch_save_size = 10  # 每处理成功10个题目就保存一次
    
    # ===== 配置参数区域结束 =====
    
    print(f"当前处理难度: {difficulty}")
    print(f"当前处理类型: {cpptype}")
    print(f"输入文件路径: {input_file_path}")
    print(f"最大线程数: {max_threads}")
    print(f"批量保存大小: {batch_save_size}")
    
    # 检查文件是否存在
    if not os.path.exists(input_file_path):
        print(f"错误: 输入文件不存在: {input_file_path}")
        print("请检查文件路径或修改 difficulty/cpptype 参数")
    else:
        process_algorithm_classification(input_file_path, difficulty, cpptype, max_threads, batch_save_size) 