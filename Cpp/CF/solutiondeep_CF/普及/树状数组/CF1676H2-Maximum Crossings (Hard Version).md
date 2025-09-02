# 题目信息

# Maximum Crossings (Hard Version)

## 题目描述

The only difference between the two versions is that in this version $ n \leq 2 \cdot 10^5 $ and the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

A terminal is a row of $ n $ equal segments numbered $ 1 $ to $ n $ in order. There are two terminals, one above the other.

You are given an array $ a $ of length $ n $ . For all $ i = 1, 2, \dots, n $ , there should be a straight wire from some point on segment $ i $ of the top terminal to some point on segment $ a_i $ of the bottom terminal. For example, the following pictures show two possible wirings if $ n=7 $ and $ a=[4,1,4,6,7,7,5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H2/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)A crossing occurs when two wires share a point in common. In the picture above, crossings are circled in red.

What is the maximum number of crossings there can be if you place the wires optimally?

## 说明/提示

The first test case is shown in the second picture in the statement.

In the second test case, the only wiring possible has the two wires cross, so the answer is $ 1 $ .

In the third test case, the only wiring possible has one wire, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2```

### 输出

```
6
1
0
3```

# AI分析结果

### 题目中文重写
# 最大交叉数（困难版本）

## 题目描述
两个版本之间的唯一区别在于，在这个版本中 $ n \leq 2 \cdot 10^5 $，并且所有测试用例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $。

终端是一排 $ n $ 个相等的线段，按顺序编号为 $ 1 $ 到 $ n $。有两个终端，一个在另一个上方。

给定一个长度为 $ n $ 的数组 $ a $。对于所有 $ i = 1, 2, \dots, n $，应该有一条直线从顶部终端的线段 $ i $ 上的某个点连接到底部终端的线段 $ a_i $ 上的某个点。例如，如果 $ n = 7 $ 且 $ a = [4,1,4,6,7,7,5] $，以下图片展示了两种可能的布线方式。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H2/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)当两条线共享一个公共点时，就会发生交叉。在上面的图片中，交叉处以红色圆圈标记。

如果以最优方式放置这些线，最多会有多少个交叉点？

## 说明/提示
第一个测试用例如题目描述中的第二张图片所示。

在第二个测试用例中，唯一可能的布线方式使两条线交叉，因此答案是 $ 1 $。

在第三个测试用例中，唯一可能的布线方式只有一条线，因此答案是 $ 0 $。

## 样例 #1

### 输入
```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2
```

### 输出
```
6
1
0
3
```

### 题解综合分析与结论
- **思路**：各题解均指出本题可转化为求逆序对问题，即满足 $i < j$ 且 $a_i \geq a_j$ 的有序对 $(i, j)$ 的数量。
- **算法要点**：
    - **暴力枚举**：适用于简单版本，枚举所有点对 $(i, j)$ 并判断是否满足条件，时间复杂度 $O(n^2)$。
    - **归并排序**：将数组分成两部分分别排序，合并时统计逆序对数量，时间复杂度 $O(n \log n)$。
    - **树状数组**：维护值域，插入元素时查询大于等于当前元素的数量，时间复杂度 $O(n \log n)$，常数较小，代码量短。
- **解决难点**：
    - 理解线段交叉与逆序对的关系，特别是端点在同一段时默认有交点以保证最大交点数。
    - 对于不同算法，掌握其实现细节，如归并排序的合并过程和树状数组的单点修改与区间查询。

### 评分较高的题解
- **RE_Prince（5星）**：
    - **关键亮点**：思路清晰，通过图形直观解释逆序对与线段交叉的关系，代码注释详细，适合初学者。
    - **核心代码**：
```cpp
inline void merge_sort(int l, int r)
{
    int m = (l + r) / 2;
    if (l == r) return;
    else
    {
        merge_sort(l, m);
        merge_sort(m + 1, r);
    }
    int i = l;
    int j = m + 1;
    int tot = l;
    while (i <= m && j <= r)
    {
        if (a[i] >= a[j]) f += m - i + 1, t[tot++] = a[j++];
        else t[tot++] = a[i++];
    }
    while (i <= m) t[tot++] = a[i++];
    while (j <= r) t[tot++] = a[j++];
    for (int i = l; i <= r; i++) a[i] = t[i];
}
```
核心思想：将数组分成两部分分别递归排序，合并时统计逆序对数量。
- **Coros_Trusds（4星）**：
    - **关键亮点**：区分简单版本和困难版本，分别给出不同解法，详细解释了端点相同情况的处理，树状数组代码规范。
    - **核心代码**：
```cpp
struct BIT {
    int tr[N];
    #define lowbit(x) (x & -x)
    inline void init() {
        memset(tr,0,sizeof tr);
    }
    inline void update(int x,int k) {
        for (;x <= S;x += lowbit(x)) {
            tr[x] += k;
        }
    }
    inline int query(int x) {
        int res = 0;
        for (;x;x -= lowbit(x)) {
            res += tr[x];
        }
        return res;
    }
    inline int getsum(int l,int r) {
        return query(r) - query(l - 1);
    }
    #undef lowbit
} bit;
```
核心思想：定义树状数组结构体，实现初始化、单点修改和区间查询功能。
- **Sincerin（4星）**：
    - **关键亮点**：详细分析不同解法的优缺点，强调树状数组的适用性，代码简洁，注释清晰。
    - **核心代码**：
```cpp
inline void change(int x,int v)//单点修改 
{
    for(;x<=n;x+=lowbit(x)) 
        dat[x]+=v;
    return;
}
inline int query(int x)//单点查询前缀和
{
    res=0;
    for(;x;x-=lowbit(x)) 
        res+=dat[x];
    return res;
}
```
核心思想：实现树状数组的单点修改和前缀和查询功能。

### 最优关键思路或技巧
- **思维方式**：将线段交叉问题转化为逆序对问题，通过分析线段端点的位置关系建立数学模型。
- **数据结构**：树状数组在处理逆序对问题时具有常数小、代码量短的优势，适合本题的数据范围。

### 可拓展之处
- **同类型题**：涉及二维偏序的问题，如平面上点对的比较、区间覆盖等。
- **类似算法套路**：归并排序和树状数组常用于解决逆序对、区间统计等问题，可根据具体情况选择合适的算法。

### 洛谷相似题目推荐
- P1908 逆序对
- P3374 【模板】树状数组 1
- P3810 【模板】三维偏序（陌上花开）

### 个人心得摘录与总结
- **RE_Prince**：作者表示写题解时感觉难以表达清楚思路，反映出将复杂的算法思路清晰传达给读者有一定难度。
- **Sincerin**：强调了本题数据范围适合使用树状数组，提醒读者根据数据范围选择合适的算法。 

---
处理用时：36.17秒