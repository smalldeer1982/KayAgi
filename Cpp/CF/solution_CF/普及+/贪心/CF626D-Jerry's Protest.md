# Jerry's Protest

## 题目描述

Andrew and Jerry are playing a game with Harry as the scorekeeper. The game consists of three rounds. In each round, Andrew and Jerry draw randomly without replacement from a jar containing $ n $ balls, each labeled with a distinct positive integer. Without looking, they hand their balls to Harry, who awards the point to the player with the larger number and returns the balls to the jar. The winner of the game is the one who wins at least two of the three rounds.

Andrew wins rounds 1 and 2 while Jerry wins round 3, so Andrew wins the game. However, Jerry is unhappy with this system, claiming that he will often lose the match despite having the higher overall total. What is the probability that the sum of the three balls Jerry drew is strictly higher than the sum of the three balls Andrew drew?

## 说明/提示

In the first case, there are only two balls. In the first two rounds, Andrew must have drawn the $ 2 $ and Jerry must have drawn the $ 1 $ , and vice versa in the final round. Thus, Andrew's sum is $ 5 $ and Jerry's sum is $ 4 $ , so Jerry never has a higher total.

In the second case, each game could've had three outcomes — $ 10-2 $ , $ 10-1 $ , or $ 2-1 $ . Jerry has a higher total if and only if Andrew won $ 2-1 $ in both of the first two rounds, and Jerry drew the $ 10 $ in the last round. This has probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626D/278aa205373ddbc5533818ea01281d6e5a703b92.png).

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
0.0000000000
```

## 样例 #2

### 输入

```
3
1 2 10
```

### 输出

```
0.0740740741
```

# 题解

## 作者：Mav11Young (赞：5)

一道dp~~水~~题

dp[1/2][i]表示第1/2次A拿出的球与B拿出的球的差为i的概率（i>0）

dp[3][i]表示前两次A拿出的球与B拿出的球的差的和为i的概率（i>0）

f[i]纪录dp[3]的前缀和，也就是前两次A与B的差小于等于i的概率

于是最后就可以枚举第3次B拿出的球以及A拿出的球，以及B与A的差x，
然后ans+=f[x-1]即可。

但在过程中还有一点小问题，这是一道概率题，在求dp数组以及统计ans时，需要除以“总概率”。这个总概率也就是从n个球中选出两个，并且保证其中一个大于另一个的概率。这也就是组合数C（n，2），即n*（n-1）/2。所以要在刚开始的时候定义一个tmp，每次求dp和ans时都乘上，然后就可以~~愉快的~~A掉这题了。

上代码：
```cpp
#include<bits/stdc++.h>
#define debug(a) cout<<#a<<"="<<a<<endl;
#define LL long long
using namespace std;
const int N=2005;
int a[N];
double dp[5][10005],f[10005];
int main(){
	int n,mx=-1e9,mi=1e9;
	scanf("%d",&n);
	double tmp=1.0/(1ll*n*(n-1)/2);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),mx=max(mx,a[i]),mi=min(mi,a[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i]>a[j])dp[1][a[i]-a[j]]+=tmp,dp[2][a[i]-a[j]]+=tmp;
	for(int i=1;i<=mx-mi;i++)
		for(int j=1;j<=mx-mi;j++)dp[3][i+j]+=dp[1][i]*dp[2][j];
	for(int i=1;i<=2*(mx-mi);i++)f[i]=f[i-1]+dp[3][i];
	double ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[j]>a[i])ans+=f[a[j]-a[i]-1]*tmp;
	printf("%.10lf",ans);
	return 0;
}
```


---

## 作者：IGA_Indigo (赞：1)

## 题目大意
两个人 $A$ 和 $B$ 摸 $n$ 个球，球上有各不相同的大小，一共摸三回合，每个回合两个人都摸一个，然后再放回去，问前两回合 $A$ 摸的大于 $B$ 但是三个球加起来 $B$ 大于 $A$ 的概率。
## 大体思路
暴力解决显然是过不了的，我们观察一下这道题。

设 $A$ 和 $B$ 摸到的三个球分别为 $a_1$、$a_2$、$a_3$、$b_1$、$b_2$ 和 $b_3$。

那么题目给出的这个摸球的方案的要求是：

$a_1<b_1$ 且 $a_2<b_2$ 且 $a_1+a_2+a_3<b_1+b_2+b_3$。

化简一下得到：

$(a_1-b_1)+(a_2-b_2)<(b_3-a_3)$，显然 $b_3$ 大于 $a_3$ 很多。

我们首先得出一共可能摸出的方案数，一共有 $n(n-1)/4$ 种。

我们再来枚举判断一下能够满足题目所给条件的组数即可得到概率。

考虑 DP。
### 状态设置与转移
$f_{p,q}$ 表示在不等号左边（$p=1$），不等号右边（$p=2$），答案等于 $q$ 的方案数。

当 $p=1$ 的时候，我们处理的是 $(b_3-a_3)$，从前到后二层 for 循环查询一下，找到合法的（相减大于零的），$f_{1,a_{i,j}}$ 就加一。

当 $p=2$ 的时候，我们处理的是 $(a_1-b_1)+(a_2-b_2)$，从前到后二层 for 循环一下，转移方程是：

$f_{2,i+j}=f_{2,i+j}+f_{1,i}\times f_{1,j}$。

一种方法是先求出每个球可能被摸出来的概率，排序一下优化查找（由于是求概率，所以说顺序什么的没有影响），然后像上面一下转移一下，最后 for 循环处理下答案即可。

详见代码，全文注释。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2005];
long double f[5][5005];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);//由于是求概率，所以说顺序什么的没有影响，从小到大比较好处理 
	int fm=0;//分母
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){//排完序就不用考虑乱七八糟的东西了 
			if(a[j]>a[i]){
				f[1][a[j]-a[i]]++;
				fm++;					
			}
		}
	}
	for(int i=1;i<=5000;i++){//把分母除进去 
		f[1][i]/=fm;//就得到抽到每个球的概率了 
	}
	for(int i=1;i<=5000;i++){
		for(int j=1;i+j<=5000;j++){
			f[2][i+j]+=f[1][i]*f[1][j];//转移 
		}
	}
	long double ans=0;
	for(int i=1;i<=5000;i++){
		for(int j=i+1;j<=5000;j++){
			ans+=f[2][i]*f[1][j];//处理答案可能性 
		}
	}
	cout<<setprecision(10)<<ans;
	return 0;
}
```

---

## 作者：EnochWenzhou (赞：1)

设三次A取了a_a1,a_a2,a_a3，

B取了a_b1,a_b2,a_b3。

那么需要满足的是:

a_a1>a_b1,

a_a2>a_b2,

a_a1+a_a2+a_a3<a_b1+a_b2+a_b3。

即（a_a1-a_b1）+(a_a2-a_b2)<(a_b3-a_a3)。

容易发现（a_a1-a_b1），(a_a2-a_b2)，(a_b3-a_a3)只有最多n（n-1）/4 种可能可以全部枚举并存下每种a_i-a_j是否可能出现以及出现的种类数有多少种，那么就可以得到结果了。

AC：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5010],cnt;
double f[2][5050],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+1+n);//先排个序，方便操作
	for(int i=1;i<n;i++)for(int j=i+1;j<=n;j++)
		if(a[i]<a[j])f[0][a[j]-a[i]]++,cnt++;
   //cnt表示a_j-a_i的种类数，f[0][k]表示a_i-a_j==k的（i，j）组数
	for(int i=1;i<=5003;i++)f[0][i]/=cnt;//计算每一种的概率
	for(int i=1;i<=5003;i++)for(int j=1;i+j<=5003;j++)f[1][i+j]+=f[0][i]*f[0][j];//f[1][x]表示a_i-a_j+a_k-a_l==x的（i，j，k，l）组数，即为处理不等式左边部分
	for(int i=1;i<5003;i++)for(int j=i+1;j<=5003;j++)ans+=f[1][i]*f[0][j];//处理答案
	printf("%.10lf",ans);
	return 0;
}
```

---

