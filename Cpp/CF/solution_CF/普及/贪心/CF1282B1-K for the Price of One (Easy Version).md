# K for the Price of One (Easy Version)

## 题目描述

This is the easy version of this problem. The only difference is the constraint on $ k $ — the number of gifts in the offer. In this version: $ k=2 $ .

Vasya came to the store to buy goods for his friends for the New Year. It turned out that he was very lucky — today the offer " $ k $ of goods for the price of one" is held in store. Remember, that in this problem $ k=2 $ .

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
6
5 6 2
2 4 3 5 7
5 11 2
2 4 3 5 7
2 10000 2
10000 10000
2 9999 2
10000 10000
5 13 2
8 2 8 2 5
3 18 2
1 2 3
```

### 输出

```
3
4
2
0
4
3
```

# 题解

## 作者：alan1118 (赞：2)

## 题意

[【Easy Version】](https://www.luogu.com.cn/problem/CF1282B1)
/[【Hard Version】](https://www.luogu.com.cn/problem/CF1282B2)

题目描述很清楚，不再过多解释。

## 思路

第一步要注意，输入的 $a$ 数组不一定有序，所以要先排序。

然后开始考虑 DP。定义 DP 状态 $dp_i=j$ 表示买前 $i$ 个物品最少需要花 $j$ 元。

有了这个转移方程就非常简单了：

1. 如果这个比物品便宜的 $>1$，换句话说，这个物品排序后的下标 $\ge 2$，这时候 $dp_i=\min(dp_i,dp_{i-2}+a_i)$。

2. 如果下标 $<2$，$dp_i=\min(dp_i,dp_{i-1}+a_i)$。

最后倒着遍历一遍，如果 $dp_i\le p$ 就直接输出 $i$ 即可。注意有可能一个都买不了，这时候要特判一下。

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
			if(i >= 2) dp[i] = min(dp[i], dp[i-2] + a[i]);
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

如果你 AC 了这道题，可以去看看 [Hard Version](https://www.luogu.com.cn/article/sjcpjxjw)。

---

## 作者：SnapYust (赞：1)

## 题目传送门

[K for the Price of One (Easy Version)](https://www.luogu.com.cn/problem/CF1282B1)

## 思路

看了一遍除我以外的那篇题解，用 dp 做的，写的很好，但依然可以优化，本篇题解会给出更加详细的**推导过程**和**优化方案**。

------------

相信大家看到题面都知道是用 dp 来做的吧，这是一道 dp 练手题，可供像我一样的蒟蒻练习。

根据[我的这篇文章](https://snap-yust666.blog.luogu.org/ji-chu-dp-di-zuo-ti-jing-yan)可知，最少硬币问题及其变种（比如本题）通常会设 $dp_i$ 为前 $i$ 个的最小花费，但在本题很难直接看出这种状态转移方程。

初步地，我们可以设 $dp_{i,k(k\in[0,1])}$ 为前 $i$ 个，选或不选第 $i$ 个的最小花费。

在 $k=1$ 时：因为是最小花费，因此是 $dp_{i-1,0}$ 和 $dp_{i-1,1}$ 取 $\min$，又因为选当前的，所以后面还要加上第 $i$ 件物品的价格，即 $a_i$。

因此：

$$dp_{i,1}=\min(dp_{i-1,0},dp_{i-1,1})+a_i$$

在 $k=0$ 时，考虑继承。

**但是注意**！有很多人（包括我最开始）都会在这里掉坑，会把转移方程误认为：

$$dp_{i,0}=\min(dp_{i-1,0},dp_{i-1,1})$$

这样做会发生什么呢？因为 $dp_{0,0}$ 的初始值为 $0$，每次取 $\min$，最后每一个 $dp_{i,0}$ 的值都为 $0$，直接导致了答案的错误。

实际地，$dp_{i,0}$ 从某种意义上来说，并不是有意义的状态（有点绕口），就是说，$dp_{i,0}$ 只是为 $dp_{i,1}$ 服务的，本身并没有意义，再来想想 $dp_{i,0}$ 的含义，表示前 $i$ 个**并且不取**第 $i$ 个的最小花费，那不就是前 $i-1$ 个的最小花费吗？

搞懂了这个问题，状态转移方程也就迎刃而解了：

$$dp_{i,0}=dp_{i-1,1}$$

至此，也就推导出了最普通的状态转移方程：

$$dp_{i,1}=\min(dp_{i-1,1},dp_{i-1,0})+a_i$$

$$dp_{i,0}=dp_{i-1,1}$$

$$ans=\max i(1\le i\le n,dp_{i,1}\le p)$$

现在线性的复杂度可以**切爆本题**。

现在来想想**优化**。

线性的时间复杂度是很难再优化了，我们来优化空间常数。

我上面说的：$dp_{i,0}$ 从某种意义上来说，并不是有意义的状态，因为 $dp_{i,0}$ 完全可以用 $dp_{i-1,1}$ 来替代，现在用 $dp_{i-1,1}$ 来替代 $dp_{i,0}$，代入到上面的状态转移方程中：

$$(1)dp_{i,1}=\min(dp_{i-1,1},dp_{i-2,1})+a_i$$

$$(2)ans=\max i(1\le i\le n,dp_{i,1}\le p)$$

根据上式，发现 $i$ 后面跟着的都变成了 $1$，因此，我们可以将空间缩小为原来的一半（虽然这在考场上没什么用（））。

因此：

$$dp_1=a_1$$

$$dp_{i}=\min(dp_{i-1},dp_{i-2})+a_i$$

$$ans=\max i(1\le i\le n,dp_{i}\le p)$$

实现用循环就行，不放代码了。

---

## 作者：liuyz11 (赞：1)

# 题解 CF1282B1 【K for the Price of One (Easy Version)】

该场比赛的题解:[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12173579.html)

题目大意：有n个商品，每个商品价值为 ai ，现在有一个活动优惠，买一个物品可以选择k - 1个价值小于等于该它的物品免费获得（要么一个也不选，要么一定要选k - 1个），求k个硬币一共能买多少物品。在该题中k = 2。

不难发现，买下来的的物品一定是最便宜的那几个。我们设状态 dp[i][0/1] 表示第i个物品选还是不选的最小花费。

若是不选了i个，i - 1肯定要选，若是选了第i个，第i - 1个可以选可以不选，得到转移方程。

最后找到最大的 dp[i][1] 小于等于p即为答案。

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

int a[MAXN], dp[MAXN][2];

int main(){
	int t;
	scanf("%d", &t);
	rep(times, 1, t){
		int n, p, k;
		scanf("%d%d%d", &n, &p, &k);
		rep(i, 1, n) scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		rep(i, 1, n){
			dp[i][0] = dp[i - 1][1];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
		}
		int ans = 0;
		rep(i, 1, n)
			if(dp[i][1] <= p) ans = i;
			else break;
		printf("%d\n", ans);
	}
    return 0;
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1282B1)

## 思路
由于只能免费得到价格更小的商品，而且要买尽可能多的商品，所以我们可以对商品按价格从小到大进行排序，然后尽可能得到价格小的商品。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = (st); i <= (ed); ++i)
#define RFOR(st, ed, i) for (int i = (ed); i >= (st); --i)

//#define debug

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;

const int maxn = 2e5 + 10;

int t;
	int n, p, k;
	int a[maxn];

int ans;
int dp[maxn];

void work_t () {
	ans = 0;
	
	scanf("%i%i%i", &n, &p, &k);
	FOR (1, n, i) {scanf("%i", &a[i]);}
	
	sort(a + 1, a + n + 1);
	FOR (1, k - 1, i) {
		dp[i] = dp[i - 1] + a[i];
		if (dp[i] <= p) {ans = i;}
	}
	FOR (k, n, i) {
		dp[i] = dp[i - k] + a[i];
		if (dp[i] <= p) {ans = i;}
	}
	
	printf("%i\n", ans);
}
int main () {
	scanf("%i", &t);
	while (t--) {work_t();}
	return 0;
}
```

---

## 作者：Rex01 (赞：0)

## [CF1282B1 题目传送门](https://www.luogu.com.cn/problem/CF1282B1)

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

const int N = 3e6 + 80;
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
  	return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF1282B1 K for the Price of One (Easy Version)](https://www.luogu.com.cn/problem/CF1282B1)

本题题解可以通过[加强版](https://www.luogu.com.cn/problem/CF1282B2)。

一道基础 DP + 贪心。

## 思路

这道题要求得到商品数量的最大值，那么肯定是选越便宜的越好。所以开头先要排序。

接下来步入正题：我们设 $f_i$ 表示买前 $i$ 个商品花的最小钱数，那么转移方程就显而易见。

$$
\begin{cases}
f_i = f_{i - k} + a_i & i < k \\
f_i = f_{i - 1} + a_i & i \ge k
\end{cases}
$$

解释一下：商品数量不足 $k − 1$ 个时则无法免费得到它们，所以前 $k - 1$ 个商品需要付费购买；而商品数量比 $k − 1$ 多时则可以免费得到前 $k - 1$ 个商品。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[200005], dp[200005];

void solve()
{
    int n, p, k, pos = 0;
    cin >> n >> p >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + 1 + n);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i >= k)
            dp[i] = dp[i - k] + a[i];
        else
            dp[i] = dp[i - 1] + a[i];
        if (dp[i] <= p)
            pos = i;
    }
    cout << pos << endl;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

为什么之前的 tj 都是 DP 啊，没人用贪心么。

那我就来一发吧。

首先先给 $a$ 数组排个序，因为在本题的条件下，取价格少的物品肯定更优。

因为 $k=2$，所以就把这些数两两一组，就有以下三种情况：

- 当前的硬币不够买这一组的第一个物品了，直接 `break`。
  
- 当前的硬币不够买这一组的第二个物品了，但是够买这一组的第一个物品了，将 `ans` 加 $1$，然后 `break`。

- 当前的硬币够买这一组的第二个物品，那么将硬币数量减少第二个物品的价格，然后使用优惠，将这一组的第 $1$ 个也买下来，所以将 `ans` 加 $2$。

当然，分组的方法也有两种，第一种是以 $1$ 开头分组，第二种是以 $2$ 开头进行分组，两种取最大值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 10;
int T,n,p,k;
int a[N],sum[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> n >> p >> k;
	int P = p;
	for (int i = 1 ; i <= n ; i++)
		cin >> a[i];
	sort (a + 1,a + n + 1);
	int ans = 0; // 第一种方法
	for (int i = 1 ; i <= n / 2 ; i++){
		if (a[(i << 1) - 1] > p) break;
		if (a[(i << 1)] > p){
			ans++;
			break;
		}else{
			ans += 2;
			p -= a[(i << 1)];
		}
	}
	if (n & 1) if (p >= a[n]) ans++; // 如果末尾还有单独一个
	p = P;
	int ans2 = 0; // 第二种方法
	if (p >= a[1]){
		p -= a[1];
		ans2++;
	} // 先判第一个
	for (int i = 1 ; i <= (n - 1) / 2 ; i++){
		if (a[(i << 1)] > p) break;
		if (a[(i << 1) + 1] > p){
			ans2++;
			break;
		}else{
			ans2 += 2;
			p -= a[(i << 1) + 1];
		}
	}
	if (n % 2 == 0) if (p >= a[n]) ans2++;
	cout << max(ans,ans2) << endl;
}
signed main(){
	close();
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

题目指定 $k=2$，则显然每次只能选或不选一个比 $i$ 价值小的物品。

那显然经典价值问题，定义 $f_{i,0/1}$ 表示为前 $i-1$ 个必须获得且当前不选或选的最小金币值，则：

- $f_{i,1}=\min\left(f_{i-1,0},f_{i-1,1}\right)+a_{i}$
- $f_{i,0}=f_{i-1,1}+a_{i}$

当然可以像[这篇题解](https://www.luogu.com.cn/article/gwf6v5a5)一样进行优化常数，在这里不多进行阐述。

#### code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define lx first
#define ly second
const int maxn=2e5+10;
int T;int n,p,k;
int a[maxn];
inline int read(){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
int f[maxn][10];
signed main(){
    T=read();
    while(T--){
        n=read(),p=read(),k=read();
        for(int i=1;i<=n;++i)scanf("%d",a+i);
        sort(a+1,a+n+1);int ans=0;
        f[1][0]=0,f[1][1]=a[1];
        for(int i=2;i<=n;++i)f[i][1]=min(f[i-1][0],f[i-1][1])+a[i],f[i][0]=f[i-1][1];
        for(int i=1;i<=n;++i){
            if(f[i][0]<=p)ans=max(ans,i-1);
            if(f[i][1]<=p)ans=max(ans,i);
        }
        // for(int i=1;i<=n;++i)cout << f[i][0] << " " << f[i][1] << endl;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

