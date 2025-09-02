# Feed the cat

## 题目描述

## 题意翻译

安德鲁在 $hh:mm$ 时刻醒来后，意识到他又忘记喂他唯一的猫了（~~猜猜为什么只有一只猫~~）。猫现在的饥饿程度是 $H$ 点，而且每分钟没有食物都会增加 $D$ 点的饥饿感。

在任何时候，安德鲁都可以去一家卖美味面包的商店（你可以假设去商店和回来不需要时间）。一个这样的小圆面包要花费 $C$ 卢布，减少 $N$ 点的饥饿感。由于对面包店的需求在晚上大幅下降，因此从 20:00 开始，面包有 $20%$ 的特别折扣（注意，成本可能会变得合理）。当然，小圆面包不能分批出售。

确定安德鲁为养猫必须花费的最低金额。如果这只猫的饥饿程度小于或等于零，它就被认为是被喂养的。

## 说明/提示

在第一个样本中，安德鲁可以在 $20$ 点 $20$ 分准时去商店。猫的饥饿将等于 $315$，因此有必要购买 $315$ 个小圆面包。最后的答案是 $25200$ 卢布。

在第二个样本中，他醒来后立刻去商店是最佳选择。然后他每 $15$ 卢布就要买 $91$ 个小圆面包，总共要花 $1365$ 卢布。

## 样例 #1

### 输入

```
19 00
255 1 100 1
```

### 输出

```
25200.0000
```

## 样例 #2

### 输入

```
17 41
1000 6 15 11
```

### 输出

```
1365.0000
```

# 题解

## 作者：respect_lowsmile (赞：1)

## solution

### 贪心

如果安德鲁醒来的时间在 20：00 之后了~~话说中午睡觉和晚上睡觉能睡到20：00以后也是真的离谱~~，那么很明显，最优的策略就是直接去买，因为这时面包的价格已经固定，再拖下去会增加猫的饥饿度，需要的面包数也就要增多，花的钱也越多。

如果安德鲁醒来的时间在 20：00 之前，那么就有两种情况，一种是直接去买，另一种是等到 20：00 之后立刻去买，至于为什么立刻去买，证明过程同上，我们从两个值中取最小值就是正解。

好的，下面是大家最喜欢的代码部分。

## code

 ```
#include<iostream>
#include<cmath>
using namespace std;
double hh,mm,h,d,c,n,num,ans,numm,anss;
double MIN(double a,double b)//返回值类型一定不要写错
{
	return a>b?b:a;//三目运算符更快 
}
int main()
{
	scanf("%lf%lf%lf%lf%lf%lf",&hh,&mm,&h,&d,&c,&n);
	if(hh>=20)//起床时间晚于20：00的情况 
		num=ceil(h/n),ans=num*c*0.8;
	else if(hh<20)//起床时间早于20：00的情况 
	{
		num=ceil(h/n),ans=num*c;//直接买的情况 
		double minute=60*(20-hh)-mm;//等到20：00之后再买的情况 
		h=h+d*minute;
		numm=ceil(h/n),anss=numm*c*0.8;
		ans=MIN(ans,anss);
	}
	printf("%.4lf",ans);
	return 0;
} 

```


---

## 作者：MrFish (赞：1)

#### 整体思路：如果时间已经过了20点，直接去买面包，否则输出等到20点去买所需的钱和立刻去买所需的钱的最小值。

奉上我的AC代码：

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>

using namespace std;

int main()
{
    double hour,minute;
    double h,d,c,n;
    cin>>hour>>minute>>h>>d>>c>>n; //读入
    if(hour>=20)
    {
        printf("%0.4f",c*0.8*(ceil(h/n))); //直接用打折后的价钱来算
    } //如果时间已经过了20点
    else
    {
        double a,b;
        a=c*0.8*ceil((h+((20-hour)*60-minute)*d)/n);  //等到20点买
        b=c*ceil(h/n);  //立刻去买
        printf("%0.4f",min(a,b));  //输出等到20点去买所需的钱和立刻去买所需的钱的最小值
    }
    return 0;
}
```
公式推导：
```latex
a:先算出当前时间和20点的差，即为(20-hour)*60-minute，然后算出猫当前的饥饿值，再算出需要多少面包（要向上取整），最后乘以打折后面包的单价。
b:算出需要多少面包（要向上取整），再乘以面包的单价。
```
拜拜！

---

## 作者：lrmlrm_ (赞：0)

# 题意

$ 20 $ 点后买面包价钱变为原来的 $ 80\% $  ， 其他时间原价 ， 要花的钱最少 。

# 思路

有两种情况 : 

$ \ \ $ 1 . 当 $ 20 $ 点与 $ 20 $ 点后 ， 直接去买面包即可 。

$ \ \ $ 2 . 在 $ 20 $ 点钱 ， 就在直接买和等到 $ 20 $ 点再买中找出最小值 。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c,d,e,f;
int main()
{
	cin>>a>>b>>c>>d>>e>>f;
	if(a>=20)
		printf("%.4lf",ceil(c/f)*(e*0.8));
	else
    	printf("%.4lf",min(ceil(c/f)*e,ceil((c+((20-a-1)*60+60-b)*d)/f)*(e*0.8)));
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 题意
安德鲁在 $hh$：$mm$ 刻醒来后，意识到他又忘记喂他唯一的猫了。猫现在的饥饿程度是 $H$ 点，而且每分钟没有食物都会增加      
 $D$ 点的饥饿感。

在任何时候，安德鲁都可以去一家卖美味面包的商店。一个这样的小圆面包要花费 $C$ 卢布，减少 $N$ 点的饥饿感。由于对面包店的需求在晚上大幅下降，因此从 $20$:$00$ 开始，面包有八折的特别折扣（注意，成本可能会变得合理）。当然，小圆面包不能分批出售。

确定安德鲁为养猫必须花费的最低金额。如果这只猫的饥饿程度小于或等于零，它就被认为是被喂养的。

# 思路

情况 $1$: 安德鲁醒来时已经过了 $20$ 点，直接去买面包。

情况 $2$: 安德鲁醒来时还没到 $20$ 点，输出立即买面包的钱和等到 $20$ 点再去买面包的钱的最小值。

# 代码
 
```cpp
#include<bits/stdc++.h>
using namespace std;
double x,y,a,b,c,d;
int main()
{
	cin>>x>>y>>a>>b>>c>>d; 
	if(x>=20) printf("%.4lf",ceil(a/d)*c*0.8);
	else printf("%.4lf",min(ceil(a/d)*c,ceil((a+((20-x)*60-y)*b)/d)*c*0.8));
	return 0;
}
```

---

## 作者：_cmh (赞：0)

[原题传送门~](https://www.luogu.com.cn/problem/CF955A)

## $\texttt{Description}$

$20$ 点后买面包价钱变为原来的 $80\%$，其他时间原价。要求花的钱最少。

## $\texttt{Solution}$

分类讨论。

- 当 $20$ 点后，直接去买面包即可。

- 其余情况分 直接买 和 等到 $20$ 点再去买 两种情况进行比较，输出最小值即可。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	double a,b,h,d,c,n;
	scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&h,&d,&c,&n);
	printf("%.4lf",a>=20?c*0.8*ceil(h/n):min(c*ceil(h/n),c*0.8*ceil((h+((20-a)*60-b)*d)/n)));	
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

这题似乎没有黄题的难度。

#### 思路：只要醒来时过了20点就直接去买面包，否则就判断是20点去买面包还是立刻去买面包更便宜。

**重点：**

1. 注意小面包的个数要向上取整，这里要运用到一个 ceil 函数。~~我也是看其他题解学来的······~~

2. 题目中“面包有 $20$ 的特别折扣”是指面包的价格变为原来的$(1-20)$%，也就是原来的$80$%，计算时乘$0.8$即可。

代码：~~(可能不需要)~~

```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c,d,e,f,t;
int main()
{
	cin>>a>>b>>c>>d>>e>>f;
	if(a>=20)//如果过了20点
	{
		printf("%.4lf",ceil(c/f)*(e*0.8));//直接输出直接去买面包的价格
	}
	else
	{
		t=(20-a-1)*60+60-b;//离20点还有多久
		printf("%.4lf",min(ceil(c/f)*e,ceil((c+t*d)/f)*(e*0.8)));//输出直接去买面包的价格和20点去买面包的价格中的较小值
	}
	return 0;
}
```

---

## 作者：dang_dang (赞：0)

这道题不难。

一句吐槽：这是神马翻译啊！
#### 翻译
本文作者的翻译。

在 $hh$:$dd$ 醒来以后， Andrew 发现他又忘记去喂他唯一的一只猫了（你猜为啥他只有一只猫）。现在的这只猫的饥饿水平是 $H$ 点，如果你不喂它，他每分钟的饥饿值就会增加 $D$ 点。

Andrew 加的附近有一家面包店，可是只卖一种面包。一个面包价值 $C$ 卢布，可以降低 $D$ 点饥饿值。面包店在下午 $8:00$ 后开始做优惠，打八折（$×0.8$）。在这里，我们假设他买面包不需要时间。如果猫的饥饿值小于等于 0 ，就算猫被喂饱了。

现在，求喂饱猫最少需要多少卢布。

#### 开始讲思路了
首先，我们先判断时间，进行分类讨论：

如果时间比晚上八点晚了，那么就直接过去买8折的小面包来喂猫。

如果还没到八点，那么我们再次进行分情况讨论：
1. 等到八点，去买 8 折小面包
2. 直接去买小面包
这两种情况，看哪一种所需花的价格最少，选择花费最少的那个方案并输出。
然后算出答案就好啦！

#### 答案
给有需要者：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int hour,m;
	cin>>hour>>m;
	double res; 
	int c,n,h,d;
	cin>>h>>d>>c>>n; //基本的输入
	if(hour>=20)
	{
		if(h%n!=0) h+=n;
		res=h/n*(0.8*c);
	} //八点以后，直接去买
	else
	{
		int eta=1200-hour*60-m; //计算到八点前的时间
		int h2=h+eta*d; //如果等到8点，猫有多饿
		if(h2%n!=0) h2+=n;
		if(h%n!=0) h+=n; //向上取整
		double aft=h2/n*(0.8*c); //八点以后买小面包的价钱
		int now=h/n*c;//现在就去买的钱
		res=min(aft,now);//找便宜的
	}
	printf("%.4lf",(double)res); //输出
	return 0; //返回值，一定要加
}
```
结束。

**管理们，你们辛苦了！给过一下吧！**

---

## 作者：_Spectator_ (赞：0)


[可能更好的食用体验](https://www.luogu.com.cn/blog/523641/cf955a-feed-the-cat-ti-xie)

[题目传送门](https://www.luogu.com.cn/problem/CF955A)

------------
这题很简单，直接上代码

```cpp
#pragma G++ optimize(2)
#include<bits/stdc++.h>
using namespace std;
double hh,mm,h,d,c,n;
int main()
{
	ios::sync_with_stdio(false);
	cin>>hh>>mm>>h>>d>>c>>n;
	if(hh>=20)//如果已经过了20:00，直接以折扣后的价格购买 
	{
		double p=ceil(h/n)*c*0.8;//计算折扣后的价格，其中ceil()函数表示向上取整 
		printf("%.4lf",p);//使用printf保留4位小数输出 
	}
	else //还没过20:00时，分情况计算 
	{
		double p1=ceil(h/n)*c;//计算醒来后直接去买面包的价钱
		h+=((20-hh)*60-mm)*d;//如果等到20:00再去买面包，增加猫的饥饿值
		double p2=ceil(h/n)*c*0.8;//计算折扣后的价格
		printf("%.4lf",min(p1,p2));//输出两个价格之间的较小值 
	}
	return 0;
}

```
唯一要注意的是翻译中的一句话：
>“因此从 20:00 开始，面包有 $20$ 的特别折扣”

其中有 $20$ 的特别折扣指价格降低$20$%，即将价格乘$0.8$

**xt__温馨提示：**

**${\color{brown}\colorbox{White}{题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $**

---

## 作者：WinterRain208 (赞：0)

CF955A Feed the cat

不得不说小数处理真的很烦。

思路：题目不涉及跨天，按当前时间分类讨论计算即可。

如果可享受优惠，那么不等直接去买是最优的。

反之讨论：是在现在没有优惠的基础上去买还是等到20：00再去买，比较。

代码：

```cpp
#include<bits/stdc++.h> 

using namespace std;

int main(){
    double hh,mm,h,d,c,n;
    cin>>hh>>mm>>h>>d>>c>>n;
    if(hh>=20)printf("%0.4f",c*0.8*(ceil(h/n)));
    else printf("%0.4f",min(c*0.8*ceil((h+((20-hh)*60-mm)*d)/n),c*ceil(h/n)));  
    return 0;
}

```

代码还是推荐写简洁一点。

---

