# [ARC043B] 難易度

## 题目描述

cdcq想出一场模拟赛  
作为暴力选手，cdcq出的题自然是要有明显的梯度，来让更多的选手拿到自己的分数  
现在cdcq的idea库里有$ N(4\leq N\leq 10^5) $个idea，并且他给每个idea评估了一个难度值  
他要从中选择4个idea来出题，并且这些idea需要满足如下三个条件：  
第二道题的难度值必须大于等于第一道题的两倍  
第三道题的难度值必须大于等于第二道题的两倍  
第四道题的难度值必须大于等于第三道题的两倍  
现在cdcq想考考你他总共能组出多少套题  
因为答案太大，所以你需要对$ 1,000,000,007(10^9+7) $取模

## 说明/提示

部分点  
有50分满足$ 4\leq N \leq 3,000 $  
剩下的50分满足$ N(4\leq N\leq 10^5) $，共计100分  
Sample Explanation 1  
$ 1,2,3,5 $和$ 1,2,4,5 $都是可行的题目组合  
Sample Explanation 2  
没有任何一种组合满足题目条件  

感谢 @cdcq 提供的翻译

## 样例 #1

### 输入

```
5
1
2
4
5
10```

### 输出

```
2```

## 样例 #2

### 输入

```
10
11
12
13
14
15
16
17
18
19
20```

### 输出

```
0```

## 样例 #3

### 输入

```
20
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20```

### 输出

```
94```

# 题解

## 作者：什么叫中二呀 (赞：5)

第一次看题面的时候，想着：大概DFS能过……

看完数据范围，果断决定DP。

**我对于判断是否用DP的方法是:~~如果每一个数都不大，但数的总数很大，那基本上就用DP了……~~**

看这题，嗯，N<=$10^5$,$a_i$<$10^5$,就准备推方程。

我们定义DP数组(如果觉得好理解可以用二维)，$DP_j$表示难度为j的题目作为第i(1<=i<=4)道题有几种可能。

最终答案很好表示，就是$∑DP_i$。

题目说:难度最少二倍，所以$DP_i$=$∑DP_(i/2)$

时间复杂度:O(4*$max($a_i$)^2$)

最坏情况是4*$(10^5)^2$=40000000000~~(太大了吧)~~

所以还要优化。

对于$∑DP_(i/2)$，我们可以前缀和O(1)算出。

但是注意一定要乘$a_i$,~~我被坑了两次~~,算可能性要有几个算几个

~~**至于耗费大量空间我们不管，反正够用**~~

主题代码如下
***
```cpp
for(int j=1;j<=m;j++)
{	//这里有个奇怪的变量名
	//  	↓	
    qzh[j]=qzh[j-1]+dp[j];//算前缀和
	dp[j]=a[j]*qzh[j/2];//计算DP
}
```
***
对于输入呢，我们运用了桶排的思想。

**某大佬提醒：NOIP千万别用桶排**

下面是 输入+桶排 代码:
***
```cpp
scanf("%d",&N);
while(N--)
{
	scanf("%d",&temp);
	dp[temp]++;a[temp]++;//桶排
	m=max(temp,m);//记最大数，省点时间
}
```
***
最后就是计算$∑DP_i$和输出啦

CODE:
***
```cpp
for(int i=0;i<=m;i++)
	sum=(sum+dp[i])%mod;
printf("%d\n",sum%mod);
```
***
整合代码：
***
```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum,dp[100005],a[100005],qzh[100005];
int N,temp,m,mod=1000000007;
int main()
{
	scanf("%d",&N);
	while(N--)
	{
		scanf("%d",&temp);
		dp[temp]++;a[temp]++;
		m=max(temp,m);
	}
	for(int i=0;i<3;i++)
		for(int j=1;j<=m;j++)
		{
			qzh[j]=qzh[j-1]+dp[j];
			dp[j]=a[j]*qzh[j/2];
		}
	for(int i=0;i<=m;i++)
		sum=(sum+dp[i])%mod;
	printf("%d\n",sum%mod);
	return 0;
}
```
***

## 注：代码中有重要的一点，没有及时取模

这一题为什么不需要呢？

最大值约为$max(a_i)^3/6$,且$log$ $max(a_i)^3/6$大约是46点几的样子，不爆$long long$,就不需要及时取模了。

但为什么结尾要取模呢？

~~因为题目里说了……~~

---

## 作者：StarPatrick (赞：3)

这题明显可以 DFS 加上记忆化就可以了。

定义 $dfs(i, u)$ 表示上一次选的是第 $i$ 道题目，已经确定了第 $u$ 道题。接下来就可以开始爆搜。

循环从 $i+1$ 到 $n$，如果此题目 $p$ 的难度大于上一次选择的题目，即 $a[i]$，就搜索 $dfs(p,u+1)$ 就行了。

边界：$u=4$ 时答案加一，加上记忆化就可以了。

温馨提醒：要开 long long int

核心代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std;
#define int long long
int n, a[100005], dp[100005][5];
const int mod = 1e9+7;
int dfs(int i, int u)
{
	if (dp[i][u]!=-1)
	{
		return dp[i][u];
	}
	if (u==4)
	{
		return dp[i][u]=1;
	}
	int ans = 0;
	for (int p=i+1;p<=n;p++)
	{
		if (a[p]>=a[i]*2)
		{
			ans+=dfs(p, u+1);
			ans%=mod;
		}
	}
	return dp[i][u]=ans;
}
signed main()
{
	memset(dp, -1, sizeof(dp));
	cin>>n;
	for (int p=1;p<=n;p++)
	{
		cin>>a[p];
	}
	cout<<dfs(0, 0);
	return 0;
}
```


---

## 作者：Rhapsodia (赞：0)

来写写 Python 题解。

看到数据范围， $4 \le N \le 10^5$ ，就用 dp 。

我们统计有多少个一位，二位，三位，四位，再加起来输出答案。

设 $X_i$ 表示难度为 $i$ 的数能作为几个二位。

我们设 $c_i$ 为 $D_i$ 的桶，可以推出 $dp_i=\sum\limits_{j=1}^{i/2} dp_j \times cnt_i$ ，前缀和可求。

代码如下。


```python
N = int(input())
M = 100000
X = [[0] * (M + 1) for i in range(4)]
D = []
for _ in range(N):
    d = int(input())
    D.append(d)
    X[0][d] += 1
    
for k in range(4):
    for i in range(1, M+1):
        X[k][i] += X[k][i-1]
    if k == 3:
        break  
    for d in D:
        X[k+1][d] += X[k][d//2]
print(X[3][-1]%(10**9+7)) #这里要取模
```

---

## 作者：Deuteron (赞：0)

### 写在前面：我的思路非常奇怪，希望大佬不要D我（

## 题意简述：
给定一个长度为 $n$ 的数组 $a_i$ 求出四个数 $f_1,f_2,f_3,f_4$ 满足 $ 2*f_1 \le f_2 ,2*f_2\le f_3 ,2*f_3\le f_4$

## solution

我们先将 $a$ 增序排序，用处之后会提到

我们设 $dp_{i,j}$ 表示把第 $i$ 题出作模拟赛的第 $j$ 题的方案数，

则在这道题之前且难度不超过这道题的难度的一半的题均可以出作 $j-1$ 题

由于难度是单调递增的，所以我们可以二分求出这道题。

我们可以得到状态转移柿子如下：

$dp_{i,j}=\sum_{k=1}^{f_i} dp_{k,j-1}$

其中 $f_i$ 表示第一道满足题意的题。

可以发现这个算法的时间复杂度是 $O(n^2)$ 的，显然无法通过此题。

我们观察到所需要的之前的状态是连续的一段，是从 $1$ 到 $f_i$ 的和，

这时我们可以使用前缀和，

$sum_{i,j}=\sum_{k=1}^{i} dp_{i,j}$

这样我们的状态转移方程就会变为

$dp_{i,j}=sum_{f[i],j-1}$

这样就可以将时间复杂度压缩至 $O(n\log{n})$ 可以通过本题。$\log$ 来源于二分。

初始化：

$dp_{i,1}=1$

$sum_{i,1}=\sum_{k=1}^{i} dp_{k,1}=i$

最后，别忘了开```long long```以及取模！

代码菌：（写的很丑

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e6+5;
const int mod=1e9+7;
int a[N];
int to[N];
long long dp[N][5];
long long s[N][5];
int n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];//输入 
	}
	sort(a+1,a+n+1);//排序 
	for(int i=2;i<=n;i++){
		int l=1,r=i;
		while(l<r){
			int mid=(l+r)/2;
			if(a[mid]*2>a[i]){
				r=mid;
			}
			else l=mid+1;
		}
		if(a[l]*2>a[i]) l--;
		to[i]=l;//二分求出f 
	}
	for(int i=1;i<=n;i++){//初始化 
		dp[i][1]=1;
		s[i][1]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=4;j++){
			dp[i][j]=s[to[i]][j-1]%mod;//状态转移方程 
			s[i][j]=s[i-1][j]+dp[i][j];//求前缀和 
			s[i][j]%=mod;//别忘了取模
		}
	}
	cout<<s[n][4]%mod<<endl;//输出 
	return 0;//好习惯 
}
```
希望管理员大大让我通过！

---

## 作者：Jiyuu_no_Tsubasa (赞：0)

这是一道典型的 DP 题，

状态的设计与转移也比较简单。

我们可以用 $f_{i,j}$ 表示大小为 $j$ 的数 出现在 $i$ 的位置上的次数。

转移方程即为 $f_{i,j} \gets  b_{j}\times\sum \limits_{k=1}^{i\div2}f_{i-1,k}$。（$b_{j}$ 表示  $j$ 出现的次数）

它的意义就是，在 $i$ 的位置上 $j$ 能出现多少次取决于 $b_j$ 与能与它匹配的数，

根据乘法原理，两者相乘就能获得答案。

最终的答案就是 $\sum \limits_{i=1}^nf_{4,i}$，也就是每个数在最后出现的次数之和。

那么根据刚才的思想，我们可以用桶来记录输入。

但我们可以发现，每次转移所耗费的时间非常之大，

因此时间复杂度就变成了 $O(4\times \max(a_i)^2)$，也就是 $O(n^2)$ 级别，

在 $n\le 10^5$ 的数据下显然会被卡掉，因此我们需要优化。

我们可以想到用前缀和对区间进行 $O(1)$ 查询，因此我们就完成了 $AC$ 所需的优化。

但我们还可以发现，二维数组 $f$ 实际上使用了许多空间，

但它每次只使用一个维度的数据，因此我们可以将其降至一维。

所以状态转移方程就变成了 $f_{j} \gets  b_{j}\times s_{j \div 2}$（$s_{j}$ 表示 $\sum \limits_{k=1}^{j}f_{k}$）。

这样我们就完成了程序，代码如下。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int MOD=1e9+7;
long long s[N],f[N],b[N];
int main(){
    int n; cin>>n;
    int m=0,x;
    while(n--){
        cin>>x;
        m=max(m,x);
        b[x]++,f[x]++;
    }
    for(int i=1;i<4;i++)//因为第i次求出i+1位置上的答案
    			//因此只需要循环三次
        for(int j=1;j<=m;j++){
            s[j]=(s[j-1]+f[j])%MOD;//注意顺序，先记录前缀和
            f[j]=(b[j]*s[j/2])%MOD;//再转移状态
        }
    long long ans=0;
    for(int i=0;i<=m;i++)
        ans=(ans+f[i])%MOD;//求和
    cout<<ans;
    return 0;
}

```

---

## 作者：yyy爱编程 (赞：0)

一看就知道用DP吧。

当然还有前缀和啦

用DP第一个先推那个什么什么方程，推好了题目也基本上就解出来了。

至于公式怎么推，可以从小数据入手，然后逐渐到大数据，再找规律吧。

一共要选四道题，那么我们设$dp_{i}$是把难度为$i$的题目放在$1$~$4$题有几种可能。

又看见两倍，那么再$÷2$就好了。

最后还要求和，方案数全部加起来嘛，就用个$\sum$好了。

所以呢，公式基本上就推出来了:

$dp_{i}$=$\sum dp_{\frac{2}{i}}$

代码就是读入，排个序，计算$\sum dp_{i}$，再输出就OK了。





---

