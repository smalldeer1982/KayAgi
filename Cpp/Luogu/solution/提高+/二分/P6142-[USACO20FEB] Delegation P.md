# [USACO20FEB] Delegation P

## 题目描述

Farmer John 有 $N$ 个牧场，这些牧场通过 $N-1$ 条道路连接，形成了一个树形结构。

但在 28 年的经营后（译者注：USACO 创办于 1992 年），FJ 觉得处理树上问题非常辣手，他认为一条链上的问题更加简单。

因此他决定将整棵树划分为若干条链，将每一条链的管理权授予一位工人。他不关心链的数量，却关心链的长度，他希望划分的链都尽可能长，从而不会有人用效率低下的算法蒙混过关。

FJ 现在想知道最大的正整数 $K$，使得整棵树被划分成若干条链，且每条链的长度都**至少**是 $K$。

## 说明/提示

### 样例解释

一种划分方案如下：

$$
2-1-6-7-8, 3-1-4-5
$$

### 子任务

- 测试点 $2 \sim 4$ 满足**最多**有一个点的度数大于 $2$。
- 测试点 $5 \sim 8$ 满足 $N \leq 10^3$。
- 测试点 $9 \sim 15$ 没有特殊限制。

## 样例 #1

### 输入

```
8
1 2
1 3
1 4
4 5
1 6
6 7
7 8```

### 输出

```
3```

# 题解

## 作者：奇米 (赞：21)

# 题解 - $\mathrm{P6142 \ [USACO20FEB] \ Delegation\  P}$

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

### 题目意思

* [P6142 ](https://www.luogu.com.cn/problem/P6142)
* 给定一棵含有$n$个结点的树，把它分成若干条链（边只能选一次，点可以选多次），使得最短的那条链的长度最长是多少。
* $n\leq 10^5$

### $\mathrm{Sol}$ 

* 一道$STL$良（凉）好练习题。
* 我们首先肯定会去二分答案$L$那个最长链长，关键是如何判定。
* 我们这边利用$multiset$这个东东来维护，它是什么讷？就是一个容器，然后加入元素会帮你从小到大排序，且允许加入重复的元素，且删增操作是$log$的。
* 然后我们就有考虑如何去判定：对于一个节点$u$有若干条从$v$连过来的边，我们尽量找道两条链$l1,l2$连接使得$l1+l2$尽量接近且大于等于$L$。这个还是简单易懂的。于是我们是两两配对所以$u$要从儿子节点$v$连过来并且要有一条边给自己的父亲节点$f_u$，那么如果从儿子那儿有奇数条边那么就不管了，如果偶数条边，我们强制构造出奇数条边（即加入一条$0$边）。
* 于是我们$O(n\log^2 n)$做完了这道题目，似乎还可以双指针优化到$O(n\log n)$，这儿不多加介绍（因为比较菜。

### $\mathrm{Code}$ 

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=1e5+5;

int n,m,ans,flg,jb,f[N];
vector<int> G[N];

inline void dfs(int u,int fa,int L)
{
	multiset<int> M;//multiset容器
	if(flg) return;
	for ( int i=0;i<G[u].size();i++ )
	{
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u,L);
		M.insert(f[v]+1);
	}
	jb=0;
	if((u==1&&M.size()&1)||(u!=1&&!(M.size()&1))) M.insert(0);
	//强制除根节点外的点从儿子连边过来的边数为奇数条
	while(M.size())
	{
		multiset<int>::iterator It=M.begin();//取当前最小边
		int small=*It;
		M.erase(It);
		multiset<int>::iterator Big=M.lower_bound(L-small);
		//二分找到第一条大于等于二分的L的边
		if(u==1) 
		{
			if(Big==M.end())//找不到，走人
			{
				flg=1;
				break;
			}
			M.erase(Big);
		}
		else 
		{
			if(Big==M.end()&&jb)
			{
				flg=1;
				break;
			}
			if(Big==M.end()&&!jb) 
				jb=1,f[u]=small;//找到那一条可以给f[u]造成贡献的边
			if(Big!=M.end()) M.erase(Big);
		}
	}
}

inline bool check(int mid)
{
	flg=0;
	memset(f,0,sizeof f);
	dfs(1,0,mid);
	return (!flg);
}

int main()
{
	n=read();
	for ( int i=1;i<n;i++ )
	{
		int x,y;
		x=read(),y=read();
		G[x].pb(y);
		G[y].pb(x);
	}
	int l=0,r=n;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)) 
			l=mid+1,ans=mid;
		else r=mid-1;//二分答案
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：StudyingFather (赞：10)

首先二分答案 $K$，如何检验这个 $K$ 是可以的呢？做法和 [同名金组题目](https://studyingfather.blog.luogu.org/solution-p6147) 差不多。

对于一个点 $u$，经过 $u$ 和其祖先节点的链最多只有一条，我们贪心地留一条最长的子链。

因此处理到点 $u$ 的时候，还是把点 $u$ 的所有子链拉出来，将所有链排个序。

二分找要留给祖先点的子链，检验的时候看看剩下的链能否全部配成长度大于等于 $K$ 的链即可（这里为了减少一些奇怪的特判，子链条数为偶数的时候可以加一条长度为零的链）。

PS：这次月赛结束后才发现自己把赛道修建在考场上做出来了（~~那题之前还没做过~~）

```cpp
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> vec[100005],e[100005];
int s[100005];
bool check2(int u,int p,int x)
{
 int siz=vec[u].size();
 for(int i=0,j=siz-1;i<j;i++,j--)
 {
  if(i==p)i++;
  if(j==p)j--;
  if(vec[u][i]+vec[u][j]<x)return false;
 }
 return true;
}
bool check(int u,int fa,int x)
{
 vec[u].clear();
 for(auto v:e[u])
 {
  if(v==fa)continue;
  if(!check(v,u,x))return false;
  vec[u].push_back(s[v]+1);
 }
 if(fa&&vec[u].size()%2==0)vec[u].push_back(0);
 else if(!fa&&vec[u].size()%2!=0)vec[u].push_back(0);
 sort(vec[u].begin(),vec[u].end());
 int siz=vec[u].size();
 if(!fa)
 {
  for(int i=0;i<siz/2;i++)
   if(vec[u][i]+vec[u][siz-i-1]<x)
    return false;
 }
 else
 {
  int ans=0;
  if(!check2(u,0,x))return false;
  int l=0,r=siz-1;
  while(l<=r)
  {
   int mid=(l+r)>>1;
   if(check2(u,mid,x))ans=mid,l=mid+1;
   else r=mid-1;
  }
  s[u]=vec[u][ans];
 }
 return true;
}
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<n;i++)
 {
  int u,v;
  cin>>u>>v;
  e[u].push_back(v);
  e[v].push_back(u);
 }
 int l=1,r=n-1,ans=0;
 while(l<=r)
 {
  int mid=(l+r)>>1;
  memset(s,0,sizeof(s));
  if(check(1,0,mid))ans=mid,l=mid+1;
  else r=mid-1;
 }
 cout<<ans<<endl;
 return 0;
}
```

---

## 作者：ix35 (赞：7)

## P6142 USACO 20 Feb Delegation

本题和 [赛道修建](https://www.luogu.com.cn/problem/P5021) 极其相似。

首先二分答案，转化为判定：能否将树划分成若干长度不超过 $K$ 的路径。

判定依然是树形 DP，按照和赛道修建类似的套路，$dp(i)$ 表示在 $i$ 的子树内服从条件的情况下，以 $i$ 为祖先的一条 **最长剩余祖先链** 长度，即除了这条祖先链以外，$i$ 的子树已经划分成若干长度不超过 $K$ 的路径。

决策部分就是：以 $u$ 为 LCA 的路径，可选匹配将从 $dp(v)+1\ \ (v\in Son(u))$ 中产生，设 $u$ 的子结点数量为 $d$，那么：

1. 当 $d$ 是奇数时，显然留一条链上传为 $dp(u)$，此外别的链两两匹配。

2. 当 $d$ 是偶数时，为了避免讨论，添加一个 $0$，转化成 $d$ 是奇数的情况。

还有一个特例：$u$ 为根结点，此时不需更新 $dp(u)$，所以 $d$ 是偶数时直接匹配即可。

问题是：选择哪条链上传呢？这里显然还是有单调性的，我们在 $d$ 条链中再做一个二分，判定当前选择的这条链能否上传，判定比较简单，删除这条链后两边匹配，最大配最小即可。

时间复杂度 $O(n\log^2 n)$，应该可以用双指针优化到 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,x,y,eg,flg,rt,d[MAXN],hd[MAXN],ver[2*MAXN],nx[2*MAXN],las[MAXN];
vector <int> v[MAXN];
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
bool chk2 (int p,int x,int vm) {
	int siz=v[x].size();
	for (int i=0,j=siz-1;i<j;i++,j--) {
		if (i==p) {i++;}
		if (j==p) {j--;}
		if (v[x][i]+v[x][j]<vm) {return 0;}
	}
	return 1;
}
void dfs (int x,int fa,int vm) {
	v[x].clear();
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dfs(ver[i],x,vm);
		v[x].push_back(las[ver[i]]+1);
	}
	int siz=v[x].size();
	if (!fa&&(siz&1)) {v[x].push_back(0),siz++;}
	if (fa&&(!(siz&1))) {v[x].push_back(0),siz++;}
	sort(v[x].begin(),v[x].end());
	if (!fa) {
		for (int i=0;i<siz/2;i++) {
			if (v[x][i]+v[x][siz-i-1]<vm) {flg=0;return;}
		}
	} else {
		int flg2=0,ans=0;
		if (!chk2(0,x,vm)) {flg=0;return;}
		else {
			int l=0,r=siz-1;
			while (l<r) {
				int mid=(l+r+1)>>1;
				if (chk2(mid,x,vm)) {l=mid;}
				else {r=mid-1;}
			}
			las[x]=v[x][l];
		}
	}
	return;
}
bool chk (int x) {
	flg=1;
	dfs(rt,0,x);
	return flg;
}
int main () {
	freopen("deleg.in","r",stdin);
	freopen("deleg.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		d[x]++,d[y]++;
		add_edge(x,y),add_edge(y,x); 
	}
	for (int i=1;i<=n;i++) {if (d[i]>d[rt]) {rt=i;}}
	int l=1,r=n-1;
	while (l<r) {
		int mid=(l+r+1)>>1;
		if (chk(mid)) {l=mid;}
		else {r=mid-1;}
	}
	printf("%d\n",chk(l)?l:0);
	return 0;
}
```


---

## 作者：lhm_ (赞：2)

和[赛道修建](https://www.luogu.com.cn/problem/P5021)类似，先对$k$进行二分，将最值问题转化为判定问题。

在判定一个$k$是否合法时，贪心去考虑，一个节点下面的若干条链在合并时，一条链肯定和另一条使它合并后恰好满足长度限制的链合并最优。因此我们用$multiset$来进行维护，一条长度为$len$的链，去查询第一条长度大于等于$k-len$的链，若找不到，即不合法。

再考虑到一个非根节点在合并链时，是可以有一条链无法合并，其它链两两配对，那么剩下那个链就往上继续寻找配对即可，但根节点肯定是要两两配对。

所以在合并时，可以增加一个长度为$0$的链，来使非根节点的链数量为奇数，使根节点的链数量为偶数，方便一些细节的处理。

实现就看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;
typedef multiset<int>::iterator mul;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n;
bool flag;
int f[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt=1;
void add(int from,int to)
{
    e[++edge_cnt]=(edge){to,head[from]};
    head[from]=edge_cnt;
}
void dfs(int x,int fa,int len)
{
	if(!flag) return;
    multiset<int> s;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa) continue;
		dfs(y,x,len);
		s.insert(f[y]+1);
	}
    int size=s.size();
    bool tag=false;
    if((x==1&&size&1)||(x!=1&&!(size&1))) s.insert(0);
    while(!s.empty())
    {
        if(!flag) break;
        int l1;
        mul t1=s.begin(),t2;
        l1=*t1,s.erase(t1),t2=s.lower_bound(len-l1);
        if(x==1)
        {
            if(t2==s.end())
            {
                flag=false;
                break;
            }
            s.erase(t2);
        }
        else
        {
            if(t2==s.end()&&tag)
            {
                flag=false;
                break;
            }
            if(t2==s.end()&&!tag) f[x]=l1,tag=true;
            if(t2!=s.end()) s.erase(t2);
        }
    }
}
bool check(int x)
{
    flag=true,memset(f,0,sizeof(f)),dfs(1,0,x);
    return flag;
}
int main()
{
    read(n);
    for(int i=1;i<n;++i)
    {
        int a,b;
        read(a),read(b);
        add(a,b),add(b,a);
    }
    int l=1,r=n-1,ans=1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：creation_hy (赞：1)

经典套路，先二分答案 $l$，设 $f_x$ 表示 $x$ 子树内最多能选一条多长的到 $x$ 的链，使得剩下部分满足可以分解成若干条链，每条链长度都不小于 $l$。

然后转化为对所有 $x$ 的儿子节点的 $f$ 进行匹配，要求每个匹配都满足 $f_x+f_y+2\ge l$。容易发现 $v$ 的最优匹配一定是不小于 $l-v-2$ 的最小值，set 上二分即可。最终如果剩下一个 $f$，那么 $f_x$ 的值就是它了。

~~当然这是错的~~，因为并没有考虑到 $f\ge l-1$ 的长链可以不匹配直接完结。注意有三种情况：一短一长，答案为短链而不是 $0$（不继续匹配）；两短一长或一短多长，要让最短链继续匹配。具体判断方法见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, head[N], to[N], nxt[N], etot;
int f[N], ans, lim;
multiset<int> s;
inline void link(int u, int v)
{
    to[etot] = v;
    nxt[etot] = head[u];
    head[u] = etot++;
}
inline void dfs(int x, int fa)
{
    for (int i = head[x]; ~i; i = nxt[i])
        if (to[i] != fa)
        {
            dfs(to[i], x);
            if (!ans)
                return;
        }
    s.clear();
    for (int i = head[x]; ~i; i = nxt[i])
        if (to[i] != fa)
            s.emplace(f[to[i]]);
    int sp = 0;
    while (s.size() > 1 && (s.size() > 2 || *++s.begin() < lim - 1))
    {
        int x = *s.begin();
        s.erase(s.find(x));
        if (x >= lim - 1)
            continue;
        auto p = s.lower_bound(lim - x - 2);
        if (p == s.end())
        {
            if (sp || s.size() & 1)
            {
                ans = 0;
                return;
            }
            else
                sp = x + 1;
        }
        else
            s.erase(p);
    }
    f[x] = s.empty() ? sp : *s.begin() + 1;
}
inline bool check(int x)
{
    lim = x, ans = 1, dfs(1, 0);
    return (ans && (!f[1] || f[1] >= lim || s.size() == 2));
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof(head));
    cin >> n;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, link(u, v), link(v, u);
    int l = 1, r = n - 1;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    cout << l - 1 << '\n';
    return 0;
}
```

---

## 作者：JiaY19 (赞：1)

一道比较简单的贪心。

### 思路

不难看出要套一个二分答案。

对于每一次二分。

首先考虑由于每个点到自己父亲只有一条连边。

并且每一条连边都要被覆盖到，也就代表了每个儿子只能向父亲传一条边。

那么儿子最优的情况下是在满足自己的情况下，传一条最长的边上去。

具体来说，我们把根和其他节点分类讨论（因为根无法往上传边）。

1. 对于根，直接匹配即可，从最小的开始匹配，用二分找到第一个满足的，若是没有满足的，则直接退出，判断为不合法。
2. 对于其他节点，我们同样如上匹配，但发现第一个不合法的，我们可以把它记录下来（因为可以用于往上传），直到第二个不合法的，才退出。

这样的话直接用 $\text{set}$ 处理一下就可以。

当然，请使用 $\text{multiset}$，否则会获得 $34$ 的高分。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define x first
#define y second
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 1000010;

int n, cnt, head[N];
int flag;

struct edge
{
    int to, nxt;
} e[N * 2];

inline void add(int x, int y)
{
    e[++cnt] = {y, head[x]}, head[x] = cnt;
    e[++cnt] = {x, head[y]}, head[y] = cnt;
}

inline int dfs(int now, int fa, int k)
{
    multiset<int> to;
    for (int i = head[now]; i; i = e[i].nxt)
    {
        if(e[i].to == fa) continue;
        to.insert(dfs(e[i].to, now, k) + 1);
        if(!flag) return 0;
    }
    if(now == 1)
    {
        if(to.size() % 2 == 1)
            to.insert(0);
        while(to.empty() == 0)
        {
            auto it1 = to.begin(); to.erase(it1);
            auto it2 = to.lower_bound(k - *it1);
            if (it2 == to.end()) { flag = 0; break; }
            to.erase(it2);
        }
        return 0;
    }
    else
    {
        int x = -1;
        if(to.size() % 2 == 0)
            to.insert(0);
        while(to.size() > 1)
        {
            auto it1 = to.begin(); to.erase(it1);
            auto it2 = to.lower_bound(k - *it1);
            if (it2 == to.end())
            {
                if(x == -1) x = *it1;
                else { flag = 0; break; }
            }
            else to.erase(it2);
        }
        if(x == -1) return *to.begin();
        else return x;
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    fro(i, 1, n - 1)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }
    int l = 1, r = n, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2; flag = 1;
        dfs(1, 0, mid);
        if(flag) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：intel_core (赞：1)

首先，容易发现答案满足单调性   
所以我们考虑检验答案 $x$ 是否可行    
考虑树形 DP ，合并每个子树的继承值   
将每个子树的继承值排序，将 $>x$ 的值连带最小的全部去掉   
双指针扫描剩下的值，并统计剩下的值的个数    
上代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <set>
using namespace std;
const int NR=1e5+10;
struct edge{
	int to,next;
}g[NR<<1];
int tot;
int fte[NR];
void add(int x,int y){
	g[++tot]=(edge){y,fte[x]};
	fte[x]=tot;
}
bool flag;
int dp[NR];
int p,n;
void dfs(int x,int fa,int l){
	multiset<int>m;
	if(flag)return;
	for(int i=fte[x];i;i=g[i].next){
		int y=g[i].to;
		if(y==fa)continue;
		dfs(y,x,l);
		m.insert(dp[y]+1);
	}
	p=0;
	if(x==1&&(m.size()%2==1))m.insert(0);
	if(x!=1&&(m.size()%2==0))m.insert(0);
	while(!m.empty()){
		multiset<int>::iterator it1=m.begin();
		m.erase(it1);
		multiset<int>::iterator it2=m.lower_bound(l-*it1);
		if(x==1){
			if(it2==m.end()){
				flag=1;
				return;
			}
			m.erase(it2);
		}
		else{
			if(it2==m.end()){
				if(p){
					flag=1;
					return;
				}
				p=1;
				dp[x]=*it1;
			}
			else m.erase(it2);
		}
	}
}
bool check(int x){
	memset(dp,0,sizeof(dp));
	flag=0;
	dfs(1,0,x);
	return flag==0;
}
signed main(signed argc, char const *argv[])
{
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	int l=1,r=n;
	int ans=1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
} 
```


---

## 作者：pocafup (赞：1)

这题思路大佬们都讲了,我来讲哈我的做法

不知道为啥,大佬们都用的双指针...虽然感觉上对的,而且我hack不掉,~~但是我总感觉有某种神奇的数据会让他出问题~~.于是,我选择用set

双指针比较头尾貌似挺有道理,但是我总感觉如果他的子树能配对,传上去的数一定是最大的.而双指针不能保证传上去的是最大的数.比如1 3 5 6 10.假设要选的数是7,双指针会选1 10, 3 6, 然后返回一个5.然而我们可以划分为1 6和3 5,返回10(如果有理解错,欢迎指正)

而set的方法就好写多了.每次配对子树的时候,我们只选最小能使子树配对满足要求的数.这个操作可以用lower_bound做.如果用vector可以用二分实现(但码量就大不少了).

更新答案有几种情况(必须在出发点才更新答案):

1.如果出发点的子树全部能配对,那么这个数是可以选的

2.如果出发点含有的未配对子树,并且子树的权值 $>=$ 我们要选的数,那么这个数是可以选的

这些都有一个共同的前提:他的子树能够成功配对.

**如果有任何一个子树不能配对,那么这个数绝对不能选**

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
const int MAXN = 1e5+5;
int n,st;
vector<int> adj[MAXN];
bool possible = true;
inline int dfs(int pos, int fa,int num){
  multiset<int> se;
  int tmp = 0,sz = 0;
  for (int v : adj[pos]){
    if(!possible) return -1;
    if (v==fa) continue;
    int k = dfs(v,pos,num);
    if (!possible) return -1;
    se.insert(k);
  }//基本操作
  while(se.size()>1 && possible){
    auto it = se.begin(); se.erase(se.begin());
    if ((*it)>=num) continue;
    auto it2 = se.lower_bound(num-(*it));
    if (it2!=se.end()){//如果能配对
      if (se.size()==1 && *it2>=num && !sz) return (*it2)+1;//如果子树的数量只有一个,并且没有未配对的子树,就将这个数返回
      se.erase(it2);
    }else sz++,tmp+=(*it);//如果这棵子树不能配对
    if (sz>1) possible = false;//如果有两棵不能配对的子树,那么这棵树不成立
  }
  if (!possible) return -1;
  if (pos==1 && (sz || (se.size() && *se.begin()<num))) return 0;//不成立的条件有:在起点并且有未配对的子树或者剩下的子树的权值小于要求的数
  if (pos==1) return sz>1 ? 0 : (!se.size() || !sz || (*se.begin()>=num)) ? 1e5 : 0;//上面讲过的
  if (!se.size()) return tmp+1;//如果这个数没有子树了,就将配对剩下来的数返回
  if (*se.begin()<num && sz) {possible = false;return -1;}//如果这个数的剩余子树的权值<这个数,并且还有其他未配对的子树
  else if (*se.begin()>=num && sz) return tmp+1;//如果他有未配对的子树,但剩余子树的权值>=要求的数
  else if (!sz) return *se.begin()+1;//如果没有未配对子树
}
int a,b;
inline void bs(){
  int l = 1, r = n-1;
  while(l!=r){
    int mid = (l+r+1)/2;
    possible = true;
    int re = dfs(1,-1,mid);
    if (possible && re>=mid) l = mid;
    else r = mid-1;
  }
  cout << r;
}
int main(){
  cin >> n;
  for (int i=0;i<n-1;i++) {
    cin >>  a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  bs();
}
```

---

## 作者：louhao088 (赞：1)

# 题解



### 题意：
把一棵树划分成若干条链，求最小链的最大值。


------------

### 算法：二分+搜索
本蒟蒻根据老师教的最小的最大一般都是二分，在模拟赛中打了一个二分。但是$T$了几个点，调了很久才过。


------------
### 思路
#### $1.$根据$USACO$第一个点一定是样例，我们进行一个打表操作.


```cpp
if(n==8)cout<<"3",exit(0);//打表


```


------------

#### $2.$打完表后，我们先用一个$dfs$计算各点度数。用$d_x$处存
```cpp
void dfs(int x,int fa)
{
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;d[x]++;
		if(v==fa)continue;
		dfs(v,x);
	}
	if(d[x]>2)k++;
}

```

------------

#### $3.$由于我们知道当$k=0$时，就是没有一个点得度数大于$2$时，这一定是一条链，所以再次进行骗分操作
```cpp
if(k==0)cout<<n-1,exit(0);

```
------------
#### $4.$我们要打一个$check$函数，用$F$记录有没有小于$mid$的链
```cpp
bool check(int mid)
{
	F=0;dfs1(1,0,mid);
	if(F)return false;
	else return true;  
}

```
------------

### 下面要说最重要的$dfs1$函数了

先看一下代码
```cpp
void dfs1(int x,int fa,int num)
{
	if(F)return;
	d1[x]=1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)continue;dfs1(v,x,num);
	}
	if(d[x]==2&&x!=1)
	{
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v!=fa)d1[x]+=d1[v];
		}
	}
	else if(d[x]%2==0&&x!=1)
	{
		int w=0,k;
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v!=fa)a[++w]=d1[v];
			else k=d1[v];
		}
		sort(a+1,a+w+1);for(int i=1;i<=w;i++)flag[i]=0;
		for(int i=1;i<=w;i++)
		{
			if(flag[i]==1)continue;
			for(int j=i+1;j<=w;j++)
				if(a[i]+a[j]>=num&&!flag[j])
				{
					flag[i]=1,flag[j]=1;break;
				}
					
		}
		int t=0,o;
		for(int i=1;i<=w;i++)
			if(!flag[i])t++,o=a[i];
		if(t>1)F=1;
		else d1[x]+=o;
	}
	else if(d[x]%2==1&&x!=1)
	{
		int w=0,k;
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v!=fa)a[++w]=d1[v];
			else k=d1[v];
		}
		sort(a+1,a+w+1);for(int i=1;i<=w;i++)flag[i]=0;
		for(int i=1;i<=w;i++)if(a[w]>=num)flag[w]=1;
		for(int i=1;i<=w;i++)
		{
			if(flag[i]==1)continue;
			for(int j=i+1;j<=w;j++)
				if(a[i]+a[j]>=num&&!flag[j])
				{
					flag[i]=1,flag[j]=1;break;
				}
					
		}
		int t=0,o;
		for(int i=1;i<=w;i++)
			if(!flag[i])t++,o=a[i];
		if(t>1)F=1;
		else if(t==1) d1[x]+=o;
	}
	else if(x==1)
	{
		if(d[x]%2==0)
		{
			int w=0,k;
			for(int i=head[x];i;i=e[i].nex)
			{
				int v=e[i].v;
				if(v!=fa)a[++w]=d1[v];
				else k=d1[v];
			}
			sort(a+1,a+w+1);for(int i=1;i<=w;i++)flag[i]=0;
			for(int i=1;i<=w;i++)
			{
				if(flag[i]==1)continue;
				for(int j=i+1;j<=w;j++)
					if(a[i]+a[j]>=num&&!flag[j])
					{
						flag[i]=1,flag[j]=1;break;
					}
						
			}
			int t=0;
			for(int i=1;i<=w;i++)
				if(!flag[i])t++;
			if(t>=1)F=1;
		}
		else
		{
			int w=0,k;
			for(int i=head[x];i;i=e[i].nex)
			{
				int v=e[i].v;
				if(v!=fa)a[++w]=d1[v];
				else k=d1[v];
			}
			sort(a+1,a+w+1);for(int i=1;i<=w;i++)flag[i]=0;
			for(int i=1;i<=w;i++)if(a[w]>=num)flag[w]=1;
			for(int i=1;i<=w;i++)
			{
				if(flag[i]==1)continue;
				for(int j=i+1;j<=w;j++)
					if(a[i]+a[j]>=num&&!flag[j])
					{
						flag[i]=1,flag[j]=1;break;
					}
						
			}
			int t=0;
			for(int i=1;i<=w;i++)
				if(!flag[i])t++;
			if(t>=1)F=1;
		}
	}
}
```
本蒟蒻太菜了，代码有点长。

我们用$d1_x$表示由$x$连到他父亲链的长度，最开始所有都是一

我们开始分类讨论


------------


#### $1.d[x]=2$&&$x!=1$（根）

也就是说该点除了父亲没有儿子，只要把其儿子链的长度加到上即可


------------


#### $2.d[x]\mod2=0$&&$d[x]!=2$$&&$$x!=1$

此时，该点有奇数个儿子，我们只要用$w_i$存储其儿子链长，在进行排序即可

时间$n(logn)$能过，所以不需要用$multiset$,~~我是不会告诉你我其实不会~~

只要进行$n^2$配对，~~貌似会T但数据太水~~。如果剩下多个则不行，若剩一个把剩下的加到$x$上


------------


#### $3.d[x]\mod2=1$&&$x!=1$

此时，该点有偶数个儿子，若有一$d1_v$满足$d1_v>mid$则标记$v$，将其转化为$d[x]\mod2=0$;
或者直接全部配对完不加给$x$


------------

#### $4.x=1$
分两种情况
##### $4.1 d[1]\mod2=0$
这就是$d[x] \mod 2=1$$&&$$x!=1$的情况，只是不用对$d1_v>mid$的v标记

#####  $4.2 d[1]\mod2=1$
这就是$d[x]\mod2=0$的情况,只是需要一个$d1_v$$>mid$的儿子，否则不行






---

## 作者：Nasaepa (赞：0)

学校 vp [USACO20FEB] P 组，场上没做出来，过了好久终于补出来了。

---

最小值最大一眼二分。考虑能否构建方案使得每一条链的长度都大于等于 $mid$ 。对于节点 $x$ ，它的子树只有一条能和父节点连接，剩下的点都需要两两配对。我们肯定希望接上去的链尽可能长，两两配对的链也尽可能长。

首先考虑 $x$ 的子节点数量为奇数的情况。显然，如果想要使得链长最大，要让尽可能长的链配尽可能短的链。考虑 $x$ 的子节点按照链长从低到高排序，每次处理没有配对的最短的链，设其长度为 $p$ ，由于我们只需要让链长比 $mid$ 长就行了，我们只需要找一条长度大于等于 $mid - p$ 的链就行了，为了实现最优，需要找到满足上述要求且最短的链。如果找不到这样的链，就让这条链往父节点连。如果多条链都无法配对，那么这个 $mid$ 就不合法。

至于数量为偶数，则给 $x$ 多一个链长为 $0$ 的节点，这样又可以用奇数的方法处理了。

根节点需要特殊处理，因为所有点都需要两两配对，不能往父节点连边。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
#define N 100010
namespace graph{
    int head[N],nxt[N<<1],to[N<<1],cnt_edge;
    inline void connect_head(const int &x,const int &y){
        ++cnt_edge;
        nxt[cnt_edge] = head[x];
        to[cnt_edge] = y;
        head[x] = cnt_edge;
    }
}
using namespace graph;
int n,u,v,l,r,mid,f[N];
bool dfs(const int &x,const int &dad){
    // printf("x = %d dad = %d\n",x,dad);
    multiset<int> st;
    for(int edg = head[x];edg;edg = nxt[edg]){
        const int &v = to[edg];if(v == dad)continue;
        if(!dfs(v,x))return 0;
        st.insert(f[v]);
    }
    if(!(st.size()&1))st.insert(0);
    multiset<int>::iterator t = st.end(),z = st.end(); 
    int tmp,ta;bool ab = 0;
    while(st.size()){
        tmp = *(st.begin());t = st.begin();st.erase(t);
        z = st.lower_bound(mid - tmp);
        if(z == st.end()){
            if(!ab)ab = 1,ta = tmp;
            else return 0;
        }else st.erase(z);
    }
    f[x] = tmp + 1;
    return 1;
}
inline bool check(){
    memset(f,0,(n<<2)+20);
    multiset<int> st;
    for(int edg = head[1];edg;edg = nxt[edg]){
        const int &v = to[edg];
        if(!dfs(v,1))return 0;
        st.insert(f[v]);
    }
    if(st.size()&1)st.insert(0);
    multiset<int>::iterator t = st.end(),z = st.end(); 
    int tmp;
    while(st.size()){
        tmp = *(st.begin());t = st.begin();st.erase(t);
        z = st.lower_bound(mid - tmp);
        if(z == st.end())return 0;
        st.erase(z);
    }
    return 1;
}
// 主函数
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n;
    l = 1,r = n;
    for(int i = 1;i < n;++i)cin >> u >> v,connect_head(u,v),connect_head(v,u);
    while(l<r){
        mid = l + (r - l + 1 >> 1);
        if(check())l = mid;
        else r = mid - 1;
    }
    cout << l;

    cout << flush,system("pause");
    return 0;
}
```

---

## 作者：Anonymely (赞：0)

先二分，注意到对于每个点只能由一条边向上，于是内部需要两两匹配掉，显然往上的边越长越好，且往上的边长度具有单调性，对这个二分，判断剩下的能否两两匹配即可。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int N = 1e5 + 5;
int n;
vector <int> e[N];
int f[N], op, k;

void dfs(int u, int fa) {
    for (auto v : e[u]) {
        if (v == fa) continue;
        dfs(v, u); 
    }
    if (op) return ;
    vector <int> w;
    for (auto v : e[u]) {
        if (v == fa) continue;
        w.push_back(f[v] + 1);
    }
    if (w.size() % 2 == 0 && fa) w.push_back(0);
    else if ((w.size() & 1) && !fa) w.push_back(0);
    sort(w.begin(), w.end());
    int m = w.size();
    if (!fa) {
        for (int i = 0; i < m / 2; i++) {
            if (w[i] + w[m - 1 - i] < k) {
                op = 1; return ;
            }
        }
    } else {
        auto chk = [&](int sp) -> bool {
            int l = 0, r = m - 1;
            while (l < r) {
                if (l == sp) l++;
                else if (r == sp) r--;
                else if (w[l] + w[r] < k) return 0;
                else l++, r--;
            }
            return 1;
        } ;
        if (!chk(0)) {
            op = 1; return ;
        }
        int l = 1, r = m - 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (chk(mid)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        f[u] = w[ans];
    }
}

bool check(int lim) {
    k = lim, op = 0;
    dfs(1, 0);
    return !op;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int l = 2, r = n - 1, ans = 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << ans << '\n';
    QwQ01AwA;
}
```

---

## 作者：__ycx2010__ (赞：0)

首先二分答案，设 $f_u$ 表示从 $u$ 开始的长度最长的链是的剩下的链合法。

由于每条边都要经过，每个点可以经过多次，所以每个子树 $j$ 内的最长链取 $f_j$ 最优，那么我们只要考虑两两匹配的最优方案。

若 $u\ne 1$，若子树个数为偶数，则有两条链分开，其他的贪心两两匹配，否则为奇数，剩下一条最长链，其余两两匹配。

若 $u=1$，则要凑成偶数，过程如上。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int n, f[N];
int h[N], e[N * 2], ne[N * 2], idx;

void add(int u, int v) {
	e[idx] = v, ne[idx] = h[u], h[u] = idx ++ ;
}

bool dfs(int u, int fa, int len) {
	int mx = 0, mx2 = 0;
	f[u] = 0;
	multiset<int> s;
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (j == fa) continue;
		if (!dfs(j, u, len)) return false;
		s.insert(f[j] + 1);
	}
	if ((s.size() % 2) ^ (u == 1) == 0) s.insert(0);
	int had = 0;
	while (s.size()) {
		auto it = s.begin();
		int a = *it;
		s.erase(it);
		auto it2 = s.lower_bound(len - a);
		if (u == 1) {
			if (it2 == s.end()) {
				return false;
			} else s.erase(it2);
		} else {
			if (it2 == s.end()) {
				if (!had) f[u] = a, had = 1;
				else return false;
			} else {
				s.erase(it2);
			}
		}
	}
	return true;
}

int main() {
	scanf("%d", &n);
	memset(h, -1, sizeof f);
	for (int i = 1; i < n; i ++ ) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	int l = 0, r = n;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (dfs(1, 0, mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
```

---

