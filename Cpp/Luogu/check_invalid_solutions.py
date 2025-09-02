#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
检查题解文件夹中的无效文件
用于找出因为正则表达式错误导致的错误题解文件

原问题：使用 r'[BP]\d{4,5}' 正则表达式导致 P11111 这样的题号被错误处理
解决方案：以 tag_problems 下的信息作为基准数据，找出 solution 文件夹中的无效文件
"""

import os
import re
import json
from collections import defaultdict
from pathlib import Path

class SolutionValidator:
    def __init__(self):
        # 获取项目根目录
        current_dir = os.path.dirname(os.path.abspath(__file__))
        print(f"当前脚本目录: {current_dir}")
        
        # 直接使用相对路径，因为脚本在 Cpp/Luogu 目录下
        self.tag_problems_dir = os.path.join(current_dir, "tag_problems")
        self.solution_dir = os.path.join(current_dir, "solution")
        
        print(f"计算的tag_problems路径: {self.tag_problems_dir}")
        print(f"计算的solution路径: {self.solution_dir}")
        print(f"tag_problems目录存在: {os.path.exists(self.tag_problems_dir)}")
        print(f"solution目录存在: {os.path.exists(self.solution_dir)}")
        
        # 存储有效的题号集合
        self.valid_pids = set()
        self.invalid_files = []
        self.valid_files = []
        
        # 存储可能被截断的题号模式
        self.potential_truncated_pids = set()  # 5位以上的题号
        
        print(f"标签问题目录: {self.tag_problems_dir}")
        print(f"题解目录: {self.solution_dir}")
    
    def extract_pid_from_filename(self, filename: str) -> str:
        """从文件名中提取题号（正确的方式）"""
        # 使用正确的正则表达式，支持任意位数
        match = re.match(r'([BP]\d+)', filename)
        return match.group(1) if match else None
    
    def extract_old_pid_from_filename(self, filename: str) -> str:
        """使用旧的错误正则表达式提取题号（用于对比）"""
        # 模拟旧的错误正则表达式，只匹配4-5位数字
        match = re.match(r'([BP]\d{4,5})', filename)
        return match.group(1) if match else None
    
    def detect_truncated_pid(self, filename: str) -> dict:
        """检测被截断的题号"""
        # 提取完整的题号
        full_match = re.match(r'([BP]\d+)', filename)
        # 提取被截断的题号（旧逻辑）
        truncated_match = re.match(r'([BP]\d{4,5})', filename)
        
        result = {
            'full_pid': full_match.group(1) if full_match else None,
            'truncated_pid': truncated_match.group(1) if truncated_match else None,
            'is_truncated': False,
            'original_pid': None
        }
        
        if result['full_pid'] and result['truncated_pid']:
            # 如果完整题号比截断题号长，说明发生了截断
            if len(result['full_pid']) > len(result['truncated_pid']):
                result['is_truncated'] = True
                result['original_pid'] = result['full_pid']
        
        return result
    
    def load_valid_pids_from_tag_problems(self):
        """从tag_problems目录加载所有有效的题号"""
        print("\n=== 从tag_problems加载有效题号 ===")
        
        if not os.path.exists(self.tag_problems_dir):
            print(f"错误: tag_problems目录不存在: {self.tag_problems_dir}")
            return
        
        # 遍历所有难度目录
        for difficulty in os.listdir(self.tag_problems_dir):
            difficulty_path = os.path.join(self.tag_problems_dir, difficulty)
            if not os.path.isdir(difficulty_path):
                continue
            
            print(f"处理难度: {difficulty}")
            
            # 遍历该难度下的所有consolidated文件
            for file in os.listdir(difficulty_path):
                if file.startswith("consolidated_") and file.endswith("_list.md"):
                    file_path = os.path.join(difficulty_path, file)
                    pids = self.extract_pids_from_consolidated_file(file_path)
                    self.valid_pids.update(pids)
                    
                    # 收集可能被截断的题号（5位以上）
                    for pid in pids:
                        if len(pid) > 5:  # P/B + 5位以上数字
                            self.potential_truncated_pids.add(pid)
                    
                    print(f"  从 {file} 中提取了 {len(pids)} 个题号")
        
        print(f"\n总共加载了 {len(self.valid_pids)} 个有效题号")
        print(f"其中可能被截断的长题号: {len(self.potential_truncated_pids)} 个")
        print(f"有效题号示例: {list(self.valid_pids)[:10]}")
        
        if self.potential_truncated_pids:
            print(f"长题号示例: {list(self.potential_truncated_pids)[:5]}")
    
    def extract_pids_from_consolidated_file(self, file_path: str) -> set:
        """从consolidated文件中提取所有题号"""
        pids = set()
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
                # 使用正确的正则表达式提取题号
                pattern = r'[BP]\d+'
                found_pids = re.findall(pattern, content)
                pids.update(found_pids)
        except Exception as e:
            print(f"读取文件错误 {file_path}: {str(e)}")
        
        return pids
    
    def check_solution_files(self):
        """检查solution目录下的所有文件"""
        print("\n=== 检查solution目录下的文件 ===")
        
        if not os.path.exists(self.solution_dir):
            print(f"错误: solution目录不存在: {self.solution_dir}")
            return
        
        # 统计信息
        total_files = 0
        invalid_count = 0
        valid_count = 0
        truncated_count = 0
        
        # 遍历所有难度目录
        for difficulty in os.listdir(self.solution_dir):
            difficulty_path = os.path.join(self.solution_dir, difficulty)
            if not os.path.isdir(difficulty_path):
                continue
            
            print(f"\n检查难度: {difficulty}")
            
            # 遍历该难度下的所有算法/标签目录
            for category in os.listdir(difficulty_path):
                category_path = os.path.join(difficulty_path, category)
                if not os.path.isdir(category_path):
                    continue
                
                print(f"  检查分类: {category}")
                
                # 遍历该分类下的所有文件
                for file in os.listdir(category_path):
                    if file.endswith('.md'):
                        total_files += 1
                        file_path = os.path.join(category_path, file)
                        
                        # 检测题号截断情况
                        truncation_info = self.detect_truncated_pid(file)
                        correct_pid = truncation_info['full_pid']
                        
                        # 判断文件状态
                        is_valid = correct_pid and correct_pid in self.valid_pids
                        is_truncated = truncation_info['is_truncated']
                        
                        # 添加调试输出（仅前20个文件）
                        if total_files <= 20:
                            print(f"    调试: {file}")
                            print(f"      提取的题号: {correct_pid}")
                            print(f"      在有效列表中: {correct_pid in self.valid_pids if correct_pid else False}")
                            print(f"      截断信息: {truncation_info}")
                        
                        # 特殊检查：查找疑似被旧正则表达式处理的文件
                        if not is_valid and correct_pid:
                            # 检查是否存在对应的长题号（被截断的原始题号）
                            for potential_original in self.potential_truncated_pids:
                                if potential_original.startswith(correct_pid):
                                    # 找到可能的原始题号
                                    is_truncated = True
                                    truncation_info['is_truncated'] = True
                                    truncation_info['original_pid'] = potential_original
                                    truncation_info['truncated_pid'] = correct_pid
                                    if total_files <= 20:
                                        print(f"      发现可能截断: {correct_pid} -> {potential_original}")
                                    break
                        
                        if is_valid and not is_truncated:
                            # 文件完全有效
                            valid_count += 1
                            self.valid_files.append({
                                'file_path': file_path,
                                'file_name': file,
                                'difficulty': difficulty,
                                'category': category,
                                'correct_pid': correct_pid,
                                'truncation_info': truncation_info
                            })
                        else:
                            # 文件有问题
                            invalid_count += 1
                            if is_truncated:
                                truncated_count += 1
                            
                            reason = self.get_invalid_reason(correct_pid, truncation_info)
                            
                            self.invalid_files.append({
                                'file_path': file_path,
                                'file_name': file,
                                'difficulty': difficulty,
                                'category': category,
                                'correct_pid': correct_pid,
                                'truncation_info': truncation_info,
                                'reason': reason
                            })
                            print(f"    ❌ 问题文件: {file}")
                            print(f"       题号: {correct_pid}")
                            print(f"       原因: {reason}")
                            if is_truncated:
                                print(f"       疑似截断: {truncation_info['truncated_pid']} -> {truncation_info['full_pid']}")
        
        print(f"\n=== 检查完成 ===")
        print(f"总文件数: {total_files}")
        print(f"有效文件: {valid_count}")
        print(f"问题文件: {invalid_count}")
        print(f"疑似截断文件: {truncated_count}")
    
    def get_invalid_reason(self, correct_pid: str, truncation_info: dict) -> str:
        """获取文件无效的原因"""
        if not correct_pid:
            return "无法提取题号"
        elif truncation_info['is_truncated']:
            return f"疑似题号被截断：原始 {truncation_info['original_pid']} -> 截断 {truncation_info['truncated_pid']}"
        elif correct_pid not in self.valid_pids:
            return f"题号 {correct_pid} 不在有效题号列表中（可能是错误生成的题号）"
        else:
            return "未知原因"
    
    def generate_report(self):
        """生成检查报告"""
        print("\n=== 生成检查报告 ===")
        
        # 生成详细报告
        report_file = "solution_validation_report.json"
        report_data = {
            "summary": {
                "total_valid_pids": len(self.valid_pids),
                "total_files_checked": len(self.valid_files) + len(self.invalid_files),
                "valid_files_count": len(self.valid_files),
                "invalid_files_count": len(self.invalid_files)
            },
            "invalid_files": self.invalid_files,
            "valid_files_sample": self.valid_files[:10] if len(self.valid_files) > 10 else self.valid_files
        }
        
        with open(report_file, 'w', encoding='utf-8') as f:
            json.dump(report_data, f, ensure_ascii=False, indent=2)
        
        print(f"详细报告已保存到: {report_file}")
        
        # 生成删除脚本
        if self.invalid_files:
            self.generate_delete_script()
        
        # 打印统计信息
        self.print_statistics()
    
    def generate_delete_script(self):
        """生成删除无效文件的脚本"""
        script_file = "delete_invalid_solutions.py"
        
        with open(script_file, 'w', encoding='utf-8') as f:
            f.write("#!/usr/bin/env python3\n")
            f.write("# -*- coding: utf-8 -*-\n")
            f.write('"""\n')
            f.write("删除无效的题解文件\n")
            f.write("此脚本由 check_invalid_solutions.py 自动生成\n")
            f.write('"""\n\n')
            f.write("import os\n\n")
            f.write("def delete_invalid_files():\n")
            f.write('    """删除所有无效文件"""\n')
            f.write(f"    invalid_files = [\n")
            
            for file_info in self.invalid_files:
                f.write(f"        r'{file_info['file_path']}',  # {file_info['reason']}\n")
            
            f.write("    ]\n\n")
            f.write("    deleted_count = 0\n")
            f.write("    for file_path in invalid_files:\n")
            f.write("        try:\n")
            f.write("            if os.path.exists(file_path):\n")
            f.write("                os.remove(file_path)\n")
            f.write("                print(f'已删除: {file_path}')\n")
            f.write("                deleted_count += 1\n")
            f.write("            else:\n")
            f.write("                print(f'文件不存在: {file_path}')\n")
            f.write("        except Exception as e:\n")
            f.write("            print(f'删除失败 {file_path}: {str(e)}')\n")
            f.write("    \n")
            f.write("    print(f'\\n删除完成，共删除 {deleted_count} 个文件')\n\n")
            f.write("if __name__ == '__main__':\n")
            f.write("    print('警告：此操作将删除所有无效的题解文件！')\n")
            f.write("    confirm = input('确认要删除吗？(输入 YES 确认): ')\n")
            f.write("    if confirm == 'YES':\n")
            f.write("        delete_invalid_files()\n")
            f.write("    else:\n")
            f.write("        print('操作已取消')\n")
        
        print(f"删除脚本已生成: {script_file}")
        print("⚠️  请谨慎使用删除脚本！")
    
    def print_statistics(self):
        """打印统计信息"""
        print("\n=== 统计信息 ===")
        
        # 按难度统计无效文件
        difficulty_stats = defaultdict(int)
        category_stats = defaultdict(int)
        reason_stats = defaultdict(int)
        
        for file_info in self.invalid_files:
            difficulty_stats[file_info['difficulty']] += 1
            category_stats[file_info['category']] += 1
            reason_stats[file_info['reason']] += 1
        
        print("\n按难度统计无效文件:")
        for difficulty, count in sorted(difficulty_stats.items()):
            print(f"  {difficulty}: {count} 个")
        
        print("\n按分类统计无效文件:")
        for category, count in sorted(category_stats.items()):
            print(f"  {category}: {count} 个")
        
        print("\n按原因统计无效文件:")
        for reason, count in sorted(reason_stats.items()):
            print(f"  {reason}: {count} 个")
        
        # 显示一些无效文件示例
        if self.invalid_files:
            print(f"\n无效文件示例（前10个）:")
            for i, file_info in enumerate(self.invalid_files[:10], 1):
                print(f"  {i}. {file_info['file_name']}")
                print(f"     路径: {file_info['file_path']}")
                print(f"     原因: {file_info['reason']}")
                print()
    
    def run_validation(self):
        """运行完整的验证流程"""
        print("开始验证题解文件...")
        
        # 步骤1: 加载有效题号
        self.load_valid_pids_from_tag_problems()
        
        if not self.valid_pids:
            print("错误: 没有加载到任何有效题号，无法继续验证")
            return
        
        # 步骤2: 检查solution文件
        self.check_solution_files()
        
        # 步骤3: 生成报告
        self.generate_report()
        
        print("\n✅ 验证完成！")

def main():
    validator = SolutionValidator()
    validator.run_validation()

if __name__ == "__main__":
    main()

