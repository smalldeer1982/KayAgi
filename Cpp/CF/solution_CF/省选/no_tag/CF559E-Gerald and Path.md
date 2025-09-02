# Gerald and Path

## 题目描述

The main walking trail in Geraldion is absolutely straight, and it passes strictly from the north to the south, it is so long that no one has ever reached its ends in either of the two directions. The Geraldionians love to walk on this path at any time, so the mayor of the city asked the Herald to illuminate this path with a few spotlights. The spotlights have already been delivered to certain places and Gerald will not be able to move them. Each spotlight illuminates a specific segment of the path of the given length, one end of the segment is the location of the spotlight, and it can be directed so that it covers the segment to the south or to the north of spotlight.

The trail contains a monument to the mayor of the island, and although you can walk in either directions from the monument, no spotlight is south of the monument.

You are given the positions of the spotlights and their power. Help Gerald direct all the spotlights so that the total length of the illuminated part of the path is as much as possible.

## 样例 #1

### 输入

```
3
1 1
2 2
3 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
1 2
3 3
4 3
6 2
```

### 输出

```
9
```

# 题解

## 作者：xht (赞：25)

> [CF559E Gerald and Path](https://codeforc.es/contest/559/problem/E)

## 题意

- 有 $n$ 条线段。
- 每条线段给定其中一端的位置及长度。
- 求所有线段覆盖的最大长度。
- $n \le 100$。

## 题解

首先对一端位置排序。

考虑 dp，设 $f_{i,j,p}$ 表示考虑前 $i$ 条线段，最靠右的线段是第 $j$ 条，其方向为 $p$（$0$ 左 $1$ 右）。

考虑如何转移，从小到大枚举 $i$ 后面的线段以及它的方向，同时维护枚举过的线段中最靠右的线段以及它的方向。

设线段 $j$ 在 $p$ 方向的右端点是 $o$；此时枚举到线段 $k$，它的方向为 $q$，长度为 $l$，右端点是 $t$；枚举过的线段中最靠右的线段是 $x$，它的方向为 $y$，右端点是 $z$。

那么有转移 $f_{k,x,y} \leftarrow f_{i,j,p} + \min(l, t - o) + z - t$。

时间复杂度 $\mathcal O(n^3)$。

## 代码

```cpp
const int N = 107;
int n, ans, f[N][N][2];
pi a[N];

int main() {
	rd(n);
	for (int i = 1; i <= n; i++) rd(a[i].fi), rd(a[i].se);
	sort(a + 1, a + n + 1);
	a[0].fi = -1e9;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= i; j++)
			for (int p = 0; p < 2; p++) {
				ans = max(ans, f[i][j][p]);
				int o = a[j].fi + p * a[j].se, mx = -1e9, x, y;
				for (int k = i + 1; k <= n; k++)
					for (int q = 0; q < 2; q++) {
						int t = a[k].fi + q * a[k].se;
						if (t > mx) mx = t, x = k, y = q;
						f[k][x][y] = max(f[k][x][y], f[i][j][p] + min(a[k].se, t - o) + mx - t);
					}
			}
	print(ans);
	return 0;
}
```

---

## 作者：灵梦 (赞：20)

参考了 xht 的做法，画了几张图，可能会好理解一些。

首先对所有线段按给出的端点位置排序，然后考虑 DP。令状态 $f(i,j,p)$ 表示处理了前 $i$ 条线段，它们覆盖的最右边的一段由线段 $j$ 贡献，且 $j$ 的方向为 $p$（左 $0$ 右 $1$）。如果正常的考虑加入一条线段转移，即由 $i$ 转移到 $i+1$，应该考虑线段 $i+1$ 的贡献。但这个贡献是不好处理的，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/o3p7w7jq.png)

黑色的表示已经计入贡献的线段，红色的表示新加入的线段。发现黑色中间的空隙是算不了的，所以这样会产生后效性。但是同时我们发现第二段黑色线段是没有任何用的，我们扔掉这种「没有用的线段」，加入时就只需要考虑 $j$ 右端点后面的部分了。所以，我们从 $i$ 转移到 $k\in[i+1,n]$ 的所有线段，并不计线段 $i+1\sim k-1$ 的贡献。但是注意，还是需要考虑一种贡献：

![](https://cdn.luogu.com.cn/upload/image_hosting/6op82xst.png)

这里紫色的线段 $x$ 超过了 $k$ 的右端点，并成为最靠右的线段。假设 $x$ 的方向为 $y$，那么 $f(i,j,p)$ 应该转移到 $f(k,x,y)$，还要加上 $k$ 后面一段的贡献。$x$ 应该从 $i+1\sim k-1$ 中取右端点的最大值，而从小到大顺次枚举 $k$ 时可以直接维护。所以转移的复杂度是 $O(n)$，总复杂度就是 $O(n^3)$。

---

## 作者：mrsrz (赞：15)

[可能更好的体验](https://mrsrz.github.io/2019/12/07/CF559E/)

为了避免线段重合的问题，我们对于线段 $[l,r]$，其前缀 $[l,l],[l,l+1],[l,l+2],\cdots,[l,r-1]$ 也可以产生贡献。即若选择这条线段，则 $l\sim r$ 每个位置都要更新贡献，这里的长度为实际算上去的长度而非线段原来的长度。

离散化，对线段按照端点位置排序，令 $f_{i,j}$ 表示前 $i$ 条线段，最右端覆盖到位置 $j$ 时覆盖的最长长度。

考虑这个 $[l,p],[p,r]$ 二选一的两种方法：

向右放（选择 $[p,r]$）。这种情况与之前不会产生冲突，直接转移。$f_{i,j}=\max\{f_{i-1,p}+\mathrm{dist}(p,j)\},j\in[p,r]$。

向左放（选择 $[l,p]$）。这种情况就会产生一个问题：它左边可能存在一条或多条往右的线段，使得右端点在更右边。

我们直接枚举 $k$ 并令 $k\sim i-1$ 这些线段都向右放。令 $R$ 表示右端点最右的位置。则 $f_{i,j}=\max\{f_{k-1,l}+\mathrm{dist}(l,R)\}$。

正确性：如果中间有线段往左放的，那我们这里计算的时候，那个往左放的线段只算进了它的一个前缀的贡献，其冲突部分算在后面这条线段。因此贡献是对的。

直接枚举的复杂度为 $O(n^3)$。考虑 $k$ 从大到小枚举，更新 $R$ 的值。令 $g[R]$ 表示右端点为 $R$ 时的最大答案。

我们直接算出 $g[R]$ 后，还要对其做一遍后缀的处理。就是相当于取前缀计算贡献。具体可以见代码里的处理。

最后每次还要对 $f_i$ 求前缀最大值。

时空复杂度 $O(n^2)$。

## Code：

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>vec;
const int N=105;
struct lne{
	int l,r,p;
	inline bool operator<(const lne&rhs)const{return p<rhs.p;}
}d[N];
int n,f[N][N*3],g[N*3];
inline void find(int&x){x=lower_bound(vec.begin(),vec.end(),x)-vec.begin();}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	vec.push_back(-1e9);
	for(int i=1;i<=n;++i){
		int a,l;
		cin>>a>>l;
		d[i]=(lne){a-l,a+l,a};
		vec.push_back(d[i].l);
		vec.push_back(d[i].r);
		vec.push_back(d[i].p);
	}
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for(int i=1;i<=n;++i)find(d[i].l),find(d[i].r),find(d[i].p);
	const int m=vec.size()-1;
	sort(d+1,d+n+1);
	for(int i=1;i<=n;++i){
		memcpy(f[i],f[i-1],sizeof*f);
		int L=d[i].l,R=d[i].r,p=d[i].p;
		//left
		memset(g,0,sizeof g);
		int nr=p;
		g[nr]=f[i-1][L]+vec[nr]-vec[L];
		for(int j=i-1;j;--j){
			nr=max(nr,d[j].r);
			g[nr]=max(g[nr],f[j-1][L]+vec[nr]-vec[L]);
		}
		for(int j=m;j>=L;--j){
			f[i][j]=max(f[i][j],g[j]);
			g[j-1]=max(g[j-1],g[j]-vec[j]+vec[j-1]);
		}
		//right
		for(int j=p;j<=R;++j)f[i][j]=max(f[i][j],f[i-1][p]+vec[j]-vec[p]);
		for(int j=1;j<=m;++j)f[i][j]=max(f[i][j],f[i][j-1]);
	}
	cout<<f[n][m]<<'\n';
	return 0;
}
```


---

## 作者：1kri (赞：11)

提供一种不同的思路。

首先发现值域很大，但有用的点数不多。那么可以离散化，只将所有的 $a_i$、$a_i-b_i$、$a_i+b_i$ 存下。

下面使用的所有位置下标均为离散化后的下标。

考虑最终点亮的情况，将所有相交的线段并起来称为同一个连通块，那么最终局面就是若干个不交连通块的并。我们在 $dp$ 时枚举每个连通块，算贡献即可。

具体地，我们记 $g_{l,r}$ 表示只使用位置在 $[l,r]$ 之间的灯，能否将 $[l,r]$ 这一段完全覆盖，再记 $f_i$ 表示考虑到位置 $i$ 的最长长度。

当我们求出所有的 $g_{l,r}$ 后，就容易得到 $f_i=\max \{f_{j-1}+s_i-s_j\}$ ，其中 $j \in [1,i-1]$ 且 $g_{j,i}$ 为真，$s_x$ 表示离散化数组中第 $x$ 个位置的值。

接下来考虑如何求所有的 $g_{l,r}$ 。

有一道很类似的题目：[CF1476F](https://codeforces.ml/problemset/problem/1476/F) 。

将所有灯按位置排序，对于每个 $l$ ，我们将所有位置 $\geq l$ 的灯拉出来 $dp$ 。

$dp$ 时考虑求出前 $i$ 盏灯能覆盖的最长前缀长度，记 $dp_i$ 表示前 $i$ 盏灯能照亮的最长前缀长度（从 $l$ 开始，忽略 $l$ 前的长度）。每盏灯有两种决策：向左照或向右照。

一盏灯能向右照，当且仅当 $dp_{i-1} \geq pos_i$ 。

一盏灯向左照，则 $dp_i=\max r_j$ ，其中需要满足 $dp_j \geq l_j$ 。$l_j$ 和 $r_j$ 分别表示第 $j$ 盏灯向左或向右能照到的位置。

这个 $dp$ 可能还有一些细节，但对着样例不难调试。

对于每个 $l$ ，求出 $dp$ 数组后就容易得到 $g_l$ 数组了。

这样这道题目就做完了，时间复杂度 $O(n^3)$ 。


---

## 作者：MLEAutoMaton (赞：9)

## CF559E 【Gerald and Path】

这个题的$dp$很有意思,我也不知道怎么个有意思法.

考虑设$dp_{i,j}$表示前$i$个喷洒点,最右边的点是$j$,那么怎么转移?

1. 这个向左边喷洒,考虑每一条线段可以拆成一个前缀,所以直接枚举前面到哪个点断开即可.

2. 这个向右边喷洒,这个有些复杂.

  - 对于当前这个转移,如果不会对后面产生影响(即后面的不选这个或者是向右选),直接转移(像向左喷洒一样).
  - 当前这个转移点是一个端点且向左转移,那你就整体考虑这两个线段带来的贡献,然后上一个转移从这个线段的左端点开始,经过当前$i$线段的断点的转移,用一个前缀最大值维护即可.

总复杂度为$\Theta(n^2)$的.

```cpp
/*
  mail: mleautomaton@foxmail.com
  author: MLEAutoMaton
  This Code is made by MLEAutoMaton
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<iostream>
using namespace std;
#define ll long long
#define REP(a,b,c) for(int a=b;a<=c;a++)
#define re register
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
inline int gi(){
	int f=1,sum=0;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int N=100010;
int n,o[N],tot,id[N];
struct node{
	int x,l,r;
	bool operator<(const node &rhs)const{return x<rhs.x;}
}p[N];
int f[3010][9010];
int main(){
#ifndef ONLINE_JUDGE
	freopen("kill.in","r",stdin);
	freopen("kill.out","w",stdout);
#endif
	n=gi();
	for(int i=1;i<=n;i++){
		p[i].x=gi(),p[i].l=gi(),p[i].r=gi();
		p[i].l=p[i].x-p[i].l;p[i].r=p[i].x+p[i].r;
		o[++tot]=p[i].x,o[++tot]=p[i].l,o[++tot]=p[i].r;
	}
	sort(p+1,p+n+1);sort(o+1,o+tot+1);tot=unique(o+1,o+tot+1)-o-1;
	for(int i=1;i<=n;i++){
		p[i].x=lower_bound(o+1,o+tot+1,p[i].x)-o;
		p[i].l=lower_bound(o+1,o+tot+1,p[i].l)-o;
		p[i].r=lower_bound(o+1,o+tot+1,p[i].r)-o;
		id[p[i].x]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=tot;j++)f[i][j]=f[i-1][j];
		for(int j=p[i].l+1;j<=p[i].x;j++)f[i][j]=max(f[i][j],f[i][j-1]+o[j]-o[j-1]);
		int mx=f[i-1][p[i].x];
		for(int j=p[i].x+1;j<=p[i].r;j++){
			f[i][j]=max(f[i][j],mx+o[j]-o[p[i].x]);
			if(id[j] && p[id[j]].l<p[i].x)
				mx=max(mx,f[i-1][p[id[j]].l]+o[p[i].x]-o[p[id[j]].l]);
		}
		for(int j=1;j<=tot;j++)f[i][j]=max(f[i][j],f[i][j-1]);
	}
	printf("%d\n",f[n][tot]);
	return 0;
}
```





---

## 作者：w9095 (赞：4)

[CF559E Gerald and Path](https://www.luogu.com.cn/problem/CF559E)

很困难的 DP 题，状态不是很好想。对于这种线段覆盖类题目，显然先覆盖哪个线段没有影响，我们可以通过按照端点位置升序排序后按照顺序考虑，这样可能会有一些额外性质。

之后，考虑转移时需要什么东西来刻画一个状态的轮廓。显然我们需要知道现在是第几条线段，并且计算贡献需要知道覆盖右端点最远的线段以及其方向。如果这样设计状态，非最远线段的影响就会在加入最远线段时被计算，是正确的。

设状态 $f_{i,j,k}$ 表示考虑到第 $i$ 条线段，右端点最远的线段为 $j$，方向为 $k$。考虑刷表，枚举 $p$ 为考虑到的线段，$q$ 为其方向。我们可以在从小到大枚举 $p$ 的时候顺便记录右端点最大的值 $x$ 与此时的方向 $y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4fabzq76.png)

假设方向全都是向右，我们可以通过上图辅助理解。我们发现，增加的贡献可以分为两段。一段是 $l+1\sim r$，另一段是 $r+1\sim mx$。在此图中，第一段贡献为 $r-l$，第二段贡献是 $mx-r$，把这些加到转移时的贡献中。事实上，如果方向不是向右，也是一样的，

![](https://cdn.luogu.com.cn/upload/image_hosting/gz162g3u.png)

假设方向全都是向右，注意到还有这种情况。此时第二段贡献还是 $mx-r$，但是第一段贡献需要减去 $l-r$。注意到这等价于加上 $r-l$，所以维持原转移不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/adpyucbw.png)

假设方向全都是向右，注意到还有这种情况。第二段贡献不变，但处理第一段时，如果 $l$ 和 $r$ 中间有空隙，那么 $r-l$ 算出来的贡献就过大了，应该只有 $l[p]$。此时我们只需要把 $r-l$ 和 $l[p]$ 取较小值。

综上所述，状态转移方程为如下。

$$f_{p,x,y}=\max\{f_{p,x,y},f_{i,j,k}+\min\{l[p],r-l\}+mx-r\}$$

时间复杂度 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct val
{
	long long a,l;
}a[200];
long long n,f[200][200][2],ans=0;
bool cmp(struct val a,struct val b)
{
	return a.a<b.a;
}

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].a,&a[i].l);
	sort(a+1,a+n+1,cmp);
	a[0].a=-1e18;
	for(int i=0;i<=n;i++)
	    for(int j=0;j<=i;j++)
	        for(int k=0;k<2;k++)
	            {
	            	long long l=a[j].a+k*a[j].l,mx=-1e18,x=0,y=0;
	            	for(int p=i+1;p<=n;p++)
	            	    for(int q=0;q<2;q++)
	            	        {
	            	        	long long r=a[p].a+q*a[p].l;
	            	        	if(r>mx)mx=r,x=p,y=q;
	            	        	f[p][x][y]=max(f[p][x][y],f[i][j][k]+min(a[p].l,r-l)+mx-r);
							}
				}
	for(int i=0;i<=n;i++)
	    for(int j=0;j<=i;j++)
	        for(int k=0;k<2;k++)
	            ans=max(ans,f[i][j][k]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：tzc_wk (赞：4)

[题面传送门](https://codeforces.ml/contest/559/problem/E)

真·难度 *3000 的 D1E hb 跟我们说“做不出来不太应该”。

首先我们将所有线段按 $a_i$ 从小到大排序，一个很显然的想法是 $dp_{i,j,d}$ 表示我们已经钦定了前 $i$ 个线段的方向，其中右端点最靠右的线段为 $j$，它的方向为 $d$ 所覆盖的最大长度是多少。

接下来考虑转移，考虑从 $i$ 转移到 $i+1$，那么线段 $i+1$ 覆盖 $j$ 与 $i+1$ 中间的部分的长度就是 $\min(\text{线段}\ i+1\ \text{的右端点}-\text{线段}\ j\ \text{的右端点},\text{线段}\ i+1\ \text{的长度})$。

但是我们这样计算线段 $i+1$ 的贡献是错误的，因为可能会出现以下的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/236me23g.png)

这种情况下贡献是无法直接计算的。不过我们注意到在这种情况下线段 $j$ 被完全包含在线段 $i$ 中，也就是说线段 $j$ 的贡献为 $0$。于是我们考虑另一种转移方式：枚举下一个被计入贡献的线段 $k$，直接忽略线段 $[i+1,k-1]$ 的贡献。然后按照上面的方式计算即可——虽然我们知道可能 $[i+1,k-1]$ 中的线段也会产生贡献，也就是说我们算出来的贡献不一定是真正的贡献。但是我们清楚，我们忽略了这些贡献，所得到的答案一定没有标准来得更优，并且最优方案一定会被我们考虑到，所以我们这样计算贡献也是正确的。

回到本题来，我们这样计算其实还会忽略一种贡献，那就是在 $[i+1,k-1]$ 中右端点最靠右的线段 $j$ 的右端点超过了 $k$ 的右端点，那这样还会产生 $\text{线段}\ j\ \text{的右端点}-\text{线段}\ k\ \text{的右端点}$ 的贡献，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/yanny09x.png)

也就是说，对于 $[i+1,k-1]$ 的线段，我们贪心地钦定每个线段都朝右（我们假设这些线段朝左都没有贡献了），然后看是否存在某条线段右端点超过 $k$。

具体来说，我们枚举 $k\in [i+1,n]$，以及 $k$ 的方向 $d_k$，然后在枚举的过程中，记录下右端点最大的线段编号 $r$，方向 $d_r$。然后 $\mathcal O(1)$ 从 $dp_{i,j,d}$ 转移到 $dp_{k,r,d_r}$，那么它产生的贡献就是 $\text{线段}\ r\ \text{的右端点}-\text{线段}\ k\ \text{的右端点}+\min(\text{线段}\ k\ \text{的右端点}-\text{线段}\ j\ \text{的右端点},\text{线段}\ k\ \text{的长度})$。

时间复杂度 $\mathcal O(n^3)$

[代码戳这儿](https://codeforces.ml/contest/559/submission/106921926)

---

## 作者：关怀他人 (赞：4)

### CF 559E
#### Solution
首先对坐标离散化，然后对所有灯按照放置的位置排序，考虑依次加入线段计算贡献，设$f[i][j]$表示考虑到第$i$个点，已经覆盖到最右端点为$j$的覆盖长度最大值（并不要求$[i,j]$都被覆盖）。

初始时$f[i][j]=f[i - 1][j]$，设$p,l,r$分别为灯离散化后的坐标，往左照时的端点和往右照时的端点。考虑每次添加一个灯，有两种转移
1. 向右照，直接转移即可，$f[i][j]=f[i-1][p]+dis(p,j)$，其中$dis$表示原坐标的差
2. 向左照，此时便有可能重复计算贡献，考虑如何处理这种情况，可以强行钦定一个$k$让$[k,i-1]$的所有灯全部向右照，所有这样便可以确定这些灯的最右端点$R=max_{j=k}^{i-1}r_j$，于是便有转移$f[i][R] = f[k-1][l] + dis(l,R)$
考虑这样做的正确性，因为如果在$[k,i-1]$中有线段向左，那么它的贡献早已在当前的$i$向右时就计算过了。

直接dp的复杂度是$\mathcal O(n^3)$的，考虑优化，不难发现如果倒序枚举$k$，则$R$一定是单调不降的，设$g[R]$为对于当前的$i$，$f[k-1][l]+dis(l,R)$的最大值，对其做一遍后缀最大值更新答案即可。

时间复杂度$\mathcal O(n^2)$
#### Code
```cpp
int n,tot;
int b[MAXM],f[MAXN][MAXM],g[MAXM];

struct Seg{
    int p,l,r;
} a[MAXN];

bool cmp(const Seg &x,const Seg &y){
    return x.p < y.p;
}

int main(){
    scanf("%d",&n);
    for(int i = 1,len;i <= n;i++){
        scanf("%d%d",&a[i].p,&len);
        a[i].l = a[i].p - len; a[i].r = a[i].p + len;
        b[++tot] = a[i].p; b[++tot] = a[i].l; b[++tot] = a[i].r;
    }
    sort(a + 1,a + 1 + n,cmp);
    sort(b + 1,b + 1 + tot);
    tot = unique(b + 1,b + 1 + tot) - b - 1;
    for(int i = 1;i <= n;i++){
        a[i].l = lower_bound(b + 1,b + 1 + tot,a[i].l) - b;
        a[i].p = lower_bound(b + 1,b + 1 + tot,a[i].p) - b;
        a[i].r = lower_bound(b + 1,b + 1 + tot,a[i].r) - b;
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= tot;j++) g[j] = 0;
        for(int j = 1;j <= tot;j++) f[i][j] = f[i - 1][j];
        int p = a[i].p,l = a[i].l,r = a[i].r;
        int R = p;
        g[R] = f[i - 1][l] + b[R] - b[l];
        for(int j = i - 1;j >= 1;j--){
            checkMax(R,a[j].r);
            checkMax(g[R],f[j - 1][l] + b[R] - b[l]);
        }
        for(int j = tot;j >= l;j--){
            checkMax(f[i][j],g[j]);
            checkMax(g[j - 1],g[j] - (b[j] - b[j - 1]));
        }
        for(int j = p;j <= r;j++)
            checkMax(f[i][j],f[i - 1][p] + b[j] - b[p]);
        for(int j = 1;j <= tot;j++)
            checkMax(f[i][j],f[i][j - 1]);
    }
    printf("%d\n",f[n][tot]);
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：3)

**sol of CF559E**

考场上写了个裸的没优化的 $O(n ^ 3)$ 还写挂了！！！但是多亏了 data 非常水水了很多分！！！

考虑一个很显然的性质：按 $a$ 排序，最后覆盖的所以区间将会以很多个**联通连续段**的形式出现。这是因为如果一个区间如果以某种形式被拓展出来，中间的所有 $a$ 都会被覆盖。

先将端点与所有 $a$ 离散化，称它们为有效端点。故我们尝试用线性 dp 来做，甚至你发现这个连续段 dp 也不需要枚举是否需要 split/merge 当前端点进入上一个连续段，只需要每次转移时枚举这个连续段就好了，这样外层 dp 是 $O(n ^ 2)$ 的。

还是把 dp 式子裂出来，我们设 $dp_i$ 表示前 $i$ 个有效端点决策后的最长覆盖区间长度，则 $dp_{i} = \max_{j = 1} ^ {i - 1} (dp_j + len_{j + 1,i}) \times [c(j+1,i) == 1]$。其中 $c(l,r)$ 表示只靠 $a$ 处于第 $l$ 个有效端点到第 $r$ 个有效端点中的所有监控，是否能将这个区间完全覆盖。

考虑处于这个 $c(l,r)$，我们发现这玩意儿很像 CF1476F！那考虑做 $n$ 次该题就行了。

具体地，我们假设 $f_{l,r}$ 表示区间 $[l,r]$ 中的监控最远可以覆盖的以 $l$ 为开头意义下的前缀长度。那么 $c(l,r) = [f_{l,r} \geq r]$。

这样 dp 的正确性既可以从前缀保留的角度理解，也可以从任意一个端点要么被左边的监控覆盖，要么被右边的监控覆盖这个角度理解，可以参考我关于此题的[题解](https://www.luogu.com.cn/blog/eulogized/solution-cf1476f)。

那么这道题照样画葫芦：

- $r$ 处没有监控；则 $f_{l,r} = f_{l,r - 1}$；

- 否则先考虑向右照；显然 $f_{l,r} = \max(f_{l,r-1},R_r)$，即向右找没用以及向右照是当前的最优右端点；

- 考虑向左照；显然找到最小的一个 $j$ 满足 $L_r \leq f_{l,j}$，维护 $[j + 1 , r - 1]$ 向右照贡献的最远位置即可，采用二分与 st 表维护两个信息。

这样就做到了时间 $O(n ^ 2 \log n)$，常数小的离谱。

一个可以继续优化的想法，发现这个 $L$ 其实值域很小，所以我们直接在每次做一个 $l$ 固定时的 $f$ 状态时用 $O(n)$ 的时间复杂度维护出来所有二分值对应的位置，平摊了时间复杂度使其降为 $O(n ^ 2)$，但是由于确实 $n$ 太小，没啥明显优势。

```cpp
/*
考虑固定 l 的转移。
若 r 没有，f_r = f_{r - 1}
否则：
{
	考虑 Lanterns 的转移。
	向右照，若 f_{r - 1} > r 那么 f_r = max(f_{r - 1},R_r) 否则向右照一定不合法，直接取 f_r = f_{r - 1}
	向左照，在前面找一个状态转移就好了。 
}
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 6e3 + 5 , M = 1e4 + 5 , Inf = 4e8;
int n,m,dp[Len * 3],lsh[Len * 3],f[Len][Len],cnt;
struct Node
{
	int a,l,L,R;
	Node(){a = l = L = R = 0;}
	Node(int A,int Ll,int LL,int RR){a = A , l = Ll , L = LL , R = RR;}
}bot[Len]; 
bool cmp(Node x,Node y){return x.a < y.a;}
int L[M],R[M],vis[M];
int st[25][M],lg[M];
void init()
{
	for(int i = 2 ; i <= cnt ; i ++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1 ; i <= cnt ; i ++) st[0][i] = R[i];
	for(int i = 1 ; (1 << i) <= cnt ; i ++)
		for(int j = 1 ; j + (1 << i) - 1 <= cnt ; j ++) st[i][j] = max(st[i - 1][j] , st[i - 1][j + (1 << (i - 1))]);
}
inline int Mx(int l,int r)
{
	if(l > r) return -1;
	int k = lg[r - l + 1];
	return max(st[k][l] , st[k][r - (1 << k) + 1]);
}
int main()
{
	//freopen("monitor.in","r",stdin);
	//freopen("monitor.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d %d",&bot[i].a,&bot[i].l);
		bot[i].L = bot[i].a - bot[i].l;
		bot[i].R = bot[i].a + bot[i].l;
		lsh[++ cnt] = bot[i].a - bot[i].l;
		lsh[++ cnt] = bot[i].a + bot[i].l;
		lsh[++ cnt] = bot[i].a;
	}
	sort(lsh + 1 , lsh + 1 + cnt);
	cnt = unique(lsh + 1 , lsh + 1 + cnt) - lsh - 1;
	sort(bot + 1 , bot + 1 + n , cmp);
	for(int i = 1 ; i <= n ; i ++) 
	{
		bot[i].L = lower_bound(lsh + 1 , lsh + 1 + cnt , bot[i].L) - lsh;
		bot[i].R = lower_bound(lsh + 1 , lsh + 1 + cnt , bot[i].R) - lsh;
		bot[i].a = lower_bound(lsh + 1 , lsh + 1 + cnt , bot[i].a) - lsh;
		L[bot[i].a] = bot[i].L , R[bot[i].a] = bot[i].R , vis[bot[i].a] = 1;
	}
	init();
	for(int i = 1 ; i <= cnt ; i ++) 
	{
		if(vis[i]) f[i][i] = R[i];
		else f[i][i] = i;	
		for(int j = i + 1 ; j <= cnt ; j ++) 
		{
			if(!vis[j]) f[i][j] = f[i][j - 1];
			else
			{
				if(f[i][j - 1] >= j) f[i][j] = max(f[i][j - 1] , R[j]);
				else f[i][j] = f[i][j - 1];
				int mx = j;
				int ll = i , rr = j - 1 , anss = -1;
				while(ll <= rr)
				{
					int mid = (ll + rr) >> 1;
					if(L[j] <= f[i][mid]) anss = mid , rr = mid - 1;
					else ll = mid + 1;
				}
				if(anss != -1 && anss + 1 <= j - 1) f[i][j] = max(f[i][j] , Mx(anss + 1 , j - 1));
				if(L[j] <= f[i][j - 1]) f[i][j] = max(f[i][j] , j);
			}
			//printf("%d %d %d %d %d\n",i,j,f[i][j],L[j],R[j]);
		}
	}
	int as = 0;dp[0] = 0;
	for(int i = 1 ; i <= cnt ; i ++)
	{
		for(int j = 0 ; j < i ; j ++) if(f[j + 1][i] >= i) dp[i] = max(dp[i] , dp[j] + lsh[i] - lsh[j + 1]);
		as = max(as , dp[i]);
	}
	printf("%d\n",as);
	return 0;	
} 
```

---

## 作者：Sky_Maths (赞：2)

Update on 2024.10.7 错误有点多

# 前言
[CF559E Gerald and Path](https://www.luogu.com.cn/problem/CF559E)

从 $O(n^3)$ 讲到 $O(n^2)$。

# $O(n^3)$ 做法
首先有用的位置不会超过 $3n$ 个（原位置，向左，向右），想到将 $3n$ 个位置离散化后 DP。

考虑最终状态，发现显然是一段段的（不然呢）。

把所有线段按左端点排序。

## 约定

设 $f_{i,j}$ 为当前已经处理了前 $i$ 条线段，且只考虑 $(-\infty,j]$ 上的覆盖的最大覆盖长度。

$l_i,r_i,p_i$ 分别代表第 $i$ 条线段 向左/向右/原点 的位置。

$x$ 是离散化后的点值所对应的实际点值，$dis(i,j) = |x_{i} - x_{j}|$。

## 转移

考虑如何转移，分类讨论第 $i$ 条线段向左/向右。

### 向右

$f_{i,j} = f_{i-1,p_i} + dis(p_i, \min(j, r_i))$

### 向左

发现存在特殊情况，即左边的线段往右而右边的线段往左。

那我们考虑要求 $k\sim i - 1$ 间的线段全部往右，而 $i$ 往左，当 $k$ 取遍 $1\sim i - 1$ 时，发现已经包含了所有情况。

令 $R = \max\limits_{j = k}^{i - 1}r_j$。

枚举 $k$，此时 $f_{i,j}  = f_{k - 1, l_i} + dis(l_i, \min(j,R))$。

### 特殊
最后再让每个 $f_{i,j}$ 向 $f_{i,j-1},f_{i-1,j}$ 取 $\max$ 即可。

## 代码
```cpp
rep(i, 1, n) {
	rep(j, 1, m) {
		cmax(f[i][j], f[i - 1][p[i]] + dis(p[i], min(j, r[i])));
		int R = p[i];
		per(k, i, 1) {
			if(k != i) cmax(R, r[k]);
			cmax(f[i][j], f[k - 1][l[i]] + dis(l[i], min(R, j)));
		}
		cmax(f[i][j], f[i - 1][j]);
	}
}
```

# $O(n^2)$ 做法

考虑对上面的代码重构。

```cpp
rep(i, 1, n) {
	rep(j, 1, m) {
		cmax(f[i][j], f[i - 1][p[i]] + dis(p[i], min(j, r[i])));
		cmax(f[i][j], f[i - 1][j]);
   }
	rep(j, 1, m) {
		int R = p[i];
		per(k, i, 1) {
			if(k != i) cmax(R, r[k]);
			cmax(f[i][j], f[k - 1][l[i]] + dis(l[i], min(R, j)));
		}
	}
}
```

再将第二个 $n^2$ 循环内外翻转。

```cpp
int R = p[i];
per(k, i, 1) {
	if(k != i) cmax(R, r[k]);
	rep(j, 1, m) {
		cmax(f[i][j], f[k - 1][l[i]] + dis(l[i], min(R, j)));
	}
}

```

发现可以对 $\min(R,j)$ 进行类似分类讨论？

因为发现对于每个 $j< R$，$f_{i,j} = f_{i,R} - dis(j, R)=f_{i,j + 1}-dis(j,j + 1)$。

所以只需要对于每个 $R$ 修改 $f_{i,R}$，最后统一取 $\max$ 即可（不是真正取 $\max$），然后就成了 $O(n)$ 的。

所以总复杂度变为 $O(n^2)$。

## 代码

```cpp
ci N = 1009;
int n, m;
int x[N], l[N], r[N], p[N], F[N];
int f[N][N];
pii a[N];
int xtoi(int xvar) {
	return lower_bound(x + 1, x + m + 1, xvar) - x;
}
int dis(int li, int ri) {
	return x[ri] - x[li];
}
int main() {
	freopen("a.in", "r", stdin);
	rd(n);
	rep(i, 1, n) {
		rd(a[i].fi);
		rd(a[i].se);
	}
	sort(a + 1, a + n + 1);
	rep(i, 1, n) {
		x[++ m] = a[i].fi;
		x[++ m] = a[i].fi - a[i].se;
		x[++ m] = a[i].fi + a[i].se;
	}
	sort(x + 1, x + m + 1);
	m = unique(x + 1, x + m + 1) - x - 1;
	rep(i, 1, n) {
		l[i] = xtoi(a[i].fi - a[i].se);
		p[i] = xtoi(a[i].fi);
		r[i] = xtoi(a[i].fi + a[i].se);
	}
	rep(i, 1, n) {
		rep(j, 1, m) {
			F[j] = f[i - 1][p[i]] + dis(p[i], min(j, r[i]));
			cmax(F[j], f[i - 1][j]);
		}
		int R = p[i];
		per(k, i, 1) {
			if(k != i) cmax(R, r[k]);
			cmax(F[R], f[k - 1][l[i]] + dis(l[i], R));
		}
		per(j, m - 1, 1) {
			cmax(F[j], F[j + 1] - dis(j, j + 1));
		}
		rep(j, 1, m) {
			cmax(F[j], F[j - 1]);
			f[i][j] = F[j];
		}
	}
	pt("%d\n", f[n][m]);
	return 0;
}
```

---

## 作者：Sio_ (赞：1)

唐题。    
很容易发现一个事情，对于两个向左的点，如果两个点的覆盖范围有包含关系，那么被包含的点转为向右一定更优。   
我们离散化后按 $a_i$ 排序，$dp_{i,j}$ 表示第 $i$ 个点向左，覆盖范围从 $a_i$ 向右还有 $j$ 个点的最大覆盖范围，转移直接枚举下一个向左的点，中间的点必须全部向右，使用线段树优化即可，时间复杂度 $O(n^3 \log n)$，应该还有优化空间，但是已经能通过了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls cur*2
#define rs cur*2+1
#define mid (l+r)/2
const int maxn=305,inf=1e9;
int tree[maxn*4],sum[maxn*4],tag[maxn*4],pos[maxn],n,tot;
int l[maxn],r[maxn],p[maxn],len[maxn];
map<int,int> mp;
void addtag(int cur,int opt){tree[cur]=sum[cur]*opt,tag[cur]=opt;return ;}
void build(int cur,int l,int r)
{
    tag[cur]=-1;
    if(l==r){sum[cur]=pos[l]-pos[l-1];return ;}
    build(ls,l,mid),build(rs,mid+1,r);
    sum[cur]=sum[ls]+sum[rs];
}
void pushdown(int cur)
{
    if(tag[cur]==-1) return ;
    addtag(ls,tag[cur]),addtag(rs,tag[cur]);
    tag[cur]=-1;
}
void update(int cur,int l,int r,int lt,int rt,int opt)
{
    if(lt<=l&&r<=rt){addtag(cur,opt);return ;}
    if(l>rt||r<lt) return ;
    pushdown(cur);
    update(ls,l,mid,lt,rt,opt),update(rs,mid+1,r,lt,rt,opt);
    tree[cur]=tree[ls]+tree[rs];
}
int query(int cur,int l,int r,int lt,int rt)
{
    if(lt<=l&&r<=rt) return tree[cur];
    if(l>rt||r<lt) return 0;
    pushdown(cur);
    return query(ls,l,mid,lt,rt)+query(rs,mid+1,r,lt,rt);
}
void add(int l,int r){update(1,1,tot,l+1,r,1);}
void clear(){update(1,1,tot,1,tot,0);}
int ask(int l,int p){return query(1,1,tot,l+1,p);}
int dp[maxn][maxn],t[maxn];
bool cmp(int a,int b){return p[a]<p[b];}
int main()
{
    vector<int> v;
    cin>>n,n+=1;
    for(int i=1;i<=n;i++)
    {
        if(i==n) p[i]=2e8+10,len[i]=1;
        else cin>>p[i]>>len[i];
        v.push_back(p[i]),v.push_back(p[i]-len[i]),v.push_back(p[i]+len[i]),t[i]=i;
    }
    sort(t+1,t+n+1,cmp),sort(v.begin(),v.end());
    mp[v[0]]=tot=1,pos[1]=v[0];
    for(int i=1;i<v.size();i++)
        if(v[i]!=v[i-1]) mp[v[i]]=++tot,pos[tot]=v[i];
    for(int i=1;i<=n;i++) l[i]=mp[p[i]-len[i]],r[i]=mp[p[i]+len[i]],p[i]=mp[p[i]];
    build(1,1,tot);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=tot;j++) dp[i][j]=-inf;
    dp[0][0]=0;
    pos[0]=-1e9;
    for(int i=0;i<n;i++)
        for(int k=0;k<=tot;k++)
        {
            int x=t[i],maxi=k;
            clear(),add(p[x],k);
            for(int j=i+1;j<=n;j++)
            {
                int y=t[j];
                dp[j][max(maxi,p[y])]=max(ask(p[x],l[y])+min(len[y],pos[p[y]]-pos[p[x]])+dp[i][k],dp[j][max(maxi,p[y])]);
                add(p[y],r[y]),maxi=max(maxi,r[y]);
            }
        }
    int maxi=0;
    for(int j=0;j<=tot;j++) maxi=max(maxi,dp[n][j]);
    cout<<maxi-1;
}
```

---

## 作者：_ANIG_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF559E)

方法好像跟其他题解不太一样。

直接 dp 由于有两个方向，不好处理。

如果让当前的位置往左放，不知道和前面会有多少重叠。

为了处理这种情况，我们可以把贡献先算上，然后打个标记，表示需要后面某个线段往左放来完成这个贡献。

直接设计一个三维的状态：$f_{n,m,k}$ 表示考虑前 $n$ 个位置，需要一个往左至少到 $m$，且 $n$ 右边第 $n$ 到第 $k$ 个位置已经被覆盖的答案。

可以离散化一下，这样状态是三次方的。

再定义 $g_{n,k}$ 表示前 $n$ 个位置，$n$ 右边到第 $k$ 个位置已经被覆盖且 $n$ 前面没有需求的答案。

转移的时候，要么当前线段往左放满足状态里的需求，要么往右放。

如果这个位置没有线段，则考虑是否要把段的贡献算上，如果要算上，就会产生一个需求，直接塞状态里。

这样转移是 $O(1)$ 的，总复杂度 $O(n^3)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=305;
int f[N][N][N],dp[N][N],n,p[N],g[N],idx,dy[N],cnt,wz[N],sms[N],res;
map<int,int>q;
void chk(int&a,int b){a=max(a,b);}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%lld%lld",&wz[i],&sms[i]),g[++idx]=wz[i],g[++idx]=wz[i]-sms[i],g[++idx]=wz[i]+sms[i];
    g[++idx]=-1e9;
    sort(g+1,g+idx+1);
    g[0]=1e9;
    for(int i=1;i<=idx;i++){
        if(g[i]!=g[i-1])cnt++;
        q[g[i]]=cnt;
        dy[cnt]=g[i];
    }
    for(int i=1;i<=n;i++)p[q[wz[i]]]=sms[i];
    memset(f,-0x3f,sizeof(f));
    memset(dp,-0x3f,sizeof(dp));
    dp[1][1]=0;
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=i;j++){
            for(int k=1;k<=cnt;k++){
                if(p[i]){
                    if(dy[i]-p[i]<=dy[j]){
                        chk(dp[i+1][max(i,k)],f[i][j][k]);
                        if(k<=i)chk(f[i+1][i][max(i,k)],f[i][j][k]+dy[i+1]-dy[i]);
                    }
                    if(k<=i)chk(f[i+1][j][q[dy[i]+p[i]]],f[i][j][k]+p[i]);
                    else if(dy[i]+p[i]>dy[k])chk(f[i+1][j][q[dy[i]+p[i]]],f[i][j][k]+dy[i]+p[i]-dy[k]);
                    else chk(f[i+1][j][k],f[i][j][k]);
                }else{
                    if(k<=i)chk(f[i+1][j][k],f[i][j][k]+dy[i+1]-dy[i]);
                    else chk(f[i+1][j][k],f[i][j][k]);
                }
            }
        }
        for(int j=1;j<=cnt;j++){
            if(p[i]){
                if(j<=i)chk(dp[i+1][q[dy[i]+p[i]]],dp[i][j]+p[i]);
                else if(dy[i]+p[i]>dy[j])chk(dp[i+1][q[dy[i]+p[i]]],dp[i][j]+dy[i]+p[i]-dy[j]);
                else chk(dp[i+1][j],dp[i][j]);
            }else{
                if(j<=i)chk(f[i+1][i][j],dp[i][j]+dy[i+1]-dy[i]);
                chk(dp[i+1][j],dp[i][j]);
            }
        }
    }
    for(int i=1;i<=cnt;i++)res=max(res,dp[cnt+1][i]);
    cout<<res;
}
```


---

## 作者：情非昔比 (赞：1)

## 题目大意：
一个数轴上有n条线段，每条线段可以为$[x_i-l_i,x_i]$或$[x_i,x_i+l_i]$

问这条数轴上最大覆盖长度为多少。
## 解题思路：
首先我们将这些线段按照中心点$x$排序

我们考虑dp，我们用$dp_{i,j,k}$表示前$i$条线段中，最右边的覆盖是$j$贡献的，并且$j$的方向为$k$的最大覆盖长度。

至于转移，我们考虑枚举之后的线段，具体转移看代码。
# Code：
```cpp
#include<cstdio>
#include<algorithm>
using std::sort;
using std::max;
using std::min;
int n,ans,dp[120][120][2];
struct Point{
	int x,l;
	bool operator<(Point b)const{
		return x<b.x;
	}
}point[110];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&point[i].x,&point[i].l);
	sort(point+1,point+n+1);
	point[0].x=-1e8;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=i;j++)
			for(int di=0;di<=1;di++){
				ans=max(ans,dp[i][j][di]);
				int pre=point[j].x+point[j].l*di;
				for(int k=i+1,Max=-1e8,a,b;k<=n;k++)
					for(int di2=0;di2<=1;di2++){
						int nxt=point[k].x+point[k].l*di2;
						if(nxt>Max)Max=nxt,a=k,b=di2;
						dp[k][a][b]=max(dp[k][a][b],dp[i][j][di]+min(point[k].l,nxt-pre)+Max-nxt);
					}
			}
	printf("%d\n",ans);
}
```

---

## 作者：Penguin_Master (赞：0)

这种题怎么评上 *3000 的啊。

先按 $a_i$ 排序。

首先一个 naive 的想法是直接设 $dp_{i,j,0/1}$ 表示 DP 了前 $i$ 条线段，最右边的被覆盖的点在 $x_j-1/x_j+l_j-1$ 的覆盖长度最大值，然后转移就枚举第 $i$ 条线段往左或往右，根据记录下来的最右端点的信息更新答案。

但是这显然是错的，因为线段 $i$ 可能填补了**前面的一些空隙**，不难发现出现这种情况当且仅当 $i$ 往左，并且 $i$ 填补的空隙肯定是所有空隙的一段后缀。

于是我们直接枚举这个空隙的开始节点 $k$，不难发现 $k \sim i-1$ 都一定往右，然后大力转移即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/vygqtb62.png)

暴力的时间复杂度是 $\Theta(n^4)$ 的，预处理一下可以做到 $\Theta(n^3)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,j,k) for (int i=j;i<=k;++i)
#define per(i,j,k) for (int i=j;i>=k;--i)
int const N=105;
int n,dp[N][N][2];
struct node{int x,l;}a[N];
#define chkmax(x,y) (x=max(x,y))
inline void work(int L,int R,int &k1,int &k2){
    int rightpos=(k2)?(a[k1].x+a[k1].l-1):(a[k1].x-1);
    rep(i,L,R)
        if (a[i].x+a[i].l-1>rightpos){
            rightpos=a[i].x+a[i].l-1;
            k1=i,k2=1;
        }
}
inline int allright(int k,int L,int R){
    int q=min(a[R].l,max(0ll,a[R].x-1-k)),mx=0;
    rep(i,L,R-1) chkmax(mx,a[i].x+a[i].l-1);
    q+=max(0ll,mx-max(k+1,a[R].x)+1);
    return q;
}
inline void solve(){
    cin>>n;
    rep(i,1,n) cin>>a[i].x>>a[i].l;
    sort(a+1,a+n+1,[](node a,node b){return a.x<b.x;});
    a[0].x=-1e9,dp[1][1][0]=a[1].l,dp[1][1][1]=a[1].l;
    rep(i,2,n) rep(j,0,i-1) rep(u,0,1){
        int rightpos=(u)?(a[j].x+a[j].l-1):(a[j].x-1);
        {
            int k1=j,k2=u;
            if (a[i].x-1>rightpos) k1=i,k2=0;
            chkmax(dp[i][k1][k2],dp[i-1][j][u]+min(a[i].l,max(0ll,a[i].x-1-rightpos)));
        }
        {
            int k1=j,k2=u;
            if (a[i].x+a[i].l-1>rightpos) k1=i,k2=1;
            chkmax(dp[i][k1][k2],dp[i-1][j][u]+min(a[i].l,max(0ll,a[i].x+a[i].l-1-rightpos)));
        }
        rep(k,j,i-1){
            if (a[i].x-a[i].l>a[k].x) continue;
            int lef=a[i].x-a[i].l,k1=j,k2=u;
            if (a[i].x-1>rightpos) k1=i,k2=0;
            work(k,i-1,k1,k2);
            chkmax(dp[i][k1][k2],dp[k-1][j][u]+allright(rightpos,k,i));
        }
    }
    int ans=0;
    rep(i,1,n) chkmax(ans,dp[n][i][0]),chkmax(ans,dp[n][i][1]);
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=1;
    // cin>>t;
    while (t--) solve();
    cerr<<"Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
    return 0;
}
```

---

## 作者：Nine_Suns (赞：0)

趣题。

看着好像很好做，但实际想起来并不容易。

首先把所有线段按 `a` 排序，之后可以发现一个性质，如果在最终的方案中，线段的并构成了若干个长线段，那么构成每个长线段的线段编号是连续的。

于是考虑通过枚举长线段的方式 dp。设 $f_{i,j}$ 表示到第 $i$ 个线段，要构成一个长线段最左段的未覆盖的段的左端点为 $j$ 的最大覆盖长度（不包括当前长线段），$r_{i,j}$ 为此时长线段的右端点。

然后的转移就容易了。如果当前线段的覆盖不能覆盖长线段最左端的未覆盖的点，$j$ 不变，尝试更新 $r$。不然的话可以完成一段长线段，枚举下一个长线段的起始点，统计贡献。

值域比较大，可以离散化一下。复杂度 $O(n^3)$，应该可以优化到 $O(n^2\log n)$。

[Code](https://codeforces.com/contest/559/submission/259284914)。

---

## 作者：xuantianhao (赞：0)

# [Gerald and Path](https://www.luogu.com.cn/problem/CF559E)

考虑将所有线段按照固定的那一端从小往大排序，并且对线段的端点离散化。

这之后，设 $f_{i,j}$ 表示当前处理到线段 $i$，且所有线段中最右的那根的右端点不右于位置 $j$（即可以在 $j$ 左面或与 $j$ 重合）时的最优答案。

我们考虑，假设我们放了一根线段 $[l,r]$。因为不知道将来会放什么东西把它盖掉一部分，所以我们干脆在放线段 $[l,r]$ 时，同时也放下线段 $[l,l],[l,l+1],[l,l+2],\dots,[l,r-1]$，这样就不用担心被盖掉等讨论了。

于是我们现在考虑处理第 $i$ 根线段。设其向左是 $[l,p]$，向右是 $[p,r]$。

首先，其有可能在接下来（或者在 $i$ 之前就已经）被完全覆盖掉。于是一开始就有 $f_{i-1,j}\rightarrow f_{i,j}$。

其次，考虑其向右摆。向右摆，就意味着最右位置一定是 $r$，若最右位不是 $r$，则一定在 $i$ 之前还有一条向右摆的线段 $[p',r']$ 满足 $r'\geq r$。但是因为我们已经按照 $p$ 递增排序了，故必有 $[p,r]\subset[p',r']$，即 $[p,r]$ 被完全覆盖，我们已经在上面说过了。

则有 $f_{i,r}\leftarrow f_{i-1,p}+[p,r]$，因为我们已经令 $f_{i,j}$ 表示“不右于”的最优值，所以就不用费尽心思枚举 $i-1$ 时的最右位置了。同时，也不用担心重叠问题，因为按照我们上述讨论，为了避免重叠，我们直接将线段 $[l,r]$ 看作了所有 $[l,l\sim r]$。

但是这也意味着，我们的线段 $[p,r]$ 也要被看作是所有的 $[p,p\sim r]$。于是我们枚举 $j\in[p,r]$，则有 $f_{i,j}\leftarrow f_{i-1,p}+[p,j]$。

然后就考虑其向左摆了。向左摆，就意味着最右位置不一定是 $p$，因为完全可以存在一条 $[p',r']$，满足 $r'>p\operatorname{and}$，即两者无交。

首先，最右位是 $p$ 的就可以跟之前一样类似地转移，不在话下。

然后，对于最右位不是 $p$ 的，我们枚举一个 $j<i$，表示最右位是 $j$ 对应的 $[p',r']$（明显这里上述 $r'>p\operatorname{and}p'>l$ 应被满足）。则所有 $k\in(j,i]$ 都应该向左摆，因为若其向右摆，要么右端点在 $r'$ 左边或与 $r'$ 重合，被完全包含；要么右端点在 $r'$ 右边，则 $r'$ 就不是最右位了。

设所有 $k\in(j,i]$ 的东西中，最左的那个是 $[l'',p'']$，则整个 $[j,i]$ 中所有线段，加一块可以变成一个 $[l'',r']$ 的大线段，且该线段是最右的。于是此处就可以跟前面一样，枚举一个 $k\in[l'',r']$ 进行转移了。

时间复杂度 $O(n^3)$，因为枚举了 $i,j,k$ 三个元素。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define bs(x) lower_bound(v.begin(),v.end(),x)-v.begin()+1
const int N=110;
int n,m,f[N][N];
pair<int,int> p[N];
vector<int>v;
int L[N],P[N],R[N],res;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
		scanf("%d%d",&p[i].first,&p[i].second);
		v.push_back(p[i].first);
		v.push_back(p[i].first-p[i].second);
		v.push_back(p[i].first+p[i].second);
	}
    sort(p+1,p+n+1);
	sort(v.begin(),v.end());
	v.resize(m=unique(v.begin(),v.end())-v.begin());
    for(int i=1;i<=n;i++){
		L[i]=bs(p[i].first-p[i].second);
		P[i]=bs(p[i].first);
		R[i]=bs(p[i].first+p[i].second);
	}
    for(int i=1;i<=n;i++){
        memcpy(f[i],f[i-1],sizeof(f[i]));
        for(int j=P[i];j<=R[i];j++) f[i][j]=max(f[i][j],f[i-1][P[i]]+v[j-1]-v[P[i]-1]);
        for(int j=i;j;j--){
            int Rmax=(j==i?P[j]:R[j]);
            if(Rmax<P[i])continue;
            int Lmin=(j==i?L[j]:P[j]);
            for(int k=j+1;k<=i;k++) Lmin=min(Lmin,L[k]);
            for(int k=Lmin;k<=Rmax;k++) f[i][k]=max(f[i][k],f[j-1][Lmin]+v[k-1]-v[Lmin-1]);
        }
        for(int j=1;j<=m;j++) f[i][j]=max(f[i][j],f[i][j-1]);
    }
    for(int i=1;i<=m;i++) res=max(res,f[n][i]);
    printf("%d\n",res);
    return 0;
}
```


---

