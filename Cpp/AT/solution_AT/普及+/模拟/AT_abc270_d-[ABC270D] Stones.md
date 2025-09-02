# [ABC270D] Stones

## 题目描述

#### 题目翻译
Takahashi 和 Aoki 在玩一个取石子的游戏。

刚开始，有 $N$ 个石子，还有一个长度为 $K$ 的序列 $A = \{A_1,A_2,\cdots,A_K\}$。

现在，他们要按照以下规则轮流取石子：

* 对于每次操作，他可以选择一个 $i$（$1 \leq i \leq K$），这时他会取走 $A_i$ 块石子。

* 当一个人没法取石子时，游戏结束。

现在，Takahashi 先取石子，Aoki 后取石子。
他们都想尽可能的最大化他们自己取走的石子数量。

若他们都以最优策略取石子，最后 Takahashi 会取走多少块石子？

## 说明/提示

对于 $100\%$ 的数据，保证：
* $1 \leq N \leq 10^4$
* $1 \leq K \leq 100$
* $1 = A_1 < A_2 < \cdots < A_K \leq N$

## 样例 #1

### 输入

```
10 2
1 4```

### 输出

```
5```

## 样例 #2

### 输入

```
11 4
1 2 3 6```

### 输出

```
8```

## 样例 #3

### 输入

```
10000 10
1 2 4 8 16 32 64 128 256 512```

### 输出

```
5136```

# 题解

## 作者：lottle1212 (赞：15)

# [[ABC270D] Stones](https://www.luogu.com.cn/problem/AT_abc270_d) 题解

## 前言

作者原先在做这道题时，一直不理解**贪心**为什么错，且别的题解里没有详细说明。本篇题解主要对这一部分作一个补充。

## 题目大意

- 有 $N(1 \leq N \leq 10 ^ 4)$ 块石子，每次可以从中取 $ A_i (1 = A_1 < A_2 < \dots < A_K \leq N) $ 块石子。
- 有两个人以**最优策略**（最大化自己取的石子数量）取石子，求先手取走的石子数量。

## 解题思路

容易想到 $\text{DP}$。

设 $dp_i$ 表示当前石子数量为 $i$ 时，先手最多可以取的石子数量。

转移时类似**背包**的思想，枚举所有可取的石子数量 $a_k$，则前一次取时的先手最多取 $dp_{i - a_k}$ 块石子，易得 $dp_i = \max \{i - dp_{i - a_k}\}$。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, a[10010], dp[10010];
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= k; ++ i) cin >> a[i];
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= k; ++ j) {
			if (i < a[j]) break;
			dp[i] = max(dp[i], i - dp[i - a[j]]);
		}
	printf("%d\n", dp[n]);
	return 0;
}
```

再来说下**贪心**为什么不行。

我们可以把这个问题想成为什么**背包**不能用**贪心**实现。

比如在**完全背包**中，有读入样例如（数据格式与题目相同）：

```
12 4
1 3 4 5
```

**贪心**求得答案为 $5 + 5 + 1 = 11$，而**背包**答案可以是 $4 + 4 + 4 = 12$（不唯一）。**贪心**就错在取完后有剩余。

在本题中，这个样例用**贪心**答案为 $5 + 1 = 6$，即先手先取 $5$，后手取 $5$，先手再取 $1$。

但实际上，先手可以先取 $4$，后手取 $5$，先手再取 $3$。此时，答案为 $4 + 3 = 7$。而 $7 > 6$。

因此，此题无法用**贪心**实现。

---

## 作者：DengDuck (赞：8)

设 $f_i$ 表示还剩 $i$ 个石头时，先手能获得的最多石头数。

那么假设这次我们选择了 $a_j$ 个石头，对方变为先手，接下来对方最多获得 $f_{i-a_j}$ 石头，其他都是我们的，也就是 $(i-a_j-f_{i-a_j})$。

简单化简一下得：

$$
f_i=i-f_{i-a_j}
$$

利用这个式子，我们就可以在 $O(nk)$ 的时间复杂度下求解了。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, a[10005], f[10005];
int main() {
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (i < a[j])
                break;
            f[i] = max(f[i], i - f[i - a[j]]);
        }
    }
    cout << f[n] << endl;
}
```

---

## 作者：Zhao_daodao (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc270_d)
# 题目描述
存在 $n$ 块石头，`Takahashi` 和 `Aoki` 两人轮流取，`Takahashi` 先手。

给出一个长度为 $k$ 的序列 $s$，元素为 $s_{1},\cdots,s_{k}$。

每次选择一个数 $i,i\in \left[1,k\right]$，并取出 $s_{i}$ 个石头。无法再取时游戏结束。

求 `Takahashi` 最多能得到多少石头。
# 题目分析
考虑 `dp`。
### 状态
$dp_{i}$ 为当前石子数量为 $i$ 时，先手最多能取多少石子。
### 转移方程
如果现在先手拿的是 $a_{k}$。则后手能将剩下的 $dp_{i-a_{k}}$ 拿了。相当于先手只拿了 $i-dp_{i-a_{k}}$。

方程：$dp_{i}=\max{dp_{i-a_{k}}},k\in\left[1,n\right]$。
### 答案
`ans` 即为 $dp_{k}$。
### 时间复杂度
时间复杂度为 $O(nk)$，不会超时。
# 参考代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=1e4+1;
int f[N],n,a[N],k;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>k>>n;
	for(R i=1; i<=n; i++)cin>>a[i];
	for(R i=1; i<=k; i++)
		for(R j=1; j<=n; j++)
			if(i>=a[j])f[i]=max(f[i],i-f[i-a[j]]);
	cout<<f[k];
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：2)

## [Stones](https://www.luogu.com.cn/problem/AT_abc270_d)

一道博弈论 dp 题

## 思路分析

设 $dp_i$ 表示当前的石子数量为 $i$ 时，先手能取的最大值。

假设先手 Takahashi 取的是 $a_j$，那么石子数变为 $i-a_j$，Takahashi 取完后，此时的先手是 Aoki。

此时 Aoki 能取到的最大石子数表示为 $dp_{i - a_j}$，所以 $dp_i$ 可以由 $a_j+i-a_j-dp_{i-a_j}$ 转移得到，即 $dp_i$ 由 $i-dp_{i-a_j}$ 转移得到。

所以 $dp_i=\max(dp_i,i-dp_{i-a_j})$。

时间复杂度：$O(nk)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=1e4+1;
int f[N],n,a[N],k;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>k>>n;
	for(R i=1; i<=n; i++)cin>>a[i];
	for(R i=1; i<=k; i++)
		for(R j=1; j<=n; j++)
			if(i>=a[j])f[i]=max(f[i],i-f[i-a[j]]);
	cout<<f[k];
	return 0;
}

```

---

## 作者：Hisaishi_Kanade (赞：2)

首先很显然直接贪心是不行的，就好像背包的时候一直选价值最大的肯定会假一样。

诶？背包？这题还真有点像背包。

考虑像背包一样设，$f_i$ 表示剩下 $i$ 个石子的先手最大获得石头数。

设最后一步拿走了 $m$ 颗石子，显然 $m\in A$。那么有 $f_i=i-f_{i-m}$（总共 $i$ 个嘛，对手肯定也是按照这个最优方案搞的，那么拿走的就是是 $f_{i-m}$）。

然后直接 $O(NK)$ 就把这题冲过了。

```cpp
#include <stdio.h>
int val[10005];
int f[10005];
inline int max(int x,int y)
{
	return x>y?x:y;
}
int main()

{
	int n,i,j,k;scanf("%d %d",&n,&k);
	for(i=1;i<=k;++i)
	{
		scanf("%d",val+i);
	}
	for(i=1;i<=n;++i)
		for(j=1;j<=k;++j)
			if(i>=val[j])
				f[i]=max(f[i],i-f[i-val[j]]);//这一坨真的很像背包诶。
	//个人认为这题用到了背包的思想。
	printf("%d",f[n]);
	return 0;
}
```

---

## 作者：Demons_Killer (赞：2)

# 解题思路：
很简单的一道贪心模拟题。

每次都取最大的石头，$n$ 不够就取少一点的石头，取到不能取为止。记得要先排一个序，让石头序列保持单调递增，这样才能尽可能多的取石头。

把每次取的石头数量加起来，就得到了最终答案。

# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+10;
int n,k;
int a[N];
int f[N];
int ans;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+k);
	while(n>=a[1]){
		for(int i=k;i>=1;i--){
			if(n>=a[i]){
				ans+=a[i];
				n-=a[i];
				break;
			}
		}
		for(int i=k;i>=1;i--){
			if(n>=a[i]){
				n-=a[i];
				break;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：yyz_100110 (赞：1)

# [[ABC270D] Stones ](https://www.luogu.com.cn/problem/AT_abc270_d)

## 题面：

我们有一个 $N$ 个石子，还有一个长度为 $K$ 的数列 $A={A_1,A_2\cdots,A_K}$。

我们看一看这题，这不是博弈论吗。但你仔细一看这又像背包，那我们怎么做呢，从样例入手会更好的理解。

## 思路：

```
10 2      5
1 4

11 4      8
1 2 3 6
```

我们看前两个样例，我们可以得出一个道理，如果我拿的是先手即 $A_K$，那么他就只能拿 $dp_i-a_k$，我们可以得出一个很关键的方程式：$dp_i =\max dp_{i-a_k}$，相当于在程序中我们只要输出 $a_n$ 即可，详见代码。

温馨提示： 时间复杂度 $O(nk)$，我们这么写完全不会超时的。


# AcCode:
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int a[100086],b[100086];
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=k;j++)
            if(i>=a[j])
                b[i]=max(b[i],i-b[i-a[j]]);
    cout<<b[n]<<endl;
return 0;
}
~~~
奉上 [AC 记录](https://www.luogu.com.cn/record/114504779)。

辛苦管理员审核了。

切勿抄袭。

---

## 作者：Mingrui_Yang (赞：0)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc270_d)

## 思路

考虑 DP。

令 $f_{i}$ 表示当前石头数量为 $i$，先手可以拿到的最多石头数量。

设最后一步拿走了 $a_j$ 个石头，剩下 $i - a_j$ 个，此时对方为先手，所以对方最多拿走 $f_{i - a_j}$ 个石头，则剩下的石头 $i - f_{i - a_j}$ 都可以拿走。

状态转移方程：
$$
f_{i} = \max_{j = 1}^{k}i - f_{i - a_j}
$$

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n, k;
int a[N];
int f[N];
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= k; i ++ ) cin >> a[i];
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= k; j ++ )
			if (i >= a[j])
				f[i] = max(f[i], i - f[i - a[j]]);
	cout << f[n] << endl;
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

$Problem$：

初始 $n$ 块石头，$A$ 和 $B$ 两人轮流取，$A$ 先手。

给出一个长度为 $k$ 的序列 $s$，元素为 $s_1,\cdots,s_k$。每次选择一个数 $i$（$i \in [1,k]$），并取出 $s_i$ 个石头。无法再取时游戏结束。

问：如果双方均按照最优策略（即最大化自己得到的石头数量），$A$ 能得到多少石头？



------------
$Solution$：

容易想到 dp。

设计状态 $dp_{i,0/1}$ 表示形成当前局面（剩 $i$ 块石头，$0$ 为 $A$ 先手，$1$ 相反）时，$A$ 能取到的石头数量。

令当前状态为 $dp_{i,p}$。枚举 $s$，只要 $a_j+i \le n$，就说明可以从 $dp_{i+a_j,1/0}$ 进行转移：

- $p=1$，说明上一步是 $A$ 做的。由于 $A$ 要最大化自己的石头数，所以 $dp_{i,p}=\max_{j=1}^{k} (dp_{i+a_j,0}+a_j)$。

- $p=0$，说明上一步是 $B$ 做的，则 $dp_{i,p}=\min_{j=1}^{k} dp_{i+a_j,1}$。

最后，答案为所有无法再取的 $i$ 的两个 $dp$ 值的较大值的最大值。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=1e4+5;
const int M=105;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x*f;
}

int n,m,ans,a[M],dp[N][2];

main(){
	m=wrd(),n=wrd();
	for(int i=1;i<=n;++i) a[i]=wrd();
	
	dp[m][0]=dp[m][1]=0;
	for(int i=0;i<m;++i) dp[i][1]=inf;
	
	for(int i=m-1;i>=0;--i){
		for(int j=1;j<=n;++j){
			int k=i+a[j];
			if(k>m) break;
			dp[i][0]=max(dp[i][0],dp[k][1]+a[j]);
			dp[i][1]=min(dp[i][1],dp[k][0]);
		}
	}
	
	for(int i=0;i<a[1];++i) ans=max(ans,max(dp[i][1],dp[i][0]));
	return printf("%lld",ans),0;
}
```

---

## 作者：Register_int (赞：0)

考虑 dp，设 $dp_i$ 为当石子有 $i$ 个时先手最多能取的石子数量。如果当前取走 $a_j$ 个石子，那么先后手转变，后手就按之前推出的先手最优策略取石子。容易得出 $dp$ 方程：
$$dp_i=\max^{k}_{j=1}(i-dp_{i-a_j})$$
顺推即可算出最终答案。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e4 + 10;
const int MAXM = 1e2 + 10;

int n, k;

int a[MAXM], dp[MAXN];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; i++) scanf("%d", &a[i]);
	sort(a + 1, a + k + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			if (a[j] > i) break;
			dp[i] = max(dp[i], i - dp[i - a[j]]);
		}
	}
	printf("%d", dp[n]);
}
```

---

## 作者：0xFF (赞：0)

设 $f_{i,0/1}$ 表示剩余 $i$ 块石子时，在先手和后手都使用最优策略的情况下，先手/后手会取走多少块石子。

根据本题限制，后手的一切行为都被先手控制，先手一定可以取到最优，而后手只能取到剩余的 $i-f_{i,0}$ 块石子。

$$f_{i,0} = \max \left \{ f_{i-a_j,1} \right \} $$

$$f_{i,1} = i - f_{i,0}$$

设先手本次取 $a_j$ 块石子，那么 $f_{i}$ 转态就只与 $f_{i-a_j}$ 转态有关，且剩余 $i$ 块石子时的先手是剩余 $i-a_j$ 块石子时的后手，所以可得上述转移方程。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<map>
#include<climits>
#include<queue>
#include<deque>
#include<vector>
#define int long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int N = 1e5 + 10;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int ans = 0;
int a[N],f[N][2];
signed main(){
	int n = read() , k = read();
	for(int i=1;i<=k;i++) a[i] = read();
	for(int i=1;i<=n;i++){
		f[i][0] = INF;
		for(int j=1;j<=k;j++){
			if(i >= a[j]){
				f[i][1] = max(f[i][1],f[i-a[j]][0] + a[j]);
			} 
		}
		f[i][0] = i - f[i][1];
	}
	cout<<f[n][1];
	return 0;
}
```


---

## 作者：郑朝曦zzx (赞：0)

## 一 解题思路
首先，贪心肯定是不行的，我们无法证明每次取最多的石子数量就能保证最优解，证据：[提交记录](https://atcoder.jp/contests/abc270/submissions/35846827)。

考虑 DP，令 $dp_{i,1}$ 表示先手取石子的最优解，$dp_{i,0}$ 表示后手取石子的最优解，那么 $dp_{n,1}$ 即为所求。

那么有 $i$ 个石子状态，可以从所有 $i - a_j$ 个石子的状态转移，先手取时取最大，后手取时取最小。

即：

$dp_{i,1} = \max(dp_{i - a_j,0} + a_j)$

$dp_{i,0} = \min(dp_{i - a_j,1})$

换句话说，先手在上一步是后手，后手上一步是先手，先手一定会选择最优解，后手只剩下最差解。

## 二 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read()
{
	bool flag = true;
	char c = getchar();
	if (c == '-') flag = false;
	while(!(c >= '0' && c <= '9')) c = getchar();
	int x = 0;
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (flag == true) return x;
	return -x;
}
int a[10010], dp[10010][2];
int ans;
int main()
{
	int n = read(), k = read();
	for (int i = 1; i <= k; ++i)
		a[i] = read();
	for (int i = 1; i <= n; ++i)
	{
		dp[i][0] = 1e9;
		for (int j = 1; j <= k; ++j)
		{
			if (i >= a[j])
				dp[i][1] = max(dp[i - a[j]][0] + a[j], dp[i][1]);
			if (i >= a[j])
				dp[i][0] = min(dp[i - a[j]][1], dp[i][0]);
		}
	}
	printf("%d\n", dp[n][1]);
    return 0;
}
```


---

