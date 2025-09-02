# Switch and Flip

## 题目描述

There are $ n $ coins labeled from $ 1 $ to $ n $ . Initially, coin $ c_i $ is on position $ i $ and is facing upwards (( $ c_1, c_2, \dots, c_n) $ is a permutation of numbers from $ 1 $ to $ n $ ). You can do some operations on these coins.

In one operation, you can do the following:

- Choose $ 2 $ distinct indices $ i $ and $ j $ .
- Then, swap the coins on positions $ i $ and $ j $ .
- Then, flip both coins on positions $ i $ and $ j $ . (If they are initially faced up, they will be faced down after the operation and vice versa)

Construct a sequence of at most $ n+1 $ operations such that after performing all these operations the coin $ i $ will be on position $ i $ at the end, facing up.

Note that you do not need to minimize the number of operations.

## 说明/提示

Let coin $ i $ facing upwards be denoted as $ i $ and coin $ i $ facing downwards be denoted as $ -i $ .

The series of moves performed in the first sample changes the coins as such:

- $ [~~~2,~~~1,~~~3] $
- $ [-3,~~~1,-2] $
- $ [-3,~~~2,-1] $
- $ [~~~1,~~~2,~~~3] $

In the second sample, the coins are already in their correct positions so there is no need to swap.

## 样例 #1

### 输入

```
3
2 1 3```

### 输出

```
3
1 3
3 2
3 1```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
0```

# 题解

## 作者：command_block (赞：20)

**题意** ： 桌面上有 $n$ 枚硬币。初始时第 $c_i$ 号硬币位于位置 $i$，正面朝上（$c$ 是一个 $1 \sim n$ 的排列）。

每次操作的流程如下：

- 选择两个不同的 $i$ 和 $j$。
- 交换位于 $i$ 和 $j$ 的两枚硬币。
- 把位于 $i$ 和 $j$ 的两枚硬币分别翻转。

你可以进行不超过 $n + 1$ 次操作，使得对于所有 $1\leq i\leq n$，第 $i$ 号硬币位于位置 $i$，且都是正面朝上。

构造任意一种方案。

$n\leq 2\times 10^5$ ，时限$\texttt{1s}$。

------------

若不考虑翻面，则是经典的交换排序问题。

解法 ： 将 $c$ 看做我们需要完成的置换，对于每个环，设大小为 $m$ ，使用 $m-1$ 次交换将其构造。这也是操作数的下界。

------------

根据这一相似性，仍然以环为单位来考虑。

观察旧的交换策略在本问题中的效果。

每次交换形如 : 指定 $i$ 并将 $c_i$ 与 $c_{c_i}$ 交换。

效果如下图，涂色代表翻面。我们记这样的一次操作为 $(a,b,c)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/c3a0emrh.png)

考虑这类交换对环的实际影响。一种对环操作的方案如下图 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/ady87jxl.png)

即，首次随意操作，接下来每次将环中的黑色点作为 $a$ 进行操作，这样能保证环上总有一个黑点（且黑点的位置是不变的）。

观察交换次数的限制，不难发现，若每个环分别考虑，则大小为 $m$ 的环的交换次数应 $\leq m$。

此时若仅多用一次操作，即共用 $m$ 次操作，不能将该环复原，至少需要 $\geq m+1$ 次。故对每个环分别考虑并不能满足操作次数的限制。

------------

考虑每两个环 $m_1,m_2$ 一并处理，首先使用一步交换两个环的任意一对元素，将两个环连接为一个大环。

然后，只能用 $m_1+m_2-1$ 次操作将该环整理，否则超出限制。

问题转化为 ： 如何将恰有两个黑点的大小为 $m$ 的环用 $m-1$ 次操作整理完毕。

以每个黑点为 $a$ 不断操作，直到后继为黑点。当最终两个黑点成环时，一次交换即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/kltxbo58.png)

若环的个数为偶数，则两两处理。

若环的个数为奇数且 $>1$ ，则最后一个环配上前面的一个自环处理即可，额外步数为 $1$。

若环的个数为 $1$ ，进行特殊处理。

先考虑如何处理长为 $3$ 的环，手玩不(ban)难(tian)得到  $(c,a,b)\rightarrow(-a,-c,b)\rightarrow(-b,-c,a)\rightarrow(-b,-a,c)\rightarrow(a,b,c)$ 

对于大于 $3$ 的环，先随意进行一步交换 $a,b$ ，将大环拆成两个含有一个反面硬币的环。

然后利用上面的过程逐渐变为一系列自环，当其中一个环只剩两个点时停止。此时即为 $(-a,-c,b)$ 的形式，再用 $3$ 次操作处理完。

以这种方法处理单个环，交换次数是 $m+1$。

```cpp
#include<algorithm>
#include<cstdio>
#define MaxN 200500
using namespace std;
struct Data{int u,v;}ans[MaxN];
int tot,p[MaxN];
void qswap(int u,int v)
{swap(p[u],p[v]);ans[++tot]=(Data){u,v};}
void mdf(int u,int v)
{
  qswap(u,v);
  while(p[u]!=v)qswap(u,p[u]);
  while(p[v]!=u)qswap(v,p[v]);
  qswap(u,v);
}
bool vis[MaxN];
int n,t[MaxN],tn;
int main()
{
  scanf("%d",&n);
  for (int i=1;i<=n;i++)scanf("%d",&p[i]);
  for (int i=1;i<=n;i++)
    if (!vis[i]){
      t[++tn]=i;
      for (int u=i;!vis[u];u=p[u])vis[u]=1;
    }
  if (tn==1){
    int b=t[1],a=p[b];
    qswap(a,b);
    while(p[p[b]]!=b)qswap(b,p[b]);
    int c=p[b];
    qswap(a,c);
    qswap(b,c);
    qswap(a,b);
  }else {
    for (int i=1;i+1<=tn;i+=2)mdf(t[i],t[i+1]);
    if (tn&1)mdf(t[1],t[tn]);
  }
  printf("%d\n",tot);
  for (int i=1;i<=tot;i++)
    printf("%d %d\n",ans[i].u,ans[i].v);
  return 0;
}
```


---

## 作者：serverkiller (赞：5)

这里是官方题解。

这道题分为两部分：

- 将置换环个数降为 $1$。考虑如何 $|S_1|+|S_2|$ 次操作完成两个置换环的交换。

我们先交换两个环上的任意一对元素。

然后，我们发现可以通过不断将第一个环上元素和被置换位置交换来将第一个置换环除被交换数位置之外的所有位置归位；同理第二个环也可以这样归位。

之后，将两个被交换位置换回去。

如下：

$[2,3,1,5,4] \rightarrow [-5,3,1,-2,4] \rightarrow [-4,3,1,-2,5] \rightarrow [-4,2,1,-3,5] \rightarrow [-4,2,3,-1,5]  \rightarrow [1,2,3,4,5]$

- 将最后一个置换环归位。我们要用至多 $|S|+1$ 步将它归位。

如果这个置换环长度大于 $2$，那么可以将这个置换环的前两个元素交换，然后顺次归位，特判掉最后三个位置，例如：（特判的步骤换了一种箭头表示）

$[3,5,2,1,4] \rightarrow [-2,5,-3,1,4] \rightarrow [-5,2,-3,1,4] \rightarrow [-4,2,-3,1,5] \Rightarrow [-4,2,-1,3,5] \Rightarrow [-3,2,-1,4,5] \Rightarrow [1,2,3,4,5]$

如果这个置换环长度等于 $2$，设其包含 $a,b$，那么我们可以找到另一个归位了的元素 $c$，并执行交换 $(a,c),(b,c),(a,c)$ 来将这两个元素交换。

至此，我们即可在 $n+1$ 次操作内解决这个问题。

---

## 作者：dead_X (赞：3)

## 前言
Constructive algorithms 永远滴神！

下文记 $i$ 为最终位置为 $i$ 的硬币，$p_i$ 为这枚硬币当前的位置。
## Part 1
首先，如果我们只 switch，不 flip，怎么做？

这是一个很经典的问题。我们先将 $i$ 向 $p_i$ 连边，把置换拆成环，然后对每个环单独处理。

然后，我们只要交换在环上相邻的两个 $i$ 的 $p_i$ 互换，即 $p'_i=p_{p_i},p'_{p_i}=p_i$，就可以将环长减少 $1$ 了。

如果这个解释不清楚可以看这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ay3lvais.png)
## Part 2
如果我们 flip 了呢？

原来的方法当然不能直接用了，因为交换完了会有两个硬币被 flip，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/u973jem4.png)

但是，如果一开始已经有两个硬币被 flip，这样就可以完美完成任务了，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wn1rj7b7.png)

考虑要求的次数，是 $n+1$ 次。按照上面的方法，一个长度为 $S$ 的环会被操作 $S-1$ 次，而如果一个环操作了 $S+1$ 次，总次数就会超出，所以我们有且只有**一次**额外的操作。

于是，我们考虑，如何通过**一次翻转**生成一个这样的环？
## Part 3
手玩一下会发现如果只是在这个环里整活必然会失败（悲），我们考虑在不同的环上操作，我们可以把两个环通过一次翻转**接起来**！

于是对于每两个环，我们可以在 $S_1+S_2$ 次操作内解决。

只有一个问题……环数是奇数咋办呢？

事实上我们发现，最后一个环我们可以用 $S+1$ 次去解决。这部分其实挺 trivial 的，留给读者自行分析，具体可以看代码实现。
## 代码
```cpp
// Problem: G. Switch and Flip
// Contest: Codeforces - Codeforces Global Round 13
// URL: https://codeforces.com/contest/1491/problem/G
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int X[1000003],Y[1000003],C;
int p[1000003];
void print(int x,int y)
{
	X[++C]=min(x,y),Y[C]=max(x,y),
	swap(p[x],p[y]),
	p[x]=-p[x],p[y]=-p[y];
}
void flush()
{
	printf("%d\n",C);
	for(int i=1; i<=C; ++i) printf("%d %d\n",X[i],Y[i]);
	return ;
}
void check(int n)
{
	for(int i=1; i<=n; ++i) cerr<<p[i]<<" ";
	return ;
}
bool f[1000003],vis[1000003];
int h[1000003],sz[1000003],c;
signed main()
{
	int n=read();
	for(int i=1; i<=n; ++i) p[i]=read();
	for(int i=1; i<=n; ++i) if(!vis[i]&&(p[i]!=i))
	{
		int id=i,cnt=0;
		while(!vis[id]) vis[id]=1,++cnt,id=p[id];
		h[++c]=id,sz[c]=cnt;
	}
	while(c>=2)
	{
		int A=h[c],B=h[c-1];
		print(A,B);
		while(abs(p[A])!=B) print(A,abs(p[A]));
		while(abs(p[B])!=A) print(B,abs(p[B]));
		print(A,B);
		c-=2;
	}
	if(c)
	{
		if(sz[c]==2)
		{
			for(int i=1; i<=n; ++i) if(p[i]==i)
			{
				int A=i,B=h[1],C=p[B];
				print(A,B);
				print(A,C);
				print(A,B);
				break;
			}	
		}
		else
		{
			int A=h[1],B=p[A],C=p[B];
			print(A,B);
			print(B,C);
			while(abs(p[A])!=B) print(A,abs(p[A]));
			while(abs(p[B])!=A) print(B,abs(p[B]));
			print(A,B);
		}
	}
#ifdef LOCAL
	check(n);
#endif
	flush();
	return 0;
}
```

---

## 作者：SSerxhs (赞：2)

把 $c_i$ 看成图上存在一条 $i\to c_i$ 的边，则每个点恰有一条入边一条出边，可以证明图构成若干个环。

考虑如何同时处理两个环。

可以这样构造（下为 $c_i$）

231 564   
234 561  
134 562  
124 563  
123 564  
123 465  
123 456  

这里通过一开始一次多余的操作，使每个数字恰好被操作两次。

于是我们通过 $|S_1|+|S_2|$ 次操作处理了两个环 $S_1,S_2$。

考虑对于剩下那个环怎么处理，一个简单而错误的想法是直接借一个已经归位的自环处理。

然而整张图可能就是一个大环，这时并不能用这种方法。

我们模仿上面的过程进行构造。

23451  
32451  
42351  
52341  

这里同样是借助多做一次操作，使 234 归位。

然而这里 5 不能再归位了，因为 1 和 2 的操作次数会不对。

这里我们继续使用一次操作使 1 操作次数正确。

51342  
15342  
12345  

至此，通过 $|S|+1$ 次操作，成功解决了环 $S$。

总操作次数至多为 $n+1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
std::mt19937 rnd(time(0));
inline int sj(int n)
{
	unsigned int x=rnd();
	return x%n+1;
}
#define rand fst
template<typename typC> void read(register typC &x)
{
	register int c=getchar(),fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
template<typename typC> void write(register typC x)
{
	if (x<0) putchar('-'),x=-x;
	static int st[100];
	register int tp=1,y;st[1]=x%10;x/=10;
	while (x) y=x/10,st[++tp]=x-y*10,x=y;++tp;
	while (--tp) putchar(st[tp]|48);
}
template<typename typC> void write(register typC *a,register int num)
{
	for (register int i=1;i<=num;i++) write(a[i]),putchar(i==num?10:32);
}
#define space(x) write(x),putchar(32)
#define enter(x) write(x),putchar(10)
const int N=1e6+2,M=1e6+2,p=998244353;
inline void inc(register int &x,const int y)
{
	if ((x+=y)>=p) x-=p;
}
inline void dec(register int &x,const int y)
{
	if ((x-=y)<0) x+=p;
}
inline int ksm(register int x,register int y)
{
	register int r=1;
	while (y)
	{
		if (y&1) r=(ll)r*x%p;
		x=(ll)x*x%p;
		y>>=1;
	}
	return r;
}
vector<int> bel[N];
char s[N];
int a[N],ed[N],st[N],ans[N][2];
int T,n,m,c,i,j,k,x,y,z,ass,la,tp;
int main()
{
	read(n);
	for (i=1;i<=n;i++) read(a[i]);
	for (i=1;i<=n;i++) if (!ed[i])
	{
		ed[i]=i;bel[i].push_back(i);
		for (j=a[i];j!=i;j=a[j]) ed[j]=i,bel[i].push_back(j);
	}
	for (i=1;i<=n;i++) if (ed[i]==i) st[++tp]=i;
	for (i=1;i+1<=tp;i+=2)
	{
		x=st[i];y=st[i+1];
		ans[++ass][0]=bel[x][0];ans[ass][1]=bel[y][0];
		for (int i=1;i<bel[x].size();i++) ans[++ass][0]=bel[y][0],ans[ass][1]=bel[x][i];
		for (int i=1;i<bel[y].size();i++) ans[++ass][0]=bel[x][0],ans[ass][1]=bel[y][i];
		ans[++ass][0]=bel[x][0];ans[ass][1]=bel[y][0];
	}
	for (;tp&1;)
	{
		if (bel[st[tp]].size()==1) break;x=st[tp];
		if (bel[x].size()==2)
		{
			for (i=1;i<=n;i++) if (i!=bel[x][0]&&i!=bel[x][1]) break;
			ans[++ass][0]=bel[x][0],ans[ass][1]=i;
			ans[++ass][0]=bel[x][1],ans[ass][1]=i;
			ans[++ass][0]=bel[x][0],ans[ass][1]=i;break;
		}
		for (i=1;i+1<bel[x].size();i++) ans[++ass][0]=bel[x][0],ans[ass][1]=bel[x][i];
		ans[++ass][0]=bel[x][1];ans[ass][1]=bel[x][bel[x].size()-1];
		ans[++ass][0]=bel[x][0];ans[ass][1]=bel[x][bel[x].size()-1];
		ans[++ass][0]=bel[x][1];ans[ass][1]=bel[x][0];
		break;
	}
	printf("%d\n",ass);
	for (i=1;i<=ass;i++) printf("%d %d\n",ans[i][0],ans[i][1]);
}
```

---

## 作者：ax_by_c (赞：1)

令 $i$ 向 $p_i$ 连边，可得若干个环。

## 解法 1

考虑长度为 $3$ 的环，如 $3,1,2$，可得以下解：

1. $-2,1,-3$

2. $-2,3,-1$

3. $-3,2,-1$

4. $1,2,3$

考虑长度 $> 3$ 的环，如 $6,1,2,3,4,5$，可得以下解：

1. $-5,1,2,3,4,-6$

2. $-4,1,2,3,5,-6$

3. $-3,1,2,4,5,-6$

4. $-2,1,3,4,5,-6$

5. $-2,6,3,4,5,-1$

6. $-6,2,3,4,5,-1$

7. $1,2,3,4,5,6$

不难发现在长度为 $3$ 的环的基础上用常规方法处理其他元素即可，于是我们得到了使用 $n+1$ 次操作解决长度为 $n$ 的环的解法。

## 解法 2

考虑同时解决两个环，如 $2,1,5,3,4$，可得以下解：

1. $2,-5,-1,3,4$

2. $1,-5,-2,3,4$

3. $1,-4,-2,3,5$

4. $1,-3,-2,4,5$

5. $1,2,3,4,5$

不难发现任意选择两个元素并用常规方法处理其他元素即可，于是我们得到了使用 $a+b$ 次操作解决长度为 $a$ 的环和长度为 $b$ 的环的解法。

## 通解

分讨：

- 偶数个环

  两两配对使用解法 2 即可，共用 $\sum sz=n$ 次操作。

- 奇数 $(>1)$ 个环

  两两配对使用解法 2，最后一个环和前面留下的自环使用解法 2 即可，共用 $\sum sz+1=n+1$ 次操作。

  此处不能用解法 1 是因为解法 1 需要环的长度至少是 $3$。

- 一个环

  使用解法 1 即可，共用 $n+1$ 次操作。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const int N=2e5+5;
struct DSU{
	struct node{
		int fa,sz;
	}a[N];
	void Init(int n){
		rep(i,1,n)a[i]={i,1};
	}
	int find(int x){
		if(a[x].fa==x)return x;
		return a[x].fa=find(a[x].fa);
	}
	bool meg(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return 0;
		if(a[x].sz>a[y].sz)swap(x,y);
		a[x].fa=y,a[y].sz+=a[x].sz;
		return 1;
	}
}dsu;
vector<int>hds;
vector<pii>ans;
int n,a[N];
void mak(int x,int y){
	ans.pb({x,y});
	swap(a[x],a[y]);
	a[x]=-a[x],a[y]=-a[y];
}
void mak_(int x,int y){
	mak(x,y);
	rep(_,1,dsu.a[y].sz-1)mak(x,abs(a[x]));
	rep(_,1,dsu.a[x].sz-1)mak(y,abs(a[y]));
	mak(x,y);
	dsu.a[x].sz=dsu.a[y].sz=1;
}
void slv(){
	scanf("%d",&n);
	dsu.Init(n);
	rep(i,1,n)scanf("%d",&a[i]),dsu.meg(a[i],i);
	rep(i,1,n)if(dsu.find(i)==i)hds.pb(i);
	if(hds.size()==1){
		int t1=abs(a[1]);
		mak(1,abs(a[1]));
		rep(_,1,n-3)mak(1,abs(a[1]));
		int t2=abs(a[1]);
		mak(t2,t1);
		mak(1,t2);
		mak(1,t1);
	}
	else{
		for(int i=0;i+1<(int)hds.size();i+=2)mak_(hds[i],hds[i+1]);
		if(hds.size()&1)mak_(hds[0],hds.back());
	}
	printf("%d\n",(int)ans.size());
	for(auto it:ans)printf("%d %d\n",it.first,it.second);
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

真的是神仙构造题。                
            
建议去看command_block的题解，讲的很清楚。             

大概想到了要把题转化成一堆环然后杀，但是没有想出来什么很有效的方法最后就被这道题干爆了。                

首先我们不难发现 $c_i$ 的意思就是说要把当前位置 $i$ 的数给移到 $c_i$ 去，转为图就是 $i$ 到 $c_i$ 有一条连边，并且每个点一个入度一个出度，自然而然就构成了很多个环。                     

我们考虑三种情况：            

- 环个数为偶数

- 环个数为奇数且大于 $1$             

- 只有一个环                  

定义黑点为翻面的点，白点为未翻面的点。

对于第一种情况，我们考虑两两环之间处理，首先先交换一下两个环上的任意两个点变成一个环，接着两个黑点一直暴力和它的后继节点交换直到碰到另外的黑点为止，最后两个黑点交换一次就好了，在环大小次内完成。              

对于第二种情况，我们把单出来的环和一个自环进行一次多余匹配，可以证明最大次数为 $n + 1$ 。                

对于第三种情况，由于大小为 $3$ 的环可以单独处理，我们可以先交换一下任意两个在环上紧贴在一起的节点，变成两个环后再用上述的方法一直交换成只有 $3$ 个点的环，最后特殊处理。             

综上，我们可以在 $n + 1$ 次内完成构造。

---

## 作者：tzc_wk (赞：1)

[Codeforces 题目传送门](https://codeforces.com/contest/1491/problem/G) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1491G)

~~obviously，难度高一点的构造题对我来说都是不可做题~~

首先考虑将排列拆成一个个置换环，也就是 $\forall i$ 连边 $i\to p_i$，显然这样我们可以得到一个个环。

首先考虑怎样同时处理两个置换环，假设有两个环，长度分别为 $p,q$，元素分别为 $x_1,x_2,\cdots,x_p;y_1,y_2,\cdots,y_q$。我们考虑以下步骤同时将这两个环中所有元素复位：

- 交换 $x_1,y_1$，两个置换环变为 $-y_1,x_2,\cdots,x_p;-x_1,y_2,\cdots,y_q$。
- $\forall i\in[2,q]$，依次交换 $y_i$ 与原本 $x_1$ 位置上的数，置换环依次变为：
  - $-y_2,x_2,x_3,\cdots,x_p;-x_1,y_1,y_3,\cdots,y_q$
  - $-y_3,x_2,x_3,\cdots,x_p;-x_1,y_1,y_2,\cdots,y_q$
  - ……
  - $-y_q,x_2,x_3,\cdots,x_p;-x_1,y_1,y_2,\cdots,y_{q-1}$
- 同理 $\forall i\in[2,p]$ 交换 $x_i$ 与原本 $y_1$ 位置上的数，置换环依次变为：
  - $-y_q,x_1,x_3,\cdots,x_p;-x_2,y_1,y_2,\cdots,y_{q-1}$
  - $-y_q,x_1,x_2,\cdots,x_p;-x_3,y_1,y_2,\cdots,y_{q-1}$
  - ……
  - $-y_q,x_1,x_2,\cdots,x_{p-1};-x_p,y_1,y_2,\cdots,y_{q-1}$

- 交换 $x_p,y_q$（原本 $x_1,y_1$ 位置上的数），置换环变为 $x_p,x_1,x_2,\cdots,x_{p-1};y_q,y_1,y_2,\cdots,y_{q-1}$，大功告成

因此我们实现了用 $p+q$ 次操作同时处理两个置换环，但是显然置换环的个数不一定是偶数，即可能出现剩余一个置换环的情况，故进一步考虑怎样处理最后一个置换环。

还是假设最后一个置换环的元素分别为 $x_1,x_2,\cdots,x_p$，分两种情况：

- 若 $p\le 2$，我们就找出一个 $y$ 使得 $y$ 已经复位了——显然，由于 $n\ge 2$，我们总能找出这样的 $y$，那么我们就执行以下操作：

  - 交换 $x_1,y$，当前局面为 $-y,x_2,-x_1$
  - 交换 $x_1,x_2$（原本 $y,x_2$ 位置上的数），当前局面为 $-y,x_1,-x_2$
  - 交换 $x_2,y$（原本 $y,x_1$ 位置上的数），当前局面为 $x_2,x_1,y$

  共使用了三次操作。

- 若 $p>2$，那么考虑以下操作：

  - $\forall i\in[2,p-1]$，交换 $x_i,x_1$ 位置上的数，置换环依次变为：
    - $x_1,x_2,x_3,x_4,\cdots,x_{p-1},x_p$
    - $-x_2,-x_1,x_3,x_4,\cdots,x_{p-1},x_p$
    - $-x_3,-x_1,x_2,x_4,\cdots,x_{p-1},x_p$
    - $-x_4,-x_1,x_2,x_3,\cdots,x_{p-1},x_p$
    - ……
    - $-x_{p-1},-x_1,x_2,x_3,\cdots,x_{p-2},x_p$
  - 此时我们不能再交换 $x_{p-1}$ 与 $x_p$ 了，因为那样会使 $x_1,x_p$ 的操作次数的奇偶性发生错误，因此考虑特判最后三个元素，即执行以下操作：
    - 交换 $x_1,x_p$，得到 $-x_{p-1},-x_p,x_2,x_3,\cdots,x_{p-2},x_1$
    - 交换 $x_1,x_{p-1}$，得到 $-x_1,-x_p,x_2,x_3,\cdots,x_{p-2},x_{p-1}$
    - 交换 $x_1,x_p$，得到 $x_p,x_1,x_2,x_3,\cdots,x_{p-2},x_{p-1}$

  共使用了 $p+1$ 次操作。

这样即可实现本题要求，操作次数不超过 $n+1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=2e5;
int n,p[MAXN+5],pth_n;
bool vis[MAXN+5];
vector<int> pth[MAXN+5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++) if(!vis[i]&&p[i]!=i){
		int cur=p[i];pth[++pth_n].pb(i);vis[i]=1;
		while(cur!=i) pth[pth_n].pb(cur),vis[cur]=1,cur=p[cur];
	} vector<pii> ans;//printf("%d\n",pth_n);
	for(int i=1;i+1<=pth_n;i+=2){
		ans.pb(mp(pth[i][0],pth[i+1][0]));
		for(int j=1;j<pth[i].size();j++) ans.pb(mp(pth[i][j],pth[i+1][0]));
		for(int j=1;j<pth[i+1].size();j++) ans.pb(mp(pth[i+1][j],pth[i][0]));
		ans.pb(mp(pth[i][0],pth[i+1][0]));
	}
	if(pth_n&1){
		if(pth[pth_n].size()==2){
			for(int i=1;i<=n;i++){
				if((i^pth[pth_n][0])&&(i^pth[pth_n][1])){
					ans.pb(mp(i,pth[pth_n][0]));
					ans.pb(mp(i,pth[pth_n][1]));
					ans.pb(mp(i,pth[pth_n][0]));
					break;
				}
			}
		} else {
			for(int i=1;i+1<pth[pth_n].size();i++)
				ans.pb(mp(pth[pth_n][0],pth[pth_n][i]));
			ans.pb(mp(pth[pth_n][1],pth[pth_n].back()));
			ans.pb(mp(pth[pth_n][0],pth[pth_n].back()));
			ans.pb(mp(pth[pth_n][0],pth[pth_n][1]));
		}
	} printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++) printf("%d %d\n",ans[i].fi,ans[i].se);
	return 0;
}
```



---

## 作者：_Cheems (赞：0)

挺妙的一题，不过慢慢推还是能推出来的。

考虑 $c_i\to i$ 连边，则得到若干个环。一次操作 $(x,y)$ 会交换 $x,y$ 两个点的出边，且将 $x,y$ 取反，目标是全变成自环且均为正。

自然会想到考察交换一条环边两端节点带来的影响，因为只有这样才能得到子环，对 $a\to b$ 交换如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nq5k5xcm.png)

相当于将 $b$ 从环上剥出来。然后考虑对一个环进行操作，为了尽量抵消取反，那么我肯定优先让被取反过的点作为 $a\to b$ 中的 $b$，这样就可以得到一个未被取反的自环。但不幸的是，按上述方式操作一定会有两个点被取反。

但是你惊喜的发现，可以对两个环上的点进行交换，这样会合并为一个大环，且大环恰有两个取反的点：

![](https://cdn.luogu.com.cn/upload/image_hosting/pskm49ap.png)

现在考虑恰好取反这两个点：当环大小 $\ge 3$ 时，必然有一个取反点满足其前驱未被取反，那么交换它们两，就可以剥出一个未取反的自环，同时前驱被取反，递归下去。最终大小 $=2$ 时直接交换即可。

于是，可以选取两个环 $A,B$，通过 $|A|+|B|$ 步将两个环分解为自环。

假如环数是奇数，则会剩下一个环。可以将其与先前一个自环进行操作。假如一开始只有一个环怎么办？大力构造！

若其大小 $=3$，可以通过两步使两个点被取反然后解决：

![](https://cdn.luogu.com.cn/upload/image_hosting/9rlav7iz.png)

若其大小 $>3$，可以选取两个不相邻的点交换，分割为两个恰有一个取反点的环。一直进行操作，直到两环大小分别为 $1,2$，发现就是上图中间的情况，可以 $3$ 步解决。总次数为 $n+1$。
#### 代码
写死我了。实现略丑，慎看。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, fa[N], nxt[N], pre[N], cir;
bool col[N];
vector<int> buc[N], Cir;
vector<pair<int, int> > ans;

inline void debug(){
	for(int i = 1; i <= n; ++i) cout << nxt[i] << ' ';
	cout << endl;
}
inline int find(int u) {return fa[u] == u ? u : fa[u] = find(fa[u]);}
inline void initcir(){
	for(int i = 1; i <= n; ++i) fa[i] = i, buc[i].clear();
	for(int i = 1; i <= n; ++i) fa[find(i)] = find(nxt[i]);
	Cir.clear();
	for(int i = 1; i <= n; ++i){
		buc[find(i)].push_back(i);
		if(fa[i] == i) Cir.push_back(i);
	}
	/*
	for(auto i : Cir){
		for(auto j : buc[i])
			cout << j << ' ';
		cout << endl;
	}
	*/
}
inline void swp(int x, int y){
	ans.push_back({nxt[x], nxt[y]});
	col[x] ^= 1, col[y] ^= 1;
	swap(pre[nxt[x]], pre[nxt[y]]);
	swap(nxt[x], nxt[y]);
}
inline void solve(int id){
//	debug();
	int x = -1, y = -1, m = buc[id].size();
	for(auto i : buc[id])
		if(col[i]){
			if(x == -1) x = i;
			else y = i;
		}
//	cout << x << ' ' << y << ' ' << m << endl;
	while(m > 2){
		if(pre[x] == y) swap(x, y);
		int _x = pre[x];
		swp(_x, x);
		x = _x;
		--m;
	}
	swp(x, y);
}
inline void solve2(int fir, int sec){
	int x = buc[fir].back(), y = buc[sec].back();
	swp(x, y);
	int fx = find(x), fy = find(y); 
	for(auto i : buc[fx]) buc[fy].push_back(i);
	fa[fx] = fy;
	solve(fy);
}
inline int solve3(int id, int lim){
	int x, m = buc[id].size();
	for(auto i : buc[id]) if(col[i]) x = i;
	while(m > lim){
		int _x = pre[x];
		swp(_x, x);
		x = _x;
		--m;
	}
	return x;
}
inline void calc1(){
	if(n == 3) swp(1, nxt[1]), swp(nxt[1], 5 - nxt[1]), solve(find(1));
	else{
		int p;
		for(int i = 2; i <= n; ++i) if(pre[1] != i && nxt[1] != i) p = i;
		swp(1, p), initcir();
		int fir = Cir[0], sec = Cir[1];
		if(buc[sec].size() == 1) swap(fir, sec);
		int a = solve3(fir, 1), b = solve3(sec, 2), c = pre[b];
		swp(a, c), swp(a, b), swp(a, c);
	}
}
inline void calc2(){
	while(Cir.size() >= 2){
		int fir = Cir.back(); Cir.pop_back();
		int sec = Cir.back(); Cir.pop_back();
		solve2(fir, sec);
	}
	if(!Cir.empty()){
		int fir = Cir.back(), sec;
		for(int i = 1; i <= n; ++i) if(find(i) != fir) sec = i;
		swp(buc[fir][0], sec), buc[fir].push_back(sec);
		solve(fir);
	}
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; ++i) scanf("%d", &pre[i]), nxt[pre[i]] = i;
	initcir();
	if(Cir.size() == 1) calc1();
	else calc2();
	printf("%d\n", ans.size());
	for(auto [x, y] : ans) printf("%d %d\n", x, y);
	return 0;
}
```

---

## 作者：zyh_helen (赞：0)

---
---

先随便手玩几组样例，感觉到总体思路应该是先交换两个，然后把其他的归位，最后剩三个的时候特殊操作一下归位。

```
2  3  4  5  1
-3 -2 4  5  1
-4 -2 3  5  1
-5 -2 3  4  1
-2 -5 3  4  1
-2 -1 3  4  5
1  2  3  4  5
```
发现这样子正好是 $n+1$ 次操作。

---

但是问题是有些时候两个交换的位置最后被属于该位置的数填上了，就无法推进了，并且尝试通过改变交换的顺序也无果。

```
2  3  1  5  4
-3 -2 1  5  4
-1 -2 3  5  4
```
发现这三个其实自身就构成了最后的特殊情况。

---

于是我们联想到分成很多个步骤完成。每个步骤处理哪些呢？看看之前的几个样例，应该是每个步骤完成一个环了。

但是这样子的话我们的操作数就是环的数量加 $n$，显然无法通过。

---

再次手推一些样例，发现有些时候同时处理两个环也可以。

```
2  1  4  3
2  -4 -1 3
1  -4 -2 3
1  -3 -2 4
1  2  3  4
```
这个时候我们神奇的发现，同时处理两个环的话，操作数仅仅是两环环长之和，并且不用特殊操作最后三步！

---

那么做法就很明显了，统计出所有的环，如果能操作两个环就操作，最后如果剩了一个环就像最开始那样操作。

操作数是 $n$（环的个数为偶数）或 $n+1$（环的个数为奇数）。

---
---

代码实现是注意特判最后一个环环长为 2 的情况。

```cpp
#include<bits/stdc++.h>
//#include<Windows.h>
#define int long long
//#define double long double
//#define ls t[p].l
//#define rs t[p].r
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 2e6 + 10, inf = 1e9;
int mod = 998244353;
//const int AQX = 9;
//mt19937 rnd(time(0) ^ clock());
//int random(int l, int r){
//	return rnd() % (r - l + 1) + l;
//}
const double eps = 1e-8, pi = 3.1415926;
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/
//
//int head[N], tot;
//struct edge{
//	int t, f;
//	int d, key;
//	int next;
//}e[N << 1];
//void edge_add(int u, int v, int w = 0){
//	e[++tot].next = head[u];
//	e[tot].t = v;
//	e[tot].d = w;
//	e[tot].f = u;
//	head[u] = tot;
//}
//int qmr(int x, int a){
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}

int n, a[N], vis[N], cnt;
vector<pair<int, int> >ans;
vector<int>v[N];
void work(int x, int y, int s, int t){
	ans.push_back({x, y});
	swap(a[x], a[y]);
	while(s > t){
		if(a[x] != y)ans.push_back({x, a[x]}), swap(a[x], a[a[x]]), s--;
		else ans.push_back({y, a[y]}), swap(a[y], a[a[y]]), s--;
	}
}
void print(){
	cout << ans.size() << endl;
	for(int i = 0;i < ans.size();i++)printf("%lld %lld\n", ans[i].first, ans[i].second);
}
signed main(){
	cin >> n;
	int st = 1, s = 0;
	for(int i = 1;i <= n;i++){
		scanf("%lld", a + i);
		if(a[i] != i)s++;
	}
	if(s == 2){
		int x = 0, y = 0;
		for(int i = 1;i <= n;i++){
			if(a[i] != i){
				if(!x)x = i;
				else y = i;
			}
		}
		int xx = 1;
		while(xx == x || xx == y)xx++;
		cout << 3 << endl << xx << " " << x << endl << xx << " " << y << endl << xx << " " << x << endl;
		return 0;
	}
	for(int i = 1;i <= n;i++){
		if(vis[i] || a[i] == i)continue;
		int x = i;
		cnt++;
		while(!vis[x]){
			vis[x] = 1;
			v[cnt].push_back(x);
			x = a[x];
		}
	}
	for(int i = 1;i + 1 <= cnt;i += 2){
		int x = v[i][0], y = v[i + 1][0];
		work(x, y, v[i].size() + v[i + 1].size(), 2);
		ans.push_back({x, y});
		swap(a[x], a[y]);
	}
	if(!(cnt & 1)){
		print();
		return 0;
	}
	if(v[cnt].size() == 2){
		int z = 1, x = v[cnt][0], y = v[cnt][1];
		while(z == x || z == y)z++;
		ans.push_back({x, z});
		ans.push_back({y, z});
		ans.push_back({x, z});
		print();
		return 0;
	}
	int x = v[cnt][0], y = v[cnt][1];
	work(x, y, v[cnt].size(), 3);
	int z;
	for(int i = 1;i <= n;i++)if(i != x && i != y && a[i] != i)z = i;
	if(a[x] == x){
		ans.push_back({x, z});
		ans.push_back({y, z});
		ans.push_back({x, y});
	}
	else if(a[y] == y){
		ans.push_back({y, z});
		ans.push_back({x, z});
		ans.push_back({x, y});
	}
	else {
		if(a[x] == y)ans.push_back({y, z});
		else ans.push_back({x, z});
		ans.push_back({x, y});
	}
//	if(ans.size() == 200002)cout << 114514;
	print();
	return 0;
}

---

## 作者：RockyYue (赞：0)

#### 1491G

$n$ 个数，初始在位置 $i$ 的数是 $a_i$，$a_{1\dots n}$ 为 $n$ 阶排列。每次操作可以交换两位并将这两位上的数分别取相反数，要求构造方案使得 $n+1$ 次操作内，数 $i$ 位于位置 $i$ 且所有数为正，要求 $O(n)$。

#### Sol

- 这种 $a_{1\dots n}$ 为排列，每次交换的题可以考虑按置换考虑，即 $i\to a_i$ 连边，则必然形成若干环，对每个环单独考虑，本题中任意时刻 $i\to |a_i|$ 连边，操作时要维护这个性质。
- 考虑环内操作，后文中 $a_i$ 均是指当前时刻下。“对一条边 $(x,y)$ 操作”定义为交换当前 $x,y$ 两位（操作过程中点编号正负性不改变，只是标记），操作前有 $|a_x|=y$，操作后 $|a_x|=|a_y|,|a_y|=y$，故若不考虑正负性，$y$ 操作后归位，而 $x$ 向点 $|a_y|$ 连边。
- 现在考虑正负，设有环 $c_1\to c_2\to c_3\to \dots \to c_k\to c_1$，考虑如何操作使其变为 $k$ 个自环，且所有数值为正。
  1. 操作 $c_1\to c_2$，此时数 $a_{c_1}$ 和 $a_{c_2}$ 为负数，相当于值为 $c_2$ 和 $c_3$ 的两位为负，图中点 $c_2$ 形成自环，余下部分 $c_1\to c_3\to \dots \to c_k\to c_1$.
  2. 操作 $c_1\to c_3$，值为 $c_3$ 和 $c_4$ 两位取反，数 $c_3$ 为正，其形成自环，余下部分 $c_1\to c_4\to \dots $
  3. 不断重复，直到 $c_1\to c_k\to c_1$，此时值 $c_k$ 为负，$c_1$ 为正，自环部分值 $c_2$ 为负，值 $c_{3\dots k-1}$ 为正，这两条边无论如何操作总会是一个数正一个数负，最终形成 $k$ 个自环但两个数为负，$k-1$ 步。
     - 你发现这样的局面不会改变，若全局这样操作，则每个环余下两个负数（除了环大小 $\le 2$ 情况），不优。
     - 于是在环内余两个点时考虑引入 $c_2$ 位操作，将此时情况表示在序列上：$-c_n \thinspace -c_2\thinspace c_3\thinspace c_4\dots c_{n-1}\thinspace c_1$。
     - 有方案：依次交换，值为 $(-c_2,c_1)$，$(-c_n,c_2)$，$(-c_2,-c_1)$ 两位，可以在 $k+1$ 步内完成。
- 若每个环的次数都比点数多 $1$，不满足次数要求，而单个环的操作显然并无优化空间，考虑跨环处理。
- 发现对于两个环，每个环中找一个点，将这两个点所代表的位交换，在图上这两个环就被合并成了一个，具体地，$c_1\to \dots \to c_p\to c_1$ 和 $d_1\to \dots \to d_q\to d_1$ 两个环，若交换 $c_i,d_j$ 两位，新图为 $c_1\to \dots \to a_i\to d_j\to \dots \to d_q\to d_1\to \dots \to d_{j-1}\to c_{i+1}\to \dots \to c_p\to c_1$，其中 $a_{c_i}$ 和 $a_{d_j}$ 两位为负，既然对称，不妨操作 $i=j=1$。
- 其可以写作大环 $f$，其大小 $l=p+q$，其中两位值为负，设为 $f_i$ 和 $f_j$（$i<j$），则对 $f_{(i,j]}$ 这一段执行如下操作：
  1. 操作则环，$f_{j-1}$ 位为负。
  2. 重复操作 $f_{j-2}\to f_{j-1},f_{j-3}\to f_{j-2},\dots, f_{i+1}\to f_{i+2}$，此时 $f_{i+2\dots j}$ 这些位分别形成正自环，$f_{i+1},f_{i}$ 两位为负，环形态如 $f_1\to \dots \to f_i\to f_{i+1}\to f_{j+1}\to \dots \to f_l\to f_1$。
  3. 再分别对 $f_{i-1}\to f_i,f_{i-2}\to f_{i-1},\dots,f_1\to f_2,f_{l}\to f_1,\dots f_{j+1}\to f_{j+2}$ 操作，此时 $f_{i+1},f_{j+1}$ 两位为负，环中仅这两点，操作一条边即可。
- 于是对于两个环，可以花费合并的 $1$ 步加后面 $p+q-1$ 步共 $p+q$ 步将其操作到满足条件，不断找两个环这样操作即可。
- 若最终还余下一个环，用最开始的方法操作之，至多 $n+1$ 步。 
- 需要注意的是，最开始的方法针对的是长度 $\ge 3$ 的环，需要判断长度小的情况，那么不如直接将这个环和处理完的一个自环合并处理。

---

## 作者：MiRaciss (赞：0)



首先你肯定得把他放在环上，**然后你发现颜色这个限制被转换到了边上**。然后你每次处理环上相邻的两个点就是把两点的出边先反色，然后靠前的出边和后面那个点形成自环跑出去了，后面那条边和前面的点继续留在环上。一直这样换那么一个长度为 $m$ 的环就被我们转换成了 $m$ 个自环，其中有两个自环的边的颜色变为反色。显然再对这两个自环处理是会超操作次数限制的。发现我们可以先把两个环挼（rua）成一个大环，这时候环上有两条边是反色。你每次操作都把这两条边向下递进颜色，这样两个长度为 $m1,m2$ 的环就在 $m1+m2$ 次操作下变成了全部都是原色的自环，也就是归位成功了。

那么如果说环的个数是奇数呢？前面先两两匹配最后剩下一个环，然后你发现把一个自环放进这个环里之后这个环上刚好有两条反色边。这样你有条边处理了两次，所以总操作次数为 $n+1$。

如果一来环就只有一个呢？你按照老样子相邻两个点依次换，当最后剩下了两个点，这时环上有一条反色边，还有一个边反色的自环。然后你把那个自环上的反色边和环上的原色边挼在一起，这样环上就变成了两条反色边一条原色边。再操作即可。应该是 $n+1$ 次。

代码实现参考 `cmd`。

```cpp
// LUOGU_RID: 130404183
#include<bits/stdc++.h>
using namespace std;

int n;
int a[200005];
int p[200005];
int vis[200005];
int v[200005];

struct zz{
	int x,y;
};
vector<zz> ans;
int tot=0;

void Swap(int x,int y){
	swap(p[x],p[y]);ans.push_back((zz){x,y});
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++) if(!vis[i]){
		v[++tot]=i;
		while(!vis[i]) vis[i]=1,i=p[i];
	}
	if(tot==1){
		int x=1,y=p[x];
		Swap(x,y);
		while(p[p[x]]!=x) Swap(x,p[x]);
		int z=p[x];
		Swap(y,z),Swap(x,z),Swap(x,y);
	}
	else{
		for(int i=1;i+1<=tot;i+=2){
			int x=v[i],y=v[i+1];
			Swap(x,y);
			while(p[x]!=y) Swap(x,p[x]);
			while(p[y]!=x) Swap(y,p[y]);
			Swap(x,y);
		}
		if(tot&1){
			int x=v[1],y=v[tot];
			Swap(x,y);
			while(p[x]!=y) Swap(x,p[x]);
			while(p[y]!=x) Swap(y,p[y]);
			Swap(x,y);
		}
	}
	printf("%d\n",ans.size());
	for(auto now:ans) printf("%d %d\n",now.x,now.y);
	return 0;
}
```


---

