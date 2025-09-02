# [NOI Online #2 提高组] 涂色游戏

## 题目背景

1s 256M

## 题目描述

你有 $10^{20}$ 个格子，它们从 $0$ 开始编号，初始时所有格子都还未染色，现在你按如下规则对它们染色：

1. 编号是 $p_1$ 倍数的格子（包括 $0$ 号格子，下同）染成红色。
2. 编号是 $p_2$ 倍数的格子染成蓝色。
3. 编号既是 $p_1$ 倍数又是 $p_2$ 倍数的格子，你可以选择染成红色或者蓝色。

其中 $p_1$ 和 $p_2$ 是给定的整数，若格子编号是 $p_1$ 或 $p_2$ 的倍数则它必须要被染色。在忽略掉所有未染色格子后，你不希望存在 $k$ 个连续的格子颜色相同，因为你认为这种染色方案是无聊的。现在给定 $p_1$, $p_2$, $k$，你想知道是否有一种染色方案不是无聊的。


## 说明/提示

| 测试点编号 | $p_1$, $p_2 \leq$ | $k \leq$ | $T \leq$ |
| :-- | :-- | :-- | :-- |
| 1 $\sim$ 3 | $15$ | $15$ | $3375$ |
| 4 $\sim$ 6 | $10^3$ | $10^3$ | $10^4$ |
| 7 $\sim$ 8 | $10^3$ | $10^3$ | $10$ |
| 9 $\sim$ 10 | $10^5$ | $10^3$ | $10^3$ |
| 11 $\sim$ 12 | $10^5$ | $5 \times 10^5$ | $10$ |
| 13 $\sim$ 14 | $10^5$ | $5 \times 10^5$ | $10^5$ |
| 15 | $10^9$ | $10^9$ | $10$ |
| 16 $\sim$ 20 | $10^9$ | $10^9$ | $10^6$ |

对于所有测试点：$1 \leq T\leq 10^6$，$1\leq p_1,p_2$，$k\le 10^9$。

## 样例 #1

### 输入

```
4
2 10 4
2 3 6
1 4 7
1 1 2```

### 输出

```
No
Yes
Yes
Yes```

## 样例 #2

### 输入

```
8
370359350 416913505 3
761592061 153246036 6
262185277 924417743 5
668232501 586472717 2
891054824 169842323 6
629603359 397927152 2
2614104 175031972 68
924509243 421614240 4```

### 输出

```
Yes
Yes
Yes
No
No
No
Yes
Yes```

# 题解

## 作者：chen_zhe (赞：55)

这里是民间数据的 std：

不妨设 $p_1<p_2$，且 $p_1,p_2$ 互质。 

则会发现：最坏情况，也就是从 $kp_2+1$ 到 $(k+1)p_2-1$ 这个连续串内塞 $p_1$ 所对应的颜色。

这样就有 $\dfrac{p_2-2}{p_1}+1$ 个连续块，将其与 $k$ 比较即可。

因为可能不互质，所以可以两边除 $\gcd(p_1,p_2)$ 即可。 

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

inline int gcd(int a,int b)
{
	return !b?a:gcd(b,a%b);
}

int main()
{
	//freopen("color.in","r",stdin);
	//freopen("color.out","w",stdout);
	int T=read();
	while (T--)
	{
		int p1=read(),p2=read(),k=read();
		if (k==1)
		{
			puts("NO");
			continue;
		}
		if (p1>p2)
			swap(p1,p2);
		int GCD=gcd(p1,p2);
		p1/=GCD;
		p2/=GCD;
		puts((p2>2 && (p2-2)/p1+1>=k)?"NO":"YES");
	} 
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
```


---

## 作者：华山骚竹 (赞：17)

额。。开始看到这题的时候那个10^20把我吓了一跳，所以暴力是不行的了 ~~(这不废话)~~ 

仔细想想不难发现，每lcm(p1,p2)个数就是一个循环，因此只需要考虑这一个循环节内的情况就好了

首先设p1>p2（p1是红色，p2是蓝色），然后关于任意涂色的位置，也就是第lcm（p1,p2）个格子那里，比起涂蓝色，肯定涂红色是一个更优的方法，因为左右两边最近的一定是蓝色

**然后就是最关键的求最长连续颜色长度的问题了**，我也不想用什么复杂的数学推理 ~~（其实是不会）~~ ，我就想起了抽屉原理。我们不妨把相离最近的两个红色格子之间当做一个抽屉，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/9j1wobzk.png)

我们可以求出，一个循环节内有p1/gcd(p1,p2)个蓝色格子，有p2/gcd(p1,p2)个红色格子。

**但这里有一个需要注意的一点**，上面已经知道了，第lcm(p1,p2)个格子那里需要涂红色，所以实际上是只有p1/gcd(p1,p2)-1个蓝色格子（我就忘记减了结果没能AC）

然后就轮到我们的抽屉原理啦，将蓝色格子个数设为n1，红色格子个数设为n2，懂抽屉原理的都知道，每个抽屉里最多只会有n1/n2或n1/n2+1个蓝色格子，如果n1%n2=0的话，就是n1/n2个蓝色格子，否则就是n1/n2+1个

最后与题目所给的k比一下就得出答案啦

**需要注意的点**  
1、当k=1时，无论怎么涂都是No

2、当k>1时，如果p1=p2，那么一定是Yes（因为可以交叉涂了）

3、建议使用long long（死在这无数次的我）   

~~4、这两个特判我都没忘hiahiahia(ಡωಡ)，但我还是WA了（为什么说着说着就哭了）~~

那么最后是通过了的代码

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}
long long T,p1,p2,k,n1,n2,now_gcd,n;
int main()
{
	//freopen("color.in","r",stdin);
	//freopen("color.out","w",stdout);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld %lld %lld",&p1,&p2,&k);
		if(k<2)
		{
			printf("No\n");
			continue;
		}
		if(p1==p2)
		{
			printf("Yes\n");
			continue;
		}
		if(p1<p2)
		p1^=p2^=p1^=p2;
		now_gcd=gcd(p1,p2);
		n1=p1/now_gcd-1;
		n2=p2/now_gcd;		
		if(n1%n2!=0)
			n=(n1/n2)+1;
		else
			n=n1/n2;
		if(n>=k)
		printf("No\n");
		else
		printf("Yes\n");
	}
	return 0;
}

```


---

## 作者：Register (赞：8)

~~去原题那交了一下，过了，差点自闭。~~

不妨设 $p_1\ge p_2$ 。

- 先看个奇怪的条件：就是随意染色。

显然选择红色（$p_1$）因为它左右一定都是蓝色（$p_2$）

- 接着你看这个 $10^{20}$ 有没有什么用呢？

没有。只需要考虑到 $\operatorname{lcm}(p_1,p_2)$ 。

因为 $\operatorname{lcm}(p_1,p_2)$ 已经确定了颜色。

- 最大的连续一段颜色显然是蓝色（$p_2$）。

如何求最大的连续一段颜色呢？

这一段颜色显然是这样的： $mp_1<np_2<(n+1)p_2<\cdots<(n+k)p_2<(m+1)p_1$

当 $t=np_2-mp_1\ (t>0)$ 最小时， $k$ 最大。

那么可以得到 $mp_1+np_2=-t$ 。

根据裴蜀定理，我们知道 $mp_1+np_2=-t$ 有解当且仅当 $\gcd(p_1,p_2)|-t$ 。

$m,n$ 是什么不重要，因为只需要 $t$ 就能求出 $k$ 是多少。

显然 $t=\gcd(p_1,p_2)$ 。

然后就可以求出 $k=\frac{p_1-t-1}{p_2}$ （下取整）

不过实际的 $k$ 还要 $+1$ ，再和题面给出的 $k$ 比较大小即可。

```cpp
#include <cstdio>
inline int read(){
    char ch=getchar();int res=0,w=1;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
    return res*w;
}
int t,a,b,k,ans;
int gcd(int a,int b) {return b?gcd(b,a%b):a;}
void solve(){
	a=read();b=read();k=read();
	if(b>a) {int l=a;a=b;b=l;}
	ans=(a-gcd(a,b)-1)/b+1;puts(ans>=k?"NO":"YES");
}
signed main(){
	//freopen("color.in","r",stdin);freopen("color.out","w",stdout);
	t=read();while(t--) solve();
	//fclose(stdin);fclose(stdout);
    return 0;
}

```
不过要特判一下 $p_1=p_2=k=1$ 的情况，所以我代码挂了（应该只会有一个测试点吧。。。）

---

## 作者：hanzhongtlx (赞：5)

## [更好的阅读体验点这里>_<](https://www.cnblogs.com/tlx-blog/p/12805704.html)

一种新的解法，对数论能力要求**更**低！    
考场上推错式子了，只有 25 分.....    

题目链接：[P6476 [NOI Online #2 提高组]涂色游戏（民间数据）](https://www.luogu.com.cn/problem/P6476)    

声明：此文中用 $x,y$ 代表 $p1,p2$ ，$(x,y)$ 指 $\gcd(x,y)$当然还可能是开区间，$[x,y]$ 指 $lcm(x,y)$当然还可能是闭区间，并满足 $x<y$。

我们做这个题的第一反应一定是这样的：   
每隔一个 $y$ 倍数的区间都有 $\left\lfloor\dfrac{y}{x}\right\rfloor$ 个 $x$ 的倍数出现，然后和 $k$ 比大小即可。   
然而被无情 hack 了，such as:
```
输入：
1
5 9 2
输出：
NO

```   
我们发现在 $(9,18)$ 中有 $2$ 个 $x$ 的倍数：$10$，$15$。    

那我们可以利用一个规律：   
在 $y$ 和 $x$ 没有整除关系时，每一段 $y$ 内 $x$ 倍数出现次数 $\in\{\left\lfloor\dfrac{y}{x}\right\rfloor,\left\lfloor\dfrac{y}{x}\right\rfloor+1\}$ 。  
为什么呢？   
我们设 $z=\left\lfloor\dfrac{y}{x}\right\rfloor$。   
首先不可能更少的次数，因为 $(0,y)$ 中浪费最少了。   
假如存在更多的次数，比如 $z+2$，
中间的空隙算上就已经 $>y$ 了。   
显然得证。   
所以最上面的解法只存在一种可能：   
我们设**第一次**在 $y$ 区间内出现 $z+1$ 个 $x$ 倍数的区间为$(my,(m+1)y)$，其中的 $x$ 分别为 $kx,(k+1)x......(k+z)x$。   
那么这个区间是样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/ufucxbvb.png)   

（字丑不要介意啦quq   
此时显然满足：
$$\begin{cases}my<kx\\(m+1)y>(k+z)x\end{cases}$$     

我们注意：
我们定义的数都是**第一次**出现这种情况的，所以显然：
$$k=mz+1$$    
结合一下：
$$\begin{cases}my<(mz+1)x\\(m+1)y>(mz+z+1)x\end{cases}$$   
容易解得：
$$\begin{cases}m<\dfrac{x}{y-zx}\\\\m>\dfrac{(z+1)x-y}{y-zx}\end{cases}$$    
 
显然在 $y-zx=0$ 即 $x|y$ 是无意义，我们需要特判一下，循环节只有一个有 $z-1$ 个数，这时候直接判断即可。
 
这就完了吗？   
并没有，我们显然发现每个 $y$ 区间的 $x$ 倍数出现数在每个 $[x,y]$ 长的区间都有循环节。  
那么显然：
$$(m+1)y\leqslant [x,y]=\dfrac{xy}{(x,y)}$$   
容易得到：
$$m\leqslant\dfrac{x}{(x,y)}-1$$   
也就是：
$$m<\dfrac{x}{(x,y)}$$
还有一个条件:
$$m>0$$   

那么问题转化成了：
是否存在整数 $m$ 满足：
$$m\in(\max\{0,\dfrac{(z+1)x-y}{y-zx}\},\min\{\dfrac{x}{(x,y)},\dfrac{x}{y-zx}\})$$    
这些过程是可以直接模拟的。   
代码如下：
```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

#define read(x) scanf("%d",&x)

int t,x,y,z,k;
double l,r;
int g;

inline int gcd(int a,int b){return b==0?a:gcd(b,a%b);}

int check(double l,double r)//判断区间是否有正整数
{
	if(l>r) return 0;
	l=ceil(l),r=floor(r);
	if(l<=r) return 1;
	else return 0;
}

int main()
{
	read(t);
	while(t--)
	{
		read(x),read(y),read(k);
		if(x>y) swap(x,y);
		if(k==1){printf("NO\n");continue;}
		else if(y%x==0)
		{
			z=y/x-1;
			if(k<=z){printf("NO\n");continue;}
			else{printf("YES\n");continue;}
		}
		else
		{
			z=y/x,g=gcd(x,y),g=x/g;
			if(k<=z){printf("NO\n");continue;}
			else if(k==z+1)
			{
				l=max((double)0,((double)(z+1)*(double)x-(double)y)/(y-z*x));
				r=min(double(g),(double)x/(y-z*x));
				if(check(l,r)){printf("NO\n");continue;}
				else printf("YES\n");
				continue;
			}
			else{printf("YES\n");continue;}
		}
	}
	return 0;
}
```
然而这样只有 $85\;pts$,为啥呢？   
因为我们要判断的区间有可能是这个亚子：
$$(5,6)$$   
我们需要一个小 trick ,运用极限思想，把区间改成这样：
$$(5+eps,6-eps)$$   
就可以 $AC$ 了。   
总的来说，这种做法比小学奥数还小学奥数，只要够细致就可以得到答案。   
最后附上 $AC$ 代码：
```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

#define read(x) scanf("%d",&x)

int t,x,y,z,k;
long double l,r;
int g;

inline int gcd(int a,int b){return b==0?a:gcd(b,a%b);}

int check(double l,double r)
{
	if(l>r) return 0;
	l+=0.0000001,r-=0.0000001;
	l=ceil(l),r=floor(r);
	if(l<=r) return 1;
	else return 0;
}

int main()
{
	read(t);
	while(t--)
	{
		read(x),read(y),read(k);
		if(x>y) swap(x,y);
		if(k==1){printf("NO\n");continue;}
		else if(y%x==0)
		{
			z=y/x-1;
			if(k<=z){printf("NO\n");continue;}
			else{printf("YES\n");continue;}
		}
		else
		{
			z=y/x,g=gcd(x,y),g=x/g;
			if(k<=z){printf("NO\n");continue;}
			else if(k==z+1)
			{
				l=max((double)0,((double)(z+1)*(double)x-(double)y)/(y-z*x));
				r=min(double(g),(double)x/(y-z*x));
				if(check(l,r)){printf("NO\n");continue;}
				else printf("YES\n");
				continue;
			}
			else{printf("YES\n");continue;}
		}
	}
	return 0;
}
```

---

## 作者：_CHO (赞：4)

看到题解里似乎没有我这种~~瞎草的~~方法，于是来水一发

我们要充分发挥OI精神 ~~大胆猜想 不用证明~~

~~首先这题原题来自CF1260C，但是~~出题人改了题

# K可以等于$1$

不要小看这个条件，在洛谷的数据中如果没有特判的话，只有20pts

~~我jio得官方数据不会这么草~~

下面进入正题，首先我们忽略掉没有用的格子。

显然，如果一个格子有用，那么它要么是$p1$的倍数要么是$p2$的倍数。

题目则是在求**最少有多少个格子的颜色是连续的**

我们假设$p1<p2$，他们的最小公倍数为$q$，那么显然有

- 无论左侧还是右侧距离$q$最近的格子，都只能是$p1$的倍数。

- 为保证连续的颜色相同的格子尽可能少，$q$的颜色应该与$p2$相同

并且我们简单举例就可以知道

- $p1$和$p2$除以他们的最大公约数，可以简化运算，且对答案没有影响

并且我们还可以显然得出

- 我们只需要考虑$(0,q)$这一部分的格子，因为每到$nq$的时候就相当于是重新开始了一个循环。又因为$q$的颜色与$p2$相同，所以我们也不需要考虑$q$这个格子。

因为$p1$和$p2$是在互相插空，我们感性理解可以想到答案应该与$p2%p1$和$p2/p1$有关~~关于这一点手玩几个样例就能想到~~

最后在注意一下余数为$1$时候的特判，~~就能轻松拿到$20pts$啦~~

特判$k==1$才可以$100pts$

```cpp
#include <bits/stdc++.h>
using namespace std;

int gcd(int a,int b){
	return (b==0)?a:gcd(b,a%b);
}
int main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--){
		int p1,p2,k;
		scanf("%d%d%d",&p1,&p2,&k);
		if(p1>p2) swap(p1,p2);
		int u=gcd(p1,p2);
		p1/=u;
		p2/=u;
		int ans=p2%p1,res;
		if(ans==0) res=p2/p1 - 1;
		else if(ans==1) res=p2/p1;
		else res=p2/p1 + 1;
		if(k==1) printf("NO\n");   //这一行，80pts
		else if(k>res) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```
完结，撒花！

求过QAQ


---

## 作者：CircleOO (赞：3)

本题解法同 https://codeforces.com/contest/1260/problem/C 

不难发现，出现的较为密集（即$p1$和$p2$中的较小值）的颜色才会导致不符合$k$个方块内不同色的要求。

因此我们假设$p1 \le p2$（红方块不比蓝方块出现得稀疏），如果不符合，可以将$p1$和$p2$换过来，不影响最终答案。

将所有需要涂颜色的方块排在一起后，我们发现红色方块会被一个个的蓝色方块方块隔开。

我们现在所需要考虑的就是在每两个相邻的蓝色方块之间，最多能够有多少个红色方块，并检验这些红色方块的数目有没有大于等于$k$。

当蓝色方块下一个就是红色方块时，这个区间内的红色方块数目肯定是最多的，因为有最多的空间留给红色方块继续出现。

![](https://cdn.luogu.com.cn/upload/image_hosting/bfin40dx.png)

当$\gcd(p1, p2) = 1$的时候，一定能找到这样两个编号连续的方块，，因为方块的位置一定对应$p1 * x - p2 * y = 1$ 的解。

此时，我们需要检验的就是$\lceil\frac{p_2 - 1}{p1}\rceil \le k - 1$。

在这个蓝色方块到下一个蓝色方块之间，有$p_2 - 1$个空位，而这些空位最多可以塞入$\lceil\frac{p_2 - 1}{p1}\rceil$个红色方块。因此如果任意两个蓝色方块之间最多只能塞下 $k - 1$个红色方块，就不会导致出现无聊的填色方案。

而如果$\gcd(p1, p2) \ne 1$，我们只需要把$p1$,$p2$每一个数都除以它们的最大公约数，使得$\gcd(p1, p2) = 1$，再判断即可，不影响最终结果（因为只是相当于把中间那些没有涂色的方块个数缩了一下），如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/04mz9kby.png)

**这里还需要加特殊判定（我考试的时候也没加，看了讨论帖才发现有必要qwq)。
即k = 1的时候不论如何方案都是无聊的。**

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x = 0;
	char c = getchar();
	while (!isdigit(c))
	{
		c = getchar();
	}
	while (isdigit(c))
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	return x;
}
long long gcd(long long x, long long y)
{
	return (y == 0) ? x : gcd(y, x % y);
}
int T;
int main()
{
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	T = read();
	while (T--)
	{
		long long p1, p2, k;
		p1 = read();
		p2 = read();
		k = read();
		if (k == 1)
		{
			printf("No\n");
			continue;
		}
		if (p1 > p2) swap(p1, p2);
		long long g = gcd(p1, p2);
		p1 /= g;
		p2 /= g;
		if ((k - 1) * p1 >= p2 - 1)
		{
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}
```




---

## 作者：hekaiyu (赞：2)

# 题意
一个神奇的填色游戏 。
# 分析
首先我们可以把 $10^{20}$ 格子划分成几个区间 ，使得每个区间的涂色方案一样。所以我们将区间划分为好几个长度为 $\operatorname{lcm}(a,b)$ 的小区间 。

为什么是等价的？

可以把题目看作有两个小球在跳，把 $\operatorname{lcm}(a,b)\times n$ 作为起始点 
那么他们一定会在下一个个起始点相遇进行新一轮弹跳 。

那么每个起始点该染成什么颜色呢？

由于 $p1,p2$ 等价，我们假设 $p1\le p2$ 则起始点的左右两边肯定是红色（均忽略没染色的格子）所以我们将所有起始点染成蓝色是最优的 。

现在我们的问题已经转到每个区间了。

我们再进行划分，在每个 $p2$ 弹跳的区间内讨论 。

什么情况下区间染成红色的格子最多呢？

显然我们要贪心的把区间内的第一个红点左移 。（离起始点位置最近）得到距离式子 $x\times a -y\times b,x\in N^*,y\in N^* $ 这不就是[裴蜀定理](https://www.luogu.com.cn/problem/P4549)吗？
最小值 $\gcd(a,b)$ 。

结果就出来了，最多的连续红色个数 $(b-\gcd(a,b)-1)/a+1<k$

再看看 $k=1$显然不满足。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b); 
}
int main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	int t=0;
	scanf("%d",&t);
	while(t--){
		int a,b,k;
		scanf("%d%d%d",&a,&b,&k);
		if(a>b)swap(a,b);
		int c=gcd(a,b);
		if(k==1){
		printf("No\n");continue;}
		if((b-c-1)/a+1>=k)printf("No\n");
		else printf("Yes\n");
	}
	return 0;
} 
```



---

## 作者：small_rubbish (赞：1)

首先，我们需要知道的是，如果既能被染成红色也能被染成蓝色应该染成什么颜色？$p1$ 和 $p2$ 中小的那个数出现的频率肯定大，所以染成大的那个颜色。当然，我们可以先约分一下。用 $a$ 代表小的那个，$b$ 代表大的那个。

现在就相当于找一个 $k$，似的 $k \times b \sim (k+1) \times b$ 中 $a$ 的出现次数最多。显然，如果 $a\space | \space k \times b-1$，那么肯定最大，所以用一个 exgcd 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b){return b==0?a:gcd(b,a%b);}
void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	long long z=x;
	x=y,y=z-a/b*y;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		long long a,b,k,x,y,p;
		scanf("%lld%lld%lld",&a,&b,&k);
		if(k==1)
		{
			printf("No\n");
			continue;
		}
		if(a>b)swap(a,b);
		p=gcd(a,b),a/=p,b/=p;
		exgcd(a,b,x,y);
		p=x/b,x+=p*b,y-=p*a;
		if(y<=0)x-=b,y+=a;
		if((y*b-1)/a-(y-1)*b/a>=k)printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}
```

---

## 作者：QiFeng233 (赞：1)

我的做法比较玄学。首先，注意到这玩意儿是有循环节的，所以我们只用考虑 $lcm(p_1,p_2)$ 以内的。

然后我们假设 $p_1>p_2$。

转化一下思路，关键来了：把两个 $p_1$ 之间叫做大块，两个 $p_2$ 之间叫做小块，那么有：

大块数量 $\times (k-1) \geq $ 小块数量 $-1$

特判 $k=1$。

在原题那边过了。

```cpp
#include<cstdio>
#include<algorithm>
using std::swap;
namespace QiFeng233{
	typedef long long ll;
	int t;
	ll p1,p2,k;
	ll gcd(ll a,ll b){
		if(b)return gcd(b,a%b);
		else return a;
	}
	void solve(){
		scanf("%d",&t);
		while(t--){
			scanf("%lld%lld%lld",&p1,&p2,&k);
			if(k==1){
				printf("NO\n");
				continue;
			}
			if(p1<p2)swap(p1,p2);
			ll g=gcd(p1,p2);
			ll l=p1*p2/g;
			ll m=l/p1,n=l/p2-1,x=k-1;
			if(m*x>=n)printf("YES\n");
			else printf("NO\n");
		}
	}
}
signed main(){
	//freopen("color.in","r",stdin);
	//freopen("color.out","w",stdout);
	QiFeng233::solve();
	return 0;
}
```

---

