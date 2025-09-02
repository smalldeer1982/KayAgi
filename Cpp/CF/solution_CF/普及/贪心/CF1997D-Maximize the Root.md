# Maximize the Root

## 题目描述

给你一棵有根的树，由 $n$ 个顶点组成。树上的顶点从 $1$到 $n$ 编号，根是顶点 $1$ 。第 $i$ 个顶点上的值为 $a_i$。

你可以执行以下操作任意次(可以为零次):选择一个至少有一个子顶点的顶点 $v$; 将 $a_v$ 增加 $1$ 并且对于 $v$ 的子树中的所有顶点 $u$ 将 $a_u$ 减少 $1$ (除了 $v$ 本身)。但是，在每次操作之后，所有顶点上的值都应该是非负的。

你的任务是使用前面提到的运算来计算写在根上的最大可能值。

## 样例 #1

### 输入

```
3
4
0 1 0 2
1 1 3
2
3 0
1
5
2 5 3 9 6
3 1 5 2```

### 输出

```
1
3
6```

# 题解

## 作者：Muse_Dash (赞：8)

若只题，这难度最多橙题。

发现对于 $1$ 节点，其在原数值基础上能增加的答案是 $\min\limits_{i=2}^na_i$。因此 要使得 $\min\limits_{i=2}^na_i$ 最大。

如遍历到 $u(u\neq1)$ 节点，如果其值作为以其为根的子树最小值，那么就要考虑消耗除他以外的子树节点的值，使得 $\min$ 最大。$u=1$，不需要考虑总子树 $\min$ 最大，而是消耗其他节点直到其他节点的 $\min$ 为 $0$。

dfs 这个过程即可，复杂度 $\Theta(n)$，搞不懂某些人为什么写二分。


```cpp
void dfs(int u,int fa){
	mn[u]=1e18;
	for (auto v:e[u]){
		if (v==fa) continue;
		dfs(v,u);
		mn[u]=min(mn[v],mn[u]);
	}
	if (mn[u]==1e18) mn[u]=a[u];
	if (mn[u]>a[u]&&u!=1) mn[u]=(mn[u]+a[u])/2;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：5)

考虑类似贪心的做法。

对于每一个节点，若要使其节点能达到的值最大，则其子树中的节点中的最小值也一定要尽可能大。

定义 $dis_i$ 为节点 $i$ 的子树中所可能达到的最大的最小值。

假设 $u$ 是 $v$ 的子节点，接下来分类讨论：

如果 $a_v\ge dis_u$，那没什么好说的，$dis_v$ 显然等于 $dis_u$（无法将父节点的值“传”给子节点）。

如果 $a_v<dis_u$，则 $dis_v=\lfloor\dfrac{a_v+dis_u}{2}\rfloor$（可以将子节点的值“传”给父节点，下取整的原因是求的是最小值）。

为什么这里不是将子树的权值全部加起来求平均值？因为父节点增加 $1$，所有其他的节点全部都要减 $1$，即只有最小值和原有的权值 $a_v$ 决定了 $dis_v$ 的值。

如果一个节点有多个子节点，显然取在多个算得结果中取最小值即可。

由于我们知道对于任意一个叶子节点 $leaf$，$dis_{leaf}=a_{leaf}$，那么根据上述操作我们可以得出整棵树的 $dis$ 值。

______

问题来了，就算知道了 $dis$ 数组怎么求题目要求的根节点最大值？

答案十分显然，将根节点权值和剩余节点中的最小值相加即可。

至于如何进行对树的遍历，方法一抓一大把，本人用的是拓扑排序，正确性无误即可。

_______

此处提醒：注意多测清空以及清空方式，本人赛时查了半个小时错愣是没看出来。

上代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dis[1000005];
int p[1000005];
int a[1000005];
int in[1000005];
struct node{
	int v,w,next;
}edge[1000005];
int num;
int head[1000005];
void add(int u,int v,int w){
	edge[++num].next=head[u];
	head[u]=num;
	edge[num].w=w;
	edge[num].v=v;
}
queue<int>q;
void tupo(){
	while(!q.empty()){
		int t=q.front();
		q.pop();
		if(t==1)continue;
		for(int i=head[t];i;i=edge[i].next){
			int v=edge[i].v;
			if(dis[t]>=a[v]){
				if(v==1){
					dis[v]=min(dis[v],dis[t]);
				}
				else
				dis[v]=min(dis[v],(dis[t]+a[v])/2);
			}
			else{
                if(v==1){
					dis[v]=min(dis[v],dis[t]);
				}
                else
				dis[v]=min(dis[v],min(dis[t],a[v]));
			}
			in[v]--;
			if(!in[v])q.push(v);
		}
	}
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		while(!q.empty())q.pop();
		num=0;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			head[i]=0;
		}
		for(int i=1;i<=n;i++){
			in[i]=0;
		}
		for(int i=1;i<=n;i++){
			dis[i]=0x3f3f3f3f3f3f3f3f;
		}
		for(int i=2;i<=n;i++){
			int p;
			cin>>p;
			add(i,p,0);
			in[p]++;
		}
		for(int i=2;i<=n;i++){
			if(in[i]==0){
				q.push(i);
				dis[i]=a[i];
			}
		}
		tupo();
		cout<<dis[1]+a[1]<<endl;
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：4)

> 给出一棵树，带点权，每次操作可以选定一个 $u$，将 $u$ 的子树中除 $u$ 外的每个节点权值减 $1$，$u$ 的权值加 $1$。求在保证任何时刻每个节点点权非负的情况下节点 $1$ 的权值能达到的最大值。

不难发现若不操作子树，节点 $1$ 的最多操作数为其子节点的子树中点权的最小值。

考虑使子树的最小值最大，递归求解。若当前根节点的点权 $a_u$ 小于其所有子节点的子树的点权最小值 $a_{min}$，则对该节点进行操作直到 $a_u=a_{min}$ 或 $a_{min}-a_u=1$，将 $a_u$ 返回。若 $a_u$ 大于等于 $a_{min}$ 则不对 $u$ 进行操作，将 $a_{min}$ 返回。

实现时需从节点 $1$ 的每个子节点开始递归，设所有子节点的答案为 $a_{min}$，则最终答案为 $a_1+a_{min}$。

```cpp
#include <bits/stdc++.h>
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=2e5+10;
int T,n,a[N],f[N];
vector<int> g[N];
int dfs(int u){
	if(!g[u].size()) return a[u];
	int mn=0x3f3f3f3f;
	for(auto v:g[u]) mn=min(mn,dfs(v));
	if(a[u]>=mn) return mn;
	else return (a[u]+mn)>>1;
}
void solve(){
	read(n);
	int mx=0;
	rep(i,1,n) read(a[i]),g[i].clear(),mx=max(mx,a[i]);
	rep(i,2,n){
		read(f[i]);
		g[f[i]].push_back(i);
	}
	int mn=0x3f3f3f3f;
	for(auto v:g[1]) mn=min(mn,dfs(v));
	printf("%d\n",a[1]+mn);
}
int main(){
	read(T);while(T--) solve();
	return 0;
}
```

---

## 作者：vorDeal (赞：3)

赛时首次切 Div.2 D 祭。

给你一棵树，可以通过将一个节点为根的子树中的每一个节点的值减少一个整数，增加该节点的权值这个整数，在每个节点的值非负的前提下，最大化根节点的权值。

考虑树上贪心。我们分三种节点来讨论：

1. 叶子节点  
   无需操作。
2. 根节点  
   求得其儿子的最小值，直接与根节点相加即可。
3. 普通节点  
   求得其儿子的最小值。  
   由于是要将子树中的每一个节点的值减少，所以对于该节点的上一级，我们只能取该节点及其儿子的最小值作为贡献，所以我们对该节点及其儿子的最小值平均地分配权值。  
   注意：父节点不能倒贴给儿子节点！

请使用链式前向星存图，经实践，vector 存图会 MLE。

数据千万条，清空第一条。多测不清空，爆零两行泪。

时间复杂度为 $O(\sum n)$，可以通过本题。

**AC Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, p, tot;
int a[200005], f[200005];
int ver[200005], nxt[200005], head[200005];

void add(int x, int y)
{
    ver[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
    return;
}

void dfs(int u)
{
    if (head[u] == 0)
    {
        f[u] = a[u];
        return;
    }
    int minn = 1e9 + 5;
    for (int i = head[u]; i > 0; i = nxt[i])
        dfs(ver[i]), minn = min(minn, f[ver[i]]);
    if (u == 1)
    {
        f[1] = minn + a[1];
        return;
    }
    if (a[u] < minn)
        f[u] = (a[u] + minn) >> 1;
    else
        f[u] = minn;
    return;
}

void solve()
{
    tot = 0;
    for (int i = 1; i <= n; i++)
        f[i] = head[i] = ver[i] = nxt[i] = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 2; i <= n; i++)
        cin >> p, add(p, i);
    dfs(1);
    cout << f[1] << endl;
    return;
}

int main()
{
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：coding_goat (赞：3)

注意到对于每一个节点的大小只与所有子节点的最小值有关，因此保存每个节点的最小值 $minn$，我们用设 $u$ 为 $i$ 的所有子节点，$\min(minn_u)$ 表示对于 $i$ 的所有子节点的最小值。如果当前的 $a_i < \min(minn_u)$，那么将同时操作 $a_i$ 使其变为不超过 $\min(minn_u)$ 的最大值。对于根节点，答案为 $a_1+\min(minn_u)$（其中 $u$ 为 $1$ 的所有子节点）。

---

## 作者：白鲟 (赞：2)

这个 D 题能秒我？诶还真是。

思路很容易。

首先二分转为判定性问题。

贪心地，最优的操作顺序必然是从叶结点到根结点。这可以保证对每个结点都是先增后减，更容易非负。顺序的影响由此消除。

接下来只需要使得每个结点的峰值至少能保证它在它的祖先所做的减法后非负。从根结点扫下来，累计已经做过的减法，即可得到当前结点所需要达到的峰值的最小值，亦即可以得到当前结点需要补做的加法的值。最后判断叶结点的值是否满足条件即可。

时间复杂度为 $\operatorname{O}(n\log V)$。接下来才是重头戏：二分的 $l + r$ 的范围会超过 `int`，这一点会让你 TLE on 16；若作判定的值过大会超过 `long long`（可以指数增长），需要提前跳出，这一点会让你 WA on 19。另外需要注意如果当前结点的值已经满足条件，不能倒扣，这一点会错在哪儿不知道。

唉。TLE on 16。

```cpp
#include <algorithm>
#include <cctype>
#include <cstdio>
const int maxn = 2e5;
int T, n, tot, a[maxn + 1], parent[maxn + 1], 
    head[maxn + 1], suc[maxn + 1], to[maxn + 1];
using ll = long long;
ll l, r, mid, ans;
bool dfs(int now, ll value) {
    bool ans = true;
    if (value > 2e9) {
        return false;
    }
    if (!head[now]) {
        return a[now] >= value;
    }
    for (int i = head[now]; i; i = suc[i]) {
        ans &= dfs(to[i], value + 
                std::max(value - a[now], 0ll) - (now == 1) * mid);
    }
    return ans;
}
void read(int &x) {
    x = 0;
    char t = getchar();
    while (!isdigit(t)) {
        t = getchar();
    }
    while (isdigit(t)) {
        x = x * 10 + t - '0';
        t = getchar();
    }
    return;
}
int main() {
    read(T);
    while (T--) {
        read(n);
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            read(a[i]);
            head[i] = 0;
        }
        for (int i = 2; i <= n; ++i) {
            read(parent[i]);
            suc[++tot] = head[parent[i]];
            head[parent[i]] = tot;
            to[tot] = i;
        }
        l = a[1], r = 2e9;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (dfs(1, mid)) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：wmrqwq (赞：2)

# 题目链接

[CF1997D Maximize the Root (codeforces)](https://codeforces.com/problemset/problem/1997/D)

[CF1997D Maximize the Root (luogu)](https://www.luogu.com.cn/problem/CF1997d)

# 解题思路

二分答案。

可以逐一计算每个节点在节点一最终的权值为 $Mid$ 时的所需要的付出的代价，可以通过 dfs 来进行代价的下传。

代价的转移比较显然。

时间复杂度 $O(n \log V)$。其中 $V$ 为答案的上界。

注意下传代价时可能会爆 `long long`，记得及时剪枝。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);init();
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
ll n;
ll a[200010];
vector<ll>G[200010];
ll L,R;
ll fl;
ll x,y;
void dfs(ll x,ll fa,ll need)
{
	if(need>1e17)
	{
		fl=0;
		return ;
	}
	ll pd=0;
	for(auto i:G[x])
		if(i!=fa)
			pd=1,dfs(i,x,need+max(0ll,need-a[x]));
//	cout<<x<<' '<<fa<<' '<<need;
	if(pd==0 && a[x]<need)
	{
//		need=max(need-a[x],0ll);
		fl=0;
	}
}
bool check(ll x)
{
	fl=1;
	for(auto i:G[1])
		dfs(i,1,x-a[1]);
	return fl;
}
void solve()
{
	_clear();
	cin>>n;
	forl(i,0,n+2)
		G[i].clear();
	forl(i,1,n)
		cin>>a[i];
	forl(i,2,n)
		cin>>x,G[x].pb(i),G[i].pb(x);
	L=0,R=1e10;
	while(L<R)
	{
		ll Mid=(L+R+1)/2;
		if(check(Mid))
			L=Mid;
		else
			R=Mid-1;
	}
	cout<<L<<endl;
}
void init(){}
int main()
{
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：tzzl3035 (赞：1)

# CF1997D 题解
### 声明：
本蒟蒻的做法有猜的成分，但未参考其它题解。所以若有错误，请点击下方本蒟蒻的 Codeforces 原站的**赛时提交记录**尝试 hack，或告知本蒟蒻。
### 题目大意
有 $t$ 组数据，每组给出一个有根树，有 $n$ 个节点，第 $1$ 个为根节点，接着输入一行 $n$ 个正整数 $a_i$，表示每个节点的权值。接着输入一行 $n-1$ 个正整数 $p_i$，表示除根节点外每个节点的父亲节点。定义一次操作为将一个有子节点的节点权值增加 $1$，且将**子树中每个节点**的权值减少 $1$，**每个节点的权值不为负数**。问进行任意次操作后，**根节点的最大权值**为多少。
### 大致思路
经过研究样例，寻找规律，可以发现，我们可以定义一个递归函数，如果某个节点为叶子节点，返回本身的权值，否则遍历节点的每个叶子节点，进行递归，取递归结果中的最小值。若最小值比节点权值小，返回这个最小值，否则返回两者的平均值。将根节点每个孩子节点进行递归，最后取最小值加上根节点的权值输出即可。
### 核心代码
```cpp
void solve() {
  // 输入
  int n;
  std::cin >> n;
  std::vector<long long> a(n+3);
  std::vector<std::set<int>> p(n+3);
  for(int i = 1; i <= n; ++i) 
    std::cin >> a[i];
  for(int i = 2; i <= n; ++i) {
    int fa; std::cin >> fa;
    p[fa].insert(i);
  }
  // 递归函数
  auto f = [&](auto && f, int x) -> long long {
    if(p[x].size() == 0) 
      return a[x];
    long long omin = 1e18;
    for(int i: p[x]) {
      omin = std::min(omin, f(f, i));
    }
    if(omin >= a[x]) return (omin+a[x]) >> 1;
    else return omin;
  };
  // 递归根节点的孩子节点
  long long amin = 1e18;
  for(int j: p[1]) amin = std::min(amin, f(f, j));
  // 输出
  std::cout << a[1]+amin << '\n';
}

```
### [RESULT](https://codeforces.com/contest/1997/submission/273575832)

---

