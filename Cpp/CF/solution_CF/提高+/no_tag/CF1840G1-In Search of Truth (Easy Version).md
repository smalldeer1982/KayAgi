# In Search of Truth (Easy Version)

## 题目描述

The only difference between easy and hard versions is the maximum number of queries. In this version, you are allowed to ask at most $ 2023 $ queries.

This is an interactive problem.

You are playing a game. The circle is divided into $ n $ sectors, sectors are numbered from $ 1 $ to $ n $ in some order. You are in the adjacent room and do not know either the number of sectors or their numbers. There is also an arrow that initially points to some sector. Initially, the host tells you the number of the sector to which the arrow points. After that, you can ask the host to move the arrow $ k $ sectors counterclockwise or clockwise at most $ 2023 $ times. And each time you are told the number of the sector to which the arrow points.

Your task is to determine the integer $ n $ — the number of sectors in at most $ 2023 $ queries.

It is guaranteed that $ 1 \le n \le 10^6 $ .

## 说明/提示

Hacks

To hack, use the following test format.

In the first line, output a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of sectors.

In the second line, output $ n $ different integers $ 1 \le a_1, a_2, \dots, a_n \le n $ — the numbers of the sectors in clockwise order, the arrow initially points to the sector with the number $ a_1 $ .

## 样例 #1

### 输入

```
1

5

6

7

2

10

9

8

4

3

1```

### 输出

```
+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

+ 1

! 10```

# 题解

## 作者：YxYe (赞：14)

## 题意

[交互题](https://www.luogu.com.cn/problem/CF1840G1)，给你一个写有 $1\sim n$ 的乱序的转盘，每次可以顺时针转 $k$ 格，告诉你旋转后格子上的数，求 $n$ 的值。

弱化版数据范围：$n \le 10^6,k\le 2023$

## 分析

显然，为了知道 $n$ 的值，转盘至少转一圈回到我们查询过的值。因为我们不知道一共转了几圈，所以我们最好让转盘只转一圈后就找到答案。而为了找到我们查询过的值，一开始跳着转显然不一定可以，所以我们在一开始可以连续转，这样我们就有了一段连续区间的值，转完一圈之后就可以轻松找到啦！

转完连续的之后，显然继续连续转会超限制，于是我们就可以跳了。假设我们一开始连续转了 $m$ 格，那么只要我们接下来每次跳 $m$ 格就一定不会错过这个区间。

所以我们的策略就是：先取连续段，跳跃找答案！

那么 $m$ 等于多少呢？我们知道 $k=m+n\div m$，那么为了不超限制，通过小学的知识我们可以得到 $m$ 最优为 $\sqrt{n}$ 即 $10^3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hgkacptn.png)

觉得不错就点个赞吧！

(会了简单版怎么能不切[加强版](https://www.luogu.com.cn/blog/YxYe/solution-cf1840g2)呢？

---

## 作者：Leasier (赞：3)

好有脑子。新时代根号分治题。

------------

显然这里的 $a_i$ 除了拿来给你判重之外没有任何用处（

考虑一个类似 BSGS 的根号分治操作：

- 令 $N = 10^6, M = \sqrt{N} = 10^3$。
- 先做 $M$ 次 $+ 1$ 操作，如果碰到有相同就直接输出。
- 再做 $\leq M$ 次 $+ M$ 操作，找到第一个与前面某一次 $+ 1$ 操作中相同的项就直接输出。

于是总操作次数为 $2M = 2 \times 10^3 \leq 2023$，可以通过。

代码：
```cpp
#include <stdio.h>

const int N = 1e6, M = 1e3;
int vis[N + 7];

int main(){
	int x;
	scanf("%d", &x);
	for (int i = 1; i <= N; i++){
		vis[i] = -1;
	}
	vis[x] = 0;
	for (int i = 1; i <= M; i++){
		printf("+ 1\n");
		fflush(stdout);
		scanf("%d", &x);
		if (vis[x] != -1){
			printf("! %d\n", i - vis[x]);
			fflush(stdout);
			return 0;
		}
		vis[x] = i;
	}
	for (int i = 1; ; i++){
		printf("+ %d\n", M);
		fflush(stdout);
		scanf("%d", &x);
		if (vis[x] != -1){
			printf("! %d\n", M * (i + 1) - vis[x]);
			fflush(stdout);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

每次询问获得的信息只有当前所在位置的数字。考虑这样一件事情，如果我们询问了 $b_1, b_2, ..., b_k$ 之后，走到了询问 $b_1$ 前所在的数字，就说明 $n \mid \sum\limits_{i = 1}^k b_i$。可以考虑构造一个步数序列 $a_1, a_2, ..., a_m$，如果能满足任何一个 $x \in [1, 10^6]$ 都存在 $1 \le l \le r \le m$ 使得 $\sum\limits_{i = l}^r a_i = x$，那么就做完了。

先考虑 G1 $2023$ 次询问怎么做。发现是 $2 \sqrt{n}$ 级别，启发我们类似 BSGS 地，构造 $a_1 = a_2 = \cdots = a_{1000} = 1, a_{1001} = a_{1002} = \cdots = a_{2000} = 1000$。所用询问次数为 $2000$，[可以通过 G1](https://codeforces.com/contest/1840/submission/208838446)。

---

## 作者：ケロシ (赞：2)

# 题目分析
这道题要求的 $n$ 是 $10^6$， 但是只有 $2023$ 次询问，所以随机取最大值是不可取的。  
这时需要探讨别的性质。    
题目中是一个环，而环是首尾相连的，所以如果分别旋转了 $a$ 和 $b$ 次 $(a<b)$，那么 $n \mid b - a$。   
所以说首先需要找到两个相同的数。   
那么此题询问次数为 $2023$，可以通过以下方法找到两个相同的数。    
首先记录连续 $1000$ 个数字，然后每次指针跳动 $1000$ 格，随后绕环一圈就能找到两个相同的数字。    
这样最坏情况下 $2000$ 次就能找到两个相同的数字。   
在 $n \ge 1000$ 时，是绕环一圈，$n$ 直接为 $b - a$。
在 $n < 1000$ 时，说明绕了不止一圈，不能直接确定答案，所以在前面记录连续 $1000$ 个数字时判断是否有重复的数即可，然后取所有数的最大值。
# 代码
```cpp
void solve() {
    int N = 1000, V = 1000005;
    vector<int> a(N), b(V);
    cin >> a[0];
    b[a[0]] = 1;
    int mx = 0;
    FOR(i, 1, N - 1) {
        cout << "+ 1" << endl << flush;
        cin >> a[i];
        chmax(mx, a[i]);
        if(b[a[i]]) { // n小于1000
            cout << "! " << mx << endl << flush;
            return;
        }
        b[a[i]] = i + 1;
    }
    int cnt = 1, pos;
    FOR(i, 1, N) { // 绕环
        cout << "+ 1000" << endl << flush;
        int x;
        cin >> x;
        pos = x;
        if(b[x]) break;
        cnt++;
    }
    cout << "! " << cnt * 1000 + N - b[pos] << endl << flush;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
这是一个交互题。

有一个转盘，你可以转，_~~转来转去的~~_，最多转 $2023$ 次，每次返回转到了哪个数，求在转盘上一共有多少个数  _~~在转来转去~~_。
# 题目思路
先一个一个往同一个方向转 $1000$ 次，求出这 $1000$ 个数，然后继续往同一个方向一千一千的转，最后会落在求出的区间内，就求出来了。
# AC Code
```cpp
#include <bits/stdc++.h>

//#define endl '\n'
//#define float double
#define int long long
#define inf 0x3f3f3f3f

//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Os")
//#pragma GCC optimize("Ofast")
//
using namespace std;

int in, cnt, a[1005];

void init() {
}

signed main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	init();
	
	cin >> in;
	a[0] = in;
	
	for (int i = 1; i <= 1000; ++ i) {
		cout << "+ 1" << endl;
		cin >> in;
		a[++ cnt] = in;
		if (in == a[0]) {
			cout << "! " << cnt << endl;
			return 0;
		}
	}
	
	for (int i = 1; i <= 1023; ++ i) {
		cout << "+ 1000" << endl;
		cin >> in;
		
		for (int j = 0; j <= 1000; ++ j) {
			if (a[j] == in) {
//				cout << "! 1" << i << endl;
				cout << "! " << (i + 1) * 1000 - j << endl;
				return 0;
			}
		}
	}
	
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

upd 2023/06/12 修改了一些错误。

$\color{orange}\texttt{Difficulty: 2200}$

首先发现 $n\le 10^3$ 的时候可以每一次 $+1$ 暴力判断。如果某一次 $+1$ 之后发现已经走过了，那么就转了一圈了。

如果执行了 $10^3$ 次操作之后还是没有转完一圈，说明 $n>10^3$。于是每一次 $+10^3$。

如果某一次跳完之后答案已经出现过了那么就计算出了答案（往回推即可）。

容易发现这样最多走 $2\times 10^3$ 步就可以求出答案。

---

## 作者：hellolin (赞：0)

## Codeforces Round 878 (Div. 3) - G1 - In Search of Truth (Easy Version)

[洛谷题面](https://www.luogu.com.cn/problem/CF1840G1) | [Codeforces 题面](https://codeforces.com/contest/1840/problem/G1) | [AC 记录](https://www.luogu.com.cn/record/112393198)

首先想到的是，如果我询问的 $k$ 恰巧等于 $n$，那么转一圈回来正好指到原来的数字，就能知道答案了。

$$
{\color{red}3},\ 1,\ 4,\ 5,\ 2,\ 6\\
\texttt{+ 6}\\
{\color{red}3},\ 1,\ 4,\ 5,\ 2,\ 6\\
\texttt{! 6}
$$

但是这样做显然有一个问题，一旦 $k$ **不等于** $n$，我们不知道现在指向的这个数转完了一圈还是没转完，也就无法确定下一步应该执行什么。

$$
{\color{red}3},\ 1,\ 4,\ 5,\ 2,\ 6\\
\texttt{+ 4}\\
3,\ 1,\ 4,\ 5,\ {\color{red}2},\ 6
$$

$$
{\color{red}3},\ 1,\ 4,\ 5,\ 2,\ 6\\
\texttt{+ 1145}\\
3,\ 1,\ 4,\ 5,\ 2,\ {\color{red}6}
$$

既然只靠一个数确定位置无法满足我们，那么我们可以确定出来好多好多数的位置。在开始时执行 $10^3$ 次 `+ 1` 操作，这样我们就知道了前 $10^3+1$ 个数和它们的位置（都紧挨着）。

如果在询问过程中没有出现重复的数（$n>10^3$），那就说明执行的这 $10^3$ 次操作没有转完一圈。

此时，我们再执行 `+ 1000` 操作直到出现重复的数，并计算答案。此时由于一次转 $10^3$ 个位置，而我们已经确定了前 $10^3+1$ 个位置，所以可以保证第一次出现重复的数是只转了一圈出来的结果。

后面这一步最大操作次数约是 $\frac{10^6-10^3}{10^3} = 999$，$10^3 + 999 = 1999$，小于 $2023$，可以通过 Easy Version。

``` cpp
// 珍爱账号，请勿贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr static int N = 1e6 + 11;
int ask(bool d, int h) {
    cout << (d ? '+' : '-') << ' ' << h << endl;
    int x;
    cin >> x;
    return x;
}
void determine(int w) {
    cout << "! " << w << endl;
    exit(0);
}

int a[N], cur, tmp;
void solve() {
    cin >> tmp;
    a[tmp] = cur = 1;
    for (int i = 1; i <= 1000; i++) {
        ++cur;
        tmp = ask(1, 1);
        if (a[tmp]) {
            determine(cur - a[tmp]);
        }
        a[tmp] = cur;
    }
    for (;;) {
        cur += 1000;
        tmp = ask(1, 1000);
        if (a[tmp]) {
            determine(cur - a[tmp]);
        }
        a[tmp] = cur;
    }
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
```

---

