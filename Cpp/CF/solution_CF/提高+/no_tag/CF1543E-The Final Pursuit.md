# The Final Pursuit

## 题目描述

Finally, you have defeated Razor and now, you are the Most Wanted street racer. Sergeant Cross has sent the full police force after you in a deadly pursuit. Fortunately, you have found a hiding spot but you fear that Cross and his force will eventually find you. To increase your chances of survival, you want to tune and repaint your BMW M3 GTR.

The car can be imagined as a permuted $ n $ -dimensional hypercube. A simple $ n $ -dimensional hypercube is an undirected unweighted graph built recursively as follows:

- Take two simple $ (n-1) $ -dimensional hypercubes one having vertices numbered from $ 0 $ to $ 2^{n-1}-1 $ and the other having vertices numbered from $ 2^{n-1} $ to $ 2^{n}-1 $ . A simple $ 0 $ -dimensional Hypercube is just a single vertex.
- Add an edge between the vertices $ i $ and $ i+2^{n-1} $ for each $ 0\leq i < 2^{n-1} $ .

A permuted $ n $ -dimensional hypercube is formed by permuting the vertex numbers of a simple $ n $ -dimensional hypercube in any arbitrary manner.

Examples of a simple and permuted $ 3 $ -dimensional hypercubes are given below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1543E/aea140f70de8ed5134f37d1a4e3eeede0b9ad62a.png)Note that a permuted $ n $ -dimensional hypercube has the following properties:

- There are exactly $ 2^n $ vertices.
- There are exactly $ n\cdot 2^{n-1} $ edges.
- Each vertex is connected to exactly $ n $ other vertices.
- There are no self-loops or duplicate edges.

Let's denote the permutation used to generate the permuted $ n $ -dimensional hypercube, representing your car, from a simple $ n $ -dimensional hypercube by $ P $ . Before messing up the functionalities of the car, you want to find this permutation so that you can restore the car if anything goes wrong. But the job isn't done yet.

You have $ n $ different colours numbered from $ 0 $ to $ n-1 $ . You want to colour the vertices of this permuted $ n $ -dimensional hypercube in such a way that for each and every vertex $ u $ satisfying $ 0\leq u < 2^n $ and for each and every colour $ c $ satisfying $ 0\leq c < n $ , there is at least one vertex $ v $ adjacent to $ u $ having a colour $ c $ . In other words, from each and every vertex, it must be possible to reach a vertex of any colour by just moving to an adjacent vertex.

Given the permuted $ n $ -dimensional hypercube, find any valid permutation $ P $ and colouring.

## 说明/提示

The colouring and the permuted hypercube for the first test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1543E/24b381f853d139f5b42196277a1d932f42b60e97.png)The colouring and the permuted hypercube for the second test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1543E/782238ab7b06fc67a8cfcb7bb5396c04aba44a9e.png)The permuted hypercube for the third test case is given in the problem statement. However, it can be shown that there exists no way to colour that cube satifying all the conditions. Note that some other permutations like $ [0, 5, 7, 3, 1, 2, 4, 6] $ and $ [0, 1, 5, 2, 7, 4, 3, 6] $ will also give the same permuted hypercube.

## 样例 #1

### 输入

```
3
1
0 1
2
0 1
1 2
2 3
3 0
3
0 1
0 5
0 7
1 2
1 4
2 5
2 6
3 5
3 6
3 7
4 6
4 7```

### 输出

```
0 1
0 0
0 1 3 2
0 0 1 1
5 3 0 7 2 6 1 4
-1```

# 题解

## 作者：Leap_Frog (赞：5)

### P.S.
来个有证明的题解  
[更 紬·文德斯 的体验](https://www.cnblogs.com/pealfrog/p/15065478.html)

### Description.
定义一张图是 $n$ 完美图当且仅当：  
- 有 $2^n(n\in\mathbb N)$ 个点和 $n\times 2^{n-1}$ 条边
- $\forall x,y$，$x$ 和 $y$ 有边当且仅当 $x\oplus y=2^k(k\in\mathbb N)$

定义一张图是 $n$ 好图当且仅当：  
- 它可以通过一 $n$ 完美图通过点置换得到

一个 $k$ 染色方案是合法的当且仅当：  
- 染色在 $n$ 进行，染了 $n$ 种颜色分别为 $\{0,1,...,n-1\}$  
- 对于一个点，和它相邻的所有点颜色有 $n$ 种不同的取值  

给定一张好的图，请构造一个点置换，并构造一种合法的染色方案，如果无解输出 `-1`  

### Solution.
首先考虑第一问  
$n$ 完美图是唯一的，且第 $i$ 号点和 $i\oplus(2^k)$ 对称，这点根据定义可得。  
$\because k\in[0,n)$，所以图上任意两个点都对称。  
所以我们可以任意钦定一个点为完美图上的 $0$ 号点。  
同时，我们发现了一个性质，按照 $\text{bit}(x)$ 的个数来分层，完美图是一个分层图。  
那就钦定一个点为第 $0$ 层，然后钦定第一层的全是 $\{2^k\}$，然后下一层的就等于上一层所有向他连边数的 $\text{or}$  
然后第一问就构造完了，而且正确性显然。  

考虑第二问，每个点总共就 $n$ 条出边，而且分别 $\oplus 2^i(i\in[0,n))$。  
考虑第一种颜色出现次数，它在每个节点周围出现了一次，总计 $2^n$ 次。  
然后每个颜色为 $1$ 的节点，它周围有 $n$ 个点，所以它被算重了 $n$ 次。  
所以真正出现次数是 $\frac{2^n}{n}$，这必定是一个整数。  
我们证明了在 $n$ 不为 $2^k(k\in\mathbb N$ 的情况下必定无解。  

首先考虑 $0$ 号点，那我们可以钦定第 $2^i$ 号点颜色是 $i$。  
同时，考虑一个性质，一个长度为 $2^k$ 的排列 $\oplus x(x\in[0,2^k))$ 后仍然是个排列，证明显然。  
所以我们可以对于一个数字，它所有拥有的位取 $\oplus$，可以证明这个构造方式一定是正确的。  
设 $n=2^k$，那相当于它周围的所有点是 $a_x\oplus y\ (y\in[0,2^k))$，根据上面的性质，必然是一个排列。  
所以正确性得证。  

然后这题就做完了。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}/*}}}*/
const int N=65537;int n,m,lim,iv[N],rs[N];char v[N];
struct edge{int to,nxt;}e[N<<4];int et,head[N];
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
inline void solve()
{
	read(n),m=n*(1<<(n-1)),lim=1<<n,et=0;for(int i=0;i<lim;i++) head[i]=iv[i]=v[i]=0;
	for(int i=0,x,y;i<m;i++) read(x),read(y),adde(x,y),adde(y,x);
	vector<int>ls,nw;iv[0]=0,v[0]=1;int cnt=1;
	for(int i=head[0],j=0;i;i=e[i].nxt,j++)
		iv[e[i].to]=1<<j,ls.push_back(e[i].to),cnt++,v[e[i].to]=1;
	while(cnt!=lim)
	{
		for(int x:ls) for(int i=head[x];i;i=e[i].nxt) if(!v[e[i].to]) iv[e[i].to]|=iv[x];
		for(int x:ls) for(int i=head[x];i;i=e[i].nxt)
			if(!v[e[i].to]) nw.push_back(e[i].to),v[e[i].to]=1,cnt++;
		swap(nw,ls),nw.clear();
	}
	for(int i=0;i<lim;i++) rs[iv[i]]=i;
	for(int i=0;i<lim;i++) printf("%d%c",rs[i],i==lim-1?'\n':' '),iv[i]=0;
	if((n&(-n))!=n) return puts("-1"),void();
	for(int i=0;i<lim;i++) for(int j=0;j<n;j++) if((i>>j)&1) iv[rs[i]]^=j;
	for(int i=0;i<lim;i++) printf("%d%c",iv[i],i==lim-1?'\n':' ');
}
int main() {int Ca;for(read(Ca);Ca--;) solve();return 0;}
```

---

## 作者：dead_X (赞：2)

## 题意
我读错了巨大多次题浪费了巨大多时间。

* 定义一张图为 $n$ 维**简单超立方体**。
* 这张图有 $2^n$ 个点和 $n2^{n-1}$ 条边，点编号从 $0$ 到 $2^n-1$。
* 对于任意两个异或起来为 $2$ 的整数次幂的点之间有一条边。
* 定义一张图为 $n$ 维**排列超立方体**。
* 这张图也有 $2^n$ 个点和 $n2^{n-1}$ 条边，点编号从 $0$ 到 $2^n-1$。
* 对于一个排列超立方体，存在一个 $0\sim n-1$ 的排列 $p_i$。
* 对于原图中一条连接 $(u,v)$ 的边，在新图中也存在一条连接 $(p_u,p_v)$ 的边。
* 给定一个 $n$ 维**排列超立方体**，你需要完成以下两个任务：
* 找到一个合法的排列 $p_i$。
* 给每个点染色 $0\sim n-1$，使得对于任意一个点，其连接的所有点的颜色也构成一个 $0\sim n-1$ 的排列。
* 对于第二个任务，可能存在无解的情况，请输出 $-1$。
* 有多组测试数据，$1\leq n\leq 16,\sum2^n\leq 65536$。

## Task 1
显然第一问就是白给然后加码量的。

我们直接随便钦定一个点对应 $0$。

然后将这个点连出来的点分别对应 $2^1,2^2,\cdots,2^{n-1}$。

然后按照距离 $0$ 需要经过的最少边数分层 dp，某一层的权值就等于它连接的所有上一层的点的权值的 $\text{or}$ 和。

时间复杂度 $O(n2^n)$。
## Task 2
显然第二问就是白给然后送 AK 的。

这里我们考虑在简单超立方体上构造。

手玩加上暴力发现好像只有 $n$ 为 $2$ 的整数次幂的时候能构造出解。

这部分的证明我并没有研究，但是 3B1B 居然已经证明过了，有兴趣的可以看一下这个视频。

然后考虑构造。

不难发现 $x$ 连接的所有点就是 $x\oplus2^0,x\oplus2^1,\cdots,x\oplus2^{n-1}$。

一个很自然的想法就是让这些点的颜色分别为 $x$ 的颜色异或 $0\sim n$。

于是，我们直接枚举每个数为 $1$ 的位数，如果这个数在第 $i$ 位为 $1$，就将这个数的颜色异或上 $i$。

时间复杂度 $O(n2^n)$。
## 代码
其实也不是很难写。

```cpp
//And in that light,I find deliverance.
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
vector<int> e[65536];
int vis[65536];
int id[65536],inv[65536];
int col[65536];
signed main()
{
	for(int T=read();T--;)
	{
		int n=read();
		int m=n*(1<<(n-1));
		int N=1<<n;
		for(int i=0; i<N; ++i) e[i].clear(),vis[i]=0,id[i]=0;
		for(int i=1; i<=m; ++i) 
		{
			int u=read(),v=read();
			e[u].push_back(v);
			e[v].push_back(u);
		}
		int visc=1;
		vector<int> cur,nxt;
#define pb push_back
		vis[0]=2;
		int powpowpow2=1;
		for(int i:e[0])
		{
			vis[i]=1,cur.pb(i),id[i]=powpowpow2,++visc;
			powpowpow2<<=1;
		}
		while(visc!=N)
		{
			nxt.clear();
			for(int i:cur) vis[i]=2;
			for(int i:cur) for(int j:e[i]) if(vis[j]!=2)
			{
				id[j]|=id[i];
				if(!vis[j]) vis[j]=1,++visc,nxt.pb(j);
			}
			cur=nxt;
		}
		for(int i=0; i<N; ++i) inv[id[i]]=i;
		for(int i=0; i<N; ++i) printf("%d ",inv[i]);
		puts(""); 
		int o=n;
		while(!(o&1)) o>>=1;
		if(o!=1) puts("-1");
		else
		{
			for(int i=0; i<N; ++i)
			{
				int s=0;
				for(int j=0; j<n; ++j) if(i&(1<<j)) s^=j;
				col[inv[i]]=s;
			}
			for(int i=0; i<N; ++i)
			{
				set<int> s;
				for(int j:e[i]) s.insert(col[j]);
				assert((int)s.size()==n);
			}
			for(int i=0; i<N; ++i) printf("%d ",col[i]);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

~~一开始又猜错结论了，以为 $n\ge 3$ 第二问答案肯定是 $-1$，又是根据错误的数据猜结论的一天（~~

首先第一问很容易，由于数据保证合法，因此可以随便钦定一个点为 $0$，并以任意顺序钦定它们为 $2^0,2^1,2^2,\cdots,2^{n-1}$。然后 BFS 一遍即可，每次 BFS 时取出一个点 $x$ 并将其所有邻居的编号设为该点编号与该邻居编号的 or。

难点在于第二问，手动构造 $n=4$ 时我们有这样一个感觉，就是 $n$ 如果可以表示成 $2^k$ 的形式，那么第二问答案就不是 $-1$。否则第二问答案就是 $-1$。碰到这样形式的题我们可以很自然地想到**归纳构造**，具体来说 $n=1$ 的构造是很 trivial 的，而假设 $res_k$ 为当 $n=2^m$ 时，点 $k$ 的颜色，那么考虑根据 $res_k$ 构造出 $res’_k$ 表示当 $n=2^{m+1}$ 时，点 $k$ 的颜色。稍加思考可以得到：
$$
res'_k=2^{m}·(\text{popcount}(\lfloor\frac{k}{2^m}\rfloor)\bmod 2)+(res_{\lfloor\frac{k}{2^m}\rfloor}+res_{k\bmod 2^m})\bmod 2^{m}
$$
为什么这样归纳构造出来的颜色序列符合要求？首先对于我们称所有 $\lfloor\dfrac{k}{2^m}\rfloor$ 相同的 $k$ 为“同一块”，那么每个点的所有邻居中，恰好有 $2^m$ 个与其在同一块，另外 $2^m$ 个与其不在同一块中，显然与其在同一块的点，它们的 $2^{m}·(\text{popcount}(\lfloor\frac{k}{2^m}\rfloor)\bmod 2)$ 与 $res_{\lfloor\frac{k}{2^m}\rfloor}$ 都是相同的，根据 $n=2^m$ 的构造可知所有邻居的 $res_{k\bmod 2^m}$ 都是不同的，因此与其在同一块中的邻居的颜色不会重复，而对于不在同一块之间的邻居，由于它的邻居与其异或起来一定是 $2$ 的幂，且由于这些邻居与其不在同一块中，因此对于所有符合该要求的邻居 $k’$，都有 $\text{popcount}(\lfloor\frac{k’}{2^m}\rfloor)\bmod 2\ne \text{popcount}(\lfloor\frac{k}{2^m}\rfloor)$，且 $k’\equiv k\pmod{2^m}$，因此所有这样的邻居的 $2^{m}·(\text{popcount}(\lfloor\frac{k}{2^m}\rfloor)\bmod 2)$ 与 $res_{k\bmod 2^m}$ 都是相同的，唯一不同的肯定是 $res_{\lfloor\frac{k}{2^m}\rfloor}$，而如果我们把每一块缩成一个点，那得到的肯定是一个 $n=2^m$ 的图，因此这些邻居的 $res_{\lfloor\frac{k}{2^m}\rfloor}$ 也互不相同。又因为对于与 $k$ 在同一块与与 $k$ 不在同一块的邻居，它们之间的 $\lfloor\dfrac{k}{2^m}\rfloor$ 的奇偶性必定完全不同，因此它们必然一类全部 $<2^m$，一类全部 $\ge 2^m$，不存在重复的情况。

---

