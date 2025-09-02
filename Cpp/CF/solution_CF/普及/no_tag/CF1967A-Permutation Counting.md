# Permutation Counting

## 题目描述

你有一些卡片。具体地，你有 $a_i$ 张写着 $i$ 的卡片 $(i\in [1,n])$。

现在你可以从商店购买 $k$ 张空白卡片，并且在这 $k$ 张卡片上任意填上一个 $[1,n]$ 中的整数。

定义一个序列是 $n$ 好的，且仅当它长度为 $n$ 且升序排序后是 $1$ 到 $n$ 的排列。

购买并填完 $k$ 张卡片后，你需要重新将这些卡片排序，使得你的序列中的 $n$ 好子段个数最多并求出个数。

## 说明/提示

$1\le n\le 2\times 10^5,0\le a_i,k\le 10^{12},1\le T\le 100,1\le\sum n\le 5\times 10^5$

## 样例 #1

### 输入

```
8
1 10
1
2 4
8 4
3 4
6 1 8
3 9
7 6 2
5 3
6 6 7 4 6
9 7
7 6 1 7 6 2 4 3 3
10 10
1 3 1 2 1 9 3 5 7 5
9 8
5 8 7 5 1 3 2 9 8```

### 输出

```
11
15
15
22
28
32
28
36```

# 题解

## 作者：yanqijin (赞：1)

# 题目大意
给你一堆标号为 $1$ 到 $n$ 的卡牌，标号为 $i$ 的卡牌有 $a_i$ 张。你可以变出 $k$ 张卡牌。你要最大化使用了 $k$ 张卡牌之后排列出的连续的标号 $1$ 到 $n$ 的个数。
# 思路
一眼贪心。首先我们发现可以持续连着多少轮是由最小值决定的，所以我们考虑将最小值最大化。最大化最小值后再尽量放平均即可。
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,a[200005];
void read(long long &x)
{
	x=0;
	int w=1;
	char ch=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	x*=w;
}
void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	int sta[100];
	int top=0;
	do
	{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(sta[--top]+48);
	putchar('\n');
}
int main()
{
	read(t);
	while(t--)
	{
		read(n);read(k);
		for(int i=1;i<=n;i++) read(a[i]);
		sort(a+1,a+1+n);//排序
		long long sum=0,id=0,gg=0;
		for(int i=1;i<=n;i++)
		{
			sum+=a[i];
			if(a[i]*i-sum<=k) id=i,gg=a[i]*i-sum;//最大化最小值
		}
		k-=gg;
		long long h=k/id,hh=k%id;
		long long f=a[id]+h;
		write(f*n-n+1+(n-id+hh));//平均
	}
	return 0;
} 
```

---

## 作者：exCat (赞：0)

简单题。\
如果给你最终的卡牌，如何让好字段数量最多？显然我们把 $a_1,a_2,a_3,...,a_n$ 当一组，凑出尽可能多的组连着放，剩下的不成组的单个接着往后放。最优的组内的顺序应该是 $a_1$ 到 $a_n$ 按数量升序排。所以影响我们的主要因素是最小的数量。\
所以问题转化为最小值最大的问题，所以二分解决问题。\
二分最小的数量，然后将每一个不足的 $a_i$ 向上补，判断是否合法，即可。\
拓展：还有实现更为复杂的线性做法，不过总时间复杂度瓶颈不在最后，所以时间复杂度不变。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
#define ll long long
const ll ee=1e18+10;
ll ans,t,n,k,a[N];
ll check(ll x)
{
	ll cnt=0,sum=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<=x)cnt++,sum+=x-a[i];
		if(sum>k)return ee; 
	}
	return cnt-(k-sum);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		ll l=1,r=1e15+10,mid,sum=0;
		while(l<=r)
		{
			mid=(l+r)>>1;ll tmp=check(mid);
			if(tmp!=ee)ans=mid,sum=tmp,l=mid+1;
			else r=mid-1;
		}
		cout<<ans*n-(n-1)+n-sum<<'\n';
	}
	return 0;
} 
```

---

