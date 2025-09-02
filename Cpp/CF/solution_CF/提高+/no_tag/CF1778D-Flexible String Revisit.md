# Flexible String Revisit

## 题目描述

You are given two binary strings $ a $ and $ b $ of length $ n $ . In each move, the string $ a $ is modified in the following way.

- An index $ i $ ( $ 1 \leq i \leq n $ ) is chosen uniformly at random. The character $ a_i $ will be flipped. That is, if $ a_i $ is $ 0 $ , it becomes $ 1 $ , and if $ a_i $ is $ 1 $ , it becomes $ 0 $ .

What is the expected number of moves required to make both strings equal for the first time?

A binary string is a string, in which the character is either $ \tt{0} $ or $ \tt{1} $ .

## 说明/提示

In the first test case, index $ 1 $ is chosen randomly and $ a_1 $ is flipped. After the move, the strings $ a $ and $ b $ are equal. The expected number of moves is $ 1 $ .

The strings $ a $ and $ b $ are already equal in the second test case. So, the expected number of moves is $ 0 $ .

The expected number of moves for the third and fourth test cases are $ \frac{56}{3} $ and $ \frac{125}{3} $ respectively.

## 样例 #1

### 输入

```
4
1
0
1
2
00
00
4
1000
1110
5
01001
10111```

### 输出

```
1
0
665496254
665496277```

# 题解

## 作者：LinuF (赞：12)

### 题意

给出两个长度均为 $n$ 的 $01$ 串 $S$ 和 $T$。

每次随机将 $S$ 中的某一位取反。

问：第一次 $S = T$ 时操作次数的期望。

### 思路

首先我们得目的是将两串不匹配的位置使得它能够匹配。

我们定义状态 $f_{i}$ 意思为从剩余 $i$ 个需要匹配的位置转移到到剩余 $i-1$ 个，需要的次数的期望。

这个时候我们要从状态 $i$ 转移到状态 $i-1$ 的两种情况分析。

- 修改的位置恰好能匹配上，期望是 $\frac{i}{n}$。

- 修改的位置不能匹配上，那这个时候不匹配的个数会从 $i$ 变成 $i+1$，期望是 $\frac{n-i}{n}$，那这个时候还要采用 $f_{i+1}$ 来转移回 $i$，再从 $i$ 转移到 $i-1$。

是能够证明只有这两种情况的，因为上下两个串要不然就是匹配，要不然就是不匹配，那修改要不然会改错，要不然就是改对了。

表现成状态转移方程是这样的：

$$f_{i}=\frac{n-i}{n}(1+f_{i+1}+f_{i})+\frac{i}{n}$$

化简过后会变成：

$$f_{i}=\frac{(n-i)dp_{i+1}+n}{i}$$

这样就能线性递推求解了，最后的答案 $\sum_{i=1}^{\text{nums}}dp_{i}$。

其中 $\text{nums}$ 表示有多少位置没有匹配上。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
char a[N],b[N];
int n,dp[N],mod=998244353;
int qmi(int a,int b){
    int res=1;
    while(b){
        if(b&1){
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return res%mod;
}
int inv(int x){
    return qmi(x,mod-2);
}
signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        cin>>(a+1)>>(b+1);
        int nums=0;
        for(int i=1;i<=n;i++){
            // cout<<a[i]<<" "<<b[i]<<endl;
            if(a[i]!=b[i]) nums++; 
        }
        for(int i=n;i>=1;i--){
            dp[i]=((n-i)*dp[i+1]%mod+n)*inv(i)%mod;
        }
        int res=0;
        for(int i=1;i<=nums;i++){
            res=(res+dp[i])%mod;
        }
        cout<<res<<endl;
    }
}
```


---

## 作者：Ray1 (赞：11)

设 $f_i$ 为还剩 $i$ 个字符未匹配，翻转一个未匹配字符的期望次数。

当全部字符均未匹配时，必然翻转未匹配字符，所以 $f_n=1$。

每次有 $\frac in$ 的概率翻转一个未匹配字符，$\frac{n-i}n$ 的概率翻转一个已匹配字符。翻转到已匹配字符需要 $f_{i+1}$ 期望次数才能回到当前状态，然后又需要 $f_i$ 期望次数才能翻转一个未匹配字符。于是有方程：
$$f_i=1+\frac{n-i}n\times(f_{i+1}+f_i)$$
化简得：
$$f_i=\frac{n+(n-i)f_{i+1}}i$$
设初始状态为还剩 $x$ 个字符未匹配，则翻转到全部匹配的期望次数为 $f_x+f_{x-1}+f_{x-2}+\cdots+f_1$。

---

## 作者：氧少Kevin (赞：9)

## CF1778D - Flexible String Revisit

https://codeforces.com/contest/1778/problem/D

## 题意
给出两个长度均为 $n(n\leq 10^6)$ 的 01 串 $S$ 和 $T$。

每次随机将 $S$ 中的某一位取反。

问：第一次 $S = T$ 时操作次数的期望。

## 思路
显然，我们只关心当前 $S$ 与 $T$ 有几个位置不同。

用 $f_i$ 表示当前有 $i$ 个位置不同，从当前状态到 $S = T$ 操作次数的期望。

转移方程：

$$
f_i = 
\begin{cases}
    0 &,i=0 \\
    f_{n-1}+1 &,i=n\\
    f_{i+1}\times(1-\frac{i}{n})+f_{i-1}\times \frac{i}{n}+1 &,1\leq i\leq n-1\\
\end{cases}
$$

显然，此转移方程存在环。
如何处理？

不妨从 $1\leq i\leq n-1$ 时下手，将这个方程改写成一般的线性递推式。

当 $1\leq i\leq n-1$ 时，
$$f_i=f_{i+1}\times(1-\frac{i}{n})+f_{i-1}\times \frac{i}{n}+1 \quad,1\leq i\leq n-1$$
可以改写成一般的线性递推式：
$$f_i=\frac{f_{i-1}-f_{i-2}\times \frac{i-1}{n}-1}{1-\frac{i-1}{n}} \quad,2\leq i \leq n$$
因为 $f_0=0$，所以 $i=2$ 时有：
$$f_2=\frac{f_1-f_0\times \frac{i-1}{n}-1}{1-\frac{i-1}{n}}=\frac{f_1-0-1}{1-\frac{i-1}{n}}$$
由此不难发现，$f_i$ 的每一项都可以改写成如下形式：
$$f_i=p_i\times f_1+q_i$$
注意到：
$$f_n=f_{n-1}+1$$
$$f_n-f_{n-1}=1$$
$$p_n\times f_1+q_n - (p_{n-1}\times f_1+q_{n-1})=1$$

$p_n,q_n,p_{n-1},q_{n-1}$ 均是可以递推出的已知量，因此可以求解出 $f_1$。


 **如何递推 $p_i$ 和 $q_i$？**
 
   观察递推式：$f_i=\frac{f_{i-1}-f_{i-2}\times \frac{i-1}{n}-1}{1-\frac{i-1}{n}} \quad$ 
    注意到分子的 $-1$ 是常数，他只应该作用在常数 $q$ 上。
    也就是：
    $p_i=\frac{p_{i-1}-p_{i-2}\times \frac{i-1}{n}}{1-\frac{i-1}{n}},q_i=\frac{q_{i-1}-q_{i-2}\times \frac{i-1}{n}-1}{1-\frac{i-1}{n}}$。


最后，答案就是 $f_x=p_x\times f_1+q_x$，其中 $x$ 是 $S$ 和 $T$ 不同的位置数量。

```cpp
void Sol()
{
	vector< pair<int,int> > dp(n+5);
	
	dp[0] = {0, 0};
	dp[1] = {1, 0};
	
	for (int i=2; i<=n; i++)
	{
		int inv = Div(i-1, n);
        // 递推 pi, qi
		dp[i].first = Div(((dp[i-1].first-(dp[i-2].first*inv%MOD)+MOD)%MOD+MOD)%MOD, (1-inv+MOD)%MOD);
		dp[i].second = Div(((dp[i-1].second-(dp[i-2].second*inv%MOD)+MOD)%MOD-1+MOD)%MOD, (1-inv+MOD)%MOD);
	}
	// 求解 f1
	int p = (dp[n].first-dp[n-1].first+MOD)%MOD;
	int q = (dp[n].second-dp[n-1].second+MOD)%MOD;
	int t = Div((1-q+MOD)%MOD, p);
	
	int cnt = 0;
	for (int i=1; i<=n; i++)
		cnt += (S[i] != T[i]);
	
	int ans = (dp[cnt].first*t%MOD + dp[cnt].second)%MOD;
	printf("%lld\n", ans);
}
```


---

## 作者：ningago (赞：6)

注意到答案只和匹配的位置的多少有关。

令 $p_i$ 表示匹配了 $i$ 个位置，期望还需几步。

一个有后效性的状态转移方程为：

$$\begin{cases}p_i=\dfrac{n-i}{n}p_{i+1}+\dfrac{i}{n}p_{i-1}+1&1\leq i< n\\p_i=p_{i+1}+1&i=0\\p_i=0&i=n\end{cases}$$

考虑将 $p_i$ 表示为 $p_{i+1}$ 的线性组合，即 $p_i=a_i\cdot p_{i+1}+b_i$。

已知的是 $a_0=b_0=1$。

推导一下：

$$p_i=\dfrac{n-i}{n}p_{i+1}+\dfrac{i}{n}(a_{i-1}\cdot p_i+b_{i-1})+1$$

解得：

$$p_i=\dfrac{n-i}{n-i\cdot a_{i-1}}p_{i+1}+\dfrac{i\cdot b_{i-1}+n}{n-i\cdot a_{i-1}}$$

至此可以线性推导出 $a,b$。进而计算出 $p$。

（通过推导及实践可知，$a$ 数组的值恒为 $1$。）

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 1000010
#define mod 998244353
#define int long long

int T;
int n;
char stra[N],strb[N];
int b[N];
int p[N];

int ksm(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1)
			res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%s%s",&n,stra + 1,strb + 1);
		int m = 0;
		for(int i = 1;i <= n;i++)
			if(stra[i] == strb[i])
				m++;
		b[0] = 1;
		for(int i = 1;i < n;i++)
		{
			int t = ksm(n - i,mod - 2);
			b[i] = (b[i - 1] * i % mod + n) % mod * t % mod;
		}
		p[n] = 0;
		for(int i = n - 1;i >= 0;i--)
			p[i] = (p[i + 1] % mod + b[i]) % mod;
		printf("%lld\n",p[m]);
	}
	return 0;
}
```

---

## 作者：Miraik (赞：4)

脑子越来越不好使了，这玩意能调半天。。

$f_i$ 表示由 $i$ 个 $a_k\neq b_k$ 变成 $i-1$ 个 $a_k\neq b_k$ 的期望。

取 $p=\frac{i}{n}$，即随机选取一个 $i$ 选中 $a_i \neq b_i$ 的期望。

$f_i = p + (1-p)(f_i+f_{i+1}+1)$

移项一下：

$f_i = 1 + \frac{(1-p)(f_{i+1}+1)}{p} $

这样就可以直接转移了，初始化 $f_n=1$。

答案是 $\sum_{i=1}^{cnt} f_i,cnt=\sum_{i=1}^n  [a_i \neq b_i]$。

---

## 作者：hgzxwzf (赞：2)

## [CF1778D](https://www.luogu.com.cn/problem/CF1778D)
### 解题思路：
读完题就想到了 [这个题](https://www.luogu.com.cn/problem/P3750)。
一样的 dp 思路，设 $dp_i$ 表示还剩 $i$ 个关键灯要反转到还剩 $i-1$ 个关键灯要反转的期望操作数。

$dp_i=(dp_{i+1}+dp_i+1)\times \frac{n-i}{n}+1\times \frac{i}{n}$。

首先有进行一次 $1$ 操作，有 $\frac{n-i}{n}$ 的概率反转了错误的灯，这时就还有 $i+1$ 个关键灯，需要 $dp_{i+1}$ 使得只有 $i$ 个关键灯，但这还不够，还需要 $dp_i$ 使关键灯的数量为 $i-1$；有 $\frac{i}{n}$ 的概率反转了正确的灯。

将 $dp_i$ 移过来得到 $dp_i=\frac{n+(n-i)\times dp_{i+1}}{i}$。

设 $cnt$ 为刚开始关键灯的个数，$cnt$ 就等于 $s_1$ 串和 $s_2$ 串不同位置的个数。

$ans=\sum^{i=1}_{cnt}dp_i$。

### Code：
```cpp
const int N=1e6+10;

char s[N],s2[N];
mint dp[N];

int main()
{
//	freopen("in","r",stdin);
//	freopen("out","w",stdout);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		scanf("%d %s%s",&n,s+1,s2+1);
		per(i,1,n)
		{
			dp[i]=mint(n-i)/n*dp[i+1]+1;
			dp[i]*=mint(n)/i;
		}
		int cnt=0;
		rep(i,1,n) cnt+=s[i]!=s2[i];
		mint res=0;
		rep(i,1,cnt) res+=dp[i];
		printf("%d\n",res);
	}
	return 0;
}
```


---

## 作者：shinkuu (赞：1)

原题，但是仍然是好题。

明显操作的影响只与选中那一位的数有关。于是设 $dp_i$ 表示当有 $i$ 位为 $1$ 时，期望去多少次能有 $i+1$ 位为 $1$。

考虑每次取只有两种可能性：$1$ 的数量 $-1$ 或 $+1$。因为每次有 $\frac {n-i}n$ 的概率为后者，所以期望进行 $\frac n{n-i}$ 次才能取到。

但此时还没算 $-1$ 的贡献。既然要进行 $\frac n{n-i}$ 次，那么就有 $\frac n{n-i}-1$ 次 $-1$ 操作。每次操作又要额外花费 $dp_{i-1}+1$ 次操作才能回到原来状态（后面的 $+1$ 是 $-1$ 操作产生），所以就可以列出状转方程：

$$dp_i=(\frac n{n-i}-1)\times(dp_{i-1}+1)+1$$

初始状态 $dp_0=1$。

答案即为 $\sum_{i=\sum [S_j=T_j]}^{n-1} dp_i$。

注意勤取模。

很好码，就不放代码了（其实是 CF 炸了）。

---

## 作者：masonpop (赞：0)

经典期望 $dp$ 套路。做过 P3750 的应该都会。

注意到如果设 $dp_i$ 表示剩余 $i$ 个字符未匹配的期望次数，则转移时会出现不知道前两项的奇怪的二阶线性递推，需要回带回去解方程，非常麻烦。我们考虑更改定义，设 $dp_i$ 表示剩余 $i$ 个字符未匹配时**多匹配一个字符的期望次数。**

这样的好处是，一次翻转要么直接成功，要么转移到了 $dp_{i+1}$，相当于是一阶线性递推。由于翻转成功则直接结束，反转失败则需要翻转回来，可以列出转移方程：

$dp_i=\frac{i}{n}+\frac{n-i}{n}(1+dp_{i+1}+dp_{i})$。

化简得到

$dp_i=\frac{(n-i)dp_{i+1}+n}{i}$。

初始状态是 $dp_{n}=1$，这样可以倒着解出所有的 $dp_i$。设刚开始有 $k$ 个字符未匹配，则答案为 $\sum\limits_{i=1}^kdp_i$。[代码](https://codeforces.com/contest/1778/submission/210729417)。

---

## 作者：xxx2022 (赞：0)

显然，我们可以先忽略两个串已经一样的部分，只考虑剩下不一样的部分，然后我们就可以将它抽象成一个链上游走问题。我们记 $g_i$ 为从第 $i-1$ 个到第 $i$ 个点的期望步数，此时 $g_1=1$。且 $g$ 满足：
  
  $$g_i=\frac{n}{n-i}+\frac{i \cdot g_{i-1}}{n-i}$$
  
  这时令 $m=n-\sum \limits_{i=1}^{n}{[a_i = b_i]}$，所以根据期望的线性性，答案即为 $\sum \limits_{i=1}^{m}{g_i}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int mod=998244353;
inline int read(){
	int f=1,w=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')    f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		w=(w<<1)+(w<<3)+(c^48);
		c=getchar();
	}
	return f*w;
}
int quickpow(int x,int p){
	int ans=1;
	while(p){
		if(p&1){
			ans=ans*x%mod;
		}
		x=x*x%mod;
		p>>=1;
	}
	return ans;
}
int inv(int x){
	return quickpow(x,mod-2)%mod;
}
int g[N];
int t;
int n;
signed main(){
	t=read();
	while(t--){
		n=read();
		string s1,s2;
		cin>>s1>>s2;
		int s=0;
		for(int i=0;i<n;i++){
			if(s1[i]==s2[i])	s++;
		}
		if(s==n){
			printf("0\n");
			continue;
		}
		g[0]=1;
		for(int i=1;i<n;i++){
			g[i]=((n*inv(n-i))%mod+((i*g[i-1])%mod*inv(n-i)%mod))%mod;
		}	
		int ans=0;
		for(int i=s;i<n;i++){
			ans=(g[i]+ans)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

