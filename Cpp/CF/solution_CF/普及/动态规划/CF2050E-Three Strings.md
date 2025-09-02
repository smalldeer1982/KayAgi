# Three Strings

## 题目描述

You are given three strings: $ a $ , $ b $ , and $ c $ , consisting of lowercase Latin letters. The string $ c $ was obtained in the following way:

1. At each step, either string $ a $ or string $ b $ was randomly chosen, and the first character of the chosen string was removed from it and appended to the end of string $ c $ , until one of the strings ran out. After that, the remaining characters of the non-empty string were added to the end of $ c $ .
2. Then, a certain number of characters in string $ c $ were randomly changed.

For example, from the strings $ a=\color{red}{\text{abra}} $ and $ b=\color{blue}{\text{cada}} $ , without character replacements, the strings $ \color{blue}{\text{ca}}\color{red}{\text{ab}}\color{blue}{\text{d}}\color{red}{\text{ra}}\color{blue}{\text{a}} $ , $ \color{red}{\text{abra}}\color{blue}{\text{cada}} $ , $ \color{red}{\text{a}}\color{blue}{\text{cada}}\color{red}{\text{bra}} $ could be obtained.

Find the minimum number of characters that could have been changed in string $ c $ .

## 样例 #1

### 输入

```
7
a
b
cb
ab
cd
acbd
ab
ba
aabb
xxx
yyy
xyxyxy
a
bcd
decf
codes
horse
codeforces
egg
annie
egaegaeg```

### 输出

```
1
0
2
0
3
2
3```

# 题解

## 作者：OIerWu_829 (赞：5)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF2050E) / [Codeforces](https://codeforces.com/contest/2050/problem/E)

原来这题还可以写题解的吗，赶紧来一篇。

---

赛时思路，可能比较麻烦。

我们设 $f_{i,j}$ 表示使用 $a$ 的前 $i$ 个字符和 $b$ 的前 $j$ 个字符构造出 $c$ 的前 $i+j$ 个字符时，最少需要改变的字符数量。

+ 如果 $i=0$ 并且 $j=0$，则没有字符可以用来构造 $c$，跳过。
+ 如果 $i=0$，意味着只用 $b$ 的字符来构造 $c$，因此只需要检查 $b$ 的第 $j-1$ 个字符是否与 $c$ 的第 $j-1$ 个字符相等，所以 $f_{i,j}=f_{i,j-1}+[b_{j-1}\ne c_{j-1}]$。
+ 如果 $j=0$，意味着只用 $a$ 的字符来构造 $c$，因此只需要检查 $a$ 的第 $i-1$ 个字符是否与 $c$ 的第 $i-1$ 个字符相等，所以 $f_{i,j}=f_{i-1,j}+[a_{i-1}\ne c_{i-1}]$。
+ 对于其他情况，取决于两个选择的最小值：
  + 从 $a$ 中取出第 $i-1$ 个字符，检查它是否与当前 $c$ 的字符匹配。
  + 从 $b$ 中取出第 $j-1$ 个字符，检查它是否与当前 $c$ 的字符匹配。
  + 所以 $f_{i,j}=\min(f_{i-1,j}+[a_{i-1}\ne c_{i+j-1}],f_{i,j-1}+[b_{j-1}\ne c_{i+j-1}])$。

最终答案是 $f_{n,m}$，其中 $n$ 和 $m$ 分别代表字符串 $a$ 和 $b$ 的长度。**记得多测清空！**

```cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 5;

int f[N][N];

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		string a, b, c;
		cin >> a >> b >> c;
		int n = a.size(), m = b.size();
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++)
				f[i][j] = 0;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++)
			{
				if (i == 0 && j == 0) continue;
				else if (i == 0) f[i][j] = f[i][j - 1] + (b[j - 1] != c[j - 1]);
				else if (j == 0) f[i][j] = f[i - 1][j] + (a[i - 1] != c[i - 1]);
				else f[i][j] = min(f[i - 1][j] + (a[i - 1] != c[i + j - 1]), f[i][j - 1] + (b[j - 1] != c[i + j - 1]));
			}
		cout << f[n][m] << "\n";
	}
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：3)

考虑 DP。

设 $dp_{i,j}$ 为字符串 $a$ 的前 $i$ 个字符和字符串 $b$ 的前 $j$ 个字符组成字符串 $c$ 的前 $i+j$ 个字符的最少替换次数。

如果这个字符来源于字符串 $a$，当这个字符是目标字符时，$dp_{i,j} = dp_{i-1,j}$，否则为 $dp_{i,j} = dp_{i-1,j} + 1$。

如果这个字符来源于字符串 $b$，当这个字符是目标字符时，$dp_{i,j} = dp_{i,j-1}$，否则为 $dp_{i,j} = dp_{i,j-1} + 1$。

对于以上两种情况取最小值即可。

不要忘了初始化。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2005;
const int inf = 1e16;
int T,n,m;
int dp[N][N];
string a,b,c;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> a >> b >> c;
	n = a.size(),m = b.size();
	for (int i = 0 ; i <= n ; i++)
		for (int j = 0 ; j <= m ; j++)
			dp[i][j] = inf;
	dp[0][0] = 0;
	for (int i = 1 ; i <= n ; i++)
		dp[i][0] = dp[i - 1][0] + (a[i - 1] != c[i - 1]);
	for (int i = 1 ; i <= m ; i++)
		dp[0][i] = dp[0][i - 1] + (b[i - 1] != c[i - 1]);
    // 初始化
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++)
			dp[i][j] = min(dp[i - 1][j] + (a[i - 1] != c[i + j - 1]),dp[i][j - 1] + (b[j - 1] != c[i + j - 1]));
	cout << dp[n][m] << endl;
}
signed main(){
	close();
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Drifty (赞：2)

### Solution

简单 DP 题。

我们记 $f_{i, j}$ 为用了 $a$ 的前 $i$ 个字符，用了 $b$ 的前 $j$ 个字符最多能匹配上 $c$ 的字符个数。

对于每一个决策 $(i,j)$，要么是从 $(i - 1,j)$ 取了 $a$ 中一个字符转移过来的，要么是从 $(i,j - 1)$  取了 $b$ 中一个字符转移过来的。

因此我们有转移：

$$
f_{i,j} = \max \left \{
f_{i - 1,j} + \left [a_i = c_{i + j}\right ], f_{i, j - 1} + \left [b_j = c_{i + j}\right ]
\right \}
$$

然后处理下边界直接转移就好。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using Vector = vector <int>;
int T, x, y, z;
void solve() {
    string a, b, c;
    cin >> a >> b >> c;
    x = a.size(), y = b.size(), z = c.size();
    vector <Vector> f(x + 1, Vector(y + 1, 0));
    for (int i = 1; i <= x; i ++) f[i][0] = f[i - 1][0] + (c[i - 1] == a[i - 1]);
    for (int i = 1; i <= y; i ++) f[0][i] = f[0][i - 1] + (c[i - 1] == b[i - 1]);
    if (a[0] == c[0]) f[1][0] = 1;
    if (b[0] == c[0]) f[0][1] = 1;
    for (int i = 1; i <= x; i ++) {
        for (int j = 1; j <= y; j ++) {
            f[i][j] = max(f[i - 1][j] + int(c[i + j - 1] == a[i - 1]), 
                          f[i][j - 1] + int(c[i + j - 1] == b[j - 1]));
        }
    }
    cout << z - f[x][y] << '\n';
}
int main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    cin >> T;
    while (T --) solve();
    return 0;
}

```

---

## 作者：_Lazy_whr_ (赞：0)

显而易见的 DP。

我们可以定义 $dp_{i, j}$ 表示用了 $s1$ 的前 $i$ 个字符和 $s2$ 的前 $j$ 个字符所组成的字符串最少改变几次能与 $t$ 的前 $i + j$ 个字符相同。

**初始状态**：$dp_{0, 0} = 0$。

**状态转移方程**：$dp_{i, j} = \min(dp_{i - 1, j} + (s1_i \neq t_{i + j}), dp_{i, j - 1} + (s2_j \neq t_{i + j}))$。

**答案**：$dp_{n, m}$。

# AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define x0 x00
#define x1 x10
#define y0 y00
#define y1 y10
#define rep(i, l, r, x) for (int i = l; i <= r; i += x)
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 20), stdin), p1 == p2) ? EOF : *p1++)
// #pragma GCC target("avx")
// #pragma GCC optimize(3,"Ofast","inline")
namespace FastIO {
	char buf[(1 << 20)], *p1, *p2;
	char pbuf[(1 << 20)], *pp;
	inline int read() {
		int x = 0, f = 1;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	
	template <typename T> inline void read (T &x) { x = read(); }
	
	template <typename T, typename... Args> inline void read (T &x, Args &...x_) {
		read (x);
		read (x_...);
	}
}

namespace Constants {
	const int INF = 1e18;
	const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	const double EPS = 1e-7;
	const double PI = acos (-1);
}

using namespace std;
using namespace FastIO;
using namespace Constants;

const int N = 1010;

string s1, s2, t;

int dp[N][N];
// dp[i][j] : 用了 s1 的前 i 个字符和 s2 的前 j 个字符所组成的字符串最少改变几次能与 t 的前 i + j 个字符相同

void Solve() {
	cin >> s1 >> s2 >> t;
	int n = s1.size(), m = s2.size();
	s1 = " " + s1; s2 = " " + s2; t = " " + t;
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) dp[i][j] = INF; // 别忘了初始化为正无穷
	}

	dp[0][0] = 0;
  // 注意要从 0 开始枚举，因为可以不取
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j] + (s1[i] != t[i + j]));
			if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1] + (s2[j] != t[i + j]));
		}
	}

	cout << dp[n][m] << endl;
}

main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	int T = 1;
	cin >> T;
	while (T--) Solve();

	return 0;
}

```

总的来说，是一道很简单的 DP 题。

---

## 作者：GreenMelon (赞：0)

设使用了字符串 $a$ 的前 $i$ 个字符，使用了字符串 $b$ 的前 $j$ 个字符。

如果不截取字符串 $a$ 的任何字符（即 $i=0$），改变次数将为 $dp_{i, j-1}+(b_j\not= c_{i+j})$。其中，$dp_{0, j-1}$ 代表当 $a$ 不截取任何字符，$b$ 截取钱前 $j-1$ 个字符时所需要改变的次数，$b_j\not= c_{i+j}$ 代表插入后是否需要进一步修改字符。

如果不截取字符串 $b$ 的任何字符（即 $j=0$），改变次数将为 $dp_{i-1, j}+(a_i\not= c_{i+j})$。原理同上。

如果 $i$ 和 $j$ 都大于 $0$，就从 $dp_{i, j-1}+(b_j\not= c_{i+j})$ 和 $dp_{i-1, j}+(a_i\not= c_{i+j})$ 当中取最小值。

特别的，$dp_{0,0}$ 值为 $0$，因为空字符串不需要任何操作。

最后提炼出转移方程：

$$dp_{i,j}= \begin{cases} 
0&i=j=0\\
dp_{i, j-1}+(b_j\not= c_{i+j})&i=0\\
dp_{i-1, j}+(a_i\not= c_{i+j})&j=0\\
\min\big[dp_{i, j-1}+(b_j\not= c_{i+j}),dp_{i-1, j}+(a_i\not= c_{i+j})\big]&i,j>0
\end{cases}$$

答案就是 $dp_{|a|, |b|}$。

注意哈，对于每个测试用例必须重新初始化数组 $dp$！

---

## 作者：O_v_O (赞：0)

# CF2050E 题解

## 题意

每次操作可以将 $a$ 或 $b$ 中的一个非空字符串的第一个字符添加到 $c$ 的末尾，求最终结果与给定 $c$ 的不同字符数量的最小值。

## 思路

**定义状态**： $dp_{i, j}$ 表示字符 $a$ 用了前 $i$ 个，字符 $b$ 用了前 $j$ 个。

**状态转移方程：**

$$
dp_{i, j} =
\begin{cases}
dp_{i, j - 1} + (b_j \not= c_{i + j}) & i = 0 \\
dp_{i - 1, j} + (a_i \not= c_{i + j}) & j = 0 \\
\min(dp_{i, j - 1} + (b_j \not= c_{i + j}), dp_{i - 1, j} + (a_i \not= c_{i + j})) & i > 0 \; j > 0
\end{cases}
$$

**初始状态：** $dp_{0, 0} = 0$

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10;

int t, dp[N][N];
string c, a, b;

void solve() {
  cin >> a >> b >> c;
  a = ' ' + a, b = ' ' + b, c = ' ' + c;
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      dp[i][j] = 0x3f3f3f3f; // 初始成最大值
    }
  }
  dp[0][0] = 0; // 初始化
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      if (i == 0 && j == 0) // 注意特判
        continue;
      if (i == 0) {
        dp[i][j] = dp[i][j - 1] + (b[j] != c[i + j]);
      } else if (j == 0) 
        dp[i][j] = dp[i - 1][j] + (a[i] != c[i + j]);
      else
        dp[i][j] = min(dp[i - 1][j] + (a[i] != c[i + j]), dp[i][j - 1] + (b[j] != c[i + j]));
    }
  }
  cout << dp[a.size() - 1][b.size() - 1] << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
/*
dp[x][y] = min(dp[x - 1][y] + (a[x] != c[x + y]), dp[x][y - 1] + (b[y] != c[x + y));
*/
```

---

## 作者：mahaorui2012 (赞：0)

# 题意

每次操作可以将 $a$ 或 $b$ 中的一个非空字符串的第一个字符添加到 $c$ 的末尾，求最终结果与给定 $c$ 的不同字符数量的最小值 

以下称由 $a$ 与 $b$ 构造出的 $c$ 为 $d$。 

# 思路

容易联想到[P2649](https://www.luogu.com.cn/problem/P2639)。

由于当前能选什么只取决于 $a$ 中已选字符的数量和 $b$ 中已选字符的总数量，且决策无后效性，考虑动态规划。

所以可以设状态 $f_{i,j}$ 为**在 $a$ 中选了 $i$ 个字符且在 $b$ 中选了 $j$ 个字符时当前的 $d$ 与 $c$ 的前 $i+j$ 位的不同字符数量最小值**。
  
易得初始状态为 $f_{0,0}=0$。

得转移方程为：

$$
f_{i,j}= \begin{cases}

\min(f_{i-1,j},f_{i,j-1}) & i>0,j>0\\
f_{i-1,j} & i>0,j=0\\
f_{i,j-1} & i=0,j>0

\end{cases}
$$  

由于 $|a|\times |b| \le 4\times 10^6$，不需要任何优化。 

注意转移顺序：先枚举 $i+j$，再枚举 $i$，此时可得 $j$。 
# AC CODE
```C++
#include <iostream>
#include <cstring>
using namespace std;

int dp[2005][2005];
char a[2005],b[2005],c[2005];

int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>(a+1)>>(b+1)>>(c+1);
		dp[0][0]=0;
		int na=strlen(a+1),nb=strlen(b+1),nc=strlen(c+1);
		for(int k=1;k<=nc;++k){
			for(int i=max(0,k-nb);i<=k && i<=na;++i){
				int j=k-i;
				if(i==0){
					dp[i][j]=dp[i][j-1]+(b[j]!=c[k]);
				}else if(j==0){
					dp[i][j]=dp[i-1][j]+(a[i]!=c[k]);
				}else{
					dp[i][j]=min(dp[i-1][j]+(a[i]!=c[k]),dp[i][j-1]+(b[j]!=c[k]));
				}
			}
		}cout<<dp[na][nb]<<'\n';
	}return 0;
}

```

---

## 作者：z_yq (赞：0)

# 题意
这道题目真的都没有人给一个翻译，挺痛苦的，对于我这种虽然有实力人肉翻译但是不想的人就很不友好。\
题目意思很简单，给出了三个字符串 $a,b,c$，而且存在 $d$ 串可以由 $a,b$ 得到，得到的方式就是每一次从 $a,b$ 两串中的任意一串取走头并加入到 $d$ 的尾，求 $c,d$ 两串最少有多少个位置是不同的。
# 做法
首先考虑如果我们是问的字典序最小怎么做。\
这个板子很容易想到就是 $dp_{i,j}$ 表示 $a$ 的前面 $i$ 个字符和 $b$ 的前面 $j$ 个字符可以取到的最小字典序。\
此时转移也很好做，$dp_{i,j}$ 就是 $dp_{i-1,j}+a_i$ 和 $dp_{i,j-1}+b_j$ 中小的那个。\
将这个东西转化成原问题，状态设计从原来的表示字典序最小变成匹配数量最多，那么状态转移也很好出来了就是 $dp_{i-1,j}+(a_i \neq c_{i+j})$ 和 $dp_{i,j-1}+(b_j \neq c_{i+j})$ 中的小的那个，最后答案就是 $dp_{n,m}$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9;
int T,dp[N][N],n,m;
string a,b,c;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>a>>b>>c;n=a.size();m=b.size();
		a=' '+a;b=' '+b;c=' '+c;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				if(i!=0 || j!=0)
				{
					if(i!=0) dp[i][j]=dp[i-1][j]+(c[i+j]!=a[i]);
					if(j!=0)
					{
						if(i!=0) dp[i][j]=min(dp[i][j],dp[i][j-1]+(c[i+j]!=b[j]));
						else dp[i][j]=dp[i][j-1]+(c[i+j]!=b[j]);
					}
				}
		cout<<dp[n][m]<<endl;
	}
	return 0;
}

```
# 总结
很版的一道题目，没有什么总结，可以用来做 DP 入门或者练手题目。

---

## 作者：songtaoran (赞：0)

类似最长公共子序列的 dp。  
状态设计：设 $f_{i,j}$ 表示用 $a$ 字符串的前 $i$ 个字符和 $b$ 字符串的前 $j$ 个字符组成的 $c$ 字符串至少需要替换多少次。  
状态转移方程：$f_{i,j} = \min(f_{i-1,j} + (a_i \ne c_{i+j}),f_{i,j-1} + (b_j \ne c_{i+j}))$。表示可以将 $a_i$ 或者 $b_i$ 添加到 $c$ 字符串的末尾。  
初始化：$f_{i,0} = f_{i - 1,0} + (a_i \ne c_i), f_{0,i} = f_{0,i - 1} + (b_i \ne c_i)$。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T, n, m, f[1010][1010];
char a[1010], b[1010], c[2010];
int main(){
	cin >> T;
	while(T--){
		scanf("%s %s %s", a + 1, b + 1, c + 1); n = strlen(a + 1); m = strlen(b + 1);
		for(ll i = 0; i <= n; i++)
			for(ll j = 0; j <= m; j++) f[i][j] = 0;
		for(ll i = 1; i <= n; i++) f[i][0] = f[i - 1][0] + (a[i] != c[i]);
		for(ll i = 1; i <= m; i++) f[0][i] = f[0][i - 1] + (b[i] != c[i]);
		for(ll i = 1; i <= n; i++)
			for(ll j = 1; j <= m; j++)
				f[i][j] = min(f[i - 1][j] + (a[i] != c[i + j]), f[i][j - 1] + (b[j] != c[i + j]));
		printf("%lld\n", f[n][m]);
	}
	return 0;
}
```
[提交记录 - $298035317$](https://codeforces.com/problemset/submission/2050/298035317)

---

