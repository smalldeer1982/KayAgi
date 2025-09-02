# Shuffle

## 题目描述

You are given an array consisting of $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ . Initially $ a_x = 1 $ , all other elements are equal to $ 0 $ .

You have to perform $ m $ operations. During the $ i $ -th operation, you choose two indices $ c $ and $ d $ such that $ l_i \le c, d \le r_i $ , and swap $ a_c $ and $ a_d $ .

Calculate the number of indices $ k $ such that it is possible to choose the operations so that $ a_k = 1 $ in the end.

## 说明/提示

In the first test case, it is possible to achieve $ a_k = 1 $ for every $ k $ . To do so, you may use the following operations:

1. swap $ a_k $ and $ a_4 $ ;
2. swap $ a_2 $ and $ a_2 $ ;
3. swap $ a_5 $ and $ a_5 $ .

In the second test case, only $ k = 1 $ and $ k = 2 $ are possible answers. To achieve $ a_1 = 1 $ , you have to swap $ a_1 $ and $ a_1 $ during the second operation. To achieve $ a_2 = 1 $ , you have to swap $ a_1 $ and $ a_2 $ during the second operation.

## 样例 #1

### 输入

```
3
6 4 3
1 6
2 3
5 5
4 1 2
2 4
1 2
3 3 2
2 3
1 2```

### 输出

```
6
2
3```

# 题解

## 作者：Milthm (赞：3)

## CF1366B 题解

### 前置知识

- 区间

### 题目解法

我们可以先想一下，如果 $l_i$ 到 $r_i$ 中包含可能是 $1$ 的地方，那么通过交换以后肯定都有可能是 $1$。

这样一想就明白了，那么是不是只需要枚举就可以呢？

——不可能。

容易发现，枚举是肯定超时的。这个时候我们再想一下，可以开始想象有一个区间，这个区间就是可能有 $1$ 的区间。因为肯定 $[l_i,r_i]$ 区间和它有重复元素才能和它进行反应，所以这个区间一定是连续的。那么我们只需要两个变量，分别代表左端点和右端点，如果有重叠部分就将区间扩大至正好包括两个区间就可以了。

具体判断是否重叠方法看代码。

### AC代码

```cpp
#include<iostream>
using namespace std;
int t,n,m,x,l,r,ql,qr;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x>>m;
		ql=qr=x;//初始化区间为 [x,x]
		while(m--){
			cin>>l>>r;
			if(l<=ql&&ql<=r||l<=qr&&qr<=r){//如果左端点在区间内或右端点在区间内就扩大（不然两个区间绝对不可能重合）
				ql=min(ql,l);//扩大左端点
				qr=max(qr,r);//扩大右端点
			}
		}
		cout<<qr-ql+1<<endl;//输出区间长度
	}
	return 0;
} 
```


---

## 作者：Error_Eric (赞：1)

### 思路

我们先举一个简单的例子：

$\{a_n\}=\{1,0,0,0,0,0\},l=2,r=4$

对于这次交换，交换后只有 $a_1$ 可能是 $1$ 。

$\{a_n\}=\{?,?,?,0,0,0\},l=4,r=6$( $?$ 表示可能是 $1$ )

对于这次交换，交换后只有 $a_1,a_2,a_3$ 可能是 $1$ 

由这一类例子可以推导出的是：**对于任意的 $l,r$，当 $[ l , r ]$ 之间交换之前没有可能是 $1$ 的数的时候，这个区间里面交换之后也没有可能有是 $1$ 的数。**

------------

我们再举一个简单的例子：

$\{a_n\}=\{1,0,0,0,0,0\},l=1,r=4$ 。

对于这次交换，交换后 $a_1$ 到 $a_4$ 都可能是 $1$ 。

$\{a_n\}=\{0,0,0,?,?,?\},l=1,r=4$ 。

对于这次交换，交换后 $a_1$ 到 $a_6$ 都可能是 $1$ 。

由这一类例子可以推导出的是：**对于任意的 $l,r$，当 $[ l , r ]$ 之间交换之前有可能是 $1$ 的数的时候，这个区间里面交换之后全部的数都可能为 $1$ 。**

----------

综上所述:**对于任意的 $l,r$，当且仅当在交换之前$[l,r]$之间有可能是 $1$ 的数时，这个区间里的所有数在交换后有可能为 $1$ 。**

我们的第一版代码就这么出来了。用$\Theta(r-l+1)$扫一遍判断是否可能有 $1$ ,如果有，就把这个区间全部赋成 $1$ 。

我们一看数据大小：$1\le n \le 10^9$,极端情况总时间复杂度$\Theta(nmt)$，直接炸裂！

那么有没有更快的办法呢？

一看，**开始只有 ${a_x=1}$** ,换言之，所有的可能为 $1$ 的数字都在一个连续的区间中，并且这个区间是由$[x,x]$扩展而来的！

只需要扩展区间，问题就解决了。

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int t,n,x,m,xi,yi,fr,to;//前四个如题,xi->l,yi->r,fr->区间左端,to->区间右端。
int main(){
    scanf("%d",&t);//有多组数据
    while(t--){
        scanf("%d%d%d",&n,&x,&m),fr=to=x;//输入，初始区间为[x,x]。
        for(int i=1;i<=m;i++){//对于每一次扩展。
            scanf("%d%d",&xi,&yi);//输入。
            if((not(xi>to) and (not(yi<fr))))如果这次输入的区间与可能有1的区间有重合部分。
                fr=min(fr,xi),to=max(to,yi);那么这次输入的区间里面的数字都可能是1。
        }
        printf("%d\n",to-fr+1);//区间大小就是元素个数
    }
}
```

---

## 作者：45dinо (赞：1)

阅读样例后，可以模糊地找到一个规律：如果某一个区间中有一个点有可能是 1 ，这个区间的所有点都有可能是 1。

或许下面的说法会更合适。

一开始只有 x 的位置进行了标记，枚举 $1-m$ 的每次操作，对于第 $i$ 次操作，如果 $l_i$ 到 $r_i$ 之间有位置被标记，就标记整个区间。最后被标记的位置的个数即为所求。

显而易见，这种算法会 ![](https://cdn.luogu.com.cn/upload/image_hosting/51d80tin.png) 。原因也显而易见，不能也不需要把 $l_i$ 到 $r_i$ 每一个元素的访问一遍。

在寻找一些深层次的规律，发现每一次标记完的区间都是一个连续段，所以每次的寻找——标记的过程就可以看作两个区间的合并——第 i 个区间和第 i-1 操作结束后被标记的区间。

看到这里，应该就有思路了吧。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,m,L,R,k,l[101],r[101];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&n,&x,&m);
		k=L=R=0;
		for(int i=1;i<=m;i++)
			scanf("%d%d",&l[i],&r[i]);
		for(int i=1;i<=m;i++)
			if(l[i]<=x&&x<=r[i])
			{
				k=i;
				L=l[i];
				R=r[i];
				break;
			}
		for(int i=k+1;i<=m;i++)
		{
			if(r[i]<L)
				continue;
			if(l[i]>R)
				continue;
			L=min(l[i],L);
			R=max(r[i],R);
		}
		cout<<R-L+1<<endl;
	}
	return 0;
}
```

---

## 作者：lhs_chris (赞：0)

# 暴力
先从暴力写起。枚举 $l \sim r$，只要这个区间内有一个 $1$，那么就将区间内的所有数字都变成 $1$。
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
#define lhs printf("\n");
using namespace std;
const int N=1e7+10;
const int M=2024;
const int inf=0x3f3f3f3f;
int t,n,m,x; 
bool a[N];
int l,r,ans;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		memset(a,0,sizeof a);
		scanf("%d%d%d",&n,&x,&m);
		a[x]=1;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&l,&r);
			bool flag=0;
			for(int j=l;j<=r;j++)
			{
				if(a[j]==1)
				{
					flag=1;
					break;
				}
			}
			if(flag)
			{	
				for(int j=l;j<=r;j++)
				{
					a[j]=1;
				} 
			}
		}
		for(int i=1;i<=n;i++)if(a[i])ans++;
		printf("%d\n",ans);
		
	}
	return 0;
}
```
但是看到数据范围 $n \leq 10^9$，这个范围，数组不仅开不下，而且还会超时。那么考虑正解。
# 思路
由于每次扩充区间都是连续的，所以只需要记录该序列的左端点坐标与右端点坐标。每次更新两端的坐标即可。
# 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
#define lhs printf("\n");
using namespace std;
const int N=1e7+10;
const int M=2024;
const int inf=0x3f3f3f3f;
int t,n,m,x; 
bool a[N];
int l,r,ansl,ansr;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		memset(a,0,sizeof a);
		scanf("%d%d%d",&n,&x,&m);
		ansl=ansr=x;//初始区间
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&l,&r);
			if(l<=ansl and ansl<=r)
			{
				ansl=min(ansl,l);
			}
			if(l<=ansr and ansr<=r)
			{
				ansr=max(ansr,r);
			}
		}
 
		printf("%d\n",ansr-ansl+1);
		
	}
	return 0;
}
```

---

