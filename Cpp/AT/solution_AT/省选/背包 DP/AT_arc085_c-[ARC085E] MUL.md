# [ARC085E] MUL

## 题目描述

有 $N$ 个宝石，编号为 $1, 2, .., N$

你可以进行任意次以下操作（可以一次也不做）

- 选择一个正整数 $x$，将所有编号为 $x$ 的倍数的宝石打碎

最后，对于每个没有被打碎的宝石 $i$，你可以获得 $a_i$ 円。要注意的是，有些 $a_i$ 是负值，这意味着你要倒贴钱。

在最好的情况下，你能获得多少円呢？

## 说明/提示

所有输入的数都是整数

$1 \leq N \leq 100$

$ |a_i| \leq 10^9$

## 样例 #1

### 输入

```
6
1 2 -6 4 5 3```

### 输出

```
12```

## 样例 #2

### 输入

```
6
100 -100 -100 -100 100 -100```

### 输出

```
200```

## 样例 #3

### 输入

```
5
-1 -2 -3 -4 -5```

### 输出

```
0```

## 样例 #4

### 输入

```
2
-1000 100000```

### 输出

```
99000```

# 题解

## 作者：big_news (赞：7)

这题居然是绿的？？！

### 正解：最大流+最大权闭合子图

**初步分析**

先不妨称砸掉宝石为筛去一个数值。设筛去的总权值为$v$，获得的利益为$w$，则有$w=\sum\limits_{i=1}^n a_i -v$。显然，$v$越小，$w$越大，得到的答案越优。

也就是说，要让删除的数之和最小。

**问题的转化**

考虑我们删除一个数的条件。删掉第$k$个数，必须要将编号为$2\times k,3\times k,...,ik(ik\leqslant n)$的数一起删掉。
不妨从编号为$k$的数向编号为$k$的倍数的数$ik$连一条有向边，那么我们会得到一张图。现在再分析删除一个数的条件：即是将从该节点所能到达的所有节点删除。那么这时候就可以引入一个新的概念：闭合子图。

- 闭合子图：在一张图中选出一些节点，它们及从它们所能到达的所有节点组成原图的的一张闭合子图。

同时这张图上每个节点都是有权值的（即问题中宝石的价值），我们要让选出的闭合子图权值最小。那么问题转化成了在我们所建的图中，求出最小权闭合子图。

**网络流模型**

先抛开最小权闭合子图。

我们知道最大权闭合子图的网络流模型：将图中所有正权节点与源点$s$相连，所连边的流量限制为节点权值；所有负权节点与汇点$t$相连，所连边的流量限制为节点权值的相反数（绝对值）；图上原有边的流量限制为$\infty$。设$s\to t$的最小割（最大流）的大小为$g$，则最大权闭合子图的权值和为$\sum\limits_{1\leqslant i\leqslant n}^{a_i>0}a_i - g$。
说得像人话一点，就是图上所有正权值之和减最小割。

以上结论我并不会证明，但是它是对的。好了，剩下的问题是用这个模型求出“最小权闭合子图”。

不妨将节点权值全部乘上$-1$，套用上面的模板，那么我们求出来的最大权闭合子图即是最小权闭合子图大小的相反数。设最小权闭合子图大小为$s$，则有$s = -(-\sum\limits_{1\leqslant i\leqslant n}^{a_i<0}a_i - g)$，即图上所有负权值的绝对值之和减最小割。

设最优解为$f$，则有$f = \sum\limits_{i=1}^na_i - s = \sum\limits_{i=1}^na_i +(-\sum\limits_{1\leqslant i\leqslant n}^{a_i<0}a_i - g)$。好了，问题解决了。

用Dinic求出这个$g$，注意，`long long`不要忘开，边数开多一点，然后千万别写当前弧优化！

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
using namespace std;

#define LL long long

const int CP=110;
const int CE=CP*CP*20;

const LL INF=0x3f3f3f3f3f3f3f3f;

LL read(){
    LL s=0,ne=1; char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') ne=-1;
    for(;c>='0'&&c<='9';c=getchar()) s=(s<<1)+(s<<3)+c-'0';
    return s*ne;
}

class fs{
  public:
  	int from,to,nxt; LL cap,flow;
  	void init(int f,int t,int n,LL c,LL fl)
  	{from=f;to=t;nxt=n;cap=c;flow=fl;}
}E[CE];
int hd[CP],ecnt=1;
void add(int x,int y,LL z){
    E[++ecnt].init(x,y,hd[x],z,0);
    hd[x] = ecnt;
    E[++ecnt].init(y,x,hd[y],0,0);
    hd[y] = ecnt;
}

//v define
int n;
LL a[CP];
void copy(int *a,int *b,int pos,int sz){
    for(int i=pos;i<pos+sz;i++) b[i] = a[i];
}

//dinic
int dep[CP];
bool build(int s,int t){ //构造分层图 
    memset(dep,0,sizeof(dep));
    dep[s] = 1;
    
    queue<int> Q;
    Q.push(s);
    
    while(!Q.empty()){
        int u = Q.front();
        Q.pop(); 
        
        for(int k=hd[u]; k; k=E[k].nxt){
            int v = E[k].to;
            if(!dep[v] && E[k].cap-E[k].flow>0){
                dep[v] = dep[u]+1;
                Q.push(v);
            }
        }
    }
    
    return dep[t];
}
LL augment(int u,int t,LL rst){ //多路增广 
    if(u == t) return rst;
    
    LL used = 0;
    for(int k=hd[u]; k; k=E[k].nxt){
        fs &e = E[k];
        
        if(dep[e.to] == dep[u]+1){
            LL a = augment(e.to,t, min(rst-used,e.cap-e.flow));
            if(a){
                used += a;
                E[k].flow += a;
                E[k^1].flow -= a;
                if(used == rst) return rst;
            }
        }
    }
    
    return used;
}
LL mf(int s,int t){ //最大流
    LL _mf = 0;
    while(build(s,t))
        _mf += augment(s,t,INF);
    return _mf;
}

int main()
{
    n = read();
    for(int i=1;i<=n;i++)
        a[i] = read();
        
    for(int i=1;i<=n;i++)
        for(int k=2;i*k<=n;k++)
            add(i,i*k,INF); //原图内的边
    int s = n+1,t = n+2;
    for(int i=1;i<=n;i++)
        if(a[i] > 0) add(i,t,a[i]); //反着连边，搞不懂自己推一推
            else add(s,i,-a[i]);
    
    LL sum = 0,sigma = 0;
    for(int i=1;i<=n;i++) //求负权的绝对值之和 
        if(a[i] < 0) sigma -= a[i];
    for(int i=1;i<=n;i++)
        sum += a[i];
    
    printf("%lld",sum+(sigma-mf(s,t)));	
            
    return 0;
}
```

蒟蒻的博客推广：[big-news' Blog](https://big-news.cn/)

$$ - - - - \mathcal{End} - - - -  $$

---

## 作者：一念之间、、 (赞：4)

# 题意
$n\le100$ 选择一些 $x$ 然后对于 $x$ 的倍数将其标记为不合法，问最大化未标记权值的总和。

# 题解
这边介绍一个 dp 求解的方式。

观察 $n$ 很小，尝试规约问题进行状压求解。

发现对于 $>{n\over2}$ 的元素直接将其价值与 0 取 max 。

我们的想法是考虑状压前 $25$ 个元素，然后对于后面的元素分类讨论解决。

粗略估计有 $2^{25}=33554432$ 个状态，跑一个爆搜，对于实际有用的状态只有 $109297$ 个，这边称一个状态是有用的，当且仅当不存在一个元素被选择，而他的因子也被选择。

考虑进一步的讨论，对于元素在 $26\sim 50$ 的时候，我们发现这些元素的 $2$ 倍就已经超过 ${n\over2}$ 的范围了，所以对于这些元素分组尝试进行一个 dp，具体的，对于 $i,i\times2,i\times3$ 分为一组，对于$i\times2,i\times3$ 我们在 $i$ 位置对其进行决策，因为如果将 $i$ ban掉只会影响这两个位置。

再进一步的，我们发现此时有一些小小的瑕疵，即对于存在 $26\sim 50$ 时，$i\times 3=t\times2$，此时这两个元素会有相互影响。

发现只会有这样的情况，我们将这两个元素同时拿出来进行讨论选择情况即可。

复杂度：$O(n\times109297+n\times109297*25)$ 非常不满，瓶颈在于预处理。

# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define dd double
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
//#define getchar gc
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(ll x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(ll x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x);pc(op,0);
}
int to[33554432+2];
//128MB
//本质上只有1e5个不同的！ 
//做一个映射吧,先考虑dfs的过程了 
//本质上只有109297个 
bool check(int x,int y)
{
	for(int i=1;i<=25;i++)
		if((y>>(i-1)&1)&&x%i==0)return 0;
	return 1;
}
int ty[109299],ct;
void dfs(int x,int now)
{
//	cout<<x<<" "<<now<<"ASD\n";
	if(x==26)
	{
//		to[now]=++ct;
		ty[++ct]=now;
		return;
	}
	if(check(x,now))dfs(x+1,now+(1<<(x-1)));
	dfs(x+1,now); 
}
const int xx=105;
int n,a[xx];
ll f[109299];
bitset<109299>ck[xx];
int vis[xx*xx];
int main(){
//	freopen("a.in","r",stdin);
	//1取min，2分组，3dp 
	dfs(1,0);
	sort(ty+1,ty+ct+1);//从小到大 
	for(int i=1;i<=ct;i++)to[ty[i]]=i;
	for(int i=1;i<=100;i++)for(int j=1;j<=ct;j++)ck[i][j]=check(i,ty[j]);
	//简单的预处理一下 
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n/2+1;i<=n;i++)a[i]=max(a[i],0);
	memset(f,-0x3f,sizeof(f));
	f[1]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=ct;j>=1;j--)//有钦定的话顺序变大 
		{
			if(f[j]<-1e18)continue;
			if(vis[i])continue;//已经被做了选择了。 
			if(i<=25)
			{
			//否则暂时不变 
			//考虑ban的时候的情况 
			//没啥顺序的/fn 
				if(ck[i][j])f[to[ty[j]+(1<<(i-1))]]=max(f[to[ty[j]+(1<<(i-1))]],f[j]);//ban了 
				if(ck[i][j])f[j]+=a[i];//不ban强制加 
				
			}
			if(26<=i&&i<=50)
			{
				//两两一组 
				//他会有*3哦！ 
				//那就3个一组。 
				//因为*2就超了 
				if(i*3<=n&&i*3%2==0)
				{
					//讨论i与i*3/2的选取情况 
					//首先ban完的情况=fj 
					assert(a[i*2]>=0);
					assert(a[i*3]>=0);
					ll ls=f[j];
					if(ck[i][j]&&ck[i*3/2][j])
					{
						//这里发现了，说不能单判2,3！ 
						if(ck[i*2][j]&&ck[i*3][j])f[j]=max(f[j],ls+a[i]+a[i*3/2]+a[i*2]+a[i*3]);
						//那是他的2啊！ 
						if(ck[i*2][j])f[j]=max(f[j],ls+a[i]+a[i*3/2]+a[i*2]);
						if(ck[i*3][j])f[j]=max(f[j],ls+a[i]+a[i*3/2]+a[i*3]);
						f[j]=max(f[j],ls+a[i]+a[i*3/2]);
						f[j]=max(f[j],ls+a[i*3/2]);
						f[j]=max(f[j],ls+a[i]);
						if(ck[i*2][j])f[j]=max(f[j],ls+a[i]+a[i*2]);
					}
					if(!ck[i][j]&&!ck[i*3/2][j]);
					else 
					if(!ck[i][j])
						f[j]=max(f[j],ls+a[i*3/2]);
					else if(!ck[i*3/2][j])
					{
						f[j]=max(f[j],ls+a[i]);
						if(ck[i*2][j])f[j]=max(f[j],ls+a[i]+a[i*2]);
					}
					//有一边没有/ban这边 
					vis[i*3]=vis[i*2]=vis[i*3/2]=1;
				}
				else 
				{
					ll val=a[i];
					if(i*2<=n)val+=a[i*2];
					if(i*3<=n)val+=a[i*3];
					if(!ck[i][j]);
					else 
					{
						if(!ck[i*2][j]&&!ck[i*3][j])f[j]=max(f[j],f[j]+a[i]);//不ban，但是上面遭了 
						else if(!ck[i*3][j])
						{
							if(i*2<=n)f[j]=max(f[j],f[j]+a[i]+a[i*2]);
							else f[j]=max(f[j],f[j]+a[i]);
						}
						else if(!ck[i*2][j])
						{
							if(i*3<=n)f[j]=max(f[j],f[j]+a[i]+a[i*3]);
							else f[j]=max(f[j],f[j]+a[i]);
						}
						else f[j]=max(f[j],f[j]+val);
						//默认可ban，ban了较大的就不作选择了。 
					}
					//还有一些个同时分组的/fn 
					//讨论一下了！ 
					vis[i*2]=1;
					vis[i*3]=1;
				}
			}
			if(50<i)
			{
				assert(a[i]>=0);
				//不拿白不拿。 
				if(ck[i][j])f[j]+=a[i];
				//否则不变 
			}
		}
	}
	ll ans=-1e18;
	for(int i=1;i<=ct;i++)ans=max(ans,f[i]);
	cout<<ans<<'\n';
//	vector<int>ans;
//	for(int i=0;i<33554432;i++)
//	{
//		vector<int>v;
//		for(int j=1;j<=25;j++)
//			if(i>>(j-1)&1)v.push_back(j);
//		int cr=1;
//		for(int i=0;i<v.size();i++)
//		for(int j=i+1;j<v.size();j++)if(v[j]%v[i]==0)cr=0;
//		if(cr)ans.push_back(i);
//	}
//	cout<<ans.size()<<"\n";
//	for(auto it:ans)cout<<it<<" ";
//	puts("");
	pc('1',1);
	return 0;
}
```




---

## 作者：shenmadongdong (赞：4)

注意到这题 $N$ 很小，所以可以考虑乱搞

我们从后往前考虑，有一个非常 naive 的贪心，就是如果它的倍数编号的宝石的价值总和为负数，就把它们全部打碎，否则就不打碎

然后可以发现这个贪心随便搞搞就能 hack 掉。。。

但我们可以引入随机化，如果它的倍数编号的宝石的价值总和为负数，就极大概率把它们全部打碎，否则就极大概率不打碎，这样重复个许多遍对答案取最大值

事实证明这样跑出来基本上都是对的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[170],b[170],sum,ans=-1e18;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>b[i];
    int T=1e5;
	while(T--)
	{
		for(int i=1;i<=n;i++) a[i]=b[i];
		for(int i=n;i;i--)
		{
			sum=0;
			for(int j=1;j<=n/i;j++) sum+=a[j*i];
			if ((sum<=0)^(rand()%13==0)) for(int j=1;j<=n/i;j++) a[j*i]=0;
		}
		sum=0;
        for(int i=1;i<=n;i++) sum+=a[i];
		ans=max(ans,sum);
	}
	cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：zhuzhu2891 (赞：2)

我们发现 $N$ 很小，考虑爆搜。

一个朴素的想法是从前往后枚举每一个数要不要把它的倍数去掉。如果一个数已经被去掉，那么显然它的倍数已经都被去掉，再枚举它是不需要的。

然后我们发现这个东西 T 得死死的。

我们发现，当搜到一个大于 $50$ 的数时，它没有除自己以外的倍数，因此可以直接决定。

然后我们发现这个东西还是 T 得死死的。

我们继续发现，当搜到一个在 $(33,50]$ 中的数，只有一个除自己以外的倍数，可以直接讨论它自己以及两倍它自己是否要被操作。

然后我们发现这个东西还是以稳稳的 $1.1s$ 过去了。

代码：

```cpp
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#define f first
#define s second
#define ll long long
#define mp make_pair
#define pll pr<ll,ll>
#define pii pr<int,int>
#define piii pr<int,pii>
using namespace std;
ll a[102];
int cnt[102];
bool pr[102];
bool sp[102];
bool dd[102];
int c;
ll sc(int i)
{
	if(i==101) return 0;
	if(cnt[i]>0) return sc(i+1);
	if(i>50) if((i&1)||i<=66) return max(0ll,a[i])+sc(i+1);
	else return sc(i+1);
	if(i>33) if(cnt[i*2]) return max(0ll,a[i])+sc(i+1);
	else return max(max(0ll,a[i]),a[i]+a[i*2])+sc(i+1);
	ll mx=0;
	for(int j=i*2;j<=100;j+=i) cnt[j]++;
	mx=max(mx,sc(i+1));
	for(int j=i*2;j<=100;j+=i) cnt[j]--;
	return max(mx,a[i]+sc(i+1));
}
int main()
{
	ios_base::sync_with_stdio(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cout<<sc(1)<<endl;
	return 0;
}
```

---

## 作者：CHU2 (赞：2)

第一篇题解说求最大流并不准确，要求的其实是最小割，因为 最小割=最大流 所以就转化成最大流了。

然后第一篇题解还没证明，于是我来证一下这个建图求最小割的正确性。

设$S$连所有正权点，流量为权值，$T$连所有负权点，流量为权值的绝对值，关系边流量为$inf$

你考虑最小割割的是个什么东西：关系边的流量为$inf$不能割，所以能割的就是连接$S$的边和连接$T$的边。

再考虑割边的意义是啥：每割一条与$S$相连的边，就代表不选一个正权点，割一条与$T$相连的边，就代表选了一个负权点，貌似挺对

那为什么最后要求最小割呢？如果还存在一条$S\rightarrow T$的路径，就说明和$T$最近的那个点，它的前驱选了但它没有选，这不符合最大权闭合子图的定义。

所以要求的就是最小割了。

你谷没有代码不让过题解，就放个代码吧
```cpp
#include <bits/stdc++.h>
#define N 110
#define ll long long
#define For(i,x,y) for(int i=(x);i<=(y);++i)
#define Rof(i,x,y) for(int i=(x);i>=(y);--i)
#define Edge(x) for(int i=head[x],to=e[i].v;i;i=e[i].nxt,to=e[i].v)
#define Cur(x) for(int &i=cur[x],to=e[i].v;i;i=e[i].nxt,to=e[i].v)
#define mset(x,y) memset(x,y,sizeof(x))
using namespace std;
const int S=0,T=102;
int dep[N],n,head[N],cur[N],cnt=1,a[N];
queue<int> q;
struct ed{ int v,nxt;ll f; }e[N*32];
void add(int u,int v,ll f){
	e[++cnt]=(ed){v,head[u],f},head[u]=cnt;
	e[++cnt]=(ed){u,head[v],0},head[v]=cnt;
}
bool bfs(){
	while(!q.empty()) q.pop();
	For(i,0,T) cur[i]=head[i],dep[i]=0;
	dep[S]=1,q.push(S);
	while(!q.empty()){
		int x=q.front();q.pop();
		Edge(x) if(!dep[to] && e[i].f) dep[to]=dep[x]+1,q.push(to);
	}
	return dep[T];
}
ll dfs(int x,ll f){
	if(x==T) return f;
	ll use=0;
	Cur(x){
		if(dep[to]==dep[x]+1 && e[i].f){
			ll o=min(f-use,e[i].f);
			ll w=dfs(to,o);
			use+=w,e[i].f-=w,e[i^1].f+=w;
			if(f==use) return f;
		}
	} return use;
}
int main(){
	ll ans=0,sum=0;
	scanf("%d",&n);
	For(i,1,n) scanf("%d",&a[i]),a[i]=-a[i];
	For(i,1,n) for(int j=2*i;j<=n;j+=i) add(i,j,(ll)1e18);
	For(i,1,n){
		if(a[i]>0) add(S,i,a[i]);
		else add(i,T,-a[i]),sum+=-a[i];
	}
	while(bfs()) ans+=dfs(S,(ll)1e18);
	printf("%lld\n",sum-ans);
}
```




---

## 作者：swiftc (赞：0)

设 `solve(S)` 为只考虑 $S$ 这个集合内数时的答案，我们将每一个数向它的倍数连边建出一张无向图，容易发现如果这张图不连通每一个连通块是互不影响的（因为无论怎么选都不会导致另一个连通块内的点被删除），于是可以枚举最小的数选不选，如果删除之后不连通就分别调用 `solve` 解决，感性理解一下可以发现在较小的数都被决策完之后图上的连通块不可能十分大，这种做法在 $n \le 100$ 时可以在较短的时间内通过。

```cpp
#include <bits/stdc++.h>
#define N 110
#define ll long long
using namespace std;
int n, val[N], vis[N];
vector<int> v[N];
ll solve(vector<int> c) {
  if (c.empty())
    return 0;
  for (auto x : c)
    vis[x] = 1;
  queue<int> q;
  vis[c.front()] = 0, q.push(c.front());
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (auto to : v[x]) {
      if (vis[to]) {
        vis[to] = 0;
        q.push(to);
      }
    }
  }
  vector<int> a, b;
  for (auto x : c) {
    if (!vis[x]) {
      if (x != c.front())
        a.push_back(x);
    } else
      vis[x] = 0, b.push_back(x);
  }
  vector<int> tmp;
  for (auto x : a)
    if (x % c.front())
      tmp.push_back(x);
  return solve(b) + max(solve(tmp), solve(a) + val[c.front()]);
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> val[i];
  for (int i = 1; i <= n; i++)
    for (int j = 2; i * j <= n; j++)
      v[i].push_back(i * j), v[i * j].push_back(i);
  vector<int> c;
  for (int i = 1; i <= n; i++)
    c.push_back(i);
  cout << solve(c) << '\n';
  return 0;
}
```

---

## 作者：_edge_ (赞：0)

我不会最大流，我不会 DP，我没有脑子不能发现任何性质。

咋办呢？

退火！

我们先考虑一个问题，确定了一个 $01$ 序列，及当前某些倍数的点是否要取的时候就可以在 $O(n \log n)$ 的时间内 check 出答案。

具体的 check 方法是把他和他倍数的都染色标记一下就没了。

然后我们用模拟退火来确定该 $01$ 序列。

模拟退火的大致思想就是随机找一个点然后更改掉，由于答案应该是若干峰的，所以他更改一次会变优也有可能变劣，这时候再进行一次 check，和当前最优答案比较，如果比较比他优则代替，否则的话就需要估价了。

具体的，当温度比较低的时候就不返回，当差值比较大的时候也不返回。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
int n,m,cnt,vis[INF],a[INF],P[INF],ans1;
int check() {
	cnt++;
	for (int i=1;i<=n;i++) {
		if (!vis[i]) continue;
		for (int j=i;j<=n;j+=i) P[j]=cnt;
	}
	int ans=0;
	for (int j=1;j<=n;j++)
		if (P[j]!=cnt) ans+=a[j];
	return ans;
}
void SA() {
	for (int i=1;i<=n;i++) vis[i]=rand()%2;
	double T=2008;int res=check();
	while (T>=1e-15) {
		int x=rand()%n;
		vis[x]^=1;
		int now=check();
		if (res<now) res=now;
		else if (exp(res-now)/T*RAND_MAX>rand()) vis[x]^=1;
		T*=0.997;
	}
	ans1=max(ans1,res);
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	srand(20080209);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	while (clock()<CLOCKS_PER_SEC*1.95) SA();
	cout<<ans1<<"\n";
	return 0;
}
```


---

