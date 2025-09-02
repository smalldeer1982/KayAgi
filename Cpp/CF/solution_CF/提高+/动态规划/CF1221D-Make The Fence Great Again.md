# Make The Fence Great Again

## 题目描述

你有一个由 $n$ 块竖直木板组成的栅栏。每块木板的宽度为 $1$。第 $i$ 块木板的高度为 $a_i$。如果没有任意一对相邻的木板高度相同，你认为这个栅栏是“完美的”。更正式地说，只有当对于所有从 $2$ 到 $n$ 的下标，条件 $a_{i-1} \neq a_i$ 都成立时，这个栅栏才是“完美的”。

不幸的是，现在你的栅栏可能不是“完美的”。但你可以进行修改！你可以将第 $i$ 块木板的长度增加 $1$，但你需要为此支付 $b_i$ 卢布。每块木板的长度可以增加任意次（也可以不增加）。

请计算，为了让栅栏再次变得“完美”，你最少需要花费多少卢布！

你需要回答 $q$ 个独立的询问。

## 说明/提示

在第一个询问中，你需要将第二块木板的长度增加 $2$。所以你的总花费是 $2 \cdot b_2 = 2$。

在第二个询问中，你需要将第一块木板的长度增加 $1$，第三块木板的长度增加 $1$。所以你的总花费是 $1 \cdot b_1 + 1 \cdot b_3 = 9$。

在第三个询问中，栅栏本身就是“完美的”，所以你不需要花费卢布。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3
2 4
2 1
3 5
3
2 3
2 10
2 6
4
1 7
3 3
2 6
1000000000 2
```

### 输出

```
2
9
0
```

# 题解

## 作者：Chavapa (赞：13)

# *DP*
首先证明：任意位置上的数增加值$\Delta x=0,1,2$ 

考虑$a[i]$值的增加：若$a[i±1]=a[i]$，那么我们把$a[i]$加$1$；这时如果发现$a[i]$加$1$后又与$a[i∓1]$相等，那么我们就再把$a[i]$加$1$。这时如果再加$1$就没有意义。故增加值只能为$0,1,2$。

设$f[i][j]$表示$a[i]$的$\Delta x=j$，且前$i$个数组成的数列是好的时的最小花费。

显然$f[i][j]=min(f[i,j],f[i-1,k]+b[i]*j)$ ，其中$a[i-1]+k≠a[i]+j$

## Code

```c
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
    return x*f;
}
const ll INF=1e18+7;
const int N=6e5+7;
int Q,n,a[N],b[N];
ll f[N][3];
int main()
{
    Q=read();
    memset(f,0x3f,sizeof(f));
    while(Q--)
    {
        for(int i=0;i<=n;i++) f[i][0]=f[i][1]=f[i][2]=INF;
        n=read(); 
        for(int i=1;i<=n;i++) a[i]=read(),b[i]=read();
        f[0][0]=0; 
        for(int i=1;i<=n;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    if(a[i-1]+k!=a[i]+j) 
                      f[i][j]=min(f[i][j],f[i-1][k]+1ll*b[i]*j);
        ll ans=INF; 
        for(int i=0;i<3;i++) ans=min(ans,f[n][i]);
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：F_Mu (赞：5)

题意：对于n个栅栏，对于每个$i$，有高度$a[i]$，对于任意$2<=i<=n$,有$a[i]!=a[i-1]$，则称该组栅栏为好栅栏，每个栅栏可花费$b[i]$提升$1$个高度（可无限提升）。给一组栅栏，问最少花费多少可以将这组栅栏变为好栅栏。
分析：对于第$i$个栅栏，他要保证不与第$i-1$和$i+1$个栅栏相同，最多提升$2$，如果提升$2$与第$i-1$或$i+1$相同，则可选择提升$0$或$1$,同理如果此时与另一侧栅栏相同，则可提升$0$或$1$使该栅栏与两侧栅栏不同。题意给出其实提醒了$DP$（说$a[i]!=a[i-1]$）。我们设置$DP[i][j]$表示对于第$i$个栅栏，提升$j$后，使得前$i$个栅栏为好栅栏，$0<=j<=2$。
（1）对于$a[i]==a[i-1]$的情况

如果第$i$个栅栏提升$0$，则第$i-1$个栅栏需提升$1$或者$2$，那么有
$$dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]$$
如果第$i$个栅栏提升$1$，则第$i-1$个栅栏需提升$0$或者$2$，那么有
$$dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + b[i]$$

如果第$i$个栅栏提升$2$，则第$i-1$个栅栏需提升$0$或者$1$，那么有
$$dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + b[i] * 2$$
（2）对于$a[i]==a[i-1]+1$的情况

如果第$i$个栅栏提升$0$，则第$i-1$个栅栏需提升$0$或者$2$，那么有
$$dp[i][0] = min(dp[i - 1][0], dp[i - 1][2])$$
如果第$i$个栅栏提升$1$，则第$i-1$个栅栏需提升$0$或者$1$，那么有
$$dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + b[i]$$
如果第$i$个栅栏提升$2$，则第$i-1$个栅栏需提升$0$或者$1$或者$2$，那么有

$$dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1],dp[i-1][2])) + b[i] * 2$$
（3）对于$a[i]==a[i-1]+2$的情况

如果第$i$个栅栏提升$0$，则第$i-1$个栅栏需提升$0$或者$1$，那么有
$$dp[i][0] = min(dp[i - 1][0], dp[i - 1][1])$$
如果第$i$个栅栏提升$1$，则第$i-1$个栅栏需提升$0$或者$1$或者$2$，那么有
$$dp[i][1] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i]$$
如果第$i$个栅栏提升$2$，则第$i-1$个栅栏需提升$0$或者$1$或者$2$，那么有
$$dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i] * 2$$
（4）对于$a[i]==a[i-1]-1$的情况

如果第$i$个栅栏提升$0$，则第$i-1$个栅栏需提升$0$或者$1$或者$2$，那么有
$$dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]))$$
如果第$i$个栅栏提升$1$，则第$i-1$个栅栏需提升$1$或者$2$，那么有
$$dp[i][1] = min(dp[i - 1][1], dp[i - 1][2]) + b[i]$$
如果第$i$个栅栏提升$2$，则第$i-1$个栅栏需提升$0$或者$2$，那么有
$$dp[i][2] = min(dp[i - 1][0], dp[i - 1][2]) + b[i] * 2$$
（5）对于$a[i]==a[i-1]-2$的情况

如果第$i$个栅栏提升$0$，则第$i-1$个栅栏需提升$0$或者$1$或者$2$，那么有

$$dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]))$$
如果第$i$个栅栏提升$1$，则第$i-1$个栅栏需提升$0$或者$1$或者$2$，那么有
$$dp[i][1] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i]$$
如果第$i$个栅栏提升$2$，则第$i-1$个栅栏需提升$1$或者$2$，那么有
$$dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]) + b[i] * 2$$
（6）其他情况

第$i$个栅栏提升$0,1,2$，第$i-1$个栅栏可提升$0$或者$1$或者$2$，有
$$dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]))$$
$$dp[i][1] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i]$$
$$dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i] * 2$$
最后输出$min(dp[n][0], min(dp[n][1], dp[n][2]))$即可

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
using namespace std;
const int maxn = (ll) 3e5 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;
int dp[maxn][3];
int a[maxn], b[maxn];

signed main() {
    start;
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i] >> b[i];
            dp[i][0] = dp[i][1] = (ll) (1e18) + 5;//千万不能用memset
        }
        /*初始化*/
        dp[1][0] = 0;
        dp[1][1] = b[1];
        dp[1][2] = b[1] * 2;
        for (int i = 2; i <= n; ++i) {
            if (a[i] == a[i - 1]) {
                dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]);
                dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + b[i];
                dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + b[i] * 2;
            } else if (a[i] == a[i - 1] + 1) {
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][2]);
                dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + b[i];
                dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1],dp[i-1][2])) + b[i] * 2;
            } else if (a[i] == a[i - 1] + 2) {
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][1] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i];
                dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i] * 2;
            } else if (a[i] == a[i - 1] - 1) {
                dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]));
                dp[i][1] = min(dp[i - 1][1], dp[i - 1][2]) + b[i];
                dp[i][2] = min(dp[i - 1][0], dp[i - 1][2]) + b[i] * 2;
            } else if (a[i] == a[i - 1] - 2) {
                dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]));
                dp[i][1] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i];
                dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]) + b[i] * 2;
            } else {
                dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]));
                dp[i][1] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i];
                dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + b[i] * 2;
            }
        }
        cout << min(dp[n][0], min(dp[n][1], dp[n][2])) << '\n';
    }
    return 0;
}
```
（这题我竟然和一个吉尔吉斯斯坦的小姐姐代码撞了，被判重然后unrated，哭了）
（萌新的第一篇Latex题解）

---

## 作者：hyfzelda (赞：2)

### [Make The Fence Great Again CF1221D](https://www.luogu.com.cn/problem/CF1221D)
## **1.** 思路
#### (1) 题意
给出 $n$ 个数，定义一个数列是好的当且仅当 $a_{i}\ne a_{i-1}$。

你可以通过调整数的大小来把一个数列变成好的，将一个位置 $i$ 上的数 $+1$ 需要的花费是 $b_i$，问：最小的花费？

有 $q$ 组询问，保证 $\sum_{i=1}^q n_i\le3\times10^5$，答案在 long long 范围内，翻译非常明了。
#### (2) 状态

本题为一道 dp。

如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/tsu9h9sh.png)

使 $a_i$ 与 $a_{i-1}$ 不同，最劣情况如上图。

将 $a_i+1$ 后，又发现 $a_i$ 与 $a_{i-1}$ 相同，此时再将 $a_i+1$ 才符合要求。 

所以最多进行 $2$ 次操作。

第 $i$ 项仅与第 $i-1$ 项有关，所以定义状态为：$dp[i][j]$ (考虑到第 $i$ 项,$1 \le i\le n$，进行了 $j$ 次操作，$0\le j\le2$)。
#### (3) 转移方程

设计有以下方程：$dp[i][j]=\min(dp[i][j],dp[i-1][k]+b[i]×j)$（$k$ 为 $a_{i-1}$ 的操作次数，$0\le k\le2$），另外，$a_i+j\neq a_{i-1}+k$，即经过操作后，二者值不同。

枚举 $k$ 的大小，从前一项的三种情况中选择最优的那种。
 
 
##  2. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[300005][3],n,a[300005],b[300005];
signed main()
{
	int t;
	scanf("%lld",&t);//多组数据，记得初始化 
	while(t--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i],&b[i]);
		for(int i=1;i<=n;i++)
		{
			dp[i][0]=dp[i][1]=dp[i][2]=1e18+7;
		}//值域较大,使用memset会超时
		dp[0][0]=dp[0][1]=dp[0][2]=0; 
		for(int i=1;i<=n;i++) 
		{
			for(int j=0;j<=2;j++)//枚举i的操作次数 
			{
				for(int k=0;k<=2;k++)//枚举i-1的操作次数 
				{
					if(a[i]+j!=a[i-1]+k)//如果两者经过操作后不同 
					{
						dp[i][j]=min(dp[i][j],dp[i-1][k]+b[i]*j);//转移方程	
					}
				}
			}
		}
		printf("%lld\n",min(dp[n][0],min(dp[n][1],dp[n][2])));//n的三种情况取最小 
        	return 0;
	}
}
```


---

## 作者：AveMujica (赞：1)

## 思路
有一个关键观察是，对于连续的三个数 $x$、$y$、$z$，为了确保这三个数两两不等，我们最多对其中一个数加二即可。最极端的情况是样例一给出的 $2$、$2$、$3$，此时中间的数与相邻的两个数的差值分别为 $0$ 和 $1$，细心的小伙伴可能发现了，这不就是 mex 嘛！没错，从差值的角度来看，任意相邻的三个数的差值的集合的 mex 最大就是 $2$，对于连续的 $n$ 个数，若 $n \ge 3$，我们总能把它拆为若干的连续的 $3$ 个数的情形，若 $n \le 2$，它的 mex 就更小了，不需要单独讨论。于是答案就呼之欲出啦，我们令 $f_{ij}$ 表示前 $i$ 个数两两不同所需要的最小花费，且当前栅栏的高度加 $j$。$h$ 表示栅栏的高度，$c$ 表示花费，则状态转移为 $f_{ij} = \min \limits_k (f_{i-1,k} + c_i \times j) \quad \text{subject to} \quad h_{i-1} + k \ne h_i + j$。
## AC代码
```
#include <bits/stdc++.h>
using namespace std;
using i64=long long;
void F1ower() {
    // f[n][x]: 前 i 个数, 当前数 + x[0, 2]
    int n;
    cin >> n;
    vector<i64> h(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i] >> c[i];
    vector<vector<i64>> f(n + 1, vector<i64>(3));
    for (int i = 0; i <= 2; i++) f[1][i] = i * c[1];
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 2; j++) {
            f[i][j] = j * c[i];
            i64 cur = h[i] + j;
            i64 cost = LONG_LONG_MAX;
            for (int k = 0; k <= 2; k++) {
                if (h[i - 1] + k != cur) cost = min(cost, f[i - 1][k]);
            }
            f[i][j] += cost;
        }
    }
    i64 ans = LONG_LONG_MAX;
    for (int i = 0; i <= 2; i++) ans = min(ans, f[n][i]);
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        F1ower();
    }
    return 0;     
}
```

---

## 作者：kimi0705 (赞：0)

# Make The Fence Great Again
## 题意
给出 $n$ 个数，定义一个数列是好的当且仅当 $a_{i}\ne a_{i-1}$。你可以通过调整数的大小来把一个数列变成好的，将一个位置 $i$ 上的数 $+1$ 需要的花费是 $b_i$，问：最小的花费。\
有 $q$ 组询问，保证 $\sum_{i=1}^q n_i\le3\times10^5$，答案在 $\texttt{long long}$ 范围内。
## 思路
显然任意位置上的数增加值 $\Delta x=0,1,2$
考虑 $\texttt{dp}$。
### 设计状态
$dp_{i,j}$ 表示把第 $i$ 个数加 $j$,前 $i$ 个数合法的最小代价。
### 状态转移
设上次加 $k$，\
并且合法即 $a_{i-1}+k \ne a_i + j$\
那么 $dp_{i,j}=\min\{dp_{i,j},dp_{i-1,k} + jb_i\}$
## code 
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10;
int q, n;
int a[N], b[N];
int dp[N][5];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> q;
	while (q--) {
		cin >> n;
		for (int i = 1; i <= n; i++) dp[i][0] = dp[i][1] = dp[i][2] = 1e18;//初始值
		for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
		for (int i = 0; i <= 2; i++) dp[1][i] = i * b[1];//初始值
		for (int i = 2; i <= n; i++) // dp转移
			for (int j = 0; j <= 2; j++)
				for (int k = 0; k <= 2; k++)
					if (a[i - 1] + k != a[i] + j)
						dp[i][j] = min(dp[i][j], dp[i - 1][k] + b[i] * j);
		cout << min(min(dp[n][0], dp[n][1]), dp[n][2]) << '\n';
	}
	return 0;
}
```

---

## 作者：A_Đark_Horcrux (赞：0)

对于一段需要调整的区间：

```
2 2 2
```

我们模拟一下调整的过程。如果遇到第一个数时，判断它与下一个数相等，立刻进行加一操作：

```
3 2 2
```

之后遇到了第二个数，又需要进行加一操作：

```
3 3 2
```

但是这时候第二个数又与第一个数相等了。此时如果回到上一个数操作比较麻烦，而且如果上一个数加一以后，又与再上一个数相等，那必须一直往前，最坏情况下 $O(n^2)$

```
9 8 7 6 5 4 3 2 2
//↑如果在第一个2处加1，就要一直更新到最前面
```

所以这种策略是行不通的。与其要反复地加一，不如一次直接加上二：

```
2 2 2 -> 4 2 2 -> 4 3 2
```

如果下一个数还需要进行操作，则再加二即可。由于加二已经满足了需求，因此不需要考虑加三、加四的情况。

据此我们可以设计出状态：设 $f_{i,0/1/2}$ 为第 $i$ 位加上了 $0/1/2$ 以后使前 $i$ 位满足需求的最小花费。

对于第 $i+1$ 位，如果加上 $k$ 后与第 $i$ 位加上 $j$ 不相等，则可以从第 $i$ 位转移而来，花费等于前 $i$ 位的花费加上第 $i+1$ 位每次加一的花费乘以加上的数，

即若 $a_{i}+j \neq a_{i+1}+k$，则 $f_{i+1,k}=\min{(f_{i+1,k},f_{i,j}+b_i*j)}$

然后要将 $f_{1,0/1/2}$ 初始化。

最后答案即为 $\min(f_{n,0},f_{n,1},f_{n,2})$

记得答案在 longlong 范围内！

另外我在第三个点TLE了两次，然后发现由于 $\Sigma n$ 其实很小，因此用 memset 不如直接循环。

```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
const int N=3e5+10;
inline int read()
{
	int s=0,b=1; char c=getchar();
	while(c<'0'||c>'9') {if (c=='-') b=-1; c=getchar();}
	while(c>='0'&&c<='9') s=(s<<3)+(s<<1)+(c&15),c=getchar();
	return s*b;
}
int T,n,i,j,k;
ll ans=1e18,h[N],b[N],f[N][3];
ll min(ll x,ll y){return x<y?x:y;}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(i=1;i<=n;i++) h[i]=read(),b[i]=read();
		for(i=0;i<=n;i++) f[i][0]=f[i][1]=f[i][2]=1e18;//dp数组初始化为无限大
		ans=1e18;
		f[1][0]=0,f[1][1]=b[1],f[1][2]=b[1]*2;//初始化第一位
		for(i=1;i<=n;i++)
			for(j=0;j<=2;j++)
				for(k=0;k<=2;k++)
					if(h[i]+j!=h[i+1]+k)
						f[i+1][k]=min(f[i+1][k],f[i][j]+b[i+1]*k);//转移
		for(i=0;i<=2;i++) ans=min(ans,f[n][i]);//记录答案
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

