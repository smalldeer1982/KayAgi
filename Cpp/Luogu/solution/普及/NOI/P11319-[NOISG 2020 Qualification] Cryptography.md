# [NOISG 2020 Qualification] Cryptography

## 题目背景

Charles 是一位密码学家，他正在研究生成随机数的新方法。他试图通过组合多个随机数源来创建一个密码学安全的伪随机数生成器（CSPRNG）。

## 题目描述

他发明了一种算法，包括以下步骤：

1. 随机生成一个长度为 $N$ 的正整数序列 $S$，其中元素两两不同。
2. 随机打乱 $S$，得到一个长度为 $N$ 的排列 $P$。
3. 计算排列 $P$ 的字典序排名。
4. 输出排名对 $10^9 + 7$ 取模的结果。

排列 $P$ 的字典序排名定义为所有小于等于 $P$ 的排列数量。

Charles 是一位密码学家，但不是程序员。现在，给定排列 $P$，请帮助 Charles 计算其字典序排名，并对 $10^9 + 7$ 取模。

## 说明/提示

【样例解释】

对于样例 #1，以下是所有排列的字典序：

1. $[1, 42, 100]$ 
2. $[1, 100, 42]$
3. $[42, 1, 100]$
4. $[42, 100, 1]$
5. $[100, 1, 42]$
6. $[100, 42, 1]$

排列 $[42, 100, 1]$ 的字典序排名为 $4$。

【数据范围】

- $1 \leq N \leq 3 \times 10^5$  
- $1 \leq P_i \leq 10^9$  
- 对于任意 $i \neq j$，$P_i \neq P_j$

| 子任务编号 | 分值       | 限制条件                                              |
|:--------:|:---------:|:--------------------------------------------------:|
| $1$      | $5$       | $N = 2$                                              |
| $2$      | $9$       | $1 \leq N \leq 8$                                    |
| $3$      | $10$      | $P$ 为严格递增或递减                                 |
| $4$      | $11$      | $P = [k, 1, \dots, k-1, k+1, \dots, N]$，$1 \leq k \leq N$ |
| $5$      | $21$      | $1 \leq N \leq 3 \times 10^3, 1 \leq P_i \leq N$     |
| $6$      | $13$      | $1 \leq N \leq 3 \times 10^3$                        |
| $7$      | $19$      | $1 \leq P_i \leq N$                                  |
| $8$      | $12$      | 无其他特殊限制                                       |

## 样例 #1

### 输入

```
3
42 100 1```

### 输出

```
4```

## 样例 #2

### 输入

```
5
1 5 2 4 3```

### 输出

```
20```

## 样例 #3

### 输入

```
2
2 1```

### 输出

```
2```

# 题解

## 作者：Eason_cyx (赞：2)

无聊缝合怪题。就是俩板子合一起了。

-----

你会发现这些“随机打乱”和所谓的字典序，都是按照相对大小排序的。那么每个数具体是多少其实不重要，那么直接离散化。离散化完了之后就转换成了 [【模板】康托展开](https://www.luogu.com.cn/problem/P5367)，不会的可以去学习一下，此处直接贺板子即可。

时间复杂度瓶颈在离散化的排序和康托展开的树状数组。总时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Mod = 1e9 + 7;
long long jc[1000005], tree[1000005], rk[1000005], n, ans = 1;
struct node { long long id,x;
	bool operator < (const node& y) const { return x < y.x; }
} a[1000005]; long long lowbit(long long x) { return x & (-x); }
long long sum(long long x) {
	long long ans = 0; while(x) ans += tree[x] % Mod, x -= lowbit(x);
	return ans % Mod;
} void add(long long x,long long k) {
	while(x <= n) tree[x] += k, x += lowbit(x);
} int main() { cin >> n; jc[0] = 1;
	for(int i = 1;i <= n;i++) cin >> a[i].x, a[i].id = i;
	sort(a+1,a+n+1); for(int i = 1;i <= n;i++) rk[a[i].id] = i;
	for(int i = 1;i <= n;i++) jc[i] = jc[i-1] * i % Mod, jc[i] %= Mod;
	for(int i = 1;i <= n;i++) add(i,1); for(int i = 1;i <= n;i++) {
		ans += ((sum(rk[i]) - 1) * jc[n-i] % Mod) % Mod; add(rk[i],-1);
	} cout << ans % Mod << endl;
	return 0;
}
```

---

## 作者：Soviet_Onion (赞：1)

## P11319 Cryptography 题解
### Solution
板子题吧，参考[这个](https://www.luogu.com.cn/problem/P5367)。

计算排列排名的方法如下：

$$S=1+\displaystyle{\sum^{n}_{i=1}A_i\times(n-i)!}$$

其中 $A_i$ 的计算方法如下：
$$A_i=\displaystyle{\sum^{n}_{j=i}[a_i>a_j]}$$

显然，暴力肯定会爆炸。下面开始优化。
### 优化
- 其实阶乘没有必要每次都循环计算。我们可以使用一个变量 $fac$ 来代替它。公式中的 $(n-i)!$ 实质上就是依次计算 $1!,2!,\dots,n!$，因为是倒着计算，如下文，所以每次可以令 $fac \gets fac\times i$。
- 离散化：由于排列中每个数字都只出现了一次，所以其实序列的值并不重要。重要的是元素之间的**相对排名**。因此，我们可以将数组排序，然后进行二分查找操作，以确定每个数的排名。
- 下面是重点：计算 $A_i$。

首先，因为 $A_i$ 只和 $i$ 位置之后的元素有关，所以我们可以倒序存储序列，或者倒着扫。由于前面的离散化操作已经使得排列中的每一项都在 $1$ 到 $n$ 范围以内，所以我们可以对 $1$ 到 $n$ 建立**树状数组** $c$。每次扫到一个元素 $P_i$，就查询 $c_1$ 到 $c_{P_i-1}$ 的前缀和；然后将 $c_{P_i}$ 位置增加 $1$。具体可参考树状数组模板题写法。不难发现 $c_i$ 的含义是**目前为止**有多少个 $i$ 出现在当前扫到的排列当中。同时由于排列的性质，本题中 $c_i$ 最大值是 $1$。

上述方法同时也是求逆序对的方法。（题外话）

### 结语&注意事项
至此本题解就基本结束了。本题考察的知识点比较多，细节也比较多，是一道比较不错的题。
- 取模 $10^9+7$。
- 最后加 $1$ 之后不要忘记取模。（好习惯）
### [AC](https://www.luogu.com.cn/record/191588279) Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=3e5+10;
const int MOD=1e9+7;
int a[N],p[N],l[N],n;
long long JC=1,ans;
int main(){
	cin>>n;
	for(int i=n;i>=1;i--) cin>>a[i],p[i]=a[i];
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++) a[i]=lower_bound(p+1,p+n+1,a[i])-p;
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=a[i];j>=1;j-=(j&(-j))) sum+=l[j];
		ans=(long long)(ans+sum*JC)%MOD;
		JC=1LL*JC*i%MOD;
		for(int j=a[i];j<=n;j+=(j&(-j))) l[j]++;
	}
	cout<<(ans+1)%MOD<<endl;
	return 0;
} 
```

---

## 作者：ben090302 (赞：1)

首先离散化把原数组映射成一个排列，然后就是康拓展开的板子了，树状数组优化一下就能做到 $n\log n$。

```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
const int mod=1e9+7;
int n;

pair<int,int> a[N];
int p[N];
long long fac[N];
int tr[N];
void add(int x){
	for(int i=x;i<=n;i+=(i&-i)) tr[i]++;
}
int ask(int x){
	int ret=0;
	for(int i=x;i;i-=(i&-i)) ret+=tr[i];
	return ret;
}
long long ans=1;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	fac[0]=1;
	for(int i=1;i<=n;i++) cin>>a[i].first,a[i].second=i,fac[i]=fac[i-1]*i%mod;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		p[a[i].second]=i;
	}
	for(int i=n;i>=1;i--){
		ans=(ans+(ask(p[i])%mod)*fac[n-i]%mod)%mod;
		add(p[i]);
	}
	cout<<ans;
}
```

---

## 作者：PCSJZ (赞：0)

## 康托展开

[模版](https://www.luogu.com.cn/problem/P5367)

给大家一个式子，这个式子就是康托展开的模版。

$rank = 1 + \sum_{i=1}^{n} a_n \times (n-i)!$ 

然后我们对这个排列 $P$ 进行离散化，最后直接来个康托展开的模版就行了。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>


using namespace std;

const int maxm = 1000006;
const int mod = 1e9 + 7;
typedef long long ll;
ll fac[maxm], c[maxm], pos[maxm], n, ans = 1;
// 因为计算排名，所以 ans 初始为 1 
// c 为树状数组 

struct node {
	ll id, x;
}a[maxm];

bool cmp(node x, node y) {
	return x.x < y.x;
}

ll lowbit(ll x) {
	return x & -x; 
}

ll sum(ll x) { // 求和 
	ll ans = 0;
	while (x > 0) {
		ans += c[x] % mod;
		x -= lowbit(x);
	}
	return ans % mod;
}

void add(ll x, ll k) { // 增加 k  
	while (x <= n) {
		c[x] += k;
		x += lowbit(x);
	}
}

int main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%lld", &a[i].x), a[i].id = i;
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		pos[a[i].id] = i; // 离散化，使数值减小并且更加清楚 
	fac[0] = 1; // fac 计算阶乘 
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i-1] * i % mod;
		fac[i] %= mod;
	}
	// 康托展开模版 
	for (int i = 1; i <= n; i++) add(i, 1);
	for (int i = 1; i <= n; i++) {
		ans += ((sum(pos[i]) - 1) * fac[n - i] % mod) % mod;
		add(pos[i], -1);
	}
	printf("%lld\n", ans % mod);
	return 0;
}
``````

---

## 作者：DFM_O (赞：0)

## [P11319 题目](https://www.luogu.com.cn/problem/P11319)

### 解题思路
首先把原数组离散化一下，定义 $b_i$ 为所有 $j\in (i,n]$ 中满足 $a_j<a_i$ 的个数。

易知排名即为 $\sum^n_{i=1} (n-i)!\times b_i$。

然后就变成逆序对板子题了，树状数组优化即可。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const long long p=1e9+7;
int c[2000001],jc[300001],a[300001],b[300001],n;
inline void add(int x,int y)
{
	for(;x<=n;x+=x&-x)
		c[x]+=y;
}
inline int ask(int x)
{
	int s=0;
	for(;x>0;x-=x&-x)
		s+=c[x];
	return s;
}
signed main()
{
	ios::sync_with_stdio(false);
	jc[0]=1,jc[1]=1;
	for(int i=2;i<=300000;i++)
		jc[i]=jc[i-1]*i%p;
	int s=1;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],b[i]=a[i],add(i,1);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	for(int i=1;i<=n;i++)
	{
		int x=a[i];
		s=(s+(ask(x)-1)*jc[n-i]%p)%p;
		add(x,-1),add(n+1,1);
	}
	cout<<s;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

简单题，建议绿。

考虑钦定前缀 $[1, i - 1]$ 是相同的，我们要统计 $i \in [1, n]$ 的答案。

要使得字典序更小，只需要 $a_i' < a_i$ 即可；然后后面的 $(n - i)$ 位是全排列；则令 $h$ 表示第 $i$ 位能填的 $< a_i$ 的数的个数，贡献为 $h \times (n-i)!$。

求 $h$ 可以直接树状数组，时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define fi first
#define se second
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 3e5 + 10, mod = 1e9 + 7;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, ans;
int a[N], h[N], f[N], t[N];
inline void add(int x){
	for(int i = x; i <= n; i += lowbit(i))
	  ++t[i];
}
inline int ask(int x){
	int ans = 0;
	for(int i = x; i; i -= lowbit(i))
	  ans += t[i];
	return ans;
}
bool End;
int main(){
	f[0] = f[1] = 1;
	n = read();
	for(int i = 1; i <= n; ++i){
		f[i] = 1ll * i * f[i - 1] % mod;
		a[i] = read();
		h[i] = a[i];
	}
	sort(h + 1, h + n + 1);
	for(int i = 1; i <= n; ++i){
		a[i] = lower_bound(h + 1, h + n + 1, a[i]) - h;
		ans = (ans + 1ll * f[n - i] * (a[i] - ask(a[i]) - 1) % mod) % mod;
		add(a[i]);
	}
	write((ans + 1) % mod);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：LG086 (赞：0)

给出一个长度为 $n$ 的序列 $P$，求它的字典序排名。这很容易想到[康托展开](https://www.luogu.com.cn/problem/P5367)。


---


对于康托展开，有如下式子：

$$
ans = 1 + \sum^n_{i=1} {a_i \times (n-i)!}
$$

其中 $a_i$ 表示在 $i+1$ 到 $n$ 的范围内大于 $P_i$ 的数的个数。

又由于 $n\le3\times 10^5$，所以直接 $O(n^2)$ 会炸，所以需要用到树状数组进行一定优化，时间复杂度 $O(n\log n)$。

以上操作均与模板题的操作相同。



---



还有几点需要注意：

- 给出的数字并不保证为 $1$ 到 $n$ 的排列。对于这一点，可以先进行从小到大的排序，记录每个数字的排名，并将每个数的值替换为它的排名。
- 输出 $ans+1$ 时也要取模。对于这一点，只需要在输出时再取模一遍即可。

---

