# The Party and Sweets

## 题目描述

 $ n $ boys and $ m $ girls came to the party. Each boy presented each girl some integer number of sweets (possibly zero). All boys are numbered with integers from $ 1 $ to $ n $ and all girls are numbered with integers from $ 1 $ to $ m $ . For all $ 1 \leq i \leq n $ the minimal number of sweets, which $ i $ -th boy presented to some girl is equal to $ b_i $ and for all $ 1 \leq j \leq m $ the maximal number of sweets, which $ j $ -th girl received from some boy is equal to $ g_j $ .

More formally, let $ a_{i,j} $ be the number of sweets which the $ i $ -th boy give to the $ j $ -th girl. Then $ b_i $ is equal exactly to the minimum among values $ a_{i,1}, a_{i,2}, \ldots, a_{i,m} $ and $ g_j $ is equal exactly to the maximum among values $ b_{1,j}, b_{2,j}, \ldots, b_{n,j} $ .

You are interested in the minimum total number of sweets that boys could present, so you need to minimize the sum of $ a_{i,j} $ for all $ (i,j) $ such that $ 1 \leq i \leq n $ and $ 1 \leq j \leq m $ . You are given the numbers $ b_1, \ldots, b_n $ and $ g_1, \ldots, g_m $ , determine this number.

## 说明/提示

In the first test, the minimal total number of sweets, which boys could have presented is equal to $ 12 $ . This can be possible, for example, if the first boy presented $ 1 $ and $ 4 $ sweets, the second boy presented $ 3 $ and $ 2 $ sweets and the third boy presented $ 1 $ and $ 1 $ sweets for the first and the second girl, respectively. It's easy to see, that all conditions are satisfied and the total number of sweets is equal to $ 12 $ .

In the second test, the boys couldn't have presented sweets in such way, that all statements satisfied.

In the third test, the minimal total number of sweets, which boys could have presented is equal to $ 4 $ . This can be possible, for example, if the first boy presented $ 1 $ , $ 1 $ , $ 2 $ sweets for the first, second, third girl, respectively and the second boy didn't present sweets for each girl. It's easy to see, that all conditions are satisfied and the total number of sweets is equal to $ 4 $ .

## 样例 #1

### 输入

```
3 2
1 2 1
3 4
```

### 输出

```
12```

## 样例 #2

### 输入

```
2 2
0 1
1 0
```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 3
1 0
1 1 2
```

### 输出

```
4```

# 题解

## 作者：cute_overmind (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1158A)
### 题目大意
有 $n$ 个男孩和 $m$ 个女孩，其中 $a_i$ 表示第 $i$ 个男孩给女孩糖果的最少数量，$b_i$ 表示第 $i$ 个女孩受到男孩糖果的最多数量，在第 $x$ 个女孩从男孩那里得到的糖果是 $g_x$。
### 题目分析
结论题。

为表示方便，这里记变量 $ans$ 为最终输出结果。

我们可以先分类讨论来找到结论。
- 如果 $b_n < g_1$，那么可以发现此时 $\max(a_1,a_2\dots a_n) < \min(b_1,b_2 \dots b_m)$，所以是无解的，$ans = -1$。
- 如果 $b_n = g_1$，那么此时 $ans = \max(a_1,a_2 \dots a_n)$。
- 如果 $b_n > g_1$，那么此时我们发现最优化是有一个男生给第二多的，其余男生给最多的。

### [代码](https://www.luogu.com.cn/record/162606862)
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5; 
int n , m , b[N], g[N] , ans;
signed main() 
{
    cin >> n >> m;
    for (int i = 1;i <= n;i++) cin >> b[i];
    for (int i = 1;i <= m;i++) cin >> g[i];
    sort(b + 1, b + n + 1);
    sort(g + 1, g + m + 1);
    if (b[n] > g[1]){
        cout << -1 << endl;
        return 0;
    }
    if (b[n] == g[1]){
        for (int i = 1;i < n;i++) ans += b[i] * m; 
        for (int i = 1;i <= m;i++) ans += g[i];
    } 
	else{
        for (int i = 1;i < n;i++) ans += b[i] * m;
        ans = ans - b[n - 1] + g[1] + b[n];
        for (int i = 2;i <= m;i++) ans += g[i];
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Storm_Lightning (赞：2)

# CF1158A The Party and Sweets

[题目传送门](https://www.luogu.com.cn/problem/CF1158A)

## 题目大意

有 $n$ 个男孩和 $m$ 个女孩，$a_i$ 表示第 $i$ 个男孩给女孩糖果的最少数量，$b_i$ 表示第 $i$ 个女孩受到男孩糖果的最多数量，求男孩给女孩最少多少糖果。

## 算法分析

这道题代码巨短，但思维量较大，可以考虑分类讨论。

- 如果男生送的最小值中的最大值比女生收到的最大值中的最小值小，那么是不可以。

- 我们发现如果男生送的最小值中的最大值和女生收到的最大值中的最小值一样，那么其他最大值就等于男生中的最大值。

- 如果一二条都不满足，那么找出一个男生中的次大值，其他都给最大值。

## 实例代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
long long n,m;
long long b[100086];
long long g[100086];
int main()
{
    scanf("%lld%lld",&n,&m);
    for(long long i=0;i<n;i++) 
    {
    	scanf("%lld",&b[i]);
	}
    for(long long i=0;i<m;i++) 
    {
    	scanf("%lld",&g[i]);
	}
    sort(b,b+n);
    sort(g,g+m);
    if(b[n-1]>g[0]) 
    {
    	printf("-1\n");
	}
    else
	{
        long long sum=0;
        if(b[n-1]==g[0])
		{
            for(long long i=0;i<n-1;i++)
            {
            	sum+=b[i]*m;
			}
            for(long long i=0;i<m;i++) 
            {
            	sum+=g[i];
			}
        }
        else
		{
            for(long long i=0;i<n-1;i++) 
            {
            	sum+=b[i]*m;
			}
            sum=sum-b[n-2]+g[0]+b[n-1];
            for(long long i=1;i<m;i++) 
            {
            	sum+=g[i];
			}
        }
        printf("%lld\n",sum);
    }
    return 0;
}
```

---

## 作者：king_xuan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/solution/CF1158A)

# 前言

#### 这道题代码不难，主要就是思维上

# 题意

有 $n$ 男孩和 $m$ 个女孩，每个男孩都给女孩分了糖果。

已经给出每个男孩分给每个女孩的糖果数量中最少的数量和每个女孩从一个男孩中收到的最大糖果数量

求男孩给出的最小糖果总数。

# 思路（分类讨论）

不难发现若男孩分给每个女孩的糖果数量中最少的数量中的最大值比每个女孩收到的糖果数量中最多的数量中的最小值大才行；

如果小了是不对的；

如果相同，所有最大值都会为男孩分给每个女孩的糖果数量中最少的数量中的最大值。

$b$ 数组表示每个男孩分给每个女孩的糖果数量中最少的数量，$g$ 数组表示个女孩收到的糖果数量中最多的数量。将这两个数组进行升序排序。

# 代码

```
#include<bits/stdc++.h>//万能头 
using namespace std;
#define int long long//建议大家都写上,毕竟"十年OI一场空,不开long long见祖宗" 
int n,m;
int b[100010],g[100010];
signed main(){//记得将int换成signed
    cin>>n>>m;
    for(int i=1;i<=n;i++){
	    cin>>b[i];
	}
    for(int i=1;i<=m;i++){
	    cin>>g[i];
	}
    sort(b,b+n);
    sort(g,g+m);
    if(b[n-1]>g[0]){
	    cout<<-1<<endl;
    }else{
        int ans=0;
        if(b[n-1]==g[0]){
            for(int i=0;i<n-1;i++){
			    ans+=b[i]*m;
			}
            for(int i=0;i<m;i++){
			    ans+=g[i];
			}
        }else{
            for(int i=0;i<n-1;i++){
			    ans+=b[i]*m;
			}
            ans=ans-b[n-2]+g[0]+b[n-1];
            for(int i=1;i<m;i++){
			    ans+=g[i];
			}
        }
        cout<<ans;
    }
    return 0;//养成好习惯 
}
```

---

## 作者：米奇 (赞：2)

## 思维题+分类讨论

首先发现如果男生送的最小值中的最大值比女生收到的最大值中的最小值 小，那么是不合法的。

我们发现如果男生送的最小值中的最大值和女生收到的最大值中的最小值一样，那么其他最大值就由男生中的最大值变成。

否则，留一个个男生中的次大值，其他都给最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int n,m,sum,ans,a[N],b[N];
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}*/
#define gc getchar
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	if(b[1]<a[n]){puts("-1");return 0;}//如果 
	if(a[n]==b[1])
	{
		for(int i=1;i<=n-1;i++)ans+=a[i]*m;
		for(int i=1;i<=m;i++)ans+=b[i];
		cout<<ans;
		return 0;
	}
	for(int i=1;i<=n-1;i++)ans+=a[i]*m;
	for(int i=1;i<=m-1;i++)ans+=b[i];
	ans-=a[n-1];
	ans+=b[m];
	ans+=a[n];
	cout<<ans;
	return 0;
	return 0;
}
```

---

## 作者：29SNyyds (赞：1)

# CF1158A 题解
## Step 1 理解题意
$2$ 个提醒：

1. 要注意每个男生是会给每个女生糖果的。

2. 中文题面没有标注如果女生收到糖果的最大值中的最小值甚至没有到男生给出的糖果数量的最小值中的最大值（男生并没有给出那么多的糖果），那么输出 $-1$.

## Step 2 整体思路
首先要注意要把男女生贡献和获得的糖果从小到大排序一遍，其次，判断无解，之后进行分类讨论。

#### 第一类：女生收到糖果的最大值中的最小值和男生给出的糖果数量的最小值中的最大值相等

处理办法：这意味着所有女生收到糖果的最大值都可以由男生给出糖果的最小值中的最大值来贡献，可以看代码。

#### 第二类：女生收到糖果的最大值中的最小值大于男生给出的糖果数量的最小值中的最大值

处理办法：这意味着除了第一个女生以外，其他所有女生收到糖果的最大值都可以由男生给出糖果的最小值中的最大值来贡献（第一个女生所需要的糖果的最大值大于男生给出的糖果数量的最小值中的最大值）

## Step 3 细节处理

注意开 long long。

## Step 4 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,t1[100001],t2[100001];
signed main() {
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>t1[i];
	for (int i=1;i<=m;i++) cin>>t2[i];
	sort(t1+1,t1+n+1);sort(t2+1,t2+m+1);
	if (t1[n]>t2[1]) {cout<<-1;return 0;} 
	else if (t1[n]==t2[1]) {int ans=0;
		for (int i=1;i<n;i++) ans+=t1[i]*m;
		for (int i=1;i<=m;i++) ans+=t2[i];
		cout<<ans;
	}	
	else if (t1[n]<t2[1]) {int ans=0;
		for (int i=1;i<=n;i++) ans+=t1[i];
		for (int i=1;i<=m;i++) ans+=t2[i];
		for (int i=1;i<=n-2;i++) ans+=t1[i]*(m-1);
		ans+=t1[n-1]*(m-2);
		cout<<ans;
	}
	return 0;
} 
```

---

## 作者：Rookie_t (赞：1)

### 就是一道分类讨论特判题 

预处理：把男生的数组和女生的数组排序。

首先找到无解的情况：

如果男生的最小值中的最大值比女生的最大值中的最小值小，那么无解。

还有特殊解的情况：

如果男生的最小值中的最大值和女生收到的最大值中的最小值相等，那么解就是男生的最大值。

否则，留一个个男生中的次大值，其他都给最大值。

代码： 

```cpp
#include<iostream>
#include<cstdio>
#include<alborithm>
#define int long long
usinb namespace std;
int n,m;
int ans;
int a[100010],b[100010];
sibned main(){
    cin>>n>>m;
    for(int i = 1;i <= n;i++){
	    cin>>a[i];
	}
    for(int i = 1;i <= m;i++){
	    cin>>b[i];
	}
    sort(a,a+n);
    sort(b,b+m);
    if(a[n-1]>b[0]){
	    cout<<-1<<endl;
    }
	else{
        ans = 0;
        if(a[n-1] == b[0]){
            for(int i=0;i<n-1;i++){
			    ans += a[i]*m;
			}
            for(int i=0;i<m;i++){
			    ans += b[i];
			}
        }
		else{
            for(int i=0;i<n-1;i++){
			    ans += a[i]*m;
			}
            ans = ans-a[n-2]+b[0]+a[n-1];
            for(int i = 1;i<m;i++){
			    ans += b[i];
			}
        }
        cout<<ans;
    }
    return 0;
}
```

---

## 作者：qiuweilin666 (赞：1)

### 题意
有 $n$ 个男孩，$m$ 个女孩，每个男孩给每个女孩一堆糖果。$b$ 数组表示每个男孩给出的最少糖果数，$g$ 数组表示每个女孩子收到的最大糖果数。求所有男孩给出的最小糖果总数。

### 题解

先对 $b$ 数组和 $g$ 数组从小到大排序。

#### 第一种情况：
如果给出最多的男孩比收到最少的女孩的还多，即 $b[n-1] >g[0]$，则不成立，直接输出 -1。

#### 第二种情况：
一共有 $n \times m$ 堆糖果，显然 $g$ 数组的糖果数只能出现一次 $($ 女孩收到的最大堆糖果只有一次，其他都是很小堆，能多小就多小 $)$，直接让最后一个男孩发每个女孩的最大堆糖果。

（1）当如果 $b[n-1] < g[0]$ 时：

比如：

```
3 2 

1 2 8

9 100
```
第三个男孩需要给出一堆 8 个的，再去满足所有 $g$ 数组，但是加上本来的一堆 8 个，第三个男孩一共给出 2 堆，取一堆 8 个的，只能再分配一个 $g$ 数组元素，则剩下一个 $g$ 数组元素需要其他男孩分配,就让第二个男孩来提供。最终是，第一个男孩给了 1，1 两堆，第二个男孩给了 2，9 两堆，第三个男孩给了 8，100 两堆。

所以有 $1+1+2+9+8+100=121$。

又如果 $g[0]$ 让第一个男孩给出，则第一个男孩给了 1，9 两堆，第二个男孩给了 2，2 两堆，第三个男孩给了 8，100 两堆。

所以有 $1+9+2+2+8+100=122$。

用贪心策略不难推出是倒数第二个男孩满足第一个女孩的最大堆。

（2）当如果 $b[n-1]=g[0]$ 时：

比如：

```
3 2 

1 2 8

8 100
```
第三个男孩在给出一堆 8 个的情况下 顺便满足了第一个女孩，那么他可以满足所有的女孩的最大堆。则第一个男孩给了 1 , 1 两堆，第二个男孩给了 2，2 两堆，第三个男孩给了 8，100 两堆。

所以有 $1+1+2+2+8+100=114$。

### 代码

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define ll long long
using namespace std;
ll n,m;
ll b[100086];
ll g[100086];
int main(){
    while(scanf("%lld %lld",&n,&m)!=EOF){
        for(ll i=0;i<n;i++) scanf("%lld",&b[i]);
        for(ll i=0;i<m;i++) scanf("%lld",&g[i]);
        sort(b,b+n);
        sort(g,g+m);
        if(b[n-1]>g[0]) printf("-1\n");
        else{
            ll sum=0;
            if(b[n-1]==g[0]){
                for(ll i=0;i<n-1;i++) sum+=b[i]*m;
                for(ll i=0;i<m;i++) sum+=g[i];
            }
            else{
                for(ll i=0;i<n-1;i++) sum+=b[i]*m;
                sum=sum-b[n-2]+g[0]+b[n-1];
                for(ll i=1;i<m;i++) sum+=g[i];
            }
            printf("%lld\n",sum);
        }
    }
}
```


---

## 作者：GeYang (赞：0)

# 题意

有 $n$ 个男孩和 $m$ 个女孩，每个男孩都给女孩分了糖果，给出每个男孩分给每个女孩的糖果数量中最少的数量，和每个女孩从一个男孩中收到的最大糖果数量，求出女孩收到的总糖果数最少是多少。

# 思路

- 如果男生送的最大值小于女生收的最小值，那么就会有一个不存在的人送出一个不存在的数，所以不符合题意。

- 如果男生送的最大值等于女生收的最小值，那么其他最大值就等于男生中的最大值。

- 如果男生送的最大值大于女生收的最小值，那就找出男生中的第二大值，别的都给最大值。

三种情况都出现了寻找最大值，所以要先排序。

# 代码

和其他人基本相同，不展示。

---

## 作者：_Michael0727_ (赞：0)

# 题解：CF1158A The Party and Sweets

[文章食用效果更佳](https://www.luogu.com.cn/article/wb6ehc4u)

---

## 审题

[题目传送门](https://www.luogu.com.cn/problem/CF1158A)

### 题意：

有 $n$ 个男孩和 $m$ 个女孩来参加聚会。每个男孩从一个男孩中收到的最大数量糖果，求出女孩收到的总糖果数最少是多少。所有男孩的编号都是 $1$ 到 $n$ 的整数，所有女孩的编号都是 $1$ 到 $m$ 的整数。在所有 $1 \leq i \leq n$ 的情况下，第 i 个男孩送给某个女孩的糖果的最小数量等于 $b_i$；在所有 $1 \leq j \leq m$ 的情况下，第 j 个女孩从某个男孩那里得到的糖果的最大数量等于 $g_j$。

---

## 思路

题目难度不大，但是需要**深度思考**。

进行分类讨论：

- 如果男生送的最小值中的最大值比女生收到的最大值中的最小值小，那么是不可能的，输出 $-1$。
- 如果男生送的最小值中的最大值和女生收到的最大值中的最小值一样，那么其他最大值就等于男生中的最大值。
- 如果以上情况都不满足，那么找出一个男生中的次大值，其他都给最大值。

---

**AC 代码**

```cpp
# include<bits/stdc++.h>
using namespace std ;
long long n , m , b [114514] , g [114514] ;
int main ( )
{
	cin >> n >> m ;
    for ( long long i = 1 ; i <= n ; i ++ )
    {
    	cin >> b [i] ;
	}
    for ( long long i = 1 ; i <= m ; i ++ )
    {
    	cin >> g [i] ;
	}
    sort ( b + 1 , b + n + 1 ) ;
    sort ( g + 1 , g + m + 1 ) ;
    if ( b [n] > g [1] )
    {
    	cout << -1 << endl ;
	}
    else
	{
        long long sum = 0 ;
        if ( b [n] == g [1] )
		{
            for ( long long i = 1 ; i < n ; i ++ )
            {
            	sum += b [i] * m ;
			}
            for ( long long i = 1 ; i <= m ; i ++ )
            {
            	sum += g [i] ;
			}
        }
        else
		{
            for ( long long i = 1 ; i < n ; i ++ )
            {
            	sum += b [i] * m ;
			}
            sum = sum - b [n - 1] + g [1] + b [n] ;
            for ( long long i = 2 ; i <= m ; i ++ )
            {
            	sum += g [i] ;
			}
        }
        cout << sum << endl ;
    }
    return 0 ;
}
```

---

[AC 记录](https://www.luogu.com.cn/record/162544049)

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1158A)

# 题意：
一共有 $n$ 个男孩，$m$ 个女孩，然后每一个男孩都要给女孩红包，给出每一个男孩给出最小的红包，和给出每一个女孩收到的最大的红包，让你求出怎样发红包使得红包总和最小。

# 思路：
1. 我们需要先判断不符合现实的情况，就是在男孩中的最小红包的最大应该小于女孩最大红包的最小，因为每个男孩都要给女孩红包，如果存在一个男孩的最小红包都大于这个女孩收到的最大红包是不可能的。（~~就像王思聪给你 $100$ 万，但你说不要这样~~）

2. 很明显直接贪心，让最小红包最大的派给女孩，但是你最小的红包还是要派出去，所以最多派 $m - 1$ 个女孩，但是如果她的最大红包恰好是你的最小，也能派。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int n,m,a[N],b[N],ans,x=1,y=1,flag,temp;
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+m,cmp);
	if(b[m]<a[1]){
		flag=1;
	}
	if(flag){
		cout<<-1<<endl;
	}else{
		while(x<=n){
			if((temp<m-1||a[x]==b[y])&&y<=m){
				ans+=b[y];
				temp++;
				y++;
			}else{
				ans+=(m-temp)*a[x];
				x++;
				temp=0;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
完结撒花~

---

