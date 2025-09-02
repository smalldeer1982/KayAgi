# Money Buys Happiness

## 题目描述

Being a physicist, Charlie likes to plan his life in simple and precise terms.

For the next $ m $ months, starting with no money, Charlie will work hard and earn $ x $ pounds per month. For the $ i $ -th month $ (1 \le i \le m) $ , there'll be a single opportunity of paying cost $ c_i $ pounds to obtain happiness $ h_i $ .

Borrowing is not allowed. Money earned in the $ i $ -th month can only be spent in a later $ j $ -th month ( $ j>i $ ).

Since physicists don't code, help Charlie find the maximum obtainable sum of happiness.

## 说明/提示

In the first test case, Charlie only gets paid at the end of the month, so is unable to afford anything.

In the second test case, Charlie obtains the free happiness in the first month.

In the third test case, it's optimal for Charlie to buy happiness in the second month. Even with money left at the end, Charlie could not go back in time to obtain the happiness on offer in the first month.

## 样例 #1

### 输入

```
7
1 10
1 5
2 80
0 10
200 100
3 100
70 100
100 200
150 150
5 8
3 1
5 3
3 4
1 5
5 3
2 5
1 5
2 1
5 3
2 5
2 4
4 1
5 1
3 4
5 2
2 1
1 2
3 5
3 2
3 2```

### 输出

```
0
10
200
15
1
9
9```

# 题解

## 作者：Weekoder (赞：5)

### 思路

背包，但是 $c_i$ 太大，不能直接作为下标，怎么办？或许我们可以改变一下状态：令 $dp_{i,j}$ 表示在前 $i$ 个月想要获得 $j$ 的幸福能剩下的最大价钱。如果我们在第 $i$ 个月花钱买了幸福，剩下的钱就会减去 $c_i$，而幸福值则会增加 $h_i$。而实际上某个月剩余的钱只与上个月有关，所以可以像背包问题一样省去第一维。容易得到状态转移方程：

$$
dp_j=\max(dp_j,dp_{j-h_i}-c_i),dp_{j-h_i}\ge c_i
$$

最后不要忘记在每个月末给 $dp_j$ 加上工资 $x$。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 5;

int T, m, x, c[N], h[N], dp[N], sum;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T --) {
	    cin >> m >> x;
	    sum = 0;
	    for (int i = 1; i <= m; i++)
	       cin >> c[i] >> h[i], sum += h[i];
	    memset(dp, 0xcf, sizeof dp);
	    dp[0] = 0;
	    for (int i = 1; i <= m; i++) {
	        for (int j = sum; j >= h[i]; j--)
	           if (dp[j - h[i]] >= c[i])
	               dp[j] = max(dp[j], dp[j - h[i]] - c[i]);
	        for (int j = 0; j <= sum; j++)
	           if (dp[j] >= 0)
	               dp[j] += x;
	    }
	    for (int i = sum; i >= 0; i--) if (dp[i] >= 0) {
	        cout << i << "\n";
	        break;
	    }
	}
	return 0;
}
```

---

## 作者：Louis_lxy (赞：4)

很简单的 dp 技巧题，多做点 dp 就能一眼秒。

观察数据范围后我们发现，这题不能用普通的背包计算，我们直接转化定义即可，我们让 $f_i$ 表示获得 $i$ 的价值能剩下的最大代价，转移方程显然就是 $f_j=\max(f_j,f_{j-h_i}-c_i)$，$i$ 表示计算到第 $i$ 个月，$j$ 表示枚举的价值，转移顺序与普通 01 背包并无区别。

注意如果会导致欠钱，那么不能转移，还有就是要记得在转移后给所有不用欠钱的 $f_j$ 都加上工资 $x$。

AC 记录：https://www.luogu.com.cn/record/168618135

---

## 作者：jianhe (赞：4)

一个经典的 trick。

点开题面，看上去似乎就是一个简单的 **01 背包**，但观察数据范围，$1 \le c_i \le 10^8$，并不能直接做。

注意到 $h_i$  比较小，那么我们可以将普通背包中的下标与存值调换，这道题就变得很简单啦～

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll M=1e5+10;
ll T,m,x,c,h,s,dp[M];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>m>>x;s=0;
		memset(dp,128,sizeof dp);dp[0]=0;
		for(int i=1;i<=m;i++){
			cin>>c>>h;s+=h;
			for(int j=s;j>=0;j--){
				if(j>=h&&dp[j-h]>=c)
					dp[j]=max(dp[j],dp[j-h]-c);
				if(dp[j]>=0) dp[j]+=x;
			}
		}
		for(int i=s;i>=0;i--)
			if(dp[i]>=0){cout<<i<<"\n";break;}
	}
	return 0;
}

```

---

## 作者：Stars_visitor_tyw (赞：2)

## CF1974E Money Buys Happiness 题解
### 分析
一眼动态规划。

考虑按幸福度进行转移，统计 $h_i$ 的和 $sum$，双重循环进行转移。其实就是背包啦。

状态：$dp_i$ 表示当幸福度为 $i$ 时花的最小的钱。

状态转移：

```cpp
        for(int i=1;i<=m;i++)
        {
            for(int j=sum;j>=h[i];j--)
            {
                if(dp[j-h[i]]+c[i]<=(i-1)*x)
                {
                    dp[j]=min(dp[j],dp[j-h[i]]+c[i]); 
                }
            }
        }
```

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, m, x, dp[50005], h[55], c[55];
signed main()
{
    for(cin>>t;t;t--)
    {
        for(int i=1;i<=50000;i++)
        {
            dp[i]=1e11;
        }
        int sum=0;
        cin>>m>>x;
        dp[0]=0;
        for(int i=1;i<=m;i++)
        {
            cin>>c[i]>>h[i];
            sum+=h[i];
        }
        for(int i=1;i<=m;i++)
        {
            for(int j=sum;j>=h[i];j--)
            {
                if(dp[j-h[i]]+c[i]<=(i-1)*x)
                {
                    dp[j]=min(dp[j],dp[j-h[i]]+c[i]); 
                }
            }
        }
        int ans=0;
        for(int i=sum;i>=0;i--)
        {
            if(dp[i]<=(m-1)*x)
            {
                ans=i;
                break;
            }
        } 
        cout<<ans<<"\n";
    } 
	return 0;
}

```

---

## 作者：DrAlfred (赞：2)

摘要：动态规划，背包

[传送门：https://www.luogu.com.cn/problem/CF1974E](https://www.luogu.com.cn/problem/CF1974E)

## 题意

你是一个物理学家。一开始你没有钱，每个月的末尾你会得到 $x$ 英镑。在第 $i$ 个月里，你可以付出 $c_i$ 英镑，获取 $h_i$ 的幸福。

在任何时刻你都不能欠钱，问你在 $m$ 个月过后最多能获得多少幸福。

保证 $\sum h_i \leq 10^5$。

## 分析思路

注意到 $\sum h_i \leq 10^5$ 这一特殊的性质。考虑 dp。设 $dp_{i, j}$ 表示到第 $i$ 个月的末尾为止，获取 $j$ 的幸福值所剩余的最多钱数。容易得到转移式：

$$
\begin{equation*}
dp_{i, j}=\left\{
\begin{array}{lcl}
dp_{i - 1, j} & & {0 \leq j < h_i}\\
\max(dp_{i - 1, j}, dp_{i - 1, j - h_i} - c_i) & & {j \geq h_i}\\
\end{array} \right.
\end{equation*}
$$

计算完 $dp_i$ 一整行之后，对于 $dp_{i, j} \geq 0$ 的所有 $dp_{i, j}$, 令 $dp_{i, j} \gets dp_{i, j} + x$。

最后找到最大的 $j$，使得 $dp_{m, j} \geq 0$，即为答案。

实现上发现第一个维度没有用，删除即可。

总时间复杂度 $O\left(m \sum h\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 t, m, x, sum, h, c;
inline void solve(void) {
    vector<i64> dp{0};
    cin >> m >> x, sum = 0;
    for (int i = 1; i <= m; i++) {
        cin >> c >> h, sum += h;
        dp.resize(sum + 1, -1);
        for (int j = sum; j >= h; j--) {
            if (dp[j - h] >= c) {
                dp[j] = max(dp[j], dp[j - h] - c);
            }
        }
        for (int j = 0; j <= sum; j++) {
            if (dp[j] >= 0) dp[j] += x;
        }
    }
    for (int i = sum; i >= 0; i--) {
        if (dp[i] >= 0) {
            cout << i << '\n';
            return;
        }
    }
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：O_v_O (赞：2)

# CF1974E Money Buys Happiness 题解

## 题意

你有 $m$ 个月，每个月你会得到 $x$ 元钱，第 $i$ 个月，你可以用 $c_i$ 元钱获得 $h_i$ 点幸福，请求出最大幸福值（注：第 $i$ 个月赚的钱不能在第 $i$ 个月使用，要在大于它的月使用）。

## 思路

这道题先不考虑 dp 数组形式如何写，我们先推出 dfs 式的状态和转移。

### 状态和转移

$(x, val, sum)$ 表示前 $x$ 个数，你现有的钱数为 $val$，你的总幸福值为 $sum$。

我们在想，你第 $i$ 天只有两种可能，你要不就花费 $c_i$ 元钱获得 $h_i$ 点幸福值，要不就不花钱，将 $val$ 加上 $x$。由此，我们可以得到以下转移方程：

$$
(x, val, sum) \to
\begin{cases}
(x + 1, val + x, sum)\\
(x + 1, val + x - c_i, sum + h_i) & val > c_i
\end{cases}
$$

### DP

状态和转移都被我们写出来了，大家们可以先试试写 dfs，然后再来看着一部分。

1. 设计 DP 状态
  
    我们看，上面有三个数值 $x$、$val$、$sum$，将 $x$ 当作第一维是肯定的，那谁来当作第二维呢？

    1. 将 $val$ 作为第二维

        我们可以很明显的发现 $val$ 的值非常大，足足可以达到 $5 \times 10^9$，在乘上个 $50$ 直接 MLE，所以是不行的。

    2. 将 $sum$ 作为第二维

        题目中说过 $\sum h_i \le 10^5$，所以我们最大开到 $10^5$，$x$ 最大为 $50$，$10^5 \times 50 = 5 \times 10^6$，不会 MLE。
    
    所以 $dp_{i, j}$ 最终状态表示为：前 $i$ 个数，总幸福值为 $j$ 的最大总钱数。

2. 推状态转移方程

    我们已经将 dp 状态给搞定了，状态转移方程也非常简单，大家们可以再看一看上面的转移，下面直接将转移方程列出来：

    $$
    dp_{i, j} = \max
    \begin{cases}
    dp_{i - 1, j} + x \\
    dp_{i - 1, j - h_i} + x - c_i & j \geq h_i & dp_{i - 1, j - h_i} \geq c_i
    \end{cases}
    $$

    拓扑序为：$i$ 从小到大。

    最优化属性为：总钱数最多。

3. 时空复杂度分析

    我们看上面的 dp 方程式，单次转移 $1$ 种状态，一共有 $MAXV$ 次转移，所以时间复杂度为 $O(n \times MAXV)$ （注：$MAXV$ 表示最大幸福和）。

    空间复杂度为：$O(n \times MAXV)$。 

### 拓展

我们看上面的 dp 转移方程，他只用到了前一维，所以我们只需要一维的 dp 空间，空间优化为：$O(MAXV)$。

这是本蒟蒻的第 $5$ 篇题解，管理员求过 $QwQ$。

---

## 作者：liyp (赞：1)

## 思路
很简单的动态规划。

我们会发现，这是一道非常明显的**背包问题**，对于第 $i$ 个月份，我们有两种选择：一是**花费** $c_i$ 的金钱来**购买** $h_i$ 的快乐，二是**不花费**钱，快乐值**不变**。

和传统的背包不同，这一题的动态规划**不能拿价值总和**（也就是剩下的钱值）当做下标。我们可以用 $dp_{i,j}$ 代表在第 $i$ 个月份获得 $j$ 的快乐值最大剩下的钱。

可以很容易推出转移方程：
$$dp_{i,j}=\max(dp_{i,j},dp_{i,j-h_i}-c_i)$$

当然这个转移方程只能在 $dp_{i,j} \ge c_i$ 时**有效**。

```cpp
if (dp[i][j - h[i]] >= c[i]) {
    dp[i][j] = max(dp[i][j], dp[i][j - h[i]] - c[i]);
}
```

在得出转移方程后，我们可以再次进行分析，会发现像传统的背包一样，只有第 $i-1$ 个月份会影响到第 $i$ 个月份，因此可以**省掉一个维度**。
```cpp
if (dp[j - h[i]] >= c[i]) {
    dp[j] = max(dp[j], dp[j - h[i]] - c[i]);
}
```

当然，这道题有一个特殊点，就是每个月份物理学家可以领到 $x$ 英镑的钱，因此每个月份要给**剩下的钱加上**收入 $x$。

```cpp
for (int j = 0; j <= sigma_h; j++) {
    if (dp[j] >= 0) {
        dp[j] += x;
    }
}
```

最后不要忘了，动态规划数组要开 ``long long``，**不然会炸**！

## 完整代码
```cpp
#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int MAXN = 50 + 10;
int c[MAXN], h[MAXN];
long long dp[(int)1e5 + 10];
void solve()
{
    int m, x; int sigma_h = 0;
    cin >> m >> x;
    
    for (int i = 1; i <= m; i++) {
        cin >> c[i] >> h[i];
        sigma_h += h[i];
    }
    memset(dp, 0xcf, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = sigma_h; j >= h[i]; j--)
        {
            if (dp[j - h[i]] >= c[i]) {
                dp[j] = max(dp[j], dp[j - h[i]] - c[i]);
            }
        }
        for (int j = 0; j <= sigma_h; j++) {
            if (dp[j] >= 0) {
                dp[j] += x;
            }
        }
    }
    for (int i = sigma_h; i > -1; i--) {
        if (dp[i] >= 0) {
            cout << i<<endl;
            return;
        }
    }
}
signed main()
{
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：Fuxh_18 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1974E)
## 思路
看到题的第一眼，会想到背包，但数据范围，有点不合人意。~~看一眼标签~~，我们可以**用 dp 做**，用 $dp_{i,j}$ 来表示第 $i$ 天当幸福为 $j$ 时，最少的用钱。和背包一样，**第一维可以省略**。最后求出幸福值最高且买得起的那一个幸福值，就是正确答案。
## 注意
- 有多组数据，要记得**初始化**。
- 不开 long long 见祖宗。（本蒟蒻被此折磨甚久）
## [AC](https://www.luogu.com.cn/record/166898651) Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int m,c[51],h[51],s;
long long dp[N],x; //开 long long 
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>m>>x;
		memset(dp,0x3f,sizeof dp); //初始化 
		s=0;
		for(int i=1;i<=m;i++){
			cin>>c[i]>>h[i];
			s+=h[i]; //存一下幸福的总值 
		}
		dp[0]=0; //边界值
		for(int i=1;i<=m;i++){
			for(int j=s;j>=h[i];j--){
				dp[j]=min(dp[j],dp[j-h[i]]+c[i]); //判断要或不要哪种更省钱 
				if(dp[j]>(i-1)*x){ //买不起，设个极大值标记一下 
					dp[j]=0x3f3f3f3f3f3f3f3f;
				}
			}
		}
		for(int i=s;i>=0;i--){ //从大的幸福值往小的搜 
			if(dp[i]!=0x3f3f3f3f3f3f3f3f){ //第一个遇到的买得起的，肯定是幸福值最大的 
				cout<<i<<endl;
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

### 常规思路

一道非常简单的背包，定义 $dp_{i}$ 表示在拥有 $i$ 英镑时最多能获得的幸福值。但是 $c_{i}$ 太大，不能作为状态，怎么办？

### 正解

我们发现 $\sum h_{i} \le 10^5$，可以作为状态。

定义 $dp_{i}$ 表示花费 $i$ 英镑能获得的最大幸福值。

状态转移：
- $dp_{i} = \max ( dp_{i}, dp_{i - h_{i}} - c_{i} )$（当 $dp_{i-h_i} > c_{i}$ 时）

### Code

```cpp
#include <bits/stdc++.h>
#define int long long // 不开 long long 见祖宗
using namespace std;

const int N = 1e5 + 5;
int T, n, x;
int c[N], h[N], dp[N];

signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0); 
	cout.tie(0);
	cin >> T;
	while ( T-- ) 
	{
	    cin >> n >> x;
	    int s = 0;
	    for ( int i = 1; i <= n; i++ )
	    {
	    	cin >> c[i] >> h[i];
			s += h[i];
		}
	    memset ( dp, -0x3f, sizeof dp ); // 初始化
	    dp[0] = 0;
	    for ( int i = 1; i <= n; i++ ) 
		{
	        for ( int j = s; j >= h[i]; j-- )
	        {
				if ( dp[j - h[i]] >= c[i] ) dp[j] = max ( dp[j], dp[j - h[i]] - c[i] );
			}
			for ( int j = 0; j <= s; j++ ) if ( dp[j] >= 0 ) dp[j] += x;
	    }
	    for ( int i = s; i >= 0; i-- ) 
		{
			if ( dp[i] >= 0 )
			{
	        	cout << i << '\n';
	        	break;
	        }
	    }
	}
	return 0;
}
```

---

## 作者：gaomingyang101011 (赞：0)

# # CF1974E Money Buys Happiness 题解

## 思路：

这是一道动态规划的题目，我们很简单的就能想到用付出的英镑来建立动态转移方程，但英镑的数据范围最大能到 $5\times10^9$ 数组会爆掉，所以我们只能考虑别的方法。

在输入中告诉我们的除了英镑就是获得的幸福，那我们就可以考虑用幸福值来建立动态转移方程，表示为获得 $i$ 点幸福值所用的最少的英镑数。

下面是代码，有不懂的可以根据代码来理解。

## 代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const long long N=1e5+5;
long long t;
long long m,x;
long long c,h;
// 变量名与题目描述相同 
long long dp[N];
int main(){
	scanf("%d",&t);
	while(t--){
		long long love=0;
		// love是幸福值 
		memset(dp,127,sizeof(dp));
		dp[0]=0;
		// 初始值 
		scanf("%d%d",&m,&x);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&c,&h);
			love+=h;
			for(int j=love;j>=h;j--) if(dp[j-h]+c<=(i-1)*x) dp[j]=min(dp[j],dp[j-h]+c);
			// 算获得j的幸福需要的最小的钱 
		}
		while(dp[love]>(m-1)*x) love--;
		// 算最大能获得多少幸福 
		cout<<love<<endl;
	}
	return 0;
}
```

---

## 作者：chatoudp (赞：0)

一道很好的背包练习题。

### 若我们按照常规思路：

$dp_i$ 表示在拥有 $i$ 英镑时最多能获得的幸福值，那么你就会发现数组要开 $50 \times 10^8$。

开不了那么大啊！怎么办？

### 正解：

我们发现有一条件我们没用上：$\sum_{i=1}^{i\le m}h_i \le 10^5$。

我们可以发现可以让 $dp_i$ 表示拥有 $i$ 的幸福值时最少花几英镑，若无法正好获得这么多幸福值或会导致欠钱则为无穷大。此时数组只需开 $10^5$。

### 核心的背包代码：
```cpp
for(int i=1;i<=n;i++)
	for(int j=sum;j>=b[i];j--) {
		dp[j]=min(dp[j],dp[j-b[i]]+a[i]);
		if(dp[j]>(i-1)*x) dp[j]=0x3f3f3f3f3f3f3f3f;
	}
```

### 当然别忘了：

十年 oi 一场空，不开 long long 见祖宗！！！

## AC 代码：
```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
int t,n,a[55],b[55];
ll dp[100005],x;//十年oi一场空，不开long long见祖宗！！！ 
int main(){//'_' T_T ^_^
	scanf("%d",&t);
	while(t--){
		scanf("%d%lld",&n,&x);
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		int sum=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i],&b[i]);
			sum+=b[i];
		}
		for(int i=1;i<=n;i++)
			for(int j=sum;j>=b[i];j--) {
				dp[j]=min(dp[j],dp[j-b[i]]+a[i]);
				if(dp[j]>(i-1)*x) dp[j]=0x3f3f3f3f3f3f3f3f;
			}
		for(int i=sum;i>=0;i--)
			if(dp[i]!=0x3f3f3f3f3f3f3f3f){
				printf("%d\n",i);
				break;
			}
	}
	return 0;
}

```

---

## 作者：Sun_pirf (赞：0)

## [luogu CF1974E](https://www.luogu.com.cn/problem/CF1974E)


## 思路
明显的背包 dp ，考虑 $\operatorname{dp_{i,j}}$ 含义，可令 $dp$ 为 $(x,val,sum)$ 。

再依据背包特性，发现第一维无用，实际剩余钱数仅仅与上一月有关，遂省去一维。

易得状态转移方程：
$$
dp_{j}=\max(dp_j,dp_{j-h_i}-c_i)(当dp_{j-h_i}\ge c时)
$$

细节都在下面代码注释中。
## 代码
```cpp
#include<bits/stdc++.h>
#define N 100005
#define int long long //不开long long见祖宗（WA on #14）
using namespace std;
int t,m,x;
int c[N],h[N],dp[N];
int sum;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>t;
	for(int k=1;k<=t;k++){
		cin>>m>>x;
		sum=0;
		for(int i=1;i<=m;i++){
			cin>>c[i]>>h[i];
			sum+=h[i];
		}
		memset(dp,0xcf,sizeof(dp)); 
		dp[0]=0;//初始化
		for(int i=1;i<=m;i++){
	        for(int j=sum;j>=h[i];j--){
	        	if(dp[j-h[i]]>=c[i]){ //判断状态转移是否进行
	            	dp[j]=max(dp[j],dp[j-h[i]]-c[i]);
				}
			}     
	        for(int j=0;j<=sum;j++){//月末加工资x
	        	if(dp[j]>=0){
	               dp[j]+=x;	
				}
			}    
	    }
	    for(int i=sum;i>=0;i--){
	    	if(dp[i]>=0) {
		        cout<<i<<"\n";
		        break;
		    }
		} 
	}
	return 0;
}
```
Thanks For Watching.

---

## 作者：__LZH__ (赞：0)

# CF1974E Money Buys Happiness

## 题意

一共 $m$ 个月，每月结束后会收到 $X$ 元钱，在第 $i$ 个月可用 $c_i$ 的钱买 $h_i$ 的幸福，不能欠钱，求 $m$ 个月最大可得的幸福。

## 思路

第一眼想到 DP，第二眼 $O(n^2)$ 可过，直接开干。

## 状态与转移

状态：$(x,sum,cost)$，表示到了第 $x$ 个月，一共 $sum$ 的幸福，还剩 $cost$ 元。

转移：$(x,sum,cost) \to (x+1,sum,cost+X),(x+1,sum+h_x,cost-c_i+x)$

最优化属性：注意如果把 $sum$ 当最优化属性，$cost$ 最大可达 $5 \times 10^9$，DP 数组直接炸，所以改为 $cost$ 作最优化属性，越多越好。

## DP

状态：$dp_{i,j}$ 表示第 $i$ 月 $j$ 幸福，记录当前情况可得的最大钱数。

转移：$dp_{i,j}=\max(dp_{i-1,j}+x,dp_{i-1,j-h_i}-c_i+x)$

code:

```cpp
#include<bits/stdc++.h>

using namespace std;

int T, n, x, a[55], b[55];
long long dp[55][50010];

void solve(){
  cin >> n >> x;
  int sum = 0;
  for(int i = 1; i <= n; i++){
    cin >> a[i] >> b[i];
    sum += b[i];
  }
  for(int i = 0; i <= n; i++){
    for(int j = 0; j <= sum; j++){
      dp[i][j] = -1e18;
    }
  }
  dp[0][0] = 0;
  for(int i = 1; i <= n; i++){
    for(int j = 0; j <= sum; j++){
      dp[i][j] = max(dp[i - 1][j] + x, dp[i][j]);
    }
    for(int j = b[i]; j <= sum; j++){
      if(dp[i - 1][j - b[i]] >= a[i]){
        dp[i][j] = max(dp[i][j], dp[i - 1][j - b[i]] - a[i] + x);
      }
    }
  }
  for(int i = sum; i >= 0; i--){
    if(dp[n][i] >= 0){
      cout << i << '\n';
      return ;
    }
  }
}

int main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--){
    solve();
  }
  return 0;
}


//
```

---

## 作者：迟暮天复明 (赞：0)

显然钱数不能放到下标里。于是考虑类似于[这个题](https://www.luogu.com.cn/problem/AT_dp_e)的思路，把本应放在值上的量放到下标上，同时把剩下钱的数量作为 dp 数组记录的值，这题就可以做了。

具体做法就是：设 $f_{i,j}$ 是做到第 $i$ 个月，总开心程度为 $j$ 时能剩下的最多的钱。转移显然是 $f_{i,j}=\max\{f_{i-1,j}+k,(f_{i-1,j-h_i}-c_i)+k\}$。时间和空间复杂度都是 $O(m\sum h)$。数组的第一维可以压，但是这题不需要。

[提交记录](https://codeforces.com/contest/1974/submission/261992535)

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

模型其实很简单，典型的背包，但是不同寻常的是其价值值域较小，而代价的值域偏大。

因此逆向思考，第二维用价值代替代价，求此时剩余的最大代价。如果这个值大于等于 $0$，那么意味着这个价值是可行的。

最后，用上背包常用的压维度，原地滚动就能过掉此题。

代码如下：

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m, dp[100005], l, r, sm;
signed main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n >> m; sm = 0;
		memset(dp, 0xcf, sizeof dp);
		dp[0] = 0;
		for (int i = 1; i <= n; ++i) {
			cin >> l >> r; sm += r;
			for (int j = sm; j >= 0; --j) {
				if (j >= r && dp[j - r] >= l)
					dp[j] = max(dp[j], dp[j - r] - l);
				if (dp[j] >= 0) dp[j] += m;
			}
		}
		for (int i = sm; i >= 0; i--)
			if (dp[i] >= 0) {
				cout << i << endl; break;
			}
	}
	return 0;
}
```

---

