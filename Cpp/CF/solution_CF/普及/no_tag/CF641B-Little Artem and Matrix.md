# Little Artem and Matrix

## 题目描述

有一个 $n \times m$ 的矩阵，Artem 对它进行了 $q$ 次操作，每次操作一定属于下列三种中的一种：

- $1 \  r$，代表对于第 $r$ 行，第一个数挪到最后一个，第二个数挪到第一个，第三个数挪到第二个，以此类推，直到最后一个数挪到倒数第二个。

- $2 \  c$，代表对于第 $c$ 列，第一个数挪到最后一个，第二个数挪到第一个，第三个数挪到第二个，以此类推，直到最后一个数挪到倒数第二个。

- $3 \  r \  c \  x$，代表查询此时第 $r$ 行第 $c$ 列的数的值，结果为 $x$。

现在 Artem 记得这 $q$ 次操作，但不记得原来的矩阵是什么样子，请你帮他还原出这个矩阵，只要与操作不矛盾即可。

## 样例 #1

### 输入

```
2 2 6
2 1
2 2
3 1 1 1
3 2 2 2
3 1 2 8
3 2 1 8
```

### 输出

```
8 2 
1 8 
```

## 样例 #2

### 输入

```
3 3 2
1 2
3 2 2 5
```

### 输出

```
0 0 0 
0 0 5 
0 0 0 
```

# 题解

## 作者：OIerWu_829 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF641B)

既然要求出最开始的矩阵，那我们可以倒推。

从第 $q$ 次操作开始，按题意模拟操作就可以了。总感觉评黄有点高……

```cpp
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
const int M = 1e3 + 10;
int opt[N], h[N], l[N], a[N];
int ans[M][M];
int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= q; i++) {
        cin >> opt[i];
        if (opt[i] == 1) cin >> h[i];
        else if (opt[i] == 2) cin >> l[i];
        else cin >> h[i] >> l[i] >> a[i];
    }
    for (int k = q; k >= 1; k--)
        if (opt[k] == 1) {
            int pos = ans[h[k]][m];
            for (int i = m; i > 1; i--)
                ans[h[k]][i] = ans[h[k]][i - 1];
            ans[h[k]][1] = pos;
        } else if (opt[k] == 2) {
            int pos = ans[n][l[k]];
            for (int i = n; i > 1; i--)
                ans[i][l[k]] = ans[i - 1][l[k]];
            ans[1][l[k]] = pos;
        } else
            ans[h[k]][l[k]] = a[k];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cout << ans[i][j] << " \n"[j == m];
    return 0;
}
```

---

## 作者：oddy (赞：1)

# 题意翻译

## 题目描述

有一个 $n \times m$ 的矩阵，Artem 对它进行了 $q$ 次操作，每次操作一定属于下列三种中的一种：

- $1 \  r$，代表对于第 $r$ 行，第一个数挪到最后一个，第二个数挪到第一个，第三个数挪到第二个，以此类推，直到最后一个数挪到倒数第二个。

- $2 \  c$，代表对于第 $c$ 列，第一个数挪到最后一个，第二个数挪到第一个，第三个数挪到第二个，以此类推，直到最后一个数挪到倒数第二个。

- $3 \  r \  c \  x$，代表查询此时第 $r$ 行第 $c$ 列的数的值，结果为 $x$。

现在 Artem 记得这 $q$ 次操作，但不记得原来的矩阵是什么样子，请你帮他还原出这个矩阵，只要与操作不矛盾即可。

## 输入格式

第一行，三个整数，分别代表 $n$，$m$，$q$。

接下来 $q$ 行，每行输入上述的一个操作。

## 输出格式

输出原来的矩阵。如果有多组解，输出任意一组即可。

# 解题思路

简单的模拟，按照题意倒推即可。细节会注释在代码上。

# 代码

```cpp
#include <cstdio>

int n, m, q, a[101][101], t[10001], r[10001], c[10001], x[10001];
// t 数组存储操作类型

void row(int k) // 操作 1
{
	int tmp = a[k][m]; // 先用临时变量记录最后一个数，因为它待会要被覆盖掉
	for (int i = m; i >= 2; i--)
		a[k][i] = a[k][i - 1];
	a[k][1] = tmp; // 最后单独把临时变量赋给第一个数
}

void column(int k) // 操作 2
{
	int tmp = a[n][k]; // 同理
	for (int i = n; i >= 2; i--)
		a[i][k] = a[i - 1][k];
	a[1][k] = tmp;
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= q; i++)
	{
		scanf("%d", t + i);
		if (t[i] == 1) scanf("%d", r + i);
		if (t[i] == 2) scanf("%d", c + i);
		if (t[i] == 3) scanf("%d%d%d", r + i, c + i, x + i);
	}
	for (int i = q; i >= 1; i--) // 倒推
	{
		if (t[i] == 1) row(r[i]);
		if (t[i] == 2) column(c[i]);
		if (t[i] == 3) a[r[i]][c[i]] = x[i]; // 查询时第 r 行第 c 列是 x
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

