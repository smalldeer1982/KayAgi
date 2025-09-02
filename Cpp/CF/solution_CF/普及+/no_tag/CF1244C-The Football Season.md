# The Football Season

## 题目描述

Berland Capital Team 比了 $n$ 场比赛，总得分为 $p$。已知胜一场得 $w$ 分，平一场得 $d$ 分，败一场不得分。

求任意一组 $(x,y,z)$ 使得如果 Berland Capital Team 胜 $x$ 场，平 $y$ 场，败 $z$ 场时总分为 $p$。如果不存在这样的三元组，输出 $-1$。

### 形式化题意

求下列方程组的任意一组非负整数解，无解输出 $-1$：

$$
\begin{cases}
x\cdot w+y\cdot d=p\\
x+y+z=n
\end{cases}
$$

## 样例 #1

### 输入

```
30 60 3 1
```

### 输出

```
17 9 4
```

## 样例 #2

### 输入

```
10 51 5 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
20 0 15 5
```

### 输出

```
0 0 20
```

# 题解

## 作者：AutumnKite (赞：10)

其实就是要求 $ax+by=c$ 的一组 $x+y$ 最小的非负整数解。同时又保证了 $a>b$，那么显然只要使得 $y$ 最小即可。

一开始写了一个扩欧，发现 $x,y$ 同时乘 $c/gcd(a,b)$ 会爆 `long long`。

回过头来看数据范围，$a,b$ 只有 $10^5$。我们知道，如果原方程有非负整数解，那么 $y$ 在 $[0,a)$ 中一定存在一个非负整数解。

直接枚举即可。

时间复杂度 $O(a)$。

```cpp
#include <cstdio>
long long n, p, a, b, x, y;
int main(){
	scanf("%lld%lld%lld%lld", &n, &p, &a, &b);
	while (y < a && (p - 1ll * b * y) % a) ++y;
	if (y == a) return puts("-1"), 0;
	x = (p - 1ll * b * y) / a;
	if (x < 0 || x + y > n) return puts("-1"), 0;
	printf("%lld %lld %lld\n", x, y, n - x - y);
}
```

---

## 作者：lyb666666 (赞：7)

[更好的阅读体验？？](https://www.cnblogs.com/Tieechal/p/11677253.html)

**Hint**

$1<=n<=10^{12}$,$0<=p<=10^{17}$，$1<=d<w<=10^{15}$。

注意，题目数据保证了$d<w$，也就是赢一场的得分严格大于平局一场的得分。

## 题解

一开始看题，直接打了个exgcd去解不定方程最小解，结果好像中间会爆long long 就WA掉了。其实仔细读题，根本根本不需要这样搞。

现在需要解一个这样的方程组

$$x+y+z=n\cdots(1)$$ 
$$x \cdot w+y \cdot d=p\cdots (2)$$

①式可以转化为$x+y<=n$，$z$的大小再根据$x,y$具体调整即可。

假设存在一组二元组$(x,y)$，已经能够满足②式了，现在考虑再构造一组解，使得$x+y$尽量小，能满足①式。

则有
$$x\cdot w+w\cdot d-w\cdot d+y\cdot d=p$$
$$→(x+d)\cdot w+(y-w)\cdot d=p$$

也就是说必然还存在一组满足②式的解$(x+d,y-w)$，多次进行这样的操作，可以得到$(x+2d,y-2w)$，$(x+3d,y-3w)$，......，由于需要满足$x>0,y>0,z>0$，必然有一个下限使得此时的$y'<w$，减不动了，可以证明此时的这组解一定是最优的（也就是此时的$x'+y'$最小）。为什么呢，由于题目强调了$w>d$，也就是$x->x'$的增量小于$y->y'$减量，所以此时的$x'+y'$一定最小。

所以只用枚举$y∈[0,w-1]$即可，然后分别带入计算得到此时的$x$，再判一下$x+y<=n$这个条件，如果这个范围内都没有满足条件的解，$y$再往大枚举也不可能出现满足条件的解了。

综上时间复杂度为$O(W)$，$W<=10^5$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
ll n,p,w,d;
signed main(){
	cin>>n>>p>>w>>d;
	for(int y=0;y<w;y++){
		int left=p-y*d;
		if(left%w)continue;
		int x=left/w;
		if(x>=0&&x+y<=n){
			printf("%lld %lld %lld\n",x,y,n-x-y);
			return 0;
		}
	}
	puts("-1");
}
```

---

## 作者：寒鸽儿 (赞：6)

人间降智行为  
直接套exgcd然后overflowed了  
然后考虑暴力  
显然若使$x + y$最小,有$y \in [0, w) $  
枚举$y$即可  
```cpp
#include <cstdio>
#define ll long long

using namespace std;

int main() {
	ll n, p, a, b, x, y;
	scanf("%lld %lld %lld %lld", &n, &p, &a, &b);
	for(y = 0; y < a; ++y) {
		if(!((p-b*y)%a)) {
			x = ( p - b * y ) / a;
			if(x + y > n || x < 0) {
				printf("-1\n");
			} else {
				printf("%lld %lld %lld\n", x, y, n - x - y);
			}
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
```

---

## 作者：AFOier (赞：5)

首先推荐一篇简洁明快的博客：

[关于ax+by=c的解x，y的min(|x|+|y|)值问题](https://www.cnblogs.com/tuigou/p/4644057.html)


------------


这题暴力乱搞都能过。。。

我比赛的时候还写半天然后忘记取模直接爆炸了

题面说得很清楚，即要求求出满足

$x ⋅ w + y ⋅ d = p$ ①

$x + y + z = n$ ②

的任意一组非负整数解$x, y, z$

我们发现当$x+y$取得最小值时，$z$可以取得最大值。若此时仍有$z<0$，**则无解，输出$-1$**

接下来考虑有解的情况:

对于①式，我们可以将其移项为

$y=\frac{p}{d}-\frac{w}{d}x$

题面中有$w > d$，所以$k=-\frac{w}{d}<-1$

可画出图像：

![](https://cdn.luogu.com.cn/upload/image_hosting/oupphvsr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


$∵k<-1$

$∴$当$y=0$时，$x+y$取得最小值

但是此时取得的点不一定为整点，所以我们考虑取通过exgcd求满足$x>=0, y>=0$的y最小的整点

然后再判断，如果此时$x<0$或$z<0$，则**无解**

否则**此时$x, y, z$即为该方程的一组合法解**

---

## 作者：ethan0328 (赞：2)

## 错误示范

一眼 exgcd，然后发现炸了。

## 正确思路

发现若要使 $x+y$ 最小，因为 $d<w$，所以要让 $y \le w$。

$w\le 10^5$，直接枚举即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int w,d,p,n;
signed main()
{
	cin>>n>>p>>w>>d;
	for(int i=0;i<=w&&i*d<=p;i++)
	{
		if((p-i*d)%w==0)
		{
			if((p-i*d)/w+i<=n)
			{
				cout<<(p-i*d)/w<<" "<<i<<" "<<n-(p-i*d)/w-i;
				return 0;
			}
		}
	}
	cout<<-1;
}
```


---

## 作者：luckyqwq (赞：1)

# CF1244C The Football Season 题解

### 大致思路：

因为在这道题目中，会发现 $z$ 对于最终的分数 $p$，是不会产生贡献的，所以可以先不考虑 $z$。问题就变成了找出一组合法解 $x, y$，使得满足 $x ⋅ w + y ⋅ d = p$ 和 $x + y \le n$，很明显从本题的数据范围中可以发现，我们肯定不能从 $n$ 中入手，必定得从 $w$ 或者 $d$ 中入手。我们可以通过感性想一想，$x, y$ 必定不会特别大，也就是不会超过 $\max(w, d)$，因为 $w, d$ 已经很大了，如果 $x, y$ 也很大，那么会导致超过范围。

再接着，我们需要想到一道很经典的题目，百钱买百鸡，我们是通过鸡的个数，优化了最里面那一层循环。在本题也是如此，我们可以通过枚举一个数，在通过得分 $p$ 倒推出另一个数字，在这里，我们会发现 $w > d$，那么可以想到如果枚举 $x$，由于 $x ⋅ w$ 应该会较为大，所以枚举 $y$ 感觉效果较好。

可能有人会问，不是还有 $z$ 吗？但是我们前面讲到 $z$ 对于 $p$ 是没有贡献的，通过前面的倒推，$z$ 显然就等于 $n - x - y$，总时间复杂度为 $O(\max(w, d))$。

### 代码实现：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, p, w, d, x, y;
signed main()
{
    cin >> n >> p >> w >> d;
    int mx = max(w, d);
    while(1)
    {
        if((p - (y * d)) >= 0 && (p - (y * d)) % w == 0 && n - ((p - (y * d)) / w) - y >= 0)
        {
            x = (p - (y * d)) / w;
            cout << x << " " << y << " " << n - x - y << "\n";
            return 0;
        }
        if(n - ((p - (y * d)) / w) - y < 0 || y > n || (p - (y * d)) < 0 || y > mx)
        {
            cout << "-1\n";
            return 0;
        }
        ++ y;
    }
    return 0;
}
```

这样这道题目就完成啦！！！

---

## 作者：123zbk (赞：1)

本题就是要找到 $ax+by=c$ 的一组 $x+y$ 的最小非负整数解。因为 $a>b$，所以让 $y$ 最小即可。

考虑从 $0$ 开始枚举 $y$，现在需要知道上界是什么。注意到如果 $y\ge w$，那么一定可以用 $d$ 个 $x$ 换 $w$ 个 $y$ 而让 $x+y$ 更小，也就是 $y$ 的取值就是 $y_{min}+kw$。所以只需在 $[0,w)$ 枚举 $y$ 即可，最后判断 $x+y$ 是否小于 $n$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,p,w,d;
signed main()
{
    scanf("%lld%lld%lld%lld",&n,&p,&w,&d);
    for(int y=0;y<w;y++)
    {
        int num=p-y*d;
        if(num%w!=0)
        {
            continue;
        }
        int x=num/w;
        if(x>=0&&x+y<=n)
        {
            printf("%lld %lld %lld",x,y,n-x-y);
            exit(0);
        }
    }
    puts("-1");
    return 0;
}
```

---

## 作者：过往梦魇之殇 (赞：1)

# 总算咕出一篇题解来了，真是不容易啊！

不多废话，直接切入正题：

这道题可以从方程求解上考虑：

已知方程 $x×w+y×d=p$

假设该方程存在一组解为:(花括号打不出来，$wtcl$）

$x0$

$y0=kw+v$  $(0<v<w)$

则原方程可以转化为：

$x0×w+(kw+v)×d=p$

$⇒x0×w+k×w×d+v×d=p$

$⇒(x0+k×d)×w+v×d=p$    

所以，必然存在一组解为：

$x=x0+k×d$

$y=v$

且因为$w>d$

则有 $x+y=x0+k×d+v<x0+k×w+v$ 一式

所以前者比后者更有可能成为答案。

便直接枚举所有的$v$的值即可！！！（思考完毕）



------------

以上为我的一些思路，接下来便到了快乐的代码展示啦！（$bzsc$）

个人码风，请勿介意。

```cpp
/*CF1244C The Football Season*/
#include<bits/stdc++.h>
#define int long long//我太喜欢了这个
#define re register
#define in inline
#define pi acos(-1.0)
#define inf 2147483640
using namespace std;
in int read()//快读
{
    int sum=0,negative=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')negative=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum*negative;
}
in void write(int X)//快输
{
    if(X<0)putchar('-'),X=-X;
    if(X>=10)write(X/10);
    putchar(X%10+'0');
}
int n,p,w,d;
void scan(){//输入
	n=read();
	p=read();
	w=read();
	d=read();
}
void print(int x,int i){//输出
	write(x);
	printf(" ");
	write(i);
	printf(" ");
	write(n-x-i);
	printf("\n");
}
void count(){//枚举
	for(re int i=0;i<w;i++){
		if((p-i*d)%w==0){
			int x=(p-i*d)/w;
			if(x>=0&&x+i<=n){
                print(x,i);
                return;
            }
		}
	}
	puts("-1");
}
signed main()//标准格式
{
	scan();
	count();
    return 0;
}
```

> 好了，最后祝愿各位$RP++$！！

---

## 作者：灵茶山艾府 (赞：1)

暴力可过，补一个扩展欧几里得的解法。

记 $g=gcd(a,b)$，则不定方程 $ax+by=g$ 有无穷组整数解，记其中一个解为 $(x_0,y_0)$。

对于 $ax+by=p$，若有 $g|p$，则解为 $(x_0*\frac{p}{g},y_0*\frac{p}{g})$，否则无解。

根据线性方程定理，不定方程 $ax+by=g$ 的所有解可表示为 $(x_0+k*\frac{b}{g},y_0-k*\frac{a}{g}), k\in Z$。

设 $a>b$，若不定方程有非负整数解 $(x,y)$，则 $y$ 越小 $x+y$ 也越小。

Python 代码如下：

```python
def exgcd(a, b):
    if b == 0:
        return a, 1, 0
    gcd, y, x = exgcd(b, a % b)
    y -= a // b * x
    return gcd, x, y


n, p, a, b = map(int, input().split())

gcd, x, y = exgcd(a, b)
if p % gcd != 0:
    print(-1)
    exit()
p //= gcd
a0 = a // gcd
b0 = b // gcd
x *= p
y *= p

min_y = (y % a0 + a0) % a0
x -= (min_y - y) // a0 * b0
y = min_y
if x < 0:
    print(-1)
    exit()
if x + y > n:
    print(-1)
    exit()
print(x, y, n - x - y)

---

## 作者：caidzh (赞：1)

注意到$d<w$，所以我们可以得到$y$越小，$x+y$越小，答案越可能满足条件，因此直接求出方程$wx+dy=p$中$y$的最小非负整数解即可，这可以使用$exgcd$完成

注意中间不取模会爆$long\ long$，所以处处要小心
```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
int n,p,d,w;
int exgcd(int &x,int &y,int a,int b){if(!b){x=1;y=0;return a;}int r=exgcd(x,y,b,a%b);int t=x;x=y;y=t-a/b*y;return r;}
void work(){
	int x,y;int t=exgcd(x,y,w,d);y=(((p/t)%(w/t))*(y%(w/t)))%(w/t);
	y=(y%(w/t)+w/t)%(w/t);x=(p-d*y)/w;
	if(x+y<=n&&x>=0&&y>=0&&p%t==0)cout<<x<<" "<<y<<" "<<n-x-y;else printf("-1");
}
signed main(){n=read();p=read();w=read();d=read();work();return 0;}
```


---

## 作者：Pelom (赞：1)

[更好的阅读体验](https://pelom.top/archives/54/)
# 题意

求解

$wx+dy=p$

$x+y \le n$

$x,y\ge 0$

的一组解$(x,y)$

**数据范围：**$2 \le n \le 10^{12},1 \le p \le 10^{17},1 \le d < w \le 10^5$

# 题解

因为$d<w$，显然在满足第一个式子的时候$x$越大（$y$越小）更能使第二个式子得到满足

证明：第一个式子可用**扩展欧几里得算法**求得特解$(x_0,y_0)$；而调整解的时候，$x_0$增加$\frac{d}{gcd(w,d)}$，$y_0$对应减少$\frac{w}{gcd(w,d)}$，因为$d<w$，所以$x_0+y_0$减少$\frac{w}{gcd(w,d)}-\frac{d}{gcd(w,d)}>0$，和变小，更优

不必使用**扩展欧几里得算法**求得特解，此时求得满足条件的最小$y$即可

将一式左右两边都除以$gcd(w,d)$，再考虑一式在模$w$意义下的情况$$dy \equiv p \ (\bmod w)$$

所以

$$y \equiv \frac{p}{d} \ (\bmod w)$$

即为最小的满足条件的$y$（此处使用**扩展欧几里得算法**求$d$关于$w$的逆元）

而此时

$$x=\frac{p-dy}{w}$$

再验证满足答案即可

**代码：**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define int long long
int n,p,w,d,x,y,g;
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
int exgcd(int a,int b,int &x,int &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    int gcd=exgcd(b,a%b,x,y);
    int t=x;
    x=y;
    y=t-a/b*y;
    return gcd;
}
inline int inv(int x,int p){
    int x0,y0;
    exgcd(x,p,x0,y0);
    return (x0%p+p)%p;
}
signed main(){
    scanf("%lld%lld%lld%lld",&n,&p,&w,&d);
    g=gcd(w,d);
    if(p%g!=0){
        puts("-1");
        return 0;
    }
    p/=g,w/=g,d/=g;
    y=p%w*inv(d,w)%w,x=(p-y*d)/w;
    if(x<0 || x+y>n){
        puts("-1");
        return 0;
    }
    printf("%lld %lld %lld",x,y,n-x-y);
    return 0;
}
```

---

## 作者：Li_Yichen (赞：0)

首先声明一点，本题解在洛谷上因为评测问题没有评测记录，但是在官网已经通过。这个题让我们求满足条件的不等式，那么我们显然可以使用拓展欧几里得求出 $x$ 和 $y$，那么可以用 $n - x - y$ 求出 $z$，但是此时会数据溢出。那么观察数据，发现 $y$ 的范围不大，那么我们可以直接枚举 $y$，如果遇到一组合法解直接输出即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,p,w,d;
signed main(){
	cin >> n >> p >> w >> d;
	for(int y=0;y<w;y++){
		if((p - d * y) % w == 0){
			int x = (p - d * y) / w;
            int z = n - x - y;
			if(x < 0 || z < 0) cout << -1;
            else cout << x << " " << y << " " << z;
			return 0;
		}
	}
	cout << -1;
    return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
因为要求 $x+y+z=n$，而 $z$ 并不在第一个式子中，所以考虑求解 $x$ 和 $y$，并且使 $x+y$ 最小来满足两个方程。那么怎么求解 $x$ 和 $y$，考虑直接暴力枚举 $y$，之后计算 $x$ 并判断合法即可。

那么为什么可以直接暴力，题目中 $d<w$，所以 $y<x$，只需要让 $y$ 尽可能小即可。同时观察到若 $y\ge w$，则可以用 $d$ 个 $x$ 换 $w$ 个 $y$ 这样就可使 $x+y$ 更小了。
### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std; 
ll n,p,w,d,xw,x;
int main(){
	cin>>n>>p>>w>>d;
	for(ll y=0;y<=w;y++){
		xw=p-d*y;
		if(xw%w==0){
			x=xw/w;
			if(n-x-y>=0 and x>=0){
				cout<<x<<' '<<y<<' '<<n-x-y<<'\n';
				return 0;
			}
		}
	}
	cout<<-1;
	return 0;
}

```

---

## 作者：lovely_codingcow (赞：0)

## 思路

我们看到题目，给定四个数 $n$、$p$、$w$、$d$，求解三元一次不定方程组：
$$
\left\{
\begin{array}{l}
x\cdot w+y\cdot d=p\\
x+y+z=n
\end{array}
\right.
$$
观察一下你就会发现 $z$ 的值是你可以随便指定的，因为他只对 $n$ 产生影响，而不对方程一产生任何贡献。于是我们忽略 $z$ 的取值。

由此我们就可以把方程组化简为一条二元一次不定方程：
$$
x\cdot w+y\cdot d=p
$$
由于 $w>d$，可以发现使 $y$ 最小就可以得到一组可能存在的解。因此考虑枚举 $y$。分析数据范围可以发现 $\frac{p}{n}$ 的范围刚好就是 $w$ 和 $d$ 的最大范围，因此我们可以证明，如果原方程组有非负正整数解，那么解中的 $y$ 必定在区间 $[0,\,w)$ 中。

故枚举 $y \in [0, \,w)$ 然后判断解是否合法即可，若找不到，则原方程必定无解。

## 代码

```cpp 
#include <iostream>

#define int long long

using namespace std;

int n, p, w, d;

signed main() {
    cin >> n >> p >> w >> d;
    for (int y = 0; y < w; y++) {
        if ((p - y * d) >= 0 && (p - y * d) % w == 0 && n - ((p - y * d) / w + y) >= 0) {
            int x = (p - y * d) / w;
            cout << x << " " << y << " " << n - (x + y);
            return 0;
        }
    }
    cout << -1;
}
```

---

## 作者：loser_seele (赞：0)

题解都没正常用 exgcd 过题的，来补一发。

首先 [模板题](https://www.luogu.com.cn/problem/P5656) 告诉我们怎么求出 exgcd 的一个特解，并求出其正整数解的上下界区间，这里不再详述。

观察到如果 $ y \geq w $，那么实际上可以用 $ d $ 个 $ x $ 换 $ w $ 个 $ y $，答案一定不会更劣。于是考虑按 $ y $ 递增的顺序在解的上下界区间内暴力枚举解，如果 $ y \geq w $ 直接退出即可。注意这个剪枝是必要的，否则可能的解非常多以至于会超时。

因为不同的 $ y $ 取值并不会很多，所以可以通过。时间复杂度不会算，大概比纯暴力好一点？

对于 exgcd 溢出的问题，使用 int128 即可。

[提交记录](https://codeforces.cc/contest/1244/submission/193937890)

---

## 作者：zplqwq (赞：0)

我们先简化下题意。

在已知 $a>b$ 的情况下求 $ax+by=c$ 的一组 $x+y$ 最小的非负整数解。

因此我们只要求 $y$ 最小即可。

我没学过扩展欧几里得，所以直接考虑暴力枚举。

我们先假设原方程有最小非负整数解，则可以推出，$0 \le y < a$ 直接枚举然后判断可不可行即可，记得开 `long long `

给出核心代码：

```cpp

for(int y=0;y<a;y++)
	{
		if(!((p-b*y)%a)) 
		{
			x=(p-b*y)/a;
			if(x+y>n or x<0) 
			{
				cout<<-1<<endl;
			} 
			else 
			{
				cout<<x<<" "<<y<<" "<<n-x-y<<endl;
			}
			return 0;
		}
	}
```

---

## 作者：xukuan (赞：0)

考虑到考场上的心态和数据问题，这题是这次比赛两道相对较难的题（CF）中较简单的一道

其实exgcd是不存在的，暴力也可以过

$1 \leq d < w \leq 10^5$

我们贪心的去考虑，肯定是让$w$对应的值尽可能大，那么我们从小到大穷举$d$去找解。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,p,d,w,x,y,z;

int main(){
	cin>>n>>p>>d>>w;
	while(y<d&&(p-w*y)%d) y++;
	if(y==d) return printf("-1")&0;
	x=(p-w*y)/d; z=n-x-y;
	if(x>=0&&z>=0) printf("%lld %lld %lld",x,y,z);
	else printf("-1");
	return 0;
}
```

---

## 作者：RicardoShips (赞：0)

先扔一个结论，如果方程有解，那么在$y \leq w$范围内一定有解

考虑证明，假设存在$y'=aw+b(a \ge 1,0 \leq b < w)$使得$xw+y'd=p$

即$xw+(aw+b)d=xw+awd+bd=(x+ad)w+bd$

观察这个式子左右两项，左边的系数和为$x+aw+b$，右边的系数为$x+ad+b$

因为$w>d$，所以在$y \leq w$范围内$x+y$一定最小，得证

在$[0,w)$范围内枚举$y$，计算是否存在合法的$x$即可

```cpp
#include<bits/stdc++.h>
using namespace std;
int main () {
	register long long n,p,w,d,z=0;
	scanf("%lld%lld%lld%lld",&n,&p,&w,&d);
	for(register long long i=0;i<w;++i)
	    if((p-i*d)%w==0) {
	    	register long long x=(p-i*d)/w;
	    	if(x>=0&&x+i<=n) printf("%lld %lld %lld\n",x,i,n-x-i);
	    	else puts("-1"); z=1; break ;
		}
	if(!z) puts("-1");
	return 0;
}
```


---

## 作者：SIGSEGV (赞：0)

观察题面可得可以用exgcd做，但是Pretest 5/7会爆long long...

然后我喜闻乐见地用Py3水了一发，但是由于系数没有化简$\color{red}{FST}$了......
```python
import sys
x = 0
y = 0
def exgcd(a,b):
    global x,y
    if b == 0:
        x = 1
        y = 0
        return a
    ret = exgcd(b,a % b)
    t = x
    x = y
    y = t - (a // b) * y
    return ret
 
n,p,w,d = map(int,input().split())
ret = exgcd(w,d)
if p % ret: #方程无解情况
    print(-1)
else:
    x *= p // ret 
    y *= p // ret
    d //= ret #系数化简......
    w //= ret
    # print(x,y)
    if x < 0:
        tmp = (-x + d - 1) // d #x加上/减去化简后的d，y减去/加上化简后的w，方程仍然成立
        x += tmp * d
        y -= tmp * w
    elif y < 0:
        tmp = (-y + w - 1) // w
        x -= tmp * d
        y += tmp * w
    if x >= 0 and y >= 0:
        if w > d: #这是比赛时的代码改的，当时没有仔细读题
            tmp = y // w
            y %= w
            x += tmp * d
        else:
            tmp = x // d
            x %= d
            y += tmp * w
    if x + y > n or x < 0 or y < 0:
        print(-1)
    else:
        print(x,y,n - x - y)
```

---

## 作者：Llf0703 (赞：0)

[更好的阅读体验](https://llf0703.com/p/cf-1244.html#cthefootballseason)

## 题意

求解方程

$$w\times x+d\times y=p$$

要求 $x+y\le n$ 。

$1\le n\le 10^{12},0\le p\le 10^{17},1\le d < w\le 10^5$ 。

## 题解

一眼exgcd裸题，直接解出 $x,y$，因为 $w > d$ ，所以让 $y$ 尽可能小肯定最优。

WA了。后来发现 $p\le 10^{17}$ ，直接 $\times \frac{p}{\gcd (w,d)}$ 显然会爆。

那总不可能写高精吧，去看status发现无数老哥交 `Pypy3` ，于是我就开始改python，不过毕竟之前没用py写过oi题，中途因为 `//=` 写成 `/=` 等原因一共WA了7发，最后A的时候就只剩500多分了。

```python
n,p,w,d=[int(i) for i in input().split(" ")]

def exgcd(a,b):
    if b==0:
        return (1,0)
    tx,ty=exgcd(b,a%b)
    return (ty,tx-a//b*ty)

def gcd(a,b):
    if b==0:
        return a
    return gcd(b,a%b)

x,y=exgcd(w,d)
g=gcd(w,d)
if p%g!=0:
    print("-1")
    exit()
p//=g
x*=p
y*=p
w//=g
d//=g
if x<0: #把 x 变成非负
    tmp=(-x+d-1)//d
    x+=tmp*d
    y-=tmp*w
if y<0: #把 y 变成非负
    tmp=(-y+w-1)//w;
    y+=tmp*w
    x-=tmp*d
if x<0:
    print("-1")
    exit()
if y>=w: #让 y 尽可能小
    tmp=y//w
    y-=tmp*w;
    x+=tmp*d;
if x+y>n:
    print("-1")
    exit()
print(int(x),int(y),int(n-x-y))
```

赛后看其他人的写法，发现其实并不需要用 exgcd 来解方程。$y$ 的最小值就是 $\dfrac{p}{d}\mod w$ ，然后 $x=\dfrac{p-d\times y}{w}$ 。

不过还是需要 exgcd 来求个逆元。

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

inline ll read()
{
    char ch=getchar(); ll f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

ll n,p,w,d;

ll gcd(ll x,ll y) { return y ? gcd(y,x%y) : x; }

ll exgcd(ll l,ll r,ll &x,ll &y)
{
    if (!r)
    {
        x=1; y=0;
        return l;
    }
    ll ans=exgcd(r,l%r,y,x);
    y-=l/r*x;
    return ans;
}

inline ll inv(ll a,ll ha)
{
    ll x=0,y=0;
    exgcd(a,ha,x,y);
    return (x+ha)%ha;
}

signed main()
{
    n=read(); p=read(); w=read(); d=read();
    ll g=gcd(w,d);
    if (p%g) return 0&puts("-1"); //无解
    p/=g; w/=g; d/=g; //除了gcd方程等价
    ll y=p%w*inv(d,w)%w,x=(p-y*d)/w; //直接算出 x,y
    if (x<0 || x+y>n) return 0&puts("-1"); //无解
    return !printf("%lld %lld %lld",x,y,n-x-y);
}
```

---

