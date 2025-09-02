# [ABC374E] Sensor Optimization Dilemma 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc374/tasks/abc374_e

ある製品の製造には $ 1,2,\dots,N $ の番号が付いた $ N $ 個の工程が必要です。

各工程 $ i $ について、それを処理する $ 2 $ 種類の機械 $ S_i,T_i $ が売られています。

- 機械 $ S_i $ : $ 1 $ 台につき $ 1 $ 日あたり製品 $ A_i $ 個分の処理ができ、 $ 1 $ 台 $ P_i $ 円で導入できる
- 機械 $ T_i $ : $ 1 $ 台につき $ 1 $ 日あたり製品 $ B_i $ 個分の処理ができ、 $ 1 $ 台 $ Q_i $ 円で導入できる

それぞれの機械は $ 0 $ 台以上何台でも導入できます。

機械の導入の結果、工程 $ i $ を $ 1 $ 日あたり製品 $ W_i $ 個分処理できるようになったとします。  
このとき、製造能力を $ W $ の最小値、すなわち $ \displaystyle\ \min^{N}_{i=1}\ W_i $ と定義します。

全体の予算が $ X $ 円のとき、達成可能な製造能力の最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 100 $
- $ 1\ \le\ A_i,B_i\ \le\ 100 $
- $ 1\ \le\ P_i,Q_i,X\ \le\ 10^7 $

### Sample Explanation 1

例えば、次の通り機械を導入することで製造能力を $ 4 $ にすることができ、これが達成可能な最大値です。 - 工程 $ 1 $ に対し機械 $ S_1 $ を $ 2 $ 台導入する。 - $ 1 $ 日あたり製品 $ 4 $ 個分の処理に相当し、導入に合計 $ 10 $ 円かかる。 - 工程 $ 2 $ に対し機械 $ S_2 $ を $ 1 $ 台導入する。 - $ 1 $ 日あたり製品 $ 1 $ 個分の処理に相当し、導入に合計 $ 1 $ 円かかる。 - 工程 $ 2 $ に対し機械 $ T_2 $ を $ 1 $ 台導入する。 - $ 1 $ 日あたり製品 $ 3 $ 個分の処理に相当し、導入に合計 $ 3 $ 円かかる。 - 工程 $ 3 $ に対し機械 $ T_3 $ を $ 2 $ 台導入する。 - $ 1 $ 日あたり製品 $ 4 $ 個分の処理に相当し、導入に合計 $ 8 $ 円かかる。

### Sample Explanation 3

正の製造能力が得られない場合もあります。

## 样例 #1

### 输入

```
3 22
2 5 3 6
1 1 3 3
1 3 2 4```

### 输出

```
4```

## 样例 #2

### 输入

```
1 10000000
100 1 100 1```

### 输出

```
1000000000```

## 样例 #3

### 输入

```
1 1
1 10000000 1 10000000```

### 输出

```
0```

## 样例 #4

### 输入

```
10 7654321
8 6 9 1
5 6 4 3
2 4 7 9
7 8 9 1
7 9 1 6
4 8 9 1
2 2 8 9
1 6 2 6
4 2 3 4
6 6 5 2```

### 输出

```
894742```

# 题解

## 作者：Binah_cyc (赞：15)

本文给出一个看似是乱搞的正解并且给出了证明。

## 做法：

本题二分显然，二分每一个步骤需要达到的生产力，然后考虑对二分出的答案进行判断。

判断时考虑贪心，对于每一个步骤，性价比更劣的那一台机器我们最多使用 $100$ 台，这样跑的飞快，并且是正确的。

示例代码：
```c
// Problem: E - Sensor Optimization Dilemma 2
// Contest: AtCoder - KEYENCE Programming Contest 2024（AtCoder Beginner Contest 374）
// URL: https://atcoder.jp/contests/abc374/tasks/abc374_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,X;
struct Node
{
	pair<int,int> a,b;
}x[105];

int work(int k,int mid)
{
	int cnt=INT_MAX;
	for(int i=0;i<=100;i++)
		cnt=min(cnt,x[k].b.second*i+(mid-x[k].b.first*i+x[k].a.first-1)/x[k].a.first*x[k].a.second);
	//枚举机器b使用多少个，快速计算总答案
	return cnt;
}
bool check(int mid)
{
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=work(i,mid);
	return cnt<=X;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>X;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i].a.first>>x[i].a.second>>x[i].b.first>>x[i].b.second;
		if(1.0*x[i].a.second/x[i].a.first>1.0*x[i].b.second/x[i].b.first) swap(x[i].a,x[i].b);//钦定机器a是性价比更高的机器
	}
	int l=0,r=1e9,ans;//能达到的最大生产力为1e9
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}
```

## 证明

对于每一个步骤，我们设该步骤使用了 $x$ 台 A 机器与 $y$ 台 B 机器，二分出来的最低生产力要求为 $k$，显然，有 $Ax+By \ge k$。

因为 $A,B \le 100$，所以 $Ax+By-k \le 100$，设它等于 $c$。

现在，我们假设先全都使用机器 A，我们可以得到 $c_0$，然后减少 $1$ 个 A 机器的数量，并使用 B 机器代替它，就可以得到 $c_1$，再减少一个 A 并使用 B 代替它，得到 $c_2$，等等。

因为 $c$ 只有 $100$ 个取值，所以它**在 $100$ 以内必定存在循环节**。考虑到这里，结论也就呼之欲出了。

---

## 作者：zzk2010 (赞：9)

省流：二分+小学数学

注意到 $N \le 100$ 和 $A_i,B_i \le 100$，这个数据范围比较小，很可能与时间复杂度有关。

题目要求 $\displaystyle W=\min_{i=1}^N W_i$ 的最大值，看到最小值最大，果断二分。于是思路就出来了：二分 $W$，看能否用 $X$ 的预算达到。

具体来讲，二分 $W$，对于第 $i$ 轮加工，我们要使 $W_i \ge W$，也就是找到这样的 $a_i,b_i$，使得 $W_i = a_iA_i+b_iB_i \ge W$ 且 $\sum_{i=1}^N a_iP_i+b_iQ_i \le X$。

要想不超过预算，花费就得尽可能少，也就是要使 $a_iP_i+b_iQ_i$ 最小，同时要让 $a_iA_i+b_iB_i \ge W$。这不禁让人想起小学数学题：
> 有一群人要租车。有小客车、大客车。怎样租车最便宜？

这种问题烦人之处在于，有的时候你不仅要选最划算的车，还要让座位的利用率高（我反正只会凑答案……）。购入机器也是一样的。但是每种机器购入多少台呢？

这就引出本题的一个结论：第 $i$ 轮加工的两种机器中，必有一种的购入数量少于另一种的单台机器产量。

换句话说，如果你主要购入 $S_i$，那么你购入的 $T_i$ 的数量少于 $A_i$。反之亦然。

这是因为，每当你购入 $B_i$ 台 $S_i$ 或 $A_i$ 台 $T_i$，你都会获得 $A_iB_i$ 的产量。而对于相同的 $A_iB_i$ 的产量，为使花费最少，一定只会选择两种方案中更便宜的那一种（也就是 $\min(B_iP_i,A_iQ_i)$）。所以，当你主要购入 $S_i$ 的时候（此时 $B_iP_i \le A_iQ_i$），每当你购入 $A_i$ 台 $T_i$，你都可以将其换成更优的 $B_i$ 台 $S_i$。

那么我们直接在二分里面枚举 $S_i$ 或 $T_i$ 的数量，取花费最小值即可。

代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 105
using namespace std;
int a[N], b[N], p[N], q[N], n, X;
bool check(int x) {
	int sum = 0;  //达到x生产容量的最小花费 
	for(int i = 1; i <= n; i++) {
		int res = 1e15;   //寻找最小花费 
		for(int j = 0; j < a[i]; j++) {
			//枚举主要购买Si时，购入的Ti数量 
			if(j*b[i] > x) break;
			int tmp = x-j*b[i];
			res = min(res, j*q[i]+(tmp+a[i]-1)/a[i]*p[i]);
		}
		for(int j = 0; j < b[i]; j++) {
			//枚举主要购买Ti时，购入的Si数量 
			if(j*a[i] > x) break;
			int tmp = x-j*a[i];
			res = min(res, j*p[i]+(tmp+b[i]-1)/b[i]*q[i]);
		}
		sum += res;
	}
	return sum <= X; 
}
signed main() {
	cin >> n >> X;
	for(int i = 1; i <= n; i++) cin >> a[i] >> p[i] >> b[i] >> q[i];
	int l = 0, r = 1e10, mid;   //二分W（上界差不多1e9吧） 
	while(l <= r) {
		mid = (l + r) >> 1;
		if(check(mid)) l = mid+1;
		else r = mid-1;
	}
	cout << l-1;
	return 0;
}
```

---

## 作者：lunjiahao (赞：4)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc374_e)

[AT题目传送门](https://atcoder.jp/contests/abc374/tasks/abc374_e)
### 题目大意：
给定 $n$ 道工序，你有 $X$ 元的资金，对于第 $i$ 道工序，有两种机器供你选择，第一种机器可以花费 $P_i$ 元处理 $A_i$ 个产品，第二种机器可以花费 $Q_i$ 元处理 $B_i$ 个产品。

钦定第 $i$ 天处理的产品个数为 $W_i$，求在总花费不超过 $X$ 元的前提下，最大化 $\min_{i=1}^{n} W_i$。

数据范围：$1 \leq n,A_i,B_i \leq \color{red}100 \color{black},1 \leq P_i,Q_i,X \leq 10^7$。

### 题目分析：
看到这个最大化最小值就想到要使用二分答案了。

在 `check` 函数中，我们考虑进行两次 `for` 循环，第一次循环枚举选第一个机器的个数，从大到小枚举，起始点为 $\lfloor \frac{mid}{A_i} \rfloor +1$，终止点为 $\lfloor \frac{mid}{A_i} \rfloor - L$，（这里 $L$ 先留个悬念后面再提），第二次循环以此类推，每次取费用最小的相加与总花费 $X$ 比较即可。

`check` 函数实例：
```cpp
bool check(int mid)
{
	int sum=0;//本次 check 的总花费
	for(int i=1;i<=n;i++)
	{
		int s=INF;//第 i个工序的最小花费
		//枚举选第一个机器的个数 
		for(int j=mid/a[i]+1;j>=max(mid/a[i]-100,0ll);j--)//下界要与 0 取 max 
		{
			int y=max(0ll,mid-j*a[i]+b[i]-1);
			//这里其实是我懒，不想打 if 判断余数，所以就加了 (b[i]-1)，顺便规避了负数会导致计算出错的问题 
			s=min(s,j*p[i]+y/b[i]*q[i]);
		}
		//同理 
		for(int j=mid/b[i]+1;j>=max(mid/b[i]-100,0ll);j--)
		{
			int y=max(0ll,mid-j*b[i]+a[i]-1);
			s=min(s,j*q[i]+y/a[i]*p[i]);
		}
		sum+=s;
	}
	return sum<=x;
}
```
好了这里上述程序的 $L$ 取了 $100$ 左右，原因是 $A_i,B_i \leq 100$，两种机器都能处理到 $A_iB_i$，既可以变化的产品最多到 $\Delta=\operatorname{lcm}(A_i,B_i)$ 即可。

因为对于上述的 `check` 枚举的是机器个数，故对于第一个机器的下界取到 $\max(0,\lfloor \frac{mid}{A_i} \rfloor -\frac{\Delta}{A_i})$ 即可，即对于这变化的产品不再使用第一个机器处理，转而使用第二个机器处理，计算花费即可，枚举第二个机器的数量同理。

时间复杂度：$O(L \log V)$，其中 $L \approx A_i+B_i \leq 200,V=10^9$，$V$ 为二分答案的值域。

### Code:
赛时代码写得有点丑 :)
```cpp
#include<bits/stdc++.h>
#define int long long//只是怕有可能爆 int，实际上应该不会爆
using namespace std;
const int N=105,INF=2e9;
int n,x,a[N],b[N],p[N],q[N];
bool check(int mid)
{
	int sum=0;//本次 check 的总花费
	for(int i=1;i<=n;i++)
	{
		int s=INF;//第 i个工序的最小花费
		//枚举选第一个机器的个数 
		for(int j=mid/a[i]+1;j>=max(mid/a[i]-100,0ll);j--)//下界要与 0 取 max 
		{
			int y=max(0ll,mid-j*a[i]+b[i]-1);
			//这里其实是我懒，不想打 if 判断余数，所以就加了 (b[i]-1)，顺便规避了负数会导致计算出错的问题 
			s=min(s,j*p[i]+y/b[i]*q[i]);
		}
		//同理 
		for(int j=mid/b[i]+1;j>=max(mid/b[i]-100,0ll);j--)
		{
			int y=max(0ll,mid-j*b[i]+a[i]-1);
			s=min(s,j*q[i]+y/a[i]*p[i]);
		}
		sum+=s;
	}
	return sum<=x;
}
signed main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>p[i]>>b[i]>>q[i]; 
	int l=0,r=1e9,ans=0;//一定要取到 10^9
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：3)

# E - Sensor Optimization Dilemma 2

事奇怪做法（悲）。

## Description

一个产品制造，需要 $n$ 个流程。

其中每一个流程都有两个特殊的机器，$S_i$ 和 $T_i$。

- $S_i$ 每台每天能够处理 $A_i$ 件产品，报价 $P_i$ 元。
- $T_i$ 每台每天能够处理 $B_i$ 件产品，报价 $Q_i$ 元。

你可以同时买两种，也可以一个都不买。只要你想买，机器提供无限个。

假设由于引入了机器，流程 $i$ 每天可以处理 $W_i$ 个产品。

因为产品需要 $n$ 个流程，所以每天的产品数量，定义为 $W_i$ 的最小值。

你现在有 $X$ 的预算，求每一天能够生产最多多少个产品。

## Solution

这个东西非常可以二分。

二分生产的产品数量 $x$，计算出当前的预算，和 $X$ 比大小。

这样只需要对于每一个流程 $i$，算出满足生产数量 $x$ 的最小预算 $w_i$，最后加起来就可以了。

---

计算出 $S_i$ 平均生产每一个产品的报价 $\frac{P_i}{A_i}$，$T_i$ 平均生产每一个产品的报价 $\frac{Q_i}{B_i}$。

将这两个平均价格比大小。

显然价格更大的那一个机器更亏，不会买很多个嘛！

所以枚举亏的机器的数量，从 0 枚举到 200。

在这中间取一个最小值，~~大概就是真的最小值~~。

最后交上去，发现过了。

时间复杂度 $O(CN\log K)$。

$K$ 是你二分的区间大小，因为答案的上界为 $10^9$，所以取 $10^9$ 就可以了。

$C$ 是你猜测亏的那个机器的最多数量，这个因人而异，我取的 200。

反正最后能过，跑得还挺快。~~就是不知道对不对。~~

---

## 作者：forever_nope (赞：2)

思路来自こたつがめ（kotatsugame）大佬的视频。

---

首先，容易想到我们可以二分答案 $W$（最大生产力），对于每一个工程令生产力总和 $\ge W$，然后计算出来所需花费，判断是否 $\le X$ 即可。

对于一个工程 $\langle A,P,B,Q\rangle$，我们需要找到两个机器的生产力 $x,y\ge0$ 满足 $Ax+By\ge W$ 的条件下，最小化 $Px+Qy$ 的值。

$$
\begin{aligned}
&Ax+By\ge W\\
\Longrightarrow\quad&y\ge\left\lceil\dfrac{W-Ax}{B}\right\rceil\\
\Longrightarrow\quad&y=\max\left(0,\left\lceil\dfrac{W-Ax}{B}\right\rceil\right)
\end{aligned}
$$

不妨使用带余除法分解 $x$：

$$
x=x_1B+x_0\quad(0\le x_0<B)
$$

那么，使用顶函数的性质：

$$
\begin{aligned}
y&=\max\left(0,\left\lceil\dfrac{W-Ax}{B}\right\rceil\right)\\
&=\max\left(0,\left\lceil\dfrac{W-Ax_0}{B}-Ax_1\right\rceil\right)\\
&=\max\left(0,\left\lceil\dfrac{W-Ax_0}{B}\right\rceil-Ax_1\right)\\
\end{aligned}
$$

不妨记：

$$
w=\left\lceil\dfrac{W-Ax_0}{B}\right\rceil
$$

则：

$$
y=\max\left(0,w-Ax_1\right)
$$

---

我们考虑直接枚举 $x_0$ 为常数并钦定后面的式子 $\ge0$，

$$
w-Ax_1\ge0 \iff x_1\le\left\lfloor\dfrac{w}{A}\right\rfloor
$$

此时：

$$
\begin{aligned}
Px+Qy&=Px_0+Qw+PBx_1-QAx_1\\
&=Px_0+Qw+(PB-QA)x_1
\end{aligned}
$$

是关于 $x_1$ 的一次函数，不妨两个端点都直接记入贡献。

---

然后考虑后面的式子 $\le0$ 即：

$$
x_1>\left\lfloor\dfrac{w}{A}\right\rfloor=\left\lfloor\dfrac{w}{A}\right\rfloor+1
$$

那么：

$$
Px+Qy=P(x_0+Bx_1)
$$

---

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl "\n"

using ll = long long;

#define int ll

int n, x;

struct pt {
    int a, p;
    int b, q;
};

vector<pt> process;

bool check(int W) {
    int rest = x;
    for (auto [a, p, b, q] : process) {
        int cost = rest + 1;
        for (int x0 = 0; x0 < b; ++x0) {
            int w = (max(0ll, W - a * x0) + b - 1) / b;
            int base = p * x0 + q * w;
            int add = p * b - q * a;
            int lx = 0, rx = w / a;
            cost = min({
                cost,
                p * (x0 + b * (rx + 1)),
                base + add * lx,
                base + add * rx
            });
        }
        if ((rest -= cost) < 0)
            return false;
    }
    return true;
}

void Main() {
    cin >> n >> x;
    process.resize(n);
    for (auto &[a, p, b, q] : process)
        cin >> a >> p >> b >> q;
    int l = 0, r = 1e9;
    int ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    cout << ans << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    return Main(), 0;
}

```

---

## 作者：Running_a_way (赞：2)

[cnblogs](https://www.cnblogs.com/Running-a-way/p/18448870)

好题。爱做。

---
标签：二分。

求最大的最小值，考虑二分答案。然后问题就转化成了（求 $n$ 次）：有两种物品，每种物品有一个代价和价值，求获得**不少于**给定价值所需的最小代价。

下文记物品的代价为 $w$，价值为 $v$，所拿的数量为 $cnt$。

假设有两种物品 $S$ 与 $T$，$S$ 物品的性价比（价值 / 代价）比 $T$ 高，那么有一种较优的拿法是全拿 $S$。但手玩一下发现，这不一定是最优的。那我们从大到小枚举所拿 $S$ 物品的个数，剩下的价值用 $T$ 物品补齐，然后计算出代价，取最小值即可。

但是直接枚举是会 [TLE](https://atcoder.jp/contests/abc374/submissions/58500616) 的。注意到当我们拿了很多的 $T$ 物品的时候，我们把若干 $T$ 物品替换成相同价值的 $S$ 物品会更优。具体地说，假如 $cnt_T \times v_T$ 是 $v_S$ 的倍数，那我们只需要把所有的 $T$ 物品换成 $\frac{cnt_T \times v_T}{v_S}$ 个 $S$ 物品即可。

所以，$cnt_T$ 的上界为 $\text{lcm}(v_T, v_S) / v_T$，再拿多就不优了。同理可以计算出少拿 $S$ 物品的个数的上界。由于 $\text{lcm}(v_T, v_S) \le v_T \times v_S$，枚举上界不会超过 $10^4$。

然后就做完了。时间复杂度 $O(n k\log V)$。$k$ 是单组枚举上界，不超过 $10^4$；$V$ 是二分价值的值域，不超过 $10^9$。

（我赛时更豪放一点，$k$ 开到了 $10^5$）

code :

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;
typedef double db;
const int N = 110;
int a[N], b[N], c[N], d[N], n;
ll X;

ll get(ll i, ll x) {
    db c1 = b[i] * 1.0 / a[i], c2 = d[i] * 1.0 / c[i];
    if(c1 > c2) swap(a[i], c[i]), swap(b[i], d[i]);
    ll cnt1 = (x + a[i] - 1) / a[i], res = 1e18;
    int k = 0;
    while(~cnt1 && k <= 100000) {
        ll cnt2 = (max(0ll, x - cnt1 * a[i]) + c[i] - 1) / c[i];
        res = min(res, cnt1 * b[i] + cnt2 * d[i]);
        cnt1--;
        k++;
    }
    return res;
}
bool chk(ll mid) {
    ll res = 0;
    for (int i = 1; i <= n; i++) res += get(i, mid);
    return res <= X;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> X;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i] >> d[i];
    ll l = 0, r = 1e9;
    while(l < r) {
        ll mid = (l + r + 1) / 2;
        if(chk(mid)) l = mid;
        else r = mid - 1;
    }
    cout << l;
    return 0;
}
```

---

## 作者：MrPython (赞：2)

赛时魔怔了，这没瞪出来！

很容易想到，对着答案二分，检查每个工序的效率大于等于 mid 时所需的最少钱数之和是否小于等于 $X$。

在决定每条生产线需要哪些机器时，从贪心的角度考虑，应该多选一些性价比更高的机器，性价比低的机器使用量应该较小。感性理解一下，性价比低的机器绝对不会选太多。卡着数据范围选一个比较大的数（我使用了 $100000$），枚举性价比较低的机器使用多少台，最后选择这些可能中较小的作为当前生产线的答案就对了。

~~其实选择 $100$ 就足够了，但是我比较懒，不想写证明。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n;
  uli x;
  fin >> n >> x;
  vector<array<pair<uli, uli>, 2>> a(n);
  for (auto& i : a) {
    fin >> i[0].first >> i[0].second >> i[1].first >> i[1].second;
    if ((float)i[0].first / i[0].second > (float)i[1].first / i[1].second)
      swap(i[0], i[1]);
  }
  uli l = 0, r = 1e9 + 1;
  while (l < r) {
    uli mid = (l + r + 1) / 2;
    uli sum = 0;
    for (auto const& i : a) {
      uli minx = numeric_limits<uli>::max();
      for (ui j = 0; j < 10000; ++j)
        minx = min(minx, i[0].second * j +
                             (i[0].first * j >= mid
                                  ? 0
                                  : (mid - i[0].first * j + i[1].first - 1) /
                                        i[1].first * i[1].second));
      sum += minx;
    }
    sum <= x ? l = mid : r = mid - 1;
  }
  fout << l;
  return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[E - Sensor Optimization Dilemma 2](https://atcoder.jp/contests/abc374/tasks/abc374_e)

讲一下赛时做法。

首先能看到最小值最大，考虑二分答案。

对于每一个流程，我们可以算出来所需的最小费用，最后判断费用和是否小于 $X$ 即可。

但是贪心的一直去选某一个，数量不够时再选另一个的方案明显是有反例的。

我们考虑一个事情，如果两个物品性价比是不一样的，肯定优先去选性价比高的物品，只剩下较小的一部分选另一个物品，并不会两个物品选的个数都很多。

所以考虑暴力 check，可以暴力枚举其中一种物品选的个数，再 $\mathcal O(1)$ 计算出另一个物品的个数，从而计算费用，该流程的费用为这些方案中最小的。

这样的复杂度是 $\mathcal O(nX\log V)$。其中 $V$ 是二分的值域，$X$ 是你枚举的上限，由于 $n$ 很小，$X$ 可以较大，我取的 $X=10000$ 过了。

```cpp
#define int long long
bool check (int x) {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int mi = 1e9;
        for (int j = 0; j <= 10000 && j * a[i] <= x; j++)
            mi = min (mi, j * p[i] + q[i] * ((x - j * a[i]) / b[i] + ((x - j * a[i]) % b[i] != 0)));
        for (int j = 0; j <= 10000 && j * b[i] <= x; j++)
            mi = min (mi, j * q[i] + p[i] * ((x - j * b[i]) / a[i] + ((x - j * b[i]) % a[i] != 0)));
        res += mi;
        if (res > X) return 0;
    }
    return 1;
}
```

---

## 作者：rnf5114 (赞：1)

比较抽象但是好想代码也好写的思路。

先把 $w$ 二分出来然后检查的时候按照性价比选到余下的 $w$ 小于 $10000$  即可。然后直接暴力跑背包就结束了。


```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x,ans,dp[11010];
struct node{
	int a,p,b,q;
}a[110];
bool check(int k){
	int m=x;
	for(int i=1;i<=n;i++){
		memset(dp,0x3f,sizeof dp);
		dp[0]=0;
		int awa=0,flag,tmp=k,mtmp,mv,qwq;
		double tmp1=(1.0*a[i].a/a[i].p),tmp2=(1.0*a[i].b/a[i].q);
		if(tmp1>tmp2)
			mtmp=a[i].p,mv=a[i].a;
		else
			mtmp=a[i].q,mv=a[i].b;
		int ju=max(0ll,tmp-10900)/mv;
		if(tmp-mv*ju>10900)
			ju++;
		tmp-=mv*ju;
		awa+=ju*mtmp;
		qwq=tmp;
		tmp=1e9+10;
		for(int j=0;j<=10900;j++){
			if(j>=qwq)
				tmp=min(tmp,dp[j]);
			dp[j+a[i].a]=min(dp[j+a[i].a],dp[j]+a[i].p);
			dp[j+a[i].b]=min(dp[j+a[i].b],dp[j]+a[i].q);
		}
		for(int j=10901;j<=11000;j++)
			tmp=min(tmp,dp[j]);
		m-=(awa+tmp);
	}
	return m>=0;
}
signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++)
		cin>>a[i].a>>a[i].p>>a[i].b>>a[i].q;
	int l=0,r=1000000000000;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid))
			l=mid+1,ans=max(ans,mid);
		else
			r=mid-1;
	}
	cout<<ans;
	return 0;
}

/*
       ┏┓　　　┏┓
     ┏┛┻━━━┛┻┓
     ┃　　　　　　　┃
     ┃　　　━　　　┃
     ┃　┳┛　┗┳　┃
     ┃　　　　　　　┃
     ┃　　　┻　　　┃
     ┃　　　　　　　┃
     ┗━┓　　　┏━┛
         ┃　　　┃
         ┃　　　┃
         ┃　　　┗━━━┓
         ┃　　　　　 ┣┓
         ┃　　　　 ┏┛
         ┗┓┓┏━┳┓┏┛
           ┃┫┫　┃┫┫
           ┗┻┛　┗┻┛


*/
```

---

## 作者：DGL__DGL_AFO (赞：1)

## 题目传送门： [link](https://www.luogu.com.cn/problem/AT_abc374_e)

# ~~窝们充分发扬人类智慧~~

## 题意简述：
![](https://cdn.luogu.com.cn/upload/image_hosting/yzm0ea6y.png)

## 人类智慧思路分析：

发现答案具有单调性（如果某个 $W$ 值可行，那比这个 $W$ 值小的 $W$ 值也都可行），于是想到进行二分。

~~然而蒟蒻不会判断答案是否可行，怎么办捏？~~

唉！我有个点子！

我们充分发扬人类智慧：

将每道工序的机器 $S$ 和机器 $T$ 根据性价比（产量 $/$ 单价）排序。

根据数学直觉，在排序后，一定会多买性价比高的机器。

所以我们对于每道工序,先全部买性价比高的机器，再用性价比低的机器逐个替换掉性价比高的机器，重复 $100$ 次并记录这个过程中的价格最小值即可。

这样速度快的飞起，所有的点都能在 $2ms$ 内~~卡~~跑过。

![](https://cdn.luogu.com.cn/upload/image_hosting/4dqd6qwf.png)

## 代码（莫抄！）


```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
struct Node
{
	int x,v;
} a[114][3];
ll l,r,mid;
ll res,p;
int maxx;

inline bool check()
{
	res=0;
	for(int i=1;i<=n;i++)
	{
	  int cnt=100;
		ll op=0;
	  ll aa,bb,gen;
	  aa=ceil(mid*1.0/a[i][1].x); 
	  gen=aa*a[i][1].x;
		op=aa*a[i][1].v;
		while(cnt--&&aa>=1)
		{
			aa--;
			gen-=a[i][1].x;
			if(gen<mid)
				bb=ceil((mid-gen)*1.0/a[i][2].x);
			op=min(op,aa*a[i][1].v+bb*a[i][2].v);
		}
	
	  res+=op; 
		
	  if(res>m)
	    return false;
	}
	//cout<<res<<'\n';
	return true;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i][1].x>>a[i][1].v>>a[i][2].x>>a[i][2].v;
		
		if(a[i][1].x*1.0/a[i][1].v<a[i][2].x*1.0/a[i][2].v)
		  swap(a[i][1],a[i][2]);
	}
		
	l=0,r=1e9+7;//二分上界要大于1e9，但也不能太大，否则会在check（）时爆long long
	
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check())
		  l=mid;
		else
		  r=mid;
		if(mid==((l+r)>>1))
		  break;
			//cout<<mid<<' ';	  
	}
	p=mid;
	
	cout<<mid;
	
	
	return 0;
}
```

## 说句闲话：为啥这个蒟蒻赛时没过

二分的上界开大，被卡了 $3$ 个点，一定要注意口牙！

---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/AT_abc374_e)

~~赛时差点不会？~~，这可能不是正解，是 $O(X\log (Xa_i))$ 的。

一眼二分答案。

但是对于每个项目，我们希望它花的钱最小。考虑 $dp_i$ 表示花费 $i$ 能获得的最多物品数量。

容易有：

$$dp_i=\max(dp_{i-q_i}+b_i,dp_{i-p_i}+a_i)$$

然后就做完了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e5+10;
#define int long long 
int p[N],a[N],q[N],b[N],n,X,dp[100000001];
bool check(int Wmin){
	int sum=0;
	for(int i=1;i<=n;i++){
		dp[0]=0; bool f=false;
		int pre=0;
		for(int j=1;j<=X;j++){
			dp[j]=0;
			if(j>=p[i])	dp[j]=max(dp[j],dp[j-p[i]]+a[i]);
			if(j>=q[i])	dp[j]=max(dp[j],dp[j-q[i]]+b[i]);
			if(dp[j]>=Wmin)	{pre=j;f=true;break;}
		}
		sum+=pre;
		if(f==false)	return false;
		if(sum>X)	return false;
	}
	return true;
}
void Slove(){
	int ans=0,l=0,r=1e10;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(check(mid))	ans=mid,l=mid;
		else	r=mid;
	}
	cout<<ans<<endl;
}
signed main(){
	cin>>n>>X;
	for(int i=1;i<=n;i++)	cin>>a[i]>>p[i]>>b[i]>>q[i]; // p q is cost  
	Slove();
//	cout<<check(5);
	return 0;
}
```

---

## 作者：201012280925LSY (赞：0)

## 题目大意：
有 $N$ 种任务，每种任务都有两种机器，每种机器都需要钱来购买，同时每个单位时间可以做不同的任务数。现在给你 $X$ 元钱，请你输出对于对于每种任务，可以达到最大的每个单位时间完成最小任务数（$w_i$ 为第 $i$ 种任务每个单位时间可以完成的任务数），即使得 $ \min^{N}_{i=1} w_i $ 最大。

## 思路

显然，如果我们钱越多，所以能买到的机器也就更多。不难发现，最大的最小工作量是随 $X$ 单调不降的。考虑二分最大的最小工作量。

现在知道是二分，那么 `check()` 函数怎么写呢，如果单纯是枚举某一种种机器买的数量，那么肯定过不了。

首先我们肯定优先买性价比高的那种机器，观察数据范围，注意到~~作者的注意力比较惊人~~每一台机器最多每个单位时间完成 $100$ 个任务。所以说我们最多只要买一百台某种机器，就可以顶的上一台另一种机器，则性价比低的机器，我们最多要买零到一百台。

那么也就是说我们每种任务都只用枚举一百次，时间复杂度足够通过此题。

PS：在判断两种机器谁的性价比高的时候，应该是交叉相乘，不然如果用 `double` 除的话，会导致精度丢失。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
struct machine
{
	long long x,y,q,p;
}a[110];
long long give(long long x,long long u)
{
	long long answer=1e18,A,B,C,D;//A 是性价比高的机器的工作效率，B是性价比高的机器的单机成本，C是性价比低的机器的工作效率，D是性价比低的机器的单机成本。
	if(a[x].x*a[x].p>a[x].y*a[x].q)A=a[x].x,B=a[x].q,C=a[x].y,D=a[x].p;//判断性价比的高低
	else A=a[x].y,B=a[x].p,C=a[x].x,D=a[x].q;
	for(int i=0;i<=99;i++)
	{
		long long sum=i*C,ans=0;
        if((u-sum)%A==0)ans=(u-sum)/A;//通过性价比低的机器的购买数量推出性价比高的机器的购买数量
        else ans=(u-sum)/A+1;
		answer=min(answer,B*ans+D*i);//取需要货币的最小值
	}
	return answer;
}
bool check(long long ans)
{
	long long sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=give(i,ans);//加上所有的成本
	}
	if(sum<=m)return true;
	else return false;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld%lld",&a[i].x,&a[i].q,&a[i].y,&a[i].p);
	}
	long long l=0,r=1e11,mid;
	while(l+1<r)//二分最小任务数
	{
		mid=(l+r)/2;
		if(check(mid)==true)l=mid;
		else r=mid;
	}
	cout<<l;
	return 0; 
 } 
```

---

## 作者：hjyowl (赞：0)

### 题目大意

有 $n$ 个任务，第 $i$ 个任务有两种机器，每种机器一台有不同的效率和价格。你只有 $m$ 元，你希望在钱不超过 $m$ 元是使得能处理出来的产品最小的任务的产品数尽可能大。

### 思路

这种让满足某个情况下的最大或最小的问题一般来讲都是二分。

考虑二分枚举最小的产品数 $x$，这个东西显然有单调性。

然后接下来，对于每一个位置进行贪心求解最小的花费使得它至少有 $x$。

具体是贪心怎么弄，只需要枚举第一种机器的数量，第二种机器的数量可以直接得到，然后得到过后在这些方案里取最小值就是他最小的花费。

然后最后二分只需要把每个地方的最小花费加起来，如果没有超过 $m$，那就返回真，否则就是假。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 100010;
long long n,m,T;
long long a[N],b[N],c[N],d[N];
long long checker(long long n, long long a, long long b, long long c, long long d) {  
	double x = 1.0 * double(b) / a;  
	double y = 1.0 * double(d) / c; 
	long long res = 1e12;
	if (x <= y) {  
		for (long long k = n / a - 100; k <= n / a; k ++ ){
			k = max(k,0ll);
			res = min(res,b * (k) + min(((n - k * a) + a - 1)  / a * b,((n - k * a) + c - 1) / c* d));
		}
	}
	else {  
		for (long long k = n / c - 100; k <= n / c; k ++ ){
			k = max(k,0ll);
			res = min(res,d * k + min(((n - k * c) + a - 1) / a * b,((n - k * c) + c - 1) / c* d));
		}
	} 
	return res;  
}  
bool check(long long x){
	long long s = 0;
	for (long long i = 1; i <= n; i ++ ){
		s += checker(x,a[i],b[i],c[i],d[i]);
		if (checker(x,a[i],b[i],c[i],d[i]) >= 1e12 / 2 || s > m){
			return 0; 
		}
	}
	return s <= m;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for (long long i = 1; i <= n; i ++ ){
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	}
	long long res;
	long long l = 0,r = 1e9;
	while (l <= r){
		long long mid = l + r >> 1;
		if (check(mid)){
			l = mid + 1;
			res = mid;
		}
		else{
			r = mid - 1;
		}
	}
	cout << res;
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

首先看到题目，是最小值最大问题，考虑二分。

现在我们考虑对于每一天如何选择机器使得既能满足条件又能花费最少。因为只有两种，所以考虑贪心。我们选择全选 $S_i$ 或全选 $T_i$，或者只选一台 $S_i$ 或只选一台 $T_i$，这样子写我们就能过样例了。

但是我们 WA 了。考虑优化。如果不是只选一台，而是选多台 $S_i$ 和 $T_i$。我们暴力枚举选多少 $S_i$，计算。并枚举选多少 $T_i$，计算取较小值。我们实际上最多选 $100$ 个 $S_i$ 或 $100$ 个 $T_i$，所以只要枚举到 $100$ 即可。

```cpp
// LUOGU_RID: 180398044
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 205
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), m = rd(), a[N], b[N], p[N], q[N];
il bool check(ll w){
	ll sum = 0;
	for (int i = 1; i <= n; i++){
		ll t = 1e18;
		for (int j = 0; j <= 100; j++){
			ll x = j * a[i], y = (w - x + b[i] - 1) / b[i], res = j * p[i];
			if (x < w) res = res + (w - x + b[i] - 1) / b[i] * q[i];
			t = min(t, res);
		}swap(a[i], b[i]), swap(p[i], q[i]);
		for (int j = 0; j <= 100; j++){
			ll x = j * a[i], y = (w - x + b[i] - 1) / b[i], res = j * p[i];
			if (x < w) res = res + (w - x + b[i] - 1) / b[i] * q[i];
			t = min(t, res);
		}sum += t;
	}return sum <= m;
}
int main(){
	for (int i = 1; i <= n; i++) a[i] = rd(), p[i] = rd(), b[i] = rd(), q[i] = rd();
	ll l = 0, r = 2000000000, ans = 0;
	while (l <= r){
		ll mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1, ans=  mid;
		else r = mid - 1;
	}printf ("%lld\n", ans);
	return 0;
}

```

---

## 作者：happy_zero (赞：0)

很明显先二分答案 $x$，然后对每个 $i$ 求共产出至少 $x$ 个的最小代价。

经典小学数学题：求出两台机器生产一个的代价 $c=\frac{p_i}{a_i}$ 和 $d=\frac{q_i}{b_i}$，则优先选择单个代价低的。

不妨设 $c<d$，由于可能用 $d$ 来凑会更优，因此枚举选第二个机器的个数，这个个数肯定小于 $\frac{\operatorname{lcm}(a_i,b_i)}{b_i}$，否则用第一个选 $\frac{\operatorname{lcm}(a_i,b_i)}{a_i}$ 代替更优，枚举到 $a,b$ 值域 $V=100$ 即可。

设 $W$ 为二分值域（大概是 $100\times 10^7=10^9$）复杂度 $O(nV\log W)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 105;
const int INF = 1e16;
int n, m, a[N], b[N], c[N], d[N];
bool chk(int x) {
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		int ans = INF;
		for (int j = 0; j <= 200; j++) 
			ans = min(ans, d[i] * j + (int)ceil(max(0ll, x - c[i] * j) * 1.0 / a[i]) * b[i]);
		sum += ans; if (sum > m) return 0;
	}
	return 1;
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i]; 
		if (b[i] * c[i] > a[i] * d[i]) 
			swap(a[i], c[i]), swap(b[i], d[i]); 
	}
	int l = 0, r = 1e9, ans = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (chk(mid)) ans = mid, l = mid + 1;
		else r = mid - 1; 
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

E 最可惜的一集。赛时一直调不出来，最后发现二分右边界 $10^{18}$ 爆 long long 了。

最小值最大，考虑二分答案 $mid$。

进一步地，对于一个工序 $a,b,p,q$，我们需要找到非负整数 $x,y$，使得 $ax+by \ge mid$ 且 $px+qy$ 最小。然后累加 $px+qy$ 看是否小于预算即可。

注意到，如果我们可以确定 $x$，那么 $y$ 越小，$px+qy$ 越小。故 $ax+by \ge mid$ 取得等号时 $y$ 最小，为 $\max(0,\lceil \dfrac{mid-ax}{b} \rceil)$。确定 $y$ 时的情况是同理的。而最优时一定有 $x \le b$ 或 $y \le a$，所以枚举到 $a+b$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 105;

#define int long long
int n, x;
struct node {
	int a, p, b, q;
} h[N];

inline bool check(int mid) {
	int cost = 0;
	for (int i = 1; i <= n; i++) {
		int a = h[i].a, b = h[i].b, p = h[i].p, q = h[i].q, mncost = 4e18;
		
		auto calc1 = [&](int x) -> int {
			int y = max(0LL, (int) ceil(1.0 * (mid - a * x) / b));
			int cur = p * x + q * y;
			mncost = min(mncost, cur);
			return cur;
		};
		auto calc2 = [&](int y) -> int {
			int x = max(0LL, (int) ceil(1.0 * (mid - b * y) / a));
			int cur = p * x + q * y;
			mncost = min(mncost, cur);
			return cur;
		};
		for (int i = 0; i <= a; i++) calc2(i);
		for (int i = 0; i <= b; i++) calc1(i);
		
		cost += mncost;
		if (cost > x) return false;
	}
	return cost <= x;
}

void _main() {
	cin >> n >> x;
	for (int i = 1; i <= n; i++) cin >> h[i].a >> h[i].p >> h[i].b >> h[i].q;
	int l = 0, r = 1e9, res = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << res;
}
```

---

## 作者：xiaofu15191 (赞：0)

评价：考验选手对向上取整以及强制类型转换的括号摆放位置的理解。

发现我们想让 $W=\displaystyle\ \min^{N}_{i=1}\ W_i$ 这种东西最大，考虑二分 $W$。接下来看给定 $W$ 之后如何构造方案。

令每一天可以生产的产品数最少为 $W$，此时我们想要使每一天的费用 $cost_i$ 最小，如果 $\displaystyle\ \sum_{i=1}^{n} cost_i \le X$，那么这个 $W$ 就是可行的。

列出式子，令第 $i$ 天购买了机器 $S_i$ $x$ 台，得到

$$
cost_i=P_ix+\max(0,\lceil {\dfrac{W-A_ix}{B_i}} \rceil) \times Q_i.
$$

这个式子看上去像是个一次函数。然后我赛时把 $G_i=P_i+\dfrac{Q_iW-A_iQ_i}{B_iQ_i}$ 当成一次函数系数直接做最值问题了。如果你这么做，你会发现样例 4 过不了，比答案少了 $1$。实际上这个系数并不准确。

和暴力枚举 $x$ 的程序比较一下，发现暴力程序在第 $3$ 天，$cost_i$ 的系数 $G_i<0$ 的情况下，最小解依旧取到了 $x=1$。

几分钟后我发现不用考虑系数的正负性，因为不是机器 $S_i$ 数量很少趋近于 $0$，就是 $T_i$ 数量少。

所以，我们只需从小到大枚举 $S_i$ 的数量取 $cost_i$ 最小值，再从小到大枚举 $T_i$ 的数量取 $cost_i$ 值即可。

这里只放核心代码。尤其要注意向上取整和类型转换的细节。

```cpp
bool check(long long mid)
{
	long long sum=0;
	for(long long i=1;i<=n;i++)
	{
		long long f=min((long long)(ceil((double(mid))/a[i])*p[i]),(long long)(ceil((double(mid))/b[i])*q[i]));
		for(long long j=0;j<=100;j++)
			f=min(f,p[i]*j+max(0ll,(long long)(ceil((double)(mid-a[i]*j)/b[i])))*q[i]);
		for(long long j=0;j<=100;j++)
			f=min(f,q[i]*j+max(0ll,(long long)(ceil((double)(mid-b[i]*j)/a[i])))*p[i]);
		sum+=f;
	}
	return sum<=x;
}
```

---

