# Vasya and Big Integers

## 题目描述

Vasya 拥有三个大整数 $a, l, r$。我们定义 $x$ 的一种划分为一组字符串序列 $s_1, s_2, \dots, s_k$，使得 $s_1 + s_2 + \dots + s_k = x$，其中 $+$ 表示字符串的拼接。$s_i$ 是划分中的第 $i$ 个元素。例如，数字 $12345$ 有如下划分方式：\["1", "2", "3", "4", "5"\]，\["123", "4", "5"\]，\["1", "2345"\]，\["12345"\]，以及许多其他方式。

我们称 $a$ 的某种划分为“美丽的”，如果其每个元素都不包含前导零。

Vasya 想知道，$a$ 的美丽划分中，有多少种划分使得每个 $s_i$ 都满足 $l \le s_i \le r$。注意，这里的比较是整数比较，而不是字符串比较。

请你帮助 Vasya 计算满足所有要求的划分数量。由于结果可能非常大，请输出对 $998244353$ 取模后的结果。

## 说明/提示

在第一个测试用例中，有两种合法划分方式：$13+5$ 和 $1+3+5$。

在第二个测试用例中，有一种合法划分方式：$1+0+0+0+0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
135
1
15
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10000
0
9
```

### 输出

```
1
```

# 题解

## 作者：Dilute (赞：13)

[$$\color{darkblue}\huge\texttt{在本人blog食用更佳}$$](https://dilute.xyz/2019/05/28/Solutions/Solution-CF1051E/)

## 哈希 + 二分 + DP

首先看到题面，很容易想到一个$DP$，令$f[i]$为划分到$i$为止的方案数。

然后朴素的暴力转移是$O(n^2)$的，非常显然一个状态$i$能够转移到的$j$是一段连续的，进而想到使用前缀和优化。

<!--more-->

令$l$的长度为$sl$，$r$的长度为$sr$，那么长度为$len$（$sl < len < sr$）的一段数字$s$必定满足$l < s < r$。然后那么我们只需要考虑当前状态$i$的时候$[i, i + sl)$和$[i,i + sr)$这两段区间分别和$l,r$的大小关系。

如果我们我们要比较两个字符串$a$和$b$的大小关系，我们完全先特判掉两个完全一样的情况，然后再求出它们的$lcp$，然后那么$a$和$b$的大小关系就是$a[lcp + 1]$和$b[lcp + 1]$的大小关系了。

$lcp$可以哈希 + 二分解决，接下来的事情就是$DP$的了

## 代码实现

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647
#define mod 998244353
#define px 11
#define mul(a, b) ((ll)(a) * (ll)(b) % mod)

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

char s[1000010], l[1000010], r[1000010];
ll f[1000010], sum[1000010];
int n, sl, sr, pl[1000010], pr[1000010], hshs[1000010], hshl[1000010], hshr[1000010], fpow[1000010];

bool ok1(int x){
    if(x + sl - 1 > n)
        return false;
    if(sl == pl[x])
        return true;
    return l[pl[x] + 1] < s[x + pl[x]];
}

bool ok2(int x){
    if(x + sr - 1 > n)
        return false;
    if(pr[x] == sr)
        return true;
    return r[pr[x] + 1] > s[x + pr[x]];
}

int get_hsh(int *hsh, int l, int r){
    return (hsh[r] - mul(hsh[l - 1], fpow[r - l + 1]) + mod) % mod;
}

void solve(int *s, int *hsh, int len){ // 求lcp
    for(int i = 1; i <= n - len + 1; i++){
        int l = 0;
        int r = len;
        while(l < r){
            int mid = (l + r + 1) >> 1;
            if(get_hsh(hshs, i, i + mid - 1) == get_hsh(hsh, 1, mid))
                l = mid;
            else
                r = mid - 1;
        }
        s[i] = l;
    }
}

void gethash(char *str, int *hsh, int len){
    for(int i = 1; i <= len; i++)
        hsh[i] = ((ll)(hsh[i - 1]) * (ll)(px) + str[i] - '0' + 1) % mod;
}

int main(){
    fpow[0] = 1;
    for(int i = 1; i <= 1000000; i++)
        fpow[i] = mul(fpow[i - 1], px);
    scanf("%s", s + 1);
    scanf("%s", l + 1);
    scanf("%s", r + 1);
    n = strlen(s + 1);
    sl = strlen(l + 1);
    sr = strlen(r + 1);
    gethash(l, hshl, sl);
    gethash(r, hshr, sr);
    gethash(s, hshs, n);
    f[0] = 1;
    solve(pl, hshl, sl);
    solve(pr, hshr, sr);
    // for(int i = 1; i <= n; i++)
    //     printf("%d ", pl[i]);
    // putchar('\n');
    // for(int i = 1; i <= n; i++)
    //     printf("%d ", pr[i]);
    // putchar('\n');
    for(int i = 0; i <= n; i++){
        if(i){
            sum[i] += sum[i - 1];
            f[i] += sum[i];
            f[i] %= mod;
        }
        // printf("f[%d] = %d\n", i, f[i]);
        if(s[i + 1] == '0'){
            if(sl == 1 && l[1] == '0'){
                f[i + 1] += f[i];
                f[i + 1] %= mod;
            }
            continue;
        }
        if(sl < sr){
            sum[sl + i + 1] += f[i];
            sum[sl + i + 1] %= mod;
            sum[sr + i] += mod - f[i];
            sum[sr + i] %= mod;
        }
        if(sl == sr){
            if(ok1(i + 1) && ok2(i + 1)){
                f[i + sl] += f[i];
                f[i + sl] %= mod;
            }
        } else {
            if(ok1(i + 1)){
                f[i + sl] += f[i];
                f[i + sl] %= mod;
            }
            if(ok2(i + 1)){
                f[i + sr] += f[i];
                f[i + sr] %= mod;
            }
        }
        // printf("f[%d] = %d\n", i, f[i]);
    }
    std::cout << f[n] << std::endl;
}
```



---

## 作者：fighter (赞：8)

关于dp这一部分， Dilute大佬讲得非常好，大家可以去%一下，这里主要是提出一点复杂度的优化。

由于我们在dp转移判断的时候，需要求出一个模式串和原字符串中一段的LCP，如果采用二分+哈希的话，复杂度是$O(n\log n)$的。

但是我们实际上可以把这个看成模式串与原串的一个后缀求LCP，那么就可以用exkmp（z函数）进行$O(n)$预处理，然后$O(1)$求LCP。

如果你不知道什么是exkmp，可以去模板区看看。

[P5410 【模板】扩展 KMP（Z 函数）](https://www.luogu.com.cn/problem/P5410)

## 代码

一些dp实现的细节上参考了Dilute大佬。

```cpp
#include <bits/stdc++.h>
#define MAX 2000005
#define ll long long
#define P 998244353
using namespace std;

struct exkmp{
    int n;
    int z[MAX], p[MAX];
    char str[MAX];
    void build(char *s){
        n = strlen(s+1);
        z[1] = n, str[1] = s[1];
        for(int i = 2, l = 0, r = 0; i <= n; i++){
            str[i] = s[i];
            if(i <= r) z[i] = min(z[i-l+1], r-i+1);
            while(i+z[i] <= n && s[i+z[i]] == s[z[i]+1]) z[i]++;
            if(i+z[i]-1 > r) r = i+z[i]-1, l = i;
        }
    }
    void get_lcp(char *s){
        int m = strlen(s+1);
        for(int i = 1, l = 0, r = 0; i <= m; i++){
            if(i <= r) p[i] = min(z[i-l+1], r-i+1);
            while(i+p[i] <= m && s[i+p[i]] == str[p[i]+1]) p[i]++;
            if(i+p[i]-1 > r) r = i+p[i]-1, l = i;
        }
    }
}L, R;

char a[MAX], l[MAX], r[MAX];
int n;
ll f[MAX], g[MAX];

void add(ll &a, ll b){
    a += b;
    if(a >= P) a -= P;
    if(a < 0) a += P;
}

bool chk(int x, int len){
    int p = L.p[x], f1 = 0, f2 = 0;
    if(L.n < len || p == L.n || L.str[p+1] < a[x+p]) f1 = 1;
    p = R.p[x];
    if(R.n > len || p == R.n || R.str[p+1] > a[x+p]) f2 = 1;
    return (f1 && f2);
}

int main()
{
    scanf("%s%s%s", a+1, l+1, r+1);
    n = strlen(a+1);
    L.build(l), R.build(r);
    L.get_lcp(a), R.get_lcp(a);
    f[0] = 1;
    for(int i = 0; i <= n; i++){
        if(i) add(g[i], g[i-1]), add(f[i], g[i]);
        if(a[i+1] == '0'){
            if(L.n == 1 && L.str[1] == '0') add(f[i+1], f[i]);
            continue;
        }
        if(L.n < R.n) add(g[i+L.n+1], f[i]), add(g[i+R.n], -f[i]);
        if(chk(i+1, L.n)) add(f[i+L.n], f[i]);
        if(R.n != L.n && chk(i+1, R.n)) add(f[i+R.n], f[i]);
    }
    cout << f[n] << endl;

    return 0;
}
```

---

## 作者：Nangu (赞：2)

## 解法一
设 $f_i$ 表示从后往前在第 $i$ 位前分割的情况数。可得 $f_i=\sum f_j$，其中 $l\le a_{i, j}\le r$。判断是否合法 $O(n)$，状态数 $O(n)$，转移 $O(n)$，总复杂度 $O(n^3)$。
## 解法二
令 $sl$ 为 $l$ 的长度，$sr$ 为 $r$ 的长度，那么若 $sl< j-i+1< sr$，$j$ 必然合法。只需要判断两个边缘情况是否合法即可。对于中间的情况，我们可以记录 $f$ 数组的后缀和，进行 $O(1)$ 的转移。总复杂度 $O(n^2)$。
## 解法三
对于两种边缘情况，我们可以用一种 $O(\log n)$ 的算法判断是否合法：

- 预处理出字符串哈希后的值
- 进行二分查找，找到两字符串第一个不相等的位置
- 判断这个位置两字符串的大小

然后，总复杂度就降为了 $O(n \log n)$ 了，可以通过此题。

# Code
~~记得千万别用自然溢出啊，卡了我亿年~~
```cpp
#include <bits/stdc++.h>
 
#define F(i, j, k) for(int i=(j), ENDD=(k); i<=ENDD; ++i)
#define R(i, j, k) for(int i=(j), ENDD=(k); i>=ENDD; --i)
#define de(x) cout<<#x<<' '<<x<<"  "
#define end cout<<'\n'
#define md(x) (x<mod?x:x-mod)
#define int long long
 
using namespace std;
 
typedef long long ll;
 
const int N=2e6+7, mod=998244353;
const ll base=13, p=mod;
 
char a[N], l[N], r[N];
ll ha[N], hl[N], hr[N], power[N];
int sum[N], f[N], n, sl, sr;
 
void get_hash(char *s, ll *a, int len){
	a[0]=0;
	F(i, 1, len) a[i]=(a[i-1]*base+s[i]-'0')%p;
}
 
inline ll calc(ll *a, int l, int r){
	return (a[r]-a[l-1]*power[r-l+1]%p+p)%p;
}
 
int n_lcp(ll *a, ll *b, int len){
	int l=0, r=len, mid;
	while(l<r){
		mid=l+r>>1;
		calc(a, 0, mid)==calc(b, 0, mid)?(l=mid+1):(r=mid);
	}
	return l;
}
 
inline int cmp(ll *a, ll *b, char *c, char *d, int len){
	int pos=n_lcp(a, b, len);
	return pos==len?2:(c[pos]>d[pos]);
}
 
signed main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>a+1>>l+1>>r+1;
	n=strlen(a+1), sl=strlen(l+1), sr=strlen(r+1);
	power[0]=1;
	F(i, 1, max({n, sl, sr})) power[i]=power[i-1]*base%p;
	get_hash(a, ha, n);
	get_hash(l, hl, sl);
	get_hash(r, hr, sr);
	int pl, pr;
	sum[n+1]=f[n+1]=1;
	R(i, n, 1){
		if(i+sl-1>n || a[i]=='0' && !(sl==1 && l[1]=='0')){
			sum[i]=sum[i+1];
			continue;
		}
		if(a[i]=='0')
			pl=i, pr=i;
		else
			pl=i+sl-(cmp(ha+i, hl+1, a+i, l+1, sl)!=0),
			pr=i+sr-2+(i+sr-1<=n && cmp(ha+i, hr+1, a+i, r+1, sr)!=1);
		if(pl>pr) return cout<<0, 0;
		f[i]=(sum[pl+1]-sum[pr+2]+mod)%mod;
		sum[i]=md(sum[i+1]+f[i]);
	}
	cout<<f[1];
 	return 0;
}
```
~~写题解不易，给个赞再走呗~~

---

## 作者：Skykguj (赞：2)

不难想到一个 dp：设 $f_i$ 表示划分完 $1\sim i$ 的方案数，那么 $f_i \gets f_j, j < i$，这显然是一个 $O(n^3)$ 的做法。

可以发现能转移到 $f_i$ 的是一段连续的区间，但是中间的 $0$ 不能转移到 $f_i$。由于 $f_i$ 可以转移到的状态也是一段连续的区间，可以想到用 $f_i$ 去转移其他的状态。

$f_i \to f_j, j \in [i+|l|, i+|r|]$。

事实上这个区间中只有 $i+|l|$ 和 $i+|r|$ 可能转移不到 $f_i$，那么我们就有了一个优秀的 $O(n^2)$ 的做法：

https://codeforces.com/contest/1051/submission/234047134

那么转移实质上是一个单点查，区间加，直接树状数组维护即可，复杂度的瓶颈变成了检验转移是否合法。

同时检验是一个经典的字符串字典序比较问题，直接用 $hash$ + 二分求最长公共前缀判断下一个位置的大小即可。

时间复杂度 $O(n \log n)$。

然而这题卡自然溢出，WA 了 100 年。

代码很简单：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
 
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}
 
const int N = 1000010;
const int mod = 998244353;
const int base = 2009107;
const int hash_mod = 1e9 + 9;
 
char a[N], l[N], r[N];
int n, sl, sr, max_len, f[N], tr[N];
ll hsh[5][N], pw[N];
 
ll get(int l, int r, ll hsh[]) {
	return (hsh[r] - hsh[l - 1] * pw[r - l + 1] % hash_mod + hash_mod) % hash_mod;
}

bool check(int st, int ed) {
	int len = ed - st + 1;
	if (len == sl) {
		int ql = 1, qr = sl, ans = 0;
		while (ql <= qr) {
			int mid = (ql + qr) >> 1;
			if (get(1, mid, hsh[0]) == get(st, st + mid - 1, hsh[2])) ql = mid + 1, ans = mid;
			else qr = mid - 1;
		}
		if (ans != sl && l[ans + 1] > a[st + ans]) return false;
	}
	if (len == sr) {
		int ql = 1, qr = sr, ans = 0;
		while (ql <= qr) {
			int mid = (ql + qr) >> 1;
			if (get(1, mid, hsh[1]) == get(st, st + mid - 1, hsh[2])) ql = mid + 1, ans = mid;
			else qr = mid - 1;
		}
		if (ans != sr && r[ans + 1] < a[st + ans]) return false;
	}
	return true;
}
 
int lowbit(int x) { return x & -x; }
 
int query(int pos) {
	int res = 0; pos ++ ;
	for (; pos; pos -= lowbit(pos)) res = (res + tr[pos]) % mod;
	return res;
}
 
void modify(int pos, int x) { pos ++ ; for (; pos <= n + 1; pos += lowbit(pos)) tr[pos] = (tr[pos] + x) % mod; }
void modifyPoint(int pos, int x) { modify(pos, x), modify(pos + 1, mod - x); }
 
int main() {
	scanf("%s%s%s", a + 1, l + 1, r + 1);
	n = strlen(a + 1), sl = strlen(l + 1), sr = strlen(r + 1), pw[0] = 1;
	max_len = max({n, sl, sr});
	for (int i = 1; i <= max_len; i ++ ) pw[i] = pw[i - 1] * base % hash_mod;
	for (int i = 1; i <= sl; i ++ ) hsh[0][i] = (hsh[0][i - 1] * base % hash_mod + l[i]) % hash_mod;
	for (int i = 1; i <= sr; i ++ ) hsh[1][i] = (hsh[1][i - 1] * base % hash_mod + r[i]) % hash_mod;
	for (int i = 1; i <= n; i ++ ) hsh[2][i] = (hsh[2][i - 1] * base % hash_mod + a[i]) % hash_mod;
	modifyPoint(0, 1);
	for (int i = 0; i <= n; i ++ ) {
		int down = i + sl, up = min(i + sr, n), val = query(i);
		if (down > up) continue;
		if (a[i + 1] == '0') { // 下一段的开头如果是 0 的话，只能转移到 f[i + 1]。
			if (down == i + 1) modifyPoint(down, val * check(i + 1, down));
			continue;
		}
		modifyPoint(down, val * check(i + 1, down));
		if (down + 1 <= up) { // 注意 down == up 时，不能转移。
			modifyPoint(up, val * check(i + 1, up));
			modify(down + 1, val), modify(up, mod - val);
		}
	}
	printf("%d\n", query(n));
	return 0;
}
```

---

## 作者：zhongpeilin (赞：2)

## 题目大意：
有一个正整数 $N$，还有两个数 $l, r$ 询问有多少种划分方案使得将 $N$ 划分成 $a_{1}, a_{2}, \dots$，且 $l \le a_{i} \le r$，答案模 $998244353$。  
## 解题思路：
首先我们不难想到 dp，那么我们设 $dp_{i}$ 表示 $N$ 的前 $i$ 位有多少划分方案。这样我们就有了个 $O(n^3)$ 的转移，就是枚举 $i$，枚举分割点 $j$，比较大小。  
这样显然不行，但不难发现合法的 $j$ 是一段区间，而我们可以二分左端点，二分右端点，从而前缀和优化一下，降到 $O(n^2 \log n)$。  
还是过不了，再想怎么优化比较。首先我们要会字符串的比较，就是通过二分加哈希去解决，为什么要加一个二分呢？因为哈希只能比较相不相同，不能直接比较大小，所以需要二分出最后一个前缀相同的位置，再比较一下下一个字符。  
但是他要求的是数字比较，不过我们发现当数位相同的时候，可以直接字符串比较，而字符不同的时候，直接比较长度即可，所以数字比较能与处理哈希的话，也可以做到 $O(\log n)$。  
而我们所需要比较的，是 $N$ 的子串，和 $l, r$。所以可以预处理哈希。结合二分分割点，$O(n \log_{2}^2 n)$。  
**注：因为作者为了方便没有前导 0，没写上面所说的 dp，而是写的枚举 $i$ 后二分一下他可以更改的部分，用树状数组维护的差分序列，不过同理**。  
那里细节不懂可以私信作者 QWQ!
## code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int MOD = 1000000009;
const int sed = 423;

int dp[1000005];
int pw[1000005], llen, rlen;
int hs[4][1000005], C[1000005];
string n, l, r;

int get_hash(int id, int L, int R){ //取hash
	return (hs[id][R] - hs[id][L - 1] * pw[R - L + 1] % MOD + MOD) % MOD;
}

int Com(int L, int R, int i){ //N的子串左右端点，在比较l还是r，i=2是l，i=3是r 
	int maxn = (i == 2 ? llen : rlen); //去出长度
	if(R - L + 1 > maxn) return 2; //比较长度
	else if(R - L + 1 < maxn) return 0;
	
	int LL = 1, RR = maxn, ans = 1; //二分出来最大相同，不过ans存的是第一个不同的位置
	while(LL <= RR){
		int mid = (LL + RR) / 2;
		if(get_hash(1, L, L + mid - 1) == get_hash(i, 1, mid)){ //比较hash
			ans = mid + 1;
			LL = mid + 1;
		} else {
			RR = mid - 1;
		} 
	}
	if(ans == maxn + 1) return 1; //相同
	
	if(i == 2){ //判断大小
		if(n[ans + L - 1] < l[ans]) return 0;
		return 2;
	}
	if(n[ans + L - 1] < r[ans]) return 0;
	return 2;
}

int check(int L, int R){ //0是<l, 1是在l,r之间，2是大于r
	if(Com(L, R, 2) == 0) return 0; 
	if(Com(L, R, 3) == 2) return 2;
	return 1; 
}


void add(int x, int c){ //树状数组
	for(int i = x; i <= 1000000; i += (i & (-i))) C[i] = (C[i] + c) % mod;
}
int ask(int x){
	int ans = 0;
	for(int i = x; i; i -= (i & (-i))) ans = (ans + C[i]) % mod;
	return ans;
}
void solve(){
	cin >> n >> l >> r;
	llen = l.size(); rlen = r.size();
	n = " " + n; l = " " + l; r = " " + r;
	
	pw[0] = 1;
	for(int i = 1; i <= 1000000; i++) pw[i] = pw[i - 1] * sed % MOD;
	for(int i = 1; i < n.size(); i++) hs[1][i] = (hs[1][i - 1] * sed % MOD + n[i]) % MOD;
	for(int i = 1; i < l.size(); i++) hs[2][i] = (hs[2][i - 1] * sed % MOD + l[i]) % MOD;
	for(int i = 1; i < r.size(); i++) hs[3][i] = (hs[3][i - 1] * sed % MOD + r[i]) % MOD;
	//以上预处理哈希
	
	dp[0] = 1;
	for(int i = 0; i < n.size(); i++){
		if(i > 0){
			dp[i] = (dp[i] + ask(i)) % mod;
			//在这里算dp[i]
		}
		if(i == n.size() - 1) continue; //终止
		if(n[i + 1] == '0'){ //这样只能圈1个
			if(l[1] != '0') continue;
			dp[i + 1] = (dp[i + 1] + dp[i]) % mod; //直接加上
			continue;
		}
		
		int l = i + 1, r = n.size() - 1, ansl = 1, ansr = 0;
		while(l <= r){ //这里是二分合法左端点
			int mid = (l + r) / 2;
			int val = check(i + 1, mid); //获取小了，在l~r之间，大于r
			if(val == 0) l = mid + 1;
			else { 
				r = mid - 1;
				if(val == 1) ansl = mid; //只有满足条件才能改变答案
			}
		}
		
		l = i + 1, r = n.size() - 1;
		while(l <= r){ //二分合法右端点
			int mid = (l + r) / 2;
			int val = check(i + 1, mid); //上面同理
			if(val <= 1){
				l = mid + 1;
				if(val == 1) ansr = mid;
			} else r = mid - 1;
		}
		if(ansl > ansr) continue; //如果没有合适的，不改了
		
		add(ansl, dp[i]);//维护的差分数组，不过也可以用线段树
		add(ansr + 1, mod - dp[i]);
	}
	cout << dp[n.size() - 1] << endl; //输出答案
}
signed main(){
	ios::sync_with_stdio(false);
	solve();
	return 0;
} 
```
点个赞吧 QWQ！

---

## 作者：C　C　A (赞：2)

$\quad\rm ExKMP+$前缀和优化 $\rm DP$。

$\quad$记 $f_i$ 表示 $a_{1\sim i}$ 有多少种合法的划分方案，显然有一个 $\Theta(n^2)$ 的暴力 $\rm DP$，即往前枚举转移点 $j$，判断转移是否合法后累加即可。

$\quad$观察到合法的转移点是一段连续的区间，若令 $len_l$ 和 $len_r$ 分别表示两限制字符串的长度，显然对于满足 $len_l<i-j<len_r$ 的转移点 $j$，这个转移都是合法的，现在的问题在于判断当 $j=i-len_l$ 或 $j=i-len_r$ 的时候转移是否合法。

$\quad$考虑用 $\rm ExKMP$ 对任意一个 $i$， 求 $\rm LCP(s_{i\sim n},l)$ 和 $\rm LCP(s_{i\sim n},r)$，这样就可以快速求出 $s_{i-len_l+1\sim i}$ 与 $l$ 的最长公共前缀 $zl_{i-len_l+1}$，并通过比较 $s_{i-len_l+1+z_{i-len_l+1}}$ 与 $l_{z_{i-len_l+1}+1}$ 的大小判断当 $j=i-len_l$ 时转移是否合法，同理，当 $j=i-len_r$ 时转移是否合法也可以通过相同方式判断。

$\quad$这样，合法转移点的区间就在 $\Theta(1)$ 的时间内求出来了，剩下的用前缀和记录一下即可。需要注意的是，由于不能出现前导零，所以当转移点的后一位为 '$0$' 时不能将其加入前缀和数组。

$\quad$总时间复杂度 $\Theta(n)$.

---

