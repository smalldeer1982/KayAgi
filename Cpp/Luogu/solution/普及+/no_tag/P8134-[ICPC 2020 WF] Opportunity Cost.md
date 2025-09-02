# [ICPC 2020 WF] Opportunity Cost

## 题目描述

正如大多数类型的产品一样，购买新手机可能是困难的。主要的挑战之一是手机有很多不同的方面可能会影响你的选择，比如价格、性能和用户友好性。通常情况下，不会有一款手机在所有这些方面都是最好的：最便宜的手机、最强大的手机和最用户友好的手机可能是不同的手机。

因此，在购买手机时，你必须在你关心的不同方面之间做出一些妥协，选择一款在这些方面达到最佳平衡的手机（当然，“最佳”取决于你的优先级是什么）。衡量这种妥协的一种方法被称为*机会成本*，在这个问题中，我们将其定义如下。

假设你购买了一款价格为 $x$、性能为 $y$、用户友好性为 $z$ 的手机。为了简化问题，我们假设这三个值是在一个可比较的数值尺度上测量的，数值越高越好。如果有 $n$ 款可用的手机，并且 $(x_i, y_i, z_i)$ 表示第 $i$ 款手机的（价格、性能、用户友好性），那么你手机的机会成本定义为

$$\max _{1 \leq i \leq n}\left(\max \left(x_{i}-x, 0\right)+\max \left(y_{i}-y, 0\right)+\max \left(z_{i}-z, 0\right)\right)$$

编写一个程序，给定可用手机的列表，找到机会成本最小的手机。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
20 5 5
5 20 5
5 5 20
10 10 10```

### 输出

```
10 4
```

## 样例 #2

### 输入

```
4
15 15 5
5 15 15
15 5 15
10 10 10```

### 输出

```
10 1```

# 题解

## 作者：fish_love_cat (赞：6)

> KDL：做不做 Ad-hoc？

于是有了这篇题解。

---

观察题面这个式子，注意到三个取最大之间是用加号连接的，这启示我们拆式子进行分讨。

我们对于每一个取最大的运算取到的值进行分讨，总共三个，组合一下共有 $8$ 种情况。

然后我们知道原式的值就是八个互不影响的情况的最大值。于是分别对于每一种情况进行考虑。

观察现在这个式子的形式，注意到每次被减数一定是其他手机某些参数的和，而每个情况这个和的最大值是固定的。

由于只看最大值，所以最后的值只与最大的被减数挂钩。

这启示我们对每个情况预处理最大的被减数即可，然后扫一遍所有手机求答案。

做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005][3];
int b[200005][9];
int mx[9];
int ans=1e18,flc;
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i][0]>>a[i][1]>>a[i][2];
        for(int j=1;j<=8;j++){
            for(int k=0;k<=2;k++)
                b[i][j]+=((j>>k)&1)*a[i][k];
            mx[j]=max(mx[j],b[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        int qwq=0;
        for(int j=1;j<=8;j++)
            qwq=max(qwq,mx[j]-b[i][j]);
        if(ans>qwq)ans=qwq,flc=i;
    }cout<<ans<<' '<<flc;
}
```

---

## 作者：dspt (赞：5)

## 思路
这道题要求编号，所以我们很显然的想到要把每个手机机会成本算出来。这题允许的时间复杂度为 $O(n)$ 或 $O(n\log n)$。由于本题无法将 ${x,y,z}$ 转化为单个值求解，所以不能用二分。那么需要时间复杂度为 $O(n)$ 的算法。

记每个手机需要考虑的因素有 $m$ 个，此题中 $m=3$，但由于复杂度都与 $3$ 有关，写起来不太好看，于是都用 $m$ 来写。

本题的 $\max$ 套 $\max$ 式子中，有非常麻烦的一点就是非负。这个非常难处理，于是我们将式子转化为

$$cost_i=\max\limits_{1\le k\le n} ((0/1)\times(x_i-x_k)+(0/1)\times(y_i-y_k)+(0/1)\times(z_i-z_k))$$

我们将每一位的 $(0/1)$ 记录下来，作为一个 $01$ 串。对于一个 $i$，这个 $01$ 串是确定的。我们如果把每一个 $01$ 计算出来，那么显然是超时的，我们考虑优化。

$\forall0\le j<8$，我们记 $\text{bin}(j,x)$ 为 $j$ 的二进制从左往右的第 $x$ 位，对于 $cost_i$，记  
$a_j=\text{bin}(j,0),\ b_j=\text{bin}(j,1),\ c_j=\text{bin}(j,2),\ 
v_{k,j}=a_j(x_i-x_k)+b_j(y_i-y_k)+c_j(z_i-z_k)$

显然 $a=[x_i>x_k]$，$b,c$ 同理，那么假设 $\{x_i,y_i,z_i\}$ 与 $\{x_k,y_k,z_k\}$ 的大小关系应该用 ${a_p,b_p,c_p}$ 来表示，那么对于 ${a_q,b_q,c_q}(p\neq q)$，有 $v_{k,p}\ge v_{k,q}$。

>  假设 $a_p\neq a_q$（$p,q$ 同理）。  
1.若 $x_i>x_k$，则 $a_p=1,a_q=0,(x_i-x_k)(a_p-a_q)>0$，故 $v_{k,p}>v_{k,q}$  
2.若 $x_i\le x_k$，则 $a_p=0,a_q=1,(x_i-x_k)(a_p-a_q)\ge 0$，故 $v_{k,p}\ge v_{k,q}$

对于 $cost_i$，我们**枚举** $j$，一定能找到的最大值，因为所有错误值（即非最大值）都会被正确值（即最大值）覆盖。于是问题转变为求：

$$\min\limits_{1\le i\le n}\min\limits_{0\le j<8}\max\limits_{1\le k\le n}(a_j(x_i-x_k)+b_j(y_i-y_k)+c_j(z_i-z_k))$$

但是这个的复杂度仍然是 $O(2^mn^2m)$，因为我们在此做了很多重复的操作。$\forall0\le j<8$，我们只需要找到 $w_j=\max\limits_{1\le k\le n} (a_jx_k+b_jy_k+c_jz_k)$，则 $cost_i=\max\limits_{0\le j<8}(a_jx_i+b_jy_i+c_jz_i-w_j)$。

&nbsp;
## 代码
```cpp
#include <stdio.h>
typedef unsigned int ui;
ui w[10], c(3e9);
int a[200005][3], n, s = 1;
int main() 
{
	scanf("%d", &n);
    for (int i(1); i <= n; ++i) 
		for (int j(0); j < 3; ++j) // m = 3
			scanf("%d", &a[i][j]);
	for (int i(1); i <= n; ++i)
		for (int k(0); k < 8; ++k) // 1 << m = 8
		{
			ui sum(0);
			for (int j(0); j < 3; ++j) if ((k >> j) & 1) sum += a[i][j];
			if (sum > w[k]) w[k] = sum; 
		}
    for (int i(1); i <= n; ++i)
    {
    	ui b(0);
    	for (int k(0); k < 8; ++k)
	    {
	    	ui sum(0);
			for (int j(0); j < 3; ++j) if ((k >> j) & 1) sum += a[i][j];
			if (w[k] - sum > b) b = w[k] - sum;
		}
		if (b < c) c = b, s = i; 
	}
	printf("%u %d\n", c, s);
    return 0;
}
```

&nbsp;
## 注意事项

$w_j$ 的值有可能达到 $3\times 10^9$，所以 $w$ 数组等要用 ```unsigned int```。

另外我在此处滚动了 $cost$ 数组，使空间复杂度为 $O(nm)$。

如果一个手机有 $4$ 个因素需要考虑，那么只需要将 $m$ 改为 $4$ 即可，以此类推。

---

## 作者：KDL_ANIPLEX (赞：5)

### 放在前面
[翻译的式子是错的](https://www.luogu.com/discuss/414005)

来一发更加易懂的题解。

### 思路

对于题目中的式子，我们可以通过转化将加号去掉。

$$\max\limits_{1\leqslant i\leqslant n}(\max(0,x_i-x,y_i-y,z_i-z,x_i-x+y_i-y,x_i-x+z_i-z,y_i-y+z_i-z,x_i-x+y_i-y+z_i-z))$$

说人话，式子中的和 $0$ 取最大值，就分 $0$ 更大与更小两种情况。

所以一共有 $8$ 种情况。每种情况都有一个值，就是上面的式子。

为什么将这些值（情况）取最大就是原式的值？

换句话说，为什么一个值（情况）不是最大值，就不是原式的值？

因为较小的值（情况）将原式中，将本该是正数的变成 $0$ 或本该是 $0$ 的变成负数（所以才较小），是错误的；反之最大值是正确的。

将式子整理一下。

$$\max\limits_{1\leqslant i\leqslant n}(\max(0,x_i-x,y_i-y,z_i-z,x_i+y_i-x-y,x_i+z_i-x-z,y_i+z_i-y-z,x_i+y_i+z_i-x-y-z))$$

观察式子，可以发现好做多了，预处理出最大值，再扫一遍即可。

欧对了，$8$ 种情况可以用二进制表示，即 $0$ 至 $7$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
/*
111,110,101,011,100,010,001,000
*/
int n;
struct node {
	int x, y, z;
} a[200005];
int sun[10];
int ans = 1e18, ansid;

signed main() {

	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);

	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i].x >> a[i].y >> a[i].z;
	for (int i = 1; i <= n; i++) {
		for (int k = 0; k < 8; k++) {
			int s = 0;
			if (k % 2) s += a[i].z;
			if (k / 2 % 2) s += a[i].y;
			if (k / 4 % 2) s += a[i].x;
			sun[k] = max(sun[k], s);
		}
	}
	for (int i = 1; i <= n; i++) {
		int g = 0;
		for (int k = 0; k < 8; k++) {
			int s = sun[k];
			if (k % 2) s -= a[i].z;
			if (k / 2 % 2) s -= a[i].y;
			if (k / 4 % 2) s -= a[i].x;
			g = max(g, s);
		}
		if (ans > g)
			ans = g, ansid = i;
	}
	cout << ans << " " << ansid << endl;


	return 0;
}
```

---

## 作者：XiaoQuQu (赞：1)

题意即为求 $\min\limits_{i=1}^n \max\limits_{j=1}^n(\max(x_i-x_j,0),\max(y_i-y_j,0),\max(z_i-z_j,0))$，容易观察到，$x,y,z$ 任意一项，都会产生对答案有贡献或对答案无贡献两种情况，且我们要求的 $\max(x_i-x_j,0),\max(y_i-y_j,0),\max(z_i-z_j,0)$ 即为这 $2^3=8$ 种情况的最大值。我们可以将其状压为一个三位二进制数 $S$，表示贡献的情况。

然后注意到，对于一个确定的 $i$，我们要求的是 $\max\limits_{j=1}^n(\max(0,x_i-x_j,y_i-y_j,z_i-z_j,x_i-x_j+y_i-y_j,\cdots))$，发现 $x_i,y_i,z_i,x_i+y_i,\cdots$ 在 $i$ 确定时已经确定可以提出来，剩下的直接对于每种情况 $S$ 预处理即可。

```cpp
#define int long long

const int MAXN = 2e5 + 5;
int n, a[MAXN][3], mx[8];

void work() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i][0] >> a[i][1] >> a[i][2];
	for (int S = 0; S < (1ll << 3); ++S) {
		for (int i = 1; i <= n; ++i) {
			int tmp = 0;
			for (int k = 0; k < 3; ++k) {
				if (S >> k & 1) tmp += a[i][k];
			}
			mx[S] = max(mx[S], tmp);
		}
	}
	int ans = LLONG_MAX, ansi = 0;
	for (int i = 1; i <= n; ++i) {
		int anss = 0;
		for (int S = 0; S < (1ll << 3); ++S) {
			int tmp = 0;
			for (int k = 0; k < 3; ++k) {
				if (S >> k & 1) tmp += a[i][k]; 
			}
			anss = max(anss, mx[S] - tmp);
		}
		if (anss < ans) ans = anss, ansi = i;
	}
	cout << ans << ' ' << ansi << endl;
}
```





---

