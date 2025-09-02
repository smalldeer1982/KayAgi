# Levko and Strings

## 题目描述

Levko loves strings of length $ n $ , consisting of lowercase English letters, very much. He has one such string $ s $ . For each string $ t $ of length $ n $ , Levko defines its beauty relative to $ s $ as the number of pairs of indexes $ i $ , $ j $ $ (1<=i<=j<=n) $ , such that substring  $ t[i..j] $ is lexicographically larger than substring $ s[i..j] $ .

The boy wondered how many strings $ t $ are there, such that their beauty relative to $ s $ equals exactly $ k $ . Help him, find the remainder after division this number by $ 1000000007 $ $ (10^{9}+7) $ .

A substring $ s[i..j] $ of string $ s=s_{1}s_{2}...\ s_{n} $ is string $ s_{i}s_{i+1}...\ s_{j} $ .

String $ x=x_{1}x_{2}...\ x_{p} $ is lexicographically larger than string $ y=y_{1}y_{2}...\ y_{p} $ , if there is such number $ r $ ( $ r&lt;p $ ), that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&gt;y_{r+1} $ . The string characters are compared by their ASCII codes.

## 样例 #1

### 输入

```
2 2
yz
```

### 输出

```
26
```

## 样例 #2

### 输入

```
2 3
yx
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 7
abcd
```

### 输出

```
21962
```

# 题解

## 作者：Rorschachindark (赞：3)

# Levko and Strings
## 思路
$\ \ \ \ \ \ $ 这道题不应该是蓝的，至少都应该是紫色的吧。。。

$\ \ \ \ \ \ $ 首先，我们考虑使用动态规划。我们设$dp[i][j]$表示已经考虑前面$i$位，后面的字符都一样，产生的贡献为$j$的方案数。

$\ \ \ \ \ \ $ 考虑如何转移。我们设$l$是$i$之前从右往左数第一位$\text {s,t}$不同的位置。我们考虑分类讨论。

>
如果$t[i]>s[i]$

$\ \ \ \ \ \ $ 很显然，我们$\text {left point}\in [l+1,i],\text {right point}\in [i,n]$的时候，是满足的，其他情况都没有影响，所以这种情况对答案的贡献为$(\text {'z'}-s[i])\times \sum_{l=0}^{i-1} dp[l][j-(i-l)\times (n-i+1)]$

>
如果$t[i]<s[i]$

$\ \ \ \ \ \ $ 可以看出这种情况不会产生新的相关度，所以对答案的贡献为$(s[i]-\text {'a'})\times \sum_{l=0}^{i-1} dp[l][j]$

$\ \ \ \ \ \ $ 综上，可以得到转移方程:

$$dp[i][j]=(\text {'z'}-s[i])\times \sum_{l=0}^{i-1}dp[l][j-(i-l)\times (n-i+1)]+(s[i]-\text {'a'})\times \sum_{l=0}^{i-1} dp[l][j]$$

$\ \ \ \ \ \ $ 最后的答案很显然就是:

$$\sum_{i=0}^{n} dp[i][k]$$
## $\text {Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define mod 1000000007
#define ll long long
#define MAXN 2005

int n,k;

char s[MAXN];

int dp[MAXN][MAXN],sum[MAXN];

void Add (int &x,int y){x = (x + y >= mod ? x + y - mod : x + y);}

int Solve ()
{
	sum[0] = dp[0][0] = 1;
	for (Int i = 1;i <= n;++ i)
		for (Int j = 0;j <= k;++ j)
		{
			for (Int l = i - 1;l >= 0 && (i - l) * (n - i + 1) <= j;-- l)
				Add (dp[i][j],dp[l][j - (i - l) * (n - i + 1)]);
			dp[i][j] = (ll)('z' - s[i]) * dp[i][j] % mod;
			Add (dp[i][j],(ll)sum[j] * (s[i] - 'a') % mod);
			Add (sum[j],dp[i][j]);
		}
	int Ans = 0;
	for (Int i = 0;i <= n;++ i) Add (Ans,dp[i][k]);
	return Ans;
}

int read ()
{
	int x = 0;char c = getchar();int f = 1;
	while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}
	while (c >= '0' && c <= '9'){x = (x << 3) + (x << 1) + c - '0';c = getchar();}
	return x * f;
}

void write (int x)
{
	if (x < 0){x = -x;putchar ('-');}
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
}

signed main()
{
	n = read (),k = read ();
	scanf ("%s",s + 1);
	write (Solve ()),putchar ('\n');
	return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
非常好动态规划，使我的大脑旋转上升。题意很清晰，这里举个例子。

我们令字符串 $s$ 为 ```aabb``` 字符串 $t$ 为 ```bbbb```。那么在区间 $\left[1,1\right],\left[1,2\right],\left[1,3\right],\left[1,4\right],\left[2,2\right],\left[2,3\right],\left[2,4\right]$ 中，它们构成的子串中，所对应下标子串的子串数量都满足 $t$ 比 $s$ 大。此时价值就是 $7$。现在告诉你价值，请找出满足题意的 $t$ 的个数。
## 分析。
下文中的“相等”均是题目定义而非日常定义。

这个动态规划一步就想到不太可能，那么我们就将最暴力的状态设出来，然后通过降维这个基本的方式一步步化简。
### 第一部分：暴力。
显然我们可以列出一个思维的暴力。设 $dp\left[i\right]\left[j\right]\left[a\right]\left[b\right]$ 表示前 $i$ 个位置有总共 $j$ 个子串大于 $s$ 的子串。其中有 $a$ 个位置是从 $i$ 开始都和 $s$ 相等，有 $b$ 个开头位置，已经满足某个位置大于 $s$ 的情况存在，这样在每次枚举转移时，只要看当前的位置是等于小于还是大于即可。

时间复杂度 $O\left(n^4\right)$ 显然超时。
### 第二部分：考虑缩小范围。
有一个很显然的定理：考虑统计中大于 $s$ 的位置产生的贡献，如果这个位置是 $i$ 同时它的前面有 $k$ 个相等的位置，那么就有 $\left(k+1\right)\times\left(n-i+1\right)$ 个子串的贡献。其中左端点大于 $i$ 的子串都会在后面被统计到。这样我们的动态规划需要三维即可。

时间复杂度优化到 $O\left(n^3\right)$ 还是有危险。
### 第三部分：优化掉一个维。
因为在这里面三个维度都不好去掉，所以我们从最不容易对答案产生影响的维下手。那么我们考虑枚举有多少个位置是相等的，这样就可以至少在状态上去掉它了。所以我们整理一下，重新定义：

设 $dp\left[i\right]\left[j\right]$ 表示考虑前 $i$ 个位置，该子串中的最后的一个位置要求不能填“相等”的方案数有 $j$ 个。答案统计下来每一个维度即可。具体转移方程如下：

设 $a$ 为该字符在 ASCLL 码表中的对应字符，相似的还有 $z$ 的表示方法。

- 填小于号：  
那么我们就可以枚举前面的等号有多么长。转移方程为 $dp\left[i\right]\left[j\right]=\sum_{k=0}^{i-1}dp\left[k\right]\left[j\right]\times\left(s\left[i\right]-a\right)$ 可以通过前缀和进行优化。
- 填大于号：  
同样枚举，转移方程为 $dp\left[i\right]\left[j\right]=\sum_{k=1}^idp\left[i-k\right]\left[j-k\times\left(n-i+1\right)\right]\times\left(z-s\left[i\right]\right)$ 即可得。


那么我们就需要枚举的次数为 $\sum_{i=1}^{i=n}\left\lfloor\dfrac{n}{i}\right\rfloor$ 所以时间复杂度为 $O\left(n^2\log n\right)$ 足以通过本题。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
const int mod=1e9+7;
int n,k;
int ans,dp[2005][2005],sum[2005];
char s[2005];
int main(){
    cin>>n>>k;
	cin>>s+1;
	if(k==0) ans=1;
    for(int i=1;i<=n;i++){
	    s[i]-='a'-1;
	}
    sum[0]=1;
	dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            (dp[i][j]+=1LL*sum[j]*(s[i]-1)%mod)%=mod;
            for(int k=1;k<=i&&j>=k*(n-i+1);k++){
                (dp[i][j]+=1LL*dp[i-k][j-k*(n-i+1)]*(26-s[i])%mod)%=mod;
            }
            (sum[j]+=dp[i][j])%=mod;
            //sum[i]%=mod;
        }
        (ans+=dp[i][k])%=mod;
        //ans%=mod;
    }
    cout<<ans/*%mod*/<<"\n";
    return 0;
}
/*
in:
47 0
tmvdxhumdsbypyocuydhqevkgfijsbdoucgugqkruktmlem
out:
129331153
*/
```
## 后记。
为什么前言中说使我的大脑旋转上升呢？因为每一次错误的提交都在第五个测试点上，以为是推导中间有问题所以一直去推式子，结果发现是没有特判。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
给一个为 $n$ 的只有小写字母组成的串 $s$，定义它与一个长度为 $n$ 的串 $t$ 的美丽度为：存在多少个二元组 $(i,j) \ 1\leq i \leq j \leq n$ 满足 $s_{i...j}<t_{i...j}$，这里的'<'是字典序比较。求有多少个 $t$，使得 $s$ 与 $t$ 的美丽度为 $k$.   
$n,k \leq 2000$
## $\text{Solution}$
很好的 DP 题.  
一种不太一样的做法.  
容易想到设计 $dp_{i,j}$ 表示 $[1...i]$ 已经确定的二元组有 $j$ 个的方案数.  
设 $up_i$ 为大于 $s_i$ 的字符数，设 $bot_i$ 为小于 $s_i$ 的字符数.  

对于第 $i$ 位填不同于 $s_i$ 的字符时，比较容易写出转移：  
1. $t_i<s_i$ 时，合法二元组数量不变，所以有：
$$bot_i\times dp_{i-1,j}\to dp_{i,j}$$
2. $t_i>s_i$ 时，对于任意的 $i\le j\le n$，$(i,j)$ 都是合法的二元组，一共增加了 $n-i+1$ 个，所以有：
$$up_i\times dp_{i-1,j}\to dp_{i,j+(n-i+1)}$$

接下来就是 $s_i=t_i$ 的情况，相对比较麻烦.  

还是分情况来讨论.  
1. 连续多位相等，到某一位 $t_k<s_k$。合法二元组不变，则有：
$$bot_k\times dp_{i-1,j}\to dp_{k,j}(i<k\le n)$$
>暴力统计显然会 T，但是可以开一个 $sum$ 数组然后把 $dp_{i,j}$ 加到 $sum_j$ 里面，统计到后面的时候把 $sum_j$ 里所有的值统计起来即可.
2. 连续多位相等，到某一位 $t_k>s_k$。对于 $i\le a\le k,k\le b\le n$，$(a,b)$ 都是合法的二元组，增加的二元组数量是 $(k-i+1)\times (n-k+1)$，所以有：
$$up_k\times dp_{i-1,j}\to dp_{k,j+(k-i+1)\times (n-k+1)}(i<k\le n)$$
> 这个想用类似情况 $1$ 的方法统计比较困难，但是我们发现，在 $n-i$ 较大时，增加二元组的数量是一个关于 $k$ 的二次单峰函数，由于 $m$ 只有 $O(n)$ 级别，所以有效的转移非常少。我们可以从两边暴力转移，增量超过 $m$ 就 break 即可.
3. 不要忘记还有可能始终到最后都相等，可以直接：
$$dp_{i,j}\to dp_{n,j}$$

## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2005;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;
char s[N];
ll dp[N][N],botsum[N];
ll c[N];
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  //debug("%d\n",(int)sizeof(dp)/1024/1024);
  n=read();m=read();
  scanf(" %s",s+1);
  dp[0][0]=1;
  for(int i=1;i<=n;i++){
    for(int j=0;j<=m;j++){
      int bot=s[i]-'a',up='z'-s[i];      
      (dp[i][j]+=bot*botsum[j])%=mod;
      (dp[i][j]+=bot*dp[i-1][j])%=mod;
      if(j-(n-i+1)>=0){
	(dp[i][j]+=up*dp[i-1][j-(n-i+1)])%=mod;	
      }
      //printf("i=%d j=%d bot=%d up=%d dp=%lld\n",i,j,bot,up,dp[i][j]);
    }
    for(int j=0;j<=m;j++){
       (botsum[j]+=dp[i-1][j])%=mod;      
       (dp[n][j]+=dp[i-1][j])%=mod;
       int l=i+1,r=n;
       for(;l<=n;l++){
	 int add=(l-i+1)*(n-l+1);
	 if(j+add>m) break;
	 (dp[l][j+add]+=('z'-s[l])*dp[i-1][j])%=mod;
       }
       for(;r>l;r--){
	 int add=(r-i+1)*(n-r+1);
	 if(j+add>m) break;
	 (dp[r][j+add]+=('z'-s[r])*dp[i-1][j])%=mod;
       }
    }
  }
  printf("%lld\n",dp[n][m]);
  return 0;
}
/*
3 3
tsy
*/

```


---

## 作者：cike_bilibili (赞：0)

## 动态规划

设 $f_{i,j}$ 表示前 $i$ 个字符已经有 $j$ 美丽度，转移时考虑第 $i$ 个字符产生的贡献，贡献总共分为两种情况。第一种情况是 $s_i \ge t_i$，此时无法产生贡献，则 $f_{i,j} = \sum_{k=1}^{i} f_{k-1,j} \cdot (s_i-1) $。第二种情况是 $s_i \le t_i$，则 $f_{i,j} = \sum_{k=1}^{i} f_{k-1,j-(i-k+1)(n-i+1)}$，时间复杂度 $O(n^2 k)$。

考虑优化，第一种情况显然可以前缀和优化，第二种情况中，注意到 $j-(i-k+1)(n-i+1) \ge 0$，而对于每一个 $i$，$n-i+1$ 均不相同，所以这可以看成一个调和级数，剪枝即可，时间复杂度 $O(nk \ln n)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
const int mod=1e9+7;
int n,k;
char s[2005];
int f[2005][2005];
int pre[2005][2005];
int ans;
signed main(){
	n=read(),k=read();
	scanf("%s",s+1);
	f[0][0]=1;
	pre[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			f[i][j]=pre[i-1][j]*(s[i]-'a')%mod;
			for(int k=i;k>=1&&j-(i-k+1)*(n-i+1)>=0;k--){
				f[i][j]=(f[i][j]+f[k-1][j-(i-k+1)*(n-i+1)]*('z'-s[i])%mod)%mod;
			}
			pre[i][j]=pre[i-1][j]+f[i][j];
		}
		ans=(ans+f[i][k])%mod;
	}
	if(k==0)ans++;
	cout<<ans;
	return 0;
} 
```

---

