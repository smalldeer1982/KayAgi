# Valera and Swaps

## 题目描述

时间限制 $1s$   |   空间限制 $256M$




给出长度为$n$的排列$p$，定义长度为$n$的*本体排列* 为满足$p_i=i$（$1\le i\le n$）的排列。互换操作是指对于$(i,j)$（$1\le i,j\le n$）互换$p_i,p_j$在排列中的位置。设$f(p)$为将排列$p$通过互换操作转变为本体排列的最小操作数。请求出如何花费最小的步数将排列$p$转变为排列$q$使得$f(q)=m$。

## 样例 #1

### 输入

```
5
1 2 3 4 5
2
```

### 输出

```
2
1 2 1 3 ```

## 样例 #2

### 输入

```
5
2 1 4 5 3
2
```

### 输出

```
1
1 2 ```

# 题解

## 作者：zhendelan (赞：1)

## 题意  

给定一个长度为$n$的排列$p$。$f(p)$为使变为排列$1,2...n$的最小交换次数。  

每次交换$(i,j)$指交换$p_i$与$p_j$。  

给定一个$m$，问使$f(p)=m$的最小交换次数。  

## 分析 

先考虑$f(p)$怎么求。  

发现排列中的关系是几个环。比如排列$2,1,4,5,3$。  
  
将$-$看做目标位置的话的话，上面这个排列可以表示成。  
  
$2-1-2,4-5-3-4$。两个环，那么上面排列的$f$值就是$5-2=3$。(因为一个环可以减少一次交换，建议自己试试看更好理解)。  


这样就可以求出$O(n)$求出一个排列的$f$了。  

设环的个数为$k$,比较初始的$n-k$与$m$。  

如果$n-k<m$就要减少环的数量。任取两个环，交换其中任意元素就可以了，这样就把两个环相连了，环的个数减少了$1$。  

如果$n-k>m$就要增加环的数量。在一个点数大于$2$的环内，任意交换两个元素，这个环就断成了两个，也就减少了一个环。  


这题要求字典序最小，所以每次枚举合法的字典序最小的方案，然后再在排列上把每个点所在的环以及环的大小跑出来就可以了。  

时间复杂度$O(n^2)$。    

不过要注意，这里是让交换的编号最小，即$(i,j)$最小，不是$(p_i,p_j)$最小。

## 代码 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3020;
int tot,in[N],siz[N];
int n,a[N];
void build()
{
	memset(in,0,sizeof(in));
	tot = 0;
	for(int i=1;i<=n;i++)if(!in[i])
	{
		++tot;siz[tot]=1;
		in[i] = tot;
		for(int j=a[i];j!=i;j=a[j])in[j]=tot,siz[tot]++;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	build();
	int m;
	scanf("%d",&m);
	printf("%d\n",abs(n-tot-m));
	if(n-tot>m)
	{
		while(n-tot>m)
		{
			for(int i=1;i<=n;i++)if(siz[in[i]]>=2)
			{
				int lag=0;
				for(int j=i+1;j<=n;j++)if(in[j]==in[i])
				{
					lag=j;
					break;
				}
				swap(a[i],a[lag]);
				printf("%d %d ",i,lag);
				break;
			}
			build();
		}
	}
	else
	{
		while(n-tot<m)
		{
			for(int i=2;i<=n;i++)if(in[i]!=in[1])
			{
				swap(a[1],a[i]);
				printf("%d %d ",1,i);
				break;
			}
			build();
		}
	}
	return 0;
}
```

---

