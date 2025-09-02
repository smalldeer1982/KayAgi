# [USACO10NOV] Candy S

## 题目描述

Farmer John knows that Bessie loves to eat candy. FJ has N (1 <= N <= 40,000) candies that he wants to give Bessie over some number of days. Each day, Farmer John gives Bessie a choice of how many candies she chooses to eat that day by choosing the number from a master list FJ supplies that has Nopt (1 <= Nopt <= 50) different options, C\_i (1 <= C\_i <= N). She must take exactly C\_i candies, no more, no less.

Farmer John has also disclosed F (1 <= F <= 50) of his favorite numbers, FN\_i (1 <= FN\_i <= N). Whenever the number of candies remaining at the end of the day precisely matches one of these favorite numbers, Bessie has the option to have him add exactly M (1 <= M <= 100) more candies to the candy supply. Bessie might get another option to add M candies several times if adding candies creates another favorite number. In the best circumstances, Bessie can obtain an infinite amount of candy!

When Bessie cannot choose some amount of candy to take (because there is not enough), and the number of candies remaining is not any of FJ's favorite numbers, she cannot have any more candy.

Unfortunately, Bessie cannot think ahead as far as she'd like to, so she needs your help in order to eat as many candies as possible.

By way of example, consider this scenario:

\* Farmer John's basket initially contains 10 candies

\* Bessie can chose to eat either 3 or 5 candies each day

\* Farmer John will add 1 candy any time the remaining number of candies is 2 or 4

Bessie could use this set of choices to maximize the amount of candy she can eat:

```cpp

                  Initial      # Candies   Remaining     Bonus     Final
        Day      # Candies       Eaten      Candies     Candies   Candies

         1          10             3          7            0        7
         2           7             3          4            1        5
         3           5             3          2            1        3
         4           3             3          0            0        0

```

Total candies eaten = 3 + 3 + 3 + 3 = 12. 

农民约翰知道Bessie喜欢吃糖果。约翰有N（1≤N≤40000）的糖果，他想给Bessie几天。每一天，贝茜从一个列表（有nopt（1 <= nopt <= 50）种不同的选择），选择那一天吃掉刚好C\_i（1 <= c\_i <= N）个糖果。


农民约翰也透露F（1≤f≤50）他最喜欢的数字，FN\_i（1 <= FN\_i <= N）。当当天最后剩下的糖果数量精确匹配其中一个喜欢的号码，Bessie可以让他添加恰好M（1 <= M = 100）个糖果。如果加后得到的个数，还是FJ喜欢的数字，就可以继续添加糖果M个（加几次由贝西决定）。在最好的情况下，Bessie可以吃掉无限量的糖果！


当Bessie不能选择一定量的糖（因为没有足够的），或者糖果的剩余数量不是任何约翰最喜欢的号码，她不能有任何更多的糖果。


不幸的是，Bessie想不出她想做的事，所以她需要你的帮助才能吃尽可能多的糖果。


## 说明/提示

感谢@ 王彦梓 提供翻译，kkksc03进行了修正。


## 样例 #1

### 输入

```
10 2 2 1 
3 
5 
4 
2 
```

### 输出

```
12 
```

# 题解

## 作者：L______ (赞：8)

看到这种类型的问题基本上就是什么可反悔的贪心或者是dp之类的了。

最开始想了一下是不是可以用堆维护然后可反悔的贪心，但是发现想不出来（~~事实上是因为我太菜了~~），就开始想dp思路。

首先我们可以考虑，当不存在可以加糖的情况时，我们以dp[i]表示当剩余糖的个数为i时最多可以吃掉的糖的数量。于是可以很轻松地推出状态转移方程

```
dp[i-c[j]]=max(dp[i-c[j]],dp[i]+c[j]);
```
其中c[j]为题目给出的每次可以选择吃掉的糖的数量。

但是题目中给出当存在i为一个fj喜欢的数的时候时是可以加入m个糖的，那么i+m以后的状态都有可能受到影响，那么该怎么办呢？

很简单，我们如果正常枚举状态是从n枚举到1，对于一个i下一个枚举的状态就是i-1，假如i为fj喜欢的数,那么就把i加上m+1，于是我们下一个枚举的状态就会从i+m开始了（~~总感觉有点小暴力但是时间复杂度什么的蒟蒻我又不会证~~）

用cnt[i]记录到达每个状态的次数，然后就可以判断是否可以无限吃糖的情况了。

**Code**
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
#define inf 0x7f7f7f7f
#define N 60
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,nopt,F,m,c[N],f[N],book[40110],dp[40110],cnt[40110],ans;

int main(){
	n=read(),nopt=read(),F=read(),m=read();
	for(int i=1;i<=nopt;i++) c[i]=read();
	for(int i=1;i<=F;i++) book[read()]=1;
	memset(dp,-1,sizeof(dp));
	dp[n]=0;book[n]=false;
	for(int i=n;i;i--){
		if(dp[i]==-1) continue;
		if(cnt[i]>F+1) return printf("-1\n"),0;
		if(book[i]){
			cnt[i]++;
			if(dp[i]>dp[i+m]){
				dp[i+m]=dp[i];
				i+=m+1;
			}
			continue;
		}
		for(int j=1;j<=nopt;j++){
			if(i-c[j]<0) continue;
			dp[i-c[j]]=max(dp[i-c[j]],dp[i]+c[j]);
		}
	}
	for(int i=n;i>=0;i--) ans=max(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

今天考试考的。没有 latex 差评。

考虑能够把这个东西用图论建模表示出来。首先每个点 $i$ 表示当前剩 $i$ 个糖，往 $i-c_j$ 连一条边权为 $c_j$ 的边，代表转移过去会吃到 $c_j$ 的糖果数。每个 $f_i$ 往 $f_i+m$ 连一条边权为 $0$ 的边，代表得到奖励，但没有真正吃到糖。题目保证 $f_i\le n$，那么最多糖数为 $n+m$，在 $n$ 这个量级。

假设最后吃不到糖是终点，考虑对所有点往 $0$ 连一条边权为 $0$ 的边，代表此时结束吃糖。

于是我们的问题变成求 $n$ 到 $0$ 的最长路。

无解情况很简单，有任何一个 **能从 $n$ 到达的** 环，就可以无限制地走下去。所以判环就好，方法有很多，这里用的是 ~~（大概？）~~ 最简单的 dfs 判环。

考虑最长路怎么求，好像在本人的印象里面 dijk 是不能求正边权最长路的，而此题数据范围似乎 spfa 有死的可能。但是我们发现只用求两个单点之间的最长路，直接记忆化搜索就好。

具体地，$dp_i$ 表示 $i$ 到 $0$ 的最长路，访问到就再用一遍。

复杂度 $O(n\times nopt)$，也就是连边的复杂度，求解的复杂度是 $O(n)$ 的。

code:

```cpp
#include <bits/stdc++.h>
//#define int long long
#define lowbit(x) ((x)&(-x))
#define Rg register
#define Ri Rg int
#define Il inline
#define pb push_back
#define vec vector
#define fi first
#define se second
#define IT ::iterator

using namespace std;
typedef pair<int,int> pii;
typedef double db;
const int N=5e4;

int n,cn,fn,m,c[N+5],f[N+5],dp[N+5];
vec<pii>v[N+5];
bool vis[N+5],Vis[N+5];

Il bool find(int p){
	if(Vis[p])return 0;
	if(vis[p])return 1;
	vis[p]=1;
	for(Rg pii i:v[p])if(find(i.fi))return 1;
	vis[p]=0;
	Vis[p]=1;
	return 0;
}

Il int dfs(int p){
	if(dp[p]||!p)return dp[p];
	for(Rg pii i:v[p])if((p^n)||i.se)dp[p]=max(dp[p],dfs(i.fi)+i.se);
	return dp[p];
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>cn>>fn>>m;
	for(Ri i=1;i<=cn;i++)cin>>c[i];
	for(Ri i=1;i<=fn;i++){
		cin>>f[i];
		v[f[i]].pb({f[i]+m,0});
	}
	for(Ri i=1;i<=n+m;i++){
		for(Ri j=1;j<=cn;j++)if(i-c[j]>=0)v[i].pb({i-c[j],c[j]});
		if(i<c[1])v[i].pb({0,0});
	}
	cout<<(find(n)?-1:dfs(n));
	return 0;
}
```

注意一下 #5，是个 hack，初始状态无法得到奖励，因为你一定要先吃。我们发现在没有环的情况下初始状态只能到达一次，所以这种 hack 直接特判掉就好了。

---

## 作者：lizhous (赞：1)

[洛谷传送门](https://www.luogu.com.cn/problem/P2998)


## 分析
~~我不会dp~~

所以这道题我们建模做。

第 $i$ 个节点代表剩余 $i$ 个糖果。显然点 $i$ 会向每个 $i-c_j(1 \le j \le nopt)$ 连一条边权为 $c_j$ 的边，表示剩 $i$ 个时选择吃掉 $c_j$ 个。而对于每个幸运数字，可以选择增加一些糖果，即对于幸运数字 $FN_i$，向 $FN_i+M$ 连一条边权为 $0$ 的边，因为加糖并不会让奶牛多吃到糖。值得注意的是，剩余糖果可能超过 $n$，所以点要多一些。因为 $M$ 最多 $100$，所以用 $n+100$ 个点即可。

建完模后显然是一个单源最长路，用最长路跑一下就可以了。

分析一下时间复杂度。共约 $n+100$ 个点，$nopt\times n$ 条边，总时间复杂度约为 $O(nopt\times n\log n)$。可以通过。

一个细节：若最开始的糖果量就是幸运数字，是不能加糖的。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#define int long long
using namespace std;
int n,k,m,add;
struct edge
{
	int v,w;
};
vector<edge> g[50101];
struct point
{
    int id,d;
    bool operator < (point a) const
    {
        return d<a.d;
    }
};
priority_queue<point> q;
int dij[50101];
signed main()
{
	scanf("%lld%lld%lld%lld",&n,&m,&k,&add);
	for(int i=1;i<=m;i++)
	{
		int mul;
		scanf("%lld",&mul);
		for(int z=mul;z<=n+100;z++)
		{
			g[z].push_back((edge){z-mul,mul}); //建一般的边
		}
	}
	for(int i=1;i<=k;i++)
	{
		int u;
		scanf("%lld",&u);
		g[u].push_back((edge){u+add,0}); //奖励边
	}
	
	for(int i=0;i<=n+100;i++) dij[i]=-10000000000; //初值
    dij[n]=0;
    q.push((point){n,0});
    int cnt=0;
    while(q.empty()==false&&cnt<=500000) //最长路
    {
        int u=q.top().id;
        q.pop();
        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i].v;
            int w=g[u][i].w;
            if(u==n&&w==0) continue;
            if(dij[u]+w>dij[v])
            {
                dij[v]=dij[u]+w;
                q.push((point){v,dij[v]});
            }
        }
        cnt++;
    }
    else
    {
    	int ans=0;
		for(int i=0;i<=n+100;i++) //取答案
		{
			ans=max(dij[i],ans);
		}
		cout<<ans;
	}
} 
```

---

## 作者：Gaode_Sean (赞：1)

### 解题思路:
这题想当然就是一个 DP。

我们注意到，$fn_i$ 数据范围极小，用一个 $mp_i$ 记录  $i$ 是否是幸运数字。

我们求的是 $dp_n$，对于 $(1 \le i \le nopt)$，如果       $mp_i=1$, $dp_i=\max(dp_i,dp_{i+m})$,对于 $(1 \le j \le nopt,c_j \le i)$， $dp_i=\max(dp_i,c_j+dp_{i-c_j})$。

如何判断是否能吃无限个?

每当还剩$i$个糖果，$v_i=1$（注意回溯时 $v_i=0$）,所以，每当访问到一个节点标记为 $1$ 时，输出 $-1$ (这里有多种实现方法)。

### 实现细节：
$1.$ 注意保存 $dp_i$。

$2.$ 当 $n$ 是幸运数字时，不能加糖果，因为 $n$ 不算剩余的量。

### 记忆化 DP 代码:
```cpp
int dfs(int now)
{
	if(v[now]){
		cout<<-1;
		exit(0);
	}
	if(dp[now]) return dp[now];
	v[now]=1;
	if(mp[now]&&now!=n) dp[now]=max(dp[now],dfs(now+m));
	for(int i=1;i<=np;i++) if(now>=a[i]) dp[now]=max(dp[now],a[i]+dfs(now-a[i]));
	v[now]=0;
	return dp[now];
}
```

---

## 作者：MVP_Harry (赞：1)

感觉前面两位$dalao$写的太深奥了，还是**记忆化**更为简便一些，~~其实好像不需要记忆化也能过~~。

对于这个search函数来说，如果$cur \ge T[i]$的话，那我们就可以比较$T[i] + search(cur - T[i])$.而如果$cur$还是FJ的“好数”的话，还需与$search(cur + M)$比较。注意函数最后需要回溯一下，其他就没什么难点了，详细注释见代码。

```
#include<bits/stdc++.h>
using namespace std;

const int maxn = 4e4 + 5;

int N, OPT, F, M, T[55], vis[maxn + 100], d[maxn + 100];

set<int> FJ; //用set记录一下FJ的“好数”，其实因为数据小，set也不是特别的必要

int search(int cur) {
	if (vis[cur]) return 10000000; //判重的方法，因为不可能到达10^7，所以超了肯定就是无限循环了。
	if (d[cur]) return cur;
	vis[cur] = 1;
	int ans = 0;
	if (FJ.count(cur) == 1 && cur != N) ans = max(ans, search(cur + M));
	for (int i = 1; i <= OPT; i++) {
		if (cur >= T[i])
			ans = max(ans, T[i] + search(cur - T[i]));
	}	
	vis[cur] = 0; //回溯
	return d[cur] = ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> OPT >> F >> M;
	for (int i = 1; i <= OPT; i++) {
		cin >> T[i];
	}
	for (int i = 1, temp; i <= F; i++) {
		cin >> temp;
		FJ.insert(temp);
	}
	int res = search(N);
	if (res >= 10000000) cout << -1 << endl;
	else cout << res << endl;
}
```

---

## 作者：Priestess_SLG (赞：0)

十分简单一题。考虑记忆化搜索。设当前有 $x$ 个糖果，那么枚举其每一个可以转移到的糖果数并继续搜索。若当前搜索到了一个之前已经搜索过的元素，那么代表出现了环，此时说明 Bessie 可以无限吃糖果，输出 $-1$ 即可。

具体见 [代码](https://www.luogu.com.cn/paste/wb8hcpxh)。

---

## 作者：Lance1ot (赞：0)

~~题目描述好别扭~~

~~被同学拉着做题，搞到了这一题。~~


先不考虑增加糖，对于每一种糖的数量抽象成一个点，吃糖看做连接点与点之间的边。很容易就发现，这张图是一个DAG。DAG就可以跑简单的dp了。

然后考虑有增加糖的情况，讲增加糖这一行为也抽象成点。我们会发现，无限吃糖在图上的表现就是出现了环。否则就是个DAG。

所以我们可以先判断是否会无~~线~~吃糖，然后在再dp。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>

using std::max;
using std::queue;

const int maxn=101000;

int ind[maxn],like[maxn];
int ate[maxn],f[maxn];
int g[maxn];
int n,nopt,fn,m;
int vis[maxn],instk[maxn];
queue<int>q;

template<class T>
void read(T& val)
{
    char c=getchar(); val=0;
    while(!isdigit(c)) c=getchar();
    while(isdigit(c))
    {
        val=(val<<3)+(val<<1)+c-'0';
        c=getchar();
    }
    return ;
}

void dfs(int now)
{
    vis[now]=instk[now]=1;
    int nxt;
    for(int i=1;i<=nopt;++i)
    {
        nxt=now-ate[i];
        if(nxt<0) continue;
        if(instk[nxt])
        {
            printf("-1");
            exit(0);
        }
        else
        {
            ++ind[nxt];
            if(!vis[nxt]) dfs(nxt);
        }
    }
    if(like[now]&&now!=n)
    {
        nxt=now+m;
        if(instk[nxt])
        {
            printf("-1");
            exit(0);
        }
        else
        {
            ++ind[nxt];
            if(!vis[nxt]) dfs(nxt);
        }
    }
    instk[now]=0;
}

int main()
{
    // freopen("data.in","r",stdin);
    read(n),read(nopt),read(fn),read(m);
    for(int i=1;i<=nopt;++i) read(ate[i]);
    for(int i=1;i<=fn;++i) read(f[i]),like[f[i]]=1;
    dfs(n);
    q.push(n); ind[n]=0;
    int pas,nxt;
    while(!q.empty())
    {
        pas=q.front(); q.pop();
        for(int i=1;i<=nopt;++i)
        {
            nxt=pas-ate[i];
            if(nxt<0) continue;
            g[nxt]=max(g[nxt],g[pas]+ate[i]);
            --ind[nxt];
            if(!ind[nxt]) q.push(nxt);
        }
        if(like[pas]&&pas!=n)
        {
            nxt=pas+m;
            g[nxt]=max(g[nxt],g[pas]);
            --ind[nxt];
            if(!ind[nxt]) q.push(nxt);
        }
    }
    int ans=0;
    for(int i=0;i<=n+m;++i) ans=max(ans,g[i]);
    printf("%d",ans);
    return 0;
}
```
如何判环？ 使用dfs，对每个点打两个标记。一个是是否曾经遍历过，另一个是否在dfs栈中。如果我们在dfs中遇到一个在dfs栈中的，则说明找到了一个环。如果不在栈中却遍历过，则可以不进行遍历（为了保证时间复杂度）
。

如果这个不在栈中却遍历过的点X，是上的一个点，则我们不会进行当前的dfs，而是在X在栈中的时候直接退出。换种说话，就是可以保证X不是在环上的点。

另外，如果john喜欢的数字中有n（糖的总和），则当糖的数量是n时，不能进行加糖的操作（第一次吃糖之前不能加，因为那不是剩下的。以后加糖加到n不能再往上加了，因为出现了环）。这是要注意的点。

---

