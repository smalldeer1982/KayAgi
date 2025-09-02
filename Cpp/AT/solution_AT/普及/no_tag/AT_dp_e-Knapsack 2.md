# Knapsack 2

## 题目描述

$N$ 个物品被编号为 $1, 2, \ldots, N$。对于 $1 \leq i \leq N$，物品 $i$ 的重量是 $w _ i$，价值是 $v _ i$。

太郎君决定从 $N$ 个物品中选择一些放入背包中带回家。背包的容量为 $W$，带回的物品的总重量不能超过 $W$。

请计算太郎君能带回的物品的最大总价值。

## 样例 #1

### 输入

```
3 8
3 30
4 50
5 60```

### 输出

```
90```

## 样例 #2

### 输入

```
1 1000000000
1000000000 10```

### 输出

```
10```

## 样例 #3

### 输入

```
6 15
6 5
5 6
6 4
6 6
3 5
7 2```

### 输出

```
17```

# 题解

## 作者：Haphyxlos (赞：40)

# AT4526 Knapsack 2
[题目传送门](https://www.luogu.com.cn/problem/AT4526)

前置芝士：[AT4525 Knapsack 1](https://www.luogu.com.cn/problem/AT4525)

本题还是很“普通”的背包问题，只是数据范围略有不同，由于$w$达到了$10^{9}$的量级，我们之前的算法无法通过。但我们可以注意到，每样物品的价值上限仅为$10^{3}$，故我们可以另辟蹊径。

设$dp[i][j]$表示 “只考虑前$i$个物品的 情况下，总价值是$j$所需的最小容量”。那么在计算$dp[i][j]$的时候，所有情况 依然可以分成两类考虑： 
1.拿第$i$件物品，那么别的物品的总价值需要凑出$j−v_i$，而由于每样物品 只能拿一件，所以我们只需要考虑前$i−1$件物品的最优选取方式，即最终重量为$dp[i−1][j−v_i]+wi$。

2.不拿第$i$件物品，那么别的物品需要凑出$j$的价值。由于我们选择不拿第$i$件物品，现在只需要考虑前$i−1$件物品的最优选取方式，即最小重量为 $dp[i-1][j]$。 

计算完所有状态的值后，只需要选取满足重量上限的最大价值即可。

然后呢，我们还可以参照01背包的方法，将状态转移方程压成1维。

故，我们可得本题的状态转移方程为：$dp[j]=min(dp[j],dp[j-v[i]]+w[i])$

本题参考代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
int n,m,v[105],w[105],dp[maxm],Max;
int main(int argc,char const *argv[]){
	std::ios::sync_with_stdio(false);
	cin>>n>>m;
	Max=n*1000;//最大价值
	for(int i=1;i<=n;++i)cin>>w[i]>>v[i];
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=n;++i){
		for(int j=Max;j>=v[i];--j){
			dp[j]=min(dp[j],dp[j-v[i]]+w[i]);
		}
	}
	for(int i=Max;i;--i){
		if(dp[i]<=m){
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：lzyqwq (赞：13)

这道题除了数据，其他都完全符合 01 背包的性质。动态规划有三要素：阶段、状态、策略。接下来本篇题解将从这三个方面来讲解这道 01 背包题.

### 一、阶段

阶段和 01 背包一样，都是从 $1$ 到 $n$。

### 二、状态

经过观察我们发现此题的重量有 $10^9$ 那么大，用普通 01 背包的做法是肯定不行的。但是每件物品的价值只有 $10^3$ 那么小，加上 $n$ 不超过 $100$，所以我们可以想到用 $f_{i,j}$ 表示取前 $i$ 个物品价值为 $j$ 的最小重量，这样就不会爆了。

### 三、状态

状态也和 01 背包类似，不过是最小重量，所以状态转移方程为 $f_{i,j}=\min(f_{i-1,j},f_{i-1,j-v_i}+w_i)$。

### 四、二维 01 背包代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[105][100005],v[105],w[105],n,m,s;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&w[i],&v[i]);
		s+=v[i];
	}
	f[0][0]=0;
	for(int i=1;i<=s;i++)
	{
		f[0][i]=0x3f3f3f3f;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=s;j>=0;j--)
		{
			f[i][j]=min(f[i-1][j],j>=v[i]?f[i-1][j-v[i]]+w[i]:0x3f3f3f3f);
		}
	}
	for(int j=s;j>=0;j--)
	{
		if(f[n][j]<=m)
		{
			printf("%d\n",j);
			return 0;
		}
	}
}
```

### 五、一维 01 背包代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[100005],v[105],w[105],n,m,s;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&w[i],&v[i]);
		s+=v[i];
	}
	for(int i=1;i<=s;i++)
	{
		f[i]=0x3f3f3f3f;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=s;j>=v[i];j--)
		{
			f[j]=min(f[j],f[j-v[i]]+w[i]);
		}
	}
	for(int j=s;j>=0;j--)
	{
		if(f[j]<=m)
		{
			printf("%d\n",j);
			return 0;
		}
	}
} 
```

谢谢大家！完结撒花！


---

## 作者：koishi_offical (赞：3)

仔细读题，发现虽然背包体积能很大，但是物品种类和物品价值都很小，
我们可以改变一下一般 01 背包的状态转移方程式：

设 $ f(j) $ 为总价值为 $ j $ 时所需背包体积的最小值，容易得出状态转移方程式为： 
$f(j)=\min(f(j),f(j-v(i))+w(i))$。  

最后输出答案时把价值从高到底扫一遍，遇到所需体积小于等于背包体积的输出并结束程序即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int f[N];
int n,m;
signed main() {
    cin>>n>>m;
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++)
      {
          int w,v;
          cin>>w>>v;
          for(int j=100000;j>=v;j--) f[j]=min(f[j],f[j-v]+w);
      }
    for(int j=100000;j>=0;j--)
      if(f[j]<=m) 
        {
            cout<<j;
            return 0;
        }
}
```


---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4526) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_e)

>有$n$个物品，第$i$个物品重量为$w_i$，价值为$v_i$。要选若干个物品装进一个容量为$m$的背包，求在总重量不超过$m$的情况下，总价值的最大值。

>$n\in[1,100],m\in\left[1,10^9\right],v_i\in\left[1,10^3\right]$。

$m$如此之大，不能再用01背包的原始方法做了。注意到$v_i$如此之小~~（与$m$形成了鲜明的对比）~~，不妨考虑算出对于每个可能达到的总价值，最少需要占用多少背包容量达到。下面就可以~~愉快地~~DP了。

设$dp_{i,j}$表示考虑到第$i$个物品，获得总价值恰好为$j$的情况下，总重量的最小值。边界是$dp_{0,i}=\begin{cases}0&i=0\\\infty&i\neq0\end{cases}$（$i\neq0$时状态不合法），目标是$\max\limits_{dp_{n,i}\leq m}\{i\}$，状态转移方程是$dp_{i,j}=\min\begin{cases}dp_{i-1,j}\\dp_{i-1,j-v_i}+w_i&j\geq v_i\end{cases}$（选或不选第$i$个物品）。由于若$x>\sum\limits_{i=1}^nv_i$，那么总价值$x$不可能到达，所以状态数是$\mathrm O\!\left(n\sum\limits_{i=1}^nv_i\right)$。时间复杂度也是这个。

另外，本题的状态转移方程和01背包极其相似，所以可以跟01背包类似地用将数组压成一维的简便写法。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100,V_I=1000;
int n,m;
int v[N+1],w[N+1];
int dp[N*V_I+1];//dp' 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>w[i]>>v[i];
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;//边界 
	for(int i=1;i<=n;i++)for(int j=N*V_I;j>=v[i];j--)//转移 
		dp[j]=min(dp[j],dp[j-v[i]]+w[i]);
	for(int i=N*V_I;;i--)if(dp[i]<=m)return cout<<i,0;//目标 
	return 0;
}
```

---

## 作者：Cocoly1990 (赞：1)

题意
----
**数据范围奇怪**的01背包

思路简述
----
显然正常的 01 背包是 $\mathcal{O}\left(NW\right)$，然后看一眼数据范围，推算一下，只需要静心等待 5 年，就可以通过了。

考虑怎么优化时间复杂度，再观察一眼数据范围，看看巨小的 $v_i$，我们可以试着优化成 $\mathcal{O}\left(n\sum\limits_{i=1}^n v_i \right)$.

对于状态 $f_i$，对于普通的 01 背包，我们定义其为消耗总**体积**为 $i$ 时获得的**最大价值**，那么我们在这题中完全可以定义 $f_i$ 为获得总**价值**为 $i$ 时消耗的**最小体积**。对于初始化，因为**过程中使 $f_i$ 尽量小**，所以初始化时可以令每个 $f_i=m+1$. 

显然就是将正常 01 背包状态转移中的**体积**和**价值**互换一下，考察的是对 01 背包本质的理解和掌握程度。

有了上述思路，套一下 01 背包的板子，代码（核心部分）就写出来了。
```cpp
for(int i = 1 ; i <= n * 1000 ; i ++) f[i] = m + 1 ; //初始化
for(int i = 1 ; i <= n ; i ++) //01背包板子的改
	for(int j = n * 1000 ; j >= v[i] ; j --)
		f[j] = min(f[j] , f[j - v[i]] + w[i]) ;
```







---

## 作者：Aw顿顿 (赞：0)

是很板子的一道背包题，这里写详细一些。

------

题意与普通 $\texttt{0/1}$ 背包是一致的，而题目的特殊之处在于 $w_i$ 达到了 $10^9$ 的数量级，而 $v_i$ 却只有 $10^3$ 这一量级。考虑通过与普通 $\texttt{0/1}$ 背包设计不同的状态来应对这一性质。

传统 $\texttt{0/1}$ 背包的 $f(i,j)$ 表示考虑前 $i$ 个物品时，填满容量 $j$ 的背包可达到的最大价值。现在显然第二维背包不能承载这样的数据规模，因此我们考虑将价值和体积互换。

具体地，令 $f(i,j)$ 表示考虑前 $i$ 个物品时，达到 $j$ 的价值所需的最小体积，接下来我们思考状态的转移。对于第 $i$ 个物品有取与不取两种方案，不难写出方程：

$$f(i,j)=\min\bigg(\ f(i-1,j),f(i-1,j-v_i)+w_i\ \bigg)$$

如果不选，则直接继承 $i-1$ 种物品的情况；如果选，那就需要加上 $w_i$ 的体积，考虑从 $j-v_i$ 到来的状况。同时使用滚动数组很容易能够把空间复杂度降下来：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1005
#define M 1000005
using namespace std;
int n,m,v[N],w[N],f[M],mx;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&w[i],&v[i]);
        mx+=v[i];
    }for(int i=1;i<=mx;i++)f[i]=1e16;
	for(int i=1;i<=n;i++)
		for(int j=mx;j>=v[i];--j)
			f[j]=min(f[j],f[j-v[i]]+w[i]);
	for(int i=mx;i>=0;i--) {
		if(f[i]<=m){
			printf("%lld\n",i);
			break;
		}
	}return 0;
}
```

但是实现的过程中有几个注意点：

- 如果你使用了 $\texttt{memset}$ 初始化，那么要记得将 $f_0$ 设为 $0$。
- 对于 $f_i<m$ 的判断，需要输出 $i$ 而非 $f_i$。
- 将 $mx$ 设为 $\sum v_i$ 常数上会比设为 $10^3n$ 更优。
- 找答案的时候从后往前找。

---

## 作者：Violet___Evergarden (赞：0)

由于 $w_i \le 10^9$ 数据范围很大，不能直接用[这一题](https://www.luogu.com.cn/problem/AT4525)的方法 dp，又考虑到 $v_i$ 的数据范围很小，所以可以到过来 dp。

设 $dp_{i,j}$ 表示用了前 $i$ 个物品组成 $v_i$ 的和为 $j$ 需要的最小的 $w$。

由于第 $i$ 个物品可以取或者不取，如果不取，则花费的 $w$ 就是 $dp_{i-1,j}$，取则是 $dp_{i-1,j-v_i}+w_i$。

所以：
$$ dp_{i,j}=\min(dp_{i-1,j} , dp_{i-1,j-v_i}+w_i)$$
再枚举 $dp_{n,0} , dp_{n,1} \cdots$，取符合要求的最大的 $v$。


------------

按照这种做法可以通过这一题，但空间复杂度还可以降一维。

设 $dp_j$ 表示用了前 $i$ 个物品组成 $v_i$ 的和为 $j$ 需要的最小的 $w$。

$$dp_j=\min(dp_j,dp_{j-v_i}+w_i)$$

由于我们需要知道前一层的 $dp_0, \cdots$，所以我们要从后往前扩展。

```cpp
#include<iostream>
#define int long long
using namespace std;
int n,mw;
int v[101],w[101],dp[1000001],sum;
signed main()
{
cin>>n>>mw;
for(int i=1;i<=n;i++)
{
  cin>>w[i]>>v[i];
  sum+=v[i];
}
for(int i=1;i<=sum;i++)
{
  dp[i]=1e17;
}
dp[0]=0;
for(int i=1;i<=n;i++)
{
  for(int j=sum;j>=v[i];j--)
  {
    dp[j]=min(dp[j],dp[j-v[i]]+w[i]);
  }
}
for(int i=sum;i>=0;i--)
{
  if(dp[i]<=mw)
  {
    cout<<i<<"\n";
    return 0;
  }
}
return 0;
}
```

---

