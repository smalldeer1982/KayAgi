# Cleaning Robots

## 题目描述

The new ICPC town has $ N $ junctions (numbered from $ 1 $ to $ N $ ) which are connected by $ N-1 $ roads. It is possible from one junction to go to any other junctions by going through one or more roads. To make sure all the junctions are well-maintained, the government environment agency is planning to deploy their newest advanced cleaning robots. In addition to its cleaning ability, each robot is also equipped with a movement ability such that it can move from one junction to any other junctions connected by roads. However, as you might have guessed, such robots are not cheap. Therefore, the agency is considering the following deployment plan.

Let $ T_k $ be the set of junctions which should be cleaned by the $ k^{th} $ robot (also known as, the robot's task), and $ |T_k| \ge 1 $ be the number of junctions in $ T_k $ . The junctions in $ T_k $ form a path, i.e. there exists a sequence of $ v_1, v_2, \dots, v_{|T_k|} $ where $ v_i \in T_k $ and $ v_i \neq v_j $ for all $ i \neq j $ such that each adjacent junction in this sequence is connected by a road. The union of $ T $ for all robots is equal to the set of all junctions in ICPC town. On the other hand, no two robots share a common junction, i.e. $ T_i \cap T_j = \emptyset $ if $ i \neq j $ .

To avoid complaints from citizens for an inefficient operation, the deployment plan should be irreducible; in other words, there should be no two robots, $ i $ and $ j $ , such that $ T_i \cup T_j $ forms a (longer) path. Note that the agency does not care whether the number of robots being used is minimized as long as all the tasks are irreducible.

Your task in this problem is to count the number of feasible deployment plan given the town's layout. A plan is feasible if and only if it satisfies all the above-mentioned requirements.

For example, let $ N = 6 $ and the roads are $ \{(1,3),(2,3),(3,4),(4,5),(4,6)\} $ . There are $ 5 $ feasible deployment plans as shown in the following figure.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1252B/adc19c47bb7f0ca12ae9e18a1b13130ee5669936.png)

- The first plan uses $ 2 $ robots (labeled as A and B in the figure) to clean $ \{1,2,3\} $ and $ \{4,5,6\} $ .
- The second plan uses $ 3 $ robots (labeled as A, B, and C in the figure) to clean $ \{1,3,4,6\} $ , $ \{2\} $ , and $ \{5\} $ .
- The third plan uses $ 3 $ robots to clean $ \{1,3,4,5\} $ , $ \{2\} $ , and $ \{6\} $ .
- The fourth plan uses $ 3 $ robots to clean $ \{1\} $ , $ \{2,3,4,6\} $ , and $ \{5\} $ .
- The fifth plan uses $ 3 $ robots to clean $ \{1\} $ , $ \{2,3,4,5\} $ , and $ \{6\} $ .

 No other plans are feasible in this case. For example, the plan $ \{\{1,3\},\{2\},\{4,5,6\}\} $ is not feasible as the task $ \{1,3\} $ and $ \{2\} $ can be combined into a longer path $ \{1,3,2\} $ . The plan $ \{\{1,2,3,4\},\{5\},\{6\}\} $ is also not feasible as $ \{1,2,3,4\} $ is not a path.

## 说明/提示

Explanation for the sample input/output #1

This is the example from the problem description.

## 样例 #1

### 输入

```
6
1 3
2 3
3 4
4 5
4 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
1 2
2 3
2 4
4 5
```

### 输出

```
3
```

# 题解

## 作者：SofanHe (赞：5)

[通过证明](http://codeforces.com/contest/1252/submission/67182219)

从自己的博客搬运一篇[题解](https://blog.csdn.net/H_18763886211/article/details/103603762)

# [Codeforces 1252B](http://codeforces.com/problemset/problem/1252/B)

Tag：树上DP，数学优化，图论，动态规划

---
## 题目分析
### 题目大意
给定一个**无向树**，求任意两个路径的终点都不向连的路径集**个数**。其中点数小于等于1e5

### 做法猜测
树上的问题，还是计数，复杂度要求在O(nlogn)之内，直接考虑树上DP。

---

## 动态规划设计
### 前置说明
记当前节点为 $u$，子节点为$v_{i}$
使用的编译指令为
```cpp
g++ filename.cpp -o filename.exe -O2 -std=c++11
```
预处理头文件与常量定义为
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+17,M = 3e5+17;
```
存图方式为链式前向星，其中存图的代码可以参考下述
```cpp
int n,tails,fr[N],to[M],nxt[M];
void add(int f,int t){
	nxt[++tails] = fr[f];
	fr[f] = tails;
	to[tails] = t;
	return;
}
```
遍历的方式为
```cpp
void DFS(int u,int fa){
	for(int zj=fr[u],v;zj;zj=nxt[zj]){
		if((v=to[zj]) == fa)	continue;
		DFS(v,start);
	}
	return;
}
```
### 状态说明
记本节点为节点 $u$，其子节点为 $v$。
记每个节点存在的下列状态分别为$0/1/2$
同时使用$F[N][3]$来记录每个状态
```cpp
long long MOD = 1e9+7,F[N][4];
```

~~不要问我怎么出来的这个状态，Three Hours淦出来的~~

**“自闭”状态**
定义 $u$ 节点已经连接向两个子节点，且其他节点均处在满足题意的状态为状态0。

**“不满”状态**
定义 $u$ 节点已经连接了不足两个子节点；且如果 $u$ 节点连向父节点后，以 $u$ 为根的树满足题目中的要求的状态为状态1。
简单来说，就是如果 $u$ 与其父节点连接时满足题意的状态。

**“自信”状态**
定义 $u$ 节点在不考虑父节点的情况下，满足题意的状态为状态2。

### 状态分析
#### 状态转移方程的确立

**“自闭”状态**

一个“自闭”状态的形成一定有两个“不满”状态影响，且其他子节点都在“自信”状态中。

于是我们得到了初步的计算式：

$F[u][0] = \sum_{v1,v2 \in son_{u} , v1 \ne v2} (F[v1][1] * F[v2][1]  * \prod_{v \in son_{u},v \ne v1, v \ne v2}F[v][2])$

**“不满”状态**
一个“不满”状态可能的组成情况有下列两种：

 - $u$ 与一个 $v$ 的“不满”状态相连接，其它节点均处在“自信”状态。
 - $u$ 自成一体，所有 $v$ 都处在“自闭”状态。

这个状态需要说明一下，如果有 $v$ 不处在“自闭”状态，则即使 $u$ 与其父节点相连的情况下，这个子树$v$一定与 $u$ 各处在一个路径的端点，而此两点相连，不满足题意。因此所有 $v$ 均应当处在“自闭”状态。

$F[u][1] = \sum_{v1 \in son_{u}}(F[v1][1]* \prod_{v \in son_{u},v \ne v1}F[v][2]) + \prod_{v \in son_{u}}F[v][0]$

**“自信”状态**

一个“自信”状态的构成，也可以分为两部分。

 - 这个节点处在“自闭”状态。
 - 这个节点处在所有 $v$ 都“自闭”的状态。
 - 这个节点处在与一个“不满”子节点相连，其他子节点均“自闭”的状态

$F[u][2] = F[u][0] + \prod_{v \in son_{u}}F[v][0] + \sum_{v1 \in son_{u}}(F[v1][1] *\prod_{v \in son_{u},v \ne v1}F[v][0])$

##### 初始状态转移的时空复杂度
##### 时间复杂度
对于每一个节点，我们朴素计算每个单独的计算单元。

$\prod_{v \in son_{u}}F[v][2]$	

$\prod_{v \in son_{u}}F[v][0]$

时间复杂度为 $O(son_{u})$

然后枚举 $v1$，计算出

$\sum_{v1 \in son_{u}}(F[v1][1] *\prod_{v \in son_{u},v \ne v1}F[v][0])$

$\sum_{v1 \in son_{u}}(F[v1][1]* \prod_{v \in son_{u},v \ne v1}F[v][2])$

时间复杂度为 $O(son_{u})$

枚举 $v1$ 的同时，枚举 $v2$，计算

$\sum_{v1,v2 \in son_{u} , v1 \ne v2} (F[v1][1] * F[v2][1]  * \prod_{v \in son_{u},v \ne v1, v \ne v2}F[v][2])$

时间复杂度$O(son_{u}^{2})$

总时间复杂度 $O(n^{2})$
显然超时。
##### 空间复杂度
~~So easy,I won't want to do this~~

---
## 动态规划方程的一种优化方式
### 基本思想
借鉴之前优化连乘算式的方法，我们考虑一个一个加入新的元素，并计算新加入元素的贡献。

### 举个例子
##### 目标方程

$\sum_{v1 \in son_{u}}(F[v1][1] *\prod_{v \in son_{u},v \ne v1}F[v][0])$

##### 变量声明
$v0$ 为新遍历到的节点
$son1_{u}$ 为在 $v0$ 前进入的子节点集合

##### 优化分析
我们假设新加入了一个子节点 $v0$

那么考虑 $v0$ 对在上式中 $v1$ 取其它节点的贡献

$F[v0][0] * \sum_{v2 \in son1_{u}}(F[v2][1]*\prod_{v \in son1_{u},v \ne v2}F[v][0])$

考虑 $v0$ 对上式中 $v1$ 取 $v0$ 时的贡献

$F[v0][1] *\prod_{v2 \in son1_{u}}F[v2][0]$

将以上两个式子相加即可得到加入一个节点 $v0$ 后的结果。

$F[v0][0] * \sum_{v2 \in son1_{u}}(F[v2][1]*\prod_{v \in son1_{u},v \ne v2}F[v][0]) + F[v0][1] *\prod_{v2 \in son1_{u}}F[v2][0])$

此时我们发现一个**重要**的事情，即上面

$\sum_{v2 \in son1_{u}}(F[v2][1]*\prod_{v \in son1_{u},v \ne v2}F[v][0])$

不正是我们没有加入 $v0$ 时的结果吗？

所以我们不妨设计这样两个东西

$s1 = \sum_{v2 \in son1_{u}}(F[v2][1]*\prod_{v \in son1_{u},v \ne v2}F[v][0])$

$s2 = \prod_{v \in son1_{u}}F[v][0]$

#### 代码实现

于是在代码中，我们就可以这样维护这两个变量

```cpp
void DFS(int u,int fa){
	long long s1=0,s2=1;//Notice: s2 = 1
	for(int zj=fr[u],v;zj;zj=nxt[zj]){
		if((v=to[zj])==fa)	continue;
		DFS(v,u);
		s1 = (s1*F[v][0] + s2*F[v][1])%MOD;
		s2 = (s2*F[v][0])%MOD;
	}
}
```

#### 时空复杂度
**时间复杂度**

由于每次遍历到新的子节点都做了常数次操作，因此我们

### 推广一下

#### 简单改名
我们通过改改名字就能实现下面这个式子

$\sum_{v1 \in son_{u}}(F[v1][1] *\prod_{v \in son_{u},v \ne v1}F[v][2])$

记住这个式子????叫做 $w2$
记住这个式子????叫做 $w2$
记住这个式子????叫做 $w2$

这么简单我就直接上代码了

```cpp
void DFS(int u,int fa){
	long long w2=0,w3=1,s1=0,s2=1;
	for(int zj=fr[u],v;zj;zj=nxt[zj]){
		if((v=to[zj])==fa)	continue;
		else				DFS(v,u);
		w2 = (w2*F[v][2] + w3*F[v][1])%MOD;
		w3 = (w3*F[v][2])%MOD;
		s1 = (s1*F[v][0] + s2*F[v][1])%MOD;
		s2 = (s2*F[v][0])%MOD;
	}
}
```

#### 双变量枚举
做完上面的这些工作之后，我们就剩下一个式子没有处理了。

~~先把它给供起来，真的脑筋急转弯~~

$\sum_{v1,v2 \in son_{u} , v1 \ne v2} (F[v1][1] * F[v2][1]  * \prod_{v \in son_{u},v \ne v1, v \ne v2}F[v][2])$

此处建议大家手动推一下这个式子的优化。

还是老规矩，考虑新加入节点对原先节点的影响。

##### 符号说明
$v0$ 新加入节点
$son1_{u}$ 在 $v0$ 之前加入的节点

##### 开工动手
既然原始式子中取了两个变量，那我们不妨假设$v1 < v2$
如果原始式子中的 $v2$ 取 $v0$ 的话，我们考虑其对答案更新的贡献

$F[v0][1] * \sum_{v3 \in son1_{u}} (F[v3][1]  * \prod_{v \in son1_{u},v \ne v3}F[v][2])$

如果原始式子中 $v1$ 与 $v2$ 均不取 $v0$ 的话，考虑其对答案更新的贡献

$F[v0][2] * \sum_{v1,v2 \in son1_{u} , v1 \ne v2} (F[v1][1] * F[v2][1]  * \prod_{v \in son1_{u},v \ne v1, v \ne v2}F[v][2])$

##### 奇妙发现1
我们看下面这个式子跟 $w2$ 有啥关系吗？

$F[v0][1] * \sum_{v3 \in son1_{u}} (F[v3][1]  * \prod_{v \in son1_{u},v \ne v3}F[v][2])$

嘻嘻嘻，相信你也发现了，上面这个式子等价于下面的这个

$F[v0][1] * \sum_{v3 \in son1_{u}} (F[v3][1]  * \prod_{v \in son1_{u},v \ne v3}F[v][2]) \iff F[v0][1]*w2$

##### 奇妙发现2
我们看下面这个式子是什么

$\sum_{v1,v2 \in son1_{u} , v1 \ne v2} (F[v1][1] * F[v2][1]  * \prod_{v \in son1_{u},v \ne v1, v \ne v2}F[v][2])$

这不正是在 $v0$ 之前的所有点的结果吗？

我们再拿个 $w1$ 来维护这个结果，于是可以得到下段程序
```cpp
void DFS(int u,int fa){
	long long w1=0,w2=0,w3=1,s1=0,s2=1;
	for(int zj=fr[u],v;zj;zj=nxt[zj]){
		if((v=to[zj])==fa)	continue;
		else				DFS(v,u);
		w1 = (w1*F[v][2] + w2*F[v][1])%MOD;
		w2 = (w2*F[v][2] + w3*F[v][1])%MOD;
		w3 = (w3*F[v][2])%MOD;
		s1 = (s1*F[v][0] + s2*F[v][1])%MOD;
		s2 = (s2*F[v][0])%MOD;
	}
}
```

### 合并计算结果
由上面式子

$F[u][0] = \sum_{v1,v2 \in son_{u} , v1 \ne v2} (F[v1][1] * F[v2][1]  * \prod_{v \in son_{u},v \ne v1, v \ne v2}F[v][2])$

$F[u][1] = \sum_{v1 \in son_{u}}(F[v1][1]* \prod_{v \in son_{u},v \ne v1}F[v][2]) + \prod_{v \in son_{u}}F[v][0]$

$F[u][2] = F[u][0] + \prod_{v \in son_{u}}F[v][0] + \sum_{v1 \in son_{u}}(F[v1][1] *\prod_{v \in son_{u},v \ne v1}F[v][0])$

可以得到下面这段代码
```cpp
void DFS(int u,int fa){
	long long w1=0,w2=0,w3=1,s1=0,s2=1;
	for(int zj=fr[u],v;zj;zj=nxt[zj]){
		if((v=to[zj])==fa)	continue;
		else				DFS(v,u);
		w1 = (w1*F[v][2] + w2*F[v][1])%MOD;
		w2 = (w2*F[v][2] + w3*F[v][1])%MOD;
		w3 = (w3*F[v][2])%MOD;
		s1 = (s1*F[v][0] + s2*F[v][1])%MOD;
		s2 = (s2*F[v][0])%MOD;
	}
	F[u][0] = w1;	
	F[u][1] = (w2 + s2)%MOD;;
	F[u][2] = (F[u][0] + s1 + s2)%MOD;
}
```

---

## 完整代码
~~主函数那么简单，我就不用说明了吧~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+17,M = 3e5+17;
long long MOD = 1e9+7,F[N][4];
int n,tails,fr[N],to[M],nxt[M];
void add(int f,int t){
	nxt[++tails] = fr[f];
	fr[f] = tails;
	to[tails] = t;
}
void DFS(int u,int fa){
	long long w1=0,w2=0,w3=1,s1=0,s2=1;
	for(int zj=fr[u],v;zj;zj=nxt[zj]){
		if((v=to[zj])==fa)	continue;
		else				DFS(v,u);
		w1 = (w1*F[v][2] + w2*F[v][1])%MOD;
		w2 = (w2*F[v][2] + w3*F[v][1])%MOD;
		w3 = (w3*F[v][2])%MOD;
		s1 = (s1*F[v][0] + s2*F[v][1])%MOD;
		s2 = (s2*F[v][0])%MOD;
	}
	F[u][0] = w1;	
	F[u][1] = (w2 + s2)%MOD;;
	F[u][2] = (F[u][0] + s1 + s2)%MOD;
}
int main(){
	scanf("%d",&n);
	for(int i=1,p1,p2;i<n;++i){
		scanf("%d %d",&p1,&p2);
		add(p1,p2),add(p2,p1);
	}
	DFS(1,0),printf("%I64d",F[1][2]);
	return 0;
}
```

---

## 作者：灵梦 (赞：2)

如果题解页面公式显示错误，请[在博客中查看](https://www.luogu.com.cn/blog/Hakurei-Reimu/solution-cf1252b) .

对于节点 $u$，它可以向它的儿子发最多 $2$ 条边。同时，它的连边有三种情况：

- 向它的儿子一共发了恰好 $2$ 条边，此时它的父亲不能向它连边（不可选）。将方案数记为 $f_{u,0}$。
- 向它的儿子一共发了 $0$ 或 $1$ 条边，此时它的父亲可以不向它连边（可选）。将方案数记为 $f_{u,1}$。
- 向它的儿子一共发了 $0$ 或 $1$ 或 $2$ 条边，且没有连边的儿子不会与它构成链，此时它的父亲可以不向它连边（可不选）。将方案数记为 $f_{u,2}$。

对以上三种情况分别考虑转移。如果是第一种的情况，则 $u$ 连边的儿子必须可选，没有连边的儿子必须可不选：
$$
f_{u,0}=\sum_{x,y\in son_u\wedge x\neq y}f_{x,1}f_{y,1}\prod_{v\in son_u\wedge v\neq x,y}f_{v,2}
$$
如果是第二种情况，若 $u$ 发了 $0$ 条边，则它的所有儿子都必须**不可选**，因为如果有一个儿子可选则会与 $u$ 构成链，且无论父亲怎么决策都无法消除影响，所以这样就会直接不合法；若 $u$ 发了 $1$ 条边，则 $u$ 连边的儿子必须可选，没有连边的儿子必须可不选：
$$
f_{u,1}=\prod_{v\in son_u}f_{v,0}+\sum_{x\in son_u}f_{x,1}\prod_{v\in son_u\wedge v\neq x}f_{v,2}
$$
如果是第三种情况，若 $u$ 发了 $0$ 条边，则同理它的所有儿子都必须不可选；若 $u$ 发了 $1$ 条边，则 $u$ 连边的儿子必须可选，没有连边的儿子必须**不可选**，因为如果有一棵儿子可选则会与 $u$ 构成链，那么 $u$ 的父亲必须向 $u$ 连边（$u$ 必须选），违反了状态的定义；若 $u$ 发了 $2$ 条边，则与第一种情况相同：
$$
f_{u,2}=f_{u,0}+\prod_{v\in son_u}f_{v,0}+\sum_{x\in son_u}f_{x,1}\prod_{v\in son_u\wedge v\neq x}f_{v,0}
$$
假设我们以 $1$ 为根，则最终的答案为 $f_{1,2}$。

考虑 DP，直接转移是 $O(n^3)$ 的，但可以将其优化。下面是我的优化方式，以第一种情况的转移为例：
$$
f_{u,0}=\sum_{x,y\in son_u\wedge x\neq y}f_{x,1}f_{y,1}\prod_{v\in son_u\wedge v\neq x,y}f_{v,2}
$$

$$
=\sum_{x,y\in son_u\wedge x\neq y}\frac{f_{x,1}f_{y,1}}{f_{x,2}f_{x,2}}\prod_{v\in son_u}f_{v,2}
$$

$$
=\frac{1}{2}\left[\left(\sum_{x\in son_u}\frac{f_{x,1}}{f_{x,2}}\right)^2-\sum_{x\in son_u}\left(\frac{f_{x,1}}{f_{x,2}}\right)^2\right]\prod_{v\in son_u}f_{v,2}
$$

其他两种情况的优化比较容易，在这里就省略了。

还有个问题是 $0$ 在模意义下无逆元，因此要特殊处理。具体就是记下 $0$ 的位置再讨论讨论，同样不难处理。

时间复杂度为 $O(n\log mod)$，这里的 $\log$ 是求逆的复杂度。实际上如果用前缀和优化可以做到 $O(n)$。

---

## 作者：InQueue (赞：1)

树上 dp。

（指定 $1$ 为根结点，下文中“叶结点”表示度数为 $1$ 的非根结点。）

### 状态定义

对每个 $1\le i\le n$ 有 $dp_{i,0/1/2}$：

- $dp_{i,0}$ 表示 $i$ 子树内路径合法，且点 $i$ 处无路径可向上连接的方案数。如图：（打 √ 代表选择这条边组成路径）

![](https://cdn.luogu.com.cn/upload/image_hosting/1lfq2c24.png)

图示方案可对 $dp_{2,0}$ 贡献 $1$。

- $dp_{i,1}$ 表示 $i$ 子树内路径合法，且点 $i$ 处有路径向上连接的方案数。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rp427fph.png)

图示方案可对 $dp_{2,1}$ 贡献 $1$。

- $$dp_{i,2}$$ 表示点 $i$ 处有路径向上连接，且选择向上连接后子树内路径合法的方案数。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tqhlcjx0.png)

图示方案可对 $dp_{2,2}$ 贡献 $1$。

注意：$dp_{i,2}$ 的方案包含 $dp_{i,1}$ 的方案。

### 边界
对于所有叶结点 $i$，$dp_{i,0}=0,dp_{i,1} = dp_{i,2} = 1$。

### 转移

$$\begin{aligned}

dp_{x,0} &= \sum_{i,j\in son(x),i<j}dp_{i,2}dp_{j,2}\prod_{k\in son(x),k\neq i,k\neq j}(dp_{k,0}+dp_{k,1})

\\ &= \sum_{i\in son(x)}dp_{i,2}\left(\prod_{j\in son(x),j<i}(dp_{j,0}+dp_{j,1})\right)\sum_{j\in son(x),j>i}dp_{j,2}\prod_{k\in son(x),k>i,k\neq j}(dp_{k,0}+dp_{k,1})

\\ dp_{x,1} &= \left(\sum_{i\in son(x)}dp_{i,2}\prod_{k\in son(x),k\neq i}dp_{k,0} \right)+\left(\prod_{i\in son(x)}dp_{i,0}\right)

\\ dp_{x,2} &= \left(\sum_{i\in son(x)}dp_{i,2}\prod_{k\in son(x),k\neq i}(dp_{k,0}+dp_{k,1})\right)+\left(\prod_{i\in son(x)}dp_{i,0}\right)

\end{aligned}$$

对于 $dp_{x,0}$，枚举两条在 $x$ 处连接的路径，计算贡献。实现时倒序枚举 $i$，前半部分预处理前缀积后好算。后半部分动态维护。具体地，维护一个 $sum$ 表示第二个 $\sum$ 的结果，在 $i$ 处更新完答案后，执行 $sum\gets sum\times (dp_{i,0}+dp_{i,1})+dp_{i,2}\prod_{j\in son(x),j>i}(dp_{j,0}+dp_{j,1})$。预处理后缀积其也是好算的。

对于 $dp_{x,1/2}$，前半部分表示 $x$ 连接了某个子树的路径。后半部分表示 $x$ 自己新建一条路径，此时所有子树不能有可向上连接的路径。预处理前后缀积后计算是容易的。

### 答案

$$ANS = dp_{1,0} + dp_{1,1}$$

[CF 提交记录。](https://codeforces.com/contest/1252/submission/300783558)

---

## 作者：bsdsdb (赞：1)

题意：求有多少种用链剖分一个树的方式，使得没有两个链能直接合并成一个更大的。

树上计数那基本上就是树形 dp 了。设：

- $\mathrm{dp}_{x,0}$ 表示 $x$ 是其所属链的终点，且 $x$ 不往上连也合法的情况数；
- $\mathrm{dp}_{x,1}$ 表示 $x$ 不是其所属链的终点的情况数；
- $\mathrm{dp}_{x,2}$ 表示 $x$ 是其所属链的终点，但 $x$ 不往上连就不合法的情况数。

如这棵树：

```text
..1....
./.\...
2...3..
.../.\.
..4...5
```

$\mathrm{dp}_{1,0}$ 代表 $\{\{\{1,2\},\{4,3,5\}\}\}$，$\mathrm{dp}_{1,1}$ 代表 $\{\{\{2,1,3,5\},\{4\}\},\{\{2,1,3,4\},\{5\}\}\}$，$\mathrm{dp}_{1,2}$ 代表 $\{\{\{1,3,4\},\{2\},\{5\}\},\{\{\{1,3,5\},\{2\},\{4\}\}\}$。

转移分为四种情况：

- $x$ 不往下连，此时下面的都要是 $\mathrm{dp}_{i,1}$ 的情况；
- $x$ 往下连一个，子树内合法，此时连的要是个 0 / 2，其余都是 1；
- $x$ 往下连一个，子树内不合法，此时连的要是 0 / 2，其余都是 0 / 1，但不能全是 1；
- $x$ 往下连两个，此时要连两个 0 / 2，其余是 0 / 1。

分别有转移：

$$
\mathrm{dp}_{x,0}\gets\prod_i\mathrm{dp}_{i,1}\\
\mathrm{dp}_{x,0}\gets\sum_i(\mathrm{dp}_{i,0}+\mathrm{dp}_{i,2})\prod_{j\neq i}\mathrm{dp}_{j,1}\\
\mathrm{dp}_{x,2}\gets\sum_i(\mathrm{dp}_{i,0}+\mathrm{dp}_{i,2})\left(\prod_{j\neq i}(\mathrm{dp}_{j,0}+\mathrm{dp}_{j,1})-\prod_{j\neq i}\mathrm{dp}_{j,1}\right)\\
\mathrm{dp}_{x,1}\gets\sum_{i\neq j}(\mathrm{dp}_{i,0}+\mathrm{dp}_{i,2})(\mathrm{dp}_{j,0}+\mathrm{dp}_{j,2})\prod_{k\neq i,j}(\mathrm{dp}_{k,0}+\mathrm{dp}_{k,1})
$$

（此处 $\gets$ 对应编程语言中的 `+=`）

前三个都是很好解决的，对于计算 $\prod_{j\neq i}$ 的情况用个前缀积和后缀积的情况。为什么不整体积再除以一个 $i$ 的？因为可能除以 $0$。重点是第四种情况。我们可以使用背包来优化。具体的，设 $s_{x,i}$ 代表 $x$ 的第 $i$ 个子结点，$f_{w,0/1/2}$ 表示考虑了前 $w$ 个子结点，没有式中的 $i,j$ / 有 $i$ 没 $j$ / 有 $i,j$ 的 $\mathrm{dp}_{x,1}$。有转移：

$$
t:=s_{x,w}\\
p:=\prod_{u<w}(\mathrm{dp}_{u,0}+\mathrm{dp}_{u,1})\\
f_{w,0}\gets f_{w-1,0}(\mathrm{dp}_{t,0}+\mathrm{dp}_{t,1})\\
f_{w,1}\gets f_{w-1,1}(\mathrm{dp}_{t,0}+\mathrm{dp}_{t,1})+f_{w-1,0}(\mathrm{dp}_{t,0}+\mathrm{dp}_{t,2})\\
f_{w,2}\gets f_{w-1,2}(\mathrm{dp}_{t,0}+\mathrm{dp}_{t,1})+f_{w-1,1}(\mathrm{dp}_{t,0}+\mathrm{dp}_{t,2})
$$

就做完了。如果你愿意，也可以给第二、三种情况套上背包，还可以用滚动数组，但空间和时间复杂度终究是 $\Omicron(n)$。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace modint {
    const ll MOD = 1e9 + 7;
    struct modint {
        ll val, mod;
        void setmod(ll x) {
            mod = x;
        }
        explicit operator ll() {
            return val;
        }
        modint() {
            val = 0, mod = MOD;
        }
        modint(ll v, ll m = MOD) {
            if (m == 1) {
                cus_throw("init modint without mod");
            }
            v %= m;
            if (v < 0) {
                v += m;
            }
            val = v;
            mod = m;
        }
    };
    #define chkmod(x, y) if (x.mod != y.mod) cus_throw("mod isn't the same")
    modint operator+(modint x, modint y) {
        chkmod(x, y);
        return modint(x.val + y.val, x.mod);
    }
    modint operator-(modint x, modint y) {
        chkmod(x, y);
        return modint(x.val - y.val, x.mod);
    }
    modint operator*(modint x, modint y) {
        chkmod(x, y);
        return modint(__int128(1) * x.val * y.val, x.mod);
    }
    modint qpow(modint x, ll y) {
        if (!y) {
            return modint(1, x.mod);
        } else if (y & 1) {
            return x * qpow(x, y ^ 1);
        } else {
            return qpow(x * x, y >> 1);
        }
    }
    modint inv(modint x) {
        return qpow(x, x.mod - 2);
    }
    modint operator/(modint x, modint y) {
        chkmod(x, y);
        if (ll(y) == 0) {
            cus_throw("modint divide by 0");
        }
        return x * inv(y);
    }
    modint operator+=(modint& x, modint y) {
        return x = x + y;
    }
    modint operator-=(modint& x, modint y) {
        return x = x - y;
    }
    modint operator*=(modint& x, modint y) {
        return x = x * y;
    }
    modint operator/=(modint& x, modint y) {
        return x = x / y;
    }
    bool operator==(modint x, modint y) {
        chkmod(x, y);
        return x.val == y.val;
    }
}

const ll MAXN = 2e5 + 5, ISTOP = 0, ISLCA = 1, MUSTUP = 2;

modint::modint dp[MAXN][3], d21[MAXN];
ll n;
vector<ll> e[MAXN];

void srh(ll x, ll pr) {
//	cerr << "srh " << x << ' ' << pr << endl;
	if (e[x].size() == bool(pr)) {
		dp[x][ISTOP] = 1;
		dp[x][ISLCA] = 0;
		dp[x][MUSTUP] = 0;
//		for (ll i : {0, 1, 2}) {
//			cerr << "dp[" << x << "][" << i << "]=" << ll(dp[x][i]) << endl;
//		}
		return;
	}
	modint::modint prod1 = 1;
	for (ll i : e[x]) {
		if (i == pr) continue;
		srh(i, x);
		prod1 *= dp[i][1];
	}
//	cerr << "cal " << x << ' ' << pr << endl;
	for (ll i = 0; i < e[x].size(); ++i) {
		if (e[x][i] == pr) {
			swap(e[x][i], e[x][e[x].size() - 1]);
		}
	}
	// 2
//	cerr << 2 << endl;
	modint::modint prep = 1;
	for (ll i : e[x]) {
		if (i == pr) continue;
		dp[x][0] *= dp[i][1];
		dp[x][0] += prep * (dp[i][0] + dp[i][2]);
		prep *= dp[i][1];
	}
	// 1
//	cerr << 1 << endl;
	dp[x][0] += prod1;
	// 3
//	cerr << 3 << endl;
	prep = 1;
	modint::modint d31 = 0, d32 = 0;
	for (ll i : e[x]) {
		if (i == pr) continue;
		d31 *= dp[i][1] + dp[i][0];
		d31 += prep * (dp[i][0] + dp[i][2]);
		prep *= (dp[i][1] + dp[i][0]);
	}
	prep = 1;
	for (ll i : e[x]) {
		if (i == pr) continue;
		d32 *= dp[i][1];
		d32 += prep * (dp[i][0] + dp[i][2]);
		prep *= dp[i][1];
	}
	dp[x][2] = d31 - d32;
	if (e[x].size() - bool(pr) == 1) {
		dp[x][2] = 0;
	}
	// 4
//	cerr << 4 << endl;
	vector<vector<modint::modint> > bb4;
	bb4.resize(e[x].size());
	for (auto& i : bb4) {
		i.resize(5);
	}
	bb4[0][0] = dp[e[x][0]][1] + dp[e[x][0]][0];
	bb4[0][1] = dp[e[x][0]][0] + dp[e[x][0]][2];
	for (ll i = 1; i < e[x].size() - bool(pr); ++i) {
		ll to = e[x][i];
		bb4[i][0] = bb4[i - 1][0] * (dp[to][1] + dp[to][0]);
		bb4[i][1] = bb4[i - 1][0] * (dp[to][0] + dp[to][2]) + bb4[i - 1][1] * (dp[to][1] + dp[to][0]);
		bb4[i][2] = bb4[i - 1][1] * (dp[to][0] + dp[to][2]) + bb4[i - 1][2] * (dp[to][1] + dp[to][0]);
	}
	dp[x][1] = bb4[e[x].size() - 1 - bool(pr)][2];
//	for (ll i : {0, 1, 2}) {
//		cerr << "dp[" << x << "][" << i << "]=" << ll(dp[x][i]) << endl;
//	}
}

int main() {
	read(n);
	for (ll i = 1, u, v; i < n; ++i) {
		read(u), read(v);
		e[u].empb(v);
		e[v].empb(u);
	}
	srh(1, 0);
	write(ll(dp[1][ISTOP] + dp[1][ISLCA])), enter();
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
求用若干条端点不相邻的路径覆盖一棵树的方案数。
### 分析
容易想到是计数 DP。

于是先抿一下状态，一维肯定不够。然后我们只关心端点是否相邻，所以儿子往父亲转移的时候我们只要看有没有端点必须/可以向上延伸/被截断。

所以状态只需要包含子树根相邻的路径的信息，具体地：$dp_{u,0}$ 表示子树根不是端点的方案数，$dp_{u,1}$ 表示子树根是端点，**可以**被截断或向上延伸的方案数，$dp_{u,2}$ 表示子树根是端点，**必须**向上延伸的方案数。

好的现在可以推柿子了。

$dp_{u,0}$ 是从子树里选两个可以向上延伸的连起来，方案数是 $dp_{v,1}dp_{v,2}$，剩下的儿子方案数就是 $\prod dp_{v,0}dp_{v,1}$。这里乘起来再加起来最好不要用分配律直接算，因为可能出现对 $0$ 求逆元的情况，所以笔者这里就写一个内部的小 dp，同时转移不延伸，选 $1$ 个延伸和选 $2$ 个延伸的方案数。

$dp_{u,1}$ 也差不多，选一个向上延伸，剩下的必须是用 $dp_{v,0}$ 转移。注意可以全都不延伸然后 $u$ 自己作为一个端点。

$dp_{u,2}$ 相当于选一个延伸，其它的儿子方案数 $\prod dp_{v,0}dp_{v,1}$。但是注意不能所有儿子都不是端点否则不符合定义，所以再减掉这部分贡献。把柿子写出来就会发现前面的 dp 已经都求好了。

最终答案就是 $dp_{1,0}+dp_{1,1}$，时间复杂度 $O(n)$。还是一道很值得一做的树形 DP 入门题。
### 代码
其实无敌短。

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
mt19937 rnd(time(NULL));
const int maxn=1e5+5;
const int mod=1e9+7;
int n;
vector<int> T[maxn];
int dp[maxn][3];
void dfs(int u,int f){
	int tn0[3]={1,0,0},tn1[2]={1,0};
	for(int v:T[u]){
		if(v==f) continue;
		dfs(v,u);
		int x=dp[v][0]+dp[v][1],y=dp[v][1]+dp[v][2];
		if(x>=mod) x-=mod;if(y>=mod) y-=mod;
		tn0[2]=(tn0[2]*x+tn0[1]*y)%mod;
		tn0[1]=(tn0[1]*x+tn0[0]*y)%mod;
		tn0[0]=tn0[0]*x%mod;
		tn1[1]=(tn1[1]*dp[v][0]+tn1[0]*y)%mod;
		tn1[0]=tn1[0]*dp[v][0]%mod;
	}
	dp[u][0]=tn0[2];
	dp[u][1]=tn1[0]+tn1[1];
	dp[u][2]=(tn0[1]-tn1[1]+mod)%mod;
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		T[u].eb(v),T[v].eb(u);
	}
	dfs(1,0);
	cout<<(dp[1][0]+dp[1][1])%mod<<'\n';
	return 0;
}
```

---

