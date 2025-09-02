# [POI 2014] KUR-Couriers

## 题目描述

Byteasar works for the BAJ company, which sells computer games.

The BAJ company cooperates with many courier companies    that deliver the games sold by the BAJ company to its customers.

Byteasar is inspecting the cooperation of the BAJ company with the couriers.

He has a log of successive packages with the courier company that made the delivery    specified for each package.

He wants to make sure that no courier company had an unfair advantage over the others.

If a given courier company delivered more than half of all packages sent in some period of time,    we say that it dominated in that period.

Byteasar wants to find out which courier companies dominated in certain periods of time, if any.

Help Byteasar out!

Write a program that determines a dominating courier company or that there was none.

给一个数列，每次询问一个区间内有没有一个数出现次数超过一半


## 样例 #1

### 输入

```
7 5
1 1 3 2 3 4 3
1 3
1 4
3 7
1 7
6 6
```

### 输出

```
1
0
3
0
4
```

# 题解

## 作者：Vivian_IMproved (赞：62)

看到大家的做法好正经啊~~不要被数据结构懵逼了双眼~~

向大(神)家(仙)推荐一种超好(幼)写(稚)的做法：区间随机化

注意到区间出现次数严格大于一半，根据概率相关知识，我们有大概在$\frac{1}{2}$的概率随机到这个数字，如果我们随机的次数较大，那么将会有较大概率随机到答案

考虑如何判断无解，当随机化次数达到阈值还没有得到答案，就可以近似认定为无解，下面定义阈值为$k=30$

假设我们最终得到的是有解，那么$\frac{1}{2^k}$次判断失误，概率相当小

于是我们得到了一个算法：

小范围区间直接暴力，大范围区间随机区间内的一个数字进行检验

于是问题就变成了如何检验一个数字在区间内出现的次数，神仙说：善用$STL$

直接把每个数字出现的位置丢进$vector$之后查询用$upper_bound-lower_bound$即可

于是做完了，但是同时需要一些其他的优化，尽量减少二分的次数

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int R_int(){
	register int n=0;
	register char ch=getchar();
	register bool I=false;
	while(ch<'0'||ch>'9')I=(ch=='-'?1:0),ch=getchar();
	while(ch>='0'&&ch<='9')n=(n<<1)+(n<<3)+(ch^'0'),ch=getchar();
	return I?-n:n;
}

const int maxn=1000000+10;

vector<int>p[maxn];
int sta[100],top;
bool vis[maxn];
int v[maxn];
int M[maxn];
int n,m;

signed main(){
	srand((long long)new char);
	n=R_int(),m=R_int();
	for(int i=1;i<=n;i++)v[i]=R_int(),p[v[i]].push_back(i);
	for(int c=1,L,R,len;c<=m;c++){
		L=R_int(),R=R_int();len=R-L+1;
		if(len<=100){
			int tag=0;
			len=len>>1;
			for(int i=L;i<=R;i++){
				if(++M[v[i]]>len){
					tag=v[i];
					while(i>=L)--M[v[i--]];
					break;
				}
			}
			if(!tag)for(int i=L;i<=R;i++)--M[v[i]];
			printf("%d\n",tag);
		}
		else {
			int tag=0;
			for(int i=1;i<=30;i++){
				int tmp=v[rand()%len+L];
				sta[++top]=tmp;
				if(!vis[tmp]&&p[tmp].size()>(len>>1)&&std::upper_bound(p[tmp].begin(),p[tmp].end(),R)-std::lower_bound(p[tmp].begin(),p[tmp].end(),L)>(len>>1)){
					tag=tmp;break;
				}
				vis[tmp]=1;
			}
			while(top)vis[sta[top--]]=0;
			printf("%d\n",tag);
		}
	}
	return 0;
}
```

---

## 作者：I_AM_HelloWord (赞：31)

属于一个裸的主席树模板，难度标签打的好高。

[主席树基础传送门。](http://blog.csdn.net/no1\_terminator/article/details/77601599)

这题可以这么考虑，我们直接把读入的数字插入到主席树中，

然后对于询问[i,j]，

在[1..n]中我们看看小于mid的数字有多少个，显然如果个数的两倍<=j-i+1那么[1..mid]中就不存在，

不然我们再看看大于mid的数字有多少个，同理，

如果两个都不行，就返回0，递归搞一搞就好了。


参考代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5e5+5;
const int M=N*21;
struct Presiedent_Tree{
    int sum,L,R;
}T[M];
int n,m,root[N],T_cnt=1;
int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
void insert(int &now,int x,int l=1,int r=n){
    T[T_cnt++]=T[now];now=T_cnt-1;
    T[now].sum++;
    if (l==r)return;
    int mid=(l+r)>>1;
    if (x<=mid)insert(T[now].L,x,l,mid);
        else insert(T[now].R,x,mid+1,r);
}
int query(int i,int j,int x,int l=1,int r=n){
    if (l==r)return l;
    int mid=(l+r)>>1;
    if (2*(T[T[j].L].sum-T[T[i].L].sum)>x)return query(T[i].L,T[j].L,x,l,mid);
    if (2*(T[T[j].R].sum-T[T[i].R].sum)>x)return query(T[i].R,T[j].R,x,mid+1,r);
    return 0;
}
int main(){
    n=read(),m=read();
    root[0]=0;
    for (int i=1;i<=n;i++){
        int x=read();
        root[i]=root[i-1];
        insert(root[i],x);
    }
    for (int i=1;i<=m;i++){
        int l=read(),r=read();
        printf("%d\n",query(root[l-1],root[r],r-l+1));
    }
    return 0;
}
```

---

## 作者：pzc2004 (赞：27)

[题目传送门](https://www.luogu.org/problem/P3567)

~~刚学主席树，写篇题解加强记忆。~~

思路：和[主席树模板](https://www.luogu.org/problem/P3834)一样，先离散化，再建树，~~其实只需要把[主席树模板](https://www.luogu.org/problem/P3834)的AC代码最后的查询还有数组的大小改一改~~。

代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N=500001;//唯二和主席树模板不一样的地方
int n,q,m,cnt;
int a[N],b[N],t[N];
struct sb
{
	int s,l,r;
}tre[N<<5];
int build(int l,int r)//以下全部和主席树模板一样
{
	int p=++cnt;
	if(l<r)
	{
		int mid=(l+r)>>1;
		tre[p].l=build(l,mid);
		tre[p].r=build(mid+1,r);
	}
	return p;
}
int update(int p1,int l,int r,int x)
{
	int p=++cnt;
	tre[p].l=tre[p1].l;
	tre[p].r=tre[p1].r;
	tre[p].s=tre[p1].s+1;
	if(l<r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)tre[p].l=update(tre[p1].l,l,mid,x);else tre[p].r=update(tre[p1].r,mid+1,r,x);
	}
	return p;
}//以上全部和主席树模板一样
int query(int u,int v,int l,int r,int k)//唯二和主席树模板不一样的地方，k表示区间长度的一半
{
    if(l>=r)return l;
    int l1=tre[tre[v].l].s-tre[tre[u].l].s,r1=tre[tre[v].r].s-tre[tre[u].r].s;//计算当前区间大于等于l小于等于mid的数字的数量和大于mid小于等于r的数字的数量
    int mid=(l+r)>>1;
    if(l1>k)return query(tre[u].l,tre[v].l,l,mid,k);//如果大于等于l小于等于mid的数字的数量超过一半就往下查询
    if(r1>k)return query(tre[u].r,tre[v].r,mid+1,r,k);//同上
    return 0;//否则说明该区间中不存在出现数量超过一半的数，返回0
}
int main()//以下全部和主席树模板一样
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	t[0]=build(1,m);
	for(int i=1;i<=n;i++)
	{
		int l=lower_bound(b+1,b+m+1,a[i])-b;
		t[i]=update(t[i-1],1,m,l);
	}
	while(q--)
	{
		int a1,a2;
		scanf("%d%d",&a1,&a2);
		printf("%d\n",b[query(t[a1-1],t[a2],1,m,(a2-a1+1)/2)]);//查询
	}
}//以上全部和主席树模板一样
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：panyf (赞：26)

和其他题解不同的方法

前置知识：摩尔投票法，不会的左转[P2397](https://www.luogu.com.cn/problem/P2397)学习一下。

摩尔投票是可以合并的，可以用线段树维护。我们只需维护区间内可能的众数和票数即可，合并时分类讨论一下。注意选出的数还需验证其出现次数是否达到区间长度的一半，可以用动态开点线段树维护每个数的出现次数。

本题还有增强版[P3765](https://www.luogu.com.cn/problem/P3765)，不过毒瘤卡空间，动态开点线段树要写空间回收。

详细注释代码如下：
```cpp
#include<cstdio>
struct T1{
	int v,s;//v是选出的数，s为票数
}t[2000009];
struct T2{
	int l,r,v;//v为区间内该数出现次数
}s[10000009];
int u,v,id,p[500009],rt[500009];
void build(int k,int l,int r){
	if(l==r){
		t[k].v=p[l],t[k].s=1;
		return;
	}
	register int m=l+r>>1,a=k<<1,b=a|1;
	build(a,l,m),build(b,m+1,r);
 	//以下为核心部分
	if(t[a].v==t[b].v)t[k].v=t[a].v,t[k].s=t[a].s+t[b].s;//众数相同，票数相加
	else if(t[a].s>t[b].s)t[k].v=t[a].v,t[k].s=t[a].s-t[b].s;//众数不同，取票数多的为众数，票数相减
	else t[k].v=t[b].v,t[k].s=t[b].s-t[a].s;
}
T1 qry(int k,int l,int r){//查询众数
	if(u<=l&&r<=v)return t[k];
	register int m=l+r>>1,a=k<<1,b=a|1;
	if(m>=v)return qry(a,l,m);
	if(u>m)return qry(b,m+1,r);
	register T1 x=qry(a,l,m),y=qry(b,m+1,r);
	if(x.v==y.v)x.s+=y.s;
	else if(x.s>y.s)x.s-=y.s;
	else x.v=y.v,x.s=y.s-x.s;
	return x;
}
void upd(int&k,int l,int r){//动态开点线段树插入
	if(!k)k=++id;
	++s[k].v;
	if(l==r)return;
	register int m=l+r>>1;
	if(u<=m)upd(s[k].l,l,m);else upd(s[k].r,m+1,r);
}
int qnum(int k,int l,int r){//查询区间内某个数出现次数
	if(u<=l&&r<=v)return s[k].v;
	register int m=l+r>>1,z=0;
	if(u<=m)z=qnum(s[k].l,l,m);
	if(m<v)z+=qnum(s[k].r,m+1,r);
	return z;
}
int main(){
	register int n,m,i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%d",p+i),u=i,upd(rt[p[i]],1,n);
	build(1,1,n);
	while(m--){
		scanf("%d%d",&u,&v),j=qry(1,1,n).v;
		if((qnum(rt[j],1,n)<<1)>v-u+1)printf("%d\n",j);//出现次数超过一半再输出
		else puts("0");
	}
	return 0;
}
```


---

## 作者：Kewth (赞：13)

这题做法好多啊，比较无脑的有主席树和莫队。  
特点是好想但是不太好写。

比较妙的做法我知道的有两个，  
一个是随机取点，利用的是有至少 1/2 的概率取到严格众数的性质。  
这个有人提到过了，再次不赘述。

另一个是二进制拆分，也就是我要介绍的算法。

一个区间若存在一个数 x 出现次数大于一半，那么把二进制的每个位 k 单独考虑， x 的第 k 位出现次数也一定大于一半。  
那么枚举每一位 k 如果能求出第 k 位的严格众数，把每一位的结果拼起来就是答案。  
如何求第 k 位上的严格众数？这时序列相当于只有 01 ，那么只要求出 1 的个数 0 的个数也是确定的。  
而只需对每一位维护前缀和就能轻松求出该位的一个区间内 1 的个数。

这样做一定对吗？  
事实上，这样无法处理无解的情况，因此特判一下无解，求出答案 x 后二分检查一下 x 的出现次数就好了。

代码（不知道为什么常数有点大，有一个点要开 O2 才能过）：

```cpp
#if 0
2019.09.19

一个数出现次数超过一半的话，它的二进制位的每一位单独考虑也一定超过一半。
那么问题转换为 01 序列，代价是一个 log 。
01 序列求众数直接用前缀和查区间值即可。
另外需要判断无解，求出答案 x 后在 pos[x] 里二分出 x 的数量即可，
其中 pos[x] 是 x 的出现位置集合。
一个坑点是算出来的 x 可能根本不存在。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, maxk = 20;
int s[maxk][maxn];
std::vector<int> pos[maxn];

int main() {
	int n = input(), q = input();

	for(int i = 1; i <= n; i ++) {
		int x = input();
		for(int k = 0; k < maxk; k ++)
			s[k][i] = s[k][i - 1] + (x >> k & 1);
		pos[x].push_back(i);
	}

	while(q --) {
		int l = input(), r = input(), ans = 0;

		for(int k = 0; k < maxk; k ++) {
			int x = s[k][r] - s[k][l - 1];
			if((x << 1) > r - l + 1)
				ans |= 1 << k;
		}

		if(ans > n) {
			puts("0");
			continue;
		}

		int lp = int(
				std::lower_bound(pos[ans].begin(), pos[ans].end(), l) - pos[ans].begin());
		int rp = int(
				std::upper_bound(pos[ans].begin(), pos[ans].end(), r) - pos[ans].begin() - 1);

		if(((rp - lp + 1) << 1) > r - l + 1)
			printf("%d\n", ans);
		else
			puts("0");
	}
}
```

---

## 作者：Tari (赞：10)

还有一种主席树做法，来自上课老师的启发$qwq$  
前置芝士：静态区间第$k$大（主席树板子）  
主要思路：  
**若一个数在区间中出现次数大于一半，那么他一定是中位数**  
所以我们可以求出中位数（区间第$k$大），记为$tmp$，然后再求一下$tmp$出现次数，如果出现次数超过一半，$tmp$即为答案。否则没有答案。  
注意讨论区间长度的奇偶性$qwq$，偶数时要先比较是否相等再求出现次数  

代码：
```cpp
#include<cstdio>
#include<iostream>
#define R register int
using namespace std;
#define ull unsigned long long
#define ll long long
#define pause (for(R i=1;i<=10000000000;++i))
#define In freopen("NOIPAK++.in","r",stdin)
#define Out freopen("out.out","w",stdout)
namespace Fread {
	static char B[1<<15],*S=B,*D=B;
#ifndef JACK
	#define getchar() (S==D&&(D=(S=B)+fread(B,1,1<<15,stdin),S==D)?EOF:*S++)
#endif
	inline int g() {
		R ret=0,fix=1; register char ch;
		while(!isdigit(ch=getchar()))
			fix=ch=='-'?-1:fix;
		if(ch==EOF) return EOF;
		do
			ret=ret*10+(ch^48);
		while(isdigit(ch=getchar()));
		return ret*fix;
	}
	inline bool isempty(const char& ch) {
		return (ch<=36||ch>=127);
	}
	inline void gs(char* s) {
		register char ch; while(isempty(ch=getchar()));
		do *s++=ch; while(!isempty(ch=getchar()));
	}
}
using Fread::g;
using Fread::gs;

namespace Luitaryi {
const int N=500010,M=N*20;
int tot,n,m;
int ls[M],rs[M],sum[M],rt[N];
inline void build(int& tr,int l,int r) {
	tr=++tot; if(l==r) return ;
	R md=l+r>>1;
	build(ls[tr],l,md),build(rs[tr],md+1,r);
}
inline void change(int pre,int& tr,int l,int r,int vl) {
	tr=++tot; ls[tr]=ls[pre],rs[tr]=rs[pre],sum[tr]=sum[pre]+1;
	if(l==r) return ; R md=l+r>>1;
	if(vl<=md) change(ls[pre],ls[tr],l,md,vl);
	else change(rs[pre],rs[tr],md+1,r,vl);
}
inline int query(int lt,int rt,int l,int r,int pos) {
	if(l==r) return sum[rt]-sum[lt];
	R md=l+r>>1;
	if(pos<=md) return query(ls[lt],ls[rt],l,md,pos);
	else return query(rs[lt],rs[rt],md+1,r,pos);
}
inline int calc(int lt,int rt,int l,int r,int k) {
	if(l==r) return l;
	R md=l+r>>1,sz=sum[ls[rt]]-sum[ls[lt]];
	if(sz>=k) return calc(ls[lt],ls[rt],l,md,k);
	else return calc(rs[lt],rs[rt],md+1,r,k-sz);
}
inline void solve(int l,int r) {
	if((r-l+1)&1) {
		R tmp=calc(rt[l-1],rt[r],1,n,(r-l+2)/2);
		if(query(rt[l-1],rt[r],1,n,tmp)>(r-l+1)/2)
			printf("%d\n",tmp);
		else printf("0\n");
	} else {
		R tmp=calc(rt[l-1],rt[r],1,n,(r-l+1)/2),
			tnp=calc(rt[l-1],rt[r],1,n,(r-l+3)/2);
		if(tmp==tnp&&query(rt[l-1],rt[r],1,n,tmp)>(r-l+1)/2) 
			printf("%d\n",tmp);
		else printf("0\n");
	}
}
inline void main() {
	n=g(),m=g();
	for(R i=1,x;i<=n;++i) x=g(),change(rt[i-1],rt[i],1,n,x);
	for(R i=1;i<=m;++i) {
		R l=g(),r=g();
		solve(l,r);
	}
}
}
signed main() {
	Luitaryi::main(); 
	return 0;
}
```


---

## 作者：Andrewzdm (赞：7)

看了下题解区，基本上不是主席树就是随机化乱搞……

我寻思着看到这题想到回滚莫队不是很自然吗？？？

我们发现题目有如下特征：
+ 静态（不带修改，多次查询）
+ 每次查询是区间 $[l,r]$
+ 统计数的出现次数，而这个是经典的可以用莫队做的问题

判断是否存在数的出现次数严格大于区间长度的一半，就等价于判断区间里所有数的出现次数最大值是否严格大于区间长度的一半。

出现次数的最大值，是一个在添加过程中易维护，而在删除过程中不易维护的信息。因此我们考虑使用回滚莫队，也就是不删除莫队。

回滚莫队的实现方式及细节不了解的请自行移步模板题，这里不再赘述。

于是这题变成了一道板子题。时间复杂度 $O(n\sqrt n)$，由于 $n,m$ 同阶统一使用 $n$。

本人不大会卡常，这题由于数据范围是 $5 \times 10^5$，在不开 O2 的情况下会 T 掉两个点，开了 O2 之后最大规模测试点在 600ms 内可以跑过。思路放在这里给大家一个参考。

代码：
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 5e5 + 10 , maxm = 5e5 + 10, maxb = 715;
int n, m;
int a[maxn];
struct query {
    int l, r, id;
} q[maxm];
int ans[maxm];
int blen, bnum, bel[maxn];
int cnt[maxn];
int L[maxb], R[maxb];

bool cmp(const query &x, const query &y) { return bel[x.l] != bel[y.l] ? bel[x.l] < bel[y.l] : x.r < y.r; }

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    blen = sqrt(n);
    bnum = n / blen;
    for(int i = 1; i <= bnum; ++i) {
        L[i] = (i - 1) * blen + 1;
        R[i] = i * blen;
    }
    if(R[bnum] != n) {
        L[bnum + 1] = R[bnum] + 1;
        R[++bnum] = n;
    }
    for(int i = 1; i <= bnum; ++i) fill(bel + L[i], bel + R[i] + 1, i);
    sort(q + 1, q + m + 1, cmp);
    int l = 1, r = 0, lst = 0, mx, fr;
    for(int i = 1; i <= m; ++i) {
        if(bel[q[i].l] != lst) {
            while(r >= l) --cnt[a[r--]];
            mx = 0; fr = 0;
            lst = bel[q[i].l];
            r = R[lst];
            l = r + 1;
        }
        if(bel[q[i].l] == bel[q[i].r]) {
            for(int j = q[i].l; j <= q[i].r; ++j)
                if(++cnt[a[j]] > mx)
                    mx = cnt[fr = a[j]];
            ans[q[i].id] = mx > (q[i].r - q[i].l + 1) / 2 ? fr : 0;
            for(int j = q[i].l; j <= q[i].r; ++j) --cnt[a[j]];
            mx = 0; fr = 0;
            continue;
        }
        while(r < q[i].r) {
            if(++cnt[a[++r]] > mx)
                mx = cnt[fr = a[r]];
        }
        int lol = l, tmp = mx, ffr = fr;
        while(lol > q[i].l) {
            if(++cnt[a[--lol]] > tmp)
                tmp = cnt[ffr = a[lol]];
        }
        ans[q[i].id] = tmp > (q[i].r - q[i].l + 1) / 2 ? ffr : 0;
        while(lol < l) --cnt[a[lol++]];
    }
    for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：Leasier (赞：3)

前置芝士：[莫队](http://oi-wiki.com/misc/mo-algo/)、[随机化](http://oi-wiki.com/misc/rand-technique/)

看到“在 $[l, r]$ 中出现的次数”容易想到莫队。

但如果你尝试对于每个询问遍历区间内每个数的出现次数，时间复杂度为 $O(nm)$，在 NKOJ 上（数据范围为 $1 \leq n, m \leq 10^5$）都会炸成 $76 \operatorname{pts}$（如果不考虑卡常）。

但是……如果区间内有满足条件的数，难道不是在区间内期望猜 $2$ 次就可以猜到这个数吗？

于是考虑随机化。设定阀值 $M$，每次在区间内猜 $M$ 次这个数的下标，如果满足则有答案；否则，**在绝大多数情况下**无解。如果有答案，则这样做仍然猜不到答案的概率为 $\frac{1}{2^{M - 1}}$。我的代码中取 $M = 20$。

事实上，即使我们这样做，在 Luogu 上仍然只有 $60 \operatorname{pts}$。考虑卡常，我采用了快读、奇偶排序、前置自增、将 int 改为 unsigned int 的方法 AC 了这道题。

时间复杂度为 $O(m \log m + n \sqrt{m} + nM)$。

代码：
```cpp
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

typedef unsigned int uint;

typedef struct {
	uint id;
	uint pos;
	uint l;
	uint r;
} Query;

const uint N = 5e5 + 7, M = 20;
uint block;
uint a[N], cnt[N], ans[N];
Query query[N];

bool operator <(const Query a, const Query b){
	if (a.pos != b.pos) return a.pos < b.pos;
	if (a.pos % 2 == 0) return a.r > b.r;
	return a.r < b.r;
}

inline uint read(){
	uint ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

#define add(x) ++cnt[a[x]]
#define del(x) --cnt[a[x]]

int main(){
	uint n = read(), m = read();
	block = ceil(n / sqrt(m));
	srand(time(NULL));
	for (register uint i = 1; i <= n; ++i){
		a[i] = read();
	}
	for (register uint i = 1; i <= m; ++i){
		query[i].l = read();
		query[i].r = read();
		query[i].id = i;
		query[i].pos = (query[i].l - 1) / block + 1;
	}
	sort(query + 1, query + m + 1);
	for (register uint i = 1, j = 1, k = 0; i <= m; ++i){
		uint limit = (query[i].r - query[i].l + 1) / 2;
		while (j > query[i].l) add(--j);
		while (k < query[i].r) add(++k);
		while (j < query[i].l) del(j++);
		while (k > query[i].r) del(k--);
		for (register uint l = 1; l <= M; ++l){
			uint pos = rand() % (query[i].r - query[i].l + 1) + query[i].l;
			if (cnt[a[pos]] > limit){
				ans[query[i].id] = a[pos];
				break;
			}
		}
	}
	for (register uint i = 1; i <= m; ++i){
		printf("%u\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：kouylan (赞：3)

## P3567 [POI2014]KUR-Couriers 题解

### 【题意】
给一个长度为$n$的序列$a$。1<=$a_i$<=$n$

$m$组询问，每次询问一个区间[$l,r$]，是否存在一个数在[$l,r$]中出现的次数大于$(r-l+1)/2$。如果存在，输出这个数，否则输出0。

### 【分析】
看到求区间的数值出现次数，就知道用[主席树](https://www.luogu.com.cn/problem/P3834)。

$insert$跟模板一样，在此就不再赘述。

$query$
```cpp
int query(int l,int r,int x,int y,int k)
{
	if(l==r)
		return l;
	if(dat[y].sum-dat[x].sum<=k) //如果对应区间出现的数少于k，直接返回。
		return 0;
	if(dat[dat[y].l].sum-dat[dat[x].l].sum>k) //如果合法数字在左子树中
		return query(l,mid,dat[x].l,dat[y].l,k);
	else if(dat[dat[y].r].sum-dat[dat[x].r].sum>k) //如果合法数字在右子树中
		return query(mid+1,r,dat[x].r,dat[y].r,k);
	return 0; //否则不合法
}
```
下面是AC代码
```cpp
/*
luogu P3567
*/
#include <bits/stdc++.h>
using namespace std;

#define mid (l+r>>1)

int n,q;
int root[500005],cnt;
struct hjtree{
	int l,r,sum;
}dat[500005<<5];

void insert(int &o,int l,int r,int pre,int x)
{
	o = ++cnt;
	dat[o] = dat[pre];
	dat[o].sum++;
	if(l==r)
		return;
	if(x<=mid)
		insert(dat[o].l,l,mid,dat[pre].l,x);
	else
		insert(dat[o].r,mid+1,r,dat[pre].r,x);
}

int query(int l,int r,int x,int y,int k)
{
	if(l==r)
		return l;
	if(dat[y].sum-dat[x].sum<=k)
		return 0;
	if(dat[dat[y].l].sum-dat[dat[x].l].sum>k)
		return query(l,mid,dat[x].l,dat[y].l,k);
	else if(dat[dat[y].r].sum-dat[dat[x].r].sum>k)
		return query(mid+1,r,dat[x].r,dat[y].r,k);
	return 0;
}

int main()
{
	cin>>n>>q;
	for(int i=1,x;i<=n&&cin>>x;i++)
		insert(root[i],1,n,root[i-1],x);
	while(q--)
	{
		int l,r,k;
		scanf("%d %d",&l,&r);
		k = r-l+1>>1;
		printf("%d\n",query(1,n,root[l-1],root[r],k));
	}
	
	return 0;
}
```
祝大家AC愉快！

---

## 作者：_sin_ (赞：2)

首先，求区间严格众数有一个经典做法：摩尔投票法。这个是简单的，不会的可以看 P2397 的题解。

众数没有可合并性，但是区间严格众数的摩尔投票具有可合并性。具体维护是简单的。

考虑怎么判断一个数是否是区间严格众数。别的题解里面写的都是用主席树维护，其实不必这么麻烦。由于这个问题没有强制在线，所以我们可以离线所有询问。考虑扫描线，用一个桶维护出现次数，差分一下就可以得到答案。

代码非常好写，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return f*x;
}

const int N = 5e5+5;
int n, m, a[N],t[N];
int L[N],R[N],ans1[N],ans2[N];
struct Node{int x,cnt;}s[N<<2];
struct Query{int id,l,r,x;};
vector<Query>vec[N];

Node merge(Node a, Node b){
	Node res;if(a.x==b.x)res=Node{a.x,a.cnt+b.cnt}; 
	else if(a.cnt>b.cnt)res=Node{a.x,a.cnt-b.cnt};
	else res=Node{b.x,b.cnt-a.cnt};return res;
}
void build(int l, int r, int p){
	if(l==r)return s[p]=Node{a[l],1},void();int mid=l+r>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);s[p]=merge(s[p<<1],s[p<<1|1]);
}
Node query(int l, int r, int L, int R, int p){
	if(L<=l&&r<=R)return s[p];int mid=l+r>>1;
	if(R<=mid)return query(l,mid,L,R,p<<1);
	if(mid<L)return query(mid+1,r,L,R,p<<1|1);
	return merge(query(l,mid,L,R,p<<1),query(mid+1,r,L,R,p<<1|1));
}

int main(){
	n=read(),m=read();for(int i=1;i<=n;i++)a[i]=read();
	build(1,n,1);for(int i=1;i<=m;i++){
		int l=read(),r=read();auto tmp=query(1,n,l,r,1);
		ans1[i]=tmp.x;vec[r].push_back(Query{i,l,r,ans1[i]});
		vec[l-1].push_back(Query{i,l,r,ans1[i]});L[i]=l,R[i]=r;
	}
	for(int i=1;i<=n;i++){
		t[a[i]]++;
		for(auto qu:vec[i]){
			if(qu.l==i+1)ans2[qu.id]-=t[qu.x];
			else ans2[qu.id]+=t[qu.x];
		}
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans2[i]*2>R[i]-L[i]+1?ans1[i]:0);
	return 0;
}
```

---

## 作者：GoldenPotato137 (赞：1)

# 题面
[戳我获得更好的阅读体验](https://www.goldenpotato.cn/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/luogu-p3567-poi2014kur-couriers/)

---
# Solution
~~大水题啊，真没什么好讲的~~

我们考虑建一颗权值主席树，从左往右逐个插入。因为个数满足可减性，因此我们可以很方便的“扣”出$[L,R]$区间构成的主席树。接下来只需要在树上二分看一下有没有出现次数超过$K$的即可。

时间复杂度$O(nlogn)$
就酱，这题就被我们切掉啦︿(￣︶￣)︿

---
# Solution
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=500000+100;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
struct SegmentTree
{
    #define mid ((now_l+now_r)>>1)
    static const int M=25*N;
    int size[M],son[M][2],to;
    inline void update(int now)
    {
        size[now]=size[son[now][0]]+size[son[now][1]];
    }
    void Add(int now,int pre,int x,int now_l,int now_r)
    {
        if(now_l==now_r)
        {
            size[now]=size[pre]+1;
            return;
        }
        if(x<=mid)
        {
            son[now][1]=son[pre][1];
            Add(son[now][0]=++to,son[pre][0],x,now_l,mid);
        }
        else
        {
            son[now][0]=son[pre][0];
            Add(son[now][1]=++to,son[pre][1],x,mid+1,now_r);
        }
        update(now);
    }
    int Query(int now,int pre,int x,int now_l,int now_r)
    {
        if(now_l==now_r)
            return now_l;
        if(size[son[now][0]]-size[son[pre][0]]>=x)
            return Query(son[now][0],son[pre][0],x,now_l,mid);
        else if(size[son[now][1]]-size[son[pre][1]]>=x)
            return Query(son[now][1],son[pre][1],x,mid+1,now_r);
        return 0;
    }
    #undef mid
}sgt;
int root[N],n,m;
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        int tmp=read();
        sgt.Add(root[i]=++sgt.to,root[i-1],tmp,1,n);
    }
    
    for(int i=1;i<=m;i++)
    {
        int l=read(),r=read(),mid=(r-l+1)/2+1;
        printf("%d\n",sgt.Query(root[r],root[l-1],mid,1,n));
    }
    return 0;
}

```





---

## 作者：luoguliujiaxin (赞：0)

对于本题的 [随机化算法](https://www.luogu.com.cn/article/sqyde4et)，令随机化次数阈值为 $B$，则判断正确的概率不低于 $(1-\frac{1}{2^B})^m$。为保证通过，可取 $B=30$，此时一次性通过全部测试点的概率约为 $95\%$。

然而，如果使用题解中 $O(\log n)$ 的 check 方式，总时间复杂度将达到 $O(Bn\log n)$，需要一定的优化才能通过。

下面给出**一种 $O(1)$ 的 check 方式**。


让我们考虑一下，是什么带来了原先 check 方式的 $\log$？

事实上，是**二分**。

为什么非得二分呢？

为了找到该数字**出现的次数**，**并与 $\lfloor\frac{len}{2}\rfloor$ 比较**。

等等，我们转换一下思路。

事实上，**我们不一定要知道它具体出现几次，只需要知道它是否出现了至少 $\lfloor\frac{len}{2}\rfloor$ 次**。

将询问离线，按右端点升序排序，并依次遍历。在右端点右移的过程中，我们仍旧将每个数字出现的位置塞进 vector。

由于我们按右端点遍历询问，当前在 vector 中的所有位置都在右端点(含)的左侧，只需判断最后 $\lfloor\frac{len}{2}\rfloor$ 个出现的位置是否在左端点(含)的右侧。

如果该数字倒数第 $\lfloor\frac{len}{2}\rfloor$ 次出现在左端点(含)的右侧，则说明在左端点(含)的右侧至少出现了 $\lfloor\frac{len}{2}\rfloor$ 次。否则说明出现不足 $\lfloor\frac{len}{2}\rfloor$ 次。

也就是：
```cpp
if(v[p][v[p].size()-(len>>1)-1]>=q[i].l) return p;
```


要注意总出现次数不足 $\lfloor\frac{len}{2}\rfloor$ 时的数组越界。

时间复杂度 $O(Bn)$。

PS：如果你选择一个好的随机数种子，$B$ 的范围还可进一步缩小，跑得飞快。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=500005;
const int B=30;
mt19937 rnd(time(0));
int get(int p){return (rnd()%p+p)%p;}
int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while( isdigit(ch)){ret=(ret<<3)+(ret<<1)+(ch&15);ch=getchar();}
    return ret*f;
}
int n,m;
int a[maxn];
struct ques{
    int l,r,id;
    bool operator<(const ques &B)const{return r<B.r;}
}q[maxn];
vector<int> v[maxn];
int ans[maxn];
int calc(int i){
    int len=q[i].r-q[i].l+1;
    for(int t=1;t<=B;++t){
        int p=a[get(len)+q[i].l];
        if(v[p].size()<=(len>>1)) continue;
        if(v[p][v[p].size()-(len>>1)-1]>=q[i].l) return p;
    }
    return 0;
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=m;++i){
        q[i].l=read();
        q[i].r=read();
        q[i].id=i;
    }
    sort(q+1,q+m+1);
    int p=1;
    for(int i=1;i<=n;++i){
        v[a[i]].push_back(i);
        while(q[p].r==i){
            ans[q[p].id]=calc(p);
            p++;
        }
    }
    for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：King丨帝御威 (赞：0)

考虑主席树，加点操作就不用说了吧。。重点强调一下查询操作，我们想，如果一个数出现次数大于区间长度一半的话，那么它在权值线段树中可能出现在左子树中，也可能出现在右子树中，那么我们主席树只需要维护一个sum表示每个区间中数出现的次数就可以了，然后查询分左右子树来查。(其实就是个主席树板子题啦。。。)


具体实现看代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#define maxn 10000007
using namespace std;
int rt[maxn],sum[maxn],lc[maxn],rc[maxn],n,m,cnt,a[maxn],b[maxn];
inline int qread() {
  char c=getchar();int num=0,f=1;
  for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
  for(;isdigit(c);c=getchar()) num=num*10+c-'0';
  return num*f;
}
void add(int &now, int last, int l, int r, int x) {
  now=++cnt;
  lc[now]=lc[last],rc[now]=rc[last],sum[now]=sum[last]+1;
  if(l==r) return;
  int mid=(l+r)>>1;
  if(x<=mid) add(lc[now],lc[last],l,mid,x);
  else add(rc[now],rc[last],mid+1,r,x);
}
int query(int l, int r, int L, int R, int x) {
  if(l==r) return l;
  int cyh=sum[lc[R]]-sum[lc[L]],lcy=sum[rc[R]]-sum[rc[L]];
  int mid=(l+r)>>1;
  if(cyh>x) return query(l,mid,lc[L],lc[R],x);
  else if(lcy>x) return query(mid+1,r,rc[L],rc[R],x);
  else return 0; 
}
int main() {
  n=qread(),m=qread();
  for(int i=1;i<=n;++i) a[i]=qread(),b[i]=a[i];
  sort(a+1,a+1+n);
  int len=unique(a+1,a+1+n)-a-1;
  for(int i=1;i<=n;++i) {
    int p=lower_bound(a+1,a+1+len,b[i])-a;
    add(rt[i],rt[i-1],1,len,p);
  }
  for(int i=1,l,r;i<=m;++i) {
    l=qread(),r=qread();
    printf("%d\n",a[query(1,len,rt[l-1],rt[r],(r-l+1)>>1)]);
  }
  return 0;
}
```

---

## 作者：顾z (赞：0)


# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

主席树板子题

~~话说为啥是个板子题,我也没看出来~~

查询时需要找出出现次数为$(r-l+1)/2$的.

主席树基本操作,**离散化**是必须的.

然后建树操作与之前操作相同.

难点在于查询时候如何做.

最基本的查询,是判断当前根的左节点的$sum$与查询的大小的关系.

如果左边的$sum$大于等于$(r-l+1)/2$则,此数在左侧.

然后如何**判断在右侧**?

用当前根总共的$sum$减去左边的$sum$,即为右边的$sum$,判断是否大于$(r-l+1)/2$即可.

否则$return 0$

``代码``

```c++
#include<cstdio>
#include<cctype>
#include<algorithm>
#define N 500008
#define R register
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int n,m,new_n=1;
int a[N],b[N],cnt;
int root[N*20],sum[N*20],lson[N*20],rson[N*20];
void build(int lastroot,int &nowroot,int l,int r,int pos)
{
	nowroot=++cnt;
	sum[nowroot]=sum[lastroot]+1;
	lson[nowroot]=lson[lastroot];
	rson[nowroot]=rson[lastroot];
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)build(lson[lastroot],lson[nowroot],l,mid,pos);
	else build(rson[lastroot],rson[nowroot],mid+1,r,pos);
}
int query(int lastroot,int nowroot,int l,int r,int pos)
{
	if(l==r)return l;
	int tmp=sum[lson[nowroot]]-sum[lson[lastroot]];
	int mid=(l+r)>>1;
	if(pos<tmp)return query(lson[lastroot],lson[nowroot],l,mid,pos);
	if(sum[nowroot]-sum[lastroot]-tmp>pos)return query(rson[lastroot],rson[nowroot],mid+1,r,pos);
	return 0;
}
int main()
{
	in(n),in(m);
	for(R int i=1;i<=n;i++)in(a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	for(R int i=2;i<=n;i++)if(b[i]!=b[new_n])b[++new_n]=b[i];
	for(R int i=1;i<=n;i++)
		build(root[i-1],root[i],1,new_n,lower_bound(b+1,b+new_n+1,a[i])-b);
	for(R int i=1,l,r;i<=m;i++)
	{
		in(l),in(r);
		int pos=query(root[l-1],root[r],1,new_n,(r-l+1)>>1);
		printf("%d\n",b[pos]);
	}
}
```



---

## 作者：arfa (赞：0)

> ### 静态主席树

题面大意就是给定一个区间$l,r$,让你求出一个数字$num$的出现次数大于$\frac{r-l+1}{2}$。虽然是一个很显然的主席树裸题,不过~~怎么能卡我空间呢~~?

思路就是,出现次数大于一半肯定是绝对的。如果左儿子的权值已经大于$\frac{r-l+1}{2}$,那么右儿子肯定小于$\frac{r-l+1}{2}$。也可能两边都等于$\frac{r-l+1}{2}$,不过这样子就说明没有答案。

如果左儿子(或者右儿子)的权值大于$\frac{r-l+1}{2}$,那么答案肯定在左子树中,这样就可以$log\ n$的时间求出答案。

> ### $Code$

```pascal
// luogu-judger-enable-o2 //没有说pascal不能开
// 注意空间
var
    left,right,tree:array[-1..10010007] of longint; //分别为左儿子的位置,右儿子的位置,本节点的权值
    root:array[-1..10010007] of longint; //每一个根的编号
    recf:array[-1..1500007] of longint; //每一个数的编号,直接用桶来代替离散化
    bucket:array[-1..5001007] of longint; //每一个编号所代表的数
    i,j,n,m,cnt,now,fa,tail,num,l,r,find:longint;
    condition:real; //满足要求,即为(r-l+1)/2,其实可以是整数

procedure Build(l,r,key:longint); 
var
    mid:longint;
begin
    inc(cnt); //动态开点
    tree[cnt]:=tree[fa]+1; 
    if l=r then 
        exit;

    mid:=(l+r) div 2;
    if key<=mid then //往左走
    begin //记得全部都要往左
        left[cnt]:=cnt+1; //左儿子一定是cnt+1(除了叶子结点)
        right[cnt]:=right[fa];
        fa:=left[fa];
        Build(l,mid,key);
    end;
    if key>mid then //如上
    begin
        right[cnt]:=cnt+1;
        left[cnt]:=left[fa];
        fa:=right[fa];
        Build(mid+1,r,key);
    end;
end;

procedure Query(l,r:longint);
var
    mid,value:longint;
begin
    if l=r then
    begin
        find:=bucket[l];
        exit;
    end;

    value:=tree[left[fa]]-tree[left[now]]; //左边的权值
        mid:=(l+r) div 2;
    if value>condition then //满足
    begin
        fa:=left[fa];
        now:=left[now];
        Query(l,mid);
    end;
    value:=tree[right[fa]]-tree[right[now]]; //如上
    if value>condition then
    begin
        fa:=right[fa];
        now:=right[now];
        Query(mid+1,r);
    end;
end;

begin
    read(n,m);
    tail:=0;
    for i:=1 to n do
    begin
        read(num);
        if recf[num]=0 then //给予每一个数字编号
        begin
            inc(tail); //给予编号
            recf[num]:=tail; 
            bucket[tail]:=num;
        end;
        root[i]:=cnt+1;
        fa:=root[i-1];
        Build(1,n,recf[num]); //往编号的位置插入,代替离散化。不过你是求区间第K大的话这样子是不行的
    end;

    for i:=1 to m do
    begin
        read(l,r); 
        condition:=(r-l+1)/2; //条件,小数类型
        now:=root[l-1]; 
        fa:=root[r];
        find:=0;
        Query(1,n);
        writeln(find);
    end;
end.
```

---

## 作者：never_see (赞：0)


这题并不难吧。

就是一个裸的主席树(虽然我手冷调了好久)

权值线段树往差值大于$l-r+1$的那一边走






    
```cpp
#include<cstdio>
template <typename Type> inline void Read( Type& in ){
    in = 0;char ch=getchar();
    for(;ch> '9'||ch< '0';ch=getchar());
    for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';
}
const int MAXN = 5e5 +1;
int n,m,Ct,u,v,In;
int Root[MAXN],Lc[MAXN*20],Rc[MAXN*20],Sum[MAXN*20];
void Build( int& Nd,int Pt,int l,int r,int p ){
    Nd = ++Ct;
    Sum[Nd] = Sum[Pt]+1;
    if( l==r )return;
    Lc[Nd] = Lc[Pt];Rc[Nd] = Rc[Pt];
    int Mid = l+r >>1;
    if( p<=Mid )Build( Lc[Nd],Lc[Pt],l,Mid,p );
    else Build( Rc[Nd],Rc[Pt],Mid+1,r,p );
}
int Query( int Nd,int Pt,int l,int r,int k ){
    if( l==r )return l;
    int Mid = l+r >>1;
    if( Sum[Lc[Nd]]-Sum[Lc[Pt]]>k ) return Query( Lc[Nd],Lc[Pt],l,Mid,k );
    else if( Sum[Rc[Nd]]-Sum[Rc[Pt]]>k ) return Query( Rc[Nd],Rc[Pt],Mid+1,r,k );
    return 0;
}
int main(){
    Read( n );Read( m );
    for( int i=1;i<=n;i++ )Read( In ),Build( Root[i],Root[i-1],1,n,In );
    while( m-- ){
        Read( u );Read( v );
        printf("%d\n",Query( Root[v],Root[u-1],1,n,v-u+1>>1 ));
    }
    return 0;
}
```

---

