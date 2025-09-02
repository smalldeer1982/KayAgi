# Dasha and cyclic table

## 题目描述

Dasha is fond of challenging puzzles: Rubik's Cube $ 3×3×3 $ , $ 4×4×4 $ , $ 5×5×5 $ and so on. This time she has a cyclic table of size $ n×m $ , and each cell of the table contains a lowercase English letter. Each cell has coordinates $ (i,j) $ ( $ 0<=i&lt;n $ , $ 0<=j&lt;m $ ). The table is cyclic means that to the right of cell $ (i,j) $ there is the cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/a5d005af310d530b73654f2e5c374c68f16d2ee4.png), and to the down there is the cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/1a381522c9ac4a424562398196989e9e4585022e.png).

Dasha has a pattern as well. A pattern is a non-cyclic table of size $ r×c $ . Each cell is either a lowercase English letter or a question mark. Each cell has coordinates $ (i,j) $ ( $ 0<=i&lt;r $ , $ 0<=j&lt;c $ ).

The goal of the puzzle is to find all the appearance positions of the pattern in the cyclic table.

We say that the cell $ (i,j) $ of cyclic table is an appearance position, if for every pair $ (x,y) $ such that $ 0<=x&lt;r $ and $ 0<=y&lt;c $ one of the following conditions holds:

- There is a question mark in the cell $ (x,y) $ of the pattern, or
- The cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/54ce001d702da711f4c8fe98e24e25993cb660d2.png) of the cyclic table equals to the cell $ (x,y) $ of the pattern.

Dasha solved this puzzle in no time, as well as all the others she ever tried. Can you solve it?.

## 样例 #1

### 输入

```
5 7
qcezchs
hhedywq
wikywqy
qckrqzt
bqexcxz
3 2
??
yw
?q
```

### 输出

```
0000100
0001001
0000000
0000000
0000000
```

## 样例 #2

### 输入

```
10 10
fwtoayylhw
yyaryyjawr
ywrdzwhscy
hnsyyxiphn
bnjwzyyjvo
kkjgseenwn
gvmiflpcsy
lxvkwrobwu
wyybbcocyy
yysijsvqry
2 2
??
yy
```

### 输出

```
1000100000
0000000001
0001000000
0000010000
0000000000
0000000000
0000000000
0100000010
1000000001
0000010000
```

## 样例 #3

### 输入

```
8 6
ibrgxl
xqdcsg
okbcgi
tvpetc
xgxxig
igghzo
lmlaza
gpswzv
1 4
gx??
```

### 输出

```
000100
000001
000000
000000
010001
000000
000000
000000
```

# 题解

## 作者：素质玩家孙1超 (赞：6)

没有题解，那我就来写一篇好了。本文的所有暴力代码部分若有错误，欢迎指出。

题意：

$A$矩阵（$size(A)=n \times m$，仅含'a'-'z'）在整个平面做周期延拓，问$B$矩阵（$size(B)=r \times c$，包含'a'-'z'及'?'，'?'为通配符）在哪些位置能与$A$矩阵匹配。输出$n \times m$的01矩阵，1表示在该位置匹配。

其中 $ n,m \leq 500$。

如果不怎么好理解可以结合样例看看。

---

朴素的思想大概就是对于每一个点暴力匹配，是 $O(n^4)$ 的

代码大致如下：

```cpp
for (int i=1;i<=n;i++)
for (int j=1;j<=m;j++)
{
	bool _=1;
	for (int k=0;k<r;k++)
	for (int l=0;l<c;l++)
		_&=(A[(i+k)%n][(j+l)%m]==B[k][l]|B[k][l]=='?');
	ans[i][j]=1;
}

```

我们可以稍加思考 $O(n^4)$ 而本题时限 6s ，大概可以过 $n=100$ 多一点的点。但在数量级上已经和 $n=500$ 差不多了。

而当你看到最底层的运算是 `&` 这个运算时，就容易想到用 `bitset` 优化，优化一下复杂度大概就可以艹过去了。如果你不知道 `bitset` 优化，可以自行百度。

（我其实平时没怎么用这种科技，只是知道有这么个东西，所以写一篇题解）

---

考虑把 $A$ 拆成 $26$ 个矩阵，每一位的值代表在这一位上是否有这个字母。

然后每输入一个字母，可以考虑这个字母可以把哪些位置上的 $ans$ 卡掉。

显然一个字母的对应矩阵 $0$ 的位置可以把还原过来的那个位置卡掉，这个卡掉显然就是 `&` 运算。

由于我是第一次写，我也把这个东西的暴力给写了出来：

```
for (int i=0;i<r;i++)
for (int j=0;j<c;j++)
{
	scanf(" %c", &q);
	if(q=='?') continue;
	for(int k=1;k<=n;k++)
	for(int l=1;l<=m;l++)
	ans[(k-i+n+1)%n][(l-j+m+1)%m]&=A[k][q-'a'][l];
}
```
稍微转换一下把最后一维循环给换成 `bitset` 然后最后代码还是比较简洁优美的：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int (i)=0;(i)<(n);++(i))
bitset<423> ans[423], p[423][26];
char q;
int main() {
    int n, m; cin >> n >> m;
    rep(i, n) rep(j, m) scanf(" %c", &q), p[i][q-'a'][j] = ans[i][j] = 1;
    int r, c; cin >> r >> c;
    rep(i, r) rep(j, c) if (scanf(" %c", &q), q != '?')
	rep(k, n) ans[(k+n-i%n)%n] &= p[k][q-'a']>>j%m|p[k][q-'a']<<m-j%m;
    rep(i, n) rep(j, m) printf("%d%s", (int)ans[i][j], j==m-1?"\n":"");
}
```





---

## 作者：JWRuixi (赞：1)

### 题意

给定一个循环向外无限延伸的 $n \times m$ 的表格，和一个 $r \times c$ 的询问表格。

问对于 $0 \le i < n, 0 \le j < m$，哪些点满足将第二张表的左上角挪到 $(i,j)$ 后两张表重合。

$n,m,r,c \le 400$。

### 分析

考虑逐步优化暴力：

#### 算法一

枚举 $(i,j)$，暴力判断，复杂度 $\mathcal O(n^4)$：

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        bool fl = 1;
        for (int x = 0; x < r; x++) for (int y = 0; y < c; y++) fl &= (s[(i + x) % n][(j + y) % m] == t[x][y]);
        as += fl;
    }
}
```

#### 算法二

考虑底层比较方式是 `=`，考虑用 `bitset` 优化，将整个表格拆成每个字母，逐个字母判断，复杂度 $\mathcal O(\dfrac{n^4|S|}{\omega})$。

#### 算法三

不考虑哪些可以，考虑哪些不行，对于每个询问表格上的点会使哪些点挂掉，复杂度 $\mathcal O(n^4)$。

#### 算法四

同样考虑用 `bitset` 优化，我们对每个字母建立一张表格，那么可以统计每种字母必须出现在哪些位置，从而推出起点必须出现在哪些位置，复杂度 $\mathcal O(\dfrac{n^4}{\omega})$。

### Code

提交记录：<https://codeforces.com/contest/754/submission/222448017>。

---

## 作者：joke3579 (赞：1)

首先考虑朴素的 $O(n^4)$ 如何实现。令 $P$ 为 $n\times m$ 的矩阵，$T$ 为 $r\times c$ 的矩阵。

```cpp
memset(ans, true, sizeof(ans));
for (int k = 1; k <= r; ++ k) for (int l = 1; l <= c; ++ l) if (T[k][l] != '?')
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= m; ++ j) 
		ans[(i - k + n) % n][(j - l + m) % m] &= (T[k][l] == P[i][j]);
```

发现最终我们需要对答案数组的整行进行有条件的与操作。这使我们想到使用 bitset 优化进程。     
对 $P$ 矩阵中每行使用 26 个 bitset ，第 $i$ 位保存 $\text a\sim \text z$ 是否存在于这一位。我们发现朴素实现的第 $4$ 层循环可以使用 bitset 表示。

因此采用 bitset 优化后可以做到 $O(\frac {nmrc} {w})$，足以通过本题。


本题的思想类似于 [CF914F](https://www.luogu.com.cn/problem/CF914F)，二者都是通过 bitset 进行带通配符的字符串匹配。

同时，本题还有采用多项式的解法，方式形如[本题](https://www.luogu.com.cn/problem/P4173)。时间复杂度为 $O(nmc\log n)$。由于常数过大，在实际测评中远不如 bitset 做法优秀。

$\text{code(bitset) :}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
#define pre(i,s,t) for (register int i = (s), i##_ = (t) - 1; i > i##_; -- i)
const int N = 400 + 10;
int n, m, r, c;
char str[N];
bitset<N> ans[N], mask[26][N];

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cin >> n >> m;
	rep(i,1,n) {
		ans[i].set();
		cin >> str + 1;
		rep(j,1,m) mask[str[j]-'a'][i].set(j);
	} cin >> r >> c;
	rep(i,1,r) {
		cin >> str + 1;
		rep(j,1,c) if (str[j] != '?') rep(k,1,n) 
			ans[(k - i % n + n) % n + 1] &= (mask[str[j] - 'a'][k] >> (j - 1 + m) % m) | (mask[str[j] - 'a'][k] << m - (j - 1 + m) % m);
	} 
	rep(i,1,n) {
		rep(j,1,m) cout << ans[i][j];
		cout << '\n';
	}
}
```

---

