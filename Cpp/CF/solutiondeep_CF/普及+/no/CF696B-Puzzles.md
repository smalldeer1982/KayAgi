# 题目信息

# Puzzles

## 题目描述

Barney lives in country USC (United States of Charzeh). USC has $ n $ cities numbered from $ 1 $ through $ n $ and $ n-1 $ roads between them. Cities and roads of USC form a rooted tree (Barney's not sure why it is rooted). Root of the tree is the city number $ 1 $ . Thus if one will start his journey from city $ 1 $ , he can visit any city he wants by following roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696B/ba3e1e6f719802c9fe4b318c8d8513024bc088eb.png)Some girl has stolen Barney's heart, and Barney wants to find her. He starts looking for in the root of the tree and (since he is Barney Stinson not a random guy), he uses a random DFS to search in the cities. A pseudo code of this algorithm is as follows:

```plain
let starting_time be an array of length n
current_time = 0
dfs(v):
	current_time = current_time + 1
	starting_time[v] = current_time
	shuffle children[v] randomly (each permutation with equal possibility)
	// children[v] is vector of children cities of city v
	for u in children[v]:
		dfs(u)
```

As told before, Barney will start his journey in the root of the tree (equivalent to call dfs(1)).

Now Barney needs to pack a backpack and so he wants to know more about his upcoming journey: for every city $ i $ , Barney wants to know the expected value of starting\_time\[i\]. He's a friend of Jon Snow and knows nothing, that's why he asked for your help.

## 样例 #1

### 输入

```
7
1 2 1 1 4 4
```

### 输出

```
1.0 4.0 5.0 3.5 4.5 5.0 5.0 
```

## 样例 #2

### 输入

```
12
1 1 2 2 4 4 3 3 1 10 8
```

### 输出

```
1.0 5.0 5.5 6.5 7.5 8.0 8.0 7.0 7.5 6.5 7.5 8.0 
```

# AI分析结果

### 题目内容
# 谜题

## 题目描述
巴尼生活在 USC 国（查泽合众国）。USC 有 $n$ 个城市，编号从 $1$ 到 $n$，并且它们之间有 $n - 1$ 条道路。USC 的城市和道路构成了一棵有根树（巴尼不确定为什么它是有根的）。树的根是城市编号 $1$。因此，如果一个人从城市 $1$ 出发，他可以通过道路访问任何他想去的城市。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696B/ba3e1e6f719802c9fe4b318c8d8513024bc088eb.png)
某个女孩偷走了巴尼的心，巴尼想找到她。他从树的根开始寻找，并且（因为他是巴尼·斯汀森，不是普通人），他使用随机深度优先搜索（DFS）在城市中搜索。这个算法的伪代码如下：
```plain
let starting_time be an array of length n
current_time = 0
dfs(v):
	current_time = current_time + 1
	starting_time[v] = current_time
	shuffle children[v] randomly (each permutation with equal possibility)
	// children[v] 是城市 v 的子城市向量
	for u in children[v]:
		dfs(u)
```
如前所述，巴尼将从树的根开始他的旅程（相当于调用 dfs(1)）。

现在巴尼需要打包背包，所以他想更多地了解他即将到来的旅程：对于每个城市 $i$，巴尼想知道 starting\_time\[i\] 的期望值。他是琼恩·雪诺的朋友，什么都不知道，这就是为什么他向你求助。

## 样例 #1
### 输入
```
7
1 2 1 1 4 4
```
### 输出
```
1.0 4.0 5.0 3.5 4.5 5.0 5.0 
```

## 样例 #2
### 输入
```
12
1 1 2 2 4 4 3 3 1 10 8
```
### 输出
```
1.0 5.0 5.5 6.5 7.5 8.0 8.0 7.0 7.5 6.5 7.5 8.0 
```

### 算法分类
概率论

### 题解综合分析与结论
这些题解思路基本一致，均通过树形DP来求解每个节点的期望时间戳。核心思路是利用随机DFS的特性，分析每个节点期望时间戳与父节点及兄弟节点子树大小的关系。关键在于证明兄弟节点先于当前节点被搜索的概率为$\frac{1}{2}$，进而得出状态转移方程。各题解在表述和代码实现细节上略有不同，但整体算法框架相同。

### 所选的题解
- **作者：Terac（5星）**
    - **关键亮点**：思路清晰简洁，先明确题意和数据范围，再直接给出状态转移方程的推导过程，代码结构清晰，注释详细。
    - **重点代码核心实现思想**：通过两次DFS，第一次`dfs1`计算每个节点的子树大小`siz`，第二次`dfs2`根据状态转移方程`f[u] = f[fa] + (siz[fa] - siz[u] - 1) * 0.5 + 1`计算每个节点的期望时间戳`f`。
```cpp
void dfs1(int u) {
    siz[u] = 1;
    for(int i = head[u], v; i; i = e[i].nxt) {
        v = e[i].to;
        dfs1(v);
        siz[u] += siz[v];
    }
}
void dfs2(int u, int fa) {
    if(fa) f[u] = f[fa] + (siz[fa] - siz[u] - 1) * 0.5 + 1;
    for(int i = head[u], v; i; i = e[i].nxt) {
        v = e[i].to;
        dfs2(v, u);
    }
}
```
- **作者：daiarineko（4星）**
    - **关键亮点**：对状态转移方程的推导过程阐述详细，从期望时间戳的组成部分逐步分析，最后得出完整的DP方程，代码注释丰富。
    - **重点代码核心实现思想**：与Terac类似，`pre`函数计算子树大小`siz`，`solve`函数依据状态转移方程`dp[v] = dp[u] + 1.0 + (siz[u] - siz[v] - 1) * 0.5`计算期望时间戳`dp`。
```cpp
void pre(int u, int fa) {
    siz[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;
        if (v == fa)
            continue;
        pre(v, u);
        siz[u] += siz[v];
    }
    return;
}
void solve(int u, int fa) {
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;
        if (v == fa)
            continue;
        dp[v] = dp[u] + 1.0 + (siz[u] - siz[v] - 1) * 0.5;
        solve(v, u);
    }
    return;
}
```
- **作者：shiroi（4星）**
    - **关键亮点**：从概率期望DP角度出发，通过分析兄弟节点在DFS序中的排名得出转移方程，代码实现简洁明了。
    - **重点代码核心实现思想**：`dfs`函数计算子树大小`size`和兄弟节点子树大小和`sum`，`dp`函数利用转移方程`ans[y]=ans[x]+1+0.5*sum[y]`计算期望时间戳`ans`。
```cpp
void dfs(int x,int fa) {
    size[x]=1;
    for(int &y : G[x])
        if(y^fa) dfs(y,x),size[x]+=size[y];
    for(int &y : G[x])
        if(y^fa) sum[y]=size[x]-size[y]-1;
}
inline void dp(int x,int fa) {
    for(int &y : G[x])
        if(y^fa) ans[y]=ans[x]+1+0.5*sum[y],dp(y,x);
}
```

### 最优关键思路或技巧
1. **概率分析**：利用随机DFS的特点，通过分析兄弟节点与当前节点的搜索顺序关系，得出兄弟节点先于当前节点被搜索的概率为$\frac{1}{2}$，这是解题的关键。
2. **树形DP**：基于树的结构，通过两次DFS，一次计算子树大小，一次根据状态转移方程计算期望时间戳，将问题转化为树形结构上的动态规划问题。

### 拓展思路
此类题目属于树形结构上的概率期望问题，常见的拓展方向有：
1. **改变树的结构或性质**：如给定带权树，考虑边权对期望的影响。
2. **改变搜索方式**：除了随机DFS，还可能是按特定概率分布搜索等。
3. **增加限制条件**：例如在搜索过程中有某些节点不能访问等。

### 洛谷相似题目推荐
1. [P3802 小魔女帕琪](https://www.luogu.com.cn/problem/P3802)
2. [P4316 绿豆蛙的归宿](https://www.luogu.com.cn/problem/P4316)
3. [P4550 收集邮票](https://www.luogu.com.cn/problem/P4550)

### 个人心得摘录总结
部分作者提到在实现过程中要注意变量名不要使用`size`，因为在某些环境下可能会导致问题，如在OI比赛中可能会爆0。还有作者提到在计算期望时间戳的状态转移方程中，除法运算要注意使用`2.0`而不是`2`，避免出现精度问题。 

---
处理用时：83.72秒