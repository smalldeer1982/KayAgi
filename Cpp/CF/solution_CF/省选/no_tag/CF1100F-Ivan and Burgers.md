# Ivan and Burgers

## 题目描述

Ivan 喜欢汉堡和花钱。在 Ivan 所住的街道上有 $n$ 家汉堡店。Ivan 有 $q$ 个朋友，第 $i$ 个朋友建议在第 $l_i$ 家汉堡店见面，然后一起走到第 $r_i$ 家汉堡店（$l_i \leq r_i$）。在和第 $i$ 个朋友散步的过程中，Ivan 可以访问所有满足 $l_i \leq x \leq r_i$ 的汉堡店 $x$。

对于每家汉堡店，Ivan 都知道其中最贵的汉堡价格，记为 $c_i$ burles。Ivan 想在路上选择一些汉堡店，每到一家就买最贵的汉堡，并且花掉最多的钱。但有个小问题：他的银行卡坏了，每次消费后卡上的金额变化如下。

如果消费前 Ivan 有 $d$ burles，在汉堡店消费了 $c$ burles，那么消费后他卡上的余额会变成 $d \oplus c$，其中 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

目前 Ivan 卡上有 $2^{2^{100}} - 1$ burles，他想和朋友们一起散步。请你帮他计算：如果和第 $i$ 个朋友一起散步，他最多能花掉多少钱？他花掉的钱定义为初始金额减去最终金额。

## 说明/提示

在第一个测试中，为了和第一个和第三个朋友花掉最多的钱，Ivan 只需要进入第一家汉堡店。和第二个朋友时，Ivan 只需要进入第三家汉堡店。

在第二个测试中，对于第三个朋友（从第一家走到第三家），一共有 8 种花钱方式——$0$、$12$、$14$、$23$、$12 \oplus 14 = 2$、$14 \oplus 23 = 25$、$12 \oplus 23 = 27$、$12 \oplus 14 \oplus 23 = 20$。最大能花掉的钱是 $12 \oplus 23 = 27$，也就是进入第一家和第三家汉堡店。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
7 2 3 4
3
1 4
2 3
1 3
```

### 输出

```
7
3
7
```

## 样例 #2

### 输入

```
5
12 14 23 13 7
15
1 1
1 2
1 3
1 4
1 5
2 2
2 3
2 4
2 5
3 3
3 4
3 5
4 4
4 5
5 5
```

### 输出

```
12
14
27
27
31
14
25
26
30
23
26
29
13
13
7
```

# 题解

## 作者：jun头吉吉 (赞：48)

## 题意
给定一组数$a$，有$q$组询问求$a_l\to a_r$的异或最大值
## 题解
这是一道**前缀**线性基的板子题

我们的前缀线性基需要两个变量：$p[i]$表示第$i$位的值，$pos[i]$表示对第$i$位造成影响的数的编号。那么很显然，假如我们已经求出了$1\to r$的线性基，其中所有$pos≥l$的数构成的线性基就是区间$[l,r]$的数构成的线性基

根据**贪心**的思想，我们知道，我们要尽可能地让$pos[i]$的值最大，这样才能保证我们通过上述方法构造出的线性基是$[l,r]$的线性基

**那么如何保证$pos[i]$的值最大呢？**

很简单，如果我们插入一个值$x$，它的位置为$w$，那么如果有一位的$pos<w$，那么我们就把这一位的$p$取出来换成$x$，$pos$换成$w$，然后把$pos,p $继续往下插入，这样构造出的线性基$pos$就是最大的
## 代码
```cpp
#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
typedef long long ll;
const int max_wei=30;
const int maxn=500000+10;
struct Prefix_Linear_Basis{
	ll p[max_wei+1];int pos[max_wei+1];
	inline void init(){memset(p,0,sizeof p);memset(pos,0,sizeof pos);}
	inline void insert(Prefix_Linear_Basis A,int w,ll val){
		*this=A;
		for(int i=max_wei;i>=0;i--)if(val>>i&1){
			if(!p[i]){p[i]=val,pos[i]=w;return;}
			else if(pos[i]<w){swap(pos[i],w);swap(p[i],val);}
			val^=p[i];
		}
	}
	inline ll Query(int l){
		//查询此基中所有≥l的最大值
		ll ans=0;
		for(int i=max_wei;i>=0;i--)
			if(p[i]&&pos[i]>=l)ans=max(ans,ans^p[i]);
		return ans; 
	}
}a[maxn];
int n,q,x,l,r;
signed main(){
	read(n);a[0].init();
	for(int i=1;i<=n;i++)
		read(x),a[i].insert(a[i-1],i,x);
	read(q);
	while(q--){
		read(l,r);
		write(a[r].Query(l));
		putchar('\n');
	}
}
```

---

## 作者：_sys (赞：29)

因为$n,q=500000,a[i]=1e6$，所以复杂度分析全用$n$表示

看到$xor$最大我们想到线性基。
先介绍$O(n\log^3n)$的做法：用线段树维护线性基，每次暴力合并（一个线性基的所有元素插入到另一个线性基里）
原题：

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn=500005;
int n,q,a[Maxn];
int read(int &x)
{
	x=0; 
	char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x*=10,x+=ch-'0',ch=getchar();
}
struct Lin
{
	int val[21];
	Lin()
	{
		memset(val,0,sizeof(val));
	}
};
struct Tree
{
	int lt,rt;
	Lin bas;
}tree[4*Maxn];
Lin tmp;
void insert_base(int x)
{
	if(!x) return ;
	int hb=log2(x);
	if(!tmp.val[hb]) tmp.val[hb]=x;
	if(tmp.val[hb]) insert_base(x^tmp.val[hb]);
}
Lin merge(Lin x,Lin y)
{
	tmp=y;
	for(int i=0;i<=20;i++)
		insert_base(x.val[i]);
	return tmp;
}
void build(int root,int lt,int rt)
{
	tree[root]=(Tree){lt,rt};
	if(lt+1!=rt)
	{
		int mid=(lt+rt)/2;
		build(root<<1,lt,mid);
		build(root<<1|1,mid,rt);
		tree[root].bas=merge(tree[root<<1].bas,tree[root<<1|1].bas);
	}
	else 
		if(a[lt]) tree[root].bas.val[(int)log2(a[lt])]=a[lt];
}
Lin ask(int root,int lt,int rt)
{
	if(lt==tree[root].lt&&rt==tree[root].rt)
		return tree[root].bas;
	else
	{
		int mid=(tree[root].lt+tree[root].rt)/2;
		if(lt>=mid) return ask(root<<1|1,lt,rt);
		else if(rt<=mid) return ask(root<<1,lt,rt);
		else
			return merge(ask(root<<1,lt,mid),ask(root<<1|1,mid,rt));
	}
}
int work(Lin a)
{
	int ans=0;
	for(int i=20;i>=0;i--)
		if(ans<(ans^a.val[i])) ans=ans^a.val[i];
	return ans;
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);
	build(1,1,n+1);
	read(q);
	for(int i=1;i<=q;i++)
	{
		int l,r;
		read(l),read(r);
		printf("%d\n",work(ask(1,l,r+1)));
	}
	return 0;
}
```

但是$n,q=500000$，显然三只 $\log$ 过不去。
于是我们考虑，对于$[l,r],[l+1,r],[l+2,r]...[r,r]$的线性基最多只有20(也就是$log_21000000$ 种)。并且当r向后，线性基发生改变的还是这些点与新加入的$[r,r]$的子集。
我们可以把询问按$r$排序，维护$[1,r],[2,r],[3,r]...[r,r]$的线性基的集合与线性基发生改变的点，当$r$向后推时把$a[r]$插入这20个线性基中。

时间复杂度$O(n\log^2n)$

代码:

（玄学WA17，咕咕咕中）

实际上，我们还有更优秀的做法。

我们考虑线性基取子集异或最大值的过程。如果第$i$位有值，那么就取第$i$位，这样$ans$的第$i$位就能保证是$1$。

我们还是按$r$排序。我们令 $pos[i]$ 表示 $[l,r]$ 线性基第 $i$ 位有值的最大的$l$，每一次按照普通线性基插入的方式向线性基$base$中插入$a[i]$。处理答案时，如果$base[i]$有值，且$pos[i]\geq l$，那么就代表我们可以选择这一位，这样贪心地取，就是答案。

时间复杂度$O(n\log n)$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn=500005;
int bas[21],pos[21],n,rt,a[Maxn],q;
struct quest
{
	int lt,rt,id;
	bool operator < (const quest &tmp) const
	{
		return rt<tmp.rt;
	}
}Q[Maxn];
void insert(int x,int id)
{
	for(int i=20;i>=0;i--)
	{
		if(x&(1<<i))
		{
			if(!bas[i])
			{
				bas[i]=x;
				pos[i]=id;
				return ;
			}
			if(pos[i]<id) swap(pos[i],id),swap(x,bas[i]);
			x^=bas[i];
		}
	}
}
int work(int lt)
{
	int ans=0;
	for(int i=20;i>=0;i--)
		if(pos[i]>=lt&&ans<(ans^bas[i]))
			ans^=bas[i];
	return ans;
}
int ans[Maxn];
int main()
{ 
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
		scanf("%d%d",&Q[i].lt,&Q[i].rt),Q[i].id=i;
	sort(Q+1,Q+1+q);
	for(int i=1;i<=q;i++)
	{
		while(rt<Q[i].rt)
		{
			rt++;
			insert(a[rt],rt);
		}
		ans[Q[i].id]=work(Q[i].lt);
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

不过还没有结束(滑稽)。

实际上，$O(n\log n)$的算法可以强制在线。

我们对于每个$r$都这样预处理下来，就能够直接查询了。



---

## 作者：Juanzhang (赞：10)

如果暴力维护线性基，线段树时间复杂度为 $O(n\log^2n)-O(\log^3n)$

由于重复元素对答案没有影响，于是可以用ST表维护，时间复杂度为 $O(n\log^3n)-O(\log^2n)$

两种做法都无法通过本题。

如果沿用这个思路，瓶颈显然在线性基合并的 $O(\log^2n)$ 上，无法再加优化

常见的 RMQ 有ST表的 $O(n\log n)-O(1)$ 的做法，但 $O(n)-O(1)$ 的标准RMQ很难写、常数较大，且无法解决本题，于是可以考虑在随机数据下期望 $O(n)-O(1)$ 的 lxl ST表

> 分块，大小设为 $x$
>
> 预处理每个块两端到块内每个点的前缀 $\max$ 和后缀 $\max$
>
> 预处理块间ST表
>
> 若查询 $[l,\ r]$ ，且 $l,\ r$ 分别在块 $a,\ b$ 中
>
> 则查块 $a,\ b$ 之间的 RMQ ，以及 $l$ 在 $a$ 块的后缀 $\max$ 和 $r$ 在 $b$ 块的前缀 $\max$
>
> 当 $l,\ r$ 在同一块中时，暴力求解
>
> 可以取 $x=\log n$ ，当 $l,\ r$ 不在同一块中时，这个算法是 $O(1)$ 的
>
> 摘自 [P3793 由乃救爷爷](https://www.luogu.org/problemnew/show/P3793)

如上维护，预处理块中前缀后缀线性基 $O(n\log n)$ ，块间ST表线性基 $O(\frac{n}{x}\log n\log^2n)=O(n\log^2n)$

若 $l,\ r$ 在同一块中，将 $[l,\ r]$ 中的元素暴力插入线性基， $O(x\log n)=O(\log^2n)$ ；若 $l,\ r$ 不在同一块中，合并前缀后缀块间三个线性基 $O(\log^2n)$

综上所述，时间复杂度 $O(n\log^2n)$ ，可能还需要卡卡常

代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10, maxm = 7850, base = 63;
int n, m, tot, lg[maxm], a[maxn];

#define get(x) (((x) + base) >> 6)

struct linear_base {
  int a[20];

  inline void clr() {
    memset(a, 0, sizeof a);
  }

  inline void ins(int x, int lim = 19) {
    for (int i = lim; ~i; --i) {
      if (x >> i & 1) {
        if (!a[i]) { a[i] = x; return; }
        x ^= a[i];
      }
    }
  }

  inline int query() {
    int res = 0;
    for (int i = 19; ~i; --i) {
      if ((res ^ a[i]) > res) res ^= a[i];
    }
    return res;
  }
} null, lef[maxn], rig[maxn], val[13][maxm];

inline linear_base operator + (linear_base A, const linear_base &B) {
  for (int i = 19; ~i; --i) {
    if (B.a[i]) A.ins(B.a[i], i);
  }
  return A;
}

const int maxn_r = maxn * 23, maxn_w = maxn * 8;
char buf_r[maxn_r], *now_r = buf_r;
char buf_w[maxn_w], *now_w = buf_w;

inline int read() {
  int x = 0;
  while (*now_r < 48) ++now_r;
  while (*now_r > 47) x = (x << 3) + (x << 1) + (*now_r ^ 48), ++now_r;
  return x;
}

inline void write(int x) {
  static char *tp, st[7];
  if (!x) *now_w = 48, ++now_w;
  for (tp = st; x; *++tp = x % 10 | 48, x /= 10);
  while (tp != st) *now_w = *tp, ++now_w, --tp;
  *now_w = 10, ++now_w;
}

inline linear_base query(const int &l, const int &r) {
  if (l > r) return null;
  const int k = lg[r - l + 1];
  return val[k][l] + val[k][r - (1 << k) + 1];
}

int main() {
  fread(buf_r, 1, maxn_r, stdin);
  n = read(), tot = get(n);
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    val[0][get(i)].ins(a[i]);
  }
  for (int i = 2; i <= tot; ++i) {
    lg[i] = lg[i >> 1] + 1;
  }
  linear_base lst;
  lst.clr();
  for (int i = 1; i <= n; ++i) {
    lst.ins(a[i]), lef[i] = lst;
    if (!(i & base)) lst.clr();
  }
  lst.clr();
  for (int i = n; i; --i) {
    if (!(i & base)) lst.clr();
    lst.ins(a[i]), rig[i] = lst;
  }
  for (int i = 1; i <= lg[tot]; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= tot; ++j) {
      val[i][j] = val[i - 1][j] + val[i - 1][j + (1 << (i - 1))];
    }
  }
  m = read();
  register linear_base ans;
  for (int q = 1; q <= m; ++q) {
    const int l = read(), r = read();
    const int L = get(l), R = get(r);
    ans.clr();
    if (L == R) {
      for (register int i = l; i <= r; ++i) {
        ans.ins(a[i]);
      }
    } else {
      ans = rig[l] + lef[r] + query(L + 1, R - 1);
    }
    write(ans.query());
  }
  fwrite(buf_w, 1, now_w - buf_w, stdout);
  return 0;
}
```

---

## 作者：decoqwq (赞：9)

我们将一个序列转为一棵树(链)

然后就是树的点分治，每次求出重心后，求出重心到每个点路径上的数的线性基，对于每个询问，只需要暴力合并两个线性基即可。

因为是一条链，所以重心直接取当前链中点即可

时间复杂度大概$O(30nlogn+900q)$

不给代码啦

---

## 作者：mrsrz (赞：8)

在一些数中取若干个数，要求异或和最大，不难想到线性基。

直接线段树维护区间，则复杂度达到$O((n+q)\log^3 n)$，用ST表的话，预处理复杂度也达到了$O(n\log^3 n)$，难以接受。

考虑离线，然后分治。每次考虑解决经过当前区间中点的询问。

对于一个区间，我们处理出中点$mid$往左的后缀线性基、往右的前缀线性基，则可以在$O(\log^2 n)$（线性基合并）的复杂度解决一个经过中点的询问。

然后，对于两端点都在左边的区间，往左递归处理；两端点都在右边的区间，往右递归处理。

分治时间复杂度：$T(n)=2T(\frac n 2)+O(n\log n)=O(n\log^2 n)$。加上处理所有询问的复杂度$O(q\log^2 n)$，总复杂度$O((n+q)\log^2 n)$。

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
struct istream{
	char buf[23333333],*s;
	inline istream(){
		buf[fread(s=buf,1,23333330,stdin)]='\n';
		fclose(stdin);
	}
	inline istream&operator>>(int&d){
		for(d=0;!isdigit(*s);++s);
		while(isdigit(*s))d=(d<<3)+(d<<1)+(*s++^'0');
		return*this;
	}
}cin;
struct ostream{
	char buf[8000005],*s;
	ostream(){s=buf;}
	inline ostream&operator<<(int d){
		if(!d){*s++='0';}else{
			int w=1;
			while(w<=d)w*=10;
			for(;w/=10;d%=w)*s++=d/w^'0';
		}
		return*this;
	}
	inline ostream&operator<<(const char&c){*s++=c;return*this;}
	void flush(){fwrite(buf,1,s-buf,stdout);s=buf;}
	~ostream(){flush();}
}cout;
const int N=500005;
struct base{
	int s[20];
	inline void ins(int p){
		if(p)
		for(int i=19;~i;--i)
		if(p>>i&1){
			if(!s[i]){s[i]=p;break;}
			p^=s[i];
		}
	}
	inline void clear(){memset(s,0,sizeof s);}
}d[N];
int merge(base a,base b){
	for(int i=19;~i;--i)a.ins(b.s[i]);
	int ret=0;
	for(int i=19;~i;--i)
	if((ret^a.s[i])>ret)ret^=a.s[i];
	return ret;
}
int a[N],n,q[N],qL[N],qR[N],ans[N],m;
void solve(int l,int r,int L,int R){
	if(L>R)return;
	if(l==r){
		for(int i=L;i<=R;++i)ans[q[i]]=a[l];return;
	}
	static int tmpL[N],tmpR[N];int tL=0,tR=0;const int mid=l+r>>1;
	d[mid].clear();d[mid].ins(a[mid]);
	for(int i=mid-1;i>=l;--i)(d[i]=d[i+1]).ins(a[i]);
	for(int i=mid+1;i<=r;++i)(d[i]=d[i-1]).ins(a[i]);
	for(int i=L;i<=R;++i)
	if(qL[q[i]]<=mid){
		if(qR[q[i]]>mid)ans[q[i]]=merge(d[qL[q[i]]],d[qR[q[i]]]);else
		tmpL[++tL]=q[i];
	}else tmpR[++tR]=q[i];
	for(int i=1;i<=tL;++i)q[L+i-1]=tmpL[i];
	for(int i=1;i<=tR;++i)q[L+tL+i-1]=tmpR[i];
	solve(l,mid,L,L+tL-1);
	solve(mid+1,r,L+tL,L+tL+tR-1);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;++i)cin>>qL[i]>>qR[i],q[i]=i;
	solve(1,n,1,m);
	for(int i=1;i<=m;++i)cout<<ans[i]<<'\n';
	return 0; 
}
```

---

## 作者：chenxia25 (赞：7)

~~什么是前缀线性基，爬罢~~

首先有个显然的线段树和 st 表维护线性基的做法。前者是预处理 2log 询问 3log，后者是预处理 3log 询问 2log 都过不了。它明显 2log 都不想让你过了。考虑发明一个 1log 的做法。

考虑把询问离线下来，按照 $r$ 分类，扫描线，时刻维护对每个 $l$ 的 $[l,r]$ 线性基。

线性基有个跟 gcd 很相似的概念：从一处往右扩展，相等段的数量是 log 的。原理也跟 gcd 差不多，一开始线性基大小为 $0$，往右移一格就可能加一或者大小不变。大小不变说明没插进去，那就整个都没变了。

那就时刻维护对当前 $r$ 的关于 $l$ 的 log 个线性基相等段。考虑 $r$ 右移一位的更新？新加一个 $([r,r],\varnothing)$ 相等段，然后把 $a_r$ 插进前面 log 个相等段。我们需要合并新的大小相同的线性基的相等段，这样才能保证以后一直都是 log 段。但是要知道一个集合的线性基（仅化为阶梯型）与插入顺序有关。而上述操作显然都是从左往右插入的，而只有从右往左插入才能保证大小相同的线性基相同。但其实一点关系都没有，因为生成空间相等……根据的是一个（有限维）线性空间的等维子空间只有本身。那就随便选一个线性基就好啦。

那这样是 2log 的，瓶颈在于每次都要试图插入 log 次。其实对固定的 $r$，插入的成功性是单调的，必定是连续段序列的一个后缀。那如果到第一个失败就 `break`，那其实成功插入的复杂度可以由势能支付掉，因为每个位置最多插入成功（大小增加）log 次，那么总共 2log，一次插入 log，总复杂度就是 3log，前面不乘以 $n$​ 相当于常数。而每个位置只会失败一次，所以总复杂度 1log。这样一来合并也不用写的那么精细，因为合并次数也能由势能支付掉，随便暴力枚举可合并相邻对就行了 `vector` 的 `erase` 也随便用，不用管那么多。

~~（但是好像跑得很慢，我好菜啊）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=500010;
int n,qu;
int a[N];
vector<pair<int,int> > qry[N];
struct base{
	int sz,b[30];
	base(){sz=0;memset(b,0,sizeof(b));}
	void insert(int x){
		for(int i=20;~i;i--)if(x>>i&1)
			if(b[i])x^=b[i];
			else{sz++,b[i]=x;break;}
	}
	int ask(){
		int res=0;
		for(int i=20;~i;i--)if(!(res>>i&1))res^=b[i];
		return res;
	}
};
vector<pair<pair<int,int>,base> > v;
int ans[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	cin>>qu;
	for(int i=1;i<=qu;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		qry[r].pb(mp(l,i));
	}
	for(int i=1;i<=n;i++){
		v.pb(mp(mp(i,i),base()));
		for(int j=v.size()-1;~j;j--){
			int sz=v[j].Y.sz;
			v[j].Y.insert(a[i]);
			if(v[j].Y.sz==sz)break;
		}
		while(true){
			bool flg=false;
			for(int j=0;j+1<v.size();j++)if(v[j].Y.sz==v[j+1].Y.sz){
				flg=true;
				int r=v[j+1].X.Y;
				v.erase(v.begin()+j+1);
				v[j].X.Y=r;
				break;
			}
			if(!flg)break;
		}
		for(int j=0;j<qry[i].size();j++)for(int k=0;k<v.size();k++)
			if(v[k].X.X<=qry[i][j].X&&qry[i][j].X<=v[k].X.Y)ans[qry[i][j].Y]=v[k].Y.ask();
	}
	for(int i=1;i<=qu;i++)printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：peterwuyihong (赞：6)

题意：给定一个数列，每次询问一个区间中选取一些数的异或最大值，可以离线，$n\le 5\times10^5$。

显然 $3\log$ 跑不过去，考虑 $2\log$ 做法。

思考一种神秘的对整体二分的做法。

对值域 $[1,n]$ 二分，记录 $mid=\lfloor\frac{1+n}{2}\rfloor$，把 $r$ 小于 $mid$ 的询问分到左边，把 $l$ 大于 $mid$ 的询问分到右边，再处理掉经过 $mid$ 的询问，对于这一个的处理，可以记录从 $mid$ 开始的前缀线性基和后缀线性基，这样复杂度一层就是 $O(n\log n)$ 总时间复杂度就是 $O(n\log^2n)$。

现在是 $21:20$，我看我什么时候写完。

现在是 $21:39$，我写完了。

```cpp
#define maxn 500010
struct xxj{
	#define Maxbit 21
	#define _Tp int
	_Tp p[Maxbit+1];
	void insert(_Tp x){
	  if(!x)return;
		for(int i=Maxbit;i+1;i--){
			if(!(x>>i))continue;
			if(!p[i]){p[i]=x;break;}
			x^=p[i];
		}
	}
	void clear(){memset(p,0,sizeof p);}
	void insert(xxj h){for(int i=0;i<=Maxbit;i++)insert(h.p[i]);}
	_Tp ask(){
		_Tp ans=0;
		for(int i=Maxbit;i+1;i--)
		if((ans^p[i])>ans)ans^=p[i];
		return ans;
	}
}st[maxn];
int n,m;
int a[maxn];
struct prpr{
	int l,r,id;
}q[maxn],tmpl[maxn],tmpr[maxn];
int Ans[maxn];
int work(xxj a,xxj b){
	return a.insert(b),a.ask();
}
void solve(int l,int r,int L,int R){
	if(L>R)return;
	if(l==r){
		for(int i=L;i<=R;i++)Ans[q[i].id]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	st[mid].clear();
	st[mid].insert(a[mid]);
	for(int i=mid-1;i>=l;i--)st[i]=st[i+1],st[i].insert(a[i]);
	for(int i=mid+1;i<=r;i++)st[i]=st[i-1],st[i].insert(a[i]);
	int ll=0,rr=0;
	for(int i=L;i<=R;i++){
		if(q[i].r<mid)tmpl[++ll]=q[i];
		else if(q[i].l>mid)tmpr[++rr]=q[i];
		else Ans[q[i].id]=work(st[q[i].l],st[q[i].r]);
	}
	for(int i=1;i<=ll;i++)q[L+i-1]=tmpl[i];
	for(int i=1;i<=rr;i++)q[L+ll+i-1]=tmpr[i];
	solve(l,mid,L,L+ll-1);
	solve(mid+1,r,L+ll,L+ll+rr-1);
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n;for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;for(int i=1;i<=m;i++)cin>>q[i].l>>q[i].r,q[i].id=i;
	solve(1,n,1,m);
	for(int i=1;i<=m;i++)cout<<Ans[i]<<endl;
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
合并时千万要把两个线性基合并起来再计算，不能不合并，like this
```cpp
int ans=0;
for(int i=21;i+1;i--)if((ans^a.p[i])>ans)ans^=a.p[i];
for(int i=21;i+1;i--)if((ans^b.p[i])>ans)ans^=b.p[i];
return ans;
```

---

## 作者：whiteqwq (赞：3)

[CF1100F Ivan and Burgers](https://www.luogu.com.cn/problem/CF1100F)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1751553)

## 题意
- 给定长度为$n$的序列$c$，$q$次询问，每次求$l$到$r$选取任意个数异或和最大是多少。
- 数据范围：$1\leqslant n,m\leqslant 5\times 10^5,1\leqslant c_i\leqslant 10^6$。

## 分析
这道题的测试点数是真的多。。。

一道[猫树分治](https://immortalco.blog.uoj.ac/blog/2102)+线性基题。

猫树分治的操作：从区间$[l,r]$中选一个分治中点$mid$，预处理$[l,mid]$的信息，预处理$[mid,r]$的信息，然后对所有跨越了$mid$的询问快速合并，不经过$mid$直接向子区间分治。

这道题我们可以直接把询问离线，然后上猫树分治。

具体地，我们用$O(\log c)$的暴力预处理$[a,mid]$和$[mid,b]$的线性基（其中$a\in[l,mid],b\in[mid,r]$），然后在合并的时候用$O(\log^2 c)$的暴力合并跨越$mid$的两个线性基。

总复杂度：$O(n\cdot\log n\cdot \log c+q\cdot\log^2 c)$。

## 代码
```
#include<stdio.h>
const int maxn=500005,maxm=500005,maxk=31;
int n,m;
int a[maxn],ans[maxm];
struct question{//询问
	int l,r,id;
}q[maxm],tmp1[maxm],tmp2[maxm];
struct base{//线性基
	int p[maxk];
	void clear(){
		for(int i=0;i<maxk;i++)
			p[i]=0; 
	}
}b[maxn];
void insert(base &now,int x){//线性基插入
	for(int i=30;i>=0;i--){
		if(((x>>i)&1)==0)
			continue;
		if(now.p[i]==0){
			now.p[i]=x;
			return ;
		}
		x^=now.p[i];
	}
}
base merge(base a,base b){//线性基合并
	for(int i=0;i<=30;i++)
		if(b.p[i])
			insert(a,b.p[i]);
	return a;
}
int getmax(base x){//线性基求异或最大值
	int res=0;
	for(int i=30;i>=0;i--)
		if((res^x.p[i])>res)
			res^=x.p[i];
	return res;
}
void solve(int l,int r,int ql,int qr){//猫树分治
	if(ql>qr)
		return ;
	if(l==r){
		for(int i=ql;i<=qr;i++)
			ans[q[i].id]=a[l];
		return ;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
	b[mid].clear(),insert(b[mid],a[mid]);
	for(int i=mid-1;i>=l;i--)
		b[i]=b[i+1],insert(b[i],a[i]);
	for(int i=mid+1;i<=r;i++)
		b[i]=b[i-1],insert(b[i],a[i]);
	for(int i=ql;i<=qr;i++){//合并左右预处理过的线性基
		if(l<=q[i].l&&q[i].l<=mid&&mid+1<=q[i].r&&q[i].r<=r){
			ans[q[i].id]=getmax(merge(b[q[i].l],b[q[i].r]));
			continue;
		}
		if(q[i].l<=mid&&q[i].r<=mid)
			tmp1[++cnt1]=q[i];
		else tmp2[++cnt2]=q[i];
	}
	for(int i=1;i<=cnt1;i++)
		q[ql+i-1]=tmp1[i];
	for(int i=1;i<=cnt2;i++)
		q[ql+cnt1+i-1]=tmp2[i];
	solve(l,mid,ql,ql+cnt1-1),solve(mid+1,r,ql+cnt1,ql+cnt1+cnt2-1);//分治解决子问题
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	solve(1,n,1,m);
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：FxorG (赞：2)

## $\text{Solution:}$

首先看到异或和最大立马想到线性基，然而 $[l,r]$ 就很烦。

我们发现线性基是能够合并的，想到猫树分治维护即可。

维护 $[l,mid]$ 的后缀线性基以及 $[mid+1,r]$ 的前缀线性基，对于询问判断是否跨过两边即可。

设 $q=n$ ，复杂度 $O(n \log^2 n)$。

需要注意的是，merge 不能传参！

## $\text{Code:}$

```cpp
#include <bits/stdc++.h>

#define N (int)(5e5+5)

using namespace std;
int rd() {int f=1,sum=0; char ch=getchar();while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}return sum*f;}
struct ques {
	int l,r;
}q[N];

int a[N],p[N],ans[N],n,m;

struct node {
	int d[22];
	void clr() {
		memset(d,0,sizeof(d));
	}
	void ins(int x) {
		for(int i=20;i>=0;i--) {
			if((x>>i)&1) {
				if(d[i]) x^=d[i];
				else {
					d[i]=x; break;
				}
			}
		}
	}
	int qry() {
		int res=0;
		for(int i=20;i>=0;i--) {
			if((res^d[i])>res) res^=d[i];
		}
		return res;
	}
}g[N];

int merge(node x,node y) {
	for(int i=20;i>=0;i--) x.ins(y.d[i]);
	return x.qry();
}

int tmp[N];
void solve(int l,int r,int L,int R) {
	if(L>R) return;
	int mid=(l+r)>>1,t1=L-1,t2=0;
	g[mid].clr(); g[mid].ins(a[mid]);
	//cout<<g[mid].qry()<<endl;
	for(int i=mid+1;i<=r;i++) (g[i]=g[i-1]).ins(a[i]);
	for(int i=mid-1;i>=l;i--) (g[i]=g[i+1]).ins(a[i]);
	for(int i=L,x;i<=R;i++) {
		x=p[i];
		if(q[x].r<=mid) p[++t1]=x;
		else if(q[x].l>mid) tmp[++t2]=x;
		else {
			ans[x]=merge(g[q[x].l],g[q[x].r]); 
		}
	}
	for(int i=1;i<=t2;i++) p[t1+i]=tmp[i];
	solve(l,mid,L,t1); solve(mid+1,r,t1+1,t1+t2);
}

int main() {
	n=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	m=rd();
	int tot=0;
	for(int i=1;i<=m;i++) {
		q[i]=ques{rd(),rd()};
		if(q[i].l==q[i].r) ans[i]=a[q[i].l];
		else p[++tot]=i;
	}
	solve(1,n,1,tot);
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：qiyue7 (赞：0)

给出一个基于前缀线性基和线段树的做法（离线）

首先我们注意到，线性基合并的复杂度log^2n,这里复杂度没有很好的优化空间，那么我们就考虑能不能优化一下减少合并次数。考虑线段树的结构，我们可以观察到每一个非叶节点一定会在某个节点被分割为当前节点的mid的前后缀，那么我们通过先把所有的询问的分解，L==R的询问直接回答，dfs线段树对每个节点做前后缀线性基，然后只用一次合并就可以离线回答询问（可以在线，但是空间肯定不够）。

具体细节看代码。


AC代码：复杂度O((n+q)*log^2n)（CF的评测机是真的快。。。n=q=500000而且完全跑满复杂度的代码  最大的case跑完只用了1.1s）



```cpp

const int sigma = 20;
struct Base
{
	array<int, sigma + 1> d;
	int base = 1, cntp;
	int addtag;
	Base()
	{
		addtag = 1;
		d.fill(0);
	}
	void add(int x)
	{
		for (int i = sigma; i >= 0; i--)
		{
			if (x&(base << i))
			{
				if (d[i])
					x ^= d[i];
				else
				{
					d[i] = x;
					return;
				}
			}
		}
		addtag = 0;
	}
	int MAX()
	{
		int anss = 0;
		for (int i = sigma; i >= 0; i--)
			if ((anss^d[i]) > anss)anss ^= d[i];
		return anss;
	}
};
array<int, 510000> arr, ans;
struct node2
{
	node2 *L, *R;
	int l, r;
	list<tuple<int, int, int>> query;
};
node2 *root;
void build_root(int L, int R)
{
	root = new node2();
	root->l = L, root->r = R;
}
void pl(node2 *a)
{
	if ((a->L != NULL) || (a->l == a->r))
		return;
	int mid = (a->l + a->r) / 2;
	a->L = new node2();
	a->L->l = a->l, a->L->r = mid;
}
void pr(node2 *a)
{
	if ((a->R != NULL) || (a->l == a->r))
		return;
	int mid = (a->l + a->r) / 2;
	a->R = new node2();
	a->R->l = mid + 1, a->R->r = a->r;
}
void update(node2 *p)
{
	if (p->l == p->r)
		return;
}
int kk, vall;
void build(node2 *x)
{
	pl(x), pr(x);
	if (x->l == x->r)
	{
		return;
	}
	else
		build(x->L), build(x->R);
	update(x);
}
int se1;
node2 *segment[50];
void split(node2 *p, int l, int r, int k)
{
	int mid = (p->l + p->r) / 2;
	if (l <= mid && r > mid)
	{
		p->query.push_back({ l,r,k });
	}
	else if (r <= mid)
		split(p->L, l, r, k);
	else if (l >= mid + 1)
		split(p->R, l, r, k);
}
Base b[510000], b2;
void dfs(node2 *p2)
{
	if (p2->l == p2->r)
		return;
	int mid = (p2->l + p2->r) / 2;
	b[mid].d.fill(0);
	b[mid].add(arr[mid]);
	b[mid + 1].d.fill(0);
	b[mid + 1].add(arr[mid + 1]);
	for (int i = mid - 1; i >= p2->l; --i)
	{
		b[i].d = b[i + 1].d;
		b[i].add(arr[i]);
	}
	for (int i = mid + 2; i <= p2->r; ++i)
	{
		b[i].d = b[i - 1].d;
		b[i].add(arr[i]);
	}
	while (!p2->query.empty())
	{
		auto it = p2->query.back();
		p2->query.pop_back();
		b2.d = b[get<0>(it)].d;
		for (int i = sigma; i >= 0; --i)
			b2.add(b[get<1>(it)].d[i]);
		ans[get<2>(it)] = b2.MAX();
	}
	dfs(p2->L), dfs(p2->R);
}
int32_t main()
{
	int n, m, val, l, r;
	io >> n;
	build_root(1, n);
	build(root);
	for (int i = 1; i <= n; ++i)
		io >> arr[i];
	io >> m;
	for (int i = 1; i <= m; ++i)
	{
		io >> l >> r;
		if (l != r)
			split(root, l, r, i);
		else
			ans[i] = arr[l];
	}
	dfs(root);
	for (int i = 1; i <= m; ++i)
		io << ans[i] << endl;
	return 0;
}
```


---

