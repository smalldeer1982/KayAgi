# Laboratory on Pluto

## 题目描述

As you know, Martian scientists are actively engaged in space research. One of the highest priorities is Pluto. In order to study this planet in more detail, it was decided to build a laboratory on Pluto.

It is known that the lab will be built of $ n $ square blocks of equal size. For convenience, we will assume that Pluto's surface is a plane divided by vertical and horizontal lines into unit squares. Each square is either occupied by a lab block or not, and only $ n $ squares are occupied.

Since each block is square, it has four walls. If a wall is adjacent to another block, it is considered inside, otherwise — outside.

Pluto is famous for its extremely cold temperatures, so the outside walls of the lab must be insulated. One unit of insulation per exterior wall would be required. Thus, the greater the total length of the outside walls of the lab (i. e., its perimeter), the more insulation will be needed.

Consider the lab layout in the figure below. It shows that the lab consists of $ n = 33 $ blocks, and all the blocks have a total of $ 24 $ outside walls, i. e. $ 24 $ units of insulation will be needed.

You should build the lab optimally, i. e., minimize the amount of insulation. On the other hand, there may be many optimal options, so scientists may be interested in the number of ways to build the lab using the minimum amount of insulation, modulo a prime number $ m $ .

Two ways are considered the same if they are the same when overlapping without turning. Thus, if a lab plan is rotated by $ 90^{\circ} $ , such a new plan can be considered a separate way.

To help scientists explore Pluto, you need to write a program that solves these difficult problems.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/19a2731aaaa55a0f9a8048f01dd79ff768ce23d2.png)

## 说明/提示

Consider the second example.

If $ n=1 $ , the only way to build a lab is to place a single block. In this case, the perimeter will be equal to four.

When $ n=2 $ , you must place two blocks side by side. This can be done either vertically or horizontally, so there are two ways. It is easy to see that the lab has six outside walls in this case.

For $ n=7 $ , all the $ 22 $ optimal plans are shown in the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/2d61b154960a5ef9890728641d5e6f811e5f6274.png)

## 样例 #1

### 输入

```
3 1
1
2
7```

### 输出

```
1 1
#
1 2
##
2 4
.###
####```

## 样例 #2

### 输入

```
3 2
1000000007
1
2
7```

### 输出

```
4 1
6 2
12 22```

# 题解

## 作者：Hovery (赞：8)

只讲询问 $2$，询问 $1$ 直接枚举就行。

我们设长方形的一条边长为 $a$，另一条为 $b$，且 $a < b$。

那么 $a,b$ 就要满足条件 $a\times b-n \le a$。

然后还要周长最小，发现这样的长方形数大概在根号级别，且 $a$ 也在 $\sqrt{n}$ 附近，我们就可以枚举这个长方形。

然后考虑知道长方形的之后怎么做。

从答案入手，发现长方形一定是只抠 $4$ 个角中的任意几个角，而且抠出来的形状要是阶梯形，要不然会影响周长。

设 $f_i$ 表示在一个角抠掉 $i$ 个块的方案数。

如果我们知道了这个，那么 $4$ 个角的答案是可以合并的，即不会相互影响，因为我们有 $a\times b-n < a$。

至于 $f_i$，而且抠掉的是个阶梯型，就想到了[P1025](https://www.luogu.com.cn/problem/P1025)。

只要保证分出来的组数小于 $a$ 即可。

就有 $f_i = \sum_{j=1}^i dp_{i,j}$。

这里的 $dp$ 就是上面那道题的 $dp$ 数组。

合并的话是一个卷积的形式。

由于要抠掉的格子数是根号级别，可以暴力卷，卷 $3$ 次就行了。

然后你发现这样还是过不了，要先预处理 $f_i$ 才能过。

---

## 作者：Mine_King (赞：4)

- **upd on 2023/01/11：** 图炸了，重新上传了一遍。

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/17042849.html)

# F. Laboratory on Pluto

## Problem

[CF1775F Laboratory on Pluto](https://codeforces.com/contest/1775/problem/F)

**题目大意：**

在一个无限大的网格中，你要选择 $n$ 个格子，使得其周长最小。

每个数据可能是以下两种情况：

$Type = 1$，则要求构造任意一种最优解。保证 $\sum n \le 8 \times 10^5$。

$Type = 2$，则要求输出最小的周长和最优解的方案数。

## Solution

首先考虑第一问，显然构造成下图的类似于矩形的形状一定不劣。

![](https://cdn.luogu.com.cn/upload/image_hosting/ffkbn1o4.png)

故可以枚举矩形的长宽中较小的一条的长度。

考虑第二问，显然最优解一定是一个矩形扣掉四个角，类似于下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/rswvujrd.png)

考虑单独一个角怎么做。

由于一个角上的空格成阶梯状，故可以将每行的格子数取下来形成一个单调不降的序列，于是数空格数为 $k$ 的方案数变成了求有多少个单调不降的序列满足总和 $=k$。  
这是一个经典的 DP，设 $dp_{i,j}$ 表示长度为 $i$，总和为 $j$ 的方案数。
$$
dp_{i,j} = dp_{i-1,j-1} + dp_{i,j-i}
$$
转移方程分别对应往序列前面添加一个 $1$ 和给整个序列 $+1$。

设 $f_i$ 表示 $i$ 个空格的答案，则：
$$
f_i = \sum\limits_{j=1}^i dp_{j,i}
$$
显然四个角上的答案都一样，所以最后把这四个卷起来即可。注意空格数是 $O(\sqrt{n})$ 的，所以可以暴力卷积。

为什么这样不会出现同一个空格被两个角计算的情况？

注意到一个显然但是重要的结论：空格数不超过长宽的较小值。故不会算重。

但是注意到 $\sum n \le 8 \times 10^5$ 只在 $Type = 1$ 的时候成立，故还需要加一些优化。

- $dp,f$ 和最终的答案显然可以预处理，这样预处理的复杂度为空格数的平方，即 $O(n)$。
- 枚举合法的矩形长宽也不能直接来，但是大胆猜想最优矩形一定在根号左右，故枚举根号前后 $100$ 个即可。

## Code

注意取模。

```cpp
// Think twice, code once.
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int T,Type,n,mod;

void solve1() {
	int len=1;
	for (int i=2;i<=n;i++)
		if (len+(n+len-1)/len>i+(n+i-1)/i) len=i;
	int cnt=n;
	printf("%d %d\n",len,(n+len-1)/len);
	for (int i=1;i<=len;i++,puts(""))
		for (int j=1;j<=(n+len-1)/len;j++)
			if (cnt) putchar('#'),cnt--;
			else putchar('.');
	return ;
}

int dp[1005][1005];
int f[1005],g[1005],gg[1005];
void solve2() {
	int len=1;
	for (int i=max((int)sqrt(n)-100,1);i<=min((int)sqrt(n)+100,n);i++)
		if (len+(n+len-1)/len>i+(n+i-1)/i) len=i;
	printf("%d ",(len+(n+len-1)/len)*2);
	// printf("\n%d %d\n",k,len);
	// puts("");
	int ans=0;
	for (int r=max((int)sqrt(n)-100,1);r<=min((int)sqrt(n)+100,n);r++)
		if (len+(n+len-1)/len==r+(n+r-1)/r) {
			int c=(n+r-1)/r;
			if (r>c) break;
			int k=r*c-n;
			
			ans=(ans+gg[k]*(r==c?1:2)%mod)%mod;
		}
	printf("%d\n",ans);
	return ;
}

int main() {
	scanf("%d%d",&T,&Type);
	if (Type==2) {
		scanf("%d",&mod);
		dp[0][0]=1;
		for (int i=1;i<=1000;i++)
			for (int j=i;j<=1000;j++) {
				if (i==j) {
					dp[i][j]=1;
					continue;
				}
				if (i>0) dp[i][j]=dp[i-1][j-1];
				if (j>i) dp[i][j]=(dp[i][j]+dp[i][j-i])%mod;
			}
		f[0]=1;
		for (int i=1;i<=1000;i++)
			for (int j=1;j<=i;j++)
				f[i]=(f[i]+dp[j][i])%mod;
		for (int i=0;i<=1000;i++)
			for (int j=0;j<=1000;j++)
				if (i+j<=1000) g[i+j]=(g[i+j]+(long long)f[i]*f[j]%mod)%mod;
		for (int i=0;i<=1000;i++)
			for (int j=0;j<=1000;j++)
				if (i+j<=1000) gg[i+j]=(gg[i+j]+(long long)f[i]*g[j]%mod)%mod;
		for (int i=0;i<=1000;i++) g[i]=gg[i],gg[i]=0;
		for (int i=0;i<=1000;i++)
			for (int j=0;j<=1000;j++)
				if (i+j<=1000) gg[i+j]=(gg[i+j]+(long long)f[i]*g[j]%mod)%mod;
	}
	while (T--) {
		scanf("%d",&n);
		if (Type==1) solve1();
		else solve2();
	}
	return 0;
}
```



---

## 作者：zac2010 (赞：3)

### 前言

这道题我的做法是**枚举**和**动态规划**。

这道题对思维能力及模型转化能力有一定要求，且要用到多次动态规划（虽然每次都比较好想），所以是道不错的题。只是可能会有些难想。

感觉其他的大部分题解讲解的真的是清晰得不太明显（因为我很菜），然后我打算针对我思考时所想的时间较长的地方进行较详细的讲解，其他地方略写。

### 题意

这翻译似乎不那么简洁。

题目大意：在一个无限大的网格图中，告诉你一个大小 $n$，你要选择 $n$ 个格子，使得周长最小。有两种操作：
1. 让你输出任意一种方案。
2. 让你求方案数。

至于格式见题面的输入输出。
### 思路

不难发现，所有的格子一定是四联通的，否则周长一定不优于这个。

不难发现，一个凸的图形一定比凹的优。
也就是说，在确定面积的时候周长一定是凸的小。

不难发现，通过 $u=1$ 的情况我们能知道所有的四联通的凸图形一定可以用一个正方形去掉每个角的一部分或者不去掉得到。且完整包含这个图形的最小矩形去掉四个角一定不会有两个角连到一起去（不然这个矩形必定可以再缩小）。以及我们根据小学数学学得 $a+b$ 相同时（即周长相等），$\lvert a-b \rvert$ 越小面积越大，所以 $a$ 与 $b$ 的取值为 $\sqrt n$ 最妥当。

不难发现，我们可以先算去掉一个角的方案数，然后拿一个角的方案数合并四次变成四个角。而对于一个角，既然是凸的，那必定是个阶梯型，不然就凹进去了（既然是阶梯，那么每行去掉的数是具有单调性的，所以发现是个分拆数）。那么可以用[这题](https://www.luogu.com.cn/problem/P1025)里面的动态规划方法算出动态规划数组，求个和，及每个角，再用背包的思想把数组合并进一个背包数组，合并四次。

不难发现，做的第一次动态规划，即分拆数的状态为 $g[i][j]$ 表示总和为 $i$、选了 $j$ 个数的方案数，再这里也就是删了 $i$ 个格子，总共删到第 $i$ 行的方案数，转移方程为 $g[i][j] = g[i - 1][j - 1] + g[i - j][j]$，前一项表示新建一个数，初始为 $1$，后一项表示把每项都加 $1$ （这个转移方程式把数从大到小算方案数的）。而第二次是求一个前缀和，表示删去大小为 $i$ 一个角的方案数 $s[i]=\sum_{j=0}^{i}f[i][j]$。至于第三次，是一个背包，状态和一个角唯一的区别在于他不止一个角，第 $i$ 次和并就是第 $i$ 个角，进行四次 $f[i] = f[i - j] \times s[j]$。

不难发现，这道题的思路已经结束了。

### 代码

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 1000;
int n, m, g[N + 10][N + 10], s[N + 10], f[N + 10];
void Init(){
	g[0][0] = 1;
	L(i, 1, N) L(j, 1, i)
		g[i][j] = (g[i - 1][j - 1] + g[i - j][j]) % m;
	L(i, 0, N) L(j, 0, i) s[i] = (s[i] + g[i][j]) % m;
	f[0] = 1;
	L(i, 1, 4) R(j, N, 0) L(k, 1, j)
		f[j] = (f[j] + 1ll * f[j - k] * s[k] % m) % m;
}
void Solve1(){
	scanf("%d", &n);
	int a = sqrt(n), b = (n - 1) / a + 1, cnt = 0;
	printf("%d %d\n", a, b);
	L(i, 1, a){
		L(i, 1, b)
			putchar(++cnt <= n? '#' : '.');
		putchar('\n');
	}
}
void Solve2(){
	scanf("%d", &n);
	int a = sqrt(n), b = (n - 1) / a + 1, c = a + b, ans = 0;
	L(i, 1, c - 1)
		if(i * (c - i) >= n)
			ans = (ans + f[i * (c - i) - n]) % m;
	c *= 2, printf("%d %d\n", c, ans);
}
int main(){
	int T, u;
	scanf("%d%d", &T, &u);
	if(u == 1) while(T--) Solve1();
	else{
		scanf("%d", &m), Init();
		while(T--) Solve2();
	}
	return 0;
}
```

---

## 作者：N2MENT (赞：2)

[CF1775](https://www.luogu.com.cn/problem/CF1775F)

***
~~发表暴论：太简单了建议降蓝~~。   
总之挺简单的。  

大家小学都学过，一样周长的矩形里正方形的面积最大。肯定是想要找到一个面积恰好大于等于实验室面积的，长和宽相差尽可能小的矩形。  

设长和宽分别为 $a$ 和 $b$ 那么只有两种情况：$a = b$ 或者 $a = b + 1$，如果 a 和 b 的差超过 $1$ 一定不优。那么 $u = 1$ 的情况直接枚举 $a$ 和 $b$，如果 $b$ 可以减小 $1$ 就减小。

在 $u = 2$ 的时候，考虑从整个矩形里去掉多余的格子，结果不会出现凹槽的形状，否则周长变长一定不优。那么只能从四个角取走格子。仔细一想，四个角互相独立，不然可以至少可以减少一行或一列。

把要去掉的部分沿着每一行划分，这些块的长度从外到内的一定不增。

设 $g_{i,j}$ 表示在一个角一共去掉了 $i$ 个格子，上一行去掉的部分长度为 $j$，转移：$g_{i,j}=\sum_{k=1}^{j} g_{i - j,k},g_{0,0}=1$。在一个角去掉 $i$ 个格子的方案数 $f_{i}= \sum_{j = 1}^{i} g_{i,j},f_0 = 1$。一共去掉四个角再做一遍类似的 dp 就行了，最后得到需要去掉 $i$ 个格子时的方案数。dp 结束后改变矩形的长和宽，$O(1)$ 记录此时的答案。

$a$ 和 $b$ 最多 $\sqrt n$，dp 时只用遍历到 $\sqrt n$，模数提前给你了所以 dp 可以预处理，加上前缀和，两次都是 $O(n)$ 的，复杂度 $O(n+t)$。

做完了，~~这么丑的代码应该没人看~~，两次 dp 黄上加黄，蓝，不能再高了。

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define Clear(x, y) memset(x, y, sizeof(x))
const int maxn = 4e5 + 10;
const int maxe = 700;
int f[maxe], g[maxe][maxe];
int h[4][maxe];
int pre[maxe][maxe];

int n, mod;
void Solve1() {
    scanf("%d", &n);
    int a = 0, b = 0;
    int bd = ceil(sqrt(n));
    for (int i = 1; i <= bd; i++) {
        if (i * i >= n) {
            a = i, b = i;
            break;
        }
    }
    if (a * (b - 1) >= n)
        b--;
    printf("%d %d\n", a, b);
    int cnt = 0;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            cnt++;
            if (cnt > n) {
                putchar('.');
            } else {
                putchar('#');
            }
        }
        putchar('\n');
    }
}
void Solve2() {
    scanf("%d", &n);
    int a = 0, b = 0;
    int bd = ceil(sqrt(n));
    for (int i = 1; i <= bd; i++) {
        if (i * i >= n) {
            a = i, b = i;
            break;
        }
    }
    if (a * (b - 1) >= n)
        b--;
    int ans = 0;
    int c = a + b;
    while (a * b >= n) {
        int rst = a * b - n;
        if (a == b)
            ans = (ans + h[3][rst]) % mod;
        else
            ans = (ans + h[3][rst] * 2 % mod) % mod;
        a++, b--;
    }
    printf("%d %d\n", c * 2, ans);
}
int t, u;
int main() {
    scanf("%d%d", &t, &u);
    if (u == 2) {
        scanf("%d", &mod);
        g[0][0] = 1;
        for (int i = 0; i < maxe; i++) {
            pre[0][i] = 1;
        }
        for (int i = 1; i < maxe; i++) {
            for (int j = 1; j <= i; j++) {
                g[i][j] = pre[i - j][j];
            }
            for (int j = 1; j < maxe; j++) {
                pre[i][j] = (pre[i][j - 1] + g[i][j]) % mod;
            }
            f[i] = pre[i][i];
        }
        f[0] = 1;
        for (int i = 0; i < maxe; i++) {
            h[0][i] = f[i];
        }
        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < maxe; j++) {
                for (int k = 0; k <= j; k++) {
                    h[i][j] = (h[i][j] + 1ll * h[i - 1][j - k] * f[k] % mod) % mod;
                }
            }
        }
    }
    while (t--) {
        if (u == 1) {
            Solve1();
        } else {
            Solve2();
        }
    }
    return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：1)

先考虑 $u=1$，打表（或者一眼秒）可以发现，一定存在一个方案，是由一个长为 $\sqrt{n}$ 面积比 $n$ 大的最小的矩形，从四个角删掉多余正方形，删完之后仍为凸多边形，这个凸多边形即为方案。输出方案即可。

对于 $u=2$ 的部分，先用 $u=1$ 部分的方法算出周长，我们可以发现，所有的方案都是一个周长为答案的矩形从角删多余正方形形成的。并且容易发现，任意一个角删除的正方形一定不会和另一个角删除的正方形相邻，如果相邻的最小周长就变了，所以可以求出从一个角删正方形的方案数，之后这个方案数数组的四次方就是从四个角删的方案数（设为 $dp_i$），而从一个角的方案数就是经典的整数划分问题，由于上界是 $\sqrt{n}$，所以直接用平方的求法即可。之后枚举矩形的长，根据周长求出宽，设面积为 $S$，如果 $S<n$ 则对答案没有贡献，否则对答案的贡献为 $dp_{S-n}$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace Wilson_Inversion {
void gi(int &x) {
	x = 0;
	int y = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') y = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + (c & 15);
		c = getchar();
	}
	x *= y;
}
int T, n, dp[1010][1010], u, f[2010], g[2010], mod;
void main() {
	gi(T);
	gi(u);
	if (u == 1) {
		while (T--) {
			gi(n);
			int c(sqrt(n));
			int d((n - 1) / c + 1);
			printf("%lld %lld\n", c, d);
			int num(0);
			for (int i(1); i <= c; ++i) {
				for (int j(1); j <= d; ++j) {
					if (num == n)
						putchar('.');
					else {
						putchar('#');
						++num;
					}
				}
				puts("");
			}
		}
		return;
	}
	gi(mod);
	dp[0][0] = 1;
	for (int i(0); i <= 1000; ++i) {
		for (int j(0); j <= 1000; ++j) {
			if (i + 1 <= 1000 && j + 1 <= 1000) (dp[i + 1][j + 1] += dp[i][j]) %= mod;
			if (j + i <= 1000 && i != 0) (dp[i][j + i] += dp[i][j]) %= mod;
		}
	}
	for (int i(0); i <= 1000; ++i) {
		for (int j(0); j <= i; ++j) (f[i] += dp[j][i]) %= mod;
	}
	for (int Case(1); Case <= 2; ++Case) {
		memcpy(g, f, sizeof(g));
		memset(f, 0, sizeof(f));
		for (int i(0); i <= 1000; ++i) {
			for (int j(0); j <= 1000; ++j) {
				if (i + j <= 1000) (f[i + j] += g[i] * g[j]) %= mod;
			}
		}
	}
	while (T--) {
		gi(n);
		int c(sqrt(n));
		int d((n - 1) / c + 1);
		int sum(c + d), ans(0);
		for (int i(1); i < sum; ++i) {
			if (i * (sum - i) < n) continue;
			(ans += f[i * (sum - i) - n]) %= mod;
		}
		printf("%lld %lld\n", sum * 2, ans);
	}
}
}
#undef int
int main() {
	Wilson_Inversion::main();
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：1)

首先，我们基地必然是一个四联通块，否则咋样合并一下周长总会减小。

其次，基地不凹——将周长投影在两维，不可能存在两层以上的重叠。

这样的话，基地的周长就是其外边框的周长。

枚举外边框矩形的一边长度 $a$，就可以得到 $u=1$ 的答案。

$u=2$，对于每一个 $a$，我们可以确定最小的另一边长 $b$。规定 $a\le b$，$a=b$ 时答案要 $\times 2$。

我们考察外边框减基地的那些空位，个数必然 $<a$，所以怎么排都不会减小外边框。

空位放在一个角上的方案数就是无序分拆数（这个暴力求即可），我们将其（OGF）四次方就是总方案数。

预处理复杂度 $O(\max n)$，单次询问复杂度 $O(n^{1/4})$。

为什么是 $n^{1/4}$ 呢？因为合法的外边框数只有 $O(n^{1/4})$，考虑从接近正方形的外边框不断缩小一边的长度，缩小一个单位另一边必然增加至少一个单位，若增加至少两个单位则接下来都不是答案了，然而边框内空位个数会以平方级别减少，所以最多 $\sqrt{\sqrt n}$ 次就会不止一个单位地增加。

当然写单次 $O(\sqrt n)$ 最方便。

---

## 作者：Priestess_SLG (赞：0)

第一道 $*\red{2500}$ 的题捏（有可能是最后一道了呜呜呜

忽然发现这是我打的第一场现场 CF，，那个时代，再见了 qwq

首先考虑第一问。这是简单的。考虑一个基本的均值不等式：

$$
\frac{a+b}{2}\ge\sqrt{ab}
$$

且上式当且仅当 $a=b$ 时取等号。

将上式不等式两侧同时平方得到：

$$
\frac{1}{4}(a+b)^2\ge ab
$$

考虑钦定一个矩形的长为 $a$ 宽为 $b$。则根据上面的分析，若 $a+b$ 的值已经固定，$|a-b|$ 的值越小，$ab$ 的值越大。

然后还有一个结论就是说格式相同点数相同的条件下，凸图形一定比凹图形周长要小。（说的可能不太清楚）这也是挺显然的，一个凹槽就会额外增加一定量的周长。例如：

```
...
. .
```

比

```
...
 ..
```

的周长要多 $2$，多在 $(2,2)$ 位置的凹槽上。

因此考虑贪心。若 $\exists k,n=k^2$ 且 $k\in\mathbb{N}$，则构造一个 $k\times k$ 的连续正方形一定不会变差。若不存在上述的 $k$，则考虑构造 $k'$ 满足 $k'\in\mathbb{N},k'^2\ge n$ 且 $k'$ 的值尽量小。构造一个 $k'\times k'$ 的正方形矩阵，然后考虑将该矩阵内所有的点 $(x,y)$ 按照 $x+y$ 的值从小到大排序，然后按照顺序删除这些点，直到剩余的点的数量恰好为 $n$。容易感性证明**经过上述删除点的方案后，剩余图形一定是凸的。**

然后考虑第二问。

根据第一问的贪心分析可以知道第二问的答案一定是在上面构造的矩形中四个角分别挖去一些元素并使得图形仍然保持为凸。

发现四个角的问题互相独立，因此先考虑挖去一个角怎么做。（~~一脸不可做~~）考虑一个很牛的转化。

[![pABojts.png](https://s21.ax1x.com/2024/10/30/pABojts.png)](https://imgse.com/i/pABojts)

（上图为矩形中挖去左上角后的情况）

此时可以写出一个简单的 dp：设 $f_i$ 表示在矩形左上角中挖去 $i$ 个元素，满足剩余图形为凸的不同的方案数。条件 **剩余图形为凸** 可以被转化为 **选取一个序列 $a$ 满足其所有元素的和为 $i$ 且序列单调不下降的方案数。**

然后经典转移。再设 $g_{i,j}$ 表示序列当前元素长度为 $i$，一共选择了 $j$ 个元素的方案数。

则显然有转移式：$g_{i,j}=g_{i-1,j-1}+g_{i,j-i}$。求和得 $f_i=\sum g_{i,j}$。

于是挖去一个角元素的情况就做完了。把这个问题跑四遍，则容易证明 $h_i=\sum_{a,b,c,d}[a+b+c+d=i]f_i$。直接做显然超时，因此把式子拆开，得到卷积的形式，可以上 FFT。但是容易发现多项式的项数最多为根号级别，因此直接暴力乘时间复杂度也正确。

于是问题结束，时间复杂度为 $O(n\sqrt n)$，可以通过。

代码：

```cpp
mt19937_64 mt(time(0));
int g[2010][2010], f[2010], h[2010];
 
void run() {
    int T = read(), o = read();
    if (o == 1) {
        while (T--) {
            int n = read();
            int x = (int)sqrt(n), y = (n - 1) / x + 1;
            cout << x << ' ' << y << '\n';
            vector<pair<int, int>> vec;
            for (int i = 1; i <= x; ++i) {
                for (int j = 1; j <= y; ++j) {
                    vec.eb(i - 1, j - 1);
                }
            }
            sort(vec.begin(), vec.end(), [&](auto l, auto r) {
                return l.first + l.second < r.first + r.second;
            });
            vector<vector<char>> maps;
            maps.resize(x);
            for (int i = 0; i < x; ++i) {
                maps[i].resize(y, '.');
            }
            int idx = 0;
            for (auto &[x, y] : vec) {
                if (++idx <= n) {
                    maps[x][y] = '#';
                }
            }
            for (int i = 1; i <= x; ++i, cout << '\n') {
                for (int j = 1; j <= y; ++j) {
                    cout << maps[i - 1][j - 1];
                }
            }
        }
    } else {
        int mod = read();
        h[0] = g[0][0] = 1;
        for (int i = 1; i <= 2000; ++i) {
            for (int j = 1; j <= i; ++j) {
                g[i][j] = (g[i - 1][j - 1] + g[i - j][j]) % mod;
            }
        }
        for (int i = 0; i <= 2000; ++i) {
            for (int j = 0; j <= i; ++j) {
                f[i] = (f[i] + g[i][j]) % mod;
            }
        }
        for (int i = 2000; ~i; --i) {
            for (int j = 1; j <= i; ++j) {
                h[i] = (h[i] + h[i - j] * f[j]) % mod;
            }
        }
        for (int i = 2000; ~i; --i) {
            for (int j = 1; j <= i; ++j) {
                h[i] = (h[i] + h[i - j] * f[j]) % mod;
            }
        }
        for (int i = 2000; ~i; --i) {
            for (int j = 1; j <= i; ++j) {
                h[i] = (h[i] + h[i - j] * f[j]) % mod;
            }
        }
        for (int i = 2000; ~i; --i) {
            for (int j = 1; j <= i; ++j) {
                h[i] = (h[i] + h[i - j] * f[j]) % mod;
            }
        }
        while (T--) {
            int n = read();
            int x = (int)sqrt(n), y = (n - 1) / x + 1;
            int s = 0;
            for (int i = 1; i <= x + y - 1; ++i) {
                if (i * (x + y - i) >= n) {
                    s = (s + h[i * (x + y - i) - n]) % mod;
                }
            }
            cout << (x + y) * 2 << ' ' << s << '\n';
        }
    }
}
 

```

------------------------------------


> $\qquad$ 我们会慢慢长大成人，在不断流逝的季节之中，盛开在路旁的花儿们，也在渐渐变化，盛开在那个季节里的花朵叫什么名字呢，在风中小小摇曳，伸手触碰便被扎得疼痛，把脸凑近，就能闻到一股淡淡的青涩的太阳芳香，那股芳香渐渐消散，而我们渐渐长大，但是，那朵花一定依旧盛开在某处。
>
> $\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad$ ——《我们仍未知道那天所看见的花的名字》

![](https://s11.ax1x.com/2023/09/21/pPITyi8.png)

---

## 作者：SamHJD (赞：0)

## [CF1775F Laboratory on Pluto](https://www.luogu.com.cn/problem/CF1775F)

### 题意

在网格中画 $n$ 个格子，求使整个图形的周长最小的方案数，并能输出一种方案。

### 解法

首先计算最小周长。

根据直觉，整个图形一定是团型，在这种情况下我们可以将周长转化成一个矩形的周长。

设矩形的周长为 $len$，那么面积最大为 $\left\lfloor\dfrac{len}{2}\right\rfloor\times(n-\left\lfloor\dfrac{len}{2}\right\rfloor)$。于是可以二分周长，判断最大面积是否不小于 $n$ 即可。对于 $type=1$，直接任意构造出一种方案。

考虑方案数。我们已经得到了矩形的周长，取一种 $l\times r$ 的情况来看，方案一定为将四个角中的一些挖成类似弧形的形状。


对于其中一个角，假设我们要挖去 $k$ 个格，容易发现方案数为 $k$ 的拆分数，于是预处理拆分数 $p_{i,j}$ 为拆 $j$ 个数和为 $i$ 的方案数：

$$p_{i,j}=p_{i-1,j-1}+p_{i-j,j}$$

设 $f_{i,j}$ 为前 $i$ 个角，挖了 $j$ 个格的方案数，枚举第 $i$ 个角挖的格数转移。

$$f_{i,j}\gets f_{i-1,j-k}\times p_k$$

倒序枚举 $j$，可将第一维压掉。

### [代码](https://www.luogu.com.cn/paste/kru7l74w)

---

## 作者：zhouyuhang (赞：0)

哈哈，讲一下场上的弱智做法！

直接快进到 $u=2$。注意到最终形态一定是凸的！正常人这个时候就会想到扣角下来 dp！但是我属于纸张！

记网格大小为 $x\times y$，第 $i$ 列格子数量为 $a_i$，那么有 $a$ 先不减后不增，且中间连续的一段 $a_i=x$。分析可知对于一种序列 $a$，共有 $\prod_{i=1}^{y-1}(|{a_{i+1}-a_i}|+1)$ 种放置的方法。

先不减后不增比较难处理，可以枚举中间极长的 $a_i=x$ 连续段，这样两侧就都可以被看成是不减的了。记 $f_{i,j}$ 为长为 $i$ 的和为 $j$ 的不减序列对应的放置方法之和，有转移 $f_{i,j}=\sum_{k=1,ik\le j}(k+1)f_{i-1,j-ik}$。又有于枚举的是极长连续段，所以序列的第一个不能是 $0$，故 $g_{i,j}=f_{i,j}-f_{i-1,j}$ 是真正的方法数。还没完，由于需要将两侧的合起来，所以对于 $h_{i,j}=h_{i-1,j}+g_{i,j}$，我们需要计算出 $h$ 和 $g$ 的二维卷积即可。不难想到将二维拍到序列上，即取 $B>2\max j$，让 $(i,j)\to iB+j$，之后 MTT 计算。

复杂度 $O(n\log n+T\sqrt n)$，代码没有写。

---

