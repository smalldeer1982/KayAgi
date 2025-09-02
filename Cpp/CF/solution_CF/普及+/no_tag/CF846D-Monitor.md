# Monitor

## 题目描述

## [题目简述]

Luba最近买了个显示器，这个显示器是一个n×m的矩形。但是不久之后她发现这个显示器上有些像素不正常工作（可能会成为坏点）。如果屏幕上有一块k*k的区域都是坏点，那么Luba就觉得这个显示器坏了。她知道有q个像素不正常，而且知道它们彻底罢工变成坏点的时间。

请告诉Luba显示器会不会坏掉，如果会请告诉她具体时间。

## 样例 #1

### 输入

```
2 3 2 5
2 1 8
2 2 8
1 2 1
1 3 4
2 3 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 3 2 5
1 2 2
2 2 1
2 3 5
3 2 10
2 1 100
```

### 输出

```
-1
```

# 题解

## 作者：泠小毒 (赞：4)

# Monitor
有一个n×m的矩阵,矩阵上的点会破碎，当有一个边长为k的正方形完全破碎时，整个矩阵就会破碎

现给出q个信息，x,y,t，表示x行y列会在t时破碎

求出整个矩阵什么时候会破碎，如果不会，输出-1
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190514/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190514.html)
## 解法
a[i][j]表示i行j列破碎的时间，如果不会破碎，就是inf

我们需要查询所有边长为k的正方形中最大值的最小值

暴力的话是n^4，而可接受的是n^3，想一想

可以预处理出max[i][j]表示i行j~j+k-1列中的最大值，就优化成n^3了
## ac代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,k,q,x,y,t,s,ans=0x3f3f3f3f,a[510][510],maxx[510][510];
int main()
{
	memset(a,0x3f,sizeof(a)),memset(maxx,0,sizeof(maxx)),scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1;i<=q;i++)scanf("%d%d%d",&x,&y,&t),a[x][y]=t;
	for(int i=1;i<=n;i++)for(int j=1;j<=m-k+1;j++)
		for(int kk=0;kk<k;kk++)maxx[i][j]=max(maxx[i][j],a[i][j+kk]);
	for(int i=1;i<=n-k+1;i++)for(int j=1;j<=m-k+1;j++)
	{
		s=0;
		for(int kk=0;kk<k;kk++)s=max(s,maxx[i+kk][j]);
		ans=min(ans,s);
	}
	if(ans>1e9)puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Error_Eric (赞：2)

### 题意

二维滑动窗口。


### Sol

严格 $O(nm)$ 做法，题解区复杂度最小，目前最优解。可以通过 $n=5000,m=5000$ 的加强数据。

因为是二维滑动窗口，所以可以拆解为两个一维滑动窗口的问题。

具体地，记每个像素点坏掉的时间是 $a_{x,y}$ （如果不会坏掉则为 $+\infty$）。

重构一个二维数组 $b$，其中 $b_{x,y}$ 表示 $\min_{i=y}^{y+k} a_{x,i}$。也即 $x,y$ 右起前 $k$ 个的最大值。

容易发现这个东西对 $a$ 的每一行做一个滑动窗口板子即可实现。

重构一个二维数组 $c$ 其中 $c_{x,y}$ 表示 $\min_{i=x}^{x+k}b_{i,y}$。

容易发现这个东西对 $b$ 的每一列做一个滑动窗口板子即可实现。

那么根据这两个数组的定义不难发现 $c_{x,y}$ 表示左上角为 $(x,y)$ 的 $k\times k$ 窗口内的最大值。

对 $c$ 数组取 min 即为所求。

### Code

显然不需要真的把 $c$ 建出来，只需要更新 $ans$ 就可以了。

代码比较简单，学过单调队列的应该都会写，就放个链接罢。

[Link](https://codeforc.es/contest/846/submission/179836876)（186ms）。

此题还有 $O(m(n\log n)+n(m\log m))$ 的优先队列解法，也放个链接。

[Link](https://codeforc.es/problemset/submission/846/179831795)（233ms）。

---

## 作者：lukelin (赞：2)

看了一眼这题所用的操作，我觉得二维树状数组珂做，然后发现如果按时间顺序把节点一个个加进去再判会TLE，但发现二分时间明显比刚刚的做法快，于是二分时间+暴力插入该时间之内的点+树状数组维护即可AC

贴个代码：
```cpp
#include <cstdio>
#include <cstring>
#define ll long long
#define lowbit(x) (x&(-x))

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int C[1005][1005];
int n, m, k, q;
int xi[250005], yi[250005];
ll ti[250005];

void clr(){
    memset(C, 0, sizeof(C));
}

void modify(int i, int j, int val){
    for(int x = i; x <= n; x += lowbit(x))
        for(int y = j; y <= m; y += lowbit(y))
            C[x][y] += val;
}

int getsum(int i, int j){
   int res = 0;
   for(int x = i; x > 0; x -= lowbit(x))
        for(int y = j; y > 0; y -= lowbit(y))
            res += C[x][y];
   return res;
}

inline bool judge(ll num){
    clr();
    for (int i = 1; i <= q; ++i)
        if (ti[i] <= num)
            modify(xi[i], yi[i], 1);
    for (int i = k; i <= n; ++i)
        for (int j = k; j <= m; ++j){
            int tmp1 = getsum(i, j) - getsum(i - k, j) - getsum(i, j - k) + getsum(i - k, j - k);
            if (tmp1 == k * k)
                return true;
        }
    return false;
}

int main(){
    n = read(), m = read(), k = read(), q = read();
    ll _max = 0;
    for (int i = 1; i <= q; ++i){
        xi[i] = read(), yi[i] = read(), ti[i] = read();
        if (ti[i] > _max) _max = ti[i];
    }
    ll l = 0, r = _max + 1, ans = -1;
    while (l <= r){
        ll mid = (l + r) >> 1ll;
        if (judge(mid)){
            r = mid - 1;
            ans = mid;
        }
        else
            l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Acfboy (赞：1)

为什么题解里都是奇怪的二维树状数组做法啊，~~1900 的题真的需要这么高级的东西吗~~ 这题完全可以直接做。

首先这东西显然可以二分，然后我们希望尽量快地判断按时间时间排序的前 $x$ 个点会不会组成一个 $k\times k $ 的方形。

那么记 $f_{i,j}$ 为第 $i$ 行第 $j$ 列结尾的最长连续段数，$cnt_{i, j}$ 表示以 $(i, j)$ 为右下角点的满足长为 $k$ 的矩形的最大高度。  
$f$ 很好转移，而 $cnt$ 的一个列上的值要增加当且仅当这一行以第 $j$ 个结尾的有超过 $k$ 个的，那么只需要判断一下 $f_{i, j}$ 是否大于 $k$，是则 $cnt_{i, j} = cnt_{i-1, j} + 1$，否则把 $cnt_{i, j}$ 设为 $0$ 就可以了。

最后判断一下存不存在 $cnt_{i, j} \ge k$ 即可。  
$cnt, f$ 都可以滚动。

时间复杂度 $O(nm \log_2 q)$，好于树状数组的做法，代码在[这里](https://codeforces.com/contest/846/submission/122276380)。

但是想一想，我们真的需要二分吗？

由一次上面的操作就可以得到每一个点为右下角的是否可行，而一块可行之后就只要判断其中点的最晚时间就可以了，由于每个点只出现一次，所以直接用单调队列求出每个 $k\times k$ 的矩形中的最大值就可以了。最后若右下的 $cnt \ge k$ 就用里面的答案去更新。

时间复杂度 $O(nm)$，在洛谷上获得了最优解，但不知为什么在 CF 上跑得比带 $\log$ 的还要慢（  

注意单调队列别搞错头尾、时间可以有 $0$，我不会告诉你我因此调了很久。

代码。

```cpp
#include <cstdio>
#include <deque>
#include <algorithm>
const int N = 505, INF = 0x3f3f3f3f;
int n, m, k, q, f[N][N], cnt[N][N], map[N][N], tot, ans = INF, max[N][N],
	twt[N][N];
std::deque<int> que;
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &q);
	for (int i = 1, x, y, z; i <= q; i++) {
		scanf("%d%d%d", &x, &y, &z);
		map[x][y] = z+1;
	}
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) {
			f[i][j] = (map[i][j]) ? (f[i][j-1] + 1) : 0;
			cnt[i][j] = (f[i][j] >= k) ? (cnt[i-1][j] + 1) : 0;
		}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			while (!que.empty() && map[i][que.back()] < map[i][j]) que.pop_back();
			que.push_back(j);
			max[i][j] = map[i][que.front()];
			while (!que.empty() && j - que.front() + 1 >= k) que.pop_front();
		}
		while (!que.empty()) que.pop_back();
	}
	for (int j = 1; j <= m; j++) { 
		for (int i = 1; i <= n; i++) {
			while (!que.empty() && max[que.back()][j] < max[i][j]) que.pop_back();
			que.push_back(i);
			twt[i][j] = max[que.front()][j];
			while (!que.empty() && i - que.front() + 1 >= k) que.pop_front();
		}
		while (!que.empty()) que.pop_back();
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) 
			if (cnt[i][j] >= k) ans = std::min(ans, twt[i][j]);
	if (ans == INF) ans = -1;
	else ans -= 1;
	printf("%d", ans);
	return 0;
}
```

---

## 作者：registerGen (赞：1)

安利我的 [blog](https://registergen.github.io/) 和我的 [2020 年 7 月水题选做](https://registergen.github.io/post/problems-in-july-2020/)。

# Hint

二分答案内套一个二维 BIT。

# Solution

显然，时间越往后坏掉的像素就越多。于是可以二分屏幕坏掉的时间。

二分的 `check(x)` 函数怎么写呢？

思路是对于每个 $i\in [1,q]$，若 $t_i\le x$，则把 $(x_i,y_i)$ 弄坏。最后在 $n\times m$ 的屏幕上枚举每个边长为 $k$ 的正方形。若存在一个正方形，使得它里面的坏点为 $k^2$，则这个答案是合法的，返回 `true`，否则返回 `false`。

暴力枚举正方形并统计正方形内坏点个数的复杂度是 $\mathcal O(nmk^2)$ 的，过不了。

于是考虑优化。发现可以用二维 BIT 代替暴力。

具体做法是：二维 BIT 统计坏点的个数。先把符合要求的 $(x_i,y_i)$ 都在 BIT 上加 $1$。然后枚举正方形的某一个端点（我选的是右上角），用 BIT 及二维差分的思想数出正方形内坏点的个数。然后判断是否合法即可。

这样做的复杂度是 $\mathcal O(q\log n\log m+nm\log n\log m)$ 的。由于这是 `check` 函数的复杂度，所以总复杂度为 $\mathcal O(\log(\max t_i)\cdot(q\log n\log m+nm\log n\log m))$，能过。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

const int N=500;

int n,m,k,q,a[N+10][N+10],c[N+10][N+10];
int x[N*N+10],y[N*N+10],t[N*N+10];

#define lowbit(x) (x&(-x))

inline void modify(int _x,int _y,int v)
{
	for(int i=_x;i<=n;i+=lowbit(i))
		for(int j=_y;j<=m;j+=lowbit(j))
			c[i][j]+=v;
}

inline int query(int _x,int _y)
{
	int res=0;
	for(int i=_x;i;i-=lowbit(i))
		for(int j=_y;j;j-=lowbit(j))
			res+=c[i][j];
	return res;
}

#undef lowbit

inline bool check(int X)
{
	memset(c,0,sizeof(c));
	for(int i=1;i<=q;i++)
		if(t[i]<=X)
			modify(x[i],y[i],1);
	for(int i=k;i<=n;i++)
		for(int j=k;j<=m;j++)
		{
			int tmp=query(i,j)-query(i-k,j)-query(i,j-k)+query(i-k,j-k);
			if(tmp==k*k)return 1;
		}
	return 0;
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&q);
	int l=0,r=0,mid,ans=-1;
	for(int i=1;i<=q;i++)
		scanf("%d%d%d",x+i,y+i,t+i),r=std::max(r,t[i]);
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Expector_Hutch (赞：0)

> 这几乎就是个二维 ST 表板子

先考虑暴力，显然可以遍历所有以 $(x,y)$ 为左上角的矩形区域，求一个最大值，朴素算法 $\mathcal{O}(nmk^2)$，很容易优化掉一维到 $\mathcal{O}(nmk)$，但是~~我想直接用现成的板子~~我想练习一下数据结构，于是就想到了二维 ST 表，最终复杂度 $\mathcal{O}(nm\log n\log m)$。

---

也是写这道题的时候突然想到要是有二维 ST 表就好了，现学现卖，这里简单讲一下怎么实现二维 ST 表。

类比一维 ST 表，我们可以用 $st[x,y][i,j]$ 表示左上角坐标为 $(x,y)$，右下角坐标为 $(x+2^{i-1},y+2^{j-1})$ 的矩形区域的最大值，分情况将矩形区域分割为横向或纵向两部分，不难想到状态转移方程：

$$
st[x,y][i,j]=\begin{cases}
\max(st[x,y][i-1,j],st[x+2^{i-1}][y,i-1,j]) & \text{ if } x\neq 0 \\
\max(st[x,y][i,j-1],st[x,y+2^{j-1}][i,j-1]) & \text{ otherwise }
\end{cases}
$$

预处理复杂度 $\mathcal{O}(nm\log n\log m)$。查询也很简单，只要分成四块区域就可以了：

$$
\max\limits_{x,y=x_1,y_1}^{x_2,y_2}a_{x,y}=\max\left\{\begin{matrix}
st[x_1,y_1][i,j]\\
st[x_3,y_1][i,j]\\
st[x_1,y_3][i,j]\\
st[x_3,y_3][i,j]
\end{matrix}\right\}
$$

其中 $a$ 表示原二维矩阵，$(x_1,y_1)$ 为左上角坐标，$(x_2,y_2)$ 为右下角坐标，$i = \log_2(x_2 - x_1 + 1)$，$j = \log_2(y_2 - y_1 + 1)$，$x_3 = x_2 - 2^i + 1$，$y_3 = y_2 - 2^j + 1$。查询复杂度 $\mathcal{O}(1)$。

> 一点小优化：
>
> 用库函数来计算 $\lfloor\log_2(x)\rfloor$ 效率比较低，我们可以使用下面的代码实现 $\mathcal{O}(1)$ 计算：
>
> ```cpp
> const auto lb = [](const int x) -> const int { return x ? 31 - __builtin_clz(x) : 0; };
> ```
> 原理是利用了 `__builtin_clz` 内置函数来计算最高有效位的位置。具体来说，`__builtin_clz(x)` 返回 `x` 的前导零的数量，`31 - __builtin_clz(x)` 则计算出 `x` 的最高有效位的位置，从而得到 `floor(log2(x))` 的值。

---

## 参考代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    // 禁用同步 I/O 以提高输入输出效率
    std::cin.tie(nullptr)->sync_with_stdio(false);

    // 读取输入
    int n, m, k, q;
    cin >> n >> m >> k >> q;

    // 定义一个 lambda 函数，用于计算 log_2(n)
    const auto lb = [](const int x) -> const int { return x ? 31 - __builtin_clz(x) : 0; };

    // 初始化 ST 表，初始值为 INT_MAX
    vector<vector<vector<vector<int>>>> st(
        n + 1, vector<vector<vector<int>>>(m + 1, vector<vector<int>>(lb(n) + 1, vector<int>(lb(m) + 1, INT_MAX))));

    // 读取 q 次查询并初始化 ST 表
    while (q--) {
        int x, y, t;
        cin >> x >> y >> t;
        st[x][y][0][0] = t;
    }

    // 预处理 ST 表
    for (int i = 0; i <= lb(n); ++i)
        for (int j = i != 0 ? 0 : 1; j <= lb(m); ++j)
            for (int x = 1; x + (1 << i) - 1 <= n; ++x)
                for (int y = 1; y + (1 << j) - 1 <= m; ++y)
                    st[x][y][i][j] = i != 0 ? max(st[x][y][i - 1][j], st[x + (1 << (i - 1))][y][i - 1][j])
                                            : max(st[x][y][i][j - 1], st[x][y + (1 << (j - 1))][i][j - 1]);

    // 定义查询函数，用于查询区间 [x1, y1] 到 [x2, y2] 的最大值
    const auto quest = [&st, &lb](int x1, int y1, int x2, int y2) {
        const int i = lb(x2 - x1 + 1), j = lb(y2 - y1 + 1);
        const int x3 = x2 - (1 << i) + 1, y3 = y2 - (1 << j) + 1;
        return max({st[x1][y1][i][j], st[x3][y1][i][j], st[x1][y3][i][j], st[x3][y3][i][j]});
    };

    // 初始化答案为 INT_MAX
    int ans = INT_MAX;

    // 遍历所有可能的 k x k 子矩阵，找到最小的最大值
    for (int i = 1; i + k - 1 <= n; ++i)
        for (int j = 1; j + k - 1 <= m; ++j)
            ans = min(ans, quest(i, j, i + k - 1, j + k - 1));

    // 输出答案
    cout << (ans != INT_MAX ? ans : -1) << '\n';

    return 0;
}
```

---

## 作者：StarsIntoSea_SY (赞：0)

# Solution

二维单调队列板子题。

对于每一个 $k \times k$ 的区间，如果区间有一个格子没有被赋值，那么这个区间就不符合要求，否则就符合。

那么对于一个符合要求的区间，该区损坏就是这片区间的**最大值**，我们所求答案就是这些区间的最大值的最小值。同样的，我们可以记录每个区间最小值，对于没有赋值的格子计为 $-1$，若一个区间最小值为 $-1$，那么这个区间就不符合要求。

考虑使用二维单调队列维护区间最值，可以从行开始，每一行跑一遍单调队列，记录答案。再根据这个答案每一列跑一遍单调队列即可。

时间复杂度 $O(nm)$，常数较大。

# Code


```cpp
#include <stdio.h>
#include <list>
int a,b,n,q;
int dpmax[505][1005],dpmin[505][505];
int map[505][505];
int f_max[505][1005],f_min[505][1005];
int main(){
	scanf("%d%d%d%d",&a,&b,&n,&q);
	for(int i=1;i<=a;++i)
		for(int j=1;j<=b;++j)
			map[i][j]=-1;
	while(q--){
		int u,v,t;
		scanf("%d%d%d",&u,&v,&t);
		map[u][v]=t;
	}
	for(int i=1;i<=a;++i){
		std::list<int> depmax,depmin;
		for(int j=1;j<=b;++j){
			while(!depmax.empty() && map[i][depmax.back()]<map[i][j])
				depmax.pop_back();
			depmax.push_back(j);
			if(depmax.front()<=j-n) 
				depmax.pop_front();
			if(j>=n) dpmax[i][j-n+1]=map[i][depmax.front()];
		}
		for(int j=1;j<=b;++j){
			while(!depmin.empty() && map[i][depmin.back()]>map[i][j])
				depmin.pop_back();
			depmin.push_back(j);
			if(depmin.front()<=j-n)
				depmin.pop_front();
			if(j>=n) dpmin[i][j-n+1]=map[i][depmin.front()];
		}
	}
	b=b-n+1;
	for(int j=1;j<=b;++j){
		std::list<int> depmax,depmin;
		for(int i=1;i<=a;++i){
			while(!depmax.empty() && dpmax[depmax.back()][j]<dpmax[i][j])
				depmax.pop_back();
			depmax.push_back(i);
			if(depmax.front()<=i-n)
				depmax.pop_front();
			if(i>=n) f_max[i-n+1][j]=dpmax[depmax.front()][j];
		}
		for(int i=1;i<=a;++i){
			while(!depmin.empty() && dpmin[depmin.back()][j]>dpmin[i][j])
				depmin.pop_back();
			depmin.push_back(i);
			if(depmin.front()<=i-n)
				depmin.pop_front();
			if(i>=n) f_min[i-n+1][j]=dpmin[depmin.front()][j];
		}
	}
	a=a-n+1;
	int res=2147483647;
	for(int i=1;i<=a;++i)
		for(int j=1;j<=b;++j)
			res=(f_min[i][j]>-1&&f_max[i][j]<res?f_max[i][j]:res);
	printf("%d\n",res==2147483647?-1:res);
}
```

---

## 作者：f_hxr_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF846D)

[双倍经验](https://www.luogu.com.cn/problem/P2216)

[三倍经验](https://www.luogu.com.cn/problem/P9905)

我们先把不会坏点的点，将其坏掉时间设为无穷大。

一个 $k \times k$ 的方框，它坏掉的时间，就是其内部像素的坏掉时间的最大值。

特别地，这个方框里但凡有一个不会坏掉的点，这个方框的最大值就是无穷大。

题目说“只要有一个 $k \times k$ 的方框坏掉，那么这个显示屏就坏掉。”那么我们只要把所有的 $k \times k$ 的方框的“坏掉时间”都拿出来，取最小值即可。

坏掉时间怎么求？这是一个二位滑动窗口问题。可以直接套用[三倍经验](https://www.luogu.com.cn/problem/P9905)，这里我把过程再写一遍。

首先，对每一行开个长为 $k$ 的滑动窗口，这样我们就得到了每一行的每个滑动窗口的最大值。

然后将每 $k$ 个窗口拼在一起，就是一个 $k \times k$ 的窗口了。

怎么将窗口拼在一起？同样可以用单调队列。将最大值单独拎出来，再做一遍滑动窗口就行了。

不会滑动窗口出门左转[膜版区](https://www.luogu.com.cn/problem/P1886)或[ NOI Online](https://www.noi.cn/pxsp/2020-09-22/717311.shtml)。

下面是 AC 代码。注意在笔者写这篇题解的时候 CF 升级到了 C++20，所以如果你 UKE 把 C++ 版本开到 20 或以上试试。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL maxn=1003;
const LL inf=1e9+7;
LL N,M,R,S,Q,qwq=1e18+7;
LL a[maxn][maxn],ans[maxn][maxn],ans2[maxn][maxn],fo[maxn];
struct dp{
	LL dat[maxn],head=1,tail=0;
	bool empty(){return head>tail;}
	void push_back(LL xx){dat[++tail]=xx;}
	void pop_front(){++head;}
	void pop_back(){--tail;}
	void clear(){head=1;tail=0;dat[1]=dat[0]=0;}
	LL front(){return dat[head];}
	LL back(){return dat[tail];}
}q[maxn],q3;
LL get(LL inx,LL xx){//横向滑动窗口:长度:S 
	LL ret=-1;
	while(!q[inx].empty()&&q[inx].front()<xx-S+1)q[inx].pop_front();
	while(!q[inx].empty()&&a[inx][q[inx].back()]<=a[inx][xx])q[inx].pop_back();
	q[inx].push_back(xx);
	if(xx>=S)ret=q[inx].front();
	return ret;
}
int main(){
	scanf("%lld%lld",&N,&M);
	for(LL i=1;i<=N;i++)for(LL j=1;j<=M;j++)a[i][j]=inf;
	scanf("%lld",&R);S=R;
	scanf("%lld",&Q);
	while(Q--){
		LL x,y,t;scanf("%lld%lld%lld",&x,&y,&t);a[x][y]=t;
	}
	for(LL i=1;i<=M;i++){//从前往后推进 
		q3.clear();fo[0]=0;
		for(LL j=1;j<=N;j++){//枚举每一行:处理最小值 
			LL p=get(j,i);
			if(p==-1){fo[0]=1;continue;}
			fo[j]=a[j][p];
		}
		if(fo[0])continue;
		for(LL j=1;j<=N;j++){
			while(!q3.empty()&&q3.front()<j-R+1)q3.pop_front();
			while(!q3.empty()&&fo[q3.back()]<=fo[j])q3.pop_back();
			q3.push_back(j);
			if(j<R)continue;
			qwq=min(qwq,fo[q3.front()]);
		}	
	}
	printf("%lld",qwq==inf?-1:qwq);
	return 0;
}
```

---

## 作者：osfly (赞：0)

提供一种 $O(nm\log nm)$ 的做法。

答案单调性显然：

如果这个显示器第 $i$ 秒坏掉，则 $i+1$ 秒的时候这个显示器也一定是坏掉的。

那么就可以对答案进行二分，利用二维前缀和就可以做到 $O(nm\log 10^9)$ ，已经能通过此题。

但是我不满意。有什么方法能压一下吗？

其他题解的做法我一开始没想到，于是我 ~~拉屎的时候~~ 想到先对时间离散化一下就能把 $\log10^9$ 这个常数压到 $\log nm$。

$\log 10^9\approx 27,\log (nm)_{max}\approx18$，还行吧。

~~跑得还没 $O(nm\log 10^9)$ 快，怎么回事 /fn。~~

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=510;
const int inf=2e9;

int n,m,k,q;
int t[N][N];

int lsh[N*N],tot;

int sum[N][N];

bool chk(int x)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(t[i][j]<=x);
	for(int i=k;i<=n;i++)
		for(int j=k;j<=m;j++)
			if(sum[i][j]+sum[i-k][j-k]-sum[i][j-k]-sum[i-k][j]==k*k) return 1;
	return 0;
}

int main()
{
	lsh[0]=-1;
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) t[i][j]=inf;
	while(q--)
	{
		int x,y,T;
		scanf("%d%d%d",&x,&y,&T);
		t[x][y]=T;
		lsh[++tot]=T;
	}
	sort(lsh+1,lsh+1+tot);
	tot=unique(lsh+1,lsh+1+tot)-lsh-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(t[i][j]!=inf) t[i][j]=lower_bound(lsh+1,lsh+1+tot,t[i][j])-lsh;
	int l=1,r=tot,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(chk(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d",lsh[ans]);
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

考虑二分时间，然后把这个时间之前的点标记在数组中，问题变为求矩阵中最大的全是 $1$ 的矩阵，这个可以用简单的动态规划求。

至于咋做可以看看 [ABC311E](https://www.luogu.com.cn/problem/AT_abc311_e)。

然后判断一下是否超过 $k$ 就行了。

或者你也可以直接枚举 $k\times k$ 的子矩阵，看看是否全是 $1$，可以用二维前缀和实现。

时间复杂度都是 $\mathcal O(nm\log R)$ 的，$R$ 表示时间的值域。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=505;
const LL inf=1e9;
LL n,m,k,d,a[N][N],f[N][N],x[N*N],y[N*N],t[N*N];
bool pd(LL X)
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)a[i][j]=f[i][j]=0;
	}
	for(int i=1;i<=d;i++)
	{
		if(t[i]<=X)a[x[i]][y[i]]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!a[i][j])continue;
			f[i][j]=min({f[i-1][j-1],f[i-1][j],f[i][j-1]})+1;
			if(f[i][j]>=k)return true;
		}
	}
	return false;
}
int main()
{
	cin>>n>>m>>k>>d;
	for(int i=1;i<=d;i++)
	{
		cin>>x[i]>>y[i]>>t[i];
	}
	LL l=0,r=inf,ans=-1;
	while(l<=r)
	{
		LL mid=l+r>>1;
		if(pd(mid))
		{
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	cout<<ans<<endl;
}
```

---

