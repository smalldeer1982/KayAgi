# [ARC055C] ABCAC

## 题目描述

有一个字符串 $s$，你需要找到所有满足如下拆分方法的方法总数：

你需要将 $s$ 分成 $5$ 个字符串，使得第 $1$ 个字符串和第 $4$ 个字符串完全相同，都是 $A$ 字符串；第 $3$ 个字符串和第 $5$ 个字符串完全相同，都是 $C$ 字符串。第 $2$ 个字符串（即 $B$ 字符串）与他们都不相同。

即题目标题中所说的 `ABCAC`。

## 样例 #1

### 输入

```
takaitai
```

### 输出

```
2
```

## 样例 #2

### 输入

```
aaaaaaaaaa
```

### 输出

```
6
```

## 样例 #3

### 输入

```
abcabc
```

### 输出

```
0
```

# 题解

## 作者：Register_int (赞：0)

首先将串分割为 $\verb!ABC\AC!$ 的形式，则 $\verb!A!$，$\verb!C!$ 分别为这两个串的一个公共前后缀。求出两个串的最长公共前后缀后，可以直接计算符合的方案数。前后缀跑个 exkmp 就可以了，时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

inline 
void getz(char *s, int *z, int n) {
	z[1] = n;
	for (int i = 2, l = 0, r = 0; i <= n; i++) {
		if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
		for (; i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]; z[i]++);
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}

int z1[MAXN], z2[MAXN];

int n; char s[MAXN], t[MAXN];

ll ans;

int main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	for (int i = n; i; i--) t[i] = s[n - i + 1];
	getz(s, z1, n), getz(t, z2, n);
	for (int i = 2; i <= n; i++) {
		if (i - 1 <= n - i + 1) continue;
		z1[i] = min(z1[i], n - i), z2[n - i + 2] = min(z2[n - i + 2], n - i);
		ans += max(0, z1[i] + z2[n - i + 2] - n + i);
	}
	printf("%lld", ans);
}
```

---

