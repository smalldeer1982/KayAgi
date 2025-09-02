# 「Wdcfr-1」CONsecutive and CONcat (hard version)

## 题目描述

Lily White is playing with strings. Being a yousei, she is not capable of complex speech. Thus, she likes strings that only contain one kind of letter, she calls such strings of length $x$ a "$x$-CON string". For example, `qqqq` is a "$4$-CON string", while `aaab` is not any type of "CON string".

Lily White composed an array $a$. It contains $n$ strings of length $m$ that she will use to herald spring. For each permutation of $1,2,\ldots, n$, let us denote current permutation as $p=\{p_1,p_2,\cdots,p_n\}$. Lily White concatenates all the string in array $a$ in the order of $a_{p_1},a_{p_2},\cdots,a_{p_n}$ into a string $s$ of length $nm$ . 

As she likes $k$-CON strings, she wants to know the sum of the number of "$k$-CON string" in all non-empty substrings of $s$ composed by all $n!$ permutations. Since the answer may be enormous, just print the answer taken modulo $998,244,353$ (a large prime).


## 说明/提示

### Explanation

#### Sample \#1

- For permutation $1,2,3$, the formed $s$ is `aaabaabaa`, none on the non-empty substring in this string are "$5$-CON string".
- For permutation $1,3,2$, the formed $s$ is `aaabaabaa`, none on the non-empty substring in this string are "$5$-CON string".
- For permutation $2,1,3$, the formed $s$ is `baaaaabaa`, this string has one substring `aaaaa` which is a "$5$-CON string".
- For permutation $2,3,1$, the formed $s$ is `baabaaaaa`, this string has one substring `aaaaa` which is a "$5$-CON string".
- For permutation $3,1,2$, the formed $s$ is `baaaaabaa`, this string has one substring `aaaaa` which is a "$5$-CON string".
- For permutation $3,2,1$, the formed $s$ is `baabaaaaa`, this string has one substring `aaaaa` which is a "$5$-CON string".

In summary, the answer is $0+0+1+1+1+1=4$.

#### Sample \#2

In all of the full permutation of length $3$, there will be six different $s$: `xyzqaqaba`, `xyzabaqaq`, `qaqxyzaba`, `qaqabaxyz`, `abaqaqxyz`, and `abaxyzqaq`. None of these has a non-empty substrings which is a "$2$-CON string". So the answer is $0$.

### Constraints

$2\le k \le n\cdot m\le 10^6;\ 1\le m \le 100$. $a_i$ contains only lowercase English letters.

## 样例 #1

### 输入

```
3 3 5
aaa
baa
baa
```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3 2
xyz
qaq
aba
```

### 输出

```
0```

## 样例 #3

### 输入

```
5 3 2
cca
cbb
acb
bbb
acb
```

### 输出

```
600```

## 样例 #4

### 输入

```
5 3 5
aba
bbb
bbb
aba
bcb
```

### 输出

```
120```

# 题解

## 作者：yzy1 (赞：1)

## D1

考虑将贡献分为两种——字符串内部的贡献和拼接处产生的贡献。第一种贡献直接暴力求即可，重点是第二种。考虑一个有长度为 $i$ 的连续极大后缀的字符串和一个长度为 $j$ 的极大连续前缀的字符串相拼接。会对答案造成 $i+j-k+1$ 的贡献。我们可以预处理出有极大前缀为字符 $c$，长度为 $i$ 的字符串数量 $\operatorname{pre}(c,i)$，极大后缀为字符 $c$，长度为 $j$ 的字符串数量 $\operatorname{suf}(c,j)$。枚举 $c,i,j$，从两个集合各选出一个字符串拼接在一起的方案数为 $\operatorname{suf}(c,j)\operatorname{pre}(c,i)$。考虑将「所有的全排列中 $k$ 连串数量的总和」转化为「随机洗牌后 $k$ 连串数量的期望」。从 $n$ 个位置中选择两个位置共有 $\operatorname{C}_n^2 = n(n-1)$ 种方案。而这 $n(n-1)$ 种方案中只有 $(n-1)$ 种使得两个字符串正好相邻。也就是说，随机洗牌后这两个字符串正好相邻形成 $k$ 连串的概率为 $\dfrac{n-1}{n(n-1)}=\dfrac 1 n$。所以对答案的贡献为：
$$
\dfrac{\operatorname{suf}(c,j)\operatorname{pre}(c,i)(i+j-k+1)} n.
$$
但是这会忽略一种特殊情况，试想有这样一组数据：

```
-1
2 3 2
aba
cde
```

正确答案显然为 $0$，但是根据上面那种方式得到的答案为 $1$，原因是因为字符串 `aba` 的前后缀有相同的字符，计算答案时会「自己和自己拼接」而造成贡献，我们可以记录多少个字符串有着极大前后缀字符均为 $c$ 的，前缀长度为 $i$，后缀长度为 $j$ 的字符串数量 $\operatorname{same}(c,i,j)$，计算答案时减去即可。故最终答案为：
$$
\sum_{c=\verb!a!}^{\verb!z!}\sum_{i=1}^{m-1}\sum_{j=1}^{m-1}\dfrac{(\operatorname{suf}(c,i)\operatorname{pre}(c,i)-\operatorname{same}(c,i,j))(i+j-k+1)} n.
$$

## D2

考虑将贡献分五种情况：

- 单个串内部；
- 纯由相同字母组成的串拼接；
- 一段后缀 + 几个相同字母组成的串；
- 几个相同字母组成的串 + 一段前缀；
- 一段后缀 + 几个相同字母组成的串 + 一段前缀。

分别考虑这些情况，计算答案即可。公式的推导与 easy version 类似，这里不再重复。

设 $G(i,j,k)$ 为后缀长度 $=i$，相同字母的串的个数 $=j$，前缀长度 $=k$ 对答案造成的贡献。需要注意的是，统计答案的时候可能会重复统计答案，比如当 $m=3,k=5$ 时。$G(2,1,1)=1$ 而不是 $2$，因为 $(2,1,1)$ 的情况包括  $(2,1,0)$ 的情况，会重复计算一遍贡献。具体来说，在计算 $G(x,y,z)$ 时，要减掉 $G(x,1\cdots y,0)$、$G(0,1\cdots y,z)$、$G(0,1\cdots y,0)$ 的贡献。贡献的计算可以通过一个简单 DP 求出，也可以分情况直接 $O(1)$ 判断。

```cpp
int Gx(int i, int ed, int st) {
  if (ed == 0 && st == 0) {
    int res = m + k - (i - 1) * m - 1;
    if (res > m) res = i * m - k + 1;
    if (res < 0) res = 0;
    return res;
  }
  if (ed == 0 || st == 0) {
    int j = ed | st;
    int res = j + k - 1 - (i - 1) * m - j;
    if (res > m) res = i * m + j - k + 1;
    if (res > j) res = j;
    if (res < 0) res = 0;
    return res;
  }
  int mn = min(st, ed), mx = max(st, ed);
  int res = mn + k - 1 - i * m - mn;
  if (res > mx) res = i * m + mn + mx - k + 1;
  if (res > mn) res = mn;
  if (res < 0) res = 0;
  return res;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> k;
  jc[0] = jcinv[0] = 1;
  re (i, n)
    jc[i] = 1ll * jc[i - 1] * i % mo, jcinv[i] = Inv(jc[i]);
  re (i, n) {
    string s;
    cin >> s;
    int f = s[0], b = s.back();
    int l = s.find_first_not_of(f), r = m - s.find_last_not_of(b) - 1;
    f -= 'a', b -= 'a';
    if (l < 0)
      l = n, ++all[f];
    else {
      ++pre[f][l], ++suf[b][r];
      if (f == b) ++same[f][l][r];
    }
    int len = 1;
    rep (i, l, m - r - 1) {
      if (s[i] == s[i - 1])
        ++len;
      else
        len = 1;
      if (len >= k) ++ans;
    }
  }
  rep (c, 0, 25) {
    pre[c][0] = suf[c][0] = 1;
    rep (mid, 0, all[c]) {
      rep (ed, 0, m - 1) {
        rep (st, 0, m - 1) {
          int qw = Gx(mid, ed, st);
          if (qw <= 0) continue;
          int glx = (1ll * suf[c][ed] * pre[c][st] - same[c][st][ed] + mo) % mo * A(all[c], mid) %
                    mo * (n - mid + 1 - bool(st) - bool(ed)) % mo,
              gly = A(n, mid + bool(st) + bool(ed));
          ans += 1ll * qw * glx % mo * Inv(gly) % mo, umod(ans);
        }
      }
    }
  }
  cout << 1ll * ans * jc[n] % mo << '\n';
}

```

---

## 作者：xtzqhy (赞：1)

提供一个简单做法。

我们把贡献分为两种：自己内部的贡献和拼接产生的贡献。

第一部分是好求的。

只需要找到一个串内的所有长度 $\ge k$ 的连续段，它们一定能贡献到所有排列里，所以贡献为 $(len-k+1)\times n!$。

然后考虑第二部分。

算重后再减去太麻烦了，能不能直接计算？

为了不重不漏，我们计算**以每个位置为起点，向后长度为 $k$ 的区间的贡献**。

那么这个区间一定是形如一个后缀散块+若干整块+一个前缀散块的形式。

设后缀长度为 $len$，该区间对应字符的整块个数为 $num$，区间内整块数量为 $num_1$，该区间对应字符的长度为 $len'$ 的前缀的块（且该块不能全为一种字符）的数量为 $cnt_{len'}$。

我们需要对前缀散块分类讨论：

1. 没有前缀散块。

此时方案数为 $A_{num}^{num_1}\times (n-num_1)!$。

2. 前缀散块所在的整块内的字符种类 $>1$

此时方案数为 $A_{num}^{num_1}\times cnt_{k-len-num_1\times m}\times (n-num_1-1)!$。

3. 前缀散块所在的整块内的字符种类 $= 1$

此时方案数为 $A_{num}^{num_1+1}\times (n-num_1-1)!$。

注意：在算当前块作为后缀散块时，一定要把当前块从桶里去掉，否则会算上自己对自己的贡献，这是错误的。

复杂度 $O(nm)$。
```cpp
#include"bits/stdc++.h"
#define re register
#define int long long
using namespace std;
const int maxn=1e6+10,maxm=110,maxv=30,mod=998244353;
int n,m,k,ans;
int fac[maxn],inv[maxn];
int buc[maxv],num[maxv][maxm];
string s[maxn];
inline int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
inline int Inv(int x){return qpow(x,mod-2);}
inline void init(){
	fac[0]=1;
	for(re int i=1;i<=n*m;++i) fac[i]=fac[i-1]*i%mod;
	inv[n*m]=Inv(fac[n*m]);
	for(re int i=n*m-1;i>=0;--i) inv[i]=inv[i+1]*(i+1)%mod;
}
inline int A(int n,int m){if(n<m) return 0;return fac[n]%mod*inv[n-m]%mod;}
inline void add(string s){
	int cnt=1;char c=s[0];
	for(re int i=1;i<m;++i) cnt+=(s[i]==c);
	if(cnt==m) ++buc[c-'a'];
	else{
		int pre=1;
		for(re int i=1;i<m;++i){
			if(s[i]!=c) break;
			else ++pre;
		}
		for(re int i=1;i<=pre;++i) ++num[c-'a'][i];
	} 
}
inline void del(string s){
	int cnt=1;char c=s[0];
	for(re int i=1;i<m;++i) cnt+=(s[i]==c);
	if(cnt==m) --buc[c-'a'];
	else{
		int pre=1;
		for(re int i=1;i<m;++i){
			if(s[i]!=c) break;
			else ++pre;
		}
		for(re int i=1;i<=pre;++i) --num[c-'a'][i];
	} 
}
inline void solve(string s){
    int len=0;char lst=0;
    for(re int i=0;i<m;++i){
        if(s[i]!=lst){
            if(len>=k) ans=(ans+(len-k+1)*fac[n]%mod)%mod;
            lst=s[i],len=1;
        }
        else ++len;
    }
    if(len>=k) ans=(ans+(len-k+1)*fac[n]%mod)%mod;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	init();
	for(re int i=1;i<=n;++i){
		cin>>s[i];
		add(s[i]);solve(s[i]);
	}
	for(re int i=1;i<=n;++i){
		del(s[i]);
		char c=s[i][m-1];
		for(re int j=m-1,len,num1,len1;j>=0;--j){
			if(s[i][j]!=c) break;
			if(m-j>=k) continue;
			len=k-(m-j);num1=len/m;len1=len-num1*m;
			if(!len1) ans=(ans+A(buc[c-'a'],num1)%mod*fac[n-num1]%mod)%mod;
			else ans=(ans+A(buc[c-'a'],num1)%mod*num[c-'a'][len1]%mod*fac[n-num1-1]%mod+A(buc[c-'a'],num1+1)%mod*fac[n-num1-1]%mod)%mod;
		}
		add(s[i]);
	}
	cout<<ans;
	return 0;
}
```

---

