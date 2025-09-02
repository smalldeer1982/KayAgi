# [USACO23FEB] Hungry Cow P

## 题目描述

**注意：本题的时间限制为 6 秒，是默认的三倍。内存限制为 512MB，是默认的两倍。**

Bessie 是一头饥饿的奶牛。每天晚餐时，如果谷仓里有干草，她就会吃掉一捆干草。农夫 John 不想让 Bessie 挨饿，所以有些天他会送来干草，这些干草会在早上（晚餐前）到达。特别地，在第 $d_i$ 天，农夫 John 会送来 $b_i$ 捆干草 $(1 \le d_i \le 10^{14}, 0 \le b_i \le 10^9)$。

处理 $U(1 \le U \le 10^5)$ 次更新如下：给定一对 $(d,b)$，更新第 $d$ 天到达的干草数量为 $b$。每次更新后，输出 Bessie 吃干草的所有天数之和，结果对 $10^9+7$ 取模。

## 说明/提示

### 示例 1 的解释

每次更新后的答案：

$4+5+6=15$  
$1+2+3+4+5+6+7+8=36$  
$1+2+4+5+6=18$

### 评分

- 输入 3：$U \le 5000$
- 输入 4-10：更新只会增加第 $d$ 天到达的干草数量。
- 输入 11-22：无额外约束。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
4 3
1 5
1 2```

### 输出

```
15
36
18```

## 样例 #2

### 输入

```
9
1 89
30 7
101 26
1 24
5 1
60 4
5 10
101 0
1 200```

### 输出

```
4005
4656
7607
3482
3507
3753
4058
1107
24531```

# 题解

## 作者：kradcigam (赞：20)

赛时开始一眼线段树分治，交了几发都 T 了，就意识到事情不对。后来想了想发现势能分析不能带撤销。。。

后来加了一些不能改变复杂度假了的优化，没过之后就自闭跑路了。。。

赛后听别人说了个楼房重建就明白怎么做了。

首先，我们离线下来把 $a$ 排序，去重（这样方便一点，不然权值线段树上的空节点得特判），线段树的叶子节点表示的是 $[t_i,t_{i+1})$ 这段区间。为了方便，我们设 $t_{n+1}=\inf$。

我们维护当前线段树区间的 $4$ 个值：

1. 总共匹配了多少个值；
2. 总共向右超出了多少个值；
3. 匹配的答案是多少；
4. 左区间超出部分的答案，若左区间超出部分在右区间依旧超出，那就不管了。

考虑 `pushup`，分 $2$ 种情况：

1. 左区间超出部分在右区间依旧超出，则右区间被填满了；
2. 左区间超出部分都可以在右区间插入，我们在右区间做线段树二分，计算出最后一个左区间超出部分的位置。由于需要减掉原始匹配的答案所以具体实现时需要维护 4（在 pushup 的时候记一下）。

写的时候刚睡醒，一个地方 `+` 和 `-` 打反了，调了半年。

代码很短：

```cpp
#include <bits/stdc++.h>
#define ls num << 1
#define rs ls | 1
#define li ls, l, mid
#define ri rs, mid + 1, r
#define int long long
#define SZ(x) (int) x.size() - 1
#define all(x) x.begin(), x.end()
#define ms(x, y) memset(x, y, sizeof x)
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define DF(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> void chkmax(T &x, T y) { x = max(x, y); }
template <typename T> void chkmin(T &x, T y) { x = min(x, y); }
template <typename T> void read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
const int N = 1e5 + 10, MOD = 1e9 + 7, inv2 = (MOD + 1) / 2;
int rt, tot, x[N], y[N], t[N];
int qq(int l, int r) {
	return ((r - l + 1) % MOD) * ((l + r) % MOD) % MOD * inv2 % MOD;
}
struct seg {
	int out, sum, ans, lans;
} tt[N * 4];
pair <int, int> query(int num, int l, int r, int x) {
	if (l == r) return make_pair(t[l] + tt[num].sum + x - 1, tt[num].ans);
	int mid = (l + r) >> 1;
	int cnt = t[mid + 1] - t[l] - tt[ls].sum;
	if (x <= cnt) return query(ls, l, mid, x);
	pair <int, int> ans = query(rs, mid + 1, r, x - cnt + tt[ls].out);
	ans.second += tt[ls].ans + tt[num].lans;
	return ans;
}
void pushup(int num, int l, int r) {
	int mid = (l + r) >> 1;
	int cnt = t[r + 1] - t[mid + 1] - tt[rs].sum;
	if (cnt < tt[ls].out) {
		tt[num].out = tt[rs].out + tt[ls].out - cnt;
		tt[num].sum = tt[ls].sum + t[r + 1] - t[mid + 1];
		tt[num].ans = tt[ls].ans + qq(t[mid + 1], t[r + 1] - 1);
		tt[num].lans = -1;
	} else {
		tt[num].out = tt[rs].out;
		tt[num].sum = tt[ls].sum + tt[rs].sum + tt[ls].out;
		pair <int, int> pos = make_pair(t[mid + 1] - 1, 0);
		if (tt[ls].out) pos = query(rs, mid + 1, r, tt[ls].out);
		tt[num].lans = qq(t[mid + 1], pos.first) - pos.second;
		tt[num].ans = tt[ls].ans + tt[rs].ans + tt[num].lans;
	}
}
void change(int num, int l, int r, int x, int y) {
	if (l == r) {
		tt[num].sum = min(y, t[l + 1] - t[l]);
		tt[num].ans = qq(t[l], t[l] + tt[num].sum - 1);
		tt[num].out = y - tt[num].sum;
		return;
	} int mid = (l + r) >> 1;
	if (mid >= x) change(li, x, y);
	else change(ri, x, y);
	pushup(num, l, r);
}
signed main() {
	int n; read(n);
	F(i, 1, n) read(x[i]), read(y[i]), t[i] = x[i];
	sort(t + 1, t + n + 1);
	int m = unique(t + 1, t + n + 1) - t - 1;
	t[m + 1] = 1e18;
	F(i, 1, n) {
		change(1, 1, m, lower_bound(t + 1, t + m + 1, x[i]) - t, y[i]);
		cout << (tt[1].ans % MOD + MOD) % MOD << '\n';
	}
	return 0;
}
```

---

## 作者：_maze (赞：16)


>线段树具有很优秀的性质并且易于扩展。例如，对于懒标记的下传操作，我们可以使用标记永久化取消。而这道题则对上传操作进行了扩展，利用了线段树树高只有 $\log$ 层的性质，对区间贡献的情况进行了分类讨论（实质为在线段树这一结构上二分）来统计贡献。

天数区间很大，于是我们考虑维护下标区间 $[1,10^{14}]$ 的动态开点线段树。思考我们要维护哪些信息。

1. 显然，我们要维护答案区间 $ans$。
2. 对于一个区间，我们需要知道其对之后区间的干草捆数贡献 $rem$。
3. 为了在合并时知道贡献，我们需要维护当前区间有多少天还未有干草。由于区间范围过大，我们转而维护当前区间有干草吃的天数 $num$。
4. 知道了左区间对之后区间干草捆数贡献，如何查找左区间当前左区间对右区间的贡献 $nop$？我们另开一个函数求解此信息，函数作用为：求解区间 $[l,r]$ 在左边有 $x$ 捆干草送入（且自身已有一定的贡献）的情况下会对答案数组有多少贡献。

考虑实现该函数，我们利用 $num$ 数组进行判断：

1. 如果 $x$ 会在 $[l,mid]$ 内消耗完，那么就对 $[mid+1,r]$ 没有影响，求解 $x$ 在 $[l,mid]$ 之内的贡献，再加上右区间内部的贡献。发现右区间内部贡献就是右儿子的 $nop$，因此右区间的查询是 $O(1)$ 的。
2. 否则说明 $[l,mid]$ 中每一天都有干草吃，对其 $O(1)$ 计算，将 $x$ 减去左区间没有干草吃的天数，对右区间进行求解。

上面两种情况都只会对一个儿子向下求解，因此其复杂度为 $\log n$。所以总复杂度为 $n\log^2 n$，可以通过此题。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define pre(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
ll read(ll t = 0, bool f = 1, char c = 0) {
	while(!isdigit(c = getchar())) f = c^45;
	while(isdigit(c)) t = (t << 1) + (t << 3) + (c ^ 48), c = getchar();
	return f ? t: -t;
}
const int N=1e7+5,p=1e9+7,i2=500000004;
int tot, rt=1;
#define mid ((l+r)>>1)
array<int,N> ls,rs;
array<ll,N> ans,num,rem,nop;
int plu(int u,int v) { return u+v>=p?u+v-p:u+v; }
int mul(int u,int v) { return (1ll*u*v)%p; }
int sum(ll n) { return mul(mul(n%p,(n+1)%p),i2); }
int range(ll l,ll r) { assert(l<=r);return plu(sum(r),p-sum(l-1)); }
int query(int u,ll l,ll r,ll x) {
  if(l==r) return x?l%p:ans[u];
  if(mid-l+1-num[ls[u]]>=x) return plu(query(ls[u],l,mid,x),nop[u]);
  else return plu(range(l,mid),query(rs[u],mid+1,r,x-(mid-l+1-num[ls[u]])+rem[ls[u]])); 
}
void pu(int u,ll l,ll r) {
  num[u]=num[ls[u]]+min(num[rs[u]]+rem[ls[u]],r-mid);
  rem[u]=rem[rs[u]]+max(num[rs[u]]+rem[ls[u]]-(r-mid),0ll);
  ans[u]=plu(ans[ls[u]],(nop[u]=query(rs[u],mid+1,r,rem[ls[u]])));
}
void add(ll f,ll val,int &u=rt,ll l=1,ll r=2e14) {
  if(u==0) u=++tot;
  if(l==r) {
    if(val==0) ans[u]=rem[u]=num[u]=0;
    else ans[u]=l%p,num[u]=1,rem[u]=val-1;
    return;
  }
  if(f<=mid) add(f,val,ls[u],l,mid);
  else add(f,val,rs[u],mid+1,r);
  pu(u,l,r);
}
void B() {
  ll q=read(),d,b;;
  tot=1;
  while(q--) {
    d=read(),b=read();
    add(d,b);
    printf("%lld\n",ans[rt]);
  }
}
signed main() {
  int T;T=1;B();
  return 0;
}
```


---

## 作者：DengDuck (赞：8)

神仙题，收获很大。

首先容易想到用动态开点线段树维护每个区间的答案，但是很快实现上就有许多的问题，比如：左儿子溢出给右儿子的贡献怎么处理？

如果直接对于右儿子进行区间修改，那么修改左儿子的时候，怎么撤销贡献？不好弄。

然后有一个比较天才的想法，我不把对右儿子的贡献下传，但是我把他算下来保存在根节点，这样修改左儿子的时候就只需要修改这个保存的值，整个过程不会修改右儿子。

这样我们发现合并的问题也解决了，只要向上合并的时候以保存在根节点的这个值和左儿子合并即可。

每次修改都要重新计算右儿子受到贡献之后的值，发现单次计算是 $\mathcal O(\log n)$ 的，那么一次修改操作就是 $\mathcal O(\log^2n)$，总的时间复杂度就是 $\mathcal O(q\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL mod=1e9+7;
const LL inv=5e8+4;
//const LF eps;
//const LL P;
const LL M=2e7+5;
const LL inf=2e14;

struct node
{
	LL l,r,val,sz,ans,out;
}t[M];
LL tot;
LL cal(LL l,LL r)
{
	return (l+r)%mod*((r-l+1)%mod)%mod*inv%mod;
}
LL supply(LL rt,LL l,LL r,LL x)
{
	if(!x)return t[rt].ans;
	if(l==r)return l%mod;
	LL mid=l+r>>1;
	if(x<=mid-l+1-t[t[rt].l].sz)return (supply(t[rt].l,l,mid,x)+t[rt].val)%mod;
	return (cal(l,mid)+supply(t[rt].r,mid+1,r,x-(mid-l+1-t[t[rt].l].sz)+t[t[rt].l].out));
}
void pushup(LL rt,LL l,LL r)
{
	LL mid=l+r>>1;
	t[rt].sz=t[t[rt].l].sz+min(t[t[rt].r].sz+t[t[rt].l].out,r-mid);
	t[rt].out=t[t[rt].r].out+max(t[t[rt].l].out+t[t[rt].r].sz-(r-mid),0ll);
	t[rt].val=supply(t[rt].r,mid+1,r,t[t[rt].l].out);
	t[rt].ans=(t[rt].val+t[t[rt].l].ans)%mod;
}
void upd(LL &rt,LL l,LL r,LL x,LL k)
{
	if(x<l||r<x)return;
	if(!rt)rt=++tot;
	if(l==r)
	{
		if(!k)
		{
			t[rt].sz=t[rt].ans=t[rt].out=0;
			return;
		}
		t[rt].sz=1,t[rt].ans=l%mod,t[rt].out=k-1;
		return;
	}
	LL mid=l+r>>1;
	upd(t[rt].l,l,mid,x,k);
	upd(t[rt].r,mid+1,r,x,k);
	pushup(rt,l,r);
}
LL q,rt;
int main()
{
	scanf("%lld",&q);
	while(q--)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		upd(rt,1,inf,x,y);
		printf("%lld\n",t[rt].ans);
	}
	return 0;
}
//RP++
```

---

## 作者：xuanxuan001 (赞：7)

做法不太一样，而且复杂度比较优，所以发一篇题解。

这题很容易想到维护有饭吃的天的区间，然后每次更新。但是这个做法似乎没什么前途，因为如果某一天给的草数量可以变少的话复杂度就没有保证了。而且每天对这个情况的贡献也没有什么好的性质。

那么就需要换一个思路来考虑了。如果认为 Bessie 每天会吃送到最早的干草的话，那么同一天送到的干草被吃的时间一定是连续的，而且这个时间段的开始时间之和在这堆干草送到之前的情况有关，那么这个性质就非常好了。

那么考虑给问题离线，然后可以认为有 $U$ 只 Bessie，第 $i$ 只是前 $i$ 次操作完成后的情况。那么这些操作就相当于是给 $U$ 个区间在某一天给一些干草，按照给的时间从前到后进行操作。

然后先考虑维护处每一个 Bessie 最后一次吃到饭是哪一天，那么一个在第 $x$ 天给 $y$ 份干草的操作就可以转换为：

- 将这个区间的每个值对 $x$ 取 $\max$。
- 将这个区间的每个值加上 $y$。

那么这是个经典的吉司机线段树，直接维护即可，而且不需要查询，只需要到最后将标记全部下传输出最终序列即可。

那么下面还需要考虑中间没饭吃的天的编号和，而空的天数只有在取 $\max$ 的时候让答案增加时会出现，而这个在吉司机线段树的过程中就能维护出来。

时间复杂度 $O(U \log^2 U)$，但跑不满。

代码

```
#include<cstdio>
#include<algorithm>
#define TY ll
#define MAXN 100002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
using namespace std;
typedef long long ll;
const TY M=1e9+7;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
inline void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a){if(a>9)qw(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY n=qr(),x[MAXN],y[MAXN],id[MAXN],mn[MAXN<<2],sc[MAXN<<2];
TY ad[MAXN<<2],th[MAXN<<2],ans[MAXN<<2],l,r,k;
inline TY js(TY a){a%=M;return (a*(a+1)>>1)%M;}
bool cmp(TY a,TY b){return x[a]!=x[b]?x[a]<x[b]:a<b;}
void build(TY i,TY j,TY id){
	sc[id]=1e15;if(i==j)return;TY mid=i+j>>1;
	build(i,mid,id<<1);build(mid+1,j,id<<1|1);
}inline void pushdown(TY id){
	TY sn=id<<1;
	if(mn[sn]+ad[id]==mn[id]){
		mn[sn]+=ad[id];ad[sn]+=ad[id];add(ans[sn],ans[id]);
	}else{mn[sn]+=th[id];ad[sn]+=th[id];}
	th[sn]+=th[id];sc[sn]+=th[id];
	if(mn[sn|=1]+ad[id]==mn[id]){
		mn[sn]+=ad[id];ad[sn]+=ad[id];add(ans[sn],ans[id]);
	}else{mn[sn]+=th[id];ad[sn]+=th[id];}
	th[sn]+=th[id];sc[sn]+=th[id];
	ad[id]=th[id]=ans[id]=0;
}inline void upd(TY id){
	TY sn=id<<1;mn[id]=mn[sn];sc[id]=sc[sn];
	if(mn[id]==mn[sn|=1]){
		updmn(sc[id],sc[sn]);return;
	}if(mn[id]>mn[sn]){
		sc[id]=minn(mn[id],sc[sn]);mn[id]=mn[sn];
	}else updmn(sc[id],mn[sn]);
}void chg(TY i,TY j,TY id){//区间取 max 并更新答案
	TY mid=i+j>>1;if(i!=j)pushdown(id);
	if(l>i||j>r){
		if(r>mid)chg(mid+1,j,id<<1|1);
		if(l<=mid)chg(i,mid,id<<1);upd(id);return;
	}if(mn[id]>=k)return;
	if(sc[id]>k){
		add(ans[id],M-js(k));
		add(ans[id],js(mn[id]));
		ad[id]+=k-mn[id];mn[id]=k;return;
	}chg(i,mid,id<<1);
	chg(mid+1,j,id<<1|1);upd(id);
}void add(TY i,TY j,TY id){//区间加
	if(l<=i&&j<=r){mn[id]+=k;sc[id]+=k;ad[id]+=k;th[id]+=k;return;}
	TY mid=i+j>>1;pushdown(id);if(l<=mid)add(i,mid,id<<1);
	if(r>mid)add(mid+1,j,id<<1|1);upd(id);
}void findans(TY i,TY j,TY id){//输出答案
	if(i==j){add(ans[id],js(mn[id]));qw(ans[id],'\n');return;}
	TY mid=i+j>>1;pushdown(id);
	findans(i,mid,id<<1);findans(mid+1,j,id<<1|1);
}int main(){
	FOR(i,1,n){x[id[i]=i]=qr();y[i]=qr();}
	sort(id+1,id+n+1,cmp);build(1,n,1);
	FOR(i,1,n){
		if(x[id[i]]!=x[id[i+1]]){
			l=id[i];r=n;k=x[id[i]]-1;chg(1,n,1);
			k=y[id[i]];add(1,n,1);
		}if(x[id[i-1]]!=x[id[i]])continue;
		l=id[i-1];r=id[i]-1;k=x[id[i]]-1;chg(1,n,1);
		k=y[id[i-1]];add(1,n,1);//qw(l,' ');qw(r,' ');qw(k,'\n');
	}findans(1,n,1);return 0;
}
```

---

## 作者：大眼仔Happy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P9130)

不会 DS 的我被教育了。

---

对于两个区间合并，前面的区间溢出的干草显然会影响后面，而后面不会影响前面。

所以我们设 $f([l,r],x)$ 表示前面溢出了 $x$ 份干草给 $[l,r]$ 这个区间所得到的答案。分讨一下：

- $x$ 份干草给 $[l,mid]$ 用完了，递归左区间。注意这里加右区间的贡献的时候不是 `t[rc].ans` 而是 `t[k].ans-t[lc].ans`，因为 `ans` 中算的是 $x=0$ 的情况。
- $x$ 份干草有些用到了右区间，说明左区间每天都能吃，这个部分可以 $O(1)$ 计算，然后递归右区间。

上述说明求解 $f$ 每次只会往单侧递归，故一个 pushup 的时间复杂度是 $O(\log n)$ 的。

综上所述，对于每个区间，我们需要维护以下几个东西：

1. 区间的答案。
2. 有多少天可以吃到。
3. 溢出了多少份干草。

所以总时间复杂度是 $O(n\log^2 n)$，自带一个动态开点的大常数。

注意等差数列那里多取模。

~~还别说格式化了代码之后是好看了一点。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
#define ll long long
const ll mod = 1e9 + 7, inv2 = 5e8 + 4;
ll inline read() {
	ll num = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
int q, rt, tot;
struct node {
	int ls, rs;
	ll cnt, out, ans;
} t[N * 46];
#define lc t[k].ls
#define rc t[k].rs
#define mid (l + r >> 1ll)
ll sum(ll L, ll R) {
	return (L + R) % mod * ((R - L + 1) % mod) % mod * inv2 % mod;
}
ll f(int k, ll l, ll r, ll x) {
	if(!x)return t[k].ans;
	if(l == r)return l % mod;
	if(x + t[lc].cnt <= mid - l + 1)return (f(lc, l, mid, x) + t[k].ans - t[lc].ans + mod) % mod;
	else return (sum(l, mid) + f(rc, mid + 1, r, x - (mid - l + 1 - t[lc].cnt) + t[lc].out)) % mod;
}
void pushup(int k, ll l, ll r) {
	t[k].cnt = t[lc].cnt + min(t[lc].out + t[rc].cnt, r - mid);
	t[k].out = t[rc].out + max(t[lc].out + t[rc].cnt - (r - mid), 0ll);
	t[k].ans = (t[lc].ans + f(rc, mid + 1, r, t[lc].out)) % mod;
}
void upd(int &k, ll l, ll r, ll q, ll v) {
	if(!k)k = ++tot;
	if(l == r) {
		if(!v)t[k].cnt = t[k].out = t[k].ans = 0;
		else t[k].cnt = 1, t[k].out = v - 1, t[k].ans = l % mod;
		return;
	}
	if(q <= mid)upd(lc, l, mid, q, v);
	else upd(rc, mid + 1, r, q, v);
	pushup(k, l, r);
}
int main() {
#ifdef file
	freopen("P9130.in", "r", stdin);
	freopen("P9130.out", "w", stdout);
#endif
	q = read();
	while(q--) {
		ll x = read(), y = read();
		upd(rt, 1, 2e14, x, y);
		printf("%lld\n", t[rt].ans);
	}
	return 0;
}
```

---

## 作者：IamZZ (赞：4)

**P组练习总结#2**

### 题目大意

奶牛 Bessie 总是饿，她需要每天吃干草堆，FJ 在特定的几天会给她送来干草堆。

如果仓库里还有干草堆，Bessie 会毫不犹豫选择吃掉一个，剩下的存着，如果仓库空了，那她也没有办法只能选择饿自己了。

当然啦，尽管 Bessie ~~的生命活动极其微弱~~可以 $10^{14}$ 天连续不吃东西，FJ 仍不想她挨饿。

一开始没有一天会送来干草，FJ 会给你 $U(U\leq10^5)$ 个修改操作，具体来说，将第 $d$ 天送来的干草修改为 $b$ 堆，对，是修改，不是增加。

$1\leq d\leq10^{14},0\leq b\leq10^9$。

### 题解思路

数学？一段段的，又不连续，等差数列求和很难实现，很难快速求。

其实，不需要想远，我们用最简单的思想，试着去**模拟**它！

当然需要点技巧，这个过程我们可以用线段树优化，这可真的是一道线段树好题~

建树，我们选择动态开点，直接把整个时间轴建好，注意，最大的时间可以达到近 $2\times10^{14}$，要开大一点。

线段树记录以下信息：

$l,r$：左儿子右儿子，这个正常；

$o(out)$：从这个区间可以剩下多少干草堆贡献给后面的区间；

$s(size)$：记录这个区间已经有几天吃上饭了，反之也知道有几天吃不上饭了；

$w$：左儿子贡献给右儿子干草堆后，右儿子的答案；

$v$：答案。

有了这些关键信息，我们已经可以尝试去解决这道题目啦~

### 具体实现

通过实现线段树的左右儿子信息合并，我们可以快速查询答案。

$s$：左儿子的天数（不受影响的）不变，而右儿子的天数包括自己原本的，还要加上左边可以贡献给右边的，但是要和右区间的大小取 min，两个相加；

$o$：右儿子往后贡献的（不受影响）不变，而左儿子往后贡献的如果把右边填满了还可以剩下一点也能贡献给后面，所以要减去右边空的天数，且不能负，相加；

$w$：最复杂的操作，稍后专讲；

$v$：左儿子的 $v$ 加上当前区间的 $w$；

细讲 $w$ 的处理方式，思维难度都堆在这里了……

设现在我们向后面的区间贡献了 $a$ 个干草堆：

A：如果 $a$ 比左儿子区间空的天数大，我们是不是可以填满它？

这里面的答案可以用等差数列求和解决，而我们只需要递归右区间继续处理，$a$ 会消耗填满左区间的天数，但也会增加左区间向右区间贡献的干草堆数。

B：如果小于呢？

那我们肯定填不满左区间，递归左区间，$a$ 不变，而整个区间的答案还要加上当前区间的 $w$，也就是没有递归的右区间的答案。

如此看来，我们每次肯定只会递归一边的区间，只会增加一个 $\log_2 n$ 的复杂度，可以接受。

$w$ 的处理方式就解决啦~

总复杂度 $\Theta(U\log_2^2N),(N=2\times10^{14})$。

足以通过这题，完结撒花 (●'◡'●)！

### 参考代码

```c++
#include<bits/stdc++.h>
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
typedef long long ll;
using namespace std;
const ll N=2e14;
const int mod=1e9+7,od=5e8+4;
int q,v,c=1,s;
ll x;
struct tree
{
	ll v,s,o,w;//s:size;o:out;w:val;v:ans;
	int l,r;
}t[20000001];
int calc(ll l,ll r)
{
	int v=1ll*(l+r)%mod*((r-l+1)%mod)%mod*od%mod;
	return v;
}
int find(ll l,ll r,int p,ll v)
{
	if(!v)
	  return t[p].v;
	if(l==r)
	  return l%mod;
	ll d=l+r>>1;
	if(v<=d-l+1-t[t[p].l].s)
	  return (find(l,d,t[p].l,v)+t[p].w)%mod;
	return (calc(l,d)+find(d+1,r,t[p].r,v-d+l-1+t[t[p].l].s+t[t[p].l].o))%mod;
}
ll max(ll a,ll b)
{
	return a>b?a:b;
}
ll min(ll a,ll b)
{
	return a<b?a:b;
}
void pushup(ll l,ll r,int p)
{
	int a=t[p].l,b=t[p].r;
	ll d=l+r>>1;
	t[p].s=t[a].s+min(t[b].s+t[a].o,r-d);
	t[p].o=t[b].o+max(t[a].o-r+d+t[b].s,0);
	t[p].w=find(d+1,r,b,t[a].o);
	t[p].v=(t[a].v+t[p].w)%mod;
	return ;
}
int modify(ll l,ll r,int p,ll x,int v)
{
	if(l>x||r<x)
	  return p;
	if(!p)
	  ++c,p=c;
	if(l==r)
	{
		if(!v)
		{
			t[p].s=t[p].v=t[p].o=0;
			return p;
		}
		t[p].s=1,t[p].v=l%mod,t[p].o=v-1;
		return p;
	}
	ll d=l+r>>1;
	t[p].l=modify(l,d,t[p].l,x,v);
	t[p].r=modify(d+1,r,t[p].r,x,v);
	pushup(l,r,p);
	return p;
}
int main()
{
	int i;
	scanf("%d",&q);
	while(q)
	{
		--q;
		scanf("%lld%d",&x,&v);
		modify(1,N,1,x,v);
		printf("%d\n",t[1].v);
	}
	return 0;
}

```



---

## 作者：Arghariza (赞：4)

这个涂色很容易让人想到均摊的 set 维护，但是有可能修改同一个位置，不太可做。

同样地，我们考虑只带插入不同位置的情况。

考虑一个线段树做法，直接维护整行格子的权值和以及黑色格子的个数。考虑一个修改 $(i,j)$ 相当于区间覆盖 $[i,k]$ ，其中 $[i,k]$ 中修改前白色格子的数量为 $j$。显然有单调性，于是可以线段树上二分。

于是你可以把弱化版（铜组 T1）过了，复杂度 $O(n\log w)$。

考虑到两个下标相同的修改 $(i,j_1)$ 和 $(i,j_2)$ 分别在时刻 $t_1,t_2(t_1<t_2)$ 进行，并且之间没有任何 $i$ 位置的修改。可以看作 $(i,j_1)$ 操作的影响范围为 $[t_1,t_2)$，也就是说每次操作的影响范围都是一段区间。直接线段树分治，做完了。

由于不太好撤销，可以在时间线段树每个节点上开动态开点线段树。需要可持久化一下，并且合理利用空间。复杂度是 $O(n\log n\log w)$ 的。

[提交记录。](https://qoj.ac/submission/84798)

---

## 作者：yinianxingkong (赞：3)

根号做法。

修改影响过大，十分困难，得转换成增加。

线段树分治需要撤销，直接势能是不对的，可能得上别的科技。

一个常见技巧是将时间和下标翻转，这样可以对下标维度作扫描线。

本题翻转后，用线段树维护每个询问当前位置还剩多少草。修改体现在时间维度就是区间加。

问题大致变成了：全局减一，和零取最值，区间加，非零的位置答案加一个值。

注意到时间轴有点长，需要离散化，重新整理一下：全局减，和零取最值，区间加。答案贡献是：设全局减的数为 $x$，比 $x$ 小的数自己位置的答案加一个类似等差数列的值，否则加一个定值。

这个比较像历史和的东西我没想出线段树做法。

二维限制考虑分块。注意到所有操作都不会影响整块间的相对顺序，考虑维护排序后的数组。维护块内指针，表示一个前缀的值是相同的，显然全局减只会使指针右移。区间加重构散块时重置指针，只会重置 $Q$ 次，也就是多跑 $Q\sqrt{n}$ 次，复杂度可以接受。称这个前缀为“零段”。

考虑一次全局减并计算贡献。零段内的数的贡献相同，是一个前缀加，打标记重构时遍历即可。指针移动时，被移动的数暴力更新，没被移动的数是后缀加同理。

总复杂度 $O(Q\sqrt{n})$。

要代码私信。

作者数据结构不太好，感觉这个思路能有 $\text{polylog}$ 做法，欢迎和我探讨。

---

## 作者：C_Pos_Princess (赞：1)

## 题解

我们想到用线段树维护，那么更改一个点可能会让后面区间的值改变，那么如何维护。

既然一个区间影响到了另一个区间，那我们不妨只维护左区间的数值，去更新根节点答案即可。

那每次修改操作是 $O(\log n)$ 的，计算贡献也是 $O(\log n)$ 的，总复杂度 $O(q\log^2n)$ 。

## 实现过程
维护四个值：

1. 吃饭的有几天；
2. 左区间贡献给右区间的有多少；
3. 右区间答案；
4. 总答案。


## 完整代码
```
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e7+10;
const int mod = 1e9+7;
const ll inv = 5e8+4;
const ll inf = 2e14+10;
struct node{
	ll l,r;
	ll val,siz,ans,out;	
	
}tr[N];
ll tot;
ll cal(ll l,ll r){
	return (l+r)%mod*((r-l+1)%mod)%mod*inv%mod;
}

ll supply(ll rt,ll l,ll r,ll x){
	
	if(!x) return tr[rt].ans;
	if(l== r) return l%mod;
	ll mid = l+r>>1;
	if(x<=mid-l+1-tr[tr[rt].l].siz) return (supply(tr[rt].l,l,mid,x)+tr[rt].val)%mod;
	return (cal(l,mid)+supply(tr[rt].r,mid+1,r,x-(mid-l+1-tr[tr[rt].l].siz)+tr[tr[rt].l].out));
}

void pushup(ll rt,ll l,ll r){
	
	ll mid= l+r>>1;
	tr[rt].siz = tr[tr[rt].l].siz+min(tr[tr[rt].r].siz+tr[tr[rt].l].out,r-mid);
	tr[rt].out = tr[tr[rt].r].out+max(tr[tr[rt].l].out+tr[tr[rt].r].siz-(r-mid),0ll);
	tr[rt].val = supply(tr[rt].r,mid+1,r,tr[tr[rt].l].out);
	tr[rt].ans = (tr[rt].val+tr[tr[rt].l].ans)%mod;
}

void update(ll &rt,ll l,ll r,ll x,ll k){
	
	if(!rt)rt = ++tot;
	if(l == r){
		if(!k){
			tr[rt].siz = tr[rt].ans = tr[rt].out = 0;
			return;
		}
		tr[rt].siz = 1,tr[rt].ans = l%mod,tr[rt].out = k-1;
		return;
	}
	ll mid = l+r>>1;
	if(x<=mid) update(tr[rt].l,l,mid,x,k);
	else update(tr[rt].r,mid+1,r,x,k);
	pushup(rt,l,r);
}

ll q,rt;

int main(){
	scanf("%lld",&q);
	while(q--){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		update(rt,1,inf,x,y);
		printf("%lld\n",tr[rt].ans);
	}	
	
	
	return 0;
}
```

---

## 作者：Luciylove (赞：1)

本来以为是 [P5609 [Ynoi2013] 对数据结构的爱
](https://www.luogu.com.cn/problem/P5609) 一样维护分段函数。

注意到这个东西是初始值为 $0$ 的函数，我们使用权值线段树维护之。

观察到我们一个点模拟完左半边的天数会对右半边产生贡献，所以我们可以考虑使用单侧递归线段树。

按照线段树二分的条件，我们需要维护该节点有的吃草的天数 $d$，以及会溢出到右儿子的贡献 $o$，还有按照模板来的左儿子的答案 $v$。

这两段信息的合并是类似线段树维护连续段信息的，只需要判定是否可以连起来就好了。

然后你写一个线段树二分查询左儿子对于右儿子的贡献，如果只能递归左儿子，那么需要知道右儿子从 $0$ 开始的分段函数结果，再结合无法递归的条件容易知道答案是 $v_x - v_{lc}$。递归到右儿子贡献就是一个等差数列。


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define lc t[x].ls
#define rc t[x].rs
using namespace std;

typedef long long ll;
const int i2 = (1e9 + 8) / 2, mod = 1e9 + 7;

struct seg {
	int ls, rs;
	ll dy, out, ans; 
} t[20000000 + 5]; 
int n, q, cnt;
ll qSum (ll l, ll r) {
	return (r - l + 1) % mod * ((l + r) % mod) % mod * i2 % mod;
}
ll query (int x, ll l, ll r, ll d) {
	if (!d) return t[x].ans;
	if (l == r) return l % mod;
	ll mid = (l + r) >> 1;
	if (d + t[lc].dy <= mid - l + 1)
		return (query(lc, l, mid, d) + (t[x].ans - t[lc].ans + mod) % mod) % mod;
	else return (qSum(l, mid) + query(rc, mid + 1, r, d - (mid - l + 1 - t[lc].dy) + t[lc].out)) % mod;
}
void pushup (int x, ll l, ll mid, ll r) {
	t[x].dy = t[lc].dy + min(t[rc].dy + t[lc].out, r - mid);
	t[x].out = t[rc].out + max(t[lc].out + t[rc].dy - (r - mid), 0ll);
	t[x].ans = (t[lc].ans + query(rc, mid + 1, r, t[lc].out)) % mod;
}
void Insert (int &x, ll l, ll r, ll v, ll k) {
	if (!x) x = ++ cnt;
	if (l == r) {
		if (!k) t[x].dy = t[x].out = t[x].ans = 0;
		else t[x].dy = 1, t[x].ans = l % mod, t[x].out = k - 1;
		return ;
	}
	ll mid = (l + r) >> 1;
	v <= mid ? Insert(lc, l, mid, v, k) : Insert(rc, mid + 1, r, v, k);
	pushup(x, l, mid, r);	
}
int main () {
	int rt = 0;
	cin >> q;
	while (q --) {
		ll x, y;
		scanf("%lld%lld", &x, &y);
		Insert(rt, 1, 2e14, x, y);
		printf("%lld\n", t[rt].ans);	
	}
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：1)

动态开点线段树来维护。

对于每个节点管辖的区间 $[l,r]$，你想直接维护答案，但是会寄。

再维护一个染黑的个数，还是合并不了。

再维护一个向右溢出的个数，好像能合并了。

你发现更新答案又是个问题。要求计算右半区间的答案。你考虑左边溢出的扔到右边对右边答案的改变，再写一个线段树二分即可。我们要左边溢出的尽量往左边空着的填，单侧递归即可。

填的时候若 $[l,mid]$ 都满了，左边的答案是 $\sum_{j=l}^{mid} j$，然后再往 $[mid+1,r]$ 递归，填不满就往左子递归。

时间复杂度 $O(n\log A\log n)$。

---

## 作者：LinkWish (赞：1)

提供一种代码难度稍微大一点，但是思路极其简单的解法。

不难想到线段树分治，使用可持久化平衡树来维护空白的区间。

一次操作可以看做删除位置大于等于给定位置的最开始的若干个白块。注意一下边界情况，即长度不能直接分成若干个区间的和时，需要再次拆分成小区间再继续操作。

时间复杂度 $O(n\log^2n)$，虽然空间复杂度也是 $O(n\log n)$，由于空间常数较大，记得把数组开大一点。

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define fi first
#define se second
#define si static inline
using namespace std;
typedef const int ci;
typedef const long long cl;
typedef long long ll;
typedef long double ld;
typedef __int128 li;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int iinf=INT_MAX;
const ll linf=LLONG_MAX;
const ld pi=acos(-1);
template<typename T>
si bool gmax(T &x,T y)
{if(y>x){x=y;return 1;}return 0;}
template<typename T>
si bool gmin(T &x,T y)
{if(y<x){x=y;return 1;}return 0;}
ci N=100005,mod=1e9+7,lim=2e14;
int n,all;

struct node{
	int l,r,sum,len;
	int ls,rs,key;
}t[N*100];
int cnt;
int rt[N*10],bb;
mt19937 R(time(0));
si int np(int l,int r){
	cnt++;
	t[cnt].l=l,t[cnt].r=r,t[cnt].sum=li(l+r)*(r-l+1)/2%mod;
	t[cnt].ls=t[cnt].rs=0,t[cnt].key=R(),t[cnt].len=r-l+1;
	return cnt;
}
si void push_up(int x){
	t[x].sum=(t[t[x].ls].sum+t[t[x].rs].sum+li(t[x].l+t[x].r)*(t[x].r-t[x].l+1)/2%mod)%mod;
	t[x].len=t[t[x].ls].len+t[t[x].rs].len+t[x].r-t[x].l+1;
}
void split(int pre,int &x,int &y,int k){
	if(!pre)return x=y=0,void();
	int cur=++cnt;
	t[cur]=t[pre];
	if(t[cur].r>=k){
		y=cur;
		split(t[pre].ls,x,t[cur].ls,k);
	}
	else{
		x=cur;
		split(t[pre].rs,t[cur].rs,y,k);
	}
	push_up(cur);
}
void splitl(int pre,int &x,int &y,int k){
	if(!pre)return x=y=0,void();
	int cur=++cnt;
	t[cur]=t[pre];
	if(k<=t[t[pre].ls].len){
		y=cur;
		splitl(t[pre].ls,x,t[cur].ls,k);
	}
	else{
		x=cur;
		splitl(t[pre].rs,t[cur].rs,y,k-t[t[x].ls].len-t[x].r+t[x].l-1);
	}
	push_up(cur);
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	int cur=++cnt;
	if(t[x].key<t[y].key){
		t[cur]=t[x];
		t[cur].rs=merge(t[cur].rs,y);
	}
	else{
		t[cur]=t[y];
		t[cur].ls=merge(x,t[cur].ls);
	}
	push_up(cur);
	return cur;
}
si void insert(int &nrt,int l,int r){
	int a,b;
	split(nrt,a,b,l);
	nrt=merge(a,merge(np(l,r),b));
}
si void adjust(int pos,int len){
	int a,b,c;
	split(rt[bb],a,b,pos);
	int now=b,v,nxt;
	while(t[now].ls)now=t[now].ls;
	if(t[now].l<pos)insert(a,t[now].l,pos-1),v=len+pos-t[now].l;
	else v=len;
	split(b,b,c,v);
	if(t[b].len!=v){
		nxt=b;
		while(t[nxt].rs)nxt=t[nxt].rs;
		if(t[now].l==t[nxt].l&&t[now].r==t[nxt].r)insert(c,max(pos,t[nxt].l)+len,t[nxt].r);
		else insert(c,t[nxt].l+v-(t[b].len-t[nxt].r+t[nxt].l-1),t[nxt].r);
	}
	rt[++bb]=merge(a,c);
}

struct opr{int pos,len;};
vector<opr> g[N<<2];
si int ls(int x){return x<<1;}
si int rs(int x){return x<<1|1;}
void add(int x,int l,int r,int L,int R,opr k){
	if(l>=L&&r<=R)return g[x].push_back(k),void();
	int mid=(l+r)>>1;
	if(L<=mid)add(ls(x),l,mid,L,R,k);
	if(R>mid)add(rs(x),mid+1,r,L,R,k);
}
void solve(int x,int l,int r){
	int tmp=bb,tc=cnt;
	for(opr i:g[x]){
		if(i.len)adjust(i.pos,i.len);
	}
	if(l==r){
		cout<<(all-t[rt[bb]].sum+mod)%mod<<endl;
		bb=tmp,cnt=tc;
		return ;
	}
	int mid=(l+r)>>1;
	solve(ls(x),l,mid);
	solve(rs(x),mid+1,r);
	bb=tmp,cnt=tc;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	map<int,pii> lst;
	for(int i=1,pos,len;i<=n;i++){
		cin>>pos>>len;
		if(lst.count(pos))add(1,1,n,lst[pos].fi,i-1,opr{pos,lst[pos].se});
		lst[pos]=pii(i,len);
	}
	for(auto i:lst)add(1,1,n,i.se.fi,n,opr{i.fi,i.se.se});
	rt[++bb]=np(1,lim),all=li(1+lim)*lim/2%mod;
	solve(1,1,n);
	return 0;
}
```

update：可持久化线段树也可以维护线段树分治上的操作，并且代码简单一些，只不过要注意复杂度的保证，不要写成了伪的带撤销势能分析，要严格 $O(\log n)$ 完成单次操作。维护的东西不太一样，线段树维护的是值域。

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define fi first
#define se second
#define si static inline
using namespace std;
typedef const int ci;
typedef const long long cl;
typedef long long ll;
typedef long double ld;
typedef __int128 li;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int iinf=INT_MAX;
const ll linf=LLONG_MAX;
const ld pi=acos(-1);
template<typename T>
si bool gmax(T &x,T y)
{if(y>x){x=y;return 1;}return 0;}
template<typename T>
si bool gmin(T &x,T y)
{if(y<x){x=y;return 1;}return 0;}
ci N=100005,mod=1e9+7,lim=2e14;
int n;
struct node{
	int ls,rs,sum,len;
	bool full;
}t[N*120];
int rt[N],cnt,cur;
si void push_up(int x){
	t[x].sum=(t[t[x].ls].sum+t[t[x].rs].sum)%mod;
	t[x].full=t[t[x].ls].full&t[t[x].rs].full;
	t[x].len=t[t[x].ls].len+t[t[x].rs].len;
}
void adjust(int pre,int &x,int l,int r,int goal,int &k){
	t[x=++cnt]=t[pre];
	if(!k)return ;
	if(l==r){
		if(!t[x].full&&k)t[x].sum=l%mod,t[x].full=1,k--,t[x].len=1;
		return ;
	}
	if(goal<=l&&k>=r-l+1-t[x].len){
		k-=r-l+1-t[x].len,t[x].full=1;
		t[x].sum=li(l+r)*(r-l+1)/2%mod,t[x].len=r-l+1;
		return ;
	}
	int mid=(l+r)>>1;
	if(goal<=mid){
		if(!t[t[x].ls].full)adjust(t[pre].ls,t[x].ls,l,mid,goal,k);
		if(k&&!t[t[x].rs].full)adjust(t[pre].rs,t[x].rs,mid+1,r,goal,k);
	}
	else if(!t[t[x].rs].full)adjust(t[pre].rs,t[x].rs,mid+1,r,goal,k);
	push_up(x);
}

struct opr{int pos,len;};
vector<opr> g[N<<2];
si int ls(int x){return x<<1;}
si int rs(int x){return x<<1|1;}
void add(int x,int l,int r,int L,int R,opr k){
	if(l>=L&&r<=R)return g[x].push_back(k),void();
	int mid=(l+r)>>1;
	if(L<=mid)add(ls(x),l,mid,L,R,k);
	if(R>mid)add(rs(x),mid+1,r,L,R,k);
}
void solve(int x,int l,int r){
	int tmp=cur,p,tc=cnt;
	for(opr i:g[x]){
		cur++,p=i.len;
		adjust(rt[cur-1],rt[cur],1,lim,i.pos,p);
	}
	if(l==r){
		cout<<t[rt[cur]].sum<<endl;
		cur=tmp,cnt=tc;
		return ;
	}
	int mid=(l+r)>>1;
	solve(ls(x),l,mid);
	solve(rs(x),mid+1,r);
	cur=tmp,cnt=tc;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	map<int,pii> lst;
	for(int i=1,pos,len;i<=n;i++){
		cin>>pos>>len;
		if(lst.count(pos))add(1,1,n,lst[pos].fi,i-1,opr{pos,lst[pos].se});
		lst[pos]=pii(i,len);
	}
	for(auto i:lst)add(1,1,n,i.se.fi,n,opr{i.fi,i.se.se});
	solve(1,1,n);
	return 0;
}
```

---

## 作者：LJ07 (赞：1)

通过类比，可以 尝试考虑 类似楼房重建（抑或是兔队线段树）的想法。（下面的涂色即为吃干草 的意思。色块即为吃的干草块

从考虑如何 pushup 入手。考虑前面的区间的涂色对后面区间的涂色的影响（这里的前后指的是起始点的前后）。

发现如果前面区间占用了后面区间的位置超过一个限定值，那么后面区间的涂色的色块就会合成一个连续段。

同时容易发现如果没有使得后面的区间的涂色的色块合成一个连续段，那么后面区间涂的最右边的色块的位置不变。

那么 pushup 思路就很显然了：

```
  if (前面区间占用了 Lson 区间的位置超过一个限定值) 
    计算左区间的贡献，递归右区间
  else
    右区间的贡献不变（参照楼房重建），递归左区间
```

剩余部分都是容易的。

离散化后时间复杂度 $O(n\log^2n)$，空间复杂度 $O(n)$。

[初值赋丑巨多特判的Code](https://www.luogu.com.cn/record/104287042)

---

## 作者：_AIR (赞：0)

题目大意：每次给出一组 $x,y$，从 $x$ 开始往后数 $y$ 个值为 $0$ 的数，将其赋为 $1$，然后查询数组中所有值为 $1$ 的数的编号之和。

由于 $x \leqslant 10^{14}$，一个比较显然的做法是直接用**动态开点线段树**维护整个时间轴的值，但是很快就会发现有些困难，因为我的某些区间是会向右溢出的，溢出的这一部分比较不好维护更新。

于是我们设一个函数 $\operatorname{overflow}(rt,l,r,x)$ 表示 $[l,r]$ 区间的左边的区间溢出了 $x$ 到 $[l,r]$ 对答案产生的贡献。

- 如果 $x$ 在 $[l,mid]$ 就被用完了，那么就递归左区间求解，然后加上右区间贡献。
- 如果 $x$ 到 $[mid+1,r]$ 还有剩余，那么 $[l,mid]$ 的答案就全部统计上，就是一个等差数列，然后递归右区间求解。

一次操作的时间复杂度是 $\log$ 的，一次 $\operatorname{pushup}$ 就是 $\log^2$，足够通过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 1000000007
const int inf=1.5e14;
const int inv2=5e8+4;
int q;
struct Tree
{
    int ls,rs;
    int ans,out,cnt;//cnt表示当前区间有多少个1，out表示当前区间向外溢出多少，ans表示区间答案
}tr[20000005];
int tot;
int cal(int l,int r)
{
    return (l+r)%mod*((r-l+1)%mod)%mod*inv2%mod;
}
int overflow(int rt,int l,int r,int x)
{
    if(!x)return tr[rt].ans;
    if(l==r)return l%mod;
    int mid=(l+r)>>1;
    if(x+tr[tr[rt].ls].cnt<=mid-l+1)return ((overflow(tr[rt].ls,l,mid,x)+tr[rt].ans-tr[tr[rt].ls].ans)%mod+mod)%mod;//左区间全部用完
    else return (cal(l,mid)+overflow(tr[rt].rs,mid+1,r,x-(mid-l+1-tr[tr[rt].ls].cnt)+tr[tr[rt].ls].out))%mod;//左区间还有剩余
}
inline void pushup(int rt,int l,int r)
{
    int mid=(l+r)>>1;
    tr[rt].cnt=tr[tr[rt].ls].cnt+min(tr[tr[rt].ls].out+tr[tr[rt].rs].cnt,r-mid);
    tr[rt].out=tr[tr[rt].rs].out+max(tr[tr[rt].ls].out+tr[tr[rt].rs].cnt-(r-mid),0ll);
    tr[rt].ans=(tr[tr[rt].ls].ans+overflow(tr[rt].rs,mid+1,r,tr[tr[rt].ls].out))%mod;
    return ;
}
inline void update(int &rt,int l,int r,int pos,int val)
{
    if(!rt)rt=++tot;
    if(l==r)
    {
        if(!val)tr[rt].cnt=tr[rt].out=tr[rt].ans=0;
        else tr[rt]={tr[rt].ls,tr[rt].rs,l%mod,val-1,1};
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)update(tr[rt].ls,l,mid,pos,val);
    else update(tr[rt].rs,mid+1,r,pos,val);
    pushup(rt,l,r);
}
int root;
signed main()
{
    scanf("%lld",&q);
    while(q--)
    {
        int x,y;
        scanf("%lld%lld",&x,&y);
        update(root,1,inf,x,y);
        printf("%lld\n",tr[root].ans);
    }
}
```

---

