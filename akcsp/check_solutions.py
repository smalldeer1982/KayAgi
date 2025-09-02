import os
import shutil

def check_solutions(solution_dir, solution_deep_dir, output_dir):
    """
    比对 solution 和 solutiondeep 目录下的文件差异
    将在 solution 中存在但在 solutiondeep 中不存在的文件复制到 solution_nodo
    """
    print("开始校对文件...")
    
    # 记录差异文件数量
    diff_count = 0
    
    # 遍历 solution 目录
    for root, dirs, files in os.walk(solution_dir):
        # 获取相对路径
        rel_path = os.path.relpath(root, solution_dir)
        
        for file in files:
            if file.endswith('.md'):
                # 构建源文件路径
                source_file = os.path.join(root, file)
                
                # 构建在 solutiondeep 中对应的文件路径
                deep_file = os.path.join(solution_deep_dir, rel_path, file)
                
                # 如果文件在 solutiondeep 中不存在
                if not os.path.exists(deep_file):
                    # 构建目标路径
                    target_dir = os.path.join(output_dir, rel_path)
                    target_file = os.path.join(target_dir, file)
                    
                    # 确保目标目录存在
                    os.makedirs(target_dir, exist_ok=True)
                    
                    # 复制文件
                    shutil.copy2(source_file, target_file)
                    
                    print(f"发现差异: {os.path.join(rel_path, file)}")
                    diff_count += 1
    
    print(f"\n校对完成！")
    print(f"共发现 {diff_count} 个未处理的文件")
    print(f"这些文件已被复制到: {output_dir}")

if __name__ == "__main__":
    # 设置目录路径
    solution_dir = "d:/ChatgptKay/luogu_crawler-main/Luogu/solution"
    solution_deep_dir = "d:/ChatgptKay/luogu_crawler-main/Luogu/solutiondeep"
    solution_nodo_dir = "d:/ChatgptKay/luogu_crawler-main/Luogu/solution_nodo"
    
    # 执行校对
    check_solutions(solution_dir, solution_deep_dir, solution_nodo_dir) 


        # 设置目录路径
    solution_dir = "d:/ChatgptKay/luogu_crawler-main/CF/solution_CF"
    solution_deep_dir = "d:/ChatgptKay/luogu_crawler-main/CF/solutiondeep_CF"
    solution_nodo_dir = "d:/ChatgptKay/luogu_crawler-main/CF/solution_nodo_CF"
    
    # 执行校对
    check_solutions(solution_dir, solution_deep_dir, solution_nodo_dir) 

        # 设置目录路径
    solution_dir = "d:/ChatgptKay/luogu_crawler-main/AT/solution_AT"
    solution_deep_dir = "d:/ChatgptKay/luogu_crawler-main/AT/solutiondeep_AT"
    solution_nodo_dir = "d:/ChatgptKay/luogu_crawler-main/AT/solution_nodo_AT"
    
    # 执行校对
    check_solutions(solution_dir, solution_deep_dir, solution_nodo_dir) 