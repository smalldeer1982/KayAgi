# Hanoi Factory

## 题目描述

你肯定听说过著名的游戏汉诺塔吧，但是你知道有一个神奇的工厂专门制造这种游戏塔上的环吗？很久之前，古埃及的裁定者命令“汉诺工厂”（上文提到的工厂）的工人制造一座尽可能高的汉诺塔，而他们没有做好准备去执行这样一个奇怪的命令，所以他们不得不用已经造好的环。
工厂储备有$n$个环，其内径为$a_i$，外径为$b_i$，高度为$h_i$。要求环的放置条件如下：
-    塔的外半径从下至上为非递增序列，即越下面的环外径不能小于上面的环
-    环不能掉下来，即相邻两环上方的环的外径必须大于下面的环的内径
-    塔的高度必须最大

## 说明/提示

Translated by Venus

## 样例 #1

### 输入

```
3
1 5 1
2 6 2
3 7 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
1 2 1
1 3 3
4 6 2
5 7 1
```

### 输出

```
4
```

# 题解

## 作者：Aryzec (赞：5)

#### [题面](https://www.luogu.org/problem/show?pid=CF777E)


------------

### 大致题意：

有 $n$ 个环，每个环有内径 $a_i$ , 外径 $b_i$ , 以及高度 $h_i$.

当满足以下条件时，可以将一个环放在另一个环的上面（记上面的环的编号为 $i$，下面的环的编号为 $j$）:

* **$b_i$ $\leq$ $b_j$ **
* **$b_i$ $ >  $ $a_j$ **

要求求出所能叠放到的最高高度


------------

### 先讲讲暴力

暴力一点都不难想：

用 $f_i$ 表示以编号为i的环为最上面的环所能达到的最高高度

我们可以先将这 $n$ 个环按外径从大到小排一遍序,这样转移的时候就可以保证 $b_i$ $\leq$ $b_j$。**注意排序的时候也有一些小细节，我会在后面说的。**

那么就有 $f_i= Max \lbrace f_j \rbrace (1≤j<i)+h_i$ ，转移条件：$b_i > a_j$

最后在所有的 $f_i$ 里取个最大值就好了



#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//注意要开 long long
ll f[100005],n,ans;
struct tzg{ll a,b,h;}a[100005];
bool cmp(tzg x,tzg y){
	if(x.b==y.b)return x.a>y.a;
	return x.b>y.b;
}//这个排序在后面的AC代码中解释的 
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;++i)scanf("%lld%lld%lld",&a[i].a,&a[i].b,&a[i].h);
	sort(a+1,a+n+1,cmp);
	for(ll i=1;i<=n;++i){
		for(ll j=0;j<i;++j){//因为第i个环下面也有可能没有环，所以j从0开始循环
			if(a[i].b>a[j].a)//如果可以转移 
				f[i]=max(f[i],f[j]+a[i].h);
		}
		ans=max(ans,f[i]);//更新ans 
	}
	cout<<ans;
	return 0;
}

```


------------

### 正解

暴力的时间复杂度是 $O(n^2)$ ，肯定是过不了的，我们想想怎么优化。

很明显，只有 $f_j$ 和 $j$ 有关，让我们想想怎么去把这一维给优化掉

每次都要找最大值，考虑用大根堆来实现。但是有一个转移条件 $b_i>a_j$，每次取堆头是都要判断一下这个转移是否合法，如果不合法就把堆顶弹掉。

这样会不会把对之后更新有影响的元素弹掉呢？

其实是不会的，让我们来看一下：

记堆顶元素为 $tp$ , 该状态位于最上面的环的内径为 $tp.w$ ，此时对应的高度为 $tp.h$

对于当前的 $i$ , 如果转移是非法的，即 $b_i \leq tp.w$ ，那么可以得出 $b_{i+1} \leq tp.w $ （因为是按外径从大到小排序的），所以说把堆顶元素弹掉不会影响之后的状态

那么就好办了，用一个堆维护最大值就行了

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll f[100005],n,ans;
struct tzg{ll a,b,h;}a[100005];
bool cmp(tzg x,tzg y){
	if(x.b==y.b)return x.a>y.a;//当两个环外径相等时,要将内径小的环放在上面，这样可以更方便对于后面外径比这个环小的状态的转移 
	return x.b>y.b;
}
struct node{
	ll w,h;
	bool operator<(const node &rhs)const{
		return h<rhs.h;
	}
};
priority_queue<node> q;
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;++i)scanf("%lld%lld%lld",&a[i].a,&a[i].b,&a[i].h);
	sort(a+1,a+n+1,cmp);
	q.push((node){0,0});//可以直接从下面没有环的状态转移过来 
	for(ll i=1;i<=n;++i){
		while(q.top().w>=a[i].b)q.pop();
		f[i]=q.top().h+a[i].h;//其实这个f数组没有必要开 
		q.push((node){a[i].a,q.top().h+a[i].h});
		ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：crh1272336175 (赞：3)

思路：栈+贪心

看了两位大佬的dp和堆的题解，本蒟蒻来写一个栈的做法

首先肯定还是要根据外径从大到小排序的，这样子我们在遍历1~n的时候就可以保证外径已经有序

然后维护一个栈，每次操作之先维护栈顶
具体来说，如果不能放了（也就是当前的内径要小于等于栈顶的时候）就把栈顶弹出

然后再将当前节点入栈，注意要实时记录答案的最大值，这样才能保证最后的答案是正确的

AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
typedef long long ll;
ll n,ans,sum;
ll f[M];
struct node
{
	ll a,b,h;
}p[M];
stack<int> stk;
bool cmp(node x,node y)
{
    if(x.b!=y.b) return x.b>y.b; 
    return x.a>y.a;
}
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
    	int a,b,c; scanf("%d%d%d",&a,&b,&c);
    	p[i]={a,b,c};
	}
    sort(p+1,p+1+n,cmp);
    ans=sum=p[1].h;
    stk.push(1);
    for(int i=2; i<=n; i++)
    {
    	while(!stk.empty() && p[stk.top()].a>=p[i].b)
    	{
    		sum-=p[stk.top()].h;
    		stk.pop();
		}
		sum+=p[i].h;
		stk.push(i);
		ans=max(ans,sum);
	}
	printf("%lld",ans);
    return 0;
}
```


---

## 作者：Smallbasic (赞：2)

考虑$i$能放在$j$上面，由题目可知，此时$a_j<b_i \le b_j$

我们先按照$b$排序，保证$b$是降序排列的，就能够写出一个很暴力的dp:设$f_i$表示只考虑前$i$个且$i$放在最上面的最优方案，则：

$$f_i=\max_{j<i,a_j<b_i} f_j+h_i$$

由于已经按$b$排过序，就不用考虑下面的比上面的外径小这种情况。

直接暴力dp是$O(n^2)$的，我们可以讲$a_i,b_i$离散化后树状数组维护前缀最大值即可，细节见代码。

~~所以为什么神仙把这题放到单调栈的题里面啊~~

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long ll;

using namespace std;

const int N = 100005;

int n, a[N];
ll tree[N];

#define lowbit(x) ((x)&(-(x)))

inline ll max_(ll a, ll b) {
	return a > b ? a : b;
}

inline void add(int x, ll a) {
	for (int i = x; i < N; i += lowbit(i)) tree[i] = max_(tree[i], a); 
}

inline ll qmax(int x) {
	ll ret = 0;
	for (int i = x; i; i -= lowbit(i)) ret = max_(ret, tree[i]);
	return ret;
}

struct Cycle {
	int a, b, h;
}cy[N];

inline bool cmp(Cycle a, Cycle b) {
	if (a.b == b.b) return a.a > b.a;
	return a.b > b.b;
}

ll f[N], ans = 0;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &cy[i].a, &cy[i].b, &cy[i].h);
		a[i] = cy[i].a;
	} sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i)
		cy[i].a = lower_bound(a + 1, a + n + 1, cy[i].a) - a;
	sort(cy + 1, cy + n + 1, cmp);
	ans = cy[1].h; f[1] = cy[1].h;
	add(cy[1].a, f[1]);
	for (int i = 2; i <= n; ++i) {
		f[i] = qmax(lower_bound(a + 1, a + n + 1, cy[i].b) - a - 1);
		f[i] += cy[i].h;
		add(cy[i].a, f[i]);
		ans = max_(f[i], ans);
	} printf("%lld", ans);
	return 0;
}
```


---

## 作者：cannotdp (赞：1)

### 首先想到的是 DP
先将 $n$ 个环按照外径从大到小排序，若外径相同，再按照内径从大到小排序。

- 设 $f_i$ 表示以编号为 $i$ 的环为最上面的环所能到达的最高高度。

- 状态转移方程为：$f_i=\max{f_j}+h_i (1\le j<i,b_i>a_j)$。

- 最后在所有的 $f_i$ 中取最大值。
时间复杂度为 $O(n^2)$。

### 关键代码
```cpp
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++){
	for(int j=0;j<i;j++){
		if(a[i].b>a[j].a)
			f[i]=max(f[i],f[j]+a[i].h);
	}
	ans=max(ans,f[i]);
}
```
------------
### 然而直接进行 DP 显然时间复杂度过高，所以我们可以考虑使用堆优化。
记堆顶元素为 $L$，该状态位于最上面的环的内径为 $L.w$，此时对应的高度为 $L.h$。

因为在DP转移的过程中要求 $b_i>a_j$，每次取堆头是都要判断一下这个转移是否合法，如果不合法就把堆顶弹掉。

时间复杂度为 $O(n\log n)$。

### 代码
```cpp
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
int n;
struct L{
	int a,b,h;
}p[100010];
bool cmp(L x,L y){
	return x.b>y.b||(x.b==y.b&&x.a>y.a);
}
stack<L>q;
long long ans,now;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].h);
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(q.empty()||p[i].b==q.top().b){
			q.push(p[i]);
			now+=p[i].h;
		}
		else{
			while(!q.empty()&&p[i].b<=q.top().a){
				ans=max(ans,now);
				now-=q.top().h;
				q.pop();
			}
			q.push(p[i]);
			now+=p[i].h;
			ans=max(ans,now);
		}
	}
	ans=max(ans,now);
	cout<<ans;
	return 0;
}
```


---

## 作者：wwlw (赞：1)

[Link](https://www.luogu.com.cn/problem/CF777E)
----------

### Solution
容易想到用 $f_i$ 表示顶部圆环是 $i$ 时的塔的最大高度。考虑如何转移，一个圆环 $i$ 能放在另一个圆环 $j$ 上，必有 $b_i\leq b_j$，所以容易想到按照 $b$ 降序排序，那么 $f_i$ 只需要从 $j \ (j<i)$ 转移，就没有后效性。容易写出转移方程
$$f_i=\max \limits_{a_j<b_i} \{f_j\}+h_i \quad j\in[1,i)$$
形象地说就是在前 $i-1$ 个圆环中，找到 $a$ 值小于一个值的所有 $f$ 的最大值。显然可以离散化 $a$ 和 $b$ 后用树状数组维护。

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
#define N 100007
#define ll long long

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct Node{
    int a,b; ll h;
    bool operator <(const Node &x) const{
        return b!=x.b? b>x.b:a>x.a;
    }
}t[N];

int n,X[N<<1],sz;
ll f[N],c[N<<1];

inline int lowbit(int x){return -x&x;}
inline void add(int x,ll v){while(x<=sz)c[x]=max(c[x],v),x+=lowbit(x);}
inline ll query(int x){ll ret=0;while(x)ret=max(ret,c[x]),x-=lowbit(x);return ret;}

int main(){
    n=read();
    for(int i=1;i<=n;i++){
        t[i].a=read(),t[i].b=read(),t[i].h=read();
        X[(i<<1)-1]=t[i].a,X[i<<1]=t[i].b;
    }
    sort(t+1,t+1+n),sort(X+1,X+1+2*n);
    sz=unique(X+1,X+1+2*n)-(X+1);
    for(int i=1;i<=n;i++){
        t[i].a=lower_bound(X+1,X+1+sz,t[i].a)-X;
        t[i].b=lower_bound(X+1,X+1+sz,t[i].b)-X;
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        f[i]=query(t[i].b-1)+t[i].h;
        add(t[i].a,f[i]);
        ans=max(ans,f[i]);
    }
    printf("%lld",ans);
}
```

----------

后面发现并不需要树状数组，观察这句话：
```cpp
f[i]=query(t[i].b-1)+t[i].h;
```
因为 $b$ 是单调不增的，所以决策集合一直在减小。对于三个圆环 $j$ 、$i$ 和 $k$，且有 $j<i<k$，如果 $i$ 不能从 $j$ 转移过来，那么 $k$ 也一定不能从 $j$ 转移。所以我们可以维护这个决策集合，如果 $j$ 不合法就直接删掉而不会对后面造成影响。再次观察转移方程，每次我们取了决策集合里面的最大值，之后又加上了一个正整数 $h$，所以再把现在更新出来的 $f_i$ 加入决策集合，$f_i$ 就会成为决策集合里面的最大值，所以决策集合里的 $f$ 也具有单调性，且是单增的。那么剩下的就可以用单调栈来维护了。单调栈复杂度 $O(n)$

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
#define N 100007
#define ll long long

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct Node{
    int a,b; ll h;
    bool operator <(const Node &x) const{
        return b!=x.b? b>x.b:a>x.a;
    }
}t[N],sta[N];

int n,top=0;
ll f[N];

inline ll max(ll x,ll y){return x>y? x:y;}
int main(){
    n=read();
    for(int i=1;i<=n;i++)
        t[i].a=read(),t[i].b=read(),t[i].h=read();
    sort(t+1,t+1+n);
    ll ans=0;
    for(int i=1;i<=n;i++){
        while(top&&t[i].b<=sta[top].a) top--;
        sta[++top]=t[i];
        sta[top].h+=sta[top-1].h;
        ans=max(ans,sta[top].h);
    }
    printf("%lld",ans);
}
```

发现不需要离散化了，瓶颈在于排序。如果再把快排换成基数排序，那么总的时间复杂度大概就是 $O(n)$。

### Tips
对于 $b_i=b_j$，要按照 $a$ 降序排序，因为顶部的内径越小越好，对后面的转移有正的影响。

---

## 作者：_O_v_O_ (赞：0)

100th 题解！同时这题也是我的 1000th AC。

我们考虑将 $\{a_i,b_i\}$ 按 $b_i$ 降序排序，那么条件就只剩 $b_i>a_j$ 了。

那么我们考虑 dp，设 $dp_i$ 表示前 $i$ 个圆可以放的最大值，那么有转移方程 $dp_i=\max_{j=1}^{i-1}\{dp_j[b_i>a_j]\}+h_i$。

我们考虑将上面优化一下：

我们看到 $\max$ 考虑维护一个堆来优化转移。

可是这样就维护不了上面的 $[b_i>a_j]$，事实上我们注意到因为 $b_i$ 已经递减，所以一旦一个 $a_j\le b_i$，那么 $a_j$ 一定也 $\le b_{i+1}$，所以我们再在堆中维护一个 $a$，一旦我们遇到某个 $a_j$ 无法转移，直接弹掉就行了。

代码很简单，不放了。

---

## 作者：Mashu77 (赞：0)

题意：给出一堆指环的内径 $a$、外径 $b$、高 $h$，要把指环叠成塔，即外径从下往上不递增，同时两个上下相邻的指环中上面的指环的外径要大于下面指环的内径（不然上面的指环就掉下去了），求最高的塔。



思路：将所有 $a_i$ 的内外半径排序，并且离散化为单调数组，也就是拿单调离散数组的下标去映射 $a_i$。然后就只需要用树状数组维护区间最大高度。
```cpp
#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;
struct abc
{
    long long a,b,c;
} a[3000001];

inline bool cmp(abc x,abc y)
{
    return (x.b>y.b|| (x.b==y.b && x.a>y.a));
}

long long n,tree[3000001],m=0;

 vector<int> has;	//将内半径和外半径离散化

//树状数组, 保留塔高最大值
void upd(long long x,long long y)
{	// m 为外半径位置序号的最大值
    for (;x<=m;x+=x&(-x)) tree[x]=max(tree[x],y);
}
long long get(long long x)
{
    long long p=0;
    for (;x;x-=x&(-x)) p=max(p,tree[x]);
    return p;
}

int main()
{

	FILE *fi;
	freopen_s(&fi,"CF777Ein.txt","r",stdin);

    scanf_s("%lld",&n);
    long long i;
    for (i=1;i<=n;i++)
        scanf_s("%lld%lld%lld",&a[i].a,&a[i].b,&a[i].c);

    for (i=1;i<=n;i++)
        has.push_back(a[i].a),has.push_back(a[i].b);

	  sort(has.begin(), has.end());
	    for (i=0;i<has.size();i++)cout<<", "<<has[i];
		cout<<endl;
		// 将内外半径离散化，以方便使用树状数组
    for (i=1;i<=n;i++)
	{
        a[i].a= lower_bound(has.begin(), has.end(), a[i].a)-has.begin()+1;//  a[i].a 为其半径位置序号
		a[i].b= lower_bound(has.begin(), has.end(), a[i].b)-has.begin()+1;//  a[i].b 为其半径位置序号
		m=max(a[i].b,m);// m 为外半径位置序号的最大值
	}
	 for (i=1;i<=n;i++)cout<<", a[i].b="<<a[i].b;
		cout<<endl;

    sort(a+1,a+n+1,cmp);// 降序排列关于b


    for (i=1;i<=n;i++)
       printf("a[i].a=%lld, %lld, %lld\n",a[i].a,a[i].b,a[i].c);
	cout<<endl;
    long long ans=0;
    for (i=1;i<=n;i++)
    {
        long long now=get(a[i].b-1)+a[i].c;// get(a[i].b-1)为寻找内半径小于a[i].b所达到的最大高度
        cout<<" get(a[i].b-1)="<<get(a[i].b-1)<<endl;
        upd(a[i].a,now);	// 上传内半径a[i].a 所达到的最大高度
		 cout<<"a[i].a="<<a[i].a<<", now="<<now<<endl;
        ans=max(ans,now);
    }
    printf("%lld\n",ans);
    return 0;
}

---

## 作者：Jμdge (赞：0)

直接代码。


```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
#define P make_pair
#define ll long long
using namespace std;
const int M=1e6+100;
const int inf=1e9;
inline int read(){
	int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}
int n,head=1,tail;
priority_queue< pair<ll,ll> > q; //大根堆,make_pair
ll res=-inf;
struct Node{
	ll a,b,h;
	friend bool operator < (const Node& x,const Node& y){
		return x.b!=y.b ? x.b>y.b : x.a>y.a; //b相同则a大的放前面（思考为何）
	}
}p[M];

int main(){
	n=read();
	for(int i=0;i<n;++i)
		p[i].a=read(),
		p[i].b=read(),
		p[i].h=read();
	sort(p , p+n);
	//此时p数组已按b值降序排序
	for(int i=0;i<n;++i){
		ll tmp=p[i].h;
		while(!q.empty() && q.top().second>=p[i].b)
			q.pop(); //pop出val值最大的但不满足条件的pair
            			//解释一下,在i之后的汉诺块的外径b肯定小于当前块p[i]的外径b,现在就不满足条件的之后肯定也不会满足条件
		if(!q.empty()) tmp+=q.top().first; //如果队里还有满足条件的汉诺块则加上val
		q.push(P(tmp,p[i].a)); //入队
		res=max(res , tmp); //更新res
	}
	cout<<res<<endl;
	return 0;
}
```

---

