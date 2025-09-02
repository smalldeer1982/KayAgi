# 〈 TREEのOI 2022 Spring 〉Counting By Ternary

## 题目背景

黑土地上，一棵小苗破土而出。

几个月里，它吮吸着甘甜的雨露，享受着温暖的阳光，愈发翠绿了起来。

![](https://cdn.pixabay.com/photo/2019/03/05/12/52/plant-4036131_960_720.jpg)

它越长越高，越长越壮，似乎要突破云霄。

它长成了一棵大树，渴望着去天空中，看一看这美丽的世界。

![](https://cdn.pixabay.com/photo/2015/02/24/15/41/wolf-647528_960_720.jpg)

## 题目描述

**请留意本题并不寻常的时空限制。**

给定一个数 $x$，用如下规则建立一棵有根树：

- 根节点为 $\lang0,x\rang$。  

- 对于一个节点 $\lang i,j\rang$，若 $j < 3$，则它是叶子节点，否则它的子节点为对于任意 $1 \le k$ 且 $j$ 的位数 $\ge k$， $\lang j_k, k\rang$，其中 $j_k$ 为它三进制表示从左向右的第 $k$ 位。  

求这棵树的叶子节点的数目。

## 说明/提示



**本题采用 SubTask 捆绑测试。**

| SubTask 编号 | 分值 | 特殊性质 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $10$ | $p\le 3^{15}$，$q=1$ |
| $1$ | $10$ | $p\le 3^{35}$，$q=1$ |
| $2$ | $20$ | $p=3$，$q\le 3^{15}$ |
| $3$ | $60$ | $p=3$，$q\le 3^{35}$ |


对于 $100\%$ 的数据，$p^q \le 3^{3^{35}}$（$10^{10^9} \lt 3^{3^{35} } \lt 10^{2.5 \times 10^9}$），保证 $p = 3^l(l\in \mathbb N^+)$。 


## 样例 #1

### 输入

```
9 1```

### 输出

```
4```

## 样例 #2

### 输入

```
27 1```

### 输出

```
6```

# 题解

## 作者：过氧化氢_syq0057 (赞：3)

## 题外话

很好的题，只不过是冲着分块标签来的发现不是分块 /ll。

## Solution

手动画几个图可以发现，一个节点 $i$ 好像只连向 $\lfloor \log_3{i} \rfloor+1$ 的节点，所以我们可以很快推出递推式：

$$
f_i= \sum_{j=1}^{\lfloor \log_3i \rfloor +1} f_j
$$

以下是核心代码

```cpp
int main() {
	scanf("%lld%lld", &p, &q);
	ll x = q * Log3(p) + 1;//这里手写log3
	f[1] = 1, f[2] = 1;
	for (ll i=3; i<=x; i++)
		for (ll j=1; j<=Log3(i)+1; j++)
			f[i] += f[j];
	for (ll i=1; i<=x; i++)
		ans += f[i];
	printf("%lld\n", ans);
}
```

这样就能得到 $20pts$ 了。

这种算法我们时间复杂度是 $O(\log_3{p^q})$ 即为 $O(3^{35})$ 的，考虑优化。

观察到 $f_i$ 有很长一段相同的取值（因为 $ \lfloor \log_3i \rfloor +1$ 限制了它的发挥）。

$$
f_1=f_2=1
$$
$$
f_3=f_4=...=f_8=2
$$
$$
f_9=f_{10}=...=f_{26}=4
$$
$$
f_{27}=f_{28}=...=f_{80}=6
$$

于是我们设 $g_i$ 代表 $f_{3^{i-1}}$ 到 $f_{3^i-1}$ 的值。
$$
g_1=f_1=f_2=1
$$
$$
g_2=f_3=f_4=...=f_8=2
$$
$$
g_i=f_{3^{i-1}}=...=f_{3^{i}-1}
$$

根据一开始的公式，显然（把 $f_i$ 推到 $g_i$ 上）
$$
g_i= \sum_{j=1}^i f_i
$$
令 $x=\log_3p^q$，所以
$$
ans= \sum_{i=1}^x f_i= \sum_{j=1}^{\lfloor \log_3i \rfloor +1} g_j \times (3^j-3^{j-1})
$$
注意对 $g_n$ 特殊处理（最后一项只能到 $q \times \lfloor \log_3p \rfloor + 1$）

这样，我们就在 $O(\log_3 \log_3p^q)$ 内即 $O(35)$ 内处理，就可过了。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cmath>
#include <queue>
#include <map>
using namespace std;
const int N = 2000005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
inline int read() {
	int x = 0, f = 1; char ch;
	ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}
ll p, q;
ll f[N], g[N];
ll ans;
ll Log3(ll s) {//下取整 
	ll res = 0;
	while (s) {
		s /= 3;
		res++;
	}
	return res - 1;
}
ll ksm(ll x, ll y) {
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x;
		x = x * x;
		y >>= 1;
	}
	return res;
}
int main() {
	scanf("%lld%lld", &p, &q);
	ll x = q * Log3(p) + 1;
	ll log3x = Log3(q * Log3(p)) + 1;
	f[1] = 1, f[2] = 1;
	for (int i=3; i<=100; i++)
		for (int j=1; j<=Log3(i)+1; j++)
			f[i] += f[j];
	g[1] = 1, g[2] = 2;
	for (ll i=3; i<=log3x; i++)
		for (int j=1; j<=i; j++)
			g[i] += f[j];
	for (int i=1; i<=log3x; i++) {
		if (i == log3x) ans += (x - ksm(3, i - 1) + 1) * g[i];//注意特殊处理
		else ans += (ksm(3, i) - ksm(3, i - 1)) * g[i];
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：1)

观察可以发现，每个节点的第一项可以不要，而节点 $x$（第二项为 $x$，下同）连向 $[1,\lfloor\log_3x\rfloor+1]$，所以得出递推式：
$$f_x = \sum\limits_{i=1}^{\lfloor\log_3x\rfloor+1}f_i $$
边界条件：$f_1 = 1$。  
这样，你就可以通过 $40\%$ 的数据（预处理出 $f_{1..\lfloor\log_3x\rfloor+1}$）。  
但是 $ \mathcal O(q\log_3 p)$ 的复杂度还是不够优秀，无法通过此题，但是我们考虑第三层（$\log_3 \log_3 p^q$）  
首先，我们定义 $f$ 的前缀和数组为 $g$，所以有 $f_x = g_{\lfloor\log_3x\rfloor+1}$。  
统计 $g_{\lfloor\log_3x\rfloor+1}$ 中$f_{1..\lfloor\log_3(\lfloor\log_3x\rfloor+1)+1\rfloor}$ 的个数，推推柿子，即可解决。  
具体：  
注意~~不~~到：  
$$f_1 = f_2 = 1$$  
$$f_3 = f_4 = f_5 = f_6 = \dots = f_8 = f_1 + f_2$$  
$$f_{3^2} = f_{3^2+1} = \dots = f_{3^3-1} = g_3$$  
预处理 $\log_3 \log_3 p^q$ 以内的 $g$ 即可。  
更具体地：  
$$g_x = \sum_{i = 1}^{\lfloor\log_3x\rfloor} (3^{i} - 3^{i-1}) g_i + Ext$$  
$$Ext = (x - 3^{\lfloor\log_3x\rfloor} + 1)g_{\lfloor\log_3x\rfloor + 1}$$  
$$f_x = g_{\lfloor\log_3x\rfloor + 1}$$
可以在 $\mathcal O(\log_3 \log_3 p^q)$ 时间内解决。  



Code:  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
using namespace FastIO; // FastIO 的具体时间就不粘了，因为很长

const int maxn = 1e+5 + 1;
const double eps = 1e-6;

int p, q, log3pq, log3log3pq, ext, ans;
int g[maxn];

int log3(int mx)
{
    return log(mx) / log(3) + eps;
}

int power(int base, int freq)
{
    int ans = 1, tmp = base;
    while (freq > 0)
    {
        if (freq % 2 == 1)
            ans = ans * tmp;
        freq /= 2;
        tmp = tmp * tmp;
    }
    return ans;
}

void generate()
{
    log3pq = q * log3(p) + 1;
    log3log3pq = log3(log3pq);
    g[1] = 1;
    g[2] = 2;
    for (int x = 3; x <= log3(log3pq) + 1; x++)
    {
        ext = (x - power(3, log3(x)) + 1) * g[(int)log3(x) + 1];
        g[x] += ext;
        for (int i = 1; i <= log3(x); i++)
        {
            g[x] += (power(3, i) - power(3, i - 1)) * g[i];
        }
    }
}

int getans()
{
    ext = (log3pq - power(3, log3log3pq) + 1) * g[(int)log3log3pq + 1];
    ans = 0;
    for (int i = 1; i <= log3(log3pq); i++)
    {
        ans += (power(3, i) - power(3, i - 1)) * g[i];
    }
    return ans + ext;
}

void init()
{
    memset(g, 0, sizeof(g));
    ans = 0;
}

signed main()
{
    fin >> p >> q;
    init();
    generate();
    fout << getans() << endl;
    return 0;
}
```

---

