# Fly

## 题目描述

Natasha is going to fly on a rocket to Mars and return to Earth. Also, on the way to Mars, she will land on $ n - 2 $ intermediate planets. Formally: we number all the planets from $ 1 $ to $ n $ . $ 1 $ is Earth, $ n $ is Mars. Natasha will make exactly $ n $ flights: $ 1 \to 2 \to \ldots n \to 1 $ .

Flight from $ x $ to $ y $ consists of two phases: take-off from planet $ x $ and landing to planet $ y $ . This way, the overall itinerary of the trip will be: the $ 1 $ -st planet $ \to $ take-off from the $ 1 $ -st planet $ \to $ landing to the $ 2 $ -nd planet $ \to $ $ 2 $ -nd planet $ \to $ take-off from the $ 2 $ -nd planet $ \to $ $ \ldots $ $ \to $ landing to the $ n $ -th planet $ \to $ the $ n $ -th planet $ \to $ take-off from the $ n $ -th planet $ \to $ landing to the $ 1 $ -st planet $ \to $ the $ 1 $ -st planet.

The mass of the rocket together with all the useful cargo (but without fuel) is $ m $ tons. However, Natasha does not know how much fuel to load into the rocket. Unfortunately, fuel can only be loaded on Earth, so if the rocket runs out of fuel on some other planet, Natasha will not be able to return home. Fuel is needed to take-off from each planet and to land to each planet. It is known that $ 1 $ ton of fuel can lift off $ a_i $ tons of rocket from the $ i $ -th planet or to land $ b_i $ tons of rocket onto the $ i $ -th planet.

For example, if the weight of rocket is $ 9 $ tons, weight of fuel is $ 3 $ tons and take-off coefficient is $ 8 $ ( $ a_i = 8 $ ), then $ 1.5 $ tons of fuel will be burnt (since $ 1.5 \cdot 8 = 9 + 3 $ ). The new weight of fuel after take-off will be $ 1.5 $ tons.

Please note, that it is allowed to burn non-integral amount of fuel during take-off or landing, and the amount of initial fuel can be non-integral as well.

Help Natasha to calculate the minimum mass of fuel to load into the rocket. Note, that the rocket must spend fuel to carry both useful cargo and the fuel itself. However, it doesn't need to carry the fuel which has already been burnt. Assume, that the rocket takes off and lands instantly.

## 说明/提示

Let's consider the first example.

Initially, the mass of a rocket with fuel is $ 22 $ tons.

- At take-off from Earth one ton of fuel can lift off $ 11 $ tons of cargo, so to lift off $ 22 $ tons you need to burn $ 2 $ tons of fuel. Remaining weight of the rocket with fuel is $ 20 $ tons.
- During landing on Mars, one ton of fuel can land $ 5 $ tons of cargo, so for landing $ 20 $ tons you will need to burn $ 4 $ tons of fuel. There will be $ 16 $ tons of the rocket with fuel remaining.
- While taking off from Mars, one ton of fuel can raise $ 8 $ tons of cargo, so to lift off $ 16 $ tons you will need to burn $ 2 $ tons of fuel. There will be $ 14 $ tons of rocket with fuel after that.
- During landing on Earth, one ton of fuel can land $ 7 $ tons of cargo, so for landing $ 14 $ tons you will need to burn $ 2 $ tons of fuel. Remaining weight is $ 12 $ tons, that is, a rocket without any fuel.

In the second case, the rocket will not be able even to take off from Earth.

## 样例 #1

### 输入

```
2
12
11 8
7 5
```

### 输出

```
10.0000000000
```

## 样例 #2

### 输入

```
3
1
1 4 1
2 5 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
6
2
4 6 3 3 5 6
2 6 3 6 5 3
```

### 输出

```
85.4800000000
```

# 题解

## 作者：Y2y7m (赞：4)

我们要先想明白一件事：

**当我们离开一个星球后，我们一定要去剩下的星球中降落+起飞所用燃油最小的星球。**

我觉得我不用解释吧，自己想想就明白了……

那我们怎么算一个星球的燃油消耗量呢？

设我们降落这个第 $i$ 星球之前的总重量为 $x$ 。

所以我们降落所需要的汽油为: $\frac{x}{b_i}$ ，剩下的重量为： $x-\frac{x}{b_i}$ 。

接下来，我们能算出起飞所需的燃油为： $\frac{x-\frac{x}{b_i}}{a_i}$ 。

为了使他们好看些，我把 $\frac{1}{b_i}$ 设为 $u$ ，$\frac{1}{a_i}$ 设为 $v$ .

则我们算出起飞和降落所需汽油之和为： $x-ux+(x-ux)×v$

合并之后得： $(1-u)vx$ 。

改回原来的就是： $(1-\frac{1}{b_i})\frac{1}{a_i}x$ 。

直接结构体排序。

干的漂亮，看到这里，这道题已经解决了：

**$50\%$**

你会发现，正着走算出来需要的燃油似乎不太好想。

那就**倒着走！**

我们绕一圈回来之后肯定不剩下燃油最好，那就一个一个倒着往回推，从降落地球往回推。

公式自己推推？

或者看我代码理解理解吧。

code：
```cpp
#include <bits/stdc++.h>

using namespace std;
struct node
{
	double a,b,id,ta,tb;
}b[1010];
bool cmp(node x,node y)
{
	return x.ta*x.tb<y.ta*y.tb;
}
int main()
{
	int n;
	double m,t;
	cin>>n>>m;
	t=m;
	for(int i=1;i<=n;i++)
		cin>>b[i].a,b[i].ta=b[i].a,b[i].ta=1.0*1/b[i].ta;//排序靠ta,tb
	for(int i=1;i<=n;i++)
		cin>>b[i].b,b[i].tb=b[i].b,b[i].tb=1.0*1/b[i].tb,b[i].tb=1-b[i].tb;
	sort(b+2,b+1+n,cmp);//注意，第一个是地球不要排序
	if(b[1].b==1)//一吨油只能载一吨物品肯定不行
	{
		cout<<"-1"<<endl;
		return 0;
	}
	m+=1.0*m/(b[1].b-1);
	for(int i=n;i>=2;i--)
	{
		if(b[i].a==1)
		{
			cout<<"-1"<<endl;
			return 0;
		}
		m=1.0*m/(b[i].a-1)*b[i].a;//自己理解理解这个地方
		if(b[i].b==1)
		{
			cout<<"-1"<<endl;
			return 0;
		}
		m=1.0*m/(b[i].b-1)*b[i].b;
	}
	if(b[1].a==1)
	{
		cout<<"-1"<<endl;
		return 0;
	}
	m+=1.0*m/(b[1].a-1);
	printf("%.10lf\n",m-t);
	return 0;
}

```



---

## 作者：chichichichi (赞：4)

~~（翻译看得云里雾里 我原题面对照着三份翻译看的）~~
## 二分答案

设携带的燃料重量为 $w$，每次消耗的燃料重量为 $cost$，燃料的效率为 $k$。

则在第 $i$ 个星球起飞时：$k=a[\,i\,]$

在第 $i$ 个星球降落时： $k=b[\,i\,]$

对于每一次消耗我们得到如下两个~~柿子~~式子：

$cost=\dfrac{(w+m)}{k}\qquad\qquad\mathtt{1}$

$w-=cost\qquad\qquad\qquad\;\,\mathtt{2}$

变换一下的话似乎可以得到消耗燃料的总和的表达式：

$$Sum=\sum\limits_{i=1}^{2n}\dfrac{w_i+m}{k_i}$$

其中第 $i=1$ 表示从 $1$ 号星球起飞，$i=2n$表示降落在 $1$ 号星球。

~~然而并没有什么用，我不会数学证明~~

感性的去理解一下，我们携带的燃料越多，需要消耗的就越多，但大于一个数值后一定能保证燃料够用，且带的越多剩余的越多，可以假设携带无穷多的燃料，这样永远也用不完。我们想要携带的燃料最少，就要找到那个分界点，答案具有单调性，我们就可以来二分答案。

注意无答案的情况：

若有效率为 $1$则输出 $-1$，因为当 $k=1$时，$\mathtt{1}$ 式显然不成立


二分答案的细节见代码：
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
const int maxn=1100;
int n;
double m;
double a[maxn],b[maxn];
double ans;
bool check(double w)
{
	//模拟飞行过程
	for(int i=1;i<=n+1;i++)
	{
		double cost;
		if(i>1)
		{
			int x=i%n;
			if(!x)
			x=n;
			cost=(w+m)/b[x];
			w-=cost;

		}
		if(i<=n)
		{
			cost=(w+m)/a[i];
			w-=cost;
		}	
	}
	if(w<0)//不能完成飞行
	return 0;
    //能完成飞行
	return 1;
}
int main(){
	scanf("%d%lf",&n,&m);
	int flag=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&a[i]);
		if(a[i]==1)
		flag=1;
	}
	for(int i=1;i<=n;i++)
	
	{
		scanf("%lf",&b[i]);
		if(a[i]==1)
		flag=1;
	}
	if(flag)//若有效率为1则不可能完成飞行
	{
		printf("-1\n");
		return 0;
	}
    //二分
	double l=1,r=1e9+10;
	while(fabs(r-l)>1e-6)//题目要求精度1e-6，多了会超时
	{
		double mid=(l+r)/2;
		if(check(mid))
		r=mid;
		else
		l=mid;
	}
	if(r==1e9+10)//在范围内找不到答案
	printf("-1\n");
	else
	printf("%.10lf",r);
	return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF1010A Fly](https://www.luogu.com.cn/problem/CF1010A)

只要你有小学数学水平，就可以轻轻松松切掉这道水题。

## 思路

这道题需要推导一下数学公式。

因为 $l \times p = m$，所以 $l = \dfrac{m}{p}$。

因此，比如在第 $2$ 个行星起飞后，$m = m - \dfrac{m - \dfrac{m - \dfrac{m}{p}}{p}}{p}$

但我们不知道 $m$ 是什么，其实我们不必倒着求，将式子转换一下，就豁然开朗。

$$
\begin{aligned}
m &= m - \dfrac{m - \dfrac{m - \dfrac{m}{p}}{p}}{p} \\
m &= m - \dfrac{m - \dfrac{m - \dfrac{1}{p}m}{p}}{p} \\
m &= m - \dfrac{m - \dfrac{1}{p}(m - \dfrac{1}{p}m)}{p} \\
m &= m - \dfrac{1}{p}(m - \dfrac{1}{p}(m - \dfrac{1}{p}m)) \\
\end{aligned}
$$

再拆括号。

$$
\begin{aligned}
m &= m - \dfrac{1}{p}(m - \dfrac{1}{p}(m - \dfrac{1}{p}m)) \\
m &= m - \dfrac{1}{p}(m - \dfrac{1}{p}m - \dfrac{1}{p} \times \dfrac{1}{p}m) \\
m &= m - \dfrac{1}{p}m - \dfrac{1}{p} \times \dfrac{1}{p}m - \dfrac{1}{p} \times \dfrac{1}{p} \times \dfrac{1}{p}m \\
\end{aligned}
$$

最后添括号。

$$
\begin{aligned}
m &= m - \dfrac{1}{p}m - \dfrac{1}{p} \times \dfrac{1}{p}m - \dfrac{1}{p} \times \dfrac{1}{p} \times \dfrac{1}{p}m \\
m &= m - m(1 - \dfrac{1}{p})(1 - \dfrac{1}{p})(1 - \dfrac{1}{p}) \\
\end{aligned}
$$

等式右半部分的 $m$ 就是输入的 $m$。

这样就不必倒推了，直接算就行！

这道水题就被切掉啦！

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int p[2005];

signed main()
{
	int n, m, flag = 0;
	double t = 1.0, x;
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= 2 * n; i++)
	{
		scanf("%lld", &p[i]);
		if (p[i] <= 1)
			flag = 1;
	}
	if (flag)
	{
		printf("-1");
		return 0;
	}
	for (int i = 1; i <= 2 * n; i++)
		t *= 1 - 1.0 / p[i];
	x = (m - m * t) / t;
	printf("%.6lf", x);
	return 0;
}
```

---

## 作者：Dream_It_Possible (赞：0)

### **思路：**

设x为这次起飞或降落时所需的燃料,m为火箭除燃料外的重量，y为一吨燃料可支撑的重量。
则：

**x+m=xy**

**x=m/(y-1)**

由于我们不知道一开始有多少燃料，所以我们必须逆推，从最后一次降落到第一次起飞。

### **细节：**

**1**.要开double。

**2**.输出小数点后十位。

### **代码：**

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int a[100005],b[100005];
int main()
{
	int n,i,j;
	double m;
	cin>>n>>m;
	for (i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for (i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
	}
	double ans=0.00,x;
	for (i=1;i<=n;i++)
	{
		if (i%2==1)
		{
			//b
			x=(double)(m)/(double)(b[i]-1);
			//cout<<x<<endl;
			ans+=x; 
			m+=x;
		}
		else
		{
			//a
			x=(double)(m)/(double)(a[i]-1);
			//cout<<x<<endl;
			ans+=x; 
			m+=x;
		}
	}
	for (i=n;i>=1;i--)
	{
		if (i%2==0)
		{
			//b
			x=(double)(m)/(double)(b[i]-1);
			//cout<<x<<endl;
			ans+=x; 
			m+=x;
		}
		else
		{
			//a
			x=(double)(m)/(double)(a[i]-1);
			//cout<<x<<endl;
			ans+=x; 
			m+=x;
		}
	}
	if(ans>=2147483647)
	cout<<"-1";
	else
	printf("%.10f",ans);
	return 0;
}
```

---

## 作者：StudyingFather (赞：0)

设要加的油为f，那么我们可以解一个方程：

$ a+f=kf $

其中a是载荷重量，k是题目中给出的系数。

显然，当k=1时，原方程无解。

我们可以从后往前倒退，最后求出出发时需要的油量。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[1005],b[1005];
bool is_equal(double x,double y)//浮点数判断相等
{
 return abs(x-y)<=1e-9;
}
double solve(int x,double y)
{
 if(x==1||is_equal(-1,y))return -1;
 return y+y*1.0/(x-1);
}
int main()
{
 int n,m;
 scanf("%d%d",&n,&m);
 for(int i=1;i<=n;i++)
  scanf("%d",&a[i]);
 for(int i=1;i<=n;i++)
  scanf("%d",&b[i]);
 double f=m;
 f=solve(b[1],f);
 f=solve(a[n],f);
 for(int i=n-1;i>=1;i--)
 {
  f=solve(b[i+1],f);
  f=solve(a[i],f);
 }
 if(is_equal(-1,f))printf("-1");
 else printf("%.10lf",f-m);
 return 0;
}
```

---

