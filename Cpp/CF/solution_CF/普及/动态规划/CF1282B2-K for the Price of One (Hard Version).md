# K for the Price of One (Hard Version)

## 题目描述

This is the hard version of this problem. The only difference is the constraint on $ k $ — the number of gifts in the offer. In this version: $ 2 \le k \le n $ .

Vasya came to the store to buy goods for his friends for the New Year. It turned out that he was very lucky — today the offer " $ k $ of goods for the price of one" is held in store.

Using this offer, Vasya can buy exactly $ k $ of any goods, paying only for the most expensive of them. Vasya decided to take this opportunity and buy as many goods as possible for his friends with the money he has.

More formally, for each good, its price is determined by $ a_i $ — the number of coins it costs. Initially, Vasya has $ p $ coins. He wants to buy the maximum number of goods. Vasya can perform one of the following operations as many times as necessary:

- Vasya can buy one good with the index $ i $ if he currently has enough coins (i.e $ p \ge a_i $ ). After buying this good, the number of Vasya's coins will decrease by $ a_i $ , (i.e it becomes $ p := p - a_i $ ).
- Vasya can buy a good with the index $ i $ , and also choose exactly $ k-1 $ goods, the price of which does not exceed $ a_i $ , if he currently has enough coins (i.e $ p \ge a_i $ ). Thus, he buys all these $ k $ goods, and his number of coins decreases by $ a_i $ (i.e it becomes $ p := p - a_i $ ).

Please note that each good can be bought no more than once.

For example, if the store now has $ n=5 $ goods worth $ a_1=2, a_2=4, a_3=3, a_4=5, a_5=7 $ , respectively, $ k=2 $ , and Vasya has $ 6 $ coins, then he can buy $ 3 $ goods. A good with the index $ 1 $ will be bought by Vasya without using the offer and he will pay $ 2 $ coins. Goods with the indices $ 2 $ and $ 3 $ Vasya will buy using the offer and he will pay $ 4 $ coins. It can be proved that Vasya can not buy more goods with six coins.

Help Vasya to find out the maximum number of goods he can buy.

## 样例 #1

### 输入

```
8
5 6 2
2 4 3 5 7
5 11 2
2 4 3 5 7
3 2 3
4 2 6
5 2 3
10 1 3 9 2
2 10000 2
10000 10000
2 9999 2
10000 10000
4 6 4
3 2 3 2
5 5 3
1 2 2 1 2
```

### 输出

```
3
4
1
1
2
0
4
5
```

# 题解

## 作者：Rex01 (赞：3)

## [CF1282B2 题目传送门](https://www.luogu.com.cn/problem/CF1282B2)

## 题目大意
有 $n$ 个商品，每种商品都有价格 $a_i$，每种商品只能购买一次。现在买一个物品，可以免费拿走价格低于它的 $k - 1$ 个物品，但当比它价格小的商品不足 $k - 1$ 个时，此优惠无效。给定总钱数，求能购买的最多物品数量。

## 解决思路
根据~~课上老师讲的思路~~我自己的推导，我想到了**贪心**并得到了两个 DP 公式：
- 若 $i < k$，则 $z_i = z_{i - 1} + a_i$；
- 若 $i \geq k$，则 $z_i = z_{i - k} + a_i$。

然后就好说了，枚举上述式子中的 $z$ 数组，当 $z_i \leq p$ 时，$i$ 即为答案。

## 代码展示
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
//不用万能头，从我做起
using namespace std;

sont int N = 3e6 + 80;
int t, n, p, k, a[N], z[N], ans;

int main()
{
	ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);//减少输入时间
	cin >> t;
	while(t--)
	{
		ans = 0;
		cin >> n >> p >> k;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + n + 1);//从小到大排序
		for(int i = 1; i <= n; i++)
			z[i] = 0x3f3f3f3f;//代替memset,全部赋值
		for(int i = 1; i <= n; i++)
		{//分情况讨论 
			if(i >= k) z[i] = min(z[i], z[i - k] + a[i]);
			z[i] = min(z[i], z[i - 1] + a[i]);
		}
		for(int i = 1; i <= n; i++)
			if(z[i] <= p) ans = i;//枚举最终答案
		cout << ans << endl;
	}
```

---

## 作者：OIerWu_829 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1282B2)

水 DP。

先把 $a$ 数组从小到大排个序，然后设 $f_i$ 表示买前 $i$ 个物品所需的钱数，如果 $i<k$ 则不会有免费的优惠，如果 $i\ge k$ 则会免费得到价格低于当前的 $k-1$ 个物品，则状态转移方程如下：

$$
f_i=\begin{cases}
f_{i-1}+a_i & i<k \\
f_{i-k}+a_i & i\ge k
\end{cases}
$$

最后因为要输出最多能够买的物品数量，所以从 $n$ 到 $1$ 循环，如果 $f_i\le p$ 则钱数就在限制范围内，输出 $i$，如果没有符合要求的就输出 $0$。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5 + 5;
const int Inf = 0x3f3f3f3f;

int a[N], f[N]; 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
	int T;
	cin >> T;
	while (T--)
	{
		int n, p, k;
		cin >> n >> p >> k;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			f[i] = Inf;
		}
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; i++)
		{
			if (i < k) f[i] = min(f[i], f[i - 1] + a[i]);
			else f[i] = min(f[i], f[i - k] + a[i]);
		}
        bool fl = true;
		for (int i = n; i >= 1; i--)
			if (f[i] <= p)
			{
                fl = false;
				cout << i << "\n";
				break;
			}
        if (fl) cout << "0\n";
	}
	return 0;
}
```

---

## 作者：__cheems__ (赞：2)

## 思路

考虑排序、贪心与动规。

首先对于给出的 $n$ 个商品，我们可以先将其排序。则对于第 $i$ 个商品，若条件 $i \ge k$ 成立，则我们可以用 $a_i$ 元的价格买下 $k$ 个商品。

然后使用贪心。对于任意两个可以免费得到 $k$ 个商品的商品，选择价格较小的商品的方案更优。所以尽量选价格小的商品。

最后是动规。定义 $dp_i$ 的状态表示若买下前 $i$ 个商品至少需要 $dp_i$ 元钱。那么对于 $dp_i$ 此时分两种情况。

- $i < k$，此时购买第 $i$ 个商品不会免费得到商品，因此 $dp_i=dp_{i-1}+a_i$。

- $i \ge k$，此时购买第 $i$ 个商品会免费得到 $k - 1$ 的商品，因此 $dp_i=dp_{i-k}+a_i$。

程序结尾枚举每一个 $dp_i$ ，当 $dp_i \le p$ 且 $dp_{i+1} > p$ 时，$i$ 即为购买商品数量的最大值。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int n, p, k, a[3000080];
int dp[3000080];
int main()
{
	cin >> t;
	while (t--)
	{
		int ans = 0;
		cin >> n >> p >> k;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) dp[i] = 0x3f3f3f3f;
		for (int i = 1; i <= n; i++)
		{
			if (i >= k) dp[i] = min(dp[i], dp[i - k] + a[i]); // i >= k 的情况下，购买前 i 个商品只需要用 dp[i - k] + a[i] 元钱
			dp[i] = min(dp[i], dp[i - 1] + a[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			if (dp[i] <= p)
			{
				ans = i; // 枚举答案
			}
		}
		cout << ans << "\n";
	}
    return 0;
}

```

---

## 作者：ztytql (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1282B2)
## Description
有 $n$ 个商品，每个商品都有价格 $a_i.$ 现在有一个活动促销，具体为买一个物品，可以免费拿走价格低于它的 $k-1$ 个物品，特别的，当比他价格小的商品不足 $k-1$ 个时，此优惠无效。

给定总钱数，求能购买的最多物品数量。
## Solution
考虑贪心。

我们可以想到，在没有优惠的前提下，如果要使购买数量最大化，我们必须要购买价格更低的物品。所以对于此题来说，最优解应是先将 $k-1$ 个价格最低的物品尽可能购买，如果有剩余的钱数，在判断是否满足优惠政策。

设 $dp_i$ 为购买前 $i$ 个物品所需要的总钱数，我们可以总结出递推式：

当 $i<k$ 时，$dp_i=dp_{i-1}+a_i,$

否则 $dp_i=dp_{i-k}+a_i.$

这样算出的结果一定是最优解，我们就可以从后向前枚举购买的个数，并判断是否小于所给钱数即可。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 200010;

int q, n, p, k; // q, n, p, k 如题目中所述
int a[N], dp[N];

signed main()
{
	cin >> q;
	
	while (q --)
	{
		cin >> n >> p >> k;
		
		for (int i = 1 ; i <= n ; i ++)
			cin >> a[i];
		
		sort(a + 1, a + 1 + n); // 排序，为了保证价格从小到大
		
		for (int i = 1 ; i <= n ; i ++) // 刚刚的递推式
			if (i < k)
				dp[i] = dp[i - 1] + a[i];
			else
				dp[i] = dp[i - k] + a[i];
		
		for (int i = n ; i >= 0 ; i --) // 从后向前枚举，这样第一个符合条件的数便是最终结果
			if (dp[i] <= p)
			{
				cout << i << endl;
				break;
			}
	}
	
	return 0;
}
```

---

## 作者：alan1118 (赞：1)

## 题意

[【Easy Version】](https://www.luogu.com.cn/problem/CF1282B1)
/[【Hard Version】](https://www.luogu.com.cn/problem/CF1282B2)

题目描述很清楚，不再过多解释。

## 思路

一道 DP 好题，这道题跟 Easy Version 唯一的区别其实就是 $k$ 不是固定的数，但方法其实一模一样。

第一步要注意，输入的 $a$ 数组不一定有序，所以要先排序。

然后开始考虑 DP。定义 DP 状态 $dp_i=j$ 表示买前 $i$ 个物品最少需要花 $j$ 元。

有了这个转移方程就非常简单了。

1. 如果这个比物品便宜的 $>k-1$，换句话说，这个物品排序后的下标 $\ge k$，这时候 $dp_i=\min(dp_i,dp_{i-k}+a_i)$。

2. 如果下标 $<k$，$dp_i=\min(dp_i,dp_{i-1}+a_i)$。

最后倒着遍历一遍，如果 $dp_i\le p$ 就直接输出 $i$ 就行了。但是这里有个坑点，就是有可能一个都买不了，这时候要特判一下。

## Code
``` cpp
#include <iostream>
#include <algorithm>
using namespace std;
 
const int N = 2e5 + 5;
 
int a[N], dp[N];
 
int main()
{
	int t;
	cin >> t;
	while(t--)
    {
		int n, p, k;
		cin >> n >> p >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i <= n; i++) dp[i] = 2e9;
		sort(a+1, a+n+1);
		for(int i = 1; i <= n; i++)
		{
			if(i >= k) dp[i] = min(dp[i], dp[i-k] + a[i]);
			else dp[i] = min(dp[i], dp[i-1] + a[i]);
		}
        int f = false;
		for(int i = n; i >= 1; i--)
			if(dp[i] <= p)
            {
                cout << i << endl;
                f = true;
                break;
            }
        if(!f) cout << 0 << endl;
	}
	return 0;
}
```

---

## 作者：Lu_xZ (赞：1)

**CF1282B2		\*1600**

怎么清一色 dp，我来发个贪心。

将物品排序，我们要做的等效于在数轴上取若干孤立点和长度为 $k$ 的整段。

证明几个结论：

1. $k$ 个孤立点不优于一个整段。

   设这 $k$ 个点分别为 $a_1, a_2,\cdots, a_k$，满足前一个点小于后一个点。

   把 $1\sim k - 1$ 个点靠到 $k$ 左边，这样总代价只需要 $a_k$。

   考虑这个操作产生的影响。

   对于大于 $r$ 的部分，没有影响。

   对于小于 $r$ 的部分，如果存在整段或孤立点小于 $r$ 但不属于这 $k$ 个点，那么会被挤到左边，代价变小。

2. 整段间一定连续。

   有间隔只会使代价变大，全部靠紧最优。

3. 孤立点一定是 $[1, k - 1]$ 的一个前缀。

   首先根据结论 $1$，已经证明了孤立点数小于 $k$。

   如果最大的孤立点左边大于 $k - 1$，那么一定能花更小的代价买一个整段，且物品数量变多。

   孤立点一定连续，与结论 $2$ 类似。

贪心策略：

枚举用了前几个孤立点，不断往后取连续整段。

时间复杂度 $O(k \cdot \dfrac{n}{k})$。

```cpp
void solve() {
	cin >> n >> p >> k;
	for(int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	int ans = 0;
	int sum = 0;
	for(int i = 0; i < k; ++ i) {
		sum += a[i];
		if(sum > p) {
			break;
		}
		int tmp = i, cur = sum;
		for(int j = i + k; j <= n; j += k) {
			cur += a[j];
			if(cur > p) break;
			tmp += k;
		}
		ans = max(ans, tmp);
	}
	cout << ans << '\n';
}
```

---

## 作者：User757711 (赞：1)

# [CF1282B2 K for the Price of One (Hard Version)](https://www.luogu.com.cn/problem/CF1282B2) 题解
### 题目大意
有 $n$ 个商品，每个的价格为 $a_{i}$，现在买一个物品就可以拿走 $k-1$ 个价格低于它的商品。

价格比它小的商品不足 $k-1$ 个时，活动无效。
### 思路分析
主要思路为贪心。

如果要使购买数量最多，就要尽可能买价格小的。

递推式：

如果 $i<k$，$f_i=f_{i-1}+a_i$。

如果 $k \le i$，$f_i=f_{i-k}+a_i$。

这样一定为最优解，最后遍历一遍寻找答案即可。
### 最后，附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e6+7;
int w[200050],f[200050];
int ans;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int n,p,k;
		cin>>n>>p>>k;
		for(int j=1;j<=n;j++)
		{
			cin>>w[j];
		}
		sort(w+1,w+1+n); //从小到大排序
		memset(f,0,sizeof(f));
		for(int j=1;j<=n;j++)
		{
			if(j<k) //递推式1
			{
				f[j]=f[j-1]+w[j];
			}
			else //递推式2
			{
				f[j]=f[j-k]+w[j];
			}
		}
		for(int j=1;j<=n;j++)
		{
			if(f[j]<=p) //寻找答案
			{
				ans=j;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
### The End！

---

## 作者：__Creeper__ (赞：1)

## 题意

有 $n$ 个商品，每个商品价格为 $a_{i}$，现在买一个物品就可以拿走 $k−1$ 个价格低于它的商品。价格比它小的商品不足 $k−1$ 个时，活动无效。

## 思路

主要思路为贪心，如果要使购买数量最多，就要尽可能买价格小的，我们可以使用动态规划。

#### 定义状态

$dp_{i}$ 表示买了前 $i$ 个商品的最低价格。而对于题目中说的买了某个商品可以免费得到 $k−1$ 个价格比该商品低的商品。

#### 状态转移

我们可以贪心地将免费得到的商品设为都是比该商品低的最贵的那 $k−1$ 个，可以用 sort 排序实现，这绝对是最优的，即：

- 当 $i \ge k$ 时，$dp_{i} = dp_{i-k} + a_{i}$

- 当 $i < k$ 时，$dp_{i} = dp_{i-1} + a_{i}$

#### 最终结果

最后就是倒序去枚举能够买到的商品个数 $i$，其需要的最低价格即 $dp_{i}$，判断是否能用 $p$ 元买下即可。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int q, n, p, k;
int a[N], dp[N];

signed main()
{
	cin >> q;
	while ( q-- )
	{
		memset ( dp, 0, sizeof ( dp ) );
		cin >> n >> p >> k;	
		for ( int i = 1; i <= n; i++ )
		{
			cin >> a[i];
		}
		sort ( a + 1, a + n + 1 );
		for ( int i = 1; i <= n; i++ )
		{
			if ( i < k )
			{
				dp[i] = dp[i - 1] + a[i];
			}
			else
			{
				dp[i] = dp[i - k] + a[i];
			}
		}
		for ( int i = n; i >= 0 ; i-- )
		{
			if ( dp[i] <= p )
			{
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：liuyz11 (赞：1)

# 题解 CF1282B2 【K for the Price of One (Hard Version)】

原比赛题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12173579.html)

题目大意：有n个商品，每个商品价值为  ai  现在有一个活动优惠，买一个物品可以选择k - 1个价值小于等于该它的物品免费获得（要么一个也不选，要么一定要选k - 1个），求k个硬币一共能买多少物品。在该题中k <= n。

做完这道题发现B1写复杂了，其实这两题代码一样的……

主要思路就是贪心+递推。

很显然，若是买了第i个物品，价值小于它的必然要选（不要白不要，而且肯定要最贵的）。

那么我们就得出了递推式 f[i] = f[i - k] + a[i] ，但是注意若i小于等于k，需要的花费为前i个物品的总和。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 200005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int a[MAXN], dp[MAXN];

int main(){
	int t;
	scanf("%d", &t);
	rep(times, 1, t){
		int n, p, k;
		scanf("%d%d%d", &n, &p, &k);
		rep(i, 1, n) scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		int ans = 0;
		rep(i, 1, n){
			if(i < k) dp[i] = dp[i - 1] + a[i];
			else dp[i] = dp[i - k] + a[i];
		}
		rep(i, 1, n)
			if(dp[i] <= p) ans = i;
		printf("%d\n", ans);
	}
    return 0;
}

```

---

## 作者：Pump_kin (赞：0)

首先简单考虑一下，如果说你买了一个价值较大的物品，那么显然不是最优的，因为你可以选一个较小的物品。

于是很自然想到对 $a$ 数组排序。

由于 $p$ 的范围是很大的，因此，我们不从 $p$ 去入手，而是从 $n$ 的角度，考虑选取前 $i$ 需要多少钱。

设置动态规划数组 $dp_i$，表示选取前 $i$ 最少花费的钱数。

根据定义，不难写出转移方程：

> 当 $i<k$，$dp_i=dp_{i-1}+a_i$
> 
> 当 $i\ge k$，$dp_i=dp_{i-k}+a_i$

这是因为 $dp_{i-k}$ 肯定比 $dp_i$ 要大。

然后正常写就好啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
const int inf=2e9+1e7;
int T;
int n,p,k;
int a[N];
#define L(i,j,k) for(int i=j;i<=k;i++)

int dp[N];

void solve(){
	dp[0]=0;
	cin>>n>>p>>k;
	L(i,1,n)dp[i]=inf;
	L(i,1,n)cin>>a[i];
	sort(a+1,a+n+1);
	L(i,1,n){
		if(i>=k)dp[i]=min(dp[i],dp[i-k]+a[i]);
		else dp[i]=dp[i-1]+a[i];
	}
	int ans=0;
	L(i,1,n)if(dp[i]<=p)ans=max(ans,i);
	cout<<ans<<'\n';
}

int main(){
	
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	
	cin>>T;
	
	while(T--)solve();
	
	return 0;
}
```

---

## 作者：HEzzz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1282B2)

## 解析

因为题目要求买到的商品数量最多，所以我们考虑贪心地从便宜的买起，即先把商品按价格排序。

不难想到我们可以使用动态规划，定义状态 $dp_i$ 表示前 $i$ 全都买了的最低价格。而对于题目中说的买了某个商品可以免费得到 $k-1$ 个价格比该商品低的商品，我们可以贪心地将免费得到的商品设为都是比该商品低的最贵的那 $k-1$ 个，仔细想想可以知道这绝对是最优的，即

- 当 $i\ge k$ 时，$dp_i=dp_{i-k}+a_i$。

- 而当 $i<k$ 时，显然就是 $dp_i=dp_{i-1}+a_i$。

这样我们就可以轻易求出 $dp_i$ 了。最后就是倒序去枚举能够买到的商品个数 $i$，其需要的最低价格即 $dp_i$，判断是否能用 $p$ 元买下即可。

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(LL i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(LL i=(a);i>=(b);i--) 
using namespace std;
typedef long long LL;
typedef double db;
const int N=2e5+5,Mod=1e9+7;
int t,n,p,k,a[N],dp[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>p>>k;
		_rep(i,1,n) cin>>a[i],dp[i]=0;
		sort(a+1,a+n+1);//先排序
		_rep(i,1,n)
		{
			if(i<k) dp[i]=dp[i-1]+a[i];
			else dp[i]=dp[i-k]+a[i];
		}
		_antirep(i,n,0)
		{
			if(dp[i]<=p)
			{
				cout<<i<<"\n";
				break;
			}
		}
	}
 	return 0;
}
```

---

## 作者：Shunpower (赞：0)

这题样例怎么这么弱……

## Solution

很套路地可以想到将 $a$ 排序之后，每次拿走的 $k$ 个商品肯定是连续的。

> 结论 1. 在购买 $a$ 商品后选取赠送所得的 $k-1$ 个商品时，一定选择目前场上未购买且价值小于等于 $a$ 的商品中最大的 $k$ 个。  
> 证明：显然，如果不连续，则在拿走相同数量商品的前提下，场上剩余商品的价值对之后不优。（因为多拿了价值小的商品，舍弃了价值大的商品）

下面我们都直接把 $a$ 变成从小到大排序后的 $a$ 了。

在此基础上，进一步想到应该是每 $k$ 个拿一下最优，发现这也是对的。

> 结论 2. 把一次拿 $k$ 个看作是一次拿一段长为 $k$ 的区间（通过拿区间右端点那个商品来取走这个区间里的所有商品），则这些区间首尾相连。  
> 证明：考虑区间 $i,i+1$ 之间首尾不相连，且中间空出的部分最后不再回来单个拿，则把 $i+1$ 向前移动，得到的商品总数不变，但拿走 $i+1$ 这个区间花费的钱变少了。如果中间空出的部分有后面需要回来单个拿的，则至少可以调整到回来拿的部分是恰好夹在两个区间中间的一整段（全都往左挤压到 $i$ 区间的右端点）。  
> 下面我们进一步证明这是不优的。考虑回来拿的部分的最左端 $a_l$，可以发现，将区间 $i$ 的右端点挪到 $l$，则左边可以空出一个一定 $\leq a_l$ 的值，此时调整过去，商品总数不变，但花费钱数单调不增。

可以发现，调整过程类似于把“最后回来拿的一整段”从 $i+1$ 前面挪到了 $i$ 前面。以此类推可知，“最后回来拿的一整段”最后会直接成为 $a$ 的一个前缀。我们枚举这个前缀的最后一位 $i$，然后从 $i+1$ 开始 $k$ 个 $k$ 个地取到不能取就行了。

想得出能取多少位，可以按照下标对 $k$ 的余数分别垒前缀和，直接在 $(i+1)\bmod k$ 的那个前缀和里面二分就可以了。

## Code

```cpp
int tc;
int n,p,k;
int a[N];
vector <int> sum[N];
void solve(){
    cin>>n>>p>>k;
    fr1(i,1,n) cin>>a[i];
    sort(a+1,a+n+1);
    fr1(i,0,k) sum[i].clear(),sum[i].pb(0);
    fr1(i,1,n-k+1) sum[i%k].pb(sum[i%k].back()+a[i+k-1]);
    int ans=0;
    int res=0;
    fr1(i,0,n){
        ans+=a[i];
        if(ans>p) break;
        int id=(i+1)%k;
        int nex=(i+1-((i+1)%k-1+k)%k)/k+1;
        int it=upper_bound(sum[id].begin(),sum[id].end(),p-ans+sum[id][nex-1])-sum[id].begin()-1;
        res=max(res,i+max(0,it-nex+1)*k);
    }
    cout<<res<<'\n';
}
```

---

