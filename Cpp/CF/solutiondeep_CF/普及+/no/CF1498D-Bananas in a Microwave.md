# 题目信息

# Bananas in a Microwave

## 题目描述

You have a malfunctioning microwave in which you want to put some bananas. You have $ n $ time-steps before the microwave stops working completely. At each time-step, it displays a new operation.

Let $ k $ be the number of bananas in the microwave currently. Initially, $ k = 0 $ . In the $ i $ -th operation, you are given three parameters $ t_i $ , $ x_i $ , $ y_i $ in the input. Based on the value of $ t_i $ , you must do one of the following:

Type 1: ( $ t_i=1 $ , $ x_i $ , $ y_i $ ) — pick an $ a_i $ , such that $ 0 \le a_i \le y_i $ , and perform the following update $ a_i $ times: $ k:=\lceil (k + x_i) \rceil $ .

Type 2: ( $ t_i=2 $ , $ x_i $ , $ y_i $ ) — pick an $ a_i $ , such that $ 0 \le a_i \le y_i $ , and perform the following update $ a_i $ times: $ k:=\lceil (k \cdot x_i) \rceil $ .

Note that  $ x_i $ can be a fractional value. See input format for more details. Also, $ \lceil x \rceil $ is the smallest integer $ \ge x $ .

At the $ i $ -th time-step, you must apply the $ i $ -th operation exactly once.

For each $ j $ such that $ 1 \le j \le m $ , output the earliest time-step at which you can create exactly $ j $ bananas. If you cannot create exactly $ j $ bananas, output $ -1 $ .

## 说明/提示

In the first sample input, let us see how to create $ 16 $ number of bananas in three timesteps. Initially, $ k=0 $ .

- In timestep 1, we choose $ a_1=2 $ , so we apply the type 1 update — $ k := \lceil(k+3)\rceil $ — two times. Hence, $ k $ is now 6.
- In timestep 2, we choose $ a_2=0 $ , hence value of $ k $ remains unchanged.
- In timestep 3, we choose $ a_3=1 $ , so we are applying the type 1 update $ k:= \lceil(k+10)\rceil $ once. Hence, $ k $ is now 16.

It can be shown that $ k=16 $ cannot be reached in fewer than three timesteps with the given operations.

In the second sample input, let us see how to create $ 17 $ number of bananas in two timesteps. Initially, $ k=0 $ .

- In timestep 1, we choose $ a_1=1 $ , so we apply the type 1 update — $ k := \lceil(k+3.99999)\rceil $ — once. Hence, $ k $ is now 4.
- In timestep 2, we choose $ a_2=1 $ , so we apply the type 2 update — $ k := \lceil(k\cdot 4.12345)\rceil $ — once. Hence, $ k $ is now 17.

It can be shown that $ k=17 $ cannot be reached in fewer than two timesteps with the given operations.

## 样例 #1

### 输入

```
3 20
1 300000 2
2 400000 2
1 1000000 3```

### 输出

```
-1 -1 1 -1 -1 1 -1 -1 -1 3 -1 2 3 -1 -1 3 -1 -1 -1 3```

## 样例 #2

### 输入

```
3 20
1 399999 2
2 412345 2
1 1000001 3```

### 输出

```
-1 -1 -1 1 -1 -1 -1 1 -1 -1 3 -1 -1 -1 3 -1 2 -1 3 -1```

# AI分析结果

### 题目翻译
# 微波炉里的香蕉

## 题目描述
你有一个故障的微波炉，你想往里面放一些香蕉。在微波炉完全停止工作之前，你有 $n$ 个时间步。在每个时间步，它会显示一个新的操作。

设 $k$ 为当前微波炉里香蕉的数量。初始时，$k = 0$。在第 $i$ 个操作中，你会在输入中得到三个参数 $t_i$、$x_i$、$y_i$。根据 $t_i$ 的值，你必须执行以下操作之一：

类型 1：（$t_i = 1$，$x_i$，$y_i$）——选择一个 $a_i$，使得 $0 \le a_i \le y_i$，并执行以下更新 $a_i$ 次：$k := \lceil (k + x_i) \rceil$。

类型 2：（$t_i = 2$，$x_i$，$y_i$）——选择一个 $a_i$，使得 $0 \le a_i \le y_i$，并执行以下更新 $a_i$ 次：$k := \lceil (k \cdot x_i) \rceil$。

注意，$x_i$ 可以是一个小数。更多细节请参阅输入格式。此外，$\lceil x \rceil$ 是大于或等于 $x$ 的最小整数。

在第 $i$ 个时间步，你必须恰好执行一次第 $i$ 个操作。

对于每个满足 $1 \le j \le m$ 的 $j$，输出你能恰好得到 $j$ 根香蕉的最早时间步。如果你无法恰好得到 $j$ 根香蕉，输出 $-1$。

## 说明/提示
在第一个示例输入中，让我们看看如何在三个时间步内得到 16 根香蕉。初始时，$k = 0$。
- 在时间步 1 中，我们选择 $a_1 = 2$，所以我们执行类型 1 的更新——$k := \lceil(k + 3)\rceil$——两次。因此，$k$ 现在是 6。
- 在时间步 2 中，我们选择 $a_2 = 0$，因此 $k$ 的值保持不变。
- 在时间步 3 中，我们选择 $a_3 = 1$，所以我们执行类型 1 的更新 $k := \lceil(k + 10)\rceil$ 一次。因此，$k$ 现在是 16。

可以证明，使用给定的操作，在少于三个时间步内无法达到 $k = 16$。

在第二个示例输入中，让我们看看如何在两个时间步内得到 17 根香蕉。初始时，$k = 0$。
- 在时间步 1 中，我们选择 $a_1 = 1$，所以我们执行类型 1 的更新——$k := \lceil(k + 3.99999)\rceil$——一次。因此，$k$ 现在是 4。
- 在时间步 2 中，我们选择 $a_2 = 1$，所以我们执行类型 2 的更新——$k := \lceil(k \cdot 4.12345)\rceil$——一次。因此，$k$ 现在是 17。

可以证明，使用给定的操作，在少于两个时间步内无法达到 $k = 17$。

## 样例 #1
### 输入
```
3 20
1 300000 2
2 400000 2
1 1000000 3
```
### 输出
```
-1 -1 1 -1 -1 1 -1 -1 -1 3 -1 2 3 -1 -1 3 -1 -1 -1 3
```

## 样例 #2
### 输入
```
3 20
1 399999 2
2 412345 2
1 1000001 3
```
### 输出
```
-1 -1 -1 1 -1 -1 -1 1 -1 -1 3 -1 -1 -1 3 -1 2 -1 3 -1
```

### 算法分类
动态规划

### 综合分析与结论
这些题解均围绕动态规划展开，通过不同的状态定义和转移方式来解决问题。
- **思路对比**：大部分题解设 $f$ 数组表示到达某个状态的答案，$g$ 数组辅助转移。vectorwyx 的题解将问题转化为多重背包问题，利用差分优化转移。
- **算法要点**：核心是状态转移，根据操作类型更新状态。不同题解在处理小数和边界条件上略有差异。
- **解决难点**：主要解决操作次数限制和小数计算问题，通过状态数组和取整操作来处理。

### 所选题解
- **do_while_true（5星）**
    - **关键亮点**：思路清晰，代码规范，对状态转移的处理简洁明了。
- **vectorwyx（4星）**
    - **关键亮点**：将问题转化为多重背包问题，利用差分优化转移，有独特的思考角度。
    - **个人心得**：赛时因一处爆 int 而痛失 AC，提醒要注意数据范围。
- **bryce（4星）**
    - **关键亮点**：思路简洁，代码实现简单易懂。

### 重点代码
#### do_while_true 的核心代码
```cpp
void work(int q) {
    int t, y; ll x;
    for(int i = 1; i <= m; ++i) g[i] = INF;
    read(t); read(x); read(y);
    if(t == 1) {
        x = x / 100000 + (x % 100000 > 0);
        g[x] = 1;
        for(int i = 1; i <= m; ++i)
            if(f[i] != INF) g[i] = 0;
        for(int i = 1; i <= m; ++i)
            if(g[i] != y && g[i] != INF && i+x <= m)
                g[i+x] = Min(g[i+x], g[i]+1);
        for(int i = 1; i <= m; ++i)
            if(g[i] <= y && f[i] == INF)
                f[i] = q;
    }
    else {
        for(int i = 1; i <= m; ++i)
            if(f[i] != INF) g[i] = 0;
        for(int i = 1; i <= m; ++i) {
            int p = (int)std::ceil(1.0 * i * x / 100000);
            if(g[i] != y && g[i] != INF && p <= m)
                g[p] = Min(g[p], g[i]+1);
        }
        for(int i = 1; i <= m; ++i)
            if(g[i] <= y && f[i] == INF)
                f[i] = q;
    }
}
```
**核心实现思想**：根据操作类型更新 $g$ 数组，再用 $g$ 数组更新 $f$ 数组。

#### vectorwyx 的核心代码
```cpp
if(t[i]==1){
    fo(j,0,m) if(vis[j]!=ti){
        top=0;
        for(int k=j;k<=m;k+=ceil(x[i]/F)) st[++top]=k,val[top]=0;
        fo(k,1,top) val[k]+=f[i-1][st[k]],val[min(k+y[i]+1,top+1)]-=f[i-1][st[k]];
        fo(k,1,top) val[k]+=val[k-1],f[i][st[k]]=val[k],vis[st[k]]=ti;
    }
}else{
    fo(j,1,m) if(vis[j]!=ti){
        top=0;
        for(ll k=j;k<=m;k=ceil(k*x[i]/F)) st[++top]=k,val[top]=0;
        fo(k,1,top) val[k]+=f[i-1][st[k]],val[min(k+y[i]+1,top+1)]-=f[i-1][st[k]];
        fo(k,1,top) val[k]+=val[k-1],f[i][st[k]]=val[k],vis[st[k]]=ti;
    }
}
```
**核心实现思想**：将问题转化为多重背包问题，利用差分优化转移。

#### bryce 的核心代码
```cpp
if (t == 1){
    for (int j = 0; j <= m; j++){
        int k = ceil(j + x0);
        if (k <= m && g[j] != INF)
            g[k] = min(g[k], g[j] + 1);
    }
}else{
    for (int j = 1; j <= m; j++){
        int k = ceil(1.0 * j * 1.0 * x / 100000);
        if (k <= m && g[j] != INF)
            g[k] = min(g[k], g[j] + 1);
    }
}
for (int j = 1; j <= m; j++)
    if (f[j] == INF && g[j] <= y) f[j] = i;
```
**核心实现思想**：根据操作类型更新 $g$ 数组，再用 $g$ 数组更新 $f$ 数组。

### 关键思路或技巧
- 状态数组的使用：通过 $f$ 数组记录最终答案，$g$ 数组辅助转移，方便处理操作次数限制。
- 差分优化：vectorwyx 的题解将问题转化为多重背包问题，利用差分优化转移，降低时间复杂度。

### 拓展思路
同类型题或类似算法套路：可以尝试更复杂的操作类型和状态转移，如增加操作的种类、限制条件等。还可以考虑多维状态的动态规划问题。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，与本题的动态规划思想类似。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，进一步加深对背包问题的理解。
- [P1832 A+B Problem（再升级）](https://www.luogu.com.cn/problem/P1832)：多重背包问题，与本题的多重背包思路有相似之处。

---
处理用时：68.28秒