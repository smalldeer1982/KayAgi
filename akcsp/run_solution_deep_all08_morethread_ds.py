import os
from concurrent.futures import ThreadPoolExecutor
import threading
from solutiondeep_all08_ds import AIProcessor
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

def process_single_file(processor, input_path, output_path, prompt_type="c"):
    try:
        if not running:  # 检查是否应该继续运行
            return
        processor.process_file(input_path, output_path, prompt_type)
    except Exception as e:
        print(f"处理文件出错 {input_path}: {str(e)}")

def collect_all_tasks(base_input, base_output, difficulty, tags, prompt_type):
    """收集所有需要处理的文件任务
    
    Args:
        base_input: 输入基础目录
        base_output: 输出基础目录
        difficulty: 难度等级
        tags: 标签列表
        prompt_type: 提示词类型
        
    Returns:
        tuple: (任务列表, 跳过的文件列表)
    """
    all_tasks = []
    skipped_files = []
    
    for tag in tags:
        # 构建完整的输入输出路径
        input_dir = os.path.join(base_input, difficulty, tag)
        output_dir = os.path.join(base_output, difficulty, tag)
        
        # 检查输入目录是否存在
        if not os.path.exists(input_dir):
            print(f"警告: 输入目录不存在: {input_dir}")
            continue
            
        print(f"正在收集任务: {difficulty}/{tag}")
        
        # 收集该标签下所有需要处理的文件
        for root, dirs, files in os.walk(input_dir):
            if not running:  # 检查是否应该继续运行
                return [], []
            rel_path = os.path.relpath(root, input_dir)
            for file in files:
                if file.endswith('.md'):
                    input_path = os.path.join(root, file)
                    
                    # 构建输出路径，保持相同的目录结构
                    output_path = os.path.join(output_dir, rel_path, file)
                    
                    # 检查输出文件是否已存在，如果存在则跳过
                    if os.path.exists(output_path):
                        skipped_files.append(input_path)
                        continue
                    
                    # 确保输出目录存在
                    os.makedirs(os.path.dirname(output_path), exist_ok=True)
                    
                    all_tasks.append((input_path, output_path, prompt_type))
    
    return all_tasks, skipped_files

def process_all_files(tasks, max_workers=30):
    """处理所有文件任务
    
    Args:
        tasks: 任务列表，每个任务是(输入路径, 输出路径, prompt_type)的元组
        max_workers: 最大并行工作线程数
    """
    global running
    
    if not tasks:
        print("没有新文件需要处理，任务完成")
        return
    
    # 为每个线程创建独立的 AIProcessor 实例
    processors = [AIProcessor() for _ in range(max_workers)]
    
    # 使用线程池处理文件
    with ThreadPoolExecutor(max_workers=max_workers) as executor:
        futures = []
        try:
            for i, (input_path, output_path, prompt_type) in enumerate(tasks):
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
                time.sleep(0.1)  # 减少延迟以提高提交速度
            
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

def process_difficulty_and_tags(base_input, base_output, difficulty, tags_str, prompt_type):
    """处理指定难度和标签的文件
    Args:
        base_input: 输入基础路径
        base_output: 输出基础路径
        difficulty: 难度等级（如 "普及-", "普及", "普及+"）
        tags_str: 标签字符串，用逗号分隔（如 "前缀和,递推,贪心"）
        prompt_type: 提示词类型
    """
    # 分割标签
    tags = [tag.strip() for tag in tags_str.split(',')]
    
    # 收集所有需要处理的文件
    print("\n=== 开始收集所有需要处理的文件 ===")
    all_tasks, skipped_files = collect_all_tasks(base_input, base_output, difficulty, tags, prompt_type)
    
    if skipped_files:
        print(f"已跳过 {len(skipped_files)} 个已处理过的文件")
    
    print(f"找到 {len(all_tasks)} 个文件需要处理")
    
    # 处理所有文件
    print("\n=== 开始处理所有文件 ===")
    print(f"开始多线程处理文件，使用 30 个线程")
    
    process_all_files(all_tasks, max_workers=30)

if __name__ == "__main__":
    # 注册信号处理器
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)
    
    try:
        # # # 设置基础路径
        base_input = "d:/ChatgptKay/KayAgi/Cpp/Luogu/solution"
        base_output = "d:/ChatgptKay/KayAgi/Cpp/Luogu/solutiondeep_visualds8"
        
        # # # 设置AT基础路径
        # base_input = "d:/ChatgptKay/KayAgi/Cpp/AT/solution_AT"
        # base_output = "d:/ChatgptKay/KayAgi/Cpp/AT/solutiondeep_AT_visualds3"

        # base_input = "d:/ChatgptKay/KayAgi/Cpp/CF/solution_CF"
        # base_output = "d:/ChatgptKay/KayAgi/Cpp/CF/solutiondeep_CF_visualds3"

        # base_input = "d:/ChatgptKay/KayAgi/Cpp/SP/solution_SP"
        # base_output = "d:/ChatgptKay/KayAgi/Cpp/SP/solutiondeep_SP_visualds3"

        # 用doubao1.6-think
        difficulty = "提高+"  # 可以是 "普及-", "普及", "普及+"
        tags = "贪心,数学,二分"
        #tags = "排序,树形,状压,背包"
        #tags = "深度优先搜索 DFS,广度优先搜索 BFS"
        #tags = "构造,队列,单调队列,优先队列"
        #tags = "状压,排序,树形,状压,背包,深度优先搜索 DFS,广度优先搜索 BFS,构造,队列,单调队列,优先队列"
        #tags = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,树形 DP,状压 DP,区间 DP,AC 自动机,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法"
        #tags = "洛谷月赛"
        #tags = "双指针 two-pointer,基环树,单调栈,根号分治,Manacher 算法,凸包,扫描线,随机化,树的直径,莫比乌斯反演,矩阵运算,欧拉函数,中国剩余定理 CRT,双连通分量,斐波那契数列,线性递推,费用流,Tarjan,欧几里德,欧拉回路,动态树 LCT,快速傅里叶变换 FFT,最小割,斜率优化,后缀数组 SA,快速数论变换 NTT,可持久化,虚树"
        #tags = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,树形 DP,状压 DP,区间 DP,AC 自动机,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,USACO,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队,洛谷月赛,NOIP 提高组,NOIP 普及组,CSP-S 提高级,CSP-J 入门级,博弈论,树链剖分,排列组合,动态规划优化,双指针 two-pointer,基环树,NOI,单调栈,根号分治,Manacher 算法,凸包,扫描线,随机化,树的直径,莫比乌斯反演,矩阵运算,欧拉函数,中国剩余定理 CRT,双连通分量,斐波那契数列,线性递推,费用流,Tarjan,欧几里德,欧拉回路,动态树 LCT,快速傅里叶变换 FFT,APIO,最小割,斜率优化,后缀数组 SA,快速数论变换 NTT,可持久化,虚树"
        #tags = "洛谷原创,语言月赛"
        #tags = "各省省选,蓝桥杯国赛,ICPC,蓝桥杯省赛,梦熊比赛,洛谷比赛,NOI 导刊,BCSP-X,扩展欧几里德算法,三分,蓝桥杯青少年组,整除分块,链表,线性 DP,数组,图遍历,不定方程,函数与递归,结构体,鸽笼原理,Catalan 数,不定方程,IOI,THUPC,集训队互测,cdq 分治,SG 函数,折半搜索 meet in the middle,笛卡尔树,离线处理,线性基,点分治,可并堆,原根,生成函数,快速沃尔什变换 FWT,模拟退火,线性代数,Lucas 定理,向量,K-D Tree,树上启发式合并,整体二分,快速莫比乌斯变换 FMT,Kruskal 重构树"
        #tags = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,树形 DP,状压 DP,区间 DP,AC 自动机,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队,NOIP 提高组,NOIP 普及组,CSP-S 提高级,CSP-J 入门级,博弈论,树链剖分,排列组合,动态规划优化,双指针 two-pointer,基环树,NOI,单调栈,根号分治,Manacher 算法,凸包,扫描线,随机化,树的直径,莫比乌斯反演,矩阵运算,欧拉函数,中国剩余定理 CRT,双连通分量,斐波那契数列,线性递推,费用流,Tarjan,欧几里德,欧拉回路,动态树 LCT,快速傅里叶变换 FFT,APIO,最小割,斜率优化,后缀数组 SA,快速数论变换 NTT,可持久化,虚树,洛谷原创,各省省选,蓝桥杯国赛,ICPC,蓝桥杯省赛,梦熊比赛,洛谷比赛,NOI 导刊,语言月赛,BCSP-X,扩展欧几里德算法,三分,蓝桥杯青少年组,整除分块,链表,线性 DP,数组,图遍历,不定方程,函数与递归,结构体,鸽笼原理,Catalan 数,不定方程,IOI,THUPC,集训队互测,cdq 分治,SG 函数,折半搜索 meet in the middle,笛卡尔树,离线处理,线性基,点分治,可并堆,原根,生成函数,快速沃尔什变换 FWT,模拟退火,线性代数,Lucas 定理,向量,K-D Tree,树上启发式合并,整体二分,快速莫比乌斯变换 FMT,Kruskal 重构树"

        # 中文
        # prompt_type="c"
        # cn表示需要翻译+需要加tag 
        prompt_type="cn"
        # 处理文件
        process_difficulty_and_tags(base_input, base_output, difficulty, tags, prompt_type)

        print("\n所有文件处理完成！")

    except KeyboardInterrupt:
        print("\n程序已停止")
        sys.exit(0)