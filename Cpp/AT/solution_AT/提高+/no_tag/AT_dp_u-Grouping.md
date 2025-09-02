# Grouping

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_u

$ N $ 羽のうさぎたちがいます。 うさぎたちには $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。

各 $ i,\ j $ ($ 1\ \leq\ i,\ j\ \leq\ N $) について、うさぎ $ i $ と $ j $ の相性が整数 $ a_{i,\ j} $ によって与えられます。 ただし、各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について $ a_{i,\ i}\ =\ 0 $ であり、各 $ i,\ j $ ($ 1\ \leq\ i,\ j\ \leq\ N $) について $ a_{i,\ j}\ =\ a_{j,\ i} $ です。

太郎君は、$ N $ 羽のうさぎたちをいくつかのグループへ分けようとしています。 このとき、各うさぎはちょうど $ 1 $ つのグループに属さなければなりません。 グループ分けの結果、各 $ i,\ j $ ($ 1\ \leq\ i\ <\ j\ \leq\ N $) について、うさぎ $ i $ と $ j $ が同じグループに属するならば、太郎君は $ a_{i,\ j} $ 点を得ます。

太郎君の総得点の最大値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 16 $
- $ |a_{i,\ j}|\ \leq\ 10^9 $
- $ a_{i,\ i}\ =\ 0 $
- $ a_{i,\ j}\ =\ a_{j,\ i} $

### Sample Explanation 1

$ \{1,\ 3\},\ \{2\} $ とグループ分けすればよいです。

### Sample Explanation 2

$ \{1\},\ \{2\} $ とグループ分けすればよいです。

### Sample Explanation 3

$ \{1,\ 2,\ 3,\ 4\} $ とグループ分けすればよいです。 答えは 32-bit 整数型に収まらない場合があります。

## 样例 #1

### 输入

```
3
0 10 20
10 0 -100
20 -100 0```

### 输出

```
20```

## 样例 #2

### 输入

```
2
0 -10
-10 0```

### 输出

```
0```

## 样例 #3

### 输入

```
4
0 1000000000 1000000000 1000000000
1000000000 0 1000000000 1000000000
1000000000 1000000000 0 -1
1000000000 1000000000 -1 0```

### 输出

```
4999999999```

## 样例 #4

### 输入

```
16
0 5 -4 -5 -8 -4 7 2 -4 0 7 0 2 -3 7 7
5 0 8 -9 3 5 2 -7 2 -7 0 -1 -4 1 -1 9
-4 8 0 -9 8 9 3 1 4 9 6 6 -6 1 8 9
-5 -9 -9 0 -7 6 4 -1 9 -3 -5 0 1 2 -4 1
-8 3 8 -7 0 -5 -9 9 1 -9 -6 -3 -8 3 4 3
-4 5 9 6 -5 0 -6 1 -2 2 0 -5 -2 3 1 2
7 2 3 4 -9 -6 0 -2 -2 -9 -3 9 -2 9 2 -5
2 -7 1 -1 9 1 -2 0 -6 0 -6 6 4 -1 -7 8
-4 2 4 9 1 -2 -2 -6 0 8 -6 -2 -4 8 7 7
0 -7 9 -3 -9 2 -9 0 8 0 0 1 -3 3 -6 -6
7 0 6 -5 -6 0 -3 -6 -6 0 0 5 7 -1 -5 3
0 -1 6 0 -3 -5 9 6 -2 1 5 0 -2 7 -8 0
2 -4 -6 1 -8 -2 -2 4 -4 -3 7 -2 0 -9 7 1
-3 1 1 2 3 3 9 -1 8 3 -1 7 -9 0 -6 -8
7 -1 8 -4 4 1 2 -7 7 -6 -5 -8 7 -6 0 -9
7 9 9 1 3 2 -5 8 7 -6 3 0 1 -8 -9 0```

### 输出

```
132```

# 题解

## 作者：FelFa_1414666 (赞：24)

数据范围知**状压 dp** 系列。

[atcoder 题目传送门](https://atcoder.jp/contests/dp/tasks/dp_u) & [洛谷题目传送门](https://www.luogu.com.cn/problem/AT4542)

[更好的阅读体验](https://www.luogu.com.cn/blog/xesssb10108899/solution-at4542)

---

## Description

有 $n$ 个兔子，要将它们分成若干组，对于每一对 $1\le i,j\le n$，如果兔子 $i$ 和兔子 $j$ 在同一组，会获得 $a_{i,j}$ 的分值，求能获得的最大总分值。

- $1\le n\le 16$
- $\left\vert a_{i,j}\right\vert\le 10^9$

---

## Solution

首先，考虑一个朴素地不能再朴素的 dp 状态：

- $dp_{mask}$ 表示当前已选兔子的情况为 $mask$ 的最大总分值。（其中，$mask$ 为二进制状压变量，每个二进制位对应一个兔子的占用情况）

同样地，考虑一个朴素地转移：

$$dp_{mask}=\max\{dp_{pmask}+V_{mask\bigoplus pmask}\}$$

解释一下，其中 $pmask$ 是 $mask$ **枚举出的子集**，$V$ 数组是预处理出的**每一个集合如果分成一组会获得的分数**，预处理复杂度为 $O(n^22^n)$（至于如何预处理参考代码吧）$\bigoplus$ 表示**按位异或**运算。转移需要枚举所有集合 $pmask$ 并判断是否 $pmask\subseteq mask$，总的时间复杂度是 $O(2^{2n})$。

这样做的意义是：枚举上一次选出一组之前已占用状态 $pmask$，用这一状态下的最大总分值加上新一组，即 $mask\bigoplus pmask$ 分为一组能获得的总分值

**然后你就会发现，卡一卡常，竟然就过了！！！**

![](https://cdn.luogu.com.cn/upload/image_hosting/hnpfuult.png)

~~虽然但是，为了配合这个题目的本意，我们假装这样写过不了。~~

来考虑优化，我们发现二进制枚举集合，并判断子集的部分有些浪费。为什么呢？因为其实有一大部分集合都不是 $mask$ 的子集，这个操作浪费了很多复杂度，maybe 我们的优化可以从这里入手。

这就引发了我们的思考，有没有一种方法，能让**枚举出来的全是 $mask$ 的子集呢？**

答案是肯定的。

只要我们将循环语句这样写，就能做到我们想要的：

```cpp
for(int pmask=mask;pmask>0;pmask=(pmask-1)&mask)
```

`pmask=(pmask-1)&mask`是关键。它保证了循环的过程中 $pmask$ 的值是严格递减的，同时**与运算**保证 $pmask\subseteq mask$ 。这样就能不重不漏不浪费地完成对子集地枚举。

这样就能 AC 了。我们继续来分析一下算法的时间复杂度。

> 可以证明：对于所有状态，枚举子集。总的时间复杂度是 $O(3^n)$ 的。

我们可以将不属于 $mask$ 的元素看作 0，属于 $mask$ 但不属于 $pmask$ 的元素看作 1，属于 $pmask$ 的元素看作 2。对于每个兔子，都有 3 种可能的状态，所以总时间复杂度是 $O(3^n)$。

- 时间复杂度：$O(n^22^n+3^n)$

- 空间复杂度：$O(2^n)$

![](https://cdn.luogu.com.cn/upload/image_hosting/glscan3e.png)

咱就是说，优化效果还是很顶的。

---

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const ll INF=1e18+7;
int n;
ll a[25][25],v[(1<<16)+5],dp[(1<<16)+5];//v数组记录每个集合分成一组会获得的分值
int main()
{
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];
	for(int mask=1;mask<(1<<n);mask++)
	{//预处理v数组，对于每个集合mask，O(n^2)地枚举其中每一对兔子，求总分值
		for(int i=0;i<n;i++) if ((mask>>i)&1)
			for(int j=i+1;j<n;j++) if ((mask>>j)&1)
				v[mask]+=a[i][j];
		dp[mask]=v[mask];//初始化dp数组
	}
	for(int mask=1;mask<(1<<n);mask++)
		for(int pmask=mask;pmask>0;pmask=(pmask-1)&mask)
			dp[mask]=max(dp[mask],dp[pmask]+v[pmask^mask]);//转移
	cout<<dp[(1<<n)-1]<<endl;//答案为全集的dp值
	return 0;
}
```

---

本题的关键在与对状压 dp 转移的设计，以及如何优化枚举子集的过程。~~虽然不优化卡一卡也能过。~~ 

希望题解对你有帮助！

---

## 作者：Phartial (赞：17)

由于 $n \le 16$，考虑状压 dp。

设 $f_i$ 为集合为 $i$ 时的最大得分，那么我们可以把集合 $i$ 划分成两个集合，答案即为这两个集合的答案之和。

不难推出转移方程为 $ f_i=\max\limits_{j\subset i}\{f_j+f_{i-j}\} $。

记忆化搜索即可。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 16;

int n, t;
LL a[kN][kN], f[1 << kN];

LL C(int i) {
  if (~f[i]) {
    return f[i];
  }
  f[i] = 0;
  for (int j = 0; j < n; ++j) {
    for (int k = j + 1; k < n; ++k) {
      if ((i >> j) & 1 && (i >> k) & 1) {
        f[i] += a[j][k];  // 先算出不划分集合情况下的得分
      }
    }
  }
  for (int j = i; j = (j - 1) & i;) {   // 枚举子集
    f[i] = max(f[i], C(j) + C(j ^ i));  // 更新答案
  }
  return f[i];
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> a[i][j];
    }
  }
  fill(f + 1, f + (1 << n), -1);  // 初始化
  cout << C((1 << n) - 1);
  return 0;
}
```


---

## 作者：Akoasm_X (赞：7)

先看一眼数据范围 $n \leq 16 $，可以试着进行状态压缩。

设 $dp[i]$ 表示状态为 $i$ 的情况下最大的分组收益。

1. 第一步我们枚举每个状态 $i$，计算得出状态为 $i$ 时分成一组的收益是多少。

2. 我们考虑对状态 $i$ 进行分组，枚举一个子集为 $j$，其补集记为 $k$，可以得出方程

$$dp[i] = \max\,(\,dp[i]\,,\,dp[j]+dp[k]\,)$$

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 17;
int n,m;
int A[maxn][maxn];
LL dp[1<<maxn],va[1<<maxn];

int main()
{
	scanf("%d",&n);m = (1<<n)-1;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&A[i][j]);
	//预处理状态i分成1个组的收益 
	for(int i=1;i<=m;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<j;k++)
				if(((1<<k)&i)&&((1<<j)&i))
					va[i] += A[j][k];
	for(int i=1;i<=m;i++)
	{//枚举状态 
		dp[i] = va[i];
		for(int j=i&(i-1);j;j=i&(j-1))//这一步枚举子集，可以理解为把状态i强制分成两组 
			dp[i] = max(dp[i],dp[i^j]+dp[j]);
	}
	printf("%lld\n",dp[m]);
	return 0;
}
```


---

## 作者：Leowang2009 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_u)

# 思路

题目上给的数据范围为 $n \le 16$，这个显然是[状压 dp](https://oi-wiki.org/dp/state/)。

这个转移方程应该也比较好想。设当前已选择的集和为 $S$，从状态 $T$ 转移过来。初始状态显然为全分为一组时的总贡献，转移方程为：

$$f_S= \max \limits_{T\subseteq S}\{f_T+f_{\complement_sT}\}$$

枚举子集的时间复杂度为 $O(3^n)$，计算贡献的复杂度为 $O(n^2)$，共 $2^n$ 种情况，故总复杂度为 $O(2^nn^2+3^n)$。

# 代码

这个题应该没什么代码上的难点，和正常状压一样，$1$ 代表选，$0$ 代表不选，计算总贡献代码如下：

```cpp
ll calc(int x){
	ll res=0;
	for(int i=1;i<=n;i++){
		if(!((1<<(i-1))&x)) continue;//如果没有选则跳过
		for(int j=i+1;j<=n;j++)//从i+1开始枚举，可以避免重复
			if((1<<(j-1))&x) res+=g[i][j];//如果有这对数，将其贡献加入
	}
	return res;
}
```

dp 代码如下：

```cpp
for(int i=1;i<=s;i++){
	f[i]=calc(i);
	for(int t=i&(i-1);t;t=i&(t-1))//枚举子集，原因还请读者自行思考
		f[i]=std::max(f[t]+f[i^t],f[i]);
}
```

## AC code：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
int n;
ll f[1<<16],g[20][20];
ll calc(int x){
	ll res=0;
	for(int i=1;i<=n;i++){
		if(!((1<<(i-1))&x)) continue;//如果没有选则跳过
		for(int j=i+1;j<=n;j++)//从i+1开始枚举，可以避免重复
			if((1<<(j-1))&x) res+=g[i][j];//如果有这对数，将其贡献加入
	}
	return res;
}
int main(){
	scanf("%d",&n);
	const int s=(1<<n)-1;//全集s
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",g[i]+j);//输入
	for(int i=1;i<=s;i++){
		f[i]=calc(i);
		for(int t=i&(i-1);t;t=i&(t-1))//枚举子集，原因还请读者自行思考
			f[i]=std::max(f[t]+f[i^t],f[i]);
	}
	printf("%lld",f[s]);//输出答案
	return 0;
}
```

完结撒花！

---

## 作者：lnwhl (赞：2)

# $\text{Description}$
对 $n$ 个物品任意分组，如果第 $i$ 个物品和 第 $j$ 个物品分在一组，会产生 $a_{i,j}$ 的得分，最大化得分之和。$(i,j)$ 和 $(j,i)$ 的贡献只计算一次。$n\le16$。
# $\text{Solution}$
注意到 $n\le16$，考虑状压 dp。

设 $f_i$ 表示当前集合为 $i$ 时的最大得分。转移时枚举子集，即枚举当前集合是由哪两个子集构成的。

可以的出如下转移方程：
$$f_i=\max\limits_{j\subset i}{\{f_j+f_{i-j}\}}$$
时间复杂度为 $O(2^nn^2+3^n)$，分别来自 求集合不分成两部分的得分 和 穷举子集。
# $\text{Code}$
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,mx,a[17][17],f[1<<17];
signed main()
{
	cin>>n;mx=(1<<n)-1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin>>a[i][j];
	for(int i=0;i<=mx;++i)
	{
		for(int j=1;j<=n;++j)
			for(int k=j+1;k<=n;++k)
				if(((1<<(j-1))&i)&&((1<<(k-1))&i))
					f[i]+=a[j][k];//集合不分成两部分的得分
		for(int j=i;j;j=(j-1)&i)//穷举子集
			f[i]=max(f[i],f[j]+f[i^j]);
	}
	cout<<f[mx];	
	return 0;
}
```

---

## 作者：MortisM (赞：1)

题意：给你 $n$ 个物品需要分组，你可以将它们分成一些组合，每组内部每一对 $(i,j)$ 都会产生一个贡献 $a_{i,j}$（可能为负数），问你最大可能产生的总贡献。

数据范围：$n\leq 16$。

这个数据范围暗示着这道题使状压 DP。

设计出 DP 状态：设 $f(i)$ 表示选择状态为 $i$ 时的最大总贡献。

考虑转移，转移就是你一个 $i$ 有两种选择：

+ 不划分（直接成为一个集合，即 $i$ 内部两两直接产生贡献）。

+ 划分成多个集合（划分后每个集合分别计算）。

但你考虑这个情况并不需要真的划分成多个集合，只要划分成 2 个然后这 2 个在递归继续划分。

划分成 2 个的过程可以通过用二进制枚举子集来实现。

时间复杂度 $O(2^N\cdot N^2)$。

**[代码](https://atcoder.jp/contests/dp/submissions/33882491)**

---

## 作者：wangyibo201026 (赞：1)

## 思路

看到 $n \le 16$，想到状压 DP。

显然可以设 $f_s$ 为对集合 $s$ 进行划分，可能得到的最大得分，其中 $s$ 为二进制数。

显然有状态转移方程：

$$f_i = \max\limits_{i \subseteq s}\{f_{i - j} + score(j)\}$$

其中 $score(j)$ 表示集合 $j$ 里的分数。

空间复杂度：$O(2^n)$。

时间复杂度：预处理 $O(n^2 \times 2^n)$，其中可以用这么多时间处理每一个集合的分数。转移 $O(4^n)$。

显然我们可以只用枚举 $s$ 的子集即可，并不需要花 $O(2^n)$ 的时间来枚举，只需枚举 $1$ 即可。

因此时间复杂度降到了 $O(\sum\limits_{k=0}^{n}C^k_n2^k)$，根据某某二项式定理可以得出时间复杂度为 $O(3^n)$，可以过啦！

## 代码

Code：

```cpp
#include<bits/stdc++.h>

#define endl '\n';
#define int long long

using namespace std;

const int N = 20;

int n;
int a[N][N], C[1 << N], f[1 << N];

int dfs(int s){
  if(!s){
    return 0;
  }
  if(~f[s]){
    return f[s];
  }
  for(int i = s; i; i = (i - 1) & s){   //枚举每一个 1 是否选
    f[s] = max(f[s], dfs(s - i) + C[i]);   //转移
  }
  return f[s];
}

void Solve(){
  cin >> n;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> a[i][j];
    }
  }
  for(int s = 1; s < 1 << n; s++){  //预处理每个集合的分数
    f[s] = -1;
    for(int i = 0; i < n; i++){
      if(s >> i & 1){
        for(int j = i + 1; j < n; j++){
          if(s >> j & 1){
            C[s] += a[i][j];
          }
        }
      }
    }
  }
  cout << dfs((1 << n) - 1);   //注意要 -1
}

signed main(){
  Solve();
  return 0;
}
```

---

