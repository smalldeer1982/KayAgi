# AI robots

## 题目描述

In the last mission, MDCS has successfully shipped $ N $ AI robots to Mars. Before they start exploring, system initialization is required so they are arranged in a line. Every robot can be described with three numbers: position ( $ x_i $ ), radius of sight ( $ r_i $ ) and IQ ( $ q_i $ ).

Since they are intelligent robots, some of them will talk if they see each other. Radius of sight is inclusive, so robot can see other all robots in range $ [x_i - r_i, x_i + r_i] $ . But they don't walk to talk with anybody, but only with robots who have similar IQ. By similar IQ we mean that their absolute difference isn't more than $ K $ .

 Help us and calculate how many pairs of robots are going to talk with each other, so we can timely update their software and avoid any potential quarrel.

## 说明/提示

The first robot can see the second, but not vice versa. The first robot can't even see the third. The second and the third robot can see each other and their IQs don't differ more than 2 so only one conversation will happen.

## 样例 #1

### 输入

```
3 2
3 6 1
7 3 10
10 5 8
```

### 输出

```
1```

# 题解

## 作者：p_b_p_b (赞：20)

[$$\large \color{purple} My\;Blog$$](https://www.cnblogs.com/p-b-p-b/p/10361614.html)

------------

简单的CDQ分治题。

由于对话要求互相看见，无法简单地用树套树切掉，考虑CDQ分治。

按视野从大到小排序，这样只要右边能看见左边就可以保证互相看见。

发现$K$固定，那么左右按智商排序、位置离散化之后可以$two\;pointers$一下，套个树状数组，就做完了。

由于复杂度瓶颈在树状数组，没必要归并，可以直接$sort$。

复杂度应该是$O(n\log^2 n)$。

-------------

```cpp
#include<bits/stdc++.h>
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define sz 301001
	typedef long long ll;
	template<typename T>
	inline void read(T& t)
	{
		t=0;char f=0,ch=getchar();
		double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.')
		{
			ch=getchar();
			while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();
		}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>
	inline void read(T& t,Args&... args){read(t); read(args...);}
	void file()
	{
		#ifndef ONLINE_JUDGE
		freopen("a.txt","r",stdin);
		#endif
	}
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n,K;
ll ans;
int A[sz];
struct hh{int p,l,r,q,len;}a[sz];
inline bool cmp(const hh &x,const hh &y){return x.len>y.len;}
inline bool cmp2(const hh &x,const hh &y){return x.q<y.q;}

int sum[sz];
void add(int x,int v){while (x<=n) sum[x]+=v,x+=(x&(-x));}
int query(int x){int ret=0;while (x) ret+=sum[x],x-=(x&(-x));return ret;}
int query(int l,int r){return query(r)-query(l-1);}

void solve(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid);solve(mid+1,r);
	int L=l,R=l-1;
	rep(i,mid+1,r)
	{
		while (L<=mid&&a[i].q-a[L].q>K) add(a[L].p,-1),++L;
		while (R<mid&&a[R+1].q-a[i].q<=K) ++R,add(a[R].p,1);
		ans+=query(a[i].l,a[i].r);
	}
	rep(i,L,R) add(a[i].p,-1);
	sort(a+l,a+r+1,cmp2);
}

int main()
{
	file();
	read(n,K);
	int c;
	rep(i,1,n) read(a[i].p,a[i].len,a[i].q),A[i]=a[i].p;
	sort(A+1,A+n+1);c=unique(A+1,A+n+1)-A-1;
	rep(i,1,n) 
		a[i].l=lower_bound(A+1,A+c+1,a[i].p-a[i].len)-A,
		a[i].r=upper_bound(A+1,A+c+1,a[i].p+a[i].len)-A-1,
		a[i].p=lower_bound(A+1,A+c+1,a[i].p)-A;
	sort(a+1,a+n+1,cmp);
	solve(1,n);
	cout<<ans;
	return 0;
}
```



---

## 作者：liangbowen (赞：17)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1045G)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16814716.html)

和模版稍有不同的 cdq 分治。

## 思路

cdq 是离线算法，所以我们可以先给 $x_i$ 离散化一下。

同时，记录下 $(x_i - r_i)$ 与 $(x_i + r_i)$ 离散化后对应的结果，即视野范围。

然后，按视野范围从大到小排序。接着就是 cdq 分治了。

---

假设已经处理好了 $[l, mid]$ 与 $[mid + 1, r]$ 的区间。

现在来到了 cdq 分治的重点部分：处理在 $[l, mid]$ 与 $[mid + 1, r]$ 两个不同区域的机器人。

我们可以再对两个分治区间的智商从小到大排序。

这样，单独看一个子区间，显然具有单调性（废话，都排好序了），于是就可以用 $\text{two pointers}$ 来解决了。

实现上有点类似尺取法。对于每个 $i$ 从 $mid + 1 \to r$，双指针维护 iq 值可以交流的区间。

对于每一个 $i$，双指针维护完后，统计区间里有多少个数，位置在 $[x_i - r_i, x_i + r_i]$ 里面即可。

这一点可以用树状数组实现。因此，时间复杂度 $O(n \log^2 n)$。正常的 cdq 可以很轻松的通过 $N = 10^5$。

## 代码

分治区间对 iq 排序时，使用归并排序，更加迅速。

由于时间瓶颈在 $\text{two pointers}$ 那一块，所以直接 `sort` 也可以。

直接 `sort` 的代码可以看：[pb 学长的题解](https://www.cnblogs.com/p-b-p-b/p/10361614.html)。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5 + 5;
struct Data {int pos, lpos, rpos, iq, R;} a[N], t[N];
int x[N], unq[N];
bool cmp(Data p, Data q) {return p.R > q.R;}
int n, k;
LL ans;

int idx[N]; //树状数组板子
int lowbit(int x) {return x & -x;}
void update(int i, int k) {for (; i <= n; i += lowbit(i)) idx[i] += k;}
int query(int i)
{
	int sum = 0;
	for (; i; i -= lowbit(i)) sum += idx[i];
	return sum;
}
int sum(int i, int j) {return query(j) - query(i - 1);}

void MergeSort(int l, int r) //cdq 分治！
{
	if (l >= r) return;
	int mid = (l + r) >> 1;
	MergeSort(l, mid), MergeSort(mid + 1, r);
	int L = l, R = l - 1; //类似尺取法，利用 k 的有序性不断更新 L 和 R
	for (int i = mid + 1; i <= r; i++)
	{
		while (L <= mid && a[i].iq - a[L].iq > k) update(a[L++].pos, -1);  //过时了就减掉
		while (R < mid && a[R + 1].iq - a[i].iq <= k) update(a[++R].pos, 1); //可以接受就加入
		ans += sum(a[i].lpos, a[i].rpos); //统计视野内可见的机器人个数
	}
	for (int i = L; i <= R; i++) update(a[i].pos, -1); //清空 
	
	int i = l, j = mid + 1; //归并排序
	int cur = 0;
	while (i <= mid && j <= r)
		if (a[i].iq <= a[j].iq) t[++cur] = a[i], i++;
		else t[++cur] = a[j], j++;
	while (i <= mid) t[++cur] = a[i], i++;
	while (j <= r) t[++cur] = a[j], j++;
	for (i = l, j = 1; j <= cur; i++, j++) a[i] = t[j];
}
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &x[i], &a[i].R, &a[i].iq), unq[i] = x[i];
	sort(unq + 1, unq + n + 1); //离散化ing 
	int m = unique(unq + 1, unq + n + 1) - unq - 1;
	for (int i = 1; i <= n; i++)
	{
		a[i].pos = lower_bound(unq + 1, unq + m + 1, x[i]) - unq;
		a[i].lpos = lower_bound(unq + 1, unq + m + 1, x[i] - a[i].R) - unq;
		a[i].rpos = upper_bound(unq + 1, unq + m + 1, x[i] + a[i].R) - unq - 1;
	}
	sort(a + 1, a + n + 1, cmp);
	MergeSort(1, n);
	printf("%lld", ans);
	return 0;
}
```

希望能帮助到大家！

---

## 作者：shadowice1984 (赞：15)

zz的布星啊……经rqy指点一番才做了这题

~~rqy是我们的红太阳,没有他我们就会死~~
____________________

# 本题题解

既然有翻译了我就不再重新复述题意了

那么我们来看既然一对机器人只会被数一次，那么我们就有三种选择了

1.让智商高的数智商低的

2.让看的近的数看的远的

3.让靠右的数靠左的

然后我们会发现更好的选择是选择2,为什么呢?

因为你发现如果我们使用方法1或者方法3进行计数的话，我们都有一个相当难受的问题就是我们需要让两个机器人可以互相看见，而这两个机器人的视野是不同的……，此时你就会发现你可能需要相当复杂的树套树技巧才可以解决这题

然而我们让看的近的数看的远的会发生什么情况呢？

你会发现一个相当有趣的事实就是只要这个机器人能看到的就一定可以看到它

两个机器人互相可以看见的问题转化成了一个机器人可以看到另一个的问题

此时我们就相当好做这题咯

我们先把所有机器人按照视野范围倒序排序

然后我们相当于对于每一个机器人统计一下它可以和在他之前的几个机器人交流，由于排序已经帮我们解决了一维限制了，因此我们就是要统计有多个机器人的$x$坐标在当前机器人的$[x-r,x+r]$之间且这个机器人的$q$值在当前机器人的$[q-k,q+k]$之间

那么这个东西就是一个普通的矩形查询问题，我们将$(x,q)$视为二维平面上的一个点的话，我们发现我们需要兹次的操作就是单点加二维矩形查询

如果你够无脑的话可以写树套树，不过你发现这题的第二维相当的小(只有40)

因此我们可以直接每个q值开一个动态开点线段树，然后每次暴力的扫一遍求个和就可以解决这道题了

上代码~

```C
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;const int N=1e5+10;typedef long long ll;
int n;int k;map <int,int> mp;int S;ll res;
struct linetree//简易动态开点线段树 
{
    map <int,int> rot;int s[22*N][2];int v[22*N];int ct;
    inline void ins(int p,int l,int r,int pos)
    {
        v[p]++;if(r-l==1){return;}int mid=(l+r)/2;
        if(pos<=mid)ins(s[p][0]=s[p][0]?s[p][0]:++ct,l,mid,pos);
        else ins(s[p][1]=s[p][1]?s[p][1]:++ct,mid,r,pos);
    }
    inline int qry(int p,int l,int r,int dl,int dr)
    {
        if((dl==l&&dr==r)||p==0){return v[p];}int mid=(l+r)/2;int res=0;
        if(dl<mid)res+=qry(s[p][0],l,mid,dl,min(dr,mid));
        if(mid<dr)res+=qry(s[p][1],mid,r,max(dl,mid),dr);return res;
    }
    inline void cins(int q,int x)
    {if(rot.count(q)==0)rot[q]=++ct;ins(rot[q],0,S,x);}
    inline int cqr(int q,int dl,int dr)
    {if(rot.count(q)==0)return 0;return qry(rot[q],0,S,dl,dr);}
}lt;
struct data//排序 
{int x;int r;int q;friend bool operator <(data a,data b){return a.r>b.r;}}a[N];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].x,&a[i].r,&a[i].q);sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){mp[a[i].x]=1;mp[a[i].x+a[i].r]=1;mp[a[i].x-a[i].r]=1;}
    map <int,int> :: iterator it,it1;
    for(it=mp.begin(),it1=it,++it1;it1!=mp.end();++it,++it1)it1->second+=it->second;
    S=mp.size();
    //for(it=mp.begin();it!=mp.end();++it)printf("(%d,%d) ",it->first,it->second);printf("\n");
    for(int i=1;i<=n;i++)//暴力统计一下就没了 
    {
        for(int j=a[i].q-k;j<=a[i].q+k;j++)res+=lt.cqr(j,mp[a[i].x-a[i].r]-1,mp[a[i].x+a[i].r]);
        lt.cins(a[i].q,mp[a[i].x]);
    }printf("%I64d",res);return 0;//拜拜程序~ 
}
```

---

## 作者：寒鸽儿 (赞：7)

首先注意到$k <= 20$  
这暗示我们可以按照iq值分类统计数据  
通常都是统计当前的点与之前的点的关系  
当前的点肯定是在iq允许下查找$[x - r, x + r]$范围内的值  
但是之前的点的范围有没有$x$是不知道的  
为了保证我们在当前点的区域内统计到的点的范围都包含$x$,将范围$r$降序排序即可  
这样子我们就应该想到用权值线段树存储已经访问过的点的下标  
把iq离散化,然后对每种iq开一棵线段树,对于每个点的查询都是在iq范围内,最多不超过$2k$棵线段树  
令$m$为下标的值域大小,复杂度$O(knlogm)$
```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#define itra map<int,int>::iterator
#define ll long long

using namespace std;

const int N = 100010, SIZE = N * 36;
int dat[SIZE], ls[SIZE], rs[SIZE], root[SIZE], tot = 1;
inline int newnode() {
	ls[tot] = rs[tot] = 0;
	return tot++;
}

inline void update(int p) {
	dat[p] = dat[ls[p]] + dat[rs[p]];
}

inline void insert(int p, int lp, int rp, int x) {
	if(lp == rp) {
		++dat[p];
		return;
	}
	int mid = (lp + rp) >> 1;
	if(x <= mid) {
		if(!ls[p]) ls[p] = newnode();
		insert(ls[p], lp, mid, x);
	} else {
		if(!rs[p]) rs[p] = newnode();
		insert(rs[p], mid + 1, rp, x);
	}
	update(p);
}

inline int qry(int p, int lp, int rp, int l, int r) {
	if(l <= lp && rp <= r) return dat[p];
	int mid = (lp + rp) >> 1;
	int ans = 0;
	if(l <= mid && ls[p]) ans += qry(ls[p], lp, mid, l, r);
	if(r > mid && rs[p]) ans += qry(rs[p], mid + 1, rp, l, r);
	return ans;
}

struct Rob {
	int x, r, q;
	Rob() {}
	Rob(int X, int R, int Q): x(X), r(R), q(Q) {}
}rob[N];
bool cmp1(Rob a, Rob b) { return a.r > b.r; }
map<int, int> iqidx;
int iqval[N], iqnum;

int main() {
	int n, k, x, r, q, maxx = 0;
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d %d %d", &x, &r, &q);
		rob[i] = Rob(x, r, q);
		iqval[i] = q;
		maxx = max(x, maxx);
	}
	sort(rob + 1, rob + n + 1, cmp1);
	sort(iqval + 1, iqval + n + 1);
	iqnum = unique(iqval + 1, iqval + n + 1) - iqval - 1;
	for(int i = 1; i <= iqnum; ++i) {
		root[i] = newnode();
		iqidx[iqval[i]] = i;
	}
	ll ans = 0;
	for(int i = 1; i <= n; ++i) {
		int qval = rob[i].q, qid = iqidx[qval];
		x = rob[i].x; r = rob[i].r;
		for(int i = qid; ~i && qval - iqval[i] <= k; --i) {
			ans += qry(root[i], 1, maxx, x - r, x + r);
		}
		for(int i = qid + 1; i <= iqnum && iqval[i] - qval <= k; ++i) {
			ans += qry(root[i], 1, maxx, x - r, x + r);
		}
		insert(root[qid], 1, maxx, x);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Sol1 (赞：4)

给个不一样的做法，不依赖 $k\leq 20$。

~~我才不会告诉你这个是我化学中考的时候想出来的。~~

考虑忽略 $q$ 的限制，给定一个机器人集合，再给定另外一个机器人，如何查询这个机器人能够看到多少个机器人。

有如下方法：对于该集合内的所有机器人 $(x_i,r_i)$，在二维平面上添加一条平行于 $y$ 轴的线段 $(x_i,x_i-r_i)-(x_i,x_i+r_i)$。对于给定的机器人 $(X,R)$，求平行于 $x$ 轴的线段 $(X-R,X)-(X+R,X)$ 上面的交点个数即可。

现在引入 $q$ 的限制，可以把机器人按 $q$ 排序之后双指针维护出查询一个机器人能看到的数量时对应的被看到的机器人集合。再通过上述方法，问题被转化为动态加入和删除平行于 $y$ 轴的线段，以及给定平行于 $x$ 轴线段查询交点数量。

如果问题是静态的，即给定的 $y$ 轴线段不被修改，则可以对修改线段差分后在 $y$ 轴上扫描线解决。动态后直接在扫描线上套 cdq 分治，复杂度为 $O(n\log^2n)$。

看起来常数很大，但跑起来还是蛮快的，cf 上最大点 481ms。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

struct Bot {
	int x, r, q;
	bool operator < (const Bot& b) const {
		return q < b.q;
	}
};
struct Opt {
	int type, x, yl, yr;
	Opt() {}
	Opt(int type, int x, int yl, int yr) : type(type), x(x), yl(yl), yr(yr) {}
};
Opt opt[500005], tmp[500005];
int n, k, q, vtop, c[1500005];
long long ans = 0, val[1500005];
Bot a[100005];
int top = 0;

inline void Read() {
	n = qread(); k = qread();
	for (int i = 1;i <= n;i++) {
		a[i].x = qread();
		a[i].r = qread();
		a[i].q = qread();
	}
}

inline void Prefix() {
	int l = 1, r = 1;
	for (int i = 1;i <= n;i++) {
		while (r <= n && a[r].q <= a[i].q + k) {
			opt[++q] = Opt(1, a[r].x - a[r].r, a[r].x, a[r].x);
			opt[++q] = Opt(-1, a[r].x + a[r].r + 1, a[r].x, a[r].x);
			r++;
		}
		while (l <= n && a[l].q < a[i].q - k) {
			opt[++q] = Opt(-1, a[l].x - a[l].r, a[l].x, a[l].x);
			opt[++q] = Opt(1, a[l].x + a[l].r + 1, a[l].x, a[l].x);
			l++;
		}
		//printf("%d [%d,%d] %d\n", i, l, r, a[r].q);
		opt[++q] = Opt(0, a[i].x, a[i].x - a[i].r, a[i].x + a[i].r);
	}
	for (int i = 1;i <= q;i++) {
		val[i] = opt[i].yl;
		val[i + q] = opt[i].yr;
		val[i + 2 * q] = opt[i].x;
	}
	sort(val + 1, val + 3 * q + 1);
	vtop = unique(val + 1, val + 3 * q + 1) - val - 1;
	for (int i = 1;i <= q;i++) {
		opt[i].yl = lower_bound(val + 1, val + vtop + 1, opt[i].yl) - val;
		opt[i].yr = lower_bound(val + 1, val + vtop + 1, opt[i].yr) - val;
		opt[i].x = lower_bound(val + 1, val + vtop + 1, opt[i].x) - val;
	}
	//for (int i = 1;i <= q;i++) printf("%d %d %d %d\n", opt[i].type, opt[i].x, opt[i].yl, opt[i].yr);
}

inline int Lowbit(int x) {
	return x & -x;
}

inline void Update(int i, int x) {
	for (int j = i;j <= vtop;j += Lowbit(j)) c[j] += x;
}

inline int Query(int i) {
	int ans = 0;
	for (int j = i;j >= 1;j -= Lowbit(j)) ans += c[j];
	return ans;
}

inline void Clear(int i) {
	for (int j = i;j <= vtop;j += Lowbit(j)) {
		if (!c[j]) break;
		c[j] = 0;
	}
}

inline void Cdq(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	Cdq(l, mid);
	Cdq(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (opt[i].x <= opt[j].x) {
			if (opt[i].type) Update(opt[i].yl, opt[i].type);
			//else ans += sgt.Query(sgt._root, -1e9, 2e9, opt[i].yl, opt[i].yr);
			tmp[k++] = opt[i++];
		} else {
			if (!opt[j].type) ans += Query(opt[j].yr) - Query(opt[j].yl - 1);
			tmp[k++] = opt[j++];
		}
	}
	while (i <= mid) {
		if (opt[i].type) Update(opt[i].yl, opt[i].type);
		//else ans += sgt.Query(sgt._root, -1e9, 2e9, opt[i].yl, opt[i].yr);
		tmp[k++] = opt[i++];
	}
	while (j <= r) {
		if (!opt[j].type) ans += Query(opt[j].yr) - Query(opt[j].yl - 1);
		tmp[k++] = opt[j++];
	}
	for (int i = l;i <= mid;i++) Clear(opt[i].yl);
	for (int i = l;i <= r;i++) opt[i] = tmp[i];
}

int main() {
	Read();
	sort(a + 1, a + n + 1);
	Prefix();
	Cdq(1, q);
	printf("%lld", (ans - n) / 2);
	#ifdef CFA_44
	while (1);
	#endif
	return 0;
}
```

---

## 作者：ReseeCher (赞：3)

这里给一种不用任何高级数据结构和算法的做法，用玄学vector水过去

首先将机器人按视野从小到大排序，对于机器人$i$考虑能匹配多少视野比它大的机器人

因为$K$很小，所以直接枚举匹配对象的智商值$Q$，这样问题就转化成了“有多少智商为$Q$的机器人位置在$[x_i-r_i,x_i+r_i]$”

可以写数据结构~~但没必要~~

考虑对于每个存在的智商开一个vector，将机器人的位置有序的塞在vector里，这样就可以方便的用两个lower_bound来解决以上问题（用末尾位置减去起始位置就是中间的元素个数）

在统计完机器人$i$后把它从vector中删除，就能保证维护的机器人始终视野比统计的机器人大了

再偷懒用map解决掉离散化，代码就非常简单了

复杂度$O(NKlogN)$

什么？vector的删除是$O(N)$的，所以是$O(N^2)$？

vector的insert和erase有玄学常数，实测在O2前提下将1e5个数按随机位置插入到vector中再按随机位置删除，主流环境下1s内过是妥妥的

在飞快的机子上能卡过2e5（1s）

所以复杂度 O(稳能过)

```
#include<bits/stdc++.h>
#define LL long long
#define F(x,y,z) for(int x=y;x<=z;++x)
using namespace std;
const int N=100010;
LL R(){
    LL ans=0,f=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if (c=='-') f=-1;
    for(;c>='0'&&c<='9';c=getchar()) ans=ans*10+c-'0';
    return ans*f;
}

int n,K,cnt;LL ans;
map<int,int> ys;
vector<int> v[N];

struct Robot{
	int p,r,q,id;
	void In(){
		p=R(),r=R(),q=R();
		if(!ys[q])ys[q]=++cnt;
		id=ys[q];
	}
}q[N];
bool cmpr(Robot a,Robot b){return a.r<b.r;}
bool cmpp(Robot a,Robot b){return a.p<b.p;}
void Sol(int p,int l,int r){
	if(!ys.count(p))return;
	int id=ys[p];
	ans+=lower_bound(v[id].begin(),v[id].end(),r+1)-lower_bound(v[id].begin(),v[id].end(),l);
}

int main(){
	n=R();K=R();
	F(i,1,n)q[i].In();
	sort(q+1,q+1+n,cmpp);
	F(i,1,n)v[q[i].id].push_back(q[i].p);
	sort(q+1,q+1+n,cmpr);
	F(i,1,n){
		v[q[i].id].erase(lower_bound(v[q[i].id].begin(),v[q[i].id].end(),q[i].p));
		F(k,q[i].q-K,q[i].q+K)
			Sol(k,q[i].p-q[i].r,q[i].p+q[i].r);
	}
	cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：hgzxwzf (赞：2)

**cdq 分治**。
## 解题思路
------------

- cdq 分治的双指针扫描法：

前提：不一定满足单指针扫描法的第一个前提，但满足第二个前提。

开始两个指针 $L$ 和 $R$ 分别指向 $l$ 和 $l-1$，也就是说维护一个区间。

当 $L$ 与 $i$ 不满足关于 $b$ 的大小关系，那么我们就让 $L$ 指向 $L+1$；

当 $R+1$ 与 $i$ 满足关于 $b$ 的大小关系且 $R<mid$，那么我们就让 $R$ 指向 $R+1$。

------------

回到本题，对于距离的处理，直接离散化，然后求每个机器人能看到的最左边的机器人和最右边的机器人。

再根据机器人视野从大到小排序，这样右边的机器人能看到左边，每次只统计右边的机器人所贡献的答案，既做到了不重，又做到了不漏。

左边的机器人一定能看到右边，局部按智商排序，通过智商的单调性再用双指针统计答案。

```cpp
#include<cstdio>
#include<algorithm>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
using namespace std;
const int N=1e5+10;
struct node
{
	int l,r,x,q,s; 
}no[N];
struct robots
{
	int x,r,q;
}ro[N];
int lis[N];
long long ans;
int t[N],n,k;
inline void add(int i,int x) {while(i<=n) t[i]+=x,i+=i&-i;}
inline int query(int i) {int sum=0;while(i) sum+=t[i],i-=i&-i;return sum;}
bool comp(const node &P,const node &Q) {return P.s>Q.s;}
bool comp2(const node &P,const node &Q) {return P.q<Q.q;}
void CDQ(int l,int r)
{
	if(l==r) return ;
	int mid=l+r>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	sort(no+l,no+mid+1,comp2);//按智商排序
	sort(no+mid+1,no+r+1,comp2);
	int L=l,R=l-1;
	rep(i,mid+1,r)
	{
		while(L<=mid&&no[i].q-no[L].q>k) add(no[L++].x,-1);
		while(R<mid&&no[R+1].q-no[i].q<=k) add(no[++R].x,1);
		ans+=query(no[i].r)-query(no[i].l-1);
	}
	rep(i,L,R) add(no[i].x,-1);
}
int main()
{
	scanf("%d%d",&n,&k);
	rep(i,1,n) scanf("%d%d%d",&ro[i].x,&ro[i].r,&ro[i].q),lis[i]=ro[i].x;
	sort(lis+1,lis+1+n);
	int tot=unique(lis+1,lis+1+n)-lis-1;
	rep(i,1,n)
	{
		no[i].l=lower_bound(lis+1,lis+1+tot,ro[i].x-ro[i].r)-lis;
		no[i].r=upper_bound(lis+1,lis+1+tot,ro[i].x+ro[i].r)-lis-1;
		no[i].x=lower_bound(lis+1,lis+1+tot,ro[i].x)-lis;
		no[i].q=ro[i].q;
		no[i].s=ro[i].r;
	}
	sort(no+1,no+1+n,comp);//按视野排序
	CDQ(1,n);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：ExplodingKonjac (赞：2)

### [原题链接](https://www.luogu.com.cn/problem/CF1045G)

本蒟蒻不会cdq分治qwq，写一个不同的解法。

## 解题思路

首先将问题转化为，对于每一个机器人，有多少个机器人可以和它对话。

然后这里有两个限制条件：智商 $q_i-K\le q_j\le q_i+K$，位置 $x_i-r_i\le x_j\le x_i+r_i$，这似乎是树套树的模板题。然而：

> Since they are intelligent robots, some of them will talk **if they see each other**.

这要求两个机器人可以互相看到，那树套树就有些麻烦了，同时也会轻易超出本题小的可怜的250MB内存限制。

我们根据 $r_i$ **从大到小**对所有机器人进行排序，然后我们让**排在后面的数排在前面的**。这样做有两个用处：

1. 如果视野小的能看到视野大的，那么视野大的一定看得到视野小的，解决了互相看到的问题；
2. 可以防止出现十分恶心的数重数漏的问题。

现在我们只剩下了位置和智商两个限制条件。可以写树套树~~但是空间会炸。~~

其实题面给了一个非常好的东西 $K\le20$。这意味着对于第 $i$ 个机器人，我们完全可以枚举 $[q_i-K,q_i+K]$。开一个map记录**每一个智商对应的权值线段树**，我们就可以完美地切掉这题了。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,maxx;
set<int> num;
map<int,int> no;
struct TreeNode
{
	int val;
	TreeNode *lc,*rc;
	TreeNode(): val(0)
		{ lc=rc=nullptr; }
};
typedef TreeNode *pNode;
void modify(int p,pNode &i,int l=1,int r=maxx)
{
	if(!i)	i=new TreeNode;
	i->val++;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		if(mid>=p)	modify(p,i->lc,l,mid);
		else	modify(p,i->rc,mid+1,r);
	}
}
int query(int lq,int rq,pNode i,int l=1,int r=maxx)
{
	if(!i)	return 0;
	if(l>=lq && r<=rq)	return i->val;
	int mid=(l+r)>>1,res=0;
	if(mid>=lq)	res+=query(lq,rq,i->lc,l,mid);
	if(mid<rq)	res+=query(lq,rq,i->rc,mid+1,r);
	return res;
}
map<int,pNode> t;
struct Robot
{
	int x,r,q;
	inline bool operator <(const Robot &b)const
		{ return r>b.r; }
}a[100005];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].r,&a[i].q);
		num.insert(a[i].x);
		num.insert(a[i].x+a[i].r);
		num.insert(a[i].x-a[i].r);
	}
	for(int i: num)	no[i]=++maxx;
	sort(a+1,a+n+1);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		int x=no[a[i].x],lb=no[a[i].x-a[i].r],rb=no[a[i].x+a[i].r];
		for(int j=a[i].q-k;j<=a[i].q+k;j++)
		{
			auto tj=t.find(j);
			if(tj!=t.end())
				ans+=query(lb,rb,tj->second);
		}
		modify(x,t[a[i].q]);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：cyffff (赞：1)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1045G)
## 题意
有 $n$ 个人，每个人三个属性 $x_i,r_i,q_i$。两个人 $i,j$ 可以互相看到当且仅当 $x_i\in[x_j-r_j,x_j+r_j],x_j\in[x_i-r_i,x_i+r_i],|q_i-q_j|\le k$。求有多少对人会互相看到。

$1\le n\le 10^5$，$0\le k\le 20$。

## 思路
神秘波特题，写一个波特题解。本题解为口胡，若有错误或想复杂了请指出。

先离散化。枚举波特 $i$，求有多少合法的波特 $j$。

把每个波特 $i$ 放到第 $q_i$ 个 `vector` 中，枚举 $q_j$，对每个合法 $q_j$ 二分出对应它的 `vector` 中 $x_j\in[x_i-r_i,x_i+r_i]$ 的区间。

这个区间内的数满足了限制 $2,3$，考虑有多少个区间里的 $j$ 满足 $x_i\in[x_j-r_j,x_j+r_j]$。转化为点对序列 $(x_j-r_j,x_j+r_j)$，求区间内有多少点 $(a,b)$ 满足 $a\le x_i\le b$。经典转化：相当于对区间内所有 $(a,b)$ 执行区间 $[a,b]$ 加一之后 $x_i$ 位置的值。扫描线，可以差分为前缀 $[1,r]$ 和前缀 $[1,l-1]$ 时的 $x_i$ 位置的值相减。

这样时间复杂度是 $O(nk\log n)$ 的。看起来不太好。

考虑优化，二分部分，每个序列 $q_j$ 二分的值是一样的。把所有二分的值取出来排个序再挂回序列上询问，进行归并即可求出每个值在询问序列上的前驱后继。

扫描线部分，我们执行了 $O(n)$ 次区间加和 $O(nk)$ 次单点求值。考虑不使用树状数组而使用分块。这样可以做到 $O(n\sqrt n+nk)$，略优秀一些。不妨考虑迭代分块，将整块打标记和散块暴力加再分别用分块维护。这样可以做到 $O(n\sqrt[4]n+nk)$。事实上，迭代分块可以做到 $O(n^{1+eps})$ 修改 $O(1)$ 查询。

最终时间复杂度 $O(n\sqrt[4]n+n\log n+nk)$。

本题解为口胡，无代码，若有错误或想复杂了请指出。

---

## 作者：Rorschachindark (赞：1)

# AI robots
[题目传送门](https://www.luogu.com.cn/problem/CF1045G)
## 思路
很妙。。。

可以先按视野大小从大到小排序，这样右边的人看得到左边的人，那么左边的人必定看得到右边的人。

因为$k$是固定的，所以可以按智商排序，然后直接用$\text {cdq}$分治求得答案即可，具体见代码。
## $\text {Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define ll long long
#define MAXN 301005

int read ()
{
	int x = 0;char c = getchar();int f = 1;
	while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}
	while (c >= '0' && c <= '9'){x = (x << 3) + (x << 1) + c - '0';c = getchar();}
	return x * f;
}

void write (ll x)
{
	if (x < 0){x = -x;putchar ('-');}
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
}

int n,k,cnt;
int tmp[MAXN];

struct Node
{
	int l,r,len,Index,q;//它的视野范围，它的坐标，它的智商 
	bool operator < (const Node &p)const
	{
		return q < p.q;
	}
}rob[MAXN];

class Bit_tree
{
	private:
		int bit[MAXN];
		int lowbit (int x){return x & (-x);}
	public:
		void update (int pos,int x){for (Int i = pos;i <= n;i += lowbit (i)) bit[i] += x;}
		int query (int pos){int ans = 0;for (Int i = pos;i;i -= lowbit (i)) ans += bit[i];return ans;}
		int query (int l,int r){return query (r) - query (l - 1);} 
}Tree;

ll Ans;

void cdq (int l,int r)
{
	if (l == r) return ;
	int mid = (l + r) >> 1;
	cdq (l,mid),cdq (mid + 1,r);
	int L = l,R = l - 1;//表示跟当前机器人智商差距不大于k的左右端点 
	for (Int i = mid + 1;i <= r;++ i)
	{
		while (L <= mid && rob[i].q - rob[L].q > k) Tree.update (rob[L ++].Index,-1);
		while (R < mid && rob[R + 1].q - rob[i].q <= k) Tree.update (rob[++ R].Index,1);
		Ans += Tree.query (rob[i].l,rob[i].r); 
	}
	for (Int i = L;i <= R;++ i) Tree.update (rob[i].Index,-1);
	sort (rob + l,rob + r + 1);
}

signed main()
{	
	n = read (),k = read ();
	for (Int i = 1;i <= n;++ i)
		rob[i].Index = tmp[i] = read (),rob[i].len = read (),rob[i].q = read ();
	sort (tmp + 1,tmp + n + 1);
	cnt = unique (tmp + 1,tmp + n + 1) - tmp - 1;
	for (Int i = 1;i <= n;++ i)
		rob[i].l = lower_bound (tmp + 1,tmp + cnt + 1,rob[i].Index - rob[i].len) - tmp,
		rob[i].r = upper_bound (tmp + 1,tmp + cnt + 1,rob[i].Index + rob[i].len) - tmp - 1,
		rob[i].Index = lower_bound (tmp + 1,tmp + cnt + 1,rob[i].Index) - tmp;
	sort (rob + 1,rob + n + 1,[](Node A,Node B){return A.len > B.len;});
	cdq (1,n);
	write (Ans),putchar ('\n');
	return 0;
}
```

---

## 作者：Y_B_X (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1045G)  
提供一个稍微不同的 cdq 分治写法，不依赖 $K$ 的大小。  
首先一个限制为 $q$ 的值差距不大于 $K$ 。  
于是可以对 $q$ 排完序后对每个下标 $i$ 查其他点 $q$ 值在 $q_i+K$ 内的贡献减去 $q_i-K-1$ 内的贡献，  
这一维便可直接用 cdq 在外层解决。  
而后是“能相互看到”的限制。  
设每个人下标、能看到的最左、最右及其位置分别为 $i,l_i,r_i,pos_i$ 。  
则对于一对人能相互看到的充要条件为 $l_j\leq pos_i \leq pos_j \leq r_i$ 。  
那在分治每层只需对 $[l,mid]$ 内的数据以 $l$ 排序，$[mid+1,r]$ 内的数据以 $pos$ 排序，  
然后在 $l_j\leq pos_i$ 中查 $pos_i \leq pos_j \leq r_i$ 的 $j$  的个数，用个树状数组即可。  
但这还没完，因为每个点对在其位置不相同是只算了一次，但是在位置相同时被算两次。  
一种解决方法是再找一遍位置相同的点两两间的贡献减掉，但比较麻烦。  
更快的方法是再累加一遍在 $l_j\leq pos_i$ 中 $pos_i < pos_j \leq r_i$ 的 $j$ 的个数。  
然后把统计出的答案除以 $2$ ，这相当于对位置不同的点对再算一次，除 $2$ 后就是真正答案。  
时间复杂度为 $O(n\times \log(n)^2)$ 。  
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m,_n,nn,x,r,y,tot;
long long ans;int b[N];
struct cdq{
	int l,r,pos,q,opt;
	cdq()=default;
	cdq(int _l,int _r,int _pos,int _q,int _opt):l(_l),r(_r),pos(_pos),q(_q),opt(_opt){}
}q[N];char ch;
inline void read(int &x){
	x=0;ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
}
void write(long long x){if(x>=10)write(x/10);putchar('0'+x%10);}
bool cmpq(cdq &x,cdq &y){return x.q^y.q?x.q<y.q:abs(x.opt)<abs(y.opt);}
bool cmpl(cdq &x,cdq &y){return x.l<y.l;}
bool cmppos(cdq &x,cdq &y){return x.pos<y.pos;}
int t[N];
#define lowbit(i) i&(-i)
void update(int pos,int v){for(int i=pos;i<=nn;i+=lowbit(i))t[i]+=v;}
void clear(int pos){for(int i=pos;i<=nn;i+=lowbit(i))t[i]=0;}
int inquiry(int pos){int res=0;for(int i=pos;i;i-=lowbit(i))res+=t[i];return res;}
void solve(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(l,mid);solve(mid+1,r);
	sort(q+l,q+mid+1,cmpl);sort(q+mid+1,q+r+1,cmppos);
	int j=l;
	for(int i=mid+1;i<=r;i++){
		while(j<=mid&&q[j].l<=q[i].pos){
			if(!q[j].opt)update(q[j].pos,1);
			j++;
		}
		if(q[i].opt)ans+=(2*inquiry(q[i].r)-inquiry(q[i].pos-1)-inquiry(q[i].pos))*q[i].opt;
		//算入pos_i<=pos_j<=r_i以及pos_i<pos_j<=r_i的贡献 
	}
	for(int i=l;i<j;i++)if(!q[i].opt)clear(q[i].pos);
}
main(){
	read(n),read(m);
	for(int i=1;i<=n;i++){
		read(x),read(r),read(y);
		b[++_n]=x-r;b[++_n]=x+r;b[++_n]=x;
		q[++tot]=cdq(x-r,x+r,x,y,0);
		q[++tot]=cdq(x-r,x+r,x,y+m,1);
		q[++tot]=cdq(x-r,x+r,x,y-m-1,-1);
		//opt=1代表加上，opt=-1代表减去 
	}
	sort(b+1,b+_n+1);nn=unique(b+1,b+_n+1)-b-1;
	for(int i=1;i<=tot;i++)
		q[i].l=lower_bound(b+1,b+nn+1,q[i].l)-b,
		q[i].r=lower_bound(b+1,b+nn+1,q[i].r)-b,
		q[i].pos=lower_bound(b+1,b+nn+1,q[i].pos)-b;
	sort(q+1,q+tot+1,cmpq);
	solve(1,tot);
	ans-=n;//在统计pos_i<=pos_j<=r_i时会算进自己，应减掉 
	write(ans>>1);
}
```

---

## 作者：Jsxts_ (赞：0)

先把 $x,q$ 离散化。

对于 $x_i$ 和 $x_j$，智商允许的情况下，需要满足下面两个条件：

- $x_i-r_i\le x_j \le x_i+r_i$
- $x_j-r_j\le x_i \le x_j+r_j$

考虑对于每一个 $i$ 枚举 $j$ 所有与 $i$ 能对话的智商，把每种智商对应的机器人存在对应的 $\text{vector}$ 中，此时由第一个条件可得 $x_j$ 是一段区间，可以二分出来，那么问题就变成了：区间查询有多少个区间包含 $x_i$。

把询问离线、差分，然后对于每个 $q$ 内的询问从左到右扫描线，加进一个点就区间加一，查询就单点查询，用树状数组维护即可。

注意这样统计了自己看自己，并且每一对都算了两遍，输出的时候减掉即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,K;
struct node {
	int x,l,r,q,ql,qr;
	bool operator < (const node &a) const {
		return x < a.x;
	}
}a[100010];
struct node2 {
	int x,l,r;
	bool operator < (const node2 &a) const {
		return x < a.x;
	}
};
vector<node2> vc[300010];
int h[300010],totq,totx;
struct ask {
	int l,x,f;
};
vector<ask> vc2[300010];
int cmp2(ask x,ask y) {
	return x.l < y.l;
}
int c[300010];
ll ans;
void upd(int x,int s) {
	for (;x <= totx;x += (x & -x)) c[x] += s;
}
int getsum(int x) {
	int res = 0;
	for (;x;x -= (x & -x)) res += c[x];
	return res;
}
int main() {
	n = read(), K = read();
	for (int i = 1;i <= n;i ++ ) {
		a[i].x = read();
		int r = read(); a[i].q = read();
		a[i].ql = max(0,a[i].q - K), a[i].qr = a[i].q + K;
		a[i].l = max(0,a[i].x - r), a[i].r = a[i].x + r;
		h[++totq] = a[i].ql, h[++totq] = a[i].qr, h[++totq] = a[i].q;
	}
	sort(h+1,h+totq+1);
	totq = unique(h+1,h+totq+1)-h-1;
	for (int i = 1;i <= n;i ++ ) {
		a[i].ql = lower_bound(h+1,h+totq+1,a[i].ql) - h;
		a[i].qr = lower_bound(h+1,h+totq+1,a[i].qr) - h;
		a[i].q = lower_bound(h+1,h+totq+1,a[i].q) - h;
	}
	for (int i = 1;i <= n;i ++ ) h[++totx] = a[i].x, h[++totx] = a[i].l, h[++totx] = a[i].r;
	sort(h+1,h+totx+1);
	totx = unique(h+1,h+totx+1)-h-1;
	for (int i = 1;i <= n;i ++ ) {
		a[i].x = lower_bound(h+1,h+totx+1,a[i].x) - h;
		a[i].l = lower_bound(h+1,h+totx+1,a[i].l) - h;
		a[i].r = lower_bound(h+1,h+totx+1,a[i].r) - h;
		vc[a[i].q].push_back({a[i].x,a[i].l,a[i].r});
	}
	for (int i = 1;i <= totq;i ++ ) sort(vc[i].begin(),vc[i].end());
	for (int i = 1;i <= n;i ++ ) {
		for (int j = a[i].ql;j <= a[i].qr;j ++ ) {
			int l = lower_bound(vc[j].begin(),vc[j].end(),(node2){a[i].l,0,0}) - vc[j].begin();
			int r = upper_bound(vc[j].begin(),vc[j].end(),(node2){a[i].r,0,0}) - vc[j].begin() - 1;
			if (l >= 1) vc2[j].push_back({l-1,a[i].x,-1});
			if (r >= 0) vc2[j].push_back({r,a[i].x,1});
		}
	}
	for (int i = 1;i <= totq;i ++ ) {
		sort(vc2[i].begin(),vc2[i].end(),cmp2);
		int r = 0;
		for (int j = 0;j < vc[i].size();j ++ ) {
			upd(vc[i][j].l,1), upd(vc[i][j].r+1,-1);
			for (;r < vc2[i].size() && vc2[i][r].l == j;r ++ ) ans += vc2[i][r].f * getsum(vc2[i][r].x);
		}
		for (int j = 0;j < vc[i].size();j ++ ) upd(vc[i][j].l,-1), upd(vc[i][j].r+1,1);
	}
	cout << (ans - n) / 2;
	return 0;
}
```


---

## 作者：JoaoFelix (赞：0)

计算对数，一开始降智直接写了个

```
a[++cnt] = { 1, x, q, 0 };
a[++cnt] = { 2, x - r, q, -1, i };
a[++cnt] = { 2, x + r, q, 1, i };
```
这样的东西，然后统计答案，结果Wrong answer on test 2

这样显然是不对的，因为有些对数会被统计两遍！

我们换一种方法：考虑两个点会产生关系，能互相看到

也就是我们按r从大到小排序，小的可以看到大的，那么大的一定可以看到小的

此时我们已经有了一种偏序关系，也就是r的偏序关系

然后我们考虑还有两个条件需要满足，一个就是能互相看见，还有一个就是他们的q要

满足相差不超过k

于是我们可以用cdq分治，因为cdq分治里面的关系我们可以自行调换里外

所以我们可以把不相差k放在外层，然后里层直接有个树状数组维护一下（要离散化）

具体的我们内层归并然后单调队列维护一下即可！

CDQ核心代码：

```cpp
while (L <= mid || R <= r) {
	if (R > r || (L <= mid && c[L].q <= c[R].q + K)) {
		Q[++qr] = mp(Get(c[L].x), c[L].q); Modify(Get(c[L].x), 1); L++;
	} else {
		while (ql <= qr && Q[ql].snd < c[R].q - K) Modify(Q[ql++].fst, -1);
		ans += Query(Get(c[R].x + c[R].rl)) - Query(Get(c[R].x - c[R].rl) - 1); R++;
	}
}
while (ql <= qr) Modify(Q[ql++].fst, -1);
```

主要要总结2点吧！

1 首先cdq的前提是找到偏序关系，我们可以根据题目找到偏序关系！

2 cdq里面往往有两层或者三层（既在cdq里面做的是二维或三维偏序）

这个层与层之间我们可以自己调换，然后找最简单的维护方法！！！

---

