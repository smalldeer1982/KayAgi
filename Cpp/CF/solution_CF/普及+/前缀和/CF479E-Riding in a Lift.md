# Riding in a Lift

## 题目描述

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
5 2 4 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 3 4 1
```

### 输出

```
0
```

# 题解

## 作者：gxy001 (赞：15)

考虑 $\text{dp}$。

### 状态转移方程

---

我们定义 $f_{i,j}$ 为走到第 $i$ 层，共走了 $j$ 次的方案数，容易得到转移方程：

$$f_{i,j}=\sum\limits_{k=down}^{up} f_{k,j-1}\ [k!=i]$$

其中 $down$ 为能走到 $i$ 层的下界，$up$ 为上界。

时间复杂度 $O(n^2k)$，显然无法 $\text{A}$ 掉此题。这时，有经验的 $\text{OIer}$ 就会发现，这是可以用前缀和优化的。我们设 $s_{i,j}=\sum\limits_{k=1}^if_{k,j}$，得到新的转移方程：

$$f_{i,j}=s_{up,j-1}-s_{down-1,j-1}-f_{i,j-1}$$

时间复杂度 $O(nk)$，可以 $\text{AC}$。

### 一些细节

---

显然，由于 $\mid x-y\mid <\mid x-b\mid $ 的限制，你只能在 $b$ 的一侧运动，那么，我们可以将 $b$ 层当做 $0$ 层。

```cpp
if(a>b) n-=b,a-=b;
else n=b-1,a=b-a;
```

这样，我们就可以快速的求出 $up$ 和 $down$ 了，$up=n$，$down=\lfloor\frac i 2\rfloor+1$。

---

初始化：$f_{a,0}=1$

---

我们注意到，$j$ 次的方案数只依赖于 $j-1$ 次，所以我们可以采用滚动数组对空间进行优化。

### 代码
---
```cpp
#include<cstdio> //for printf,scanf
#include<algorithm> //for min
int const mod=1000000007;
long long n,k,a,b,f[5010],s[5010];
int main(){
	scanf("%lld%lld%lld%lld",&n,&a,&b,&k);
	if(a>b) n-=b,a-=b;
	else n=b-1,a=b-a;
	f[a]=1;
	for(int i=a;i<=n;i++)s[i]=1;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++) f[j]=(s[n]-s[j>>1]-f[j]+mod+mod)%mod;
		for(int j=1;j<=n;j++) s[j]=(s[j-1]+f[j])%mod;
	}
	printf("%lld",s[n]);
	return 0;
}

```

---

## 作者：zhaozixu2006 (赞：4)

### 题目链接：[戳这里](https://www.luogu.com.cn/problem/CF479E)

### 题目大意

有 $n$ 个点，给定起点，有一个点不能到达，每个点都可以移动到一定范围内的点，一共移动 $k$ 次，问有多少种方案。

### 开始解题

观察到 $n$ 和 $k$ 都很小，题目充斥着很浓的 $dp$ 的味道，所以我们首先考虑 $dp$。

开始设状态：设 $f_{i,j}$ 表示第 $i$ 步走到 $j$ 的方案数。

设 $l$ 为能到达的最高的点, 设 $r$ 为能到的最小的点。

开始想转移：$f_{i+ 1,j}=$ $\sum_{k = l}^{r} f_{i,k}$

这样复杂度就是 $O(n^2k)$。

很明显会超时，下面考虑优化。

注意到转移的本质就是一个区间加法，于是考虑差分优化。

所以转移方程就转化为：

$f_{i + 1, l}$ = $f_{i + 1, l}$ + $f_{i,j}$

$f_{i + 1, r}$ = $f_{i + 1, r}$ - $f_{i, j}$

同时还要注意亿点细节：

1. 如果从 $l$ 到 $r$ 包含 $j$ 要再做一次差分把 $j$ 去掉。

2. 不能到 $b$ 点。

### 代码如下

```cpp
/*

　　　　　／＞　   フ
　　　　　| 　_　 _|
　 　　　／`ミ _x 彡
　　 　 /　　　 　 |
　　　 /　  ヽ　　 ?
　／￣|　　 |　|　|
　| (￣ヽ＿_ヽ_)_)
　＼二つ

*/
#include<bits/stdc++.h>
using namespace std;

long long read()
{
    long long x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}

const int mod = 1e9 + 7;

int n, a, b, k, ans;

int dp[5010][5010];

int main()
{
	n = read(), a = read(), b = read(), k = read();
	dp[0][a] = 1;//初始化 
	for(int i = 0; i <= k; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(j == b) continue;//不能到达 b 点 
			int dis = abs(j - b);//能到达的最远距离 
			int l = max(1, j - dis + 1);//左端点 
			int r = min(n + 1, j + dis);//右端点 + 1
			dp[i + 1][l] = (dp[i + 1][l] + dp[i][j]) % mod;
			dp[i + 1][r] = (dp[i + 1][r] - dp[i][j] + mod) % mod;//差分 
			if(l <= j && j <= r)//如果包含j，再做一次差分 
			{
				dp[i + 1][j] = (dp[i + 1][j] - dp[i][j] + mod) % mod;
				dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % mod;
			}
		}
		for(int j = 1; j <= n; j++)//前缀和更新答案 
		{
			dp[i + 1][j] = (dp[i + 1][j] + dp[i + 1][j - 1]) % mod;
		}
	}
	for(int i = 1; i <= n; i++)//直接求解 
	{
		ans += dp[k][i];
		ans %= mod;
	}
	cout << ans;
    return 0;
}

```

-----

### 小结

本题做开始的 $dp$ 其实并不难想，主要是把区间操作转化为前缀和这一步的思维难度比较大，第一次遇见可能难以想到，建议读者反复思考。


---

## 作者：Crab_Dave (赞：3)

## CF479E Riding in a Lift 题解

只会做1900的水题，被踩爆了/kk

+ 题意

  有一栋大楼，总共有 $n$ 层，一开始你处于第 $a$ 层, 限定第 $b$ 层无法到达。你将坐 $k$ 次电梯，每次可以从第 $x$ 层到第 $y$ 层，但是需要满足 `x!=y&&abs(x-b)>abs(x-y)`，乘坐完 $k$ 次电梯后会得到一个到达楼层的序列，求这个序列的方案数，答案模1e9+7。

+ 思路

  首先观察到答案与 `a>b` 或 `a<b` 无关，只与两点间的距离有关。

  于是我们首先对 `a>b` 的情况，将整个区间翻转一遍，这样就只讨论一种情况了。

  观察到数据范围大概是 $n^2$ 的，于是考虑设二维状态。

  设 `dp[i][k]` 表示当前在 $a$ 位置，走了 $k$ 步的方案数。

  显然边界条件为 `dp[a][0]=1`。

  根据题意我们列出大致方程的思路：

  ```cpp
  for(k=1->K)
      for(i=1->b){
          dp[i][k]+=(所有i左边的dp[][k-1]值)
          dp[i][k]+=(i右边到i和b的中点的dp[][k-1]值)
      }
  ```

  注意，**`i和b的中点` 指 `(i+b-1)/2`**，请自己思考为什么。

  观察到给 $x$ 位置贡献的总是**连续的一段区间**，考虑前缀和优化。

  然后这题就没了（确信

+ 代码

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  
  const int maxn=5005;
  const int mod=1e9+7;
  int n,a,b,kkk,dp[maxn][maxn],sum[maxn][maxn];
  void mo(int &x){while(x>mod)x-=mod;}
  
  signed main(){
  	scanf("%d%d%d%d",&n,&a,&b,&kkk);
  	if(a>b)a=n-a+1,b=n-b+1;
  	dp[a][0]=1;
  	for(int K=1;K<=kkk;K++){
  		for(int i=1;i<b;i++)
  			mo(sum[i][K-1]=sum[i-1][K-1]+dp[i][K-1]);
  		for(int i=1;i<b;i++){
  			mo(dp[i][K]+=sum[i-1][K-1]);
  			mo(dp[i][K]+=(sum[(i+b-1)/2][K-1]-sum[i][K-1]+mod)%mod);
  		}
  	}
  	for(int i=1;i<=b;i++)mo(sum[i][kkk]=sum[i-1][kkk]+dp[i][kkk]);
  	printf("%d\n",sum[b][kkk]);
  	return 0;
  }
  ```

  

---

## 作者：XTianShuo (赞：2)

提供一种不一样的解法，不需要对 $a,b$ 进行操作  


## 算法解释
前几篇题解都使用的前缀和，用以前的状态更新现在的状态，这里我们使用差分并用现在的状态更新未来的状态。  
首先，我们定义状态为 $f(i,j)$，走 $i$ 步达到 $j$ 层的方案数，最后只需要将 $f(p,j)$ $j\in[1,n]$ 累加起来即可。

易得朴素的状态转移方程：
$$f(i+1,j)=\sum\limits_{k=l}^rf(i,k)$$
$$k \ne i$$
$$l=\max\{j-p+1,1\}$$
$$r=\min\{j+p-1,n\}$$
 
好了，现在到这里，复杂度为 $O(n^2p)$，你可以过五个点了，我们还需要继续优化。

状态无法继续优化，我们把优化的重点放在决策变量 $k$ 上，我们可不可以不枚举 $k$ 呢？是可以的。  
我们可以在求解 $f(i,j)$ 的时候就预处理出来 $f(i,j)$ 可能更新的那些状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/v1gk8unt.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
$+$ 的位置为 $\max\{j-p+1,1\}$,$-$ 的位置为 $\min\{j+p,n\}$。  
为什么是 $j-p+1$ 和 $j+p$ 呢？  
正如上所说，我们利用的差分思想，$+$ 是能更新 $f(i+1,j)$ 的层数左端点，而 $-$ 是其右端点加一。  
  
  
如图，红色的 $f(i,j)$ 为当前枚举到的状态，蓝色中的区间是它要更新的状态，在上述朴素算法中，每次求解它要更新的状态时，都要枚举一遍它，很费时，我们现在只需要更新一遍，最后求一遍前缀和即可。  
现在的复杂度为 $O(np)$ 可通过此题。

## code
代码中在重点部分有注释。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5010,P=1e9+7;

int n,a,b,k;
int f[N][N];

int main()
{
	scanf("%d%d%d%d",&n,&a,&b,&k);
	f[0][a]=1;
	for(int i=0;i<k;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(j==b)	continue;
			int d=abs(j-b);
			int l=max(1,j-d+1);
			int r=min(n+1,j+d);
			f[i+1][l]=(f[i+1][l]+f[i][j])%P;
			f[i+1][r]=((f[i+1][r]-f[i][j])%P+P)%P;
			//差分
			if(j>=l&&j<r)
			{
				f[i+1][j]=(f[i+1][j]-f[i][j]+P)%P;
				f[i+1][j+1]=(f[i+1][j+1]+f[i][j])%P;
			}
			//如果j在[l,r)的话，我们需要在差分数组中把j删去，因为它不能不走
		}
		for(int j=1;j<=n;j++)
			f[i+1][j]=(f[i+1][j]+f[i+1][j-1])%P;	
		//前缀和
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+f[k][i])%P;
	cout<<ans;
	return 0;
}
```
代码较丑，不喜勿喷

---

## 作者：_H17_ (赞：1)

## 题外话

模拟赛全场唯一想出正解，写挂之后直接没有拉爆全场的能力了。

## 题目分析

### 考虑朴素 DP

$f_{i,j}$ 表示走了 $i$ 步，到了 $j$ 的方案数。

答案是 $\sum\limits_{i=1}^{n} f_{k,i}$。

转移：$f_{i,j}=\sum\limits_{t=1}^{n} f_{i-1,t}\times[\lvert t-j \rvert<\lvert b-j\rvert \And t\ne j]$。

特别地：$f_{i,b}=0$，初始状态是：$f_{0,a}=1$。

### 前缀和优化

注意到有效的 $t$ 是连续的一段，考虑前缀和优化。

设 $S_i(l,r)=\sum\limits_{j=l}^{r}f_{i,j}$。

转移变为 $f_{i,j}=S_{i-1}(\operatorname{getmin}(j),\operatorname{getmax}(j))-f_{i-1,j}$。

这里如何求得最小、最大？

分类讨论 $j<b,j>b$。

显然 $j<b$ 时，$1$ 是最小的，$\lvert 1-j \rvert<\lvert 1-x \rvert$；最大的是 $x,j$ 的中点，由于严格要求小于，这里向上取一位（**注意不是向上取整**）。

$j>b$ 同理，不在阐述，详细请看代码。

## 避坑

考试的时候本地不会爆出一些 `RE`，一定要滚动数组，不然会炸死。（也怪我太粗心了，这个都忘了算了。）

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int p=1e9+7,N=5001;
int n,k,a,b,f[N],s[N];
int query(int l,int r){
    return(s[r]-s[l-1])%p;
}
int get_min(int x){
    if(x<b)
        return 1;
    int t=x+b;
    if(t&1)
    	return(t+1)>>1;
    return(t>>1)+1;
}
int get_max(int x){
    if(x>b)
        return n;
    int t=x+b;
    if(t&1)
    	return t>>1;
    return(t>>1)-1;
}
signed main(){
    cin>>n>>a>>b>>k;
	f[a]=1;
	for(int i=1;i<=k;i++){
        for(int j=1;j<=n;j++)
            s[j]=s[j-1]+f[j],s[j]%=p;
		for(int j=1;j<=n;j++)
            f[j]=query(get_min(j),get_max(j))-f[j],f[j]%=p;
        f[b]=0;
	}
	for(int i=1;i<=n;i++)
        s[i]=s[i-1]+f[i],s[i]%=p;
    cout<<(s[n]+p)%p;
	return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

显然是 dp。

设 $f_{i,j}$ 表示 $i$ 层走了 $j$ 步则显然有暴力转移：
$$
f_{i,j}=\sum_{p=d}^u f_{p,j-1}
$$
特殊的，$p\neq i$。

发现一步之内能直接移动到的 $[d,u]$ 是一段区间，所以用一个可以维护区间和的数据结构来维护一下 $f$ 数组即可。

时间复杂度为 $O(n^2)$（前缀和）或者 $O(n^2\log n)$（线段树）。

---

## 作者：DPair (赞：1)

## 【思路】
首先看到统计方法数，考虑递推（当然你想叫DP也行）。

不难列出式子：

$$
dp[i]=\sum_{j=l}^{r}dp[j]-dp[i]
$$

其中 $l,r$ 表示能够到达 $i$ 位置的**最远**的两个点的坐标，然后由于不能停留，减去**我自己到达自己**的情况。

不难发现（~~其实我根本不熟练~~）这个式子可以前缀和优化。

设：

$$
sum[i]=\sum_{j=1}^idp[i]
$$

那么显然有：

$$
dp[i]=sum[r]-sum[l-1]-dp[i]
$$

然后只需要快速求出 $l,r$ 即可。

这里我们分两类讨论：

1、 $a > b$

此时由于 $|x-y|<|x-b|$ ，我们永远不可能到达 $y<b$ 的点，因此只需要考虑 $y > b$ 的点即可（也算是一种优化）

不难发现此时对于所有 $x > y$ ，由于 $y > b$ ，所以 $x - y > x - b$ ，一定可行，所以 $r=n$ ，下面考虑 $l$ 。

此时 $x < y$ ，而 $x > b$ ，可得：

$$
y - x < x - b
$$
$$
y + b < 2x
$$
$$
\frac{y+b}2 < x
$$

然后找出最小的 $x$ 即可。

2、 $a < b$
与上面的推导方式类似，留给读者自行思考，最终结果在代码中有体现。

最终复杂度 $O(nk)$ ，可以通过本题。

## 【代码】
只展示关键部分。
```cpp
typedef long long LL;
const LL MOD = 1000000007;
int n, k, A, B;
LL dp[5010], sig[5010];

int main(){
    read(n);read(A);read(B);read(k);
    dp[A] = 1;
    for (register int i = 1;i <= n;i ++) sig[i] = sig[i - 1] + dp[i];
    if(A > B){//情况1
        for (register int t = 1;t <= k;t ++){
            for (register int i = B + 1;i <= n;i ++){
                int l = (B + i) / 2 + 1, r = n;//算出l,r
                dp[i] = (sig[r] - sig[l - 1] - dp[i] + MOD) % MOD;
            }
            sig[B] = 0;
            for (register int i = B + 1;i <= n;i ++) sig[i] = (sig[i - 1] + dp[i]) % MOD;
        }
        fprint((sig[n] - sig[B] + MOD) % MOD, 10);
    }
    else{//情况2
        for (register int t = 1;t <= k;t ++){
            for (register int i = 1;i < B;i ++){
                int r = (B + i - 1) / 2, l = 1;//算出l,r
                dp[i] = (sig[r] - sig[l - 1] - dp[i] + MOD) % MOD;
            }
            sig[0] = 0;
            for (register int i = 1;i < B;i ++) sig[i] = (sig[i - 1] + dp[i]) % MOD;
        }
        fprint(sig[B - 1], 10);
    }
}
```

---

## 作者：XXh0919 (赞：0)

一道简单的 dp。

### 解法

我们令 $dp_{i,j}$ 表示当前走了 $i$ 次，一共走了 $j$ 层的总方案数。那么总方案数就是所有能够走到当前第 $j$ 层的方案数之和。于是转移方程就显而易见：

$$dp_{i,j}=\sum_{k=l}^{r}{dp_{i-1,k}}[k\neq j]$$

方程中 $r$ 指最上面能走到的楼层，$l$ 指最下面能走到的楼层。

然后我们可以发现，其实我们所有能够走到当前第 $j$ 层的楼层是连续的一段，那么我们就可以想到用前缀和来优化。那么前缀和数组 $sum_i$ 表示的就是从第 $1$ 层走到第 $i$ 层所得到的方案数之和。那转移方程就变成了：

$$dp_{i,j}=\sum_{j=1}^{n}{sum_r-sum_{l-1}+dp_{i-1,j}}$$

接着我们可以发现，由于转移方程中所有状态只跟第 $i-1$ 这一维有关系，所以我们可以用滚动数组把这一维压掉。所以最终的转移方程就是：

$$dp_{j}=\sum_{j=1}^{n}{sum_r-sum_{l-1}+dp_{j}}$$

根据题意，我们可以这样来求 $l$ 和 $r$：如果当前楼层 $j$ 在 $b$ 层以下，那么最下面能走到的楼层就是第 $1$ 层，最上面能走到的楼层就是第 $\lfloor{\frac{j+b}{2}\rfloor}$ 层。相反，如果当前楼层 $j$ 在 $b$ 层以上，那么最下面能走到的楼层就是第 $\lceil{\frac{j+b}{2}\rceil}$ 层，最上面能走到的楼层就是第 $n$ 层。如果不太懂，可以自己画图理解。

不要忘了取模！不要忘了取模！不要忘了取模！

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pi pair<int,int>
#define mkp(a,b) make_pair((a),(b)) 
#define IOS cin.tie(0)->sync_with_stdio(0)
using namespace std;
const int N=5005+15,mod=1e9+7;

int n,a,b,k;
int sum[N],dp[N];
int ans;

signed main(){
	IOS;
	cin>>n>>a>>b>>k;
	dp[a]=1;
	rep(i,1,k){
		rep(j,1,n){
			sum[j]=(sum[j-1]+dp[j])%mod;
		}
		rep(j,1,n){
			int l,r;
			if(j<b){
				l=1;
				r=(j+b)%2==0?(j+b)/2-1:(j+b)/2;
			}else{
				l=(j+b)/2+1;
				r=n;
			}
			dp[j]=(sum[r]-sum[l-1]-dp[j]+mod)%mod;
		}
		dp[b]=0;
	}
	rep(i,1,n)ans+=dp[i],ans%=mod;
	cout<<(ans+mod)%mod<<endl;
	return 0;
}
```
祝各位大佬 NOIP2024 RP++！

---

## 作者：Kevin911 (赞：0)

~~一道大水题~~
## 思路
因为分 $k$ 轮，每轮之间可以转移，所以考虑 $dp$。

$dp[i]$ 表示这一轮以到达 $i$ 方案数。

不难发现，要分两种情况分类讨论。

1. $i>y$，即改点在实验室上方。那么可以转移的位置就是 $y$ 到 $i$ 的中点以上的部分（$\lceil \frac{i+y}{2}\rceil$ 到 $n$）

2. $i<y$，即改点在实验室下方。那么可以转移的位置就是 $i$ 到 $y$ 的中点以下的部分（$1$ 到 $\lfloor \frac{i+y}{2}\rfloor$）

然后可以整出一个时间复杂度 $O(kn^2)$ 的暴力代码。因为转移部分基本是连续的区间，可以考虑前缀和优化，最终时间复杂度 $O(kn)$。

注意一些细节：

1. 不能停留在原地，所以要减去原来的 $dp$ 值。
2. $\lvert x-y \rvert < \lvert x-b \rvert$，所以要注意重点的取舍问题。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5010,mod=1e9+7;
int dp[maxn],sum[maxn];
signed main()
{
	int n,x,y,k;
	cin>>n>>x>>y>>k;
	dp[x]=1;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+dp[i];
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<y;j++) dp[j]=(sum[(j+y-1)/2]-dp[j]+mod)%mod;
		for(int j=y+1;j<=n;j++) dp[j]=(sum[n]-sum[(j+y)/2]-dp[j]+mod)%mod;
		for(int j=1;j<=n;j++) sum[j]=(sum[j-1]+dp[j])%mod;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=(ans+dp[i])%mod;
	cout<<(ans+mod)%mod;
}
```

---

## 作者：白简 (赞：0)

### 题目大意
一栋楼有 $n$ 层，初始位置在 $a$ 层，你可以移动到的 $y$ 层满足 $\left|x-y\right|<\left|x-b\right|$。不可以走到 $b$ 层或留在原地，问一共走 $k$ 次，有多少种走法。
### 思路
考虑简单的 DP。

记 $dp_{i,j}$ 表示走到第 $i$ 层，走了 $j$ 次的方案数，$l,r$ 分别是能够走到第 $i$ 层的下界和上界，显然有：
$$dp_{i,j}=\sum_{k=l}^{r}dp_{k,j-1} \left[k  \neq i \right]$$
这个时间复杂度肯定爆炸，所以考虑前缀和优化。

记 $$\operatorname{sum}_{i,j}=\sum_{k=1}^i dp_{k,j}$$
这样我们刚才的转移方程就可以变成这样：
$$dp_{i,j}=\operatorname{sum}_{r,j-1}-\operatorname{sum}_{l-1,j-1}-dp_{i,j-1}$$
时间复杂度没问题了。

考虑空间，这道题需要开 `long long`，如果开两个二维的 `long long` 数组会炸空间。但由于本题有取模，我们可以考虑在计算过程中将变量转为 `long long`。

也可以选择滚动数组，观察状态转移方程，显然走 $j$ 次的方案数只与走 $j-1$ 次的方案数有关，可以滚掉，实测空间不到 1MB。
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int Mod = 1e9 + 7;

int n,k,a,b;

int dp[5050][5050],sum[5050][5050];
// dp[i][j]：走到 i 用了 j 步的方案数 
// sum：前缀和优化 

signed main() {
    cin >> n >> a >> b >> k;
    if(a > b) {
        n -= b;
        a -= b;
    }
    else {
        a = b - a;
        n = b - 1;
    }
    // 只能在 B 层的一侧活动 
    // 可以直接把 B 层当做 0 层，方便计算 
    dp[a][0] = 1;
    for(int i = a;i <= n; i++)
        sum[i][0] = 1;
    for(int i = 1;i <= k; i++) {
        for(int j = 1;j <= n; j++) 
            dp[j][i] = ((long long)sum[n][i - 1] - (long long)sum[j >> 1][i - 1] - (long long)dp[j][i - 1] + 2ll * Mod) % Mod;
        for(int j = 1;j <= n; j++) 
            sum[j][i] = ((long long)sum[j - 1][i] + (long long)dp[j][i]) % Mod;
    }
    cout << sum[n][k];
    return 0;
}
```

---

