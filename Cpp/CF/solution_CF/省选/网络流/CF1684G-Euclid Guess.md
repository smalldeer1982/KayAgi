# Euclid Guess

## 题目描述

下面是一个经过部分改动的求 $\gcd$ 的伪代码（其中 $t$ 是一个初始为空的序列）：

```plain
function Euclid(a, b):
    if a < b:
        swap(a, b)
    if b == 0:
        return a
    r = reminder from dividing a by b      (即设 r 为 a mod b)
    if r > 0:
        append r to the back of t          (即将 r 插入到 t 的尾部)
    return Euclid(b, r)
```

有一个由数对构成的序列 $p$，接下来我们对 $p$ 中每个数对都执行一次上述函数，然后把 $t$ 重新排列并给定到输入中。  
给定 $n,m$ 和长度为 $n$ 的序列 $t$。  
你需要构造一个长度不超过 $2\times10^4$ 的数对序列 $p$，满足：

- 每个数对中的元素都是不超过 $m$ 的正整数。  
- 根据序列 $p$ 可以经过上述操作得到输入中给定的 $t$。

有解输出任意一组解，无解输出 `-1`。

## 样例 #1

### 输入

```
7 20
1 8 1 6 3 2 3```

### 输出

```
3
19 11
15 9
3 7```

## 样例 #2

### 输入

```
2 10
7 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 15
1 7```

### 输出

```
1
15 8```

## 样例 #4

### 输入

```
1 1000000000
845063470```

### 输出

```
-1```

# 题解

## 作者：monstersqwq (赞：5)

很有趣的题，场上的时候差最后一步没做出来。

首先发现这个对答案行数的限制没啥用，对两个数做 $\gcd$ 至少会在列表里加上一个数，所以随便构造就行，不用管上限。

但是这样的限制也提醒我们可以寻找每次只在列表里增加一个数的构造方式，具体来说，如果希望只在列表里加上 $x$，那稍微手玩一下会发现可以构造 $(3x,2x)$ 这样的对，所以这样的 $x$ 不能超过 $\dfrac{m}{3}$。

现在我们只关心对于大于 $\dfrac{m}{3}$ 的 $x$ 如何构造，注意到在某次 $\gcd$ 过程中会出现的数由前两个出现的数决定，那么考虑前两个数分别是 $x,y(x\ge y)$ 的情况，发现最小只能构造 $(2x+y,x+y)$ 的对，也就是说，如果我们希望 $x,y$ 中有一个大于 $\dfrac{m}{3}$，另一个就必须不超过 $\dfrac{m}{3}$，也就是说，在 $\dfrac{m}{3}$ 两边的数是一一匹配的，这不是一眼二分图匹配？

但是会发现每次匹配的时候还可能会产生其它数，但是注意到最后一个产生的数一定是第一个数的因数，和中间的无关，且我们希望用不超过 $\dfrac{m}{3}$ 的数的个数尽可能小，那直接拿第一个数和最后一个数匹配即可。

现在问题变成了，将大数与小数匹配，需要保证所有大数都能匹配到某个小数，且对于匹配的大数 $x$ 和小数 $y$，有 $y|x,2x+y\le m$，直接二分图匹配就行。

```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<unordered_map>
#define y1 fjodifjsdidi
typedef long long ll;
using namespace std;
const int maxn=1005;
int n,m;
int t[maxn];
int val[maxn],N,S,T;
int hed[maxn],to[maxn*maxn*4],nxt[maxn*maxn*4],cnt=1,ww[maxn*maxn*4];
void adde(int u,int v,int w)
{
	ww[++cnt]=w;
	to[cnt]=v;
	nxt[cnt]=hed[u];
	hed[u]=cnt;
}
int ans;
int dis[maxn],ind[maxn];
queue<int> q;
bool bfs()
{
	while(!q.empty()) q.pop();
	for(int i=1;i<=N;i++) ind[i]=hed[i];
	memset(dis,0,sizeof(dis));dis[S]=1;q.push(S);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=hed[u];i!=0;i=nxt[i])
		{
			int v=to[i];
			if(ww[i]&&!dis[v])
			{
				dis[v]=dis[u]+1;
				if(v==T) return true;
				q.push(v); 
			}
		}
	}
    return false;
}
int dfs(int u,int lim)
{
	if(!lim||u==T) return lim;
	int fl=0;
	for(int i=ind[u];i!=0;i=nxt[i])
	{
		int v=to[i];
		if(ww[i]&&dis[u]+1==dis[v])
		{
			ind[u]=i;
			int t=dfs(v,min(lim-fl,ww[i]));
			if(t==0) dis[v]=-1;
			ww[i]-=t;ww[i^1]+=t;
			fl+=t;
			if(fl==lim) break;
		}
	}
	return fl;
}
void dinic()
{
	while(bfs()) ans+=dfs(S,2e9);
}
bool vis[maxn];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t[i]);
	}
	N=n+2;S=N-1;T=N;
	int qwq=0;
	for(int i=1;i<=n;i++)
	{
		if(t[i]<=m/3)
		{
			adde(i,T,1);adde(T,i,0);
		}
		else
		{
			adde(S,i,1);adde(i,S,0);
			qwq++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(t[i]>m/3&&t[j]<=m/3&&t[j]<=m-2*t[i]&&t[i]%t[j]==0)
			{
				adde(i,j,1);adde(j,i,0);
			}
		}
	}
	dinic();
	if(ans!=qwq)
	{
		printf("%d\n",-1);
		return 0;
	}
	printf("%d\n",qwq+(n-2*qwq));
	for(int i=1;i<=n;i++)
	{
		if(t[i]<=m/3) continue;
		for(int j=hed[i];j!=0;j=nxt[j])
		{
			int v=to[j];
			if(v==S||ww[j]==1) continue;
			printf("%d %d\n",t[i]*2+t[v],t[v]+t[i]);
			vis[v]=true;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]||t[i]>m/3) continue;
		printf("%d %d\n",3*t[i],2*t[i]);
	}
	return 0;
}
```


---

## 作者：周子衡 (赞：5)

可以发现，题目里要求最后构造出来的总对数 $\leq 2\times 10^4$ 这个条件其实没用——毕竟不往 $t$ 里面加入任何元素的数对直接删掉就行了，而最后 $t$ 的大小为 $n$，那么插入的数对肯定不超过 $n$ 个。

我们尽量试着把每个元素分开来考虑。比如，我们可以用一个数对 $(2x,3x)$ 来往 $t$ 里面加入一个元素 $x$。可以发现，如果没有 $m$ 的限制，我们直接用 $n$ 个 $(2x,3x)$ 就可以通过本题。下面我们称 $t$ 中满足 $3x\leq m$ 的元素为**小元素**，否则称为**大元素**。我们来看看怎么处理大元素。

值得注意的一点是：如果 $t$ 中某个元素大于等于 $\dfrac{m}{2}$，则整个问题是无解的。这是因为，一个正整数模另一个比它小的正整数后一定小于原来的一半。我们只考虑所有大元素都在 $(\dfrac{m}{3},\dfrac{m}{2})$ 之间的情况。这时可以发现，两个大元素不可能同时由一对元素构造出来——否则较小的那个大元素小于 $\dfrac{m}{4}$，与大元素定义矛盾。同时大元素不可能单独由某对数生成，我们可以知道，大元素一定要搭上某个小元素。

假设有一个大元素 $b$ 和一个小元素 $s$，我们来看看什么情况下 $b$ 后面有机会直接接一个 $s$。可以发现，在初始的数对 $(u,v)(u > v)$ 中，$v$ 大小至少要为 $b+s$，而 $u$ 的大小至少要为 $v+s=2b+s$。那么必须要有 $2b+s\leq m$。同时，$b$ 和 $s$ 后续生成的元素都应该在 $t$ 中。

我们延续“尽量试着把每个元素分开来考虑”的思路，来看看能否将问题简单化。关键的观察是：我们没有必要让某个数对产生多于 $2$ 个数！假设对于某个“大元素” $b$，我们在生成 $b$ 的同时生成了 $s_1 > s_2 > \cdots > s_k$。我们总可以调整，让这个序列只包含 $b$ 和 $s_k$！这是因为，我们一定有 $s_k | b$，同时 $2b+s_k < 2b+s_1\leq m$。这样我们可以通过构造一组 $(b+s_k,2b+s_k)$，只“占用” $t$ 中的 $b,s_k$ 两个元素，从而节省下更多的小元素 $s_1 \sim s_{k-1}$ 给别的大元素用。

接下来的事情便简单了。问题转化为：对每个大元素 $b$，我们要找到一个小元素 $s$ 使得 $2b+s\leq m$ 且 $s|b$。考虑建立一张二分图 $G$，左部为所有小元素，右部为所有大元素，按照上述规则连边。那么，我们只需要在这张二分图上找到一组包含全部右部点的匹配即可。使用匈牙利算法或者网络流算法求解二分图最大匹配，分别可以在 $O(n^3)$ 和 $O(n^2\sqrt n)$ 的时间复杂度内通过此题。

```cpp
#include<cstdio>
#include<vector>

using namespace std;

int cp[2000];bool E[2000][2000],vis[2000];
int s,b,small[2000],big[2000];

int fnd(int j)
{
	for(int i=1;i<=s;i++)
	{
		if(!vis[i]&&E[i][j])
		{
			vis[i]=1;
			if(!cp[i]||fnd(cp[i])){cp[i]=j;return 1;}
		}
	}
	return 0;
}

int main()
{
	int n=0,m=0;scanf("%d%d",&n,&m);
	for(int i=1,t=0;i<=n;i++)
	{
		scanf("%d",&t);if(2*t>=m){puts("-1");return 0;}
		if(3*t<=m)small[++s]=t;else big[++b]=t;
	}
	for(int i=1;i<=s;i++)for(int j=1;j<=b;j++)if(big[j]%small[i]==0&&2*big[j]+small[i]<=m)E[i][j]=1;
	for(int i=1;i<=b;i++)
	{
		for(int j=1;j<=s;j++)vis[j]=0;
		if(!fnd(i)){puts("-1");return 0;}
	}
	vector<pair<int,int> > ans;
	for(int i=1;i<=s;i++)
	{
		if(cp[i])
		{
			ans.push_back(make_pair(big[cp[i]]+small[i],2*big[cp[i]]+small[i]));
		}
		else{ans.push_back(make_pair(2*small[i],3*small[i]));}
	}
	printf("%d\n",ans.size());for(int i=0;i<ans.size();i++)printf("%d %d\n",ans[i].first,ans[i].second);
}
```

---

## 作者：huangzirui (赞：4)

题意：

你有一个数组 $t$，初始为空。

你可以进行若干次操作，每次选择两个 $[1,m]$ 之间的整数 $a,b$，然后对它们不断辗转相除，每次把余数放进数组中，不包括 $0$。

已知最后被打乱的数组 $t$，你需要构造一组方案或判断无解。

$n\leqslant 1000,m \leqslant 10^9$

---

假如没有 $m$ 的限制，我们想构造 $x$ 只需使用 $(2x,3x)$ 即可。

另外，容易发现对于 $x$ 满足 $2x \geqslant m$，显然是无解的。

因此我们只需要考虑 $x \in [\dfrac{m}{3},\dfrac{m}{2}]$ 之间的元素 $x$。

假设我们选择了 $(a+x,a)$ 这一对，我们有：$x \leqslant a\leqslant m-x \leqslant 2x$。

显然这个二元组在进行一次操作以后出现的余数一定都小于 $\dfrac{m}{3}$。

现在考虑操作 $(a+x,a)$ 会产生的元素中，必然出现了 $\gcd(a+x,x)$。记 $w=\gcd(a+x,x)$，那么上面那个二元组一定不如 $(x+w,x+x+w)$。因为我们既能满足 $a+x$ 取到最小，同时也能让尽量少消耗数字。

于是我们考虑所有满足 $x \in [\dfrac{m}{3},\dfrac{m}{2}]$ 的元素，它可以和满足 $y|x,x+x+y\leqslant m$ 的 $y$ 配对。那么直接二分图匹配就行了。

$O(n^3)$，可以通过此题，实际因为边不满所以飞快。

---

## 作者：Alex_Wei (赞：3)

> [CF1684G Euclid Guess](https://www.luogu.com.cn/problem/CF1684G) *2800

还算有点意思的网络流题。

首先，为使得余数为 $t$，则除数 $b$ 必然 $> t$，不妨令 $b = t + 1$。因为 $a > b$，所以 $a$ 最小为 $2t + 1$。因此首先判掉若存在 $2t + 1 > m$ 则无解。

考虑接下来的过程。若 $1\leq k < t$，则 $(2t + k, t + k) \to (t + k, t) \to (t, k)$，这意味着如果要搞出一个 $t$，我们还需要一些比较小的数作为垫背。

但是当 $k = t$ 时，整个过程 $(3t, 2t)$ 只会形成一个数 $t$，很棒，唯一的问题是需要满足 $3t \leq m$。

这样一来我们就有了大致思路。找到所有 $3t > m$ 的 **大** $t$，我们需要一个 $(2t + k, t + k)$ 来消灭掉这个 $t$，并且还需要 $k$ 以及 $(t, k)$ 后续形成的数作为垫背。如果存在方案使得每个数够用，那么剩下来所有 $3t\leq m$ 的 **小** $t$ 可以每次用一个 $(3t, 2t)$ 消灭掉。

问题转化为怎么消灭掉较大的 $t$。如果直接尝试枚举其对应的 $k$ 等于某个小 $t$，由于一次操作会涉及多个小 $t$，我们没有办法解决这种情况。

考察欧几里得算法本身，我们发现对于一开始的 $(a, b)$ 而言，$\gcd(a, b)$ 一定会出现在序列当中。这就好办了啊！如果 $k$ 不是 $t$ 的约数，那么令 $k\gets \gcd(k, t)$ 显然一定更优，因为后者涉及到的数完全包含于前者。更劲爆的是，后者只会涉及到 $k$ 本身一个数。

综上，枚举大 $t_i$ 和小 $t_j$，若 $t_j \mid t_i$ 且 $2t_i + t_j \leq m$，则 $i\to j$ 连边。跑一个二分图最大匹配（大 $t$ 之间由于 $3t > m$ 所以内部不会连边，是二分图）。如果所有左部点均被匹配掉则有解，将匹配对应的方案输出，并将剩下来的小 $t$ 通过 $(3t, 2t)$ 消灭掉。否则无解。

[代码](https://codeforces.com/contest/1684/submission/157754086)。

---

## 作者：NATO (赞：1)

有意思的一道题。

首先，我们可以知道一对数如果是要有用的，它必然会产生至少一个数到 $t$ 中，那么题目中比 $n$ 还大的神秘 $p$ 序列长度限制就是没有用的，因为我们最多会构造出 $n$ 对数。

其次，题目中说了，顺序是不重要的，我们的目的只是让构造出的数对所产生的数和序列中可以一一对应即可。

考虑为了让数尽可能地小于等于 $m$，我们构造时肯定是取最小的数对是最优的，于是我们想到对于 $\le\lfloor \frac{m}{3}\rfloor$ 的数 $x$，我们可以通过数对 $(2x,3x)$ 来构造且仅构造出 $x$ 这个数，而对于 $>\lfloor \frac{m}{3}\rfloor$ 的数 $x$ 我们可以通过数对 $(2x+y,x+y)$（当然 $x>\lfloor \frac{m}{2}\rfloor$ 自然是无解啦）构造出 $x$ 和 $y$，可是当数对变为 $(x,y)$ 后之后还会有一些数被构造产生，此时问题似乎就变成了有一些物品，选择某个物品可以满足某些条件，问是否存在一种精准覆盖的方案，并且可以满足的条件某些之间可以替换（一个数 $x$ 有多个），解决这个问题显然不弱于解决精准覆盖问题的，是不存在多项式复杂度的解法的。

继续观察性质。

注意到 $(x,y)$ 最后产生的一个数就是 $\gcd(x,y)$，所以如果我们要使用数对 $(2x+y,x+y)$，$\gcd(x,y)$ 就必然是在 $t$ 中的，而我们还发现当 $y|x$ 时，我们构造出来的数就只会有 $x,y$，那么我们用数对 $(2x+\gcd(x,y),x+\gcd(x,y))$ 去构造必然是不劣于用 $(2x+y,x+y)$ 去构造的（由于 $x>\lfloor \frac{m}{3}\rfloor$，而 $2x+y\le m$，那么 $y\le\lfloor \frac{m}{3}\rfloor$，那么数对 $(x,y)$ 构造出来的数都是 $\le\lfloor \frac{m}{3}\rfloor$ 的，那么这些数我们都是可以用 $(3x,2x)$ 这样的形式去构造的），而 $\gcd(x,y)$ 就告诉我们构造 $x$ 的时候必然是用的 $x$ 的某一个不等于它自己的因数来与 $x$ 组队的。

那么我们就自然地想到把 $>\lfloor \frac{m}{3}\rfloor$ 的数作为一部，$\le\lfloor \frac{m}{3}\rfloor$ 的数作为另一部，将 $>\lfloor \frac{m}{3}\rfloor$ 的数 $x$ 与 $\le\lfloor \frac{m}{3}\rfloor$ 且是它因数的数连边，跑二分图最大匹配，如果 $>\lfloor \frac{m}{3}\rfloor$ 的一部每个点都有匹配，说明有解，否则无解。

输出方案就匹配点 $(2x+y,x+y)$ 一对，其余点 $(3x,2x)$ 一对即可。

时间复杂度取决于你是用啥跑的二分图最大匹配，笔者用的网络流，故复杂度最坏 $O(n^2)$（$O(n\sqrt m)$ 的东西边数建满就 $O(n^2)$）。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
using namespace std;
ll n,m;
ll in[2005],b[1005];
map<ll,ll>sum;
bool cmp(ll a,ll b)
{
	return a>b;
}
struct ed
{
	ll v,w,next;
}edge[8010005];
ll head[2005],cnt=1;
void add(ll u,ll v,ll w)
{
	edge[++cnt].v=v;edge[cnt].w=w;edge[cnt].next=head[u];head[u]=cnt;
	edge[++cnt].v=u;edge[cnt].next=head[v];head[v]=cnt;
}
ll t;
ll dep[2005],cur[2005];
queue<ll>k;
bool bfs()
{
	cur[0]=head[0];
	for(ll i=1;i<=t;++i)dep[i]=0,cur[i]=head[i];
	dep[0]=1;
	k.push(0);
	while(!k.empty())
	{
		ll id=k.front();k.pop();
		for(ll i=head[id];i;i=edge[i].next)
		{
			ll v=edge[i].v,w=edge[i].w;
			if(!w||dep[v])continue;
			dep[v]=dep[id]+1;
			k.push(v);
		}
	}
	return dep[t];
}
ll dfs(ll id,ll get)
{
	if(id==t)return get;
	ll use=0;
	for(ll i=cur[id];i;i=edge[i].next)
	{
		cur[id]=i;
		ll v=edge[i].v,w=edge[i].w;
		if(!w||dep[v]!=dep[id]+1)continue;
		ll nu=dfs(v,min(get,w));
		edge[i].w-=nu;
		edge[i^1].w+=nu;
		get-=nu;use+=nu;
		if(!nu)dep[v]=0;
		if(!get)return use;
	}
	if(!use)dep[id]=0;
	return use;
}
struct px
{
	ll a,b;	
}ans[2005];
ll tot;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;++i)cin>>in[i],b[i]=in[i],++sum[in[i]];
	sort(b+1,b+1+n);
	ll cot=unique(b+1,b+1+n)-b-1;
	sort(b+1,b+1+cot,cmp);
	ll ls=0,rs=0,ns=0;
	for(ll i=1;i<=cot;++i)
	{
		if(b[i]<=m/3)break;
		++ls;
		add(0,ls,sum[b[i]]);
		ns+=sum[b[i]];
		for(ll j=i+1;j<=cot;++j)
			if(b[i]*2+b[j]<=m&&b[i]%b[j]==0)
			add(i,j,INF);
	}
	t=cot+1;
	for(ll i=ls+1;i<=cot;++i)add(i,t,sum[b[i]]);
	ll lls,res=0;
	while(bfs())
		while(lls=dfs(0,INF))res+=lls;
	if(res!=ns)cout<<-1;
	else
	{
		for(ll i=1;i<=ls;++i)
			for(ll j=head[i];j;j=edge[j].next)
			{
				ll v=edge[j].v;
				if(v)
				{
					for(ll k=1;k<=edge[j^1].w;++k)ans[++tot].a=b[i]*2+b[v],ans[tot].b=b[i]+b[v];
				}
			}
		for(ll i=ls+1;i<=cot;++i)
			for(ll j=head[i];j;j=edge[j].next)
			{
				ll v=edge[j].v;
				if(v==t)
				for(ll k=1;k<=edge[j].w;++k)ans[++tot].a=b[i]*3,ans[tot].b=2*b[i];
			}
		cout<<tot<<'\n';
		for(ll i=1;i<=tot;++i)cout<<ans[i].a<<' '<<ans[i].b<<'\n';
	}
} 
```

---

## 作者：Purslane (赞：1)

# Solution

考虑这个过程在做什么？不妨钦定输入的数是 $a$ 和 $b$，其中 $a \ge b$，则实际上我们会把 $a \bmod b$，$b \bmod (a \bmod b)$，$(a \mod b) \bmod (b \bmod (a \bmod b))$……依次加入 $t$ 中。

如果 $b \bmod (a \bmod b)=0$，我们可以比较精巧的控制恰好加入 $a \bmod b$ 进入 $t$ 中。很容易构造出 $(3x,2x)$，这样第一步加入 $x$，第二步就是 $0$ 了。

不过需要满足 $x \le \dfrac{m}{3}$，并不是所有都能满足。

注意到一个数对比他小的数取模，至少会减少一半。因此 $a \bmod b < \dfrac{m}{2}$，如果某个数 $x$ 满足 $2x \ge m$ 那么必定无解。


如果 $b \bmod (a \bmod b) > \dfrac{m}{3}$，则 $b > \dfrac{2m}{3}$，那么 $a \bmod b  < \dfrac{m}{3}$ 与单调性矛盾。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e3+10,MAXE=1e6+10;
struct Edge {int to,nxt,w;}edge[MAXE];
int n,m,tval[MAXN],s,t,tans,tmp,tot=1,flg[MAXN],hd[MAXN],cur[MAXN],dis[MAXN];
void add_edge(int u,int v,int w) {
	edge[++tot]={v,hd[u],w},hd[u]=tot;
	edge[++tot]={u,hd[v],0},hd[v]=tot;
	return ;	
}
int bfs(void) {
	memset(dis,-1,sizeof(dis));
	dis[s]=0; queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u=q.front(); q.pop();
		cur[u]=hd[u];
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,w=edge[i].w;
			if(dis[to]!=-1||!w) continue ;
			dis[to]=dis[u]+1,q.push(to);
		}
	}
	return dis[t]!=-1;
}
int dinic(int u,int mx) {
	if(u==t) return mx;
	int ans=0;
	for(int i=cur[u];i;i=edge[i].nxt) {
		int to=edge[i].to,w=edge[i].w;
		if(dis[to]!=dis[u]+1||!w) continue ;
		int tmp=dinic(to,min(mx,w));
		if(tmp) {
			ans+=tmp,mx-=tmp,edge[i].w-=tmp,edge[i^1].w+=tmp;
			if(mx==0) break ;
		}	
		else dis[to]=-1;
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>tval[i];
	ffor(i,1,n) if(tval[i]*2>=m) return cout<<-1,0;
	s=0,t=n+1,tans=0;
	ffor(i,1,n) if(tval[i]*3>m) ffor(j,1,n) if(tval[i]!=tval[j]&&tval[i]%tval[j]==0&&tval[j]<=m-2*tval[i]) add_edge(i,j,1);	
	ffor(i,1,n) if(tval[i]*3>m) add_edge(s,i,1),tans++; else add_edge(i,t,1);
	while(bfs()) while(tmp=dinic(s,998244353)) tans-=tmp;
	if(tans) return cout<<-1,0;
	vector<pair<int,int>> ans;
	ffor(i,1,n) if(tval[i]*3>m) {
		int mth=0;
		for(int e=hd[i];e;e=edge[e].nxt) {
			int to=edge[e].to,w=edge[e].w;
			if(w==0&&to!=s&&to!=t) {mth=to;break; }
		}
		int x=tval[i],y=tval[mth];
		flg[mth]=1,ans.push_back({x+x+y,x+y});
	}
	ffor(i,1,n) if(tval[i]*3<=m&&flg[i]==0) ans.push_back({3*tval[i],2*tval[i]});
	cout<<ans.size()<<'\n';
	for(auto pr:ans) cout<<pr.first<<' '<<pr.second<<'\n';
	return 0;
}
```

---

## 作者：Leasier (赞：0)

若 $\exists i, 2t_i \geq m$，一定无解。

一个简单的想法是让每一对数生成一个插入到 $t$ 中的数。

具体地，对于一个 $t_i$，我们希望构造 $(a, b)$ 使得：

- $a > b$。
- $t_i = a \bmod b > 0$。
- $b \bmod t_i = 0$。

于是 $a = (k + 1) t_i, b = k t_i$，其中 $k \in Z, k \geq 2$；进而我们可以构造 $a = 3t_i, b = 2t_i$。此时我们要求 $3t_i \leq m$。

那当 $3t_i > m$ 怎么办呢？设构造 $(a, b)$，则有：

- $a \bmod b = t_{i_1}$。
- $b \bmod t_{i_1} = t_{i_2}$。
- $\cdots$
- $t_{i_{k - 1}} \bmod t_{i_k} = 0$。

其中 $b = u t_{i_1} + t_{i_2}, a = vb + t_{i_1} = (uv + 1) t_{i_1} + v t_{i_2}$。

于是 $u = v = 1$，则 $2t_{i_1} + t_{i_2} \leq m$。

对于所有 $t_{i_j}$，我们还要求其为 $t_{i_k}$ 的倍数。

但这是不是太麻烦了点，注意到我们删去 $t_{i_{2 \sim k - 1}}$ 是不劣的，于是我们只需要关注其匹配关系。

建二分图用网络流跑二分图最大匹配即可。具体地，我们令左部点为所有 $3t_i \leq m$ 者，右部点为所有 $3t_j > m$ 者，$t_j \bmod t_i = 0, t_i + 2t_j \leq m$ 时左部 $i$ 向右部 $j$ 连边。

时间复杂度为 $O(n^2 \sqrt{n})$。

代码：
```cpp
#include <iostream>
#include <queue>

using namespace std;

typedef struct {
	int nxt;
	int end;
	int dis;
} Edge;

int cnt = 1;
int t[1007], head[1007], pos[1007], nxt[1007][1007], dis[1007], cur_edge[1007], dis_cnt[1007];
Edge edge[502007];
queue<int> q;

inline void init(int n){
	for (register int i = 0; i <= n; i++){
		dis[i] = 0x7fffffff;
		cur_edge[i] = head[i];
	}
}

inline void add_edge(int start, int end, int dis){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
	edge[cnt].dis = dis;
}

inline void bfs(int start){
	dis[start] = 0;
	q.push(start);
	while (!q.empty()){
		int cur = q.front(), dis_i = dis[cur] + 1;
		q.pop();
		dis_cnt[dis[cur]]++;
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (dis[x] == 0x7fffffff){
				dis[x] = dis_i;
				q.push(x);
			}
		}
	}
}

int dfs(int u, int flow, int start, int end, int n){
	if (u == end) return flow;
	int ans = 0;
	for (register int i = cur_edge[u]; i != 0; i = edge[i].nxt){
		cur_edge[u] = i;
		if (edge[i].dis != 0){
			int x = edge[i].end;
			if (dis[u] == dis[x] + 1){
				int t = dfs(x, min(flow - ans, edge[i].dis), start, end, n);
				edge[i].dis -= t;
				edge[i ^ 1].dis += t;
				ans += t;
				if (ans == flow || dis[start] == n) return ans;
			}
		}
	}
	cur_edge[u] = head[u];
	if (--dis_cnt[dis[u]] == 0) dis[start] = n;
	dis_cnt[++dis[u]]++;
	return ans;
}

inline int isap(int start, int end, int n){
	int ans = 0;
	bfs(end);
	while (dis[start] < n) ans += dfs(start, 0x7fffffff, start, end, n);
	return ans;
}

int main(){
	int n, m, half;
	cin >> n >> m;
	half = (m + 1) / 2;
	for (register int i = 1; i <= n; i++){
		cin >> t[i];
		if (t[i] >= half){
			cout << -1;
			return 0;
		}
	}
	int third = m / 3, bigger = 0, end = n + 1;
	for (register int i = 1; i <= n; i++){
		if (t[i] <= third){
			add_edge(0, i, 1);
			pos[i] = cnt;
			add_edge(i, 0, 0);
		} else {
			bigger++;
			add_edge(i, end, 1);
			pos[i] = cnt;
			add_edge(end, i, 0);
			for (register int j = 1; j <= n; j++){
				if (t[i] % t[j] == 0 && t[i] * 2 + t[j] <= m){
					add_edge(j, i, 1);
					nxt[i][j] = cnt;
					add_edge(i, j, 0);
				}
			}
		}
	}
	init(end);
	if (isap(0, end, end + 1) < bigger){
		cout << -1;
		return 0;
	}
	cout << n - bigger << endl;
	for (register int i = 1; i <= n; i++){
		if (edge[pos[i]].dis == 1) cout << t[i] * 2 << " " << t[i] * 3 << endl;
	}
	for (register int i = 1; i <= n; i++){
		if (t[i] > third){
			for (register int j = 1; j <= n; j++){
				if (nxt[i][j] != 0 && edge[nxt[i][j]].dis == 0){
					int val = t[i] * 2 + t[j];
					cout << val << " " << t[i] + t[j] << endl;
					break;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/1684/problem/G) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1684G)

~~煞笔题，我是什么煞笔，在这么煞笔的比赛中没有做出这么煞笔的题？~~

（u1s1 其实感觉这道题还挺有意思的）

首先对于一个数 $t$，要想得到 $t$ 为余数，除数至少是 $t+1$，这样 $a$ 就至少是 $2t+1$，因此如果存在 $2t_i+1>m$ 就直接输出 $-1$ 好了。我们还可以发现，对于一个满足 $3t\le m$ 的数，我们可以通过直接构造 $(3t,2t)$ 将其消去并且不会影响到其他数，但是对于 $3t>m$ 的数就不能这样构造了。换而言之，要想消掉一个 $3t>m$ 的 $t$，我们需要选择一个 $k$ 使得 $2t+k\le m$，并构造 $(2t+k,t+k)$，这样可以消掉 $t$ 并进而对 $(t,k)$ 进行辗转相除。因此我们可以想到一个很自然的想法：先用 $3t\le m$ 的小 t 消去 $3t>m$ 的大 t，剩余的小 t 直接 $(3t,2t)$ 带走。

但是对于一个大 t 我们又该选择怎样的 $k$ 呢？贪心？好像没法贪。不过我们注意到一个性质，就是最终 $\gcd(t,k)$ 肯定会在辗转相除得到的序列中，因此我们不妨就令 $k=\gcd(t,k)$，即 $k\mid t$，这样会恰好消除 $k,t$ 两个数，感性理解这样肯定最优，因此我们考虑在符合 $t_j\mid t_i$，$3t_i>m,3t_j\le m$ 的 $i,j$ 之间连边，然后跑最大匹配，由于是二分图，最大匹配容易求得，如果最大匹配不等于大 t 数量则无解，否则根据前面的过程构造出解即可。

```cpp
const int MAXN = 1e3;
const int MAXE = 2e6;
const int INF = 0x3f3f3f3f;
int n, m, a[MAXN + 5];
int S, T, hd[MAXN + 5], to[MAXE + 5], nxt[MAXE + 5], cap[MAXE + 5], ec = 1;
void adde(int u, int v, int f) {
	to[++ec] = v; cap[ec] = f; nxt[ec] = hd[u]; hd[u] = ec;
	to[++ec] = u; cap[ec] = 0; nxt[ec] = hd[v]; hd[v] = ec;
}
int dep[MAXN + 5], now[MAXN + 5];
bool getdep(int S, int T) {
	memset(dep, -1, sizeof(dep)); queue<int> q;
	q.push(S); dep[S] = 0;
	while (!q.empty()) {
		int x = q.front(); q.pop(); now[x] = hd[x];
		for (int e = hd[x]; e; e = nxt[e]) {
			int y = to[e], z = cap[e];
			if (z && dep[y] == -1) {
				dep[y] = dep[x] + 1;
				q.push(y);
			}
		}
	}
	return ~dep[T];
}
int getflow(int x, int f) {
	if (x == T) return f; int ret = 0;
	for (int &e = now[x]; e; e = nxt[e]) {
		int y = to[e], z = cap[e];
		if (z && dep[y] == dep[x] + 1) {
			int w = getflow(y, min(f - ret, z));
			cap[e] -= w; cap[e ^ 1] += w; ret += w;
			if (ret == f) return ret;
		}
	}
	return ret;
}
int dinic() {
	int ret = 0;
	while (getdep(S, T)) ret += getflow(S, INF);
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if (2 * a[i] + 1 > m) return puts("-1"), 0;
	}
	T = (S = n + 1) + 1;
	int cnt = 0;
	for (int i = 1; i <= n; i++) if (3ll * a[i] > m) {
		for (int j = 1; j <= n; j++) if (3ll * a[j] <= m && a[i] % a[j] == 0 && 2ll * a[i] + a[j] <= m)
			adde(i, j, 1);
		cnt++;
	}
	for (int i = 1; i <= n; i++) {
		if (3ll * a[i] > m) adde(S, i, 1);
		else adde(i, T, 1);
	}
	if (dinic() != cnt) return puts("-1"), 0;
	vector<pii> res;
	for (int i = 1; i <= n; i++) if (3ll * a[i] > m) {
		for (int e = hd[i]; e; e = nxt[e]) {
			int y = to[e];
			if (to[e] != S && !cap[e]) res.pb(mp(2 * a[i] + a[y], a[i] + a[y]));
		}
	}
	for (int i = 1; i <= n; i++) if (3ll * a[i] <= m) {
		for (int e = hd[i]; e; e = nxt[e]) {
			int y = to[e];
			if (y == T && cap[e]) res.pb(mp(3 * a[i], 2 * a[i]));
		}
	}
	printf("%d\n", (int)(res.size()));
	for (pii p : res) printf("%d %d\n", p.fi, p.se);
	return 0;
}
```



---

