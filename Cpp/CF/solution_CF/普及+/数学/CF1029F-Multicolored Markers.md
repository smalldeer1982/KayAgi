# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 9
```

### 输出

```
14
```

## 样例 #3

### 输入

```
9 3
```

### 输出

```
14
```

## 样例 #4

### 输入

```
3 6
```

### 输出

```
12
```

## 样例 #5

### 输入

```
506 2708
```

### 输出

```
3218
```

# 题解

## 作者：Siyuan (赞：7)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Codeforces 1029F](https://codeforces.com/contest/1029/problem/F)

有一个由正方形砖块组成的板子（你可以认为是无限大的），你需要将 $a$ 个格子染成红色，$b$ 个格子染成蓝色。最终有颜色的砖块要形成一个大小为 $a+b$ 的矩形，并且其中至少有一种颜色也需要形成一个矩形。求出所有染色方案中，有颜色的砖块组成的矩形的周长最小值。

数据范围：$1\le a,b\le 10^{14}$

------

## Solution

我们可以发现，如果忽略染色的情况，那么矩形的形态总共有 $O(\sqrt{a+b})$ 个。对于这个数据范围，我们显然可以枚举矩形的较短边的长度 $i$。根据贪心的思路，我们从大到小枚举，遇到第一个满足条件的 $i$ 就可以得到最优解 $2\times(i+\frac{a+b}{i})$。

接下来的问题就是如何判断是否可以将某一种颜色形成一个矩形。此时我们也可以贪心，假设需要染成矩形的颜色有 $a$ 个，那么我们找到最大的 $j$ 满足 $j\le i$ 并且 $j\mid a$。如果 $\frac{a}{j}\le \frac{a+b}{i}$ 那么就说明满足条件。

我们又可以发现这个 $j$ 是单调的，所以可以 $O(\sqrt a)$ 求出 $a$ 的因子，直接用一个指针移动就能找到当前最大的 $j$ 了。

**时间复杂度**：$O(\sqrt a)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

long long solve(long long tot,long long a) {
    std::vector<int> f;
    for(int i=1;1LL*i*i<=a;++i) if(a%i==0) f.push_back(i);
    int p=(int)f.size()-1;
    for(int i=sqrt(tot);i>=1;--i) {
        if(tot%i) continue;
        while(f[p]>i) --p;
        if(a/f[p]<=tot/i) return 2LL*(i+tot/i);
    }
    return 1LL<<60;
}
int main() {
    long long n,m;
    scanf("%lld%lld",&n,&m);
    printf("%lld\n",std::min(solve(n+m,n),solve(n+m,m)));
    return 0;
}
```



---

## 作者：BLUESKY007 (赞：2)

这道题其实难度应该小于紫题...除了一点小特判以外没什么难度...$\leq50$行代码即可$AC$此题  
题目大意:给定两个数$a,b(1\leq a,b\leq 10^{14})$分别表示红色方格个数和蓝色方格个数,求这$a$个红色方格和$b$个蓝色方格构成的矩形周长的最小值,且满足在所构成的矩形中至少有一种颜色的所有方块也能构成一个矩形,数据保证存在至少一种合法的染色方案.  
这道题本质是数学题,根据矩形周长一定时长与宽的差越小矩形面积越大可以反推出矩形面积一定时长与宽的差越小矩形周长越小,所以我们可以从$\lfloor\sqrt{a+b}\rfloor$到$1$枚举所构成的大矩形的宽,这样可以保证有合法解即为最优解,不需要再考虑后面其他的合法解.  
对于一个合法的大矩形,设其宽为$i$,长为$d$,应当满足$a+b==i\times d$,且对于$a$和$b$中至少一个数存在一种因数分解方案$e\times f(e\leq f)$满足$e\leq i$且$f\leq d$(即当红色或蓝色方块构成矩形时能够被大矩形所包含),对此我们只需要对$i$做一次$O(\lfloor\sqrt{a+b}\rfloor)$的枚举.检验时只需对$a$和$b$做$O(i)$的枚举即可(当枚举的宽$>i$时显然已经不合法故只需枚举$\leq i$的宽).  
下面例行放$AC$代码$\downarrow\downarrow\downarrow$  
```cpp
#include<cstdio>//CF1029F
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;

long long a,b,c,d;

bool check(int u,long long v){
	for(int i=1;i<=u;i++){
		if(a%i==0){
			long long rep=a/i;
			if(i<=u&&rep<=v){
				return true;
			}
		}
	}
	for(int i=1;i<=u;i++){
		if(b%i==0){
			long long rep=b/i;
			if(i<=u&&rep<=v){
				return true;
			}
		}
	}
	return false;
}

int main(){
	scanf("%lld%lld",&a,&b);
	c=a+b;
	for(int i=(int)sqrt(c);i;i--){
		if(c%i==0){
			d=c/i;
			if(check(i,d)){
				printf("%lld",(d+i)*2);
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：guanyf (赞：1)

### 题意

- 有 $a$ 个红色方格和 $b$ 个蓝色方格，求这些方格构成的矩形的最大周长，且满足至少一种颜色的方格也能构成矩形。

- $1 \le a,b \le 10^{14}$

### 分析、思路

非常容易想到的思路就是：枚举所有方格构成的矩形的长 $x$ 和宽 $y$，在分别枚举红色和蓝色方格构成的矩形的长 $i$ 和宽 $j$，只要其中一组长和宽满足 $x \le i$ 并且 $y \le j$ 则 $x,y$ 是合法的。

思考上述思路可以优化的部分：
1. 由于只需要枚举长就可以算出宽，并且长和宽是成对出现的，因此只需要枚举到 $\sqrt{a+b}$ 就可以了，枚举红蓝方格时同理。

2. 由于题目求的是最大的周长，因此可以从 $\sqrt{a+b}$ 开始枚举，当找到一组合法的长和宽时候，就直接输出。枚举红蓝方格时同理。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
LL a, b;
bool check(LL tot, LL x, LL y) {
  for (int i = x; i >= 1; i--) {
    if (tot % i == 0 && tot / i <= y) {
      return 1;
    }
  }
  return 0;
}
int main() {
  ios::sync_with_stdio(0);
  cin >> a >> b;
  for (LL i = sqrt(a + b); i >= 1; i--) {
    if ((a + b) % i == 0) {
      LL j = (a + b) / i;
      if (check(a, i, j) || check(b, i, j)) {
        cout << 2 * (i + j), exit(0);
      }
    }
  }
  return 0;
}
```

### 扩展

由于枚举矩形的长和宽是具有单调性的，因此在每次检验的时候都不需要从头枚举。我们可以分别记录红和蓝的长分别枚举到了多少，每次只需要从 $\min(i,x)$ 开始枚举，找到第一个是当前矩形的边的值就行了。最后当当前长宽都合法时，才能返回 $1$。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
LL a, b, id[2] = {INT_MAX, INT_MAX};
bool check(LL tot, LL x, LL y) {
  LL& i = id[tot == b];
  for (i = min(i, x); tot % i; i--) {
  }
  return (tot / i <= y);
}
int main() {
  ios::sync_with_stdio(0);
  cin >> a >> b;
  for (LL i = sqrt(a + b); i >= 1; i--) {
    if ((a + b) % i == 0) {
      LL j = (a + b) / i;
      if (check(a, i, j) || check(b, i, j)) {
        cout << 2 * (i + j), exit(0);
      }
    }
  }
  return 0;
}
```


---

## 作者：Xiao_mo (赞：0)

# Step1
## [原题面](https://www.luogu.com.cn/problem/CF1029F)
数据范围为 $a,b≤10^{14}$ 。

简化题面: 一个面积为 $a+b$ 的大矩形，且大矩形包含一个面积为 $a$ 或 $b$ 的小矩形，求此矩形的最小周长。

# Step2
首先可以想到 $O(\sqrt{a+b})$ 枚举大矩形的宽 $i$ 。

此时只要判断能不能存在一个小矩形。

先预处理出面积为 $a$ 或 $b$ 的矩形的宽的可能值为 {$x_{l_1}$} 和 {$y_{l_2}$} 。

判断是否存在 $j$ 使得 $x_j≤i$ , $\frac{a}{x_j}≤\frac{a+b}{i}$ 或者使得 $y_j≤i$ , $\frac{b}{y_j}≤\frac{a+b}{i}$ 。

# Step3
因为要求周长最小。

又因为当 $i$ 越接近 $\frac{a+b}{i}$ 时,周长越小。

所以可到从大到小枚举大矩形的宽。

当找到一个可以构造就直接结束程序。

# End
```
#include<bits/stdc++.h>
#define ll long long
#define rg register
using namespace std;
inline ll read(){
	register ll s=0,f=0;
	register char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
ll a,b,ha[10000],hb[10000],la,lb;
int main() {
	a=read(),b=read();
	if(a>b)swap(a,b);
	ll sa=sqrt(a),sb=sqrt(b);
	for(int i=sb;i;i--){//预处理 
		if(i<=sa&&a%i==0)ha[++la]=i;
		if(b%i==0)hb[++lb]=i;
	}
	ll s=sqrt(a+b),c=a+b;
	for(ll i=s;i;i--){//从大到小枚举大矩形的宽 
		if(c%i!=0)continue;
		for(int j=1;j<=la;j++){//判断能否构造面积为a的小矩形 
			if(ha[j]>i)continue;
			if(a/ha[j]>c/i)break;
			printf("%lld",(i+c/i)*2);
			exit(0);
		}
		for(int j=1;j<=lb;j++){//判断能否构成面积为b的小矩形 
			if(hb[j]>i)continue;
			if(b/hb[j]>c/i)break;
			printf("%lld",(i+c/i)*2);
			exit(0);
		}
	}
	return 0;
}
```

---

## 作者：Bring (赞：0)

[更好的阅读体验请点这里](https://www.cnblogs.com/BrianPeng/p/12360327.html)

令$c=a+b$

一个整数边矩形的边长一定是矩形面积的因数

于是这个问题等价于求最大$i\leqslant\sqrt c,i|c$，使得有$f\leqslant i,f|a$且$\frac{a}{f}\leqslant \frac{c}{i}$，或有$g\leqslant i,g|b$且$\frac{b}{g}\leqslant \frac{c}{i}$，于是输出$2(i+\frac{c}{i})$

既然是求最大$i$，就让$i$从$\lfloor\sqrt c\rfloor$开始往下枚举

不失一般性，可以假设$f\leqslant\sqrt a,g\leqslant\sqrt b$

那么如果矩形$a$可以嵌入，就必有$f\leqslant i$且$\frac{a}{f}\leqslant \frac{c}{i}$

鉴于$f$与$\frac{a}{f}$在$f\geqslant 1$时负相关，可以把$f$设为$i$，然后向下寻找$a$的最大因数，判断$\frac{a}{f}$是否可行

另外因为外循环中$i$是下降的，所以$f$在每次循环开始时应设为$\min(f,i)$

$g$同理

**Time complexity:** $O(\sqrt a)$

**Memory complexity:** $O(1)$

细节见代码（$1.46$s / $12.00$KB）（貌似是rank $1$）

```cpp
//This program is written by Brian Peng.
#pragma GCC optimize("Ofast","inline","no-stack-protector")
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int read(){
	int x;char c(getchar());bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	if(c^'-')k=1,x=c&15;else k=x=0;
	while(isdigit(Gc(c)))x=(x<<1)+(x<<3)+(c&15);
	return k?x:-x;
}
void wr(int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(int i(a);i<(b);++i)
#define Frn1(i,a,b) for(int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
int a,b,c,f,g;
signed main(){
	c=Rd(a)+Rd(b),f=sqrt(a),g=sqrt(b);
	Frn_(i,sqrt(c),1)if(!(c%i)){
		f=min(f,i),g=min(g,i);
		while(a%f)--f;
		if(a/f<=c/i)wr((i+c/i)<<1),exit(0);
		while(b%g)--g;
		if(b/g<=c/i)wr((i+c/i)<<1),exit(0);
	}
	exit(0);
}
```


---

## 作者：ACM天体星月 (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a ,b ,c ,d;
const ll inff = 0x3f3f3f3f3f3f3f3fLL; //18
bool check(ll x , ll y){
	
	for(ll i = x ; i >= 1 ; i-- ){
		if(a % i == 0 && a / i <= y) return 1;
		if(b % i == 0 && b / i <= y) return 1;
	}
	return false ;
}

int main(){
//ll a, b;
	cin >> a >> b;
	 c = a + b;
	 ll ans = inff;
	 //从大往小枚举，即宽最大时，周长最小 
	for(ll i = 1ll; i * i <= c; i++){
		if(c % i == 0 ){
		 d = c / i;
		 if(check(i,d)){
		 	ans = min(ans,2ll * (d + i));
		 	//不优化反而更快 
		 //	cout << ans << endl;
		 //	return 0;
		 }
		} 
	}
	cout << ans << endl;
}
```


---

## 作者：Mickey_snow (赞：0)

[CF1029F](http://codeforces.com/problemset/problem/1029/F) _Multicolored Markers_ : 枚举

你需要在一个排布着无限个瓦块的地方将 $a$ 片瓦块染成红色， $b$ 片瓦块染成蓝色。一开始所有的瓦块都是白色的，你只能在白色的瓦块上染色。而且染色完成之后的瓦块必须满足：

1. 所有红色瓦块形成一个矩形或者所有蓝色瓦块形成一个矩形。
2. 所有不是白色的瓦块形成一个矩形。

求出在所有可行的方案中，所有不是白色的瓦块形成的矩形的最小周长 $min(C)$ . 输出这个 $C$.

可以发现，最终有色瓦块形成的这个矩形的长和宽如果分别为 $m$ 和 $n$ ,那么 $m+n=a+b$.我们将所有可能的 $m$ 和 $n$ 全部枚举出来，找到一个最小的 $C$ 就可以了。

不难发现，一组符合条件的 $m$ 和 $n$ 满足下列条件：

1. $m | a+b$ .
2. $n \ge \lceil a \div m \rceil$ 或 $n \ge \lceil b \div m \rceil$ .

我们可以用两次循环分别枚举 $m$ 满足条件2的前半部分或者后半部分。如果限制 $m \leq n$ ，那么 $m \in [1, \sqrt {a+b}]$ 且 $m \in N^+$ ,缩小了枚举范围。时间复杂度为 $O(\sqrt{N})$ .

代码如下：

```c#
using System;

namespace CF1029F 
{
	class Program 
	{
		static void Main(string[] args) 
		{
			string[] div = Console.ReadLine().Split(' ');
			Int64 a = Convert.ToInt64(div[0]), b = Convert.ToInt64(div[1]), _min = Int64.MaxValue;
			Int64 tot = a + b, siz = (Int64)Math.Sqrt(tot) + 1, len = a;

			for(int i = 1;i < siz;i++) {
				if(a % i == 0)
					len = a / i;
				if(tot % i == 0 && tot / i >= len)
					_min = Math.Min(_min, ((tot / i + i) << 1));
			}
			len = b;
			for(int i = 1;i < siz;i++) {
				if(b % i == 0)
					len = b / i;

				if(tot % i == 0 && tot / i >= len)
					_min = Math.Min(_min, ((tot / i + i) << 1));
			}

			Console.WriteLine(_min.ToString());
		}
	}
}
```

---

