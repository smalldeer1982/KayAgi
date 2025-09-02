# Balance

## 题目描述

1. 选择两个相邻字符，将第一个字符替换成第二个。 
2. 选择两个相邻字符，将第二个字符替换成第一个。 这样，通过任意多次的操作，可以得到许多不同的串，为了追求字符的平衡， 我们要求a,b,c三种字符在字符串中出现的次数两两之差都不能大于1。

你的任 务是，统计给定字符串通过任意多次的操作，能够得到的不同的平衡串的个数。

## 样例 #1

### 输入

```
4
abca
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4
abbc
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
ab
```

### 输出

```
1
```

# 题解

## 作者：_fairytale_ (赞：6)

看完一圈题解没看懂，于是跑去 CF 看官方题解，有了一些理解，所以自己写一篇。

记给定的字符串为 $A$，用题目中的操作生成的字符串为 $B$。

我们考虑一种“压缩”操作，把 $A,B$ 中所有相邻的相同字母缩成一个，得到 $A',B'$，比如 $\text{aaabcc}$ 就会缩成 $\text{abc}$。

可以发现，$B'$ 一定是 $A'$ 的子序列。

因此我们其实可以只关心 $A'$，只考虑 $A'$ 合法的子序列，同时生成合法的 $B$ 串。

考虑 DP，设 $f_{i,cnta,cntb,cntc}$ 表示考虑了 $A'$ 的前 $i$ 个字符，生成的 $B$ 中 $\text{a}$ 有 $cnta$ 个，$\text{b}$ 有 $cntb$ 个，$\text{c}$ 有 $cntc$ 个的方案数。

其实我们是在 $A'$ 的子序列自动机上 DP，但是在这里你不需要掌握任何子序列自动机的知识，只需要知道，合法的转移有三种：

以下记 $next_{i,letter}$ 表示最小的一个 $j$，满足 $j\ge i$ 且 $A'_j=letter$，同时假设 $A_i'=\text{a}$。

1. 再复制一个 $\text{a}$ 添加到 $B$ 的末尾，即 $f_{i,cnta,cntb,cntc}\to f_{i,cnta+1,cntb,cntc}$。

2. 跳到下一个字符 $\text{b}$，把 $\text{b}$ 添加到 $B$ 的末尾，即 $f_{i,cnta,cntb,cntc}\to f_{next_{i,b},cnta,cntb+1,cntc}$。

3. 跳到下一个字符 $\text{c}$，把 $\text{c}$ 添加到 $B$ 的末尾，即 $f_{i,cnta,cntb,cntc}\to f_{next_{i,c},cnta,cntb,cntc+1}$。

不难发现这样跳过的路径一定是 $A'$ 的子序列，而且可以生成所有合法的 $B$。

```cpp
#include<bits/stdc++.h>
#define rep(x,qwq,qaq) for(int (x)=(qwq);(x)<=(qaq);++(x))
#define per(x,qwq,qaq) for(int (x)=(qwq);(x)>=(qaq);--(x))
using namespace std;
#define maxn 155
#define mod 51123987
int n,m,k;
int a[maxn];
string s;
char A[maxn];
void add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
int ans;
int f[maxn][55][55][55];
int nxt[maxn][4];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>s;
	s=" "+s;
	rep(i,1,n){
		while(i<=n-1&&s[i+1]==s[i])++i;
		A[++m]=s[i];
	}
	nxt[m+1][0]=nxt[m+1][1]=nxt[m+1][2]=m+1;
	A[0]='d';
	per(i,m,0){
		nxt[i][0]=nxt[i+1][0];
		nxt[i][1]=nxt[i+1][1];
		nxt[i][2]=nxt[i+1][2];
		nxt[i][A[i]-'a']=i;		
	}
	f[0][0][0][0]=1;
	rep(i,0,m){
		int Lima=n/3+1;
		rep(cnta,0,Lima){
			int Limb=min(n-cnta,n/3+1);
			rep(cntb,0,Limb){
				int Limc=min(n-cnta-cntb,n/3+1);
				rep(cntc,0,Limc){
					if(cnta+cntb+cntc==n&&abs(cnta-cntb)<=1&&abs(cntb-cntc)<=1&&abs(cnta-cntc)<=1)add(ans,f[i][cnta][cntb][cntc]);
					add(f[nxt[i][0]][cnta+1][cntb][cntc],f[i][cnta][cntb][cntc]);
					add(f[nxt[i][1]][cnta][cntb+1][cntc],f[i][cnta][cntb][cntc]);
					add(f[nxt[i][2]][cnta][cntb][cntc+1],f[i][cnta][cntb][cntc]);
				}
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：ylxmf2005 (赞：6)

### Description

给定一个由 `a b c` 构成的字符串 $S$，可以选择任意两个相邻字符，用第一个覆盖第二个或用第二个覆盖第一个。求能变出多少不同的字符串，`a b c` 的个数两两差 $\leq 1$，对 $51123987$ 取模。

$1 \leq |S| \leq 150$。

### Solution

序列自动机 + dp。

等价于从 $S$ 中选出一个子序列，把每个元素复制几次得到 $T$。设状态为 $f_{i,a,b,c}$ 表示当前选到了 $i$，此时 $T$ 中 `a b c` 出现的次数为 $a ,\ b ,\ c$ 时，有多少个不同的 $T$。

令 $nxt_{i,c}$ 为 $c$ 在 $i$ 及 $i$ 之后第一次出现的位置，$0 \ 1 \ 2$ 分别代表 `a b c`。转移如下


$$f_{1,0,0,0} = 1$$

$$f_{nxt_{i,0}, a + 1, b, c} = f_{nxt_{i,0}, a + 1, b, c} + f_{i,a,b,c}$$

$$f_{nxt_{i,1}, a, b + 1, c} = f_{nxt_{i,1}, a, b + 1, c} + f_{i,a,b,c}$$

$$f_{nxt_{i,2}, a, b, c + 1} = f_{nxt_{i,2}, a, b, c  + 1} + f_{i,a,b,c}$$

解释一下，如果 $S_i =$ `a` 那么 $f_{i,a,b,c}$ 会转移到 $f_{i,a+1,b,c}$，再转移到 $f_{i,a+2,b,c}$，相当于 $S_i$ 在进行复制。那么 $f_{i,a,b,c}$ 应该如何向 $i$ 后面的字母转移呢？假设下一个进行复制的字母是 `b`。首先你的 `b` 只能来源于 $i$ 后面的字母，如果来源于 $i$ 前面的字母，那么你就不可能选 `a`。其次，我们要保证不会算重，如果同时向 $i$ 后面的所有 `b` 进行转移，比如 $S=$ `abb` 那么可以选第二个 `b` 进行一次复制，也可以选第三个 `b` 进行一次复制。这样得到的是相同的 $T$，但是答案会算两次。所以转移到 $nxt_{i,1}$ 就可以了。

还有一个需要思考的地方，比如 $S=$ `aba`，我们选第一个 `a` 进行复制，和不选第一个 `a` 而是选第三个 `a` 进行复制，都可以得到 $T=$ `aaa`。所以我们要钦定只有第一个 `a` 才可以直接在空串的基础上进行复制，且第一个 `a` 不能直接转移到第三个 `a`。

枚举 $i ,\ a ,\ b ,\ c$。如果有 $a + b + c = n $ 且 $|a-b|, \ |a - c|, \ |b-c| \leq1$，那么将 $f_{i,a,b,c}$ 计入答案。

因为每个字符出现的次数不会超过 $\frac{n + 2}{3}$，所以时空复杂度为 $O(\frac{n^4}{27})$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 150 + 5, p = 51123987;
char s[N];
int f[N][(N + 2) / 3][(N + 2) / 3][(N + 2) / 3], nxt[N][3], n, ans;
int main() {
    scanf("%d%s", &n, s + 1);
    nxt[n + 1][0] = nxt[n + 1][1] = nxt[n + 1][2] = n + 1;
    for(int i = n; i >= 1; i--) {
        nxt[i][0] = nxt[i + 1][0];
        nxt[i][1] = nxt[i + 1][1];
        nxt[i][2] = nxt[i + 1][2];
        if(s[i] == 'a') nxt[i][0] = i;
        if(s[i] == 'b') nxt[i][1] = i;
        if(s[i] == 'c') nxt[i][2] = i;
    }
    f[1][0][0][0] = 1;
    for(int i = 1; i <= n; i++)
        for(int a = 0; a <= (n + 2) / 3; a++)
            for(int b = 0; b <= (n + 2) / 3; b++)
                for(int c = 0; c <= (n + 2) / 3; c++)
                {
                    if(a + b + c == n && abs(a - b) <= 1 && abs(a - c) <= 1 && abs(b - c) <= 1) 
                    	ans = (ans + f[i][a][b][c]) % p; 
                    f[nxt[i][0]][a + 1][b][c] = (f[nxt[i][0]][a + 1][b][c] + f[i][a][b][c]) % p;
                    f[nxt[i][1]][a][b + 1][c] = (f[nxt[i][1]][a][b + 1][c] + f[i][a][b][c]) % p;
                    f[nxt[i][2]][a][b][c + 1] = (f[nxt[i][2]][a][b][c + 1] + f[i][a][b][c]) % p;
                }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：帅到报警 (赞：2)

### 【题意描述】
ge 出一个字符串，只由 a , b , c 组成。我们可以将某个字符的左边或者右边的字符变为他，但是 3 个字符数量差不能超过 k 个。然后求出这样多次操作之后可以得到的字符串种类数。
### 【分析】
本来我以为这道题是用组合来做的。（~~这难道真的不是组合题？？？~~）结果就。。。就做不出来了(|||ﾟдﾟ)

那么我来说一波正解。看了看 codeforces 的标签， 这竟然是一道 dp 题。。（黑人问号？？？）那么经过了一波对题解的观摩，我们可以定义 dp[ i ][ a ][ b ][ c ]为第 i 个字符做出了 a 个 a，b 个 b，c 个 c 的方案数。因为此题的范围只有 n <= 150，那么每一个字符出现次数只有 50 次左右,所以 1 维枚举位置，3 维枚举 3 个字符的出现次数并不会超时。

然后我们再仔细分析一下改变的方式，我们可以发现一些规律：
	
    对于一段字符串譬如 abbbaaaac，不管怎么变，
    只要 b 的后面还存在 a，都不能将 c 的位置
    变幻到 b 与 a 的中间。

利用这个规律，我们可以预处理好每一个 a,b,c 所对应的下一个 a,b,c 的位置，**因为我们可以确定每一个字符的数量，那么无论有多少个位置，其和都是不变的**。

### 【核心代码】
1、预处理，注意最后一个点的下一个位置要设置到 n + 1，这样在每次判断下一个字符的位置的时候就可以处理好边界了。
```cpp
nxt[n + 1][0] = nxt[n + 1][1] = nxt[n + 1][2] = n + 1;
for(int i = n; i >= 1; i--)
{
	nxt[i][0] = nxt[i + 1][0];
	nxt[i][1] = nxt[i + 1][1];
	nxt[i][2] = nxt[i + 1][2];
	if(s[i] == 'a')
		nxt[i][0] = i;
	if(s[i] == 'b')
		nxt[i][1] = i;
	if(s[i] == 'c')
		nxt[i][2] = i;
}
```
2、 dp 过程（记得一定要%%%）
```cpp
for(int i = 1; i <= n; i++)
	for(int a = 0; a <= lim; a++)
		for(int b = 0; b <= lim; b++)
			for(int c = 0; c <= lim; c++)
			{
				if(a + b + c == n && Abs(a - b) <= 1 && Abs(a - c) <= 1 && Abs(b - c) <= 1)//当枚举到总和为 n 的时候判断答案
				{
					(ans += dp[i][a][b][c]) %= MOD;
					continue;
				}
				if(nxt[i][0] <= n)
					(dp[nxt[i][0]][a + 1][b][c] += dp[i][a][b][c]) %= MOD;
				if(nxt[i][1] <= n)
					(dp[nxt[i][1]][a][b + 1][c] += dp[i][a][b][c]) %= MOD;
				if(nxt[i][2] <= n)
					(dp[nxt[i][2]][a][b][c + 1] += dp[i][a][b][c]) %= MOD;
			}
```

### 【正解】
```cpp
#include <bits/stdc++.h>
using namespace std;

char s[155];
int nxt[151][3];
int n, lim, ans;
int dp[155][55][55][55];
const int MOD = 51123987;

inline int Abs(int x)
{
	return x > 0 ? x : -x;
}

int main()
{
  	freopen("balance.in", "r", stdin);
  	freopen("balance.out", "w", stdout);
  	scanf("%d", &n);
  	scanf("%s", s + 1);
  	nxt[n + 1][0] = nxt[n + 1][1] = nxt[n + 1][2] = n + 1;
	for(int i = n; i >= 1; i--)
	{
		nxt[i][0] = nxt[i + 1][0];
		nxt[i][1] = nxt[i + 1][1];
		nxt[i][2] = nxt[i + 1][2];
		if(s[i] == 'a')
			nxt[i][0] = i;
		if(s[i] == 'b')
			nxt[i][1] = i;
		if(s[i] == 'c')
			nxt[i][2] = i;
	}
	lim = (n + 2) / 3;
	dp[1][0][0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int a = 0; a <= lim; a++)
			for(int b = 0; b <= lim; b++)
				for(int c = 0; c <= lim; c++)
				{
					if(a + b + c == n && Abs(a - b) <= 1 && Abs(a - c) <= 1 && Abs(b - c) <= 1)
					{
						(ans += dp[i][a][b][c]) %= MOD;
						continue;
					}
					if(nxt[i][0] <= n)
						(dp[nxt[i][0]][a + 1][b][c] += dp[i][a][b][c]) %= MOD;
					if(nxt[i][1] <= n)
						(dp[nxt[i][1]][a][b + 1][c] += dp[i][a][b][c]) %= MOD;
					if(nxt[i][2] <= n)
						(dp[nxt[i][2]][a][b][c + 1] += dp[i][a][b][c]) %= MOD;
				}
	printf("%d", ans);
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

好题。

考虑一段操作的本质是将一段连续的字母进行拓展。最终的一段字母可以由一个字母得来。

问题转化为从原串选出若干个字母，能拓展出多少种序列。

令 $f_{i,a,b,c}$ 表示最后一个选第 $i$ 个字母，且还未拓展的方案数。

转移令 $nxt_{i,0/1/2}$ 表示 $i$ 后对应字符第一个出现的位置，从 $i$ 转移过去即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=155;
const int mod=51123987;
int n,ans;
char s[N];
int nxt[N][3];
int f[N][N/3+5][N/3+5][N/3+5];
int check(int a,int b,int c){
	return (a+b+c==n&&abs(a-b)<=1&&abs(b-c)<=1&&abs(a-c)<=1);
}
int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	nxt[n+1][0]=nxt[n+1][1]=nxt[n+1][2]=n+1;
	for(int i=n;i>=1;i--){
		nxt[i][0]=nxt[i+1][0];
		nxt[i][1]=nxt[i+1][1];
		nxt[i][2]=nxt[i+1][2];
		nxt[i][s[i]-'a']=i;
	}
	f[1][0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int a=0;a<=n/3+1;a++){
			for(int b=0;b<=min(n/3+1,n-a);b++){
				for(int c=0;c<=min(n/3+1,n-a-b);c++){
					if(check(a,b,c)) ans=(ans+f[i][a][b][c])%mod;
					f[nxt[i][0]][a+1][b][c]=(f[nxt[i][0]][a+1][b][c]+f[i][a][b][c])%mod;
					f[nxt[i][1]][a][b+1][c]=(f[nxt[i][1]][a][b+1][c]+f[i][a][b][c])%mod;
					f[nxt[i][2]][a][b][c+1]=(f[nxt[i][2]][a][b][c+1]+f[i][a][b][c])%mod; 
				}
			}
		}
	}
	printf("%d\n",ans);
    return 0;
}

```

---

## 作者：ademik (赞：1)

#### 分析:

我们发现，一个位置的字符可以被替换成其他字符，当且仅当它前方或者后方存在一个其他字符。

我们考虑从 $1$ 到 $n$ 递推，那么此时，我们只需要考虑其前方所有的字符即可(由于其后方的字符已经确定，而每次修改当前位置的字符会改变后方的字符)。

我们令 $f(i, a, b, c)$ 表示在位置 $i$，已经有了 $a$ 个 $\texttt{a}$，$b$ 个 $\texttt{b}$，$c$ 个 $\texttt{c}$ 的方案数。

令 $nxt(i, 0/1/2)$ 分别表示位置 $i$ 处的下一个 $\texttt{a}$ / $\texttt{b}$ / $\texttt{c}$ 所在的位置。

那么我们的转移方程即为：

$$\begin{cases} 
f(nxt(i, 0), a + 1, b, c) += f(i, a, b, c)\\
f(nxt(i, 1), a, b + 1, c) += f(i, a, b, c) \\
f(nxt(i, 2), a, b, c + 1) += f(i, a, b, c)
\end{cases}$$

关于这个方程的一些问题与解答：

+ 为何直接转移到 $nxt$ 而不是 $i + 1$？

> 我们修改字符是并不是直接修改，而是将当前位置到 $nxt$ 全部覆盖为 $nxt$ 位置的字符。如果转移到 $i + 1$ 的位置并且 $nxt$ 不变的话，那么它还可以再次计算覆盖 $i + 1$ 到 $nxt$ 的位置的方案数，如果第 $i$ 位置的字符与 $nxt$ 处的字符相同，那么这两次所得到的字符串完全相同。这样的话就会重复计算答案。

+ 既然是覆盖 $i$ 到 $nxt$ 的位置，为何计算字母个数时只加 $1$？

> 这就考虑到我们只遍历到了位置 $i$，而当我们遍历到 $i + 1$ 的位置时，这个位置的字符可能被再次修改，故而不用考虑。

我们最终所求答案即为：

$$\sum f(i, a, b, c) \times [a + b + c = n ][\text{abs}(a - b) \le 1][\text{abs}(b - c) \le 1][\text{abs}(a - c) \le 1]$$

时间复杂度为 $O(n)$。

#### Code:

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
const int N = 160, Mod = 51123987;
char ch[N]; 
int dp[N][55][55][55], n, nxt[N][3];
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >>n >>(ch + 1);
    nxt[n + 1][0] = nxt[n + 1][1] = nxt[n + 1][2] = n + 1;
    for(int i = n; i >= 1; i --) {
        nxt[i][0] = nxt[i + 1][0];
        nxt[i][1] = nxt[i + 1][1];
        nxt[i][2] = nxt[i + 1][2];
        nxt[i][ch[i] - 'a'] = i;
    }   
    dp[1][0][0][0] = 1; i64 ans = 0;
    for(int i = 1; i <= n; i ++) {
        for(int a = 0; a <= (n + 2) / 3; a ++) {
            for(int b = 0; b <= (n + 2) / 3; b ++) {
                for(int c = 0; c <= (n + 2) / 3; c ++) {
                    if(a + b + c == n && abs(a - b) <= 1 && abs(a - c) <= 1 && abs(b - c) <= 1) 
                    	(ans += dp[i][a][b][c]) %= Mod;
                    (dp[nxt[i][0]][a + 1][b][c] += dp[i][a][b][c]) %= Mod;
                    (dp[nxt[i][1]][a][b + 1][c] += dp[i][a][b][c]) %= Mod;
                    (dp[nxt[i][2]][a][b][c + 1] += dp[i][a][b][c]) %= Mod;
                }
            }
        }
    }
    cout <<ans <<endl;
    return 0;
} 
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2500}$
---
### 解题思路：

两种操作都是只能对相邻的数进行的，所以字母块与字母块之间的相对位置是不会变化的。而一开始数组中一个字母块到底长度多少并不被关心，直接缩成一个字母就行了。

然后考虑动态规划，设 $f_{i,a,b,c}$ 表示用前 $i$ 个位置进行拓展（注意不是拓展至第 $i$ 个位置），已经有了 $a$ 个 $a$，$b$ 个 $b$，$c$ 个 $c$ 的方案数。

然后每一次的转移一个尚未转移过的字母进行一次拓展（同一位置可以进行多次拓展），具体拓展的位置并不关心，只需要知道有一个新的和拓展位置的字母一样的字母出现即可。

但是这样转移会要求记录下所有的位置是否被拓展，复杂度过高，考虑贪心下一次的转移位置。分别记录下每一位置上 $a,b,c$ 下一个可拓展位置，然后直接进行拓展就行了，不妨记为 $nxt_{i,0/1/2}$（$0,1,2$ 分别表示 $a,b,c$）。

具体地，刷表法的转移的方程为：

$\begin{cases}
f_{nxt_{i,0},a+1,b,c}+=f_{i,a,b,c}\\
f_{nxt_{i,1},a,b+1,c}+=f_{i,a,b,c}\\
f_{nxt_{i,2},a,b,c+1}+=f_{i,a,b,c}
\end{cases}$

---
注意一定**不要**开 $\text{long long}$，会超出空间限制。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MOD=51123987;
int n,f[151][52][52][52],ans,nxt[205][5],now;
char c[205];
char get(){
	char c=getchar();
	while(c>'z'||c<'a')c=getchar();
	return c;
}
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++)c[i]=get();
	now=0;
	for(int i=1;i<=n;i++)
	if(c[i]!=c[i-1])c[++now]=c[i];
	for(int i=now;i>=1;i--){
		for(int l=0;l<=2;l++){
			nxt[i][l]=nxt[i+1][l];
			if(c[i]=='a'+l)nxt[i][l]=i;
		}
	}
	f[1][0][0][0]=1;
	for(int i=1;i<=now;i++)
	for(int a=0;a<=(n+2)/3;a++)
	for(int b=0;b<=(n+2)/3;b++)
	for(int c=0;c<=(n+2)/3;c++){
		if(a+b+c==n&&abs(a-b)<=1&&abs(b-c)<=1&&abs(a-c)<=1)
		ans=(ans+f[i][a][b][c])%MOD;
		f[nxt[i][0]][a+1][b][c]=(f[nxt[i][0]][a+1][b][c]+f[i][a][b][c])%MOD;
		f[nxt[i][1]][a][b+1][c]=(f[nxt[i][1]][a][b+1][c]+f[i][a][b][c])%MOD;
		f[nxt[i][2]][a][b][c+1]=(f[nxt[i][2]][a][b][c+1]+f[i][a][b][c])%MOD;
	}
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：OldDriverTree (赞：0)

# Solution

首先原问题看着很不直观，可以把题意转化为从 $S$ 中选择一个子序列，其中子序列中的每个元素都可以复制几次，要求复制完得到的字符串长度为 $n$，且满足三种字符在字符串中出现的次数两两之差都不能大于 $1$。

由于对于相同的子序列，是只会统计一次的，直接 $\text{DP}$ 显然会算重，考虑在子序列自动机上 $\text{DP}$，设 $f_{i,x,y,z}$ 表示选出来的子序列当前匹配到了 $i$ 这个位置，目前的子序列的元素复制后得到了 $x$ 个 $\text{a}$，$y$ 个 $\text{b}$，$z$ 个$\text{c}$ 的方案数。

对于转移，就是枚举子序列的下一个位置是什么字符。

令 $nxt_{i,0/1/2}$ 为 $i$ 后面第一个 $\text{a}/\text{b}/\text{c}$ 的位置（为了方便转移，这里的“后面”是包括 $i$ 本身的，这样将本身复制一个就可以直接用转移到 $nxt$ 了）。

状态转移方程就是：

$$
\begin{cases}
f_{i,x,y,z}\to f_{nxt_{i,0},x+1,y,z}\\
f_{i,x,y,z}\to f_{nxt_{i,1},x,y+1,z}\\
f_{i,x,y,z}\to f_{nxt_{i,2},x,y,z+1}\\
\end{cases}
$$

对于统计最后的答案，就枚举子序列最后匹配到了哪个位置，以及 $x,y,z$，如果 $\max\{x,y,z\}-\min\{x,y,z\}\le 1$ 就将 $f_{i,x,y,z}$ 加入答案。

时间复杂度 $O(n^4)$。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
const int N=152,mod=51123987;
int f[N][52][52][52];
int n,ans,nxt[N][3];
char s[N];

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
main()
{
	n=read(),scanf("%s",s+1);
	nxt[n+1][0]=nxt[n+1][1]=nxt[n+1][2]=n+1;
	for (int i=n;i;i--) {
		nxt[i][0]=nxt[i+1][0];
		nxt[i][1]=nxt[i+1][1];
		nxt[i][2]=nxt[i+1][2];
		nxt[i][s[i]-'a']=i;
	}
	f[1][0][0][0]=1;
	for (int i=1;i<=n;i++)
		for (int x=0;x<=(n+2)/3;x++)
			for (int y=0;y<=(n+2)/3;y++)
				for (int z=0;z<=(n+2)/3;z++) {
					if (x+y+z==n&&max({x,y,z})-min({x,y,z})<2) ans=(ans+f[i][x][y][z])%mod;
					f[nxt[i][0] ][x+1][y][z]=(f[nxt[i][0] ][x+1][y][z]+f[i][x][y][z])%mod;
					f[nxt[i][1] ][x][y+1][z]=(f[nxt[i][1] ][x][y+1][z]+f[i][x][y][z])%mod;
					f[nxt[i][2] ][x][y][z+1]=(f[nxt[i][2] ][x][y][z+1]+f[i][x][y][z])%mod;
				}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：天空即为极限 (赞：0)

手玩一下样例可以发现，如果一个字符没有被覆盖，那么它与之前的所有没被覆盖的字符的相对顺序是不变的。

例如原串为 `abcc`，则对于任意一个操作后的串例如 `aabc`，我们发现后面的 `c` 与 `a`，`b` 的相对顺序没变。（可以打个表观察）

我们还可以发现，若我们选择了一些原串的字符，将他们称为贡献数组，我们就可以把题目转化为把这些字符每个扩展为一段按顺序排列，要求每一段长度加起来为 $n$ 。例如原串 `abacbcac`，我们选了 `a c a` 作为贡献数组，我们就可以通过操作转化为 `aaacccaa` 或 `acccccca` 等。

结合第一个结论，我们可以发现一个事情，若我们选出来的字符存在相邻两个字符相同，那么这是重复的。例如选出来的贡献数组是 `a a b c`，那么他一定能被 `a b c` 给包含，这为我们提供了良好的去重方法，具体的，我们只要将当前的字符只能转移到后面第一个与其不同的字符即可。

于是，我们设计 $f_{i,a,b,c}$ 表示当前的第 $i$ 个字符选进了贡献数组，我们已经填了最后的串的前 $a+b+c$ 位，当前选的 `a b c` 数量分别为 $a, b, c$。

状态转移也很好推：

$$

f_{nxt_{i, 0},a+1,b,c} = f_{nxt_{i, 0},a+1,b,c} + f_{i,a,b,c}
\\
f_{nxt_{i, 1},a,b+1,c} = f_{nxt_{i, 1},a,b+1,c} + f_{i,a,b,c}
\\
f_{nxt_{i, 2},a,b,c+1} = f_{nxt_{i, 2},a,b,c+1} + f_{i,a,b,c}

$$

其中 $nxt_{i,0/1/2}$ 是之后第一个为 $a/b/c$ 的位置，需要注意的是，若当前字符为 $a$，则 $nxt_{i,0}=i$，这是为了保证之后转移到不同字符，且对于当前 $i$ 的字符组成最后一个字符段加入一个 `a`，其他字符同理。`a+1`，`b+1`，`c+1` 的目的是保证当前字符进了贡献数组（至少要填一个吧）。

答案就是：
$$
\sum\limits_{i=1}^{n} [a+b+c=n][|a-b|\le 1][|a-c|\le 1][|b-c|\le 1] f_{i,a,b,c}
$$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 51123987;

int f[155][55][55][55], nxt[155][3], a[155], g[3];

int main ( ) {
  int n; cin >> n;
  for ( int i = 1; i <= n; i ++ ) {
    char c; cin >> c;
    a[i] = c - 'a';
  }
  for ( int i = n; i >= 1; i -- ) {
    g[a[i]] = i;
    nxt[i][0] = g[0];
    nxt[i][1] = g[1];
    nxt[i][2] = g[2];
  }
  f[1][0][0][0] = 1; int ans = 0;
  for ( int i = 1; i <= n; i ++ ) {
    for ( int j = 0; j <= ( n + 2 ) / 3; j ++ ) 
      for ( int k = 0; k <= ( n + 2 ) / 3; k ++ )
        for ( int l = 0; l <= ( n + 2 ) / 3; l ++ ) {
          if ( j + k + l == n and abs ( j - k ) <= 1 and abs ( k - l ) <= 1 and abs ( j - l ) <= 1 ) 
            ans = ( ans + f[i][j][k][l] ) % mod;
          f[nxt[i][0]][j + 1][k][l] = ( f[nxt[i][0]][j + 1][k][l] + f[i][j][k][l] ) % mod;
          f[nxt[i][1]][j][k + 1][l] = ( f[nxt[i][1]][j][k + 1][l] + f[i][j][k][l] ) % mod;
          f[nxt[i][2]][j][k][l + 1] = ( f[nxt[i][2]][j][k][l + 1] + f[i][j][k][l] ) % mod;
        }
  }
  cout << ans << "\n";
}
```

---

## 作者：hgzxwzf (赞：0)

## 解题思路：
$0$ 代表 $\verb!a!$，$1$ 代表 $\verb!b!$，$2$ 代表 $\verb!c!$。

定义 $dp_{i,a,b,c}$ 表示 考虑到 $i$ 位置替换或被替换，有 $a$ 个 $0$，$b$ 个 $1$ 和 $c$ 个 $2$。

我们还需要求原串中从每个位置出发第一个 $0$ 或 $1$ 或 $2$，记为 $nex_{i,0},nex_{i,1},nex_{i,2}$。

转移方程（$1,2$ 同理）：
$dp_{nex_{i,0},a+1,b,c}=(dp_{nex_{i,0},a+1,b,c}+dp_{i,a,b,c})$。

将 $i$ 变为 $0$ 需要两步：先将 $i$ 后面的一个 $0$ 一路复制到 $i+1$，再从 $i+1$ 复制到 $i$，所以 $0$ 的个数加了 $1$。（$1$ 和 $2$ 同理）

之所以只向 $nex_{i,0}$ 转移，是因为 $nex_{i,0}$ 后面的 $0$ 一路复制到 $i+1$ 和从 $nex_{i,0}$ 一路复制到 $i+1$ 没有本质区别，这样做可以去重。

---

