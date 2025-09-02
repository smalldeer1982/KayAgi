# Messenger Simulator

## 题目描述

Polycarp is a frequent user of the very popular messenger. He's chatting with his friends all the time. He has $ n $ friends, numbered from $ 1 $ to $ n $ .

Recall that a permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array.

So his recent chat list can be represented with a permutation $ p $ of size $ n $ . $ p_1 $ is the most recent friend Polycarp talked to, $ p_2 $ is the second most recent and so on.

Initially, Polycarp's recent chat list $ p $ looks like $ 1, 2, \dots, n $ (in other words, it is an identity permutation).

After that he receives $ m $ messages, the $ j $ -th message comes from the friend $ a_j $ . And that causes friend $ a_j $ to move to the first position in a permutation, shifting everyone between the first position and the current position of $ a_j $ by $ 1 $ . Note that if the friend $ a_j $ is in the first position already then nothing happens.

For example, let the recent chat list be $ p = [4, 1, 5, 3, 2] $ :

- if he gets messaged by friend $ 3 $ , then $ p $ becomes $ [3, 4, 1, 5, 2] $ ;
- if he gets messaged by friend $ 4 $ , then $ p $ doesn't change $ [4, 1, 5, 3, 2] $ ;
- if he gets messaged by friend $ 2 $ , then $ p $ becomes $ [2, 4, 1, 5, 3] $ .

For each friend consider all position he has been at in the beginning and after receiving each message. Polycarp wants to know what were the minimum and the maximum positions.

## 说明/提示

In the first example, Polycarp's recent chat list looks like this:

- $ [1, 2, 3, 4, 5] $
- $ [3, 1, 2, 4, 5] $
- $ [5, 3, 1, 2, 4] $
- $ [1, 5, 3, 2, 4] $
- $ [4, 1, 5, 3, 2] $

So, for example, the positions of the friend $ 2 $ are $ 2, 3, 4, 4, 5 $ , respectively. Out of these $ 2 $ is the minimum one and $ 5 $ is the maximum one. Thus, the answer for the friend $ 2 $ is a pair $ (2, 5) $ .

In the second example, Polycarp's recent chat list looks like this:

- $ [1, 2, 3, 4] $
- $ [1, 2, 3, 4] $
- $ [2, 1, 3, 4] $
- $ [4, 2, 1, 3] $

## 样例 #1

### 输入

```
5 4
3 5 1 4```

### 输出

```
1 3
2 5
1 4
1 5
1 5```

## 样例 #2

### 输入

```
4 3
1 2 4```

### 输出

```
1 3
1 2
3 4
1 4```

# 题解

## 作者：YLWang (赞：31)

正解是个很有创造力的做法，感觉自己get了不少。两个月没碰OI水平果然大幅度下降了。

首先我们一看，这是个把数往数组开头怼的序列问题。因为移动数组中元素是个非常麻烦的事情，我们在数组的左端添加 $m$ 个虚点，用来存放移动过去的东西。

我们把实际上没有放数的点设为$0$，实际上放了数的点设为$1$。

这样我们只需要查询在一个点前面有多少个$1$就可以确定它在原数组中的位置。容易发现可以使用树状数组或者线段树维护。

因为最小值只可能是$1$或者这个数原来的位置，最大值只可能在一个数移动之前或者在完成所有操作后出现，所以我们只需要m + n次查询。（每次操作查询一次，最后查询n次）

然后我们就很愉快地解决了这个问题。

代码非常好写，自认为思路比楼下小哥清晰不少。

```cpp
const int MAXN = 600005;
int n, m, mini[MAXN], maxi[MAXN], c[MAXN], pos[MAXN];
void update(int x, int v) {for(; x <= n+m; x += (x&-x)) c[x] += v;}
int query(int x) {int ans = 0;for(; x; x -= (x&-x)) ans += c[x];return ans;}
signed main()
{
	cin >> n >> m;
	For(i, 1, n) mini[i] = maxi[i] = i, pos[i] = m+i, update(pos[i], 1);
	int now = m;
	For(k, 1, m) {
		int i = read(); mini[i] = 1;
		ckmax(maxi[i], query(pos[i]));
		update(pos[i], -1); 
		pos[i] = now--;
		update(pos[i], 1);
	}
	For(i, 1, n) ckmax(maxi[i], query(pos[i]));
	For(i, 1, n) printf("%d %d\n", mini[i], maxi[i]);
    return 0;
}
```

---

## 作者：whhsteven (赞：5)

清新的一道题。

首先，容易看出，如果一个联系人发了至少一条消息，那么他的最前位置就是 $1$，否则就是他的编号（即最初排名）。

思考最后位置。个人觉得拿到这道题有两种很自然的思路，分别走就可以得到三种做法。

第一种思路是直接模拟。我们需要支持删除一个点，在最前面加入一个点以及查一个点排名三种操作。通过这三种操作求出答案是容易的，这里只说说如何支持这三种操作。

直接平衡树这样做就是第一种做法。

考虑删除一个点即其原位置后面所有点排名减 $1$，插入一个点即其插入位置后面所有点排名加 $1$。我们在最前面为 $m$ 次操作留出 $m$ 个空位，然后再依次放下 $n$ 个点并做后缀加操作，之后每次要将一个点换到最前面时，只需要将这个点从原位置删掉并做后缀减，再放到这次操作对应的空位并做后缀加。后缀加减、单点求值，树状数组上单点修改、前缀求和即可做到。这是第二种做法。

另一种思路是，一个联系人这次发消息和上次发消息之间（或第一次发消息之前）发过消息的不同联系人数，就是这个人相对于排名 $1$（或初始排名）的偏移量。这是很典型的二维数点问题。这样做就是第三种做法。

本人很快想到的是二维数点做法，和同学交流后实现的是树状数组模拟的做法。[参考实现](/paste/7x0q6dwj)

---

## 作者：米奇 (赞：3)

## 简单思维+数据结构

#### 1.首先发现x的最小值一定是x或1（x出现过就为1，否则为x）

#### 2.然后我们发现x最大值要么是x，要么是出现x 之前的 x所在位置。这个我们直接用线段树维护每个值的位子即可。相当于对于一个数，他会把比他大的数都加1。修改某个数的位子，就先消除这个数之前的+1，然后把他放到最前，在把后面的数加1。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define next Next
#define gc getchar
//#define int long long
const int N=1e6+5;
int n,m,mi[N],ma[N],pos[N],tree[N*4],lazy[N*4];
//char buf[1<<21],*p1=buf,*p2=buf;
//inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
inline int read()
{
    int ret=0,f=0;char c=gc();
    while(!isdigit(c)){if(c=='-')f=1;c=gc();}
    while(isdigit(c)){ret=ret*10+c-48;c=gc();}
    if(f)return -ret;return ret;
}
void pushdown(int nod)
{
	tree[nod*2]+=lazy[nod];
	tree[nod*2+1]+=lazy[nod];
	lazy[nod*2]+=lazy[nod];
	lazy[nod*2+1]+=lazy[nod];
	lazy[nod]=0;
}
void change(int nod,int l,int r,int L,int R,int val)
{
	if(l==L&&r==R)
	{
		tree[nod]+=val;
		lazy[nod]+=val;
		return;
	}
	pushdown(nod);
	int mid=(l+r)/2;
	if(R<=mid)change(nod*2,l,mid,L,R,val);
	else if(L>mid)change(nod*2+1,mid+1,r,L,R,val);
	else{
		change(nod*2,l,mid,L,mid,val);
		change(nod*2+1,mid+1,r,mid+1,R,val);
	}
	tree[nod]=tree[nod*2]+tree[nod*2+1];
}
int find(int nod,int l,int r,int x)
{
	if(l==r)return tree[nod];
	pushdown(nod);
	int mid=(l+r)/2;
	if(x<=mid)return find(nod*2,l,mid,x);
	else return find(nod*2+1,mid+1,r,x);
}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)mi[i]=ma[i]=i;
	for(int i=1;i<=n;i++)change(1,0,n+m,pos[i]=i+m,n+m,1);
	for(int i=1;i<=m;i++)
	{
		int x=read();
		mi[x]=1;
		ma[x]=max(ma[x],find(1,0,n+m,pos[x]));
		change(1,0,n+m,pos[x],n+m,-1);
		pos[x]=m-i;
		change(1,0,n+m,pos[x],n+m,1);
	}
	for(int i=1;i<=n;i++)ma[i]=max(ma[i],find(1,0,n+m,pos[i]));
	for(int i=1;i<=n;i++)printf("%d %d\n",mi[i],ma[i]);
	return 0;
}
/*
发现如果一个数x没有出现，那么最小值一定是x
出现了，最小值就是1
最大值要么是x，要么是出现x前的值，这个我们线段树维护一下即可，区间加，单点查 
*/
```

---

## 作者：V1mnkE (赞：2)

小清新 ds 题，首先想到 $i$ 的位置最小值显然是 $1$ 或者 $i$，然后只需要考虑位置最大值怎么求。

位置其实就是 $pos_i$ 左边的数字个数，直接在原数组上删除和插入很难维护，那可以维护一个数据结构，在 $1$ 的左边加上 $m$ 个空点，把放了数的位置设为 $1$，没放数的位置设为 $0$。第 $i$ 次操作把原来位置的值 $-1$，位置 $m-i+1$ 的值 $+1$，然后查询前缀和就可以知道这个数现在的位置。

最大值只可能在每次这个数被移动前或全部操作完成后出现，所以只需要 $n+m$ 次查询，$2n$ 次修改，可以接受。

综上，我们要维护一个数据结构，支持单点修改，区间查询，那么线段树和树状数组都可以做。

```cpp
#include<bits/stdc++.h>
#define ls o<<1
#define rs o<<1|1
using namespace std;
const int maxn=6e5+5;
int T;
int n,m,q[maxn>>1],ans;
int t[maxn<<2];
void pushup(int o){
	t[o]=t[ls]+t[rs];
	return ;
}
void update(int o,int l,int r,int pos,int val){
	if(l==r){
		t[o]+=val;
		return ;
	}
	int mid=l+r>>1;
	if(pos<=mid)update(ls,l,mid,pos,val);
	else update(rs,mid+1,r,pos,val);
	pushup(o);
}
void query(int o,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		ans+=t[o];
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid)query(ls,l,mid,x,y);
	if(y>mid)query(rs,mid+1,r,x,y);
	return ;
}
int mn[maxn>>1],mx[maxn>>1],pos[maxn>>1],cnt;
int main(){
	T=1;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			pos[i]=i+m;
			update(1,0,n+m,i+m,1);
			mn[i]=mx[i]=i;
		}
		cnt=m;
		for(int i=1;i<=m;i++){
			cin>>q[i];
			mn[q[i]]=1;
			ans=0;
			query(1,0,n+m,0,pos[q[i]]);
			mx[q[i]]=max(mx[q[i]],ans);
			update(1,0,n+m,pos[q[i]],-1);
			pos[q[i]]=cnt;
			cnt--;
			update(1,0,n+m,cnt+1,1);
		}
		for(int i=1;i<=n;i++){
			ans=0;
			query(1,0,n+m,0,pos[i]);
			mx[i]=max(mx[i],ans);
		}
		for(int i=1;i<=n;i++){
			cout<<mn[i]<<' '<<mx[i]<<endl;
		}
	}
}

```


---

## 作者：syksykCCC (赞：2)

我们将答案分为两部分 $minn_i, maxx_i$，分别表示 $i$ 最靠前的位置和最靠后的位置。

## 计算 $minn$

这一部分是很好求的，因为，如果 $a$ 中出现了 $i$，那么 $minn_i$ 就必然是 $1$ 了（也就是 $i$ 刚发来消息时位置最靠前）。

如果 $i$ 从来没有发来消息的话，那 $minn_i$ 就是 $i$ 了，因为它一开始就在 $i$ 的位置，后来位置只可能往后，不可能往前。

## 计算 $maxx$

首先，我们来回忆一下自己收到信息时的场景。

* $i$ 的信息来了，$i$ 跳到了最前面；
* 收到另一条信息（比如是 $j$ 发来的），那 $i$ 到了第二位；
* 又收到了一条信息（当然，不是 $i$ 发来的）：
	* 如果还是 $j$ 发来的，那 $i$ 依然在第二位；
	* 如果不是 $j$ 发来的，那 $i$ 就到了第三位。
* （若干信息……）
* 又收到了 $i$ 的信息，$i$ 回到了最前面。

所以，我们发现，$i$ 的位置一定在他自己发来信息之前达到最大值！

也就是说，$i$ 的位置是这么一个函数：

![image.png](https://i.loli.net/2020/01/17/ojRUABpQgY9yaqf.png)

若干段 **单调不上升函数**！

那么，如果 $a_p = i$，$a_q = i$，并且中间没有 $i$ 了，则在 $q$ 时刻前 $i$ 的位置就是从 $a_p \sim a_{q - 1}$ 中 **不同的数的个数**。

还有一些麻烦的事情：比如 $i$ 出现了 $x$ 次，我们只处理了 $x - 1$ 个间隔的答案，那 $1 \sim$ 最先出现 $i$ 的位置，以及最后出现 $i$ 的位置 $\sim n$ 的答案怎么办呢？

后者十分容易处理：再数一遍最后出现 $i$ 的位置 $\sim n$ 的不同的数字的个数即可。

前者我们不妨将上图中所示的第一段函数反向延长，使得其位置为 $1$（此时的 $x$ 坐标为 $-i + 1$），然后我们能不能构造一段新的 $a$，插在老 $a$ 的前面，使得达到我们想要的目的呢？

很显然，前面补上 $n \sim 1$ 这个长度为 $n$ 的序列就行了，然后对于原序列中最先出现 $i$ 的位置，只要数它和这个新添加的 $i$（$n \sim 1$ 的序列中肯定有 $i$） 之间的不同的数字的个数即可。

考虑怎么统计不同的数字的个数。

如果采取莫队的方法，类比于 [[国家集训队]数颜色](https://www.luogu.com.cn/problem/P1903)，那时间复杂度是根号的，很悬。（但好像出题人 @pikmike 有意放这种做法过？）

考虑不带修改，那么就是可以用树状数组维护，类比于 [[SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)，可以在一个 $\log$ 的时间复杂度内解决这个问题！

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int n, m, cnt, a[N << 1], minn[N], maxx[N], lst[N];
struct tree_array // 树状数组相关 
{
#define lowbit(x) x & -x
	int o[N << 1];
	tree_array() { memset(o, 0, sizeof o); }
	int query(int p)
	{
		int res = 0;
		for(; p; p -= lowbit(p)) res += o[p];
		return res;
	}
	void modify(int p, int v)
	{
		for(; p <= n + m; p += lowbit(p)) o[p] += v;
	}
} tr;
struct qry // 询问 
{ 
	int v, l, r; // 因为要离线，v 表示这个询问的结果用来更新 maxx[v] 
	bool operator < (const qry &oth) const { return r < oth.r; }
} q[N << 1];
void add_query(int v, int l, int r) { q[++cnt] = (qry){v, l, r}; }
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) a[n - i + 1] = i; // 构造 a 
	for(int i = 1; i <= m; i++) cin >> a[i + n];
	for(int i = 1; i <= n; i++) minn[i] = maxx[i] = i;
	for(int i = n + 1; i <= n + m; i++) minn[a[i]] = 1;
	for(int i = 1; i <= n + m; i++)
	{
		if(!lst[a[i]]) lst[a[i]] = i;
		else
		{
			add_query(a[i], lst[a[i]] + 1, i); // 添加两两之间的询问（自然包括了构造的部分） 
			lst[a[i]] = i;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(a[n + m] == i) continue; // 添加到末尾的询问 
		add_query(i, lst[i], n + m);
	}
	memset(lst, 0, sizeof lst);
	sort(q + 1, q + cnt + 1);
	
	// 处理离线后的每个询问 
	int now = 1;
	for(int i = 1; i <= cnt; i++)
	{
		for(; now <= q[i].r; now++)
		{
			if(lst[a[now]]) tr.modify(lst[a[now]], -1);
			lst[a[now]] = now;
			tr.modify(now, 1);
		}
		maxx[q[i].v] = max(maxx[q[i].v], tr.query(q[i].r) - tr.query(q[i].l - 1));
	}
	
	for(int i = 1; i <= n; i++) cout << minn[i] << ' ' << maxx[i] << endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1288E)

[CF](https://codeforces.com/problemset/problem/1288/E)

### 题意

不断进行把一个数组中的一个数字插入数组开头，初始数组顺序排列，求出每个数字出现位置的最小值和最大值。

### 分析

先对于每个数字分析最小值。假设这个数字为 $x$，可以发现，如果我们进行过把这个数字插入数组开头的操作，那么最小值就是 $1$，否则最小值就是其初始位置 $x$。

比较复杂的是最大值，对于每一个数字，我们每把一个后面的数字插入数组开头，最大值就增加 $1$，然而，将其前面的数字插入数组开头并不会改变其最大值。

我们把所有的操作记为一个插入序列。

假设一个数字在插入序列的第 $l$ 个，此时，它在开头，所有数字都在它后面。随着别的数字的不断插入，它的位置会不断地后移，知道它再一次地被插到开头，此时的插入序列位置记为 $r$，**在这个过程中其最大位置就是区间 $[l,r]$ 中的不重复数字个数。** 其实这也不难理解，因为被插入到其前面的数字再次插入不会改变其位置。

但有些数字初始不在开头，我们在插入序列前插入一段 $n,n-1,\dots,3,2,1$ 的序列，即倒序向前插入所有数字，这样，每个数字都在开头出现过，就完美地解决了上述问题。

所以，我们从前到后遍历插入序列，并求出这个数字上次在插入序列中出现的位置到这个位置的区间不重复数字个数，更新答案即可。

注意在最后，我们再次统计一下每个数字上次出现位置到结尾的区间不重复数字个数，更新答案。

至于区间不重复数字个数的求法，我们可以用树状数组维护后缀和，每次在这一个位置 $+1$，在上一次出现的位置 $-1$。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define N 300010
int a[N],b[N],ans[N][2],n,m;
struct Tree
{
	int sum[N<<1];
	inline void update(int x,int y) 
	{
		while(x)
		{
			sum[x] += y;
			x -= x & -x;
		}
	}
	inline int query(int x)
	{
		int ret = 0;
		while(x <= n+m)
		{
			ret += sum[x];
			x += x & -x;
		}
		return ret;
	}
}tree;
int main()
{
	scanf("%d%d",&n,&m);
	F(i,1,n) 
	{
		ans[i][0] = ans[i][1] = i;
		b[i] = n-i+1;
		tree.update(i,1);
	}
	F(i,n+1,n+m)
	{
		int x;
		scanf("%d",&x);
		ans[x][0] = 1;
		tree.update(i,1);
		tree.update(b[x],-1);
		ans[x][1] = max(ans[x][1],tree.query(b[x]+1) - tree.query(i) + 1);
		b[x] = i;
	}
	F(i,1,n) ans[i][1] = max(ans[i][1],tree.query(b[i]+1) + 1);
	F(i,1,n) printf("%d %d\n",ans[i][0],ans[i][1]);
	return 0;
}
```
### 写在后面

人类文明的发展史，就是知识的传承史。从西汉造纸术的发明，到元朝活字印刷的出现，再到现代以来电子计算机的逐渐推广，知识得以更方便地传播。我写了 $30$ 篇题解发现——写题解，不仅仅是为了记录自己的学习过程，也是为了分享与交流自己的独特见解。洛谷的题解功能，也营造了开放、包容的学术分气。在学习的过程中，摒弃闭门造车的挂念，积极交流、深度互动，让知识不断传承。

---

## 作者：UnyieldingTrilobite (赞：1)

这个题……我也不知道为什么要手写数据结构什么的啊……真的不知道啊……

首先我们观察到一个性质：在一轮操作中，如果一个数不是被提到首位的那一个，那它的位置不会向前移动。这是显然的，分在提前的元素前还是后就可以了。

这样的话最小值就已经可以求了，
~~如果不会的话请找几道水红题切了然后冷静一下~~。对于第 $x$ 个元素，如果被提前过，那么就是 $1$，反之就是 $x$，是不是很无聊（

对于最大值的话，我们如果每一次提前之前都对每个数更新一次，复杂度过高。但是我们发现，如果这一次数 $x$ 没有被提前，那么可以先咕了不更，等下再更不会出问题（因为直到 $x$ 被提前，它的位置都是不会向前的）。特殊地，所有操作结束后对每个数再重新计算一下，免得出问题（问题在哪留给读者自行思考，~~如果看不出的话请找几道水红题切了然后冷静一下~~）。

然后就只需要维护一个数据结构支持把一个数提前，以及查一个数的排名就好了。我们可以直接用 pbds 的平衡树跑过去。没有任何要注意的点。

```cpp
#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
template <typename T, typename U = null_type>
using rbt = tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
constexpr int N = 3e5 + 9;
rbt<int> st;
rbt<int>::iterator its[N];
int n, m, ansmin[N], ansmax[N];
signed main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) its[i] = st.insert(ansmin[i] = i).first;
  for (int a, i = 0; i < m; ++i) {
    cin >> a, ansmin[a] = 1;
    ansmax[a] = max(ansmax[a], (int)st.order_of_key(*its[a]) + 1);
    st.erase(its[a]), its[a] = st.insert(-i).first;
  }
  for (int i = 1; i <= n; ++i)
    ansmax[i] = max(ansmax[i], (int)st.order_of_key(*its[i]) + 1);
  for (int i = 1; i <= n; ++i) cout << ansmin[i] << ' ' << ansmax[i] << '\n';
  return cout << flush, 0;
}
```

（开头那个 `#include <bits/extc++.h>`，CF 是能跑得过去的，洛谷也能（好吧 OJ 上基本都能），NOI Linux也能，但是我的 windows 不能，但是我处理过于是能了，所以对于读者而言有可能会出现本地 CE 的情况，并不是题解的 bug。）

以上。

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1288E Messenger Simulator](https://www.luogu.com.cn/problem/CF1288E)

# 解题思路

发现向前移的部分普通维护比较困难，因此我们考虑通过某种方式来维护这个东西。

考虑建立 $m$ 个虚点来维护，每次询问都将实点移至虚点去。这里求答案我们需要支持单点加，区间求和，可以用树状数组轻松维护。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
ll n,m;
ll pos[1000010];
ll q[1000010];
ll tree[1000010];
ll last;
ll ans1[1000010],ans2[1000010];
void add(ll x,ll y)
{
    if(x==0)
        return ;
    for(;x<=1e6+5;x+=lowbit(x))
        tree[x]+=y;
}
ll query(ll x)
{
    ll sum=0;
    for(;x;x-=lowbit(x))
        sum+=tree[x];
    return sum;
}
void solve()
{
    _clear();
    cin>>n>>m;
    last=m;
    forl(i,1,m)
        cin>>q[i];
    forl(i,1,n)
        pos[i]=m+i;
    forl(i,1,n)
        ans1[i]=ans2[i]=i;
    forl(i,1,n)
        add(pos[i],1);
    forl(i,1,m)
    {
        Max(ans2[q[i]],query(pos[q[i]]));
        add(pos[q[i]],-1);
        pos[q[i]]=last--;
        ans1[q[i]]=1;
        add(pos[q[i]],1);
    }
    forl(i,1,n)
        Min(ans1[i],query(pos[i])),
        Max(ans2[i],query(pos[i]));
    forl(i,1,n)
        cout<<ans1[i]<<' '<<ans2[i]<<endl;
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
//    cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：__yun__ (赞：0)

### 思路
如果弹到过顶部，那么最靠上的位置就是 $1$，否则为他的编号。 

最靠下的位置只可能在弹到顶部之前或最后，在每次弹到顶部前统计前面有几个人，最后再对每个人统计一遍，取最大值即可。

取 $m+n$ 个位置，用线段树维护每个位置的人数。一开始所有人都在最后 $n$ 个位置中，这 $n$ 个位置人数都为 $1$。如果第 $i$ 个发消息的人编号为 $x$，先求出 $1 \sim pos_x$ 的区间和，即为他当前的位置。随后将 $pos_x$ 减 $1$；将他的位置更新到 $m-i+1$，将他的新位置人数加 $1$。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m,pos[N],up[N],dw[N];
struct node{
	int l,r,val,lazy;
}tr[N<<3];
void pushup(int u){
	tr[u].val=tr[u<<1].val+tr[u<<1|1].val;
	return ;
}
void build(int u,int l,int r){
	if(l==r){
		tr[u]={l,r,(l>m),0};
		return ;
	}
	tr[u]={l,r,0,0};
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
	return ;
}
void pushdown(int u){
	if(tr[u].lazy){
		int l=u<<1,r=u<<1|1;
		tr[l].val+=(tr[l].r-tr[l].l+1)*tr[u].lazy;
		tr[r].val+=(tr[r].r-tr[r].l+1)*tr[u].lazy;
		tr[l].lazy+=tr[u].lazy;
		tr[r].lazy+=tr[u].lazy;
		tr[u].lazy=0; 
	}
	return ;
}
void update(int u,int l,int r,int val){
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].val+=(tr[u].r-tr[u].l+1)*val;
		tr[u].lazy+=val;
		return ;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=l) update(u<<1,l,r,val);
	if(mid<r) update(u<<1|1,l,r,val);
	pushup(u);
	return ;
}
int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r){
		return tr[u].val;
	}
	pushdown(u);
	int ret=0;
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=l) ret+=query(u<<1,l,r);
	if(mid<r) ret+=query(u<<1|1,l,r);
	pushup(u);
	return ret;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		pos[i]=m+i;
		up[i]=i;
		dw[i]=i;
	}
	build(1,1,m+n); 
	int x;
	for(int i=1;i<=m;i++){
		cin>>x;
		up[x]=1;
		dw[x]=max(dw[x],query(1,1,pos[x]));
		update(1,pos[x],pos[x],-1);
		pos[x]=m-i+1;
		update(1,pos[x],pos[x],1);
	}
	for(int i=1;i<=n;i++){
		dw[i]=max(dw[i],query(1,1,pos[i]));
		cout<<up[i]<<" "<<dw[i]<<endl;
	}
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

一开始考虑了使用链表来维护整个过程，但是发现无法简单的维护排名。

当前位置如何简单的计算？当然是统计它前面有多少个数。将整个过程抽象为有 $n+m$ 个格子，初始只有后 $n$ 个格子有数，然后每次删掉一个数，在前面的格子把这个数重新写上。

利用树状数组可以简单维护格子中的数的数量，然后记录每个数的位置，就可以直接计算排名。

什么时候更新答案呢？移动一个数时，只有这个数的最小位置会发生改变（变为 $1$），那么在移动之前就可能是它的最大位置。所有操作进行完之后再次计算所有数的最大位置就能求出答案。


```cpp
#include <bits/stdc++.h>
using namespace std; 

int n, m, a[600005], pos[300005]; 
int mn[300005], mx[300005]; 
int C[600005]; 

void add(int x, int k) { for (; x <= n + m; x += x & -x) C[x] += k; }
int qans(int x) { int r = 0; for (; x; x -= x & -x) r += C[x]; return r; }

int main(void) {
    scanf("%d%d", &n, &m); 
    for (int i = m + 1; i <= m + n; ++i) a[i] = i - m, add(i, 1), pos[i - m] = i; 
    for (int i = 1; i <= n; ++i) mn[i] = mx[i] = i; 
    for (int _ = 1; _ <= m; ++_) {
        int x; scanf("%d", &x); mx[x] = max(mx[x], qans(pos[x])); 
        add(pos[x], -1); pos[x] = m - _ + 1; add(pos[x], 1); mn[x] = 1; 
    }
    for (int i = 1; i <= n; ++i) mx[i] = max(mx[i], qans(pos[i])); 
    for (int i = 1; i <= n; ++i) printf("%d %d\n", mn[i], mx[i]); 
    return 0; 
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1288E)
## 思路
这个题比较奇妙，乍一看似乎是道水题，但是我就被坑了。

我们设 $up_i$ 表示 $i$ 最靠上的位置，$down_i$ 表示 $i$ 最靠下的位置，$rank_i$ 表示 $i$ 当前的排名。

首先这个题需要用到线段树，相信各位读者都发现了，接着，我们发现了一个显然的性质，那就是若一个好友出现在了消息列表中，这个好友的 $up$ 值显然为 $1$，$down$ 值需要与当前的 $rank$ 取 $\max$，接着我们把 $rank_i<rank$ 的 $i$ 的位置全部加上 $1$，然后把 $rank$ 变成 $1$。

然后我就码出了一个线段树：[提交记录](https://codeforces.com/problemset/submission/1288/174967131)。

但是，我们会惊讶地发现这个程序 $\verb!TLE!$ 了，为什么呢，因为我的线段树在更新的时候访问的并不是一段连续的区间，具体地，我的线段树的下标是 $i$，值存的才是 $rank_i$，而我们修改是按照 $rank_i$ 来的，所以访问了多段区间，复杂度退化为 $O(n^2 \log n)$，甚至连暴力都不如。

通过反思原来线段树存在的问题，我们可以通过一些小 $\verb!trick!$ 优化掉。我们最终的目标就是让修改的区间是一个连续的区间，所以我们不妨以 $rank_i$ 为下标。

我们设 $loc_i$ 表示 $i$ 不能修改的区间为 $loc_i$ 至 $n+m$，即区间 $loc_i$ 至 $n+m$ 内的数的 $rank$ 均大于等于 $rank_i$。初始我们把每个 $loc_i$ 赋值为 $i+m$，为的是不与我们之后修改 $loc_i$ 的操作冲突。

每当我们扫到一个 $i$，设 $x_i$ 为当前要处理的数，我们给 $x_i$ 一个新的 $loc_{x_i}$，记为 $m-i$，我们需要 $\verb!update!$ 的区间即为 $m-i$ 至 $loc_{x_i}-1$，为了避免 $\verb!RE!$，我们可以分成两个做。这里的 $loc_{x_i}$ 指的是修改之前的。

接下来说明一下为什么要这么设，因为显然后面的 $x_i$ 是要去更新前面的 $x_i$ 的，所以我们设成 $m-i$ 更容易修改。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=6e5+10;
int up[N],down[N],loc[N];
struct Segment_Tree{
	int c[N<<2],lazy[N<<2];
	#define ls (x<<1)
	#define rs (x<<1|1)
	#define mid ((l+r)>>1)
	inline void pushdown(int x){
		lazy[ls]+=lazy[x];lazy[rs]+=lazy[x];
		c[ls]+=lazy[x];c[rs]+=lazy[x];
		lazy[x]=0;
	}
	inline void update(int x,int l,int r,int ll,int rr,int v){
		if (ll<=l && r<=rr){c[x]+=v,lazy[x]+=v;return;}
		pushdown(x);
		if (ll<=mid) update(ls,l,mid,ll,rr,v);
		if (mid<rr) update(rs,mid+1,r,ll,rr,v);
		c[x]=c[ls]+c[rs];
	}
	inline int query(int x,int l,int r,int p){
		if (l==r) return c[x];
		pushdown(x);
		if (p<=mid) return query(ls,l,mid,p);
		else return query(rs,mid+1,r,p);
	}
}T;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for (int i=1;i<=n;++i) up[i]=down[i]=i;
    for (int i=1;i<=n;++i) loc[i]=i+m,T.update(1,1,n+m,loc[i],n+m,1);
    for (int i=1;i<=m;++i){
    	int x;cin>>x;up[x]=1;
    	down[x]=max(down[x],T.query(1,1,n+m,loc[x]));
    	T.update(1,1,n+m,loc[x],n+m,-1);loc[x]=m-i;
    	T.update(1,1,n+m,loc[x],n+m,1);
    }
    for (int i=1;i<=n;++i) down[i]=max(down[i],T.query(1,1,n+m,loc[i]));
 	for (int i=1;i<=n;++i) cout<<up[i]<<' '<<down[i]<<'\n';
    return 0;
}
```


---

## 作者：_edge_ (赞：0)

简单的数据结构题。

分析一下题意，可以发现，最小和最大是两个独立的情况尝试分开来讨论。

对于最小的情况，这种情况下，我们只需要判断它是否移到了第一个，如果有的话则是第一个，否则就是它的初始位置，因为后面的操作不会把它往上推。

对于最大的情况，这种情况就稍微有点麻烦了。

分开来考虑两段的情况，一个是 $1$ 到 第一次出现的位置，另外一个是两次出现位置之间的间隔。

第二种情况会比较好做一点，就是数一下区间里面出现过了多少本质不同的数。

区间数颜色这个是个经典问题，可以尝试用 HH 的项链来做，就是离线然后把最接近右端点的视为 $1$，其余视为 $0$ 即可。

第一种情况的话我们会发现它本质上是多了 $1$ 到 $i-1$ 这些数在他的前面，我们在查询这个区间颜色的时候，把 $1$ 到 $i-1$ 中的数出现过的减掉即可。

感觉还是挺好写的吧，建议读者自行写。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
const int INF=1e6+5;
vector<int> v[INF];
int n,m,a[INF],sum1[INF],la[INF];
int ans[INF],pre[INF],res[INF];
struct BIT{
	int tree[INF];
	void add(int x,int y) {for (int i=x;i<=3e5;i+=i&-i) tree[i]+=y;}
	int query(int x) {int sum=0;for (int i=x;i;i-=i&-i) sum+=tree[i];return sum;}
}T1,T2;
struct _node_edge{
	int to_,next_,v1,v2;
}edge[INF<<1];
int head[INF],tot;
void add_edge(int x,int y,int v1,int v2) {
	edge[++tot]=(_node_edge){y,head[x],v1,v2};
	head[x]=tot;return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=m;i++) cin>>a[i];
	for (int i=1;i<=m;i++) v[a[i]].pb(i);
	for (int i=1;i<=n;i++) v[i].pb(m+1);
	for (int i=1;i<=n;i++) {
		if (v[i].size()>1) sum1[i]=1;
		else sum1[i]=i;
	}
	for (int i=1;i<=n;i++) {
		int len=v[i].size();
		for (int j=0;j<len;j++) {
			if (j==0) add_edge(v[i][0],0,1,i),add_edge(v[i][0],0,2,i);
			else add_edge(v[i][j],v[i][j-1],0,i);
		}
	}
	
	for (int x=1;x<=m+1;x++) {
		if (x!=m+1) {
			if (la[a[x]]) T1.add(la[a[x]],-1),T1.add(x,1),la[a[x]]=x;
			else T1.add(x,1),la[a[x]]=x,T2.add(a[x],1);
		}
		for (int i=head[x];i;i=edge[i].next_) {
			int v=edge[i].to_,v1=edge[i].v1,v2=edge[i].v2;
			if (!v1) ans[v2]=max(ans[v2],T1.query(x-1)-T1.query(v));
			else if (v1==1) res[v2]-=T2.query(v2);
			else res[v2]+=T1.query(x);
//			cout<<v2<<" "<<T1.query(x)-T1.query(v)<<" "<<v<<" endl\n"; 
		}
	}
	
	for (int i=1;i<=n;i++) {
		cout<<sum1[i]<<" "<<max(res[i]+i,ans[i]+1)<<"\n";
//		cout<<ans[i]<<" ?\n";
	}
	return 0;
}
```

这里给出数据生成器，方便读者进行对拍。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
std::mt19937 mt_rand(std::chrono::system_clock::now().time_since_epoch().count());
int gen(int l,int r) {return l+mt_rand()%(r-l+1);}
int Map[1005][1005];
signed main()
{
	int n=gen(1,5),m=gen(1,5);
	cout<<n<<" "<<m<<"\n";
	for (int i=1;i<=m;i++) cout<<gen(1,n)<<" ";
	cout<<"\n";
	return 0;
}
```



---

## 作者：Albedo (赞：0)

### Preface

这道题的trick如果要我自己想，我一定想不到。

### Description

一开始为 $ 1,2,3..n $ 的排列有 $ m $ 的变化，每次变化把 $ a_i $ 放到排列的最前面，然后问你每个数能达到的最前面的位置和最后面的位置。

### Method

#### 最前面

容易发现，如果一个 $ i $ 在 $ m $ 个数出现过，那么他就是 $ 1 $ 因为他到达过 $ 1 $，否则是 $ i $，因为他只会往后，不会往前，所以最小是 $ i $，就是一开始的位置。

#### 最后面

这个比较难做，我们可以把问题进行转化，如果一个数在 $ m $ 个数中出现过，那么就判断相邻两个 $ a_i $ 中有多少个不同就可以了，因为如果有一个不同的，那么他一定是在 $ a_i $ 的后面，因为 $ a_i $ 一开始是在最前面的，如果有不同的那么一定在他的后面，如果有相同的，那么因为之前已经移到 $ a_i $的前面，所以不会造成影响，当然还要判断最后一个对于一个 $ i $，他在 $ m $ 中出现的最后一个位置到 $ m $ 的最后一个位置所出现的不同的数的数量。但是现在还有一个问题，就是这个 $ i $ 在 $ m $ 中出现前的操作怎么办呢，这个就是我想不到的trick，我们可以一开始的排列是做从 $ n $ 开始到 $ 1 $ 一次插入，这样子形成的排列和 $ 1,2,3 \cdot \cdot \cdot n $ 是等价的，然后就可以做了，太高了。

#### 如何判断区间内有几个不同的数

详见HH的项链，这里不再赘述（因为是模板呀）。

### Code

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read()			
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
struct hxz{
	int l,r,id;
};
hxz b[2000000];
int f[1001000],apr[2000000],e[2000000],a[2000000],c[2000000],exist[2000000];
int x,mm,n,m,i,j,ans,lft;
int lowbit(int x)
{
	return x & -x;
}
bool cmp(hxz a,hxz b)
{
	return a.r<b.r;
}
void add(int x,int y)
{
	for (;x<=m;x+=lowbit(x))
	    e[x]+=y;
}
int query(int x)
{
	int ans=0;
	for (;x;x-=lowbit(x))
	    ans+=e[x];
	return ans;
}
int main()
{
	n=read();mm=read();
	for (i=n;i>=1;i--) apr[i]=n-i+1,a[n-i+1]=i;
	for (i=1;i<=mm;i++)
	    {
	    	x=read();a[n+i]=x;f[x]=1;
	    	m++;b[m].l=apr[x];b[m].r=n+i-1;b[m].id=x;apr[x]=n+i;
		}
	for (i=1;i<=n;i++)
	     {
	     	m++;b[m].l=apr[i];b[m].r=mm+n;b[m].id=i;
		 }
	sort(b+1,b+m+1,cmp);
	lft=1;
	for (i=1;i<=m;i++)
	    {
	    	for (j=lft;j<=b[i].r;j++)
	    	    {
	    	    	if (exist[a[j]]!=0) add(exist[a[j]],-1);
	    	    	exist[a[j]]=j;
	    	    	add(exist[a[j]],1);
				}
			lft=b[i].r;
			c[b[i].id]=max(c[b[i].id],query(b[i].r)-query(b[i].l-1));
		}
	for (i=1;i<=n;i++) c[i]=max(c[i],i);
	for (i=1;i<=n;i++) if (f[i]==0) f[i]=i;
	for (i=1;i<=n;i++)
	  printf("%d %d\n",f[i],c[i]);
	return 0;
}
```

---

## 作者：Star_Cried (赞：0)

## CF1288E Messenger Simulator

### 题意

一个长度为 $n$ 的好友列表，自上而下依次是 $1∼n$，你依次收到了 $m$ 条消息，第 $i$ 条消息是 $a_i$ 发来的，这时 $a_i$ 会跳到会话列表的最上面，其它的按原顺序顺延，求 $1∼n$ 每个好友最靠上的位置和最靠下的位置。

~~用过手机吧~~

### 思路

最靠上的位置如果不会请现在停止阅读（微笑）

先不考虑原序列，就考虑相同好友的相邻两次消息，会发现时间段内该好友最下的位置就是区间内**不同数字的数目+1**。

想亿想，为什么？

想通了的话，考虑加上原序列，实际上就是将空列表**从n到1依次插入列表**，于是就可以转化成我们刚才的问题，即求两个相邻的相同好友区间的不同数字数目+1取最大值。

想亿想，为什么？

于是问题转化。如何快速求给定多个区间的区间内不同数字数目？

这里我用的方法是树状数组，具体做法可参考“HH的项链”一题。这里不再赘述。

### 实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=3e5+10;
	int n,m,a[maxn<<1],tot,cur[maxn],nxt[maxn<<1],cnt,ans[maxn];
	bool mark[maxn];
	struct seg{
		int l,r,id;
		inline bool operator < (const seg &zp) const{return l<zp.l;}
	}q[maxn<<1];
	struct BIT{
		int c[maxn<<1];
		inline void insert(int x,int k){for(;x<=tot;x+=x&-x) c[x]+=k;}
		inline int query(int x){int ans=0;for(;x;x-=x&-x)ans+=c[x];return ans;}
	}S;
	inline void work(){
		n=read(),m=read();
		for(int i=n;i;i--) a[++tot]=i,cur[tot]=n+m+1;
		for(int i=1;i<=m;i++) a[++tot]=read();
		for(int i=tot;i;i--){
			if(cur[a[i]]>i+1) q[++cnt]=(seg){i+1,cur[a[i]]-1,a[i]};
			nxt[i]=cur[a[i]];
			cur[a[i]]=i;
		}
		for(int i=1;i<=tot;i++){
			if(!mark[a[i]]) S.insert(i,1);
			mark[a[i]]=1;
		}
		for(int i=n+1;i<=tot;i++) mark[a[i]]=0;
		sort(q+1,q+1+cnt);
		for(int i=1,now=1;i<=cnt;i++){
			while(now<=tot and now<q[i].l) S.insert(now,-1),S.insert(nxt[now],1),now++;
			ans[q[i].id]=max(ans[q[i].id],S.query(q[i].r)-S.query(q[i].l-1));
		}
		for(int i=1;i<=n;i++)printf("%d %d\n",mark[i]?i:1,ans[i]+1);
	}
}
signed main(){
	star::work();
	return 0;
}
```

---

