# [ABC191D] Circle Lattice Points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc191/tasks/abc191_d

$ 2 $ 次元平面上に中心 $ (X,\ Y) $ 、半径 $ R $ の円があります。  
 この円の内部または周上にある格子点 ($ x,\ y $ 座標がともに整数である点) の個数を求めてください。

## 说明/提示

### 制約

- $ |X|\ \le\ 10^5 $
- $ |Y|\ \le\ 10^5 $
- $ 0\ \lt\ R\ \le\ 10^5 $
- $ X,\ Y,\ R $ は高々小数第 $ 4 $ 位まで与えられる

### Sample Explanation 1

以下のような円になります。赤く印の付いた点が、この円の内部または周上にある格子点です。 !\[グラフ\](https://img.atcoder.jp/ghi/4f37b99cfbdbb337043b16d8ce64571c.png)

### Sample Explanation 2

$ X,\ Y,\ R $ には小数点が含まれないかもしれません。 円周上の格子点も数える対象に含むことに注意してください。

## 样例 #1

### 输入

```
0.2 0.8 1.1```

### 输出

```
3```

## 样例 #2

### 输入

```
100 100 1```

### 输出

```
5```

## 样例 #3

### 输入

```
42782.4720 31949.0192 99999.99```

### 输出

```
31415920098```

# 题解

## 作者：Tang_poetry_syndrome (赞：4)

## [ABC191D] Circle Lattice Points 

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc191_d) [Atcoder 题面](https://atcoder.jp/contests/abc191/tasks/abc191_d)

### 题目大意

给出一个半径为 $R$ 的圆，圆心在 $(X,Y)$。求在这个圆内（包括圆边）坐标皆为整数的格点数。

### 思路

楼上神犇的题解没看懂，又乱搞了一种简单写法。  
同样枚举 $y$ 坐标，但是采用数学的方法求左右边界。  
首先我们先构建一个圆，经过下列手推可以发现，$y$ 轴到圆边距离垂直，考虑使用勾股定理求解。  
![此为手推例图](https://cdn.luogu.com.cn/upload/image_hosting/9no9jdwr.png)  
我们设当前 $y$ 坐标为 $i$，左端点为 $Q$，右端点为 $P$，$dis$ 为 $x$ 到左右圆边的距离（即 $\frac{QP}{2}$）($QP$ 为线段）。  
$\because PQ \perp Oi \therefore dis^2+(y-i)^2=r^2$，即 $dis=\sqrt{r^2-(y-i)^2}$。  
容易得出 $Q$ 为 $(\lceil x-dis \rceil,i)$，$P$ 为 $(\lfloor x+dis \rfloor,i)$。$y$ 坐标为 $i$ 时的整格点数即为 $P-R+1$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,j,k) for(register ll i=j;i<=k;++i)
#define g(i,j,k) for(register ll i=j;i>=k;--i)
#define pii pair<int,int>
#define pb push_back
const int N=1e5+10,Mod=998244353;
long double x,y,r,dist;
ll ans;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>x>>y>>r;
    r+=1e-14;
    f(i,ceil(y-r),floor(y+r))
    	dist=sqrt(r*r-(y-i)*(y-i)),ans+=(int)floor(x+dist)-(int)ceil(x-dist)+1; 
	cout<<ans;
	return 0;
}
```

[提交记录](https://atcoder.jp/contests/abc191/submissions/46727281)

---

## 作者：_Life_ (赞：2)

### 题意

有一个圆 $(x-X)^2+(y-Y)^2=R^2$，求圆内或圆上的整点个数。

整点指 $x,y$ 坐标均为整数的点。

$|X|,|Y|,R\leq 10^5$，输入的 $X,Y,R$ 小数点后最多有四位。

### 题解

绝世傻逼卡精度题。

思路是显然的，枚举 $y$ 坐标，求出左右边界统计答案即可。

但对于本题，写出一份马马虎虎的代码很简单，写出一份足以通过毒瘤数据的代码却路途坎坷。

避免浮点误差的最好方法就是不用浮点数。观察到输入数据小数点后最多有四位，因此可以将输入数据放大 $10000$ 倍后用 `long long` 存储，规避浮点误差。

`sqrt(),ceil(),floor()` 之类的函数也可以手写代替。可以用二分求出左右边界代替 `sqrt()`，手写 `if` 代替 `ceil(),floor()`。

实现细节见代码。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
//#define mod 1000000007
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
using namespace std;
typedef pair<int,int> pii;
void setIn(string s){freopen(s.c_str(),"r",stdin);}
void setOu(string s){freopen(s.c_str(),"w",stdout);}
void setIO(string s){setIn(s+".in"),setOu(s+".out");}
template<class T>void chkmax(T &a,T b){a=max(a,b);}
template<class T>void chkmin(T &a,T b){a=min(a,b);}
template<class T>T read(T &x)
{
	x=0;T f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*=f;
}
template<class T,class ...L>void read(T &x,L &...l){read(x),read(l...);}
template<class T>void write(T x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);}putchar(x%10+'0');
}
template<class T>void write(T x,char c){write(x),putchar(c);}
int x,y,r,ans;
double t;
int getr(int i,int R)
{
	int l=x,r=x+R,ans;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if((mid-x)*(mid-x)+(i-y)*(i-y)<=R*R)
			ans=mid,l=mid+1;
		else
			r=mid-1;
	}
	return ans;
}
int getl(int i,int R)
{
	int l=x-R,r=x,ans;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if((mid-x)*(mid-x)+(i-y)*(i-y)<=R*R)
			ans=mid,r=mid-1;
		else
			l=mid+1;
	}
	return ans;
}
signed main()
{
	scanf("%lf",&t);x=round(t*10000);
	scanf("%lf",&t);y=round(t*10000);
	scanf("%lf",&t);r=round(t*10000);
	for(int i=-200000*10000;i<=200000*10000;i+=10000)
		if(y-r<=i&&i<=y+r)
		{
			int a=getr(i,r);
			int b=getl(i,r);
			//相当于手写 a=floor(a/10000.0);
			if(a%10000==0)a/=10000;
			else if(a>=0)a/=10000;
			else a=a/10000-1;
			//相当于手写 b=ceil(b/10000.0);
			if(b%10000==0)b/=10000;
			else if(b>=0)b=b/10000+1;
			else b/=10000;
			ans+=max(0ll,a-b+1);
		}
	write(ans);
}
```

---

## 作者：11400F (赞：1)

## ABC191D Circle Lattice Points 题解

### 题目大意：

给定一个圆的圆心坐标和半径，求有多少个 $x$ 坐标和 $y$ 坐标均为整数的点在圆上或圆内。

### 思路：

这道题的思路其实非常的好想。设圆心坐标为 $(a, b)$，因为 $|Y| \le 10^5$，所以我们可以枚举整数 $y$ 坐标。假设当前枚举到的纵坐标为 $c$，我们选定一个和圆心横坐标相同的点 $(a, c)$，根据勾股定理，我们就可以得出纵坐标为 $c$ 时对应的 $x$ 坐标的范围。我们再给 $x$ 坐标的范围取整，会得到一个整数范围 $[l,r]$。最后纵坐标为 $c$ 的整数点的个数就是 $r-l+1$。

并且如果纵坐标为 $c$ 时没有整数点在圆上或圆内，那么 $l$ 会比 $r$ 大 $1$，最后算出来的答案还是 $0$。

如下图：

![cirlce-img](https://s21.ax1x.com/2024/12/05/pAozKUI.png)

整点的横坐标范围只需要给 $L$ 点横坐标向上取整，$R$ 点横坐标向下取整即可。

然而还没完，**这道题是一道至尊无敌特大卡精度题**！

因为 double 型的浮点误差，所以这里必须改用 long double。并且还要设置一个极小值 $eps = 1\times 10^{-14}$ 加到半径上，来保证圆上的点能完全的被算到。

（P.S. 亲测 1e14 可过，1e13及以上会 WA 3 或 WA 4，1e15 及以下会 WA 1。~~出题人专门手写了几个 corner case 就卡你精度。~~）

代码很短，但请注意细节：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long double db;
db X, Y, R, eps = 1e-14;
typedef long long ll;
int main(){
    cin>>X>>Y>>R;
    R += eps;
    int ydown = ceil(Y-R), yup = floor(Y+R);
    ll ans = 0;
    for(int y=ydown;y<=yup;y++){
        db ylen = y-Y;
        db xlen = sqrt(R*R-ylen*ylen);
        int rpoint = floor(X+xlen);
        int lpoint = ceil(X-xlen);
        ans += (rpoint - lpoint + 1);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Expert_Dream (赞：1)

恭喜你水了一道蓝题。

首先，由于是整点，我们不妨枚举一个维度。

我这里枚举 $Y$ 坐标。

但是此时要计算有多少个不同 $X$ 坐标点。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jketru8e.png)

由于我们枚举，知道绿线长度，然后蓝线即为半径，那么可以用小学一年级学的勾股定理来求出橙色线的距离，然后我们将他向下取整就是这右边的点数。

这样通过枚举，就做完了。

但是由于他很恶心，卡你精度，所以你要把 $r$ 加上一个很小很小的偏移量，因为有些恰好压着原边的点会被卡掉。

[link](https://atcoder.jp/contests/abc191/submissions/52279330)。

---

## 作者：dvsfanjo (赞：0)

# 题解：AT_abc191_d [ABC191D] Circle Lattice Points

说句闲话，精度卡的真毒瘤。

## 分析

对于一个圆心在 $(x_0, y_0)$ 且半径为 $r$ 的圆，它的解析式为：

$(x-x_0)^2+(y-y_0)^2=r^2$

枚举整数 $x$ 并判断对应两个 $y$ 值之间有几个整数即可。

$y_1=\sqrt{r^2-(x-x_0)^2}+y_0$

$y_2=2\times r-y_0$

之间整数的个数即为：

$\lfloor y_1 \rfloor - \lfloor y_2 \rfloor$

如果 $y_2$ 是整数那么个数还要加一。

注意：精度要求太毒瘤了，看大佬们的做法是一开始给 $r$ 加上一个极小的值，而且要用精度更高的浮点数类型。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
long double n, m, r, y_1, y_2;
long long ans;
//可以得到解析式：(x - n)^2 + (y - m)^2=r^2
//so y = sqrt((r + n - x)(r + x - n)) + m
int main()
{
	cin >> n >> m >> r;
	r += 1e-14;
	for (int x = ceil(n - r); x <= floor(n + r); x++)
	{
		y_1 = sqrt(r * r - (x * 1.0 - n) * (x * 1.0 - n)) + m;
		y_2 = m + m - y_1;
		ans += floor(y_1) - floor(y_2);
		if (int(y_2) == y_2)
          		ans++;
	}
	cout << ans << endl;
	return 0;
}
```

太毒瘤了，看了题解好多次才调出来。

---

## 作者：Empty_Dream (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/AT_abc191_d)

## 分析
直接上圆的方程 $x^2+y^2=r^2$，这里设原点为 $x_0,y_0$，那么方程变为 $(x-x_0)^2+(y-y_0)^2=r^2$。

我们可以考虑只遍历所有满足条件的 $x$ 然后求出满足条件 $y$ 的个数。稍微变形一下公式 $y=\sqrt{r^2-(x-x_0)^2}+y_0$，这里求的是较上面的那个在圆上的 $y$ 值，那么在下面的就是 $y'=2y_0-y$（圆的对称性）。统计答案类似前缀和，等于 $\lfloor y \rfloor-\lfloor y' \rfloor$，这里要特判一下 $y'$ 是否为整数，如果是还要加 $1$。

注意：这题卡精度，可以给 $r$ 加上一个极小值解决（开根号可能会把小数点后几位抹除）。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;

int ans;
double x, y, r;

signed main(){
	cin >> x >> y >> r;
	r += 1e-14;//卡精度
	for (int i = ceil(x - r); i <= floor(x + r); i++){
		double tmp = sqrt(r * r - (i * 1.0 - x) * (i * 1.0 - x)) + y;//y
		double tmp1 = y + y - tmp;//y'
		if (floor(tmp1) == tmp1) ans++;//特判y'是否为整数
		ans += floor(tmp) - floor(tmp1);//统计答案
	}
	cout << ans;
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

很久之前做过的卡精度题。

考虑枚举整点的竖坐标，然后对于一个竖坐标我们找到圆内最上方的整点和圆内最下方的整点，然后就可以求中间有多少了。

然后求这两个点可以考虑把这个竖坐标下圆上的两个点利用圆方程算出来，然后取整就行。

注意这题卡精度，所以要用一些玄学办法，同校神犇的做法是把半径加上一个很小的数字。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
//const LL N;
//const LL M;
//const LL mod;
const LF eps=1e-14;
//const LL P;
LF x,y,r;
LL ans;
int main()
{
	scanf("%Lf%Lf%Lf",&x,&y,&r);
	r+=eps;
	for (int i=ceil(y-r);i<=floor(y+r);i++)
	{
		LF t=sqrtl(r*r-(y-i)*(y-i));
		LF l=x-t,r=x+t;
		if (ceil(l)<=floor(r))ans+=floor(r)-ceil(l)+1;
	}
	printf("%lld",ans);
	return 0;
}
//RP++
```

---

