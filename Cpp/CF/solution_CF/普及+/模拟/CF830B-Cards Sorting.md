# Cards Sorting

## 题目描述

Vasily has a deck of cards consisting of $ n $ cards. There is an integer on each of the cards, this integer is between $ 1 $ and $ 100000 $ , inclusive. It is possible that some cards have the same integers on them.

Vasily decided to sort the cards. To do this, he repeatedly takes the top card from the deck, and if the number on it equals the minimum number written on the cards in the deck, then he places the card away. Otherwise, he puts it under the deck and takes the next card from the top, and so on. The process ends as soon as there are no cards in the deck. You can assume that Vasily always knows the minimum number written on some card in the remaining deck, but doesn't know where this card (or these cards) is.

You are to determine the total number of times Vasily takes the top card from the deck.

## 说明/提示

In the first example Vasily at first looks at the card with number $ 6 $ on it, puts it under the deck, then on the card with number $ 3 $ , puts it under the deck, and then on the card with number $ 1 $ . He places away the card with $ 1 $ , because the number written on it is the minimum among the remaining cards. After that the cards from top to bottom are $ [2,6,3] $ . Then Vasily looks at the top card with number $ 2 $ and puts it away. After that the cards from top to bottom are $ [6,3] $ . Then Vasily looks at card $ 6 $ , puts it under the deck, then at card $ 3 $ and puts it away. Then there is only one card with number $ 6 $ on it, and Vasily looks at it and puts it away. Thus, in total Vasily looks at $ 7 $ cards.

## 样例 #1

### 输入

```
4
6 3 1 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
1
1000
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
3 3 3 3 3 3 3
```

### 输出

```
7
```

# 题解

## 作者：Acc_Robin (赞：3)

> 能用树状数组为什么还要用线段树呢？

这是一篇不需要线段树的题解。

考虑优化暴力，对每一个数开桶，存下来它每一次出现的位置，为了方便，把 $x$ 第一次和最后一次出现的位置用 $l[x]$ 和 $r[x]$ 表示。

开一个树状数组来标记每个位置的数字是否还存在，一开始全部赋值为 $1$。

按值域从小到大遍历，用一个变量 $p$ 来作为模拟的指针，如果对于一个数 $x$：

- $p\le l[x]$

说明 $p$ 只需要接着向右移动到 $r[x]$ 即可，这一步对答案的贡献就是树状数组上查询 $p+1\sim r[x]$。

- $p>l[x]$

说明 $p$ 需要向右一直走到序列尾，再从头开始走到 $x$ 在 $p$ 之前出现的最后一个位置。

那么我们可以二分出这个位置，记为 $q$，那么 $p$ 应该移动到 $q$，这一步对答案的贡献就是树状数组上查询 $p+1\sim n$ 再加上 $1\sim q$。

处理完一个数字之后，在树状数组上给这个数字的所有出现位置都减一。

总复杂度（将值域与 $n$ 视为同阶）：$O(n\log n)$。

注意一些小细节，在代码中已经标注了：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
#define int long long
#define id second
	const int N=1e5+10;
	pair<int,int>a[N];
	int n,z=1,l[N],r[N],p=1,m;//z是答案，初始为 1 的原因是最后一个数的贡献没有算
	basic_string<int>v[N];
	struct BIT{
		int t[N];
		void add(int x,int k){for(int i=x;i<=n;i+=i&-i)t[i]+=k;}
		int pre(int x){int r=0;for(int i=x;i;i-=i&-i)r+=t[i];return r;}
		int ask(int l,int r){return l>r?0:pre(r)-pre(l-1);}
		void bd(){for(int i=1,j;i<=n;i++)if(t[i]++,(j=i+(i&-i))<=n)t[j]+=t[i];}//树状数组O(n)建树，虽然没什么用
	}t;
	void work(){
		cin>>n,t.bd(),memset(l,0x3f,sizeof l);
		for(int i=1,x;i<=n;i++)cin>>x,a[i]={x,i},v[x]+=i,l[x]=min(l[x],i),r[x]=max(r[x],i),m=max(m,x);
		for(int i=1,q;i<=m;i++)if(v[i].size()){
			if(sort(v[i].begin(),v[i].end()),p>l[i]){
				if((q=lower_bound(v[i].begin(),v[i].end(),p)-v[i].begin()))q--;//查前驱记得特判
				z+=t.ask(p+1,n)+t.ask(1,v[i][q]),p=v[i][q];
			}else z+=t.ask(p+1,r[i]),p=r[i];
			for(int j:v[i])t.add(j,-1);
		}
		cout<<z<<'\n';
	}
#undef int
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：xxr___ (赞：2)

### 题意简述：
有 $ N $ 个卡片你要每次判断是否为最小值，是则将其删除，否则将其放到队尾。
### 思路：
用一个集合记录，因为`set`是升序排序的,所以每次取出堆顶元素,也就是最小值跟每个元素比较一下,复杂度是 $ O( N \log N ) $ 可行。
### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010];
set<int>st[100010];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		st[a[i]].insert(i);
	}
	sort(a+1,a+n+1);
	int pos=1;
	long long ans=n;
	for(int i=1;i<=n;i++){
		auto it=st[a[i]].lower_bound(pos);
		if(it==st[a[i]].end()){
			ans+=n-i+1;
			pos=1;
			it=st[a[i]].lower_bound(pos);
		}
		pos=*it;
		st[a[i]].erase(it);
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：2018ljw (赞：2)

智商不够，DS 来凑。

观察我们的操作：若不为全局最小值，那么放到序列末尾；若为全局最小值，那么删去。

不难发现，这个操作可以等价于找到第一个全局最小值，删掉这个位置并把前面的序列放到最后，代价为这个最小值在当前序列中的下标。

找最小和删除是非常好搞的，比较难处理的是序列移动和统计贡献。

正常一点的做法是序列复制后线段树维护，但毕竟还是有些细节的，脑子不够。

又刚好是序列操作，所以我们不妨 splay 维护序列。对每个点，维护其子树大小和子树中，最小值位置对应的最小的节点编号。

这样找最小、统计贡献就很显然了，一个是根节点信息一个是排名。

考虑移动操作，假设最小值位置为 $x$。

先把 $x$ 转到根节点，那么根据中序遍历的性质可知，左子树就是 $x$ 前的序列。从根一直往右跳直至某个点右子节点为空，直接把整个树接到这个点的右儿子上就行。

再考虑删除，此时根节点已经没有左子树了，直接把根节点变成它的右儿子就行。

```cpp
#include<cstdio>
#define ls(x) tre[x].son[0]
#define rs(x) tre[x].son[1]
int n,rt,cnt,a[100001];
long long res;
struct splay{
	int son[2],fa;
	int sz,ps;
}tre[100001];
bool fx(int x){
	return rs(tre[x].fa)==x;
}
void pushup(int x){
	tre[x].sz=tre[ls(x)].sz+tre[rs(x)].sz+1;
	tre[x].ps=x;
	if(a[tre[ls(x)].ps]<=a[x])tre[x].ps=tre[ls(x)].ps;
	if(a[tre[rs(x)].ps]<a[tre[x].ps])tre[x].ps=tre[rs(x)].ps;
}
void rotate(int x){
	int y=tre[x].fa,z=tre[y].fa,p=fx(x)^1;
	if(z)tre[z].son[fx(y)]=x;
	tre[tre[x].son[p]].fa=y;
	tre[y].fa=x;
	tre[x].fa=z;
	tre[y].son[p^1]=tre[x].son[p];
	tre[x].son[p]=y;
	pushup(y);
	pushup(x);
}
void splay(int x,int to){
	while(tre[x].fa!=to){
		int y=tre[x].fa,z=tre[y].fa;
		if(z)fx(x)==fx(y)?rotate(y):rotate(x);
		rotate(x);
	}
	if(!to)rt=x;
}
void insert(){
	if(!rt){
		rt=++cnt;
		tre[1].sz=1;
		tre[1].ps=1;
		return;
	}
	int x=rt,k=++cnt;
	while(rs(x))x=rs(x);
	tre[k].fa=x;
	tre[x].son[1]=k;
	pushup(k);pushup(x);
	splay(k,0);
}
void del(int x){
	splay(x,0);
	res+=tre[ls(x)].sz+1;
	if(!rs(x)){
		tre[ls(x)].fa=0;
		rt=ls(x);
		pushup(rt);
		return;
	}
	int k=x;
	while(rs(k))k=rs(k);
	rs(k)=ls(x);
	tre[ls(x)].fa=k;
	pushup(k);
	tre[rs(x)].fa=0;
	rt=tre[rs(x)].fa;
	splay(k,0);
}
int main(){
	int i,n;
	scanf("%d",&n);
	a[0]=998244353;
	for(i=1;i<=n;i++)scanf("%d",&a[i]),insert();
	for(i=1;i<=n;i++)del(tre[rt].ps);
	printf("%lld",res);
}
```

---

## 作者：CaiXY06 (赞：2)

看到大家都是数据结构的做法，那我就来篇不一样的吧。

我们观察到 $a_i\leq 10^5$，所以我们可以对于所有值记录下其在 $a$ 中出现的位置，然后从小到大枚举数值进行暴力跳位置以及运算。具体实现我们可以使用**链表**或者 **set**。时间复杂度：采用链表的话是 $O(n)$ 的，**set** 是 $O(n\log n)$ 的。这里我们采用 **set**（毕竟写写方便不是么）。详细请见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010];
set<int>S[100010];//开1e5个set存下每个值出现的位置
set<int>::iterator it;//指针
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		S[a[i]].insert(i);//插入位置
	}
	sort(a+1,a+n+1);//将数值从小到大排序，免去枚举无值的set
	int p=1;long long ans=n;//p记录当前在a中的位置
	for(int i=1;i<=n;i++){
		it=S[a[i]].lower_bound(p);//二分查找当前数值第一个出现在p之后的位置
		if(it==S[a[i]].end())ans+=n-i+1,p=1,it=S[a[i]].lower_bound(p);//如果当前数值已经没有在p之后的，就从头重新找
		p=*it,S[a[i]].erase(it);
	}
	printf("%lld",ans);
	return 0;
} 
```




---

## 作者：C_Zn (赞：2)

[题目传送门](https://codeforces.com/problemset/problem/830/B)
### 题意
你有一个长度为 $n$ 个队列，你每次取出这个队列的队首，如果这个数是队列中最小的数那么就把他丢掉，否则就放在队列的队尾。
### 解题方法
我们首先就想到了暴力的做法，每次枚举第一个然后扔到后面去，复杂度是$o(n^2)$的，发现根本过不了，于是我们就要想到一些优化，我们发现这个队列就和一个环一样，所以我们先把原来的$a$数组复制一遍，因为我们每次取出下一个被扔走的数一定是在$[last+1,last+n-1]$这个区间内的，我们就就可以直接用线段树求出这个最小值得位置就可以了，取出这个数以后就把这个位置和位置$+n$的值都变成一个很大数，然后我们该怎么样统计答案呢？答案不能是简单的现在的位置减去上去的位置，因为当中有些数已经被扔出去了，不能再重复计数了，我们就再开一个数据结构，查询$[last+1,now-1]$中有多少数已经出去了，对于每次扔出去的数我们在那个位置和那个位置$+n$的地方都变成1，就可以解决了。
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[200500];
int n;
struct node
{
	int l,r;
	int minn,pos;
	friend node operator + (node x,node y)
	{
		node lans;
		if(x.minn<=y.minn)
		{
			lans.minn=x.minn;
			lans.pos=x.pos;
		}
		else
		{
			lans.minn=y.minn;
			lans.pos=y.pos;
		}
		return lans;
	} 
}t[200500<<2];
void pushup(int rt)
{
	if(t[rt<<1].minn<=t[rt<<1|1].minn)
	{
		t[rt].minn=t[rt<<1].minn;
		t[rt].pos=t[rt<<1].pos;
	}
	else
	{
		t[rt].minn=t[rt<<1|1].minn;
		t[rt].pos=t[rt<<1|1].pos;
	}
}
void build(int rt,int l,int r)
{
	t[rt].l=l;
	t[rt].r=r;
	if(l==r)
	{
		t[rt].minn=a[l];
		t[rt].pos=l;
		return;
	}
	int mid=l+r>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
	return;
}
void change(int rt,int x,int d)
{
	if(t[rt].l==t[rt].r&&t[rt].l==x)
	{
		t[rt].minn=d;
		return;
	}
	int mid=t[rt].l+t[rt].r>>1;
	if(x<=mid)change(rt<<1,x,d);
	else change(rt<<1|1,x,d);
	pushup(rt);
}
node query(int rt,int l,int r)
{
	if(t[rt].l>=l&&t[rt].r<=r)
	{
		node lans;
		lans.minn=t[rt].minn;
		lans.pos=t[rt].pos;
		return lans;
	}
	int mid=t[rt].l+t[rt].r>>1;
	node lans;
	if(l<=mid)
	{
		lans=query(rt<<1,l,r);
		if(mid<r)
		  lans=lans+query(rt<<1|1,l,r);
	}
	else
	{
		if(mid<r)
		  lans=query(rt<<1|1,l,r);
	}
	return lans;
}
int c[1000000];
int lowbit(int x)
{
	return x&(-x);
} 
int update(int x,int v)
{
	while(x<=2*n)
	{
		c[x]+=v;
		x+=lowbit(x);
	}
}
int sum(int x)
{
	int res=0;
	while(x>0)
	{
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
} 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&a[i]),a[n+i]=a[i];
	build(1,1,2*n);
	int last=0;
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		node lans;
		if(i==1)
		{
			lans=query(1,1,n);
		}
		else 
	 	    lans=query(1,last+1,n+last-1);
	 	int x=lans.pos;
	 	ans+=x-last-(sum(x)-sum(last));
	 	if(x>n)last=x-n;else last=x;
	 	change(1,last,1e7);change(1,last+n,1e7);
	 	update(last,1);update(last+n,1);
	}
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：DrAlfred (赞：0)

摘要：分块，树状数组，RMQ

[传送门：https://www.luogu.com.cn/problem/CF830B](https://www.luogu.com.cn/problem/CF830B)

## 题意

桌子上有 $n$ 张卡片排成一列，每张卡片上有一个数 $a_i$（$1\le a_i\le10^5,a_i\in \mathbf{Z}$）。

有一个人每次从卡片的最左端开始，依次向右看过去，如果当前这张牌是现在的全局最小值，那么将它移除，如果不是，那么将它放到序列的最右端。持续到序列为空为止。求他进行的这两种操作的总次数。

## 分析思路

来一个特别~~逗比~~的分块解法。（其实或许还可以线段树上二分但是我不会 QAQ）

记当前正在看的数的位置为 $cur$。如果我们把这个序列看做一个环，这个问题等价于：找到环上第一个仍然未被删除的在 $cur$ 右边的值最小的新位置 $pos$，然后加上 $cur$ 到 $pos$ 之间的距离。（话说这定语真是有点长）

环问题很容易让我们想到破环为链，然后查找 $[cur, cur + n - 1]$ 中的下标最小的最小值的位置，这个问题可以使用分块解决。

但是我们还需要维护一个删除操作，分块本身很难直接支持显式的删除操作，于是我们可以通过将 $a_{pos}$ 赋值为极大值并且暴力重构块的方式来在 $O\left(\sqrt n\right)$ 的时间复杂度内解决找到并且维护最小值信息的操作。

最后就是查询两个位置之间的距离，我们构造数组 $del_i$ 表示 $i$ 这个位置是否已经被删除，查询 $[l, r]$ 之间的距离等价于查询 $del_l, \cdots, del_r$ 中 $1$ 的个数，这一操作可以通过树状数组轻易地动态维护。

时间复杂度 $O\left(n \sqrt n + n \log n\right)$，~~喜提最劣解~~。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
template <class _Tp>
struct Fenwick {
    std::vector<_Tp> c;
    inline int lowbit(int x) { return x & -x; }
    inline void merge(_Tp &x, _Tp y) { x = x + y; } // remember to modify
    inline _Tp subtract(_Tp x, _Tp y) { return x - y; }
    inline void update(size_t pos, _Tp x) {
        for (pos++; pos < c.size(); pos += lowbit(pos)) merge(c[pos], x);
    }
    inline void clear(void) {
        for (auto &x : c) x = _Tp();
    }
    inline _Tp query(size_t pos) {
        _Tp ans = _Tp();
        for (pos++; pos; pos ^= lowbit(pos)) merge(ans, c[pos]);
        return ans;
    }
    inline _Tp query(size_t l, size_t r) {
        return subtract(query(r), query(l - 1));
    }
    Fenwick(size_t len) : c(len + 2) {}
};
Fenwick<int> C(N);
int n, m, B, a[N], bel[N], mn[450];
inline void update(int &x, int y) {
    if (a[y] < a[x]) x = y;
}
inline void remake(int b) {
    mn[b] = b * B;
    for (int i = b * B; bel[i] == b; i++) {
        update(mn[b], i);
    }
}
// 找到 [l, r] 以内下标最小的最小值
inline int query(int l, int r) {
    int L = bel[l], R = bel[r], res = l;
    if (L == R) {
        for (int i = l; i <= r; i++) update(res, i);
        return res;
    }
    for (int i = l; bel[i] == L; i++) update(res, i);
    for (int i = L + 1; i < R; i++) update(res, mn[i]);
    for (int i = R * B; i <= r; i++) update(res, i);
    return res;
}
inline void remove(int x) {
    x %= n;
    for (int i = 0; i < 2; i++, x += n) {
        C.update(x, -1), a[x] = 1e9, remake(bel[x]);
    }
}
int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n, m = 2 * n, B = sqrt(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i], a[i + n] = a[i];
    }
    for (int i = 0; i < m; i++) {
        C.update(i, 1), bel[i] = i / B;
    }
    for (int i = 0; i <= (m - 1) / B; i++) {
        remake(i);
    }
    long long cur = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        int pos = query(cur, cur + n - 1);
        ans += C.query(cur, pos);
        remove(pos), cur = pos % n;
    }
    cout << ans << '\n';
    return 0;
}
```

---

