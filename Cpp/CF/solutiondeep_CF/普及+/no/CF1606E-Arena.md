# 题目信息

# Arena

## 题目描述

There are $ n $ heroes fighting in the arena. Initially, the $ i $ -th hero has $ a_i $ health points.

The fight in the arena takes place in several rounds. At the beginning of each round, each alive hero deals $ 1 $ damage to all other heroes. Hits of all heroes occur simultaneously. Heroes whose health is less than $ 1 $ at the end of the round are considered killed.

If exactly $ 1 $ hero remains alive after a certain round, then he is declared the winner. Otherwise, there is no winner.

Your task is to calculate the number of ways to choose the initial health points for each hero $ a_i $ , where $ 1 \le a_i \le x $ , so that there is no winner of the fight. The number of ways can be very large, so print it modulo $ 998244353 $ . Two ways are considered different if at least one hero has a different amount of health. For example, $ [1, 2, 1] $ and $ [2, 1, 1] $ are different.

## 样例 #1

### 输入

```
2 5```

### 输出

```
5```

## 样例 #2

### 输入

```
3 3```

### 输出

```
15```

## 样例 #3

### 输入

```
5 4```

### 输出

```
1024```

## 样例 #4

### 输入

```
13 37```

### 输出

```
976890680```

# AI分析结果

### 题目翻译
# 竞技场

## 题目描述
有 $n$ 个英雄在竞技场中战斗。初始时，第 $i$ 个英雄有 $a_i$ 点生命值。

竞技场中的战斗分若干轮进行。在每一轮开始时，每个存活的英雄都会对其他所有英雄造成 $1$ 点伤害。所有英雄的攻击同时发生。在一轮结束时生命值小于 $1$ 的英雄被视为死亡。

如果在某一轮结束后恰好有 $1$ 个英雄存活，那么他将被宣布为胜利者。否则，没有胜利者。

你的任务是计算为每个英雄 $a_i$ 选择初始生命值的方法数，其中 $1 \le a_i \le x$，使得战斗没有胜利者。方法数可能非常大，因此请将结果对 $998244353$ 取模。如果至少有一个英雄的生命值不同，则两种方法被认为是不同的。例如，$[1, 2, 1]$ 和 $[2, 1, 1]$ 是不同的。

## 样例 #1
### 输入
```
2 5
```
### 输出
```
5
```

## 样例 #2
### 输入
```
3 3
```
### 输出
```
15
```

## 样例 #3
### 输入
```
5 4
```
### 输出
```
1024
```

## 样例 #4
### 输入
```
13 37
```
### 输出
```
976890680
```

### 算法分类
动态规划

### 综合分析与结论
这些题解大多采用动态规划的方法来解决问题。核心思路是通过定义合适的状态，根据不同情况进行状态转移，从而计算出没有胜利者的方案数。
- **思路对比**：大部分题解定义状态时考虑了存活人数和最大血量或已扣血量等因素，如 `f[i][j]` 或 `dp[i][j]`，但在状态转移时，不同题解根据不同的情况分类讨论，如根据存活人数和最大血量的大小关系等。
- **算法要点**：普遍使用快速幂和组合数的预处理来优化时间复杂度，同时在状态转移时利用乘法原理和加法原理计算方案数。
- **解决难点**：难点在于准确分析每一轮战斗后英雄的存活情况和血量变化，以及如何根据这些情况进行状态转移，同时要注意取模操作避免溢出。

### 所选题解
- **作者：StudyingFather (4星)**
  - **关键亮点**：思路清晰，状态定义和转移过程详细，代码实现规范，注释丰富。
  - **核心代码**：
```cpp
#include <iostream>
using namespace std;
const int MOD = 998244353;
long long f[505][505], c[505][505];
long long fpow(long long x, int y) {
  long long ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD;
    y >>= 1;
  }
  return ans;
}
int main() {
  int n, x;
  cin >> n >> x;
  for (int i = 0; i <= n; i++) c[i][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
  for (int i = 2; i <= n; i++)
    for (int j = 1; j <= x; j++) {
      if (i > j) {
        f[i][j] = ((fpow(j, i) - fpow(j - 1, i)) % MOD + MOD) % MOD;
      } else {
        for (int k = 1; k <= i; k++) {
          f[i][j] =
              (f[i][j] + c[i][k] * fpow(i - 1, i - k) % MOD * f[k][j - i + 1]) %
              MOD;
        }
      }
    }
  long long ans = 0;
  for (int i = 1; i <= x; i++) ans = (ans + f[n][i]) % MOD;
  cout << ans << endl;
  return 0;
}
```
**核心实现思想**：定义 `f[i][j]` 表示当前场上还有 $i$ 个人，其中最大血量为 $j$ 时，最后场上没有赢家的方案数。根据 $i - 1$ 和 $j$ 的大小关系分情况讨论进行状态转移，最后累加所有最大血量情况下的方案数得到最终结果。

- **作者：MinimumSpanningTree (4星)**
  - **关键亮点**：状态定义和转移过程分析详细，对时间复杂度进行了合理推测，代码实现中对取模等细节处理得当。
  - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll MOD=998244353;
const int N=510;
ll n,x,dp[N][N],c[N][N],ans;
ll quick_pow(ll a,ll b)
{
	ll sum=1;
	while(b)
	{
		if(b%2==1) b--,sum=(sum*a)%MOD;
		a=(a*a)%MOD,b>>=1;
	}
	return sum;
}
int main()
{
	scanf("%lld%lld",&n,&x);
	for(int i=0;i<=n;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
	}
	for(ll i=2;i<=n;i++) 
	{
		for(ll j=1;j<=x;j++)
		{
			if(i-1>=j) dp[i][j]=(quick_pow(j,i)+MOD-quick_pow(j-1,i))%MOD;
			else
			{
				for(int k=1;k<=i;k++) dp[i][j]=(dp[i][j]+(((dp[k][j-(i-1)]*c[i][k])%MOD)*quick_pow(i-1,i-k))%MOD)%MOD;
			}
		}
	}
	for(int i=1;i<=x;i++) ans=(ans+dp[n][i])%MOD;
	printf("%lld",ans);
	return 0;
}
```
**核心实现思想**：定义 `dp[i][j]` 表示 $i$ 人存活，最大血量为 $j$ 时，最后无人生还的方案数。同样根据 $i - 1$ 和 $j$ 的大小关系分情况进行状态转移，最后累加得到结果。

- **作者：Genius_Star (4星)**
  - **关键亮点**：采用反向思考的方式，先计算有胜利者的方案数，再用总方案数减去有胜利者的方案数得到没有胜利者的方案数，思路独特。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=505;
const ll mod=998244353;
ll n,x;
ll C[N][N],dp[N][N];
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
void init(){
    C[0][0]=1;
    for(int i=1;i<N;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++)
          C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
}
int main(){
	memset(dp,0,sizeof(dp));
	init();
	n=read(),x=read();
	for(int i=1;i<=x;i++)
	  dp[1][i]=i;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=x;j++){
			if(j<i)
			  continue;
			for(int k=0;k<i;k++)
			  dp[i][j]=(dp[i][j]+((dp[i-k][j-i+1]*qpow(i-1,k))%mod*C[i][k])%mod)%mod;
		}
	}
	write((qpow(x,n)-dp[n][x]+mod)%mod);
	return 0;
} 
```
**核心实现思想**：定义 `dp[i][j]` 为 $i$ 位勇士，生命值都在 $j$ 以内，最终剩余一位勇士的方案数。通过枚举这一轮生命值降为 $0$ 以下的人数 $k$ 进行状态转移，最后用总方案数 $x^n$ 减去 `dp[n][x]` 得到结果。

### 最优关键思路或技巧
- **状态定义**：合理定义状态，如考虑存活人数和最大血量或已扣血量等因素，是解决动态规划问题的关键。
- **分类讨论**：根据不同情况进行分类讨论，如根据存活人数和最大血量的大小关系，分别计算方案数。
- **预处理优化**：使用快速幂和组合数的预处理来优化时间复杂度。

### 可拓展之处
同类型题或类似算法套路：可以拓展到更复杂的战斗规则，如英雄有不同的攻击力、技能等，或者改变胜利条件。在算法上，仍然可以使用动态规划的思想，通过定义合适的状态和状态转移方程来解决问题。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)

### 个人心得摘录与总结
- **MinimumSpanningTree**：提到一开始写 `b/=2` TLE 了，改成 `b>>=1` 就过了，提醒在代码实现中要注意细节，避免因运算方式导致超时。

---
处理用时：88.98秒