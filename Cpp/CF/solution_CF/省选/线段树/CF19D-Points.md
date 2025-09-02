# Points

## 题目描述

Pete and Bob invented a new interesting game. Bob takes a sheet of paper and locates a Cartesian coordinate system on it as follows: point $ (0,0) $ is located in the bottom-left corner, $ Ox $ axis is directed right, $ Oy $ axis is directed up. Pete gives Bob requests of three types:

- add x y — on the sheet of paper Bob marks a point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is not yet marked on Bob's sheet at the time of the request.
- remove x y — on the sheet of paper Bob erases the previously marked point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is already marked on Bob's sheet at the time of the request.
- find x y — on the sheet of paper Bob finds all the marked points, lying strictly above and strictly to the right of point $ (x,y) $ . Among these points Bob chooses the leftmost one, if it is not unique, he chooses the bottommost one, and gives its coordinates to Pete.

Bob managed to answer the requests, when they were 10, 100 or 1000, but when their amount grew up to $ 2·10^{5} $ , Bob failed to cope. Now he needs a program that will answer all Pete's requests. Help Bob, please!

## 样例 #1

### 输入

```
7
add 1 1
add 3 4
find 0 0
remove 1 1
find 0 0
add 1 1
find 0 0
```

### 输出

```
1 1
3 4
1 1
```

## 样例 #2

### 输入

```
13
add 5 5
add 5 6
add 5 7
add 6 5
add 6 6
add 6 7
add 7 5
add 7 6
add 7 7
find 6 6
remove 7 7
find 6 6
find 4 4
```

### 输出

```
7 7
-1
5 5
```

# 题解

## 作者：_Anchor (赞：19)

## Problem

题目已经说的很清楚了，只不过还有要注意的就是这个“右上方”指的是严格大于，也就是 $x_1>x_2$，$y_1>y_2$ 。

## Solution

首先看到值域的数据范围我们可以想到先离散化一下。

然后我们考虑用线段树维护横坐标为 $1,2,3,4...$ 时的纵坐标最大值。（也就是每一个横坐标上的最大纵坐标，在这个基础上线段树维护最大值。）

对于每一个横坐标可以开一个 set 维护这个坐标内部的点。

那么题目上的操作就很好实现了，添加操作就是先看看可不可以取代当前的那个位置上的最大值，然后再插入进 set 里。

删除操作就是先在对应横坐标的 set 里删除，然后再用当前 set 里的最大值放进线段树里，覆盖掉原来的那个。

最后 查找操作就是先在线段树上二分，找到最左边的，且横坐标大于 $x$ ，值大于 $y$ 的位置。

（注意这里的值指的是线段树维护的那个 Max ，因为我们这里只是看在这个坐标上有没有解，至于题目要求的还要 $y$ 尽可能小，我们一会先定位横坐标，再在这个横坐标的 set 上找。）

于是我们再在这个位置上的 set 当中二分找到第一个大于 $y$ 的值，再映射回原数组（因为离散化了的），就是答案了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return ;
}
const int N=4e5+5; 
#define ll long long
struct Query{int op,x,y;}Q[N];
int n,m,b[N],cnt,Max[N<<2];
set<int> ST[N];
void Pushup(int x){Max[x]=max(Max[x<<1],Max[x<<1|1]);return ;}
void Modify(int x,int l,int r,int pos,int v){
    if(l==r){Max[x]=max(Max[x],v);return ;}
    int mid=l+r>>1;
    if(pos<=mid) Modify(x<<1,l,mid,pos,v);
    else Modify(x<<1|1,mid+1,r,pos,v);
    Pushup(x);
    return ;
} 
void Change(int x,int l,int r,int pos,int v){
    if(l==r){Max[x]=v;return ;}
    int mid=l+r>>1;
    if(pos<=mid) Change(x<<1,l,mid,pos,v);
    else Change(x<<1|1,mid+1,r,pos,v);
    Pushup(x);
    return ;
} 
int QueryPos(int x,int l,int r,int X,int Y){
    if(l==r){
        if(Max[x]>Y) return l;
        return -1;
    }
    int mid=l+r>>1,res=-1;
    if(X<=mid&&Max[x<<1]>Y) res=QueryPos(x<<1,l,mid,X,Y);
    if(~res) return res;
    if(Max[x<<1|1]>Y) return QueryPos(x<<1|1,mid+1,r,X,Y); 
    return -1;
}
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        char op[10];int x,y;
        scanf("%s",op);read(x),read(y);
        if(op[0]=='a') Q[i].op=1,Q[i].x=x,Q[i].y=y; 
        else if(op[0]=='r') Q[i].op=2,Q[i].x=x,Q[i].y=y; 
        else Q[i].op=3,Q[i].x=x,Q[i].y=y; 
        b[++cnt]=x,b[++cnt]=y;
    }
    sort(b+1,b+cnt+1);
    int idx=unique(b+1,b+cnt+1)-b-1;
    for(int i=1;i<=n;i++) Q[i].x=lower_bound(b+1,b+idx+1,Q[i].x)-b,Q[i].y=lower_bound(b+1,b+idx+1,Q[i].y)-b;
    for(int i=1;i<=n;i++){
        if(Q[i].op==1) ST[Q[i].x].insert(Q[i].y),Modify(1,1,idx,Q[i].x,Q[i].y);
        else if(Q[i].op==2){
        	ST[Q[i].x].erase(ST[Q[i].x].find(Q[i].y));
        	if(ST[Q[i].x].empty()){
        		Change(1,1,idx,Q[i].x,0);
        		continue;
        	}
        	Change(1,1,idx,Q[i].x,*ST[Q[i].x].rbegin());
        }
        else{
            int Pos=QueryPos(1,1,idx,Q[i].x+1,Q[i].y);
            if(Pos==-1) puts("-1");
            else write(b[Pos]),putchar(' '),write(b[*ST[Pos].upper_bound(Q[i].y)]),putchar('\n');
        }
    }
    return 0;
}
```


---

## 作者：mrsrz (赞：10)

~~写了半天的树套树被卡空间~~

线段树+set即可。

首先显然要离线下来，然后离散化一下。

对每个$x$，开一个对应的set，存横坐标为$x$的点的所有纵坐标。

对于一个询问$x,y$，我们要找到在$x$右边的、最大纵坐标大于$y$的、最左边的列$x'$。

用线段树维护一段横坐标区间内，纵坐标最大值。

然后找满足条件的横坐标$x'$的时候，直接在线段树上二分即可。最小的纵坐标则直接在相应的set里lower_bound即可。

对于修改操作，在线段树上和对应的set里直接修改即可。

时间复杂度$O(n\log n)$。

## Code：
```cpp
#include<cstdio>
#include<algorithm>
#include<set> 
#include<vector>
#define N 200005
struct istream{
	template<typename T>
	inline istream&operator>>(T&d){
		static int c;
		while(!isdigit(c=getchar()));
		for(d=0;isdigit(c);c=getchar())
		d=(d<<3)+(d<<1)+(c^'0');
		return*this;
	}
}cin;
int n;
std::vector<int>X,Y;
struct cmd{
	char opt[7];
	int x,y;
}q[N];
int d[N<<2];
std::set<int>b[N]; 
void modify(int l,int r,int o,const int&pos,const int&ch){
	if(l==r)d[o]=ch;else{
		const int mid=l+r>>1;
		if(pos<=mid)modify(l,mid,o<<1,pos,ch);else
		modify(mid+1,r,o<<1|1,pos,ch);
		d[o]=std::max(d[o<<1],d[o<<1|1]);
	}
}
void query(int l,int r,int o,const int&X,const int&Y,int&x){
	if(l==r){
		if(d[o]>=Y)
		x=l;return;
	}
	const int mid=l+r>>1;
	if(X<=mid&&d[o<<1]>=Y)query(l,mid,o<<1,X,Y,x);
	if(~x)return;
	if(d[o<<1|1]>=Y)query(mid+1,r,o<<1|1,X,Y,x);
}
void build(int l,int r,int o){
	d[o]=-1;
	if(l<r){
		const int mid=l+r>>1;
		build(l,mid,o<<1),build(mid+1,r,o<<1|1);
	}
}
int main(){
	X.push_back(-1),Y.push_back(-1);
	cin>>n;
	build(1,n,1);
	for(int i=1;i<=n;++i){
		scanf("%s",q[i].opt);cin>>q[i].x>>q[i].y;
		if(*q[i].opt=='f')++q[i].x,++q[i].y;
		X.push_back(q[i].x),Y.push_back(q[i].y);
		b[i].insert(-1);
	}
	std::sort(X.begin(),X.end());
	std::sort(Y.begin(),Y.end());
	X.erase(std::unique(X.begin(),X.end()),X.end());
	Y.erase(std::unique(Y.begin(),Y.end()),Y.end());
	for(int i=1;i<=n;++i){
		q[i].x=std::lower_bound(X.begin(),X.end(),q[i].x)-X.begin();
		q[i].y=std::lower_bound(Y.begin(),Y.end(),q[i].y)-Y.begin();
		if(*q[i].opt=='a'){
			int mx=*b[q[i].x].rbegin();
			if(mx<q[i].y)modify(1,n,1,q[i].x,q[i].y);
			b[q[i].x].insert(q[i].y);
		}else
		if(*q[i].opt=='r'){
			b[q[i].x].erase(b[q[i].x].find(q[i].y));
			modify(1,n,1,q[i].x,*b[q[i].x].rbegin());
		}else{
			int x=-1;
			query(1,n,1,q[i].x,q[i].y,x);
			if(x==-1)puts("-1");else
			printf("%d %d\n",X[x],Y[*b[x].lower_bound(q[i].y)]);
		}
	}
	return 0;
}
```

---

## 作者：resftlmuttmotw (赞：7)


## $Firstly$,离散
坐标范围太大

考虑离散化

## $Secondly$,线段树

**在一个笛卡尔坐标系中，定义三种操作:**

由题意的这句话非常容易想到这是一道数据结构题

$1<=n<=2⋅10^5$$\Rightarrow$最多有$2⋅10^5$个横坐标

针对每一个$x_i$对应的${y_i}_{max}$我们用线段树来维护

> 3.find x y :找到所有已标记并在（x，y）右上方的点中,最左边的点，若点不唯一,选择最下面的一个点; 如果没有符合要求的点,给出"-1",否则给出x y.

酱紫,我们可以再二分线段树$\Rightarrow$在$logn$的时间复杂度内完成操作$3$

操作$1$,$2$就只是更改某个$x$的${y_i}_{max}$$\Rightarrow$单点修改

## $Additionally$,$set$

也许你认为到这就可以了

但是你忽略了一点 : 操作$1$,$2$是否该更改

一些数据结构大神跳出来话说 针对每一个$x$上的$y$我们构建一个平衡树

支持插入,删除,维护最大值

其实 $set$就可以完全实现这些操作

## $Finally$

这道题有卡常倾向

线段树$+$平衡树貌似是过不了的

线段树$+$ $set$ $+$直接二分只能$A51$个点

线段树$+$ $set$ $+$线段树二分才能$AC$

## $Code$


$AC Code$
```cpp
#include <map>
#include <set>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register
const int MAXN = 2e5 + 10;
struct node {
	int sit,x,y;
	void assignedment(int SIT) {
		sit = SIT;
	}
};
int T,Right,seg[MAXN];
set<int> st[MAXN];
node option[MAXN];
map<string,int> mp;
map<int,int> past_x,past_y;
//记录以前的值  
namespace pre {
	pair<int,int> a[MAXN],b[MAXN];
	inline void init() {
		mp["add"] = 1,mp["find"] = 2,mp["remove"] = 3;
		scanf("%d",&T);
		for(reg int i = 1; i <= T; i++) {
			string sit;
			cin >> sit;
			int x,y;
			scanf("%d%d",&x,&y);
			a[i] = make_pair(x,i);
			b[i] = make_pair(y,i);
			option[i].assignedment(mp[sit]);
		}
	}
	inline void hash() {
		sort(a + 1,a + 1 + T);
		sort(b + 1,b + 1 + T);
		int va,vb;
		va = vb = 0;
		for(reg int i = 1; i <= T; i++) {
			if(i == 1||a[i].first > a[i - 1].first) va++;
			if(i == 1||b[i].first > b[i - 1].first) vb++;
			option[a[i].second].x = va;
			past_x[va] = a[i].first;
			past_y[vb] = b[i].first;
			option[b[i].second].y = vb;
		}
		Right = va;
	}
	//输入及离散化 
}
namespace segment {
	int tree[MAXN << 2];
	inline void change(int l,int r,int k,int pos,int x) {
		if(l == r&&l == pos) {
			tree[k] = x;
			return;
		}
		int mid = l + r >> 1;
		if(pos <= mid) change(l,mid,k << 1,pos,x);
		else change(mid + 1,r,k << 1 | 1,pos,x);
		tree[k] = max(tree[k << 1],tree[k << 1 | 1]);
	}
	inline int query(int l,int r,int k,int ql,int qr) {
		if(ql <= l&&r <= qr)
			return tree[k];
		int mid = l + r >> 1,k1,k2;
		k1 = k2 = -1;
		if(ql <= mid) k1 = query(l,mid,k << 1,ql,qr);
		if(qr > mid) k2 = query(mid + 1,r,k << 1 | 1,ql,qr);
		return max(k1,k2);
	}
	//线段树 
	inline int findans(int l,int r,int k,int pos,int x)
	{
		if(l == r) return l;
		int mid = l + r >> 1,k1,k2;
		k1 = k2 = Right + 1;
		if(pos < mid&&tree[k << 1] > x) k1 = findans(l,mid,k << 1,pos,x);
		if(k1 < Right + 1) return k1;
		//这一句必须加 不然T(左边已经找到了 没必要找右边的) 
		if(tree[k << 1 | 1] > x) k2 = findans(mid + 1,r,k << 1 | 1,pos,x);
		return min(k1,k2);
	}
	//线段树上的二分 
}
inline void solve() {
	for(reg int i = 1; i <= T; i++) {
		switch(option[i].sit) {
			case 1: {
				if(st[option[i].x].size() == 0)
					segment::change(1,Right,1,option[i].x,option[i].y);
				else {
					auto it = st[option[i].x].end();
					if(option[i].y > *(--it)) segment::change(1,Right,1,option[i].x,option[i].y);
				}
				st[option[i].x].insert(option[i].y);
				//加点 用set 
				break;
			}
			case 2: {
				int l = option[i].x + 1,r = Right;
				int res = segment::query(1,Right,1,l,r);
				if(res <= option[i].y) printf("-1\n");
				else {
					int j = segment::findans(1,Right,1,option[i].x,option[i].y);
					printf("%d %d\n",past_x[j],past_y[*(st[j].upper_bound(option[i].y))]);
				}
				//求答案 
				break;
			}
			case 3: {
				auto it = st[option[i].x].upper_bound(option[i].y);
				bool f = 0;
				if(it == st[option[i].x].end()) f = 1;
				st[option[i].x].erase((--it));
				if(f) {
					int pas;
					if(st[option[i].x].size() == 0)
						pas = 0;
					else {
						auto it = st[option[i].x].end();
						pas = *--it;
					}
					segment::change(1,Right,1,option[i].x,pas);
				}
				//删点 用set 
				break;
			}
		}
	}
}
int main() {
	pre::init();
	pre::hash();
	solve();
	return 0;
}
```
$Tle code$

```cpp
#include <map>
#include <set>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register
const int MAXN = 2e5 + 10;
struct node {
	int sit,x,y;
	void assignedment(int SIT) {
		sit = SIT;
	}
};
int T,Right,seg[MAXN];
set<int> st[MAXN];
node option[MAXN];
map<string,int> mp;
map<int,int> past_x,past_y;
namespace pre {
	pair<int,int> a[MAXN],b[MAXN];
	inline void init() {
		mp["add"] = 1,mp["find"] = 2,mp["remove"] = 3;
		scanf("%d",&T);
		for(reg int i = 1; i <= T; i++) {
			string sit;
			cin >> sit;
			int x,y;
			scanf("%d%d",&x,&y);
			a[i] = make_pair(x,i);
			b[i] = make_pair(y,i);
			option[i].assignedment(mp[sit]);
		}
	}
	inline void hash() {
		sort(a + 1,a + 1 + T);
		sort(b + 1,b + 1 + T);
		int va,vb;
		va = vb = 0;
		for(reg int i = 1; i <= T; i++) {
			if(i == 1||a[i].first > a[i - 1].first) va++;
			if(i == 1||b[i].first > b[i - 1].first) vb++;
			option[a[i].second].x = va;
			past_x[va] = a[i].first;
			past_y[vb] = b[i].first;
			option[b[i].second].y = vb;
		}
		Right = va;
	}
}
namespace segment {
	int tree[MAXN << 2];
	inline void change(int l,int r,int k,int pos,int x) {
		if(l == r&&l == pos) {
			tree[k] = x;
			return;
		}
		int mid = l + r >> 1;
		if(pos <= mid) change(l,mid,k << 1,pos,x);
		else change(mid + 1,r,k << 1 | 1,pos,x);
		tree[k] = max(tree[k << 1],tree[k << 1 | 1]);
	}
	inline int query(int l,int r,int k,int ql,int qr) {
		if(ql <= l&&r <= qr)
			return tree[k];
		int mid = l + r >> 1,k1,k2;
		k1 = k2 = -1;
		if(ql <= mid) k1 = query(l,mid,k << 1,ql,qr);
		if(qr > mid) k2 = query(mid + 1,r,k << 1 | 1,ql,qr);
		return max(k1,k2);
	}
}
inline void solve() {
	for(reg int i = 1; i <= T; i++) {
		switch(option[i].sit) {
			case 1: {
				if(st[option[i].x].size() == 0)
					segment::change(1,Right,1,option[i].x,option[i].y);
				else {
					auto it = st[option[i].x].end();
					if(option[i].y > *(--it)) segment::change(1,Right,1,option[i].x,option[i].y);
				}
				st[option[i].x].insert(option[i].y);
				break;
			}
			case 2: {
				int l = option[i].x + 1,r = Right;
				int res = segment::query(1,Right,1,l,r);
				if(res <= option[i].y) printf("-1\n");
				else {
					while(l < r) {
						int mid = l + r >> 1;
						int res = segment::query(1,Right,1,l,mid);
						if(res > option[i].y) r = mid;
						else l = mid + 1;
					}
					int j = l;
					printf("%d %d\n",past_x[j],past_y[*(st[j].upper_bound(option[i].y))]);
				}
                
                //与上面AC的代码不一样的只有这里 上面是在树上二分的 时间复杂度O(logn) 而这里直接二分+线段树求区间最大值O(log^2n)
				break;
			}
			case 3: {
				auto it = st[option[i].x].upper_bound(option[i].y);
				bool f = 0;
				if(it == st[option[i].x].end()) f = 1;
				st[option[i].x].erase((--it));
				if(f) {
					int pas;
					if(st[option[i].x].size() == 0)
						pas = 0;
					else {
						auto it = st[option[i].x].end();
						pas = *--it;
					}
					segment::change(1,Right,1,option[i].x,pas);
				}
				break;
			}
		}
	}
}
int main() {
	pre::init();
	pre::hash();
	solve();
	return 0;
}
```

---

## 作者：一扶苏一 (赞：5)

## Solution

$x,y$这么大，先给他离散化再说。

考虑一个笛卡尔坐标系上，对每个横坐标$x$任取**一个**$y$组成点$(x,y)$，是与一个数列$A$有一一对应关系的。即，点$(x,y)$对应序列$A_x=y$。

考虑对于一次查询，一列能做为答案的必要条件是这一列上$y$轴最大的点大于被查询的点的纵坐标。于是就想到将每个$x$对应的最大的$y$写入序列。于是每次查询时在序列上查询大于$x$的后缀上第一个大于$y$的位置的下标。这个显然可以用线段树搞定。考虑剩下的$y$怎么记录。使用线段树可以查询出应该被选择的横坐标。则纵坐标就是这一列上大于$y$的第一个数。于是对于每一列开一个$set$，维护这一列上所有的$y$，查询时直接upper_bound即可。

考虑线段树的写法。对于线段树的一个区间，维护这段区间中最大值的下标是多少。查询时，先递归查询左区间，如果左区间不合法则递归查询右区间。一个区间不合法当且仅当他与被查询的区间无交或他的最大值小于被查询的值$k$。

考虑这么做的复杂度：因为一个区间会被线段树划分成$O(log(len))$个线段。发现这些遍历这些线段是$O(log)$的，于是一次操作的复杂度是$O(log)$的。总复杂度$O(nlogn)$

## Code

```cpp
#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
#ifdef ONLINE_JUDGE
#define putchar(o)\
puts("I am a cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

template <typename T>
inline void qr(T &x) {
	rg char ch=getchar(),lst=' ';
	while((ch > '9') || (ch < '0')) lst=ch,ch=getchar();
	while((ch >= '0') && (ch <= '9')) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(lst == '-') x=-x;
}

namespace IO {
	char buf[120];
}

template <typename T>
inline void qw(T x,const char aft,const bool pt) {
	if(x < 0) {x=-x,putchar('-');}
	rg int top=0;
	do {IO::buf[++top]=x%10+'0';} while(x/=10);
	while(top) putchar(IO::buf[top--]);
	if(pt) putchar(aft);
}

template <typename T>
inline T mmax(const T a,const T b) {return a > b ? a : b;}
template <typename T>
inline T mmin(const T a,const T b) {return a < b ? a : b;}
template <typename T>
inline T mabs(const T a) {return a < 0 ? -a : a;}

template <typename T>
inline void mswap(T &_a,T &_b) {
	T _temp=_a;_a=_b;_b=_temp;
}

const int maxn = 200010;
const int maxt = 1600010;

struct M {
	int opt,x,y;
};
M MU[maxn];

int n,tcnt,num;
int temp[maxt],CU[maxt];
std::set<int>ss[maxt];

struct Tree {
	int v;
	inline void update(const Tree &_ls,const Tree _rs) {
		if(!(~(_ls.v))) this->v = _rs.v;
		else if(!(~(_rs.v))) this->v = _ls.v;
		else {
			if(CU[_ls.v] >= CU[_rs.v]) this->v=_ls.v;
			else this->v=_rs.v;
		}
	}
};
Tree tree[maxt];

void init_hash();
void change(ci,ci,ci,ci);
int ask(ci,ci,ci,ci,ci);

int main() {
	qr(n);
	for(rg int i=1;i<=n;++i) {
		M &now=MU[i];
		rg char ch=getchar();
		while((ch > 'z') || (ch < 'a')) ch=getchar();
		if(ch == 'a') now.opt=1;
		else if(ch == 'r') now.opt=3;
		else now.opt=2;
		qr(now.x);qr(now.y);
		temp[++tcnt]=now.x;temp[++tcnt]=now.y;
	}
	init_hash();
	memset(tree,-1,sizeof tree);
	for(rg int i=1;i<=n;++i) {
		M &now=MU[i];
		switch(now.opt) {
			case 1: {
				ss[now.x].insert(now.y);
				if(now.y == *(--ss[now.x].end())) {CU[now.x]=now.y;change(1,num,1,MU[i].x);}
				break;
			}
			case 2: {
				int k=ask(1,num,1,now.x+1,now.y);
				if(!(~k)) {puts("-1");break;}
				qw(temp[k],' ',true);
				std::set<int>::iterator zay = ss[k].upper_bound(now.y);
				qw(temp[*zay],'\n',true);
				break;
			}
			case 3: {
				if(now.y == *(--ss[now.x].end())) {
					ss[now.x].erase(now.y);
					if(ss[now.x].empty()) CU[now.x]=0;
					else CU[now.x]=*(--ss[now.x].end());
					change(1,num,1,MU[i].x);
				}
				else ss[now.x].erase(now.y);
				break;
			}
		}
	}
	return 0;
}

void init_hash() {
	std::sort(temp+1,temp+1+tcnt);s
	int *ed=std::unique(temp+1,temp+1+tcnt);
	num=ed-temp-1;
	for(rg int i=1;i<=n;++i) {
		MU[i].x=std::lower_bound(temp+1,ed,MU[i].x)-temp;
		MU[i].y=std::lower_bound(temp+1,ed,MU[i].y)-temp;
	}
}

void change(ci l,ci r,ci p,ci aim) {
	if(l > r) return;
	if((l > aim) || (r < aim)) return;
	if(l == r) {tree[p].v=l;return;}
	int mid=(l+r)>>1,dp=p<<1,ddp=dp|1;
	change(l,mid,dp,aim);change(mid+1,r,ddp,aim);
	tree[p].update(tree[dp],tree[ddp]);
}

int ask(ci l,ci r,ci p,ci aim,ci v) {
	if(l > r) return -1;
	if(r < aim) return -1;
	if(!(~(tree[p].v))) return -1;
	if(CU[tree[p].v] <= v) return -1;
	if(l == r) return tree[p].v;
	int mid=(l+r)>>1,dp=p<<1,ddp=dp|1;
	if(mid >= r) return ask(l,mid,dp,aim,v);
	else if(mid < l) return ask(mid+1,r,ddp,aim,v);
	else {
		int _ans;
		if(~(_ans=ask(l,mid,dp,aim,v))) return _ans;
		else return ask(mid+1,r,ddp,aim,v);
	}
}
```

## Solution

一个笛卡尔坐标系中对于每一个横坐标$x$选择一个纵坐标$y$后，可以将之一一对应到一个下标为$x$，值为$y$的线段上。利用这个性质可以将坐标问题改为序列修改问题使用数据结构处理。

---

## 作者：KobeBeanBryantCox (赞：3)

# CF19D Points 题解

---------------

[题目传送门](https://www.luogu.com.cn/problem/CF19D)。

大佬们都说线段树套平衡树过不了，但是怎么还没有**线段树套线段树**的做法呢？

Fun Fact：

原来我之前某次模拟赛做过这道原，当时我还不知道那是个原。然而我把之前的代码拿来提交发现居然过不了？结果是一个非常细节的错误，离散化的时候要 $-1$ 而不是 $+1$。看来模拟赛的数据还有待提高啊！

这是我之前模拟赛写的[线段树套 set](https://codeforces.com/problemset/submission/19/309196655)（当时写的线段树二分居然是非递归版的？），但是本题解不讲这种做法。

---------------

## 题意

此题题意简洁无废话，题意见题目描述。

需要注意的是，题目中指的右上方的点是严格右上方的。

--------------

## 思路

先想到的肯定是线段树套 set。

但是，~~为了显得与众不同一点~~，我偏要用线段树套线段树。

具体的，先把 $x$ 和 $y$ 两个都离散化。

开一颗动态开点权值线段树 $T$ 维护 $x$ 轴。

$T$ 中的每一个叶子结点开一颗动态开点权值线段树 $t$ 维护 $y$ 轴。

插入和删除就直接在对应位置操作即可，注意 $T$ 和 $t$ 都要维护区间个数和，然后 $T$ 要维护插入的 $y$ 的区间最大值来方便二分。

然后查询，我们令查询的是 $(X,Y)$ 右上角（注意大小写以便区分）。

先在 $T$ 中线段树二分找到区间 $[X+1,totx]$ 中第一个 $p$，满足 $p$ 位置存在点，且点的 $y$ 坐标最大值要大于 $Y$（若最大值都大于 $Y$，一定有点符合条件），这就是我们要维护最大值的原因。

然后在节点 $p$ 的 $t$ 中找到区间 $[Y+1,toty]$ 中最小的，这是普通的线段树二分。

这样就用两个线段树二分做完了。

时间复杂度 $O(n\log n)$，由于我们是找一个再找一个，并不是找一个过程中要找另一个，所以不是两只 $\log$ 相乘，而是相加。

注意空间。

-------------

## 一些细节

由于非严格，我们对于每一个查询的 $(X,Y)$，先让 $X$ 和 $Y$ 自增 $1$ 再操作。

由于自增了 $1$，此时 $X$ 和 $Y$ 有可能大于 $totx$ 或 $toty$，刚开始把离散化后的 $totx$ 和 $toty$ 也自增 $1$ 即可。

**再分享一下我的线段树二分的方法**，参考来自[此文](https://www.luogu.com.cn/article/qkpv0t0i)（侵权请联系删除），相较于普通的线段树二分，这样的好处是不用处理边界情况，而且遇到较为复杂的线段树二分也能处理。

考虑全局怎么做。直接维护区间和，然后判断左边是不是大于等于 $k$，是的话递归左边，否则右边。

然后考虑 $[l,r]$ 怎么做。先用一个 queue 按顺序存覆盖 $[l,r]$ 的线段树节点编号，共有 $\log n$ 个。

然后枚举这 $\log n$ 个节点，如果遇到某个区间第一个满足条件就递归进去，类似于全局一样查找即可，后面的直接 break 掉。

值得注意的是，queue 千万别写 list。

1. list 弹出元素会释放内存，但是速度慢。适合空间卡的紧的题目。
2. queue 弹出元素不会释放内存，删除时会释放，速度比 list 快。

   适合时间卡的紧的题目，但如果空间卡的紧就别用了，类似的题目有[这个](https://www.luogu.com.cn/article/tkja5bqn)。

我刚开始用 list 就 TLE 了，除了这一点，其余的都不需要卡常。

具体的一些细节看代码，有注释。

---------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
int in()
{
	int k=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=2e5+5;
int toty=0;
struct Seg_y
{
	struct node{int lc,rc,sum;}tr[N*35];
	#define lc tr[x].lc
	#define rc tr[x].rc
	void pushup(int x){tr[x].sum=tr[lc].sum+tr[rc].sum;}
	#define mid ((l+r)>>1)
	int cnt=0;
	void modify(int &x,int p,int v,int l=1,int r=toty)
	{
		if(!x)x=++cnt;
		if(l==r)return tr[x].sum+=v,void();
		if(p<=mid)modify(lc,p,v,l,mid);
		else modify(rc,p,v,mid+1,r);
		pushup(x);
	}
	int kth(int x,int k,int l=1,int r=toty) // 这里和下面是线段树二分的部分，另一颗线段树的二分也是同理的，就不写注释了
	{
		if(l==r)return l;
		if(tr[lc].sum>=k)return kth(lc,k,l,mid);
		else return kth(rc,k-tr[lc].sum,mid+1,r);
	}
	queue<array<int,3> >q;
	void findrangeid(int &x,int ql,int qr,int l=1,int r=toty) // 找到覆盖的节点，保存在 q 中
	{
		if(!x)x=++cnt;
		if(l>=ql&&r<=qr)return q.push({x,l,r}),void();
		if(ql<=mid)findrangeid(lc,ql,qr,l,mid);
		if(qr>mid)findrangeid(rc,ql,qr,mid+1,r);
	}
	int find(int &x,int k,int ql,int qr)
	{
		while(!q.empty())q.pop();
		findrangeid(x,ql,qr);
		int ss=0;
		for(;!q.empty();q.pop()) // 直接枚举
		{
			int xx=q.front()[0];
			if(ss+tr[xx].sum>=k)return kth(xx,k-ss,q.front()[1],q.front()[2]); // 合法直接递归查找后 return 掉即可
			ss+=tr[xx].sum;
		}
		return -1; // 没找到代表没有
	}
	#undef lc
	#undef rc
	#undef mid
}t;
int totx=0;
struct Seg_x
{
	struct node{int lc,rc,root,sum,maxx;}tr[N*35];
	#define lc tr[x].lc
	#define rc tr[x].rc
	void pushup(int x){tr[x].sum=tr[lc].sum+tr[rc].sum,tr[x].maxx=max(tr[lc].maxx,tr[rc].maxx);} // 这里还要多维护一个 maxx
	#define mid ((l+r)>>1)
	int cnt=0,root=0;
	void modify(int &x,int p,int pp,int v,int l=1,int r=totx)
	{
		if(!x)x=++cnt;
		if(l==r)
		{
			tr[x].sum+=v;
			t.modify(tr[x].root,pp,v);
			tr[x].maxx=t.kth(tr[x].root,t.tr[tr[x].root].sum); // 请注意更新 maxx 需要这样，不能直接 maxx=max(maxx,v)，因为有可能是删除
			return;
		}
		if(p<=mid)modify(lc,p,pp,v,l,mid);
		else modify(rc,p,pp,v,mid+1,r);
		pushup(x);
	}
	pair<int,int>kth(int x,int k,int ql,int qr,int l=1,int r=totx)
	{
		if(l==r)return {l,t.find(tr[x].root,1,ql,qr)};
		if(tr[lc].sum>=k&&tr[lc].maxx>=ql)return kth(lc,k,ql,qr,l,mid);
		else return kth(rc,k-tr[lc].sum,ql,qr,mid+1,r);
	}
	queue<array<int,3> >q;
	void findrangeid(int &x,int ql,int qr,int l=1,int r=totx)
	{
		if(!x)x=++cnt;
		if(l>=ql&&r<=qr)return q.push({x,l,r}),void();
		if(ql<=mid)findrangeid(lc,ql,qr,l,mid);
		if(qr>mid)findrangeid(rc,ql,qr,mid+1,r);
	}
	pair<int,int>find(int &x,int ql,int qr,int qll,int qrr)
	{
		while(!q.empty())q.pop();
		findrangeid(x,ql,qr);
		for(;!q.empty();q.pop())
		{
			int xx=q.front()[0];
			if(tr[xx].maxx>=qll&&tr[xx].sum)return kth(xx,1,qll,qrr,q.front()[1],q.front()[2]);
		}
		return {-1,-1};
	}
	#undef lc
	#undef rc
	#undef mid
}T;
struct que{int x,y;char op;}a[N];
vector<int>X,Y;
int main() // 剩余的都是常规操作
{
	int q=in();
	for(int i=1;i<=q;i++)
	{
		char c=getchar();
		while(!isalpha(c))c=getchar();
		int x=in(),y=in();
		a[i]={x,y,c},X.push_back(x),Y.push_back(y);
	}
	sort(X.begin(),X.end()),X.erase(unique(X.begin(),X.end()),X.end());
	sort(Y.begin(),Y.end()),Y.erase(unique(Y.begin(),Y.end()),Y.end());
	totx=X.size()+1,toty=Y.size()+1; // 注意 +1
	for(int i=1;i<=q;i++)
	{
		int x=lower_bound(X.begin(),X.end(),a[i].x)-X.begin()+1;
		int y=lower_bound(Y.begin(),Y.end(),a[i].y)-Y.begin()+1;
		char c=a[i].op;
		if(c=='a')T.modify(T.root,x,y,1);
		if(c=='r')T.modify(T.root,x,y,-1);
		if(c=='f')
		{
			pair<int,int>ans=T.find(T.root,x+1,totx,y+1,toty); // 这里也要注意 +1
			if(ans.first!=-1&&ans.second!=-1)out(X[ans.first-1]),putchar(' '),out(Y[ans.second-1]);
			else out(-1);
			putchar('\n');
		}
	}
	return 0;
}
```

------------

如果有错误或者不清晰的地方，欢迎私信或评论指出。

---

## 作者：Arghariza (赞：2)

upd : 修改了代码中的错误，原 `tr[x].st.end()` 应改成 `tr[x].st.rbegin()`。

## Description

定义三种操作:

1. `add x y` : 在坐标系上添加一个点 $(x,y)$。

2. `remove x y` : 移除点 $(x,y)$。

3. `find x y` : 找到所有已标记并在 $(x,y)$ 右上方的点中，最左边的点。

$m \le 2 \times 10^5$，$0 \le x,y \le 10^9$。

## Solution

可以先将所有点**按横坐标离散化**一遍，使用数据结构维护在某个 $x$ 坐标上的**所有点的纵坐标**。

我们思考一下我们需要维护什么，由于查询需要 $y_{ans}>y$，于是我们可以记录每个 $x$ 坐标**对应的所有点的 $y$ 坐标的最大值**，可以使用线段树，查询时在线段树上二分即可。

二分到第一个存在一个点，使得纵坐标大于给定 $y$ 的横坐标之后，我们需要求出这个横坐标对应的、纵坐标大于 $y$ 的最下面的点。由于一共不超过 $2\times 10^5$ 个点，我们离散化后可以对每个横坐标开一个 `set`，存储横坐标对应点的所有纵坐标，查询二分即可。

复杂度大概是 $O(n\log^2 n)$ 的，不用卡常。

[AC 记录](https://codeforces.com/contest/19/submission/174303857)

---

## 作者：SUNCHAOYI (赞：2)

所有操作均建立在二维平面上，容易想到 STL 库的 `set`。将点的 $y$ 坐标放入到对应的集合 $x$ 中进行相应的操作。插入操作为 ` s[x].insert (y)`，删除操作为 `s[x].erase (y)`，而查询操作需要从小到大遍历下标大于 $x$ 的集合，找到第一个不为空的集合且集合中存在一个元素大于 $y$。由题可知 $x,y$ 均较大，但是最多只有 $2 \times 10^5$ 次插入，容易想到将 $x$ 进行离散化，所以查询操作可以写成：

```cpp
//对于所有 j 均满足大于 x （离散化后的编号）
if (!s[j].empty () && s[j].upper_bound (q[i].y) != s[j].end ()) // print the answer
```

综上，我们可以得到第一份代码，只放了主函数的部分：

```cpp
int main ()
{
	n = read ();
	for (int i = 1;i <= n;++i) scanf ("%s",q[i].ty),q[i].x = read (),tmp[i] = q[i].x,q[i].y = read ();
	sort (tmp + 1,tmp + 1 + n);
	tot = unique (tmp + 1,tmp + n + 1) - tmp - 1;
	for (int i = 1;i <= n;++i) q[i].id = lower_bound (tmp + 1,tmp + 1 + tot,q[i].x) - tmp;//离散化
	for (int i = 1;i <= n;++i)
	{
		if (q[i].ty[0] == 'a') s[q[i].id].insert (q[i].y);
		else if (q[i].ty[0] == 'r') s[q[i].id].erase (q[i].y);
		else 
		{
			bool ok = 0;
			for (int j = q[i].id + 1;j <= tot;++j)
			{
				if (!s[j].empty () && s[j].upper_bound (q[i].y) != s[j].end ())
				{
					ok = 1;
					printf ("%d %d\n",tmp[j],*s[j].upper_bound (q[i].y));
					break;//找到最小的一个即可
				}
			}
			if (!ok) puts ("-1");//不存在就输出 -1
		}
	}
	return 0;
}
```

容易看得出复杂度主要在查询操作上，最坏情况下可以达到 $O(n^2)$。由于要找到一个最小的答案，所以可以进行线段树上的二分。每一个叶子节点的存的是离散化后 $x$ 对应编号的集合的最大值，换句话说，如果最大值都不符题意，那么该集合中一定无解。

将 `set` 与线段树配合着使用，插入的同时将离散化后 $x$ 对应编号的集合的所对应的节点改为当前集合的最大值（可能不会发生变化），删除操作也是同理，但要注意删除后集合为空的情况。

查询操作通过线段树求得对应的离散化后的 $x$ 或者无解，然后再通过 `set` 里的函数求解，因此主要的难度在于如何写线段树的查询操作，进行分类讨论：

- 区间不存在或线段树的某一个区间的最大值小于 $y$，不符，直接返回 $-1$。

- 已经递归至一个大小为 $1$ 的符合题意的区间（退化成点），之间返回端点编号。

- 递归左区间，如果合法就返回左区间的递归值；否则再递归右区间。

综上所述，我们得到了时间复杂度为 $O(n \log n)$ 的代码，一些重点在注释中有讲：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 4e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,tot,cnt,k[MAX],tree[MAX << 2]; 
struct node
{
	char ty[10];
	int x,y;
} q[MAX];
set <int> s[MAX];
void modify (int cur,int l,int r,int x,int v);
int query (int cur,int l,int r,int x,int y,int v);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();
	for (int i = 1;i <= n;++i) scanf ("%s",q[i].ty),q[i].x = read (),q[i].y = read (),k[++cnt] = q[i].x,k[++cnt] = q[i].y;
	sort (k + 1,k + 1 + cnt);
	tot = unique (k + 1,k + cnt + 1) - k - 1;
	for (int i = 1;i <= n;++i)//x y 都进行了离散化
	{
		q[i].x = lower_bound (k + 1,k + 1 + tot,q[i].x) - k;
		q[i].y = lower_bound (k + 1,k + 1 + tot,q[i].y) - k;//y 进行离散化是因为存在 y = 0 的点 离散化后便于与空集合作区分
	}
	for (int i = 1;i <= n;++i)
	{
		if (q[i].ty[0] == 'a') s[q[i].x].insert (q[i].y),modify (1,1,tot,q[i].x,*(--s[q[i].x].end ()));//插入后查找最值
		else if (q[i].ty[0] == 'r')
		{
			s[q[i].x].erase (q[i].y);
			if (!s[q[i].x].size ()) modify (1,1,tot,q[i].x,0);//区间为空，直接更新成 0
			else modify (1,1,tot,q[i].x,*(--s[q[i].x].end ()));//删除后查找最值
		}
		else 
		{
			int pos = query (1,1,tot,q[i].x + 1,tot,q[i].y);
			if (pos == -1) puts ("-1");//无解
			else printf ("%d %d\n",k[pos],k[*s[pos].upper_bound (q[i].y)]);//还原成原来的值后输出
		}
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void modify (int cur,int l,int r,int x,int v)//单点更新
{
	if (l == r)
	{
		tree[cur] = v;
		return ;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) modify (cur << 1,l,mid,x,v);
	else modify (cur << 1 | 1,mid + 1,r,x,v);
	tree[cur] = max (tree[cur << 1],tree[cur << 1 | 1]);//维护最大值
}
int query (int cur,int l,int r,int x,int y,int v)
{
	if (tree[cur] <= v || y < l || x > r) return -1;//无解
	if (l == r) return l;//区间长度为 1
	int mid = (l + r) >> 1,s = query (cur << 1,l,mid,x,y,v);
	if (~s) return s;//有解 显然左区间的编号更小
	return query (cur << 1 | 1,mid + 1,r,x,y,v);//左区间无解在进行右区间的递归
}
```

---

## 作者：幻影星坚强 (赞：2)

介绍一种操作分块做法。

首先对于每一组询问我们可以直接暴力查询所有点是否是最优答案，单次复杂度 $O(n)$。我们也可以离线所有点并排序（先横坐标从大到小，后纵坐标从大到小），对于加入的点我们把它加入一个单调栈内，因为排序过，所以加入的点肯定在询问的左边，于是对于询问的点我们在单调栈二分第一个在它上方的点即可，这样预处理单调栈的复杂度为 $O(n \log n)$（需要先排序），所有询问的复杂度之和为 $O(q\log n)$。

之后我们先预处理出所有点的顺序。之后考虑每 $B$ 次操作将下面 $B$ 次修改的点单独拿出暴力查询，其余的点用单调栈处理，然后对于询问取两者的最优值。
因为所有点的顺序都已求出，所以预处理单调栈就无须排序，这样时间复杂度为 $O(n\log n + \frac{q}{B}\times n + q\times B + q\log n)$。理论上 $B=\sqrt{n}$ 最优，复杂度为 $O(n\log n + q\sqrt{n} + q\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int block = 1500;
#define x first
#define y second
struct QUE
{
	int op, ids, x, y;
}que[N];
int n, m;
pair<int, int> P[N], now[N];
int vis[N], sf[N], nw[N];
int S[N], top, ans[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++ i)
	{
		char now[10];
		pair <int, int> p;
		cin >> now >> p.x >> p.y;
		if(now[0] == 'a')
		{
			que[i].op = 1;
			que[i].x = p.x;
			que[i].y = p.y;
			P[++ m] = p;
		}
		else
		if(now[0] == 'r')
		{
			que[i].op = 2;
			que[i].x = p.x;
			que[i].y = p.y;
			P[++ m] = p;
		}
		else
		{
			que[i].op = 3;
			que[i].x = p.x;
			que[i].y = p.y;
			P[++ m] = p;
		}
	}
	sort(P + 1, P + 1 + m);
	m = unique(P + 1, P + 1 + m) - P - 1;
	for (int i = 1; i <= n; ++ i)
	{
		que[i].ids = lower_bound(P + 1, P + 1 + m, make_pair(que[i].x, que[i].y)) - P;
	}
	P[0].x = -2e9;
	P[0].y = -2e9;
	top = 0;
	for (int l = 1; l <= n; l += block)
	{
		int r = min(l + block - 1, n);
		int num = 0, tot = 0;
		memcpy(sf, vis, sizeof(sf));
		for (int i = l; i <= r; ++ i)
		{
			if(que[i].op <= 2)
			sf[que[i].ids] = 0, nw[++ tot] = que[i].ids;
			else
			sf[que[i].ids] |= 2;
		}
		sort(nw + 1, nw + 1 + tot);
		tot = unique(nw + 1, nw + 1 + tot) - nw - 1;
		for (int i = 1; i <= m; ++ i)
		{
			if(sf[i] & 1)
			now[++ num] = make_pair(i, 1);
			
			if(sf[i] & 2)
			now[++ num] = make_pair(i, 0);
		}
		top = 0;
		for (int i = num; i; -- i)
		{
			int be = i;
			for (int j = i; ; -- j)
			{
				if(now[j].y == 0)
				{
					int l = 1, r = top;
					ans[now[j].x] = -1;
					while(l <= r)
					{
						int mid = (l + r) >> 1;
						if(P[S[mid]].y > P[now[j].x].y) ans[now[j].x] = S[mid], l = mid + 1;
						else r = mid - 1;
					}
					
				}
				i = j;
				if(P[now[j].x].x != P[now[j - 1].x].x)
				break;
			}
			for (int j = be; j >= i; -- j)
			{
				if(now[j].y == 1)
				{
					while(top && P[S[top]].y <= P[now[j].x].y)-- top;
					S[++ top] = now[j].x;
				}
			}
			
		}
		for (int i = l; i <= r; ++ i)
		{
			if(que[i].op == 1)
				vis[que[i].ids] = 1;
			else
			if(que[i].op == 2)
				vis[que[i].ids] = 0;
			else
			{
				int aa = ans[que[i].ids];
				for (int j = 1; j <= tot; ++ j)
				if(vis[nw[j]] && P[nw[j]].x > que[i].x && P[nw[j]].y > que[i].y && (aa == -1 || P[nw[j]].x < P[aa].x || (P[nw[j]].x == P[aa].x && P[nw[j]].y < P[aa].y)))
				aa = nw[j];
				if(aa == -1)
				cout << "-1\n";
				else
				cout << P[aa].x << " " << P[aa].y << "\n";
			}
		}
	}
}
```


---

## 作者：数学系 (赞：2)

权值线段树，将x作为线段树的下标，y作为下标为x的叶子节点的值（每一个x上可能会有许多y，我们只在线段树上存最大的y，剩下的存到set里。set支持log效率查询最大值，查找大于某树的最小值，插入，删除，代替了手写平衡树）。  
每次删除，直接用set中的查询删除相应值，再用set中的最大值更新x点的值即可。
每次查询，查询x+1到n中y值大于所要查询的y且x值最小的点，得到答案的x。这个点上可能有多个y满足条件，所以要查询set中比要查询的y的值大一些的值，得到答案的y。
另外空间有限，所以要离散化。


```cpp
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int maxn=200002;

char op[maxn][8];
int x[maxn],y[maxn];
int nums[maxn<<1];
int n;

set<int> pos_x[maxn];

struct node 
{
    int max;
    node *ls,*rs;
}pool[maxn<<1],*root;
int cnt=0;

int max(int a,int b)
{
    return a>b?a:b;
}

void change(node *&p,int l,int r,int pos)
{
    if(!p)
    {
        p=&pool[++cnt];
        p->max=-1;
    }
    if(l==r)
    {
    	p->max=(pos_x[pos].size()==0)?-1:(*(--pos_x[pos].end()));
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)
        change(p->ls,l,mid,pos);
    else
        change(p->rs,mid+1,r,pos);
    if(!p->ls)
    {
        p->ls=&pool[++cnt];
        p->max=-1;
    }
    if(!p->rs)
    {
        p->rs=&pool[++cnt];
        p->max=-1;
    }
    p->max=max(p->ls->max,p->rs->max);
}

int query(node *&p,int l,int r,int ql,int qr,int v)
{
    if(!p)
    {
        p=&pool[++cnt];
        p->max=-1;
    }
    int ans=0;
    if(l==r)
    {
    	return p->max>v?l:-1;
    }
    if(l==ql && r==qr)
    	if(p->max<=v)
    		return -1;
    int mid=(l+r)>>1;
    if(qr<=mid)
        return query(p->ls,l,mid,ql,qr,v);
    else if(ql>mid)
        return query(p->rs,mid+1,r,ql,qr,v);
    else
    {
    	if(p->ls)
    	{
	    	ans=query(p->ls,l,mid,ql,mid,v);
	    	if(ans>=0)
	    		return ans;
    	}
    	if(p->rs)
    		return query(p->rs,mid+1,r,mid+1,qr,v);
    }
    return -1;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
    	scanf("%s%d%d",&op[i],&x[i],&y[i]);
        nums[i]=x[i];
    }
    sort(nums+1,nums+n+1);
    int o=unique(nums+1,nums+n+1)-(nums+1)+1;
    for(int i=1;i<=n;i++)
        x[i]=lower_bound(nums+1,nums+o,x[i])-nums;
    
    int pos=0,pos_y=0;
    for(int i=1;i<=n;i++)
    {
        if(op[i][0]=='a')
        {
            pos_x[x[i]].insert(y[i]);
            change(root,1,o,x[i]);
        }
        else if(op[i][0]=='r')
        {
            pos_x[x[i]].erase(pos_x[x[i]].find(y[i]));
            change(root,1,o,x[i]);
        }
        else
        {
            pos=query(root,1,o,x[i]+1,o,y[i]);
            if(pos==-1)
            	printf("-1\n");
            else
            {
                pos_y=*pos_x[pos].upper_bound(y[i]);
                printf("%d %d\n",nums[pos],pos_y);	
            }
        }
    }
    return 0;
}

```

---

