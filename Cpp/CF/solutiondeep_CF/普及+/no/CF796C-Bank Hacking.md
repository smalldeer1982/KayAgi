# 题目信息

# Bank Hacking

## 题目描述

Although Inzane successfully found his beloved bone, Zane, his owner, has yet to return. To search for Zane, he would need a lot of money, of which he sadly has none. To deal with the problem, he has decided to hack the banks.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796C/2dce5999c2db79450d45fe87441c705c32509051.png)There are $ n $ banks, numbered from $ 1 $ to $ n $ . There are also $ n-1 $ wires connecting the banks. All banks are initially online. Each bank also has its initial strength: bank $ i $ has initial strength $ a_{i} $ .

Let us define some keywords before we proceed. Bank $ i $ and bank $ j $ are neighboring if and only if there exists a wire directly connecting them. Bank $ i $ and bank $ j $ are semi-neighboring if and only if there exists an online bank $ k $ such that bank $ i $ and bank $ k $ are neighboring and bank $ k $ and bank $ j $ are neighboring.

When a bank is hacked, it becomes offline (and no longer online), and other banks that are neighboring or semi-neighboring to it have their strengths increased by $ 1 $ .

To start his plan, Inzane will choose a bank to hack first. Indeed, the strength of such bank must not exceed the strength of his computer. After this, he will repeatedly choose some bank to hack next until all the banks are hacked, but he can continue to hack bank $ x $ if and only if all these conditions are met:

1. Bank $ x $ is online. That is, bank $ x $ is not hacked yet.
2. Bank $ x $ is neighboring to some offline bank.
3. The strength of bank $ x $ is less than or equal to the strength of Inzane's computer.

Determine the minimum strength of the computer Inzane needs to hack all the banks.

## 说明/提示

In the first sample, Inzane can hack all banks using a computer with strength $ 5 $ . Here is how:

- Initially, strengths of the banks are $ [1,2,3,4,5] $ .
- He hacks bank $ 5 $ , then strengths of the banks become $ [1,2,4,5,-] $ .
- He hacks bank $ 4 $ , then strengths of the banks become $ [1,3,5,-,-] $ .
- He hacks bank $ 3 $ , then strengths of the banks become $ [2,4,-,-,-] $ .
- He hacks bank $ 2 $ , then strengths of the banks become $ [3,-,-,-,-] $ .
- He completes his goal by hacking bank $ 1 $ .

In the second sample, Inzane can hack banks $ 4 $ , $ 2 $ , $ 3 $ , $ 1 $ , $ 5 $ , $ 7 $ , and $ 6 $ , in this order. This way, he can hack all banks using a computer with strength $ 93 $ .

## 样例 #1

### 输入

```
5
1 2 3 4 5
1 2
2 3
3 4
4 5
```

### 输出

```
5```

## 样例 #2

### 输入

```
7
38 -29 87 93 39 28 -55
1 2
2 5
3 2
2 4
1 7
7 6
```

### 输出

```
93```

## 样例 #3

### 输入

```
5
1 2 7 6 7
1 5
5 3
3 4
2 4
```

### 输出

```
8```

# AI分析结果

### 题目内容
# 银行黑客

## 题目描述
尽管因扎内成功找到了他心爱的骨头，但他的主人赞恩尚未归来。为了寻找赞恩，他需要大量的钱，而遗憾的是他身无分文。为了解决这个问题，他决定入侵银行。

有\(n\)家银行，编号从\(1\)到\(n\)。同时有\(n - 1\)条线路连接这些银行。所有银行最初都是在线状态。每家银行也有其初始强度：银行\(i\)的初始强度为\(a_{i}\)。

在继续之前，我们先定义一些关键词。银行\(i\)和银行\(j\)相邻，当且仅当存在一条线路直接连接它们。银行\(i\)和银行\(j\)半相邻，当且仅当存在一个在线银行\(k\)，使得银行\(i\)和银行\(k\)相邻，且银行\(k\)和银行\(j\)相邻。

当一家银行被入侵时，它会变为离线状态（不再在线），并且与它相邻或半相邻的其他银行的强度会增加\(1\)。

为了开始他的计划，因扎内首先会选择一家银行进行入侵。实际上，这家银行的强度不能超过他电脑的强度。在此之后，他会反复选择其他银行进行入侵，直到所有银行都被入侵，但他能够继续入侵银行\(x\)，当且仅当满足以下所有条件：
1. 银行\(x\)是在线的。即银行\(x\)尚未被入侵。
2. 银行\(x\)与某个离线银行相邻。
3. 银行\(x\)的强度小于或等于因扎内电脑的强度。

确定因扎内入侵所有银行所需电脑的最小强度。

## 说明/提示
在第一个样例中，因扎内可以使用强度为\(5\)的电脑入侵所有银行。过程如下：
- 最初，银行的强度为\([1,2,3,4,5]\)。
- 他入侵银行\(5\)，然后银行的强度变为\([1,2,4,5,-]\)。
- 他入侵银行\(4\)，然后银行的强度变为\([1,3,5,-,-]\)。
- 他入侵银行\(3\)，然后银行的强度变为\([2,4,-,-,-]\)。
- 他入侵银行\(2\)，然后银行的强度变为\([3,-,-,-,-]\)。
- 他通过入侵银行\(1\)完成目标。

在第二个样例中，因扎内可以按顺序入侵银行\(4\)、\(2\)、\(3\)、\(1\)、\(5\)、\(7\)和\(6\)。通过这种方式，他可以使用强度为\(93\)的电脑入侵所有银行。

## 样例 #1
### 输入
```
5
1 2 3 4 5
1 2
2 3
3 4
4 5
```
### 输出
```
5```

## 样例 #2
### 输入
```
7
38 -29 87 93 39 28 -55
1 2
2 5
3 2
2 4
1 7
7 6
```
### 输出
```
93```

## 样例 #3
### 输入
```
5
1 2 7 6 7
1 5
5 3
3 4
2 4
```
### 输出
```
8```

### 算法分类
无算法分类

### 题解综合分析与结论
这些题解主要围绕如何确定入侵所有银行所需电脑的最小强度展开。有的题解通过暴力枚举结合线段树维护来解决，有的则是通过对各种情况进行细致分析得出答案的取值规律从而求解。不同题解在思路清晰度、代码复杂度和优化程度上存在差异。

### 所选的题解
- **作者：Zq_water (赞：2)  星级：4星**
    - **关键亮点**：采用正难则反的思路，将原操作转化为对根节点权值 -2，其儿子节点 -1 的操作，利用线段树维护，时间复杂度优化到 \(O(n\log n)\)，思路独特且高效。
    - **核心代码片段**：
```cpp
// 线段树构建
void build(int u,int l,int r){
    t[u].l=l,t[u].r=r;
    if(l==r){t[u].maxx=a[l];return;}
    int mid=l+r>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    pushup(u);
}
// 线段树单点修改
void modify(int u,int pos,int k){
    if(t[u].l==t[u].r){
        t[u].maxx+=k;
        return;
    }
    int mid=t[u].l+t[u].r>>1;
    if(pos<=mid)modify(ls,pos,k);
    else modify(rs,pos,k);
    pushup(u);
}
// 主函数中核心操作
for(int i=1;i<=n;i++){
    modify(1,i,-2);
    for(int v:g[i])modify(1,v,-1);
    ans=min(ans,t[1].maxx);
    for(int v:g[i])modify(1,v,1);
    modify(1,i,2);
}
```
核心实现思想：先对所有点权值加2后构建线段树，枚举每个点作为根节点，对根节点及相邻节点进行权值修改，通过线段树查询当前全局最大值，取所有枚举情况的最小值作为答案，操作完成后恢复权值以便下次枚举。
- **作者：littleseven (赞：1)  星级：4星**
    - **关键亮点**：通过对不同情况的细致分析，总结出答案仅有 \(ans = val_{max}\)、\(ans = val_{max} + 1\)、\(ans = val_{max} + 2\) 三种情况，并针对 \(val = val_{max}\) 的点个数不同分别讨论，逻辑清晰。
    - **核心代码片段**：
```cpp
if (totmx == 1) {
    if (totse == 0) {
        cout << mx << endl;
        return 0;
    }
    else {
        int now = 0;
        for (int i = head[tmp]; i; i = nxt[i]) {
            if (val[to[i]] == mx - 1) {
                now ++ ;
            }
        }
        if (now == totse) {
            cout << mx << endl;
            return 0;
        }
        else {
            cout << mx + 1 << endl;
            return 0;
        }
    }
}
if (totmx >= 2) {
    for (int i = 1; i <= n; i ++ ) {
        int cnt = 0;
        for (int j = head[i]; j; j = nxt[j]) {
            int now = to[j];
            if (val[now] == mx) {
                cnt ++ ;
            }
        }
        if (val[i]!= mx && cnt == totmx) {
            cout << mx + 1 << endl;
            return 0;
        }
        if (val[i] == mx && cnt == totmx - 1) {
            cout << mx + 1 << endl;
            return 0;
        }
    }
}
cout << mx + 2 << endl;
```
核心实现思想：先统计最大值 \(mx\) 及其出现次数 \(totmx\)，次大值（\(mx - 1\)）出现次数 \(totse\)。根据 \(totmx\) 的值分情况讨论，若 \(totmx == 1\)，再看 \(totse\) 的情况及与最大值点的连接关系确定答案；若 \(totmx >= 2\)，检查所有最大值点是否满足特定连接关系来确定答案。

### 最优关键思路或技巧
- **正难则反思路**：如Zq_water的题解，将复杂的原操作转化为更易处理的反向操作，结合线段树优化维护，降低时间复杂度。
- **情况分析归纳**：littleseven通过对不同情况的全面分析，总结出简洁的答案取值规律，直接根据条件判断得出答案，避免复杂的模拟过程。

### 拓展思路
此类题目属于树形结构上的操作与最值求解问题，类似的题目通常围绕树的结构特性和节点操作展开。常见的套路包括对树的遍历方式选择（如DFS、BFS），利用数据结构（如线段树、树状数组）优化对节点信息的维护和查询，以及对各种情况进行细致分类讨论。

### 相似知识点洛谷题目
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及树的遍历和节点状态设置，与本题在树形结构操作上有相似之处。
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：在树上进行决策和最值求解，与本题在树形结构上求最值思路类似。
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：通过树形DP解决树上的选择问题，和本题在树形结构上进行操作决策有相似知识点。 

---
处理用时：72.81秒