# [ABC340F] S = 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc340/tasks/abc340_f

整数 $ X,\ Y $ が与えられます。$ X,\ Y $ は $ X\ \neq\ 0 $ と $ Y\ \neq\ 0 $ の少なくとも一方を満たします。  
 次の条件を全て満たす整数の組 $ (A,\ B) $ を発見してください。そのような整数の組が存在しない場合はそれを報告してください。

- $ -10^{18}\ \leq\ A,\ B\ \leq\ 10^{18} $
- $ xy $ 平面上の点 $ (0,\ 0),\ (X,\ Y),\ (A,\ B) $ を頂点とする三角形の面積は $ 1 $

## 说明/提示

### 制約

- $ -10^{17}\ \leq\ X,\ Y\ \leq\ 10^{17} $
- $ (X,\ Y)\ \neq\ (0,\ 0) $
- $ X,\ Y $ は整数
 
### Sample Explanation 1

点 $ (0,\ 0),\ (3,\ 5),\ (1,\ 1) $ を頂点とする三角形の面積は $ 1 $ です。よって $ (A,\ B)\ =\ (1,\ 1) $ は条件を満たします。

## 样例 #1

### 输入

```
3 5```

### 输出

```
1 1```

## 样例 #2

### 输入

```
-2 0```

### 输出

```
0 1```

## 样例 #3

### 输入

```
8752654402832944 -6857065241301125```

### 输出

```
-1```

# 题解

## 作者：Genius_Star (赞：11)

### 思路：

先考虑求由 $(0,0),(x,y),(a,b)$ 组成的三角形的面积，画一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/34wci6cb.png)

明显该三角形面积为这个长方形的面积减去周边三个小三角形的面积：

$$ay-\frac{ab}{2}-\frac{xy}{2}-\frac{(a-x)(y-b)}{2}$$

化简得：

$$\frac{ay-bx}{2}$$

因为我们现在之考虑了在第二象限的情况，所以可能会有负数的情况出现，则这个三角形的面积应该是：

$$|\frac{ay-bx}{2}|$$

因为题目要求 $|\frac{ay-bx}{2}|=1$，则 $|ay-bx|=2$，发现可以用 exgcd 求，化为一般形式 $|ay+(-bx)|=2$，求一组特解出来即可。

时间复杂度为 $O(\log W)$，其中 $W$ 为值域。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll x,y,t,a,b;
ll gcd(ll n,ll m){
	return (n%m==0)?m:gcd(m,n%m);
}
void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){
		x=1;
		y=0;
		return;
	}
	ll p;
	exgcd(b,a%b,x,y);
	p=x;
	x=y;
	y=p-(a/b)*y;
	return;
}
bool check(ll x,ll y){
	return x>=-1e18&&x<=1e18&&y>=-1e18&&y<=1e18;
}
void print(ll x,ll y){
	write(x);
	putchar(' ');
	write(y);
}
int main(){
	x=read(),y=read();
	if(abs(__gcd(x,y))>2){
		puts("-1");
		exit(0);
	}
    exgcd(x,y,b,a);
	t=2/abs(__gcd(x,y)); 
    if((x*b+y*a)<0)
	  b=-b,a=-a;
	a*=t,b*=t;
	if(check(a,b))
	  print(a,-b);
	else
	  puts("-1");
	return 0;
}
```


---

## 作者：千秋星辰 (赞：4)

#### 前置~~高中数学~~知识

点 $(x_0,y_0)$ 到直线 $Ax+By+C=0$ 距离为 $\dfrac{|Ax_0+By_0+C|}{\sqrt{A^2+B^2}}$；点 $(x_0,y_0)$ 与点 $(0,0)$ 间距离为 $\sqrt{x_0^2+y_0^2}$。

#### 思路

假设输入点坐标为 $(x_0,y_0)$，所求点坐标为 $(X,Y)$。

$(x_0,y_0)$ 与 $(0,0)$ 点所在直线为 $y_0x-x_0y=0$，由三角形面积为**所求点到该直线距离**乘以**该线段长度**再除以 $2$，~~不就是底乘高除以二嘛~~，得出 $\dfrac{1}{2}\cdot\dfrac{|y_0X-x_0Y|}{\sqrt{y_0^2+(-x_0)^2}} \cdot\sqrt{x_0^2+y_0^2}=1$，化简得 $y_0X-x_0Y=2$。

所以题目的要求就是解 $y_0X-x_0Y=2$ 这个不定方程，本题有 Special Judge，所以输出任一可行解即可。

对于[二元一次不定方程](https://www.luogu.com.cn/problem/P5656)，我们一般采用[扩展欧几里得算法](https://baike.baidu.com/item/%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95/2029414)求解。

#### 代码

```cpp
#define int long long

int exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	int res=exgcd(b,a%b,y,x);
	y-=(a/b*x);
	return res;
}

signed main()
{
	int a,b,x,y,GCD,read1,read2;
	read(read1,read2);
	a=read2;
	b=-read1;
	GCD=exgcd(a,b,x,y);
	if(2ll%GCD) write(-1);
	else
	{
		x*=2ll/GCD;
		y*=2ll/GCD;
		writen(x,y);
	}
	return (0^0);
}
```
注：
`read()` 函数为我自己定义的读入函数，`write()`、`out()` 及 `writen()` 函数为我自己定义的输出函数。

---

## 作者：Register_int (赞：3)

看来大部分人的小学在二年级时并没有教这么高深的内容，那么……

#### 前置知识：向量叉积

假设我们有两个二维向量 $\vec a$ 跟 $\vec b$，那么他们的叉积 $\vec a\times\vec b$ 则为 **垂直于二者所在平面，且长度为他们所张的平行四边形的向量**。

偷张图。

![](https://pic2.zhimg.com/80/v2-651dfbe781025dcd295fd206778e72cd_720w.webp)

同样的，向量还可以通过它从 $(0,0)$ 指向哪来定义。而三角形面积则为这个平行四边形面积的一半，所以只要我们算出叉积，就能算出三角形面积。

而事实上，这个平行四边形正是一个单位正方形被 $\vec a,\vec b$ 拉伸后得到的，所以我们就能得到叉积的公式。设 $\vec a=(x_1,y_1),\vec b=(x_2,y_2)$，则有：

$$|\vec a\times\vec b|=\det\left(\left[\begin{matrix}x_1&x_2\\y_1&y_2\end{matrix}\right]\right)=|x_1y_2-y_1x_2|$$

撒花。设 $O(0,0),P(x,y),Q(a,b)$，则三角形面积为：

$$\dfrac12\left|\overrightarrow{OP}\times\overrightarrow{OQ}\right|=\dfrac12|xb-ya|$$

也就是我们要解方程 $|xb-ya|=2$。绝对值我们并不关心，因为 $a,b$ 的正负没有做限制。直接解不定方程即可，时间复杂度 $O(\log V)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, void(0);
	exgcd(b, a % b, y, x), y -= a / b * x;
}

ll a, b, ta, tb, x, y, c, d;

int main() {
	scanf("%lld%lld", &a, &b), a = -a, ta = abs(a), tb = abs(b);
	c = 2, d = __gcd(ta, tb);
	if (c % d) return puts("-1"), 0;
	exgcd(a / d, b / d, y, x), x *= c / d, y *= c / d;
	if (ta < 0) x = -x;
	if (tb < 0) y = -y;
	printf("%lld %lld", x, y);
}
```

---

## 作者：xiaoshumiao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc340_f)

别人的向量叉积做法都好强，其实手画几个图就能证明了，~~甚至 xxs 可能都会~~

结论是：$(0,0)$，$(x,y)$，$(a,b)$ 的面积为 $\frac{|ay-bx|}{2}$，即需要求出一组 $a,b$ 满足：

$$ay-bx=\pm2$$

下记 $g=\gcd(x,y)$。

- 若 $g>2$，则式子右边的 $\pm2$ 必为 $g$ 的倍数，无解。

- 否则，直接调用 $\operatorname{exgcd}(y,-x)$ 算出一组特解。若 $g=1$，则将答案乘二即可。

[code](https://atcoder.jp/contests/abc340/submissions/50201905)

---

## 作者：_sin_ (赞：2)

## 题意

给出一个点 $A(x,y)$ ，求点 $B(a,b)$ 使得 $S_{\triangle AOB} = 1$ ，如果不存在则输出 $-1$

## 思路
首先，根据向量的叉积，我们知道 $S_{\triangle AOB} = \frac{1}{2} |bx-ay|$ 所以我们就是求解方程 $|bx-ay|=2$ 的一个整数解，这个形式非常像 exgcd ，然后就可以用 exgcd 来做了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int ex_gcd(int a, int b, int &x, int &y){
	if(!b)return x=1,y=0,a;
	int d=ex_gcd(b,a%b,x,y),t=x;x=y;y=t-(a/b)*y;
	return d;
}

int x,y,a,b,d;

signed main(){
	scanf("%lld%lld",&x,&y);
	d=ex_gcd(x,-y,b,a);
	if(2%d)return puts("-1"),0;
	printf("%lld %lld",a*2/d,b*2/d);
	return 0;
}
```


---

## 作者：incra (赞：2)

### Solution
参考官解。

水题，但是没水到我会做的程度。

首先，多画几个图推一下式子可以发现三点为 $(0,0),(x,y),(a,b)$ 的点面积为 $\dfrac{\left|ay-bx\right|}{2}$（找几个形状不同的推一下就行，这里不赘述了）。

那么题目就是要求整数对 $(x,y)$ 满足 $\left|ay-bx\right|=2$。

显然扩欧可以解决这道题，注意 $x$ 的系数是 $-1$。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
LL x,y,a,b;
LL exgcd (LL a,LL b,LL &x,LL &y) {
	if (!b) {
		x = 1,y = 0;
		return a;
	}
	LL d = exgcd (b,a % b,y,x);
	y -= a / b * x;
	return d;
}
int main () {
	cin >> a >> b;
	LL d = exgcd (a,b,y,x);
	x = -x;
	if (2 % d) {
		puts ("-1");
		return 0;
	}
	x = x * (2 / d),y = y * (2 / d);
	cout << x << ' ' << y << endl;
	return 0;
}
```

---

## 作者：Otue (赞：1)

$(0,0),(x,y),(a,b)$ 的面积可以转化为 $\dfrac{1}{2}\times |ay-bx|$。

那么面积为 $1$ 等价于 $|ay-bx|=2$。可以将绝对值去掉变成 $ay-bx=2$，因为这道题 $x,y$ 随便取，不用担心正负号的问题，如果反了直接将解取相反数就行。这就转化为了不定方程求解的问题，可以用 exgcd 来做。

* 若 $\gcd(a,b)>2$，原方程无解。
* 若 $\gcd(a,b)\leq2$，可以用 exgcd 求出一组 $ay-bx=\gcd(a,b)$ 的解，得到的结果乘上 $\dfrac{2}{\gcd(a,b)}$ 即可。

给一个 exgcd 的通用模板：

```c++
void exgcd(int a, int b, int& x, int& y) {
	if (b == 0) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
}

bool get(int a, int b, int c, int& x, int& y) { // x,y为最终答案
	int x0, y0;
	int g = __gcd(a, b);
	if (c % g != 0) return 0;
	exgcd(a, b, x0, y0);
	x = x0 * (c / g);
	y = y0 * (c / g);
	return 1;
}
```
有些题目可能会限制解为正数，但这道题随便。

主函数：

```c++
signed main() {
	cin >> a >> b;
	c = 2;
	int x, y;
	if (get(-b, a, c, x, y)) cout << x << ' ' << y << endl;
	else puts("-1");
}
```

祝大家学习愉快！

---

## 作者：fcy20180201 (赞：1)

本期赛后 10 分钟 AC 又有素材了（
## 思路
一个三角形的两个顶点分别为 $(0,0)$ 和 $(x,y)$，问是否存在第三个顶点 $(a,b)$ 满足 $a,b$ 均为整数且三角形的面积**等于 $1$**。

思路是以 $(0,0),(x,y)$ 为底，算高，推式子。最近刚好学了点到直线的距离公式，能用上：

设直线为 $ax+by+c=0$，则点 $(u,v)$ 到直线的距离（高）为：
$$\frac{|au+bv+c|}{2\sqrt{a^2+b^2}}$$

证明是用相似，在这里就不过多赘述了。

开始推式子（以下的 $x_0,y_0$ 分别表示三角形第二个顶点的横纵坐标）！！！

首先直线的方程用 $y=kx+b$ 表示就是 $y=\frac{y_0}{x_0}x$（经过原点 $b$ 为 $0$）,改成一般式之后就是 $\frac{y_0}{x_0}x-y=0$，$a=\frac{y_0}{x_0},b=-1$。

三角形的面积 

$$=\frac{|au+bv+c|}{\sqrt{a^2+b^2}} \times \sqrt{(x_0-0)^2+(y_0-0)^2}$$

$$=\frac{|\frac{y_0}{x_0}u-v|}{2\sqrt{(\frac{y_0}{x_0})^2+(-1)^2}} \times \sqrt{{x_0}^2+{y_0}^2}=1$$

移项：
$$|\frac{y_0}{x_0}u-v| \times \sqrt{{x_0}^2+{y_0}^2}=2\sqrt{(\frac{y_0}{x_0})^2+(-1)^2}$$

平方：
$$(\frac{y_0}{x_0}u-v)^2\times({x_0}^2+{y_0}^2)=4((\frac{y_0}{x_0})^2+1)$$

两边同乘 ${x_0}^2$：

$$({y_0}\times u-v\times {x_0})^2\times({x_0}^2+{y_0}^2)=4({y_0}^2+{x_0}^2)$$

由于 $(x_0,y_0)\ne(0,0)$，则 ${x_0}^2+{y_0}^2\ne0$，因此两边同除 ${x_0}^2+{y_0}^2$：
$$({y_0}\times u-v\times {x_0})^2=4$$

同时开根：
$$|{y_0}\times u-v\times {x_0}|=2$$

即 ${y_0}\times u-{x_0}\times v=\pm2$，由于 $u,v$ 正负不限，不妨转化为 ${y_0}\times u-{x_0}\times v=2$。

于是：拓欧，启动！！！

### 拓欧细节
拓欧帮我们求 $ax+by=\gcd(a,b)$ 的一组特解，但我们要求的是 ${y_0}\times u-{x_0}\times v=2$。因此求出 $y_0\times u+x_0 \times v=\gcd(y_0,x_0)$ 后将 $u,v$ 同乘 $\frac{2}{\gcd(y_0,x_0)}$，再将 $v$ 取相反数就行。

注意到“将 $u,v$ 同乘 $\frac{2}{\gcd(y_0,x_0)}$”，得到 $\gcd(y_0,x_0)|2$ 时才有整数解。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll x,y,ax,ay;

ll EXgcd(ll a,ll b,ll &xx,ll &yy){//拓欧板子
    if(b==0){xx=1,yy=0;return a;}
    ll g;
    g=EXgcd(b,a%b,yy,xx),yy-=a/b*xx;
    return g;
}

int main(){
	scanf("%lld%lld",&x,&y);
	ll g=EXgcd(y,x,ax,ay);
	if(2ll%g){puts("-1");return 0;}//无解
	ax*=2/g,ay*=2/g;//处理
	printf("%lld %lld",ax,-ay);
	return 0;
}
```

---

## 作者：NaOHqwq (赞：1)

~~有人说是 ```exgcd``` 板子。~~

以下称 $(0,0)$ 为 $O$，$(X,Y)$ 为 $P$，$(A,B)$ 为 $Q$，$l$ 为 $OP$ 所在直线。

显然 $l$ 的方程为 $Yx-Xy=0$。根据三角形面积公式，$Q$ 到 $l$ 的距离应为 $\frac2{\sqrt{X^2+Y^2}}$。

由于点 $(x_0,y_0)$ 到直线 $Ax+By+C=0$ 的距离为 $\frac{|Ax_0+By_0+C|}{\sqrt{A^2+B^2}}$，则 $Q$ 到 $l$ 的距离可以写成 $\frac{|AY-BX|}{\sqrt{X^2+Y^2}}$。

所以 $AY-BX=\pm2$。

由裴蜀定理得若 $|\gcd(X,Y)|>2$ 则不存在符合条件的 $Q$，否则可以由 ```exgcd``` 求出答案。

因为 ```exgcd``` 求解的是 $ax+by=gcd(a,b)$，若$|\gcd(X,Y)|=2$，则可以直接输出  ```exgcd``` 的结果，否则将 $X,Y$ 同乘 $2$，得到 $P=(2X,2Y)$ 时的结果 $(a,b)$，由于 $OP$ 延长了 $2$ 倍，$\sqrt{a^2+b^2}=\frac{OQ}{2}$，输出 $(2a,2b)$。

---

## 作者：Xiphi (赞：1)

有够抽象的。报了 unr 结果 15min 切掉 F，没报反而掉分/tuu。

考虑到海伦公式没前途，考虑 Shoelace Theorem（鞋带定理）。大意如下：对于任意一个多边形，如果已知其各个顶点的坐标 $A_1(x_1,y_1),A_2(x_2,y_2),\dots,A_n(x_n,y_n)$，其面积为 $\frac{|\sum_{i=1}^n x_i\times y_{i+1}-x_{i+1}\times y_{i}| }{2}$。其中 $y_{n+1}=y_1$，$x_{n+1}$ 同理。

转化到这题上，三角形面积即为 $|0\times y - x \times 0+x\times B-y\times A+0\times A-0\times B|$ **除以 $2$** 的值。题目要求其面积为 $1$，也就是说简化之后相当于 $|x\times B-y\times A|=2$。这个就是典型的二元一次方程求根，exgcd 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define ll long long
int A,B,C=2;
ll gcd(ll a,ll b)
{
	if(!b)return a;
	return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b){x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	ll t=x;
	x=y,y=t-a/b*y;
}
signed main(){
	cin>>A>>B;
	//Bx-Ay=2;
	int d=gcd(B,-A);
	if(C%d!=0)
	{
		printf("-1\n");
		exit(0);
	}
	int x=0,y=0;
	A/=d,B/=d,C/=d;
	exgcd(B,-A,x,y);
	x*=C,y*=C;
	cout<<x<<' '<<y<<'\n';
	return 0;
}

```


---

## 作者：Starrykiller (赞：1)

# 【题解】 [ABC340F] $S = 1$

题意很清楚了。

线性代数板子题。

我们有如下的结论：

对于 $\triangle ABC$，$\overrightarrow{AB}=(x_1,y_1)$，$\overrightarrow{AC}=(x_2,y_2)$，则 

$$2S_{ABC}=\left|\det 
\left|
\begin{matrix}
x_1 & x_2 \\
y_1 & y_2 
\end{matrix}
\right|
\right|$$

证明：考虑行列式的几何意义。二阶行列式 $\left|
\begin{matrix}
x_1 & x_2 \\
y_1 & y_2 
\end{matrix}
\right|$ 的几何意义即为两个从原点出发的向量 $(x_1,y_1)$ 和 $(x_2,y_2)$ 构成的平行四边形的**有向面积**。

于是不难得到上述结论。

问题转化为：给定 $X,Y$，求出 $A,B$，使得

$$\left|\det 
\left|
\begin{matrix}
X & Y \\
A & B 
\end{matrix}
\right|
\right|=2$$

（为了方便将矩阵转置了一下，不难证明不影响结论）

也就是

$$|BX-AY|=2$$

当 $BX-AY=-2$ 时，只需令 $B'=-B,A'=-A$ 即可使得 $B'X-A'Y=2$。

注意到这是一个二元一次不定方程的形式。无解当且仅当 $2\nmid \gcd(X,Y)$。

感谢 **escapist404** 指出，exgcd 求得的解的绝对值不大于其系数的绝对值。由于 $|X|,|Y|\leq 10^{17}$，所以 exgcd 有解则一定有符合要求的解。

随便写一下就过了。

[My submission](https://atcoder.jp/contests/abc340/submissions/50168612)

---

## 作者：Nelofus (赞：0)

令原线段长度为 $len=\sqrt{X^2+Y^2}$，原线段所在直线解析式可以写作
$$
y=\frac{Y}{X}x
$$
$$
-\frac{Y}{X}x+y=0
$$
我们知道点 $(a,b)$ 到这条直线的距离是：
$$
\begin{aligned}
\frac{|\frac{Y}{X}a-b|}{\sqrt{\frac{Y^2}{X^2}+1}}&=\frac{2}{len}\\

\end{aligned}
$$
推一下式子：
$$
\begin{aligned}
\frac{|\frac{Y}{X}a-b|}{\sqrt{\frac{Y^2}{X^2}+1}}&=\frac{2}{len}\\
|\frac{Y}{X}a-b|&=\frac{2\sqrt{\frac{Y^2}{X^2}+1}}{len}\\
|\frac{Y}{X}a-b|&=\frac{2\frac{1}{X}\sqrt{X^2+Y^2}}{len}\\
|\frac{Y}{X}a-b|&=\frac{2}{X}\\
|Ya-Xb|&=2
\end{aligned}
$$
直接 EXGCD 解方程就行了。
```cpp
#include <bits/stdc++.h>
using i64 = long long;
using i128 = __int128;

void exgcd(i64 a, i64 b, i64 &x, i64 &y, i64 &d) {
	if (b == 0)
		d = a, x = 1, y = 0;
	else {
		exgcd(b, a % b, y, x, d);
		y -= a / b * x;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	i64 X, Y;
	std::cin >> X >> Y;

 	i64 x, y, d;

	exgcd(X, Y, y, x, d);

	if (std::gcd(X, Y) > 2) {
		std::cout << -1 << '\n';
		return 0;
	}
	x = x * (2 / d), y = y * (2 / d);
	std::cout << -x << ' ' << y << '\n';
	return 0;
}
```

---

## 作者：atomic_int (赞：0)

**tips：已知三角形三点坐标 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$，则该三角形的面积为 $\frac{1}{2}\left| (y_2-y_1)(x_3-x_1)+(y_1-y_3)(x_2-x_1) \right|$。**

所以 $|AY-BX|=2$ 时存在 $(A,B)$。列出方程 $AY-BX=2$，若 $\gcd(X,Y) \nmid 2$，则无解；反之，用扩展欧几里得求出一组 $=\gcd(X,Y)$ 时的解 $A,B$，再将他们乘上 $\frac{2}{\gcd(X,Y)}$ 即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  ll d = exgcd(b, a % b, x, y);
  ll t = x;
  x = y, y = t - a / b * y;
  return d;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll x, y;
  cin >> x >> y;
  x = -x;
  if (2 % __gcd(x, y) != 0) {
    cout << "-1\n";
    return 0;
  }
  ll a, b;
  exgcd(y, x, a, b);
  a *= 1ll * 2 / __gcd(x, y);
  b *= 1ll * 2 / __gcd(x, y);
  cout << a << " " << b << "\n";

  return 0;
}
```

---

## 作者：NATO (赞：0)

### 一句话题意:

给定坐标 $(x,y)$，求是否存在坐标 $(a,b)$ 满足 $a,b$ 均为整数且 $(x,y),(a,b),(0,0)$ 三点围成三角形面积为 $1$，若存在则任意输出一个答案即可。

### 解题思路：

本题重点在于对题目的转化。

考虑我们如何表示出三角形的面积。由于在坐标系内，我们就想要尽量将面积用坐标表示。由于我们的三点中有一个原点，容易想到将从原点到另外两个点的有向线段看作向量。根据向量叉乘的几何意义可知，本题三角形的面积即为 $\frac{|xb-ya|}{2}$，那么我们需要解决的问题既是如下方程是否有整数解：

$$\frac{|xb-ya|}{2}=1$$

考虑我们有解只需要任意输出一个答案，那么我们可以不管绝对值（如果有解，那么将 $a,b$ 分别取反必然是另外一个解，无解也就仍然无解），直接化简为如下形式：

$$xb-ya=2$$

看到这里，我们可以意识到这就是一个二元一次不定方程的模板，套板子即可，在此不做过多说明，有解输出时注意顺序和正负即可。

总结一下，我们对这道题的转化核心是注意到了特殊点原点，进而利用向量的知识去表示面积。在平面直角坐标系中，这种将点转化为向量的方法可以使我们获得强大的工具去对数值进行处理，这是我们这道题最大的收获。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll x,y;
ll exgcd(ll a,ll b,ll &x,ll &y)
{
	ll d=a; 
	if(b==0) x=1,y=0; 
	else d=exgcd(b,a%b,y,x),y-=a/b*x;
	return d;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>x>>y;
	ll val=__gcd(abs(x),abs(y));
	if(2%val)
	{
		cout<<-1;return 0;
	}
	ll a,b;
	ll d=exgcd(abs(x)/val,abs(y)/val,b,a);
	cout<<(y<0?-1:1)*-a*(2/val)<<' '<<(x<0?-1:1)*b*(2/val);
} 
```


---

## 作者：PikachuQAQ (赞：0)

## Description

[**Link**](https://www.luogu.com.cn/problem/AT_abc340_f)

已知坐标系里有两点 $(0,0)$ 和 $(a,b)$，求一点 $(x,y)$ 使得这三点组成的三角形面积为 $1$。无解输出 $-1$。

## Solution

注意到已知其中两个点坐标分别为 $(a,b)$ 和 $(0,0)$，面积为 $S$，则有 $\dfrac{|ay-bx|}{2}=1$，据题得 $ay-bx=±2$。这种形式的方程，可以用 exgcd 解决。当 $a$ 和 $b$ 的最大公因数大于 $2$，那么无解。

我们通过 exgcd 得到了一对解，为 $ay_0-bx_0=±\gcd(a,b)$，将 $(x_0,y_0)$ 分别除以 $-\dfrac{g}{2}$ 和 $\dfrac{g}{2}$ 即可得到正确解 $(x,y)$。

## Code

```cpp
// 2024/2/11 PikachuQAQ

#include <iostream>

using namespace std;

typedef long long ll;

ll a, b, x, y, g;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    } else {
        ll d = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> a >> b, g = exgcd(a, b, y, x);
    if (abs(g) > 2) {
        cout << "-1";
        return 0;
    }
    x *= -2 / g, y *= 2 / g;
    cout << x << ' ' << y;

    return 0;
}
```

---

## 作者：cancan123456 (赞：0)

首先我们需要知道如何计算三角形面积，可以使用叉积进行计算。

即，$(0,0),(a,b),(x,y)$ 三点围成的三角形面积是：

$$\frac12|(a,b)\times(x,y)|=\frac12|ay-bx|$$

所以我们需要找到满足 $|ay-bx|=2$ 的 $(a,b)$，注意到如果 $ay-bx=-2$，那么 $a\cdot(-y)-b\cdot(-x)=2$，所以我们不需要考虑 $ay-bx=-2$ 的情况。

这个 $-bx$ 不是很顺眼，所以我们做一个替换，令 $x'=-x$，则原方程变为 $ay+bx'=2$，这个形式很像 [exgcd](https://www.luogu.com.cn/problem/P5656)，于是就做完了。

时间复杂度为 $O(\log\max(a,b))$，可以通过此题。

```cpp
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;
// ax + by = gcd(a, b)
ll exgcd(ll a, ll b, ll & x0, ll & y0) {
	if (b == 0) {
		x0 = 1;
		y0 = 0;
		return a;
	} else {
		ll g = exgcd(b, a % b, y0, x0);
		y0 -= a / b * x0;
		return g;
	}
}
pair < ll, ll > solve(ll x, ll y) {
	y *= -1;
	int sgn_x = 1, sgn_y = 1;
	if (x < 0) {
		sgn_x = -1;
		x *= -1;
	}
	if (y < 0) {
		sgn_y = -1;
		y *= -1;
	}
	ll a, b;
	ll g = exgcd(x, y, b, a);
	if (2 % g != 0) {
		return make_pair(0, 0);
	} else {
		ll mult = 2 / g;
		return make_pair(a * sgn_x * mult, b * sgn_y * mult);
	}
}
int main() {
	ll x, y;
	scanf("%lld %lld", &x, &y);
	pair < ll, ll > p = solve(x, y);
	if (p.first == 0 && p.second == 0) {
		printf("-1");
	} else {
		printf("%lld %lld", p.first, p.second);
	}
	return 0;
}
```

---

## 作者：SJZ2010 (赞：0)

### 简要题意

给出一个点 $P$ 的坐标 $(X,Y)$，求另一个点 $Q$ 的坐标 $(A,B)$（$A$ 和 $B$ 都是整数），使 $S_{\Delta OPQ}=1$。

### 做法

我们知道，三角形的面积可以用向量的叉积来求，即：

$$S_{\Delta OPQ}=\frac{|\overrightarrow{OP} \times\overrightarrow{OQ}|}{2} $$

我们移项，将右边展开来：

$$
\begin{aligned}
2S_{\Delta OPQ} &= |(X,Y)\times (A,B)| \\
&= |XB-YA|
\end{aligned}
$$

于是我们就得到了方程：

$$|XB-YA|=2$$

这个方程用 exgcd 解出 $XB_0-YA_0 = \gcd(X,Y)$ 时的一组解，然后输出 $A = \frac{A_0 \times 2}{g}, B = \frac{B_0 \times 2}{g} $ 即可。（$g = \gcd(X, Y)$）具体原理在[这里](https://oi-wiki.org/math/number-theory/gcd/#%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95)。

[无解的情况](https://oi-wiki.org/math/number-theory/linear-equation/#%E7%94%A8%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95%E6%B1%82%E8%A7%A3)是 $\gcd(X,Y) \nmid 2$，这时 $A$ 和 $B$ 无整数解。

代码：

```cpp
#include <bits/stdc++.h>

using ll = long long;
using LL = __int128;
using qi = std::queue < int >;
using vi = std::vector < int >;
#define pq std::priority_queue
#define ve std::vector < edge >
#define VE std::vector < EDGE >
#define me(a, b) std::memset(a, b, sizeof(a))

const int N = 1e5 + 5; // This need you to adjust
const double TLS = 1;
const double eps = 1e-9;
const int inf = 0x3f3f3f3f;
const int CPS = CLOCKS_PER_SEC;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const double TLC = TLS * 0.97 * CPS;

LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}
void exgcd(LL a, LL b, LL& x, LL& y) // 解方程
{
	if (!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

ll x, y;

void write(LL a) // 用了 __int128，要手写输出
{
	if (a < 0) // 注意判断负数，不然会输出奇怪符号
	{
		putchar('-');
		a = -a;
	}
	if (a / 10)
		write(a / 10);
	putchar(a % 10 + '0');
}

int main()
{
	scanf("%lld %lld", &x, &y);
	LL A, B;
	// xB - yA = +-2
	LL g = gcd(x, y);
	if (g != 1 && g != -1 && g != 2 && g != -2)
	{ // 判断无解
		printf("-1\n");
		return 0;
	}
	exgcd(x, -y, B, A); // 解方程 XB-YA=2，注意带入的是 -y 
	LL k = 2 / g;
	write(A * k), putchar(' '), write(B * k), putchar('\n');//计算最终结果并输出
	return 0;
}

```

---

## 作者：rainygame (赞：0)

既然题目已经给了三角形的两个点了，我们不妨考虑计算这两个点连的边上的高来构造三角形。

首先这条边的长度显然为 $l=\sqrt{X^2+Y^2}$，且所在直线方程式为 $Yx-Xy=0$，根据点到直线距离公式，点 $(A,B)$ 到直线 $Yx-Xy=0$ 的距离为 $d=\dfrac{\lvert YA-XB\rvert}{\sqrt{X^2+Y^2}}$，这样所构成的三角形面积为 $\dfrac{1}{2}dl=1$，化简可得 $\lvert YA-XB\rvert=2$。发现这个绝对值有没有无所谓（大不了 $A,B$ 同时取相反数），所以只需要找到 $YA-XB=2$ 的任意一组整数解即可。

这是一个关于 $A,B$ 的二元一次方程，直接上 exgcd 解即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int x, y, a, b;

int ex_gcd(int a,int b,int &x,int &y){
    if(b==0) {x=1;y=0;return a;}
    int d=ex_gcd(b,a%b,x,y);
    int tmp=x;x=y;y=tmp-a/b*y;
    return d;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> x >> y;
    if (__gcd(llabs(x), llabs(y)) > 2){
        cout << -1;
        return 0;
    }
    swap(x, y);
    y = -y;

    int d(ex_gcd(x, y, a, b));
    cout << 2/d*a << ' ' << 2/d*b;

    return 0;
}

```


---

## 作者：xixisuper (赞：0)

# [ABC340F] S = 1 题解

一道好题。

## 思路

需要用到基础数论知识和一些初中的做题经验。

题目含义简述：

- 给定一个点的坐标 $(a,b)$（题目中给的是 $X$、$Y$，但为了方便计算，用 $a$、$b$ 代替）。
- 问是否存在一个点 $(c,d)$，使得以 $(0,0)$、$(a,b)$ 和 $(c,d)$ 所构成的三角形面积为 $1$，且 $c$、$d$ 为整数。如果存在，输出任意一组 $c$、$d$，否则输出 $-1$。

在初中阶段，我们解决平面直角坐标系中一般三角形求面积的题时，会使用**铅锤高 $\times$ 水平宽 $\div 2$ 这一面积公式**。

![三角形](https://cdn.luogu.com.cn/upload/image_hosting/7eygoltj.png?x-oss-process=image/resize,m_lfit,h_780,w_900)

PS：该公式的本质就是把 $\triangle ABC$ 分割成了 $\triangle ACE$ 和 $\triangle BCE$ 两部分，先分别求面积，再加和，最后使用乘法分配律，读者可自行推导。

我们设三角形的面积为 $S$，铅锤高为 $h$，水平宽为 $p$。

由于我们已知三角形的两点坐标为 $(0,0)$ 和 $(a,b)$，所以可以推得 $p=\left| a \right|$（其实这里 $a$ 的正负并不影响计算结果，所以我们默认 $a$ 是正数）。又因为 $S=1$，我们便可以求出铅锤高。

$$S=\frac{1}{2}ph$$
$$1=\frac{1}{2}ah$$
$$h=\frac{2}{a}$$

原来两点所构成的直线解析式为：
$$y=\frac{b}{a}x$$

则点 $(c,d)$ 一定在如下直线上：
$$y=\frac{b}{a}x \pm \frac{2}{a}$$

则问题转化为该直线上是否存在横纵坐标都为整数的点，我们可以简单的将该直线解析式转换一下。

等号两边同乘 $a$ 得：

$$ay=bx \pm 2$$

移项得：

$$-bx+ay=\pm 2$$

用**扩展欧几里得算法**解这个不定方程即可（不会扩欧算法的请自行 bdfs）。

## 代码

本人代码水平不高，不喜勿喷。

```cpp
#include <iostream>
#define ll long long
using namespace std;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;y=0;
		return a; 
	}
	ll ret=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return ret;
}
int main(){
	ios::sync_with_stdio(false);
	ll a,b;
	cin>>a>>b;
	ll x,y,g=exgcd(-b,a,x,y);
	if(2%g!=0){
		cout<<-1;
		return 0;
	}
	ll k=2/g;
	cout<<k*x<<' '<<k*y;
	return 0;
}
```


---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://atcoder.jp/contests/abc340/tasks/abc340_f)

如果你知道了以 $(0, 0), (A, B), (C, D)$ 为顶点的三角形的面积为 $\frac{|AD - BC|}{2}$，那么这个问题就很好解决了。可以在草稿纸上画一下，很轻松理解。

## 思路

题目给定了 $X,Y$，然后吧唧吧唧一大堆，就是想让我们求出一个 $A, B$，使得 $\frac{|AY-BX|}{2}$ 为 $1$，转换一下，就是 $|AY+(-B)X| = 1$，这不就是典型的扩展欧几里得吗？

## 做法

我们设 $g$ 为 $\gcd(X, Y)$，如果 $g \ge 3$ 那么说明无解，因为当 $AX + BY = \gcd(A,B)$ 时该方程才有解。将 $-Y, X$ 带入上述方程求出 $A, B$，将 $A, B$ 分别乘上 $\frac2g$ 就可以得到正确的答案。因为我们要求 $AX + BY = 2$，而现在是 $AX +BY = g$，左右两边同时乘上 $\frac2g$ 即可。

## AC Code：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
long long x, y;
long long e_gcd(long long a, long long b, long long &x, long long &y) {
	if (!b) {
		x = 1ll;
		y = 0ll;
		return a;
	}
	long long gcd = e_gcd(b, a % b, y, x);
	y -= a / b * x;
	return gcd;
}
long long a, b;
long long gcd(long long x, long long y) {
	if (y == 0ll) return x;
	return gcd(y, x % y);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> x >> y;          
	long long g = gcd(x, y);
	e_gcd(y, -x, a, b);
	if (abs(g) >= 3ll) {
		cout << -1ll;
		return 0;
	}
	a *= 2ll / g, b *= 2ll / g;
	cout << a << ' ' << b;
	return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution

首先有一个重要的结论：三角形的面积为 $\dfrac{\vert AY-BX\vert}2=1$，建议自己画下图理解。

把 $2$ 移过去，得到 $AY-BY=\pm2$。

可以发现这个式子的形式很像 $\texttt{exgcd}$ 式子的形式 $ax+by=\gcd(a,b)$。

令 $a=Y$，$x=Y$，$b=-B$，$y=X$，跑下 $\texttt{exgcd}$。

如果 $\gcd(a,b)>2$，那么一定无解。

否则就可以构造出一组解：$X=\dfrac{2y}{\gcd(a,b)}$，$Y=\dfrac{2x}{\gcd(a,b)}$。

注意要特判一下跑完 $\texttt{exgcd}$ 后返回的 $\gcd$ 为负数的情况，时间复杂度为 $O(\log\min(\vert X\vert,\vert Y\vert) )$。

# Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;

int exgcd(int a,int b,int &x,int &y)
{
	if (!b) return x=1,y=0,a;
	int d=exgcd(b,a%b,y,x);
	return y-=a/b*x,d;
}
main()
{
	int a,b,x,y,d;
	scanf("%lld%lld",&a,&b);
	b=-b,d=exgcd(a,b,y,x);
	if (abs(d)>2) printf("-1");
	else printf("%lld %lld",x*2/d,y*2/d);
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

没有学过解析几何的同学的福利。

现在平面上有点 $(x_0, y_0)$。过 $(x_0, y_0)$ 和 $(0, 0)$ 做直线 $l : y = \dfrac{y_0}{x_0} x$。移项得 $h = \dfrac{2}{\sqrt{x_0 ^ 2 + y_0 ^ 2}}$

将 $(x_0, y_0)$ 到原点的距离 $\sqrt{x_0 ^ 2 +y_0 ^ 2}$ 作为三角形底的长度，$(a, b)$ 直线 $y = \dfrac{y_0}{x_0} x$ 的垂线段作为高 $h$。所求即为 $(a, b)$ 使得 $\dfrac{1}{2} h \sqrt{x_0 ^ 2 +y_0 ^ 2} = 1$。

考虑如何求出 $h$。由于到直线 $l$ 距离相等的点集为两条直线 $l_1, l_2$，且 $l_1, l_2$ 与 $l$ 平行。

不妨设 $l_2 : y = \dfrac{y_0}{x_0}x +b, l_3: y= \dfrac{y_0}{x_0} x - b$。

这里仅对其中一条进行讨论。设直线 $y = \dfrac{y_0}{x_0} x$ 与 $x$ 轴的夹角为 $\alpha$，则有 $\tan \alpha = \dfrac{y_0}{x_0}$。

由此可以求出其正弦值 $\sin \alpha = \dfrac{y_0}{\sqrt{x_0 ^ 2 + y_0 ^ 2}}$。

我们知道 $l_3$ 与 $x$ 轴交点的横坐标为 $-\dfrac{b}{k} = \dfrac{-bx_0}{y_0}$。

由此可以得到 $l_3$ 到 $l$ 的距离为 $\dfrac{-bx_0}{y_0} \times \sin \alpha = \dfrac{-bx_0}{y_0} \times \dfrac{y_0}{\sqrt{x_0 ^ 2 + y_0 ^ 2}}$

由于我们要让三角形的面积为 $1$，根据上面的分析，则有

$$\dfrac{-bx_0}{y_0} \times \dfrac{y_0}{\sqrt{x_0 ^ 2 + y_0 ^ 2}} = \dfrac{2}{\sqrt{x_0 ^ 2 + y_0 ^ 2}}$$

$$b = - \dfrac{2}{x_0}$$

代入表达式可知，$l_2 : y = \dfrac{y_0}{x_0}x - \dfrac{2}{x_0}\dfrac{}{}, l_3: y= \dfrac{y_0}{x_0} x + \dfrac{2}{x_0}$。这里得到：

$$l' :x_0 y - y_0 x = \pm 2$$

其中 $x, y$ 是未知数，$x_0, y_0, 2$ 为常数，转化为不定方程求解问题。求出的不定方程的根即为 $(a, b)$。

```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

int x0, y0, x, y;
int gcd(int a, int b) { 
	return !b ? a : gcd(b, a % b); 
}
int exgcd(int &x, int &y, int a, int b) {
    if (!b) { x = 1, y = 0; return a; }
    int d = exgcd(y, x, b, a % b);
    y -= (a / b) * x; return d;
}
signed main() {
	scanf("%lld%lld", &x0, &y0);
	int d = gcd(x0, y0);
	if (2 % d != 0) return puts("-1"), 0;
	exgcd(x, y, y0, x0);
	x *= -2 / d, y *= 2 / d;
	cout << x << ' ' << y << endl;
	return 0;
}
```

---

## 作者：MornStar (赞：0)

# ABC340F S=1 题解

## 题目大意

给定点 $A(a,b)$ ，求一个点 $B(x,y)$，使得 $S_{\Delta{OAB}}=1$。其中 $O$ 为原点。

## 思路

给出一个结论：$S_{\Delta{OAB}}=\dfrac{\mid ay-bx\mid}{2}$。

在这个视频里有较详细的讲解，[行列式的本质是什么？三行四列行列式有什么问题？【无痛线代】](https://www.bilibili.com/video/BV13e411m7Js/?spm_id_from=333.337.search-card.all.click&vd_source=560a9aad2d29b7776dcac2c0840ba2ed)。

因为这里是三角形，所以我们可以翻折一下，将其变成平行四边形，问题就转化成了使平行四边形面积为 $2$ 即 $\mid ay-bx\mid=2$。

因为我们只需要求出一个解，问题可以简单的转化成 $ay-bx=2$。

于是我们就可以使用 exgcd 解出这个方程。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,x,y;
long long gcd(long long x,long long y){return y?gcd(y,x%y):x;}
void Exgcd(long long a,long long b,long long& x,long long &y){
	if(!b){
		x=1,y=0;return;
	}else	Exgcd(b,a%b,y,x),y-=a/b*x;
}
int main(){
	cin>>x>>y;
	int gd=gcd(abs(x),abs(y));
	if(2%gd!=0)	cout<<"-1\n";
	else{
		Exgcd(x,-y,b,a);
		cout<<a*(2/gd)<<" "<<b*(2/gd)<<"\n";
	}
}
```




---

