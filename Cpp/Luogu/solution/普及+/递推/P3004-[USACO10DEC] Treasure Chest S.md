# [USACO10DEC] Treasure Chest S

## 题目描述

Bessie and Bonnie have found a treasure chest full of marvelous gold coins! Being cows, though, they can't just walk into a store and buy stuff, so instead they decide to have some fun with the coins.

The N (1 <= N <= 5,000) coins, each with some value C\_i (1 <= C\_i <= 5,000) are placed in a straight line. Bessie and Bonnie take turns, and for each cow's turn, she takes exactly one coin off of either the left end or the right end of the line. The game ends when there are no coins left.

Bessie and Bonnie are each trying to get as much wealth as possible for themselves. Bessie goes first. Help her figure out the maximum value she can win, assuming that both cows play optimally.

Consider a game in which four coins are lined up with these values:

30  25  10  35

Consider this game sequence:

Bessie    Bonnie       New Coin

Player   Side   CoinValue   Total     Total         Line

Bessie   Right     35        35         0       30  25  10

Bonnie   Left      30        35        30         25  10

Bessie   Left      25        60        30           10

Bonnie   Right     10        60        40           --

This is the best game Bessie can play.

小 A 和小 B 在玩游戏。

初始时，有 $n$ 个硬币被摆成了一行，从左至右数第 $i$ 个硬币的价值为 $c_i$。

小 A 和小 B 每人一回合，在一个人的回合中，他可以选择**当前**硬币序列最左侧或者最右侧的硬币，并将他从序列中取出，将其价值累加到自己获得的累计价值中，然后进行另一个人的回合。当硬币全部被取走时，游戏结束。

请求出在双方都尽可能的使自己累计价值最大的情况下，若由小 A 进行第一回合，那么他能获得的累计价值最大是多少。

## 说明/提示

#### 输入输出样例 $1$ 解释

初始时，硬币序列为 $\{30,~25,~10,~35\}$。

第一回合，小 A 取走最右侧的硬币，序列变为 $\{30,~25,~10\}$，小 A 的累加价值为 $35$。

第二回合，小 B 取走最左侧的硬币，序列变为 $\{25,~10\}$，小 B 的累加价值为 $30$。

第三回合，小 A 取走最左侧的硬币，序列变为 $\{10\}$，小 A 的累加价值为 $35 + 25 = 60$。

第四回合，小 B 取走最左侧的硬币，序列变为空，小 B 的累加价值为 $30 + 10 = 40$，游戏结束。

小 A 获得的最大累计价值为 $60$。

#### 数据范围与约定

对于全部的测试点，$1 \leq n \leq 5 \times 10^3$，$1 \leq c_i \leq 5 \times 10^3$。

**提示：请注意，本题的空间限制为 $64$ Mib。**

## 样例 #1

### 输入

```
4 
30 
25 
10 
35 
```

### 输出

```
60 
```

# 题解

## 作者：ghj1222 (赞：26)

不难写出状态：

令`f[l][r]`代表区间`[l,r]`中取钱的最大值，不难写出转移：

`f[l][r] = sum[l][r] - min{f[l + 1][r], f[l][r + 1]}`

`sum[l][r]`是区间和

意思就是区间`[l, r]`由我和对手取，一共取得的是`sum`个，考虑这次我取的是左边的硬币还是右边的硬币，显然我要让对手得到的最小，用区间的和减去对手的最小值就是我的最大值

观察转移方程我们发现一定是长度大的由长度小的转移过来

不难写出程序：

```cpp
#include <bits/stdc++.h>
using namespace std;

int N, a[5010], f[5010][5010], sum[5010][5010];

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= N; i++)
        f[i][i] = a[i];
    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j++)
            sum[i][j] = sum[i][j - 1] + a[j];
    for (int len = 2; len <= N; len++)
        for (int i = 1; i + len - 1 <= N; i++)
            f[i][i + len - 1] = sum[i][i + len - 1] - min(f[i + 1][i + len - 1], f[i][i + len - 2]);
    printf("%d\n", f[1][N]);
    return 0;
}
```

交上去qtmd90pts，MLE一个点，~~把评测鸡吊起来干一顿~~，然后一看内存，woc64MB想搞鬼？？？

然后我们干脆直接优化掉`sum`，用前缀和一减

```cpp
#include <bits/stdc++.h>
using namespace std;

int N, a[5010], f[5010][5010];

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= N; i++)
        f[i][i] = a[i];
    for (int i = 1; i <= N; i++)
        a[i] += a[i - 1];
    for (int len = 2; len <= N; len++)
        for (int i = 1; i + len - 1 <= N; i++)
            f[i][i + len - 1] = a[i + len - 1] - a[i - 1] - min(f[i + 1][i + len - 1], f[i][i + len - 2]);
    printf("%d\n", f[1][N]);
    return 0;
}
```

交上去qtmd90pts，又tmMLE一个点，~~把评测鸡吊起来干一顿~~

然后可以输出数组a的大小，一看100MB(左右)，空间限制是64MB。

然后考虑f数组的使用，我们只用了f数组的一半，所以我们可以开动态内存，避免浪费一般的内存

注意第一维的下标是始终小于第二维的，所以这里偷懒直接把两个下标互换了一下

```cpp
#include <bits/stdc++.h>
using namespace std;

int N, a[5010], *f[5010];

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= N; i++)
    {
        f[i] = new int[i + 2];
        for (int j = 1; j <= i; j++)
            f[i][j] = 0;
        f[i][i] = a[i];
    }
    for (int i = 1; i <= N; i++)
        a[i] += a[i - 1];
    for (int len = 2; len <= N; len++)
        for (int i = 1; i + len - 1 <= N; i++)
            f[i + len - 1][i] = a[i + len - 1] - a[i - 1] - min(f[i + len - 1][i + 1], f[i + len - 2][i]);
    printf("%d\n", f[N][1]);
    for (int i = 1; i <= N; i++)
    {
        delete []f[i];
        f[i] = 0;
    }
    return 0;
}
```

关于C++动态内存的使用：

```cpp
int *p = new int;//申请一个int的空间
int *p = new int[100];//申请100个int的空间，就相当于开大小为100的一维数组
memset(p, 0, sizeof(p));//这样使用是错误的，想一想为什么
delete p;//对应第一行，释放内存
delete []p;//对应第二行的申请数组，释放内存
//如果想申请二维数组可以开一个指针数组(如上面的程序)
```

备注

当然我们可以通过std的vector(变长数组)，这里我没有实现不知道行不行

题解里有一个一维数组的做法，大家尽量参考那一篇(那才是真正的王道)，我这个就是莫名其妙想出来的卡进空间限制的方法

经验/教训：做题要早一点做否则改了内存就gg了

让我们一起膜拜大佬林瑞堂@[olinr](https://www.luogu.org/space/show?uid=88460)

---

## 作者：逝星DS (赞：22)

P3004 【[USACO10DEC]宝箱Treasure Chest】

题目描述

Bessie and Bonnie have found a treasure chest full of marvelous gold coins! Being cows, though, they can't just walk into a store and buy stuff, so instead they decide to have some fun with the coins.

The N (1 <= N <= 5,000) coins, each with some value C_i (1 <= C_i <= 5,000) are placed in a straight line. Bessie and Bonnie take turns, and for each cow's turn, she takes exactly one coin off of either the left end or the right end of the line. The game ends when there are no coins left.

Bessie and Bonnie are each trying to get as much wealth as possible for themselves. Bessie goes first. Help her figure out the maximum value she can win, assuming that both cows play optimally.

Consider a game in which four coins are lined up with these values:

30 25 10 35

Consider this game sequence:

Bessie Bonnie New Coin

Player Side CoinValue Total Total Line

Bessie Right 35 35 0 30 25 10

Bonnie Left 30 35 30 25 10

Bessie Left 25 60 30 10

Bonnie Right 10 60 40 --

This is the best game Bessie can play.

贝西和伯尼找到了一个装满了金币的宝箱！但是，作为奶牛，他们不能随便进入一家商店去买东西。所以他们决定去用这些金币玩一个游戏。

这里有N（1<=N<=5000）个硬币，每个都有一个价值C_i（1<=C_i<=5000）。这些硬币被摆成了一行。贝西和伯尼每人一回合。到了一只奶牛的回合时，他就要拿走最左边或者最右边的硬币。当没有硬币时，游戏结束。

贝西和伯尼都想要使自己拿到的金币价值尽量高，贝西先拿。现在贝西想要你帮帮她，算出她最多可以拿多少钱（伯尼也会尽量取到最优）。

输入输出格式

输入格式：
* Line 1: A single integer: N

* Lines 2..N+1: Line i+1 contains a single integer: C_i

输出格式：
* Line 1: A single integer, which is the greatest total value Bessie can win if both cows play optimally.

输入输出样例

输入样例#1： 复制
4 
30 
25 
10 
35 
输出样例#1： 复制
60 

思路：
一般思路是直接开二维数组，即f[i][j]表示从i到j的最优解，输出答案即
f[1][N];
然而弊端在于这个题目中N<=5000，所以5000*5000必炸（测试点二）（不知道楼上怎么过的题解，难道数据改了？？）
所以针对内存不够的问题，我们可以开一个滚动数组，一遍一遍地更新，数组直接从二维降到一维```

附上代码：

```cpp
#include <iostream>
#define maxN 5010
using namespace std;
int N;
int s[maxN];  //前缀和; 
int f[maxN];  //一维滚动数组; 
int main()  {
	cin>>N;
	int v;
	for(int i=1;i<=N;i++)  {
		cin>>v;
		f[i]=v;  //初始化，f[i]一开始即相当于二维中的f[i][i]； 
		s[i]=s[i-1]+v;  //前缀和累加; 
	}
	for(int l=2;l<=N;l++)  {  //l为长度,注意从2开始； 
		for(int i=1;i+l-1<=N;i++)  {  //枚举head; 
			int j=i+l-1;  //计算出tail; 
			f[i]=s[j]-s[i-1]-min(f[i],f[i+1]);
			//‘s[j]-s[i-1]’为i到j区间总价值，
			//f[i]为从i到i+l-2区间最优解（已在上一步算出，f[i+1]同）; 
		}
	}
	cout<<f[1];  //输出即可; 
	return 0;
}
```

---

## 作者：＂黎筱っ (赞：16)

## $P3004$宝箱

贝西和伯尼找到了一个装满了金币的宝箱！但是，作为奶牛，他们不能随便进入一家商店去买东西。所以他们决定去用这些金币玩一个游戏。

这里有$N(1\leq N\leq 5000)$个硬币，每个都有一个价值$C_i(1\leq C_i\leq 5000)$。这些硬币被摆成了一行。贝西和伯尼每人一回合。到了一只奶牛的回合时，他就要拿走最左边或者最右边的硬币。当没有硬币时，游戏结束。

贝西和伯尼都想要使自己拿到的金币价值尽量高，贝西先拿。现在贝西想要你帮帮她，算出她最多可以拿多少钱（伯尼也会尽量取到最优）。



区间$DP$。设$f[l][r]$为区间$[l,r]$能取到的最大值。

转移显然为$f[l][r] = sum[l][r] - min(f[l+1][r], f[l][r-1])$

当然这么写是不行的。因为空间限制是$64MB$，直接$MLE$

于是尝试压缩空间。$sum[i][j]$显然可以用前缀和相减，关键是$f$怎么压成一维。

观察状态转移

```cpp
for(int l = 2; l <= n; ++l)
        for(int i = 1; i + l - 1 <= n; ++i)
            f[i][i + l - 1] = a[i + l - 1] - a[i - 1] - 
            				min(f[i + 1][i + l - 1], f[i][i + l - 2]);
```

每个点是由左边和下边的点更新来的，每次更新完一列之后，其左边的一列就没有用了。于是可以滚动数组。只保留当前列。

$f[i]$表示：以$i$为起点，长度为$len$的区间能取到的最大值。

因为每次进入第二循环的时候，$len++$，所以未修改的$f[i]$就表示以$i$为起点，长度为$len - 1$的区间能取到的最大值。$len$是当前的$len$。

所以可以这么写：

```cpp
for(int l = 2; l <= n; ++l)
        for(int i = 1; i + l - 1 <= n; ++i)
            f[i] = a[i + l - 1] - a[i - 1] - min(f[i + 1], f[i]);
```

代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long read(){
    long long x = 0; int f = 0; char c = getchar();
    while(c < '0' || c > '9') f |= c == '-', c = getchar();
    while(c >= '0' && c <= '9') x = (x <<1) + (x << 3) + (c ^ 48), c = getchar();
    return f? -x:x; 
}

int n, a[5005], f[5005];
int main(){
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i <= n; ++i) f[i] = a[i], a[i] += a[i - 1];
    for(int l = 2; l <= n; ++l)
        for(int i = 1; i + l - 1 <= n; ++i)
            f[i] = a[i + l - 1] - a[i - 1] - min(f[i + 1], f[i]);
    printf("%d\n", f[1]);
    return 0;
}
```



---

## 作者：Kinandra (赞：13)

看了好像都是DP的做法, 我发一个贪心的做法, 目前还不会证明, 欢迎大家一起讨论证明(或**证伪**).

考虑剩$3$个数$a_1, a_2, a_3$且$a_2>a_1,a_2>a_3$, 那么先手能比后手多取到$a_1+a_3-a_2$, 我们于是我们将形如$a_i>a_{i+1}, a_i>a_{i-1}$的缩成一个数$a_{i+1}+a_{i-1}-a_i$,**反复操作**直到$\exists j,s.t.\forall i<j,a_{i+1}< a_i$且$\forall i>j,a_{i-1}< a_{i}$,即函数变为以$j$为谷值点的**单谷函数**.

时间容易用栈做到$\mathcal O(n)$.

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int read();
int n;
int st[1000005], top;
long long sum = 0;
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        int x = read();
        sum += x;
        st[++top] = x;
        while (top >= 3 && st[top - 1] >= st[top] && st[top - 1] >= st[top - 2])
            st[top - 2] = -(st[top - 1] - st[top] - st[top - 2]), top -= 2;
    }
    int l = 1, r = top;
    long long res = 0;
    while (l <= r) {
        if (st[l] > st[r])
            res += st[l++];
        else
            res += st[r--];
        if (l > r) break;
        if (st[l] > st[r])
            res -= st[l++];
        else
            res -= st[r--];
    }
    printf("%lld %lld\n", (res + sum) / 2);
    return 0;
}
int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```


---

## 作者：K0stlin (赞：7)

首先，我们先来看一下此题目处理数据的过程：

要么一排硬币左边被拿走，要么右边被拿走。

所以有DP经验的OIER们基本能看出来了：

## 区间DP

左边被拿走:区间[L,R]->[L+1,R]

右边被拿走:区间[L,R]->[L,R-1]

故可以写出方程：F[L,R]=SUM[R]-SUM[L-1]-MIN(F[L+1,R],F[L,R-1])

(解释：SUM[X]为前缀和（1~X），F[X,Y]是贝西取得最大值（此时贝西取），SUM[X]-SUM[Y-1]-F[X,Y]即是伯尼取得最小值，故F[L,R]=原式=[L,R]总价值-[L,R]伯尼所取最小值=[L,R]贝西所取最大值）

**但是**，很快我们发现F[5000,5000]空间会炸，所以用DP缩空间神器——**滚动数组**：F[R%2][L]=SUM[R]-SUM[L-1]-MIN(F[R%2][L+1],F[(R-1)%2][L])

再用二进制优化：F[R&1][L]=SUM[R]-SUM[L-1]-MIN(F[R&1][L+1],F[!(R&1)][L])

上代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,a,sum[5005],f[3][5005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a);
		sum[i]=sum[i-1]+a;
		f[1][i]=a;//因为下文j（阶段）从2开始，所以为F[(j-1)%2][i],即F[1][i]
	}
	for(int j=2;j<=n;++j)//枚举区间右端点
		for(int i=j;i>=1;--i)//枚举区间左端点
			f[j&1][i]=sum[j]-sum[i-1]-min(f[!(j&1)][i],f[j&1][i+1]);//转移方程
	printf("%d\n",f[n&1][1]);//即F[1][N]
	return 0;
}

```
-完-

---

## 作者：125E591 (赞：7)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int s[5002];//前缀和 
int f[5002][5002];//f[i][j]表示她在i-j间的最优拿法 
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s[i]);
		f[i][i]=s[i];
		s[i]+=s[i-1];
	}
	for(int k=2;k<=n;k++)//k表示区间长度 
	for(int i=1;i+k-1<=n;i++) 
	{
		int j=i+k-1;
		f[i][j]=s[j]-s[i-1]-min(f[i][j-1],f[i+1][j]);
	}
	cout<<f[1][n];
	return 0;
}
```
这个代码显然超出了空间限制,所以我们要进行压维
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int s[5002];//前缀和 
int f[5002];//f[i]表示她以i开头的最优拿法(滚动数组)
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s[i]);
		f[i]=s[i];
		s[i]+=s[i-1];
	}
	for(int k=2;k<=n;k++)//k表示区间长度 
	for(int i=1;i+k-1<=n;i++) 
	{
		int j=i+k-1;
		f[i]=s[j]-s[i-1]-min(f[i],f[i+1]);//此时f[i]记录的是以i开头长度为j的最优拿法 
	}
	cout<<f[1];
	return 0;
}
```

如果有错误请dalao指出


---

## 作者：tuliwei (赞：6)

# 看到没有贪心的题解，赶紧水一发
---------------
## 分情况讨论 ：
- 单调:直接从大的往小的取即可(~~显然~~)
- 呈V型:
	1. 两侧不相等 ：直接消掉相等的即可
	2. 挑大的那一边取
- 呈/\型(**重点**):   
	假设有一段长这样：  
    $\ $ $\ $ $\ $ $......a1,a2,a3...... (a1 \leq a2, a2 \geq a3)$   
    那么我们可以把它变成 $......(a1+a3-a2)......\ $(~~玄学~~)   
    (关于正确性~~可以打表证明~~我也不会证……但它是对的)   
    

------------

### 代码：

```cpp   

#include <bits/stdc++.h>

using namespace std;

int stk[5005], top;
int n, x, sa, sb, sum;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x), sum += x;
		stk[++top] = x;
		while (top > 2 && stk[top - 1] >= stk[top - 2] && stk[top - 1] >= stk[top])
			stk[top - 2] = stk[top - 2] + stk[top] - stk[top - 1], top -= 2;//重点在此
	}

	int l, r;
	for (l = 1, r = top; l < r; ) {
		if (stk[l] == stk[r]) { ++l, --r; continue; }
		if (stk[l] > stk[r])
			sa += stk[l++];
		else sa += stk[r--];
		if (stk[l] > stk[r])
			sb += stk[l++];
		else sb += stk[r--];
	}
	if (l == r) sa += stk[l];
	sa = (sum - (sb - sa)) >> 1;
	printf("%d\n", sa);
	return 0;
}

```


---

## 作者：wwq123 (赞：4)

1.这道题与P2734的《游戏 A Game》极为相似，但数据较大，根据n的大小，我们最多使用2维的数组，这是极限

2.选的人只能从最左或最右拿，dp[i][j]表示的是在i~j之间的最优拿法，dp[i+1][j]则是另一个人的最优拿法

3.状态转移方程为dp[i][j]=max(su[j]-su[i-1]-dp[i+1][j],su[j]-su[i-1]-dp[i][j-1])，其中su[i]是前i个数字的和，所以su[j]-su[i-1]就是i~j的所有数的和，这样一来，减去dp[i+1][j]或减去dp[i][j-1]就相当于从最前或最后拿的最优解

4.i之所以倒着来写，主要是写法的问题，读者可以自行进行修改

以下为代码（如有冗余还望见谅）

```cpp
#include<iostream>
using namespace std;
const int MAXN=5000+2;
int dp[MAXN][MAXN];
int su[MAXN],k[MAXN];
int n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>k[i];
        su[i]+=su[i-1]+k[i];
        dp[i][i]=k[i];
    }
    for(int i=n-1;i>=1;i--){
        for(int j=i+1;j<=n;j++){
            dp[i][j]=max(su[j]-su[i-1]-dp[i+1][j],su[j]-su[i-1]-dp[i][j-1]);
        }
    }
    cout<<dp[1][n]<<endl;
    return 0;
}
```

---

## 作者：览遍千秋 (赞：3)

## [My blog](https://www.cnblogs.com/liubainian/)

---

## 问题描述

[LG3004](https://www.luogu.org/problem/P3004)

---

## 题解

把拿走的过程反向，看做添加的过程，于是很显然的区间DP模型。

设$opt_{i,j}$代表区间$[i,j]$中Bessie可以获得的最大值，显然有

$$opt_{l,r}=sum_{l,r}-min(opt_{l+1,r},opt_{l,r+1})$$

于是爆了空间。

强行压成一维，滚动数组优化即可。

---

## $\mathrm{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-'){
		fh=-1;ch=getchar();
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

const int maxn=5007;

int s[maxn],opt[maxn],n;

int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(opt[i]);s[i]=s[i-1]+opt[i];
	}
	for(int len=2;len<=n;len++){
		for(int l=1;l+len<=n+1;l++){
			int r=l+len-1;
			opt[l]=s[r]-s[l-1]-min(opt[l],opt[l+1]);
		}
	}
	printf("%d\n",opt[1]);
	return 0;
}
```

---

## 作者：LikC1606 (赞：2)

### 题意
给出长为n的序列，有两个人，轮流拿最左边或最右边的，且两个人的拿法的是最优的，写一个程序，判断第一个人能拿到的的最大值。
### 做法
动态规划，表示从i开始拿长度为L的序列的先手比后手多的分值因为内存的关系，所以我们要用滚动数轴，因为递推的值只与前一个值有关。拿法只有两种，所以只要max求最大值即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int f[2][5001];//动态规划，表示从i开始拿长度为L的序列的先手比后手多的分值 
int sum;
int a[5001];
int main()
{
	scanf("%d",&n);
	int o=1;
	for(int i=1;i<=n;++i)
	scanf("%d",&a[i]),f[o][i]=a[i],sum+=a[i]; 
	for(int i=2;i<=n;++i)
	{
		for(int j=1;j+i-1<=n;++j)
		   f[o^1][j]=max(a[j]-f[o][j+1],a[j+i-1]-f[o][j]);//max求最大值，分别是拿左边的和拿右边的 
		o^=1;
	} 
	printf("%d\n",(sum+f[o][1])/2);
	return 0;
}
```


---

## 作者：StephenYoung (赞：2)

最开始的时候就看了一下这个题目，觉得只是一个简单的模拟，怎么可以的“提高+/省选-”呢？

大概思路就如下了，设两个指针：begin与end，初始化begin=1，end=n，如果a[begin]>=a[end]的话，加进a[begin],begin++;反之，就操作end，代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=50005;
int n,c[maxn],begin,end,cnt,ans[5];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
	}
	begin=1;
	end=n;
	while(begin<=end)
	{
		cnt++;
		if(c[begin]>=c[end])
		{
			ans[cnt%2]+=c[begin];
			begin++; 
		}
		else ans[cnt%2]+=c[end],end--;
	}
	printf("%d",ans[1]);
	return 0; 
} 
```
但是只过了一半！

于是再看看这个题，想到用dp来优化，当然，我用了滚动数组，思路：

对于一段区间（i，j），我们有两种决策，选i或者j

于是

定义$f[i][j]$为当前玩家对于区间$[i,j]$的最优策略

边界$f[i][j]=0,f[i][i]=a[i]$

状态转移：

$f[i][j]$=$max$

$(sum(i+1,j)$−$f[i+1][j]$+$a[i]$,
$sum(i,j-1)$−
$f[i][j-1]$+$a[j])$

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000010

int n,a[maxn],f[3][maxn],s[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		f[i&1][i]=a[i];
		s[i]=s[i-1]+a[i];
	}
	for(int l=2;l<=n;l++)
	{
		for(int i=1;(i+l-1)<=n;i++)
		{
			int j=i+l-1;
			f[i&1][j]=max(s[j]-s[i]-f[(i+1)&1][j]+a[i],s[j-1]-s[i-1]-f[i&1][j-1]+a[j]);
		}
	}
	printf("%d",f[1][n]);
	return 0;
}
```


---

## 作者：kkxhh (赞：1)

我们定义**状态 d[l][r] 为在区间[l,r]先手的人（牛）能取到的最大值**。显然，区间的长度每加1，先手的人就会互换一次，于是为了让这一次的先手更大，就要让上一次的先手更小，于是我们就可以得到状态状态转移方程。

### d[l][r]=sum[r]-sum[l-1]-min(d[l][r-1],d[l+1][r])
**（sum是前缀和数组）**

### 这样写出来的代码如下

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n,a[5010],sum[5010]={0},d[5010][5010]={0};

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?-1:k,c=getchar();
    while(c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
    return num*k;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(a[i]=d[i][i]=read());
    for(int len=2;len<=n;len++)
        for(int l=1,r=l+len-1;r<=n;l++,r++)
            d[l][r]=sum[r]-sum[l-1]-min(d[l][r-1],d[l+1][r]);
    printf("%d",d[1][n]);
    return 0;
}
```

然而，这样交上去会MLE一个点~~（这题真是毒瘤）~~，于是我们还需要再用一个滚动数组

### 真正的代码如下

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n,a[5010],sum[5010]={0},d[2][5010]={0},k=0;

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?-1:k,c=getchar();
    while(c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
    return num*k;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(a[i]=d[k][i]=read());
    //很毒瘤的强行压行，不过实际上只是处理了一下前缀和以及区间长度为1时的情况
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++)
            d[k^1][l]=sum[l+len-1]-sum[l-1]-min(d[k][l],d[k][l+1]);
        k^=1;//因为 1^1=0 0^1=1 于是这样就可以反复在两个数组间滚动
    }
    printf("%d",d[k][1]);
    return 0;
}
```

---

## 作者：huayucaiji (赞：0)

设f[i,j]为从第i堆到第j堆先手可获得的最大利润;s[i]为前i堆金币数总和。易得转移方程：

# f[i,j]=s[j]-s[i-1]-min(f[i+1,j],f[i,j-1])


有3种方法，详见注释。
```cpp
#include<bits/stdc++.h>
using namespace std;
/*法一：递归，速度慢，要用记忆法搜索。
int memo[200][200];
bool calc[200][200];
int f(int i,int j)
{
	if(calc[i][j]==1)
	{
		return memo[i][j];
	}
	int ret=s[j]-s[i];//核心公式 
	ret-=min(f(i+1,j),f(i,j-1));//核心公式 
	calc[i][j]=1;
	memo[i][j]=ret;
	return ret;
}*/ 
int main()
{
	int n;
	cin>>n;
	int c[n+1],s[n+1],f[n+1];
	memset(s,0,sizeof(s));
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		f[i]=c[i];
		s[i]=s[i-1]+c[i];
	} 
	/*法二：递推，速度快，易错。*/ 
	for(int i=n;i>=1;i--)
	{
		for(int j=i+1;j<=n;j++)
		{
			f[j]=s[j]-s[i-1]-min(f[j],f[j-1]);//核心公式 
		}
	}
	cout<<f[n];
	/*法三 ：点长式 ,较难理解，但实用。 
	for(int len=2;len<=n;len++)
	{
		for(int i=1;i+len-1<=n;i++)
		{
			j=i+len-1;
			1：f[i][j]=s[j]-s[i]-min(f[i+1][j],f[i][j-1]);//核心公式 
			2：g[i]=s[j]+s[i-1]-min(g[i],g[i+1]); //滚动数组，省内存。输出g[1] 
		}
	}*/ 
}
```

温馨提示：
用二维数组会超时哦！！！

---

