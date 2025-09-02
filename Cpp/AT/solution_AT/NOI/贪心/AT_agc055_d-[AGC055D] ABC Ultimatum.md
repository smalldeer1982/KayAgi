# [AGC055D] ABC Ultimatum

## 题目描述

当且仅当一个长度为 $3N$ 的字符串 $T$，恰好包含 $N$ 个 `A`、$N$ 个 `B` 和 $N$ 个 `C`，并且存在一种将 $T$ 分解为 $N$ 个长度为 $3$ 的（不一定连续的）子序列的方法，使得每个子序列都是 `ABC`、`BCA` 或 `CAB` 之一时，我们称 $T$ 为**好字符串**。

现给定一个由 `A`、`B`、`C`、`?` 组成的长度为 $3N$ 的字符串 $S$。请你计算有多少种将每个 `?` 替换为 `A`、`B` 或 `C` 的方案，使得最终得到的字符串是好字符串。由于答案可能非常大，请输出答案对 $998244353$ 取模的结果。

## 说明/提示

### 限制条件

- $1 \leq N \leq 15$
- $S$ 是一个由 `A`、`B`、`C`、`?` 组成的长度为 $3N$ 的字符串。

### 样例解释 1

可以得到的好字符串有 `ABC`、`BCA`、`CAB` 共 $3$ 个。

### 样例解释 2

可以得到的好字符串有 `AABBCC`、`AABCBC` 共 $2$ 个。

### 样例解释 3

由于已经包含 $4$ 个 `A`，无法得到好字符串。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
???```

### 输出

```
3```

## 样例 #2

### 输入

```
2
AA????```

### 输出

```
2```

## 样例 #3

### 输入

```
3
?A?A?A?A?```

### 输出

```
0```

## 样例 #4

### 输入

```
9
?????????A??B??C???????????```

### 输出

```
331653164```

# 题解

## 作者：翼德天尊 (赞：6)

好妙的题……甚至妙到了不知该如何去追溯思路。所以该题目记录只能尽可能地去还原思维路径。

第一眼看到本题显然会想到 dp，然后我们会想到类似分别记录当前 `A`，`B`，`C`，`AB`，`CA`，`BC`，`ABC`，`BCA`，`CAB` 的数量进行线性 dp 的思路，但是这样并不好去除重复方案，若去掉则时间复杂度过高。

于是，学到的一点是，**在根据题意实在无法进行 dp 时，要尽量思考出一个满足题目要求的充要条件，并对该充要条件进行 dp。**

我们发现题目中要求的 $n$ 个子序列很有特点：`ABC`，`BCA`，`CAB`，具体来说是关于 `A`，`B`，`C` 的三个轮换，这里是不是会存在一些巧妙的性质呢？答案是有的。

不妨记 $x_A$ 表示 `A` 的个数，$x_B$ 表示 `B` 的个数，$x_C$ 表示 `C` 的个数。 

具体来说，我们拿 `A` 举例，我们发现在 `BCA` 和 `CAB` 中，`A` 是一定会在 `C` 的后面的，即如果只有这两种子序列，对于任意前缀子串而言，$x_A$ 一定不大于 $x_C$，但事实上我们还存在子序列 `ABC`，在该子序列中，`A` 是会排在 `C` 之前的，故我们此时有结论：

- 对于任意前缀子串而言，$x_A-x_C$ 一定不大于 `ABC` 的个数。

类似的，我们可以写出轮换的另外两个结论。而由于子序列个数为 $n$，于是此时我们得到了一个看上去并没有那么强但也还不弱的结论：

- 设 $A'=\max(x_A-x_C)$，$B'=\max(x_B-x_A)$，$C'=\max(x_C-x_B)$，则有 $A'+B'+C'\le n$。其中 $\max$ 表示前缀最大值。

到这里我们其实已经论证了该结论的**必要性**，即对于满足条件的方案，一定满足该结论。但是如果满足该结论，是否就一定说明当前方案满足条件呢？

如果还能论证该结论的充分性，我们就可以顺利地将原问题转化为新的充要问题进行 dp 了。

考虑构造方案：对于第 $i$ 个 `A`，我们找到第 $i+B'$ 个 `B`，由于对于任意前缀 `B` 的个数最多比 `A` 多 $B'$ 个，故第 $i+B'$ 个 `B` 一定在第 $i$ 个 `A` 之后；类似地，我们找到第 $i+B'+C'$ 个 `C`，以及第 $i+B'+C'+A'$ 个 `A`。如果下标超出 $n$ 则对 $n$ 取模。此时又由于 $B'+C'+A'\le n$，所以第 $i+B'+C'$ 个 `C` 一定在第 $i+B'+C'+A'$ 个 `A` 前面，同样也一定在第 $i$ 个 `A` 前面。故此时对应的三个字母构成了一个前后顺序正确的环，且只会绕整个串至多一次，又由于此时这些字母一一对应，**故充分性显然**。

于是我们便可以对转化后的问题设计 dp 了！由于我们需要记录的信息是「前缀最大」的 $x_A-x_C$，$x_B-x_A$，$x_C-x_B$，所以我们还需要额外记录下当前 $a,b,c$ 的个数，由于 $a+b+c=i$ 的原因我们可以省去一维，故总状态数为 $O(n^6)$，转移为 $O(1)$，时间复杂度 $O(n^6)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=47;
const int M=17;
const int mod=998244353;
int n,m;
char s[N];
ll dp[N][M][M][M][M][M];
int read(){
	int w=0,fh=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') fh=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*fh;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	m=read(),n=m*3;
    scanf("%s",s+1);
    dp[0][0][0][0][0][0]=1;
    for (int i=0;i<n;i++){
        for (int a=0;a<=m;a++){
            for (int b=0;b<=m;b++){
                int c=i-a-b;
                if (c<0||c>m) continue;
                for (int x=0;x<=m;x++){
                    for (int y=0;y<=m;y++){
                        for (int z=0;z<=m;z++){
                            if (x+y+z>m) continue;
                            if (s[i+1]=='A'||s[i+1]=='?')
                                dp[i+1][a+1][b][max(x,a+1-c)][y][z]=(dp[i+1][a+1][b][max(x,a+1-c)][y][z]+dp[i][a][b][x][y][z])%mod;
                            if (s[i+1]=='B'||s[i+1]=='?')
                                dp[i+1][a][b+1][x][max(y,b+1-a)][z]=(dp[i+1][a][b+1][x][max(y,b+1-a)][z]+dp[i][a][b][x][y][z])%mod;
                            if (s[i+1]=='C'||s[i+1]=='?')
                                dp[i+1][a][b][x][y][max(z,c+1-b)]=(dp[i+1][a][b][x][y][max(z,c+1-b)]+dp[i][a][b][x][y][z])%mod;
                        }
                    }
                }
            }
        }
    }
    ll ans=0;
    for (int i=0;i<=m;i++)
        for (int j=0;j<=m;j++)
            for (int k=0;k<=m;k++)
                if (i+j+k<=m) ans=(ans+dp[n][m][m][i][j][k])%mod;
    cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：UnyieldingTrilobite (赞：3)

对于长度为 $n$ 的字符串 $S$，定义 $f_{AB}(i)=\sum_{j=1}^{i}([S_i=B]-[S_i=A])$，$M_A=\max\{f_{AB}(i)|0\le i\le 3n\}$，人话就是 $A,B$ 分别赋值成 $-1,1$ 后 $S$ 上的最大前缀和。同理定义 $f_{BC},f_{CA},M_B,M_C$。

我们将会由此导出 $S$ 是好串的充要条件：$M_A+M_B+M_C\le n$。

---

+ 充分性：

我们考虑把字符串 $S$ 翻三倍变成 $S+S+S$，那么这个串中有 $3n$ 个 $A$，$3n$ 个 $B$ 和 $3n$ 个 $C$。考虑到一个 $S$ 周期里的 $A$ 和 $B$ 数量是一样的，所以我们的 $M_A$ 依然是这个新串的全局最大 $f_{AB}$。

那么我们考虑从左到右第 $i$ 个 $A$，它一定不会在第 $i+M_A$ 个 $B$（若存在）之后，否则在第 $i+M_A$ 个 $B$ 的位置上 $f_{AB}$ 的值将至少是 $(i+M_A)-(i-1)=M_A+1$ 矛盾。同理第 $i+M_A$ 个 $B$ 一定不在第 $i+M_A+M_B$ 个 $C$ 之后，而后者又不在第 $i+M_A+M_B+M_C$ 个 $A$ 之后，更加不在第 $i+n$ 个 $A$ 之后。换而言之，对于 $1\le i\le n$，第 $i$ 个 $A$，第 $i+M_A$ 个 $B$，第 $i+M_A+M_B$ 个 $C$，这三个字母在 $S$ 的同一个周期内。拍回原来的 $S$ 上（也就是第 $x$ 个 $A/B/C$ 的 $x$ 不断减 $n$ 直到 $n$ 以内），它们的位置一定是轮换转的，也就成为了符合题目要求的划分方式。

+ 必要性：

考虑好串 $S$ 的一个划分，假设分别有 $A_1,B_1,C_1$ 个 $ABC$，$BCA$，$CAB$。那么注意到对于任意 $f_{AB}(i)$，一个 $B$ 如果在划分中不属于某个 $BCA$，那么它的贡献一定会被前面的 $A$ 消掉，换而言之，$f_{AB}(i)\le B_1$，进一步 $M_A\le B_1$，剩下两个同理，于是 $M_A+M_B+M_C\le B_1+C_1+A_1=n$。

---

接下来的过程就非常喜闻乐见了，当前 $A$ 数量，当前 $B$ 数量，当前 $C$ 数量，当前最大 $M_A$，当前最大 $M_B$，当前最大 $M_C$，写进状态里然后 $O(n^6)$ 大力 dp 就可以了。

代码充满暴力美学。

```cpp
#include <atcoder/all>
using namespace std;
typedef atcoder::modint998244353 mint;
constexpr int A = 16;
int n;
string s;
mint f[A][A][A][A][A][A], ans;
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> s;
  f[0][0][0][0][0][0] = 1;
  for (int a = 0; a <= n; ++a)
    for (int b = 0; b <= n; ++b)
      for (int c = 0; c <= n; ++c)
        for (int ma = 0; ma <= n; ++ma)
          for (int mb = 0; mb <= n - ma; ++mb)
            for (int mc = 0; mc <= n - ma - mb; ++mc) {
              mint v = f[a][b][c][ma][mb][mc];
              if (!v.val()) continue;
              int d = a + b + c;
              if (d == 3 * n)
                ans += v;
              else {
                auto trans = [&](char x) {
                  int na = a + (x == 'A'), nb = b + (x == 'B'),
                      nc = c + (x == 'C');
                  if (na > n || nb > n || nc > n) return;
                  int nma = max(ma, nb - na), nmb = max(mb, nc - nb),
                      nmc = max(mc, na - nc);
                  f[na][nb][nc][nma][nmb][nmc] += v;
                };
                if (char x = s[d]; x != '?')
                  trans(x);
                else
                  trans('A'), trans('B'), trans('C');
              }
            }
  return cout << ans.val() << endl, 0;
}
```

---

闲话：

+ 数据范围：$n\le 15$。

+ 你以为的：$O(3^n)$。

+ 实际上的：$O(n^6)$。

官方题解甚至还专门分析了一下为啥是六次方而不是七次方，他真的我哭死。

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc055_d)

**题目大意**

> 定义一个长度为 $3n$ 的字符串 $S$ 是好的，当且仅当其可以划分为 $n$ 个 $\texttt{ABC,BCA,CAB}$ 序列。
>
> 给定字符串的一部分，求有多少种补全方式使得该串是好的。
>
> 数据范围：$n\le 15$。

**思路分析**

我们设 $f_{A}(i)$ 表示 $S[1,i]$ 中 $\texttt B$ 的个数减去 $\texttt A$ 的个数，并记 $\max f_{A}(i)=f_A$，同理定义 $f_B,f_C$。

那么我们发现 $S$ 是好的当且仅当 $f_A+f_B+f_C\le n$，下面给出证明：

先证充分性：

> 我们观察字符串 $S+S$，由于每个 $S$ 中 $\texttt{A,B,C}$ 个数相等，因此 $S\to 2S$ 的 $f_A,f_B,f_C$ 不变。
>
> 考虑第 $i$ 个 $\texttt A$ 所在位置 $p_i$，由于 $f_A(p_i-1)\le f_A$，因此 $S[1,p_i-1]$ 中 $\texttt B$ 的个数不超过 $i-1+f_A$。
>
> 因此第 $i+f_A$ 个 $\texttt B$ 在第 $i$ 个 $\texttt A$ 右边，同理第 $i+f_A+f_B$ 个 $\texttt C$ 在第 $i+f_A$ 个 $\texttt B$ 右边，第 $i+f_A+f_B+f_C$ 个 $\texttt A$ 在第 $i+f_A+f_B$ 个 $\texttt C$ 右边。
>
> 由于 $f_A+f_B+f_C\le n$，那么 $\texttt C$ 的位置在第 $i+n$ 个 $\texttt{A}$ 左边，因此这三个 $\texttt{A,B,C}$ 在 $S+S$ 范围内，且距离 $<|S|$。
>
> 因此我们取出这三个 $\texttt{A,B,C}$ 匹配成子序列（$>|S|$ 的减去 $|S|$），由于他们之间的距离 $<|S|$，只会把一段后缀提到前缀上，因此划分出来的一定是 $\texttt{ABC,BCA,CAB}$ 中的一个。

再证必要性：

> 对于一个合法的 $S$，我们设 $\texttt{ABC,BCA,CAB}$ 数量分别为 $g_A,g_B,g_C$。
>
> 注意到一个 $\texttt{ABC,CAB}$ 只会让 $f_{A}(i)$ 区间 $-1$，只有 $\texttt{BCA}$ 会让 $f_A(i)$ 区间 $+1$，因此显然有 $f_A\le g_B$。
>
> 同理可知 $f_B\le g_C,f_C\le g_A$，因此 $f_A+f_B+f_C\le g_A+g_B+g_C$。

所以我们 dp 记录 $f_{a,b,c,fa,fb,fc}$ 表示当前 $\texttt{A,B,C}$ 个数，以及当前 $f_A,f_B,f_C$ 即可，转移枚举下一个字符。

时间复杂度 $\mathcal O(n^6)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
int n,f[16][16][16][16][16][16],ans;
char s[55];
inline void add(int &x,const int &y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
signed main() {
	scanf("%d%s",&n,s+1);
	f[0][0][0][0][0][0]=1;
	for(int i=0;i<=n;++i) for(int j=0;j<=n;++j) for(int k=0;k<=n;++k) {
		for(int x=0;x<=n;++x) for(int y=0;x+y<=n;++y) for(int z=0;x+y+z<=n;++z) {
			const int &w=f[i][j][k][x][y][z];
			if(!w) continue;
			int t=i+j+k+1;
			if(t>3*n) { add(ans,w); continue; }
			if((s[t]=='?'||s[t]=='A')&&i<n) add(f[i+1][j][k][x][y][max(z,i-k+1)],w);
			if((s[t]=='?'||s[t]=='B')&&j<n) add(f[i][j+1][k][max(x,j-i+1)][y][z],w);
			if((s[t]=='?'||s[t]=='C')&&k<n) add(f[i][j][k+1][x][max(y,k-j+1)][z],w);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：cyh_toby (赞：1)

首先考虑如何判定合法。两种思路，搞出 DFA，或者找充要条件。大概想一下会发现 DFA 状态数肯定是爆炸的，所以只能找充要条件。

**Lemma.** 记 $A$ 为任意前缀中 `B` 的数量减 `A` 的数量的最大值，同理定义 $B,C$，那么合法的充要条件是 $A+B+C\le n$。

**必要性.** 若 $S$ 可划分为 $n$ 个 `ABC`，`BCA`，`CAB`，那么 $A$ 一定不大于 `BCA` 的数量，$B,C$ 类似。于是可知 $A+B+C\le n$。

**充分性.** 考虑如下构造：第 $i$ 个 `A` 与第 $i+A$ 个 `B` 与第 $i+A+B$ 个 `C` 构成一个三元组（下标超过 $n$ 的看做循环）。根据定义可知第 $i+A$ 个 `B` 一定在第 $i$ 个 `A` 后面，第 $i+A+B$ 个 `C` 一定在第 $i+A$ 个 `B` 后面；且第 $i+A+B$ 个 `C` 一定在第 $i+A+B+C$ 个 `A` 之前，又由于 $A+B+C\le n$，所以这个 `A` 一定不超过第 $i+n$ 个 `A` 即第 $i$ 个 `A`。由此可以发现，这样的三元组从 `A` 走到 `B` 走到 `C` 不会走过一整圈，且是按顺序走的，进而可以得知一定是符合题意的。 

于是，设 $f(i,a,b,c,A,B,C)$ 表示考虑前 $i$ 个字符，`A,B,C` 分别有 $a,b,c$ 个，$A,B,C$ 的含义如上所述，的方案数。显然 $a+b+c=i$，因此实际上状态数是 $O(n^6)$ 的，转移是 $O(1)$ 的，所以总复杂度 $O(n^6)$，且常数非常小。

[代码](https://atcoder.jp/contests/agc055/submissions/38180885)



---

## 作者：yzc001 (赞：0)

# 0.前言
[在博客园食用更佳](https://www.cnblogs.com/zan-mei-tai-yang/p/18979437)  
省流：[**275307894a**](https://www.luogu.com.cn/user/181766) 对 蒟蒻们 使用了 模拟赛  
蒟蒻们 rp++
# 1.思路
是[双倍经验](https://www.luogu.com.cn/problem/P12472)的部分分，[我的题解](https://www.luogu.com.cn/article/irgwazd0/)。  
由于串固定，所以可以先枚举 `ABC`,`BCA`,`CAB` 的数量。  
容易想到枚举每个 `A`,`B`,`C` 的位置。  
显然，第一个字符要作为一个字符串的第一个字符，最后一个字符要作为一个字符串的最后一个字符  
故考虑贪心  
令 `ABC` 的数量=$A$，`BCA` 的数量=$B$，`CAB` 的数量=$C$，则方案如下
|串|ABC|BCA|CAB|
|-|-|-|-|
|第一个字符所在位置|$(1,A)$|$(1,B)$|$(1,C)$
|第二个字符所在位置|$(B+1,B+A)$|$(C+1,C+B)$|$(A+1,A+C)$
|第三个字符所在位置|$(C+B+1,C+B+A)$|$(A+C+1,A+C+B)$|$(B+A+1,B+A+C)$

这里的位置指的是相对位置。  
形式化地，如设所有 `A` 中的第 $i$ 个 `A` 为 $a_i$，则 $(1,A)$ 指 `ABC` 的 `A` 应出现在 $(a_1,a_A)$ 范围内。   
也即，**当每个串最前面的字符出现在每种字符的最前面，最后的字符出现在每种字符的最后面**时，若不存在方案，则说明 $A,B,C$ 不是一个可行的方案。  

> 省流：前面在前面，后面在后面，如果没方案，肯定没方案
### 具体证明：  

反证，假设存在一种方案在 $A,B,C$ 的约束下成立，但在以上方案不成立，则可以通过数次交换 `ABC`,`BCA`,`CAB` 中的 `A`,`B`,`C`，使其最终化为此方案  
如~~我手搓的~~样例
```
ABCCAB
```
如选取 $a_1,b_1,c_1$ 组成 `ABC`,$c_2,a_2,b_2$ 组成 `CAB`，  
则显然 $a_1,b_1,c_2$ 组成 `ABC`,$c_1,a_2,b_2$ 组成 `CAB` 一定也是一个可行的方案。  
故，在以上方案成立是当前方案成立的**充分必要条件**。  

> 省流：上一句话是对的

于是，你就得到了一种在 $O(n^3)$ 时间内求出一个方案是否成立的方法。  
接下来，考虑优化枚举过程。  
考虑给定$A$, $B$ 如何计数，则上面的最优分配方案可以转化为对于$p_a,i$ 和 $p_b,B+i$ 等的顺序限制。  
然后设 $f_{a,b,c}$ 表示当前填了前 $a$ 个 `A`，$b$ 个 `B`，$c$ 个 `C` 的方案数。这个dp是 $O(n^3)$ 的。  
对于一般的情况，只需要枚举哪些子集对是合法的，容斥即可计算答案。  
注意到如果两个子集 $max$ 加起来大于 $n$ 肯定是无解的，因此只有
$O(2^nn)$ 个子集对需要计算，时间复杂度 $O(2^nn^4)$，可以通过。

# 2.代码
[click](https://www.cnblogs.com/zan-mei-tai-yang/p/18979437) 
# 3.后记
1. 膜拜巨佬 [**275307894a**](https://www.luogu.com.cn/user/181766)  
2. [双倍经验](https://www.luogu.com.cn/problem/P12472),而且呈包含关系
3. ~~给好不容易搞懂此题的本蒟蒻一个赞吧~~

---

