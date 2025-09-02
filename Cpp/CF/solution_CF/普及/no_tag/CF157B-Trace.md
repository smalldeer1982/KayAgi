# Trace

## 题目描述

一天，夏洛克·福尔摩斯正在跟踪一个重要罪犯时，他在墙上发现了一张美妙的画。这个墙可以被表示成一个平面，墙上有许多同心圆，将平面分成了若干块。除此之外，相邻的两个部分被交错填上了红色和蓝色。其中在所有圆外的部分被填了蓝色。夏洛克想知道红色部分的面积是多少。

## 样例 #1

### 输入

```
1
1
```

### 输出

```
3.1415926536
```

## 样例 #2

### 输入

```
3
1 4 2
```

### 输出

```
40.8407044967
```

# 题解

## 作者：LegendaryGrandmaster (赞：3)

## 题目大意

在一个平面上给定 $n$ 个同心圆。

这些同心圆构成的图形是蓝红相间的，其中**最外面**的圆是**蓝色**。

请问，这 $n$ 个同心圆构成的图形中，蓝色部分的总面积是多少？

### 输入格式
第一行包含整数 $n$。

第二行包含 $n$ 个整数， $r_1,r_2,…,r_n$ ，表示各个圆的**半径**。

### 输出格式

输出**蓝色部分**的总面积。

误差不超过 $10^{-4}$

### 数据范围

$ 1 ≤ n ≤ 100 $

$ 1 ≤ ri ≤ 1000 $

所有圆的半径**两两不同**。

-----------------

## 解题思路

首先，你需要有**足够的智商**（或者**神圣的百度**），把圆周率给**算出来**，这样精度就会**越来越接近**，也就更**容易对**。

```cpp
P=3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105118548074462379962749567351885752724891227938183011949129833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132000568127145263560827785771342757789609173637178721468440901224953430146549585371050792279689258923542019956112129021960864034418159813629774771309960518707211349999998372978049951059731732816096318595024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303598253490428755468731159562863882353787593751957781857780532171226806613001927876611195909216420198938095257201065485863278865936153381827968230301952035301852968995773622599413891249721775283479131515574857242454150695950829533116861727855889075098381754637464939319255060400927701671139009848824012858361603563707660104710181942955596198946767837449448255379774726847104047534646208046684259069491293313677028989152104752162056966024058038150193511253382430035587640247496473263914199272604269922796782354781636009341721641219924586315030286182974555706749838505494588586926995690927210797509302955;
```
我们一开始输入的**半径**，它的无序的，如果我们直接算的话，就**乱套了**，因此我们之前先排个序。

**由小到大**排序，我们 for 循环反着来算；如果是**由大到小**排序，我们 for 循环就正着来算。

众所周知，计算**圆的面积**公式是： $πr^2$

因为题目说了，蓝的是在**外面**，我们可以一蓝一红**两两组合**，大的减小的后就可以得出**圆环的面积**，以此类推，直到结束：

```cpp
for(int i=n;i>=1;i-=2)
    c+=a[i]*a[i]*P-a[i-1]*a[i-1]*P;
```

-----------------

因为误差不超过 $10^{-4}$ ，保留**4位小数**即可

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
double a[101],c=0;
double P=3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105118548074462379962749567351885752724891227938183011949129833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132000568127145263560827785771342757789609173637178721468440901224953430146549585371050792279689258923542019956112129021960864034418159813629774771309960518707211349999998372978049951059731732816096318595024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303598253490428755468731159562863882353787593751957781857780532171226806613001927876611195909216420198938095257201065485863278865936153381827968230301952035301852968995773622599413891249721775283479131515574857242454150695950829533116861727855889075098381754637464939319255060400927701671139009848824012858361603563707660104710181942955596198946767837449448255379774726847104047534646208046684259069491293313677028989152104752162056966024058038150193511253382430035587640247496473263914199272604269922796782354781636009341721641219924586315030286182974555706749838505494588586926995690927210797509302955;
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=n;i>=1;i-=2){
    	c+=a[i]*a[i]*P-a[i-1]*a[i-1]*P;
    }
    cout<<fixed<<setprecision(4)<<c;
}
```

--------------------
上一次审核：

原因是 普通英文内容（一般英文单词、题目名、算法名、人名等）不应该使用 LaTeX 公式；「公式/英文/数字」与「汉字」之间应当加空格；


这一次已经改正，求管理员大佬通过QwQ

---

## 作者：ljk654321 (赞：2)

虽然我也不知道为什么会被评成黄题（这题顶多橙题难度），因为就连我这样的蒟蒻都能几分钟切掉它...

总有一种恶意评级的感觉来着...

大意：

一个墙可以被表示成一个平面，墙上有许多同心圆，将平面分成了若干块。除此之外，相邻的两个部分被交错填上了红色和蓝色。其中在所有圆外的部分被填了蓝色。夏洛克想知道红色部分的面积是多少。

题目分析:

这道题是道很明显的求同心圆的面积的题目。

* 减去蓝色的面积后剩下的就是所求面积

由于输入的时候半径没有从大到小排好序，所以我们要先排个序，然后按直径从大到小计算每个圆的大小，假如红色的就让总和加上面积，否则就减。这样最终就只剩下红色了的面积了。

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(int x,int y)
{
	return x<y;
}
long long n,s[101];
double pi=3.1415926535897932385,sum=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	sort(s+1,s+n+1,cmp);
	for(int i=n;i>=1;i-=2)
	{
		sum+=s[i]*s[i]*pi-s[i-1]*s[i-1]*pi;
	}
	cout<<fixed<<setprecision(10)<<sum;
	return 0;
}
```




---

## 作者：codeLJH114514 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF157B)

# 题目大意

给你 $n$ 个同心圆的半径，最外层的圆的颜色是红色的，背景是蓝色的，由外向内依次是 红蓝红蓝红蓝 $\cdots\cdots$，要你计算所有颜色为红色的面积之和。

![图片](https://cdn.luogu.com.cn/upload/image_hosting/8o3cqywz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

# 解题思路

(其实这题我觉得用递归好像更容易理解，不喜勿喷。)

这里，我们定义了 $\pi = \operatorname{acos}(-1)$，理论上比手打很多位好很多。
(前提是`#include <cmath>`)

我还定义了一个类，叫 $\text{circle}$，用来表示一个圆。

输入没什么好说的，直接循环输入半径，然后排序。

输出全局变量 `ans` 即可。

$Code$ (未完整)

```cpp
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#define maxn 128
#define pi acos(-1)
using namespace std;
class circle{
    public:
        int radius;
        circle(): radius(0){};
        double GetArea();
        bool operator<(circle);
};
circle arr[maxn];
int n;
double ans;
void GetAreas(int, bool);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].radius;
    }
    sort(arr + 1, arr + n + 1);
    GetAreas(n, false);
    cout << fixed << setprecision(20) << ans; // 保留20位小数输出ans
    return 0;
}
double circle::GetArea() {
    return pi * radius * radius;
}
bool circle::operator<(circle other) {
    return radius < other.radius;
}
```

接下来就是函数 $\text{GetAreas}$ 的实现了：

（判断当前圆是否是红色的，如果是则将该圆的面积减去内层圆的面积的差加入 $\text{ans}$）

```cpp 
void GetAreas(int x, bool IsBlue) { // x 为现在是第几个圆，IsBlue 表示当前圆是否是蓝色的
    if (x == 1) { // 边界条件
        if (not IsBlue)
            ans += arr[x].GetArea();
        return;
    }
    if (not IsBlue)
        ans += arr[x].GetArea() - arr[x - 1].GetArea();
    GetAreas(x - 1, not IsBlue); // 递归
}
```

接下来上完整 $\text{Code}$:

```cpp
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#define maxn 128
#define pi acos(-1)
using namespace std;
class circle{
    public:
        int radius;
        circle(): radius(0){};
        circle(int r): radius(r){};
        double GetArea();
        bool operator<(circle);
};
circle arr[maxn];
int n;
double ans;
void GetAreas(int, bool);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].radius;
    }
    sort(arr + 1, arr + n + 1);
    GetAreas(n, false);
    cout << fixed << setprecision(20) << ans; // 保留20位小数输出ans
    return 0;
}
double circle::GetArea() {
    return pi * radius * radius;
}
bool circle::operator<(circle other) {
    return radius < other.radius;
}
void GetAreas(int x, bool IsBlue) { // x 为现在是第几个圆，IsBlue 表示当前圆是否是蓝色的
    if (x == 1) { // 边界条件
        if (not IsBlue)
            ans += arr[x].GetArea();
        return;
    }
    if (not IsBlue)
        ans += arr[x].GetArea() - arr[x - 1].GetArea();
    GetAreas(x - 1, not IsBlue); // 递归
}
```

无注释版:

```cpp
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#define maxn 128
#define pi acos(-1)
using namespace std;
class circle{
    public:
        int radius;
        circle(): radius(0){};
        circle(int r): radius(r){};
        double GetArea();
        bool operator<(circle);
};
circle arr[maxn];
int n;
double ans;
void GetAreas(int, bool);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].radius;
    }
    sort(arr + 1, arr + n + 1);
    GetAreas(n, false);
    cout << fixed << setprecision(20) << ans;
    return 0;
}
double circle::GetArea() {
    return pi * radius * radius;
}
bool circle::operator<(circle other) {
    return radius < other.radius;
}
void GetAreas(int x, bool IsBlue) {
    if (x == 1) {
        if (not IsBlue)
            ans += arr[x].GetArea();
        return;
    }
    if (not IsBlue)
        ans += arr[x].GetArea() - arr[x - 1].GetArea();
    GetAreas(x - 1, not IsBlue);
}
```

管理大大辛苦啦!

---

## 作者：MattL (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF157B) &[原题链接](http://codeforces.com/problemset/problem/157/B)

~~这能黄题？~~

这篇题解是综合各题解写出来的。

---

**题意**

>一天，夏洛克·福尔摩斯正在跟踪一个重要罪犯时，他在墙上发现了一张美妙的画。这个墙可以被表示成一个平面，墙上有许多同心圆，将平面分成了若干块。除此之外，相邻的两个部分被交错填上了红色和蓝色。其中在所有圆外的部分被填了蓝色。夏洛克想知道红色部分的面积是多少。 

我们的理解：

>有 $n$ 个同心圆，由于覆盖，形成 $n$ 个圆环。相邻的两个圆环被交错填上了红色和蓝色，其中在所有圆外的部分被填了蓝色。给出他们的半径，求红环的面积。

---

**思考**

我们小学就学过的圆环公式：

$$S=\pi (R^2-r^2)$$

其中 $R$ 为大圆的半径，$r$ 为小圆的半径 。

然后 $\pi$ 我们可以最后再乘，所以可以把 $R^2-r^2$ 部分存起来。

当 $n$ 为偶数时，答案为：

$$-r_1^2+r_2^2-r_3^2+\cdots+r_n^2$$

当 $n$ 为奇数时，答案为：

$$r_1^2-r_2^2+r_3^2+\cdots+r_n^2$$

或者换一个更简洁的表达，设 $t_i$ 为前 $i$ 个圆环的答案。则最终答案就是 $t_n$。（参考某题解）

转移方程为：

$$t_i=r_i^2-t_{i-1}$$

---

**注意**

1. @Azazel 不理解的，这里解答一下。由于最外面一定是红环所以 $n$ 为偶数时不需减 $1$。
2. 根据题目要求，$\pi=3.1415926536$。
3. 记住保留三位小数（`.10lf` 与 `setprecision(10)` 均可（后者记得`fixed`））
4. 要排序，数据不保证有序，不然会出错。

---

**代码**

以下不同写法的都在注释里。

```cpp
#include <bits/stdc++.h>
using namespace std;
double Pi=3.1415926536;
int n,a[110],ans;
//int t[110];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=n;i>=1;i-=2)
        ans+=a[i]*a[i]-a[i-1]*a[i-1];
//  for(int i=1;i<=n;++i)
//	t[i]=a[i]*a[i]-t[i-1];
    cout<<setprecision(10)<<fixed<<ans*Pi<<endl;
//  printf("%.10lf\n",ans*Pi);
    return 0;
}
```

---

## 作者：Azazеl (赞：1)

就这么一道题竟然卡了我半个小时，是我自己的问题吗？  
题意也很简单：$n$个同心圆，从内到外依次是红、蓝、红、蓝······最外层圆的外面是蓝色的，大概长这样：![无标题.png](https://i.loli.net/2019/08/07/avg6L3oxcQOh1Gj.png)
~~（忽略这个奇丑无比的画功）~~  
所以呢？所以我们只需要对于每一个奇数层进行加法，加入每一个奇数层的面积。  
鉴于两个同心圆面积公式为$\pi*(R^2-r^2)$，我们只需要将$(R^2-r^2)$的部分存起来即可。  
~~喜闻乐见的~~代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const double PI=3.1415926535898;
int r[10005];
int main(){
	int n;
	double ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&r[i]);
	sort(r+1,r+1+n);
	//if(n%2==0) n--;
	for(int i=n;i>=1;i-=2) ans+=r[i]*r[i]-r[i-1]*r[i-1];
	printf("%.10lf\n",double(ans*PI));
	return 0;
}

```
但是作者到现在还有一个问题：
>//if(n%2==0) n--;  

作者本来是觉得如果最外面是蓝色区域（$n$是偶数）那么就$-1$,从红色最大层开始，但不知道为什么加上这一句就会$WA$，聪明的你告诉我，这是为什么呢？  

好了，蒟蒻先溜了，知道的小伙伴在评论区留言哦。

---

## 作者：VitrelosTia (赞：0)

其实是一道很简单的模拟题啊，不过我写的和题解区不是很一样呢。

由于输入的时候半径没有从大到小排好序，所以我们要先排个序，然后考虑一个非常暴力的方法，就是按直径从大到小计算每个圆的大小，假如红色的就让总和加上面积，否则就减。这样最终就只剩下红色了。

```
const int N = 105;
const double pi = acos((double) - 1);//圆周率
int n, r[N];

void solve() {
	read(n);
	rep(i, 1, n) read(r[i]);
	sort(r + 1, r + n + 1, greater<int>());//从大到小排序
	double ans = 0.0;
	rep(i, 1, n) {
		if (i & 1) {
			ans += (r[i] * r[i]) * pi;//红色
		} else {
			ans -= (r[i] * r[i]) * pi;//蓝色
		}
	}
	cout << fixed << setprecision(10) << ans << '\n';
}
```

---

## 作者：FiraCode (赞：0)

[【原题链接】](luogu.com.cn/problem/CF157B)
## 解题思路：
先按递减的顺序排序，然后依次枚举每个半径，因为他是一红一蓝一红一蓝......

所以每次枚举时 $i$ 要每次 $+2$。

求圆的面积需要知道 $π$,这里设 $PI = \operatorname{acos(-1)}$($\operatorname{acos()}$ 是反余弦函数，$\operatorname{acos(π)} = -1$，所以 $π = $ $\operatorname{acos(-1)}$)。

圆的面积计算方法：
![](https://cdn.luogu.com.cn/upload/image_hosting/7bxszy67.png)
[【AC记录】](https://www.luogu.com.cn/record/67158479)
## AC Code:
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const double PI = acos(-1);
const int N = 110;
int n;
int r[N];
int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> r[i];
    sort (r , r + n , greater<int>());//排序，按递减的顺序排 
    double res = 0;
    for (int i = 0; i < n; i += 2)//因为红色的中间隔着一个蓝色的，所以每次i+=2 
        res += PI * (r[i] * r[i] - r[i + 1] * r[i + 1]);//计算他的面积，用他本身的面积减去他包含的面积 
    printf ("%.6lf" , res);//输出保留6为小数 
    return 0;
}
```

---

## 作者：zhangyuhao9 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF157B)

题目大意
---
这个题目翻译写得比较清楚了。

第一行输入 $n$ 表示墙上有 $n$ 个同心圆，第二行输入 $n$ 个数分别表示这 $n$ 个圆的半径这些圆把墙分成了许多部分。现在将这些为部分涂上红和蓝两种颜色。要求不在这些圆内的墙的其它部分全部涂成蓝色，求红色部分的面积。

题目分析
---
这道题是道很明显的求同心圆的面积的题目。

很明显最外一圈的圆是红的。

则推出求同心圆面积的公式是最大那个圆的半径的平方减去第二圈的半径的平方，再加上第三圈的圆的半径的平方 $……$ 以此类推，到最里圈时停止，然后乘上圆周率。

题目给的圆周率是 $10$ 位所以取 $10$ 位即可。

~~剩下的看代码和注释吧。~~

CODE
---
```cpp
#include<bits/stdc++.h>
using namespace std;
double r[101],t[101]; //r表示半径
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;++i){
	cin>>r[i];//输入各个圆的半径
    }
    sort(r+1,r+1+n);   //排序  
    for(int i=1;i<=n;++i){
	    t[i]=r[i]*r[i]-t[i-1];
	}
	printf("%.10lf",3.1415926536*t[n]);//如题目，取10位
	return 0;
}
```
管理员求过。

---

## 作者：Fat_Fish (赞：0)

这道题就是求多层同心圆面积

同心圆的面积公式大家都知道，在此不再赘述

那么我们只需求出每一层的半径平方的差，再乘以圆周率即可

$Code$
```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const int maxn=101;
double r[maxn],t[maxn];
const double p=3.1415926536;//根据题目定义十位
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>r[i];
	}
	sort(r+1,r+1+n);//排序，数据可能无序
	for(int i=1;i<=n;++i){
		t[i]=r[i]*r[i]-t[i-1];//大圆半径平方减小圆半径平方
	}
	printf("%.10lf",p*t[n]);//输出十位即可
	return 0;
}
```


---

## 作者：Trimsteanima (赞：0)

就讲下题意吧。。。
具体还是很好写的吧QWQ
一个平面上有很多同心圆，将平面分成若干块。相邻两部分交错填上了红蓝两色。所有圆外部分填蓝色。求红色部分的面积是多少。
```cpp
#include <bits/stdc++.h>
#define PI 3.141592653589793
using namespace std;
int t, a[102], val;
int main() {
	scanf("%d", &t);
	for (int i = 0; i < t; ++i) scanf("%d", &a[i]);
	sort(a, a + t);
	for (int i = t - 1; i >= 0; i -= 2) 
		val = val + (i - 1 >= 0 ? ((a[i] * a[i]) - (a[i - 1] * a[i - 1])) : a[i] * a[i]);
	printf("%.10lf\n", (double)PI * val);
	return 0;
}
```

---

