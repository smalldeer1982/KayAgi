# [USACO12MAR] Haybale Restacking G

## 题目描述

Farmer John has just ordered a large number of bales of hay.  He would like to organize these into N piles (1 <= N <= 100,000) arranged in a circle, where pile i contains B\_i bales of hay.  Unfortunately, the truck driver delivering the hay was not listening carefully when Farmer John provided this information, and only remembered to leave the hay in N piles arranged in a circle.  After delivery, Farmer John notes that pile i contains A\_i bales of hay.  Of course, the A\_i's and the B\_i's have the same sum.

Farmer John would like to move the bales of hay from their current configuration (described by the A\_i's) into his desired target configuration (described by the B\_i's).  It takes him x units of work to move one hay bale from one pile to a pile that is x steps away around the circle.  Please help him compute the minimum amount of work he will need to spend.

给出n块土地，现有泥土A[i]，需要改造成B[i]，但这次土地排列成环，且不可买进买出，只能运，且∑A[i]=∑B[i]，问最小花费。


## 说明/提示

There are 4 piles around a circle.  Initially, the piles contain 7, 3, 9, and 1 bales of hay.  Farmer John would like to move them so the piles contain 1, 4, 2, and 13 bales of hay.


A minimum of 13 units of work is required (move 6 bales from pile 1 to pile 4, move 1 bale from pile 3 to pile 2, and move 6 bales from pile 3 to pile 4).


## 样例 #1

### 输入

```
4 
7 1 
3 4 
9 2 
1 13 
```

### 输出

```
13 
```

# 题解

## 作者：Altwilio (赞：6)

#### $0.$ 前言
话说这题有至少四五倍经验啊，结论都一样。
本人太菜了考试的时候没有推出来。
将式子变形竟出现了 $\textbf{绝对值不等式}$。
#### $1.$ 翻译
农夫约翰订购了很多干草，他在农场里标记了 $N$ 个位置。这些位置近似地构成一个圆环。他原打算 让送货司机在 $i$ 号位卸下 $Bi$ 捆干草。然而，送货司机搞乱了约翰的部署，胡乱卸货之后就离开了。 约翰数了数，目前在 $i$ 号位有 $Ai$ 捆干草，(题目保证$∑Ai=∑Bi$）。

无奈之下，农夫约翰只能自己来移动这些干草。但他必须沿相邻位置来移动干草，每移动一捆干草到一个相邻位置，要消耗约翰一单位的能量。请帮约翰规划一下，他最少消耗多少能量才能让所有位置 的干草数量从 $Ai$ 变成 $Bi$ (注意：1 号位和 $N$ 号位也算作是相邻的！）
#### $2.$ 思路
本题与均分纸牌大体一致，除了变成换无他。
维护 $C$ 数组。内容是 $C[i] = B[i] - A[i] + C[i - 1]$
可以看出，$C[i]$ 是每一项 $B[i] - A[i]$ 的前缀和。
设 $X[i]$ 为 $i$ 到 $i + 1$ 的移动数量。有通项 $ X[i] = X[i] + A[1] + A[2] + … + A[i] - B[1] - B[2] - … - B[i]$，看到这里就知道前缀和数组的用处了。为使总移动距离最小，使: $|Q - C[1]| + |Q - C[2]| + … |Q - C[n]|$ 最小。$\textbf{绝对值不等式}$ 出现了，只需使 $Q$ 为 $C$ 数组排序后的中位数即可。
#### $3.$ 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100010;
int n, a[N], b[N], c[N];

int main(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i] >> b[i];
		c[i] += (b[i] - a[i] + c[i - 1]); 
	}
	sort(c + 1, c + n +1);
	int mid = c[n / 2 + 1];
	long long ans = 0;
	for(int i = 1; i <= n; i ++){
		ans += abs(mid - c[i]);
	}
	cout << ans;
	return 0;
}
```
非常简短。

---

## 作者：chager (赞：5)

（~~说真的楼下写的题解不是很能懂，可能是我太菜了~~）

前置知识：[P1031均分纸牌](https://www.luogu.org/problemnew/show/P1031)、小学奥数

这题一看真的没啥思路啊~~（虽然题意已经很明白了）~~

##### 算法一：乱搞（预计得分10～20pts）~~（其实我也不知道怎么乱搞，交一个P1031？）~~

##### 算法二：枚举a[1]往左移几个格子，往右移几个，然后再用P1031代码（预计得分30~60？？？没给部分分范围qaq）

### 算法三：
##### 考虑a[1]往n移几个格子：设向n移了k个，则：a[2]要往a[1]移b[1]-a[1]+k个，以此类推......所以a[n]要往a[n-1]移Σ(b[i]-a[i])（1<=i<n）+k个。不妨设a[x]要往a[(x-2)%n+1]（保证a[1]向a[n]移）移c[x]+k个（由此易知c[x+1]=c[x]+b[x]-a[x]），所以答案即为Σ|c[i]+k|（1<=i<=n）。

### 以下较重要：

##### 然后，k怎么求呢？
##### 其实，可以将|c[i]+k|转化为|c[i]-(-k)|，所以此时答案可以看成一条数轴上，值为c[i]（1<=i<=n）的点到（-k）的距离。所以：当k为其中位数时，答案最小。
##### (以下为证明，无兴趣看的巨佬可以略过)
![](https://cdn.luogu.com.cn/upload/pic/50383.png)

一：n为奇数

很显然，若此时k往右移x，那前（n+1）/2个数到k距离增加x，后（n-1）/2个数到k距离减小x，总距离增加一个x。往左同理。

![](https://cdn.luogu.com.cn/upload/pic/50387.png)

二：n为偶数

按照n为奇数的思路，易知k在c[n/2]和c[n/2+1]之间（包括两端点）时k最小。

综上，证毕。

上代码：
```cpp
# include <stdio.h>
# include <math.h>
# include <algorithm>
long long a[100010],b[100010],c[100010];
int main()
{
    int i,j,n;
    long long mi,an=0,m;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%lld%lld",&a[i],&b[i]);
    for(i=2;i<=n;i++)
        c[i]=c[i-1]+b[i-1]-a[i-1];
    std::sort(c+1,c+n+1);
    mi=c[(n+1)/2];
    m=0-mi;
    for(i=1;i<=n;i++)
        an+=abs(c[i]+m);
    printf("%lld",an);
    return 0;
}
```
（简洁明了的代码）

---

## 作者：yxy_ (赞：4)

### 大意：
从原来的环形数列变成目标数列，对于所有物品，每移动一个单位，移动距离 $x$ 花费为 $x$。

求变换成目标序列的最小花费。

---

### 思考：
移动距离 $=$ 花费，那就是**相邻位置之间传递一单位物品，花费为1。**

于是题意转化为：**相邻位置间相互传递，使得原序列变成目标序列。求最小移动的数量总和**。 
	
为[糖果传递](https://www.luogu.com.cn/problem/P2512)的一个变式题。
	
设 $x_i$ 为最终从 $i$ 位置传递到 $i+1$ 位置的总干草数量。则：

$B_i = A_i - x_i + x_{i-1}$；

目标数量 $=$ 该位置原数量 $-$ 传递到下一位置的总数量 $+$ 上一位置传递过来的总数量。 
	
$B_1 = A_1 - x_1 + x_n$；

$\Rightarrow$  $ x_1 = x_n + A_1 - B_1$；

$B_2 = A_2 - x_2 + x_1$；

$\Rightarrow$  $ x_2 = x_1 + A_2 - B_2 = x_n + A_1 + A_2 - B_1 - B_2$；

$B_3 = A_3 - x_3 + x_2$；

$\Rightarrow$ $ x_3 = x_2 + A_3 - B_3 = x_n + A_1 + A_2 + A_3 - B_1 - B_2 - B_3$；

$...$

$B_n = A_n - x_n + x_{n-1}$；

$\Rightarrow$ $  x_n = x_{n-1} + A_n - B_n = x_n + A_1 + A_2 +...+ A_n - B_1 - B_2 -...- B_n$；
	
要使移动的数量总和最小：
	即 $x_1 + x_2 + x_3 + ... + x_n$ 最小，令 $C_i = B_i - A_i$，则：

$|x_n - C_1| + |x_n - C_1 - C_2| + |x_n - C_1 - C_2 - C_3| + ... + |x_n - C1 - C_2 -...-C_n|$ 最小。
	
$C_i$ 维护前缀和 $S_i$，则使：
	$|x_n - S_1| + |x_n - S_2| + ...+ |x_n - S_n|$ 最小。
	
**绝对值不等式**，当 $x_n$ 为 $S_1,S_2...S_n$ 中位数的时候，总和最小。 

---

### Code：
```
#include<iostream>
using namespace std;

const int N=200010;
int n,m,a[N], b[N], c[N];

int main(){
	cin>>n;
	
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	
	for(int i=1;i<=n;i++) c[i]=b[i]-a[i], c[i]+=c[i-1]; //差值、前缀
	
	sort(c+1,c+n+1);
	
	int mid=c[n/2+1]; //取中位数
	
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=abs(mid-c[i]);
	}
	cout<<ans;
	
	return 0;
}
```

---

三倍经验：

[糖果传递](https://www.luogu.com.cn/problem/P2512)、
[士兵站队](https://www.luogu.com.cn/problem/P1889)。

---

## 作者：巨型方块 (赞：2)

假如
1给n k个

那么
1->n  k

2->1 b[1]-(a[1]-k)=b[1]-a[1]+k

3->2 b[1]+b[2]-a[1]-a[2]+k

。。。

n->n-1 Σ(b[i]-a[i])｛1<=i<n｝+k

那么我们可以计算出来每一个项除k外的部分成c[i]

那么答案就是

Σ|c[i]+k|｛1<=i<=n｝
那么k的最优解就是c[]的中位数取反；

这个就是均分纸牌了

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=1e5+5;
Ll a[N],b[N],c[N];
Ll n,m,mid,ans;
int main()
{
    scanf("%lld",&n);
    for(Ll i=1;i<=n;i++)scanf("%lld%lld",&a[i],&b[i]);
    for(Ll i=2;i<=n;i++)c[i]=c[i-1]+b[i-1]-a[i-1];
    sort(c+1,c+n+1);
    mid=c[(n+1)/2];
    m=0-mid;
    for(Ll i=1;i<=n;i++)ans+=abs(c[i]+m);
    printf("%lld",ans);
}

```

---

## 作者：ShineEternal (赞：1)

[如有显示不完整请点击这里](https://blog.csdn.net/kkkksc03/article/details/102164718)

## description：
![在这里插入图片描述](https://img-blog.csdnimg.cn/201910051857512.png)
## solution：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20191005185809232.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2tra2tzYzAz,size_16,color_FFFFFF,t_70)

## code:

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;
int a[100005],b[100005],c[100005];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
	}
	for(int i=2;i<=n;i++)
	{
		c[i]=c[i-1]+b[i]-a[i];
	}
	sort(c+1,c+n+1);
	int tmp=c[(n+1)/2];
	int x=-tmp;
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=abs(c[i]+x);
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：Sincerin (赞：0)

[题目传送门！](https://www.luogu.com.cn/problem/P3051)

[更好的阅读体验？](https://www.luogu.com.cn/blog/sincerin520/solution-p3051)

题外话：[双倍经验](https://www.luogu.com.cn/problem/SP11117)。

## 题意

雪豹的农场里有 $n$ 个仓库围成了一个**环**，每个仓库都有一个编号 $i \in [1,n]$。他买了一些干草堆，希望在第 $i$ 号仓库存放 $B_i$ 堆干草。奈何司机师傅表示这是另外的价钱，然后胡乱卸完货就走人了，于是雪豹只能自己花时间调整。现在第 $i$ 号仓库有 $A_i$ 堆干草，雪豹只能在第 $i$ 号仓库左右相邻的两个仓库中拿取干草堆来调整 $i$ 号仓库的数量，每运送一堆干草，雪豹要消耗 $1$ 点体力。求使得 $\forall i \in [1,n]$，仓库 $i$ 存放干草堆数变为 $B_i$ 的最小体力。

- $1 \leq n \leq 100000 \ , 1 \leq A_i,B_i \leq 1000$。

- 保证 $\sum_{i=1}^n{A_i}=\sum_{i=1}^n{B_i}$。

## 解析

这题算是环形均分纸牌的加强版。虽然不是均分了，但还是老套路（没做过均分纸牌的同学可以先看看[P2512](https://www.luogu.com.cn/problem/P2512)）。

我们只考虑向前传递的过程，进行贪心：

设第 $i$ 号仓库向 第 $i-1$ 号仓库运了 $C_i$ 堆干草， $i+1$ 号仓库向 第 $i$ 号仓库运了 $C_{i+1}$ 堆干草。

运之前 $i$ 号仓库有 $A_i$ 堆干草，现在有 $B_i$ 堆，可得：

$$A_i-C_i+C_{i+1}=B_i$$

移项，得：

$$C_{i+1}-C_i=B_i-A_i$$

观察柿子，容易发现：

$$C_{2}-C_1=B_1-A_1 $$
$$C_{3}-C_2=B_2-A_2 $$
$$\dots$$
$$C_{k}-C_{k-1}=B_{k-1}-A_{k-1} $$

对上述柿子求和，可得：

$$C_{k}-C_{1}=\sum_{i=1}^{k-1}(B_i-A_i)$$

即

$$C_{k}=C_{1}- \sum_{i=1}^{k-1}(A_i-B_i)$$

使用前缀和优化一下：

我们不妨设 $S_k=\sum_{i=1}^{k}(A_i-B_i)$，此时 $C_{k}=C_{1}- S_{k-1}$。

我们发现要使 $\sum{\mid C_i\mid}$ 最小化，实际上就是一个[货仓选址](https://www.acwing.com/problem/content/106/)问题，当 $C_1$ 为序列 $S$ 的中位数时，$\sum{\mid C_i\mid}$ 最小。

静态区间第 $k$ 小其实是可以通过归并的思想达到 $\Theta(n)$ 的，`STL` 的 `nth_element()` 貌似就是这么实现的。但是我比较懒，直接排序了。

时间复杂度 $\Theta(n \log n)$。

#### 注意：

- 中位数需要上取整，即 $\lceil \frac{n}{2}\rceil$。

- 对于取在中位数左边或右边，$C_i$ 会出现对应的正数或负数取值，最后统计的时候要取绝对值。

- 最后统计的序列应该是 $\sum_{i=2}^{n+1}{\mid C_i\mid}$，$C_i$ 是 $i$ 号仓库向 $i-1$ 号仓库运的堆干草，$\mid C_{n+1} \mid$ 也可以表示 $1$ 和 $n$ 之间的运输关系。若想使用 $\sum_{i=1}^{n}{\mid C_i\mid}$ 来统计，应该重新开一个数组保存前缀和，因为排序会改变前缀和顺序。

对于第 $3$ 条：

因为 $\sum_{i=1}^n{A_i}=\sum_{i=1}^n{B_i}$，所以 $S_n=\sum_{i=1}^n{(A_i-B_i)}=0$，排序后会来到 $S_1$ 的位置，导致答案少统计一个原来的 $S_1$。

## AC Code

```cpp
//C++20 O2 925B 52ms 3.47MB
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cmath>
#define _ 1
using namespace std; 
#define int long long//防止见祖宗 
#define ri register int
const int N=100001;
int n,k,a[N],b[N],c[N],s[N],ans,res;
inline void read(int &n)
{
	register bool f=false;
	register char c=getchar();
	while(c<'0'||c>'9'){f^=(c=='-');c=getchar();}
	while(c>='0'&&c<='9'){n=(n<<3)+(n<<1)+(c^48);c=getchar();}
	if(f) n=-n;
}
inline void print(int n)
{
	if(n<0){n=-n;putchar('-');}
	if(n>9) print(n/10); 
	putchar(n%10+'0');
}
signed main(void)
{
	read(n);
	for(ri i=1;i<=n;++i)
	{
		read(a[i]); read(b[i]); 
		a[i]+=a[i-1];//前缀和 of a
		b[i]+=b[i-1];//前缀和 of b
		s[i]=a[i]-b[i];//前缀和 of a-b
	}  
	sort(s+1,s+n+1);//排序 
	k=(n+1)>>1; c[1]=s[k];//中位数上取整 
	for(ri i=2;i<=n+1;++i) 
	{
		c[i]=c[1]-s[i-1]; //计算Ci 
		ans+=abs(c[i]);//统计
	}
	print(ans);
	putchar('\n'); 
	return !(0^_^0);//完结撒花！ 
}
```
[AC Record](https://www.luogu.com.cn/record/129499373)


另一种写法：

```cpp
signed main(void)
{
	read(n);
	for(ri i=1;i<=n;++i)
	{
		read(a[i]);
		read(b[i]); 
		a[i]+=a[i-1];
		b[i]+=b[i-1];
		d[i]=s[i]=a[i]-b[i];//d=s
	}  
	sort(s+1,s+n+1);
	k=(n+1)>>1; c[1]=s[k];
	for(ri i=1;i<=n;++i) 
	{
		c[i]=c[1]-d[i-1];//原来的前缀和d
		ans+=abs(c[i]);
	}
	print(ans);
	putchar('\n'); 
	return !(0^_^0);
}
```


---

## 作者：int08 (赞：0)

# 前言

我来到这道题的方式其实是 [通过这道题的多倍经验来到的](https://www.luogu.com.cn/discuss/475739)。

然后我把代码直接复制，粘贴，提交，不出所料，$0$ 分了。（
# Solution

虽然题目有一定的区别，但其实整体解法和 [P2125](https://www.luogu.com.cn/problem/P2125) 是差不多的。

大家可以先看那一道题，也可以参照 [我那一道题的题解](https://www.luogu.com.cn/blog/int08/solution-p2125)。

所以我们就在想如何让这一道题使用和那一题差不多的方法解出来。

同样设第 $i$ 个书架给了上个书架 $p_i$ 本书（这个数值可以为负数）。

于是我们得到一个有 $n$ 个未知数，$n$ 个方程的方程组。

但是其中有一个方程是跟前面的方程等价。

所以这是一个有 $n$ 个未知数，$n-1$ 个方程的不定方程组。

我们所需要求出的就是 $\sum\limits_{i=1}^n|p_i|$ 的最小值。

## 具体做法

### 计算 $p_i$
我们先给 $p_1$随便代一个值（例如我的代码中代入的是 $1$）。

于是我们就可以想如何用已知的 $p_1$ 求出其他的 $p_i$。

然后我们愉快地发现这道题中我们所需要的式子只是和上一道题有较小的区别而已。

具体的说本题中我们所获得的式子为：

$p_i=a_{i-1}-b_{i-1}-p_{i-1}$

于是我们照样可以把其他的 $p_i$ 求出来。

那么以下就和那道题是一样的了，~~我直接复制粘贴了啊哈。~~

### 使得结果最小化

容易发现这些数当且仅当同时加或者减相同的值时候，方程仍成立。

那我们如何让结果 $\sum\limits_{i=1}^n|p_i|$ 最小化呢？

同样容易发现，当 $p_i$ 大多数是正数的时候，对所有的数减 $1$ 之后，结果变得更小。（因为大多数的绝对值减了 $1$，少部分绝对值加了 $1$。）反之，当 $p_i$ 大多数是负数的时候，对所有的数减 $1$ 之后，结果变得更大。

那么最小值就出来了：当 $a$ 数组中正数和负数一样多的时候，结果达到了最小。

（因为此时不管是增加或者减少，都只能让结果变得更大。）

同时，因为所有数只能同加同减相同的值，所以说这些数的大小顺序其实是固定的。

那么什么时候正数和负数一样多呢？

~~C位出道的~~中位数闪亮登场！

没错，**当中位数正好被调整为0的时候，数组内正数和负数一样多，答案达到最小。**

所以我们只需要模拟一下以上的调整过程，时间复杂度 $O(n)$，就可以了。

这其中我们需要求中位数。~~方法一是使用 STL，~~ 方法二是先排一遍序，再找到中位数，时间复杂度 $O(n\text{log}n)$，方法三是使用快速排序的二分思想，平均时间复杂度 $O(n)$。

~~但是以本题的数据大小方法二就已经够用了，不需要再使用方法三写一大串代码。~~

于是这道题就做出来了。

# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
long long n,i,j,a[5555555],b[5555555],p[5555555],q[5555555],an,ans;
int main()
{
	n=read();b[1]=read();a[1]=read();
	p[1]=q[1]=1;
	for(i=2;i<=n;i++)
	{
		b[i]=read();a[i]=read();q[i]=p[i]=a[i-1]-(b[i-1]-p[i-1]);
	}
	sort(q+1,q+n+1);
	an=q[(n+1)/2];
	for(i=1;i<=n;i++)
	{
		p[i]-=an;
		ans+=abs(p[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```
~~容易发现自从上次比赛之后，我每次都使用的是那次比赛的快读模板。~~

---

## 作者：daniEl_lElE (赞：0)

看大家写的都是小学奥数，给个三分的解法。

## 思路

首先我们考虑暴力计算，容易发现我们可以枚举 $a_1$ 给 $a_2$ 的数量（可以是负数），这样复杂度是 $\Theta(n^2\times1000)$，显然不能通过。

容易发现，当我们在枚举时，有相邻的若干个最小值。那么我们现在就想通过一些速度较快的解法找到这个最小值。

当我们将 $a_i$ 给 $a_2$ 多了一个时，可以发现 $a_2$ 给 $a_3$ 的就自然会多一个，以此类推。我们发现这些给的时候可能为负数，那么对于负数就会减少方案书，对于正数就会增加方案，所以会发现每次修改量是和负数和正数的数量有关的，增加时，正数的数量会越来越多，导致了他变成了一个**凹函数**。想到这里，就可以自然使用有唯一定点函数求极值的三分法。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((L+R)>>1)
using namespace std;
int n,x[100005],y[100005];
int cal(int i){//cal函数的作用就是计算当a1给a2 i个时总共要多少个。
    int now[n+1];
    for(int j=1;j<=n;j++){
        now[j]=x[j];//先转到另一个数组中
    }
    now[1]-=i,now[2]+=i;
    int tmp=llabs(i);
    for(int j=2;j<n;j++){
        int zy=now[j]-y[j];//贪心，求需要给下一个多少个
        now[j]-=zy;
        now[j+1]+=zy;
        tmp+=llabs(zy);
    }
    tmp+=llabs(now[n]-y[n]);
    return tmp;
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&x[i],&y[i]);
    }
    int L=-n*1000,R=n*1000;//最小和最大值
    while(L<R){
        int a1=cal(mid),a2=cal(mid+1);//基本三分
        if(a1<a2){
            R=mid;
        }
        else{
            L=mid+1;
        }
    }
    cout<<cal(L);//最后不是输出a1个a2几个，而是总共多少个
    return 0;
} 
```

---

## 作者：mengdai (赞：0)

借用zhzh2001的话说

“这题其实本质就是一个均分纸牌”

然后这题就结

------------------------------------======================分割线===================------------------------------------

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
long long n,ans;
long long x[100003],y[100003],sum[100003];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        sum[i]=x[i-1]-y[i-1]+sum[i-1];
    }
    sum[1]=x[n]-y[n]+sum[n];
    sort(sum+1,sum+n+1);
    for(int i=1;i<=n;i++){
        ans+=abs(sum[i]-sum[n/2+1]);
    }
    cout<<ans<<endl;
    return 0;
}
```
/\*

in:
4
7 1
3 4
9 2
1 13

out:
13

\*/

---

