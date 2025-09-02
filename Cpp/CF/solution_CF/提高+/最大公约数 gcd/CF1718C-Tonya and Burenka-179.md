# Tonya and Burenka-179

## 题目描述

Tonya 收到了一个长度为 $ n $ 的数列，写在了他的生日卡片上。出于某种原因，这个卡片原来是一个循环数组，所以严格位于第 $n$ 个元素右侧的元素的下标是 $ 1 $ 。Tonya 想更好地研究它，所以他买了一个机器人 `Burenka-179`。

Burenka 的程序是一个数对 $ (s, k) $ ，其中 $ 1 \leq s \leq n $ ， $ 1 \leq k \leq n-1 $ 。请注意，$k$ 不能等于 $n$。最初，Tonya 将机器人放在数组 $ s $ 的位置。之后，Burenka 在数组中准确地向前或者向后走了 $ n $ 步。如果在开始的时候，Burenka 站在 $i$ 的位置，那么会发生以下情况：

1. 数字$a_{i}$被加入到了到程序的有用值中。
2. Burenka 向右移动了 $k$ 步（ 一般情况下 $ i := i + k $ ，如果 $ i $ 变得大于 $ n $ ，则 $ i := i - n $ ）。

如果任何程序的初始有用值为 $ 0 $ ，则帮助 Tonya 算出程序最大可能的有用值。

此外，Tonya 的朋友 Ilyusha 要求他更改数组 $ q $ 次。每次他想为给定下标 $ p $ 和值 $ x $ 分配 $ a_p := x $ 。在每次进行这些更改之后，你得再次算出程序的最大可能有用值。

## 说明/提示

在第一个测试用例中，最初时和更改后时，可以在 $ s = 1 $ 、 $ k = 1 $ 或 $ s = 2 $ 、 $ k = 1 $ 处找到答案。

在第二个测试用例中，最初，当 $ s = 1 $ , $ k = 2 $ 或 $ s = 3 $ , $ k = 2 $ 时得到答案。在第一次更改之后，在 $ s = 2 $ , $ k = 2 $ 或 $ s = 4 $ , $ k = 2 $ 处找到答案。

## 样例 #1

### 输入

```
4
2 1
1 2
1 3
4 4
4 1 3 2
2 6
4 6
1 1
3 11
9 3
1 7 9 4 5 2 3 6 8
3 1
2 1
9 1
6 3
1 1 1 1 1 1
1 5
4 4
3 8```

### 输出

```
3
5
14
16
24
24
24
57
54
36
36
6
18
27
28```

# 题解

## 作者：Alex_Wei (赞：13)

> [CF1718C Tonya and Burenka-179](https://www.luogu.com.cn/problem/CF1718C)

根据经典结论，在长为 $n$ 的环上从任意位置开始每步跳 $k$ 个位置，路径形成长度为 $L = \dfrac n {\gcd(n, k)}$ 的环，环上每个节点模 $\gcd(n, k)$ 同余。因此对于给定 $(s, k)$，其贡献即 $\gcd(n, k)\sum\limits_{i \equiv s\pmod {\gcd(n, k)}} a_i$。

一个朴素的想法是对 $n$ 的所有不等于 $n$ 的约数 $d$ 以及所有 $j\in [0, d)$，求出 $f(j, d) = d\sum\limits_{i\equiv j\pmod d} a_j$。则 $\max f$ 即答案。

因为单点修改时需要对所有 $d$ 修改 $f(p\bmod d, d)$，所以时间复杂度 $\mathcal{O}(nd(n)\log n)$，无法通过。

但我们注意到，若当前环长为 $P$ 且 $P$ 不是质数，那么考虑 $P$ 的某个真因数 $D$ 以及所有长度为 $D$ 的 $\dfrac P D$ 个子环。由于这些子环的贡献的平均值等于当前环的贡献，所以存在长为 $D$ 的子环不劣于当前环。因此只需考虑所有质数环长，即只需对使得 $\dfrac n d$ 为质数的 $d$ 维护 $f(j, d)$。

时间复杂度 $\mathcal{O}(n\omega(n)\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 2e5 + 5;
int n, q, a[N], d[8];
ll f[8][N];
multiset<ll> s;
void solve() {
  s.clear();
  cin >> n >> q;
  for(int i = 1; i <= n; i++) cin >> a[i];
  int tmp = n, cnt = 0;
  for(int i = 2; i <= tmp; i++)
    if(tmp % i == 0) {
      d[++cnt] = n / i;
      while(tmp % i == 0) tmp /= i;
    }
  for(int i = 1; i <= cnt; i++) {
    for(int j = 0; j < d[i]; j++) f[i][j] = 0;
    for(int j = 1; j <= n; j++) f[i][j % d[i]] += a[j];
    for(int j = 0; j < d[i]; j++) s.insert(d[i] * f[i][j]);
  }
  cout << *s.rbegin() << "\n";
  for(int i = 1; i <= q; i++) {
    int p, x;
    cin >> p >> x;
    for(int j = 1; j <= cnt; j++) {
      s.erase(s.find(d[j] * f[j][p % d[j]]));
      f[j][p % d[j]] += x - a[p];
      s.insert(d[j] * f[j][p % d[j]]);
    }
    cout << *s.rbegin() << "\n";
    a[p] = x;
  }
}
int main() {
  ios::sync_with_stdio(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：Leasier (赞：2)

不难发现题目想让你求 $\displaystyle\sum_{i = 0}^n a_{(s + ik) \bmod n}$ 的最大值。

注意到令 $k \leftarrow \gcd(k, n)$ 与上式等价，于是我们实际上只需要枚举所有 $k \mid n$。

又注意到 $i \geq \frac{n}{k}$ 时会循环，实际上上式等于 $k \displaystyle\sum_{i = 0}^{\frac{n}{k} - 1} a_{s + ik}$。

于是现在我们会做一次询问的情况了，即我们可以直接枚举所有 $n$ 的非自己的因数和 $1 \leq s \leq \frac{n}{k}$ 再对上式求和。时间复杂度为 $O(\displaystyle\sum_{k \mid n}^{n - 1} k \times \frac{n}{k}) = O(n \tau(n))$。

但遗憾的是有多次询问。注意到单点修改对于每个因数而言只会对一个 $s$ 产生影响，且这个 $s$ 容易得到就是 $(p - 1) \bmod k + 1$，于是我们可以用一个可删优先队列 / multiset 来维护。时间复杂度为 $O(\sum \tau(n) \log n (n + q))$。

然后你发现这样写会 MLE，因为我们需要维护一个大小为 $\sigma(n)$ 的静态数组 / vector 和可删优先队列 / multiset。

为了减小空间消耗，我们希望减小可能作为答案的 $k$ 的因数的数量。

回过头去，注意到题目要求 $k < n$，为什么呢？当 $k = n$，我们直接令 $s$ 为 $a$ 中最大的位置即可。

从这个角度思考，不难想到我们可以仅仅让 $k$ 取遍所有 $\frac{n}{p}$，其中 $p$ 为质数。

为什么呢？假如我们有另一个选择 $k' \mid k, k' < k$，且我们选择两个**本质相同**的 $s, s'$（即 $s \equiv s' \pmod{k'}$），则我们可以通过在满足本质相同的前提下移动 $s$，令 $S_x = \displaystyle\sum_{i = 0}^{k' - 1} a_{x + i \frac{k}{k'}}$，则选择 $k'$ 的贡献可以表示为 $\displaystyle\sum_{i = 1}^{\frac{k}{k'}} S_i$，选择 $k$ 的贡献可以表示为 $\frac{k}{k'} \displaystyle\max_{i = 1}^{\frac{k}{k'}} S_i$，于是结论显然成立。

时间复杂度为 $O(\sum \omega(n) \log n (n + q))$。

代码：
```cpp
#include <iostream>
#include <queue>
#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

typedef long long ll;

typedef struct {
	priority_queue<ll> q1, q2;
	
	inline void clear(){
		while (!q1.empty()) q1.pop();
		while (!q2.empty()) q2.pop();
	}
	
	inline void push(ll x){
		q1.push(x);
	}
	
	inline void release(){
		while (!q2.empty() && q1.top() == q2.top()){
			q1.pop();
			q2.pop();
		}
	}
	
	inline ll top(){
		release();
		return q1.top();
	}
	
	inline void erase(ll x){
		q2.push(x);
	}
} PriorityQueue;

PriorityQueue pq;
int a[200007], divisor[7];
ll sum[7][200007];

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, q, cnt = 0;
		scanf("%d %d", &n, &q);
		pq.clear();
		for (int j = 1; j <= n; j++){
			scanf("%d", &a[j]);
		}
		for (int j = 2, k = n; j <= k; j++){
			if (k % j == 0){
				divisor[++cnt] = n / j;
				while (k % j == 0){
					k /= j;
				}
			}
		}
		for (int j = 1; j <= cnt; j++){
			for (int k = 1; k <= divisor[j]; k++){
				sum[j][k] = 0;
				for (int l = k; l <= n; l += divisor[j]){
					sum[j][k] += a[l];
				}
				pq.push(divisor[j] * sum[j][k]);
			}
		}
		cout << pq.top() << endl;
		for (int j = 1; j <= q; j++){
			int p, x;
			scanf("%d %d", &p, &x);
			for (int k = 1; k <= cnt; k++){
				int y = (p - 1) % divisor[k] + 1;
				pq.erase(divisor[k] * sum[k][y]);
				sum[k][y] += x - a[p];
				pq.push(divisor[k] * sum[k][y]);
			}
			a[p] = x;
			cout << pq.top() << endl;
		}
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1HB4y1L7qy)

### 2 思路

首先我们将数列整体左挪一位，变成 $a_0$ 到 $a_{n-1}$。这样会好算一些。

我们发现，设 $asksum(s,k)$ 为对应的 `usefulness` 值，$asksum(s,k)=asksum(s,\gcd(n,k))$。

所以我们选择 $k$ 的时候只用考虑 $n$ 的因数，因为选其它 $k$ 等价于 $k=1$。

并且我们发现，如果 $k_2$ 是 $k_1$ 的因数，并且它们都是 $n$ 的因数。那么选 $k_1$ 要好过 $k_2$。为什么呢？

我们可以发现，对于长度为 $ci$ 的数组 $c$，很容易发现。$ci\times\max_{i=1}^{ci}c_i\ge\sum_{i=1}^{ci}c_i$。

同样的，对于上面的，设选择 $(s,k_2)$ 产生的 `usefulness` 序列为长度为 $n$ 的 $c$ 序列。可以发现，如果我们任意选择 $s$ ，肯定存在一些方式，使得选出来的东西是 $c$ 序列的一部分重复 $\dfrac{k_1}{k_2}$ 次。这一部分的总和肯定不小于 $\sum_{i=1}^nc_i$ 的 $\dfrac{k_2}{k_1}$ 倍。那么选 $k_1$ 肯定更优。

所以我们只用考虑一部分 $n$ 的因数。设 $n=\prod p_i^{a_i}$，其中 $p_i$ 均为质数。我们只需要考虑 $k=\dfrac{n}{p_i}$ 的情况。我们可以发现 $k$ 的个数不会超过 $\log n$ 个

我们可以发现，则 $asksum(s,k)=asksum(s\bmod k,k)$。所以我们可以通过记录每个 $k$ 并且记录每个 $s(0\le s<k)$ 的 $asksum(s,k)$ 的方式记录下来所有的情况。

设每次更改 $a_x$，那么对于每个 $k$ 更改 $asksum(x\bmod k,k)$ 的方式即可。

输出依靠优先队列即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
#define max_n 200000
bool isp[max_n+2];
int t;
int n;
int q;
long long a[max_n+2];
int k[max_n+2];
int ki;
vector<long long>sum[max_n+2];
priority_queue<long long>del;
priority_queue<long long>ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1718C_2.in","r",stdin);
	freopen("CF1718C_2.out","w",stdout);
	#endif
	memset(isp,true,sizeof(isp));
	for(int i=2;i<=max_n;++i){
		if(!isp[i])continue;
		for(int j=(i<<1);j<=max_n;j+=i)isp[j]=false;
	}
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&q);
		for(int i=0;i<n;++i)scanf("%lld",a+i);
		ki=0;
		for(int i=2;i<=n;++i){
			if(n%i==0&&isp[i])k[++ki]=n/i;
		}
		for(int i=1;i<=ki;++i)sum[i].clear();
		for(int i=1;i<=ki;++i){
			for(int j=0;j<k[i];++j)sum[i].push_back(0);
		}
		for(int i=1;i<=ki;++i){
			for(int j=0;j<n;++j)sum[i][j%k[i]]+=a[j]*k[i];
		}
		while(!del.empty())del.pop();
		while(!ans.empty())ans.pop();
		for(int i=1;i<=ki;++i){
			for(int j=0;j<k[i];++j)ans.push(sum[i][j]);
		}
		printf("%lld\n",ans.top());
		while(q--){
			int x;
			long long w;
			scanf("%d%lld",&x,&w);
			--x;
			for(int i=1;i<=ki;++i){
				del.push(sum[i][x%k[i]]);
				sum[i][x%k[i]]+=(w-a[x])*k[i];
				ans.push(sum[i][x%k[i]]);
			}
			a[x]=w;
			while(!del.empty()&&del.top()==ans.top()){
				del.pop();
				ans.pop();
			}
			printf("%lld\n",ans.top());
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/84175620)

By **dengziyue**

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
### 解题思路：

考虑满足 $\gcd(n,k_1)=\gcd(n,k_2)$ 的一组 $k_1$ 和 $k_2$，有 $\sum_{i=1}^na_{ik_1\bmod n}=\sum_{i=1}^na_{ik_2\bmod n}$。

感性证明就是考虑提取出被用到的所有 $\gcd(n,k)|i$，然后规约到 $(n,p)=1$ 的情况证明其恰好取完了所有的数，然后翻上 $\gcd(n,k)$ 就得到了原来的结果。

另一种比较严谨的证明方式就是对于一个 $a_i$ 分析其被取到了多少次，写起来很麻烦，所以我选择偷懒。

---
有了上面那个结论就能很容易地发现只需要分析 $n$ 的所有因数就行了。但是还不够，考虑与 $n$ 的最大公约数不相同的 $k_1$ 和 $k_2$ 且有 $k_1k_2|n$ 的一组 $k_1$ 和 $k_2$，有结论 $k_1k_2$ 作为取数差值的最大值一定不比另外两者的最大值小。这个揭露的证明可以考虑将 $k_1k_2$ 所取在 $k_1$ 取得数集中最大的一个两两间隔 $k_2$ 倍数的子集。将这个大小为   $\dfrac{n}{k_1k_2}$ 个数复制 $k_2$ 份使得其数量和 $k_1$ 取得数的数量相等，并与每一个两两间隔 $k_2$ 倍数的子集比较就能得出 $k_1k_2$ 较大的结论了。

从上面那个结论推广下去，可以发现在不能取 $n$ 的前提下，最大答案一定在 $k=\dfrac{n}{p}$ 其中 $p$ 是 $n$ 的一个素因数中取。由此 $k$ 的取值就被缩小到一个 $\log n$ 的级别了。

然后发现对于一个取值 $k$，一共有 $k$ 个本质不同取值位置。所以一开始处理的时候直接对于每一种 $k$ 遍历一遍，对于 $k$ 个起始位置统计一下答案就行。

---

对于每一次更改，对于每一种取值 $k$ 涉及到一个本质不同的位置，然后就需要一个能够快速求出 $k$ 种取值中最大的一个，并进行相应的更改的数据结构。

这里可以使用两个堆进行维护。一个堆记录被删除的值，另一个堆记录第一个堆中的所有值和当前实际存在的所有值。当需要加入一个值的时候，直接向第二个堆中加入。当需要删除一个值的向第一个堆中加入这个值。查询时，比较两个堆的堆顶元素是否相等，如果相等，说明这个元素应当已经被删除，弹出两个堆顶直到第一个堆为空或者元素不等，说明当前第二个堆的堆顶元素是存在的最大元素。

---
### 代码：

```cpp
#include<vector>
#include<cstdio>
#include<queue>
using namespace std;
#define int long long
const int MAXN=400005;
priority_queue <long long> p,p_del;
int T,n,m,a[MAXN],x,y,num[MAXN],tot,n_;
vector <int> ans[MAXN];
void init(){
	while(!p.empty())p.pop();
	while(!p_del.empty())p_del.pop();
	for(int i=1;i<=tot;i++)ans[i].clear();
	tot=0;
}
void del(int num){
	p_del.push(num);
	while((!p_del.empty())&&(p_del.top()==p.top())){
		p_del.pop();
		p.pop();
	}
}
void query(){
	int ANS=p.top();
	printf("%lld\n",ANS);
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		init();
		scanf("%lld%lld",&n,&m);
		n_=n;
		for(int i=2;i<=n_;i++){
			if(n_%i==0)num[++tot]=n/i;
			while(n_%i==0)n_/=i;
		}
		if(num[tot]==n)tot--;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=tot;i++)ans[i].resize(num[i]+1);
		
		for(int i=1;i<=n;i++)
		for(int j=1;j<=tot;j++)
		ans[j][i%num[j]]+=a[i]*num[j];
			
		for(int i=1;i<=tot;i++)
		for(int j=0;j<num[i];j++)
		p.push(ans[i][j]);

		query();
		while(m--){
			scanf("%lld%lld",&x,&y);
			for(int i=1;i<=tot;i++){
				del(ans[i][x%num[i]]);
				ans[i][x%num[i]]-=a[x]*num[i];
				ans[i][x%num[i]]+=y*num[i];
				p.push(ans[i][x%num[i]]);
			}
			a[x]=y;
			query();
		}
	}
	return 0;
} 
```



---

## 作者：intel_core (赞：0)

注意到给定的 $(s,k)$ 一定是沿着一个环在走，并且环长是 $\gcd(k,n)$；同时不难发现走了 $\frac{n}{\gcd(n,k)}$ 次，并且环上的点满足 $x \equiv s(\bmod \frac{n}{\gcd(n,k)})$。

因为环长必须是 $n$ 的因数，最多是 $O(\sqrt{n})$ 级别的；所以我们可以对所有不同的环长分开统计。

显然，我们可以在 $O(nd(n))$ 内求出所有可能的环对应的答案。

考虑修改，枚举每个 $n$ 的约数 $d$，修改 $x$ 所在环的数据然后更新最大值。

复杂度 $O(nd(n)\log n)$，单点修改全局最大无法做到 $O(\log n)$ 以内的复杂度，所以会被卡的很惨。

考虑优化，对于环长为 $k$ 的环，若 $p$ 是 $k$ 的因数，不难发现一定有一个长度为 $p$ 的环能完爆所有长度为 $k$ 的环。用平均值原理不难证明。

所以我们只需考虑环长为质数的环即可；$2\times 3 \times 5\times 7\times 11\times 13\times 17=510510$，所以复杂度 $O(7n\log n)$。

---

