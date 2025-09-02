# [ABC204D] Cooking

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc204/tasks/abc204_d

高橋君は料理 $ 1 $ から $ N $ の $ N $ 品の料理を作ろうとしています。

料理 $ i $ はオーブンを連続した $ T_i $ 分間使うことで作れます。$ 1 $ つのオーブンを $ 2 $ つ以上の料理のために同時に使うことはできません。

$ 2 $ つのオーブンを使えるとき、$ N $ 品の料理を全て作るまでに最短で何分かかりますか？ なお、オーブンを使う時間以外は無視できるものとします。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ T_i\ \leq\ 10^3 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

例えば $ 2 $ つのオーブンを次のように使うことで、$ 13 $ 分で全ての料理を作ることができます。 - $ 1 $ つ目のオーブン：料理 $ 5,1 $ を順に作る。 - $ 2 $ つ目のオーブン：料理 $ 2,4,3 $ を順に作る。

## 样例 #1

### 输入

```
5
8 3 7 2 5```

### 输出

```
13```

## 样例 #2

### 输入

```
2
1000 1```

### 输出

```
1000```

## 样例 #3

### 输入

```
9
3 14 15 9 26 5 35 89 79```

### 输出

```
138```

# 题解

## 作者：syzxzqy (赞：6)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc204_d)  
#### 题目意思：  
两个烤箱，每个烤箱最多烤一盘菜，求所有菜最少要用多少时间。  
#### 题目分析：
此题为背包水题。  
求两盘菜需多少时间，只要求出其中多的时间，也就是要少的时间极可能多，这就用到了背包。  
$f_i$ 表示在时间 $i$ 内最多能用到多少时间。  
$s=\displaystyle\sum_{i=1}^n a_i$，$s$ 也就是时间之和，$f_{s/2}$ 就是时间少的烤箱所用时间。  
答案也就是 $s-f_{s/2}$。
#### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100001,M=1001;
int n,i,j,s,a[N],f[N];//定义
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i],s+=a[i];//累加求和
	for(i=1;i<=n;i++)//枚举每道菜
		for(j=(s>>1);j>=a[i];j--)//枚举每个时间点
			f[j]=max(f[j-a[i]]+a[i],f[j]);
	cout<<s-f[s>>1];//位运算
}
```


---

## 作者：ryf_loser (赞：1)

此题正解：背包动态规划。

此题一看就要用动态规划，单用什么样的动态规划才能解决此题呢？

其实只要深入思考一下，我们就会发现：此题可以把时间总和求出来，并折半，就可以达到背包动态规划的效果。

深入一点，我们计算出 $\sum_{i=1}^{n}T$，的值后，可以把 $\frac{\sum_{i=1}^{n}T}{2}$，作为一个背包容量的最大值使用。想象一下，有一个烤箱所花的时间仅可能 $\leq\frac{\sum_{i=1}^{n}T}{2}$。而我们要让两个烤箱的工作截止时间相近，这样才可能得到最优解，这样我们需要这个 $\leq\frac{\sum_{i=1}^{n}T}{2}$ 的烤箱工作时间尽可能多，这样就能得到最优解。

01 背包的代码大家应该很清楚了，我就放一个通项公式了：

$dp_{j}\leftarrow\max(dp_{j},dp_{j-t_{i}}+t_{i})$

而此时我们就可以写代码了。

AC CODE

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,dp[100001],t[101],tot,tmp,ans;
int main(){
	scanf ("%d",&n);
	for (int i=1;i<=n;i++){
		scanf ("%d",&t[i]);
		tot+=t[i];
	}
	for (int i=1;i<=n;i++)
		for (int j=(tot>>1);j>=t[i];j--)
			dp[j]=max(dp[j],dp[j-t[i]]+t[i]);
	printf ("%d",tot-dp[tot>>1]);
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

### 题目大意

两个人要洗 $N$ 个碗，其中任意一个人洗第 $i$ 个碗需要 $T_i$ 分钟。一个人不能同时洗多个碗。

两个人一起洗碗，洗完所有碗至少需要多少分钟。


### 思路

其问题等价于：给定序列 $T$，将其分成两个子序列 $A$ 和 $B$，求最小的 $A,B$ 元素和。

将 $\sum T$ 分成两半，其中一半为 $\lfloor\frac{\sum T}2\rfloor$。

我们应使得 $\sum A\le\lfloor\frac{\sum T}2\rfloor$，这样答案就为 $\sum T-\sum A$。


### 代码

```cpp
#include<cstdio>
using namespace std;
int dp[100005],a[105];
int main()
{
	int n,sum=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",a+i);
		sum+=a[i];//求和。 
	}
	int t=sum;
	sum/=2;
	for(int i=0;i<n;i++)
		for(int j=sum;j>=a[i];j--)
		{
			if(dp[j-a[i]]+a[i]>dp[j]) dp[j]=dp[j-a[i]]+a[i];//经典背包问题。 
		}
	printf("%d\n",t-dp[sum]);
	return 0;
}

```


---

## 作者：loser_seele (赞：0)

注意到数据范围很小，考虑枚举答案，判断答案是否合法。

问题转化为是否能选出一个子集，满足子集的和为 $ x $。这个可以用一个类似 01 背包的 dp 来实现，设 $ dp_{i,j} $ 表示前 $ i $ 个物品能表示出和为 $ j $，则显然有转移 $ dp_{i+1,j+T_i}=dp_{i,j},dp_{i+1,j}=dp_{i,j} $，分别对应选与不选第 $ i $ 个物品的情况。

状态数为 $ \mathcal{O}(n\sum T_i) $，所以总时间复杂度 $ \mathcal{O}(n\sum T_i) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
bitset<100010>dp[110];
int t[100010];
int main()
{
  int n; 
  cin>>n;
  for(int i=0;i<n;i++) 
  cin>>t[i];
  int sum=0; 
  for(int i=0;i<n;i++) 
  sum+=t[i];
  dp[0][0]=1;
  for(int i=0;i<n;i++)
    for(int j=0;j<sum+1;j++)
      if(dp[i][j])
        dp[i+1][j+t[i]]=1,dp[i+1][j]=1;
  int ans=sum;
  for(int i=0;i<=sum;i++)
    if(dp[n][i])
      ans=min(ans,max(i,sum-i));
  cout<<ans;
}
```


---

