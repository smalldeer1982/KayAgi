# Bookshelves

## 题目描述

## 题意：

$Keks$ 先生是 $Byteland$ 大陆的典型的白领。

他办公室里有一个书架，上面有几本书，每本书都有一个值为正整数的价格。

$Keks$ 先生把书架的价值定义为书价的总和。         

出乎意料地是， $Keks$ 先生升职了，现在他要去一个新的办公室。

他知道，在新的办公室里，他将有不止一个书架，而恰恰是 $K$ 个书架。

他认为 $K$ 个书架的美丽程度在于所有书架的价值的“按位与”和。 

他还决定不花时间重新整理书籍，所以他会先把几本书放在第一个书架上，下几本书放在下一个书架上，以此类推。当然，他会在每一个架子上放置至少一本书。这样，他会把所有的书放在 $K$ 个书架上，尽量使书架的美观程度越大越好。计算这个最大可能的美丽程度。

## 样例 #1

### 输入

```
10 4
9 14 28 1 7 13 15 29 2 31
```

### 输出

```
24
```

## 样例 #2

### 输入

```
7 3
3 14 15 92 65 35 89
```

### 输出

```
64
```

# 题解

## 作者：Siyuan (赞：13)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io)

---

> 题目链接：[Codeforces 981D](https://codeforces.com/contest/981/problem/D)

给出 $n$ 本书，每本书有一个价值 $a_i$。将这 $n$ 本书按照顺序放到 $k$ 个书架上（连续若干本书放在一个书架上，接下来连续若干本放在下一个书架上），定义一个书架的美观程度为这个书架上所有书的价值总和，定义 $k$ 个书架的美观程度为每个书架美观程度的按位与和，求这 $k$ 个书架的最大美观程度。

数据范围：$1\leqslant k\leqslant n\leqslant 50$，$0<a_i<2^{50}$

------

## Solution

对于按位与和，我们可以从高位到低位贪心选择。这个贪心的证明显然：如果一位为 $1$ 肯定比这一位为 $0$ 且后面都为 $1$ 更优。

如果当前最优解为 $ans$，接下来贪心第 $i$ 位，我们用 $\texttt{DP}$ 验证 $ans'=ans\ \texttt{OR}\ 2^i$ 这个答案是否可行。$\texttt{DP}$ 的状态定义为：$f[i][j]$ 表示前 $i$ 本书放到 $j$ 个书架是否可以得到答案 $x$ 使得 $ans'\in x$（$x\ \texttt{AND}\ ans'=ans'$）。转移方程为 $f[i][j]|=f[k][j-1]\ \texttt{AND}\ [sum(k+1,i)\ \texttt{AND}\ x=x]$，如果 $f[n][k]=1$ 则直接更新答案。

**时间复杂度**：$O(n^2 k\log \sum a_i)$

------

## Code

```cpp
#include <cstdio>
#include <cstring>

const int N=55;
int n,k;
long long a[N];
bool f[N][N];

bool check(long long x) {
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=1;i<=n;++i) {
        for(int j=1;j<=k;++j) {
            for(int k=0;k<i;++k) {
                f[i][j]|=f[k][j-1]&(((a[i]-a[k])&x)==x);
            }
        }
    }
    return f[n][k];
}
int main() {
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]),a[i]+=a[i-1];
    long long ans=0;
    for(int i=60;i>=0;--i) {
        long long now=ans|(1LL<<i);
        if(check(now)) ans|=(1LL<<i);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Libre_dreagonm (赞：4)

按位贪心+DP的好题qwq

首先看到题目的要求，统计价值的时候的操作是按位与，就要有按位分别计算的意识

~~开始没意识到结果想了好久还是看了题解才想到~~

由于统计价值的方式不是加和，所以可能会出现两个较大的值AND起来更小甚至变成0，所以不能直接DP

考虑按位贪心

显然高位为1后的值一定比高位不为1的值要大，所以从高位向下贪心，每次检查能否在使前i个位值不变的情况下，使新加入的位变为1

检查的时候用区间dp实现即可

设$dp[i][j]$表示前j本书分到前i个书架上是否能使前面的位不变且当前检查的位为1

状态转移方程为：

```cpp
dp[i][j]|=dp[i-1][kx]&&(((sum[j]-sum[kx])&&x)==x) 
```

总的复杂度是$O(n^{2}k)$

**注意位运算优先级和枚举的最高位的位数**

代码
```cpp

#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n,k,a[51],sum[51],dp[51][51],ans=0;
int check(int x){
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++)
            for(int kx=0;kx<j;kx++)
                dp[i][j]|=dp[i-1][kx]&&(((sum[j]-sum[kx])&x)==x);
    return dp[k][n];
}
signed main(){
    scanf("%lld %lld",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+a[i];
    for(int i=60;i>=0;i--){
        int mid=ans|(1LL<<i);
        if(check(mid))
            ans|=(1LL<<i);
    }
    printf("%lld",ans);
    return 0;
}

```

[最后给自己的博客打个广告](https://www.cnblogs.com/dreagonm/)

---

## 作者：jch123 (赞：1)

## 思路：

显然优先选高位更好，然后看当前这一位选不选，设选了之后的答案为 $x$ 用一个动态规划来检查，$dp(i,j)$ 表示前 $i$ 本书放到 $j$ 个书架上能否得到 $x$，转移方程就为 $dp(i,j)|=dp(k,j-1)\ \texttt{AND}\ [s(k+1,i)\ \texttt{AND}\ x=x]$，然后就很好做了。



## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=62;
int n,k;
int dp[N][N];
ll a[N],s[N];
bool check(ll x)
{
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			for(int k=0;k<i;k++)
				dp[i][j]|=dp[k][j-1]&(((s[i]-s[k])&x)==x);
	return dp[n][k]; 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i],s[i]=s[i-1]+a[i];
	ll ans=0;
	for(ll i=60;i>=0;i--)
	{
		ll x=1ll<<i;
		if(check(ans|x))
			ans|=x;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑贪心，首先更高位（二进制位）的 $1$ 更重要，考虑从大到小枚举 $w$，使得第 $w$ 位是 $1$，如果不行就不要这一位。在更高位 $w'$ 满足的情况尽可能多满足 $w$。

如何判断可不可以？考虑使用 DP 的方式。设 $f_{i,j}$ 表示前 $i$ 本书，分成 $j$ 个书架是否可以每一个第 $w$ 位都是 $1$ 且满足已经成功更高位的 $w'$。

$f_{i,j}=\bigvee_{k=1}^{i} f_{k-1,j}\bigwedge (\sum_{l=k}^{i} a_l \operatorname{and} w' = w')$

意思就是所有满足范围的 $k$，只要有一个满足 $[k,i]$ 区间和不会影响已有的 $w'$ 并且满足 $f_{k-1,j}$ 即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,k,a[61],ans;
bool f[61][61];
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]+=a[i-1];
    }
    for(int w=1ll<<60;w;w>>=1){//枚举位置
        memset(f,0,sizeof(f));
        f[0][0]=1;
        ans|=w;//ans是题解中的w'，加入这一位
        for(int i=1;i<=n;i++)
            for(int j=1;j<=k;j++){
                for(int t=1;t<=i;t++){
                    f[i][j]|=f[t-1][j-1]&&(((a[i]-a[t-1])&ans)==ans);//满足条件
                }
            }
        if(!f[n][k])
            ans^=w;//如果不行再去掉这一位
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：panyanppyy (赞：0)

给出一种暴力**能过**的做法。
## Problem
给出 $n$ 个数，要求分成 $k$ 组，使每组数和的按位与值最大。
## Solution
考虑 dp。设 $f_{i,j}$ 表示把前 $i$ 个数分成 $j$ 个组的贡献。

然后得到转移方程：

$$f_{i,r}=f_{i-1,l-1}\operatorname{AND}(s_r-s_{l-1})[1\le l\le r]$$

$s_i$ 表示 $\sum_{i=1}^{n}$

但是考虑到 $\operatorname{and}$ 操作取最大值不一定是最优解，所以一种想法就诞生了：**把所有状态都存起来！**

每个 $f_{i,j}$ 维护所有转移到当前点的可能的贡献，每次用 $f_{i,j}$ 中的所有数全部转移一遍即可。

由于多个相同的值得贡献相同，所以对每个点开一个 ```unordered_set<>``` 去重。最后求出 $f_{n,k}$ 的最大值就行了。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) x.begin(),x.end()
using namespace std;
const int N=101;
int n,k;
ll a[N],s[N];
unordered_set<ll>f[N][N];
namespace pts1{
	inline void work(){printf("%lld\n",a[1]);}
}
namespace pts100{
	ll ans=0;
	inline void work(){
		for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];//前缀和
		for(int i=1;i<=n;i++)f[i][1].insert(s[i]);//初始化
		for(int i=2;i<=k;i++)
			for(int l=1;l<=n;l++)
				for(int r=l;r<=n;r++)
					for(ll v:f[l-1][i-1])//暴力转移
					f[r][i].insert(v&(s[r]-s[l-1]));
		for(ll i:f[n][k])ans=max(ans,i);//unordered_set<>是无序的
		printf("%lld\n",ans);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	if(n==1)pts1::work();
	else pts100::work();
	return 0;
}
```

---

