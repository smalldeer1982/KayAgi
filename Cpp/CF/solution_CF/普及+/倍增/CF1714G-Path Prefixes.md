# Path Prefixes

## 题目描述

现有一颗以 $1$ 为根的树，节点编号从 $1$ 到 $n$。

每条边有两个权值，分别为 $a_j$ 和 $b_j$。

输出 $n-1$ 个数 $r_2,r_3\cdots,r_n$，其中 $r_i$ 定义如下：

考虑从根节点（$1$ 号节点）到第 $i$ 号节点 $(2\le i\le n)$ 的路径，令沿该路径每条边的花费 $a_j$ 之和为 $A_i$，则 $r_i$ 为该路径的最长前缀长度，使该前缀的 $b_j$ 之和不大于 $A_i$ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1714G/fb21910eda699947633b658de9a5b141ee71688b.png)

以 $n=9$ 时为例，如上图，蓝色数字表示 $a_j$ 的花费，红色数字表示 $b_j$ 的花费。

在这种情况下：
- $r_2=0$，因为到节点 $2$ 的路径中有 $a_j=5$，只有前缀为 $0$ 时才可能有较小（或相等）的 $b_j$；
- $r_3=3$，因为到节点 $3$ 的路径中 $a_j$ 为 $5+9+5=19$，长为 $3$ 的前缀使 $b_j$ 为 $6+10+1=17(17\le19)$ 符合题意；
- $r_4=1$，因为到节点 $4$ 的路径中 $a_j$ 为 $5+9=14$，长为 $1$ 的前缀使 $b_j$ 为 $6$（这是最长的符合题意的前缀，因为长为 $2$ 的前缀的 $b_j$ 为 $6+10=16$，大于 $ 14 $）；
- $r_5=2$，因为到节点 $5$ 的路径中 $a_j$ 为 $5+9+2=16$，长为 $2$ 的前缀使 $b_j$ 为 $6+10=16$（是最长的符合题意的前缀，因为长为 $3$ 的前缀的 $b_j$ 为 $6+10+1=17$，比 $16$ 大）；
- $r_6=1$，因为到节点 $6$ 的路径中 $a_j$ 为 $2$，长为 $1$ 的前缀使 $b_j$ 等于 $1$；
- $r_7=1$，因为到节点 $7$ 的路径中 $a_j$ 为 $5+3=8$，长为 $1$ 的前缀使 $b_j$ 等于 $6$（这是最长的符合题意的前缀，因为长为 $2$ 的前缀的 $b_j$ 为 $6+3=9$，超出了期望的 $ 8 $）；
- $r_8=2$，因为到节点 $8$ 的路径中 $a_j$ 为 $2+4=6$，长为 $2$ 的前缀使 $b_j$ 为 $1+3=4$；
- $r_9=3$，因为到节点 $9$ 的路径中 $a_j$ 为 $2+4+1=7$，长为 $3$ 的前缀使 $b_j$ 为 $1+3+3=7$。

## 说明/提示

#### 样例解释
第一组样例解释在题目描述。

在第二组样例中：
- $r_2=0$，因为到节点 $2$ 的路径中 $a_j$ 等于 $1$，只有前缀为 $0$ 时才可能有较小（或相等）的 $b_j$；
- $r_3=0$，因为到节点 $3$ 的路径中 $a_j$ 为 $1+1=2$，长为 $1$ 的前缀使 $b_j$ 等于 $100( 100>2)$；
- $r_4=3$，因为到节点 $4$ 的路径中 $a_j$ 为 $1+1+101=103$，长为 $3$ 的前缀使 $b_j$ 为 $102$。

## 样例 #1

### 输入

```
4
9
1 5 6
4 5 1
2 9 10
4 2 1
1 2 1
2 3 3
6 4 3
8 1 3
4
1 1 100
2 1 1
3 101 1
4
1 100 1
2 1 1
3 1 101
10
1 1 4
2 3 5
2 5 1
3 4 3
3 1 5
5 3 5
5 2 1
1 3 2
6 2 1```

### 输出

```
0 3 1 2 1 1 2 3 
0 0 3 
1 2 2 
0 1 2 1 1 2 2 1 1```

# 题解

## 作者：SmallBlack (赞：7)

**upd** 2022-8-5：感谢 @随弑stay 提出的代码漏洞，已修改

#### 前言：
闲着没事帮同学上分，结果创下了赛时 $30$ 分钟过这道题的好成绩……

### 正文：

#### 题意简述

（这里为了简便，直接套用原题中用以解释样例的图片）

![CF1714G原题图片](https://espresso.codeforces.com/bd6d8cb2c85fc5a38647dbbb0d01d503860c4807.png)

- 给定一个点数为 $n$ 且每条边有两种边权 $a,b$ 的树，其中 $n \le 2\times 10^5$，保证树的根节点为 $1$（图中使用了两种颜色的数字代表一条边的两种边权，蓝色对应边权 $a$，红色则对应 $b$）。
- 我们定义 $A_x$ 表示 $1$ 到 $x$ 的路径上边权 $a$ 的总和。
- $r_x$表示：从 $1$ 开始沿着 $1$ 到 $x$ 的路径，最多可以走过 $r_x$ 个点，满足经过的边的边权 $b$ 之和不超过 $A_x$。
- 要求输出 $r_2,r_3,...,r_n$。
- 多组测试数据，保证 $\sum n \le 2\times 10^5$。

#### 做题思路

首先我们观察 $n$ 的数据范围在 $2\times 10^5$ 以下。~~盲猜~~依照经验，时间复杂度为 $O(n\log n)$。

题目中提到了“从 $1$ 走到节点 $x$ 经过的边的边权 $b_i$ 之和”，为了方便，我在后文将其记作 $B_x$。

在题目里又有两个关键字眼：**最多**和**不超过**，我们可以想到**二分**这一思想。

做和树有关的题目，dfs 是不可或缺的，我们可以尝试利用它得到各个节点 $r_x$ 的值，用数组存下并在程序最后输出。

于是一个暴力求解想法在我们的脑中浮现：

1. 先进行一次 dfs，存下各个节点 $A_x$ 的值。
2. 再次搜索，把当前经过的节点对应的 $B_x$ 存入一个栈中。
3. 在栈中的元素找到最后一个小于等于 $A_x$ 的数，并存下这个数在栈中的位置。

第 $1,2$ 步的时间复杂度为 $O(n)$，第 $3$ 步的时间复杂度为 $O(n\log n)$，总时间复杂度 $O(n\log n)$，可以通过此题。

#### 代码实现

有部分细节会在代码中注释。

```
// Problem: G. Path Prefixes
// Contest: Codeforces - Codeforces Round #811 (Div. 3)
// URL: https://codeforc.es/contest/1714/problem/G
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Date:2022-08-01 22:48:15
// By:SmallBlack
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long s=0,k=1;
	char c=getchar();
	while(!isdigit(c))
	{
		k=(c=='-')?-1:1;
		c=getchar();
	}
	while(isdigit(c))
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*k;
}
#define d read()
#define ll long long
#define Maxn 400010
#define Size 200010
#define mp make_pair
#define pb push_back
#define fi first
#define se second
struct e
{
	ll v,w1,w2,nxt;
}e[Maxn];
ll h[Size],top;
void add(ll u,ll v,ll w1,ll w2)//链式前向星存边
{
	e[top]={v,w1,w2,h[u]};
	h[u]=top;
	top++;
}
ll A[Size];
//第一遍dfs,计算出所有节点A_x的值
ll dfs(ll x,ll fa)
{
	for(int i=h[x];~i;i=e[i].nxt)
	{
		ll v=e[i].v;
		if(v==fa) continue;
		A[v]=A[x]+e[i].w1;
		dfs(v,x);
	}
}
ll ans[Size],B[Size];
vector<ll>now;//我用vector替换stack，因为stack不能用在upper_bound中
//第二遍dfs,计算并存储当前所经过路径上各节点的B_x
void dfs1(ll x,ll fa)
{
	now.pb(B[x]);
	ans[x]=upper_bound(now.begin(),now.end(),A[x])-now.begin()-1;
	//这里我使用upper_bound计算对应的第三步中提到的：
 	//“最后一个小于等于 A_x 的数”
	//upper_bound找到的是第一个严格大于 A_x 的数
	//因此，这个数的前一个便是我们想求的数
	for(int i=h[x];~i;i=e[i].nxt)
	{
		ll v=e[i].v;
		if(v==fa) continue;
		B[v]=B[x]+e[i].w2;
		dfs1(v,x);
	}
	now.pop_back();
}//貌似可以直接合并为一个Dfs?
int main()
{
	ll t=d,n=0;
	while(t--)//多组数据，特别注意初值的设置
	{
		top=0;//清空边
		n=d;
		for(int i=1;i<=n;i++) h[i]=-1;//链式前向星初始化
		for(int i=2;i<=n;i++)
		{
			ll x=d,w1=d,w2=d;
			add(i,x,w1,w2);add(x,i,w1,w2);//加边
		}
		dfs(1,0);
		dfs1(1,0);
		for(int i=2;i<=n;i++) printf("%lld ",ans[i]);//输出
		putchar('\n');
	}
}
```

#### 尾声

第一步看数据范围，可以对正解的时间复杂度有粗略估计，~~也可以用来暴力骗分~~。

---

## 作者：Ginger_he (赞：3)

# 题解

设 $p_i$ 和 $q_i$ 分别为根节点到 $i$ 号点的 $a_i$ 和 $b_i$ 之和，则在 dfs 过程搜到 $i$ 号点时，我们将 $q_i$ 放入 set，并查询 set 中有多少个数不超过 $p_i$，这个值就作为 $r_i$，回溯时弹出 $q_i$ 即可。

## 注意

- 由于 set 不支持查询某个数的 rank，所以我们用 map 记录即可。

- 记得开 long long！！！

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
int t,n,p[N],r[N];
ll a[N],b[N];
vector<int> g[N];
set<ll> s;
map<ll,int> mp;
void dfs(int x)
{
	for(auto i:g[x])
	{
		if(i!=p[x])
		{
			a[i]+=a[x];
			b[i]+=b[x];
			s.insert(b[i]);
			mp[b[i]]=s.size()-1;
			auto it=s.upper_bound(a[i]);
			it--;
			r[i]=mp[*it];
			dfs(i);
			s.erase(b[i]);
		}
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		s.clear();
		mp.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			g[i].clear();
			r[i]=a[i]=b[i]=0;
		}
		for(int i=2;i<=n;i++)
		{
			scanf("%d%d%d",&p[i],&a[i],&b[i]);
			g[p[i]].push_back(i);
		}
		s.insert(0);
		dfs(1);
		for(int i=2;i<=n;i++)
			printf("%d ",r[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Dr_Gilbert (赞：3)

# CF1714G Path Prefixes

【题目大意】给定一棵以 $1$ 为根的有根树，每条边上有 $a,b$ 两种边权。设从根到点 $i$ 路径上的 $a$ 边权和为 $A_i$，设从根到点 $i$ 的 $b$ 边权和为 $B_i$，则定义 $r_i$ 为从根到 $i$ 的路径上，满足 $B_j\le A_i$ 的点 $j$ 中深度最深的点的深度。对于 $i\in [2,n]$，求 $r_i$。根的深度为 $0$。

---

作为 Div.3 G 实在是有点简单了。从根进行 DFS，求出每个点到根的 $a,b$ 边权和，倍增求出每个点的若干级祖先。对于每个点，利用预处理好的倍增数组进行类似于  `upper_bound` 的操作即可。具体地，按 $j$ 从大到小考虑点 $x$ 的 $2^j$ 级祖先，设点 $x$ 的 $2^j$ 级祖先祖先为 $anc$，若 $B_{anc}>A_i$，则令 $x\leftarrow anc$。最后判断 $B_x$ 和 $A_i$ 的关系，若 $B_x>A_i$，往上跳一层，即令 $x\leftarrow fat[x][0]$ 即可。时间复杂度 $\mathcal O(n\log n)$。 参考代码如下（甚至没有我写的 D 长）：

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=3e5+10;
vector<vector<tuple<int,int,int>>> G;
int suma[N],sumb[N],fat[N][20],dep[N];
void dfs(int x, int fa){
    fat[x][0]=fa;dep[x]=dep[fa]+1;
    for (int i=1;i<=18;i++){
        fat[x][i]=fat[fat[x][i-1]][i-1];
    }
    for (auto p:G[x]){
        int v=get<0>(p),a=get<1>(p),b=get<2>(p);
        suma[v]=suma[x]+a;sumb[v]=sumb[x]+b;dfs(v,x);
    }
    return;
}
void solve(){
    int n;cin>>n;G.clear();G.resize(n+10);
    for (int i=2;i<=n;i++){
        int fa,a,b;cin>>fa>>a>>b;
        G[fa].push_back(make_tuple(i,a,b));
    }sumb[1]=suma[1]=0;dfs(1,0);
    for (int i=2;i<=n;i++){
        int x=i,tmp=suma[i];
        for (int j=18;j>=0;j--){
            if (sumb[fat[x][j]]>=tmp) x=fat[x][j];
        }if (sumb[x]>tmp) x=fat[x][0];
        cout<<dep[x]-1<<' ';
    }cout<<endl;return;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);cout.tie(nullptr);
    int t;cin>>t;
    while (t--) solve();
    return 0;
}
```



---

## 作者：__stick (赞：2)

# 题意

给出一个树，边权有两种： $a$ 和 $b$，对于每个节点定义 $A$ 表示 $1$ 到根节点路径上边权值 $a$ 的总和，$B$ 同理。对每个节点，求出第一个 $B$ 小于等于 当前节点 $A$ 的祖先的深度。

# 实现

首先不难发现，每个点的 $B$ 能影响到它的子树中的 $A$，所以我们维护一下每个节点子树中 $A$ 的权值集合就可以了。

其实这题最好写的方法不是单调栈，是 set 启发式合并，我们预处理出来每个节点的 $A$ 和 $B$，将 $A$ 扔到当前节点的 set 里面。对于每个节点，在递归返回时在 set 上二分出大于等于当前节点 $B$ 的位置，将这些点的答案记录为当前这个点的深度并删除这些点。

由于每个点最多删除一次，所以复杂度就是 set 启发式合并的复杂度： $O(n\log^2n)$ 。

# 代码

其实用 map 也是可以的，不过考场上没想到，直接用比较散兵的 set+pair 解决，不过常数不算太大，大概 233 ms 就过去了。

为了避免头文件太长，就只贴个主程序了：

```cpp
struct node
{
	int v,a,b;
};
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while(T--)
	{
		int n;cin>>n;
		int f,a,b;
		vector<vector<node> >e(n+1);
		for(int i=2;i<=n;i++)cin>>f>>a>>b,e[f].push_back({i,a,b});
		vector<set<pair<ll,int> > >s(n+1);
		function<void(int,ll,ll,int)>dfs;
		vi ans(n+1);
		dfs=[&](int u,ll sum,ll sumb,int d)
		{
			s[u].insert({sum,u});
			for(const node& p:e[u])
			{
				int v=p.v;
				dfs(v,sum+p.a,sumb+p.b,d+1);
				if(s[u].size()<s[v].size()) s[u].swap(s[v]);
				for(const auto& x:s[v])
				{
					s[u].insert(x);
				}
			}
			auto ii=s[u].lower_bound({sumb,0}),it=ii;
			while(ii!=s[u].end())ans[ii->Y]=d,ii++;
			s[u].erase(it,s[u].end());
		};
		dfs(1,0,0,0);
		for(int i=2;i<=n;i++)cout<<ans[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```




---

## 作者：迟暮天复明 (赞：0)

[题面](https://codeforces.com/contest/1714/problem/G)

Description:

给一棵树，每条边有两个权值 $vala$ 和 $valb$，对于每个点 $i$，设 $A_i$ 是从 $1$ 号节点走到 $i$ 的 $vala$ 之和，问节点 $j$ 的最大深度，其中 $j$ 在根节点到 $i$ 的简单路径上，且从 $1$ 号节点走到 $j$ 的 $valb$ 之和 $\le A_i$。

$1\le N \le 2\times 10^5$

-----
先计算从 $1$ 号节点到每个点的 $vala$ 和 $valb$ 之和，记为 $suma_i$ 和 $sumb_i$。

则问题转化为对于每一点 $i$，找到最深的节点 $j$，使得 $sumb_j \le suma_i$。

又因为从 $1$ 到 $i$ 路径上的每个点 $j$，$sumb_j$ 递增，而 $suma_i$ 不变，所以这个 $j$ 满足二分性。因为是在树上，所以考虑使用倍增算法。从 $i$ 号节点开始倍增，如果找到的点不满足上述条件，就跳上去。否则不跳。那最终答案就是跳到的那个点的父亲节点。

时间复杂度 $O(n\log n)$。

[代码](https://paste.ubuntu.com/p/y76bwxtgCz/)

---

## 作者：cachejtt (赞：0)

## 题意
给你一个以 $1$ 号节点为根的树，每一条边有两个权值 $a$ 和 $b$。我们定义从根走到一个点的所有边的 $a$ 之和为这个点的 $A$，$b$ 之和为这个点的 $B$。

请你求出，对于每个点 $x$，从根节点走到它的路径上，那些点中，$B_y$ 不超过 $A_x$ 的最大值的那个点的深度是多少。

$2\le n \le 2\times 10^5$

## 思路
由于我们需要找不超过 $a_x$ 的最大值，考虑先预先处理出每个点的深度，$A$ 和 $B$，然后在 dfs 时维护一个栈，存储从根节点到这个点的路径上所有点的 $B$ 值，再在上面二分即可。

注意二分可能会有误差，因此加上两个循环来解决误差。
## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
#define int ll
using namespace std;
int t,n,p,pa,pb;
int ans,sum;
struct edge{
  int v;
  int a,b;
};
vector<edge> e[200005];
int r[200005];
int sa[200005],sb[200005],dep[200005];
int st[200005],head;
void calc(int x){
  if(x==1)return;
  int l=1,rr=head;
  int mid=(l+rr)>>1;
  while(l<rr){
    if(st[mid]>sa[x])rr=mid;
    else l=mid+1;
    mid=(l+rr)>>1;
  }
  while(st[l]<sa[x] && l<head)l++;
  while(st[l]>sa[x])l--;
  r[x]=l;
}
void dfs(int now,int fa,int suma,int sumb,int depb){
  sa[now]=suma;
  sb[now]=sumb;
  dep[now]=depb;
  for(auto q:e[now]){
    if(q.v==fa)continue;
    if(sumb+q.b<suma+q.a)dfs(q.v,now,suma+q.a,sumb+q.b,depb+1);
    else dfs(q.v,now,suma+q.a,sumb+q.b,depb+1);
  }
}
void solve(int now,int fa){
  if(now!=1)st[++head]=sb[now];
  calc(now);
  for(auto q:e[now]){
    if(q.v==fa)continue;
    solve(q.v,now);
  }
  head--;
}
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    head=0;
    cin>>n;
    memset(e,0,sizeof(e));
    rep(i,2,n){
      cin>>p>>pa>>pb;
      e[i].push_back({p,pa,pb});
      e[p].push_back({i,pa,pb});
    }
    dfs(1,0,0,0,0);
    solve(1,0);
    rep(i,2,n)cout<<r[i]<<" ";
    cout<<endl;
  }
  return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1Qg41117Qb)

### 2 思路

设每个点的深度为 $de_u$，特别地，$de_1=1$。

我们可以用深度优先搜索解决这个问题。

我们搜到点 $u$ 的时候，要记录下从 $1$ 点到 $u$ 点的 $a$ 值之和，设为 $sa_{u}$。

然后，我们要完整记录下从 $1$ 到 $u$ 的路径，并完整记录 $1$ 点到路径上各点的 $b$ 值之和，设为 $sb$。

我们可以发现，这条路径上一共有 $de_u$ 个点，点的深度依次递增。

然后，我们可以二分一下，看看最下能够到达哪个深度的点。

最终统计答案即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
#define inf 2000000000000000//2e15
int t;
int n;
struct E{
	int v,nx;
}e[max_n+2];
int fir[max_n+2];
int fa[max_n+2][22];
long long a[max_n+2];
long long b[max_n+2];
int de[max_n+2];
int st[max_n+2];
long long sb[max_n+2];
int ans[max_n+2];
int askans(int l,int r,long long x){
	int mid,res=1;
	while(l<=r){
		mid=(l+r)>>1;
		if(sb[st[mid]]<=x){
			res=st[mid];
			l=mid+1;
		}
		else r=mid-1;
	}
	return res;
}
void dfs(int u,long long sa){
	de[u]=de[fa[u][0]]+1;
	st[de[u]]=u;
	sb[u]=sb[fa[u][0]]+b[u];
	for(int i=fir[u];i;i=e[i].nx)dfs(e[i].v,sa+a[e[i].v]);
	int res=askans(1,de[u],sa);
	ans[u]=de[res]-1;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1714G_1.in","r",stdin);
	freopen("CF1714G_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)fir[i]=0;
		fa[1][0]=0;
		b[1]=0;
		de[0]=0;
		for(int i=2;i<=n;++i){
			scanf("%d%lld%lld",fa[i],a+i,b+i);
			e[i]=(E){i,fir[fa[i][0]]}; fir[fa[i][0]]=i;
		}
		dfs(1,0);
		for(int i=2;i<=n;++i)printf("%d ",ans[i]);
		printf("\n");
	}
}
```

[记录传送门](https://www.luogu.com.cn/record/82204095)

By **dengziyue**

---

## 作者：sixrc (赞：0)

这真的是 G 吗？

正解就两句话：dfs 对树上每一个结点做 $a,b$ 从根节点开始的前缀和，定义 $a_i,b_i$ 为从根节点到某个点经过 $i$ 条边的前缀和。然后对于结点 $p$，记从根节点到 $p$ 经过的边为 $x$，在 $b$ 中二分查找第一个 $\le a_x$ 的数，下标即为所求。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, p, x, y, z, w, h[200010], a[200010], b[200010], ans[200010];
struct node{
	int x, y, z, w, next;
}d[400010];
void add(int x, int y, int z, int w){
	d[++p].y = y, d[p].z = z, d[p].w = w, d[p].next = h[x], h[x] = p;
}
void dfs(int x, int fa, int dep){
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		b[dep] = b[dep-1] + d[i].w;
		a[dep] = a[dep-1] + d[i].z;
		//printf ("%d : %d %d\n", d[i].y, a[dep], b[dep]);
		ans[d[i].y] = upper_bound(b+1, b+dep+1, a[dep]) - b - 1;
		dfs(y, x, dep+1);
	}
}
signed main(){
	scanf ("%lld", &t);
	while (t --){
		scanf ("%lld", &n);
		for (int i=1; i<=p; i++){
			d[i].x = d[i].y = d[i].z = d[i].w = d[i].next = 0;
			h[i] = 0;
			a[i] = 0;
			b[i] = 0;
			ans[i] = 0;
		}
		p = 0;
		for (int i=2; i<=n; i++){
			scanf ("%lld%lld%lld", &x, &z, &w);
			add(i, x, z, w); add(x, i, z, w);
		}
		dfs(1, 0, 1);
		for (int i=2; i<=n; i++){
			printf ("%lld ", ans[i]);
		}
		puts ("");
	}
	return 0;
}
```

---

## 作者：Burnling (赞：0)

### 题意简述

给出一棵有 $n$ 个节点的有根树，顶点编号为从 $1$ 到 $n$。根节点编号为 $1$。

每一条边上有两个正整数，分别为 $a_j$ 和 $b_j$。

对于每一条从节点 $1$ 到节点 $i$ 的路径，令 $A_i$ 表示这条路径上所有 $a_j$ 的和。

$r_i$ 的值为这条路径的最大前缀长度，并满足该前缀路径的 $b_j$ 和不超过 $A_i$。

最终输出 $r_2,r_3,\dots,r_n$。

### 题目分析

显然这是一道图论题。

通过一遍 DFS ，我们可以获取到所有 $A_i$ 的值，然后就可以考虑如何获取 $r_i$ 的值。

根据 $r_i$ 的定义，我们可以通过一个数组 $B$ 来维护到达该点的的 $b_j$ 的前缀和。

经过某条边后，将该边的 $b_j$ 添加到 $B$ 中；从某条边返回时，将 $b_j$ 从数组中删除。

以题里的这颗有根树为例，到达节点 $3$ 时，$B$ 中有三个元素：$6,16,17$。

由于 $1\leq a_j,b_j \leq 10^9$， $b_j$ 为正整数，那么 $B$ 中的值一定是单调递增的。

下一步就是在数组中找到最大的不超过 $A_i$ 的  $B_j$，则 $r_i$ 的值就为 $j$。

由于 $B$ 中所有元素单调递增，可以用二分查找来寻找最后一个不大于 $A_i$ 的 $B_j$。

而查找答案也可以在计算 $A_i$ 的同时计算，因为到达点 $i$ 时一定已经经过了其所有的祖先节点，$B$ 数组一定有到达该点所有的前缀 $b_j$ 值。

有两点需要注意：

1. 存图用 `vector` 而不是链前（我反正链前被卡了，可能是因为每组测试用例前归零耗时太大了罢。
2. 需要 `long long` ，因为 $1\leq a_j,b_j \leq 10^9$ 且 $2\leq n\leq 2\cdot10^5$ ，前缀和很有可能爆 int。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5 + 10;
typedef long long ll;

vector<int> TO[maxN];
vector<int> A[maxN];
vector<int> B[maxN];

inline void add_edge(int u, int v, int a, int b) {
    TO[u].push_back(v);
    A[u].push_back(a);
    B[u].push_back(b);
}

int N;
int cnt;
ll pre[maxN];
int ans[maxN];

inline void read(int &x) {
    x=0;int f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    x*=f;
}

//prefixS 表示到达该点经过所有a的和
//prefixSb 表示到达该点经过所有b的和
void dfs(int k, int fa, ll prefixS, ll prefixSb) {
    
    pre[++cnt] = prefixSb;

    //使用 upper_bound 来找到第一个大于等于Ai的值的下标
    //由于pre数组的数据下标从1开始，所以实际的前缀长度需要 -1
    int p = upper_bound(pre + 1, pre + 1 + cnt, prefixS) - pre - 1;
    //由于需要的是第一个不大于Ai的值，找到的是第一个大于Ai的值，所以需要再多减 1
    ans[k] = p - 1;

    for (int i = 0; i < TO[k].size(); i++) {
        int v = TO[k][i];
        if (v == fa) continue;
        dfs(v, k, prefixS + A[k][i], prefixSb + B[k][i]);
    }
    //从前缀数组中将该边的影响移除
    cnt--;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        /*
        初始化，这里的N为上一个测试用例中N的值
        因为一共N个节点，所以上一次始点的最大值为N
        这里的始点表示 edge[u][v] 中的 u
        */
        for (int i = 0; i <= N; i++) {
            A[i].clear();
            B[i].clear();
            TO[i].clear();
        }
        read(N);
        cnt = 0;

        for (int i = 2; i <= N; i++) {
            int p, a, b;
            read(p);read(a);read(b);
            add_edge(i, p, a, b);
            add_edge(p, i, a, b);
        }

        dfs(1, -1, 0, 0);

        for (int i = 2; i <= N; i++) {
            printf("%d ", ans[i]);
        }
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：zhicheng (赞：0)

### 题目简述

给定一个有 $n$ 个点的树，以点 $1$ 为根，边有**两种**边权（$a$ 边权和 $b$ 边权）。

设点 $1$ 到点 $i$ 的距离（路径上的 $a$ 边权之和）为 $A_i$。

对于 $i \in [2,n]$，求出点 $1$ 到点 $i$ 路径上的最长前缀，使得这个前缀上的 $b$ 边权之和不超过 $A_i$。输出这个前缀所包含的边数。

### 思路

很明显，求 $A_i$ 只需要一个 DFS 即可。那我们看怎样同时得出答案。考虑记录从 $1$ 到 $i$ 的路径上所有的 $b_i$。需要求前缀的边权和，那么我们就做一个前缀和。然后就很明显了：直接在这个前缀和数组里二分查找，找到小于等于 $A_i$ 的数中最大的那个。具体实现可以用 upper_bound 找到第一个大于 $A_i$ 的，然后减去 $1$ 即可。（见代码）

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,ans[200010],tot,first[200010],nnext[400010],to[400010];
long long r[200010],w1[400010],w2[400010];  //记得开 long long！
void add(int a,int b,int c,int d){  //邻接表建边
	nnext[++tot]=first[a];
	first[a]=tot;
	to[tot]=b;
	w1[tot]=c;
	w2[tot]=d;
}
void dfs(int u,int fa,long long q){
	if(u!=1){  //记录答案，方法见上
		ans[u]=upper_bound(r+1,r+cnt+1,q)-r-1;
	}
	for(int e=first[u];e;e=nnext[e]){
		if(to[e]!=fa){
			q+=w1[e];  //算出 A[i]
			cnt++;
			r[cnt]=w2[e]+r[cnt-1];  //记录 b[i]，前缀和
			dfs(to[e],u,q);
			q-=w1[e];  //回溯
			r[cnt--]=0;
		}
	}
}
int main(){
	int n,a,b,c,x;
	scanf("%d",&n);
	while(n--){
		cnt=tot=0;
		memset(first,0,sizeof(first));  //多测清空
		scanf("%d",&a);
		for(int i=2;i<=a;i++){
			scanf("%d%d%d",&x,&b,&c);  //输入需要稍加注意
			add(i,x,b,c);
			add(x,i,b,c);
		}
		dfs(1,0,0);
		for(int i=2;i<=a;i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
}
```

~~这个 Div.3 G 真的太简单了，虽然这个蒟蒻最后 5 min 才发现这一点，然后没打完寄了~~

---

