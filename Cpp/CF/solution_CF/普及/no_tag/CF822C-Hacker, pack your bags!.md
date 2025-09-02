# Hacker, pack your bags!

## 题目描述

It's well known that the best way to distract from something is to do one's favourite thing. Job is such a thing for Leha.

So the hacker began to work hard in order to get rid of boredom. It means that Leha began to hack computers all over the world. For such zeal boss gave the hacker a vacation of exactly $ x $ days. You know the majority of people prefer to go somewhere for a vacation, so Leha immediately went to the travel agency. There he found out that $ n $ vouchers left. $ i $ -th voucher is characterized by three integers $ l_{i} $ , $ r_{i} $ , $ cost_{i} $ — day of departure from Vičkopolis, day of arriving back in Vičkopolis and cost of the voucher correspondingly. The duration of the $ i $ -th voucher is a value $ r_{i}-l_{i}+1 $ .

At the same time Leha wants to split his own vocation into two parts. Besides he wants to spend as little money as possible. Formally Leha wants to choose exactly two vouchers $ i $ and $ j $ $ (i≠j) $ so that they don't intersect, sum of their durations is exactly $ x $ and their total cost is as minimal as possible. Two vouchers $ i $ and $ j $ don't intersect if only at least one of the following conditions is fulfilled: $ r_{i}&lt;l_{j} $ or $ r_{j}&lt;l_{i} $ .

Help Leha to choose the necessary vouchers!

## 说明/提示

In the first sample Leha should choose first and third vouchers. Hereupon the total duration will be equal to $ (3-1+1)+(6-5+1)=5 $ and the total cost will be $ 4+1=5 $ .

In the second sample the duration of each voucher is $ 3 $ therefore it's impossible to choose two vouchers with the total duration equal to $ 2 $ .

## 样例 #1

### 输入

```
4 5
1 3 4
1 2 5
5 6 1
1 2 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2
4 6 3
2 4 1
3 5 4
```

### 输出

```
-1
```

# 题解

## 作者：MuYC (赞：2)

#### 前言

这是一道很棒的思维题/数据结构！

update(2020.12.22):让内容更加客观具体了，去掉了一些带有个人主观性的东西（水话少了），求管理员通过。

做法：二分，排序 

#### 题意搬运：

给定 $n,m$ 以及 $n$ 个区间，区间 $i$ 有左端点 $l_i$ 和 右端点 $r_i$ 以及 花费 $cost_i$ ,要求你选出两个区间,满足下面两个条件:
+ 两个区间没有交集
+ 两个区间的长度和等于 $m$ (这里的长度为 $r_i - l _i + 1$ )

现在要求你选出的这两个区间的权值和最小，输出最小权值和。

#### 做法：

因为是两个区间，考虑枚举其中一个区间。

因为两个区间要不相交，所以很容易想到把所有区间按照其 $l$ 从小到大排序，如果 $l$ 相等，则按照 $r$ 从小到大排序。

通过枚举区间 $a$，只需要找到所有左端点 $l_b$ 大于其右端点 $r_a$ 的区间 $b$，这样子 $a$ , $b$ 两个区间就是不相交的。

可以通过二分找到第一个左端点 $l$ > $r_a$ 的区间,这样子所有左端点在这个找到的区间的左端点右边的区间都是满足条件的区间，假设找到的是第 $j$ 个区间，因为所有区间是按 左端点 $l$ 排序好了的，所以从 第 $j$ 到 第 $n$ 个区间跟当前区间 $i$ 都是没有交点的。

找到 $[L_i,R_i]$ 内满足 $lenb = m - lena$ 的所有区间的权值最小值，也就是跟当前区间 $i$ 的长度之和为 $m$ 的 所有区间中区间的权值最小的区间。
( $R_i$ 直接设置为 $n$ , $L_i$ 用之前提到的二分找到，如果不存在 $L_i$ ，那么说明这个区间是无法与其他区间满足条件的)

这样子就满足了第一个限制,并且每一张票都有了一个自己查询的区间：$[L_i,R_i]$。

对于枚举的每一个区间都进行查询很不方便，但是感觉可以用神奇数据结构来搞（目测线段树？

观察到每次要查的右区间是固定的，不妨将枚举到 $i$ 的时候需要查询的 $L_i$ 给记录下来，然后把 $L_i$ 按照从大到小排序。

这样子 O($n$) 扫一遍过来，开个桶在扫的时候记录一下 $Min[len]$ ，也就是长度为 $len$ 的所有区间的权值最小值，这时候对于询问就直接O(1) 获得答案。

#### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 400005,INF = 100000000000000000;
int n , m ;
int Min[MAXN],cnt = 0;

struct Node {
	int l,r,cost;
} T[MAXN];

struct P {
	int L,D,F;
    //L记录查[L,R]的左端点L,D表示枚举到的区间的权值，F表示要找的长度 即长度为 m-lena 
} C[MAXN];

bool cmp(Node A , Node B)
{
	if(A.l != B.l)
	return A.l < B.l;
	return A.r < B.r;
}

int cmp1(P A, P B)
{
	return A.L > B.L;
}

inline int read()
{
	int x = 0 , flag = 1;
	char ch = getchar();
	for( ; ch > '9' && ch < '0' ; ch = getchar())if(ch == '-')flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar())x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

signed main()
{
	n = read() , m = read();
	for(int i = 1 ; i <= n ; i ++)
	T[i].l = read(),T[i].r = read(),T[i].cost = read();
	sort(T + 1 , T + 1 + n , cmp);//按照左端点从小到大排序，左端点相同的按照右端点从小到达排序
	for(int i = 1 ; i <= m ; i ++)Min[i] = INF;
	for(int i = 1 ; i <= n ; i ++)
	{
		int lena = T[i].r - T[i].l + 1;
		if(lena >= m){C[i].L = -1;continue;}
                //剪枝了一下，如果当前区间长度大于等于m了，另外一个区间需要长度小于等于0，不存在答案
		int K = n + 1;
		for(int j = log2(n - i + 1) ; j >= 0 ; j --)
			if(T[K - (1 << j)].l > T[i].r && K - (1 << j) >= 1)K -= (1 << j);//二分换成倍增了。
		if(K != n + 1)
			C[i].L = K , C[i].D = T[i].cost , C[i].F = m - lena;
		else C[i].L = -1;//题解里说的L不存在，赋值为-1
	}
	sort(C + 1 , C + 1 + n , cmp1);//按照L排序
	int now = 1,Ans = INF;
	for(int i = n ; i >= 1 ; i --)
	{
		if(C[now].L == -1)break;//如果没有询问了直接break
		int len = T[i].r - T[i].l + 1;
		Min[len] = min(Min[len],T[i].cost);//扫的时候记录长度为len的区间的权值最小值
		while(C[now].L == i && now <= n)一个点可能有多个询问，用while
		{
			if(C[now].L == -1)break;//没有询问了
			Ans = min(Ans,C[now].D + Min[C[now].F]);//O(1)获得答案，取min
			now ++;
		}
	}
	if(Ans == INF)	cout << -1;
	else cout << Ans;
	return 0;
}
```

下面是无注释版本的代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 400005,INF = 100000000000000000;
int n , m ;
int Min[MAXN],cnt = 0;
 
struct Node {
    int l,r,cost;
} T[MAXN];
 
struct P {
    int L,D,F;
} C[MAXN];
 
bool cmp(Node A , Node B)
{
    if(A.l != B.l)
    return A.l < B.l;
    return A.r < B.r;
}
 
int cmp1(P A, P B)
{
    return A.L > B.L;
}
 
inline int read()
{
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' && ch < '0' ; ch = getchar())if(ch == '-')flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar())x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
 
signed main()
{
    n = read() , m = read();
    for(int i = 1 ; i <= n ; i ++)
    T[i].l = read(),T[i].r = read(),T[i].cost = read();
    sort(T + 1 , T + 1 + n , cmp);
    for(int i = 1 ; i <= m ; i ++)Min[i] = INF;
    for(int i = 1 ; i <= n ; i ++)
    {
        int lena = T[i].r - T[i].l + 1;
        if(lena >= m){C[i].L = -1;continue;}
        int K = n + 1;
        for(int j = log2(n - i + 1) ; j >= 0 ; j --)
            if(T[K - (1 << j)].l > T[i].r && K - (1 << j) >= 1)K -= (1 << j);
        if(K != n + 1)
            C[i].L = K , C[i].D = T[i].cost , C[i].F = m - lena;
        else C[i].L = -1;
    }
    sort(C + 1 , C + 1 + n , cmp1);
    int now = 1,Ans = INF;
    for(int i = n ; i >= 1 ; i --)
    {
        if(C[now].L == -1)break;
        int len = T[i].r - T[i].l + 1;
        Min[len] = min(Min[len],T[i].cost);
        while(C[now].L == i && now <= n)
        {
            if(C[now].L == -1)break;
            Ans = min(Ans,C[now].D + Min[C[now].F]);
            now ++;
        }
    }
    if(Ans == INF)    cout << -1;
    else cout << Ans;
    return 0;
}
```

另外建议不要用$cin$,如果用$cin$评测得很慢，虽然不会超时，但是你得评测$1$分半钟.....（因为一共136个点！）

---

## 作者：AC_love (赞：1)

考虑到答案选择的区间一定是形如：$[l_1, \ r_1]$ 和 $[l_2, \ r_2]$ 的形式且 $l_1 \le r_1 < l_2 \le r_2$。

那么我们不妨把所有区间按照左端点排序，然后针对每个区间看看它左面有没有合适的能和它匹配的区间，在所有合适的区间里找一个代价最小的匹配上。

这个东西看起来很神秘，因为如果直接暴力匹配的话显然是 $O(n^2)$ 的会直接 T 飞，所以考虑优化。

我的思路是用一堆动态数组来记录这些东西。

首先，我在从左往右扫的时候，可以把长度为 $k$ 的区间的信息放到下标为 $k$ 的数组里。

显然对于任何一个数组，这个数组里的所有区间右端点都单调不降。

当我们扫到一个长度为 $k$ 的区间时，我们就去长度为 $m - k$ 的数组里二分找到右端点小于当前区间左端点的最靠右的区间，然后查询左面那一半的最小值。

按理说我们单次查询最坏是 $O(n)$ 的，这样的话我们的时间复杂度还是 $O(n^2)$，不过我们可以用类似前缀和的东西维护一下前缀 $\min$，这样的话查询就是 $O(1)$ 的。但是由于二分还是带了个 $\log$，所以总复杂度还是 $O(n \log n)$。

只跑了 $300$ 毫秒，毫不夸张的说真就跑得飞快。

代码实现如下（本题其实不加快读也不会 T，但是一共有一百多个测试点，如果用 `cin` 就会等很久，所以提交代码的时候还是建议加个快读）：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int inf = 2147483647;
int ans = inf;

inline int read()
{
	long long xr = 0, F = 1;
	char cr;
	while(cr = getchar(), cr < '0' || cr > '9')
		if(cr == '-')
			F = -1;
	while(cr >= '0' && cr <= '9') xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

const int N = 214514;
int n, m;

struct section 
{
	int l;
	int r;
	int cost;
	int val;
};

section s[N];

vector <section> v[N];
vector <int> minn[N];

bool cmp(section i, section j)
{
	return i.l < j.l;
}

signed main()
{
	n = read();
	m = read();
	
	for(int i = 1; i <= n; i = i + 1)
	{
		s[i].l = read();
		s[i].r = read();
		s[i].cost = read();
		s[i].val = s[i].r - s[i].l + 1;
	}
	sort(s + 1, s + 1 + n, cmp);
	for(int i = 1; i <= n; i = i + 1)
	{
		if(s[i].val >= m)
			continue;
		v[s[i].val].push_back(s[i]);
		int sz = minn[s[i].val].size();
		minn[s[i].val].push_back(sz == 0 ? s[i].cost : min(s[i].cost, minn[s[i].val][sz - 1]));
		int f = m - s[i].val;
		if(v[f].size() == 0 || v[f][0].r >= s[i].l)
			continue;
		int l = -1, r = v[f].size();
		while(l < r - 1)
		{
			int mid = (l + r) / 2;
			if(v[f][mid].r < s[i].l)
				l = mid;
			else
				r = mid;
		}
		ans = min(ans, s[i].cost + minn[f][l]);
	}
	if(ans == inf)
		cout << "-1";
	else
		cout << ans;
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF822C)

------------

# 思路：
这题目肯定是枚举一条线段再找剩下一条线段，假设枚举右线段，且其长为 $len1$，那么我们需要找这条线段左边的长度为 $x - len1$ 的线段的 $cost$ 最小值，直接暴力的话是 $n^2$ 的复杂度，肯定爆。可以给这些线段按照左右端点排下序，那么我们可以从按左端点排序的数组中枚举右线段，然后在按右端点排序的数组中找左线段，但是如果暴力找的话时间复杂度还是 $n^2$。我们可以维护一个 $vis$ 数组，$vis[i]$ 为当前右线段的左边线段中长度为 $i$ 的 $cost$ 最小值，那么 $vis[x - len1]$ 即为当前左线段的 $cost$ 最小值。

那么 $cost1 + vis[x - len1]$ 的最小值即为答案啦。

代码：
```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 2e5 + 10;
const int inf = 0x7f7f7f7f;
ll vis[MAXN];
struct node{
    int l, r;
    ll w;
}gel1[MAXN], gel2[MAXN];

bool cmp1(node a, node b){
    return a.l < b.l;
}

bool cmp2(node a, node b){
    return a.r < b.r;
}

int main(void){
    int n, x;
    ll ans = inf;
    scanf("%d%d", &n, &x);
    for(int i = 0; i < n; i++){
        scanf("%d%d%lld", &gel1[i].l, &gel1[i].r, &gel1[i].w);
        gel2[i] = gel1[i];
    }
    sort(gel1, gel1 + n, cmp1);
    sort(gel2, gel2 + n, cmp2);
    memset(vis, 0x7f, sizeof(vis));
    int indx = 0;
    for(int i = 0; i < n; i++){
        ll gg = gel1[i].w;
        while(indx < n && gel2[indx].r < gel1[i].l){
            int cnt = gel2[indx].r - gel2[indx].l + 1;
            if(vis[cnt] > gel2[indx].w) vis[cnt] = gel2[indx].w;
            indx++;
        }
        int cc = x - (gel1[i].r - gel1[i].l + 1);
        if(cc <= 0) continue;
        gg += vis[cc];
        if(ans > gg) ans = gg;
    }
    if(ans == inf) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}
```

---

## 作者：Mariposa (赞：1)

第一眼主席树，一看只有$1600$？怀疑自己眼瞎。

确实有非暴力数据结构做法，不过这里讲一下显然的主席树做法。


------------
考虑将区间按右端点排序，对每个区间查询它左边的最小的区间，更新答案。

考虑到一个区间在另一个区间左边，只需满足其右端点小于另一个的左端点即可。

形象化的，可以描述为一个$l\rightarrow r$的区间长度为$len$，

查询它前面的区间$x$使$r_x<l$且$len_x+len=m$的最小$cost_x$。

建一棵以$r$为时间轴，$len$为下标，维护$cost$最小值的主席树即可。

细节较多，代码奉上，仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f; 
}
#define inf 1e15+7
const int maxn=2e5+10;
const int N=2e5;
struct node{
	int l,r,len,c;
}p[maxn];
inline int cmp(node x,node y){return x.r<y.r;}
int n,m,a[maxn<<1],b[maxn];
int rt[maxn<<1],cnt,ans=inf;
struct {
	int l,r,val;
}tr[maxn*50];
inline int build(int h,int l,int r){
	h=++cnt;tr[h].val=inf;
	if(l==r)return h;
	int mid=(l+r)>>1;
	tr[h].l=build(tr[h].l,l,mid);
	tr[h].r=build(tr[h].r,mid+1,r);
	return h;
}
inline int modify(int h,int h1,int l,int r,int x,int y){
	h=++cnt;tr[h]=tr[h1];
	tr[h].val=min(tr[h].val,y);
	if(l==r)return h;
	int mid=(l+r)>>1;
	if(mid>=x)tr[h].l=modify(tr[h].l,tr[h1].l,l,mid,x,y);
	else tr[h].r=modify(tr[h].r,tr[h1].r,mid+1,r,x,y);
	return h;
}
inline int query(int h,int l,int r,int x){
	if(!h)return inf;
	if(l==r)return tr[h].val;
	int mid=(l+r)>>1;
	if(mid>=x)return query(tr[h].l,l,mid,x);
	else return query(tr[h].r,mid+1,r,x);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=p[i].l=read();
		a[i+n]=p[i].r=read();
		p[i].len=p[i].r-p[i].l+1;
		p[i].c=read();
	}
	sort(a+1,a+1+2*n);
	int t=unique(a+1,a+1+2*n)-a-1;
	for(int i=1;i<=n;i++){
		p[i].l=lower_bound(a+1,a+1+t,p[i].l)-a;
		p[i].r=lower_bound(a+1,a+1+t,p[i].r)-a;
	}
	sort(p+1,p+1+n,cmp);
	rt[0]=build(rt[0],1,N);
	int pos=1,x=0;
	for(int i=1;i<=t;i++){
		rt[i]=rt[i-1];
		while(pos<=n&&p[pos].r<=i){
			x=query(rt[p[pos].l-1],1,N,m-p[pos].len);
			ans=min(ans,x+p[pos].c);
			rt[i]=modify(rt[i],rt[i],1,N,p[pos].len,p[pos].c);
			pos++;
		}
	}
	if(ans==inf)puts("-1");
	else printf("%lld\n",ans);
	return 0;
}
```

---

