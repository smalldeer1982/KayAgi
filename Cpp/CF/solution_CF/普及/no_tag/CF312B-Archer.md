# Archer

## 题目描述

小R是一个弓箭手，他正在与 $Zanoes$ 进行弓箭手之间的对决。他们轮流尝试着射中目标，小R先射。小R每次射中目标的概率是 $\frac{a}{b}$ , $Zanoes$ 的概率是 $\frac{c}{d}$。
首先射中目标的人获胜。

请计算小R获胜的概率。
小R是一个弓箭手，他正在与 $Zanoes$ 进行弓箭手之间的对决。他们轮流尝试着射中目标，小R先射。小R每次射中目标的概率是 $\frac{a}{b}$ , $Zanoes$ 的概率是 $\frac{c}{d}$。
首先射中目标的人获胜。

请计算小R获胜的概率。

## 样例 #1

### 输入

```
1 2 1 2
```

### 输出

```
0.666666666667```

# 题解

## 作者：到底几只鱼呢 (赞：9)

## 谨以此篇感谢Acc大佬带我入门简单概率！

## Solution:

### 前置：全概率公式

在概率空间 $(\Omega,F,P)$ 中，若一组事件 $A1,...An$ 两两不相
容且和为$\Omega$，则对任意事件 $B$ 都有

$$P(B) = \sum_{i=1}^{n}P(A_i)P(B|A_i)$$

那么对于这道题来说获胜的概率推导如下：

设 $p=\frac{a}{b}$ , $q=\frac{c}{d}$ ,获胜的概率 $ans$ 即为：

$$ans=p+(1-p)(1-q)p+[(1-p)(1-q)]^2p+[(1-p)(1-q)]^3p+...$$

设 $(1-p)(1-q)=x$ ,提出 $p$ 则有：

$$ans=p(1+x+x^2+x^3+...)$$

对于 
$$1+x+x^2+x^3+...$$

考虑等比数列求和则有：

$$\frac{1-x^n}{1-x}$$

又因为 $x<1$ ,则 $n$ 趋于无穷大时 $x^n$ 趋近于 $0$ ，
则原式化为：

$$\frac{1}{1-x}$$

$$ans=\frac{p}{1-x}$$

### Code:

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#define inf 0x3f3f3f3f
using namespace std;

int main() {
	double a,b,c,d;
	scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
	printf("%.12lf",(double)(a/b)/(double)(1-(1-a/b)*(1-c/d)));
	return 0;
}
```




---

## 作者：nekko (赞：5)

设$f$表示小$R$射中对方的概率

则$$\huge f=\frac{a}{b}+(1-\frac{a}{b})(1-\frac{c}{d})f$$

化简得$$\huge f=\frac{\frac{a}{b}}{1-(1-\frac{a}{b})(1-\frac{c}{d})}$$

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	double a, b, c, d; cin >> a >> b >> c >> d;	 
	double ans = 0;
	ans = (a / b) / (1 - (1 - a / b) * (1 - c / d)); 
	printf("%.12lf\n", ans);
}
```

---

## 作者：communist (赞：5)

容易算出这人第一次胜利的概率，第二次的，第三次的……

好像可以无限乘下去

但是这题精度卡到$1e-6$

不妨设一个$eps$，当这次胜率小于$eps$时，就$break$掉，反正它已经不影响答案了

我设的是$eps=1e-12$

```
#include<iostream>
#include<cstdio>
using namespace std;
const double eps=1e-12;
int a,b,c,d;
double ans,g[2];
int main()
{
    scanf("%d%d%d%d",&a,&b,&c,&d);
    g[0]=1.0*a/b,g[1]=1.0*(d-c)/d;
    double tmp=1;
    while(tmp>eps)
    {
        ans+=tmp*g[0];
        tmp*=(1-g[0])*g[1];
    }
    printf("%.12lf\n",ans);
    return 0;
}
```

---

## 作者：Grisses (赞：2)

两个弓箭手 A 和 B，命中的概率分别是 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$，A 先射。谁先射中对方就赢，问 A 赢的概率。

由于对精度的要求比较小，我们可以枚举在第几回合 A 获胜。对于第 $i$ 回合，想要进行的这里，要求前 $i-1$ 个回合两人全部射空，概率为 $(1-\dfrac{a}{b})^{i-1}\times(1-\dfrac{c}{d})^{i-1}$。然后 A 命中了，概率为 $\dfrac{a}{b}$。所以乘起来就是 $(1-\dfrac{a}{b})^{i-1}\times(1-\dfrac{c}{d})^{i-1}\times\dfrac{a}{b}$。然后对于 $\forall i\in[1,1000000]$ 算出来累加就行了（到 1000000 的原因是到怎么大过后算出来的结果远小于 $10^{-6}$ 了，不会有什么影响）。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int a,b,c,d;
  double p,q,x,ans;
  signed main()
  {
      scanf("%d%d%d%d",&a,&b,&c,&d);
      p=1.0*a/b;
      q=1.0*c/d;
      int k=1e6;
      x=1;
      while(k--){
          ans+=x*p;
          x*=(1-p)*(1-q);//累乘
      }
      printf("%.10lf",ans);
      return 0;
  }
```

---

## 作者：lxgw (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF312B)
## 题意
小R$Zanoes$ 进行对决。他们轮流尝试着射中目标，小R先射。小R有$\frac{a}{b}$的概率赢 , $Zanoes$ 有  $\frac{c}{d}$ 的概率赢，问小R有多少概率赢。
## 思路
设第 n 轮（第 n 轮时到小R射击）时小R的获胜概率为 $f_n$ ，可求得 $f_n$ = $f_{n-2}$ （小R的上一轮获胜概率）$\times (1-\frac{a}{b})$ (小R没获胜) $\times (1-\frac{c}{d})$（对手也没获胜） $+\frac{a}{b}$（这轮获胜的概率），所以可以不断算下去直到满足精度条件。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const double jd=1e-8;//精度要求
int a,b,c,d;double ans,g1,g2;
int main()
{
    cin>>a>>b>>c>>d;
    g1=1.0*a/b,g2=1.0*(d-c)/d;
    double tmp=1;
    while(tmp>jd)
        ans+=tmp*g1,tmp*=(1-g1)*g2;//当没满足精度条件时就不断计算下去
    cout<<fixed<<setprecision(8)<<ans;//保留八位小数输出
    return 0;
}
```


完结撒花~

谢谢 qwq

---

## 作者：qhztz (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF312B)
## 思路：
不妨设 $r$ 表示小R射中对方的概率

则$ r=\frac{a}{b}+(1-\frac{a}{b})(1-\frac{c}{d})r $

化简得$ r=\frac{\frac{a}{b}}{1-(1-\frac{a}{b})(1-\frac{c}{d})} $

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c,d,r;
int main(){
	cin>>a>>b>>c>>d;
	r=(a/b)/(1-(1-a/b)*(1-c/d)); //根据公式算胜率
	printf("%.12lf\n",r);//根据题目输出
}
```
 拜拜 qwq


---

## 作者：copper_ingot (赞：0)

[luogu](https://www.luogu.com.cn/problem/CF312B)

[CF](https://codeforces.com/problemset/problem/312/B)

[可能更好的阅读体验](https://www.luogu.com.cn/article/l08ymzfi)

小 R 第一次射中获胜的概率显然是 $\dfrac{a}{b}$。

而小 R 第二次射中获胜的概率是（小 R 第一次射不中的概率 $\times$ Zanoes 第一次射不中的概率 $\times$ 小 R 第二次射中的概率），即 $\dfrac{b-a}{b}\times\dfrac{d-c}{c}\times\dfrac{a}{b}$。

以此类推，小 R 第 $i$ 次射中获胜概率是 $(\dfrac{b-a}{b}\times\dfrac{d-c}{c})^{i-1}\times\dfrac{a}{b}$。

则小 R 的总获胜概率就是他每次获胜的概率之和，即 
$$\sum^{\infin}_{i=1} [(\frac{b-a}{b}\times\frac{d-c}{c})^{i-1}\times\frac{a}{b}] = \frac{a}{b}\times\sum^{\infin}_{i=1} (\frac{b-a}{b}\times\frac{d-c}{c})^{i-1}$$

由等比数列的求和公式 $S_i = \dfrac{1 -q^i}{1-q}$ 得
$$\frac{a}{b}\times\sum^{n}_{i=1} (\frac{b-a}{b}\times\frac{d-c}{c})^{i-1} = \frac{a}{b}\times\frac{1-(\frac{b-a}{b}\times\frac{d-c}{c})^n}{1-\frac{b-a}{b}\times\frac{d-c}{c}}$$

当 $n \to \infin$ 时，因为 $\dfrac{b-a}{b}\times\dfrac{d-c}{c}<1$，所以 $(\dfrac{b-a}{b}\times\dfrac{d-c}{c})^n \to 0$。

所以原式 $=\dfrac{a}{b}\times\dfrac{1}{1-\dfrac{b-a}{b}\times\dfrac{d-c}{c}}$，输出答案即可。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	double a, b, c, d;
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	printf("%.12lf", (a / b) / (1 - (b - a) / b * (d - c) / d));
	return 0;
}
```

---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF312B)

### 思路

~~直接暴力。~~

我们一次一次看。

首先是第一次它就射中了，概率为 $\dfrac{a}{b}$。

然后看第三次如果他射中了，首先要保证第三次以前都没有射中，然后让第三次射中，就是 $\dfrac{b-a}{b}\times \dfrac{d-c}{d} \times \dfrac{a}{b}$。

以此类推，只需要保证在第 $2\times n+1 $ 次时，算出来的概率时大于 $10^{-6}$ 就算可行方案，否则就没有必要在算下去了。（精度）

所以我们可以直接定义一个 $n=10^6$ 的常数来方便我们实现。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	double a,b,c,d;
	double ans=0,now=1;
	cin>>a>>b>>c>>d;
	for(int i=1;i<=int(1e6);++i)
	{
		now=now*a/b;
		ans+=now;
		now=now*(b-a)/a*(d-c)/d;
	}
	printf("%.7lf",ans);
}
```

---

## 作者：qwq___qaq (赞：0)

首先，对于小 R，如果他第 $i$ 次射中，那么前 $i-1$ 次两人都未射中，那么我们可以得到：

对于第 $i$ 次射中，其概率为 $(1-\dfrac{a}{b})^{i-1}(1-\dfrac{c}{d})^{i-1}\dfrac{a}{b}$。

我们可以枚举一定的次数，比如 $10^4$ 次，那么答案就是 $\sum\limits_{i=1}^{10000}(1-\dfrac{a}{b})^{i-1}(1-\dfrac{c}{d})^{i-1}\dfrac{a}{b}$。

---

## 作者：一只大龙猫 (赞：0)

这是一篇 **Python** 题解，文末也会附上 C++ 代码。

我们先一起来推一推公式。

设小 R 第 $i$ 次射箭后射中目标且获胜的概率为 $S_i$，则小 R 获胜的概率为 $\sum_{i=1}^{+\infty}S_i$。

其中，$S_1$ 为小 R 第一次就射中的概率，即 $\frac{a}{b}$；

$S_2$ 为小 R 第一次没有射中，且 Zanoes 第一次没有射中，且小 R 第二次射中的概率，即 $\frac{b-a}{b} \times \frac{d-c}{d} \times \frac{a}{b}$；（$\frac{b-a}{b}$ 为小 R 第没有射中的概率，$\frac{d-c}{d}$ 为 Zanoes 没射中的概率，$\frac{a}{b}$ 为小 R 射中的概率。）

$S_3$ 为小 R 第一次没有射中，且 Zanoes 第一次没有射中，且小 R 第二次没有射中，且 Zanoes 第二次没有射中，且小 R 第三次射中的概率，即 $\frac{b-a}{b} \times \frac{d-c}{d} \times \frac{b-a}{b} \times \frac{d-c}{d} \times \frac{a}{b}$；

……

容易发现，这就是一个首项为 $\frac{a}{b}$，公比为 $\frac{b-a}{b} \times \frac{d-c}{d}$ 的无限等比数列。因为 $| \frac{b-a}{b} \times \frac{d-c}{d} |<1$（证明过程在[这里](https://www.luogu.com.cn/paste/jipzdnwo)），所以这还是一个**无限递缩等比数列**。

根据[无限递缩等比数列求和公式](https://baike.baidu.com/item/%E6%97%A0%E7%A9%B7%E9%80%92%E9%99%8D%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F/5601350?fr=aladdin)，我们可以得出 $\sum_{i=1}^{+\infty}S_i=\frac{\frac{a}{b}}{1-\frac{b-a}{b} \times \frac{d-c}{d}}$，这就是小 R 获胜的概率。

代码如下：

Python

```python
a,b,c,d=map(int,input().split())
print("%.8f" % ((a/b)/(1-((b-a)/b)*((d-c)/d))))
```

C++

```cpp
#include<iostream>
#include<iomanip>
using namespace std;
int a,b,c,d;
int main(){
	cin>>a>>b>>c>>d;
	cout<<fixed<<setprecision(8)<<((double)a/b)/(1.0-(((double)b-a)/b)*(((double)d-c)/d));
    return 0;
}
```

---

## 作者：Mysterious_Mini (赞：0)

这是本蒟蒻的第 $4$ 篇题解。
### 思路：
概率 + 推公式。

我们假设一回合中 小R 与 Zanoes 均射箭一次。

设射中的概率为 $ans$。

小R 先射：

$1.$ 射中了：

概率为 $\frac{a}{b}$。

$2.$ 没射中：

这一分支概率为 Zanoes 本回合没射中的概率 $×$ 小R 本回合没射中的概率 $×$ $ans$，

即 $(1-\frac{a}{b})(1-\frac{c}{d})ans$。

∴ $ans=(1-\frac{a}{b})(1-\frac{c}{d})ans+\frac{a}{b}$

∴ $(1-(1-\frac{a}{b})(1-\frac{c}{d}))ans=\frac{a}{b}$

∴ $ans=\frac{\frac{a}{b}}{1-(1-\frac{a}{b})(1-\frac{c}{d})}$

完结撒花！
### 代码：
```cpp
#include<cstdio>
using namespace std;
double a, b, c, d, tmp1, tmp2;
int main()
{
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	tmp1 = a / b, tmp2 = c / d;
	printf("%.8lf\n", tmp1 / (1 - (1 - tmp1) * (1 - tmp2))); //注意精度
	
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/48490492)：Nice！

求过+求赞QwQ

---

## 作者：Mysterious_Cat (赞：0)

### 题目思路：递推求期望
**不妨设$f$为射中敌方的概率**  
我们模拟一下小R的情况  
1. 射中：概率为$\frac{a}{b}$ 
2. 射不中：概率为$1-\frac{a}{b}$，此时交给对手射箭，有$1-\frac{c}{d}$的概率射不中，重新交还给小R射箭，此时概率为$(1-\frac{a}{b})(1-\frac{c}{d})f$   

易知 $f=\frac{a}{b}+(1-\frac{a}{b})(1-\frac{c}{d})f$  
即 $f=\frac{\frac{a}{b}}{1-(1-\frac{a}{b})(1-\frac{c}{d})}$

### Code:
```cpp
#include<cstdio>
using namespace std;
  
int main()
{
	double a, b, c, d;
  	scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
  	printf("%.12lf", (a / b) / (1 - (1 - a / b) * (1 - c / d)));

	return 0;
}
```


---

## 作者：lsw1 (赞：0)

小R要想胜利，那么要么射中对手，要么两人都没射中，然后开始下一轮射击，**且下一轮胜利的概率和这一轮的相等。**

$\dfrac{a}{b}$ 表示小R射中对手的概率， $(1-\dfrac{a}{b})\times(1-\dfrac{c}{d})\times P$ 表示两人都没射中目标，之后小R胜利的概率。

设 $P$ 为小R胜利的概率，则有：
$$P=\dfrac{a}{b}+(1-\dfrac{a}{b})\times(1-\dfrac{c}{d})\times P$$
化简得：
$$P=\dfrac{ad}{ad+bc+ac}$$
```cpp
#include <iostream>
using namespace std;
int main()
{
	double a,b,c,d;
	cin >> a >> b >> c >> d;
	cout << (a * d) / (a * d + b * c - a * c);
	return 0;
}
```

---

## 作者：Nozebry (赞：0)

## $Problems$
小 $R$ 和 $Zanoes$ 都是弓箭手。小 $R$ 准备与 $Zanoes$ 举行一场射箭比赛，小 $R$ 第一个射箭，然后两人轮流进行射箭，小 $R$ 投中靶子的概率为 $\frac{a}{\ b}$ ， $Zanoes$ 投中靶子的概率为 $\frac{c}{\ d}$ ，谁第一个投中靶子谁就获胜，求 小 $R$ 赢得比赛的概率。
## $Answer$
我们其实不难发现，这道题其实是一道等比数列的题。。。

设一个等比数列的首项是 $a_1$ ,公比是 $q$ ，数列前 $n$ 项和是 $S_n$。

当公比不为 $1$ 时$S_n=a_1+a_1q^1+a_1q^2+...+a_1q^{n-1}$

将这个式子两边同时乘以公比 $q$ ，得$S_nq=a_1q^1+a_1q^2+...+a_1q^{n-1}+a_1q^n$


两式相减，得 $Sn(1-q)=a_1-a_1q^n$

所以，当公比不为 $1$ 时，等比数列的求和公式为 $Sn=\frac{[a_1(1-q^n)]}{1-q}$

对于一个无穷递降数列，数列的公比小于 $1$ ,当上式得 $n$ 趋向于正无穷大时，分子括号中的值趋近于 $1$ ，取极限即得**无穷递减数列求和公式**$S=\frac{a_1}{1-q}$
## $Code$
```pascal
var
    a,b,c,d:double;
begin
    readln(a,b,c,d);
    writeln(a/b/(1-(1-a/b)*(1-c/d)):0:12);
end.
```

---

