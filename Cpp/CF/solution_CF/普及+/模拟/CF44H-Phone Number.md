# Phone Number

## 题目描述

Alas, finding one's true love is not easy. Masha has been unsuccessful in that yet. Her friend Dasha told Masha about a way to determine the phone number of one's Prince Charming through arithmancy.

The phone number is divined like that. First one needs to write down one's own phone numbers. For example, let's suppose that Masha's phone number is $ 12345 $ . After that one should write her favorite digit from $ 0 $ to $ 9 $ under the first digit of her number. That will be the first digit of the needed number. For example, Masha's favorite digit is $ 9 $ . The second digit is determined as a half sum of the second digit of Masha's number and the already written down first digit from her beloved one's number. In this case the arithmetic average equals to $ (2+9)/2=5.5 $ . Masha can round the number up or down, depending on her wishes. For example, she chooses the digit $ 5 $ . Having written down the resulting digit under the second digit of her number, Masha moves to finding the third digit in the same way, i.e. finding the half sum the the third digit of her number and the second digit of the new number. The result is $ (5+3)/2=4 $ . In this case the answer is unique. Thus, every $ i $ -th digit is determined as an arithmetic average of the $ i $ -th digit of Masha's number and the $ i-1 $ -th digit of her true love's number. If needed, the digit can be rounded up or down. For example, Masha can get:

 $ 12345 $   $ 95444 $  Unfortunately, when Masha tried dialing the number, she got disappointed: as it turned out, the number was unavailable or outside the coverage area. But Masha won't give up. Perhaps, she rounded to a wrong digit or chose the first digit badly. That's why she keeps finding more and more new numbers and calling them. Count the number of numbers Masha calls. Masha calls all the possible numbers that can be found by the described means of arithmancy, except for, perhaps, her own one.

## 样例 #1

### 输入

```
12345
```

### 输出

```
48
```

## 样例 #2

### 输入

```
09
```

### 输出

```
15
```

# 题解

## 作者：一扶苏一 (赞：4)

## Solution

数数题，考虑DP。

设$f_{i,j}$是前$i$个数，第$i$个数是$j$的ans。

刷表转移显然：

$$f_{i+1,next}+=f_{i,j}$$

其中$next$是$j+a_{i+1}$的上下取整，其中$a$是原数组。

考虑那个能拼出原数就-1的限制

显然可以数位DP，设$f_{i,j,0/1}$，第三维代表前$i$位是否与原号码完全相同，但是转移比较复杂，懒癌晚期表示能不写数位DP就不写……

考虑这里没有顶上界的概念，于是我们发现可以直接用布尔量递推这一位能不能被表示为与原数码完全相同

具体的，当且仅当第$i$位是$a_i$且$i+1$位是$a_{i+1}$且$flag_i=true$时，$flag_{i+1}=true$

于是代码就变得十分好写了

## Code

```cpp
#include<cstdio>
#include<cstring>
#ifdef ONLINE_JUDGE
#define freopen(a,b,c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

template <typename T>
inline void qr(T &x) {
	rg char ch=getchar(),lst=' ';
	while((ch > '9') || (ch < '0')) lst=ch,ch=getchar();
	while((ch >= '0') && (ch <= '9')) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(lst == '-') x=-x;
}

namespace IO {
	char buf[120];
}

template <typename T>
inline void qw(T x,const char aft,const bool pt) {
	if(x < 0) {x=-x,putchar('-');}
	rg int top=0;
	do {IO::buf[++top]=x%10+'0';} while(x/=10);
	while(top) putchar(IO::buf[top--]);
	if(pt) putchar(aft);
}

const int maxn = 55;

char MU[maxn];
ll frog[maxn][11];
bool flag[maxn];

int main() {
	freopen("1.in","r",stdin);
	scanf("%s",MU+1);
	int n=strlen(MU+1);
	for(rg int i=1;i<=n;++i) MU[i]-='0';
	for(rg int i=0;i<10;++i) frog[1][i]=1;
	flag[1]=true;
	for(rg int i=1;i<n;++i) {
		rg int di=i+1;
		for(rg int j=0;j<10;++j) {
			int _temp=j+MU[di];
			int k=_temp>>1;
			if(_temp&1) frog[di][k]+=frog[i][j],frog[di][k+1]+=frog[i][j];
			else frog[di][k]+=frog[i][j];
			if((MU[i] == j) &&flag[i]) {
				if(MU[di] == k) flag[di]=true;
				else if((_temp&1) && (MU[di] == (k+1))) flag[di]=true;
			}
		}
	}
	rg ll ans=flag[n]?-1:0;
	for(rg int i=0;i<10;++i) ans+=frog[n][i];
	qw(ans,'\n',true);
	return 0;
}
```

## Summary

当限制较少时，可以通过递推另一个布尔量显著减少转移的讨论情况

---

## 作者：Juanzhang (赞：4)

一道较明显的**dp**

**思路：**

- **dp**
  - 记搜

  - 填表

  - 刷表

$dp_{i,j}$表示前$i$位，最后一位为数字$j$的方案数

**状态转移方程：**

$dp_{i,j}=dp_{i-1,2j-a_{i-1}+1}+dp_{i-1,2j-a_{i-1}}+dp_{i-1,2j-a_{i-1}-1}$

最后的答案为$\displaystyle\sum_{i=0}^9{dp_{n,i}}$

注意判断越界

**代码**

- 记搜 - 搜索+记忆化

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 60;
int n;
char str[maxn];
ll ans, dp[maxn][10];

ll dfs(int now, int last) {
	if (now == n) {
		return 1;
	}
	if (~dp[now][last]) {
		return dp[now][last];
	}
	const int t = (str[now + 1] ^ 48) + last;
	return dp[now][last] = dfs(now + 1, t >> 1) + (t & 1 ? dfs(now + 1, (t >> 1) + 1) : 0);
}

int main() {
	gets(str + 1);
	n = strlen(str + 1);
	if (n == 1) {
		return puts("9"), 0;
	}
	memset(dp, -1, sizeof dp);
	for (int i = 0; i < 10; i++) {
		ans += dfs(1, i);
	}
	for (int i = 2; i <= n; i++) {
		if (abs(str[i] - str[i - 1]) > 1) {
			break;
		}
		if (i == n) {
			ans--;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

- 填表 - 将已知用未知求出

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 60;
int n;
char str[maxn];
ll ans, dp[maxn][10];

int main() {
	gets(str + 1);
	n = strlen(str + 1);
	if (n == 1) {
		return puts("9"), 0;
	}
	fill(dp[1], dp[1] + 10, 1);
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < 10; j++) {
			int t = (j << 1) - (str[i] ^ 48);
			for (int k = -1; k < 2; k++) {
				if (t + k >= 0 && t + k < 10) {
					dp[i][j] += dp[i - 1][t + k];
				}
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		ans += dp[n][i];
	}
	for (int i = 2; i <= n; i++) {
		if (abs(str[i] - str[i - 1]) > 1) {
			break;
		}
		if (i == n) {
			ans--;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

- 刷表 - 用已知不断更新未知

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 60;
int n;
char str[maxn];
ll ans, dp[maxn][10];

int main() {
	gets(str + 1);
	n = strlen(str + 1);
	if (n == 1) {
		return puts("9"), 0;
	}
	fill(dp[1], dp[1] + 10, 1);
	for (int i = 1; i < n; i++) {
		int x = str[i + 1] ^ 48;
		for (int j = 0; j < 10; j++) {
			dp[i + 1][j + x >> 1] += dp[i][j];
			if (j + x & 1) {
				dp[i + 1][j + x + 1 >> 1] += dp[i][j];
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		ans += dp[n][i];
	}
	for (int i = 2; i <= n; i++) {
		if (abs(str[i] - str[i - 1]) > 1) {
			break;
		}
		if (i == n) {
			ans--;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：kimi0705 (赞：1)

# 思路
用 $dp_{i,j}$ 表示已经计算了前 $i$ 个字符，且第 $i$ 个字符为 $j$ 的方案数。
### Part1：基础 dp

显然的： $dp_{0,i}=1$ 。因为第一位想放什么就放什么。

其余的： $dp_{i,j}=dp_{i-1,j \times  2 - s_{i}-1}+dp_{i-1,j \times 2 - s_i}+dp_{i-1,j \times 2 - s_i+1}$
### Part2：新号码是否与原号码相同
因为：第 $i$ 个新号码 $=$（第 $i-1$ 个新号码 $+$ 第 $i$ 个老号码的和 $)\div2$ 

所以
$$\lvert s_i-(s_{i-1}+s_i)\div2\rvert\le\frac{1}{2}$$
$$\lvert s_i-s_{i-1}\rvert\le1$$
### Part3：Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[51][51], ans;
string s;
bool check() { // 判断是否会生成旧号码
	for (int i = 1; i <= s.size() ; i++) {
		if(abs(s[i] - s[i - 1] > 1)) return 0;
	}
	return 1;
}
int main() {
	cin >> s;
	for (int i = 0; i <= 9; i++) dp[0][i] = 1; // 初始值
	for (int i = 1; i < s.size(); i++) {
		for (int j = 0; j <= 9; j++) {
			if (0 <= j * 2 - s[i] + '0' && j * 2 - s[i] + '0' <= 9)
				dp[i][j] += dp[i - 1][j * 2 - s[i] + '0'] ;
			if (0 <= j * 2 - s[i] + '0' + 1 && j * 2 - s[i] + '0' + 1 <= 9)
				dp[i][j] += dp[i - 1][j * 2 - s[i] + '0' + 1] ;
			if (0 <= j * 2 - s[i] + '0' - 1 && j * 2 - s[i] + '0' - 1 <= 9)
				dp[i][j] += dp[i - 1][j * 2 - s[i] + '0' - 1] ;
		}
	}
	for (int i = 0; i <= 9; i++) ans += dp[s.size() - 1][i];
	cout << ans - check();
}
```

---

