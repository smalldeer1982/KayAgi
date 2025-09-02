# 「DROI」Round 1 距离

## 题目背景

没有什么距离是无法跨越的。

## 题目描述

定义一棵树 $G$ 上两点 $u,v$ 之间的距离 $\operatorname{dis}(u,v)$ 为两点之间点的数量。

若对于树上两点 $u,v$，满足 $\forall x \in G,\operatorname{dis}(u,x) \leq \operatorname{dis}(u,v)$ **且** $\operatorname{dis}(v,x) \leq \operatorname{dis}(u,v)$，那么我们称无序点对 $(u,v)$ 为**极远点对**。

同时，树 $G$ 上一点 $x$ 的权值 $v_x$ 定义为：满足两点间最短路径经过 $x$ 的极远点对的数量。

现给定树 $G$，求 $\sum\limits_{x \in G}{v_x^k}$ 对 $998244353$ 取模的值，其中 $k$ 是给定的常数，且 $k \in [1,2]$。

## 说明/提示

#### 样例解释 #1

$(1,2)$ 为极远点对，所以 $1$ 号和 $2$ 号点点权均为 $1$，$1^1 + 1^1 =2$。

------------

#### 样例解释 #2

极远点对有 $(2,3),(2,4),(2,5),(3,4),(3,5),(4,5)$，故答案为 $4 \times 3^2 + 6^2 = 72$。

------------

#### 数据范围

| 测试点编号 | $1$ | $2$ | $3$ | $4 \sim 5$ | $6$ | $7$ | $8 \sim 9$ | $10$ |
| :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: |
| $n$ | $300$ | $300$ | $2000$ | $2000$ | $10^5$ | $5 \times 10^6$ | $10^5$ |  $5 \times 10^6$|
| $k$ | $1$ | $2$ | $1$ | $2$ | $1$ | $1$ | $2$ | $2$ |

对于 $100\%$ 的数据，满足 $n \leq 5 \times 10^6$，$1 \leq  k \leq 2$。

**本题输入量较大，请用较快的输入方法。**




## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
5 2
1 2
1 3
4 1
5 1
```

### 输出

```
72```

# 题解

## 作者：Demeanor_Roy (赞：8)

- 出题人题解。

------------

不妨思考极远点对的本质是什么。发现若 $(u,v)$ 为极远点对，可以看作从任意点 $u$ 找到距离其最远点 $v$，再从点 $v$ 找到距离其最远点且此点恰好为 $u$，不难察觉这符合dfs两遍求树的直径的过程，故 $u,v$ 为同一直径两端点。

所以题目意转化为对于每个点，求出其在多少条直径上。

将树以 $1$ 为根定型，然后求解答案。

不妨先树形 DP 求出总直径数 $sum$，以 $x$ 为端点直径数的子树和 $l_x$，挂在 $x$ 上的直径数 $p_x$，$p_x$ 的子树和 $s_x$。其中除了 $l_x$ 的求解略显繁琐外，其他的求解都是朴素的（注意细节，一定要想清楚再写，数组的含义千万不能弄混）。

考虑经过 $x$ 的直径数，不难得到：$v_x =p_x + (l_x - s_x \times 2)$。前者是挂在 $x$ 上的直径，后者是简单容斥得到的横穿 $x$ 子树内外的直径。同样，这样的计算是直观的。

至此整道题解决完毕，时间复杂度线性。

下面阐述一下部分分缘由：

1. $n \leq 300$，暴力找极远点对，暴力标记即可。$O(n^3)$。

2. $n \leq 2000$，暴力找极远点对，树上差分标记即可。$O(n^2 \log n)$。

3. $n \leq 10^5$，给数据结构学傻的人。

4. $k=1$，不难发现贡献可以合起来算，令 $len$ 为直径长度，答案即为 $len \times sum$。

下附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=5e6+10,mod=998244353;
int n,k,len,ans,s[N],l[N];
int h[N],e[N<<1],ne[N<<1],idx;
struct node
{
	int val,cnt;
}p[N],fi[N],se[N];
inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}
inline void add(int a,int b)
{		
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
inline void dfs(int u,int fa)
{
	fi[u].val=fi[u].cnt=1;
	for(int i=h[u];~i;i=ne[i])
	{
		if(e[i]==fa)	continue;
		dfs(e[i],u);
		if(fi[u].val+fi[e[i]].val>p[u].val) p[u]={fi[u].val+fi[e[i]].val,(int)((LL)fi[u].cnt*fi[e[i]].cnt%mod)};	
		else if(fi[u].val+fi[e[i]].val==p[u].val) p[u].cnt=(p[u].cnt+(LL)fi[u].cnt*fi[e[i]].cnt%mod)%mod;
		if(fi[e[i]].val+1>fi[u].val) se[u]=fi[u],fi[u]={fi[e[i]].val+1,fi[e[i]].cnt};
		else if(fi[e[i]].val+1==fi[u].val) fi[u].cnt+=fi[e[i]].cnt;
		else if(fi[e[i]].val+1>se[u].val) se[u]={fi[e[i]].val+1,fi[e[i]].cnt};
		else if(fi[e[i]].val+1==se[u].val) se[u].cnt+=fi[e[i]].cnt;
	} 
	len=max(len,p[u].val);
}
inline void DFS(int u,int fa,int up,int num)
{
	s[u]=p[u].cnt=(p[u].val==len?p[u].cnt:0);
	for(int i=h[u];~i;i=ne[i])
	{
		if(e[i]==fa)	continue;
		int cur=max(up+1,(fi[e[i]].val+1==fi[u].val&&fi[e[i]].cnt==fi[u].cnt)?se[u].val:fi[u].val);
		if(fi[e[i]].val+1==fi[u].val&&fi[e[i]].cnt==fi[u].cnt) DFS(e[i],u,cur,num*((up+1)==cur)+se[u].cnt*((se[u].val)==cur));
		else if(fi[e[i]].val+1==fi[u].val) DFS(e[i],u,cur,num*((up+1)==cur)+(fi[u].cnt-fi[e[i]].cnt)*((fi[u].val)==cur));
		else DFS(e[i],u,cur,num*((up+1)==cur)+fi[u].cnt*((fi[u].val)==cur));
		l[u]=(l[u]+l[e[i]])%mod;s[u]=(s[u]+s[e[i]])%mod;
	}
	if(up+1==len) l[u]=(l[u]+num)%mod;
	if(fi[u].val==len) l[u]=(l[u]+fi[u].cnt)%mod;
}
inline int pwr(int x,int y){return y==1?x:(LL)x*x%mod;}
int main()
{
	memset(h,-1,sizeof h);
	n=read(),k=read();
	for(int i=1;i<n;i++)	
	{
		int u,v;
		u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,-1);DFS(1,-1,0,0);
	for(int i=1;i<=n;i++) ans=(ans+pwr(p[i].cnt+(l[i]-s[i]*2),k))%mod;
	printf("%d",ans);
	return 0;
}
```

似乎验题人有更简单的做法。。。


---

## 作者：qwer6 (赞：3)

写这道题的时候一篇题解都看不懂，所以决定写一篇简单的题解。  
首先，我们可以容易知道所谓极远点对指的是直径的端点。  
为什么呢？因为对于一个点，距离它最远的点是直径的端点之一，而对于直径端点，距离最远的显然是另一个端点，所以对于一个非直径端点 $u$，只有 $(u,x)$ 这个点对可能成为极远点对，其中 $x$ 为距离它最远的直径端点，但是由于直径是最长的链，所以一定存在直径端点 $y$，$(x,y)$ 的距离大于 $(u,x)$，所以极远点对只可能是直径端点。  
知道了这个，问题转换为求每一个点有多少条直径经过它。  
看上去还是不好求的样子，但是我们知道，对于所有直径，必定交于同一点，也就是树的中点，具体证明[戳这里](https://oi-wiki.org/graph/tree-diameter/#%E8%8B%A5%E6%A0%91%E4%B8%8A%E6%89%80%E6%9C%89%E8%BE%B9%E8%BE%B9%E6%9D%83%E5%9D%87%E4%B8%BA%E6%AD%A3%E5%88%99%E6%A0%91%E7%9A%84%E6%89%80%E6%9C%89%E7%9B%B4%E5%BE%84%E4%B8%AD%E7%82%B9%E9%87%8D%E5%90%88)。  
所以我们考虑从树的中点入手，让树的中点成为根，将树的形态定下来，下文中所有根都指树的中点，求解相关信息均以中点为根时的树为准。  
此时我们发现，直径一定是由根的最长链和次长链组成的，原因就是直径是最长链，这应该十分好理解。  
当直径长度为奇数的时候，直径由根的两条最长链组成；当直径长度为偶数时，直径由根的一条最长链和一条次长链组成。  
既然都分奇偶了，那显然需要分类讨论了。  
首先，无论直径长度的奇偶性，我们都需要求出此时树中以每一个节点为起点的最长链长度与最长链个数。  
下面问题直接变成组合数学了。  
当直径长度为奇数时，考虑对于根的每一棵子树，如果这棵子树对于最长链个数没有贡献，我们直接跳过，因为没有任何一条直径经过这棵子树，原因就是此时直径是由两条最长链组成的。  
如果这棵子树对于最长链有贡献，那么假设根的最长链共有 $tot$ 条，这棵子树对最长链数量贡献为 $cnt$，我们可以容易知道，对于这棵子树中所有点，可以对点权产生贡献的端点有 $tot-cnt$ 个，那么对于这棵子树中所有对最长链数量有贡献的点，都应该将点权加上 $k\times (tot-cnt)$，其中 $k$ 表示点对于最长链数量的贡献，也就是我们上文中求解出的以每一个节点为起点的最长链数量。  
当直径长度为偶数时，根据树的中点的相关知识，此时会有两个中点，而我们此时取了其中一个作为根，所以，对于此时的根，一定存在一棵子树，它的根节点是另一个中点。  
而我们上面说过，当直径长度为偶数时，直径由根的一条最长链和一条次长链组成，我们假设最长链数量为 $tot_1$，次长链数量为 $tot_2$，那么 $tot_1$ 与以另一个中点为起点的最长链数量相同。  
显然，直径数量为 $tot_1\times tot_2$，十分简单的组合数学问题，这里不做解释。  
对于对次长链数量有贡献的子树中点，可以对点权产生贡献的端点有 $tot_1$ 个，对于以另一个中点为根的子树，可以对点权产生贡献的端点有 $tot_2$ 个，统计点权的方式与直径长度为奇数时相同。  
对于中点点权，显然为直径条数。  
最后直接统计答案即可。  
注意俗话说的好，好事多模，不然容易爆，这道题把所有数组全开 long long 的话，空间有点卡，最后选择在运算时类型强转为 long long，模完之后再换回 int。
```c++
/*by qwer6*/
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("------------------------------")
namespace FastIO{
	int write_top,read_f,read_x;
	char read_char;
	int write_st[20];
	inline int read(int &a){
		read_char=getchar();
		read_f=1;
		a=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			a=(a<<1)+(a<<3)+(read_char^48);
			read_char=getchar();
		}
		return a=a*read_f;
	}
	inline int read(){
		read_char=getchar();
		read_f=1;
		read_x=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			read_x=(read_x<<1)+(read_x<<3)+(read_char^48);
			read_char=getchar();
		}
		return read_x*read_f;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		write_top=0;
		do{
		   write_st[++write_top]=x%10;
		   x/=10;
		}while(x);
		while(write_top)putchar(write_st[write_top--]+'0');
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=5e6+5,mod=998244353;
int n,k,p,a,b,len,ans;
int dis[N],fa[N],mx[N],cnt[N],val[N];
vector<int>e[N];
void dfs(int u,int las,bool opt){
	if(opt)fa[u]=las;
	for(int v:e[u]){
		if(v==las)continue;
		dis[v]=dis[u]+1;
		dfs(v,u,opt);
	}
}
void redfs(int u,int las){//将树以中点为根定型，求解 mx 和 cnt 
	fa[u]=las;
	mx[u]=cnt[u]=1;
	for(int v:e[u]){
		if(v==las)continue;
		redfs(v,u);
		if(mx[u]<mx[v]+1){
			mx[u]=mx[v]+1;
			cnt[u]=cnt[v];
		}else if(mx[u]==mx[v]+1)cnt[u]=(cnt[u]+cnt[v])%mod;
	}
}
inline void find(int &x){
	x=1;
	for(int i=2;i<=n;i++)
		if(dis[x]<dis[i])
			x=i;
}
void solve(int u,int las,int value){//将 u 这棵子树最长链上所有点的 +val 
	val[u]=(val[u]+1ll*value*cnt[u])%mod;//u 肯定在最长链上 
	for(int v:e[u]){
		if(v==las)continue;
		if(mx[v]+1==mx[u])solve(v,u,value);
	}
}
inline int cal(int val){
	return k==1?val:1ll*val*val%mod;
}
signed main(){
	read(n),read(k);
	if(n==2){
		write(2);
		exit(0);
	}
	for(int i=2,u,v;i<=n;i++){
		read(u),read(v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0,0);
	find(a);
	dis[a]=1;
	dfs(a,0,1);
	find(b);
	len=dis[b];
	int mid=(len+1)/2,now=b,tmp=1;
	while(now){
		if(tmp==mid){
			p=now;
			break;
		}
		now=fa[now],tmp++;
	}
	redfs(p,0);
	if(len&1){//长度是奇数 
		int tot=0;
		for(int v:e[p])if(mx[v]==len/2)tot+=cnt[v];
		for(int v:e[p]){
			if(mx[v]==len/2){
				solve(v,p,tot-cnt[v]);
				val[p]=(val[p]+1ll*(tot-cnt[v])*cnt[v]%mod)%mod;
			}
		}
		val[p]=1ll*val[p]*499122177%mod;
	}else{//长度是偶数 
		int tot1=0,tot2=0;
		for(int v:e[p]){
			if(mx[v]==len/2)tot1=cnt[v];
			else if(mx[v]==len/2-1)tot2+=cnt[v];
		}
		for(int v:e[p]){
			if(mx[v]==len/2-1)solve(v,p,tot1);
			else if(mx[v]==len/2){
				solve(v,p,tot2);
				val[v]=1ll*tot1*tot2%mod;
			}
		}
		val[p]=1ll*tot1*tot2%mod;
	}
	for(int i=1;i<=n;i++)ans=(ans+cal(val[i]))%mod;
	write(ans);
}
```

---

## 作者：Hilaria (赞：2)

### 题意

给你一棵树 $G$，定义树上一点 $x$ 的价值 $v_x$ 为该点被树的直径覆盖的次数，求 $\sum\limits_{x \in G}{v_x^k}$ 对 $998244353$ 取模的值，其中 $k$ 是给定的常数，且 $k \in [1,2]$。

---

### 思路

这题乍一看还蛮玄乎的哈，~~根本不会做啊~~，但是我们再仔细一瞅，我们会惊奇地发现：**极远点对**的定义其实就是把树的直径换个说法讲吗。那么 $v_x$ 也可以换一个简单的说法，就是这个 $x$ 点被树的直径覆盖的次数嘛。

那这个覆盖次数怎么求更好捏，这就要提到一个有关于树的直径的性质了，那就是若树上所有边边权均为正，则树的所有直径中点重合。那也就是说不管这些直径在哪里，它们的中点都恒过同一个点。

所以我们可以先跑两次 dfs 把树的直径和树的直径的中点求出来，然后以这个中点为树的根，一次 dfs 算出每个点向下能延伸的最长长度 $maxx[i]$（依题意这个长度指点数）以及这种长度的有多少条 $num[i]$。

如这张图，2 号点是中点，那么 $maxx[1]=3,num[1]=2$

![](https://cdn.luogu.com.cn/upload/image_hosting/u6z63lb2.png)

然后再跑一次 dfs 把除中点外所有点的 $v$ 算出来，最后再把中点的 $v$ 算出来，注意这里要分类讨论。

当直径为奇数个点时，中点只有一个。此时中点的孩子的 $maxx$ 应该都是一样的。

但是当直径为偶数个点时，如上图，中点既可以是 2，也可以是 1。此时中点的孩子中，会有且仅有一个孩子的 $maxx$ 比其他孩子大 1。这时经过中点的直径数量就应该是这个特殊的
孩子的 $num$ 与其他孩子的 $num$ 的乘积。

---

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXX=5e6+10;
const int MOD=998244353;

int n,k;
int head,tail,mid;
vector<int> nodes[MAXX];
int rt;
ll dist[MAXX],fa[MAXX];	//边数 

void dfs(int p,int f)
{
	fa[p]=f;
	if(dist[p]>dist[rt]) rt=p;
	int len=nodes[p].size();
	for(int i=0;i<len;i++)
	{
		int child=nodes[p][i];
		if(child==f) continue;
		dist[child]=dist[p]+1;
		dfs(child,p);
	}
}

ll num[MAXX];		//最长叶子节点数量
ll maxx[MAXX];		//最长叶子节点深度
ll val[MAXX];		//价值 
void dfs2(int p,int f)
{
	maxx[p]=1;
	num[p]=1;
	int len=nodes[p].size();
	for(int i=0;i<len;i++)
	{
		int child=nodes[p][i];
		if(child==f) continue;
		dfs2(child,p);
		if (maxx[p]<maxx[child]+1)
		{
			maxx[p]=maxx[child]+1;
			num[p]=num[child];
		}
		else if (maxx[p]==maxx[child]+1)
		{
			num[p]+=num[child];
		}
	}
}
ll tot1,tot2;
ll ans;
void dfs3(int p,int f,int w)
{
	if(k==1) ans=(ans+w*num[p]%MOD)%MOD;
	else ans=(ans+w*num[p]%MOD*w%MOD*num[p]%MOD)%MOD;
	//处理孩子	
	int len=nodes[p].size();
	for(int i=0;i<len;i++)
	{
		int child=nodes[p][i];
		if(child==f||maxx[child]!=maxx[p]-1) continue;
		dfs3(child,p,w);
	}
}

int main()
{
//	cin>>n>>k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		nodes[u].push_back(v);
		nodes[v].push_back(u);
	}
	if(n==1)
	{
		cout<<0;
		return 0;
	}
	if(n==2)
	{
		cout<<2;
		return 0;
	}
	
	dist[1]=0;
	dfs(1,0);
	head=rt;
	dist[head]=0;
	dfs(head,0);
	tail=rt;

	mid=tail;
	while(dist[mid]>dist[tail]/2) mid=fa[mid];
	dfs2(mid,0);
	int len=nodes[mid].size();
	for(int i=0;i<len;i++)
	{
		int child=nodes[mid][i];
		if(maxx[child]==dist[tail]/2) tot1+=num[child];
		else if(maxx[child]>dist[tail]/2) tot2+=num[child];
	}
	ll c_n=0;
	if(dist[tail]%2==0)
	{
		for(int i=0;i<len;i++)
		{
			int child=nodes[mid][i];
			if(maxx[child]==dist[tail]/2)
			{
				val[child]=tot1-num[child];
			}
		}
		ll tmp=tot1;
		for(int i=0;i<len;i++)
		{
			int child = nodes[mid][i];
			if (maxx[child]!=dist[tail]/2) continue;
			tmp -= num[child];
			c_n += (num[child] * tmp) % MOD;
			c_n %= MOD;
		}
	}
	else
	{
		for(int i=0;i<len;i++)
		{
			int child=nodes[mid][i];
			if(maxx[child]>dist[tail]/2) val[child]=tot1;
			else if(maxx[child]==dist[tail]/2) val[child]=tot2;
		}
		c_n = (tot1 * tot2) % MOD;
	}
	for(int i=0;i<len;i++)
	{
		int child=nodes[mid][i];
		if(maxx[child]>=dist[tail]/2)
		{
			dfs3(child,mid,val[child]);
		}
	}
//	cout<<"c_n:"<<c_n<<"\n";
	if(k==1) ans=(ans+c_n)%MOD;
	else ans=(ans+c_n*c_n%MOD)%MOD;
	printf("%lld",(ans%MOD+MOD)%MOD);

	return 0;
}
```


---

## 作者：_Vix_ (赞：2)

[原题链接](https://www.luogu.com.cn/problem/P8981)

## 前言

作为验题人，感觉是挺有意思的一道题，从题目转化到完成这道题都是循序渐进的。这道题也不怎么卡常，跑下来最慢的点差不多 $1.1s$。

这里分享一种**不用树形 DP** 的做法。 ~~（wtcl）~~

## 题意
给定一棵 $n$ 个节点的树，求每个点被直径穿过的次数的 $k$ 次方之和。

## 分析
下面有两个简单的结论。

**结论 1：** 一定**存在**一个点 $p$ 被所有直径穿过。

证明：考虑反证法。假如现在有两条直径 $a \rightarrow b$ 和 $c \rightarrow d$ 不相交，且分别穿过 $p_1$ 和 $p_2$ (可以结合下图，灵魂画手)。那么路径 $b \rightarrow p_1 \rightarrow p_2 \rightarrow c$ 显然更长，所以路径 $a \rightarrow b$ 和 $c \rightarrow d$ 不是直径。因此没有两条直径不相交，所有直径一定交于一点。

UPD：我的证明比较感性，更完整的证明可以参考[这个](https://oi-wiki.org/graph/tree-diameter/)。

![](https://cdn.luogu.com.cn/upload/image_hosting/7ximh5nb.png)

**结论 2：** 所有直径都是由从 $p$ 出发的最长链和次长链组成。（ $p$ 是被所有直径穿过的一点）

证明显然。

现在我们再来看这道题（下面的分析均在树有最长链和次长链的情况下）。首先找到点 $p$，以 $p$ 为树根，记录每个点 $u$ 的最长链个数和长度分别为 $cnt_u$ 和 $len_u$，特别地，记录 $p$ 的最长链和次长链的个数分别为 $num_1$ 和 $num_2$。

那么怎么统计每个点被直径穿过的次数呢？我们考虑所有的叶节点，如果一个叶节点在直径上，要么是在最长链上，与所有次长链构成直径，它的答案就是 $num_2$；要么是在次长链上，同理，它的答案就是 $num_1$。最后向上合并答案，点 $p$ 的答案算重复了，要除以 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/yjh1mdfo.png)

再考虑一种特殊的情况：这棵树只有最长链。

结合下图，在最长链上的叶节点的答案就是 $num_1 - cnt_u$。

![](https://cdn.luogu.com.cn/upload/image_hosting/b5lgn12r.png)

至此，每一个点被直径穿过的次数都被求了出来，按照题目求 $k$ 次方和就行了。

时空复杂度均为 $O(n)$，是优秀的线性做法。

UPD：忘记了一个特殊情况被 hack 了，感谢。如果还有 hack 数据可以私信我。（时隔太久，已经快要忘记当初写的什么东西了）

还有一种特殊情况就是只有最长链且对应的 $p$ 的儿子只有一个，那么最长链上的叶节点的答案就是 $1$，向上合并就行了，且 $p$ 的答案没有算重复，不用除以 $2$。

## 注意

1. 取模要勤快，不然后面的大数据会爆掉。
2. 分情况讨论答案。

## Code
由于代码又丑又长，就贴在[剪贴板](https://www.luogu.com.cn/paste/dc48z7d1)了。有什么错误还请 dalao 在评论区指出。

---

## 作者：SudoXue (赞：0)

[更好的阅读体验](https://www.cnblogs.com/xueruhao/p/18989169)

集训习题。特别地，让我们膜拜一下教练 [zmwang](https://www.luogu.com.cn/user/33653)。

对极远点对的理解是关键：设树的直径长度为 $d$，任意互为最远点的无序点对恰好是所有直径端点对。两次 BFS 求得一条直径 $(s,t)$ 并记录整条路径即可得到 $d$。

若 $d=2L$ 为偶数，则直径唯一中心是顶点 $c$。所有直径端点都在深度 $L$ 的叶子，且必位于 $c$ 的不同一级子树中；同一子树内部两叶间距离最多为 $d-2$ 不可能再是直径。令 $S_x$ 表示结点 $x$ 的子树里端点数，$T=S_c$；对非中心结点 $x$，端点对必须一端在 $x$ 的子树，另一端在不同一级子树内，记 $top_x$ 为 $x$ 所属的一级子树根，则结点贡献为 $v_x=S_x\bigl(T-S_{top_x}\bigr)$。对中心结点自身，需要在不同一级子树之间任选两端点组合，按前缀累加可在线性时间算出 $v_c$。

若 $d=2L+1$ 为奇数，则中心是一条边 $(c_0,c_1)$。所有直径端点必分列此边两侧，且深度分别为 $L$ 与 $L+1$。对每个结点统计其子树内 A 侧端点数 $A_x$ 与 B 侧端点数 $B_x$。两中心自身贡献为 $A_{c_0}\cdot B_{c_0}$。若 $x$ 在 A 侧且非中心，直径要穿过 $x$ 必须另一端在整条 B 侧，于是 $v_x=A_x\cdot B_{c_0}$；B 侧对称。

用一次深搜自底向上传递计数。输出要求是 $\sum_x v_x^k\pmod{998244353}$；遍历所有结点累加，$k=1$ 直接相加，$k=2$ 先平方再相加即可。

时间复杂度 $O(n)$。

[link](https://www.luogu.com.cn/record/224946940)

---

