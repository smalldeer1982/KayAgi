# [ABC210E] Ring MST

## 题目描述

- 给定一张 $n$ 个点的图，顶点的编号为 $[0, n - 1]$，同时给出两个长度为 $m$ 的数组 $a_1, a_2, \cdots, a_m$ 和 $b_1, b_2, \cdots, b_m$。

- 初始时图中并没有任何边，你可以按照以下操作加边：选择一个 $1 \le i \le m$ 和一个 $0 \le x < n$，并在顶点 $x$ 和顶点 $(x + a_i) \bmod n$ 中添加一条长度为 $b_i$ 的边。

- 你现在想要知道，你添加的边的长度总和至少为多少，才能使得整个图连通?如果无论如何都不能使整个图连通，输出 `-1`。

## 说明/提示

- 对于 $30 \%$ 的数据：$1 \le n, m \le 1000, 1 \le b_i \le 10^9$。

- 对于 $60 \%$ 的数据：$1 \le n, m \le 10^5, 1 \le b_i \le 10^9$。

- 对于 $100 \%$ 的数据：$1 \le n \le 10^9, 1 \le m \le 10^5, 1 \le b_i \le 10^9$。

翻译提供者：[Sunrize](https://www.luogu.com.cn/user/502658)。

## 样例 #1

### 输入

```
4 2
2 3
3 5```

### 输出

```
11```

## 样例 #2

### 输入

```
6 1
3 4```

### 输出

```
-1```

# 题解

## 作者：hswfwkj_ (赞：6)

贪心，按照 $c$ 排一遍序，如果 $a$ 和 $n$ 互质，非常好办，那么我们不断选取当前这个数，一定构成一个能够构成关于 $n$ 的完全剩余类。

不互质？是个问题。

根据上面的思考，可以进一步的得到结论，若是 $\gcd(a_1, a_2, \cdot\cdot\cdot,a_{m - 1},a_m) > 1$，则无解，因为这样我们是凑不出来的。

先在前面连尽可能多的边，那么不难发现，对于 $n$ 和 $a_i$，我们每次合并所连上的点，最后剩下的一定是 $\gcd(n, a_i)$ 个点。然后我们便将问题成功进行转化，我们得到了一共 $a_i$ 个同余类，我们便又将问题转化为如何使得有 $a_i$ 个点，编号为 $0$ 至 $a_i - 1$ 的图联通？按照上面的方法解决即可。然后不难发现，同余类的个数不断在取 $\gcd$，当 $\gcd$ 为 $1$ 时便代表整张图已经联通，统计可以结束。

代价？每次连接两个点付出 $c_i$ 的代价，同时点个数减少一，那么只需要拿上次的同余类个数减去这次的同余类个数再乘上 $c_i$ 不就行了？

时间复杂度 $O(m \log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
struct node {
	int a, c;
} t[100005];
inline bool cmp(node x, node y) {return x.c < y.c;}
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
		cin >> t[i].a >> t[i].c;
	sort(t + 1, t + m + 1, cmp);
	long long ans = 0;
	for(int i = 1; i <= m; i++)
	{
		ans += 1ll * (n - __gcd(n, t[i].a)) * t[i].c;
		n = __gcd(n, t[i].a);
		if(n == 1) break;
	}
	if(n > 1) cout << -1;
	else cout << ans;
	return 0;
}
```

---

## 作者：Ray662 (赞：2)

### 题目描述

- 给定一张 $n$ 个点的图，顶点的编号为 $[0, n - 1]$，同时给出两个长度为 $m$ 的数组 $a_1, a_2, \cdots, a_m$ 和 $b_1, b_2, \cdots, b_m$。

- 初始时图中并没有任何边，你可以按照以下操作加边：选择一个 $1 \le i \le m$ 和一个 $0 < x < n$，并在顶点 $x$ 和顶点 $(x + a_i) \bmod n$ 中添加一条长度为 $b_i$ 的边。

- 你现在想要知道，你添加的边的长度总和至少为多少，才能使得整个图连通?如果无论如何都不能使整个图连通，输出 `-1`。

- $1 \le n \le 10^9, 1 \le m \le 10^5, 1 \le b_i \le 10^9$。

---

### 分析

首先我们可以想到把 $(x, (x + a_i) \bmod n)$ 看成一条边然后答案就是最小生成树，使用 Kruskal，时间复杂度是 $O(nm \log nm)$。

模拟 Kruskal 的算法过程。把 $(a_i, b_i)$ 按照 $b_i$ 升序排序，然后考虑尽可能的用较前的 $(a_i, b_i)$ 来建边。

假设只加了 $(a_1, b_1)$ 的边，那么有一个结论：令 $g = \gcd(a_1, n)$，则所有模 $g$ 相同的节点均可以连到同一个连通块，并且会有 $g$ 个这样的连通块。

以此类推，如果用了前 $i$ 种边，则令 $g = \gcd(a_1, a_2, \cdots, a_i, n)$，上述结论仍然成立。

当 $g = 1$ 时，图就联通了。令 $g_i$ 表示加入前 $i$ 种边之后的 $g$ 值，边权之和只要用 $\sum_{i = 1}^m(g_{i - 1} - g_i) \times b_i$ 计算即可。时间复杂度 $O(m \log n)$。

---

### 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define _for(i, a, b)  for (int i = (a); i <= (b); i ++ )
#define _all(i, a, b)  for (int i = (a); i >= (b); i -- )
using namespace std;
const int N = 1e5 + 5;
int T, n, m, ans, a[N], b[N];
vector<PII > v;
signed main() {
	ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	v.clear();
	_for (i, 1, m) {
		int x, y;
		cin >> x >> y;
		v.pb(mp(y, x));
	}
	sort(v.begin(), v.end());
	int ans = 0;
	int g = n;
	_for (i, 0, m - 1) {
		int tmp = g;
		g = __gcd(g, v[i].S);
		ans += (tmp - g) * v[i].F;
	}
	if (g != 1)  cout << "-1\n";
	else  cout << ans << endl;
	return 0;
}
```

---

## 作者：xiaoPanda (赞：1)

## ABC210E - Ring MST(*1618)
### Problem
给出一个图，每个点标号为 $0$ 到 $n-1$，有 $m$ 种操作，每次操作可以连点 $x$ 和 $(x+a_i)\bmod n$，代价为 $c_i$，每种操作可以使用无数次，问将图连通的最小费用。

### Solution
将图连通的最小费用也就是图的最小生成树，但注意到 $n$ 很大，显然不能直接暴力。

最小生成树的 Kruskal 算法的核心是将边权小的边连接，放到这题上，也可以将边权排序，尽量使用边权小的边，答案一定是最优。

考虑每个点肯定不行，所以只考虑连通块数量，假设使用操作 $i$ 前连通块有 $x$ 个，使用后连通块有 $y$ 个，根据贪心原则，在连通块内的点一定不会再连边，所以这时候要连 $x-y$ 条边，代价为 $c_i*(x-y)$。

这时候难点就是如何计算操作后连通块数量，如果单独计算某一操作后的连通块数量，会有重复的，所以我们计算使用前 $i$ 操作，那么如果 $u,v$ 相连，存在一组解 $(k_1,k_2,...,k_i)$ 满足 $u=(v+k_1* a_1+k_2* a_2+...+k_i* a_i)\bmod n=v+k_1* a_1+k_2* a_2+...+k_i* a_i+h* n$，相当于可以通过之前的操作一次一次建边使得其相连。

令 $d=\gcd(a_1,a_2,...,a_i,n)$，那么 $a_i=w_i* d$，所以 $u=v+k_1* w_1* d+k_2* w_2* d+...+k_i* w_i* d+h* p* d=v+td$ 即 $v\equiv u(\bmod d)$，注意到一个数与 $d$ 取余有 $d$ 种结果，也就是存在 $d$ 个连通块，与之前的相减，即可得出新建边的数量，当只剩 $1$ 个连通块就是求出了答案。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+7;
struct node
{
    int x,y;
}a[N];
bool cmp(node x,node y)
{
	return x.y<y.y;
}
main()
{
	int n,m,d,last,ans=0;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	scanf("%lld%lld",&a[i].x,&a[i].y);
	sort(a+1,a+m+1,cmp);
	d=last=n;
	for(int i=1;i<=m;i++)
	{
		d=__gcd(d,a[i].x);
		ans+=(last-d)*a[i].y;
		if(d==1)break;
		last=d;
	}
	if(d!=1)puts("-1");
	else printf("%lld",ans);
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

由于 RMJ 坏了，[这是我的 AC 记录](https://atcoder.jp/contests/abc210/submissions/64954231)。       

为了使用最少数量的边，我们只要连接 $n-1$ 条边，同时尽量使边权小的边用的多一点，边权大的边用的少一点。     
我们把操作们按照 $b_i$ 从小到大排序，然后尽可能多的连接，但是又要让每一条边都作出贡献。   
什么叫“作出贡献”？如果把用边相连在一起的点们看作一个个集合，“有贡献”就相当于把两个集合连在一起，使它们被合并为一个集合。      
那么具体有多少条边呢？~~请看 VCR。~~ 请看下面的例子，比如有 $10$ 个点，$a=4$ 的时候：
![](https://cdn.luogu.com.cn/upload/image_hosting/39x89auv.png)

这个连线可以分为三个阶段：

- `0-4-8` 的时候，它还没有进入新一轮轮回。可以看到，这几个数字对 $4$ 取模的余数都是一样的。
- `8-2-6` 的时候，它进入了一个新的轮回。$8$ 对 $4$ 取模的余数是 $0$，但是 $2$ 对 $4$ 取模的余数是 $2$。这一条边使得所有除以 $4$ 余 $0$ 的数和除以 $4$ 余 $2$ 的数被合并进了同一个集合。   
这个 $2$ 是什么来头？观察到 $\gcd(10,4)=2$。再观察到被连接的数字们都是偶数，也就是说，我们可以猜想对于一个 $a$，它可以使得所有对 $\gcd(n,a)$ 取模相同的数字合并在一起。    
经过手动模拟，我们发现这个规律是对的。~~为什么呢？我似乎不会证明。如果有会证明的欢迎交流。~~
- `6-0` 的时候，我们发现它们原本已经在同一个集合内了，再往下走会重复到第一步的过程，因此不用继续往下走。

我们数一数有多少条边。一共有 $10 \div 2=5$ 个数被连接，所以有 $4$ 条边。这就是把一组数字连在一起需要的贡献。    
但是我们只考虑了一组数，显然不只有一组数。那么具体有几组数呢？前文分析说，对于一个 $a$，它可以使得所有对 $\gcd(n,a)$ 取模相同的数字合并在一起。对 $\gcd(n,a)$ 取模的结果有 $\gcd(n,a)$ 种情况，因此合并结束之后，会剩下 $\gcd(n,a)-1$ 组。   
每一组有 $n \div \gcd(n,a)-1$ 条边，每一条边的权值为 $b$，相乘就是这一次操作得到的答案。   

合并完之后，我们得到了几个集合。下一步我们要做的就是把这些集合们再次合并。这个时候，一个集合我们可以看作一个“大的点”。于是问题变成了通过下一个操作，把 $\gcd(n,a)$ 个点连在一起。这就是和前面一样的问题了，只需要把 $n$ 赋值为 $\gcd(n,a)$，然后循环回前面的操作即可。   
如果某一次合并之后 $n=1$，那么全部的点都在同一个集合内，合并就算完成了。    
如果 $m$ 个操作都用完了，$n$ 还是 $\not=1$，那么就证明无论如何都不能使图连通。   

参考代码可以看上面的 AC 记录。

---

## 作者：guozhetao (赞：0)

## 链接
[洛谷相应链接](https://www.luogu.com.cn/problem/AT_abc210_e?contestId=180222)
 [
atcoder 相应链接](https://atcoder.jp/contests/abc210/tasks/abc210_e)

## 题意
给 $n(1 \leq n \leq 10^9)$ 个点的图，并给长度为 $m(1 \leq m \leq 10^5)$ 的两个数组 $a,b(1 \leq a_i \leq n - 1,1 \leq b_i \leq 10^9)$。

每次可选择在点 $x(1\leq x\leq n)$ 和 $(x + a_i)\bmod n$ 中添加一个长度为 $b_i$ 的边，问添加的边的长度总和至少为多少，才能使得整个图连通，不连通输出 `-1`。
##  思路
考虑 $m = 1$ 时，如果要建成联通图，必须要让 $\gcd(n,a_1) = 1$，否则会发生如下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/0n6zmkgz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果 $m > 1$ 则同理可得当 $\gcd(n,a_1,a_2\cdots a_m) = 1$ 时有解。这样我们已经解决了判断无解的情况。

对于任意一个 $i$，可知最多可将剩下的 $p$ 个点合并成剩下 $\gcd(p,a_i)$ 个点，我们先按照 $b_i$ 大小排序，对于每一次操作连通块的数量都由 $p \gets \gcd(p,a_i)$，则 $ans \gets ans + (p - \gcd(p,a_i)) \times b_i$。若有解，最后输出 $ans$ 即可。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int gcd(int x,int y) {
	return y?gcd(y,x % y):x;
}
struct edge{
	int a,b;
	friend bool operator <(edge x,edge y) {
		return x.b < y.b;
	}
}node[200005];
int ans = 0;
signed main() {
	cin >> n >> m;
	for(int i = 1;i <= m;i++) cin >> node[i].a >> node[i].b;
	sort(node + 1,node + m + 1);
	for(int i = 1;i <= m;i++) {
		ans += (n - gcd(n,node[i].a)) * node[i].b;
		n = gcd(n,node[i].a);
		if(n <= 1) {
			cout<<ans<<endl;
			return 0;
		}
	}
	cout<<"-1"<<endl;
	return 0;
}

```

---

## 作者：SpringFullGarden (赞：0)

## 题意

有一个 $n$ 个点的图，顶点的编号为 $[0, n - 1]$，同时有两个长度为 $m$ 的数组 $a_1, a_2, \cdots, a_m$ 和 $b_1, b_2, \cdots, b_m$。

对于任意的 $1 \le i \le m$ 和 $0 \le x < n$，顶点 $x$ 和顶点 $(x + a_i) \bmod n$ 有一条长度为 $b_i$ 的边。

若图联通，求最小生成树的各边的长度之和，否则输出 $-1$。

## 思路

按照 Kruskal 算法的想法，先按照 $b_i$ 排序。

发现对于每一个 $i$，将边全部加完之后会形成若干个连通块。设上一次连完边后的连通块的数量为 $n$，每个连通块的顶点数量为 $k$，则连通块的数量为 $\frac{n}{k}$。

在一个连通块内，对于任意一个顶点 $x$，$x + a_i \cdot k \equiv x \pmod n$。

解得 $a_i \cdot k \equiv 0 \pmod n$。为了使 $\frac{n}{k}$ 最小，所以 $k$ 取最大值为 $\frac{n}{\gcd(a_i, n)}$。

所以环的数量为 $\frac{n}{k} = \gcd(a_i, n)$。

在一个连通块中的点不用连边，为了使连通块数量变为 $\gcd(a_i, n)$ 个，就要连 $n - \gcd(a_i, n)$ 条边，所以 $ans \gets ans + (n - \gcd(a_i, n)) \cdot b_i$。

若 $\gcd(a_i, n) = 1$，图就联通了；否则 $n \gets \gcd(a_i, n)$。

### 代码

```cpp
struct node {
	ll a, b;
} s[100005];
bool cmp(node x, node y) {
	return x.b < y.b;
}
ll gcd(ll x, ll y) {
	return (!y ? x : gcd(y, x % y));
}
signed main() {
	ll n = rd(), m = rd(), ans = 0;
	for(ll i = 1; i <= m; i++) s[i].a = rd(), s[i].b = rd();
	sort(s + 1, s + m + 1, cmp);
	for(ll i = 1; i <= m; i++) {
		ll g = gcd(s[i].a, n);
		ans += (n - g) * s[i].b;
		n = g;
		if(k == 1) return cout << ans, 0; 
	} 
	cout << -1;
	return 0;
}
```

---

