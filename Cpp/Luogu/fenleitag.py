import os
import re

def extract_tags_and_content(file_path):
    """
    从 Markdown 文件中提取标签(tag)和正文内容，并解析题号。
    """
    with open(file_path, "r", encoding="utf-8") as file:
        content = file.read()

        # 提取标签，支持 ['动态规划 DP'] 格式
        tag_match = re.search(r"tag:\s*\[(.*?)\]", content)
        if tag_match:
            raw_tags = tag_match.group(1)
            # **拆分时考虑含空格的 tag**
            tags = [t.strip().strip("'\"") for t in re.split(r",\s*", raw_tags)]
        else:
            tags = []

        # 提取题号
        title_match = re.search(r"title:\s*\"?(.+?)\"?\n", content)
        pid_match = re.search(r"pid:\s*(.+)", content)

        title = title_match.group(1).strip() if title_match else "未知题号"
        pid = pid_match.group(1).strip() if pid_match else "未知PID"

        print(f"📜 解析文件: {file_path}")
        print(f"🔍 提取标签: {tags}")
        print(f"🔢 题号: {pid}（{title}）\n")

        return tags, pid, title, content


def consolidate_files_by_tag(target_dir, output_base_dir, target_tag):
    """
    按照指定标签（target_tag）检索并拼接 Markdown 文件，并输出题号列表。
    """
    matched_contents = []
    matched_titles = []

    diff_name = os.path.basename(target_dir)

    for file_name in os.listdir(target_dir):
        if file_name.endswith(".md"):
            file_path = os.path.join(target_dir, file_name)
            tags, pid, title, content = extract_tags_and_content(file_path)

            # ✅ **允许部分匹配**
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
        print(f"✅ 整合完成: {output_file}")

        # 生成题号列表
        list_output_file = os.path.join(output_dir, f"consolidated_{diff_name}_{target_tag}_list.md")
        with open(list_output_file, "w", encoding="utf-8") as list_output:
            list_output.write("# 题号列表\n\n")
            for title in matched_titles:
                list_output.write(f"- {title}\n")
        print(f"✅ 题号列表已保存: {list_output_file}")
    else:
        print(f"⚠️ 未找到包含标签 '{target_tag}' 的文件。")


def combine_all_md_files(output_base_dir, combined_file_name="combined.md"):
    """
    将 OUTPUT_BASE_DIR 文件夹中的所有 Markdown 文件合并为一个文件。
    """
    combined_file_path = os.path.join(output_base_dir, combined_file_name)
    os.makedirs(output_base_dir, exist_ok=True)

    with open(combined_file_path, "w", encoding="utf-8") as combined_file:
        for root, _, files in os.walk(output_base_dir):
            for file_name in files:
                if file_name.endswith(".md"):
                    file_path = os.path.join(root, file_name)
                    with open(file_path, "r", encoding="utf-8") as file:
                        combined_file.write(file.read())
                        combined_file.write("\n\n---\n\n")
    print(f"✅ 所有 Markdown 文件已合并到: {combined_file_path}")

if __name__ == "__main__":

    # # 配置路径和目标标签
    # TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\sorted_problems\普及-"  # 指定文件夹路径
    # OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\tag_problems"  # 保存结果的根目录
    # TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,USACO,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队"  # 输入需要检索的标签，用逗号分隔

    # # 遍历每个标签
    # for tag in TARGET_TAGS.split(','):
    #     tag = tag.strip()  # 去除可能的空格
    #     print(f"\n处理标签: {tag}")
    #     consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
    #     #combine_all_md_files(OUTPUT_BASE_DIR)

    # # 配置路径和目标标签
    # TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\sorted_problems\普及"  # 指定文件夹路径
    # OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\tag_problems"  # 保存结果的根目录
    # TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,USACO,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队"  # 输入需要检索的标签，用逗号分隔

    # # 遍历每个标签
    # for tag in TARGET_TAGS.split(','):
    #     tag = tag.strip()  # 去除可能的空格
    #     print(f"\n处理标签: {tag}")
    #     consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
    #     #combine_all_md_files(OUTPUT_BASE_DIR)

    # # 配置路径和目标标签
    # TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\sorted_problems\普及+"  # 指定文件夹路径
    # OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\tag_problems"  # 保存结果的根目录
    # TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,USACO,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队"  # 输入需要检索的标签，用逗号分隔

    # # 遍历每个标签
    # for tag in TARGET_TAGS.split(','):
    #     tag = tag.strip()  # 去除可能的空格
    #     print(f"\n处理标签: {tag}")
    #     consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
    #     #combine_all_md_files(OUTPUT_BASE_DIR)

    # # 配置路径和目标标签
    # TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\sorted_problems\提高+"  # 指定文件夹路径
    # OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\tag_problems"  # 保存结果的根目录
    # TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,USACO,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队"  # 输入需要检索的标签，用逗号分隔

    # # 遍历每个标签
    # for tag in TARGET_TAGS.split(','):
    #     tag = tag.strip()  # 去除可能的空格
    #     print(f"\n处理标签: {tag}")
    #     consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
    #     #combine_all_md_files(OUTPUT_BASE_DIR)

    #  # 配置路径和目标标签
    # TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\sorted_problems\省选"  # 指定文件夹路径
    # OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\tag_problems"  # 保存结果的根目录
    # TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,USACO,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队"  # 输入需要检索的标签，用逗号分隔

    # # 遍历每个标签
    # for tag in TARGET_TAGS.split(','):
    #     tag = tag.strip()  # 去除可能的空格
    #     print(f"\n处理标签: {tag}")
    #     consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
    #     #combine_all_md_files(OUTPUT_BASE_DIR)

    #  # 配置路径和目标标签
    # TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\sorted_problems\入门"  # 指定文件夹路径
    # OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\tag_problems"  # 保存结果的根目录
    # TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,USACO,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队"  # 输入需要检索的标签，用逗号分隔

    # # 遍历每个标签
    # for tag in TARGET_TAGS.split(','):
    #     tag = tag.strip()  # 去除可能的空格
    #     print(f"\n处理标签: {tag}")
    #     consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
    #     #combine_all_md_files(OUTPUT_BASE_DIR)


    TARGET_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\sorted_problems\NOI"  # 指定文件夹路径
    OUTPUT_BASE_DIR = r"D:\ChatgptKay\kayagi\cpp\Luogu\tag_problems"  # 保存结果的根目录
    #TARGET_TAGS = "NOIP 提高组","NOIP 普及组","CSP-S 提高级","CSP-J 入门级","博弈论","树链剖分","排列组合","动态规划优化","双指针 two-pointer","基环树","NOI","单调栈","根号分治","Manacher 算法","凸包","扫描线","随机化","树的直径","莫比乌斯反演","矩阵运算","欧拉函数","中国剩余定理 CRT","双连通分量","斐波那契数列","线性递推","费用流","Tarjan","欧几里德","欧拉回路","动态树 LCT","快速傅里叶变换 FFT","APIO","最小割","斜率优化","后缀数组 SA","快速数论变换 NTT","可持久化","虚树"
    #TARGET_TAGS = "洛谷原创,各省省选,蓝桥杯国赛,ICPC,蓝桥杯省赛,梦熊比赛,洛谷比赛,NOI 导刊,语言月赛,BCSP-X,扩展欧几里德算法,三分,蓝桥杯青少年组,整除分块,链表,线性 DP,数组,图遍历,不定方程,函数与递归,结构体,鸽笼原理,Catalan 数,不定方程,IOI,THUPC,集训队互测,cdq 分治,SG 函数,折半搜索 meet in the middle,笛卡尔树,离线处理,线性基,点分治,可并堆,原根,生成函数,快速沃尔什变换 FWT,模拟退火,线性代数,Lucas 定理,向量,K-D Tree,树上启发式合并,整体二分,快速莫比乌斯变换 FMT,Kruskal 重构树"
    #TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,USACO,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队,NOIP 提高组,NOIP 普及组,CSP-S 提高级,CSP-J 入门级,博弈论,树链剖分,排列组合,动态规划优化,双指针 two-pointer,基环树,NOI,单调栈,根号分治,Manacher 算法,凸包,扫描线,随机化,树的直径,莫比乌斯反演,矩阵运算,欧拉函数,中国剩余定理 CRT,双连通分量,斐波那契数列,线性递推,费用流,Tarjan,欧几里德,欧拉回路,动态树 LCT,快速傅里叶变换 FFT,APIO,最小割,斜率优化,后缀数组 SA,快速数论变换 NTT,可持久化,虚树"
    # 输入需要检索的标签，用逗号分隔

    TARGET_TAGS = "贪心,动态规划,搜索,二分,差分,数学,分治,字符串,排序,递推,递归,前缀和,进制,质数,深度优先搜索 DFS,广度优先搜索 BFS,模拟,队列,位运算,高精度,枚举,组合,剪枝,最短路,树状数组,离散化,构造,并查集,概率论,组合数学,线段树,图论,分块,状压,树形,素数,筛法,哈希,背包,栈,生成树,树形 DP,状压 DP,区间 DP,AC 自动机,背包 DP,单调队列,堆,树形数据结构,拓扑排序,ST 表,逆元,平衡树,容斥原理,数位 DP,数论,线性数据结构,记忆化搜索,树的遍历,字典树 Trie,最大公约数 gcd,二分图,优先队列,最近公共祖先 LCA,KMP 算法,分类讨论,强连通分量,计算几何,矩阵乘法,连通块,树论,矩阵加速,倍增,图论建模,容斥原理,平衡树,期望,网络流,可持久化线段树,高斯消元,莫队,NOIP 提高组,NOIP 普及组,CSP-S 提高级,CSP-J 入门级,博弈论,树链剖分,排列组合,动态规划优化,双指针 two-pointer,基环树,NOI,单调栈,根号分治,Manacher 算法,凸包,扫描线,随机化,树的直径,莫比乌斯反演,矩阵运算,欧拉函数,中国剩余定理 CRT,双连通分量,斐波那契数列,线性递推,费用流,Tarjan,欧几里德,欧拉回路,动态树 LCT,快速傅里叶变换 FFT,APIO,最小割,斜率优化,后缀数组 SA,快速数论变换 NTT,可持久化,虚树,洛谷原创,各省省选,蓝桥杯国赛,ICPC,蓝桥杯省赛,梦熊比赛,洛谷比赛,NOI 导刊,语言月赛,BCSP-X,扩展欧几里德算法,三分,蓝桥杯青少年组,整除分块,链表,线性 DP,数组,图遍历,不定方程,函数与递归,结构体,鸽笼原理,Catalan 数,不定方程,IOI,THUPC,集训队互测,cdq 分治,SG 函数,折半搜索 meet in the middle,笛卡尔树,离线处理,线性基,点分治,可并堆,原根,生成函数,快速沃尔什变换 FWT,模拟退火,线性代数,Lucas 定理,向量,K-D Tree,树上启发式合并,整体二分,快速莫比乌斯变换 FMT,Kruskal 重构树"
    # 遍历每个标签
    for tag in TARGET_TAGS.split(','):
        tag = tag.strip()  # 去除可能的空格
        print(f"\n处理标签: {tag}")
        consolidate_files_by_tag(TARGET_DIR, OUTPUT_BASE_DIR, tag)
        combine_all_md_files(OUTPUT_BASE_DIR)



