# [ABC273F] Hammer 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc273/tasks/abc273_f

数直線の原点に高橋君がいます。高橋君は座標 $ X $ にあるゴールに移動しようとしています。

また、数直線上に $ N $ 枚の壁と $ N $ 本のハンマーがあります。

- 座標 $ Y_1,Y_2,\dots,Y_N $ にはそれぞれタイプ $ 1,2,\dots,N $ の壁があります。
  - 最初、高橋君は壁を超えて移動することができません。
- 座標 $ Z_1,Z_2,\dots,Z_N $ にはそれぞれタイプ $ 1,2,\dots,N $ のハンマーがあります。
  - 高橋君はハンマーのある座標に着くとそこにあるハンマーを手に入れます。
  - タイプ $ i $ のハンマーはタイプ $ i $ の壁を破壊するための専用のもので、タイプ $ i $ のハンマーを手に入れた後でなら、タイプ $ i $ の壁を破壊して通過できるようになります。

高橋君がゴールに到達することが可能か判定し、可能であれば移動距離の最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 1500 $
- $ 1\ \le\ |X|,|Y_i|,|Z_i|\ \le\ 10^9 $
- 合計 $ 2\ \times\ N\ +\ 1 $ 個の座標 $ X,Y_i,Z_i $ は相異なる

### Sample Explanation 1

以下の手順により、移動距離 $ 40 $ で高橋くんがゴールに到達でき、これが移動距離の最小です。 - 座標 $ 0 $ から高橋君が行動を開始する。 - 座標 $ 3 $ に行く。タイプ $ 3 $ のハンマーを手に入れる。 - 座標 $ 5 $ に行く。タイプ $ 1 $ のハンマーを手に入れる。 - 座標 $ -2 $ に行く。タイプ $ 1 $ の壁を破壊する。 - 座標 $ -5 $ に行く。タイプ $ 3 $ の壁を破壊する。 - 座標 $ -10 $ に行く。タイプ $ 2 $ のハンマーを手に入れる。 - 座標 $ 8 $ に行く。タイプ $ 2 $ の壁を破壊する。 - 座標 $ 10 $ に行く。ここがゴールである。

### Sample Explanation 2

ゴールに移動するために、ハンマーを手に入れる必要も壁を破壊する必要もない場合もあります。

### Sample Explanation 3

高橋君がタイプ $ 1 $ のハンマーを手に入れることは不可能であり、ゴールに辿り着くこともできません。

## 样例 #1

### 输入

```
3 10
-2 8 -5
5 -10 3```

### 输出

```
40```

## 样例 #2

### 输入

```
5 -1
10 -20 30 -40 50
-10 20 -30 40 -50```

### 输出

```
1```

## 样例 #3

### 输入

```
1 100
30
60```

### 输出

```
-1```

## 样例 #4

### 输入

```
4 865942261
703164879 -531670946 -874856231 -700164975
-941120316 599462305 -649785130 665402307```

### 输出

```
4078987507```

# 题解

## 作者：myyes (赞：7)

摘自我的博客文章：[钥匙题专项训练](https://www.luogu.com.cn/blog/666666new/keys-tm)。

今天有师傅想看我的博客，我就来更新一下咩！

题意：数轴上有 $n$ 个锁，第 $i$ 个锁的位置在 $y_i$，它的钥匙位置在 $z_i$，有一个师傅现在在 $0$ 这个位置，他要开车去北京。北京的位置是 $X$。遇到一串钥匙就可以把它撇到皮带上面以后可以随便用它来开对应的锁。问师傅最短好久能到北京？

分析：这个题还是相当的基础的得咩！就是一个简单的区间 DP 得咩。其实就是一个 089 年的[关路灯](https://www.luogu.com.cn/problem/P1220)的模型咩。我们把所有钥匙和锁的位置嗲出来排个序，我们设一个 $f_{l,r,0/1}$ 表示我们已经走完 $l\sim r$ 这些地点的最短时间，现在在 $l$ 还是 $r$。然后就去往左边和右边扩展，计算一下走出去需要花的时间。能更新的条件就是扩展出来的这个锁它在 $[l,r]$ 的范围里面，因为在范围里面的话它肯定已经经过过并撇在自己的皮带上面了。这样就做完了得咩。跟关路灯一模一样的。相当的规范！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,x,y[3333],z[3333];
long long f[3333][3333][2],inf=6666666666666;
struct node
 {
  int x,y;
   bool operator<(node b)
   {return x<b.x;
     }
} a[3333];
 int main()
  {scanf("%d%d",&n,&x);
  for(int i=1;i<=n;i++)scanf("%d",&y[i]),a[++m]={y[i],i};
  for(int i=1;i<=n;i++) scanf("%d",&z[i]),a[++m]=(node){z[i],0};
   a[++m]={x,0};
   a[++m]=(node){0,0};
  sort(a+1,a+m+1);
   int wei=0,chu=0;
  for(int i=1;i<=m;i++)
  	{if(a[i].x==x)wei=i;
}
 for(int i=1;i<=m;i++)
if(!a[i].x) chu=i;
 for(int i=0;i<3333;i++)
 {for(int j=0;j<3333;j++)
{
   f[i][j][0]=f[i][j][1]=inf; }
  }
 f[chu][chu][0]=f[chu][chu][1]=0;
 for(int len=1;len<m;len++)
for(int l=1;l<=m-len+1;l++)
  {
 int r=l+len-1;
  if(l>1)
   {
 if(a[l-1].y>0&&(z[a[l-1].y]<a[l].x||z[a[l-1].y]>a[r].x)){
 }
  else
   {
f[l-1][r][0]=min(f[l-1][r][0],f[l][r][0]+a[l].x-a[l-1].x);
 f[l-1][r][0]=min(f[l-1][r][0],f[l][r][1]+a[r].x-a[l-1].x);
  }
}
 if(r<m)
  {
  if(a[r+1].y>0&&(z[a[r+1].y]<a[l].x||z[a[r+1].y]>a[r].x))
  	 ;else
  {f[l][r+1][1]=min(f[l][r+1][1],f[l][r][0]+a[r+1].x-a[l].x);
f[l][r+1][1]=min(f[l][r+1][1],f[l][r][1]+a[r+1].x-a[r].x);}
  }
    }
  long long ans=inf;
 for(int i=1;i<=wei;i++)
{for(int j=wei;j<=m;j++){
  ans=min(ans,min(f[i][j][0],f[i][j][1]));
  }
   }
  if(ans==inf)cout<<-1;
else cout<<ans;
   return 0;
 }
```

---

## 作者：Iratis (赞：5)

读完题目，很容易发现题目存在阶段，且大区间包含了小区间，所以容易想到区间 dp。将题目数据范围离散化，并定义 $ f[i][j][0/1] $ 表示走遍区间 $ i \sim j $ 且最后在 $ i/j $ 的位置。

所以判断一个区间是否能转移到下一个更大的区间只需要判断现在的区间内是否存在对应的锤子。例如，从 $ [i,j] $ 转移至 $ [i,j+1] $，且 $ j+1 $ 位置为一面墙，那么即判断 $ [i,j] $ 中是否存在能摧毁 $ j+1 $ 位置的墙的锤子。这件事情显然可以对于锤子位置二分，但是作者赛时并未想到，便用了类似状压的方式，利用 bitset 判断转移是否成立。

代码如下：

```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<bitset>
using namespace std;
#define int long long
#define md(a) a=(a%mod+mod)%mod
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
const int N=3005,inf=1e15;
int n,m,x,qx,zx;
int y[N],z[N],f[N][N][2];
bitset<1505>g[N][N];
struct num
{
	int x,ty,val;
	bool friend operator <(num a,num b){return a.x<b.x;}
}pos[N];
void DP1(int l,int r)
{
	f[l][r][0]=min(f[l][r][0],f[l+1][r][0]+pos[l+1].x-pos[l].x);
	f[l][r][0]=min(f[l][r][0],f[l+1][r][1]+pos[r].x-pos[l].x);
}
void DP2(int l,int r)
{
	f[l][r][1]=min(f[l][r][1],f[l][r-1][1]+pos[r].x-pos[r-1].x);
	f[l][r][1]=min(f[l][r][1],f[l][r-1][0]+pos[r].x-pos[l].x);
}
bool check(int l,int r,int x){return g[l][r][x]==1;}
void DP()
{
	for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)f[i][j][0]=f[i][j][1]=inf;
	f[qx][qx][0]=f[qx][qx][1]=0;
	for(int len=2;len<=m;len++)
	{
		for(int i=1;i+len-1<=m;i++)
		{
			int j=i+len-1;
			if(pos[i].val==2){if(check(i+1,j,pos[i].ty))DP1(i,j);}else DP1(i,j);
			if(pos[j].val==2){if(check(i,j-1,pos[j].ty))DP2(i,j);}else DP2(i,j);
		}
	}
}
int solve()
{
	int ans=1e15;
	if(qx<=zx)for(int i=1;i<=qx;i++)ans=min(ans,f[i][zx][1]);
	else for(int i=qx;i<=m;i++)ans=min(ans,f[zx][i][0]);
	if(ans==1e15)return -1;
	return ans;
}
signed main()
{
	scanf("%lld%lld",&n,&x);pos[++m]={0,0,0},pos[++m]={x,0,1};
	for(int i=1;i<=n;i++)scanf("%lld",&y[i]),pos[++m]={y[i],i,2};
	for(int i=1;i<=n;i++)scanf("%lld",&z[i]),pos[++m]={z[i],i,3};
	sort(pos+1,pos+m+1);for(int i=1;i<=m;i++)if(pos[i].val==3)g[i][i][pos[i].ty]=1;
	for(int len=2;len<=m;len++)
	{
		for(int i=1;i+len-1<=m;i++){int j=i+len-1;g[i][j]=(g[i][j-1]|g[i+1][j]);}
	}
	for(int i=1;i<=m;i++){if(pos[i].x==0)qx=i;if(pos[i].x==x)zx=i;}
	DP();cout<<solve();
	return 0;
}
```


---

## 作者：Pengzt (赞：5)

[ABC273F](https://www.luogu.com.cn/problem/AT_abc273_f)

一道比较板的区间 $\text{dp}$。

先对坐标离散化，令离散化数组为 $v[]$。

令 $f_{i,j}$ 表示能走到区间 $[v_i,v_j]$ 的最短路程，显然 $f$ 数组初始为 $inf$。

但发现这样无法转移，可以再增加一维 $k \in \{0,1\}$，表示此时在 $[v_i,v_j]$ 的 $v_i/v_j$ 处。

则有转移方程：

$$f_{i-1,j,0} = \min\{f_{i-1,j,0}, f_{i,j,0}+v_i-v_{i-1}, f_{i,j,1}+v_j-v_{i-1}\}$$

$$f_{i,j+1,1} = \min\{f_{i,j+1,1}, f_{i,j,0}+v_{j+1}-v_i, f_{i,j,1}+v_{j+1}-v_j\}$$

[评测记录](https://www.luogu.com.cn/record/102623222)

---

## 作者：Epoch_L (赞：3)

## F
平面上有墙和锤子，一个锤子对应只能敲掉一面墙，最开始在原点，给定终点，问最小步数。
### Solution
赛时降智，一个简单 DP 应该要过的，客观原因是因为改 D 改了很久。

首先坐标较大可以离散化掉，设 $f(i,j,0/1)$ 表示在区间 $[i,j]$ 的左端或右端的最小答案，然后就写完了，暴力转移即可。在区间扩展的时候，如果扩展到的是墙，要判断当前区间是否包含敲掉那面墙的锤子。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=3e3+7;
int n,T,s[N],t[N],x[N],m,nd[N];
int f[N][N][2];
main(){
  read(n);read(T);
  for(int i=1;i<=n;i++)read(t[i]),x[++m]=t[i];
  for(int i=1;i<=n;i++)read(s[i]),x[++m]=s[i];
  x[++m]=0,x[++m]=T;
  sort(x+1,x+m+1);m=unique(x+1,x+m+1)-x-1;
  for(int i=1;i<=n;i++)s[i]=lower_bound(x+1,x+m+1,s[i])-x;
  for(int i=1;i<=n;i++)t[i]=lower_bound(x+1,x+m+1,t[i])-x,nd[t[i]]=i;
  int S=lower_bound(x+1,x+m+1,0)-x;
  T=lower_bound(x+1,x+m+1,T)-x;
  memset(f,63,sizeof f);
  f[S][S][0]=f[S][S][1]=0;
  for(int len=1;len<m;len++)
  for(int l=1;l<=m;l++){
    int r=l+len-1;
    if(l>1){
      int p=nd[l-1];
      if(!p||(p&&l<=s[p]&&s[p]<=r)){
        f[l-1][r][0]=min(f[l-1][r][0],f[l][r][0]+x[l]-x[l-1]);
        f[l-1][r][0]=min(f[l-1][r][0],f[l][r][1]+x[r]-x[l-1]);
      }
    }
    if(r<m){
      int p=nd[r+1];
      if(!p||(p&&l<=s[p]&&s[p]<=r)){
        f[l][r+1][1]=min(f[l][r+1][1],f[l][r][0]+x[r+1]-x[l]);
        f[l][r+1][1]=min(f[l][r+1][1],f[l][r][1]+x[r+1]-x[r]);
      }
    }
  }
  int ans=1e18;
  for(int i=1;i<=T;i++)
  for(int j=T;j<=m;j++)
    ans=min({ans,f[i][j][0],f[i][j][1]});
  if(ans==(int)1e18)puts("-1");
  else printf("%lld\n",ans);
  return 0;
}
```

---

## 作者：AC_love (赞：1)

首先将初始位置，锤子位置，墙的位置和目的地作为关键点离散化一下。显然点的个数是 $O(N)$ 级别的。

设 $f(l, r, 0 / 1)$ 表示当前走完了 $[l, r]$ 区间内所有的点，且现在在 $l$ 或 $r$ 位置时的最少步数。令初始位置为 $s$，初始化 $f(s, s, 0) = f(s, s, 1) = 0$。

接下来考虑怎么转移。

对于一个 $f(l, r)$，它可以扩展到 $f(l - 1, r)$ 或 $f(l, r + 1)$，当且仅当要扩展的位置不是墙，或要扩展的墙对应的锁在 $[l, r]$ 区间内。

判断能走过去之后直接计算走过去用的步数即可，与之前的 $f$ 值取 $\min$ 来更新。

[code](https://atcoder.jp/contests/abc273/submissions/59511778)

---

## 作者：normalpcer (赞：1)

## 题意翻译
高桥（Takahashi）位于数轴的原点，他希望到达点 $X$。

此外，数轴上还有 $N$ 堵墙和 $N$ 把锤子。
- 坐标 $Y_1, Y_2, \dots, Y_N$ 分别为编号为 $1, 2, \dots, N$ 的墙。
  - 起初，他不能穿过墙。
- 坐标 $Z_1, Z_2, \dots, Z_N$ 分别为编号为 $1, 2, \dots, N$ 的锤子。
  - 当他到达了含有锤子的点，他就获得了这个锤子。
  - 编号为 $i$ 的锤子能且仅能破坏编号同样为 $i$ 的墙。当他获得了一把锤子，他就可以破坏并穿过对应的墙。
  
判断他能否到达目的地。如果可以，寻找他到达目的地的最短路程。

## 思路

使用区间 dp。

由于到达了含有锤子的点必然会获得这个锤子，所以只要知道经过的所有点，就可以知道获得了哪些锤子。

我们可以用状态 $F_{i, j}, G_{i, j}$ 表示：区间 $[i, j]$ 全部走过，且分别处于区间左端或右端的最短路程。

这时我们遇到一个问题：坐标的数据范围很大，直接开数组会爆掉。于是可以考虑“离散化”处理。

注意到，只有有墙或者锤子的点才会对我们造成实际影响。我们可以称呼这些点为“特殊点”（`SpecialPoint`），记录这些特殊点的位置，按照它们的顺序处理即可。

上文所述的 $F_{i, j}$ 和 $G_{i, j}$ 中的 $i, j$ 即特殊点的编号。

考虑如何转移。

首先我们可以断言：对于一次“折返”操作（即进行两次转向），除非到达过没有走过的点，否则一定不会是最优解。这是很显然的，因为这并不会带来额外的“收益”（如获得锤子），只会徒增路程。但是，如果到达过未走过的点，就有可能获得额外的锤子——这是必要的。这也是我们这样设状态的原因。接下来，我们称呼在原方向再走一个点为“顺向”，折返后走到第一个没走过的点为“反向”。

所以转移如下：（$d_{x, y}$ 表示特殊点 $x$ 到 $y$ 的距离）

如果可以转移：（目的地没有墙，或者走过的区域内有对应的锤子）

（左侧顺向）$F_{i-1, j} = \min\left\{F_{i-1, j}, F_{i, j} + d_{i-1, i}\right\}$

（左侧反向）$F_{i-1, j} = \min\left\{F_{i-1, j}, G_{i, j} + d_{i-1, j}\right\}$

（右侧顺向）$G_{i, j+1} = \min\left\{G_{i, j+1}, G_{i, j} + d_{j, j+1}\right\}$

（右侧反向）$G_{i, j+1} = \min\left\{G_{i, j+1}, F_{i, j} + d_{i, j+1}\right\}$

至于初始状态，我们设起点是第 $s$ 个特殊点，即有 $F_{s, s} = G_{s, s} = 0$。另外，将其他的 $F_{i, j}$ 和 $G_{i, j}$ 设为无穷大，可以避免不合法的状态发生意外的转移。

## 编码
理清思路，代码就比较简单了。

首先离散化处理，遍历一遍输入“映射”成特殊点。

然后初始化状态，进行区间 dp 即可。由于我们修改的状态 $[i', j']$ 相比于用到的状态 $[i, j]$，必然有 $i'\le i, j'\ge j$，所以选择倒序遍历 $i$，正序遍历 $j$。

至于最终答案，我采用的方法是，如果当前区间 $[i, j]$ 完全包含了起点到终点的区间，说明它有可能成为答案，进行一次检查。但是 dp 需要完整完成，不能提前结束。例如：
```
Y1 0 Z1 X 
```
这样的情况，从 $0$ 到 $X$ 的区间会比从 $Y_1$ 到 $X$ 的正解先遍历到，但是它不是答案，而是无穷大——这当然是不合理的。

一些细节见源代码的注释。

```cpp
/**
 * @link https://www.luogu.com.cn/problem/AT_abc273_f
 * @link https://atcoder.jp/contests/abc273/tasks/abc273_f
 */

#include <bits/stdc++.h>
#define upto(i,n) for(int i=1;i<=(n);i++)  // 遍历 [1, n]
#define from(i,b,e) for(int i=(b);i<=(e);i++)  // 遍历 [b, e]
#define rev(i,e,b) for(int i=(e);i>=(b);i--)  // 反向遍历 [b, e]
#define chkMin(base,cmp...) (base=std::min({(base),##cmp}))  // 检查最小值
#define check(v, con, otw) (((v) con)? (v): (otw))  // 检查条件，如果条件成立则返回 v，否则返回 otw(otherwise)
typedef long long ll;

#define spCount (N*2+2) // 特殊点的数量。总是包含所有的墙、所有的锤子、起点和终点，共 2N+2 个。
#define _spCount (_N*2+2)  // spCount 的最大值。

// 含义同题面。若无特殊说明，所有数组从 1 开始存。
const int _N = 1505;
int N, X;
int Y[_N], Z[_N];

ll F[_spCount][_spCount], G[_spCount][_spCount];  // 含义见上文；注意，这里需要开 long long，否则可能会被多次折返卡掉。
struct SpecialItem {int p, origin /* 原始列表中的编号；墙为正，锤子为负，其它为 0 */;} sp[_spCount];  // 特殊点及其列表
int begin, end;  // 起点和终点的特殊点编号
ll ans = 0x7fffffffffffffffLL;  // 记录最终答案

void mapping() {    // 映射
    // 统计所有“特殊点”
    sp[1] = { X, 0 };  // 记录终点
    upto(i, N) {
        sp[i*2] = { Y[i], i };  // 墙
        sp[i*2+1] = { Z[i], -i };  // 锤子
    }
    sp[spCount] = { 0, 0 };  // 记录起点
    std::sort( sp+1, sp+spCount+1, [](SpecialItem x, SpecialItem y){return x.p < y.p;} );  // 从小到大排序
    upto(i, spCount) {  // 遍历所有特殊点，找出起点和终点
        if (sp[i].p==0)  begin = i;
        if (sp[i].p==X)  end = i;
    }
}

inline bool reachable(SpecialItem p, int i, int j) {  // 已经走过的区间为 [i, j]，判断是否可以转移到 p
    int wall = p.origin;
    if (wall>0) {  // 有墙，判断能不能砸开
        return i<=Z[wall] && Z[wall]<=j;
    }
    return true;  // 没有墙，必然可以到达
}

int main() {
    scanf("%d%d", &N, &X); 
    upto(i, N) scanf("%d", Y+i); 
    upto(i, N) scanf("%d", Z+i); 
    
    mapping();  // 建立映射

    // 初始化 dp 数组
    std::memset(F, 0x3f, sizeof(F));
    std::memset(G, 0x3f, sizeof(G));
    F[begin][begin] = G[begin][begin] = 0;

    // 动态规划
    rev(i, begin, 1) {
        from(j, begin, spCount) {
            if (reachable(sp[i], sp[i].p, sp[j].p)) {  // 如果可以转移到
                chkMin(F[i][j], F[i+1][j] + sp[i+1].p - sp[i].p);  // 左侧顺向
                chkMin(F[i][j], G[i+1][j] + sp[j].p - sp[i].p);    // 左侧反向
            }
            if (reachable(sp[j], sp[i].p, sp[j].p)) {
                chkMin(G[i][j], F[i][j-1] + sp[j].p - sp[i].p);    // 右侧反向
                chkMin(G[i][j], G[i][j-1] + sp[j].p - sp[j-1].p);  // 右侧顺向
            }
            // 可以记录答案
            if (std::min(i, j) <= std::min(begin, end) && std::max(i, j) >= std::max(begin, end))
                chkMin(ans, F[i][j], G[i][j]);
        }
    }

    printf("%lld\n", check(ans, <0x3f3f3f3f3f3f3f3f, -1));  // 特别地，如果距离为无穷大（不可到达），输出 -1
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/180143060)

---

## 作者：Rnfmabj (赞：1)

## ABC273F

*2277

### 题意

高桥在数轴原点，他想走到坐标 $X$。

数轴上有 $N$ 面墙和 $N$ 把锤子。

- 第 $i$ 面墙位于坐标 $Y_i$，高桥不能穿墙。
- 第 $i$ 把锤子位于坐标 $Z_i$。
  - 高桥路过有锤子的坐标时会捡起锤子。
  - 第 $i$ 把锤子可以把第 $i$ 面墙锤烂，然后高桥就可以过去了。

判断高桥是否可以达成目标，如果可以，找出最小移动距离。

- $1≤N≤1500$
- $1≤|X|,|Y_i|,|Z_i|≤10^9$
- 坐标两两不同

### 题解

注意到 “路过锤子就可以捡起来”，说明只需要知道左右两边最远到过的位置，即可得知当前持有锤子的情况。而随着锤子的增多容易发现左右端点会不断扩展（除非无解），考虑 DP。

将起点、终点、锤子坐标、墙坐标放在一起排序，就可以获得数轴上的分布情况；从起点开始，每次我们都会试图向左或向右扩展一个端点，可以是到达终点、捡锤子，在墙对应的锤子已经被捡起时可以到达墙。

考虑记 $f_{l,r}$ 表示左端点为 $l$，右端点为 $r$ 时到终点还需要走的距离。按理这样可以记录下当前的所有锤子，但是不好确定当前在哪个位置，如果加一维 $p$ 记录当前所在的坐标复杂度就不能接受了。

注意到每次都是向左或向右用脚去扩展端点，并且为了最小化答案我们不会无故反复横跳。所以每次扩展完端点，当前位置一定会在两个端点中的一个上。多开一维 $p \in {0,1}$ 表示当前在 $l$ 还是 $r$ 即可。

转移的话，如果接下来要扩展的点不是墙那么就可以直接走过去；反之需要检查对应的锤子在不在手上，如果在就可以走。

时间复杂度 $O(n^2)$。

### 代码

使用记忆化搜索实现。

```cpp
const ll maxn=1.5e3+5;
struct node{
	ll id,ty,p;
	friend bool operator < (const node &x,const node &y){
		return x.p<y.p;
	}
}a[maxn<<1];
ll k[maxn];
ll n,tot,fin;
ll f[maxn<<1][maxn<<1][2];
ll dfs(ll x,ll y,bool cur){
	if(a[x].ty==0||a[y].ty==0){
		if((a[x].ty==0&&cur==0)||(a[y].ty==0&&cur==1)){
			return 0;
		}
		return dfs(x,y,cur^1)+a[y].p-a[x].p;
	}
	if(~f[x][y][cur])return f[x][y][cur];
	ll res=1ll<<60;
	if(x-1){
		if(a[x-1].ty!=1){
			res=min(res,dfs(x-1,y,0)+a[x].p-a[x-1].p+(cur==0?0:a[y].p-a[x].p));
		}
		else if(k[a[x-1].id]>=a[x].p&&k[a[x-1].id]<=a[y].p){
			res=min(res,dfs(x-1,y,0)+a[x].p-a[x-1].p+(cur==0?0:a[y].p-a[x].p));
		}
	}
	if(y+1<=tot){
		if(a[y+1].ty!=1){
			res=min(res,dfs(x,y+1,1)+a[y+1].p-a[y].p+(cur==1?0:a[y].p-a[x].p));
		}
		else if(k[a[y+1].id]>=a[x].p&&k[a[y+1].id]<=a[y].p){
			res=min(res,dfs(x,y+1,1)+a[y+1].p-a[y].p+(cur==1?0:a[y].p-a[x].p));
		}
	}
	return f[x][y][cur]=res;
}
void solve(){
	n=R,fin=R;
	a[++tot].id=0;
	a[tot].ty=0,a[tot].p=fin;
	a[++tot].id=0;
	a[tot].ty=3,a[tot].p=0;
	for(ll i=1;i<=n;i++){
		a[++tot].id=i;
		a[tot].ty=1;
		a[tot].p=R;
	}
	for(ll i=1;i<=n;i++){
		a[++tot].id=i;
		a[tot].ty=2;
		a[tot].p=R;
		k[i]=a[tot].p;
	}
	sort(a+1,a+1+tot);
	memset(f,-1,sizeof(f));
	ll s=0;
	for(ll i=1;i<=tot;i++){
		if(a[i].ty==3){
			s=i;
			break;
		}
	}
	ll ans=dfs(s,s,0);
	if(ans>=(1ll<<60))puts("-1");
	else we(ans);
	return ;
}
```

---

## 作者：Acerkaio (赞：0)

## 题解：AT_abc273_f [ABC273F] Hammer 2

### 思路

注意到移动的区间是连续的。

考虑典区间 $\text{dp}$ [关路灯](https://www.luogu.com.cn/problem/P1220) 的思路。

我们也设 $dp_{i,j,0/1}$ 表示已任意方式走完区间 $\left [ i,j \right ] $ 并在左端点或右端点。考虑这是个从起始点扩展的过程，故 $dp_{i,j,0}$ 只会从 $dp_{i+1,j,0/1}$ 转移，$dp_{i,j,1}$ 只会从 $dp_{i,j-1,0/1}$ 转移。能不能转移只要再看一下在转移区间里有没有锤子即可，这是容易的。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1510;
int lsh[N<<1],cnt,y[N],z[N],f[N<<1][N<<1][2],ans=1e18,nd[N<<1];
signed main(){
	int n,st=0,to;cin>>n>>to;lsh[++cnt]=to,lsh[++cnt]=0;
	for(int i=1;i<=n;i++)cin>>y[i],lsh[++cnt]=y[i];
	for(int i=1;i<=n;i++)cin>>z[i],lsh[++cnt]=z[i];
	sort(lsh+1,lsh+cnt+1);cnt=unique(lsh+1,lsh+cnt+1)-lsh-1;
	st=lower_bound(lsh+1,lsh+cnt+1,st)-lsh;
	to=lower_bound(lsh+1,lsh+cnt+1,to)-lsh;
	for(int i=1;i<=n;i++){
		y[i]=lower_bound(lsh+1,lsh+cnt+1,y[i])-lsh;
		z[i]=lower_bound(lsh+1,lsh+cnt+1,z[i])-lsh;
		nd[y[i]]=z[i];
	}
	memset(f,0x3f,sizeof f);
	f[st][st][0]=f[st][st][1]=0;
	for(int len=2;len<=cnt;len++){
		for(int i=1,j;j=i+len-1,j<=cnt;i++){
			if(!nd[i]||i+1<=nd[i]&&nd[i]<=j)f[i][j][0]=min({f[i][j][0],f[i+1][j][0]+lsh[i+1]-lsh[i],f[i+1][j][1]+lsh[j]-lsh[i]});
			if(!nd[j]||i<=nd[j]&&nd[j]<=j-1)f[i][j][1]=min({f[i][j][1],f[i][j-1][1]+lsh[j]-lsh[j-1],f[i][j-1][0]+lsh[j]-lsh[i]});
			if(i<=to&&to<=j)ans=min({ans,f[i][j][1],f[i][j][0]});
		}
	}
	if(ans<1e13)cout<<ans<<'\n';
	else cout<<-1<<'\n';
	return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# ABC273F Hammer 题解

## 题目大意

数轴上有 $n$ 个锤子和 $n$ 堵墙，第 $i$ 个锤子位于 $x_i$，第 $i$ 堵墙位于 $y_i$，第 $i$ 个锤子可以对应的敲开第 $i$ 堵墙。以原点为起点，给定终点 $t$，问最少移动多少个单位长度才能走到 $t$。必须拿到对应锤子敲开墙才能走过这堵墙。

## Solve

考虑建图。对于一堵墙 $y_i$，对于所有必须先经过这堵墙才能到达的点 $u$，我们连一条从 $y_i$ 到 $u$ 的有向边，意为限制必须先经过 $y_i$ 才能到 $u$。然后再连一条从 $x_i$ 到 $y_i$ 的有向边，意义同上。处理完之后再从原点向所有点连有向边。

先离散化，再在建出来的图上跑拓扑最长路即可，每条边的边权即为两端点位置之差。

至于为什么是最长路，由于图是在一个数轴上建出来的，比较特殊，所以一个点若受到多个点的约束，那么约束它的点之间一定也有约束关系，不会相互独立，所以更长的路一定包含更短的路的状态。意会一下。

无解的情况显然是从 $s$ 到 $t$ 的路径上有环，即约束 $t$ 的条件无法全被满足，拓排完判断一下 $t$ 的入度是否被消到 $0$ 即可。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=1510,M=3010;
int n,s,t,x[N],y[N],k[M],ind[M],m;
long long f[M];
vector<int>e[M];
inline void topo()
{
	queue<int>q;q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(u==t)    break;
		for(int i:e[u])
		{
			f[i]=max(f[i],f[u]+abs(k[i]-k[u]));
			if(!--ind[i])	q.push(i);
		}
	}
	if(ind[t])	puts("-1");
	else	printf("%lld",f[t]);
}
signed main()
{
	n=read();t=read();m=(n<<1);
	for(int i=1;i<=n;i=-~i)	k[i]=x[i]=read();
	for(int i=1;i<=n;i=-~i)	k[i+n]=y[i]=read();
	k[m+1]=0;k[m+2]=t;
	sort(k+1,k+m+3);
	m=unique(k+1,k+m+3)-k-1;
	for(int i=1;i<=n;i=-~i)
		x[i]=lower_bound(k+1,k+m+1,x[i])-k,
		y[i]=lower_bound(k+1,k+m+1,y[i])-k;
	t=lower_bound(k+1,k+m+1,t)-k;
	s=lower_bound(k+1,k+m+1,0)-k;
	for(int i=1;i<=n;i=-~i)
	{
		e[y[i]].push_back(x[i]);ind[x[i]]=-~ind[x[i]];
		if(x[i]>s)
			for(int j=x[i]+1;j<=m;j=-~j)
				e[x[i]].push_back(j),ind[j]=-~ind[j];
		else
			for(int j=1;j<x[i];j=-~j)
				e[x[i]].push_back(j),ind[j]=-~ind[j];
	}
	for(int i=1;i<=m;i=-~i)
		if(i!=s)	e[s].push_back(i),ind[i]=-~ind[i];
	return topo(),0;
}
```

---

## 作者：Mingrui_Yang (赞：0)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc273_f)

## 题意

数轴上有一些墙和锤子，一把锤子只能敲掉对应的一面墙，最开始在原点，给定终点，求最小步数。

## Solution

`x` 是终点坐标，`y[]` 表示墙的坐标，`z[]` 表示锤子的坐标。

首先，坐标较大但 $N$ 较小，需要离散化。   
离散化后 `y[]` 用来存以前的 `y[]` 在离散化数组中的位置，`z[]` 用来存以前的 `z[]` 在离散化数组中的位置，`x` 用来存终点在离散化数组中的位置，在定义 `s` 用来存原点在离散化数组中的位置。

定义 $f_{i, j, 0/1}$ 表示在区间 $\left[ i, j \right]$ 的左端点或右端点的最小步数。    
通过扩大区间的方式来进行转移（通过 `f[l][r][0/1]` 转移 `f[l - 1][r][0]` 和 `f[l][r + 1][1]`），扩大过程中，如果遇到墙（即 $l - 1$ 或 $r + 1$ 的位置存在墙），则需要查看区间 $\left[ i, j \right]$ 是否存在这面墙的钥匙（定义 `isy[]` 数组存 `y[]` 对应钥匙的坐标，在离散化后更新 `y[]` 时，顺便处理 `isy[]`）。     

答案就是包含终点的区间中的最小值 。

## CODE

```cpp
#include <bits/stdc++.h>

#define int long long 

using namespace std;

const int N = 1510, M = N << 1; // 离散化需要双倍 

int n, x;
int y[N], z[N];
int m, alls[M]; // 离散化 
int f[M][M][2]; // f[i][j][1/0]  在区间 [i,j] 的左端或右端的最小答案 
int isy[M]; // 存储 y[] 对应的钥匙，为 0 则说明当前位置不是墙 

signed main() {
	cin >> n >> x;
	for (int i = 1; i <= n; i ++ ) cin >> y[i], alls[ ++ m] = y[i];
	for (int i = 1; i <= n; i ++ ) cin >> z[i], alls[ ++ m] = z[i];
	alls[ ++ m] = 0, alls[ ++ m] = x;
	sort(alls + 1, alls + m + 1);
	m = unique(alls + 1, alls + m + 1) - alls - 1;
	for (int i = 1; i <= n; i ++ ) z[i] = lower_bound(alls + 1, alls + m + 1, z[i]) - alls;
	for (int i = 1; i <= n; i ++ ) y[i] = lower_bound(alls + 1, alls + m + 1, y[i]) - alls, isy[y[i]] = i;
	int s = lower_bound(alls + 1, alls + m + 1, 0) - alls;
	x = lower_bound(alls + 1, alls + m + 1, x) - alls;
	
	memset(f, 0x3f, sizeof f); // 初始化为正无穷 
	f[s][s][1] = f[s][s][0] = 0; // 起点 
	for (int len = 1; len <= m; len ++ )
		for (int l = 1; l + len - 1 <= m; l ++ ) {
			int r = l + len - 1;
			int p = isy[l - 1];
			if (!p || (l <= z[p] && z[p] <= r)) // 为 0 则说明当前位置不是墙 ，是墙一定需要钥匙 
				f[l - 1][r][0] = min(f[l - 1][r][0], f[l][r][0] + alls[l] - alls[l - 1]),
				f[l - 1][r][0] = min(f[l - 1][r][0], f[l][r][1] + alls[r] - alls[l - 1]);
			p = isy[r + 1];
			if (!p || (l <= z[p] && z[p] <= r)) // 为 0 则说明当前位置不是墙 ，是墙一定需要钥匙  
				f[l][r + 1][1] = min(f[l][r + 1][1], f[l][r][0] + alls[r + 1] - alls[l]),
				f[l][r + 1][1] = min(f[l][r + 1][1], f[l][r][1] + alls[r + 1] - alls[r]);
		}
	
	int ans = LLONG_MAX; // 在包含终点的区间中找到最小值 
	for (int i = 1; i <= x; i ++ )
		for (int j = x; j <= m; j ++ )
			ans = min(ans, min(f[i][j][0], f[i][j][1]));
			
	if (ans >= 0x3f3f3f3f3f3f3f3f) puts("-1"); // 答案与初始化相同，这说明没有正确的答案 
	else cout << ans << endl;
	
	return 0; 
}
```

~~bye~~~~

---

