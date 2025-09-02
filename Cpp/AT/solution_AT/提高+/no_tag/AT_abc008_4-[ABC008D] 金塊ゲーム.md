# [ABC008D] 金塊ゲーム

## 题目描述

高桥君正在玩一个基于无限二维网格的游戏。网格坐标系以 $(0, 0)$ 为原点，向东为 $x$ 轴正方向，向北为 $y$ 轴正方向。坐标为 $(x, y)$ 的格子表示从原点向东移动 $x$ 格（若 $x$ 为负则向西移动 $-x$ 格），向北移动 $y$ 格（若 $y$ 为负则向南移动 $-y$ 格）的位置。

网格中存在 $W \times H$ 个金块，分布在所有满足 $1 \leq p \leq W$ 且 $1 \leq q \leq H$ 的格子 $(p, q)$ 上。其中有恰好 $N$ 个格子设有金块回收装置（编号 $1$ 至 $N$）。装置满足以下条件：
- 任意两个装置所在的格子 $(a, b)$ 和 $(c, d)$ 都满足 $a \neq c$ 且 $b \neq d$
- 每个装置所在的格子互不相同

当装置启动时，首先回收所在格子的金块，然后向东南西北四个方向延伸机械臂进行扩展回收。机械臂的延伸需满足以下规则：
- **东向**：选择整数 $p > x+1$，使得区间 $(x+1, y)$ 到 $(p-1, y)$ 的格子均有金块，且 $(p, y)$ 无金块。回收该区间所有金块。
- **西向**：选择整数 $p < x-1$，使得区间 $(p+1, y)$ 到 $(x-1, y)$ 的格子均有金块，且 $(p, y)$ 无金块。回收该区间所有金块。
- **南向**：选择整数 $q < y-1$，使得区间 $(x, q+1)$ 到 $(x, y-1)$ 的格子均有金块，且 $(x, q)$ 无金块。回收该区间所有金块。
- **北向**：选择整数 $q > y+1$，使得区间 $(x, y+1)$ 到 $(x, q-1)$ 的格子均有金块，且 $(x, q)$ 无金块。回收该区间所有金块。

对于每个方向，若不存在满足条件的 $p$ 或 $q$，则无法在该方向延伸机械臂。此外，若某个方向存在可回收的金块，则必须执行回收操作。下图展示了满足条件的回收示例（图中以 `M` 表示装置，粗框表示可回收范围）。

![](http://abc008.contest.atcoder.jp/img/abc/008/4-1.png)

高桥君需要决定所有装置的启动顺序，不同的顺序可能导致最终回收数量不同。由于高桥君希望最大化金块回收量，请编写程序计算可能获得的最大金块数量。

## 说明/提示

### 部分分
- 数据集 1 ($N \leq 8$, $W,H \leq 80$)：80 分
- 数据集 2 ($W,H \leq 80$)：合计 99 分
- 数据集 3 (无限制)：合计 100 分

### 样例解释 1
输入样例 1 的初始状态如下图所示（图片链接保留）：

![](http://abc008.contest.atcoder.jp/img/abc/008/4-2.png)

按照 1 号、2 号、3 号装置的顺序启动，可以回收 19 个金块，操作过程如下图所示：

![](http://abc008.contest.atcoder.jp/img/abc/008/4-3.png)

### 样例解释 2
存在可回收全部金块的启动顺序

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6 4
3
2 4
3 1
4 3```

### 输出

```
19```

## 样例 #2

### 输入

```
3 3
3
1 1
2 3
3 2```

### 输出

```
9```

## 样例 #3

### 输入

```
15 10
8
7 10
12 8
4 4
5 7
9 9
1 6
6 5
3 2```

### 输出

```
112```

# 题解

## 作者：Union_Find (赞：2)

一道比较简单的题。

首先注意到 $1 \leq n \leq 30$，这种数据范围大概率是 $O(n^k),k \leq 5$ 或者 $O(2^{\frac{n}{2}})$ 的。这题是最优解问题，考虑 dp，所以应该是第一种时间复杂度。

注意到每次使用一台设备，会使得原来 $n \times m$ 的矩阵分裂成四个子矩阵。我们设 $f_{ax,ay,bx,by}$ 表示矩阵左上角是 $(ax,ay)$，右下角是 $(bx,by)$，该矩阵内的最优解（即只使用该矩阵内的设备，也只取该矩阵内的金块）。

那么对于一个矩阵 $(ax,ay),(bx,by)$ 来说，如果该矩阵内有一台位于 $(x,y)$ 的设备，那么就可以从分裂开的四个子矩阵转移过来。我知道没有图片很难受，所以~~盗用~~使用了 AT 题解的图片解释。

![](https://cdn.luogu.com.cn/upload/image_hosting/ziv3gomx.png)

如图，M 表示设备，那么黄色的道路就是挖金块的道路。因为这些金块都没了，所以之后的设备挖金块的道路都不会穿过这行和这列。最后问题就递归成了四个子问题。

于是我们有了如下代码。

```cpp
ll n, m, k, x[N], y[N];
il ll solve(ll ax, ll ay, ll bx, ll by){
	if (ax > bx || ay > by) return 0;
	ll ans = 0;
	for (int i = 1; i <= k; i++) if (ax <= x[i] && x[i] <= bx && ay <= y[i] && y[i] <= by) //枚举在矩阵内的设备 
		ans = max(ans, bx - ax + by - ay + 1 + // 这台设备的贡献 
			solve(ax, ay, x[i] - 1, y[i] - 1) + // 四个子矩阵枚举 
			solve(x[i] + 1, ay, bx, y[i] - 1) + 
			solve(ax, y[i] + 1, x[i] - 1, by) + 
			solve(x[i] + 1, y[i] + 1, bx, by));
	return ans;
}
```

然后，恭喜你 T 飞了。因为这样子的时间复杂度比暴力更优，所以我们还要优化。

考虑到是递归，我们加上记忆化，然后。

就 A 了。

其实这样子加完记忆化后时间复杂度就对了。看似有 $H \times W$ 个状态，但实际上我们发现，每次的矩阵的四条边都是顶着一台设备或者边缘的，所以总共只有 $O(n^4)$ 个状态，实际上并不满，因为这只是粗略的估计，实际上有很多状态跑不到。

于是我们就过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 35
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, m, k, x[N], y[N];
map <pair<pair<ll, ll>, pair<ll, ll> >, ll> tp; 
il ll solve(ll ax, ll ay, ll bx, ll by){
	if (ax > bx || ay > by) return 0;
	if (tp.count({{ax, ay}, {bx, by}})) return tp[{{ax, ay}, {bx, by}}];
	ll ans = 0;
	for (int i = 1; i <= k; i++) if (ax <= x[i] && x[i] <= bx && ay <= y[i] && y[i] <= by)
		ans = max(ans, bx - ax + by - ay + 1 + 
			solve(ax, ay, x[i] - 1, y[i] - 1) + 
			solve(x[i] + 1, ay, bx, y[i] - 1) + 
			solve(ax, y[i] + 1, x[i] - 1, by) + 
			solve(x[i] + 1, y[i] + 1, bx, by));
	return tp[{{ax, ay}, {bx, by}}] = ans;
}
int main(){
	n = rd(), m = rd(), k = rd();
	for (int i = 1; i <= k; i++) x[i] = rd(), y[i] = rd();
	printf ("%lld\n", solve(1, 1, n, m));
	return 0;
}

```

---

## 作者：gaojt (赞：1)

> DFS 记忆化搜索

>由题意知，不同顺序的使用起重机，收集到的金块数量是不同的。则可以想到使用 DFS 大法来搜索，如果不同顺序的使用起重机的结果。但是使用了起重器后，会对没用过的起重器有影响。因为起重器抓完后会出现两条空间，会将地图分为：左上，左下，右上，右下，共四个部分。如果我们对这四个部分去分别的搜索，就可以避免之前使用过的起重器产生的影响，但这样会超时。所以我使用了记忆化搜索来避免这个问题，最后，加上换行。
>
>代码如下
```
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;//long long 太长了，重新定义一个long long类型
ll w,h,n;
struct node{
	int x,y;
}a[1000010];
map<pair<pair<ll,ll>,pair<ll,ll>>,ll> op;
ll dfs(ll x,ll y,ll ww,ll hh){
	if(x>ww||y>hh)return 0;
	if(op.count({{x,y},{ww,hh}}))return op[{{x,y},{ww,hh}}];
	ll ans=0;
	for(int i=1;i<=n;i++){//判断一下要用哪个收集器（起重机）
		ll nx=a[i].x,ny=a[i].y;
		if(x<=nx&&y<=ny&&ww>=nx&&hh>=ny) ans=max(ans,ww-x+hh-y+1+dfs(x,y,nx-1,ny-1)+dfs(nx+1,ny+1,ww,hh)+dfs(x,ny+1,nx-1,hh)+dfs(nx+1,y,ww,ny-1));//使用了收集器之后，地图会被分成四部分，使用在这个部分的收集器。接着求最大值

	}
	op[{{x,y},{ww,hh}}]=ans;
	return ans;
}
int main(){
    std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);//加快输入输出
	cin>>w>>h>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	cout<<dfs(1,1,w,h)<<endl;
	return 0;
}
```

---

