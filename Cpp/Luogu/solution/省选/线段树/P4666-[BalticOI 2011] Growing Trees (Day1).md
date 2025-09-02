# [BalticOI 2011] Growing Trees (Day1)

## 题目描述

给出一个长度为 $N$ 的数组 $a$，数组中每个数的取值范围均为 $[1,N]$（没说互不相同）。
接下来有 $M$ 组操作，操作分为两种：
1. $\texttt{F}\:\:c\:\:h$  
将满足 $a[i] \ge h$ 的所有 $a[i]$ 中最小的 $c$ 个数都 $+1$；
2. $\texttt{C}\:\:max\:\:min$  
输出满足 $min \le a[i] \le max$ 的 $a[i]$ 的个数。

## 样例 #1

### 输入

```
5 7
1 3 2 5 2
F 2 1
C 3 6
F 2 3
C 6 8
F 2 1
F 2 2
C 3 5```

### 输出

```
3
0
5```

# 题解

## 作者：柳易辰 (赞：20)

## Start
前置知识：[树状数组](https://www.luogu.com.cn/problem/P3368)

区间修改，单点查询。

&nbsp;
## 1.思路
看到各个大佬们用的都是 FHQ、Splay、权值线段树等高级数据结构，我自愧弗如。

但是我可以用简单基本的算法~~吊打~~：树状数组。

现在所有通过的[程序](https://www.luogu.com.cn/record/list?pid=P4666&orderBy=1&status=&page=1)中，最优解速度第 4（没有开 O2，快读等优化），空间 & 码量都是最小的。

&nbsp;
## 2.建树

根据差分，树状数组 $b_i=a_i-a_{i-1}$，先把 $a_i$ 数组排序，然后依次单点修改：`add(i, a[i] - a[i - 1])`。但是我们在查询中就会有一个问题：我们无法知道 $\min$ 和 $\max$ 在 $b$ 这个**不下降数组**的位置？于是我们写两个二分函数 `left(x)` 和 `right(x)`。

`left`：查询 `sum(i) >= x` 时 $i$ 的最大值，即最后一个前缀和 $\ge x$ 的位置。

`right`：查询 `sum(i) <= x` 时 $i$ 的最小值，即第一个前缀和 $\le x$ 的位置。

这两个函数在修改中必不可少。  

&nbsp;
## 3.修改
查询很简单，前面说了，考虑如何修改。

修改最重要的就是有一些高度相同的树，只有**一部分**修改，另一部分不修改（样例第一个输出），如何处理？

假设修改操作的两个输入分别是 $x,y$，那么我们先算出找到要修改的数的值得区间 $[x,s]$，`s = sum(x + left(y) - 1)`，很好理解。

接下来分成两段处理，一段是值在 $[x,s-1]$ 中的，另一段是值为 $s$ 的。具体代码：

```cpp
const int z(left(y)), s(sum(x + z - 1)), l(left(s)), r(right(s));
add(z, 1), add(l, -1);
add(l + r - x - z + 1, 1), add(r + 1, -1);
```

&nbsp;
## End
特判：
1. 查询的范围在 $a$ 中最大值与最小值之外
2. 需要修改的数的数量大于符合范围的数的数量

[代码](https://www.luogu.com.cn/paste/85efkn8x)

---

## 作者：_luanyi_ (赞：18)

平衡树好题，考验细节（我 `getval` 函数没 `push_down` 调了两个小时……）。  
本题解给出 fhq-treap 的做法。  
PS：本人的 fhq 将权值相同的结点分开存储，split 时 $< key$ 的为左子树，$\geqslant key$ 的为右子树。  
我们依次考虑每个操作应当如何处理。  
先考虑查询。

***

$\texttt{C}\ mn\ mx$

这个相对比较简单，分别将 $mn$ 与 $mx+1$ 作为 $key$ 分裂即可。

***

$\texttt{F}\ c\ h$

我们考虑先将 $\geqslant key$ 的部分分裂出来。  
对于这部分，因为会有重复的元素出现，所以不能直接查询第 $c$ 大的元素然后分裂，应当根据排名分裂（再写一个分裂函数，我名字取作 splitt）。设分裂以后左子树为 $\text{l}$，右子树为 $\text{r}$。  
如果我们将 $\text{l}$ 的 lazytag 直接增加，我们会发现无法将 $\text{l}$ 和 $\text{r}$ 合并起来（因为要满足 $\text{l}$ 中所有元素都 $\leqslant \text{r}$ 中所有元素）。  
考虑人类智慧。  
我们设之前根据排名分裂时该分裂的位置的元素值为 $val$。  
不难发现 $\text{l}$ 中最大的元素为 $val+1$，而 $\text{r}$ 中最小的元素 $\geqslant val$。  
于是我们可以将 $\text{l}$ 根据 $val+1$ 分裂，设分裂成了 $\text{ll}$ 和 $\text{lr}$。  
则 $\text{lr}$ 中的元素要么为空，要么都是 $val+1$ 。  
我们再将 $\text{r}$ 根据 $val+2$ 分裂，设分裂成了 $\text{rl}$ 和 $\text{rr}$。  
则 $\text{rl}$ 中的元素 $x$ 一定满足 $val \leqslant x \leqslant val+1$。
综合一下，我们可以得到 $\text{ll} \leqslant \text{rl} \leqslant \text{lr} \leqslant \text{rr}$。  
依次合并即可。（做完了）

**code**  

```cpp
#include <bits/stdc++.h>
#define fq(i,a,b) for (int i = a; i <= b; i++)
using namespace std;
#define int long long
inline int rd () {//快读
	int f = 1;
	char ch = getchar ();
	while (!isdigit (ch)) {if (ch == '-') f *= -1; ch = getchar ();}
	int num = 0;
	while (isdigit (ch)) num = num * 10 + ch - '0', ch = getchar ();
	return num * f;
}
#define d rd ()

const int maxn = 100500;
struct node {//fhq节点
	int l, r, key, pri, sz, tag;
	node () {}
	node (int k) {
		l = r = 0;
		sz = 1;
		pri = rand ();
		key = k;
		tag = 0;
	}
} p[maxn]; int cnt;
int addnode (int key) {p[++cnt] = node (key); return cnt;}
void push_up (int rt) {p[rt].sz = p[p[rt].l].sz + p[p[rt].r].sz + 1;}
void push_down (int rt) {
	if (p[rt].l) p[p[rt].l].key += p[rt].tag, p[p[rt].l].tag += p[rt].tag;
	if (p[rt].r) p[p[rt].r].key += p[rt].tag, p[p[rt].r].tag += p[rt].tag;
	p[rt].tag = 0;
}

pair <int, int> split (int rt, int key) {//按权值分裂
	if (!rt) return make_pair (0, 0);
	push_down (rt);
	if (key <= p[rt].key) {
		pair <int, int> q = split (p[rt].l, key);
		p[rt].l = q.second;
		push_up (rt);
		return make_pair (q.first, rt);
	} else {
		pair <int, int> q = split (p[rt].r, key);
		p[rt].r = q.first;
		push_up (rt);
		return make_pair (rt, q.second);
	}
}

pair <int, int> splitt (int rt, int k) {//按排名分裂
	push_down (rt);
	if (k <= p[p[rt].l].sz) {
		pair <int, int> q = splitt (p[rt].l, k);
		p[rt].l = q.second;
		push_up (rt);
		return make_pair (q.first, rt);
	} else if (k == p[p[rt].l].sz + 1) {
		int rr = p[rt].r;
		p[rt].r = 0;
		push_up (rt);
		return make_pair (rt, rr);
	} else {
		pair <int, int> q = splitt (p[rt].r, k - p[p[rt].l].sz - 1);
		p[rt].r = q.first;
		push_up (rt);
		return make_pair (rt, q.second);
	}
}

int merge (int l, int r) {//合并
	if (!l || !r) return l | r;
	push_down (l); push_down (r);
	if (p[l].pri < p[r].pri) {
		p[l].r = merge (p[l].r, r);
		push_up (l);
		return l;
	} else {
		p[r].l = merge (l, p[r].l);
		push_up (r);
		return r;
	}
}


int getval (int rt, int k) {//查询排名为k的节点的权值
	push_down (rt);
	if (k <= p[p[rt].l].sz) return getval (p[rt].l, k);
	k -= p[p[rt].l].sz + 1;
	if (!k) return p[rt].key;
	return getval (p[rt].r, k);
}

int rt;
void insert (int key) {
	pair <int, int> q = split (rt, key);
	rt = merge (q.first, merge (addnode (key), q.second));
}

int n;
signed main () {
//	srand(time(NULL));
	n = d;
	int q = d;
	fq (i, 1, n) insert (d);
	while (q--) {
		string op; cin >> op;
		if (op[0] == 'F') {
			int c = d, k = d;
			pair <int, int> q = split (rt, k);
			if (!q.second) continue;//如果没有符合条件的元素就跳过
			int vl = getval (q.second, min (p[q.second].sz, c));
			//进行若干次分裂
			pair <int, int> r = splitt (q.second, min (p[q.second].sz, c));
			p[r.first].tag++;
			p[r.first].key++;
			pair <int, int> s = split (r.first, vl + 1);
			pair <int, int> t = split (r.second, vl + 2);
			//然后合并
			rt = merge (q.first, merge (s.first, merge (merge (t.first, s.second), t.second)));
		} else {
			int mn = d, mx = d;
			pair <int, int> q = split (rt, mn);
			pair <int, int> r = split (q.second, mx + 1);
			cout << p[r.first].sz << endl;
			rt = merge (q.first, merge (r.first, r.second));
		}
	}
	return 0;
}
```


---

## 作者：agicy (赞：5)

[点此使用更佳](https://www.lu-anlai.com/oi/solution/balticoi-2011-d1t1/)。

一道简单的 Splay 题目。

题目链接：[Luogu P4666](https://www.luogu.com.cn/problem/P4666)/[LibreOJ 2630](https://loj.ac/problem/2630)/BalticOI 2011 D1T1。

当年比赛的官网链接（已挂）：https://www.boi2011.dk/ 。

# 题目

## 题目描述

给出一个长度为 $N$ 的数组 $a$，数组中每个数的取值范围均为 $[1,N]$。 接下来有 $M$ 组操作，操作分为两种：

- $\texttt{F}\quad\texttt{c}\quad\texttt{h}$

	将满足 $a[i]\geq h$ 的所有 $a[i]$ 中最小的 $c$ 个数都 $+1$；
    
- $\texttt{C}\quad\texttt{max}\quad\texttt{min}$

	输出满足 $\texttt{min}\leq a[i]\leq\texttt{max}$ 的个数。

## 数据范围

$$1\leq n,m\leq 10^5$$

## 时空限制

|题目|时间限制|空间限制|
|:-:|:-:|:-:|
|[Luogu P4666](https://www.luogu.com.cn/problem/P4666)|$$1\text{s}$$|$$250\text{MiB}$$|
|[LibreOJ 2630](https://loj.ac/problem/2630)|$$1\text{s}$$|$$256\text{MiB}$$|
|BalticOI 2011 D1T1|$$1\text{s}$$|$$256\text{MiB}$$|

# 题解

## 思路

发现这道题目要求我们维护数列，于是考虑使用数据结构。

首先用排除法：~~暴力~~、~~树状数组~~、~~线段树~~、$\text{Splay}$。

我们发现 $\text{Splay}$ 可以解决这道题目，下面就介绍一下如何用 $\text{Splay}$ 解决这道题目。

### 操作一

$$\texttt{F}\quad\texttt{c}\quad\texttt{h}$$

将满足 $a[i]\geq h$ 的所有 $a[i]$ 中最小的 $c$ 个数都 $+1$；

考虑找到 $\text{Splay}$ 中权值为 $h$ 的位置，旋转到根，再从左子树中找到排名为 $c$ 的位置，（如果左子树大小小于 $c$ 则对左子树大小取 $\min$）。再修改 $\text{tag}$即可。

### 操作二

$$\texttt{C}\quad\texttt{max}\quad\texttt{min}$$

输出满足 $\texttt{min}\leq a[i]\leq\texttt{max}$ 的个数。

找到 $\texttt{min}$ 的位置，旋转到根，再把 $\texttt{max}$ 转到根的右节点，统计根节点的右节点的左子树大小即为答案。

### 细节

另外，注意一些细节，记得插入哨兵节点（正负无穷），同时记得把不存在的节点的内部最大值（查询时用）设为 $-\infty$（我就被这里卡了）。

## 代码

$\text{Splay}$ 的渐近时间复杂度为 $\Theta(n\log_2n)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F //定义正无穷
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){ //快读
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+100;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN];

inline void Read(void){
	n=read(),m=read(); // 读入 n,m
	for(reg int i=1;i<=n;++i)
		a[i]=read(); //读入 a[]
	return;
}

struct Splay{ //Splay
	int root;
	int val[MAXN],Max[MAXN],tag[MAXN];
	int fa[MAXN],ch[MAXN][2];
	int size[MAXN];
	inline bool get(const int& x){
		return x==ch[fa[x]][1];
	}
	inline void pushup(const int& ID){
		Max[ID]=max(val[ID],max(Max[ch[ID][0]],Max[ch[ID][1]]));
		size[ID]=size[ch[ID][0]]+size[ch[ID][1]]+1;
		return;
	}
	inline int Build(const int& father,const int& l,const int& r,reg int a[]){
		if(l>r)
			return 0;
		int mid=(l+r)>>1;
		val[mid]=Max[mid]=a[mid];
		fa[mid]=father;
		size[mid]=1;
		ch[mid][0]=Build(mid,l,mid-1,a);
		ch[mid][1]=Build(mid,mid+1,r,a);
		pushup(mid);
		return mid;
	}
	inline void rotate(const int& x){
		int f=fa[x],ff=fa[f];
		reg bool wh=get(x);
		if(ff)
			ch[ff][get(f)]=x;
		fa[f]=x;
		ch[f][wh]=ch[x][wh^1];
		if(ch[f][wh])
			fa[ch[f][wh]]=f;
		fa[x]=ff;
		ch[x][wh^1]=f;
		pushup(f);
		pushup(x);
		return;
	}
	inline void add(const int& ID,const int& Val){
		val[ID]+=Val,Max[ID]+=Val,tag[ID]+=Val;
		return;
	}
	inline void pushdown(const int& ID){
		if(tag[ID]){
			if(ch[ID][0])
				add(ch[ID][0],tag[ID]);
			if(ch[ID][1])
				add(ch[ID][1],tag[ID]);
			tag[ID]=0;
		}
		return;
	}
	inline void push(const int& x){
		if(fa[x])
			push(fa[x]);
		pushdown(x);
		return;
	}
	inline void splay(const int& x,const int& goal){
		push(x);
		for(int qwq;(qwq=fa[x])!=goal;rotate(x)){
			if(fa[qwq]!=goal){
				rotate(get(x)==get(qwq)?qwq:x);
			}
		}
		if(goal==0)
			root=x;
		return;
	}
	inline int find(const int& x){
		int now=root,res=0;
		while(true){
			pushdown(now);
			if(x<=Max[ch[now][0]])
			    now=ch[now][0];
			else{
				res+=size[ch[now][0]];
				if(x<=val[now])
					return res+1;
				++res;
				now=ch[now][1];
			}
		}
		return -1;
	}
	inline int kth(reg int x){
		int now=root;
		while(true){
			pushdown(now);
			if(x<=size[ch[now][0]])
			    now=ch[now][0];
			else{
				x-=size[ch[now][0]];
				if(x==1){
					splay(now,0);
					return now;
				}
				--x;
				now=ch[now][1];
			}
		}
		return -1;
	}
	inline int split(const int& l,const int& r){ //把 l,r 旋转到根、根的右儿子
		int x=kth(l),y=kth(r+2);
		splay(x,0),splay(y,x);
		return y;
	}
	inline void F(const int& c,const int& h){ //题目中的操作一
		int l=find(h)-1,r=min(n,l+c-1);
		if(l>n)
			return;
		int mid=find(val[kth(r+1)])-1,tr=ch[split(mid,r)][0];
		fa[tr]=ch[fa[tr]][0]=0;
		++tag[tr],++val[tr],++Max[tr]; //统计信息
		if(mid>l){
			reg int now=ch[split(l,mid-1)][0];
			++tag[now],++val[now],++Max[now];
		}
		int p=find(val[tr])-1,u=split(p,p-1);
		fa[tr]=u,ch[u][0]=tr;
		splay(tr,0);
		return;
	}
	inline int C(const int& Max,const int& Min){ //操作二
		int l=find(Max)-1,r=find(Min+1)-2; //先旋转，记得不要忘了哨兵节点对编号的影响
		return size[ch[split(l,r)][0]]; //返回答案
	}
};

Splay S;

inline void Work(void){
	S.Max[0]=-INF; //注意细节
	a[n+1]=-INF,a[n+2]=INF; //插入哨兵节点
	sort(a+1,a+n+3); //排序
	S.root=S.Build(0,1,n+2,a); //建树
	while(m--){
		static char opt;
		static int c,h,max,min;
		do
			opt=getchar();
		while(opt!='F'&&opt!='C');
		switch(opt){
			case 'F':{
				c=read(),h=read();
				S.F(c,h);
				break;
			}
			case 'C':{
				max=read(),min=read();
				printf("%d\n",S.C(max,min));
				break;
			}
			default:break;
		}
	}
	return;
}
```

---

## 作者：hyfzelda (赞：1)


# 题意
给出一个长度为 $N$ 的数组 $a$，数组中每个数的取值范围均为 $[1,N]$（没说互不相同）。
接下来有 $M$ 组操作，操作分为两种：
1. $\texttt{F}\:\:c\:\:h$  
将满足 $a[i] \ge h$ 的所有 $a[i]$ 中最小的 $c$ 个数都 $+1$。
2. $\texttt{C}\:\:\min\:\:\max$  
输出满足 $\min \le a[i] \le \max$ 的 $a[i]$ 的个数。

### 输入格式

第一行有两个整数 $N$ 和 $M$。   
第二行有 $N$ 个整数，表示数组 $a$。 
在接下来的 $M$ 行中，每行有一组操作。

### 输出格式

对于每组 $\texttt{C}\:\:\min\:\:\max$ 操作输出一行，每行一个整数，表示满足 $\min \le a[i] \le \max$ 的 $a[i]$ 的个数。

# 做法

### 1.思路

不想写平衡树？你可以试试树状数组！本题为一道树状数组的区间修改，单点查询。

### 2.查询

对于  $\texttt{C}$ 操作，我们需要补充两个函数：

1.查询 $sum_i$ （即第 $i$ 位的前缀和） $\ge x$ 的最小值的
函数 $l$，需要特判 $sum_n<x$ 的情况。

2.查询 $sum_i$ （即第 $i$ 位的前缀和） $\le x$ 的最大值的
函数 $r$，需要特判 $sum_1>x$ 的情况。

为了节省时间，我们考虑二分，因此需要将初始数组进行排序。

接下来，只需要查询 $\max(0,r_{y}-l_x+1)$ 就好了（大于等于 $\min$ 且小于等于 $\max$ 的个数） 。

### 3.修改

对于 $\texttt{F}$ 操作，需要先求出修改的值域 $(y,aim)$，$aim=c+l_y-1$，即修改对象。

然后分两段修改：

1.修改小于 $aim$ 的部分。
```cpp
int tmp=_l(y);
int l=_l(aim);
add(tmp,1);
add(l,-1);
```
2.修改等于 $aim$ 的部分。

```cpp
int l=_l(aim);
int tmp=_l(y);
int r=_r(aim);
add(l+r-tmp-x+1,1);
add(r+1,-1);
```
$x$,$y$ 为输入数据，分别对应 $c$, $h$。

需要特判 $x+tmp>n$ 的情况，此时修改 $add(tmp,1)$ 即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,va[100005],a[100005];
int lowbit(int x)
{
	return x&(-x);
}
void add(int now,int add)
{
	while(now<=n)
	{
		a[now]+=add;
		now+=lowbit(now);
	}
}
int sum(int now)
{
	int summ=0;
	while(now)
	{
		summ+=a[now];
		now-=lowbit(now);
	}
	return summ;
}
int _l(int x)
{
	if(sum(n)<x) return n+1;
	int l=1,r=n,mid,ans;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(sum(mid)>=x)
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return ans;
}
int _r(int x)
{
	if(sum(1)>x) return 0;
	int l=1,r=n,mid,ans;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(sum(mid)<=x)
		{
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&va[i]);
	sort(va+1,va+n+1);
	for(int i=1;i<=n;i++)
	{
		add(i,va[i]-va[i-1]);
	}
	while(m--)
	{
		char op;
		int x,y;
		//scanf("%c%d%d",&op,&x,&y);
		cin>>op>>x>>y;
		if(op=='C')
		{
			printf("%d\n",max(0,_r(y)-_l(x)+1));
		}
		else{
			int tmp=_l(y);
			if(x+tmp>n) add(tmp,1);
			else{
				int aim=sum(x+tmp-1);
				int l=_l(aim);
				int r=_r(aim);
				add(tmp,1);
				add(l,-1);
				add(l+r-tmp-x+1,1);
				add(r+1,-1);
			}
		}
	}
} 
```


---

## 作者：cike_bilibili (赞：0)

# fhq-treap 题解

## 思路
### C 操作
C 操作是比较简单的，把区间 Split 出来输出 size 即可。
### F 操作
直接拆开后区间加在合并显然是不可取的，因为两个区间的最大最小值可能会有冲突。

例如 $3,3,4,4$ 整体加一后和 $4,4$ 合并，变成 $4,4,5,5,4,4$ 。

记前面区间为 $q1$，后面区间为 $q2$。我们考虑将 $q1$ 再次拆分，记 $q2$ 的最小值为 $m$，将 $q1$ 拆分为所有元素 $<m$ 的区间 $q3$ 与所有元素 $=m$ 的区间 $q4$，将 $q3$ 接到 $q2$ 之前，$q4$ 接在 $q2$ 中所有 $m$ 之后即可，这样整体加一后序列还是有序的。
## AC CODE
```cpp
#include <bits/stdc++.h>
#include <random>
#define ls tree[i].lson
#define rs tree[i].rson
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
random_device R;
mt19937 G(R());
int rd(int l,int r){
	return uniform_int_distribution<int>(l,r)(G);
}
struct tree{
	int lson;
	int rson;
	int val;
	int sz;
	int pri;
	int lazy;
}tree[1000005];
int Root;
int tim;
int n,m;
void pushup(int i){
	tree[i].sz=tree[ls].sz+tree[rs].sz+1;
}
void new_node(int &x,int val){
	x=++tim;
	tree[x]={0,0,val,1,rd(1,1e9),0};
}
void pushdown(int i){
	if(tree[i].lazy){
		if(ls){
			tree[ls].lazy+=tree[i].lazy;
			tree[ls].val+=tree[i].lazy;
		}
		if(rs){
			tree[rs].lazy+=tree[i].lazy;
			tree[rs].val+=tree[i].lazy;
		}
		tree[i].lazy=0;
	}
}
void split_val(int i,int &l,int &r,int val){
	if(!i){
		l=r=0;
		return;
	}
	pushdown(i);
	if(tree[i].val<=val){
		l=i;
		split_val(tree[i].rson,tree[l].rson,r,val);
	}
	else{
		r=i;
		split_val(tree[i].lson,l,tree[r].lson,val);
	}
	pushup(i); 
}
void split_sz(int i,int &l,int &r,int sz){
	if(!i){
		l=r=0;
		return;
	}
	pushdown(i);
	if(tree[ls].sz+1<=sz){
		l=i;
		split_sz(tree[i].rson,tree[l].rson,r,sz-tree[ls].sz-1);
	}
	else{
		r=i;
		split_sz(tree[i].lson,l,tree[r].lson,sz);
	}
	pushup(i); 
}
void merge(int &i,int l,int r){
	if(!l||!r){
		i=l|r;
		return;
	}
	pushdown(i);
	pushdown(l);
	pushdown(r);
	if(tree[l].pri>tree[r].pri){
		i=l;
		merge(tree[i].rson,tree[l].rson,r);
	}
	else{
		i=r;
		merge(tree[i].lson,l,tree[r].lson);
	}
	pushup(i);
}
int getmin(int i){
	pushdown(i);
	if(!tree[i].lson)return tree[i].val;
	return getmin(tree[i].lson);
}
void insert(int val){
	int root1,root2,root3,root4;
	split_val(Root,root1,root2,val);
	new_node(root3,val);
	merge(root4,root1,root3);
	merge(Root,root4,root2);
}
void F(int c,int h){
	int root1,root2,root3,root4,root5,root6,root7,root8;
	split_val(Root,root1,root2,h-1);
	split_sz(root2,root3,root4,c);
	//root1 --> root3 --> root4
	int minn=getmin(root4);
	split_val(root3,root5,root6,minn-1);
	split_val(root4,root7,root8,minn);
	tree[root5].lazy++;
	tree[root5].val++;
	tree[root6].lazy++;
	tree[root6].val++;
	merge(root3,root5,root7);
	merge(root3,root3,root6);
	merge(root2,root3,root8);
	merge(Root,root1,root2);
}
void C(int l,int r){
	int root1,root2,root3,root4;
	split_val(Root,root1,root2,l-1);
	split_val(root2,root3,root4,r);
	printf("%d\n",tree[root3].sz);
	merge(root2,root3,root4);
	merge(Root,root1,root2);
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		int x=read();
		insert(x);
	}
	while(m--){
		char ch=getchar();
		if(ch=='F'){
			int c=read(),h=read();
			F(c,h);
		}else{
			int l=read(),r=read();
			C(l,r);
		}
	}
}
```


---

## 作者：wuhupai (赞：0)

自己第一道不看题解写出来的紫题，庆祝一下（~~没初始化种子导致调了30min~~）

这是一个 fhq-treap 的题解

## 思路来源:

首先看题目，因为是序列上的问题，不难想到是一道数据结构题。

首先看到操作 C：对于这种操作，我们可以用平衡树解决，具体方法是，将树 split 成 $<min,min \le x \le max,>max$ 这三个部分，这个操作可以用按权值分裂解决，答案就是 $ry$ 的子树大小（$rx,ry,rz$表示分裂出来的三棵树）。

其次考虑操作 F：我们可以把操作分成三部分

1. 分裂出一颗满足树上权值大于 $ \ge h$ 的子树（直接按 $val$ split）
 
2. 找出权值前 $c$ 大的点(直接按 $siz$ split)

3. 将树上每一个点加一

这是就会有聪明的小朋友要问了，操作 F 不是 $O(n)$ 的吗？但是这个区间加让我们想到 lazytag，所以我们可以用 lazytag 将复杂度优化到 $O(\log{n})$

## 代码实现

思路可行，代码貌似也不难

看到操作 C 不难得出
```cpp
	split(root,x-1,rx,ry);
	split(ry,y,ry,rz);
	cout<<size[ry]<<endl;
	root=merge(merge(rx,ry),rz);
```
看到操作 F 很快啊，我就把思路模拟出来了，可是连样例都没过。此时我们想到两颗 fhq-treap 能 merge 的前提是以 $l$ 为根的子树的权值小于等于以 $r$ 为根的子树。区间加的操作会破坏这个性质。这个也好解决，我们按照最暴力的方法：
![](https://cdn.luogu.com.cn/upload/image_hosting/hkmg7k9f.png)
这样就可以合并了：
```cpp
	 split(root,y-1,rx,ry);
	 if(!ry) continue;
	 split1(ry,x,ry,rz);
	 la[ry]++;
	 p[ry].val++;
	 gg=p[getrnk(ry,size[ry])].val;
	 split(ry,gg-1,ry,ra);
	 split(rz,gg,rz,rb);
	 root=merge(merge(merge(merge(rx,ry),rz),ra),rb);
```
最后附上完整版（有问题多多留言哦）
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int val,rd;
}p[100005];
int n,m,x,y,cnt=0,rx,ry,rz,ra,rb,root,gg;
int size[100005],son[100005][2],la[100005];
char op;
inline int read(){
    int x=0; bool flag=1; char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();}
    if(flag) return x;
    return ~(x-1);
}inline void write(int x){
    if(x<0) {x=~(x-1); putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
void push_up(int x){
	size[x]=size[son[x][0]]+size[son[x][1]]+1;
}
void push_down(int x){
	if(la[x]!=0){
		p[son[x][0]].val+=la[x];
		p[son[x][1]].val+=la[x];
		la[son[x][0]]+=la[x];
		la[son[x][1]]+=la[x];
		la[x]=0;
	}
}
int add(int x){
	cnt++;
	p[cnt].rd=rand();
	p[cnt].val=x;
	size[cnt]=1;
	return cnt;
}
void split(int rt,int key,int &x,int &y){
	if(!rt){
		x=y=0;
		return;
	}
	push_down(rt);
	if(p[rt].val<=key){
		x=rt;
		split(son[rt][1],key,son[rt][1],y);
	}else{
		y=rt;
		split(son[rt][0],key,x,son[rt][0]);
	}
	push_up(rt);
}
void split1(int rt,int siz,int &x,int &y){
	if(!rt){
		x=y=0;
		return;
	}
	push_down(rt);
	if(size[son[rt][0]]+1<=siz){
		x=rt;
		split1(son[rt][1],siz-(size[son[rt][0]]+1),son[rt][1],y);
	}else{
		y=rt;
		split1(son[rt][0],siz,x,son[rt][0]);
	}
	push_up(rt);
}
int merge(int l,int r){
	if(!l||!r){
		return l+r;
	}
	push_down(l),push_down(r);
	if(p[l].rd<p[r].rd){
		son[l][1]=merge(son[l][1],r);
		push_up(l);
		return l;
	}else{
		son[r][0]=merge(l,son[r][0]);
		push_up(r);
		return r;
	}
}
int getrnk(int x,int k){
	while(true){
		push_down(x);
		if((size[son[x][0]]+1)==k){
			return x;
		}else if((size[son[x][0]]+1)<k){
			k-=(size[son[x][0]]+1);
			x=son[x][1];
		}else x=son[x][0];
	}
}
int main(){
	srand(time(0));
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		x=read();
		split(root,x,rx,ry);
		root=merge(merge(rx,add(x)),ry);
	}
	while(m--){
		op=getchar();
		x=read(),y=read();
		if(op=='F'){
			split(root,y-1,rx,ry);
			split1(ry,x,ry,rz);
			la[ry]++;
			p[ry].val++;
			gg=p[getrnk(ry,size[ry])].val;
			split(ry,gg-1,ry,ra);
			split(rz,gg,rz,rb);
			root=merge(merge(merge(merge(rx,ry),rz),ra),rb);
		}else{
			split(root,x-1,rx,ry);
			split(ry,y,ry,rz);
			write(size[ry]);
			putchar('\n');
			root=merge(merge(rx,ry),rz);
		}
	}
	
	return 0;
}
```

---

## 作者：sane1981 (赞：0)

## 背景
一道平衡树好题，大佬可以跳过前面废话。
## 题目解读
[原题传送门](https://www.luogu.com.cn/problem/P4666)

题意已经说得十分清楚了，就是注意所谓的最小的 $c$ 个数指的是排名。

本蒟蒻平衡树只会 FHQ Treap。太弱了！

注：根据 $x$ 分裂成 $l$ 和 $r$ 中 $x$ 是包含在 $l$ 内的。
#### 操作 C $min\ max$
分别按 $min-1$ 和 $max$ 分裂成 $l$，$p$，$r$ 三棵树。答案就是 $siz[p]$。
#### 操作 F $c\ h$
这里就比较复杂了。
先按权值 $h-1$ 分裂成 $l$ 和 $r$ 两棵树。

在根据排名 $c$ 在树 $r$ 分裂成 $L$，$R$ 两棵树。

在增加 $1$ 的同时，可能会出现前面的数大于后面的数。这时候我们不能盲目合并 $L$，$R$。

这时我们要来一波操作，配合图片食用更佳：

![](https://cdn.luogu.com.cn/upload/image_hosting/udq7mxbs.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

我们先知道第 $c$ 个数的大小 $val$，这时候第 $c$ 个数之前之后都可能会有数 $val$。所以在加上一后，$L$ 前面最大有 $val+1$，根据 $val$ 分裂成 $ll$ 和 $lr$。同时在 $R$ 中根据 $val$ 分裂成 $rl$ 和 $rr$。这时候 $lr$ 中都是 $val+1$ 而 $rl$ 中都是 $val$，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0wauv6zz.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

很好，现在就可以愉快的 merge 了，注意交换 $lr$ 和 $rl$。

这里要特判 $r$ 是否为空，否则会 MLE。同时能 Pushdown 的地方一定要 Pushdown。我为此调了一晚上。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,a,b;
char s;
struct FHQ_Treap{
	int ls,rs,siz,prio,key;
	int Add;
}t[N];
int root,tot;
void Newnode(int x){
	t[++tot].siz=1;
	t[tot].ls=t[tot].rs=0;
	t[tot].prio=rand();
	t[tot].key=x;
}
void Pushup(int x){
	t[x].siz=t[t[x].ls].siz+t[t[x].rs].siz+1;
}
void Pushdown(int x){
	if(t[x].Add==0) return;
	t[t[x].ls].Add+=t[x].Add;
	t[t[x].rs].Add+=t[x].Add;
	t[t[x].ls].key+=t[x].Add;
	t[t[x].rs].key+=t[x].Add;
	t[x].Add=0;
}
void Split1(int u,int x,int &l,int &r){
	if(u==0){
		l=r=0;return;
	}
	Pushdown(u);
	if(t[u].key<=x)
		l=u,Split1(t[u].rs,x,t[u].rs,r);
	else r=u,Split1(t[u].ls,x,l,t[u].ls);
	Pushup(u);
}
void Split2(int u,int k,int &l,int &r){
	if(u==0){
		l=r=0;return;
	}
	Pushdown(u);
	if(t[t[u].ls].siz+1<=k)
		l=u,Split2(t[u].rs,k-t[t[u].ls].siz-1,t[u].rs,r);
	else r=u,Split2(t[u].ls,k,l,t[u].ls);
	Pushup(u);
}
int Merge(int l,int r){
	if(l==0||r==0) return l+r;
	if(t[l].prio>t[r].prio){
		Pushdown(l);
		t[l].rs=Merge(t[l].rs,r);
		Pushup(l);return l;
	}else{
		Pushdown(r);
		t[r].ls=Merge(l,t[r].ls);
		Pushup(r);return r;
	}
}
void Insert(int x){
	int l,r;
	Split1(root,x,l,r);
	Newnode(x);
	root=Merge(Merge(l,tot),r);
}
int Kth(int u,int k){
	Pushdown(u);
	if(t[t[u].ls].siz+1==k) return u;
	else if(t[t[u].ls].siz>=k) return Kth(t[u].ls,k);
	else return Kth(t[u].rs,k-t[t[u].ls].siz-1);
}
void Modify(int c,int h){
	int l,r,L,lr,rl;
	Split1(root,h-1,l,r);
	if(!r) return;
	Split2(r,c,L,r);
//	cout<<t[L].siz<<endl;
	int value=t[Kth(L,t[L].siz)].key;
//	cout<<"value="<<value<<endl;
	t[L].key++;t[L].Add++;
	Split1(L,value,L,lr);
	Split1(r,value,rl,r);
	root=Merge(Merge(l,Merge(L,Merge(rl,lr))),r);
}
int Query(int L,int R){
	int l,r,p;
	Split1(root,R,l,r);
	Split1(l,L-1,l,p);
	int res=t[p].siz;
	root=Merge(l,Merge(p,r));
	return res;
}
int main(){
	srand(time(NULL));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		Insert(a);
	}
//	for(int j=1;j<=n;j++) cout<<t[Kth(root,j)].key<<" ";
//	cout<<endl;
	for(int i=1;i<=m;i++){
		scanf("%s %d%d",&s,&a,&b);
		if(s=='F') Modify(a,b);
		else printf("%d\n",Query(a,b));
//		for(int j=1;j<=n;j++) cout<<t[Kth(root,j)].key<<" ";
//		cout<<endl;
	}
	return 0;
}
```
有锅必补，谢谢神犇提醒。

---

## 作者：Erotate (赞：0)

### Solutions

这题可以用树状数组或者平衡树来做，在这篇题解中将使用 fhq_treap 来实现。

对于操作一：

设 $v$ 为大于等于 $h$ 的数中第 $c$ 小的数，我们直接删掉 $v$，然后在树中插入 $v+1$。然后对于大于等于 $h$ 并且小于 $v$ 的数，我们将其直接加上 $1$ 即可。这一部分整体加上 $1$ 后，它们的相对大小并不改变，所以这并不破坏平衡树的结构，因此直接加 $1$ 是没问题的。

对于操作二：

按值分裂，将所有大于等于 $\min$ 并且小于等于 $\max$ 的数分裂成一棵子树，然后直接输出子树的大小即可。

### code

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=1e5+5;
struct fhq_treap{
	int ls,rs,sz,val,rd,w,tag;
}tr[N<<2];
int n,m,rt,idx;
int New(int v,int len){
	tr[++idx]=((fhq_treap){0,0,len,v,rand(),len,0});
	return idx;
}
void push_up(int k){
	tr[k].sz=tr[tr[k].ls].sz+tr[tr[k].rs].sz+tr[k].w;
}
void add(int k,int v){
	tr[k].val+=v;
	tr[k].tag+=v;
}
void push_down(int k){
	if(!tr[k].tag) return;
	if(tr[k].ls) add(tr[k].ls,tr[k].tag);
	if(tr[k].rs) add(tr[k].rs,tr[k].tag);
	tr[k].tag=0;
}
void split(int k,int v,int &lrt,int &rrt){
	if(!k){
		lrt=rrt=0;
		return;
	}
	push_down(k);
	if(tr[k].val<=v){
		lrt=k;
		split(tr[k].rs,v,tr[k].rs,rrt);
	}else{
		rrt=k;
		split(tr[k].ls,v,lrt,tr[k].ls);
	}
	push_up(k);
}
int merge(int x,int y){
	if(x) push_down(x);
	if(y) push_down(y);
	if(!x || !y) return x|y;
	if(tr[x].rd>tr[y].rd){
		tr[x].rs=merge(tr[x].rs,y);
		push_up(x);
		return x;
	}else{
		tr[y].ls=merge(x,tr[y].ls);
		push_up(y);
		return y;
	}
}
void Insert(int v,int len){
	int r1,r2,r3;
	split(rt,v,r1,r2);
	split(r1,v-1,r1,r3);
	if(!r3) rt=merge(merge(r1,New(v,len)),r2);
	else{
		tr[r3].w+=len,tr[r3].sz+=len;
		rt=merge(merge(r1,r3),r2);
	}
}
void Delete(int v,int len){
	int r1,r2,r3;
	split(rt,v,r1,r2);
	split(r1,v-1,r1,r3);
	tr[r3].sz-=len,tr[r3].w-=len;
	if(!tr[r3].w) r3=merge(tr[r3].ls,tr[r3].rs);
	rt=merge(merge(r1,r3),r2);
}
int Num(int k,int v){
	while(k){
		push_down(k);
		if(tr[tr[k].ls].sz+tr[k].w<v){
			v-=tr[tr[k].ls].sz+tr[k].w;
			k=tr[k].rs;
		}else if(tr[tr[k].ls].sz>=v) k=tr[k].ls;
		else break;
	}
	return tr[k].val;
}
int C(int mn,int mx){
	int r1,r2,r3;
	split(rt,mx,r1,r2);
	split(r1,mn-1,r1,r3);
	cout<<tr[r3].sz<<endl;
	rt=merge(merge(r1,r3),r2);
}
void F(int c,int h){
	 int r1,r2,r3;
	 split(rt,h-1,r1,r2);
	 c=min(c,tr[r2].sz);
	 int v=Num(r2,c),r4;
	 split(r2,v-2,r3,r2);
	 split(r2,v-1,r4,r2);
	 int siz=tr[r4].sz;
	 r2=merge(r4,r2);
	 rt=merge(r1,merge(r3,r2));
	 c-=siz;
	 Delete(v-1,siz);
	 Insert(v,siz);
	 split(rt,h-1,r1,r2);
	 c=min(c,tr[r2].sz);
	 split(r2,v-2,r3,r2);
	 c-=tr[r3].sz;
	 if(r3) add(r3,1);
	 rt=merge(r1,merge(r3,r2));
	 if(!c) return;
	 Delete(v,c);
	 Insert(v+1,c);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	srand(time(0));
	cin>>n>>m;
	for(int i=1,x;i<=n;++i){
		cin>>x;
		Insert(x,1);
	}
	for(int i=1,c,h;i<=m;++i){
		char op[5];
		cin>>op+1>>c>>h;
		if(op[1]=='F') F(c,h);
		else if(op[1]=='C') C(c,h);
	}
	return 0;
}
```


---

## 作者：yizhiming (赞：0)

麻了，少写个标记下传调了将近一整天。

放一手 [$Link$](https://www.luogu.com.cn/problem/P4666)。

## 题目大意

给定一个长度为 $n$ 的集合，$m$ 次操作。

- 将 $\geq h$ 的最小的 $c$ 个数的值 $+1$。

- 查询权值在 $[min,max]$ 区间的数的个数。


$1\leq n,m \leq 10^5,c\leq n$，值域 $10^9$。

## 题目分析

这道题的算法标签还是挺好猜的，看到像这种维护区间值域，区间打标记的，多半是值域线段树或者平衡树，我觉得平衡树实现更为好写，于是用的 FHQ。

说实话，我不清楚线段树标签是哪来的，权值线段树实现平衡树的操作？

对于第二个操作，若能够维护好值域，那么直接在平衡树上将 查询的区间分裂出来统计大小即可。

所以现在的问题就变成了，怎样维护一个区间修改的平衡树的权值。

这就有一个有用的小技巧，我们考虑将一个值域区间 $[l,r]$ 整体加会怎样？

平衡树上对应的 $[l,r-1]$ 会整体变成 $[l+1,r]$，其相对的大小关系并没有发生变化，我们知道平衡树是利用相对大小关系维护左右儿子的，所以此时这部分的平衡树结构并未发生变化，直接打上标记即可。只有 $r$ 这一部分，增加后会与原本的 $r+1$ 对应的节点产生冲突，怎么办呢？我们直接删除掉当前的 $r$ 节点，然后将贡献累加到 $r+1$ 这个节点上即可。

怎么累加呢？我们对于每个节点多维护一个值 $len$，表示这个平衡树节点对应的权值的出现次数，注意这个不能用原本的 $siz$ 来表示，不然的话会导致 $siz$ 的更新出问题。

放一下这个技巧的的类似用法，思想还是基本一致的 [$Link$](https://www.luogu.com.cn/problem/CF702F)，如果这道题做不明白，我推销一下我的 [博客](https://www.luogu.com.cn/blog/yizhiming/shuo-ju-jie-gou-di-shi-yong)，因为是做题记录，建议直接全局查找这道题。

回到现在这道题，我们发现修改操作要查找前 $c$ 小的数，难道还要再写一份按区间大小分裂的平衡树吗？

当然不，我们还是刚才那种想法，我们设最大的能被修改的权值为 $val$，那么此时 $val$ 的处境就和之前 $r$ 一样了，把这个节点暴力修改掉，然后贡献累加即可。那么 $val$ 的值是什么呢？显然是 $\geq h$ 的数中第 $c$ 小的数，直接在平衡树上查询第 $c$ 小即可。

但是还有一个问题，权值为 $val$ 的节点不一定删干净，所以 $val-1$ 在增加的时候也会破坏空间结构，$val-1$ 也要特殊处理。

到这里就已经完全解决了，每次修改最多只有四次插入/删除操作，单次 $\log n$ 复杂度正确。

## Code

这玩意的细节特别多，注意在合并、分裂以及查询第 $k$ 大的时候都要下传标记，不然你可能像某个蒟蒻一样调一整天。

查询第 $k$ 大的时候因为单点的出现次数不为 $1$，所以要魔改查询，具体就是 $siz_{ls}<rank\leq siz_{ls}+len_{u}$ 则说明 $u$ 这个节点存的值是答案。

删除的时候，若已经将当前节点的出现次数删成 $0$ 了，则将其真正删除，否则只修改当前的出现次数，插入同理。

插入删除都要魔改成修改 $k$ 个相同的数的形式。

修改单个节点的出现次数时记得将 $siz$ 和 $len$ 的值都进行更改。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e5+5; 
struct aa{
	int lc,rc,siz,val,tag,rnd,len;
}node[N*4];
void lazy_tag(int u,int k){
	if(!u){
		return;
	}
	node[u].val+=k;
	node[u].tag+=k;
}
void pushdown(int u){
	if(!node[u].tag){
		return;
	}
	lazy_tag(node[u].lc,node[u].tag);
	lazy_tag(node[u].rc,node[u].tag);
	node[u].tag = 0;
}
void pushup(int u){
	node[u].siz = node[node[u].lc].siz+node[node[u].rc].siz+node[u].len;
} 
int rt,tot;
int newnode(int val,int k){
	node[++tot].val = val;
	node[tot].rnd = rand();
	node[tot].siz = k;
	node[tot].len = k;
	return tot;
}
void split(int u,int val,int &x,int &y){
	if(!u){
		x = 0;y = 0;
		return;
	}
	pushdown(u);
	if(node[u].val<=val){
		x = u;
		split(node[u].rc,val,node[u].rc,y);
	}else{
		y = u;
		split(node[u].lc,val,x,node[u].lc);
	}
	pushup(u);
}
int merge(int u,int v){
	if(!u||!v){
		return u+v;
	}
	pushdown(u);pushdown(v);
	if(node[u].rnd>node[v].rnd){
		node[u].rc = merge(node[u].rc,v);
		pushup(u);
		return u;
	}else{
		node[v].lc = merge(u,node[v].lc);
		pushup(v);
		return v;
	}
}
int x,y,z;
void ins(int val,int k){
	split(rt,val,x,y);
	split(x,val-1,x,z);
	if(!z){
		rt = merge(merge(x,newnode(val,k)),y);
	}else{
		node[z].siz+=k;
		node[z].len+=k;
		rt = merge(merge(x,z),y);
	}
}
void del(int val,int k){
	split(rt,val,x,y);
	split(x,val-1,x,z);
	node[z].siz-=k;
	node[z].len-=k;
	if(!node[z].len){
		z = merge(node[z].lc,node[z].rc);
	}
	rt = merge(merge(x,z),y);
}
int query(int l,int r){
	split(rt,r,x,y);
	split(x,l-1,x,z);
	int ans = node[z].siz;
	rt = merge(merge(x,z),y);
	return ans;
}

int getnum(int rank,int now){
	while(now){
		pushdown(now);
		if(node[node[now].lc].siz<rank&&rank<=node[now].len+node[node[now].lc].siz){
			break;
		}else if(node[node[now].lc].siz>=rank){
			now = node[now].lc;
		}else{
			rank-=node[node[now].lc].siz+node[now].len;
			now = node[now].rc;
		}
	}
	return node[now].val;
}
int xx;
void upd(int c,int h){
	split(rt,h-1,x,y);
	c = min(c,node[y].siz);
	int val = getnum(c,y);
	split(y,val-2,z,y);
	split(y,val-1,xx,y);
	int sum = node[xx].siz;
	y = merge(xx,y);
	rt = merge(x,merge(z,y));
	c-=sum;
	del(val-1,sum);
	ins(val,sum);
	split(rt,h-1,x,y);
	c = min(c,node[y].siz);
	split(y,val-2,z,y);
	c-=node[z].siz;
	lazy_tag(z,1);
	rt = merge(x,merge(z,y));
	if(!c){
		return;
	}
	del(val,c);
	ins(val+1,c);
}
char s[5];
int main(){
	int n,m,l,r;
	n = read();m = read();
	for(int i=1;i<=n;i++){
		l = read();
		ins(l,1);
	}
	while(m--){
		scanf("%s",s);
		if(s[0]=='F'){
			l = read();r = read();
			upd(l,r);
		}else{
			l = read();r = read();
			cout<<query(l,r)<<'\n';
		}
	}
	return 0;
}
```

突然发现自己是代码长度和题解长度都最长的一篇。

---

## 作者：chen_qian (赞：0)

一种线段树的解法，效率相比平衡树稍好，实现也更为方便。

首先考虑到每次操作都是基于值域，考虑开一颗值域线段树，但是值会有变化，所以这个方法行不通，考虑到每次都是对全局进行修改查询，所以考虑用线段树来维护一个递增的序列，这样就可通过二分来解决查询，但是如何解决修改呢？

考虑操作的特性，发现每次都只会增加 $1$ 。那么最小的 $x$ 满足 $a_x \ge h$ 的 $x$ 是可以二分找到的，然后所有小于 $a_{x+c-1}$ 的数都可以直接加，然后就是所有等于 $a_{x+c-1}$ 的数排在后面的一些数加，一共加 $k$ 个数即可，这样就维护了一个有序序列。只需要线段树二分即可。复杂度 $O(n \log{n})$ 。

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,a[N],m;
int tag[N<<2],maxn[N<<2],minn[N<<2];
void push_up(int p){
	maxn[p]=max(maxn[p<<1],maxn[p<<1|1]);
	minn[p]=min(minn[p<<1],minn[p<<1|1]);
}
void push_tag(int p,int v){
	maxn[p]+=v;
	minn[p]+=v;
	tag[p]+=v;
}
void push_down(int p){
	if(tag[p]){
		push_tag(p<<1,tag[p]);
		push_tag(p<<1|1,tag[p]);
		tag[p]=0;
	}
}
void build(int p,int l,int r){
	if(l==r){
		minn[p]=maxn[p]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
}
void modify(int p,int l,int r,int ql,int qr,int v){
	if(ql>qr) return ;
	if(ql<=l&&qr>=r){
		push_tag(p,v);
		return ;
	}
	push_down(p);
	int mid=(l+r)>>1;
	if(ql<=mid) modify(p<<1,l,mid,ql,qr,v);
	if(qr>mid) modify(p<<1|1,mid+1,r,ql,qr,v);
	push_up(p);
}
int queryl(int p,int l,int r,int v){
	if(l==r) return l;
	push_down(p);
	int mid=(l+r)>>1;
	if(maxn[p<<1]>=v) return queryl(p<<1,l,mid,v);
	else return queryl(p<<1|1,mid+1,r,v);
}
int queryr(int p,int l,int r,int v){
	if(l==r) return l;
	push_down(p);
	int mid=(l+r)>>1;
	if(minn[p<<1|1]<=v) return queryr(p<<1|1,mid+1,r,v);
	else return queryr(p<<1,l,mid,v);
}
int queryval(int p,int l,int r,int x){
	if(l==r) return maxn[p];
	push_down(p);
	int mid=(l+r)>>1;
	if(x<=mid) return queryval(p<<1,l,mid,x);
	else return queryval(p<<1|1,mid+1,r,x);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	build(1,1,n);	
	while(m--){
		char c;
		cin>>c;
		int x,y;
		scanf("%d%d",&x,&y);
		if(c=='F'){
			if(y>maxn[1]) continue;
			int pos=queryl(1,1,n,y);
			x=min(n-pos+1,x);
			int val=queryval(1,1,n,pos+x-1);
			int l=queryl(1,1,n,val),r=queryr(1,1,n,val);
			int t=l-pos;
			modify(1,1,n,pos,l-1,1);
			modify(1,1,n,r-(x-t)+1,r,1);
		}
		else{
			if(maxn[1]<x||minn[1]>y){
				puts("0");
				continue;
			}
			int l=queryl(1,1,n,x),r=queryr(1,1,n,y);
			printf("%d\n",r-l+1);
		}
	}
	return 0;
}
```


---

