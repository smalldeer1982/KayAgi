# Rudolph and Christmas Tree

## 题目描述

Rudolph drew a beautiful Christmas tree and decided to print the picture. However, the ink in the cartridge often runs out at the most inconvenient moment. Therefore, Rudolph wants to calculate in advance how much green ink he will need.

The tree is a vertical trunk with identical triangular branches at different heights. The thickness of the trunk is negligible.

Each branch is an isosceles triangle with base $ d $ and height $ h $ , whose base is perpendicular to the trunk. The triangles are arranged upward at an angle, and the trunk passes exactly in the middle. The base of the $ i $ -th triangle is located at a height of $ y_i $ .

The figure below shows an example of a tree with $ d = 4, h = 2 $ and three branches with bases at heights $ [1, 4, 5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846D/37fc4e66c82224ed8a6c688f81f74511a07dacd6.png)Help Rudolph calculate the total area of the tree branches.

## 样例 #1

### 输入

```
5
3 4 2
1 4 5
1 5 1
3
4 6 6
1 2 3 4
2 1 200000
1 200000
2 4 3
9 11```

### 输出

```
11
2.5
34.5
199999.9999975
11.333333```

# 题解

## 作者：slzx_CPS (赞：2)

 _第一篇题解，多多包涵~_ 
 
 [题目传送门](https://www.luogu.com.cn/problem/CF1846D)
 
 在每一个 $test case$ 中，每一个三角形的形态是确定的，因此我们可以直接 $ans$ 中放入不考虑重叠的情况下的面积之和
 
 然后，我们开始处理重叠：
 
 我们可以发现出题人善良地放了 $ y_1 < y_2 < \dots < y_n $，省得我们排序了。
 
 然后我们发现重叠部分形成的三角形和原三角形是相似的，而很多边是可以知道的，因此我们可以推导出 
 
  $S = ( x - last) ^ 2 \times d \div (2 \times h)$
 
 【详细推导过程见图片】
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/2b0glx4a.png)
 
 这样大体思路就清晰了，下面附上代码：
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//养成好习惯~
int t,n;
double ans,h,d,last,x;
signed main(){
	cin>>t;
	for(int e=0;e<t;e++){//个人习惯，也可以是while(t--)
		cin>>n>>d>>h;
		last=0;//保存之前的三角形的顶点纵坐标
		ans=d*h/2*n;//直接存入不计重叠时的总面积
		for(int i=1;i<=n;i++){
			cin>>x;//读入当前三角形的底边纵坐标
			if(last>x) ans-=d*(last-x)*(last-x)/(2*h);//去除重复的面积
			last=x+h;//保存顶点
		}
		printf("%.8f\n",ans);//输出，注意小数部分长度
	}
	return 0;
}
```


---

## 作者：Larryyu (赞：1)

## _Decription_
一颗圣诞树由 $n$ 个底边为 $d$，高度为 $h$ 的等腰三角形组成，每个三角形以 $y$ 轴为对称轴，底边均平行于 $x$ 轴，三角形有可能重叠。

给出 $n,d,h$ 以及每个三角形底边与 $x$ 轴的距离,求该圣诞树的面积。
## _Solution_
![](https://cdn.luogu.com.cn/upload/image_hosting/tzx7rq3v.png)


如图，这是一棵圣诞树,其由两部分组成，完整的一个三角形 $ABC$ 和 等腰梯形 $DEGF$（底边之差大于 $h$ 时,为完整的一个三角形）。

设 $dd=FG,hh=BD$。

$\therefore S_{\texttt{tree}}=S_{\vartriangle \texttt{ABC}}+S_{\texttt{梯DEGF}}=d\times h\div2+(d+dd)\times hh$

$\because S_{\vartriangle HFG}\sim S_{\vartriangle HDE}$

$\therefore \dfrac{dd}{d}=\dfrac{h-hh}{h}$

$\therefore dd=(h-hh)\div h\times d$


因为 $hh$ 为两三角形上下底边之差，所以所有数据都已知，可以得出答案。

## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define doubl long double
int t;
double a[200200]; //要记得开 double
void solve(){
	int n;
	double d,h,ans=0;
	cin>>n>>d>>h;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
		if(a[i]-a[i-1]>h) ans+=d*h/2.0; //不重叠时是一个三角形
		else {
			double dd=(h-(a[i]-a[i-1]))*d/h;
			ans+=(dd+d)*(a[i]-a[i-1])/2.0;  //得出梯形面积
		}
	}
	ans+=d*h/2.0;  //最后一个图形总为完整的三角形
	printf("%.6lf\n",ans); //要输出6位小数
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

本来这种水题不打算写题解的，但这次上分多。。

------------

首先假设不重叠，算出总面积 $\frac{n\times d\times h}{2}$。

然后对于连续的两个相交的三角形用相似求出重叠部分减去。

若其中高的一个高度为 $a$，矮的为 $b$，重叠部分为 $\frac{d\times(b+h-a)^2}{h\times2}$。

复杂度 $\operatorname{O}(n)$。

------------

真没啥意思。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int T,n,d,h,y,lasty;
db ans;
int main(){
    T=read();
    while(T--){
        n=read();
        d=read();
        h=read();
        ans=db(d)*h/2.0*n;
        lasty=-1e9;
        for(int i=1;i<=n;i++){
            y=read();
            if(lasty+h>y)
                ans-=db(d)/h*(lasty+h-y)*(lasty+h-y)/2.0;
            lasty=y;
        }
        printf("%lf\n",ans);
    }
    return 0;
}
```


---

## 作者：foryou_ (赞：1)

因为 $n$ 个三角形有重叠部分，所以我们可以倒序处理每个三角形，并对其进行分类讨论：

- 若当前三角形编号为 $n$，则直接将总面积加上 $\dfrac{d \times h}{2}$。

- 否则，再次分出两种情况：

	- 若当前三角形的 $y_i + h > y_{i+1}$（即编号为 $i,i+1$ 的三角形有重叠），则如下图所示：
    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/2oj3hj1c.png)
    
    红色部分为重叠部分，则有 $nh=y_i+h-y_{i+1}$，根据 $\dfrac{nh}{h}=\dfrac{nd}{d}$（因为两个三角形互为相似三角形，所以底和高都是同比例放大的），可知 $nd=d \times \dfrac{nh}{h}$。
    
  - 否则，直接将总面积加上 $\dfrac{d \times h}{2}$。
  
注意强制类型转换为 `long double`，且输出时至少需要保留小数点后 $6$ 位。

[$code$](https://codeforces.com/contest/1846/submission/212980122)

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1846D)

## 思路

输入数据后将底边高度高度**从大到小排序**（因为之后要把高的三角形和低的三角形的高度做差）。之后循环枚举每一条边。记 $last$ 为上一个底边的位置并**赋初始值**为 $2\times10^{18}$（防止第一个三角形判定错误），记当前的底边高度为 $a_i$。

之后分两类讨论。

- 如果 $a_i+h\le last$，就说明这个三角形和上一个三角形**没有重叠**，这个三角形的面积就是 $d\times h\div 2$，并记录 $last=a_i$。

- 如果 $a_i+h>last$，就说明这个三角形和上一个三角形**重叠了**。这时我们可以利用简单的“整体减空白”的方法，计算出这个梯形的面积。重叠部分的三角形的高是 $h-(last-a_i)$。重叠部分的底边长可以由小高和原高的**比例**推算出来。计算得出重叠部分的底边长是 $d\times[h-(last-a_i)]\div h$。最后将大三角形面积和小三角形面积**作差**，得出这个重叠的三角形面积。

最后输出所有构成圣诞树的三角形的面积和即可。

## 注意事项

- 精度要求是 $10^{-6}$，记得开 long double，且输出的时候要至少输出**小数点后 $7$ 位**保证精度。

- 有多组测试数据，记得清空变量。

这里就不放代码了，按照上面的解析一步步模拟即可。

---

## 作者：szhqwq (赞：0)

## $\tt{Solution}$

先将 $n$ 三角形的面积加在一起，然后减去重复计算的重叠的面积。

重叠部分的面积可以采用相似三角形的方法计算出来。首先，我们可以判断如果 $y_i - y_{i - 1} < h(i \ge 2)$，那么三角形 $i$ 与 $i - 1$ 之间有重叠，$h - (y_i - y_{i - 1})$ 即为**覆盖高度**。

通过**覆盖高度**计算出覆盖三角形和原三角形的比例，然后再算出覆盖三角形的底，即可算出面积。

**注意：需要保留小数点后 $6$ 位。**

[Link](https://codeforces.com/contest/1846/submission/213239982)

---

## 作者：sgl654321 (赞：0)

震惊，CF 居然有平面几何题。
### 题目大意
- 给定 $n$ 个等腰直角三角形，它们的底均为 $d$，高均为 $h$。
- 它们的底分别在直线 $y=y_i(i\in[1,n])$ 上。对于任意 $i\in[1,n-1]$，都有 $y_i<y_{i+1}$。同时，这些等腰直角三角形底边上的高都在 $x$ 轴上。
- 请输出这些三角形的面积并。

### 解题思路
每个三角形的面积都是 $\dfrac{1}{2}dh$。从枚举到第 $2$ 个三角形，我们就要考虑减去重叠部分的面积了。

如果 $y_i-y_{i-1}\ge h$，那么没有重叠部分，无需减去面积。其他情况，都有重叠。为了方便，下面令 $\Delta y=y_i-y_{i-1}$。

重叠部分是一个等腰直角三角形。它底边上的高为 $h-\Delta y$。那么底怎么求呢？我们看下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/35fnzp9r.png)

$\triangle ABC$ 和 $\triangle DEF$ 的重叠部分为 $\triangle DGH$。连接 $AD$ 并延长交 $BC$ 于点 $I$，显然有 $\triangle AIC\sim \triangle DIH$。

故 $\dfrac{AI}{DI}=\dfrac{IC}{IH}=\dfrac{BC}{GH}$。

由于 $AI=h,DI=h-\Delta y,BC=d$，代入有 $\dfrac{h}{h-\Delta y}=\dfrac{d}{GH}$。

$GH=\dfrac{d(h-\Delta y)}{h}$，重叠部分的面积为 $\dfrac{d(h-\Delta y)^2}{2\times h}$。

减去这个值就 OK 了。
### 参考代码
注意整型和浮点型变量的转化，以及最后的保留小数。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long tt,n,d,h,y[200010],dy;
double ans;
int main(){
	cin>>tt;
	while(tt--){
		cin>>n>>d>>h;
		ans=d*h*1.0/2;
		for(int i=1;i<=n;i++)
			cin>>y[i];
		for(int i=2;i<=n;i++){
			ans+=d*h*1.0/2.0;
			if(y[i]-y[i-1]>=h)continue;
			dy=y[i]-y[i-1];
			ans-=(h-dy)*d*(h-dy)*1.0/h/2.0;
		}
		cout<<fixed<<setprecision(10)<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：Coffee_zzz (赞：0)

数学题。

### 分析

考虑把这 $n$ 个三角形看成若干个不重叠的梯形和三角形。

我们进一步优化，把三角形看成上底长为 $0$ 的梯形。

我们首先求每个梯形的高。

对于第 $i$ 个梯形，它原本的高是 $h$，但是由于上面的三角形的影响，它的高不能超过 $y_{i+1}-y_i$，所以它的高为 $\min(h,y_{i+1}-y_i)$。再根据相似，我们可以知道它的上底为 $d \times(1-\dfrac{\min(h,y_{i+1}-y_i)}{h})$。于是我们就可以求出每个梯形的面积，最终全加起来就可以。

要注意特判第 $n$ 个梯形，它的上面没有三角形，它的高就不会受到影响，就是原本的高 $h$。

### 代码

```c++
const int N=2e5+5;
int y[N];
void solve(){
	int n=read(),d=read(),h=read();
	long double ans=0.5*d*h,a;
	int c;
	for(int i=1;i<=n;i++) y[i]=read();
	for(int i=1;i<n;i++){
		c=min(h,y[i+1]-y[i]);
		a=d*(1.0-c*1.0/h);
		ans=ans+0.5*(d+a)*c;
	}
	printf("%.10Lf\n",ans);
}
```

---

## 作者：Otue (赞：0)

这个题，把所有三角形面积相加再减去重叠部分即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/ietzcrx5.png)

由相似知识得，黄边比蓝边等于 $\dfrac{h-(b-a)}{(b-a)}$，则绿边比红边等于 $\dfrac{h-(b-a)}{h}$。根据题意，红边长为 $d$，则绿边长为 $d\times \dfrac{h-(b-a)}{h}$。则重叠小三角形面积为 $\dfrac{1}{2}\times d\times \dfrac{h-b+a}{h}\times (h-b+a)$（不想整理了）。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;

int t, n, d, h;
double y[N], ans;

signed main() {
	cin >> t;
	while (t--) {
		ans = 0;
		cin >> n >> d >> h;
		for (int i = 1; i <= n; i++) cin >> y[i], ans += 0.5 * d * h;
		for (int i = 1; i < n; i++) {
			if (y[i] + h > y[i + 1]) {
				ans -= 0.5 * d * (h - y[i + 1] + y[i]) / h * (h - y[i + 1] + y[i]);
			}
		}
		printf("%.8lf\n", ans);
	}
}
```

---

