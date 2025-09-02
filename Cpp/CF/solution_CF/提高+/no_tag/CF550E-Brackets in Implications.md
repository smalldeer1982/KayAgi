# Brackets in Implications

## 题目描述

蕴含是一个由两个逻辑参数构成的函数。当第一个参数为真而第二个参数为假时，其值为假。

在逻辑表达式中，蕴含运算符使用符号 "$\to$" 表示，参数和结果以 '0'（表示假）和 '1'（表示真）来表示。根据定义，蕴含运算具体如下：

- $0 \to 0 = 1$
- $0 \to 1 = 1$
- $1 \to 0 = 0$
- $1 \to 1 = 1$

在没有括号的逻辑表达式中，多个蕴含运算从左到右依次计算。例如：

$$0 \to 1 \to 0 = (0 \to 1) \to 0 = 1 \to 0 = 0.$$

如果使用括号，先计算括号内的内容。例如：

$$0 \to (1 \to 0) = 0 \to 0 = 1.$$

给定一个逻辑表达式 $a_1 \to a_2 \to \cdots \to a_n$，判断是否能够通过添加括号使表达式的结果为假。如果可以，请给出一种实现该效果的括号添加方式。

## 样例 #1

### 输入

```
4
0 1 1 0
```

### 输出

```
YES
(((0)-&gt;1)-&gt;(1-&gt;0))
```

## 样例 #2

### 输入

```
2
1 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
YES
0
```

# 题解

## 作者：MyukiyoMekya (赞：0)

因为 0 后面接啥都是 1，所以最后肯定是前面 n-1 个数并起来变成 1 然后接上最后的 0 ，最后一位不是 0 那直接 GG

然后用 1 前面接啥都是 1 的特性，我们只要把最后一个 0 前面搞出一个 1 就 ok

考虑几种情况

```plain
... 1 0
```

这种直接按顺序就行了，就是 `x->x->x-> ... ->1->0`

```plain
... 0 .. 0 0
```

这个的意思是 1 前面有一连串的 0 并且 0 的个数大于 1

那么也一样，先把这堆 0 并成 1，然后和上面一样做

就是 `x->x-> ... -> (0->(0->...->(0->0)))->0`

还有一种有点麻烦

```plain
... 1 0 0
```

最后一位前连续 0 的个数为 1，这种情况其实还可以抢救一下

就是找到一连串 1 前面还有没有 0，没有就抢救失败，有的话可以这么搞：

`x->x-> ... -> 0->(1->(1->(1->...->(1->0))))->0`

$\texttt{Code}$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#pragma GCC optimize("Ofast,O3,inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
#define reg register
#define ln puts("")
#define lsp putchar(32)
using namespace std;
const int MaxN=100050;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
int a[MaxN],n;
signed main(void)
{
	read(n);
	reg int cnt=0;
	for(int i=1;i<=n;++i)
		read(a[i]),cnt+=a[i];
	if(n==1)
	{
		puts(cnt?"NO":"YES");
		if(!cnt)
			puts("0");
		return 0;
	}
	if(a[n])
	{
		puts("NO");
		return 0;
	}
	if(!cnt)
	{
		if(n==2)
			return puts("NO"),0;
		puts("YES");
		for(int i=1;i<=n-2;++i)
			printf("(0->");
		putchar('0');
		for(int i=1;i<=n-2;++i)
			putchar(')');
		puts("->0");
		return 0;
	}
	for(int i=n-1;i;--i)
		if(a[i])
		{
			if(n-i==2)
			{
				reg int pos=-1;
				for(int j=i-1;j>0;--j)
					if(!a[j])
					{
						pos=j;
						break;
					}
				if(pos==-1)
					return puts("NO"),0;
				puts("YES");
				for(int j=1;j<pos;++j)
					printf("%d->",a[j]);
				printf("(0->(");
				for(int j=pos+1;j<=n-2;++j)
					printf("1->");
				puts("0))->0");
				return 0;
			}
			puts("YES");
			reg int d=n-i-1;
			for(int j=1;j<=i;++j)
				printf("%d->",a[j]);
			for(int j=1;j<d;++j)
				printf("(0->");
			if(d)
				putchar('0');
			for(int j=1;j<d;++j)
				putchar(')');
			if(d)
				printf("->");
			puts("0");
			return 0;
		}
	return 0;
}
```





---

