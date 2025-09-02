# Shave Beaver!

## 题目描述

一位聪明的海狸最近发明了一种新型的纳米技术多功能海狸剃毛机「Beavershave 5000」，它能为整家族的海狸剃毛！这台机器是如何工作的呢？真是简单极了！

现有 $n$ 只海狸，每只海狸都有一个从 1 到 $n$ 的唯一编号。设想一个由这些海狸编号组成的排列 $a_1, a_2, \ldots, a_n$。如果存在一串下标 $i_1 < i_2 < \ldots < i_k$，使得 $a_{i1} = x$，$a_{i2} = x+1$，一直到 $a_{ik-1} = y-1$，$a_{ik} = y$，那么 Beavershave 5000 就可以在一次会话中为从编号 $x$ 到 $y$ 的海狸剃毛。例如，对排列 $1, 2, 3, \ldots, n$ 的海狸来说，只需要一次会话。

如果无法用一次会话剃掉编号从 $x$ 到 $y$ 的海狸，海狸们可以被分成若干组：$[x, p_1]$，$[p_1+1, p_2]$，……，$[p_m+1, y]$（$x \leq p_1 < p_2 < \ldots < p_m < y$），这样机器就可以在每组内一次完成剃毛。但此时 Beavershave 5000 总共需要 $m+1$ 次会话来处理从 $x$ 到 $y$ 的海狸。

这些海狸常常不安分，总是在尝试交换位置。因此，我们会遇到以下两类查询：

- 查询 Beavershave 5000 需要多少次会话才能完成编号从 $x$ 到 $y$ 的海狸的剃毛任务？
- 查询交换位置 $x$ 和 $y$ 上海狸（即交换 $a_x$ 和 $a_y$）。

可以假设任何一只海狸可以多次被剃毛。

## 样例 #1

### 输入

```
5
1 3 4 2 5
6
1 1 5
1 3 4
2 2 3
1 1 5
2 1 5
1 1 5
```

### 输出

```
2
1
3
5
```

# 题解

## 作者：WYZ20030051 (赞：0)

题意：给定一个 $1-n$ 的排列 $a$ 和 $q$ 次操作。
操作1：查询数字 $x$ 到数字 $y$ 有多少连续上升子序列。
操作2：交换 $a_x$ 和 $a_y$。

------------

作为 B2 的究极弱化版（$n\le100$），只要能读对题意就很容易能写对了（至少我是因为读错题卡了半个小时没看出来错误）。注意这里的操作一指的是求值域在 $[x,y]$ 之间的数组成的序列中有多少连续子序列，操作二的交换操作指的是交换下标所对应的数字。

操作二直接暴力 swap 就行了，操作一因为 $n$ 非常小所以直接暴力统计答案就可以了。

------------

### CODE
```cpp
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int ll
int read()
{
    ll now = 0, nev = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            nev = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        now = (now << 1) + (now << 3) + (c & 15);
        c = getchar();
    }
    return now * nev;
}
const int MAXN = 1e6 + 10;
const int mod = 998244353;
int n,m;
int a[MAXN];
void modefy(int x,int y)
{
	swap(a[x],a[y]);
}
int query(int x,int y)
{
	int res=0;
	while(x<=y)
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]==x)
				x++;
		}
		res++;
	}
	return res;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	m=read();
	for(int i=1;i<=m;i++)
	{
		int op=read(),x=read(),y=read();
		if(op==1)
			printf("%lld\n",query(x,y));
		if(op==2)
			modefy(x,y);
	}
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

区间连续上升子段划分，考虑枚举断点，当 $a_i$ 的位置大于 $a_i+1$ 的位置时，一定会出现一个新段。交换两个元素便维护变化量，树状数组即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,q;
int a[300005];
int p[300005];
struct BIT{
	int tree[300005];
	int lowbit(int i){return i&-i;}
	void add(int pos,int val){
		for(int i=pos;i<=n;i+=lowbit(i))tree[i]+=val;
	}
	int ask(int l,int r){
		int ans=0;
		for(int i=r;i;i-=lowbit(i))ans+=tree[i];
		for(int i=l-1;i;i-=lowbit(i))ans-=tree[i];
		return ans;
	}
}T;
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),p[a[i]]=i;
	for(int i=1;i<n;i++)if(p[i]>=p[i+1])T.add(i,1);
	a[n+1]=n+1;
	p[n+1]=n+1;
	q=read();
	while(q--){
		int opt=read();
		if(opt==2){
			int x=read(),y=read();
			if(a[x]>a[y])swap(x,y);
			if(p[a[x]]>=p[a[x]+1])T.add(a[x],-1);
			if(p[a[x]-1]>=p[a[x]])T.add(a[x]-1,-1);
			if(p[a[y]]>=p[a[y]+1])T.add(a[y],-1);
			if(a[y]-1!=a[x]&&p[a[y]-1]>=p[a[y]])T.add(a[y]-1,-1);
			swap(p[a[x]],p[a[y]]);
			swap(a[x],a[y]);
			swap(x,y);
			if(p[a[x]]>=p[a[x]+1])T.add(a[x],1);
			if(p[a[x]-1]>=p[a[x]])T.add(a[x]-1,1);
			if(p[a[y]]>=p[a[y]+1])T.add(a[y],1);
			if(a[y]-1!=a[x]&&p[a[y]-1]>=p[a[y]])T.add(a[y]-1,1);
		}else{
			int l=read(),r=read();
			cout<<T.ask(l,r-1)+1<<"\n";
		}
	}
} 
```

---

