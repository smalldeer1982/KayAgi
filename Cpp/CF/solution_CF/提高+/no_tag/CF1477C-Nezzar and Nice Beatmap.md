# Nezzar and Nice Beatmap

## 题目描述

Nezzar loves the game osu!.

osu! is played on beatmaps, which can be seen as an array consisting of distinct points on a plane. A beatmap is called nice if for any three consecutive points $ A,B,C $ listed in order, the angle between these three points, centered at $ B $ , is strictly less than $ 90 $ degrees.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1477C/e3be07fe7f328d9736ba1797d6c378eea9a0cf27.png)Points $ A,B,C $ on the left have angle less than $ 90 $ degrees, so they can be three consecutive points of a nice beatmap; Points $ A',B',C' $ on the right have angle greater or equal to $ 90 $ degrees, so they cannot be three consecutive points of a nice beatmap.Now Nezzar has a beatmap of $ n $ distinct points $ A_1,A_2,\ldots,A_n $ . Nezzar would like to reorder these $ n $ points so that the resulting beatmap is nice.

Formally, you are required to find a permutation $ p_1,p_2,\ldots,p_n $ of integers from $ 1 $ to $ n $ , such that beatmap $ A_{p_1},A_{p_2},\ldots,A_{p_n} $ is nice. If it is impossible, you should determine it.

## 说明/提示

Here is the illustration for the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1477C/c3fc0fe3cc31d46f5db97d11a3cc278faa7f4e6f.png)Please note that the angle between $ A_1 $ , $ A_2 $ and $ A_5 $ , centered at $ A_2 $ , is treated as $ 0 $ degrees. However, angle between $ A_1 $ , $ A_5 $ and $ A_2 $ , centered at $ A_5 $ , is treated as $ 180 $ degrees.

## 样例 #1

### 输入

```
5
0 0
5 0
4 2
2 1
3 0```

### 输出

```
1 2 5 3 4```

# 题解

## 作者：Miko35 (赞：12)

一道不错的思维题 $(2200)$。

题意简述：平面上有 $n$ 个点 $(3\leq n\leq 5000)$，问题是要你给出一个点的排列，使得任意连续三个点所形成的角为锐角，若无解则输出 $-1$。~~显然，这样的排列是一定存在的。~~

刚看到题的时候立即就想到，对于一个点 $A$，一定存在一个点 $O$，使得对于剩下任意一个点 $B$ 都有 $∠AOB<90\degree$，理由是：一开始随便选择一个点 $O'$，若存在一个点 $B'$ 使得 $∠AO'B'\ge 90\degree$，那么把 $B'$ 作为新的 $O$ 点，重复这个过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/kn4zpw58.png)

以这个图为例，显然 $∠AO'B'\ge 90\degree$，这样我们就把 $B'$ 当做新的 $O'$ 继续做。但是这样就会出现一个问题。图中红色区域内的点原本在 $O'$ 的“可选取范围”之中，然而替换为 $B'$ 之后却不是。正确性如何保证？

不妨换个思路，观察上述过程中，每更换一次 $O$，当前点到 $O$ 的距离都会增加。结合数据范围，这样可以想到，下一步选择的就是距离 $A$ **最远的点**。

![](https://cdn.luogu.com.cn/upload/image_hosting/cqdv1b1k.png)

知道这个结论之后证明并不困难，若当前点为 $A$，距离它最远的点为 $O$，那么其余的所有点一定都在以 $A$ 为圆心 $AO$ 为半径的圆内，从而一定在蓝色直线，也就是 $O$ 的下一个点的可选取范围之中。所以若此次选择的是最远的点，可以保证下次无论选取哪一个点，都是合法的。从任意一点出发，每次都选取距离当前的点最远的点作为下一个点，这样就构造出了一种方案。

代码：

```cpp
const int N=5010;
int n;
ll x[N],y[N],v[N],now,l,res;
inline ll dis(int a,int b){
	return (x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]);
}
int main(){
	read(n),l=n;
	for(rgi i=1;i<=n;++i)read(x[i],y[i]);
	while(l){
		v[res=now]=1,--l;
		for(rgi j=1;j<=n;++j){
			if(!v[j]&&dis(now,j)>dis(now,res))res=j;
		}
		write(now=res,' ');
	}
	return 0;
}
```



---

## 作者：dead_X (赞：4)

## 前言
垃圾 System Tests 放过了我的卡精度错解（

这个题被我一个 MO 同学秒杀了！
## 结论
我们直接说结论：必定有解。

我们考虑一个构造方案：

* 选第一个点。
* 之后每次选择没选中的点中**离前一个被选中的点最远**的点。

可以证明这是对的。
## 证明
考虑每个角，必然是连续选的三个点组成的。

我们画一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/qa8jzigf.png)

然后随便挑三个点来考虑。

![](https://cdn.luogu.com.cn/upload/image_hosting/eydpqcsf.png)

不难发现，如果我们形成了一个钝角，画风一定是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/arjbpi4w.png)

但是如果我们在连了蓝线之后又连了这条绿线，但是这样第三个点和第一个点的距离就比第二个点大了。

由于我们保证了第二个点一定是最远的点，所以第三个点一定在黄线的同侧，因此这个夹角一定是锐角，证毕。
## 代码
注意，算距离的时候要保证精度，不用 ``sqrt`` 和 ``double``。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int x[10003],y[10003];
bool f[10003];
long long dis(int A,int B)
{
	int p=abs(x[A]-x[B]),q=abs(y[A]-y[B]);
	return p*p+q*q;
}
int ans[10003],cnt;
void print(int x)
{
	ans[++cnt]=x;
}
void fff()
{
	for(int i=1; i<=cnt; i++) printf("%d ",ans[i]);
	return ;
}
signed main()
{
	int n=read();
	for(int i=1; i<=n; i++) x[i]=read(),y[i]=read();
	print(1);
	f[1]=1;
	for(int i=1,lst=1,llst=-1; i<n; i++)
	{
		long long mn=-1;
		int k=0;
		for(int j=1; j<=n; j++) if(!f[j])
		{
			long long t=dis(lst,j);
			if(t>mn)
			{
				mn=t;
				k=j;
			}
		}
		f[k]=1;print(k);
		llst=lst,lst=k;
	}
	fff();
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

提供一个不带脑子的做法。

首先，让答案等于 $[1,2,\dots,n]$。这肯定会产生一些不合法角度。

于是，我们考虑冒泡排序：扫描排列，每一次遇见 $p_j,p_{j+1},p_{j+2}$ 产生不合法角度，就交换 $j+1,j+2$；显然每一次交换要么减少一个不合法要么将一个不合法往后推迟。由于每一个不合法位置最多推迟 $n$ 遍，自然只需要将数组扫描 $n$ 遍。

代码：

```cpp

ll x[5005],y[5005];
bool chk(int a,int b,int c){
	ll x1=x[a]-x[b],y1=y[a]-y[b];
	ll x2=x[c]-x[b],y2=y[c]-y[b];
	return x1*x2+y1*y2>0;
}
int perm[5005];
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;cin>>n;
	rep(i,n)cin>>x[i]>>y[i];
	rep(i,n)perm[i]=i;
	rep(i,n+1){
		bool ok=1;
		rep(j,n-2)if(!chk(perm[j],perm[j+1],perm[j+2])){
			ok=0;swap(perm[j+1],perm[j+2]);
		}
		if(ok){
			rep1(i,n)cout<<perm[i-1]+1<<" \n"[i==n];
			return 0;
		}
	}
	cout<<-1<<endl;
}
```

---

## 作者：lalaouye (赞：0)

不要畏惧几何题。

注意到如果 $A_{p_i},A_{p_{i+1}},A_{p_{i+2}}$ 三个点构成了钝角，则交换 $p_{i+1},p_{i+2}$ 就可以将这三个点组成的角变成锐角，然而有可能会影响到 $p_{i-1}$，那么继续往后进行类似的处理即可，并且显然后面的修改不会影响到前面，手画一下图就会发现即使后面的修改了，前一个角也一定是锐角，因为前面的三个角一开始一定是钝角才会继续往后修改，而改变了顺序之后后面的那个角不可能成为钝角，手玩一下可以更好的理解。

时间复杂度 $\mathcal{O}(n^2)$，代码：

 
```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i (l); i <= r; ++ i)
#define rrp(i, l, r) for (int i (r); i >= l; -- i)
#define eb emplace_back
#define pii pair <int, int>
#define ls (p << 1)
#define rs (ls | 1)
using namespace std;
constexpr int N = 2.5e6 + 5, B = 35, P = 1e9 + 7;
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = x * x % P) if (y & 1) ret = ret * x % P;
  return ret;
}
int n;
int x[N], y[N];
int p[N];
int dist (int i, int j) {
  return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}
bool check (int i, int j, int k) {
  int a = dist (i, j), b = dist (i, k), c = dist (j, k);
  if (b >= (unsigned long long) a + c) return 1;
  return 0;
}
int32_t main () { 
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd ();
  rep (i, 1, n) p[i] = i;
  rep (i, 1, n) {
    x[i] = rd (), y[i] = rd ();
  }
  // cout<<check(2,3,4)<<endl;
  rep (i, 1, n - 2) {
    int j = i;
    while (check (p[j], p[j + 1], p[j + 2])) {
      // cout<<j<<endl;
      swap (p[j + 1], p[j + 2]);
      -- j;
      if (j < 1) break;
    }
  }
  rep (i, 1, n) printf ("%lld ", p[i]);
}
```

---

## 作者：Lezy233 (赞：0)

# [Nezzar and Nice Beatmap](https://www.luogu.com.cn/problem/CF1477C)


## 题解思路
> 做法：随机化乱搞。

1. 每次查询时将点**随机化排列**。
1. 每次暴力遍历所有没有填过的点。
- 可以的话查询下一个。
- 不行就将当前点排出。

没错，就是这么简单。

接下来我们思考为什么这样可行。

显然，对于还未选择的点集 $S$ 和一条已经确定的边 $\vec{uv}$ ，当且仅当 $\forall w \in S, \vec{uv} \cdot \vec{vw} \le 0$ 时其他点才不能选择，此时我们会进行换一个点尝试的操作，此时显然有 $\vec {uw} \cdot \vec {wv} \gt 0$ 这一个合法的答案。

当然仅仅是这样的话很有可能复杂度被卡到 $O(n^3)$ ，关键在于最初的那个随机化，使得我们将所有点视为在二维平面上随机分布，这样显然一步找到下一个点的概率是 $\frac 1 2$ ，每一次找点的期望次数是 $\frac {\left| S \right| } {2}$ 次，时间复杂度为 $O(n^2)$ 。

实际上 [这份代码](https://codeforces.com/contest/1477/submission/286609230) 在 CodeForces 上跑得很快，最慢测试点用时 $108 \text ms$ 。

## AC 代码
```cpp
#include <bits/stdc++.h>
using std::cin, std::cout, std::vector, std::array;
#define endl "\n"
#define ALL(x) x.begin(), x.end()
using ll = long long;
using A3I = std::array<int, 3>;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
    int n; cin>>n;
    vector<array<int,2>> ps(n);
    for(auto &[x,y]:ps) cin>>x>>y;

    auto isAcute_Angle = [&ps](int u, int v, int w) {
        ll ba_X = 1LL*ps[u][0]-ps[v][0], ba_Y = 1LL*ps[u][1]-ps[v][1];
        ll bc_X = 1LL*ps[w][0]-ps[v][0], bc_Y = 1LL*ps[w][1]-ps[v][1];
        return ba_X*bc_X+ba_Y*bc_Y > 0;
    };
    
    vector<int> IDs(n);
    std::iota(ALL(IDs), 0);
    while(true) {
        std::ranges::shuffle(IDs, rng);
        
        vector<int> res = {IDs[0]};
        vector<short> used(n);
        used[0] = 1;
        auto dfs = [&](auto self)->bool {
            if(res.size() == n) return true;
            int curSiz = res.size();
            for(int i=0; i<n; ++i) if(!used[i]) {
                if(curSiz == 1 || isAcute_Angle(res[curSiz-2], res[curSiz-1], IDs[i])) {
                    used[i] = 1;
                    res.emplace_back(IDs[i]);
                    if(self(self)) return true;
                    used[i] = 0;
                    res.pop_back();
                }
            }
            return false;
        };
        if(dfs(dfs)) {
            for(auto &i:res) cout << i+1 << " ";
            break;
        }
    }
    cout << endl;
}

int32_t main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T = 1;
    // std::cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：fanfansann (赞：0)

**每日妙妙题精选**

**Problem F Nezzar and Nice Beatmap**

平面上有 $n$ 个点（$3 ≤ n ≤ 5000$），请你找到一个点的排列，如 $a_1,a_2,a_3,a_4,\cdots,a_n$，使得这个排列中的任意相邻的三个点 ABC 组成的角 ∠ABC 是锐角（指 $∠a_1a_2a_3，∠a_2a_3a_4，∠a_3a_4a_5,\cdots, ∠a_{n-2}a_{n-1}a_n$均为锐角）

**Solution**

题目要求的是输出一个排列，这个排列所有连续的三个点组成的角都是锐角。

我们首先考虑任意三个点

画一个草图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210204214159789.png?x-oss-process=image )

我们发现一个钝角三角形，除了有钝角以外，还有两个锐角！


也就是说根据我们选择的顺序不同，是一定能找到一个锐角的排列的，也就是说一定是有解的。



我们发现钝角的对边是最长的那一条，如果我们不想要那个钝角，我们把这个最长的对边，变成我们的角边，不就不是钝角了嘛

思路来了，我们从任意一个点出发，在所有没有被选择过的点之中，找到一个跟它距离最远的点，连上，这样把所有最长的**对边**都变成**角边**，不就没有钝角了嘛


然后我们扩充到四个点


![在这里插入图片描述](https://img-blog.csdnimg.cn/2021020421422774.png?x-oss-process=image )
~~由于一定存在解，我们每次选择最远的点，这样就不会有钝角啦~~ 

考虑证明一下这个解法。

如果对于任意三个点，ABC ，我们已经确定选择了离 A 最远的 B ，离 B 最远的 C，那么 AC 一定小于 AB，那么 B 的对边一定不是最长的边，也就意味着 ∠ABC 一定是锐角（


**Code**

注意为了减少精度误差，因为题目中并没有提示精度误差的大小，说明**不能有精度误差**，所以我们求距离的时候就不用开根了，反正我们只需要比大小就行了。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;
typedef long long ll;
typedef int itn;
const int N = 5e4 + 7, mod = 1e9 + 7;
const ll INF = 1e18 + 7;

struct Point
{
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) { }
}p[N];

typedef Point Vector;
typedef Point POint;
int n, m;
ll ans[N], vis[N];

itn main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i)
        scanf("%lld%lld", &p[i].x, &p[i].y);
    ans[1] = vis[1] = 1;
    for(int i = 2; i <= n; ++ i) {
        ll maxx = -1;
        ll id = -1;
        for(int j = 1; j <= n; ++ j) {
            if(vis[j] == 0) {
                if(id == -1 || maxx < (p[j].x - p[ans[i - 1]].x) * (p[j].x - p[ans[i - 1]].x) + (p[j].y - p[ans[i - 1]].y) * (p[j].y - p[ans[i - 1]].y)) {
                    maxx = (p[j].x - p[ans[i - 1]].x) * (p[j].x - p[ans[i - 1]].x) + (p[j].y - p[ans[i - 1]].y) * (p[j].y - p[ans[i - 1]].y);
                    id = j;
                }
            }
        }
        ans[i] = id, vis[id] = 1;
    }
    for(int i = 1; i <= n; ++ i) {
        printf("%lld ", ans[i]);
    }
    puts("");
    return 0;
}

```

---

## 作者：Fairicle (赞：0)

构造题.

考虑一个钝角三角形是什么样的。如图所示，有且仅有一个钝角，其中钝角所对的边是最长的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/rjc1zswd.png)

如果出现了一个钝角三角形，一定是 $A$ 点连向了 $B$ 点，然后 $B$ 点连向了 $C$ 点这样的方式。那么为什么不直接把 $AC$ 连起来？

于是一个做法出现了：首先随便选一个起始点，然后对于每一个选定的点，找还未被选点中距离它最远的点。

考虑反证法：

如果距离 $A$ 最远的是 $B$，距离 $B$ 最远的是 $C$，此时我们如果得到一个钝角三角形，那么就说明 $AC > AB + BC$（不可能取等，取等就会发现两点重合），与 $B$ 是距离 $A$ 最远的点不符。所以这种做法不会出现钝角三角形。

code：

```cpp
#include"bits/stdc++.h"
using namespace std;
#define ri register int
#define ll long long
#define N 5010
int n,ans[N],ok[N];
ll x[N],y[N];
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(ri i=1;i<=n;++i) cin>>x[i]>>y[i];
    ans[1]=ok[1]=1;
    for(ri i=2;i<=n;++i){
        ll mxdis=-1,idx=-1;
        for(ri j=1;j<=n;++j){
            if(ok[j]) continue;
            if(idx==-1||mxdis<(x[j]-x[ans[i-1]])*(x[j]-x[ans[i-1]])+(y[j]-y[ans[i-1]])*(y[j]-y[ans[i-1]])) mxdis=(x[j]-x[ans[i-1]])*(x[j]-x[ans[i-1]])+(y[j]-y[ans[i-1]])*(y[j]-y[ans[i-1]]),idx=j;
        }
        ans[i]=idx;ok[idx]=1;
    }
    for(ri i=1;i<=n;++i) cout<<ans[i]<<" ";
    return 0;
}
```


---

