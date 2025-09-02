# [ABC222D] Between Two Arrays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc222/tasks/abc222_d

長さ $ n $ の数列 $ S\ =\ (s_1,\ s_2,\ \dots,\ s_n) $ がすべての $ i $ $ (1\ \leq\ i\ \leq\ n\ -\ 1) $ に対して $ s_i\ \leq\ s_{i+1} $ を満たすとき、かつそのときに限り「数列 $ S $ は広義単調増加である」と呼びます。

広義単調増加な長さ $ N $ の整数列 $ A\ =\ (a_1,\ a_2,\ \dots,\ a_N),\ B\ =\ (b_1,\ b_2,\ \dots,\ b_N) $ が与えられます。  
 このとき、次の条件を満たす広義単調増加な長さ $ N $ の整数列 $ C\ =\ (c_1,\ c_2,\ \dots,\ c_N) $ を考えます。

- すべての $ i $ $ (1\ \leq\ i\ \leq\ N) $ に対して $ a_i\ \leq\ c_i\ \leq\ b_i $ が成り立つ。

整数列 $ C $ としてあり得る数列の個数を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 0\ \leq\ a_i\ \leq\ b_i\ \leq\ 3000 $ $ (1\ \leq\ i\ \leq\ N) $
- 整数列 $ A,B $ は広義単調増加である。
- 入力はすべて整数である。

### Sample Explanation 1

$ C $ としてあり得る数列は次の $ 5 $ 個です。 - $ (1,\ 1) $ - $ (1,\ 2) $ - $ (1,\ 3) $ - $ (2,\ 2) $ - $ (2,\ 3) $ 数列 $ (2,\ 1) $ は広義単調増加でないため条件を満たさないことに注意してください。

### Sample Explanation 2

$ C $ としてあり得る数列は次の $ 1 $ 個です。 - $ (2,\ 2,\ 2) $

### Sample Explanation 3

個数を $ 998244353 $ で割ったあまりを求めることに注意してください。

## 样例 #1

### 输入

```
2
1 1
2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
3
2 2 2
2 2 2```

### 输出

```
1```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
1 4 9 16 25 36 49 64 81 100```

### 输出

```
978222082```

# 题解

## 作者：Dream_poetry (赞：5)

### 思路：
考虑 dp。

作 dp 数组 $f$，令 $f_{i,j}$ 来表示前 $i$ 个里面，最后一个数字小于等于 $j$ 的个数。

#### 动态转移方程：

由于 $f_{i,j}$ 必然包含着 $f_{i-1,j}$ 和 $f_{i,j-1}$，所以推得：

$if (j \le b_{i-1})$

$ f_{i,j}= f_{i,j-1}+f_{i-1,j}$

$ else $

$ f_{i,j}= f_{i,j-1}+f_{i-1,b_{j-1}}$

由此得出程序:
```cpp
f[i][j]=(f[i][j]+f[i][j-1]+f[i-1][min(j,b[i-1])])%mod;
```

最后的答案即为 $f_{n,b_n}$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3050,mod=998244353;
int a[maxn],b[maxn];
int f[maxn][maxn];
int n;
signed main(){	
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=a[1];i<=b[1];i++)
		f[1][i]=i-a[1]+1;
	for(int i=2;i<=n;i++){
		for(int j=a[i];j<=b[i];j++){
			f[i][j]=(f[i][j]+f[i][j-1]+f[i-1][min(j,b[i-1])])%mod;
		}
	}
	cout<<f[n][b[n]];
	return 0;
}
```


---

## 作者：MMXIandCCXXII (赞：3)

## 思路
这道题我们可以用 DP 解决，开一个二维数组，第一维记录选到了数组的第几个数，第二维记录这个数是啥。
状态如何转移？只需要和前一个数比较。在前一个数小于等于当前的数时，我们就要把这个数的情况算上，由于符合条件的是连续的一段，所以我们可以用前缀和优化。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 998244353;

int a[3010], b[3010], f[3010][3010], s[3010][3010];
vector <vector<char> > v;

signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = a[1]; i <= b[1]; i++)
	{
		f[1][i] = 1;
		s[1][i] = s[1][i-1] + 1;
	}
	for (int i = 2; i <= n; i++)
	{
		for (int j = a[i]; j <= b[i]; j++)
		{
			int x = min (j, b[i-1]);
			f[i][j] =(s[i-1][x] - s[i-1][a[i-1]-1]) % mod;
			s[i][j] = s[i][j-1] + f[i][j];
		}
	}
	int ans = 0;
	for (int i = a[n]; i <= b[n]; i++)
	{
		ans = (ans + f[n][i]) % mod;
	}
	cout << ans % mod << endl;
	return 0;
}
```

---

## 作者：CQ_Bab (赞：2)

# 思路
我们可以用后缀和来处理，那么我们就可以用两个数组来处理，用一个 $S_{i,j}$ 来后缀和然后用 $f_{i,j}$ 来处理答案（$S_{i,j}$ 为取到第 $i$ 项并且取的 $j$ 的方案数，$f_{i,j}$ 就位取到第 $i$ 项并且取的 $j$ 的总方案数，注意啊我们是从后面枚举的），所以我们就可以先将第 $n$ 位的数值求出来就有 $b_i-a_i$ 种，那么对于每一种后缀和都是 $1$。然后对于中间项，我们先要将 $S_{i,j}$ 赋值，那么 $j$ 是什么呢？因为不能比后面取的大，所以就为 $\max(j,a_{i+1})$，毕竟在同一项中越靠前的后缀和越大所以用 $a_{i+1}$。然后我们就用当前点的方案数加上 $f_{i,j+1}$（因为前面已经处理好了）即可。
# 代码
```
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y,k) for(int i=x;i<=y;i+=k)
#define rep1(i,x,y,k) for(int i=x;i>=y;i-=k)
#define IOS std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define int long long
#define fire signed
const int mod=998244353;
int n,a[3010],x[3010];
int f[3010][3010],s[3010][3010];
fire main() {
	IOS;
	cin>>n;
	rep(i,1,n,1) cin>>a[i];
	rep(i,1,n,1) cin>>x[i];
	rep1(i,x[n],a[n],1) {
		s[n][i]=1; //初始化
		f[n][i]=1+f[n][i+1]; 
	}
	rep1(i,n-1,1,1) {
		rep1(j,x[i],a[i],1) {
			s[i][j]=f[i+1][max(j,a[i+1])]%mod; //更新后缀和
			f[i][j]=(s[i][j]+f[i][j+1])%mod; //更新答案
		}
	}
	cout<<f[1][a[1]]%mod<<endl;
	return false;
}
```


---

## 作者：Mingrui_Yang (赞：2)

## 题意

给定两个单调不下降的序列 $a$，$b$，求单调不下降序列 $c$（序列 $c$ 需要满足 $a_i \le c_i \le b_i$）的数量。  
答案对 $998244353$ 取模。

## Solution

考虑 DP。

状态表示：令 $f_{i, j}$ 表示在序列 $c$ 的前 $i$ 个中且 $a_i \le c_i \le j$ 的数量。   
状态计算：显然，$f_{i, j}$ 一定包含 $f_{i, j - 1}$ 和 $f_{i - 1, j}$。所以转移方程如下（注意：$j$ 需要满足 $j \le b_{i - 1}$）：
$$
\begin{cases}
 f_{i, j} = f_{i, j - 1} + f_{i - 1, j} & \text{ if } j \le b_{i - 1} \\
 f_{i, j} = f_{i, j - 1} + f_{i - 1, b_{j - 1}} & \text{ if } j > b_{i - 1}
\end{cases}
$$

在递推之前先处理一下 $i = 1$ 的状态，即递推起点。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3010, Mod = 998244353;

int n;
int a[N], b[N];
int f[N][N]; // f[i][j]表示 在序列c的前i个中且a[i]<=c[i]<=j的数量

signed main() {
	// 输入 
	cin >> n; 
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	for (int i = 1; i <= n; i ++ ) cin >> b[i];
	
	for (int i = a[1]; i <= b[1]; i ++ ) f[1][i] = i - a[1] + 1; // 初始化递推起点 
	for (int i = 2; i <= n; i ++ )
		for (int j = a[i]; j <= b[i]; j ++ )
			f[i][j] = (f[i][j - 1] + f[i - 1][min(j, b[i - 1])]) % Mod; // 记得模 998244353 
	
	cout << f[n][b[n]] << endl; // 输出答案 
	
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：1)

# 思路
我们设 `dp[i][j]` 表示前 $i$ 个里面最后一个数字小于等于 $j$ 的个数。

可以推出转移方程为 `dp[i][j]+=dp[i-1][j]+dp[i-1][j-b[i]]` 表示可以不选第 $i$ 个或选第 $i$ 个，最后的答案就是 `dp[n][b[n]]`，当然这个还可以用滚动数组滚掉一维，但因为够了，所以就没有做优化。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3050,mod=998244353;
int a[maxn],b[maxn];
int dp[maxn][maxn];
signed main(){	
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=a[1];i<=b[1];i++)dp[1][i]=i-a[1]+1;
	for(int i=2;i<=n;i++){
		for(int j=a[i];j<=b[i];j++){
			dp[i][j]=(dp[i][j]+dp[i][j-1]+dp[i-1][min(j,b[i-1])])%mod;
		}
	}
	cout<<dp[n][b[n]];
	return 0;
}
```

---

## 作者：aimcf (赞：1)

设 $f_{i,j}$ 表示现在选 $1\sim i$ 个数，第 $i$ 个数值为 $j$ 的方案数。

容易发现 $f_{i,j}$ 可以由所有满足条件的 $f_{i-1,k}$ 进行转移，也就是 $f_{i,j} = \sum_{i=a_{i-1}}^j f_{i-1,k}\bmod 998244353$。

然而时间复杂度是 $O(n^3)$ 的，会超时。

容易发现 $f$ 值更新时求的是一段连续区间的和，那么可以用前缀和维护。时间复杂度 $O(n^2)$。

可以滚动一维状态。

[Code（大号的）](https://atcoder.jp/contests/abc222/submissions/35980739)

---

## 作者：ZBH_123 (赞：1)

## 思路分析
本题是一道 DP。关于做法，我们可以设 $dp_{i,j}$ 为 $c$ 的前 $i$ 项中，最后一项不超过 $j$ 的序列数量。很明显，$a_i \le j \le b_i$。在推状态转移方程时，我们需要分情况讨论。分的情况就是 $j$ 是否小于等于 $b_{i-1}$。

先讨论 $j \le b_{i-1}$ 的情况。对于这种情况，$c_i$ 可以是 $j$，也可以不是 $j$。是 $j$ 的情况下，前 $i-1$ 项的最后一项的最大值为 $j$，序列数量为 $dp_{i-1,j}$；不是 $j$ 的情况下，第 $i$ 项的最大值为 $j-1$，序列数量为 $dp_{i,j-1}$。因此，这种情况下的序列数量为 $dp_{i-1,j}+dp_{i,j-1}$。

接着再来讨论 $j \gt b_{i-1}$ 的情况。$c_i$ 不是 $j$ 的情况的序列数量也是 $dp_{i,j-1}$；而 $c_i$ 是 $j$ 的情况下，由于 $j \gt b_{i-1}$，所以序列数量为 $dp_{i-1,b_{i-1}}$。因此，这种情况下的序列数量为 $dp_{i-1,b_{i-1}}+dp_{i,j-1}$。

综上所述，这个程序的状态转移方程就是：
$$dp_{i,j}=\begin{cases} dp_{i-1,j}+dp_{i,j-1} & j \le b_{i-1} \\ dp_{i-1,b_{i-1}}+dp_{i,j-1} & j \gt b_{i-1} \end{cases}$$
## 代码实现
对于边界条件，自然就有：
$$dp_{1,i}=i-a_1+1$$
其中，$i \in \{a_1 \sim b_1\}$。答案自然就是 $dp_{n,b_n}$。

**附上代码：**
```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define ll long long
const int mod=998244353;
int n,a[3005],b[3005];
ll dp[3005][3005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=a[1];i<=b[1];i++){
		dp[1][i]=i-a[1]+1;
	}
	for(int i=2;i<=n;i++){
		for(int j=a[i];j<=b[i];j++){
			if(j<=b[i-1]){
				dp[i][j]=(dp[i-1][j]+dp[i][j-1])%mod;
			}
			else{
				dp[i][j]=(dp[i][j-1]+dp[i-1][b[i-1]])%mod;
			}
		}
	}
	cout<<dp[n][b[n]];
	return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 思路：
由于题目中的序列是单调不递增，且 $a_{i} \le c_{i} \le b_{i}$，我们可以用动态规划来做。$dp_{i,j}$ 表示前 $i$ 个数中，最后一项小于 $j$ 的情况数量，其中 $dp_{i,j}$ 一定包含了 $dp_{i,j-1}$ 和 $dp_{i-1,j}$ 的情况，且要判断一下 $j$ 和 $b_{i-1}$ 那个更小一些，防止越界。所以我们可得状态转移方程为 $dp_{i,j} = dp_{i-1,j} + dp_{i,\min(j-1,b_{i-1})}$。记得要进行取模。

我们最后得到的答案为 $dp_{n,b_{n}}$。

# code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3010,p=998244353;
int a[N],b[N];
int dp[N][N];
int n;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=a[1];i<=b[i];i++){
		dp[1][i]=i-a[1]+1;
	}
	for(int i=2;i<=n;i++){
		for(int j=a[i];j<=b[i];j++){
			dp[i][j]=(dp[i][j-1]+dp[i-1][min(b[i-1],j)])%p;
		}
	}
	cout<<dp[n][b[n]];
	return 0;
}

```

---

## 作者：lzyqwq (赞：0)

值域很小，可以用作状态。设 $f_{i,j}$ 为前 $i$ 个数且第 $i$ 个数为 $j$ 的方案数，那么前 $i-1$ 个数可以取 $0\sim j$，因为单调不下降。所以 $f_{i,j}=\sum\limits_{k=0}^j f_{i-1,k}$，这个前缀和做即可。注意由于有 $a$ 和 $b$ 的限制，所以 $j\in[a_i,b_i]$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 5005
#define mod 998244353
int a[N],b[N],s[N],f[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
	}
	for(int i=a[1];i<=b[1];i++)//只有这么多合法的
	{
		f[i]=1;
	}
	for(int i=2;i<=n;i++)
	{
		s[0]=f[0];
		for(int j=1;j<=3000;j++)//此时s即为f[i-1][0~j]的前缀和
		{
			s[j]=s[j-1]+f[j];
			s[j]%=mod;
		}
		for(int j=0;j<=3000;j++)//初始化，一开始所有的状态都无方案，合法的状态会被转移，不合法的状态这样就可以做到无方案
		{
			f[j]=0;
		}
		for(int j=a[i];j<=b[i];j++)//a[i]<=b[i]，所以这样枚举就行
		{
			f[j]=s[j];
			f[j]%=mod;
		}
	}
	int ans=0;
	for(int i=0;i<=3000;i++)
	{
		ans+=f[i];
		ans%=mod;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

