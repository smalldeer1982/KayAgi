# Anthem of Berland

## 题目描述

Berland has a long and glorious history. To increase awareness about it among younger citizens, King of Berland decided to compose an anthem.

Though there are lots and lots of victories in history of Berland, there is the one that stand out the most. King wants to mention it in the anthem as many times as possible.

He has already composed major part of the anthem and now just needs to fill in some letters. King asked you to help him with this work.

The anthem is the string $ s $ of no more than $ 10^{5} $ small Latin letters and question marks. The most glorious victory is the string $ t $ of no more than $ 10^{5} $ small Latin letters. You should replace all the question marks with small Latin letters in such a way that the number of occurrences of string $ t $ in string $ s $ is maximal.

Note that the occurrences of string $ t $ in $ s $ can overlap. Check the third example for clarification.

## 说明/提示

In the first example the resulting string $ s $ is "winlosewinwinlwinwin"

In the second example the resulting string $ s $ is "glorytoreorand". The last letter of the string can be arbitrary.

In the third example occurrences of string $ t $ are overlapping. String $ s $ with maximal number of occurrences of $ t $ is "abcabcab".

## 样例 #1

### 输入

```
winlose???winl???w??
win
```

### 输出

```
5
```

## 样例 #2

### 输入

```
glo?yto?e??an?
or
```

### 输出

```
3
```

## 样例 #3

### 输入

```
??c?????
abcab
```

### 输出

```
2
```

# 题解

## 作者：fighter (赞：35)

## 题解

dp与kmp的巧妙结合。

设文本串s长度为$n$，模式串t长度为$m$。题面中赤裸裸地告诉你$nm\leq 10^7$，这就摆明了复杂度应该在$O(nm)$这个级别，这个$n$的复杂度肯定是扫一遍s，至于$m$，可以猜想是对于s的每个位置进行暴力的匹配。

我们可以考虑用dp来解决这个问题。设$f_i$表示t在s的前$i$个位置最大的出现次数。那么如果一个位置想从之前的位置转移过来，就必须满足t能在这个位置与s匹配，这一部分可以$O(m)$暴力判断。

具体怎么转移呢？首先很明显可以直接从$f_{i-m}$转移过来，表示$i-m+1\sim i$这段放一个完整的t。

但是这还不够，因为有可能在这个位置之前连续而重叠地放了好几个t，也就意味着新放进去地这个t并不是完整地，而是和上一个t的后缀重叠构成的。那么这就需要满足t的一段后缀和一段前缀相等。

这就令我们想到了kmp算法中的next数组。我们可以通过从m开始一直跳next，来保证前缀与后缀相等。

但是又有一个问题，假设我们现在长度为$k$的前后缀相等，我们却不能直接从$f_{i-(m-k)}$转移，因为$f$的定义并不能保证$f_{i-(m-k)}$这个位置上一定放了t。

所以我们再定义一个$g_i$，表示s的前$i$个位置，强制最后放一个t的最大出现次数。那么这样我们上面的情况就可以通过$g$之间的转移来实现了。即$g_i=\max\{g_{i-(m-k)}+1,g_i\}$，一直跳next更新即可。

转移完$g$之后，我们再令$f_i=\max\{f_{i-1}, g_i\}$，也就是考虑放和不放t两种情况。

## 代码

```cpp
#include <bits/stdc++.h>
#define MAX 100005
using namespace std;

char s[MAX], t[MAX];
int n, m;
int Next[MAX], f[MAX], g[MAX];

bool chk(int p){
    for(int j = 1; j <= m; j++){
        if(s[p-j+1] != t[m-j+1] && s[p-j+1] != '?') return false;
    }
    return true;
}

int main()
{
    scanf("%s%s", s+1, t+1);
    n = strlen(s+1), m = strlen(t+1);
    for(int i = 2, j = 0; i <= m; i++){
        while(j && t[j+1] != t[i]) j = Next[j];
        if(t[j+1] == t[i]) j++;
        Next[i] = j;
    }

    for(int i = 1; i <= n; i++){
        f[i] = f[i-1];
        if(chk(i)){
            g[i] = f[i-m]+1;
            for(int j = Next[m]; j; j = Next[j]){
                g[i] = max(g[i], g[i-(m-j)]+1);
            }
            f[i] = max(f[i], g[i]);
        }
    }
    cout << f[n] << endl;

    return 0;
}
```



---

## 作者：xyf007 (赞：15)

来一个与 $|s|\times|t|$ 无关的做法，其实是对某些题解做法的优化。

设 $f_i$ 表示考虑 $s$ 的前 $i$ 个字符，且 $t$ 恰好匹配 $s[i-|t|+1..i]$ 的情况下，$t$ 在 $s$ 中出现次数最大值。这样需要预处理每一个位置能否匹配 $t$，可以使用 FFT，参考 [P4173 残缺的字符串](https://www.luogu.com.cn/problem/P4173)。  
考虑转移，如果上一次出现的位置与这一次不相交，那么就是 $\max\limits_{j\le i-|t|}f_j+1$。如果相交，重叠部分既是 $t$ 的前缀也是 $t$ 的后缀，即 $t$ 的 border，转移为 $\max\limits_{j>i-|t|,j-(i-|t|)\in B(t)}f_j+1$。根据结论「一个长度为 $n$ 的字符串所有 border 可以划分成 $O(\log n)$ 段等差数列」，只需要对每一个公差 $d$ 维护形如 $f_{t-d},f_{t-2d},\ldots,f_{t-kd}$ 的最大值，可以通过单调队列实现。此外，由于第一种转移的存在，把这个等差数列的滑动窗口最大值变成前缀最大值不会导致错误，可以不用单调队列，简化代码。  
预处理时间复杂度 $O((|s|+|t|)\log(|s|+|t|))$，转移时间复杂度 $O(|s|\log|t|)$，总时间复杂度 $O((|s|+|t|)\log(|s|+|t|))$。

参考代码
```cpp
#pragma GCC optimize("O3,unroll-loops")
#include <algorithm>
#include <atcoder/convolution>
#include <atcoder/modint>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using mint = atcoder::modint998244353;
template <typename T1, typename T2>
void checkmax(T1 &x, T2 y) {
  if (x < y) x = y;
}
template <typename T1, typename T2>
void checkmin(T1 &x, T2 y) {
  if (x > y) x = y;
}
std::string s, t;
int n, m, nxt[100001], f[100001], pre[100001], g[100001][41];
bool ok[100001];
int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
  std::getline(std::cin, s), std::getline(std::cin, t);
  n = s.size(), m = t.size();
  if (m > n) {
    std::cout << "0\n";
    return 0;
  }
  std::vector<mint> a(n), b(m), c(n), d(n);
  for (int i = 0; i < n; i++) a[i] = s[i] == '?' ? 0 : s[i] - 'a' + 1;
  for (int i = 0; i < m; i++) b[i] = t[i] - 'a' + 1;
  std::reverse(b.begin(), b.end());
  for (int i = 0; i < n; i++) c[i] = a[i] * a[i];
  c = atcoder::convolution(b, c);
  for (int i = m - 1; i < n; i++) d[i] = mint::raw(mint::mod() - 2) * c[i];
  c.resize(n);
  std::copy(a.begin(), a.end(), c.begin());
  for (int i = 0; i < m; i++) b[i] *= b[i];
  c = atcoder::convolution(b, c);
  for (int i = m - 1; i < n; i++) d[i] += c[i];
  for (int i = 0; i < n; i++) a[i] = a[i] * a[i] * a[i];
  std::partial_sum(a.begin(), a.end(), a.begin());
  d[m - 1] += a[m - 1];
  for (int i = m; i < n; i++) d[i] += a[i] - a[i - m];
  for (int i = m - 1; i < n; i++) ok[i] = !d[i].val();
  nxt[0] = -1;
  for (int i = 1, j = -1; i < m; i++) {
    while (j != -1 && t[j + 1] != t[i]) j = nxt[j];
    if (t[j + 1] == t[i]) j++;
    nxt[i] = j;
  }
  std::vector<int> border;
  border.reserve(m);
  for (int i = nxt[m - 1]; i != -1; i = nxt[i]) border.emplace_back(i + 1);
  std::vector<std::pair<int, int>> tr;
  if (border.size() == 1) {
    tr.emplace_back(border[0], 0);
  } else {
    int d = 0;
    for (std::size_t i = 1; i < border.size(); i++)
      if (border[i - 1] - border[i] != d)
        d = border[i - 1] - border[i], tr.emplace_back(border[i - 1], d);
  }
  for (int i = m - 1; i < n; i++) {
    int w = 0;
    if (ok[i]) {
      f[i] = i >= m ? pre[i - m] : 0;
      for (std::size_t j = 0; j < tr.size(); j++)
        checkmax(f[i], g[i - m + tr[j].first][j]);
      w = ++f[i];
    }
    pre[i] = std::max(pre[i - 1], w);
    for (std::size_t j = 0; j < tr.size(); j++)
      g[i][j] = std::max(g[i - tr[j].second][j], w);
  }
  std::cout << *std::max_element(f, f + n) << '\n';
  return 0;
}
```

---

## 作者：Vocalise (赞：15)

## 题意

给一个包含不定字符的主串 $s$ 和一个确定的模式串 $t$，求把不定字符分配后的匹配数最大值。

$|t|,|s|\leq 10^5,|s|\times |t| \le 10^7$

## 解法

看到数据范围，我们考虑 dp。

设 $f_{i,j}$ 表示 $s$ 的前 $i$ 位和 $t$ 匹配，其中最后几个字符和 $t$ 匹配到第 $j$ 个字符的最大匹配数。

特别地，若 $j=m$，它的贡献我们会加上。

初始状态：$f_{0,0} = 0$，其它设为 $-\inf$。

对于转移，我们分情况考虑：

$j>0$，此时有匹配段。

$s_i = t_j$ 或者 $s_i = \texttt ?$ 时，我们可以尝试匹配该位，令 $f_{i,j} = f_{i-1,j-1}$。

之后，如果 $j=m$，需要单独考虑：

先加上本段贡献。令 $f_{i,j}$ 加一。

发现之后的串可以以当前的一个后缀作前缀直接匹配。也就是 $\text{Border}$。

预处理 $t$ 的失配数组后，我们暴力遍历 $t$ 的所有 $\text{Border}$，设其长 $k$，令 $f_{i,k}$ 与 $f_{i,j}$ 取最大值。这一步类比 KMP 算法中匹配成功后回跳一步的过程就可以理解了。

最后，因为可以在任意位置中断下一个字符的匹配，所以 

$f_{i,0} = \max\limits_{j=1}^m\{f_{i,j},f_{i-1,j}\}$

那么，可以清楚地看出，这就在 $\mathcal O(|s|\times|t|)$ 的时间内解决了该问题。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

const int N = 100001;
const int NM = 11100101;

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

char s[N],t[N];
int F[NM],n,m,p[N];

int &f(int x,int y) { return F[x * (m + 1) + y + 1]; }

int main() {
    std::scanf("%s\n%s",s + 1,t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    p[1] = 0;
    for(int i = 2, j = 0;i <= m;i++) {
        while(j && t[j + 1] != t[i]) j = p[j];
        if(t[j + 1] == t[i]) j++;
        p[i] = j;
    }
    memset(F,128,sizeof F);
    f(0,0) = 0;
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= m;j++) {
            if(s[i] == t[j] || s[i] == '?') {
                f(i,j) = f(i - 1,j - 1);
            }
            if(j == m) {
                f(i,j)++;
                for(int k = p[m];k;k = p[k]) f(i,k) = std::max(f(i,k),f(i,j));
            }
        }
        for(int j = 0;j <= m;j++) f(i,0) = std::max(f(i,0),std::max(f(i,j),f(i - 1,j)));
    }
    std::printf("%d\n",f(n,0));
    return 0;
}

```



---

## 作者：Saliеri (赞：10)

给一发不用脑子的做法。

___

前置知识：KMP 自动机。

其核心是一个数组 $aut_{i,c}$,其意义为：模式串的前 $i-1$ 位已经匹配完成，用 $c$ 与 $t_i$ 匹配后的匹配长度。

构造方式：

首先求出 $next$ 数组。

$aut$ 数组的构造方式（转移方程）：

 $$
 aut_{i,c} = 
\begin{cases}
aut_{next_{i-1}+1,c} & i = 1 \operatorname{or} t_i\neq c\\
i+[t_i = c] & a \lt 1 \\
\end{cases}
$$

解释一下 $aut_{next_{i-1}+1,c}$ 的意义。

我们现在只匹配好了前 $i-1$ 位，用 next 数组跳回后还需跳至它的下一位。

tip：一般为了实现方便，会往字符串末尾加一个特殊字符 #。

___

进入正题：

一眼 DP

设 $dp_{i,j}$ 为当前扫描到 s 的第 i 位，在 KMP 自动机上的节点 j ，匹配的最大次数。

转移比较显然，建议看代码。

最后的答案就是 $\max_{1\leq i\leq |t|}dp_{|s|,i}$。

因为 s,t 大小不定，需要滚动数组。

时间复杂度 $O(|s|\times|t|)$,带一个 26 的常数，~~但是卡过去了~~.

代码：

```cpp
#include <cstdio>
#include <cstring>
const int maxn = 1e5+5;
inline int max(int a,int b){return a>b?a:b;}
int n,m,dp[2][maxn],next[maxn],aut[maxn][26];
char s[maxn],t[maxn];
int main(){
	scanf("%s%s",s+1,t+1);
	n = strlen(s+1),m = strlen(t+1);
	t[++m] = '#';
	next[1] = 0;
	for(int i=2,j=0;i<=m;++i){
		while(j&&t[i]!=t[j+1])j = next[j];
		if(t[i] == t[j+1])++j;
		next[i] = j;
	}
	for(int i=1;i<=m;++i){
		for(int c=0;c<26;++c){
			if(i>1&&t[i]!=c+'a')
				aut[i][c] = aut[next[i-1]+1][c];
			else aut[i][c] = i+(t[i]==c+'a');
		}
	}
	memset(dp,0xcf,sizeof(dp));
	dp[0][1] = 0;
	for(int i=1;i<=n;++i){
		if(s[i] == '?'){
			for(int j=1;j<=m;++j){
				for(int c=0;c<26;++c)
					dp[i&1][aut[j][c]] = max(dp[i&1][aut[j][c]],dp[(i-1)&1][j]+(aut[j][c]==m));
			}
		}else{
			for(int j=1;j<=m;++j)
				dp[i&1][aut[j][s[i]-'a']] = max(dp[i&1][aut[j][s[i]-'a']],dp[(i-1)&1][j]+(aut[j][s[i]-'a']==m));
		}
		for(int j=1;j<=m;++j)dp[(i-1)&1][j] = -0x3f3f3f3f;
	}
	int maxx = 0;
	for(int j=1;j<=m;++j)maxx = max(maxx,dp[n&1][j]);
	printf("%d",maxx);
	return 0;
}
```

---

## 作者：Rushroom (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF808G)

KMP 好题。

相信做完这道题后一定会对 KMP 有更深的理解了。

### 前置芝士

> [KMP 算法](https://oi-wiki.org/string/kmp/)

### 约定

$n= \left| s \right|,m= \left| t \right|$

### 思路

我们首先想一想，我们平时在做 KMP 的时候，是怎么匹配的。

很明显就是一边走，一边跳 $fail$ 是吧。

每次 $fail$ 跳到 $m$ 的时候，就把匹配的次数 $+1$。

因为这个过程是分成一步一步的，那么很容易想到用 DP 解决。

设 $f_{i,j}$ 为：现在处理到 $s$ 的第 $i$ 位，$fail$ 指针跳到了 $j$，最多匹配次数是多少。

那么我们转移的时候，既然已经知道了 $fail$ 是多少，那就直接跳 $fail$ 转移就行了。

如果遇到 `?`，就枚举它是什么字母。

### 优化

上面的做法可能会 TLE（说 可能 是因为我也没试过）。

优化的方法是预处理出 $to_{i,j}$ 表示：现在 $fail$ 跳到 $i$，当前的字母是 $j$，最后会 $fail$ 会跳到哪里。

预处理可以直接按普通的 KMP 做就行了，不懂的可以看代码。

最后，时间复杂度是 $O(nm \left| 
\Sigma \right|)$，其中 $\left| 
\Sigma \right|=26$。

~~神奇的是它居然卡过去了~~

### [Code](https://www.luogu.com.cn/paste/lrhqxf66)

---

### 推荐练习

[P3193 [HNOI2008]GT考试](https://www.luogu.com.cn/problem/P3193)

跟这个题思路类似，只是要套一个矩阵快速幂（~~怎么跟我出的题一样缝合啊~~）

---

## 作者：zhimao (赞：4)

令 $s$ 串长度 $n$，$t$ 串长度 $m$。

这是一个傻逼 $O(|\sum|m^2+|\sum|nm)$ 做法，但不需要 kmp 。

其实很简单，把 kmp 改成 $m^2$ 暴力即可。

但这样复杂度为什么正确呢？因为 $nm\le10^7$，答案不为 0 时 $m\le n$ 所以 $m\le\sqrt{10^7}$。

我的 dp 比较拉跨因此它的复杂度会带上字符集，大概是这样

正常匹配 
$
f[i][j]=\max(f[i][j],f[i-1][b[j][s[i]]])
$

当正好匹配完时 
$
f[i][nex_m]=\max(f[i][nex_m],f[i-1][m-1])
$

当无法匹配时 
$
f[i][0]=\max(f[i][0],f[i-1][j])
$

其中 $f[i][j]$ 为 $s$ 前 $i$ 位最后匹配到 $t$ 前 $j$ 位最多匹配了几次，$nex$ 就相当于 kmp 失配数组，$b[i][j]$ 为匹配到 $t$ 的前 $i$ 位，下一位字符是 $j$ 时最多可匹配到前几位。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000000],f[20000005],b[10005][26];
char s[100005],t[100005];
inline int id(const int x,const int y)
{
	return x*m+y;
}
void add(int p,char y)
{
	for(int i=0;i<m;i++)
	{
		int x=b[i][y-97];
		if(t[x+1]==y)
		{
			if(x+1==m) f[id(p,a[m])]=max(f[id(p-1,i)]+1,f[id(p,a[m])]); else f[id(p,x+1)]=max(f[id(p,x+1)],f[id(p-1,i)]);
		}
		else f[id(p,x)]=max(f[id(p,x)],f[id(p-1,i)]);
	}
}
int main()
{
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	if(n<m)
	{
		puts("0");
		return 0;
	}
	for(int i=m;i>1;i--)
		for(int j=1;i+j-1<=m;j++)
			if(t[j]==t[i+j-1]) a[i+j-1]=j; else break;
	for(int i=1;i<m;i++)
		for(int j=0;j<26;j++)
		{
			b[i][j]=i;
			while(b[i][j]&&t[b[i][j]+1]!=j+97) b[i][j]=a[b[i][j]];
		}
	for(int i=1;i<=m;i++) f[id(0,i)]=-10000000;
	for(int j=1;j<=n;j++)
		for(int i=0;i<=m;i++) f[id(j,i)]=-10000000;
	for(int i=1;i<=n;i++)
		if(s[i]=='?')
		{
			for(char j=97;j<123;j++) add(i,j);
		}
		else add(i,s[i]);
	int ans=0;
	for(int i=0;i<m;i++) ans=max(ans,f[id(n,i)]);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：3)

### Preface

难度可以稍微降一降？至多蓝吧……

我只用了 Dp 啊，没用啥哈希、KMP……

### Analysis

**以下字符串下标从 $1$ 开始，$|s|=n,|t|=m,n\ge m$。**

时间显然是 $O(nm)$ 或 $O(m^2)$ 的。

如果不考虑 $t$ 重叠的情况，那 Dp 非常容易。设 $f_i$ 表示 $s$ 中 $t$ 当前最后匹配到 $s[i\dots(i+m-1)]$ 时的最大匹配次数。若 $s[i\dots(i+m-1)]$ 可以等于 $t$，那么：

$$f_i=1+\max\limits_{j=1}^{i-m}f_j$$

用前缀和优化即可。

考虑 $t$ 重叠的情况，重叠部分长度为 $len$ 的条件为 $t[1\dots len]=t[(m-len+1)\dots m]$（前缀 $=$ 后缀），我们可以 $O(m^2)$ 预处理出所有可行的 $len$ 存为集合 $S$。

那 Dp 转移改一下就能 $O(m(n+m))$ 过了：

$$f_i=1+\max\{\max\limits_{j=1}^{i-m}f_j,\max\limits_{j\in S}f_{i-m+j}\}$$

### Code

[Link](https://codeforces.com/contest/808/submission/146633288)

---

## 作者：Piwry (赞：2)

## 解析

用 ACAM 做

考虑直接 dp

设 $dp(i, q)$ 表示输入完 $s[0..i]$ 后自动机状态为 $q$ 时的最大匹配数

于是就做完了。比起先求出可能的匹配位置再 dp 的做法要简单很多；但是最坏复杂度多了一个字符集，是 $\Theta((m+nm)|\Sigma|)$ 的。好在能卡过 \kk

（和 [这篇题解](https://www.luogu.com.cn/blog/shan-cheng/solution-cf808g) 说的其实是一个东西）

## CODE

比起另一种写法的代码要短不少（

```cpp
#include <cstdio>
#include <vector>
using std::vector;
using std::max;

const int MAXN =1e5+20, MAXCH ='z'-'a'+1;

/*------------------------------IO------------------------------*/

struct string{
	char data[MAXN];
	int len;
	
	int size() const{
		return len;
	}
	
	char & operator [] (const int &index){
		return data[index];
	}
	char operator [] (const int &index) const{
		return data[index];
	}
};

void read_string(string &s){
	char ch =getchar();
	while((ch < 'a' || ch > 'z') && ch != '?')
		ch =getchar();
	s.len =0;
	while((ch >= 'a' && ch <= 'z') || ch == '?')
		s[s.len++] =ch, ch =getchar();
}

/*------------------------------ACAM------------------------------*/

namespace ACAM{
	int delta[MAXN][MAXCH];
	int fail[MAXN];
	
	void init(const string &s){
		for(int i =0; i < s.size(); ++i)
			delta[i][s[i]-'a'] =i+1;
		for(int u =1; u <= s.size(); ++u)
			for(int ch =0; ch < MAXCH; ++ch){
				if(delta[u][ch])
					fail[delta[u][ch]] =delta[fail[u]][ch];
				else
					delta[u][ch] =delta[fail[u]][ch];
			}
	}
};

/*------------------------------Main------------------------------*/

int main(){
	string s, t;
	read_string(s), read_string(t);
	
	ACAM::init(t);
	
	vector<int> dp(t.size()+1, -0x3f3f3f3f);
	dp[0] =0;
	for(int i =0; i < (int)s.size(); ++i){
		vector<int> dp_tmp(t.size()+1, -0x3f3f3f3f);
		if(s[i] == '?')
			for(int q =0; q <= t.size(); ++q)
				for(int ch =0; ch < MAXCH; ++ch){
					const int q_ =ACAM::delta[q][ch];
					dp_tmp[q_] =max(dp_tmp[q_], dp[q]+(q_ == t.size()));
				}
		else
			for(int q =0; q <= t.size(); ++q){
				const int q_ =ACAM::delta[q][s[i]-'a'];
				dp_tmp[q_] =max(dp_tmp[q_], dp[q]+(q_ == t.size()));
			}
		dp.swap(dp_tmp);
	}
	int ans =0;
	for(int q =0; q <= t.size(); ++q)
		ans =max(ans, dp[q]);
	printf("%d", ans);
}
```

---

