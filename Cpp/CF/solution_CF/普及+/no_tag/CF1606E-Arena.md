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

# 题解

## 作者：StudyingFather (赞：14)

设 $f(i,j)$ 表示当前场上还有 $i$ 个人，其中**最大血量**为 $j$ 时，最后场上没有赢家的方案数。

分两种情况考虑：

1. $i - 1 \geq j$ 时，这个回合后所有人都会死亡，因此任何满足最大血量为 $j$ 的血量分配方法均符合要求，总方案数即 $j^i - (j-1)^i$；
2. $i - 1 < j$ 时，本回合后场上还会有人存活，且最大血量为 $j - (i - 1)$。我们先枚举场上还有哪几个人活着，再确定死了的人的血量。显然本回合内死掉的人的血量取 $[1, i - 1]$ 中的任意整数均可，从而有：

$$
f(i,j) = \sum_{k = 1}^{i} \binom{i}{k} f(k, j - (i - 1)) \times (i - 1)^{i - k}
$$

时间复杂度为 $O(n^2x)$。

```cpp
// Problem: E. Arena
// Contest: Codeforces - Educational Codeforces Round 116 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1606/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
  for (int i = 2; i <= n; i++) // 还剩下一个人的情况显然不符合题意
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
  /*
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= x; j++) cerr << f[i][j] << ' ';
    cerr << endl;
  }
  */
  for (int i = 1; i <= x; i++) ans = (ans + f[n][i]) % MOD;
  cout << ans << endl;
  return 0;
}
```

---

## 作者：MinimumSpanningTree (赞：7)

[题目链接](https://www.luogu.com.cn/problem/CF1606E)

考虑 DP。看到 $500$ 这个数据范围，推测这个 dp 是三维状态 $O(1)$ 转移或者二维状态一重循环转移。

* 状态表示：$dp_{i,j}$ 表示 $i$ 人存活，最大血量为 $j$ 时，最后无人生还的方案数。

* 状态转移：

	* 因为当 $i-1\ge j$ 时，必定无人生还，所以所有方案都能满足无人生还的条件，即 $j^i$，但要满足最大血量为 $j$，故需要减去 $(j-1)^i$。
    
    * 所以当 $i-1\ge j$ 时，$dp_{i,j}=j^i-(j-1)^i$。
    
    * 因为当 $i-1<j$ 时，必定有人活下来，但无法知道活下来的数量。我们可以枚举活下来的人数 $k$，由于每个人减去的血量是相同的，所以最大血量的人还是原来那个，最大血量变为 $j-(i-1)$。但我们并不知道活下来的是哪 $k$ 个，所以还要乘 $C^k_i$。显然死的人的血量需要在 $1\sim i-1$ 这个区间内，故乘 $(i-1)^{i-k}$。
    * 所以当 $i-1<j$ 时，$dp_{i,j}=dp_{k,j-(i-1)}\times C^k_i\times(i-1)^{i-k}$。
    
* 答案在哪：显然我们需要的方案是满足 $n$ 个人，血量在 $[1,x]$ 的，但没有对最大的血量做出要求，故 $ans=\sum_{i=1}^xdp_{n,i}$。

另外由于 dp 部分时间复杂度已经是 $O(n^3)$ 的，所以求组合数和幂的部分需要分别使用杨辉三角和快速幂优化。

几个需要注意的点：

* 开 long long。

* 取模要模够。

* 怎么这年头还有卡 `/=2` 要写 `>>=1` 才能过的。一开始写了 `b/=2` TLE 了调了半天，改成 `b>>=1` 就过了。不过可能确实是我个人习惯不好的问题。 

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

---

## 作者：漠寒 (赞：6)

## 题意

有 $n$ 个人，他们要进行下面的进程：每轮设存活 $i$ 个人，那么每个人会减少 $i-1$ 的血量，血量小于等于零就会被淘汰，现在需要你给他们每个人设置一个在 $[1,x]$ 之间的初始血量，使得某轮游戏结束后，无人生还，求这样的方案数。

## 分析

考虑 dp 处理，以 $f[i,j]$ 表示还存活 $i$ 个人，且他们都已经受到 $j$ 点伤害，已被淘汰的人的血量的方案数。因此我们每次考虑转移时，向目标转移的倍数一定是由本次决策淘汰的人决定的，容易知道，当枚举到 $f[i,j]$ 作为被转移的值时，目标的第二维一定是 $\min(j+i-1,x)$，所以只需枚举第一维，所以时间复杂度是 $O(n^3)$。

然后本次被淘汰的人的血量范围为 $[j+1,i+j-1]$。因为题目中说了每个人各不相同，所以还要乘上组合数，从 $i$ 个人中选 $k$ 个人存活，再乘上 $f[i,j]$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
inline void read(int &res){
	char c;
	int f=1;
	res=0;
	c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int n,x;
int f[505][505];
int c[505][505];
inline int qpow(int ds,int zs){
	int ans=1;
	while(zs){
		if(zs&1)ans=ans*ds%mod;
		ds=ds*ds%mod;zs>>=1;
	}
	return ans;
}
signed main()
{
	read(n);read(x);
	c[0][0]=1;
	for(int i=1;i<=500;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;//预处理组合数 
	}
	f[n][0]=1;
	for(int i=n;i>=2;i--){//不枚举1，不合法 
		for(int j=0;j<=x;j++){
			if(!f[i][j])continue;
			if(j>=x)continue;//小剪枝 
			for(int k=i;k>=0;k--){
				f[k][min(i+j-1,x)]+=f[i][j]*c[i][k]%mod*qpow(min(i+j-1,x)-j,i-k)%mod;//转移 
				if(f[k][min(i+j-1,x)]>=mod)f[k][min(i+j-1,x)]-=mod;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=x;i++){
		ans=(ans+f[0][i])%mod;
	}
	cout<<ans;
	return 0;
}


```


---

## 作者：智子 (赞：4)

## 题意

竞技场里有 $n$ 个英雄，每个英雄的生命值为 $a_i$（$1 \leq a_i \leq x$）。每一次战斗中，每个英雄都会对其他所有英雄造成 $1$ 点伤害，生命值降到 $0$ 后英雄就会退场，如果若干次战斗后只剩下一个英雄，这个英雄就是赢家。

求有多少种生命值方案使得最后没有赢家，答案模 $998244353$。两种方案不同当且仅当至少有一个英雄的生命值不同。

## 思路

直接思考没有赢家的方案数似乎没什么思路，我们不妨考虑计算有赢家的方案数。

定义 $f_{i, j}$ 为有 $i$ 个英雄，生命值最大为 $j$ 的方案数，就可以得到状态转移方程：

$$f_{i, j} = \sum_{k = 0}^{i - 1}f_{i - k, j - i + 1}(i - 1)^k C_i^k$$

其中 $k$ 为这一次战斗退场的英雄数。

要注意的一点是，这道题的时限会导致一般的快速幂不能过。我采取的方式是对幂进行预处理，具体内容参见代码。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 500 + 5;
const int MOD = 998244353;

long long C[MAXN][MAXN], f[MAXN][MAXN], qpow[MAXN][MAXN];
int n, m;

void init() {
	C[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
	}
	for(int i = 1; i < MAXN; i++) {
		qpow[i][0] = 1;
		for(int j = 1; j < MAXN; j++) {
			qpow[i][j] = qpow[i][j - 1] * i % MOD;
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	init();
	for(int j = 1; j <= m; j++) {
		f[1][j] = j;
		f[2][j] = j * (j - 1);
	}
	for(int i = 3; i <= n; i++) {
		for(int j = i; j <= m; j++) {
			for(int k = 0; k < i; k++) {
				f[i][j] = (f[i][j] + (f[i - k][j - i + 1] * qpow[i - 1][k]) % MOD * C[i][k] % MOD) % MOD;
			}
		}
	}
	printf("%lld\n", ((qpow[m][n] - f[n][m]) % MOD + MOD) % MOD);
	
	return 0;
}

```

---

## 作者：LinkZelda (赞：3)

- **题意**：

给定 $n,m$，表示有 $n$ 个英雄，每个英雄有一个初始血量 $a_i(1\leq a_i\leq m)$，每轮战斗中，每个英雄会对其他的每一个活着的英雄造成 $1$ 点伤害，每轮中血量 $<1$ 的英雄死亡。若最后剩下一个英雄，则认为这个英雄胜利。

求有多少种初始血量满足没有一个英雄胜利,两个方案不同当且仅当至少有一个英雄血量不同。

$n,m\leq 500$。

- **做法**：

容易发现每个英雄在每轮结束时受到的伤害是一样的，那么设 $dp_{i,j}$ 表示还有 $i$ 个英雄没死，对每个活着的英雄的总伤害为 $j$ 的方案数。

我们要保证没有一个英雄剩下，那么在 `dp` 过程中忽略掉 $i=1$ 的转移即可。现在只需要考虑 $i>1$ 应该如何转移。

每一轮对每个英雄会造成的伤害显然是 $i-1$（因为自己不会打自己），然后我们枚举剩下多少个英雄，设为 $k$，那 $dp_{i,j}$ 可以转移到 $dp_{k,\min(m,j+(i-1))}$，但是因为每个英雄都是有标号的，所以转移的时候还要乘上 ${i\choose i-k}\times {(\min(j+(i-1),m)-j)^{i-k}}$。

时间复杂度为 $O(n^2m\log m)$。

有一个小细节就是，当 $dp_{i,j}=0$ 时，我们应该直接跳过而不是继续向后转移，不加上这个剪枝貌似会被卡掉。

- [代码](https://www.luogu.com.cn/paste/cmu8etn7)

---

## 作者：Diana773 (赞：3)

# 题意简述
- 有 $n$ ( $2 \le n \le 500$ ) 个英雄，每个英雄初始有一个大于等于 $1$ 而小于等于 $x$ ( $1 \le x \le 500$ )的体力值，英雄的体力值严格小于 $1$ 时死亡。

- 给英雄设定初始体力以满足以下条件：
  - 每一回合所有英雄减少 $a-1$ 点体力，$a$ 为当前英雄存活数量。
  
  - 持续进行上述操作，直至英雄全部死亡，并保证不存在仅有一名英雄存活的情况出现。
  
- 输出合法的方案数量对 $998244353$ 取模的值。
 
# 题目分析

- 观察本题数据范围，可以考虑动态规划，假设 $dp[n][x]$ 为有 $n$ 个英雄，每个英雄体力值大于等于 $1$ 且小于等于 $x$ 的方案数。 

- 当 $ n = 2 $ 时，两个英雄每回合都减少一点体力，只有在两个英雄体力相等时满足条件，方案数明显为 $x$。

- 当 $ x < n $ 时，所有英雄会在第一回合后死亡。方案数明显为 $x^n$。

- 当 $ x \geq n $ 时
   - 先考虑一回合后有英雄存活情况，设 $i$ 个英雄死亡，选择死亡英雄的位置有 $\dbinom{n}{i}$ 种方案，死亡体力分配有 $(n-1)^i$ 种方案。活下去的英雄转移到 $n-i$ 个英雄存活，每个英雄体力值大于等于 $1$ 且小于等于 $x-(n-1)$ 的状态。$i$ 可从 $0$ 到  $n-2$ 取值，这种情况方案数为 
   $\sum_{i=0}^{n-2}\dbinom{n}{i}(n-1)^i dp[n-i][x-(n-1)]$
   - 一回合后无英雄存活，方案数明显为 $dp[n][n-1]$

- 初始状态：$dp[2][x] = x$ 
- 转移方程:

$$    
dp[n][x]=\left\{   
	\begin{aligned}

	 x^n \quad x<n\\        
	dp[n][n-1]+\sum_{i=0}^{n-2}\dbinom{n}{i}(n-1)^i dp[n-i][x-(n-1)] \quad x\geq n\\

	\end{aligned}   

	\right
	.   
$$

# 参考代码

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

const long long mod=998244353;
long long cc[1010][1010];
long long ans[1010][1010];
long long n,m;

long long power(long long a,long long n) //快速幂 
{
    long long anss=1;
    while(n>0) 
    {
        if(n&1) 
        {
            anss*=a;
            anss=anss%mod;
        }
        a=(a*a)%mod;
        n/=2;
    }
    return anss;
}


int main()
{
	ios::sync_with_stdio(false);
	cc[1][1]=1;
	for (int i=2; i<=510; i++) //预处理组合数 
	  for (int j=1; j<=i; j++)
	    cc[i][j]=(cc[i-1][j-1]+cc[i-1][j])%mod;
	
	for (int i=1; i<=501; i++)
	  ans[2][i]=i;
	for (int i=3; i<=501; i++)
	  for (int j=1; j<=501; j++)
	  {
	   	if (j<i)
		  ans[i][j]=power(j,i);
		else
		{
			for (int k=0; k<=i-2; k++)
			  ans[i][j]=(ans[i][j]+(cc[i+1][k+1]*power(i-1,k))%mod*ans[i-k][j-(i-1)]%mod)%mod;
			ans[i][j]=(ans[i][j]+ans[i][i-1])%mod;
		}
	  }
	  
	cin>>n>>m; 
	cout<<ans[n][m];
	
	return 0;
}
```

---

## 作者：dontwannacry (赞：2)

### 思路：
当场上还剩下 $L$ 人时，每个英雄都扣了**相同的** $B$ 点血，且该回合还会扣 $L-1$ 点血。也就是说，一个英雄在该回合有 $L-1$ 种死法。

考虑构造状态进行动态规划。状态为 $dp_{B,L}$，一维为还剩下 $L$ 个人，一维为已经扣掉的血量 $B$ 。考虑这个回合死了 $K$ 个英雄，则总的死亡方案数为 $C_L^K(L-1)^Kdp_{B,L}$。

即 $dp_{B,L}$ 对 $dp_{B+L-1,L-K}$ 的贡献为 $C_L^K(L-1)^Kdp_{B,L}$。

但是要考虑特殊情况：当 $B+L-1>X$ 时由于血量上限的限制，在这一回合所有人都会直接死掉，总死亡方案数为 $(X-B)^Ldp_{B,L}$。($K=L$，人都死光了。)

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int N,X;long long dp[510][510],C[510][510],fac[510],ANS;
long long POW(long long A,long long B){
	long long res = 1,st = A;
	if(A == 0) return 0;
	while(B){
		if(B&1) res = res*st%MOD;
		st = st*st%MOD;
		B /= 2;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> X;
	fac[0] = 1;
	for(int i = 1;i <= N;++i){fac[i] = fac[i-1]*i%MOD;}
	C[0][0] = 1;
	for(int i = 0;i < N;++i){
		for(int j = 0;j <= i;++j){
			C[i+1][j] = (C[i][j]+C[i+1][j])%MOD;
			C[i+1][j+1] = (C[i][j]+C[i+1][j+1])%MOD;
		}
	}
	dp[0][N] = 1;
	for(int B = 0;B <= X;++B){
		for(int L = N;L >= 2;L--){
			if(B+L-1 <= X){
				for(int K = 0;K <= L;++K){
					dp[B+L-1][L-K] = (dp[B+L-1][L-K] + (dp[B][L]*C[L][K])%MOD*POW(L-1,K))%MOD;
				}			
			}else{dp[X][0] = (dp[X][0]+dp[B][L]*POW(X-B,L))%MOD;}
		}
	}
	for(int i = 0;i <= X;++i) ANS = (ANS+dp[i][0])%MOD;
	cout << ANS;
	return 0;
}
```

---

## 作者：IceKylin (赞：1)

### CF1606E Arena 题解

简单题。

设计状态 $f(n,k)$ 表示当前场上有 $n$ 个存活着的英雄，其中最大血量为 $k$ 的合法方案总数。

$n=1$ 显然不合法，所以下面直接考虑 $n\ge2$ 的情况。

对于状态 $f(n,k)$，在一个回合过后，每个英雄都将扣除 $(n-1)$ 点单位血量，所以血量小于 $n$ 的英雄都将不再存活。

分类讨论：

1. 当 $n\le k$ 时，此时在一个回合后，场上必然有英雄存活。

考虑枚举有多少个英雄血量小于 $n$。设有 $i$ 个，则有 $\displaystyle{n\choose i}$ 种选择英雄的方式，对于不再存活的 $i$ 个英雄，血量在 $[1,n-1]$ 之间任意赋值。状态将转移至 $f(n-i,k-n+1)$。

所以有：

$$\displaystyle f(n,k)=\sum_{i=0}^{n-1}{n\choose i}(n-1)^if(n-i,k-n+1)$$

2. 当 $n>k$ 时，此时在一个回合后，场上没有英雄存活。

考虑每个英雄的血量，除去某个英雄的血量必须为 $k$ 外，其余英雄的血量在 $[1,k]$ 之间任意赋值。

但这样并不好计算，换种角度思考，设状态 $g(n,k)$ 表示当前场上有 $n$ 个存活着的英雄，其中最大血量 **小于等于** $k$ 的合法方案总数。显然，当 $n>k$ 时，有 $g(n,k)=n^k$。

那么有 $f(n,k)=g(n,k)-g(n,k-1)=n^k-(n-1)^k$。

讨论结束，最终答案即为 $\displaystyle\sum_{i=1}^xf(n,i)$。

---

## 作者：Genius_Star (赞：1)

### 题意：

现有 $n$ 位勇士，生命值在 $[1,x]$ ，每回合所有勇士减少 $t-1$ 点生命值，其中 $t$ 是生命值为正的勇士数量。

问：有多少种分配各勇士生命值的方法，可以使得最终所有勇士生命值均降为 $0$ 及以下。

### 思路：

我们反向考虑最终剩余一位勇士的方案数，因为数据很小，容易想到用动态规划求解，设 $dp_{i,j}$ 为 $i$ 位勇士，生命值都在 $j$ 以内，最终剩余一位勇士的方案数。

考虑初始状态 $dp_{1,i}=i$，只有一个勇士，随便选血量，都只是剩余一位勇士，所以方案数为 $i$。

然后考虑转移，但是我们发现有点儿不好转移，因为我们不知道在有 $i$ 位勇士，生命值都在 $j$ 以内的情况下，这一轮有多少个勇士生命值会降为 $0$ 及以下。

所以，我们新定义一个 $k$，表示在这 $i$ 位勇士中有 $k$ 位勇士血量值在 $i$ 以下，为什么要这么定义呢？

因为这一轮有 $i$ 位勇士，生命值都是正的，所以这一轮过后所有勇士的生命都要减去 $i-1$，现在我们定义的 $k$ 就相当于这一轮过后生命值降为 $0$ 以下的人数。

这样我们就知道了这一轮剩下的人数 $i-k$，则我们可以由 $dp_{i-k,???}$ 转移而来，现在求问号，因为这 $i$ 个勇士中最大的生命值可以是 $j$，这一轮要减去 $i-1$ 的血量，得到剩下的勇士中最大血量为 $j-i+1$，则这一轮过后生命值为正的勇士的方案为 $dp_{i-k,i-j+1}$。

然后在加上我们对于 $k$ 个勇士分配的血量的方案为 $(i-1)^k$（因为这 $k$ 个勇士的血量要在 $[1,i-1]$ 之间），然后还有在这 $i$ 名勇士之中选出 $k$ 名勇士的方案，即 $C_i^k$，根据乘法原理，都需要乘在一起。

就可以得到状态转移方程：

$$dp_{i,j}=dp_{i,j}+dp_{i-k,j-i+1} \times (i-1)^k \times C_i^k$$

至于求组合数的话，可以根据递推公式 $O(n^2)$ 计算：

$$C_i^j=C_{i-1}^{j-1}+C_{i-1}^j$$

现在我们考虑如何求答案，首先求出生命值分配的总方案数为 $x^n$，则我们可以减去不满足条件的（即有勇士剩余的方案数，因为有勇士剩余那就只会剩余一个），那么我们最终的答案就是：

$$x^n-dp_{n,x}$$

时间复杂度为：$O(n^2 \times x)$。

~~注意，可以不用龟速乘，不会爆 long long，用了还会 TLE！~~

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=505;
const ll mod=998244353;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,x;
ll C[N][N],dp[N][N];
ll qpow(ll a,ll b){ //快速幂 
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
void init(){ //递推求组合数 
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
	for(int i=1;i<=x;i++) //初始状态 
	  dp[1][i]=i;
	for(int i=2;i<=n;i++){ //状态转移 
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


---

## 作者：_Diu_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1606E)

[CF 的传送门](https://codeforces.com/contest/1606/problem/E)

## dp

看到数据范围，不难想到可能可以用 $n^3$ 的 dp。

设状态 $f_{i,j}$ 表示 $i$ 个英雄，每个英雄的血量 $\in [1,j]$。

则答案即为 $f_{n,x})$。

我们发现，这一局下来，不管如何，每个英雄的血量都会减少 $i-1$ 格。

我们可以枚举有多少个英雄血量是小于等于 $i-1$ 的。

也就是枚举这一局下来有多少个英雄壮烈牺牲。

假设有 $k$ 位英雄壮烈牺牲，那么这一局之后会有 $i-k$ 个英雄，每个英雄血量 $\in [1,j-i+1]$。

牺牲的 $k$ 位英雄可以从 $i$ 个位置里面随便挑位置，共 $C_n^k$。

牺牲的 $k$ 位英雄可以从 $[1,i-1]$ 这些血量中任选一个，共 $(i-1)^k$。

全部乘起来就是这一次的贡献。

注意特盘一下 $j<i$ 的情况，这样一来英雄们会全军覆没。

## code

我写成了递归形式，个人觉得这样写更容易一些。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510,p=998244353;
int n,x,f[N][N],fac[N],ifac[N];
int qpow(int x,int y){
	int m=1;
	for(;y;y>>=1,x=x*x%p)if(y&1)m=m*x%p;
	return m;
}
int C(int n,int m){
	return fac[n]*ifac[m]%p*ifac[n-m]%p;
}
int dp(int n,int x){
	if(n==0)return 1;
	if(n==1)return 0;
	if(x<=0)return 0;//注意特盘如果英雄们全军覆没的情况
	if(f[n][x]!=-1)return f[n][x];
	int ans=0;
	for(int i=0;i<=n;i++)ans=(ans+dp(i,x-n+1)*qpow(min(x,n-1),n-i)%p*C(n,i)%p)%p;
	return f[n][x]=ans;
}
signed main(){
	memset(f,-1,sizeof(f));
	scanf("%lld%lld",&n,&x);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%p,ifac[i]=qpow(fac[i],p-2);
	printf("%lld\n",dp(n,x));
}
```

---

