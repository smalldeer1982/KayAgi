# 题目信息

# Ideal Point

## 题目描述

You are given $ n $ one-dimensional segments (each segment is denoted by two integers — its endpoints).

Let's define the function $ f(x) $ as the number of segments covering point $ x $ (a segment covers the point $ x $ if $ l \le x \le r $ , where $ l $ is the left endpoint and $ r $ is the right endpoint of the segment).

An integer point $ x $ is called ideal if it belongs to more segments than any other integer point, i. e. $ f(y) < f(x) $ is true for any other integer point $ y $ .

You are given an integer $ k $ . Your task is to determine whether it is possible to remove some (possibly zero) segments, so that the given point $ k $ becomes ideal.

## 说明/提示

In the first example, the point $ 3 $ is already ideal (it is covered by three segments), so you don't have to delete anything.

In the fourth example, you can delete everything except the segment $ [5, 5] $ .

## 样例 #1

### 输入

```
4
4 3
1 3
7 9
2 5
3 6
2 9
1 4
3 7
1 3
2 4
3 5
1 4
6 7
5 5```

### 输出

```
YES
NO
NO
YES```

# AI分析结果

### 题目内容
# 理想点

## 题目描述
给定 $n$ 条一维线段（每条线段由两个整数表示 —— 它的端点）。

定义函数 $f(x)$ 为覆盖点 $x$ 的线段数量（若 $l \leq x \leq r$，其中 $l$ 是线段左端点，$r$ 是线段右端点，则该线段覆盖点 $x$）。

若整数点 $x$ 被包含的线段数比其他任何整数点都多，即对于任何其他整数点 $y$ 都有 $f(y) < f(x)$，则称整数点 $x$ 为理想点。

给定整数 $k$，你的任务是判断是否有可能通过移除一些（可能为零个）线段，使得给定的点 $k$ 成为理想点。

## 说明/提示
在第一个样例中，点 $3$ 已经是理想点（它被三条线段覆盖），所以无需删除任何线段。

在第四个样例中，你可以删除除线段 $[5, 5]$ 之外的所有线段。

## 样例 #1
### 输入
```
4
4 3
1 3
7 9
2 5
3 6
2 9
1 4
3 7
1 3
2 4
3 5
1 4
6 7
5 5
```
### 输出
```
YES
NO
NO
YES
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是围绕如何通过对包含点 $k$ 的线段进行处理，判断是否能使 $k$ 成为理想点。主要差异在于判断的具体方式和实现技巧。
1. **思路对比**：
    - **qifan_maker**：认为只要存在 $[l,k]$ 和 $[k,r]$ 形式的线段，或存在 $[k,k]$ 形式的线段，就能使 $k$ 成为理想点，通过遍历线段判断是否存在这样的线段端点等于 $k$。
    - **Ray1**：维护所有覆盖 $k$ 的线段的交集 $[L,R]$，判断最终交集是否为 $[k,k]$。
    - **loser_seele**：删除不包含 $k$ 的线段后，求剩余线段的交集，判断交集大小是否为 $1$。
    - **ztlh**：Solution 1 统计所有对 $k$ 有贡献的区间对各点的贡献，再遍历判断；Solution 2 类似 Ray1，维护区间 $[L,R]$ 判断最终是否 $L = R$。
    - **ダ月**：贪心选择对 $k$ 有贡献的线段，用差分统计每个点覆盖线段数，再判断是否有点覆盖数大于等于 $k$ 位置的覆盖数。
    - **ttq012**：与ダ月类似，用差分计算各点 $f$ 值，判断是否存在点的 $f$ 值大于等于 $f(k)$。
    - **liujy_**：判断是否存在仅包含点 $k$ 的线段，或两条线段交只包含点 $k$。
2. **算法要点**：
    - **qifan_maker**：遍历线段检查端点。
    - **Ray1**：维护线段交集。
    - **loser_seele**：求线段交集判断大小。
    - **ztlh**：统计贡献或维护区间。
    - **ダ月**：差分统计覆盖数。
    - **ttq012**：差分计算 $f$ 值。
    - **liujy_**：枚举线段判断交。
3. **解决难点**：关键在于如何简洁有效地判断能否通过调整线段使 $k$ 被覆盖次数最多。有的方法通过直接判断线段形式，有的通过求交集，有的通过统计覆盖数等方式。

### 所选的题解
 - **qifan_maker**（5星）
    - **关键亮点**：思路清晰简洁，直接抓住使 $k$ 成为理想点的线段特征，代码实现简单高效。
    ```cpp
    signed main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
        int t;
        cin >> t;
        while (t--){
            int n,k;
            cin >> n >> k;
            bool f1,f2;
            f1 = f2 = false;
            for (int i=1;i<=n;i++){
                int l,r;
                cin >> l >> r;
                if (l == k){
                    f1 = true;
                }
                if (r == k){
                    f2 = true;
                }
            }
            if (f1 and f2){
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
        }
        return 0;
    }
    ```
 - **Ray1**（4星）
    - **关键亮点**：通过维护线段交集的方式判断，思路巧妙，代码简洁。
    ```cpp
    bool check(){
        int L=1,R=50;
        for(int i=1;i<=n;i++){
            cin>>l>>r;
            if(l<=k&&k<=r)L=max(L,l),R=min(R,r);
        }
        return L==R;
    }
    ```
 - **loser_seele**（4星）
    - **关键亮点**：先删除不包含 $k$ 的线段简化问题，再通过求交集判断，逻辑清晰。

### 最优关键思路或技巧
qifan_maker 的思路最为直接高效，通过分析使 $k$ 成为理想点的线段形式，直接遍历线段端点判断，避免了复杂的计算和维护。这种直接抓住问题本质特征的思维方式，能快速简化问题并实现高效求解。

### 拓展
此类题目属于线段覆盖相关问题，常见的类似套路有通过维护线段的一些特性（如交集、覆盖范围等）来解决问题。同类型题目可考虑线段相交、线段合并等场景。

### 推荐题目
 - [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)：涉及括号匹配及区间判断，可锻炼对区间相关问题的处理能力。
 - [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)：虽然主要是区间动态规划，但其中对区间的处理思想有一定相似性。
 - [P3957 [NOIP2017 提高组] 跳房子](https://www.luogu.com.cn/problem/P3957)：涉及区间选择和最优解判断，可加深对区间相关问题的理解。 

---
处理用时：44.77秒