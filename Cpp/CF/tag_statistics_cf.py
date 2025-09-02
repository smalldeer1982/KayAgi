import os
import re
from collections import Counter

def extract_tags(file_path):
    """从 Markdown 文件中提取标签"""
    with open(file_path, "r", encoding="utf-8") as file:
        content = file.read()
        tag_match = re.search(r"tag:\s*\[(.*?)\]", content)
        if tag_match:
            raw_tags = tag_match.group(1)
            # 拆分标签，考虑含空格的tag
            return [t.strip().strip("'\"") for t in re.split(r",\s*", raw_tags)]
        return []

def analyze_tags_by_difficulty(problems_dir, difficulty):
    """分析指定难度下的标签分布"""
    # 构建难度文件夹的完整路径
    difficulty_dir = os.path.join(problems_dir, difficulty)
    
    if not os.path.exists(difficulty_dir):
        print(f"❌ 错误：找不到难度文件夹 '{difficulty}'")
        return
    
    # 收集所有标签
    all_tags = []
    file_count = 0
    
    # 遍历指定难度下的所有md文件
    for file_name in os.listdir(difficulty_dir):
        if file_name.endswith(".md"):
            file_path = os.path.join(difficulty_dir, file_name)
            tags = extract_tags(file_path)
            all_tags.extend(tags)
            file_count += 1
    
    # 使用Counter统计标签频率
    tag_counter = Counter(all_tags)
    
    # 获取前20个最常见的标签
    top_20_tags = tag_counter.most_common(40)
    
    # 打印统计结果
    print(f"\n📊 {difficulty}难度题目统计:")
    print(f"总题目数: {file_count}")
    print(f"不同标签数: {len(tag_counter)}")
    print("\n🏷️  前20个最常见标签:")
    print("-" * 40)
    print("排名  标签名称                 出现次数  占比")
    print("-" * 40)
    
    for rank, (tag, count) in enumerate(top_20_tags, 1):
        percentage = (count / file_count) * 100
        print(f"{rank:2d}.   {tag:<22} {count:5d}   {percentage:5.1f}%")

if __name__ == "__main__":
    # 配置路径
    PROBLEMS_DIR = r"D:\ChatgptKay\luogu_crawler-main\CF\sorted_problems_CF"
    
    # 指定要分析的难度
    difficulty = "普及+"  # 可以改为其他难度：'入门', '普及', '普及+' 等
    
    # 运行分析
    analyze_tags_by_difficulty(PROBLEMS_DIR, difficulty) 
    

    #常用的tag
    # 贪心
    # 动态规划
    # 搜索
    # 二分
    # 差分
    # 数学
    # 分治
    # 字符串
    # 排序
    # 递推
    # 递归
    # 前缀和
    # 进制
    # 质数
    # 深度优先搜索 DFS
    # 广度优先搜索 BFS
    # 模拟
    # 队列
    # 位运算
    # 高精度
    # 枚举
    # 组合
    # 剪枝
    # 最短路
    # 树状数组
    # 离散化
    # 构造
    # 并查集
    # 概率论
    # 组合数学
    # 图论