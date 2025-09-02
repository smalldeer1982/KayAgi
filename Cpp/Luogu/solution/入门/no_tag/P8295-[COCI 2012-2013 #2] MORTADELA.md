# [COCI 2012/2013 #2] MORTADELA

## 题目背景

**本题分值按 COCI 原题设置，满分 $50$。**

## 题目描述

全国连锁超市（NSC）喜欢吹嘘它们的意式肉肠是全国最低的。

实际上，如果顾客打算在其他连锁超市里找到更便宜的肉肠，那么 NSC 会向其补上差价。

Matej 和 Filip 决定接受这个挑战。他们将会挨个走访 $N$ 家不同连锁店，来找到不仅比 NSC 便宜的熟香肠，而且在市场上最便宜的。如果他们成功了，他们就可以在他们学校附近的 NSC 分店买到最便宜的香肠。

NSC 希望没有人能找到更便宜的香肠，因为所有所有连锁超市（包括 NSC）都以一种复杂的方式表示香肠的价格：$X$ 元 $Y$ 克香肠。

请编写一个程序，给定 NSC 与其余 $N$ 家连锁店中的香肠价格，求 Matej 和 Filip 必须为靠近学校的 NSC 中的 $1000$ 克熟香肠支付的价格。

## 样例 #1

### 输入

```
5 100
3
4 100
3 100
7 100```

### 输出

```
30.00```

## 样例 #2

### 输入

```
13 6
5
56 679
35 120
99 999
56 73
37 532```

### 输出

```
69.55```

## 样例 #3

### 输入

```
100 5
3
99 8
65 14
78 10```

### 输出

```
4642.86```

# 题解

## 作者：liangbowen (赞：4)

### 前言

[题目传送门](https://www.luogu.com.cn/problem/P8295)

[$\color{red}{see}\space \color{green}{in}\space \color{blue}{my}\space \color{purple}{blog}$](https://www.luogu.com.cn/blog/liangbowen/solution-P8295)

这题并不困难，代码也挺短的，题目理解稍有困难。

### 题目大意

有 $(n+1)$ 家商店，也就是 $n$ 家商店与 NSC 商店。

求 这 $(n+1)$ 家商店 $1000$ 克香肠的价钱的**最小值**。

### 思路

将所有商店 $1000$ 克香肠的价钱都求出来，再求最小值即可。

比如，$x$ 元 $y$ 克的香肠，转换成 $1000$ 克就是 $\dfrac{1000 \times x}{y}$ 元。

代码就很容易写了，注意最后需要保留两位小数。

### 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int x, y;
	scanf("%d%d", &x, &y);
	double ans = 1.0 * x / y * 1000;  //乘上 1.0 强制变成浮点数。 
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &x, &y);
		ans = min(ans, 1.0 * x / y * 1000);
	}
	printf("%.2lf", ans);  //强制保留两位小数。 
	return 0;
}
```

---

## 作者：hepp (赞：3)

本题其实就是求 $n+1$ 组数中 $x/y$ 最小的。

注意 $n$ 输入时在第二行。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    double x,y;
    int n;
    scanf("%lf%lf",&x,&y);
    scanf("%d",&n);
    double ans=x/y*1000;//x/y是1克的价钱，x/y*1000就是1000克的价钱
    while(n--)//等同于for(int i=1;i<=n;i++) 不过这里n会逐渐变小
    {
        double u,v;
        scanf("%lf%lf",&u,&v);
        ans=min(ans,u/v*1000);//取其中最小的
    }
    printf("%.2lf",ans);//输出时注意保留两位小数
    return 0;
}
```

---

## 作者：TernaryTree (赞：3)

## 简化题意

给定第 $i$ 家香肠店香肠的 $n+1$ 个价格 $X_i$ 和重量 $Y_i$，求买 $1000$ 克香肠最低的价格。

## 思路分析

对于第 $i$ 个香肠，每克的价格就是 $\dfrac{X_i}{Y_i}$。

我们设最初的最低价格 $t=\dfrac{X_{NSC}}{Y_{NSC}}$。然后遍历 $X_i,Y_i$，如果比 $t$ 小则更新 $t$，遍历结束就得到了每克香肠的最低价。

输出记得乘上 $1000$，并保留 $2$ 位小数。

## 完整代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 1;

int n, x, y;
double t;

int main() {
    cin >> x >> y;
    t = (double) x / y;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        t = min(t, (double) x / y);
    }
    cout << fixed << setprecision(2) << t * 1000 << endl;
    return 0;
}

```

---

## 作者：Galaxy_Q (赞：1)

### 题目大意：
分别给出 $NSC$ 和其他商店所售的 $Y$ 克香肠和它所对应的价钱 $X$ 元，之后找到最便宜的香肠 $1kg$ 所对应的价钱.


### 题目分析：
需要有以下几个注意点（~~简单模拟~~）：

1. 输出要保留两位小数

2. $NSC$ 商店的价格也要计算

3. 输出价格为买 $1kg$ 香肠的价格


### 代码实现如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
double a[110],b[110],ans=9999999;
int n;
signed main() {
	scanf("%lf%lf",&a[1],&b[1]);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i+1],&b[i+1]);
	for(int i=1;i<=n+1;i++)
		ans=min(ans,a[i]/b[i]*1000);
	printf("%.2lf\n",ans);
	return 0;
}
```


---

## 作者：WilliamFranklin (赞：1)

这道题不愧是入门。

## 主要思路

这其实就是比较 $n+1$ 个商店。

### 第一种方法：

我们可以算出每一个商店香肠的单价，也就用 $x$ 除以 $y$ 可以得出单价，然后再求出单价最小值，乘以 $1000$ 即可。

好啦，上代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n, x, y;
	double minn;
	cin >> x >> y;
	minn = (double)x / y;
	cin >> n;
	for (int i = 2; i <= n + 1; i++) {
		cin >> x >> y;
		minn = min((double)x / y, minn);
	}
	printf("%.2lf", minn * 1000);
	return 0;
}
```

### 第二种方法：

我们其实可以直接求出买 $1000$ 克每一个商店所需的钱，就是 $1000/y*x$，再求出它们的最小值即可。

好啦，贴代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n, x, y;
	double minn;
	cin >> x >> y;
	minn = 1000.00 / y * x;
	cin >> n;
	for (int i = 2; i <= n + 1; i++) {
		cin >> x >> y;
		minn = min(1000.00 / y * x, minn);
	}
	printf("%.2lf", minn);
	return 0;
}
```

祝贺 $\color{lightgreen}AC$！！！

---

## 作者：iiiiiiiiiiiiiiiiiii (赞：1)

## 题目大意

给你总店和 $n$ 家连锁店买 $y$ 克香肠需要的价格 $x$，求买 $1000$ 克香肠的最小价格。

## 算法

先算出每家商店的单价，再算出买 $1000$ 克需要的总价，取最小值即可。别忘了总店也要计算哦。

## 代码

```cpp
//read()是输入
double s,t,ans;
int n;
signed main()
{
	scanf("%lf%lf",&s,&t);
	n=read();
	ans=1000.0/t*x;
	for(int i=1;i<=n;i++)
	{
		double x=read(),y=read();
		ans=min(ans,1000.0/y*x);
	}
	printf("%.2lf",ans);
	return 0;
}

```


---

## 作者：ZepX_D (赞：0)

## 题意
给你几个市场的肉肠的价格，求出买 $ 1000 $ 克肉肠最少需要多少元

## 分析
很显然，我们只要找出单价最低的商场就可以。
记得不要把 $ NSC $ 漏了就可以

## 代码
```cpp
#include<cstdio>
#include<iostream>

using namespace std;


int main()
{
	int x,y,n;
	scanf("%d%d%d",&x,&y,&n);
	double ans=(1000.0/y)*x;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		ans=min(ans,1000.0/y*x);
	}
	printf("%.2lf",ans);
	return 0;
}
```


---

## 作者：int32 (赞：0)

若 $x$ 根香肠 $y$ 元，则每根香肠单价为 $\dfrac xy$ 元。对于每个商家比较即可。注意答案输出是买 $1000$ 根香肠的钱而非 $1$ 根。

本题可以忽略浮点数精度误差，不影响 AC。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int xnsc, ynsc, n;
int x[N], y[N];
double ans;
signed main(){
    cin>>xnsc>>ynsc>>n;
    ans=1000.0*xnsc/ynsc;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    for(int i=1;i<=n;i++){
        if(xnsc*y[i]>ynsc*x[i])
        ans=min(ans,1000.0*x[i]/y[i]);
    }
   printf("%.2lf",ans);
    return 0;
}
```

---

## 作者：sgl654321 (赞：0)

### 题目大意
有 $n+1$ 个香肠店，每个店都标明了该店 $x$ 元可以购买的香肠质量 $y$。请求出最便宜的店，买 $1000$ 克香肠所需要的钱数。保留 $2$ 位小数。

### 解题思路
由于第 $i$ 家店 $(i\in[0,n])$ 中 $x_i$ 元可以买 $y_i$ 克香肠，根据小学公式，可以知道每家店的单价 $p_i=\dfrac{x_i}{y_i}$。找出最便宜的店，实际上就是找出最小的 $p_i$。所以整理信息，题目实际上想要求的是这个： 
- 输入 $3$ 个整数 $x_0,y_0,n$。
- 再输入 $n$ 个整数 $x_i$ 和 $n$ 个整数 $y_i$，其中 $i\in[1,n]$。
- 求对于所有的 $i\in [0,n]$ 中，$\min\{\dfrac{x_i}{y_i}\}\times 1000$ 的值。保留 $2$ 位小数。

以样例 $1$ 为例：

- $x_0=5,y_0=100,p_0=\dfrac{x_0}{y_0}=0.05$
- $x_1=4,y_1=100,p_1=\dfrac{x_1}{y_1}=0.04$
- $x_2=3,y_2=100,p_2=\dfrac{x_2}{y_2}=0.03$
- $x_3=7,y_3=100,p_3=\dfrac{x_3}{y_3}=0.07$

$\therefore \min\{p_i\}$，即 $\min\{\dfrac{x_i}{y_i}\}=0.03$。应输出 $30.00$。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n,x,y;
double ans,mi;
int main(){
	cin>>a>>b;
	mi=a*1.0/b;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		mi=min(mi,x*1.0/y);
	}
	ans=mi*1000;
	printf("%.2lf",ans);
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

# 题意
有 $n$ 种香肠，对于每种香肠，给定 $X,Y$，表示 $Y$ 克这种香肠值 $X$ 元。

同时还有一种 $NSC$ 香肠，也给定 $X,Y$，表示 $Y$ 克 $NSC$ 香肠值 $X$ 元。

要买 $1000$ 克香肠，问这 $n+1$ 种香肠中，最便宜的那一种需要多少钱？
# 思路
我们知道 总价 = 单价 × 数量，也就是 总价 = 单价 × 1000。

可以看出第 $i$ 种香肠的单价为 $\dfrac{Y_i}{X_i}$，花费即为 $\dfrac{1000Y_i}{X_i}$。

注意：除法运算时，要保证两个操作数中至少有一个浮点数。
# 代码
```cpp
#include <cstdio>
int n, a, b;double s, t;
int main()
{
    scanf("%d%d%d", &a, &b, &n);s = 1000.0 * a / b;
    while(n--) scanf("%d%d", &a, &b), (t = 1000.0 * a / b) < s && (s = t);
    return printf("%.2lf", s), 0;
}
```


---

## 作者：arrow_king (赞：0)

## 一道非常适合练手的题目
这个题其实主旨在于计算每家超市香肠的价格。    

我们用一个 `double` 型数组 $price$ 来表示香肠的价格，$price_i$ 表示第 $i$ 家商店香肠价格。特别的，$price_0$ 表示 NSC 的香肠价格。

因为香肠的价格格式为 $X$ 元 $Y$ 克香肠，所以我们计算单价时需要计算的是 $\dfrac{X}{Y}$。

下面给出计算单价的代码：
```cpp
price[i]=x*1.0/y;    //为保证精度，x在除以y之前需要乘以1.0
```
为了优化常数，我们可以边读入边计算单价，同时统计最小值。

**核心代码如下：**
```cpp
double minn=price[0];    //先将最小值初始化为NSC的单价
for(int i=1;i<=n;i++) {
	scanf("%d%d",&x,&y);
	price[i]=x*1.0/y;
	if(price[i]<minn) minn=price[i];    //统计最小值
}
```
时间复杂度 $\mathcal{O}(n)$，但是数据量较小，常数大一点也没什么。

---

## 作者：MrCR7 (赞：0)

## 题意简化
给定 $n$，输入 $n+1$ 组 $x_i$ 与 $y_i$，$x_i$ 是第 $i$ 家超市 $y_i$ 个单位的价格。

输出 $1000$ 个单位需要的最小价格。
## 思路分析
我们可以求出在第 $i$ 家商店 $1$ 个单位所需要的价格，用最小的价格乘 $1000$ 即可。
## Ac Code
```cpp
#include <bits/stdc++.h>
using namespace std;
double a[103];//定义数组。
int main (){
	double x, y;
	scanf ("%lf%lf", &x, &y);//第一家的价格，把它的单位价格放在a[0]。
	a[0]=x/y;
	int n;
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){//如题。
		double xx, yy;
		scanf ("%lf%lf", &xx, &yy);
		a[i]=xx/yy; //求出每一家超时的单价。
	}
	sort (a, a+n+1);//从小到大排序。
	printf ("%.2lf", a[0]*1000);//a[0]便是最少的单位价格。
	return 0;
} 
```
这道题就这样啦！

审核的管理员辛苦啦！

---

## 作者：Dangerou (赞：0)

首先，根据题意不难发现，因为要买的量是一定的，要求最低价格，实际上就是在所有店铺中选择单价最低的那一家的单价作为学校附近连锁店的单价。因此，只需要求出所有连锁店中单价最低的那家店铺的单价，然后乘上要买的量即可。（注意要使用浮点型存储价格和质量）

代码如下：
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n;
double v[101],w[101];//v[]储存题目所提供的价格，w[]储存题目所提供的质量
double ans=0x3f3f3f;//初始化一个极大的值（因为要求的是最小值）
int main()
{
	scanf("%lf%lf",&v[1],&w[1]);//把学校附近的连锁店也囊括其中
	scanf("%d",&n);
	n++;
	for(int i=2;i<=n;i++) scanf("%lf%lf",&v[i],&w[i]);//不要直接单价，不然会有误差存在
	for(int i=1;i<=n;i++) ans=min(ans,v[i]*1000/w[i]);//求最小值，先乘或先除的效果差不多，但是先乘能降低误差
	printf("%.2lf\n",ans);//用printf输出浮点型的代码更简洁
	return 0;
}
```


---

## 作者：JustinXiaoJunyang (赞：0)

思路分析：

由于 mortadella 的价格是以非标准格式“$X$ 美元兑换 $Y$ 克”表示的，因此我们应该首先将其转换为可以比较的格式。一种可能的方法是计算一克莫塔黛拉的价格。它可以通过价格除以质量得到。最后，我们必须找到一克的最低价格，然后乘以 1000。

参考代码：

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double x, y;
    cin >> x >> y;
    int n;
    cin >> n;
    double price = x / y;
    for (int i = 1; i <= n; i++)
    {
        double xi, yi;
        cin >> xi >> yi;
        if (xi / yi < price) price = xi / yi;
    }
    cout << setprecision(2) << fixed << price * 1000 << endl;
    return 0;
}
```

---

## 作者：可爱的小于 (赞：0)

**题目大意：** 给定 $n+1$ 个香肠的价格和数量，求最便宜的 $1000$ 克香肠所需的钱数。

**算法标签：** 循环。

**思路：** 输入价格和数量，求出香肠每克的价格，并用一个值进行最小值替换，当然也可以用数组进行排序。注意最后要乘以 $1000$ 并保留两位小数。

保留两位小数的方法：

`cout<<fixed<<setprecision(2)<<a[1]*1000.0;` 

`printf("%.2lf",sum*1000.0);`

 
代码 $1:$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double x,y,sum;
int main() 
{
    cin>>x>>y;
    cin>>n;
    sum=x/y;//求出初始价格
    while(n--){
        cin>>x>>y;//输入n个价格
        sum=min(sum,x/y);//求出最小值
    }
    printf("%.2lf",sum*1000.0);//保留两位小数并输出
    return 0;
}
```

代码$2:$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double a[105],x,y;
int main()
{
    cin>>x>>y;
    a[1]=x/y;//初始价格
    cin>>n;
    for(int i=1;i<=n;i++){//输入 n 个价格
        cin>>x>>y;
        a[i+1]=x/y;//求出每个价格
    }
    sort(a+1,a+2+n);//排序，求出最小值
    cout<<fixed<<setprecision(2)<<a[1]*1000;//保留两位小数并输出
    return 0;
}
```




---

## 作者：BlackPanda (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/P8295)**

------------
### 题意：
给定一个标准价格和 $n$，然后给出 $n$ 个不同的价格，找出最便宜的买 $1000$ 克香肠的价格。

------------
### 思路：
模拟题，直接根据题意进行模拟即可。

可以进行比较每家店每克的价格，最后在乘 $1000$ 即可。

------------
### code：
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

int x,y,n;
double ans;

int main(){
	x=read();y=read();n=read();
	ans=1.0*x/y;
	for(int i=1;i<=n;i++){
		x=read();y=read();
		ans=min(ans,1.0*x/y);
	}
	printf("%.2lf",ans*1000);
	return 0;
}


```

---

## 作者：Micnation_AFO (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8295#submit)


------------

>**题目大意**：给定 $n + 1$ 个 $x$ 和 $y$，让你求出 $\frac{x}{y} \times 1000$ 的 最小值。

注意第一行输入的是一对 $x$ 与 $y$，第二行输入的才是 $n$，剩下的用循环取最小值即可。可以建立临时变量以减少内存消耗。

保留两位小数方法：
```cpp
printf("%.2lf\n", ans * 1000);
```

**AC Code：**
```cpp
#include <iostream>
using namespace std;

#define int long long
#define yn y_n
double xn, yn;
int n; 
double ans;

double min(double a, double b) { return a < b ? a : b; }

signed main() {
    cin >> xn >> yn;
    cin >> n;
    ans = xn / yn;
    while (n--) {
        double x, y;
        cin >> x >> y;
        ans = min(x / y, ans);
    }
    printf("%.2lf\n", ans * 1000);
    return 0;
}

```

---

