# [ABC274D] Robot Arms 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc274/tasks/abc274_d

長さ $ N $ の正整数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ および整数 $ x,\ y $ が与えられます。  
次の条件をすべて満たすように、$ xy $ 座標平面上に $ N+1 $ 個の点 $ p_1,\ p_2,\ \dots,\ p_N,\ p_{N+1} $ を配置することができるか判定してください。(同じ座標に $ 2 $ 個以上の点を配置してもよいです。)

- $ p_1\ =\ (0,\ 0) $
- $ p_2\ =\ (A_1,\ 0) $
- $ p_{N+1}\ =\ (x,\ y) $
- 点 $ p_i $ と点 $ p_{i+1} $ の距離は $ A_i $ ($ 1\ \leq\ i\ \leq\ N $)
- 線分 $ p_i\ p_{i+1} $ と線分 $ p_{i+1}\ p_{i+2} $ のなす角は $ 90 $ 度 ($ 1\ \leq\ i\ \leq\ N\ -\ 1 $)

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^3 $
- $ 1\ \leq\ A_i\ \leq\ 10 $
- $ |x|,\ |y|\ \leq\ 10^4 $
- 入力される値はすべて整数

### Sample Explanation 1

$ xy $ 座標平面に $ p_1\ =\ (0,\ 0),\ p_2\ =\ (2,\ 0),\ p_3\ =\ (2,\ 1),\ p_4\ =\ (-1,\ 1) $ として点を配置したのが以下の図です。これは問題文の条件をすべて満たしています。 !\[\](https://img.atcoder.jp/ghi/9e66a2e8cd081f011d3baba22dbe64fa.jpg)

### Sample Explanation 2

$ p_1\ =\ (0,\ 0),\ p_2\ =\ (2,\ 0),\ p_3\ =\ (2,\ 2),\ p_4\ =\ (0,\ 2),\ p_5\ =\ (0,\ 0),\ p_6\ =\ (2,\ 0) $ とすれば問題文の条件をすべて満たすことができます。同じ座標に複数の点を置いてもよいのに注意してください。

## 样例 #1

### 输入

```
3 -1 1
2 1 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 2 0
2 2 2 2 2```

### 输出

```
Yes```

## 样例 #3

### 输入

```
4 5 5
1 2 3 4```

### 输出

```
No```

## 样例 #4

### 输入

```
3 2 7
2 7 4```

### 输出

```
No```

## 样例 #5

### 输入

```
10 8 -7
6 10 4 1 5 9 8 6 5 1```

### 输出

```
Yes```

# 题解

## 作者：Kyl_in_2024 (赞：4)

**前言**

一个使用 `bitset` 的超短代码！

**思路**

因为第一步只能正着走，所以可以当成从 $\left ( A_{1},0 \right )$ 出发，然后走 $n-1$ 步；横纵坐标一起处理会爆？那就分开处理，反正要么竖着走要么横着走；数据存在负数？那就坐标加上一个极大值，比如 $10^{3} \times 10$，因为这个数是 $N$ 和 $A_{i}$ 的最大值的乘积。

**实现**

用数组的话还要一个一个遍历，太麻烦了，对键盘和发际线不好。

于是可以想到 ——`bitset`。

`bitset` 为什么方便一点？因为它不仅可以直接用方括号 `[]` 赋值，还支持位运算，定义时还能用字符串赋值，比如：

`bitset<3> a("110");`

就相当于 `a[2]=1,a[1]=1,a[0]=0`。

所以在这里，我们可以直接定义 `bitset<10005>bx,by;` 然后直接把其中一个赋值为它本身左移或上它本身右移的结果就行，也就是 `t=(t<<a[i])|(t>>a[i])`。

**代码**

```
#include<bits/stdc++.h>
using namespace std;
const int N=10005;
bitset<2*N>bx,by;
int main(){
	int n,x,y,m;
	cin>>n>>x>>y>>m;
	bx[N+m]=1,by[N]=1;
	for(int i=2;i<=n;i++){
		cin>>m;
		if(i%2==1)bx=(bx<<m)|(bx>>m);
		else by=(by<<m)|(by>>m);
	}
	if(bx[x+N]&&by[y+N])cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：Code_AC (赞：4)

[更好的阅读体验](https://www.cnblogs.com/yhx-error/p/16818610.html)

这是一道较为简单的可行性DP。

首先看到题目，很容易想到将横纵坐标一起进行处理，但显然时间会炸飞。

所以我们将横纵坐标拆开分别处理，那么就有如下状态：

$dpa_{i,j}$ 表示在所有竖直移动的操作中，进行到第 $i$ 个时能否到达 $j$。

$dpb_{i,j}$ 表示在所有水平移动的操作中，进行到第 $i$ 个时能否到达 $j$。

那么转移方程很显然：

$$
\begin{cases}dpa_{i,j}=dpa_{i-1,j-a_i}|dpa_{i-1,j+a_i}\\dpb_{i,j}=dpb_{i-1,j-a_i}|dpb_{i-1,j+a_i}\end{cases}
$$

然后就做完了。

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e4+5;

// char buf[1<<21],*p1=buf,*p2=buf;
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar(); }
    while(isdigit(ch))
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}

int n,x,y;
int a[MAXN],b[MAXN];
int cnta,cntb;
int dpa[2005][20005],dpb[2005][20005];

int main()
{
    n=read(),x=read()+10000,y=read()+10000;
    for(int i=1;i<=n;i++)
    {
        int x=read();
        if(i%2==0) a[++cnta]=x;
        else b[++cntb]=x;
    }
    dpa[0][10000]=true;
    for(int i=1;i<=cnta;i++)
        for(int j=a[i];j<=20000;j++)
            dpa[i][j]=dpa[i-1][j-a[i]]|dpa[i-1][j+a[i]];
    dpb[1][b[1]+10000]=true;
    for(int i=2;i<=cntb;i++)
        for(int j=b[i];j<=20000;j++)
            dpb[i][j]=dpb[i-1][j-b[i]]|dpb[i-1][j+b[i]];
    if(dpa[cnta][y] && dpb[cntb][x]) printf("Yes\n");
    else printf("No\n");
    return 0;
}
```

---

## 作者：SUNCHAOYI (赞：2)

首先提醒一下不要读错题目，因为题目并没有要求旋转 $90$ 度是顺时针还是逆时针。

将 $dx,dy$ 分开考虑，题目转换为 $dx = A_1,dy = 0$，然后 $A_{2i + 1},A_{2i} (i > 0)$ 分别对 $dx,dy$ 产生影响，问能否凑成题目所求的数 $(x,y)$。尝试 $\texttt{dp}$，若某一维的 $x$ 可以得到，那么对于本轮的 $A$，可以得到 $x - A$ 与 $x + A$，转移的时候直接枚举上一轮所有被标记的位置即可。为了方便负数的操作，直接使用 `map` 存储。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e3 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,x,y,dx,dy,a[MAX];
map <int,int> dpx[MAX],dpy[MAX];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();x = read ();y = read ();
	for (int i = 1;i <= n;++i) a[i] = read ();
   //坐标x y 分开考虑
	dpx[1][a[1]] = 1;//初始化
	for (int i = 3;i <= n;i += 2)
		for (auto j : dpx[i - 2])//由上一轮得到的数进行转移
			dpx[i][j.first + a[i]] = dpx[i][j.first - a[i]] = 1;	
	dpy[0][0] = 1;//初始化
	for (int i = 2;i <= n;i += 2)
		for (auto j : dpy[i - 2])
			dpy[i][j.first + a[i]] = dpy[i][j.first - a[i]] = 1;
	if (dpx[(n & 1) ? n : n - 1].count (x) && dpy[(n & 1) ? n - 1 : n].count (y)) puts ("Yes");
	else puts ("No");
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：JiaY19 (赞：1)

[**更好的阅读体验**](https://www.cnblogs.com/mfeitveer/p/16821377.html)

### 思路

比较简单的一道题。

考虑到方向都是确定的，只要考虑每一步走正的还是走负。

很简单就可以想到使用背包来做这个问题。

设 $f_{i,j}$ 为第 $\text{i}$ 步，能否走到坐标 $j$。

可以对于 $x,y$ 坐标分别考虑。

但需要注意，坐标有可能是负的，所以需要给整体加上一个极大值。

给一个 $\text{dp}$ 转移式。

$$f_{i,j} = f_{i,j-a_i} + f_{i,j+a_i}$$

时间复杂度：$O(nm)$，$m$ 为值域。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int inf = 10000;

int a[N] , f[3][2][inf * 2];

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

int main()
{
    int n = read() , x = read() , y = read();
    for(int i = 1;i <= n;i++)
        a[i] = read();
    int opt = 0 , optl[3];
    for(int k = 1;k <= 2;k++)
    {
        int opt = 0; 
        if(k == 1) f[k][opt][inf + a[1]] = 1;
        else f[k][opt][inf] = 1;
        for(int i = (k == 1 ? 3 : 2);i <= n;i += 2)
        {
            opt ^= 1;
            memset(f[k][opt] , 0 , sizeof f[k][opt]);
            for(int j = 0;j <= 2 * inf;j++)
            {
                if(j - a[i] >= 0) f[k][opt][j] |= f[k][opt ^ 1][j - a[i]];
                if(j + a[i] <= 2 * inf) f[k][opt][j] |= f[k][opt ^ 1][j + a[i]];
            }
        }
        optl[k] = opt;
    }
    if(f[1][optl[1]][x + inf] && f[2][optl[2]][y + inf])
        puts("Yes");
    else puts("No");
    return 0;
}
```

---

## 作者：JustForYourself (赞：0)

一道动态规划好题。本人测试[直接暴力](https://atcoder.jp/contests/abc274/submissions/35888658)会超时。

很容易发现因为要求线段垂直，两个维度是互相独立的。

也就是说对于 $i=1,3,5$ 直到超出 $N$ 的范围，我们需要让所有的 $a_i$ 加加减减凑出 $x$，对于 $y$ 同理。

我们显然可以进行一个动态规划，令 $dp(i,j)$ 为放置完第 $i$ 个点，当前的 $x$（$i$ 为奇数） 或是 $y$（$i$ 为偶数）能否为 $j$。那么 $dp(i,j) = dp(i-2,j-a_i) \space | \space dp(i-2,j+a_i)$，其中 $|$ 为逻辑或运算。

注意 $j$ 有可能是负数，我们需要特殊处理，这里笔者是把 $j$ 都加上 10000。

最后判断就好了，[代码](https://atcoder.jp/contests/abc274/submissions/35908243)并不难写。

---

