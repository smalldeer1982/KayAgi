# Diamond Miner

## 题目描述

[题目链接](https://codeforces.com/problemset/problem/1495/A)

在一个平面直角坐标系上，有 $n$ 个矮人与 $n$ 个钻石。保证所有矮人都在 $y$ 轴上，所有钻石都在 $x$ 轴上，且没有东西在原点

现在，每个矮人都需要去捡一个钻石。假设矮人和钻石的坐标分别为 $(x,y),(u,v)$，那么这个矮人去捡这个钻石所花费的体力就是 $\sqrt{(x-u)^2+(y-v)^2}$（也就是两点间的距离）

求一个钻石的分配方案，使得所有矮人花费的总体力最少，并输出这个最小值

## 说明/提示

$1 \le T \le 10$  
$1\le n \le 10^5,\sum n\le 10^5$  
$|x|,|y|\le 10^8$

## 样例 #1

### 输入

```
3
2
0 1
1 0
0 -1
-2 0
4
1 0
3 0
-5 0
6 0
0 3
0 1
0 2
0 4
5
3 0
0 4
0 -3
4 0
2 0
1 0
-3 0
0 -10
0 -2
0 -10```

### 输出

```
3.650281539872885
18.061819283610362
32.052255376143336```

# 题解

## 作者：TonyYin (赞：16)

2021.11.10upd: 修正题意，"欧几里得距离之和" $\rightarrow$ “欧几里得距离之和**的最小值**”

## 题意

给定 $2n$ 个点，其中 $n$ 个在 $x$ 轴上，另外 $n$ 个在 $y$ 轴上。现在要求每一个 $x$ 轴上的点与一个 $y$ 轴上的点连线，每个点**恰好被连线一次**。求所有线段的**欧几里得距离之和的最小值**。

![](https://pic.tonyyin.top/2021/03/12/60fd2edafc780.png)

## 分析

首先根据数据范围 $n\leq 10^5$，在考场可以判断出贪心或二分。

之后看到样例解释的配图，发现可以抽象出：对于两条线段的模型。

![](https://pic.tonyyin.top/2021/03/12/84106fb92fa8b.png)

由上图可以看出，对于四个点，只有两种连线方法：不交叉或交叉。

**不交叉**的欧几里得距离和为：$|AB|+|CD|$，**交叉**的欧几里得距离为 $|AC|+|BD|$.

经过肉眼观测，我们可以用小学数学证明**不交叉一定优于交叉**：

由于三角形任意两边之和大于第三边，所以 $|AB|<|AO|+|BO|$，$|CD|<|CO|+|DO|$.

于是 $|AB|+|CD|<|AO|+|BO|+|CO|+|DO|=|AC|+|BD|$.

将结论推广到 $n$ 条线段，发现**所有线段都不交叉是最优的**，否则将交叉的两个线段交换，可以使距离和更小。

考虑如何按照这个方法，对所有点进行两两配对。

容易想到，把所有处于负半轴上的点，**对称到正半轴上**。这样处理后距离和不变。

所以，把 $x$ 轴上的点和 $y$ 轴上的点分别按照横竖坐标**升序排序**，排名相同的点进行配对，一定不会交叉。

## 代码

考场代码）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 10;
int T;
double a[MAXN], b[MAXN];
signed main() {
    cin >> T;
    while(T--) {
        int n, cnt1 = 0, cnt2 = 0; cin >> n;
        for(int i = 1; i <= 2 * n; i++) {
            int x, y; scanf("%lld%lld", &x, &y);
            if(x == 0) {
                if(y < 0) y *= -1;
                a[++cnt1] = y;
            }
            if(y == 0) {
                if(x < 0) x *= -1;
                b[++cnt2] = x;
            }
        }
        sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
        double ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += sqrt(a[i] * a[i] + b[i] * b[i]);
        }
        printf("%.11lf\n", ans);
    }
    return 0;
}
```





---

## 作者：血色黄昏 (赞：3)

十年 OI 一场空，强转 ll 见祖宗 /dk

题意是在 x 和 y 轴上都有 n 个点，要求你把这 2n 个点一个点只能连一个点连起来，要求距离最短。

看数据范围就知道不能枚举，那么看这种题就是贪心，大力猜想，小心论证（~~虽然那天我赶时间就乱写了一个没证）~~

以经验而言，每次连接离原点最近的两个点总距离会最小，之后我们可以~~口胡~~证一下

设有四个点 $(x_1, 0), (x_2, 0), (0, y_1), (0, y_2),x_1 < x_2,y_1<y_2$ ，我们目的是证
$\sqrt{x_1^2+y_1^2}+\sqrt{x_2^2+y_2^2} \le \sqrt{x_1^2+y_2^2}+\sqrt{x_2^2+y_1^2}$ ，其余情况的同理

那么开方后两边减去所有数的平方得 $(x_1^2+y^2_1)(x_2^2+y^2_2) \le (x_1^2+y^2_1)(x_2^2+y^2_2)$ ，因为我们贪心时取绝对值较小的数，所以说各数平方后大小顺序不变那么，根据小学就探究过的如果四个数分两组两组相加为同一个数，那么两个数差越小积越大即可得证

那么就可以愉快的开始贪心10min切掉这道题了

但是如果你 $10^8$ 的大小的数开一个 int 这么写

```
int a[100001],b[100001];
long double ans = 0;
ans += sqrt(1.0 * (long double)(a[i] * a[i]) + 1.0 * (long double)(b[i] * b[i]));
```

那么恭喜你，你在 Pretest 2 就会挂掉，会输出 nan。

所以记得不要像我一样习惯性为了省空间结果强制转换炸了死活挑不出来 /kk

下面放正解代码，虽然是我赛后写的 qwq

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, t, k, a[100010], b[100010];//定义数组
bool cmp(int a, int b)//按绝对值排序
{
	return abs(a) < abs(b);
}
int main()
{
	cin>>t;
	while(t --)//多测
	{
		long double ans = 0;//答案
		int cnt1 = 0, cnt2 = 0;//两个数组记录到那里了
		cin>>n;
		for(int i = 1;i <= n;i ++)
		{
			int x, y;
			cin>>x>>y;
			if(x == 0)a[++ cnt1] = y;//分坐标轴读入
			else b[++ cnt2] = x;
			cin>>x>>y;
			if(x == 0)a[++ cnt1] = y;//同上
			else b[++ cnt2] = x;
		}
		sort(a + 1, a + n + 1, cmp);//排序
		sort(b + 1, b + n + 1, cmp);
		for(int i = 1;i <= n;i ++)
		{
			ans += sqrt(1.0 * (long double)(a[i] * a[i]) + 1.0 * (long double)(b[i] * b[i]));//每次加最近两个的相对距离
		}
    	cout<<setiosflags(ios::fixed)<<setprecision(30);//输出精度开到1e-30
    	cout<<ans<<endl;//输出
	}
    return 0;
}
```


---

## 作者：Silence_water (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1495A)

---

**Analyse**

由于将 $x$ 或 $y$ 取绝对值后答案不变，因此读入时直接转为绝对值即可。

考虑下图情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/ih0j7mo1.png)

此时可能的答案有 $ans_1=|AC|+|BD|$ 或 $ans_2=|AD|+|BC|$。

此时有 $ans_2=|AD|+|BC|=|OC|+|OA|+|OD|+|OB|>|AC|+|BD|=ans_1$。

故选择图中红线是最优的。

将 $y=0$ 的点按照 $|x|$ 从小到大排序，将 $x=0$ 的点按照 $|y|$ 从小到大排序，对应一一连线，这些连线的长度和就是答案了。

----

**Solution**

注意精度问题和强制转 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
int T,n,k,a[M],b[M];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
    	scanf("%d",&n);
    	int a0=0,b0=0;
    	for(int i=1;i<=2*n;i++)
    	{
    		int x,y;
    		scanf("%d%d",&x,&y);
    		if(y==0)a[++a0]=abs(x);
    		else b[++b0]=abs(y);
		}
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		double ans=0.0;
		for(int i=1;i<=n;i++)
			ans+=sqrt((long long)a[i]*a[i]+(long long)b[i]*b[i]);
		printf("%.11lf\n",ans);
	}
    return 0;
}
```

---

**The end**

感谢您的观看！如有不足，请麻烦指正哦。

---

## 作者：Priori_Incantatem (赞：2)

[题目链接](https://codeforces.com/problemset/problem/1495/A)  
[在我的Blog查看](https://blog.csdn.net/Brian_Pan_/article/details/114655180)

本题其实就是一个贪心

首先我们把题意转化一下，变为：  
有 $n$ 条横向边与 $n$ 条纵向边，现在要将他们两两配对，满足组成的直角三角形的斜边和最小。

**方法 1**

我们先将这些边任意配对，并尝试将它修改地更优。  
那么，刚开始的配对情况可能长这样：  
![image.png](https://img-blog.csdnimg.cn/img_convert/349f4ff7344d31d52a13d26871af0776.png)

我们尝试修改：

![image.png](https://img-blog.csdnimg.cn/img_convert/709d11405929b397b572521e8a6e8b42.png)

如上图，根据三角形边长定理，显然红边长度和小于绿边长度和。那么我们就用红边来替代绿边。

那么，对于每两条交叉的边，我们按如上方法对分配方案进行修改。最后，这些斜边肯定是两两不相交的。所以，我们只需要按边长排序，然后长边跟长边配，短边跟短边配即可。

**方法 2**

这个是我赛时口胡出来的方法，比较不严谨QwQ。

首先，如果题目是要求求距离的平方和的话，那答案就是所有直角边的平方之和。我们设这个答案为 $val$。

根据根号的性质，如果 $x$ 越大，那么 $x-\sqrt x$ 就越大。  
换而言之，我们将越大的数开方，数值减少的效果就显著。  
那么，我们尽量地把长的直角边配成对，就可以让最终答案与 $val$ 的差尽可能大，答案也就最优了。

由于两个方法得到的结论一样，这里就只贴一份代码。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int Maxn=1e5+10;
long double a[Maxn],b[Maxn];
int n;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	// freopen("in.txt","r",stdin);
	int T=read();
	while(T--)
	{
		n=read();
		int tot=0,cnt=0;
		for(int i=1;i<=(n<<1);++i)
		{
			int x=read(),y=read();
			if(!x)a[++tot]=(double)abs(y);
			else b[++cnt]=(double)abs(x);
		}
		sort(a+1,a+1+n);
		sort(b+1,b+1+n);
		long double ans=0.0;
		for(int i=1;i<=n;++i)
		ans+=sqrt(a[i]*a[i]+b[i]*b[i]);
		printf("%.12Lf\n",ans);
	}
	return 0;
}
```

---

## 作者：vectorwyx (赞：1)

注意到矿工开采某个钻石矿所耗费的能量只与矿工纵坐标的平方 $t$ 以及钻石矿横坐标的平方 $w$ 有关，而且 $t$ 和 $w$ 是相互独立的，因此我们可以把所有坐标的非零项的平方作为新的权值，问题就变成了给定两个长度为 $n$ 的正整数序列 $A,B$，要求最小化 $\sum_{i=1}^n \sqrt{A_{i}+B_{p_{i}}}$，其中 $p$ 为 $1\sim n$ 的某个排列。

先从最简单的情况入手，假设 $n=2$，$A$ 中的元素为 $a,b$，$B$ 中的元素为 $c,d$，那么答案只有两种可能：$\sqrt{a+c}+\sqrt{b+d},\sqrt{a+d}+\sqrt{b+c}$。不妨设 $a<b,c<d$，两边同时平方后再相减，得 $2(\sqrt{(a+c)(b+d)}-\sqrt{(a+d)(b+c)})$。因为 $(a+c)(b+d)-(a+d)(b+c)=(b-a)(c-d)<0$，所以 $2(\sqrt{(a+c)(b+d)}-\sqrt{(a+d)(b+c)})<0$，所以 $\sqrt{a+c}+\sqrt{b+d}<\sqrt{a+d}+\sqrt{b+c}$。

这也就是说小的配小的，大的配大的始终比小的配大的大的配小的优，在几何意义上讲就是交叉的线段始终不如不交叉的线段。那么 $n$ 个元素的情况也是同样的道理，故我们只需要求出 $A,B$ 再排个序，把对齐元素的和的平方根求和即可。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<algorithm>
#define db long double
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e5+5;
ll a[N],b[N],t1,t2;

void work(){
	t1=t2=0;
	int n=read();
	fo(i,1,2*n){
		ll x=read(),y=read();
		if(x==0) a[++t1]=y*y;
		else b[++t2]=x*x;
	}
	sort(a+1,a+1+n);sort(b+1,b+1+n);
	//fo(i,1,t1) printf("%lld ",a[i]);puts("");
	//fo(i,1,t2) printf("%lld ",b[i]);puts("");
	db ans=0;
	fo(i,1,n) ans+=sqrt(a[i]+b[i]);
	cout<<fixed<<setprecision(15)<<ans<<endl;
	//puts("");
}

int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：Ryo_Yamada (赞：1)

作为 Div.2 的 C 题感觉简单了点（

[题目传送门](https://www.luogu.com.cn/problem/CF1495A)，题意已经有了就不翻了。

首先，因为所有点都在 $x$ 轴或 $y$ 轴上，取绝对值不影响结果，我们可以把所有点的坐标去绝对值，即都移动到正半轴或原点上。

此时四个点两种连边方式的选择，有交叉和不交叉两种方式。显然不交叉比交叉更优。所以我们将所有数按它们的绝对值排序，随后两两配对一定最优。

Code ：

```cpp
bool cmp(ll x, ll y) {
	return abs(x) < abs(y);
}

//...

long double ans = 0.0;
c1 = c2 = 0;
int n; qread(n);
rep(i, 1, (n << 1)) {
	int a, b;
	qread(a, b);
   if(!a) y[++c2] = b;
   else x[++c1] = a;
}
sort(x + 1, x + n + 1, cmp);
sort(y + 1, y + n + 1, cmp);
rep(i, 1, n) {
	ans += sqrt(x[i] * x[i] + y[i] * y[i]);
}
printf("%.15Lf\n", ans);
```


---

## 作者：Skies (赞：1)

- ## solution

首先，正负对于答案没有影响（因为由负转正可以看成对称，没有影响）。

然后，对于4个点，$(x1,0),(x2,0),(0,y1),(0,y2)$。

设 $ x1<x2   ,y1<y2$。

那么有两种选择：

1. 选 $(x1,0),(0,y1)$和$ (x2,0),(0,y2)$，令它的代价为ans1

2. 选 $(x2,0),(0,y1)$和$ (x1,0),(0,y2)$，令它的代价为ans2

现在我们来比较ans1,ans2的大小

$
ans1=\sqrt{x1\times x1+y1\times y1}  +\sqrt{x2\times x2+y2\times y2}$


$
ans2=\sqrt{x2\times x2+y1\times y1}  +\sqrt{x2\times x2+y1\times y1}$

$
ans1^2=x1\times x1+y1\times y1+x2\times x2+y2\times y2+2\times \sqrt{(x1\times x1+y1\times y1)\times (x2\times x2+y2\times y2)} $


$
ans2^2=x2\times x2+y1\times y1  +x2\times x2+y1\times y1+2\times \sqrt{(x2\times x2+y1\times y1)\times (x1\times x1+y2\times y2)}$

因为**和一定，差小积大，差大积小**

即

$
(x2\times x2+y1\times y1)\times (x1\times x1+y2\times y2)>(x1\times x1+y1\times y1)\times (x2\times x2+y2\times y2)
$



所以$ans1<ans2$

因此，我们只要每次选矿工中和钻石中绝对值最小的即可。

代码还是比较好实现

我的毒瘤码风最好还是别看，自己打一遍。

[我的代码](https://www.luogu.com.cn/paste/jlud4x6i)

---

## 作者：_Clown_ (赞：0)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF1495A}$|$\texttt{洛谷难度:暂无评定}$|[$\texttt{On 2021/03/12}$](https://www.luogu.com.cn/record/47750419)|
# 解析
这是一道简单题。

题意不难理解。

我们考虑贪心。

实际上只有两种情况：
- 双线交叉。
- 双线不交叉。

因为两边之和大于第三边，

所以所有的线段都不交叉一定是最优的。

我们只需要按照 $abs$ 值排个序，

然后小的和小的对，大的和大的对即可。

至于距离，相信大家都知道：
$$
Dist=\sqrt{((X1-X2)^2 + (Y1-Y2)^2}
$$
```cpp
/*
Author:Xsmyy
Problem:CF1496C
Date:2021/03/10
*/
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int A[500001],B[500001];
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("SampleIN.in","r",stdin);
	#else		
	#endif
	register int Case;
	cin>>Case;
	while(Case--)
	{
		register int N;
		cin>>N;
		register int i;
		for(i=1;i<=N;i++)A[i]=0;
		for(i=1;i<=N;i++)B[i]=0;
		register int C,D;
		C=D=0;
		for(i=1;i<=(N<<1);i++)
		{
			register int X,Y;
			cin>>X>>Y;
			if(!X)A[++C]=abs(Y);
			else B[++D]=abs(X);
		}
		sort(A+1,A+C+1);
		sort(B+1,B+D+1);
		register double Ans;
		Ans=0;
		for(i=1;i<=N;i++)Ans+=1.0*sqrt(1.0*A[i]*A[i]+1.0*B[i]*B[i]);
		printf("%.15lf\n",Ans);
	}
	return 0;
}
```


---

## 作者：清烛 (赞：0)

### 题意
在 $x$ 轴上有 $n$ 个钻石矿，$y$ 轴上有 $n$ 个矿工，保证所有的矿工和钻石都不在原点。需要建立每个矿工与每个钻石矿的一一对应关系使得每对矿工和矿的距离之和最小。

### 题解
$n$ 的数据范围为 $10^5$，暗示了我们要么是贪心要么是 $O(n)$ 的 dp，先考虑两对矿工和钻石的情况：（由于正负其实不影响，所以我们把所有的钻石和矿的坐标都取绝对值，在正半轴上考虑问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/mr5jap3w.png)

如上图，假设有两个钻石矿 $(a,0)$ 和 $(b,0)$，且 $a\lt b$；和两个矿工 $(0,c)$ 和 $(0,d)$，且 $c\lt d$。

这种两对点的情况无非就是**交叉着连**（蓝线）和**平行着连**（红线）。所以考虑哪个要大一些：

即比较 $\sqrt{a^2 + d^2} + \sqrt{b^2 + c^2}$ 和 $\sqrt{a^2 + c^2} + \sqrt{b^2 + d^2}$ 的大小。

两边同时平方：

$$
a^2 + b^2 + c^2 + d^2 + \sqrt{(a^2 + d^2)(b^2 + c^2)}
$$

和

$$
a^2 + b^2 + c^2 + d^ 2+ \sqrt{(a^2 + c^2)(b^2 + d^2)}
$$

所以只需要考虑 $(a + d)(b+ c)$ 与 $(a + c)(b + d)$ 的大小即可，化简之后不难发现

$$
(a + d)(b + c)\ge(a + c)(b + d)
$$

所以**平行的连法一定是最优的**。将所有的点取绝对值后排序然后依次累加答案就搞定了。

```cpp
#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

typedef double db;

const int maxn = 1e5 + 5;
db x[maxn], y[maxn];
int n, cntx, cnty;

int main()
{
    int T = read();
    while (T--)
    {
        n = read();
        db ans = 0;
        cntx = cnty = 0;
        FOR(i, 1, n << 1)
        {
            int xx = read(), yy = read();
            if (!xx) y[++cnty] = yy;
            if (!yy) x[++cntx] = xx;
        }
        std::sort(x + 1, x + cntx + 1);
        std::sort(y + 1, y + cnty + 1);
        FOR(i, 1, n)
            ans += sqrt(x[i] * x[i] + y[i] * y[i]);
        printf("%.15lf\n", ans);
    }
    return 0;
}
```


---

## 作者：cmll02 (赞：0)

首先这个正负没有影响，所以直接读入绝对值。

之后证明：坐标绝对值小的和小的连更优。

大概是这样：（显然 $a,b,c,d$ 是坐标的平方）

令 $a>b>0,c>d>0$,

$(\sqrt{a+c}+\sqrt{b+d})^2=a+b+c+d+2\sqrt{ab+ad+bc+cd}$

$(\sqrt{a+d}+\sqrt{b+c})^2=a+b+c+d+2\sqrt{ab+ac+bd+cd}$

根号外面的一样，根号里面的作差就可以比出大小。

那就不用说了，排个序直接连就行了。

```cpp
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#include <math.h>
#define int long long
inline int read()
{
	int num=0,f=1;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num;
}
int a[100005],b[100005];
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		int cnt1=0,cnt2=0;
		for(int i=0;i<n+n;i++)
		{
			int x=read(),y=read();
			if(x==0)b[cnt2++]=y;
			else a[cnt1++]=x;
		}
		std::sort(a,a+n);
		std::sort(b,b+n);
		double ans=0.0;
		for(int i=0;i<n;i++)
		{
			//int j=n-i-1;
			int j=i;
			//printf("match %lld %lld\n",a[i],b[j]);
			ans+=sqrt(1.0*a[i]*a[i]+1.0*b[j]*b[j]);
		}
		printf("%.10lf\n",ans);
	}
}
```

---

