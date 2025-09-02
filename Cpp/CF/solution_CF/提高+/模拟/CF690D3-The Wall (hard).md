# The Wall (hard)

## 题目描述

So many wall designs to choose from! Even modulo $ 10^{6}+3 $ , it's an enormous number. Given that recently Heidi acquired an unlimited supply of bricks, her choices are endless! She really needs to do something to narrow them down.

Heidi is quick to come up with criteria for a useful wall:

- In a useful wall, at least one segment is wider than $ W $ bricks. This should give the zombies something to hit their heads against. Or,
- in a useful wall, at least one column is higher than $ H $ bricks. This provides a lookout from which zombies can be spotted at a distance.

This should rule out a fair amount of possibilities, right? Help Heidi compute the number of useless walls that do not confirm to either of these criteria. In other words, a wall is useless if every segment has width at most $ W $ and height at most $ H $ .

Parameter $ C $ , the total width of the wall, has the same meaning as in the easy version. However, note that the number of bricks is now unlimited.

Output the number of useless walls modulo $ 10^{6}+3 $ .

## 说明/提示

If there is no brick in any of the columns, the structure is considered as a useless wall.

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 2 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 2 3
```

### 输出

```
4
```

## 样例 #4

### 输入

```
3 2 2
```

### 输出

```
19
```

## 样例 #5

### 输入

```
5 4 9
```

### 输出

```
40951
```

## 样例 #6

### 输入

```
40 37 65
```

### 输出

```
933869
```

# 题解

## 作者：jianhe (赞：3)

### 思路：
首先考虑暴力 dp。

$dp_{i,j}$ 表示当前考虑第 $i$ 个数，最近的 $0$ 到 $i$ 的距离为 $j$ 的方案数。

填 $0$ 的情况：$dp_{i,0}=\sum\limits_{j=0}^{w} dp_{i-1,j}$。

填其他数的情况：$dp_{i,j}=dp_{i-1,j-1} \times h$。

直接转移是 $O(c \times w)$ 的，考虑优化。

对于 $(i,j)$ 而言，会给 $(i+1,0)$ 带来 $dp_{i,j}$ 的贡献，给 $(i+1,j+1)$ 带来 $dp_{i,j} \times h$ 的贡献。

于是可以矩阵快速幂优化，每次乘下面这个矩阵即可。

$$
\begin{bmatrix}
	1 & H & 0 & 0 & \dots & 0 \\
	1 & 0 & H & 0 & \dots & 0 \\
	1 & 0 & 0 & H & \dots & 0 \\
  \dots & \dots & \dots & \dots & \dots & \dots \\
  1 & 0 & 0 & 0 & \dots & H \\
  1 & 0 & 0 & 0 & \dots & 0
\end{bmatrix}
$$
### 代码：
```cpp
/*
 * @Author: jianhe
 * @Date: 2025-03-04 14:30:06
 * @LastEditTime: 2025-03-04 14:35:31
 */
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=111,mod=1e6+3;
ll c,w,h,res;
struct Mat{
    ll a[N][N]={};
    ll* operator[](ll x){return a[x];}
    Mat operator*(Mat b){
        Mat c;
        for(int i=0;i<=w;i++)
            for(int j=0;j<=w;j++)
                for(int k=0;k<=w;k++)
                    (c[i][j]+=a[i][k]*b[k][j])%=mod;
        return c;
    }
}ans,a;
void qp(ll b){while(b){if(b&1) ans=ans*a;a=a*a,b>>=1;}}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>c>>w>>h;ans[0][0]=1;
    for(int i=0;i<=w;i++) a[i][0]=1,a[i][i+1]=h;
    qp(c);
    for(int i=0;i<=w;i++) (res+=ans[0][i])%=mod;cout<<res;
    return 0;
}
```

---

## 作者：thostever (赞：3)

## 题意：

给定 $C$,$W$ 和 $H$，问有多少个长度为 $C$ 的序列 $a$ 满足以下条件：
1. $0\leq a_i\leq H$
2. 所有不包含 $0$ 的子串的长度都不超过 $W$

## 题解：

我们先考虑最朴素的 dp：令 $dp_{i,j}$ 表示前 $i$ 个位置，$a_{i-j}=0$ 且 $a_{i-j+1}$ 到 $a_i$ 不为 $0$ 时的方案数。（即最后 $j$ 个位置不为 $0$）

显然，有转移：

$$
\left\{\begin{matrix}
 dp_{i,j}=dp_{i-1,j-1}\times H & (1\leq j\leq W)\\
 dp_{i,0}=\sum_{k=0}^W dp_{i-1,k}
\end{matrix}\right.
$$

初始值 $dp_{0,0}=1$，答案为 $\sum_{j=0}^W dp_{C,j}$

我们再回去看一下范围：$1\leq C\leq 10^8$

噢~~~~~~

恍然大悟

直接考虑矩阵乘法：

$$
\begin{Bmatrix}
 dp_{i,0} & dp_{i,1} & dp_{i,2} & dp_{i,3} & ... & dp_{i,W} 
\end{Bmatrix}
$$

$$
\times 
\begin{Bmatrix}
 1 & H & 0 & 0 & ... & 0 \\
 1 & 0 & H & 0 & ... & 0 \\
 1 & 0 & 0 & H & ... & 0 \\
 1 & 0 & 0 & 0 & ... & 0 \\
 ... & ... & ... & ... & ... & ... \\
 1 & 0 & 0 & 0 & ... & H \\
 1 & 0 & 0 & 0 & ... & 0 \\

\end{Bmatrix}
$$

$$
=
\begin{Bmatrix}
dp_{i+1,0} & dp_{i+1,1} & dp_{i+1,2} & dp_{i+1,3} & ... & dp_{i+1,W} 
\end{Bmatrix}
$$

要注意：由于我们矩阵是 $W+1$ 维的，所以我们相乘的时候下标要从 $0$ 开始。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e6+3;
int C,W,H;
struct ma
{
	int a[110][110];
}A,I;
ma operator *(const ma x,const ma y)
{
	ma z;
	for(int i=0;i<=W;i++) for(int j=0;j<=W;j++) z.a[i][j]=0;
	for(int i=0;i<=W;i++) for(int j=0;j<=W;j++) for(int k=0;k<=W;k++) z.a[i][j]+=x.a[i][k]*y.a[k][j],z.a[i][j]%=mod;
	return z;
}
signed main()
{
	cin>>C>>W>>H;
	I.a[0][0]=1;
	for(int i=0;i<=W;i++) A.a[i][0]=1;
	for(int i=1;i<=W;i++) A.a[i-1][i]=H;
	while(C)
	{
		if(C&1) I=I*A;
		A=A*A;
		C>>=1;
	}
	int ans=0;
	for(int j=0;j<=W;j++) ans+=I.a[0][j],ans%=mod;
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：small_john (赞：0)

## 思路

神仙题。

首先容易想到 DP，设 $f_{i,j}$ 表示前 $i$ 位，上一个 $0$ 在第 $i-j$ 的位置上，有转移：

$$
\displaystyle
\begin{cases}
f_{i,j}=f_{i-1,j-1}\times H & (1\le j\le W)\\
f_{i,0}=\sum_{j=0}^{W}f_{i-1,j}
\end{cases}
$$

暴力做的时间复杂度是 $O(nW)$ 的，很明显做不了。但发现 $1\le W\le 100$，上矩乘！

设矩阵 $A_i=\begin{bmatrix} f_{i,0}&f_{i,1}&\cdots&f_{i,W}\end{bmatrix}$，则 $A_0=\begin{bmatrix} 1&0&\cdots & 0\end{bmatrix}$。我们需要构造一个转移矩阵 $B$ 满足 $A_i\times B=A_{i+1}$。

对于第二条转移，$B$ 的第 $0$ 列全部为 $1$。对于第一条转移，需要满足 $B_{i-1,i}=H$（其中 $1\le i\le W$）。所以构造出来的矩阵长这样：

$$
\begin{bmatrix}
1 & H & 0 & \cdots &0 \\
1 & 0 & H & \cdots &0\\
\vdots &\vdots &\vdots &\ddots&\vdots\\
1 & 0 & \cdots & 0 & H \\
1 & 0 & 0 & \cdots & 0 
\end{bmatrix}
$$

最后输出 $A_0\times B^n$ 的各项之和即可。注意下标要从 $0$ 开始。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 105,mod = 1e6+3;
int n,h,w;
struct node{
	int a[N][N];
	inline void init(int x = 0)
	{
		for(int i = 0;i<N;i++)
			for(int j = 0;j<N;j++)
				a[i][j] = x; 
	}
	inline friend node operator * (node x,node y)
	{
		node res;res.init();
		for(int i = 0;i<=w;i++)
			for(int j = 0;j<=w;j++)
				for(int k = 0;k<=w;k++)
					(res.a[i][j]+=1ll*x.a[i][k]*y.a[k][j]%mod)%=mod;
		return res;
	}
}f,base;
inline node qpow(node x,int y)
{
	node res = x;y--;
	while(y)
	{
		if(y&1) res = res*x;
		y>>=1;
		x = x*x; 
	}
	return res;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(w),read(h);
	f.init(),base.init();
	for(int i = 1;i<=w;i++)
		base.a[i-1][i] = h;
	for(int i = 0;i<=w;i++)
		base.a[i][0] = 1;
	base = qpow(base,n);
	f.a[0][0] = 1;
	f = f*base;
	int ans = 0;
	for(int i = 0;i<=w;i++)
		ans = (ans+f.a[0][i])%mod;
	write(ans);
	return 0;
}
```

$\KaTeX$ 肝爆的一集，求管理员大大给过！

---

