# Beautiful Sequence

## 题目描述

An integer sequence is called beautiful if the difference between any two consecutive numbers is equal to $ 1 $ . More formally, a sequence $ s_1, s_2, \ldots, s_{n} $ is beautiful if $ |s_i - s_{i+1}| = 1 $ for all $ 1 \leq i \leq n - 1 $ .

Trans has $ a $ numbers $ 0 $ , $ b $ numbers $ 1 $ , $ c $ numbers $ 2 $ and $ d $ numbers $ 3 $ . He wants to construct a beautiful sequence using all of these $ a + b + c + d $ numbers.

However, it turns out to be a non-trivial task, and Trans was not able to do it. Could you please help Trans?

## 说明/提示

In the first test, it is easy to see, that the sequence is beautiful because the difference between any two consecutive numbers is equal to $ 1 $ . Also, there are exactly two numbers, equal to $ 0 $ , $ 1 $ , $ 2 $ and exactly one number, equal to $ 3 $ .

It can be proved, that it is impossible to construct beautiful sequences in the second and third tests.

## 样例 #1

### 输入

```
2 2 2 1
```

### 输出

```
YES
0 1 0 1 2 3 2
```

## 样例 #2

### 输入

```
1 2 3 4
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2 2 2 3
```

### 输出

```
NO
```

# 题解

## 作者：_edge_ (赞：6)

楼上 dalao 的特判着实惊到我了。

这里我来说一下某位红名 dalao 的简单想法。

首先，枚举头，然后走到两边就可以，这样进行构造就可以了。

我们把它看成一张图，两个绝对值相差为 $1$ 的有一条边，那么我们要走的即为这样的一个欧拉回路，我们发现，$0$ 和 $3$ 端点处比较麻烦，可以直接走到他们那里，然后 $0$ 和 $1$ 进行交替行走，这样子是比较优的。

正确性证明，还是不太会严格证明，感性理解一下，端点处不能留下来，最好就跟其他端点对拼消耗掉即可。

总时间复杂度 $O(n)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=1e5+5;
int aa[INF],bb[INF],ans[INF],sum,fl;
void solve(int xx) {
	for (int i=0;i<4;i++) bb[i]=aa[i];
	if (!bb[xx]) return ;
	bb[xx]--;ans[1]=xx;
	for (int i=2;i<=sum;i++) {
		if (xx<3 && bb[xx+1]) xx++;
		else if (xx && bb[xx-1]) xx--;
		else return ;
		ans[i]=xx;bb[xx]--;
	}
	cout<<"YES\n";fl=1;
	for (int i=1;i<=sum;i++) cout<<ans[i]<<" ";
	cout<<"\n";
	exit(0);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>aa[0]>>aa[1]>>aa[2]>>aa[3];
	sum+=aa[0]+aa[1]+aa[2]+aa[3];
	solve(0);solve(1);
	solve(2);solve(3);
	if (!fl) cout<<"NO\n";
	return 0;
}
```


---

## 作者：Guess00 (赞：4)

~~这是一个特判题~~

----
先考虑一些特殊情况$:$
> $1.$当$a,b,c,d$中有$3$个为$0,1$个为$1$时$,$输出$\text{YES}$和为$1$的字母所对数字$.$
>
> $2.$当$a=b=0,d=c+1$或$c=d=0,a=b+1$时$.$以$a=b=0,d=c+1$为例$,$易得此时应输出$\text{YES}$和$c$个$43$再加上一个$4.$另一种情况同理$.$
>
> $3.$当不是上述两种情况时$,$若$a>b$或$d>c,$明显不能成立$,$以$0$和$1$为例$,$当有一个$0$时$,$肯定会出现一个$1,$故不能成立$.$

$($以下情况的考虑排除上述三种情况$)$

除上述情况$,$剩下两种情况$,a\leq b<c\geq d$或$a\leq b>c\geq d,$两种情况相仿$,$可只考虑一种$,$另一种同理$.($详见代码$)$

考虑$a\leq b<c\geq d:$
> 若每有一个$0,$则定会出现一个$1.$将$a$个$01$输出$.$
>
> 同理$,$输出$(b-a)$个$12,(c-b+a)$个$23.$
>
> 当$d-c+b-a$为$0,1,-1$时$,$是可以的$($开头$,$结尾的位置会导致最后会有一点误差$),$若不为这三个数$,$就不可以$.$
>
> 最后要调整一下输出顺序$.($详见代码$)$

$\mathbb{CODE:}$
```cpp
#include <bits/stdc++.h>
int i,a,b,c,d,aa,bb,cc,dd;
inline void read(int &x)  //快读
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
signed main(void)
{
	read(a),read(b),read(c),read(d);
	if ((!a) && (!b) && (!c) && d==1)
		return printf("YES\n3"),0;
	if ((!a) && (!b) && (!d) && c==1)
		return printf("YES\n2"),0;
	if ((!a) && (!d) && (!c) && b==1)
		return printf("YES\n1"),0;
	if ((!d) && (!b) && (!c) && a==1)
		return printf("YES\n0"),0;
	if ((!a) && (!b) && d==c+1)
	{
		printf("YES\n");
		for (i=1;i<=c;i++)
			printf("3 2 ");
		return putchar('3'),0;
	}
	if ((!c) && (!d) && a==b+1)
	{
		printf("YES\n");
		for (i=1;i<=b;i++)
			printf("0 1 ");
		return putchar('0'),0;
	}
	if (a>b || d>c)
		return printf("NO"),0;
	//↑对特殊情况的特判↑ 
	aa=a,bb=b,cc=c,dd=d;
	if (b<c)//分别考虑b<c 和 b>=c的情况 
	{
		bb-=aa,cc-=bb,dd-=cc;
		switch (dd)
		{
			//注意输出的顺序 
			case 0:
				printf("YES\n");
				for (i=1;i<=aa;i++)
					printf("0 1 ");
				for (i=1;i<=cc;i++)
					printf("2 3 ");
				for (i=1;i<=bb;i++)
					printf("2 1 ");
				exit(0);
			case 1:
				printf("YES\n");
				if (!bb)
				{
					for (i=1;i<=aa;i++)
						printf("1 0 ");
					printf("1 ");
					for (i=1;i<=cc;i++)
						printf("2 3 ");
					exit(0);
				}
				for (i=1;i<=aa;i++)
					printf("1 0 ");
				for (i=1;i<=bb;i++)
					printf("1 2 ");
				for (i=1;i<=cc;i++)
					printf("3 2 ");
				putchar('3');
				exit(0);
			case -1:
				printf("YES\n");
				for (i=1;i<=aa;i++)
					printf("0 1 ");
				for (i=1;i<=bb;i++)
					printf("2 1 ");
				for (i=1;i<cc;i++)
					printf("2 3 ");
				putchar('2');
				exit(0);
		}
	}
	else
	{
		cc-=dd,bb-=cc,aa-=bb;
		switch (aa)
		{
			case 0:
				printf("YES\n");
				for (i=1;i<=dd;i++)
					printf("3 2 ");
				for (i=1;i<=bb;i++)
					printf("1 0 ");
				for (i=1;i<=cc;i++)
					printf("1 2 ");
				exit(0);
			case 1:
				printf("YES\n");
				if (!cc)
				{
					for (i=1;i<=dd;i++)
						printf("2 3 ");
					printf("2 ");
					for (i=1;i<=bb;i++)
						printf("1 0 ");
					exit(0);
				}
				for (i=1;i<=dd;i++)
					printf("2 3 ");
				for (i=1;i<=cc;i++)
					printf("2 1 ");
				for (i=1;i<=bb;i++)
					printf("0 1 ");
				putchar('0');
				exit(0);
			case -1:
				printf("YES\n");
				for (i=1;i<=dd;i++)
					printf("3 2 ");
				for (i=1;i<=cc;i++)
					printf("1 2 ");
				for (i=1;i<bb;i++)
					printf("1 0 ");
				putchar('1');
				exit(0);
		}
	}
	//若两次dd都不等于0,1,-1,输出NO 
	return printf("NO"),0;
}
```

---

## 作者：yangmuguang (赞：1)

### 题意

你有 $a$ 个 $0$、$b$ 个 $1$、$c$ 个 $2$、$d$ 个 $3$ $(0<a+b+c+d\le10^5)$。你要用它们组成一个“完美”的数列：相邻两个数的差都是 $1$。可以做到吗？

### 思路

枚举用哪个数开始，再顺次在每个位置上放数：假设上一个数是 $x$，要是 $x-1$ 还有数，放 $x-1$；否则要是 $x+1$ 有数，放 $x+1$；否则无解。

至于正确性，可以感性理解，先把最小的 $0$ 通过和 $1$ 对掉解决，因为 $0$ 一定会和 $1$ 对掉，所以先对掉不会更劣。再消掉 $1$ 和 $2$ 就行了。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
ll a[10],sum,b[10],ans[100005]; 
int main()
{
	faster;
	cin>>a[1]>>a[2]>>a[3]>>a[4];
	sum=a[1]+a[2]+a[3]+a[4];
	b[1]=a[1];b[2]=a[2];b[3]=a[3];b[4]=a[4];
	for (ll ty=1;ty<=4;ty++)
	{
		ll x=ty;
		a[1]=b[1];a[2]=b[2];a[3]=b[3];a[4]=b[4];
		if (a[x]==0)continue;
		a[x]--;
		ll i;
		ans[1]=x;
		for (i=2;i<=sum;i++)
		{
			if (a[x-1])
			{
				a[x-1]--;
				x--;
				ans[i]=x;
			}
			else if (a[x+1])
			{
				a[x+1]--;
				x++;
				ans[i]=x;
			}
			else break;
		}
		if (i==sum+1)
		{
			cout<<"YES\n";
			for (ll i=1;i<=sum;i++)
			{
				cout<<ans[i]-1<<" ";
			}
			return 0;
		}
	}
	cout<<"NO";
	return 0;
}
```

---

