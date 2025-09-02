# [NWRRC 2015] Alex Origami Squares

## 题目描述

有一张矩形纸，要求将其裁成三个全等的正方形，且每一个正方形的侧面都与纸张的侧面平行，问裁成的小正方形边长最大是多少。

## 样例 #1

### 输入

```
210 297
```

### 输出

```
105.0
```

## 样例 #2

### 输入

```
250 100
```

### 输出

```
83.333333
```

# 题解

## 作者：ybc2025chenyuyang (赞：3)

# P7048 [NWRRC2015] Alex Origami Squares题解
本题就是一个数学水题，特别简单。
## 题目大意
给你一个长方形，如何剪出 $3$ 个最大的长方形。
## 思路
只需要在 $3$ 个并排和一上两下中取出最大值即可。

代码实现就非常简单，只要去最小值和最大值，按照思路来做就行了，下面给出本题的代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main() {
    cin>>n>>m;
    double a=max(n,m);
    double b=min(n,m);
    printf("%.6f",max(min(b,a/3.0),b/2.0));
    return 0;
}
```


---

## 作者：zt17 (赞：3)

# P7048 题解
[题目传送门](https://www.luogu.com.cn/problem/P7048)

## 分析过程
这道题是一个数学题，我们采取分类讨论的方式得出答案。设长方形的长为 $a$，宽为 $b$。

### 1.$a \ge 3b$
这时很明显答案就是 $b$，易证，在此不详细说明。

### 2.$3b > a \ge 1.5b$
数学好的人可以看出答案是 $\frac{a}{3}$，但是怎么得来的呢？

解题过程：
$$\begin{aligned}
& \because 3b > a \ge 1.5b \\
& \therefore ans \ne b,b > \frac{a}{3} \ge \frac{b}{2} \\
& \because 3b > a \\
& \therefore ans \le \frac{a}{3}\ \\
\end{aligned}$$
得出答案最大为 $\frac{a}{3}$。
### 3.$1.5b \ge a > b$
解题过程：
$$\begin{aligned}
& \because 1.5b \ge a \\
& \therefore ans \le \frac{b}{2}
\end{aligned}$$
得出答案最大为 $\frac{b}{2}$。

完毕。
## 完整代码
```cpp
#include <bits/stdc++.h>
#define IOS cin.tie(0), ios::sync_with_stdio(false)
using namespace std;
typedef unsigned long long ull;
typedef pair<int, int> pii;

int main()
{
    double a, b;
    cin >> a >> b;
    if (a < b)
        swap(a, b);
    if (a >= 3 * b)
        cout << b;
    else if (a > 1.5 * b)
        cout << a / 3;
    else
        cout << b / 2;
    return 0;
}

```
最优解第一面！~~管理大大求过QAQ~~

---

## 作者：BLG_Wu (赞：2)

这是一道非常基础的数学题（确）。

[题目传送门](https://www.luogu.com.cn/problem/P7048)
# 题目分析

我们首先来考虑一共有多少种情况。

首先，不妨设 $h\leqslant w$ 。

可以~~十分抽象地~~考虑到，当 $w\ll h$ 时，选取正方形的边长为 $w$ ，然后考虑临界情况，当给出的图形符合 $w\times 3\eqcirc h$ 时，达到临界点。

然后接着往下看，当矩形的长进一步减小，简单画个图就能知道，三个正方形还应是并列放置的，但**宽**要被裁剪，正方形边长变成了 $\frac{h}{3}$ 。再次考虑临界情况，当裁去的宽还能塞下一个正方形的边长时，三个正方形就可以呈“L”型排列，此时符合 $w\times 3\eqcirc h\times 2$ 即 $w\times 1.5\eqcirc h$ 。

那最后一种情况就是三个正方形呈“L”型排列，此时边长为 $\frac{w}{2}$ 当 $h\eqcirc w$ 达到临界点，因为先前设 $h\leqslant w$ ，所以不存在其他情况。

于是就得到：

$ans = \begin{cases}
  w & w\times 3\leqslant h \\
  \frac{h}{3} & w\times 3> h \land w\times 1.5\leqslant h \\
  \frac{w}{2} & w\times 1.5>h
\end{cases}$

# 代码奉上：
```cpp
#include<bits/stdc++.h>
using namespace std;
float h,w;
int main(){
	scanf("%f%f",&h,&w);
	if(h<w)swap(h,w);
	if(h>=3*w)printf("%f",w);
	else if(h>=1.5*w)printf("%f",h/3);
	else printf("%f",w/2);
	return 0;
}
```


---

## 作者：feiji_code (赞：1)

## 思路：
这道题有 3 种情况，分别是 $h$ 大于等于 $w$ 的 $3$ 倍以上，宽等于 $w$。

$h$ 大于等于 $w$ 的 $1.5$ 倍以上但是小于 $w$ 的 $3$ 倍，宽等于 $h$ 除 $3$。

$h$ 大于等于 $w$ 的 $1$ 倍以上 但是小于 $w$ 的 $1.5$ 倍，宽等于 $w$ 除 $2$。

根据以上的情况，可以得出以下代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	double h,w,a;
	cin>>h>>w;
	if(w>h) {//如果w>h就交换 
		a=w,w=h,h=w;
	}
	if(h>=3*w){
		cout<<w;
	} 
	if(h>=1.5*w&&h<3*w) {
		cout<<h/3;
	}
	if(h>=1*w&&h<1.5*w){
		cout<<w/2;
	}
	return 0;
}
```
但是这样的代码不够简洁，这时候就得用 ```if...else if...else``` 了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	long double h,w,a;
	cin>>h>>w;
	if(w>h) {//如果w>h就交换 
		a=w,w=h,h=w;
	}
	if(h>=3*w){
		cout<<w;
	} 
	else if(h>=1.5*w) {
		cout<<h/3;
	}
	else cout<<w/2;
	return 0;
}
```





---

## 作者：ys_kylin__ (赞：1)

本题其实是一道纯数学题，很简单。最开始，为了接下来方便操作，我们把长根宽我们分别看三种情况：


 1. 假如长比宽大 $3$ 倍以上：此时我们直接把长方形截成三块，边长就是宽。
 
 2. 假如长比宽大 $1.5$ 到 $3$ 倍：此时就可以把长度填满，边长为长 $\div3$。
 
 3. 剩余情况就是两个正方形沿着宽边，还有一个随便放，边长为宽 $\div2$。
 
 然后就没了。
 

------------
代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
void sp(double &x,double &y){if(x<y)swap(x,y);}//让长严格大于宽
int main(){
	double c,k;
	scanf("%lf%lf",&c,&k);//c是长，k是宽
	sp(c,k);
	if(c>=3*k) /*printf("%.lf",k)*/cout<<k;//三种情况 
	else if(c>=1.5*k) /*printf("%.lf",c/3)*/cout<<c/3;
	else /*printf("%.lf",k/2)*/cout<<k/2;
	return 0;
}
```

---

## 作者：nj_peak (赞：0)

**题意**：有一张矩形纸，要求将其裁成三个全等的正方形，且每一个正方形的侧面都与纸张的侧面平行，问裁成的小正方形边长最大是多少。

其实，这是一道比较简单的题，首先我们来分析一项这道题目，一张长方形纸把他尽可能切割成多的正方形，我们只需要考虑一下 $3$ 种情况：
1. 当长大于宽的 $3$ 倍时，那么正方形的边长就是为宽。
2. 当长大于等于宽的 $1.5$ 倍但小于 $3$ 倍时，正方形的边长就是长除以 $3$。
3. 当长大于等于宽的 $1$ 倍但小于 $1.5$ 倍时，正方形的边长就是宽除以 $2$。

注：在写主题部分之前一定要先比较长和宽的大小，不然会出错！

代码：
```cpp
#include<bits/stdc++.h> //万能头。
using namespace std;
double a,b;  //一定要double，不然精度不够。
int main() 
{
	scanf("%lf%lf",&a,&b);
	if(b>a) 
	{
		swap(b,a); 	 // 比较A和B
		}
	if(a>=3*b) 
	{
		printf("%lf",b);	
		}
	else if(a>=1.5*b)	
	{
		printf("%lf",a/3);
		}				
	else 
	{
		printf("%lf",b/2);
		}
	return 0;
}
```


---

## 作者：continueOI (赞：0)

## 题目描述

有一张矩形纸，要求将其裁成三个全等的正方形，且每一个正方形的侧面都与纸张的侧面平行，问裁成的小正方形边长最大是多少。

## 分析

这其实是一道纯数学题，可以将矩形纸片根据长与宽的关系分为3种情况：

### 1.长大于等于宽的 3 倍：

![](https://cdn.luogu.com.cn/upload/image_hosting/pfoswf1c.png)

要取得边长最大的三个相同正方形应将其边长切为 $w$，此时矩形纸长会有剩余或切完。

### 2.长大于等于宽的 1.5 倍但小于 3 倍：

![](https://cdn.luogu.com.cn/upload/image_hosting/82a7lrvz.png)

要取得边长最大的三个相同正方形应将其边长切为 $h/3$，此时矩形纸宽会有剩余或切完。

### 3.长大于等于宽的 1 倍但小于 1.5 倍：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ppyibah.png)

要取得边长最大的三个相同正方形应将其边长切为 $w/2$，此时矩形纸长会有剩余或切完。

## 代码

提示一下，输入时可能矩形纸的宽会比长大，所以在进行矩形纸切割判断前要先判断宽是否大于长。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	double h,w;
	cin>>h>>w;
	if(w>h) swap(w,h); 
	if(h>=3*w) cout<<w;
	else if(h>=1.5*w) cout<<h/3;
	else cout<<w/2;
	return 0;
}
```

---

## 作者：Daben1 (赞：0)

**题目简述**

这道题并不难，重点是数论以及数学思维的运用，也可以说这是一道数学题。

**题目分析**

据长宽比例可以算出三种情况，如果长比宽大三倍以上，那么正方形边长就是宽；如果长在宽的 $1.5$ 倍到 $3$ 倍之间，那么正方形边长就是长除以 $3$；如果长在宽的 $1$ 到 $1.5$ 倍之间，正方形边长就是宽除以 $2$。

**代码书写**

这里输入了长 $h$，以及宽 $w$，此直接将两者代入计算，分类讨论判断上述的这个题目的三种情况即可通过本题。

**AC代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	double h, w, t, r;
	cin >> h >> w; //输入长和宽
	if (w > h) //确定数值大小
		t = w, w = h, h = t; //交换变量的值
	if (w >= 2. / 3 * h)
		r = w / 2.; //1.5倍到3倍之间的第一种情况
	else if (w >= 1. / 3 * h)
		r = h / 3.; //1到1.5倍之间的第二种情况
	else
		r = w; //长比宽大三倍以上的第三种情况
	printf("%lf\n", r);
	return 0;
}

---

## 作者：xxxxxzy (赞：0)

#### P7048的题解

~~建议评红题。~~

三个全等的正方形，要使边长最大，容易想到只有两种情况：

- 三个正方形连续排成一行。

- 三个正方形组成一个差一个角的大正方形。

对于第一种情况，需要判断一下，短的那条边是否有长的那条边的 $\frac{1}{3}$，如果有，那么就以长的边为正方形边长的三倍，否则以短的边为正方形的边长。

对于第二种情况，取最短边一半作边长就行了。

最后再比较大小。

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int h,w;
	double ans=0;
	cin>>h>>w;
	if(h<w) swap(h,w);
	if(w*3>=h) ans=max(ans,h/3.0);
	else ans=max(ans,w*1.0);
	ans=max(ans,min(w,h)/2.0);
	printf("%.3lf",ans);
}
```



---

