# [POI 2002] B-Smooth 数

## 题目描述

$B$ 是一个正整数。

 如果一个自然数 $n$ 被称为 B-smooth 数,那么它的质因子中没有任何一个超过 $B$。 

我们说和 $n$ 等价的一个 B-smooth 数是指它能够表示成小于或等于  $B$ 的正整数乘积。 

你的任务是对给定的闭区间 $[n,n+m]$，求出他们中的 B-smooth 数的个数。

## 说明/提示

对于 $100\%$的数据，$1\le n\le 2\times 10^9$， $1\le m\le 10^8$， $1\le B\le 10^6$。

## 样例 #1

### 输入

```
30 10 5```

### 输出

```
4```

# 题解

## 作者：徐晨轩✅ (赞：2)

差分转化为求 $[1,x]$ 之间的 B-smooth 数。

记忆化搜索。先预处理出所有 $\le B$ 的质数。令 $f(x,i)$ 表示搜完前 $i-1$ 个质数，剩下的乘积 $\le x$ 的方案数。显然有 $f(x,i)=f(x,i+1)+f(\dfrac{x}{p_i},i)$ ，其中 $p_i$ 为第 $i$ 个质数。$f(x,1)$ 即为答案。

注意剪枝：如果 $p_i ^ 2 > x$，显然剩下的只能是单个质数（或者是 $1$）。二分即可统计方案数。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1000005;

int l, r, p, np[N];
vector<int> pr;
unordered_map<int, int> mem;

void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!np[i])
            pr.push_back(i);
        for (int j : pr) {
            if (i * j > n) break;
            np[i * j] = 1;
            if (i % j == 0) break;
        }
    }
}

int count_primes(int x, int i) {
    int l = i, r = pr.size() - 1, ans = i;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (pr[mid] <= x) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    return ans - i + 1;
}

int dfs(int x, int i = 0) {
    if (x < 1) return 0;
    if (i >= pr.size() || pr[i] > x) return 1;
    if (pr[i] * pr[i] > x) return count_primes(x, i) + 1;
    int id = x * pr.size() + i;
    if (mem.count(id)) return mem[id];
    return mem[id] = dfs(x, i + 1) + dfs(x / pr[i], i);
}

signed main() {
    cin >> l >> r >> p;
    r += l;
    init(p);
    cout << dfs(r) - dfs(l - 1) << endl;
    return 0;
}

```

---

## 作者：Leasier (赞：2)

前置芝士：[Min_25 筛](https://oi-wiki.org/math/min-25/)

考虑差分，定义**完全积性函数** $f(n)$ 仅当 $n$ 的每个质因数都 $\leq b$ 时取 $1$，其他时候值为 $0$。

此函数的前缀和显然可以用 Min_25 筛求出。时间复杂度为 $O(\frac{(n + m)^{\frac{3}{4}}}{\log{(n + m)}})$。

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef long long ll;

const int N = 1e6 + 37, M = 1e5 + 7, K = 5e4 + 7;
int prime[N], number[M], g[M], id1[K], id2[K];
bool p[N];

inline int get_id(ll n, int m, int k){
	return n <= m ? id1[n] : id2[k / n];
}

inline int init1(int &b, int &a){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i < N; i++){
		if (!p[i]) prime[++cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i <= cnt; i++){
		if (prime[i] > b && prime[i - 1] <= b){
			a = i - 1;
			break;
		}
	}
	for (register int i = 1; i <= cnt; i++){
		if (prime[i] >= b){
			b = prime[i];
			break;
		}
	}
	return cnt;
}

inline int init2(int n, int m, int cnt){
	int t = 0;
	for (register int i = 1, j; i <= n; i = j + 1){
		int tn = n / i;
		j = n / tn;
		t++;
		number[t] = tn;
		g[t] = tn - 1;
		if (tn <= m){
			id1[tn] = t;
		} else {
			id2[j] = t;
		}
	}
	for (register int i = 1; i <= cnt && prime[i] * prime[i] <= n; i++){
		int temp = prime[i] * prime[i];
		for (register int j = 1; j <= t && temp <= number[j]; j++){
			g[j] -= g[get_id(number[j] / prime[i], m, n)] - (i - 1);
		}
	}
	return cnt;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

int solve(ll n, int m, int k, int x, int b, int a, int cnt){
	if (prime[m] > n) return 0;
	int ans = min(g[get_id(n, k, x)], a) - min(m, a);
	for (register int i = m + 1; i <= cnt && prime[i] * prime[i] <= n && prime[i] <= b; i++){
		int j = 1;
		for (register ll y = prime[i]; y <= n; j++, y *= prime[i]){
			ans += solve(n / y, i, k, x, b, a, cnt) + (j > 1 ? 1 : 0);
		}
	}
	return ans;
}

inline int get_f_sum(int n, int m, int b, int a, int cnt){
	return solve(n, 0, m, n, b, a, cnt) + 1;
}

int main(){
	int n, m, k, x, b, a, cnt, ans;
	scanf("%d %d %d", &n, &m, &b);
	ans = m + 1;
	cnt = init1(b, a);
	k = n + m;
	x = sqrt(k);
	init2(k, x, cnt);
	ans -= k - get_f_sum(k, x, b, a, cnt);
	k = n - 1;
	x = sqrt(k);
	init2(k, x, cnt);
	ans += k - get_f_sum(k, x, b, a, cnt);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Betrayer_of_love (赞：1)

### 题目解析
------------
设 $f(c,l,r,k)$ 表示 $[l,s]$ 的数在分解完前 $c-1$ 个质因子，并且第 $c$ 个分解了 $k$ 个后，恰好为 $1$ 的个数（说白了，就是只有前 $c$ 个质数中的若干个）。

那么：$f(c,l,r,k)=f(c-1,l,r,k)+ f(c,\lceil\frac{l}{pc}\rceil,\lfloor \frac{r}{pc} \rfloor ,k-1)$。

解释一下：

首先 $k'$ 表示的是 $\max_{l \le x \le r ,p^k}|s^{k}$，这个应该很好理解。

然后第二个式子：显然我们可以把 $[l,r]$ 内的所有满足是 $p_c$ 的倍数的整数表示为： $\lceil\frac{l}{p_c}\rceil \times p_c,( \lceil \frac{l}{p_c}\rceil +1) \times p_c...,\lfloor \frac{r}{p_c} \rfloor \times p_c$，那么把所有的这些都除以一个 $p_c$ 就可以得到上面的这个式子，然后这个东西可以用**记忆化搜索**去算（其实并不需要真的去使用记忆化搜索，毕竟也开不下这么大的数据）。

由于递归的层数可以代替 $k$ ，那就可以不带 $k$ 玩了。

**可能需要一点优化，都在代码里了,请看正确代码！！！**

### CODE

```c
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX=1e6+10;
const int MOD=1e9+7;
inline char readchar() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline int read() {
#define readchar getchar
	int res = 0, f = 0;
	char ch = readchar();
	for(; !isdigit(ch); ch = readchar()) if(ch == '-') f = 1;
	for(; isdigit(ch);ch = readchar()) res = (res << 1) + (res << 3) + (ch ^ '0');
	return f ? -res : res;
}
inline void write(int x) {
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m,p,sum;
int vis[MAX],cnt,pri[MAX];
inline int f(int c,int l,int r){
	if(r<=pri[c])return r-l+1;
    if(c==1){
        return __lg(r) - __lg(l - 1);
    }
    if(l==r){
        int t=l;
        for(int i=c;i>=1;i--) while(t%pri[i]==0) t/=pri[i];
        if(t==1) return 1; return 0;
    } 
	return f(c-1,l,r)+f(c,(l+pri[c]-1)/pri[c],r/pri[c]);
}
signed main(){
	n=read(),m=read(),p=read();
	vis[1]=1;
	for(int i=2;i<=p;i++){
		if(!vis[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<=p;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0) break;
		}
	}
	cout<<f(cnt,n,n+m);
	return 0;

```


完结撒花，谢谢

---

## 作者：蒟蒻tyy (赞：1)

#### $\mathcal Description:$

$\quad$ 问你区间 $[l,r]$ 之间，最大质因子小于等于 $p$ 的数有几个。

#### $\mathcal Solution:$

$\bullet$ 楼上 ~~**所谓的正解**~~ 这里不再阐述。

$\bullet$ 这里一次性给出几种做法，顺便给出题目的加强版。

$\bullet$ 直接转换，考虑差分即可。

$\bullet\quad 1)$

$\quad$ 定义函数 $f$ 如下：

$$
f(n) = [maxp(n) \leq p]
$$

$\quad$ 其中 $maxp$ 代表数的最大质因子。

$\quad$ $f$ 完全积性，直接使用 $\text{Min\_25}$ 即可。

$\bullet\quad 2)$

$\quad$ 这题直接暴力搜索即可，加上适当手段减枝，甚至可以通过 $l,r\leq 10^{13},p \leq 2 \cdot 10^7$ 的版本。

$\bullet\quad 3)$ 

$\quad$ 如果你足够无聊的话可以考虑素因子的影响直接**逆向**实现 $\text{Min\_25}$ 来达到求和的效果。但是实际上效果没前两种效果好。

$\quad$ **本题的加强版**

$$l,r,p \leq 10^9$$

$\quad\bullet$ 当 $p \leq \sqrt n$ 的时候，可以参考上面的方案。

$\quad\bullet$ 当 $p$ 大的时候考虑影响后，数论分块，区间素数个数，结合两次 $\text{Min\_25}$ 可以实现。



---

