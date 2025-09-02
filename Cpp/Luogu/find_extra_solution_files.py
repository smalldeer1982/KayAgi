#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
找出solution目录中多出来的文件
按照难度/分类进行精确比较，找出每个分类中多出来的文件

逻辑：
1. 读取tag_problems/难度/consolidated_难度_分类_list.md中记录的PID
2. 读取solution/难度/分类/目录下的实际文件
3. 比较两者差异，找出多出来的文件
"""

import os
import re
import json
from collections import defaultdict

class ExtraSolutionFinder:
    def __init__(self):
        current_dir = os.path.dirname(os.path.abspath(__file__))
        self.tag_problems_dir = os.path.join(current_dir, "tag_problems")
        self.solution_dir = os.path.join(current_dir, "solution")
        
        # 存储结果
        self.comparison_results = []
        self.total_extra_files = []
        
        print(f"tag_problems目录: {self.tag_problems_dir}")
        print(f"solution目录: {self.solution_dir}")
        
    def extract_pid_from_filename(self, filename: str) -> str:
        """从文件名中提取题号"""
        match = re.match(r'([BP]\d+)', filename)
        return match.group(1) if match else None
    
    def get_pids_from_list_file(self, list_file_path: str) -> set:
        """从consolidated_*_list.md文件中提取所有PID"""
        pids = set()
        try:
            with open(list_file_path, 'r', encoding='utf-8') as f:
                content = f.read()
                # 匹配格式: "- P1234 - 题目名"
                matches = re.findall(r'^- ([BP]\d+) -', content, re.MULTILINE)
                pids.update(matches)
        except Exception as e:
            print(f"读取文件错误 {list_file_path}: {str(e)}")
        
        return pids
    
    def get_pids_from_solution_dir(self, solution_dir_path: str) -> set:
        """从solution目录中提取所有文件的PID"""
        pids = set()
        try:
            if os.path.exists(solution_dir_path):
                for filename in os.listdir(solution_dir_path):
                    if filename.endswith('.md'):
                        pid = self.extract_pid_from_filename(filename)
                        if pid:
                            pids.add(pid)
        except Exception as e:
            print(f"读取目录错误 {solution_dir_path}: {str(e)}")
        
        return pids
    
    def compare_category(self, difficulty: str, category: str):
        """比较某个难度/分类下的文件"""
        print(f"\n=== 比较 {difficulty}/{category} ===")
        
        # 构建文件路径
        list_file_path = os.path.join(
            self.tag_problems_dir, 
            difficulty, 
            f"consolidated_{difficulty}_{category}_list.md"
        )
        solution_dir_path = os.path.join(self.solution_dir, difficulty, category)
        
        # 检查文件是否存在
        if not os.path.exists(list_file_path):
            print(f"⚠️  list文件不存在: {list_file_path}")
            return
        
        if not os.path.exists(solution_dir_path):
            print(f"⚠️  solution目录不存在: {solution_dir_path}")
            return
        
        # 获取两边的PID集合
        tag_pids = self.get_pids_from_list_file(list_file_path)
        solution_pids = self.get_pids_from_solution_dir(solution_dir_path)
        
        # 计算差异
        extra_pids = solution_pids - tag_pids  # solution中有但tag_problems中没有的
        missing_pids = tag_pids - solution_pids  # tag_problems中有但solution中没有的
        
        print(f"tag_problems中记录: {len(tag_pids)} 个题目")
        print(f"solution中实际有: {len(solution_pids)} 个文件")
        print(f"多出来的文件: {len(extra_pids)} 个")
        print(f"缺少的文件: {len(missing_pids)} 个")
        
        # 记录结果
        result = {
            'difficulty': difficulty,
            'category': category,
            'tag_count': len(tag_pids),
            'solution_count': len(solution_pids),
            'extra_count': len(extra_pids),
            'missing_count': len(missing_pids),
            'extra_pids': list(extra_pids),
            'missing_pids': list(missing_pids)
        }
        
        self.comparison_results.append(result)
        
        # 如果有多出来的文件，记录具体的文件信息
        if extra_pids:
            print(f"多出来的PID: {sorted(list(extra_pids))[:10]}...")  # 只显示前10个
            
            for pid in extra_pids:
                # 找到对应的文件名
                for filename in os.listdir(solution_dir_path):
                    if filename.startswith(pid + '-') and filename.endswith('.md'):
                        file_path = os.path.join(solution_dir_path, filename)
                        self.total_extra_files.append({
                            'difficulty': difficulty,
                            'category': category,
                            'pid': pid,
                            'filename': filename,
                            'file_path': file_path
                        })
                        break
        
        if missing_pids:
            print(f"缺少的PID: {sorted(list(missing_pids))[:10]}...")  # 只显示前10个
    
    def find_all_categories(self):
        """找出所有需要比较的难度/分类组合"""
        categories_to_compare = []
        
        # 遍历tag_problems目录
        for difficulty in os.listdir(self.tag_problems_dir):
            difficulty_path = os.path.join(self.tag_problems_dir, difficulty)
            if not os.path.isdir(difficulty_path):
                continue
            
            # 查找所有consolidated_*_list.md文件
            for filename in os.listdir(difficulty_path):
                if filename.startswith("consolidated_") and filename.endswith("_list.md"):
                    # 从文件名中提取分类名
                    # 格式: consolidated_难度_分类_list.md
                    parts = filename.replace("consolidated_", "").replace("_list.md", "")
                    if parts.startswith(difficulty + "_"):
                        category = parts[len(difficulty) + 1:]  # 去掉"难度_"前缀
                        categories_to_compare.append((difficulty, category))
        
        return categories_to_compare
    
    def run_comparison(self):
        """运行完整的比较流程"""
        print("开始查找多出来的solution文件...")
        
        # 找出所有需要比较的分类
        categories = self.find_all_categories()
        print(f"\n找到 {len(categories)} 个分类需要比较")
        
        # 逐个比较
        for difficulty, category in categories:
            self.compare_category(difficulty, category)
        
        # 生成报告
        self.generate_report()
        
        print("\n✅ 比较完成！")
    
    def generate_report(self):
        """生成详细报告"""
        print("\n=== 生成报告 ===")
        
        # 统计总体情况
        total_extra = sum(r['extra_count'] for r in self.comparison_results)
        total_missing = sum(r['missing_count'] for r in self.comparison_results)
        categories_with_extra = len([r for r in self.comparison_results if r['extra_count'] > 0])
        
        print(f"\n总体统计:")
        print(f"  总共多出来的文件: {total_extra} 个")
        print(f"  总共缺少的文件: {total_missing} 个")
        print(f"  有多余文件的分类: {categories_with_extra} 个")
        
        # 保存详细报告
        report_data = {
            "summary": {
                "total_extra_files": total_extra,
                "total_missing_files": total_missing,
                "categories_with_extra": categories_with_extra,
                "total_categories": len(self.comparison_results)
            },
            "comparison_results": self.comparison_results,
            "extra_files_detail": self.total_extra_files
        }
        
        report_file = "extra_solution_files_report.json"
        with open(report_file, 'w', encoding='utf-8') as f:
            json.dump(report_data, f, ensure_ascii=False, indent=2)
        
        print(f"详细报告已保存到: {report_file}")
        
        # 显示前10个有最多多余文件的分类
        print(f"\n多余文件最多的分类 (前10个):")
        sorted_results = sorted(self.comparison_results, key=lambda x: x['extra_count'], reverse=True)
        for i, result in enumerate(sorted_results[:10], 1):
            if result['extra_count'] > 0:
                print(f"  {i}. {result['difficulty']}/{result['category']}: "
                      f"+{result['extra_count']} 文件 "
                      f"(tag: {result['tag_count']}, solution: {result['solution_count']})")
        
        # 生成删除脚本
        if self.total_extra_files:
            self.generate_delete_script()
    
    def generate_delete_script(self):
        """生成删除多余文件的脚本"""
        script_file = "delete_extra_solution_files.py"
        
        with open(script_file, 'w', encoding='utf-8') as f:
            f.write("#!/usr/bin/env python3\n")
            f.write("# -*- coding: utf-8 -*-\n")
            f.write('"""\n')
            f.write("删除多余的solution文件\n")
            f.write("此脚本由 find_extra_solution_files.py 自动生成\n")
            f.write('"""\n\n')
            f.write("import os\n\n")
            f.write("def delete_extra_files():\n")
            f.write('    """删除所有多余的文件"""\n')
            f.write(f"    extra_files = [\n")
            
            for file_info in self.total_extra_files:
                # 使用 os.path.abspath 确保路径正确，并用 repr() 处理特殊字符
                abs_path = os.path.abspath(file_info['file_path'])
                f.write(f"        {repr(abs_path)},  # {file_info['difficulty']}/{file_info['category']} - {file_info['pid']}\n")
            
            f.write("    ]\n\n")
            f.write("    deleted_count = 0\n")
            f.write("    for file_path in extra_files:\n")
            f.write("        try:\n")
            f.write("            if os.path.exists(file_path):\n")
            f.write("                os.remove(file_path)\n")
            f.write("                print(f'已删除: {os.path.basename(file_path)}')\n")
            f.write("                deleted_count += 1\n")
            f.write("            else:\n")
            f.write("                print(f'文件不存在: {os.path.basename(file_path)}')\n")
            f.write("        except Exception as e:\n")
            f.write("            print(f'删除失败 {os.path.basename(file_path)}: {str(e)}')\n")
            f.write("    \n")
            f.write("    print(f'\\n删除完成，共删除 {deleted_count} 个文件')\n\n")
            f.write("if __name__ == '__main__':\n")
            f.write("    print('警告：此操作将删除所有多余的solution文件！')\n")
            f.write("    print(f'即将删除 {len(extra_files)} 个文件')\n")
            f.write("    confirm = input('确认要删除吗？(输入 YES 确认): ')\n")
            f.write("    if confirm == 'YES':\n")
            f.write("        delete_extra_files()\n")
            f.write("    else:\n")
            f.write("        print('操作已取消')\n")
        
        print(f"删除脚本已生成: {script_file}")
        print("⚠️  请谨慎使用删除脚本！")

def main():
    finder = ExtraSolutionFinder()
    finder.run_comparison()

if __name__ == "__main__":
    main()
