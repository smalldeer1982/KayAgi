# Count Triangles

## 题目描述

给出四个整数$A,B,C,D$ ，其中$1 \leq A \leq B \leq C \leq D \leq 5 \cdot 10^5$
 
求三边长分别为 $x,y,z$ 并且满足 $A \leq x \leq B \leq y \leq C \leq z \leq D$ 的非退化三角形（三顶点不共线）的个数

## 样例 #1

### 输入

```
1 2 3 4```

### 输出

```
4```

## 样例 #2

### 输入

```
1 2 2 5```

### 输出

```
3```

## 样例 #3

### 输入

```
500000 500000 500000 500000```

### 输出

```
1```

# 题解

## 作者：b6e0_ (赞：16)

打完CF又来写题解啦~求兹磁qwq（第一次AC div2的D题）

[CF题面传送门](https://codeforces.com/contest/1355/problem/C) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1355C) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1355C)

首先补充一个小学三四年级就学过的知识：三角形三边的关系。

对于三角形的三条边$a,b,c$($a\le b\le c$)，一定满足$a+b>c$（必须大于$c$）。这个就不证了，比较简单。

---
推式子。

首先看到数据范围是$5\times10^5$，我们就可以枚举一维再计算。我首先想到的是枚举$z$，可是$a$和$b$不好计算组数。为了可以使$x,y,z$都能知道组数，我想到枚举$a+b$的和为$i$。下面我们分别看$z$和$x,y$怎么求组数。

$z$应该很好求：$z$有两个取值范围，$[c,i-1]$和$[c,d]$，两个取方案数小的那一个。

$x,y$稍微有点麻烦，我赛时调了很久。

1. $x$和$y$的最小取值是$a$和$b$，我们就可以将$i$比$a+b$多的部分往$a$和$b$上面加。设$i-a-b=j$，则有这几种方法：$a,b+j$,$a+1,b+j-1$,$a+2,b+j-2$......$a+j-1,b+1$,$a+j,b$一共$j+1$种。但是，如果$a+j>b$或者$b+j>c$，就没有这么多了。

2. 还有一种考虑方法：$x$和$y$的最大取值是$b$和$c$，我们就可以将$i$比$b+c$少的部分往$b$和$c$上面减。设$b+c-i=k$，则有这几种方法：$b,c-k$,$b-1,c-k+1$,$b-2,c-k+2$......$b-k+1,c-1$,$b-k,c$一共$k+1$种。但是，如果$b-k<a$或者$c-k<b$，就没有这么多了。

其实当$a+j>b$或者$b+j>c$时，第二种计算方法一定是正确的。当$b-k<a$或者$c-k<b$时，第一种计算方法一定是正确的。但是，有反例（这是我对拍出来的）：
```
1 3 3 3
```
上面两种方法输出的是$4$，其实答案是$3$。所以，我们就要考虑第三种计算方法。

3. 当不考虑$i$的情况时，有$\min(b-a+1,c-b+1)$种。

将这$3$种情况取$\min$，就能得出最终$x,y$的方案数。

由于调试的原因，代码比较长：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b,c,d,i,ans=0;//建议开long long
	cin>>a>>b>>c>>d;
	for(i=a+b;i<=b+c;i++)//枚举
		ans+=min(max(0ll,i-c),d-c+1)*min(i-a-b+1,min(c+b-i+1,min(c-b+1,b-a+1)));//式子
	cout<<ans;
	return 0;
}
```
时间复杂度是$O(c-a+1)$。

---
上面是我赛时想出来的。赛后我想出来了一种更简洁的方法。

首先枚举的时候可以做一个小优化：左端点优化为$\max(c+1,a+b)$。

按照这种枚举方法，$x$确定了，$y$就能确定。$y$确定了，$x$就能确定。所以我们只需要考虑$x$。$x$有两种取值范围：$[a,b]$（考虑$x$）和$[i-b,i-c]$（考虑$y$再减）。于是，更短的代码出现了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b,c,d,i,s=0;
	cin>>a>>b>>c>>d;
	for(i=max(c+1,a+b);i<=b+c;++i)//循环做了一个小优化
		s+=(min(d+1,i)-c)*(min(i-b,b)-max(i-c,a)+1);//新式子
	cout<<s;
	return 0;
}
```
时间复杂度是$O(\min(b,c-a+1))$。

---

## 作者：流绪 (赞：14)

差分前缀和！十分无脑的做法！

首先显然有 $X+Y>Z$,考虑枚举 $Z$，那么就需要算出符合的 $X+Y$ 的值，暴力的话要 $n^2$，考虑优化他！

我们可以枚举 $X+Y$ 的长度，差分前缀和搞一下就可以算出每一个长度若可能为 $X+Y$，他会有几种组成情况，然后再反着前缀和一下就可以算出 $X+Y$ 大于当前长度的种数有多少！我直接遍历所有长度了，应该可以优化！

那么我们就可以在枚举 $Z$ 时 $O(1)$ 查询符合的种类数目啦，然后统计一下就好了。

下面是 $AC$ 代码！
```cpp
	ios::sync_with_stdio(0);
	int a,b,c,d;
	cin >> a >> b >> c >> d;
	rep(i,a,b)
	{
		sum[i+b]++;
		sum[i+c+1]--;//差分
	}
	rep(i,1,maxn)
		sum[i] += sum[i-1];//前缀和
	per(i,maxn-1,0)
		sum[i] += sum[i+1];//反着前缀和
	int ans = 0;
	rep(i,c,d)
		ans += sum[i+1];//统计答案
	cout << ans;
	return 0;
```


---

## 作者：Eibon (赞：7)

问题容易转化为 $x+y \ge z$，因为 $x_{\min} = A$，$y_{\min} = B$，所以 $x+y$ 的取值范围为 $\left[\max\left(c+1,a+b\right),b+c\right]$。

令 $i=x+y$。

对于 $z$。因为 $z_{\max} = D$，所以 $z$ 的取值个数为 $\min\left(d,i-1\right)-c+1=\min\left(d+1,i\right)-c$。

对于 $x$ 与 $y$，因为和为定值 $i$，所以每一个 $x$ 与 $y$ 是一一对应的。不妨只考虑 $x$ 的取值。因为 $B\le y \le C$，所以 $i-C \le x \le i-B$，又因为 $A \le x \le B$，所以 $x$ 的取值范围为 $\left[\max\left(A,i-C\right),\min\left(B,i-B\right)\right]$。所以 $x$ 与 $y$ 的取值个数为 $\min\left(B,i-B\right)-\max\left(A,i-C\right)$。

最后，根据乘法原理，对于每个 $i$，将 $x、y$ 与 $z$ 的取值个数相乘。根据加法原理，让 $ans$ 加上每个 $i$ 能带来的贡献即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2000+5;
int A,B,C,D,ans;
signed main()
{
	scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
	for(int i=max(A+B,C+1);i<=B+C;i++){
		ans+=(min(D+1,i)-C)*(min(B,i-B)-max(A,i-C)+1);
	}
	printf("%lld\n",ans);
	return 0;
}
//dyyyyds
```

---

## 作者：LlLlCc (赞：4)

之前PanH带打CF时（~~双双掉分~~）推了好久的式子，发现方向都错了，现在想想其实挺水的

------------
考虑枚举$x+y$，对于一个$x+y$，不难发现$z$的取值数为$\max(0,\min(x+y-C,D-C+1))$

所以我们只要知道$x+y$能由多少个$x$和$y$组成就行

这个可以预处理，枚举$x$，容易发现区间$[x+B,x+C]$中的所有数的组成方案都加一了，所以只要差分一下就行

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int A,B,C,D,sum[2000005];
ll ans;
int main(){
	cin>>A>>B>>C>>D;
	for (int i=A;i<=B;i++) sum[i+B]++,sum[i+C+1]--;
	for (int i=0;i<=2000005;i++) sum[i]+=sum[i-1];
	for (int i=A+B;i<=B+C;i++) ans+=(ll)sum[i]*max(0,min(i-C,D-C+1));
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：do_while_true (赞：3)


当 $x+y>z$ 的时候才会有三角形符合条件，所以我们枚举 $a+b$ 的值，然后去算有多少对 $(x,y)$ 满足  $A\leq x\leq B \leq y \leq C$，有多少 $z$ 满足 $C\leq z \leq D$，两者相乘加到答案里即可。

先看 $x+y$ 的枚举范围：因为 $z$ 最小为 $C$ ，则 $x+y$ 最小是 $C+1$，最大我们枚举到 $x$ 的最大值加上 $y$ 的最大值也就是 $B+C$即可。

再看有多少对 $(x,y)$，我们算出 $x$ 的最小取值，然后算出对应的 $y$ 的取值。然后 $x$ 每 $+1$ ，对应的 $y-1$ 即新的一对 $x,y$。 $x$ 最大值为 $B$，$y$ 的最小值也是 $B$ ，我们就能算出 $x$ 能加多少 $1$，$y$ 能减多少 $1$，两个取 $\min$ 就是有多少对 $(x,y)$。

之后有多少 $z$ 满足答案呢？显然满足 $C\leq z\leq\min(x+y,d)$ 的所有 $z$ 都符合条件，上界和下界相减就能得到有多少可能的取值。

两个相乘，加到答案里即可。

[$\mathcal{Code}$](https://codeforces.com/contest/1355/submission/80349213)

---

## 作者：nksunhaolan (赞：2)

可能会很长，只是想讲细一点。

### step1：暴力
枚举 $x$，$y$，$z$ 再判断是否可行。

时间复杂度：$O(n^3)$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	ll A,B,C,D,ans=0;
	cin>>A>>B>>C>>D;
	for(ll x=A;x<=B;x++){
		for(ll y=B;y<=C;y++){
			for(ll z=C;z<=D;z++){
				if(x+y>z)ans++;
			}
		}
	} 
	cout<<ans;
	return 0;
}
```
### step2：优化一层循环
如果我们已经确定了 $x$，$y$。

其实 $z$ 的范围已经确定了（小学的三边边长）。

即：

$\begin{aligned}
 z  <x+y\\
C\le  z \le D
\end{aligned}$

但 $<$ 与 $\le$ 的取等问题导致两式不好合并，不过因为边长为**正整数**，所以一式可化为：$z\le x+y-1$。

合并一下：

$C\le z\le\min(x+y-1,D)$

此时我们设 $z$ 有 $k$ 种取值，结合上式可知：$k=\max(0,\min(x+y-1,D)-C+1)$。

则此时答案为 $\sum_{x=A}^{B}\sum_{y=B}^{C}\max(0,\min(x+y-1,D)-C+1)$。

时间复杂度：$O(n^2)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	ll A,B,C,D,ans=0;
	cin>>A>>B>>C>>D;
	for(ll x=A;x<=B;x++){
		for(ll y=B;y<=C;y++){
			ans+=max(0ll,min(x+y-1,D)-C+1);
		}
	} 
	cout<<ans;
	return 0;
}
```

### step3：AC

**但！** 是：$O(n^2)$ 还是会TLE耶……

回顾一下刚刚的公式：

$\sum_{x=A}^{B}\sum_{y=B}^{C}\max(0,\min(x+y-1,D)-C+1)$

我们发现 $x$，$y$ 在一块耶……

那是不是可以尝试枚举 $x+y$ 来求解呢？（这样时间复杂度就可以来到 $O(n)$ 啦！）。

设 $sum=x+y$（范围通过不等式可以推出：$A+B\le sum \le B+C$）。

则 $k=\max(0,\min(sum-1,D)-C+1)$。

可是此时的 $sum$ 所对应的答案并不是 $k$。

因为 $k$ 只表示了一个 $sum=x+y$ 数对的取值而 $sum=x+y$ 的数对有很多个。

所以此时 $k$ 要乘上一个数，我们把它设为 $d$。

此时答案是 $\sum_{sum=A+B}^{B+C}\max(0,\min(sum-1,D)-C+1) \times d$。

问题来了：$d$ 的取值？

浅浅的分析一下~~

定义：$d$ 表示有多少对 $x$，$y$ 和为 $sum$。

已知：$sum$，$A$，$B$，$C$，$D$。

条件（限制）：$A\le x\le B$，$B\le y\le C$，$ x+y=sum$。

**不妨来解一下不等式吧！**

为方便计算，把 $y$ 消了：$y=sum-x$。

$\begin{cases}
A\le&x&\le B\\
B\le&sum-x& \le C
\end{cases}$

$\begin{cases}
A&\le&x&\le&B\\
B-sum&\le&-x&\le&C-sum
\end{cases}$

$\begin{cases}
A&\le&x&\le&B\\
sum-B&\ge&x&\ge&sum-C
\end{cases}$

$\begin{cases}
A&\le&x&\le&B\\
sum-C&\le&x&\le&sum-B
\end{cases}$

$\max(A,sum-C)\le x\le\max(B,sum-B)$

则此时 $x$ 的可行取值数就是 $d$。

即 $d=\max(0,\min(B,sum-B)-\max(A,sum-C)+1)$。

很好！此时答案为：

$\begin{aligned}
 &\sum_{sum=A+B}^{B+C}\max(0,\min(sum-1,D)-C+1)\times d\\
=&\tiny{\sum_{sum=A+B}^{B+C}\max(0,\min(sum-1,D)-C+1)\times\max(0,\min(B,sum-B)-\max(A,sum-C)+1)}
\end{aligned}$ 

最好再自己推一下，实际上很好想。

时间复杂度：$O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	ll A,B,C,D,ans=0;
	cin>>A>>B>>C>>D;
	for(ll sum=A+B;sum<=B+C;sum++){
		ll k=max(0ll,min(sum-1,D)-C+1);
		ll d=max(0ll,min(sum-B,B)-max(sum-C,A)+1);
		ans+=k*d;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：钓鱼王子 (赞：2)

这道题做法很多，但感觉我的做法还算简单。

这个数据范围肯定是枚举，但枚举哪一个呢？

构成三角形的边满足 $x+y>z$，于是我枚举的是 $x+y$。

枚举之后 $z$ 个数很好求，关键是 $x,y$ 个数，可以通过边界值得出，相减即为个数，具体可以看代码。

记得开 long long。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,ans,a,b,c,d,x,y;
signed main(){
	a=read();b=read();c=read();d=read();
	for(re int i=1;i<=1e6;++i){
		x=i-c;y=i-b;x=max(x,a);y=min(y,b);//x,y边界值
		x=y-x+1;
		if(x<=0)continue;//否则输出负数
		y=min(i-1,d)-c+1;//z边界值
		if(y<=0)continue;//同理
		ans+=x*y;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：feecle6418 (赞：1)

以下默认 $d-c\ge c-b$，若不满足可令 $b+d-c\to c$ 不影响答案。

枚举 $x$，问题转化为有多少个 $b\le y\le c\le z\le d$ 使 $z-y\le x-1$。

- $x\le c-b+1$ 即无论怎么扩展都填不满任意一边，这时满足的 $(y,z)$ 有 $1+2+\dots+x=\dfrac{x(x+1)}{2}$ 对。
- $c-b+1<x\le d-c+1$，此种情况 $y$ 在 $b$ 处 时，$z$ 有 $b+x-c$ 种取值；$y$ 在 $c$ 处时，$z$ 有 $x$ 种取值，且 $y$ 每往右移动一格 $z$ 取值数加一。因此满足的 $(y,z)$ 有 $(b+x-c)+\dots+x=\dfrac{(2x+b-c)(c-b+1)}{2}$ 对。
- $d-c+1<x\le d-b$，此时再分类讨论。
  - $y\le d-x$ 时，同上讨论知 $y$ 从 $b$ 移动至 $d-x+1$ 时 $z$ 取值数成等差数列。此时总答案为 $\dfrac{(d-b-x+2)(d-2c+1+b+x)}{2}$。
  - $y>d-x$，则随便 $z$ 取。总答案为 $(d-c+1)(c-d+x-1)$。
- $x>d-b$，随便取，答案为 $(d-c+1)(c-b+1)$。

分段求和可优化至 $O(1)$。这里提供 $O(b-a)$ 的代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
ll ans=0;
int a,b,c,d;
int main(){
	cin>>a>>b>>c>>d;
	if(c-b>d-c)c=b+(d-c);
	for(int i=a;i<=b;i++){
		int x=c-b,y=d-c;
		if(i<=x+1)ans+=1ll*i*(i+1)/2;
		else if(i<=y+1)ans+=1ll*(c-b+1)*(b+i-c+i)/2;
		else {
			if(i>d-b){
				ans+=1ll*(d-c+1)*(c-b+1);
				continue;
			}
			ans+=1ll*(d-b-i+2)*(d-c+1+b+i-c)/2+1ll*(d-c+1)*(c-d+i-1);
		}
		//cout<<i<<' '<<ans<<endl;
	}
	cout<<ans;
}
```

---

## 作者：rainbow_cat (赞：0)

这道题本质上求 $\sum_{i=a}^{b}\sum_{j=b}^{c}\sum_{k=c}^{d}[i+j > k]$，这个式子可以转化为 $\sum_{i=a}^{b}\sum_{j=b}^{c}\min(\max(a+b-c,0),d-c+1)$，注意到式子只和 $a+b$ 有关，转化为 $\sum_{i=max(a+b,c+1)}^{b+c}\min(\max(i-c,0),d-c+1) \times f(i)$，其中 $f(i)$ 为在 $a \le x \le b\le y \le c$ 的条件下使得 $x+y=i$ 的方案数。   

$f(i)=\min(i-b,b)-\max(i-c,a)+1$，所以我们可以在 $O(n)$ 的复杂度内解决。

---

## 作者：oimaster (赞：0)

## 题面

给定四个数 $A, B, C, D\left(1 \leq A \leq B \leq C \leq D \leq 5 \cdot 10^5\right)$，让你求 $x, y, z$。首先，必须满足 $A \leq x \leq B \leq y \leq C \leq z \leq D$，接下来，还要满足 $x, y, z$ 为三条边，这三条边能组成三角形。求出一共有多少种方法。**本题不是多测。**

## 思路

我们可以枚举 $x, y$ 的和。接下来，我们发现，$x$ 和 $y$ 的方案数为 $\min\left(i-b, b\right)-\max\left(i-c,a\right)+1$。然后我们继续推算。$z$ 的方案数为 $\min\left(d+1, i\right)-c$，意思是在 $d+1-c$（也就是总范围）和 $i-c$ （受 $x, y$ 的和影响的范围）中取小的值，正好就是 $z$ 的方案数。

## 代码

代码就很简单啦~

```c++
#include<iostream>
#define int long long
using namespace std;
signed main(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	int tot=0;
	for(int i=max(c+1,a+b);i<=b+c;++i)
		tot+=(min(d+1,i)-c)*(min(i-b,b)-max(i-c,a)+1);
	cout<<tot<<endl;
}
``



---

