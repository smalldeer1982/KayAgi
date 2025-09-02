# 『MdOI R1』Group

## 题目背景

此题为比赛时的数据。

然鹅后来yummy觉得没这个必要，于是放弃加强。

**存在不使用`long double`和`__int128`的写法。**

## 题目描述

为了让我们团队的同学更加团结，我们需要让各个成员的水平尽量平均。这时，就需要有人对自己产生一些改变。

我们的团队有 $n$ 个同学，第 $i$ 个同学的水平值是一个整数 $a_i$。

我们认为当整组同学水平值的 **方差** **不超过 $m$** 的时候，这组同学就是团结的。  

请问至少要让几个同学改变自己的水平值（可以改成任意一个 **实数**），这个团队才可以做到团结？

为避免读入时的精度误差，本题输入的 $m$ 是 **实际值的 $n$ 倍**，这个值是一个整数。

---

如果你不知道什么叫做方差，以下是方差的基本概念：

方差是衡量一组数据 **波动程度** 的指标。

设长度为 $n$ 的序列 $a_{1\dots n}$ 的平均数为 $p$，则该序列的方差 $S$ 为：

$$
S=\frac{1}{n} \sum_{i=1}^n(a_i-p)^2
$$

## 说明/提示

【样例 1 解释】   

这组样例中，$n=4$，真实的 $m=\dfrac{32}{n}=8$。

一开始，所有同学水平值 $a_i$ 的平均数为 $1$，方差为：

$$S=\dfrac{1}{4}[(3-1)^2+(7-1)^2+(-5-1)^2+(-1-1)^2]=20$$

把第 $3$ 个同学的水平值改成 $3$ 后，平均数为 $3$，方差为：

$$S=\dfrac{1}{4}[(3-3)^2+(7-3)^2+(3-3)^2+(-1-3)^2]=8$$

只改变了 $1$ 人的水平值，即满足了题目要求。

【样例 2 解释】

这组样例中，$n=5$，真实的 $m=\dfrac{18}{n}=3.6$。

一开始，所有同学水平值 $a_i$ 的平均数为 $4.6$，方差为 $7.44$：

把第 $5$ 个同学的水平值改成 $3.5$ 后，平均数为 $3.5$，**方差为 $2.6$。**

只改变了 $1$ 人的水平值，即满足了题目要求。

---

【数据范围】   

|子任务编号|$n\leq$|分值|
|:-:|:-:|:-:|
|1|$16$|15|
|2|$300$|17|
|3|$10^3$|20|
|4|$5\times 10^3$|7|
|5|$10^4$|8|
|6|$2\times 10^5$|33|

对于所有测试点，$1\leq n\leq 2\times 10^5$，$1\leq m\leq 10^{18}$，$0\leq |a_i|\leq 10^6$。

## 样例 #1

### 输入

```
4 32
3 7 -5 -1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 18
1 4 3 6 9
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 679
5 83 56 20 54 111
```

### 输出

```
3
```

# 题解

## 作者：liangbowen (赞：19)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/P6069)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16745402.html)

恶心的二分答案。（以前觉得很难，现在看来也还好？毕竟是黄题。）

## 思路

首先，很容易想到二分答案：$\operatorname{chk(x)}$ 表示去掉 $x$ 个数是否能成立。那么 $\operatorname{chk(x)}$ 很显然具有单调性。

为了方便叙述，设和为 $\texttt{sum}$，平方和为 $\texttt{sqsum}$。

$\because S=\dfrac{1}{n} \sum\limits_{i=1}^n(a_i-p)^2$

$\therefore S = \dfrac{1}{n} \cdot \texttt{sqsum} - \dfrac{\texttt{sum}^2}{n^2}$

$\therefore S = \dfrac{1}{n} \cdot (\texttt{sqsum} - \dfrac{\texttt{sum}^2}{n})$

又因为我们需要 $S \le \dfrac{m}{n}$：

$\therefore \dfrac{1}{n} \cdot (\texttt{sqsum} - \dfrac{\texttt{sum}^2}{n}) \le \dfrac{m}{n}$

$\therefore \texttt{sqsum} - \dfrac{\texttt{sum}^2}{n} \le m$

$\therefore (n \cdot \texttt{sqsum} - \texttt{sum}^2) \le n\cdot m$

推这一大坨公式有什么用呢？很容易想到，要修改就修改到**计算答案时没有影响**，也就是可以理解为：直接去掉这个数。

还有一个很重要的结论：**剩下的数最好是连续的**。

感性理解，方差是衡量一组数据**波动程度**的指标。所以数据越接近，方差就越小。

那么有了以上的理论支持后，这道题就很水了。

预处理前缀和以及前缀平方和，然后二分，时间复杂度 $O(\log n)$。

$\operatorname{chk(x)}$ 枚举连续的区间即可，时间复杂度 $O(n)$。

所以，总时间复杂度显然就是 $O(n \log n)$，可以通过。

线性做法可以将二分改为尺取维护。排序用桶排即可。这样就能实现 $O(n)$ 了。

但是毕竟是我很久以前打的题目，就懒得写双指针了。

## 完整代码

很久以前的代码，凑合着看。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#define LL __int128  //直接用神器！
using namespace std;
const int N = 2e5 + 5;
int n, a[N];
long long M;
LL m, sum[N], sqsum[N];
bool chk(int peo)
{
	for (int l = 1, r = peo; r <= n; l++, r++) //枚举一段长度为 peo 的区间
	{
		LL t1 = peo * (sqsum[r] - sqsum[l-1]); //这里就是上面推出来的公式，公式里的 n 就是 peo。
		LL t2 = sum[r] - sum[l-1]; t2 *= t2;
		if (t1 - t2 <= peo * m) return true;
	}
	return false;
}
int FIND(int l, int r) //非常模版的二分答案
{
	int pos = -1; //pos 就是去掉多少个人
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (chk(mid)) l = mid+1, pos = mid;
		else r = mid-1;
	}
	return n - pos; //要求的是剩下多少人
}
int main()
{
	scanf("%d%lld", &n, &M);
	m = (LL)M; //懒得写快读了，这里是强转 __int128
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a+1, a+n+1); //注意要排序
	for (int i = 1; i <= n; i++)
	{
		sum[i] = sum[i-1] + a[i];
		sqsum[i] = sqsum[i-1] + (LL)a[i] * a[i];
	}
	printf("%d", FIND(0, n));
	return 0;
}
```

希望能帮助到大家！

---

## 作者：yummy (赞：15)

Update：配了一张图，修改下标错误，补充了一点点内容。
## Subtask 1
显然，我们如果要修改一个同学的水平值，那么一定要修改到这个同学对方差的贡献为0，也就可以看作扔掉这个数。   
暴力枚举每个数字是否被扔掉，然后计算方差。
## Subtask 2
显然可以看出，在最优情况下，排好序后我们保留的同学一定是连续的一段。  
否则的话，我们将边缘的同学改成区间中间的同学，方差一定会更小。  
![image.png](https://i.loli.net/2020/06/27/7LPKXOIYyTzfpiN.png)
三个绿色正方形是左边方差，三个黄色正方形是右边方差。

因此我们要对所有同学排序，然后枚举答案，并检验是否存在一个区间满足条件。时间复杂度$O(N^3)$.
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double m,a[1005],s[1005];
bool check(int left)//剩下left个同学是否符合条件
{
    for(int i=1;i<=n-left+1;i++)
    {
        double t=0,pj=(s[i+left-1]-s[i-1])/left;
      	//pj=区间平均数，t=方差
        for(int j=i;j<i+left;j++)
            t=t+(pj-a[j])*(pj-a[j]);
        if(t<=m)
            return 1;
    }
    return 0;
}
int main()
{
    scanf("%d%lf",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lf",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        s[i]=s[i-1]+a[i];
    int ans=0;
    for(int i=n;i>0;i--)
        if(check(i))
        {
            printf("%d",n-i);
            return 0;
        }
}
```
## Subtask 3-4
我们发现，如果扔掉$k$个同学满足条件，则$k+1$个同学也满足条件。   
这意味着什么？我们可以将答案二分！   
> 总有一种算法能够让你成功拿到分   
无论是贪心还是动规或者将答案二分

二分 $k$ 用时$O(\log N)$,枚举举所有扔掉 $k$ 个数的区间用时$O(N)$,计算区间方差用时$O(N)$,总用时$O(N^2\log N)$.   
该方法分数依常数而定，可以过3-4个Subtask。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double m,a[5005],s[5005];
//s表示前缀和
bool check(int left)//剩余left个数的时候能否满足条件
{
    for(int i=1;i<=n-left+1;i++)
    {
        double t=0,pj=(s[i+left-1]-s[i-1])/left;
        for(int j=i;j<i+left;j++)
            t=t+(pj-a[j])*(pj-a[j]);
        if(t<=m)
            return 1;
    }
    return 0;
}
int erfen(int l,int r)
{
    if(r==l+1)
        return l;
    int mid=(l+r)/2;
    if(check(mid))
        return erfen(mid,r);
    else
        return erfen(l,mid);
}
int main()
{
    scanf("%d%lf",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lf",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        s[i]=s[i-1]+a[i];
    printf("%d",n-erfen(1,n));
    return 0;
}
```
## Subtask 6
我们接着优化求方差的时间，设 $p$ 为平均数，那么题目要求：
$$\sum_{k=i}^j(a_k-p)^2$$
利用完全平方公式，知道它等价于：
$$\sum_{k=i}^ja_k^2-2p\cdot a_k+p^2$$
因此，我们维护区间和与区间平方和，就可以$O(1)$求方差。   
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long m,a[200005],s[200005],pfh[200005];
bool check(int left)
{
    for(int i=1;i<=n-left+1;i++)
    {
        double sum=s[i+left-1]-s[i-1];
        double pf=pfh[i+left-1]-pfh[i-1];
        double pj=sum*1.0/left;
        double fc=pf-2*pj*sum+pj*pj*left;
        if(fc<=m)
            return 1;
    }
    return 0;
}
int erfen(int l,int r)
{
    if(r==l+1)
        return l;
    int mid=l+r>>1;
    if(check(mid))
        return erfen(mid,r);
    else
        return erfen(l,mid);
}
char in[30],out[30];
int main()
{
	    scanf("%d%lld",&n,&m);
	    for(int i=1;i<=n;i++)
	        scanf("%lld",&a[i]);
	    sort(a+1,a+n+1);
	    for(int i=1;i<=n;i++)
	    {
	        s[i]=s[i-1]+a[i];
	        pfh[i]=pfh[i-1]+a[i]*a[i];
	    }
	    printf("%d",n-erfen(1,n+1));
    return 0;
}
```
你可能要问我，Subtask5是干啥的？   
xht说，建议加入 $O(N^2)$ 的部分分，给那些没有二分的同学。
## Subtask Extra
（by世界第一肥宅BF）   
这样的话，我们就可以考虑使用双指针的方式来维护。
维护和，平方和，平均数以及当前区间内的个数，然后计算是否符合条件。  
如果当前区间符合条件，则将右指针右移扩大区间，否则将左指针左移缩小区间。  
于是将这一步过程变成了 $\operatorname{O}(n)$。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
inline void write(register int x){
    if(x<0){
		putchar('-'), x=-x;
	}
    if(x>=10){
		write(x/10);
	}
    putchar('0'+x%10);
}
const int maxn=200005;
int n,m,a[maxn],sum,ans,l,r,sum2,num;
double now;
bool chk(){
	if(sum2*1.0-2*now*sum+now*now*num<=m) return 1;
	return 0;
}
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+1+n);
	now=a[1];
	sum=a[1];sum2=a[1]*a[1];
	l=1;r=1;
	num=ans=1;
	while(1){
		if(chk()){
			ans=max(ans,num);
			r++;
			if(r>n) break;
			sum+=a[r];sum2+=a[r]*a[r];
			num++;now=(double)sum/num;
		} 
		else{
			sum-=a[l],sum2-=a[l]*a[l];
			num--;now=(double)sum/num;
			l++;
		}
	}
	write(n-ans);
	return 0;
}
```
另外，由于 $a_i$ 的值域已知，我们可以通过基数排序或计数排序优化的方式将复杂度真正优化到线性，在此不加赘述。
## 一些拓展
如果修改第 $i$ 个同学水平值的代价是 $v_i$，要想让方差不超过 $m$，最少代价是多少呢？

如果二分代价，那么如何写 $check$ 函数才能在 $O(N)$ 时间完成呢？

如果想知道关于方差的更多知识，可以买一本《程序员的数学》或者挑战下我未完工的[概率期望24题](https://www.luogu.com.cn/blog/yummy-loves-114514/gai-shuai-ji-wang-24-ti)。

---

## 作者：MoonCake2011 (赞：12)

题目里说，方差的表达一组数据的波动程度的数据。

所以我们先对数组 $a$ 排序，其中的一段肯定是不用改水平的同学。

我们可以二分找出不用改水平的同学的个数就能求出答案。

二分的 $check$ 函数怎么写呢。

因为改水平一定会改为数列的平均值，所以它对方差的改变可以忽略不记。

所以我们只用求区间的方差。

我们可以枚举长度为 $mid$ 的区间，对这个区间求方差。

但是我们需要 $\text O(1)$ 求那段区间的方差。

那怎么 $\text O(1)$ 求方差呢？

我们对方差的式子拆开。

$p=\frac{\sum_{i=1}^na_i}{n}$。

$S=\frac{1}{n} \sum_{i=1}^na_i^2+p^2-2 \times a_i \times p$。

所以我们可以记录 $a$ 的前缀和与 $a$ 的前缀平方和。

就可以 $\text O(1)$ 求出那段区间的方差。

我们接下来就可以愉快的二分了。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
double m;
int a[signed(2e5)+10];
int s[signed(2e5)+10],ps[signed(2e5)+10];
bool check(int x){
	double minn=2e9;
	for(int i=1;i+x-1<=n;i++){
		double p1=ps[i+x-1]-ps[i-1];
		double p2=s[i+x-1]-s[i-1];
		double p=p2/x;
		double ans=p1-2*p*p2+p*p*x;
		if(ans<=m) return true;
	}
	return false;
}
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i],ps[i]=ps[i-1]+a[i]*a[i];
	int l=0,r=n,mid,ans=1;
	while(l<=r)
		if(check(mid=l+r>>1)) l=mid+1,ans=mid;
		else r=mid-1;
	cout<<n-ans;
	return 0;
}
```

---

## 作者：8atemak1r (赞：4)

这题需要一点推柿子的技巧 + 一个清醒的头脑

---

如果你觉得自己的柿子推对了但是样例不过，注意一下 `check` 的长度和 $n$ 的区别。

否则你可以向下看了

---

显然修改的同学越多方差越小，所以具有单调性，想到二分。

不难发现最优方案是排序之后留下某一段连续的值，将剩下的值变为这段值的平均数，对方差的贡献即为 $0$

设我们留下的段是 $p_l,p_{l+1},\dots,p_{r-1},p_{r}$，则方差的 $n$ 倍，即题中给出的 $m$ 为：

$$\begin{aligned} m & = \sum_{i=l}^r(a_i-p)^2\\
& = \sum_{i=l}^ra_i^2+\sum_{i=l}^rp^2-2\sum_{i=l}^rpa_i\\
&= \sum_{i=l}^ra_i^2 + \sum_{i=l}^r\dfrac{\left(\sum_{i=l}^ra_i\right)^2}{len^2}-2\sum_{i=l}^r\dfrac{\sum_{i=l}^ra_i}{len}a_i\\
&= \sum_{i=l}^ra_i^2 + \dfrac{\left(\sum_{i=l}^ra_i\right)^2}{len}-2\dfrac{\left(\sum_{i=l}^ra_i\right)^2}{len}\\
&= \sum_{i=l}^ra_i^2 + \dfrac{\left(\sum_{i=l}^ra_i\right)^2}{len}
\end{aligned}$$

维护前缀平方和与前缀和即可，`check` 部分如下：

```cpp
bool check(int x) {
	int len = n - x, l, r;
	rep(i, 1, n - len + 1) {
		l = i, r = i + len - 1;
		if(m * len >= (sn[r] - sn[l - 1]) * len - (s[r] - s[l - 1]) * (s[r] - s[l - 1])) return 1;
	}
	return 0;
}
```



---

## 作者：Register (赞：4)

- ~~我谔谔~~

~~因为文化课所以比赛结束后不到10min才调出来~~

设 $sum1=\sum a_i$

$sum2=\sum {a_i}^2$

则 $p=\frac{s}{n}$

$S=\sum_{i=1}^{n}(a_i-p)^2$

$S=\sum_{i=1}^{n}(a_i-\frac{sum1}{n})^2$

$S=\sum_{i=1}^{n}{a_i}^2-2\frac{a_isum1}{n}+\frac{sum1^2}{n^2}$

$S=sum2-2\frac{sum1^2}{n}+\frac{sum1^2}{n}$

$S=sum2-\frac{sum1^2}{n}$

然后有 $2$ 个显而易见的结论：

- 排序后选取同样个数的数连续的方差比不连续的小

- 你选择修改的数到最后一定是等于平均数的

二分一个答案表示最后没修改的个数，修改了的等于平均数不用管，剩下的在套用第 $1$ 个结论比较一下即可

### 代码

```cpp
#include <cstdio>
#include <algorithm>
#define int __int128
int n,m,l=1,r,a[200001],s1[200001],s2[200001];
signed ans;
inline int read(){
	char ch=getchar();int res=0,w=1;
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
	return res*w;
}
bool check(int x){
	for(register int i=1,j=i+x-1;j<=n;i++,j++)
		if((s2[j]-s2[i-1])*x-(s1[j]-s1[i-1])*(s1[j]-s1[i-1])<=m*x) return true;
	return false;
}
signed main(){
	r=n=read();m=read();
	for(register int i=1;i<=n;i++) a[i]=read();
	std::sort(a+1,a+n+1);
	for(register int i=1;i<=n;i++) {s1[i]=s1[i-1]+a[i];s2[i]=s2[i-1]+a[i]*a[i];}
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) {l=mid+1;ans=n-mid;}
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：YT0104 (赞：1)

一直不会方差的转换，正好遇到了这道题目，好好学了一下。

~~当年NOIP……哎说多了都是泪。~~

# [P6069 『MdOI R1』Group](https://www.luogu.com.cn/problem/P6069)

## [更好的阅读体验](https://www.cnblogs.com/Jack-YT/p/18296241)

## 思路：

### 1. 二分。

首先，上来我们就可以注意到最终的答案 $ans$ 是满足可二分性的，那么我们可以考虑二分，现在的问题就是怎么在修改的次数确定的情况下判断是否可行。

### 2. 考虑怎么修改。

既然我们已经明确可以二分，那么，**我们先要考虑在 $ans$ 确定的时候，我们怎么修改，才能让方差最小。**

由于方差的性质我们可知，方差其实就是对于一组数字与他们的相互之间偏差的**波动大小**，所以我们如果要改变一个数，一定是改变偏差**最大**的，将它对于波动程度的**影响消除**，其实就相当于是删除了这个数。

同时我们可以发现最后**剩下的数**一定是**原数组排序后的一段连续的数**（可以意会一下），因为最大或最小的数一定比中间的某个数与本数组的偏差大。

在求解的时候，我们可以 $O(n)$ 枚举长度为 $n-ans$（剩下的数的数量）的区间，将这个区间的方差与 $\frac{m}{n}$ 比较。

那么，我们最后就剩下了一个问题：**如何快速求一个区间的方差。**

### 3.方差的转化。

方差的原式子是不太好快速判断的，只能做到 $O(n)$判断，这样的话复杂度就是 $O(n^2\log n)$ 了。

我们考虑将方差的式子转化。

设 $S$ 为 $a$ 数组的方差，$p$ 为平均数。

则：

$$
S=\frac{1}{n}\sum_{i=1}^{n}(a_i-p)^2\\
p=\frac{1}{n}\sum_{i=1}^{n}a_i
$$

若设：

$$
sum=\sum_{i=1}^{n}a_i\\
psum=\sum_{i=1}^{n}a_i^2
$$

之后可转化为：

$$
S=\frac{1}{n}\sum_{i=1}^{n}(a_i^2+p^2-2a_ip)\\
\implies S=\frac{1}{n}(
\sum_{i=1}^{n}a_i^2+
\sum_{i=1}^{n}(p^2-2a_ip)
)\\
\implies S= \frac{1}{n}(psum+\sum_{i=1}^{n}(\frac{sum^2}{n^2}-2a_i\frac{sum}{n}))\\
\implies S=\frac{1}{n}(psum+\frac{sum^2}{n}-\frac{2sum^2}{n})\\
\implies S=\frac{1}{n}(psum-\frac{sum^2}{n})\\
$$

我们要判断：

$$
\frac{m}{n} \ge S
$$

即相当于：

$$
m \ge psum-\frac{sum^2}{n}
$$

这里需要注意修改后的数组相当于删掉了 $ans$ 个数字，所以在求方差的时候，原数组的长度就不是 $n$ 了，$n$ 就要变为 $n-ans$，设为 $len$。

那么我们可以将式子变为：

$$
m\times len\ge psum\times len-sum^2
$$

这样就可以去掉除法导致的精度问题了。

对于 $psum$ 和 $sum$ 我们可以前缀和预处理，就可以做到 **$O(1)$ 求方差。**

所以**最终复杂度就是 $O(n\log n)$。**

还有，要注意虽然式子右边可以发现一定在 long long 范围内，但是左边的 $m\times len$ 不一定，所以可以临时强转一下 __int128 或者特判。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll __int128
inline int read(){
	int rt=0;	bool kk=0;	char g=getchar();
	while(g<'0'||g>'9')	kk|=(g=='-'),g=getchar();
	while(g>='0'&&g<='9')	rt=(rt<<3)+(rt<<1)+g-'0',g=getchar();
	return (kk?-rt:rt);
}
inline ll lread(){
	ll rt=0;	bool kk=0;	char g=getchar();
	while(g<'0'||g>'9')	kk|=(g=='-'),g=getchar();
	while(g>='0'&&g<='9')	rt=(rt<<3)+(rt<<1)+g-'0',g=getchar();
	return (kk?-rt:rt);
}
int n,ans;
ll m,ls;
bool kk;
ll a[200005],sum[200005],psum[200005];
int main()
{
	n=read();	m=lread();
	for(int i=1;i<=n;i++)	a[i]=read();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+a[i],psum[i]=psum[i-1]+a[i]*a[i];
	
	int l=1,r=n,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;	kk=0;
		for(int i=mid;i<=n&&!kk;i++)
		{
			ls=sum[i]-sum[i-mid];
			kk|=((psum[i]-psum[i-mid])*mid-ls*ls<=m*mid);
		}
		if(kk)	l=mid+1,ans=mid;
		else r=mid-1;
	}
	
	printf("%d",n-ans);
	return 0;
}
``````

---

## 作者：focus_aurora (赞：1)

## 思路

首先，改动同学水平时，最优方案显然是改成平均数。此时就相当于去掉了这个同学。

看到题目要求最少需要改变同学的个数，而且答案单调，所以考虑二分答案。

二分需要改变的个数。

注意到保留的同学水平从小到大排序后一定是一个区间，所以我们二分保留同学的个数，然后遍历每个长度为 $mid$ 的区间，求方差。

但是这样会超时，考虑优化。

求方差的时候 $(a_i-p)^2$ 可以转化为 $a_i^2-2\cdot a_i\cdot p+p^2$。

这样的话就可以 $O(1)$ 求方差，我们只需要先预处理出前缀和和前缀平方和就可以了。

时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long a[1000005];
long long sum[1000005];
long long fac[1000005];
int check(int mid){
	for(int i=1;i<=n-mid+1;i++){
		long double ping=sum[i+mid-1]-sum[i-1];//求区间和
		long double sl=ping*1.0/mid;//求平均数
		long double ccf=fac[i+mid-1]-fac[i-1];//求区间平方和
		long double fangcha=ccf-2*sl*ping+sl*sl*mid;//计算方差
		if(fangcha<=m){//判断条件
			return 1;
		}
	}
	return 0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);//排个序
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];//前缀和
		fac[i]=fac[i-1]+a[i]*a[i];//前缀平方和
	}
	long long l=1,r=n+1;
	long long ans;
	while(l<=r){//二分答案
		long long mid=(l+r)/2;
		if(check(mid)){
			l=mid+1;
			ans=mid;
		}
		else{
			r=mid-1;
		}
	}
	cout<<n-ans;//输出结果
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：1)

# 前言

很恶心的卡精度题目，交了好几发才过，感觉评个绿都不为过。

# 正文

首先要改一个同学的水平，必须改成对方差的贡献为 0, 是我们可以视作这个同学死了。（不然改了也不是最小方差）

于是有了暴力：枚举改的人数，枚举改哪几个人，求得方差不大于 $M$ 即为最优解。

尝试排序利用单调性质优化，发现排序后如果要求改最少的人，必须是连续的一段。

这样方差相较于其他改了相同人数的方案就会最小。复杂度为 $\mathcal{O}(N^3)$.

考虑到答案的连续性（如果杀 $ans$ 个人能合法，那么杀 $ans + 1$ 个人一定能合法），于是尝试二分答案。

这样复杂度为 $\mathcal{O}(N^2 \log_2 N)$, 还是不够优秀.

尝试对方差的计算过程动手脚。观察求方差的柿子：

$$
S^2 = \frac{1}{N} \sum^{N}_{i = 1}{(a_i - p)^2}
$$

拆一下可得：

$$
S^2 = \frac{1}{N} \sum^{N}_{i = 1}{(a_i^2 -2 a_i \cdot p + p^2)}
$$

注意到柿子内有 $a_i^2$ 与 $-2 a_i \cdot p$, 结合前面的求和，可以看出区间平方和与区间和。

于是可以维护前缀平方和与前缀和, $\mathcal{O}(1)$ 求得区间方差。

复杂度变为 $\mathcal{O}(N \log_2 N)$, 显然可以通过此题。

# 关于 BF 的 Extra Subtask 解法的说明

一开始看到感觉好神奇，这线性做法是人能想到的吗？

后来看了一下感觉挺好的，思路很简单：

我们可以利用三个数组的单调性玩 two-pointer, 当区间方差超了就缩小左指针，当区间方差合法就扩右指针，可以做到假的 $\mathcal{O}(N)$ 复杂度。

~~毕竟还有 $\mathcal{O}(N \log_2 N)$ 的排序。~~

当然，我们观察到 $a_i$ 值域只有 $10^6$, 显然使用 $O(N)$ 桶排可以做到真正的线性。不过代码就不写啦。

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

inline __int128 read()
{
	char c = getchar();
    __int128 res = 0, sym = 1;
	while(c < '0' || c > '9') 
    {
        if(c == '-') sym = -1;
        c = getchar();
    }

	while(c >= '0' && c <= '9') 
    {
        res = res * 10 + c - '0';
        c = getchar();
    }

	return res * sym;
}

inline void write(__int128 x)
{
    if(x < 0)
		putchar('-'), x = -x;

    if(x >= 10)
		write(x / 10);

    putchar('0' + x % 10);
}

__int128 N;
__int128 M, ans;
__int128 arr[200005], sum[200005], sqsum[200005];

bool check(__int128 mid)
{
    for(int lp = 1, rp = lp + mid - 1; rp <= N; lp ++, rp ++) // Kill at most `mid` students below
    {
        __int128 __sum = (__int128) (sum[rp] - sum[lp - 1]);
        __int128 __sqsum = (__int128) (sqsum[rp] - sqsum[lp - 1]);
        long double avr = __sum * 1.000 / mid * 1.000;
        long double sqflt = __sqsum - 2.000 * avr * __sum + avr * avr * mid;
        if(sqflt <= M * 1.000)
            return true;
    }

    return false;
}

signed main()
{
    N = read(), M = read();
    for(__int128 i = 1; i <= N; ++ i)
        arr[i] = read();

    sort(arr + 1, arr + N + 1);
    for(__int128 i = 1; i <= N; ++ i)
    {
        sum[i] = sum[i - 1] + arr[i];
        sqsum[i] = sqsum[i - 1] + arr[i] * arr[i];
    }

    __int128 l, r;
    l = 1, r = N + 1;
    while(l <= r)
    {
        __int128 mid = (l + r) >> 1;
        if(check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }

    write(N - ans);
    return 0;
}
```

# 后言

二分答案的题目有些亦可尺取，复杂度更为优秀。

不过为了方便，在出题人不是特意卡你的情况下也用不着尺取，写二分即可。

注意本题精度很卡，记得写 `long double` 与 `__int128`.

---

## 作者：xiaohuang (赞：1)

### 分析

我们先将题目的式子简化一下：

$$\begin{aligned}S&=\frac{1}{n} \sum_{i=1}^n(a_i-p)^2\\S&=\frac{1}{n} \sum_{i=1}^n(a_i^2-2a_ip+p^2)\\S&=\frac{1}{n} \sum_{i=1}^n\left(a_i^2-2a_i\times\frac{sum1}{n}+\left(\frac{sum1}{n}\right)^2\right)\\nS&=sum2+\frac{sum1^2}{n}-2\times\frac{sum1^2}{n}\\nS&=sum2-\frac{sum1^2}{n}\end{aligned}$$

不难发现，要先排序，然后选取**一段连续区间的方差**一定比**选取同样个数的不连续区间的方差**小。所以我们可以二分答案（区间的长度），然后连续取每一段区间逐一判断就好了，时间复杂度为$\mathbb{O(n \log n)}$。

修改的数不用管，因为你可以修改成任意一个数。

### 代码

```cpp
#include<bits/stdc++.h>
#define int __int128
//不开int128会炸
using namespace std;

typedef long long LL;
const int MAXN = 200005;
int n, m, a[MAXN], sum1[MAXN], sum2[MAXN];
LL ans;
inline int read() {//int128必须快读
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void prepare() {
    sort(a + 1, a + n + 1);
    for (LL i = 1; i <= n; i++) {
        sum1[i] = sum1[i - 1] + a[i];
        sum2[i] = sum2[i - 1] + a[i] * a[i];
    }
}
inline bool check(LL x) {
    for (LL L = 1, R = L + x - 1; R <= n; L++, R++)
        if ((sum2[R] - sum2[L - 1]) * x - (sum1[R] - sum1[L - 1]) * (sum1[R] - sum1[L - 1]) <= x * m) return 1;
    return 0;
}
signed main() {
    n = read(), m = read();
    for (LL i = 1; i <= n; i++)
        a[i] = read();
    prepare();
    LL l = 1, r = n;
    while (l <= r) {
        LL mid = l + r >> 1;
        if (check(mid)) l = mid + 1, ans = n - mid; else r = mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Sternenlicht (赞：0)

思路：二分答案。

我们先将式子展开：

$$S=\frac{1}{n}\sum\limits_{i=1}^n(a_i-p)^2$$

$$S=\frac{1}{n}\sum\limits_{i=1}^na_i^2-2a_ip+p^2$$

又 $\because p=\sum\limits_{i=1}^na_i \div n$，设 $sum1=\sum\limits_{i=1}^na_i$，$sum2=\sum\limits_{i=1}^na_i^2$。


$$\therefore n\times S=sum2-2\times \frac{sum1^2}{n}+\frac{sum1^2}{n}$$

$$n\times S = sum2 - \frac{sum1^2}{n}$$

结论：$k$ 个连续的方差一定比 $k$ 个不连续的方差小。

将 $a$ 数组排序后，根据结论，二分答案区间长度，将每个区间逐个判断即可，时间复杂度为 $O(n \log_2 n)$。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define int __int128//注意要开int128，不然会炸 
	inline int read(){
		int x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(int x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[40];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

const int N = 2e5+10;
int sum1[N],sum2[N],a[N],n,m,l,r,mid,ans;
bool check(int x){//x是区间长度 
	for (int l=1,r=l+x-1;r<=n;l++,r++)//枚举区间判断是否合法 
		if ((sum2[r]-sum2[l-1])*x-(sum1[r]-sum1[l-1])*
		(sum1[r]-sum1[l-1])<=m*x)return true;
	return false;
}
signed main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);l=1,r=n;//排序，二分初始化 
	for (int i=1;i<=n;i++)//维护区间和、区间平方和 
		sum1[i]=sum1[i-1]+a[i],sum2[i]=sum2[i-1]+a[i]*a[i];
	while (l<=r)//二分答案
		if (check(mid=(l+r)>>1))
			l=mid+1,ans=n-mid;
		else
			r=mid-1;
	write(ans);//输出答案 
	return 0;
}
```

---

