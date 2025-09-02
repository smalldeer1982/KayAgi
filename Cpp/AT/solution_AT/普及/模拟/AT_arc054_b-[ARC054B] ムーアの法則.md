# [ARC054B] ムーアの法則

## 题目描述

原题网址:[link](https://atcoder.jp/contests/arc054/tasks/arc054_b)



高橋君对塔卡哈什曼函数感兴趣。高桥君想计算$T（334）$的值（$T$表示塔卡哈什曼函数[译者注:可能是暗示了哈克曼函数:`Ackermann`，可能是解题方法的暗示]），但由于现代计算机需要$P$年，所以很难计算。

高橋君几乎放弃了一半的计算，知道了世界上有摩尔法则这个法则。根据摩尔法则，我们发现计算机的速度是每$1.5$年翻倍的速度，呈指数增长。

更准确地说，$x$年后计算机的速度将是现代的$2^{x/1.5}$倍。

高桥君想通过在适当的时机开始计算，并尽快结束$T（334）$的计算。当然，因为在计算过程中不能改变计算机，所以计算结束之前的时间是（开始计算之前的时间）+（开始计算时的计算机计算$T（334）$所需的时间）。

请计算结束前的最短时间$m$。

## 说明/提示

- $0<P\leqslant10^{18}$  
- $P$是实数，保留小数点后$4$位输出。

## 样例 #1

### 输入

```
3.0000```

### 输出

```
2.8708930019```

## 样例 #2

### 输入

```
0.0400```

### 输出

```
0.0400000000```

## 样例 #3

### 输入

```
1000000000000000000.0000```

### 输出

```
90.1855078128```

# 题解

## 作者：Never_care (赞：6)

这里来一篇纯摩尔定律计算的题解。
### 思路
首先思考摩尔的指数。计算机速度每 $1.5$ 年翻倍，所以我们先设当前速度为 $v_0$，则 $n$ 年后的速度为 $v(n)=v_0\times2^{n/1.5}$。

第二想如何计算时间。题面中提出由于现代计算机需要 $P$ 年，则 $n$ 年后的时间为 $\frac{P}{2^{n/1.5}}$。

第三将 $n$ 年再加上刚刚计算出的时间得到总时间。

到这里开始第二部分的推导。

第一对于推导出来的总时间求导并找到边界点：$f(n)=n+P\times2^{-n/1.5}$。令导数为 $0$ 后求导，解出 $2^{-n/1.5}=\frac{1.5}{P\times \operatorname{log_2}}$。提取出 $\operatorname{log_2}$，得到：$n=\frac{1.5}{\operatorname{log_2}}\times \operatorname{log}(\frac{P\times \operatorname{log_2}}{1.5})$。

最后一步是判断情况。如果 $\frac{P\times \operatorname{log_2}}{1.5}\le1$，简单分析可知 $n\le0$，根据题意直接输出 $P$。否则利用公式计算总时间。
### code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f  
using namespace std;
int main(){
    double n;
    cin>>n;
    double log2=log(2);
    double temp=(n*log2)/1.5;
    if(temp<=1.0){
        cout<<fixed<<setprecision(10)<<n<<'\n';
    }
	else{
        double t=(1.5/log2)*log(temp);
        cout<<fixed<<setprecision(10)<<t+n/pow(2,t/1.5)<<'\n';
    }
    return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/r62xrvzo.png)

---

## 作者：Like_Amao (赞：1)

蒟蒻的第一篇题解

**思路**

不难发现，在刚开始计算时，计算的速度快速下降，开始时间不会有太大变化，总用时长减少；当 $x$ 逐渐增大时，计算的速度比开始的速度少，因此总用时长回升，这就形成先降后升趋势，故用三分。（个人感觉跟题目中讲到的 ```Ackermann``` 函数并无直接联系，也可能是我太蒟了，不知道）

**代码**


```cpp
#include<bits/stdc++.h>
using namespace std;
double n;
double f(double);
int main()
{
	double left=0,right=1e18;
	cin>>n;
	while(right-left>1e-10)
	{
		double middle1=(2*left+right)/3,middle2=(left+right*2)/3;
		if(f(middle1)<f(middle2))
		{
			right=middle2;
		}
		else
		{
			left=middle1;
		}
	}
	cout<<fixed<<setprecision(10)<<f((left+right)/2.0);
	return 0;
}
double f(double x)
{
	return x+n/pow(2,x/1.5);
}
```

---

## 作者：__Creeper__ (赞：0)

## 思路

不难发现：刚开始计算时，速度呈指数级下降，开始时间变化小，当 $x$ 越来越大时，计算速度比开始速度小。总时长前降后升，呈凸函数。我们可以用[三分法](https://oi-wiki.org/basic/binary/#%E4%B8%89%E5%88%86%E6%B3%95)求函数最值。

## Code

```cpp
#include <bits/stdc++.h>
#define X1 x1
#define X0 x0
#define Y1 y1
#define Y0 y0
#define int long long
using namespace std;

const long double eps = 1e-10;
long double p;
long double calc ( long double x ) { return x + p / pow ( 2, x / 1.5 ); }

void solve()
{
	cin >> p;
	long double l = 0, r = p;
	while ( r - l > eps ) 
	{
		double midl = ( 2 * l + r ) / 3, midr = ( l + 2 * r ) / 3;
		if ( calc ( midl ) < calc ( midr ) ) r = midr;
		else l = midl;
	}
	printf ( "%.10Lf\n", calc ( ( l + r ) / 2 ) );
}

signed main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0);
//	cout.tie(0);
	int T = 1;
//	cin >> T;
	while ( T-- ) solve();
	return 0;
}
```

---

## 作者：yangfengzhao (赞：0)

## 思路
通过推导，不难发现：**刚开始计算时，速度快速下降（指数级下降），开始时间变化较小，当 ${x}$ 越来越大时，计算速度比开始速度小。**\
因此，能发现**总时长回升**，形成了**前降后升**，故用三分。
>高桥他知道**摩尔法则**[^1]，于是他准备从一个适合的时机计算 ${T(334)}$，尽早结束 ${T(334)}$ 的运算。
---
**得到公式**：\
计算结束之前的时间=开始计算之前的时间+开始计算时的计算机计算 ${T(334)}$ 所需的时间[^2]。
## 代码
```cpp
#include<iostream>
#define Eps 1e-10
//题目限度是1e-10，即0.000000001
using namespace std;
double N;
double TimeCompute(double X)
{
	return X+N/pow(2,X/1.5);//运用到摩尔法则...
}
signed main(){
	scanf("%d",&N);
	double L=0,R=N;
	while(R-l>Eps){
		double Mid1=(L*2+R)/3,Mid2=(L+R*2)/3;
		if(TimeCompute(Mid1)<TimeCompute(Mid2))R=Mid2;//不合适，往前选择
		else L=Mid1;//仍然时间太长，再往后
	}
	printf("%10.lf\n",TimeCompute((L+R)/2));
	return 0;
}
```
>岛国水题要换行！
## 补充
[^1]:**摩尔法则**是指在 ${n}$ 年后，计算机的速度将会是现在的 ${2^{x\div{1.5}}}$ 倍。
[^2]:为了使时间能尽可能的短，故用三分。

---

## 作者：topcsa (赞：0)

## 思路

首先，它可以满足一个单调条件，开始时，每将 $x$ 增加 $1$，总时间就会减少非常多，但到后面，减少的时间微乎其微，甚至没有 $1$ 这么多，会使总时间越来越多，所以满足一个两边高，中间低的一个模型，即可使用三分算法来写。

## 代码

AC Code (~~空格洁癖型码风~~)：

```cpp
#include <bits/stdc++.h>
#define double long double
#define int double
using namespace std;
double p;
double func(double x) {
	return x + p / pow(2, x / 1.5); // 封装计算
}
signed main()
{
	cin >> p;
	double l = 0, r = p;
	while (r - l > 1e-10) { // 精度！精度！精度！重要的事情说三遍，不能直接 l <= r，这是 double，会有精度问题
        // 正常三分
		double mid1 = (2 * l + r) / 3; 
		double mid2 = (l + 2 * r) / 3;
		if (func(mid1) < func(mid2)) { // 找到时间较少的点三分
			r = mid2;
		}
		else {
			l = mid1;
		}
	}
	cout << fixed << setprecision(10) << func((l + r) / 2.0);
	return 0;
}

```

---

## 作者：lzh_juruo (赞：0)

# [ARC054B] ムーアの法則 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc054_b)

此题考虑三分。

因为在开始时，大量的计算时间会指数级减少，而开始时间只会缓慢增加，总用时减少。到达用时最少的点后，因为计算时间已经很少而不足以抵消开始时间的增加，就导致总用时增加。函数图像是一个谷的形状，故三分可行。

 AC 代码：
 
```cpp
#include<bits/stdc++.h>
#define eps 1e-10
using namespace std;
double n;
double tim(double x){
	return x+n/pow(2,x/1.5);
}
signed main(){
	cin>>n;
	double l=0,r=n;
	while(r-l>eps){
		double mid1=(l*2+r)/3,mid2=(l+r*2)/3;
		if(tim(mid1)<tim(mid2)) r=mid2;
		else l=mid1;
	}
	cout<<fixed<<setprecision(10)<<tim((l+r)/2);
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

高橋君对塔卡哈什曼函数感兴趣。高桥君想计算 $T(334)$的值（$T$ 表示塔卡哈什曼函数[译者注：可能是暗示了哈克曼函数：`Ackermann`，可能是解题方法的暗示]），但由于现代计算机需要 $P$ 年，所以很难计算。

高橋君几乎放弃了一半的计算，知道了世界上有摩尔法则这个法则。根据摩尔法则，我们发现计算机的速度是每 $1.5$ 年翻倍的速度，呈指数增长。

更准确地说，$x$ 年后计算机的速度将是现代的 $2^{x\div1.5}$ 倍。

高桥君想通过在适当的时机开始计算，并尽快结束 $T(334)$的计算。当然，因为在计算过程中不能改变计算机，所以计算结束之前的时间是（开始计算之前的时间）$+$（开始计算时的计算机计算 $T(334)$所需的时间）。

计算结束前的最短时间 $m$。

这道题明显的数学题，算出答案很简单，代码也很短：

- 所以用三分。

最终答案为：
```c
#include<bits/stdc++.h>
#define db double
using namespace std;
db n,l=0,r=1e18;
db f(db x){
	return x+n/pow(2,x/1.5);
}
int main(){
	cin>>n;
	while(r-l>1e-10){
		int mid1=(2*l+r)/3,mid2=(l+r*2)/3;
		if(f(mid1)<f(mid2))r=mid2;
		else l=mid1;
	}
	printf("%0.10lf\n",f((l+r)/2.0));
	return 0;
}
```
~~格式到全国统一程序。~~

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [ムーアの法則](https://www.luogu.com.cn/problem/AT_arc054_b)
## 思路
求在平面直角坐标系上使 $2^{x/1.5}-P=0$ 的 $x$ 的值。

最后解得 $x=\frac{3\log(P\frac{\log2}{1.5})}{\log4}$。

所以，答案为 $\operatorname{f(x)}=x+\frac P{2^\frac{x}{1.5}}$。

再用[函数模拟器 $desmos$](https://www.desmos.com/calculator?lang=zh-CN)画出该图像。

[GIF 图片](https://ibb.co/pzK6KSZ)

所以，当 $P>0$ 时该图像为凸函数。

故考虑三分，如果不会请点击[这里](https://www.luogu.com.cn/problem/P3382)。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define db double
using namespace std;
db n,l=0,mid1,mid2,r=1e18;
db f(db x){return x+n/pow(2,x/1.5);}
int main(){
	cin>>n;
	while(r-l>1e-10){
		mid1=(2*l+r)/3,mid2=(l+r*2)/3;
		if(f(mid1)<f(mid2))r=mid2;
		else l=mid1;
	}
	printf("%.10lf\n",f((l+r)/2.0));
	return 0;
}

```

---

