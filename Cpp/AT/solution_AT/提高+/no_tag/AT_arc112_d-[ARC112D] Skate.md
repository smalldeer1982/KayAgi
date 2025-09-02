# [ARC112D] Skate

## 题目描述

给定一个 $h$ 行 $w$ 列的网格图，图中的每个格子不是`#`就是`.`。

若当前处于静止状态，可以向四个方向中的任意一个移动，直到到达网格图边界或到达一个为`#`的格子时才可停止。

将图中上起第 $r$ 行左起第 $c$ 列的格子记为 $(r,c)$。“从 $(r,c)$ 来看，可以满足目的”的条件是：从 $(r,c)$ 出发，通过以上形式的移动，在移动若干次以后能够访问到图中的所有格子。

问最少改变多少个`.`格子为`#`格子才能满足：从任意一个格子来看，都能满足目的？

## 说明/提示

#### 数据规模与约定

$2\le h,w\le 1000$。

#### 样例 #1 解释

将格子 $(2,2)$ 改成`#`即可。

## 样例 #1

### 输入

```
3 9
.........
.........
.........```

### 输出

```
1```

## 样例 #2

### 输入

```
10 10
..........
#...#.....
..........
..........
..........
....#.....
.#......#.
..........
..........
..........```

### 输出

```
6```

# 题解

## 作者：StudyingFather (赞：8)

容易发现，无论起点是哪个格子，最后都能到达地图的左上角，因此只需统计从$(1, 1)$ 出发情况下的答案即可。

在这种情况下，最优的行进方案一定是从按行覆盖或按列覆盖二者之一，于是考虑如何统计一行（列）已经被覆盖。

由于边界的存在，边界的两个行（列）都是可以覆盖的。而对于地面格，由于在该格需要停下，该格所在行的覆盖情况和所在列的覆盖情况等价。

考虑建立图论模型：如果 $(r, c)$ 为地面格，则从第 $r$ 行向第 $c$ 列连边，表示二者被覆盖的情况一致。如果两行（列）位于同一连通分量内，则只要其中一行（列）被覆盖，另外一行（列）即可同样被覆盖。

到这里，所求就等价于，求最少添加多少条边，使得所有行（列）处在同一个连通分量中。

并查集维护即可，时间复杂度 $O(hw \log hw)$。

```cpp
// Problem: D - Skate
// Contest: AtCoder - AtCoder Regular Contest 112
// URL: https://atcoder.jp/contests/arc112/tasks/arc112_d
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cstring>
#include <iostream>
#include <string>
using namespace std;
struct dsu {
  int fa[2005];
  void init(int n) {
    for (int i = 0; i < n; i++) fa[i] = i;
  }
  int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
  }
} ds;
string ma[1005];
bool vis[2005];
int main() {
  int h, w;
  cin >> h >> w;
  for (int i = 0; i < h; i++) cin >> ma[i];
  ds.init(h + w - 1);
  // 所有边界覆盖情况一致
  ds.merge(0, h);
  ds.merge(0, h + w - 1);
  ds.merge(h - 1, h);
  ds.merge(h - 1, h + w - 1);
  for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++) {
      if (ma[i][j] == '#') ds.merge(i, h + j);
    }
  int cnt1 = 0, cnt2 = 0;
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < h; i++) {
    int x = ds.find(i);
    if (!vis[x]) cnt1++, vis[x] = true;
  }
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < w; i++) {
    int x = ds.find(h + i);
    if (!vis[x]) cnt2++, vis[x] = true;
  }
  cout << min(cnt1 - 1, cnt2 - 1) << endl;
  return 0;
}
```

---

## 作者：koukilee (赞：2)

注意不要把题目中的 “停止” 理解成 “终止” 了，不然你读题会读半天。

一个 $h \times w$ 的矩阵，每个点有 `#` 与 `.` 两种情况，每个点可以向四联通方向走，直到遇到边界或者 `#` 停止。

求解最后最少添加多少个 `#` 使得每一个点都可以通过上述方式到达所有点。

****

我们从简单入手，如何判断初始矩阵是否满足条件？

最简单的做法就是从每一个点开始跑一遍 BFS 判断是否联通，时间复杂度 $O(h^2w^2)$。

明显是直接 TLE 飞。

分析题目，发现答案具有单调性，但是并不能二分出具体每一个 `#` 的摆放位置，所以不能二分答案，或者说是比较不好做的。

发现一个 `#` 只对这一行和这一列有贡献，我们于是将整个矩阵拆成 $h$ 个行点表示一行，$w$ 个列点表示一列。

如果一个点 $(i,j)$ 是 `#` 就将他的 $h_i$ 与 $w_j$ 相连，表示第 $i$ 行和第 $j$ 列上的点都可以通过这个点停下来并互相到达。

题目转化为 $h$ 个横边，$w$ 个列边，连最小的边数使得最后成为一个联通块，即每一个点互相可达。

时间复杂度 $O(n \alpha (n))$ 。


****
Code

```c++
/* The code is from koukilee*/

int main() noexcept{
	read(n, m);
	for (i32 i = 1; i <= n + m; i++)
		s[i] = i;
	for (i32 i = 1; i <= n; i++){
		scanf("%s", (ch[i] + 1));
		for (i32 j = 1; j <= m; j++){
			if (ch[i][j] == '#')
				s[find(i)] = find(j + n);
		}
	}
	
	s[find(1)] = find(1 + n), s[find(1)] = find(n + m);
	s[find(n)] = find(1 + n), s[find(n)] = find(n + m);
	for (i32 i = 1; i <= n; i++){
		i64 x = find(i);
		if (!vis[x])
			vis[x] = 1, sa++;
	}
	
	vis.reset();
	for (i32 i = n + 1; i <= n + m; i++){
		i64 x = find(i);
		if (!vis[x])
			vis[x] = 1, sb++;
	}
	
	put(min(sa, sb) - 1);
    return 0;
}

```

---

## 作者：cqbzlzm (赞：1)

### Description

有一个 $n\times m$ 的溜冰场，每个点可能是 $.$（**冰**）或者 $\#$（**地**）。每次溜冰只有在碰到边界或者碰到**地**才能停下来。求至少将多少**冰**改成**地**才能使地从任意点出发溜冰，可以遛完整个溜冰场。

### Solution

这种题应该算作套路了吧。

我们发现直接硬钢的话很难搞，那么我们考虑**地**的意义是什么。事实上，**地**可以让一次溜冰停下来。

我们考虑一个全是**冰**的溜冰场，我们只能一脚滑到底，这时候面前出现了一块**地**，于是我们可以停下来，选择继续前进或者转弯，甚至掉头。

继续思考，我们可以把溜冰场看做 $n+m$ 条冰道，只有在**地**上可以切换冰道。所以**地**的作用其实是横竖间冰道的转换。若 $(i,j)$ 是冰道，那么我们给第 $i$ 条横冰道和第 $j$ 条竖冰道连边，这样图显然是二分图。最终目标是通过加边使得原图的左部点或右部点全部联通，用并查集计算即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000;
int n, m;
int father[MAXN + 5];
int find(int x) {return father[x] == x ? x : father[x] = find(father[x]);}
bool merge(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return 0;
    father[a] = b;
    return 1;
}
int vis[MAXN + 5];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n + m; i ++) father[i] = i;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            char x; cin >> x;
            if (x == '#') merge(i, j + n);
        }
    }
    merge(1, n + 1);
    merge(n, n + 1);
    merge(1, n + m);
    merge(n, n + m);
    int ansi = 0, ansj = 0;
    for (int i = 1; i <= n; i ++) {
        if (!vis[find(i)]) {
            vis[find(i)] = 1;
            ansi ++;
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = n + 1; i <= n + m; i ++) {
        if (!vis[find(i)]) {
            vis[find(i)] = 1;
            ansj ++;
        }
    }
    cout<<min(ansi, ansj) - 1;
    return 0;
}
```

---

## 作者：SoyTony (赞：1)

发现一个 `#` 设置的意义是使得第 $r$ 行和第 $c$ 列可以互达，这种双向的二元关系视为无向边，那么只要连通就可以从任何一个位置出发到达所有位置。而四个拐角处可以使得 $(1,1),(1,W),(H,1),(H,W)$ 四组点对互达，初始将这些边连出。剩下边界的情况例如从第 $r$ 行可以回到第 $1$ 列或第 $W$ 列是单向关系，由于连边（增加 `#`）都是无向边，这些单向关系可以忽略。

现在问题变成给定一个二分图，初始有一些边，要求增加最少的边使得左部点连通或右部点连通，使用并查集维护即可。

提交记录：[Submission - AtCoder](https://atcoder.jp/contests/arc112/submissions/45539792)

---

## 作者：run_away (赞：1)

## 题意

一个长 $h$ 宽 $w$ 的地图，`#` 代表陆地，`.` 代表冰面，如果人在陆地上可以向任何方向转向，否则只能一直滑到边缘然后在边缘选择转向。

现在可以花费 $1$ 的代价把一块冰面改为陆地，求最少花费多少代价使得人从任何地方出发都可以滑到所有地方。

## 分析

显然只会选择垂直转向，因为掉头和停下来再向前没有意义。

这是个点的联通问题，发现加入一块陆地就可以把这个点所在横线和竖线上的点全部联通。

转化为用最少的点让所有线联通在一起。

联通类问题的一个好用工具就是并查集，用 $2n$ 个数表示横线和竖线，这个思路好像在二分图的一些题里也用过。

输入时如果有一块陆地，就直接把它的横与竖连接起来。

枚举每一条横线和竖线，给它们的 $pre$ 打一个 bool 标记。每枚举到一条线，如果它父亲没有被标记过，就说明它是一个新的连通块，这就需要用一条边把它和之前的块连在一起，所以给答案加一。

最后在横与竖的答案中取最小值，由于第一个块不需要连接，所以给答案减一。

注意因为有边界，所以最开始要把四个顶点的横竖线连起来。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
// static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
// #define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
namespace tobe{
	const ll maxn=2e5+5,mod=998244353;
	ll n,m,pre[maxn];
	bool vis[maxn];
	string s;
	inline ll find(ll x){return x==pre[x]?x:pre[x]=find(pre[x]);}
	inline void merge(ll x,ll y){
		x=find(x),y=find(y);
		if(x==y)return;
		pre[x]=y;
	}
	inline void mian(){
		n=read(),m=read();
		for(ll i=1;i<=n+m;++i)pre[i]=i;
		for(ll i=1;i<=n;++i){
			cin>>s;s=" "+s;
			for(ll j=1;j<=m;++j){
				if(s[j]=='#')merge(i,j+n);
			}
		}
		merge(1,1+n),merge(n,1+n);
		merge(1,n+m),merge(n,n+m);
		ll ans1=0,ans2=0;
		for(ll i=1;i<=n;++i){
			if(!vis[find(i)]){
				vis[find(i)]=1;
				++ans1;
			}
		}
		memset(vis,0,sizeof(vis));
		for(ll i=n+1;i<=n+m;++i){
			if(!vis[find(i)]){
				vis[find(i)]=1;
				++ans2;
			}
		}
		write(min(ans1,ans2)-1);
	}
}
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	ll t=1;
	while(t--)tobe::mian();
	// fwrite(obuf,p3-obuf,1,stdout);
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

~~这道题的算法怎么和我用户名重名了？~~

首先观察题目，从每一个格子分别考虑显然不现实，所以我们希望找到每一个格子的共性，即找到每个格子可以到达的**充要条件**帮助我们求解。最好是找到那种每个格子都可以到达的格子。

有没有呢？当然有，从每个格子出发，一定可以到达 $(1,1)$ 以及其他三个角落。所以我们只要判断是否可以从 $(1,1)$ 出发走到每个格子即可。

我们还会发现，这个问题的答案不会超过 $\min(n,m)-2$。因为最劣情况就是样例一，只要在一行或一列的一边除了角落摆满即可。这启示我们从行列的角度考虑。

我们注意到，只要我们可以走到一行，我们就可以通过这一行上的所有地面走到其他列上去，列也同理，可以走到行上去。所以我们可以访问的格子是类似于行列覆盖的。所以我们考虑一行或一列是否可以走到。

如果把每一行和每一列看作一个点，那么位于 $(r,c)$ 的地面相当于串联起了第 $r$ 行和第 $c$ 列，是他们两个只要有一个可达，另一个就一定可达。这十分像合并操作。所以我们考虑将所有互相可达的行和列连起来，用并查集去维护。

我们可以先将四条边连起来，然后枚举每一个地板，连同第 $r$ 行和第 $c$ 列。

最后的答案考虑只要所有行或所有列都互相可达即可。所以答案就是行的连通块数量和列的连通块数量的较小值。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll int
#define il inline
#define N 1005
#define mg(u, v) fu = find(u), fv = find(v), sz[fu] > sz[fv] ? (sz[fu] += sz[fv], fa[fv] = fu) : (sz[fv] += sz[fu], fa[fu] = fv)
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), m = rd(), fu, fv, sz[N << 1], fa[N << 1], t1[N << 1], t2[N << 1], c1, c2;
il ll find(ll x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
char s[N][N];
int main(){
	for (int i = 1; i <= n; i++) scanf ("%s", s[i] + 1);
	for (int i = 1; i <= n + m; i++) fa[i] = i, sz[i] = 1;
	mg(1, n), mg(1, n + 1), mg(1, n + m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (s[i][j] == '#') mg(i, n + j);
	for (int i = 1; i <= n; i++) if (!t1[find(i)]) c1++, t1[find(i)] = 1;
	for (int i = n + 1; i <= n + m; i++) if (!t2[find(i)]) c2++, t2[find(i)] = 1; 
	printf ("%d\n", min(c1, c2) - 1);
	return 0;
}

```

---

## 作者：Autream (赞：0)

## 题意简述
原来的题意有点不清楚，看了好久才看懂。

给你一个 $H \times W$ 的溜冰场（矩阵），其中 `.` 表示冰面，`#` 表示地面。当你在边界或地面上时是静止的，当你静止时可以选择向相邻的四个方向移动，**直到再次停止才能改变方向。**

现在要你求出至少需要添加多少地面才能使从溜冰场上任意一个点出发，都能经过其它所有点。
## 题目分析
不难发现，与 $(x,y)$ 同一行同一列的坐标 $(x+i,y),i \in [1-x,H-x]$ 或 $(x,y+j),j \in [1-y,W-y]$ 总是可以经过的。

地面的作用是停止，停止后可以改变方向。如果 $(x,y)$ 可以到达地面 $(x+a,y)$，那么它就可以另外经过 $(x+a,y+j),j \in [1-j,W-j]$ 这一行。

也就是说，一块地面可以将一行与一列连接起来。我们的目标是将所有的行和列连接起来，其实就是需要我们去找还有多少个行和列没有连接。

考虑枚举是从补全所有的行还是补全所有的列，取最小值，用并查集维护即可。

时间复杂度线性对数。
## AC Code
```cpp
// Problem: [ARC112D] Skate
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc112_d
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Date: 2024/09/29 20:54:19
// Author: Li_Feiy
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)a[i]=read()
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
    char ch=getchar();
    int r=0,w=1;
    while(ch<'0'||ch>'9') w=ch=='-'?-1:w,ch=getchar();
    while(ch>='0'&&ch<='9') r=r*10+ch-'0',ch=getchar();
    return r*w;
}
CI N=2e3+5;
int n,m,ans1,ans2,fa[N],vis1[N],vis2[N];
char mp[N][N];
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y) {fa[find(y)]=find(x);}
signed main() {
	n=read(),m=read();
	rep(i,1,n+m) fa[i]=i;
	rep(i,1,n) rep(j,1,m) {std::cin>>mp[i][j];if(mp[i][j]=='#') merge(i,n+j);}//表示将第i行和第j列连接起来
	merge(1,n+1),merge(1,n+m);
	merge(n,n+1),merge(n,n+m);//初始时最外围是连通的
	rep(i,1,n) if(!vis1[find(i)]) vis1[find(i)]=1,ans1++;//补全所有的行
	rep(i,n+1,n+m) if(!vis2[find(i)]) vis2[find(i)]=1,ans2++;//补全所有的列
	std::cout<<std::min(ans1,ans2)-1;
    return 0;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 思路

这道题我们发现如果地图的左上角能到达所有点的话整张图就一定联通了。

然后我们考虑并查集。

我们在每个井号的地方把他的行和列所在的集合合并。最后我们看行和列的集合有多少个不同的，而我们需要使整张图连通，所以我们要把那些所在不同集合的点连起来，假设有 $n$ 个点则我们需要连 $n-1$ 条边。最后取最小值即可。

### 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll,ll>
#define mkp make_pair
using namespace std;
ll read() {
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
ll f[2005];
ll findr(ll x) {
	if(f[x]==x) {
		return x;
	}
	return f[x]=findr(f[x]);
}
char a[2005][2005];
bool vis[2005];
int main() {
// 	freopen("skate.in","r",stdin);
// 	freopen("skate.out","w",stdout);
	ll n,m;
	cin>>n>>m;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			cin>>a[i][j];
		}
	}
	for (int i=1; i<=n+m; i++) {
		f[i]=i;
	}
	f[findr(1)]=findr(n+1);
	f[findr(1)]=findr(n+m);
	f[findr(n)]=findr(n+1);
	f[findr(n)]=findr(n+m);
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			if(a[i][j]=='#') {
				f[findr(i)]=findr(n+j);
			}
		}
	}
	ll ans1=0;
	for (int i=1; i<=n; i++) {
		if(!vis[findr(i)]) {
			vis[findr(i)]=1;
			ans1++;
		}
	}
	ll ans2=0;
	memset(vis,0,sizeof(vis));
	for (int i=1; i<=m; i++) {
		if(!vis[findr(n+i)]) {
			vis[findr(n+i)]=1;
			ans2++;
		}
	}
	cout<<min(ans1,ans2)-1;
	return 0;
}
~~~

---

