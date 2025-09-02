# Ehab's REAL Number Theory Problem

## 题目描述

You are given an array $ a $ of length $ n $ that has a special condition: every element in this array has at most 7 divisors. Find the length of the shortest non-empty subsequence of this array product of whose elements is a perfect square.

A sequence $ a $ is a subsequence of an array $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements.

## 说明/提示

In the first sample, you can choose a subsequence $ [1] $ .

In the second sample, you can choose a subsequence $ [6, 6] $ .

In the third sample, you can choose a subsequence $ [6, 15, 10] $ .

In the fourth sample, there is no such subsequence.

## 样例 #1

### 输入

```
3
1 4 6```

### 输出

```
1```

## 样例 #2

### 输入

```
4
2 3 6 6```

### 输出

```
2```

## 样例 #3

### 输入

```
3
6 15 10```

### 输出

```
3```

## 样例 #4

### 输入

```
4
2 3 5 7```

### 输出

```
-1```

# 题解

## 作者：George1123 (赞：21)

# Ehab's REAL Number Theory Problem

**[博客中阅读](https://www.cnblogs.com/Wendigo/p/12505876.html)**

**前置知识**

> 质数
> 分解质因数
> 无向无权图最小环<讲>

---

> [Ehab's REAL Number Theory Problem](https://www.luogu.com.cn/problem/CF1325E)/[onCF](https://codeforces.ml/contest/1325/problem/E)

> 给 $n$ 个数 $a_i$（$a_i$ 的因数个数不超过 $7$），求最少选出多少个数，使得乘积为完全平方。无解输出 $-1$。

> 数据范围：$1\le n\le 10^5$，$1\le a_i\le 10^6$。

---

没想到一场普通的 $\texttt{CF}$ 比赛能出出这么~~毒瘤~~好的题！

---

很明显，把每个 $a_i$ 的平方因子除尽后对答案没有影响，所以可以把每个 $a_i$ 的平方因子除尽。

如果某个 $a_i$ 的质因子除尽后为 $1$，**直接选它**便解决了问题。

然后**剩下的质因子的幂次肯定为 $1$**。

而且**最多只有两个质因子**，因为如果 $a_i$ 有三个质因子，按照约数个数定理，$d(a_i)=(1+1)^3=8>7$，**矛盾**。

最后问题简化为，``选最少的数，使乘积包含的质因子幂次都为 2``（可以自己想为什么不需要选幂次为 $4$）。

**过程：**

> $$18=2\times 3^2\to 2$$

---

有一个极其巧妙的方法是**建一个图，节点是质数，然后把每个数转换为它的两个质因子之间的一条边，求最小环**。

如果某个数 $a_i$ 质因数个数为 $1$（不存在为 $0$ 的，因为已经满足方案），把 $1$ 也看做质数节点，连 $1$ 和 $a_i$。

根据环的性质，**每个点的度为 $2$，所以边对应的数的乘积每个质因子幂次都为 $2$**。

边没有长度，是无向边，所以问题又简化为了``求无向无权图最小环``。

**过程：**

$a_i$：``2 3 6 15``。

$$2\to 1\times 2,3\to 1\times 3,6\to 2\times 3,15\to 3\times 5$$

![CF1325E.jpg](https://i.loli.net/2020/03/16/6THemV4WRKzgNUX.jpg)

**最小环为 $(1,2,3)$。**

---

无向无权图最小环使不得 $\texttt{Floyd}$！这里的点数最大约是 $78500$，$\Theta(n^3)$ 能跑到射手座去了。
   
可以枚举起点，然后 $\texttt{Bfs}$，因为问题特殊，所以可以有很大优化。

因为 $1\le a_i\le 10^6$，所以每个 $a_i$ 对应的边不可能连接两个 $>1000$ 的质数。

所以如果有环，那么环必然有一个起点对应的质数 $\in[1,1000]$。

所以可以枚举这个起点 $s$，然后 $\texttt{Bfs}$。

设 $dep_x$ 表示节点 $x$ 的深度，所以 $dep_s=0$。每次 $Bfs$ 前清空。

然后沿着队列顶的点 $x$ 连的边走如果走到一个 $dep$ 未赋值的节点 $to$，就令 $dep_{to}=dep_x+1$。

如果走到一个已经遍历过的点，那么说明这里有一个环，令 $ans=\min\{ans,dep_{to}+dep_x+1\}$。

**$\texttt{Bfs}$ 过程中可以走重复的点，不能走重复的边。**

这里有一个问题：**如何知道这个环是否以 $s$ 为其中一个起点呢？**

答案是**不需要知道**，无论 $s$ 在不在环上都直接 $ans=\min\{ans,dep_{to}+dep_x+1\}$。

因为**如果 $s$ 不在环上，$dep_{to}+dep_x+1$ 肯定比 $s$ 在环上大**（别忘了每个 $s$ 都要枚举过去的啊！）。

时间复杂度 $\Theta(n \sqrt n)$。

**过程：**

![CF1325E.jpg](https://i.loli.net/2020/03/16/6THemV4WRKzgNUX.jpg)

**只展示 $s=1$ 的 $\texttt{Bfs}$ 过程：**

![gif5新文件.gif](https://i.loli.net/2020/03/16/ej7UQENgx4RJIAk.gif)

---

代码实现的时候，可以把质数离散化一下。

## $\texttt{code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define inf 0x3f3f3f3f
#define re register
#define il inline
typedef long long lng;
typedef vector<int> veci;

//&Data
#define N 100000
#define MX 1000000
#define P 78500--->1000000内质数数量
int n,a[N+10];

//&Prime--->筛质数
bitset<MX+10> np;
int p[P+10],ip[MX+10],pcnt,S;
il void Prime(){
	np[1]=true,ip[1]=p[++pcnt]=S=1;
	for(re int i=2;i<=MX;i++){
		if(!np[i]) p[++pcnt]=i,ip[i]=pcnt,S+=(i<=999);
		for(re int j=1;j<=pcnt&&i*p[j]<=MX;j++)
			np[i*p[j]]=1;
	}
}

//&Graph
veci e[P+10];
int E=1,to[(N<<1)+10];//---->同网络流思想，使互为反边的两条边通过^1可得
il void add(re int x,re int y){ //加双向边
	e[x].push_back(++E),to[E]=y;
	e[y].push_back(++E),to[E]=x;
}
il void Add(re int x){ // 把数转换为边
	re int dcnt=0,div[4];
	for(re int j=2;j<=pcnt&&p[j]*p[j]<=x;j++)
		if(x%p[j]==0){
			while(x%(p[j]*p[j])==0) x/=(p[j]*p[j]);
			if(x%p[j]==0) div[++dcnt]=j,x/=p[j]; 
		}
	if(x>1) div[++dcnt]=ip[x],x=1;
	if(dcnt==0) puts("1"),exit(0);
	else if(dcnt==1) add(1,div[1]);
	else add(div[1],div[2]);
}
int sz=inf,q[P+10][2],dep[P+10];
il void Bfs(re int s){ //以s为起点Bfs
	fill(dep+1,dep+P+1,inf);
	re int qcnt=0;
	q[++qcnt][1]=s,dep[s]=0;
	for(re int ft=1;ft<=qcnt;ft++){
		re int x=q[ft][1],f=q[ft][0];
		for(re int i:e[x])if(i!=(f^1)){
			if(dep[to[i]]==inf){
				dep[to[i]]=dep[x]+1;
				q[++qcnt][1]=to[i];
				q[qcnt][0]=i;
			} else sz=min(sz,dep[x]+dep[to[i]]+1); //找到环
		}
	}
}

//&Main
int main(){
	Prime();
	scanf("%d",&n);
	for(re int i=1;i<=n;i++)
		scanf("%d",a+i),Add(a[i]);
	for(re int i=1;i<=S;i++) Bfs(i); //枚举起点
	if(sz==inf) puts("-1");
	else printf("%d\n",sz);
	return 0;
}
```
---

**祝大家学习愉快！**


---

## 作者：Froggy (赞：9)

这场CF就死在了这道题目上面..

---

题面上有句话非常重要：

>每个数的因数个数不超过 $7$

这意味着**每个数最多有2个质因子**。

证明： 如果有3个质因子，根据因数个数定理，这个数的因数个数至少是 $2^3=8$ 个。显然质因子大于3个肯定更不可能。

然后把每个数质因数分解一下，由于题目让求几个数的乘积是完全平方数，那么把分解后的每个质数的指数模2对答案没有任何影响。

这样处理过之后，每个数的形式只有三种情况：

1. $p\times q$
2. $1\times p$
3. $1\times 1$

对于第三种情况，显然答案就是 $1$，直接输出即可。

对于前两种情况，我们可以把 $1$ 和每个质数看成点，那么对于一种情况将 $p$ 和 $q$ 连边，第二种情况将 $1$ 和 $p$ 连边。（边权均为1）

题目就转化为求**这张图的最小环**。

想一想为什么？

环上的每个节点都被乘了两次，所以环上的数乘起来一定是一个完全平方数。

无向图求最小环？Floyed？？

NONONO！

由于边权都为1，所以可以用经典的**bfs求最小环**。

**bfs求最小环**的做法就是存储上一个节点和当前节点，遇到已经bfs过的节点直接更新答案，否则往队列里面扔就好了。

但是时间复杂度是 $\mathcal{O}(n^2)$ 的，过不去qwq。

我们令 $m=\sqrt{\max{a_i}}$

我们发现所有大于 $m$ 的质数之间不可能连边，否则就超过了 $\max a_i$。

所以我们枚举起点的时候只需要枚举 $1\sim m$ 即可。

时间复杂度：$\mathcal{O}(nm)$ 其实节点数是质数个数，所以实际上远达不到这个上限。

---

***code：***


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdlib>
using namespace std;
const int inf=0x3f3f3f3f;
#define N 2000100
int p[N],pn,pos[N],ans,R,n,dis[N];
bool ntp[N];
void init(int n){
	ntp[1]=true;
	pos[1]=R=1;
	for(register int i=2;i<=n;i++){
		if(!ntp[i]){
			p[++pn]=i,pos[i]=pn+1;
			if(i<1000)++R;
		}
		for(int j=1;j<=pn&&p[j]*i<=n;++j){
			ntp[p[j]*i]=true;
			if(i%p[j]==0)break;
		}
	}
}
int cnt,head[N];
struct Edge{
	int to,nxt;
}edge[N<<1];
void add(int a,int b){
	++cnt;
	edge[cnt].to=b;
	edge[cnt].nxt=head[a];
	head[a]=cnt;
}
void check(int x){
	int p=0,q=0;
	for(register int i=2;i*i<=x;i++){  //分解质因数
		if(x%i==0){
			int cnt=0;
			while(x%i==0)++cnt,x/=i;
			if(cnt&1){
				if(!p)p=i;
				else q=i;
			}
		}
	}
	if(x>1){
		if(!p)p=x;
		else q=x;
	}
	if(!p&&!q){
		printf("1\n");
		exit(0);
	}
	if(!q){
		add(pos[p],1),add(1,pos[p]);	
	}
	else{
		add(pos[q],pos[p]),add(pos[p],pos[q]);
	}
}
int main(){
	n=read();
	init(1000000);   //预处理线筛质数
	ans=inf;
	for(int i=1;i<=n;i++){
		int x=read();
		check(x);
	}
    //bfs求最小环↓↓
	for(int s=1;s<=R;++s){         //枚举起点
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0;
		queue<pair<int,int> > q;  //（当前节点，上一个节点）
		q.push(make_pair(s,0));
		while(!q.empty()){
			int u=q.front().first,fa=q.front().second;
			q.pop();
			for(int i=head[u];i;i=edge[i].nxt){
				int v=edge[i].to;
				if(v==fa)continue;
				if(dis[v]>=inf){   //没有bfs过
					dis[v]=dis[u]+1;
					q.push(make_pair(v,u));
				}
				else if(dis[u]+dis[v]>0){   //bfs过就更新答案
					ans=min(ans,dis[u]+dis[v]+1);
				}
			}
		}
	}
	if(ans>n){
		printf("-1\n");
	}
	else{
		printf("%d\n",ans);
	}
	return 0;
}

```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!




---

## 作者：YLWang (赞：4)

有意思的题。

我们先考虑把每个数的所有完全平方因子去掉。

因为每个数的因数个数不超过 $7$，所以其必定只会包含 $0, 1$ 或 $2$ 种质因子。

所以所有数都可以表示为 $1, p, p \times q$ 三种类型。

如果有 $1$，则直接输出他就行了。

接下来我们观察到匹配完全平方数时很像首尾相接形成了一个环。于是我们套路地将每个质数设成一个点，对于每个 $p \times q$ 类的数连接 $p$ 与 $q$。

那么对于 $p$ 一类数怎么办？我们发现它其实只提供了一边，所以建一个虚点 $s$，连接 $p$ 和 $s$ 即可。

最后我们就是要求一个无权图的最小环。我们发现我们只需要把 $\leqslant \sqrt{\max\{a_i\}}$ 的点作为根跑一遍最短路树就可以了。

该题启示：遇事不决建个图，建图不决造虚点。

---

## 作者：syksykCCC (赞：4)

「每个的因数个数不超过 $7$」看上去非常玄学，它的本质是什么？

> **唯一分解定理**：任何一个大于 $1$ 的自然数 $N$，可以唯一分解成有限个质数的乘积。即：
> 
> $$N = \prod_{i=1}^{n} p_i ^{k_i}$$
> 
> 这里 $\forall 1 \le i \le n, k_i \ge 1$，$p_1 < p_2 < \cdots <p_n$，且 $\forall 1\le i \le n, p_i \in \text{prime} $，正确性显然。

> **约数个数定理**：任何一个大于 $1$ 的自然数 $N$，它的约数个数为：
>
> $$ d(N) = \prod_{i=1}^{n}(k_i + 1) $$
>
> 显然对于每一种质因子，都有选 $0$ 个，选 $1$ 个……选 $k_i$ 个共 $(k_i + 1)$ 种选法，根据乘法原理，当然是它们的乘积。

好，我们用一下约数个数定理。设想 $a_i$ 有 $3$ 种质因数，那么 $d(a_i)$ 最小应当是 $(1+1)^3 = 8$，和 $d(a_i) \le 7$ 矛盾，所以，$a_i$ 至多有 $2$ 种质因子。

所以，$a_i$ 要么是 $1$，要么可以表示为 $p_1^{k_1}$ 的形式，要么可以表示为 $p_1^{k_1} \cdot p_2^{k_2}$ 的形式。不难发现把 $k$ 对 $2$ 取模不会对答案造成影响，这是因为一个数本身的平方因子可以直接相消了。

现在，$a_i$ 只会是 $1$，$p_1$，$p_1 \cdot p_2$ 三种可能了。

* 如果一个 $a_i = 1$，直接输入 $1$，结束程序，因为直接选它就好了；
* 如果一个 $a_i = p_1$，那么，建一条边，把 $1$ 和 $p_1$ 连起来；
* 如果一个 $a_i = p_1\cdot p_2$，那么，建一条边，把 $p_1$ 和 $p_2$ 连起来。

注意 $p$ 的值可能很大，需要离散化，可以在线性筛的时候预处理。

现在得到了一个图，答案就是这个图的 **最小环** 的大小。

为什么？选择一个数，就是选择一条边，如果我们选了一个环，那么环上的每个 $p_i$ 都有两条边相连，也就是乘了 $2$ 次，那么这当然是一个完全平方数了！

$10^6$ 以内质数大概是 $78500$ 个，这个数字记作 $P$。

用 Floyd 算法 $\mathcal O(P^3)$ 求最小环是行不通的。

因为边权为 $1$，可以枚举起点然后 BFS，当然，这样直接做的复杂度是 $\mathcal O(nP)$，当然也是行不通的。（枚举起点 $\mathcal O(P)$，单次 BFS 是 $\mathcal O(n)$，因为有 $n$ 条边）

深入剖析，发现 **一个环内必然有一个点 $\le \sqrt{\max a_i}$**，这是因为不会有两个大于 $\sqrt{\max a_i}$ 的点之间有连边，只要这个较小数作为起点被枚举了，那么这个环就必然会被 BFS 到。所以，起点只要枚举到 $\sqrt{\max a_i} = 10^3$ 即可。

当然，必然点都是质数，所以我们记 $10^3$ 以内的质数个数为 $P'$，这个算法的时间复杂度就是 $\mathcal O(nP')$，可以通过。

当然我的代码偷个懒是直接枚举到 $\sqrt{\max a_i} = 10^3$ 的……

```cpp
#include <bits/stdc++.h>
#define REP(i, x, y) for(register int i = x; i <= y; i++)
using namespace std;
const int N = 1e5 + 5, A = 1e6 + 5, SQRTA = 1000;
const int INF = 0x3f3f3f3f;
int n, ncnt, hd, tl, que[N][2], ans = INF;
int a[N], prm[N], id[A], h[N], dis[N];
bool npr[A];
struct edge
{
	int v, nxt;
} e[A << 1];
void EulerSieve()
{
	for(int i = 2; i < A; i++)
	{
		if(!npr[i]) prm[++prm[0]] = i, id[i] = prm[0] + 1;
		for(int j = 1; j <= prm[0] && i * prm[j] < A; j++)
		{
			npr[i * prm[j]] = true;
			if(i % prm[j] == 0) break;
		}
	}
}
inline void AddEdge(int u, int v)
{
	e[++ncnt] = (edge){v, h[u]}; h[u] = ncnt;
	e[++ncnt] = (edge){u, h[v]}; h[v] = ncnt;
}
void Divide(int x)
{
	int p[4] = {0}, k[4] = {0}; 
	for(int i = 1; i <= prm[0] && prm[i] * prm[i] <= x; i++)
	{
		if(x % prm[i] == 0)
		{
			p[++p[0]] = prm[i];
			while(x % prm[i] == 0) k[p[0]] ^= 1, x /= prm[i];
			if(!k[p[0]]) p[0]--;
		}
	}
	if(x > 1) p[++p[0]] = x, k[p[0]] = 1;
	if(!p[0]) { cout << 1 << endl; exit(0); }
	else if(p[0] == 1) AddEdge(1, id[p[1]]);
	else AddEdge(id[p[1]], id[p[2]]);
}
void Bfs(int s)
{
	memset(dis, 0x3f, sizeof dis);
	dis[s] = 0;
	que[1][0] = s; que[1][1] = 0;
	hd = tl = 1;
	while(hd <= tl)
	{
		int u = que[hd][0], fa = que[hd][1]; 
		hd++;
		for(int i = h[u]; i; i = e[i].nxt)
		{
			int v = e[i].v;
			if(v == fa) continue;
			if(dis[v] == INF)
			{
				tl++;
				que[tl][0] = v; que[tl][1] = u;
				dis[v] = dis[u] + 1;
			}
			else ans = min(ans, dis[u] + dis[v] + 1);
		}
	}
}
int main()
{
	cin >> n;
	REP(i, 1, n) cin >> a[i];
	EulerSieve();
	REP(i, 1, n) Divide(a[i]);
	REP(i, 1, SQRTA) Bfs(i);
	if(ans == INF) cout << -1 << endl;
	else cout << ans << endl;
	return 0;
}
```

---

## 作者：Andrewzdm (赞：2)

# [CF1325E Ehab's REAL Number Theory Problem](https://www.luogu.com.cn/problem/CF1325E)
我的数学老师有一句至理名言：

> 题目当中没有废话！

于是，当我看到这道题，我发现有一句话至关重要：

> Every element in this array has at most 7 divisors.

解读一下就变成了：

> 该数组中每个元素的质因子不超过2个。

这个条件肯定有用。

接着思考一下：如果我们将一个数质因数分解，并将每一个因式的指数都模2，不会影响最终结果。或者换句话说，如果一个数能够被一个完全平方数整除，我们就把这个数除以该完全平方数。

举个例子：现在我们有 $12,75,10$ 三个数。

质因数分解：
- $12=2^2 \times 3$
- $75=3 \times 5^2$
- $10=2 \times 5$

最后的答案应该是2，因为我们可以选择12和75.而我们之所以这么选择是因为 $12 \times 75=2^2 \times 3^2 \times 5^2$ ，这是一个完全平方数。

但我们如果一开始把指数模2：
- $12=2^2 \times 3 \rightarrow 3=3$
- $75=3 \times 5^2 \rightarrow 3=3$
- $10=2 \times 5 \rightarrow 2 \times 5=10$

最终结果不受影响，我们还是会选择前两个数。

所以我们首先把所有数质因数分解并按如上所述的方法处理。接下来有一句话就要派上用场了：

> 该数组中每个元素的质因子不超过2个。

于是最终数组的每个元素都可以表示成一下三种方式的一种：
1. $1$
2. 一个质数 $p$
3. 两个质数 $p,q$ 的乘积 $p \times q$

如果有任何一个元素为1，直接输出1就结束了。

接下来怎么办？

我的一个同学说过一句话：

> 遇事不决建个图。

我们把出现的所有质因子和数1表示成点，把数组的元素表示成一条边，如果这个元素是上面的第3种情况，我们就在节点 $p$ 和节点 $q$ 之间建边。如果是第2种情况，我们就在节点 $p$ 和节点 $1$ 之间建边。所有的边是无向的且边权为1.

我们最终的答案其实就是这个图中的最小环。

举两个具体的例子帮助大家理解：

### Example 1

第一个例子是CF原题的第3个样例：

Input
----
`3`

`6 15 10`

Output
----
`3`

最后我们建出来的图如下：

![Example 1](https://cdn.luogu.com.cn/upload/image_hosting/k51sq5wq.png)

所有的边权均为1，这里的边旁边的信息指的是它所对应的原数组中的元素（下标从1开始）。

图中的最小环长度为3，所以答案是3.

### Example 2

第二个例子是CF原题的第4个样例：

Input
----
`4`

`2 3 5 7`

Output
----
`-1`

建出来的图长这样：

![Example 2](https://cdn.luogu.com.cn/upload/image_hosting/uo8p1okw.png)

图中根本就没有最小环，所以答案为-1.

But why?

因为我们的每一条边的意义就是把这条边两端的节点所对应的数相乘，而如果我们走一个环，这个环上每个节点都乘了两次，最终的乘积肯定是个完全平方数。而我们的每条边对应数组的1个元素，边权为1，最小环就代表选的数最少。

用**bfs**求最小环就可以了。

可是时间复杂度 $O(n^2)$ ，怎么优化？

我们在所有的 $a_i$ 里找到 $max\ a_i$ ，令 $m=\sqrt{max\ a_i}$ ，则我们在bfs求最小环时的起点都不能超过 $m$ ，所走的边的两端的乘积就会大于 $max\ a_i$。

优化完成，可以过了。

回顾、总结一下思路：
* 首先处理数组的每个元素，简化成3种形式。
* 然后建图，求最小环。
* 最后进行时间复杂度上的优化，完成该题。

~~调了1年的~~AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int maxa = 1000010;
int n, a[maxn], maxx;

vector<int> prime;
bool isp[maxa];
int pr_tot;

bool changed[maxa]; 
vector<int> p[maxa]; 

int h[maxa], en;
struct Edge
{
	int u;
	int v;
	int next;
};
Edge e[2 * maxn];

int ans;
int dis[maxa];
//线性素数筛法
void find_prime(int x)
{
	fill(isp + 2, isp + x + 1, true);
	for(int i = 2; i <= x; i++)
	{
		if(isp[i])
		{
			prime.push_back(i);
			pr_tot++;
		}
		for(int j = 0; j < pr_tot && i * prime[j] <= x; j++)
		{
			isp[i * prime[j]] = false;
			if(i % prime[j] == 0)
				break;
		}
	}
	return;
}
//分解质因数并将该数简化
void divide(int x)
{
	int var = x;
	for(int i = 2; i * i <= var; i++)
		if(x % i == 0)
		{
			int index = 0;
			while(x % i == 0)
			{
				x /= i;
				index++;
			}
			if(index % 2 == 1)
				p[var].push_back(i);
		}
	if(isp[x])
		p[var].push_back(x);
	return;
}
//建边
void addedge(int u, int v)
{
	en++;
	e[en].u = u;
	e[en].v = v;
	e[en].next = h[u];
	h[u] = en;
	return;
}
//bfs求最小环
void bfs()
{
	ans = INT_MAX;
	prime.insert(prime.begin(), 1);
	for(int i = 0; i <= pr_tot; i++)
	{
		if((long long)prime[i] * prime[i] > maxx)
			break;
		queue<pair<int, int> > q;
		fill(dis + 1, dis + maxx + 1, INT_MAX);
		q.push(make_pair(prime[i], 0));
		dis[prime[i]] = 0;
		while(!q.empty())
		{
			pair<int,int> tmp = q.front();
			q.pop();
			int u = tmp.first, fa = tmp.second;
			for(int j = h[u]; j != 0; j = e[j].next)
			{
				int v = e[j].v;
				if(v == fa)
					continue;
				if(dis[v] == INT_MAX && v != prime[i])
				{
					dis[v] = dis[u] + 1;
					q.push(make_pair(v, u));
				}
				else
					ans = min(ans, dis[u] + dis[v] + 1);	
			}
		}
	}
	if(ans == INT_MAX)
		ans = -1;
	return;
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		maxx = max(maxx, a[i]);
	}
	find_prime(maxx);
	for(int i = 1; i <= n; i++)
	{
		if(!changed[a[i]])
			divide(a[i]);
		changed[a[i]] = true;
	}
	for(int i = 1; i <= n; i++)
	{
		if(p[a[i]].empty())
		{
			cout << 1 << endl;
			return 0;
		}
		if(p[a[i]].size() == 1)
			p[a[i]].push_back(1);
		addedge(p[a[i]][0], p[a[i]][1]);
		addedge(p[a[i]][1], p[a[i]][0]);
	}
	bfs();
	cout << ans << endl;
	return 0;
}
```


---

## 作者：huayucaiji (赞：1)

这，也是一道纯数论题，首先题目里有一句很重要的话：“every element in this array has at most 7 divisors”，然而我们知道，如果 $p$ 表示质数，则：
$$a=\Pi_{i=1}\ p_i^{c_i}$$

所以 $a$ 共有：  
$$\Pi_{i=1}\ c_i+1$$
个约数，然而这道题里的数，至多有 $7$ 个约数，这代表，这道题里给出的数一定能用（$p,q$ 为质数）：
$$a=p^x\cdot q^y$$
每个数最多只有两个不同质因子，这样这个就简单很多了。

我们不难想到，可以对 $p,q$ 建边，若果 $x,y$ 中有一个为0，那么就把另一个对应的底数与 $1$ 相连。所以，对于样例3来说，就是这样的图：

![E](http://image.qingtengbc.com/2020/03/17/c4ce216841cfe.png)

发现了什么？这是一个环！！！所以在这样的图里，任意一个环，都代表着一个完全平方数的诞生，所以我们只需要找到最小环即可。

但为什么呢？我们发现，我们可以把每一条边想象成一个数，每次走过这条边，就相当于我们用了这个数。所以通过这条边，也相当于在最后我们所需要的形成的那个完全平方数上把其两个节点的编号乘上去。所以只要形成了环，那么每个节点被乘上去的次数就为 $2$，这样我们最后得到一个完全平方数。由于我们要找的数，越少越好，所以求得就算是最小环。

但是还有一个问题：最小环算法是 $O(n^2)$ 的，会超时。其实我们只需要从编号 $\leq \sqrt{\max a_i}$ 即可，这个可以给读者思考为什么。算法的时间复杂度就降到了 $O(p(n)\cdot p(\max a_i))$，$p(x)$ 指小于等于 $x$ 的质数的个数。

```cpp
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10; 

struct edge {
	int v,next;
}e[maxn<<3];

int n,h[maxn*10],cnt,a[maxn],prime[maxn],p_cnt,dis[maxn*10];
vector<int> p[maxn*10];
bool isp[maxn*10],calc[maxn*10];

void addedge(int u,int v) {
	e[cnt].v=v;
	e[cnt].next=h[u];
	h[u]=cnt++;
}

void init(int x)  {
	int xx=sqrt(x),rec=x;
	for(int i=2;i<=xx;i++) {
		if(x%i==0) {
			int num=0;
			while(x%i==0) {
				x/=i;
				num++;
			}
			if(num&1) {
				p[rec].push_back(i);
			}
		}
	}
	if(isp[x]) {
		p[rec].push_back(x);
	}
}
void find_prime(int x) {
	fill(isp+1,isp+x+1,1);
	isp[1]=isp[0]=0;
	for(int i=2;i<=x;i++) {
		if(isp[i]) {
			prime[p_cnt+1]=i;
			p_cnt++;
		}
		for(int j=1;j<=p_cnt;j++){
			if(i*prime[j]>x) break;
			isp[i*prime[j]]=0;
			if(prime[j]%i==0) {
				break;
			}
		}
	}
}

signed main() {
	
	n=read();
	int maxx=-1;
	for(int i=1;i<=n;i++) {
		a[i]=read();
		maxx=max(maxx,a[i]);
	}
	find_prime(maxx);
	fill(h+1,h+1+maxx,-1);
	for(int i=1;i<=n;i++) {
		if(!calc[a[i]])
			init(a[i]);
		calc[a[i]]=1;
	} 
	
	for(int i=1;i<=n;i++) {
		if(p[a[i]].empty()) {
			cout<<1<<endl;
			return 0;
		}
		if(p[a[i]].size()==1) {
			p[a[i]].push_back(1);
		}
		addedge(p[a[i]][1],p[a[i]][0]);
		addedge(p[a[i]][0],p[a[i]][1]);
	}
	
	int ans=2e9;
	prime[0]=1;
	for(int i=0;i<=p_cnt;i++) {
		if(prime[i]*prime[i]>maxx) {
			break;
		}
		queue<pair<int,int> > q;
		fill(dis+1,dis+maxx+1,1e9);
		q.push(make_pair(prime[i],-1));
		dis[prime[i]]=0;
		
		while(!q.empty()) {
			pair<int,int> p=q.front();
			q.pop();
			int u=p.first,fa=p.second;
			
			for(int j=h[u];~j;j=e[j].next) {
				int v=e[j].v;
				if(j!=fa&&j!=(fa^1)) {
					if(dis[v]==1e9&&v!=prime[i]) {
						q.push(make_pair(v,j));
						dis[v]=dis[u]+1;
					}
					else {
						ans=min(ans,dis[u]+dis[v]+1);
					}
				}
			}
		}
	}
	
	printf("%lld",ans==2e9? -1:ans);
	return 0;
}
```

#### *UPD1：感谢 @炸鸡块君指出时间复杂度的问题*

---

## 作者：mydiplomacy (赞：0)

首先将所有数的平方因子除掉，这样不影响答案；

如果某个数有三个素因子，可以证明其至少有$8$个因数；所以每个数都最多有两个素因子。又因为我们已经去除了所有平方因子，所以所有数只有三种可能性，$1$、$p$、$p*q$（$p$、$q$是素数）。如果存在一个$1$，则答案一定是$1$。否则，我们需要选择最少数量的数，使得这些数的乘积是平方数。

我们考虑建图解决这个问题。我们将每个素数对应一个图中的节点（特别地，$1$也对应一个节点），每个数组中的数对应一条无向边。对于每个数$p*q$，我们把节点$p$和节点$q$连起来；对于每个素数$p$，我们把节点$p$和节点$1$连起来。

下面我们证明，对于图中的任何一个简单环，这个环上的边对应的数的乘积一定是完全平方数：对于环上的一个节点$p$，环上必然有恰好两条边与节点$p$相连，所以必然有恰好两个选出的数包含了素因子$p$，所以$p$在乘积中的次幂是$2$。所以乘积一定是完全平方数。

所以我们只需要找到图中的最小环就可以。

一个方法是，注意到图中不存在连接两个$>1000$的节点之间有边（这是因为，如果它们之间有边，那么这条边对应的数组中的数一定$>1000*1000=10^6$），所以每一个至少有两条边的环中必然包含至少一个$<1000$的节点。所以我们只需要从每个$<1000$的素数所对应的节点做一遍bfs，就可以找到所有环，更新答案。

时间复杂度是$O(n*sqrt(C))$，其中$C$代表$a_i$中的最大值。代码不难写，就不放了qwq

---

## 作者：Clever_Jimmy (赞：0)

#### E. Ehab's REAL Number Theory Problem [题目链接](https://codeforces.ml/contest/1325/problem/E)

![图1](https://i.imgflip.com/3sl9ed.jpg)

注意到有 $3$ 不同质因数的数最多会有 $8$ 个约数，则 *at most 7 divisors* 等价于 *at most 2 prime factors*。

如果 $a_i$ 有平方因子，那么将它约去对答案不会有影响。

因此我们将 $a_i$ 的平方因子都约去，此时 $a_i$ 只能表示为 $1, p, pq$ 的形式（其中 $p, q$ 为质数且 $p\neq q$）。

我们构造一个图，使得：

1.  若 $a_i = 1$ 则不做操作；
2.  若 $a_i = p$，那么在 $1, p$ 间连一条边；
3.  若 $a_i = pq$，那么在 $p, q$ 间连一条边。

原问题等价于在这张图上跑最小环，使用 bfs 即可。

点要离散化。

特别的，若存在 $i$，使得被约去平方因子前 $a_i$ 是一个完全平方数，那么答案为 $1$。

[code](https://codeforces.ml/contest/1325/submission/73325433)

```cpp
#include <bits/stdc++.h>
#define LL long long

const int oo = 0x3f3f3f3f;
const int E = 1e6 + 5;
const int N = 1e6 + 5;
const int M = 1e6 + 5;

int n, cntPrimes, cnt, flag, ans = oo;
int first[E], dis[E], npr[M] = { 1, 1 }, p[M], pos[M];

std::vector <int> v[N];

struct NODE {
	int id, edge;
	NODE(int d = 0, int ee = 0) {
		id = d, edge = ee;
	}
};

struct EDGE {
	int to, _next;
} e[E << 1];

void Add_Edge(int u, int v) {
	e[cnt].to = v;
	e[cnt]._next = first[u];
	first[u] = cnt++;
}

void sieve(int maxNum) {
	for(int i = 2; i <= maxNum; ++i) {
		if(npr[i]) continue;
		else p[++cntPrimes] = i, pos[i] = cntPrimes;
		for(int j = 1; i * p[j] <= maxNum; ++j) {
			npr[ i * p[j] ] = 1;
			if(i % p[j] == 0) break;
		}
	}
}

int bfs(int st) {
	std::queue <NODE> q;
	memset(dis, 0x3f, sizeof(dis));
	q.push(NODE(st, -1)), dis[st] = 0;
	int res = oo;
	while(!q.empty()) {
		NODE _x = q.front(); q.pop();
		int x = _x.id, w = _x.edge;
		for(int i = first[x], y = e[i].to; ~i; i = e[i]._next, y = e[i].to) {
			if(i == (w ^ 1)) continue;
			if(dis[y] >= 1e9) {
				dis[y] = dis[x] + 1;
				q.push(NODE(y, i));
			}
			else
				res = std::min(res, dis[x] + dis[y] + 1);
		}
	}
	return res;
}

int main() {
	scanf("%d", &n);
	memset(first, -1, sizeof(first));
	sieve(1e6);
	/*printf("%d\n", cntPrimes);
	for(int i = 1; i <= cntPrimes; ++i) printf("%d ", p[i]);*/
	for(int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		for(int j = 1; p[j] <= 1e3; ++j) {
			if(x % p[j] == 0) {
				int t = 0;
				while(x % p[j] == 0) {
					++t, x /= p[j];
				}
				if(t & 1) v[i].push_back(j);
			}
		}
		if(x == 1 && !v[i].size()) {
			puts("1");
			return 0;
		}
		if(x > 1) v[i].push_back(pos[x]);
		v[i].push_back(0);
		Add_Edge(v[i][0], v[i][1]);
		Add_Edge(v[i][1], v[i][0]);
	}
	/*for(int i = 1; i <= n; ++i) {
		assert(v[i].size() <= 2);
		for(int j = 0; j < v[i].size(); ++j)
			printf("%d ", v[i][j]);
		putchar('\n');
	}*/
	for(int i = 0; p[i] <= 1e3; ++i)
		ans = std::min(ans, bfs(i));
	printf("%d", ans >= 1e9 ? -1 : ans);
	return 0;
}
/*
6
10 8 75 6 7 35

*/
```


---

## 作者：万弘 (赞：0)

这里$L^AT_EX$可能崩，建议去[My blog](https://oierwanhong.cc/2020/03/16/CF1325E/) 查看

题意：给一个长为$n$的正整数序列，每个数至多有$7$个约数，要你选出一个乘积为完全平方数的最短子序列，输出长度即可  

$n\le 10^5,a_i\le 10^6$

<!--more-->

每个数至多有$7$个约数$\rightarrow$ 每个数至多两个不同的质因数   

- 如果某个数没有指数为奇数的质因子，那么它就是一个完全平方数，输出1即可  
- 如果某个数有1个指数为奇数的质因子，让这个质因子和虚点1连无向边。
- 某个数有两个指数为奇数的质因子，让这两个质因子间连无向边

问题等价于，求该无向图中的最小环。    

常用的求最小环方法是`Floyd`,但时间复杂度$\mathcal O(n^3)$显然无法接受。注意到所有边权均为1的性质，可以使用`bfs`最小环：枚举点作为起点，然后`bfs`，如果下一个点$v$不是现在点$u$的前驱：如果$v$没有被访问过，那么记录距离，放入队尾（并记录其前驱是$u$),否则更新答案。

这样的时间复杂度仍是$\mathcal O(nV)$,无法接受。~~无法接受~~

考虑$x> \sqrt V$,有$x^2>V$,即超过$\sqrt V$的素数不可能被考虑超过1次，于是不需要把这些点作为起点。  

时间复杂度$\mathcal O(n\sqrt V)$   

找出素因子那里，直接每次$\sqrt V$做就好，不用预处理了。  

```cpp
#define MAXN 1000011
struct Edge
{
    ll v,nxt;
}e[MAXN<<1|1];
ll cnt=0,last[MAXN],pre[MAXN],dis[MAXN];
void adde(ll u,ll v)
{
    e[++cnt].v=v;
    e[cnt].nxt=last[u],last[u]=cnt;
}
ll ans=INF;
void bfs(ll s)
{
    static std::queue<ll>q;
    memset(dis,0,sizeof dis);
    //printf("work %lld:\n",s);
    dis[s]=1,pre[s]=0;
    q.push(s);
    while(!q.empty())
    {
        ll u=q.front();q.pop();
        //printf("dis[%lld]=%lld,pre=%lld\n",u,dis[u],pre[u]);
        for(ll i=last[u];i;i=e[i].nxt)
        {
            ll v=e[i].v;
            if(v==pre[u])continue;
            if(!dis[v])
            {
                dis[v]=dis[u]+1,pre[v]=u;
                q.push(v);
            }
            else umin(ans,dis[u]+dis[v]-1);
        }
    }
}
bool is_prime(ll n)
{
    for(ll i=2;i*i<=n;++i)
        if(n%i==0)return 0;
    return 1;
}
int main()
{
    ll n=read();
    for(ll i=1;i<=n;++i)
    {
        ll x=read(),c1=0,c2=1;
        for(ll j=2;j*j<=x;++j)
            if(x%j==0)
            {
                ll t=0;
                while(x%j==0)++t,x/=j;
                if((t&1))
                {
                    if(!c1)c1=j;
                    else c2=j;
                }
            }
        if(x>1)
        {
            if(!c1)c1=x;else c2=x;
        }
        //printf("c1=%lld c2=%lld\n",c1,c2);
        if(!c1)
        {
            puts("1");return 0;
        }
        adde(c1,c2),adde(c2,c1);
    }
    bfs(1);
    for(ll i=2;i<=1000;++i)
    {
        if(is_prime(i))bfs(i);
    }
    if(ans>n)puts("-1");
    else printf("%lld",ans);
    return 0;
}
```



---

