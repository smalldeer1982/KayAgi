#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
删除多余的solution文件
此脚本由 find_extra_solution_files.py 自动生成
"""

import os

def delete_extra_files():
    """删除所有多余的文件"""
    extra_files = [
        'D:\\ChatgptKay\\KayAgi\\cpp\\luogu\\solution\\省选\\数学\\P6156-简单题.md',  # 省选/数学 - P6156
        'D:\\ChatgptKay\\KayAgi\\cpp\\luogu\\solution\\省选\\数学\\P5087-数学.md',  # 省选/数学 - P5087
        'D:\\ChatgptKay\\KayAgi\\cpp\\luogu\\solution\\省选\\构造\\P2022-有趣的数.md',  # 省选/构造 - P2022
        'D:\\ChatgptKay\\KayAgi\\cpp\\luogu\\solution\\省选\\模拟\\P2021-faebdc玩扑克.md',  # 省选/模拟 - P2021
    ]

    deleted_count = 0
    for file_path in extra_files:
        try:
            if os.path.exists(file_path):
                os.remove(file_path)
                print(f'已删除: {os.path.basename(file_path)}')
                deleted_count += 1
            else:
                print(f'文件不存在: {os.path.basename(file_path)}')
        except Exception as e:
            print(f'删除失败 {os.path.basename(file_path)}: {str(e)}')
    
    print(f'\n删除完成，共删除 {deleted_count} 个文件')

if __name__ == '__main__':
    print('警告：此操作将删除所有多余的solution文件！')
    print(f'即将删除 {len(extra_files)} 个文件')
    confirm = input('确认要删除吗？(输入 YES 确认): ')
    if confirm == 'YES':
        delete_extra_files()
    else:
        print('操作已取消')
