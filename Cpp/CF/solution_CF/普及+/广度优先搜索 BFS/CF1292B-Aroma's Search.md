# Aroma's Search

## 题目描述

获得了新身体后，我们的偶像 Aroma White（或者应该被称为 Kaori Minamiya？）开始在 OS 空间中寻找她尘封的过去。

这个空间可以看作是一个二维平面，在其内部有着无限多的数据点，从 $0$ 开始标号，它们的坐标定义如下：

- 第 $0$ 个点的坐标为 $(x_0, y_0)$。
- 对于 $i > 0$，第 $i$ 个点的坐标为 $(x_i, y_i) = (a_x \cdot x_{i-1} + b_x, a_y \cdot y_{i-1} + b_y)$。

初始时 Aroma 的位置为 $(x_s, y_s)$。她只能留在 OS 空间中最多 $t$ 秒，因为她还需要传送回真实世界。她不需要返回初始位置 $(x_s, y_s)$ 也能传送回家。

在 OS 空间中，Aroma 可以做如下操作：

- 在点 $(x, y)$ 上时，Aroma 可以移动到这四个点之一：$(x-1, y), (x+1, y), (x, y-1), (x, y+1)$。这个操作需要耗费 $1$ 秒。
- 如果 Aroma 当前的位置上有数据点，她可以收集它。我们可以假定这个操作耗费 $0$ 秒。当然，每个数据点只能被收集一次。

Aroma 想要在传送回去之前，收集尽可能多的数据点。你能帮助她计算在 $t$ 秒内最多能收集的数据点的个数吗？

## 样例 #1

### 输入

```
1 1 2 3 1 0
2 4 20```

### 输出

```
3```

## 样例 #2

### 输入

```
1 1 2 3 1 0
15 27 26```

### 输出

```
2```

## 样例 #3

### 输入

```
1 1 2 3 1 0
2 2 1```

### 输出

```
0```

# 题解

## 作者：syksykCCC (赞：19)

首先，很容易观察到点的一些特征:

* 都在第一象限；
* 点的分布越来越稀疏。

以样例为例：

![image.png](https://i.loli.net/2020/01/20/6LiTFbklzEMIsqj.png)

还有无限个点没有画出来。

根据点的分布越来越稀疏的特性，能不能发现收集点的规律呢？
比如我们可以先枚举一个点 $i$，直接从 $(x_s, y_s)$ 出发去收集 $\text P_i$。

然后呢？如果往 $\text P_0$ 的方向收集，点会非常密集；如果往 $\text P_\infty$ 的方向收集，点就会非常稀疏。

当然，我们往 $\text P_0$ 的方向收集！

但是，这边的点是有限的，如果全部收集完了时间还绰绰有余呢？

那就原路返回，再往 $\text P_\infty$ 的方向收集！

有人可能会疑惑，为什么这里都原路返回了，答案还是最优呢？

首先，因为随着 $j$ 的增大，$x_j, y_j$ 都在增大，所以 $\sum_{j = 1}^{i}\operatorname{dist}(\text P_{j-1}, \text P_j)$（也就是从 $\text P_i$ 收集到 $\text P_0$ 的总距离）就等于 $\operatorname{dist}(\text P_0 ,\text P_i)$（$\operatorname{dist}$ 表示曼哈顿距离）。

下面为了分析方便只看 $x$ 坐标（$\operatorname{Xdist}$ 表示 $x$ 坐标之差）。

点最密集的时候应该是什么时候？很显然，$a_x$ 和 $b_x$ 都最小的时候，也就是 $a_x = 2, b_x = 0$。

$$ \operatorname{Xdist}(\text P_{i+1}, \text P_{i}) = (a_x \cdot x_{i} + b_x) - x_{i} = (a_x - 1)\cdot x_{i} + b_x = x_i $$

$$ \operatorname{Xdist}(\text P_{0}, \text P_{i}) = x_i - x_0 $$

$\because x_0 \ge 1 \qquad \therefore \operatorname{Xdist}(\text P_{i+1}, \text P_{i}) > \operatorname{Xdist}(\text P_{0}, \text P_{i})$

现在 $y$ 坐标也加进来，就可以得到 $\operatorname{dist}(\text P_{i+1}, \text P_{i}) > \operatorname{dist}(\text P_{0}, \text P_{i})$。

这说明什么？收集 $\text P_0 \sim \text P_{i - 1}$ 的时间比只收集一个 $\text P_{i + 1}$ 的时间还要少！

如果当初选择向右走，那再去收集 $\text P_{i + 2}$ 的时候，显然 $\operatorname{dist}(\text P_{i+1}, \text P_{i +2}) > \operatorname{dist}(\text P_{i}, \text P_{i+1})$，那么 $\operatorname{dist}(\text P_{i+1}, \text P_{i +2}) + \operatorname{dist}(\text P_{i}, \text P_{i+1}) > 2 \operatorname{dist}(\text P_{0}, \text P_{i})$。说明向 $\text P_{\infty}$ 方向收集 $2$ 个点的时候，$\text P_0$ 方向已经回来了，并收集了 $i$ 个点，如果 $i \ge 2$ 那么直接可以知道答案更优了，还剩两种情况：

* $i=0$，这时没什么左右之分，那不影响答案；
* $i=1$，直接带入算一算，$x_1 = 2 x_0$，$x_2 = 4 x_0$，那么左边加上返回的时间是 $2 x_0$，直接去 $\text P_2$ 的时间也是 $2 x_0$，因为越往后点越稀疏，而两种方案当前耗时相同，起点不同，所以 $\text P_0$ 方向还是更优。

还有一个小问题，就是数组开多大，因为 $2^{64} > 10^{18}$，所以数组开到 $70$ 就绰绰有余了。

时间复杂度 $\mathcal O(n^2)$，$n$ 是要用到的点数，算到 $x_n > x_s, y_n > y_s, \operatorname{dist}(\text P_n, \text S) > t$ 即可。

```cpp
#include <bits/stdc++.h>
#define max(a, b) a > b ? a : b
typedef long long LL;
const int N = 70;
LL ax, ay, bx, by, ans, n; 
LL x[N], y[N], xs, ys, t;
LL dist(LL x1, LL y1, LL x2, LL y2) { return llabs(x1 - x2) + llabs(y1 - y2); }
int main()
{
	scanf("%lld %lld %lld %lld %lld %lld", x, y, &ax, &ay, &bx, &by);
	scanf("%lld %lld %lld", &xs, &ys, &t);
	while(++n)
	{
		x[n] = ax * x[n - 1] + bx; y[n] = ay * y[n - 1] + by;
		if(x[n] > xs && y[n] > ys && dist(xs, ys, x[n], y[n]) > t) break;
	}
	for(int i = 0; i <= n; i++)
	{
		LL tans = 0, tt = t;
		if(dist(xs, ys, x[i], y[i]) <= tt) tt -= dist(xs, ys, x[i], y[i]), tans++; // S -> Pi 
		else { ans = max(ans, tans); continue; }
		for(int j = i; j; j--) // Pi -> P0
		{
			if(dist(x[j], y[j], x[j - 1], y[j - 1]) <= tt)
				tt -= dist(x[j], y[j], x[j - 1], y[j - 1]), tans++;
			else break;
		}
		for(int j = 1; j <= n; j++) // P0 -> Pi -> P∞
		{
			if(dist(x[j], y[j], x[j - 1], y[j - 1]) <= tt)
				tt -= dist(x[j], y[j], x[j - 1], y[j - 1]), tans += j > i; // 注意 j > i 的时候才能算入 
			else break;
		}
		ans = max(ans, tans);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Tony102 (赞：5)

[CF1292B](https://www.luogu.com.cn/problem/CF1292B)

[更好的阅读体验My Blog](https://tony102.xyz/index.php/2020/10/24/cf1292b-aromas-search/)

### Description

平面上有无穷多个物品,坐标满足递推关系 $x_i = a_i x_{i-1} + b_x$, $y_i=a_iy_{i-1}+b_y$ 起始位置在 $(x s , y s )$,每时刻可以向前后左

右移动 1 单位长度。当你移动到一个物品所在坐标时可以立即获得这个物品。求 $t$ 时间内最多能获得多少物品。



### Solution

透过现象看本质

注意到$b_x,b_y$的范围都很大，再观察物品的坐标是满足一个一次函数关系的。$a_x,a_y$是斜率，而截距很大。注意到自变量其实是你上一个坐标，所以这些物品的坐标会当$x_{i-1},y_{i-1}$达到一定范围的时候，增长极大。

由此我们可以知道，在我们有限的时间$t$内，是不可能走到很多点的（最多大概是$100$）左右，所以可以走到的这些物品的位置我们都可以算出来。

有了这些，我们只需要考虑如何选点即可。当$x_{i-1},y_{i-1}$还处于一个比较小的范围的时候，相对于全局他们的分布是密集的。当$x_{i-1},y_{i-1}$上升到一定大小时，两个点会间隔较远。$t$内有可能走不到。

于是我们贪心地走，因为点不多，所以我们可以枚举一个起始的物品，从它开始往下选物品，选到不能选到时候，走回来，看看还能不能往上选物品（因为实际上你的选物品的路径一定是一个从下网上选物品的）。

复杂度$O(n^2)$

写法还有很多种，效果是一样的。范围又小，这一种还比较好写，因为这道题细节有点多。



### Code

又到了我最喜欢的代码环节

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int x0, Y0, ax, ay, bx, by, xs, ys, t;

std::vector < pair < int, int > > a;

inline int read()
{
	char ch = getchar();
	int f = 1, x = 0;
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
	return x * f;
}

inline void init()
{
	int xi = x0, yi = Y0, nx = 0, ny = 0;
	a.push_back(make_pair(x0, Y0));
	while (1) {
		nx = ax * xi + bx, ny = ay * yi + by;
		if (abs(nx - x0) > (1e17) || abs(ny - Y0) > (1e17)) break;
		a.push_back(make_pair(nx, ny));
		xi = nx, yi = ny;
	}
}

signed main()
{
	x0 = read(), Y0 = read(), ax = read(), ay = read(), bx = read(), by = read();
	xs = read(), ys = read(), t = read();
	init();
	int ans = 0;
	for (register int i = 0; i < a.size(); ++ i) {
		int tim = llabs(xs - a[i].first) + llabs(ys - a[i].second), cnt = 0;
		if (tim > t) continue;
		++ cnt;
		int xi = a[i].first, yi = a[i].second;
		if (i > 0) {
			for (register int j = i - 1; j >= 0; -- j) {
				int dis = (llabs(xi - a[j].first) + llabs(yi - a[j].second));
				tim += dis;
				if (tim > t) break;
				++ cnt;
				xi = a[j].first, yi = a[j].second;
			}
		}
		if (tim >= t) { ans = std::max(ans, cnt); continue; }
		for (register int j = i + 1; j < a.size(); ++ j) {
			int dis = llabs(xi - a[j].first) + llabs(yi - a[j].second);
			tim += dis;
			if (tim > t) break;
			++ cnt;
			xi = a[j].first, yi = a[j].second;
		}
		ans = std::max(ans, cnt);
	}
	printf("%lld\n", ans);
	return 0;
}
```



---

## 作者：寒鸽儿 (赞：3)

data nodes的横纵坐标的增长级显然是指数级别的,所以合法点个数的级别是$O(log_a t)$,当a取2时为$O(log_2t)$。也就是不到50个点。  
所以可以先算出合法范围内的点的坐标。  
根据贪心性原则,很显然所收集的点是合法点按坐标排序后的一个连续区间的点。  
那么可以枚举从$(xs, ys)$到的第一个点的下标,以及收集的点的区间。求最大的区间长度。  
复杂度$O(log_a^3t)$
```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#define ll long long

using namespace std;


inline ll getdis(ll x1, ll y1, ll x2, ll y2) { return abs(y2 - y1) + abs(x2 - x1); }
ll ax, ay, bx, by;
inline ll prex(ll xi) { return (xi - bx) / ax; }
inline ll nexx(ll xi) { return xi * ax + bx; }
inline ll prey(ll yi) { return (yi - by) / ay; }
inline ll nexy(ll yi) { return yi * ay + by; }

vector<ll> vx, vy;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll x0, y0, xs, ys, t;
    cin >> x0 >> y0 >> ax >> ay >> bx >> by >> xs >> ys >> t;
    ll xi = x0, yi = y0;
    while(xi < 3e16 && yi < 3e16) {
        if(getdis(xi, yi, xs, ys) <= t) {
            vx.push_back(xi);
            vy.push_back(yi);
        }
        xi = nexx(xi);
        yi = nexy(yi);
        if(xi < 0 || yi < 0) break;
    }
    ll tt;
    int ans = 0;
    for(int i = 0; i < vx.size(); ++i) { // start place
        for(int l = 0; l < vx.size(); ++l) { // left side
            for(int r = l; r < vx.size(); ++r) { //right side
                if(l <= i && i <= r) {
                    tt = getdis(vx[i], vy[i], xs, ys) + getdis(vx[l], vy[l], vx[r], vy[r]) + min(getdis(vx[l], vy[l], vx[i], vy[i]), getdis(vx[r], vy[r], vx[i], vy[i]));
                    if(tt <= t) {
                        ans = max(ans, r - l + 1);
                    }
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：rrrrr (赞：2)

wa了五次

#### 题意
在坐标平面上根据题意构造一些点，从 $sx,sy$ 经过最多 $t$ 秒最多能通过多少点。
#### 思路
首先$ 2\le a_x,a_y\le100$
所以节点大小增长速度很快，能访问的节点很少，且向左访问比向右更优（想一想）               
所以枚举每一个节点，暴力先向左跑，跑完向右跑，实现有点麻烦，看代码。
#### 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int xz,yz,ax,ay,bx,by,sx,sy,t,ssd;
int x[55050],y[55050],nk[51111],ans=0,kk[50111],kc[50011];
void bbc(int ki)
{
	int nz=ki;
	int an=0;
	int tt=t;
	int nm=nz;
	if(tt>=nk[nz])
	{
	tt-=nk[nz];
	an++;
	while(tt>=kk[nz]&&nz>0)
	{
		tt-=kk[nz--];
		an++;
	}
	if(tt>=kc[nm+1])
	{
		tt-=kc[nm+1];
		an++;
		nz=nm+2;
		while(tt>=kk[nz])
		{
			tt-=kk[nz++];
			an++;
		}
		
	}
	ans=max(an,ans);
	}
}
signed main()
{
	cin>>xz>>yz>>ax>>ay>>bx>>by>>sx>>sy>>t;
	x[0]=xz,y[0]=yz;
	int as=0x3f3f3f3f3f3f3f3f,nz=0;
	for(int i=1;i<=1000;i++)
	{
		x[i]=ax*x[i-1]+bx;
		y[i]=ay*y[i-1]+by;
		
		nk[i]=abs(sx-x[i])+abs(sy-y[i]);
		kk[i]=abs(x[i-1]-x[i])+abs(y[i-1]-y[i]);
		kc[i]=kc[i-1]+kk[i];
		if(nk[i]<as)
		{
			as=nk[i];
			nz=i;
		} 
		ssd=i;
		if(x[i]<0||y[i]<0||x[i]>3*1e16||y[i]>3*1e16||ax*x[i]+bx>3*1e17||ay*y[i]+by>3*1e17)
		break;
	}
	nk[0]=abs(sx-x[0])+abs(sy-y[0]);
	if(t>=as)
	ans=1;
	for(int i=0;i<=ssd;i++)
	{
		bbc(i);
	}
	cout<<ans;
}
```

---

## 作者：Eason_AC (赞：2)

## Content
给定一个坐标系，已知第一个点的坐标为 $(x_0,y_0)$，第 $i(i>0)$ 个点的坐标满足这样的两个递推式：$x_i=a_xx_{i-1}+b_x,y_i=a_yy_{i-1}+b_y$。现在从 $(x_s,y_s)$ 出发，每秒钟能够上下左右走一个格子，求在 $t$ 秒内最多能够经过的点的个数。

**数据范围：$1\leqslant x_0,y_0,x_s,y_s,t\leqslant 10^{16},2\leqslant a_x,a_y\leqslant 100,0\leqslant b_x,b_y\leqslant 10^{16}$。**
## Solution
我们发现，坐标的增长是指数级的。因此坐标在 $10^{16}$ 以内的点其实并不多，甚至可以说是非常有限。而且可以确定的是，要想经过点最多，一定得要从近的点走到远的点。所以我们考虑直接暴力模拟，先往左跑，再往右跑，看哪边能够经过的点多就取哪一边的答案。

依据这种思路写的代码跑的挺快，最慢的点大约也就 $30$ ms，不用担心会超时。
## Code
```cpp
long long ax, ay, bx, by, xs, ys, t, x[100007], y[100007];

int main() {
	getll(x[0]), getll(y[0]), getll(ax), getll(ay), getll(bx), getll(by), getll(xs), getll(ys), getll(t);
	int num = 0;
	while(x[num] <= xs + t && y[num] <= ys + t) num++, x[num] = ax * x[num - 1] + bx, y[num] = ay * y[num - 1] + by;
	ll tmp = 0; int ans = 0;
	_for(i, 0, num) {
		tmp = t - llabs(x[i] - xs) - llabs(y[i] - ys);
		int j = i + 1, cnt = 0;
		while(tmp >= 0 && j <= num) cnt++, tmp -= (x[j] - x[j - 1] + y[j] - y[j - 1]), j++;
		cnt += (tmp >= 0), ans = max(ans, cnt), tmp = t - abs(x[i] - xs) - abs(y[i] - ys), j = i - 1, cnt = 0;
		while(tmp >= 0 && j <= num) cnt++, tmp -= (x[j + 1] - x[j] + y[j + 1] - y[j]), j--;
		cnt += (tmp >= 0), ans = max(ans, cnt);
	}
	writeint(ans);
	return 0;
}
```

---

## 作者：chinaxjh (赞：1)

# 前言
此题题目不难，思路很好想，但是我上界定太大爆炸了，$fst$直接下青，发现很多人也在此题$fst$了，于是来写篇题解
# 题意分析
有一些数据节点，主人公要去收集这些节点，问在指定时间内最多收集多少个
# 思路
可以轻易想到，数据节点的位置分布是有$\color{red}\text{特点}$的（详情请看题目），节点的横纵坐标是在不断增大，且增大的量越来越大($\text{ax,ay>1}$)，所以不论我们一开始到哪个节点去收集，接下来一定是向前一个节点收集能比往后一个节点收集的多，并且向前收集就会不断往前收集，直到到头再去考虑后面没有收集过的。

所以我们可以暴力枚举第一个采集的节点，然后先向前，在往后收集，判断有无超过时限即可
# 时间复杂度
$$O(log_2(t)^2)$$
# $\text{code}$
```pascal
const jie=50000000000000000;//不要定太大!!!，我就是作死写了1e17然后fst的，够大就可以了
var
  x,y:array[0..1000] of int64;
  ax,ay,bx,by,xs,ys,t,time:int64;
  n,i,ans,anss,j:longint;
begin
  readln(x[0],y[0],ax,ay,bx,by);
  readln(xs,ys,t);
  n:=100;
  for i:=1 to n do
  begin
    x[i]:=x[i-1]*ax+bx;
    y[i]:=y[i-1]*ay+by;
    if (x[i]>=jie) or (y[i]>=jie) then break;
  end;//预处理信息节点
  n:=i-1;
  for i:=0 to n do//枚举采集的第一个节点
  begin
    if anss>ans then ans:=anss;//取最大值
    anss:=0;
    time:=abs(xs-x[i])+abs(ys-y[i]);
    if time>t then continue;//超时就换第一个节点
    inc(anss);
    for j:=i-1 downto 0 do//先向前采
    begin
      time:=time+abs(x[j+1]-x[j])+abs(y[j+1]-y[j]);
      if time>t then break;
      inc(anss);
    end;
    time:=time+x[i+1]-x[0]+y[i+1]-y[0];
    if time>t then continue;
    inc(anss);
    for j:=i+1 to n-1 do//再向后采
    begin
      time:=time+abs(x[j+1]-x[j])+abs(y[j+1]-y[j]);
      if time>t then break;
      inc(anss);
    end;
  end;
  if anss>ans then ans:=anss;//取最大值
  writeln(ans);
end.

```
# 后记
题目不难，代码量也不大，但一定要仔细小心，避免$fst$之后掉到$2000+$然后下青的命运

$\mid\color{red}\text{诚实面对自己的悲伤，与事与愿违的世界释怀}$

---

## 作者：lytqwq (赞：1)

**这题就是个模拟**

说是有无限个点，但是有的点根本到不了，我只要算出可能到的点的坐标：

```cpp
	for(int i=1;;i++)
	{
		x[i]=x[i-1]*ax+bx;
		y[i]=y[i-1]*ay+by;
		if(x[i]>2e16||y[i]>2e16)
		{
			n=i-1;
			break;
		}
	}
```


我们根据$ax>=2,bx>=2$，判断出

这样的点最多有
$log$  $2e16$ 个。


因为从第$i$个点到第$i+1$个点的距离显然比从第$i$个点到第$0$个点的距离大，所以先往回走更优。

枚举一个点i，让起始点先到$i$，然后按$i-1,i-2....0,i+1,i+2,i+3...$的顺序走就行了。

（所以真的是模拟

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 101
long long int x[N],y[N],ax,ay,bx,by,xs,ys,T,n,sum,maxn;
int main()
{
	cin>>x[0]>>y[0]>>ax>>ay>>bx>>by>>xs>>ys>>T;
	for(int i=1;;i++)
	{
		x[i]=x[i-1]*ax+bx;
		y[i]=y[i-1]*ay+by;
		if(x[i]>2e16||y[i]>2e16)
		{
			n=i-1;
			break;
		}
	}
	for(int i=0;i<=n;i++)
	{
		long long int sT=T-(abs(xs-x[i])+abs(ys-y[i]));
		if(sT<0)
		{
			continue;
		}
		sum=1;
		maxn=max(maxn,sum);
		for(int o=i-1;o>=0;o--)
		{
			sT-=(abs(x[o+1]-x[o])+abs(y[o+1]-y[o]));
			if(sT<0)
			{
				break;
			}
			sum++;
		}
		sT-=(abs(x[0]-x[i])+abs(y[0]-y[i]));
		if(sT<0)
		{
			maxn=max(maxn,sum);
			continue;
		}
		for(int o=i+1;o<=n;o++)
		{
			sT-=(abs(x[o]-x[o-1])+abs(y[o]-y[o-1]));
			if(sT<0)
			{
				break;
			}
			sum++;
		}
		maxn=max(maxn,sum);
	}
	cout<<maxn<<endl;
}
```




---

## 作者：yesong (赞：0)

比较有趣的模拟吧，要考虑的细节还比较多

说几个点：
## 性质
- 把无限点集的坐标视为数列，由数列的递推公式中，k>=2
，可知若干个之后点，必然是无法到达，因此我们要确定上界：

```cpp
if(x[i+1]>t+xs||y[i+1]>t+ys) {
	N=i;
	break;
}
```
- 那么如何走才能得到尽可能多的点？

由贪心可得，Aroma如果走到了一个点，此时向左走比向右走是更优的，如果走到最左还有剩余的时间，我们再往右走。

因此我们枚举Aroma到每个点的情况，在该情况下求最优值。

```cpp
//from yesong
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;

const int maxn=1e3+10;
const int mod=1000000000+7;
const double eps=1e-6;

ll dis(ll x1,ll y1,ll x2,ll y2) {
    return abs(x1-x2)+abs(y1-y2);
}
ll x0,y0,ax,ay,bx,by,xs,ys,t,N;
ll d[maxn],x[maxn],y[maxn];

int main() {
   // freopen("test.txt","r",stdin);
    cin>>x0>>y0>>ax>>ay>>bx>>by;
    cin>>xs>>ys>>t;
    x[1]=x0,y[1]=y0;
    //d[i]  i->i+1 所需路程
    N=110;
    for(int i=1;i<=N;i++) {
        x[i+1]=ax*x[i]+bx;
        y[i+1]=ay*y[i]+by;
        d[i]=x[i+1]-x[i]+y[i+1]-y[i];
        if(x[i+1]>t+xs||y[i+1]>t+ys) {
            N=i;
            break;
        }
    }
    int ans=0;
    for(int i=1;i<=N;i++) {
        int time=0;
        if(dis(xs,ys,x[i],y[i])<=t) {
            ll temp=0;
            time++;
            ll t1=t-dis(xs,ys,x[i],y[i]);
            for(int j=i-1;j>=1;j--) {
                if(t1>=d[j]) {
                    t1-=d[j];
                    temp+=d[j];
                    time++;
                } else {
                    break;
                }
            }
            t1-=temp;
            if(t1) {
                for(int j=i;j<=N;j++) {
                    if(t1>=d[j]) {
                        t1-=d[j];
                        time++;
                    } else {
                        break;
                    }
                }
            }
            ans=max(ans,time);
        }
    }
    cout<<ans<<endl;
    return 0;
}

```


---

