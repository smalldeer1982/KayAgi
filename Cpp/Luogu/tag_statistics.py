import os
import re
from collections import Counter

# 需要过滤的基础标签（可通过参数控制是否启用）
FILTER_TAGS = {
    '贪心', '动态规划', '搜索', '二分', '差分', '数学', '分治', '字符串', '排序',
    '递推', '递归', '前缀和', '进制', '质数', '深度优先搜索 DFS', '广度优先搜索 BFS',
    '模拟', '队列', '位运算', '高精度', '枚举', '组合', '剪枝', '最短路', '树状数组',
    '离散化', '构造', '并查集', '概率论', '组合数学', '线段树', '图论', '分块',
    '状压', '树形', '素数', '筛法', '哈希', '背包', '栈', '生成树', '树形 DP',
    '状压 DP', '区间 DP', 'AC 自动机', '背包 DP', '单调队列', '堆', '树形数据结构',
    '拓扑排序', 'ST 表', '逆元', '平衡树', '容斥原理', '数位 DP', '数论',
    '线性数据结构', '记忆化搜索', '树的遍历', '字典树 Trie', '最大公约数 gcd',
    '二分图', '优先队列', '最近公共祖先 LCA', 'KMP 算法', 'USACO', '分类讨论',
    '强连通分量', '计算几何', '矩阵乘法', '连通块', '树论', '矩阵加速', '倍增',
    '图论建模', '期望', '网络流', '可持久化线段树', '高斯消元', '莫队', '洛谷月赛',
    'NOIP 提高组','NOIP 普及组','CSP-S 提高级','CSP-J 入门级','博弈论','树链剖分','排列组合','动态规划优化','双指针 two-pointer','基环树','NOI','单调栈','根号分治','Manacher 算法','凸包','扫描线','随机化','树的直径','莫比乌斯反演','矩阵运算','欧拉函数','中国剩余定理 CRT','双连通分量','斐波那契数列','线性递推','费用流','Tarjan','欧几里德','欧拉回路','动态树 LCT','快速傅里叶变换 FFT','APIO','最小割','斜率优化','后缀数组 SA','快速数论变换 NTT','可持久化','虚树'


}

# 需要排除的标签（默认排除，不受参数控制）
# EXCLUDED_TAGS = {
#     'O2优化', 'Special Judge', '福建省历届夏令营', '语言月赛', '洛谷原创',
#     'COCI', '蓝桥杯省赛', 'ICPC', '江苏', '信息与未来', 'CCC', 'ROIR',
#     '传智杯', '蓝桥杯国赛', '梦熊比赛', '各省省选', '山东', 'PA', 'CSP-X 小学组', '高校校赛', 'NOI 导刊',
#     '安徽', '提交答案', 'XCPC', 'JOI', 'Ad-hoc', 'NOISG',
#     'POI', '北京', '陕西', 'Code+', '广东', 'BalticOI', 'BCSP-X', '洛谷比赛',
#     '天津', '交互题', '\ufeff基础算法', '南京', '福建', '小学科创活动', '湖北', '湖南', '河南',
#     '集训队互测', '吉林', '云南', 'CEOI', '澳门', '济南', '上海', '青岛'
# }

EXCLUDED_TAGS = {
    'O2优化', 'Special Judge'
}

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

def filter_tags(tags, enable_filter=False):
    """过滤标签
    Args:
        tags: 原始标签列表
        enable_filter: 是否启用基础标签过滤
    Returns:
        过滤后的标签列表
    """
    # 首先排除默认的排除标签
    filtered_tags = [tag for tag in tags if tag not in EXCLUDED_TAGS]

    # 如果启用了基础标签过滤，进一步过滤掉基础标签
    if enable_filter:
        filtered_tags = [tag for tag in filtered_tags if tag not in FILTER_TAGS]

    return filtered_tags

def analyze_tags_by_difficulty(problems_dir, difficulty, enable_filter=False):
    """分析指定难度下的标签分布
    Args:
        problems_dir: 题目目录路径
        difficulty: 难度等级
        enable_filter: 是否启用基础标签过滤（True表示只显示增量标签）
    """
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

    # 过滤标签
    filtered_tags = filter_tags(all_tags, enable_filter)

    # 使用Counter统计标签频率
    tag_counter = Counter(filtered_tags)

    # 获取所有标签（按频率排序）
    top_tags = tag_counter.most_common()

    # 打印统计结果
    mode_text = "增量标签" if enable_filter else "全量标签"
    print(f"\n📊 {difficulty}难度题目统计 ({mode_text}):")
    print(f"总题目数: {file_count}")
    print(f"原始标签总数: {len(all_tags)}")
    print(f"过滤后不同标签数: {len(tag_counter)}")

    if enable_filter:
        print(f"已过滤掉 {len(FILTER_TAGS)} 个基础标签和 {len(EXCLUDED_TAGS)} 个排除标签")
    else:
        print(f"已排除 {len(EXCLUDED_TAGS)} 个默认排除标签")

    print(f"\n🏷️  标签统计 (共{len(top_tags)}个):")
    print("-" * 80)
    print("排名  标签名称                 出现次数  占比")
    print("-" * 80)

    for rank, (tag, count) in enumerate(top_tags, 1):
        percentage = (count / file_count) * 100
        print(f"{rank:3d}.   {tag:<22} {count:5d}   {percentage:5.1f}%")

    # 如果启用了过滤模式，额外显示增量标签列表
    if enable_filter and len(top_tags) > 0:
        print(f"\n💡 增量标签列表（逗号分隔，可直接复制使用）:")
        incremental_tags_str = ','.join([tag for tag, _ in top_tags])
        print(f"{incremental_tags_str}")
    elif enable_filter:
        print("\n该难度下没有发现增量标签")

if __name__ == "__main__":
    # 配置路径
    PROBLEMS_DIR = r"D:\ChatgptKay\kayagi\cpp\luogu\sorted_problems"

    # 指定要分析的难度
    difficulty = "省选"  # 可以改为其他难度：'入门', '普及', '普及+' 等

    # 选择模式
    # enable_filter = False  # 全量标签模式（显示所有标签，排除默认排除标签）
    enable_filter = True   # 增量标签模式（只显示基础标签列表之外的标签）

    print("=" * 80)
    print("🏷️  洛谷题目标签统计分析工具")
    print("=" * 80)
    print(f"分析目录: {PROBLEMS_DIR}")
    print(f"分析难度: {difficulty}")
    print(f"分析模式: {'增量标签模式' if enable_filter else '全量标签模式'}")

    # 运行分析
    analyze_tags_by_difficulty(PROBLEMS_DIR, difficulty, enable_filter)

    print("\n" + "=" * 80)
    print("💡 使用说明:")
    print("- 全量标签模式: 显示所有标签的统计信息（排除默认的地区、比赛等标签）")
    print("- 增量标签模式: 只显示基础标签列表之外的新标签，方便做增量筛选")
    print("- 修改 enable_filter 变量可以切换模式")
    print("=" * 80)
    