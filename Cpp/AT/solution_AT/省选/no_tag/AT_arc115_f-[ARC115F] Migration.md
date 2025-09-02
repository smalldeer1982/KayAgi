# [ARC115F] Migration

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc115/tasks/arc115_f

$ N $ 頂点の木が与えられます。頂点には $ 1,\ \ldots,N $ の番号がついており、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ をつないでいます。また、頂点 $ i $ には整数 $ h_i $ が書かれています。  
 駒が $ K $ 個あり、$ i $ 番目の駒ははじめ頂点 $ s_i $ に置かれています。あなたはこれから「一つ駒を選び、それが現在置かれている頂点に隣接するいずれかの頂点に移動させる」という操作を繰り返します。 各駒 $ i $ が頂点 $ t_i $ に置かれている状態になったら操作を終了します。各駒 $ i $ を頂点 $ s_i $ から頂点 $ t_i $ へ最短経路で移動させる必要は**ありません**。  
 ある駒の配置に対して、それぞれの駒が置かれている頂点に書かれた整数を足し合わせた値を**ポテンシャル**と呼ぶことにします。ただし、同じ頂点に複数の駒がある場合、その頂点の整数はその駒の個数だけ足し合わせるものとします。  
 操作を通してのポテンシャルの最大値は最小でいくつになるか求めてください。ただし、はじめの状態と終わりの状態も考えるものとします。

## 说明/提示

### 制約

- $ 1\ \leq\ N,K\ \leq\ 2000 $
- $ 1\ \leq\ u_i,v_i\ \leq\ N $
- $ 1\ \leq\ h_i\ \leq\ 10^9 $
- $ 1\ \leq\ s_i,t_i\ \leq\ N $
- 与えられるグラフは木

### Sample Explanation 1

以下のように操作をすることで操作を通してのポテンシャルの最大値は $ 4 $ となります。 - はじめ、ポテンシャルは $ 3 $。 - 駒 $ 2 $ を頂点 $ 2 $ に移動させる。ポテンシャルは $ 4 $ になる。 - 駒 $ 2 $ を頂点 $ 1 $ に移動させる。ポテンシャルは $ 2 $ になる。 - 駒 $ 1 $ を頂点 $ 2 $ に移動させる。ポテンシャルは $ 4 $ になる。 - 駒 $ 1 $ を頂点 $ 3 $ に移動させる。ポテンシャルは $ 3 $ になる。 ポテンシャルの最大値が $ 4 $ より小さくなるような操作の方法は存在しないため、$ 4 $ が答えです。

## 样例 #1

### 输入

```
3
1 3 2
1 2
2 3
2
1 3
3 1```

### 输出

```
4```

## 样例 #2

### 输入

```
7
100 101 1 100 101 1 1000
1 2
2 3
4 5
5 6
1 7
4 7
2
1 3
4 6```

### 输出

```
201```

## 样例 #3

### 输入

```
5
2 1 100 5 6
1 2
2 3
3 4
3 5
2
2 2
4 5```

### 输出

```
101```

## 样例 #4

### 输入

```
4
1 2 3 100
1 4
2 4
3 4
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3```

### 输出

```
115```

## 样例 #5

### 输入

```
6
1 100 1 1 10 1000
1 2
2 3
4 5
1 6
4 6
3
1 3
5 5
5 5```

### 输出

```
102```

# 题解

## 作者：command_block (赞：14)

**题意** ： 给出一棵 $n$ 个节点的树，点有点权 $h_u$ 。

树上有 $k$ 块石子，记第 $i$ 块石子的位置为 $u_i$ ，则当前局面的“不稳定度”定义为 $\sum_{i=1}^kh_{u_i}$ 。

给出石子的初始位置，你的目标是将第 $i$ 个石子移动到节点 $t_i$ ，每次只能将一个石子移到相邻的节点（允许多个石子放在一个节点上），最小化过程中不稳定度的最大值。

$n\leq 2000$ ，时限$\texttt{4s}$。

------------

考虑二分。

记 $S$ 为初始局面，$T$ 为终止局面。

记 $H(S)$ 为局面 $S$ 的不稳定度（若不稳定度相同则比较字典序）， $f(S)$ 为局面 $S$ 所能到达（有 $mid$ 约束）的最小的 $H(V)$。

不难发现，由于操作的可逆性，$S$ 能到达 $T$ 当且仅当两者能到达的不稳定度最小的局面相同。

问题转化为求 $f(S)$ 。

------------

根据操作的可逆性，若 $S,S'$ 能互相到达，则 $f(S)=f(S')$ 。

那么，我们每次找出一个可达的 $S'$ 使得 $H(S')<H(S)$ ，重复若干次即可得到最小的 $H$ 。

为了便于维护，我们每次只考虑一个石子的连续移动，将这个石子（合法地）移动到一个 $H$ 更小的位置。

可以证明，若不存在这种方案，则不存在任意 $S'$ 使得 $H(S')<H(S)$。于是只用考虑这种移动就好。

显然这样的移动最多 $O(nk)$ 次。

我们需要快速求解 ： 从 $u$ 点移动，所到的点权不超过 $L$ ，能到达的最小点权。特殊地，若点权不能变小，则置为 $+\infty$ 。这个随便 dfs 预处理。

然后再用堆维护每个石子的最小出边即可。

------------

可以发现其实不用二分，只需每次挑一步最大不稳定度最小的转移。

记 ${\rm maxh}(u,v)$ 为路径 $(u,v)$ 的最大权值。

这样，我们对每个 $u$ 记 $t_u$ 表示 $v$ 点满足 $h_v<h_u$ 且 ${\rm maxh}(u,t_u)$ 最小（若相同，则比较 $v$ 的权值）。

当我们移动 $u$ 点时，必然会前往 $t_u$ 。

这样的复杂度为 $O(nk\log k)$ ，已经足以通过。

------------

$t$ 的求法：考虑按 $h_u$ 从小到大加入点的过程，建立类克鲁斯卡尔重构树。然后再次从小到大考虑 $h_u$ 目标就是找到 $u$ 与更小的点的 $\rm LCA$ ，容易倍增求算。复杂度为 $O(n\log n)$。

建立一张新图，对于 $u$ ，连有向边 $u\rightarrow t_u$ ，边权为 $c_u={\rm maxh}(u,t_u)-h_u$ （即不稳定度的增量）。这形成一棵内向树。

贪心时，每次走 $c_u$ 最小的边。

- **性质** ：若 $t_a=b,t_b=c$ ，则有 $c_a\le c_b$ 。也就是说，在新树上越浅边权越大。

  **证明** ：$a,b,c$ 的分布如下图：（其他一些情况可以视为该图的退化）
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/pmebay2r.png)
  
  记 $A={\rm maxh}(a,t),B={\rm maxh}(b,t),C={\rm maxh}(c,t)$ 。
  
  若 $A$ 最大或 $B$ 最大：此时 ${\rm maxh}(a,b)\geq {\rm maxh}(a,c)$ ，$t_a$ 选择 $c$ ，矛盾。
  
  因此只可能是 $C$ 最大，则 ${\rm maxh}(a,b)=\max(A,B)\le \max(B,C)={\rm maxh}(b,c)$ .
  
  ${\rm maxh}(a,b)\le {\rm maxh}(b,c)$ 结合 $h_a\ge h_b$ 则有 $c_a\le c_b$ 。
  
于是，我们可以直接给边按 $c$ 从小到大排个序（也是从浅往深，若权值相同则比较深度），然后依次移动就是。

这里我们可能同时移动多个石子，用 xor Hash 维护集合特征，并记一个集合大小以计算不稳定度的变化。

可以把二分加回来以简化实现。

复杂度 $O(n\log n)$。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define ll long long
#define pb push_back
#define MaxN 2050
using namespace std;
struct UFS{
  int f[MaxN];
  void Init(int n)
  {for (int i=1;i<=n;i++)f[i]=i;}
  int find(int u)
  {return f[u]==u ? u : f[u]=find(f[u]);}
  void merge(int u,int v)
  {f[find(u)]=find(v);}
}F;
int n,k,h[MaxN],p[MaxN],u1[MaxN],u2[MaxN],rnd[MaxN],o1[MaxN],o2[MaxN];
bool cmp(int A,int B){return h[A]<h[B];}
vector<int> g[MaxN];
int f[12][MaxN],vist[MaxN],t[MaxN],c[MaxN],dep[MaxN];
int up(int u)
{
  if (vist[u])return u;
  for (int k=10;k>=0;k--)
    if (!vist[f[k][u]])u=f[k][u];
  return f[0][u];
}
bool cmp2(int A,int B){return c[A]==c[B] ? dep[A]>dep[B] : c[A]<c[B];}
const int INF=1000000000;
int cnt[MaxN];
void solve(int *u,int *o,ll lim)
{
  ll s=0;
  for (int i=1;i<=n;i++)o[i]=cnt[i]=0;
  for (int i=1;i<=k;i++){
    s+=h[u[i]];
    o[u[i]]^=rnd[i];
    cnt[u[i]]++;
  }
  for (int i=1;i<n;i++){
    int u=p[i],v=t[u];
    if (!cnt[u])continue;
    if (s+c[u]>lim)break;
    o[v]^=o[u];o[u]=0;
    s+=1ll*cnt[u]*(h[v]-h[u]);
    cnt[v]+=cnt[u];cnt[u]=0;
  }
}
bool chk(ll lim)
{
  solve(u1,o1,lim);solve(u2,o2,lim);
  for (int i=1;i<=n;i++)if (o1[i]!=o2[i])return 0;
  return 1;
}
int main()
{
  scanf("%d",&n);F.Init(n);
  for (int i=1;i<=n;i++)scanf("%d",&h[p[i]=i]);
  sort(p+1,p+n+1,cmp);
  for (int i=1,u,v;i<n;i++){
    scanf("%d%d",&u,&v);
    g[u].pb(v);g[v].pb(u);
  }
  for (int j=1;j<=n;j++){
    int u=p[j];vist[u]=1;
    for (int i=0;i<g[u].size();i++){
      int v=F.find(g[u][i]);
      if (u==v||!vist[v])continue;
      f[0][v]=u;F.merge(v,u);
    }
  }
  for (int j=1;j<=10;j++)
    for (int i=1;i<=n;i++)
      f[j][i]=f[j-1][f[j-1][i]];
  for (int i=1;i<=n;i++)vist[i]=0;
  for (int i=1;i<=n;i++){
    int u=p[i];
    if (i>1){
      int v=up(u);
      t[u]=vist[v];
      c[u]=h[v]-h[u];
    }else c[u]=INF;
    for (int v=u;!vist[v];v=f[0][v])vist[v]=u;
  }
  for (int j=2;j<=n;j++)
    dep[p[j]]=dep[t[p[j]]]+1;
  sort(p+1,p+n+1,cmp2);
  scanf("%d",&k);
  ll s1=0,s2=0;
  for (int i=1;i<=k;i++){
    scanf("%d%d",&u1[i],&u2[i]);
    rnd[i]=rand()<<15^rand();
    s1+=h[u1[i]];s2+=h[u2[i]];
  }
  ll l=max(s1,s2),r=1ll<<45,mid;
  while(l<r){
    mid=(l+r)>>1;
    if (chk(mid))r=mid;
    else l=mid+1;
  }printf("%lld",r);
  return 0;
}
```

---

## 作者：DengDuck (赞：3)

感觉是很有意思的题啊！

我的做法和实现同 CCX_CoolMint，但是我的理解不太一样。

首先如果只有一个棋子，那么它一定会老老实实地走，为什么多个棋子不一定这么走呢？因为棋子可以先走到一个不在最短路径的点，让局面的值尽可能小，来让别的棋子移动的时候局面总和小一点，然后你再走出来。

那么这个点显然就是一个点权比你小的点（这里为了区分，我们定义点的编号为第二关键字），然后在这个条件下，因为你移动途中的最大局面代价也是要统计的，所以你这个点权比你小的点你希望你到它的路径的最大值尽可能小。

所以你对于每个点都要求一个点，使得这个点点权比我小，而且我去到你的代价最小，一次深搜可以求出来，总体时间复杂度 $\mathcal O(n)$。

接下来多个棋子一起跳，我们优先跳哪个？显然优先跳的是跳过去过程中的最大局面与当面局面的差最小的先跳，这样因为可以放缓答案被更新成更大的值的进程就被放慢了。

如果跳到最小的点，就别跳了。

这样我们再考虑，我们不断跳到一个比较小的点，然后再去到终点。

从小点走到终点的过程是不是太抽象了，不太好弄啊！我们甚至不能确定跳到什么时候停止。


但是我们想想，我们不妨在终点也放棋子，同时倒过来跑，是不是很有道理，因为你倒过来跑的贡献和正着跑过来的贡献是一样的。

现在你只需要两边一起跑，哪边空了跑哪边，不然哪边跳过去过程中的最大局面与当面局面的差最小的就先跳，什么时候跳到两个局面一样就终止。

这个策略，只要理解了策略到底是个什么东西，它的正确性就比较显然，当然理解需要比较感性。

因为 $2K$ 个棋子跳都是跳到更小的点，所以最多跳 $N$ 次，时间复杂度为 $\mathcal O(NK\log K)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define fir first
#define sec second
using namespace std;
//const LL inf;
const LL N=2e3+5;
//const LL M;
//const LL mod;
//const LF eps;
//const LL P;
LL n,m,a[N],to[N],s[N],t[N],val[N],ss,st,ans=1e15,cnt;
vector<LL>v[N];
priority_queue<pLL>ps,pt;
void dfs(LL x,LL f,LL mx,LL c)
{
	if(a[x]<a[c]||(a[x]==a[c]&&x<c))
	{
		if(!to[c]||mx<val[c])to[c]=x,val[c]=mx;
		if(mx==val[c])to[c]=min(to[c],x);
	}
	for(LL i:v[x])
	{
		if(i==f)continue;
		dfs(i,x,max(mx,a[i]),c);
	}
}
void works()
{
//	cout<<"s"<<endl;
	LL x=ps.top().sec;
	ps.pop();
	ans=max(ans,ss+val[s[x]]);
	ss-=a[s[x]];
	if(s[x]!=t[x])cnt--;
	s[x]=to[s[x]];
	ss+=a[s[x]];
	if(s[x]!=t[x])cnt++;
	if(to[s[x]])ps.push({-val[s[x]],x});
}
void workt()
{
//	cout<<"t"<<endl;
	LL x=pt.top().sec;
	pt.pop();
	ans=max(ans,st+val[t[x]]);
	st-=a[t[x]];
	if(s[x]!=t[x])cnt--;
	t[x]=to[t[x]];
	st+=a[t[x]];
	if(s[x]!=t[x])cnt++;
	if(to[t[x]])pt.push({-val[t[x]],x});
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n-1;i++)
	{
		LL x,y;
		cin>>x>>y;
		v[x].pb(y),v[y].pb(x);
	}
	for(int i=1;i<=n;i++)
	{
		dfs(i,0,a[i],i);
		val[i]-=a[i];
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		LL x,y;
		cin>>x>>y;
		s[i]=x,t[i]=y;
		if(to[s[i]])ps.push({-val[x],i});
		if(to[t[i]])pt.push({-val[y],i});
		ss+=a[x],st+=a[y];
		cnt+=x!=y;
	}
	ans=max(ss,st);
	while(cnt)
	{
		if(ps.empty())workt();
		else if(pt.empty())works();
		else if(ss-ps.top().fir<st-pt.top().fir)works();
		else workt();
	}
	cout<<ans<<endl;
	return 0;
}
//RP++
```

---

## 作者：CCX_CoolMint (赞：2)

首先考虑如下容易想到的贪心方法：

令 $f_i$ 为某一颗个棋子 $i$ 下一步要经过的点的点权。

对于每一个点，我们考虑它到终点的路径上经过的下一个点，我们想要答案尽可能小，那么对于下一步的局面，肯定是移动 $f_i$ 最小的棋子最优。但显而易见，这样的贪心方法是错误的，因为我们并没有考虑以后的每一个局面是否最优。

考虑动态规划？比赛结束后，发现它仍然可以用贪心来做，只要保证贪心的正确性就可以了。

根据上面的贪心方法，我们可以这样考虑：

 - 如果对于某一个点 $i$，我们将其移动到比它自身点权要小的一个点上，那么此时对于这个操作后的下一步操作，相较于移动当前尚未移动棋子的情况，其总潜能的最大值是不会变大的。那么我们只要考虑在移动的过程中，保证潜能增大的量最小就可以了，这样的移动方式这样可以满足最大值最小。
 - 而考虑中间的移动过程，对于一次抉择过程，假设我们选择了一颗棋子可以使潜能增大的量最小，即路径中经过的点权最大值最小，那么优先移动这颗棋子所造成的的潜能增大量一定会比优先移动其他棋子的潜能增大量要小，因为这颗棋子在走到终点后点权变小的过程中，其路径上的潜能增大量相较于其他棋子也是更小的，而后再移动其他棋子增大量也会基于这个最小增大量，那么优先移动这颗棋子一定是最优的且不会有更优于它的棋子。这样往后多考虑一些点而不止一个的方法，正确性便可得以证明。
 
思考做法。我们对于任意一颗棋子，如果直接考虑到达终点行动轨迹，似乎有些难想。但是，棋子一定能够有路径从起点走到终点，那我们在终点设置一颗虚拟的棋子，让它也依照上面的贪心方法移动，最终一定能够让两颗棋子相遇，这样就能够形成一条完整的路径，那么它就是答案路径。面对两颗棋子可能多次相遇，意味着后面有更优的点使得潜能更小，那么我们选择它们最后一次相遇的点作为两条轨迹的连接点即可。

具体做法如下：
设 $f_i$ 为要跳到的比自身点权小的点，$w_i$ 为跳过去的路径中点权最大值的最小值，$sum$ 为一开始尚未移动棋子的局面的潜能。那么跳过去之后当前潜能将变为 $sum-h_i+h_{f_i}$，而在移动过程中潜能最大值为 $sum-h_i+w_i$。首先用 dfs 找出每一个点往后的路径的点权最大值得到 $w_i$。接着我们用两个优先队列，一个为真实棋子队列 ``qs``，一个为虚拟棋子队列 ``qt``，分别将真实棋子和虚拟棋子的 $w_i$ 值放进去，最优策略显然是移动当前 $w_i$ 值最小的棋子，简单分为下面四种情况：

 1. 队列 ``qs`` 为空，此时 ``qt`` 中的虚拟棋子进行移动
 2. 队列 ``qt`` 为空，此时 ``qs`` 中的真实棋子进行移动
 3. $sums$ 减去 ``qs`` 队列中 $w_i$ 值最小的棋子小于 $sumt$ 减去 ``qt`` 队列中 $w_i$ 值最小的棋子，此时移动 ``qs`` 队列中的棋子更优
 4. 反之于第三种情况，此时移动 ``qt`` 队列中的棋子更优。

按照上述贪心方法对棋子进行移动，直到所有对应真实棋子和虚拟棋子相遇为止，最终的答案即为潜能最大值的最小值。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,u,v,p[5000],head[5000],cnt,k,s[5000],t[5000];
ll mx[5000],f[5000],w[5000],ss,st,dif,ans;
//f是要跳到的比自身点权小的点，w是跳过去的路径中点权最大值的最小值
priority_queue<pair<ll,ll> >qs,qt;
struct node
{
    ll to,nxt;
}e[5000];
void add(ll x,ll y)
{
    e[++cnt].to=y;
    e[cnt].nxt=head[x];
    head[x]=cnt;
}
void dfs(ll x,ll fa)
{
    mx[x]=max(p[x],mx[fa]);
    for(int i=head[x];i;i=e[i].nxt)
    {
        ll y=e[i].to;
        if(y!=fa) dfs(y,x);
    }
}
void works()
{
    ll x=qs.top().second;
    qs.pop();
    ans=max(ans,ss+w[s[x]]);
    ss-=p[s[x]];
    if(s[x]!=t[x]) dif--;
    s[x]=f[s[x]];
    ss+=p[s[x]];
    if(s[x]!=t[x]) dif++;
    if(f[s[x]]) qs.push({-w[s[x]],x});
}
void workt()
{
    ll x=qt.top().second;
    qt.pop();
    ans=max(ans,st+w[t[x]]);
    st-=p[t[x]];
    if(s[x]!=t[x]) dif--;
    t[x]=f[t[x]];
    st+=p[t[x]];
    if(s[x]!=t[x]) dif++;
    if(f[t[x]]) qt.push({-w[t[x]],x});
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<n;i++)
    {
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++)
    {
        dfs(i,0);
        for(int j=1;j<=n;j++)
        {
            if(p[i]>p[j]||(p[i]==p[j]&&j<i))
            {
                if(!f[i]||mx[j]<w[i]||(mx[j]==w[i]&&j<f[i]))
                {
                    f[i]=j;
                    w[i]=mx[j];
                }
            }
        }
        w[i]-=p[i];
    }
    cin>>k;
    for(int i=1;i<=k;i++)
    {
        cin>>s[i]>>t[i];
        ss+=p[s[i]],st+=p[t[i]];
        if(f[s[i]]) qs.push({-w[s[i]],i});
        if(f[t[i]]) qt.push({-w[t[i]],i});
        if(s[i]!=t[i]) dif++;
    }
    ans=max(ss,st);
    while(dif)
    {
        if(qs.empty()) workt();
        else if(qt.empty()) works();
        else if(ss-qs.top().first<st-qt.top().first) works();
        else workt();
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

这种最大值最小化的题一般可以先考虑二分。设二分了一个 $mid$。

记 $A = (a_1,a_2,...,a_k)$ 为表示每个棋子的位置的状态，如果 $A,B$ 可以互相到达，就在它们之间连一条无向边。则要判断的是 $S = (s_1,s_2,...,s_k)$ 和 $T = (t_1,t_2,...,t_k)$ 是否在同一连通块内。

记 $f(A)$ 为 $\sum\limits_{i=1}^k a_{A_i}$，那我们不妨让 $S$ 和 $T$ 都到达一个 $f(A)$ 最小的状态 $A$（如果 $f(A)$ 相同则比较字典序）。如果两个 $A$ 都相同，则 $S,T$ 在同一连通块内，否则不在。

设 $g(A)$ 为 $A$ 能到达的最小状态，则问题转化成了求 $g(A)$。

考虑一个暴力做法：每次找到能移的棋子中造成的贡献最大的，移动这个棋子（需要预处理点 $u$ 经过权值不超过 $D$ 的点能到达的所有点的点权最小值）。因为每个棋子的移动不会重复经过某个点，所以最多移动 $O(nk)$ 次。时间复杂度是 $O(nk^2 \log n \log ans)$，[显然会 T](https://atcoder.jp/contests/arc115/submissions/40914722)。

考虑加点优化。用堆维护下一个贡献最大的操作。每次 $\sum\limits_{i=1}^k a_i$ 变小时，一些点的移动会变得合法，将它们加入堆中即可。需要[精细实现](https://atcoder.jp/contests/arc115/submissions/40923965)，复杂度 $O(\text{可过})$。

---

## 作者：zzh0755 (赞：1)

# 题意如下
   一棵树每个点有权值 $h_{i} $ ，有 $k$ 个人，初始状态每个人在 $s_{i}$ ，终止状态每个人在 $t_{i} $ 。一个状态的代价为 $\sum h_{a_{i} }$ ，其中 $a_{i}$ 表示 $i$ 此时所在位置。每个时刻选一个人走一步。要求经过的状态中最大值最小。$（n,k≤2000）$
# 方法
 如果二分出一个上界 $\lim$ ，考虑如下做法：让 $S$ 和 $T$ 都走的到可到达的状态中的最低点，如果它们相遇了，那就合法。

把状态以及状态之间的转移看做一个图，显然这是双向的。所以如果规定了唯一的最低点并且它们都能到达，那么它们之间一定能互相到达。

现在对于每个点 $x$ ，求 $f_{x}$ 表示满足 $h_{y}<h_{x}$（或$h_{x}=h_{y}$,$y<x$）的 $y$ 中满足 $x$ 到 $y$ 路径上的最大值最小的 $y$ ，$w_{x}$ 表示 $x$ → $f_{x}$ 路径上的最大值。显然 $(x,f_{x})$ 连成了一棵内向森林。

于 $S$（或 $T$ ）中每次取出 $w_{x}$ 最小的 $x$ ，如果从 $x$ 跳到 $f_{x}$ 没有超过上限，那就跳过去。由于总和减小，这样操作一定会利于后面的操作，于是一定能到达最低点。

然后发现其实可以不用二分。就是在 $S , T$ 不重合时，取出 $S$ 和 $T$ 中 $w_{x}$ 最小的 $x$，扩大上界。

用个堆维护一下，时间 $\mathcal{O}(nk\;lg\;n)$ 。

另外还有性质：如果有 $f_{x}=y,f_{y}=z$ ，则 $w_{x} \le w_{y}$ 。具体证明可以根据 $x,y,z$ 所在位置分类讨论。所以实际上操作的时候，相当于 $(x,f_{x})$ 连出的树上每次剥叶子。把在同一个叶子上的点一起操作，时间就是 $\mathcal{O}(n\;lg\;n+k)$ 。

# 代码如下
```cpp
using namespace std;
#include <bits/stdc++.h>
#define N 2005
#define ll long long
#define INF 10000000000000
#define fi first
#define se second
#define mp(x,y) make_pair(x,y)
int n,K;
int h[N];
struct EDGE{
	int to;
	EDGE *las;	
} e[N*2];
int ne;
EDGE *last[N];
void link(int u,int v){
	e[ne]={v,last[u]};
	last[u]=e+ne++;
}
int s[N],t[N];
ll mx[N];
int to[N];
ll w[N];
void dfs(int x,int fa,ll s){
	mx[x]=max(mx[fa],s);
	for (EDGE *ei=last[x];ei;ei=ei->las)
		if (ei->to!=fa)
			dfs(ei->to,x,s+h[ei->to]-h[x]);
}
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > qs,qt;
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;++i）scanf("%d",&h[i]);
	for (int i=1；i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		link(u,v)，link(v,u)；
	}
	scanf("%d",&K);
	for (int i=1;i<=K;++i)
		scanf("%d%d",&s[i],&t[i]);
	mx[0]=-INF;
	for (int i=1;i<=n;++i){
		dfs(i,0,0);
		for (int j=1;j<=n;++j)
			if (h[j]<h[i] || h[j]==h[i] && j<i){
				if (to[i]==0 || mx[to[i]]>mx[j])
					to[i]=j,w[i]=mx[j];
			}
	}
	int cnt=0;
	ll S=0,T=0,ans=0;
	for (int i=1;i<=K;++i){
		S+=h[s[i]],T+=h[t[i]];
		if (to[s[i]]) qs.push(mp(w[s[i]],i));
		if (to[t[i]]) qt.push(mp(w[t[i]],i));
		cnt+=(s[i]!=t[i]);
	}
	ans=max(S,T);
	while (cnt>0/* && (!qs.empty() || !qt.empty())*/){
		if (qt.empty() || !qs.empty() && S+qs.top().fi<T+qt.top().fi){
			int x=qs.top().se;
			qs.pop();
			ans=max(ans,S+w[s[x]]);
			cnt-=(s[x]!=t[x]）;
			S-=h[s[x]];
			s[x]=to[s[x]];
			S+=h[s[x]];
			cnt+=(s[x]!=t[x])；
			if (to[s[x]])
				qs.push(mp(w[s[x]],x));
		}
		else{
			int x=qt.top().se;
			qt.pop()；
			ans=max(ans,T+w[t[x]]);
			cnt-=(s[x]!=t[x]）;
			T-=h[t[x]];
			t[x]=to[t[x]];
			T+=h[t[x]];
			cnt+=(s[x]!=t[x]);
			if (to[t[x]])
				qt.push(mp(w[t[x]],x));
		}
	}
	printf("%lld\n",ans）;
	return 0;
}
```
### 审核大大求过，小蒟蒻元旦假期没了。


---

## 作者：Inui_Sana (赞：0)

一个跑了整整 3900ms 的做法。

考虑如果当前有一个状态 $A$ 能在和不超过 $lim$ 的前提下到达一个状态 $B$，则 $B$ 在同样条件的前提下也能到达 $A$。

于是对于初始状态 $S$，会发现最优策略一定是先把和变得尽可能小，达到状态 $R$，以此让某些要经过很大值的点通过，然后再变成结束状态 $T$。

如果我们想知道一个状态 $A$ 在操作过程中和不超过 $lim$ 的前提下，和尽可能小的状态 $B$ 是简单的。考虑记录 $d_{i,j}$ 表示一个棋子从 $i$ 点移动到 $j$ 点，其他不动，会使和 $s$ 增加多少。

容易发现我们只会把棋子从 $h_i$ 大的移动到 $h_i$ 小的。同时，若 $dis_{i,j}<dis_{i,k}$，先移动到 $j$ 一定不劣。于是对于每个位置 $u$，下一次会移动到的点 $to_u$ 是固定的，只需要每次找可移动的点移动即可。一共会移动 $O(n^2)$ 次，使用优先队列优化后这一部分是 $O(n^2\log n)$ 的。

但是此时又发现一个问题：求 $R$ 是否能到达 $T$ 是困难的。但是由于一开始给出的结论，考虑对于 $T$ 求出它能到达的和最小的状态 $R'$，于是只用求 $R$ 是否能到达 $R'$。

这个判断是简单的，容易发现，若 $R$ 和 $R'$ 中两个对应的棋子的 $h$ 不同，则一定无解。因为若 $R$ 中的 $h_x$ 小于 $R'$ 中的 $h_y$，那么说明这个 $x$ 无法到达 $y$，否则 $R$ 会变化。于是只用判断此时 $R$ 的和 $sum$ 是否有 $sum+\max dis_{x,y}\le lim$ 即可。

同时这个 $lim$ 显然是可二分的，所以二分答案，复杂度为 $O(n^2\log V\log n)$。

然而此时大概率还无法通过。于是卡卡常，首先是发现设 $S,T$ 的和分别为 $s,t$，则二分边界可以设成 $l=\max(s,t),r=l+10^9$。同时，发现 at 的 c++17 比 c++20 要快。于是 3900ms 通过。

code：

```cpp
int n,m,dis[N][N],a[N],b[N],c[N],f[N],g[N],to[N];
priority_queue<pii> q;
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void dfs(int u,int f,int s){
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dis[s][v]=max(dis[s][u],c[v]-c[s]);
		dfs(v,u,s);
	}
}
bool check(ll lim){
	ll s=0,t=0;
	rep(i,1,m){
		s+=c[a[i]],t+=c[b[i]];
	}
	while(q.size()){
		q.pop();
	}
	rep(i,1,m){
		f[i]=a[i];
		if(to[f[i]]){
			q.emplace(-dis[f[i]][to[f[i]]],i);
		}
	}
	while(q.size()){
		int u=q.top().se,w=-q.top().fi;
		q.pop();
		if(s+w>lim){
			break;
		}
		s+=c[to[f[u]]]-c[f[u]];
		f[u]=to[f[u]];
		if(to[f[u]]){
			q.emplace(-dis[f[u]][to[f[u]]],u);
		}
	}
	while(q.size()){
		q.pop();
	}
	rep(i,1,m){
		g[i]=b[i];
		if(to[g[i]]){
			q.emplace(-dis[g[i]][to[g[i]]],i);
		}
	}
	while(q.size()){
		int u=q.top().se,w=-q.top().fi;
		q.pop();
		if(t+w>lim){
			break;
		}
		t+=c[to[g[u]]]-c[g[u]];
		g[u]=to[g[u]];
		if(to[g[u]]){
			q.emplace(-dis[g[u]][to[g[u]]],u);
		}
	}
	int mx=0;
	rep(i,1,m){
		if(c[f[i]]!=c[g[i]]){
			return 0;
		}
		mx=max(mx,dis[f[i]][g[i]]);
	}
	return s+mx<=lim;
}
void Yorushika(){
	read(n);
	rep(i,1,n){
		read(c[i]);
	}
	rep(i,1,n-1){
		int u,v;read(u,v);
		add(u,v),add(v,u);
	}
	rep(i,1,n){
		dfs(i,0,i);
	}
	rep(i,1,n){
		rep(j,1,n){
			if(c[j]<c[i]){
				if(!to[i]||dis[i][j]<dis[i][to[i]]){
					to[i]=j;
				}
			}
		}
	}
	read(m);
	ll s=0,t=0;
	rep(i,1,m){
		read(a[i],b[i]);
		s+=c[a[i]],t+=c[b[i]];
	}
	ll l=max(s,t),r=l+1e9,ans=1ll*inf*inf;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	// read(t);
	while(t--){
		Yorushika();
	}
}
```

话说好像不用二分，就不卡常了。

---

