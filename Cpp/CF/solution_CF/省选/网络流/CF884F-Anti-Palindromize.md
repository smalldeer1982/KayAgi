# Anti-Palindromize

## 题目描述

对于一个字串 $a$，若其长度 $m$ 为偶数，且对于 $\forall i \in[1,m]$，有 $a_i \neq a_{m-i+1}$，则将其称为反回文串。

Ivan 有一个由 $n$ 个小写拉丁字母构成的字串 $s$，且 $n$ 为偶数。他想用 $s$ 的一些排列构成一些反回文串 $t$。同时他称 $i$ 的美丽值为 $b_i$，且字串 $t$ 的美丽值 $Ans=\sum_{i=1}^{len(s)} b_i[s_i=t_i]$。

请帮 Ivan 确定 $Ans$ 的最大值。

## 样例 #1

### 输入

```
8
abacabac
1 1 1 1 1 1 1 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
8
abaccaba
1 2 3 4 5 6 7 8
```

### 输出

```
26
```

## 样例 #3

### 输入

```
8
abacabca
1 2 3 4 4 3 2 1
```

### 输出

```
17
```

# 题解

## 作者：TLE_Automat (赞：7)

## [CF884F.Anti-Palindromize](https://codeforces.ml/contest/884/problem/F)

**题意：**

定义一个长度为 $x$ 的字符串 $t$ 是 **反回文串** ，需要满足以下条件：

- $x$ 是偶数。
- 对于任意的整数 $i\in [1,x]$ ，$t_{i} \neq t_{x-i+1}$ 。

现在给定一个长度为 $n$ 的字符串 $s$ 和一个长度为 $n$ 的序列 $b$ ，保证 $n$ 为偶数。

要求将 $s$ 的字符重新排列得到字符串 $t$ ，使得 $t$ 是反回文串，定义 $t$ 的价值为 $\sum_{i=1}^{n} b_i[s_i=t_i]$ 。

求字符串 $t$ 的最大价值。

**数据范围：**

$1\le n \le 100 , 1\le b_i \le 100$ 。

## 解法一：费用流

考虑把字符串 $s$ 重新排列不好想，不如直接把字符全都拿出来重新放。

我们先来分析以下把字符拿出来再重新放回去需要满足的条件：

1. 放回去之后，每个字符的出现次数必须跟 $s$ 中的一样。
2. 放回去之后 $t_i \neq t_{x-i+1}$ 。
3. 每个位置能且仅能放一个字符。
4. 价值最大。

那么现在我们对于每一个条件考虑一下建图的解决方案，约定 $(x,y)$ 代表容量为 $x$ ，费用 $y$ 的边：

1. 因为出现次数必须一样，可以考虑对于每一个字符建一个点，从源点向每个字符连一条 $(cnt_x,0)$ 的边，$cnt_x$ 为字符 $x$ 出现的次数。
2. 因为对应位置不能放相同的字符，可以考虑对于每一个字符，新建 $\frac{n}{2}$ 个点，这 $\frac{n}{2}$ 个点联系着 $\frac{n}{2}$ 个对应位置，每个点都向对应位置分别连一条 $(1,0)$ 的边，然后再从这个字符的点向新建的 $\frac{n}{2}$ 个点连 $(1,0)$ 的边，这样就保证了对应位置最多只放一个相同字符。
3. 把每个位置代表的点向汇点连 $(1,0)$ 的边，这样只要跑最大流保证满流，就能保证每个位置放且仅能放 $1$ 个字符。
4. 考虑什么时候字符的放置会对价值产生贡献，就是与原字符串 $s$ 在相同位置字符相同的时候会产生贡献，于是我们可以对第 $2$ 操作魔改一下，在放的字符与 $s$ 的相同位置上的字符相同时，费用改成 $b_{pos}$ ，$pos$ 为该位置。

然后我们跑最大费用最大流即可算出最大价值，但这么跑可能在 $\text{spfa}$ 的时候出现正权环挂掉。

于是我们先把所有位置的贡献加起来，然后在操作 $4$ 的时候考虑减掉放置的字符与 $s$ 的相同位置上的字符不相同时，扣除的贡献，这样就可以跑最小费用最大流，算减掉的最小的贡献。

$\text{Source} : $

```cpp
#include <bits/stdc++.h> // 字典树上字典游 , 字去树空网络流 

using namespace std;

#define SZ(x) ((int)((x).size()))
#define lb(x) ((x)&(-(x)))
#define mkp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=1e2+10;
const int MAXS=1e5+10;
const int inf=1e9;

struct Edge{ int to,nxt,w,c; };

int n,cnt_e=1,cnt_d,S,T;
char s[MAXN];
int b[MAXN];
int head[MAXS],curh[MAXS];
int dis[MAXS];
bool inq[MAXS];
Edge e[MAXS];

inline void addedge(int u,int v,int w,int c,bool fg)
{
	e[++cnt_e].to=v; e[cnt_e].w=w;
	e[cnt_e].nxt=head[u]; e[cnt_e].c=c;
	head[u]=cnt_e;
	if(fg) addedge(v,u,0,-c,false);
}

inline bool spfa()
{
	for(int i=1;i<=cnt_d;i++)
		curh[i]=head[i],
		dis[i]=inf;
		
	queue<int> q;
	dis[S]=0; q.push(S);
	inq[S]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		inq[u]=false;
		
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to,w=e[i].w,c=e[i].c;
			if(!w || dis[u]+c>=dis[v]) continue;
			dis[v]=dis[u]+c;
			if(!inq[v]) q.push(v),inq[v]=true;
		}
	}	
	return dis[T]!=inf;
}

int cost=0;
inline int dfs(int u,int flow)
{
	if(!flow || u==T) return flow;
	
	int res=0;
	inq[u]=true;
	for(int &i=curh[u];i;i=e[i].nxt)
	{
		int v=e[i].to,w=e[i].w,c=e[i].c;
		if(!w || dis[v]!=dis[u]+c || inq[v]) continue;
		int kkk=dfs(v,min(flow,w));
		
		e[i].w-=kkk; e[i^1].w+=kkk;
		flow-=kkk; res+=kkk;
		cost+=kkk*c;
		if(!flow) break;
	}
	inq[u]=false;
	
	return res;
}

inline int dinic()
{
	int res=0;
	while(spfa()) res+=dfs(S,inf);
	return res; 
}

int main()
{
	scanf("%d\n%s",&n,s+1);
	int ans=0;
	for(int i=1;i<=n;i++) scanf("%d",&b[i]),ans+=b[i];
	
	static int tot[26];
	for(int i=1;i<=n;i++) tot[s[i]-'a']++;
	
	cnt_d=n;
	S=n+26*n/2+26+1; T=S+1;
	static int dian[26];
	for(int i=0;i<26;i++)
	{
		dian[i]=++cnt_d;
		addedge(S,dian[i],tot[i],0,true);
		for(int j=1;j<=n/2;j++)
			addedge(++cnt_d,j,1,(s[j]-'a'==i ? 0 : b[j]),true),
			addedge(cnt_d,n-j+1,1,(s[n-j+1]-'a'==i ? 0 : b[n-j+1]),true),
			addedge(dian[i],cnt_d,1,0,true);
	}
	for(int i=1;i<=n;i++) addedge(i,T,1,0,true);
	cnt_d+=2; assert(cnt_d==n+26*n/2+26+2);
	
	dinic();
	printf("%d\n",ans-cost);
	 
	return 0;
}
```



## 解法二：贪心（参考于[官方题解](https://codeforces.ml/blog/entry/55470)）

考虑先令 $t = s$ ，此时我们的价值为能取到的最大值 $\sum_{i=1}^{n}b_i$ 。这时候，我们只需要考虑从里面扣掉最少的贡献，就能求出最大价值了。那么我们怎么扣掉最少的贡献呢？

显然，我们交换一些满足 $s_i=s_{n-i+1}$ 的位置 $i$ ，假设满足这一条件的 $(i,n-i+1)$ 的数对有 $m$ 对，现在我们想要最小化交换字符减少的贡献。假设需要交换的字符 $x$ 有 $cnt_x$ 个，我们可以分两种情况讨论：

- $\forall x , 2\cdot x \le m $ 。这样的话，我们只需要把这些成对中的其中一个字符互相换掉，减去成对中的贡献较小的一个字符的贡献，即可算出答案。
- $\exist x,2\cdot x > m$ 。显然，如果存在，那么最多只有一个 $x$ 。这时候，成对的字符互换不足以把字符 $x$ 全都换走，我们需要找不成对的字符去跟换不走的 $x$ 交换，这时候我们只要把所有的满足 $s_i\neq x , s_{n-i+1}\neq x ,s_i\neq s_{n-i+1}$ 的 $(i,n-i+1)$ 的位置的贡献从小到大排一下序，然后挨个取走贡献小的跟 $x$ 交换即可。

$\text{Source} : $

```cpp
#include <bits/stdc++.h> // 总为缩点能 AC , 贪心满分使人愁 

using namespace std;

#define SZ(x) ((int)((x).size()))
#define lb(x) ((x)&(-(x)))
#define mkp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=1e2+10;

int n;
int b[MAXN];
char s[MAXN];

int main()
{
	scanf("%d\n%s",&n,s+1);
	int sum=0;
	for(int i=1;i<=n;i++) scanf("%d",&b[i]),sum+=b[i];
	
	int m=0;
	static int tong[26];
	vector<int> vec;
	for(int i=1;i<=n/2;i++)
		if(s[i]==s[n-i+1])
		{
			m++;
			tong[s[i]-'a']++;
			vec.pb(min(b[i],b[n-i+1]));
		}
	
	bool fg=false;
	int ch=-1;
	for(int i=0;i<26;i++)
		if(2*tong[i]>m)
			ch=i,fg=true;
	
	int tot=0;
	for(int i=0;i<m;i++) tot+=vec[i];
	int ans=sum-tot;
	if(!fg)
	{
		printf("%d\n",ans);
		return 0;
	}
	
	vector<int> vec2;
	for(int i=1;i<=n/2;i++)
		if(s[i]!=s[n-i+1] && (s[i]-'a')!=ch && (s[n-i+1]-'a')!=ch)
			vec2.pb(min(b[i],b[n-i+1]));
	sort(vec2.begin(),vec2.end());
	
	for(int i=0;i<tong[ch]-(m-tong[ch]);i++)
		ans-=vec2[i];
	printf("%d\n",ans);
	
	return 0;
}
```







---

## 作者：yuzhechuan (赞：5)

提供一个不同的建图方法

---

### 题解：

建图目的是将26个字母分别匹配到每个位置上求贡献

对于字母数量的限制，我们可以对于每种字母建一个点，从源点向它连边，容量为该种字母的出现次数，无费用，表示源点能提供的字母的个数

每种字母在目标串的$i$和$n-i+1$上只能填一个，对于这个性质，我们建$\frac{n}{2}$个点，第$i$个点代表位置$i$和$n-i+1$

于是我们可以让每个字母点向位置点连边，容量为1（因为只能摆1个），费用为可以填的原字母的较大价值

因为一个位置点代表了两个位置，所以要从每个位置点向汇点连容量为2，无费用的边

最后跑一遍费用流就好啦

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=2005,M=5e5+5;
int en=1,h[N],dis[N],mc,mf,n,cnt[30],a[N];
char s[N];
bool v[N];

struct edge{
	int n,v,f,w;
}e[M<<1];

struct fafafa{
	int fa,id;
}pre[N];

void add(int x,int y,int f,int w){
	e[++en]=(edge){h[x],y,f,w};
	h[x]=en;
}

bool spfa(int s,int t){
	memset(v,0,sizeof v);
	memset(pre,0,sizeof pre);
	memset(dis,0x3f,sizeof dis);
	queue<int> q;
	q.push(s);
	v[s]=1;
	dis[s]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].n){
			int y=e[i].v;
			if(e[i].f&&dis[x]+e[i].w<dis[y]){
				dis[y]=dis[x]+e[i].w;
				pre[y]=(fafafa){x,i};
				if(!v[y]){
					v[y]=1;
					q.push(y);
				}
			}
		}
		v[x]=0;
	}
	return dis[t]^0x3f3f3f3f;
}

void mcmf(int s,int t){
	while(spfa(s,t)){
		int flow=INT_MAX;
		for(int i=t;i^s;i=pre[i].fa)
			flow=min(flow,e[pre[i].id].f);
		for(int i=t;i^s;i=pre[i].fa){
			e[pre[i].id].f-=flow;
			e[pre[i].id^1].f+=flow;
		}
		mf+=flow;
		mc+=flow*dis[t];
	}
}

void exadd(int x,int y,int f,int w){
	add(x,y,f,w);
	add(y,x,0,-w);
}

signed main(){
	read(n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) cnt[s[i]-'a'+1]++;
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=26;i++) exadd(0,i,cnt[i],0);
	for(int i=1;i<=26;i++)
		for(int j=1;j<=n/2;j++){
			int val=0;
			if(s[j]-'a'+1==i) val=max(val,a[j]);
			if(s[n-j+1]-'a'+1==i) val=max(val,a[n-j+1]);
			exadd(i,26+j,1,-val);
		}
	for(int i=1;i<=n/2;i++) exadd(26+i,27+n/2,2,0);
	mcmf(0,27+n/2);
	write(-mc);
}
```

---

## 作者：lemonaaaaa (赞：3)

### 【题意】

将一个字符串打乱后放回，满足第一个位置上的字符和最后一个位置上的字符不相同，第二个的位置上的字符和倒数第二个位置上的字符不相同...以此类推。每个位置有一个权值，如果原串和新串的位置上的字符相同，就获得这个位置上的权值。求满足条件的最大的权值和。

### 【解】

~~显然我们要尽可能地保证原字符串中尽可能多的字符在原位上，那么如果两个对应位置相同，我们可以视作将权值小的提到前面，然后优先考虑交换它们的位置和顺序，于是可以用dp等方法求出。~~

上面的是我最开始的思路，但是状态的设计和转移都比较难。我们可以换一种思想考虑，我们先把所有的字符全部拿出来，然后再一个个地放回去。那么我们考虑放回去的时候的约束有哪些：

1.放回去的时候每个字符的总个数要和原串中每个字符的总个数相同。

2.放回去之后前后两个对应的位置上不能出现重复的字符。(也就是说同种字符只能放在两个位置上的其中一个)

3.每一个位置都必须放一个字符。

从这里就看出了可以用网络流相关知识来求解了。那么现在来考虑如何保证权值最大。

同样我们可以只考虑哪些字符不在原来的位置上即可，所以我们可以求出不在原来位置上的权值和，用总权值-这些值就是答案。

### 【实现】

算法：最小费用最大流

首先建立源点S和汇点T

考虑约束条件1，我们先求出每个字符出现的次数cnt[i]，然后从S向每个字符(设点的类型为A)连流量为cnt[i]，费用为0的边，这样就保证了每个字符只能选最多cnt[i]次。

考虑约束条件2，由于同样的字符在每两个对应位置上只能放一个，那我们每个字符最多只能放n/2次，那么我们每个字符的点再新建n/2个点(设点的类型为B)，第i个点分别对应位置i和位置n-i+1，那么我们从每个A类型的点向对应的B类型的点连流量为1，费用为0的点，就限制了对于每个字符，对应的两个位置只能选一个来放。

考虑约束条件3，我们对每一个位置建一个点(设点的类型为C)，那么我们对每一个位置都建一条到汇点T流量为1，费用为0的点，就保证了每一个位置最多有一个字符。然后我们从B类型的点向C类型的点连边，这里是关键的一步，由上一个约束条件的考虑得出第i个点分别向i和n-i+1连流量为1的边即可。考虑费用：如果B类型的点的字符和连的位置对应的原串的字符相等，则费用为0，否则费用为对应的权值。

显然，在题意给定一定合法的情况下，这个网络一定满流。那我们就得出了修改所需要的代价，最后答案就是所有权值和-最小费用。

可能语言组织有些混乱，~~毕竟很久没有上常规课了~~，如有疏漏和错误之处请提出和见谅。~~估计提出也没用了，还有两天就省选了，马上就退役了233333~~

谨以此题解纪念即将结束的美好的OI生涯。

附上代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1000005;
const int inf=0x7f7f7f7f;
struct node
{
	int to,next,cost,flow;
} edge[maxn<<1];
int head[maxn],dist[10005],k=1,tot_cost=0,ans=0,s,t;
bool visit[10005];
void add(int u,int v,int w,int c)
{
	edge[++k].to=v;edge[k].next=head[u];edge[k].flow=w;edge[k].cost=c;head[u]=k;
	swap(u,v);
	edge[++k].to=v;edge[k].next=head[u];edge[k].flow=0;edge[k].cost=-c;head[u]=k;
}
bool spfa()
{
	memset(dist,inf,sizeof(dist));
	memset(visit,false,sizeof(visit));
	dist[t]=0;visit[t]=true;deque<int> q;q.push_back(t);
	while(!q.empty())
	{
		int x=q.front();q.pop_front();visit[x]=false;
		for(int i=head[x];i;i=edge[i].next)
		{
			if(dist[edge[i].to]>dist[x]-edge[i].cost&&edge[i^1].flow)
			{
				dist[edge[i].to]=dist[x]-edge[i].cost;
				if(!visit[edge[i].to])
				{
					visit[edge[i].to]=true;
					if(!q.empty()&&dist[q.front()]>dist[edge[i].to]) q.push_front(edge[i].to);
					else q.push_back(edge[i].to);
				}
			}
		}
	}
	return dist[s]!=inf;
}
int dfs(int x,int f)
{
	visit[x]=true;
	if(x==t||!f) return f;
	int flow=0;
	for(int i=head[x];i;i=edge[i].next)
	{
		if(visit[edge[i].to]) continue;
		if(dist[edge[i].to]!=dist[x]-edge[i].cost||!edge[i].flow) continue;
		int temp=dfs(edge[i].to,min(f-flow,edge[i].flow));
		edge[i].flow-=temp;
		edge[i^1].flow+=temp;
		flow+=temp;
		tot_cost+=temp*edge[i].cost;
		if(f==flow) break;
	}
	return flow;
}
void zkw()
{
	while(spfa())
	{
		visit[t]=true;
		while(visit[t])
		{
			memset(visit,false,sizeof(visit));
			dfs(s,inf);
		}
	}
}
int cnt[maxn],n,b[maxn],alp[maxn];
char str[maxn];
int main()
{
	#ifdef lemon
	freopen("844f.in","r",stdin);
	#endif
	scanf("%d",&n);s=0;t=4000;
	scanf("%s",str+1);
	for(int i=1;i<=n;i++) alp[i]=str[i]-'a'+1;
	for(int i=1;i<=n;i++) scanf("%d",&b[i]),ans+=b[i];
	//s:0
	//alp:1-26
	//alp_split:100-2700(100*alp+num(n/2))
	//point:3000-3100
	//t:4000
	for(int i=1;i<=n;i++) cnt[alp[i]]++;
	for(int i=1;i<=26;i++)
	{
		add(s,i,cnt[i],0);
		for(int j=1;j<=(n>>1);j++)
		{
			add(i,100*i+j,1,0);
			if(alp[j]==i) add(100*i+j,3000+j,1,0);
			else add(100*i+j,3000+j,1,b[j]);
			if(alp[n-j+1]==i) add(100*i+j,3000+n-j+1,1,0);
			else add(100*i+j,3000+n-j+1,1,b[n-j+1]);
		}
	}
	for(int i=1;i<=n;i++) add(3000+i,t,1,0);
	zkw();
	printf("%d",ans-tot_cost);
	return 0;
}
```

---

## 作者：do_it_tomorrow (赞：2)

[更好的阅读体验](https://www.doittomorrow.xyz/post/anti-palindromize/)

## 题目大意

给定长度为 $n$ 的字符串 $s$，要求找出 $s$ 的排列 $t$ 在满足 $\forall i\in [1,n]\cap \mathbb{N}\mid t_i\ne t_{n-i+1}$ 的情况下使 $\sum\limits_{i=1}^{n}b_i\cdot [s_i=t_i]$ 最大。

其中数据范围满足，$1\le n\le 100$，$n$ 为偶数且保证有解。

## 思路

考虑统计出 $s$ 中每个字符出现的次数 $cnt_i$，将 $s$ 的一样的字符一起考虑。

将原点 $S$ 向代表第 $i$ 种字符的节点连一条流量为 $cnt_i$ 费用为 $0$ 的边，这样可以保证在最大流量为 $n$ 时新的序列 $t$ 种每种字符出现的次数都是 $cnt_i$，也就是保证 $t$ 是 $s$ 的一个排列。

因为需要满足 $t_i\ne t_{n-i+1}$，所以考虑将 $t_i$ 和 $t_{n-i+1}$ 合并为 $1$ 个点，接着想每一种字母只连一条容量为 $1$ 的边，这样就保证了到达这个点的流量一定来自两个不同的字母。

考虑连边的边权，如果将 $ch$ 向 $i$ 连一条费用为 $x$ 的边，那么：

$$x=\max([s_i=x]\cdot b_i,[s_{n-i+1}=x]\cdot b_{n-i+1})$$

因为如果只有 $s_i=x\vee  s_{n-i+1}=x$，那么如果一定要在一个地方放 $x$ 那么为了收益最大先让应该将 $x$ 放在与 $s$ 相等的地方，这样就可以获得对应的收益。

如果 $s_i=x\wedge s_{n-i+1}=x$，那么肯定应该将 $x$ 放在收益最大的地方，因为另一个地方一定不是 $x$ 所以这样可以让收益最大化。

对于代表 $t_i$ 和 $t_{n-i+1}$ 的节点，将他们连向 $T$ 流量为 $2$ 费用为 $0$，这就保证了这对应的 $2$ 和点一定只有 $2$ 个不同的颜色选择了。

所以直接跑一个网络流就可以了，时间复杂度为 $O(n^3\log n)$，但是最大流量只有 $100$ 所以快的一批。

[Submission #271715922 - Codeforces](https://codeforces.com/contest/884/submission/271715922)

---

## 作者：Daidly (赞：2)

#### 解法一：费用流

> 若 $s_i$ 在 $i$ 上则增加 $b_i$ 的贡献。

考虑分配字符，从 $s$ 向代表 $a\sim z$ 的 $26$ 个点连以字符个数为流量，费用为 $0$ 的边。

再从代表字符的点向下标连。如何满足 $s_i\ne s_{n-i+1}$ 的限制？将下标折半，建 $\frac{n}{2}$ 个点，以一个点表示 $s_i$ 和 $s_{n-i+1}$。

字符 $c$ 向 $i$ 点连边满足：

- 若 $c=s_{i}$ 且 $c=s_{n-i+1}$，则费用为 $\max(b_i,b_{n-i+1})$，流量为 $1$；
- 若 $c=s_{i}$ 或 $c=s_{n-i+1}$，则费用为 $b_i$ 或 $b_{n-i+1}$，流量为 $1$；
- 若 $c\ne s_i$ 且 $c\ne s_{n-i+1}$，则费用为 $0$，流量为 $1$。

对于 $\frac{n}{2}$ 个点，向 $t$ 连费用为 $0$，流量为 $2$ 的边。

跑最大费用最大流即可，[My Submission](https://codeforces.com/contest/884/submission/196755810)。

#### 解法二：贪心

对于所有回文数对，按字符分组，若所有组内个数不超过总数的一半，可以内部消化，每一对共享为值取 $\max$。

否则比较麻烦，显然内部需要消耗掉共享为 $\min$ 的。

考虑最多个数的字符，只有一个，从剩余中选出一些可交换的排序，从小往大取即可。

假设最多个数的字符为 $c$，则需要满足 $s_i\ne s_{n-i+1},s_i\ne c,s_{n-i+1}\ne c$ 或 $s_i=s_{n-i+1},s_i\ne c$。

代码：[My Submission](https://codeforces.com/contest/884/submission/196759486)。



---

## 作者：Eltaos_xingyu (赞：0)

难得的我自己做出来的网络流题。

翻译一下题面，这题就是一个 $s$ 的排列 $t$ 在 $t_i\not=t_{n-i+1}$ 的限制下求 $b_i[s_i=t_i]$ 的最大值。

所以我们一个限制一个限制地讨论。

首先，对于 $t$ 是 $s$ 的排列，我们可以先统计 $s$ 的字符集桶，然后连 $S\to i$，流量为 $i$ 桶的值（即 $s$ 中有几个 $i$）。

其次，我们要满足 $t_i\not=t_{n-i+1}$，我们可以先建出虚点 $P_{i,j}$，其中 $i$ 表示字符 $i$，$j$ 表示 $j$ 和 $n-j+1$ 里面只能选一个。我们对于所有 $j$ 有 $i\to P_{i,j}$，流量为 $1$。然后连接 $P_{i,j}\to L_j,P_{i,j}\to L_{n-j+1}$，流量均为 $1$，其中 $L_i$ 表示第 $i$ 个位置所对应的点。最后 $L_i\to T$，流量为 $1$，我们就满足了这个限制。

最后我们要求 $b_i[s_i=t_i]$，显然我们可以对于每个 $i$ 对应的 $P_{s_i,k}\to L_{t_i}$ 边加上一个 $b_i$ 的费用，其中 $k=t_i$ 或 $n-k+1=t_i$。其余边费用为 $0$，跑一遍最大费用最大流即可。

由于流量最大才 $100$，所以跑得飞快。

贴上部分代码：

```cpp
int buc[27];
int n;
char S[101];
int b[101];
int id[27][101],idcnt=26;
#define addE T.addE
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>S[i];
		buc[S[i]-'a'+1]++;
	}
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=26;i++){
		for(int j=1;j<=n/2;j++){
			id[i][j]=++idcnt;
		}
	}
	int s=idcnt+n+1,t=s+1;
	for(int i=1;i<=26;i++)addE(s,i,buc[i],0);
	for(int i=1;i<=26;i++){
		for(int j=1;j<=n/2;j++){
			addE(i,id[i][j],1,0);
			if(S[j]=='a'+i-1)addE(id[i][j],idcnt+j,1,-b[j]);
			else addE(id[i][j],idcnt+j,1,0);
			if(S[n-j+1]=='a'+i-1)addE(id[i][j],idcnt+n-j+1,1,-b[n-j+1]);
			else addE(id[i][j],idcnt+n-j+1,1,0);
		}
	}
	for(int i=1;i<=n;i++)addE(idcnt+i,t,1,0);
	cout<<-T.MCMF(s,t).second;
	return 0;
}
```

---

## 作者：jucason_xu (赞：0)

我们发现这个题的数据范围、“字符和位置匹配”再加上一条奇怪的限制，长得就很网络流，那么就考虑如何用网络流做。

考虑重新解释一下这个题面，其实就是：给定一个字符集和 $n$ 个位置进行匹配，其中，字符 $ch$ 到位置 $i$ 的边和字符 $ch$ 到位置 $n-i+1$ 的边只能选一个。对于一个匹配可能会有边权，具体而言，位置 $i$ 和字符 $ch$ 匹配边的权值是 $b_i\cdot[s_i=ch]$。求一个最大权值的匹配。

我们已经将题意转化成很贴近费用流的样子了，唯一的问题在于“字符 $ch$ 到 $i$ 的边和字符 $ch$ 到 $n-i+1$ 的边只能选一个”很难搞。

考虑增加一组点用于限制，限制点 $(ch,i)(i\le \dfrac{n}{2})$ 是一个从 $ch$ 连到 $i$ 和 $n-i+1$ 必须经过的点。而从 $ch$ 到 $i$ 和 $n-i+1$ 最多有一个流量，所以点 $ch$ 到 $(ch,i)$ 的流量是 $1$，就解决了两条边只能选一个的问题。再从 $(ch,i)$ 连到 $i$ 和 $n-i+1$，边权还是一样计算，唯一的不同就是 $ch$ 出发的流量只能到达 $i$ 和 $n-i+1$ 其中之一。

我们就得到了一个最大费用最大流的问题，把边权设成负的就变成普通的费用流。设 $\sigma=26$，点数是 $2+\sigma+n+\dfrac{\sigma n}{2}$，边数是 $\sigma+n+\dfrac{3\sigma n}{2}$，流量是 $n$，总的复杂度是 $O(\sigma^2n^3)$，但是网络流一般跑不满，实际表现只跑了 `31ms` 。

```cpp
//因为本人的习惯，费用流是封的板子，解释一下主函数中调用的部分：
//Juc::ptt(i)是在图中加上编号为i的点
//Juc::add(a,b,c,d)是在图中加上从a到b，流量为c，费用为d的边和反向边
//Juc::s是源点
//Juc::t是汇点
//Juc::MCMF()是跑费用流
//Juc::cost是运行出来的费用

#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=b;i>=a;i--)
#define st string
#define vt vector
#define pb push_back
typedef long long ll;
namespace Juc{
	int n,m,s,t,a,b,c,d;
	vt<int>pnts;
	int dep[200005],vis[200005],cur[200005],dist[200005],vist[200005];
	struct edge{
		int a,b,f,c;
		edge(int _a,int _b,int _f,int _c){
			a=_a,b=_b,f=_f,c=_c;
		};
	};
	vt<edge>ve;
	vt<int>vv[200005];
	inline void add(int a,int b,int c,int d){
		ve.pb(edge(a,b,c,d));
		ve.pb(edge(b,a,0,-d));
		vv[a].pb(ve.size()-2);
		vv[b].pb(ve.size()-1);
	}
	inline void ptt(int a){
		pnts.pb(a);
	}
	inline bool SPFA(){
		for(auto i:pnts)dist[i]=1e9,vist[i]=0,vis[i]=0,cur[i]=0;
		queue<int>q;
		q.push(s),vist[s]=1,dist[s]=0;
		while(q.size()){
			int i=q.front();
			q.pop();
			vist[i]=0;
			for(auto g:vv[i]){
				auto &e=ve[g];
				if(e.f&&dist[i]+e.c<dist[e.b]){
					dist[e.b]=dist[i]+e.c;
					if(!vist[e.b]){
						vist[e.b]=1;
						q.push(e.b);
					}
				}
			}
		}
		return dist[t]!=1e9;
	}
	int cost=0;
	inline int DFS(int i,int f){
		if(i==t||f==0)return f;
		vis[i]=1;
		int res=0;
		for(int j=cur[i];j<vv[i].size();j++){
			edge& e=ve[vv[i][j]];
			cur[i]=j;
			if(!vis[e.b]&&dist[e.b]==dist[i]+e.c&&e.f){
				ll flow=DFS(e.b,min(e.f,f));
				ve[vv[i][j]].f-=flow,ve[vv[i][j]^1].f+=flow;
				f-=flow,res+=flow;
				cost+=flow*e.c;
			}
			if(!f)break;
		}
		vis[i]=0;
		return res;
	}
	inline int MCMF(){
		int ans=0;
		while(SPFA()){
			ans+=DFS(s,1e9);
		}
		return ans;
	}
}
int n,b[105],cnt[26];
st s;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>s;s='$'+s;
	rp(i,n)cin>>b[i];
	rp(i,n)cnt[s[i]-'a']++;
    //建立源点
	Juc::ptt(0);Juc::s=0;
    //建立字符点和初始流量
	rd(i,26)Juc::ptt(i+1),Juc::add(0,i+1,cnt[i],0);
    //建立位置点
	rp(i,n)Juc::ptt(26+i);
    //建立限制点
	rp(i,n/2)rd(j,26){
		int cur=26+n+(i-1)*26+j+1;
		Juc::ptt(cur);
       //通过流量为1进行限制
		Juc::add(j+1,cur,1,0);
       //连贡献边
		Juc::add(cur,26+i,1,-b[i]*(j+'a'==s[i]));
		Juc::add(cur,26+n-i+1,1,-b[n-i+1]*(j+'a'==s[n-i+1]));
	}
    //建立汇点和最终流量
	int tot=26+n+n*26+1;
	Juc::t=tot;Juc::ptt(tot);
	rp(i,n)Juc::add(26+i,tot,1,0);
	Juc::MCMF();
	cout<<-Juc::cost<<endl;
	return 0;
}
//Crayan_r
```

---

