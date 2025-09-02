# New Year's Problem

## 题目描述

Vlad 有 $n$ 个朋友，每个朋友需要且仅需要 $1$ 个礼物。有 $m$ 家礼物商店，如果在第 $i$ 个商店中为朋友 $j$ 买礼物，朋友 $j$ 将获得 $p_{ij}$ 的快乐值。

由于时间紧迫， Vlad 最多只会在 $n-1$ 家不同的商店中买礼物。请你使每位朋友能获得的快乐值中的最小值最大。

## 样例 #1

### 输入

```
5

2 2
1 2
3 4

4 3
1 3 1
3 1 1
1 2 2
1 1 3

2 3
5 3 4
2 5 1

4 2
7 9
8 1
9 6
10 8

2 4
6 5 2 1
7 9 7 2```

### 输出

```
3
2
4
8
2```

# 题解

## 作者：Erotate (赞：11)

题目中“请你使每位朋友能获得的快乐值中的最小值最大。”这句话已经告诉我们要用二分答案来做了。

因为只在 $n-1$ 个商店买礼物，可以发现，有两种情况是无解的：

1. 一个人在哪都买不到满足他的礼物。
2. 没有一个商店可以满足两个或以上的人。证明：根据容斥原理，$n$ 个人在 $n-1$ 个商店买礼物，至少有两个人在同一家商店买礼物。

所以我们只需要分两个循环来判断是否存在上面两个情况即可。

---
有一个空间优化的小技巧，我们可吧把每个店对于每一个小孩的信息压缩为一维数组，即：
```cpp
a[(i-1)*n+j]
```
来表示第 $i$ 个商店对于第 $j$ 个小朋友的快乐值。

代码：
```cpp
#include<bits/stdc++.h>
#define lhr long long
using namespace std;
lhr t,n,m,a[200005],b,l=0,r=1000000000;
bool check(int x){
    for(int i=1;i<=n;++i){
        int f=1;
        for(int j=1;j<=m;++j)
            if(a[(j-1)*n+i]>=x) f=0;
        if(f) return 0;
    }
    for(int i=1;i<=m;++i){
        int cnt=0;
        for(int j=1;j<=n;++j)
            if(a[(i-1)*n+j]>=x) cnt++;
        if(cnt>=2) return 2;
    }
    return 0;
}
int main(){
    cin>>t;
    while(t--){
        cin>>m>>n;
        for(int i=1;i<=m;++i)
            for(int j=1;j<=n;++j) cin>>a[(i-1)*n+j];
        l=0,r=1000000000;
        while(l<r){
            int mid=(l+r)/2;
            if(check(mid+1)) l=mid+1;
            else r=mid;
        }
        cout<<l<<endl;
    }
    return 0;
}
```


---

## 作者：lsroi (赞：4)

**前言：** 这里提供一种非二分的解法。

**思路：** 注意到最多可以选择 $n-1$ 家商店，这意味着至少有两个朋友的礼物是在同一家店购买的。

所以可以枚举商店，以及是要为哪两个朋友在该店购买礼物。现在还有 $n-2$ 家商店可选择，那么剩下的人选使他们快乐值最大的商店即可，这个可以花费 $O(m*n)$ 预处理。

时间复杂度 $O(m * n ^ 2)$ ，看似过不了，其实不然，分类讨论： 

①若 $n - 1 >= m$ ，意味着每家商店都可以买礼物，就直接取max就行了，此时时间复杂度 $O(m * n)$ 。

②若 $n - 1 < m$ ，因为 $m * n <= 100000$ ，故此时n最大只有316， $O(m * n ^ 2)$ 的复杂度是可以接受的。


**代码如下：**


```cpp
//by_lsroi
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1e5+1;
const int INF=1e9+1;
vector<int >p[N];
int Max[N];
int main(){
	ios::sync_with_stdio(false);
	int T,m,n,x;
	cin>>T;
	while(T--){
    //初始化
		cin>>m>>n;  int ans=0,Min=INF;
		for(int i=0;i<m;i++)p[i].clear();
		for(int i=0;i<n;i++)Max[i]=0;
		
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				cin>>x,Max[j]=max(Max[j],x),p[i].push_back(x);
		for(int i=0;i<n;i++)Min=min(Min,Max[i]);
		
		if(n-1>=m)ans=Min;
		else{
			for(int k=0;k<m;k++)
				for(int i=0;i<n;i++)
					for(int j=i+1;j<n;j++)
						ans=max(ans,min(Min,min(p[k][i],p[k][j])));
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Zhou_yu (赞：3)

## 题目描述：
### [CF1619D 题目传送门](https://www.luogu.com.cn/problem/CF1619D)
从题面中的“最小快乐值的最大值”明显看出使用二分，此题坑点不多，[数据很强](https://www.luogu.com.cn/record/166937658)。
## 所用算法：
1. 二分
2. 二维数组转一维数组
3. 抽屉原理
## 算法思路：
### Q1：如何解决题目 $n,m$ 的范围不清所导致的存储问题？
对于 $n,m$ 单个变量不定的情况，为了安全容易出现爆空间($10^5 \times 10^5 > 6 \times 10^7$）所以尝试使用**二维数组转一维数组**的方法，即将 $a[i][j]$ 转化为 $b[(i-1)*m+j]$。

这样数组最多只需要开到 $10^5$ 即可，大大节省浪费的空间。

### Q2：不会写二分怎么办？
啊这……模板奉上：
```cpp
bool check(int mid)
{
	//check area
}
while(l<=r)
{
	int mid=(l+r)>>1;
	if(check(mid))l=mid+1;
	else r=mid-1;
}
cout<<l-1;
```

### Q3：如何解决判断当前 $mid$ 值是否可行？
1. 由题面可得：每个朋友都需要找到有**至少一个商店**能满足当前的 $mid$ 值，否则当前 $mid$ 值不成立。

2. 再次观察题目特点发现，在 $m$ 个商店中只能选择 $n-1$ 个进行购买，但我们有 $n$ 个朋友，所以根据抽屉原理，**必然存在一个商店会有至少两个人的礼物在此购买。**（百度：[抽屉原理](https://baike.baidu.com/item/%E6%8A%BD%E5%B1%89%E5%8E%9F%E7%90%86/233776?fr=ge_ala)）

3. 基于抽屉原理发现：必须有一个商店满足**至少两个朋友**对于礼物的要求，否则当前 $mid$ 值不成立。

小结 Q3：从以上分析发现，实现当前 $mid$ 值**是否不成立**似乎比正向实现要简单。

### Q4：你这复杂度~~保熟~~能过吗？
可知判断当前 $mid$ 值是否可行需要 $O(n \times m)$，二分复杂度 $O(\log_{2}{10^9})$，总复杂度趋向于 $O(n^2 \times \log_{2}{n})$，对于此题范围足够了。

**最后避坑注意：千万不要把两种判断当前 $mid$ 值不成立的情况放在一起，不然就会 [TLE](https://www.luogu.com.cn/record/166937658)！**（所谓“数据很强”的原因）

特附：[TLE代码](https://www.luogu.com.cn/paste/hwkq73oy)

理论存在，实践开始。
## AC 代码
[AC 记录](https://www.luogu.com.cn/record/166942005)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int p[200005]; 
bool check(int mid)
{
	for(int i=1;i<=n;i++)
	{
		bool f=1;
		for(int j=1;j<=m;j++)
		if(p[(j-1)*n+i]>=mid){f=0;break;}
		if(f)return 0;
	}//每个朋友都需要找到有至少一个商店能满足当前的 mid值
	int cnt[100005]={0}; 
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(p[(j-1)*n+i]>=mid)
	{
		cnt[j]++;
		if(cnt[j]>1)return 1;
	}//必然存在一个商店会有至少两个人的礼物在此购买
	return 0;//不成立
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>m>>n;
		for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)cin>>p[(i-1)*n+j];//二维数组转一维数组
		int l=0,r=pow(10,9)+1;
		while(l<=r)//二分板子
		{
			int mid=(l+r)>>1;
			if(check(mid))l=mid+1;
			else r=mid-1;
		}
		cout<<l-1<<'\n';
	}
	return 0;
}
```
## 总结
练手好题，不肝不伤脑，值得一做。

---

## 作者：Coros_Trusds (赞：3)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15790360.html)

这是二分答案的题解，但是我看到一种更有趣的方法 [戳这里](https://isshiki_hugh.gitee.io/blog/2021/12/26/cf752/#D-New-Year%E2%80%99s-Problem)

# 题目大意

$\rm Vlad$ 有 $n$ 个朋友，每个朋友需要且仅需要 $1$ 个礼物。有 $m$ 家礼物商店，如果在第 $i$ 个商店中为朋友 $j$ 买礼物，朋友 $j$ 将获得 $p_{i,j}$ 的快乐值。

由于时间紧迫，$\rm Vlad$ 最多只会在 $n-1$ 家不同的商店中买礼物。请你使每位朋友能获得的快乐值中的最小值最大。

# 题目分析

看到类似求“最大值最小”“最小值最大”的题马上想到二分答案。

所以我们二分快乐值。

对于每一个快乐值，我们怎么判断它不可行呢？

两种情况：有一个人没有礼物和所有店都只能满足一个人（因为是选择 $n-1$ 家店，所以可行必定至少有一家店满足的人数大于等于 $2$）。

---

一个小 $\rm trick$:

> 遇到题目中这种 $n\times m$ 的和不超过 $10^5$ 的题目，开二维数组的话，$n,m$ 的具体范围未知，可能会导致 $\verb!MLE!$。
>
> 解决办法有两个：
>
> + 用 $\mathbf{vector}$；
>
> + 压缩成一维数组。
> 
> 也就是：
>
> ```cpp
> a[(i-1)*m+j]=a[i][j]
> ```
>
> 可以有效减少内存。

# 代码

```cpp
//2022/1/11

const int ma=1e5+5;

int a[ma];

int T,n,m;

inline bool check(int now)
{
	for(register int i=1;i<=m;i++)
	{
		bool mark=true;
		
		for(register int j=1;j<=n;j++)
		{
			if(a[(j-1)*m+i]>=now)
			{
				mark=false;
			}
		}
		
		if(mark==true)//一个人的礼物在哪家店都买不到 
		{
			return false;
		}
	}
	
	for(register int i=1;i<=n;i++)
	{
		int num(0);
		
		for(register int j=1;j<=m;j++)
		{
			if(a[(i-1)*m+j]>=now)
			{
				num++;
			}
		}
		
		if(num>=2)//有一家店至少能同时买到至少两个人的礼物
		{
			return true;
		}
	}
	
	return false;
}

inline int binary()
{
	int l=1,r=1e9;
	
	//枚举快乐值 
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		
		if(check(mid)==true)
		{
			l=mid;
		}
		
		else
		{
			r=mid-1;
		}
	}
	
	return l;
}

inline void solve()
{
	mst(a,0);
	
	n=read(),m=read();
	
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=m;j++)
		{
			a[(i-1)*m+j]=read();
		}
	}
	
	printf("%d\n",binary()); 
}

int main(void)
{
	T=read();
	
	while(T--)
	{
		solve();
	}
	
	return 0;
}
```

---

## 作者：lefthand166 (赞：2)

# CF1619D New Year's Problem  

## 解题说明
这是一道非常简单的贪心水题。   

时间复杂度为 $O(m \times n)$，空间复杂度 $O(n)$。  

显而易见，首先求出每个人的快乐值先取得可取到的最大值，存为数组 $f[i]$。但是，如果每个人都去了不同的商店，会导致去的商店总数等于 $n$ ，不符合题意，因此至少有两个人得去一个商店。  

我们可以获得每个商店能提供的快乐值的次大值 $m2$ ，然后获得这些次大值中的最大值，记为 $ma$ 。所以，我们可以在这个商店购买其中两个朋友的商品，此时我们就会满足总数 $ \le n-1$ 
答案就是 $\min(\min(f[i]),ma)$。 

## 为什么这样做是可行的呢？
因为我们想把两个朋友移到一个商店，那么我们就尽量把这两人移得尽量大，那很显然，这两个人中获得较小快乐值的人会对结果产生影响，所以我们记录了 $ma$ 是次大值中的最大值。  

移过来之后我们需要比较一下 $ma$ 和  $\min(f[i])$ 取其中较小的，就是答案。  

这很	 $\textit{\textbf{贪心}}$ 。  
## tips
+ 为了避免开过大的数组我们可以边输入边处理，比如处理每个商店的次大值和朋友的最大快乐值。
+ 求次大值的方法也很简单，m2是次大值，如下：
```cpp
if(k>m2)swap(m2,k);
if(m2>m1)swap(m1,m2);
```
## 具体细节看 AC 代码 (202ms,100 KB )：
```cpp
#include<iostream>
using namespace std;
const int maxn=1e5+10;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int m,n,ma=0,f[maxn]={0};
		scanf("%d%d",&m,&n);
		for(int i=1;i<=m;i++)
		{
			int m1=0,m2=0; 
			for(int j=1;j<=n;j++)
			{
				int k;
				scanf("%d",&k);
				f[j]=max(f[j],k);
				if(k>m2)swap(m2,k);
				if(m2>m1)swap(m1,m2);
			}
			ma=max(ma,m2);
		}
		for(int i=1;i<=n;i++)ma=min(f[i],ma);
		printf("%d\n",ma);
	}
	return 0;
}
```

---

## 作者：cff_0102 (赞：2)

设 $ans$ 是我们要求的答案（最小值的最大值），$\operatorname{check}(x)=\left\{
\begin{aligned}
&1\quad ans\ge x \\
&0\quad ans < x 
\end{aligned}
\right.$，则可以通过 $\operatorname{check}(x)$ 来二分求出最终最小快乐值的最大值。

$\operatorname{check}$ 函数可以这样实现：

1. 要实现 $ans\ge x$，必须有一种方案，它的快乐值的最小值大于等于 $x$。
2. 那么，就有一种方案，使得没有一个人的快乐值小于 $x$。
3. 考虑建立一个 $01$ 矩阵，原来矩阵中小于 $x$ 的就变成 $0$。要是 $\operatorname{check}(x)=1$ 的话，这些是 $0$ 的位置肯定不能选。那么，判断 $\operatorname{check}(x)$ 的问题就转化为：在一个 $m$ 行 $n$ 列的 $01$ 矩阵中，选择 $n$ 个数，满足每一列都有一个 $1$，且至少有一行有两个 $1$。
4. 那么，$\operatorname{check}(x)=1$，当且仅当这个 $01$ 矩阵每一列都有一个 $1$，且有一行有 $2$ 个 $1$。
5. 转化回原数组，就是 $p$ 的每一列至少有一个数大于等于 $x$，且至少有一行有至少两个数大于等于 $x$。

这样就能在 $O(nm)$ 的时间复杂度完成 $\operatorname{check}(x)$。

然后再套一个二分即可。


------------

但是，在代码实现时，还会碰到一个问题：$n,m$ 的值不确定，只知道它们的积肯定不会超过 $10^5$，应该存储数组？实际上，把一个二维数组的每一行拼起来能够变成一个一维数组。而我们知道这个一维数组的大小肯定不超过 $10^5$。这样就能防止 MLE 了。

定义一个函数 $\operatorname{cal}(i,j)$，用于计算 $p_{ij}$ 对应在这个一维数组上的位置。将 $m,n$ 设为全局变量，$\operatorname{cal}(i,j)$ 的返回值就是 $(i-1)\times n+j$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[114514];//a 数组用来存储每一次询问中的二维数组 
int cal(int x,int y){return (x-1)*n+y;}
bool check(int x){
	for(int j=1;j<=n;j++){//这里先遍历每列 
		bool f=0;
		for(int i=1;i<=m;i++)if(a[cal(i,j)]>=x)f=1;//这一列有大于等于 x 的数 
		if(f==0)return 0;//如果这一列没有，则 check(x) = 0 
	}
	for(int i=1;i<=m;i++){
		int s=0;//s 记录这一行大于等于 x 的数的个数 
		for(int j=1;j<=n;j++)if(a[cal(i,j)]>=x)s++;
		if(s>=2)return 1;//如果这一行符合要求（大于等于 x 的数的个数大于等于 2），则 check(x) = 1 
	}
	return 0;//没有一行符合要求，check(x) = 0 
}
int main(){
	int t;cin>>t;
	while(t--){
		cin>>m>>n;
		int mx=-1;//用来记录所有数的最大值，待会用作二分右端点 
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				cin>>a[cal(i,j)];
				mx=max(mx,a[cal(i,j)]);
			}
		}
		int l=1,r=mx;
		while(l<r){//二分 
			int mid=(l+r)/2;
			if(check(mid))l=mid+1;
			else r=mid;
		}
		if(check(l))cout<<l<<endl;
		else cout<<l-1<<endl;//二分到的答案是恰好满足 check(x) = 0 的最小值，而不是满足 check(x) = 1 的最大值，所以再减 1 
	}
	return 0;
}
```

---

## 作者：WydnksqhbD (赞：1)

# [CF1619 New Year's Problem](https://www.luogu.com.cn/problem/CF1619D) 题解
## 思路
由于本题的答案具有单调性，所以可以二分答案，使用 $check$ 函数检查每一个答案。

首先写出二分代码：

```cpp
while(left<=right)
		{
			long long mid=(left+right)>>1;
			if(check(mid))
			{
				ans=mid;
				left=mid+1;
			}
			else
			{
				right=mid-1;
			}
		}
```

那么我们现在就需要写 $check$ 函数。

如何 $check$ 呢？

以下两种情况绝对排除：

+ 有一个人买不到礼物
+ 每一家商店都只能容下 $1$ 个人。（根据容斥原理，$n$ 个人去 $n-1$ 家商店买东西，必有一家商店有 $2$ 人）

其余的就是对的答案了。$check$ 函数代码如下：

```cpp
bool check(long long x)
{
	for(int i=1;i<=n;i++)
	{
		int flag=1;
		for(int j=1;j<=m;j++)
		{
			if(a[(j-1)*n+i]>=x)
			{
				flag=0;
			}
		}
		if(flag)
		{
			return 0;
		}
	}
	for(int i=1;i<=m;i++)
	{
		int cnt=0;
		for(int j=1;j<=n;j++)
		{
			if(a[(i-1)*n+j]>=x)
			{
				cnt++;
			}
		}
		if(cnt>=2)
		{
			return 1;
		}
	}
	return 0;
}
```

最终代码为：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
ll t,n,m,a[N];
bool check(long long x)
{
	for(int i=1;i<=n;i++)
	{
		int flag=1;
		for(int j=1;j<=m;j++)
		{
			if(a[(j-1)*n+i]>=x)
			{
				flag=0;
			}
		}
		if(flag)
		{
			return 0;
		}
	}
	for(int i=1;i<=m;i++)
	{
		int cnt=0;
		for(int j=1;j<=n;j++)
		{
			if(a[(i-1)*n+j]>=x)
			{
				cnt++;
			}
		}
		if(cnt>=2)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld %lld",&m,&n);
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
			{
				scanf("%lld",&a[(i-1)*n+j]);
			}
		}
		ll left=1,right=1e9,ans=0;
		while(left<=right)
		{
			long long mid=(left+right)>>1;
			if(check(mid))
			{
				ans=mid;
				left=mid+1;
			}
			else
			{
				right=mid-1;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

新手备注：`>>1` 的意思是在**二进制**下将数字右移 $1$ 位，即 $\div 2$，也可以写作 `/2`。

---

## 作者：Y_QWQ_Y (赞：0)

这道题我们可以用贪心来做。

### 解题思路
我们先用一个数组记录每个朋友能够取到的最大快乐值。显然，当所有人的最大快乐值刚好都不在同一个商店时，我们可以取一个最大的次大值，来使整体答案最大。

对于其他情况，每个朋友都可以选择使他们开心值最大的商店，至少有一个开心值最大重复在一个商店的情况可以使得最多会去 $n-1$ 家商店，这种情况是满足题意的，所以可以取到最优的结果。

那么，我们继续考虑所有快乐值最大的商店没有重复的情况。显然，因为这题要求最大的最小值，只要取除去所有最大值外的最大值，也就是最大的次大值，就一定会使答案最优。但是，有一点需要注意，最大的次大值只是相对的，也有可能某个商店的次大值比某个商店的最大值更大。所以，求出的最大的次大值不一定是答案，还需要跟所有最大值比较求出最小值才是答案。详细的，答案为 $\min{\min}{_{i=1}^n{f_i},secondmax}$。

我的求次大值思路借鉴了 [这篇文章](https://www.luogu.com/article/9qprsxp9)。显然我们只需要维护最大值和次大值，那么不妨就只记录这两个值，以及当前商店的快乐值，对于 $a_i>secondmax$ 时，直接用 $a_i$ 替换次大值。当 $secondmax>firstmax$ 时，交换最大值和次大值。

### 代码部分

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, m, n, Max, f[100005];
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> t;
	while (t --)
	{
		cin >> m >> n;
		Max = 0;
		memset (f, 0, sizeof (f));
		for (int i = 1; i <= m; ++ i)
		{
			int Fi_Max = 0, Se_Max = 0;
			for (int j = 1; j <= n; ++ j)
			{
				int a;
				cin >> a;
				f[j] = max (f[j], a);
				if (k > Se_Max)Se_Max = a;
				if (Se_Max > Fi_Max)swap (Se_Max, Fi_Max);
			}
			Max = max (Max, Se_Max);
		}
		for (int i = 1; i <= n; ++ i)Max = min (f[i], Max);
		cout << Max << '\n';
	}
	return 0;
}
```

---

## 作者：yonghu_848119 (赞：0)

### 思路：
"最小值最大"，一眼二分，二分答案最大的最小快乐值即可。

如果正向思考怎样可以是比较麻烦的，不如逆向思考哪几种情况不行。很轻松可知，有两种情况是不能取此值的。

1）任何一个商店都不能满足要求。（即当前二分的这个值）

2）根据鸽巢原理，可知 $n$ 个人到 $n-1$ 个店里买东西，至少会有两个人到同一家店中买东西。所以当任意一家店都没有可以满足两个人的快乐值都大于当前值，是不行的。

$n\times m$ 的和不超过 $10\times 10^5$，却并没有说 $n$ 与 $m$ 的值，所以考虑用一维数组代替二维数组。

附上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
int a[N], c[N];
int t, n, m;
bool check (int x) {
	for (int i = 1; i <= m; i++) {
		bool f = 0;
		for (int j = 1; j <= n; j++) {
			if (a[ (j - 1) * m + i] >= x) {
				f = 1; 
			}
		}
		if (!f) return 0; //如果当前的这个人，任意商店均不能满足他，当前这个值不能满足
	}
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		for (int j = 1; j <= m; j++)
			if (a[ (i - 1) * m + j] >= x) cnt++;
		if (cnt >= 2) return 1; //假如有一个商店可以满足两个人在这里买，一定可以
	}
	return 0;
}
int main() {
	scanf ("%d", &t);
	while (t--) {
		scanf ("%d%d", &n, &m);
		int ma = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf ("%d", &a[ (i - 1) * m + j]);//一维数组代替二维
		int l = 0, r = 1e9 + 1;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (check (mid) ) l = mid;
			else r = mid;
		}
		printf ("%d\n", l);
	}
	return 0;
}
```

---

## 作者：VanishmentThisWorld (赞：0)

比较水的一道题吧……下面讲做法

注意到题面里“**最小快乐值的最大值**”，容易想到二分答案。

于是我们只需要考虑 check 函数的实现。为了使得快乐值不比 check 的 $mid$ 小，我们将只考虑快乐值大于等于 $mid$ 的礼物。

又因为只在 $n-1$ 家买礼物，所以有以下两条结论：

1. 若一个人的礼物无论在哪家店都买不到，无解

1. 若没有一家店能同时买到至少两个人的礼物，无解 

然后代码就是这样：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-48,ch=getchar();
	return x*f;
}
#define rd read()
int t,n,m,a[200005],b;
inline int cal(int x,int y){return (x-1)*n+y;}
bool check(int mid){
	for(int j=1;j<=n;++j){
		int flg=1;
		for(int i=1;i<=m;++i)
			if(a[cal(i,j)]>=mid)flg=0;
		if(flg)return 0;
	}
	for(int i=1;i<=m;++i){
		b=0;
		for(int j=1;j<=n;++j)
			if(a[cal(i,j)]>=mid)b++;
		if(b>=2)return 1;
	}
	return 0;
}
signed main(){
	t=rd;
	while(t--){
		m=rd;n=rd;int l=1,r=1000000000,mid;
		for(int i=1;i<=m;++i)
			for(int j=1;j<=n;++j)
				a[cal(i,j)]=rd;
		while(l<r){
			mid=(l+r)>>1;
			if(check(mid+1))l=mid+1;
			else r=mid;
		}
		printf("%d\n",l);
	}
	return 0;
}
```


---

