# 「QFOI R1」头

## 题目背景

可以看看这个讨论：<https://www.luogu.com.cn/discuss/703835>。

## 题目描述

小 R 是一个可爱的女孩子。有一天，她在被摸头时，突然灵光乍现，便随手加强了一道题给你做。

这道题的名字叫涂色游戏。初始时你有一个 $n$ 行 $m$ 列的网格，所有格子上都没有颜色。有 $k$ 种颜色的刷子，颜色编号为 $1\sim k$。然后给出 $q$ 次操作，每次操作给出 $op,l,r,c,t$ 五个参数：

- 如果 $op=1$，表示将第 $l\sim r$ 行的所有格子涂成颜色 $c$。
- 如果 $op=2$，表示将第 $l\sim r$ 列的所有格子涂成颜色 $c$。
- 如果 $t=0$，意味着如果涂色时遇到已经被染色的格子，就不再进行染色。
- 如果 $t=1$，意味着如果涂色时遇到已经被染色的格子，就用新的颜色覆盖它。

在所有涂色操作结束以后，对于每种颜色，求出有多少个格子被染成了这种颜色。

## 说明/提示

**样例 $1$ 解释**

用浅灰色表示颜色 $1$，灰色表示颜色 $2$。

涂色过程如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/gl7dmh5b.png)

共有 $17$ 个区域被染成颜色 $1$，$7$ 个区域被染成颜色 $2$。

---

**数据范围**

本题共 $20$ 个测试点，每个测试点 $5$ 分。

对于全部数据，保证 $1\le n,m,q\le 2\times 10^6$，$1\le k\le 5\times 10^5$，$op\in\{1,2\}$，若 $op=1$ 则 $1\le l\le r\le n$，若 $op=2$ 则 $1\le l\le r\le m$，$1\le c\le k$，$t\in\{0,1\}$。

- 对于测试点 $1\sim 3$：保证 $n,m,k,q\le 200$。
- 对于测试点 $4\sim 6$：保证 $n,m,k,q\le 2\times 10^3$。
- 对于测试点 $7\sim 9$：保证 $n,m,k,q\le 10^5$，$op=1$。
- 对于测试点 $10\sim 12$：保证 $n,m,k,q\le 10^5$，$t=1$。
- 对于测试点 $13\sim 18$：保证 $n,m,k,q\le 10^5$。
- 对于测试点 $19\sim 20$：无特殊限制。

## 样例 #1

### 输入

```
5 5 2 4
1 2 4 1 0
2 4 5 1 1
2 2 4 2 0
1 1 1 2 1```

### 输出

```
17 7```

## 样例 #2

### 输入

```
5 5 3 6
2 1 3 3 1
2 2 4 1 0
1 4 4 2 0
2 1 1 1 0
1 2 5 2 0
1 1 5 3 0```

### 输出

```
5 4 16```

# 题解

## 作者：registerGen (赞：23)

这里是官方题解。

春测 2023 T1 加强版。

## 算法一

对于一次染色操作，暴力地将相应区域染上相应颜色，最后用桶统计答案。

时间复杂度 $\mathcal O(nmq)$。

## 算法二

考虑当 $t=1$ 时怎么做。

将所有操作倒过来考虑。这样一来一个区域只要被染色了，它的颜色就再也不会变了，我们就再也不用管它了。

于是我们只需维护每一行是否全部被染色（记为 $R_i$）和每一列是否全部被染色（记为 $C_i$）。每次操作（以 $op=1$ 为例）我们考虑计算新增的被染色的格子数量，要干的事情如下：

1. $ans_c\gets ans_c+(r-l+1-\sum_{i=l}^rR_i)(m-\sum_{i=1}^mC_i)$；
2. 对于所有 $l\le i\le r$，$R_i\gets 1$。

我们要进行的操作有：区间求和、区间赋值。这显然可以通过线段树维护。

时间复杂度 $\mathcal O(q\log\max\{n,m\})$。

p.s. 线段树有 90 分是因为放不了很多那么大的数据，而且基础赛不让把输入格式搞那么复杂（也就是说不让在程序内生成数据

## 算法三

考虑优化算法二。

我们维护单向链表 $nxtR,nxtC$，$nxtR_i$ 表示当前的 $R$ 中在 $R_i$ 右边的第一个为 $0$ 的位置，$nxtC_i$ 的定义类似。每次查询我们直接暴力跳 $nxt$ 并统计答案，修改时边跳 $nxt$ 边把当前的 $nxt$ 更新为 $nxt_r$（如果没有理解这句话，你可以参考 std 中的 `Solver::modify` 函数和 `Solver::query` 函数）。

注意到我们查询完一个区间后就要对这个区间做修改，故 $R,C$ 的每个位置最多被访问一次。于是时间复杂度就被均摊成线性了。

时间复杂度 $\mathcal O(n+m+q)$。

## 算法四

事实上我们只需要安排一个操作顺序，使得后面的操作不“影响”前面的操作。我们可以先从后往前进行完所有 $t=1$ 的操作，再从前往后进行完所有 $t=0$ 的操作。

时间复杂度 $\mathcal O(n+m+q)$。

## std

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;

const int N = 2e6;

struct Query { int opt, l, r, c, t; };

int n, m, k, q;
Query qry[N + 10];
ll ans[N + 10];

struct Solver {
  int sum, a[N + 10], nxt[N + 10];

  inline void modify(int ql, int qr) {
    int lst = 0;
    for (int i = ql; i <= qr; i = nxt[i]) {
      if (a[i] == 0) sum++;
      a[i] = 1;
      if (lst) nxt[lst] = nxt[qr];
      lst = i;
    }
  }

  inline int query(int ql, int qr) {
    int res = 0;
    for (int i = ql; i <= qr; i = nxt[i]) {
      res += !a[i];
    }
    return qr - ql + 1 - res;
  }
} tr, tc;

void modify(int id) {
  int opt = qry[id].opt, l = qry[id].l, r = qry[id].r, c = qry[id].c;
  if (opt == 1) {
    int cntr = tr.query(l, r), cntc = tc.sum;
    ans[c] += 1LL * (r - l + 1 - cntr) * (m - cntc);
    tr.modify(l, r);
  } else {
    int cntr = tr.sum, cntc = tc.query(l, r);
    ans[c] += 1LL * (n - cntr) * (r - l + 1 - cntc);
    tc.modify(l, r);
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m, &k, &q);
  for (int i = 1; i <= q; i++)
    scanf("%d%d%d%d%d", &qry[i].opt, &qry[i].l, &qry[i].r, &qry[i].c, &qry[i].t);
  for (int i = 1; i <= n; i++) tr.nxt[i] = i + 1;
  for (int i = 1; i <= m; i++) tc.nxt[i] = i + 1;
  for (int i = q; i >= 1; i--)
    if (qry[i].t) modify(i);
  for (int i = 1; i <= q; i++)
    if (!qry[i].t) modify(i);
  for (int i = 1; i <= k; i++)
    printf("%lld%c", ans[i], " \n"[i == k]);
  return 0;
}
```

---

## 作者：__3E24AC7002AD9292__ (赞：14)

居然是[赛场](https://www.luogu.com.cn/record/127812373)切掉的！

这里提供一个 $\text O(n\log n)$ 的**优先队列维护区间修改**的考场做法，加卡常数能过。

给每种操作定义一个优先级。显然 $t\in\{0,1\}$ 的操作都分别满足第一、二种性质：

- $t=1$ 操作，在后面执行的优先级比在前面的高。
- $t=0$ 操作，在前面执行的优先级比在后面的高。

而且第一种操作优先级显然大于第二种，这也是十分显然的。所以这里我设计的优先级是这样的：假设当前是第 $i$ 次操作，则如果 $t_i=1$，则优先级为 $i$，反之为 $-i$。

然后考虑 $op\in\{1,2\}$ 的操作，可以分开处理，最后一起统计。因为格子都是整行或者整列地复制，所以可以将二维的统计单格颜色分开变为两个维护行、列颜色的数组（同时保存优先级）。

保存所有操作的修改之后，可以将二维数组转化，将行、列的所有未被覆盖的操作按照从大到小的优先级排序，依次遍历，覆盖颜色。如果在遍历到某一行的时候，在之前覆盖了 $x$ 列，则因为优先级大的会覆盖优先级小的操作，这次操作只会覆盖该行的 $n-x$ 格。遍历到列的时候处理是类似的。

这样复杂度就是 $\text O(n^2)$，空间复杂度可以从原来的 $\text O(n^2)$ 优化为 $\text O(n)$。

接下来考虑优化时间复杂度。分开记录行、列操作。处理行的时候，可以把每次操作的区间和优先级记录到一个 `vector` 里，维护一个优先队列（优先级从小到大排序），遍历 $1\sim n$，遍历到 $i$ 的时候，先将队列顶部保存的操作不断弹出，直到顶部操作右区间不小于 $i$，然后 操作区间左边界为 $i$ 的行操作放入优先队列，取队列顶的操作并将该行设置为对应颜色（后面的操作优先级被覆盖，所以不用管）。列处理与行类似。最后合并行、列处理即可。

时间复杂度 $\text O(n\log n)$，其中一只 $\log n$ 是优先队列的。

顺带一提，由于使用了较多的 `STL` 数据结构，所以常数较大。所以遍历 `vector` 的时候建议使用 `auto` 遍历，读入输出使用较快方式，可以卡常数时间。

```cpp
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define mpr make_pair
#define fr first
#define sc second
#define qwq pair<int,pair<pair<int,int>,int> >
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)//快速读取字符
inline const int read(){//基于快读读取字符的超级快读
    int x=0,f=1;register char ch=nc();
    while (ch<48||ch>57) {if (ch=='-') f=-1;ch=nc();}
    while (ch>=48&&ch<=57) x=x*10+ch-48,ch=nc();
   	return x*f;
}
const int n=read(),m=read(),k=read(),q=read();
int cnt1,cnt2;
long long sum[500005];
pair<int,int>opt1[2000005],opt2[2000005];
pair<pair<int,int>,int>qq[4000005];//{c,t},type
vector<pair<int,pair<int,int> > >op1[2000005],op2[2000005];//r,{c,t}
inline bool comp(const pair<pair<int,int>,int> &o,const pair<pair<int,int>,int> &p) {return o.fr.sc>p.fr.sc;}
void init1(){
	priority_queue<qwq,vector<qwq >,less<qwq > >que;//t,{{l,r},c}
	for (register int i=1;i<=n;++i){
		while (!que.empty()){
			if (que.top().sc.fr.sc<i) que.pop();
			else break;
		}
		for (auto j:op1[i]) que.push(mpr(j.sc.sc,mpr(mpr(i,j.fr),j.sc.fr)));
		if (!que.empty()){
			const int col=que.top().sc.sc,tt=que.top().fr;
			opt1[i]=mpr(col,tt);
		}
	}
}
void init2(){
	priority_queue<qwq,vector<qwq >,less<qwq > >que;//t,{{l,r},c}
	for (register int i=1;i<=m;++i){
		while (!que.empty()){
			if (que.top().sc.fr.sc<i) que.pop();
			else break;
		}
		for (auto j:op2[i]) que.push(mpr(j.sc.sc,mpr(mpr(i,j.fr),j.sc.fr)));
		if (!que.empty()){
			const int col=que.top().sc.sc,tt=que.top().fr;
			opt2[i]=mpr(col,tt);
		}
	}
}
int main(){
	int op,l,r,c,t,ggg;
	for (register int i=1;i<=q;++i){
		op=read(),l=read(),r=read(),c=read(),t=read(),ggg=(t==1?i:-i);
		if (op==1) op1[l].push_back(mpr(r,mpr(c,ggg)));
		else op2[l].push_back(mpr(r,mpr(c,ggg)));
	}
	init1(),init2();
	for (register int i=1;i<=n;++i) qq[i]=mpr(opt1[i],1);
	for (register int i=1;i<=m;++i) qq[n+i]=mpr(opt2[i],2);
	sort(qq+1,qq+n+m+1,comp);
	for (register int i=1;i<=n+m;++i){
		int col=qq[i].fr.fr,typ=qq[i].sc;
		if (col==0) continue;
		if (typ==1) ++cnt1,sum[col]+=m-cnt2;
		else ++cnt2,sum[col]+=n-cnt1;
	}
	for (register int i=1;i<=k;++i) printf("%lld ",sum[i]);
	return 0;
}
```


---

## 作者：SamHJD (赞：10)

## [P9715 「QFOI R1」头](https://www.luogu.com.cn/problem/P9715)

首先处理 $t$，我们尝试以某种顺序排列染色操作，使得其变为每次都为覆盖染色的形式。十分简单，对于 $t$ 相同的两次操作，如果 $t=1$，那么按照时间从小到大排，否则按照时间从大到小排，$t$ 不相同则将 $t=1$ 的放后面。

我们排序后逆序处理操作，形象来说就是在所有已经染的颜色下面染色。我们需要找到两个量计算这种颜色在这次操作的贡献，以染一行为例：

* 在 $[l,r]$ 内有 $x$ 行没有被染色。

* 有 $y$ 列没有被染色。

对这种颜色的贡献便是 $x\times y$。$y$ 很好计算，我们处理列的染色时如果能记录每次染了多少列，那么用一个变量存储即可。

对于 $x$，我们尝试用**链表**处理。

还是以行举例，我们设 $next_i$ 为 $i$ 之后最近的没染色的一行的位置，从 $l$ 开始跳链表，直到下一个位置超过了 $r$。过程中更新 $next_i=next_{r+1}$ 即可，并且更新还有多少行没有被染色。

染色不能撤销，一行、一列的每一个位置我们只经过一次，于是复杂度便为 $O(n+m+q)$，可以通过。

```cpp
#include "bits/stdc++.h"
#define int long long
using namespace std;
const int N=8e6+10;
int n,m,k,Q,sum[N],nxt[N][5],last[5],mp[N][5];
struct nodeq{
    int op,l,r,c,t,id;
}q[N];
bool cmp(nodeq a,nodeq b){
    if(a.t!=b.t) return a.t<b.t;
    else if(a.t==1) return a.id<b.id;
    else return a.id>b.id;
}
signed main(){
    scanf("%lld%lld%lld%lld",&n,&m,&k,&Q);
    for(int i=1;i<=Q;++i){
        scanf("%lld%lld%lld%lld%lld",&q[i].op,&q[i].l,&q[i].r,&q[i].c,&q[i].t);
        q[i].id=i;
    }
    sort(q+1,q+Q+1,cmp);
    for(int i=1;i<=n+1;++i) nxt[i][1]=i;
    for(int i=1;i<=m+1;++i) nxt[i][2]=i;
    //这里要到n,m+1，防止后面next访问越界死循环
    last[1]=n;//还剩多少行
    last[2]=m;//还剩多少列
    for(int i=Q;i>=1;--i){
        int cnt=0,x;
        for(int j=q[i].l;j<=q[i].r;j=nxt[j+1][q[i].op]){
            if(!mp[j][q[i].op]) cnt++,last[q[i].op]--;
            //这行没被染色
            mp[j][q[i].op]=1;
            if(x<=q[i].r) nxt[j][q[i].op]=nxt[q[i].r+1][q[i].op];
        }
        sum[q[i].c]+=cnt*last[3-q[i].op];
        //3-q[i].op即行->列，列->行
    }
    for(int i=1;i<=k;++i) printf("%lld ",sum[i]);
    return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：10)

这里是极其抽象的珂树做法。

首先假若只有行或者只有列，那么考虑先正着处理 $t = 0$ 的操作再倒着处理 $t = 1$ 的操作，容易发现我们只需要处理区间覆盖即可，直接上珂朵莉树解决。

然后行和列同时存在考虑这么办：对于每一个行或列，假若被 $t = 1$ 的操作覆盖过那么记下最后一个这样的操作，否则记下第一个 $t = 0$ 的覆盖操作，这个也容易在前面的珂朵莉树上解决，然后对于每一个行或者列计算这样的覆盖会在最后保存多少格，这个容易把操作挂在时间轴上扫描一遍计算。

那么就做完了，最后记得卡卡常，赛时我用 C++ 98 才卡过了。

```cpp
#include<bits/stdc++.h>
namespace IO{
	const int SIZE=1<<21;
	static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
	#define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
	#define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
	#define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
	#define puts(x) IO::Puts(x)
	template<typename T>
    inline void read(T&x){
    	for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
    	for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
    	x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
    	for(int i=0;s[i];i++)
			putchar(s[i]);
		putchar('\n');
	}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
//#define lowbit(x) (x&(-x))
const int maxn = 2e6+14;
using namespace std;
struct Node{
    int l,r,v,tim;
    Node(int l,int r = 0,int v = 0,int tim = 0) : l(l), r(r), v(v), tim(tim){}
    bool operator<(const Node &a) const {
        return l < a.l;
    }
};
set<Node> s;
set<Node>::iterator split(int pos) {
    set<Node>::iterator it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) {
        return it;
    }
    it--;
    if (it->r < pos) return s.end();
    int l = it->l;
    int r = it->r;
    int v = it->v;
    int tim = it->tim;
    s.erase(it);
    s.insert(Node(l, pos - 1, v, tim));
    return s.insert(Node(pos, r, v, tim)).first;
}
void assign(int l, int r, int x,int tim = 0) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(Node(l, r, x, tim));
}
int col[maxn][2];//每行最终的颜色 
int tt[maxn][2];
struct opt{
	int l,r,c,t,tim;
	opt(int L,int R,int C,int T,int TIM){
		l=L,r=R,c=C,t=T,tim=TIM;
	}
};
vector<opt> R,C;//行 列 
int n,m,k,q;
long long answer[maxn];
inline bool cmp1(opt x,opt y){
	return x.tim>y.tim;
}
inline bool cmp2(opt x,opt y){
	return x.tim<y.tim;
}
vector<int> r[maxn],c[maxn];
int main(){
	read(n);
	read(m);
	read(k);
	read(q);
	for(int i=1;i<=q;i=-~i){
		int op,l,r,c,t;
		read(op);
		read(l);
		read(r);
		read(c);
		read(t);
		if(op==1) R.push_back(opt(l,r,c,t,i));
		else C.push_back(opt(l,r,c,t,i));
	}
	s.insert(Node(1,n,0,0));
	sort(R.begin(),R.end(),cmp1);
	for(int i=0;i<R.size();i++){
		opt now=R[i];
		if(now.t==0){
			assign(now.l,now.r,now.c,-now.tim);
		}
	}
	sort(R.begin(),R.end(),cmp2);
	for(int i=0;i<R.size();i++){
		opt now=R[i];
		if(now.t==1){
			assign(now.l,now.r,now.c,now.tim);
		}
	}
	for(set<Node>::iterator it=s.begin();it!=s.end();++it){
		for(int j=(it->l);j<=(it->r);j++){
			col[j][0]=(it->v);
			tt[j][0]=(it->tim);
			if(tt[j][0]>0) r[tt[j][0]].push_back(j);
		}
	}
	s.clear();
	s.insert(Node(1,m,0,0));
	sort(C.begin(),C.end(),cmp1);
	for(int i=0;i<C.size();i++){
		opt now=C[i];
		if(now.t==0){
			assign(now.l,now.r,now.c,-now.tim);
		}
	}
	sort(C.begin(),C.end(),cmp2);
	for(int i=0;i<C.size();i++){
		opt now=C[i];
		if(now.t==1){
			assign(now.l,now.r,now.c,now.tim);
		}
	}
	for(set<Node>::iterator it=s.begin();it!=s.end();++it){
		for(int j=(it->l);j<=(it->r);j++){
			col[j][1]=(it->v);
			tt[j][1]=(it->tim);
			if(tt[j][1]>0) c[tt[j][1]].push_back(j);
		}
	}
	int sum1=0,sum2=0;; 
	for(int i=q;i>=1;--i){
		for(int j=0;j<c[i].size();j++){
			int now=c[i][j];
			sum1++;
			answer[col[now][1]]+=n-sum2;
		}
		for(int j=0;j<r[i].size();j++){
			int now=r[i][j];
			sum2++;
			answer[col[now][0]]+=m-sum1;
		}
	}
	for(int i=1;i<=m;i=-~i){
		if(tt[i][1]<0){
			c[-tt[i][1]].push_back(i);
		}
	}
	for(int i=1;i<=n;i=-~i){
		if(tt[i][0]<0){
			r[-tt[i][0]].push_back(i);
		}
	}
	sum1=0,sum2=0;
	for(int i=q;i>=1;--i){
		for(int j=0;j<c[i].size();j++){
			int now=c[i][j];
			if(tt[now][1]>0) sum1++;
			if(tt[now][1]<0){
				answer[col[now][1]]+=n-sum2;
			}
		}
		for(int j=0;j<r[i].size();j++){
			int now=r[i][j];
			if(tt[now][0]>0) sum2++;
			if(tt[now][0]<0){
				answer[col[now][0]]+=m-sum1;
			}
		}
	}
	sum1=0,sum2=0;
	for(int i=1;i<=q;i=-~i){
		for(int j=0;j<c[i].size();j++){
			int now=c[i][j];
			sum1++;
			if(tt[now][1]<0){
				answer[col[now][1]]-=sum2;
			}
		}
		for(int j=0;j<r[i].size();j++){
			int now=r[i][j];
			sum2++;
			if(tt[now][0]<0){
				answer[col[now][0]]-=sum1;
			}
		}
	}
	for(int i=1;i<=k;i=-~i){
		write(answer[i]);
		putchar(' ');
	}
	return 0;
}
```






---

## 作者：262620zzj (赞：9)

首先一眼丁真看到数据范围 $n,m\le 2\times 10^6$ ，以及题目要求“涂色”，想到分别处理行和列的信息。

然后，有的操作覆盖，有的操作不覆盖，有点麻烦。不过好在我们可以离线处理。进行一个排序，先倒着进行 $t=1$ 的操作，然后正着进行 $t=0$ 的操作（操作时都不覆盖以前的颜色），这样所有操作都统一特性了，并且与原来等效。

接下来就要解决涂色操作了

![](https://cdn.luogu.com.cn/upload/image_hosting/4vukfp3b.png)

这个例子中，我们要对2到6行涂成黑色，如何计算贡献呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/gzox9dw9.png)

不难发现要涂色的点就是图中黑点，因为所有涂色操作必然涂的是一个长方形，所以黑点一定也组成一个长方形。那么这次操作后黑色的格子数量就 $+=l\sim r$  中未涂色的行数 $  \times 1\sim m$ 中未涂色的列数。列的操作同理。涂色完成后，$l\sim r$ 全部设为已涂色。

所以我们要解决的就是区间查询，以及区间修改。~~这种问题我只会写线段树~~用2个线段树分别维护行和列的涂色情况即可。

- 虽然比较坏的情况复杂度 $O(q(\log (\max(n,m)+\log(q)))$，但是我们可以优化一下，由于有很多次涂色，所以查询的时候，一旦发现区间内全部已涂色，那么直接返回0，可以加快速度。
- 其实可以用两个容器分别存覆盖操作和不覆盖操作，节省排序时间
- $2\times 10^6$ 组操作，每组操作 $5$ 个数记得要快读。
- 线段树不一定要开 $4*N$ ，可以节省空间。

```cpp
//bool c用于区分行或列
#include<bits/stdc++.h>
using namespace std;
template<typename T>void read(T &x){
	x=0;
	char c=getchar();
	int f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	x*=f;
}
template<typename T,typename ...Args>
void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=2e6+5,K=5e5+5;
typedef long long ll;
int n,m,k,q;
ll ans[K];
bool c;
struct operation{int dir,l,r,c;}op[N]; 
vector<operation> op1,op0;
struct segment_tree{int dir,l,r,v,tag;}tr[2][3*N];
void build(int p,int l,int r){
	int ls=p<<1,rs=p<<1|1,mid=l+r>>1;
	if(l==r){
		tr[c][p].l=tr[c][p].r=l;
		tr[c][p].v=1;
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[c][p].l=tr[c][ls].l;
	tr[c][p].r=tr[c][rs].r;
	tr[c][p].v=r-l+1;
}
void add(int p,int L,int R){
	int ls=p<<1,rs=p<<1|1,l=tr[c][p].l,r=tr[c][p].r;
	if(r<L||R<l)return;
	if(tr[c][p].v==0)return;
	if(L<=l&&r<=R){
		tr[c][p].v=0;
		return;
	}
	add(ls,L,R);
	add(rs,L,R);
	tr[c][p].v=tr[c][ls].v+tr[c][rs].v;
}
int query(int p,int L,int R){
	int ls=p<<1,rs=p<<1|1,l=tr[c][p].l,r=tr[c][p].r;
	if(r<L||R<l||tr[c][p].v==0)return 0;
	if(L<=l&&r<=R)return tr[c][p].v;
	return query(ls,L,R)+query(rs,L,R);
}
int main(){
	read(n,m,k,q);
	for(int i=1,tt,l,r,c,t;i<=q;i++){
		read(tt,l,r,c,t);
		if(t==1)op1.push_back((operation){tt,l,r,c});
		else op0.push_back((operation){tt,l,r,c});
	}
	for(int i=0;i<op1.size();i++)op[op1.size()-i]=op1[i];
	for(int i=0;i<op0.size();i++)op[op1.size()+i+1]=op0[i];
	c=1;
	build(1,1,n);
	c=0;
	build(1,1,m);
	for(int i=1;i<=q;i++){
		int l=op[i].l,r=op[i].r,w=op[i].c;
		if(op[i].dir==1){
			c=1;
			int tmp=query(1,l,r);
			c=0;
			ans[w]+=1ll*tmp*query(1,1,m);
			c=1;
			add(1,l,r);
		}
		else{
			c=0;
			int tmp=query(1,l,r);
			c=1;
			ans[w]+=1ll*tmp*query(1,1,n);
			c=0;
			add(1,l,r);
		}
	}
	for(int i=1;i<=k;i++)printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：xishanmeigao (赞：7)

（[题目传送门](https://www.luogu.com.cn/problem/P9715)）

$t=1$ 和 $t=0$ 的操作混杂在一起很麻烦，考虑将它们归并到一起

因为 $t=1$ 会覆盖掉全部的颜色，所以可以考虑让 $t=1$ 的先做，在所有 $t=1$ 中，让最后操作的先做。而 $t=0$ 的就按顺序在 $t=1$ 之后做即可。这样所有的操作都是不覆盖先前颜色的

这样我们只需记录已经染过的行个数 $rt$，列个数 $ct$。对于一个 `1,l,r,c,0/1` 的操作来说，只需让 $l\sim r$ 中没被染过的行分别使 $ans_c$ 加上 $m-ct$ 即可。列操作同理

问题是怎么维护染过的行和列，可以用类似并查集的思想，一开始令每一行/列的父亲都指向自己，如果自己被染色，就将父亲指向下一行/下一列，这样每次跳的时候都会直接跳到没有染过色的行/列

因为每一列和每一行只会访问一次，所以时间复杂度是 $O(n)$ 的（忽略并查集）

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=2e6+10,K=5e5+10;

int n,m,k,q;
int rt,ct;
LL ans[K];
struct Ask{int op,l,r,c,t,id;}a[N];

bool cmp(Ask x,Ask y)
{
	if(x.t!=y.t)
		return x.t>y.t;
	if(x.t==1)
		return x.id>y.id;
	return x.id<y.id;
}

struct DS
{
	int fa[N];
	
	int get(int x)
	{
		if(x==fa[x])	
			return x;
		return fa[x]=get(fa[x]);
	}
}row,col;

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1; i<=q; i++)
	{
		scanf("%d%d%d%d%d",&a[i].op,&a[i].l,&a[i].r,&a[i].c,&a[i].t);
		a[i].id=i; 
	}
	
	sort(a+1,a+1+q,cmp);
	
	for(int i=1; i<=n+1; i++)
		row.fa[i]=i;
	for(int j=1; j<=m+1; j++)
		col.fa[j]=j;
	
	for(int i=1; i<=q; i++)
	{
		int l=a[i].l,r=a[i].r;
		if(a[i].op==1)
		{
			for(int j=row.get(l); j<=r; j=row.get(j))
			{
				rt++;  row.fa[j]=j+1;
				ans[a[i].c]+=1LL*(m-ct);
			}
		}
		else
		{
			for(int j=col.get(l); j<=r; j=col.get(j))
			{
				ct++;  col.fa[j]=j+1;
				ans[a[i].c]+=1LL*(n-rt); 
			}
		}
	}
	
	for(int i=1; i<=k; i++)
		printf("%lld ",ans[i]);

	return 0;
}
```


---

## 作者：irris (赞：7)

## Preface

哎呦这不我们 [原题](https://www.luogu.com.cn/problem/P2391) 吗？

## Solution

阅读时请注意 $t, op$ 的定义。不要像我一样写着写着题解搞反了。

首先考虑给所有操作确定一个合理的执行顺序，使得我们 **能够将所有 $\bm{t = 1}$ 的操作转化为 $\bm{t = 0}$ 的操作**。我们发现，若 $1 \leq i \lt j \leq m$ 且 $i, j$ 操作有重叠，则：

+ $t_j = 1$ 时，$j$ 会覆盖 $i$；
+ $t_j = 0$ 时，$i$ 会覆盖 $j$。

不难发现一个合理的标顺序方式为，先将所有 $t = 1$ 的操作倒序执行，再将所有 $t = 0$ 的操作顺序执行。这样重排序后，我们就将所有操作改写为了 $t = 0$。

接下来，我们考虑所有操作是 $t = 0$ 时如何计算答案！不妨设 $op = 1$，发现它的一维版本就是 [白雪皑皑](https://www.luogu.com.cn/problem/P2391)！回想这题我们怎么做的，用并查集模拟单向链表，即设 $fa_u$ 表示 $\geq u$ 的列中 **最小的、未被染色的** 的列，维护这样一个结构后暴力跳 $fa$ 即可。

+ 这个结构，用树论的话来说，应该是 **毛毛虫**；
+ 我们可以按照并查集的处理方式，使用 **路径压缩**（不光节省了暴力跳的时间，而且保证了正确性）的方法，在每次访问时更新 $fa_u$。
+ 根据一些简易的分析，这个做法应当是能做到时间复杂度 $\mathcal O(n)$ 的。

然后我们做完了一维，想要跳到二维，怎么办呢？发现事实上，我们每次染色相当于是在大矩形中扣去一些横着的条和竖着的条，根据小学奥数，最后拼起来还是一个矩形。我们已经知道了对应维度没有被染色的列有多少个，那么我们只要记录未被染色的行有多少个，**这是对于每一列统一的**，我们只要维护 $cnt$ 初始为 $n$，每染掉一行就 $cnt \gets cnt - 1$ 即可。把两个乘起来贡献给对应颜色即可。

另一维是同理的，可以封装维护。

我的代码的时间复杂度 $\mathcal O(n\log n + m\log m + k + q)$，但是瓶颈在 `std::sort`，众所周知 `std::sort` 跑 $10^7$ 用不了 1 秒，完全可以通过。优化成线性的方法即为使用桶排序。

## Code

放了一点赛场上自己魔怔时写的彩蛋。

```cpp
#include <bits/stdc++.h>

namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return; write<T>(x / 10), putchar(x % 10 ^ '0'); }
	template <typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; else if (x == 0) putchar('0'); write<T>(x); }
	template <typename T> inline void print(T x, char en) { if (x < 0) putchar('-'), x = -x; else if (x == 0) putchar('0'); write<T>(x), putchar(en); }
}; using namespace FastIO;

#define MAXN 2000005
struct amortizeUFS {
	int fa[MAXN], tim[MAXN], col[MAXN], N;
	void inis(int n) { N = n; for (int i = 1; i <= N + 1; ++i) fa[i] = i; }
	inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { x = find(x), y = find(y); if (x != y) fa[x] = y; }
	void cover(int t, int c, int l, int r) {
		for (int i = find(l); i <= r; ) tim[i] = t, col[i] = c, merge(i, i + 1), i = find(i);
	}
	int oongdhy() { return 131313; }
	int ppkxxsn() { return 114514; }
	int qqohzrr() { return 1919810; }
} row, col;

int l[MAXN], r[MAXN], c[MAXN];
bool op[MAXN], t[MAXN];

long long ans[MAXN];
int main() {
	int N = read<int>(), M = read<int>(), K = read<int>(), Q = read<int>();
	auto Grt = [&](int time) -> int { return std::abs(time); };
	row.inis(N), col.inis(M);
	for (int i = 1; i <= Q; ++i) 
		op[i] = (read<int>() - 1), l[i] = read<int>(), r[i] = read<int>(), c[i] = read<int>(), t[i] = read<int>();
	for (int i = Q; i; --i) if (t[i]) {
		if (!op[i]) row.cover(i, c[i], l[i], r[i]);
		else col.cover(i, c[i], l[i], r[i]);
	}
	for (int i = 1; i <= Q; ++i) if (!t[i]) {
		if (!op[i]) row.cover(-i, c[i], l[i], r[i]);
		else col.cover(-i, c[i], l[i], r[i]);
	}
	std::vector<std::pair<int, int>> A, B;
	for (int i = 1; i <= N; ++i) if (row.tim[i]) A.push_back({row.tim[i], row.col[i]});
	for (int j = 1; j <= M; ++j) if (col.tim[j]) B.push_back({col.tim[j], col.col[j]});
	std::sort(A.begin(), A.end()), std::sort(B.begin(), B.end());
	for (int i = (int)A.size() - 1, j = (int)B.size() - 1, R = N, C = M; i != -1 || j != -1; ) {
		if (i == -1) ans[B[j--].second] += R, --C;
		else if (j == -1) ans[A[i--].second] += C, --R;
		else if (A[i].first > B[j].first) ans[A[i--].second] += C, --R; else ans[B[j--].second] += R, --C;
	}
	for (int i = 1; i <= K; ++i) print<long long>(ans[i], " \n"[i == K]);
	return 0;
}
```

---

## 作者：sjr3065335594 (赞：7)

## 题意简述

每次操作给网格某些行或某些列涂色并有覆盖与不覆盖两种操作，问最后每种颜色的格子有几个。

## 思路

看到这题我们可能会想到今年春测的 T1，于是想维护每一行每一列最后被涂上的颜色，再一看数据范围，直接爆炸。

于是改变思路，我们先思考一下简单的，如果只有 $t=1$ 怎么办。我们可以从后往前做，发现从后往前做的时候 $t=1$ 和 $t=0$ 是一样的（都是不覆盖之前的）。

我们考虑对询问进行排序， $t=1$ 按倒序排序，$t=0$ 按正序排序，这样我们就把所有修改都变成了 $t=0$ 的形式。

接下来想一下如何计算每次覆盖对这个颜色的贡献。我们对横行和纵列各开一颗线段树，维护哪些地方还没有被放过，每次操作的贡献就是 $[l,r]$ 区间内没有被覆盖的行或列乘上这几行或几列中没有被覆盖的区域。时间复杂度 $O(q\log q+q\log n)$，但是常数较大，所以需要进行一些优化。

在线段树中，如果找到一个区间全部被覆盖，那就没有必要再去递归了，能节省很多时间。查询的时候，由于会多次查询 $[1,n]$ 和 $[1,m]$ 这个区间，在没有修改的情况下，多次询问很浪费时间，我们就先存储起来，若这个区间被修改再更新这个值。这样就可以通过本题了。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e6+5;
const int M=1e6+5;
const int INF=2e9;
int n,m,k,q,row[N],arr[N];
ll ans[N];
struct SegmentTree {
	int L[N<<2],R[N<<2],sum[N<<2],lz[N<<2];
	inline void pushup(int p) {
		sum[p]=sum[p*2]+sum[p*2+1];
	}
	inline void pushdown(int p) {
		if(!lz[p])return;
		sum[p*2]=sum[p*2+1]=0;
		lz[p*2]=1;
		lz[p*2+1]=1;
		lz[p]=0;
	}
	inline void build(int p,int l,int r) {
		L[p]=l,R[p]=r;
		if(l==r) {
			sum[p]=1;
			return;
		}
		int mid=l+r>>1;
		build(p*2,l,mid);
		build(p*2+1,mid+1,r);
		pushup(p);
	}
	inline void change(int p,int l,int r) {
		if(L[p]>=l&&R[p]<=r) {
			sum[p]=0;
			lz[p]=1;
			return;
		}
		pushdown(p);
		int mid=L[p]+R[p]>>1;
		if(l<=mid&&sum[p*2]!=0)change(p*2,l,r);
		if(r>mid&&sum[p*2+1]!=0)change(p*2+1,l,r);
		pushup(p);
	}
	inline int query(int p,int l,int r) {
		if(L[p]>=l&&R[p]<=r) {
			return sum[p];
		}
		pushdown(p);
		int mid=L[p]+R[p]>>1,val=0;
		if(l<=mid&&sum[p*2]!=0)val+=query(p*2,l,r);
		if(r>mid&&sum[p*2+1]!=0)val+=query(p*2+1,l,r);
		return val;
	}
}tree1,tree2;
struct Query {
	int op,l,r,c,id;
	bool operator < (const Query &rhs) const {
		return id>rhs.id;
	}
}query[N];
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-48;
	x*=f;
}
template<typename T>
inline void write(T x) {
	if(x>=10)write(x/10);
	putchar(x%10+48);
}
int main() {
	read(n),read(m),read(k),read(q); 
	for(int i=1;i<=q;i++) {
		int op,l,r,c,t;
		read(op),read(l),read(r),read(c),read(t);
		if(t==0)query[i]=(Query){op,l,r,c,-i};
		else query[i]=(Query){op,l,r,c,i};
	}
	sort(query+1,query+q+1);
	tree1.build(1,1,n);
	tree2.build(1,1,m);
	ll last1=-1,last2=-1; 
	for(int i=1;i<=q;i++) {
		int op=query[i].op,l=query[i].l,r=query[i].r,c=query[i].c;
		if(op==1) {
			if(last2==-1)last2=tree2.query(1,1,m);
			last1=-1;
			ans[c]+=1ll*tree1.query(1,l,r)*last2;
			tree1.change(1,l,r);
		}
		if(op==2) {
			if(last1==-1)last1=tree1.query(1,1,n);
			last2=-1;
			ans[c]+=1ll*tree2.query(1,l,r)*last1;
			tree2.change(1,l,r);
		}
	}
	for(int i=1;i<=k;i++)printf("%lld ",ans[i]);
	return 0;
}



```


---

## 作者：Pekac (赞：7)

[P9715](https://www.luogu.com.cn/problem/P9715)

不一样的线段树做法。

假如只有 $t=1$ 的操作是容易的。考虑加上 $t=0$ 后怎么做。显然地，我们对每一个操作附上一个时间 $tim$，不妨令 $tim$ 小的数能覆盖掉 $tim$ 大的数。这时候就只需要维护区间取 min 和最后的 $n$ 次求 $c$ 和 $tim$，线段树随便维护一下。然后我是对行和列都开了一棵。最后统计就是枚举每一行，统计是 $c$ 的个数，即 $m$ 减去小于 $tim_{now}$ 的个数，对列再做一遍类似的统计，加起来即可。求全局小于某个值的个数可以开一个桶，做一遍前缀和。

注意 long long 以及赋初值。

然后你发现就 T 掉了，常数巨大。可以在区间取 min 时判断一下当前节点的 $tim_u$ 是否小于传入的值 $w$，如果是就直接返回，配合快读容易通过。

代码：
```cpp
struct segt{
	struct node{
		int v,t,tgv,tgt;
	} tr[N<<2];
	void pushdown(int u){
		if(tr[u].tgt!=inf){
			if(tr[u].tgt<tr[u<<1].t)tr[u<<1].v=tr[u<<1].tgv=tr[u].tgv,tr[u<<1].t=tr[u<<1].tgt=tr[u].tgt;
			if(tr[u].tgt<tr[u<<1|1].t)tr[u<<1|1].v=tr[u<<1|1].tgv=tr[u].tgv,tr[u<<1|1].t=tr[u<<1|1].tgt=tr[u].tgt;
			tr[u].tgv=0,tr[u].tgt=inf;
		}
	}
	void update(int u,int l,int r,int L,int R,int c,int tim){
		if(tr[u].t!=inf&&tim>tr[u].t)return;
		if(L<=l&&r<=R){
			if(tr[u].t==inf||tim<tr[u].t)tr[u].v=tr[u].tgv=c,tr[u].t=tr[u].tgt=tim;
			return;
		}
		pushdown(u);
		int mid=(l+r)>>1;
		if(L<=mid)update(u<<1,l,mid,L,R,c,tim);
		if(mid<R)update(u<<1|1,mid+1,r,L,R,c,tim);
	}
	void query(int u,int l,int r,int typ){
		if(l==r){ if(tr[u].t!=inf)t[tr[u].t][typ]++,t2[l][typ]=tr[u].t,co[l][typ]=tr[u].v;return; }
		pushdown(u);
		int mid=(l+r)>>1;
		query(u<<1,l,mid,typ);
		query(u<<1|1,mid+1,r,typ);
	}
} ta,tb;

int main(){
	for(int i=0;i<N<<2;i++)ta.tr[i].t=tb.tr[i].t=ta.tr[i].tgt=tb.tr[i].tgt=inf;
	n=read(),m=read(),K=read(),Q=read();
	for(int i=1,opt,l,r,c,t;i<=Q;i++){
		opt=read(),l=read(),r=read(),c=read(),t=read();
		if(opt==1)ta.update(1,1,n,l,r,c,t?Q-i:i+Q);
		else tb.update(1,1,m,l,r,c,t?Q-i:i+Q);
	}
	ta.query(1,1,n,0),tb.query(1,1,m,1);
	for(int i=1;i<=Q<<1;i++)t[i][0]+=t[i-1][0];for(int i=1;i<=Q<<1;i++)t[i][1]+=t[i-1][1];
	for(int i=1;i<=m;i++){
		int cnt=t[t2[i][1]][0];
		col[co[i][1]]+=n-cnt;
	}
	for(int i=1;i<=n;i++){
		int cnt=t[t2[i][0]][1];
		col[co[i][0]]+=m-cnt;
	}
	for(int i=1;i<=K;i++)print(col[i],' ');
	return 0;
}
```

---

## 作者：VioletIsMyLove (赞：7)

既然这道题卡了线段树，那么我就非要发一篇超级优化线段树的题解 qwq。

对于 $t=1$ ，我们发现后涂的肯定不会被先涂的盖住，所以只需要倒序处理直接计算就行。

而对于 $t=0$ ，我们也会发现如果它不会盖住在它之前涂的，反过来看的话就是在它之前涂的把它盖住了！那么只需要将 $t=0$ 的情况正序接在倒序的 $t=1$ 后面就行了。

所以每次操作就只需要找到当前 $l$ 和 $r$ 范围内已经被涂过的行或列再乘以未被涂过的列或行(前面是行后面就是列，前面是列后面就是行)。

而这个操作肯定不能每次 $O(N)$ 去遍历执行，因此我们就可以引入线段树直接处理区间。

很可惜，这道题的最后两个点卡了线段树，因此我们需要优化！

首先这道题的读入数据很大，我们需要将读数据的方式改成内存池读法。

然后我们会发现如果当前的操作是对行进行处理的，在计算未被涂过的列的时候并不需要再去进行区间查询，而是可以在上一次处理列的时候进行记录。对当前操作列也是同理。

最重要的来了，这道题的懒标记并不需要和正常线段树的一样用过就要擦除，而是可以一直保留，在查询的时候如果当前的区块已经被懒标记标记过了，就可以直接弹出区间长度。

具体细节已经在代码里面标记出来了，看代码吧。

Code:
```cpp
#include<algorithm>
#include<cstdio>
#include<iostream>
using namespace std;
namespace IO {//内存池输入
    const int SIZE = (1 << 22) + 1;
    char ibuf[SIZE], *iS, *iT;
    inline char gc() {
        return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
    }
    inline void qread() {}
    template<class T1, class ...T2>
    inline void qread(T1 &IEE, T2 &... ls) {
         T1 __ = 0, ___ = 1;
         char ch;
        while (!isdigit(ch = gc())) ___ = (ch == '-') ? -___ : ___;
        do {
            __ = (__ << 1) + (__ << 3) + (ch ^ 48);
        } while (isdigit(ch = gc()));
        __ *= ___;
        IEE = __;
        qread(ls...);
        return;
    }
}
using namespace IO;
struct ZS{
	int op,l,r,c;
}a[2][2000005];
int n,m,k,q,N,M,x,y,cnt;
int t[2][8000005],tag[2][8000005];
int len[2];
long long ans[500005];
void push_up(int p,int opt){t[opt][p]=t[opt][p<<1]+t[opt][p<<1|1];}
void push_down(int p,int l,int r,int opt){t[opt][p<<1]=r-l+2>>1;t[opt][p<<1|1]=r-l+1>>1;tag[opt][p<<1]=tag[opt][p<<1|1]=1;}//不需要擦除懒标记了
void update(int l,int r,int p,int opt){
	if(tag[opt][p]){push_down(p,l,r,opt);return;}
	if(x<=l&&r<=y){t[opt][p]=r-l+1;tag[opt][p]=1;return;}
	int mid=(r-l>>1)+l;
	if(x<=mid)update(l,mid,p<<1,opt);
	if(mid<y)update(mid+1,r,p<<1|1,opt);
	push_up(p,opt);
}
int query(int l,int r,int p,int opt){
	if(x<=l&&r<=y)return t[opt][p];
	int res=0,mid=(r-l>>1)+l;
	if(tag[opt][p]){
		if(l<=x&&y<=r)return y-x+1;//如果包含直接弹出区间长度
		push_down(p,l,r,opt);
	}
	if(x<=mid)res+=query(l,mid,p<<1,opt);
	if(mid<y)res+=query(mid+1,r,p<<1|1,opt);
	return res;
}
int main(){
	qread(n,m,k,q);N=n;M=m;
	int op,l,r,c,t;
	for(int i=1;i<=q;i++){
		qread(op,l,r,c,t);op--;
		if(t)a[0][++len[0]]=(ZS){op,l,r,c};
		else a[1][++len[1]]=(ZS){op,l,r,c};
	}
	for(int i=len[0];i>=1;i--){//倒序处理t=1
		if(!N||!M)break;
		x=a[0][i].l;y=a[0][i].r;
		cnt=query(1,a[0][i].op?m:n,1,a[0][i].op);
		ans[a[0][i].c]+=(long long)(a[0][i].r-a[0][i].l+1-cnt)*(a[0][i].op?N:M);
		update(1,a[0][i].op?m:n,1,a[0][i].op);
		if(a[0][i].op)M-=a[0][i].r-a[0][i].l+1-cnt;else N-=a[0][i].r-a[0][i].l+1-cnt;
	}
	for(int i=1;i<=len[1];i++){//正序处理t=0
		if(!N||!M)break;
		x=a[1][i].l;y=a[1][i].r;
		cnt=query(1,a[1][i].op?m:n,1,a[1][i].op);
		ans[a[1][i].c]+=(long long)(a[1][i].r-a[1][i].l+1-cnt)*(a[1][i].op?N:M);
		update(1,a[1][i].op?m:n,1,a[1][i].op);
		if(a[1][i].op)M-=a[1][i].r-a[1][i].l+1-cnt;else N-=a[1][i].r-a[1][i].l+1-cnt;
	}
	for(int i=1;i<=k;i++)printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：Basori_Tiara (赞：7)

RT，严格难于白雪皑皑的题评绿？

操作被分为两种，一种是全覆盖了，另一种是覆盖没覆盖过的。

然后你考虑一个全覆盖的操作，我们很难记录他哪些位置会生效，所以我们来记录他哪些位置不会生效，你发现，不覆盖的操作是没用的，全覆盖的操作才对他有用。

你考虑维护一个行的数组和一个列的数组表示这一行或者一列有没有被这样操作过，然后你倒序操作一下，考虑一次操作，他后面把他覆盖掉的已经被你维护出来了，那么很明显你就只需要维护一下你目前的区间内有多少个没有被操作过的行或者列，然后直接乘算就可以知道这次全覆盖操作对颜色的贡献。

那你维护不是全覆盖的操作，你考虑所有全覆盖的操作他都不准许走，注意是所有的，也就是在它后面的也算，为什么呢，因为他前面的，他不能覆盖已覆盖过的，他后面的，如果他在这里已经覆盖了，那么后面会被全覆盖的操作送走所以没有意义。

但是你考虑你这个不是全覆盖的操作做完之后也会填满一整行，所以你也要把这些标记全打上，然后就变成了要维护全局的全覆盖操作和前缀的不全覆盖操作，这个正着枚就行了。

然后你发现，全局的你可以动态维护，其余的你标记过的一定不会重复利用，这个东西就是[白雪皑皑](https://www.luogu.com.cn/problem/P2391)的形式，用并查集来维护下一个可用点在哪就可以了。

时间复杂度 $O(q)$，还有一个反阿克曼函数，不过太小当常数因子忽略了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2000005;
class SegTree{
   public:
   int father[MAXN];
   int sum;
   int find(int x){
      if(father[x]==x)return x;
      return father[x]=find(father[x]);
   }
   int query(int cur,int lt,int rt){
      int cnt=0;
      for(int i=find(lt);i<=rt;i=find(i)){
         cnt++;
         father[i]=i+1;
         sum--;
      }
      return (rt-lt+1)-cnt;
   }
   void build(int cur,int lt,int rt){
      sum=rt-lt+1;
      for(int i=lt;i<=rt+1;i++){
         father[i]=i;
      }
      return;
   }
}P,Q;
struct node{
   int opt,lt,rt,col,type;
}query[2000005];
int n,m,k,q;
long long ans[2000005];
signed main(){
   scanf("%d%d%d%d",&n,&m,&k,&q);
   int opt,lt,rt,col,type,tmp1,tmp2,len;
   for(int i=1;i<=q;i++){
      scanf("%d%d%d%d%d",&opt,&lt,&rt,&col,&type);
      query[i]=node{opt,lt,rt,col,type};
      if(type==1){
         if(opt==1){
            ans[col]+=1ll*(rt-lt+1)*m;
         }
         else{
            ans[col]+=1ll*(rt-lt+1)*n;
         }
      }
   }
   P.build(1,1,n);
   Q.build(1,1,m);
   for(int i=q;i>=1;i--){
      if(query[i].type==0)continue;
      opt=query[i].opt;
      lt=query[i].lt;
      rt=query[i].rt;
      col=query[i].col;
      len=rt-lt+1;
      if(opt==1){
         tmp1=P.query(1,lt,rt);
         tmp2=m-Q.sum;
         ans[col]-=1ll*(1ll*(len)*(m)-1ll*(1ll*(len-tmp1)*(m-tmp2)));
      }
      else{
         tmp1=n-P.sum;
         tmp2=Q.query(1,lt,rt);
         ans[col]-=1ll*(len)*(n)-1ll*(n-tmp1)*(len-tmp2);
      }
   }
   for(int i=1;i<=q;i++){
      if(query[i].type==1)continue;
      opt=query[i].opt;
      lt=query[i].lt;
      rt=query[i].rt;
      col=query[i].col;
      len=rt-lt+1;
      if(opt==1){
         tmp1=P.query(1,lt,rt);
         tmp2=m-Q.sum;
         ans[col]+=1ll*(len-tmp1)*(m-tmp2);
      }
      else{
         tmp1=n-P.sum;
         tmp2=Q.query(1,lt,rt);
         ans[col]+=1ll*(n-tmp1)*(len-tmp2);
      }
   }
   for(int i=1;i<=k;i++){
      printf("%lld ",ans[i]);
   }
   return 0;
}
```

---

## 作者：Jorisy (赞：7)

容易发现这是 P2391 加强版。

把操作离线下来。

可以发现，$t=0$ 时的操作等价于最开始涂这个色而后被以上操作覆盖掉。于是我们考虑开一个 deque，为零时在队头插入，否则在队尾插入。

然后沿用 P2391 的思路，倒序遍历 deque，对行列分别开一个并查集，$fa_i$ 表示 $1\sim i$ 行或列中未被涂色的编号最大的编号（如果没有就是 $0$）。

以行为例子，我们每次在涂色时记 $sr,sc,t$，前二者表示这个矩阵已经涂色的行（列）个数，第三者表示当前涂色成功涂了的行（列）数，每次涂完就让答案加上 $(m-sc)t$（列同理）。

于是做完了。

赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int op,l,r,c,t;
};
deque<node>a;
int n,m,k,q,sr,sc,far[2000005],fac[2000005];
long long ans[500005];

//bool cmp(node x,node y)
//{
//	return x.t<y.t;
//}

int findr(int x)
{
	return x==far[x]?x:far[x]=findr(far[x]);
}

int findc(int x)
{
	return x==fac[x]?x:fac[x]=findc(fac[x]);
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1;i<=q;i++)
	{
		node x;
		scanf("%d%d%d%d%d",&x.op,&x.l,&x.r,&x.c,&x.t);
		if(x.t) a.push_back(x);
		else a.push_front(x);
	}
	for(int i=1;i<=n;i++) far[i]=i;
	for(int i=1;i<=m;i++) fac[i]=i;
	for(int i=q-1;~i;i--)
	{
		if(a[i].op<2)
		{
			int t=0;
			for(int j=a[i].r;j>=a[i].l;j=far[j])
			{
				if(findr(j)==j)
				{
					far[j]=findr(j-1);
					sr++;
					t++;
				}
			}
			ans[a[i].c]+=1ll*t*(m-sc);
			continue;
		}
		int t=0;
		for(int j=a[i].r;j>=a[i].l;j=fac[j])
		{
			if(findc(j)==j)
			{
				fac[j]=findc(j-1);
				sc++;
				t++;
			}
		}
		ans[a[i].c]+=1ll*t*(n-sr);
	}
	for(int i=1;i<=k;i++) printf("%lld ",ans[i]);
 	return 0;
}
```

---

## 作者：Lele_Programmer (赞：7)

写一篇可能**不是最优**但是比较**容易理解**的解法，**适宜新手**阅读。（本思路要加快读卡常才能AC）

我们可以把每一次涂颜色的区域看作是一块“地毯”，每一块，用左上角的行和列和右下角的行和列坐标表示区域，每一块还需要一个 color 表示该块的颜色，因此，可以写出以下结构体：

```cpp
struct node {
    int r1,c1;
    int r2,c2;
    int color;
};
```

当 $t=0$ 时，只对还未涂过颜色的格子涂色，可以想成这块“地毯”**被铺在了其余地毯的下方**。

当 $t=1$ 时，对整个区域全部重新涂色，可以想成这块“地毯”**被铺在了其余地毯的最上方**。

为了把“地毯”的互相覆盖的关系处理好，可以用一个 deque 来维护，越靠近队头的“地毯”放在越下面。

处理好上下覆盖的关系后，建一个 vector 来辅助计算，从最底层的“地毯”开始枚举，对于每一块“地毯”，枚举 vector 中存在的“地毯”，判断这两块“地毯”的覆盖关系，重叠部分删除，更新 vector 中原先“地毯”的覆盖区间，最后把新的这块“地毯”加入 vector 。

如何表示两块“地毯”的位置关系？

不妨设一块“地毯”的左上角行列分别为 r1 和 c1 ，右下角行列分别为 r2 和 c2，从 deque 中拿出来的“地毯”为 nd ，vector 数组为 v ，然后分类讨论以下几种情况。

1. 当 `nd.c1==1 && nd.c2==m && v[j].r1<nd.r1 && v[j].r2>nd.r2` 时，也就是当新的“地毯”把原来的“地毯”**劈成上下两块**，将原来的“地毯”删掉，创建两块新的地毯，为劈开后上下剩余的区域，然后加入 vector 中。

2. 当 `nd.c1==1 && nd.c2==m && (v[j].r1>=nd.r1 && v[j].r1<=nd.r2) && v[j].r2>nd.r2` 时，也就是当新的“地毯”把原来的“地毯”的**靠上方的部分覆盖了**，只留下下面一部分，直接将 vector 中的地毯的数据进行更新。

3. 当 `nd.c1==1 && nd.c2==m && v[j].r1<nd.r1 && (v[j].r2<=nd.r2 && v[j].r2>=nd.r1)` 时，也就是当新的“地毯”把原来的“地毯”的**靠下方的部分覆盖了**，只留下上面一部分，也是直接将 vector 中的地毯的数据进行更新。

4. 当 `nd.c1==1 && nd.c2==m && (v[j].r1>=nd.r1 && v[j].r1<=nd.r2) && (v[j].r2>=nd.r1 && v[j].r2<=nd.r2)` 时，也就是原来的“地毯”被新的“地毯”**完全覆盖**，那直接将它删掉就好了。

5. 当 `nd.r1==1 && nd.r2==n && v[j].c1<nd.c1 && v[j].c2>nd.c2` 时，也就是把原来的地毯**劈成左右两块**，和情况1同理，删掉原来的，添加左右两块。

6. 当 `nd.r1==1 && nd.r2==n && v[j].c1<nd.c1 && (v[j].c2>=nd.c1 && v[j].c2<=nd.c2)` 时，也就是原来的地毯**靠右边的部分被覆盖了**，只留下左边一部分，直接更新 vector 中的数据即可。

7. 当 `nd.r1==1 && nd.r2==n && (v[j].c1>=nd.c1 && v[j].c1<=nd.c2) && v[j].c2>nd.c2` 时，也就是原来的地毯**靠左边的部分被覆盖了**，只留下右边一部分，直接更新 vector 中的数据即可。

8. 当 `nd.r1==1 && nd.r2==n && (v[j].c1>=nd.c1 && v[j].c1<=nd.c2) && (v[j].c2>=nd.c1 && v[j].c2<=nd.c2)` 时，也就是被**完全覆盖**了，直接从 vector 中删掉就好了。

最后要计算颜色的数量，再枚举一次 vector 中剩下的区间，这个应该不难理解了吧。

虽然这个比较暴力，还挺好理解的，但是这个思路不是最优解，时间复杂度也比较极限，开了快读才能过。

```cpp
namespace IO {
    inline void read(int &a) {
        int sym=1,num=0;
        char c=getchar();
        while (c<'0' || c>'9') {
            if (c=='-') {
                sym=-1;
        }
        c=getchar();
        }
        while (c>='0' && c<='9') {
            num=num*10+c-'0';
            c=getchar();
        }
        a=sym*num;
    }
    inline void write(int a) {
        if (a<0) {
            putchar('-');
            a*=-1;
        }
        if (a>=10) {
            write(a/10);
        }
        putchar(a%10+'0');
    }
}

using namespace IO;
```

最后强调一句：十年 OI 一场空，不开 long long 见祖宗！

提交记录：https://www.luogu.com.cn/record/127881990

最终代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

namespace IO {
    inline void read(int &a) {
        int sym=1,num=0;
        char c=getchar();
        while (c<'0' || c>'9') {
            if (c=='-') {
                sym=-1;
        }
        c=getchar();
        }
        while (c>='0' && c<='9') {
            num=num*10+c-'0';
            c=getchar();
        }
        a=sym*num;
    }
    inline void write(int a) {
        if (a<0) {
            putchar('-');
            a*=-1;
        }
        if (a>=10) {
            write(a/10);
        }
        putchar(a%10+'0');
    }
}

using namespace IO;

int n,m,k,q;
int op,l,r,c,t;
int colors[500005];

struct node {
    int r1,c1;
    int r2,c2;
    int color;
};

vector<node> v;
deque<node> dq;

signed main() {
    // scanf("%lld %lld %lld %lld",&n,&m,&k,&q);
    read(n);read(m);read(k);read(q);
    memset(colors,0,sizeof(colors));
    for (int i=1;i<=q;++i) {
        // scanf("%lld %lld %lld %lld %lld",&op,&l,&r,&c,&t);
        read(op);read(l);read(r);read(c);read(t);
        node nd;
        if (op==1) {
            nd.r1=l;
            nd.r2=r;
            nd.c1=1;
            nd.c2=m;
            nd.color=c;
        } else {
            nd.c1=l;
            nd.c2=r;
            nd.r1=1;
            nd.r2=n;
            nd.color=c;
        }
        if (t==0) {
            dq.push_front(nd);
        } else {
            dq.push_back(nd);
        }
    }
    node nd,nd2;
    for (int i=1;i<=q;++i) {
        nd=dq.front();
        for (int j=0;j<v.size();++j) {
            if (nd.c1==1 && nd.c2==m && v[j].r1<nd.r1 && v[j].r2>nd.r2) {
                nd2.r1=v[j].r1;
                nd2.r2=nd.r1;
                nd2.c1=v[j].c1;
                nd2.c2=v[j].c2;
                nd2.color=v[j].color;
                v.push_back(nd2);
                nd2.r1=nd.r2;
                nd2.r2=v[j].r2;
                v.push_back(nd2);
                v.erase(v.begin()+j);
                --j;
            } else if (nd.c1==1 && nd.c2==m && (v[j].r1>=nd.r1 && v[j].r1<=nd.r2) && v[j].r2>nd.r2) {
                v[j].r1=nd.r2+1;
            } else if (nd.c1==1 && nd.c2==m && v[j].r1<nd.r1 && (v[j].r2<=nd.r2 && v[j].r2>=nd.r1)) {
                v[j].r2=nd.r1-1;
            } else if (nd.c1==1 && nd.c2==m && (v[j].r1>=nd.r1 && v[j].r1<=nd.r2) && (v[j].r2>=nd.r1 && v[j].r2<=nd.r2)) {
                v.erase(v.begin()+j);
                --j;
            } else if (nd.r1==1 && nd.r2==n && v[j].c1<nd.c1 && v[j].c2>nd.c2) {
                nd2.r1=v[j].r1;
                nd2.c1=v[j].c1;
                nd2.r2=v[j].r2;
                nd2.c2=nd.c1;
                nd2.color=v[j].color;
                v.push_back(nd2);
                nd2.c1=nd.c2;
                nd2.c2=v[j].c2;
                v.push_back(nd2);
                v.erase(v.begin()+j);
                --j;
            } else if (nd.r1==1 && nd.r2==n && v[j].c1<nd.c1 && (v[j].c2>=nd.c1 && v[j].c2<=nd.c2)) {
                v[j].c2=nd.c1-1;
            } else if (nd.r1==1 && nd.r2==n && (v[j].c1>=nd.c1 && v[j].c1<=nd.c2) && v[j].c2>nd.c2) {
                v[j].c1=nd.c2+1;
            } else if (nd.r1==1 && nd.r2==n && (v[j].c1>=nd.c1 && v[j].c1<=nd.c2) && (v[j].c2>=nd.c1 && v[j].c2<=nd.c2)) {
                v.erase(v.begin()+j);
                --j;
            }
        }
        v.push_back(nd);
        dq.pop_front();
    }
    for (int i=0;i<v.size();++i) {
        colors[v[i].color]+=(v[i].r2-v[i].r1+1)*(v[i].c2-v[i].c1+1);
    }
    for (int i=1;i<=k;++i) {
        // printf("%lld ",colors[i]);
        write(colors[i]);
        putchar(' ');
    }
    return 0;
}
```

---

## 作者：SError_ (赞：6)

按顺序依次操作的话就会有这样的情况：$t=1$ 时，我们需要减掉一些已经染色的格子对答案的贡献。这样不太好做，考虑在操作的顺序上做些手脚。

由于 $t=1$ 的染色操作优先级比 $t=0$ 高，且 $t=1$ 的操作越往后优先级越高，所以我们先**倒序**进行所有 $t=1$ 的操作，然后**顺序**进行所有 $t=0$ 的操作。

如此可以把所有操作都变成 $t=0$ 的情况。

以行为例，假设现在要将 $[l,r]$ 行染色为 $c$.

对于每个没有进行过行染色操作的 $i\in[l,r]$，设当前一共有 $fy$ 列进行过列染色操作，那么就会新产生 $m-fy$ 个颜色为 $c$ 的格子，同时记 $fx$ 为进行过行染色操作的行数，令 $fx$ 加上 $1$.

对于列染色操作同理，每个未染色过的列 $i\in[l,r]$ 都会对颜色 $c$ 产生 $n-fx$ 的贡献。

但是直接判断每个 $i$ 是否染色过的复杂度是 $O(nq)$ 的（假设 $n,m$ 同阶），不难想到并查集：以行为例，初始让 $i\in[1,n+1]$ 的 $fa$ 均指向自己，染色后将 $fa$ 指向 $i+1$，表示不需要进行操作，调用 $find$ 即可找到下一个操作的位置。

可以做到时间复杂度 $O(n)$，我的代码中直接对每次操作赋予了一个时间戳进行排序。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2000010
#define M 500010
using namespace std;
int read(){
	int x=0,w=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*w;
}
int n,m,k,Q;
struct option{
	int typ,l,r,c,tim;//1 -> line 2 -> row
	bool operator<(const option &x)const{
		return tim<x.tim;
	}
}a[N];
int c1,c2;
ll ans[M];int fx,fy;
set<int>line,row;
int gx[N],gy[N];
int findx(int x){
	return gx[x]==x?x:gx[x]=findx(gx[x]);
}
int findy(int x){
	return gy[x]==x?x:gy[x]=findy(gy[x]);
}
int main(){
	n=read(),m=read(),k=read(),Q=read();
	for(int i=1;i<=Q;i++){
		a[i].typ=read(),a[i].l=read(),a[i].r=read(),a[i].c=read();
		a[i].tim=read()?--c1:++c2;
	}
	for(int i=1;i<=n+1;i++)gx[i]=i;
	for(int i=1;i<=m+1;i++)gy[i]=i;
	sort(a+1,a+1+Q);
	queue<int>q;
	for(int i=1,typ,l,r,c;i<=Q;i++){
		typ=a[i].typ,l=a[i].l,r=a[i].r,c=a[i].c;
		if(typ==1){
			for(int x=findx(l);x<=r;x=findx(x+1))
				fx++,ans[c]+=m-fy,gx[x]=x+1;
		}
		if(typ==2){
			for(int x=findy(l);x<=r;x=findy(x+1))
				fy++,ans[c]+=n-fx,gy[x]=x+1;
		}
	}
	for(int i=1;i<=k;i++)
		printf("%lld ",ans[i]);
	printf("\n");
	
	return 0;
}
```

---

## 作者：Loser_Syx (赞：6)

考虑优先级。

首先我先 $t=1$ 的肯定最先，因为 $t=1$ 是覆盖的，不存在被遮挡这一说，其中 $t=1$ 时按照从后往前搞。

其次 $t=0$，按照从前往后，因为后面不会影响前面的。

然后统一完 $t$ 之后发现每个操作就变成一样的了，都是删除某行/列，于是就可以考虑维护了。

不难想到使用「白雪皑皑」的方式维护，并查集维护右边最近的一个没有删除的节点，对其进行删除。

由于每个节点只删一次，且此并查集是不能按秩合并的，所以复杂度为极小常数 $O(n \log n)$。

```cpp
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define int long long
#define yes puts("Yes")
#define no puts("No")
namespace Syxqwq {
	inline int read() {
		int x = 0, f = 1;
		char c = getchar();
		while (c > '9' || c < '0') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c <= '9' && c >= '0') {
			x = (x << 1) + (x << 3) + (c ^ '0');
			c = getchar();
		}
		return x * f;
	}
	void Write(int x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x > 9) Write(x / 10);
		putchar(x % 10 + '0');
	}
	inline void write(int x, char c) {
		Write(x), putchar(c);
	}
} using namespace Syxqwq;
int ans[2010101];
struct node {
	int op, l, r, c, t;
	int i;
	bool operator < (const node &a) const {
		if (t != a.t) return t == 1;
		else if(t == 1) return i > a.i;
		else return i < a.i;
	}
} p[2010101];

int fa[2][2010101];
int find(int x, bool tp) {
	if(fa[tp][x] == x)
		return x;
	return fa[tp][x] = find(fa[tp][x], tp);
}

void merge(int u, int v, int tp) {
	u = find(u,tp);
	v = find(v,tp);
	fa[tp][u] = v;
}

signed main() {
	int n = read(), m = read(), k = read(), l = read();
	for (int i = 1; i <= l; ++i) {
		p[i].op = read();
		p[i].l = read();
		p[i].r = read();
		p[i].c = read();
		p[i].t = read();
		p[i].i = i;
	}
	for(int i = 1; i <= max(n,m) + 5; ++i) {
		fa[1][i] = fa[0][i] = i;
	}
	sort(p + 1, p + 1 + l);
//	set<int> s, t;
//	for (int i = 1; i <= n; ++i) s.insert(i); // 行
//	for (int j = 1; j <= m; ++j) t.insert(j); // 列
	for (int i = 1; i <= l; ++i) {
		if (p[i].op == 1) {
			int ptr = find(p[i].l, 0);
			while(ptr <= p[i].r) {
				ans[p[i].c] += m;
				--n;
				int nxt = find(ptr, 0);
				if(nxt <= p[i].r) {
					merge(ptr, nxt + 1, 0);
				}
				ptr = find(nxt, 0);
			}
		} else {
			int ptr = find(p[i].l, 1);
			while(ptr <= p[i].r) {
				ans[p[i].c] += n;
				--m;
				int nxt = find(ptr, 1);
				if(nxt <= p[i].r) {
					merge(ptr, nxt + 1, 1);
				}
				ptr = find(nxt, 1);
			}
//			auto x = t.lower_bound(p[i].l), y = t.upper_bound(p[i].r);
//			vector<int> ers;
//			while (x != y) {
//				ers.emplace_back(*x);
//				++x;
//			}
//			for (const auto& j : ers) {
//				t.erase(j);
//				ans[p[i].c] += n;
//				--m;
//			}
		}
	}
	for (int i = 1; i <= k; ++i) write(ans[i], ' ');
	return 0;
}
```

---

## 作者：escapist404 (赞：6)

注意到 $t=0$ 的倒过来执行就变成了 $t=1$，反之亦然。

我们将所有的操作离线下来，考虑到对于同一个位置的操作，$t=1$ 的必然比 $t=0$ 的有效（即 $t=1$ 的操作能够覆盖 $t=0$ 的操作），我们先倒序处理 $t=1$ 的操作，再正序处理 $t=0$ 的操作，因为这样避免了颜色由于覆盖先后顺序造成的冲突。

注意到这个网格始终满足：在上面任选一个有颜色的格子，其所在行（或列）必然上色；任选一个无颜色的格子（下文称为空格子），其所在行（和列）必然没有上色。（原因是染色操作只针对行或列）。

对于一个操作，其对将涂上的颜色的贡献是覆盖区域的空格子数量，由第三段的内容可知，空格子的数量即为空行的数量乘空列的数量。

考虑建立两棵线段树 $S$、$T$ 分别维护 $1 \sim m$ 列中空列的数量、$1 \sim n$ 行中空行的数量。

设 $a$ 序列为每种颜色的格子数量。

* 对 $op = 1$ 的操作 $l, r, c$，$a_c \gets a_c + S(1, m) \times T(l, r)$，$T(l, r) \gets 0$。
* 对 $op = 2$ 的操作 $l, r, c$，$a_c \gets a_c + S(l, r) \times T(1, n)$，$S(l, r) \gets 0$。

然而时间复杂度为 $O(n \log n)$，赛时根本过不去。

注意到我们要进行 $q$ 次区间覆盖 $0$ 的操作，如果一个结点的值已经为 $0$ 就不再向下更新。

加上这一优化后，算法的运行时间实际接近 $O(n)$，但似乎可以卡到 $O(n \log n)$（每次强制其访问 $O(\log n)$ 个点）。

欢迎 hack，或提供时间复杂度的证明。

```cpp
#include <bits/stdc++.h>

template <const size_t _Size = 16>
class quick_io {
private:
  char buf_in[1 << _Size], buf_out[1 << _Size];
  size_t index_in, index_out;
  FILE *in, *out;

public:
  inline void flush_in() {
    fread(buf_in, sizeof(char), 1 << _Size, in), index_in = 0;
  }
  inline void flush_out() {
    fwrite(buf_out, index_out, 1, out), index_out = 0;
  }
  inline quick_io& operator>>(char& ch) {
    if (index_in == (1 << _Size)) flush_in();
    ch = buf_in[index_in++];
    return *this;
  }
  inline quick_io& operator>>(char* str) {
    size_t origin = strlen(str);
    char ch = 0;
    size_t len = 0;
    do {
      *this >> ch;
      if (!isgraph(ch)) break;
      str[len++] = ch;
    } while (true);
    if (len < origin)
      while (len < origin) str[len++] = 0;
    return *this;
  }
  template <typename T>
  inline quick_io& operator>>(T& value) {
    value = 0;
    short sign = 1;
    char ch = 0;
    do sign = ch == '-' ? -1 : sign, *this >> ch;
    while (ch < '0' || ch > '9');
    do value = (value << 3) + (value << 1) + ch - '0', *this >> ch;
    while ('0' <= ch && ch <= '9');
    value *= sign;
    return *this;
  }
  inline quick_io& operator<<(const char ch) {
    if (index_out == (1 << _Size)) flush_out();
    buf_out[index_out++] = ch;
    return *this;
  }
  inline quick_io& operator<<(const char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) *this << str[i];
    return *this;
  }
  inline quick_io& operator<<(char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) *this << str[i];
    return *this;
  }
  template <typename T>
  inline quick_io& operator<<(T value) {
    if (value < 0) *this << '-', value = -value;
    static size_t stack[50], dep = 0;
    do stack[++dep] = value % 10, value /= 10;
    while (value);
    do *this << (char)(stack[dep--] + '0');
    while (dep);
    return *this;
  }
  quick_io(FILE* in = stdin, FILE* out = stdout)
    : index_in(0), index_out(0), in(in), out(out) {}
  ~quick_io() { flush_out(); }
};

using i64 = long long;

struct Value {
  i64 sum;
  int size;
  Value(i64 sum = 0, int size = 1) : sum(sum), size(size) {}
};

struct Lazy {
  i64 assign;
  Lazy(i64 assign = -1) : assign(assign) {}
};

Value operator+(Value x, Value y) {
  return Value(x.sum + y.sum, x.size + y.size);
}

Value operator+(Value x, Lazy y) {
  if (y.assign == -1)
    return x;
  else
    return Value(y.assign * x.size, x.size);
}

Lazy operator+(Lazy x, Lazy y) {
  if (y.assign == -1)
    return x;
  else
    return y;
}

class LazySegTree {
private:
  int n, root;
  std::vector<Value> value;
  std::vector<Lazy> lazy;
  struct Child {
    int lhs, rhs;
    Child(int lhs = -1, int rhs = -1) : lhs(lhs), rhs(rhs) {}
  };
  std::vector<Child> child;
  void check_node(int& id, int size) {
    if (~id) return;
    id = value.size();
    value.push_back(Value(0, size));
    lazy.push_back(Lazy());
    child.push_back(Child());
  }
  void push_up(int id) {
    value[id] = value[child[id].lhs] + value[child[id].rhs];
  }
  void push_down(int id, int size) {
    check_node(child[id].lhs, size / 2);
    value[child[id].lhs] = value[child[id].lhs] + lazy[id];
    lazy[child[id].lhs] = lazy[child[id].lhs] + lazy[id];
    check_node(child[id].rhs, size - size / 2);
    value[child[id].rhs] = value[child[id].rhs] + lazy[id];
    lazy[child[id].rhs] = lazy[child[id].rhs] + lazy[id];
    lazy[id] = Lazy();
  }
  void set(int id, int l, int r, int _l, int _r, Lazy _k) {
    if (_l <= l && r <= _r)
      return value[id] = value[id] + _k, lazy[id] = lazy[id] + _k, void();
    push_down(id, r - l);
    int m = (l + r) / 2;
    if (_l < m) {
      if (value[child[id].lhs].sum != 0)
	set(child[id].lhs, l, m, _l, _r, _k);
    }
    if (_r > m) {
      if (value[child[id].rhs].sum != 0)
	set(child[id].rhs, m, r, _l, _r, _k);
    }
    push_up(id);
  }
  Value get(int id, int l, int r, int _l, int _r) {
    if (_l <= l && r <= _r) return value[id];
    push_down(id, r - l);
    int m = (l + r) / 2;
    if (_l >= m) {
      if (value[child[id].rhs].sum != 0)
	return get(child[id].rhs, m, r, _l, _r);
      else
	return 0;
    }
    if (_r <= m) {
      if (value[child[id].lhs].sum != 0)
	return get(child[id].lhs, l, m, _l, _r);
      else
	return 0;
    }
    return (value[child[id].lhs].sum != 0 ? get(child[id].lhs, l, m, _l, _r)
	    : 0) +
      (value[child[id].rhs].sum != 0 ? get(child[id].rhs, m, r, _l, _r)
       : 0);
  }

public:
  void set(int l, int r, Lazy k) { set(root, 0, n, l, r, k); }
  void set(int p, Lazy k) { set(p, p + 1, k); }
  void set(Lazy k) { set(0, n, k); }
  Value get(int l, int r) {
    if (r <= l) return Value();
    return get(root, 0, n, l, r);
  }
  Value get(int p) { return get(p, p + 1); }
  Value get() { return value.front(); }
  LazySegTree(int n) : n(n), root(-1) { check_node(root, n); }
};

int main() {
  quick_io<16> io;
  int n, m, k, q;
  io >> n >> m >> k >> q;

  std::vector<i64> answer(k);

  std::vector<std::tuple<int, int, int, int, int, int>> p;
  for (int i = 0; i < q; ++i) {
    int op, l, r, c, t;
    io >> op >> l >> r >> c >> t;
    --c, --l;
    if (t == 1) {
      p.push_back(std::make_tuple(-1, -i, op, l, r, c));
    } else {
      p.push_back(std::make_tuple(0, i, op, l, r, c));
    }
  }

  std::sort(p.begin(), p.end());

  LazySegTree S(m), T(n);
  S.set(Lazy(1));
  T.set(Lazy(1));

  for (auto [type, time, op, l, r, c] : p) {
    if (op == 1) {
      answer[c] += S.get().sum * T.get(l, r).sum;
      T.set(l, r, Lazy(0));
    } else {
      answer[c] += S.get(l, r).sum * T.get().sum;
      S.set(l, r, Lazy(0));
    }
  }

  for (auto i : answer) io << i << ' ';

  return 0;
}

```


---

## 作者：c1ampy (赞：6)

$ t $ 不同的两种操作不容易同时维护，但我们不难想到：

- 如果操作 $ \texttt{B} $ 会覆盖操作 $ \texttt{A} $，这就相当于先执行操作 $ \texttt{A} $，再执行操作 $ \texttt{B} $，且操作 $ \texttt{A} $ 不覆盖操作 $ \texttt{B} $。

于是，我们可以将 $ t = 1 $ 的操作转化为 $ t = 0 $ 的操作，具体方法如下：

- 先按**倒序**，将 $ t = 1 $ 的操作直接当作 $ t = 0 $ 的操作处理，再按**正序**处理余下的 $ t = 0 $ 的操作。

对每次操作，我们只需求出在将要被覆盖的范围内**仍未被覆盖**的行数和列数即可。

每一行（列）是否被覆盖只需一个变量维护。$ n $ 行 $ n $ 个（$ m $ 列 $ m $ 个）变量，我们需要实现**区间覆盖**与**区间求和**操作，不难想到用**线段树**维护。

可是出题人的本意就是要卡掉线段树做法，于是我们考虑优（卡）化（常）。

- 对一个已被全部覆盖的区间执行区间覆盖操作是无用的。而我们发现，在题目中执行区间覆盖操作前，我们总会对同样的区间执行一次区间求和操作。因此，我们可以根据区间求和操作的查询结果判断是否需要执行区间覆盖操作。

- 在线段树上执行区间覆盖操作时，如果当前结点的区间已被全部覆盖，直接返回。

```cpp
if (node[cur].len == node[cur].sum)
    return;
```

- 在线段树上执行区间求和操作时，如果当前结点的区间全都没有被覆盖或已被全部覆盖，直接计算答案并返回。

```cpp
if (!node[cur].sum)
    return 0;
if (node[cur].sum == node[cur].len)
    return std::min(r, node[cur].r) - std::max(l, node[cur].l) + 1;
```

具体代码如下：

```cpp
#include <iostream>

const int max_n = 2e6 + 10;
const int max_k = 5e5 + 10;
const int max_q = 2e6 + 10;

class SegmentTree
{
private:

    struct Node
    {
        int l, r;
        int len;
        int sum;

        void get_tag()
        {
            sum = r - l + 1;
        }
    };

    void push_up(const int cur)
    {
        node[cur].sum = node[cur << 1].sum + node[cur << 1 | 1].sum;
    }

    void push_down(const int cur)
    {
        if (node[cur].sum != node[cur].len)
            return;
        node[cur << 1].get_tag();
        node[cur << 1 | 1].get_tag();
    }

    Node node[max_n << 2];

public:

    void build(const int l, const int r, const int cur = 1)
    {
        node[cur].l = l, node[cur].r = r, node[cur].len = r - l + 1;
        if (l == r)
            return;
        
        int mid = l + r >> 1;
        build(l, mid, cur << 1);
        build(mid + 1, r, cur << 1 | 1);
    }

    void update(const int l, const int r, const int cur = 1)
    {
        if (node[cur].len == node[cur].sum)
            return;
        if (l <= node[cur].l && node[cur].r <= r)
        {
            node[cur].get_tag();
            return;
        }
        
        push_down(cur);
        int mid = node[cur].l + node[cur].r >> 1;
        if (l <= mid)
            update(l, r, cur << 1);
        if (r > mid)
            update(l, r, cur << 1 | 1);
        push_up(cur);
    }

    int query(const int l, const int r, const int cur = 1)
    {
        if (!node[cur].sum)
            return 0;
        if (node[cur].sum == node[cur].len)
            return std::min(r, node[cur].r) - std::max(l, node[cur].l) + 1;
        if (l <= node[cur].l && node[cur].r <= r)
            return node[cur].sum;

        push_down(cur);
        int mid = node[cur].l + node[cur].r >> 1;
        int res = 0;
        if (l <= mid)
            res += query(l, r, cur << 1);
        if (r > mid)
            res += query(l, r, cur << 1 | 1);
        return res;
    }
};

namespace quick_io
{
    template <typename T> void read(T &num)
    {
        char ch = getchar();
        while (ch < '0' || '9' < ch)
            ch = getchar();
        num = 0;
        while ('0' <= ch && ch <= '9')
            num = (num << 3) + (num << 1) + (ch ^ 48), ch = getchar();
    }

    template <typename T> void write(const T &num)
    {
        if (num > 9)
            write(num / 10);
        putchar(num % 10 + 48);
    }
}

SegmentTree T_1, T_2;
long long ans[max_k];
int op[max_q], l[max_q], r[max_q], c[max_q], t[max_q];

int main()
{
    using namespace quick_io;

    int n, m, k, q;
    read(n), read(m), read(k), read(q);
    for (int i = 1; i <= q; ++i)
        read(op[i]), read(l[i]), read(r[i]), read(c[i]), read(t[i]);

    T_1.build(1, n), T_2.build(1, m);
    for (int i = q; i; --i)
    {
        if (!t[i])
            continue;
        if (op[i] == 1)
        {
            int q_1 = T_1.query(l[i], r[i]), q_2 = T_2.query(1, m);
            ans[c[i]] += (long long)(r[i] - l[i] + 1 - q_1) * (m - q_2);
            if (q_1 != r[i] - l[i] + 1)
                T_1.update(l[i], r[i]);
        }
        else
        {
            int q_1 = T_1.query(1, n), q_2 = T_2.query(l[i], r[i]);
            ans[c[i]] += (long long)(n - q_1) * (r[i] - l[i] + 1 - q_2);
            if (q_2 != r[i] - l[i] + 1)
                T_2.update(l[i], r[i]);
        }
    }

    for (int i = 1; i <= q; ++i)
    {
        if (t[i])
            continue;
        if (op[i] == 1)
        {
            int q_1 = T_1.query(l[i], r[i]), q_2 = T_2.query(1, m);
            ans[c[i]] += (long long)(r[i] - l[i] + 1 - q_1) * (m - q_2);
            if (q_1 != r[i] - l[i] + 1)
                T_1.update(l[i], r[i]);
        }
        else
        {
            int q_1 = T_1.query(1, n), q_2 = T_2.query(l[i], r[i]);
            ans[c[i]] += (long long)(n - q_1) * (r[i] - l[i] + 1 - q_2);
            if (q_2 != r[i] - l[i] + 1)
                T_2.update(l[i], r[i]);
        }
    }

    for (int i = 1; i <= k; ++i)
        write(ans[i]), putchar(' ');

    return 0;
}
```

程序的时间复杂度为 $ \mathcal{O} \left(q \log \max\{n, m\}\right) $，虽然没有达到出题人要求，但足以通过赛时数据。

本人接受诸位大佬对此份时间复杂度不正确的程序的批评指正，并欢迎诸位大佬给出 Hack 数据。


---

## 作者：Rei_Sen (赞：6)

在这里感谢 Larry76 将宝贵的写题解机会让给了铃仙，贴贴/tyt。

不妨考虑一下 $t = 0$ 的本质是什么，容易发现实际上就相当于当前所有的染色操作都在这个操作的上面。

明白了这一点就很好做了，我们先还原出「原本的」染色的顺序，因为一旦我们获得了原本正常的染色顺序后，题目就比较套路了。

不难想到反着做，因为这样使得后操作的不会影响先操作的，由于每次都是**染一段连着的行、列**，故不难得出「当行、列被染色后，就不会再对颜色产生贡献了」这一结论。

这样就好玩了，由于这一性质的存在，我们在顺着处理的时候跳过已经被执行染色操作的行、列，然后对于行的染色等价于列的全局减，对于列的染色等价于对于行的全局减，简单的，维护两个 $tag$ 就好了。

现在的问题是怎么跳过已经被执行过染色操作的行、列，这是一个经典的 trick，维护一个并查集即可，考虑让并查集初始时维护自己，当我们操作的时候，就让他与其右边的点 `merge`（右边的点当父亲），然后原先的指针右移一格变成先右移一格，然后 `find` 一下跳到 `fa`（也就是没有处理的部分）即可。

到这里我们就做完了，时间复杂度 $O(q(\log n + \log m + \log q))$。

```cpp
struct node {
	int op, l, r, c, t;
	int i;
	bool operator < (const node &a) const {
		if (t != a.t) return t == 1;
		else if(t == 1) return i > a.i;
		else return i < a.i;
	}
} p[MAX_SIZE];

int ans[MAX_SIZE], fa[2][MAX_SIZE];

int find(int x, bool tp) {
	if(fa[tp][x] == x)
		return x;
	return fa[tp][x] = find(fa[tp][x], tp);
}

void merge(int u, int v, int tp) {
	u = find(u,tp);
	v = find(v,tp);
	fa[tp][u] = v;
}

signed main() {
	int n = read(), m = read(), k = read(), l = read();
	for (int i = 1; i <= l; ++i) {
		p[i].op = read();
		p[i].l = read();
		p[i].r = read();
		p[i].c = read();
		p[i].t = read();
		p[i].i = i;
	}
	for(int i = 1; i <= max(n, m)+5; ++i) {
		fa[1][i] = fa[0][i] = i;
	}
	sort(p + 1, p + 1 + l);
	for (int i = 1; i <= l; ++i) {
		if (p[i].op == 1) {
			int ptr = find(p[i].l, 0);
			while(ptr <= p[i].r) {
				ans[p[i].c] += m;
				--n;
				int nxt = find(ptr, 0);
				if(nxt <= p[i].r) {
					merge(ptr, nxt + 1, 0);
				}
				ptr = find(nxt, 0);
			}
		} else {
			int ptr = find(p[i].l, 1);
			while(ptr <= p[i].r) {
				ans[p[i].c] += n;
				--m;
				int nxt = find(ptr, 1);
				if(nxt <= p[i].r) {
					merge(ptr, nxt + 1, 1);
				}
				ptr = find(nxt, 1);
			}
		}
	}
	for (int i = 1; i <= k; ++i) write(ans[i], ' ');
	return 0;
}
```

如果你想走，那先别急，我在这里在推荐一个用到这种「并查集维护颜色段」trick 的题目：[CF1847D Professor Higashikata](https://www.luogu.com.cn/problem/CF1847D)，铃仙祝大家玩的愉快。

---

## 作者：AKPC (赞：3)

场切，补个题解。

你会发现这个题目很像 P2391 和 $2023$ 春测签到题。

先把这个题目简化：

有一个数列 $a$，长度 $n$，初始时 $a$ 所有元素均为 $0$。  
现在要给 $a$ 数列进行 $q$ 次修改操作，每次操作将某一区间所有值均修改为特定的同一值。  
最后求 $a$ 数列每个元素的值。  
数据范围：$1\leq n,m\leq 10^5$，对于最后的答案 $1\leq a_{\forall i}\leq 10^9$。

样例输入：

```
5 3
1 3 1
2 4 2
3 3 3
```

样例输出：

```
1 2 3 2 0
```

**1. 存储区间。**

考虑按照修改区间的左顶点在 `vector` 里存储区间，便于后面线性的遍历。

存储区间代码大致长这样：

```cpp
#define mpr make_pair

inline int read(){//自己手敲的屑快读qwq
	int res=0,f=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {res=res*10+(c-'0');c=getchar();}
	return res*f;
}

vector<pair<int,pair<int,int> > >a[100005];//r,{color,t}

for (int i=1;i<=q;i++){
	int x=read(),y=read(),z=read();
	a[x].push_back(mpr(y,mpr(z,i)));//这里的i在后面会讲
}
```

**2. 优先队列维护区间集的排序方式。**

存储区间的时候记录一个优先级。

越后面的操作优先级越大（在上面的代码里取了 $i$）。在后面使用优先队列的处理中，需要根据优先级从小到大排序。

代码见上部分。

**3. 线性遍历所有区间。**

遍历一遍 $1\sim n$，维护优先队列（优先级从小到大），维护这几个操作：

- 弹出队列顶部右端点小于 $i$ 的操作区间（弹出顶部过时操作）。
- 放入所有左端点 $i$ 的区间。
- 选取队列顶部的操作区间对应的值赋值给答案数组对应的下标。

遍历区间的代码大致长这样：

```cpp
#define fr first
#define sc second

int a[100005];

priority_queue<pair<pair<int,int>,pair<int,int> >,vector<pair<pair<int,int>,pair<int,int> > >,less<pair<pair<int,int>,pair<int,int> > > >que;//{t,color},{l,r}

for (int i=1;i<=n;i++){
	while (!que.empty()){//弹出过时区间
		if (que.top().sc.sc<i) que.pop();
		else break;
	}
	for (auto j:a[i]) que.push(mpr(mpr(j.sc.sc,j.sc.fr),mpr(i,j.fr)));//放入新的区间
	if (!que.empty()){//统计该位置答案
		const int x=que.top().sc.fr,y=que.top().fr.sc;
		ans[i]=y;	
	}
}
```

**4. 输出答案。**

直接输出 `ans` 数组即可。

代码如下：

```cpp
for (int i=1;i<=n;i++) cout<<ans[i]<<' ';
```


这种做法的正确性就是在每次遍历，弹出过时区间和放入区间之后，队列顶部的一定没有过时，且优先级一定最大。而且在弹出过时区间的时候，可以不考虑队列不在顶部的区间，因为在该区间到顶部的时候会自动弹出，一直没到顶部就更不用管了。

其实你用并查集可以优化，但我偏不。

[code](https://www.luogu.com.cn/paste/fpx61x94)

而这个跟题目的关系就在于你已经解决了一维情况下 $t=1$ 的操作了，现在你发现 $t=0$ 的优先级便是 $-i$。然后变成二维处理每行，每列的各个操作并处理答案，对于每个格子取个优先值最大的作为最终答案即可。

当然这肯定是不行的。所以呢自然可以想到春测 $2023$ 的经典签到题目，将行、列的所有未被覆盖的操作按照优先级从大到小排序，线性遍历，如果在遍历到某一行的时候，在之前覆盖了 $x$ 列，则因为优先级大的会覆盖优先级小的操作，这次操作只会覆盖该行的 $n-x$ 格。遍历到列的时候处理是类似的。

讲的很详细了代码就不给了，当然你也可以根据这个思路写并查集的优化做法。并查集做法可以参考 P2391 的题解。

---

## 作者：Forg1weN (赞：0)

## 题面
初始时你有一个 $n$ 行 $m$ 列的网格，所有格子上都没有颜色。有 $k$ 种颜色的刷子，颜色编号为 $1\sim k$。然后给出 $q$ 次操作，每次操作给出 $op,l,r,c,t$ 五个参数：

- 如果 $op=1$，表示将第 $l\sim r$ 行的所有格子涂成颜色 $c$。
- 如果 $op=2$，表示将第 $l\sim r$ 列的所有格子涂成颜色 $c$。
- 如果 $t=0$，意味着如果涂色时遇到已经被染色的格子，就不再进行染色。
- 如果 $t=1$，意味着如果涂色时遇到已经被染色的格子，就用新的颜色覆盖它。

在所有涂色操作结束以后，对于每种颜色，求出有多少个格子被染成了这种颜色。

保证 $1\le n,m,q\le 2\times 10^6$，$1\le k\le 5\times 10^5$，$op\in\{1,2\}$，若 $op=1$ 则 $1\le l\le r\le n$，若 $op=2$ 则 $1\le l\le r\le m$，$1\le c\le k$，$t\in\{0,1\}$。

## Solution
不断的覆盖操作很难维护，考虑倒序加入。

若操作 $i$ 的 $t=0$，也就是说对于 $t=1$ 的操作，无论如何都是会被覆盖的。

所以按照 $t$ 从小到大排序，然后 $t=1$ 时按照编号从大到小排序（后面会覆盖前面），$t=0$ 按照编号从小到大排序（后面不会覆盖前面）。

**这样子的染色能保证后面的染色一定不会覆盖前面的染色。**

然后如果染色一列，记已经染色的行 $ht$，则贡献为 $n-ht$。列同理。

维护区间 $[l,r]$ 是否被染色，可以使用并查集维护，具体指一个位置指向从自己往后数最近的还未染色的位置。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2e6+10;
int n,m,k,q,ht,lt;
LL c[maxn];

struct Father {
	int fa[maxn];
	int getfa(int x) {
		if(x==fa[x])return x;
		return fa[x]=getfa(fa[x]);
	}
}h,l;
struct Sub {
	int op,l,r,c,t,id;
}a[maxn];
bool cmp(Sub a,Sub b) {
	if(a.t!=b.t)
		return a.t>b.t;
	if(a.t==1)
		return a.id>b.id;
	return a.id<b.id;
}
int main() {
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1;i<=q;i++)
		scanf("%d%d%d%d%d",&a[i].op,&a[i].l,&a[i].r,&a[i].c,&a[i].t),a[i].id=i;
	sort(a+1,a+1+q,cmp); 
	for(int i=1;i<=n+1;i++)h.fa[i]=i;
	for(int i=1;i<=m+1;i++)l.fa[i]=i;
	for(int i=1;i<=q;i++) {
		if(a[i].op==1) {
			for(int j=h.getfa(a[i].l);j<=a[i].r;j=h.getfa(j)) {
				ht++;h.fa[j]=j+1; 
				c[a[i].c]+=m-lt;
			}
		}
		else {
			for(int j=l.getfa(a[i].l);j<=a[i].r;j=l.getfa(j)) {
				lt++;l.fa[j]=j+1; 
				c[a[i].c]+=n-ht;
			}
		}
	}
	for(int i=1;i<=k;i++)
		printf("%lld ",c[i]);
	return 0;
}
```



---

