# Umka and a Long Flight

## 题目描述

The girl Umka loves to travel and participate in math olympiads. One day she was flying by plane to the next olympiad and out of boredom explored a huge checkered sheet of paper.

Denote the $ n $ -th Fibonacci number as $ F_n = \begin{cases} 1, & n = 0; \\ 1, & n = 1; \\ F_{n-2} + F_{n-1}, & n \ge 2. \end{cases} $

A checkered rectangle with a height of $ F_n $ and a width of $ F_{n+1} $ is called a Fibonacci rectangle of order $ n $ .

Umka has a Fibonacci rectangle of order $ n $ . Someone colored a cell in it at the intersection of the row $ x $ and the column $ y $ .

It is necessary to cut this rectangle exactly into $ n+1 $ squares in such way that

- the painted cell was in a square with a side of $ 1 $ ;
- there was at most one pair of squares with equal sides;
- the side of each square was equal to a Fibonacci number.

Will Umka be able to cut this rectangle in that way?

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/e5f4a8a6969129eb7406262bfa57aeda28c2a7af.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/f9a9f5019cb436c08d516ca2337b43e44d86aeca.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811D/b75cbdcea405d71b913c844c613b79782c601576.png) The first, third and fourth test cases.

## 样例 #1

### 输入

```
12
1 1 1
2 1 2
3 1 4
3 3 2
4 4 6
4 3 3
5 6 5
5 4 12
5 2 12
4 2 1
1 1 2
44 758465880 1277583853```

### 输出

```
YES
NO
YES
YES
YES
NO
YES
NO
NO
YES
YES
NO```

# 题解

## 作者：Coffee_zzz (赞：8)

### 思路

显然这个长为 $F_{n+1}$ 宽为 $F_n$ 的长方形应被分为 $1$ 个边长为 $F_0$ 的正方形，$1$ 个边长为 $F_1$ 的正方形，$1$ 个边长为 $F_2$ 的正方形，一直到 $1$ 个边长为 $F_n$ 的正方形。证明根据题目中所给的公式推导即可。

题目给定了边长为 $F_0$ 的正方形的位置，需要求是否存在一种分割方法。

我们依次考虑边长为 $F_n$ 至边长为 $F_1$ 的正方形是否能被分割出来。想要按照题目分割下去，显然需要使每次分割的正方形在原长方形的最左端或最右端。当最左端和最右端都无法分割（即这两种分割方式都需要切掉给定的正方形）时，显然无解，输出 `NO`。

全分割完成后，直接输出 `YES` 即可。

其中，在检验这两种分割方式前，可以判断给定的小正方形是否在原长方形的左半边，若在左半边则将其对称至右半边，在检验是否可以分割的时候只检验是否能在最左端分割即可。在每次分割完之后需要将长方形旋转一下，让它的宽不大于它的长。

斐波那契数列可以直接预处理得到。不要忘记开 `long long`。

这里使用了递归去实现。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
int fib[50];
bool dfs(int n,int a,int b,int x,int y){
	if(n==1) return 1;
	int p=b/2;
	if(y<=p) y=b+1-y; //对称
	if(y<=a) return 0; //判断是都可以分割
	return dfs(n-1,b-a,a,y-a,x); //旋转长方形并递归
}
void solve(){
	int n,x,y;
	n=read(),x=read(),y=read();
	int a=fib[n],b=fib[n+1];
	if(dfs(n,a,b,x,y)) cout<<"yEs\n";
	else cout<<"nO\n";
}
signed main(){
	fib[0]=1,fib[1]=1;
	for(int i=2;i<=45;i++) fib[i]=fib[i-1]+fib[i-2];
	int t;
	t=read();
	while(t--) solve();
	return 0;
}
```

---

## 作者：Happy_14 (赞：5)

# CodeForce 1811D. Umka and a Long Flight
##  一个结论

$$
F_0^2+F_1^2+...+F_n^2=F_n\cdot F_{n+1}
$$

通过简单的迭代证明：

$$
F_n \cdot F_{n+1} = F_n \cdot (F_{n-1}+F_n)=F_{n-1} \cdot F_n+F_n^2
$$

因此，对于面积为 $F_n \cdot F_{n+1}$ 的矩形，只能切割为边长为 $F_0,F_1,....F_{n}$ 的正方形。

我们贪心地每次放最大的正方形，从而把问题不断缩小为一个更小的矩形，且问题性质不变，也就是放置一个正方形后，将问题转换为 $F_{n-1} \cdot F_n$ 的矩形。

## 代码
```cpp
#include <iostream>
#include<cstring>
#include<cmath>
using namespace std;

int fib[50];

void init()
{
	fib[0] = fib[1] = 1;
	for (int i = 2; i < 50; ++i)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
	}
}

int main()
{
	int t;
	int n;
	int x, y;
	init();
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		scanf("%d%d", &x, &y);

		int l = 1, r = fib[n + 1];
		int d = 1, u = fib[n];
		bool flag = true;
		for (int i = n; i >= 2; --i)
		{
			if (r - l + 1 > u - d + 1)
			{ 
				if (y > l + fib[i] - 1)
				{
					l += fib[i];
				}
				else if (y < r - fib[i] + 1)
				{
					r -= fib[i];
				}
				else
				{
					flag = false;
					break;
				}
			}
			else
			{
				if (x > d + fib[i] - 1)
				{

					d += fib[i];
				}
				else if (x < u - fib[i] + 1)
				{
					u -= fib[i];
				}
				else
				{
					flag = false;
					break;
				}
			}
		}
		printf(flag ? "YES\n" : "NO\n");
	}
	return 0;
}
```


---

## 作者：ncwzdlsd (赞：4)

一个结论：

$$
F_0^2+F_1^2+\cdots+F_{n-1}^2+F_n^2=F_n\times F_{n+1}
$$

对于题目要求的 $F_n\times F_{n+1}$ 的矩形，考虑将其不断拆分掉一个正方形，剩余矩形可以按照之前的方式继续操作。观察到此时的划分方案即为题目要求的。

如果某时刻（设定长大于宽）的 $y\in(F_{siz-1},F_{siz}]$，那么无论如何它一定会被一个完整的正方形切割掉，此时不存在方案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int F[45],n,x,y;

void init()
{
	F[0]=1,F[1]=1;
	for(int i=2;i<=44;i++) F[i]=F[i-1]+F[i-2];
}

bool cut(int siz,int x,int y)
{
	if(siz==1) return 1;
	if(y<=F[siz-1]) return cut(siz-1,y,x);//(x,y)在左
	else if(y>F[siz]) return cut(siz-1,y-F[siz],x);//(x,y)在右
	return 0;
}

void solve()
{
	cin>>n>>x>>y;
	if(cut(n,x,y)) cout<<"YES\n";
	else cout<<"NO\n";
}

signed main()
{
	int t;cin>>t;
	init();
	while(t--) solve();
	return 0;
}
```

---

## 作者：eb0ycn (赞：2)

传送门：[CF1811D](https://www.luogu.com.cn/problem/CF1811D)。

## 题意

- 给你一个整数 $n$ 和一个长为 $F_{n+1}$ 宽为 $F_{n}$ 的矩形。

- 数组 $F$ 为斐波那契数列，且 $F_1=1$，$F_2=2$。

- 问能否把该矩形分为几个最多有一对相同的正方形，其中第 $x$ 行，第 $y$ 列的必须单独划分为一个 $1 \times 1$ 的小正方形。

## 思路

首先感性理解一下：所有正方形的边长一定是 $F_{1} \sim F_{n}$，这里建议画图理解，或者看看这幅图：[斐波那契数列的图片](https://baike.baidu.com/pic/%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0%E5%88%97/99145/1/63d0f703918fa0ec5e978378219759ee3d6ddb77?fromModule=lemma_top-image&ct=single#aid=1&pic=63d0f703918fa0ec5e978378219759ee3d6ddb77)。

如果当前矩形为 $x \times y$ 且有解，那么一定能在边界放一个 $y \times y$ 的正方形，让剩下的 $y \times (x-y)$ 的矩形有解。

具体细节看下面的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/18yyimus.png)


然后一步一步模拟，直到宽变为 $1$ 或发现无解。

什么情况下无解呢？就是到了某个时候左边右边都放不下正方形了，目标点被夹在中间。

## 代码

```cpp
#include<cstdio>
using namespace std;
int t,n,f[46],x,y,h,l,tmp;
bool flg;
int main(){
	f[1]=1,f[2]=2,scanf("%d",&t);
	for(int i=3;i<46;++i)f[i]=f[i-1]+f[i-2];
	while(t--){
		scanf("%d%d%d",&n,&x,&y),flg=0,h=f[n+1],l=f[n];
		while(l>1&&!flg){
			tmp=y,y=x;
			if(tmp>l)x=tmp-l;
			else x=tmp;
			if(x<l)tmp=l,l=h-l,h=tmp;
			else flg=1;
		}printf("%s\n",flg?"NO":"YES");
	}
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：

对于一个 $n$ 阶斐波那契矩形，可以将其分为一个 $F_{n} \times F_{n}$ 的矩阵和一个 $n-1$ 阶斐波那契矩阵

考虑给出的坐标 $(x,y)$，根据上面的分解方法，可得每次升阶会加在当前矩阵的较长边上，也就是说每次升阶根据**奇偶性**在**左/右**或者**上/下**方加一个矩阵，那么坐标  $(x,y)$ 每次的变化就是确定的 $F_{i}$，那么 $x \div y$ 可以分解为 $F_{a}+F_{b}+F_{c}+...$。

### 代码：
```
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 50;

int T, n, a, b;
int f[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	f[0] = 1, f[1] = 1;
	for (int i = 1; i <= 50; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	while (T--) {
		cin >> n >> a >> b;
		for (int i = n; i >= 1; i--) {
			if ((n - i) & 1) {
				if (a > f[i])
					a -= f[i];
			} else {
				if (b > f[i])
					b -= f[i];
			}
		}
		if (a == 1 && b == 1)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}

```

---

## 作者：WaterSun (赞：0)

# 思路

假设原题目中的 $n$ 在本文中为 $num$，则原长方形的长 $m = f_{num + 1}$ 和宽 $n = f_{num}$。

显然对于最初始的长方形，显然是要将一个 $f_{num} \times f_{num}$ 的长方形丢进去的，并且要么放最左边，要么放在最右边。因为对于当前的 $m = f_{num + 1} = f_{num} + f_{num - 1}$，减去当前要放进去的方块，剩余的长只剩下 $f_{num - 1}$，而 $f_{num - 1} \leq f_{num}$，所以额外的那一个点要么会使放在左边的不行，要么是放在右边的不行。

发现放置一个方块后，其余的情况是类似的直接递归处理即可。每一次递归更新 $m,n$ 以及额外点的新位置即可。（无解的情况是额外的点既会影响放在左边的情况，也会影响放在右边的情况）

需要注意的是 $m$ 被减后，$n > m$，所以需要将整个图形顺时针或逆时针转 $90 ^\circ$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 110;
int num,n,m,x,y;
int f[N] = {1,1};

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void init(){
    for (re int i = 2;i <= 50;i++) f[i] = f[i - 1] + f[i - 2];
}

inline bool dfs(int u,int n,int m,int x,int y){
    if (!u) return true;
    if (y > f[u]){
        m -= f[u];
        y -= f[u];
        return dfs(u - 1,m,n,y,n - x + 1);
    }
    if (y < m - f[u] + 1){
        m -= f[u];
        return dfs(u - 1,m,n,y,n - x + 1);
    }
    return false;
}

inline void solve(){
    num = read();
    n = f[num];
    m = f[num + 1];
    x = read();
    y = read();
    if (dfs(num,n,m,x,y)) puts("YES");
    else puts("NO");
}

signed main(){
    init();
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1811D)

&nbsp;

### 题目大意
给定一个整数 $n$ 和一个长为 $F_n$，宽为 $F_{n+1}$ 的矩形，$F_i$ 代表斐波那契数列中的第 $i$ 项。

然后标记矩阵中位于第 $i$ 行，第 $j$ 列的一个 $1 \times 1$ 的单元格，让你判断能否将该矩形分割成若干个边长为斐波那契数列中某一项的正方形，使得被标记的单元格被单独分割。

同时需要满足的是，分割出来的正方形中至多有两个边长相等的正方形。

&nbsp;

### 解题思路
我们尝试从编号为 $1$ 的矩形开始递推，发现一个编号为 $i$ 的矩形可以由编号为 $[0,i-1]$ 的 $i$ 个矩形合并得到，就像下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/0e1jbaiu.png)

而在题面中我们可以注意到，至多有 $2$ 个矩形的边长是相同的。而在这样的分割方式下，矩形 $F_0$ 和 $F_1$ 边长均为 $1$，达到了题目限制，也就是说我们不能再对其中的矩形进行拆分。

也就是说我们只需要判断给定的矩形能否在使 $(i,j)$ 独立的情况下分割出编号为 $1\sim n-1$ 的矩形即可。

发现 $n$ 并不大，于是考虑递推解决，预处理出边长，接着从大至小分割，每次分割矩形左侧，然后旋转矩形，对于标记点在矩形左侧的情况将标记点对称到右边即可。

代码如下：
```cpp
bool cut(int siz,ll a,ll b,ll x,ll y){
	if(siz==1) return 1;//分割到只剩下1*1的方格
	int mid=b/2ll;
	if(y<=mid) y=b-y+1ll;//判断是否在左侧
	if(y<=a) return 0;//是否能够分割
	return cut(siz-1,b-a,a,y-a,x);
}

int main(){
	ios::sync_with_stdio(false);
   
    scanf("%d",&t);
    a[0]=a[1]=1ll;
    for(int i=2;i<=45;i++){//预处理
    	a[i]=a[i-1]+a[i-2];
	}
    
    while(t--){
    	int x,y;
    	scanf("%d%lld%lld",&n,&x,&y);
    	if(cut(n,a[n],a[n+1],x,y)) printf("YES\n");
    	else printf("NO\n");
	}
    return 0;
}

```
完结撒花 OvO

---

## 作者：BLX32M_10 (赞：0)

## 题意

给你一个长为 $F_{n + 1}$，宽为 $F_n$ 的矩形（$F_i$ 为斐波那契数列的第 $i$ 项，$F_0=F_1=1$）和一个点，在这个矩形中可以放一些边长斐波那契数列中的数的正方形（同种最多两种），求能否在填满这个矩形的同时让这个点恰好在一个 $1 \times 1$ 的矩形中。

## 题解

易证如果想要填满这个矩形，那么选取的正方形的边长必须是 $F_0,F_1,F_2,\cdots,F_n$。

不难发现每一个正方形必须填在剩余长方形的一侧才能填满矩形，所以我们考虑从大到小填正方形。

那么我们考虑每次看该点是否可以在填下一个正方形的前提下在填下正方形的另一侧。

形式化地，如果该正方形在最左侧或最右侧的 $F_{nown+1}-F_{nown}$ 格（我们假设这个长方形是横向的），那么将坐标转化为长为 $F_{nown}$，宽为 $F_{nown-1}$ 的长方形中的坐标继续运算，否则判定为不可以达成并终止。如果运算到长为 $2$，宽为 $1$ 的长方形，那么判定为可以达成并终止。

本人使用的递归来实现这种算法。（感觉一个循环就行但是当时在做的时候就用的是递归）

AC code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int fib[100];
bool slv(int n, int x, int y)
{
    if (n == 1)
        return 1;
    if (y <= fib[n - 1])
        return dfs(n - 1, y, x);
    else if (y > fib[n])
        return dfs(n - 1, y - fib[n], x);
    return 0;
}
signed main()
{
    int t, n, x, y;
    scanf("%lld", &t);
    fib[0] = fib[1] = 1;
    for (int i = 2; i <= 46; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    while (t--)
    {
        scanf("%lld %lld %lld", &n, &x, &y);
        if (slv(n, x, y))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
```

---

## 作者：20120511qhc (赞：0)

## 思路

通过数学归纳法，容易证明：$F_0^2 + F_1^2 + F_2^2 +...+ F_n^2 = F_n \times F_{n+1}$

于是，我们可以使用贪心，从最大的正方形开始往长方形里放，如果能放完，输出 `YES` ，否则输出 `NO`。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, x, y, fib[50] = {1, 1, 2}, f;
void init(){
    for(int i = 3; i <= 49; i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}
void S(int j, int x, int y){
    if(j == 1) return;
    if(j % 2){
        if(y > fib[j]){
            S(j - 1, x, y - fib[j]);
        }
        else if(fib[j + 1] - y + 1 > fib[j]){
            S(j - 1, x, y);
        }else{
            f = 1;
            return;
        }
    }else{
        if(x > fib[j]){
            S(j - 1, x - fib[j], y);
        }
        else if(fib[j + 1] - x + 1 > fib[j]){
            S(j - 1, x, y);
        }else{
            f = 1;
            return;
        }
    }
}
signed main(){
    init();
    for(cin >> t; t; t--){
        cin >> n >> x >> y;
        f = 0;
        if(n % 2 == 0){
            int u = x;
            x = y;
            y = fib[n] - u + 1;
        }
        S(n, x, y);
        if(f){
            cout << "NO\n";
        }else{
            cout << "YES\n";
        }
    }
    return 0;
}
```


---

