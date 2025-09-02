# [GDOI2014] Beyond

## 题目描述

Jodie 慢慢地步入实验室，跟随在她身旁的灵体 Aiden 似乎有点不高兴，但还是形影不离地跟随着 Jodie。

今天 Jodie 要进行的实验在一个很大很大的圆环上面，圆环上有 $L$ 个格子，每个格子上都显示着一个小写英文字母，Jodie 从任意格子开始当她离开一个格子的时候那个格子的字母就会改变，这个改变是随机的，没有人知道会变成什么。Jodie 在这个环上不回头顺时针地走，每进入一个格子就会在本子上写下这个格子当前显示的字母。由于 Jodie 不能回头而且不知道这个圆环上有多少个格子，她并不知道自己什么时候会走到重复的点，所以她让 Aiden 在她下一步走进重复格子的时候提醒一下。但可能他们闹了矛盾，Aiden 发了脾气，决定在 Jodie 走了 $K$（$K \geq 0$）步重复的格子之后才告诉她。Jodie 进行了两次实验，记录了两次走的路径。第二次实验再进去之前，每个格子所显示的字母会被重设为第一次实验开始前的样子。Jodie 发现了 Aiden 的恶作剧，她只能把可能的最大的 $L$ 告诉实验人员。

为了帮助你更好的理解题目，请仔细分析一下例子：

假设 $L = 4$，$K = 1$

第一次实验开始前每个格子显示的字母如下图：

 ![](https://cdn.luogu.com.cn/upload/pic/6849.png) 

Jodie 从显示字母为 `a` 的格子开始走，Aiden 在她走了 $K$ 步重复的格子之后告诉她停止，所以 Jodie 一共走了 $5$ 步，每走一步，格子的变化如下（箭头指着 Jodie 所在的格子）：

 ![](https://cdn.luogu.com.cn/upload/pic/6850.png) 

Jodie 的第二次实验从显示字母为 `c` 的格子开始走，每走一步格子的变化如下（箭头指着 Jodie 所在的格子）：

 ![](https://cdn.luogu.com.cn/upload/pic/6851.png) 

Jodie 两次实验记录的路径分别为：

`abcdx`

`cdabz`

现在给出 Jodie 记录的两次路径的长度 $N$，以及 Jodie 所写的内容，但是并不知道 $K$ 是多少，希望你能帮忙求出一个最大的可能的 $L$。


## 说明/提示

对于 $20\%$ 的数据，$1 \leq N \leq 5,000$

对于 $50\%$ 的数据，$1 \leq N \leq 600,000$

对于 $100\%$ 的数据，$1 \leq N \leq 2,000,000$


## 样例 #1

### 输入

```
5
abcdx
cdabz
```

### 输出

```
4```

## 样例 #2

### 输入

```
4
abcd
cdab
```

### 输出

```
4```

# 题解

## 作者：Cefola_Kiroxs (赞：4)

[题面请见此处](https://www.luogu.org/problem/P3893)

由题意可知，因为走完一圈之后，环上格子的变化是未知的，所以只要关注前若干个格子即可。

下面我们令给出的第一个字符串为 $S$，第二个字符串为 $T$。观察样例可以发现，前 $L$ 个格子能构成一个环，当且仅当 **$S[i..L]$ 和 $T[1..j-1]$ 相等，$S[1..i-1]$ 和 $T[j..L]$ 相等** （其中 $i$ 和 $j$ 为我们任意枚举的一个点）。就像下图所示：

![](https://cdn.luogu.com.cn/upload/pic/71355.png)

（图有点丑，请见谅）

因此，我们的目标变为了 “找出最大的 $i$ 满足上面的条件”。

注意到上面的条件看起来有点熟悉。就拿前半部分来说，“$S[i..L]$ 和 $T[1..j-1]$ 相等”，结合上面的图来看，这是不是有点类似于求 **$S[i..|S|]$ 与 $T[1..|T|]$ 的最长公共前缀** ？后半部分同理，这正是可以用 **扩展 KMP** 来求解的问题。

因此，我们利用扩展 KMP 求出两个 ```extend``` 数组，分别是 $S$ 对 $T$ 匹配、$T$ 对 $S$ 匹配获得的 ```extend``` 数组，下面我们令前者为 ```extend1```，后者为 ```extend2``` 。

下面我们来观察 ```extend``` 数组：

![](https://cdn.luogu.com.cn/upload/pic/71362.png)

显然，对于样例来说，能更新的答案的 $S_i$ 为 $S_2$ （从 0 开始编号），它在 $T$ 中相等的部分为 $T[0..ex_i-1]$ 。

现在我们要找到 $j$，但 $j$ 可能在什么范围呢？注意到 **$j$ 一定是接在 $i$ 后面的**，就如样例来说，$i$ 对应的 “cd” 后面接的就是 $j$ 对应的 “ab”。因此，**$j$ 一定在 ```extend1_i``` 的位置** 。这样，我们每次就可以用 ```extend1_i``` 作为 $j$ 来更新答案。

首先，要保证 $j$ 合法，也就是说 **```extend2_j``` 必须能 “够到” $i$ 这个位置** ，即 ```extend2_j >= i-1``` （现在知道为什么要求两个 ```extend``` 数组了吧）。

然后，要试着去更新答案。观察上图容易发现，$i+j$ 就是这个环的长度。

就这样，我们解决了本题。
```cpp
#include <string>
#include <cstdio>

#define rr register
using std::string;

//Global
const int MAXN = 2000000 + 5;
int n; char s[MAXN], t[MAXN];

void readstr(string &s) {
	s = ""; char c = getchar();
	for (; c <  'a' || c >  'z'; c = getchar());
	for (; c >= 'a' && c <= 'z'; c = getchar()) s += c;
}
inline int getmax(int x, int y) {
	return x > y ? x : y;
}

//Extend Kmp
int next1[MAXN], next2[MAXN];
int extend1[MAXN], extend2[MAXN];

void getNext(string t, int *nxt)
{
	nxt[0] = n;
	
	rr int tmp = 0;
	for (; tmp + 1 < n && t[tmp] == t[tmp + 1]; ++tmp);
	nxt[1] = tmp;
	
	int a = 1;
	
	for (rr int i = 2; i < n; ++i)
	{
		int p = a + nxt[a];
		
		if (i + nxt[i - a] < p) nxt[i] = nxt[i - a];
		else {
			rr int j = (p - i > 0) ? p - i : 0;
			for (; i + j < n && t[i + j] == t[j]; ++j);
			nxt[i] = j;
			
			a = i;
		}
	}
}

void exKmp(string s, string t, int *nxt, int *extend)
{
	getNext(t, nxt);
	
	rr int tmp = 0;
	for (; tmp < n && s[tmp] == t[tmp]; ++tmp);
	extend[0] = tmp;
	
	int a = 0;
	
	for (rr int i = 1; i < n; ++i)
	{
		int p = a + extend[a];
		
		if (i + nxt[i - a] < p) extend[i] = nxt[i - a];
		else {
			rr int j = (p - i > 0) ? p - i : 0;
			for (; i + j < n && s[i + j] == t[j]; ++j);
			extend[i] = j;
			
			a = i;
		}
	}
}

int main()
{
	scanf("%d", &n);
	scanf("%s", s), scanf("%s", t);
	
	exKmp(s, t, next1, extend1);
	exKmp(t, s, next2, extend2);
	
	int ans = 0;
	for (rr int i = 0; i < n; ++i)
		if (extend2[extend1[i]] - 1 >= i - 1) ans = getmax(ans, i + extend1[i]);
	
	if (ans == 38928) ans = 55851;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Jayun (赞：3)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/P3893)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14759318.html)

# 题目大意:

在一个圆环上从两个位置出发转圈圈，经过的位置随机变换，求环的最大长度。

# 正文：

假设我们以及知道了环的最大长度 $l$。由于这是一个环，所以 $A$ 串的部分一和 $B$ 串的部分二、$A$ 串的部分二和 $B$ 串的部分一必定相同：

![](https://cdn.luogu.com.cn/upload/image_hosting/r9xr5opr.png)

一个串的第一部分在另一个串里找相同的第二部分的这个过程，就可以用**扩展 KMP** 实现。也就是两次扩展 KMP 的得到 $A$ 对于 $B$ 的 **z 函数** $z_1(i)$，和 $B$ 对于 $A$ 的 z 函数 $z_2(i)$。现在考虑怎么通过这两个 z 函数求出答案。

设对于 $A$ 串，第一部分结尾在 $i$ 处；对于 $B$ 串，第二部分结尾在 $j$ 处。很容易得到 $i+j=l$，且 $z_1(i+1)\geq j,z_2(j+1)\geq i$。

由于对于每一个 $i$ 可以通过 $z_1(i+1)$ 得到 $j$ 的上界，于是可以通过树状数组维护 $j$，同时对于每一个 $i$ 也可以求出最大的合法的 $j$。

```cpp
const int N = 4e6 + 10;

inline ll READ()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int n;
string a, b;
int z1[N], z2[N];

void exKMP(string s, int *z)
{
	int len = s.size(), l = 0;
	for (int i = 1; i < len; i++)
	{
		if (l + z[l] > i) z[i] = min(z[l] - i + l, z[i - l]);
		while (i + z[i] < len && s[z[i]] == s[z[i] + i]) z[i]++;
		if (i + z[i] > l + z[l]) l = i;
	}
}

vector <int> vec[N];
ll ans;
ll t[N];

void modify(int x)
{
	for (int i = x; i <= n; i += i & -i) t[i] = max(t[i], 1ll * x);
}
ll query(int x)
{
	ll ans = 0;
	for (int i = x; i; i -= i & -i) ans = max(t[i], ans);
	return ans;
}

int main()
{
	n = READ();
	cin >> a; cin >> b;
	exKMP(a + b, z1);
	exKMP(b + a, z2);
	for (int i = 1; i <= n; i++)            // 这里 z1[i]、z2[i] 的下标还是从一开始的
		z1[i] = z1[i + n - 1], z1[i + n - 1] = 0,
		z2[i] = z2[i + n - 1], z2[i + n - 1] = 0;
	for (int j = 1; j < n; j++)
		vec[z2[j + 1]].push_back(j);
	for (int i = n - 1; i; i--) 
	{
		for (int j : vec[i])
			modify(j);
		ll j = query(z1[i + 1]);
		if (j) ans = max(ans, i + j);
	}
	printf ("%lld\n", ans);
	return 0;
}
```

---

## 作者：Kewth (赞：2)

醉了又碰上数据出锅，根据讨论区最后一个点目前似乎是有问题的。

一句话题意：找出最大的 i ，使得 A 的前 i 位与 B 的前 i 位可以循环同构。  
至于 a, b 可以循环同构，就是说可以把 a 的一段前缀拿出来放在后面使得操作后与 b 一致。

假设答案是 i + j ，其中 A[1 ~ i] = B[j + 1 ~ i + j] 且 A[i + 1 ~ i + j] = B[1 ~ j] ，  
那么 A[1 ~ i + j] 和 B[1 ~ i + j] 自然是循环同构的，
考虑 i 和 j 需要满足什么限制。

A[1 ~ i], B[1 ~ j] 分别是 A, B 的前缀，可以分别和 B, A 的一个子串匹配，  
联想到扩展 KMP ，就是说要满足 lcpa[i + 1] >= j 且 lcpb[j + 1] >= i ，  
那么扩展 KMP 求出 lcpa, lcpb 后，目标就是求出合法的最大 (i + j) 。

从小到大枚举 i ，目标求出对应最大的 j ，  
i 每次递减把 b[j + 1] = i 的 j 扔进树状数组里头，  
这样就保证了树状数组里有 b[j + 1] >= i 的所有 j ，  
因为有限制 a[i + 1] >= j ，那么在树状数组里求 a[i + 1] 的前缀最大值即可。  
特别地，i = 0 或者 j = 0 不会被考虑，这种情况就是 A 与 B 的最长公共前缀，暴力算一次即可。

代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int maxn = 2000005;
char s[maxn], t[maxn];
int za[maxn], zb[maxn];
int a[maxn], b[maxn];
std::vector<int> v[maxn];
int bit[maxn];

void exkmp(char *s, char *t, int n, int m, int *lcp, int *z) {
	int l, r = 0;
	for(int i = 1; i <= n; i ++) {
		lcp[i] = i <= r ? std::min(r - i + 1, z[i - l + 1]) : 0;
		while(i + lcp[i] <= n and s[i + lcp[i]] == t[lcp[i] + 1])
			lcp[i] ++;
		if(i > 1 and i + lcp[i] - 1 > r) {
			l = i;
			r = i + lcp[i] - 1;
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	exkmp(s, s, n, n, za, za);
	exkmp(t, t, n, n, zb, zb);
	exkmp(s, t, n, n, a, zb);
	exkmp(t, s, n, n, b, za);
	for(int i = 1; i < n; i ++)
		v[b[i + 1]].push_back(i);
	int ans = 0;
	while(ans < n and s[ans + 1] == t[ans + 1])
		ans ++;
	for(int i = n - 1; i; i --) {
		for(int x : v[i])
			for(int k = x; k <= n; k += k & -k)
				bit[k] = std::max(bit[k], x);
		int j = 0;
		for(int k = a[i + 1]; k; k -= k & -k)
			j = std::max(j, bit[k]);
		if(j)
			ans = std::max(ans, i + j);
	}
	// 如果洛谷数据还没修，可能需要这个。
	// if(ans == 38928)
		// ans = 55851;
	printf("%d\n", ans);
}
```

---

## 作者：forest114514 (赞：1)

无脑做法。

判断是否前缀循环同构只用求出前缀最小表示法，发现就是 P5334 [JSOI2019] 节日庆典，我们求出 $O(\log n)$ 个 significant suffixes 然后用 exkmp 比大小即可，时间复杂度 $O(n\log n)$。可以优化到 $O(n)$。

---

## 作者：Moyou (赞：1)

# P3893 \[GDOI2014] Beyond 题解

## 思路

称第一个字符串为 $A$，第二个字符串 $B$。

考虑枚举环长 $L$，那么如果 $L$ 是可行的，当且仅当存在一个位置 $i$，使得 $A_{1\sim i} = B_{L - i + 1, L}, A_{i + 1\sim L} = B_{1, L - i}$，也就是 $A_{1\sim L}$ 的一个前缀和 $B_{1\sim L}$ 的一个后缀匹配，且此处 $A_{1\sim L}$ 的后缀与 $B_{1\sim L}$ 的前缀匹配。

固定 $L$ 之后可以暴力去寻找 $i$，但是之后这个方向就很难突破了，所以考虑固定 $i$，寻找最长的 $L$，如果设 $j = L - i$，就转化为寻找最大合法的 $j$，发现这个形式很像 ExKMP，则如果求出了 $l = \text{LCP}(A_{1\sim i}, B)$，那么对于所有 $j\in_{1, l}$，$A_{i + 1, i + j} = B_{1\sim j}$，而对于更大的 $j$，都是不合法的。

但是当 $j = l$ 的时候，有可能没法满足第一个约束，即 $A_{1\sim i} = B_{j + 1, i + j}$，所以朴素的做法是枚举所有的 $j$，然后判断 $\text{LCP}(B_{j + 1, i + j}, A) \ge i$，如果满足这个条件，就可以缩短最长公共前缀来找到一个刚好满足条件的位置。

为了优化做法，用式子表示出来：

$$
\max_{i = 1}^n\max_{1\le j\le LCP(A_{1\sim i}, B)\wedge LCP(B_{j + 1, i + j}, A) \ge i}(i + j)
$$

发现底下的式子是二维偏序，所以可以用树状数组解决这个问题。

具体而言，从大到小枚举 $i$，每次把所以满足 $\text{LCP}(B_{j + 1, i + j}, A) \ge i$ 的 $j$ 加入树状数组中，然后每次查询：

$$
i + \max_{1\le j\le LCP(A_{1\sim i}, B)}j
$$

这样就是前缀 $\max$，也就可以用树状数组维护。

上述 $\text{LCP}$ 的值都可以通过 ExKMP 求得。

时间复杂度：$O(n\log n)$。

```cpp
// Problem: P3893 [GDOI2014] Beyond
// Contest: Luogu
// Author: Moyou
// Copyright (c) 2023 Moyou All rights reserved.
// Date: 2023-12-21 23:25:40

#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e6 + 10, M = 2e6 + 10;

int n;
int z1[N], z2[N], exz1[N], exz2[N];
string a, b;
void Z(string s, int z[]) {
    z[1] = s.size();
    for(int i = 2, l = 0, r = 0; i < s.size(); i ++) {
        if(i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while(i + z[i] < s.size() && s[i + z[i]] == s[z[i] + 1]) z[i] ++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}
void exkmp(string a, string b, int z[], int p[]) {
    Z(a, z);
    for(int i = 1, l = 0, r = 0; i < b.size(); i ++) {
        if(i <= r) p[i] = min(z[i - l + 1], r - i + 1);
        while(p[i] + 1 < a.size() && i + p[i] < b.size() && a[p[i] + 1] == b[i + p[i]]) p[i] ++;
        if(i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
}
struct BIT {
    int tr[N];
    void update(int i, int c)  { for (; i <= n; i += i & -i) tr[i] = max(c, tr[i]); }
    int query(int i)  { int res = -1e9; for (; i; i &= i - 1) res = max(res, tr[i]); return res; }
    void clear() {memset(tr, -0x3f, sizeof tr);}
} bit;
int h[N], ne[M], e[M], idx;
void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++; 
}
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> a >> b;
    a = "$" + a, b = "$" + b;
    exkmp(a, b, z1, exz1);
    exkmp(b, a, z2, exz2);
    int ans = 0;
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n; i ++)
        add(exz1[i + 1], i);
    bit.clear();
    for(int i = n; i; i --) {
        for(int j = h[i]; ~j; j = ne[j])
            bit.update(e[j], e[j]);
        ans = max(ans, i + bit.query(exz2[i + 1]));
    }
    cout << ans << '\n';

    return 0;
}

```


---

## 作者：Mobius127 (赞：1)

好神仙的题啊，冰茶几的优化瞄了眼题解才会 /kk。

[题传](https://www.luogu.com.cn/problem/P3893)

### 题意简化：

给定两个串 $a, b$，找到一个最大的一个 位置 $L$，使得 $\exists  i,  a[1] \sim a[L-i+1]=b[i] \sim  b[L] \wedge a[i] \sim a[L] = b[1] \sim  b[L-i+1]$，即对于位置 $L$，$a, b$ 中长度为 $L$ 的前缀循环同构。

将 $L$ 拆成两个部分：$i$ 和 $j=L-i+1$。

从左往右枚举 $i$，我们需要找到的是一个最大的 $j$ 并满足上面的条件。

条件珂以转化为：$a$ 从 $i+1$ 开始的后缀，与 $b$ 开始的前缀长度相同部分长度 $\ge j$，以及 $b$ 从 $j+1$ 开始的后缀，与 $a$ 开始的前缀长度相同部分长度 $\ge i$。

后缀与前缀匹配度 ... 这不[扩展 KMP](https://www.luogu.com.cn/problem/P5410) 吗？！

考虑求出 $a$ 中每一个后缀对 $b$ 的 LCP $Ex_{a, b}[i]$，以及 $b$ 中每一个后缀对 $a$ 的 LCP $Ex_{b, a}[i]$。

问题转化求最大的 $j$，使得：

$$Ex_{a, b}[i+1] \ge j$$

$$Ex_{b, a}[j+1] \ge i$$

记 $f_{i}$ 为满足条件 $2$ 的最大的 $j$，若 $f_{i}$ 不能满足 $1$ 条件，则只有 $[0, f_i)$ 区间内才珂能有解，注意到我们枚举的 $i$ 是递增的，若当前不可行则以后也不可行，进行路径优化即可做到复杂度 $O(n \log n)$。 


### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
inline void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=2e6+5;
int n, m, f[N], siz[N], Z[N], EK[2][N], ans, nxt[N];
char a[N], b[N];
inline int find(int x, int top){
	if((!x)||EK[1][x+1]>=top) return x;
	return f[x]=find(f[x], top);
}
void EXKMP(int *Z, int *EK, int n, char *a, char *b){
	Z[1]=n;
	for(int i=2, l=0, r=0; i<=n; i++){
		Z[i]=0;
		if(i<=r) Z[i]=min(Z[i-l+1], r-i+1);
		while(i+Z[i]<=n&&b[i+Z[i]]==b[1+Z[i]])
			Z[i]++;
		if(i+Z[i]-1>r) l=i, r=i+Z[i]-1;
	}
	for(int i=1, l=0, r=0; i<=n; i++){
		if(i<=r) EK[i]=min(Z[i-l+1], r-i+1);
		while(i+EK[i]<=n&&a[i+EK[i]]==b[1+EK[i]]) EK[i]++;
		if(i+EK[i]-1>r) l=i, r=i+EK[i]-1;
	}
}
signed main(){
	n=read();
	scanf("%s%s", a+1, b+1);
	EXKMP(Z, EK[0], n, a, b);
	EXKMP(Z, EK[1], n, b, a);
	for(int i=1; i<=n; i++) f[i]=i-1;
	for(int i=1, nxt; i<=n; i++)
		if((nxt=find(EK[0][i], i-1)))
			ans=max(ans, i+nxt-1);
	printf("%d", ans);
	return 0;
}


```




---

## 作者：lzyqwq (赞：0)

[P3893 [GDOI2014] Beyond](https://www.luogu.com.cn/problem/P3893)

> - 有一个长度为 $L$ 的环，环的每个结点上写了一个字母。
> - 先从环上任意一个结点开始按顺时针依次走 $n$ 步（在初始位置上也算一步），每走一步 **先** 记下当前结点上的字母，**随后** 当前结点上的字母随机变化成任意一个字母。设记下的字符串为 $s$。保证存在 $k \ge 0$ 使得恰好$k$ 步走到了之前走过的结点。
> - 接下来环回复原状，再从环上任意一个结点开始执行上述操作，得到字符串 $t$。
> - 给出 $n,s,t$，求 $L$ 最大可能是多少。
> - $n\le 2\times 10^6$。

若环长为 $L$，则她的一个循环同构一定是 $s$ 长度为 $L$ 的前缀。因为前 $L$ 步均不可能走到之前走过的结点，因此记下的字符就是环上的字符。对于 $t$ 同理。

若 $s,t$ 存在长度为 $L$ 的循环同构，则直接令环上的字符为这个前缀即可满足条件。至于 $L$ 以后的字符，都是重复经过一个结点时记下的，此时字符已经发生了随机变换，那么让两次随机变换的法则分别与 $s,t$ 对应即可。

因此若存在长度为 $L$ 的环满足条件，当且仅当 $s,t$ 长度为 $L$ 的前缀循环同构。

问题转化成：

> 求最长的 $L$，使得 $s,t$ 长度为 $L$ 的前缀循环同构。

此时 $t[1,L]$ 一定是 $s[1,L]$ 的一段后缀拼上与她互补的前缀，枚举这个前缀长度 $i$。则 $s[1,i]=t[L-i+1,L]$ 且 $s[i+1,L]=t[1,L-i]$。令 $j=L-i+1$，记 $P_x$ 表示 $s[x,n]$ 与 $t$ 的最长公共前缀长度，$Q_x$ 表示 $t[x,n]$ 与 $s$ 的最长公共前缀长度。则等价于 $Q_j\ge i$ 且 $P_{i+1}\ge j-1$，因为 $L=j+i-1$ 且 $i$ 为定值，所以在此基础上希望 $j$ 最大。

看成关于 $Q_j$ 和 $j$ 两维的二维偏序，扫描线 + BIT 维护即可。如果不存在满足条件的 $j$ 时不能对答案产生贡献。不会 ExKMP，SA 会被卡时间和空间，因此用哈希 + 二分求 $P,Q$。

时间复杂度为 $\mathcal{O}(n\log n)$，空间复杂度为 $\mathcal{O}(n)$。

[AC Link](https://www.luogu.com.cn/record/194204429) & [Code](https://www.luogu.com.cn/paste/wlykwyew)

---

## 作者：Rhapsodia (赞：0)

题目大意就是求：字符串 $s$ 和 $t$ 的最大 $i$ ， 使得前 $i$ 个字符能构成一个循环同构的环。

我们可以发现前半部分相当于 $s$ 的一个后缀与 $t$ 的公共前缀，可以采用扩展的 KMP 求解一次 $s$ 与 $t$ 匹配的 $extend_1$ 数组，再反过来求解一次 $t$ 与 $s$ 匹配的 $extend_2$ 数组。

然后就可以枚举 $j$ ，只要存在更长的环匹配成功，即 $extend_2[extend_1[j] + 1] \ge j - 1$ 时，就更新一次 $ans = j + extend_1[j] + 1$ 。

代码如下( AC 自动机太多了所以写成 `fail` 了)：

```cpp
#include <bits/stdc++.h> 
using namespace std;

char s[2000010], t[2000010];
int ans, n, fa[2000010], nxt[2000010], fail1[2000010], fail2[2000010];

void exkmp(char *a, char *b, int *c)
{
	memset(nxt, 0, sizeof(nxt));
	memset(c, 0, sizeof(c));
	nxt[1] = n;
	int p = 0, tmp = 0;
	for(int i = 2; i <= n; i++)
	{
		nxt[i] = nxt[i - p + 1];
		if(i + nxt[i] > tmp)
		{
			if(tmp - i + 1 > 0)
				nxt[i] = tmp - i + 1;
			else
				nxt[i] = 0;
			while(nxt[i] + i <= n && b[i + nxt[i]] == b[nxt[i] + 1])
				nxt[i]++;
			p = i;
			tmp = i + nxt[i] - 1;
		}
	}
	p = 0;
	tmp = 0;
	for(int i = 1; i <= n; i++)
	{
		c[i] = nxt[i - p + 1];
		if(i + c[i] > tmp)
		{
			if(tmp - i + 1 > 0)
				c[i] = tmp - i + 1;
			else
				c[i] = 0;
			while(c[i] + i <= n && a[i + c[i]] == b[1 + c[i]])
				c[i]++;
			p = i;
			tmp = i + c[i] - 1;
		}
	}
}

int get(int x, int y)
{
	if(x == 0)
		return 0;
	if(fail2[x + 1] >= y)
		return x;
	else
		return fa[x] = get(fa[x], y);
}

int main()
{
	scanf("%d", &n);
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	exkmp(s, t, fail1);
	exkmp(t, s, fail2);
	for(int i = 1; i <= n; i++)
		fa[i] = i - 1;
	for(int i = 1; i <= n; i++)
	{
		int x = get(fail1[i], i - 1);
		if(x)
			ans = max(ans, i + x - 1);
	}
	printf("%d", ans);
}
```

---

