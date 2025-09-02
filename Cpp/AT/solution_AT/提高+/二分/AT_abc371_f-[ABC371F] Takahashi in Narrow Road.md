# [ABC371F] Takahashi in Narrow Road

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc371/tasks/abc371_f

東西に続く道があり、道の上には $ N $ 人の高橋くんがいます。 道は原点と呼ばれる点から東西に十分長く続いています。

$ i $ 番目 $ (1\leq\ i\leq\ N) $ の高橋くんは、はじめ原点から東に $ X\ _\ i $ メートル進んだところにいます。

高橋くんたちは道の上を東西に動くことができます。 具体的には、次の移動を好きなだけ行うことができます。

- 高橋くんを一人選ぶ。**移動する先に他の高橋くんがいない場合**、選んだ高橋くんを $ 1 $ メートル東に、もしくは西に移動させる。

高橋くんたちには合計 $ Q $ 個の用事があり、$ i $ 個目 $ (1\leq\ i\leq\ Q) $ の用事は次の形式で表されます。

- $ T\ _\ i $ 番目の高橋くんが座標 $ G\ _\ i $ に到着する。

$ Q $ 個の用事を先頭から順にすべて完了するために必要な移動回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10\ ^\ 5 $
- $ 0\leq\ X\ _\ 1\lt\ X\ _\ 2\lt\dotsb\lt\ X\ _\ N\leq10\ ^\ 8 $
- $ 1\leq\ Q\leq2\times10\ ^\ 5 $
- $ 1\leq\ T\ _\ i\leq\ N\ (1\leq\ i\leq\ Q) $
- $ 0\leq\ G\ _\ i\leq10\ ^\ 8\ (1\leq\ i\leq\ Q) $
- 入力はすべて整数

### Sample Explanation 1

高橋くんたちの最適な行動は以下のようになります（それぞれの高橋くんの座標は正確に描かれているとは限りません）。 !\[\](https://img.atcoder.jp/abc371/2ebef79b440e6dae3115bb518fccfb5f.png) それぞれの用事では、高橋くんたちは次のように移動しています。 - $ 4 $ 番目の高橋くんが $ 6 $ 回東に進み、$ 3 $ 番目の高橋くんが $ 15 $ 回東に進む。 - $ 2 $ 番目の高橋くんが $ 2 $ 回西に進み、$ 3 $ 番目の高橋くんが $ 26 $ 回西に進み、$ 4 $ 番目の高橋くんが $ 26 $ 回西に進む。 - $ 4 $ 番目の高橋くんが $ 18 $ 回東に進み、$ 3 $ 番目の高橋くんが $ 18 $ 回東に進み、$ 2 $ 番目の高橋くんが $ 18 $ 回東に進み、$ 1 $ 番目の高橋くんが $ 25 $ 回東に進む。 - $ 5 $ 番目の高橋くんが $ 13 $ 回東に進み、$ 4 $ 番目の高橋くんが $ 24 $ 回東に進み、$ 3 $ 番目の高橋くんが $ 24 $ 回東に進み、$ 2 $ 番目の高橋くんが $ 24 $ 回東に進む。 高橋くんたちの移動回数の合計は $ 21+54+79+85=239 $ 回となります。 移動回数の合計を $ 238 $ 回以下としてすべての用事を完了することはできないため、`239` を出力してください。

### Sample Explanation 2

途中で一部の高橋くんが原点より西側や、原点より $ 10\ ^\ 8+1 $ メートル以上東に進んだところに移動する必要がある場合があることに注意してください。 また、答えが $ 2\ ^\ {32} $ を超える場合があることに注意してください。

## 样例 #1

### 输入

```
5
10 20 30 40 50
4
3 45
4 20
1 35
2 60```

### 输出

```
239```

## 样例 #2

### 输入

```
8
0 1 2 3 4 5 6 100000000
6
1 100000000
8 0
1 100000000
8 4
1 100000000
5 21006578```

### 输出

```
4294967297```

## 样例 #3

### 输入

```
12
1558 3536 3755 3881 4042 4657 5062 7558 7721 8330 8542 9845
8
9 1694
7 3296
12 5299
5 5195
5 5871
1 2491
8 1149
8 2996```

### 输出

```
89644```

# 题解

## 作者：KSCD_ (赞：16)

### 思路
发现由于移动时不能让两人在同一位置，所以所有人的相对顺序不会改变，同时移动时若旁边已经有人，还可能需要带上别的人一起动。

考虑把相邻的人看成一个整块一起移动，初始每个人各为一个块，移动时暴力向目标方向走，接上下一个块就合成一个整块接着走，直到到达终点。

具体维护时可以在 set 中维护 $(p_i,x_i)$ 表示一个从 $p_i$ 开始的整块，此时 $p_i$ 的位置为 $x_i$。每个块的右端点和长度可以结合下一个块的左端点来计算，具体操作还是看代码实现吧。

时间复杂度上由于每次操作只可能从一个整块中分出一个含 $T_i$ 的小块，总块数不超过 $S=N+Q$，合并的次数不超过总块数，所以时间复杂度是 $O(S\log S)$ 的。
### 代码

```cpp
#include<iostream>
#include<set>
#define int long long
#define pii pair<int,int>
using namespace std; 
const int N=4e5+10;
const int inf=1e18;
int n,Q,res;
set <pii> s;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;i++) cin>>x,s.insert({i,x});
	s.insert({0,-inf}),s.insert({n+1,inf}),cin>>Q; // 处理边界 
	while(Q--)
	{
		int p,to; cin>>p>>to;
		pii te=*--s.upper_bound({p,inf}); s.erase(te); // p 所在的整块 
		int lp=te.first,lx=te.second,nowx=lx+(p-lp),nlp=(*s.upper_bound(te)).first; // lp 为左端点人的编号，lx 为位置 
		if(to<nowx) // 向左走 
		{
			if(p+1!=nlp) s.insert({p+1,nowx+1}),nlp=p+1; // 拆块 
			to-=(p-lp); //转化为左端点移动到的位置 
			while(lx!=to)
			{
				pii tt=*(--s.upper_bound({lp,lx})); // 左边的块 
				int tp=tt.first,tx=tt.second,lim=tx+(lp-tp),tto=max(to,lim);
				res+=(nlp-lp)*(lx-tto),lx=tto;  
				if(lx==lim) s.erase(tt),to-=(lp-tp),lp=tp,lx=tx; // 合并 
			}
		}
		else //向右走 
		{
			if(p!=lp) s.insert({lp,lx}),lp=p,lx=nowx; // 拆块 
			while(lx!=to)
			{
				pii tt=*(s.upper_bound({lp,lx})); // 右边的块 
				int np=tt.first,nx=tt.second,lim=nx-(np-lp),tto=min(to,lim);
				res+=(np-lp)*(tto-lx),lx=tto;
				if(lx==lim) s.erase(tt); // 合并 
			}
		}
		s.insert({lp,lx}); //把目前的块重新加入集合 
	}
	cout<<res;
	return 0;
}
```

---

## 作者：george0929 (赞：15)

**upd: 2024/9/18 修正了一些小错误。**

好不容易赛时做出 F，写篇题解纪念一下。

不难发现一次操作会让序列中一段数变为公差为 $1$ 的等差数列，处理这种问题的常用套路是将第 $i$ 个数减去 $i$，这样公差为 $1$ 的等差数列就会变为相同的一段数。

拿样例举个例子：

原始操作：

```
10 20 30 40 50
10 20 45 46 50
10 18 19 20 50
35 36 37 38 50
35 60 61 62 63
```

将第 $i$ 个数减去 $i$：

```
9 18 27 36 45
9 18 42 42 45
9 16 16 16 45
34 34 34 34 45
34 58 58 58 58
```

问题转换为每次将区间所有数修改为同一个值。

记将第 $i$ 个数减去 $i$ 所得序列为 $\{y\}$。若要将区间 $[l,r]$ 修改为 $v$，则对答案的贡献为 $|(\sum\limits_{i=l}^{r} y_i)-v\times (r-l+1)|$。

可以使用线段树维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int x[200005],ans;
struct node{
	int l,r,mx,sum,tg;
}t[800005];
void pushup(int p){
	t[p].mx=max(t[p*2].mx,t[p*2+1].mx);
	t[p].sum=t[p*2].sum+t[p*2+1].sum;
}
void pushdown(int p){
	if(t[p].tg==-1e18) return;
	int tmp=t[p].tg;
	t[p].tg=-1e18;
	t[p*2].tg=t[p*2+1].tg=tmp;
	t[p*2].mx=t[p*2+1].mx=tmp;
	t[p*2].sum=tmp*(t[p*2].r-t[p*2].l+1);
	t[p*2+1].sum=tmp*(t[p*2+1].r-t[p*2+1].l+1);
} 
void build(int p,int l,int r){
	t[p].l=l,t[p].r=r,t[p].tg=-1e18;
	if(l==r){
		t[p].mx=t[p].sum=x[l];
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	pushup(p);
}
void setv(int p,int l,int r,int v){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].sum=(t[p].r-t[p].l+1)*v;
		t[p].mx=t[p].tg=v;
		return;
	} 
	pushdown(p);
	int mid=(t[p].l+t[p].r)/2;
	if(mid>=l) setv(p*2,l,r,v);
	if(mid<r) setv(p*2+1,l,r,v);
	pushup(p);
}
int querymx(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r){
		return t[p].mx;
	}
	pushdown(p);
	int mid=(t[p].l+t[p].r)/2,mx=-1e18;
	if(mid>=l) mx=max(mx,querymx(p*2,l,r));
	if(mid<r) mx=max(mx,querymx(p*2+1,l,r));
	return mx;
}
int query(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r){
		return t[p].sum;
	}
	pushdown(p);
	int mid=(t[p].l+t[p].r)/2,sum=0;
	if(mid>=l) sum+=query(p*2,l,r);
	if(mid<r) sum+=query(p*2+1,l,r);
	return sum;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i];
		x[i]-=i;
	}
	build(1,1,n);
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		int t,g;
		cin>>t>>g;
		int tpos=query(1,t,t);
		if(tpos==g-t) continue;
		if(tpos>g-t){
			int l=1,r=t-1,pos=t;
			while(l<=r){
				int mid=(l+r)/2;
				if(querymx(1,1,mid)<g-t){//通过二分找到要修改的 l 和 r。
					l=mid+1;
				}else{
					r=mid-1;
					pos=mid;
				}
			}
			ans+=query(1,pos,t);
			ans-=(g-t)*(t-pos+1);
			setv(1,pos,t,g-t);
		}else{
			int l=t+1,r=n,pos=t;
			while(l<=r){
				int mid=(l+r)/2;
				if(querymx(1,t,mid)>g-t){
					r=mid-1;
				}else{
					l=mid+1;
					pos=mid;
				}
			}
			ans+=(g-t)*(pos-t+1);
			ans-=query(1,t,pos);
			setv(1,t,pos,g-t);
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Redshift_Shine (赞：8)

十分惊奇地发现题解通道还没关闭，那就水一篇题解。

这道题的套路在 Codeforces 上可以被称作人尽皆知。那就是，将一个单调上升序列转换为单调不下降序列，即 $a'_i=a_i-i$。

将原来的位置经过这种方式转换后，可以惊奇地发现原来复杂的移动策略简化为了区间赋值操作。

移动的区间可以通过在序列内寻找第一个不小于目标点的位置确定，而移动的总距离可以通过区间求和和简单的乘法确定。

线段树维护修改懒标记，区间和以及区间最大值。如此，查找位置可以线段树上二分，区间求和是基本操作。

注意修改时需要将目标点转化为位置对应的形式。

时间复杂度 $O(n+q\log n)$。

```c++
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10;
int n, m, a[N];
using ll = long long;
ll tr[N << 2], mx[N << 2], tag[N << 2], res, y;
void init(int x, int l, int r)
{
	tag[x] = -1;
	if (l == r)
	{
		tr[x] = mx[x] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	init(x << 1, l, mid);
	init(x << 1 | 1, mid + 1, r);
	tr[x] = tr[x << 1] + tr[x << 1 | 1];
	mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
}
void psh(int x, int l, int r)
{
	int mid = (l + r) >> 1;
	tr[x << 1] = (mid - l + 1) * tag[x];
	tr[x << 1 | 1] = (r - mid) * tag[x];
	mx[x << 1] = mx[x << 1 | 1] = tag[x];
	tag[x << 1] = tag[x];
	tag[x << 1 | 1] = tag[x];
	tag[x] = -1;
}
void update(int x, int l, int r, int lb, int rb, ll v)
{
	if (l >= lb and r <= rb)
	{
		mx[x] = v;
		tr[x] = (r - l + 1) * v;
		tag[x] = v;
		return;
	}
	if (~tag[x])
		psh(x, l, r);
	int mid = (l + r) >> 1;
	if (lb <= mid)
		update(x << 1, l, mid, lb, rb, v);
	if (rb > mid)
		update(x << 1 | 1, mid + 1, r, lb, rb, v);
	tr[x] = tr[x << 1] + tr[x << 1 | 1];
	mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
}
int fnd(int x, int l, int r, ll v)
{
	if (l == r)
		return tr[x] < v ? l + 1 : l;
	if (~tag[x])
		psh(x, l, r);
	int ret = 0, mid = (l + r) >> 1;
	if (mx[x << 1] >= v)
		ret = fnd(x << 1, l, mid, v);
	else
		ret = fnd(x << 1 | 1, mid + 1, r, v);
	tr[x] = tr[x << 1] + tr[x << 1 | 1];
	mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
	return ret;
}
ll query(int x, int l, int r, int lb, int rb)
{
	if (l >= lb and r <= rb)
		return tr[x];
	if (~tag[x])
		psh(x, l, r);
	int mid = (l + r) >> 1;
	ll ret = 0;
	if (lb <= mid)
		ret += query(x << 1, l, mid, lb, rb);
	if (rb > mid)
		ret += query(x << 1 | 1, mid + 1, r, lb, rb);
	tr[x] = tr[x << 1] + tr[x << 1 | 1];
	mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
	return ret;
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", a + i);
		a[i] -= i;
	}
	init(1, 0, n - 1);
	scanf("%d", &m);
	for (int i = 1, x, tar, tmp; i <= m; i++)
	{
		scanf("%d%lld", &x, &y);
		x--;
		y -= x;
		tar = fnd(1, 0, n - 1, y);
		tmp = x;
		if (tar > tmp)
		{
			tar--;
			res += y * (tar - tmp + 1) - query(1, 0, n - 1, tmp, tar);
			update(1, 0, n - 1, tmp, tar, y);
		}
		else
		{
			res += query(1, 0, n - 1, tar, tmp) - y * (tmp - tar + 1);
			update(1, 0, n - 1, tar, tmp, y);
		}
		// printf("%lld\n", res);
		// for (int j = 0; j < n; j++)
		// {
		// 	printf("%lld%c", query(1, 0, n - 1, j, j), " \n"[j == n - 1]);
		// }
	}
	printf("%lld\n", res);
}
```

---

## 作者：wusixuan (赞：6)

赛后20分钟做出来了 F 题，第一次切 F，写篇题解纪念一下。

我们观察样例可以发现，每一步任务 $(t,g)$ 之后，想要使答案最小，位置被 $t$ 所影响的人一定是拼在一起的。为了验证这个想法，可以把其他的样例也都推一下，可以发现这是正确的。

那样我们就可以得出 $O(nq)$ 的做法，找到影响的人（人数为 $x$），然后把他们按顺序拼到 $[g,g+x]$ 里面，注意影响的人并不包括 $t$ 本人。

但是我们并不满足于这样的做法，但是这种做法让人有一股优化到 $\log$ 的冲动。

找到影响的人那部分，不就是二分可以解决的吗？（具体如何二分读者可以先思考一遍，我的代码当中会体现出来）

拼到区间里面，就相当于一个首项为 $g$，公差为 $1$ 的等差数列，使我想到了 [T233406](https://www.luogu.com.cn/problem/T233406) 那道题，那道题是加法，而这道题只是变成了赋值，主题思路是不变的。

问题来了，如何计算步数？我们可以使用线段树当中的区间和查询，答案就是等差数列的各项和减去区间和即可。

于是我们得到了大体思路：

第一步：二分查找被影响到的人（容易发现是个区间）。

第二步：线段树维护等差数列赋值，还要支持区间查询。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 200010
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mid ((l + r) >> 1)
int n, m, a[N];
int node[N << 2], lazy1[N << 2], lazy2[N << 2];//lazy1代表首项，lazy2代表公差

//node表示区间和
void pushup(int now) {//上推很显然就是加起来
	node[now] = node[ls(now)] + node[rs(now)];
}

void pushdown(int now, int l, int r) {
	if (lazy2[now] != 0) {//满足lazy1!=0或lazy2!=0条件均可
		lazy2[ls(now)] = lazy2[now];
		lazy2[rs(now)] = lazy2[now];//把公差赋值到左右儿子
		lazy1[ls(now)] = lazy1[now];
		lazy1[rs(now)] = lazy1[now] + (mid - l + 1) * lazy2[now];//维护首项
		node[ls(now)] = (mid - l + 1) * lazy1[now] + (mid - l) * (mid - l + 1) / 2 * lazy2[now];
		node[rs(now)] = (r - mid) * lazy1[now] + (r - mid - 1) * (r - mid) / 2 * lazy2[now] + (r - mid) *
		                (mid - l + 1) * lazy2[now];//计算公式，这里不详细阐述，读者应该自己推出来
		lazy2[now] = 0;
		lazy1[now] = 0;
	}
}

void build(int now, int l, int r) {//建树
	lazy1[now] = lazy2[now] = 0;
	if (l == r) {
		node[now] = a[l];
		return;
	}
	build(ls(now), l, mid);
	build(rs(now), mid + 1, r);
	pushup(now);
}

int query(int now, int l, int r, int ql, int qr) {//查询区间和
	if (ql <= l && r <= qr)
		return node[now];
	pushdown(now, l, r);
	int res = 0;
	if (ql <= mid)
		res += query(ls(now), l, mid, ql, qr);
	if (mid < qr)
		res += query(rs(now), mid + 1, r, ql, qr);
	return res;
}

void modify(int now, int l, int r, int ql, int qr, int x, int val) {//修改
	if (ql <= l && r <= qr) {
		node[now] = (l + r - 2 * ql) * (r - l + 1) / 2 * val + (r - l + 1) * x;
		lazy2[now] = val;
		lazy1[now] = (l - ql) * val + x;
		return;
	}
	pushdown(now, l, r);
	if (ql <= mid)
		modify(ls(now), l, mid, ql, qr, x, val);
	if (mid < qr)
		modify(rs(now), mid + 1, r, ql, qr, x, val);
	pushup(now);
}

int find_right(int x, int pos) {//找被影响的人的右端点
	int l = x, r = n, ans;
	while (l <= r) {
		if (mid - x + pos > query(1, 1, n, mid, mid))//如果人堆到一个区间还是会造成影响
			ans = mid, l = mid + 1;
		else
			r = mid - 1;
	}
	return ans;
}

int find_left(int x, int pos) {//找被影响的人的左端点
	int l = 1, r = x, ans;
	while (l <= r) {
		if (pos - (x - mid) < query(1, 1, n, mid, mid))//同上
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	return ans;
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);
	cin >> m;
	int ans = 0;
	while (m--) {
		int x, pos;
		cin >> x >> pos;
		if (query(1, 1, n, x, x) == pos)
			continue;
		else if (query(1, 1, n, x, x) < pos) {
			int r = find_right(x, pos);
			int len = r - x;
			ans += (pos + pos + len) * (len + 1) / 2 - query(1, 1, n, x, r);
			modify(1, 1, n, x, r, pos, 1);//上面的思路
		} else {
			int l = find_left(x, pos);
			int len = x - l;
			ans += query(1, 1, n, l, x) - (pos + pos - len) * (len + 1) / 2;
			modify(1, 1, n, l, x, pos - len, 1);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：chenxumin1017 (赞：4)

# 前言

关于我这次 ABC，A 题做了 $15$ 分钟还 WA 了 $3$ 发，C 题没做出来，还上了大分这件事，真的太离谱了。

# 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/lz7grha6.png)

## 性质

观察上图中标红的地方，我们可以发现，位置移动了的人一定是端点为本次操作需要移动的人的一段区间，且移动后他们的位置为一段连续的区间。

## 实现

对于寻找每次操作要移动的人的区间，我们直接二分另外一个端点即可。

剩下就只需要写一个数据结构支持以下操作即可：

- 区间求和。

- 区间修改为公差为一的等差数列。

这些操作显然可以用线段树，第一个操作直接维护即可，第二个操作对每个区间维护一个左端点修改为那个数的懒标记即可。

# 代码

代码较丑就不贴了，要的话[自取](https://atcoder.jp/contests/abc371/submissions/57785829)。

---

## 作者：Fire_flame (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc371_f)

## $\mathtt{Solution}$

~~样例解释都把方法讲明白了，你怎么还不会。~~

看到样例解释，发现是区间赋值一个等差数列（等差数列的最后/最前一项可以二分得到），以及区间查询数字总和。

就没了，不过对于往左移动和往右移动分类一下即可。

唯一需要特别注意的是可能会移动到小于等于 $0$ 的位置，所以 `lazy` 不能设置成 $0$，一定要设置成无穷小。

赛时代码：

```cpp
#include<bits/stdc++.h>
#define left rt * 2
#define right rt * 2 + 1
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1;ch = getchar();}
	while(isdigit(ch)){s = s * 10 + ch - '0';ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5, MR = 8e5 + 5;
int n, m, ans, a[MAXN];
struct Segment_tree{
	int lf[MR], rf[MR], num[MR], lazy[MR];
	void push_up(int rt){num[rt] = num[left] + num[right];}
	void build(int rt, int l, int r){
		lf[rt] = l, rf[rt] = r, lazy[rt] = -11451419;
		if(l == r){
			num[rt] = a[l];
			return ;
		}
		int mid = l + r >> 1;
		build(left, l, mid);
		build(right, mid + 1, r);
		push_up(rt);
	}
	void push_down(int rt){
		if(lazy[rt] == -11451419)return ;
		num[left] = (lazy[rt] * 2 + (rf[left] - lf[left])) * (rf[left] - lf[left] + 1) / 2;
		num[right] = (lazy[rt] * 2 + (rf[right] - lf[left]) + (rf[left] - lf[left] + 1)) * (rf[right] - lf[right] + 1) / 2;
		lazy[left] = lazy[rt];
		lazy[right] = lazy[rt] + (rf[left] - lf[left] + 1);
		lazy[rt] = -11451419;
	}
	void change_list(int rt, int l, int r, int x){
		if(l > rf[rt] || r < lf[rt])return ;
		if(l <= lf[rt] && rf[rt] <= r){
			num[rt] = (x * 2 + rf[rt] - lf[rt]) * (rf[rt] - lf[rt] + 1) / 2;
			lazy[rt] = x;
//			printf("%lld %lld %lld\n", lf[rt], rf[rt], num[rt]);
			return ;
		}
		push_down(rt);
		change_list(left, l, r, x);
		change_list(right, l, r, x + max(rf[left] - max(lf[left], l) + 1, 0ll));
		push_up(rt);
	}
	int query(int rt, int l, int r){
		if(l > rf[rt] || r < lf[rt])return 0;
//		printf("%lld %lld %lld %lld\n", lf[rt], rf[rt], num[rt], lazy[rt]);
		if(l <= lf[rt] && rf[rt] <= r)return num[rt];
		push_down(rt);
		return query(left, l, r) + query(right, l, r);
	}
}tr;
signed main(){
	n = read();
	for(int i = 1;i <= n;i ++)a[i] = read();
	tr.build(1, 1, n);
	m = read();
	while(m --){
		int x = read(), y = read();
		int h = tr.query(1, x, x);
		if(h > y){
			int lpos = 1, rpos = x, lp = x;
			while(lpos <= rpos){
				int mid = lpos + rpos >> 1ll;
				if(tr.query(1, mid, mid) < y + mid - x)lpos = mid + 1;
				else lp = mid, rpos = mid - 1;
			}
			ans += tr.query(1, lp, x) - y * (x - lp + 1) + (x - lp) * (x - lp + 1) / 2;
			tr.change_list(1, lp, x, y - x + lp);
//			printf("1. %lld\n", lp);
		}
		else{
			int lpos = x, rpos = n, lp = x;
			while(lpos <= rpos){
				int mid = lpos + rpos >> 1ll;
				if(tr.query(1, mid, mid) > y + mid - x)rpos = mid - 1;
				else lpos = mid + 1, lp = mid;
			}
			ans += (y * 2 + lp - x) * (lp - x + 1) / 2 - tr.query(1, x, lp);
			tr.change_list(1, x, lp, y);
//			printf("2. %lld\n", lp);
		}
//		for(int i = 1;i <= n;i ++)
//			printf("ANS : %lld %lld\n", i, tr.query(1, i, i));
	}
	write(ans);
	return 0;
}

```

---

## 作者：zdd6310 (赞：4)

# [ABC371F] Takahashi in Narrow Road

## description

给你一个长度为 $n$ 的严格递增序列 $a$，求：在始终严格递增的情况下，依次满足询问中 $a_i=j$ 的条件，总共要将 $a$ 数组的每一个数改变多少。

## solution

下面我们对于询问 $a_i=j$ 考虑。

不妨假设此时的 $a_i<j$，也就是要向右移动。

首先根据样例，肯定是将第 $i$ 的一侧的数全部“推”到一边。

也就是 $a_i=j$，$a_{i+1}=j+1$，以此类推。

每一次移动都可能会将 $a_i$ 变成一个块，在其中 $a_i+1=a_{i+1}$。

自然，想到将每一个 $a_i$ 减去 $i$，设 $b_i=a_i-i$。

那么每一个连在一起的 $a_i$，他们的 $b_i$ 都相等。

而且题目中严格递增的 $a$，转换为了不降的 $b$。

现在就非常简单了，在 $b_i$ 右侧小于 $j$ 的应该全部变成 $j$。

然后统计答案，区间推平。

这就非常经典了。

---

你可以线段树上二分，这样要维护区间 $\max$，区间 $\min$，区间和。

或者二分套线段树，这样就只需要维护区间和了。

记得不管是哪一种方法，都要一个全局推平的 $tag$。

我写的是第一种做法，复杂度 $O(n\log n)$。

## code

这边建议读者慢慢打。

---

## 作者：g1ove (赞：2)

DS 题。

观察题目，我们发现每一次操作会先把一块中的一些人分裂出来，然后再把一些人合并成一块，然后进行整体操作。

观察每次操作，每次分裂使得总块数最多增加 $1$，因此最多只有 $n+q$ 块。

因此，我们用 `set` 存下所有块，按题意暴力模拟即可。每个块只会被遍历、删除、查询一次，时间复杂度 $O((n+q)\log n)$。

代码很丑：[Submission](https://atcoder.jp/contests/abc371/submissions/57788392)

---

## 作者：_Lazy_whr_ (赞：2)

对于第 $i$ 个人的坐标 $x_i$ ，我们定义一个整数 $X_i'$ 使得 $X_i=X_i'+i$。

然后，这个操作可以重新表述为如下：

给定 $T$ 和 $G$ 。为了将所有 $i$ 的 $X_i'$ 设置为 $G$ ，我们需要支付的成本是 $|X_i' - G|$ 。也就是说，如果 $X_T'\le G$ 且 $X_i'\in[X_T',G]$ 并且 $T\le i$ 时，否则，如果 $X_i'\in[G,X_T']$ 并且 $i\le T$ 时。

根据约束条件，$X_i'$ 相对于 $X_i$ 是单调的。此外，根据 $X_i'$ 的条件，支付的成本形式为 $\sum_{l \le i \le r} (X_i' - G) \times (r - l + 1)$ 或 $G \times (r - l + 1) - \sum_{l \le i \le r} X_i'$。

那么思路就有了：
- 使用像懒惰线段树这样的数据结构，它支持区间赋值、区间和、最小值和最大值检索，以直接执行上述操作。
-  使用 `map` ，来管理具有相同 $X_i'$ 值的索引段。

那么我就写了一个懒惰线段树：
```cpp
#include<bits/stdc++.h>
#include<atcoder/lazysegtree>//我才不会告诉你可以用这个
#define int long long
using namespace std;
int main()
{
    constexpr int offset{100000000};
    int n;
    cin>>n;
    //建树
    auto segment_tree=[](auto N)
    {
        struct Node
        {
            int length;
            int sum;
            int min, max;
        };
        using assign_type = optional<int>;
        atcoder::lazy_segtree<Node,[](auto& lhs, auto& rhs)->Node
        {
            auto &[l_len, l_sum, l_min, l_max]{lhs};
            auto &[r_len, r_sum, r_min, r_max]{rhs};
            return {l_len + r_len, l_sum + r_sum, min(l_min, r_min), max(l_max, r_max)};
        }, []()->Node
        {
            return {0U, 0UL, offset*2, 0U};
        }, assign_type, [](auto& f, auto x) {
           return f ? Node{x.length, static_cast<int>(*f) * x.length, *f, *f} : x;
        }, [](auto& f, auto &x){
            return f ? f : x;
        }, []{return std::nullopt;}> result(N);
        for (int i{}; i < N; i++)
        {
            int x;
            cin >> x;
            X += offset-i;
            result.set(i, {1, X, X, X});
        }
        return result;
    }(N);
    int q;
    cin>>q;
    int ans{};
    //模拟刚刚说的那个过程即可
    for (int i{}; i<Q; i++) {
        int t, g;
        cin >> t >> g;
        --t;
        g += offset-t;
        auto now_position{segment_tree.get(t).max};
        if (now_position < g)
        {
            auto upper_bound{segment_tree.max_right(t, [g](auto& v){return v.max < g;})};
            auto &[length, sum, min, max]{segment_tree.prod(t, upper_bound)};
            ans += static_cast<int>(length) * g - sum;
            segment_tree.apply(t, upper_bound, g);
        }
        else
        {
            auto it{segment_tree.min_left(t + 1, [g](auto& v){return v.min > g;})};
            auto& [length, sum, min, max]{segment_tree.prod(it, t + 1)};
            ans += sum - static_cast<int>(length) * g;
           segment_tree.apply(it, t + 1, g);
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：wangshulin (赞：1)

# 思路
数据结构题。

发现每次移动的总步数等于移动过后的坐标和与移动前的坐标和的差的绝对值，所以需要维护查询区间坐标和。

发现每次坐标的更改又需要维护区间求等差数列。

于是做法就是：每次用二分求出“推箱子”最远会波及哪个人（可以用线段树二分，也可以二分套线段树），求出他们的坐标和，更新答案，然后将这段区间进行等差数列赋值操作即可。

赛时写了 $O(n \log^2 n)$ 的二分套线段树做法，线段树二分可以到 $O(n \log n)$。
# 代码
赛时 [code](https://atcoder.jp/contests/abc371/submissions/57778442)。

---

## 作者：Coffee_zzz (赞：0)

首先考虑一下当我们需要把第 $i$ 个人从位置 $x$ 移动到位置 $y$ 时怎么做：

- 若 $x\lt y$，则我们需要先把 $[x+1,y]$ 中的所有人依次推到位置 $y$ 的右侧（即 $y+1,y+2,\dots$），再把第 $i$ 个人推到位置 $y$；
- 若 $y\lt x$，则我们需要先把 $[y,x-1]$ 中的所有人依次推到位置 $y$ 的左侧（即 $y-1,y-2,\dots$），再把第 $i$ 个人推到位置 $y$；
- 若 $x=y$，则不需要进行任何操作。

直接用线段树模拟可以做到 $\mathcal O(n \log n)$，但这个也太难写了。注意到，困难之处主要在于人之间不能重合，即**任意时刻人的位置序列单调递增**，因此我们考虑一个优化：把第 $i$ 个人的初始位置和所有目标位置都左移 $i$ 位，并将限制条件修改为**任意时刻人的位置序列单调不减**。优化后的问题和原问题显然是等价的，我们只要将第 $i$ 个人的位置右移 $i$ 位即可还原为原问题。

这样优化的巧妙之处在于，在优化后，当我们需要把第 $i$ 个人从位置 $x$ 推到位置 $y$ 时，只需要把 $[x,y]$ 中的所有人都推到位置 $y$ 即可！！！

于是，我们可以用一棵线段树维护每个人的位置 $w$。每次把第 $i$ 个人从位置 $x$ 推到位置 $y$ 时，分类讨论一下：

- 若 $x\lt y$，则用线段树二分找到最大的正整数 $r$ 使得 $w_r\le y$，并把 $w_i\sim w_r$ 的值赋为 $y$；
- 若 $y\lt x$，则用线段树二分找到最小的正整数 $l$ 使得 $y\le w_l$，并把 $w_l\sim w_i$ 的值赋为 $y$；
- 若 $x=y$，则不需要进行任何操作；

由于我们每次只会把人往同一个方向推，所以这样操作的次数等于原来的 $\sum w_k$ 与当前的 $\sum w_k$ 的差的绝对值。

直接按照任务的顺序模拟即可。我们认为 $n,q$ 同阶，则时间复杂度为 $\mathcal O(n \log n)$。

---

## 作者：Forg1weN (赞：0)

赛时想到了做法但是码力太差没有写出来。

观察题目，发现移动的本质是一个块不断被合并的一个过程，即移动的时候是一个块一起移动，然后不断的把路上的块合并在一起，考虑刚开始有 $n$ 个块，里面只有一个人，最多只会合并 $n$ 次，每次的询问有可能劈开一个长块，也就是直接模拟的复杂度是 $O(n+q)$ 的。

假设现在询问的人是 $i$，知道了其在块 $s$ 里面，只维护左右端点的话没办法知道其具体位置，于是我们多维护一个每个块开头的人的编号，这样在分裂块的时候能够知道 $i$ 的位置。

于是我们要维护的是：

- 块在数轴上的左右端点。
- 块的最左边人的编号。
- 每个人在哪个块中。

考虑条件一和二可以用链表来维护，劈开一个长块相当于在原有的块基础上新增一个块，条件三可以用线段树区间赋值维护，总时间复杂度量级为 $O(q\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+10;
const int bj=5e5;

int n,Q,tot;
int x[maxn];
ll ans;
struct TREE {
	#define lson (now<<1)
	#define rson (now<<1|1)
	#define mid ((l+r)>>1)
	int t[maxn*4],tag[maxn];
	void pushdown(int now) {
		if(tag[now]==-1)return;
		t[lson]=t[rson]=tag[now];
		tag[lson]=tag[rson]=tag[now];
		tag[now]=-1;
	}
	void build(int now=1,int l=1,int r=n) {
		if(l==r) { t[now]=l;tag[now]=-1; return; }
		tag[now]=-1;
		build(lson,l,mid);
		build(rson,mid+1,r);
	}
	void update(int now,int l,int r,int x,int y,int z) {
		if(x<=l&&r<=y){ t[now]=z,tag[now]=z;return;}
		pushdown(now);
		if(x<=mid)update(lson,l,mid,x,y,z);
		if(mid<y)update(rson,mid+1,r,x,y,z);
	}
	int query(int now,int l,int r,int x) {
		if(l==r)return t[now];
		pushdown(now);
		if(x<=mid)return query(lson,l,mid,x);
		else return query(rson,mid+1,r,x); 
	}
}T;

struct node {
	int l,r,f,pre,nxt;
}s[maxn];
signed main() {
	scanf("%d",&n);
	s[0].nxt=1,s[n+1].pre=n;
	for(int i=1;i<=n;i++) {
		scanf("%d",&x[i]);
		s[i].pre=i-1,s[i].nxt=i+1;
		s[i].l=x[i],s[i].r=x[i],s[i].f=i;
		tot++;
	}
	s[n].nxt=bj;
	T.build();
	scanf("%d",&Q);
	while(Q--) {
		int man,To;
		scanf("%d%d",&man,&To);
		int id=T.query(1,1,n,man);
		int pos=s[id].l+(man-s[id].f);
		if(s[id].l!=pos&&pos<To) {
			s[++tot]=(node){s[id].l,pos-1,s[id].f,s[id].pre,id};
			int len=(pos-1)-s[id].l+1;
			T.update(1,1,n,s[tot].f,s[tot].f+len-1,tot);
			s[s[id].pre].nxt=tot;
			s[id]=(node){pos,s[id].r,man,tot,s[id].nxt};
		}
		else if(To<pos&&s[id].r!=pos){
			s[++tot]=(node){pos+1,s[id].r,man+1,id,s[id].nxt};
			int len=s[id].r-(pos+1)+1;
			T.update(1,1,n,s[tot].f,s[tot].f+len-1,tot);
			s[s[id].nxt].pre=tot;
			s[id]=(node){s[id].l,pos,s[id].f,s[id].pre,tot};
		}
		else if(pos==To)continue;
		if(pos<To) {
			int dis=To-pos;
			int nowl=s[id].l,nowr=s[id].r;
			while(nowr+dis>=s[s[id].nxt].l&&s[id].nxt!=bj) {
				int del=s[s[id].nxt].l-nowr-1;
				dis-=del;
				ans+=1ll*del*(nowr-nowl+1);
				nowl+=del,nowr+=del;
				nowr+=s[s[id].nxt].r-s[s[id].nxt].l+1;
				s[id].nxt=s[s[id].nxt].nxt;
				s[s[id].nxt].pre=id;
			}
			ans+=1ll*dis*(nowr-nowl+1);
			nowl+=dis,nowr+=dis;
			s[id].l=nowl,s[id].r=nowr;
			int len=nowr-nowl+1;
			T.update(1,1,n,s[id].f,s[id].f+len-1,id);
		}
		else if(To<pos) {
			int dis=pos-To;
			int nowl=s[id].l,nowr=s[id].r;
			while(nowl-dis<=s[s[id].pre].r&&s[id].pre!=0) {
				int del=nowl-s[s[id].pre].r-1;
				dis-=del;
				ans+=1ll*del*(nowr-nowl+1);
				nowl-=del,nowr-=del;
				nowl-=s[s[id].pre].r-s[s[id].pre].l+1;
				s[id].f=s[s[id].pre].f;
				s[id].pre=s[s[id].pre].pre;
				s[s[id].pre].nxt=id;
			}
			ans+=1ll*dis*(nowr-nowl+1);
			nowl-=dis,nowr-=dis;
			s[id].l=nowl,s[id].r=nowr;
			int len=nowr-nowl+1;
			T.update(1,1,n,s[id].f,s[id].f+len-1,id);
		}
	}cout<<ans;
 	return 0;
}
```

---

## 作者：lizicheng3042 (赞：0)

做的时候有点急，没处理好细节，遗憾退场。  
这里提供一种不同于题解的线段树 $O(n\log^2n)$ 做法，不是很优，但是胜在好想。  
## 思路简述  
我们先考虑模拟这个过程，对于每个任务，我们要找到最外围的必须因此任务而运动的人，显然从给出人到这个人之间的人都是要移动的，我们再把这一部分人移动到目标地点，他们的坐标会构成一个公差为 $1$ 的等差数列，然后我们再把答案累加上每个人的坐标变化量，时间复杂度爆了，考虑优化模拟。  
我们考虑这个过程中我们到底需要维护的是什么：  
1. 求某个人的坐标。  
2. 求一个连续区间内人的坐标和。  
3. 更改一个连续区间内的人的坐标为一个公差为 $1$ 的等差数列。  
这很像是线段树可以维护的东西。（不会加等差数列的可以先去做 [无聊的数列](https://www.luogu.com.cn/problem/P1438)）所以我们考虑使用线段树去维护。  
然后我们发现那个最外围的人一次好像找不出来，但是我们发现如果某个人不必移动，和他相比距离给出的人更远的也不必移动，说明这个位置的可行性是有单调性的，可以二分求解，每次的复杂度 $O(\log^2n)$。  
然后其他的操作都是线段树的正常操作（区间求和，区间加等差数列），复杂度 $O(\log n)$，我就不用细说了。  
还有一个关键就是注意边界，由于题目中的数轴是有负半轴的，所以我们的懒标记的初始值要赋成一个很大或很小的数，还有就是 $0$ 和 $n+1$ 这两个位置特判一下，或者把这两个也放进线段树里即可，于是本题就这么做完了。
## 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int n,m,q,pos[1600005],x,k;
ll tree[1600005],lazy[1600005],ans;
bool i;
void maketag(int u,int l,int r,ll v)
{
	ll len=r-l;
	tree[u]=1ll*(v+len+1)*(v+len)/2ll-1ll*(v-1ll)*v/2ll;lazy[u]=v;
}
void pd(int u,int l,int r)
{
	if(lazy[u]!=-998244)
	{
		int mid=(l+r)>>1;
		maketag(u<<1,l,mid,lazy[u]);
		maketag(u<<1|1,mid+1,r,lazy[u]+mid-l+1);
		lazy[u]=-998244;
	}
}
void pu(int u)
{
	tree[u]=tree[u<<1]+tree[u<<1|1];
}
void update(int u,int l,int r,int L,int R,ll v)
{
	if(l>=L&&r<=R)
	{
		maketag(u,l,r,v);
		return;		
	}
	pd(u,l,r);
	int mid=(l+r)>>1;
	if(mid>=L)
		update(u<<1,l,mid,L,R,v);
	if(mid<R)
		update(u<<1|1,mid+1,r,L,R,v+max(0,mid+1-max(L,l)));
	pu(u);
}
ll query(int u,int l,int r,int L,int R)
{
	
	if(l>=L&&r<=R)
	{
		return tree[u];		
	}

	pd(u,l,r);
	int mid=(l+r)>>1;ll k=0;
	if(mid>=L)
		k+=query(u<<1,l,mid,L,R);
	if(mid<R)
		k+=query(u<<1|1,mid+1,r,L,R);
	return k;
}
int find(int x,int to)//找到要和x不一起移动的最外围的人
{
	ll now=query(1,0,n+1,x,x);
	if(now>to)
	{
		int l=1,r=x;
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			ll now1=query(1,0,n+1,mid,mid);
			ll now2=query(1,0,n+1,mid-1,mid-1);
			if(now2>=to)
				r=mid-1;
			else if(to-now2>=x-mid+1)
				l=mid;
			else
				r=mid-1;
		}
		return l;
	}
	else if(now<to)
	{
		int l=x,r=n;
		while(l<r)
		{
			int mid=(l+r)>>1;
			ll now1=query(1,0,n+1,mid,mid);
			ll now2=query(1,0,n+1,mid+1,mid+1);
			if(now2<=to)
				l=mid+1;
			else if(now2-to>=mid-x+1)
				r=mid;
			else
				l=mid+1;			
		}
		return l;
	}
	else
		return x;
}
void build(int u,int l,int r)
{
	lazy[u]=-998244;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(u<<1,l,mid);build(u<<1|1,mid+1,r);
}
int main()
{
	scanf("%d",&n);
	for(int a=1;a<=n;a++)
	{
		scanf("%d",&pos[a]);
		update(1,0,n+1,a,a,pos[a]);
	}
	update(1,0,n+1,0,0,-9982000ll);
	update(1,0,n+1,n+1,n+1,2140000000ll);
	build(1,0,n+1);
	scanf("%d",&q);
	for(int a=1;a<=q;a++)
	{
		scanf("%d%d",&x,&k);
		int y=find(x,k);
		if(y<x)
			swap(x,y),i=true;
		ll c=query(1,0,n+1,x,y);
		if(i)
			k-=y-x;
		update(1,0,n+1,x,y,k);
		ll d=query(1,0,n+1,x,y);
		ans+=abs(c-d);
		i=false;
	}
	printf("%lld",ans);
	return 0;
}
```

---

