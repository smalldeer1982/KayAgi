# Car Repair Shop

## 题目描述

Polycarp 开始创业了，明天他将开始汽车修理。目前，汽车修理厂非常小，不能同时修理多辆汽车。

Polycarp 已经从客户那里收集了 $n$ 个请求。请求编号从 $1$ 到 $n$。

第 $i$ 个请求包含两个值：$s_i$ 为客户希望开始维修其汽车的日期，$d_i$ 为维修汽车所需天数。天数从 $1$ 开始计算，第一天是明天，第二天是后天，依此类推。

Polycarp 从 $1$ 到 $n$ 依次考虑每个请求，对于第 $i$ 个请求：

- 如果 $\left[s_i,s_i+d_i-1\right]$ 这些天修理厂是闲置的，那么 $\left[s_i,s_i+d_i-1\right]$ 这些天就用来修理第 $i$ 个客户的车子

- 否则就找到最小的一个 $x$，满足 $\left[x,x+d_i-1\right]$ 这些天工厂是闲置的，然后把 $\left[x,x+d_i-1\right]$ 这些天用来修理第 $i$ 个客户的车子

给出 $n$ 个请求，请求出每个客户的车子是在那些天被修理的。

## 样例 #1

### 输入

```
3
9 2
7 3
2 4
```

### 输出

```
9 10
1 3
4 7
```

## 样例 #2

### 输入

```
4
1000000000 1000000
1000000000 1000000
100000000 1000000
1000000000 1000000
```

### 输出

```
1000000000 1000999999
1 1000000
100000000 100999999
1000001 2000000
```

# 题解

## 作者：Ninelife_Cat (赞：2)

提供一种 STL 写法。

我们把所有空闲的区间丢进一个 ```set``` 里面，然后对于每个修理请求，遍历 ```set```。

如果有一段空闲区间 $[l,r]$ 包含了 $[s_i,s_i+d_i-1]$，那么我们就把 $[l,r]$ 分成 $[l,s_i-1]$，$[s_i,s_i+d_i-1]$ 和 $[s_i+d_i,r]$ 三部分。因为我们使用的是 $[s_i,s_i+d_i-1]$ 这一段区间，所以区间 $[l,s_i-1]$
 和 $[s_i+d_i,r]$ 仍是空闲的。那么如果区间 $[l,s_i-1]$ 和 $[s_i+d_i,r]$ 不为空，就把它们丢回 ```set``` 里。

如果没有任何一段空闲区间包含 $[s_i,s_i+d_i-1]$，那么就找到最前面的一段长度大于等于 $d_i$ 的区间 $[l,r]$，把它分成 $[l,l+d_i-1]$ 和 $[l+d_i,r]$ 两部分。此时我们使用的是 $[l,l+d_i-1]$ 这段区间，那么如果 $[l+d_i,r]$ 不为空就把它丢回 ```set``` 里。

核心代码：

```cpp
#define mp make_pair
#define int long long
const int N=201+10;
int n,s[N],d[N];
set<pair<int,int> > q;
signed main()
{
	n=read();
	for(ri int i=1;i<=n;++i)
		s[i]=read(),d[i]=read();
	q.insert(mp(1,2000000000));//初始的空闲区间
	for(ri int i=1;i<=n;++i)
	{
		ri int f=0;
		for(set<pair<int,int> >::iterator it=q.begin();it!=q.end();++it)
		{
			pair<int,int> res=*it;
			if(res.fir<=s[i]&&res.sec>=s[i]+d[i]-1)
			{
				q.erase(q.find(res));cout<<s[i]<<" "<<s[i]+d[i]-1<<endl;f=1;
				if(res.fir<s[i]) q.insert(mp(res.fir,s[i]-1));
				if(res.sec>s[i]+d[i]-1) q.insert(mp(s[i]+d[i],res.sec));
				break;
			}
		}//该请求空闲的情况
		if(!f) for(set<pair<int,int> >::iterator it=q.begin();it!=q.end();++it)
		{
			pair<int,int> res=*it;
			if(res.sec-res.fir+1>=d[i])
			{
				q.erase(q.find(res));cout<<res.fir<<" "<<res.fir+d[i]-1<<endl;
				if(res.sec>res.fir+d[i]-1) q.insert(mp(res.fir+d[i],res.sec));
				break;
			}
		}	
	}
	return 0;
}
```

---

## 作者：Bai_R_X (赞：1)

## 思路
我们储存已经分配好的一个个“内存线段”，优先考虑最开始输入的以 $s_i$ 为开头的线段，遍历一遍已经存好的线段，看是否重叠，不重叠就直接存。

而对于重叠，我们遍历左端点。但如果直接遍历是否重叠了话，时间复杂度会极高，所以我们可以考虑使用贪心优化：如果当前线段不重叠，直接存储；否则直接跳转到重叠的线段的右端点的右边，这样就可以优化了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct line
{
	int l,r;
	line(){}
	line(int L,int R)
	{
		l=L;
		r=R;
	}
	void set(int L,int R)
	{
		l=L;
		r=R;
	}
	bool check(const line& x)
	{
		return (l<=x.r&&l>=x.l)||(r<=x.r&&r>=x.l)||(l<=x.l&&r>=x.r);
	}
	bool operator<(const line& x)
	{
		return l<x.l;
	}
}a[205];
int n,i,j,s,d,cnt;
signed main()
{
    cin>>n;
    while(n--)
    {
    	cin>>s>>d;
    	bool f=0;
    	line nw(s,s+d-1);
    	for(i=1;i<=cnt;i++)
    	{
    		if(nw.check(a[i]))
    		{
    			f=1;
    			break;
			}
		}
		if(f)
		{
			sort(a+1,a+cnt+1);//PS:这句话好像可以不加
			for(i=1;;)
			{
				nw.set(i,i+d-1);
				bool f=1;
				for(j=1;j<=cnt;j++)
				{
					if(nw.check(a[j]))
		    		{
		    			i=a[j].r+1;
		    			f=0;
		    			break;
					}
				}
				if(f)break;
			}
		}
		a[++cnt]=nw;
		cout<<nw.l<<" "<<nw.r<<endl;
	}
    return 0;
}
```

---

## 作者：luckydrawbox (赞：0)

## 题意

有 $n$ 个请求，每次请求一个区间 $[s_i,s_i+d_i-1]$：

- 如果该区间完全没有被占用，占用该区间。

- 如果该区间有位置已经被占用，占用另一个长度为 $s_i$，左端点最小的且完全未被占用的区间。

求出每个请求占用的区间。

## 分析

我们需要进行的操作有：

- 查询某个区间是否被用过。

- 插入某个已知边界的区间。

- 插入某个已知长度的区间。

由于有插入操作的存在，所以我们需要一个支持在任意位置插入元素、查询元素的数据结构，可以看到 $n$ 最大只有 $200$，所以我们可以使用**链表**来实现。

```cpp
struct Q{
	int nxt;//下一个节点
	ll l,r;//左右边界
}a[N];
```

### 初始化

一开始，令整个链表只有两个节点 $0$ 和 $1$，分别是起点和终点，节点 $0$ 中的区间是 $[0,0]$，节点 $1$ 中的区间是 $[10^{10},10^{10}]$，由题目中的数据可以算出题目所用的区间一定在这两个之间。

```cpp
a[0].l=a[0].r=0;
a[1].l=a[1].r=1ll*1e5*1e5;
a[0].nxt=1;
a[1].nxt=0;
```

### 查询某个区间是否被用过

设查询 $[l,r]$ 是否被占用。

依次遍历每个节点，如果某个区间 $i$ 满足以下条件，说明它查询区间被占用，立即结束。

- $a[i].l\le l$ 且 $l\le a[i].r$：$[l,r]$ 的左部分被别的区间占用。

- $a[i].l\le r$ 且 $r\le a[i].r$：$[l,r]$ 的右部分被别的区间占用。

- $l\le a[i].l$ 且 $a[i].r\le r$：$[l,r]$ 的中部分被别的区间占用。

```cpp
bool find(ll l,ll r){
	for(int i=a[0].nxt;i;i=a[i].nxt)
		if((l>=a[i].l&&l<=a[i].r)||(r>=a[i].l&&r<=a[i].r)||(l<=a[i].l&&r>=a[i].r))
			return 1;
	return 0;
}
```

### 插入某个已知边界的区间

设插入区间 $[l,r]$。

依次遍历每个节点 $i$，并记录它的下一个节点 $j$，如果 $[l,r]$ 在两个区间之间的区间中，即 $a[i].r<l$ 且 $r<a[j].l$，就插入这个区间。

注意新的区间可能比之前的更小，**所以遍历要从 $0$ 节点开始**。

```cpp
void insert1(ll l,ll r){
	for(int i=0;a[i].nxt;i=a[i].nxt){
		int j=a[i].nxt;
		if(a[i].r<l&&r<a[j].l){
			a[++t].l=l;
			a[t].r=r;
			a[i].nxt=t;
			a[t].nxt=j;
			return;
		}
	}
}
```

### 插入某个已知长度的区间

设插入区间长度为 $len$。

同样依次遍历每个节点 $i$，并记录它的下一个节点 $j$，如果这两个区间之间的区间大于等于 $len$ 的，即 $a[j].l-a[i].r-1\ge len$，就插入这个区间，并用 $al,ar$ 记录答案。

同样注意新的区间可能比之前的更小，**所以遍历要从 $0$ 节点开始**。

```cpp
void insert2(ll len){
	for(int i=0;a[i].nxt;i=a[i].nxt){
		int j=a[i].nxt;
		if(a[j].l-a[i].r-1>=len){
			al=a[++t].l=a[i].r+1;
			ar=a[t].r=a[t].l+len-1;
			a[i].nxt=t;
			a[t].nxt=j;
			return;
		}
	}
}
```

时间复杂度 $O(n^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
const int N=210;
int n,t=1;
ll s,d,al,ar;
struct Q{
	int nxt;
	ll l,r;
}a[N];
bool find(ll l,ll r){
	for(int i=a[0].nxt;i;i=a[i].nxt)
		if((l>=a[i].l&&l<=a[i].r)||(r>=a[i].l&&r<=a[i].r)||(l<=a[i].l&&r>=a[i].r))
			return 1;
	return 0;
}
void insert1(ll l,ll r){
	for(int i=0;a[i].nxt;i=a[i].nxt){
		int j=a[i].nxt;
		if(a[i].r<l&&r<a[j].l){
			a[++t].l=l;
			a[t].r=r;
			a[i].nxt=t;
			a[t].nxt=j;
			return;
		}
	}
}
void insert2(ll len){
	for(int i=0;a[i].nxt;i=a[i].nxt){
		int j=a[i].nxt;
		if(a[j].l-a[i].r-1>=len){
			al=a[++t].l=a[i].r+1;
			ar=a[t].r=a[t].l+len-1;
			a[i].nxt=t;
			a[t].nxt=j;
			return;
		}
	}
}
int main(){
	a[0].l=a[0].r=0;
	a[1].l=a[1].r=1ll*1e5*1e5;
	a[0].nxt=1;
	a[1].nxt=0;
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>s>>d;
    	if(find(s,s+d-1)){
    		insert2(d);
    		cout<<al<<" "<<ar<<endl;
		}
		else{
			insert1(s,s+d-1);
			cout<<s<<" "<<s+d-1<<endl;
		}
	}
	return 0;
}
```


---

