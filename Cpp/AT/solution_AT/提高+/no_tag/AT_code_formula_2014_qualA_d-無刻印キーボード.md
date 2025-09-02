# 無刻印キーボード

## 题目描述

高桥君非常喜欢无标记键盘。今天，他计划在一个只标有字母和数字的键盘上输入一段文字。

不过高桥君并没有完全记住键盘的布局。对于他记得的字符，可以直接敲击对应的键；对于不记得的字符，则必须随机敲击按键，如果按错了，就要用退格键来删除。

他希望输入一串文本 $S$，且希望敲击键盘的次数尽可能少。他可以根据之前按下的键对应的字符来记忆信息，并在下次选择按键时进行优化。

请计算高桥君在使用最优策略下，每次键击的期望次数。

假设高桥君记住了退格键的位置，以及所有非字母和数字的键的位置。另外，不允许使用方向键或鼠标等改变输入位置的操作。

## 样例 #1

### 输入

```
takahashikun
1234567890abcdefghijklmnopqrstuvwxyz```

### 输出

```
12```

## 样例 #2

### 输入

```
p
1234567890abcdefghijklmnorstuvwxyz```

### 输出

```
2```

# 题解

## 作者：_zzzzzzy_ (赞：0)

## 思路
我们可以发现给给定数组离散化求问题是没有变化的，只是把重复的按一遍就行了，然后知道的字母数字也是可以删去的。

所以我们就把这个字符串变成了一个长度为 $k$ 的不重复的字符串，那么就不用字符串了，因为没有区别，我们设 $dp_{i,j}$ 表示要打的并且不知道字符串长度是 $i$，别的不知道，也不用打的个数为 $j$ 个。

那么我们可以分类转移，我们考虑一次就是我们要的的贡献是 $\frac{dp_{i-1,j}+1}{i+j}$，表示在 $i+j$ 隔离选出来一个的期望贡献，然后考虑选的不是下一个，但是是后面要打的，我们可以先删掉这个字母，然后先打后面的，因为到那里的时候打，和先打是没有区别的，那么贡献就是 $\frac{dp_{i-1,j}+3}{i+j}(i-1)$，表示有 $i-1$ 种这样的贡献，最后就是打出来的是不用打但是不知道的，我们答案就是 $\frac{dp_{i,j-1}+2}{i+j}j$，那么这样记忆化搜索就行了。

## 代码

```cpp
// Problem: 無刻印キーボード
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_code_formula_2014_qualA_d
// Memory Limit: 64 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (r); i >= (l); i--)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using i64 = long long;
const int maxn = 200;
char s[maxn], t[maxn];
double dp[maxn][maxn];
int n, m;
double solve(int a, int b) {
	double res = 0;
	if (dp[a][b] != -1) {
		return dp[a][b];
	}
	if (a == 0) {
		return dp[a][b] = 0;
	}
	res += (solve(a - 1, b) + 1) / (a + b);
	res += (solve(a - 1, b) + 3) / (a + b) * (a - 1);
	if (b != 0) {
		res += (solve(a, b - 1) + 2) / (a + b) * b;
	}
	return dp[a][b] = res;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	cin >> (s + 1) >> (t + 1);
	n = (int)strlen(s + 1), m = (int)strlen(t + 1);
	rep(i, 0, 199) {
		rep(j, 0, 199) {
			dp[i][j] = -1;
		}
	}
  double ans = 0, a = 0, b = 0;
  rep(i, 1, n) {
  	bool flag = 0;
  	rep(j, 1, m) {
  		if (t[j] == s[i]) {
  			flag = 1;
  			break;
  		}
  	}
  	if (flag == 1) {
  		ans++;
  		continue;
  	}
  	rep(j, 1, i - 1) {
  		if (s[i] == s[j]) {
  			flag = 1;
  			break;
  		}
  	}
  	if (flag == 1) {
  		ans++;
  		continue;
  	}
  	a++;
  }
  b = 36 - m - a;
  ans += solve(a, b);
  cout << setprecision(10) << fixed << ans << "\n";
	return 0;
}
```

---

