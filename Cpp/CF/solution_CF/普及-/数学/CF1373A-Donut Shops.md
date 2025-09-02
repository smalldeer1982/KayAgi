# Donut Shops

## 题目描述

There are two rival donut shops.

The first shop sells donuts at retail: each donut costs $ a $ dollars.

The second shop sells donuts only in bulk: box of $ b $ donuts costs $ c $ dollars. So if you want to buy $ x $ donuts from this shop, then you have to buy the smallest number of boxes such that the total number of donuts in them is greater or equal to $ x $ .

You want to determine two positive integer values:

1. how many donuts can you buy so that they are strictly cheaper in the first shop than in the second shop?
2. how many donuts can you buy so that they are strictly cheaper in the second shop than in the first shop?

If any of these values doesn't exist then that value should be equal to $ -1 $ . If there are multiple possible answers, then print any of them.

 The printed values should be less or equal to $ 10^9 $ . It can be shown that under the given constraints such values always exist if any values exist at all.

## 说明/提示

In the first testcase buying any number of donuts will be cheaper in the second shop. For example, for $ 3 $ or $ 5 $ donuts you'll have to buy a box of $ 10 $ donuts for $ 4 $ dollars. $ 3 $ or $ 5 $ donuts in the first shop would cost you $ 15 $ or $ 25 $ dollars, respectively, however. For $ 20 $ donuts you'll have to buy two boxes for $ 8 $ dollars total. Note that $ 3 $ and $ 5 $ are also valid answers for the second shop, along with many other answers.

In the second testcase buying any number of donuts will be either cheaper in the first shop or the same price. $ 8 $ donuts cost $ 32 $ dollars in the first shop and $ 40 $ dollars in the second shop (because you have to buy two boxes). $ 10 $ donuts will cost $ 40 $ dollars in both shops, so $ 10 $ is not a valid answer for any of the shops.

In the third testcase $ 1 $ donut costs $ 2 $ and $ 3 $ dollars, respectively. $ 2 $ donuts cost $ 4 $ and $ 3 $ dollars. Thus, $ 1 $ is a valid answer for the first shop and $ 2 $ is a valid answer for the second shop.

In the fourth testcase $ 10^9 $ donuts cost $ 10^{18} $ dollars in the first shop and $ 10^9 $ dollars in the second shop.

## 样例 #1

### 输入

```
4
5 10 4
4 5 20
2 2 3
1000000000 1000000000 1000000000```

### 输出

```
-1 20
8 -1
1 2
-1 1000000000```

# 题解

## 作者：zct_sky (赞：2)

### Solution:
-----
首先，如果要使第一家商店中购买比在第二家商店购买便宜，那肯定是只买一个。

如果买一个都没有第二家商店便宜（$a\ge c$），则输出 $-1$，否则输出 $1$。

然后，如果要使第二家商店中购买比在第一家商店购买便宜，那肯定是只买一盒。

如果买一盒都没有第一家商店便宜（$c\ge a\times b$），则输出 $-1$，否则输出 $b$。
### Code:
-----
```c++
#include <bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
ll t,a,b,c;
int main(){
	cin>>t;
	for(ll i=0;i<t;i++){
		cin>>a>>b>>c;
	    if(a>=c) cout<<"-1 ";
	    else cout<<"1 ";
		if(a*b<=c) cout<<"-1\n";
		else cout<<b<<"\n";
	}
	return 0; 
}
```

---

## 作者：cyh_toby (赞：2)

# 题意

原题：[CF1373A【Donut Shops】](https://www.luogu.com.cn/problem/CF1373A)

给定正整数 $a,\,b,\,c$ ，两种方案：

- 单个买，每个费用 $a$ ；

- 套装买 ，一个套装 $b$ 个，每套费用 $c$ ，可以买多但不能拆开。

求购买数量 $x$ 或判定无解：

1. 单个买费用严格小于套装买费用；

1. 套装买费用严格小于单个买费用。

# 分析

称上述单个买的方案费用为 $A$，套装买费用为 $B$。

首先考虑什么时候 $A$ **一定**更小。
显然是 $a < \dfrac{c}{b}$ 。此时对于 $1$ 任意一个 $x$ 即可，并且 $2$ 一定无解。

此外还有什么时候 $A$ **可以**更小？
注意到 $B$ 要向上取整，又由于 $2 \le b$，因此当 $a<c$ 时，$x=1$ 即满足 $1$ 。

除此以外 $A$ 不可能更小，即 $1$ 无解。

那么什么时候 $B$ **可以**更小？
显然想最优化 $B$，一定要当 $b|x$ 时（这样相对于零售才不会有浪费）。这个时候用套装买其实就等价于单价 $\dfrac{c}{b}$ 的零售。因此当 $a\times b > c$ 时取 $x = b$ 即满足 $2$。反之则 $2$ 无解。

将上述整理写出代码

# 源码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		ll a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		if (a < (double)c / b) {
			printf("1 -1\n");
			continue;
		}
		if (a < c) {
			printf("1 ");
		}
		else {
			printf("-1 ");
		}
		if (a*b > c) {
			printf("%lld\n", b);
		}
		else
			printf("-1\n");
	}
	return 0;
}
```


---

## 作者：159号程序员 (赞：2)

这道题是一道模拟题，难度适中。

有两家甜甜圈店。

第一家店散卖甜甜圈， $x$ 元一个

第二家店按箱卖甜甜圈，一箱有 $y$ 个甜甜圈，$z$ 元一箱。

如果你想从第二家店买 $a$ 个甜甜圈，你必须使得你买的箱数 乘 $y$ 的积 $\ge$ $a$。

一共有两个问题：

1. 你要买多少甜甜圈，才可以使得你在第一家店的花费小于在第二家店的花费。

2. 你要买多少甜甜圈，才可以使得你在第二家店的花费小于在第一家店的花费。

如果两个数中的一个数不可能存在，就输出 $-1$。

---

可以直接模拟：

_AC Code_
```cpp
#include<bits/stdc++.h>
using namespace std;

int T, a, b, c;
int ans1, ans2;
int main()
{
	cin >> T; //有 T 次操作
	while(T--)
        {	
		cin >> x >> y >> z;
		if(z / y >= x)//假如一箱里一个甜甜圈比散装的一个甜甜圈还有贵的话，不可能成功。
		{
		    ans2 = -1;
		}
		else //否则，y 个一定能满足 ¹
		{
		    ans2 = b;
		}
		if(a >= c) //如果一个甜甜圈比一箱还贵，不可能成功。
		{
		    ans1 = -1;
		}
		else
		{
			for(int i = 1; i < b; i++) //循环枚举找出答案。
			{
				if(i * a < c)
				{
					ans1 = i;
					break;
				} 
			}
		}
		cout << ans1 << " " << ans2 << endl; //输出，记得换行。
	}
	return 0;
}
```
引用：
感谢[`_Fontainebleau_`](https://www.luogu.com.cn/blog/why20080504/solution-cf1373a) 告诉了我题目的大概翻译(我英语不好)和 ¹ 处的判断！

---

## 作者：Colorful_Unicorn (赞：1)

首先，这是一道数学题。

我们可以分别讨论两家店子的情况：

1. 考虑第一家，当选择第一家店单个售出，比第二家店一盒售出还要贵（$a_i\ge c_i$），那就不选择第一家，即输出 $-1$，否则买一个，输出 $1$。
2. 考虑第二家，当选择第二家一盒售出，比第一家店要贵（$c\ge a\times b$），那么选择第一家，即输出 $-1$，否则买一盒，输出 $b$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long  //切记开long long
int n,q[1000005],w[1000005],e[1000005];
signed main()
{
    cin >> n;
    for (int i=1;i<=n;i++)
        cin >> q[i] >> w[i] >> e[i];
    for (int i=1;i<=n;i++)
    {
        if (q[i]>=e[i])
            cout << "-1 ";
        else 
            cout << "1 ";
        //第一种情况，关于第一家
        if (e[i]>=q[i]*w[i])
            cout << "-1\n";
        else
            cout << w[i] << "\n";
        //第二种情况，关于第二家
    }
    return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1373A)

## 题目分析

如果在第一家商店买比第二个买便宜，那么就买一个，输出 1 ，否则就输出 -1 。

如果要令在第二家商店比在第一家商店买便宜，那么就只买一盒，输出 b ，否则就输出 -1 。

## 注意事项

十年 oi 一场空，没开 long long 见祖宗。

## 贴上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T;
int main(){
	cin>>T;
	while(T--){
		register long long a,b,c;
		cin>>a>>b>>c;
		if(a>=c) cout<<"-1 ";
		else cout<<"1 ";
		if(a*b>c) cout<<b<<endl;
		else cout<<"-1"<<endl;
	}
}
```

---

## 作者：_Fontainebleau_ (赞：1)

## 题意

有两家甜甜圈店。

第一家店零售甜甜圈， $a$ 元一个

第二家店整箱出售甜甜圈，一箱有 $b$ 个甜甜圈，需要 $c$ 元。如果你想从第二家店买 $x$ 个甜甜圈，你必须使得你买的箱数 乘 $b$ 的积 $≥x$ 。

现在请你求两个数。

第一个：你要买多少甜甜圈，才可以使得你在第一家店的花费严格地小于在第二家店的花费。

第二个：你要买多少甜甜圈，才可以使得你在第二家店的花费严格地小于在第一家店的花费。

如果两个数中的一个数不存在，就输出 -1 。


------------
一看就是一道模拟， $CF$ 上给的算法标签是 贪心，模拟，数论。

直接上代码，具体在注释中分析
```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int t;
int a,b,c;
int res1,res2;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		res1=-1;
		scanf("%d%d%d",&a,&b,&c);
		if(c/b>=a)	res2=-1;//如果b/c比a大，那么不存在第二种可能
		else	res2=b;//要不然 b 个甜甜圈一定能满足2
		if(a>=c)	res1=-1;//很显然，如果单价≥一箱子的价钱1肯定不行
		else
			for(int i=1;i<=b;i++)
				if(i*a<c)//第一个数就这么出来了
				{
					res1=i;
					break;
				} 
		printf("%d %d\n",res1,res2);
	}
	return 0;
}

```

---

## 作者：b6e0_ (赞：1)

[CF题面传送门](https://codeforces.com/contest/1373/problem/A) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1373A) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1373A)

第一个问题：可以只买$1$个，这样会使得在商店二购买商品时会多买一些东西（至少不会少买）。这样在商店一购买需要$a$元，在商店二购买需要$c$元。比较即可。

第二个问题：可以买$b$个，这样在商店二购买时不会多买，正好。这样在商店一购买需要$a\times b$元，在商店二购买需要$c$元。比较即可。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int a,b,c;
		cin>>a>>b>>c;
		if(a>=c)
			cout<<"-1 ";
		else
			cout<<"1 ";
		if(c>=a*b)
			cout<<"-1\n";
		else
			cout<<b<<endl;
	}
	return 0;
}
```
过于简单，就不加注释了。时间复杂度为$O(t)$。

---

## 作者：_ouhsnaijgnat_ (赞：0)

## 题目大意

有两个商店，第一个商店每个甜甜圈 $a$ 元每个，第二个商店共 $b$ 个甜甜圈需要 $c$ 元。

让你求在第一家商店中购买几个甜甜圈比在第二家商店中便宜？

以及在第二家商店中购买几个甜甜圈比在第一家商店中便宜？

## 思路

我们先理一下，若第一家商店的单价比第二家商店的单价小，肯定输出 $1$，否则就无解，输出 $-1$。

第一个问题解决了，再来看第二个问题，如果在第一个商店买 $b$ 个甜甜圈比第二个商店便宜，则无解。反之，因为只能整盒买，所以输出 $b$。

---

## 作者：Back_Stuff (赞：0)

## 思路

一道很简单的模拟题，只要考虑糖果价钱之间的关系就行了，但是要考虑周到。

1. 在第一家商店中购买几个甜甜圈比在第二家商店中便宜？

	如果 $a$ 比 $c$ 大,那么无论 $b$ 是多少，在第一家商店中购买甜甜圈就不可能比在第二家商店中便宜，输出 $-1$。

	要是 $a$ 是与 $c$ 相同的，就要考虑 $b$ 了。$b$ 不为 $1$ 时，在第一家商店中购买甜甜圈只能比在第二家商店中昂贵或价格相等，所以也输出 $-1$。

	其余情况均输出 $1$ 即可。

2. 在第二家商店中购买几个甜甜圈比在第一家商店中便宜？

	只要在第二家商店中买甜甜圈的平均价格比第一家的低，那么在第二家商店中买一定个数的甜甜圈，就肯定比在第一家商店中便宜。

	反过来也就是说，只要在第二家商店中买甜甜圈的平均价格比第一家的高或相等，那么在第二家商店中购买甜甜圈就不可能比在第一家商店中便宜。

	其余情况均输出 $b$ 即可。

## 代码

在思路中已详细讲解，代码中就不做太多的注释了，勿喷。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)//优化
using namespace std;
ll t,a,b,c;//虽然不用也可以，但我觉得最好开long long
int main(){
    IOS;
    cin>>t;
    while(t--){
        cin>>a>>b>>c;
        if(a>c||a==c&&b>1) cout<<"-1 ";
        else cout<<"1 ";
        if((c*1.0/b)>=a) cout<<"-1\n";
        else cout<<b<<"\n";
    }
    return 0;
}
```

---

## 作者：XCH_0803 (赞：0)

首先这道题是一道构造题

如果第一家商店买一个甜甜圈都没有第二个商店买一盒甜甜圈便宜,那不管卖多少都不会比第二家便宜,所以输出 $-1$ ,否则就买一个，输出 $1$ 

如果在第二家商店买一盒甜甜圈，都没有第一个商店买同样个数的甜甜圈便宜，那么就输出 $-1$ ，否则就循环找答案


话不多说上代码

```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int sum=-999;
		long long a,b,c;//要开long long 不然会爆int
		cin>>a>>b>>c;
		if(a>=c){
			sum=-1;
		}
		else{
			sum=1;
		}
		int num=0;
		if(a*b<=c){
			num=-1;
		}
		else{
			for(int i=1;;i++){
				num+=b;
				if(a*num>c){
					break;
				}
			}
		}
		cout<<sum<<" "<<num<<endl;
	} 
    return 0;
}
```


---

## 作者：MrCR7 (赞：0)

## 简述题意
输入第一行一个数字 $t$，代表数据组数。

接下来的 $t$ 行，每行三个整数 $a$，$b$，和 $c$，$a$ 代表第 $1$ 家商店的一个甜甜圈的价格,而 $b$ 和 $c$ 第二家店散装出售甜甜圈一盒 $b$ 个甜甜圈的价格为 $c$。

问题：

1. 在第 $1$ 家商店中购买几个甜甜圈比在第 $2$ 家商店中便宜？

2. 在第 $2$ 家商店中购买几个甜甜圈比在第 $1$ 家商店中便宜？

如果其中某个答案不存在，输出 $-1$。如果有多个可能的答案，请输出任 $1$ 个。
## 思路分析
1. 如果要使第 $1$ 家商店中购买比在第 $2$ 家商店购买便宜，那肯定是只买 $1$ 个（本题随意输出 $1$ 种可能）。即 $c \le a$ 时，输出的便是 $1$，否则输出 $-1$。
2. 第二个问题略麻烦一些，我们算出在第 $2$ 家购买的单价，设为 $f$，跟第 $1$ 家的 $a$ 进行对比，当 $a \le f$ 的时候，输出 $-1$，否则输出 $b$ （在第 $2$ 家 $b$  个甜甜圈 $1$ 份）。
## Ac Code
```cpp
#include<stdio.h>
void work(){
		double a,b,c;//如题。
		scanf("%lf%lf%lf",&a,&b,&c);
		if(a>=c) printf("-1 ");
		else printf("1 ");//判断a>=c是否成立。
		double f=c/b;//算出第二家商店一个的单价。
		if(f>=a) puts("-1");//判断。
		else printf("%.0lf\n",b);//记得这里要取整！
		return ;
}
int main(){
		int t;
		scanf("%d",&t);
		while(t--) work();
		return 0;
}
```

本篇题解到这里就结束啦~

希望过审，管理员辛苦了。

---

## 作者：45dinо (赞：0)

一个有点细节的——构造题

显然，最极端的情况是 $1$ 个甜甜圈去 $A$ 商店， $n$ 个甜甜圈去 $B$ 商店，所以只用判断这两种情况是否可行即可。

注意第二种情况显然不能用乘法判断，只能用除法。

具体细节看代码：

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
double a,b,c;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        cin>>a>>b>>c;
        if(a>=c)
            cout<<-1<<" ";
        else
            cout<<1<<" ";
        double x=c/b;
        if(x>=a)
            cout<<-1<<endl;
        else
            cout<<(int)b<<endl;
    }
    return 0;
}
```


---

## 作者：_0x46EDC (赞：0)

[获得更好的阅读体验](https://www.luogu.com.cn/blog/jasonying/cf1373a-donut-shops) [题目传送门](https://www.luogu.com.cn/problem/CF1373A)

---

### 题目分析

有两家甜甜圈商店，甲商店每个甜甜圈 $a$ 元，乙商店每盒 $b$ 个甜甜圈共 $c$ 元。

求购买甜甜圈数量 $x$ 或判定无解（无解时输出`-1`；特别地，乙商店中只能多买不能少买）：

- 甲商店花费小于乙商店花费

- 乙商店花费小于甲商店花费

### 推导

甲商店：$ax$

乙商店：$\lceil\dfrac{x}{b}\rceil \times c$

---

#### $1.$ 甲商店小于乙商店

即 $ax < \lceil\dfrac{x}{b}\rceil \times c$

$(1).\quad ax<\dfrac{c}{b}x$

$\because x>0$

$\therefore a<\dfrac{c}{b}$

$\therefore ab<c,x\in R$

$(2).\quad \dfrac{c}{b}x \le ax < \lceil \dfrac{x}{b} \rceil \times c$

$\because b \ge 2 $

$\therefore a<c,x=1$

---

#### $2.$ 乙商店小于甲商店

推导过程类似

得 $ab>c,x=b$

---

综上，

$\left\{\begin{aligned}x&\in R(ab<c)\\x&=1(a<c)\end{aligned}\right.$ 时 $1$ 成立；

$x=b(ab>c)$ 时 $2$ 成立。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
int main(){
    cin>>T;
    while(T--){
        ll a,b,c;
        cin>>a>>b>>c;
        if(a*b<c||a<c)cout<<"1 ";
        else cout<<"-1 ";//这两句为第一问的答案
        if(a*b>c)cout<<b<<endl;
        else cout<<"-1"<<endl;//这两句为第二问的答案
    }
    return 0;
}
```

### 结语

给了一份相较于其他题解稍微详细一点的推导过程，如果能有更加详细的，可以私信我哦。

---

## 作者：SymphonyOfEuler (赞：0)

**题目大意：**

有两个竞争的甜甜圈商店，第一个商店按单个算，每个甜甜圈$a$元。第二个商店按盒子算，每盒$b$个甜甜圈一共$c$元。所以你如果想买$x$个甜甜圈，那么你就嘚买的几盒中甜甜圈总数大于或等于$x$。

让你求一下两个的数：

- 你最多可以从第一个商店买多少比第二个商店的便宜。
- 你最多可以从第二个商店买多少比第一个商店的便宜

**思路：**

我们设第一个问的答案为$sum1$，第二个为$sum2$，都初始化为$-1$，因为最后答案如果无解，那么输出$-1$。

```
long double T;
    cin>>T;
    while(T--){
         long double a,b,c,sum1=-1;
         int sum2=-1;
         cin>>a>>b>>c;
```


然后输入进来$a,b,c$。先判断如果第一个的单价大于每盒的价钱，那么第二个$sum=1$。
```
if(a>c) sum2=1;
```


或者如果第一个的价钱=每盒的价钱，那么第二个$sum=2$。

```
else if(a==c) sum2=2;
```

否则第一个sum是1，然后如果第二个的单价小于$a$，那么$sum2=c/a$

```
else {
            sum1=1;
            if(c/b<a)
            	sum2=int(c/a+1);
 
          }   
```


注意事项:

- $t ( 1 \le t \le 1000)$

- $( 1 \le a \le 10^9, 2 \le b \le 10^9, 1 \le c \le 10^9)$


---

