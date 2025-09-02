# [ABC251E] Takahashi and Animals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc251/tasks/abc251_e

高橋君と $ N $ 匹の動物がいます。 $ N $ 匹の動物はそれぞれ動物 $ 1 $ 、動物 $ 2 $ 、$ \ldots $ 、動物 $ N $ と呼ばれます。

高橋君は下記の $ N $ 種類の行動をそれぞれ好きな回数だけ（ $ 0 $ 回でも良い）行います。

- $ A_1 $ 円払い、動物 $ 1 $ と動物 $ 2 $ に餌をあげる。
- $ A_2 $ 円払い、動物 $ 2 $ と動物 $ 3 $ に餌をあげる。
- $ A_3 $ 円払い、動物 $ 3 $ と動物 $ 4 $ に餌をあげる。
- $ \cdots $
- $ A_i $ 円払い、動物 $ i $ と動物 $ (i+1) $ に餌をあげる。
- $ \cdots $
- $ A_{N-2} $ 円払い、動物 $ (N-2) $ と動物 $ (N-1) $ に餌をあげる。
- $ A_{N-1} $ 円払い、動物 $ (N-1) $ と動物 $ N $ に餌をあげる。
- $ A_N $ 円払い、動物 $ N $ と動物 $ 1 $ に餌をあげる。

上記の $ N $ 種類目の行動では、「動物 $ N $ と動物 $ 1 $ に」餌をあげることに注意してください。

すべての動物にそれぞれ $ 1 $ 回以上餌をあげるまでにかかる費用の合計として考えられる最小値を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

高橋君が $ 1 $ 種類目、$ 3 $ 種類目、$ 4 $ 種類目の行動をそれぞれ $ 1 $ 回ずつ行うと、 動物 $ 1 $ に $ 1 $ 回、動物 $ 2 $ に $ 1 $ 回、動物 $ 3 $ に $ 1 $ 回、動物 $ 4 $ に $ 2 $ 回、動物 $ 5 $ に $ 1 $ 回餌をあげることになり、すべての動物にそれぞれ $ 1 $ 回以上餌をあげることができます。 このときにかかる費用の合計は $ A_1\ +\ A_3\ +\ A_4\ =\ 2\ +\ 3\ +\ 2\ =\ 7 $ 円であり、これが考えられる最小値です。

## 样例 #1

### 输入

```
5
2 5 3 2 5```

### 输出

```
7```

## 样例 #2

### 输入

```
20
29 27 79 27 30 4 93 89 44 88 70 75 96 3 78 39 97 12 53 62```

### 输出

```
426```

# 题解

## 作者：slzx2022YuYihan (赞：7)

[更好的阅读体验？](https://www.luogu.com.cn/blog/slzx2022YuYihan/solution-at-abc251-e)

# Solution

水一波黄题题解......

首先，一眼看破，是到环形dp题 ~~（如果你看不出, 我也无能为力）~~

## Step 1 : 设计状态

我们令 $dp[i][0/1]$ 表示当前第 $i$ 个宠物，$\mathbb{0}$ 表示不喂养，$\mathbb{1}$ 表示喂养。

## Step 2 : 状态转移

首先来看不喂养，也就意味这前一个必定喂养，因此：$dp[i][0]=dp[i-1][1]$.

再来看喂养， 那么前一个喂养或者不喂养都可以，然后加上花费 $a[i]$，因此：$dp[i][1]=\min(dp[i-1][0],dp[i-1][1])+a[i]$.

## Step 3 : 细节处理

因为是一个环，所以我们在读入的时候处理一下；$a[i]=a[i+n]$.

然后，我们做两次dp，第一次从 $\mathbb{1}$ 开始，第二次从  $\mathbb{n}$ 开始。每次开始之前做初始化，赋 $dp$ 数组一个很大的值（因为要求最小值），第一次将 $dp[1][1]=a[1]$，第二次将 $dp[n][1]=a[n]$。第一次循环从 $2\sim n$，第二次循环从 $n+1\sim 2n-1$。

记 $ans1$ 为第一次dp的 $\min(dp[n][0],dp[n][1])$，$ans2$ 为第二次 dp 的 $\min(dp[2n-1][0],dp[2n-1][1])$。最终答案 $ans=\min(ans1,ans2)$。

讲解的那么详细，相信代码能轻松写出。

------------
# Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);
#define int long long
#define space putchar(' ')
#define enter puts("")
using namespace std;
inline int read(){
    int s = 0, w = 0;char ch = getchar();
    while (!isdigit(ch))    w |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch & 15), ch = getchar();
    return w ? ~(s - 1) : s;
}
inline void write(int x){
    if (x < 0)  putchar('-'), x = ~(x - 1);
    if (x > 9)  write(x / 10);
    putchar(x % 10 ^ 48);
}
const int N = 3e5 + 5;
int n, a[N << 1], ans, ans1, ans2, dp[N << 1][2];
signed main(){
    //IOS
    n = read();
    for (int i = 1; i <= n; ++i)    a[i] = a[i + n] = read();
    memset(dp, 0x3f, sizeof(dp));
    dp[1][1] = a[1];
    for (int i = 2; i <= n; ++i)
        dp[i][0] = dp[i - 1][1], dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    ans1 = min(dp[n][0], dp[n][1]);
    memset(dp, 0x3f, sizeof(dp));
    dp[n][1] = a[n];
    for (int i = n + 1; i <= (n << 1) - 1; ++i)
        dp[i][0] = dp[i - 1][1], dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    ans2 = min(dp[(n << 1) - 1][0], dp[(n << 1) - 1][1]);
    ans = min(ans1, ans2);
    write(ans), enter;
    return 0;
}//rp++
```


------------
# My Blog


最后推荐一下我的博客，觉得不错可以点点赞……

[我的博客](https://www.luogu.com.cn/blog/slzx2022YuYihan/)


------------


---

## 作者：panhongxuanyyds (赞：2)

[[ABC251E] Takahashi and Animals](https://www.luogu.com.cn/problem/AT_abc251_e)

# Solution

首先，很容易看出是道环形 dp。

$dp[i][0/1]$ 表示喂食 $[1,i]$ 的动物，且是否花费$a[i]$喂食第 $i$ 和第 $i+1$ 只动物需要的最小花费。

状态转移方程：$dp[i][0] = dp[i - 1][1]$（因为这一格没有选，所以必须喂养上一只动物）

$dp[i][1] = \max \{ dp[i-1][0], dp[i - 1][1]\} + a[i]$

考虑如何破环。

可以分类讨论是否喂养$a_1$，如果喂养，答案就取 $\max \{dp[n][0], dp[n][1]\}$；如果不喂养，则答案只能取 $dp[n][1]$。

一种错误的思路是复制一个 $a$ 数组，做长度是 $2n$ 的 dp，最后对于每个长度为 $n$ 的区间，用类似前缀和的方法求它的答案，最后取最小值。错误的原因是区间开头的 dp 值和区间结尾的 dp 值所选择的方案不一定相同。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 300000 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
ll n, m, ans, a[maxn], dp[maxn][2], f[maxn][2];
int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    dp[1][0] = INF;
    dp[1][1] = a[1];
    for (ll i = 2; i <= n; ++i) {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    }
    ans = min(dp[n][0], dp[n][1]);
    dp[1][0] = 0;
    dp[1][1] = INF;
    for (ll i = 2; i <= n; ++i) {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    }
    ans = min(ans, dp[n][1]);
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：ZBH_123 (赞：1)

### 思路：动态规划
#### 1.设计状态&设置边界
本题是一道线性 DP，可以设计的状态是设 $dp_{i,0/1}$ 为喂食完前 $i$ 只动物，$A_i$ 选或不选的最小花费。由于题目给出的是一个环，所以考虑断环为链，即将 $A_{i+1}$ 设为 $A_i$。这样，我们就要做两次 DP，第一次从 $A_2$ 开始推，答案是 $\max(dp_{n,0},dp_{n,1})$；第二次从 $A_{n+1}$ 开始推，答案是 $\max(dp_{2 \times n-1,0},dp_{2 \times n-1,1})$。而两次递推的边界分别是 $dp_{1,1}=a_1$，$dp_{n,1}=a_n$。$dp_{1,0}$ 和 $dp_{n,0}$ 初始化成极大值就行了，因为后面没有 $A_i$ 能喂到它们。
#### 2.状态转移方程
对于 $A_i$ 不选的情况，$A_{i-1}$ 一定要选才能使第 $i$ 只动物被喂食。所以，我们可以推出下面这个状态转移方程：
$$dp_{i,0}=dp_{i-1,1}$$
对于 $A_i$ 要选的情况，$A_{i-1}$ 可选可不选，反正第 $i$ 只动物一定能被喂食。在这种情况下，我们推出了下面这个状态转移方程：
$$dp_{i,1}=\min(dp_{i-1,0},dp_{i-1,1})+A_i$$
### 总结经验
以上就是做本题的方法了，大家可能会发现，线性 DP 的状态一般都是前 $i$ 个物品达到什么条件能得到的最优解或方案数，比如背包问题、LIS 和 LCS。

附上本题的 AC code:
```cpp
#include<iostream>
using namespace std;
const int maxn=3e5;
int n,a[2*maxn+5];
long long dp[2*maxn+5][2],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	dp[1][0]=0x3f3f3f3f,dp[1][1]=a[1];
	for(int i=2;i<=n;i++){
		dp[i][0]=dp[i-1][1];
		dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a[i];
	}
	ans=min(dp[n][0],dp[n][1]);
	dp[n][0]=0x3f3f3f3f,dp[n][1]=a[n];
	for(int i=n+1;i<2*n;i++){
		dp[i][0]=dp[i-1][1];
		dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a[i];
	}
	ans=min(ans,min(dp[2*n-1][0],dp[2*n-1][1]));
	cout<<ans;
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：1)

下文中的下标从 $0$ 开始。

假设不是环形的，那么定义 $f[i][0/1]$ 表示喂食前 $i$ 只动物的最小花费，其中 $f[i][0]$ 表示没有花费 $a[i]$，$f[i][1]$ 表示花费 $a[i]$。

则有 $f[i][0] = f[i-1][1]$，$f[i][1] = \min(f[i-1][0], f[i-1][1]) + a[i]$。

回到原问题，分类讨论：
- 如果不花费 $a[n-1]$，那么初始 $f[0][0] = \infty$，$f[0][1] = a[0]$，答案为 $f[n-1][0]$。
- 如果花费 $a[n-1]$，那么初始 $f[0][0] = a[n-1]$，$f[0][1] = a[n-1]+a[0]$，答案为 $\min(f[n-2][0],f[n-2][1])$。

代码实现时 $f$ 可以压缩成两个变量。

AC 代码（Golang）：

```go
package main
import ("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n int
	Fscan(in, &n)
	a := make([]int, n)
	for i := range a {
		Fscan(in, &a[i])
	}

	notPay, pay := int(1e18), a[0]
	for _, v := range a[1:] {
		notPay, pay = pay, min(notPay, pay)+v
	}
	ans := notPay

	notPay, pay = a[n-1], a[n-1]+a[0]
	for _, v := range a[1 : n-1] {
		notPay, pay = pay, min(notPay, pay)+v
	}
	Println(min(ans, min(notPay, pay)))
}

func min(a, b int) int { if a > b { return b }; return a }
```

也可以合并成一个 for 循环：

```go
package main
import ("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, v int
	Fscan(in, &n, &v)
	np1, p1 := int(1e18), v
	np2, p2 := 0, v
	for ; n > 1; n-- {
		Fscan(in, &v)
		np1, p1 = p1, min(np1, p1)+v
		np2, p2 = p2, min(np2, p2)+v
	}
	Print(min(np1, p2))
}

func min(a, b int) int { if a > b { return b }; return a }
```


---

## 作者：_shine_ (赞：0)

定义 $f_{i,0/1}$ 为前 $i$ 个宠物，当前这个 $a_i$ 喂或不喂，所获得的最小价值。则可以推出 $f_{i,0}=f_{i-1,1},f_{i,1}=\min{f_{i-1,0},f_{i-1,1}}$。

但是可以发现，在环形的接口处，有处理的问题：$f_{1,0}$ 必须选择 $a_n$，所以这里要单独进行处理，改变状态函数，让 $f_{i,0/1}$ 表是 $a_1$ 要喂的情况下，当前 $a_i$ 喂或不喂，前 $i$ 个能获得的最小代价，$dp_{i,0/1}$ 同理，但 $a_1$ 不喂，$a_n$ 要喂。这样使得 $dp_{i,0}$ 必须选择喂 $a_n$，没有不选这个选项即可。

则，答案为 $f_{n,0},f_{n,1},dp_{n,0}$ 这几个选项中最小的一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e5+10;
int n,a[maxn];
int f[maxn][2];
int dp[maxn][2];
signed main(){
//	freopen("feed.in","r",stdin);
//	freopen("feed.out","w",stdout);
	memset(f,0x3f,sizeof(f));
	memset(dp,0x3f,sizeof(dp));
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> a[i];
	}
	f[1][0]=a[1];
	f[1][1]=a[1];
	for(int i=2;i<=n;++i){
		f[i][0]=f[i-1][1];
		f[i][1]=min(f[i-1][0],f[i-1][1])+a[i];
//		cout << f[i][0] << " " << f[i][1] << endl;
	}
	dp[1][0]=0;
	dp[1][1]=0;
	dp[2][0]=dp[2][1]=a[2];
	for(int i=3;i<n;++i){
		dp[i][0]=dp[i-1][1];
		dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a[i];
	}
	dp[n][1]=min(dp[n-1][0],dp[n-1][1])+a[n];
	cout << min(min(f[n][0],f[n][1]),dp[n][1]) << endl;
	return 0;
}

```


---

## 作者：mi_Y13c (赞：0)

### 算法分析

先对问题进行分析：

- 若想给动物 $1$ 喂食，操作 $1$ 和操作 $n$ 需至少选一个。

- 若想给动物 $2$ 喂食，操作 $1$ 和操作 $2$ 需至少选一个。

- $...$

- 若想给动物 $n$ 喂食，操作 $n-1$ 和操作 $n$ 需至少选一个。

定义 dp 状态：

$dp[i][0]$ 表示已对前 $i-1$ 个进行决策且不选第 $i$ 个的最小费用。

$dp[i][1]$ 表示已对前 $i-1$ 个进行决策且选第 $i$ 个的最小费用。

状态转移：

$dp[i][0]=dp[i-1][1]$，

$dp[i][1]=\min(dp[i-1][0],dp[i-1][1])+a_i$。

边界情况及问题答案：

- 若不进行操作 $1$，$dp[1][0]=\infty$，此时必须进行操作 $n$，故答案为 $dp[n][1]$。

- 若进行操作 $1$，$dp[1][1]=a_1,dp[1][0]=\infty$，此时答案为 $\min(dp[n][0],dp[n][1])$。

将以上两种情况的答案取最小值就是本题的答案。

### 最终代码

```

#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    const ll INF = 1e18;
    vector dp(n, vector<ll>(2));
    // 不选 1
    dp[0][0] = 0;
    dp[0][1] = INF;
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i-1][1];
        dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + a[i];

    }
    ll ans = dp[n-1][1];
    // 选 1 
    dp[0][1] = a[0];
    dp[0][0] = INF;
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i-1][1];
        dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + a[i];

    }
    ans = min(ans, min(dp[n-1][0], dp[n-1][1]));
    cout << ans << '\n';
    return 0;

}

```

---

## 作者：xiaoPanda (赞：0)

## ABC251E - Takahashi and Animals(*1227)

### Title
有 $N$ 个动物，第 $i$ 个饲料可以喂养第 $i$ 和第 $i+1$ 个动物，特别地，第 $N$ 个饲料可以喂养第 $1$ 和第 $N$ 个动物。第 $i$ 个饲料需要 $A_i$ 元，问喂完所有动物至少需要多少钱。

$2 \le N \le 3\times 10^5,1 \le A_i \le 1 \times 10^9$

### Solution
考虑 $dp$，设 $f[i][0/1]$ 表示第 $i$ 个饲料选或不选所得到的最小值。

分 $2$ 种情况讨论：如果第 $1$ 只动物用第 $1$ 个饲料喂，那么第 $N$ 个饲料可以选择喂或不喂，那么答案就为 $\min(f[n][0],f[n][1])$。如果第 $1$ 个动物用第 $N$ 个饲料喂，那么答案就为 $f[n][1]$。

对于每次的转移，如果前面的饲料不选，那么当前饲料就必须选，反之，则取最大值即可。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+100;
int a[N],f[N][2];
main()
{
	int n,ans=1e18;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	memset(f,127,sizeof f);
	f[1][1]=a[1];
	for(int i=2;i<=n;i++)
	{
		f[i][1]=min(f[i-1][1],f[i-1][0])+a[i];
		f[i][0]=f[i-1][1];
	}
	ans=min(ans,min(f[n][1],f[n][0]));
	memset(f,127,sizeof f);
	f[1][0]=0;
	for(int i=2;i<=n;i++)
	{
		f[i][1]=min(f[i-1][1],f[i-1][0])+a[i];
		f[i][0]=f[i-1][1];
	}
	ans=min(ans,f[n][1]);
	cout<<ans;
    
	return 0;
}
```

---

