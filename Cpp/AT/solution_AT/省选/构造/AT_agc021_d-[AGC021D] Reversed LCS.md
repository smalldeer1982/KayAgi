# [AGC021D] Reversed LCS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc021/tasks/agc021_d

高橋君はお母さんに文字列をプレゼントすることにしました。

文字列 $ T $ の価値とは、$ T $ を逆から読んだものを $ T' $ として、$ T $ と $ T' $ の最長共通部分列の長さです。 すなわち、(連続するとは限らない)部分列として $ T $ と $ T' $ の両方に現れるものの最大長です。

高橋君は、文字列 $ S $ を持っています。お母さんにできるだけ価値の高い文字列をプレゼントしたい高橋君は、 $ S $ の文字を $ K $ 箇所まで任意に変更して、できるだけ価値の高い文字列を作りたいです。

達成できる価値の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 300 $
- $ 0\ \leq\ K\ \leq\ |S| $
- $ S $ は英小文字からなる
- $ K $ は整数である

### Sample Explanation 1

$ 1 $ 文字目を `c` に変更すると、文字列は `cbcabcabc` になります。 できた文字列を $ T $ とおけば、長さ $ 7 $ の文字列 `cbabcbc` が $ T $ と $ T' $ の最長共通部分列の一例となります。

## 样例 #1

### 输入

```
abcabcabc
1```

### 输出

```
7```

## 样例 #2

### 输入

```
atcodergrandcontest
3```

### 输出

```
15```

# 题解

## 作者：NaVi_Awson (赞：4)

## Description

[题库链接](https://agc021.contest.atcoder.jp/tasks/agc021_d)

在改变原串 $S$ 最多 $K$ 个字母的前提下，使得 $S$ 和 $S$ 的反串的 $LCS$ 尽量长，问最长长度。

$1\leq K\leq |S|\leq 300$

## Solution

一个结论是字符串的最长回文子序列（ $lps$ ）长度等于其自身与反转的最长公共子序列（ $lcs$ ）长度。

证明可见 [某乎](https://www.zhihu.com/question/34580085) 。

那么显然可以用区间 $DP$ 实现了。记 $f_{l,r,k}$ 表示区间 $[l,r]$ 内修改了 $k$ 个字母的 $lps$ 长度。

转移只要考虑是否替换两端的字母即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 300;

char ch[N+5]; int f[N+5][N+5][N+5], k, n;

void work() {
    scanf("%s%d", ch+1, &k); n = strlen(ch+1);
    for (int i = 1; i <= n; i++) f[i][i][0] = 1;
    for (int l = 1; l <= n; l++)
	for (int i = 1; i+l <= n; i++)
	    for (int p = 0, j = i+l; p <= k; p++) {
		f[i][j][p] = max(f[i+1][j][p], f[i][j-1][p]);
		if (ch[i] == ch[j]) f[i][j][p] = max(f[i][j][p], f[i+1][j-1][p]+2);
		if (p) f[i][j][p] = max(f[i][j][p], f[i+1][j-1][p-1]+2);
	    }
    int ans = 0;
    for (int i = 0; i <= k; i++) ans = max(ans, f[1][n][i]);
    printf("%d\n", ans);
}
int main() {work(); return 0; }
```

---

## 作者：Comentropy (赞：2)

很有意思的题啊！

一开始看到这个正串和反串的 $LPS$，就感觉会往回文那边靠。不过这个结论还是很厉害的：

- **性质：正串和反串的 $LCS=$ 原串的最长回文子序列**。其中子序列指的是非连续子序列。

感受一下就感觉很对，而且并不难证明这个结论，很巧妙地：

我们可以通过证明不等关系来证明它必定取等：首先由于最长回文子序列反过来还是一样的，都出现在正串和反串里，所以 $LPS\leq LCS$，其中 $LPS$ 是最长回文子序列的简称。

随后我们要证明 $LPS\geq LCS$，就可以得到 $LCS=LPS$。

考虑这个 $LCS$ 在原序列里面长成什么样，设它长度为 $k$，是原串 $T$ 中的 $T_{i_1},T_{i_2},\dots,T_{i_k}(i_1<i_2<\dots<i_k)$，以及反过来我们也能找到这个串，设为：$T_{j_k},T_{j_2},\dots,T_{j_1}(j_1>j_2>\dots>j_k)$（在 $T'$ 中的顺序是正过来的）。

我们总能找到一个位置使 $i_p<j_p$ 而 $i_{p+1}\geq j_{p+1}$，方便起见设 $i_{k+1}=\lvert T \rvert+1$ 以及 $j_{k+1}=-1$，这样保证两个串必然有个这样的交点。（画个图就好理解了）

现在，当 $i_{p+1}>j_{p+1}$ 的时候，我们很明显可以把串变成 $T_{i_1},\dots,T_{i_p},T_{j_p},\dots,T_{j_1}$，这是一个回文串；以及 $T_{j_{k}},T_{j_{k-1}},\dots,T_{j_{p+1}},T_{i_{p+1}},\dots,T_{i_k}$。都是回文序列，而且总长度是 $2k$ 啊！这意味着至少其中有一个长度为 $k$，我们就说明了 $LCS$ 肯定可以是 $LPS$。

而当 $i_{p+1}=j_{p+1}$ 的时候，我们把这个位置分给两个回文串就可以如上构造了：$T_{i_1},\dots,T_{i_p},T_{i_{p+1}},T_{j_p},\dots,T_{j_1}$，往另一个串里塞 $T_{j_{p+1}}$ 就得到了总长为 $2k$ 的两个回文串。画张图辅助理解：
![](https://cdn.luogu.com.cn/upload/image_hosting/hxtsebss.png)

接下来问题转化为原串中最长回文子序列了，这应当是简单的，就不多说了。

---

## 作者：liujiaxi123456 (赞：1)

首先有一个结论：**S 和 S 的反串的最长公共子序列 = S 的最长回文子序列。**

- 一开始直接把这玩意儿直接用了，后面才发现还需要证明。

- 证明也还好，就把 $LCS\le LPS $ 和 $LPS\le LCS $ 个证一遍就得到相等了。

- 不想证的话感性理解一下也是很容易的。

于是考虑求解最长回文子序列：

- 可以改 $k$ 个，大概率都需要记下来 DP 处理。

- 由于回文是两边扩展的，在线性递推里几乎没有任何性质，所以考虑区间 DP。

- 于是设 $f_{l, r, k} $ 表示处理完 $[l, r]$ 的区间，改了 $k$ 个值时的最长回文子序列。

考虑转移：

- 就两种可能：$(l, r) $ 凑一对/内部继承。

- 然后分讨一下 $[s_l=s_r] $  即可。

Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 305;

namespace Josh_zmf {
	
	int N, K, f[Maxn][Maxn][Maxn]; string s;

	inline int main() {
		cin>> s>> K, N = s.size(), s = ' ' + s;
		for(int l=1; l<=N; l++) {
			for(int k=0; k<=K; k++)	f[l][l][k] = 1;
		}
		for(int len=2; len<=N; len++) {
			for(int r=len, l; r<=N; r++) {
				l = r-len+1;
				for(int k=0; k<=K; k++) {
					if(s[l] == s[r])	f[l][r][k] = f[l+1][r-1][k]+2;
					else	f[l][r][k] = max({f[l+1][r][k], f[l][r-1][k], (k ?f[l+1][r-1][k-1]+2 :0)});
					// printf("f[%d][%d][%d]:%d, sl:%c, sr:%c\n", l, r, k, f[l][r][k], s[l], s[r]);
				}
			}
		}
		int ans = 0;
		for(int k=0; k<=K; k++)	ans = max(ans, f[1][N][k]);
		cout<< ans<< '\n';
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
最后提供一组 hack：

- in

```cpp
abab
2
```
- out
```cpp
4
```

---

## 作者：shinkuu (赞：1)

大家全部都是根据回文串性质 dp 的。我带来一种不太一样的 dp 方法。

下文中定义 $\operatorname{rev}(A)$ 为序列 $A$ 翻转过后的结果。

**Lemma 1：$\operatorname{LCS}(A,B)$ 长度等于 $\operatorname{LCS}(\operatorname{rev}(A),\operatorname{rev}(B))$。**

Proof：比较显然。考虑反证，假设其中一者（设其为 $C$）比另一者长，另一者显然可以变为 $\operatorname{rev(C)}$，则假设不成立。

**Lemma 2：答案 $\operatorname{LCS}$ 一定为回文字符串。**

Proof：也比较显然。和上者类似，假设不是，则一定可以通过将某一元素对称获得不劣解。

有了上面两个性质，结合题意，可以考虑 dp。但是因为原串修改后翻转串也会修改，所以不可避免地会有后效性。但是结合 Lemma 2 会发现，我们其实可以把答案串看成对称的两串，只用对其中一串进行 dp，处理另一串直接 $\times 2$ 即可。

解决这个问题，可以考虑把原串劈成两半 $S,T$。然后将 $S$ 和 $\operatorname{rev}(T)$ 做最多修改 $k$ 次的 $\operatorname{LCS}$ 问题即可。这个很典，只用在求 $\operatorname{LCS}$ 的算法上稍加改进，可以 $O(n^2k)$ 解决。最后根据 Lemma 1，再将答案 $\times 2$ 即可。

但是这样显然是不对的，因为两个样例答案都是奇数。容易发现这种情况下是漏掉了中间的一个字符。于是改进算法，加上一个劈成三段的情况 $S,M,T$。处理答案即为将 $S,T$ 同上求解，最后 $ans\leftarrow ans\times2+1$ 即可。

需要补充的是，没有必要真的劈完再 dp。这样复杂度会爆炸。只用对原串 $A$ 和 $\operatorname{rev}(A)$ 做一遍来预处理即可。

code：

```cpp
int n,m,dp[N][N][N];
char s[N],t[N];
void Yorushika(){
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	memcpy(t,s,sizeof s);
	reverse(t+1,t+n+1);
	mems(dp,-0x3f);
	rep(i,0,n){
		dp[0][i][0]=dp[i][0][0]=0;
	}
	rep(i,1,n){
		rep(j,1,n){
			rep(k,0,m){
				dp[i][j][k]=max(dp[i-1][j][k],dp[i][j-1][k]);
				if(k>0)
					dp[i][j][k]=max(dp[i][j][k],dp[i][j][k-1]);
				if(s[i]==t[j])
					dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-1][k]+1);
				else if(k>0)
					dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-1][k-1]+1);
			}
		}
	}
	int ans=1;
	rep(i,1,n){
		rep(j,1,n-i){
			ans=max(ans,dp[i][j][m]*2+(i+j!=n));
		}
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

我觉得是思路最自然，而不是看范围猜算法的方式捏。

---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc021_d)

刚开始把子序列看成字串，结果想了好久，觉得这无解吧，然后发现是子序列，哦那没啥了。

首先需要将题目中给出的所谓“字符串的值”转换一下：

因为 $T'$ 是 $T$ 的相反串，而我们知道，判断一个字符串是否回文就是判断相反串和它是否相同，得出相反串相同即回文，那么，子序列相反串相同即存在相同的子序列，换句话说，就是公共子序列了，因此我们能得出这题是求修改 $1\sim k$ 次后的最长回文子序列的长度。

我们考虑区间 DP，设 $dp(i,j,k)$ 为 $i\sim j$ 修改 $k$ 次后的最长回文子序列长度，显然，我们要求 $max(dp(1,|s|,k)$。

对于 $dp(i,i,0)$，显然等于 1。

然后就要考虑对于任意的 $dp(i,j,k)$，如何继承其它的解。

$s_{i+1}$ 到 $s_j$ 和 $s_i$ 到 $s_{j-1}$ 的解显然是可以继承到 $dp(i,j,k)$ 的。

接着我们就想一想，对于回文串的 DP 题，一般会存在 $s_i=s_j$ 的情况，那么，这意味着 $dp(i+1,j-1,k)$ 是可以继承上来的，我们只需要在其基础上加上 2，也就是 $s_i$ 和 $s_j$ 的长度。

那么，$s_i \neq s_j$ 时，就只能按照上面的方式继承了吗？显然，我们还没有考虑以 $k$ 为继承焦点的方式，我们可以试着修改，那么，增加 $s_j$，会增加多少修改量呢？答案是 $j-i+2$，所以我们换一种，增加 $s_i$ 和 $s_j$，这样只需要把 $s_j$ 或 $s_i$ 修改，得出 $dp(i,j,k)=dp(i+1,j-1,k-1)+2$。

那么，上述转移方程是正确的吗？我们这样想，$s_{i+1}$ 到 $s_{j-1}$ 的这一段中的子序列加上了旁边两段相同的后，依然回文，所以是正确的。

最后贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	static int k,dp[333][333][333],c[333],ma;
	cin>>s;cin>>k;
	for(int i=0;i<s.length();i++)c[i+1]=s[i];
	for(int i=1;i<=s.length();i++)dp[i][i][0]=1;
	for(int l=2;l<=s.length();l++)
	{
		for(int i=1;i+l-1<=s.length();i++)
		{
			int j=i+l-1;
			for(int q=0;q<=k;q++)
			{
				dp[i][j][q]=max(dp[i+1][j][q],dp[i][j-1][q]);
				if(c[i]==c[j])dp[i][j][q]=max(dp[i][j][q],dp[i+1][j-1][q]+2);
				if(q!=0)dp[i][j][q]=max(dp[i][j][q],dp[i+1][j-1][q-1]+2);
			}
		}
	}
	for(int i=0;i<=k;i++)ma=max(ma,dp[1][s.length()][i]);//注意不能输出dp[1][s.length()][k]
	cout<<ma;
	return 0;
} 
```


---

## 作者：cymrain07 (赞：0)

## AGC021 D
**[题目链接](https://atcoder.jp/contests/agc021/tasks/agc021_d)**
___
**题目大意**  
给一个字符串 $s$，可以将 $s$ 中最多 $K$ 个字符更改为任何其他字符，使 $s$ 和 $s$ 的反串 $s'$ 的最长公共子区间长度最大，输出这个长度。
___
**题解**  
问题可以转化为求更改后的 $s$ 的最长回文子序列长度。
设 $dp(i,j,k)$ 表示区间 $[i,j]$ 已经修改了 $k$ 个字符的最长回文子序列长度。  
初始化 $dp(i,i,0)\gets1$。

$$
dp(i,j,k)\gets\max(dp(i+1,j,k),dp(i,j-1,k))
$$

当 $s(i)=s(j)$ 时：
$$
dp(i,j,k)\gets\max(dp(i,j,k),dp(i+1,j-1,k)+2)
$$
当 $k\neq0$ 时：
$$
dp(i,j,k)\gets\max(dp(i,j,k),dp(i+1,j-1,k-1)+2)
$$

___
**代码**
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
const int MAXN = 305;
char s[MAXN];
int K, dp[MAXN][MAXN][MAXN], ans;
int main()
{
    scanf("%s%d", s + 1, &K);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i++)
    {
        dp[i][i][0]=1;
    }
    for (int m = 1; m <= n; m++)
    {
        for (int i = 1; i + m <= n; i++)
        {
            int j = i + m;
            for (int k = 0; k <= K; k++)
            {
                dp[i][j][k] = max(dp[i + 1][j][k], dp[i][j - 1][k]);
                if (s[i] == s[j])
                {
                    dp[i][j][k] = max(dp[i][j][k], dp[i + 1][j - 1][k] + 2);
                }
                if (k != 0)
                {
                    dp[i][j][k] = max(dp[i][j][k], dp[i + 1][j - 1][k - 1] + 2);
                }
            }
        }
    }
    for (int i = 0; i <= K; i++)
    {
        ans = max(ans, dp[1][n][i]);
    }
    cout << ans;
    return 0;
}
```

---

