# Harmony Analysis

## 题目描述

The semester is already ending, so Danil made an effort and decided to visit a lesson on harmony analysis to know how does the professor look like, at least. Danil was very bored on this lesson until the teacher gave the group a simple task: find $ 4 $ vectors in $ 4 $ -dimensional space, such that every coordinate of every vector is $ 1 $ or $ -1 $ and any two vectors are orthogonal. Just as a reminder, two vectors in $ n $ -dimensional space are considered to be orthogonal if and only if their scalar product is equal to zero, that is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF610C/1ed68100811c8d9a7f92461867e21d565afe33d0.png).Danil quickly managed to come up with the solution for this problem and the teacher noticed that the problem can be solved in a more general case for $ 2^{k} $ vectors in $ 2^{k} $ -dimensinoal space. When Danil came home, he quickly came up with the solution for this problem. Can you cope with it?

## 说明/提示

Consider all scalar products in example:

- Vectors $ 1 $ and $ 2 $ : $ (+1)·(+1)+(+1)·(-1)+(-1)·(+1)+(-1)·(-1)=0 $
- Vectors $ 1 $ and $ 3 $ : $ (+1)·(+1)+(+1)·(+1)+(-1)·(+1)+(-1)·(+1)=0 $
- Vectors $ 1 $ and $ 4 $ : $ (+1)·(+1)+(+1)·(-1)+(-1)·(-1)+(-1)·(+1)=0 $
- Vectors $ 2 $ and $ 3 $ : $ (+1)·(+1)+(-1)·(+1)+(+1)·(+1)+(-1)·(+1)=0 $
- Vectors $ 2 $ and $ 4 $ : $ (+1)·(+1)+(-1)·(-1)+(+1)·(-1)+(-1)·(+1)=0 $
- Vectors $ 3 $ and $ 4 $ : $ (+1)·(+1)+(+1)·(-1)+(+1)·(-1)+(+1)·(+1)=0 $

## 样例 #1

### 输入

```
2
```

### 输出

```
++**
+*+*
++++
+**+```

# 题解

## 作者：Karry5307 (赞：3)

### 题意

给定 $n$，求 $2^n$ 个 $2^n$ 维向量满足每个向量的坐标表示中任意一维都为 $1$ 或 $-1$，且这些向量两两点积为 $0$。

数据范围：$0\leq k\leq 9$。

### 题解

把毒瘤题调完之后写写简单构造。

通过对样例输出的重排发现答案应该是一个类似于这样的分形图形：

```plain
++++
+*+*
++**
+**+
```

直接构造即可，现在来说明这个东西的正确性，考虑数学归纳法。

当 $n=1$ 时显然成立，当 $n\neq 1$ 时，假设选出的向量为第 $i$ 个和第 $j$ 个，其中 $i<j$。

如果 $i,j\leq 2^{n-1}$，则对于前 $2^{n-1}$ 维和后 $2^{n-1}$ 维来说贡献均为 $0$。$i,j>2^{n-1}$ 时同理。

现在考虑 $i\leq 2^{n-1},j>2^{n-1}$ 时的情况。考虑一个 $k=j-2^{n-1}$，这个时候第 $j$ 个向量与第 $k$ 个向量前 $2^{n-1}$ 维度符号相同，后 $2^{n-1}$ 维符号相反。

注意到 $i,k\leq 2^{n-1}$，所以第 $i$ 个向量与第 $k$ 个向量的前 $2^{n-1}$ 维和后 $2^{n-1}$ 维来说贡献均为 $0$。又由于第 $j$ 个向量与第 $k$ 个向量前 $2^{n-1}$ 维相同，贡献为 $0$，并且后 $2^{n-1}$ 维相反，贡献也为 $0$，所以第 $i$ 个向量与第 $j$ 个向量的点积也为 $0$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n;
char ch[1024][1024];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void calc(ll l,ll r,ll u,ll d,ll sgn)
{
	if(l==r)
	{
		return (void)(ch[l][u]="+*"[sgn]);
	}
	ll mid=(l+r)>>1,mid2=(u+d)>>1;
	calc(l,mid,u,mid2,sgn),calc(l,mid,mid2+1,d,sgn);
	calc(mid+1,r,u,mid2,sgn),calc(mid+1,r,mid2+1,d,sgn^1);
}
int main()
{
	n=read(),calc(1,1<<n,1,1<<n,0);
	for(register int i=1;i<=(1<<n);i++)
	{
		printf("%s\n",ch[i]+1);
	}
}
```

---

## 作者：泠小毒 (赞：1)

# Harmony Analysis
已知向量中每个坐标的值都为1或者-1

给出k(0<=k<=9)，构造出2^k个2^k维向量，使得任意这2^k个向量中任意两个向量点积为0
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190513/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190513.html)
## 解法
首先手推一下k为3时是什么样的
```cpp
++++++++
++++****
++**++**
++****++
+*+*+*+*
+*+**+*+
+**++**+
+**+*++*
```
嗯，是这个样子的，对比一下k为2时的
```cpp
++++
++**
+*+*
+**+
```
可以发现将k为2时的扩大一倍会形成前4行，后4行是怎么来的呢，前四行偶数位都取反(异或1)

~~别问我怎么看出来的，就这样看出来的QAQ~~

按照这样构造就可以了QWQ
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m=1,a[512][512];
int main()
{
	a[0][0]=1,scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)for(int k=m*2-1;k>=0;k--)a[j][k]=a[j][k/2];
		for(int j=m;j<m*2;j++)for(int k=0;k<m*2;k++)a[j][k]=a[j-m][k];
		for(int j=m;j<m*2;j++)for(int k=1;k<m*2;k+=2)a[j][k]^=1;
		m*=2;
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)if(a[i][j]==1)putchar('+');else putchar('*');
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## [CF610C Harmony Analysis](https://codeforces.com/problemset/problem/610/C)

## 思路

提供一种不同的构造方法，这里以 $k=4$ 举例。

下面将 `*` 表示成 `0`，`+` 表示成 `1`，则一个向量可以表示为一个二进制数，向量相乘即为两数异或和。

因为向量积为 $0$，显然得到的答案中一半为 `0`，一半为 `1`，于是先构造出一个一半为 `0`，一半为 `1` 的数：

```txt
0000000011111111
```

对于每次操作，我们把它的一半 `0` 与一半 `1` 交换位置，直到不能交换：

```txt
0000000011111111
0000111100001111
0011001100110011
0101010101010101
```

将该表旋转 $90°$，则可以发现该表即为 $0\sim 2^k-1$ 的十进制数的二进制表示。

```txt
0000
0001
0010
0011
0100
0101
...
```

容易证明每个数的 `0` 与 `1` 的数量仍然相等，且**若干数的异或和仍然满足该性质**。


根据该性质，我们给每个数一个二进制编号：

```txt
(0001)   0000000011111111
(0010)   0000111100001111
(0100)   0011001100110011
(1000)   0101010101010101
```

则 $0\sim 2^k-1$ 的每个数都可以表示为该表若干个数的异或和，于是可以计算出该表，再通过枚举每个数的编号求异或和得出答案。

可以发现这种方法得到的答案跟构造类似 $\begin{bmatrix}
A & A\\
A & -A
\end{bmatrix}$ 的矩阵得出的答案是一样的。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
bitset<512> d[15];
signed main() {
	cin>>k;
	for(int s=0;s<(1<<k);s++)
		for(int i=0;i<k;i++)
			if(s&(1<<i)) d[i][s]=true;
	for(int s=0;s<(1<<k);s++){
		bitset<512> res;
		for(int i=0;i<k;i++)
			if(s&(1<<i)) res^=d[i];
		for(int i=0;i<(1<<k);i++)
			cout<<(res[i]?'*':'+');
		cout<<endl;
	}
	return 0; 
}
```

---

## 作者：lkjzyd20 (赞：0)

前言：~~题目翻译的依托够使~~

### 思路

先手搓一下 $k=1$ 的情况
```
++
+*
```
继续 $k=2$ 就是样例，我们可以发现还可以构造成这样
```
++++
+*+*
++**
+**+
```
当 $k=3$ 时，手搓出来：

```
++++++++
+*+*+*+*
++**++**
+**++**+
++++****
+*+**+*+
++****++
+**+*++*
```
根据人类~~智慧~~思考，可以简单发现，这个矩阵可以变成：
$$
\begin{bmatrix}
 a & a\\
 a & -a
\end{bmatrix}
$$

于是这题只需要简单的模拟即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
int n;
char a[2000][2000];
main(){
    cin>>n;
    a[1][1]=0;
    rep(i,1,n)
    {
        int k=1<<(i-1);
        rep(i,1,k)rep(j,k+1,2*k)a[i][j]=a[i][j-k];
        rep(i,k+1,2*k)rep(j,1,k)a[i][j]=a[i-k][j];
        rep(i,k+1,2*k)rep(j,k+1,2*k)a[i][j]=a[i-k][j-k]^1;
    }
    rep(i,1,1<<n)
    {
        rep(j,1,1<<n)cout<<(!a[i][j]?'+':'*');
        cout<<'\n';
    }
}

```

---

## 作者：snowstorm1939 (赞：0)

### CF610C Harmony Analysis

在另一篇题解中构造了这样一种矩阵：

```
k=2:
++++
+*+*
++**
+**+
```

这种矩阵有一个名字：Hadamard 矩阵。

简单来说，Hadamard 矩阵里的元素为 $1$ 或 $-1$，这意味着，在一个 Hadamard 矩阵的每一对行列表示两个相互垂直的向量。

看回题意：

> 给定 $k$，求 $2^k$ 个 $2^k$ 维向量满足每个向量的坐标表示中任意一维都为 $1$ 或 $−1$，且这些向量两两点积为 $0$。$(0 \leq k \leq 9)$

~~这不巧了。~~

在此题中，我们只需要会构造这个矩阵，想了解更多的大佬，可以看[维基](https://en.wikipedia.org/wiki/Hadamard_matrix)。

设 $H$ 为一个 $n$ 阶（阶数仅能为 $1$、$2$ 或 $4$ 的倍数）矩阵,那么阶为 $2n$ 的矩阵为：

$\begin{bmatrix}H&H\\H&-H\end{bmatrix}$

于是，在你知道这个矩阵的存在后，你只需用简单的循环便能AC此题：

```c++
#include<bits/stdc++.h>
#define itn int
#define re register
#define il inline
#define ll long long
#define ull unsigned long long
using namespace std;
il int read()
{
	int sum=0,sign=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')sign=-1;ch=getchar();}
	while(isdigit(ch)){sum=sum*10+ch-'0';ch=getchar();}
	return sum*sign;
}
char a[550][550];
int n,x;
int main()
{
	n=read();
	a[1][1]='+';
	for(int i=0;i<n;i++)
	{
		x=pow(2,i);
		for(int i=x+1;i<=x+x;i++)
		for(int j=1;j<=x;j++)
		a[i][j]=a[i-x][j];
		for(int i=1;i<=x;i++)
		for(int j=x+1;j<=x+x;j++)
		a[i][j]=a[i][j-x];
		for(int i=x+1;i<=x+x;i++)
		for(int j=x+1;j<=x+x;j++)
		if(a[i-x][j-x]=='+')a[i][j]='*';
		else a[i][j]='+';
	}
	for(itn i=1;i<=pow(2,n);i++)
	{
		for(itn j=1;j<=pow(2,n);j++)
		cout<<a[i][j];
		cout<<'\n';
	}
	return 0;
}
```



---

