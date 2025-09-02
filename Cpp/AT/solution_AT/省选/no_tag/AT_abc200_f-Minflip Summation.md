# Minflip Summation

## 题目描述

我们有一个字符串 $S$，由 `0`，`1` 和 `?` 组成，$T$ 为 $S$ 重复 $K$ 次的结果。

如果我们把 $T$ 中每个 `?` 都替换成 `0` 或 `1`，我们就能够得到 $2^{Kq}$ 种不同的字符串，其中 $q$ 是 $S$ 中 `?` 的数量。对于每个由如下规则生成的字符串，解决如下问题，把答案求和并模 $10^9+7$：

> 设 $T'$ 为把 $T$ 中所有 `?` 替换为 `0` 或 `1` 得到的字符串。我们会重复执行如下操作，直到 $T$ 中所有元素均相同。最少需要多少次操作？
>
> - 选择两个整数 $l,r$ 满足 $1 \le l \le r \le |T'|$，把 $S$ 的第 $l$ 个到第 $r$ 个字符取反。取反的意思是，`0` 变为 `1`，反之亦然。

## 说明/提示

数据范围：$1 \le |S| \le 10^5$，$1 \le K \le 10^9$。

## 样例 #1

### 输入

```
101
2```

### 输出

```
2```

## 样例 #2

### 输入

```
?0?
1```

### 输出

```
3```

## 样例 #3

### 输入

```
10111?10??1101??1?00?1?01??00010?0?1??
998244353```

### 输出

```
235562598```

# 题解

## 作者：0x3F (赞：8)

不是，为啥这题题解这么复杂。

将答案除以 $2^{Kq}$，则为将 $\texttt{?}$ 随机确定为 $\texttt{01}$ 时答案的期望。

我们考虑对于一个确定的字符串如何计算答案。

将原串 $T$ 首尾相接，并且差分，则每次操作相当于选择两个位置取反。（除了对于整个字符串的操作以外，这个操作没有任何用处）

当新串中所有位置都为 $\texttt{0}$ 时，说明原串中所有位置都为 $\texttt{0}$ 或都为 $\texttt{1}$，即达到了要求。

显然，每次将两个 $\texttt{1}$ 变为 $\texttt{0}$ 是最优的，因此答案为新串中的 $\texttt{1}$ 的数量除以 $2$。（不需要取整，因为 $\texttt{1}$ 的数量一定为偶数）

根据期望的线性性，我们直接拆贡献。如果原串中相邻两个字符中有 $\texttt{?}$，则字符不同的概率为 $\frac{1}{2}$，对答案的贡献为 $\frac{1}{4}$，否则，如果字符相同，贡献为 $0$，否则贡献为 $\frac{1}{2}$。

这个直接计算 $S$ 的答案然后乘以 $K$ 就可以了。最后还要乘以方案数 $2^{Kq}$。

但是，直接交上去会 $\texttt{WA}$ 一个点。我们发现 $S=\texttt{?},K=1$ 时按照上述方法会计算出 $\frac{1}{2}$，而答案应该是 $0$。

为什么呢？我们发现与 $\texttt{?}$ 相邻的是它本身，不是独立随机变量，只能取 $(\texttt{0},\texttt{0})$ 和 $(\texttt{1},\texttt{1})$，不能取 $(\texttt{0},\texttt{1})$ 或 $(\texttt{1},\texttt{0})$，对答案的贡献是 $0$ 而不是 $\frac{1}{4}$。容易证明对于其他的 $S$ 和 $K$ 不存在上述问题，因此特判即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
inline int qpow(int a, long long b) {
    int s = 1;
    while (b) {
        if (b & 1LL) s = (long long) s * a % mod;
        a = (long long) a * a % mod;
        (b >>= 1);
    }
    return s;
}
int main() {
    string s;
    int k;
    cin >> s >> k;
    if (s == "?" && k == 1) {
        cout << 0 << endl;
    } else {
        int n = s.length();
        int q = 0;
        for (int i = 0; i <= n - 1; i++) {
            if (s[i] == '?') q++;
        }
        int ans = 0;
        for (int i = 0; i <= n - 2; i++) {
            if (s[i] == '?' || s[i+1] == '?') {
                ans = (ans + 250000002) % mod;
            } else if (s[i] != s[i+1]) {
                ans = (ans + 500000004) % mod;
            }
        }
        if (s[0] == '?' || s[n-1] == '?') {
            ans = (ans + 250000002) % mod;
        } else if (s[0] != s[n-1]) {
            ans = (ans + 500000004) % mod;
        }
        ans = (long long) ans * k % mod;
        ans = (long long) ans * qpow(2, (long long) k * q) % mod;
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：EuphoricStar (赞：8)

显然的策略：选择全部 $0$ 段变成 $1$，或选择全部 $1$ 段变成 $0$。

归纳可得一般性的结论：设字符串中 $s_i \ne s_{i+1}$ 的位置数为 $k$，答案为 $\left\lceil\frac{k}{2}\right\rceil$。

因为在模意义下不能上取整，考虑记 $k$ 的奇偶性（这样统计答案的时候就知道答案是 $\frac{k}{2}$ 还是 $\frac{k+1}{2}$），然后 dp。设 $f_{i,0/1,0/1}$ 为前 $i$ 个字符中，$k$ 的奇偶性，$s_i$ 填的数，$k$ 的总和。类似地设 $g_{i,0/1,0/1}$ 表示方案数。转移是 trivial 的。

因为 $K \le 10^9$，考虑把转移写成 $8 \times 8$ 的矩阵乘法形式，预处理第一个 copy 的 dp 值，做一遍矩阵快速幂就行。

时间复杂度 $O(8^3 (n + \log K))$。

[code](https://atcoder.jp/contests/abc200/submissions/41472734)

---

## 作者：Clover_BY (赞：7)

# [ABC200F  Minflip Summation](https://www.luogu.com.cn/problem/AT_abc200_f)
几天前 VP 了这场 ABC 并给后四道题贡了[翻译](https://www.luogu.com.cn/paste/u6wq1sma)。如您发现翻译中有瑕疵或有理解障碍，欢迎私信我或管理获得准确意思并修改。  
所以题意就不再放了。

## 题目分析  
我们把 `0` 和 `1` 看成颜色。  
首先不管是手模样例还是理性推导都能发现一个关键结论：对于一个字符串 $S$，将其颜色统一所需的最小操作数即为颜色段的个数除以 $2$ 下取整。设不同颜色段的边界数为 $b$，上面的结果同样可以用 $\lceil \frac{b}{2} \rceil$ 来表示。

基于颜色段的数量感性证明一下：可以考虑每次选取处于当前未处理串的左右两个端点，将其翻转后颜色段数会减少 $2$。这与每逢一个颜色段就做一次翻转操作是同一个效果。
```
10000110000110000001   颜色段数为 7
11111001111001111111   翻转 [2, 19]
11111110000111111111   翻转 [6, 13]
11111111111111111111   翻转 [8, 11]
```
相对于颜色段数，边界数更容易讨论。故我们之后只讨论颜色段边界相关内容。  
上取整的问题留到最后。（虽然貌似留着这个问题后患很大）

先来考虑问号如何处理。由于题目中要求我们求出所有可能的串的和，我们可以仿照计算期望的方式，将 `?` 的贡献设置好，求出单个串的贡献后乘以 $2^{Kq}$ 统一计算。  
为了方便，接下来的计算中 $\frac {1}{2}$ 均使用 $2$ 在模 $10 ^ 9 + 7$ 意义下的逆元 $inv$ 代替。

此时颜色段边界数已经可以轻松算出。考虑前后两个字符，记 $calc(S_i,S_j)$ 表示这两个位置的字符对边界数做出的贡献：

$$
calc(S_i, S_j) = \begin{cases}
  1 & S_i = S_j \\
  0 & S_i \not= S_j \\
  inv & S_i = \space \texttt? \space \lor \space S_j = \space \texttt?
\end{cases}
$$
（为了清晰和美观改成了上面的样子。第三种情况中，由于 `?` 即可填 `0` 又可填 `1`，因此只要左右至少有一个字符为 `?`，其都会对结果做出 $\frac{1}{2}$ 的贡献。）

然后再考虑如何计算拼接起来的 $T$ 的总贡献。  
记 $n=|S|$。  
显然每个 $S$ 内的贡献相同，但相邻两个 $S$ 之间需要处理。这等价于累加 $(K-1) \cdot calc(S_1,S_n)$ 到贡献之中。

于是我们统计出了所有边界的个数。现在我们争取干掉那个上取整。  
只需要让偶数不变，奇数变为偶数，就可以直接乘上逆元而不用担心这个问题了。  
那如何只对边界数为奇数的情况增加贡献呢？  
考虑下面两个串：
```
101010  b = 5
1010101 b = 4
```
第一个串边界数为奇数，首尾颜色不同；  
第二个边界数为偶数，首尾颜色相同。  
根据“只有首尾颜色不同的串边界数为奇数”这个性质，可以直接在最终贡献中再累加上 $calc(S_1, S_n)$，于是我们的目的就达到了。

同时，这样操作还有一个好处：注意到 $calc(S_1, S_n)$ 最终同样也被计算了 $K$ 次，可以与 $S$ 内部的贡献统一计算。  
故最后的答案为 $inv \cdot 2^{Kq} \cdot K \cdot \displaystyle \sum_{i=1}^{n} calc(S_i, S_{i\%n+1})$。  

另外，使用此种解法需注意对 $|S| = 1$ 的特判。

最后下取整处的转化参考了[这篇题解](https://atcoder.jp/contests/abc200/editorial/1248)的思路。

## Code
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

inline int read()
{
	int x = 0; char c;
	while(!isdigit(c = getchar()));
	do{
		x = (x << 1) + (x << 3) + (c ^ 48);
	}while(isdigit(c = getchar()));
	return x;
}

int top = 0, stk[20];
inline void write(int x)
{
	do{
		stk[++top] = x % 10;
		x /= 10;
	}while(x);
	for(register int i = top; i; --i)
		putchar(stk[i] | 48);
	putchar('\n'); top = 0;
	return ;
}

char s[100010];
const int mod = 1e9 + 7;
const int inv = 5e8 + 4;
int n, k, q, ans = 0;

inline int qpow(int a, long long b)
{
	int res = 1;
	for(register long long i = b; i; i >>= 1)
	{
		if(i & 1) res = (long long)res * a % mod;
		a = (long long)a * a % mod;
	}
	return res;
}

inline int calc(int i, int j)
{
	if(s[i] == '?' || s[j] == '?') return inv;
	return s[i] != s[j];
}

int main()
{
	scanf("%s", s + 1);
	k = read(); n = strlen(s + 1);
	if(n == 1 && (k == 1 || s[1] != '?')) return write(0), 0;
	for(register int i = 1; i <= n; ++i)
		q += s[i] == '?';
	q = (long long)qpow(2, (long long)k * q) * k % mod;
	for(register int i = 1; i < n; ++i)
		ans = (long long)(ans + calc(i, i + 1)) % mod;
	ans = (long long)(ans + calc(1, n)) % mod;
	write((long long)ans * q % mod * inv % mod);
	return 0;
}
```

---

## 作者：Semorius (赞：5)

## 题意简述：

给定一个字符串 $S$ ($ 1\ \le\ |S|\ \le\ 10^5 $)， $S$ 仅包含 $0$ , $1$ , $?$。将该字符串复制 $K$ ($ 1\ \le\ |K|\ \le\ 10^9 $) 遍，得到字符串 $S'$，$S'$ 中的 $?$ 可随意替换成 $0$ 或 $1$，对于 $S'$ 可能得到的每一种情况，求解子问题：

>给定 $01$ 串，每次操作可任选一个区间并对其进行 $01$ 反转（$0$ 变 $1$,$1$ 变 $0$），问把该 $01$ 串所有元素均变为 $0$ 或 $1$ 的最小操作次数。

输出子问题答案和。

## Hint：

首先考虑 $K=1$，且字符串中没有 $?$ 的情况，也就是先考虑子问题。

考虑操作策略，由于最终目标是把所有元素均变为 $0$ 或 $1$，所以一次操作应尽量减少 $01$ 段的数量。如果每次操作的区间包含的并不都是 $0$ 或 $1$ 的整段，比如：

>01101100

>操作区间：$[3, 7]$

>01010010

那么操作完成后 $01$ 段的数量会变多，所以操作区间覆盖的一定是完整的 $01$ 段。然后我们发现每次这样的操作最多能减少 $2$ 个 $01$ 段，设初始共有 $\text{x}$ 个 $01$ 段，那么最少操作次数为 $\left \lfloor \frac{x}{2}  \right \rfloor$。

## Solution：

然后考虑如果 $K=1$，且字符串中有 $?$ 的情况。

显然这个问题可以通过 $\text{dp}$ 求解。设 $dp_{i,0/1,0/1}$ 表示考虑到第 $i$ 个位置，第 $1$ 个位置为 $0/1$，第 $i$ 个位置为 $0/1$ 的**总答案**。设 $cnt_i$ 表示确定第 $1$ 个和第 $i$ 个位置后，下标小于等于 $i$ 的前缀字符串的合法数量。得到如下转移：

$$
\begin{aligned}
&dp_{i,0,0}=dp_{i-1,0,0}+dp_{i-1,0,1}\\
&dp_{i,0,1}=dp_{i-1,0,0}+dp_{i-1,0,1}+cnt_{i-1}\times [S_{1}\ne 1]\times [S_{i-1}\ne 1]\\
&dp_{i,1,0}=dp_{i-1,1,1}+dp_{i-1,1,0}+cnt_{i-1}\times [S_{1}\ne 0]\times [S_{i-1}\ne 0]\\
&dp_{i,1,1}=dp_{i-1,1,1}+dp_{i-1,1,0}\\
\end{aligned}
$$

注意如果 $dp_{i,j,k}$ 不合法，那么 $dp_{i,j,k}=0$。

最后考虑 $K\ne1$ 的情况，考虑使用矩阵乘法优化上面的 $\text{dp}$，时间复杂度为 $O(5^3\cdot(n + \log K))$。

最后的最后，当 $|S|=1$ 时要特判。 

---

## 作者：yangshengyu0719 (赞：3)

# 前言
本人在这里分享一种倍增做法，虽然比起其他几位大佬的简单做法要劣一些，但好在不用推麻烦的式子。
# 分析
对于一个 01 串，显然最优反转次数为 **0 段个数与 1 段个数的较小值**。

具体来讲，我们将 0 开头 0 结尾的串全变为 0 代价较小，0 开头 1 结尾的串全变为 0 或 1 代价相同，1 开头 0 结尾的串全变为 0 或 1 代价相同，1 开头 1 结尾的串全变为 1 代价较小。

由此我们可以设计朴素 DP 状态 $$f_{i,j,k}$$，其中 $$i$$ 表示前 $$i$$ 位的 01 串以 $$j$$ 开头以 $$k$$ 结尾的所有代价总和。状态转移比较简单，读者可以根据上一段的分类讨论自己分析一下，这里不再细说。至此，我们已经解决了原串的代价和。

然后我们发现，每次复制一倍时，代价和转移方式相似，于是我们考虑倍增原串的 DP 结果。现在我们可以重新定义 $$f_{i,j,k}$$ 为原串复制 $$2^i$$ 次时以 $$j$$ 开头以 $$k$$ 结尾的代价和。再定义一个辅助数组 $$g_{i,j,k}$$ 为原串复制 $$2^i$$ 次时以 $$j$$ 开头以 $$k$$ 结尾的方案数。

然后手模一下发现，原串倍增时一般情况为：
$$ f_{i,j,k} = \sum_{x=0}^1 \sum_{y=0}^1 f_{{i-1},j,x} \times g_{{i-1},y,k} + f_{{i-1},y,k} \times g_{{i-1},j,x} $$ 
$$ g_{i,j,k} = \sum_{x=0}^1 \sum_{y=0}^1 g_{{i-1},y,k} \times g_{{i-1},j,x} $$ 
特殊情况为，$$j=k$$ 且 $$x \ne j$$，$$y \ne k$$ 和 $$j \ne k$$ 且 $$x=j$$，$$y=k$$ 的情况，即**子区间最优并非总区间最优**的情况。然而我们发现，无论是前者还是后者，无论改变左子区间还是右子区间，**每一种具体方案的代价都只会增减 1**，故直接加减总方案数即可（代码 19 至 20 行）。

当然我们又发现原串单个的代价和也可以用这种方式，不必再单独写原本的朴素写法了，直接暴力递推一遍。
接下就直接倍增。至此我们就可以解决这道 CF 早期紫题了。

# Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,mod=1e9+7;
string s;
int n,K;
struct DP{
	int f[2][2],g[2][2];
}a[35],base[5],Ans;
DP Calc(DP x,DP y){
	DP res;
	memset(res.f,0,sizeof res.f);
	memset(res.g,0,sizeof res.g);
	for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
		for(int k=0;k<=1;k++) for(int l=0;l<=1;l++){
			res.g[i][j]=(res.g[i][j]+x.g[i][k]*y.g[l][j]%mod)%mod;
			res.f[i][j]=(res.f[i][j]+x.f[i][k]*y.g[l][j]%mod+x.g[i][k]*y.f[l][j]%mod)%mod;
		}
		if(i==j) res.f[i][j]=(res.f[i][j]-x.g[i][i^1]*y.g[j^1][j]%mod+mod)%mod;
		else res.f[i][j]=(res.f[i][j]+x.g[i][i]*y.g[j][j]%mod)%mod;
	}
	return res;
}
int Sum(DP x){
	int sum=0;
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			sum=(sum+x.f[i][j])%mod;
	return sum;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>s>>K;
	n=s.size();s=" "+s;
	base[0].g[0][0]=base[1].g[1][1]=1;
	base[2].g[0][0]=base[2].g[1][1]=1;
	if(s[1]=='?') a[0]=base[2];
	else a[0]=base[s[1]-'0'];
	for(int i=2;i<=n;i++){
		if(s[i]=='?') a[0]=Calc(a[0],base[2]);
		else a[0]=Calc(a[0],base[s[i]-'0']);
	}
	for(int i=1;i<=30;i++)
		a[i]=Calc(a[i-1],a[i-1]);
	int now=0,flag=0;
	for(int i=30;i>=0;i--)
		if(now+(1<<i)<=K){
			if(!flag) Ans=a[i],flag=1;
			else Ans=Calc(Ans,a[i]);
			now+=(1<<i);
		}
	cout<<Sum(Ans);
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

容易想到总和转期望。

显然方案就是 $A_i\not =A_{i+1}$ 的数量除以 $2$ 向下取整，取整是让人讨厌的，想个办法处理一下。

不难发现这个数量是奇数当且仅当首尾颜色不同，所以我们想到加上首尾差异的贡献，用隔壁题解的话来说就是，“首尾相连之后差分”。

现在我们考虑复制 $k$ 次的贡献，首先我们不考虑首尾这一部分，剩下的部分可以直接乘上 $k$。

对于首尾差异的部分，首先我们在串与串之间统计了 $k-1$ 次，最终我们还要像上面说的那样统计一遍首尾贡献，所以首尾也是贡献直接乘上 $k$。

于是我们发现一个很有意思的现象，多个串的期望直接由单个串的期望乘上 $k$ 就行。

注意特判 $S=\text{？}$ 且 $k=1$ 的情况。

最后乘上总方案数来还原就行。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL Mod=1e9+7;
const LL I2=(Mod+1)/2,I4=(Mod+1)/4;
const int N=1e5+5;
char C[N];
int n,k;
inline LL Ksm(LL x,LL y)
{
	LL A=1;
	while(y)
	{
		if(y&1)A=A*x%Mod;
		x=x*x%Mod,y>>=1;
	}
	return A;
}
int main()
{
	scanf("%s",C+1);n=strlen(C+1);
	scanf("%d",&k);
	if(C[1]=='?'&&k==1&&n==1)return puts("0"),0;
	LL m=0,Ans=0;
	for(int i=1;i<=n;i++)m+=C[i]=='?';
	for(int i=1;i<=n-1;i++)
	{
		if(C[i]=='?'||C[i+1]=='?')(Ans+=I4)%=Mod;
		else if(C[i]!=C[i+1])(Ans+=I2)%=Mod;
	}
	if(C[1]=='?'||C[n]=='?')(Ans+=I4)%=Mod;
	else if(C[1]!=C[n])(Ans+=I2)%=Mod;
	Ans=Ans*k%Mod;
	Ans=Ans*Ksm(2,m*k)%Mod;
	printf("%lld\n",Ans);
}
```

---

