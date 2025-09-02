# [ABC125D] Flipping Signs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc125/tasks/abc125_d

$ N $ 個の整数が並んでおり、順に $ A_1,\ A_2,\ ...,\ A_N $ です。

あなたはこの整数列に対して次の操作を好きなだけ行うことができます。

**操作**: $ 1\ \leq\ i\ \leq\ N-1 $ を満たす整数 $ i $ を選ぶ。$ A_i $ と $ A_{i+1} $ に $ -1 $ を乗算する。

操作終了後の整数列を $ B_1,\ B_2,\ ...,\ B_N $ とします。

$ B_1\ +\ B_2\ +\ ...\ +\ B_N $ の最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ -10^9\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

次のように操作を行うと、$ B_1\ =\ 10,\ B_2\ =\ 5,\ B_3\ =\ 4 $ になり、このときの $ B_1\ +\ B_2\ +\ B_3\ =\ 10\ +\ 5\ +\ 4\ =\ 19 $ が最大です。 - $ i $ として $ 1 $ を選ぶ。操作により、整数列は $ 10,\ -5,\ -4 $ に変化する。 - $ i $ として $ 2 $ を選ぶ。操作により、整数列は $ 10,\ 5,\ 4 $ に変化する。

### Sample Explanation 3

出力が $ 32 $ ビット整数型に収まらない場合があります。

## 样例 #1

### 输入

```
3
-10 5 -4```

### 输出

```
19```

## 样例 #2

### 输入

```
5
10 -4 -8 -11 3```

### 输出

```
30```

## 样例 #3

### 输入

```
11
-1000000000 1000000000 -1000000000 1000000000 -1000000000 0 1000000000 -1000000000 1000000000 -1000000000 1000000000```

### 输出

```
10000000000```

# 题解

## 作者：Nightingale_OI (赞：2)

### 大意

给你一个长度为 $ n $ 的序列 $ a $ ，让你执行任意次操作，每次可以将 $ a $ 数组中相邻两个数取相反数。

问你可以得到最大的最终数组的和是多少。

### 思路

由于是取相反数，所以每个位置有意义的操作只可能进行最多一次。

只需要用 $ dp_{i,0/1} $ 记录 $ i $ 位置是否被取过相反数的最大值即可。

时间复杂度 $ O(n) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int a[101010];
long long dp[101010][2];
int main(){
    cin>>n;
    f(i,1,n)scanf("%d",&a[i]);
    dp[1][0]=0;
    dp[1][1]=-1e15;
    f(i,2,n){
        dp[i][0]=max(dp[i-1][0]+a[i-1],dp[i-1][1]-a[i-1]);
        dp[i][1]=max(dp[i-1][0]-a[i-1],dp[i-1][1]+a[i-1]);
    }
    printf("%lld\n",max(dp[n][0]+a[n],dp[n][1]-a[n]));
    return 0;
}
```

---

## 作者：TLEWA (赞：1)

发现题解区清一色 dp，发个贪心。

## 简要题意

有一个长度为 $n$ 的数组，可以进行**无限次**操作，每次可以使第 $i$ 和第 $i+1$ 个数变成其相反数，求可能达到的最大值。

## 思路

我们首先定义两种操作：

1. 交换：当第 $i$ 个和第 $i+1$ 个元素有一个为负数时，我们就可以对他们进行操作，进而交换他们的正负.

1. 消除：当第 $i$ 个和第 $i+1$ 个元素均为负数时，我们可以对他们进行操作，进而消除两个负数。

可以发现，对于负数数量为偶数的数组，可以进行若干次交换和消除，然后将其全部变为正数，而对于负数数量为奇数的数组，则会剩下一个负数，我们贪心地通过若干次交换将其交换到绝对值最小的下标处即可。

代码如下：

```cpp
#include<iostream>
using namespace std;

int arr[100005],N,minn=1000000005,fu;
long long ans;

int main() {
	cin >> N;
	for(int i=0;i!=N;++i) {
		cin>>arr[i];
		minn=min(abs(arr[i]),minn);
		fu+=(arr[i]<0);
		ans+=abs(arr[i]);
	}
	if(fu%2)ans-=minn*2;
	cout<<ans<<endl;
	
	return 0;
}
```




---

## 作者：hxhhxh (赞：1)

## 题目大意

给定一个长度为 $ n $ 的整数序列 $ a $ ，每次可以选择连续的两个数并取相反数，求 $ \sum_{i=1}^n a_i $ 的最大值。

## 思路

对于除了第一个数的每一个数，考虑是否对它和前一个数进行操作。

如果不进行操作，那么:
$$ \sum_{j=1}^i a_j =\sum_{j=1}^{i-1}a_j+a_i $$

如果进行操作，那么:
$$ \sum_{j=1}^i a_j = \sum_{j=1}^{i-1} a_j + \begin{cases} -2\times a_{i-1}-a_i  & (\text{前一个数没有经过操作})\\ 2\times a_{i-1}-a_i & (\text{前一个数经过操作}) \end{cases} $$

考虑进行动态规划。
设 $ dp[i][1] $ 表示在进行操作的情况下 $ \sum_{j=1}^i a_j $ 的最大值。

$ dp[i][0] $ 表示在不进行操作的情况下 $ \sum_{j=1}^i a_j $ 的最大值。

## AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005],dp[100005][2];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	memset(dp,-0x3f,sizeof(dp));
	dp[1][0]=a[1];
	for(int i=2;i<=n;i++){
		dp[i][0]=max(dp[i-1][0],dp[i-1][1])+a[i];
		dp[i][1]=max(dp[i-1][0]-a[i-1]*2,dp[i-1][1]+a[i-1]*2)-a[i];
	}
	printf("%lld",max(dp[n][0],dp[n][1]));
	return 0;
}
```

---

## 作者：lkjzyd20 (赞：0)

# 简要题意
每次将相邻的两个数字都变成其各自的相反数，你可以操作无限次，问最终可得到的整个数列的最大的总和是多少。

# 思路

可以发现，如果负数数量为偶数，可以进行若干次交换，把负数移到一边，非负数移到另一边，我们会发现，负数会成对的两两消除，然后将其全部变为正数，如果负数数量为奇数，同样这么做，则会剩下一个负数，我们贪心地通过若干次交换将其交换到绝对值最小的下标处即可。

# 代码

```cpp

#include <bits/stdc++.h>

#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)

using namespace std;

int n;
int minn = LONG_LONG_MAX;
int idx;
int ans;

main()

{
    ios :: sync_with_stdio(0);
    cin.tie(); cout.tie();
    cin >> n;

    rep(i, 1, n)
    {
        int x;
        cin >> x;

        minn = min(minn, abs(x));
        
        if (x < 0)
            ++ idx;
        
        ans += abs(x);
    }

    if(idx % 2 == 1)
        cout << ans - minn * 2 << '\n' ;
    else
        cout << ans << '\n' ;

    return 0;
}

/*
3
-10 5 -4

19

5
10 -4 -8 -11 3

30

11
-1000000000 1000000000 -1000000000 1000000000 -1000000000 0 1000000000 -1000000000 1000000000 -1000000000 1000000000

10000000000
*/
```

---

## 作者：SpeedStar (赞：0)

#### 算法分析

注意到，对于 $i=x,x+1, \cdots,y-1$ 这些数执行该操作，最后只有 $A_x$ 和 $A_y$ 改变了符号。通过该操作，$A_i$ 会变成它的相反数。特别地，对于 $A_i = 0$ 而言，执行该操作对 $A_i$ 不会有影响。于是可以得到有偶数个负数或者存在 $A_i = 0$ 时，我们可以通过该操作把所有数变成非负数，否则经过该操作将会存在一个负数，此时我们不妨把 $min|A_i|$ 设为需要去掉的负数即可。


#### C++ 代码

```cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::vector;
using std::min;
using ll = long long;

const int INF = 1001001001;

int main() {
	int n;
	cin >> n;
	
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	
	ll ans = 0;
	int neg = 0;
	for (int i = 0; i < n; ++i) {
		ans += abs(a[i]);
		if (a[i] < 0) neg++;
	}
	
	if (neg % 2 == 1) {
		int minA = INF;
		for (int i = 0; i < n; ++i) minA = min(minA, abs(a[i]));
		ans -= minA * 2;
	}
	
	cout << ans << '\n';
	
	return 0;
}
```


---

