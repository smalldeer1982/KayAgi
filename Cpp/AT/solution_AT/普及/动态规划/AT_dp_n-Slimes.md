# Slimes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_n

$ N $ 匹のスライムが横一列に並んでいます。 最初、左から $ i $ 番目のスライムの大きさは $ a_i $ です。

太郎君は、すべてのスライムを合体させて $ 1 $ 匹のスライムにしようとしています。 スライムが $ 1 $ 匹になるまで、太郎君は次の操作を繰り返し行います。

- 左右に隣り合う $ 2 $ 匹のスライムを選び、それらを合体させて新しい $ 1 $ 匹のスライムにする。 合体前の $ 2 $ 匹のスライムの大きさを $ x $ および $ y $ とすると、合体後のスライムの大きさは $ x\ +\ y $ となる。 このとき、太郎君は $ x\ +\ y $ のコストを支払う。 なお、合体の前後でスライムたちの位置関係は変わらない。

太郎君が支払うコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ N\ \leq\ 400 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

次のように操作を行えばよいです。 操作対象のスライムを太字で表しています。 - (\*\*10\*\*, \*\*20\*\*, 30, 40) → (\*\*30\*\*, 30, 40) - (\*\*30\*\*, \*\*30\*\*, 40) → (\*\*60\*\*, 40) - (\*\*60\*\*, \*\*40\*\*) → (\*\*100\*\*)

### Sample Explanation 2

例えば、次のように操作を行えばよいです。 - (\*\*10\*\*, \*\*10\*\*, 10, 10, 10) → (\*\*20\*\*, 10, 10, 10) - (20, \*\*10\*\*, \*\*10\*\*, 10) → (20, \*\*20\*\*, 10) - (20, \*\*20\*\*, \*\*10\*\*) → (20, \*\*30\*\*) - (\*\*20\*\*, \*\*30\*\*) → (\*\*50\*\*)

### Sample Explanation 3

答えは 32-bit 整数型に収まらない場合があります。

### Sample Explanation 4

例えば、次のように操作を行えばよいです。 - (7, 6, 8, 6, \*\*1\*\*, \*\*1\*\*) → (7, 6, 8, 6, \*\*2\*\*) - (7, 6, 8, \*\*6\*\*, \*\*2\*\*) → (7, 6, 8, \*\*8\*\*) - (\*\*7\*\*, \*\*6\*\*, 8, 8) → (\*\*13\*\*, 8, 8) - (13, \*\*8\*\*, \*\*8\*\*) → (13, \*\*16\*\*) - (\*\*13\*\*, \*\*16\*\*) → (\*\*29\*\*)

## 样例 #1

### 输入

```
4
10 20 30 40```

### 输出

```
190```

## 样例 #2

### 输入

```
5
10 10 10 10 10```

### 输出

```
120```

## 样例 #3

### 输入

```
3
1000000000 1000000000 1000000000```

### 输出

```
5000000000```

## 样例 #4

### 输入

```
6
7 6 8 6 1 1```

### 输出

```
68```

# 题解

## 作者：TheSky233 (赞：6)

## Description

有 $n$ 个数，第 $i$ 个数是 $a_i$ ，现在要进行 $n-1$ 次操作。

对于每一次操作，可以把相邻两个数合并起来，并写上他们的和，这次操作的代价就是这个和。

求代价最小值。

## Solution

和 [$\sf{P1090}$](https://www.luogu.com.cn/problem/P1090) 不同的是，只能合并相邻的两堆，考虑区间 dp。

设 $f_{i,j}$ 为 $a_i$ 到 $a_j$ 合并的最小值。

对于每一个 $f_{i,j}$ 枚举其中间点 $k$，此区间的最小值显然等于两个子区间 $f_{i,k}$ 和 $f_{k,j}$ 加上 $f_{i,k}$ 和 $f_{k,j}$ 合并的代价的最小值。

于是就可以推出转移方程：

$$f_{i,j}=\min\left(f_{i,j},f_{i,k}+f_{k,j}+\sum^j_{l=i}a_l\right)$$

## Code

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;

const int N=500+5;

ll a[N],f[N][N],pre[N];
int n;

signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",a+i),pre[i]=pre[i-1]+a[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) f[i][j]=1ll<<60;
		f[i][i]=0;
	}
	for(int i=n;i>=1;i--){//注意 i 是倒序，因为在算 f[1][n] 前要先算完 f[2...n][n]
		for(int j=i+1;j<=n;j++){
			for(int k=i;k<j;k++){
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+pre[j]-pre[i-1]);
			}
		}
	}
	printf("%lld",f[1][n]);
}
```

---

## 作者：cjh20090318 (赞：3)

大家好，我是 CQ-C2024 蒟蒻 CJH。

这一道题目其实就是 [P1775 石子合并（弱化版）](https://www.luogu.com.cn/problem/P1775)。

前置知识：[**区间 DP**](https://oiwiki.org/dp/interval/)。

## 状态设计

$dp_{i,j}$ 表示将区间 $[i,j]$ 合并所花费的最小代价。

## 边界条件

首先把 $1\le i \le n$ 时的 $dp_{i,i}$ 赋值为 $0$，因为自己不能合并自己。

剩下的因为要取得最小值，所以全部赋为极大值。

## 转移方程

在 $[i,j]$ 中枚举中间点 $k$，此时花费的成本为：$dp_{i,k}+dp_{k,j}+cost(i,j)$，这里的 $cost(i,j)$ 指合并两次的花费，其实就是 $\sum\limits_{x=i}^ja_x$，在去最小值即可。

所以转移方程就很显然了：

$$dp_{i,j}=\min(dp_{i,j},dp_{i,k}+dp_{k,j}+cost(i,j))$$

因为这里是某一段的和，所以可以用前缀和优化。

## 所求答案

根据状态可得，答案为 $dp_{1,n}$。

## 注意事项

变量要用 `long long`，~~要不然就见祖宗~~。

## 代码

```cpp
//the code is from chenjh
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
int n;
LL a[404],b[404],dp[404][404];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),
		b[i]=b[i-1]+a[i];//前缀和。
	memset(dp,0x3f,sizeof dp);//初始化为极大值。
	for(int i=1;i<=n;i++) dp[i][i]=0;
	for(int i=n-1;i>=1;i--)for(int j=i+1;j<=n;j++)for(int k=i;k<j;k++)//i 要倒着转移。
		dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+b[j]-b[i-1]);//状态转移。
	printf("%lld\n",dp[1][n]);
	return 0;
}
```

*谢谢大家！*

---

## 作者：Phartial (赞：3)

设 $f_{i,j}$ 表示将区间 $[i,j]$ 合并成一个数的最小代价。

考虑枚举中间点 $k$，可以把区间 $[i,j]$ 分成两个长度较短的区间 $[i,k]$ 和 $[k+1,j]$，代价即为 $f_{i,k}+f_{k+1,j}+\sum_{u=i}^{j}a_u$。

时间复杂度为 $O(n^3)$，可以通过此题。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 401;

int n;
LL a[kN], f[kN][kN];

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int l = 2; l <= n; ++l) {                        // 枚举区间长度
    for (int i = 1, j; (j = i + l - 1) <= n; ++i) {     // 枚举区间
      f[i][j] = 1LL << 62;                              // 初始化
      for (int k = i; k < j; ++k) {                     // 枚举中间点
        f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);  // 更新答案
      }
      for (int k = i; k <= j; ++k) {  // 加上合并代价
        f[i][j] += a[k];
      }
    }
  }
  cout << f[1][n];
  return 0;
}

```

---

## 作者：EnofTaiPeople (赞：2)

一个很好的区间 dp 模板。

首先，由于 $n\le400$，可以使用 $O(n^3)$ 的做法。

设 $wet[i][j]$ 表示 $i$ 到 $j$ 中所有数的总和，
$dp[i][j]$ 表示将 $i$ 到 $j$ 的数合并起来的最小代价，于是产生了如下的状态转移方程：$dp[i][j]=\min\{dp[i][k]+dp[k+1][j]|i \le k<j\}$

首先预处理，让 $dp[i][i]=0$，再让$wet[i][i]=read()$，其中 $1\le i\le n$，$read()$ 是读取函数。

然后，将 $k$ 从 $1$ 到 $n-1$ 枚举，表示 $j-i$。

状态转移后，就得到了如下的 AC 代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=4e2+2;
ll dp[N][N],n,wet[N][N];
inline ll read(){
	ll an=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-f;c=getchar();
	}while(c>='0'&&c<='9'){
		an=an*10+c-'0';c=getchar();
	}return an*f;
}
int main(){
	memset(dp,0x7f,sizeof(dp));
	register int i,j,k,t;
	for(i=1,n=read();i<=n;++i){
		wet[i][i]=read();dp[i][i]=0;
	}
	for(k=1;k<=n;++k)
		for(i=1,j=i+k;j<=n;++i,++j){
			wet[i][j]=wet[i][i]+wet[i+1][j];
			for(t=i;t<j;++t)
				dp[i][j]=min(dp[i][j],dp[i][t]+dp[t+1][j]);
			dp[i][j]+=wet[i][j];
		}
	printf("%lld\n",dp[1][n]);
	return 0;
}
```
老规矩，注意此题上限是 $1e9$，加起来很有可能会炸 int,注意开 long long！

---

## 作者：_JF_ (赞：1)

# AT4535 Slimes

 这道题就是典型的**区间dp**
 
 设 $dp[i][j]$ 表示 $i-j$ 的区间的最小值.$a[i]$ 表示前缀和。
 
 于是我们就可以得到方程。
 
$dp[i][j]= \min (dp[i][j],dp[i][k]+dp[k+1][j]+a[j]-a[i-1])$

就是把 $dp[i][j]$ 分为 $dp[i][k]$ 到 $dp[k+1][j]$ 的两个区间，所以 $k$ 的取值范围就在 $i- (j-1)$ 之中了

加上 $a[j]$ 减去 $a[i-1]$ 就是加上合并的最初始的值

所以代码便是：

注意初始化的时候值要大一点.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=700;
long long a[maxn],dp[maxn][maxn];
int main()
{
	for(int i=0;i<maxn;i++)
		for(int j=0;j<maxn;j++)
			dp[i][j]=1e18;	
	long long n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		dp[i][i]=a[i];
		a[i]+=a[i-1];
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=i;j<=n;j++)
		{
			for(int k=i;k<=j-1;k++)
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+a[j]-a[i-1]);
		}
	}
	cout<<dp[1][n]-a[n]<<endl;
	return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：1)

首先观察到 $n\leq400$ 考虑 $O(n^3)$ 的算法。

而区间动态规划所用时间复杂度恰好满足。

用 $f_{i,j}$ 表示从 $i$ 到 $j$ 和并要至少多少代价，得到转移方程：

$$f_{i,j}=\min(f_{i,j},f_{i,k}+f_{k+1,j}+s_j-s_{i-1})$$

其中 $k$ 是从 $i$ 到 $j-1$ 的任意正整数，$s_i$ 表示前缀和。

特别的，因为这道题答案较大，故要 long long ，初始化时应设为 $1e18$。

## _Code_

```cpp
#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define ll long long
const int MAXN=405;
int n;
ll a[MAXN];
ll f[MAXN][MAXN];//f[i][j]表示从i到j至少多少代价
int main(){
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<MAXN;j++)
			f[i][j]=1e18;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i][i]=a[i];
		a[i]+=a[i-1];
	}
	for(int i=n;i>=1;i--)
		for(int j=i;j<=n;j++)
			for(int k=i;k<=j-1;k++)
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+a[j]-a[i-1]);
	cout<<f[1][n]-a[n]<<endl;
}
```


---

