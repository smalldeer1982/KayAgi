# Count BFS Graph

## 题目描述

You are currently researching a graph traversal algorithm called the Breadth First Search (BFS). Suppose you have an input graph of $ N $ nodes (numbered from $ 1 $ to $ N $ ). The graph is represented by an adjacency matrix $ M $ , for which node $ u $ can traverse to node $ v $ if $ M_{u, v} $ is $ 1 $ , otherwise it is $ 0 $ . Your algorithm will output the order the nodes are visited in the BFS. The pseudocode of the algorithm is presented as follows.

```
<pre class="verbatim"><br></br>    BFS(M[1..N][1..N]):<br></br>        let A be an empty array<br></br>        let Q be an empty queue<br></br><br></br>        append 1 to A<br></br>        push 1 to Q<br></br><br></br>        while Q is not empty:<br></br>            pop the front element of Q into u<br></br>            for v = 1 to N:<br></br>                if M[u][v] == 1 and v is not in A:<br></br>                    append v to A<br></br>                    push v to Q<br></br><br></br>        return A<br></br>
```

During your research, you are interested in the following problem. Given an array $ A $ such that $ A $ is a permutation of $ 1 $ to $ N $ and $ A_1 = 1 $ . How many simple undirected graph with $ N $ nodes and adjacency matrix $ M $ such that $ \text{BFS}(M) = A $ ? Since the answer can be very large, calculate the answer modulo $ 998\,244\,353 $ .

A simple graph has no self-loop ( $ M_{i, i} = 0 $ for $ 1 \leq i \leq N $ ) and there is at most one edge that connects a pair of nodes. In an undirected graph, if node $ u $ is adjacent to node $ v $ , then node $ v $ is also adjacent to node $ u $ ; formally, $ M_{u, v} = M_{v, u} $ for $ 1 \leq u < v \leq N $ .

Two graphs are considered different if there is an edge that exists in one graph but not the other. In other words, two graphs are considered different if their adjacency matrices are different.

## 说明/提示

Explanation for the sample input/output #1

The following illustration shows all graphs that satisfy the requirements.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906J/96f1bd6a81238405d96653e941a6d0d3b2152525.png)Explanation for the sample input/output #2

The only graph that satisfies the requirements is a graph with two edges: one that connects nodes $ 1 $ and $ 3 $ , and another one that connects nodes $ 3 $ and $ 2 $ .

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 3 2```

### 输出

```
1```

## 样例 #3

### 输入

```
5
1 3 2 4 5```

### 输出

```
17```

## 样例 #4

### 输入

```
11
1 2 3 4 5 6 7 8 9 10 11```

### 输出

```
379394847```

# 题解

## 作者：IGA_Indigo (赞：6)

## 题目大意
这道题是非常抽象的前缀和差分优化 DP（反正是我在考场上写不出来那种）。

为了理解题意，我写了一个非常非常朴素的 BFS 来帮助大家理解题目给出的伪代码。
```cpp
void bfs(){
	tail=0;
	while(!q.empty()){
		q.pop();
	}
	q.push(1);
	a[++tail]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v=1;v<=n;v++){
			if(m[u][v]){
				int bj=0;
				for(int i=1;i<=tail;i++){
					if(a[i]==v){
						bj=1;
						break;
					}
				}
				if(bj){
					continue ;
				}
				else{
					q.push(v);
					a[++tail]=v;
				}
			}
		}
	}
}
```
## 大体思路
众所周知 BFS 是一种层次搜索，他给的 $a$ 数组是层次搜索好了的，所以我们可以知道他搜索的顺序是每一个递增的序列作为每一次扩展来搜索的，结合一下题意就是一起被推入队列。

首先我们需要定义一个 $xl$ 数组预处理 $xl[i]$ 从 $a[i+1]$ 开始最长的一段递增序列到哪，是最大的使 $a_i$ 到 $a[xl_i-1]$ 是单调递增的下标。

实现为：
```cpp
for(int i=1;i<=n;i++){//求xl[i]从a[i+1]开始最长的一段递增序列到哪个下标 
	if(i+2>n+1){
		xl[i]=n+1;
		continue ;//如果超出了n的限制就指向n+1
	}
	xl[i]=i+2; 
	for(int j=i+2;j<=n;j++){//这里先变成i+2，如果j比j-1小，那么自然就跳出了 
		if(a[j]<a[j-1]){
			break ;//小了就跳出
		}
		else{
			xl[i]++;//否则还能再往后判断 
		}
	}
}
```

然后我们就可以设计 DP 了。
### 状态设计
我们将 $f[i][j]$ 设置为搜到 $a[i]$ 了，且 $a[j]$ 被记录的状态
### 状态转移
这个状态转移穿插着前缀和差分，不是那么纯种，所以不是很好想，我们知道 $a[j]$ 及以后的点都是由 $a[i]$ 拓展而来，所以我们还需要枚举个数 $j$ ，所以个数就变成了 $2^{j-i}$ 个。再加上累加的前缀和，就有了：
```cpp
for(int j=i;j<=n;j++){
	long long x=f[i][j]*_2[j-i]%998244353;
	s[j]=(s[j]+x)%998244353;
	s[xl[j]]=(s[xl[j]]-x+998244353)%998244353;//差分过程（避免是负数情况，加一个模数） 
}
for(int j=1;j<=n;j++){
	s[j]=(s[j]+s[j-1])%998244353;//前缀和 
}
for(int j=1;j<=n;j++){
	f[i+1][j]=s[j];//赋值成当前j被记录的前缀和，代表当前状态最大方案数 
}
```
### 答案输出
这时候我们只需要输出 $f[n+1][n]$ 就可以了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[5005];
long long xl[5005];
long long s[5005];//前缀和数组 
long long _2[5005];//先将2的下标次方预处理出来，并且%题目所给模数，在后期方便运算
long long f[5005][5005];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	_2[0]=1;//2的0次方是1；
	f[1][1]=1;//初始化 
	for(int i=1;i<=n;i++){
		_2[i]=_2[i-1]*2%998244353;//预处理 
	}
	for(int i=1;i<=n;i++){//求xl[i]从a[i+1]开始最长的一段递增序列到哪个下标 
		if(i+2>n+1){
			xl[i]=n+1;
			continue ;//如果超出了n的限制就指向n+1
		}
		xl[i]=i+2; 
		for(int j=i+2;j<=n;j++){//这里先变成i+2，如果j比j-1小，那么自然就跳出了 
			if(a[j]<a[j-1]){
				break ;//小了就跳出
			}
			else{
				xl[i]++;//否则还能再往后判断 
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			s[j]=0;//清零前缀和数组 
		}
		for(int j=i;j<=n;j++){
			long long x=f[i][j]*_2[j-i]%998244353;
			s[j]=(s[j]+x)%998244353;
			s[xl[j]]=(s[xl[j]]-x+998244353)%998244353;//差分过程（避免是负数情况，加一个模数） 
		}
		for(int j=1;j<=n;j++){
			s[j]=(s[j]+s[j-1])%998244353;//前缀和 
		}
		for(int j=1;j<=n;j++){
			f[i+1][j]=s[j];//赋值成当前j被记录的前缀和，代表当前状态最大方案数 
		}
	}
	cout<<f[n+1][n]%998244353;
	return 0;
} 
```

---

## 作者：Register_int (赞：5)

这篇题解交错了，管理帮忙改一下。 /kk

对着广搜的过程做 dp。设 $dp_{i,j}$ 为当前搜到点 $a_i$，$a_j$ 之前的点都已经被记录的方案数。由于加入队列时是按顺序加入，所以只有在原序列中连续且单调递增的一段才能被同一个点推入队列。我们预处理出，$r_i$ 为最大的使得 $i+1\sim r_i-1$ 递增的位置。在 $j$ 之前，由于位置已经被更新，连不连边均可，所以方案数为 $2^{j-i}$。有转移：

$$dp_{i+1,j}\gets\sum_{k\le j<r_k} 2^{k-i}dp_{i,k}$$

直接做是 $O(n^3)$ 的。考虑换成刷表转移，后面就变成了区间和的形式，用前缀和优化，时间复杂度 $O(n^2)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e3 + 10;
const int mod = 998244353;

int n, a[MAXN], r[MAXN];

ll p2[MAXN], dp[MAXN][MAXN], s[MAXN], x;

int main() {
	scanf("%d", &n), dp[1][1] = *p2 = 1;
	for (int i = 1; i <= n; i++) p2[i] = (p2[i - 1] << 1) % mod;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		for (r[i] = min(i + 2, n + 1); r[i] <= n && a[r[i] - 1] < a[r[i]]; r[i]++);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) s[j] = 0;
		for (int j = i; j <= n; j++) {
			x = dp[i][j] * p2[j - i] % mod;
			s[j] = (s[j] + x) % mod, s[r[j]] = (s[r[j]] - x + mod) % mod;
		}
		for (int j = 1; j <= n; j++) s[j] = (s[j] + s[j - 1]) % mod;
		for (int j = 1; j <= n; j++) dp[i + 1][j] = s[j];
	}
	printf("%lld", dp[n + 1][n]);
}
```

---

## 作者：aCssen (赞：2)

### Solution

bfs 按层进行，每个点能 push 进去一段点。设 $f_{i,j}$ 表示当前正考虑点 $P_i$ ，队列里**已经** push 到了位置 $j$ 的方案数，即，$P_i$ 带来的所有更新都是 push 在 $j$ 后面。这个状态有意义应满足 $j \ge i$。

那么 $f_{i,j}$ 可以更新 $f_{i+1,k}$，满足 $j \le k \le R_{j+1}$。其中 $R_j$ 表示从 $j$ 开始最长能延续多长的一段递增。原因就是一个点 push 进去的一定是一段编号递增的点。现在已经 push 到 $j$ 了，从 $j+1$ 开始要编号递增。

前面这 $j$ 个点已经被标记，无论 $P_i$ 和它们有没有边都不会被 push，所以这些边连不连均可，后面的被 push 进去的点与 $P_i$ 必须有边，没被 push 的必须没有边。但是如果对于每个点我们都考虑它与其他点所有的连边方案的话会算重，比如 $(1,2)$ 会被 $1$ 考虑一次 $2$ 考虑一次，所以强制只考虑位置大于自己的点即可，这样的点共有 $j-i$ 个。我们更新是向后更新，所以考虑编号大于自己的会比较好做。

整理一下就是 $f_{i+1,k}\larr 2^{j-i}f_{i,j}$，其中 $j \le k \le R_{j+1}$。初始时 $f_{1,1}=1$，就是说 $1$ 被 push 了但还没考虑它的连边。答案是 $f_{n+1,n}$，因为要考虑完这 $n$ 个点。

这样直接做是三次方的，然后你注意到一个转移是区间加一个固定的数，所以前缀和 + 差分即可，时间复杂度 $\mathcal{O}(n^2)$。

### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int MOD=998244353;
const int maxn=5005;
int f[maxn][maxn],pw[maxn],r[maxn],a[maxn],c[maxn];
int main(){
	int n=read();
	f[1][1]=1;pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=(pw[i-1]*2)%MOD;
	for(int i=1;i<=n;i++) a[r[i]=i]=read();
	for(int i=1;i<=n;i++) while(a[r[i]]<a[r[i]+1]) r[i]++;
	r[n+1]=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) c[j]=0;
		for(int j=i;j<=n;j++){
		//	for(int k=j;k<=r[j+1];k++){
		//		(f[i+1][k]+=(1ll*pw[j-i]*f[i][j])%MOD)%=MOD; 
		//		printf("%d %d %d\n",i,j,f[i][j]);
		//	}
			int x=(1ll*pw[j-i]*f[i][j])%MOD;
			c[j]=(c[j]+x)%MOD,c[r[j+1]+1]=(c[r[j+1]+1]-x+MOD)%MOD;
		}
		for(int j=1;j<=n;j++) c[j]=(c[j]+c[j-1])%MOD;
		for(int j=i;j<=n;j++) f[i+1][j]=c[j];
	}
	write(f[n+1][n]);
	return 0;
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

简单题。

bfs 的过程是一层一层遍历的。又因为存图是邻接矩阵，所以一层里一定是递增的。

考虑按照层来做 dp，令 $f_{i,j}$ 表示 遍历到了 $i$，前 $j$ 个结点已经全部入队，并预处理出 $nxt_i$ 表示使 $[i,j]$ 递增的最大的 $j$。

有 $f_{i+1,k} \gets \sum\limits_{k\in [j,nxt_{j+1}]} 2^{j-i-1} f_{i,j}$。考虑主动转移，用前缀和优化可做到 $O(n^2)$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5;
const int Mod=998244353;
int n;
int a[N],nxt[N],Pow[N];
int f[N][N],g[N][N];
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	Pow[0]=1;
	for(int i=1;i<=n;i++) Pow[i]=1ll*Pow[i-1]*2%Mod;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n+1;i++){
		nxt[i]=i;
		for(int j=i+1;j<=n;j++){
			if(a[j]>a[j-1]) nxt[i]=j;
			else break;
		}
	}
	nxt[n+1]=n;
	f[0][1]=1;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<=n;j++){
			g[i+1][j]=(g[i+1][j]+1ll*f[i][j]*Pow[max(j-i-1,0)]%Mod)%Mod;
			g[i+1][nxt[j+1]+1]=(g[i+1][nxt[j+1]+1]-1ll*f[i][j]*Pow[max(j-i-1,0)]%Mod+Mod)%Mod;
		}
		for(int j=1;j<=n;j++) g[i+1][j]=(g[i+1][j]+g[i+1][j-1])%Mod,f[i+1][j]=g[i+1][j];
	}
	printf("%d\n",f[n][n]);
	return 0;
}

```

---

