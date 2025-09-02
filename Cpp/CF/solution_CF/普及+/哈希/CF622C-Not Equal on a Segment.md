# Not Equal on a Segment

## 题目描述

给定一个有n个整数和m个查询的A数组。第i个查询是三个整数l[i]，r[i]，x[i]。对于第i个查询，查找任何位置p[i]（l[i]<=p[i]<=r[i]），以便a[p[i]]≠x[i]。

## 样例 #1

### 输入

```
6 4
1 2 1 1 3 5
1 4 1
2 6 2
3 4 1
3 4 2
```

### 输出

```
2
6
-1
4
```

# 题解

## 作者：谦谦君子 (赞：5)

## 题目大意：
给定一个长度为n（n不超过200000）的序列，有m（m不超过200000）次询问，第i次询问一个区间[li,ri]内是否存在一个数不等于一个给定值x。如果存在，就输出这个数的位置，否则输出-1，输出任意一个即可。

思路：这题还是比较好想的，用一个pos数组表示每个数前面第一个与它相同的数的下标。

**Step1:预处理：**
```cpp
if (a[i]==a[i-1])
{
	pos[i]=pos[i-1];
}
else
{
	pos[i]=i;
}
```
**Step2:判断输出**

- 当a[r] = x时， 需判断pos[r]与l的关系
- 当a[r] = x时，输出r即可

# 具体见代码

## 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001],pos[1000001];            //pos[i]表示i前面第一个相同的的下标
int n,m;
int main()
{
	while (~scanf("%d%d",&n,&m))
	{
		for (int i=1;i<=n;i++)          	//预处理，有点像并查集
		{
			scanf("%d",&a[i]);
			if (a[i]==a[i-1])
			{
				pos[i]=pos[i-1];
			}
			else
			{
				pos[i]=i;
			}
		}
		int l,r,x;
		while (m--)                     //这里就是判断输出了
		{
			scanf("%d%d%d",&l,&r,&x);
			if (a[r]==x)
			{
				if (pos[r]<=l)
				{
					cout<<"-1"<<endl;
				}
				if (pos[r]>l)
				{
					cout<<pos[r]-1<<endl;
				}
			}
			if (a[r]!=x)
			{
				cout<<r<<endl;
			}
		}
	}
	return 0;
}
```


注意：不用scanf会TLE,如果还是TLE的话cout改成printf就好了，~~实在不行写快读什么的~~

---

## 作者：oier_Jozerry (赞：1)

~~首先读题，读题是解决问题的关键。~~

说明：在自己思考无果后，查看了[这位哥们的代码](https://www.luogu.com.cn/blog/modestr/solution-cf622c)，并在思路上有所更改。

题目就是说：
依次输入 $l$ $r$ $x$。数组 $a$ 从 $r$ 开始找，直到找到 $l$，**找下标最大的**不等于 $x$ 的 $a[i]$。

我看着运行时间瑟瑟发抖。

接着，我想出了办法：

# 二分答案（思想错误并不可行）

## 此处是错误的想法的分析，希望大家以后做题可以避免

我怕 $r$ 开始出现一堆 $x$，所以**二分**应该可以避免问题并不超时。

事实上这是**错误**的，区间并**未排序**，违背了**二分答案**的算法，但因为我没想起所以会出现巨大的问题。

然后我做完测试时，发现了一个致命缺点:会查到重复的值然后出错。

演示一下：

$x=4$

$a=444414$

查到中间是 $4$，又向左查，无果。最后返回 $-1$。

所以它是会错的。

# 正确解法和思路

### 简单理解：

再开一个数组 $b$，$b[i]$ 是 $a[i]$ **连续出现时 $a[i]$ 和第一次出现 $a[i]$ 的下标的距离**。
演示一下，如:

$x=1$

$a=2 2 2 2 3 1 1 1$

$b=0 1 2 3 0 0 1 2$

如果 $x==a[r]$ 的话。

他就会判断 $r-b[r]-1$ 的值是否超界，超界直接输出 $-1$。

输出 $r-b[r]-1$ 的值，这个数就不会是重复的数了。

如果 $x!=a[r]$ 就不用找输出 $r$ 就可以了。

# 挑战最短AC代码

变量名有更改，请注意分辨。

```cpp
#include <bits/stdc++.h>
using namespace std;
int l,r,x,a,b,ns[2000500],ss[2000500];
int main()
{
	scanf("%d %d",&a,&b);
	for(int i=1;i<=a;i++){
		scanf("%d",&ns[i]);
		if(i!=1&&ns[i-1]==ns[i])ss[i]=ss[i-1]+1;
		else ss[i]=0;
	}
	for(int i=1;i<=b;i++){
		scanf("%d %d %d",&l,&r,&x);
		if(ns[r]!=x)cout<<r<<endl;
		else {
			if(r-ss[r]-1>=l)cout<<r-ss[r]-1<<endl;
			else cout<<-1<<endl;
		}
	}
    return 0;
}
```

题解就到这了，本人是一个语文不太好的初中生，这是我的第一篇题解，写了整整三个小时，希望管理员通过。

题解如有错误，望请各位斧正。

感谢各位耐心看完。

---

## 作者：S__X (赞：1)

## 题意：
给你一个序列，求 $[l,r]$ 区间中不等于 $x[i]$ 的位置。

## 思路：
-  ### 预处理
用一个下标数组 $p_i$ 表示第一个与 $p_i$ 相同的数的下标。

例如 $1\ 2\ 1\ 1\ 3\ 5$，其下标数组即为 $1\ 2\ 3\ 3\ 4\ 5$。

```cpp
a[i]==a[i-1]?p[i]=p[i-1]:p[i]=i;
```

- ### 判断—输出
每次输入 $l\ r\ x$ 时，因为要求下标最大的，所以下标从最高位 $r$ 开始判断，分为两种情况：

- $a_r\neq x$ 直接输出 $a_r$；
- $a_r=x$ 如果 $p_r$ 不在 $[l,r]$ 中，直接输出 $-1$；如果 $p_r$ 在区间范围里，则输出 $p_r-1$，表示最后一个与 $x$ 不相等的数的下标。

## code:
本题最短代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[9000005],p[9000005],l,r,x;
int main(){
	scanf("%d%d",&n,&m)
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		a[i]==a[i-1]?p[i]=p[i-1]:p[i]=i;
	}
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d",&l,&r,&x);
		a[r]==x?(p[r]<=l?printf("-1\n"):printf("%d\n",p[r]-1)):(printf("%d\n",r));
	}
	return 0;
}
```

---

## 作者：_liuyi_ (赞：0)

# 思路
纪念今年 $S$ T2没想出来，其实这题跟今年 $S$ T2差不多，都是维护一下失配指针，然后暴力去跳，用 $nxt_i$ 表示下一个和 $a_i$ 不相等的数的下标，容易得到递推式 $nxt_i=nxt_{nxt_i}(a_i=a_{nxt_i})$，然后从 $l$ 开始跳，然后如果没跳出 $r$，就是合法的。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define fi first
#define se second
#define pb push_back
#define mem(a,x) memset(a,x,sizeof(a))
#define all(x) x.begin(),x.end()
#define lisan(x) {sort(all(x));x.erase(unique(all(x)),x.end());}
#define SZ(x) ((int)((x).size()))
#define debug(x) cout<<#x<<"="<<x<<"\n";
#define ti (db)((db)clock() / CLOCKS_PER_SEC)
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef unsigned long long ull;
typedef	double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
const int N=2e5+10,M=1e6+10;
const int mod=1e9+7;
//const int mod=998244353;
int n,m,a[N],nxt[N];
inline void solve(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]); 
	per(i,1,n){
		nxt[i]=i+1;
		while(nxt[i]<=n&&a[nxt[i]]==a[i]) nxt[i]=nxt[nxt[i]];
		cmin(nxt[i],n+1);
	}
	rep(i,1,m){
		int l,r,x,now;
		scanf("%d%d%d",&l,&r,&x);
		now=l;
		while(now<=r&&a[now]==x) now=nxt[now];
		printf("%d\n",now>r?-1:now);
	}
}
int main(){
	int T=1;
	//scanf("%d",&T);
	while(T--) solve();
}
```


---

## 作者：linbaicheng2022 (赞：0)

# Not Equal on a Segment 题解

## 题意

给定长度为 $n$ 的序列和 $m$ 个询问，每次在 $l$ 到 $r$ 范围内找到下标最大的不等于 $x$ 的元素的位置，如果没有，输出 $-1$。

[题目传送门](https://www.luogu.com.cn/problem/CF622C)

## 思路

我们将序列分成若干个块，每个块内元素值相同。用 $blog$ 数组存储每个元素块的第一个元素的位置。

然后对于每组询问 $l, r, x$，首先分出两种情况讨论：

+ 1.$a_r \not= x$，不用找，直接输出 $r$ 即可；

+ 2.$a_r = x$，那么就看 $r$ 这个块第一次出现的位置是否在 $l$ 前，如果是，则说明整个 $l$ 到 $r$ 的区间都属于一个块，且块内元素均为 $x$，输出 $-1$，反之，就输出这个块起点的前一个位置即可。

## 代码：

注意本题数据范围较大，记得写 scanf 和 printf 输入输出。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
		
using namespace std;
		
const int N = 200010;
int n, m, a[N], blog[N];
		
void init () { //初始化每个块
	for (int i = 1; i <= n; i ++) {
		if (a[i] == a[i - 1]) { //如果和上一个元素一样，就把它接到上一个块
			blog[i] = blog[i - 1];
		} else { //否则，将其作为一个新块的起点
			blog[i] = i;
		}
	}
}
		
int main () {
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++)
		scanf ("%d", &a[i]);
	
	init ();
	
	while (m --) {
		int l, r, x;
		scanf ("%d%d%d", &l, &r, &x);
		
		if (a[r] == x) {
			if (blog[r] <= l) {
				printf ("%d\n", -1);
			} else {
				printf ("%d\n", blog[r] - 1);
			}
		} else {
			printf ("%d\n", r);
		}
	}
	
	return 0;
}
```

---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF622C)
## 题意：
给定一个有 $n$ 个整数和 $m$ 个查询的 $A$ 数组。每个查询是三个整数 $l$，$r$，$x$。对于每个查询，查找任何位置 $y$（$l \leq y \leq r$），如果 $a_y \ne x[i]$，则此 $y$ 符合条件，输出最大符合条件的 $y$，如果没有符合条件的 $y$，则输出 $-1$。
## 思路：
用 $p$ 数组记录第一个与自己相同的数的下标。连续是最前面一个与自己相同的数的下标，不连续是自己的下标。

每次输入 $l,r,x$ 时，因为要求下标最大的，所以从下标最大的 $r$ 开始考虑，分为两种情况：

1.$a_r \ne x$

满足要求,直接输出 $r$。

2.$a_r = x$

如果 $p_r$ 不在区间范围里，直接输出 $-1$；如果 $p_r$ 在区间范围里，则输出 $p_r-1$，表示最后面一个与 $r$ 不相等的数的下标。
## Code:
```cpp
//非洛谷题_CodeForces_CF622C_Not Equal on a Segment
#include<bits/stdc++.h>
#pragma /*G++*/GCC optimize(2)//O2
#pragma /*G++*/GCC optimize(3)//O3
long long n=0,m=0,a[1919810]={},l=0,r=0,x=0,p[1919810]={}/*用来记录第一个与自己相同的数的下标。*/;
using namespace std;
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//cin加速 
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	if(a[i]==a[i-1]){//连续时p[i]保存最前面一个与自己相同的数的下标
            p[i]=p[i-1];
        }
        else{//不连续p[i]保存自己
		    p[i]=i;
		}
	}
	while(m--){
		cin>>l>>r>>x;
		if(a[r]==x){//如果自己不满足≠x
		    if(p[r]<=l){//l和r可能会相等，若改为<样例第一组询问不对
			    cout<<"-1\n";
		    }else{//p[r]肯定是第一个与r相同的数字的坐标，所以p[r]-1就是最后一个与r不相同的元素下标了
			    cout<<p[r]-1<<"\n";
			}
		}else{//自己满足条件就输出
		    cout<<r<<"\n";
		}
	}
    return 0;
}
```

---

## 作者：yutong_Seafloor (赞：0)

# [题目在这里 · CF622C Not Equal on a Segment ](https://www.luogu.com.cn/problem/CF622C) 

### 题目简要：
给你一个长 $n$ 的数组和 $m$ 次询问，每次询问给一个区间 $[l,r]$ 和一个数 $x$，求 $[l,r]$ 区间中有没有一个数 $a_y$，使得 $a_y \ne x$，有输出该数下标 $y$，没有则输出 $-1$。

------------
### 题意分析

在这里 $l$ 数组存第一个与自己相同的数的下标。

考虑到 $a_y \ne x$ 成不成立，成立的话直接输出 $y$ 即可，不成立则属于一下即第二种情况。

如果属于第二种情况，我们先用 $r_i$ 记录第 $i$ 个数右边连续等于 $a_{i}$ 的数的最右边的数的下标，然后判断 $r_l+1 \le r$ 是否成立，成立则输出 $r_l+1$，不然就是不存在的，即指 $[l,r]$ 区间都是连续的 $x$，输出 $-1$。

------------


但是此题有一个坑：

看到那个时间限制了吗，~~经过大量的 TLE~~，发现它不能用 `cin`，需要使用 `scanf` 读入才可以。

------------
## 代码 
```cpp 
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200010],r[200010],l[200010],i,l1,r1,x;
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
    	scanf("%d",&a[i]);
    	l[i]=r[i]=i;
	}
    for(i=2;i<=n;i++)
    if(a[i-1]==a[i])//l存第一个与自己相同的数的下标
	l[i]=l[i-1],r[l[i]]=i;
    for(i=1;i<=m;i++)
	{
        scanf("%d%d%d",&l1,&r1,&x);
        if(a[l1]!=x)
		cout<<l1<<"\n";
        else 
		if(r[l[l1]]+1<=r1)
		cout<<r[l[l1]]+1<<"\n";
        else
		cout<<"-1\n";
    }
    return 0;
}//by·yutong_Seafloor
```

---

## 作者：pengzy (赞：0)

### 题意：

给你两个数 $n,m$ $(1\le n,m\le 2\times 10^{5})$ 和一个长度为 $n$ 的数列 $a$。对于每一组询问有三个数 $L,R,x$，要你求出区间 $L,R$ 中与 $x$ 不相同的数的下标（包括 $L,R$ ）。若有多个，输出下标 **最大** 的；若没有，输出 $-1$。

### 思路：

考虑用数组来维护。用 $p$ 数组记录第一个 **与自己相同的数的下标** 。

预处理 $p$ 数组代码：
```cpp
//此处的 a[i] 是输入的 a 数组元素
if(a[i]==a[i-1])//p[i] 表示最前面一个连续与自己相同的数的下标
    p[i]=p[i-1];
else p[i]=i;//不连续就是自己
```


每次输入 $L,R,x$ 时，因为要求下标最大的，所以从下标最大的 $R$ 开始考虑，分为两种情况：

1. $a_{R}≠x$

满足要求，直接输出 $R$。

2. $a_{R}=x$

如果 $p_{R}$ 不在区间范围里，直接输出 $-1$ ；如果 $p_{R}$ 在区间范围里，则输出 $p_{R}-1$，表示最后面一个与 $R$ 不相等的数的下标。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
const int MAX=2e5+5;
int n,m,a[MAX],p[MAX];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) {
		a[i]=read();
		//记录第一个与自己相同的数的坐标
		if(a[i]==a[i-1])p[i]=p[i-1];//前数若相同则记录最早一个相同的坐标
		else p[i]=i;//否则记录自己
	}
	for(int i=1,L,R,x;i<=m;i++) {
		L=read(),R=read(),x=read();
		if(a[R]==x)//如果自己不满足≠x
		    if(p[R]<=L)cout<<-1<<endl;//L 和 R 可能会相等，若改为 < 样例第一组询问不对
		    else cout<<p[R]-1<<endl;//p[R] 肯定是第一个与 R 相同的数字的坐标，所以 p[R]-1 就是最后一个与 R 不相同的元素下标了
		else cout<<R<<endl;//自己满足条件就输出
	}
	return 0;
}
```

代码怕超时采用了快读。

若有不理解的可以在下方评论，我一定会回复。

---

## 作者：hxhhxh (赞：0)

## 大意

给定一个长度为 $ n $ 的数组和 $ m $ 次询问，每次询问指定一个区间 $ [l,r] $ 和一个正整数 $ x $ ，求 $ [l,r] $ 区间中任意一个数 $ t $ ，使得 $ a_t \neq x $ 或者说不存在。

## 思路

首先，如果 $ a_l \neq x $ ，那也没有必要找别的数，直接输出 $ l $ 即可。

如果 $ a_l = x $ ，那么可以找右边的第一个不等于 $ x $ 的数。

令 $ s_i $ 表示第 $ i $ 个数右边连续的等于 $ a_{s_i} $ 的数的最右端下标。 $ s $ 数组可以 $ O(n) $ 算出来。代码里 $ s_i = r_{l_i} $ 

因为 $ a_l = x $ ，所以 $ a_{s_l+1} \neq x $ 。如果 $ s_l + 1 > r $ ，就说明 $ [l,r] $ 是连续的 $ x $ ，答案不存在；否则输出 $ s_l + 1 $ 。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200005],r[200005],l[200005];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) l[i]=r[i]=i;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=2;i<=n;i++){
    	if(a[i-1]==a[i]){
			l[i]=l[i-1];
    		r[l[i]]=i;
		}
	}
    for(int i=1,j,k,x;i<=m;i++){
        scanf("%d %d %d",&j,&k,&x);
        if(a[j]!=x) printf("%d\n",j);
        else if(r[l[j]]+1<=k) printf("%d\n",r[l[j]]+1);
        else printf("-1\n");
    }
    return 0;
}
```

---

## 作者：HMZHMZHMZ (赞：0)

### 题意

给定 $ n $ 个数，$ m $ 次询问，每一次查询提供 $ 3 $ 个参数 $ l,r,x $，询问 $ l,r $ 区间内是否存在一个数不等于 $ x $。

### 思路

对于这种区间问题，线段树一般都能解决。

我们对于这个序列建一棵线段树，维护区间的最大值最小值以及他们的坐标。

那么有了这些值，我们只需判断最大值和最小值是否都等于 $ x $ 即可。

时间复杂度 $ O(n \log n ) $。

### 代码

```cpp

#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb(x) push_back(x)
using namespace std;
const int N=2e5+10;
struct node{
	int l,r,maxn,minn,maxid,minid;
}tree[N<<2];
struct point{
	int x,id;
};
int n,m,T,a[N],l,r,x;
inline int read(){
	int s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
void build(int i,int l,int r){
	tree[i].l=l,tree[i].r=r;
	if(l<r){
		int mid=(l+r)>>1;
		build(i<<1,l,mid);
		build(i<<1|1,mid+1,r);
		if(tree[i<<1].maxn>tree[i<<1|1].maxn) tree[i].maxn=tree[i<<1].maxn,tree[i].maxid=tree[i<<1].maxid;
		else tree[i].maxn=tree[i<<1|1].maxn,tree[i].maxid=tree[i<<1|1].maxid;
		if(tree[i<<1].minn<tree[i<<1|1].minn) tree[i].minn=tree[i<<1].minn,tree[i].minid=tree[i<<1].minid;
		else tree[i].minn=tree[i<<1|1].minn,tree[i].minid=tree[i<<1|1].minid;
	}else tree[i].maxn=tree[i].minn=a[l],tree[i].maxid=tree[i].minid=l;
}
point sum_max(int i,int l,int r){
	if(tree[i].l==l&&tree[i].r==r) return (point){tree[i].maxn,tree[i].maxid};
	int mid=(tree[i].l+tree[i].r)>>1;
	if(r<=mid) return sum_max(i<<1,l,r);
	else if(l>mid) return sum_max(i<<1|1,l,r);
	else{
		point p1=sum_max(i<<1,l,mid),p2=sum_max(i<<1|1,mid+1,r);
		if(p1.x>p2.x) return p1;
		else return p2;
	}
}
point sum_min(int i,int l,int r){
	if(tree[i].l==l&&tree[i].r==r) return (point){tree[i].minn,tree[i].minid};
	int mid=(tree[i].l+tree[i].r)>>1;
	if(r<=mid) return sum_min(i<<1,l,r);
	else if(l>mid) return sum_min(i<<1|1,l,r);
	else{
		point p1=sum_min(i<<1,l,mid),p2=sum_min(i<<1|1,mid+1,r);
		if(p1.x<p2.x) return p1;
		else return p2;
	}
}
int main(){
	n=read(),T=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	build(1,1,n);
	while(T--){
		l=read(),r=read(),x=read();
		point p=sum_max(1,l,r),q=sum_min(1,l,r);
		if(p.x==x&&q.x==x) printf("-1\n");
		else printf("%d\n",p.x==x?q.id:p.id);
	}
	return 0;
}

```

---

## 作者：HDWR (赞：0)

有一个性质：$a \geq b$ 且 $a \leq b \Leftrightarrow a = b$

所以我们需要维护一个区间最小值 $\mathrm{minn}$ 和区间最大值 $\mathrm{maxn}$，如果 $\mathrm{minn} = \mathrm{maxn} = x$ 即是无解。

这题还让我们随便输出一个不等于 $x$ 的数的位置，既然 $\mathrm{maxn}, \mathrm{minn}$ 至少有一个不等于 $x$，那我们只需要输出那个数的位置就好了。

做法也很简单，使用线段树维护四个信息：区间最大值、最小值和区间最大值、最小值所在的位置。挺好写的。

时间复杂度 $O(n \log n)$。

```cpp
const int MAXN = 2e5 + 10;

int n, m;
int aa[MAXN];

namespace Segt {
    struct Node {
        int minn, maxn;
        int minp, maxp;
        Node() {minn = maxn = minp = maxp = 0;}
    } segt[MAXN << 2];

    #define ls (p << 1)
    #define rs (p << 1 | 1)

    Node Merge(Node pl, Node pr) {
        Node ret;
        if (pl.minn < pr.minn) { ret.minn = pl.minn; ret.minp = pl.minp; } 
        else { ret.minn = pr.minn; ret.minp = pr.minp; }
        if (pl.maxn > pr.maxn) { ret.maxn = pl.maxn; ret.maxp = pl.maxp; } 
        else { ret.maxn = pr.maxn; ret.maxp = pr.maxp; }
        return ret;
    }
    void Update(int p) {
        segt[p] = Merge(segt[ls], segt[rs]);
    }
    void buildTree(int p, int l, int r, int *aa) {
        if (l == r) {
            segt[p].minn = segt[p].maxn = aa[l];
            segt[p].minp = segt[p].maxp = l;
            return;
        } int mid = (l + r) >> 1;
        buildTree(ls, l, mid, aa); buildTree(rs, mid + 1, r, aa);
        Update(p);
    }
    Node Query(int p, int l, int r, int ll, int rr) {
        if (l == ll && rr == r) return segt[p];
        int mid = (l + r) >> 1;
        if (rr <= mid) return Query(ls, l, mid, ll, rr);
        else if (mid + 1 <= ll) return Query(rs, mid + 1, r, ll, rr);
        else return Merge(Query(ls, l, mid, ll, mid), Query(rs, mid + 1, r, mid + 1, rr));
    }
}

int main() {
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    rep (i, 1, n) cin >> aa[i];
    Segt::buildTree(1, 1, n, aa);
    rep (i, 1, m) {
        int l, r, x; cin >> l >> r >> x;
        Segt::Node res = Segt::Query(1, 1, n, l, r);
        if (res.minn == x && res.maxn == x) puts("-1");
        else {
            if (res.minn == x) printf("%d\n", res.maxp);
            else printf("%d\n", res.minp);
        }
    }
    return 0;
}
```

---

## 作者：zzx114514 (赞：0)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/wuxianbianjiang/solution-cf622c)
## 题目大意
给定长度为 $n$ 的数组 $a$，询问 $m$ 次，每次给出 $l,r,x$，其中 $l,r$ 表示左右区间，$x$ 表示查询区间中是否有不等于 $x$ 的元素，有的话输出任意一个的下标，否则输出 `-1`。
## 解题思路
发现 $1 \le n,m \le 2\times10^5$，$O(n^2)$ 暴力显然不行，可以考虑预处理。先预处理出数组中每一段相同区间的第一个下标，$O(1)$ 查询，具体看代码。
## 完整代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,a[200005],pos[200005],l,r,x; 
int main()
{
	scanf("%d %d",&n,&m);//输入要快，否则会超时 
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
		if (a[i]==a[i-1]) pos[i]=pos[i-1];//预处理每一段相同区间的第一个下标，存在pos数组中 
		else pos[i]=i;
	for (int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&l,&r,&x);
		printf("%d\n",(a[r]==x?(pos[r]<=l?-1:pos[r]-1):r));//查询，具体见下面分析 
	}
	return 0;
}

```
注意到代码中有一段非常复杂的三目运算，~~那是我为了压行，~~接下来细讲。  
```cpp
a[r]==x?(pos[r]<=l?-1:pos[r]-1):r
```
为了方便观察，将其拆开，分析看代码。
```cpp
if (a[r]==x)//如果右端点等于x
{
	if (pos[r]<=l) cout<<-1<<endl;//如果第一个不等于x的数在左区间之外，说明区间内全部等于x，输出-1
	else cout<<pos[r]-1<<endl;//否则输出这一段相同区间的上一个数，一定不等于x，且在左右区间内
}
else cout<<r<<endl;//否则直接输出右端点下标即可
```
撒花！

---

## 作者：t162 (赞：0)

这里说一个简单的思路。

我们可以寻找出限定区间内的最大值和最小值，记为 $a_i,b_i$。

下面分类考虑：

- $a_i=b_i=x_i$ 输出 `-1` 即可。这是显然的。
- 其余情况，输出 $a_i,b_i$ 中任意一个不等于 $x_i$ 的数，直接输出即可。这也是显然的。

于是问题转化成了 RMQ。

$O(n\log n)$ 建立两个 ST 表， $O(1)$ 查询即可。

```cpp
//This code was made by Bambusoideae
#include<cstdio>
#include<algorithm>
long long a[500001],n,m,l,r,x,lg[500001],st[2][500001][20];
long long b(int t,int l,int r){
    int bit=lg[r-l+1];
    if(t)return a[st[1][l][bit]]<a[st[1][r-(1<<bit)+1][bit]]?st[1][r-(1<<bit)+1][bit]:st[1][l][bit];
    return a[st[0][l][bit]]>a[st[0][r-(1<<bit)+1][bit]]?st[0][r-(1<<bit)+1][bit]:st[0][l][bit];
}
int main(){
    lg[1]=0;
    for(int i=2;i<500001;i++)lg[i]=lg[i>>1]+1;
    scanf("%lld%lld",&n,&m);for(int i=1;i<=n;i++)scanf("%lld",a+i),st[0][i][0]=st[1][i][0]=i;
    for(int i=1;i<=lg[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)
    st[0][j][i]=a[st[0][j][i-1]]<a[st[0][j+(1<<(i-1))][i-1]]?st[0][j][i-1]:st[0][j+(1<<(i-1))][i-1],
    st[1][j][i]=a[st[1][j][i-1]]>a[st[1][j+(1<<(i-1))][i-1]]?st[1][j][i-1]:st[1][j+(1<<(i-1))][i-1];
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&l,&r,&x);
        int lar=b(1,l,r),sma=b(0,l,r);
        if(a[lar]==a[sma]&&a[lar]==x)puts("-1");
        else printf("%d\n",a[lar]==x?sma:lar);
    }
}
```

---

