# 题目信息

# Program

## 题目描述

You are given a program that consists of $ n $ instructions. Initially a single variable $ x $ is assigned to $ 0 $ . Afterwards, the instructions are of two types:

- increase $ x $ by $ 1 $ ;
- decrease $ x $ by $ 1 $ .

You are given $ m $ queries of the following format:

- query $ l $ $ r $ — how many distinct values is $ x $ assigned to if all the instructions between the $ l $ -th one and the $ r $ -th one inclusive are ignored and the rest are executed without changing the order?

## 说明/提示

The instructions that remain for each query of the first testcase are:

1. empty program — $ x $ was only equal to $ 0 $ ;
2. "-" — $ x $ had values $ 0 $ and $ -1 $ ;
3. "---+" — $ x $ had values $ 0 $ , $ -1 $ , $ -2 $ , $ -3 $ , $ -2 $ — there are $ 4 $ distinct values among them;
4. "+--+--+" — the distinct values are $ 1 $ , $ 0 $ , $ -1 $ , $ -2 $ .

## 样例 #1

### 输入

```
2
8 4
-+--+--+
1 8
2 8
2 5
1 1
4 10
+-++
1 1
1 2
2 2
1 3
2 3
3 3
1 4
2 4
3 4
4 4```

### 输出

```
1
2
4
4
3
3
4
2
3
2
1
2
2
2```

# AI分析结果

### 题目翻译
#### 题目描述
给定一个由 $n$ 条指令组成的程序。初始时，单个变量 $x$ 被赋值为 $0$。此后，指令有两种类型：
- 将 $x$ 加 $1$；
- 将 $x$ 减 $1$。

给定 $m$ 个如下格式的查询：
- 查询 $l$ $r$ —— 如果忽略第 $l$ 条到第 $r$ 条（包含两端）的所有指令，其余指令按顺序执行，$x$ 会被赋值为多少个不同的值？

#### 说明/提示
第一个测试用例中每个查询剩余的指令如下：
1. 空程序 —— $x$ 仅等于 $0$；
2. "-" —— $x$ 取值为 $0$ 和 $-1$；
3. "---+" —— $x$ 取值为 $0$、$-1$、$-2$、$-3$、$-2$，其中有 $4$ 个不同的值；
4. "+--+--+" —— 不同的值为 $1$、$0$、$-1$、$-2$。

#### 样例 #1
##### 输入
```
2
8 4
-+--+--+
1 8
2 8
2 5
1 1
4 10
+-++
1 1
1 2
2 2
1 3
2 3
3 3
1 4
2 4
3 4
4 4
```
##### 输出
```
1
2
4
4
3
3
4
2
3
2
1
2
2
2
```

### 算法分类
前缀和

### 综合分析与结论
这些题解的核心思路都是利用前缀和来处理操作序列，通过求出不同区间的最大值和最小值，进而确定操作过程中出现的不同值的数量。对于删除区间 $[l, r]$ 的情况，将操作序列分为左右两部分，分别计算最值后合并处理，同时要考虑初值 $0$ 是否在取值范围内。

不同题解的主要区别在于使用的数据结构和实现细节：
- 部分题解使用 ST 表来维护区间最值，时间复杂度为 $O(n\log n + m)$。
- 部分题解直接通过前缀和数组计算前缀后缀的最值，时间复杂度为 $O(n + m)$。
- 还有题解使用线段树或猫树来维护最值。

### 所选题解
- **wanggk（5星）**
    - **关键亮点**：思路清晰，详细阐述了每个步骤的处理方法，包括区间处理、最值计算、去重和初值特判等，代码注释丰富，可读性高。
- **Theophania（4星）**
    - **关键亮点**：提供了两种实现方式，一种使用 ST 表，另一种直接扫两遍前缀和，对不同复杂度的实现进行了说明，代码简洁。
- **WaterSun（4星）**
    - **关键亮点**：使用 ST 表维护前缀和的极值，思路明确，对边界情况的处理有详细的特判。

### 重点代码
#### wanggk 的代码
```cpp
// 计算前缀和，前缀最大值，前缀最小值，后缀最大值，后缀最小值
sum[0]=0,mx1[0]=-inf,mx2[n+1]=-inf,mn1[0]=inf,mn2[n+1]=inf;
for(int i=1;i<=n;i++) a[i]=(s[i-1]=='+')?1:-1,sum[i]=sum[i-1]+a[i];
for(int i=1;i<=n;i++) mx1[i]=max(mx1[i-1],sum[i]),mn1[i]=min(mn1[i-1],sum[i]);
for(int i=n;i>=1;i--) mx2[i]=max(mx2[i+1],sum[i]),mn2[i]=min(mn2[i+1],sum[i]); 

// chk 函数用来特判初值 0， solve 函数用来计算两个区间的并区间
int chk(int x,int y){ if(x<=0&&y>=0) return 0; return 1; }
int solve(int x,int y,int x2,int y2)
{
    if(x>x2) swap(x,x2),swap(y,y2);
    if(x2>y) return (y-x+1)+(y2-x2+1)+(chk(x,y)&chk(x2,y2));
    return max(y,y2)-min(x,x2)+1+chk(min(x,x2),max(y,y2));
}
```
**核心实现思想**：先计算前缀和以及前缀后缀的最值，然后通过 `chk` 函数判断初值 $0$ 是否在区间内，`solve` 函数计算两个区间合并后的大小。

#### Theophania 的代码（扫两遍前缀和）
```cpp
for (int i = 1; i <= n; ++i)
{
    sum[i] = sum[i - 1] + (str[i - 1] == '-' ? -1 : 1);
    maxxl[i] = max(maxxl[i - 1], sum[i]);
    minnl[i] = min(minnl[i - 1], sum[i]);
}
maxxr[n + 1] = -inf;
minnr[n + 1] = inf;
for (int i = n; i >= 1; --i)
{
    maxxr[i] = max(maxxr[i + 1], sum[i]);
    minnr[i] = min(minnr[i + 1], sum[i]);
}
for (int cas = 1, l, r; cas <= q; ++cas)
{
    cin >> l >> r;
    int t = sum[r] - sum[l - 1];
    int ans = max(maxxl[l - 1], maxxr[r + 1] - t) - min(minnl[l - 1], minnr[r + 1] - t) + 1;
    cout << ans << '\n';
}
```
**核心实现思想**：通过两遍遍历计算前缀和以及前缀后缀的最值，对于每个查询，计算删除区间后的最值差加一得到答案。

#### WaterSun 的代码
```cpp
// 计算前缀和
for (re int i = 1;i <= n;i++){
    if (s[i] == '+') arr[i] = arr[i - 1] + 1;
    else arr[i] = arr[i - 1] - 1;
}
for (re int i = 1;i <= n;i++) st.dp1[i][0] = st.dp2[i][0] = arr[i];
st.init();
while (q--){
    int l,r;
    cin >> l >> r;
    int l1 = 1,r1 = l - 1;
    int l2 = r + 1,r2 = n;
    int Min = inf,Max = -inf;
    if (l1 <= r1){
        Min = min(Min,st.query_Min(l1,r1));
        Max = max(Max,st.query_Max(l1,r1));
    }
    if (l2 <= r2){
        Min = min(Min,st.query_Min(l2,r2) - sum(l,r));
        Max = max(Max,st.query_Max(l2,r2) - sum(l,r));
    }
    if (Min == inf) Min = 0;
    if (Max == -inf) Max = 0;
    if (Min <= 0 && 0 <= Max) cout << (Max - Min + 1) << "\n";
    else cout << (Max - Min + 2) << "\n";
}
```
**核心实现思想**：先计算前缀和，然后使用 ST 表维护前缀和的极值，对于每个查询，分别计算左右两部分的最值，合并后判断初值 $0$ 是否在区间内，从而确定答案。

### 最优关键思路或技巧
- 利用前缀和数组记录操作序列的状态变化，方便计算不同区间的最值。
- 对于删除区间的情况，将操作序列分为左右两部分，分别计算最值后合并处理，注意处理重叠部分和初值 $0$。
- 可以使用 ST 表、线段树、猫树等数据结构来维护区间最值，提高查询效率。

### 拓展思路
同类型题目可能会有更复杂的操作序列或查询条件，例如操作不仅限于加一减一，还可能有其他运算；查询可能涉及多个区间的删除或修改。类似算法套路可以应用于处理其他具有区间查询和修改需求的问题，如区间和查询、区间最值查询等。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察前缀和与动态规划，与本题利用前缀和处理区间问题的思路有相似之处。
2. [P2420 让我们异或吧](https://www.luogu.com.cn/problem/P2420)：利用前缀和的思想处理异或运算的区间查询问题。
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：涉及树状数组的区间求和操作，与前缀和的思想相关。

### 个人心得
StayAlone 提到自己用线段树维护前缀后缀最值和前缀后缀和，虽然代码不必参考，但指出了本题可以 $O(n)$ 单次处理，强调了对问题本质的理解和不同数据结构的应用。 

---
处理用时：68.16秒