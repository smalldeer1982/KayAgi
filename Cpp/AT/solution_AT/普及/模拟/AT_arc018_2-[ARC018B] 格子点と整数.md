# [ARC018B] 格子点と整数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc018/tasks/arc018_2

諸君、私は整数が好きだ。  
 私は格子点が好きだ。  
 私は面積が好きだ。  
 私は三角形が好きだ。  
 私は座標平面上の、頂点が全て格子点上にある、面積が整数の三角形が大好きだ。  
 格子点の集合をみたとき、その中の任意の $ 3 $ 点を選んで作ることができる面積が整数の三角形の個数を数えるときは心が踊る。  
 心が踊るが、格子点が多いと数えるのが面倒臭い。  
 ぜひ有能なプログラマーである諸君に私の代わりに数えてほしい。  
 $ N $ 個の格子点を与えるので、その中の任意の $ 3 $ 点を選んで作ることができる、面積が整数の三角形の個数を数えるプログラムを作って欲しい。面積が $ 0 $ の三角形は三角形とは認めん！  
 ちなみに、格子点というのは座標平面上の点 $ (x,y) $ のうち $ x $ も $ y $ も整数である点のことである。

入力は以下の形式で標準入力から与えられる。

> $ N $ $ x_1 $ $ y_1 $ $ x_2 $ $ y_2 $ : $ x_N $ $ y_N $

- $ 1 $ 行目には、格子点の個数を表す整数 $ N\ (3\ ≦\ N\ ≦\ 100) $ が与えられる。
- $ 2 $ 行目から $ N $ 行では、2つの整数が空白区切りで与えられる。 $ (x_i,\ y_i)　(1\ ≦\ x_i,\ y_i\ ≦\ 10^9) $ は $ i $ 番目の格子点の位置である。同じ格子点が二度与えられることはない。( $ i\ \neq\ j $ ならば $ (x_i,\ y_i)\ \neq\ (x_j,\ y_j) $ )
 
 $ N $ 個の格子点のうち $ 3 $ つを選んで作ることができる面積が正の整数である三角形の個数を一行で出力せよ。  
 なお、出力の最後には改行を入れること。 ```
<pre class="prettyprint linenums">
3
1 1
1 2
3 1
```

 ```
<pre class="prettyprint linenums">
1
```

 $ (1,1),\ (1,\ 2),\ (3,\ 1) $ の面積が $ 1 $ の三角形が一つだけ作れる。 ```
<pre class="prettyprint linenums">
3
1 1
1 2
2 1
```

 ```
<pre class="prettyprint linenums">
0
```

 三角形 $ (1,\ 1)\ (1,\ 2)\ (2,\ 1) $ の面積は $ 0.5 $ で整数ではない。これ以外に三角形は作ることができない。 ```
<pre class="prettyprint linenums">
3
1 1
2 2
3 3
```

 ```
<pre class="prettyprint linenums">
0
```

 $ 3 $ 点は一直線上に並ぶので、三角形を作ることができない。 ```
<pre class="prettyprint linenums">
8
3 1
4 1
5 9
2 6
5 3
5 8
9 7
9 3
```

 ```
<pre class="prettyprint linenums">
38
```

# 题解

## 作者：亦枫 (赞：4)

## Solution

题意：给你 $ n $ 个平面直角坐标系中的点，任意从其中选取 $ 3 $ 个点，要求用这三个点能构成一个面积是整数的三角形。
求符合条件的三角形个数。

我们看数据范围，因为 $ n<=100 $ 所以直接暴力枚举三个点即可。时间复杂度为 $ O(n^3) $ ,可以过。

首先，我们有三个点，先画一个矩形，四条边均平行于两条坐标轴，并且刚好将这个三角形囊括进去。

示意图：![](https://cdn.luogu.com.cn/upload/image_hosting/sujupabt.png)

那么我们怎么判断这三个点能不能构成三角形呢？

**先取两点求出经过这两点的直线的斜率，再将其中一个点换成剩下的一个点再求出经过这两点的直线的斜率。**

直线AB斜率为 $ \dfrac{y1-y2}{x1-x2} $

直线AC斜率为 $ \dfrac{y1-y3}{x1-x3} $

若这两条直线的斜率相等则有 $ \dfrac{y1-y2}{x1-x2}=\dfrac{y1-y3}{x1-x3} $。

化简后即为：
$ (y1-y2) * (x1-x3)=(y1-y3) * (x1-x2) $。

判断这个是否成立即可，若不成立则可以构成三角形。

然后，我们根据 $ A,B,C $ 三点的坐标计算出矩形其余三个顶点的坐标。

就像这样，就可以得出中间三角形的面积：![](https://cdn.luogu.com.cn/upload/image_hosting/7g3vc65g.png)

想要判断这个三角形的面积是否为整数，只用判断后面括号内的部分是否为 $ 2 $ 的倍数。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,ans;
struct p {
	ll x,y;
} a[105];
int main() {
	scanf("%lld",&n);
	for(int i=1; i<=n; i++) {
		scanf("%lld %lld",&a[i].x,&a[i].y);
	}
	for(int i=1; i<n-1; i++) {
		for(int j=i+1; j<n; j++) {
			for(int k=j+1; k<=n; k++) {
				if((a[i].x-a[k].x)*(a[i].y-a[j].y)==(a[i].x-a[j].x)*(a[i].y-a[k].y))continue;//判断能否构成三角形
				if(((a[j].x-a[k].x)*(a[k].y-a[j].y)+(a[i].x-a[j].x)*(a[i].y-a[j].y)+(a[i].x-a[k].x)*(a[i].y-a[k].y))%2==0)ans++;//判断构成三角形面积是否为整数
			}
		}
	}
	printf("%lld",ans);
}
```


---

## 作者：itisover (赞：2)

看数据范围 $n<=100$，直接枚举任意三个点，判断是否合法，合法就 ``++ans``，最后输出结束。时间复杂度 $O(n^3)$。~~（唯一坑点就是开longlong）~~

具体讲讲怎么判断

先画图：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/wry6ovep.png)

对于任意一个三个顶点都在在格点上的三角形，我们称他为格点三角形。那么对于任意一个格点三角形，都可以画出类似于这样的图。（图中字母看做大写，本人手残）其中：

$$S_{\triangle ABC}=S_\text{矩形AGCF}-(S_{\triangle ACF}-S_{\triangle ABD}-S_{\triangle BCE})-S_\text{矩形BDGE}$$

带坐标进去：

$$S_{\triangle ABC}=(x_c-x_a)\times(y_c-y_a)-\frac{1}{2}[(x_c-x_a)\times (y_c-y_a)+(x_b-x_a)\times (y_b-y_a)+(x_c-x_b)\times (y_c-y_b)]-(x_c-x_b)\times(y_b-y_a)$$

题目给出的坐标均为整数，所以判断面积是否为整数就只用看带有 $\frac{1}{2}$ 的部分，只要中括号里面的能被 $2$ 整除，那么这个三角形的面积就是整数。

那对于面积为 $0$ 的情况呢？其实就是特判一下三点共线的情况。我是算三角形三边中任意两边的斜率，如果相等那么就是三点共线。

算边 $AB$ 的斜率：

$$\frac{x_b-x_a}{y_b-y_a}$$

算边 $BC$ 的斜率：

$$\frac{x_c-x_b}{y_c-y_b}$$

当边 $AB$ 的斜率等于边 $BC$ 的斜率时，即：

$$\frac{x_b-x_a}{y_b-y_a}=\frac{x_c-x_b}{y_c-y_b}$$

交叉相乘，可得：

$$(x_b-x_a)\times(y_c-y_b)=(x_c-x_b)\times(y_b-y_a)$$

得出这个后就可以愉快的解决面积为 $0$ 的情况了！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,ans;
struct node{
  long long x,y;
}node[N];
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%lld%lld",&node[i].x,&node[i].y);
  for(int a=1;a<=n-2;a++){
    for(int b=a+1;b<=n-1;b++){
      for(int c=b+1;c<=n;c++){//_2Ssjx是那三个三角形面积和的两倍，tepan1、tepan2是算斜率
	long long _2Ssjx=abs(node[a].x-node[b].x)*abs(node[a].y-node[b].y)+abs(node[a].x-node[c].x)*abs(node[a].y-node[c].y)+abs(node[b].x-node[c].x)*abs(node[b].y-node[c].y);
	long long tepan1=((node[a].x-node[b].x)*(node[b].y-node[c].y));
	long long tepan2=((node[b].x-node[c].x)*(node[a].y-node[b].y));
	if(_2Ssjx&1) continue;
	if(tepan1==tepan2) continue;
	++ans;
      }
    }
  }
  printf("%d",ans);
  return 0;
}
```


---

## 作者：nanatsuhi (赞：2)

如你所见，这是一道实打实的红题。唯一的一个小问题就是：

如何在已知三点的情况下，算出三角形的面积？

说到三角形的面积计算，我的第一反应就是海伦公式，这道题应该可以使用。

但是事实上，海伦公式其一有精度误差，其二计算量比较大。

所以在这里，我们可以采用一种比较少见的方法。

---

首先，我们有三个点，然后记它们的横坐标与纵坐标形如$x_1,y_1$。

先画出一张示意图。（其实不止这一种情况，但剩下的也没什么差别）

![](https://cdn.luogu.com.cn/upload/image_hosting/scqnnsno.png)

然后显然可知左下角坐标为$(x_1,y_2)$。

接下来就是愉快的颓式子时间。

$$S_{\Delta }=(x_3-x_1)(y_3-y_2)-\frac{1}{2}(x_1-x_2)(y_2-y_1)-\frac{1}{2}(x_3-x_1)(y_3-y_1)-\frac{1}{2}(x_3-x_2)(y_3-y_2)$$

把这个式子因式分解，得到如下的结果：

$$S_{\Delta}=\frac{1}{2}[(x_3-x_2)(y_1-y_2)-(x_1-x_2)(y_3-y_2)]$$

这个式子就可以拿来做题了。因为题目只要求判断整数与否，所有的相反数都不重要，可以直接照抄完事。

简短的代码：
```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main()
{
    int N;
    cin >> N;
    vector<ll> x(N), y(N);
    for (int i = 0; i < N; i++)
        cin >> x[i] >> y[i];
    int c = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < i; j++)
            for (int k = 0; k < j; k++)
            {
                ll x1 = x[j] - x[i];
                ll x2 = x[k] - x[i];
                ll y1 = y[j] - y[i];
                ll y2 = y[k] - y[i];
                ll s = x1 * y2 - x2 * y1;
                if (s != 0 && s % 2 == 0)
                    c++;
            }
    cout << c << endl;
    return 0;
}
```

---

## 作者：Biden_Trump (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT812)

题意：
------------
找到面积为整数，且它在平面上的坐标为整数，面积也不能为 $ 0 $。

思路：
------------
在这道题中，运用到了小学学的整体减空白，即大的面积减去小的空白面积就是三角形的面积，我们根据这些求出三角形的面积再判断它的面积是否为 $ 0 $，且是整数即可。

代码：
------------
```
#include<bits/stdc++.h>
#define int long long

using namespace std;
int n,i,j,k,a[1000],b[1000],ans;

signed main()
{
	cin>>n;
	for(i = 1;i <= n;i ++)
	{
		cin>>a[i]>>b[i];
	}
	for(i = 1;i <= n;i ++)
	{
		for(j = i + 1;j <= n;j ++)
		{
			for(k = j + 1;k <= n;k ++)
			{
				int s=(a[k]-a[j])*(b[i]-b[j])-(a[i]-a[j])*(b[k]-b[j]);
				if(s!=0&&s%2==0)
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
~~最后说一句，其实我是小黑子。~~

---

## 作者：haotian1234 (赞：1)

水题一道，~~但是本人错了六次，额~~
## 题意暗示
就是让你找有几个面积为整数的三角形嘛，没什么好暗示的。

这个环节跳过。
## 题意分析
首先这道题有两种方法。

**海伦公式与斜率**

首先讲海伦公式，不知道海伦公式的，可以 [点击这里](https://baike.baidu.com/item/%E6%B5%B7%E4%BC%A6%E5%85%AC%E5%BC%8F/106956?fr=aladdin) ，要知道两个点的距离可以用勾股定理，勾股定理大家应该都会吧，还是不知道的，可以 [点击这里](https://baike.baidu.com/item/%E5%8B%BE%E8%82%A1%E5%AE%9A%E7%90%86/91499) ，最后就是如何判断这个数值是否是整数了，就用下面的方法：
```cpp
const double eps=1e-10;
double q=(int)(s+eps);
if(s-eps<=q&&q<=s+eps)			
{				
	ans++;			
}
```
其次，便是斜率，不知道斜率的，可以 [点击这里](https://baike.baidu.com/item/%E6%96%9C%E7%8E%87) ，当两条边斜率相同时，这个三角形面积便是整数。所以只要将斜率相加，判断这个数是否是2的倍数即可。
## 题目坑点
1. 要开 long long
1. 三角形面积不能是0！

其它没有了（~~呵呵，就这么少~~）

下面上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,i,j,k,a[1000],b[1000],ans;
int main(){
	scanf("%lld",&n);
	for (i=1;i<=n;i++) scanf("%lld%lld",&a[i],&b[i]);
	for (i=1;i<=n;i++)
		for (j=i+1;j<=n;j++)
			for (k=j+1;k<=n;k++){
				long long s=(a[k]-a[j])*(b[i]-b[j])-(a[i]-a[j])*(b[k]-b[j]);
				if (s!=0&&s%2==0) ans++;
			}
	printf("%lld\n",ans);
	return 0;
}
```
本人就写了斜率，海伦公式没写（~~因为写错了~~）

---

## 作者：Clever_Cjy (赞：1)

先来看看题目意思。

给出 $N$ 个格点。

从中任意选出 $3$ 个点作为三角形顶点。

格点即坐标平面上的点 $(x,y)$，其中 $x$ 和 $y$ 都是整数。

这道题我看了其他大佬的题解。

基本是用斜率做的。

像我这种蒟蒻连斜率都不会。

就只能用最暴力的方法做了。

先讲讲我的思路：三重循环+两点间距离公式+海伦公式。

三重循环这很简单，不用我说应该都会。

然后来讲讲两点间距离公式。

$S=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$

就上面这个公式，也很简单（初中课本上应该都有）。

具体代码：

```cpp
x=sqrt((a[i]-a[j])*(a[i]-a[j])+(b[i]-b[j])*(b[i]-b[j]));	
y=sqrt((a[j]-a[k])*(a[j]-a[k])+(b[j]-b[k])*(b[j]-b[k]));	
z=sqrt((a[i]-a[k])*(a[i]-a[k])+(b[i]-b[k])*(b[i]-b[k]));
```
然后就是海伦公式。

我觉得这个公式应该很多人知道（反正我第一个学的公式是这个）。

公式如下：

$p=\frac{a+b+c}{2}$

$S=\sqrt{p(p-a)(p-b)(p-c)}$

其中 $a$，$b$，$c$ 分别为三角形的三边。

具体代码：

```cpp
p=(x+y+z)/2.0;
s=sqrt(p*(p-x)*(p-y)*(p-z));
```
然后就是我觉得这题的难点：如何判断一个实数是否为整数。

这里我是用了 $eps$，不知道有没有人知道。

这个东西是可以来弄浮点数误差的。

我也不是太懂。

具体代码：

```cpp
const double eps=1e-10;
double q=(int)(s+eps);
if(s-eps<=q&&q<=s+eps)			
{				
	ans++;			
}
```

到此，本题基本做完。

我只给你们核心代码。

希望你们可以通过自己的思考。

将本题打出来。

---

## 作者：reclusive (赞：1)

先来看看题目意思。

给出 $N$ 个格点。

从中任意选出 $3$ 个点作为三角形顶点。

格点即坐标平面上的点 $(x,y)$，其中 $x$ 和 $y$ 都是整数。

这道题我看了其他大佬的题解。

基本是用斜率做的。

像我这种蒟蒻连斜率都不会。

就只能用最暴力的方法做了。

先讲讲我的思路：三重循环+两点间距离公式+海伦公式。

三重循环这很简单，不用我说应该都会。

然后来讲讲两点间距离公式。

$S=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$

就上面这个公式，也很简单（初中课本上应该都有）。

具体代码：

```cpp
x=sqrt((a[i]-a[j])*(a[i]-a[j])+(b[i]-b[j])*(b[i]-b[j]));	
y=sqrt((a[j]-a[k])*(a[j]-a[k])+(b[j]-b[k])*(b[j]-b[k]));	
z=sqrt((a[i]-a[k])*(a[i]-a[k])+(b[i]-b[k])*(b[i]-b[k]));
```
然后就是海伦公式。

我觉得这个公式应该很多人知道（反正我第一个学的公式是这个）。

公式如下：

$p=\frac{a+b+c}{2}$

$S=\sqrt{p(p-a)(p-b)(p-c)}$

其中 $a$，$b$，$c$ 分别为三角形的三边。

具体代码：

```cpp
p=(x+y+z)/2.0;
s=sqrt(p*(p-x)*(p-y)*(p-z));
```
然后就是我觉得这题的难点：如何判断一个实数是否为整数。

这里我是用了 $eps$，不知道有没有人知道。

这个东西是可以来弄浮点数误差的。

我也不是太懂。

具体代码：

```cpp
const double eps=1e-10;
double q=(int)(s+eps);
if(s-eps<=q&&q<=s+eps)			
{				
	ans++;			
}
```

到此，本题基本做完。

我只给你们核心代码。

希望你们可以通过自己的思考。

将本题打出来。

---

## 作者：Holy_King (赞：0)

## 解题方法

计算由a,b,c三点构成的三角形的面积，应该怎么计算呢？

记得小学时候的数格子吗？当时我们是怎么计算的？

对了，是正方形减去三个三角形

### 公式：

$$ S=(x_c-x_a)(y_c-y_b)-\frac{(x_a-x_b)(y_b-y_a)+(x_a-x_c)(y_c-y_a)+(x_c-x_b)(y_b-y_c)}{2} $$

### 因式分解后：

$$ S=\frac{(x_c-x_b)(y_a-y_b)-(x_a-x_b)(x_c-y_b)}{2} $$

最后代入即可

## 代码:

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node
{
	long long x;
	long long y;	
};

long long ans=0;

node a[110];
long long n;

long long lenx(int b1,int b2)
{
	return a[b1].x-a[b2].x;
}

long long leny(int b1,int b2)
{
	return a[b1].y-a[b2].y;
}

int main()
{
	cin >> n;
	for (int i=1; i<=n; i++)
	{
		cin >> a[i].x >> a[i].y;
	}
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<i; j++)
		{
			for (int k=1; k<j; k++)
			{
				long long S=lenx(i,j)*leny(i,k)-leny(i,j)*lenx(i,k);//公式运用
				if (S!=0&&S%2==0) ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：Fire_Raku (赞：0)

### 题目分析：

这道题需要一些关于三角形的知识，其实本质上是一道数学题，一个三角形，它可以作出一个与它的角（相切）的矩形。

如图：

![图](https://cdn.luogu.com.cn/upload/image_hosting/o1h9ktbq.png)

这样就把矩形分成四部分，三角形就可以用矩形减去各部分三角形的面积，最后剩下需要的三角形。

面积公式推出来长这样： $S = \frac{1}{2}(x_3 - x_2)(y_1 - y_2) - (x_1 - x_2)(y_3 - y_2)$。

然后三重循环枚举每三个点能不能组成三角形，如三个点组成的三角形面积不为 $0$ 且它的面积为整数，$ans$++。

```cpp
#include<bits/stdc++.h>
using namespace std ;
long long x[110] , y[110] , ans ; 
int main(){
	int n ; 
	cin >> n ; 
	for(int i = 0 ; i < n ; i++) cin >> x[i] >> y[i] ;
	for(int i = 0 ; i < n ; i++){ //枚举x1 , y1 
		for(int j = 0 ; j < i ; j++){ //枚举x2 ， y2 
			for(int k = 0 ; k < j ; k++){ //枚举x3 ， y3 ，三重循环
				long long s = (x[k] - x[j]) * (y[i] - y[j]) - (x[i] - x[j]) * (y[k] - y[j]) ; //计算面积，但是没有除以2
				if(s != 0 && s % 2 == 0) ans++ ; //在这里用取余来判断是否是整数
			}
		}
	}
	cout << ans << endl ; //记得加换行qwq
	return 0 ;
}
```

---

## 作者：一只书虫仔 (赞：0)

[AT812 格子点と整数](https://www.luogu.com.cn/problem/AT812)

这道题题目简化一下，就是说输入 $n$ 个坐标 $(x_i,y_i)$ ，然后问我们其中三个点能构造出面积为整数的三角形的个数。

~~这道题我没 AC~~ ，所以我说一下我的思路吧。

首先算已知三点 $x_1,y_1,x_2,y_2,x_3,y_3$ 求三角形面积 $S$ 的公式
$$S=(x_3-x_1)(y_3-y_2)-\dfrac{1}{2}(x_1-x_2)(y_2-y_1)-\dfrac{1}{2}(x_3-x_1)(y_3-y_1)-\dfrac{1}{2}(x_3-x_2)(y_3-y_2)$$
然后根据这个公式，套上三层枚举坐标的循环，算出来的是带小数点后精度 $\text{double}$ 类型的数 $S_d$ ，然后 $\text{double}\to \text{int}\to \text{double}$ 转换成另一个数 $S_i$，然后比较这两个数，如果 $S_d\ne S_i$ 的话，那么就说明不是整数的三角形面积，$S_d=S_i$ 的话就是。

因为出现小数的情况只有 $\dfrac{1}{2}$ 后的数不是偶数的情况，所以 $\text{double}$ 的精度应该不会超。

【暂无代码，用这种思路做出来的小伙伴可以私信给我发一下代码 \qwq】

---

