# 题目信息

# Reachable Towns

## 题目描述

[problemUrl]: https://atcoder.jp/contests/acl1/tasks/acl1_a

$ 2 $ 次元平面上に $ N $ 個の街があります。$ i $ 個目の街の座標は $ (x_i,\ y_i) $ です。ここで、$ (x_1,\ x_2,\ \dots,\ x_N) $ と $ (y_1,\ y_2,\ \dots,\ y_N) $ は、ともに $ (1,\ 2,\ \dots,\ N) $ の順列となっています。

各 $ k\ =\ 1,2,\dots,N $ について、以下の問題の答えを求めてください。

rngさんが街 $ k $ にいる。 rngさんは、今いる街よりも「$ x,\ y $ 座標がともに小さい街」か「$ x,\ y $ 座標がともに大きい街」に移動することを好きな回数繰り返すことができる。 rngさんが到達可能な街は、(街 $ k $ を含めて) 何種類あるか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200,000 $
- $ (x_1,\ x_2,\ \dots,\ x_N) $ は $ (1,\ 2,\ \dots,\ N) $ の並び替え
- $ (y_1,\ y_2,\ \dots,\ y_N) $ は $ (1,\ 2,\ \dots,\ N) $ の並び替え
- 入力される数は全て整数である．

### Sample Explanation 1

街 $ 3 $ からは街 $ 4 $ に、また逆に街 $ 4 $ からは街 $ 3 $ へ移動できます。

## 样例 #1

### 输入

```
4

1 4

2 3

3 1

4 2```

### 输出

```
1

1

2

2```

## 样例 #2

### 输入

```
7

6 4

4 3

3 5

7 1

2 7

5 2

1 6```

### 输出

```
3

3

1

1

2

3

2```

# AI分析结果

### 题目内容重写

**题目描述**

在二维平面上有 $N$ 个城市。第 $i$ 个城市的坐标是 $(x_i, y_i)$。这里，$(x_1, x_2, \dots, x_N)$ 和 $(y_1, y_2, \dots, y_N)$ 都是 $(1, 2, \dots, N)$ 的排列。

对于每个 $k = 1, 2, \dots, N$，回答以下问题：

rng 在城市 $k$。rng 可以从当前城市移动到“$x, y$ 坐标都比当前城市小的城市”或“$x, y$ 坐标都比当前城市大的城市”，并且可以重复这个过程任意次数。rng 能够到达的城市（包括城市 $k$）有多少种？

**说明/提示**

**约束**

- $1 \leq N \leq 200,000$
- $(x_1, x_2, \dots, x_N)$ 是 $(1, 2, \dots, N)$ 的排列
- $(y_1, y_2, \dots, y_N)$ 是 $(1, 2, \dots, N)$ 的排列
- 输入的所有数都是整数

**样例解释**

样例 1：

输入：

```
4

1 4

2 3

3 1

4 2
```

输出：

```
1

1

2

2
```

样例 2：

输入：

```
7

6 4

4 3

3 5

7 1

2 7

5 2

1 6
```

输出：

```
3

3

1

1

2

3

2
```

### 算法分类

并查集、排序

### 题解分析与结论

#### 题解1：Accelessar (4星)

**关键亮点：**

1. **排序与连通块划分**：通过按 $x$ 排序，将问题转化为连通块划分问题。
2. **区间性质**：证明每个连通块都是一个区间，并给出了分割点的充要条件。
3. **时间复杂度**：$O(n)$ 的时间复杂度，非常高效。

**核心代码：**

```cpp
// 核心思路：按 x 排序后，通过前缀最小值和后缀最大值确定连通块的分割点
// 具体实现略
```

#### 题解2：StayAlone (4星)

**关键亮点：**

1. **连通块大小计算**：通过计算每个点的 $t_i$，确定连通块的区间。
2. **区间合并**：通过合并相交区间，最终得到每个连通块的大小。
3. **时间复杂度**：$O(n \log n)$，可以通过桶排序优化到 $O(n)$。

**核心代码：**

```cpp
int n, ans[MAXN], p[MAXN], mi[MAXN];
pii seg[MAXN]; pair <pii, int> a[MAXN];

int main() {
    read(n);
    rep1(i, 1, n) read(a[i].fst), a[i].snd = i;
    sort(a + 1, a + 1 + n); mi[0] = INF;
    rep1(i, 1, n) p[a[i].fst.snd] = i;
    rep1(i, 1, n) mi[i] = min(mi[i - 1], p[i]);
    rep1(i, 1, n) seg[i] = mp(mi[a[i].fst.snd], i);
    // 以下是合并区间 
    sort(seg + 1, seg + 1 + n);
    int l = seg[1].fst, r = seg[1].snd;
    rep1(i, 1, n) {
        if (r >= seg[i].fst) r = max(r, seg[i].snd);
        else {
            rep1(j, l, r) ans[a[j].snd] = r - l + 1;
            tie(l, r) = seg[i];
        }
    }
    rep1(i, l, r) ans[a[i].snd] = r - l + 1;
    rep1(i, 1, n) printf("%d\n", ans[i]);
    rout;
}
```

#### 题解3：良心WA题人 (3星)

**关键亮点：**

1. **并查集与单调栈**：使用并查集和单调栈维护连通块的合并。
2. **时间复杂度**：$O(n(\log_2n+\alpha(n)))$，较为高效。

**核心代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=200004;
struct node
{
    int x,y,id;
    bool operator<(const node&it)const
    {
        return x>it.x;
    }
}a[NN];
int r[NN],siz[NN],fa[NN],ans[NN];
int find(int u)
{
    return fa[u]==u?u:fa[u]=find(fa[u]);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        fa[i]=i,siz[i]=1;
        a[i].id=i;
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
        r[i]=a[i].y;
    stack<int>sta;
    for(int i=1;i<=n;i++)
    {
        int last=i;
        while(sta.size()&&r[find(sta.top())]>a[i].y)
        {
            int fu=find(last),fv=find(sta.top());
            fa[fu]=fv;
            siz[fv]+=siz[fu];
            r[fv]=max(r[fv],r[fu]);
            last=sta.top();
            sta.pop();
        }
        sta.push(find(i));
    }
    for(int i=1;i<=n;i++)
        ans[a[i].id]=siz[find(i)];
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```

### 最优关键思路或技巧

1. **排序与连通块划分**：通过按 $x$ 排序，将问题转化为连通块划分问题，利用前缀最小值和后缀最大值确定连通块的分割点。
2. **区间合并**：通过合并相交区间，最终得到每个连通块的大小。
3. **并查集与单调栈**：使用并查集和单调栈维护连通块的合并，确保时间复杂度在可接受范围内。

### 可拓展之处

1. **类似题目**：可以扩展到三维或更高维的连通块划分问题。
2. **算法优化**：通过桶排序进一步优化时间复杂度，适用于大规模数据处理。

### 推荐题目

1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

---
处理用时：47.22秒