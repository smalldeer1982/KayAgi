# Median Smoothing

## 题目描述

最简单的中值滤波是对一个序列 $a_1,a_2,…,a_n$ ，转换为一个新的序列 $b_1,b_2,…,b_n$ ，规则如下：

- $b_1=a_1,b_n=a_n$ ，即第一个和最后一个元素不变。
- $b_i(1<i<n)$ 为 $a_{i-1},a_i,a_{i+1}$ 的中位数。

求对于一个 01 序列 $a$ ，它经过几次操作会变成“稳定的”，或者永远稳定不了。

## 说明/提示

### 样例解释
经过两次操作：$01010\longrightarrow00100\longrightarrow00000$ ，$00000$ 显然是稳定的序列。

## 样例 #1

### 输入

```
4
0 0 1 1
```

### 输出

```
0
0 0 1 1
```

## 样例 #2

### 输入

```
5
0 1 0 1 0
```

### 输出

```
2
0 0 0 0 0
```

# 题解

## 作者：PanH (赞：6)

这种题多手玩一下还是可以玩出一点性质的：

像这种 $101$ ， $010$ 中间与两边不同的子串出现的时候就可以发现它一定是会变的。

那我们统计什么，上面这种情况的出现次数？

实际上，我们可以找到最长的“ $1,0$ 交错”的子串长度。将它长度 $-1$ 再除以 $2$ ，就可以得到答案了。

那么题目还要求出最终状态，找几个例子来：

1.  $0101010 \rightarrow 0000000$

2.  $1101010 \rightarrow 1111000$

3.  $1101011 \rightarrow 1111111$

1 串的“ $1,0$ 交错”的子串是$[1,7]$，2 串的“ $1,0$ 交错”的子串是$[2,7]$ ，3 串的“ $1,0$ 交错”的子串是$[2,6]$ 。

总结一下，只要把“ $1,0$ 交错”的子串左边一半变成 $a[l]$ ，右边一半变成 $a[r]$ ，就没了。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,a[N],b[N],ans,l[N],r[N],tot;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)	read(a[i]);
	for(int i=1;i<=n;i++)
	{
		int res=0;
		l[++tot]=i;
		while(a[i+1]^a[i]==1&&i+1<=n)	i++,res++;
		r[tot]=i,ans=max(ans,(res>>1));
	}
	printf("%d\n",ans);
	for(int i=1;i<=tot;i++)
	{
		int mid=l[i]+r[i]>>1;
		for(int j=l[i];j<=mid;j++)		printf("%d ",a[l[i]]);
		for(int j=mid+1;j<=r[i];j++)	printf("%d ",a[r[i]]);
	}
	return 0;
}
```


---

## 作者：TruchyR (赞：1)

我们几次操作后说一个位置 $i$ 是固定的，当且仅当这个位置在接下来的操作不会变化。  

考虑位置 $i$ 什么时候是固定的。  

- $i=1$ 或 $i=n$，显然这两个位置不会变。
- 当前 $a_i=a_{i-1}$ 或 $a_i=a_{i+1}$，当然前提是 $1<i<n$。

对于第二种情况，一次操作的时候取中位数的三个数至少有两个等于 $a_i$，所以中位数还是 $a_i$。同理旁边相等的那个数也不会变，所以位置 $i$ 是固定的。  

综上，我们可以只考虑 01 相间的部分。  

现在假设 $[l,r]$ 这个部分是 01 相间的且都不是固定的。  

手推可得一次操作后 $[l,r]$ 中的数都会翻转，由于操作前有 $a_l\ne a_{l-1}$ 和 $a_r\ne a_{r+1}$，所以操作后就会有 $a_l=a_{l-1}$ 和 $a_r=a_{r+1}$，所以位置 $l$ 和 $r$ 会变为固定的。  

所以每次操作后，每个不固定的区间 $[l,r]$ 都会变成 $[l+1,r-1]$，直到消失。  

手动模拟这个过程即可，操作次数就是需要操作最多次的区间。    

[提交记录](https://codeforces.com/contest/590/submission/275174671)，但是没有注释。

---

## 作者：Gao_yc (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF590A)

~~这道题怎么评紫的，蓝都嫌多（~~


首先我们可以发现，对于 $a_i$ ，在一次操作后变化当且仅当 $a_{i-1}\ne a_i$，$a_{i+1}\ne a_i$；而一段连续的 1 或 0 自始至终都不会发生变化。

因此，只有连续的一段 01 相间的序列才可能变化多次。

而我们再进行多次模拟可以发现，一段长度为 $k$ 的 01 相间的序列，在经过 $\lfloor \frac{k-1}{2} \rfloor$ 次操作后，便不再变化。而最终确定的序列则是左右各分一半，数值由边界的数决定。

于是在整个序列中拆出多个 01 相间的序列进行处理，以每个 01 相间的子序列的操作数取最大值即为最终答案。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,a[N],la,ans,d[N];
int main()
{
//	freopen("","r",stdin);
//	freopen("","w",stdout);
	scanf("%d",&n);
	int len;
	for(int i=1;i<=n;++i) scanf("%d",a+i),d[i]=a[i];
	for(int i=1;i<=n;++i)
	{
		if((i==n||!(a[i+1]^a[i]))&&la) 
		{
			len=i-la+1;
			ans=max(ans,(len-1)/2);
			for(int j=la;j<la+(len/2);++j) d[j]=a[la];
			for(int j=la+(len/2);j<=i;++j) d[j]=a[i];
			la=0;
		}
		else if(a[i+1]^a[i]&&!la) la=i;
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;++i) printf("%d ",d[i]);
    return 0;
}

```


---

## 作者：FutaRimeWoawaSete (赞：1)

考试时的一道原题，其实还是不难。    

不知道为什么自己写的这么长，可能想得有点复杂。  

首先在考场上就想这么一个问题：可否进行 $O(n * ans)$ 的算法进行暴力模拟。    

手玩了一组，发现 $ans$ 可以很大，所以卡一个 $O(n ^ 2)$ 不成问题，放弃暴力模拟。    

这时再仔细~~手玩~~发现一个很重要的性质：如果相邻有多个数是一个数，那么这么多个数都不会变了。    

这点从原题就可以很简单地得知，

两个数都是 $0$ 那么该位生成的数就是 $0$ ，如果两个数都是 $1$ 那么该位生成的数就是 $1$。  

于是我们可以先将连续的的数字隔开分块，如果相邻两个数不一样就要划开分块，这里需要特判开头结尾是因为开头块结尾块自己就相当于是不变的数字，不需要依赖别的数字。

一定要记住特判开头结尾(考场上因为这个还差点打挂了)。 

为了方便说明，我们把块内数字固定的块称为具有性质 $A$ ，否则成为具有性质 $B$ 。   
接着我们又发现两个性质：
```
两两具有性质A的块之间夹杂的一定都是一些具有性质B的块或者不夹杂任何块。    
每经过一次操作后，两两具有性质A的块就向中间扩散一个单位，
因为具有性质B的块都是单一元素，
所以这里可以理解一个单位就相对于原数列中的一个单位。    
```
于是我们就直接暴力扫一遍求两两 $A$ 块之间至多需要多少次才能扩散完，然后再暴力模拟一遍生成的过程即可。    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 1e6 + 5;
int a[Len],n,belong[Len],Whi[Len],cnt,flag[Len],to[Len],ans;//原数列，这个块里有多少个元素，这个块里的元素都是什么，块的个数，这个块带有性质A还是性质B，这个A块的下一个A块的下标 
int main()
{
	//freopen("darkside.in","r",stdin);
	//freopen("darkside.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	if(n <= 2) 
	{
		printf("0\n");
		for(int i = 1 ; i <= n ; i ++) printf("%d ",a[i]);
		return 0;
	}
	belong[1] = 1;
	Whi[1] = a[1];
	cnt = 1;
	for(int i = 2 ; i < n ; i ++)
	{
		if(a[i] != a[i - 1])
		{
			cnt ++;
			belong[cnt] ++;
			Whi[cnt] = a[i];
		}
		else belong[cnt] ++;
	}
	if(a[n] == a[n - 1]) belong[cnt] ++;
	else 
	{
		cnt ++;
		belong[cnt] ++;
		Whi[cnt] = a[n];
	}//以上请结合数组定义 
	flag[1] = flag[cnt] = 1;//1就表示带A性质，0就表示B性质 
	for(int i = 2 ; i < cnt ; i ++)
	{
		if(belong[i] == 1) flag[i] = 0;
		else flag[i] = 1;//标记是具有A性质还是B性质 
	}
	int lasti = 1;//上一个A块 
	for(int i = 2 ; i <= cnt ; i ++)
	{
		if(flag[i]) 
		{
			to[lasti] = i;
			int num = i - lasti - 1;
			if(num % 2 == 1) ans = max(ans , num / 2 + 1);//因为两个块都要扩散，所以直接用两两之间的块的长度除以2向上取整 
			else ans = max(ans , num / 2);
			lasti = i;
		}
	}
	to[cnt] = cnt + 1;//特判，不然下面就直接死循环了 
	printf("%d\n",ans);
	int i = 1;
	while(i <= cnt)
	{
		int To = to[i] , num = To - i - 1;
		for(int j = 1 ; j <= belong[i] ; j ++) printf("%d ",Whi[i]);//展开 
		if(num % 2 == 1) for(int j = 1 ; j <= num ; j ++) printf("%d ",Whi[i]);//如果相距奇数个单位的话说明两个块都是一个元素，因为两两块之间的元素是相异的 
		else
		{
			for(int j = 1 ; j <= num / 2 ; j ++) printf("%d ",Whi[i]);
			for(int j = 1 ; j <= num / 2 ; j ++) printf("%d ",Whi[To]);
		}
		i = To;
	}
	return 0;
}
```

---

## 作者：Transparent (赞：1)

### 找规律

------------

#### 分析：
- 像 111111 这样连续的 1 是稳定的；

- 像 000000 这样连续的 0 也是稳定的；

- 因为是求 $3$ 个数的中位数，所以连续的 $2$ 个连续的 0 或 1 相互影响，它们可以构成一个稳定的子串；

- 无论进行多少次操作稳定的子串都不会改变；

- 因此只有 0 和 1 交替出现时才会使原串不稳定。

------------


#### 规律：
- 0 和 1 交替出现的子串有两种情况：长度为奇数和长度为偶数；

- 对于长度为奇数的串 1010101 （长度为 $7$ ）进行操作：
  
> 1. 1010101 → 1101011
> 2. 1101011 → 1110111
> 3. 1110111 → 1111111

- $3$ 次操作后稳定。

- 对于长度为奇数的串 010101010 （长度为 $9$ ）进行操作：

> 1. 010101010 → 001010100
> 2. 001010100 → 000101000
> 3. 000101000 → 000010000
> 4. 000010000 → 000000000

- $4$ 次操作后稳定。

- 综上可以得出，一个长度（设为 $len$ ）为奇数的串，在进行 $\lfloor len \div 2 \rfloor $ 次操作后可以稳定（其中 $\lfloor x \rfloor$ 表示对 $x$ 向下取整）。稳定后的串的每一位都与原串起始位置或结束位置（0 和 1 交替奇数构成的串首尾相等）相等。

- 对于长度为偶数的串 101010 （长度为 $6$ ）进行操作：

> 1. 101010 → 110100
> 2. 110100 → 111000

- $2$ 次操作后稳定。

- 对于长度为偶数的串 01010101 （长度为 $8$ ）进行操作：

> 1. 01010101 → 00101011
> 2. 00101011 → 00010111
> 3. 00010111 → 00001111

- $3$ 次操作后稳定

- 综上可以得出，一个长度（设为 $len$ ）为偶数的串，在进行 $len \div 2 -1$ 次操作后可以稳定。稳定后的串的前半部分的每一位都与原串起始位置相等，后半部分的每一位都与原串结束位置相等。即设起始位置下标为 $x$ ，结束位置下标为 $y$ ，则 $b_x$ 至 $b_{(x+y)\div 2}$ 中每一位都等于 $a_1$ ， $b_{(x+y)\div 2 + 1}$ 至 $b_y$ 中每一位都等于 $a_y$ 。

- 对于所有的串，都可以将它进行分组，分为稳定部分和 0 和 1 交替出现的不稳定部分。

- 如 001010000101110101101010 可以分组为 0 01010 00 0101 1 10101 101010 ，然后在对每一组分别统计长度，计算次数并记录结果。最终让它稳定下来需要的操作次数就等于所有组的操作次数中最大的一个。

- 而对于所有的串都可以进行如此的分组，所以所有的串都可以在若干次操作后稳定

------------

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tmp,Ans;
bool a[500001],ans[500001];
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		ans[i]=a[i]=tmp==0?0:1;
	}
	for(register int i=2;i<=n;i++)
	{
		if(a[i]^a[i-1])//相同出0，相异出1 
		{
			int len=1,bg=i-1;
			while(a[i]^a[i-1]&&i<=n)
			{
				len++;
				i++;
			}
			i--;//在最后一次while时，下一位已经不符合条件，所以i被多加了1
			if(len&1)//即len为奇数 
			{
				for(register int j=bg;j<=i;j++)
				{
					ans[j]=a[bg];
				}
				Ans=max(Ans,len/2);//统计答案 
			}
			else
			{
				for(register int j=bg;j<=(bg+i)/2;j++)
				{
					ans[j]=a[bg];
				}
				for(register int j=(bg+i)/2+1;j<=i;j++)//注意j的初始值要加1 
				{
					ans[j]=a[i];
				}
				Ans=max(Ans,len/2-1);//统计答案 
			}
		}
	}
	printf("%d\n",Ans);
	for(register int i=1;i<=n;i++)
	{
		printf("%d ",ans[i]?1:0); 
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```


---

