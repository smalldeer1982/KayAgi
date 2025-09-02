# Memory and Scores

## 题目描述

Memory and his friend Lexa are competing to get higher score in one popular computer game. Memory starts with score $ a $ and Lexa starts with score $ b $ . In a single turn, both Memory and Lexa get some integer in the range $ [-k;k] $ (i.e. one integer among $ -k,-k+1,-k+2,...,-2,-1,0,1,2,...,k-1,k $ ) and add them to their current scores. The game has exactly $ t $ turns. Memory and Lexa, however, are not good at this game, so they both always get a random integer at their turn.

Memory wonders how many possible games exist such that he ends with a strictly higher score than Lexa. Two games are considered to be different if in at least one turn at least one player gets different score. There are $ (2k+1)^{2t} $ games in total. Since the answer can be very large, you should print it modulo $ 10^{9}+7 $ . Please solve this problem for Memory.

## 说明/提示

In the first sample test, Memory starts with $ 1 $ and Lexa starts with $ 2 $ . If Lexa picks $ -2 $ , Memory can pick $ 0 $ , $ 1 $ , or $ 2 $ to win. If Lexa picks $ -1 $ , Memory can pick $ 1 $ or $ 2 $ to win. If Lexa picks $ 0 $ , Memory can pick $ 2 $ to win. If Lexa picks $ 1 $ or $ 2 $ , Memory cannot win. Thus, there are $ 3+2+1=6 $ possible games in which Memory wins.

## 样例 #1

### 输入

```
1 2 2 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
1 1 1 2
```

### 输出

```
31
```

## 样例 #3

### 输入

```
2 12 3 1
```

### 输出

```
0
```

# 题解

## 作者：_Hugoi_ (赞：10)

[传送门](https://www.luogu.com.cn/problem/CF712D)

## 题意

A，B 两人玩一个游戏，两人玩 $t$ 轮。

每人每次随机且等概率从 $[-k,k]$ 中取一个数字加到总得分中，得分高者赢。

已知 A，B 初始分别有 $a,b$ 分，问 A 取得胜利的概率是多少。

答案乘 $(2k+1)^{2t}$，对 $1000000007$ 取模。

## 分析

若只取一次，则有 $(2k+1)$ 种方案。

 A，B 共取 $2t$ 次，则有 $(2k+1)^{2t}$ 种方案。

所以答案实际上就是在求方案数。

设 A 所取的所有数和为 $A_t$，B 所取的所有数的和为 $B_t$。

题意可转化为求 $a+A_t>b+B_t$ 的方案数。

考虑移项，得到 $a-b+A_t-B_t>0$。

由于取数范围是 $[-k,k]$，所以方案数其实与 $B_t$ 的正负无关。

可以这么考虑：$B_t$ 为几个整数之和，那么 $-B_t$ 就是这几个整数的相反数的和，那么方案数一定一样。

所以原式可转化为 $a-b+A_t+B_t>0$。

即求 $a-b+$ 任取 $2t$ 个数的和 $>0$。

所以可以 DP 了。

设 $f_i$ 为当前所取数和为 $i$ 的方案数。

显然 $f_i=\sum f_j(i-k\le j\le i+k)$。

可以前缀和优化一下。

负数下标怎么处理？所有下标加上 $(2 \times k \times t) $ 就好了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;// 2*k*t*2
const int mod=1e9+7;
#define int long long
int a,b,k,t,f[N],s[N],ans=0;
signed main(){
	cin>>a>>b>>k>>t;
	int n=2*k*t;
	f[n]=1;
	for(int i=1;i<=t*2;i++){
		s[0]=f[0];
		for(int j=1;j<=2*n+k;j++){
			s[j]=(s[j-1]+f[j])%mod;
		}
		for(int j=0;j<=k;j++){
			f[j]=s[j+k];
		}
		for(int j=k+1;j<=n*2;j++){
			f[j]=(s[j+k]-s[j-k-1]+mod)%mod;
		}
	}
	for(int i=n-a+b+1;i<=n*2;i++){
		ans=(ans+f[i])%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Melo_DDD (赞：3)

作为第一道独立做出来的紫题和第 $800$ AC，写篇题解纪念之。

# 题目大意

注意取任何一个数都是**随机且均等**的，这是解题的关键。

# 题目实现

思维好题，先推导一下：

设 A 的总得分是 $s_A$，B 的总得分是 $s_B$。 

那么根据题意有：

$$
s_A+a>s_B+b
$$

$$
\iff s_A-s_B>b-a
$$

大于号不好，我们转换一下：

$$
\iff s_A-s_B\ge b-a+1
$$

减号也不好，考虑如何转化：

我们注意到取任何数的概率和可能完全相同，所以 B **所有的数都取原来的相反数和原来是等价的**。

$$
\iff s_A+s_B\ge b-a+1
$$

我们发现这和两个人取的总和有关系了，那就讨论一下：

- 两个人共取了 $2\times t$ 次，所以总和值域在 $[-2\times t \times k,2\times t \times k]$ 之间。

- 有负数，不好，不方便当做下标，于是我们假设在数轴上，将原值域整体向右平移，变成 $[0,4\times t\times k]$，**原来的原点变成了 $2\times t\times k$**。

然后就是个简简单单的 dp，貌似大家都是从二维滚到一维？反正我是直接想到一维，挺好想的。

- 我们设 $f_i$ 表示取的总和是 $i$ 的方案数，初始时 $f_{2\times t\times k}=1$（表示开始时没取）。

- 发现可以使用前缀和优化。

- 考虑转移，由于每次取的数在 $[-k,k]$ 之间，所以对于当前的和 $sum$，在 $sum-k$ 和 $sum+k$ 之间的全部可以得到它，所以有转移方程 $f_{sum}=num_{sum+k}-num_{sum-k-1}$（$num$ 是前缀和数组）。

问题解决，注意答案不能全取，要使满足题意只能取总分 $\ge b-a+1$ 的情况（对应到平移后的数轴上是 $2\times t\times k+b-a+1$ 的右侧）。

## 代码

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std ;
#define int long long
const int N = 1e6 + 7 ;
int a ,b ,k ,t ,f[N] ,num[N] ,m ,ans ;
template <typename T> inline void read (T &x) {
	x = 0 ;
	char ch = getchar () ;
	while (! isdigit (ch)) {
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch xor 48) ;
		ch = getchar () ;
	}
}
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
signed main () {
	read (a) ,read (b) ,read (k) ,read (t) ;
	m = 4 * k * t ;
	f[2 * k * t] = 1 ;
	rep (i ,1 ,2 * t ,1) {
		rep (j ,1 ,m + k ,1) {
			num[j] = (num[j - 1] + f[j]) % mod ;
		}
		rep (j ,0 ,m ,1) {
			if (j - k - 1 < 0) {
				f[j] = num[j + k] % mod ;
				goto her ;
			}
			if (j + k > m) {
				f[j] = (num[m] - num[j - k -1] + mod) % mod ;
				goto her ;
			}
			f[j] = (num[j + k] - num[j - k - 1] + mod) % mod ;
			her : ; // 注意千万不能出界所以要判边界
		}	
	}
	rep (i ,0 ,m ,1) {
		if (i >= 2 * k * t + b - a + 1) {
			ans = (ans + f[i]) % mod ;
		}
	}
	return cout << ans << '\n' ,0 ;
}
```
###### 你是否承认卡芙卡和狼谷的美貌举世无双？

---

## 作者：泠小毒 (赞：3)

# Memory and Scores
AB两人玩一个游戏，两人玩t轮

每人每次随机且等概率从[-k,k]中取一个数字加到总得分中 得分高者赢

已知A B初始分别有a b分，问A取得胜利的概率是多少

为了避免小数精度问题答案*(2k+1)^t mod 1000000007
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190512/)
## 解法
因为[-k,k]是对称的，所以可以看做初始分数为a-b，玩2t轮，每轮从[-k,k]中选一个数字加到分数中，求分数为正的概率

这样就可以dp了，dp[i]=dp[j]的和(i-k<=j<=i+k)

发现复杂度很大，k方t方的样子，反正过不了

每次转移用前缀和来优化，就可以kt方了，刚好能过
## ac代码
```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int a,b,k,t,lim,ans=0,dp[410000],f[410000];
int main()
{
	scanf("%d%d%d%d",&a,&b,&k,&t),lim=k*t*2,dp[lim]=1;
	for(int i=1;i<=t*2;i++)
	{
		f[0]=dp[0];
		for(int j=1;j<=lim*2+k;j++)f[j]=(f[j-1]+dp[j])%mod;
		for(int j=0;j<=k;j++)dp[j]=f[j+k];
		for(int j=k+1;j<=lim*2;j++)dp[j]=(f[j+k]-f[j-k-1]+mod)%mod;
	}
	for(int i=lim-a+b+1;i<=lim*2;i++)ans=(ans+dp[i])%mod;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：TH911 (赞：1)

> [题目传送门](https://www.luogu.com.cn/problem/CF712D)

# 题意分析

$A,B$ 两个人的分数是独立的，也就是说，这两个人的分数**不会相互影响**。

那么我们就可以求出两个人的分数的方案数，然后把 $A$ 的分数大于 $B$ 的分数的方案数通过乘法原理计数即可。

记 $A_{i,j}$ 表示 $A$ 在第 $i$ 轮分数为 $j$ 的方案数。（$B$ 同理可得。）

则有 $A_{0,a}=1$，这也是边界。

考虑到每次的增量为 $x\in[-k,k]$，有：

$$
A_{i,j}=\sum_{l=-k}^kA_{i-1,j+l}
$$

状态量是 $\mathcal O(t\cdot kt)=\mathcal O\left(kt^2\right)$ 的，而转移是 $\mathcal O(k)$，这样总时间复杂度就是 $\mathcal O\left(k^2t^2\right)$，会 $\text{TLE}$。使用**前缀和**优化即可。

同理，求出 $B_{i,j}$ 的值后，就可以乘法原理求出总的 $A$ 的分数大于 $B$ 的方案数。

对于 $B_{i,j}$，显然有 $b-kt\leq j\leq b+kt$。

则总方案数为：

$$
\sum_{i=a-kt}^{a+kt}A_{t,i}\sum_{b-kt}^{i-1}B_{t,j}
$$

再搞一个前缀和优化即可。

***

一个细节：分数有可能为负，数组的下标也有可能为负；此时将数组的下标整体右移即可。

# AC 代码

时间复杂度：$\mathcal O\left(kt^2\right)$。

```cpp
//#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
using namespace std;
constexpr const int K=1000,T=100,P=1e9+7;
template<typename X>
struct specialArray{
	X a[(K*T<<1)+100];
	X& operator [](int p){
		return a[p+K*T+50];
	}
};
specialArray<int>A[T+1],sumA[T+1],B[T+1],sumB[T+1];
int a,b,k,t;
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>a>>b>>k>>t;
	A[0][a]=B[0][b]=1;
	for(int i=1;i<=a+k*t;i++){
		sumA[0][i]=sumA[0][i-1]+A[0][i];
	}
	for(int i=1;i<=b+k*t;i++){
		sumB[0][i]=sumB[0][i-1]+B[0][i];
	}
	for(int i=1;i<=t;i++){
		for(int j=a-k*t;j<=a+k*t;j++){
			A[i][j]=(1ll*sumA[i-1][min(j+k,a+k*t)]-sumA[i-1][max(j-k,a-k*t)-1])%P;
			sumA[i][j]=(1ll*sumA[i][j-1]+A[i][j])%P;
		}
	}
	for(int i=1;i<=t;i++){
		for(int j=b-k*t;j<=b+k*t;j++){
			B[i][j]=(1ll*sumB[i-1][min(j+k,b+k*t)]-sumB[i-1][max(j-k,b-k*t)-1])%P;
			sumB[i][j]=(1ll*sumB[i][j-1]+B[i][j])%P;
		}
	}
	int ans=0;
	for(int i=a-k*t;i<=a+k*t;i++){
		if(min(b+k*t,i-1)>=b-k*t){
			ans=(ans+1ll*A[t][i]*(sumB[t][min(b+k*t,i-1)]-sumB[t][b-k*t-1])%P)%P;
		}
	}
	if(ans<0){
		ans+=P;
	}
	cout<<ans<<'\n';
	
	cout.flush();
	
	/*fclose(stdin);
	fclose(stdout);*/
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

## 前言

等等等等，大家怎么写的都是 DP 啊，就我一个人傻乎乎写容斥原理吗？~~蒟蒻做完这题发现没有容斥题解就来补一发呗：）~~

## 思路

考虑我们要计算的问题可以通过枚举 $a$ 最终变成的值，计算 $b$ 变得比他小的方案数。那么我们要预处理的就是在 $t$ 回合中变成 $i$ 的方案数分别有多少种。不难写出以下代码：（不再做过多解释，不懂的可以学习以下插板法以及[这个](https://www.luogu.com.cn/blog/116664/solution-p5135)）

```cpp
for(int i=-k*t;i<=k*t;i++){
    f[i+k*t+1]=(f[i+k*t+1]+C(i+(k+1)*t-1,t-1))%mod;
}
```

可惜，我们会发现这串代码 `WA` 了，为什么呢？

我们会发现，这其中包含了许多不符合要求状态的计算，比如可能包含某一次增加了 $k$ 个以上的值，这明显是不符合要求的。

这时，我们会发现这个问题变成了一个插板+隔板距离限制的问题，是一个经典的容斥套路。

考虑计算不符合要求的，也就是先分给某一个 $k$ 个，然后将这一部分扣减。扣减完了，我们会发现有一定的重复计算，这时我们又要把固定某两个均大于 $k$ 的方案数给加上。不难发现这样间隔加减的问题本质是一个容斥。

所以，我们只需要暴力枚举固定几个大于 $k$ 即可。

复杂度 $O(kt^2)$，可以通过这一题。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int fac[5000005],inv[5000005];
const int Max=5000000;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=Max;i++) fac[i]=(fac[i-1]*i)%mod;
	inv[Max]=qp(fac[Max],mod-2);
	for(int i=Max-1;i>=0;i--) inv[i]=(inv[i+1]*(i+1))%mod;
} 
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return ((inv[j]*inv[i-j]%mod)*fac[i]%mod);
} 
int f[5000005];
int pre[5000005];
signed main(){
	init();
	int a,b,k,t;
	cin>>a>>b>>k>>t;
	for(int i=-k*t;i<=k*t;i++){
		for(int j=0;j<=t;j++){
			if(j%2==0){
				f[i+k*t+1]=(f[i+k*t+1]+C(i+(k+1)*t-1-j*(2*k+1),t-1)*C(t,j)%mod)%mod;
			}
			else{
				f[i+k*t+1]=(f[i+k*t+1]+mod-C(i+(k+1)*t-1-j*(2*k+1),t-1)*C(t,j)%mod)%mod;
			}
		}
	}
	for(int i=-k*t;i<=k*t;i++){
		pre[i+k*t+1]=pre[i+k*t]+f[i+k*t+1];
		pre[i+k*t+1]%=mod;
	}
	int ans=0;
	for(int i=-k*t;i<=k*t;i++){
		int to=a+i;
		int maxv=to-b-1;
		if(maxv+k*t+1<=0) continue;
		if(maxv+k*t+1>=2*k*t+2) maxv=k*t;
		ans=(ans+pre[maxv+k*t+1]*f[i+k*t+1]%mod)%mod;
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：二哥啃菜包 (赞：1)

## Description

$AB$两人玩一个游戏，两人玩 $t$ 轮

每人每次随机且等概率从 $[-k,k]$ 中取一个数字加到总得分中 得分高者赢

已知$A,B$初始分别有 $a,b$ 分，问A取得胜利的方案数是多少

答案 $\mod 1000000007$

$a,b,t \leqslant 100 ,k \leqslant 1000$

## Solution

直接考虑这题我们可以得到一个特别恶心的状态和一个转移：

$f[i][j][k]$ 表示前 $i$ 轮 $A$ 的分数是 $j$,$B$ 的分数是 $k$的方案数。

我们转移发现是 $100*(100*1000)*(100*1000)*1000*1000$~~（至少我只会这个复杂度的转移~~

这，谁顶的住。。。

我们优化一下这个状态我们发现其实这两个人的决策分别是什么对方案数的影响可以最后计算

换句话说就是这两个人的决策是独立的，我们可以分别考虑两个人的决策方案数，然后把他们乘起来。

那么状态变成了：

$f1[i][j],f2[i][j]$ 表示分别是 $A$ 和 $B$ 的分数是 $j$ 的方案数。那么我们每次转移只要枚举一下,当前对于 $A$,$B$ 选什么。

最后合并起来就好了。

复杂度 $100*(1000*100)*1000$ ~~(好像可以过的样子~~

先放一个暴力代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=105,M=N*1000*2,P=1000000007;
int dp1[2][M],dp2[2][M],sum1[M],sum2[M];

int main(){
    int a=0,b=0,k=0,t=0;
    scanf("%d%d%d%d",&a,&b,&k,&t);
    a+=1e5; b+=1e5;
    dp1[0][a]=dp2[0][b]=1;
    for(int i=1;i<=t;++i){
        int now=i%2,pre=(i-1)%2;
        memset(dp1[now],0,sizeof(dp1[now]));
        memset(dp2[now],0,sizeof(dp2[now]));
        for(int j=-k*i;j<=k*i;++j){
        	int l=max(-k*(i-1),j-k),r=min(k*(i-1),j+k);
        	for(int p=l;p<=r;++p){
        		dp1[now][a+j]+=dp1[pre][a+p];
        		dp1[now][a+j]%=P;
        		dp2[now][b+j]+=dp2[pre][b+p];
        		dp2[now][b+j]%=P;
			}
        }
    }
    int ans=0;
    for(int i=a-k*t;i<=a+k*t;++i)
	   	for(int j=b-k*t;j<i;++j)
			ans+=(long long)dp1[t%2][i]*dp2[t%2][j]%P,ans%=P;
    ans=(ans%P+P)%P;
    printf("%d\n",ans);
    return 0;
}
```

过个头啊，我们还要优化。

我们再看看那个方程发现其实我们可以对那个枚举当前选什么然后从前一个转移哪里进行优化。（也就是p的操作）。

其实这一部分做的就是在求

$\sum_{p=j-k}^{j+k} dp[i-1][a+p]$
 
$j$ 是当前我们枚举的那个分数增加值。

那么我们对这一部分求个前缀和就好了

这样我们把最重要的一个 $1000$ 给干掉了

复杂度 $100*(1000*100)$ ~~（稳得一批。~~

我们得相信CF的评测机！！！

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=105,M=N*1000*2,P=1000000007;
int dp1[2][M],dp2[2][M],sum1[M],sum2[M];

int main(){
    int a=0,b=0,k=0,t=0;
    scanf("%d%d%d%d",&a,&b,&k,&t);
    a+=1e5; b+=1e5;
    dp1[0][a]=dp2[0][b]=1;
    sum1[a]=sum2[b]=1;
    for(int i=1;i<=t;++i){
        int now=i%2;
        memset(dp1[now],0,sizeof(dp1[now]));
        memset(dp2[now],0,sizeof(dp2[now]));
        for(int j=-k*i;j<=k*i;++j){
            int l=max(-k*(i-1),j-k),r=min(k*(i-1),j+k);
            dp1[now][a+j]+=(sum1[r+a]-sum1[l+a-1])%P;
            dp1[now][a+j]%=P;
            dp2[now][b+j]+=(sum2[r+b]-sum2[l+b-1])%P;
            dp2[now][b+j]%=P;
        }
        for(int j=1;j<M;++j){
            sum1[j]=sum1[j-1]+dp1[now][j];
            sum1[j]%=P;
            sum2[j]=sum2[j-1]+dp2[now][j];
            sum2[j]%=P;
        }
    }
    int ans=0;
    for(int i=1;i<M;++i)
        ans+=(long long)sum2[i-1]*dp1[t%2][i]%P,ans%=P;
    ans=(ans%P+P)%P;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Richard_Whr (赞：1)

**转化题意：求 $A$ 获胜的方案：**

设 $A$ 取 $t$ 轮后总得分为 $f_A$，

$B$ 取 $t$ 轮后总得分为 $f_B$。

那么就是要求：

$$f_A+a>f_B+b$$
    
$$f_A-f_B>b-a$$

$$f_A-f_B \ge b-a+1$$

设这样合法方案中 $B$ 的所有操作转化为 $01$ 串：

取正数的轮数为 $1$，取负数的轮数为 $0$。

那么对这个 $01$ 串整体取反，所以此时 $f_B'= -f_B$。

因此，所有每一种 $f_A-f_B \ge b-a+1$ 合法方案都可以转化为 $f_A+f_B \ge b-a+1$。

**因此，此时继续转化题意：**

此时 $f_A$，$f_B$ 地位完全相等，合并：共取 $2\times t$ 轮，求总得分 $\ge b-a+1$ 的方案。

 $\mathit{f}_{i,j}$ 表示到第 $i$ 轮共取了 $j$ 分的方案，

$$\mathit{f}_{i,j}=\mathit{f}_{i-1,j+s}(s\in[-k,k])$$

那么就有问题了，如果 $j$ 比较小，可能会访问到下标 $<0$ 的点。

因此，思考后发现总得分的值域在 $[-k\times 2\times t,k\times 2\times t]$ 中。

如果我们把坐标轴原点左移 $k\times 2\times t$ 个位置，值域就会变为  $[0,k\times 4\times t]$ 中，这样就不会有问题了。

此时 $0$ 的位置对应的是 $k\times 2\times t$，

也就是初始化中 $\mathit{f}_{0,0}=1$，其余为 $0$。

此时引入第二个问题：

看到状态转移是上一个阶段连续一段的值，考虑进行**前缀和优化**。

建立前缀和后就不会有阶段跨界的冲突了，因此还可以优化掉一维。

因此就有 $f_{j}=s_{j+k}-s_{j-k-1}$。

AC 代码：


```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+10,mod=1000000007;
int f[N];
int s[N];
int a,b,k,t;
int m,n;
signed main()
{
	scanf("%lld%lld%lld%lld",&a,&b,&k,&t);
	m=4*k*t,n=2*t;
	f[2*k*t]=1;
	
	for(int i=1;i<=n;i++)
	{
		s[0]=f[0];
		for(int j=1;j<=m+k;j++)
		{
			s[j]=(s[j-1]+f[j])%mod;	
		}
		for(int j=0;j<=m;j++)
		{
			if(j-k-1<0) f[j]=s[j+k];
			else if(j+k>m) f[j]=(s[m]-s[j-k-1]+mod)%mod;
			else f[j]=(s[j+k]-s[j-k-1]+mod)%mod;
		}	
	} 
	
	int res=0;
	for(int j=2*k*t+b-a+1;j<=m;j++) res=(res+f[j])%mod;
	
	printf("%lld",res);
	
	return 0;
}
```

---

## 作者：NXYorz (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF712D)

昨晚的 CF 的 E 给整自闭了，原来自己连前缀和优化 DP 都不会。

于是找到了这个古董题。

-------

### 分析

先不考虑优化，把暴力弄出来。

令 $f_{i,j}$ 表示玩家 $i$ 个回合后分数为 $j$ 的方案数。

容易得到状态转移方程 $f_{i,j} = \sum_{w=j-k}^{j+k}f_{i-1,w}$

暴力代码：
```cpp
#include<cstdio>

using namespace std;

const int N = 101;
const int K = 1001;
const int p = 1e9 + 7;

int a,b,k,t;
long long f[((K * N) << 1) + N][N][2];
long long ans;

inline int max(int x , int y)
{return x > y ? x : y;}

int main()
{
    //freopen("aa.in","r",stdin);
    scanf("%d%d%d%d",&a,&b,&k,&t);
    a += k * t , b += k * t;
    f[a][0][0] = f[b][0][1] = 1;
    for(int i = 1; i <= t; i++)
    {
        for(int j = 0; j <= 1; j++)
        {
            for(int w = -k; w <= 0; w++)
                for(int l = 0; l <= ((k * t) << 1) + max(a , b) - k * t; l++)
                    if(l - w <= ((k * t) << 1) + max(a , b) - k * t && f[l - w][i - 1][j])
                        f[l][i][j] += f[l - w][i - 1][j] , f[l][i][j] %= p;
            for(int w = 1; w <= k; w++)
                for(int l = ((k * t) << 1) + max(a , b) - k * t; l >= 0; l--)
                    if(l - w >= 0 && f[l - w][i - 1][j])
                        f[l][i][j] += f[l - w][i - 1][j] , f[l][i][j] %= p;
        }
    }
    for(int i = 0; i <= ((k * t) << 1) + (max(a , b) - k * t); i++)
        for(int j = 0; j < i; j++)
            ans += ((f[i][t][0] % p) * (f[j][t][1] % p)) % p , ans %= p;
    printf("%lld",ans % p); return 0;
}
```

发现这样做的好处是每一回合互不相关，即我们可以把上一回合的得分方案数记下来，做一个前缀和，每一转移时可以做到 $O(1)$。

```cpp
#include<cstdio>
#include<cstring>

using namespace std;

const int N = 101;
const int K = 1001;
const int p = 1e9 + 7;

int a,b,k,t;
int f[((K * N) << 1) + N][N][2] , sum[((K * N) << 1) + N][2];
long long ans;

inline int max(int x , int y)
{return x > y ? x : y;}

inline int min(int x , int y)
{return x > y ? y : x;}

int main()
{
    //freopen("aa.in","r",stdin);
    scanf("%d%d%d%d",&a,&b,&k,&t);
    a += k * t , b += k * t;
    f[a][0][0] = f[b][0][1] = 1;
    for(int i = 1; i <= t; i++)
        for(int j = 0; j <= 1; j++)
        {
            for(int l = 0; l <= ((k * t) << 1) + max(a , b) - k * t; l++)
                sum[l][j] = sum[l - 1 == 0 ? ((k * t) << 1) + max(a , b) - k * t + 1 : l - 1][j] + f[l][i - 1][j] , sum[l][j] %= p;

            for(int l = 0; l <= ((k * t) << 1) + max(a , b) - k * t; l++)
            {
                int L = max(0 , l - k - 1); int R = min(l + k , ((k * t) << 1) + max(a , b) - k * t);
                if(!L) L = ((k * t) << 1) + max(a , b) - k * t + 1;
                f[l][i][j] += sum[R][j] - sum[L][j] , f[l][i][j] %= p;
            }
        }
    
    for(int j = 0; j <= 1; j++)
        for(int l = 0; l <= ((k * t) << 1) + max(a , b) - k * t; l++)
           sum[l][j] = sum[l - 1 == 0 ? ((k * t) << 1) + max(a , b) - k * t + 1 : l - 1][j] + f[l][t][j] , sum[l][j] %= p;
        
    for(int i = 0; i <= ((k * t) << 1) + (max(a , b) - k * t); i++)
            ans += (long long)((f[i][t][0] % p) * (long long)(sum[i - 1 == 0 ? ((k * t) << 1) + max(a , b) - k * t + 1 : i - 1][1] % p)) % p , ans %= p;
    if(ans < 0) ans = ((ans % p) + p) % p;
    printf("%lld",ans % p); return 0;
}
```

---

## 作者：Erina (赞：0)

## dp题目

> 为什么这道题的题解还是这么玄学啊......

发现每个人对每个人没有**任何**影响, 所以让每个人随便选, 最后合并答案即可.

$dp[i]$表示在之前的游戏中公加了$i$分的种类数

用前缀和优化一下就好了......

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n, m, k, d;
int dp[210005], sum[210005];
int main() {
	cin >> n >> m >> k >> d;
	dp[0] = 1;
	for (int i = 0; i <= 200000; i++)sum[i] = 1;
	for (int i = 1; i <= d; i++) {
		for (int u = 0; u <= 2 * k; u++)
			dp[u] = sum[u];
		for (int u = 2 * k + 1; u <= 200000; u++)
			dp[u] = (sum[u] - sum[u - 2 * k - 1] + 1000000007) % 1000000007;
		sum[0] = dp[0];
		for (int u = 1; u <= 210000; u++)
			sum[u] = (sum[u - 1] + dp[u]) % 1000000007;
	}
	int ans = 0;
	for (int i = max(m - n + 1, 0); i <= 200000; i++)
		ans = (ans + 1ll * dp[i] * sum[i - m + n - 1]) % 1000000007;
	cout << ans;
}
```


---

