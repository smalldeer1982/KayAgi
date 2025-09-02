# [USACO04OPEN] Cave Cows 3

## 题目描述

约翰的 $ N $ ( $ 1 \leq N \leq 50000 $ )只牛在一个黑魃魃的洞里探险，他们只能通过叫声交流。

两只牛之间的曼哈顿距离决定了声音传播的时间。即牛1与牛2交流，需要的时间为
 $ |x_1-x_2|+|y_1-y_2| $ 。其中 $ -10^6 \leq x_1,x_2,y_1,y_2 \leq 10^6 $ 。

那任意一对牛之间交流时间的最大值为多少？

## 说明/提示

样例解释：

$ (2,7) $ 和 $ (8,1) $ 两点间的距离最大，为12。

## 样例 #1

### 输入

```
5
1 1
3 5
2 7
8 1
4 4```

### 输出

```
12```

# 题解

## 作者：Siyuan (赞：42)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Luogu 5098](https://www.luogu.org/problemnew/show/P5098)

约翰的 $n$ 只奶牛在一个洞里探险，他们只能通过叫声交流。用坐标 $(x_i,y_i)$ 表示第 $i$ 只牛的位置，两只牛之间的曼哈顿距离决定了声音传播的时间，即第 $i$ 只牛和第 $j$ 只牛交流，需要的时间为 $|x_i-x_j|+|y_i-y_j|$。求出任意一对牛之间交流需要的时间的最大值。

------

## Solution

由于 $i$ 和 $j$ 是无序的，我们强制 $x_i\ge x_j$，那么我们对 $y$ 进行分类讨论：

1. 如果 $y_i\ge y_j$，那么 $\texttt{原式}=x_i-x_j+y_i-y_j=(x_i+y_i)-(x_j+y_j)$。答案最大为 $\max_{x+y}-\min_{x+y}$。
2. 如果 $y_i<y_j$，那么 $\texttt{原式}=x_i-x_j-y_i+y_j=(x_i-y_i)-(x_j-y_j)$。答案最大为 $\max_{x-y}-\min_{x-y}$。

所以我们只需要维护 $x+y$ 和 $x-y$ 的最大值和最小值就行了。

**时间复杂度**：$O(n)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>

const int inf=1<<30;

int main() {
    int n,a=-inf,b=inf,c=-inf,d=inf;
    for(scanf("%d",&n);n--;) {
        int x,y;
        scanf("%d%d",&x,&y);
        a=std::max(a,x+y);
        b=std::min(b,x+y);
        c=std::max(c,x-y);
        d=std::min(d,x-y);
    }
    printf("%d\n",std::max(a-b,c-d));
    return 0;
}
```

---

## 作者：mrclr (赞：10)


看完题后突然想起jf巨佬的话：“看到曼哈顿距离就想转切比雪夫距离。”

于是我就转换了一下。

然后问题变成了求
$$max_{i, j \in n} \{ max \{ |x_i - x_j|, |y_i - y_j| \} \}$$

令差最大，只要分别找出$x, y$的最小值和最大值即可。
$O(n)$扫一遍啦。
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
#define In inline
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 5e4 + 5;
inline ll read()
{
	ll ans = 0;
	char ch = getchar(), last = ' ';
	while(!isdigit(ch)) {last = ch; ch = getchar();}
	while(isdigit(ch)) {ans = (ans << 1) + (ans << 3) + ch - '0'; ch = getchar();}
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
struct Node
{
	int x, y;
}t[maxn];

int main()
{
	n = read();
	for(int i = 1; i <= n; ++i) 
	{
		int x = read(), y = read();
		t[i] = (Node){x + y, x - y};
	}
	int Max = 1, May = 1, Mix = 1, Miy = 1;
	for(int i = 2; i <= n; ++i)
	{
		if(t[i].x < t[Mix].x) Mix = i;
		if(t[i].x > t[Max].x) Max = i;
		if(t[i].y < t[Miy].y) Miy = i;
		if(t[i].y > t[May].y) May = i;
	}
	write(max(t[Max].x - t[Mix].x, t[May].y - t[Miy].y)), enter;
	return 0;
}
```

---

## 作者：米奇奇米 (赞：10)

## 这道题目难度不是很大的，主要就是分类讨论。
### $1.1$题目意思
题目意思很简单，就是让你找出一对点对使得两点之间曼哈顿距离最大。
### $2.1$暴力大法
这道题目$(N<=5e4)$显然$O(n^2)$暴力不能过。
### $3.1$正解
这道题目难就难在分类讨论：

我们已经知道原式为：$|xi-xj|+|yi-yj|$

我们先来考虑几种情况：

$A.$当$xi>xj$以及$yi>yj$的时候，此时原式将会转换为：$xi-xj+yi-yj$。然后移项可得：$(xi+yi)-(xj+yj)$，要让这个柿子的结果尽量大，我们就要让$xi+yi$大，$xj+yj$尽量小，这个很好理解：**更大的减去更小的才能更大。**

$B.$当$xi<xj$以及$yi>yj$的时候，此时原式转换为：$-(xi-yi)+(xj-yj)$此时我们像情况$A$一样，让$xi-yi$尽量小，$xj-yj$尽量大。

最后只要比较$A,B$这两种情况谁大谁小就可以了：$ans=max(a-b,c-d)$，这样我们就将复杂度缩小到$O(n)$。
### $4.1$代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=5e4+5;
struct xjh {
	int x,y;
} num[maxn];
int n,a,b=1e12,c,d=1e12;
inline int read() {
	int sum=0,ff=1; char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		sum=sum*10+ch-48;
		ch=getchar();
	}
	return sum*ff;
}
int main() {
	n=read();
	for ( int i=1;i<=n;i++ ) {
		num[i].x=read(),num[i].y=read();
		a=max(a,num[i].x+num[i].y);
		b=min(b,num[i].x+num[i].y);
		c=max(c,num[i].x-num[i].y);
		d=min(d,num[i].x-num[i].y);
	}
	printf("%d\n",max(a-b,c-d));
	return 0;
}
```


---

## 作者：YLWang (赞：8)

本篇题解主要讲解卡常数。

好的我们看一下题目，一眼过去马上可以写出一个$O(n^2)$的大暴力，然后就可以过$89$分的数据了。

数据真水.jpg

代码：
```
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define INF (1 << 30) - 1
#define ll long long
#define reaD() read()
using namespace std;
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
int x[50005], y[50005];
signed main()
{
    int n = read();
    For(i, 1, n) {
        x[i] = read(), y[i] = read();
    } 
    int ans = 0;
    For(i, 1, n) {
        For(j, 1, n) {
            ans = max(abs(x[i] - x[j]) + abs(y[i] - y[j]), ans);
        }
    }
    cout << ans << endl;
    return 0;
}
```
发现卡卡常数应该能过，下面是几个技巧

- 2k的$pragma$头文件，可以加速一倍，但是为了规范性，我没有使用

- 把第二个循环的For(j, 1, n) 改为For(j, i+1, n).可以加快一倍。

- 由于$abs$函数非常的慢，我们可以先把原数组按照x排序，然后就可以省掉一个$abs$

- 由于$max$函数非常的慢，我们可以使用$if$来实现

然后就卡过了。

代码：
```
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define INF (1 << 30) - 1
#define ll long long
#define reaD() read()
using namespace std;
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
struct Node{
    int x, y;
}a[50005];
bool cmp(Node a, Node b) {
    return a.x < b.x;
}
signed main()
{
    int n = read();
    For(i, 1, n)
        a[i].x = read(), a[i].y = read();
    sort(a + 1, a + 1 + n, cmp); 
    int ans = 0;
    For(i, 1, n) {
        For(j, i+1, n) {
            int tmpans = a[j].x - a[i].x + abs(a[i].y - a[j].y);
            if(tmpans > ans) ans = tmpans;
        }
    }
    cout << ans << endl;
    return 0;
}
```
当然，题解末尾附赠给大家卡常头文件：
```cpp
#define _CRT_SECURE_NO_WARNINGS
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
```

希望大家可以汲取一些卡常数的技巧并在之后更好地运用！

---

## 作者：da32s1da (赞：6)

要使$|x_1-x_2|+|y_1-y_2|$最大，不妨设$x_1\ge x_2$。

当$y_1\ge y_2$时，$\text{原式}=x_1+y_1-(x_2+y_2)$，要使这个式子最大，就要用$max_{x+y}-min_{x+y}$。

当$y_1\le y_2$时，$\text{原式}=x_1-y_1-(x_2-y_2)$，要使这个式子最大，就要用$max_{x-y}-min_{x-y}$。

综上，答案为$\max(max_{x+y}-min_{x+y}\ ,\ max_{x-y}-min_{x-y})$。

```
#include<cstdio>
const int inf=1e7+9;
int n,x,y;
int a,b,c,d;
inline int max(int u,int v){return u>v?u:v;}
inline int min(int u,int v){return u<v?u:v;}
int main(){
	scanf("%d",&n);
	a=b=-inf;c=d=inf;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		a=max(a,x+y);
		c=min(c,x+y);
		b=max(b,x-y);
		d=min(d,x-y);
	}
	printf("%d\n",max(a-c,b-d));
}
```

---

## 作者：zhengrunzhe (赞：5)

~~大家好，我非常喜欢暴力数据结构，于是我就用K-D TREE过了这道题。(kdtree在做最近/远点对时确实很暴力)~~

~~众所周知 这是一道数据结构题~~

kdtree找最近/远点对的原理就是设置估价函数类似A*算法查找和某个点最近的点 for一遍所有点都查询一遍去最大/最小值就好了
```cpp
#include<cstdio>
#include<algorithm>
using std::abs;
using std::max;
using std::min;
using std::nth_element;
const int N=5e4+10,K=2,INF=1e6+10;
int n,f,ans;
struct point
{
    int d[K];
    inline const bool operator<(const point &p)const
    {
        return d[f]<p.d[f];
    }
    inline friend const int distance(const point &a,const point &b)
    {
        int dis=0;
        for (int i=0;i<K;i++)
            dis+=abs(a.d[i]-b.d[i]);
        return dis;
    }
}a[N];
template<int K>class KD_Tree
{
    private:
        struct tree
        {
            tree *son[2];
            point mn,mx,range;
            inline const void pushup()
            {
                for (int i=0;i<K;i++)
                    mn.d[i]=min(range.d[i],min(son[0]->mn.d[i],son[1]->mn.d[i])),
                    mx.d[i]=max(range.d[i],max(son[0]->mx.d[i],son[1]->mx.d[i]));
            }
            inline const int fmax(const point &x)
            {
                int f=0;
                for (int i=0;i<K;i++)
                    f+=max(abs(mn.d[i]-x.d[i]),abs(mx.d[i]-x.d[i]));
                return f;
            }
        }*root,memory_pool[N],*tail,*null;
        inline const void init()
        {
            tail=memory_pool;
            null=tail++;
            for (int i=0;i<K;i++)
                null->mn.d[i]=INF,
                null->mx.d[i]=-INF;
            root=null;
        }
        inline tree *spawn(const point &x)
        {
            tree *p=tail++;
            p->son[0]=p->son[1]=null;
            p->range=p->mn=p->mx=x;
            return p;
        }
        inline tree *build(int l,int r,int d)
        {
            if (l>r)return null;
            int mid=l+r>>1;f=d;
            nth_element(a+l,a+mid,a+r+1);
            tree *p=spawn(a[mid]);
            if (l==r)return p;
            p->son[0]=build(l,mid-1,(d+1)%K);
            p->son[1]=build(mid+1,r,(d+1)%K);
            return p->pushup(),p;
        }
        int mx;
        inline const void query(tree *p,const point &x)
        {
            mx=max(mx,distance(p->range,x));int f[2];
            for (int i=0;i<2;i++)f[i]=p->son[i]==null?-INF:p->son[i]->fmax(x);
            bool t=f[0]<=f[1];
            if (f[t]>mx)query(p->son[t],x);t^=1;
            if (f[t]>mx)query(p->son[t],x);
        }
    public:
        inline KD_Tree(){init();}
        inline const void build()
        {
            root=build(1,n,0);
        }
        inline const int query(const point &x)
        {
            return mx=0,query(root,x),mx;
        }
};
KD_Tree<K>kdt;
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        for (int j=0;j<K;j++)
            scanf("%d",&a[i].d[j]);
    kdt.build();
    for (int i=1;i<=n;i++)ans=max(ans,kdt.query(a[i]));
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Heartlessly (赞：5)

## Description

给定 $n$ 个点，每个点的坐标为 $(x,y)$，求曼哈顿距离的最大点对，输出这个最大值。

$(1 \leq n \leq 5 \times 10^4,-10^6 \leq x,y \leq 10^6)$

## Solution 1

根据题意，对于式子 $\left | x_1-x_2\right| +\left | y_1-y_2\right| $，我们可以分成四种情况考虑：

第一种情况：$x_1 - x_2 \geq 0,y_1 - y_2 \geq 0$

![VDSc36.png](https://s2.ax1x.com/2019/06/08/VDSc36.png)

第二种情况：$x_1 - x_2 < 0,y_1 - y_2 \geq 0$

![VDSWuD.png](https://s2.ax1x.com/2019/06/08/VDSWuD.png)

第三种情况：$x_1 - x_2 \geq 0,y_1 - y_2 < 0$

![VDS2jO.png](https://s2.ax1x.com/2019/06/08/VDS2jO.png)

第四种情况：$x_1 - x_2 < 0,y_1 - y_2 < 0$

![VDSfDe.png](https://s2.ax1x.com/2019/06/08/VDSfDe.png)

每种情况的答案要么只与 $x+y$ 的值有关，要么只与 $x-y$ 的值有关，所以最后的答案为
$$
\max \begin{Bmatrix} \max \begin{Bmatrix} x_i + y_i \end{Bmatrix} - \min \begin{Bmatrix} x_i + y_i \end{Bmatrix},\max \begin{Bmatrix} x_i - y_i \end{Bmatrix} - \min \begin{Bmatrix} x_i - y_i \end{Bmatrix}  \end{Bmatrix}
$$

## Code 1

```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

int n, x, y, minx = 0x7fffffff, maxx, miny = 0x7fffffff, maxy;

int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(x), read(y);
        minx = min(minx, x + y), maxx = max(maxx, x + y);
        miny = min(miny, x - y), maxy = max(maxy, x - y);
    }
    write(max(maxx - minx, maxy - miny));
    putchar('\n');
    return 0;
}
```

## Solution 2

我们考虑将题目所求的 **曼哈顿距离** 转化为 **切比雪夫距离**，即把每个点的坐标 $(x,y)$ 变为 $(x + y, x - y)$ 。

所求的答案就变为 $\max \begin{Bmatrix} \max\begin{Bmatrix} \left | x_i - x_j\right| ,\left | y_i - y_j\right| \end{Bmatrix} \end{Bmatrix}$ 。

在所有点中，横坐标之差的最大值和纵坐标之差的最大值都有可能成为答案，所以我们只需要预处理出 $x,y$ 的最大值和最小值即可。时间复杂度为 $O(n)$ 。

## Code 2

```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

int n, x, y, a, b, minx = 0x7fffffff, maxx, miny = 0x7fffffff, maxy;

int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a), read(b);
        x = a + b, y = a - b;
        minx = min(minx, x), maxx = max(maxx, x);
        miny = min(miny, y), maxy = max(maxy, y);
    }
    write(max(maxx - minx, maxy - miny));
    putchar('\n');
    return 0;
}
```



---

## 作者：_cmh (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/P5098)

## $\texttt{Description}$

找到两个点，使其曼哈顿距离最大。

## $\texttt{Solution}$

本题关键是化简曼哈顿距离的式子，对其分类讨论。

$$|x_i-x_j|+|y_i-y_j|$$

第一种情况：

$$=(x_i-x_j)+(y_i-y_j)=(x_i+y_i)-(x_j+y_j)$$

易得，最大值即为 $\max_{x_i+y_i}-\min_{x_j+y_j}$。

第二种情况：

$$=(x_i-x_j)-(y_i-y_j)=(x_i-y_i)-(x_j-y_j)$$

易得，最大值即为 $\max_{x_i-y_i}-\min_{x_j-y_j}$。

综上两种情况，我们求出 
$$\max_{x_i+y_i},\min_{x_j+y_j},\max_{x_i-y_i},\min_{x_j-y_j}$$

即可求出答案。

注意初始化时，需要将统计变量初始为**极大值**和**极小值**。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;
int main(){
	int T;
	scanf("%d",&T);
	int a=-INF,b=-INF,c=INF,d=INF;
	while(T--){
		int x,y;
		scanf("%d%d",&x,&y);
		a=max(a,x+y);
		b=max(b,x-y);
		c=min(c,x+y);
		d=min(d,x-y);
	}
	printf("%d",max(a-c,b-d));
	return 0;
}
```

感谢观看。

---

## 作者：Huang_Yuhan (赞：1)

# 题目描述：

约翰的 $N ( 1\leqslant N\leqslant50000)$只牛在一个黑魃魃的洞里探险，他们只能通过叫声交流。

两只牛之间的曼哈顿距离决定了声音传播的时间。即牛1与牛2交流，需要的时间为 $|x_1-x_2|+|y_1-y_2|$ 。其中 $ -10^6 \leqslant x_1,x_2,y_1,y_2 \leqslant 10^6 $

那任意一对牛之间交流时间的最大值为多少？

# 解：

翻译题目：给出曼哈顿坐标系下的$n$个点，求最远的两个点的曼哈顿距离。

看到曼哈顿距离和最大值，直接转换坐标系。

不懂的百度或者翻我博客.

将所有点转换成切比雪夫坐标系下。

最后的答案就是：

$$ans=\max\{\max\{|x_i-x_j|,|y_i-y_j|\}\}$$

其中$1\leqslant i,j\leqslant N$且$i\not=j$

由于$\max$有结合律。

所以展开既得：

$$ans=\max\{\max\{|x_i-x_j|\},\max\{|y_i-y_j|\}\}$$

所以开四个变量维护$xmin,xmax,ymin,ymax$就行了。

时间复杂度为$O(n)$
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=50000+5;
int xmin=1e9,xmax=-1e9,ymin=1e9,ymax=-1e9;

int main()
{
	int n;
	int x,y;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		xmin=min(xmin,x+y);
		xmax=max(xmax,x+y);
		ymin=min(ymin,x-y);
		ymax=max(ymax,x-y);
	}
	cout<<max(xmax-xmin,ymax-ymin);
}
```

---

## 作者：Mickey_jj (赞：1)

一般人正常的做法：


```cpp
#include<bits/stdc++.h>
using namespace std;
struct n{
    int x,y;
}a[50001];
int main() {
    int n,maxn=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    	cin>>a[i].x>>a[i].y;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            maxn=max(maxn,abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y));	
        }
    }
    cout<<maxn;
    return 0;
}

```
然而......[额P18882200](https://www.luogu.org/recordnew/show/18882200)

为啥子会t呢？因为O(n^2)嘛。n<=50000，肯定超时啊。
正解：
我们都知道，ans=max(max(x+y)-min(x+y),max(x-y)-min(x-y)),


```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e8+2;
int a=-inf,c=-inf,d=inf,b=inf;
int main(){
    int n,x,y;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x>>y;
        a=max(a,x+y);//max(x+y)
        b=min(b,x+y);//min(x+y)
        c=max(c,x-y);//max(x-y)
        d=min(d,x-y);//min(x-y)
    }
    cout<<max(a-b,c-d);
    return 0;
}
```

---

## 作者：zhl001 (赞：0)

### 题解里面有很多解释了（在此不多bb）：

#### 这里只是解释一点：

![参见楼上dl](https://cdn.luogu.com.cn/upload/pic/64544.png)

对于公式一和二，若不符合条件就是yi<yj（对于公式一来说）那么后面就会是加一个负值，一定不是最大；

不多说：代码：

```
#include<bits/stdc++.h>
using namespace std;
int a=-1,b=0x7f7f7f7f,c=-1,d=0x7f7f7f7f,ans,n,x,y;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		a=max(a,x+y);
		b=min(b,x+y);
		c=max(c,x-y);
		d=min(d,x-y);
	}
	ans=max(a-b,c-d);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：badgalriri (赞：0)

### 这算贪心吗emm
先上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
struct pap{
	int x,y;
}c,bm,mb,bb,mm;
int main()
{
	int i,a1,a2;
	scanf("%d",&n);
	bm.y=mb.x=mm.x=mm.y=1e9;
	bm.x=mb.y=bb.x=bb.y=-1e9;
	for(i=1;i<=n;i++){
		scanf("%d%d",&c.x,&c.y);
		if(bm.x-bm.y<c.x-c.y){
			bm.x=c.x;
			bm.y=c.y;
		}
		if(mb.y-mb.x<c.y-c.x){
			mb.x=c.x;
			mb.y=c.y;
		}
		if(bb.x+bb.y<c.x+c.y){
			bb.x=c.x;
			bb.y=c.y;
		}
		if(mm.x+mm.y>c.x+c.y){
			mm.x=c.x;
			mm.y=c.y;
		}
	}
	a1=bm.x-mb.x+mb.y-bm.y;
	a2=bb.x-mm.x+bb.y-mm.y;
	printf("%d",a1>a2?a1:a2);
	return 0;
}
```

由文中“∣x 
1
​	 −x 
2
​	 ∣+∣y 
1
​	 −y 
2
​	 ∣”可以立马想到，分成两种情况讨论（默认x1>x2）：

①y1>y2时：只要令x1+y1最大,x2+y2最小就好了。所以要找出横纵坐标和最大和最小的坐标：
```cpp
		if(bb.x+bb.y<c.x+c.y){
			bb.x=c.x;
			bb.y=c.y;
		}
		if(mm.x+mm.y>c.x+c.y){
			mm.x=c.x;
			mm.y=c.y;
		}
```


②y1<y2时：为了让x1-x2的绝对值最大，x1越大越好，x2越小越好。

为了让y1-y2的绝对值最大，y1越小越好，y2越大越好。

所以找出兼具上述条件的两个坐标：
```cpp
		if(bm.x-bm.y<c.x-c.y){
			bm.x=c.x;
			bm.y=c.y;
		}
		if(mb.y-mb.x<c.y-c.x){
			mb.x=c.x;
			mb.y=c.y;
		}
```



然后最后在比较一下哪个情况的距离最大就好了。

---

