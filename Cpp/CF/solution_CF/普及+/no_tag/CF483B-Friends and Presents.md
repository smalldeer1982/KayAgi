# Friends and Presents

## 题目描述

You have two friends. You want to present each of them several positive integers. You want to present $ cnt_{1} $ numbers to the first friend and $ cnt_{2} $ numbers to the second friend. Moreover, you want all presented numbers to be distinct, that also means that no number should be presented to both friends.

In addition, the first friend does not like the numbers that are divisible without remainder by prime number $ x $ . The second one does not like the numbers that are divisible without remainder by prime number $ y $ . Of course, you're not going to present your friends numbers they don't like.

Your task is to find such minimum number $ v $ , that you can form presents using numbers from a set $ 1,2,...,v $ . Of course you may choose not to present some numbers at all.

A positive integer number greater than 1 is called prime if it has no positive divisors other than 1 and itself.

## 说明/提示

In the first sample you give the set of numbers $ {1,3,5} $ to the first friend and the set of numbers $ {2} $ to the second friend. Note that if you give set $ {1,3,5} $ to the first friend, then we cannot give any of the numbers $ 1 $ , $ 3 $ , $ 5 $ to the second friend.

In the second sample you give the set of numbers $ {3} $ to the first friend, and the set of numbers $ {1,2,4} $ to the second friend. Thus, the answer to the problem is $ 4 $ .

## 样例 #1

### 输入

```
3 1 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 3 2 3
```

### 输出

```
4
```

# 题解

## 作者：enyyyyyyy (赞：1)

- 思路：

  二分答案 $V$ 是所选数中最大值，要求找出 $V$ 的最小值，可以想到找最大值的最小值就要可以用到二分。
  
- check 函数

  check 函数要实现判断，就是
  - $ mid-\dfrac{mid}{x}\ge n $
  - $ mid-\dfrac{mid}{y}\ge m $
  - $ mid-\dfrac{mid}{x\times y}\ge n+m $
  
- 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
typedef string st;
inline lint read() {
	lint s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(lint x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
lint n, m, x, y,mid,l=1,r=2e9,ans;
bool check() {
	return mid - mid / x >= n && mid - mid / y >= m && mid - mid / (x * y) >= n + m;
}
int main() {
	n=read(),m=read(),x=read(),y=read();
	while (l<=r) {//二分
		mid = (l + r) >> 1;
		if (check()) r = mid-1,ans=mid;
		else l = mid+1;
	}
	print(ans);
	return 0;
}

```

  

---

## 作者：囧仙 (赞：1)

## 题目大意

计算出最小的 $V$ ，使得 $1,2,3,\cdots V$ 可以选出两堆，大小分别为 $cnt_1,cnt_2$ ，使得第一堆不包含 $x$ 的倍数，第二堆不包含 $y$ 的倍数。

## 题解

有一个简单的结论：$1,2,3,\cdots n$ 中，是 $m$ 的倍数的数恰好有 $\left\lfloor\frac{n}{m}\right\rfloor$ 个，为 $m,2\times m,3\times m,\cdots,\left\lfloor\frac{n}{m}\right\rfloor \times m$ 。

两个人都不能选择的数字，显然是 $x\times y$ 的倍数。因此，选出来的答案必定满足 $V-\left\lfloor\frac{V}{x\times y}\right\rfloor \ge cnt_1+cnt_2$ 。同时，这些数中不能被 $x$ 整除的数有 $V-\left\lfloor\frac{V}{x}\right\rfloor$ 个，不能被 $y$ 整除的有 $V-\left\lfloor\frac{V}{y}\right\rfloor$ 个。

于是，我们找到了三个必要的条件：

- $V-\left\lfloor\frac{V}{x\times y}\right\rfloor \ge cnt_1+cnt_2$ 。

- $V-\left\lfloor\frac{V}{x}\right\rfloor \ge cnt_1$ 。

- $V-\left\lfloor\frac{V}{y}\right\rfloor \ge cnt_2$ 。

下证满足这三个条件的 $V$ 必定可以分成两堆，使得这两堆符合题目要求。

由条件一，我们剔除掉 $1,2,3\cdots V$ 中不能放入任意一堆的数，那么剩下来的数的个数必定不小于 $cnt_1+cnt_2$ ，且要么都能被选，要么只能选入某一堆。显然，如果某个数只能放入其中一堆，那么就优先放进去。下面再次分为三个讨论。

- 如果 $\left\lfloor\frac{V}{x}\right\rfloor \ge cnt_2$ ，且 $\left\lfloor\frac{V}{y}\right\rfloor \ge cnt_1$ ，那么就直接完成目标了。

- 如果 $\left\lfloor\frac{V}{x}\right\rfloor \ge cnt_1$ ，但 $\left\lfloor\frac{V}{y}\right\rfloor < cnt_2$ ，那么前者会溢出，而后者不够用，还差 $cnt_2-\left\lfloor\frac{V}{y}\right\rfloor$ 个。但是观察可知，

$$cnt_1+cnt_2-cnt_1=cnt_2\ge cnt_2-\left\lfloor\frac{V}{y}\right\rfloor$$

于是，剩下来的数字已经够用了。

- 如果 $\left\lfloor\frac{V}{x}\right\rfloor < cnt_1$ ，且 $\left\lfloor\frac{V}{y}\right\rfloor < cnt_2$ ，显然不会有任何数字被浪费，于是能达成目标。

我们终于证明了上面三个条件能符合要求。下面来求出 $V_{min}$ 吧。

---

首先整理上面的式子：

- $\left\lfloor\frac{V}{x\times y}\right\rfloor \le V-cnt_1-cnt_2$ 。

- $\left\lfloor\frac{V}{x}\right\rfloor \le V-cnt_1$ 。

- $\left\lfloor\frac{V}{y}\right\rfloor\le V-cnt_2$ 。

根据下取整的性质，有：

$$t-1< \lfloor t\rfloor \le t$$

因此，上面三个式子，可以分别转化为：

- $ \frac{V}{x\times y} -1 <\left\lfloor\frac{V}{x\times y}\right\rfloor \le V-cnt_1-cnt_2$ 。

- $\frac{V}{x} -1<\left\lfloor\frac{V}{x}\right\rfloor \le V-cnt_1$ 。

- $\frac{V}{y} -1<\left\lfloor\frac{V}{y}\right\rfloor\le V-cnt_2$ 。

重新整理后，可以得到：

$$\frac{(cnt_1+cnt_2-1)\times x\times y}{x\times y-1}< V,\frac{(cnt_1-1)\times x}{x-1}<V,\frac{(cnt_2-1)\times y}{y-1}<V$$

取最大值即可。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int a,b,x,y,v;
int main(){
    scanf("%d%d%d%d",&a,&b,&x,&y);
    v=max(v,(int)floor((double)(a+b-1)*x*y/(x*y-1)));
    v=max(v,(int)floor((double)(a-1)*x/(x-1)));
    v=max(v,(int)floor((double)(b-1)*y/(y-1)));
    printf("%d\n",v+1);
    return 0;
}
```

---

## 作者：离散小波变换° (赞：1)

## 题目大意

求最小的 $V$，使得存在全集为$\{1,2,3,\cdots V\}$的集合$A,B$，使得 $|A|=cnt_1,|B|=cnt_2,kx\notin A,ky\notin B,A\cap B=\varnothing$。

## 题解

楼上给出了一个二分的方法，并且可以通过本题。但为了挑战自我，我们尝试用公式直接推导。

- 首先有个简单的结论：$\mathbf{\{1,2,\cdots,n\}}$**中**，$\mathbf x$** 的倍数有 **$\mathbf{\lfloor\frac{n}{x}\rfloor}$**个**。

具体证明很简单。显然，$1,2,\cdots n$ 中 $x$ 的倍数为 $x,2\times x,3\times x ,\cdots,\lfloor\frac{n}{x}\rfloor \times x$，共 $\lfloor\frac{n}{x}\rfloor$ 个。

然后基于这个结论，使用容斥原理进行推导。

我们不妨设所有不含因子 $x$ 的集合为 $X$，不含因子 $y$ 的集合为 $Y$。那么 $|X|=V-\lfloor\frac{V}{x}\rfloor,|Y|=V-\lfloor\frac{V}{y}\rfloor,|X\cup Y|=V-\lfloor\frac{V}{x}\rfloor-\lfloor\frac{V}{x}\rfloor+\lfloor\frac{V}{xy}\rfloor$。（最后一个式子可以这样理解：从 $V$ 个数中，剔除掉 $x$ 的倍数和 $y$ 的倍数，此时多剔除了一次 $xy$ 的倍数）。为了满足题目要求，我们需要满足三个条件：

$$|X|\ge cnt_1,|Y|\ge cnt_2,|Y|-[cnt_1-(|X|-|X\cap Y|)]\ge cnt_2$$

第三个条件是，贪心地将是 $y$ 的倍数的数尽量塞到 $X$ 里面，直到塞不下再使用 $(X\cap Y)$ 这些数字。这样子就能使得塞入 $Y$ 的数字尽可能地多。

- 一个关于下取整的结论：$x \ge\lfloor x\rfloor>x-1$。

将数据带入条件一，可以得到：

$$\begin{aligned}V-\left\lfloor\frac{V}{x}\right\rfloor & \ge cnt_1\cr  V-cnt_1 & \ge \left\lfloor\frac{V}{x}\right\rfloor> \frac{V}{x}-1 \cr Vx-x\times cnt_1 & > V-x\cr V &> \frac{(cnt_1-1)\times x}{x-1}\end{aligned}$$ 

同理，我们可以得到 $V > \frac{(cnt_2-1)\times y}{y-1}$。

主要是条件三比较繁琐：

$$\begin{aligned}|Y|-|X|-|X\cap Y| & \ge cnt_1+cnt_2\cr 2\times \left\lfloor\frac{V}{x}\right\rfloor-V-\left\lfloor\frac{V}{xy}\right\rfloor & \ge cnt_1+cnt_2 \cr 2\times \left\lfloor\frac{V}{x}\right\rfloor-V-cnt_1-cnt_2 & \ge \left\lfloor\frac{V}{xy}\right\rfloor> \frac{V}{xy}-1 \cr 2xy\times \left\lfloor\frac{V}{x}\right\rfloor-Vxy-xy(cnt_1+cnt_2) & > V-xy \cr \dfrac{V}{x} \ge  \left\lfloor\frac{V}{x}\right\rfloor & > \dfrac{V-xy+Vxy+xy(cnt_1+cnt_2)}{2xy} \cr 2Vy & >V-xy+Vxy+xy(cnt_1+cnt_2) \cr (2y-1-xy)V & > xy(cnt_1+cnt_2-1) \cr V & > \dfrac{xy(cnt_1+cnt_2-1)}{2y-1-xy}\end{aligned}$$

至此，三个式子都被我们化简掉了。只需要取三者的最大值的上取整即可。



---

## 作者：ZJMZJM (赞：1)

一道大水题

V是所选数中最大值，要求找出V的最小值。

可以想到找最大值的最小值就要可以用到二分。

需要注意在1~V中，X和Y的公倍数是不可以被选的,但X的倍数可以给2号,Y的倍数可以给1号

```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>//头文件 
#define For(k,i,j) for(int k=i;k<=j;k++)//for循环 
#define ll long long //long long 
#pragma GCC optimize(4)//O4
using namespace std;
inline int read()
{
    char ch;
    int res=1;
    while((ch=getchar())<'0'||ch>'9') if(ch=='-') res=-1;
    res*=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}
int main()
{
    int cnt1=read(),cnt2=read(),x=read(),y=read();
    ll l=0,r=1e15;
    while(l<=r)
	{
        ll mid=(l+r)/2;
        ll rx=mid/x,ry=mid/y,re=mid/(x*y);
        if(mid-re>=cnt1+cnt2&&mid-rx>=cnt1&&mid-ry>=cnt2) 
			r=mid-1;
        else 
			l=mid+1;
    }
    printf("%lld\n",l);//记得long long输出 
	return 0; 
}
```

---

## 作者：The_jester_from_Lst (赞：0)

简易二分题。

考虑从一个较大范围中二分选取 $v$ 值。对于二分中产生的任意 $mid$ 值，我们有 $3$ 个具体判断方式：

1. $\lfloor \frac{mid}{x} \rfloor\le mid-cnt1$。因为在 $mid$ 个数中必然有 $\lfloor \frac{mid}{x} \rfloor$ 个数是 $x$ 的倍数，而这些数是不能给 $A$ 的。所以我们需要保证除去这些数后仍能有至少 $cnt1$ 个数可以给 $A$。

2. $\lfloor \frac{mid}{y} \rfloor\le mid-cnt2$。原理同上。
3. $\lfloor \frac{mid}{x\times y} \rfloor\le mid-(cnt1+cnt2)$。由于 $x$ 的倍数与 $y$ 的倍数在每 $x\times y$ 个数后会出现重叠，出现重叠的数 $A$，$B$ 都不能给，这些数我们还得额外排除掉。

依照这三个条件二分并判断，若满足条件，记录答案即可。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
inline void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
int cnt1,cnt2,x,y,l,r,mid,v=INT_MAX;
signed main(){
	cnt1=rd();cnt2=rd();x=rd();y=rd();
	l=1;r=1e9;
	while(l<=r){
		mid=(l+r)>>1;
		if(mid/x<=mid-cnt1&&mid/y<=mid-cnt2&&mid/(x*y)<=mid-(cnt1+cnt2))r=mid-1,v=min(v,mid);
		else l=mid+1;
	}
	wr(v);
	return 0;
}
```


---

## 作者：小恐 (赞：0)

$V$的最小值就是最优构造的最大值。因为要求最大值的最小值，所以想到了二分。

那如何判断一个数是否可作为答案呢？因为$x\ne y$且$x$，$y$都为素数，所以一个数如果能被这两个数中某一个选上的话，设这个数为$k$，则 $\operatorname{lcm}(x,y)\nmid k$，即$(x\times y)\nmid k$。所以能被选上的数的个数为$V-\left\lfloor\dfrac{V}{x\times y}\right\rfloor$。所以$V-\left\lfloor\dfrac{V}{x\times y}\right\rfloor\ge cnt1+cnt2$。同理$V-\left\lfloor\dfrac{V}{x}\right\rfloor\ge cnt1$，$V-\left\lfloor\dfrac{V}{y}\right\rfloor\ge cnt2$。~~显然~~满足这3个条件就符合题意了。

然后要求出二分的范围。最小不用分析得很细，取1即可，答案不可能比1小。然后是最大值，当$V>2\times 10^9$时，$V-\left\lfloor\dfrac{V}{x}\right\rfloor\ge V-\left\lfloor\dfrac{V}{2}\right\rfloor> 10^9>cnt1$，所以比$2\times 10^9$大的数都不行，最大值设成$2\times 10^9$就行了，复杂度$O(\log 2\times 10^9)$，能过。

上代码：
```cpp
#include<stdio.h>
using namespace std;
const int NR=1e5+5;
const int MR=1e5+5;
const int INF=0x3f3f3f3f;
typedef long long LL;
int read()
{
	int x=0;
	int bei=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			bei=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*=bei;
}
int cnt1,cnt2,x,y;
inline bool check(int k)
{
	if(k-k/(x*y)<cnt1+cnt2)
		return 0;
	if(k-k/x<cnt1)
		return 0;
	if(k-k/y<cnt2)
		return 0;
	return 1;
}
int main()
{
	cnt1=read(),cnt2=read(),x=read(),y=read();
	int l=1,r=2e9;
	int ans;
	int cnt=0;
	while(l<=r)
	{
		int mid=l+(r-l>>1);
		if(check(mid))
			ans=mid,r=mid-1;
		else
			l=mid+1;
	}
	printf("%d",ans);
	return 0;
}


```


---

