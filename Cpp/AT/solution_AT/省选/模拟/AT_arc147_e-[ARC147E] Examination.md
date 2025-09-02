# [ARC147E] Examination

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc147/tasks/arc147_e

$ 1,2,\ldots,N $ の番号のついた $ N $ 人の生徒が試験を受けました。人 $ i\,(1\ \leq\ i\ \leq\ N) $ の点数は $ A_i $ でしたが、$ B_i $ 点以上取らないと留年です。そこで誰も留年しないように、ある $ 2 $ 人の点数を入れ替える、という操作を任意の回数行うことにしました。

これが可能かを判定し、もし可能ならば一度も点数を入れ替えなかった人数の最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ 10^9\,(1\ \leq\ i\ \leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

人 $ 1 $ と人 $ 2 $ の点数を入れ替えると、誰も留年しません。このとき、一度も点数を入れ替えなかった人は人 $ 3 $ だけなので、$ 1 $ を出力します。

## 样例 #1

### 输入

```
3
1 2
3 1
3 3```

### 输出

```
1```

## 样例 #2

### 输入

```
2
100 1
100 1```

### 输出

```
2```

## 样例 #3

### 输入

```
6
3 2
1 6
4 5
1 3
5 5
9 8```

### 输出

```
-1```

## 样例 #4

### 输入

```
6
3 1
4 5
5 2
2 3
5 4
5 1```

### 输出

```
3```

# 题解

## 作者：tzc_wk (赞：11)

首先，根据霍尔定理，考虑对在 $b_i$ 位置上 $+1$，$a_i$ 位置上 $-1$，那么答案不是 $-1$ 的充要条件是所有前缀和都 $\ge 0$。

接下来考虑怎样最小化交换次数，我们记 $S$ 为所有 $a$ 交换了的人的集合，显然 $S$ 合法的充要条件是 $S$ 包含了所有原本 $a_i<b_i$ 的人，且只对 $S$ 中元素进行 $b$ 位置上的值 $+1$、$a$ 位置上的值 $-1$，依然满足所有前缀和都 $\ge 0$。

我们考虑从 $S$ 中只包含 $a_i<b_i$ 的人开始进行调整，我们扫描一遍前缀和数组，假设我们扫到一个 $sum_i<0$ 的位置，那么显然我们需要加入一个 $b_j\le i<a_j$ 的人才能使其满足条件，而对于这样的人，它们的 $b$ 我们其实不关心的，而为了让其尽可能少的影响到后面的位置，我们肯定会选择这样的人中 $a$ 最大的，使用一个堆维护即可。

时间复杂度 $n\log n$。

---

## 作者：Phartial (赞：8)

小清新贪心题。

无解很好判断，排序后看有没有数满足 $a_i<b_i$，如果有就是无解。可以感性理解，当然证明也不难。

考虑把原序列所有的 $a_i<b_i$ 的数提出来，这些数是必须要交换位置的。所以可以先把 $a$ 和 $b$ 各自排个序，从小到大依此取数。如果这一对 $a_i$ 和 $b_i$ 已经满足 $a_i\ge b_i$ 了就直接跳，否则我们就要从合法的数对里引进一对数来使这一对 $a_i$ 和 $b_i$ 满足条件。可以发现我们引进的数对必须要满足 $b_j\le a_i$ 的同时 $a_j$ 最大，然后交换 $a_i$ 和 $a_j$ 即可。

实现时可以使用两个小根堆维护 $a_i$ 和 $b_i$，以及一个大根堆维护满足 $b_j\le a_i$ 的 $a_j$。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using Pii = pair<int, int>;
using Qs = priority_queue<int, vector<int>, greater<int>>;
using Ql = priority_queue<int>;

const int kN = 3e5 + 1;

int n, a[kN], b[kN], _a[kN], _b[kN], ans;
Qs qa, qb;
Ql qu;
vector<Pii> e;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i] >> b[i];
    _a[i] = a[i], _b[i] = b[i];
  }
  sort(_a + 1, _a + n + 1);
  sort(_b + 1, _b + n + 1);
  for (int i = 1; i <= n; ++i) {
    if (_a[i] < _b[i]) {
      cout << "-1";
      return 0;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (a[i] < b[i]) {  // 提出所有不合法的数对
      qa.push(a[i]), qb.push(b[i]);
    } else {  // 合法的提到候选队列
      e.emplace_back(a[i], b[i]);
    }
  }
  sort(e.begin(), e.end(), [](Pii i, Pii j) { return i.second < j.second; });
  for (int i = 0; !qa.empty();) {
    ++ans;
    int x = qa.top(), y = qb.top();
    if (x >= y) {          // 如果已经合法了
      qa.pop(), qb.pop();  // 直接跳过即可
      continue;
    }
    for (; i < e.size() && e[i].second <= x; ++i) {  // 找出所有满足 a[j]<=a[i] 的数对丢进可选队列里
      qu.push(e[i].first);
    }
    qa.pop(), qa.push(qu.top()), qu.pop();  // 选一个最大的可选 a 替代当前的 a
  }
  cout << n - ans;
  return 0;
}
```

---

## 作者：NinT_W (赞：6)

## Examination

本题解借鉴了[这位dalao](https://atcoder.jp/users/macesuted)的思路。

看上去这题没人交题解，~~那我就来一发吧~~(弥天大雾

[传送门](https://www.luogu.com.cn/problem/AT_arc147_e)

### 题意

题目已经很简洁力。

### 分析一下

一开始就不满足要求的话是肯定要交换的，我们用大根堆 $A, B$ 分别存储一开始就不满足要求的 $a_i,b_i$。

而一开始就满足要求的 $a_i,b_i$，我们用一个大根堆 $q$（这里要按照 $a_i$ 来排）存起来，然后进行交换。

### 考虑如何交换

对于一开始就不满足的人，其内部可以自己解决的话，一定会自己解决（贪心的想），即对于当前的 $top_B$ 如果 $A$ 内最大的 $a_i$（即 $top_A$ ）大于它，我们就可以直接把这两个人交换，即把当前这个人的 $a_i,b_i$ 变成 $top_A,top_B$ 即可。

如果无法内部解决，说明我们需要原本合法的人的帮助，我们肯定是要用 $a_i$ 更大的人才能帮助他的，所以我们之前使用大根堆存合法的人。贪心的想，我们在保证 $a_i$ 大于 $top_B$ 的同时，也要使 $b_i$ 尽量小，因此我们可以使用小根堆 $notB$ 将所有满足 $a_i$ 大于 $top_B$ 的人的 $b_i$ 存下来，选一个  $b_i$ 最小的进行交换即可（如果此时 $notB$ 为空，说明没人能帮 $top_B$，即无解）。

 AC code
 
 ```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<cstdlib>
#include<algorithm>
#define pii pair<int,int>

using namespace std;

const int maxn=3e5+5;

inline int read()
{
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}

int n,x,y,ans;
priority_queue<pii,vector<pii>,less<pii> > q;
priority_queue<int,vector<int>,less<int> > A,B; 
priority_queue<int,vector<int>,greater<int> > not_B;

int main()
{
	n=read();

	for(int i=1;i<=n;i++)
	{
		x=read(),y=read();
		if(x<y) A.push(x),B.push(y);
		else q.push(make_pair(x,y)),ans++;
	}
	
	while(!B.empty())
	{
		int k=B.top();B.pop();
		
		if(!A.empty() && A.top()>=k)
		{
			A.pop();continue;
		}
		
		while(!q.empty() && q.top().first>=k)
		{
			not_B.push(q.top().second);q.pop();
		}
		
		if(not_B.empty()) cout<<-1,exit(0);
		
		ans--,B.push(not_B.top()),not_B.pop();
	}
	
	cout<<ans;
	
	return 0;
}
```


---

## 作者：EXR_FAL (赞：2)

### 题目链接 [Link](https://www.luogu.com.cn/problem/AT_arc147_e)

### 前言

刷题刷到这道题，一看还能交题解，赶快来水一篇（（\
本蒟蒻提供一种~~又臭又长的~~线段树做法

### 分析

无解很好判断，排序后看有没有数满足 $A_i < B_i$，如果有就是无解。

对于有解的情况，$A_i<b_i$ 的位置必须选中，假设最终选中的集合为 $S$，那么相当于有一张二分图，左右各 $|S|$ 个点代表 $A,B$，$A_i$ 和 $B_i$ 有连边当且仅当 $A_i \geq B_i$。

我们要求这张图有完美匹配，那么根据霍尔定理，只需要检查对所有集合 $T \subseteq S$，是否有 $| N ( T ) | \geq | T |$。

我们发现一旦选定了左部点集 $T$，设 $T$ 中值最大的是 $A$，那么 $N(T)$ 只和 $A_i$ 有关，就是所有 $B_j \leq A_i$ 的 $j$ 的集合。而为了让 $| N ( T ) | - | T |$ 尽可能小，我们一定会把 $A_k \leq A_i$ 的 $k$ 全选上，而这不会使 $| N ( T ) |$ 增大，但是会让 $| T |$ 增大。

于是，我们就只需要考虑 $A$ 从大到小排序后的一段前缀作为 $T$，那么霍尔定理可以重新表述为：对每个值 $v_i \leq v$ 的 $A$ 的个数表超过 $B$ 的个数。

由于 $A_i,B_i \leq 10^9$，需要离散化：先把所有 $A_i < B_i$ 的 $i$ 都加入集合 $S$，对每个值 $j$，维护 $w_j$ 表示 $\leq j$ 的 $B_i$ 的个数减去 $\leq j$ 的 $A_i$ 个数，那么，当且仅当所有 $w_i > 0$ 时才合法。

往 $S$ 中加入一个 $A_k \geq B_k$ 的 $k$，造成的影响是对 $w$ 的 $[ A_k , + \infty)$ 区间 $-1$，把 $[ B_k , + \infty)$ 区间 $+1$。

那么问题变成，至少选择多少个区间 $+1$，能够使每个位置都 $>0$。我们每次找到最靠左的一个 $<0$ 的点 $p$，选出一个 $l \leq p$ 且 $r$ 最大的区间加入即可。

用线段树维护区间修改，时间复杂度 $O(n \log n)$。

代码如下：

```cpp
//Ciallo～(∠・ω< )⌒★

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
inline ll read(){
    ll x=0,flag=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') flag=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*flag;
}
void out(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else out(x/10),putchar(x%10+'0');
}

// 简化STL
#define be begin
#define en end
typedef pair<int,int> PII;

const int N=3e5+114;
const int M=N<<2; // 线段树空间

int n,m,a[N],b[N];
map<int,int> mp;
priority_queue<PII,vector<PII>,greater<PII>> q;
priority_queue<PII> ok;

vector<int> v; // 离散化

// // Segment Tree
#define ls(p) (p<<1)
#define rs(p) (p<<1|1)
struct Tree{
	int l,r;
	int va,mn,tag;
}tree[N<<3];
void push_up(int p){
	tree[p].va=tree[ls(p)].va+tree[rs(p)].va;
	tree[p].mn=min(tree[ls(p)].mn,tree[rs(p)].mn);
}
void push_down(int p){
	if(!tree[p].tag) return;
	tree[ls(p)].tag+=tree[p].tag;
	tree[rs(p)].tag+=tree[p].tag;
	tree[ls(p)].va+=tree[p].tag*(tree[ls(p)].r-tree[ls(p)].l+1);
	tree[rs(p)].va+=tree[p].tag*(tree[rs(p)].r-tree[rs(p)].l+1);
	tree[ls(p)].mn+=tree[p].tag;
	tree[rs(p)].mn+=tree[p].tag;
	tree[p].tag=0;
}
void build(int p,int pl,int pr){
	tree[p].l=pl;
	tree[p].r=pr;
	tree[p].va=tree[p].mn=tree[p].tag=0;
	if(pl==pr) return;
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
}
void update(int p,int pl,int pr,int v){
	if(tree[p].l>=pl&&tree[p].r<=pr){
		tree[p].tag+=v;
		tree[p].va+=v*(tree[p].r-tree[p].l+1);
		tree[p].mn+=v;
		return;	
	}
	push_down(p);
	int mid=(tree[p].l+tree[p].r)>>1;
	if(pl<=mid) update(ls(p),pl,pr,v);
	if(pr>mid) update(rs(p),pl,pr,v);
	push_up(p);
}
int query(int p){
	if(tree[p].l==tree[p].r) return tree[p].l;
	push_down(p);
	if(tree[ls(p)].mn<0) return query(ls(p));
	if(tree[rs(p)].mn<0) return query(rs(p));
	return -1;
}

int main(){

    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read(),b[i]=read();
        v.push_back(a[i]);
        v.push_back(b[i]);
    }

    sort(v.be(),v.en());
    v.resize(unique(v.be(),v.en())-v.be());
    m=v.size(),build(1,1,m);

    for(int i=1;i<=n;i++){
        a[i]=lower_bound(v.be(),v.en(),a[i])-v.be()+1;
        b[i]=lower_bound(v.be(),v.en(),b[i])-v.be()+1;
    }

    int res=n;
    for(int i=1;i<=n;i++){
        if(a[i]<b[i]){
            res--;
            update(1,a[i],m,-1);
            update(1,b[i],m,1);
        }else q.push({b[i],a[i]});
    }
    
    int t=query(1);
    while(t!=-1){
        while(q.size()&&q.top().first<=t){
            ok.push({q.top().second,q.top().first});
            q.pop();
        }
        int Ciallo=t;
        while(ok.size()&&Ciallo==t){
            res--;
            update(1,ok.top().first,m,-1);
            update(1,ok.top().second,m,1);
            ok.pop(),t=query(1);
        }
        if(Ciallo==t) return puts("-1"),0;
    }

    out(res),puts("");

    return 0;
}

```

---

## 作者：DaiRuiChen007 (赞：2)

# ARC147E 题解

## 思路分析

我们可以考虑最小化一个集合 $\mathbf S$ 表示所有需要更换的试卷的的学生构成的集合

则所有的 $b_i>a_i$ 的 $i$ 均在 $\mathbf S$ 中

考虑记 $cnt_x$ 由以下定义给出：
$$
cnt_x=\sum_{i\in\mathbf S} [b_i\le x]-\sum_{i\in\mathbf S} [a_i\le x]
$$
显然，我们最终要让所有的 $cnt_x\ge 0$

考虑对于最小的 $p$ 有 $cnt_p<0$，考虑选择若干个 $b_i<a_i$ 的 $i$ 进入 $\mathbf S$，使得 $cnt_p\ge 0$

显然我们选择的某些 $q$ 应该有 $b_q\le p<a_q$，那么此时我们显然应该优先选 $a_q$ 更大的，那么只需要用优先队列简单维护就可以了

时间复杂度 $\Theta(n\log n)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int MAXN=1e5+1;
map <int,int> mark;
priority_queue <pii,vector<pii>,greater<pii> > pr1;
priority_queue <int,vector<int>,less<int> > pr2;
signed main() {
	int n;
	scanf("%d",&n);
	int res=n,cnt=0;
	for(int i=1;i<=n;++i) {
		int A,B;
		scanf("%d%d",&A,&B);
		if(A<B) --res,--mark[A],++mark[B];
		else pr1.push(make_pair(B,A));
	}
	for(auto &x:mark) {
		cnt+=x.second;
		while(!pr1.empty()&&pr1.top().first<=x.first) {
			pr2.push(pr1.top().second);
			pr1.pop();
		}
		while(cnt<0) {
			if(pr2.empty()) return 0&puts("-1");
			auto fr=pr2.top();
			pr2.pop();
			if(fr<=x.first) continue;
			++cnt,--res;
			--mark[fr];
		}
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：MortisM (赞：2)

> [ARC147E Examination](https://atcoder.jp/contests/arc147/tasks/arc147_e)

这题不是很难吧，但是就是转化没想到，所以还是挺难的，不然怎么放 E 呢，不A过想到那步转化就怎么搞都行了。虽然但是，题解的做法还是比我要简洁很多，而且好像也不难想，特别好写，不知道为啥我写了个线段树的做法而且还调了好久，好在最后调出来了。这篇文章将讲述笔者和官方题解两个方法，鉴于笔者太菜了，所以先讲官方题解的方法罢。

***

**官方题解方法：**

这道题很自然地想判断答案是否为 `-1`，这个是简单的，只要把 $a,b$ 分别排序然后看是否 $\forall 1\leq i\leq n,a_i\geq b_i$ 即可，但是这样的判别方法很难继承到后续的做法中（我一开始就是想的这个），所以需要一些转化。

转化就是设 $A_x$ 表示 $a_i\leq x$ 的 $i$ 的个数，$B_x$ 表示 $b_i\leq x$ 的 $i$ 的个数，$C_x=B_i-A_i$。则若 $C_x<0$，就不合法，考虑这个做法如何继承到求答案的做法中。首先，如果 $a_i<b_i$ 这个一定是要动的，那么我们就需要让最少的其他的动，使得不存在 $C_x<0$。

设当前状态下最小的 $t$ 使得 $C_t<0$，那么再选的 $i$ 一定满足 $B_i\leq t$ 且 $A_i>t$，就是必须得能更新到这个，否则没有啥用。而同时，$B_i$ 只要 $\leq t$ 就行，不关心具体的值，因为反正 $t$ 随着加入越来越多只增不减。

这样就可以维护一个小根堆，第一关键字为 $B_i$，第二关键字为 $A_i$，再维护一个大根堆，表示有哪些是待选的，待选的里就只用看 $A_i$ 的从大到小了，每次用第一个更新第二个堆即可，具体还是看代码罢。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define mod 998244353
#define MOD 1000000007
#define F first
#define S second
#define ll long long
#define N 300005
using namespace std;
int n,a[N],b[N];
map<int,int> mp;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
priority_queue<int> ok;
int main(){
	cin>>n;
	int ans=n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		if(a[i]<b[i]){
			ans--;
			mp[a[i]]--;
			mp[b[i]]++;
		}
		else{
			pq.push(make_pair(b[i],a[i]));
		}
	}
	int cnt=0;
	for(auto it:mp){
		while(!pq.empty()&&pq.top().F<=it.F){
			ok.push(pq.top().S);
			pq.pop();
		}
		cnt+=it.S;
		while(cnt<0){
			if(ok.empty()||ok.top()<=it.F){
				cout<<-1<<endl;
				return 0;
			}
			cnt++;
			ans--;
			mp[ok.top()]--;
			ok.pop();
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

别急走啊，还有我的实现方法呢~

**My Solution:**

我的实现就是先将 $A_i,B_i$ 离散化，每次在线段树上更新区间 $+1/-1$，维护区间和、区间最小值即可，找的时候在线段树上二分出第一个 $<0$ 的位置，其他实现相同，但貌似难写一些？

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5+10;
int n,a[maxn],b[maxn];
vector<int> v;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
priority_queue<pair<int,int>> ok;
struct node{
	int l,r;
	int val,mn,tag;
}tree[maxn<<3];
void pushup(int x){
	tree[x].val=tree[x<<1].val+tree[x<<1|1].val;
	tree[x].mn=min(tree[x<<1].mn,tree[x<<1|1].mn);
}
void pushdown(int x){
	if(!tree[x].tag){
		return;
	}
	tree[x<<1].tag+=tree[x].tag;
	tree[x<<1|1].tag+=tree[x].tag;
	tree[x<<1].val+=tree[x].tag*(tree[x<<1].r-tree[x<<1].l+1);
	tree[x<<1|1].val+=tree[x].tag*(tree[x<<1|1].r-tree[x<<1|1].l+1);
	tree[x<<1].mn+=tree[x].tag;
	tree[x<<1|1].mn+=tree[x].tag;
	tree[x].tag=0;
}
void build(int x,int l,int r){
	tree[x].l=l;
	tree[x].r=r;
	tree[x].val=tree[x].mn=tree[x].tag=0;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int l,int r,int v){
	if(tree[x].l>=l&&tree[x].r<=r){
		tree[x].tag+=v;
		tree[x].val+=v*(tree[x].r-tree[x].l+1);
		tree[x].mn+=v;
		return;	
	}
	pushdown(x);
	int mid=(tree[x].l+tree[x].r)>>1;
	if(l<=mid){
		update(x<<1,l,r,v);
	}
	if(r>mid){
		update(x<<1|1,l,r,v);
	}
	pushup(x);
}
int find(int x){
	if(tree[x].l==tree[x].r){
		return tree[x].l;
	}
	pushdown(x);
	if(tree[x<<1].mn<0){
		return find(x<<1);
	}
	if(tree[x<<1|1].mn<0){
		return find(x<<1|1);
	}
	return -1;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		v.push_back(a[i]);
		v.push_back(b[i]);
	}
	sort(v.begin(),v.end());
	v.resize(unique(v.begin(),v.end())-v.begin());
	int m=(int)v.size();
	build(1,1,m);
	int ans=n;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
		b[i]=lower_bound(v.begin(),v.end(),b[i])-v.begin()+1;
		if(a[i]<b[i]){
			ans--;
			update(1,a[i],m,-1);
			update(1,b[i],m,1);
		}
		else{
			pq.push(make_pair(b[i],a[i]));
		}
	}
	int t=find(1);
	while(t!=-1){
		while(!pq.empty()&&pq.top().first<=t){
			ok.push(make_pair(pq.top().second,pq.top().first));
			pq.pop();
		}
		int tmp=t;
		while(!ok.empty()&&t==tmp){
			ans--;
			update(1,ok.top().first,m,-1);
			update(1,ok.top().second,m,1);
			ok.pop();
			t=find(1);
		}
		if(t==tmp){
			cout<<-1<<endl;
			return 0;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

**完结撒花 owo~**

---

## 作者：LiuIR (赞：1)

# ARC147E Examination 题解

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/AT_arc147_e)

有 $n$ 个学生，第 $i$ 个人现在有 $a_i$ 分，并想要拥有 $b_i$ 分。

你可以选择任意的 $i,j$，并交换 $a_i,a_j$。并不限操作次数。

最后要满足对所有学生 $i$，都有 $a_i\ge b_i$。

问最多的不被交换的学生数。

无解输出 `-1`。

$1\le n\le 3\times10^5,1\le a_i,b_i\le 10^9$。

## 题目分析

判无解是平凡的，直接把 $a,b$ 排序后逐个比较。

然后正难则反，考虑求出最少的被交换学生数。

先把所有学生分成两个集合

$$
A=\{1\le i\le n|a_i\ge b_i\}\\
B=\{1\le i\le n|a_i<b_i\}
$$

说人话就是 $A$ 集合是已经合法的学生，$B$ 集合是尚未合法的学生。

显然，$B$ 集合内的学生一定会被交换。所以只需最小化 $A$ 集合中被交换的学生数。

考虑维护集合 $SA,SB$ 表示被交换的学生的 $a_i,b_i$ 分别构成的集合。

记 $mxa=\max\{i|i\in SA\},mxb=\max\{i|i\in SB\}$。然后分讨 $mxa$ 与 $mxb$ 的大小关系：

+ 若 $mxa\ge mxb$，说明集合 $S$ 可以自给自足，于是可以把 $mxa,mxb$ 从 $SA,SB$ 中删去。

+ 若 $mxa<mxb$，说明需要从集合 $A$ 中找帮手。此时肯定是找到满足 $a_i\ge mxb$ 且 $b_i$ 最小的学生 $i$ 最优。由于 $mxb$ 是单调不增的，所以可以用双指针加入所有合法的 $i$。

不断重复上述过程即可。

具体实现时可以考虑用堆来维护。

## 代码

主要代码如下：

```c++
signed main()
{
    SetIO();
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> tmpa[i] >> tmpb[i];
        if (tmpa[i] >= tmpb[i])
            a[++tota] = Node{tmpa[i], tmpb[i]};
        else
            b[++totb] = Node{tmpa[i], tmpb[i]};
    }
    sort(tmpa + 1, tmpa + n + 1);
    sort(tmpb + 1, tmpb + n + 1);
    sort(a + 1, a + tota + 1, [](Node a, Node b){return a.val > b.val;});
    for (int i = 1; i <= n; i++)if (tmpa[i] < tmpb[i])
    {
        cout << -1;
        return 0;
    }
    for (int i = 1; i <= totb; i++)
    {
        heap.push(b[i].val);
        heap2.push(b[i].need);
    }
    int i = 1;
    while(!heap.empty())
    {
        if (heap.top() >= heap2.top())
        {
            heap.pop(), heap2.pop();
            continue;
        }
        while(i <= tota && a[i].val >= heap2.top())
            heapp.push(a[i]), i++;
        assert(!heapp.empty());
        ans++;
        heap.push(heapp.top().val);
        heap2.push(heapp.top().need);
        heapp.pop();
    }
    cout << n - ans - totb;
    return 0;
}
```

---

## 作者：vanueber (赞：0)

学了二分图的 Hall 定理，写一篇题解记录一下。

# Hall 定理

> 一个二分图存在 **完备匹配** ，当且仅当 $V_1$ 中任意 $k$ 个顶点至少连接 $V_2$ 中 $k$ 个顶点。

这里就不加证明，读者可自行查阅资料。

# 题目大意

给定两个数组 $A,B$，可以选择 $A$ 的一些位置任意重排，使得对于任意的 $i$ 都有 $A_i \ge B_i$。

# 分析

现将 $A,B$ 排序，本题可以转化为一个二分图的问题，如果有 $A_j \ge B_i$，则 $i,j$ 连边。

先把无解的情况判了，如果存在 $A_i < B_i$ 则无解。证明是容易的，如果存在这个 $i$，那么 $i$ 以及其后面一共 $n-i+1$ 个点在二分图中对应的右部点最多只有 $n-i$ 个点，根据 Hall 定理，此时二分图不存在完备匹配，故无解。

接下来考虑最小化被选中重排的集合 $S$，那么 $A_i < B_i$ 的一定要包含在集合中，同时 $S$ 以及对应的 $N(S)$ 也应具有完备匹配。

于是我们先将 $A_i < B_i$ 的提取出来做个排序，如果无法满足条件，则说明一定要从已经合法的一对提取出来，不难发现，我们想要的是 $j$ 满足 $B_j \le A_i$ 且 $A_j$ 最大。感性理解这样正确的原因，我们第一个约束满足了选出来的集合 $S$ 一定有 $A_i\ge B_i$，第二个约束能使得后面的决策能更容易地被满足，缩减 $S$ 的规模。

具体地，我们使用两个小根堆维护二分图的左部点集合 $V_1$，右部点集合 $V_2$。依次检索 $V_1,V_2$ 所有对应元素，如果合法则跳过，否则选取未被选取的点中 $B_j \le A_i$ 且 $A_j$ 最大的，这个可以依次加入并用大根堆维护。

时间复杂度，排序和堆都是 $\Theta(n \log n)$ 的。

# Code


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define uint unsigned int
#define rg register
#define il inline
#define vint vector<int>
#define rep(i,a,b) for(rg int i=(a);i<=(b);++i)
#define sqr(x) ((x)*(x))
using namespace std;
using ll=long long;
const int INF=0x3f3f3f3f;
inline int read()
{
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        w=(w<<1)+(w<<3)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

const int N=3e5+10;
int n,a[N],b[N],tmpa[N],tmpb[N],cnt;
priority_queue<int,vector<int>,greater<int>> V1,V2;
vector<pii> stra;
priority_queue<int> Q;

bool cmp(const pii &a,const pii &b)
{
    return a.second<b.second;
}

int main()
{
    #ifndef ONLINE_JUDGE
    //freopen("in.txt","r",stdin);
    #endif
    cnt=n=read();
    for(int i=1;i<=n;++i) tmpa[i]=a[i]=read(),tmpb[i]=b[i]=read();
    sort(tmpa+1,tmpa+n+1),sort(tmpb+1,tmpb+n+1);
    for(int i=1;i<=n;++i)
    {
        if(tmpa[i]<tmpb[i])
        {
            cout<<-1<<endl;
            return 0;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]<b[i])
        {
            V1.push(a[i]),V2.push(b[i]);
        }
        else
        {
            stra.push_back(make_pair(a[i],b[i]));
        }
    }
    sort(all(stra),cmp);
    auto it=stra.begin();
    while(!V1.empty())
    {
        --cnt;
        int va=V1.top(),vb=V2.top();
        if(va>=vb)
        {
            V1.pop(),V2.pop();
        }
        else
        {
            while(it!=stra.end()&&it->second<=va)
            {
                Q.push(it->first);
                ++it;
            }
            int now=Q.top();
            Q.pop(),V1.pop(),V1.push(now);
        }
    }
    cout<<cnt<<endl;
    return 0;
}
```

不难发现无解的情况当且仅当 $V_1,V_2$ 不合法且备选决策集合为空，所以有不用排序的代码如下。


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define uint unsigned int
#define rg register
#define il inline
#define vint vector<int>
#define rep(i,a,b) for(rg int i=(a);i<=(b);++i)
#define sqr(x) ((x)*(x))
using namespace std;
using ll=long long;
const int INF=0x3f3f3f3f;
inline int read()
{
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        w=(w<<1)+(w<<3)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

const int N=3e5+10;
int n,a[N],b[N],cnt;
priority_queue<int,vector<int>,greater<int>> V1,V2;
vector<pii> stra;
priority_queue<int> Q;

bool cmp(const pii &a,const pii &b)
{
    return a.second<b.second;
}

int main()
{
    #ifndef ONLINE_JUDGE
    //freopen("in.txt","r",stdin);
    #endif
    cnt=n=read();
    for(int i=1;i<=n;++i) a[i]=read(),b[i]=read();
    for(int i=1;i<=n;++i)
    {
        if(a[i]<b[i])
        {
            V1.push(a[i]),V2.push(b[i]);
        }
        else
        {
            stra.push_back(make_pair(a[i],b[i]));
        }
    }
    sort(all(stra),cmp);
    auto it=stra.begin();
    while(!V1.empty())
    {
        --cnt;
        int va=V1.top(),vb=V2.top();
        if(va>=vb)
        {
            V1.pop(),V2.pop();
        }
        else
        {
            while(it!=stra.end()&&it->second<=va)
            {
                Q.push(it->first);
                ++it;
            }
            if(Q.empty())
            {
                cout<<-1<<endl;
                return 0;
            }
            int now=Q.top();
            Q.pop(),V1.pop(),V1.push(now);
        }
    }
    cout<<cnt<<endl;
    return 0;
}
```

---

## 作者：cwfxlh (赞：0)

# [AT_arc147_e](https://www.luogu.com.cn/problem/AT_arc147_e)        

想岔了一点，所以最后看了一半题解才做出来，有点垃圾了。       

考虑如何判定有无解，将 $a_i$ 与 $b_i$ 排序后比较即可。于是我们要选出一个最小的有解集合 $S$ 满足 $T\subset S$，$T$ 是所有 $a_i<b_i$ 的并。       

但是上述的将 $a$ 与 $b$ 排序不好刻画（本人就是卡在这里了），如果硬做或许能做出来但比较繁琐。将 $a$ 与 $b$ 合在一起排序，$b$ 是左括号，$a$ 是右括号，如果能构成合法括号序列即合法。这个描述将两个序列合并到了一起，并且合法的充要条件变成了前缀和均不小于 0。      

将 $T$ 的前缀和搞出来，发现那些满足 $a_i\ge b_i$ 的对如果被加入，在前缀和上的改变是区间加 1 的形式。到了这里做法就明了了，贪心从前往后考虑，当前前缀和如果小于 0，就取覆盖当前点的右端点最大的区间，使用一个优先队列即可。如果有前缀和永远小于 0，就是无解。复杂度 $O(n\log n)$。          

代码：         


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,A[800003],B[800003],ans,cf[800003];
pair<int,int>stk[800003];
map<int,int>mp;
vector<int>lst[800003];
priority_queue<int>Q;
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>A[i]>>B[i];
    for(int i=1;i<=n;i++){
        stk[i*2-1]=make_pair(A[i],-i);
        stk[i*2]=make_pair(B[i],i);
    }
    sort(stk+1,stk+2*n+1);
    for(int i=1,j=1;i<=n*2;i++){
        if(i!=1&&stk[i].first!=stk[i-1].first)j++;
        if(stk[i].second<=0)A[-stk[i].second]=j;
        else B[stk[i].second]=j;
    }
    ans=n;
    for(int i=1;i<=n;i++){
        if(A[i]<B[i]){
            cf[A[i]]--;
            cf[B[i]]++;
            ans--;
        }
        else lst[B[i]].emplace_back(A[i]-1);
    }
    for(int i=1,j=0;i<=2*n;i++){
        j+=cf[i];
        for(auto u:lst[i])Q.push(u);
        while(!Q.empty()){
            if(Q.top()<i)break;
            if(j>=0)break;
            j++;
            cf[Q.top()+1]--;
            ans--;
            Q.pop();
        }
        if(j<0){cout<<-1;return 0;}
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：NightTide (赞：0)

## AT_arc147_e [ARC147E] Examination 题解

首先，考虑无解如何判定。将 $a$ 和 $b$ 分别排序，排序后，有解的充要条件是始终满足 $a_i \ge b_i$。

首先 $a_i < b_i$ 的人必然需要调整，将它们塞入一个集合 $S$ 中。首先内部调整，将 $S$ 内的 $a$ 与 $b$ 排序。然后开始遍历，若某时刻仍存在 $a_i < b_i$ 的情况，则需要其他元素来调整。那么我们必须要加入一个 $b_j \le a_i  < a_j$ 的人才能满足条件。贪心地想，我们显然优先选择 $a_j$ 最大的。

用堆实现。用两个小根堆分别存下 $a_i < b_i$ 的元素的 $a$ 与 $b$；以 $b$ 为第一关键字，用小根堆存下 $a_i \ge b_i$ 的元素；用大根堆存下满足 $b_j \le a_i$ 的所有 $a_j$ 即可。

代码实现如下：

```cpp
#include<bits/stdc++.h>
#define MAXN 300010
using namespace std;
struct node{ int a, b; };
bool operator > (node p, node q){ return p.b > q.b; }
bool operator < (node p, node q){ return p.b < q.b; }
int n, cnt;
node stu[MAXN];
int tmp_a[MAXN], tmp_b[MAXN];
priority_queue<node, vector<node>, greater<node> > t;
priority_queue<int, vector<int>, greater<int> > qa, qb;
priority_queue<int, vector<int>, less<int> > s;
int main(){
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) scanf("%d%d",&stu[i].a,&stu[i].b);
    for(int i = 1; i <= n; i++) tmp_a[i] = stu[i].a, tmp_b[i] = stu[i].b;
    sort(tmp_a + 1, tmp_a + n + 1);
    sort(tmp_b + 1, tmp_b + n + 1);
    for(int i = 1; i <= n; i++){
        if(tmp_a[i] < tmp_b[i]){
            printf("-1\n");
            exit(0);
        }
    }
    for(int i = 1; i <= n; i++){
        if(stu[i].a < stu[i].b) qa.push(stu[i].a), qb.push(stu[i].b);
        else t.push(stu[i]);
    }
    while(!qa.empty()){
        cnt++;
        int ta = qa.top(), tb = qb.top();
        if(ta >= tb){
            qa.pop(); qb.pop();
            continue;
        }
        while(!t.empty() && t.top().b <= ta){
            s.push(t.top().a);
            t.pop();
        }
        qa.pop(); qa.push(s.top()); s.pop();
    }
    printf("%d\n",n - cnt);
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

对于一堆人的集合 $S$，把分数 $a_i$ 和期望得分 $b_i$ 放到一起，看是否可以在 $S$ 内部交换，使得满足条件。

这个是容易的，只需要倒序，将 $a_i,b_i$ 挨个匹配即可。

如果用可以方便维护的数据结构呢？在 $a_i$ 处 $+1$，在 $b_i$ 处 $-1$。满足条件当且仅当后缀最小值 $\ge 0$（其实应该是 $=0$，因为第一个点的后缀一定是 $0$）。这是类似于上面的贪心。

那么，我们任务是把最少的人扔到这个交换分数的集合 $S$ 里面，满足上面条件。

首先，对于 $a_i\lt b_i$ 的人，肯定要扔进去。

那么，对于第一个后缀 $\lt 0$ 的位置 $pos$，需要一个 $\ge pos$ 的 $a_i$，为了贪心，我们希望这个人造成的 $-1$ 的位置尽可能靠前，于是应该选择 $b_i$ 最小的。

考虑到每次的 $pos$ 的单调不增的，可以扫描过来然后用 multiset 或者堆维护。后缀最小值可以用线段树维护。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fir first
#define sec second
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid (l + r >> 1)
using namespace std;
const int N = 3e5 + 5, inf = 0x3f3f3f3f;
int n, m, aa[N << 1], tot, minn[N << 3], ans, p, x, sum[N << 3], pos;
pii a[N], b[N];
struct DPQ{
	priority_queue<int> a, b;
	inline void push(int x){
		a.push(-x);
	}
	inline bool empty(){
		return a.empty();
	}
	inline void pop(int x){
		b.push(-x);
		while(!a.empty() && !b.empty() && a.top() == b.top()) a.pop(), b.pop();
	}
	inline int top(){
		return -a.top();
	}
}q;
inline void modify(int p, int l, int r, int x, int val){
	if(l == r){
		minn[p] += val;
		sum[p] = minn[p];
		return ;
	}
	if(mid >= x) modify(ls, l, mid, x, val);
	else modify(rs, mid + 1, r, x, val);
	minn[p] = min(minn[ls] + sum[rs], minn[rs]);
	sum[p] = sum[ls] + sum[rs];
}
inline int findpos(int p, int l, int r, int val = 0){
	if(l == r) return l;
	if(minn[rs] + val < 0) return findpos(rs, mid + 1, r, val);
	return findpos(ls, l, mid, val + sum[rs]);
}
inline bool cmp(pii x, pii y){
	return x.fir > y.fir;
}
int main(){
//	freopen("data.in", "r", stdin);
//	freopen("code.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d", &a[i].fir, &a[i].sec);
		aa[++tot] = a[i].fir, aa[++tot] = a[i].sec;
	}
	sort(aa + 1, aa + tot + 1);
	tot = unique(aa + 1, aa + tot + 1) - aa - 1;
	for(int i = 1; i <= n; i++){
		a[i].fir = lower_bound(aa + 1, aa + tot + 1, a[i].fir) - aa;
		a[i].sec = lower_bound(aa + 1, aa + tot + 1, a[i].sec) - aa;
		if(a[i].fir < a[i].sec){
			ans++;
			modify(1, 1, tot, a[i].sec, -1);
			modify(1, 1, tot, a[i].fir, 1);
		}
		else b[++m] = a[i];
	}
	sort(b + 1, b + m + 1, cmp);
	p = 1;
	while(minn[1] < 0){
		pos = findpos(1, 1, tot);
		while(b[p].fir >= pos){
			q.push(b[p].sec);
			p++;
		}
		if(q.empty()){
			puts("-1");
			return 0;
		}
		ans++;
		x = q.top();
		modify(1, 1, tot, pos, 1);
		modify(1, 1, tot, x, -1);
		q.pop(x);
	}
	printf("%d\n", n - ans);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

$-1$ 先判掉，这个是个人都会判，直接把 $a$ 和 $b$ 分别排序即可。

把 $a<b$ 的搞出来。

然后如果你能在内部解决掉的话，那么显然在内部解决掉即可，这样显然会让交换的人更少，所以仍然是类似的贪心策略，让 $a$ 小的匹配 $b$ 小的，$a$ 大的匹配 $b$ 大的。

剩下的显然需要和 $a\ge b$ 的进行交换。

为了让这个需要交换的元素不增加，我们显然每一步只会选择 $b'\le a$ 的来和这个交换。然后因为要让需要交换的数量尽量少，所以选 $a$ 最大的即可。

注意到此时 $a$ 变大了，可能会产生新的交换单位，用大根堆维护，把它们插入即可，但是此时 $a$ 仍然有可能没有超过 $b$，所以我们需要继续搞 $a$。

然后如果现在搞到的 $a$ 有可能比后面的 $a$ 更大，根据上面提到的“小配小大配大”原则，应该取后面的 $a$，所以我们应该对 $a$ 维护一个小根堆，每次取最小的那个就行了。

因为你判了无解，所以最后你一定能找到一个 $a\ge b$。

然后其实你不需要单独判无解，在计算过程中，如果大根堆的最大的 $a$ 已经不超过当前的 $a$ 的话，交换会更劣，不交换无解，此时显然无解，在这里输出 $-1$ 即可。

---

