# Intersecting Lines

## 题目描述

以$(x_1,y_1),(x_2,y_2),(x_3,y_3),(x_4,y_4)$的形式给出两条直线，问过$(x_1,y_1),(x_2,y_2)$的直线和过$(x_3,y_3),(x_4,y_4)$的直线的位置关系。其中$(x_1,y_1)\ne(x_2,y_2),(x_3,y_3)\ne(x_4,y_4)$。

## 样例 #1

### 输入

```
5
0 0 4 4 0 4 4 0
5 0 7 6 1 0 2 3
5 0 7 6 3 -6 4 -3
2 0 2 27 1 5 18 5
0 3 4 0 1 2 2 5```

### 输出

```
INTERSECTING LINES OUTPUT
POINT 2.00 2.00
NONE
LINE
POINT 2.00 5.00
POINT 1.07 2.20
END OF OUTPUT```

# 题解

## 作者：scp020 (赞：3)

# UVA378 Intersecting Lines 题解

怎么这么多点斜式邪教啊。

## 解法

在计算几何中，我们应该尽可能地避免使用浮点数的计算，尽可能地使用向量计算。

本篇题解默认读者具有向量基础。

为了方便讲解，我们将输入的四个点分别记作 $A,B,C,D$。

考虑两条直线 $AB,CD$ 何时平行。根据向量叉乘的几何意义，如果 $\overrightarrow{AB} \times \overrightarrow{CD}=0$，则两直线平行。

直线重合是在直线平行的基础上，如果 $C,D$ 中任一点在直线 $AB$ 上，则两直线平行。即 $\overrightarrow{AB} \times \overrightarrow{AC}=0$（这里取点  $C$）。

剩下的情况就是直线相交了。如图，设两直线交点为 $E$。

![图](https://cdn.luogu.com.cn/upload/image_hosting/nebsz3hn.png)

根据小学四年级（雾）学的燕尾模型，$\dfrac{AE}{EB}=\dfrac{S_{\Delta ADC}}{S_{\Delta BDC}}$，所以 $\dfrac{AE}{AB}=\dfrac{S_{\Delta ADC}}{S_{\Delta ADC}+S_{\Delta BDC}}$，三角形面积可以用叉积轻松求出。

所以两直线交点为 $(X_A+(X_B-X_A) \times \dfrac{AE}{AB},Y_A+(Y_B-Y_A) \times \dfrac{AE}{AB})$。

最后提一句，这道题是早期 UVA 题，没有自动忽略文末换行，这题需要有文末换行。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
	/**
	 * 省略了一部分
	*/
	inline void read(int &x,char c=Getchar())
	{
		bool f=c!=45;
		x=0;
		while(c<48 or c>57) c=Getchar(),f&=c!=45;
		while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
		x=f?x:-x;
	}
	inline void write(int x)
	{
		if(x<0) Putchar(45),x=-x;
		if(x>=10) write(x/10),x%=10;
		Putchar(x^48);
	}
	inline void read(__int128 &x,char c=Getchar())
	{
		bool f=c!=45;
		x=0;
		while(c<48 or c>57) c=Getchar(),f&=c!=45;
		while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
		x=f?x:-x;
	}
	inline void write(__int128 x)
	{
		if(x<0) Putchar(45),x=-x;
		if(x>=10) write(x/10),x%=10;
		Putchar(x^48);
	}
	inline bool inrange(const char &ch)
	{
		if(ch>=33 && ch<=126) return true;
		return false;
	}
	inline void read(std::string &st,char c=Getchar())
	{
		st.clear();
		while(!inrange(c)) c=Getchar();
		while(inrange(c)) st+=c,c=Getchar();
	}
	inline void write(std::string st)
	{
		for(int i=0;i<st.size();i++) Putchar(st[i]);
	}
	inline void read(char &ch)
	{
		ch=Getchar();
		while(!inrange(ch)) ch=Getchar();
	}
	inline void write(const char &ch)
	{
		Putchar(ch);
	}
	inline void write(double x,int fix=2)
	{
		x+=x>0?my_round[fix+1]:-my_round[fix+1],write((__int128)x),x=x>0?x:-x,x-=(__int128)x;
		if(fix)
		{
			Putchar(46);
			while(fix--) x*=10,Putchar(((int)x)^48),x-=(int)x;
		}
	}
	class fastin
	{
	public:
		template<typename T>
		inline fastin &operator>>(T &x)
		{
			read(x);
			return *this;
		}
	};
	class fastout
	{
	public:
		template<typename T>
		inline fastout &operator<<(T x)
		{
			write(x);
			return *this;
		}
	};
	fastin in;
	fastout out;
};
using namespace fast_IO;
int n;
struct point
{
	int x,y;
	point()
	{
		x=y=0;
	}
	point(int x,int y)
	{
		this->x=x,this->y=y;
	}
	inline point operator-(const point &rhs) const
	{
		return point(x-rhs.x,y-rhs.y);
	}
	inline int operator*(const point &rhs)
	{
		return x*rhs.y-y*rhs.x;
	}
};
inline int sgn(int x)
{
	return x==0?0:(x>0?1:-1);
}
struct seg
{
	point s,t;
};
seg a,b;
inline void calc()
{
	double ix,iy,rat;
	rat=(b.t-a.s)*(b.s-a.s)*1.0/((b.t-a.s)*(b.s-a.s)-(b.t-a.t)*(b.s-a.t));
	ix=a.s.x*1.0+(a.t.x-a.s.x)*rat,iy=a.s.y*1.0+(a.t.y-a.s.y)*rat;
	out<<"POINT "<<ix<<' '<<iy<<'\n';
}
int main()
{
	in>>n,out<<"INTERSECTING LINES OUTPUT\n";
	for(int i=1;i<=n;i++)
	{
		in>>a.s.x>>a.s.y>>a.t.x>>a.t.y>>b.s.x>>b.s.y>>b.t.x>>b.t.y;
		if((a.t-a.s)*(b.t-b.s)==0)
		{
			if((a.t-a.s)*(b.s-a.s)==0) out<<"LINE\n";
			else out<<"NONE\n";
		}else calc();
	}
	out<<"END OF OUTPUT\n";
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

---

## 作者：wbh20090611 (赞：1)

### 大概思路：

1. 算出两条直线一般方程
2. 对三种情况进行判断

### 第一步：算出两条直线一般方程

由直线的两点式方程得：  
$\frac{y-y_2}{y_1-y_2} = \frac{x-x_2}{x_1-x_2}$  
$\therefore (x_1 - x_2)y + (y_1-y_2)x+y_1x_2-x_1y_2 = 0$

因此：

```c++
A1 = Y2 - Y1;
B1 = X1 - X2;
C1 = -Y2 * X1 + Y1 * X2;
A2 = Y4 - Y3;
B2 = X3 - X4;
C2 = -Y4 * X3 + Y3 * X4;
```

就求出了两条直线的方程

### 第二步：根据公式逐一判断

#### 1. 重合

当且仅当 $D_3, D_4$ 都在 $l_1$ 上的时候两直线重合。

#### 2. 平行

公式：当 $A_2B_1=A_1B_2$ 成立的时候两直线平行。

#### 3. 相交

两直线交点公式 $(\frac{C_2 B_1 - C_1 B_2}{A_1 B_2 - A_2 B_1}, \frac{C_1 A_2 - C_2 A_1}{A_1 B_2 - A_2 B_1})$

### 最后，附上代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double X1, X2, Y1, Y2, X3, X4, Y3, Y4, A1, A2, B1, B2, C1, C2;
int main()
{
	printf("INTERSECTING LINES OUTPUT\n");
	scanf("%d", &n);
	while (n--)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2, &X3, &Y3, &X4, &Y4);
		A1 = Y2 - Y1;
		B1 = X1 - X2;
		C1 = -Y2 * X1 + Y1 * X2;
		A2 = Y4 - Y3;
		B2 = X3 - X4;
		C2 = -Y4 * X3 + Y3 * X4;
		if (A1 * X3 + B1 * Y3 + C1 == 0 && A1 * X4 + B1 * Y4 + C1 == 0)
			printf("LINE\n");
		else if (A1 * B2 == A2 * B1 && (B1 * C2 != B2 * C1 || A1 * C2 != A2 * C1))
			printf("NONE\n");
		else
			printf("POINT %.2lf %.2lf\n", (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1), (-C2 * A1 + C1 * A2) / (A1 * B2 - A2 * B1));
	}
	printf("END OF OUTPUT\n");
	return 0;
}
```

不会真的有人交了吧，会 WA 的（因为UVA逆天评测）

**注意**：这道题目不可以把 `printf("INTERSECTING LINES OUTPUT\n")` 写在 `cin >> t` 前面。

---

## 作者：FurippuWRY (赞：1)

非常好计算几何题。

本题前置知识：一次函数、直线方程等。

设两直线的解析式分别为 $f(x)=y=k_1x+b_1,g(x)=y=k_2x+b_2$，$k_1$ 和 $k_2$ 为斜率，$b_1$ 和 $b_2$ 为截距。

## 相交

若两直线相交，则它们的斜率肯定不相等，此时通过公式 $k=\dfrac{y_1-y_2}{x_1-x_2}$ 可以求出两直线的斜率，$b=y-kx$，解方程求出 $k$ 与 $b$。因为两直线有交点，所以此时 $f(x)=g(x)$，则有：

$$\begin{aligned}k_1x+b_1&=k_2x+b_2\\k_1x-k_2x&=b_2-b_1\\x(k_1-k_2)&=b_2-b_1\\x&=\dfrac{b_2-b_1}{k_1-k_2}\end{aligned}$$

求出 $x$ 之后，代入随便一个函数就能求出 $y$。

## 重合

若两直线重合，则它们的斜率与截距都相等，用上文两个公式求出后判定是否相等即可。

## 平行不重合

此时两直线的斜率相等，但截距不等。

## 特判

上文我们讨论的都是 $x_1 \ne x_2 \land x_3 \ne x_4$ 的情况，但还存在 $x_1=x_2 \land x_3 \ne x_4$ 等情况，此时如果无脑套公式，输出就会爆 `nan`，原因是 $x_1-x_2=0$，$k=\dfrac{y_1-y_2}{x_1-x_2}=\dfrac{y_1-y_2}{0}$，我们就要对于不同的 $x$ 的值，进行分讨。

### $x_1=x_2 \land x_3 \ne x_4$

此时两直线的斜率一定不等，存在交点 $(x_1,g(x_1))$。先求出 $k_2$ 和 $b_2$，然后求出 $g(x_1)$ 就行。

### $x_1 \ne x_2 \land x_3 = x_4$

同理，交点为 $(x_3,f(x_3))$。

### $x_1 = x_2 \land x_3 = x_4$

这种情况下，两直线的斜率都是无限大（相等），只存在平行和重合的两种情况，若 $x_1=x_3$，则为重合，否则为平行。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

double n, x[10], y[10];
double k1, k2, b1, b2, sol, solx, soly;

int main() {
	
	cin >> n;
	puts("INTERSECTING LINES OUTPUT");
	while (n--){
		for (ll i = 1; i <= 4; ++i) {
			cin >> x[i] >> y[i];
		}
		if (x[1] == x[2] && x[3] != x[4]) {
			k2 = (y[3] - y[4]) / (x[3] - x[4]);
			b2 = y[3] - x[3] * k2;
			solx = x[1];
			soly = solx * k2 + b2;
			printf("POINT %.2lf %.2lf\n", solx, soly);
		}
		else if (x[1] != x[2] && x[3] == x[4]){
			k1 = (y[1] - y[2]) / (x[1] - x[2]);
			b1 = y[1] - x[1] * k1;
			solx = x[3];
			soly = solx * k1 + b1;
			printf("POINT %.2lf %.2lf\n", solx, soly);
		}
		else if (x[1] == x[2] && x[3] == x[4]) {
			if (x[1] == x[3]) puts("LINE");
			else puts("NONE");
		}	
		else {
			k1 = (y[1] - y[2]) / (x[1] - x[2]);
			k2 = (y[3] - y[4]) / (x[3] - x[4]);
			b1 = y[1] - x[1] * k1;
			b2 = y[3] - x[3] * k2;
			if (b1 == b2 && k1 == k2) puts("LINE");
			else if (b1 != b2 && k1 == k2) puts("NONE");
			else {
				solx = (b1 - b2) / (k2 - k1);
				soly = solx * k1 + b1;
				printf("POINT %.2lf %.2lf\n", solx, soly);
			}
		}	
	}
	puts("END OF OUTPUT");
	
	return 0;
}
```

---

## 作者：Jason0211 (赞：1)

# 注：
本题解使用的全部是一次函数知识。

# 前置知识
直接看这个吧：[一道很水的紫题](https://www.luogu.com.cn/blog/Jason0211/solution-uva191)。

# 解法
先特判直线两点横坐标相等的情况，此时无法计算出斜率的值。

然后，计算出两直线的解析式，直接联立求解即可。

然后就做完了。具体细节见代码：

```cpp
#include<cstdio>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	printf("INTERSECTING LINES OUTPUT\n");
	while(n--)
	{
		double x1,y1,x2,y2,x3,y3,x4,y4,k1,k2,b1,b2,judge=1e-13;//double可精确到小数点后15位
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
		if(x1==x2&&x3!=x4)
		{
			k2=(y3-y4)/(x3-x4),b2=y3-k2*x3;
			double x=x1,y=k2*x+b2;
			printf("POINT %.2lf %.2lf\n",x,y);
		}
		else if(x1!=x2&&x3==x4)
		{
			k1=(y1-y2)/(x1-x2),b1=y1-k1*x1;
			double x=x3,y=k1*x+b1;
			printf("POINT %.2lf %.2lf\n",x,y);
		}
		else if(x1==x2&&x3==x4)
		{
			if(x1==x3) printf("LINE\n");
			else printf("NONE\n");
		}//先进行三次特判
		else
		{
			k1=(y1-y2)/(x1-x2),b1=y1-k1*x1;
			k2=(y3-y4)/(x3-x4),b2=y3-k2*x3;
			if(b1-b2<=judge&&b1-b2>=-judge&&k1-k2<=judge&&k1-k2>=-judge) printf("LINE\n");
			else if(k1-k2<=judge&&k1-k2>=-judge) printf("NONE\n");
			else{
				double x=(b1-b2)/(k2-k1),y=(b2*k1-b1*k2)/(k1-k2);//联立求解，推导过程较为简单，这里就不证了
				printf("POINT %.2lf %.2lf\n",x,y);
			}
		}
	}
	printf("END OF OUTPUT\n");
	return 0;
}
```

---

## 作者：mrclr (赞：1)

[嘟嘟嘟](https://www.luogu.org/problemnew/show/UVA378)
翻译：直线求交。

本人第一道计算几何题。已经体会到了计算几何的恶心之处……

首先当然有联立解析式的做法，然而在咱竞赛中一般都用向量的求法。

然后刚开始我就因为怎么存向量和直线的事情折腾了好半天：刚开始开了一个向量类和一个直线类，但是发现这样封装过度了，就把直线类删了。但是单纯的开一个向量类又不够，就又开了一个结构体存单点。反正最后一个比较优美的写法就是开一个向量类和单点，然后单点的变量名都是单个大写字母，向量的变量名都是两个大写字母。比如两个点$A, B$，那么$\overrightarrow{AB}$就叫$AB$。

[说正事儿]

直线求交比线段求交要简单点，只用判断是否平行或共线即可。

对于两条直线$AB, CD$。平行的条件是$\overrightarrow{AB} \times \overrightarrow{CD} = 0$。在这个前提下再判断共线：$\overrightarrow{AB} \times \overrightarrow{AC} = 0$。如果这俩都不是，那么一定有交点。
下面具体讲讲怎么求交点。

上图
![](https://img2018.cnblogs.com/blog/1284378/201811/1284378-20181117133306845-1799302394.png)

因为$A$点坐标已知，所以我们可以通过求出$\overrightarrow{AB}$以及$AO$和$AB$的比来得到$O$点坐标。
而$\frac{AO}{AB} = \frac{S_{\Delta ACD}}{S_{\Delta ACD} + S_{\Delta BCD}}$，且$S_{\Delta ACD} = \overrightarrow{AC} \times \overrightarrow{AD}$，$S_{\Delta BCD} = \overrightarrow{BC} \times \overrightarrow{BD}$。那么问题就迎刃而解了：$O = A + \frac{\overrightarrow{AB} \times S_{\Delta ACD}}{S_{\Delta ACD} + S_{\Delta BCD}}$。

代码还是相当清真的
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define rg register
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
//const int maxn = ;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n;
struct Vec
{
  int x, y;
  friend Vec mul(const Vec& A, const int& k)
  {
    return (Vec){A.x * k, A.y * k};
  }
  int operator * (const Vec& oth)const
  {
    return x * oth.y - oth.x * y;
  }
  int dot (const Vec& oth)const
  {
    return x * oth.x + y * oth.y;
  }
};
struct Point
{
  int x, y;
  Vec operator - (const Point& oth)const
  {
    return (Vec){x - oth.x, y - oth.y};
  }
}A, B, C, D;

void solve()
{
  Vec AB = B - A, CD = D - C;
  if(AB * CD == 0)
    {
      Vec AC = C - A;
      if(AB * AC == 0) puts("LINE");
      else puts("NONE");
      return;
    }
  Vec AC = C - A, AD = D - A, BD = D - B, BC = C - B;
  int s1 = AC * AD, s2 = BD * BC;
  Vec _AB = mul(AB, s1);
  db x = (db)_AB.x / (db)(s1 + s2), y = (db)_AB.y / (db)(s1 + s2);
  printf("POINT %.2lf %.2lf\n", (db)A.x + x, (db)A.y + y);
}

int main()
{
  puts("INTERSECTING LINES OUTPUT");
  n = read();
  for(int i = 1; i <= n; ++i)
    {
      A.x = read(); A.y = read(); B.x = read(); B.y = read();
      C.x = read(); C.y = read(); D.x = read(); D.y = read();
      solve();
    }
  puts("END OF OUTPUT");
  return 0;
}
```

---

## 作者：0x00AC3375 (赞：0)

### 1. 题意
- 输入若干组坐标 $(x_1,y_1),(x_2,y_2),(x_3,y_3),(x_4,y_4)$，表示经过点 $(x_1,y_1),(x_2,y_2)$ 的直线和经过 $(x_3,y_3),(x_4,y_4)$ 的直线；
- 坐标值全部为绝对值不超过 $1000$ 的整数；
- 针对每一组数据，判断两条直线的位置关系（相交/重合/平行）。如果相交，输出交点坐标。

### 2. 分析
一般地，直线的一般方程为 $Ax+By+C=0$，其中 $A,B$ 不能同时等于 $0$。对于经过 $(x_1,y_1)$ 和 $(x_2,y_2)$ 的直线，代入直线方程有

$$\begin{cases} Ax_1+By_1+C=0 \\ Ax_2+By_2+C=0\end{cases}$$

这是一个关于 $A,B,C$ 的不定方程，虽然不能直接求出值，但是能够得到 $A,B,C$ 之间的比例关系。可以求得

$$\begin{cases}A=y_1-y_2 \\ 
B=x_2-x_1 \\ 
C=x_1y_2-x_2y_1\end{cases}$$

在这里，若 $A,B,C$ 均不为零，则对于直线 $A_1x+B_1y+C_1=0$ 与 $A_2x+B_2y+C_2=0$ 而言：
- 两直线平行的条件为 $ \dfrac{A_1}{A_2} =\dfrac{B_1}{B_2}\ne\dfrac{C_1}{C_2}$；

- 两直线重合的条件为 $ \dfrac{A_1}{A_2} =\dfrac{B_1}{B_2}=\dfrac{C_1}{C_2}$

- 其余情况为两直线相交，相交时，联立两个直线方程求解交点坐标即可，联立求得

$$\begin{cases}
x=-\dfrac{B_2C_1+B_1C_2}{A_2B_1-A_1B_2} \\ \\
y=-\dfrac{A_2C_1-A_1C_2}{A_2B_1-A_1B_2}
\end{cases}$$

若 $B_1=B_2=0$，则重合的条件为 $\dfrac{C_1}{A_1}=\dfrac{C_2}{A_2}$，平行的条件为 $\dfrac{C_1}{A_1}\ne\dfrac{C_2}{A_2}$；

若 $A_1=A_2=0$，则重合的条件为 $\dfrac{C_1}{B_1}=\dfrac{C_2}{B_2}$，平行的条件为 $\dfrac{C_1}{B_1}\ne\dfrac{C_2}{B_2}$；

其余的情况均为相交。

对于分式值的比较，考虑到可能的浮点误差，建议将其转化为整数乘积的比较。

### 3. 代码

```cpp
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
using point = initializer_list<double>;

// 直线的一般方程为 ax+by+c=0，基于此定义一个直线类line
class line {
public:
	// 直接输入系数a,b,c
	line(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
	line(int _x1, int _y1, int _x2, int _y2) 
	{
		if (_x1 == _x2) { a = 1; b = 0; c = -_x1; }
		else if (_y1 == _y2) { a = 0; b = 1; c = -_y2; }
		else { a = _y1 - _y2; b = _x2 - _x1; c = _x1 * _y2 - _x2 * _y1; }
	}
	friend bool intersecting(const line&, const line&);
	friend bool parallel(const line&, const line&);
	friend bool same(const line&, const line&);
	friend point intersect_point(const line&, const line&);
protected:
	int a, b, c;
};

// 判断直线位置关系
inline bool parallel(const line& _line1, const line& _line2)
{
	// 如果直线平行:
	// 垂直为x轴时，两条直线的b,c不成比例，垂直于y轴时，a,c不成比例。
	if (_line1.a == 0 and _line2.a == 0) return _line1.b * _line2.c != _line1.c * _line2.b;
	if (_line1.b == 0 and _line2.b == 0) return _line1.a * _line2.c != _line1.c * _line2.a;
	else
	{
		// 一条平行于x轴，一条平行于y轴，肯定不平行
		if (_line1.a == 0 and _line2.b == 0 or _line1.b == 0 and _line2.a == 0) return false;
		else return (_line1.a * _line2.b == _line2.a * _line1.b and _line1.c * _line2.a != _line1.a * _line2.c);
	}
}

// 判断两直线重合
inline bool same(const line& _line1, const line& _line2) 
{
	return (_line1.a * _line2.b == _line2.a * _line1.b and _line1.c * _line2.a == _line1.a * _line2.c); 
}

// 判断两直线相交
inline point intersect_point(const line& _line1, const line& _line2)
{
	return { -1.0 * (-_line2.b * _line1.c + _line1.b * _line2.c) / (_line2.a * _line1.b - _line1.a * _line2.b),
	1.0 * (-_line2.a * _line1.c + _line1.a * _line2.c) / (_line2.a * _line1.b - _line1.a * _line2.b) };
}

int main()
{
	int n, x[5] = { 0 }, y[5] = { 0 };
	cin >> n;
	cout << "INTERSECTING LINES OUTPUT" << endl;
	for (int i = 1; i <= n; i += 1)
	{
		cin >> x[1] >> y[1] >> x[2] >> y[2] >> x[3] >> y[3] >> x[4] >> y[4];
		if (parallel(line(x[1], y[1], x[2], y[2]), line(x[3], y[3], x[4], y[4]))) cout << "NONE" << endl;
		else if (same(line(x[1], y[1], x[2], y[2]), line(x[3], y[3], x[4], y[4]))) cout << "LINE" << endl;
		else
		{
			point intersecting_point = intersect_point(line(x[1], y[1], x[2], y[2]), line(x[3], y[3], x[4], y[4]));
			printf("POINT %.2lf %.2lf\n", *(intersecting_point.begin()), *(intersecting_point.begin() + 1));
		}
	}
	cout << "END OF OUTPUT" << endl;
}
```

---

## 作者：Unnamed114514 (赞：0)

首先我们要知道怎么求斜率：

$k=\dfrac{y_1-y_2}{x_1-x_2},b=y_1-kx_1$

那么就很好搞了：

- 若 $k_1=k_2$ 且 $b_1=b_2$，那么两条直线重合。

- 若 $k_1=k_2$ 且 $b_1\ne b_2$，那么两条直线平行。

- 若 $k_1\ne k_2$，那么两条直线相交，解得 $x=\dfrac{b_1-b_2}{k_2-k_1}$。

下面与 $y$ 轴平行的 corner：

- 注意到存在 $x_1=x_2$ 的情况，此时笔者的处理是 $k=\infty,b=x_1=x_2$，这样的话如果 $k_1=k_2=\infty$，那么就看 $b_1$ 和 $b_2$ 的关系，否则交点的 $x$ 坐标就直接出来了，带入纵坐标即可。

```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#define double long double
#define endl '\n'
#define eps 1e-100
#define INF 1e100
using namespace std;
struct Line{
	double k,b;
	inline void input(){
		double x_0,x_1,y_0,y_1;
		cin>>x_0>>y_0>>x_1>>y_1;
		if(fabs(x_0-x_1)<eps) k=INF,b=x_0;
		else k=(y_1-y_0)/(x_1-x_0),b=y_1-x_1*k;
	}
}A,B;
int T;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cout<<"INTERSECTING LINES OUTPUT"<<endl;
	cin>>T;
	while(T--){
		A.input(),B.input();
		if(fabs(A.k-INF)<eps){
			if(fabs(B.k-INF)<eps){
				if(fabs(A.b-B.b)<eps) cout<<"LINE"<<endl;
				else cout<<"NONE"<<endl;
			} else cout<<fixed<<setprecision(2)<<"POINT "<<A.b<<' '<<A.b*B.k+B.b<<endl;
		} else if(fabs(B.k-INF)<eps) cout<<fixed<<setprecision(2)<<"POINT "<<B.b<<' '<<B.b*A.k+A.b<<endl; 
		else if(fabs(A.k-B.k)<eps){
			if(fabs(A.b-B.b)<eps) cout<<"LINE"<<endl;
			else cout<<"NONE"<<endl;
		} else{
			double x=(A.b-B.b)/(B.k-A.k),y=A.b+A.k*x;
			cout<<fixed<<setprecision(2)<<"POINT "<<x<<' '<<y<<endl;
		}
	}
	cout<<"END OF OUTPUT"<<endl;
	return 0;
}
```

---

## 作者：Patrickpwq (赞：0)

思路：
我们先判断这两条直线是否平行 若平行 再去判断是否重合 若不平行 算交点

具体实现：
对于平行 我们直接判断v1,v2的叉积（v1,v2是来表示L1,L2的向量）是否为0

对于重合 我们把l1上的端点p1代入l2 判断叉积

![](https://img2018.cnblogs.com/blog/1452620/201810/1452620-20181015230406037-1707535310.png)

如图 只需判断v1,v2的叉积是否为0 ，可以画个重合的图自行理解

对于算交点 暴力用一次函数的方法解方程 不过除数有可能为0 需要特判垂直于x轴的线

附代码
```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cmath>
#define N 100005
#define eps 1e-8
using namespace std;
int n;
struct Point 
{
    double x,y;
    Point(){};
    Point(double x,double y):x(x),y(y){};
}p[N];
typedef Point Vector;
Vector operator +(Vector a,Vector b)
{
    return Vector(a.x+b.x,a.y+b.y);
}
Vector operator -(Vector a,Vector b)
{
    return Vector(a.x-b.x,a.y-b.y);
}
double Dot(Vector a,Vector b)
{
    return (a.x*b.x)+(a.y*b.y);
}
double Cross(Vector a,Vector b)
{
    return (a.x*b.y)-(a.y*b.x);
}
double Len(Vector a)
{
	return sqrt(Dot(a,a));
}
struct Line
{
    Point p1,p2;
    Line(){};
    Line(Point p1,Point p2):p1(p1),p2(p2){};
}l1,l2;
int main()
{
	cin>>n;
	puts("INTERSECTING LINES OUTPUT");
	while(n--)
	{
		cin>>l1.p1.x>>l1.p1.y>>l1.p2.x>>l1.p2.y;
		cin>>l2.p1.x>>l2.p1.y>>l2.p2.x>>l2.p2.y;
		Vector v1=l1.p1-l1.p2;
		Vector v2=l2.p1-l2.p2;
		if(fabs(Cross(v1,v2))<eps)//平行 
		{
			Vector v3=l1.p1-l2.p1;//把l2.p1代入直线1
			Vector v4=l1.p2-l2.p1; 
			if(fabs(Cross(v3,v4))<eps)	puts("LINE");	//重合 
			else puts("NONE");
		}
		else
		{
			double k1=0,k2=0,b1=0,b2=0;
			cout<<"POINT ";
			if(l1.p1.x-l1.p2.x==0)//垂直于x轴
			{
				k2=(l2.p1.y-l2.p2.y)/(l2.p1.x-l2.p2.x);
				b2=l2.p1.y-k2*l2.p1.x;
				printf("%.2f %.2f\n",l1.p1.x,k2*l1.p1.x+b2);
				continue;
			}
			if(l2.p1.x-l2.p2.x==0)
			{
				k1=(l1.p1.y-l1.p2.y)/(l1.p1.x-l1.p2.x);
				b1=l1.p1.y-k1*l1.p1.x;
				printf("%.2f %.2f\n",l2.p1.x,k1*l2.p1.x+b1);
				continue;
			}
			k1=(l1.p1.y-l1.p2.y)/(l1.p1.x-l1.p2.x);
			b1=l1.p1.y-k1*l1.p1.x;
			
			k2=(l2.p1.y-l2.p2.y)/(l2.p1.x-l2.p2.x);
			b2=l2.p1.y-k2*l2.p1.x;
			
			printf("%.2f %.2f\n",(b2-b1)/(k1-k2),(k1*b2-k2*b1)/(k1-k2));
		}
	}
	puts("END OF OUTPUT");
} 
```

---

