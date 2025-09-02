# 展覧会 2 (Exhibition 2)

## 题目描述

美术馆有 $n$ 幅画，在画廊里从西向东排成一列，这些画从西向东编号为 $1$ ∼ $n$，第 $i$ 幅画在距离最西端 $x_i$ 米位置，它的价值为 $v_i$。

明天要召开展览会，来客会非常多，馆长决定只展出其中 $m$ 幅画，其他画都拿走放到库房里。如果留下的画距离太近，观众们观赏起来会不方便。所以留下的画之间的距离必须大于等于 $D$。

展览会的“华丽度”定义为展出的 $m$ 幅画中，价值最低的画的价值。通过适当选择留下的 $m$ 幅画，能得到最大的“华丽度”是多少。

## 样例 #1

### 输入

```
3 1 34
10 250
30 200
50 500```

### 输出

```
500```

## 样例 #2

### 输入

```
4 4 10
21 160
32 270
11 115
44 205```

### 输出

```
115```

## 样例 #3

### 输入

```
4 4 14
21 160
32 270
11 115
44 205```

### 输出

```
-1```

## 样例 #4

### 输入

```
6 3 4
4 2
5 2
2 1
9 2
1 1
7 2```

### 输出

```
1```

## 样例 #5

### 输入

```
15 6 129
185 2821
683 3312
101 3406
485 2120
671 1992
869 2555
872 3123
237 2970
351 2374
996 2090
729 2686
375 2219
820 3085
511 3217
924 4229```

### 输出

```
2219```

# 题解

## 作者：crzcqh (赞：6)

## 思路

既然要使华丽度最大，有合法条件，并且 $1\le n\le 10^5$，自然想到二分，可以二分华丽度，最后输出 $l$。

那么如何 check 呢？既然要保留 $m$ 幅画，那么可以我们可以贪心，在满足与上一幅**被展出的画**的距离 $\ge D$ 的情况下如果这幅画的华丽度 $\ge mid$，说明这幅画是可以展出的，记录这幅画。

经过这样的贪心策略，我们可以使能出展的画的数量最大，且华丽度 $\ge mid$。最后判断：如果出展的画的数量**大于等于** $m$，则这个 $mid$ 是合法的，继续二分缩小范围。

为什么是出展的画的数量 $\ge m$，而不是出展的画的数量 $=m$ 呢？两个原因：

1. 即使能出展的画的数量 $\ge m$，我们总是能减少几幅价值最大的画，使展出的画的数量 $=m$，且华丽度不变，因为华丽度只跟最小值有关，故答案也是正确的。

2. 为了二分，如果直接把这个方式判定为不合法，那么比 $mid$ 更下的直接不判了，自然会 WA。

时间复杂度 $O(n\log \max\limits_{1\le i \le n}(v_i))$。

## CODE

```cpp
#include<bits/stdc++.h>
#define F(l,r,i) for(i=l;i<=r;i++)
#define ll long long
#define M1 1007
#define M2 100007
using namespace std;
int n,m,D,l=-1,r=1000000007,mid;
struct node{  
	int x,y;
}a[M2];
bool cmp(node l,node r){
	return l.x<r.x;
}
bool check(int s){
	int p=0,ans=0;
	for(int i=1;i<=n;i++){
		if(a[i].x-a[p].x>=D&&a[i].y>=s) p=i,ans++;
	}
	return ans>=m;
}
int main(){
	cin>>n>>m>>D;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	sort(a+1,a+1+n,cmp);
	a[0].x=-D;
	while(l+1<r){
		mid=l+r>>1;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<l<<endl;
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_joig2021_d)

## 前置知识

[二分答案](https://oi-wiki.org/basic/binary/#二分答案)

## 解法

最小值最大，考虑二分答案。

关于 ``check`` 函数的书写，比 [luogu P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182) 多了个对位置的判定，注意对当前是第一次展出时进行特判。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
	int x,v;
}a[100001];
bool cmp(node a,node b)
{
	return a.x<b.x;
}
bool check(int mid,int n,int m,int d)
{
	int ans=0,last=0,i;
	for(i=1;i<=n;i++)
	{
		if((last==0||a[i].x-a[last].x>=d)&&a[i].v>=mid)
		{
			last=i;
			ans++;
		}
	}
	return ans>=m;
}
int main()
{
	int n,m,d,l=0,r=0,mid,ans=-1,i;
	cin>>n>>m>>d;
	for(i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].v;
		r=max(r,a[i].v);
	}
	sort(a+1,a+1+n,cmp);
	while(l<=r)
	{
		mid=(l+r)/2;
		if(check(mid,n,m,d)==true)
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

