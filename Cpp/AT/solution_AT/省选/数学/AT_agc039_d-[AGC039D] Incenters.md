# [AGC039D] Incenters

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc039/tasks/agc039_d

$ xy $ 平面上の点 $ (0,0) $ を中心とする円周上に $ N $ 個の点が与えられます。 $ i $ 個目の点の座標は $ (\cos(\frac{2\pi\ T_i}{L}),\sin(\frac{2\pi\ T_i}{L})) $ です。

これら $ N $ 個の点の中から相異なる $ 3 $ 点を一様ランダムに選ぶとき、 選んだ $ 3 $ 点を結んでできる三角形の内接円の中心の $ x $ 座標、$ y $ 座標の期待値をそれぞれ求めてください。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 3000 $
- $ N\ \leq\ L\ \leq\ 10^9 $
- $ 0\ \leq\ T_i\ \leq\ L-1 $
- $ T_i\ <\ T_{i+1} $
- 入力はすべて整数である

### Sample Explanation 1

$ 3 $ 点の座標は $ (1,0) $, $ (0,1) $, $ (0,-1) $ であり、この $ 3 $ 点を結んでできる三角形の内接円の中心の座標は $ (\sqrt{2}-1,0) $ です。

## 样例 #1

### 输入

```
3 4
0
1
3```

### 输出

```
0.414213562373095 -0.000000000000000```

## 样例 #2

### 输入

```
4 8
1
3
5
6```

### 输出

```
-0.229401949926902 -0.153281482438188```

## 样例 #3

### 输入

```
10 100
2
11
35
42
54
69
89
91
93
99```

### 输出

```
0.352886583546338 -0.109065017701873```

# 题解

## 作者：Caro23333 (赞：9)

_**“在这里，你甚至可以学习平面几何”**_

比赛的时候这个题我似乎用三角函数的技巧硬推出来一个不知道对不对的式子，然后没实现完...... 然后发现标准做法完全不是这样）

#### 定理$1$: 如图，$A,B,C$在$\odot O$上，在$\triangle ABC$中，作$\angle BAC,\angle ACB,\angle CBA$的平分线，分别交$\odot O$于$F,D,E$，并且三条角平分线交于一点$I$，则$I$是$\triangle DEF$的垂心。

![](https://cdn.luogu.com.cn/upload/image_hosting/wyogzp9g.png)

证：

$$\textrm{设}\odot O\textrm{的周长为}c$$

$$\because AF,BE,CD\textrm{分别是}\angle BAC,\angle CBA,\angle ACB\textrm{的平分线}$$

$$\therefore \overset{\LARGE{\frown}}{AE}=\overset{\LARGE{\frown}}{EC}, 
\overset{\LARGE{\frown}}{CF}=\overset{\LARGE{\frown}}{FB},
\overset{\LARGE{\frown}}{BD}=\overset{\LARGE{\frown}}{DA}$$

$$\therefore \overset{\LARGE{\frown}}{EC}+\overset{\LARGE{\frown}}{DF} = \frac{1}{2}c$$ 

$$\therefore \angle EDC+\angle DEF=90^{\circ}$$

$$\therefore DC\perp EF,\textrm{同理有}BE\perp DF,AF\perp ED$$

$$\therefore I\textrm{是}\triangle DEF\textrm{垂心}$$

证毕。

有了这个结论之后，我们就可以把求内心转化成求另一个三角形的垂心了。而垂心的位置可以通过重心来转化计算：

#### 定理$2$（欧拉线）:如图，$A,B,C$在$\odot O$上，$D,E,F$分别为$AB,BC,CA$中点，$G,H$分别为$\triangle ABC$的重心、垂心，连$OH$，则有$G$在$OH$上，且$GH=2OG$。

![](https://cdn.luogu.com.cn/upload/image_hosting/thmxckn1.png)

证：

$$\textrm{如下图，作直线}AO\textrm{交}\odot O\textrm{于}P,\textrm{连}BP,PC,PE,EH,OE$$
![](https://cdn.luogu.com.cn/upload/image_hosting/ofz82j3w.png)

$$\because AP\textrm{是直径}\ \therefore AB\perp BP$$

$$\textrm{又}\because CH\perp AB$$

$$\therefore CH\parallel BP,\textrm{同理有} CP\parallel BH$$

$$\therefore \textrm{四边形}BHCP\textrm{是平行四边形}$$

$$\therefore BP=CH$$

$$\because CH\parallel BP\ \therefore \angle PBC=\angle HCB$$

$$\textrm{又}\because BE=EC$$

$$\therefore \triangle BPE\ \cong \triangle CHE$$

$$\therefore \angle PEB=\angle HEC\ \therefore P,E,H\textrm{共线}$$

$$\therefore OE\textrm{是}\triangle PAH\textrm{中位线}\ \therefore OE=\frac{1}{2}AH$$

$$\textrm{设}AE\textrm{与}OH\textrm{交于}G'$$

$$\because OE\parallel AH\ \therefore \frac{OG'}{G'H}=\frac{G'E}{AG'}=\frac{OE}{AH}=\frac{1}{2}$$

$$\therefore G'\textrm{是重心}\ \therefore GH=2OG$$

证毕。那么由这个结论，我们有$\overrightarrow{OH}=3\overrightarrow{OG}$。

在这题中，圆心$O$恰在原点，而平面中三点$(x_A,y_A),(x_B,y_B),(x_C,y_C)$组成的三角形重心之坐标为$(\frac{x_A+x_B+x_C}{3},\frac{y_A+y_B+y_C}{3})$，**所以对于任意$\triangle ABC$，三段弧中点的坐标之和，就是$\triangle ABC$内心的坐标**。

然后随便做做就好啦！

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define pi 3.14159265358979323846

using namespace std;
typedef long long ll;
typedef long double ld;
const int MAXN = 3005;
int n,L;
ld t[MAXN],pre[2][2][MAXN][MAXN];

int main()
{
	cin >> n >> L;
	for(int i = 1; i<=n; i++)
	    cin >> t[i];
	ld ansx = 0, ansy = 0;
	for(int i = 1; i<=n; i++)
		for(int j = i+1; j<=n; j++)
	    {
			int cnt = j-i-1;
			ld tmp = pi*(t[i]+t[j])/L;
			ansx += cos(tmp)*(n-2*cnt-2), ansy += sin(tmp)*(n-2*cnt-2);
		}
	ansx /= 1ll*n*(n-1)*(n-2)/6;
	ansy /= 1ll*n*(n-1)*(n-2)/6;
	printf("%.12lf %.12lf\n",(double)ansx,(double)ansy);
	return 0;
}

```


---

## 作者：_lyx1311_ (赞：5)

这里给一个 $O(n)$ 的算法。

至于几何转化，楼上的巨佬都已经讲的很清楚了，所以就讲一下怎么将 $O(n^2)$ 的算法优化成 $O(n)$ 的算法。

令 $a_i=\frac{\pi T_i}{L}$ ，则 $\begin{cases}Ans_x=\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}\cos(a_i+a_j)\times (n-2(j-i))\\Ans_y=\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}\sin(a_i+a_j)\times (n-2(j-i))\end{cases}$。

因为 $\begin{cases}\cos(\alpha+\beta)=\cos\alpha\cos\beta-\sin\alpha\sin\beta\\\sin(\alpha+\beta)=\sin\alpha\cos\beta+\cos\alpha\sin\beta\end{cases}$。

所以： $\begin{aligned}Ans_x&=\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}(n+2i-2j)(\cos a_i\cos a_j-\sin a_i\sin a_j)\\&=\sum\limits_{i=1}^{n}\cos a_i((n+2i)\sum\limits_{j=i+1}\cos a_j-2\sum\limits_{j=i+1}^{n}j\cos a_j)-\sin a_i((n+2i)\sum\limits_{j=i+1}\sin a_j-2\sum\limits_{j=i+1}^{n}j\sin a_j)\end{aligned}$

且： $\begin{aligned}Ans_y&=\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}(n+2i-2j)(\sin a_i\cos a_j+\cos a_i\sin a_j)\\&=\sum\limits_{i=1}^{n}\sin a_i((n+2i)\sum\limits_{j=i+1}\cos a_j-2\sum\limits_{j=i+1}^{n}j\cos a_j)+\cos a_i((n+2i)\sum\limits_{j=i+1}\sin a_j-2\sum\limits_{j=i+1}^{n}j\sin a_j)\end{aligned}$

所以我们维护：$\sum\limits_{i=1}^{n}\sin a_i$，$\sum\limits_{i=1}^{n}i\sin a_i$，$\sum\limits_{i=1}^{n}\cos a_i$，$\sum\limits_{i=1}^{n}i\cos a_i$，即可$O(n)$枚举$i$，$O(1)$统计答案。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;

const long double pi = 3.14159265358979323846;

const int N = 3005;

long double a[N];

long double Sin1[N], Sin2[N], Cos1[N], Cos2[N];

int main(){
	int n, l;
	cin >> n >> l;
	
	for(int i = 1; i <= n; i ++)
		cin >> a[i], a[i] *= (pi / l);
	
	long double X = 0.0, Y = 0.0;
	
	Sin1[0] = Sin2[0] = Cos1[0] = Cos2[0] = 0.0;
	for(int i = 1; i <= n; i ++){
		Sin1[i] = Sin1[i - 1] + sin(a[i]);
		Sin2[i] = Sin2[i - 1] + sin(a[i]) * i;
		
		Cos1[i] = Cos1[i - 1] + cos(a[i]);
		Cos2[i] = Cos2[i - 1] + cos(a[i]) * i;
	}
	
	for(int i = 1; i <= n; i ++){
		X += (n + 2 * i) * cos(a[i]) * (Cos1[n] - Cos1[i]);
		X -= 2 * cos(a[i]) * (Cos2[n] - Cos2[i]);
		
		X -= (n + 2 * i) * sin(a[i]) * (Sin1[n] - Sin1[i]);
		X += 2 * sin(a[i]) * (Sin2[n] - Sin2[i]);
		
		Y += (n + 2 * i) * sin(a[i]) * (Cos1[n] - Cos1[i]);
		Y -= 2 * sin(a[i]) * (Cos2[n] - Cos2[i]);
		
		Y += (n + 2 * i) * cos(a[i]) * (Sin1[n] - Sin1[i]);
		Y -= 2 * cos(a[i]) * (Sin2[n] - Sin2[i]);
	}
	
	X /= (1.0 * n * (n - 1) * (n - 2) / 6);
	Y /= (1.0 * n * (n - 1) * (n - 2) / 6);
	
	printf("%.18lf %.18lf\n", (double)X, (double)Y);
	
	return 0;
}
```

这个代码在`Luogu`上的提交只有`211 ms`，而第二名都有`3 s+`……

---

## 作者：Albedo (赞：3)

## Introduction

在这里，你可以同时学习初中数学以及必修一数学。

## Solution

首先我们看到内心，他是角平分线的交点，是很不好做的，怎么办呢，三角形有 $ 5 $ 心，我们考虑将其他几个心与这个内心联系起来，首先外心的坐标是 $ (0,0) $ 是显然的，然后重心得坐标同样显然是 $ (\frac{x_a+x_b+x_c}{3},\frac{y_a+y_b+y_c}{3}) $，垂心我们有一个欧拉线，他们就可以得到垂心的坐标是$(x_a+x_b+x_c,y_a+y_b+y_c) $。还有一个旁心是没有用处的，就不管他了。 

接下来就是神操作了，我们要将题目中的内心转化成为垂心。

[![77rdVe.png](https://s4.ax1x.com/2022/01/25/77rdVe.png)](https://imgtu.com/i/77rdVe)

我们假设 $ \triangle ABC $ 的内心为 $ D $，我们把三条角平分线给引出来，为什么要这么做，因为 $ \frac{\angle A+\angle B+\angle C}{2}=\frac{\pi}{2} $，然后就得到了一个新的三角形 $ \triangle EFG $ ，我们可以发现的是:

 $$ \because \angle GEC=\frac{1}{2}\angle B,\angle FEC=\frac{1}{2}\angle A,\angle EGB=\frac{1}{2}\angle C$$

$$\therefore \angle FEG+EGB=\frac{\angle A+\angle B +\angle C }{2}=\frac{\pi}{2}$$

$$\therefore \text{同理可知} \angle EFG+\angle BGF=\frac{\pi}{2}$$

$$\therefore D\text{是}\triangle EFG\text{的垂心}$$

然后我们就把问题从求 $ \triangle ABC $ 的内心转换成了求 $ \triangle EFG $ 的垂心。

然后我们可以发现，因为题目给我们的是点的弧度，所以 $ \triangle EFG $ 每个点的坐标也是可以轻松求出的。

然后就是必修一的内容了。

因为我们现在的做法的复杂度是 $ O(n^3) $ 的，显然无法通过此题。

那么开始优化，我们假设选出的三个点的 $ T_i $ 是 $ x,y,z $ 。

我们可以知道的是现在的表达式是：

$$(\cos(\frac{(x+y)\times \pi}{L})+\cos(\frac{(y+z)\times \pi}{L})-\cos({\frac{(x+z)\times \pi}{L}}),\sin(\frac{(x+y)\times \pi}{L})+\sin(\frac{(y+z)\times \pi}{L})-\sin({\frac{(x+z)\times \pi}{L}}))$$

我们考虑和差化积。那么前面的表达式就是：

$$(-2)\times \sin(\frac{(y-z)\times \pi}{2\times L})\times\sin(\frac{(y+x+z\times 2)\times \pi}{2\times L})=(-2)\times \sin(\frac{(y-z)\times \pi}{2\times L})\times(\sin(\frac{(y+x)\times \pi}{2\times L}))\times \cos(\frac{z\times \pi}{L}+\cos(\frac{(y+x)\times \pi}{2\times L}))\times \sin(\frac{z\times \pi}{L})$$

然后一下后缀和就好了。

后面一个式子也是同理，然后就优化到了 $ O(n^2) $ 

## Code

```c++
n=read();L=read();
	for (i=1;i<=n;i++)  a[i]=read();
	tot=n*(n-1)*(n-2)/6;
	for (i=n;i>=1;i--) sufs[i]=sufs[i+1]+sin(a[i]/L*PI),sufc[i]=sufc[i+1] +cos(a[i]/L*PI);
	for (A=1;A<=n-2;A++)
	    for (B=A+1;B<=n-1;B++)
	       {
	       	x=x+sin((a[A]+a[B])/L*PI)*(n-B)+2*sin((a[B]-a[A])/2/L*PI)*(cos((a[A]+a[B])/2/L*PI)*sufc[B+1]-sin((a[A]+a[B])/2/L*PI)*sufs[B+1]);
            y=y+cos((a[A]+a[B])/L*PI)*(n-B)+(-2)*sin((a[B]-a[A])/2/L*PI)*(cos((a[A]+a[B])/2/L*PI)*sufs[B+1]+sin((a[A]+a[B])/2/L*PI)*sufc[B+1]);      
		}
	x/=tot;y/=tot;
	printf("%.20lf %.20lf\n",y,x);
```



---

## 作者：Celtic (赞：0)

几何结论 1：三角形的内心是外接圆三条弧中点形成的三角形的垂心。

几何结论 2：设三角形 $ABC$ 垂心为 $H$，外心为 $O$，则$\vec{OH}=\vec{OA}+\vec{OB}+\vec{OC} $。

有了这两个结论之后就可以推出答案的式子。设 $a_i=\frac{\pi t_i}{L}$，则有
$$ansx=\sum_{i=1}^{n} \sum_{j=i+1}^{n}  \sum_{k=j+1}^{n}\cos(a_i+a_j)+\cos(a_j+a_k)-\cos(a_i+a_k)$$

$$ansy=\sum_{i=1}^{n} \sum_{j=i+1}^{n}  \sum_{k=j+1}^{n}\sin(a_i+a_j)+\sin(a_j+a_k)-\sin(a_i+a_k)$$

枚举 $i,j$ 然后算贡献，可得
$$ansx=\sum_{i=1}^{n} \sum_{j=i+1}^{n}\cos(a_i+a_j)(n-2(j-i))$$
$$ansy=\sum_{i=1}^{n} \sum_{j=i+1}^{n}\sin(a_i+a_j)(n-2(j-i))$$

根据两角和公式，有
$$ansx=\sum_{i=1}^{n} \sum_{j=i+1}^{n}(\cos(a_i)\cos(a_j)-\sin(a_i)\sin(a_j))(n-2(j-i))$$
$$ansy=\sum_{i=1}^{n} \sum_{j=i+1}^{n}(\sin(a_i)\cos(a_j)+\cos(a_i)\sin(a_j))(n-2(j-i))$$

分离 $i,j$ 后可得
$$ansx=\sum_{i=1}^{n} \cos(a_i) \left( (n+2i)\sum_{j=i+1}^{n} \cos(a_j)-\sum_{j=i+1}^{n} j\cos(a_j) \right)-\sin(a_i)  \left( (n+2i)\sum_{j=i+1}^{n} \sin(a_j)-\sum_{j=i+1}^{n} j\sin(a_j) \right)$$
$$ansy=\sum_{i=1}^{n} \sin(a_i) \left( (n+2i)\sum_{j=i+1}^{n} \cos(a_j)-\sum_{j=i+1}^{n} j\cos(a_j) \right)+\cos(a_i)  \left( (n+2i)\sum_{j=i+1}^{n} \sin(a_j)-\sum_{j=i+1}^{n} j\sin(a_j) \right)$$

维护一下 $\cos(a_i),i\cos(a_i),\sin(a_i),i\sin(a_i)$ 的后缀和就行了。

复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
#define N 401001
#define MAX 2005
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=998244353,inf=1e18;
inline void read(ll &ret)
{
	ret=0;char c=getchar();bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll n,l,t[N];
db sufsin[N],sufisin[N],sufcos[N],suficos[N];
db a[N];
signed main()
{
	read(n);
	read(l);
	for(int i=1;i<=n;i++)
	{
		read(t[i]);
		a[i]=t[i]*acos(-1)/l;
	}
	for(int i=n;i;i--)
		sufsin[i]=sufsin[i+1]+sin(a[i]),sufcos[i]=sufcos[i+1]+cos(a[i]),sufisin[i]=sufisin[i+1]+i*sin(a[i]),suficos[i]=suficos[i+1]+i*cos(a[i]);
	db ansx=0,ansy=0;
	for(int i=1;i<=n;i++)
	{
		ansx+=cos(a[i])*((n+2*i)*sufcos[i+1]-2*suficos[i+1])-sin(a[i])*((n+2*i)*sufsin[i+1]-2*sufisin[i+1]);
		ansy+=sin(a[i])*((n+2*i)*sufcos[i+1]-2*suficos[i+1])+cos(a[i])*((n+2*i)*sufsin[i+1]-2*sufisin[i+1]);
	}
	ansx/=n*(n-1)*(n-2)/6,ansy/=n*(n-1)*(n-2)/6;
	printf("%.12lf %.12lf\n",ansx,ansy);
	exit(0);
}

```

---

## 作者：xht (赞：0)

## [Incenters](https://atcoder.jp/contests/agc039/tasks/agc039_d)

### 题意

- 平面直角坐标系上有 $n$ 个点，第 $i$ 个点为 $(\cos(\frac {2\pi T_i}{L}), \sin(\frac {2\pi T_i}{L}))$。
- 求出在 $n$ 个点中随机选择三个点，以这三个点为顶点的三角形的内心的期望坐标。
- $n \le 3 \times 10^3$，$0 \le T_i < L \le 10^9$。

### 题解

对于 $\triangle ABC$，取 $AB,BC,CA$ 弧的中点 $D,E,F$，可以发现 $\triangle DEF$ 的垂心就是 $\triangle ABC$ 的内心。

考虑如何求 $\triangle DEF$ 的垂心，根据欧拉线，由于 $\triangle DEF$ 的外心为 $O(0,0)$，重心为 $\frac{D+E+F}{3}$，所以垂心为 $D+E+F$。

于是显然可以 $\mathcal O(n^2)$ 枚举求答案。

### 代码

```cpp
const int N = 3e3 + 7;
const ld PI = acos(-1);
int n, L, a[N];
ld x, y;

int main() {
	rd(n, L), rda(a, n);
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			x += (n - 2 * (j - i)) * cos(PI * (a[i] + a[j]) / L),
			y += (n - 2 * (j - i)) * sin(PI * (a[i] + a[j]) / L);
	ll k = 1ll * n * (n - 1) * (n - 2) / 6;
	printf("%.20Lf %.20Lf\n", x / k, y / k);
	return 0;
}
```

---

