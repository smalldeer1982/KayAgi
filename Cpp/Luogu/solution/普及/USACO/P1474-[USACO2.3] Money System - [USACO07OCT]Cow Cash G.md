# [USACO2.3] Money System / [USACO07OCT]Cow Cash G

## 题目描述

母牛们不但创建了它们自己的政府而且选择了建立了自己的货币系统。由于它们特殊的思考方式，它们对货币的数值感到好奇。

传统地，一个货币系统是由 $1,5,10,20,25,50,100$ 的单位面值组成的。

母牛想知道有多少种不同的方法来用货币系统中的货币来构造一个确定的数值。

举例来说, 使用一个货币系统 $(1,2,5,10, \ldots)$ 产生 $18$ 单位面值的一些可能的方法是：$18 \times 1, 9 \times 2, 8 \times 2+2 \times 1, 3 \times 5+2+1$，等等。

写一个程序来计算有多少种方法用给定的货币系统来构造一定数量的面值。保证总数在 $64$ 位带符号整数的范围内。


## 说明/提示

翻译来自NOCOW

USACO 2.3


## 样例 #1

### 输入

```
3 10
1 2 5
```

### 输出

```
10
```

# 题解

## 作者：dengyaotriangle (赞：61)

看没有写C++短代码题解的就来一发~

这题就是一个完全背包问题

dp方程 x(i)=sum(x(i-h(j))  边界x(0)=1

其中x(i)代表凑成i元有x(i)种方法，h(j)代表第j个货币的面值

```
#include<bits/stdc++.h>
long long v,n,h[30],dp[10005]={1};
int main(){
	std::cin>>v>>n;
	for(int i=0;i<v;i++) std::cin>>h[i];
	for(int i=0;i<v;i++)for(int j=h[i];j<=n;j++) dp[j]+=dp[j-h[i]];
	std::cout<<dp[n];
    return 0;
}
```

---

## 作者：睿屿青衫 (赞：21)

#裸的背包求方案总数

##之前不太懂，现在讲一下，其实都比较模糊，还得靠自己悟

###我之前78分，long long开着，最后发现输出的是int！

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 400010 
#define ll long long//定义ll为long long
ll p[maxn];
ll v,n,sum[maxn],f[maxn];
using namespace std;
int main()
{
    cin>>v>>n;
    for(int i=1;i<=v;++i)
     cin>>p[i];
    f[0]=1;//上面是面值，f[i]表示面值为i时方案数，0初始为1，因为唯一的方案就是不放钱
    for(int i=1;i<=v;++i)//枚举每种面值
     for(int j=p[i];j<=n;++j)//这也是完全背包写法，可无限用，如果j<该面值无需枚举，如果j>总数不合题意了（浪费时间）
      f[j]=f[j]+f[j-p[i]];//因为从前往后，更新j面值时的方案数
    printf("%lld",f[n]);//lld！！！切记！！！
    return 0;
}

```

---

## 作者：OItby (赞：16)

[传送门](https://www.luogu.org/problemnew/show/P1474)（货币系统）

### 分析
此题实际上也是一个最大化问题，即求组成面值为$N$的货币最多有多少种方案。可以用DP来做~~（本蒟蒻也只会用DP来做此题）~~，自底向上的方式求解，以样例为依据推出前I种货币组成面值为J的方案数，

### 如下表所示：

|  |  |  |  |  |  |  |  |  |  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
|前I种货币组成面值为J的方案数|0|1|2|3|4|5|6|7|8|9|10|
|1|1|1|1|1|1|1|1|1|1|1|1|
|2|1|1|2|2|3|3|4|4|5|5|6|
|3|1|1|2|2|3|4|5|6|7|8|10|

可见：

### 状态转移方程为：$dp[j]+=dp[j-p]$；


### 代码：
(蒟蒻代码，大佬勿喷……)

    #include <iostream>
	#include <cstdio>
	using namespace std;
	
	const int N=12000;
	long long dp[N];

	int main()
	{
		int v,n,p,i,j;
		scanf("%d%d%d",&v,&n,&p);
		dp[0]=1;
		for (i=p;i<=n;i+=p) dp[i]=1;
		for (i=2;i<=v;++i)
		{
			scanf("%d",&p);
			for (j=p;j<=n;++j) dp[j]+=dp[j-p];
		}
		cout<<dp[n]<<endl;
		return 0;
	}

---

## 作者：milk_candy (赞：13)

## 题意分析

给出n张货币和它们的面值，现在要组成金额m，问有多少种方案。

```plain
3 10
1 2 5

1+1+1+1+1+1+1+1+1+1
1+1+1+1+1+1+1+1+2
1+1+1+1+1+1+2+2
1+1+1+1+2+2+2
1+1+2+2+2+2
2+2+2+2+2
5+5
5+1+1+1+1+1
5+1+1+1+2
5+1+2+2
一共10种。
```

## 解题思路

- 由于这题每种货币有无限多张，我们很快就可以想到是“动态规划·完全背包”
- 但是近一看，这个题问的是**“多少种方案”**，跟我们平时做的“背包不超容量前提下**最大价值**”不同。
- 之前平时做的“背包不超容量前提下**最大价值**”，其$f_{i,j}$代表的是**对于前面i个物品，随便拿，不超过j背包容量所能获得的最大价值是多少。**
- 对于这个题目它要求方案数，数组元素值显然就不能存什么“最大价值”。我们可以确认f数组的元素值存的是**“方案数”**。



- 这题我们设有数组f，$f_{i,j}$代表对于前面i个物品，随便拿，**刚好达到**j背包容量的方案数为多少。

  ### 怎么弄f数组的转移方程？

  - 边界值：对于0张货币，组成金额为0的问题，方案只有1种：∅。所以$f_{0,0}=1$。
  - 怎么转移：![](https://cdn.luogu.com.cn/upload/image_hosting/5pl6ys6w.png)
  - 对于$f_{i,j}$，其转移方式有2种
    1. 第一种是“该物品不选”，则这种的方案数是$f_{i-1,j}$。
    2. 第二种是“该物品选”，则当前货币总额j应当**减去当前这张货币的面额$val_i$**；由于这里是**“每张货币有无限个”**，我们应该像图中②一样，**在$f_i$里面从下往上“叠”，这种的方案数是$f_{i,j-val_i}$，随着j从$val_i$到$m$的增加，货币也就自然完成了“从小到大”的完全背包。**
  - 所以我们两种可能列出来之后，就能列出我们的方程：
  - $f_{i,j}=f_{i-1,j}+f_{i,j-val_i}$。其中$i\in[1,n],j\in[val_i,m]$。

## 参考程序

```cpp
#include<stdio.h>
int max(int a,int b)
{
	if(a>b)
		return a;
	return b;
}
int MaxStorage,n,heavy[10005];
long long f[10005];
int main()
{
	scanf("%d%d",&n,&MaxStorage);
	for(int i=1;i<=n;i++)
		scanf("%d",&heavy[i]);
	f[0]=1; 
	for(int i=1;i<=n;i++)
		for(int j=heavy[i];j<=MaxStorage;j++)
			f[j]=f[j]+f[j-heavy[i]];
	printf("%lld",f[MaxStorage]);
	return 0;
}
```



---

## 作者：Hiraeth (赞：12)

就本题而言

其实状态转移方程并不算太难想出来

如下：

$f[j]+=f[j-a[i]]$

当前面值货币能够拓展的新的面值出　那么新的面值的可执行方案就加上拓展之前的面值的可执行方案数

于是　打了这个东东

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[10005],n,m,a[30];
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),f[a[i]]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
	if (j-a[i]>=0) f[j]+=f[j-a[i]];
	printf("%d\n",f[m]);
	return 0;
} 
```
想的是每种面值的取值情况是它本身　所以初始值是1　然后$dp$

但是他是错的…

~~为什么错　我想了一天~~

~~果然我太菜了~~

如果对每种面值的初值赋值为1的话　那么对每种面值进行枚举$dp$的时候　对当前值已经可以用后面的货币来表示了

打个比方：

```cpp
f[3]=1;
f[5]=1;
a[1]=3; 
f[8]+=f[8-3]; -> f[8]+=1;
a[2]=5;
f[8]+=f[8-5]; -> f[8]+=1;
```
可以很容易得发现　出现了重复情况　所以答案错误

究其根本是没有考虑动态规划的无后效性的原则　在当前状态的决策过程中考虑之后的决策因素　所以发生了重复情况　在当前状态只考虑当前状态因素　有之前状态推算

那么如何修改？

当前状态只考虑当前　那么我们令　$f[0]=1;$

对当前即为　$f[a[i]]+=f[a[i]-a[i]];$

就没有后面的影响了

愉快地打出了下面的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[10005],n,m,a[30];
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[0]=1; 
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
	if (j-a[i]>=0) f[j]+=f[j-a[i]];
	printf("%d\n",f[m]);
	return 0;
} 
```
[然后…尴尬了…](https://www.luogu.org/recordnew/show/16559635)

~~我以为我是对的……~~

哦

## long long

在此

蒟蒻提醒您：

WA千万条

long long第一条

看题不仔细

亲人两行泪

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[10005],n,m,a[30];
int main(){
	scanf("%lld%lld",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	f[0]=1; 
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
	if (j-a[i]>=0) f[j]+=f[j-a[i]];
	printf("%lld\n",f[m]);
	return 0;
} 
```


---

## 作者：Drifterming (赞：6)

/\*想尽办法凑一个数，给定的数字可以无限用，于是想到了完全背包.和普通的完全背包有点差别，

这里要求方案数，取了这个数相当于方案数没有变，不能+1，可以知道如果一个数能够取，

那么有取或不取两种策略，如果一个数不能取，那么就只有不能取的方案了，

那么状态转移方程:dp[j]+=dp[j-money[i]];\*/



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
long long money[30],dp[30005];
int main()
{
    int v,n;
    scanf("%d%d",&v,&n);
    for(int i=1;i<=v;i++)
    {
        scanf("%d",&money[i]);
    }
    dp[0]=1;
    for(int i=1;i<=v;i++)
    {
        for(int j=money[i];j<=n;j++)
        {
            dp[j]+=dp[j-money[i]];
        }
    }
    printf("%lld",dp[n]);
    return 0;
}
```

---

## 作者：275307894a (赞：5)

题目描述

母牛们不但创建了它们自己的政府而且选择了建立了自己的货币系统。由于它们特殊的思考方式，它们对货币的数值感到好奇。

传统地，一个货币系统是由1,5,10,20 或 25,50, 和 100的单位面值组成的。

母牛想知道有多少种不同的方法来用货币系统中的货币来构造一个确定的数值。

举例来说, 使用一个货币系统 {1,2,5,10,...}产生 18单位面值的一些可能的方法是:18x1, 9x2, 8x2+2x1, 3x5+2+1,等等其它。 写一个程序来计算有多少种方法用给定的货币系统来构造一定数量的面值。保证总数将会适合long long (C/C++) 和 Int64 (Free Pascal)，即在0 到2^63-1之间。

输入输出格式

输入格式：

货币系统中货币的种类数目是 V (1<=V<=25)。要构造的数量钱是 N (1<= N<=10,000)。

第一行: 二个整数，V 和 N 。

第二行： 可用的货币的面值 。

输出格式：

单独的一行包含那个可能的用这v种硬币凑足n单位货币的方案数。

输入输出样例

输入样例#1： 复制

3 10

1 2 5

输出样例#1： 复制

10

说明

翻译来自NOCOW

USACO 2.3

说实话，在做这道题的时候真的没想到dp(因为不怎么会)，想到贪心,递推什么的。后来一看，o(vn)差不多的复杂度，于是写了个dp。打了个板子，额。。。。。。，居然RE了!不知道是板子错了还是打挂了!考试时只得了70分。

```cpp
#include<cstdio>
using namespace std;
int max(int a,int b){
    return a>b?a:b;
}
int n,m;
long long a[5039],f[5001];
int main(){
    //freopen("money.in","r",stdin);
    //freopen("money.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    f[0] = 1;
    for(int i=1;i<=n;i++)
        for(int j=a[i];j<=m;j++)
            f[j] = f[j-a[i]] + f[j];
    printf("%lld",f[m]);
    return 0;
}
```

考完试一看，哦!没懂。也没看出个所以然来。无聊地把数组开大了一点，居然过了!

原来是没看数据!(悲催的血泪史)

AC代码:

拿来减的(f[j] = f[j-a[i]] + f[j];):

```cpp
#include<cstdio>
using namespace std;
int max(int a,int b){
    return a>b?a:b;
}
int n,m;
long long a[15039],f[15001];
int main(){
    //freopen("money.in","r",stdin);
    //freopen("money.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    f[0] = 1;
    for(int i=1;i<=n;i++)
        for(int j=a[i];j<=m;j++)
            f[j] = f[j-a[i]] + f[j];
    printf("%lld",f[m]);
    return 0;
}
```

拿来加的(简单多了):


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,f[514514]={1},a;
int main(){
	//freopen("money.in","r",stdin);
	//freopen("money.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a;
		for(int i=0;i<=m;i++){
			if(f[i])f[i+a]+=f[i];
		}
	}
	cout<<f[m]<<endl;
	return 0;
} 
```

还有，这道题一定要开long long，不然，会和我有一样的悲惨遭遇:https://www.luogu.org/recordnew/show/20114348

---

## 作者：EarthGiao (赞：3)

## 【思路】
完全背包    
很水的一道完全背包题目    

### 【题目大意】
一些面额的货币    
组合成n价值一共有多少种组合方式   

### 【核心思路】
假如你有a,b,c面值的硬币   
你需要凑足acioi的面额    
那么单纯看acioi来说    
acioi的组合数量是不是就是    
(acioi - a) ， （acioi - b） 和 (acioi - c)这三种面额组成方式的和？    
所以这就可以跑完全背包了    
只不过这里是加起来   
不是求最值了     
## 【完整代码】  
```cpp
#include<iostream>
#include<cstdio>
#define int long long 

using namespace std;
const int Max = 10005;
int b[Max] = {1},a[30];//默认b[0]为1，也就是在代码中减去一种硬币的面额之后等于0，是这一种硬币一个就可以组成的，所以次数是1 
signed main()
{
	int v,n;
	cin >> v >> n;
	for(register int i = 1;i <= v;++ i)
		cin >> a[i];
	for(register int i = 1;i <= v;++ i)
		for(register int j = a[i];j <= n;++ j)
			b[j] += b[j - a[i]];
	cout << b[n] << endl;
	return 0;
}
```

---

## 作者：litianqi2529298200 (赞：3)

```cpp
#include <iostream>
using namespace std;
long long v,n,m[30],dp[10005];/*设置货币种类数目v,要构造的数量钱n,方案数dp数组,可用货币面值m数组*/
int main()
{
    dp[0]=1;//初始化方案数为1
    cin>>v>>n;
    for(long long i=1;i<=v;i++)
    {
        cin>>m[i];//输入可用的货币面值
    }
    for(long long i=1;i<=v;i++)
    {
        for(long long j=m[i];j<=n;j++)
        {
            dp[j]+=dp[j-m[i]];/*将方案数逐个加上，得到答案*/
        }
    }
    cout<<dp[n];
    return 0;//输出并结束
}/***注意**:为了防止数据类型达不到题目要求我将所有的int都变为了long long*/
```

---

## 作者：Sundial (赞：3)

**首先，这道题大家首先想到完全背包，但是上了课之后老师说
多重背包也可以，所以本蒟蒻就来发一波题解好了，活不多说，直接上代码，里面有解释，大家可以参考一下，不过这种做法时间复杂度太高，仅限于数据范围小的哦**

代码如下


```cpp
#include <bits/stdc++.h>//多重背包
#define ll long long//一定要开long long
using namespace std;
ll n, m;
ll f[10021][10021];//f[i][j]表示第i种纸币总额为j的方案数
ll a[10021];
int main () {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {//枚举种类
		for (int j = 0; j <= m; j++) {//枚举纸币总值
			for (int k = 0; k * a[i] <= j; k++) {//枚举k张面值为a[i]的纸币
				f[i][j] += f[i - 1][j - k * a[i]];//方案数直接累加
			}
		}
	}
	printf("%lld\n", f[n][m]);
	return 0;
}
```


---

## 作者：ShineEternal (赞：2)

铺垫：对于一个给定了背包容量，物品费用，物品间相互的关系(分组、依赖等)的背包问题，除了再给定每个物品的价值后求可得到的最大价值外，还可以得到装满背包或将背包装至某一指定容量的方案总数。

对于这类改变问法的问题，一般只需将状态转移方程中的max改成sum即可

事实上，这样做可行的原因在于状态转移方程已经考察了所有可能的背包组成方案

**by 一本通**




不知道以前的题解有没有，但我直接把我知道的**两种**给大家说一下。

方法1：
```
//设f[j]表示面值为j的最大方案数，如果f[j-k*a[i]]!=0,则f[j]=f[j]+f[j-k*a[i]],当1<=i<=n,m>=j>=a[i],1<=k<+j/a[i].
#include<cstdio>
using namespace std;
int a[10001];
int n,m;
long long f[10001];//注意用long long
int main()
{
	scanf("%d%d",&n,&m);//n种面值的货币，组成面值为m
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);//输入每一种面值
	} 
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=a[i];j--)//f[j]表示面值为j的总方案数
		{
			for(int k=1;k<=j/a[i];k++)
			{
				f[j]+=f[j-k*a[i]];
			}
		}
	}
	printf("%lld",f[m]);//f[m]为最优解
	return 0;
}
```

方法2：
```
//设f[j]表示面值为j的总方案数，如果f[j-a[i]]!=0,则f[j]=f[j]+f[j-a[i]],1<=i<=n,a[i]<=j<=m.
#include<cstdio>
using namespace std;
int a[10001];
long long  f[10001];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=a[i];j<=m;j++)
		{
			f[j]+=f[j-a[i]];
		}
	}
	printf("%lld\n",f[m]);
	return 0;
}
```

希望大家能接受

求过

---

## 作者：kaiyuan (赞：0)

典型的完全背包问题。

不懂的同学请[点这里]
(https://www.luogu.org/blog/kaiyuandeboke/wan-quan-bei-bao)

状态转移方程：
f[j]+=f[j-v[i]];

其中f[j]代表凑成j元有f[j]种方法，v[i]代表第i个货币的面值.

补充一句：**十年OI一场空，不开long long见祖宗**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long v[10010],f[10100]={1};
int main(){
	int n;
	int V;
	cin>>n>>V;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1;i<=n;i++){
		for(int j=v[i];j<=V;j++){
			f[j]+=f[j-v[i]];
		}
	}
	cout<<f[V]<<endl;
	return 0;
}
```
珍爱生命，远离棕名，QAQ

---

## 作者：Thaumaturge (赞：0)

我是这么想的：如果这么取，那就可以有递归方程：dp[i]+=dp[i-v[j]]

(那我真是想得美)

稍微想一下，就能知道这是会重复的！如何去重？

于是就能想到：先sort货币价值一波，这样v就是单调的了，这样就可以再用一个下标j记录最后一个货币，保证其是最大的，就不会出现重复的情况了。

这样的就变成了：dp[i][j]+=dp[i-b[j]][k]，其中k<j.

最后把dp[i][1~m]全部加起来即可

代码如下：
```
#include <bits/stdc++.h>

using namespace std;

long long dp[10010][26],i,j,v[30],m,n,sum;

int main(){
	cin>>m>>n;
	for(i=1;i<=m;i++)
	cin>>v[i];
	dp[0][1]=1;
	sort(v+1,v+m+1);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			for(int k=1;k<=j;k++)
				if(i>=v[j])
				dp[i][j]+=dp[i-v[j]][k];

	for(i=1;i<=m;i++)
	sum+=dp[n][i];
	cout<<sum;
	return 0;
}
```


---

## 作者：xiebinyu (赞：0)

这是一道完全背包问题

所以我们要定义一个f数组来解决该问题

a数组则是货币的面值

~~本蒟蒻的~~代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
long long v,n,f[10005]={1},a[26];
int main(){
    cin>>v>>n;
    for(int i=0;i<v;i++){
        cin>>a[i];
    }
    for(int i=0;i<v;i++){
        for(int j=a[i];j<=n;j++){
            f[j]=f[j]+f[j-a[i]];
        }
    }
    cout<<f[n];
    return 0;
}
```

希望对大家有帮助 \\(^o^)/~

---

## 作者：森岛_帆高 (赞：0)

## 很讨厌长长的代码啦我喜欢短短的！

### 设 f [ j ] 表示面值为j的总方案数，如果 f [ j - a [ i ] ] ! = 0 ,则 f [ j ] = f [ j ] + f [ j - a [ i ] ] , 1 < = i < = n , a [ i ] < = j < = m 。

#### 上代码：
```cpp
#include<cstdio>
long long a[10001],f[10001],m,n;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);f[0]=1;
    for(int i=1;i<=n;i++)for(int j=a[i];j<=m;j++)f[j]+=f[j-a[i]];
    printf("%lld",f[m]);
    return 0;
}
```

---

## 作者：Celebrate (赞：0)

```cpp
//思路：虽然说是DP但是我感觉是递推 
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;
#define MAXX 11000
typedef long long ll;
ll f[MAXX];//f[i]表示价格i的方案数 
int n,v,a[31];
inline void read(int &Input) {//输入优化
	char Character;
	Input=0;
	Character=getchar();
	while(Character>'9'||Character<'0')Character=getchar();
	while(Character<='9'&&Character>='0') {
		Input*=10;
		Input+=Character-'0';
		Character=getchar(); } }
inline void dp() {
	int i,j;
	read(n); read(v);//输入 
	for(i=1; i<=n; i++) read(a[i]);
	f[0]=1;//0元就是一种方案，f[0]=1主要还是为后面的核心程序奠定重要基础 
	for(i=1; i<=n; i++)//每种货币列举一次，两个for循环反过来也是可以的，但是我比较喜欢这一种 
		for(j=a[i]; j<=v; j++)//列举每种情况 
			f[j]+=f[j-a[i]];//j的价格的方案数就不断地增加f[j-a[i]]，就是j-a[i]的面值数 
	printf("%lld\n",f[v]); }
int main() {
	dp(); }
```

---

## 作者：Seas0 (赞：0)

这道题看得出是完全背包 dp走起~

```c
/*#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;*/
#include <stdio.h>
const int maxn = 50000+1000;
long long v,n,dp[maxn],vs[100];//int 有 3 个点会爆！！！ 
int main()
{
    dp[0]=1;//初始化（金额为0时有且仅有一种方案） 
    scanf("%d%d",&v,&n);
    for (int i=1;i<=v;++i)scanf("%d",vs+i);//sort(vs+1,vs+1+v);// <--并不需要。。。 
    for (int i=1;i<=v;++i)
    for (int j=vs[i];j<=n;++j)dp[j]+=dp[j-vs[i]];/*转移方程：空间为j时被j-vs[i]更新*/printf("%d", dp[n]);
                //^ 
    return 0;           // ||
    //上面因为是完全背包，所以从前往后更新以多次选择同面值钞票    
}
```
代码较长，请见谅。

外加求管理员通过


---

## 作者：Shan＿Xian (赞：0)

 
 
 
 
```cpp
//使用母函数方法
#include <stdio.h>
#include <stdlib.h>
#define _DEBUG 0
#define MAX_C 25 //硬币最多种类数
#define MAX_MONEY 10000 //构造的最多钱数
//#define MAX_MONEY 500 //构造的最多钱数,debug
int main(){
    long long c1[MAX_MONEY+1];//定义数组 
    long long c2[MAX_MONEY+1];
    long long coins[MAX_MONEY+1];
    int v,n;
    freopen("money.in","r",stdin);//专业防抄袭 
#if _DEBUG==0
    freopen("money.out","w",stdout);
#endif
    int i,j,k,c;
    scanf("%d %d",&v,&n);//读入 
    for(i=0;i<v;++i){
        scanf("%ld",&coins[i]);
    }
    for(i=0;i<=n;++i){//初始化
        c1[i]=0;
        c2[i]=0;
    }
    c1[0]=1;
    for(i=0;i<=n;i+=coins[0]){  
        c1[i]=1;
    }
    for(i=1;i<v;++i){
        c=coins[i];
        for(j=0;j<=n;++j){//这里注意，是整个程序最核心的地方 
            for(k=0;k<=n && j+k<=n;k+=c){//j+k<=n 容易忘
                c2[j+k]+=c1[j];
            }
        }
        for(j=0;j<=n;++j){//处理 
            c1[j]=c2[j];
            c2[j]=0;
        }
    }
    printf("%lld\n",c1[n]);//注意打印long long 要用%lld
}//希望大家能学习到一些东西，使用母函数方法很普遍，也希望题解能过
```

---

## 作者：attack (赞：0)

这是一个裸完全背包问题，

虽然题解里写的都是一维的，但完全背包其实可以用二维去写。。

动态转移方程：

dp[i][j]=dp[i-1][j]+dp[i][j-a[i]];(j>=a[i])

dp[i][j]=dp[i-1][j];（j<a[i]）

初始化:

dp[i][0]=1

但是二维的不论是在空间还是在代码复杂度上都劣于一维，但略微易懂。

注意开long long ！！！！！！！！！！！！！！！！！

        
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define lli long long int 
using namespace std;
const lli MAXN=10001;
void read(lli &n)
{
    char c='+';lli x=0;bool flag=0;
    while(c<'0'||c>'9')
    {c=getchar();if(c=='-')flag=1;}
    while(c>='0'&&c<='9')
    {x=x*10+(c-48);c=getchar();}
    flag==1?n=-x:n=x;
}
lli dp[31][10001];
lli v,n;
lli a[30];
int main()
{
    read(v);// 拥有的种类
    read(n);// 需要构造的钱
    for(lli i=1;i<=v;i++)
    {
        read(a[i]);
        //dp[i][a[i]]=1;
        dp[i][0]=1;
    }
    for(lli i=1;i<=v;i++)
        for(lli j=1;j<=n;j++)
            if(j>=a[i])
                dp[i][j]=dp[i-1][j]+dp[i][j-a[i]];
            else 
                dp[i][j]=dp[i-1][j];
    printf("%lld",dp[v][n]);
    return 0;
}
```

---

## 作者：自动Wrong机 (赞：0)

两种算法，两种背包，任选》》》

1：完全背包

```cpp
var f:array[0..10000] of qword;
      a:array[0..1000] of longint;
          m,n,i,j:longint;
begin
  readln(n,m);
  for i:=1 to n do read(a[i]);
    fillchar(f,sizeof(f),0);
    f[0]:=1;for i:=1 to n do for j:=a[i] to m do
        f[j]:=f[j]+f[j-a[i]];//动规方程
    writeln(f[m]);
end. 
```
2：多重背包
```cpp
var f:array[0..10000] of qword;
          a:array[0..1000] of longint;
            m,n,i,j,k:longint;
begin
  readln(n,m);
    for i:=1 to n do read(a[i]);
    fillchar(f,sizeof(f),0);f[0]:=1;
    for i:=1 to n do
        for j:=m downto a[i] do
            for k:=1 to (j div a[i]) do
          if f[j-k*a[i]]<>0 then
                    f[j]:=f[j]+f[j-k*a[i]];//动规方程
    writeln(f[m]);
end. 
希望大家不要复制！别自己坑自己！
```

---

## 作者：梦景 (赞：0)

完全背包问题

设dp[i,j]表示前i种货币构成j的方法数，用cc记录货币的面值，状态转移方程为：

dp[i,j]=dp[i-1,j];    不用第i种货币

dp[i,j]=dp[i-1,j]+dp[i,j-cc[i]]    用第i种货币，j>=cc[i]

用qword会好一点

```cpp
var
 f:array[0..10000] of Qword ;
 a:array[1..25] of longint ;
 n,m,i,j:longint ;
BEGIN
 read(n,m) ;
 for i := 1 to n do
  read(a[i]) ;
 close(input) ;
 fillchar(f,sizeof(f),0) ;
 f[0] := 1 ;
 for i := 1 to n do
  for j := a[i] to m do
   f[j] := f[j] + f[j-a[i]] ;
 writeln(f[m]) ;
END .
```

---

## 作者：san9pk (赞：0)

对于样例，我们先列一个表格

0 1 2 3 4 5 6 7 8 9 10

1 1 1 1 1 1 1 1 1 1 1 1

2 1 1 2 2 3 3 4 4 5 5 6

5 1 1 2 2 3 4 5 6 7 8 10

其中横坐标j代表钱数，纵坐标代表每种货币对应的数额w[i]

通过观察我们可以发现：当j>=w[i]时，f[i][j]=f[i-1][j]+f[i][j-w[i]]

当j<w[i]时，f[i][j]=f[i-1][j]

可以采用滚动数组的方式来节省内存空间

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using std::sort;
const int maxn=10000+5;
long long a[maxn],b[maxn],w[30];//注意要用long long，int存不下
int main(int argc,char **argv)
{
    int n,v,i,j;
    scanf("%d%d",&v,&n);
    for(i=1;i<=v;i++)
        scanf("%lld",w+i);
    sort(w+1,w+v+1);
    memset(a,0,sizeof(long long)*(n+1));
    a[0]=1;
    for(i=1;i<=v;i++)
    {
        memcpy(b,a,sizeof(long long)*(n+1));
        for(j=w[i];j<=n;j++)
            b[j]+=b[j-w[i]];
        memcpy(a,b,sizeof(long long)*(n+1));//滚动数组
    }
    printf("%lld\n",a[n]);//输出结果
    return 0;
}
```

---

## 作者：yejie (赞：0)

原来以为，来个小小的深搜就行，谁叫2^25=‭33554432‬呢？

[可悲剧了……](https://www.luogu.org/recordnew/show/20246944)

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,v,a[201],ans;
void dfs(int x,long long s)
{
    if(s==v)
    {
        ans++;
        return;
    }
    if(x==n+1)
        return;
    dfs(x+1,s);
    for(int i=1;i*a[x]<=v-s;i++)
        dfs(x+1,s+i*a[x]);
}
int main()
{
    cin>>n>>v;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    dfs(1,0);
    cout<<ans;
}
```
这个方法，OJ里有一题叫[“皇后乳品”](http://prayer.hustoj.com/problem.php?cid=1194&pid=45)

电风扇（dfs，深搜）不给力，还是用“大片”（DP，动态规划）吧

小小的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,v,a[201],f[10001];//从左到右为：货币种类数量、是需兑换金额、每种面值（数组）、DP的中心——f数组 
int main()
{
    cin>>n>>v;//注意！n是货币种类数量，v是需兑换金额！ 
    for(int i=1;i<=n;i++)
        cin>>a[i];//每种面值。
    f[0]=1;//初始化。 
    for(int i=1;i<=n;i++)
        for(int j=a[i];j<=v;j++)
    	    f[j]+=f[j-a[i]];//居然不用"max"！ 
    cout<<f[v]; 
}
```
//蒟蒻的第一篇代码，求赞！


---

## 作者：Tchaikovsky (赞：0)

背包的方案总数嘛。。。。

懂完全背包的oier对于这道题来说应该很简单，本题就是一只变形的混血完全背包呀，把max换成加就可以了。

最后f【m】即为累加的方案总数了。

（小心int会爆的）

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int read()
{
    int r=0,k=1;
    char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')k=-1;
    for(;c>='0'&&c<='9';c=getchar())r=r*10+c-'0';
    return r*k;
}
int n,m;
int a[26];
long long f[10001];
int main()
{
    n=read();
    m=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    f[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=a[i];j<=m;j++)
            f[j]=f[j]+f[j-a[i]];
    cout<<f[m]<<endl;
    return 0;
}
```

---

