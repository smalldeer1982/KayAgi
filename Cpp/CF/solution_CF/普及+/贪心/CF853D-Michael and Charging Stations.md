# Michael and Charging Stations

## 题目描述

Michael has just bought a new electric car for moving across city. Michael does not like to overwork, so each day he drives to only one of two his jobs.

Michael's day starts from charging his electric car for getting to the work and back. He spends $ 1000 $ burles on charge if he goes to the first job, and $ 2000 $ burles if he goes to the second job.

On a charging station he uses there is a loyalty program that involves bonus cards. Bonus card may have some non-negative amount of bonus burles. Each time customer is going to buy something for the price of $ x $ burles, he is allowed to pay an amount of $ y $ ( $ 0<=y<=x $ ) burles that does not exceed the bonus card balance with bonus burles. In this case he pays $ x-y $ burles with cash, and the balance on the bonus card is decreased by $ y $ bonus burles.

If customer pays whole price with cash (i.e., $ y=0 $ ) then 10% of price is returned back to the bonus card. This means that bonus card balance increases by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF853D/b63fc695c9b8ab1ed954e5b28e2ca9818fa92a5c.png) bonus burles. Initially the bonus card balance is equal to 0 bonus burles.

Michael has planned next $ n $ days and he knows how much does the charge cost on each of those days. Help Michael determine the minimum amount of burles in cash he has to spend with optimal use of bonus card. Assume that Michael is able to cover any part of the price with cash in any day. It is not necessary to spend all bonus burles at the end of the given period.

## 说明/提示

In the first sample case the most optimal way for Michael is to pay for the first two days spending 3000 burles and get 300 bonus burles as return. After that he is able to pay only 700 burles for the third days, covering the rest of the price with bonus burles.

In the second sample case the most optimal way for Michael is to pay the whole price for the first five days, getting 1000 bonus burles as return and being able to use them on the last day without paying anything in cash.

## 样例 #1

### 输入

```
3
1000 2000 1000
```

### 输出

```
3700
```

## 样例 #2

### 输入

```
6
2000 2000 2000 2000 2000 1000
```

### 输出

```
10000
```

# 题解

## 作者：activeO (赞：2)

## 题目大意

本题[题面](https://www.luogu.com.cn/problem/CF853D) 也说得比较清楚，类似于小奥的[空瓶换水问题](https://blog.csdn.net/weixin_34417814/article/details/85632709) 的加强版，这里就不细说。

## 思路

因为要尽量省钱，奖励的钱肯定尽可能凑到一起使用，于是我们就把 22000 整成一组，即 20000 元现金，和奖励的 2000 元钱。

最后有两种特殊情况：

- 总价不超过 11000 而最后一个商品是 2000 元。
- 所有商品价格全都是 2000 元。

进行特判即可，另外发现 1000 元，2000 元是假的，将所有钱数除以 100 是一样的。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=3e5+10;
int a[maxn];

int main(){
	
	int n,sum=0,cnt=0;
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum+=a[i]/1000;
		if(a[i]==1000) cnt++;
	}
	
	int tmp=sum*10/11;
	//注意这里不能用else if，两种情况可能都出现。
	if(sum<=11) tmp=sum-a[n]/1000;//特殊情况1
	if((cnt==0)&&(tmp&1)) tmp--;//特殊情况2
	
	printf("%d\n",sum*1000-tmp*100);
	
	return 0;
}
```


---

## 作者：GaryH (赞：1)

# CF853D 题解

看到其他题解用的都是贪心，那我就来一发DP。

我们注意到，题目中的 $1000,2000$ 元是假的，实际上我们可以将所有钱数除以 $100$ ，因为题中最多也就出现了 $\frac{1}{10}$ 的积分，故将所有数除以 $100$ 也不会出现小数的情况。

那么接下来，我们考虑一个暴力的DP，即：

记 $dp_{i,j}$ 代表考虑充前 $i$ 次电，积分卡中剩余 $j$ 元的最小花费。那么转移方程就是：

$dp_{i,j}=max(dp(i-1,j-\frac{a_i}{10})+a_i)$

以及：

$dp_{i,j}=max(dp(i-1,j+k)+a_i-k)$

两个方程分别表示不使用积分卡中的钱，和使用积分卡中的钱，两种情况。

看似这样的复杂度是 $O(NV^2)$ 的，但实际上，每一次积分卡里不可能出现大于 $40$ 元的钱，不然我们在这一次就用掉一部分钱，一定不会更劣。故实际上的时间复杂度是 $O(NV'^2)$ ， $V'=40$ ，空间复杂度则是 $O(NV')$ 。

实际上，该题的空间复杂度还可以用滚动数组优化到 $O(V')$ ，但其实在这个题里 $O(NV')$ 的空间复杂度完全开的下，甚至绰绰有余，所以没必要再优化了。

**code:**

```

const int V(40);
const int N(3e5+10);

int n,dp[N][V+5];

signed main(){
	
	n=read();
	
	rep(i,0,n)rep(j,0,V)dp[i][j]=1e9;
	dp[0][0]=0;
	
	rep(i,1,n){
		
		int x=read()/100,t=x/10;
		
		rep(j,t,V)ckmin(dp[i][j],dp[i-1][j-t]+x);
		// 不使用积分卡中的钱 
		
		rep(j,0,V)rep(k,0,x)if(j+k<V)
		ckmin(dp[i][j],dp[i-1][j+k]+x-k);
		// 使用了k元的积分卡中的钱
		
	} int ans=1e9;
	
	rep(i,0,V)ckmin(ans,dp[n][i]);
	
	return cout<<ans*100,0;
}

```

---

## 作者：仗剑_天涯 (赞：1)

~~众所周知，一道好题的思维难度与代码难度成反比~~

[题目大意](https://www.luogu.com.cn/paste/ppvv3jvj)

思路:

为了钱尽量多得打入奖励卡中，我们在付的时候肯定尽量不要把现金和奖励卡的钱混在一起。

那么我们考虑 $22000$ 元一组，$20000$ 元现金，$2000$元奖励卡。

最后，总价不超过11000而最后一个商品是2000元或所有商品价格全都是2000元时要特判。

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,s,coun,a[300010];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		s+=a[i]/1000;
		if(a[i]==1000)
		{
			coun++;
		}
	}
	t=s*10/11;
	if(s<=11) 
	{
		t=s-a[n]/1000;
	}
	if(coun==0&&(t&1)) 
	{
		t--;
	}
	cout<<s*1000-t*100;
	return 0;	
} 
```


---

## 作者：ran_qwq (赞：0)

不会贪心，所以这里讲一个 dp 做法。

先令 $a_i\leftarrow\dfrac{a_i}{100}$。

设 $f_{i,j}$ 为前 $i$ 次，当前有 $j$ 元优惠，最少需要多少钱。

可以不用优惠，$f_{i,j}\leftarrow f_{i-1,j-a_i}+1000a_i$。

也可以用优惠，$f_{i,j}\leftarrow f_{i-1,f+10a_i-k}+100k$，这里 $k$ 是不用优惠的钱数。

我们有一个贪心策略是买了优惠尽量及时花，所以不会存过多的优惠，$j$ 只用枚举到 $40$。

时间复杂度 $O(n)$ 带 $800$ 倍常数。

```cpp
int n,as=INF,f[N][41];
void QwQ() {
	n=rd(),mst(f,0x3f),f[0][0]=0;
	for(int i=1,x;i<=n;i++) {
		x=rd()/1000;
		for(int j=x;j<=40;j++) f[i][j]=f[i-1][j-x]+x*1000;
		for(int j=0;j<=40;j++) for(int k=max(0,j+x*10-40);k<=x*10;k++) cmin(f[i][j],f[i-1][j+x*10-k]+k*100);
	}
	for(int i=0;i<=40;i++) cmin(as,f[n][i]);
	wr(as,"\n");
}
```

---

## 作者：lfxxx (赞：0)

考虑 dp。

首先所有数除以 $100$。

然后考虑一个朴素 dp 状态 $dp_{i,j}$ 表示考虑前 $i$ 次操作奖励卡中剩余 $j$ 元的最小花费。

转移是简单的，分为是否要使用奖励卡。

考虑优化，我们打表 $dp_{i,j}$ 的差分数组发现 $j$ 越大 $dp_{i,j}$ 总体越来越劣，于是取 $j \leq 49$ 的转移即可通过。

为什么呢？

因为假设奖励卡中有 $40$ 元及以上的钱，把用在后面的操作用在当前一定不劣。

---

## 作者：_qingshu_ (赞：0)

# 题意分析：

类似于经典的买汽水问题。你需要按顺序充 $n$ 次电，每一次充电可能需要花费 $1000$ 或者 $2000$ 元，如果没有使用积分卡，那么本次支付的钱会有 $10\%$ 记录为你的积分，可以下之后任意充当现金使用。询问充完 $n$ 次电的最小花费。

# 思路解析：

因为每一次的选择方案并不会因为后面是原价购买还是使用积分卡影响优劣性，所以可以使用动态规划的方法。

首先，因为每一次产生的最小值是原价购买 $1000$ 的电积分 $100$，所以可以先把所有值除以 $100$ 减小数据范围。

考虑二维动态规划，定义 $dp[i][j]$ 为充了 $i$ 次电最后积分卡里剩余 $j$ 元的积分最小花费。

---

但是我们并不确定会有多少积分，所以考虑在什么情况下花费积分不会更劣且富余积分最多。

假设现在我们卡里有 $x$ 的积分。需要购买 $2000$ 的电（明显购买 $2000$ 的电更能说明最大值），如果原价购买我们可以获得 $(x+200)$ 的积分，在假设后面花出的情况，一共花费 $(1800-x)$ 元。

继续看花费多少积分可以做到与其相同，易得花费 $(20+x)$ 的积分最后效果是一样的。

因为积分从 $0$ 开始一次最多积分 $20$ ，所以 $0\le x\le 20$。积分富余的最大值就是 $40$。

---

# 状态转移：
分别考虑使用积分与不使用积分的情况。

### 不使用积分

$dp[i][j]=\min{(dp[i][j],dp[i-1][j-a/10]+a)}$

其中 $j$ 遍历的是加上这次积的分一共有多少积分。

### 使用积分

在 $(j+k\le40)$ 的情况下：

$dp[i][j]=\min{(dp[i][j],dp[i-1][j+k]+a-k)}$

其中 $j$ 遍历的是最后剩下的积分，$k$ 遍历的是这一次使用了多少积分。


# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a;
long long dp[300010][50];
int main(){
//	freopen("station.in","r",stdin);
//	freopen("station.out","w",stdout);
	cin>>n;
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		cin>>a;
		a/=100;
		for(int j=a/10;j<=40;j++){
			dp[i][j]=min(dp[i][j],dp[i-1][j-a/10]+a);
		}
		for(int j=0;j<=40;j++){
			for(int k=0;k<=a;k++){
				if(j+k<=40){
					dp[i][j]=min(dp[i][j],dp[i-1][j+k]+a-k);
				} 
			}
		}
	}
	long long ans=LONG_LONG_MAX;
	for(int i=0;i<=40;i++){
		ans=min(ans,dp[n][i]);
	} 
	cout<<ans*100; 
}
```
update:

23.12.6: 修改了数学公式逻辑运算符使用问题。

23.12.13: 修改了数字未使用 $\LaTeX$ 的问题。 

23.12,13：修改了错别字。

---

