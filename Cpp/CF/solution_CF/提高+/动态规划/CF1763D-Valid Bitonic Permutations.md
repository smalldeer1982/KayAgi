# Valid Bitonic Permutations

## 题目描述

You are given five integers $ n $ , $ i $ , $ j $ , $ x $ , and $ y $ . Find the number of bitonic permutations $ B $ , of the numbers $ 1 $ to $ n $ , such that $ B_i=x $ , and $ B_j=y $ . Since the answer can be large, compute it modulo $ 10^9+7 $ .

A bitonic permutation is a permutation of numbers, such that the elements of the permutation first increase till a certain index $ k $ , $ 2 \le k \le n-1 $ , and then decrease till the end. Refer to notes for further clarification.

## 说明/提示

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

An array of $ n \ge 3 $ elements is bitonic if its elements are first increasing till an index $ k $ , $ 2 \le k \le n-1 $ , and then decreasing till the end. For example, $ [2,5,8,6,1] $ is a bitonic array with $ k=3 $ , but $ [2,5,8,1,6] $ is not a bitonic array (elements first increase till $ k=3 $ , then decrease, and then increase again).

A bitonic permutation is a permutation in which the elements follow the above-mentioned bitonic property. For example, $ [2,3,5,4,1] $ is a bitonic permutation, but $ [2,3,5,1,4] $ is not a bitonic permutation (since it is not a bitonic array) and $ [2,3,4,4,1] $ is also not a bitonic permutation (since it is not a permutation).

Sample Test Case Description

For $ n=3 $ , possible permutations are $ [1,2,3] $ , $ [1,3,2] $ , $ [2,1,3] $ , $ [2,3,1] $ , $ [3,1,2] $ , and $ [3,2,1] $ . Among the given permutations, the bitonic permutations are $ [1,3,2] $ and $ [2,3,1] $ .

In the first test case, the expected permutation must be of the form $ [2,?,3] $ , which does not satisfy either of the two bitonic permutations with $ n=3 $ , therefore the answer is 0.

In the second test case, the expected permutation must be of the form $ [?,3,2] $ , which only satisfies the bitonic permutation $ [1,3,2] $ , therefore, the answer is 1.

## 样例 #1

### 输入

```
7
3 1 3 2 3
3 2 3 3 2
4 3 4 3 1
5 2 5 2 4
5 3 4 5 4
9 3 7 8 6
20 6 15 8 17```

### 输出

```
0
1
1
1
3
0
4788```

# 题解

## 作者：tuxuanming2024 (赞：9)

## 题意

给出 $n,i,j,x,y$，求有多少个长度为 $n$ 的排列 $a$，满足 $a_i=x,a_j=y$ 且存在一个 $k$ 满足 $2 \le k \le n-1$ 且 $a_1 < a_2 < \cdots a_{k-1} < a_k$ 且 $a_k > a_{k+1} > \cdots > a_{n-1} > a_n$。

## 题解

这里提供一个使用组合数的 $O(n)$ 做法。

首先，显然 $a_k = n$，不然不可能成为转折点。

那么考虑枚举 $k$，然后分类讨论。

- 情况1：$x = n$ 或 $y = n$，以 $x=n$ 为例，那么首先如果 $i=1$ 则无解，答案为 $0$。其次，我们来画个图：

![](https://s1.ax1x.com/2022/12/20/zLrAJI.png)

那么我们就要选择一些数小于 $y$ 放在红色部分，再选择一些大于 $y$ 且小于 $x$ 的数放在蓝色部分，剩余的放在 $x$ 的左边。那么答案为从 $y-1$ 个数中选 $n-j$ 个数的方案 乘 在 $x-y-1$ 个数中选择 $j-i-1$ 个数的方案，即：

$$\dbinom{x-y-1}{j-i-1} \cdot \dbinom{y-1}{n-j}$$

$y=n$ 时同理，答案为

$$\dbinom{y-x-1}{j-i-1} \cdot \dbinom{x-1}{i-1}$$

- 情况2：$k<i$，那么必须满足 $a_i > a_j$，上图：![](https://s1.ax1x.com/2022/12/20/zL6LnK.png)

此时我们要从小于 $y$ 的数中选一些放在红色部分，选大于 $y$ 小于 $x$ 的放在蓝色部分，选大于 $x$ 小于 $n$ 的放在绿色部分，那么贡献为：

$$\dbinom{y-1}{n-j} \cdot \dbinom{x-y-1}{j-i-1} \cdot \dbinom{n-x-1}{i-k-1}$$

- 情况3：$k > j$ 且 $x < y$，同情况2，贡献为

$$\dbinom{x-1}{i-1} \cdot \dbinom{y-x-1}{j-i-1} \cdot \dbinom{n-y-1}{k-j-1}$$

- 情况4：$i < k < j$，同样分两种情况：

当 $x<y$ 时，上图：

![](https://s1.ax1x.com/2022/12/20/zLc3HU.png)

首先：小于 $x$ 的数一定放在红色和蓝色部分，那么就需要满足 $x-1 \le i-1+n-j$。

其次，如果小于 $x$ 的数无法放满红色部分，那么红色的剩余部分无法被填充，因此还需满足 $x-1 \ge i-1$。

那么此时，应从 $x-1$ 个数中选择 $i-1$ 个放在红色部分，剩下的 $x-i$ 个放在蓝色部分，方案数为：

$$\dbinom{x-1}{i-1}$$

然后：考虑大于 $x$ 小于 $y$ 的部分，如果蓝色部分还未被填满，即还剩了 $n-j-(x-i)$ 个位置，就选择一些数放在蓝色的剩余部分，其余的 $y-x-1-[n-j-(x-i)]$ 个数只能放在绿色部分，方案数为：

$$\dbinom{y-x-1}{n-j-(x-i)}$$

注意：绿色部分所填的数的个数不能大于 $k-i-1$，否则填不下，因此还要判断一下 $y-x-1-[n-j-(x-i)] \le k-i-1$。

最后，考虑大于 $y$ 小于 $n$ 的部分，只需选择一些放在橙色部分，方案数为：

$$\dbinom{n-y-1}{j-k-1}$$

所以，这个情况总贡献为：

$$\dbinom{x-1}{i-1} \cdot \dbinom{y-x-1}{n-j-(x-i)} \cdot \dbinom{n-y-1}{j-k-1}$$

当 $x>y$ 时同理，贡献为：

$$\dbinom{y-1}{n-j} \cdot \dbinom{x-y-1}{i-1-[y-1-(n-j)]} \cdot \dbinom{n-x-1}{k-i-1}$$

那么就做完了。

## 代码：

```cpp
#include <bits/stdc++.h>
#ifdef LOCAL
#include "txm/debug.h"
#endif
#define int long long
using namespace std;
using ll=long long;
const int N=105,mod=1e9+7;
int n,px,py,x,y,inv[N],fac[N];
int qpow(int x,int y)
{
	int s=1;
	while(y)
	{
		if(y&1) s=s*x%mod;
		x=x*x%mod,y>>=1;
	}
	return s;
}
int C(int n,int m)
{
	return n<m?0:fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void solve()
{
	cin>>n>>px>>py>>x>>y;
	int ans=0;
	if(x==n)
	{
		if(px==1||px==n) {cout<<"0\n"; return;}
		cout<<C(n-y-1,py-px-1)*C(y-1,n-py)%mod<<'\n';
	}
	else if(y==n)
	{
		if(py==1||py==n) {cout<<"0\n"; return;}
		cout<<C(n-x-1,py-px-1)*C(x-1,px-1)%mod<<'\n';
	}
	else
	{
		int ans=0;
		for(int i=2;i<n;i++)
		{
			if(i==px||i==py) continue;
			if(i<px&&x>y) ans=(ans+C(y-1,n-py)*C(x-y-1,py-px-1)%mod*C(n-x-1,px-i-1)%mod)%mod;
			if(i>py&&x<y) ans=(ans+C(x-1,px-1)*C(y-x-1,py-px-1)%mod*C(n-y-1,i-py-1)%mod)%mod;
			if(px<i&&i<py)
			{
				int s1=y-x-1-(n-py-(x-px)),s2=x-y-1-(px-1-(y-1-(n-py)));
				if(x<y&&x>=px&&x-1<=px-1+n-py && s1<=i-px-1)
					ans=(ans+C(x-1,px-1)*C(y-x-1,n-py-(x-px))%mod*C(n-y-1,py-i-1)%mod)%mod;
				if(x>y&&y-1>=n-py&&y-1<=px-1+n-py && s2<=py-i-1)
					ans=(ans+C(y-1,n-py)*C(x-y-1,px-1-(y-1-(n-py)))%mod*C(n-x-1,i-px-1)%mod)%mod;
			}
		}
		cout<<ans<<'\n';
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	fac[0]=1;
	for(int i=1;i<=100;i++) fac[i]=fac[i-1]*i%mod;
	inv[100]=qpow(fac[100],mod-2);
	for(int i=99;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

## 后记

这场 CF 我上来就开 D 题，做了近两个小时还是做出来了，有惊无险

于是就：

![](https://s1.ax1x.com/2022/12/20/zLgUIg.png)

---

## 作者：ningago (赞：8)

题目输入的 $i,j,x,y$ 记作 $I,J,X,Y$。

因为排列要求先单调递增，再单调递减，所以递增与递减的分界线一定是 $n$，即最大的那个数。

所以决策顺序就很自然了：先把 $n$ 选出来放中间，然后按顺序选择 $[1,n)$ 中的数。对于第 $i$ 个数考虑他是放在 $n$ 左边还是右边，因为单调性，他只能排在与 $n$ 相邻的位置，因此除了左右的决策没有方案数贡献。

记 $f_{i,j}$ 表示已经了 $[1,i]$ 的数，$n$ 左边有 $j$ 个的方案数。

对于 $i\ne X,Y$ 时，转移就没有限制，按照组合意义转移即可。

$$f_{i,j}=f_{i,j}+f_{i-1,j},f_{i,j+1}=f_{i,j+1}+f_{i-1,j},j\in[1,i)$$

否则，只有满足 $X$ 或 $Y$ 位置限制的才会被转移，分左边和右边考虑。

- 如果 $X \geq J$，则 $f_{i,I}=f_{i,I}+f_{i - 1,I - 1}$。
- 如果 $X - (n - I + 1) \geq 0$，则 $f_{i,X - (n - I + 1)} = f_{i,X - (n - I + 1)}+f_{i - 1,X - (n - I + 1)}$。

$Y$ 同理。

答案输出时，如果 $\max\{X,Y\}\ne n$，则答案为 $\sum_{i=1}^{n-2}f_{n-1,i}$。

否则如果 $\max\{X,Y\}$ 对应的 $I$ 或 $J \ne 1$ 且 $\ne n$ 时，答案为 $f_{n-1,I-1}$ 或 $f_{n-1,J-1}$。

否则答案为 $0$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 110
#define mod 1000000007

int T;
int n,I,J,X,Y;

int dp[N][N];

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d",&n,&I,&J,&X,&Y);
        if(X > Y)
        {
            X ^= Y ^= X ^= Y;
            I ^= J ^= I ^= J;
        }
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for(int i = 1;i < n;i++)
        {
            if(i == X)
            {
                if(X >= I)
                    dp[i][I] += dp[i - 1][I - 1];
                if(X - (n - I + 1) >= 0)
                    dp[i][X - (n - I + 1)] += dp[i - 1][X - (n - I + 1)];
            }
            else if(i == Y)
            {
                if(Y >= J)
                    dp[i][J] += dp[i - 1][J - 1];
                if(Y - (n - J + 1) >= 0)
                    dp[i][Y - (n - J + 1)] += dp[i - 1][Y - (n - J + 1)];
            }
            else
            {
                for(int j = 0;j < i;j++)
                {
                    dp[i][j] += dp[i - 1][j];
					dp[i][j] %= mod;
                    dp[i][j + 1] += dp[i - 1][j];
					dp[i][j + 1] %= mod;
                }
            }
        }
        int ans = 0;
		if(Y != n)
		{
        	for(int i = 1;i <= n - 2;i++)
			{
        	    ans += dp[n - 1][i];
				ans %= mod;
			}
		}
		else if(J != n && J != 1)
			ans = dp[n - 1][J - 1];
		printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：SnowTrace (赞：3)

这里提供一种 $ O(n \log n)$ 的做法。

我们不妨设 $i<j$ , $x<y$ .

如果不是这样的话，我们考虑把序列反过来，这个时候情况总数还是不变的。

然后我们先分成两种情况：

1. y 的位置是最大值，这种情况直接一个组合数的相乘搞定，先处理从 1 到 i 的情况数，再乘上 i+1 到 j 的情况数，这个时候最后的一段就是固定的了。

答案是： $C^{i-1}_{x-1} \times C^{j-i-1}_{y-x-1}$

2. y 的位置不是最大值，那我们就考虑枚举最大值的位置在哪里，这里再分成两种情况，不妨设最大值的位置为 $kk$ .
	
    1) $ i < kk < j$ ：
   
   在这种情况下，大于 y 的元素肯定都在位置 i 和 j 之间，但是总共的空格数量是 $j-i+1$ 个，其他的地方都应该放的是在 $x,y$ 间的元素，共 $(j-i-1-(n-y))$ 个，而且这些元素位置肯定都在 $i,kk$ 之间（如果不是这样的话整个排列就不满足题中性质了） 。
   
   这样 位置 i,j 之间的元素就考虑好了，为 $C_{y-x-1}^{j-i-1-(n-y)} \times C_{n-y-1}^{j-kk-1}$ 个，然后再乘上两边可以放的情况，为 $C^{i-1}_{x-1}$ ，因为如果左边放好了，右边就确定了。
   
   
    2. $kk>j$ 
    
    和 $y = n$ 的情况是类似的，答案为 $C^{i-1}_{x-1} \times C_{y-x-1}^{j-i-1} \times C_{n-y-1}^{kk-j-1}$ ，就是把序列拆成三段，第一段是在 i 前面的，第二段是在 $i,j$ 之间的，第三段实在 $kk,j$ 之间的，然后这个时候最后一段唯一确定，把这三个乘起来就可以了。
    
    代码:
    
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1000000007;
bool cmp(pair<int,int> a,pair<int,int> b){
	return a.first<b.first;
}int f[200005];
int qp(int p,int q){
	int ans = 1,pro = p;
	while(q>0){
		if(q&1)ans = ans*pro%mod;
		pro = pro*pro%mod,q>>=1;
	}return ans;
}int niyuan(int x){
	return qp(x,mod-2);
}int c(int n,int m){
	if(m>n)return 0;
	if(n<0 or m<0)return 0;
	return f[n]*niyuan(f[m])%mod*niyuan(f[n-m])%mod;
}//上面为组合数计算
void solve(){
	int n,i,j,x,y;
	cin>> n >> i >> j >> x >> y;
	if(x>y)i = n-i+1,j = n-j+1,swap(x,y),swap(i,j);
  //如果x>y，反转原序列
	int ans =0;
	if(y == n){
		if(j == n)cout << 0 << endl;
		else cout << c(x-1,i-1)*c(n-x-1,j-i-1)%mod << endl;return;
	}
	for(int kk = i+1;kk<j;kk++){
     /*上文中第一种情况*/                           
		ans+=c(y-x-1,j-i-1-(n-y))*c(n-y-1,j-kk-1)%mod;ans%=mod;
	}ans*=c(x-1,i-1),ans%=mod;
	for(int kk = j+1;kk<n;kk++){
  	 /*上文中第二种情况*/
		ans+=c(x-1,i-1)*c(y-x-1,j-i-1)%mod*c(n-y-1,kk-j-1)%mod;ans%=mod;
	}assert(ans>=0);
	cout << ans << endl;
}
signed main(){
	f[0] = 1;
	for(int i =1;i<=200000;i++)f[i] = f[i-1]*i%mod;
	int t;cin>> t;
	while(t--){
		solve();
	}
}
```

需要注意的是，原题中说这个排列必须有一段是下降的，也就是说全部上升的排列是不行的，这是一个坑点，考场上坑了我 30 min qwq 。

---

## 作者：MSqwq (赞：3)

考虑如何构造一个双调的序列。可以参照 [P7915 [CSP-S 2021] 回文](https://www.luogu.com.cn/problem/P7915) ，就是两个单调上升的序列，然后把后面那个翻转一下，再拼接起来就好了。  
会了这个之后，其实本题就是让你把 $n$ 个数分成两堆（下面我称之为左边和右边），然后保证题目的两个数确定的要求，就可以了。  
那么考虑 $f_{now,a,b}$ 表示当前讨论的数是 $now$ 已经排好了 $1$ 到 $now-1$ ，排列方式为左边有 $a$ 个数，右边有 $b$ 个数。  
假设不考虑本题那两个数的要求，那么显然就可以转移：  
$f_{now+1,a+1,b}=f_{now+1,a+1,b}+f_{now,a,b}$  
$f_{now+1,a,b+1}=f_{now+1,a,b+1}+f_{now,a,b}$  
边界就是 $f_{1,0,0} = 1$。  
考虑有 $a_i = x \ \ a_j = y$ 限制的时候。  
是不是只会影响当 $now = x$ 或者 $now = y$ 的时候，那么其实就是，对于第一个转移要么 $a +1\ne i $，要么 $now = x$，同理要么 $a+1 \ne j$ 要么 $now = y$。  
对于第二个要特殊看一下，因为 $b+1$ 是在右边多怎加一个，但是要经过反转的操作，所以反转回原数组就应该是 $n-(b+1)+1 = n-b$。  
那么最终的方程就是:  
$f_{now+1,a+1,b}=f_{now+1,a+1,b}+ f_{now,a,b}\ \ (a+1\ne i \ \lor now=x)\ \land \ (a+1\ne j \ \lor\ now=y)$  
$f_{now+1,a,b+1}=f_{now+1,a,b+1}+ f_{now,a,b}\ \ (n-b\ne i \ \lor\ now=x)\ \land \ (n-b\ne j \ \lor\ now=y)$   
最后算答案的时候就枚举每个单峰，即 $f_{n+1,a,n-a}$ 求和即可。   
复杂度: $O(n^3)$。     
代码：  
https://codeforces.com/contest/1763/submission/186054883

---

## 作者：Day_Tao (赞：2)

严格 $\mathcal{O}(n+T)$ 做法。

首先我们让 $i<j\wedge x<y$，方法就是先保证 $i<j$，若 $x>y$ 则翻转一下序列，与原问题等价。

这样转化完之后考虑会出现哪几种情况。我们令 $k$ 表示 $n$ 所在的位置。

- $k=j$

  显然满足这个条件当且仅当 $y=n$。我们先将这种情况特判掉。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/uyucve0u.png)

  容易发现确定蓝色部分和绿色部分选什么之后就可以唯一确定黄色部分选的情况，所以只考虑蓝色的和绿色的。

  不难发现，在合法情况下，蓝色部分的值域为 $[1,x)$，长度为 $i-1$；绿色部分的值域是 $(x,y)$，长度为 $j-i-1$。所以这种情况的方案数为：

  $$\binom{x-1}{i-1}\binom{y-x-1}{j-i-1}$$

- $i<k<j$

  ![](https://cdn.luogu.com.cn/upload/image_hosting/zqy93wir.png)

  （黄色部分的长度为 $n-y$，即 $[y+1,n]$ 的数都在黄色部分中）

  蓝色部分的贡献仍然不变，即 $\binom{x-1}{i-1}$。

  考虑黄色部分的贡献如何计算。显然 $k$ 一定在黄色部分之中。不妨把黄色这段抠出来想，现在要放 $n-y$ 个数，要求是一个峰的形状，峰顶为 $n$，初始只有 $n$ 一个数，剩下的每个数从大到小依次加入，每次只能加在已经确定的序列的最左边或者最右边。这样黄色部分的贡献就是 $2^{n-y-1}$。

  绿色部分的贡献也是好算的，即在值域 $(x,y)$ 的数中选 $j-i-1-(n-y)$ 个数。

  所以这种情况的总贡献为：

  $$2^{n-y-1}\binom{x-1}{i-1}\binom{y-x-1}{j-i-1-(n-y)}$$

- $j<k$

  ![](https://cdn.luogu.com.cn/upload/image_hosting/csv2k2d4.png)

  黄色部分的定义跟第二种情况的一样。蓝色和绿色部分的贡献跟第一种情况中的一样，黄色部分的贡献跟第二种情况中黄色部分的贡献也一样，乘一下就能得到这种情况的贡献了：

  $$2^{n-y-1}\binom{x-1}{i-1}\binom{y-x-1}{j-i-1}$$

综上，对于 $k=j$ 时的贡献为：

$$\binom{x-1}{i-1}\binom{y-x-1}{j-i-1}$$

对于 $k\neq j$ 时的贡献为：

$$2^{n-y-1}\binom{x-1}{i-1}\left(\binom{y-x-1}{j-i-1-n+y}+\binom{y-x-1}{j-i-1}\right)$$

注意 $i=x\wedge j=y$ 时存在一个单调递增的排列合法，这种情况要减去。

组合数和 $2$ 的次幂预处理即可。代码实现跟上面的柿子完全一致。

**Code：**

```cpp
int n,i,j,x,y;
inline void SOLVE(){
	n=rd(),i=rd(),j=rd(),x=rd(),y=rd();
	if(i>j)swap(i,j),swap(x,y);if(x>y)swap(x,y),swap(i,j),i=n-i+1,j=n-j+1;
	if(y==n)printf("%lld\n",(C(x-1,i-1)*C(y-x-1,j-i-1)-(i==x&&j==y)+mod)%mod);
	else printf("%lld\n",(C(x-1,i-1)*pow2[n-y-1]%mod*
    (C(y-x-1,j-i-1-n+y)+C(y-x-1,j-i-1))-(i==x&&j==y)+mod)%mod);
	return ;
}
```

---

## 作者：stntn (赞：2)

## 题意

求一个长度为 $n$，固定位置 $i$ 为 $x$，位置 $j$ 为 $y$ 的**单峰**排列的数量。

## 分类讨论

首先如果某个已经固定的位置为最大值 $n$。

若 $x=n$：

$$
Ans=\binom{y-1}{n-j}\binom{n-y-1}{j-i-1}
$$

若 $y=n$：

$$
Ans=\binom{x-1}{i-1}\binom{n-x-1}{j-i-1}
$$

以 $x=n$ 为例，先从小于 $y$ 的数中取 $n-j$ 个数出来，再从 $(y,n)$ 中选 $j-i-1$ 个数出来即为答案，应该不难理解。

否则最大值的位置不固定，枚举最大值即可。

同样按照“取数”的思想，从可以选的数中取出当前需要的数量，逐步将最大值左边或右边填满，则另一边也随之固定。

令枚举的峰值位置为 $p$。

当 $p < i$ 贡献为（$x>y$）：


$$
\binom{n-x-1}{i-p-1}\binom{x-y-1}{j-i-1} \binom{y-1}{n-j}
$$

当 $p >j$ 贡献为（$y<x$）：

$$
\binom{x-1}{i-1} \binom{y-x-1}{j-i-1} \binom{n-y-1}{p-j-1}
$$

当 $i < p < j$ 时的贡献为：

$x>y$ ：

$$
\binom{y-1}{n-j} \binom{x-y-1}{i-1-[y-1-(n-j)]} \binom{n-x-1}{p-i-1}
$$

$x<y$：

$$
\binom{x-1}{i-1} \binom{y-x-1}{n-j-[x-1-(i-1)]} \binom{n-y-1}{j-p-1}
$$

稍微解释一下 $i<p<j$ 的时候是怎么算的，以 $x>y$ 为例：

首先从 $[1,y)$ 这些数中取出 $n-j$ 个数放入 $[j+1,n]$ 中，其余放在 $i$ 左边。此时小于 $x$ 的数还剩 $x-y-1$ 个，$[1,i]$ 中还需要 $i-1-[y-1-(n-j)]$ 个数，所以取这么多个放在 $i$ 左边把其填满，剩余的放在 $p$ 和 $j$ 之间。然后就没有限制了，用大于 $y$ 的数把 $p$ 左边填满，右边也就固定下来了。

复杂度 $O(\sum n)$。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 110
#define int long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f
#define mod 1000000007
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int T,n,p1,p2,a1,a2,ans,fac[N],fav[N];
inline int qpow(int a,int b)
{
	int res=1;
	for(;b;b>>=1,(a*=a)%=mod) if(b&1) (res*=a)%=mod;
	return res;
}
inline int C(int n,int m){if(m>n||n<0||m<0) return 0;return fac[n]*fav[m]%mod*fav[n-m]%mod;}
signed main()
{
	read(T);
	fac[0]=1;
	rep(i,1,100) fac[i]=fac[i-1]*i%mod;
	fav[100]=qpow(fac[100],mod-2);
	per(i,99,0) fav[i]=(i+1)*fav[i+1]%mod;
	while(T--)
	{
		read(n,p1,p2,a1,a2);ans=0;
		if(p1==1&&a1==n){printf("0\n");continue;}
		if(p2==n&&a2==n){printf("0\n");continue;}
		if(a1==n){printf("%lld\n",C(a2-1,n-p2)*C(n-a2-1,p2-p1-1)%mod);continue;}
		if(a2==n){printf("%lld\n",C(a1-1,p1-1)*C(n-a1-1,p2-p1-1)%mod);continue;}
		rep(i,2,n-1) if(i^p1&&i^p2)
		{
			if(i<p1)
			{
				if(a1<a2) continue;
				(ans+=C(n-a1-1,p1-i-1)*C(a1-a2-1,p2-p1-1)%mod*C(a2-1,n-p2)%mod)%=mod;
			}
			else if(p1<i&&i<p2)
			{
				if(a1<a2) (ans+=C(a1-1,p1-1)*C(a2-a1-1,n-p2-(a1-1-p1+1))%mod*C(n-a2-1,p2-i-1)%mod)%=mod;
				else (ans+=C(a2-1,n-p2)*C(a1-a2-1,p1-1-(a2-1-n+p2))%mod*C(n-a1-1,i-p1-1)%mod)%=mod;
			}
			else
			{
				if(a1>a2) continue;
				(ans+=C(a1-1,p1-1)*C(a2-a1-1,p2-p1-1)%mod*C(n-a2-1,i-p2-1)%mod)%=mod;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

[题目链接](https://codeforces.com/contest/1763/problem/D)

组合数学题。vp 的时候花了好长时间推柿子：）

没有写具体柿子，具体推导可以看别的题解。这篇主要讲解推导思路。

容易发现，$x>y$ 的答案序列与 $x<y$ 的答案序列存在一一对应的关系，即翻转。所以我们可以只关注 $x<y$ 的情况。

显然峰值点的必要不充分条件是 $a_p=n$。（不充分是因为 $p=1,p=n$ 时是错误的）。计数问题主打一个不重不漏。可以考虑枚举峰值的位置。而我们推导柿子的基础是，**在存在单调性且取值确定的连续段中，排法是唯一的。**

若峰值的位置 $p$ 恰好就是 $y$，需要特判一下。整个序列就会被分成三段。

若峰值的位置 $p$ 在 $(i,j)$ 之间。序列会分成：${\color{red}{[1,i-1]}},[i],{\color{blue}{[i+1,p-1]}},[p],{\color{purple}{[p+1,j-1]}},[j],{\color{green}{[j+1,n]}}$ 的段，有些可能不存在。这样我们就已知 $a_i=x,a_j=y,a_p=n$。**这样分是满足单调性的，然而求出来各部分排法的顺序是至关重要的，这样才能满足不重不漏。最后用乘法原理相乘即可。** 我们考虑先确定 $[1,i-1]$ 的取值，与后面毫无关联，再确定 $[p+1,j-1]$ 的取值，接下来确定 $[i+1,p-1]$ 的取值。而最后一段由于别的都已确定，只有唯一的排法。具体柿子可以看代码。

若峰值的位置 $p$ 在 $(j,n)$，序列会分成：${\color{red}{[1,i-1]}},[i],{\color{blue}{[i+1,j-1]}},[j],{\color{purple}{[j+1,p-1]}},[p],{\color{green}{[p+1,n]}}$ 的段，有些可能不存在。同样的，先确定 $[1,i-1]$ 的取值，与后面毫无关联，再确定 $[i+1,j-1]$ 的取值，接下来确定 $[j+1,p-1]$ 的取值。而最后一段由于别的都已确定，只有唯一的排法。具体柿子可以看代码。

```cpp
mint calc(int n,int p,int q,int x,int y){
	mint ans=0;
	const int posc=q-p-1,valc=y-x-1;
	const mint gg=C(x-1,p-1);
	F(i,p+1,q-1){
		mint tot=gg;
		tot*=C(valc,n-q-x+p);
		tot*=C(n-y-1,q-i-1);
		ans+=tot;
	}
	F(i,q+1,n-1){
		mint tot=gg;
		tot*=C(valc,posc);
		tot*=C(n-1-y,i-1-q);
		ans+=tot;
	}
	return ans;
}
void solve(){
	int n=read(),i=read(),j=read(),x=read(),y=read();
	if(x>y) i=n-i+1,j=n-j+1,swap(i,j),swap(x,y);
	if(y==n){
		mint ans=C(n-x-1,j-i-1);
		ans*=C(x-1,i-1);
		if(j==1||j==n) ans=0;
		printf("%lld\n",ans.x);
		return;
	}
	printf("%lld\n",calc(n,i,j,x,y));
}
```

---

## 作者：EBeason (赞：0)

提供一种 $\mathcal{O}(N)$ 的做法，~~虽然比较麻烦~~。  
首先考虑他要先递增，然后再递减，那么我们考虑枚举峰值的位置。  
峰值可能位于两边或者 $i$ 和 $j$ 的中间，通过组合计数来得到答案。  
然后考虑不重不漏的选，先选范围小的，确定了范围小的，再选范围大的，依次处理。  
### 注意特殊情况
对于 $x,y$ 中已经有 $N$ 特殊处理。  
### 坑点
对于有一组给出的在边界且数值为N，那么答案为0。
对于 $x==y$ 的情况，答案为0。  
详细情况请参考代码。  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
const int MaxN=1e6+100;
const int INF=1e9;
int T,N,M,jc[MaxN],ijc[MaxN],P=1e9+7;
template<class T>
inline void qread(T &sum)
{
	sum=0;int boo=1;
	char x=getchar();
	while(x<'0'||x>'9'){if(x=='-')boo=-1;x=getchar();}
	while(x>='0'&&x<='9'){sum=(sum<<1)+(sum<<3)+x-'0';x=getchar();}
	sum*=boo;
}
template<class T>
void qput(T x)
{
	if(x<0) {x=-x;putchar('-');}
	if(x>9) qput(x/10);
	putchar(x%10+48);
}
inline int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=res*x%P;
		x=x*x%P;
		y>>=1;
	}
	return res;
}
inline void pre()
{
	N=1e3;
	jc[0]=1;jc[1]=1;ijc[0]=1;
	for(int i=1;i<=N;i++)
	jc[i]=jc[i-1]*i%P;
	ijc[N]=ksm(jc[N],P-2);
	for(int i=N-1;i>=1;i--)
	ijc[i]=ijc[i+1]*(i+1)%P;
}
inline int C(int n,int m)
{
	if(n<0||m<0) return 0;
	if(n<m) return 0;
	return jc[n]*ijc[m]%P*ijc[n-m]%P;
}
inline void Solve()
{
	qread(N);
	int i,j,x,y;
	qread(i);qread(j);qread(x);qread(y);
	int ans=0;
	if(x==N||y==N)
	{
		if(y==N)
		{
			swap(i,j);swap(x,y);
		}
		if(i<j)
		{
			ans=C(y-1,N-j)*C(x-y-1,j-i-1)%P;
		}
		else
		{
			ans=C(y-1,j-1)*C(x-y-1,i-j-1)%P;
		}
		if(i==1||i==N)
		ans=0;
	}
	else
	{
		if(i>j)
		{
			swap(i,j);swap(x,y);
		}
		for(int t=i+1;t<j;t++)
		{
			if(x<y)
			{
				int ts;
				ts=(N-y-1)-(j-t-1);
				ans+=C(N-y-1,j-t-1)*C(y-x-1,t-i-1-ts)%P*C(x-1,i-1)%P;
				ans%=P;
			}
			else
			{
				int ts=(N-x-1)-(t-i-1);
				ans+=C(N-x-1,t-i-1)*C(x-y-1,j-t-1-ts)%P*C(y-1,N-j)%P;
				ans%=P;
			}
		}
		if(x<y)
		{
			for(int t=j+1;t<N;t++)
			{
				ans+=C(y-x-1,j-i-1)*C(x-1,i-1)%P*C(N-y-1,t-j-1)%P;
				ans%=P;
			}
		}
		else
		{
			for(int t=2;t<i;t++)
			{
				ans+=C(x-y-1,j-i-1)*C(y-1,N-j)%P*C(N-x-1,i-t-1)%P;
				ans%=P;
			}
		}
	}
	if(x==y) ans=0;
	qput(ans);putchar('\n');
}
signed main()
{
	pre();
	qread(T);
	while(T--) Solve();
}
```

---

## 作者：Cxny (赞：0)

既然有单次 $O(n)$ 解法，那为什么要放 $n\le100$？？？

不妨设 $x<y$。若不然，我们可以翻转整个序列，得到的方案数不变。

先考虑 $y<n$ 的情况。

尝试枚举峰顶 $k$ 的位置。显然 $k$ 不能在 $[1,i-1]$ 内。注意必须有上升和下降段，$k$ 不能取 $1$ 或 $n$。

无论 $k$ 在何处，$[1,i-1]$ 所有数都在 $[1,x-1]$ 内，方案数为 $\binom{x-1}{i-1}$。

- $k\in[i+1,j-1]$：$[y+1,n]$ 的数必须放在 $[i+1,j-1]$，这将会占去 $n-y$ 个空位。剩余空位用来放 $[x+1,y-1]$的数。贡献为 $\binom{n-y-1}{j-k-1}\binom{y-x-1}{j-i-1-(n-y)}$。
- $k\in[j+1,n-1]$：$[i+1,j-1]$ 必须放 $[x+1,y-1]$ 的数。$[j+1,k-1]$ 必须放 $[y+1,n-1]$ 的数。贡献为 $\binom{y-x-1}{j-i-1}\binom{n-y-1}{k-j-1}$。

于是答案为 
$$
\binom{x-1}{i-1}\sum_{k=i+1}^{j-1}\binom{n-y-1}{j-k-1}\binom{y-x-1}{j-i-1-(n-y)}+\binom{x-1}{i-1}\sum_{k=j+1}^{n-1}\binom{y-x-1}{j-i-1}\binom{n-y-1}{k-j-1}
$$
$y=n$ 的情况相当于钦定了峰顶的位置，答案为 $\binom{x-1}{i-1}\binom{y-x-1}{j-i-1}$。

代码就不放了。注意特判 $y=n$ 且无解的情况。

---

