# 题目信息

# Even Path

## 题目描述

Pathfinding is a task of finding a route between two points. It often appears in many problems. For example, in a GPS navigation software where a driver can query for a suggested route, or in a robot motion planning where it should find a valid sequence of movements to do some tasks, or in a simple maze solver where it should find a valid path from one point to another point. This problem is related to solving a maze.

The maze considered in this problem is in the form of a matrix of integers $ A $ of $ N \times N $ . The value of each cell is generated from a given array $ R $ and $ C $ of $ N $ integers each. Specifically, the value on the $ i^{th} $ row and $ j^{th} $ column, cell $ (i,j) $ , is equal to $ R_i + C_j $ . Note that all indexes in this problem are from $ 1 $ to $ N $ .

A path in this maze is defined as a sequence of cells $ (r_1,c_1), (r_2,c_2), \dots, (r_k,c_k) $ such that $ |r_i - r_{i+1}| + |c_i - c_{i+1}| = 1 $ for all $ 1 \le i < k $ . In other words, each adjacent cell differs only by $ 1 $ row or only by $ 1 $ column. An even path in this maze is defined as a path in which all the cells in the path contain only even numbers.

Given a tuple $ \langle r_a,c_a,r_b,c_b \rangle $ as a query, your task is to determine whether there exists an even path from cell $ (r_a,c_a) $ to cell $ (r_b,c_b) $ . To simplify the problem, it is guaranteed that both cell $ (r_a,c_a) $ and cell $ (r_b,c_b) $ contain even numbers.

For example, let $ N = 5 $ , $ R = \{6, 2, 7, 8, 3\} $ , and $ C = \{3, 4, 8, 5, 1\} $ . The following figure depicts the matrix $ A $ of $ 5 \times 5 $ which is generated from the given array $ R $ and $ C $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1252C/bfefd5b3fc308f224043cfc77f140d207f38f3a0.png)Let us consider several queries:

- $ \langle 2, 2, 1, 3 \rangle $ : There is an even path from cell $ (2,2) $ to cell $ (1,3) $ , e.g., $ (2,2), (2,3), (1,3) $ . Of course, $ (2,2), (1,2), (1,3) $ is also a valid even path.
- $ \langle 4, 2, 4, 3 \rangle $ : There is an even path from cell $ (4,2) $ to cell $ (4,3) $ , namely $ (4,2), (4,3) $ .
- $ \langle 5, 1, 3, 4 \rangle $ : There is no even path from cell $ (5,1) $ to cell $ (3,4) $ . Observe that the only two neighboring cells of $ (5,1) $ are cell $ (5,2) $ and cell $ (4,1) $ , and both of them contain odd numbers (7 and 11, respectively), thus, there cannot be any even path originating from cell $ (5,1) $ .

## 说明/提示

Explanation for the sample input/output #1

This is the example from the problem description.

## 样例 #1

### 输入

```
5 3
6 2 7 8 3
3 4 8 5 1
2 2 1 3
4 2 4 3
5 1 3 4
```

### 输出

```
YES
YES
NO
```

## 样例 #2

### 输入

```
3 2
30 40 49
15 20 25
2 2 3 3
1 2 2 2
```

### 输出

```
NO
YES
```

# AI分析结果

### 题目中文重写
# 偶数路径

## 题目描述
路径查找是一项在两点之间寻找路线的任务。它经常出现在许多问题中。例如，在一个 GPS 导航软件中，驾驶员可以查询推荐路线；或者在机器人运动规划中，机器人需要找到一个有效的移动序列来完成某些任务；又或者在一个简单的迷宫求解器中，需要找到从一个点到另一个点的有效路径。这个问题与解决迷宫问题有关。

本题中考虑的迷宫是一个 $N \times N$ 的整数矩阵 $A$。每个单元格的值由给定的两个长度为 $N$ 的整数数组 $R$ 和 $C$ 生成。具体来说，第 $i$ 行第 $j$ 列的单元格 $(i, j)$ 的值等于 $R_i + C_j$。注意，本题中所有的索引都从 $1$ 到 $N$。

这个迷宫中的路径定义为一个单元格序列 $(r_1, c_1), (r_2, c_2), \dots, (r_k, c_k)$，使得对于所有的 $1 \le i < k$，都有 $|r_i - r_{i + 1}| + |c_i - c_{i + 1}| = 1$。换句话说，每个相邻的单元格只在一行或一列上有所不同。这个迷宫中的偶数路径定义为路径中所有单元格都只包含偶数的路径。

给定一个元组 $\langle r_a, c_a, r_b, c_b \rangle$ 作为查询，你的任务是确定是否存在从单元格 $(r_a, c_a)$ 到单元格 $(r_b, c_b)$ 的偶数路径。为了简化问题，保证单元格 $(r_a, c_a)$ 和单元格 $(r_b, c_b)$ 都包含偶数。

例如，设 $N = 5$，$R = \{6, 2, 7, 8, 3\}$，$C = \{3, 4, 8, 5, 1\}$。下图描绘了由给定数组 $R$ 和 $C$ 生成的 $5 \times 5$ 矩阵 $A$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1252C/bfefd5b3fc308f224043cfc77f140d207f38f3a0.png)

让我们考虑几个查询：
- $\langle 2, 2, 1, 3 \rangle$：存在一条从单元格 $(2, 2)$ 到单元格 $(1, 3)$ 的偶数路径，例如 $(2, 2), (2, 3), (1, 3)$。当然，$(2, 2), (1, 2), (1, 3)$ 也是一条有效的偶数路径。
- $\langle 4, 2, 4, 3 \rangle$：存在一条从单元格 $(4, 2)$ 到单元格 $(4, 3)$ 的偶数路径，即 $(4, 2), (4, 3)$。
- $\langle 5, 1, 3, 4 \rangle$：不存在从单元格 $(5, 1)$ 到单元格 $(3, 4)$ 的偶数路径。观察可知，$(5, 1)$ 的仅有的两个相邻单元格是 $(5, 2)$ 和 $(4, 1)$，它们都包含奇数（分别为 7 和 11），因此，不可能有任何从单元格 $(5, 1)$ 出发的偶数路径。

## 说明/提示
### 样例输入/输出 #1 的解释
这是题目描述中的示例。

## 样例 #1
### 输入
```
5 3
6 2 7 8 3
3 4 8 5 1
2 2 1 3
4 2 4 3
5 1 3 4
```
### 输出
```
YES
YES
NO
```

## 样例 #2
### 输入
```
3 2
30 40 49
15 20 25
2 2 3 3
1 2 2 2
```
### 输出
```
NO
YES
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于奇偶性的规律来判断是否存在偶数路径。由于数据范围较大，不能直接构造矩阵，所以都从给定的 $R$ 和 $C$ 数组中寻找规律。关键在于发现每次移动时，相邻单元格的奇偶性必须相同，因此只要判断起点和终点所在的行和列的奇偶性是否连续相同即可。

不同题解的实现方式有所不同，有的使用简单的预处理，有的使用数据结构（如 st 表、线段树）来维护区间的奇偶性信息，但本质都是为了快速判断行和列的奇偶性是否一致。

### 所选题解
- **作者：Yawnsean (赞：7)，4星**
    - **关键亮点**：思路清晰，先分析单次操作的合法性，再推广到整个路径的判断。代码实现简洁，复杂度低，通过预处理将连续奇偶性相同的区间赋同一个值，快速判断两行/列是否在同一区间内。
```cpp
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> nums1(n), nums2(n);
    for (auto &v: nums1) cin >> v;
    for (auto &v: nums2) cin >> v;

    vector<int> p1(n), p2(n);
    for (int i = 1; i < n; i ++) {
        p1[i] = (nums1[i] % 2 == nums1[i-1] % 2 ? p1[i-1] : i);
        p2[i] = (nums2[i] % 2 == nums2[i-1] % 2 ? p2[i-1] : i);
    }

    while (q --) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 -- , y1 -- , x2 -- , y2 --;
        cout << (p1[x1] == p1[x2] && p2[y1] == p2[y2] ? "YES\n" : "NO\n");
    }

    return 0;
}
```
核心实现思想：先读取输入的 $n$ 和 $q$，以及数组 $nums1$ 和 $nums2$。然后进行预处理，对于 $p1$ 和 $p2$ 数组，如果当前元素和前一个元素奇偶性相同，则赋值为前一个元素的值，否则赋值为当前索引。最后对于每个查询，判断起点和终点所在行和列的 $p1$ 和 $p2$ 值是否相同，相同则输出 `YES`，否则输出 `NO`。

### 最优关键思路或技巧
- 利用奇偶性的规律，将连续奇偶性相同的区间赋同一个值，这样可以快速判断两行/列是否在同一连续奇偶性相同的区间内，时间复杂度为 $O(n + q)$。

### 可拓展之处
同类型题或类似算法套路：在处理矩阵或网格中的路径问题时，如果题目涉及到某些属性（如奇偶性、颜色等）的限制，可以先分析这些属性的变化规律，然后通过预处理将具有相同属性的区域进行合并或标记，从而简化问题的判断。

### 推荐洛谷题目
1. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：涉及矩阵中区域的判断和填充，与本题中对矩阵元素属性的判断有相似之处。
2. [P1596 [USACO10OCT]Lake Counting S](https://www.luogu.com.cn/problem/P1596)：同样是在矩阵中寻找连通区域的问题，需要对矩阵元素进行判断和搜索。
3. [P2002 消息扩散](https://www.luogu.com.cn/problem/P2002)：涉及图中节点的连通性判断，与本题中路径的可达性判断有一定的相似性。

### 个人心得摘录与总结
- **作者：ivyjiao**：作者提到 “输了，来水一篇题解”，但未详细阐述调试或踩坑经历。不过从题解内容可以推测，作者通过分析左右和上下移动时坐标的奇偶性变化规律，找到了问题的解决方法，体现了从问题本质出发寻找规律的思维方式。 

---
处理用时：56.80秒