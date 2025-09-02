# Accumulation of Dominoes

## 题目描述

给定一个 $N$ 行 $M$ 列的矩阵，数字从 $1$ 开始，从左到右，从上到下依次在矩阵内排列。

定义 domino 为矩阵内相邻的两个差为 $1$ 的数，求一共有多少个不同的 domino。

两个 domino 不同当且仅当第一个 domino 其中的至少一个数在第二个 domino 没有出现。

## 样例 #1

### 输入

```
3 4```

### 输出

```
9```

## 样例 #2

### 输入

```
2 1```

### 输出

```
1```

# 题解

## 作者：ran_qwq (赞：4)

因为在一行中，数是从左到右连续排列的，所以一般情况下，每行相邻两个数差为 $1$，所以每行对答案进行 $m-1$ 的贡献，所以所有行答案就是 $(m-1)n$。

但有一种特殊情况，就是 $m=1$。这时，每行不存在相邻两个数，但相邻两行之间的数差恰好为 $1$，有 $n$ 行，所以此时答案为 $n-1$。

```cpp
#include<iostream>
using namespace std;
int main()
{
	long long n,m;
	cin>>n>>m;
	if(m==1)
		cout<<n-1;
	else
		cout<<n*(m-1);
}
```


---

## 作者：mark0575 (赞：3)

# 题解：

## 思路：

许多同学可能一上手就就暴力去搜。虽然在数据小的情况下可以通过，但一旦数据量大时（例如题目的 $1\leq N,M\leq 10^9$），暴力就不行啦。

# 正解

那暴力不行，还能怎么做呢？我们先找几组例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/pzf4z561.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/b92rj4m6.png)

通过这些例子，我们可以推导出一个公式：$N\times(M-1)$。

但还有一种特例，如第二幅图，当 $M=1$ 时,横着圈是没有的，但是竖着圈确是可以的，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/pdzzqojl.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/su5prj2k.png)

由此可以推出 $M=1$ 时，公式为：$N-1$。

通过上面的推导，我们可以写出下面的伪代码：

```cpp
	if(m==1)
	{
		cout<<n-1;
		return 0;
	}
	else
	{
		cout<<(m-1)*n;
		return 0;
	}
```
通过这些我们就可以写出下面的代码了：

```cpp
	#include<bits/stdc++.h>
	using namespace std;
	int main()
	{
		int n,m;
		cin>>n>>m;
		if(m==1)
		{
			cout<<n-1;
			return 0;
		}
		else
		{
			cout<<(m-1)*n;
			return 0;
		}
		return 0;
	}

```

俗话说得好，十年 OI 一场空，不开 long long 见祖宗。当我们把这个代码提交上去时，居然 WA 了几个点。

[提交记录](https://www.luogu.com.cn/record/86500394)

在仔细一看数据范围：$1\leq N,M\leq10^9$ 。$N$ 和 $M$ 最坏都是 $10^9$，两个 $10^9$ 相乘，肯定爆 int。因此必须开 long long。

AC code:

```cpp
	#include<bits/stdc++.h>
	using namespace std;
	int main()
	{
		long long n,m;
		cin>>n>>m;
		if(m==1)
		{
			cout<<n-1;
			return 0;
		}
		else
		{
			cout<<(m-1)*n;
			return 0;
		}
		return 0;
	}

```


---

## 作者：Hisaishi_Kanade (赞：1)

首先你可以直接使用时空复杂度均为 $O(nm)$ 的做法。

显然不合法。

$n,m\le10^9$，这样的数据范围很可能是 $O(1)$。

思路很明了，当 $m$ 为 $1$ 时，结果便是 $n-1$；

否则，每一行有 $m$ 个数，植树问题告诉我们其中有 $m-1$ 个间隔。

总共 $n$ 行，答案就是 $n(m-1)$。

请注意数据范围，不开龙龙是要见祖宗的。

>三年努力一场空，不开龙龙见祖宗。

>十年信竞迷茫茫，不开龙龙泪两行。

---

## 作者：ZBAA_MKC (赞：0)

### 题意

给定一个大小为 $N \times M$ 的矩阵，数字从 $1$ 开始，从左到右，从上到下依次在矩阵内排列。求上下左右相邻的两个数的差一的组数。

### 思路分析

此题很容易想到暴力解法，直接暴力扫整个矩阵，发现上下左右相邻差一就累加答，输出即可。

但这样做的时间复杂度是 $O(N \times M)$ 的，本题数据范围 $N, M \le 10^9$，很显然无法通过本题。

再重新观察矩阵，我们会发现，在 $M \ne 1$ 时，每行有 $M - 1$ 个符合要求的数对，对于整个矩阵，共有 $N\times (M - 1)$ 个符合要求的数对。

对于 $M = 1$ 的情况我们需要特殊考虑，在这样的矩阵中只存在上下相邻的情况，共有 $N-1$ 个符合要求的数对。

### 代码实现

**十年 OI 一场空，不开 long long 见祖宗！**

```cpp
#include <iostream>
using namespace std;

int main()
{
	long long n, m;
	cin >> n >> m;
	if (m == 1)
	{
		cout << n - 1;
	}
	else
	{
		cout << n * (m - 1);
	}
	return 0;
}
```

---

## 作者：Butterfly___qwq (赞：0)

# CF1725A Accumulation of Dominoes 题解
## 题意
给定一个 $N \times M$ 列的矩阵，数字从 $1$ 开始，从左到右，从上到下依次在矩阵内排列。求相邻的两个数的差一的组数。
## 思路
题目是说给出一个 $N \times M$ 的矩阵，又要求相邻的两个数的差一的组数所以可以组的个数为 $(N-1) \times M+(M-1) \times N$。由于数据较小，我们可以暴力找组数。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n,m;
	cin>>n>>m;
	int a[100][100];
	int h
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			a[i][j]=h;
				h++;
	}
	int ans=0;
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j+1]-a[i][j]==1)
				ans++;
		}
	}
	for(int i=1;i<=m-1;i++){
		for(int j=1;j<=n;j++){
			if(a[i+1][j]-a[i][j]==1)
				ans++;
		}
	}
	cout<<ans;
}
```
那么，效率有点低。
观察可以发现，一行中有 $m$ 个数，那么共有 $m-1$ 组。
那么 $n$ 行就有 $n \times (m-1)$ 个。
但是只有一行时，就只有 $n-1$ 行。
## 代码：
```cpp
void solve() {
    ll N, M;
    cin>>N>>M;
    if (M==1) {
        cout<<N-1<<endl;
        return;
    }
    cout<<(M-1)*N<<endl;
}
```

---

## 作者：CANTORSORT (赞：0)

### 简要题意

有一个 $n\times m$ 的矩阵，矩阵内的数字从 $1$ 开始，按从左到右、从上到下的顺序进行排列，给出一个定义：

一对相邻的格子，如果满足各自内的数字之差为 $1$，则我们称这一对格子为一个 domino。

### 讲解

其实这道题，如果你想直接用朴素算法求解，思路很显然：枚举这 $n\times m$ 个格子，对于每个格子的上下左右进行判断（如果存在），最后再容斥一下（除以 $2$，因为这种算法会保证形如 $(x_1,y_1),(x_2,y_2)$ 的答案会以另一种形式出现：$(x_2,y_2),(x_1,y_1)$）。

但是时间复杂度是 $O(n\times m)$ 的，对于 $n=10^9,m=10^9$ 这样的极限情况显然会 TLE，那么我们考虑推出一个结论，直接求解。

举一个例子，设 $n=5,m=5$，那么矩阵为：

```
 1  2  3  4  5
 6  7  8  9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25
```

显然，一般情况下，第 $i(1\le i<n)$ 行的数字不能和第 $i+1$ 行 的数字构成 domino，并且每一行的 domino 数量就是 $m-1$ 的值。

那么答案就是 $n\times (m-1)$。

但还要考虑特殊情况。设 $n=5,m=1$，那么矩阵为：

```
1
2
3
4
5
```

手动计算一下，可以发现其中有 $4$ 个 domino。

但按照我们先前的计算方法，得出的结果却是 $0$。

很简单，既然每一行只有一个数字，那么我们上述的规律就不成立了（即每一行内不存在 domino，但每一列内反而会出现 $n-1$ 个 domino），所以需要特判一下。

时间复杂度 $O(1)$。

### 核心代码

```cpp
if(m==1)
	cout<<n-1<<endl;
else
	cout<<n*(m-1)<<endl;
```

---

## 作者：ttq012 (赞：0)

分类讨论。

容易发现，当 $m=1$，也就是只有一列的时候，上下两个格子是相邻而且差为 $1$ 的。

否则，也就是不只一列的情况，上下两个格子虽然相邻，但是他们的差为 $m\neq 1$，不符合条件。但是左右的两个格子相邻，并且差为 $1$。对于每一行而言，有 $m$ 个格子，就有 $m-1$ 对相邻的左右的格子，有 $n$ 行，所以答案就是 $n(m-1)$。时间复杂度 $O(1)$。

```cpp
void solve()
{
  int n, m;
  cin >> n >> m;
  if (m == 1)
    cout << n - 1 << '\n';
  else
    cout << n * (m - 1) << '\n';
}
```

---

## 作者：云裳 (赞：0)

**思路**

分类讨论即可。

若 $M$ 不为 $1$，则每一行的 $M$ 个数中一共有 $M-1$ 组相邻的两个数。

又因为每行的数是从左到右依次递增的，所以每一行共有 $M-1$ 组符合条件的两个数，共 $N$ 行，答案为 $N\times (M-1)$。

而如果 $M$ 为 $1$，则只有 $N$ 个数从上到下依次递增，有 $N-1$ 组符合条件的两个数，答案为 $N-1$。


------------

代码：
```cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int INF = 0x3f3f3f3f;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n, m;
    cin >> n >> m;
    if (m == 1)
        cout << (n - 1);
    else
        cout << n * (m - 1);

    return 0;
}
```

---

## 作者：Tetrahydrofunina (赞：0)

分类讨论。

1. $m>1$，那么任意一个数与其上（下）的数的差至少为 $2$，不满足 domino 的条件，只有同一行相邻两数（相差为 $1$）才是 domino，因此只要算出同一行相邻的两数组成的数对的数量，就是答案。这显然是 $(m-1)\times n$。
2. $m=1$，此时一行只有一个数，并且任意一个数与其上（下）的数的差为 $1$，那么我们只要算出这一列相邻的两数组成的数对的数量，就是答案。这显然是 $n-1$。

还有，**十年 OI 一场空，不开 `long long` 见祖宗**。

代码就不放了，自己打吧。

最后，提前祝大家 CSP RP++！

---

## 作者：cyhtxdy (赞：0)

可以发现，当 $m>1$ 时，垂直方向是没有多米诺骨牌的，仅水平方向有多米诺骨牌。那么每一行都有 $m-1$ 个多米诺骨牌，所以答案为 $n \times (m-1)$。

当 $m=1$ 时，水平方向是没有多米诺骨牌的，仅垂直方向有多米诺骨牌。那么这一列一共有 $n-1$ 个多米诺骨牌。

得到代码：
```
#include <bits/stdc++.h>

using namespace std;

long long n, m;

int main () {
	cin >> n >> m;
	if (m == 1) {
		cout << n - 1;
	}
	else {
		cout << n * (m - 1);
	}
}
```


---

## 作者：LeNotFound (赞：0)

### 题意简述  
给定 $N$ 行 $M$ 列的矩阵，从左上角依次递增填充，下面给出 $3$ 行 $4$ 列的矩阵示例，如图。  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725A/6ffa3c95ba2e7eb37086c5fb9dfc34c4a6f85917.png)  
找出相邻两个格子相差数字为 $1$ 的数对个数。  

### 题目分析  
不难发现，**当且仅当列宽 $M$ 为 $1$ 时**，上下两个格子相差值才为 $1$，其余情况下符合要求的数对都在各行中，可以理解为统计列之间的夹缝个数，而每行的夹缝个数恰为列宽 $M-1$(~~小学数学植树问题~~)。  
综上两种情况，可以得出答案。  

### 代码  
```cpp
#include <iostream>

using namespace std;

int N, M;

int main()
{
    cin >> N >> M;

    if (M == 1)
    {
        cout << N - 1;
        return 0;
    }

    cout << N * (M - 1);

    return 0;
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1725A)

这道题其实只要特判 $n=1$ 的情况就行了，如果 $n=1$ 输出 $m-1$，否则输出 $m \times (n-1)$。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long n,m;
int main()
{
	scanf("%lld%lld",&n,&m);
	if(m==1) printf("%lld",n-1);
	else printf("%lld",n*(m-1));
	return 0;
}
```


---

## 作者：__Allen_123__ (赞：0)

### 题意简述

- 给定一个 $N \times M$ 的矩阵。

- 给矩阵中的每个元素从上到下，每行从左到右用正整数依次标号。

- 如果一对相邻的矩形标号差正好为 $1$，那么就满足题目条件。

- 求满足条件的相邻矩形的对数。

- $1 \le N, M \le 10^9$。

### 题目分析

这题我们上手后先看数据范围，$1 \le N, M \le 10^9$， $O(n)$ 的复杂度也会爆，所以可以初步确定这是一道 $O(1)$ 的找规律题。

---

题目已经告诉我们：标号方式是从上而下，每行从左到右依次标号，所以我们根据题意可以发现：每行的相邻矩形的标号差值就为 $1$。每行有 $M$ 个矩形，所以每行就有 $M - 1$ 个合法的答案，共有 $N$ 行，相乘结果就是 $N \times (M - 1)$，得到答案。于是我们就可以通过样例 $1$。

---

但是，套用样例 $2$， 我们的推导式的最终结果就是 $2 \times (1 - 1) = 0$，而样例 $2$ 的正确结果是 $1$，这究竟是为什么呢？

画个图我们就知道了：在 $M = 1$ 的情况下，在我们标号时，从上而下的标号就依次是 从 $1$ 到 $N$。熟不熟悉？在这种情况下，这就跟我们的原来的一列是一样的（长度为 $N$），最终答案就为 $N - 1$。

---

温馨提示：$N·M$ 最大值达到了 $10^{18}$，需要开 long long。

---
### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, res;
int main(){
	scanf("%lld%lld", &n, &m);
	if(m == 1){ // 样例 2 的情况
		res = n - 1;
	}
	else{ // 其他情况
		res = n * (m - 1);
	}
	printf("%lld", res);
	return 0;
}
```

---

