# [ABC312D] Count Bracket Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc312/tasks/abc312_d

空でない文字列 $ S $ が与えられます。$ S $ の各文字は `(`, `)`, `?` のいずれかです。  
 $ S $ に含まれる `?` の個数を $ x $ とすると、`?` を `(` あるいは `)` に置き換えて新しい文字列を作る方法は $ 2^x $ 通りありますが、このうち新しくできた文字列が**括弧列**となるような置き換え方の数を $ 998244353 $ で割った余りを求めてください。

ただし、括弧列とは以下のいずれかの条件を満たす文字列のことです。

- 空文字列
- ある括弧列 $ A $ が存在して、`(`, $ A $, `)` をこの順に連結した文字列
- ある空でない括弧列 $ A,\ B $ が存在して、$ A,\ B $ をこの順に連結した文字列

## 说明/提示

### 制約

- $ S $ は長さ $ 3000 $ 以下の `(`, `)`, `?` からなる空でない文字列
 
### Sample Explanation 1

$ S $ を `()()()` あるいは `(())()` に置き換えると括弧列となります。 他の置き換え方で新しくできた文字列が括弧列となることはないので、$ 2 $ を出力します。

### Sample Explanation 3

$ 998244353 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
(???(?```

### 输出

```
2```

## 样例 #2

### 输入

```
)))))```

### 输出

```
0```

## 样例 #3

### 输入

```
??????????????(????????(??????)?????????(?(??)```

### 输出

```
603032273```

# 题解

## 作者：Engulf (赞：15)

简单 dp。

见到括号序列就有一个很绝妙的转换，我们把左括号看做 $1$，右括号看做 $-1$，那么一个合法的括号序列就满足这个序列的总和为 $0$ 且任意前缀的和都是非负的。

设 $f_{i, j}$ 表示前 $i$ 个字符，把这些字符看作数字的话和为 $j$ 的方案数。因为合法括号序列任意前缀均为非负，所以不用 dp $j < 0$ 的部分。

转移很显然：

令 $c$ 为第 $i$ 个字符。

- 若 $c$ 为左括号，$\large f_{i, j} \leftarrow f_{i, j} + f_{i - 1, j - 1}$。
- 若 $c$ 为右括号，$\large f_{i, j} \leftarrow f_{i, j} + f_{i - 1, j + 1}$。
- 若 $c$ 为问号，那么两种情况都有可能，$\large f_{i, j} \leftarrow f_{i,j}+ f_{i - 1, j - 1} + f_{i - 1, j + 1}$。

边界：$f_{0, 0} = 1$。

最终答案为 $f_{n, 0}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 3005, mod = 998244353;

int n;

char str[N];

int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> str + 1;
    n = strlen(str + 1);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        if (str[i] == '(') {
            for (int j = 1; j <= i; j++)
                f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
        } else if (str[i] == ')') {
            for (int j = 0; j < i; j++)
                f[i][j] = (f[i][j] + f[i - 1][j + 1]) % mod;
        } else {
            for (int j = 1; j <= i; j++)
                f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
            for (int j = 0; j < i; j++)
                f[i][j] = (f[i][j] + f[i - 1][j + 1]) % mod;
        }
    }
    cout << f[n][0] << "\n";
    return 0;
}
```

---

## 作者：hjfjwl (赞：6)

题目说给你一个字符串 $s$，其中你可以在 ? 的位置上填 ( 或者 ),问你有多少种填法。我们可以用 dp 来解决这道题，$dp[i][j]$ 代表的是到第 $i$ 位 ( 比 ) 多的个数，初始 $dp[0][0] = 1$。

$$\begin{cases} s[i] = ( & dp[i][j] = dp[i-1][j](0 \le j < i)\\ s[i] = ) &  dp[i][j - 1] = dp[i - 1][j](1 \le j <i)\\ s[i] = ? &dp[i][j] = dp[i-1][j](0 \le j < i) \text{ 然后 } dp[i][j - 1] = (dp[i][j - 1] + dp[i - 1][j]) \bmod mod(1 \le j <i)\end{cases}$$

AC code
```cpp
#include <iostream>
using namespace std;
#define int long long
const int mod = 998244353;
int dp[3005][3005];
signed main(){
	string s;
	cin >> s;
	s = ' ' + s;
	dp[0][0] = 1;
	for(int i = 1;i < s.size();i++)
	{	
		if(s[i] == '(')
		{
			for(int j = 0;j < i;j++)
			{
				dp[i][j + 1] = dp[i - 1][j];
			}
		}
		else if(s[i] == ')')
		{
			for(int j = 1;j < i;j++)
			{
				dp[i][j - 1] = dp[i - 1][j];
			}
		}
		else
		{
			for(int j = 0;j < i;j++)
			{
				dp[i][j + 1] = dp[i - 1][j];
			}
			for(int j = 1;j < i;j++)
			{
				dp[i][j - 1] += dp[i - 1][j];
				dp[i][j - 1] %= mod;
			}
		}
	}
	cout << dp[s.size() - 1][0];
	return 0;
}
```

---

## 作者：hzlqwq (赞：3)

显然，**每个前缀中的左括号数量都不小于右括号数量，且整个序列中的左括号数量与右括号数量相等**是一个括号序列合法的充要条件，结合数据范围，我们考虑二维 dp：

令 $f_{i,j}$ 表示括号序列前 $i$ 位有 $j$ 个右括号的方案数（$j \leq \frac{i}{2}$），则 basecase 为 $f_{0,0}=1$，转移方程为：

$$
f_{i,j}=
\left\{\begin{matrix}
f_{i-1,j-1}+f_{i-1,j}  & s_i=\mathtt{?} \\
f_{i-1,j}  & s_i=\mathtt{(} \\
f_{i-1,j-1} & s_i=\mathtt{)}
\end{matrix}\right.
$$

若 $\lvert S \rvert$ 为奇数则答案为 $0$，偶数则为 $f_{\lvert S \rvert,\frac{\lvert S \rvert}{2}}$，时间复杂度 $O\left(\lvert S \rvert^2\right)$。

```cpp
#include <cstring>
#include <iostream>

using namespace std;

const int N = 3e3 + 10, mod = 998244353;

char s[N];
int len, dp[N][N >> 1]; // 前 i 位 j 个右括号（只用计算右括号数量不超过总长一半的情况）

int main()
{
    cin >> s + 1;
    if ((len = strlen(s + 1)) & 1) // 奇数长度特判
        return cout << 0 << endl, 0;
    dp[0][0] = 1;
    for (int i = 1; i <= len; i++)
        for (int j = 0; j << 1 <= i; j++)
        {
            if (s[i] == '?')
                dp[i][j] = ((j ? dp[i - 1][j - 1] : 0) + dp[i - 1][j]) % mod; // 小心越界！
            else if (s[i] == '(')
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = j ? dp[i - 1][j - 1] : 0;
        }
    cout << dp[len][len >> 1] << endl;
    return 0;
}
```


---

## 作者：梦应归于何处 (赞：2)

## 题目大意

给定包含左右括号和问号的字符串 $S$。有 $2 ^ X$ 种方法将问号改为左右括号，其中 $X$ 是 $S$ 中的问号数量。请你求出有多少种更改方法使得结果字符串为合法括号串。

题意很简单，但是思路不是很好想。

## 思路

这个题其实就是一个二维 DP，我们设 $f_{i,j}$ 为前 $i$ 个字符中 $val$ 为 $j$ 的方案数，在这里我们定义 $val$ 为一个参数，如果当前的字符 $T$ 为左括号则 $val+1$，如果当前的字符 $T$ 为右括号则 $val-1$,如果当前的字符 $T$ 为问号则分别枚举 $T$ 是左括号和右括号的情况。

## 状态转移

我们考虑最后一步决策，如果当前是左括号，我们就可以从 $f_{i-1,j-1}$ 转移过来。如果当前是右括号，我们就可以从 $f_{i-1,j+1}$ 转移过来。如果是问号呢？我们可以分别枚举它是左括号，右括号，如果是左括号，我们上面说了可以从 $f_{i-1,j-1}$ 转移过来，如果是右括号，我们上面也说了可以从 $f_{i-1,j+1}$ 转移过来，所以我们可以把这两个加在一起就可以得到我们问号的转移方程了，就是$f_{i-1,j-1} + f_{i-1,j+1}$。

## 初始化和输出答案

初始化：$f_{0,0}=1$。

输出答案：$f_{n,0}$，为什么要输出这个呢？因为我们最终要找的是前 $n$ 个中 $val$ 为 $0$ 的答案。

## 代码

~~~cpp


#include <bits/stdc++.h>
#include <bits/stdc++.h>
#define TNTMAX INT_MAX
#define db double
#define ll long long
#define ex exit(0);
using namespace std;
string s;
ll f[4000][4000];
int main() {
	cin >> s;
	ll len = s.size();
	s = ' ' + s;
	f[0][0] = 1;
	for (int i = 1; i <= len; i++) {
		for (int j = 0; j <= len; j++) {
			if (s[i] == '(' && j >= 1) {
				f[i][j] += f[i - 1][j - 1];
			}
			if (s[i] == ')') {
				f[i][j] += f[i - 1][j + 1];
			}
			if (s[i] == '?') {
				if (j >= 1) {
					f[i][j] += f[i - 1][j - 1];
				}
				f[i][j] += f[i - 1][j + 1];
			}
			f[i][j] %= 998244353;
		}
	}
	cout << f[len][0];
	return 0;
}


~~~

---

## 作者：Halberd_Cease (赞：2)

看到数据范围，$|S|\le 3000$，想到一个 $O(n^2)$ 的朴素 DP 做法。
 
我们令 dp 数组 $dp_{i,j}$ 表示当前枚举到第 $i$ 位，还有 $j$ 个左括号没有匹配的方案总数。

然后是转移方程：

- 如果这一位是 ```(``` 的话，不匹配的位数就要多一位，有转移方程 $dp_{i,j}=dp_{i-1,j-1}$；

- 如果是 ```)``` 的话，不匹配的位数就要少一位，有转移方程 $dp_{i,j}=dp_{i-1,j+1}$；

- 如果是 ```?``` 的话，以上两种情况都可以选择，那么转移方程就应该是 $dp_{i,j}=dp_{i-1,j-1}+dp_{i-1,j+1}$。

初始化：第一位如果是 ```)``` 的话要特判处理掉，其余情况就把 $dp_{0,1}$ 赋值为 $1$，枚举区间 $[1,|S|-1]$ 处理答案即可。

核心代码：

```cpp
    for (int i = 1; i < n; i++)
    {
        if (str[i] != '(')
            for (int j = 1; j <= n; j++)
            {
                dp[i][j - 1] += dp[i - 1][j];
                dp[i][j - 1] %= MOD;
            }
        if (str[i] != ')')
            for (int j = 0; j <= n; j++)
            {
                dp[i][j + 1] += dp[i - 1][j];
                dp[i][j + 1] %= MOD;
            }
    }
```

---

## 作者：szhqwq (赞：1)

## $\tt{Solution}$

考虑 dp。

设 $dp_{i,j}$ 表示填充了前 $i$ 位中的 `?` 且 $j$ 为前 $i$ 位中 `(` 的数量减去 `)` 的数量的值的合法方案数。则答案为 $dp_{n,0}$，递推起点为 $dp_{0,0} = 1$。

状态转移我们分为 $3$ 种：

1. $s_i$ 为 `(`，$dp_{i + 1,j + 1} \gets dp_{i,j} + dp_{i + 1,j + 1}$；

2. $s_i$ 为 `)`，此时需要判断一下 $j$ 是否为 $0$，如果为 $0$，那么此处不能转移，不然 $dp_{i + 1,j - 1} \gets dp_{i,j} + dp_{i + 1,j - 1}$；

3. $s_i$ 为 `？`，有将其变为 `(` 或 `)` 两种方法，所以需要把上面两种转移一起做一遍。

[Link](https://atcoder.jp/contests/abc312/submissions/44149163)

---

## 作者：Genius_Star (赞：1)

### 题意：

由 ``(`` 和 ``)`` 组成的字符串 $S$ 是括号字符串，当且仅当满足以下三个条件：

1. 对于所有 $i$，$S$ 的前 $i$ 个字符包含更多的 ``(`` 而不是 ``)``。

2. $S$ 包含相同数量的 ``(`` 和 ``)``。

3. 这可以通过对 $S$ 的长度进行归纳来表示。

现在给出由 ``(`` 和 ``)`` 和 ``?`` 组成的字符串，其中 ``?`` 可以代表左括号也可以代表右括号，问可以形成的括号字符串的个数 $\bmod$  $998244353$。

### 思路：

很明显，这题是个动态规划问题。

首先，我们定义一个二维数组 $dp$，其中 $dp_{i,j}$ 表示在字符串 $S$ 的前 $i$ 个字符中，有 $j$ 个左括号未匹配时，生成括号字符串的方式数量。

然后，我们从左到右遍历字符串 $S$ 的每个字符，同时更新 $dp$ 数组。

**状态转移方程如下：**

1. 如果当前字符是左括号 ``(``，那么会多一个左括号没有匹配，所以我们将 $dp_{i,j}$ 更新为 $dp_{i-1,j-1}$。

2. 如果当前字符是右括号 ``)``，那么它可以匹配一个左括号，所以我们将 $dp_{i,j}$ 更新为 $dp_{i-1,j+1}$。

3. 如果当前字符是问号 ``?``，那么它可以作为左括号或右括号使用，两种情况都要考虑，因此，我们将 $dp_{i,j}$ 更新为 $dp_{i-1,j-1} + dp_{i-1,j+1} \bmod 998244353$。

最终，$dp_{n,0}$ 就是我们的答案，因为括号字符串肯定是都匹配了的，所以第二维是 $0$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3030,mod=998244353;
inline ll read(){ //快读 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){ //快输 
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
char s[N];
ll n;
ll dp[N][N];
int main(){
    cin>>s;
    n=strlen(s);
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
        	if(s[i-1]=='('||s[i-1]=='?'){
        		if(j>0)
        		  dp[i][j]=(dp[i][j]+dp[i-1][j-1])%mod;
			}
        	if(s[i-1]==')'||s[i-1]=='?')
        	  dp[i][j]=(dp[i][j]+dp[i-1][j+1])%mod;
        }
    }
    write(dp[n][0]);
    return 0;
}
```



---

## 作者：TernaryTree (赞：1)

令 $1$ 表示左括号，$-1$ 表示右括号，$0$ 表示问号。

$f_{i,j}$ 表示 $1\sim i$ 前缀和为 $j$ 的方案数。

则 

$$
f_{i,j}=
\begin{cases}
f_{i-1,j-1} &(s_i=1)\\
f_{i-1,j+1} &(s_i=-1)\\
f_{i-1,j-1}+f_{i-1,j+1} &(s_i=0)
\end{cases} 
$$

不用考虑 $j$ 为负数的情况，因为合法括号序列的前缀和非负。

$\Theta(n^2)$。

---

## 作者：Mr_Biantainne (赞：0)

# ABC312D题解
### 备注
本文中的 $|S|$ 表示字符串 $S$ 的长度。
## 题意简述
给出一个仅包含 `(`、`)` 和 `?` 的字符串 $S$，每个 `?` 都需要替换成 `(` 或 `)`，求有多少种方案使得最终的替换结果合法，答案对 $998244353$ 取模。
## 解法介绍
由于 $|S|$ 只有 $3000$，因此考虑使用动态规划。

设状态 $f_{i,j}$ 表示现在操作执行到第 $i$ 个字符，操作中 `(` 的数量减去 `)` 的数量等于 $j$。

显然，在操作过程中，如果 $j < 0$，则说明不合法。

初始化 $f_{0,0} = 1$（未开始操作时只有一种结果）。

状态转移分为三种情况：
- 若 $s_i$ 为 `(`，则下一个状态使用的是第 $i + 1$ 个字符，左括号多使用了一个，是 $j + 1$，因此转移方程为 $f_{i + 1, j + 1} \gets f_{i + 1, j + 1} + f_{i, j}$。
- 若 $s_i$ 为 `)`，则下一个状态使用的是第 $i + 1$ 个字符，右括号多使用了一个，是 $j - 1$，因此转移方程为 $f_{i + 1, j - 1} \gets f_{i + 1, j - 1} + f_{i, j}$。**注意 $j = 0$ 时不能进行此操作。**
- 若 $s_i$ 为 `?`，则前两种状态转移操作都要执行。


$i, j$ 在 $[0, |s| - 1]$ 中跑一遍，最终答案为 $f_{|S|,0}$（操作完成后 `(` 和 `)` 的数量应当一样多）。
### 注意事项
操作时要取模！
## 代码
```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
string s;
ll f[3005][3005];
const ll mod = 998244353;
int main()
{
    cin >> s;
    f[0][0] = 1;
    for (ll i = 0; i < s.size(); i++)
    {
        for (ll j = 0; j < s.size(); j++)
        {
            if (s[i] == '(') f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j]) % mod;
            else if (s[i] == ')')
            {
                if (j) f[i + 1][j - 1] = (f[i + 1][j - 1] + f[i][j]) % mod;
            }
            else
            {
                f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j]) % mod;
                if (j) f[i + 1][j - 1] = (f[i + 1][j - 1] + f[i][j]) % mod;
            }
        }
    }
    cout << f[s.size()][0];
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑 DP。

定义 $f_{i,j}$ 表示第 $i$ 位未匹配的括号数量为 $j$。则有如下两种情况：

1. 是左括号：由于这是目前的最后一位，所以一定没有与其匹配的右括号，即对于所有满足 $0 \leq j \leq len$ 都有（其中 $len$ 为字符串的长度）：$f_{i,j+1} \leftarrow f_{i,j+1} + \mathit{f}_{i,j}$。

2. 是右括号：对于所有之前有一个及以上的左括号未匹配，我们都可以与其匹配，即对于所有满足 $1 \leq j \leq len$ 都有（：$f_{i,j-1} \leftarrow f_{i,j-1} + \mathit{f}_{i,j}$。

若第 $i$ 位是左右括号，那么我们只需要分上面两种情况讨论；若第 $i$ 位是问号，那么上面的两种情况我们是都需要讨论一下的。最后的答案就是 $f_{len,0}$，即全部匹配的方案数。

注：要取模。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e3+10;
const int p=998244353;
string s;
int f[N][N];
void solve(){
	cin>>s;
	f[0][0]=1;
	for(int i=0;i<s.size();i++){
		if(s[i]=='('){
			for(int j=0;j<s.size();j++){
				f[i+1][j+1]=(f[i+1][j+1]+f[i][j])%p;
			}
		}
		else if(s[i]==')'){
			for(int j=1;j<s.size();j++){
				f[i+1][j-1]=(f[i+1][j-1]+f[i][j])%p;
			}		
		}
		else{
			for(int j=0;j<s.size();j++){
				f[i+1][j+1]=(f[i+1][j+1]+f[i][j])%p;
			}		
			for(int j=1;j<s.size();j++){
				f[i+1][j-1]=(f[i+1][j-1]+f[i][j])%p;
			}	
		}
	}
	cout<<f[s.size()][0];
}
signed main(){
	solve();
	return 0;
}
```


---

## 作者：Dream_poetry (赞：0)

### 大致思路：
一道 DP。

该题 DP 转移方程如下：

- 当第 $i$ 个字符为左括号时，$dp_{i,j}\leftarrow dp_{i,j}+dp_{i-1,j-1}$。

- 当第 $i$ 个字符为右括号时，$dp_{i,j}\leftarrow dp_{i,j}+dp_{i-1,j+1}$。

- 当第 $i$ 个字符为问号时，将以上两种均做即可。

设 $dp_{i,j}$ 表示前 $i$ 个字符确定好时，左括号数量减去右括号数量的个数为 $j$ 的情况总数。答案即为 $dp_{n,0}$。

知道了动态转移方程，接下来直接写代码即可。

**注意：一定要取模！~~赛时因为没取模卡了老久还不知道错在哪。~~**

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int mod=998244353;
ll dp[3001][3001];
char s[3005];
int n;
inline void Add(ll &a,ll b){
    (a+=b)%=mod;
}
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    dp[0][0]=1;
    for(int i=1;i<=n;i++) for(int j=0;j<i;j++)
    {
        if(s[i]!='('&&j) Add(dp[i][j-1],dp[i-1][j]);
        if(s[i]!=')') Add(dp[i][j+1],dp[i-1][j]);
    }
    printf("%lld",dp[n][0]);
    return 0;
}
```


---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定一个由左括号，右括号和问号这三种字符组成的串，问号可以换作左括号或右括号。问换完所有问号后能形成的合法括号序列有多少种，对 $998244353$ 取模。

## 思路

经典 `dp` 题。

容易知道合法括号序列的每一个前缀子串都满足左括号数量大于等于右括号数量且该括号序列总的左括号数量等于右括号数量。

设 $dp_{i,j}$ 表示前 $i$ 个字符确定后左括号数量减去右括号数量的个数为 $j$ 的情况总数。则答案即为 $dp_{n,0}$。

下面考虑状态转移。

当第 $i$ 个字符为左括号时，$dp_{i,j}\leftarrow dp_{i,j}+dp_{i-1,j-1}$。

当第 $i$ 个字符为右括号时，$dp_{i,j}\leftarrow dp_{i,j}+dp_{i-1,j+1}$

当第 $i$ 个字符为问号时则以上两种转移都做。

## 代码

注意几个特判。

```cpp
string s;
ll n,dp[3005][3005];
int main(){
	IOS
	cin>>s;
	n=s.size();
	dp[1][1]=1;
	if(s[0]==')'||s[n-1]=='('||(n%2))over(0)
	for(int i=2;i<=n;i++){
		if(s[i-1]!=')'){
			for(int j=1;j<=i;j++)dp[i][j]=(dp[i][j]+dp[i-1][j-1])%mod;
		}
		if(s[i-1]!='('){
			for(int j=0;j<=i-2;j++)dp[i][j]=(dp[i][j]+dp[i-1][j+1])%mod;
		}
	}
	over(dp[n][0])
}
```


---

