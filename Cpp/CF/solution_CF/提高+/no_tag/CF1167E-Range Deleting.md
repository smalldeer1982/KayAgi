# Range Deleting

## 题目描述

给定一个包含 $n$ 个整数 $a_1, a_2, \dots, a_n$ 的数组和一个整数 $x$。保证对于每个 $i$，都有 $1 \le a_i \le x$。

定义函数 $f(l, r)$，其作用是从数组 $a$ 中删除所有满足 $l \le a_i \le r$ 的元素，并返回删除后的新数组。例如，如果 $a = [4, 1, 1, 4, 5, 2, 4, 3]$，那么 $f(2, 4) = [1, 1, 5]$。

你的任务是计算有多少对 $(l, r)$ 满足 $1 \le l \le r \le x$，并且 $f(l, r)$ 得到的数组是非降序排列的。注意，空数组也被认为是有序的。

## 说明/提示

在第一个测试用例中，满足条件的对为 $(1, 1)$、$(1, 2)$、$(1, 3)$ 和 $(2, 3)$。

在第二个测试用例中，满足条件的对为 $(1, 3)$、$(1, 4)$、$(2, 3)$、$(2, 4)$、$(3, 3)$ 和 $(3, 4)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
2 3 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 4
1 3 1 2 2 4 3
```

### 输出

```
6
```

# 题解

## 作者：_gjm2005_ (赞：5)

我们发现，如果$f(l,r)$可以,那么$f(l,r+1) f(l,r+2) f(l,r + x)$都可以(只要$l,r$在规定范围内)于是我们可以考虑双指针，对于每个$l$，找到一个最小的$r$使其满足条件，当$l$向右移动时$r$也跟着向右移动。

那么怎么判断是否满足条件呢，我们记录以下这些数组

$p_i$表示$i$在原数组出现最早的位置

$q_i$表示$i$在原数组出现最早的位置

$p1_i$表示$i-n$在原数组出现最早的位置

$q1_i$表示$1-i$在原数组出现最晚的位置

我们考虑当$l - 1$移动到$l$时需要满足的条件，因为移动了，所以$l-1$不会被删去。

那么我们就要保证$l - 2$及以下的所有数都在$l-1$左边即$p2[l - 2] < p[l - 1]$

我们考虑当$r$移动到$r + 1$时需要满足的条件，当$q1[l - 1] > p1[r + 1]$即$l-1$以内出现最晚的数大于$r+1$之外出现最早的数，因为此时不满足题意所以才要移动$r$,最后得到的$r$就是最小的满足题意的$r$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
const int inf = INT_MAX;

#define int long long
#define FOR(i,a,b) for(int i = a;i <= b;i++)
#define _FOR(i,a,b) for(int i = a;i >= b;i--)

template<typename T> void read(T &x)
{
    x = 0;int f = 1;
    char c = getchar();
    for(;!isdigit(c);c = getchar()) if(c == '-') f = -1;
    for(;isdigit(c);c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n,k,a[N],p[N],q[N],p1[N],q1[N];
signed main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(n),read(k);
	memset(p,0x3f,sizeof(p));
	FOR(i,1,n)
	{
		read(a[i]);
		if(p[a[i]] > 1e9) p[a[i]] = i;
		q[a[i]] = i;
	}
	FOR(i,1,k)
		q1[i] = max(q1[i - 1],q[i]);
	p1[k] = p[k],p1[k + 1] = 1e9;
	_FOR(i,k - 1,1)
		p1[i] = min(p1[i + 1],p[i]);
	int r = k - 1,ans = 0;
	while(r >= 1 && q[r] < p1[r + 1]) r--;
	//FOR(i,1,n)
		//printf("%lld %lld %lld %lld\n",p[i],q[i],p1[i],q1[i]);
	FOR(l,1,k)
	{
		if(l > 2 && p[l - 1] < q1[l - 2]) break;
		//printf("!!!%lld %lld\n",q1[l - 1],p1[r + 3]);
		while(r <= k && (r < l || q1[l - 1] > p1[r + 1]))
			r++;
		ans += k - r + 1; 
	}
	printf("%lld\n",ans);
    return 0;
}



```

---

## 作者：rhn7 (赞：4)

膜拜大佬们的 $O(n)$ 做法，蒟蒻不才，分享一个卡常才能过的 $O(n\log n)$ 做法。

首先当 $l$ 确定时，$r$ 越小越不容易合法，$r$ 越大越容易合法，而且 $l$ 增加时，$r$ 不会减少（显然你把一个不降的序列删掉几个数还是不降的，但如果增加几个数就不一定了）。

满足上述两个条件就可以双指针了，对每个 $l$ 找最小的 $r$，双指针过程中 $r$ 增加时要把等于 $r$ 的数删除，$l$ 增加时要把等于 $l$ 的数增加。

若我们 $O(n)$ 判断序列是否不降会超时，所以要维护一个容易变化的量，这个量得能判断序列是否不降。大家会先想到逆序对，但动态逆序对复杂度太高了。所以需要维护相邻的顺序对，即 $a_i\le a_{i+1}$ 的 $i$ 个数，如果其等于序列长度减一，那序列不降。

既然是相邻，就要维护每个数往左、右找第一个被选中的数，还得支持增删，可以想到平衡树，要查询的其实就是前驱、后继，但常数太大了过不了。我们用 $c_i$ 表示第 $i$ 个数是否被选，用树状数组维护 $c$ 数组，然后在树状数组上倍增求第 $k$ 大，这样就可以小常数 $O(\log n)$ 查询前驱、后继了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,a[N],r,cnt,c[N];
long long ans;
vector<int> v[N];
inline int lowbit(int x){return x&(-x);}
inline void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=k;
}
inline int sum(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=c[i];
	return res;
}
inline int kth(int k){
	int t=0,tot=0;
	for(int i=20;i>=0;i--){
		t+=(1<<i);
		if(t>n||tot+c[t]>=k) t-=(1<<i);
		else tot+=c[t];
	}
	return t+1;
}
inline int getpre(int x){
	if(!sum(x-1)) return -1;
	return kth(sum(x-1));
}
inline int getnxt(int x){
	if(sum(x)==sum(n)) return -1;
	return kth(sum(x)+1);
}
inline void update(int x,int p){
	int pre=getpre(x),nxt=getnxt(x);
	cnt+=(p?1:-1)*(pre!=-1&&a[pre]<=a[x]);
	cnt+=(p?1:-1)*(nxt!=-1&&a[x]<=a[nxt]);
	cnt+=(p?-1:1)*(pre!=-1&&nxt!=-1&&a[pre]<=a[nxt]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		add(i,1);
		cnt+=(i>1&&a[i]>=a[i-1]);
		v[a[i]].push_back(i);
	}
	int k=n;
	for(int l=1;l<=m;l++){
		while(r<m&&cnt<k-1){
			r++;
			for(int x:v[r]) k--,update(x,0),add(x,-1);
		}
		if(cnt==k-1)ans+=1ll*(m-max(l,r)+1);
		for(int x:v[l]) k++,update(x,1),add(x,1);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：万弘 (赞：4)

删除$[l,r]$中的所有数后，若剩下的是一个单调递增序列，则形如$1..l-1,r+1...x$（允许有些地方没有数）

找一个最小的$suf$，满足$[suf,x]$中的数构成一个单调递增序列。这是很容易在线性时间内求解的：统计每个数的最早位置$first(i)$和最晚位置$last(i)$,倒序考虑每个$i$:若$i$没有出现，那么一定能选；若$last(i)>\max_{j>i}first(j)$那么就结束；否则可以选，并维护一下$\max_{j\ge i}first(j)$。

考虑枚举$l$,并考虑$r$的取值范围。首先若$r<suf-1$,因为$suf$是最小的，所以$[r+1,x]$不是单调递增序列，故有$r\ge suf-1$;同时有$r\ge l,r\ge\max_{j\le last(l-1)}a_j$;另外，$[1,l-1]$需要构成一个单调递增序列，这显然与$suf$的求解类似，维护一下$\max_{j<l}last(j)$即可。

时间复杂度$\mathcal O(n+x)$
```cpp
/**********/
#define MAXN 1000011
ll first[MAXN],last[MAXN],premax[MAXN];
int main()
{
    ll n=read(),m=read();
    for(ll i=1;i<=n;++i)
    {
        ll x=read();
        if(!first[x])first[x]=i;
        last[x]=i;
        premax[i]=max(premax[i-1],x);
    }
    ll suf=m+1,pos=n+1;
    for(ll i=m;i;--i)
    {
        if(!first[i]){suf=i;continue;}
        if(last[i]>pos)break;
        suf=i,pos=first[i];
    }
    ll ans=0,it=0;
    for(ll l=1;l<=m;++l)
    {
        ll r=max(suf-1,l);
        umax(r,premax[it]);
        //printf("r=%lld\n",r);
        ans+=m-r+1;
        if(first[l])
        {
            if(first[l]<it)break;
            it=last[l];
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：DPair (赞：2)

## 【前言】
就我一个菜鸡是用 ST表做的吗。。。似乎一个个跑的都比我快好几倍。。。

## 【思路】
首先大胆猜想这道题和逆序对有关。

实际上它就是问我们有多少个序列 **逆序对个数为零** 。

然后我们看一看逆序对是怎么产生的。

不难发现，如果你 **选了某一个数不删** ，那么所有比它小的数也一定不会被删，这时，如果这个大的数就会和比它小的数产生逆序对，就会导致不符合题意。

因此，我们要保证从小到大每一个 **数值** 的 **最左边那一个** 比所有比它小的数值的 **最右边那一个** 还要右边。

从大到小同理。

这个显然可以 $O(1)$ 查询，（然而我傻乎乎的写了个 ST表）。 

然后我们发现这仅仅只是一个必要条件，比如这个：

```
3 2 1
```

按我们的算法去找，从小到大和从大到小都会认为 $2$ 是第一个不满足的，但同时选 $1,3$ 不删又显然是不合法的。

然后我们发现这东西有单调性。

也就是说，如果删 $[x,y]$ 可行，那么显然删 $[x,y + 1]$ 也可行。如果删 $[x,y]$ 不可行，那么显然删 $[x + 1, y]$ 和 $[x, y + 1]$ 也不可行。

然后就可用双指针 $O(n)$ 跑出结果并统计答案。

然后就做完了。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() printf("I am a cheater!I AK IOI!%c", 10)
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
inline char next_char(){
    char ch = getchar();
    while(ch == 9 || ch == 10 || ch == 32) ch = getchar();
    return ch;
}

template <typename T>
inline T mn(T x, T y) {return x < y ? x : y;}
template <typename T>
inline T mx(T x, T y) {return x > y ? x : y;}
template <typename T>
inline void chmin(T &x, T y) {(x > y) && (x = y);}
template <typename T>
inline void chmax(T &x, T y) {(x < y) && (x = y);}

int n, x;
int l[1000005], r[1000005];
int L[1000005][21], R[1000005][21];
int Luogu[1000005];
int RL, RR;
inline int getL(int ll, int rr){
    if(rr < ll) return 0x3f3f3f3f;
    int num = Luogu[rr - ll + 1];
    return mn(L[ll][num], L[rr - (1 << num) + 1][num]);
}

inline int getR(int ll, int rr){
    if(rr < ll) return -0x3f3f3f3f;
    int num = Luogu[rr - ll + 1];
    return mx(R[ll][num], R[rr - (1 << num) + 1][num]);
}

int main(){
    read(n);read(x);
    for (register int i = 1;i <= n;i ++){
        int a;read(a);
        r[a] = i;
        if(!l[a]) l[a] = i;
    }
    for (register int i = 1;i <= x;i ++){
        if(!l[i]) l[i] = 0x3f3f3f3f;
        if(!r[i]) r[i] = -0x3f3f3f3f;
        L[i][0] = l[i];R[i][0] = r[i];
    }
    for (register int i = 1;i <= 20;i ++){
        for (register int j = 1;j + (1 << i) - 1 <= x;j ++){
            L[j][i] = mn(L[j][i - 1], L[j + (1 << (i - 1))][i - 1]);
            R[j][i] = mx(R[j][i - 1], R[j + (1 << (i - 1))][i - 1]);
        }
    }
    for (register int i = 2;i <= x;i ++) Luogu[i] = Luogu[i >> 1] + 1;
    RL = 1;
    while(RL < x && l[RL] > getR(1, RL - 1)) RL ++;
    RR = x;
    while(RR > 1 && r[RR] < getL(RR + 1, x)) RR --;
    int it = RR + 1;
    long long ans = 0;
    for (register int i = 0;i < RL;i ++){
        while(it <= x && (getL(it, x) <= getR(1, i) || it <= (i + 1))) it ++;
        ans += x - it + 2;
    }
    fprint(ans, 10);
    return 0;
}
```



---

## 作者：81179332_ (赞：2)

显然删的数越多一个序列越可能是不下降序列

那么我们从小到大枚举 $r$，$l$ 单调不减，双指针即可

我们需要维护加入一个数、删除一个数、查询是否合法，我用 `set` 查询前驱后继，用可删堆维护相邻数的差的最小值

我的写法复杂度是对的，没有撤销操作的，但是被卡常了，Time limit exceeded on test 50

还是参考线性做法的题解吧

```cpp
const int N = 1000010;
int n,x;struct data { int pos,v; }a[N];
ll ans;
set<pair<int,int> > s;
struct heap
{
	priority_queue<int,vector<int>,greater<int> > add,del;
	void push(int x) { add.push(x); } void pop(int x) { del.push(x); }
	int size() { return add.size() - del.size(); }
	int top()
	{
		while(add.size() && del.size() && add.top() == del.top()) add.pop(),del.pop();
		return add.top();
	}
}h;
void add(data x)
{
	auto a = s.upper_bound({x.pos,x.v});
	if(a != s.end()) h.push((*a).second - x.v);
	if(a != s.begin())
	{
		auto b = prev(a);
		h.push(x.v - (*b).second);
		if(a != s.end()) h.pop((*a).second - (*b).second);
	}s.insert({x.pos,x.v});
}
void del(data x)
{
	s.erase({x.pos,x.v});
	auto a = s.upper_bound({x.pos,x.v});
	if(a != s.end()) h.pop((*a).second - x.v);
	if(a != s.begin())
	{
		auto b = prev(a);
		h.pop(x.v - (*b).second);
		if(a != s.end()) h.push((*a).second - (*b).second);
	}
}
bool check() { return !h.size() || h.top() >= 0; }
int main()
{
	n = read(),x = read();for(int i = 1;i <= n;i++) a[i].v = read(),a[i].pos = i;
	sort(a + 1,a + 1 + n,[&](data a,data b) { return a.v < b.v; });
	int l = 0,pos = 1;for(int i = 1;i <= n;i++) add(a[i]);
	for(int r = 1;r <= x;r++)
	{
		while(pos <= n && a[pos].v <= r) del(a[pos++]);
		while(l < pos - 1 && check()) add(a[++l]);
		ans += a[l].v;
	}fprint(ans);
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：2)

可删堆+线段树+双指针。

我们发现，由于从一个单调序列里删一些数之后还是单调序列，所以对于一个值域的右端点$r$，合法的$l$一定是总之前某个位置$l_0$开始再往前，$f(l,r)$就都合法了，那么我们就是要对每个右端点求$l_0$。

很显然，随着$r$的递增，$l_0$也是单调不降的，考虑双指针，那么我们就是要支持在当前序列里插入/删除一些数，并且判断它是否为单调序列。

考虑维护相邻两项的差分，如果有一个地方的差分$<0$那么显然不是单调不降的序列，这个用可删堆维护，同时用个线段树来查前驱后继。

（不过这里还有个问题，我们在移动$l_0$指针的时候，先插入一遍，如果发现不合法就要撤回，但是这样撤回的话并没有复杂度的保证……反正我这么写A了……大概可以用别的双指针的实现方式修锅吧）

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#define ll long long
#define ls(_o) (_o<<1)
#define rs(_o) ((_o<<1)|1)
#define inf 1234567890
#define up(_o) data[_o]=data[ls(_o)]+data[rs(_o)]
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333){
			if(c>='0'&&c<='9')break;if(c=='-')goto s;
		}n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}s:while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
		}
	}
	typedef struct _h{
		priority_queue<int> que,del;
		inline void wh(){while(!que.empty()&&!del.empty()&&del.top()==que.top())que.pop(),del.pop();}
		inline int top(){wh();if(que.empty())return(inf);return(-que.top());}
		inline void push(int x){que.push(-x);}
		inline void erase(int x){del.push(-x);}
	}heap;
	vector<int> vec[1000001];
	int ints[1000001],data[4000001],nd[1000001];
	void build(int l,int r,int tree){
		if(l==r){
			nd[l]=tree;data[tree]=1;return;
		}int mid=(l+r)>>1;
		build(l,mid,ls(tree));
		build(mid+1,r,rs(tree));up(tree);
	}
	inline void setpt(int pt,int x){
		data[nd[pt]]=x;
		for(register int i=nd[pt]>>1;i;i>>=1)up(i);
	}
	int getlst(int rl,int rr,int l,int r,int tree){
		if(rl>rr||!data[tree])return(0);
		if(l==r)return(l);
		int mid=(l+r)>>1;
		if(rl==l&&rr==r){
			if(data[rs(tree)])return(getlst(mid+1,r,mid+1,r,rs(tree)));
			return(getlst(l,mid,l,mid,ls(tree)));
		}
		if(rl>mid)return(getlst(rl,rr,mid+1,r,rs(tree)));
		if(rr<=mid)return(getlst(rl,rr,l,mid,ls(tree)));
		int cjr=getlst(mid+1,rr,mid+1,r,rs(tree));
		if(cjr)return(cjr);
		return(getlst(rl,mid,l,mid,ls(tree)));
	}
	int getfst(int rl,int rr,int l,int r,int tree){
		if(rl>rr||!data[tree])return(0);
		if(l==r)return(l);
		int mid=(l+r)>>1;
		if(rl==l&&rr==r){
			if(data[ls(tree)])return(getfst(l,mid,l,mid,ls(tree)));
			return(getfst(mid+1,r,mid+1,r,rs(tree)));
		}
		if(rl>mid)return(getfst(rl,rr,mid+1,r,rs(tree)));
		if(rr<=mid)return(getfst(rl,rr,l,mid,ls(tree)));
		int cjr=getfst(rl,mid,l,mid,ls(tree));
		if(cjr)return(cjr);
		return(getfst(mid+1,rr,mid+1,r,rs(tree)));
	}
	void ywymain(){
		int n=get(),x=get();
		for(register int i=1;i<=n;i++)vec[ints[i]=get()].push_back(i);build(1,n,1);
		heap global;
		for(register int i=1;i<n;i++)global.push(ints[i+1]-ints[i]);
		ll ans=0;int ptr=0;
		unsigned char bswitch=0;
		for(register int i=1;i<=x;i++){
			for(register int j=0;j<vec[i].size();j++){
				int pre=getlst(1,vec[i][j]-1,1,n,1),nxt=getfst(vec[i][j]+1,n,1,n,1);
				if(pre)global.erase(i-ints[pre]);
				if(nxt)global.erase(ints[nxt]-i);
				if(pre&&nxt)global.push(ints[nxt]-ints[pre]);
				setpt(vec[i][j],0);
			}
			if(global.top()>=0)bswitch=1;
			if(bswitch){
				ans++;while(ptr+1<i){
					for(register int j=0;j<vec[ptr+1].size();j++){
						int pre=getlst(1,vec[ptr+1][j]-1,1,n,1),nxt=getfst(vec[ptr+1][j]+1,n,1,n,1);
						if(pre)global.push(ptr+1-ints[pre]);
						if(nxt)global.push(ints[nxt]-ptr-1);
						if(pre&&nxt)global.erase(ints[nxt]-ints[pre]);
						setpt(vec[ptr+1][j],1);
					}
					if(global.top()>=0)ptr++;
					else{
						for(register int j=(int)vec[ptr+1].size()-1;j>=0;j--){
							int pre=getlst(1,vec[ptr+1][j]-1,1,n,1),nxt=getfst(vec[ptr+1][j]+1,n,1,n,1);
							if(pre)global.erase(ptr+1-ints[pre]);
							if(nxt)global.erase(ints[nxt]-ptr-1);
							if(pre&&nxt)global.push(ints[nxt]-ints[pre]);
							setpt(vec[ptr+1][j],0);
						}break;
					}
				}
				ans+=ptr;
			}
		}
		cout<<ans<<endl;
	}
}
int main(){
	ywy::ywymain();return(0);
}
```

---

## 作者：BangxingPeng2024 (赞：1)

# **本题考察数据结构，是一道很好的推过程的题**

## **视频题解：![戳这里](bilibili:BV1jJ4m1G7GE)**

###### 感谢@wuliwulii提供技术支持

---------------------------------------

## **题目分析**

**题意：**
有一个长度为
n
的数组
$a_1,a_2,\dots a_n(1\le a_i\le x)$
，并删除a中权值在
$[l,r]$
的数，统计不下降序列的数对
$(l,r)$
的数量。

观察样例
2
：

```
7 4
1 3 1 2 2 4 3
```
先从第二行的第一个1开始。

- 假如一定要删除
  $l = 1$
  ，（要想满足题意）
  $r$
  不能等于
  $1/2$
   ，能等于
  $3/4$
  ，**有两个满足条件**。
- 假如
  $l = 2$
  ，
  $r$
  能等于
  $3/4$
  ，**有两个满足条件**。
- 假如
  $l = 3$
  ，权值
  $1/2$
  被保留，
  $r$
  能等于
  $3/4$
   ，**有两个满足条件**。
- 假如
  $l = 4$
  ，权值
  $1/2/3$
  被保留，
  $a_3$
  最早出现的位置早于其最晚出现的位置
  $r$
  无解，**没有满足条件**。

总结：当固定
$l$
时，找到最先必须删除的点，则从
$r$
到
$x$
都是可以删除的点。**既可以删除小区间，更可以删除大区间。**

---------------------------------------

**可以发现以下规律：**

- 枚举
  $l$
  时，要求
  $1$
  到
  $(l-1)$
  满足条件
  $(r>l)$
  。
- 确定“最早删除”的数：删去$[l,r]$权值范围，保留
  $[r+1,x]$
  范围内。
  1. 保留的数不能在
     $[1,l-1]$
     之前。
  3. 保留的数本身满足非严格不下降。

**解题步骤如下：**

1. **保留
   $l-1$
   这个数**，使得
   $[1,l-2]$
   肯定满足条件，
   $l-1$
   最早出现在
   $[1,l-2]$
   最晚出现数之后，**使
   $l-1$
   该数存在**。
3. 找最小的满足条件的$r$（最小权值），删去出现在
   $[1,l-1]$
   之前的“更大”数。并进行预处理，使
   $[r+1,x]$
   这些数合理。

## **满分代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int n, x , a[maxn], fir[maxn], las[maxn], prem[maxn];
int main() {
    scanf("%d%d", &n, &x);
    for(int i = 1; i <= n; i ++) {
    	scanf("%d", &a[i]);
    	las[a[i]] = i;
    	if(!fir[a[i]]) fir[a[i]] = i;
    	prem[i] = max(prem[i - 1], a[i]);
    }
    int p = x - 1, min_pos = fir[x];
    for(int i = x - 1; i >= 1; i --) {
    	p = i;
    	if(min_pos && las[i] > min_pos) break;
    	if(!min_pos) min_pos = fir[i];
    	if(fir[i]) min_pos = min(fir[i], min_pos);
    }
    int last_pos = 0, fbi_pos = 0;
    long long ans = 0;
    for(int l = 1, r = 1; l <= n; l ++) {
    	if(l - 2 >= 1) last_pos = max(last_pos, las[l - 2]);
    	if(l - 1 >= 1 && fir[l - 1] && fir[l - 1] < last_pos) break;
    	if(l - 1 >= 1) fbi_pos = max(fbi_pos, las[l - 1]);
    	r = max(r, l);
    	r = max(r, p);
    	r = max(r, prem[fbi_pos]);
    	ans += x - r + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF1167E Range Deleting
## 题目翻译
给定长度为 $n$ 的数组，定义 $f(l,r)$ 是删除值域为 $[l,r]$ 的数后剩余数组，求有多少组 $(l,r)$ 使得 $f(l,r)$ 是单调不下降序列。
## 从暴力到正解
我们首先考虑暴力枚举 $l,r$ 再暴力 check，那么时间复杂度就是 $O(n^3)$ 的。\
我们注意到其实假设 $[l,r]$ 是一个可行区间，那么 $[l,r+1]$ 也一定是一个可行区间，因为在一个不下降序列里无论删除什么数都还剩下一个不下降序列。\
所以我们可以优化一下我们原来的暴力，确定了左区间后我们二分第一个合法的右端点，这样的复杂度就被优化成了 $O(n^2\log n)$。\
我们进一步考虑，对于 $l,l+1$ 来说，它们的第一个合法右端点 $r_l,r_{l+1}$ 一定满足 $r_l\le r_{l+1}$。因为若 $r_l>r_{l+1}$，那么说明 $[l,r_{l+1}]$ 是不合法的而 $[l+1,r_{l+1}]$ 是合法的。通过上一步的优化我们同理可以得到若确定了右端点，左端点的合法性也应该是单调的，所以这种情况是不会存在的。\
那么我们就可以利用双指针把复杂度优化到 $O(n^2)$。\
我们继续考虑左端点从 $l\rightarrow l+1$ 的过程，实际上相当于只加入了 $l$，那我们其实只需要考虑加入 $l$ 会使 $r$ 向右移动多少即可。\
首先若加入 $l$ 会使值域 $[1,l]$ 的数不满足不下降，那么即使 $r=n$ 也一定不合法，此时后面的 $l,r$ 一定都不合法。\
那么若 $[1,l]$ 合法，删除 $[l+1,r]$ 不合法的情况只有两种：
1. $l+1>r$。
2. 有至少一个 $l+1$ 比 $[r+1,n]$ 里的某一个数晚出现。

针对第一种情况是好判断的，第二种情况我们贪心地想，若出现这种情况，最可能的就是 $l+1$ 里出现最晚的一个比 $[r+1,n]$ 里出现最早的一个出现晚。若这种情况都合法那其他情况更合法了。\
所以我们可以提前预处理后缀出现最早的位置和每个元素最晚出现的位置，这样就可以做到 $O(n)$ 的复杂度完成。\
仅仅如此吗？\
这个题有个比较麻烦的点在于中间可能有未出现的元素。\
此时我们无法确定其最早出现的位置，但是我们思考一下会发现其实无所谓，删除一个空元素不会对序列产生影响，因为原来是合法的，所以现在也肯定合法。此时只需要满足 $l\le r$ 即可。\
现在还有一个小问题，$l=1$ 时的 $r$ 如何确定，这个直接仿照前面的操作从后往前找到最后一个不合法的位置即可。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+666;
int n,x,a[N],ans;
bool vis[N];
vector<int>vec[N];
int pre[N],suf[N];
bool check(int l,int r){
    if(r>x)return 1;
    return r>=l&&suf[r+1]>=vec[l-1][vec[l-1].size()-1];
}
signed main(){
    cin>>n>>x;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        vec[a[i]].push_back(i);
        vis[a[i]]=1;
    }
    suf[x+1]=n+1;
    for(int i=x;i>=1;--i){
        if(!vis[i])suf[i]=suf[i+1];
        else suf[i]=min(suf[i+1],vec[i][0]);
    }
    for(int i=1;i<=x;++i){
        if(!vis[i])pre[i]=pre[i-1];
        else pre[i]=max(pre[i-1],vec[i][vec[i].size()-1]);
    }
    int l=1,r=x;
    while(r>1&&(!vis[r]||suf[r+1]>=vec[r][vec[r].size()-1])){
        --r;
    }
    ans+=x-r+1;
    for(l=2;l<=x;++l){
        if(!vis[l-1]){
            while(r<l)++r;
            ans+=x-r+1;continue;
        }
        if(vec[l-1][0]<pre[l-2])break;
        while(!check(l,r))++r;
        if(r>x)break;
        ans+=x-r+1;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

