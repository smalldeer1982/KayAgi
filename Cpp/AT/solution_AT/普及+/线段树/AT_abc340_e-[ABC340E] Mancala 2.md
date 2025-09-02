# [ABC340E] Mancala 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc340/tasks/abc340_e

$ 0 $ から $ N-1 $ の番号がついた $ N $ 個の箱があります。最初、箱 $ i $ には $ A_i $ 個のボールが入っています。

高橋君は $ i=1,2,\ldots,M $ の順に以下の操作を行います。

- 変数 $ C $ を $ 0 $ とする。
- 箱 $ B_i $ の中のボールを全て取り出し、手に持つ。
- 手にボールを $ 1 $ 個以上持っている間、次の処理を繰り返す：
  - $ C $ の値を $ 1 $ 増やす。
  - 手に持っているボールを $ 1 $ 個、箱 $ (B_i+C)\ \bmod\ N $ に入れる。
 
全ての操作を終えた後、各箱に入っているボールの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- $ 0\ \leq\ B_i\ <\ N $
- 入力は全て整数
 
### Sample Explanation 1

操作は次のように進行します。 !\[図\](https://img.atcoder.jp/abc340/2be752ad9f0e3a7336fb4d34561be58f.gif)

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
2 4 0```

### 输出

```
0 4 2 7 2```

## 样例 #2

### 输入

```
3 10
1000000000 1000000000 1000000000
0 1 0 1 0 1 0 1 0 1```

### 输出

```
104320141 45436840 2850243019```

## 样例 #3

### 输入

```
1 4
1
0 0 0 0```

### 输出

```
1```

# 题解

## 作者：fcy20180201 (赞：2)

## 思路
发现每次操作是取出**一个盒子**里的球，**循环放入**盒子。假设被取出球的盒子为 $x$，取出了 $y$ 个球，则放球时相当于先给**每个盒子**放 $\left\lfloor \frac{y}{n}\right\rfloor $ 个球，再把剩余的 $y \bmod n$ 个球依次放入对应的盒子。所以操作的本质是：单点查询，单点修改，区间修改，可以用树状数组实现。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;//不开 long long 见祖宗
int n,m,x;
ll tr[200005];
//树状数组
void add(int a,ll b){while(a<=n)tr[a]+=b,a+=(a&-a);}
ll ask(int a){return a?ask(a-(a&-a))+tr[a]:0ll;}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		add(i,x),add(i+1,-x);//初始化
	}
	while(m--){
		scanf("%d",&x),x++;
		ll y=ask(x);//查询取出了多少球
		add(x,-y),add(x+1,y);//将盒子清零
		add(1,y/n),add(n+1,-y/n);//先给每个盒子增加
		add(x+1,1),add(min(n,x+(int)(y%n))+1,-1);
		//先给盒子 x 后的盒子加上剩余的
		if(x+y%n>n)add(1,1),add(y%n-(n-x)+1,-1);
		//给盒子 x 前的盒子加上剩余的
	}
	for(int i=1;i<=n;i++)printf("%lld ",ask(i));
	return 0;
}
```

---

## 作者：apiad (赞：1)

遇到这种区间的题目，想都别想，直接上**线段树**。

列举一下，发现其实是可以分为这两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/z3ahyb59.png)

先看第二种情况。那么就是 $a_i \le n-i$。也就是往后填就不会跳到前面来。

第一种情况呢，就是 $a_i > n-i$。

分成三个部分进行线段树的区间修改，第一个区间是 $i+1$ 到 $n$，这里加一，也就是蓝色的线段。然后是 $1$ 到 $n$，这里要加除了第一个区间用掉的再除以 $n$ 向下取整，也就是还能有多少个来回，很显然，如图，就是有 $3$ 次，~~因为有三条绿线~~。而且都是 $1$ 到 $n$ 的线段。然后 $n$ 剩下的数就是黄色的线段。

细节还要注意下，例如第一段如果 $i=n$ 的时候是没有的，要排除掉，然后第三条一定是 $n$ 不等于 $0$ 才可以，不然就出现了一个区间 $l > r$。

[code](https://atcoder.jp/contests/abc340/submissions/50167162)。

---

## 作者：NaOHqwq (赞：1)

注意到第 $i$ 次操作是将 $A_{B_i}$ 向 $(B_i+1)\bmod n,(B_i+2)\bmod n,...,(B_i+A_{B_i})\bmod n$ 分配。

显然所有箱子都收到了 $\lfloor\frac{A_{B_i}}{n}\rfloor$ 个球，剩余的 $q=A_{B_i}\bmod n$ 个球被分配到了 $(B_i+1)\bmod n,(B_i+2)\bmod n,...,(B_i+q)\bmod n$ 里。用线段树维护区间加即可。

复杂度 $O(m\log n)$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005;
int L[N << 2], R[N << 2], val[N << 2], tag[N << 2];
int a[N];

int build(int l, int r, int p) {
	L[p] = l, R[p] = r;
	if (l == r)
		return val[p] = a[l];
	return val[p] = build(l, (l + r) / 2, p * 2) + build((l + r) / 2 + 1, r, p * 2 + 1);
}

void tg(int p, int v) {
	tag[p] += v, val[p] += (R[p] - L[p] + 1) * v;
}

void pdown(int p) {
	if (tag[p])
		tg(p * 2, tag[p]), tg(p * 2 + 1, tag[p]), tag[p] = 0;
}

void add(int l, int r, int p, int v) {
	if (L[p] > r || R[p] < l)
		return;
	if (L[p] >= l &&  R[p] <= r) {
		tg(p, v);
		return;
	}
	pdown(p);
	add(l, r, p * 2, v), add(l, r, p * 2 + 1, v);
	val[p] = val[p * 2] + val[p * 2 + 1];
}

int que(int l, int r, int p) {
	if (L[p] > r || R[p] < l)
		return 0;
	if (R[p] <= r && L[p] >= l)
		return val[p];
	pdown(p);
	return que(l, r, p * 2) + que(l, r, p * 2 + 1);
}
int v[N], r[N];

signed main() {
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	build(0, n - 1, 1);
	for (int i = 0; i < q; i++) {
		int f;
		cin >> f;
		int v = que(f, f, 1);
		add(f, f, 1, -v);
		add(0, n - 1, 1, v / n);
		v %= n;
		f = f + 1;
		f %= n;
		if (v + f - 1 >= n) {
			add(f, n - 1, 1, 1);
			add(0, v + f - n - 1, 1, 1);
		} else {
			add(f, v + f - 1, 1, 1);
		}
	}
	for (int i = 0; i < n; i++)
		cout << que(i, i, 1) << ' ';
}
```

---

## 作者：KSCD_ (赞：1)

# 题意
有 $n$ 盒球（编号从 $0$ 开始），第 $(n-1)$ 个盒的下一个盒为第 $0$ 个，每盒初始有一些球。每次拿出一个盒内的所有球，从该盒开始不断向下一个盒放一个球，放完为止，求最终每盒内的球数。

# 思路
本题有显然的模拟解法，但 $A_i$ 过大，时间复杂度过高，无法通过本题。

我们发现时间复杂度的瓶颈在于模拟放球，此处可以使用线段树优化区间加操作。

（以下设取出的球数为 $S$）

当 $S$ 较大时，每个盒子至少会被加上 $\lfloor \frac{S}{n} \rfloor$ 个球，也就是至少会把 $n$ 个盒子全部放 $\lfloor \frac{S}{n} \rfloor$ 遍。

发现这里的**多次放球**可以转化为**放多个球**，便可以用一次区间加解决。

因此先对全部盒子进行一次区间加处理，同时令 $S$ 对 $n$ 取模，如此可以保证没有重复加球的盒子。

之后使用线段树进行区间加 $1$，最后输出答案即可。

此处需要注意剩余的区间可能会从第 $(n-1)$ 个盒子跳到第 $1$ 个盒子，需要特判成两个区间分别进行维护。

具体操作请看代码实现。

# 代码
注：本题需要实现区间修改和单点查询，但单点就是长度为 $1$ 的区间，因此笔者写了区间查询。
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+10;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch=='-') w=-1; if(ch==EOF) return 0; ch=getchar();}
	while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar();}
	return s*w;
}
int n,m,t=1;
int aa[N]; 
struct nod
{
	int w,l,r,tag;
}a[N*2];//线段树记得开两倍空间 
void pushup(int u)
{
	a[u].w=a[a[u].l].w+a[a[u].r].w;
}
void pushdown(int u,int l,int r)
{
	int mid=(l+r)/2,lc=a[u].l,rc=a[u].r;
	a[lc].tag+=a[u].tag;
	a[rc].tag+=a[u].tag;
	a[lc].w+=a[u].tag*(mid-l+1);
	a[rc].w+=a[u].tag*(r-mid);
	a[u].tag=0;
} 
void build(int u,int l,int r)
{
	if(l==r)
	{
		a[u].w=aa[l];
		return;
	}
	int mid=(l+r)/2;
	a[u].l=++t;
	build(t,l,mid);
	a[u].r=++t;
	build(t,mid+1,r);
	pushup(u);
}//建树 
void add(int u,int l,int r,int ll,int rr,int k)
{
	if(l>=ll&&r<=rr)
	{
		a[u].tag+=k;
		a[u].w+=k*(r-l+1);
		return;
	}
	pushdown(u,l,r);
	int mid=(l+r)/2;
	if(ll<=mid)
		add(a[u].l,l,mid,ll,rr,k);
	if(rr>mid)
		add(a[u].r,mid+1,r,ll,rr,k);
	pushup(u);
}//对ll-rr区间加 
int check(int u,int l,int r,int ll,int rr)
{
	if(l>=ll&&r<=rr)
		return a[u].w;
	int mid=(l+r)/2,ans=0;
	pushdown(u,l,r);
	if(ll<=mid)
		ans+=check(a[u].l,l,mid,ll,rr);
	else
		ans+=check(a[u].r,mid+1,r,ll,rr);
	return ans;
}//查询ll-rr区间和 
signed main()
{
	n=read(),m=read();
	for(int i=0;i<n;i++)
		aa[i]=read();
	build(1,0,n-1);
	for(int i=1;i<=m;i++)
	{
		int tu=read();
		int ts=check(1,0,n-1,tu,tu);//取出的球数 
		add(1,0,n-1,tu,tu,-ts);//取球操作 
		int sum=ts/n;//每个盒子放一遍的轮数 
		if(sum>0)
			add(1,0,n-1,0,n-1,sum);
		ts%=n;//处理该情况
		if(ts==0)
			continue;//如果已经放完了就结束 
		if(tu+ts>n-1)
		{
			if(tu!=n-1)
				add(1,0,n-1,tu+1,n-1,1);
			ts-=(n-1-tu),tu=-1;
		}//若出现两个区间则先将以(n-1)为结尾的区间处理完，转到另一个以1开头的区间 
		tu++;
		add(1,0,n-1,tu,tu+ts-1,1);//对剩余区间操作 
	}
	for(int i=0;i<n;i++)
		cout<<check(1,0,n-1,i,i)<<' '; //输出 
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[[ABC340E] Mancala 2 ](https://www.luogu.com.cn/problem/AT_abc340_e)

线段树板题，为了方便，从 $1$ 开始标号。

直接考虑每次操作，每个人的排位构成一个环，就是把当前的人的球拿走，然后不断往后传，传到谁谁拿一个，传完就结束。

因为 $a_i$ 很大，我们不能直接模拟传球的过程，所以不妨直接计算能传多少轮（也就是走一圈回到当前点），然后对余数 $p$ 进行一个处理。

如果当前位置加一往后到 $n$ 的位置数量大于 $p$ 的话，那直接对这段区间修改即可。

否则拆成两段，从当前位置加一到 $n$，以及从 $1$ 到剩下部分修改。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long 
struct node{
	int sum,lazy;
}d[N<<1];
int a[N],n,m;
void build(int s,int t,int p){
	if(s==t){
		d[p].sum=a[s];
		return ;
	}
	int mid=(s+t)>>1;
	build(s,mid,p<<1),build(mid+1,t,p<<1|1);
	d[p].sum=d[p<<1|1].sum+d[p<<1].sum;
}
void push_down(int s,int t,int p){
	int mid=(s+t)>>1;
	d[p<<1].sum+=(mid-s+1)*d[p].lazy,d[p<<1].lazy+=d[p].lazy;
	d[p<<1|1].sum+=(t-mid)*d[p].lazy,d[p<<1|1].lazy+=d[p].lazy;
	d[p].lazy=0;
}
void update(int l,int r,int s,int t,int p,int change){
	if(l<=s&&t<=r){
		d[p].sum+=(t-s+1)*change,d[p].lazy+=change;
		return ;
	}
	int mid=(s+t)>>1;
	push_down(s,t,p);
	if(l<=mid)	update(l,r,s,mid,p<<1,change);
	if(r>mid)	update(l,r,mid+1,t,p<<1|1,change);
	d[p].sum=d[p<<1|1].sum+d[p<<1].sum;
}
int Query(int l,int r,int s,int t,int p){
	if(l<=s&&t<=r)	return d[p].sum;
	int mid=(s+t)>>1,ans=0;
	push_down(s,t,p);
	if(l<=mid)	ans+=Query(l,r,s,mid,p<<1);
	if(r>mid)	ans+=Query(l,r,mid+1,t,p<<1|1);
	return ans;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>a[i];
	build(1,n,1);
	for(int i=1,x;i<=m;i++){
		cin>>x,x++;
		int now=Query(x,x,1,n,1),pre=now/n;
		update(x,x,1,n,1,-now),update(1,n,1,n,1,pre);
		int lst=now-pre*n;
		if(x+1+lst-1<=n&&lst!=0)	
			update(x+1,x+1+lst-1,1,n,1,1);
		else{
			if(x!=n&&lst!=0)	update(x+1,n,1,n,1,1);
			if(lst!=0)	update(1,lst-(n-(x+1)+1),1,n,1,1);
		}	
	}
	for(int i=1;i<=n;i++)	cout<<Query(i,i,1,n,1)<<" ";
	cout<<endl;
}
```


---

## 作者：wizardMarshall (赞：0)

## 题意

一开始的时候有 $n$ 个盒子排成一个环，第 $i$ 个盒子有 $a_i$ 个球。

给定一个数组 $b$，对每个 $a_{b_i}$ 执行以下操作：

- 取出这个盒子里的所有球。

- 从 $b_i+1$ 个盒子开始，每个盒子放一个球，顺时针绕过来。直到球放完。

## 思路

注：以下由于作者习惯，下标从 $1$ 开始，与题面略有不同。

这道题的 $a_i\le 10^9$，不难看出需要整体进行操作，可以使用线段树对每次修改动态维护（或树状数组等）。

首先，我们在线查询每个 $a_{b_i}$ 的值，并且清零，这就是线段树里的单点查询和单点修改。

接着，我们来处理顺时针加的操作。比较方便的做法是先将所有数加上 $\lfloor \dfrac{a_{b_i}}{n} \rfloor$，即整体转了几圈。（这里可以对 $[1,n]$ 区间整体操作）

之后还有一些余数，从 $a_{b_i+1}$ 开始区间操作，分类讨论一下是否会超过 $n$ 从 $1$ 开始即可。

最后注意，$\sum a_i$ 范围大约是 $10^{14}$ 级别，整型存不下。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
int a[200005];
int lazy[800005];//区间懒标记，加了多少
int sum[800005];//注意范围要开足4倍
void build(int l, int r, int x) {//建树
	if (l == r) {
		sum[x] = a[l];
		return ;
	}int m = (l + r) / 2;
	build(l, m, x * 2);
	build(m + 1, r, x * 2 + 1);
	sum[x] = sum[x * 2] + sum[x * 2 + 1];
}

void pushdown(int x, int l, int r) {//下传懒惰标记
	int m = (l + r) / 2;
	if (lazy[x]) {
		lazy[x * 2] += lazy[x];sum[x * 2] += (m - l + 1) * lazy[x];
		lazy[x * 2 + 1] += lazy[x];sum[x * 2 + 1] += (r - m) * lazy[x];
		lazy[x] = 0;
	}return;
}

void change(int L, int R, int value, int l, int r, int x) {//成段更新（加value）
	if (L <= l && r <= R) {
		sum[x] += (r - l + 1) * value;
		lazy[x] += value;
		return;
	}pushdown(x, l, r);
	int m = (l + r) / 2;
	if (L <= m) {
		change(L, R, value, l, m, x * 2);
	}if (R > m) {
		change(L, R, value, m + 1, r, x * 2 + 1);
	}sum[x] = sum[x * 2] + sum[x * 2 + 1];
}

int ask(int L, int R, int l, int r, int x) {//查询区间总和
	if (L <= l && r <= R) {
		return sum[x];
	}pushdown(x, l, r);
	int m = (l + r) / 2;
	int ret = 0;
	if (L <= m) {
		ret += ask(L, R, l, m, x * 2);
	}if (R > m) {
		ret += ask(L, R, m + 1, r, x * 2 + 1);
	}return ret;
}
signed main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}build(1, n, 1);
	for (int i = 1; i <= m; i++) {
		int b;
		scanf("%lld", &b);b++;//为统一标准，需要+1
		int v = ask(b, b, 1, n, 1);
		change(b, b, -v, 1, n, 1);//单点清空
		if (v>= n)change(1, n, v / n, 1, n, 1);//加上转了几圈的总和
		v %= n;//接下来计算余数
		if (!v)continue;//如果v=0，区间[b+1,b]操作会陷入死循环
		if (b + v <=n) {//分讨，此时不超过n
			change(b + 1, b + v, 1, 1, n, 1); 
		}else {//此时超过n，需要从头开始
			if (b != n)change(b + 1, n, 1, 1, n, 1);//同样防止死循环
			change(1, v - (n - b), 1, 1, n, 1); 
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%lld ", ask(i, i, 1, n, 1));//相当于单点查询
	}
	return 0;
}
```

---

## 作者：incra (赞：0)

### Solution
线段树水题，考虑线段树（雾。

线段树维护序列 $\{a\}$，查询操作不赘述，修改操作简单讲一下：

设这次修改的数下标是 $x$，这个位置有 $num$ 个数。

首先，对于 $num>n$ 的情况，显然可以先给每一个数加上 $\left\lfloor\dfrac{num}{n}\right\rfloor$，然后 $num\gets num \bmod n$。

接下来，我们要执行的操作就是给 $x$ 后的 $num$ 个节点加一，此时又可以分类：

若 $x+num\le n$，直接修改。

否则，拆开操作区间，分为 $[x+1,n]$ 和 $[1,x+num-n]$。

说实话以上东西真的没什么好讲。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 200010;
int n,m;
int a[N];
struct node {
    int l,r;
    LL sum,add;
}tr[4 * N];
void push_up (int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}
void opt_add (int u,LL d) {
    tr[u].sum += (LL)d * (tr[u].r - tr[u].l + 1);
    tr[u].add += d;
}
void push_down (int u) {
    if (tr[u].add) {
        opt_add (u << 1,tr[u].add),opt_add (u << 1 | 1,tr[u].add);
        tr[u].add = 0;
    }
}
void build (int u,int l,int r) {
    tr[u] = {l,r,a[l],0};
    if (l == r) return ;
    int mid = l + r >> 1;
    build (u << 1,l,mid),build (u << 1 | 1,mid + 1,r);
    push_up (u);
}
void modify (int u,int l,int r,LL d) {
    if (l <= tr[u].l && tr[u].r <= r) {
        opt_add (u,d);
        return ;
    }
    push_down (u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) modify (u << 1,l,r,d);
    if (r >= mid + 1) modify (u << 1 | 1,l,r,d);
    push_up (u);
}
LL query (int u,int l,int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
    push_down (u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL ans = 0;
    if (l <= mid) ans += query (u  << 1,l,r);
    if (r >= mid + 1) ans += query (u << 1 | 1,l,r);
    return ans;
}
int main () {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) cin >> a[i];
	build (1,1,n);
	for (int i = 1;i <= m;i++) {
		int x;
		cin >> x;
		x++;
		LL num = query (1,x,x);
		modify (1,x,x,-num);
//		cout << "--" << num << "--" << endl;
		modify (1,1,n,num / n);
		num %= n;
		if (!num) continue;
		if (x + num > n) {
			if (x == n) modify (1,1,num,1);
			else modify (1,x + 1,n,1),modify (1,1,x + num - n,1);
		}
		else modify (1,x + 1,x + num,1);
	}
	for (int i = 1;i <= n;i++) cout << query (1,i,i) << ' ';
	return 0;
}
```

---

## 作者：__Dist__ (赞：0)

### E

线段树，挺板的。

如果把所有盒子看成一个环，就容易发现每次操作的区间是一个连续的区间。

为方便处理，我把下标记作 $1\sim n$。

分 $3$ 部分处理：

1. 从 $b_i \sim n$ 这一段。当然如果 $b_i + a_{b_i} < n$ 就是 $b_i\sim b_i+a_{b_i}$ 这一段。统一 $+1$。
2. 所有的 $1\sim n$，我们容易求出一共加了几次。
3. $1 \sim$ 剩余的部分。统一 $+1$。

最后输出答案就行了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int long long

using namespace std;

const int MAXN = 2e5 + 5;

int n, m;
int a[MAXN];
int b[MAXN];
int ans[MAXN << 2];
int tag[MAXN << 2];

inline int ls(int p) {
	return p << 1;
}
inline int rs(int p) {
	return p << 1 | 1;
}

void push_up(ll p) {
	ans[p] = ans[ls(p)] + ans[rs(p)];
}

void build(ll p, ll l, ll r) {
	tag[p] = 0;
	if (l == r) {
		ans[p] = a[l];
		return ;
	}
	ll mid = (l + r) >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	push_up(p);
}

void f(ll p, ll l, ll r, ll k) {
	tag[p] = tag[p] + k;
	ans[p] = ans[p] + k * (r - l + 1);
}

void push_down(ll p, ll l, ll r) {
	ll mid = (l + r) >> 1;
	f(ls(p), l, mid, tag[p]);
	f(rs(p), mid + 1, r, tag[p]);
	tag[p] = 0;
}

void update(ll nl, ll nr, ll l, ll r, ll p, ll k) {
	if (nl <= l && r <= nr) {
		ans[p] += k * (r - l + 1);
		tag[p] += k;
		return ;
	}
	push_down(p, l, r);
	ll mid = (l + r) >> 1;
	if (nl <= mid)update(nl, nr, l, mid, ls(p), k);
	if (nr > mid) update(nl, nr, mid + 1, r, rs(p), k);
	push_up(p);
}

int query(ll q_x, ll q_y, ll l, ll r, ll p) {
	ll res = 0;
	if (q_x <= l && r <= q_y)return ans[p];
	ll mid = (l + r) >> 1;
	push_down(p, l, r);
	if (q_x <= mid)res += query(q_x, q_y, l, mid, ls(p));
	if (q_y > mid) res += query(q_x, q_y, mid + 1, r, rs(p));
	return res;
}

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
		b[i]++;
		int sum = query(b[i], b[i], 1, n, 1);
		update(b[i], b[i], 1, n, 1, -sum);
		if(b[i] + sum <= n) {
			update(b[i] + 1, b[i] + sum, 1, n, 1, 1);
			continue;
		}
		else if(b[i] != n) update(b[i] + 1, n, 1, n, 1, 1);
		sum -= (n - b[i]);
		int p = sum / n;
		update(1, n, 1, n, 1, p);
		sum -= p * n;
		if(sum == 0) continue;
		update(1, sum, 1, n, 1, 1);
	}
	for (int i = 1; i <= n; i++) {
		cout << query(i, i, 1, n, 1) << ' ';
	}
	return 0;
}
```

---

## 作者：banned_gutongxing (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc340_e)

## 思路分析

又是一道线段树好题！

我们看一下它的操作：假设不取模，则他是在后面区间 $[x+1,x+a_i]$ 的盒子中放入1个小球，其中 $a_i$ 表示第 $i$ 个盒子里现在的小球数量。这是一个区间问题，所以我们可以使用**线段树+懒标记**来维护。

但是区间 $[x+1,x+a_i]$ 区间里面区间有可能会取模，所以我们把这样的区间分为几类：

1. 区间的左端点大于等于 $n$，此时我们需要将区间整体向左移动，即变化为区间 $[l-\lfloor \frac{l}{n}\rfloor\cdot n,r-\lfloor \frac{l}{n}\rfloor\cdot n]$；
2. 区间的右端点小于 $n$，此时整个区间进行修改；
3. 区间的右端点小于 $2n$，此时区间分为两半，为区间 $[l,n-1]$ 和区间 $[0,r]$ 分别进行修改；
4. 区间的右端点大于等于 $2n$，此时区间分为多段，有区间 $[l,n-1]$ 和中间一些完整的区间和区间 $[0,r]$ 三种区间，分别对其进行修改。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+10;
int n,m,a[MAXN];
//Segment Tree
struct SegmentTree{
	int l,r,len,sum,lazy;
}tree[MAXN*4];
void pushup(int k){
	if(tree[k].l == tree[k].r) return;
	tree[k].sum = tree[k*2].sum+tree[k*2+1].sum;
}
void pushdown(int k){
	if(tree[k].l == tree[k].r) return;
	if(tree[k].lazy){
		tree[k*2].lazy += tree[k].lazy;
		tree[k*2+1].lazy += tree[k].lazy;
		tree[k*2].sum += tree[k].lazy*tree[k*2].len;
		tree[k*2+1].sum += tree[k].lazy*tree[k*2+1].len;
		tree[k].lazy = 0;
	}
}
void build(int k,int l,int r){
	tree[k].l = l;
	tree[k].r = r;
	tree[k].len = r-l+1;
	if(l==r){
		tree[k].sum = a[l];
		return;
	}
	int mid = (l+r)>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	pushup(k);
}
void modify(int k,int l,int r,int x){
	if(tree[k].l>r||tree[k].r<l) return;
	if(tree[k].l>=l&&tree[k].r<=r){
		tree[k].sum += tree[k].len*x;
		tree[k].lazy += x;
		return;
	}
	pushdown(k);
	modify(k*2,l,r,x);
	modify(k*2+1,l,r,x);
	pushup(k);
}
int ask(int k,int l,int r){
	if(tree[k].l>r||tree[k].r<l) return 0;
	if(tree[k].l>=l&&tree[k].r<=r) return tree[k].sum;
	pushdown(k);
	int ans = ask(k*2,l,r)+ask(k*2+1,l,r);
	pushup(k);
	return ans;
}
void M(int l,int r){
	if(l>r) return;
	if(r<n){
		modify(1,l,r,1);
		return;
	}
	if(l>=n){
		int tmp = l/n*n;
		M(l-tmp,r-tmp);
		return;
	}
	if(r>=2*n){
		modify(1,l,n-1,1);
		modify(1,0,n-1,r/n-1);
		modify(1,0,r%n,1);
		return;
	}
	modify(1,l,n-1,1);
	modify(1,0,r%n,1);
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i = 0;i<n;i++){
		scanf("%lld",a+i);
	}
	build(1,0,n-1);
	for(int i = 1;i<=m;i++){
		int x;
		scanf("%lld",&x);
		int tmp = ask(1,x,x);
		modify(1,x,x,-tmp);
		M(x+1,x+tmp);
	}
	for(int i = 0;i<n;i++){
		printf("%lld ",ask(1,i,i));
	}
	return 0;
}
```



---

