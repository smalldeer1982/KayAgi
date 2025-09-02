# Falling Anvils

## 题目描述

For some reason in many American cartoons anvils fall from time to time onto heroes' heads. Of course, safes, wardrobes, cruisers, planes fall sometimes too... But anvils do so most of all.

Anvils come in different sizes and shapes. Quite often they get the hero stuck deep in the ground. But have you ever thought who throws anvils from the sky? From what height? We are sure that such questions have never troubled you!

It turns out that throwing an anvil properly is not an easy task at all. Let's describe one of the most popular anvil throwing models.

Let the height $ p $ of the potential victim vary in the range $ [0;a] $ and the direction of the wind $ q $ vary in the range $ [-b;b] $ . $ p $ and $ q $ could be any real (floating) numbers. Then we can assume that the anvil will fit the toon's head perfectly only if the following equation has at least one real root:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77B/aced119984763a9d9e5bf9bcf349dec6b5f37451.png)Determine the probability with which an aim can be successfully hit by an anvil.

You can assume that the $ p $ and $ q $ coefficients are chosen equiprobably and independently in their ranges.

## 样例 #1

### 输入

```
2
4 2
1 2
```

### 输出

```
0.6250000000
0.5312500000
```

# 题解

## 作者：__yun__ (赞：4)

### 前置芝士
一元二次方程判别式。

一元二次方程 $ax^2+bx+c=0$ 的判别式 $\Delta =b^2-4ac$。  
当 $\Delta \geq 0$ 时，方程有实根。 

详见[百度百科](https://baike.baidu.com/item/%E5%88%A4%E5%88%AB%E5%BC%8F/10834494?fr=ge_ala)。
### 题意
求一个一元二次方程 $ x^2+\sqrt{p} x+q=0,p \in [0,a],q \in [-b,b]$ 有实数根的概率。
### 思路
一元二次方程 $ x^2+\sqrt{p} x+q=0,p \in [0,a],q \in [-b,b]$ 的判别式 $\Delta = (\sqrt{p})^2 - 4 \times 1 \times q=p-4q$，$\Delta \geq 0$ 也就是 $p \geq 4q$ 时方程有实根。  

题目就转换为了求 $p \geq 4q,p \in [0,a],q \in[-b,b]$ 的概率。

分类讨论：

1. $b=0$ 时，$q=0$，则一定有 $p \geq 4q$，概率为 $1$。 

2. $a=0$ 时，$p=0$，$q$ 有 $0.5$ 的概率小于 $0$，概率为 $0.5$。

3. $b > \frac{a}{4}$ 时，情况如下图：  

![长](https://cdn.luogu.com.cn/upload/image_hosting/22rwjm4x.png)

$ S_{\text{阴影}} = \frac{a(2b+\frac{a}{4})}{2} $，$P(p \geq 4q) = \frac{S_{\text{阴影}}}{S_{\text{总}}}=\frac{a(2b+\frac{a}{4})}{4ab}=\frac{2b+\frac{a}{4}}{4b}$。

4. $b \leq  \frac{a}{4}$ 时 ，情况如下图：

![宽](https://cdn.luogu.com.cn/upload/image_hosting/fxj49rqp.png)

$S_{\text{空白}} =\frac{4b^2}{2} =2b^2$，$P(p \geq 4q) = \frac{S_{\text{阴影}}}{S_{\text{总}}}=1-\frac{S_{\text{空白}}}{S_{\text{总}}}=1- \frac{2b^2}{2ab}=1 - \frac{b}{a}$。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b;
int t;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		if(b==0){
			cout<<1<<endl;
			continue;
		}
		if(a==0){
			cout<<0.5<<endl;
			continue;
		}
		if(b>a/4) printf("%.10f\n",(2*b+a/4)/(4*b));
		else printf("%.10f\n",1.0-b/a);
	}
	return 0;
}
```

---

## 作者：摸鱼酱 (赞：2)

给定$a,b$,$p∈[0,a],q∈[-b,b]$，在$p,q$随机取值的情况下，求方程$x^2+\sqrt p·x+q=0$有实数根的概率。

显然就是要求$p\ge4q$的概率，我们让$q∈[-4b,4b]$，让$p\ge q$即可。

让$(p,q)$放到平面直角坐标系中，显然满足要求的点的坐标在直线$y=x$**下方**，于是分下图两种情况考虑答案。

![](https://cdn.jsdelivr.net/gh/moyujiang/piccdn@02116a61623dc763cfa044f9eb2b92f730f70d8d/2021/02/06/5beeed7e16b2a71b6ffea83195ecf370.png "a<4b")

![](https://cdn.jsdelivr.net/gh/moyujiang/piccdn@c7a2446296b4fd68bd7107876a9ef5ddd4cbfd62/2021/02/06/0370db4bd4de41241208a77c66ec63f6.png "a>4b")

显然，答案就分$a<4b$时的$\frac{(8b+a)a}{2*8ab}$和$a>4b$时的$\frac{4ab+\frac{(2a-4b)b}{2}}{8ab}$，相等时随便归到一类即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;cin>>t;
	while(t--){
		double a,b;
		scanf("%lf%lf",&a,&b);
		b*=4;
		if(b==0)puts("1.0");
		else if(a==0)puts("0.5");
		else if(a<b)printf("%.8lf\n",(2.0*b+a)*a/(a*b*4.0));
		else printf("%.8lf\n",(a*b+(2.0*a-b)*b/2.0)/(a*b*2.0));
	}
	return 0;
}
```

---

## 作者：Grisses (赞：2)

# upd:

2023/8/10：有个bug，改一下

---

问一个一元二次方程 $x^2+\sqrt{p}+q=0,p\in[0,a],q\in[-b,b]$ 有实数根的概率。

- 当 $b=0$ 时，显然概率是 1。

- 当 $a=0$ 时，概率为 0.5（因为只有当 $0\le b$ 时才行）。

- 否则就是看 $4q\le p$ 的概率。

而我们可以将所有情况看成一个矩形，概率就是矩形与 $4q\le q$ 这个半平面的交的面积除以整个矩形的面积。那么，怎么求这个交的面积呢？ ~~当然是半平面交。~~ 其实我们发现就只有一条直线，所以可以直接分类讨论。

如果是下图这种情况，即当 $b\le\dfrac{a}{4}$ 时，我们需要求一个梯形的面积，结合题目，我们知道上底为 $b$，下底为 $b+\dfrac{a}{4}$，高为 $a$，所有面积 $S=\dfrac{[b+(b+\dfrac{a}{4})]\times a}{2}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/aovafgvd.png)

对于另一种情况，即当 $b>\dfrac{a}{4}$ 时,我们考虑割补，易求出 $S=2ab-\dfrac{b\times 4b}{2}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/l8p24b6n.png)

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t,a,b;
  signed main()
  {

      scanf("%d",&t);
      while(t--){
          scanf("%d%d",&a,&b);
          if(b==0)puts("1.000");//感谢yun和qq815741912，应该先判断b=0，因为 0 0 是有解的，答案为1
          else if(a==0)printf("0.500000\n");
          else{
              printf("%.10lf\n",1.0-1.0*(2*b-(1.0*a/4))*a/2/(a*2*b));
          }
      }
      return 0;
  }
```

---

## 作者：ZhongYuLin (赞：0)

要求 $p\geq4q$ 的概率，看起来就很可以积分。

先特判 $a=0$ 和 $b=0$。然后开始积分。

当 $a\leq4b$ 时，答案为:

$$\frac{1}{a} \int_{0}^{a}\frac{\frac{1}{4}x +b}{2b}  \mathrm{d}x$$

$$\frac{1}{2}+\frac{a}{16b}$$

当 $a\geq 4b$时，答案为:

$$\frac{1}{a}( \int_{0}^{4b}\frac{\frac{1}{4}x +b}{2b}  \mathrm{d}x+a-4b)$$

$$1-\frac{b}{a}$$

---

## 作者：黑影洞人 (赞：0)

题意：

给定 $a, b(0\le a, b\le 10^6),a,b\in Z_+$，求方程 $x^2+\sqrt px +q$ 有至少一个实根的概率，其中 $p\in [0, a], q\in [-b, b]$，$p, q\in R$ ，在上述区间内等概率分布。

很显然，我们要把一元二次方程的条件转化。

>$x^2+\sqrt px +q$ 有至少一个实根

即

$$Δ=p-4q\geq 0 ,p\in [0,a],q\in [-b,b], p,q\in R $$

对于这个问题，我们可以进行转化。

![](https://cdn.luogu.com.cn/upload/image_hosting/5tdu57i6.png)

这是 $a<4b$ 的情况，还有 $a\geq 4b$ 的情况，很类似，运用简单的数学知识就可以求出，图片就不展示了。

值得注意的是，当 $a=0$ 时，仅存在 $p$ 轴左边的面积，概率为 $0.5$。

当 $b=0$ 时，全部矩形被包括，概率为 $1$。

对于一般情况：

$a<4b,P(Δ\geq 0)=0.5+\frac{\frac{a\times \frac{a}{4}}{2}}{2ab}$ 

$a\geq 4b,P(Δ\geq 0)=0.5+\frac{\frac{a+(a-4b)\times 4b}{2}}{2ab}$

柿子已经给出了，代码就不展示了。



---

## 作者：Astatinear (赞：0)


[题目传送门](https://www.luogu.com.cn/problem/CF77B)

~~特判烦死了。~~

显然，要让这个方程有实根，就要保证 $\Delta\ge 0$，及 $p\ge 4\times q$

我们可以考虑面积法。

先根据样例1来解释一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/zpbuc2cs.png)

根据上图，对于我们将 $q$ 看作 $x$，$p$ 看作 $y$ 建立平面直角坐标系。首先，全集就是整个画出的长方形面积。显然，对于左半部分 $x<0$ 的，都能满足有实根。然后对于所有在直线 $y=4x$ 直线及以上部分的区域也都可以保证 $y\ge 4x$，及存在实根。

然后我们用存在实根的面积去除以总面积就是概率了。

要注意的就是看 $y=4x$ 是与长方形的上面交，还是与长方形的侧面交，一边来算面积。

对于 $a,b=0$ 的情况也需要特判。（比较简单，自己思考答案。）

详情见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long double a,b;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a>>b;
		if(b<1e-9)//特判 
		{
			puts("1.0000000");
			continue;
		}
		else if(a<1e-9)
		{
			puts("0.50000000");
			continue;
		}
		double x=a/4.0;
		if(x<b)//当x交在了长方形的上方，是一个三角形 
		printf("%.7Lf\n",(x*a*0.5+b*a)/(2*b*a));
		else//当x交在了长方形的侧面，是一个梯形 
		{
			double y=b*4.0;
			y=a-y;
			printf("%.7Lf\n",(b*a+(a+y)*b/2.0)/(2*b*a));
		}
	}
}
```

---

## 作者：Unnamed114514 (赞：0)

因为有唯一实数根，所以 $\Delta\ge0$，所以 $p\ge4q$。

我们可以做出一个关于 $p$，$q$ 取值范围的 $a\times2b$ 的矩形，此时，我们画出 $y=4x$ 的图像。

如图，阴影部分是满足题意的部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/l6qirl9j.png)

此时，我们就把概率转化为面积之比，我们把阴影部分分为一个长方形和一个三角形，总面积为 $ab+\dfrac{\dfrac{a}{4}a}{2}=ab+\dfrac{a^2}{8}$，那么概率为 $\dfrac{ab+\dfrac{a^2}{8}}{2ab}=\dfrac{a+8b}{16b}$，此时发现 $a\le4b$。

但是，这只是一种情况，如果 $y=4x$ 经过的是矩形的宽，情况会有变化。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/av0a96fk.png)

此时我们的阴影会分割为一个矩形和一个梯形，总面积为 $ab+\dfrac{(a+a-4b)b}{2}=ab+ab-2b^2=2ab-2b^2$，概率就是 $\dfrac{2ab-2b^2}{2ab}=\dfrac{a-b}{a}$，此时 $a\ge4b$。

综上，当 $a\le4b$ 时，答案为 $\dfrac{a+8b}{16b}$；否则答案为 $\dfrac{a-b}{a}$。

注意：分母不为 $0$，所以当 $b=0$ 时，$p\le0$ 答案为 $1$；当 $a=0$ 时，$q\le0$，此时答案为 $\dfrac{1}{2}$。

时间复杂度 $O(T)$。

---

## 作者：XL4453 (赞：0)

### 解题思路：

几何概型的概率题。

注：本题解没有配图，建议没有学过计算几何（选修一）的自己画图理解，~~或者去学一下计算几何然后把图刻到脑子里~~。

根据一元二次方程的求根公式，方程有根的充要条件是：$0\le b^2-4ac$，带到这题里就是 $0\le p-4q$，也就是要求 $4q\le p$，此时两者的区间范围为 $[-4b,4b]$ 和 $[0,a]$。

将 $[-4b.4b]$ 投影到 $y$ 轴上，$[0,a]$ 投影到 $x$ 轴上，每一次随机选点就是随机一个点 $(x_0,y_0)$，其中 $x_0\in [0,a]$，$y_0\in [-4b,4b]$，条件就变成了这个选出的点在直线 $x-y=0$ 上或者下方（或许这边不用那么严格地讨论，反正对答案没有影响）。再次转化问题，就是求出 $(0,b)$、$(0,-b)$、$(a,b)$ 和 $(a,-b)$ 这四个点围成的矩形在 $x-y=0$ 下方的面积。

对应到坐标轴上，总可能性的面积是 $8ab$，然后有一半，也就是 $[-4b,0]$ 那一半一定可行，主要讨论上面的那一部分。

这里有：当 $a \le 4b$ 时，围成一个三角形，面积为 $\dfrac{a^2}{2}$。

反之，则构成一个梯形，上底为 $a-4b$，下底为 $a$，高为 $4b$，有面积为 $\dfrac{(2a-4b)4b}{2}=4b(a-2b)$。

但是这一种算法比较繁，直接用总面积 $8ab$ 减去左上角的 $\dfrac{16b^2}{2}=8b^2$，立刻就有了结果。

对于前者，化简结果为：$\dfrac{8ab+a^2}{16ab}$。

对于后者，化简结果为：$\dfrac{ab-b^2}{ab}$。

如果后一种减去的方法，直接得到的是 $1-\dfrac{b}{a}$，和上面那个是等价的。

---
~~要不是没带草稿纸，谁会在题解里推公式啊。~~

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int T;
double ans,a,b;
double calc(double a,double b){
	if(b==0)return 1;
	if(a==0)return 0.5;
	if(a<4*b)return ((8*a*b)+(a*a))/(16*a*b);
	return 1-b/a;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lf%lf",&a,&b);
		printf("%.8lf\n",calc(a,b));
	}
	return 0;
}
```


---

## 作者：Acc_Robin (赞：0)


## 题目描述

题目链接:[CF77B](http://codeforces.com/problemset/problem/77/B)

题意：

　　给定实数$a, b(0\le a, b\le 10^6)$，求方程$x^2+\sqrt px +qx=0$有至少一个实根的概率，其中$p\in [0, a]$, $q\in [-b, b]$，$p$, $q$均是实数，在上述区间内等概率分布。

## 解决方案

　　易知若原方程有至少一个实根，当且仅当

$$
\Delta=p-4q \ge 0
$$

　　令$x=4q,y=p$，$x\in[-4b,4b],y\in[0,a]$，则

$$
y-x\ge 0
$$

　　以$b=2$，$a=4$为例作出图像，有

![](https://accrobin.github.io/assets/image/CF77B/001.jpg)

　　其中矩形$ABCD$表示$x$和$y$的取值范围，而四边形$ABOE$表示在$x$和$y$的取值范围下满足$y-x \ge 0$的部分.

　　因为$x$和$y$在取值范围内均匀分布，所以$\frac{S_{ABOE}}{S_{ABCD}}$即为最终答案.

　　本题注意分类讨论！

## 代码：

```cpp
//CF77B Falling Anvils
//2021-3-13
#include<cstdio>
#include<algorithm>
namespace Acc{
	long long a,b;
	void work(){
		scanf("%lld%lld",&a,&b);
		if(!b)return (void)(printf("1\n"));
		if(!a)return (void)(printf("0.5000000000\n"));
		printf("%.10f\n",(double)(std::max(0ll,a-4*b)+a)*std::min(a,4*b)/(16*a*b)+0.5);
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--) Acc::work();
	return 0;
}
```

---

## 作者：brealid (赞：0)

给定实数$a, b(0\le a, b\le 10^6)$，求方程$x^2+\sqrt px +q$有至少一个实根的概率，其中$p\in [0, a], q\in [-b, b]$，$p, q$均是实数，在上述区间内等概率分布。

### 推算
$\Delta = b^2 - 4ac = (\sqrt{p})^2 - 4 \times 1 \times q = p - 4q$

由题意，$p - 4q ≥ 0$，即 $p ≥ 4q$

推理可得:

### 伪代码
```fAKe-code
input(a, b)
var f = 4 * b // 答案为 p ∈ [0, a], q ∈ [−f, f] 时 p ≥ f 的概率
if f == 0
	printAns(1)
elif a == 0 // 此时满足 a == 0 && f != 0
	printAns(0.5)
elif a >= f
	printAns((a - b) / a)
else
	printAns((a * 0.25 + f * 0.5) / f)
fi
```

### 代码

```cpp
#include <stdio.h>
using namespace std;

double a, b, f;

void input()
{
    scanf("%lf%lf", &a, &b);
}

void printAns(double ans)
{
    printf("%.10lf\n", ans);
}

void play()
{
    input();
    f = b * 4;
    if (b == 0) printAns(1);
    else if (a == 0) printAns(0.5);
    else if (a >= f) printAns((a - b) / a);
    else printAns((a * 0.25 + f * 0.5) / f);
}

int main()
{
    int test;
    scanf("%d", &test);
    while (test--) play();
    return 0;
}
```



---

