# Routine Problem

## 题目描述

Manao has a monitor. The screen of the monitor has horizontal to vertical length ratio $ a $ : $ b $ . Now he is going to watch a movie. The movie's frame has horizontal to vertical length ratio $ c $ : $ d $ . Manao adjusts the view in such a way that the movie preserves the original frame ratio, but also occupies as much space on the screen as possible and fits within it completely. Thus, he may have to zoom the movie in or out, but Manao will always change the frame proportionally in both dimensions.

Calculate the ratio of empty screen (the part of the screen not occupied by the movie) to the total screen size. Print the answer as an irreducible fraction $ p/q $ .

## 说明/提示

Sample 1. Manao's monitor has a square screen. The movie has 3:2 horizontal to vertical length ratio. Obviously, the movie occupies most of the screen if the width of the picture coincides with the width of the screen. In this case, only 2/3 of the monitor will project the movie in the horizontal dimension: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337B/429cc762b90fac9b9969eeb0bd54bb3278635967.png)

Sample 2. This time the monitor's width is 4/3 times larger than its height and the movie's frame is square. In this case, the picture must take up the whole monitor in the vertical dimension and only 3/4 in the horizontal dimension: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337B/9da098e1ff076f33756d107ad7616fb9b6b441f1.png)

## 样例 #1

### 输入

```
1 1 3 2
```

### 输出

```
1/3
```

## 样例 #2

### 输入

```
4 3 2 2
```

### 输出

```
1/4
```

# 题解

## 作者：Vidoliga (赞：5)

# 题解

### 本题过水$,$仔细观察$,$不难发现$:$

设屏幕边分别为$:ax,bx$

设电影边分别为$:cy,dy$

第一种情况如下图$:$

![](https://cdn.luogu.com.cn/upload/image_hosting/wialfvbi.png)

不难发现$:$残留比屏幕$=(ax-cy):ax$

再由左边可得$:bx=dy,$也就是$:\tfrac{x}{y}=\tfrac{d}{b}$

再拆开$(ax-cy):ax$得$:1-\tfrac{cy}{ax},$再将$\tfrac{x}{y}=\tfrac{d}{b}$带入得$:\tfrac{ad-cb}{ad}$

第二种情况如下图$:$

![](https://cdn.luogu.com.cn/upload/image_hosting/xh31w8d2.png)

如上的方法相似$,$可得$:\tfrac{bc-ad}{bc}$

接下来比较再输出就好了$QwQ$

本蒟蒻代码$:$


```cpp
#include<cstdio>
#include<cmath>
#define LL long long
using namespace std;
inline LL gcd(int a,int b){
	if(a==0) return b;
	return gcd(b%a,a);
}
int main(){
	LL a,b,c,d;
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	double x=(double)(b*c-a*d)/(b*c),y=(double)(a*d-b*c)/(a*d);
	if(x>=y){
		int e=gcd((b*c-a*d),(b*c));
		printf("%lld/%lld\n",(b*c-a*d)/e,(b*c)/e);
	}
	else{
		int e=gcd((a*d-b*c),(a*d));
		printf("%lld/%lld\n",(a*d-b*c)/e,(a*d)/e);
	}
	return 0;
} 
```

完结撒花$QaQ$

---

## 作者：gi_A (赞：2)

我们按照题目，先画出一个矩形表示屏幕，再画一个表示电影：

![](https://cdn.luogu.com.cn/upload/image_hosting/anuniubd.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

将屏幕固定，然后发现，可以将电影进行等比缩放和移动来改变剩余部分的大小。

当它被移到在左上角且某一边与屏幕重合时剩余部分最小。

![](https://cdn.luogu.com.cn/upload/image_hosting/k3ycqkmx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

分别计算长重合与宽重合两种情况。

（当剩余部分不能为 $0$ 时，某一边重合会使得电影的总大小 $>$ 屏幕大小）。

参考代码：

```cpp
#include<iostream>
using namespace std;

int a,b,c,d,q1,q2,p1,p2;
int gcd(int a,int b){//求最大公约数 
	if(!b)return a;
	return gcd(b,a%b);
}
int main()
{
	cin>>a>>b>>c>>d;
	int a1=a,b1=b,c1=c,d1=d;
//将a、c统一后，剩余部分占总屏幕的 (d-b)/d 
	d*=a;b*=c;a*=c;c=a;
	p1=d-b;q1=d;
//将b、d统一后，剩余部分占总屏幕的 (c-a)/c 
	a1*=d1;c1*=b1;b1*=d1;d1=b1;
	p2=c1-a1;q2=c1;

	if(p1>0){//长重合不会使电影大于屏幕
    	d=gcd(p1,q1);//约分
        cout<<p1/d<<"/"<<q1/d;
   }
	else{d=gcd(p2,q2);cout<<p2/d<<"/"<<q2/d;}
	return 0;
}
```

---

## 作者：Yzmddsw (赞：1)

首先第一种情况，尝试改变长度使长相等。

也就是将 $a:b$ 乘 $c$ 得 $ac:bc$， $c:d$ 乘 $a$ 得 $ac:ad$。

如果 $bc < ad$，明显不合法，则用第二种情况，改变宽度。即变为 $ad:bd$ 和 $bc:bd$。

然后求剩下部分的面积比，长宽中间必有一个相等，只需求另一个即可，即第一种情况的 $(bc-ad):bc$ 和第二种情况的 $(ad-bc):ad$。

最后约分，直接各自除以最大公约数即可。

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int main(){
    ll a,b,c,d;
    cin>>a>>b>>c>>d;
    if(b*c >= a*d){
        cout<<(b*c-a*d)/__gcd(b*c-a*d,b*c)<<"/"<<b*c/__gcd(b*c-a*d,b*c);//第一种情况
    }
    else {
        cout<<(a*d-b*c)/__gcd(a*d-b*c,b*c)<<"/"<<a*d/__gcd(a*d-b*c,b*c);//第二种情况
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

### 这是萌新的第一篇题解，如果有错误，欢迎大家指出！


#### [题目传送门](https://www.luogu.com.cn/problem/CF337B)

#### 好了，话不多说，咱们开始正题。
**题目大意**:已经说得很清楚了。题目告诉我们：屏幕的长宽之比为  $a:b $ ，电影的长宽之比为  $c:d$ ，使空余部分占总面积的比最小。

我们先来分析题意：我们统一屏幕和电影的长和宽，即可让剩余面积最小。

我们分类讨论，先看长，当长一样时，就统一两个比例的前项，变成 $ ( a \times c ) : ( b \times c) $ 与 $ ( a \times c) : (a \times d) $ ;再看宽，当宽一样时，就统一两个比例的后项，变成 $ (a \times d) : ( b \times d ) $ 与  $(b \times c) : ( b \times d)$ 。所以面积之比就是  $ ( a \times d - b \times c) : ( a \times d) $ ，最后，我们再除以它们的**最大公因数**
,也就是**约分**一下，于是我们就能愉快地写代码了    o(*￣▽￣*)ブ。

在此我真诚献上 $ \color{green}\ AC $ 代码：

```cpp
#include<bits/stdc++.h>//头文件，不用多说 
using namespace std;//这个……不用我说了吧？ 
int a,b,c,d;//屏幕、电影的长宽之比 
int main (){
	cin>>a>>b>>c>>d;//输入长宽之比 
	//当长一样与当宽一样 
	if(b*c>=a*d){
		int Gcd=__gcd(b*c-a*d,b*c);//前项与后项的最大公因数（gcd） 
		cout<<(b*c-a*d)/Gcd<<'/'<<(b*c)/Gcd<<endl;//统一前项并约分。 
	} 
	else{
		int Gcd=__gcd(a*d-b*c,a*d);//前项与后项的最大公因数（gcd） 
		cout<<(a*d-b*c)/Gcd<<'/'<<(a*d)/Gcd<<endl;//统一后项并约分。 
	}
	return 0;//华丽の结束 
}
```


感谢各位大佬的阅读，希望对Oier们有帮助（希望管理员审核通过）！

---

## 作者：Green_Yeast_King (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF337B)

题意：
--------
已知屏幕的长宽之比 $a:b$ 以及电影的长宽之比 $c:d$，使屏幕空余部分占总面积的比最小。

思路:
---------
观察题目，不难发现：我们只需将两者长 $(a,c)$ 统一，或者宽 $(b,d)$ 统一，就可以让剩余面积最小。

1：当长一样时，将 $a:b$ 和 $c:d$ 的前项统一，变成 $(a \times c):(b \times c)$ 和 $(c \times a):(d \times a)$。

可知：

面积比为 $(b \times c - a \times d) \div (b \times c)$。

2：当宽一样时，将 $a:b$ 和 $c:d$ 的后项统一，变成 $(a \times d):(b \times d)$ 和 $(c \times b):(d \times b)$。

可知：

面积比为 $(a \times d - b \times c) \div (a \times d)$。

分类讨论，最后约分即可。

AC Code:
----------
```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, c, d;
int main () {
	cin >> a >> b >> c >> d;
	//当长一样
	if (b * c >= a * d) {
		int Gcd = __gcd (b * c - a * d, b * c);
		cout << (b * c - a * d) / Gcd << '/' << (b * c) / Gcd << '\n';
	} 
	//当宽一样
	else {
		int Gcd = __gcd (a * d - b * c, a * d);
		cout << (a * d - b * c) / Gcd << '/' << (a * d) / Gcd << '\n';
	}
	return 0;
}
```

---

## 作者：Berd__ (赞：0)

## 题目简意
给出屏幕比例以及一部电影的比例，让电影适配屏幕，保留正常画面，不能畸形画面，求屏幕上剩下没被电影覆盖部分的面积与屏幕总面积的比，输出化简后的比。
## 思路
如果要让影片占的位置最大，一种是让它的长与屏幕的长一样大，一种是让它的宽与屏幕的宽一样大，即影片的某一边完全与屏幕重合。

可以证明，两种情况至少有一种情况成立。

### 第一种情况：长相等

在长相等情况下，我们可以把屏幕的长宽比（$a:b$）和电影的长宽比（$c:d$）的前项统一，化为 $(ac):(bc),(ca):(da)$。

### 第二种情况：宽相等

在宽相等情况下，把屏幕的长宽比和电影的长宽比的后项统一，化为 $(ad):(bd),(cb):(db)$。

**$\large\texttt{所以,把两种都计算出来，再比较就行了。}\tiny\texttt{（别忘了，有时长宽统一之后，画面会超出屏幕，要特别计算哦！）}$**

---

## 作者：Frictional (赞：0)

这道题很水，我们可以分两种思路考虑。一种是电影与屏幕的宽相等，一种是长相等。

1. 长相等的时候，我们要先将 $a:b$ 和 $c:d$ 的前项统一，就可以换成 $(a\times c):(b\times c)$ 和 $(c\times a):(d\times a)$，如图。
![](https://cdn.luogu.com.cn/upload/image_hosting/7ztzkbsu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以空闲屏幕与整块屏幕的面积比就是 $(b\times c-d\times a)/(b\times c)$。

2. 宽相等的时候，我们要先将 $a:b$ 和 $c:d$ 的后项统一，就可以换成 $(a\times d):(b\times d)$ 和 $(c\times b):(d\times b)$，如图。
![](https://cdn.luogu.com.cn/upload/image_hosting/59wr2fej.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以这时空闲屏幕与整块屏幕的面积比就是 $(a\times d-c\times b)/(a\times d)$。

## AC code
```
#include<bits/stdc++.h>
#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define DEBUG(x) std::cerr<<#x<<'='<<x<<std::endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
using namespace std;
int a,b,c,d;
int at,bt,ct,dt;
int t1,t2;
signed main(){
	cin>>a>>b>>c>>d;
	at=a*c;
	bt=b*c;
	ct=c*a;
	dt=d*a;
	t1=bt-dt;
	t2=bt;
	if(t1>=0){
		cout<<t1/__gcd(t1,t2)<<"/"<<t2/__gcd(t1,t2);;
	}
	else{
		at=a*d;
		bt=b*d;
		ct=c*b;
		dt=d*b;
		t1=at-ct;
		t2=at;
		cout<<t1/__gcd(t1,t2)<<"/"<<t2/__gcd(t1,t2);
	}
	return 0;
}
```


---

## 作者：Mingci (赞：0)

# CF337B Routine Problem
## 题意概要
给出屏幕长宽比例以及屏幕上一部电影的长宽比例，尽可能的让电影适配屏幕，保留正常画面，不能畸形画面，求屏幕上剩下没被电影覆盖部分的面积与屏幕总面积的比，输出化简后的比。
## 题目分析
通过读题不难看出有两种情况，第一种是让电影的长适应屏幕的长，如下图。 
![](https://cdn.luogu.com.cn/upload/image_hosting/vaju856o.png)
这种情况空余面积与总面积的比是 $\frac{bc-ad}{bc}$。此时的 $c$ 是拓展过的。
第二种情况是让电影的宽去适应屏幕的宽，如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/nztjv158.png)
这种情况空余面积与总面积的比是    $\frac{ad-bc}{ad}$。此时的 $d$ 是拓展过的。
同时我们知道了这两种情况，题目要求我们最后输出的答案要化简，我们就要用到最小公因数去化简，有一个能够直接取最小公因数的函数，这在下面的代码片段中会展示，那接下来就是~~大伙喜闻乐见的~~代码部分了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
double x,y;//分别是长与宽拓展的比例
long long a,b,c,d;//看数据范围记得开long long
int main(){
    cin >> a >> b >> c >> d;//输入
    x = double(b*c-a*d)/(b*c);//这里是计算长与宽拓展的比例
    y = double(a*d-b*c)/(a*d);//以便我们判断应拓展长还是宽，即判断是哪种情况
    int gc1 = __gcd((b*c-a*d),(b*c));//使用__gcd函数取最大公因数
    int gc2 = __gcd((a*d-b*c),(a*d));//分别是两种情况的最大公因数
    if(x>=y)//属于拓展长的情况
	cout << (b*c-a*d)/gc1 << "/" << (b*c)/gc1;
    else//否则属于拓展宽的情况
	cout << (a*d-b*c)/gc2 << "/" << (a*d)/gc2;
        //除以最大公因数是化简，然后输出
    return 0;//圆满结束awa
}
```


---

## 作者：Jr_Zlw (赞：0)

### 一道很现实很形象的题目

看到题目就突然想起平时做ppt或什么其他文档的时候放照片的那些事QAQ。

那么题目很简单，给出屏幕的比和照片的比，求怎样让空余部分最小。

按照~~我们的常识~~，如果要让照片占的位置最大，就要让它的长或宽与屏幕的长或宽一样大，即照片的某一边完全与屏幕重合。那么这种情况我们只需要找到 $a,c$ 的最小公倍数或 $b,d$ 的最小公倍数并将另一边的比同乘上这个数就很好办了。至于是统一长还是统一宽，就要看看在统一某一边时另一边是否越过屏幕，如果越过就要排除。最后因为要求的是一个比，所以得出的两个数不一定要是精确值，所以直接输出最简分数即可。

（最简分数就是直接让两个数同时除以最大公约数即可）

***记得开 long long!!!***

### 双手奉上代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int a,b,c,d;cin>>a>>b>>c>>d;
	int r=__gcd(c,d);c=c/r;d=d/r;
	int c1=c*a,d1=d*a,c2=c*b,d2=d*b;
	int a1=a*c,b1=b*c,a2=a*d,b2=b*d;
    if(d1>b1)swap(c1,c2),swap(d1,d2),swap(a1,a2),swap(b1,b2);
    int q=a1*b1,p=a1*b1-c1*d1;r=__gcd(p,q);q/=r;p/=r;
    printf("%lld/%lld",p,q);return 0;
}
```


---

## 作者：　　　吾皇 (赞：0)

### 思路分析
```
看到这种比例关系，就不难想到要让电影的长或宽与屏幕的长或宽相同。那么第一步要做的就是怎么判断更改长还是宽。那么判断完之后由于长是相同的p/q就等于(b*c-a*d)/b*c，又因为p/q是最简分数，所以需要让p、q都除以它们的最大公因数
```
#### 判断
```
假设需要使长相同，那么现在屏幕的宽就是b*c，电影的宽就是a*d，易知b*c一定不小于a*d，所以如果(b*c<a*d)，只要交换屏幕的长宽和电影的长宽即可
```
### 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,p,q,x;
int main(){
	cin>>a>>b>>c>>d;
    //读入比例关系
	if(a*d>c*b) swap(a,b),swap(c,d);
    //如判断所说使b*c>=a*d，这样让长一样就不会使电影的宽大于屏幕的宽
	p=(b*c-a*d),q=b*c;
	x=__gcd(p,q),p/=x,q/=x;
    //x是p、q的最大公因数，所以让p、q分别除以x，p/q就是最简分数
	cout<<p<<"/"<<q;
    //按照要求输出
	return 0;
}
```


---

