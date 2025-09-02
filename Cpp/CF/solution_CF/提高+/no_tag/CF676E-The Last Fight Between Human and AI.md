# The Last Fight Between Human and AI

## 题目描述

100 years have passed since the last victory of the man versus computer in Go. Technologies made a huge step forward and robots conquered the Earth! It's time for the final fight between human and robot that will decide the faith of the planet.

The following game was chosen for the fights: initially there is a polynomial

 $ P(x)=a_{n}x^{n}+a_{n-1}x^{n-1}+...+a_{1}x+a_{0}, $  with yet undefined coefficients and the integer $ k $ . Players alternate their turns. At each turn, a player pick some index $ j $ , such that coefficient $ a_{j} $ that stay near $ x^{j} $ is not determined yet and sets it to any value (integer or real, positive or negative, $ 0 $ is also allowed). Computer moves first. The human will be declared the winner if and only if the resulting polynomial will be divisible by $ Q(x)=x-k $ .Polynomial $ P(x) $ is said to be divisible by polynomial $ Q(x) $ if there exists a representation $ P(x)=B(x)Q(x) $ , where $ B(x) $ is also some polynomial.

Some moves have been made already and now you wonder, is it true that human can guarantee the victory if he plays optimally?

## 说明/提示

In the first sample, computer set $ a_{0} $ to $ -1 $ on the first move, so if human can set coefficient $ a_{1} $ to $ 0.5 $ and win.

In the second sample, all coefficients are already set and the resulting polynomial is divisible by $ x-100 $ , so the human has won.

## 样例 #1

### 输入

```
1 2
-1
?
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 100
-10000
0
1
```

### 输出

```
Yes```

## 样例 #3

### 输入

```
4 5
?
1
?
1
?
```

### 输出

```
No```

# 题解

## 作者：Yuno (赞：2)

这题最关键的地方被翻译直接解决了...

整除 $x-k$ 等价于 $f(k)=0$

因为 $f(x)=g(x)(x-k)$

令 $x=k$，得到 $f(k)=0$

然后就很简单了，分两类：

1.$k=0$

2.$k\not=0$

第一类只要看 $a_0$ 即可。

第二类的话只要判断最后一步轮到谁就行了，如果已经填完了，计算多项式的值，判断是否为 $0$ 即可。

复杂度：用秦九韶算法的话是 $O(n)$，直接算也行，是 $O(n\log_2n)$

$Code:$

```cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;
#define int long long
#define robot 1
#define human 0

char s[11];
int a[100007];

inline int qp(int base, int p, int mo) {
	int res = 1;
	while (p) {
		if (p & 1) (res *= base) %= mo;
		(base *= base) %= mo;
		p >>= 1;
	}
	return res;
}

signed main() {
	std::ios::sync_with_stdio(0);
	int n, k, cnt = 0, tot = 0;
	cin >> n >> k;
	for (int i = 0; i <= n; ++ i) {
		cin >> (s + 1);
		if (s[1] == '?') {
			++ cnt;
			a[i] = 1e9;
		} else {
			++ tot;
			int flag = 1;
			if (s[1] == '-') flag = -1;
			int len = strlen(s + 1), sum = 0;
			for (int j = 1; j <= len; ++ j) {
				if (s[j] == '-') continue; 
				sum = sum * 10 + s[j] - 48;
			}
			a[i] = sum * flag;
//			cout << a[i] << '\n';
		}
	}
	bool who;
	if (tot & 1) who = human;
	else who = robot;
	if (k == 0) {
		if (a[0] == 1e9) {
			if (who == human) cout << "Yes\n";
			else cout << "No\n";
		} else {
			if (a[0] != 0) {
				cout << "No\n";
			} else {
				cout << "Yes\n";
			}
		}
		return 0;
	}
	if (tot == n + 1) {
		int p = 998244353, sum = 0;
		for (int i = 0; i <= n; ++ i) sum = (sum + (a[i] + p) % p * qp(k, i, p) % p + p) % p;
		if (sum) {
			cout << "No\n";
			return 0;
		}
		p = 1e9 + 7, sum = 0;
		for (int i = 0; i <= n; ++ i) sum = (sum + (a[i] + p) % p * qp(k, i, p) % p + p) % p;
		if (sum) {
			cout << "No\n";
			return 0;
		}
		p = 1e9 + 9, sum = 0;
		for (int i = 0; i <= n; ++ i) sum = (sum + (a[i] + p) % p * qp(k, i, p) % p + p) % p;
		if (sum) {
			cout << "No\n";
			return 0;
		}
		cout << "Yes\n";
		return 0;
	}
	if (cnt & 1) {
		if (who == human) cout << "Yes\n";
		else cout << "No\n";
	} else {
		if (who == robot) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
} 
```

$date:2020.9.24$

---

## 作者：subcrip (赞：0)

直接大力分讨。

当 $k\ne0$ 时，设$B(x)=\sum_{i=0}^n b_ix^i$，则有 $b_{i-1}-kb_i=a_i$ 恒成立，也就是说每个 $b_i$ 可以递推得到。这说明最后一个填数的人决定人类是否获胜。如果没有不确定的数，则直接通过递推式进行验证即可。

当 $k=0$ 时，如果 $a_0$ 不确定，则电脑肯定想把它填成非 $0$ 的值，这样人类就直接输了，而人类想把它填成 $0$，这种情况就取决于谁进行下一个操作；如果 $a_0$ 确定，则直接检查它是否为 $0$ 即可。

注意那个递推式可能爆 `long long`，所以在 $b_i$ 已经非常大的时候可以直接判定人类会输。

```cpp
void solve() {
	read(int, n, k);
	readvec(string, a, n + 1);

	int q = count(a.begin(), a.end(), "?");
	if (k == 0) {
		if (a[0] == "?") {
			if (((n + 1) - q) % 2 == 0) {
				cout << "No\n";
			} else {
				cout << "Yes\n";
			}
		} else {
			if (a[0] == "0") {
				cout << "Yes\n";
			} else {
				cout << "No\n";
			}
		}
	} else {
		if (q != 0) {
			if (n % 2 == 1) {
				cout << "Yes\n";
			} else {
				cout << "No\n";
			}
		} else {
			int128 b = 0;
			for (int i = n; i; --i) {
				b = stoi(a[i]) + k * b;
				if (b > 1e17 or b < -1e17) {
					cout << "No\n";
					return;
				}
			}
			if (stoi(a[0]) == -k * b) {
				cout << "Yes\n";
			} else {
				cout << "No\n";
			}
		}
	}
}
```

---

