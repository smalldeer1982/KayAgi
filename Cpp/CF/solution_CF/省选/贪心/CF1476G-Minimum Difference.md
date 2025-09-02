# Minimum Difference

## 题目描述

You are given an integer array $ a $ of size $ n $ .

You have to perform $ m $ queries. Each query has one of two types:

- " $ 1 $ $ l $ $ r $ $ k $ " — calculate the minimum value $ dif $ such that there are exist $ k $ distinct integers $ x_1, x_2, \dots, x_k $ such that $ cnt_i > 0 $ (for every $ i \in [1, k] $ ) and $ |cnt_i - cnt_j| \le dif $ (for every $ i \in [1, k], j \in [1, k] $ ), where $ cnt_i $ is the number of occurrences of $ x_i $ in the subarray $ a[l..r] $ . If it is impossible to choose $ k $ integers, report it;
- " $ 2 $ $ p $ $ x $ " — assign $ a_{p} := x $ .

## 样例 #1

### 输入

```
12 11
2 1 1 2 1 1 3 2 1 1 3 3
1 2 10 3
1 2 11 3
2 7 2
1 3 9 2
1 1 12 1
1 1 12 4
2 12 4
1 1 12 4
2 1 5
1 3 12 2
1 1 4 3```

### 输出

```
5
4
1
0
-1
5
0
1```

# 题解

## 作者：dead_X (赞：13)

## 前言
莫队板题，适合新手练习。
## 思路
~~看到区间，数颜色，带修，离线，$10^5$，我啪一下就扔了个带修莫队模板，很快啊！~~

考虑莫队。

由于这题里我们要计算的式子中，只和 $cnt_i$ 有关，而和 $x_i$ 无关。因此我们直接维护**每个 $cnt$ 的值的数量**（这个套路同样可以用于莫队维护区间众数）。

维护号每个 $cnt$ 的值的出现次数的数组 $ccnt$ 后，我们就可以转化问题了。

现在的问题是，找出最小的 $r-l$，使得 $\sum\limits_{i=l}^rccnt_i\geq k$。

显然我们可以双指针扫一遍，复杂度是 $O(n^2)$ 的。然后你考虑维护 $k$ 不同的值，发现**一般情况**下几乎没法维护。

这时，一个关键的信息出现了：$\sum i\times ccnt_i\leq r-l+1\leq n$

于是我们发现 $ccnt_i>0$ 的 $i$ 的个数是 $\sqrt n$ 级别的！ 

这就好做多了：我们直接用链表维护 $ccnt_i>0$ 的 $i$，最后在每个询问时提取这些 $i$ 并排序。这次由于只有 $\sqrt n$ 个数了，双指针是对的。

时间复杂度 $O(n^\frac{5}{3}+n\sqrt n\log n)$。
## 代码
```
// Problem: G. Minimum Difference
// Contest: Codeforces - Educational Codeforces Round 103 (Rated for Div. 2)
// URL: https://codeforces.ml/contest/1476/problem/G
// Memory Limit: 256 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
int n,m,qcnt,bl;
int a[100003],cnt[1000003],ccnt[1000003],Ans[100003];
struct query
{
	int l,r,k,id,pl,pr,t;
	bool operator<(const query&a) const { return (pl<a.pl)||(pl==a.pl&&((pr<a.pr)||(pr==a.pr&&t<a.t))); }
}q[100003];
int p[100003],val[100003],tcnt=1;
int nxt[100003],lst[1000003],tmp[1003],sz=0,H=0,T=100001,tot=0;
inline void D(int x)
{                
	if(x<=0) return ;
	if(!--ccnt[x]) 
	{
		if(x==H) H=nxt[x];
		if(x==T) T=lst[x];
		lst[nxt[x]]=lst[x],nxt[lst[x]]=nxt[x];
	}
	return ;
}
inline void A(int x)
{
	if(x<=0) return;
	if(!ccnt[x]++) nxt[lst[T]]=x,lst[x]=lst[T],nxt[x]=T,lst[T]=x;
}
inline void add(int x){D(cnt[x]),A(++cnt[x]);return;}
inline void del(int x){D(cnt[x]),A(--cnt[x]);return;}
signed main()
{
	nxt[0]=100001,nxt[100001]=100001;
	n=read(),m=read(),bl=pow(n,0.6666)+1;
	for(int i=1; i<=n; i++) a[i]=read();
	for(int i=1,x,y; i<=m; i++) 
	{
		int op=read();
		if(op==1) 
		q[++qcnt].l=read(),q[qcnt].r=read(),q[qcnt].k=read(),q[qcnt].pl=q[qcnt].l/bl,q[qcnt].pr=q[qcnt].r/bl,q[qcnt].t=tcnt,q[qcnt].id=qcnt;
		else ++tcnt,x=read(),y=read(),p[tcnt]=x,val[tcnt]=y-a[x],a[x]=y;
	}
	sort(q+1,q+qcnt+1);
	for(int i=1,l=1,r=0,t=tcnt; i<=qcnt; i++)
	{
		while(t<q[i].t) 
		{
			++t;
			if(l<=p[t] && p[t]<=r) 
			{
				del(a[p[t]]);
				a[p[t]]+=val[t];
				add(a[p[t]]);
			}
			else a[p[t]]+=val[t];
		}
		while(t>q[i].t)
		{
			if(l<=p[t] && p[t]<=r) 
			{
				del(a[p[t]]);
				a[p[t]]-=val[t];
				add(a[p[t]]);
			}
			else a[p[t]]-=val[t];
			--t;
		}
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(l<q[i].l) del(a[l++]);
		while(r>q[i].r) del(a[r--]);
		Ans[q[i].id]=998244353;
		sz=0;
		for(int i=H; i!=T; i=nxt[i]) if(i) tmp[++sz]=i;
		//for(int i=1; i<=100000; ++i) if(ccnt[i]) tmp[++sz]=i;
		sort(tmp+1,tmp+sz+1);
		for(int l=1,r=1,g=0; r<=sz; ++r)
		{
			g+=ccnt[tmp[r]];
			if(g<q[i].k) continue;
			while(g-ccnt[tmp[l]]>=q[i].k) g-=ccnt[tmp[l]],++l;
			Ans[q[i].id]=min(Ans[q[i].id],tmp[r]-tmp[l]);
		}
		if(Ans[q[i].id]==998244353) Ans[q[i].id]=-1;
	} 
	for(int i=1; i<=qcnt; i++) printf("%d\n",Ans[i]);
	return 0;
}
```

---

## 作者：hzlqwq (赞：10)

[题目链接](https://www.luogu.com.cn/problem/CF1476G)

注意到有比较复杂的区间询问，且跟值的出现次数有关，且序列长度、询问个数和值域都较小，考虑**带修莫队**。

首先，希望出现次数的极差最小，那么肯定要维护出现次数，以及**每种出现次数的出现次数**（即“有多少个数出现了这么多次”）；于是我们可以开两个桶，$cnt_i$ 表示 $i$ 出现了多少次，$cc_i$ 表示有多少个数出现了 $i$ 次。可以做到 $O(1)$ 修改。

此处有一个重要的性质：不同的出现次数最多有 $O(\sqrt{n})$ 种。

> 简证：如果希望不同的出现次数最多，那么肯定从 $1$ 开始，每种出现次数只有一个数是最好的，那么假设 $cc_1\sim cc_x$ 都为 $1$，则序列长度至少要是 $1+2+\cdots +x=O(x^2)$，因此 $x$ 最大是 $O(\sqrt{n})$ 的。

因此，若每次询问时，我们可以快速找到那些不为 $0$ 的出现次数，就可以在上面进行双指针，找到每个最短的 $\sum cc_i\geq k$ 的段，从而 $O(\sqrt{n})$ 计算答案。

那么，怎么快速找到那些 $cc_i>0$ 的 $i$ 呢？

我们可以把整个 $cc$ 分为 $B$ 段，对于每段，维护一下这一段里面所有 $cc$ 的和，如此一来，我们可以先遍历所有段，如果某一段的和不为 $0$，再遍历其中的所有位置，否则就不用管这个段了。

通过和上文“简证”部分类似的方法，我们可以发现，最多有 $O(\sqrt{B})$ 段的和不为 $0$，因此查找的时间复杂度是 $O(B+\frac{n\sqrt{B}}{B})$ 的，当 $B=n^{\frac{2}{3}}$ 时，其为 $O(n^{\frac{2}{3}})$ 最优。

那么，总的时间复杂度就是 $O(n^{\frac{5}{3}})$ 了（$n,m$ 视为同阶）。

~~其实就是值域分块~~

**目前是你谷最优解，同时在 CF 最优解第一页。**

![](https://cdn.luogu.com.cn/upload/image_hosting/8altrz22.png)

[代码（CF 提交记录）](https://codeforces.com/contest/1476/submission/257709256)

---

## 作者：xhhhh36 (赞：9)

[传送门](https://www.luogu.com.cn/problem/CF1476G)

这题可以使用带修莫队来解决。

先开两个桶 $cnt$ 和 $cntt$。$cnt_i$ 表示值为 $a_i$ 的数在当前莫队维护的区间 $[l,r,t]$ 出现的次数；$cntt_i$ 表示当前 $cnt$ 数组中值为 $i$ 的个数，也就是 $a$ 数组在当前莫队维护的区间 $[l,r,t]$ 中出现次数为 $i$ 的值的个数。

在维护的区间变化的时候让原来的 $cntt_{cnt_{a_x}}$ 减 $1$，将 $cnt_{a_x}$ 修改后再让现在的 $cntt_{cnt_{a_x}}$ 都加 $1$ 即可，那么每次区间变化时可以 $O(1)$ 维护这两个数组的值，修改操作同理。

那么在 $cntt$ 数组上选出一段连续的区间 $cntt_l$ 到 $cntt_r$ 的和为 $k$，那么就相当于在 $cnt$ 数组中选出 $k$ 个值，并且极差为 $r-l+1$，即极差为选出 $cntt$ 数组区间的长度。那么原问题可以转化为：在 $cntt$ 数组上取一段连续的区间使区间和大于等于 $k$，求区间最小长度，如果 $cntt$ 数组的总和小于 $k$ 输出 $-1$。

为什么是大于等于 $k$ 呢？因为当你得到了最小的满足条件的区间长度，并且此时区间和大于 $k$，那么可以通过删去部分已选的 $cnt$ 的值来使 $cntt$ 数组的区间和等于 $k$。因为此时区间长度已经最优，那么不可能删去已选 $cntt$ 数组区间的左端点或右端点的值，那么原来求出的区间答案是最优的并且可以取到。

那么我们可以直接在每次询问时根据当前的 $cntt$ 数组跑一次双指针就能求出答案的值，但是这样时间复杂度为 $O(nm)$ 的，那么考虑优化。 

可以证明最多 $cntt$ 数组中最多只有 $\sqrt n$ 个不同的值。因为想要 $cntt$ 数组中的值的数量最多，最优的方法就是让 $cntt_1$ 到 $cnt_x$ 均为 $1$，此时共有 $1+2+\dots+x\approx x^2$ 个数。而 $a$ 数组共有 $n$ 个数，所以 $x$ 最大为 $\sqrt n$ 级别的数。

那么在做双指针的过程中 $cntt$ 数组中只有 $\sqrt n$ 个对答案有意义的数，其他的数都为 $0$，所以只需要找出这 $\sqrt n$ 个数来跑双指针即可。

可以考虑用分块的思想，将 $cntt$ 数组分成 $A$ 块，那么每块长为 $\frac{n}{A}$，此时最多只有 $\sqrt a$ 个块的和不为 $0$。因为如果要让尽量多的块不为 $0$，最优的方法就是让每个块的第一个数为 $1$，即 $cntt_1, cntt_{1+\frac{n}{A}},\dots,cnt_{1+\frac{xn}{A}}$ 均为 $1$，此时有 $1+1+\frac{n}{A}+\dots+1+\frac{xn}{A}\approx x+\frac{x^2n}{A}$ 个数。又因为共有 $n$ 个数，那么 $x$ 最大为 $\sqrt A$ 级别的数，所以最多只有 $\sqrt A$ 个块的和不为 $0$。

那么可以再开一个数组 $tmp$ 来维护每个块的和，每次求答案的时候枚举每个块，如果这个块的和不为 $0$ 就暴力遍历这个块的所有数，将不为 $0$ 的数直接找出来放进另一个数组中，最后跑双指针即可。这样每次找出不为 $0$ 的数的时间复杂度为 $O(A+\frac{n\sqrt A}{A})$ 此时当 $A$ 取 $n^\frac{2}{3}$ 时间复杂度为 $O(n^\frac{2}{3}+n^{1+\frac{2}{3}\times \frac{1}{2}-\frac{2}{3}})=O(n^\frac{2}{3})$ 最优。

这样每次求答案的时间复杂度降为为 $O(n^\frac{2}{3})$，总复杂度 $O(n^\frac{2}{3}m)$。
# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N=1e5+5;
int n,m,bl[N],a[N],len,t[N],cnt[N],cntt[N],ct,tim,change[N][2],tmp[N],ll[N],rr[N],ans[N];
struct node{
	int l,r,id,k,t;
}q[N];
bool cmp(node a,node b){
	return bl[a.l]!=bl[b.l]?a.l<b.l:bl[a.r]!=bl[b.r]?a.r<b.r:a.t<b.t;
}
void add(int x){
	x=a[x];
	cntt[cnt[x]]--;
	tmp[bl[cnt[x]]]--;
	cnt[x]++;
	cntt[cnt[x]]++;
	tmp[bl[cnt[x]]]++;
}
void del(int x){
	x=a[x];
	cntt[cnt[x]]--;
	tmp[bl[cnt[x]]]--;
	cnt[x]--;
	cntt[cnt[x]]++;
	tmp[bl[cnt[x]]]++;
}
void cg(int t,int l,int r){
	int x=change[t][0];
	if (l<=x&&x<=r){
		del(x);
		swap(a[x],change[t][1]);
		add(x);
	}
	else swap(a[x],change[t][1]);
}
int as[N],v[N];
int cal(int k){
	int ct=0;
	for (int i=1;i<=bl[n];i++){
		if (tmp[i]){
			for (int j=ll[i];j<=rr[i];j++){
				if (cntt[j]){
					as[++ct]=cntt[j];
					v[ct]=j;
				}
			}
		}
	}
	int ans=INT_MAX,sum=0,r=0;
	for (int l=1;l<=ct;l++){
		while (sum<k&&r<ct){
			r++;
			sum+=as[r];
		}
		if (sum>=k) ans=min(ans,v[r]-v[l]);
		sum-=as[l];
	}
	if (ans==INT_MAX) return -1;
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	len=pow(n,2.0/3);
	for (int i=1;i<=n;i++){
		cin>>a[i];
		bl[i]=(i-1)/len+1;
		if (!ll[bl[i]]) ll[bl[i]]=i;
		rr[bl[i]]=i;
	}
	for (int i=1;i<=m;i++){
		int op;
		cin>>op;
		if (op==1){
			ct++;cin>>q[ct].l>>q[ct].r>>q[ct].k;
			q[ct].id=ct;q[ct].t=tim;
		}
		else {
			tim++;cin>>change[tim][0]>>change[tim][1];
		}
	}
	sort(q+1,q+1+ct,cmp);
	int l=1,r=0,t=0;
	for (int i=1;i<=ct;i++){
		int L=q[i].l,R=q[i].r,T=q[i].t;
		while (t<q[i].t) cg(++t,l,r);
		while (t>q[i].t) cg(t--,l,r);
		while (l>L) add(--l);
		while (r<R) add(++r);
		while (l<L) del(l++);
		while (r>R) del(r--);
		ans[q[i].id]=cal(q[i].k);
	}
	for (int i=1;i<=ct;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：zcxxnqwq (赞：4)

首先它显然需要用带修莫队，问题就是如何求最小极差。

这种出现次数相关的题有一个非常巧妙的性质：$\sum\limits_{i=1}^k i=\dfrac{k(k+1)}{2}=n$，则不同的出现次数 $k$ 最多是 $O(\sqrt n)$ 级别的，可以进行一些暴力计算。

在做莫队时维护 $tong_i$ 表示有多少个不同的数出现了 $i$ 次，求最小极差那就双指针就行了。但有很多 $tong_i=0$ 的情况不能暴力扫，所以要用一个链表维护 $tong_i$ 有值的位置，在有意义的位置上做双指针。

要注意莫队加入一个数的时候新的值插入链表的哪个位置要分类讨论一下。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ff(i,s,e) for(int i=(s);i<=(e);++i)
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e5+5,lim=1e5;
int n,m,a[N],siz,bel[N],cc,cq,ans[N];
struct qwq{
    int l,r,k,t,id;
    bool operator < (const qwq &a) const{
        if(bel[l]!=bel[a.l]) return bel[l]<bel[a.l];
        if(bel[r]!=bel[a.r]) return bel[r]<bel[a.r];
        return t<a.t;
    }
}q[N];
struct qaq{
    int pos,x;
}c[N];
int tong[N],cnt[N],pre[N],nxt[N];
inline void erase(int x){
    nxt[pre[x]]=nxt[x],pre[nxt[x]]=pre[x];
}
inline void ins(int pos,int x){
    nxt[x]=nxt[pos],pre[x]=pos,nxt[pos]=x,pre[nxt[x]]=x;
}
inline void add(int x){
    int &tmp=cnt[x];
    --tong[tmp];
    if(!tong[tmp]) erase(tmp);
    ++tmp,++tong[tmp];
    if(tong[tmp]==1) ins(tong[tmp-1]?tmp-1:pre[tmp-1],tmp);
}
inline void del(int x){
    int &tmp=cnt[x];
    --tong[tmp];
    if(!tong[tmp]) erase(tmp);
    --tmp,++tong[tmp];
    if(tong[tmp]==1) ins(pre[tmp+1],tmp);
}
inline void change(int x,int i){
    if(c[x].pos>=q[i].l&&c[x].pos<=q[i].r){
        del(a[c[x].pos]),add(c[x].x);
    }
    swap(a[c[x].pos],c[x].x);
}
signed main(){
    n=read(),m=read(),siz=pow(n,0.66),tong[0]=n+1,nxt[0]=lim+1;
    ff(i,1,n) a[i]=read(),bel[i]=(i+siz-1)/siz;
    ff(i,1,m){
        int op=read(),x=read(),y=read();
        if(op==1) q[++cq]={x,y,read(),cc,cq};
        else c[++cc]={x,y};
    }
    sort(q+1,q+cq+1);
    int l=1,r=0,tim=0;
    ff(i,1,cq){
        while(l>q[i].l) add(a[--l]);
        while(r<q[i].r) add(a[++r]);
        while(l<q[i].l) del(a[l++]);
        while(r>q[i].r) del(a[r--]);
        while(tim<q[i].t) change(++tim,i);
        while(tim>q[i].t) change(tim--,i);
        int mn=1e9;  
        for(int l=nxt[0],r=0,sum=0;r<=lim;){
            while(r<=lim&&sum<q[i].k) r=nxt[r],sum+=tong[r];
            while(sum>=q[i].k) mn=min(mn,r-l),sum-=tong[l],l=nxt[l];
        }
        ans[q[i].id]=mn==1e9?-1:mn;
    }
    ff(i,1,cq) printf("%d\n",ans[i]);
    return 0;
}
```



---

## 作者：SilverLi (赞：2)

> [Minimum Difference の 传送门](https://www.luogu.com.cn/problem/CF1476G)
>
> [戳一戳](https://www.cnblogs.com/Silver-Wolf/p/18714630/CF1476G)

~~不~~显然不同出现次数的数**最多** $O \left ( \sqrt n \right )$。

> $\sum\limits_{i=1}^k i = n$
> 
> 算出 $k$ 最大为 $\sqrt n$。

则**莫队 + 值域分块**，维护每个出现次数有几个数。

查询时扫所有块，块内有值就暴力整块，把所有有值的位置提出来，做双指针。

具体一点，设当前双指针的左右端点分别为 $l, r$。

不断循环直到 $\left [ l, r \right ]$ 总的出现次数大于等于 $k$。

然后每次把 $l$ 往后移一位就行。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int f = 0, ans = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return f ? -ans : ans;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
constexpr int N = 1e5 + 5, V = 1e5, inf = 1e9;
int n, m, a[N], res[N];
int blk, l, r, bl[N], mp[N];
struct oper
{
    int p, lst, x;
} op[N];
struct quest
{
    int l, r, k, tim, id;
    bool operator<(const quest &rhs) const
    {
        if (bl[l] != bl[rhs.l])
            return l < rhs.l;
        if (bl[r] != bl[rhs.r])
            return r < rhs.r;
        return tim < rhs.tim;
    }
} q[N];
namespace block
{
    int blk, tot, bl[N], L[N], R[N];
    int t, s[N], cnt[N], cnt_blk[N];
    inline void init()
    {
        blk = pow(V, 2.0 / 3);
        tot = V / blk + (bool)(V % blk);
        for (int i = 1; i <= V; ++i)
            bl[i] = (i - 1) / blk + 1;
        for (int i = 1; i <= tot; ++i)
            L[i] = (i - 1) * blk + 1, R[i] = i * blk;
        R[tot] = V;
    }
    inline void modify(int x, int w) { x ? (cnt[x] += w, cnt_blk[bl[x]] += w) : 0; }
    inline int get_ans(int k)
    {
        t = 0;
        for (int i = 1; i <= tot; ++i)
            if (cnt_blk[i])
                for (int j = L[i]; j <= R[i]; ++j)
                    if (cnt[j])
                        s[++t] = j;
        int ans = inf, sum = 0;
        for (int l = 1, r = 0; l <= t; ++l)
        {
            while (r < t && sum < k)
                sum += cnt[s[++r]];
            if (sum < k)
                break;
            ans = min(ans, s[r] - s[l]);
            sum -= cnt[s[l]];
        }
        return ans;
    }
}
inline void init()
{
    block::init(), blk = pow(n, 2.0 / 3);
    for (int i = 1; i <= n; ++i)
        bl[i] = (i - 1) / blk + 1;
}
inline void insert(int x) { block::modify(mp[x], -1), block::modify(++mp[x], 1); }
inline void remove(int x) { block::modify(mp[x], -1), block::modify(--mp[x], 1); }
inline void insert_in_bound(int i)
{
    if (i >= l && i <= r)
        block::modify(mp[a[i]], -1), block::modify(++mp[a[i]], 1);
}
inline void remove_in_bound(int i)
{
    if (i >= l && i <= r)
        block::modify(mp[a[i]], -1), block::modify(--mp[a[i]], 1);
}
inline void forward(int i)
{
    auto &[p, lst, x] = op[i];
    remove_in_bound(p);
    a[p] = x;
    insert_in_bound(p);
}
inline void backward(int i)
{
    auto &[p, lst, x] = op[i];
    remove_in_bound(p);
    a[p] = lst;
    insert_in_bound(p);
}
signed main()
{
    // freopen("chk.in", "r", stdin);
    // freopen("chk.out", "w", stdout);
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    init();
    int que = 0, ti = 0;
    for (int i = 1; i <= m; ++i)
        if (read() == 1)
        {
            ++que, q[que] = {0, 0, 0, ti, que};
            q[que].l = read(), q[que].r = read(), q[que].k = read();
        }
        else
        {
            ++ti;
            op[ti].lst = a[op[ti].p = read()];
            a[op[ti].p] = op[ti].x = read();
        }
    while (ti)
        a[op[ti].p] = op[ti].lst, --ti;
    sort(q + 1, q + que + 1);
    l = 1, r = 0;
    for (int i = 1; i <= que; ++i)
    {
        while (l > q[i].l)
            insert(a[--l]);
        while (r < q[i].r)
            insert(a[++r]);
        while (l < q[i].l)
            remove(a[l++]);
        while (r > q[i].r)
            remove(a[r--]);
        while (ti < q[i].tim)
            forward(++ti);
        while (ti > q[i].tim)
            backward(ti--);
        res[q[i].id] = block::get_ans(q[i].k);
    }
    for (int i = 1; i <= que; ++i)
        write(res[i] == inf ? -1 : res[i]), putchar('\n');
    return 0;
}
```

---

## 作者：StarsIntoSea_SY (赞：2)

# Solution

前置知识：带修莫队，分块。

修改部分与[带修莫队板子题](https://www.luogu.com.cn/problem/P1903)基本一致，因此这里重点讲如何维护和查询。

考虑新开一个桶 $cnt$，表示出现第 $i$ 次的数有 $cnt_{i}$ 个，只需一次 $O(1)$ 修改。

在查询时，可以用双指针来 $O(n)$ 遍历 $cnt$，不断更新答案。但是时间复杂度共 $O(nm)$，需要优化。

不难发现，在双指针遍历 $cnt$ 会有大量为 $0$ 的情况，浪费时间。因此使用分块来维护 $cnt$，每个块记录当前数值的和。查询时从块开始遍历，**一旦出现某个块为 $0$ 时直接跳过，否则在块内暴力遍历找不为 $0$ 数**，统一存进数组 $e$ 中。这样就只留下了有用信息，再用双指针从 $e$ 中找答案即可。

时间复杂度 $O(n^\frac{2}{3} m)$，常数较大。最坏可能被卡到 $O(nm)$，也许是数据水或者放了这种方法。

# Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct Que{int l,r,k,t,id;};
struct Upd{int p,x;};
const int N=100005;
const int inf=2e9;
int n,m,T;
int cnt[N],d[N],a[N],ans[N],maxn=0,minn=0;
int sum[N],pos[N],L[N],R[N],bl;
Que que[N];
Upd upd[N];

inline bool cmp(Que a,Que b){
	if(a.l/T==b.l/T){
		if(a.r/T==b.r/T) return a.t/T<b.t/T;
		return a.r/T<b.r/T;
	}
	return a.l/T<b.l/T;
}

inline void fen_kuai(){     //建分块，纯板子
	bl=sqrt(n);
	for(int i=1;i<=bl;++i){
		L[i]=(i-1)*bl+1;
		R[i]=i*bl;
	}
	if(R[bl]<n) bl++,L[bl]=R[bl-1]+1,R[bl]=n;
	for(int i=1;i<=bl;++i)
		for(int j=L[i];j<=R[i];++j)
			pos[j]=i;
}

inline void add(int x){  //x出现了第d[x]次
	d[x]++;             //第d[x]次出现的数有cnt[d[x]]个
	cnt[d[x]]++;   
	cnt[d[x]-1]--;
	sum[pos[d[x]]]++;  //sum[]为当前块内数值之和
	sum[pos[d[x]-1]]--;
}

inline void del(int x){
	d[x]--;           
	cnt[d[x]]++;      
	cnt[d[x]+1]--;
	sum[pos[d[x]]]++;
	sum[pos[d[x]+1]]--;
}

inline int solve(int k){              //有e[][2]个出现了第e[][1]次的数
	int e[N][3],lc=0,res=inf;
	for(int i=1;i<=bl;++i){
		if(sum[i]<=0) continue;     //分块优化，遇到0时直接跳过
		for(int j=L[i];j<=R[i];++j) if(cnt[j]>0){ //否则暴力找不为0的
			++lc;
			e[lc][2]=cnt[j];
			e[lc][1]=j;
		}
	}
	if(lc==0) return -1;
	int l=1,r=1,temp=e[1][2];
	while(l<=r){            //双指针搜索
		if(temp>=k){    //当区间内的数满足时，更新答案
			res=min(res,e[r][1]-e[l][1]); 
			l++;  //贪心，左指针右移，因为temp值越小，所求的答案越小
			temp-=e[l-1][2];
		}
		else if(r==lc){ //右指针到头时，只能左指针右移
			l++;   
			temp-=e[l-1][2];
		}
		else { //否则一律右移右指针
			r++;
			temp+=e[r][2];
		}
	}
	return res==inf?-1:res;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	T=pow(n,0.666); 
	fen_kuai();
	int lc=0,pc=0;
	for(int i=1;i<=m;++i){
		int opt,x,y,k;
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) scanf("%d",&k),++lc,que[lc]={x,y,k,pc,lc};
		else ++pc,upd[pc]={x,y};
	}
	sort(que+1,que+lc+1,cmp);
	int x=1,y=0,now=0;
	for(int i=1;i<=lc;++i){ //带修莫队板子
		while(x>que[i].l) --x,add(a[x]);
		while(y<que[i].r) ++y,add(a[y]);
		while(x<que[i].l) del(a[x]),++x;
		while(y>que[i].r) del(a[y]),--y;
		while(now<que[i].t){
			now++;
			if(x<=upd[now].p && upd[now].p<=y) add(upd[now].x),del(a[upd[now].p]);
			swap(upd[now].x,a[upd[now].p]);
		}
		while(now>que[i].t){
			if(x<=upd[now].p && upd[now].p<=y) add(upd[now].x),del(a[upd[now].p]);
			swap(upd[now].x,a[upd[now].p]);
			now--;
		}
		ans[que[i].id]=solve(que[i].k);
	}
	for(int i=1;i<=lc;++i) printf("%d\n",ans[i]);
}
```

---

## 作者：yinianxingkong (赞：2)

# [CF1476G](https://www.luogu.com.cn/problem/CF1476G)

## 前言

算是写带修莫队以来第一次独立切紫！

~~还是 CF 3100的！~~

~~快夸我快夸我 qwq！~~

写完后看题解，发现竟然只有一篇不带 $\log$，震惊我了。

所以在这里给大家分享一种 $O(n^\frac{5}{3}+n^\frac{3}{2})$ 的做法。

~~然鹅并没有什么卵用，一个 $\log$ 显然不至于。~~

## 解法分析

注：全文假设 $n$，$m$，$V$ 同阶。

题目意思大概是，单点修改，求区间内选 $k$ 个互不相同的数，它们出现次数的最小极差。

离大谱的询问，加上单点修改，自然考虑带修莫队。

那莫队维护什么呢？

肯定要记录一个数的出现次数。极差是值域上的问题，在没有别的思路前只能考虑继续开桶维护出现次数的次数。

这就转换成了一个经典问题：给你一个序列，求最小的和大于等于 $k$ 的区间长度。显然可以双指针维护，时间复杂度 $O(n)$。

到这里似乎已经是尽头了。我们继续发掘性质，发现由于桶维护的是出现次数的次数，所以有效空间（这里指非 $0$ 位置）十分有限。直觉告诉我们，当一个数的出现次数很多时，它会挤掉别的数的位置。事实上，这里可以证明有效空间为 $O(\sqrt n)$ 级别。

设 $cnt_x$ 表示 $x$ 的出现次数。

当 $cnt_x \le \sqrt n$ 时，显然有效空间是 $O(\sqrt n)$。

当 $cnt_x > \sqrt n $ 时，因为出现次数的总和是 $O(n)$ 级别的，所以这样的数是 $O(\sqrt n)$ 级别的。

所以，用 `set` 维护，可做到 $O(n^\frac{5}{3} \log \sqrt n + n^\frac{3}{2} \log \sqrt n)$，当然，你可以采用链表做到 $O(1)$ 插入 $O(\log \sqrt n)$ 提取来优化掉前面的 $\log$。

好了，基本做法结束，**正片开始**。

想要优化复杂度，只能继续发掘性质。发现瓶颈在于不能平衡插入和查询的时间复杂度，想要优化只能想办法在插入 $O(1)$ 时就维护好有序数列。

观察一下，还是因为我们维护的是出现次数的次数，而莫队是**单维增量**（这是我的叫法，你可以看作是每次单点修改）的，也就是说，每次出现次数的**变化量为一**。

接下来就好办了，我们多维护一个数组表示每个数在链表中的位置，莫队的移动操作就可以看作加一减一，分讨即可。

~~至此，Jocker 的 $O(n^\frac{5}{3}+n^\frac{3}{2})$ 完结。~~

## 实现

几乎没什么细节，调完样例就一遍过了，其他在上面都讲的很清楚了。

## 代码

如下：

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
namespace TYX_YNXK{
	#define il inline
	#define bl bool
	#define ll long long
	#define vd void
	#define N 100005
	#define INF 0x7fffffff
	#define pb push_back
	#define pf push_front
	#define DEBUG cout<<"You are right,but you are wrong"<<'\n'
	#define END cout<<"You are right,but you are right now"<<'\n'
	int n,m,s[N],b[N<<1],p,nowque,nowupd,ans[N],to[N],tong[N<<1],now;
	namespace List{
		int tot,st[N],top,head,tail;
		struct node{
			int pre,suf;
			int pos,v;
		}list[N];
		il int neww(int a1=0,int a2=0){
			int k=top?st[top--]:++tot;
			list[k].pre=list[k].suf=0;
			list[k].pos=a1,list[k].v=a2;
			return k;
		}
		il vd push_back(int a,int b){
			list[b].suf=list[a].suf;
			if(list[b].suf) list[list[b].suf].pre=b;
			if(a) list[a].suf=b;list[b].pre=a;
			if(!list[b].suf) tail=b;
			if(!list[b].pre) head=b;
		}
		il vd push_front(int a,int b){
			list[b].pre=list[a].pre;
			if(list[b].pre) list[list[b].pre].suf=b;
			if(a) list[a].pre=b;list[b].suf=a;
			if(!list[b].suf) tail=b;
			if(!list[b].pre) head=b;
		}
		il vd pop(int a){
			if(head==a) head=list[a].suf;
			if(tail==a) tail=list[a].pre;
			if(list[a].pre) list[list[a].pre].suf=list[a].suf;
			if(list[a].suf) list[list[a].suf].pre=list[a].pre;
			st[++top]=a;
		}
	}using namespace List;
	namespace MoTeam{
		const int len=2155;
		int belong[N];
		il vd init(){for(int i=1;i<=n;i++) belong[i]=(i-1)/len+1;}
	}
	struct upd{
		int pos,k;
		upd(int a1=0,int a2=0){pos=a1,k=a2;}
	}u[N];
	struct que{
		int l,r,t,k,id;
		que(int a1=0,int a2=0,int a3=0,int a4=0,int a5=0){l=a1,r=a2,t=a3,k=a4,id=a5;}
		bl operator<(const que& a){return MoTeam::belong[l]!=MoTeam::belong[a.l]?l<a.l:MoTeam::belong[r]!=MoTeam::belong[a.r]?MoTeam::belong[l]&1?r<a.r:r>a.r:MoTeam::belong[r]&1?t<a.t:t>a.t;}
	}q[N];
	il vd add(int x){
		if(!tong[x]){
			tong[x]=1,++now;
			if(!to[1]) to[1]=neww(1,0),pf(head,to[1]);
			++list[to[1]].v;
		}else{
			++tong[x];
			if(!to[tong[x]]) to[tong[x]]=neww(tong[x],0),pb(to[tong[x]-1],to[tong[x]]);
			--list[to[tong[x]-1]].v,++list[to[tong[x]]].v;
			if(!list[to[tong[x]-1]].v) pop(to[tong[x]-1]),to[tong[x]-1]=0;
		}
	}
	il vd del(int x){
		if(tong[x]==1){
			tong[x]=0,--now;
			--list[to[1]].v;
			if(!list[to[1]].v) pop(to[1]),to[1]=0;
		}else{
			--tong[x];
			if(!to[tong[x]]) to[tong[x]]=neww(tong[x],0),pf(to[tong[x]+1],to[tong[x]]);
			--list[to[tong[x]+1]].v,++list[to[tong[x]]].v;
			if(!list[to[tong[x]+1]].v) pop(to[tong[x]+1]),to[tong[x]+1]=0;
		}
	}
	il vd update(int k,int x){
		if(u[x].pos>=q[k].l&&u[x].pos<=q[k].r) add(u[x].k),del(s[u[x].pos]);
		swap(s[u[x].pos],u[x].k);
	}
	il int query(int x){
		int l=head,r=head,sum=0,res=INF;
		while(r){
			sum+=list[r].v;
			while(sum>=x){
				res=min(res,list[r].pos-list[l].pos);
				sum-=list[l].v;
				l=list[l].suf;
			}
			r=list[r].suf;
		}
		return res;
	}
	signed main(){
		cin>>n>>m;p=n;
		for(int i=1;i<=n;i++) cin>>s[i],b[i]=s[i];
		for(int i=1;i<=m;i++){
			int opt,x,y,k;cin>>opt>>x>>y;
			switch(opt){
				case 1:cin>>k;++nowque;q[nowque]=(que){x,y,nowupd,k,nowque};break;
				case 2:++nowupd;u[nowupd]=(upd){x,y},b[++p]=y;break;
			}
		}
		sort(b+1,b+1+p);p=unique(b+1,b+1+p)-b-1;b[p+1]=INF,b[0]=-INF;
		for(int i=1;i<=n;i++) s[i]=lower_bound(b+1,b+1+p,s[i])-b;
		for(int i=1;i<=nowupd;i++) u[i].k=lower_bound(b+1,b+1+p,u[i].k)-b;
		MoTeam::init();sort(q+1,q+1+nowque);
		int l=1,r=0,t=0;
		for(int i=1;i<=nowque;i++){
			#define ql q[i].l
			#define qr q[i].r
			#define qt q[i].t
			while(l>ql) add(s[--l]);
			while(r<qr) add(s[++r]);
			while(l<ql) del(s[l++]);
			while(r>qr) del(s[r--]);
			while(t<qt) update(i,++t);
			while(t>qt) update(i,t--);
			if(now<q[i].k) ans[q[i].id]=-1;
			else ans[q[i].id]=query(q[i].k);
		}
		for(int i=1;i<=nowque;i++) cout<<ans[i]<<'\n';
		return 0;
	}
}
signed main(){
	TYX_YNXK::main();
	return 0;
}
```

## 后记

虽然在这道题里优化查询复杂度是很 Jocker 的，但这启示了我们，当时间复杂度优化不下去的时候，一定考虑观察已有的性质。

欢迎 `hack`！

---

## 作者：Tyyyyyy (赞：2)

# CF1476G

### 题意简述
给定一个数列，支持两种操作：

- 给定一个区间 $[l,r]$ 和常数 $k$，$cnt_i$ 表示**数值** $a_i$ 在 $[l,r]$ 中的出现次数。请你找到 $k$ 个**互不相同**的 $a_1,\dots,a_k$，使得 $\displaystyle\max_{i=1}^k cnt_i-\min_{i=1}^k cnt_i$ 最小，或报告无解。

- 单点修改某一位置的值。

$1\leq n,q,k,a_i\leq 10^5$。

### 题目分析
非常规的区间操作题，还带修改，考虑莫队。

记 $tcnt_x$ 表示 $cnt_i=x$ 的 $cnt_i$ 的数量，则我们需要找到一些不为 $0$ 的 $tcnt_x$，满足 $\sum tcnt_x=k$ ，且 $\max x-\min x$ 最小。

假设我们已经有了所有不为 $0$ 的 $tcnt$，这个问题显然能在 $O(n\log n)$ 的时间内排序后用双指针解决。于是我们考虑怎么记录不为 $0$ 的 $tcnt$。

显然，我们需要支持快速的插入和删除，查询则不追求速度。于是不难想到用链表来维护不为 $0$ 的 $tcnt$。

这看上去是 $O(n^{\frac{5}{3}}+qn\log n)$ 的，其实不然。

考虑对于 $tcnt$，必有 $\sum i\times tcnt_i \leq r-l+1$。因为 $tcnt$ 记录的是 $cnt$ 的数量，所以上式易证。所以，不为 $0$ 的 $tcnt$ 的数量**至多**是 $\displaystyle O(\frac{n}{\sum i})=O(\sqrt{n})$ 级别的。

因此，我们每次查询时把链表中所有非 $0$ 的位置记录下来之后排序双指针，每次的时间复杂度实际上是 $O(\sqrt{n}\log \sqrt{n})$ 的。考虑到带修莫队的复杂度，时间复杂度总共为 $O(n^{\frac{5}{3}}+q\sqrt{n}\log \sqrt{n})$，可以通过本题。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,a[N],ans[N],cnt[N],tcnt[N];
int cntq,cntu,unit;
struct query
{
	int l,r,k,t,id;
	bool operator < (query b) const
	{
		if(l/unit!=b.l/unit)return l<b.l;
		if(r/unit!=b.r/unit)
		{
			if((l/unit)&1)return r<b.r;
			return r>b.r;
		}
		if((r/unit)&1)return t<b.t;
		return t>b.t;
	}
}q[N];
struct update
{
	int p,x;
}u[N];
struct List
{
	int h,t,nxt[N],pre[N];
	void Insert(int x)
	{
		nxt[pre[t]]=x,pre[x]=pre[t],nxt[x]=t,pre[t]=x;
	}
	void Delete(int x)
	{
		if(x==h)h=nxt[x];
		if(x==t)t=pre[x];
		pre[nxt[x]]=pre[x],nxt[pre[x]]=nxt[x];	
	}	
}lis;
void add(int x)
{
	tcnt[cnt[x]]--;
	if(!tcnt[cnt[x]])lis.Delete(cnt[x]);
	cnt[x]++;
	if(!tcnt[cnt[x]])lis.Insert(cnt[x]);
	tcnt[cnt[x]]++;
}
void del(int x)
{
	tcnt[cnt[x]]--;
	if(!tcnt[cnt[x]])lis.Delete(cnt[x]);
	cnt[x]--;
	if(!tcnt[cnt[x]])lis.Insert(cnt[x]);
	tcnt[cnt[x]]++;
}
void upd(int i,int t)
{
	if(q[i].l<=u[t].p&&u[t].p<=q[i].r)
		del(a[u[t].p]),add(u[t].x);
	swap(a[u[t].p],u[t].x);
}
int tmp[N],tot;
int query(int k)
{
	tot=0;
	for(int i=lis.h;i!=lis.t;i=lis.nxt[i])if(i)tmp[++tot]=i;
	sort(tmp+1,tmp+tot+1);
	int res=1e9,now=0,l=1,r=1;
	while(r<=tot)
	{
		now+=tcnt[tmp[r]],r++;
		if(now<k)continue;
		while(now-tcnt[tmp[l]]>=k)now-=tcnt[tmp[l]],l++;
		res=min(res,tmp[r-1]-tmp[l]);
	}
	return res==1e9?-1:res;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1,op,a,b,c;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&a,&b,&c);
			cntq++;
			q[cntq]={a,b,c,cntu,cntq};
		}
		else
		{
			scanf("%d%d",&a,&b);
			u[++cntu]={a,b};
		}
	}
	unit=max(1,(int)(n/pow(m,1.0/3)));
	sort(q+1,q+cntq+1);
	lis.t=1e5+1;
	for(int i=1,l=1,r=0,t=0;i<=cntq;i++)
	{
		while(l>q[i].l)add(a[--l]);
		while(r<q[i].r)add(a[++r]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);
		while(t<q[i].t)upd(i,++t);
		while(t>q[i].t)upd(i,t--);
		ans[q[i].id]=query(q[i].k);
	} 
	for(int i=1;i<=cntq;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：tzc_wk (赞：2)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/1476/problem/G) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1476G)

~~震惊！我竟然独立切掉了这道 *3100 的题！~~

~~虽然此题难度的确虚高，感觉真实评分也就 2800~2900 罢。但感觉还是挺有成就感的（~~

注意到题目中所询问的那坨东西基于每个数在区间中出现的次数，因此此题必不可少的一个步骤就是求出每个数的出现次数 $cnt_x$，这个可以用带修莫队在 $n^{5/3}$ 的时间内求出，这里就不再赘述了。

接下来考虑怎样计算答案，这也是本题的难点所在。我们将所有 $[l,r]$ 中出现次数非零的数的出现次数从小到大排序，设为 $x_1,x_2,\cdots,x_m$，显然我们选择的数在 $x$ 序列中一定是一段连续的区间 $x_i,x_{i+1},\cdots,x_{i+k-1}$，故答案为 $\min\limits_{i=1}^{m-k+1}x_{i+k-1}-x_i$。

暴力排序求解显然是不行的，但是注意到 $x$ 数组有一个非常重要的性质，就是 $\sum\limits_{i=1}^mx_i=r-l+1\le n$，我们不妨设一个阈值 $B$，我们考虑以下两个暴力：

- 对于 $x_{i+k-1}\le B$ 的 $i$，我们开一个桶 $cnt\_cnt_i$ 表示 $\sum[x_j=i]$，也就是 $x_j=i$ 的个数，然后枚举 $x_i$，用 two pointers 找出最小的 $r$ 使得 $\sum\limits_{j=i}^rcnt\_cnt_j\ge k$ 并用 $r-i$ 更新答案。
- 对于 $x_{i+k-1}>B$ 的 $i$，注意到这样的 $i$ 不超过 $\lfloor\dfrac{n}{B}\rfloor$ 个，于是我们暴力找出 $x_i>B$ 的 $x_i$ 并将其从小到大排序，然后直接用 $x_{i+k-1}-x_i$ 更新答案即可。复杂度 $\dfrac{n}{B}\log\dfrac{n}{B}$。

用均值不等式可知 $B=\sqrt{n\log n}$ 时复杂度最优。

还有一个小问题，就是怎样求出 $x_{i}>B$ 的 $x_i$，一个很显然的思路是在莫队 `push/pop` 的过程中维护一个 `set`，如果当前加入的值的 $cnt\ge B$ 就压入 `set`，否则从 `set` 中删除当前值，不过这样会使带修莫队的复杂度变为 $n^{5/3}\log n$，无法通过。注意到如果 $i$ 满足 $i$ 从始至终在序列中出现的次数 $<B$，那么它一定不可能出现在这个 `set` 中，故考虑预处理所有**存在某个时刻在序列中出现次数 $>B$ 的 $i$**——这样的 $i$ 必定不会超过 $\dfrac{n}{B}$，然后每次询问时暴力在这样的 $i$ 中查找出现次数 $>B$ 的值，这样就能保证复杂度了。

时间复杂度 $n^{5/3}+n\sqrt{n\log n}$

~~这个莫队板子题能放到 edu 的 G 就 nm 离谱~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e5;
const int BLK_2_3=2000;
const int BLK_1_2=316;
const int INF=0x3f3f3f3f;
int n,qu,qk=0,a[MAXN+5],tot_cnt[MAXN+5],cnt[MAXN+5],cnt_cnt[MAXN+5];
int blk_cnt,L[MAXN+5],R[MAXN+5],bel[MAXN+5];
struct chg{int x,pre,cur;} c[MAXN+5];
vector<int> tot;
void push(int x){cnt_cnt[cnt[x]]--;cnt[x]++;cnt_cnt[cnt[x]]++;}
void pop(int x){cnt_cnt[cnt[x]]--;cnt[x]--;cnt_cnt[cnt[x]]++;}
struct query{
	int l,r,k,id;
	bool operator <(const query &rhs){
		if(bel[l]!=bel[rhs.l]) return l<rhs.l;
		else if(bel[r]!=bel[rhs.r]) return r<rhs.r;
		return id<rhs.id;
	}
} q[MAXN+5];
int ans[MAXN+5];
int deal(int k){
	vector<int> over;int ret=INF;
	for(int i=0;i<tot.size();i++) if(cnt[tot[i]]>BLK_1_2) over.pb(cnt[tot[i]]);
	sort(over.begin(),over.end());
	for(int l=1,r=1,sum=0;l<=BLK_1_2;l++){
		while(r<=BLK_1_2&&sum<k) sum+=cnt_cnt[r],r++;
		if(sum<k){
			int need=k-sum;
			if(need<=over.size()) chkmin(ret,over[need-1]-l);
		} else chkmin(ret,r-l-1);
		sum-=cnt_cnt[l];
	}
	for(int i=0;i+k-1<over.size();i++) chkmin(ret,over[i+k-1]-over[i]);
	return ret;
}
int main(){
	scanf("%d%d",&n,&qu);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),tot_cnt[a[i]]++;
	blk_cnt=(n-1)/BLK_2_3+1;
	for(int i=1;i<=blk_cnt;i++){
		L[i]=(i-1)*BLK_2_3+1;R[i]=min(i*BLK_2_3,n);
		for(int j=L[i];j<=R[i];j++) bel[j]=i;
	}
	for(int i=1;i<=qu;i++){
		int opt;scanf("%d",&opt);
		if(opt==1){
			qk++;scanf("%d%d%d",&q[qk].l,&q[qk].r,&q[qk].k);
			q[qk].id=i;
		} else {
			scanf("%d%d",&c[i].x,&c[i].cur);
			c[i].pre=a[c[i].x];a[c[i].x]=c[i].cur;
			tot_cnt[c[i].cur]++;
		}
	} sort(q+1,q+qk+1);int cl=1,cr=0,ct=qu;
	memset(ans,-1,sizeof(ans));
	for(int i=1;i<=MAXN;i++) if(tot_cnt[i]>BLK_1_2) tot.pb(i);
	for(int i=1;i<=qk;i++){
		while(cr<q[i].r) push(a[++cr]);
		while(cl>q[i].l) push(a[--cl]);
		while(cr>q[i].r) pop(a[cr--]);
		while(cl<q[i].l) pop(a[cl++]);
		while(ct<q[i].id){
			if(c[ct].x){
				if(q[i].l<=c[ct].x&&c[ct].x<=q[i].r) pop(c[ct].pre);
				a[c[ct].x]=c[ct].cur;
				if(q[i].l<=c[ct].x&&c[ct].x<=q[i].r) push(c[ct].cur);
			} ct++;
		}
		while(ct>q[i].id){
			if(c[ct].x){
				if(q[i].l<=c[ct].x&&c[ct].x<=q[i].r) pop(c[ct].cur);
				a[c[ct].x]=c[ct].pre;
				if(q[i].l<=c[ct].x&&c[ct].x<=q[i].r) push(c[ct].pre);
			} ct--;
		} ans[q[i].id]=deal(q[i].k);
	}
	for(int i=1;i<=qu;i++) if(~ans[i]) printf("%d\n",(ans[i]^INF)?ans[i]:-1);
	return 0;
}
/*
12 11
2 1 1 2 1 1 3 2 1 1 3 3
1 2 10 3
1 2 11 3
2 7 2
1 3 9 2
1 1 12 1
1 1 12 4
2 12 4
1 1 12 4
2 1 5
1 3 12 2
1 1 4 3
*/
/*
10 2
1 2 2 1 1 3 1 1 3 1
1 3 8 2
1 3 8 3
*/
```



---

## 作者：chlchl (赞：1)

（题外话）简单的 *3100，考场上差一步，光想 CF765F 的双 $\log$ 了，实际上这题连 trick 我都见过。

## Solution
显然什么出现次数的肯定是莫队，这就是个数颜色的板子，所以首先考虑强上一个带修莫队。

我们统计出每个数**出现次数的出现次数**（$tot_i$），这样等价于，查询的时候找到最小的 $r-l$ 使得 $\sum\limits_{i=l}^{r}tot_i\ge k$。

这个东西显然可以双指针求解。

这里有个结论：不同的出现次数不会超过 $\sqrt n$ 个。

因为一共最多只有 $n$ 个元素，即使出现次数为 $1\sim\sqrt n$ 的数各有一个，那总的出现次数也已经到达了 $\dfrac{\sqrt n\cdot(\sqrt n+1)}{2}=O(n)$ 次，所以其实这个东西的元素个数是不超过 $\sqrt n$ 的。

这个结论在 P5072 中也出现过，并且最后也是用链表维护，赛时没想到真是罪过。

所以用链表动态维护不同的出现次数，查询的时候将其排序，然后直接在上面双指针即可。

时间复杂度 $O(n^{\frac{5}{3}}+m\sqrt n\log n)$（后面那个 $\log$ 是因为要排序）。

写起来也不会依托答辩，不犯制杖错误的话 30min 应该能 AC 了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, m, cntc, cntq, a[N];
int blk, cnt[N], tot[N], ans[N];
struct query{
	int l, r, t, k, id;
	bool operator < (const query &p) const {
		if(l / blk != p.l / blk)
			return l < p.l;
		if(r / blk != p.r / blk)
			return r < p.r;
		return t < p.t;
	}
} q[N];
struct change{
	int p, x;
} c[N];
struct chainlist{
	int tot, pre[N], nxt[N];
	
	void add(int x){
		pre[x] = tot;
		nxt[tot] = x;
		tot = x;
	}
	
	void del(int x){
		if(x != tot){
			nxt[pre[x]] = nxt[x];
			pre[nxt[x]] = pre[x];
		}
		else{
			nxt[pre[x]] = 0;
			tot = pre[x];
		}
		pre[x] = nxt[x] = 0;
	}
} chlist;

void update(int v, int x){
	--tot[cnt[v]];
	if(!tot[cnt[v]])
		chlist.del(cnt[v]);
	cnt[v] += x;//cnt 是出现次数，tot是出现次数的出现次数 
	if(!tot[cnt[v]])
		chlist.add(cnt[v]);
	++tot[cnt[v]];
}

void update_time(int t, int l, int r){
	if(l <= c[t].p && c[t].p <= r){
		update(a[c[t].p], -1);
		update(c[t].x, 1);
	}
	swap(a[c[t].p], c[t].x);
}

int getans(int k){
	vector<int> xyr;
	for(int i=chlist.nxt[0];i;i=chlist.nxt[i])
		xyr.push_back(i);
	sort(xyr.begin(), xyr.end());
	int l = 0, r = 0, tmp = 0, chl = 1e9;
	for(;r<=xyr.size()-1;++r){
		tmp += tot[xyr[r]];
//		printf("Now l=%d, r=%d, my xyr[r]=%d, tot[xyr[r]]=%d, tmp=%d\n", l, r, xyr[r], tot[xyr[r]], tmp);
		if(tmp < k)
			continue;
		while(tmp - tot[xyr[l]] >= k)
			tmp -= tot[xyr[l++]];
//		printf("Wow! Now l=%d, r=%d, my xyr[r]=%d, tmp=%d\n", l, r, xyr[r], tmp);
		chl = min(chl, xyr[r] - xyr[l]);
	}
	return (chl == 1e9 ? -1 : chl);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	for(int i=1,op;i<=m;i++){
		scanf("%d", &op);
		if(op == 1){
			++cntq;
			scanf("%d%d%d", &q[cntq].l, &q[cntq].r, &q[cntq].k);
			q[cntq].id = cntq, q[cntq].t = cntc;
		}
		else{
			++cntc;
			scanf("%d%d", &c[cntc].p, &c[cntc].x);
		}
	}
	blk = pow(m, 2.0 / 3.0);
	sort(q + 1, q + 1 + cntq);
	int l = 1, r = 0, t = 0;
	for(int i=1;i<=cntq;i++){
		while(l > q[i].l)
			update(a[--l], 1);
		while(r < q[i].r)
			update(a[++r], 1);
		while(l < q[i].l)
			update(a[l++], -1);
		while(r > q[i].r)
			update(a[r--], -1);
		while(t < q[i].t)
			update_time(++t, q[i].l, q[i].r);
		while(t > q[i].t)
			update_time(t--, q[i].l, q[i].r);
		ans[q[i].id] = getans(q[i].k);
	}
	for(int i=1;i<=cntq;i++)
		printf("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：Purslane (赞：1)

# Solution

直接上带修莫队。设出现一个数出现次数为 $cnt$，这个区间内出现次数的出现次数为 $val$。这两个东西都是可以在莫队带修的时候 $O(n^{\frac{5}{3}})$ 的维护。

于是你就要在给定 $val$ 的时候把这个 $\text{dif}$ 给求出来。

然后考虑二分答案，也就是你要求二元组 $(l,r)$ 使得 $l>0$，$\sum_{i=l}^r val_i \ge k$，且 $r-l \le \text{dif}$。

然后一个经典结论，$val$ 中只有 $O(\sqrt n)$ 个点有值。

于是你就用一个链表维护所有有值的 $val$，然后用一个 two - pointer在 $O(\sqrt n \log n)$ 的复杂度内解决此题。（因为你发现，$r-l$ 越大，越有可能出解，那么我们找到极大值即可）

总的复杂度是 $O(n^{\frac{5}{3}}+n^{\frac{3}{2}} \log n)$。

---

## 作者：Ginger_he (赞：1)

考虑暴力做法，对于 $1$ 操作统计区间内每个数的出现次数 $cnt$，然后开个桶 $p$ 记录每种出现次数的个数，双指针找到对于每个 $i$ 的最小的 $j$ 使得 $j\ge i$ 且 $\sum\limits_{x=i}^jp_x\ge k$，答案即为所有的 $(i,j)$ 中 $j-i$ 的最小值，对于 $2$ 操作直接修改即可，时间复杂度 $O(n^2)$。

考虑优化，发现 $\sum\limits_{x=1}^kx=\dfrac{k\times(k+1)}{2}\le n$，故使得 $p_x$ 不为 $0$ 的 $x$ 的个数大约只有 $O(\sqrt n)$ 个，所以我们可以维护一个链表，记录 $p_x$ 不为 $0$ 的位置，同时用带修莫队，每次拓展区间就往链表里插数，缩小区间就从链表里删数，然后将链表上的数取出排序后双指针即可，时间复杂度 $O(n^{\frac{5}{3}}+n\sqrt n\log n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100005
int n,m,len,tmp,s,res,op,x,y,z,u,v,l=1,r,t;
int a[N],lst[N],nxt[N],p[N],cnt[N],f[N],ans[N];
struct query
{
	int l,r,k,t,id;
	bool operator < (const query &x) const
	{
		return l/len==x.l/len?r/len==x.r/len? 
		t<x.t:r<x.r:l<x.l;
	}
}q[N];
struct node
{
	int p,v;
}c[N];
inline void insert(int x)
{
	lst[x]=lst[n+1];
	nxt[x]=n+1;
	nxt[lst[x]]=lst[n+1]=x;
}
inline void erase(int x)
{
	lst[nxt[x]]=lst[x];
	nxt[lst[x]]=nxt[x];
}
inline void add(int x)
{
	p[cnt[x]]--;
	if(!p[cnt[x]]) erase(cnt[x]);
	if(!p[++cnt[x]]) insert(cnt[x]);
	p[cnt[x]]++;
}
inline void del(int x)
{
	p[cnt[x]]--;
	if(!p[cnt[x]]) erase(cnt[x]);
	if(!cnt[x]) return;
	if(!p[--cnt[x]]) insert(cnt[x]);
	p[cnt[x]]++;
}
inline void update(int t,int i)
{
	if(q[i].l<=c[t].p&&c[t].p<=q[i].r)
	{
		del(a[c[t].p]);
		add(c[t].v);
	}
	swap(c[t].v,a[c[t].p]);
}
int main()
{
	scanf("%d%d",&n,&m);
	len=pow(n,0.666);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&op,&x,&y);
		if(op&1) scanf("%d",&z),q[++u]=query{x,y,z,v,u};
		else c[++v]=node{x,y};
	}
	sort(q+1,q+u+1);
	nxt[0]=n+1,lst[n+1]=0;
	for(int i=1;i<=u;i++)
	{
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(l<q[i].l) del(a[l++]);
		while(r>q[i].r) del(a[r--]);
		while(t<q[i].t) update(++t,i);
		while(t>q[i].t) update(t--,i);
		tmp=s=0,res=1e9;
		for(int j=nxt[0];j!=n+1;j=nxt[j])
			f[++tmp]=j,s+=p[j];
		if(s<q[i].k)
		{
			ans[q[i].id]=-1;
			continue;
		}
		sort(f+1,f+tmp+1);
		s=0;
		for(int j=1,r=0;j<=tmp;j++)
		{
			while(r<tmp&&s<q[i].k) s+=p[f[++r]];
			if(s<q[i].k) break;
			s-=p[f[j]]; 
			res=min(res,f[r]-f[j]);
		}
		ans[q[i].id]=res;
	}
	for(int i=1;i<=u;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Others (赞：1)

这题我做了两天，第一天一直盯着题，第二天一直打暴力...
# 题目大意
题目翻译过后已经讲得够清楚了 qwq。
# 思路
这题有区间，有统计（$cnt$，极差），有修改，可以离线，明摆着的带修莫队。这题我一看是求 $cnt$ 数组中的极差，毫不犹豫地又开了个 $ccnt$ 数组记录 $cnt$ 数组，这时就只需要找 $ccnt$ 中的最小的极差了。

找极差，也就是找 $Max$ 和 $Min$，我们可以记录下 $cnt$ 中 $>0$ 的不重复元素，然后跳双指针，在跳双指针时要用到 $ccnt$ 数组记录有多少个不重复的数字。

现在剩下一个问题，就是怎样记录不重复的元素呢？这里可以用 ```set```，但 ```set``` 套了层 $log$ 这样的复杂度一般不低，而且还要搞个十分难搞的迭代器（固执的朋友可以试一试）......

这里我们可以用链表，就是在第一次统计到 $cnt$ 时插入链表，删除和插入都是 $O(1)$ 老爽了。至于为什么暴力双指针不会爆...我~~太蒟了~~不会，可以参考一下别的 dalao 的推导。

代码里还有些解释，选择性观看
```cpp
#include <bits/stdc++.h>
using namespace std;
const int P=100005;
int n,m,s,a[P],idx[P],ans[P],cnt[P],ccnt[P],op,L,R,K,T,x,cntr,cntp,l=1,r,t,be,st=100001,last[P],next[P],pos[P],top;
struct node1{//查询 
	int l,r,k,t,id;
	bool operator<(const node1 x)const{//简易的分块排序 
		return idx[l]==idx[x.l]?(idx[r]==idx[x.r]?t<x.t:r<x.r):l<x.l;
	}
}p[P];
struct node2{//修改 
	int i,from,to;
}q[P];
void Ins(int x){//插入 
	if(x==0) return; //这个特判下面说 
	if(!ccnt[x]++) next[last[st]]=x,last[x]=last[st],next[x]=st,last[st]=x;//这都不会你还是去打 set 吧... 
}
void Del(int x){
	if(x==0) return;
	if(!--ccnt[x]) {
		if(x==be) be=next[x];//这里需要特判，因为最后那一句顾及不到这里 
		if(x==st) st=last[x];
		last[next[x]]=last[x],next[last[x]]=next[x];
	}
}
void add(int x){
	Del(cnt[x]),Ins(++cnt[x]);//因为 cnt[x] 和 --cnt[x] 有可能是 0 所以在 Ins 和 Del 中要打个特判 
							  //因为最后统计的是出现次数的极差，所以链表存的是出现次数 
}
void del(int x){
	Del(cnt[x]),Ins(--cnt[x]);
}
int deal(int inx) {
	top=0;
	for(int i=be;i!=st;i=next[i]) if(i!=0) pos[++top]=i;//统计链表中的元素 
	sort(pos+1,pos+top+1); //排序，因为极差是正数 
	int sum=0,Min=2147483647,LL=1,RR=1;//跳双指针
	while(RR<=top){
		sum+=ccnt[pos[RR++]];
		if(sum<inx) continue;//过滤开头的情况 
		while(sum>=inx+ccnt[pos[LL]]) sum-=ccnt[pos[LL++]];//跳 LL 指针 
		Min=min(Min,pos[RR-1]-pos[LL]);
	}
	return Min==2147483647?-1:Min;
}
int main() {
	next[0]=next[100001]=100001;//初始化 
	scanf("%d%d",&n,&m);
	s=pow(n,2.0/3);//这里是 2/3次方！！！ 
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		idx[i]=(i+s-1)/s;
	}
	for(int i=1;i<=m;++i){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&L,&R,&K);
			p[++cntp].l=L;
			p[cntp].r=R;
			p[cntp].k=K;
			p[cntp].t=cntr;
			p[cntp].id=cntp;
		}else{
			scanf("%d%d",&x,&K);
			q[++cntr].i=x;
			q[cntr].from=a[x];
			q[cntr].to=a[x]=K;//数组记得跟着修改 
		}
	}
	for(int i=cntr;i>0;--i) a[q[i].i]=q[i].from;//还原数组 
	sort(p+1,p+cntp+1);
	for(int i=1;i<=cntp;++i){
		L=p[i].l,R=p[i].r,K=p[i].k,T=p[i].t;//以前无脑卡常时学的（不知道有没有用） 
		while(t<T) {//这是板板
			++t;
			if(q[t].i>=l&&q[t].i<=r) add(q[t].to),del(q[t].from);
			a[q[t].i]=q[t].to;
		} 
		while(t>T) {
			if(q[t].i>=l&&q[t].i<=r) del(q[t].to),add(q[t].from);
			a[q[t].i]=q[t].from;
			--t;
		}
		while(l>L) add(a[--l]);
		while(r<R) add(a[++r]);
		while(l<L) del(a[l++]);
		while(r>R) del(a[r--]);
		ans[p[i].id]=deal(K);
	}
	for(int i=1;i<=cntp;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：rainygame (赞：0)

区间查询带单点修改，不难想到带修莫队。

由于 $\sum cnt_i \le n$，所以 $cnt_i$ 的种类数不会超过 $O(\sqrt n)$ 种。

以这个为突破口，对于一个 $l$，双指针地求出最小的 $r$ 使得 $\sum[ct_i\in[l,r]] \ge k$，然后将 $r-l$ 加入答案。

实现需要维护 $v_i=\sum[ct_j=i]$，每次双指针需要跳到下一个 $v_i\ne 0$ 的位置，可以用 `bitset` 的 `_Find_next` 实现。

时间复杂度 $O(n^{\frac{5}{3}}+\frac{n^2}{\omega})$。实测最大点不超过 1.6s。

[submission](https://codeforces.com/contest/1476/submission/309214199)

---

## 作者：cike_bilibili (赞：0)

# 带修莫队

看一眼题面，区间查询还要维护数字出现次数，自然想到莫队，看到单点修改，又能想到带修莫队。

关于每一种数字 $cnt$ 有一个很优秀的性质，就是它的种类数即数字种类数的种类数不会超过 $O(\sqrt n)$，于是我们可以基于 $cnt$ 的种类数设计暴力算法，当 $cnt$ 单调上升时，我们可以使用双指针解决，至于如何保持有序，我们可以用**链表**维护，链表下标设为 $cnt$，每次将链表拍扁成数组排序即可。

时间复杂度 $O(n^{\frac{5}{3}}+n \sqrt n\log )$。

# AC CODE
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

int n,m;
int a[1000005];
struct query{
	int l;
	int r;
	int t;
	int k;
	int id;
	int ans;
}q[1000005];
int S;
bool cmp(query a,query b){
	if(a.l/S!=b.l/S)return a.l<b.l;
	if(a.r/S!=b.r/S)return a.r<b.r;
	return a.t<b.t;
}
bool cmp1(query a,query b){
	return a.id<b.id;
}
struct modify{
	int p;
	int x;
}mo[1000005];
int cnt1,cnt2;
int l,r,tim;
int cnt[1000005];
int head;
struct node{
	int lst;
	int nxt;
	int val;
}lis[1000005];
struct by{
	int cnt;
	int val;
	bool operator<(const by &a)const{
		return cnt<a.cnt;
	}
}by[1000005];
inline void del_node(int x){
	if(x==head){
		head=lis[x].nxt;
		lis[x]={0,0,0};
		return;
	}
	else{
		lis[lis[x].lst].nxt=lis[x].nxt;
		lis[lis[x].nxt].lst=lis[x].lst;
		lis[x]={0,0,0};
	}
}
inline void add_node(int x){
	lis[x].nxt=head;
	lis[head].lst=x;
	lis[x].val=1;
	head=x;
}

inline void add(int x){
	if(lis[cnt[a[x]]].val>=2){
		lis[cnt[a[x]]].val--;
	}else if(cnt[a[x]]){
		del_node(cnt[a[x]]);
	}
	cnt[a[x]]++;
	if(lis[cnt[a[x]]].val){
		lis[cnt[a[x]]].val++;
	}else if(cnt[a[x]]){
		add_node(cnt[a[x]]);
	}
}
inline void del(int x){
	if(lis[cnt[a[x]]].val>=2){
		lis[cnt[a[x]]].val--;
	}else if(cnt[a[x]]){
		del_node(cnt[a[x]]);
	}
	cnt[a[x]]--;
	if(lis[cnt[a[x]]].val){
		lis[cnt[a[x]]].val++;
	}else if(cnt[a[x]]){
		add_node(cnt[a[x]]);
	}
}
inline void move_t1(){
	++tim;
	if(mo[tim].p>=l&&mo[tim].p<=r){
		del(mo[tim].p);
		swap(a[mo[tim].p],mo[tim].x);
		add(mo[tim].p);
	}
	else{
		swap(a[mo[tim].p],mo[tim].x);
	}
}
inline void move_t2(){
	if(mo[tim].p>=l&&mo[tim].p<=r){
		del(mo[tim].p);
		swap(a[mo[tim].p],mo[tim].x);
		add(mo[tim].p);
	}
	else{
		swap(a[mo[tim].p],mo[tim].x);
	}
	--tim;
}
int main(){
	n=read();
	m=read();
	S=pow(n,0.6666);
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=m;i++){
		int opt=read();
		if(opt==1){
			int l=read(),r=read(),k=read();
			q[++cnt2]={l,r,cnt1,k,i};
		}else{
			int p=read(),k=read();
			mo[++cnt1]={p,k};
		}
	}
	sort(q+1,q+1+cnt2,cmp);
	l=r=1;
	add(1);
	for(int i=1;i<=cnt2;i++){
		while(tim<q[i].t)move_t1();
		while(tim>q[i].t)move_t2();
		while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);
		while(l<q[i].l)del(l++);
		while(r>q[i].r)del(r--);
		int top=0;
		for(int j=head;j;j=lis[j].nxt){
			by[++top]={j,lis[j].val};
		}
		sort(by+1,by+top+1);
		int L=1,R=1;
		int sum=by[1].val;
		int minn=1e9;
		if(sum>=q[i].k)minn=min(minn,0);
		while(R<=top&&L<=top){
			while((sum<q[i].k&&R<top)||(R<L)){
				R++;
				sum+=by[R].val;
			}
			if(sum<q[i].k)break;
			minn=min(minn,by[R].cnt-by[L].cnt);
			sum-=by[L].val;
			L++;
		}
		q[i].ans=minn==1e9?-1:minn;
	}
	sort(q+1,q+1+cnt2,cmp1);
	for(int i=1;i<=cnt2;i++){
		printf("%d\n",q[i].ans);
	}
} 
```

---

## 作者：7KByte (赞：0)

莫队模板题。

首先这个问题不弱于带修数颜色，所以考虑带修莫队。

同时 $cnt$ 的取值不超过 $\sqrt{n}$ 种，所以我们可以用链表维护出现的 $cnt$ 取值。

对于每次询问，将这 $\sqrt{n}$ 种 $cnt$ 从小到大排序，答案就是最短的连续一段满足出现次数之和 $\ge k$ 。

我们从小到大枚举右端点，左端点单调，直接双指针即可。

时间复杂度 $\mathcal{O}(n^{\frac{5}{3}}+m\sqrt{n}\log\sqrt{n})$，基数排序可以做到 $\mathcal{O}(n^\frac{5}{3}+m\sqrt{n})$ 。

前者手算一下大概 $6\times 10^8$ 运算，实测 $2s$ 毫无压力。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
#define pre(i,a,b) for(register int i=a;i>=b;i--)
#define N 100005
using namespace std;
int n,m,a[N],bas,t,T,p[N],u[N],c[N],f[N],nxt[N],pre[N],ans[N],sta[N];
struct node{
	int op,x,l,r,id;
	bool operator<(const node o)const{
		if(l/bas!=o.l/bas)return l<o.l;
		if(r/bas!=o.r/bas)return r<o.r;
		return id<o.id;
	}
}q[N];
inline void rem(int x){
	if(!x)return;
	pre[nxt[x]]=pre[x];
	nxt[pre[x]]=nxt[x];
}
inline void add(int x){
	if(!x)return;
	pre[nxt[0]]=x;
	nxt[x]=nxt[0];
	pre[x]=0;nxt[0]=x;
}
inline void ins(int x){
	c[f[x]]--;
	if(!c[f[x]])rem(f[x]);
	f[x]++;
	if(!c[f[x]])add(f[x]);
	c[f[x]]++;
}
inline void del(int x){
	c[f[x]]--;
	if(!c[f[x]])rem(f[x]);
	f[x]--;
	if(!c[f[x]])add(f[x]);
	c[f[x]]++;
}
inline int calc(int k){
	register int top=0,sum=0,cur=nxt[0],ed=0x3f3f3f3f;
	while(cur)sta[++top]=cur,cur=nxt[cur];
	sort(sta+1,sta+top+1);int j=1;
	rep(i,1,top){
		sum+=c[sta[i]];
		while(sum-c[sta[j]]>=k)sum-=c[sta[j++]];
		if(sum>=k)ed=min(ed,sta[i]-sta[j]);
	} 
	if(ed==0x3f3f3f3f)return ~0;
	return ed;
}
char buf[1<<22],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
int main(){
	bas=pow(n=read(),0.666666);m=read();
	rep(i,1,n)a[i]=read();
	rep(i,1,m){
		if(read()==1){
			++t;q[t].op=t,q[t].l=read(),q[t].r=read(),q[t].x=read(),q[t].id=T;
		}
		else{
			++T;p[T]=read(),u[T]=read();
		}
	}
	sort(q+1,q+t+1);
	register int l=1,r=1,tm=0;ins(a[1]);
	rep(i,1,t){
		while(l>q[i].l)ins(a[--l]);
		while(r<q[i].r)ins(a[++r]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);
		while(tm<q[i].id){
			++tm;
			if(p[tm]>=l&&p[tm]<=r)del(a[p[tm]]),ins(u[tm]);
			swap(a[p[tm]],u[tm]);
		}
		while(tm>q[i].id){
			if(p[tm]>=l&&p[tm]<=r)del(a[p[tm]]),ins(u[tm]);
			swap(a[p[tm]],u[tm]),tm--;
		}
		ans[q[i].op]=calc(q[i].x);
	}
	rep(i,1,t)printf("%d\n",ans[i]);
	return 0;
}
```

---

