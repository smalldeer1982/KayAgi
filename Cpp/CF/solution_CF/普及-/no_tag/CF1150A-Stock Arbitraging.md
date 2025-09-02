# Stock Arbitraging

## 题目描述

Welcome to Codeforces Stock Exchange! We're pretty limited now as we currently allow trading on one stock, Codeforces Ltd. We hope you'll still be able to make profit from the market!

In the morning, there are $ n $ opportunities to buy shares. The $ i $ -th of them allows to buy as many shares as you want, each at the price of $ s_i $ bourles.

In the evening, there are $ m $ opportunities to sell shares. The $ i $ -th of them allows to sell as many shares as you want, each at the price of $ b_i $ bourles. You can't sell more shares than you have.

It's morning now and you possess $ r $ bourles and no shares.

What is the maximum number of bourles you can hold after the evening?

## 说明/提示

In the first example test, you have $ 11 $ bourles in the morning. It's optimal to buy $ 5 $ shares of a stock at the price of $ 2 $ bourles in the morning, and then to sell all of them at the price of $ 5 $ bourles in the evening. It's easy to verify that you'll have $ 26 $ bourles after the evening.

In the second example test, it's optimal not to take any action.

## 样例 #1

### 输入

```
3 4 11
4 2 5
4 4 5 4
```

### 输出

```
26
```

## 样例 #2

### 输入

```
2 2 50
5 7
4 2
```

### 输出

```
50
```

# 题解

## 作者：Luo_gu_ykc (赞：2)

## 题目大意
你有 $n$ 个时刻可以买入股票，$m$ 个时刻可以卖出骨牌，现在给你这 $n$ 和 $m$ 种股票的价格。

问：经过操作后，你可以得到多少钱。

## 思路
分类讨论：
先看可不可以操作；

如果我最低的买入价格还不小于最高的卖出价格，就不操作。

### 可以操作：

先找到买入价格最低的股票价格和最高的股票卖出价格，再看可以买多少股票，最后再卖出对应数量的股票，再加上买股票后的剩余钱数即可；

### 否则：

直接输出 $r$ 。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =  35, M = 35;
int n, m, r, a[N], b[M], mini = INT_MAX, maxi = INT_MIN;
int main(){
	cin >> n >> m >> r;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		mini = min(mini, a[i]); // 最低的买入价格
	}
	for(int i = 1; i <= m; i++){
		cin >> b[i];
		maxi = max(maxi, b[i]); // 最高的卖出价格
	}
	cout << (mini >= maxi ? r : r / mini * maxi + r % mini); // 三目表达式，判断是否可以操作
	return 0;
}
```

---

## 作者：黄文烽 (赞：1)

## CF1150A题解
[题目传送门](https://www.luogu.com.cn/problem/CF1150A)
### 简化题意
**注意：输入的顺序是$n\rightarrow m\rightarrow r$,而不是$r\rightarrow n\rightarrow m$！**

你有$r$元钱,有$n$个时刻可以买入股票,$m$个时刻可以卖出股票(**这里的股票指的是同一种！**),求结束交易后能得到的最大钱数。

**数据范围：$1 \leq n \leq 30,1 \leq m \leq 30,1 \leq r \leq 1000$。**

**记第$i$个时刻的股票买入价格为$s_i$,第$j$个时刻的股票卖出价格为$b_j$,则必定有$1 \leq s_i,b_j \leq 1000$**

### 暴力
~~这个数据范围可水了，为何不用暴力？~~

本题数据范围很小,可以采用暴力的方式。我们枚举第$i$个买入时刻,第$j$个卖出时刻,买入$k$个股票(之所以不枚举卖出的股票数，是因为买入的股票必定要卖出，不然一定无法得到最优解),则$ans=r-(k*s_i)+(k*b_j)$，最后取最优解即可,时间复杂度$O(nm(ans/s_i))$

### 更好的暴力
既然我们要买$k$个股票,那么我们的最优解一定是让$(k*s_i)$最小,$(k*b_j)$最大。

因为我们枚举的是$k$,所以说我们可以将$k$视为常量,那么问题就变成了让$s_i$最小,$b_j$最大。

那么，我们可以使用两种方法:

1. 分别排序$s$数组和$b$数组,然后取极值,时间复杂度$O(knlogn)$。
2. 分别遍历$s$数组和$b$数组,然后记录遇到的极值,时间复杂度$O(kn)$。

遍历Code:
```cpp
for(int i = 0; i < n; i++){
	minn = min(x, s[i]);
}
	
for(int i = 0; i < m; i++){
	maxx = max(x, b[i]);
}
```

### 数学
我们可以把刚才的式子化简成$ans=k*(b_j-s_i)$,因为$(b_j-s_i)$的最大值已经求出,所以我们要让$ans$最大,可以分三种情况:

>如果$(b_j-s_i)>0$,那么为了让$ans$最大,$k$一定要取最大值,即$r/s_i$,所以$ans=(r/s_i)*(b_j-s_i)$

>如果$(b_j-s_i)<0$,那么为了让$ans$最大,$k$一定要取最小值,即$0$,所以$ans=r$

>如果$(b_j-s_i)=0$,那么无论$k$取何值,$ans$的值一定不变,所以$ans=r$

但是现实中,$r$不一定能够整除$s_i$,那么$ans$还需要加上剩下的钱数,即$r mod s_i$,所以$ans=(r/s_i)*(b_j-s_i)+(r \mod s_i)$

得代码如下:
```cpp
#include<iostream>

using namespace std;

int r, n, m;
int maxx, minn = 214700000; //maxx用来记录当前遇到的最大值,minn用来记录当前遇到的最小值

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> r >> n >> m;
	
	for(int i = 0; i < r; i++){
		int x;
		cin >> x;
		minn = min(x, minn); //读入并遍历
	}
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		maxx = max(x, maxx); //读入并遍历
	}
	
	if(minn > maxx) cout << m << endl; //如果(b[j] - s[i])<0
	else cout << ((m / minn) * maxx) + (m % minn) << endl; //否则
	
	return 0;
}
```
### 最后结果：[AC](https://www.luogu.com.cn/record/41064669)

---

## 作者：wgy23672 (赞：1)

题意很清楚了，这里不赘述，找出第一个数组中的最小值$aa$，第二个中的最大值$bb$，由于能无限次操作，所以只要钱够都ok，能买入的数量即为$r/aa$.

## 拓展

（新手请看）

***max_element** 和 ***min_element**函数用法

用于求数组中的最大值或最小值

比如，**求数组$a$中从第$0$个元素到第$n-1$个元素（包含第$n-1$个元素）的最大**值

```cpp
int maxx=*max_element(a,a+n);
//注意是a+n
```
需要提醒的是，*这个字符千万不能忘！，否则输出的是一个地址。

## 注意点

~~翻译有点小坑~~，**输入顺序应该是$n$,$m$,$r**$!

一定要判断$aa≥bb$的**特殊情况**，这样还是不操作划算呢

关键代码：

```cpp
cout<<r/aa*bb+r%aa;
```
说明一下：$r/aa*bb$ 指买入再卖出的利润+本金，$r %aa$ 指交易后剩下的钱数。

## 完整代码1（输入时判断最大最小值）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int r,n,m,a[31],b[31],aa=inf,bb;
int main(){
    cin>>n>>m>>r;
    for(int i=0;i<n;i++){
    cin>>a[i];
     aa=min(aa,a[i]);
    }
    for(int i=0;i<m;i++){
    cin>>b[i];
     bb=max(bb,b[i]);
    }
    if(aa>=bb){
        cout<<r;
        return 0;
    }
    cout<<r/aa*bb+r%aa;
    return 0;
}
```

## 完整代码2（*max/min_element）

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,n,m,a[39],b[39];
int main(){
    cin>>n>>m>>r;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<m;i++)cin>>b[i];
    int aa=*min_element(a,a+n);
    int bb=*max_element(b,b+m);
    if(aa>=bb){
        cout<<r;
        return 0;
    }
    cout<<r/aa*bb+r%aa;
    return 0;
}
```
希望大家都能AC！！




---

## 作者：UnyieldingTrilobite (赞：0)

一道有趣的题。

思路明确：要想赚到最大利益，要挑最便宜的买，最贵的卖，其他无视。

证明略去。

代码方面，只要所有价格，找最低的买入价和最高的卖出价，然后尽可能多的交易即可。

当然要是最高的卖出价还不到最低的买入价······就不买卖了。

能交易多少？

原式钱数除以最低买入价下取整。

然后，综上所述，这题就没了······

上python3代码罢。
```py
r=int(input().split()[2])#n和m不关心了
a=min([int(x) for x in input().split()])#最低买入价
b=max([int(x) for x in input().split()])-a#压了行，就是最高卖出价-最低买入价（最高收益）
print(r//a*max(0,b)+r)#交易
```
嗯，代码不长，但细节的处理（比如不买卖的情况）还是值得思考的！

Over.

---

## 作者：帝千秋丶梦尘 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1150A)

找到能买进的最少的价格Min，找到能卖出的最高的价格Max

若$Min≥Max$，即怎么卖都赚不了，那么直接输出原有的钱

否则，就算出能买进的最多数量，即$r/Min$，再乘上差价$Max-Min$

就是赚到的钱了，最后加上原有的钱，即所拥有的钱

CODE：

```cpp
#include<bits/stdc++.h>
#define ri register
using namespace std;
int n,m,r,Min=1e9,Max=-1e9,ans;
int a[31],b[31];
int main(void)
{
	std::ios::sync_with_stdio(false);
	cin>>n>>m>>r;
	for(ri int i(1);i<=n;++i)
	{
		cin>>a[i];
		Min=min(a[i],Min);
	}
	for(ri int i(1);i<=m;++i)
	{
		cin>>b[i];
		Max=max(b[i],Max);
	}
	if(Min<Max)
	{
		ans=r+(r/Min)*(Max-Min);
	}
	else ans=r;
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：Carotrl (赞：0)

简单的贪心题。

### 贪心思想：用最便宜的钱买进，用最贵的钱卖出。

#### 注意，若买进最便宜的钱大于卖出最贵的钱，肯定亏本了，就不买了，直接输出原本的钱数。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[100005],n,minn=0x7f7f7f7f,maxx,m,k,x;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		minn=min(minn,x);//最便宜的买进
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		maxx=max(maxx,x);//最贵的卖出
	}
	if(minn>maxx)printf("%d\n",k);//亏本就不买了
	else printf("%d\n",(k/minn*maxx)+(k-k/minn*minn));//计算总钱数
}
```


---

## 作者：do_while_false (赞：0)

【大概思路】

既然要使利益最大化，很容易想到贪心。

我们只要选择最便宜的股票买入，选择最贵的股票卖出即可实现利益最大化。

但注意一点，如果进行操作后我们不获得利益，那就不进行操作。

【代码实现】

```cpp
#include<bits/stdc++.h>
#define MAX 1<<30
using namespace std;
int n,m,r,x,num;
int minb=MAX,maxs=-MAX;
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
int main(void) {
	n=read();m=read();r=read();
	for(int i=1;i<=n;i++) {//取其最小值 
		x=read();
		minb=min(x,minb);
	}
	for(int i=1;i<=m;i++) {//取其最大值 
		x=read();
		maxs=max(maxs,x);
	}
	if(minb>=maxs) {//进行判断，如果操作后是亏损，就不进行操作 
		printf("%d\n",&r);
		return 0;
	}
	else {//计算答案 
		num=r/minb;
		r=r%minb+num*maxs;
		printf("%d\n",&r);
	}
	return 0;
} 
```

---

## 作者：Erusel (赞：0)

我们既然要使利润最大化，

贪心的想，

肯定选择最便宜的股票买入，最贵的股票卖出

但还有细节要处理：

1.如果进行操作后还是亏损，不如不进行操作。

2.你只能购买整数数量的股票

代码：

```
#include<bits/stdc++.h>

#define rd(x) x=read()
#define N 35

using namespace std;

int n,m,r;
int a[N];
int b[N];
int minn=1000,maxn;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int main()
{
	rd(n),rd(m),rd(r);
	for(int i=1;i<=n;i++)rd(a[i]),minn=min(minn,a[i]);//取最小值
	for(int i=1;i<=m;i++)rd(b[i]),maxn=max(maxn,b[i]);//取最大值
	if(minn<maxn)printf("%d\n",r/minn*maxn+r%minn);//计算答案
	else printf("%d\n",r);//如果进行操作后还是亏损，不如不进行操作
	
	
	
    return 0;
}
```


---

