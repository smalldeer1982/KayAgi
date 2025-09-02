# [ABC307Ex] Marquee

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc307/tasks/abc307_h

英大文字および英小文字からなる長さ $ L $ の文字列 $ S $ が幅 $ W $ の電光掲示板に表示されており、$ S $ が右から左へ $ 1 $ 文字分の幅ずつスクロールするように切り替わっています。

表示は、$ S $ の最後の文字が左端から消えると同時に $ S $ の最初の文字が右端から現れる、$ L+W-1 $ 周期での繰り返しとなっています。

例えば $ W=5 $、$ S= $ `ABC` のとき、電光掲示板の表示は

- `ABC..`
- `BC...`
- `C....`
- `....A`
- `...AB`
- `..ABC`
- `.ABC.`

の $ 7 $ つの状態を繰り返します。（`.` は文字が表示されていないことを表します）

より厳密には、各 $ k=0,\ldots,L+W-2 $ に対して、表示が次のようになっている相異なる状態が定まります。

- $ x $ を $ L+W-1 $ で割ったあまりを $ f(x) $ と表す。電光掲示板の左から $ (i+1) $ 番目の位置には、$ f(i+k)\ <\ L $ のとき $ S $ の $ f(i+k)+1 $ 番目の文字が表示され、そうでないとき何も表示されていない。

英大文字, 英小文字, `.`, `_` からなる長さ $ W $ の文字列 $ P $ が与えられます。  
電光掲示板の $ L+W-1 $ 種類の状態のうち、`_` の箇所を除いて $ P $ と一致するものの個数を求めてください。  
より厳密には、以下の条件を満たす状態の個数を求めてください。

- 全ての $ i=1,\ldots,W $ に対して次のいずれかが成立する
  - $ P $ の $ i $ 文字目は `_` である
  - 電光掲示板の左から $ i $ 番目に表示されている文字が $ P $ の $ i $ 文字目と等しい
  - 電光掲示板の左から $ i $ 番目には何も表示されておらず、かつ、$ P $ の $ i $ 文字目は `.` である

## 说明/提示

### 制約

- $ 1\ \leq\ L\ \leq\ W\ \leq\ 3\times\ 10^5 $
- $ L,W $ は整数である
- $ S $ は英大文字および英小文字のみからなる長さ $ L $ の文字列である
- $ P $ は英大文字, 英小文字, `.`, `_` のみからなる長さ $ W $ の文字列である

### Sample Explanation 1

電光掲示板の表示が `....A`, `...AB`, `..ABC` であるときの $ 3 $ 状態が該当します。

## 样例 #1

### 输入

```
3 5
ABC
..___```

### 输出

```
3```

## 样例 #2

### 输入

```
11 15
abracadabra
__.._________ab```

### 输出

```
2```

## 样例 #3

### 输入

```
20 30
abaababbbabaabababba
__a____b_____a________________```

### 输出

```
2```

## 样例 #4

### 输入

```
1 1
a
_```

### 输出

```
1```

# 题解

## 作者：Tony2 (赞：2)

这题是一个小 trick，即求模式串和带通配符文本串的匹配数量。

字符串匹配其实可以看作一个差卷积，两个不同的字符之间产生贡献，贡献位置是两个位置之差，使得一个匹配位置失效。

所以可以直接把字符转数字之后二进制拆位，每位都跑一次卷积。

可以选择跑两次，第一次模式串的 `0` 和文本串的 `1` 产生贡献，第二次反过来；也可以选择给通配符、`0`、`1` 分别赋 $0,1,-1$ 的权，分析两两贡献能一次卷积求出匹配失败的对数。第二种方法依赖一个串没有通配符的条件。不过这题时限很宽松，两种做法都能简单地通过。

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 3e5 + 5;
int n, m;
char c1[N], c2[N];
int a[N], b[N];
int f[N * 4], g[N * 4];
bool ban[N * 2];
int tr(char c){
	if (c == '_') return 0;
	else if ('a' <= c && c <= 'z') return c - 'a' + 1;
	else if ('A' <= c && c <= 'Z') return c - 'A' + 27;
	else return 53;
}
const int mod = 998244353, G = 3, Gi = 332748118;
int qpow(int x, int y){
	int res = 1;
	while (y){
		if (y & 1) res = 1ll * res * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return res;
}
int wk[N * 4], r[N * 4];
void ntt(int a[], int bits, int type){
	for (int i = 0; i < (1 << bits); i++){
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (bits - 1));
		if (i < r[i])
			swap(a[i], a[r[i]]);
	}
	for (int mid = 1; mid < (1 << bits); mid <<= 1){
		int w = qpow(type == 1 ? G : Gi, (mod - 1) / (mid * 2));
		wk[0] = 1;
		for (int i = 1; i < mid; i++)
			wk[i] = 1ll * wk[i - 1] * w % mod;
		for (int i = 0; i < (1 << bits); i += mid * 2)
			for (int j = 0; j < mid; j++){
				int x = a[i + j], y = 1ll * a[i + j + mid] * wk[j] % mod;
				a[i + j] = (x + y) % mod;
				a[i + j + mid] = (x - y) % mod;
			}
	}
	if (type == -1){
		int inv = qpow(1 << bits, mod - 2);
		for (int i = 0; i < (1 << bits); i++)
			a[i] = 1ll * a[i] * inv % mod;
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	cin >> n >> m >> (c1 + 1) >> (c2 + 1);
	for (int i = 1; i <= n; i++)
		a[i] = tr(c1[i]);
	int maxl = 1, minr = n + m - 1;
	for (int i = 1; i <= m; i++)
		b[i] = tr(c2[m - i + 1]);
	for (int i = 1; i <= m; i++)
		if (1 <= b[m - i + 1] && b[m - i + 1] <= 52){
			maxl = max(i, maxl);
			minr = min(i + n - 1, minr);
		}
	int bits = 32 - __builtin_clz(n + m);
	for (int t = 0; t < 6; t++){
		fill(f, f + (1 << bits), 0);
		fill(g, g + (1 << bits), 0);
		for (int i = 1; i <= n; i++)
			if (a[i] == 0) f[i] = 0;
			else f[i] = (a[i] >> t) & 1 ? 1 : -1;
		for (int i = 1; i <= m; i++)
			if (b[i] == 0) g[i] = 0;
			else g[i] = (b[i] >> t) & 1 ? 1 : -1;
		ntt(f, bits, 1);
		ntt(g, bits, 1);
		for (int i = 0; i < (1 << bits); i++)
			f[i] = 1ll * f[i] * g[i] % mod;
		ntt(f, bits, -1);
		int cnt = 0;
		for (int i = 2, l = 1, r = 0; i <= n + m; i++){
			while (r < i - 1 && r < m) cnt += b[++r] == 0;
			while (l < i - n) cnt -= b[l++] == 0;
			if ((f[i] % mod + mod) % mod + cnt + max({n + 1 - i, i - (m + 1), 0}) != n)
				ban[n + m - i + 1] = 1;
		}
	}
	int ans = 0;
	for (int i = maxl; i <= minr; i++)
		ans += !ban[i];
	cout << ans;
	return 0;
}
```

---

## 作者：SnowTrace (赞：1)

为啥没有人写 bitset 做法。

先考虑原问题，每个字母都得匹配上，下划线随便，点号考虑是划定了几段区间不能选。

本质上就是一个带通配符的字符串匹配问题，可以直接使用 bitset。

先处理出 $P$ 中需要匹配的串，处理方式是，找到 $P$ 最左边和最右边的字母，这两个位置中间所有字符拼接起来就是待匹配的串，记为 $T$，我们记录每个字母在文本串（题中的 $S$）中的出现位置，然后让 $T$ 去匹配，考虑要让 $T$ 每一个字母都匹配上，那么每一个字母的匹配位置其实就是这个字母在文本串中出现的位置的集合经过平移产生的一个集合，具体可以看代码。

考虑点号的贡献。处理出在 $T$ 左边和右边距离 $T$ 最近的点号，那么我们知道合法的匹配位置应该是一段前缀和一段后缀拼起来。 

注意考虑一下整个 $P$ 中没有出现字母的情况，还有如果 $T$ 中有点号则答案一定为 0。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;int len;
char s[300005],p[300005],t[300005];
bitset<300005>ss[53];bitset<300005>ans;
int S =0,T =-1;
int pos1 = -300000,pos2 = 600000;
int pre[300005];int tot;
signed main(){
	cin >> n >> m;
	for(int i= 1;i<=n;i++)cin >> s[i];
	for(int i = 1;i<=m;i++)cin >> t[i];
	for(int i = 1;i<=m;i++)if(t[i]!='_' and t[i]!='.'){
		S = i;break;
	}for(int i = m;i>=1;i--)if(t[i]!='_' and t[i]!='.'){
		T = i;break;
	}len = T-S+1;
	for(int i =S;i>=1;i--)if(t[i] == '.'){
		pos1 = i;break;
	}for(int i = T;i<=m;i++)if(t[i] == '.'){
		pos2 = i;break;
	}
	if(len == 0){
		int ans =0 ;
		for(int i = 1;i<=m;i++)pre[i] = pre[i-1]+(t[i] == '.');
		for(int i = 1;i<=m;i++){
			int tt = pre[i];if(i>=n)tt-=pre[i-n];
			if(!tt)ans++;
		}for(int i =1;i<n;i++){
			if(pre[m]-pre[m-i] == 0)ans++;
		}cout << ans << endl;return 0;
	}int d1 = S-pos1,d2 = pos2-T;
	tot = n-len+1;ans.set();
	for(int i =0;i<=52;i++)ss[i].reset();
	for(int i = d1+1;i<=tot;i++)ans[i] = 0;
	for(int i = tot-d2;i>=1;i--)ans[i] = 0;
	for(int i = 1;i<=n;i++){
		if(s[i]!='_'){
			if('A'<=s[i] and s[i]<='Z'){
				ss[s[i]-'A'+26][i] = 1;
			}else ss[s[i]-'a'][i] = 1;
		}
	}for(int i =S;i<=T;i++){
		if(t[i] == '.'){
			cout << 0 << endl;return 0;
		}else if(t[i]!='_'){
			if('A'<=t[i] and t[i]<='Z'){
				ans&=ss[t[i]-'A'+26]>>(i-S);
			}else{
				ans&=ss[t[i]-'a']>>(i-S);
			}
		}
	}int res =0;for(int i =1;i<=tot;i++)res+=ans[i];
	cout << res << endl;
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

一开始看错题了，看了好久才发现就是个板子。。。

这个东西本质上是循环移位，我们考虑在 $S$ 前后各添加 $W - 1$ 个 `.`，例如 $W = 5, S = \texttt{ABC}$ 时，添加后 $S = \texttt{....ABC....}$。此时我们发现 $S$ 的每个长度为 $W$ 的子串一一对应一个显示在公告板上的串。那么这就是一个**带通配符字符串匹配**问题。

接下来直接套 [P4173 残缺的字符串](https://www.luogu.com.cn/problem/P4173)即可。展开讲的话，设 $n = |s|, m = |t|$，并且 $t$ 要匹配 $s$。那我们把通配符的值设成 $0$ 后，设 $f_i = \sum\limits_{j = 1}^m t_j (s_{i - m + j} - t_j)^2$，那么 $s_{i - m + 1 \sim i}$ 能匹配 $t$ 当且仅当 $f_i = 0$。把平方拆开，就是若干个减法卷积。考虑翻转 $t$，做加法卷积即可。

时间复杂度是 $O(n \log n)$，带一个巨大常数。

这题用 NTT 会有些难受，因为 $f_i$ 能达到 $5 \times 10^9$，为了保证正确性必须要写双模数（我写的双模数还 T 了），FFT 比 NTT 快很多（可能是我 NTT 的实现劣了），所以我使用的是 FFT。

[code](https://atcoder.jp/contests/abc307/submissions/42981235)

---

