# Bracket Substring

## 题目描述

You are given a bracket sequence $ s $ (not necessarily a regular one). A bracket sequence is a string containing only characters '(' and ')'.

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Your problem is to calculate the number of regular bracket sequences of length $ 2n $ containing the given bracket sequence $ s $ as a substring (consecutive sequence of characters) modulo $ 10^9+7 $ ( $ 1000000007 $ ).

## 说明/提示

All regular bracket sequences satisfying the conditions above for the first example:

- "(((()))())";
- "((()()))()";
- "((()))()()";
- "(()(()))()";
- "()((()))()".

All regular bracket sequences satisfying the conditions above for the second example:

- "((()))";
- "(()())";
- "(())()";
- "()(())".

And there is no regular bracket sequences of length $ 4 $ containing "(((" as a substring in the third example.

## 样例 #1

### 输入

```
5
()))()
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3
(()
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2
(((
```

### 输出

```
0
```

# 题解

## 作者：hs_black (赞：4)

# CF1015F Bracket Substring

[博客内查看](https://www.cnblogs.com/Hs-black/p/12295083.html)

这题一眼[GT考试](https://www.luogu.com.cn/problem/P3193)

题意: 求有多少种合法的括号序列要求字符串S是其字串

数据范围大概是一个$\Theta(n^3)$的算法

从前往后填括号, 设$F[i][j][k]$表示填到第$i$位, "和"为$j$, 匹配了$S k$位, 其中和的定义为将左括号看做1, 右括号看作-1, 一个合法的括号序列的前缀和总大于等于零且本身的和为零(一个左括号一定匹配一个右括号)

$dp$时只需枚举下一位填$'('$或$')'$即可, 但要注意的是匹配$S$串时从第$k$位不匹配不是直接重新从0开始匹配而是求出它的$kmp$数组, 找到上一个$border$, 可以参考代码

```cpp
#pragma GCC optimize(2)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

template <typename T>
void read(T &x) {
    x = 0; bool f = 0;
    char c = getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=1;
    for (;isdigit(c);c=getchar()) x=x*10+(c^48);
    if (f) x=-x;
}

template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 305;
char s[N];
ll n, m;
int g[N][2], nxt[N];

void KMP(void) {
	int j = nxt[1] = 0;
	for (int i = 2;i <= m; i++) {
		while (j && s[i] != s[j+1]) j = nxt[j];
		if (s[i] == s[j+1]) j++;
		nxt[i] = j;
	}
	for (int i = 0;i < m; i++) {
		int k = i, p = i;
		while (k && s[k+1] != '(') k = nxt[k];
		while (p && s[p+1] != ')') p = nxt[p];
		if (s[k+1] == '(') k++;
		if (s[p+1] == ')') p++;
		g[i][1] = k, g[i][0] = p;
	}
	g[m][0] = g[m][1] = m;
}

const int P = 1e9+7;
ll f[N][N][N];

inline void add(ll &x, ll y) {
	x += y; if (x >= P) x -= P;
}

int main() {
	read(n); int al = n << 1;
	scanf ("%s", s + 1);
	m = strlen(s + 1);
	KMP();
	f[0][0][0] = 1;
	for (int i = 0; i < al; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k <= m; k++) {
				ll t = f[i][j][k];
				if (j) add(f[i+1][j-1][g[k][0]], t);
				add(f[i+1][j+1][g[k][1]], t);
			}
		}
	}
	cout << f[al][0][m] << endl;
	return 0;
}
```



---

## 作者：spire001 (赞：2)

## 前言
来一篇纯 AC 自动机的题解。

## 分析
这个题很裸，两个约束，子串以及合法的括号序列。

前一个约束可以通过 AC 自动机实现，后者直接在做动态规划的过程中保证 `(` 的数量大于 `)` 即可。

最后答案即为 `(` 等于 `)` 且长度合法，且给定字符串是其子串的方案数。

设置状态 $dp_{0/1,i,j,k}$ 表示是否为子串，当前长度，所在节点，`(` 的数量减去 `)` 数量的值的方案数。

转移是平凡的。

## 略微有点长的代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <numeric>
#include <queue>   
#include <bitset>
#define gid(x) (x - '(')

using namespace std;

typedef long long LL;
constexpr int C = 2, N = 120;
constexpr int mod = 1e9 + 7;

int n;
string s;

LL dp[2][N << 1][N << 1][N << 1]; // 数组别开太大，会 MLE
// 是否子串 长度 节点 权值


struct trie {
  int child[C][N * 4];
  int tot;
  bitset<N * C * 4> box;
  int fail[N * C * 4];

  void insert(const string &s)
  {
    const int siz = (int)s.size();

    int p = 0;

    for (int i = 0; i != siz; i++)
    {
      const int c = gid(s[i]);
      if (!child[c][p]) child[c][p] = ++tot;
      p = child[c][p];
    }
    
    box[p] = 1;

    return;
  }

  void get_fail() // fail 指针
  {
    queue<int> q;
    
    for (int i = 0; i != C; i++)
      if (child[i][0])
        q.push(child[i][0]);
  
    while (!q.empty())
    {
      int u = q.front(); q.pop();

      for (int i = 0; i != C; i++)
        if (const int v = child[i][u]; v)
          fail[v] = child[i][fail[u]], q.push(v);
        else
          child[i][u] = child[i][fail[u]];
    }

    return;
  }

  void solve()
  {
    dp[0][0][0][0] = 1; // 初始化
    for (int i = 1; i <= n * 2; i++)
      for (int j = 0; j <= tot; j++)
        for (int c = 0; c != C; c++)
          for (int s = 0; s != 2; s++)
            for (int p = 0; p <= n; p++)
            {
              int t = (c == 0 ? 1 : -1);
              const int v = child[c][j];
              if (p + t >= 0)
                (dp[s | box[v]][i][v][p + t] += dp[s][i - 1][j][p]) %= mod;
            }
    return;
  }
} t;

constexpr int siz = sizeof (dp) / 1048576;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> s;

  t.insert(s); t.get_fail();
  t.solve();

  LL ans = 0;

  for (int i = 0; i <= t.tot; i++)
    ans = (ans + dp[1][n << 1][i][0]) % mod;
  
  cout << ans << endl;

  return 0;
}

/*
begin: 2024年8月31日16:27:44
debug: 2024年8月31日17:23:18
finish: 2024年8月31日17:26:00
*/
```

---

## 作者：Mickey_snow (赞：2)

从左往右加字符，弄个预处理搞一下。

这题分为两部分，首先我们预处理出来一个二维数组 $len$.

```
	public static int[,] len = new int[s.Length + 1, 2];
```

$len$ 的第二维只可能是0或者1. $len_i,_j$ 代表 $s$ 取前i个字符，后面加上一个'('或者')'之后组成一个新的字符串 $t$ , $t$ 的后缀最多能与 $s$ 的前缀匹配多少位。

假设 s = '())()', 那么 $len_5,_1$ 就是 $s$ 取前5位再加上一个')' ，这时 $t$ = '())()), $t$ 的后缀最多能与 $s$ 的前缀匹配3位，所以 $len_5,_1 = 3$. 这一步可以暴力完成，时间复杂度不算太高。这是随后Dp的根据。

正式的Dp需要一个四维数组。

```
	public static int[,,,] Dp = new int[(len << 1) + 5, (len << 1) + 5, s.Length + 5, 2];

```

保险起见这里开的大了一点。具体含义是 $Dp_i,_j,_k,_p$ 代表搞一个长度为 $i$ 的串，这个串中左括号数量减去右括号数量为 $j$, 这个串的后缀与 $s$ 的前缀最长能够匹配 $k$ 位，这个串中是否已经出现过至少一次串 $s$（$p=0$代表没有，$p=1$反之）。数值为构成满足以上条件的串的方案数。

那么显而易见 $Dp_0,_0,_0,_0 = 1$, 除此之外 $Dp$ 数组中所有的值都是0.

这里的转移非常的暴力，准确地说这应该是递推而非动态规划。

```
	if(Global.Dp[i, j, k, fin] == 0) continue;
	if(j < len) {
		Global.Dp[i + 1, j + 1, Global.len[k, 0], fin | (Global.len[k, 0] == s.Length ? 1 : 0)] += Global.Dp[i, j, k, fin];
		Global.Dp[i + 1, j + 1, Global.len[k, 0], fin | (Global.len[k, 0] == s.Length ? 1 : 0)] %= mod;
	}
	if(j > 0) {
		Global.Dp[i + 1, j - 1, Global.len[k, 1], fin | (Global.len[k, 1] == s.Length ? 1 : 0)] += Global.Dp[i, j, k, fin];
		Global.Dp[i + 1, j - 1, Global.len[k, 1], fin | (Global.len[k, 1] == s.Length ? 1 : 0)] %= mod;
	}
```

虽然写的复杂，但是其思路是非常直观的，枚举一下当前的状态，试着往后面加一个'(',试着往后面加一个')',更新一下。

前面 $i$ 和 $j$ 的变化很好想，第三维我们保存的是这个串的后缀与 $s$ 的前缀能够匹配的最大长度，加上了一个字符应该如何更新？这就是前面算的 $len$ 的作用。因为我们知道当前串后 $k$ 位和 $s$ 的前 $k$ 位是完全一样的，那么如果加上一个 '(' 后新的 $k$ 不就应该是 $len_k,_0$ 吗，加上 ')' 则是 $len_k,_1$ 回顾 $len$ 的定义，会发现此处正好是这种情况。

Dp完了以后，还需要累加一下答案。所有 $Dp_2*_n,_0,_i,_1$ 都是符合题意的合法括号序列生成方案数，加起来就是答案。

完整的代码如下：

```
using System;

namespace CF1015F
{
    class Program
    {
		public class Global 
		{
			public static int[,] len;
			public static int[,,,] Dp;
		}

		static void Main(string[] args)
        {
			const int mod = 1000000007;

			int len = Convert.ToInt32(Console.ReadLine());
			string s = Console.ReadLine(), t = "";

			Global.len = new int[s.Length + 1, 2];
			Global.Dp = new int[(len << 1) + 5, (len << 1) + 5, s.Length + 5, 2];
			Global.Dp[0, 0, 0, 0] = 1;

			if(s[0] == '(') Global.len[0, 0] = 1;
			else Global.len[0, 1] = 1;
			for(int i = 0; i < s.Length; i++) {
				t += s[i];t += '(';
				Global.len[i + 1, 0] = Match(s, t);
				t = t.Remove(t.Length - 1, 1); t += ')';
				Global.len[i + 1, 1] = Match(s, t);
				t = t.Remove(t.Length - 1, 1);
			}

			for(int i = 0; i < (len << 1); i++)
				for(int j = 0; j <= len; j++)
					for(int k = 0; k <= s.Length; k++) 
						for(int fin = 0; fin <= 1; fin++) {
							if(Global.Dp[i, j, k, fin] == 0) continue;
							if(j < len) {
								Global.Dp[i + 1, j + 1, Global.len[k, 0], fin | (Global.len[k, 0] == s.Length ? 1 : 0)] += Global.Dp[i, j, k, fin];
								Global.Dp[i + 1, j + 1, Global.len[k, 0], fin | (Global.len[k, 0] == s.Length ? 1 : 0)] %= mod;
							}
							if(j > 0) {
								Global.Dp[i + 1, j - 1, Global.len[k, 1], fin | (Global.len[k, 1] == s.Length ? 1 : 0)] += Global.Dp[i, j, k, fin];
								Global.Dp[i + 1, j - 1, Global.len[k, 1], fin | (Global.len[k, 1] == s.Length ? 1 : 0)] %= mod;
							}
						}

			int _count = 0, final_Len = len << 1;
			for(int i = 0; i <= s.Length; i++) {
				_count += Global.Dp[final_Len, 0, i, 1];
				_count %= mod;
			}

			Console.WriteLine(_count.ToString());
		}

		static int Match(string a,string t) {
			for(int i = Math.Min(t.Length, a.Length); i > 0; i--)
				if(a.Substring(0, i) == t.Substring(t.Length - i, i))
					return i;
			return 0;
		}
	}
}
```

---

## 作者：Nightingale_OI (赞：1)

~~一道良心的 DP 题。~~

------------

考虑记 $ dp_{i,j,k} $ 表示前 $ i $ 个字符，和给定串匹配 $ j $ 个，有 $ k $ 个待匹配左括号的方案数。

让 $ i $ 从 $ i - 1 $ 转移来比较困难，可以让其转移到 $ i + 1 $ 。

枚举选的是左括号还是右括号，再套 KMP 即可。

------------

代码如下 （~~非常简单~~)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
const int mo=1e9+7;
int dp[202][202][202];
int kmp[202];
string st;
int main(){
    cin>>n;
    n=n*2;
    cin>>st;
    m=st.length();
    st="@"+st;
    l=0;
    for(register int i=2;i<=m;++i){
        while(l && st[l+1]!=st[i])l=kmp[l];
        if(st[l+1]==st[i])++l;
        kmp[i]=l;
    }
    dp[0][0][0]=1;
    for(register int i=0;i<n;++i){
        for(register int j=0;j<=m;++j){
            for(register int k=0;k<=i;++k){
                l=j;
                if(j<m){
                    while(l && st[l+1]!='(')l=kmp[l];
                    if(st[l+1]=='(')++l;
                }
                dp[i+1][l][k+1]=(dp[i+1][l][k+1]+dp[i][j][k])%mo;
                if(!k)continue;
                l=j;
                if(j<m){
                    while(l && st[l+1]!=')')l=kmp[l];
                    if(st[l+1]==')')++l;
                }
                dp[i+1][l][k-1]=(dp[i+1][l][k-1]+dp[i][j][k])%mo;
            }
        }
    }
    cout<<dp[n][m][0]<<endl;
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较大力的 KMP 题？

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
看到方案数，想到 dp。

题目中唯一比较难处理的就是子串，考虑把这东西也扔 dp 里。

因为括号序列最后还要匹配，所以要把括号序列的目前状态也扔进去。

这样我们就有了三维 dp：$f_{i,j,k}$ 表示目前填到第 $i$ 位，括号序列还有 $j$ 个多余的左括号待匹配，和字符串 $s$ 匹配到了第 $k$ 位的方案数。

考虑怎么转移这个东西。

因为括号序列只能填 `(` 和 `)`，所以对于这两种字符都填进去跑下 KMP 匹配下找到最长的 $k$ 转移即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,f[N][N][N],nxt[N];char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='('||c==')'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace KMP
{
	inline void kmp(char s[],int n,int nxt[])
	{
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;
			nxt[i]=j;
		}
	}
	inline int find(int j,char c,char s[],int nxt[])
	{
		while(j&&s[j+1]!=c) j=nxt[j];
		if(s[j+1]==c) j++;
		return j;
	}
	inline int findstr(int n,int m,char s1[],char s2[],int nxt[])
	{
		int j=0;
		for(int i=1;i<=n;i++)
		{
			while(j!=0&&s2[j+1]!=s1[i]) j=nxt[j];
			if(s2[j+1]==s1[i]) j++;
			if(j==m) return -1;
		}
		return j;
	}
}
using namespace KMP;
signed main()
{
    n=read()<<1;rd(s,m);kmp(s,m,nxt);f[0][0][0]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=i;k++)
			{
				int l=j;if(j==m) goto play1;
				while(l&&s[l+1]!='(') l=nxt[l];
				if(s[l+1]=='(') l++;play1:;
				f[i+1][l][k+1]=(f[i+1][l][k+1]+f[i][j][k])%mod;
				if(!k)continue;l=j;if(j==m) goto play2;
				while(l&&s[l+1]!=')') l=nxt[l];
				if(s[l+1]==')') l++;play2:;
				f[i+1][l][k-1]=(f[i+1][l][k-1]+f[i][j][k])%mod;
			}
	print(f[n][m][0]);
    genshin:;flush();return 0;
}
```

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

对于给定字符串 $s$，求可能的字符串 $s'$ 的个数，使得 $s'$ 满足含有子串 $s$，且 $s'$ 为合法括号序列。

### 题目分析

首先考虑合法序列这一限制，常规判断方法为设数组 $a$，对于 $s_i$，`(` 记为 $1$，`)` 记为 $0$。则对于 $s$，满足 $\forall i \in [1, |s|], (\sum \limits_{j=1}^{j\le i}a_j) \ge0$ 且 $(\sum\limits_{i=1}^{i\le |s|} a_i) = 0$。

由于 $n,|s|$ 较小，可以考虑 dp，不妨将能影响答案的变量都记在状态里，设 $f_{i,j,k,0/1}$ 表示枚举到 $s'$ 的第 $i$ 位，$(\sum\limits_{l=1}^{l\le i}a_l) = j$，同时匹配到 $s$ 的第 $k$ 个字符，当前字符为 $0/1$ 的可能 $s'$ 数量。然后发现 $s_k$ 是已知的，最后一维 $0/1$ 可以不要。

考虑转移，被动转移不好想，想主动转移即 $f_{i,j,k}$ 能转移到什么状态，假设我们想转移给 $f_{i+1,j+1,l}$，即令 $s'_{i+1}$ 为 `(`，我们只需知道 $l$ 最大是多少，假设 $s_{k+1}$ 为 `(`，则 $l$ 最大为 $k+1$，否则我们就看 $s_{border(k)+1}$ 是否为 `(`，以此类推，类似 KMP 思想。转移给 $f_{i+1,j-1,l}$ 同理。

于是我们只需要 KMP 预处理 $s$ 的 border，然后枚举状态，计算 $l$，转移即可。答案即为 $f_{2n,0,|s|}$。

所以时间复杂度是 $\mathcal O(n ^ 2 \times |s| ^ 2)$ 级别的，但是因为跑不满能过，其实可以预处理对于每个 $s_k$ 的 $l$，时间复杂度可以降到 $\mathcal O(n ^ 2 \times |s|)$ 的，在此不做过多赘述。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

const int N = 205, MOD = 1e9 + 7;
string s;
int pi[N], f[N][N][N], n, len;

void border(string s)
{
	len = s.size() - 1;
	pi[0] = pi[1] = 0;
	for(int i = 2;i <= len;i++)
	{
		int j = pi[i-1];
		while(j && s[j+1] != s[i])	j = pi[j];
		pi[i] = (s[j + 1] == s[i]) ? j + 1 : 0;
	}
}

int main()
{
	scanf("%d", &n);
	cin >> s;s = "#" + s;
	border(s);
	f[0][0][0] = 1;
	for(int i = 0;i <= n + n;i++)
	{
		for(int j = 0;j <= n;j++)
		{
			for(int k = 0;k < len;k++)
			{
				int tmp = k;
				while(tmp && s[tmp+1] != '(')	tmp = pi[tmp];
				if(s[tmp+1] == '(')
					(f[i+1][j+1][tmp+1] += f[i][j][k]) %= MOD;
				else
					(f[i+1][j+1][0] += f[i][j][k]) %= MOD;
				if(j > 0)
				{
					tmp = k;
					while(tmp && s[tmp+1] != ')')	tmp = pi[tmp];
					if(s[tmp+1] == ')')
						(f[i+1][j-1][tmp+1] += f[i][j][k]) %= MOD;
					else
						(f[i+1][j-1][0] += f[i][j][k]) %= MOD;
				}
			}
			(f[i+1][j+1][len] += f[i][j][len]) %= MOD;
			if(j > 0)	(f[i+1][j-1][len] += f[i][j][len]) %= MOD;
		}
	}
	printf("%d\n", f[n+n][0][len]);
	return 0;
}
```

---

## 作者：氧少Kevin (赞：0)

# CF1015F - Bracket Substring
>- 链接：https://codeforces.com/problemset/problem/1015/F
>- 知识点：DP、KMP、组合数学
>- 难度：蓝（*2300）

## 题意
- 给出一个括号序列 $S(|S|\leq 200)$（可能不合法），和一个正整数 $n(1\leq n\leq100)$。
- 求出以 $S$ 为**子串**的、长度为 $2n$的、合法的括号序列数量。
- 答案对 $10^9+7$ 取模。

## 思路
- 先考虑去重问题。
- 假如 $S$ 是 `()`，我现在需要合成 `()()`，可能导致重复。
- 考虑 KMP + DP。
- 设 $dp[i][j][k]$ 为目前为新串的第 $i$ 位，目前已经和原串的第 $j$ 位完成配对，目前 `(` 比 `)` 多的数量为 $k$。
- 设 $nxt2[i][0/1]$ 代表第 $i$ 个位置已经和 $S$ 的第 $i$ 位产生了配对，如果接下来放的是 `(` 或 `)`，那么将与 $S$ 的哪一位产生配对。
- 转移：
    - 放 `(` $dp[i+1][pos][k+1]+=dp[i][j][k]$，其中 当 $j=m$时，$pos=m$，否则$pos=nxt2[j][0]$
    - 放 `)` $dp[i+1][pos][k-1]+=dp[i][j][k]$，其中 当 $j=m$时，$pos=m$，否则$pos=nxt2[j][1]$
- 我们能发现，这么转移能有效避免重复。
- 重复产生的根源：同一个串中包含多个 $S$。
- 原因：注意看 DP 的状态 $dp[i][j][k]$ 中的 $j$ 代表目前**已经和**原串的第 $j$ 位完成配对。
- 对于某一种符合题意的方案，一旦到了某一位，与 $S$ 恰好产生了完全匹配，那么在这之后，$j$ 一直 $=|S|$。
- 这样能保证：对于一个新串，我在状态上确定了它是否已经与 $S$ 产生了匹配，有效避免重复。
## 代码
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#define int long long
const int N		= 210;
const int MOD	= 1e9+7;
using namespace std;

int nxt[N],nxt2[N][2];
int dp[N][N][N];
char T[N];
int n,m;

void GetNxt()
{
	nxt[1]=0;
	
	int l=0;
	for(int r=2; r<=m; r++)
	{
		while(l>0 && T[r]!=T[l+1]) 
		{
			l = nxt[l];
		}
		if(T[r] == T[l+1]) 
		{
			l ++;
		}
		nxt[r] = l;
	}
	
	for (int i=0; i<=m; i++)
	{
		if(T[i+1]=='(')	nxt2[i][0] = i+1;
		else nxt2[i][0] = nxt2[ nxt[i] ][0];
		
		if(T[i+1]==')')	nxt2[i][1] = i+1;
		else nxt2[i][1] = nxt2[ nxt[i] ][1];
	}
}

void Sol()
{
	GetNxt();
	
	dp[0][0][0] = 1;
	for (int i=0; i<=n; i++)
	{
		for (int j=0; j<=m; j++)
		{
			for (int k=0; k<=i; k++)
			{
				int tmp = nxt2[j][0];
				if(j==m)tmp = m;
				if(k+1<=i+1)dp[i+1][tmp][k+1] += dp[i][j][k], dp[i+1][tmp][k+1]%=MOD;
				
				tmp = nxt2[j][1];
				if(j==m)tmp = m;
				if(k-1>=0)dp[i+1][tmp][k-1] += dp[i][j][k], dp[i+1][tmp][k-1]%=MOD;
			}
		}
	}
	int ans = dp[n][m][0];
	printf("%lld\n",ans);
}

signed main()
{
	scanf("%lld",&n);
	n*=2;
	scanf("%s",T+1);
	m=strlen(T+1);
	Sol();
	
	return 0;
}
```

---

## 作者：hwk0518 (赞：0)

这道题可以用自动机来理解。

建出括号序列的$AC$自动机，处理出上面每一个点加上'('或')'之后能到达的节点。

记$dp[i][j][k]$表示有几个长度为$i$的串，当前在自动机的第$j$个节点，括号序列中'('比')'多$k$个（必须保证$k>0$）。

最后答案即为$dp[2*n][len][0]$。

为了防止在填的过程中已经到达终点却又回到之前的点，强制令终点加'('和')'之后到达的点都是终点。

时间复杂度$O(n^3)$。

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=205;
const int mod=1e9+7;
int n,len,ot[2][N];
int a[N],fail[N],dp[N][N][N];
char s[N];

void inc(int &x,int y)
{
	x+=y;
	if(x>=mod) x-=mod;
}

void init()
{
	scanf("%d",&n);int i;
	scanf("%s",s+1);
	len=strlen(s+1);
	for(i=1;i<=len;++i) a[i]=(s[i]==')');
}

void prework()
{
	int las=0,i;
	for(i=2;i<=len;++i)
	{
		while(las&&a[las+1]!=a[i]) las=fail[las];
		if(a[las+1]==a[i]) fail[i]=++las; 
	}
	
	ot[a[1]][0]=1;
	for(i=1;i<len;++i)
	{
		ot[a[i+1]][i]=i+1;
		int nw=fail[i];
		while(nw&&a[nw+1]==a[i+1]) nw=fail[nw];
		if(a[nw+1]!=a[i+1]) ot[a[nw+1]][i]=nw+1;
	}
	ot[0][len]=ot[1][len]=len;
}

void DP()
{
	int i,j,k;dp[0][0][0]=1;
	for(i=0;i<2*n;++i)
		for(j=0;j<=len;++j)
			for(k=0;k<=n;++k)
			{
				int gg=dp[i][j][k];
				if(!gg) continue;
				if(k+1<=n) inc(dp[i+1][ot[0][j]][k+1],gg);
				if(k) inc(dp[i+1][ot[1][j]][k-1],gg);
			}
	
	printf("%d\n",dp[2*n][len][0]);
}

int main()
{
	init();prework();DP();
	return 0;
}

```

---

