# [JOI 2016 Final] 橙子装箱 / Oranges

## 题目描述

CXR 决定将收获的 $n$ 个橙子分装进一些箱子内。在 NXY 的工厂中，橙子排列在输送带上，依次编号为 $1\dots n$。橙子 $i(1\leq i\leq n)$ 的大小为 $A_i$。由于分拣不方便，同一个箱子内，橙子的编号必须连续。

一个箱子内最多可以装 $m$ 个橙子。在一个箱子内装一些橙子的成本为 $k+s\times (a-b)$。$k$ 是箱子本身的成本，所有箱子的成本一样。$s$ 是该箱子中橙子的数目。 $a$ 是该箱子中最大橙子的大小，$b$ 是该箱子中最小橙子的大小。

求包装这 $n$ 个橙子所需的最小成本。

## 说明/提示

【数据范围与约定】

- $1\le N\le 2\times 10^4$。
- $1\le M\le 10^3$。
- $0\le K\le 10^9$。
- $1\le A_i\le 10^9 (1\le i\le N)$。
- $M\le N$。

1. Subtask $1$（$20$ pts）：$N\le 20$。
2. Subtask $2$（$50$ pts）：$N \le 2000,M \le 100$。
3. Subtask $3$（$30$ pts）：无特殊限制。

## 样例 #1

### 输入

```
6 3 6
1
2
3
1
2
1```

### 输出

```
21```

## 样例 #2

### 输入

```
16 4 12
3
10
13
10
19
9
12
16
11
2
19
9
13
2
13
19```

### 输出

```
164```

## 样例 #3

### 输入

```
16 6 14
19
7
2
15
17
7
14
12
3
14
5
10
17
20
19
12```

### 输出

```
177```

## 样例 #4

### 输入

```
10 1 1000000000
1
1
1
1
1
1
1
1
1
1```

### 输出

```
10000000000```

# 题解

## 作者：dashabi35 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P11793)

## Thinking
这道题显然是一道 dp 题。原因：当前的值和前面的有关联且无后效性（废话）。

那么 $dp[i]$ 就可以通过另一个更小的下标 $j$ 来判定。

如下：

条件：$j$ 初始为 $i$ 只到 $j<1$ 或 $i-j+1>m$ 此时结束。


$$dp[i]=\min(dp[i],dp[j-1]+k+(mmax-mmin)\times(i-j+1))$$


$mmax$ 为 $i$ 到 $j$ 中的最大值，$mmin$ 为 $i$ 到 $j$ 中的最小值，可用两个变量 $mmax$ 和 $mmin$ 每次进行遍历（便利是顺便的，不会太占用时间复杂度）。

$i-j+1$ 即为当前的数量。

## Code

这是我的第一篇题解，我希望它更加完美，经过优化，可以达到 27ms（看电脑配置）。

```cpp
#include<stdio.h> //比用万能头快 
using namespace std;
long long n,m,k;
long long a[20005],dp[20005];
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k); //比 cin 快 
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
		long long biggest=a[i];
		long long smallest=a[i]; 
		dp[i]=2e14;
		for(int j=i;j>=1&&i-j+1<=m;j--)
		{
			if(biggest<a[j]) biggest=a[j]; //比直接调 max 快很多 
			if(smallest>a[j]) smallest=a[j]; //比直接调 min 快很多 
			long long addition=k+(i-j+1)*(biggest-smallest);
			if(dp[j-1]+addition<dp[i]) dp[i]=dp[j-1]+addition; //状态转移 
		}
	}
	printf("%lld",dp[n]); //比 cout 快 
	return 0;
}
```
[AC记录 28ms](https://www.luogu.com.cn/record/211564685)

---

## 作者：封禁用户 (赞：4)

#### 题目分析
有 $n$ 个橙子排成一排，每个橙子的大小为 $A_i$。需要将它们装进若干个箱子里，每个箱子必须装连续的橙子，且最多装 $m$ 个。每个箱子的成本为 $k + (\text{箱子内橙子个数}) \times (\text{最大橙子大小} - \text{最小橙子大小})$。目标是最小化总成本。

#### 解题思路
使用动态规划（DP）求解：
设 $dp[i]$ 表示装好前 $i$ 个橙子的最小总成本。对于每个 $i$（$1 \le i \le n$），枚举最后一个箱子的起始位置 $j$（$j$ 满足 $i - m \le j < i$），最后一个箱子装橙子 $[j+1, i]$。转移方程为：

$$
dp[i] = \min_{j=\max(0, i-m)}^{i-1} \left( dp[j] + \text{cost}(j+1, i) \right)
$$

  其中 $\text{cost}(j+1, i) = k + (i - j) \times (\max_{t=j+1}^{i} A_t - \min_{t=j+1}^{i} A_t)$。
- **初始状态**：$dp[0] = 0$（没有橙子时成本为 0）。
- **边界处理**：当 $j < 0$ 时跳过。

在实现时，内层循环从 $i-1$ 反向枚举到 $i-m$，同时动态维护区间 $[j+1, i]$ 的最小值和最大值。
#### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    
    vector<long long> dp(n + 1, LLONG_MAX);
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        int min_val = A[i];
        int max_val = A[i];
        for (int j = i - 1; j >= max(0, i - m); j--) {
            if (A[j + 1] < min_val) min_val = A[j + 1];
            if (A[j + 1] > max_val) max_val = A[j + 1];
            long long cost = k + 1LL * (i - j) * (max_val - min_val);
            if (dp[j] != LLONG_MAX) {
                if (dp[j] + cost < dp[i]) {
                    dp[i] = dp[j] + cost;
                }
            }
        }
    }
    
    cout << dp[n] << endl;
    return 0;
}
```

---

## 作者：Oldxu114514 (赞：2)

**我们不需要使用单调队列等进行优化**

这题属于一个划分型动态规划的一道题，我们先看看题目中的关键信息：

1. 橙子的编号必须连续

2. 在一个箱子内装一些橙子的成本为 $k+s\times(a−b)$

3.  $a$ 是该箱子中最大橙子的大小，$b$ 是该箱子中最小橙子的大小。

可见我们可以令 $$dp_i$$ 为前 i 个数的装箱代价，枚举 j 为划分线，那么我们就可以把 $$dp_i$$ 分为两个子任务： $$dp_j$$ 与 $$k+(i-j)\times(a-b)$$ （通过题目给出的代价计算公式可得）

由此，我们可以推得状态转移方程：

$$dp_i=\min(dp_i,dp_j+k+(i-j)\times(a-b))$$

其中， $a$ 和 $b$ 则分别表示最大的橙子的大小与最小的橙子的大小，那么我们可以设置 $a$ 与 $b$ 两个变量来统计最小值，在推导的过程中，边推导边更新 $a$ 与 $b$ 的值。

这样，这道题就结束了。代码中有详细注释，蒟蒻第一次写题解，给个点赞行不行呢~


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,x;
int c[200005];
int dp[200005];
signed main(){
	// 定义 dp i 为前i个数的代价
	// 可以枚举j，以j为划分线，dp j为一个子任务，剩下的i-j为一个子任务
	// 易得状态转移方程dp i=max(dp i,dp j+k*(i-j)*(a-b))，由题易得
	// 最后的dp n即为答案 
	memset(dp,0x3f,sizeof(dp)); 
	cin>>n>>m>>k;
	dp[0]=0;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		int a=c[i];
		int b=c[i];
		// a为最大的橙子的大小，b为最小的橙子的大小 
		for(int j=i-1;j>=max(0ll,i-m);j--)//防止下标为负的越界 
		{
			dp[i]=min(dp[i],dp[j]+k+(i-j)*(a-b));
			a=max(a,c[j]);
			b=min(b,c[j]);
		}
		
	}
	cout<<dp[n]<<endl;
	return 0;
}

```

十年 OI 一场空，不开 LL 见祖宗

---

## 作者：lemoned_qwq (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11793)
# 题解：P11793
## 思路：动态规划&单调队列

动态规划状态定义：使用 $dp$ 数组来记录子问题的解，其中 $dp[i]$ 表示包装前 $i$ 个橙子所需的最小成本。

初始化：将 $dp[0]$ 初始化为 $0$ 。

状态转移：对于每个 $i$ ，尝试将不同数量的橙子放入一个新箱子。在每次尝试时，使用两个队列：单调队列 $maxQueue$ 以及单调队列 $minQueue$ 分别维护当前箱子内橙子大小的最大值和最小值，这样可以在 $O(1)$ 的时间复杂度内获取当前箱子内橙子大小的最值。通过计算将当前区间的橙子放入新箱子的成本，并结合之前 $dp$ 数组记录的结果，更新 $dp[i]$ 为最小成本。

## 代码：
```cpp
#include <iostream>
#include <vector>
#include <climits>
#include <deque>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    vector<long long> dp(n + 1, LLONG_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        deque<int> maxQueue, minQueue;
        for (int j = i - 1; j >= 0 && i - j <= m; --j) {
            // 维护最大值队列
            while (!maxQueue.empty() && A[maxQueue.back()] <= A[j]) {
                maxQueue.pop_back();
            }
            maxQueue.push_back(j);

            // 维护最小值队列
            while (!minQueue.empty() && A[minQueue.back()] >= A[j]) {
                minQueue.pop_back();
            }
            minQueue.push_back(j);

            // 移除超出当前区间的元素
            if (maxQueue.front() < j) {
                maxQueue.pop_front();
            }
            if (minQueue.front() < j) {
                minQueue.pop_front();
            }

            int maxSize = A[maxQueue.front()];
            int minSize = A[minQueue.front()];
            int s = i - j;
            long long cost = (long long)k + (long long)s * (maxSize - minSize);
            dp[i] = min(dp[i], dp[j] + cost);
        }
    }

    cout << dp[n] << endl;

    return 0;
}    
```

---

## 作者：lilong (赞：2)

注意到 $N \times M \le 2\times 10^7$，因此不难得到一个 dp 做法。设 $f_i$ 表示把前 $i$ 个橙子装进箱子内的最小成本，则不难得到以下转移式：

$$f_i=\min_{i-j\le m,0 \le j < i} f_j+k+ ( i - j ) \times ( \max_{j < k \le i} a_k - \min_{j < k \le i} a_k ) $$

同时注意到最大最小值可以在倒着枚举 $j$ 的时候顺便求出来，因此也容易做到时间复杂度 $O(NM)$。


```cpp
#include <iostream>
#include <cstdio>
#define ll long long
#define N 200010

using namespace std;

int n,m,k;
ll f[N],a[N],mx,mi;

int main()
{
	cin >> n >> m >> k;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i];
	for( int i = 1 ; i <= n ; i ++ )
	{
		f[i] = f[i - 1] + k;
		mx = mi = a[i];
		for( int j = i - 1 ; j >= max( i - m , 0 ) ; j -- )
		{
			f[i] = min( f[i] , f[j] + k + ( i - j ) * ( mx - mi ) );
			mx = max( mx , a[j] ),mi = min( mi , a[j] );
		}
		// cout << f[i] << endl;
	}
	cout << f[n];
	return 0;
}
```

---

## 作者：xqdrsn (赞：1)

[橙子装箱](https://www.luogu.com.cn/problem/P11793)这道题第一眼就察觉是动规，而且是背包问题的变形。

## 1.定类型

我们先看一下数据范围。

![](https://cdn.luogu.com.cn/upload/image_hosting/4wpxkjy0.png)

我们假设 $N$ 和 $A_i$ 都为最大，求得为 $2\times10^{13}$ 已经超过 `int`的范围，所以该使用 `long long`。

## 2.初始化

由于数组的类型为长整数类型，且题目求的是最小成本，所以 $dp$ 数组初始化为 $10^{18}$。

## 3.状态与转移
我们需要将橙子分成若干段（每段对应一个箱子），每段代价为：
- 箱子成本 $ k $ + 区间长度 $ \times $ 极差（最大值减最小值）。

状态转移方程：
$$ dp_i = \min_{1 \leq j \leq \min(i,m)} \left( dp_{i-j} + j \cdot (\max_{[i-j+1,i]} - \min_{[i-j+1,i]}) + k \right) $$

其中：
- $ \max_{[i-j+1,i]} $ 和 $ \min_{[i-j+1,i]} $ 可通过预处理区间最值计算（见代码）。

## AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,k;
ll a[20005];
ll dp[20005];
ll minn[20005];
ll maxn[20005];
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i]=minn[i]=1e18;
	}
	for(ll i=1;i<=n;i++){
		minn[i]=maxn[i]=a[i];
		for(ll j=i-1;j>=max(1ll,i-m+1);j--){
			minn[j]=min(minn[j+1],a[j]);
			maxn[j]=max(maxn[j+1],a[j]);
		}
		for(ll j=1;j<=min(i,m);j++){
			dp[i]=min(dp[i],dp[i-j]+j*(maxn[i-j+1]-minn[i-j+1])+k);
		}
	}
	cout<<dp[n];
	return 0;
} 
```
[AC记录](https://www.luogu.com.cn/record/226626036)

---

## 作者：liuzhuoran141516 (赞：1)

# 题解：P11793 [JOI 2016 Final] 橙子装箱 / Oranges
## 思路
看到有最优解，先想：贪心、暴搜加优化、动规。  
很显然本题~~我认为~~并没有贪心的做法，搜索复杂度太高，所以考虑动规。

我们定义 $\text{dp[i]}$ 为前 $i$ 个橙子的最小成本。对于第 $i$ 个橙子，我们需要考虑所有可能的箱子长度 $\text{len}$（从 $1$ 到 $m$），然后计算将最后一个箱子包含 $\text{len}$ 个橙子的成本。

对于每个可能的箱子长度 $\text{len}$，我们维护当前区间内的最大值和最小值，方便快速计算该区间的成本，并使用滑动窗口优化。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k, a[20005], dp[20005];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= 20004; ++i) {
    	dp[i] = 9223372036854775807;
	}
    for (int i = 1; i <= n; ++i) {
        int maxn = a[i], minn = a[i], pre = i - 1;
        if (pre >= 0) {
            int c = k + maxn - minn;
            if (dp[pre] + c < dp[i]) {
                dp[i] = dp[pre] + c;
            }
        }
        for (int l = 2; l <= m; ++l) {
            int srt = i - l + 1;
            if (srt < 1) break;
            maxn = max(maxn, a[srt]);
            minn = min(minn, a[srt]);
            pre = srt - 1;
            if (pre < 0) continue;
            int c = k + l * (maxn - minn);
            if (dp[pre] + c < dp[i]) {
                dp[i] = dp[pre] + c;
            }
        }
    }
    cout << dp[n];
    return 0;
}
```

---

## 作者：da_ke (赞：1)

## Solution

一看就知道是 DP 题。

每次依次装一个区间，设当前装到了第 $i$ 个，最小花费 $dp(i)$。

枚举区间的起点 $j$，便可以得到当前最后一次装的区间 $[i,j]$。计算最大值最小值，按照题目描述进行转移。

维护最大值最小值并不需要重新算一遍，只需要在枚举 $j$ 的过程中打擂台，这样时间就是 $O(NM)$ 的了。

[提交记录](https://vjudge.net/solution/59317812)

```cpp
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int N,M; ll K;
    cin>>N>>M>>K;
    vector<ll> A(N+1,0);
    rep(i,1,N) cin>>A[i];
    vector<ll> dp(N+1,1ll<<60);
    dp[0]=0,dp[1]=K;
    rep(i,2,N)
    {
        ll _max=A[i],_min=A[i];
        fdn(j,i,max(i-M+1,1))
        {   
            _max=max(_max,A[j]),_min=min(_min,A[j]);
            dp[i]=min(dp[i],dp[j-1]+K+(i-j+1)*(_max-_min));
        }
    }
    cout<<dp[N]<<endl;
}

// 路虽远行则将至，事虽难做则必成。
```

---

## 作者：Alice2012 (赞：1)

简单 DP 题。

考虑设 $f_i$ 表示将前 $i$ 个橙子分装完毕的最小代价。那么有转移 $f_i=\min_{j=\max(0,i-m)}^{i-1} f_j+K+(i-j)\times(\max_{k=j+1}^i a_k-\min_{k=j+1}^i a_k)$。表示将 $j+1\sim i$ 的橙子分装至新的一个箱子里。

但是这样会超时，考虑优化 $\max_{k=j+1}^i a_k-\min_{k=j+1}^i a_k$ 这个式子。发现这个东西可以用 ST 表预处理出来，转移的时候直接 ST 表 $\mathcal{O(1)}$ 查询即可。于是总的复杂度从 $\mathcal{O(nm^2)}$ 转化为 $\mathcal{O(nm)}$，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e4+5;
int n,m,k,a[N],lg[N];
int dp[N][20][2],f[N];
int qy(int l,int r,int op){//ST查询区间max,min 
	int p=lg[r-l+1];
	if(op==0)return max(dp[l][p][op],dp[r-(1<<p)+1][p][op]);
	else return min(dp[l][p][op],dp[r-(1<<p)+1][p][op]);
}
signed main(){
	cin>>n>>m>>k,lg[0]=-1;
	for(int i=1;i<=n;i++)cin>>a[i],lg[i]=lg[i/2]+1,dp[i][0][0]=dp[i][0][1]=a[i];	
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			dp[i][j][0]=max(dp[i][j-1][0],dp[i+(1<<j-1)][j-1][0]),
			dp[i][j][1]=min(dp[i][j-1][1],dp[i+(1<<j-1)][j-1][1]);//ST表预处理区间max,min 
	memset(f,0x3f,sizeof(f));
	f[0]=0;//初始化 
	for(int i=1;i<=n;i++)
		for(int j=max(0ll,i-m);j<i;j++)//表示前面的箱子分装完了1-j个橙子,现在分装j+1~i个橙子,注意有一个箱子最多分装m个的限制 
			f[i]=min(f[i],f[j]+k+(i-j)*(qy(j+1,i,0)-qy(j+1,i,1)));//计算贡献并取最值 
	cout<<f[n]; 
	return 0;
}
```

---

## 作者：Manchester_City_FC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11793)

### 题目大意
CXR 决定将收获的 $n$ 个橙子分装进一些箱子内。在 NXY 的工厂中，橙子排列在输送带上，依次编号为 $1\dots n$。橙子 $i(1\leq i\leq n)$ 的大小为 $A_i$。由于分拣不方便，同一个箱子内，橙子的编号必须连续。

一个箱子内最多可以装 $m$ 个橙子。在一个箱子内装一些橙子的成本为 $k+s\times (a-b)$。$k$ 是箱子本身的成本，所有箱子的成本一样。$s$ 是该箱子中橙子的数目。 $a$ 是该箱子中最大橙子的大小，$b$ 是该箱子中最小橙子的大小。

求包装这 $n$ 个橙子所需的最小成本。

### 解题思路
考虑进行 dp。

定义 $dp_i$ 表示前 $i$ 个橙子装箱的最小成本，初始状态 $dp_0=0$。

考虑将最后一个箱子中装的橙子数量设为 $s$ 且这个箱子装的位置为 $[j+1,i]$（其中 $j=i-s$）。那么该箱子的装箱成本为 $k+s\times(a-b)$，其中 $a$ 为该箱子中的最大橙子大小，$b$ 为最小橙子大小。
状态转移方程为：
$$dp_i=\min_{1\le s\le \min(m,i)} \times dp_{i-s}+t \times (i-s+1,i)$$

如何快速算出 $t$：

由于区间内的大小差在动态规划转移中需要在内层循环中计算，我们可以在枚举箱中橙子的数量时反向遍历，一边更新当前区间的最小值 $p$ 和最大值 $q$，这样可以在 $O(1)$ 的时间内得到区间 $[j+1,i]$ 对应的最小和最大值，成本计算为：
$$
t=k+(i-j) \times (q-p)
$$

时间复杂度为 $O(nm)$，可以通过此题。

### AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e4+1,inf=LLONG_MAX;
int n,m,k,a[N],dp[N],p,q,t;
signed main(){
	cin>>n>>m>>k;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		p=a[i-1],q=a[i-1];
		dp[i]=inf;
		for(int j=i-1;j>=0&&i-j<=m;j--){
			p=min(p,a[j]),q=max(q,a[j]);
			t=k+1ll*(i-j)*(q-p);
			if(dp[j]+t<dp[i]) dp[i]=dp[j]+t;
		}
	}
	cout<<dp[n];
}
```

---

