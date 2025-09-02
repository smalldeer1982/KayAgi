import os
from concurrent.futures import ThreadPoolExecutor
import threading
from solutiondeep_ss import AIProcessor
import time
import signal
import sys

# 添加一个全局变量来控制程序运行
running = True

def signal_handler(signum, frame):
    """处理 Ctrl+C 信号"""
    global running
    print("\n正在安全停止程序，请稍候...")
    running = False

def process_single_file(processor, input_path, output_path,prompt_type="c"):
    try:
        if not running:  # 检查是否应该继续运行
            return
        processor.process_file(input_path, output_path,prompt_type)
    except Exception as e:
        print(f"处理文件出错 {input_path}: {str(e)}")

def run_with_threads(input_dir, output_dir, max_workers=5,prompt_type="c"):
    global running
    tasks = []
    skipped = 0  # 添加跳过文件计数器
    
    # 收集所有需要处理的文件
    for root, dirs, files in os.walk(input_dir):
        if not running:  # 检查是否应该继续运行
            return
        rel_path = os.path.relpath(root, input_dir)
        for file in files:
            if file.endswith('.md'):
                input_path = os.path.join(root, file)
                # 构建输出路径，保持相同的目录结构
                output_path = os.path.join(output_dir, rel_path, file)
                # 检查输出文件是否已存在，如果存在则跳过
                if os.path.exists(output_path):
                    skipped += 1
                    continue
                
                # 确保输出目录存在
                os.makedirs(os.path.dirname(output_path), exist_ok=True)

                tasks.append((input_path, output_path))
    
    print(f"找到 {len(tasks)} 个文件需要处理，跳过 {skipped} 个已存在的文件")
    
    # 为每个线程创建独立的 AIProcessor 实例
    processors = [AIProcessor() for _ in range(max_workers)]
    
    # 使用线程池处理文件
    with ThreadPoolExecutor(max_workers=max_workers) as executor:
        futures = []
        try:
            for i, (input_path, output_path) in enumerate(tasks):
                if not running:  # 检查是否应该继续运行
                    break
                # 使用对应的处理器
                processor = processors[i % max_workers]
                future = executor.submit(
                    process_single_file, 
                    processor, 
                    input_path, 
                    output_path,
                    prompt_type
                )
                futures.append(future)
                time.sleep(0.5)  # 稍微减少延迟，因为现在是并发的
            
            # 等待所有任务完成并显示进度
            completed = 0
            total = len(futures)
            for future in futures:
                if not running:  # 检查是否应该继续运行
                    break
                try:
                    future.result(timeout=300)  # 5分钟超时
                    completed += 1
                    print(f"进度: {completed}/{total}")
                except Exception as e:
                    print(f"任务执行出错: {str(e)}")
                    
        except KeyboardInterrupt:
            print("\n检测到 Ctrl+C，正在停止所有任务...")
            executor.shutdown(wait=False)
            sys.exit(1)

def process_difficulty_and_tags(base_input, base_output, difficulty, tags_str,prompt_type):
    """处理指定难度和标签的文件
    Args:
        base_input: 输入基础路径
        base_output: 输出基础路径
        difficulty: 难度等级（如 "普及-", "普及", "普及+"）
        tags_str: 标签字符串，用逗号分隔（如 "前缀和,递推,贪心"）
    """
    # 分割标签
    tags = [tag.strip() for tag in tags_str.split(',')]
    
    # 处理每个标签
    for tag in tags:
        print(f"\n=== 处理 {difficulty} - {tag} ===")
        input_directory = os.path.join(base_input, difficulty, tag)
        output_directory = os.path.join(base_output, difficulty, tag)
        
        # 确保输入目录存在
        if not os.path.exists(input_directory):
            print(f"目录不存在: {input_directory}")
            continue
            
        # 创建输出目录
        os.makedirs(output_directory, exist_ok=True)
        
        # 运行处理
        run_with_threads(input_directory, output_directory, max_workers=30,prompt_type=prompt_type)

if __name__ == "__main__":
    # 注册信号处理器
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)
    
    try:
        # # 设置基础路径
        # base_input = "d:/ChatgptKay/KayAgi/Cpp/Luogu/solution"
        # base_output = "d:/ChatgptKay/KayAgi/Cpp/Luogu/solutiondeep_visualds3"
        

        # # 设置AT基础路径
        # base_input = "d:/ChatgptKay/KayAgi/Cpp/AT/solution_AT"
        # base_output = "d:/ChatgptKay/KayAgi/Cpp/AT/solutiondeep_AT_visualds3"

        base_input = "d:/ChatgptKay/KayAgi/Cpp/CF/solution_CF"
        base_output = "d:/ChatgptKay/KayAgi/Cpp/CF/solutiondeep_CF_visualds3"

        # 设置难度和标签
        difficulty = "省选"  # 可以是 "普及-", "普及", "普及+"
        tags = "搜索,广度优先搜索 BFS,深度优先搜索 DFS"  # 用逗号分隔的标签列表

        # 中文
        # prompt_type="c"
        # cn表示需要翻译+需要加tag 
        prompt_type="cn"
        # 处理文件
        process_difficulty_and_tags(base_input, base_output, difficulty, tags,prompt_type)



    except KeyboardInterrupt:
        print("\n程序已停止")
        sys.exit(0)