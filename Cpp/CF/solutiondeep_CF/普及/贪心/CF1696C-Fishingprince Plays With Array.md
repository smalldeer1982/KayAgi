# 题目信息

# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56```

### 输出

```
Yes
Yes
No
Yes
No```

# AI分析结果

### 题目内容重写

**题目描述**

Fishingprince 正在玩一个数组 $[a_1, a_2, \dots, a_n]$，他还有一个魔法数字 $m$。

他可以对数组进行以下两种操作：

1. 选择 $1 \le i \le n$，使得 $a_i$ 能被 $m$ 整除（即存在整数 $t$ 使得 $m \cdot t = a_i$）。将 $a_i$ 替换为 $m$ 个 $\frac{a_i}{m}$。其他元素的顺序不变。例如，当 $m=2$ 且 $a=[2,3]$ 且 $i=1$ 时，$a$ 变为 $[1,1,3]$。
2. 选择 $1 \le i \le n-m+1$，使得 $a_i = a_{i+1} = \dots = a_{i+m-1}$。将这 $m$ 个元素替换为一个 $m \cdot a_i$。其他元素的顺序不变。例如，当 $m=2$ 且 $a=[3,2,2,3]$ 且 $i=2$ 时，$a$ 变为 $[3,4,3]$。

注意，数组的长度可能在操作过程中发生变化。上述的 $n$ 定义为数组的当前长度（可能与输入的 $n$ 不同）。

Fishingprince 还有另一个数组 $[b_1, b_2, \dots, b_k]$。请判断他是否可以通过任意次数（可能为零次）的操作将 $a$ 变成 $b$。

### 题解分析与结论

#### 综合分析与结论

本题的核心在于通过两种操作（拆分和合并）将数组 $a$ 转化为数组 $b$。所有题解都抓住了操作的本质，即拆分和合并是互逆的操作，并且通过将两个数组完全拆解后进行比较来判断是否能够转化。

**关键思路：**
1. **互逆操作**：拆分和合并是互逆的，因此可以通过将两个数组完全拆解后进行比较来判断是否能够转化。
2. **压缩存储**：由于拆解后的数组可能非常大，使用结构体或双端队列来压缩存储相同元素的重复次数，避免内存和时间上的浪费。
3. **顺序匹配**：在拆解过程中，保持元素的顺序一致，确保匹配的正确性。

**最优关键思路：**
- **压缩存储**：使用结构体或双端队列来存储拆解后的元素及其重复次数，避免直接存储大量重复元素，提高效率。

### 高星题解推荐

#### 题解1：作者：lenlen (赞：10)
**星级：5星**
**关键亮点：**
- 使用双端队列存储拆解后的元素及其重复次数，确保顺序匹配。
- 通过逐步拆解 $b$ 并与 $a$ 的拆解结果进行匹配，避免一次性存储大量数据。

**核心代码：**
```cpp
deque <hl> q;
for(int i=1;i<=n;i++) {
    scanf("%d",&a[i]);s1+=a[i];
    int k=1;
    while(a[i]%m==0) a[i]/=m,k*=m;
    q.push_back((hl){a[i],k});
}
for(int i=1;i<=nn&&!flag;i++) {
    int k=1;
    while(b[i]%m==0) b[i]/=m,k*=m;
    while(k) {
        if(q.empty()) { flag=1; break; }
        tmp=q.front();q.pop_front();
        if(tmp.d!=b[i]) { flag=1; break; }
        if(tmp.sum<=k) k-=tmp.sum;
        else { q.push_front((hl){tmp.d,tmp.sum-k}); k=0; }
    }
}
```

#### 题解2：作者：Avocadooo (赞：5)
**星级：4星**
**关键亮点：**
- 使用结构体存储拆解后的元素及其重复次数，简化了比较过程。
- 通过合并相邻相同元素的结构体，进一步压缩存储。

**核心代码：**
```cpp
struct NUM { int rt; ll cnt; }a[N],b[N];
for(int i=1,x,y;i<=n;i++) {
    scanf("%d",&x); sum+=x,y=1;
    while(x%m==0) x/=m,y*=m;
    if(!cnt || x!=a[cnt].rt) a[++cnt].rt=x,a[cnt].cnt=y;
    else if(x==a[cnt].rt) a[cnt].cnt+=y;
}
```

### 扩展思路与推荐题目

**扩展思路：**
- 类似的问题可以通过将问题转化为某种标准形式（如完全拆解后的形式）来简化比较。
- 在处理大规模数据时，压缩存储和顺序匹配是常见的优化手段。

**推荐题目：**
1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)

这些题目都涉及到通过某种操作将问题转化为标准形式，或者通过压缩存储来优化算法。

---
处理用时：41.47秒