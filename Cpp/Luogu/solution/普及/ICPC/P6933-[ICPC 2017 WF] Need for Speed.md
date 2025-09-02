# [ICPC 2017 WF] Need for Speed

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/c7b5cigq.png)

Sheila 是一名学生，她开着一辆典型的学生车：这辆车又旧又慢，生锈并且快要散架了。最近，车速表上的指针掉了下来。她把它粘回去了，但可能放错了角度。因此，当车速表显示速度为 $s$ 时，她的真实速度是 $s+c$，其中 $c$ 是一个未知常数（可能为负）。 

Sheila 详细记录了最近的一次旅程，并希望利用这些记录来计算 $c$。这次旅程由 $n$ 段组成。在第 $i$ 段中，她行驶的距离为 $d_{i}$，车速表在整个段落中显示的速度为 $s_{i}$。整个旅程花费的时间为 $t$。请帮助 Sheila 计算 $c$。

注意，虽然 Sheila 的车速表可能显示负数，但她的真实速度在旅程的每一段中都是大于零的。

## 说明/提示

时间限制：1 秒，内存限制：512 MB。

spj 提供者：@[shenyouran](/user/137367)。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 5
4 -1
4 0
10 3
```

### 输出

```
3.000000000
```

## 样例 #2

### 输入

```
4 10
5 3
2 2
3 6
3 1
```

### 输出

```
-0.508653377
```

# 题解

## 作者：一只小咕咕 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P6933)

这道题我用的是**二分答案**，只不过这道题和一般的二分答案有些不同，是**浮点数**的二分答案。那自然和整数的二分答案有些不同，下面我会说到。我们先来看一下思路解法。

## 思路解法

首先确定了是二分答案，我们需要先确定初始的 $l$ 和 $r$ 和 check 函数。

check 函数好写，我们可以根据 

$$t_i = \frac{d_i}{s_i+c}$$ 

这个公式来求出每段路程的时间。最后将总和与 $t$ 比较，判断当前二分到的 $c$ 的大小。

那如何判断 $c$ 是大还是小呢，我们回到上面那个公式，如果 $t_i$ 的总和比 $t$ 要大，说明 $c$ 小了，那应该去右半区间中找 $c$。

接下来我们来确定初始的 $l$ 和 $r$。我们再回到上面的公式中，可以看出 $s_i+c > 0$，那么所以 $c > -s_i$ 所以 $l$ 应取 $s_i$ 最小值的相反数。

通过数据范围可以看出 $t_i$ 的最大值为 $10^6$，$s_i$ 的最小值为 $10^3$，所以 $c$ 的最大值为 $10^6 - 10^3$。大家可以尝试根据上面的公式推一下，不过 $r$ 的最大值可以取得大一些，无非就是多循环几次，影响不大。

不过此题还是有几个点需要注意的：

首先就是浮点数的二分答案和整数的二分答案的区别。因为题目中说明了输出与正确答案的差应在 $10^6$ 以内，所以循环的判断条件应为 `while((r-l)>=1e-7)`。

同时浮点数是不能使用位运算的，所以应为 `mid=(l+r)/2`。

第二个需要注意的地方是翻译有点问题，题目中的单位均为英里和英里每小时，所以是不需要单位转换的。

最后一个也是最坑的地方，除了 $n$ 输入为整数，其他的输入时均为**实数**，所以应该使用 `double` 而非 `int`。

## 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;
double t,d[1005],s[1005],l=1e9,r=2e6;
bool check(double c){
	double ans=0;
	for(int i=1;i<=n;i++){
		ans+=(d[i])/(s[i]+c);
	}
	return ans>=t;
}
int main(){
	scanf("%d%lf",&n,&t);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&d[i],&s[i]);
		l=min(s[i],l);
	}
	l=-l;
	while((r-l)>=1e-7){
		double mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%.7f",l);
	return 0;
}

```

qwq，这是我的第一篇题解，求过。

---

## 作者：Genshin_ZFYX (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P6933)

这道题我第一眼看上去毫无思路，实际上就是 ~~一道第一眼看上去毫无思路的题~~ 稍微有些难的二分答案（个人认为评黄最好）。

## 解题思路

我们首先要确定二分答案最重要的三部分：

check 函数、$l$、$r$

check 函数：我们求出每段路程所需的时间，加起来后与 $t$ 进行比较。如果总和小了小了，则说明 $c$ 也小了。

时间计算公式：

$t_i=\displaystyle \frac{d_i}{s_i+c}$

$l$：我们根据 @CodeZhangBorui 提供的题面翻译（感谢感谢）就会知道我们的实际速度不为负数，所以我们的 $c$ 最小是 $s_i$ 的最小值的相反数。

$r$ 的值我们可以取大一点，取小了会 WA。

其他不懂的看代码吧：
```
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define I return
#define love 0
#define FIRESTARS ;
int n;
double t,d[1005],s[1005]; //注意！这个地方要用 double 定义！被坑了好久呜呜呜 
bool check(double c)
{
	double sum=0;
	for(int i=1;i<=n;i++)
		sum+=d[i]/(s[i]+c);
	if(sum>=t)return true;
	else return false;
}
double find(double l,double r)
{
	double mid;
	while(l+0.0000001<=r)
	//这里 l 是我们正确答案的最大值，r 是我们错误答案的最小值 
	//因为题目说答案与正确答案相差不能大于 0.0000001(10^-6)
	//所以 l 和 r 的差距应当不大于 0.0000001
	{
		mid=l+(r-l)/2.0; //这样写不会出界
		if(check(mid))l=mid;
		else r=mid;
	}
	return l;
}
signed main()
{
	cin>>n>>t;
	double l=1e9; //l 记得开大点 
	for(int i=1;i<=n;i++)
	{
		cin>>d[i]>>s[i];
		l=min(s[i],l);
	}
	l=-l;
	double ans=find(l,1e7);//r 开 1000000 是不够的！有个数据点的答案是 1001000
	printf("%.7f",ans); 
	I love FIRESTARS //我爱火星!
}
```

THE END

---

## 作者：__zyq_666_kpzc__ (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/P6933)
### 思路分析
根据题意，我们可以知道：比正确答案 $c$ 大的数一定能在规定时间内走完，比正确答案 $c$ 小的数不可能在规定时间内走完，答案 $c$ 具有单调性。

于是，我们可以想到用二分答案解决此题，二分最后的答案 $c$，在合法的范围中求出最小的答案，直接输出。

注意：最后的答案是浮点数！！！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
const double h=1e-7;
double t,ju_li[1005],su_du[1005],l=10000000,r=10000000;;
bool check(double x){
	double sum=0;
	for(int i=1;i<=n;i++)sum+=ju_li[i]*1.0/(su_du[i]+x);
	return sum>t;
}
signed main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>ju_li[i]>>su_du[i];
		l=min(l,su_du[i]);
	}
	l=-l;
	while(l+h<r){
		double mid=(l+r)/2;
		if(check(mid)==true)l=mid;
		else r=mid; 
	}
	printf("%.7lf",r);
	return 0;
}
```

---

## 作者：Flaw_Owl (赞：2)

# P6933 [ICPC2017 WF] Need for Speed 题解

原题链接：[[ICPC2017 WF] Need for Speed](https://www.luogu.com.cn/problem/P6933)

## 题目分析

根据题意简单模拟一下，我们发现这是一个**解方程**的题，以第一个样例为例，这实际上是解这样的一个方程：

$$\frac{4}{-1+x} + \frac{4}{0+x} + \frac{10}{3+x} = 5$$

答案即为 $x$ 的小数表示。

> 注：题目的中文翻译有误导，给出的 $d$ 应当被理解为千米而不是米，**无需进行单位换算**。

对于一个解方程的题，实际上中学阶段就有介绍过用**二分法**无限逼近来求解的方式，对于编程来说当然是一种不错的解法。这道题的正解即为**实数二分**。

与大家所熟悉的**整数二分**相比，由于没有了取整的问题，编码上要更为简单。可以被概括为：

```cpp
const double eps; // 表示精度。如果下面是 for 的写法，可以不用 eps
while(R - L > eps)
{
    double mid = L + (R-L) / 2;
    if (check(mid))
        R = mid;
    else
        L = mid;
}
```

其中，`while(R - L > eps)` 的写法也可以被替换成 `for(int i = 0; i < 100; i++)`，其中 $100$ 次循环即相当于精度为 $\dfrac{1}{2^{100}} \approx \dfrac{1}{10^{30}}$。控制循环次数也可以达到控制精度的目的。由于**本题已经给出了要求的精度**，建议以前一种写法编程。

对于一道**二分**的题，我们要关注三个点：初始的二分左右区间和 `check()` 函数的设计。

对于 `L`，即左端点，题目有一个隐性的条件：实际速度 $s + c$ 必定是一个非负数，即 $c \geq -s$。可以在输入的时候取读入的 $s$ 的最小值再取相反数。

对于 `R`，即右端点，我们可以写出 $c$ 的最大情况是 $\dfrac{n_{max}d_{max}}{s_{min}+c_{max}}=t_{min}$，套入数据可以解得 $c_{max} = 10^{6}$。

对于 `check()` 函数，根据题目直接进行模拟即可。即：

$$\sum_{i=1}^n \dfrac{d_i}{s_i + c} = t$$

## 参考代码

需要注意设置的数据类型。因为是实数二分，所以很多变量需要设置成 `double` 类型。另外，建议最后的**输出精度稍微调高一些**。

```cpp
#include <iostream>
#include <cctype>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 1005;
const double eps = 1e-6;

int n, t;
int d[maxN], s[maxN];
int minS = 1005;
double L, R;
double ans;

bool check(double mid)
{
    double res = 0;
    for (int i = 1; i <= n; i++)
        res = res + d[i] / (s[i] + mid);
    return res < t;
}

int main()
{
    n = read();
    t = read();
    for (int i = 1; i <= n; i++)
    {
        d[i] = read();
        s[i] = read();
        minS = min(minS, s[i]);
    }
    L = -minS, R = 2e6;
    while (R - L > eps)
    {
        double mid = L + (R - L) / 2;
        if (check(mid))
            R = mid;
        else
            L = mid;
    }
    printf("%.10lf\n", L);
    return 0;
}
```

---

## 作者：lyas145 (赞：1)

### 解题思路
首先我们一定能看出这道题得用二分，这样的话我们处理好上下边界剩下的就 easy 了。  
上边界（下文称为 $r$）就很好处理了，$r$ 直接取一个大点的数就行了。关键是下边界（下文称为 $l$），处理不好的话[就像我一样 WA 了](https://www.luogu.com.cn/record/159906660)。那咋处理呢？分情况来想：如果**存在负数**，因为速度不能为非正数，所以至少得保证速度都为正的，$l$ 取最小值的绝对值就行了；如果**不存在负数**，那么我们同样需要保证速度为正的，所以 $l$ 就是最小值的相反数。然后我们就可以惊奇地发现这不就是最小值的相反数吗？！这样求 $l$ 就简单多了。  
代码里也有些注释。
### 码儿
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1005,INF=1e8;
const double eps=1e-7;
int n,t;
double l,r;
double s[N],v[N];
bool check(double x) {        //check函数应该都能看懂
	double ti=0;
	for (int i=1;i<=n;i++) {
		ti+=s[i]/(v[i]+x);
	}
	return ti>=t;
}
int main() {
	scanf("%d%d",&n,&t);
	l=r=INF;
	for (int i=1;i<=n;i++) {
		scanf("%lf%lf",&s[i],&v[i]);
		l=min(l,v[i]);//求最小值
	}
	l=-l;                 //取相反数
	while (r-l>eps) {     //二分，启动！
		double mid=(l+r)/2;
		if (check(mid)) {l=mid;}
		else {r=mid;}
	}
	printf("%lf\n",l);
	return 0;
} 
```
本蒟第二次写题解，谢谢观看！

---

## 作者：YangXiaopei (赞：0)

## Solution

二分板子题。

二分 $c$ 的值，判断函数直接按题意模拟即可。

唯一需要注意的是二分左端点 $l$ 的初值。

我们知道速度一定大于等于 $0$，所以 $s_i + c \ge 0$，所以 $c \ge -s_i$，所以 $l$ 最小不能比所有 $s_i$ 的相反数极小值小。所以 $l$ 初值取 $s_i$ 极小值的相反数即可。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double t, l = 1e6, r = 1e9, d[1000005], s[1000005];
bool check(double c){
	double sum = 0;
	for(int i = 1; i <= n; i++){
		sum +=  d[i] / (s[i] + c);
	}
	return sum >= t;
}
int main(){
	cin >> n >> t;
	for(int i = 1; i <= n; i++){
		cin >> d[i] >> s[i];
		l = min(s[i], l);
	}
	l = -l;
	while(l + 1e-7 <= r){
		double c = (l + r) / 2;
		if(check(c)){
			l = c;
		}   
		else{
		    r = c;       		
		}
	}
	printf("%.6lf", l);
	return 0;
}
```

---

## 作者：Hanrui1206 (赞：0)

## 思路
这道题我用的是二分答案，只不过这道题和一般的二分答案有些不同，是**浮点数**的二分答案。

直接二分答案，二分的过程套模板，但是要注意要加上浮点数，接着的 $\operatorname{check}$ 函数就需要算出以正确的速度行驶完这 $n$ 段路程所需的时间。

注意题目要求精度是 $10^{-6}$ 以内，所以二分步长为 $10^{-7}$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double t, d[1005], s[1005], c;

bool check(double x) {
	double ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += d[i] / (s[i] + x);
	}
	if (ans > t) return true;
	return false;
}

int main() {
	cin >> n >> t;
	double l = 1e7, r = 1e7, mid;
	for (int i = 1; i <= n; i++) {
		cin >> d[i] >> s[i];
		l = min(l, s[i]);
	}
	l = -l;
	while (l + 0.0000001 < r) { 
		mid = (l + r) / 2.0;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.9lf", l);
	return 0;
}
```

---

## 作者：sunhaozhe111022 (赞：0)

**思路：**

直接二分答案，二分的过程套模板，但是要注意要加上浮点数，接着的 `check` 函数就需要算出以正确的速度行驶完这 $n$ 段路程所需的时间。

**代码实现：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double t,d[1005],s[1005],c;
bool check(double x)
{
	double ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=d[i]/(s[i]+x);//以(s[i]+x)的速度行驶完d[i]的路程所需要的总时间
	}
	if(ans>t) return true;//大于规定时间，c的值需要增加
	else return false;//否则减少
}
int main()
{
	cin>>n>>t;
	double l=1e7,r=1e7,mid;
	for(int i=1;i<=n;i++)
	{
		cin>>d[i]>>s[i];
		l=min(l,s[i]);
	}
	l=-l;
	while(l+0.0000000001<r)//二分答案（虽然夸张了一点
	{
		mid=(l+r)/2.0;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%.9lf",l);//保留9位小数
	return 0;
}

---

## 作者：xd244 (赞：0)

二分练习题一道。

其实就是一道带浮点数的二分，注意题目要求精度是 $10^{-6}$ 以内，所以可以在 $r-l\leq10^{-7}$ 时停止二分。

```cpp
#include<iostream>
#include<iomanip>
using namespace std;
double t,d[1005],s[1005];
int n;
bool P(double x){
	double sum=0;
	for(int c=1;c<=n;c++)sum+=(d[c])/(s[c]+x);
	return sum>=t;
}int main(){
    cin>>n>>t;
    double l=1e9,r=1e9;
    for(int c=1;c<=n;c++)cin>>d[c]>>s[c],l=min(s[c],l);
    l*=-1;
    while(r-l>=1e-7){
        double mid=(l+r)/2.0;
        if(P(mid))l=mid;
        else r=mid;
    }cout<<fixed<<setprecision(7)<<l;
}
```

---

## 作者：abc1856896 (赞：0)

# solution
考虑二分

左边界的值是明显的，因为 $s_i+c>0$，也就是说实际速度不为负数，那l取 $s_i$ 最小值的相反数。

右边界也是简单的，直接设大就行了。

判断函数根据 $t_i= \frac{d_i}{c+s_i}$ 来计算即可，最后用总和与 $t$ 比较即可。

# code
```cpp
#define dd double
#define inf 0.0000001

dd n, t ,d [1005] ,s [1005] , lb = INT_MAX , ub = 1e9;
bool check(dd x){
	dd check_s = 0;
	for(int i = 1; i <= n ; i++) {
		check_s = check_s + ( d[i] ) / ( s[i] + x );
	}
	return check_s >= t;
}
void check () {
	cin >> n >> t;
	for ( int i = 1 ; i <= n; i++ ) {
		cin >> d [i] >> s [i];
		lb = min ( s[i] , lb);
	}
	lb = - lb;
	while ( (lb + inf) <= ub ) { 
		dd mid = ( lb + ub ) / 2;
		if (check (mid)) lb = mid ;
		else ub = mid;
	}
	printf( "%.7f" , lb);
}
```

---

## 作者：lyh4 (赞：0)

## 题解：P6933 [ICPC2017 WF] Need for Speed
### [题目传送门](https://www.luogu.com.cn/problem/P6933)

### 思路：
这道题实际上就是对 $c$ 进行二分答案，而随着 $c$ 的增加，时间越来越大，存在单调性。而检查函数可利用时间、速度与路程计算公式得：$t_i = \frac{d_i}{s_i + c}$。还要注意 $c$ 的最小值（即左指针的初始化）应为 $s_i$ 的最小值的相反数。

### 但是：坑点——double！
这道题是实数域上的二分，因此要注意 double 的运用及精度误差！~~本人因此调了好久，太蒟了。~~

### 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
double t,d[1005],s[1005];
long long n;//注意 long long 与 double
bool check(double x)//检查函数
{
	double ret = 0;
	for(int i = 0; i < n;i++)
    {
		ret += (d[i])/(s[i]+x);//时间计算公式
	}
	return  ret >= t;
}
int main()
{
    cin >>n>>t;
    double l = 1e9,r = 1e9;//指针初始化
    for(long long i = 0; i < n; i++)
    {
        cin >>d[i]>>s[i];
        l = min(s[i],l);
    }
    l = -l;//注意要取反
    while((r-l) >= 1e-7)//注意！精度误差！
    {
        double mid = (l+r)/2.0;
        if(check(mid))l = mid;
        else r = mid;
    }//二分
    printf("%.7lf",l);//输出
    return 0;
}
```
AC 结束！

---

## 作者：JoeZYQ (赞：0)

### [先看题](https://www.luogu.com.cn/problem/P6933)
### 思路分析
纯纯二分答案模板题，只不过加上了浮点数这个坑。

考虑到答案 $c$ 有单调性，我们二分最终的答案 $c$，最大化 $c$ 的值。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
double t;
double d[1005],s[1005];
bool c(double x){
	double ti=0;
	for(int i=1;i<=n;i++)
		ti+=d[i]/double(s[i]+x);
	return ti>t;
}
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	double l=10000000;
	cin>>n>>t;
	for(int i=1;i<=n;i++)
		cin>>d[i]>>s[i],l=min(l,s[i]);
	l=-l;
	double r=10000000;
	while(l+0.0000001<r){
		double mid=(l+r)/2;
		if(c(mid))l=mid;
		else r=mid; 
	}
	printf("%.10lf",r);
	return 0;
}
```

---

## 作者：zhoujunchen (赞：0)

做题思路
---
一个二分答案题。

这道题目要求通过一些旅程的记录数据，计算一个数 $
c$，该数表示修正后的实际速度与速度表显示速度之间的偏差。

- 对于每一段路程 $i$，根据实际速度计算的时间为 
$$\frac{d_i}{s_i+c_i}$$

- 使用二分查找来寻找满足条件的 $c$ 值。

code:
```c++
#include<bits/stdc++.h>
using namespace std;
#define eps 1e-8
double d[1005],s[1005],t,minn=1e18;
int n,i;
int main(){
	cin>>n>>t;
	for(i=1;i<=n;i++){
		cin>>d[i]>>s[i];
		if(s[i]<minn)minn=s[i];
	}
	double l=-minn,r=1e18;
	while (r-l>eps){
		double mid=(l+r)/2.00;
		double tt=0;
		for(i=1;i<=n;i++)tt+=d[i]/(s[i]+mid);
		if(tt>t)l=mid;
		else r=mid;
	}
	printf("%.9lf\n",l);
	return 0;
}
```

---

