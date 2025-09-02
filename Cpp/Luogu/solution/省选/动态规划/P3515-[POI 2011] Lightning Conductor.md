# [POI 2011] Lightning Conductor

## 题目描述

Progressive climate change has forced the Byteburg authorities to build a huge lightning conductor    that would protect all the buildings within the city.

These buildings form a row along a single street, and are numbered from ![](http://main.edu.pl/images/OI18/pio-en-tex.1.png) to ![](http://main.edu.pl/images/OI18/pio-en-tex.2.png).

The heights of the buildings and the lightning conductor are non-negative integers.

Byteburg's limited funds allow construction of only a single lightning conductor.

Moreover, as you would expect, the higher it will be, the more expensive.

The lightning conductor of height ![](http://main.edu.pl/images/OI18/pio-en-tex.3.png) located on the roof of the building ![](http://main.edu.pl/images/OI18/pio-en-tex.4.png) (of height ![](http://main.edu.pl/images/OI18/pio-en-tex.5.png))    protects the building ![](http://main.edu.pl/images/OI18/pio-en-tex.6.png) (of height ![](http://main.edu.pl/images/OI18/pio-en-tex.7.png)) if the following inequality holds:

![](http://main.edu.pl/images/OI18/pio-en-tex.8.png)        where ![](http://main.edu.pl/images/OI18/pio-en-tex.9.png) denotes the absolute value of the difference between ![](http://main.edu.pl/images/OI18/pio-en-tex.10.png) and ![](http://main.edu.pl/images/OI18/pio-en-tex.11.png).

Byteasar, the mayor of Byteburg, asks your help.

Write a program that, for every building ![](http://main.edu.pl/images/OI18/pio-en-tex.12.png), determines the minimum height    of a lightning conductor that would protect all the buildings if it were put    on top of the building ![](http://main.edu.pl/images/OI18/pio-en-tex.13.png).




## 样例 #1

### 输入

```
6
5
3
2
4
2
4```

### 输出

```
2
3
5
3
5
4```

# 题解

## 作者：HoshiuZ (赞：93)

设$w(x,y)$是定义在整数集合上的二院函数。若对于定义域上的任意整数$a,b,c,d$，其中$a\le b\le c\le d$，都有$w(a,d)+w(b,c)\ge w(a,c)+w(b,d)$成立，则称函数$w$满足**四边形不等式**。
# 定理

设$w(x,y)$是定义在整数集合上的二元函数。若对于定义域上的任意整数$a,b$，其中$a<b$，都有$w(a,b+1)+w(a+1,b)\ge w(a,b)+w(a+1,b+1)$成立，则函数$w$满足四边形不等式。

## 证明

对于$a<c$，有$w(a,c+1)+w(a+1,c)\ge w(a,c)+w(a+1,c+1)$

对于$a+1<c$，有$w(a+1,c+1)+w(a+2,c)\ge w(a+1,c)+w(a+2,c+1)$

两式相加，得到$w(a,c+1)+w(a+2,c)\ge w(a,c)+w(a+2,c+1)$

以此类推，对于任意的$a\le b\le c$，有$w(a,c+1)+w(b,c)\ge w(a,c)+w(b,c+1)$

同理，对任意的$a\le b\le c\le d$，有$w(a,d)+w(b,c)\ge w(a,c)+w(b,d)$

# 决策单调性

在状转方程$f[i]=\min\{f[j]+w(j,i)\},j\in[0,i)$中，若函数$w$满足四边形不等式，则$f$具有决策单调性。

## 证明

定义$p[i]$表示$i$的最优决策点。

$\forall i\in[1,n],\forall j\in[0,p[i]-1]$，根据$p[i]$为$i$的最优决策点，则有
$$
f[p[i]]+w(p[i],i)\le f[j]+w(j,i)
$$
$\forall i'\in[i+1,n]$，因为$w$满足四边形不等式，则有
$$
w(j,i')+w(p[i],i)\ge w(j,i)+w(p[i],i')
$$
移项，可得
$$
v(p[i],i')-w(p[i],i)\le w(j,i')-w(j,i)
$$
与第一个不等式相加，可得
$$
f[p[i]]+w(p[i],i')\le f[j]+w(j,i')
$$
即$i'$的最优决策点一定大于等于$p[i]$。故$f$具有决策单调性。

## 应用

那么知道其有决策单调性后，有什么应用呢？

既然其有决策单调性，定义$p[i]$表示$i$的最优决策点，则$p$内一定是非严格单调递增的。

那么根据此性质，满足决策单调性的题目主要有两种处理手法。

### 方法一：单调队列

可以用单调队列维护决策集合$p$。

当求出一个新的$f[i]$时，考虑$i$可以作为哪些$f[i']\ (i'>i)$的最优决策。根据决策单调性，我们一定可以找到一个位置，在该位置之前，$p$内存储的决策都比$i$要优，其后都比$i$差。于是便可以将该位置及其后面的部分全部变为$i$，即此时它们的最优决策均为$i$。

一个位置一个位置的修改效率很低，所以可以建立一个队列，代替$p$。队列中保存三个量$(j,l,r)$，表示$p[l$~$r]$的值都是$j$。

对于每个$i\in[1,n]$，执行以下操作：

1. 检查队头：设队头为$(j_0,l_0,r_0)$，若$r_0=i-1$，则删除队头（因为队头不需要了，$f[i]$之前的值已经被求出）。否则则令$l_0=i$。

2. 取队头保存的最优决策$j$进行状态转移，计算出$f[i]$。

3. 尝试插入新决策$i$，步骤如下

   (1) 取出队尾，即为$(j_t,l_t,r_t)$

   (2) 若对于$f[l_t]$来说，$i$是比$j_t$更优的决策，即$f[i]+w(i,l_t)\le f[j_t]+w(j_t,l_t)$，记$pos=l_t$，删除队尾，返回步骤(1)。

   (3) 若对于$f[r_t]$来说，$i$是比$j_t$更优的决策，即$f[j_t]+w(j_t,r_t)\le f[i]+w(i,r_t)$，去往步骤(5)。

   (4) 否则，则在$[l_t,r_t]$上二分查找出位置$pos$，在此之前决策比$i$优，在此之后决策$i$更优，将$[l_t,r_t]$修改为$[l_t,pos-1]$，去往步骤(5)。

   (5) 把三元组$(i,pos,n)$插入队尾。

时间复杂度$O(n\ log\ n)$。

### 方法二：分治

假设已知$[l,r]$的最优决策在$[L,R]$上。

定义$mid=\frac{l+r}{2}$，设$dp[mid]$的最优决策为$p$，根据决策单调性，可知$[l,mid-1]$的最优决策在$[L,p]$内，$[mid+1,r]$的最优决策在$[p,R]$内。

于是将问题分割成了同类型的规模更小的问题，便可递归分治。

时间复杂度$O(n\ log\ n)$

## 例题 [POI2011]Lightning Conductor

给定一个长度为$ n$的序列$\{a_n\}$，对于每个$i\in [1,n]$，求出一个最小的非负整数$p$，使得 $\forall j\in[1,n]$，都有$a_j\le a_i+p-\sqrt{|i-j|}$。

### 数据范围

$1 \le n \le 5\times 10^{5}$，$0 \le a_i \le 10^{9}$。

### 链接

[[POI2011]Lightning Conductor](https://www.luogu.com.cn/problem/P3515)

### 思路

$$
a_j \le a_i+p-\sqrt{|i-j|},\forall j\in[1,n] 
$$
$$
p \ge a_j+\sqrt{|i-j|}-a_i,\forall j\in[1,n]
$$

而$p$为非负整数，则
$$
p=\lceil \max\{ a_j+\sqrt{|i-j|}\}\rceil-a_i,\forall j\in[1,n]
$$
那么问题便转变为求$\lceil \max\{ a_j+\sqrt{|i-j|}\}\rceil,\forall j\in[1,n]$。

可以考虑做两次，正做一次，将序列翻转再做一次，结果取两次的最大值，这样便可以去掉绝对值
$$
\lceil \max\{ a_j+\sqrt{i-j}\}\rceil,\forall j\in[1,i)
$$
定义$dp[i]=\lceil \max\{ a_j+\sqrt{i-j}\}\rceil$。

此处的$w(j,i)$即为$\sqrt{i-j}$。

定义$a+1<c$。
$$
w(a,c)=\sqrt{c-a}
$$

$$
w(a+1,c)=\sqrt{c-a-1}
$$

$$
w(a,c+1)=\sqrt{c-a+1}
$$

$$
w(a+1,c+1)=\sqrt{c-a}
$$

则
$$
w(a,c+1)+w(a+1,c)-[w(a,c)+w(a+1,c+1)]=\sqrt{c-a-1}+\sqrt{c-a+1}-2\sqrt{c-a}
$$


令$d=c-a$，原式变为
$$
\sqrt{d-1}+\sqrt{d+1}-2\sqrt{d}=(\sqrt{d+1}-\sqrt{d})-(\sqrt{d}-\sqrt{d-1})
$$
而函数$f(x)=\sqrt{x}-\sqrt{x-1}$单调递减

则该式恒小于$0$。

即$w(a,c+1)+w(a+1,c)\le w(a,c)+w(a+1,c+1)$。

可推广到对于$a\le b\le c\le d$，$w(a,d)+w(b,c) \le w(a,c)+w(b,d)$。

可以发现，这东西与四边形不等式的符号相反。将上面的证明过程符号取反（因为本题求的是$\max$），便可证明$dp$满足决策单调性。

于是采用上面两种方法实现即可。

由于函数$sqrt$较慢，且本题反复调用，可提前预处理出$\sqrt{1}$~$\sqrt{n}$。

### 代码（单调队列）

```cpp
#include<bits/stdc++.h>
#define N 500010

using namespace std;

int n,head,tail,a[N];
double dp[N],sqr[N];
struct node{
	int l,r,p;
}q[N];

double w(int j,int i) {
	return double(a[j])+sqr[i-j];
}

int binary_search(int t,int x) {
	int ans=q[t].r+1,l=q[t].l,r=q[t].r;
	while(l<=r) {
		int mid=l+r>>1;
		if(w(q[t].p,mid)<=w(x,mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}

void insert(int i) {
	q[tail].l=max(q[tail].l,i);
	while(head<=tail&&w(i,q[tail].l)>=w(q[tail].p,q[tail].l)) tail--;
	if(head>tail) {
		q[++tail].l=i;
		q[tail].r=n;
		q[tail].p=i;
	}
	else {
		int pos=binary_search(tail,i);
		if(pos>n) return ;
		q[tail].r=pos-1;
		q[++tail].l=pos;
		q[tail].r=n;
		q[tail].p=i;
	}
}

void work() {
	head=1,tail=0;
	for(int i=1;i<=n;i++) {
		insert(i);
		if(head<=tail&&q[head].r<i) head++;
		else q[head].l=i;
		dp[i]=max(dp[i],w(q[head].p,i));
	}
}

int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		sqr[i]=sqrt(i);
	}
	
	work();
	for(int i=1;i<=n/2;i++) swap(a[i],a[n-i+1]),swap(dp[i],dp[n-i+1]);
	work();
	
	for(int i=n;i>=1;i--) cout<<(int)ceil(dp[i])-a[i]<<endl;
	
	return 0;
}
```

### 代码（分治）

```cpp
#include<bits/stdc++.h>
#define N 500010

using namespace std;

int n,a[N];
double dp[N],sqr[N];

double w(int j,int i) {
	return double(a[j])+sqr[i-j];
}

void work(int l,int r,int L,int R) {
	if(l>r) return ;
	int mid=l+r>>1,p;
	double maxn=0;
	for(int i=L;i<=min(mid,R);i++) {
		if(w(i,mid)>maxn) maxn=w(i,mid),p=i;
	}
	dp[mid]=max(dp[mid],maxn);
	work(l,mid-1,L,p);
	work(mid+1,r,p,R);
}

int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		sqr[i]=sqrt(i);
	}
	
	work(1,n,1,n);
	for(int i=1;i<=n/2;i++) swap(a[i],a[n-i+1]),swap(dp[i],dp[n-i+1]);
	work(1,n,1,n);
	
	for(int i=n;i>=1;i--) cout<<(int)ceil(dp[i])-a[i]<<endl;
	
	return 0;
}
```

# 参考资料

《算法竞赛进阶指南》

[【学习笔记】动态规划—各种 DP 优化](https://www.cnblogs.com/Xing-Ling/p/11317315.html)



---

## 作者：FlashHu (赞：57)

疯狂%%%几个月前就秒了此题的Tyher巨佬

借着这题总结一下决策单调性优化DP吧。蒟蒻觉得用数形结合的思想能够轻松地理解它。

首先，题目要我们求所有的$p_i$，那么把式子变一下

$$p_i\ge a_j-a_i+\sqrt{|i-j|}$$

$$p_i=\max\limits_{j=1}^n\{a_j+\sqrt{|i-j|}\}-a_i$$

绝对值看着很不爽，我们把它拆开

$$p_i=\max(\max_{j=1}^i\{a_j+\sqrt{i-j}\},\max_{j=i}^n\{a_j+\sqrt{j-i}\})-a_i$$

单独看前一部分

$$p_i=\max_{j=1}^i\{a_j+\sqrt{i-j}\}-a_i$$

很明显是个要用决策单调性优化的式子。把序列翻转以后，后一部分的算法和前面是一样的，所以只讨论前一部分了。

对于每个$j$，把$a_j+\sqrt{i-j}$看成关于$i$的函数$f_j$。我们要做的就是在所有$j\leq i$的函数中找到最值。比如样例：

![](https://cdn.luogu.com.cn/upload/pic/28914.png)

观察发现，真正有用的函数只有最上面那个！然而实际情况比这个稍复杂些。sqrt的增速是递减的，因此可能存在一个$j$比较小的函数，在某一时刻被$j$比较大的函数反超。我们大概需要维护这样的若干个函数：

![](https://cdn.luogu.com.cn/upload/pic/28913.png)

我们用队列实现决策二分栈（不懂的可以参考一下[蒟蒻的blog](https://www.cnblogs.com/flashhu/p/9480669.html)），按$j$从小到大依次维护这些函数。显然，对于其中任意两个相邻的函数$f_t,f_{t+1}$，它们都有一个临界值$k_{t,t+1}$。显然序列中的$k_{1,2},k_{2,3}...$也要严格递增。否则，如果$k_{t,t+1}\ge k_{t+1,t+2}$，可以想象$f_{t+1}$根本没有用。

先`for`一遍$i$，我们尝试着把$f_i$加入队列。这时候为了保证$k$递增，设队尾决策为$t$，我们判断，如果$k_{t-1,t}\ge k_{t,i}$（此时会有$f_t(k_{t-1,t})\le f_i(k_{t-1,t})$），那么$t$没用，出队。

该出去的都出去后，$i$就可以加入队尾了。这时候可以来求$p_i$了。我们检查一下队首决策$h$，如果$t_{h,h+1}\le i$，说明$h$的巅峰时刻已经过去，出队。最后队首就是所有函数中的最大值。

貌似并没有用到什么三元组啊qwq

update:感谢孤独·粲泽的指正，二分上下界确实该调调

不过还是没有用到什么三元组啊qwq，蒟蒻之前都把临界值$k$存下了，直接用就可以啦

```cpp
#include<bits/stdc++.h>
#define RG register
#define R RG int
#define G if(++ip==iend)fread(ip=buf,1,N,stdin)
#define calc(i,j) a[j]+sq[i-j]//计算函数值
using namespace std;
const int N=5e5+9;
char buf[N],*iend=buf+N,*ip=iend-1;
int n,a[N],q[N],k[N];
double p[N],sq[N];
inline int in(){
    G;while(*ip<'-')G;
    R x=*ip&15;G;
    while(*ip>'-'){x*=10;x+=*ip&15;G;}
    return x;
}
inline void chkmx(RG double&x,RG double y){
    if(x<y)x=y;
}
inline int bound(R x,R y){//二分临界值k
    R l=y,r=k[x]?k[x]:n,m,ret=r+1;//控制二分上下界
    while(l<=r){
        m=(l+r)>>1;
        if(calc(m,x)<=calc(m,y))
            ret=m,r=m-1;
        else l=m+1;
    }
    return ret;
}
void work(){
    for(R h=1,t=0,i=1;i<=n;++i){
        while(h<t&&calc(k[t-1],q[t])<calc(k[t-1],i))--t;//维护k单调
        k[t]=bound(q[t],i);q[++t]=i;
        while(h<t&&k[h]<=i)++h;//将已经不优的决策出队
        chkmx(p[i],calc(i,q[h]));//因为做两遍所以取max
    }
}
int main(){
    n=in();
    R i,j;
    for(i=1;i<=n;++i)
        a[i]=in(),sq[i]=sqrt(i);
    work();
    for(i=1,j=n;i<j;++i,--j)//序列翻转
        swap(a[i],a[j]),swap(p[i],p[j]);
    memset(k,0,(n+1)<<2);
    work();
    for(R i=n;i;--i)//翻转过了所以要倒着输出
        printf("%d\n",max((int)ceil(p[i])-a[i],0));
    return 0;
}
```

---

## 作者：Alex_Wei (赞：30)

> [P3515 [POI2011] Lightning Conductor](https://www.luogu.com.cn/problem/P3515)

**线性做法！**

题目相当于对每个 $i$ 求 $f_i = \max\limits_{j = 1} ^ n a_j + \lceil\sqrt {|i - j|} \rceil$。分成 $j < i$ 和 $j > i$ 分别求解，考虑 $j < i$ 的情况。

因为贡献函数 $f = \sqrt x$ 二阶导恒为负且求最大值，所以前面的决策会被后面的决策反超，具有决策单调性。这样，我们可以通过二分队列优化 $\max\limits_{j = 1} ^ {i - 1} a_j + \lceil\sqrt {|i - j|} \rceil$ 的求解。时间复杂度 $\mathcal{O}(n\log n)$。

我们发现二分队列最耗时间的部分只有二分反超点。因为本题要求的式子较特殊，我们可以 $\mathcal{O}(1)$ 计算反超点。设两个决策点 $k < j$，我们希望求出最小的 $i > j$ 使得 $k\to i$ 劣于 $j\to i$。
$$
\begin{aligned}
a_k + \sqrt {i - k} & < a_j + \sqrt {i - j} \\
\sqrt {i - k} - \sqrt{i - j} & < a_j - a_k
\end{aligned}
$$
设 $d = a_j - a_k$。当 $d \leq 0$ 时，上式恒不成立，$i$ 不存在。因此 $d > 0$。
$$
\begin{aligned}
\sqrt{i - k} & < d + \sqrt{i - j} \\
i - k & < d ^ 2 + i - j + 2d \sqrt{i - j} \\
j - k - d ^ 2 & < 2d \sqrt{i - j}
\end{aligned}
$$
当 $j - k - d ^ 2 \leq 0$，即 $j - k \leq d ^ 2$ 时，上式恒成立，$j$ 一定会把 $k$ 弹出而不会进入二分反超点的过程。因此 $j - k > d ^ 2$。根据实际意义也容易理解，当 $a_j$ 过大时，$a_k\to j$ 甚至不如 $a_j$。

不等号两侧同时平方。设 $v = \dfrac {(j - k - d ^ 2) ^ 2} {4d ^ 2}$，则 $v < i - j$，即 $i > j + v$。这样，我们 $\mathcal{O}(1)$ 得到反超点 $j + \lfloor v\rfloor + 1$。时间复杂度 $\mathcal{O}(n)$。

获得了 Luogu 和 LOJ 最优解（2022.10.27）。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using ld = long double;
// using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using us = unsigned short;
// using uint = unsigned int;
using ull = unsigned long long;
char buf[1 << 21], *p1 = buf, *p2 = buf, obuf[1 << 25], *O = obuf;
#define gc (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
#define pc(x) (*O++ = x)
inline int read() {
  int x = 0;
  char s = gc;
  while(!isdigit(s)) s = gc;
  while(isdigit(s)) x = x * 10 + s - '0', s = gc;
  return x;
}
inline void print(int x) {
  if(x >= 10) print(x / 10);
  pc(x % 10 + '0');
}
bool Mbe;
constexpr int N = 5e5 + 5;
int n, a[N], f[N];
double sqr[N];
struct dat {int p, l, r;} q[N];
double get(int u, int v) {return a[u] + sqr[v - u];}
int hd, tl;
void solve() {
  f[1] = max(f[1], a[1]);
  q[hd = tl = 0] = {1, 1, n};
  for(int i = 2; i <= n; i++) {
    if(q[hd].r < i) hd++;
    q[hd].l = i;
    while(hd <= tl && get(q[tl].p, q[tl].l) < get(i, q[tl].l)) tl--;
    if(hd > tl) q[hd = tl = 0] = {i, i, n};
    else {
      int k = q[tl].p, j = i, d = a[j] - a[k];
      ll pos;
      if(d <= 0) pos = q[tl].r + 1;
      else {
        ll v = j - k - d * d;
        pos = j + v * v / (d * d << 2) + 1;
      }
      if(pos <= n) q[tl].r = pos - 1, q[++tl] = {i, pos, n};
    }
    f[i] = max(f[i], (int) ceil(get(q[hd].p, i)));
  }
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n;
  for(int i = 1; i <= n; i++) sqr[i] = sqrt(i);
  for(int i = 1; i <= n; i++) a[i] = read();
  solve();
  reverse(a + 1, a + n + 1);
  reverse(f + 1, f + n + 1);
  solve();
  for(int i = n; i; i--) print(f[i] - a[i]), pc('\n');
  cerr << TIME << " ms\n";
  return fwrite(obuf, 1, O - obuf, stdout), 0;
}
/*
2022/10/27
author: Alex_Wei
start coding at 
finish debugging at 
*/
```

---

## 作者：QAQ_陌上花开 (赞：29)

考虑N^2大暴力
ans[i]=max(a[j]+sqrt(|i-j|)-a[i] (1<=j<=n)

把绝对值拆开：

ans[i]=max(a[j]+sqrt(i-j))-a[i] (1<=j<=i)

ans[i]=max(a[j]+sqrt(j-i))-a[i] (i<j<=n)

上面两个式子显然比较对称，我们可以考虑先正着做一遍再倒着做一遍

打表课证明对于f[i]的最优决策点g[i]是单调递增的，分治即可

solve(l,r,L,R)表示f[l]~f[r]的最优决策点在L~R

令mid=（l+r）/2,O（n）扫一遍取到g[mid]

继续分治

solve（l,mid-1,L,g[mid])

solve (mid+1,r,g[mid],R)

代码如下:
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
long double f1[6000000],f2[6000000];
long long a[6000000];
long long read()
{
	long long ret(0);
	char ch=getchar();
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-48;
		ch=getchar();
	}
	return ret;
}
void solve1(int L,int R,int l,int r)
{
	if (L>R) return;
	int mid=(L+R)>>1,g(0);
	long double tmp(0);
	f1[mid]=a[mid];
	for (int i=l;i<=min(r,mid);i++)
	{
		tmp=a[i]+sqrt(double(mid-i));
		if (tmp>f1[mid]) f1[mid]=tmp,g=i;
	}
	if (g==0) g=mid; f1[mid]-=a[mid];
	solve1(L,mid-1,l,g); 
	solve1(mid+1,R,g,r);
}
void solve2(int L,int R,int l,int r)
{
	if (L>R) return ;
	int mid=(L+R)>>1,g(0);
	long double tmp(0);
	f2[mid]=a[mid];
	for (int i=r;i>=max(mid,l);i--)
	{
		tmp=a[i]+sqrt(double(i-mid));
		if (tmp>f2[mid]) f2[mid]=tmp,g=i;
	}
	if (g==0) g=mid; f2[mid]-=a[mid];
	solve2(L,mid-1,l,g);
	solve2(mid+1,R,g,r);
}
int main()
{
	int n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	solve1(1,n,1,n);
	solve2(1,n,1,n);
	for (int i=1;i<=n;i++)
	printf("%lld \n",(long long)ceil(max(f1[i],f2[i])));
	return 0;
}
```


---

## 作者：juju527 (赞：18)

### 前置知识
一点基本的推式子能力（大概是道决策单调性优化dp好题）

### $\texttt{Solution}$

考虑题面中奇怪的 $a_j\leq a_i+p-\sqrt{|i-j|}$

把 $p$ 单独放一边

$a_j-a_i+\sqrt{|i-j|}\leq p$

我们要求 $p$ 的最小值

即对于每个 $i$ 求 $\max_{j=1}^n(a_j-a_i+\sqrt{|i-j|})$

考虑把它分两部分算，分成 $j\leq i$ 和 $j \geq i$ 两种

第二种情况我们只要把区间翻转一下就行了，故这里只考虑第一种情况

$dp_i=\max_{j=1}^i(a_j-a_i+\sqrt{|i-j|})$

我简单称 $a_j-a_i+\sqrt{|i-j|}$ 为j的权值

这就是我们的dp式了，我们称每个j为一个**决策点**

我们设 $p_i$ 表示i点的最优决策点

考虑已知 $p_i$ ，得到 $p_{i+1}$ 的情况

对于 $a_j-a_i$ 这个部分的值，每个决策点的权值差是不变的(对于两决策点j,k其权值差为 $a_j-a_k$ ，与i无关 ）

我们只要考虑 $\sqrt{|i-j|}$ 变到 $\sqrt{|i+1-j|}$ 的权值变化

我们易知 $a<b$ 则 $\sqrt{a}-\sqrt{a-1}>\sqrt{b}-\sqrt{b-1}$

对于决策点j,k(j<k<=i)

其权值变化量 

$\Delta v_j=\sqrt{|i+1-j|}-\sqrt{|i-j|}$

$\Delta v_k=\sqrt{|i+1-k|}-\sqrt{|i-k|}$

又 $i+1-j>i+1-k$

故 $\Delta v_j<\Delta v_k$

那么对于 $j<p_i$ 的决策点会更加不如 $p_i$ 点，我们可以得到 $p_i<=p_{i+1}$

那么我们已经得到了这个优越的**决策单调性**，怎么用呢？

考虑分治解决此类我们对dp式子没有好办法只能扫决策点的题目

具体做法如下：

1. 对于一个区间[l,r]，有一个决策点范围[x,y]

2. 把[l,r]切两半找到一个mid

3. 扫一遍[x,y]求出mid的dp值，找到mid的决策点

4. 分治区间[l,mid-1]，决策点范围[x,p]

5. 分支区间[mid+1,r]，决策点范围[p,y]

时间复杂度分析如下：

递归的每一层扫完的决策点范围是 $O(n)$ 的

$T(l,r,x,y)=T(l,mid-1,x,p)+T(mid+1,r,p,y)+y-x+1$

$T(1,n,1,n)=O(nlogn)$

完结撒花（虽然说了很多，但代码很短）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=5e5+5;
const double eps=1e-9;
int a[maxn];
double dp1[maxn],dp2[maxn];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
void solve(int l,int r,int x,int y,double *dp){
	if(l>r)return ;
	l=max(l,x);
	int mid=l+((r-l)>>1);
	int p;
	for(int i=x;i<=min(mid,y);i++){
		double val=a[i]-a[mid]+sqrt(mid-i);
		if(dp[mid]-val<=eps){
			dp[mid]=val;
			p=i;
		}
	}
	solve(l,mid-1,x,p,dp);
	solve(mid+1,r,p,y,dp);
	return ;
}
int main(){
	int n;
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	solve(1,n,1,n,dp1);//j<=i
	reverse(a+1,a+n+1);
	solve(1,n,1,n,dp2);//j>=i
	for(int i=1;i<=n;i++)printf("%d\n",(int)(ceil(max(dp1[i],dp2[n-i+1]))));
	return 0;
}

```

---

## 作者：hyman00 (赞：17)

upd: 更新了一些错别字


# P3515 & loj2157「POI2011 R1」避雷针 Lightning Conductor 题解 

## 0x00 拜谢

本题解用了 @[pp_orange](/user/224443) 的线性小常数做法以及 @[Alex_Wei](/user/123294) 的高效快读板子。

## 0x01 暴力做法

式子变化为对每一个 $i$，要去求 $\max\{a_j+\lceil\sqrt{|i-j|}\rceil\}-a_i$，后面说的答案默认为 $ans_i=\max\{a_j+\lceil\sqrt{|i-j|}\rceil\}$。

由于根号的取值只有 $O(\sqrt n)$ 的，就可以先预处理前缀，后缀 max，然后直接查询 $ans_i=\max\{sf_{i+j^2+1}+j+1,pf_{i-j^2-1}+j+1\}$，时间复杂度 $O(n\sqrt n)$ 可以通过此题。

## 0x02 另一种暴力

考虑不是对每一个位置求答案，而是让它去更新其他位置的答案。

因为左右时对称的，不妨只考虑向右贡献。

这样 $i$ 对 $j$ 的贡献是 $a_i+\lceil\sqrt{j-i}\rceil$，是随着 $j$ 的增加而增加的，并且最多只会取到 $[a_i,a_i+\sqrt n]$ 以内的整数。

我们可以在 $i+k^2+1$ 的位置打上 $a_i+k+1$ 的标记，最后从左往右去一遍标记的前缀 max 即可。

对每个位置都这么做，最后统计答案，也是 $O(n\sqrt n)$ 的，可以通过。

## 0x03 暴力做法的优化

其实不必对每个 $i$ 都往后打 $O(\sqrt n)$ 个标记，有些位置是不优的，可以直接忽略。

我们发现如果对于 $i$ 存在一个 $k<i$ 使得 $a_k\ge a_i$，那么对于任意的 $j>i$，$a_k+\sqrt{j-k}\ge a_i+\sqrt{j-i}$ 的，所以一个位置有用当且仅当它的 a 的值严格大于前面的所有位置。

只需要从左往右扫的时候大于当前最大值才去更新。

这个优化不影响复杂度，在数据严格递增的时候也是 $O(n\sqrt n)$ 的，但是随机数据是 $O(n+\sqrt n\log n)$ 的。

## 0x04 另一个优化

考虑找到 $\max\{a_i\}$，不妨记为 $mx$，那么每一位的答案都大于等于 $mx$，那么那些 $a_i<mx-\sqrt n$ 的位置也是没有用的，即只有 $[mx-\sqrt n,mx]$ 的是有用的，并且相同的值只有最靠前的有用。

这时有用的位置总数最多为 $O(\sqrt n)$，每次更新 $O(\sqrt n)$，总复杂度线性。

## 0x05 代码

代码极其好写，且常数非常小，这是不加读入优化的[代码](https://loj.ac/s/1821261)（514ms）。

使用了原最优解的的高效快读板子后的[代码](https://loj.ac/s/1821295)（174ms），可见大部分运行时间都用在了 IO 上。

目前卡到 loj 最优解（174ms），洛谷最优解（118ms）。

## 0x06 总结

用几个性质优化暴力，注意如果不是整数域内这个方法就用不了。

---

## 作者：hs_black (赞：15)

首先进行一步转化

$a_j \leq a_i + q - sqrt(abs(i - j))$

$a_i + q \geq a_j + sqrt(abs(i-j))$

  即 $q = max (a_j + sqrt(abs(i-j))) - a_i $

我们对$i \geq j$ 和 $j > i$ 分类讨论, 其实解决一种情况后将序列翻转再做一遍即可

有一种O($n^2$)的dp暴力应该不难想到

那么我们现在思考如何以比较优秀的时间复杂度解决

这里涉及到决策单调性

简单的说, 对于i来说, 它的答案来源是另一点j,

那么所有答案来源排成的序列$j_1,j_2,j_3,\cdots j_n$ 具有单调性

比如: 1112255566666666678888

那么我们可以考虑对于每一个i, 它可以成为哪一段区间的答案

即一个三元组(l, r, i) 对应i控制l到r

可以二分+栈(或队列)处理

 二分i和栈顶答案相等临界, 若临界小于l则弹栈重复操作

否则将新的(l, r, i) 压倒栈中

代码: 

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#define ll long long
using namespace std;
const int N = 500080;
struct node{
	ll l, r, x;
};
deque<node> q;
ll read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x * f;
} //快读
ll n;
long double ans[N], a[N];
bool check(ll x,ll y,ll k) {
	return a[x] + sqrt(k - x) > a[y] + sqrt(k - y);
}
void work(void) {
	node k = (node){1, n, 1}; 
	for (ll i = 2;i <= n; i++) {
		if (a[i] < a[k.x]) continue; //剪枝, 如果满足则它一定不会有贡献
		ll l = i, r = n, mid;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (check(k.x, i, mid)) l = mid + 1;
			else r = mid - 1;
		}//二分
		if (l == n + 1) continue;
		if (l <= k.l) {
			k = q.front();
			q.pop_front();
			i--;
			continue;
		}//弹栈
		k.r = r;
		q.push_front(k);
		k = (node){l, n, i}; //压栈
	}
	q.push_front(k);
	k = q.back();
	q.pop_back();
	for (ll i = 1;i <= n; i++) {
		if (k.r < i) {
			k = q.back();
			q.pop_back();
		}
		ans[i] = max(ans[i], a[k.x] + sqrt(i - k.x)); //要做两次,所以取max
	}
}
		
int main() {
	n = read();
	for (int i = 1;i <= n; i++) 
		a[i] = read(), ans[i] = a[i];
	work();
	for (int j = 1;j << 1 <= n; j++) 
	swap(a[j], a[n-j+1]), swap(ans[j], ans[n-j+1]);
    //翻转
	while (q.size()) q.pop_front();
	work();
	///*
	for (int i = n;i >= 1; i--)
		printf ("%d\n", int(ceil(ans[i]) - a[i]));
		//*/
	return 0;
}
```



---

## 作者：Tyher (赞：14)

## 题解似乎很少啊
### 感谢zsy的指点 题解参考了其他人的题解

dp的方程多想一下就可以出来

```
dp[i]=max(num[j]-num[i]+sqrt(abs(i-j)));
```

然后我们考虑怎么优化它

是不是感觉abs有点难搞？

我们先从前往后做一遍dp，令j<i。
再从后往前做一次，令j>i，这样把abs去掉。

对于函数y=sqrt(x)，它增长的速度应当是越来越慢的

我们先考虑从前往后的情况，如果决策点j不变的情况下，如果i不断增大，那么sqrt(i-j)的增长速度是不是不断减小？

注意到我们的dp方程是要取最大值

如果i不断增大的情况下，决策点j产生的dp值增增长幅度不断减小（注意，他仍然在增长），是不是可能存在一个决策点k，虽然他之前产生的贡献比较小，但是增幅较大，在此时决策点k将代替决策点j形成dp[i]的最优解？

可能有点绕口，类比速度和加速度的关系多想一想

那么，对于每一个决策点j，他可能形成最优解的范围应当是一段区间l到r

这样，我们可以得到一个优化dp的思路

我们可以开一个单调队列，队列里每个结点保存的是三元组{p,L,R};

就是在对于决策点p，他所能管辖到的范围是l到r，队列里所有l和r拼起来就是当前的i到n

每次枚举到一个i的时候，我们将队头的l++（满足队列区间之和为i到r），如果队头的元素所管辖的区间为空，是不是就可以删去了？

此时对于dp[i]而言，队头存储的p是不是就是最优决策点？

此时如果对于dp[n]而言，决策点p并没有决策点i优，我们是不是要在队尾加入决策点i？

那么怎么求i的管辖范围呢？

显然，此时的r=n(想一想为什么)，注意到增长速度是存在单调性的，及对于某一时刻，p突然就没有i优了，以后就一直没有i优了，所以我们可以二分临界值

二分的临界值为temp，则原队尾的r更新为temp-1，加入新的元素i，plr依次为i，temp，n

给个代码：
```
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define il inline
#define rg register
#define ll long long
#define N 540000
#define inf 2147483647
#define ll_inf 9223372036854775807
using namespace std;
int n,num[N];
double F[N],G[N];
struct T{
	int p,l,r;
}Q[N];
il void re(rg int &x);
double sol(rg int i,rg int j){
	return (double)num[j]+sqrt((double)(1.0*abs(i-j)));
}
int find(rg int le,rg int ri,rg int p,rg int i){
	rg int ans=-1;
	while(le<=ri){
		rg int mid=((le+ri)>>1);
		if(sol(mid,p)>sol(mid,i))le=mid+1;
		else ri=mid-1,ans=mid;
	}
	return ans;
}
int main(){
	freopen("s.in","r",stdin);
	re(n);
	for(rg int i=1;i<=n;++i)
		re(num[i]);
	//dp[i]=max(num[j]-num[i]+sqrt(abs(i-j)));
    //需要求出最优的解
	rg int tail=0,head=1;
	for(rg int i=1;i<=n;++i){
		Q[head].l++;
		if(head<=tail&&Q[head].r<Q[head].l)head++;
		if(head>tail||sol(n,i)>sol(n,Q[tail].p)){
			while(head<=tail&&sol(Q[tail].l,Q[tail].p)<sol(Q[tail].l,i))tail--;
			if(head>tail)
				Q[++tail].p=i,Q[tail].l=i,Q[tail].r=n;
			else{
				rg int temp=find(Q[tail].l,Q[tail].r,Q[tail].p,i);
				Q[tail].r=temp-1;
				Q[++tail].p=i,Q[tail].l=temp,Q[tail].r=n;
			}
		}
		F[i]=sol(i,Q[head].p)-num[i];
	}
	reverse(num+1,num+n+1);
	tail=0,head=1;
	for(rg int i=1;i<=n;++i){
		Q[head].l++;
		if(head<=tail&&Q[head].r<Q[head].l)head++;
		if(head>tail||sol(n,i)>sol(n,Q[tail].p)){
			while(head<=tail&&sol(Q[tail].l,Q[tail].p)<sol(Q[tail].l,i))tail--;
			if(head>tail)
				Q[++tail].p=i,Q[tail].l=i,Q[tail].r=n;
			else{
				rg int temp=find(Q[tail].l,Q[tail].r,Q[tail].p,i);
				Q[tail].r=temp-1;
				Q[++tail].p=i,Q[tail].l=temp,Q[tail].r=n;
			}
		}
		G[i]=sol(i,Q[head].p)-num[i];
	}
	reverse(G+1,G+n+1);
	for(rg int i=1;i<=n;++i)
		printf("%d\n",max(0,(int)ceil(max(F[i],G[i]))));
    return 0;
}
il void re(rg int &x){
    rg int res=0;rg int w=1;char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')w=-1,c=getchar();
    while(c>='0'&&c<='9')res=(res<<3)+(res<<1)+c-'0',c=getchar();
    x=w*res;
}

```

---

## 作者：tuxiaobei (赞：10)

**此题暴力可过**。

基本思路：贪心地，从大到小考虑每个数，去更新每个位置。如果有多个相同的数，只需要用最左边和最右边的来更新即可。

这样做是 $O(n^2)$ 的，但是我们发现距离是开了个根号，即距离的影响不超过 $\sqrt n$，也就是说我们只需要考虑 $\sqrt n$ 个不同的数即可，此时数值的影响已经超过距离的影响。

时间复杂度 $O(n\sqrt n)$ ，需要一点常数优化即可 `AC` 。

```cpp
#include <bits/stdc++.h>
#define maxn 505050
using namespace std;
char buf[1 << 23], * p1 = buf, * p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? EOF : *p1++)
inline void read(int& ret)
{
	ret = 0;
	char ch = getchar();
	while (ch < '0' || ch>'9') ch = getchar();
	while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
}
int n;
int h[maxn];
pair<int, int>r[maxn];
int p[maxn];
#define max(a, b) (a > b ? a : b)

void update(int a, int b)
{
	p[b] = max(p[b], a);
	int k = b + 1;
	for (int j = 1; k <= n; j++) {
		int u = a + j;
		int v = b + j * j;
		while (k <= v) {
			if (k > n) break;
			p[k] = max(p[k], u), k++;
		}
	}
	k = b - 1;
	for (int j = 1; k; j++) {
		int u = a + j;
		int v = b - j * j;
		while (k >= v) {
			if (k <= 0) break;
			p[k] = max(p[k], u), k--;
		}
	}
}
int main()
{
	read(n);
	for (int i = 1; i <= n; i++) read(h[i]), r[i] = make_pair(h[i], i);
	sort(r + 1, r + n + 1);
	int i = n;
	r[n + 1].first = r[0].first = -1;
	int cnt = 0, v = 2 * sqrt(n);
	while (i && cnt < v) {
		if (r[i].first == r[i + 1].first && r[i].first == r[i - 1].first) {
			i--;
			continue;
		}
		update(r[i].first, r[i].second);
		i--, cnt++;
	}
	for (int i = 1; i <= n; i++) printf("%d\n", p[i] - h[i]);
}
```



---

## 作者：jjikkollp (赞：6)

观察$\sqrt{x}$，这是一个上凸函数，所以说当一个点距离远还比距离近的节点小，他就一定不再答案区间里了，二分一下原数列，然后对于每个点做一个可行答案区间，然后就可以在$O(nlg)$的时间更新答案，注意到方程与后面的值有关，我们可以反向再做一遍。


---

## 作者：Dreamunk (赞：5)

[题目](https://www.luogu.com.cn/problem/P3515)

这阵子学二分队列，写个题解吧。

要对每个 $i$，求出最小非负整数 $p$ ，使得 $\forall j\in[1,n],a_j\le a_i+p-\sqrt{|i-j|}$。

那么 $a_i+p\ge \max\{\max_{j<i}a_j+\sqrt{i-j},\max_{j>i}a_j+\sqrt{j-i}\}$

求出大于等于号右边的东西即可。考虑求出 $\max_{j<i}a_j+\sqrt{i-j}$。（$j>i$ 的东西类似做就好）

把 $a_j+\sqrt{i-j}$ 看作以 $i$ 为自变量的函数，对于所有 $j<i$，所有函数值的最大值就是要求的。

![_O_J4_XIWGI1__V2HCIO__Y.png](https://i.loli.net/2020/04/14/gU2kBaJDcryjZOd.png)

这些函数的图像画在一起，大概长这样。

考虑其中的一个函数，在 $i$ 增大的过程中，或者是从始至终被吊打，或者是开始时不如别人，中间吊打所有人，最后又被超过，然后永世不得翻身。

为什么永世不得翻身？因为这里面所有的函数都是增长越来越慢（大概是取值范围内导数小于零）的，考虑 后面的函数 超过 前面的函数 的时候，后面的函数 的增长就比 前面的函数 快，在这之后 后面的函数 还是一直比 前面的函数 快，所以 前面的函数 在此之后不会再出头。

根据这个性质，考虑维护一个队列，队列里面是一堆函数（设为 $f_1,f_2,\cdots,f_d$），且$\forall k ,f_k$ 超过 $f_{k-1}$ 的时间要早于 $f_{k+1}$ 超过 $f_k$ 的时间。

（以下认为队尾进队头出。）

当拿到一个新函数的时候，和队尾的函数求一下交（可以二分，本题似乎也可以直接解方程），如果永远超不过队尾就扔掉；如果新函数与队尾的相交的时间晚于队尾两个函数相交的时间，就直接塞入队尾，否则一直弹队尾直到可以为止。

当你要求答案的时候，不断弹队首，直到找到需要的即可。

从前往后做一遍就求出答案了。（可以看代码，关键部分是 `Solve` 函数。）
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
const int N=5e5+3;
int n,a[N],b[N],s[N],t[N],q[N],f[N],l,r;
inline int Calc(int i,int j,int*a){//求交点的函数
	int l=j+1,r=n+1,m;
	for(;l<r;)m=l+r>>1,a[i]+sqrt(m-i)<a[j]+sqrt(m-j)?r=m:l=m+1;
	return l;
}
inline int Solve(int*a,int*s){
	int tmp;
	q[l=r=0]=1;
	for(int i=2;i<=n;i++){
	  for(;l<r&&f[l+1]<=i;l++);//弹队首
	  s[i]=a[q[l]]+ceil(sqrt(i-q[l]));//求答案
	  for(;l<r&&Calc(q[r],i,a)<f[r];r--);//弹队尾
	  if((tmp=Calc(q[r],i,a))<=n)q[++r]=i,f[r]=tmp;//加入新函数
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i),b[n-i+1]=a[i];
	Solve(a,s);
	Solve(b,t);
	for(int i=1;i<=n;i++)
	  printf("%d\n",std::max(s[i],t[n-i+1])-a[i]>0?std::max(s[i],t[n-i+1])-a[i]:0);
	return 0;
}
```

---

## 作者：GKxx (赞：4)

写一篇题解来纪念一下自己在语文课上想出的第一道非斜率优化的决策单调性。（应该是标准的用三元组的决策二分栈）

首先要求的东西就是

$f_i=\lceil \max\{a_j+\sqrt{|i-j|}\}-a_i\rceil,1\leq j\leq n$

虽然这个式子并没有什么递推，但依然可以看成一个dp来做。

首先这个绝对值非常丑，并且其实上取整符号可以忽略，我们可以把它改写成求

$f_i=\max\{a_j+\sqrt{i-j}\}-a_i,1\leq j<i$

只要先求一遍这个，然后把序列倒过来再做一遍，取max即可，所以我们只看这个怎么求

如果设$g_j(i)=a_j+\sqrt{i-j}$，事实上我们就是要在$j=1,2,...,i-1$的这$i-1$个函数$g_j(i)$中，找到最大值。

如果你学过基本初等函数，你会知道这是个幂函数平移之后得到的函数；如果你学过圆锥曲线，你会知道这是个抛物线平移得到的二次曲线；但其实你只要用几何画板就可以发现

- $g_j(i)$单调递增

- $\forall j,k, g_j(i)$与$g_k(i)$至多只有一个交点

由于本人太懒，就不画图了，要看图请看楼上FlashHu大佬的图，你就会明白这$i-1$个曲线的关系

这就是我们决策单调性的基础。

有了对这个函数的认识，就可以发现，对于每个最优决策$j$，一定会有对应的区间$[l_j,r_j]$满足：对于任意$i\in[l_j,r_j]$，$f_i$的最优决策点是$j$。

那么我们可以用一个栈来维护以上信息：栈里面的元素是三元组$(j,l_j,r_j)$，含义如上。我们让栈里的元素满足：从栈底到栈顶的每个区间$[l_j,r_j]$端点是递增的，且不重叠，并且它们的并就是$[1,n]$。

这时候对于一个$i$，只要在栈里面二分就可以找到$i$所属的区间$[l_j,r_j]$，其最优决策就是$j$。

然后考虑把第$i$个数加入栈，事实上就是在尝试能不能比栈顶元素更优：设栈顶元素为$(k,l_k,r_k)$，只要求函数$g_i$与$g_k$的交点横坐标$x$，然后判断一下：

- 如果$x>n$说明$i$不可能比栈顶元素更优，就没有$i$什么事了，结束。

- 如果$x\leq l_k$则说明在$k$发挥作用之前$i$就比它优了，那就完全可以把$k$弹掉，再将$i$去和下一个栈顶元素比。

- 如果$x$介于$l_k$与$r_k$之间，说明$i$将从$x$处开始比$k$优，把$r_k$改成$x-1$，然后把$(i,x,n)$加入栈顶，结束。

这样我们就做完了。具体可以看代码。

另外注意，上述过程做第一遍的时候是$j<i$的情况，第二遍是$j>i$的情况，但是始终没有$j=i$的情况，因此输出的时候要与$0$取max

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <cmath>

#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define dwn(I, A, B) for (int I = (A); I >= (B); --I)
#define erp(I, X) for (int I = head[X]; I; I = next[I])

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
    read(t); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> void writeln(T x) {
    write(x);
    puts("");
}
template <typename T> inline bool chkMin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkMax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

const int maxn = 5e5 + 207;
int a[maxn];
double f[2][maxn];
struct P3 {
    int j, lb, rb;
    P3() : j(0), lb(0), rb(0) {}
    P3(int i, int l, int r) : j(i), lb(l), rb(r) {}
};
P3 stk[maxn];
int n, top;

inline int inter(int i, int j) {
    int left = 0, right = n + 1, ans = n + 1;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (a[i] + sqrt(mid - i) > a[j] + sqrt(mid - j))
            ans = mid, right = mid - 1;
        else
            left = mid + 1;
    }
    return ans;
}

inline void make(double *f) {
    f[1] = 0; top = 0;
    stk[++top] = P3(1, 2, n);
    rep(i, 2, n) {
        int left = 1, right = top, pos = top;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (stk[mid].lb <= i && stk[mid].rb >= i) {
                pos = mid;
                break;
            } else if (stk[mid].lb > i) right = mid - 1;
            else left = mid + 1;
        }
        int j = stk[pos].j;
        f[i] = a[j] + sqrt(i - j) - a[i];
        int x;
        while (top && (x = inter(i, stk[top].j)) <= n) {
            if (x <= stk[top].lb) {
                if (top == 1) {
                    stk[top] = P3(i, 1, n);
                    break;
                } else stk[--top].rb = n;
            } else {
                stk[top].rb = x - 1;
                stk[++top] = P3(i, x, n);
                break;
            }
        }
    }
}

int main() {
    read(n);
    rep(i, 1, n) read(a[i]);
    make(f[0]);
    std::reverse(a + 1, a + n + 1);
    make(f[1]);
    std::reverse(f[1] + 1, f[1] + n + 1);
    rep(i, 1, n) writeln((int)std::max({(double)0, ceil(f[0][i]), ceil(f[1][i])}));
    return 0;
}
```

---

## 作者：yuzhechuan (赞：4)

很好的一道决策单调性，整体二分，观察性质，数形信结合题（雾）


---

### 题解：

首先是快乐推式子，移项后容易得到：

$p_i=\max\limits_{j=1}^{n}\{a_j+\sqrt{| i-j |}\}-a_i$

绝对值拆开，发现是两种正好相反的情况，所以这里只先考虑$i\ge j$的情况

把$a_j+\sqrt{i-j}$单独拉出来建立函数$f_j(i)=a_j+\sqrt{i-j}$

函数图象大致长这样

![](https://s1.ax1x.com/2020/07/03/NXMOAI.png)

对于$p_i$，实际就是要用一条直线$x=i$去截断，看看最高交点是啥

观察性质，很容易发现这个最高交点是在不断向右上方移动的

形式的说，具有**决策单调性**

有了这么优美的性质，接下来就有几种不同的做法，这里讲得是代码比较短的整体二分做法

同时二分决策点的横纵坐标，每次二分出一个横坐标就暴力算决策点，然后继续递归，将纵坐标分成可行和不可行两部分

复杂度是一只log的

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=5e5+5;
int n,id[N],a[N];
double ans[N];

double calc(int x,int y){
	return a[x]+sqrt(abs(x-y)); //直接计算
}

void divide(int l,int r,int p,int q){
	if(l>r) return ;
	int mid=l+r>>1,pos=0;
	double ma=0; //ma是最优决策点
	for(int i=p;i<=q&&i<=mid;i++) if(calc(i,mid)>ma) ma=calc(i,mid),pos=i; //找到最优点
	ans[id[mid]]=max(ans[id[mid]],ma); //由于有正反两次，所以注意取max
	divide(l,mid-1,p,pos); //继续往下分
	divide(mid+1,r,pos,q);
}

signed main(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]),id[i]=i;
	divide(1,n,1,n);
	reverse(a+1,a+1+n); //翻转再做一次
	reverse(id+1,id+1+n);
	divide(1,n,1,n);
	for(int i=1;i<=n;i++) write((int)ceil(ans[i]-a[n-i+1])),puts(""); //由于要是整数且合法，所以注意要上取整
}
```

---

## 作者：kkxhh (赞：3)

题目要求对于每一个 $i$ 有：

$$ \forall j \in [1,n] \quad a_{j} \le a_{i} + p_{i} - \sqrt{|i-j|} $$

我们把式子变换一下

$$ \forall j \in [1,n] \quad p_{i} \ge a_{j} + \sqrt{|i-j|} - a_{i} $$

也就是

$$ p_{i} = \lceil max \{ (a_{j} + \sqrt{|i-j|}) \} \rceil - a_{i} $$

我们考虑正反转移两遍，将绝对值去掉

$$ p_{i} = \lceil max \{ (a_{j} + \sqrt{i-j}) \} \rceil - a_{i} $$

可以发现我们是在对一些形如 $\sqrt{x-a}+b$ 的函数在某个点上取 $max$

由于从前往后函数里的 $a$ 是不断递增的，而且 $\sqrt{x}$ 的增长率是逐渐减小的，于是我们可以发现如果一个函数在某个点上被靠后（$a$ 更大）的另一个函数超越了，那么这个函数在后面是不可能再次反超的

换句话说，转移满足**决策单调性**

于是我们可以维护一个单调队列，每次比较的时候 $O(logn)$ 二分求出两个函数的交点。如果队尾的函数完全劣于新加入的函数（即新加入函数与队尾函数的交点在队尾函数与上一个函数的交点之前），我们就将它弹出。同时如果当前位置已经过了队首函数与下一个函数的交点，我们就弹出队首函数。每次转移时直接取队首转移即可

我们可以发现每次比较要么是删除掉队尾元素，要么是停止比较，于是比较的次数是 $O(n)$ 的。每次比较复杂度为 $O(logn)$ ，单调队列优化原本的复杂度也是 $O(n)$ 的，于是总复杂度为 $O(nlogn)$

完整代码如下：

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

typedef struct node{
    int a,b;
    node() {}
    node(int _a,int _b):a(_a),b(_b) {}
}node;

node q[500010];
int n,a[500010],p[500010],head,tail,maxp[500010];
double sq[500010];
// 预处理 sqrt

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?0:k,c=getchar();
    while(c>='0' && c<='9') num=num*10+c-'0',c=getchar();
    return k?num:-num;
}

double cal(node x,int p) {return (double)(x.a+sq[p-x.b]);}

int get(node x,node y){
    int l=y.b-1,r=n+1,mid;
    while(l+1<r){
        mid=(l+r)>>1;
        if(cal(y,mid)>=cal(x,mid)) r=mid;
        else l=mid;
    }
    return r;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),sq[i]=sqrt(i);
    head=1; tail=0;
    for(int i=1;i<=n;i++){
        node cur(a[i],i);
        while(head<=tail && get(q[tail],cur)<=p[tail]) tail--;
        q[++tail]=cur; p[tail]=(head<tail)?get(q[tail-1],cur):1;
        while(head<tail && i>=p[head+1]) head++;
        maxp[i]=(int)ceil(cal(q[head],i))-a[i];
    }
    for(int i=1;n-i+1>i;i++) {swap(a[i],a[n-i+1]); swap(maxp[i],maxp[n-i+1]);}
    head=1; tail=0;
    for(int i=1;i<=n;i++){
        node cur(a[i],i);
        while(head<=tail && get(q[tail],cur)<=p[tail]) tail--;
        q[++tail]=cur; p[tail]=(head<tail)?get(q[tail-1],cur):1;
        while(head<tail && i>=p[head+1]) head++;
        maxp[i]=max(maxp[i],(int)ceil(cal(q[head],i))-a[i]);
    }
    for(int i=n;i>=1;i--) printf("%d\n",maxp[i]);
    return 0;
}
```

---

## 作者：Hanghang (赞：3)

介绍一种简单无脑的算法。

摘自 [我的博客](https://www.cnblogs.com/Hanghang007/p/17722117.html)

首先你需要会李超线段树。

注意到李超线段树中有一个函数 Ans(看模板) 是用来计算函数在一个点的取值。

我们如果将我们要求的函数(非直线)的解析式带入，就解决了问题。

把绝对值拆开，正反维护各维护一边

把 $a_j+\sqrt{i-j}$ 看成函数，套上李超线段树求最大值

注意到开根运算是有定义域的，一种无脑的做法就是插入到一段区间内。

巧妙的方法是重定义开根运算，如果遇到负数就设成负无穷。

为什么不会出 bug 呢？注意到询问单调递增且都比所有插入的 $j$ 都大，那么也就不会访问到开根负数的地方。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef double db;
typedef long long ll;
const int N=5e5+3;
const db eps=1e-10;
int n,rt,a[N],sx[N],sy[N];
struct Fun{int h,g;}p[N];
struct LCT
{
    int tot=0,o=0;
    struct Tree{int lc,rc,id;}tr[N];
    int dcmp(db x,db y){return x-y>eps?1:y-x>eps?-1:0;}
    db sqr(db x){return dcmp(0,x)==1?-1e9:sqrt(x);}
    db Ans(int id,int x){return (db)p[id].h+sqr((!o)?x-p[id].g:p[id].g-x);}
    #define ls (tr[p].lc)
    #define rs (tr[p].rc) 
    #define mi ((l+r)>>1)
    void Upd(int &p,int l,int r,int u)
    {
        if(!p){p=++tot;tr[p].id=u;return;}
        int &v=tr[p].id;
        if(dcmp(Ans(u,mi),Ans(v,mi))==1)swap(u,v);
        if(dcmp(Ans(u,l),Ans(v,l))==1)Upd(ls,l,mi,u);
        if(dcmp(Ans(u,r),Ans(v,r))==1)Upd(rs,mi+1,r,u);
    }
    db Ask(int p,int l,int r,int d)
    {
        if(!p)return 0;
        db ans=Ans(tr[p].id,d);
        if(l==r)return ans;
        return max(ans,d<=mi?Ask(ls,l,mi,d):Ask(rs,mi+1,r,d));
    }
    void Clear()
    {
        for(int i=1;i<=tot;i++)tr[i].lc=tr[i].rc=tr[i].id=0;
        tot=rt=0;o=1;
    }
}T;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],p[i]={a[i],i};
    for(int i=1;i<=n;i++)sx[i]=ceil(T.Ask(1,1,n,i)),T.Upd(rt,1,n,i);
    T.Clear();
    for(int i=n;i>=1;i--)sy[i]=ceil(T.Ask(1,1,n,i)),T.Upd(rt,1,n,i);
    for(int i=1;i<=n;i++)cout<<max(max(sx[i],sy[i])-a[i],0)<<endl;
}
```

---

## 作者：Shunpower (赞：2)

核心代码共十行。

## 思路

显然可以把左侧和右侧分开处理来拆掉绝对值，下文中都考虑 $j<i$ 的左侧情况。

鉴于 $p\in\mathbb{N}$，所以可以首先把式子换成 $a_j+\left\lceil \sqrt{i-j}\right\rceil\leq a_i+p$，之后的问题就是对于每个 $i$ 算一下不等式左边那一坨东西的最大值就行了。

考虑一个比较容易想到的做法：

我们可以从左往右扫 $i$。容易发现，每次把 $i$ 右移试图计算下一个位置上的答案时，只有根号个 $a_j+\left\lceil \sqrt{i-j}\right\rceil$ 发生了变化，这些点就是类似距离为 $9,10$ 这样的上取整断点。那么我们只需要扫一遍这根号个断点，再在每一个断点中间 RMQ（显然断点之间的根号上取整都是相同的），就可以移动一下重算一次最大值，从而得到一个复杂度是 $\mathcal O(n\sqrt n \log n)$ 的做法，但这显然是过不了的。

考虑能不能不重算整个最大值。可以注意到，左侧每个点 $j$ 总是在随着我们 $i$ 的向右远去而贡献增大。这说明，每次有一个点 $j$ 通过了断点需要重新给贡献的时候，它可以完美地覆盖掉自己之前对最大值的贡献。而剩下的没有通过断点的点对最大值的贡献是不变的。

所以我们根本就没必要重算最大值，直接把那几个通过断点的点的新贡献 $\max$ 到旧的最大值里面就可以得到 $i$ 右移一位之后新的最大值。

左右各跑一遍即可在每个 $i$ 上都得到对于两侧的 $j$，$a_j+\left\lceil \sqrt{|i-j|}\right\rceil$ 的最大值。这个东西直接减掉 $a_i$ 就是 $p$ 的最小值了。

这样就可以把时间复杂度降到 $\mathcal O(n\sqrt n)$。但是还有常数，所以看起来还是过不了。然而仔细分析一下可以发现我们其实复杂度里面根本没有顶满 $n\sqrt n$，而是 $\sum\limits_{i=1}^{n} \sqrt i$。随便积一下就能知道这个东西虽然级别是 $\mathcal O(n\sqrt n)$，但是可以贡献一个 $\frac{2}{3}$ 的常数，所以清真实现一下（少用几个循环）再吸个氧就能稳过了。

下面是非常简短的代码。谷上吸了氧可以跑到 650ms 左右，LOJ 上吸氧可以跑进 500ms。

```cpp
int n;
int h[N];
int maxn;
int ans[N];
int main(){
#ifdef zjh
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n;
    fr1(i,1,n) cin>>h[i];
    maxn=0;
    fr2(i,n,1){
        ans[i]=maxn;
        for(int j=0;j*j<=n-i;j++) maxn=max(maxn,h[i+j*j]+j+1);
    }
    maxn=0;
    fr1(i,1,n){
        ans[i]=max(ans[i],maxn);
        for(int j=0;j*j<=i-1;j++) maxn=max(maxn,h[i-j*j]+j+1);
    }
    fr1(i,1,n) cout<<max(ans[i]-h[i],0)<<'\n';
    ET;
}
```

---

## 作者：LCuter (赞：2)

我觉得需要严格证明单调性

我们要证的是对于$F_i=\max _{1\le j<i}{\{a_j+\sqrt{i-j}\}}$，记$P_i$为另$F_i$取到最大值的$j$，有$P$单调不减

考虑反证法：假设$\exists j<i,P_j>P_i$

也就是$P_i<P_j<j<i$

根据$P$的最大性，我们有以下两个式子

$$a_{P_j}+\sqrt{j-P_j}> a_{P_i}+\sqrt{j-P_i}$$

$$a_{P_i}+\sqrt{i-P_i}> a_{P_j}+\sqrt{i-P_j}$$

两式相加，记$w(j,i)=\sqrt{i-j}$，有

$$w(P_j,j)+w(P_i,i)>w(j,P_i)+w(i,P_j)$$

所以，我们只需证明

$$w(P_j,j)+w(P_i,i)\le w(j,P_i)+w(i,P_j)$$

也就是$\forall a<b<c<d,w(a,d)+w(b,c)\le w(a,c)+w(b,d)$

就可以推出矛盾，从而证明原命题了，这边介绍一个定理：

- **定理** 若一个定义在整数集上的二元函数$w(x,y)$满足对于任意定义域内的$a<b$，都有$w(a,b+1)+w(a+1,b)\le w(a,b)+w(a+1,b+1)$成立，则$w(x,y)$满足$\forall a,b,c,d,w(a,d)+w(b,c)\le w(a,c)+w(b,d)$

- **证明** 

	- 考虑数学归纳法，若$k$为一非负整数，记$b=a+k$，且$b=a+k<c$
    
   - 当$k=1$

	- $$w(a-1,c+1)+w(a,c)\le w(a-1,c)+w(a,c+1)$$

	- $$w(a,c+1)+w(a+1,c)\le w(a,c)+w(a+1,c+1)$$

	- 两式相加，有

	- $$w(a,c+1)+w(a+1,c)\le w(a,c)+w(a+1,c+1)$$
    
   - 当$k>1$
   
   - 若有
   
   - $$w(a,c+1)+w(a+k-1,c)\le w(a,c)+w(a+k-1,c+1)$$

	- 因为$a+k<c$
    
   - $$w(a+k-1,c+1)+w(a+k,c)\le w(a+k-1,c)+w(a+k,c+1)$$
   
   - 两式相加，有

	- $$w(a,c+1)+w(a+k,c)\le w(a,c)+w(a+k,c+1)$$
    
   - 也就是$\forall a<b<c,w(a,c+1)+w(b,c)\le w(a,c)+w(b,c+1)$
   
   - 然后记$d=c+k$
   
   - 当$k=1$，由上式
   
   - $$w(a,c+1)+w(b+c)\le w(a,c)+w(b,c+1)$$
   
   - $$w(a,c+2)+w(b,c+1)\le w(a,c+1)+w(b,c+2)$$
   
   - 两式相加，有
   
   - $$w(a,c+2)+w(b,c)\le w(a,c)+w(b,c+2)$$
   
   - 当$k>1$
   
   - 假设有
   
   - $$w(a,c+k-1)+w(b,c)\le w(a,c)+w(b,c+k-1)$$
   
   - 因为$c+k>b$
   
   - $$w(a,c+k)+w(b,c+k-1)\le w(a,c+k-1)+w(b,c+k)$$
   
   - 两式相加，有
   
   - $$w(a,c+k)+w(b,c)\le w(a,c)+w(b,c+k)$$
   
   - 即$\forall a<b<c<d,w(a,d)+w(b,c)\le w(a,c)+w(b,d)$
   
 所以现在我们只需证明
 
 $$\forall a<b,w(a,b+1)+w(a+1,b)\le w(a,b)+w(a+1,b+1)$$
 
 记$d=b-a$
 
 将上式换为原表达式并带入$d=b-a$
 
 $$\sqrt{d+1}+\sqrt{d-1}\le \sqrt{d}+\sqrt{d}$$
 
 移项，有
 
 $$\sqrt{d+1}-\sqrt{d}\le \sqrt{d}-\sqrt{d-1}$$
 
 此处有两种证明方法，先讲第一种
 
 记$f(x)=\sqrt{x}-\sqrt{x-1}$，所以只需证明$f(x)$单调递减即可
 
 求导得$f'(x)=\frac{1}{2\sqrt{x}}-\frac{1}{2\sqrt{x-1}}$，显然有在$x\ge 0$时，$f'(x)$恒非正，故$f(x)$单调递减，证毕。
 
 现在讲第二种方法
 
 仍然是
 
 $$\sqrt{d+1}-\sqrt{d}\le \sqrt{d}-\sqrt{d-1}$$
 
 两边同时除以$1$
 
 $$\frac{\sqrt{d+1}-\sqrt{d}}{1}\leq \frac{\sqrt{d}-\sqrt{d-1}}{1}$$
 
 记$f(x)=\sqrt{x}$，容易发现两边都是拉格朗日中值定理的形式，所以存在$n\in(d,d+1),m\in(d-1,d)$，使得$f'(n)=\frac{\sqrt{d+1}-\sqrt{d}}{1},f'(m)=\frac{\sqrt{d}-\sqrt{d-1}}{1}$，注意到$f'(x)=\frac{1}{2\sqrt{x}}$单调递减且$n<m$所以上式得证。

---

## 作者：C20203030 (赞：2)

## 一、题目
已知一个长度为$n$的序列$a1,a2,...,an$。

对于每个$1<=i<=n$，找到最小的非负整数$pi$满足对于任意的$j$，$aj\leq ai+pi-\sqrt{|i-j|}$


$1≤n≤5\times10^5，0≤ai≤10^9$

## 二、解法

我们先对题目的式子进行改变：

$\Rightarrow pi>=aj+sqrt{|i-j|}-ai$

我们把题目拆成两个式子，再取最大值：

$pi>=aj+\sqrt {i-j} -ai$

$pi>=aj+\sqrt {j-i}-ai$

我们考虑第一个式子，第二个式子将之反向即可。

对于每个$j$，把$aj+\sqrt{i-j}$，看成关于$i$的函数$fj$​。我们要做的就是在所有$j≤i$的函数中找到最值。

我们维护一个决策二分栈，按$j$从大到小维护，对于每一个函数，我们可以求出栈中相邻两个元素，后面的元素刚好超过前面元素的下标$k$（临界点），原因是$sqrt$的增速会越来越慢，当到临界点时，加入的点如果比队尾元素优，那就踢出队尾元素，所以我们维护的是一个$k$单调递减的队列，当处理完队尾后，二分算出当前点的$k$，把当前点加入队列。

对于每个点，我们踢出已不优的队头，再用队头更新答案即可。


```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define cal(i,j) (a[j]+sq[i-j])
const int MAXN = 5e5+5;
int read()
{
    int num=0,flag=1;char c;
    while((c=getchar())<'0'||c>'9') if(c=='-') flag=-1;
    while(c>='0'&&c<='9')num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num*flag;
}
int n,a[MAXN],k[MAXN],q[MAXN];
double p[MAXN],sq[MAXN];
int bound(int x,int y)
{
	int l=y,r=k[x]?k[x]:n,mid,ret=r+1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(cal(mid,x)<=cal(mid,y))
			ret=mid,r=mid-1;
		else
			l=mid+1;
	}
	return ret;
}
void work()
{
	int h=1,t=0;
	for(int i=1;i<=n;i++)
	{
		while(h<t && cal(k[t-1],q[t])<cal(k[t-1],i)) t--;
		k[t]=bound(q[t],i),q[++t]=i;
		while(h<t && k[h]<=i) ++h;
		p[i]=max(p[i],cal(i,q[h]));
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),sq[i]=sqrt(i);
	work();
	for(int i=1,j=n;i<j;i++,j--)
		swap(a[i],a[j]),swap(p[i],p[j]);
	memset(k,0,sizeof k);
	work();
	for(int i=n;i>=1;i--)
		printf("%d\n",max((int)ceil(p[i])-a[i],0));
}
```



---

## 作者：Piwry (赞：1)

让我首次接触到决策单调性的题，还是发下题解X

之前在模拟赛碰到这道，当时只想出了个 $O(n\sqrt n\log n)$ 的线段树做法，看题解才发现有 $O(n\log n)$ 的做法（

## 解析

首先可以推出这题让我们求的 $p_i$ 实际上就是这个东西：$p_i=\max\limits_{1\leq j\leq n}\{a_j+\sqrt{|i-j|}\}-a_i$

其中的绝对值有点烦，于是可以把这个式子拆成两个：$p_i=\max(\max\limits_{1\leq j\leq i}\{a_j+\sqrt{i-j}\}-a_i, \max\limits_{i\leq j\leq n}\{a_j+\sqrt{j-i}\}-a_i)$

实际上就是正着做一遍再反着做一遍，于是下面我们只关心这个式子：$p_i=\max\limits_{1\leq j\leq n}\{a_j+\sqrt{i-j}\}-a_i$

这看起来有点决策单调性的味道。我们先试着对它证明四边形不等式：

$$\text{设 }f(i, j)=a_j+\sqrt{i-j}$$

$$f(i, j)+f(i+1, j+1) - (f(i+1, j)+f(i, j+1))$$

$$=(a_j+\sqrt{i-j})+(a_{j+1}+\sqrt{i-j}) - ((a_j+\sqrt{i-j+1})+(a_{j+1}+\sqrt{i-j-1}))$$

$$=2\sqrt{i-j} - (\sqrt{i-j+1}+\sqrt{i-j-1})$$

$$=(\sqrt{i-j}-\sqrt{i-j-1}) - (\sqrt{i-j+1}-\sqrt{i-j})$$

观察 $\sqrt x$ 的导函数，发现它是递减的；也就是说，一定有 $\sqrt{x}-\sqrt{x-1} > \sqrt{x+1}-\sqrt{x}$。由此得证，有 $f(i, j)+f(i+1, j+1) \geq f(i+1, j)+f(i, j+1)$

&nbsp;

证完四边形不等式后，能用的方法就多了

首先我们可以立即得出：

> 定理 $1.$ 当 $k > 0$ 时，有 $f(i, j+k)-f(i, j)$ 随 $i$ 单调不降，$f(i+k, j)-f(i, j)$ 随 $j$ 单调不降

&nbsp;

这时可以考虑枚举 $i$，并同时用单调队列维护一个决策集：

每次循环开始时，我们反复弹出队头直到队列正数第二个元素在当前枚举 $i$ 下不比队头更优，此时队头就是当前 $i$ 的答案

接着我们将 $j=i$ 的决策加入队列，加入一个新的决策 $f_0$ 时，求出 $f_0$ 比队尾决策 $f_1$ 第一次优的时间 $t_1$，和队尾决策 $f_1$ 比队列倒数第二个决策 $f_2$ 优的时间 $t_2$。如果有 $t_2\geq t_1$，根据定理 $1$，队尾决策就不再可能成为最优决策了（$f_1$ 在优于 $f_2$ 前不会作为答案，且一旦 $f_0$ 优于 $f_1$，就会一直保持下去）。不停退队直到队尾决策有可能成为最优决策，最后再将新的决策加入队列

其中确定决策交点可能需要二分 $x$ 轴（$i$），因此每次比较是 $O(\log n)$ 的

（这里其实可以直接整数二分，求某个函数的值第一次大于另一个函数的值的整数点）

于是总的复杂度就是 $O(n\log n)$

&nbsp;

由于 $f(i, j)$ 在确定 $i, j$ 时就已经确定了，我们还可以用整体二分：

我们由 定理 $1$ 发现，随着 $i$ 的增加，一个决策 $f(i, j)$ 一旦优于决策 $\{f(i, k):k<j\}$，就会一直保持下去

于是我们可以将答案区间 $[l, r]$ 和决策区间 $[p, q]$ 一起分治，每次取 `mid=(l+r)>>1`。遍历 $[p, q]$ 找到对于 $i=mid$ 的最优决策 $f(mid, k)$，于是我们有：

1. 对于 $i>mid$，它的最优决策 $f(k', i)$ 一定满足 $k'\geq k$
2. 对于 $i<mid$，它的最优决策 $f(k', i)$ 一定有 $k'\leq k$

对于 $1.$，由 定理 $1$ 可以轻易得出

对于 $2.$，我们反着来；如果对于 $i<mid$，有 $f(i, k'), k'>k$ 成为最优决策，那么根据 定理 $1$，随着 $i$ 的递增，$f(i, k')-f(i, k)$ 单调不降，于是 $k$ 就不可能成为 $i=mid$ 的最优决策，产生了矛盾

于是我们只需接着递归处理 $[l, mid-1], [p, k]$ 和 $[mid+1, r], [k, q]$ 即可

虽然 $[p, q]$ 向下递归的两个区间的规模是不等的，但若我们建出递归树，可以发现递归树显然是 $\log n$ 高的，因为递归层数取决于 $[l, r]$ 的分治；而每层遍历的 $[p, q]$ 的总复杂度可以发现是 $O(n)$，于是总复杂度就是 $O(n\log n)$ 的

## CODE

这里是整体二分的代码

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "-funroll-loops", "-fdelete-null-pointer-checks")
#pragma GCC target("ssse3", "sse3", "sse2", "sse", "avx2", "avx")
using std::max;
using std::reverse;

const int MAXN =5e5+50;

/*------------------------------Parallel Binary Search------------------------------*/

int a[MAXN], n;
int ans[MAXN];

void solve(int l, int r, int p, int q, bool opt){
	int mid =(l+r)>>1;
	double Ans =-(1e9+50); int m =0;
	for(int i =p; i <= mid && i <= q; ++i){
		double res =a[i]-a[mid]+sqrt(mid-i);
		if(res > Ans){
			Ans =res;
			m =i;
		}
	}
	if(opt)
		ans[n-1-mid] =max(ans[n-1-mid], (int)ceil(Ans));
	else
		ans[mid] =ceil(Ans);
	if(l <= mid-1)
		solve(l, mid-1, p, m, opt);
	if(r >= mid+1)
		solve(mid+1, r, m, q, opt);
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	n =read();
	for(int i =0; i < n; ++i)
		a[i] =read();
	solve(0, n-1, 0, n-1, 0);
	reverse(a, a+n);/*翻转 a 数组再做一遍，相当于反着做一遍*/
	solve(0, n-1, 0, n-1, 1);
	for(int i =0; i < n; ++i)
		printf("%d\n", ans[i]);
}
```

---

## 作者：QiFeng233 (赞：1)

# SP9070 镜像题解
~~为什么那题是黑的这题是紫的~~
# Part0.题目大意
给定一个长度为 $n$ 的序列 $\{a_n\}$，对于每个 $i\in [1,n]$ ，求出一个最小的非负整数 $p$ ，使得 $\forall j\in[1,n]$，都有 $a_j\le a_i+p-\sqrt{|i-j|}$  
**~~双倍经验~~**  
# Part1.暴力方程
“任何一个Dp题，你想要去优化它，你得先有一个暴力的方程，才能说去优化，否则暴力都写不出来，你优化个寂寞啊”  
$f_i=max(arr_j+\sqrt{|i-j|})-arr_i$  
# Part2.开始优化
首先看到绝对值不爽，那去掉绝对值就$j$从$1$到$i$跑一次$\sqrt{i-j}$的，然后再从$n$到$i$跑一次$\sqrt{j-i}$的。    
接下来，~~通过打表~~可以发现决策单调性。~~我太菜了不会严格证明。~~  
[这篇博客](https://www.luogu.com.cn/blog/83547/zong-dong-tai-gui-hua-di-ben-zhi-kan-si-bian-xing-fou-deng-shi-you-hua)的引例2的证明写的挺好的。  
然后~~我太菜了不会斜率优化~~，选择分治来解决本题。  
# Part3.分治做法
可以利用决策单调性，分治解决。假设我们当前计算的区间是$[l,r]$，中点为$mid$，$f_{mid}$取得最优值时的决策点为$x_{mid}$  
$f_l$最优时，$x_l \leq x_{mid}$。同理，$x_{mid} \leq x_r$。  
我们设$solve(l,r,L,R)$表示$f_{mid}$的决策点$x_{mid}$在$[L,R]$里，那么有如下代码（核心部分）：  
其中，函数$solve1$解决的是$j$从$1$到$i$跑一次$\sqrt{i-j}$的，函数$solve2$解决的是$j$从$n$到$i$跑一次$\sqrt{j-i}$的。
```cpp
#define ll long long
#define ld long double
void solve1(int l,int r,int L,int R){
	if(l>r)return;
	int x=0,mid=(l+r)/2;
	for(int i=L;i<=min(mid,R);++i){
		ld tmp=(ld)arr[i]+(ld)sqrt((double)(mid-i));
		if(tmp>f1[mid])f1[mid]=tmp,x=i;
	}
	f1[mid]-=arr[mid];
	solve1(l,mid-1,L,x);
  	solve1(mid+1,r,x,R);
}
void solve2(int l,int r,int L,int R){
	if(l>r)return;
	int x=0,mid=(l+r)/2;
	for(int i=R;i>=max(mid,L);--i){
		ld tmp=(ld)arr[i]+sqrt((double)(i-mid));
		if(tmp>f2[mid])f2[mid]=tmp,x=i;
	}
	f2[mid]-=arr[mid];
	solve2(l,mid-1,L,x);
  	solve2(mid+1,r,x,R);
}
```
# Part4.最终AC代码
```cpp
#include<cstdio>
#include<cmath>
#define ll long long
#define ld long double
//手玩即可发现f[i]=max(arr[j]+sqrt(|i-j|))-arr[i] 
//考虑去掉绝对值的话，分两边来两遍就好了 
//打表可以证明决策单调性。严格证明我不会。 
namespace QiFeng233{
	const int maxn=5e5+10;
	int arr[maxn];
	ld f1[maxn],f2[maxn];
	int n;
	int read(){
		int x=0,c=getchar();
		while(c<'0'||c>'9')c=getchar();
		while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
		return x;
	}
	int max(int a,int b){
		return a>b?a:b;
	}
	int min(int a,int b){
		return a<b?a:b;
	}
	ld max(ld a,ld b){
		return a>b?a:b;
	}
	//注意到决策单调性之后，就可以二分解决了，和CF868F是一样的 
	void solve1(int l,int r,int L,int R){
		if(l>r)return;
		int x=0,mid=(l+r)/2;
		for(int i=L;i<=min(mid,R);++i){
			ld tmp=(ld)arr[i]+(ld)sqrt((double)(mid-i));
			if(tmp>f1[mid])f1[mid]=tmp,x=i;
		}
		f1[mid]-=arr[mid];
		solve1(l,mid-1,L,x);
	    solve1(mid+1,r,x,R);
	}
	void solve2(int l,int r,int L,int R){
		if(l>r)return;
		int x=0,mid=(l+r)/2;
		for(int i=R;i>=max(mid,L);--i){
			ld tmp=(ld)arr[i]+sqrt((double)(i-mid));
			if(tmp>f2[mid])f2[mid]=tmp,x=i;
		}
		f2[mid]-=arr[mid];
		solve2(l,mid-1,L,x);
	    solve2(mid+1,r,x,R);
	}
	void solve(){
		n=read();
		for(int i=1;i<=n;++i)arr[i]=read();
		solve1(1,n,1,n);
    	solve2(1,n,1,n);
    	for(int i=1;i<=n;++i)printf("%lld\n",(ll)ceil(max(f1[i],f2[i])));
	}
}
signed main(){
	QiFeng233::solve();
	return 0;
} 
```

---

## 作者：MCAdam (赞：1)

[题目](https://www.luogu.com.cn/problem/P3515)

题意：给出$\{a_n\}$，对于$i\in[1,n]$，求出最小的$p$，使得$\forall j\in [1,n]$有$a_j\leq a_i+p-\sqrt{|i-j|}$

即求$f(i)=\max_{j=1}^{n}\{a_j-a_i+\sqrt{|i-j|}\}$

因为有绝对值，所以可以正着做一遍，倒着做一遍，所以转化为求：

$f(i)=\max_{j=1}^{i-1}\{a_j+\sqrt{i-j}\}-a_i$

试着证一下决策单调性

设$val(j,i)=a_j+\sqrt{i-j}$

要证对于$\forall j<i$，有$val(j,i+1)+val(j+1,i)\geq val(j,i)+val(j+1,i+1)$

即$val(j,i+1)-val(j,i)\geq val(j+1,i+1)-val(j+1,i)$

直接带进去，$a_j$就没了！！！

$\sqrt{i-j+1}-\sqrt{i-j}\geq \sqrt{i-j}-\sqrt{i-j-1}$

即$\sqrt{u+1}-\sqrt{u}\geq \sqrt{u}-\sqrt{u-1}$

这不显然是错的吗（也可以求导）

想到这时：我一度怀疑四边形不等式的正确性。照理来说应该要满足四边形不等式呀？

![](https://cdn.luogu.com.cn/upload/image_hosting/v1s63p0p.png)


~~我怕不是弱智~~

这一切的一切都是在$\min$的条件下讨论的。而这道题求的是$max$，所以把上面所有的符号取反，就满足四边形不等式了。

当然，也可以用数形结合的角度来理解。$a+\sqrt{i-j}$这个函数增长率是不断减小的

然后套上板子就好啦

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=5e5+10;
int n;
int v[2][N],ans[2][N];//0是正着的,1是反着的 
struct node
{
	int p;//最优决策 
	int l,r;//管辖的区间 
}que[N];
inline double cal(int si,int j,int i)
{
	return v[si][j]+sqrt(i-j);
}
inline void solve(int si)
{
	que[1]=(node){1,1,n};//不要从0开始 
	int head=1,tail=1;
	for(int i=2;i<=n;i++)
	{
		while(head<=tail&&que[head].r<i) head++;//排除过时决策 
		que[head].l=i;
		if(cal(si,que[head].p,i)>cal(si,ans[si][i],i)) ans[si][i]=que[head].p;//跟原来的比较 
		while(head<=tail&&cal(si,i,que[tail].l)>=cal(si,que[tail].p,que[tail].l)) tail--;//整块劣的删掉 
		int low=que[tail].l,high=que[tail].r+1;//二分出第一个劣的位置 
		while(low+1<high)
		{
			int mid=(low+high)/2;
			if(cal(si,i,mid)>=cal(si,que[tail].p,mid)) high=mid;
			else low=mid;
		}
		que[tail].r=high-1;//修改最后一块 
		if(high<=n) que[++tail]=(node){i,high,n};//插入新的一块 
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&v[0][i]);
		v[1][n-i+1]=v[0][i];
		ans[0][i]=ans[1][i]=i;//有可能是本身为最优决策 
	}
	solve(0),solve(1);
	for(int i=1;i<=n;i++)
	{
		int maxn=ceil(max(cal(0,ans[0][i],i),cal(1,ans[1][n-i+1],n-i+1)));//注意反的 
		printf("%d\n",maxn-v[0][i]);
	}
	return 0;
}
```


---

## 作者：chenguanghui (赞：0)

首先给你们普及下单调队列知识吧
单调队列顾名思义就是一个有规律的队列，这个队列的规律是：所有在队列里的数都必须按递增（或递减）的顺序列队。

**单调队列的原理：**

在处理f[i]时，去除冗杂、多余的状态，使得每个状态在队列中只会出现一次；同时维护一个能瞬间得出最优解的队列，减少重新访问的时间；在取得自己所需的值后，为后续的求解做好准备。

**整理归纳单调队列的定义：**

1、维护区间最值；

2、去除冗杂状态；

3、保持队列单调（最大值是单调递减序列，最小值是单调
递增序列）；

4、最优选择在队首

**进入正题环节：**

首先，我们可以维护一个单调队列，每次比较可以通过find函数进行三分搜索两函数的交点，从得到队列里放入front数组，再将a数组翻转再单调队列，放入ed数组，
从1到n进行枚举max(ceil(front[i].second+sqrt(i-front[i].first)-eps),ceil(ed[i].second+sqrt(ed[i].first-i)-eps))
再减去对应的a数组就是答案。
详细看代码吧！
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct mode
{
	int x,index,l,r;
	mode(){}
	mode(int x,int index,int l,int r):x(x),index(index),l(l),r(r){}
};

const double eps=1e-8;
const int N=5e5+5;
deque<mode> q;
int n;
int a[N];
pair<int,int> front[N];
pair<int,int> ed[N]; 
int ans[N];

int find(int x,int ix,int y,int iy)
{
	int ans=-1;
	int l=iy,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(y+sqrt(mid-iy)+eps>=x+sqrt(mid-ix))
		{
			r=mid-1;
			ans=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	return ans;
	
}

void f()
{
	q.emplace_back(a[1],1,2,n);
	for(int i=2;i<n;i++)
	{
		int l,r=n;
		if(q.back().x>=a[i])
			continue;
		while(q.back().l>i&&q.back().x+sqrt(q.back().l-q.back().index)+eps<=a[i]+sqrt(q.back().l-i))
		{
			l=q.back().l;
			q.pop_back();
		}
		if(q.back().x+sqrt(i-q.back().index)+eps<=a[i])
		{
			q.back().l=i;
			q.emplace_back(a[i],i,i+1,n);
			continue;
		}
		int id=find(q.back().x,q.back().index,a[i],i);
		if(id==-1)
			continue;
		else
		{
			q.back().r=id-1;
			q.emplace_back(a[i],i,id,n);
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	if(n==1)	
	{
		cout<<0<<endl;
		return 0;
	}
	f();
	for(auto m:q)
	{
		for(int i=m.l;i<=m.r;i++)
			front[i]=make_pair(m.index,m.x);
	}
	while(q.size())
		q.pop_back();	
	reverse(a+1,a+n+1);
	f();
	for(auto m:q)
	{
		for(int i=m.l;i<=m.r;i++)
			ed[n+1-i]=make_pair(n+1-m.index,m.x);
	}
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(i==1)
			ans[i]=ceil(ed[1].second+sqrt(ed[1].first-i)-eps);
		else if(i==n)
			ans[i]=ceil(front[n].second+sqrt(n-front[n].first)-eps);
		else
		{
			ans[i]=max(ceil(front[i].second+sqrt(i-front[i].first)-eps),ceil(ed[i].second+sqrt(ed[i].first-i)-eps));
		}
	}
	

	for(int i=1;i<=n;i++)
		printf("%d\n",max(0,ans[i]-a[i]));
	
    return 0;
}

```


---

