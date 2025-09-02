# Division + LCP (hard version)

## 题目描述

这是该问题的困难版本。在本版本中 $l \le r$。

给定一个字符串 $s$。对于一个固定的 $k$，将 $s$ 划分为恰好 $k$ 个连续子串 $w_1,\dots,w_k$。定义 $f_k$ 为所有划分方式中 $LCP(w_1,\dots,w_k)$ 的最大值。

$LCP(w_1,\dots,w_m)$ 表示字符串 $w_1,\dots,w_m$ 的最长公共前缀的长度。

例如，如果 $s=abababcab$ 且 $k=4$，一种可能的划分为 $\color{red}{ab}\color{blue}{ab}\color{orange}{abc}\color{green}{ab}$。此时 $LCP(\color{red}{ab},\color{blue}{ab},\color{orange}{abc},\color{green}{ab})=2$，因为 $ab$ 是这四个字符串的最长公共前缀。注意，每个子串由连续的字符组成，且每个字符恰好属于一个子串。

你的任务是求出 $f_l, f_{l+1}, \dots, f_r$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
3 1 3
aba
3 2 3
aaa
7 1 5
abacaba
9 1 6
abababcab
10 1 10
aaaaaaawac
9 1 9
abafababa
7 2 7
vvzvvvv```

### 输出

```
3 1 0 
1 1 
7 3 1 1 0 
9 2 2 2 0 0 
10 3 2 1 1 1 1 1 0 0 
9 3 2 1 1 0 0 0 0 
2 2 1 1 1 0```

# 题解

## 作者：DrAlfred (赞：14)

摘要：二分，字符串哈希，记忆化

[Easy version：https://www.luogu.com.cn/problem/CF1968G1](https://www.luogu.com.cn/problem/CF1968G1)

[Hard version：https://www.luogu.com.cn/problem/CF1968G2](https://www.luogu.com.cn/problem/CF1968G2)

本题解 G1，G2 虽然写在了一起，但是有 G1 向 G2 转化的过程，求管理大大通过 QAQ。

## 题意

给定一个字符串 $s$，对于一个正整数 $k$，我们考虑将 $s$ 分成 $k$ 个连续的子串 $w_1, \cdots, w_k$。定义 $f_k$ 是在所有分割方案中最大的 $LCP\left(w_1, \cdots, w_k\right)$，即 $w_1, \cdots, w_k$ 的最长公共前缀的长度。

现在，给定一个范围 $[l, r]$，求 $f_l, f_{l + 1}, \cdots, f_r$。

## 分析思路

本题解中 $s$ 的下标从 $1$ 开始。

### I. Easy version

首先我们来考察 `Easy version`，即 $k = l = r$ 的情况。

我们考虑枚举最长公共前缀的长度 $len$。注意到 $len$ 变大时，在 $s$ 中的出现次数是不增的。也就是说，为了使每一段都有长为 $len$ 的前缀，相应分割的段数就会减少。于是我们考虑在 $[0, \frac{n}{k}]$ 上二分 $len$。

那么，如何检验 $len$ 是否合法呢？我们需要贪心地从第一个位置开始匹配与 $s[1:len]$ 相等的不交的子串个数。考虑用字符串哈希进行快速判断两段子串是否相等。最后只要个数大于等于 $k$ 即可。

于是我们用 $O\left(n \log n\right)$ 的算法解决了 `Easy version`。代码见 [Easy version 题解](https://www.luogu.com.cn/article/52ytd5wy)。

### II. Hard version

接下来解决 $l \leq r $ 的情形。这里我们讨论 $l = 1, r = n$ 如何解决。

我们考虑对 $k$ 的大小进行分类讨论，分为 $k < \sqrt n$ 的情况与 $k \geq \sqrt n$ 的情况。（这一步是为了最终时间复杂度的正确）

#### 1. $k < \sqrt n$

此时我们沿用 `Easy version` 的做法，暴力枚举 $k$，并且进行二分即可，时间复杂度 $O\left(n \sqrt n \log n\right)$。

#### 2. $ k \geq \sqrt n$

由于 $k \geq \sqrt n, f_k \cdot k \leq n$，我们有 $f_k \leq \sqrt n$。考虑枚举最终 $LCP$ 的长度 $L$。对于每个 $L$，我们能沿用二分的 $check$，在 $O\left(n\right)$ 的时间复杂度内求得其对应的最大的 $k$。这一部分的总时间复杂度 $O\left(n \sqrt n\right)$。

因为在第二部分中，我们找到的是 $L$ 对应的最大的 $k$，所以我们还需要从后往前扫一遍更新答案为更大值。

综上，总时间复杂度为 $O\left(n \sqrt n \log n\right)$，可以通过 `Hard version`。

需要注意的是，字符串哈希有许多取模和减法操作，常数较大。考虑对 `check` 进行记忆化以及减小枚举的范围可以有效减小常数。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
class HashedString {
private:
    // change M and B if you want
    static const i64 M = (1LL << 61) - 1;
    static const i64 B;
    // pow[i] contains B^i % M
    static vector<i64> pow;

    // p_hash[i] is the hash of the first i characters of the given string
    vector<i64> r_hash, p_hash;
    i128 mul(i64 a, i64 b) { return (i128)a * b; }
    i64 mod_mul(i64 a, i64 b) { return mul(a, b) % M; }

public:
    HashedString(const string &s) : r_hash(s.size() + 1), p_hash(s.size() + 1) {
        while (pow.size() < s.size()) { pow.push_back(mod_mul(pow.back(), B)); }
        p_hash[0] = 0;
        r_hash[0] = 0;
        for (size_t i = 0; i < s.size(); i++) {
            p_hash[i + 1] = (mul(p_hash[i], B) + s[i]) % M; // 1-based
        }
        i64 sz = s.size();
        for (int i = sz - 1, j = 0; i >= 0; i--, j++) {
            r_hash[j + 1] = (mul(r_hash[j], B) + s[i]) % M;
        }
    }
    i64 getHash(int start, int end) { // 0 based
        i64 raw_val = p_hash[end + 1] - mod_mul(p_hash[start], pow[end - start + 1]);
        return (raw_val + M) % M;
    }
    i64 getRHash(int start, int end) { // 0 based
        i64 raw_val = r_hash[end + 1] - mod_mul(r_hash[start], pow[end - start + 1]);
        return (raw_val + M) % M;
    }
};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
vector<i64> HashedString::pow = {1};
const i64 HashedString::B = uniform_int_distribution<i64>(0, M - 1)(rng);
int t, n, l, r;
inline void solve(void) {
    std::string S;
    cin >> n >> l >> r >> S;
    HashedString H(S);
    vector<int> ans(n + 1);
    vector<int> mem(n + 1, -1);
    const int SQ = ceil(sqrt(n));
    auto check = [&](int len) -> int {
        int cnt = 1;
        if (len == 0) return 1e9;
        if (mem[len] != -1) return mem[len];
        auto F = H.getHash(0, len - 1);
        for (int i = len; i + len - 1 < n; i++) {
            if (F == H.getHash(i, i + len - 1)) {
                ++cnt, i = i + len - 1;
            }
        }
        return mem[len] = cnt;
    };
    int lst = n;
    for (int k = l; k <= SQ; k++) {
        int L = 0, R = min(lst, n / k), mid;
        while (L < R) {
            mid = (L + R + 1) >> 1;
            check(mid) >= k ? L = mid : R = mid - 1;
        }
        ans[k] = L, lst = R;
    }
    for (int len = 1; len <= SQ; len++) {
        int k = check(len);
        if (k < l) break;
        ans[k] = max(ans[k], len);
    }
    for (int i = n - 1; i >= l; i--) {
        ans[i] = max(ans[i], ans[i + 1]);
    }
    for (int i = l; i <= r; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：wcyQwQ (赞：8)

题解咋都是后缀数组，给个好写的 Z 函数做法。

我们考虑枚举答案 $k$，不难发现当 $k$ 合法时段数是一段后缀，于是我们求出 $\text{LCP} = k$ 时最多能划分为几段即可，我们求出原字符串的 Z 函数 $z$，在上面进行匹配，当 $z_i \ge k$ 时往后跳 $k$ 步，否则跳 $1$ 步，这样贪心的匹配显然是正确的，可以做到 $O(n^2)$。

不难发现我们跳 $k$ 步的总次数是调和级数级别的，于是只要优化掉跳 $1$ 步往下找的过程，也就是快速找到下一个 $z_i \ge k$ 的点，从小到大枚举 $k$，用并查集维护即可，时间复杂度 $O(n\log^2 n)$。

[Code](https://codeforces.com/contest/1968/submission/261795486)

---

## 作者：苏联小渣 (赞：4)

容易发现，随着划分段数增加，LCP 长度单调不增。

对于 Easy Version，容易发现 LCP 一定在第一段中出现过，不妨二分其长度，然后算出这个字符串中这个前缀最多出现多少次，且出现的字串两两不交。

显然有，设二分长度为 $x$，从头开始扫，假设当前扫到 $i$，若 $S[i,i+x-1]$ 与 $S[1,x]$ 相同，则跳到 $i+x$ 继续匹配，否则到 $i+1$，然后看最后匹配个数与 $l$ 的关系。判断相同可以用二分哈希或者扩展 KMP 完成，时间复杂度 $O(n \log n)$。

对于 Hard Version，考虑每次跳的本质：对于一个位置 $i$，定义 $f_i$ 为 $S[i,n]$ 与 $S[1,i-1]$ 的 LCP 长度，那么假设现在要求 LCP 长度为 $x$，相当于只保留 $f_i \ge x$ 的 $i$ 位置，然后从 $x+1$ 开始，每次找到右边第一个保留的位置，设作 $p$，然后跳到 $p+x$ 再继续找，如此往复，然后求出最后匹配次数。记一个 LCP 长度 $x$ 对应最多的匹配次数（也就是划分段数）为 $g_x$。

如果我们对于所有长度 $x$ 都能求出 $g_x$，那么对于划分段数为 $i$ 的答案，就是满足 $g_x \ge i$ 的 $x$ 的最大值。这个是容易做的。

观察发现对于长度为 $x$ 的 LCP，每次会往后跳 $x$ 个数，那么跳的总次数就是调和级数级别的，相当于 $O(n \log n)$。而每次寻找下一个保留的位置，相当于查找后继，可以用 set 实现，于是总时间复杂度 $O(n \log^2 n)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, l, r, base=31, to[26], f[200010], pw[200010], hsh[200010], mx[200010];
char s[200010];
const int mo = 1e9 + 7;
int query(int l, int r){
	return (hsh[r] - 1LL * hsh[l-1] * pw[r-l+1] % mo + mo) % mo;
}
vector <int> pos[200010];
set <int> ss;
set <int> :: iterator it;
int main(){
	mt19937 rand(time(0));
	for (int i=0; i<26; i++){
		to[i] = rand() % mo;
	}
	scanf ("%d", &t);
	while (t --){
		scanf ("%d%d%d%s", &n, &l, &r, s+1);
		ss.clear();
		pw[0] = 1;
		for (int i=0; i<=n; i++) pos[i].clear();
		for (int i=1; i<=n; i++){
			pw[i] = 1LL * pw[i-1] * base % mo;
			mx[i] = 0;
		}
		for (int i=1; i<=n; i++){
			hsh[i] = (1LL * hsh[i-1] * base % mo + to[s[i]-'a']) % mo;
		}
		for (int i=2; i<=n; i++){
			int len = min(i-1, n-i+1);
			int L = 1, R = len;
			f[i] = 0;
			while (L <= R){
				int mid = L + R >> 1;
				if (query(1, mid) == query(i, i+mid-1)) f[i] = mid, L = mid + 1;
				else R = mid - 1;
			}
			pos[f[i]].push_back(i);
			if (f[i] >= 1) ss.insert(i);
		}
		for (int i=1; i<=n; i++){
			int now = i+1, tmp = 1;
			while (now <= n){
				it = ss.lower_bound(now);
				if (it == ss.end()) break;
				now = *it, now = now + i, tmp ++;
			}
			for (int j=0; j<pos[i].size(); j++){
				int npos = pos[i][j];
				it = ss.find(npos); ss.erase(it);
			}
			mx[tmp] = i;
		}
		for (int i=n-1; i>=1; i--){
			mx[i] = max(mx[i+1], mx[i]);
		}
		for (int i=l; i<=r; i++){
			printf ("%d ", mx[i]);
		}
		puts ("");
	}
	return 0;
}
```

---

## 作者：woshishabi11451444 (赞：3)

因为是分连续的段，所以第一段是一段前缀，那么 $\operatorname{LCP}$ 一定也是一段前缀。

首先对问题分类考虑，假设现在要求 $f_i$：

1. $i \le \sqrt n$，由于 $\operatorname{LCP}$ 有单调性，所以二分求解，这一部分的时间复杂度：$O(n \times \sqrt n \times \log_{2} n)$。

2. $i > \sqrt n$，首先可以知道 $f_i$ 最大是 $\lfloor \frac{n}{i} \rfloor$，那么对于 $\max \limits_{i = \sqrt n + 1}^{n} f_i \le \sqrt n$，所以可以枚举可能作为 $\operatorname{LCP}$ 的前缀（长度不会超过 $O(\sqrt N)$），在枚举了可能的 $\operatorname{LCP}$ 就能计算出对哪些 $f_i$ 造成改变，能带来变化的区间一定是一段前缀，然后可以记 $d_i$ 表示 $1 \sim i$ 这段区间的 $f_i$ 至少为 $d_i$，那么每一次只需对修改的区间的右端点 $d_i$ 发生变化，最后只需对于 $d_i$ 求后缀和，这一部分的时间复杂度：$O(n \times \sqrt n \times \log_{2} n)$。

总共时间复杂度：$O(n \times \sqrt n \times \log_{2} n)$，可以通过卡常使得时间复杂度更优。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int bna = 1145141, mod = 1e9 + 7;

string s;
pair<int, int> num[N];
int T, n, k, l, r, f, dp[N], bnxt[N], maxx[N];

int Check(int x){
  if(num[x].first == f){
    return num[x].second;
  }
  int cnt = 0, pre = -1;
  for(int i = 1, j = 0; i <= n; i++){
    for(; j && s[i] != s[j + 1]; j = bnxt[j]);
    j += s[i] == s[j + 1];
    if(j == x){
      j = bnxt[j];
      if(pre == -1 || i - pre >= x){
        cnt++, pre = i;
      }
    }
  }
  num[x] = {f, cnt};
  return cnt;
}

int solve(int x){
  int l = 0, r = n / x;
  while(l < r){
    int mid = (l + r + 1) >> 1;
    Check(mid) >= x ? l = mid : r = mid - 1;
  }
  return l;
}

void Solve(){
  cin >> n >> l >> r >> s;
  s = ' ' + s;
  for(int i = 2, j = 0; i <= n; i++){
    for(; j && s[j + 1] != s[i]; j = bnxt[j]);
    j += s[j + 1] == s[i];
    bnxt[i] = j;
  }
  k = int(sqrt(n));
  fill(maxx + 1, maxx + n + 2, 0);
  fill(dp + 1, dp + n + 1, 0);
  for(int i = 1; i <= k; i++){
    dp[i] = solve(i);
  }
  for(int i = 1; i <= k; i++){
    int num = Check(i);
    maxx[num] = max(maxx[num], i);
  }
  for(int i = n; i >= 1; i--){
    maxx[i] = max(maxx[i + 1], maxx[i]);
    dp[i] = max(dp[i], maxx[i]);
  }
  for(int i = l; i <= r; i++){
    cout << dp[i] << ' ';
  }
  cout << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  for(f = 1; f <= T; f++){
    Solve();
  }
  return 0;
}
```

---

## 作者：hhhqx (赞：2)

# CF1968G2 Division + LCP (hard version) 题解
## 前言
这题可以 $O(n \sqrt{n} \log n)$ 再各种优化做，算法是二分、哈希（不知道包不包含根号分治，但是有用到根号分治的思想）。

如果读题解有些抽象的话可以看代码辅助理解。
## 题意转化
由于是从第一个位置开始分段，所以问题就是在字符串中，选出 $k(l \le k \le r)$ 个不相交的且完全相同的子段，不过必须选择从头开始的一个子段，求最长长度。
## 思路
### Easy Version
如果只用求对一个 $k$ 求答案。

可以二分答案，然后在内部可以 $O(n)$ 地 check 答案。

check 如何 $O(n)$ 做呢？第一个位置开头的子段必须选择，贪心地，第一个位置选择的子段开始，从当前子段的结尾向后找到**最近完全相等的子段**，判断子段相等可以使用哈希。

时间复杂度 $O(n \log n)$。
### Hard Version
想了很多种做法发现都不好做，猜一猜时间复杂度，假设时间复杂度带根号，没想到完全可做。

Hard Version 就是有多个 $k$ 需要同时求解，我么不如直接求所有 $1 \le k \le n$ 的答案。

- 对于 $1 \le k \le \sqrt{n}$ 的 $k$，用 Easy Version 的做法求解，时间复杂度 $O(n \sqrt{n} \log n)$。
- 对于 $\sqrt{n} < k \le n$ 的 $k$，则分段后最长的段最长 $\sqrt{n}$，所以其答案必定小于等于 $\sqrt{n}$。
	- 枚举每个长度 $l(1 \le l \le \sqrt{n})$，使用 Easy Version 中 check 的做法来求最多可以分几段，然后前缀和一下。
	- 时间复杂度 $O(n \sqrt{n})$。
    
两种做法合并起来即可。
### 优化1
发现两种情况处理的时间复杂度不同，一个 $O(n \log n)$，另一个 $O(n)$。则我们可以平衡一下。

显然第一种做法给 $1 \le k \le B$ 的直接求解，第二种做法就是长度小于等于 $\frac{n}{B}$。

这个 $B$ 显然可以设为 $200$。
### 优化2
对于第一种做法，发现 $k$ 从 $1$ 到 $B$ 对应的答案是不增的，所以二分答案时的上界可以由 $ans_{k-1}$ 决定。
### 优化3
对于第一种做法，发现答案有很长一段连续，所以在二分前先 check $ans_{k-1}$，若可以则 $ans_k = ans_{k-1}$，否则再二分答案。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using Pair = pair<LL, LL>;

const int MAXN = 2e5 + 3;
const LL mod = 998244353;
const Pair B = {37, 47}; // 使用双哈希

int n, L, R, ans[MAXN];
char s[MAXN];
Pair Hash[MAXN], Bpow[MAXN];

Pair H(int l, int r){ // 求区间哈希值
  return {(Hash[r].first - Hash[l-1].first * Bpow[r-l+1].first % mod + mod) % mod,
           (Hash[r].second- Hash[l-1].second* Bpow[r-l+1].second% mod + mod) % mod};
}

bool check(int D, int k){ // 二分中的 check 函数
  int cnt = 0;
  for(int i = 1; i + D - 1 <= n; ){
    while(i + D - 1 <= n && H(i, i + D - 1) != H(1, D)) i++;
    cnt += i + D - 1 <= n && H(i, i + D - 1) == H(1, D), i = i + D;
    if(cnt >= k) return 1;
  }
  return 0;
}

void work(){
  cin >> n >> L >> R;
  for(int i = 1; i <= n; i++){
    cin >> s[i];
  }
  Bpow[0] = {1, 1};
  for(int i = 1; i <= n; i++){ // 预处理前缀哈希
    Bpow[i] = {Bpow[i-1].first * B.first % mod, Bpow[i-1].second* B.second% mod};
    Hash[i] = {(Hash[i-1].first * B.first % mod + s[i] - 'a' + 1) % mod,
               (Hash[i-1].second* B.second% mod + s[i] - 'a' + 1) % mod};
  }
  for(int i = 1; i <= n; i++) ans[i] = 0;
  for(int D = min(n, 1000); D >= 1; D--){ // 求解 200 < k <= n 的答案
    int mx = 0;
    for(int i = 1; i + D - 1 <= n; ){ // 类似 check 函数
      while(i + D - 1 <= n && H(i, i + D - 1) != H(1, D)) i++;
      mx += i + D - 1 <= n && H(i, i + D - 1) == H(1, D), i = i + D;
    }
    ans[mx] = max(ans[mx], D); // 前缀和
  }
  for(int i = n - 1; i >= 1; i--) ans[i] = max(ans[i], ans[i + 1]);
  ans[0] = n;
  for(int k = 1; k <= min(n, 200); k++){ // 求解 1 <= k <= 200 的答案
    int l = 0, r = ans[k - 1];
    if(check(r, k)) l = r;
    while(l < r){
      int mid = (l + r + 1) >> 1;
      if(check(mid, k)){
        l = mid;
      }else r = mid - 1;
    }
    ans[k] = max(ans[k], l);
  }
  for(int i = L; i <= R; i++) cout << ans[i] << " ";
  cout << "\n";
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  cin >> T;
  while(T--) work();
  return 0;
}
```

---

## 作者：liuhao24 (赞：2)

### 题意

$f(i)$ 表示将字符串 `s` 分为 `i` 段，每一段的最长公共前缀的最长长度。

求 $f(l),f(l+1)...f(r)$。

### 解题思路

假如 $s$ 某个前缀 $t$ 在 $s$ 中最多可以找到 $x$ 个不相交和 $t$ 相同的子串，比如`ababababab`，对于前缀`abab`，最多可以找到 `2` 个不相交的和 `abab`相同的子串。

所以分成小于等于 $x$ 段的结果都可以使用 $t$ 的长度去更新，所以我们只需要枚举字符串的所有前缀。

考虑对原串构建后缀自动机，在后缀树上用启发式合并维护 `endpos` 集合，每 `dfs` 到表示前缀的节点，我们按照上方思路贪心的找到最多的不相交的子串（位置靠前优先选）每个 `endpos` 集合最大为 `n`，每次最多跳 $\left \lfloor \frac{n}{len(prefix)} \right \rfloor  $ 次，总共最多 $\sum_{i=1}^{n}\left \lfloor \frac{n}{i} \right \rfloor  $ 次，每次跳使用`lower_bound`，时间复杂度 $log(n)$，复杂度约等于 $O(n\times ln(n)\times log(n))$，启发式合并复杂度 $O(n\times log^{2}(n))$。

总时间复杂度 $O(n\times log^2(n))$。

### AC_Code

```cpp
//
// Created by liuhao.
//
#include<bits/stdc++.h>
using namespace std;
#define ios ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define endl '\n'

template<class T>
struct Suffix_Automaton {
	int tot = 1, last = 1;
	struct Node {
		signed len, fa, fipos;
		int ch[26];
	};
	vector<Node> node;
	int n;
	Suffix_Automaton(T &s) : n(s.size() - 1), node(2 * s.size()) {
		for (int i = 1; i < s.size(); i++)extend(s[i]-'a');
	}
	void extend(int c) {
		int p = last, np = last = ++tot;
		node[np].len = node[p].len + 1;
		node[np].fipos = node[np].len;
		for (; p && !node[p].ch[c]; p = node[p].fa)node[p].ch[c] = np;
		if (!p)node[np].fa = 1;
		else {
			int q = node[p].ch[c];
			if (node[q].len == node[p].len + 1)node[np].fa = q;
			else {
				int cp = ++tot;
				node[cp] = node[q], node[cp].len = node[p].len + 1;
				node[cp].fipos=0;
				node[q].fa = node[np].fa = cp;
				for (; p && node[p].ch[c] == q; p = node[p].fa)node[p].ch[c] = cp;
			}
		}
	}
	int size() { return tot; }
	Node operator[](int i) {
		return node[i];
	}
};

auto main() -> signed {
	ios;
	int T;
	cin>>T;
	while(T--){
	    int n,l,r;
		cin>>n>>l>>r;
		string s;
		cin>>s;
		s=' '+s;
		Suffix_Automaton<string>suf(s);
		vector<vector<int>>g(suf.size()+1);
		for(int i=2;i<=suf.size();i++){
			g[suf[i].fa].push_back(i);
		}
		vector<int>d(n+1);
		vector<set<int>>S(suf.size()+1);
		auto dfs=[&](auto dfs,int x)->void{
			for(auto i:g[x]){
				dfs(dfs,i);
				if(S[i].size()>S[x].size())S[i].swap(S[x]);
				for(auto j:S[i]){
					S[x].insert(j);
				}
			}
			if(suf[x].fipos!=0){
				S[x].insert(suf[x].fipos);
				int last=0;
				int res=0;
				for(auto i=S[x].begin();i!=S[x].end();){
					auto t=S[x].lower_bound(last+suf[x].len);
					if(t==S[x].end())break;
					last=*t;
					res++;
				}
				d[res]=max(suf[x].len,d[res]);
			}
		};
		dfs(dfs,1);
		for(int i=n-1;i>=1;i--){
			d[i]=max(d[i+1],d[i]);
		}
		for(int i=l;i<=r;i++){
			cout<<d[i]<<' ';
		}
		cout<<endl;
	}
    return 0;
}

```

---

## 作者：Starrykiller (赞：2)

[这](https://www.luogu.com.cn/article/0ff5crfw)是 G1 的题解。

考虑怎么将这个问题推广到 G2。如果对于 $i\in [l,r]$ 每个都做一次二分，显然太浪费了。

类比整体二分的思路，我们记 $solve(l,r,q_l,q_r)$ 为 $[q_l, q_r]$ 的询问的答案在 $[l,r]$ 内。

我们记 $mid=\left\lfloor\dfrac{l+r}{2}\right\rfloor$，然后将 $[q_l,q_r]$ 分成两部分，递归 $solve(l,mid,ql,qmid)$ 和 $solve(mid+1,r,qmid+1,qr)$ 即可。

根据 LA 群的分析，时间复杂度 $\Theta(n\sqrt n)$。

[Submission for G2](https://codeforces.com/contest/1968/submission/259225397).

---

## 作者：Reunite (赞：1)

简单题。

考虑固定答案 $len$，每次必须不重叠地往后跳，显然可以贪，即只要对于一个 $pos$，找最近的 $pos'$ 满足 $\text{lcp}\ge len$ 即可跳。

先对于所有后缀求出与原串的 $\text{lcp}$，这个爱咋写咋写，二分哈希或者 SA 都行，然后找最近的显然可以 ST 表然后二分找。注意到每次跳至少让 $pos$ 增加 $len$，那总共移动次数不超过调和级数，所以可以很简单地做到 $n\log^2 n$。

---

```cpp

#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mod 1000000007
using namespace std;

int T,n,L,R;
ll val[30];
ll hs[200005];
ll bin[200005];
char c[200005];
int lg[200005];
int lcp[200005];
int ans[200005];
int mx[20][200005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline ll get(int l,int r){return (hs[r]-hs[l-1]*bin[r-l+1]%mod+mod)%mod;}

inline int ask(int l,int r){
	int len=lg[r-l+1];
	return max(mx[len][l],mx[len][r-(1<<len)+1]);
}

inline int nxt(int p,int len){
	int l=p,r=n,mid,pos=n+1;
	while(l<=r){
		mid=(l+r)>>1;
		if(ask(p,mid)>=len) pos=mid,r=mid-1;
		else l=mid+1;
	}
	return pos;
}

int main(){
	in(T);
	while(T--){
		in(n),in(L),in(R);
		scanf("%s",c+1);
		bin[0]=1;
		for(int i=1;i<=n;i++) bin[i]=bin[i-1]*131%mod;
		for(int i=1;i<=n;i++) hs[i]=(hs[i-1]*131+c[i])%mod;
		for(int i=1;i<=n;i++){
			int l=0,r=n-i,mid;
			lcp[i]=0;
			while(l<=r){
				mid=(l+r)>>1;
				if(get(i,i+mid)==hs[1+mid]) lcp[i]=mid+1,l=mid+1;
				else r=mid-1;
			}
		}
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++) mx[0][i]=lcp[i],ans[i]=0;
		for(int j=1;j<=lg[n];j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<(j-1))]);
		for(int len=1;len<=n;len++){
			int pos=1+len,cnt=0;
			while(pos<=n+1) cnt++,pos=nxt(pos,len)+len;
			ans[cnt]=len;
		}
		for(int i=n-1;i>=1;i--) ans[i]=max(ans[i],ans[i+1]);
		for(int i=L;i<=R;i++) printf("%d ",ans[i]);
		puts("");
	}

	return 0;
}

```

---

## 作者：HHH6666666666 (赞：1)

sa 做法，思路和上一篇题解一样：LCP 必为原串前缀，因此枚举每个前缀，用 set 存下其所有出现位置在上面暴力跳，求出该前缀最多能将整个串分成几个子串。根据调和级数总复杂度为 $O(n\log^2n)$。

建出 sa，对于每个 LCP，其所有出现位置构成 sa 上一段包含 1（也就是开头）的连续段，思考如何找出这个连续段。从大到小枚举长度，这个线段不断变长，只需维护向左向右两个指针表示线段端点即可。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define ep emplace

using namespace std;

const int MAXN = 2e5 + 10;

int n, l, r;
char s[MAXN];
int sa[MAXN], rk[MAXN], temp[MAXN], cnt[MAXN];
int h[MAXN];
int ans[MAXN];

void build_sa() {
    int m = 128;
    for (int i = 0; i <= max(n, m); ++i) {
        sa[i] = rk[i] = temp[i] = cnt[i] = h[i] = 0;
    }
    for (int i = 1; i <= m; ++i) cnt[i] = 0;
    for (int i = 1; i <= n; ++i) ++cnt[s[i]];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 1; i <= n; ++i) sa[cnt[s[i]]--] = i;
    m = 0;
    for (int i = 1; i <= n; ++i) {
        if (i == 1 || s[sa[i]] != s[sa[i - 1]]) ++m;
        rk[sa[i]] = m;
    }
    for (int l = 1; l < n; l <<= 1) {
        for (int i = 1; i <= m; ++i) cnt[i] = 0;
        for (int i = 1; i <= n; ++i) ++cnt[rk[i]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i; --i)
            if (sa[i] > l) temp[cnt[rk[sa[i] - l]]--] = sa[i] - l;
        for (int i = n - l + 1; i <= n; ++i) temp[cnt[rk[i]]--] = i;
        for (int i = 1; i <= n; ++i) sa[i] = temp[i];
        m = 0;
        for (int i = 1; i <= n; ++i) {
            #define idf(x) mp(rk[x], (x + l <= n) ? rk[x + l] : -1)
            if (i == 1 || idf(sa[i - 1]) < idf(sa[i])) ++m;
            temp[sa[i]] = m;
        }
        for (int i = 1; i <= n; ++i) rk[i] = temp[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (rk[i] == 1) continue;
        int j = h[rk[i - 1]];
        j = max(0, j - 1);
        int pre = sa[rk[i] - 1];
        while (max(pre, i) + j <= n && s[pre + j] == s[i + j]) ++j;
        h[rk[i]] = j;
    }
    return;
}

void solve() {
    cin >> n >> l >> r;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    build_sa();
    int p1 = rk[1], p2 = rk[1];
    set<int> s; s.ep(1);
    for (int i = n; i; --i) {
        while (p1 > 1 && h[p1] >= i) --p1, s.ep(sa[p1]);
        while (p2 < n && h[p2 + 1] >= i) ++p2, s.ep(sa[p2]);
        int now = 1, cnt = 1;
        while (s.lower_bound(now + i) != s.end()) ++cnt, now = *s.lower_bound(now + i), assert(cnt <= n);
        ans[i] = cnt;
    }
    ans[0] = INT_MAX;
    int now = n;
    for (int i = l; i <= r; ++i) {
        while (ans[now] < i) --now, assert(now >= 0);
        cout << now << ' ';
    }
    cout << '\n';
    return;
}

int main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：Coffee_zzz (赞：0)

我们首先考虑 easy version 怎么做。

注意到问题可以转化为，找到最大的非负整数 $i$，使得 $s$ 中存在至少 $l$ 个不相交的等于 $s[1,i]$ 的子串。

显然，如果 $s$ 中存在至少 $l$ 个不相交的等于 $s[1,i+1]$ 的子串，那么 $s$ 中必然存在至少 $l$ 个不相交的等于 $s[1,i]$ 的子串。答案存在单调性，于是我们可以尝试通过二分找到最大的满足条件的非负整数 $i$。

判断是否存在至少 $l$ 个不相交的等于 $s[1,i]$ 的子串是简单的，只需要从左往右枚举每个长度为 $i$ 的子串，通过字符串 Hash 判断是否和 $s[1,i]$ 相等即可。  
注意这些子串不能相交，所以如果 $s[k,k+i-1]$ 匹配成功了，下一次需要从 $k+i$ 开始枚举。

直接二分 $i$ 即可。时间复杂度 $\mathcal O(n \log n)$。

接下来考虑 hard version 怎么做。

我们考虑直接枚举每个长度 $i$，求出 $s$ 所包含的不相交的等于 $s[1,i]$ 的子串的数量 $c_i$。

那么显然，对于所有满足 $c_{i+1} \lt k \le c_i$ 的正整数 $k$，$f_k$ 的值即为 $i$。其中我们可以认为 $c_{n+1}=0$，$c_0=n$。

于是我们现在只需要思考如何快速求出 $c$ 数组。

如果使用 easy version 的方法，暴力枚举每个长度为 $i$ 的子串，总复杂度是 $\mathcal O(n^2)$ 的，无法接受，考虑优化。

注意到，如果某个子串匹配成功了，下标会直接增加 $i$。如果每次都匹配成功，总复杂度是调和级数的，即 $\mathcal O(n \log n)$。

我们可以利用二分和 Hash 函数，求出对于每个位置 $k$，最大的满足 $s[1,p_k]=s[k,k+p_k-1]$ 的非负整数 $p_k$。

我们从大到小枚举长度 $i$，每次把所有满足 $p_k=i$ 的正整数 $k$ 进行标记后再求 $c_i$ 的值。  
在寻找可以被匹配的子串时，我们不需要一位一位枚举，只需要找到在不小于当前下标的正整数中，最小的被标记的正整数即可。其中，最小的被标记的正整数显然可以用线段树维护。

时间复杂度 $\mathcal O(n \log^2 n)$。

参考代码：<https://www.luogu.com/paste/xa04h54q>。

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

给定长度为 $n$ 的字符串 $s$ 以及 $l,r$。

对于所有 $k\in[l,r]$ 求出将 $s$ 分成 $k$ 段后每段的 LCP 最大值。

LCP 是最长公共前缀。

$1\leq n\leq 2\times 10^5,1\leq l\leq r\leq n$。多测。$1\leq \sum n \leq 2\times 10^5$。

# 题目思路

这一问需要求出很多 $l,r$。那么对于这类问题，往往是 $i$ 的答案可以推导出 $i+1$ 的答案，或者有一部分答案是一样的，需要你找出这个连续段。

~~考虑到我 duel 到的 CF786C 这题和这题做法完全一样就做完了。~~

但这题做法确实与 CF786C 一样。我慢慢说。

我们观察样例发现，最后总是有连续的相同段。大胆猜测这个就是关键。

考虑到对于 $k\geq B$ 的部分，一定存在 $|\operatorname{LCP}|\leq n/B$。

也就是说，如果我们取 $B=\sqrt n$，那么 对于 $k\geq \sqrt n$ 的部分只有 $\sqrt n$ 种答案。也就是会存在很多位置的 LCP 是一样的。

~~那么对于 $k\gt B$，我们先算一个答案，然后二分后面部分的位置找到最远的答案和自己一样的点。~~

喜报，上面划掉的做法复杂度和 $k\leq B$ 复杂度一样，常数过大我 ST 死掉了。

不这么做，考虑对于每个 LCP 长度，找到能分多少段，打个标记，之后做一个后缀 max。复杂度更优。

对于 $k\leq B$，直接做 G1 的单测即可。

# 代码链接

<https://codeforces.com/contest/1968/submission/259503068>

写得很丑。第一发 Hacked 是因为赛时卡常卡到一半莫名其妙过了。后来改了一发 Hash 的随机 Base。然后请群友把第一发叉了。~~锻炼 Hack 能力（雾）。~~

---

## 作者：_Ch1F4N_ (赞：0)

建出 SAM，然后枚举原串的一个前缀 $s$，我们假若能找出其所有出现位置，然后贪心的选取一个前缀段划分，得到 $k$ 段，那么就可以对 $f_1 \to f_k$ 做贡献。

考虑在 parent 树上 dsu 的方式求出所有出现位置，用一个 set 维护出所有出现位置，每次到一个前缀节点就用 lower_bound 找出所有划分段，由于至多有 $\frac{n}{len}$ 个所以总操作数是 $O(\sum_{i=1}^{n} \frac{n}{i})  =  O(n \log n)$，再算上 set 和 dsu 的复杂度，总复杂度就是 $O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+114;
struct SAM{
	int len,fa;
	int son[26];
}nd[maxn];
int tot,lst;
int chifan[maxn];
vector<int> E[maxn];
void ins(char c,int pos){
    int u=++tot,v=lst;
	nd[u].len=nd[lst].len+1;
    chifan[u]=pos;
  	lst=u;
	while(v!=0&&nd[v].son[c-'a']==0) nd[v].son[c-'a']=u,v=nd[v].fa;
	if(v==0){
        nd[u].fa=1;
        return ;
    }else{
        int q=nd[v].son[c-'a'];
        if(nd[v].len+1==nd[q].len){
            nd[u].fa=q;
            return ;
        }else{
            int nq=++tot;
            nd[nq]=nd[q];
            nd[nq].len=nd[v].len+1;
            nd[u].fa=nq;
            nd[q].fa=nq;
            while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
            return ;
        }
    }
}
int rt;
void insert(string s){
    lst=rt;
    for(int i=0;i<s.size();i++) ins(s[i],i+1);
}
set<int> S;
int sz[maxn],son[maxn],L[maxn],R[maxn],node[maxn],dfncnt;
void dfs(int u){
    L[u]=++dfncnt;
    node[dfncnt]=u;
    sz[u]=1;
    for(int v:E[u]) dfs(v),sz[u]+=sz[v],son[u]=(sz[v]>sz[son[u]]?v:son[u]);
    R[u]=dfncnt;
}
int dp[maxn];
void dsu(int u,bool keep){
    for(int v:E[u]){
        if(v!=son[u]) dsu(v,false);
    }
    if(son[u]!=0) dsu(son[u],true);
    for(int v:E[u]){
        if(v!=son[u]){
            for(int i=L[v];i<=R[v];i++)
                if(chifan[node[i]]!=0) S.insert(chifan[node[i]]);
        }
    }
    if(chifan[u]!=0){
        S.insert(chifan[u]);
        int cnt=0,now=1;
        while(S.lower_bound(now)!=S.end()){
            now=(*S.lower_bound(now))+chifan[u];
            cnt++;
        }
        dp[cnt]=max(dp[cnt],chifan[u]);
    }
    if(keep==false){
        for(int i=L[u];i<=R[u];i++)
            if(chifan[node[i]]!=0) S.erase(chifan[node[i]]);
    }
    return ;
}
void work(){
    dfncnt=0;
    S.clear();
    rt=++tot;
    int n,l,r;
    cin>>n>>l>>r;
    string s;
    cin>>s;
    insert(s);
    for(int i=2;i<=tot;i++) E[nd[i].fa].push_back(i);
    dfs(1);
    dsu(1,false);
    for(int i=n;i>=1;i--) dp[i]=max(dp[i],dp[i+1]);
    for(int i=l;i<=r;i++) cout<<dp[i]<<' ';
    cout<<'\n';
    for(int i=1;i<=tot;i++)
        for(int j=0;j<26;j++) nd[i].len=0,nd[i].fa=0,nd[i].son[j]=0,chifan[i]=0,sz[i]=0,son[i]=0,L[i]=0,R[i]=0,node[i]=0,dp[i]=0,E[i].clear();
    tot=lst=rt=0;
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
2
3 1 3
aba
3 2 3
aaa
*/
```

---

