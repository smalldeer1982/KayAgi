# [USACO07JAN] Balanced Lineup G

## 题目描述

For the daily milking, Farmer John's N cows (1 ≤ N ≤ 50,000) always line up in the same order. One day Farmer John decides to organize a game of Ultimate Frisbee with some of the cows. To keep things simple, he will take a contiguous range of cows from the milking lineup to play the game. However, for all the cows to have fun they should not differ too much in height.

Farmer John has made a list of Q (1 ≤ Q ≤ 180,000) potential groups of cows and their heights (1 ≤ height ≤ 1,000,000). For each group, he wants your help to determine the difference in height between the shortest and the tallest cow in the group.

每天,农夫 John 的 $n(1\le n\le 5\times 10^4)$ 头牛总是按同一序列排队。

有一天, John 决定让一些牛们玩一场飞盘比赛。他准备找一群在队列中位置连续的牛来进行比赛。但是为了避免水平悬殊，牛的身高不应该相差太大。John 准备了 $q(1\le q\le 1.8\times10^5)$ 个可能的牛的选择和所有牛的身高 $h_i(1\le h_i\le 10^6,1\le i\le n)$。他想知道每一组里面最高和最低的牛的身高差。

## 样例 #1

### 输入

```
6 3
1
7
3
4
2
5
1 5
4 6
2 2```

### 输出

```
6
3
0```

# 题解

## 作者：stone_juice石汁 (赞：434)

## 线段树都有了，怎能少了树状数组？？

那我来补一发。

其实这道题有很多种解法，也有写$ST$表的，而且貌似时间复杂度还比较优秀。

但是多一种解法毕竟是好事，可以从不同角度去做一道题。

有一位巨佬也用的树状数组，~~但是貌似只贴了个代码~~，我这里还是发一下详细的题解，毕竟有些人可能不知道如何维护最大最小值。

## 进入正题：

既然明说了需要树状数组，那么肯定要知道树状数组是什么

**不知道树状数组是什么的童鞋们[戳这戳这戳这QWQ](https://www.luogu.org/blog/stonejuice/post-xue-xi-bi-ji-shu-zhuang-shuo-zu)**

阅读题面，很容易就可以发现题目要求区间查询最大值与最小值的差。

那么我们就用两个树状数组，分别维护所有数据的最大值和最小值。

- **树状数组必备：求$lowbit$：**

这个就不过多赘述了，应该都懂。

```cpp
int lowbit(int x)
{
    return x & -x;
}
```

- **建树，维护最大最小值**

首先从建树开始。

前面我们提到过，我们使用两个树状数组维护最大值和最小值，**我们姑且把维护最大值的树状数组定义为$treex$，维护最小值的则定义为$treen$**

那么，在向上传递的过程中，我们每传递一层，就比较一次，更新一次点。

这里打个比方：

- 1、
```
| 输入的数据 | 1 | / | / | / | / | / | / | / |
| 下标i     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| treex[i]  | 1 | 1 | 0 | 1 | 0 | 0 | 0 | 1 |
| treen[i]  | 1 | 1 |inf| 1 |inf|inf|inf| 1 |
```
- 2、
```
| 输入的数据 | 1 | 5 | / | / | / | / | / | / |
| 下标i     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| treex[i]  | 1 | 5 | 0 | 5 | 0 | 0 | 0 | 5 |
| treen[i]  | 1 | 1 |inf| 1 |inf|inf|inf| 1 |
```
- 3、
```
| 输入的数据 | 1 | 5 | 3 | / | / | / | / | / |
| 下标i     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| treex[i]  | 1 | 5 | 3 | 5 | 0 | 0 | 0 | 5 |
| treen[i]  | 1 | 1 | 3 | 1 |inf|inf|inf| 1 |
```
- 4、
```
| 输入的数据 | 1 | 5 | 3 | 9 | / | / | / | / |
| 下标i     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| treex[i]  | 1 | 5 | 3 | 9 | 0 | 0 | 0 | 9 |
| treen[i]  | 1 | 1 | 3 | 1 | inf | inf | inf | 1 |
```
- 5、
```
| 输入的数据 | 1 | 5 | 3 | 9 | 4 | / | / | / |
| 下标i     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| treex[i]  | 1 | 5 | 3 | 9 | 4 | 4 | 0 | 9 |
| treen[i]  | 1 | 1 | 3 | 1 | 4 | 4 | inf | 1 |
```
- 6、
```
| 输入的数据 | 1 | 5 | 3 | 9 | 4 | 2 | / | / |
| 下标i     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| treex[i]  | 1 | 5 | 3 | 9 | 4 | 4 | 0 | 9 |
| treen[i]  | 1 | 1 | 3 | 1 | 4 | 2 | inf | 1 |
```
- 7、
```
| 输入的数据 | 1 | 5 | 3 | 9 | 4 | 2 | 11 | / |
| 下标i     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| treex[i]  | 1 | 5 | 3 | 9 | 4 | 4 | 11 | 12 |
| treen[i]  | 1 | 1 | 3 | 1 | 4 | 2 | 11 | 1 |
```
- 8、
```
| 输入的数据 | 1 | 5 | 3 | 9 | 4 | 2 | 11 | 14 |
| 下标i     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| treex[i]  | 1 | 5 | 3 | 9 | 4 | 4 | 11 | 14 |
| treen[i]  | 1 | 1 | 3 | 1 | 4 | 2 | 11 | 1 |
```
- $END$

就像刚刚那样，每次传递最大值与最小值（就是把求区间和树状数组中的累加改为了求最值）

建树代码：

```cpp
void _add(int x, int k)//建树QAQ 
{
    for(;x <= n; x += lowbit(x))
    {
    	treex[x] = max(treex[x], k);
    	treen[x] = min(treen[x], k);
    }
}
```

- **区间查询最大值与最小值**

我们刚刚说过，建树时可以直接套区间和的板子，只需要把累加改成求最值就可以了。

但是求最大值与最小值不行。因为他没有像求区间和那样的性质。

**因为区间合中，要查询$[x,y]$的区间合，是求出$[1,x-1]$的合与$[1,y]$的合，然后相减就得出了$[x,y]$区间的合。**

但是很明显，求最值是不能相减求得的，这个时候我们就要想另外一种办法。

我们这里分两中情况讨论

- 1、 $y-lowbit(y) > x$ ，这种情况下，**我们可以把求$[x,y]$区间的最值拆分成两部分，先求$[x,y-lowbit(y)]$中最值与$[y-lowbit(y)+1,y]$中的最值，再求这两者的最值。**

	稍微细心一点，就可以发现 $[y-lowbit(y)+1,y]$ 就是$tree[y]$（可以口模一下）。
    
   于是，问题就转化为：求 $[x,y-lowbit(y)]$中最值 与 $tree[y]$的最值。
   
- 2、$y-lowbit(y) < x$，在这种情况下，**我们直接把 a[y]（第$y$个输入的数据）给剥离出来，于是原问就变成了：求 $[x,y-1]$中最值 与 $a[y]$ 的最值。**

这两种情况想明白之后，就可以用**递归**解决问题了。

**递归到某一层时，$x == y$，这个时候返回 $a[x]$ 或 $a[y]$ 就行了。（毕竟 $x == y$时，区间$[x,y]$就只有$a[x]$这一个数据了）**

贴这部分的代码：

```cpp
//下面两个子函数本质上是一样的

int _findmax(int x, int y)//区间查询最大值 
{ 
	if(y > x)
	{
		if(y - lowbit(y) > x) return max(treex[y], _findmax(x, y - lowbit(y)));
		else return max(a[y], _findmax(x, y - 1));//如上所述
	}
	return a[x];
}

int _findmin(int x, int y)//区间查询最小值 
{ 
	if(y > x)
	{
		if(y - lowbit(y) > x) return min(treen[y], _findmin(x, y - lowbit(y)));
		else return min(a[y], _findmin(x, y - 1));
	}
	return a[x];
}
```

- **合并代码**

上面这两个处理完之后，就可以合并代码了。

毕竟这里没有什么单点修改之类的操作。

这里有一个要注意的点：**$treen$（维护最小值的树状数组）最开始要全部赋值为$inf$。毕竟是存最小值。而$treex$（维护最大值的树状数组）就不管了，因为没有数据小于$0$。**（实际上建树的表格里就体现出这一点了）

**最后按照题目要求来，用区间最大值减去最小值就可以了。**

## 上代码！

```cpp
#include<bits/stdc++.h>
#define mian main
#define QWQ puts("QWQ");
using namespace std;

int n, m;
int a[50005] ,treex[50005], treen[50005];

int lowbit(int x)//求lowbit:2进制下末尾0的个数。可表示tree中包含数据数量 
{
    return x & -x;
}

void _add(int x, int k)//建树QAQ 
{
    for(;x <= n; x += lowbit(x))
    {
    	treex[x] = max(treex[x], k);
    	treen[x] = min(treen[x], k);
    }
}

int _findmax(int x, int y)//区间查询最大值 
{ 
	if(y > x)
	{
		if(y - lowbit(y) > x) return max(treex[y], _findmax(x, y - lowbit(y)));
		else return max(a[y], _findmax(x, y - 1));
	}
	return a[x];
}

int _findmin(int x, int y)//区间查询最小值 
{ 
	if(y > x)
	{
		if(y - lowbit(y) > x) return min(treen[y], _findmin(x, y - lowbit(y)));
		else return min(a[y], _findmin(x, y - 1));
	}
	return a[x];
}

int main()
{
    memset(treen, 0x3f3f3f3f, sizeof(treen));
	scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++) 
    {
        scanf("%d", &a[i]);
        _add(i, a[i]);
    }
    for(int i = 1; i <= m; i ++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        cout << _findmax(l, r) - _findmin(l, r) << endl;
    }
    return 0;
}
```

~~（悄悄求赞，应该没人发现我QAQ）~~

---

## 作者：白烛葵 (赞：201)

~~好奇为啥标签没ST表~~

这题让我们求某个区间的最大，最小值的差值

看到数据范围，就知道用O(nlogn)复杂度的算法过
# 一看就知道用ST表写
不用想太复杂QWQ

如果你理解了ST表模板并A了，把模板改一下，加个最大值，就行了QWQ~~伪双倍经验~~

如果不知道ST表QWQ，我科普一下，如果想进一步了解，可以去做ST模板

ST表是专门用来求多个区间的最大，最小值，用的是倍增的思想，类似于动规

先用O(nlogn)和一个~~动规~~方程进行处理数组

之后在O(1)调用出每个区间的最大，最小值QWQ

在求完全不定区间的最值上，优于单调队列

是不是一个很神奇的算法，而且代码量不多，求一个最值只要写6行

# 重点是速度超快的QWQ

## 一共只用了316ms

下面上代码，只有28行，蒟蒻~~懒人~~福利QWQ
```
#include<bits/stdc++.h>
using namespace std;
int lxy[180010][22],hrb[180010][21],n,m,i,j,k,l,r;
//lxy数组用于求最大值，hrb数组用于求最小值
int ST(int l,int r)//O(1)调用QWQ
{
    int s=log2(r-l+1),x,y;
    //log2(r-l+1)是以2为底的对数，写成等式就是，2的log2(r-l+1)次方等于(r-l+1);
    x=max(lxy[l][s],lxy[r-(1<<s)+1][s]);//区间最大
    y=min(hrb[l][s],hrb[r-(1<<s)+1][s]);//区间最小
    //神奇的冻柜方程QWQ，记下来就好，反正不长
    return x-y;//返回差值
}
int main()
{
    scanf("%d%d",&n,&m);//输入
    for(i=1;i<=n;i++)
    scanf("%d",&lxy[i][0]),hrb[i][0]=lxy[i][0];//因为要用两个数组QWQ
	for(i=1;i<=21;i++)//这个循环的上界决定于数据的大小，即2的21次方大于数据，如果数据在大上界调高，logn是这个循环QWQ
	for(k=1;k+(1<<i)<=n+1;k++)//接进于n，算成n，其实没那么大
	{
		lxy[k][i]=max(lxy[k][i-1],lxy[k+(1<<(i-1))][i-1]);
		hrb[k][i]=min(hrb[k][i-1],hrb[k+(1<<(i-1))][i-1]);
        //神奇冻柜方程处理QWQ，不理解，也可以下来，只有4行
	}
	for(i=1;i<=m;i++)//O(1)调用开始
	{
		scanf("%d%d",&l,&r);
		printf("%d\n",ST(l,r));//上面的函数，直接输出返回值
	}
	return 0;//结束
}
```
是不是很神奇的算法，只要28行就可以切一道蓝题，是不是很开心

而且短，少，快。。。

实在是蒟蒻必备算法QWQ

很容易就学会了

如果想进一步了解ST表的，可以在洛谷找模板题

~~偷偷说一句其实ST表的很多题目是多倍经验QWQ~~

如果你认可我的思路话

# 请点赞，关注，~~投食，素质三连~~，谢谢支持QWQ

~~不可以拒绝的拥抱~~

---

## 作者：Yeji_ (赞：34)

### 前言
今天学会的RMQ，如果你跟着我的脚步走，你也会学会又短又实用的RMQ了！！！
### 题意
很清晰了，就是求一个区间内的最大值减掉最小值了，没什么可说的
### RMQ
RMQ指的是求一个区间的某个数值（例如：最大值，最小值......)

### 实现
#### 预处理

设$a[i]$是要求区间最值的数列，$F[i, j]$表示从第i个数起连续2^j个数中的最大值。（DP的状态）

例如：
a数列为：3 2 4 5 6 8 1 2 9 7

F[1，0]表示第1个数起，长度为2^0=1的最大值，其实就是3这个数。

同理 F[1,1]=max(3,2)=3,F[1，2]=max(3,2,4,5) = 5 F[1，3] = max(3,2,4,5,6,8,1,2) = 8;

并且我们可以容易的看出F[i,0]就等于a[i]。（DP的初始值）

我们把F[i，j]平均分成两段（因为F[i，j]一定是偶数个数字），
从 i 到i + 2 ^ (j - 1) - 1为一段，i + 2 ^ (j - 1)到i + 2 ^ j - 1为一段(长度都为2 ^ (j - 1))。

于是我们得到了状态转移方程$F[i, j]$=$max$$（F[ij-1],F[i+2^(j-1)，j-1]）$。


#### 查询

假如我们需要查询的区间为(i,j)，

那么我们需要找到覆盖这个闭区间(左边界取i，右边界取j) 的最小幂（可以重复，比如查询1，2，3，4，5，我们可以查询1234和2345）。

因为这个区间的长度为j - i + 1,所以我们可以取
k=log( j - i + 1)(以2为底）

则有：RMQ(i, j)=max{F[i , k], F[ j - 2 ^ k + 1, k]}。

```cpp
void work(int n) 
{
    for (re int i=1;i<=n;i++) f[i][0]=a[i];
    for (re int j=1;(1<<j)<=n;j++) 
        for (re int i=1;i+(1<<j)-1<=n;i++) 
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j - 1]);
}
int RMQ(int l, int r) 
{
    re int k=0;
    while ((1<<(k+1))<=r-l+1)
         k++;
    return max(f[l][k],f[r-(1<<k)+1][k]);
}
```
代码就很显然了，上面是求最大的

下面是求最小的
```cpp
void work2(int n) 
{
    for (re int i=1;i<=n;i++) dp[i][0]=a[i];
    for (re int j=1;(1<<j)<=n;j++) 
        for (re int i=1;i+(1<<j)-1<=n;i++) 
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j - 1]);
}
int RMQ2(int l, int r) 
{
    re int k=0;
    while ((1<<(k+1))<=r-l+1)
         k++;
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
}
```

这样就能得出全代码了
```cpp
#include<cstdio>
#include<iostream>
#define re register
using namespace std;
int a[2000005],f[50005][20],dp[50005][20];
void work(int n) 
{
    for (re int i=1;i<=n;i++) f[i][0]=a[i];
    for (re int j=1;(1<<j)<=n;j++) 
        for (re int i=1;i+(1<<j)-1<=n;i++) 
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j - 1]);
}
int RMQ(int l, int r) 
{
    re int k=0;
    while ((1<<(k+1))<=r-l+1)
         k++;
    return max(f[l][k],f[r-(1<<k)+1][k]);
}
void work2(int n) 
{
    for (re int i=1;i<=n;i++) dp[i][0]=a[i];
    for (re int j=1;(1<<j)<=n;j++) 
        for (re int i=1;i+(1<<j)-1<=n;i++) 
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j - 1]);
}
int RMQ2(int l, int r) 
{
    re int k=0;
    while ((1<<(k+1))<=r-l+1)
         k++;
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
}
int main()
{
    re int n,m;
    scanf("%d %d",&n,&m);
    for (re int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    work(n);    
    work2(n);
    for (int i=1;i<=m;i++)
    {
    	int l,r;
    	cin>>l>>r;
    	printf("%d\n",RMQ(l,r)-RMQ2(l,r));
	}
}

```






---

## 作者：轩槿 (赞：16)

#### 要求出最高和最低奶牛之间的身高差，自然就要知道最高和最低奶牛的身高，直接的想法就是贪心暴力，直接搜一遍区间，但这样很明显就会超时，那我们就想一想如何先将每一个区间内的奶牛身高最高和最低求出来，每次询问直接调用就好，这样我们就很容易想到要用到RMQ这个神奇的东西（我觉得每个算法都好神奇、、-_-|||）。
### RMQ（Range Minimum/Maximum Query），即区间最值查询，是指这样一个问题：对于长度为n的数列A，回答若干次询问RMQ(i,j)，返回数列A中下标在区间[i,j]中的最小/大值。RMQ就要用到ST算法这个也很神奇的算法
## ST（Sparse Table）算法可以在O(nlogn)时间内进行预处理，然后在O(1)时间内回答每个查询。
这个题分为两个部分，第一部分是预处理，（重点在这哈）要用到ST算法哈
设A[i]是要求区间最值的数列，F[i, j]表示从第i个数起连续2^j个数中的最大值。
###### 例如
##### A数列为：3 2 4 5 6 8 1 2 9 7
F[1，0]表示第1个数起，长度为2^0=1的最大值，其实就是3这个数。
同理 F[1,1] = max(3,2) = 3, F[1，2]=max(3,2,4,5) = 5，F[1，3] = max(3,2,4,5,6,8,1,2) = 8;
###### 并且我们可以容易的看出F[i,0]就等于A[i]。
##### 我们把F[i，j]平均分成两段（因为F[i，j]一定是偶数个数字），从 i 到i + 2 ^ (j - 1) - 1为一段，i + 2 ^ (j - 1)到i + 2 ^ j - 1为一段(长度都为2 ^ (j - 1))。于是我们得到了状态转移方程F[i, j]=max（F[i，j-1], F[i + 2^(j-1)，j-1]）。
第二部分是查询这就很随意而简单啦一般都是根据题目自己变的。。
大致的RMQ就这样具体的自己找度娘或是个随便什么网站一查就知道了，，
下面来看看这题
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
 using namespace std;
const int M=50005,N=50;
int f1[M][N],f2[M][N],x;//因为是求最大和最小值所以有两个f数组
int n,q;
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
	    scanf("%d",&x);//我直接省掉了A数组。凑个或者看吧╮(╯▽╰)╭反正内容都一样把X当做A就好啦
	    f1[i][0]=f2[i][0]=x;//初始化，从i头奶长度为2^0的区间也就是自己。
	}
	for(int j=1;1<<j<=n;j++)//枚举2的j次方
	    for(int i=1;i+(1<<j)-1<=n;i++){//枚举起点
	        f1[i][j]=max(f1[i][j-1],f1[i+(1<<j-1)][j-1]);//从i开始长度为2^j的区间最大值。（2^j=2^(j-1)+2^(j-1)这个简单的东西就可以解释f1[i+(1<<j-1)][j-1]了。                                            
	        f2[i][j]=min(f2[i][j-1],f2[i+(1<<j-1)][j-1]);//与上面同理
	    }
	while(q--){
		int a,b,k,m1,m2;
		scanf("%d%d",&a,&b);
		k=log2(b-a+1);//求出区间内a最多加多少2次方（2^j中j的最大值）
		m1=max(f1[a][k],f1[b-(1<<k)+1][k]);//区间分为a到2^K和b-2^K+1到b两部分
		m2=min(f2[a][k],f2[b-(1<<k)+1][k]);
		printf("%d\n",m1-m2);
	}
	return 0;
}

```

---

## 作者：ysner (赞：13)

题意：给一个序列，求一段区间的极差。

看看n<=50000，必定是用O（nlogn）时间复杂度的RMQ。

但RMQ的实现方式有许多种，树状数组、线段树、ST表都可以。

鉴于前面的大佬只给出了线段树与ST表做法，我就来一发常数小、代码短的树状数组，据说速度一交就排rank3，180ms，还是很快的。

用树状数组原理同时维护区间最大值最小值即可。

```cpp
    #include<iostream>
        #include<cstdio>
        #include<cmath>
        #include<cstring>
        #include<cstdlib>
        #include<algorithm>
        #include<queue>
        #define ll long long
        #define re register
        #define il inline
        #define fp(i,a,b) for(re int i=a;i<=b;i++)
        #define fq(i,a,b) for(re int i=a;i>=b;i--)
        using namespace std;
        const int N=50005; 
        int n,q,c[N],b[N],s[N]; //b维护最大值，s维护最小值
        il int gi()
        {
          re int x=0,t=1;
          re char ch=getchar();
          while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
          if(ch=='-') t=-1,ch=getchar();
          while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
          return x*t;
        }
        il void add(re int x,re int k)//区间维护最大最小值
        {
            for(;x<=n;x+=x&-x) b[x]=max(b[x],k),s[x]=min(s[x],k);
        }
        il int Query(re int l,re int r)//区间查询最大最小值
        {
            re int mn=2e9,mx=-1;
            while(l<=r)
            {
                for(;r-(r&-r)>=l;r-=r&-r) mx=max(mx,b[r]),mn=min(mn,s[r]);
                mx=max(c[r],mx);mn=min(mn,c[r]);
                r--;//还有一部分区间未涉及
            }
            return mx-mn;
        }
        int main()
        {
            memset(s,63,sizeof(s));
            n=gi();q=gi();
            fp(i,1,n)
            {
                c[i]=gi();
                add(i,c[i]);
            }
            fp(i,1,q) 
            {
              re int l=gi(),r=gi();
              printf("%d\n",Query(l,r));
            }
            return 0;
}
```

---

## 作者：shuiyuhan (赞：8)

  这题居然没有p的题解，那我来发一发
  
  题意：求l-r这个区间最大值与最小值的差
  
  于是我们联想到这是一个~~(线段树裸题)~~区间求最值的问题。
  
  区间求最值我用的是线段树。 
  
  如果不会线段树请自行学习
  
  维护两颗线段树，用tree维护区间内的最小值
  
  同时用tree1维护区间内的最大值，在求值时分别求出最大与最小值相减就行了，时间O(m lg n)
  
  上代码(代码里有注释)
```pascal
uses math;
//math库是个好东西，但注意在正式比赛里千万不要用，加assign后会217错误
var
  i,j,n,k,m,oo,ans,p,mid,x,y,id:longint;
  a,tree,tree1:array[0..4000009] of longint;//线段树注意开4倍空间
procedure build(p,l,r:longint);//建树
var
  mid:longint;
begin
  if (l=r) then begin tree[p]:=a[l]; tree1[p]:=a[l]; exit; end;
  mid:=(l+r) div 2;
  build(p*2,l,mid);
  build(p*2+1,mid+1,r);
  tree[p]:=min(tree[p+p],tree[p+p+1]);
   tree1[p]:=max(tree1[p+p],tree1[p+p+1]);
end;
//我们可以用teee维护区间最小，用tree1维护区间最大
function query(p,l,r,x,y:longint):longint;
var
  mid:longint;
begin
  mid:=(l+r) div 2;
  if (l=x)and(r=y) then exit(tree[p])
  else if y<=mid then exit(query(p*2,l,mid,x,y))
  else if x>=mid+1 then exit(query(p*2+1,mid+1,r,x,y))
  else exit(min(query(p*2,l,mid,x,mid),query(p*2+1,mid+1,r,mid+1,y)));
end;
//线段树求最小值
function query1(p,l,r,x,y:longint):longint;
var
  mid:longint;
begin
  mid:=(l+r) div 2;
  if (l=x)and(r=y) then exit(tree1[p])
  else if y<=mid then exit(query1(p*2,l,mid,x,y))
  else if x>=mid+1 then exit(query1(p*2+1,mid+1,r,x,y))
  else exit(max(query1(p*2,l,mid,x,mid),query1(p*2+1,mid+1,r,mid+1,y)));
end;
//线段树求最大值(可以把求最小值的代码复制下来改一改(逃)
begin
  oo:=100000000;
  readln(n,m);
  for i:=1 to n do readln(a[i]);
  build(1,1,n);//建树
  for i:=1 to m do
  begin
    readln(x,y);
    writeln(query1(1,1,n,x,y)-query(1,1,n,x,y));//求区间最值
  end;
end.
```



---

## 作者：Newuser (赞：7)

看了下大家做法主要:

1.朴素STable O（nlogn)预处理+O（q)询问。

2.线段树O(n)预处理+O(qlogn)询问。

这里提供O（n)预处理+期望O（q)询问的方法。

首先我们分块，块的大小是(log2(n)) （这个块长是有用的），然后一个一个分块。然后我们处理以下的几个数组。

minqianzhui[n] , maxqianzhui[n]，minhouzhui[n] , maxhouzhui[n] 分别是前缀最小值和前缀最大值，后缀最小值和后缀最大值。这里的前缀后缀是针对分块后的数组来说的。也就是对于一个块内的前后缀。

以及fkminn[][] ,fkmaxx[]， 这里是对块与块之间建立朴素ST表RMQ，fkminn[x][0]即对于x块的最小值，fkmaxx[x][2]，即对于[x,x+(1<<2)-1]这几个块里面的最大值。（这里的建立时间复杂度小于O（n））

之后我们就可以了乱搞了！考虑到[l,r]区间，如果l到r之间不是同一个块内，那么我们可以O（1）找出中间块的最大最小值，以及通过后缀l和前缀r找出来。

只有当不是一个块的时候，我们就暴力乱扫吧！由于一个块的长度为logn，所以实际上最差也不会差到qlogn。

数据可能卡你始终一个块？绝不可能。题目数据范围肯定不可能一直出在一个小范围—–不然岂不是暴力都可以过？

所以可以达到期望时间复杂度预处理O（n）+O (q)啦！

这道题数据范围较小看不出来orz orz 

code:
```cpp
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
const int maxn = 50005;
int n,q;
int a[maxn];
int blk,ks;
int fk[maxn];
int minqianzhui[maxn],minhouzhui[maxn],maxqianzhui[maxn],maxhouzhui[maxn];//前缀最大\小值，后缀最大\小值 
int logg[maxn];
int fkminn[maxn][20],fkmaxx[maxn][20];//分块rmq
int main()
{
	scanf("%d%d",&n,&q);
	logg[0]=-1;
	for(int i=1;i<=n;i++) logg[i] = logg[i>>1]+1;//预处理log2 
	blk = logg[n];
	int j=1;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		fk[i] = j;
		if(fk[i]==fk[i-1]) 
		{ 
			minqianzhui[i]=min(minqianzhui[i-1],a[i]);
			maxqianzhui[i]=max(maxqianzhui[i-1],a[i]);
		} 
		else
		{
			minqianzhui[i]=maxqianzhui[i]=a[i];
		}
		if(!(i%blk)) j++;
	}
	if(n%blk) ks=j;
	else ks=j-1;
	for(int i=n;i;i--)
	{
		if(fk[i]==fk[i+1])
		{
			minhouzhui[i]=min(minhouzhui[i+1],a[i]);
			maxhouzhui[i]=max(maxhouzhui[i+1],a[i]);
		}
		else
		{
			minhouzhui[i]=maxhouzhui[i]=a[i];
		}
	}
	for(int i=1;i<=ks;i++)
	{
		fkminn[i][0] = minhouzhui[blk*(i-1)+1];
		fkmaxx[i][0] = maxhouzhui[blk*(i-1)+1];
	}
	for(int j=1;j<=logg[ks];j++)
	{
		for(int i=1;i+(1<<j)-1<=ks;i++)
		{
			fkminn[i][j] = min( fkminn[i][j-1] , fkminn[i+(1<<(j-1))][j-1]  ); //对分块间rmq 
			fkmaxx[i][j] = max( fkmaxx[i][j-1] , fkmaxx[i+(1<<(j-1))][j-1] );
		}
	}
	for(int i=1;i<=q;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int fa = fk[l], fb =fk[r];
		if(fa!=fb)
		{
			fa+=1; fb-=1;
			int mmi=0x3f3f3f3f,mmx=-0x3f3f3f3f;
			if(fa<=fb)
			{
			int k = logg[fb-fa+1];
			mmi = min(fkminn[fa][k],fkminn[fb-(1<<k)+1][k]);
			mmx = max(fkmaxx[fa][k],fkmaxx[fb-(1<<k)+1][k]);
			}
			mmi = min(mmi,min(minhouzhui[l],minqianzhui[r]));
			mmx = max(mmx,max(maxhouzhui[l],maxqianzhui[r]));
			printf("%d\n",mmx-mmi);
		}
		else 
		{
			int mmi = 0x3f3f3f3f,mmx = -0x3f3f3f3f;
			for(int i=l;i<=r;i++) mmi=min(mmi,a[i]),mmx=max(mmx,a[i]);
			printf("%d\n",mmx-mmi);
		}
	} 
}
```
//本蒟蒻博客，欢迎来玩啊：[Newuser小站](http://www.newuser.top/2018/06/03/on%e9%a2%84%e5%a4%84%e7%90%86st%e8%a1%a8rmq%e5%ad%a6%e4%b9%a0/)

---

## 作者：K2sen (赞：6)

## P2880 [USACO07JAN]平衡的阵容Balanced Lineup
[TOC]

### 大体题意
> 给你一个区间，然后让你求得这个区间内最大值和最小值的差.

### 思路：
~~这不就是一个SB线段树维护区间和和区间差嘛，都不用待修改，多简单~~

好我们来看一下线段树维护区间最大值:

很显然啊，如果你会线段树的话很容易就明白了，不会的话[这里](https://www.cnblogs.com/TheRoadToTheGold/p/6254255.html)
```cpp
int query_max(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[rt].max;//如果在区间内，那么直接返回区间最大值
	int mid = (l + r) >> 1, maxn = -1;//因为要取ma所以搞成-1
	if (L <= mid) maxn = max(maxn, query_max(lson, l, mid, L, R));//对两边区间都要取max
	if (R > mid) maxn = max(maxn, query_max(rson, mid + 1, r, L, R));
	return maxn;
}
```

这样的话区间查询最小值就很容易了.

```cpp
int query_min(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[rt].min;
	int mid = (l + r) >> 1, minn = 1e9 + 7;
	if (L <= mid) minn = min(minn, query_min(lson, l, mid, L, R));
	if (R > mid) minn = min(minn, query_min(rson, mid + 1, r, L, R));
	return minn;
}
```
### code 
```cpp
#include <bits/stdc++.h>

#define N 100010
#define M 1010
#define lson rt << 1
#define rson rt << 1 | 1

using namespace std;
int n, q;
struct node {
	int max, min;
}tree[N << 1];

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void push_up(int rt) {
	tree[rt].max = max(tree[lson].max, tree[rson].max);
	tree[rt].min = min(tree[lson].min, tree[rson].min);
}

void build(int rt, int l, int r) {
	if (l == r) {
		tree[rt].max = tree[rt].min = read();
		return;
	}
	int mid = (l + r) >> 1;
	build(lson, l, mid);
	build(rson, mid + 1, r);
	push_up(rt);
}

int query_max(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[rt].max;
	int mid = (l + r) >> 1, maxn = -1;
	if (L <= mid) maxn = max(maxn, query_max(lson, l, mid, L, R));
	if (R > mid) maxn = max(maxn, query_max(rson, mid + 1, r, L, R));
	return maxn;
}

int query_min(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[rt].min;
	int mid = (l + r) >> 1, minn = 1e9 + 7;
	if (L <= mid) minn = min(minn, query_min(lson, l, mid, L, R));
	if (R > mid) minn = min(minn, query_min(rson, mid + 1, r, L, R));
	return minn;
}

int main() {
	n = read(), q = read();
	build(1, 1, n);
	for (int i = 1, x, y; i <= q; i++) {
		x = read(), y = read();
		int ma = query_max(1, 1, n, x, y);
		int mi = query_min(1, 1, n, x, y);
		printf("%d\n", ma - mi);
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：6)

## 瞎扯
刚看到这个题目的时候我就吓着了：蓝题？溜了溜了……但是还是好奇地点进去看了一下。看完题面之后，恕我冒昧说一句话，这题不应该是黄题吗？怎么会是蓝题？简直就是明显（luo）到不能再明显（luo）的RMQ问题。

## 正题
所谓RMQ问题，就是找一个序列某段区间当中，最大或最小的数是多少。而解决它的一种工具就是**ST表**。

我们可以假设$f_{i,j}$为区间$[i,i+2^j-1]$内的最大或最小值。然后把它从中间分开，就可以看到分成了$[i,i+2^{j-1}]$和$[i+2^{j-1},i+2^{j-1}+2^{j-1}-1]\rightarrow[i+2^{j-1},i+2^j-1]$这两个区间。所以，通过DP我们可以得出下面两个方程：

$$f1_{i,j}=\max(f1_{i,j-1},f1_{i+2^j-1,j-1})$$

$$f2_{i,j}=\min(f2_{i,j-1},f2_{i+2^j-1,j-1})$$

其中$f1$数组求的是区间内最大值，$f2$数组求的是区间内最小值。

本题的目标是要求$\max(f1_{x,k},f1_{y-2^k+1,k})-min(f2_{x,k},f2_{y-2^k+1,k})$，虽然区间$[x,x+2^k-1]$和$[y-2^k+1,y]$这两个区间有交集，但并不影响求最值。这就是ST算法的优势。

其他的内容实现就靠大家了，本人的代码仅供参考：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int f1[100007][21], f2[100007][21], n, m, log[100007], x, y;

inline int read() {
	int f = 1, x = 0;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')	f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
void pre() {
	for(int j = 1; j <= 20; ++j)
		for(int i = 1; i + (1 << j) - 1 <= n; ++i)
			f1[i][j] = max(f1[i][j - 1], f1[i + (1 << (j - 1))][j - 1]), f2[i][j] = min(f2[i][j - 1], f2[i + (1 << (j - 1))][j - 1]);
}

int main() {
	log[0] = -1;
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) {
		f1[i][0] =  read();
		f2[i][0] = f1[i][0];
		log[i] = log[i >> 1] + 1;
	}
	pre();
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read();
		int k = log[y - x + 1];
		printf("%d\n", max(f1[x][k], f1[y - (1 << k) + 1][k]) - min(f2[x][k], f2[y - (1 << k) + 1][k]));
	}
	return 0;
}
```

---

## 作者：lokiii (赞：4)

这是一个第一次一遍打下来的代码就ac的蒟蒻特别激动的打出来的题解

因为是一遍过所以啥优化也没加，就是裸的最值线段树，所以时间上比较难看请大佬轻喷。。

思路简单清楚粗暴，就是写一棵最大最小值线段树，然后输出时候取差。。

代码：

#include<iostream> //其实这个线段树没有修改还是挺短的，就是我有花括号分号换行强迫症所以看着细长。。

```cpp
#include<cstdio>
using namespace std;
int n,q,t[50001],x,y;
struct tree
{
    int l,r,mi,ma;//左、右区间、区间最小值、区间最大值 
}a[200001];//我也不知道这个带左右区间的线段树叫啥反正挺好用。。。 
void build(int ro,int l,int r)//建立树 没啥好说的 
{
    a[ro].l=l;//顺便把左右区间的值赋上 
    a[ro].r=r;
    if(l==r)
    {
        a[ro].mi=t[l];
        a[ro].ma=t[l];
    }
    else
    {
        int mid=(l+r)>>1;
        build(ro<<1,l,mid);
        build(ro<<1|1,mid+1,r);
        a[ro].ma=max(a[ro<<1].ma,a[ro<<1|1].ma);
        a[ro].mi=min(a[ro<<1].mi,a[ro<<1|1].mi);
    }
    return;
}
int maxx(int ro,int l,int r)//查询最大值 
{
    if(a[ro].l==l&&a[ro].r==r)
    return a[ro].ma;
    int mid=(a[ro].l+a[ro].r)>>1;
    if(r<=mid)//在左边搜 
    return maxx(ro<<1,l,r);
    else if(l>mid)//在右边搜 
    return maxx(ro<<1|1,l,r);
    else
    return max(maxx(ro<<1,l,mid),maxx(ro<<1|1,mid+1,r));//在两边搜 返回 左右最大值 
}
int minn(int ro,int l,int r)//查询最小值 
{
    if(a[ro].l==l&&a[ro].r==r)
    return a[ro].mi;
    int mid=(a[ro].l+a[ro].r)>>1;
    if(r<=mid)//在左边搜 
    return minn(ro<<1,l,r);
    else if(l>mid)//在右边搜 
    return minn(ro<<1|1,l,r);
    else
    return min(minn(ro<<1,l,mid),minn(ro<<1|1,mid+1,r));//在两边搜 返回 左右最小值 
}
int main()
{
    ios::sync_with_stdio(false);//这个还挺重要的 
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    cin>>t[i];
    build(1,1,n);//建 
    while(q--)
    {
        cin>>x>>y;
        cout<<maxx(1,x,y)-minn(1,x,y)<<endl;//输出最大最小值的差 
    }
    return 0;
}
```

---

## 作者：L_Y_T (赞：3)

### 最近我有点分块中毒了

这道题我是用ST表水过去的

然后我翻了翻题解,发现分块的题解几乎没有~~(仅有的一篇我还看不懂 哭笑.jpg)~~

于是就决定自己来一发

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define maxn 100000
using namespace std ;
int tag_max[maxn] , tag_min[maxn] ;//记录块内最大最小
int n , m , a[maxn] ;
int N , pos[maxn] ;//块数以及块
int l[maxn] , r[maxn] ;//刚从别的地方学到的新技能--偷懒
int query_max(int x , int y ) {//区间求最大值
	int ans = -1000 ;
	if(pos[x] == pos[y]) {
		for(int i = x ; i <= y ; i ++) ans = max(ans , a[i]) ;//暴力
	}else {
		for(int i = x ; i <= r[pos[x]] ; i ++ ) ans = max(ans,a[i]) ;//左边
		for(int i = l[pos[y]] ; i <= y ; i ++) ans = max(ans ,a[i]) ;//右边
		for(int i = pos[x] + 1 ; i <= pos[y] - 1 ; i ++) ans = max(ans,tag_max[i]) ;//中间
	}
	return ans ;
}
int query_min(int x , int y ) {//区间求最小值
	int ans = 0x7ffffff ;
	if(pos[x] == pos[y]) {
		for(int i = x ; i <= y ; i ++) ans = min(ans , a[i]) ;
	}else {
		for(int i = x ; i <= r[pos[x]] ; i ++ ) ans = min(ans,a[i]) ;
		for(int i = l[pos[y]] ; i <= y ; i ++) ans = min(ans ,a[i]) ;
		for(int i = pos[x] + 1 ; i <= pos[y] - 1 ; i ++) ans = min(ans,tag_min[i]) ;
	}
	return ans ;
}
int main() { 
	memset(tag_min,0x3f,sizeof(tag_min)) ;
	memset(tag_max,-1,sizeof(tag_max)) ;
	scanf("%d%d",&n,&m) ;N = sqrt(n) ;
	for(int i = 1 ; i <= n ; i ++) {
		pos[i] = (i-1)/N + 1 ;
	}
	for(int i = 1 ; i <= n ; i ++) l[i] = (i-1) * N + 1 , r[i] = i * N ;
	for(int i = 1 ; i <= n ; i ++) {
		scanf("%d",&a[i]) ;
		tag_max[pos[i]] = max(tag_max[pos[i]],a[i]) ;
		tag_min[pos[i]] = min(tag_min[pos[i]],a[i]) ;
	}
	for(int i = 1 ; i <= m ; i ++) {
		int x , y ;
		scanf("%d%d",&x,&y) ;
		cout << query_max(x,y) - query_min(x,y) << endl ;
	}
	return 0 ;
}
```

暴力分块真神奇!!

完结散花!!!

---

## 作者：封禁用户 (赞：3)

### 我又来发一篇题解啦

其实这一题只是一道板子题，~~但因为我对RMQ又有些不记得了~~

所以发篇题解加深印象

#### 直入正题


核心思想是DP+倍增

不妨我们先来看一个1,2,3,4，……2^n的例子

它的最大值一定是1~2^（n-1）的max与2^（n-1）+1的max的max

这样我们每次算下去就可以很快地得出答案

那么问题来了，如果我们询问的区间不是长度为2^n的呢？

不妨假设它的长度为l，令s=floor(log(l))(以下的log底数为2)

则它的最大值一定是从头取2^s个的这一段区间的max与从尾取2^s个的这一段区间的max（两者会有重叠的部分，不过不影响）

如此，这一题就搞完啦QAQ

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[50001];
int logg[50001];
int f_min[50001][20],f_max[50001][20];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	  cin>>a[i];
	logg[0]=-1;
	for(int i=1;i<=n;i++)
	  f_min[i][0]=a[i],f_max[i][0]=a[i],logg[i]=logg[i>>1]+1;
	for(int j=1;(1<<j)<=n;j++)
	  for(int i=1;i+(1<<j)-1<=n;i++)//循环顺序一定不能变，要先算出长度为2^(j-1)才能算2^j的
	  {
	  	f_min[i][j]=min(f_min[i][j-1],f_min[i+(1<<j-1)][j-1]);
	  	f_max[i][j]=max(f_max[i][j-1],f_max[i+(1<<j-1)][j-1]);
	  }
	for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        int s=logg[y-x+1];
        cout<<max(f_max[x][s],f_max[y-(1<<s)+1][s])-min(f_min[x][s],f_min[y-(1<<s)+1][s])<<endl;
    }
}
```

---

## 作者：chrB (赞：3)

#发一波线段树

##只要维护树的最大值最小值就行了

##标注在程序里

###不知道结构体是干什么的无视就行XD

```cpp
#include<bits/stdc++.h>
typedef long long ll;//把long long用ll代替 
using namespace std;
const int inf = 2000010;//随便取的 
int c[inf];
struct sgt//不懂就无视 
{
    int maxx[inf],minn[inf];
    void push_up(int o,int lson,int rson)//O是编号，lson，rson是当前左右孩子 
    {
        maxx[o]=max(maxx[lson],maxx[rson]);
        minn[o]=min(minn[lson],minn[rson]);
    }
    void build(int o,int l,int r)//O是编号，l，r是当前左右 
    {
        if(l==r)maxx[o]=minn[o]=c[l];
        else
        {
            int mid=(l+r)>>1;
            int lson=o<<1;//就是lson=o*2； 
            int rson=lson|1;//就是rson=lson+1（不代表b=a|1就是b=a+1，不要乱用） 
            build(lson,l,mid);
            build(rson,mid+1,r);
            push_up(o,lson,rson);
        }
    }
    void query(int o,int l,int r,int a,int b,int &mx,int &mn)//O是编号，l，r是当前左右，a，b是所求左右，mx，mn是当前区间最大值和最小值 
    {    
        if(l>=a&&r<=b)
        {
            mx=max(maxx[o],mx),mn=min(minn[o],mn);//维护最大值最小值 
            return;
        }
        int mid=(l+r)>>1;
        int lson=o<<1;
        int rson=lson|1;
        if(a<=mid)query(lson,l,mid,a,b,mx,mn);
        if(b>mid)query(rson,mid+1,r,a,b,mx,mn);
    }
};
sgt tree;
int n,m,f;
int x,y,k;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&c[i]);
    tree.build(1,1,n);//建树 
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        int mx=0,mn=2100000000;
        tree.query(1,1,n,x,y,mx,mn);
        printf("%d\n",mx-mn);     
    }
    return 0;
}
```

---

## 作者：Sor4 (赞：3)

//这题用RMQ比较方便，用线段树会超时。思路和楼下讲的差不多，不过分了几个函数，写起来比较清晰。


【cpp】








    
    
    
    
    
    
    


```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxx = 50000 + 10;
int n,m,x,y;
int Edge[maxx],fmax[maxx][30],fmin[maxx][30];//两个f【i】【j】都是代表从i开始2^j个元素的最大/小值 
void RmaxQ();//处理最大数表 
void RminQ();//处理最小数表 
int Query_min(int l,int r);//找最小数 
int Query_max(int l,int r);//找最大数 
int main()
{
    memset(fmax,0x7f,sizeof(fmax));//记得找最小时数组更新INF 
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&Edge[i]);
    for(int i=1;i<=n;i++)
        fmax[i][0]=Edge[i],fmin[i][0]=Edge[i];
    RmaxQ();
    RminQ();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",Query_max(x,y)-Query_min(x,y));
    } 
    return 0;
}
void RmaxQ()
{
    for(int i=1;(1<<i)<=n;i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            fmax[j][i]=max(fmax[j][i-1],fmax[j+(1<<(i-1))][i-1]);
}
void RminQ()
{
    for(int i=1;(1<<i)<=n;i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            fmin[j][i]=min(fmin[j][i-1],fmin[j+(1<<(i-1))][i-1]);
```
}//这两个函数用倍增的思想预处理，可以在纸上手推，万一不会可以搜RMQ


```cpp
int Query_min(int l,int r)
{
    int k=0;
    while( 1<<(k+1) <= r-l+1 ) k++;
    return min(fmin[l][k],fmin[r-(1<<k)+1][k]);
}
int Query_max(int l,int r)
{
    int k=0;
    while( 1<<(k+1) <= r-l+1 ) k++;
    return max(fmax[l][k],fmax[r-(1<<k)+1][k]);
}//现在查询起来就只要O(1)的复杂度了
```

---

## 作者：Apro1066 (赞：3)

给一个序列，求一段区间最大值和最小值的差。

RMQ问题，一般可以用线段树，树状数组，ST表等求。

树状数组
```cpp
#include <stdio.h>
#include <iostream>
#include <memory.h>
using namespace std;
int n,m,a[50001],maxn[50001],minx[50001],s;
inline int lowbit(int x)
{
	return x&-x;
}
inline void update(int x,int k)//区间[x,n]修改最值 
{
	while(x<=n)
	{
		maxn[x]=max(maxn[x],k);
		minx[x]=min(minx[x],k);
		x+=lowbit(x);
	}
}
inline int query(int l,int r)//区间[l,r]查询最值 
{//对比一下树状数组的查询区间和，其实还是很像的 
	register int mn(2e9+7),mx(-2e9-7);
	while(l<=r)
	{
		while(r-lowbit(r)>=l)//while(r>0)
		{
			mx=max(mx,maxn[r]);
			mn=min(mn,minx[r]);
			r-=lowbit(r);
		}
		mx=max(a[r],mx);
		mn=min(a[r],mn);
		r--;
	}
	return mx-mn;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j;
	memset(minx,2E9+7,sizeof(minx));
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		update(i,a[i]);//单点修改 
	}
	for(i=1;i<=m;i++)
	{
		register int l,r;
		cin>>l>>r;
		cout<<query(l,r)<<endl;//区间查询最值 
	}
	return 0;
}
```
线段树
```cpp
#include <stdio.h>
#include <iostream>
#define ll long long 
#define maxn 50001
using namespace std;
ll int a[maxn],n,s,m,cnt,c,ans;//a是序列
ll int minx[maxn<<2],maxx[maxn<<2];//区间最小值和最大值
inline ll int leftnode(ll int p) {return p<<1;}//左节点（左儿子） 
inline ll int rightnode(ll int p) {return p<<1|1;}//右节点（右儿子） 
inline void push_up(ll int node)//维护父子节点之间的逻辑关系（合并2个儿子节点） 
{
	minx[node]=min(minx[leftnode(node)],minx[rightnode(node)]);//最小值
	maxx[node]=max(maxx[leftnode(node)],maxx[rightnode(node)]);//最大值
}
void build(ll int node,ll int start,ll int end)
{
	if(start==end)
	{
		minx[node]=a[++cnt];//区间最小值
		maxx[node]=a[cnt];//区间最大值
		return; 
	}
	else
	{
		register ll int mid=(start+end)>>1;
		build(leftnode(node),start,mid);
		build(rightnode(node),mid+1,end);
		push_up(node);
	}
}
ll int min_query(ll int node,ll int start,ll int end,ll int cl,ll int cr)//node是当前节点，start和end是范围（是指a数组的范围），L和R是在区间[L,R]里计算和
{//最小值区间查询
	if(start>=cl && end<=cr)//如果修改的区间包括当前遍历的区间 
	{
		return minx[node];//返回这一区间的区间和 
	}
	register ll int mid=(start+end)>>1,s(99999999);
	if(cl<=mid)
	{
		s=min(s,min_query(leftnode(node),start,mid,cl,cr));
	}
	if(mid<cr)
	{
		s=min(s,min_query(rightnode(node),mid+1,end,cl,cr));
	}
	return s;
}
ll int max_query(ll int node,ll int start,ll int end,ll int cl,ll int cr)//node是当前节点，start和end是范围（是指a数组的范围），L和R是在区间[L,R]里计算和
{//最大值区间查询 
	if(start>=cl && end<=cr)//如果修改的区间包括当前遍历的区间 
	{
		return maxx[node];//返回这一区间的区间和 
	}
	register ll int mid=(start+end)>>1,s(-99999999);
	if(cl<=mid)
	{
		s=max(s,max_query(leftnode(node),start,mid,cl,cr));
	}
	if(mid<cr)
	{
		s=max(s,max_query(rightnode(node),mid+1,end,cl,cr));
	}
	return s;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register ll int i;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	build(1,1,n);
	for(i=1;i<=m;i++)
	{
		int l,r;
		cin>>l>>r;
		cout<<max_query(1,1,n,l,r)-min_query(1,1,n,l,r)<<endl;//区间最大值-最小值
	}
	return 0;
}
```
线段树和树状数组的效率其实差别还是比较大的。树状数组跑了大概$800ms$，线段树跑了$1200ms$。

---

## 作者：两年打铁 (赞：3)

# ST表详解

点了最短路的标签出了这题...
好吧一看就知道是用ST表，也想过用线段树，不过显然ST表更优秀。

我就先详讲ST的原理

我们先讲讲ST表是什么。

ST表是利用一种倍增的思想，也算是动态规划？

### 我们用一个二维数组st1 [ i ] [ j ] 表示以i为起点向右$2^j$的区间的最大值，
用一个二维数组st2 [ i ] [ j ]表示以i为起点向右$2^j$的区间的最小值。

那么我们来想怎么转移，对于一个区间像下面这样

### st1 [ i ] [ j ]可以从 i~i+$2^{j-1}$和i+$2^{j-1}$~i+$2^j$转移过来，


st2也是一样的，只不过是取最大最小罢了。

![](https://cdn.luogu.com.cn/upload/pic/52938.png)

------------

讲完了制表，我们来讲讲怎么查询，我们要用到一个炒鸡好用的函数———>$log_2$

对于要查询的区间l,r，有可能（l-r）不是2的幂次，那么我们就需要合并
这样子的两个区间

![](https://cdn.luogu.com.cn/upload/pic/52939.png)

那么我们就直接合并这个红色和绿色的区间，有些~~小天才~~可能会有疑问，
比如，这个重叠部分会有影响，答案是

# 完全没有

因为最大最小值是支持结合律的，那么我们也可以从这里推出ST表的一个性质，

ST表支持结合律的区间查询问题。

接下来就是快乐的代码时间

```
#include<bits/stdc++.h>
#define swap mswap
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)//手写据说常数小（大雾）
using namespace std;
void swap(int &x,int &y)
{
	x^=y^=x^=y;
}
void read(int &x)
{
	x=0;
	char ch=getchar();
	int pd=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			pd=-pd;
		}
		ch=getchar();
	}
	while(ch<='9'&&ch>='0')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=pd;
}
void write(const int &x)
{
	char f[100001];
	int s=0;
	int tmp=x;
	if(tmp==0)
	{
		putchar('0');
		return;
	}
	if(tmp<0)
	{
		tmp=-tmp;
		putchar('-');
	}
	while(tmp>0)
	{
		f[s++]=tmp%10+'0';
		tmp/=10;
	}
	while(s>0)
	{
		putchar(f[--s]);
	}
}
const int N=5e4+10;
int n,m,a[N],st1[N][21],st2[N][21];
int main()
{
	memset(st2,60,sizeof(st2));//最小值注意赋无穷大
	read(n);
	read(m);
	for(register int i=1;i<=n;++i)
	{
		read(a[i]);
		st1[i][0]=st2[i][0]=a[i];
	}
	for(register int j=1;j<=21;++j)
	{
		for(register int i=1;(i+(1<<j-1))<=n;++i)
		{
			st1[i][j]=max(st1[i][j-1],st1[i+(1<<j-1)][j-1]);st1记录区间最大值
			st2[i][j]=min(st2[i][j-1],st2[i+(1<<j-1)][j-1]);st2最小值
		}
	}
	for(register int i=1;i<=m;++i)
	{
		int l,r;
		read(l);
		read(r);
		int k=log2(r-l+1);//+1防止RE？（雾）
		write(max(st1[l][k],st1[r-(1<<k)+1][k])-min(st2[l][k],st2[r-(1<<k)+1][k]));;
		puts("");
	}
}
```


---

## 作者：Leelzh (赞：3)

Halo ，又带来一组较为简单识别的代码，比较适合像我这样的**蒟蒻**阅读

想法很简单，就是st表，初始一个max的和一个min的st表，然后RMQ一个max的一个min的就可以了；

    
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int a[50001],f_max[50002][21],f_min[50002][21],n,m;
void ST_max()
{
    int k=log(n)/log(2);
    for(int i=1;i<=n;i++)
        f_max[i][0]=a[i];//初始化
    for(int j=1;j<=k;j++)
        for(int i=1;(i+(1<<j)-1)<=n;i++) 
             f_max[i][j]=max(f_max[i][j-1],f_max[i+(1<<(j-1))][j-1]);
} 
int RMQ_max(int L,int R)
{
    int k=log(R-L+1)/log(2);//初始化k
    return max(f_max[L][k],f_max[R-(1<<k)+1][k]); //区间最大值
}
void ST_min()
{
    int k=log(n)/log(2);
    for(int i=1;i<=n;i++)
        f_min[i][0]=a[i];//同上
    for(int j=1;j<=k;j++)
        for(int i=1;(i+(1<<j)-1)<=n;i++) 
             f_min[i][j]=min(f_min[i][j-1],f_min[i+(1<<(j-1))][j-1]);
} 
int RMQ_min(int L,int R)//区间最小值
{
    int k=log(R-L+1)/log(2);
    return min(f_min[L][k],f_min[R-(1<<k)+1][k]); 
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    ST_max();
    ST_min();
    for(int i=1;i<=m;i++)
        {
            int x,y;
            cin>>x>>y;
            cout<<RMQ_max(x,y)-RMQ_min(x,y)<<endl;//随着读入随着输出
        }
    return 0;
}
```

---

## 作者：wycissilly (赞：3)

这里是用ST算法实现的RMQ。


RMQ其实就是区间最值。

RMQ利用了二分（或者说倍增）的思想，进行dp。

预处理O（nlogn）,与线段树比较的优点是查询O(1)，查询的思想即是用两个2^n的区间覆盖这个大区间。

顺带一提，RMQ还能用于实现离线LCA。


``` javascript
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int Min[50001][17],Max[50001][17],n,q;
void RMQ(){
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
            Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
        }
    }
}
int main(){
    while(~scanf("%d%d",&n,&q)){
        memset(Min,0,sizeof(Min));
        memset(Max,0,sizeof(Max));
        for(int i=1;i<=n;i++){
            scanf("%d",&Min[i][0]);
            Max[i][0]=Min[i][0];
        }
        RMQ();
        for(int i=1;i<=q;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            int k=log(y-x+1)/log(2);
            printf("%d\n",max(Max[x][k],Max[y-(1<<k)+1][k])-min(Min[x][k],Min[y-(1<<k)+1][k]));
        }
    }
}
```

---

## 作者：追梦_Chen (赞：3)

#### **根据题意，我们要求每个询问中，最大与最小的牛的高度差，而每个询问又是一个区间，于是乎我们可以联想到这是一道求区间最值的问题**
#### # 我们便可以使用ST算法，求出ST表，利用ST表来表达某个区间的极大或者极小值，嗯！没错！ST表就是表示某个区间极值的东东！其核心思想便是倍增，不会的小伙伴可以看李煜东大犇写的《算法竞赛进阶指南》的第38面，或者点击下面的链接：
[ST表算法详解](https://blog.csdn.net/Hanks_o/article/details/77547380)

# ST表真是个好东西！！！！！
### 好啦放代码：
```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;
long long st_max[50000][21],st_min[50000][21],a[50005];
int n,q;
void ST(){
	for(int i=1;i<=n;i++){
		st_max[i][0]=a[i];
		st_min[i][0]=a[i];
	}
	int t=log(n)/log(2)+1;
	for(int j=1;j<t;j++){
		for(int i=1;i<=n-(1<<j)+1;i++){
			st_max[i][j]=max(st_max[i][j-1],st_max[i+(1<<(j-1))][j-1]);
			st_min[i][j]=min(st_min[i][j-1],st_min[i+(1<<(j-1))][j-1]);
		}
	} 
}//核心代码，求ST表 
int st_maxn(int l,int r){
	int k=log(r-l+1)/log(2);
	return max(st_max[l][k],st_max[r-(1<<k)+1][k]);
}
int st_minn(int l,int r){
	int k=log(r-l+1)/log(2);
	return min(st_min[l][k],st_min[r-(1<<k)+1][k]);
}
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
	ST();
	for(int i=1;i<=q;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		if(x>y)	swap(x,y);
		printf("%d",st_maxn(x,y)-st_minn(x,y));
	}
		
	return 0;
}

```

---

## 作者：C20212724杨京朝 (赞：2)

区间最值维护：话说这题用st表貌似又快又方便（ ~~然而我不会~~）

#### 只好来一发线段树
对线段树不熟悉的同学可以看下这篇博客:[线段树详解](https://2016gdgzoi316.blog.luogu.org/post-chi-xu-geng-xin-xian-duan-shu-yang-xie-zong-ru-men-dao-ge-zhon)

以下附板子：[P3372 【模板】线段树 1](https://www.luogu.org/problem/P3372)
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
#define LL long long
long long a[MAXN],tag[MAXN * 4],tree[MAXN * 4],cnt;
void push_up(LL now) {
	tree[now] = tree[now * 2] + tree[now * 2 + 1];
} 
void build(LL now,LL l,LL r) {
	if(l == r) {
		cnt ++;
		tree[now] = a[cnt];
	}
	else {
		LL mid = (l + r) / 2;
		build(now * 2,l,mid);
		build(now * 2 + 1,mid + 1,r);
		push_up(now);
	}
}
void push_down(LL now,LL l,LL r) {
	LL mid = (l + r) / 2;
	tree[now * 2] += (mid - l + 1) * tag[now];
	tree[now * 2 + 1] += (r - mid) * tag[now];
	tag[now * 2] += tag[now];
	tag[now * 2 + 1] += tag[now];
	tag[now] = 0; 
	push_up(now);
}
void update(LL now,LL l,LL r,LL x,LL y,LL t) {
	if(x <= l && y >= r) {
		tree[now] += (r - l + 1) * t;
		tag[now] += t;
	}
	else {
		push_down(now,l,r);
		LL mid = (l + r) / 2;
		if(x <= mid) update(now * 2,l,mid,x,y,t);
		if(y > mid) update(now * 2 + 1,mid + 1,r,x,y,t);
		push_up(now);
	}
} 
LL look_up(LL now,LL l,LL r,LL x,LL y) {
	LL ans = 0;
	if(x <= l && y >= r) {
		ans += tree[now];
	}
	else {
		push_down(now,l,r);
		LL mid = (l + r) / 2;
		if(x <= mid) ans += look_up(now * 2,l,mid,x,y);
		if(y > mid) ans += look_up(now * 2 + 1,mid + 1,r,x,y);
	}
	return ans;
}
int main() {
	LL n,m;
	scanf("%lld %lld",&n,&m);
	for(LL i = 1;i <= n;i ++) scanf("%lld",&a[i]);
	build(1,1,n);
	for(LL i = 1;i <= m;i ++) {
		LL num;
		scanf("%lld",&num);
		if(num == 1) {
			LL x,y,k;
			scanf("%lld %lld %lld",&x,&y,&k);
			update(1,1,n,x,y,k);
		}
		else {
			LL x,y;
			scanf("%lld %lld",&x,&y);
			printf("%lld\n",look_up(1,1,n,x,y));
		}
	}
	return 0;
}
```
------------
思路：这个题可以说就是最简单的线段树，也不需要懒标记什么的，开两个数组维护即可.
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
int a[MAXN],tree_min[MAXN * 4],tree_max[MAXN * 4],cnt;//线段树所需的数组开四倍
void push_up(int now) {//维护两个数组，一个最大，一个最小
	tree_min[now] = min(tree_min[now * 2],tree_min[now * 2 + 1]);
	tree_max[now] = max(tree_max[now * 2],tree_max[now * 2 + 1]);
}
void build(int now,int l,int r) {//建树
	if(l == r) {
		cnt ++;
		tree_min[now] =	tree_max[now] = a[cnt];
	}
	else {
		int mid = (l + r) >> 1;
		build(now * 2,l,mid);
		build(now * 2 + 1,mid + 1,r);
		push_up(now);
	}
}
int look_up(int now,int l,int r,int x,int y,int &Max,int &Min) {
	if(x <= l && y >= r) {//注意每次查询维护两个值
		Max = max(Max,tree_max[now]);
		Min = min(Min,tree_min[now]);
	}
	else {
		int mid = (l + r) >> 1;
		if(x <= mid) look_up(now * 2,l,mid,x,y,Max,Min);
		if(y > mid) look_up(now * 2 + 1,mid + 1,r,x,y,Max,Min);
	}
}
int main() {
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
	build(1,1,n);
	for(int i = 1;i <= m;i ++) {
		int x,y;
		scanf("%d %d",&x,&y);
		int Min = 1000005,Max = 0;//对Min定义一个极大值，Max反之
		look_up(1,1,n,x,y,Max,Min);
		printf("%d\n",Max - Min);//极值相减
	}
	return 0;
}
```
------------
## 谢谢围观






---

## 作者：Protons (赞：2)

这个题，简直就是线段树模板

我们用线段树的记录每个区间的最大和最小值，在查询的时候调用出最大最小值再相减即可

以下是代码：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,m,a[50010],mx,mi=1000005;
int minn[200010],maxx[200010];
void build(int k,int l,int r)//建树
{
	if(l==r){minn[k]=a[l];maxx[k]=a[l];return;}//每个节点储存两个信息——区间最大值和区间最小值
	int mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	minn[k]=min(minn[k<<1],minn[k<<1|1]);//别忘了更新
	maxx[k]=max(maxx[k<<1],maxx[k<<1|1]);
}
void query(int k,int l,int r,int x,int y)//查询
{
	if(l>=x&&r<=y)
	{
		mx=max(mx,maxx[k]);//查询时直接同时修改两个全局变量即可
		mi=min(mi,minn[k]);
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)query(k<<1,l,mid,x,y);
	if(y>mid)query(k<<1|1,mid+1,r,x,y);
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	build(1,1,n);
	int u,v;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		query(1,1,n,u,v);
		printf("%d\n",mx-mi);
		mx=0;mi=1000005;//别忘了重新赋值，否则可能会WA
	}
	return 0;
}
```

---

## 作者：Big_old (赞：2)

# ↓EASY一点点的做法(分块)↓
####  本蒟蒻的第一篇题解，可能写的不太好，凑活着看吧。。。

------------
##### 代码有点长，看起来也有一些恶心，不过只要会了写起来就十分简单。

#### 分块的思想： 
		
#### 将序列a分成sqrt(n)或sqrt(n)+1份，因此每份的最长长度为sqrt(n)将每块中的一些量(和、最大值、最小值、乘积)等预处理出来(打上区间标记)，在查找一段区间内的这些量时，将该区间不全在块内的部分一个个枚举处理(最多2sqrt(n)次)，全在块内的部分用区间标记处理。代码里有注释，结合着理解一下吧。。。

注：时间复杂度O(n) = qsqrt(n)相对线段树的要多一点，一些数据大的题可能会T掉

```cpp
#include<bits/stdc++.h>
using namespace std;

int lft[100001],rit[100001];
//left好像是关键词(ono气)所以就把lft写成了lft，right写成rit
int a[1000001],ma[10001],mi[100001],b[100001];
int n,q,tot,len,l,r,ansma,ansmi;

inline int read() {//快读
	int x = 0 , f = 1;
	char c = getchar();
	while( c < '0' || c > '9' ) {
		if( c == '-' )f = -1;
		c = getchar();
	}
	while( c >='0' && c <='9' ) {
		x = ( x << 3 ) + ( x << 1 ) + c - '0';
		c = getchar();
	}
	return x * f;
}
inline int mma( int x , int y ) { return x > y ? x : y; }
inline int mmi( int x , int y ) { return x < y ? x : y; }

int main() {
	
	n = read(),q = read();
	
	int len = sqrt(n);//分成的每个块长度为len 
	int tot = n / len;//一共分成tot个块 
	if( n%len )tot++; //如果末尾元素未被加入块里，块数++
	
	for( int i = 1 ; i <= tot ; ++i )mi[i] = 2147483647;
	for( int i = 1 ; i <= n ; ++i ) {
		a[i] = read();
		b[i] = ( i - 1 ) / len + 1;	   //第i个元素所在的块为b[i]
		ma[b[i]] = mma( ma[b[i]] , a[i] );//记录第b[i]块中的max
		mi[b[i]] = mmi( mi[b[i]] , a[i] );//记录第b[i]块中的min
	}
	for( int i = 1 ; i <= tot ; ++i ) {//预处理出第i块的左、右端点
		lft[i] = ( i - 1 ) * len + 1;
		rit[i] = i * len;
	}
	
	for( int i = 1 ; i <= q ; ++i ) {
		l = read(),r = read();
		ansma = 0,ansmi = 2147483647;//分别记录l-r区间的最大、最小值
		
		for( int i = l ; i <= mmi( r , rit[b[l]] ) ; ++i ) {
        							 //暴力处理左端不全在块内的值
			ansma = mma( ansma , a[i] );
			ansmi = mmi( ansmi , a[i] );
		}
		if( b[l] != b[r] ) {		 //如果l、r不在同一块中 
			for( int i = r ; i >= lft[b[r]] ; --i ) {		
            						 //暴力处理右端不全在块内的值
				ansma = mma( ansma , a[i] );
				ansmi = mmi( ansmi , a[i] );
			}
			for( int i = b[l] + 1 ; i <= b[r] - 1 ; ++i ) {
            						 //处理左右端点所在块中间的块
				ansma = mma( ansma , ma[i] );
				ansmi = mmi( ansmi , mi[i] );
			}
		}
		
		printf("%lld\n",(ansma - ansmi));
	}
	
	return 0;
}
```
感谢收听(～o￣3￣)～

---

## 作者：江南小巫 (赞：2)

		此题我见有人使用了结构体，在此我想发一个一位数组的解法。
    
    	首先，读入数据，利用数据构造最大值和最小值两个树状数组，之后呢
	读入所需要操作的区间，直接在两个树状数组中查询就可以了，最后输出身高
    差。
    
    	在此代码中，我用了较多的inline函数和位运算，没有使用头文件中自
	带的函数，都是为了提高代码运行速度，降低时间复杂度。
    
    	(位运算解释:<<1是变成原来的2倍,>>1是除以2,<<1|1是乘2加1)

```c
#include<bits/stdc++.h>
using namespace std;
const int N=50001;

inline int min(int p,int q){//手写最大值函数 
	if (p<q)return p;
	return q;
}

inline int max(int p,int q){//手写最小值函数 
	if (p>q)return  p;
	return q;
}

inline int read(){//快速读入 
    int k=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0')
        if(c=='-'){
            f=-1;
            c=getchar();
        }
    while(c<='9'&&c>='0'){
        k=k*10+c-'0';
        c=getchar();
    }
    return k*f;
}

inline void write (int x){//快速输出(无聊用,没有太大的实际作用) 
	if (x < 10) {
		putchar (x + '0');
		return ;
	}
	write (x / 10);
	putchar (x % 10 + '0');
	return ;
}

int n,t,a[N],MAX[N<<2],MIN[N<<2],x,y;

int makemax (int v,int i,int j){//维护最大值数组,选择左孩子和右孩子中较大的结点
	if (i==j)return MAX[v]=a[i];
	int mid = i + j >> 1;
	return MAX[v]=max(makemax(v<<1,i,mid),makemax(v<<1|1,mid+1,j));
}

int makemin (int v, int i, int j){//维护最小值数组,选择左孩子和右孩子中较小的结点
	if(i==j)return MIN[v]=a[i];
	int mid=i+j>>1;
	return MIN[v]=min(makemin(v<<1,i,mid),makemin(v<<1|1,mid+1,j));
}

int findmax (int v, int i, int j){//查询区间中的最大值
	if(i>y || j<x)return 0;
	if (i>=x && j<=y)return MAX[v];
	int mid=i+j>>1;
	return max(findmax(v<<1,i,mid),findmax(v<<1|1,mid+1,j));
}

int findmin(int v, int i, int j) {//查询区间中的最小值 
	if(i>y || j<x)return (1<<30);
	if(i>=x && j<=y)return MIN[v];
	int mid=i+j>>1;
	return min(findmin(v<<1,i,mid),findmin(v<<1|1,mid+1,j));
}

int main(){
	int i;
	n=read(),t=read();
	for(i= 1;i<=n;i++)a[i]=read();
	x=makemax(1,1,n);
	x=makemin(1,1,n);
	while(t--){
		x=read(),y=read();
		int a=findmax(1,1,n);//寻找最高牛的身高 
		int b=findmin(1,1,n);//寻找最矮牛的身高 
		write(a-b);//输出最大身高差 
	}
	return 0;
}
```

---

## 作者：Shirο (赞：1)

```
st表模板
真的这题是怎么蓝的
st表就是一个区间求rmq的工具
主要原理是将数列分成(1<<(k))的块
预处理建表然后O1查询
如果查询大，st表无论在时间或者空间是远优于线段树的

```
```cpp
#include<cstdio>
#include<cstring>
#define min(a,b) a>b?b:a
#define max(a,b) a>b?a:b
using namespace std;
const int maxn=5e5+5,LOG=20;
int log(int x){int ans=-1;for(;x;x>>=1)ans++;return ans;}
int a[maxn];
struct ST_table//把st表装成结构体
{
	int f[maxn][LOG],n,usage;//usage是来控制最小值和最大值的
	void usage_select(int n){usage=n;}//更新usage
	void init()
	{
		for(int i=1;i<=n;i++)f[i][0]=a[i];//很容易的初始化，每个数的后一个之内极值一定是其本身
		for(int j=1;(1<<j)<=n;j++)
		{
			for(int i=1;i<=n;i++)
			{
				if(usage==1)f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
				else if(usage==0)f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
                //把序列拆成两半更新极值
			}
		}
	}
	int find(int l,int r)
	{
		if(r<l){int k=l;l=r;r=k;}
		int k=log(r-l+1);
		if(usage==1)return min(f[l][k],f[r-(1<<k)+1][k]);
		else if(usage==0)return max(f[l][k],f[r-(1<<k)+1][k]);
	}
}min_table,max_table; 
int main()
{
	min_table.usage_select(1);
	max_table.usage_select(0);
	int N,Q;scanf("%d%d",&N,&Q);min_table.n=max_table.n=N;
	for(int i=1;i<=N;i++)scanf("%d",&a[i]);
	min_table.init();max_table.init();
	for(int i=1;i<=Q;i++)
	{
		int L,R;scanf("%d%d",&L,&R);
		printf("%d\n",max_table.find(L,R)-min_table.find(L,R));
	}
}
```


---

## 作者：7wwwwth (赞：1)

rmq就是在一个区间里找最小值或最大值 用st的做法

理解一下rmq的原理：假设我们要查询的这个数值在区间a[i]中，那么我们用f[i][j]来表示这个数；具体含义是这样的：f[i][j]表示 从i开始的2^j个数中的最大值 那么就可以确定a[i]=f[i][0]；

那么对于一个2^j的数列我们可以把他平均分成两段 每段的长度为2^j-1;第一段是i到i+2^j-1 -1;第二段是i+2^j-1到i+2^j-1；

可以分别表示为：f[i][j-1]  f[i+2^j-1][j-1]

则设有2^k=j-i+1(即一个从i到j的区间的长度）那么有rmq（i，j）=max（f[i][k],f[j-2^k+1][k]);(区间最大值 最小值同理




```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,q,s,e,maxn,minn;
int f1[200001][51],f2[200001][51],a[200001];

int rmq(int i,int j){
	int k=0;
	while((1<<(k+1))+i<=j+1) k++;//仔细想一想很好理解
	minn=min(f2[i][k],f2[j-(1<<k)+1][k]);//区间最小值
	maxn=max(f1[i][k],f1[j-(1<<k)+1][k]);//区间最大值
	return maxn-minn;//返回两数值的差
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		f1[i][0]=f2[i][0]=a[i];
	}
	for(int j=1;(1<<j)<=n;j++)
	for(int i=1;i+(1<<j)<=n+1;i++){
		f1[i][j]=max(f1[i][j-1],f1[(1<<(j-1))+i][j-1]);
		f2[i][j]=min(f2[i][j-1],f2[(1<<(j-1))+i][j-1]);
	}
	for(int i=1;i<=q;i++){
		scanf("%d%d",&s,&e);
		cout<<rmq(s,e)<<endl;
	} 
	return 0;
}
```

---

## 作者：qscqesze_lca (赞：1)

\_RMQ是DP+二分的思想\_

\_f[i][j]表示第i个数到2的j次方-1的区间最值\_

\_空间复杂度（2\*Nlog2N+N）\_

\_时间复杂度（2\*Nlog2N+Q）\_

\_代码如下\_

/\*
在家自学了一下rmq =。= 线段树似乎会超时 思路上还是非常的清晰的 希望大家有时间可以去博客看看rmq的解法 比线段树简单多啦！

\*/
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n;
int m;
int s;
int e;
int mini;
int maxn;
int a1[100001][20];//min
int a2[100001][20];//max
int b[1000001];
void init(){
    for(int i=1;i<=n;i++){
        a1[i][0]=a2[i][0]=b[i];
    }
    for(int j=1;j<=20;j++){
        for(int i=1;i+(1<<j)<=n+1;i++){
            a1[i][j]=min(a1[i][j-1],a1[i+(1<<(j-1))][j-1]);//小 
            a2[i][j]=max(a2[i][j-1],a2[i+(1<<(j-1))][j-1]);//大 
        }
    }
}
int RMQ_MIN(int x,int y){//xiao
    int k=0;
    while((1<<(k+1))<=y-x+1){
        k++;
    }
    return min(a1[x][k],a1[y-(1<<k)+1][k]);//核心
} 
int RMQ_MAX(int x,int y){//da
    int k=0;
    while((1<<(k+1))<=y-x+1){
        k++;
    }
    return max(a2[x][k],a2[y-(1<<k)+1][k]);核心
}
int main(){
    cin>>n>>m;//输入
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    init();
    for(int i=1;i<=m;i++){
        cin>>s>>e;
        mini=RMQ_MIN(s,e);//最小
        maxn=RMQ_MAX(s,e);//最大
        cout<<maxn-mini<<endl;//输出
    }
}
到此结束 记得不懂私信哦！
```

---

## 作者：DDOSvoid (赞：1)

水一发zkw线段树

```cpp
#include<iostream>
#include<cstdio>
#define maxn 50010
#define lc i<<1
#define rc i<<1|1
using namespace std;
inline void read(int& x){
    x=0;int flag=1;char c=getchar();
    while(c<'0' || c>'9'){
        if(c=='-')flag=-1;
        c=getchar();
    }
    while(c>='0' && c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    x*=flag;
}
int n,m,dep=1,x,y;
struct node{
    int min1,max1;
}tree[maxn<<2];
void build(){
    while(dep<n)dep<<=1;
    for(int i=dep;i<dep+n;i++){//直接赋到叶子节点上 
        read(tree[i].min1);
        tree[i].max1=tree[i].min1;
    }
    for(int i=dep-1;i;i--){
        tree[i].min1=min(tree[lc].min1,tree[rc].min1);//自底向上维护 
        tree[i].max1=max(tree[lc].max1,tree[rc].max1);
    }
}
inline int query_min(int l,int r){
    int res;
    l+=dep-1;r+=dep-1;//变到叶子节点上 
    res=min(tree[l].min1,tree[r].min1);
    if(l==r)return res;
    for(;l^r^1;l>>=1,r>>=1){
        if(~l&1)res=min(res,tree[l^1].min1);// ~l&1 -> l%2==0
        if(r&1)res=min(res,tree[r^1].min1);// r&1 -> r%2!=0
        //对于左端点，如果该点的序号能被2整除，也就是说它是左儿子，那么它
        //的兄弟(也就是它的右边)一定在包含的区间内，
        //同样，对于右端点，如果他是右儿子，那么它的兄弟一定包含在区间内 
    }
    return res;
}
inline int query_max(int l,int r){
    int res;
    l+=dep-1;r+=dep-1;
    res=max(tree[l].max1,tree[r].max1);
    if(l==r)return res;
    for(;l^r^1;l>>=1,r>>=1){
        if(~l&1)res=max(res,tree[l^1].max1);
        if(r&1)res=max(res,tree[r^1].max1);
    }
    return res;
}
int main(){
    read(n);read(m);
    build();
    for(int i=1;i<=m;i++){
        read(x);read(y);
        printf("%d\n",query_max(x,y)-query_min(x,y));
    }
    return 0;
}
```

---

## 作者：Log_x (赞：1)

刚学分块，来发一波分块题解。

因为最值都可以直接暴力合并，分块写起来也很简便，预处理部分只要O(n)的复杂度，而询问只是拆成几个块暴力合并。

而神奇的是，分块询问O(m \* 根号n)的瓶颈复杂度竟然跑得炒鸡快。

代码：

// mex[i][j] / mix[i][j] 分别表示块i ~ 块j的最大/最小值








```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int Maxn = 0x3f3f3f3f;
const int N = 5e4 + 5, M = 255;
int a[N], bl[M], br[M], mex[M][M], mix[M][M];
int n, Q, S, s;
template <class T> inline T Max(const T a, const T b) {return a > b? a : b;}
template <class T> inline T Min(const T a, const T b) {return a < b? a : b;}
template <class T> inline void CkMax(T &a, const T b) {if (a < b) a = b;}
template <class T> inline void CkMin(T &a, const T b) {if (a > b) a = b;}
template <class T> inline void Swap(T &a, T &b) {a ^= b; b ^= a; a ^= b;}
inline int get()
{
    char ch; bool f = false; int res = 0;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');
    if (ch == '-') f = true;
     else res = ch - '0';
    while ((ch = getchar()) >='0' && ch <= '9')
        res = (res << 3) + (res << 1) + ch - '0';
    return f? ~res + 1 : res;
}
inline void put(int x)
{
    if (x < 0)
      x = ~x + 1, putchar('-');
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
inline void Init()
{
    memset(mex, -Maxn, sizeof(mex));
    memset(mix, Maxn, sizeof(mix));
    for (int i = 1; i <= s; ++i)
     for (int j = bl[i]; j <= br[i]; ++j)
      CkMax(mex[i][i], a[j]), CkMin(mix[i][i], a[j]);
    for (int i = 1; i < s; ++i)
     for (int j = i + 1; j <= s; ++j)
      CkMax(mex[i][j], Max(mex[i][j - 1], mex[j][j])),
      CkMin(mix[i][j], Min(mix[i][j - 1], mix[j][j]));
}
inline int Que(const int l, const int r)
{
    int L = (l - 1) / S + 1, R = (r - 1) / S + 1, Ma = -Maxn, Mi = Maxn;
    if (r - l < (S << 1)) // 注意特判没有完整的块的情况 
    {
        for (int i = l; i <= r; ++i)
         CkMax(Ma, a[i]), CkMin(Mi, a[i]);
        return Ma - Mi;
    }    
    if (l == bl[L]) L--;
    if (r == br[R]) R++;
    // 如果[l,r]刚好都在完整的块，这样就能直接返回块中信息，无需暴力处理，节省时间效率
    Ma = mex[L + 1][R - 1]; Mi = mix[L + 1][R - 1];
    int ed = br[L], st = bl[R];
    for (int i = l; i <= ed; ++i) CkMax(Ma, a[i]), CkMin(Mi, a[i]);
    for (int i = st; i <= r; ++i) CkMax(Ma, a[i]), CkMin(Mi, a[i]);
    return Ma - Mi;
}
int main()
{
    while (scanf("%d%d", &n, &Q) != EOF)
    {
        S = sqrt(n); s = 0;
        for (int i = 1; i <= n; ++i) a[i] = get();
        for (int i = 1; i <= n; ++i)
         if (i % S == 1) br[s] = i - 1, bl[++s] = i;
        br[s] = n; bl[s + 1] = br[s + 1] = n + 1;
        Init(); int x, y;
        while (Q--)
        {
            x = get(); y = get();
            put(Que(x, y)), putchar('\n');
        }
    }
    return 0;
}

```

---

## 作者：zqy1018 (赞：1)

ST表模板题...

线段树估计会挂，因为询问太多了。

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int f1[16][50005],dat[50005],f2[16][50005],N,Q; 
int max(int a,int b){return (a>b)?a:b;}
int min(int a,int b){return (a<b)?a:b;}
void sttable(int n){
    int i,j,p;
    memcpy(f1[0],dat,sizeof(dat));
    memcpy(f2[0],dat,sizeof(dat));
    for(i=1;(1<<i)<=n;i++)
        for(j=0,p=(1<<(i-1));j<n-p;j++)
            f1[i][j]=max(f1[i-1][j],f1[i-1][j+p]),
            f2[i][j]=min(f2[i-1][j],f2[i-1][j+p]);//同时对最大最小两个st表初始化，递推
}int rmq(int l,int r){
    int k=0;while((1<<(k+1))<(r-l+1))k++;
    return max(f1[k][l],f1[k][r-(1<<k)+1])-min(f2[k][l],f2[k][r-(1<<k)+1]);//询问部分
}int main(){
    scanf("%d%d",&N,&Q);
    int i,l,r;
    for(i=0;i<N;i++)
        scanf("%d",&dat[i]);
    sttable(N);
    for(i=0;i<Q;i++)
        scanf("%d%d",&l,&r),
        printf("%d\n",rmq(l-1,r-1));
    return 0;
}  
```

---

