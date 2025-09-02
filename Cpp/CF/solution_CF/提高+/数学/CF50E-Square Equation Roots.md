# Square Equation Roots

## 题目描述

A schoolboy Petya studies square equations. The equations that are included in the school curriculum, usually look simple:

 $ x^{2}+2bx+c=0 $  where $ b $ , $ c $ are natural numbers.Petya noticed that some equations have two real roots, some of them have only one root and some equations don't have real roots at all. Moreover it turned out that several different square equations can have a common root.

Petya is interested in how many different real roots have all the equations of the type described above for all the possible pairs of numbers $ b $ and $ c $ such that $ 1<=b<=n $ , $ 1<=c<=m $ . Help Petya find that number.

## 说明/提示

In the second test from the statement the following equations are analysed:

 $ b=1 $ , $ c=1 $ : $ x^{2}+2x+1=0 $ ; The root is $ x=-1 $

 $ b=1 $ , $ c=2 $ : $ x^{2}+2x+2=0 $ ; No roots

 Overall there's one root

In the second test the following equations are analysed:

 $ b=1 $ , $ c=1 $ : $ x^{2}+2x+1=0 $ ; The root is $ x=-1 $

 $ b=1 $ , $ c=2 $ : $ x^{2}+2x+2=0 $ ; No roots

 $ b=1 $ , $ c=3 $ : $ x^{2}+2x+3=0 $ ; No roots

 $ b=2 $ , $ c=1 $ : $ x^{2}+4x+1=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/3991ec922d7c769ae489eea64c57c2bbb41b0c54.png)

 $ b=2 $ , $ c=2 $ : $ x^{2}+4x+2=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/5d07b9483ebb741bb80c778aae623d469ac94a4a.png)

 $ b=2 $ , $ c=3 $ : $ x^{2}+4x+3=0 $ ; The roots are $ x_{1}=-3,x_{2}=-1 $

 $ b=3 $ , $ c=1 $ : $ x^{2}+6x+1=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/30c496d75cf97e85908b57bf3d939afa2185247b.png)

 $ b=3 $ , $ c=2 $ : $ x^{2}+6x+2=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/6c503238cbe1ecf3a5382e37b1c706ca9a71b27d.png)

 $ b=3 $ , $ c=3 $ : $ x^{2}+6x+3=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/7103d2deaa4e6cd061273d09630c96da35ced6a7.png) Overall there are $ 13 $ roots and as the root $ -1 $ is repeated twice, that means there are $ 12 $ different roots.

## 样例 #1

### 输入

```
3 3
```

### 输出

```
12
```

## 样例 #2

### 输入

```
1 2
```

### 输出

```
1
```

# 题解

## 作者：MyukiyoMekya (赞：2)

根据小学数学我们知道 $x=\dfrac {-2b\pm2\sqrt{b^2-c}}{2}$，所以 $x=-b\pm\sqrt{b^2-c}$

显然对于每个 $b$ 有 $1\le c \le \min(m,b^2)$ 的 $c$ 都可以是解的 $c$ ，然后考虑去重根。

我们把 $x$ 分两类讨论，一类是 $x=p+\sqrt q$ ，另一类 $x$ 是整数，

我们发现枚举 $b$ 的时候算到的所有 $p+\sqrt q$ 都不会出现重复，因为 $p$ 是有理数而 $\sqrt q$ 是无理数，必须 $p$ 和 $q$ 都相同才会一样。

所以我们要把 $x$ 是整数的部分进行去重，这时候 $\sqrt {b^2-c}$ 是个整数，设 $b^2-c=k^2$ ，一波不等式操作得出：
$$
\sqrt {\max(0,b^2-m)}\le k \le \sqrt {b^2-1}
$$
所以我们搞个数组把 $-b+k$ 和 $-b-k$ 的位置都加个 $1$ ，然后最后看哪些位置被多算了（大于 $1$ ），那就减掉。

发现就是 $2n$ 次区间加然后一堆单点查，差分就行，复杂度 $\mathcal O(n)$ （假定 sqrt 是 $\mathcal O(1)$ 的）。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ln std::puts("")
#define lsp std::putchar(32)
const int MaxN=1e7+50;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
int b[MaxN<<1|5],*f=b+MaxN;
signed main(void)
{
	int n,m;read(n,m);
	reg int ans=0;
	for(int b=1;b<=n;++b)
	{
		ans+=std::min(b*b,m)*2;
		reg int r=std::sqrt(b*b-1),l=std::ceil(std::sqrt(std::max(0ll,b*b-m)));
		if(l<=r)
			++f[-b+l],--f[-b+r+1],++f[-b-r],--f[-b-l+1];
	}
	for(int i=-MaxN;i<=MaxN;++i)
		f[i]+=f[i-1],f[i]&&(ans-=f[i]-1);
	write(ans),ln;
	return 0;
}
```



---

