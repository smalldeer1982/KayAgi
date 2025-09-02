# Balls Game

## 题目描述

Iahub is training for the IOI. What is a better way to train than playing a Zuma-like game?

There are $ n $ balls put in a row. Each ball is colored in one of $ k $ colors. Initially the row doesn't contain three or more contiguous balls with the same color. Iahub has a single ball of color $ x $ . He can insert his ball at any position in the row (probably, between two other balls). If at any moment there are three or more contiguous balls of the same color in the row, they are destroyed immediately. This rule is applied multiple times, until there are no more sets of 3 or more contiguous balls of the same color.

For example, if Iahub has the row of balls \[black, black, white, white, black, black\] and a white ball, he can insert the ball between two white balls. Thus three white balls are destroyed, and then four black balls become contiguous, so all four balls are destroyed. The row will not contain any ball in the end, so Iahub can destroy all 6 balls.

Iahub wants to destroy as many balls as possible. You are given the description of the row of balls, and the color of Iahub's ball. Help Iahub train for the IOI by telling him the maximum number of balls from the row he can destroy.

## 样例 #1

### 输入

```
6 2 2
1 1 2 2 1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
1 1 1
1
```

### 输出

```
0
```

# 题解

## 作者：vanueber (赞：2)

[原题传送门-Luogu](https://www.luogu.com.cn/problem/CF430B)

[原题传送门-CF](https://codeforces.com/problemset/problem/430/B)

[前置芝士-一点模拟](https://oi-wiki.org/basic/simulate/)

建议先了解祖玛游戏规则。

# 题目大意

给定 $n$ 个数，在其中插入一个数 $x$，然后不断长度大于 $3$ 的消除相连的相同的数，问最多能删除多少个。

# 题目分析

观察到题目的 $n$ 很小，考虑直接枚举插入位置，然后模拟消除操作，并计算答案。

# AC code


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn=105;
int n,k,x;
int a[maxn],b[maxn];
int ansm=-1;//变量，无需多言

int calc()
{
	int ret=0;//此次消除个数
	for(int i=1;i<=n-1;i++)
	{
		while(b[i]==-1) i++;
		int j=i+1,tar=b[i],cnt=0;//j为末指针，tar为球的颜色，cnt为区间-1个数
		while(j<=n+1)
		{
			
			if(b[j]==-1)
			{
				while(b[j]==-1) j++,cnt++;//跨越-1
			}
			if(b[j]!=tar) break;
			j++;
		}
		j--;
		int len=j-i+1-cnt;//计算最终消除长度
		if(len<3) continue;//小于3则舍去
		ret+=len;
		for(int k=i;k<=j;k++)
		{
			b[k]=-1;//标记为消除
		}
	}
	return ret!=0?ret:-1;//-1表示消除不了了！
}

int work(int pos) //得到插入x后序列
{
	for(int i=0;i<=n;i++) b[i]=-1;//用-1表示消除了
	int len=n+1;
	int i=1,j=1;
	while(j<=n+1)
	{
		if(j==pos)
		{
			b[j]=x;
		}
		else
		{
			b[j]=a[i];
			i++;
		}
		j++;
	}//生成b数组，即插入后数组
	bool flag=true;
	int ans=0;
	do{
		int x=calc();
		if(x==-1) flag=false;
		else ans+=x;
	}while(flag);//不断消除知道不能消，计算答案
	
	return ans;
}

int main()
{
	cin>>n>>k>>x;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n+1;i++)
	{
		ansm=max(ansm,work(i));
	}
	cout<<((ansm==0)?0:ansm-1);//输出答案
	return 0;
}

```

# 一些细节

本题难度不大，但细节较多。

- 移动收尾指针 $i$ 和 $j$ 时，一定要处理好加减 $1$ 的关系。
- 计算长度时，注意区间大小如何计算。
- 关注不能消除以及以及已经被消除的情况，可以使用 $-1$ 标记。
- 答案数要减 $1$，无法消除不要输出 $-1$ 了！


[AC记录](https://www.luogu.com.cn/record/170420334)

希望这篇题解对你有所帮助。

---

## 作者：Y_J_Y (赞：2)

一看这题面，类似于祖玛的射球问题

分析一下，我们会很容易的发现当我们射入球的位置，我们可以试着枚举这个球的位置的左右两端(在下面的代码中我们用l,r来表示所扩展的左右端点，然后用L，R来辅助记录答案)，然后我们什么时候停止循环呢，细想一下，就会发现当射入的位置的左右两端所构成的区间里没有三个球时，这时我们就没法继续消除了，所以这个时候就可以退出循环，否则当我们消除完这个颜色的球时，可以换下一个球继续消除

可以根据下面给出的代码来进行理解

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
	int x=0,w=1;char ch=getchar();
	for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x*w;
}
#define maxn 1001
int n,k,x;
int a[maxn];
int ans=-inf;
int main() {
	n=read();k=read();x=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=0;i<=n;i++) {//枚举射入的位置
		int l=i,r=i+1,cnt=1,L,R,col=x;
		while(1) {//向左右两边扩展
			L=l;R=r;
			while(l&&a[l]==col) {//左边的球的颜色是与当前一样的，就可以继续扩展
				l--;
				cnt++;
			}
			while(r<=n&&a[r]==col) {//右边亦然
				r++;
				cnt++;
			}
			if(cnt<=2) {//当颜色小于3个时，就可以退出了
				l=L;r=R;break;
			}else {
				col=a[l];//反之换下一个颜色继续扩展
				cnt=0;
			}
		}
		ans=max(ans,r-l-1);//记录最大的枚举的答案
	}
	printf("%d\n",ans);
	return 0;
}

```

---

