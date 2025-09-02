# 选择两个，吃掉一个

## 题目描述

一个盒子里有 $N$ 个球，每个球上写有一个介于 $1$ 和 $M-1$ 之间的整数。对于 $i=1,2,...,n$，第 $i$ 个球上写的整数是 $A_i$。

当盒子里剩下两个或更多的球时，高桥将重复以下操作：

- 首先，任意选择两个球；
- 然后，得到一个分数，该分数等于 $(x^y+y^x) \bmod M$ ，其中 $x$ 和 $y$ 是两个球上写的整数，$x \bmod M$ 表示 $x$ 除以 $M$ 得到的余数；
- 最后，任意选择其中一个球，吃掉它，并将另一个球放回盒子中。

打印高桥能获得的最大总分。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的测试点数据，保证：

- $2 \le N \le 500$
- $2 \le M \le 10^9$
- $1 \le A_i \le M-1$
- 输入的所有数值均为整数。

#### 样例 $1$ 解释

1. 从盒子中取出第一个和第三个球以获得 $(4^3+3^4) \bmod 10 = 5$ 分。然后，吃掉第一个球，将第三个球放回盒子中。现在，盒子里有第二、第三和第四个球。
2. 从盒子中取出第三和第四个球以获得 $(3^2+2^3) \bmod 10 = 7$ 分。然后，吃掉第三个球，将第四个球放回盒子中。现在，盒子里有第二和第四个球。
3. 从盒子中取出第二个和第四个球以获得 $(2^2+2^2) \bmod 10 = 8$ 分。然后，吃掉第三个球，将第四个球放回盒子中。现在，盒子里有第二和第四个球。

综上，高桥一共获得了 $5+7+8=20$ 分，可以证明这是可能的最大值。

## 样例 #1

### 输入

```
4 10
4 2 3 2```

### 输出

```
20```

## 样例 #2

### 输入

```
20 100
29 31 68 20 83 66 23 84 69 96 41 61 83 37 52 71 18 55 40 8```

### 输出

```
1733```

# 题解

## 作者：Neil_Qian (赞：7)

# [ABC282E] Choose Two and Eat One 题解
给出 $n$ 个数 $a_i$ 以及一个数 $m$，每次选出两个数 $x,y$，可以获得 $(x^y+y^x)\mod m$ 的分值，并选择其中一个数扔掉。直到只有一个数为止。求可以获得的最大分值。

一看数据范围，$n$ 才 $500$，不妨用 $O(n^2\log m)$ 的时间先把任意两个数产生的分支算出来，加上快速幂即可，用一个二维数组记录一下。对于 $n=4$ 的数据，我们画出如下图：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/wfz3fc1g.png)

我们选择两个点看看会发生什么：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/krwz5x9t.png)

这时候我们扔掉谁呢？题目上没有限制，所以应该我们自己决定。我们假设把第二个扔掉：

![图3](https://cdn.luogu.com.cn/upload/image_hosting/dx99khe9.png)

我们此时的分值为蓝色部分的分值。我们把它看成一张图的话，会发现：因为一条边选了以后要删除一个顶点，所以一定不能选择出一个环，想一想是不是。对于一棵树，令它就是答案，我们可以构造如下方案：在选择叶结点的边时，扔掉叶结点，然后之前叶结点的父亲就变成了叶结点，以此类推。

综上，用一个**最大生成树**即可。

时间复杂度预算分值 $O(n^2\log m)$，最大生成树 $n^2$ 个结点，时间复杂度 $O(n^2\log(n^2))$，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
struct Node{
	ll x,y,z;
	bool operator <(const Node b){return z>b.z;}//重载运算符
};
ll n,MOD,a[502],res,f[502],ans,cnt;vector<Node> v;
inline ll qp(ll a,ll b){//快速幂
	res=1;
	while(b){
		if(b&1)(res*=a)%=MOD;//二进制这一位上是1，要乘上
		(a*=a)%=MOD,b>>=1;//升高底数，降低次数
	}
	return res;
}
inline ll fnd(ll x){return f[x]==x?x:f[x]=fnd(f[x]);}//并查集
int main(){
	scanf("%lld%lld",&n,&MOD);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),f[i]=i;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)v.push_back
		(Node{i,j,(qp(a[i],a[j])+qp(a[j],a[i]))%MOD});//预算每两个点之间的分值，注意要取模
	sort(v.begin(),v.end());//最大生成树：排序
	for(Node t:v)if(fnd(t.x)!=fnd(t.y)){//遍历每一条边：不会构成环
		f[fnd(t.x)]=fnd(t.y),cnt++,ans+=t.z;//合并，统计边数和答案
		if(cnt==n-1){printf("%lld\n",ans);break;}//树已经生成了，输出答案
	}
	return 0;
}
```

总结一下，这道题的代码难度并不大，但思维性很强，想一会儿才能想到最大生成树，写起来就比较快。

---

## 作者：ForgotDream_CHN (赞：5)

# AT-ABC282E Choose Two And Eat One

这道题的思路真的逆天，考场上没想出来，赛后在高二巨佬 [_cyle_King](https://www.luogu.com.cn/user/582035) （orzorz）的帮助下 A 掉了，感觉思路很巧妙，于是来水一发题解。

### 题意

给定一个长度为 $N$ 的整数序列 $A$ 与一个整数 $M$，每次选取 $A$ 中的两个元素 $x, y$ 并产生 $(A_x^{A_y} + A_y^{A_x}) \bmod M$ 的贡献然后删去这两个元素中的其中一个，求能够产生的最大贡献值。

### 思路

第一眼看上去，这道题似乎无法直接维护，但是我们可以通过巧妙的变形来解决这个问题。

我们考虑建图来解决这个问题，对于 $A$ 中的每一对元素 $i, j$，在 $i, j$ 间连一条权值为 $(A_i^{A_j} + A_j^{A_i}) \bmod M$ 的边，然后跑一遍最大生成树，求出的权值之和就是答案。

那么为什么这样求得的就是最大答案呢？

不难看出，如果按上述方法建图，那么任意一个消去的序列都可以看作原图的一个生成树。
我们拿样例举例。

这是样例 1 对应的图：

![原图](https://s1.ax1x.com/2022/12/18/zbdKpD.png)


而按照样例说明建出来的图，长这个样子：

![样例对应的图](https://s1.ax1x.com/2022/12/18/zbdnfO.png)

消去的顺序为 $1 \rightarrow 3 \rightarrow 2 \rightarrow 4$，就是原图的一棵生成树嘛。

其实这是可以证明的。  
一共要消去 $N - 1$ 个点，也就是选取对应的 $N - 1$ 条边，又因为每连一次边都要删去一个点，所以任意一个节点都不会与更早删去的节点相连，那么图中不会存在环，而原图中有 $N$ 个点，那么对应的图不就是一棵树吗？

### 代码

奉上我丑陋的代码~~逃~~。

由于 $N \le 500$，我们可以直接暴力连边（赞美良心出题人）。  
由于这是个稠密图，$N$ 的范围也不大，所以用邻接矩阵的 Prim 比较合适。我的是直接从模板题那里复制过来的 Prim，因为懒，边权是原来边权的相反数，这样求最小生成树就行了。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;

const int N = 550;
int n, m, a[N], cnt;
ll ans;

int fastPower(int base, int p, int m) {
	int res = 1;
	while(p) {
		if (p & 1) res = ((ll)res * base) % m;
		base = ((ll)base * base) % m;
		p >>= 1;
	}
	return res;
}

int graph[N][N], f[N];
bool used[N];

void prim() {
	int cur = 1;
	memset(f, 0x7f, sizeof f);
	f[1] = 0;
	for (int i = 1; i <= n; i++) {
		int minn = 0x7f7f7f7f;
		for (int j = 1; j <= n; j++) 
			if (!used[j] && f[j] < minn) minn = f[j], cur = j;
		ans += minn, used[cur] = true;
		for (int j = 1; j <= n; j++) 
			if (!used[j] && graph[j][cur] < f[j]) f[j] = graph[j][cur];
	}
	cout << -ans << endl;
	return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
			graph[i][j] = graph[j][i] = -(fastPower(a[i], a[j], m) + (ll)fastPower(a[j], a[i], m)) % m;
	prim();
	return 0;
}
```



---

## 作者：zzx0102 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc282_e)

看到了 $1\leq n \leq 500$，说明此题是用常数较大的 $O(n^2)$ 或 $O(n^3)$ 做的。

既然题目的意思是求最小生成树，那么我们就考虑 kruskal 算法。

由于 $n$ 比较小，所以可以爆搜所有的边，也才 $O(n^2)$，求边权可以用快速幂 $O(\log n)$  求解

那么总复杂度是 $O(n^2\log n)$，是可以 AC 的

$code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
#define int long long 
namespace SlowIO{
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
} using namespace SlowIO;
CI N = 510;
int n, P, a[N];
int Pow(int a, int b) {
	int ans = 1;
	W(b) {
		if(b & 1) ans = ans * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return ans;
}
struct edge{
	int a, b, c;
	I edge() {}
	I edge(int x, int y, int z) {a = x, b = y, c = z;}
	bool operator <(const edge &cmp) const {return c > cmp.c;}
} E[N * N]; int tot;
struct bcj{
	int rt[N];
	I int find(int x) {return rt[x] == x ? x : rt[x] = find(rt[x]);}
	I void merge(int a, int b) {rt[find(b)] = find(a);}
} B;
signed main() {
	Read(n, P); for(int i = 1; i <= n; i++) Read(a[i]);
	for(int i = 1; i <= n; i++) B.rt[i] = i;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			E[tot++] = edge(i, j, (Pow(a[i], a[j]) + Pow(a[j], a[i])) % P);
	sort(E, E + tot);
	int ans = 0;
	for(int i = 0; i < tot; i++) {
		int a = E[i].a, b = E[i].b, c = E[i].c;
		if(B.find(a) != B.find(b)) {
			ans += c;
			B.merge(a, b);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Phartial (赞：2)

考虑把每次选择的两个点连边，由于你只会进行 $n-1$ 次操作，所以最后你会得到一棵树。那么我们就可以建出一个完全图，跑一遍最大生成树即可。

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using LL = long long;
using Pii = pair<int, int>;

const int kN = 501;

int n;
LL m, a[kN], d[kN][kN], ans, f[kN];
bool v[kN];
vector<Pii> e;

LL P(LL b, LL e) {
  LL s = 1;
  for (; e; e >>= 1, b = b * b % m) {
    (e & 1) && (s = s * b % m);
  }
  return s;
}
int F(int x) { return x == f[x] ? x : (f[x] = F(f[x])); }

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      d[j][i] = d[i][j] = (P(a[i], a[j]) + P(a[j], a[i])) % m;  // 求出边权
      e.emplace_back(i, j);
    }
  }
  sort(e.begin(), e.end(), [](Pii i, Pii j) { return d[i.first][i.second] > d[j.first][j.second]; });
  iota(f + 1, f + n + 1, 1);
  for (Pii i : e) {  // 最大生成树
    if (F(i.first) != F(i.second)) {
      ans += d[i.first][i.second];
      f[F(i.first)] = F(i.second);
    }
  }
  cout << ans;
  return 0;
}
```

---

