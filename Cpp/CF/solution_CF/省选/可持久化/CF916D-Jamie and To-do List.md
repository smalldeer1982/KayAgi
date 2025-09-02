# Jamie and To-do List

## 题目描述

“为什么我要完成这么多作业？”

Jamie 正忙于他的学校生活。

他开始忘记他必须做的作业。他决定把这些事情写在 To-Do List 上。

他为他的每项任务分配一个价值优先级(较低的价值意味着更重要)，这样他就可以决定他需要花更多的时间在哪个任务上。

几天后，Jamie 发现名单太大了，他甚至不能自己管理名单！由于您是 Jamie 的好朋友，请帮助他编写一个程序来支持待办事项列表中的以下操作:

`set ai xi`：设置任务 $a_i$ 的优先级为 $x_i$，如果该列表中没有出现则加入该任务。

`remove a_i`：删除该任务。

`query a_i`：求优先级比 $a_i$ 小的任务个数，如果该任务已被删除则输出 $-1$。

`undo sum`：删除此次操作之前的 $sum$ 次操作。

在 Day 0，To-Do List 为空，在接下来 $Q$ 个日子内，Jamie 都会在四个操作中任选一个执行。

对于每个询问操作，输出对应的答案。

## 说明/提示

保证输入的字符串由小写字符构成，设其长度为 $len$，则 $1\leq len\leq15$。

$1\le Q\le10^5$，并且保证对于所有的 undo 操作，$sum$ 不超过该天之前的天数。

## 样例 #1

### 输入

```
8
set chemlabreport 1
set physicsexercise 2
set chinesemockexam 3
query physicsexercise
query chinesemockexam
remove physicsexercise
query physicsexercise
query chinesemockexam
```

### 输出

```
1
2
-1
1
```

## 样例 #2

### 输入

```
8
set physicsexercise 2
set chinesemockexam 3
set physicsexercise 1
query physicsexercise
query chinesemockexam
undo 4
query physicsexercise
query chinesemockexam
```

### 输出

```
0
1
0
-1
```

## 样例 #3

### 输入

```
5
query economicsessay
remove economicsessay
query economicsessay
undo 2
query economicsessay
```

### 输出

```
-1
-1
-1
```

## 样例 #4

### 输入

```
5
set economicsessay 1
remove economicsessay
undo 1
undo 1
query economicsessay
```

### 输出

```
-1
```

# 题解

## 作者：Karry5307 (赞：6)

### 题意

你需要维护一个任务列表，有 $q$ 次操作，每次操作形如以下四种：

- `set a x`：设置任务 $a$ 的优先级为 $x$，如果任务列表中没有 $a$ 则加进来。

- `remove a`：将任务 $a$ 移除列表。

- `query a`：求出有多少个任务的优先级比 $a$ 的小，如果 $a$ 不在列表里输出 $-1$。

- `undo d`：撤销这次操作之前的 $d$ 个操作。

**注意撤销操作可以撤销之前的撤销操作**。

$\texttt{Data Range:}1\leq q\leq 10^5,1\leq x\leq 10^9,1\leq\vert a\vert\leq 15$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13586246.html)

我又是一个不看数据范围的屑 >_<

~~为什么这场的 D 比 E 还难写啊~~

好久没写可持久化数据结构了，来写个题解复习一下。

一看到什么撤销操作估计跟可持久化数据结构分不开了。

看到 `query` 操作其实可以开一棵可持久化权值线段树来维护一下，然后 `set` 的话需要一个可持久化数组来维护每个任务的优先级。

然后按照题意模拟就得了，因为这题的 $x\leq 10^9$ 所以不写结构体式线段树可以免去建树的空间开销。

注意一下空间问题即可通过，这里可能要根据数据范围估算一下空间开销。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51; 
map<string,ll>mp;
ll n,totn,totid,x,id,p,limit=1e9;
string op,str;
ll rt[MAXN<<2],rt2[MAXN<<2],sm[MAXN<<6],ls[MAXN<<6],rs[MAXN<<6];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll getId(string s)
{
	return mp.find(s)==mp.end()?mp[s]=++totid:mp[s];
}
inline void update(ll node)
{
	sm[node]=sm[ls[node]]+sm[rs[node]];
}
inline ll add(ll l,ll r,ll pos,ll val,ll node)
{
	ll cur=++totn;
	ls[cur]=ls[node],rs[cur]=rs[node];
	if(l==r)
	{
		return sm[cur]=sm[node]+val,cur;
	}
	ll mid=(l+r)>>1;
	if(pos<=mid)
	{
		ls[cur]=add(l,mid,pos,val,ls[node]);
	}
	else
	{
		rs[cur]=add(mid+1,r,pos,val,rs[node]);
	}
	return update(cur),cur;
}
inline ll query(ll l,ll r,ll ql,ll qr,ll node)
{
	if(ql<=l&&qr>=r)
	{
		return sm[node];
	}
	ll mid=(l+r)>>1,res=0;
	res+=ql<=mid?query(l,mid,ql,qr,ls[node]):0;
	res+=qr>mid?query(mid+1,r,ql,qr,rs[node]):0;
	return res;
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		cin>>op,rt[i]=rt[i-1],rt2[i]=rt2[i-1];
		if(op=="set")
		{
			cin>>str,x=read(),id=getId(str),p=query(1,limit,id,id,rt2[i]);
			p?rt[i]=add(1,limit,p,-1,rt[i]):1;	
			rt[i]=add(1,limit,x,1,rt[i]),rt2[i]=add(1,limit,id,x-p,rt2[i]);
		}
		if(op=="remove")
		{
			cin>>str,id=getId(str),p=query(1,limit,id,id,rt2[i]);
			p?rt[i]=add(1,limit,p,-1,rt[i]):1,rt2[i]=add(1,limit,id,-p,rt2[i]);
		}
		if(op=="undo")
		{
			x=read(),rt[i]=rt[i-x-1],rt2[i]=rt2[i-x-1];
		}
		if(op=="query")
		{
			cin>>str,id=getId(str),p=query(1,limit,id,id,rt2[i]);
			cout<<(p==0||p==1?p-1:query(1,limit,1,p-1,rt[i]))<<endl;
		}
	}
}
```

---

## 作者：chenzida (赞：3)

u1s1这题挺板子的

首先，这题要回到之前的状态，很容易想到要用可持久化数据结构，然后再看到这个题要维护插入删除以及 $rank$，所以要用平衡树。但是很明显可持久化平衡树不太可写，于是我们考虑可持久化值域线段树。

然后我们发现我们没有办法记录一个 $a_i$ 的大小，所以我们考虑开两棵主席树，一棵记录当前点的紧急度，另一棵维护 $rank$。

重点说一下维护 $rank$ 的那棵，假设一个节点对应的 $[L,R]$，那这个节点节点维护的是紧急度在 $[L,R]$ 之间的点的个数。然后查找的时候直接查找 $<$ 当前点的紧急度的点的个数即可。

注意：

1.当当前点紧急度为 $1$ 的时候，你如果直接减 $1$ 并 $query$ 的话，会直接死递归，所以要特判一下。

2.空间一定要开够，因为有两棵树。建议开到 $\text{NR<<7}$。

然后就没有啥了，代码如下：

```
#include<cstdio>
#include<cstring>
#include<iostream> 
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int NR=1e5+10;
const int MAX=1e9;
int n;
int tot,cnt;
int root1[NR],root2[NR];
map<string,int>mp;
struct Nd{int l,r,sum;}tr[NR<<7];
void update(int rt){tr[rt].sum=tr[tr[rt].l].sum+tr[tr[rt].r].sum;}
void change(int &rt,int l,int r,int x,int val)
{
	int la=rt;rt=++tot;tr[rt]=tr[la];
	if(l==r){tr[rt].sum+=val;return;}
	int mid=(l+r>>1);
	if(x<=mid)change(tr[rt].l,l,mid,x,val);
	else change(tr[rt].r,mid+1,r,x,val);
	update(rt);
}
int query(int rt,int l,int r,int L,int R)
{
	if(l==L&&r==R)return tr[rt].sum;int mid=(l+r>>1);
	if(R<=mid)return query(tr[rt].l,l,mid,L,R);
	else if(L>mid)return query(tr[rt].r,mid+1,r,L,R);
	else return query(tr[rt].l,l,mid,L,mid)+query(tr[rt].r,mid+1,r,mid+1,R);
}
int getnum(string str){return mp[str]?mp[str]:mp[str]=++cnt;}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		string op;cin>>op;
		root1[i]=root1[i-1],root2[i]=root2[i-1];
		if(op=="set")
		{
			string str;cin>>str;int x=getnum(str),y=read();
			int p=query(root1[i],1,MAX,x,x);
			if(p)change(root2[i],1,MAX,p,-1);
			change(root2[i],1,MAX,y,1);
			change(root1[i],1,MAX,x,y-p);
		}
		else if(op=="remove")
		{
			string str;cin>>str;int x=getnum(str);
			int p=query(root1[i],1,MAX,x,x);
			if(!p)continue;
			change(root1[i],1,MAX,x,-p);
			change(root2[i],1,MAX,p,-1);
		}
		else if(op=="query")
		{
			
			string str;cin>>str;int x=getnum(str);
			int p=query(root1[i],1,MAX,x,x);
			if(!p){puts("-1");continue;}
			if(p==1){puts("0");continue;}
			printf("%d\n",query(root2[i],1,MAX,1,p-1));
		}
		else{int x=read();root1[i]=root1[i-x-1],root2[i]=root2[i-x-1];}
	}
	return 0;
}

---

## 作者：xunzhen (赞：2)

这题是我主席树第一题~~实际就是一个可持久化线段树~~。我一开始做的时候~~十分naive地~~没有写可持久化，直接用STLmap来记录，然后就...
![pic](http://xz-cnyali.com/wp-content/uploads/2018/02/916D.png)

用两个数组分别记录权值线段树和每个任务的优先级，记录他们不同版本根的编号，然后就是一个板子+操作了。

```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<map>
#define debug(...) printf(__VA_ARGS__),fflush(stdout)
#define inf 1000000000
#define maxn 100010
using namespace std;
map<string,int> f;
int root[maxn],wt[maxn],cnt=0,top=0;
string s,t;
struct node{
	int ls,rs,w;
}A[10000010];
//获取字符串的ID
int get_ID(string s){
	if (f.count(s)) return f[s];
	return f[s]=++top;
}
//主席树板子
void update(int x,int y,int v){
	//指向上一个状态，节约内存
	A[x].ls=A[y].ls;
	A[x].rs=A[y].rs;
	A[x].w=A[y].w+v;
}
void change(int &nrt,int rt,int l,int r,int x,int v){
	nrt=++cnt; update(nrt,rt,v);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (x<=mid) change(A[nrt].ls,A[rt].ls,l,mid,x,v);
	else change(A[nrt].rs,A[rt].rs,mid+1,r,x,v);
}
int query(int rt,int l,int r,int L,int R){
	if (l>=L && r<=R) return A[rt].w;
	int mid=(l+r)>>1;
	int sum=0;
	if (L<=mid) sum+=query(A[rt].ls,l,mid,L,R);
	if (R>mid) sum+=query(A[rt].rs,mid+1,r,L,R);
	return sum;
}
int main(){
#ifdef xunzhen
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
#endif
	int q;
	cin>>q;
	for (int i=1;i<=q;i++){
		int k;
		cin>>t;
		//继承上一状态
		root[i]=root[i-1]; wt[i]=wt[i-1];
		//4个操作
		if (t[0]=='s'){
			cin>>s>>k;
			int id=get_ID(s);
			int p=query(wt[i],1,inf,id,id);
			if (p) change(root[i],root[i],1,inf,p,-1);
			change(root[i],root[i],1,inf,k,1);
			change(wt[i],wt[i],1,inf,id,k-p);
		}
		if (t[0]=='r'){
			cin>>s;
			int id=get_ID(s);
			int p=query(wt[i],1,inf,id,id);
			if (p) change(root[i],root[i],1,inf,p,-1);
			change(wt[i],wt[i],1,inf,id,-p);
		}
		if (t[0]=='q'){
			cin>>s;
			int id=get_ID(s);
			int p=query(wt[i],1,inf,id,id);
			if (!p) printf("-1\n");
			else if (p==1) printf("0\n");
			else printf("%d\n",query(root[i],1,inf,1,p-1));
			fflush(stdout);
		}
		if (t[0]=='u'){
			cin>>k;
			root[i]=root[i-k-1];
			wt[i]=wt[i-k-1];
		}
	}
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
这不是板板题？~~一眼就秒了~~。
# 思路
首先对于有撤销操作的多半是可持久化的某个数据结构没得跑了，那么对于这道题既然涉及到求排名，那不是可持久化平衡树就是可持久化权值线段树，这道题这持久化线段树好写一点所以我用了后者，但是由于这道题还需要维护一下每一个点的优先级，所以需要两棵线段是一棵维护优先级一棵维护排名即可。

相信大家都对可持久化线段树有所了解，就不做过多的解释，如果实在不会可以去 [模板题中学习一下](https://www.luogu.com.cn/problem/P3919)。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
int n;
unordered_map<string,int>mp;
const int N=1e5+10,M=1e9+10;
struct node{
	int l,r;
	int sum;
}tr[N<<6],tr2[N<<6];
int rt[N],rt1[N];
void up(int x) {
	tr[x].sum=tr[tr[x].l].sum+tr[tr[x].r].sum;
}
int idx,idx1;
int modify(int u,int l,int r,int k,int val) {
	int p=++idx;
	tr[p]=tr[u];
	if(l==r) {
		tr[p].sum+=val;
		return p;
	}
	int mid=l+r>>1;
	if(mid>=k) tr[p].l=modify(tr[p].l,l,mid,k,val);
	else tr[p].r=modify(tr[p].r,mid+1,r,k,val);
	up(p);
	return p;
}
int modify1(int u,int l,int r,int k,int val) {
	int p=++idx1;
	tr2[p]=tr2[u];
	if(l==r) {
		tr2[p].sum=val;
		return p;
	}
	int mid=l+r>>1;
	if(mid>=k) tr2[p].l=modify1(tr2[p].l,l,mid,k,val);
	else tr2[p].r=modify1(tr2[p].r,mid+1,r,k,val);
	return p;
}
int Ans1(int u,int l,int r,int k) {
	if(!u||!k) return u;
	if(l==r) return tr2[u].sum;
	int mid=l+r>>1;
	if(mid>=k) return Ans1(tr2[u].l,l,mid,k);
	else return Ans1(tr2[u].r,mid+1,r,k);
}
int Ans(int u,int l,int r,int k)  {
	if(!u) return false;
	if(l==r) return tr[u].sum;
	int mid=l+r>>1;
	if(mid>=k) return Ans(tr[u].l,l,mid,k);
	return tr[tr[u].l].sum+Ans(tr[u].r,mid+1,r,k);
}
int tot;
struct cha{
	string opt;
	string s;
	int x;
}q[N]; 
void solve() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	rep(i,1,n) {
		rt[i]=rt[i-1];
		rt1[i]=rt1[i-1];
		cin>>q[i].opt;
		if(q[i].opt=="set") {
			cin>>q[i].s;
			if(!mp[q[i].s]) mp[q[i].s]=++tot;
			cin>>q[i].x;
			int now=mp[q[i].s],xx=Ans1(rt1[i],1,M,now);
			if(xx) rt[i]=modify(rt[i],1,M,xx,-1);
			rt[i]=modify(rt[i],1,M,q[i].x,1);
			rt1[i]=modify1(rt1[i],1,M,now,q[i].x);
		}else if(q[i].opt=="remove") {
			cin>>q[i].s;
			int now=mp[q[i].s],xx=Ans1(rt1[i],1,M,now);
			if(!now||!xx) continue;
			rt1[i]=modify1(rt1[i],1,M,now,0);
			rt[i]=modify(rt[i],1,M,xx,-1);
		}else if(q[i].opt=="query") {
			cin>>q[i].s;
			int now=mp[q[i].s],xx=Ans1(rt1[i],1,M,now);
			if(xx==0||!now) cout<<"-1"<<endl;
			else if(xx==1) cout<<"0"<<endl;
			else cout<<Ans(rt[i],1,M,xx-1)<<endl;
			cout<<flush;
		}else {
			cin>>q[i].x;
			rt[i]=rt[i-q[i].x-1];
			rt1[i]=rt1[i-q[i].x-1];
		}
	}
	return;
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}

```

---

## 作者：OIer_ACMer (赞：1)

~~毛子的网站每天下午是有多少人打月赛啊！！！~~

------------
## 警钟敲烂：
别看这道题主席树很好切，别看这道题的代码很好码，一旦你的建树写错一切凉凉~~接着就是无数的 bug 等着你~~。

------------
## 大致思路：
这道题是一道主席树模板题，主要考察的就是学生对于主席树各个性质的灵活使用，下面，我就来讲一下这道题的大致思路。

首先，看到第四个操作的撤销应该不难想到使用主席树去维护吧，因为**主席树最大的特点就是可以访问历史版本**，不过写题的时候想了半天总是感觉维护的有点麻烦或者不太可以维护~~说白了就是自己懒~~，于是就去做找规律的题直到自己已经累到虚脱。后来在想一想，其实这道题维护的话直接用两棵主席树加一个 map 类型的 $mp$ 数组就足够了，第一个存科目，第二个存优先级。

之后，我们需要通过给出的输入数据来维护两个主席树，维护过程如下：

1. $mp$ 数组用于记录每次输入的科目的名字 $name$ 以及 $name$ 的优先级 $id$，以便为后续操作做准备。

2. 第一个 $mp$ 数组对应的字符串下标为 $id$，第二个为 $id$ 优先级，在做操作时，我们判断如果 $id$ 的值为 $0$，则没有出现，则直接进行后续操作。

3. 接着，如果操作是加入科目，则根据前面的计划判断该科目是否在列表中出现，有则在原基础以上更新，没有则新开一个点，将初始 $val$ 设为 $1$。

4. 同理，在处理删除操作时，我们也只用根据前面的操作判断是否出现皆可以了，没有出现则啥都不用管，否则就先将这个科目的优先级算出来，并**查询有多少个科目优先级小于该删除科目**，因为**删除是个复杂操作，会影响到后续节点的优先级排列**，所以在删除之后还需要对小于该科目优先级的科目进行后续处理，利用 dfs 双重搜索重新建点，并在之前将原先的点全部赋值为负数（因为不用了）。

5. 如果操作是“查询有多少个事情的优先级小于 $a_i$ 的优先级，如果 $a_i$ 不存在，输出 $-1$”，则按照原先的判断机制（就是第 $2$ 条说的）进行判断，如果有这个点，则调用 $\operatorname{query}$，并直接输出答案。而 $\operatorname{query}$ 的判断机制则和线段树求和差不多（~~真的~~），如果到了问题区间，则直接返回该区间的 $sum$ 值，并通过递归传上去，求和，并最终返回最终答案。

6. 最终，我们在处理撤销操作时，其实不用想的那么复杂，只用定义两个数组 $root$ 来存各次操作带来的影响，一个存比它优先级小的，一个存目前的，进行备份，遇上这种操作直接将原来没有撤销之前的结果赋值到现在的 $root_x$ 里面就可以了。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int inf = 0x3f3f3f3f;
const int N = 1e5 + 100;
struct Node
{
    int l, r, lson, rson, sum;
} tree[N * 100];
int root1[N], root2[N], cnt, id;
map<string, int> mp;
void update(int &k, int l, int r, int pos, int val)
{
    tree[++cnt] = tree[k], k = cnt, tree[k].sum += val, tree[k].l = l, tree[k].r = r; // 新建操作
    if (l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
    {
        update(tree[k].lson, l, mid, pos, val);
    }
    else
    {
        update(tree[k].rson, mid + 1, r, pos, val);
    }
}
int query(int k, int l, int r)
{
    if (tree[k].l > r || tree[k].r < l)
    {
        return 0;
    }
    if (tree[k].l >= l && tree[k].r <= r)
    {
        return tree[k].sum;
    }
    return query(tree[k].lson, l, r) + query(tree[k].rson, l, r);
}
int get_id(string s)
{
    if (!mp.count(s))
    {
        mp[s] = ++id;
    }
    return mp[s];
}
int main()
{
    int n;
    n = read();
    for (int i = 1; i <= n; i++)
    {
        root1[i] = root1[i - 1], root2[i] = root2[i - 1];
        string s, name;
        cin >> s;
        if (s == "set") // 将name的优先级设置为val
        {
            cin >> name;
            int val, id = get_id(name);//获取优先级
            val = read();
            int pre = query(root1[i], id, id);
            if (pre)
            {
                update(root1[i], 1, inf, id, val - pre), update(root2[i], 1, inf, pre, -1), update(root2[i], 1, inf, val, 1); // 如果有这个数
            }
            else
            {
                update(root1[i], 1, inf, id, val), update(root2[i], 1, inf, val, 1); // 没有这个数
            }
        }
        else if (s == "remove") 
        {
            cin >> name;
            int id = get_id(name);
            int pre = query(root1[i], id, id);
            if (!pre)
            {
                continue;
            }
            update(root1[i], 1, inf, id, -pre);
            update(root2[i], 1, inf, pre, -1);
        }
        else if (s == "query")
        {
            cin >> name;
            int id = get_id(name);
            int pre = query(root1[i], id, id);
            if (!pre)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << query(root2[i], 1, pre - 1) << endl;
            }
        }
        else if (s == "undo")
        {
            int x;
            x = read();
            root1[i] = root1[i - x - 1], root2[i] = root2[i - x - 1];
        }
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121855205)

---

## 作者：yizhiming (赞：1)

## 题目大意

维护一个任务字符集，四种操作。

1. 将任务 $a_i$ 优先度设为 $x_i$，若字符集中无 $a$ 则，将其加入字符集。

2. 删除任务 $a_i$。

3. 求所有优先度小于字符 $a_i$ 的字符数，若 $a_i$ 不在集合中输出 `-1`。

4. 撤销之前的 $x_i$ 次操作。

个人感觉题面翻译的有点歧义，就改了改写上去。

$1 \leq n,q \leq 10^5,1\leq x_i \leq 10^5$。

## 题目分析

撤销操作不难想到可持久化线段树回溯到历史版本。

我们需要维护每个字符串的优先度，以及每个优先度的串数量，以便于在线段树上二分查找小于 $k$ 的数的总数。

然而这东西并不能只用一棵可持久化线段树维护，所以我们考虑开两棵，一棵维护字符串索引值为 $i$ 的字符串的优先度，另一棵维护优先度为 $x$ 的字符串数量。

字符串的索引值用 $\texttt{map}$ 维护即可。

由于 $x_i \geq 1$，我们令一个字符串优先度为 $0$ 表示该字符串未出现或者被删除。每次操作 $1$，若该字符串原本优先度为 $0$，则我们直接将新的优先度插入新版本可持久化线段树上即可。并在第一棵线段树上修改字符串的优先度。

若不为 $0$，我们要先把原优先度的贡献删掉，我们可以直接将当前版本下标为原优先度的数值直接减一，相当于消去贡献，并在新优先度加一。

移除操作直接在第一棵线段树上，将字符串优先度修改即可。

查询操作，若 $a_i$ 的优先度为 $x_i$ ，则我们在第二棵线段树上二分查找下标在 $[1,x_i-1]$ 的区间和即可。

回溯操作直接更改当前版本 $rt_i$ 为 $rt_i-x_i+1$ 即可。

小细节，如果删除操作删的是一个优先度为 $0$ 的节点，虽然不用修改，但是要用上一个版本的 $rt$ 覆盖当前版本的 $rt$ （这个伞兵细节让我调了好久）。

## Code

写的有点冗长，望谅解。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <map>
using namespace std;
int read(){
	int x=0,f=1;char ch = getchar();
	while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch = getchar();}
	while(ch>='0'&&ch<='9'){x = x*10+ch-'0';ch = getchar();}
	return x*f;
}
const int N = 1e5+5;
const int M = 100*N;
map<string,int>mp;
int top;
int rk(string s){
	if(mp[s]==0){
		return mp[s]=++top;
	}else{
		return mp[s];
	}
}
struct aa{
	int lc,rc,num;
}node1[M],node2[M];//1表示以优先级为下标，出现次数为权值，2表示以字符串rnk为下标，优先级为权值。 
int tot1,tot2;
int rt1[N],rt2[N];
void pushup1(int u){
	node1[u].num = node1[node1[u].lc].num+node1[node1[u].rc].num;
}
void ins1(int &u,int v,int l,int r,int x,int z){
	u = ++tot1;
	node1[u] = node1[v];
	if(l==r){
		node1[u].num+=z;
		return;
	}
	int mid = (l+r)/2;
	if(x<=mid){
		ins1(node1[u].lc,node1[v].lc,l,mid,x,z);
	}else{
		ins1(node1[u].rc,node1[v].rc,mid+1,r,x,z);
	}
	pushup1(u);
}
int query1(int u,int l,int r,int x){
	if((!u)||(l>x)){
		return 0;
	}
	if(l==r){
		return node1[u].num;
	}
	int mid = (l+r)/2;
	if(mid>x){
		return query1(node1[u].lc,l,mid,x);
	}else{
		return node1[node1[u].lc].num+query1(node1[u].rc,mid+1,r,x);
	}
}
void ins2(int &u,int v,int l,int r,int x,int z){
	u = ++tot2;
	node2[u] = node2[v];
	if(l==r){
		node2[u].num = z;
		return;
	}
	int mid = (l+r)/2;
	if(x<=mid){
		ins2(node2[u].lc,node2[v].lc,l,mid,x,z);
	}else{
		ins2(node2[u].rc,node2[v].rc,mid+1,r,x,z);
	}
}
int query2(int u,int l,int r,int x){
	if(!u){
		return 0;
	}
	if(l==r){
		return node2[u].num;
	}
	int mid = (l+r)/2;
	if(x<=mid){
		return query2(node2[u].lc,l,mid,x);
	}else{
		return query2(node2[u].rc,mid+1,r,x);
	}
}
int main(){
	int m;
	m = read();
	string opt,x;int v;
	for(int i=1;i<=m;i++){
		cin>>opt; 
		if(opt[0]=='s'){
			cin>>x;
			v = read();
			int a = query2(rt2[i-1],1,m,rk(x));
			if(a==0){
				ins2(rt2[i],rt2[i-1],1,m,rk(x),v);
				ins1(rt1[i],rt1[i-1],1,1e9,v,1);
				
			}else{
				ins2(rt2[i],rt2[i-1],1,m,rk(x),v);
				ins1(rt1[i],rt1[i-1],1,1e9,a,-1);
				ins1(rt1[i],rt1[i],1,1e9,v,1);
			}
		}else if(opt[0]=='r'){
			cin>>x;
			int a = query2(rt2[i-1],1,m,rk(x));
			if(a!=0){
				ins2(rt2[i],rt2[i-1],1,m,rk(x),0);
				ins1(rt1[i],rt1[i-1],1,1e9,a,-1);
			}else{
				rt2[i] = rt2[i-1];rt1[i] = rt1[i-1];
			}
		}else if(opt[0]=='q'){
			cin>>x;
			rt2[i] = rt2[i-1];rt1[i] = rt1[i-1];
			int a = query2(rt2[i],1,m,rk(x));
			if(a==0){
				cout<<-1<<"\n";
			}else{
				cout<<query1(rt1[i],1,1e9,a-1)<<"\n";
			}
		}else{
			v = read();
			rt1[i] = rt1[max(0,i-v-1)];
			rt2[i] = rt2[max(0,i-v-1)];
		}
	}
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

怎么题解区没有指针写法啊（恼）

题意：维护带权字符串集合的权值修改，删除元素，求权值意义下的排名。带撤销。强制在线。

Tip：关于为什么是强制在线，这是一道交互题。
# 思路
注意到不带撤销的话平衡树可以轻松维护，但带撤销就要可持久化。

考虑怎么不写可持久化平衡树，用可持久化动态开点权值线段树维护之。

字符串作下标不太好维护，用 `std::map` 转换成编号。

建两棵树，$x_i$ 表示编号为 $i$ 的字符串的权值，$y_i$ 表示权值为 $i$ 的字符串的数量。

模拟即可。注意特判询问字符串不存在或权值为 $1$ 的情况。
# 代码
```cpp
#include <map>
#include <string>
#include <cstdio>
#define G int m = s + t >> 1
#define D if(u) M(u, -1, 1, 1e9, y[i])
#define S(v) M(a, v - u, 1, 1e5, x[i])
#define I a = F();u = Q(a, a, 1, 1e5, x[i])
#define U(v) x[i] = x[i - v - 1];y[i] = y[i - v - 1]
using namespace std;
inline int R()
{
    int r = 0;char c = getchar();while(!isdigit(c)) c = getchar();
    while(isdigit(c)) r = r * 10 + c - '0', c = getchar();return r;
}
int n, c, a, u, v;char o[7], s[16];map<string, int> m;
int F() {scanf("%s", s);return m[s] ? m[s] : m[s] = ++c;}
struct T{T *l = 0, *r = 0;int v = 0;void u() {v = 0;if
(l) v += l->v;if(r) v += r->v;}}*x[100050], *y[100050];
void M(int l, int x, int s, int t, T *&p)
{
    p = p ? new T(*p) : new T;if(s == t) {p->v += x;return;}G;if
    (l <= m) M(l, x, s, m, p->l);else M(l, x, m + 1, t, p->r);p->u();
}
int Q(int l, int r, int s, int t, T *p)
{
    if(!p) return 0;if(l <= s && t <= r) return p->v;G;int q = 0;if(l <= m)
    q += Q(l, r, s, m, p->l);if(r > m) q += Q(l, r, m + 1, t, p->r);return q;
}
int main()
{
    n = R();for(int i = 1;i <= n;++i)
    {
        scanf("%s", o);U(0);switch(o[0])
        {
            case 's': I;D;M(v = R(), 1, 1, 1e9, y[i]);S(v);break;case 'r':
            I;D;S(0);break;case 'q': I;printf("%d\n", --u <= 0 ? u : Q(1, u,
            1, 1e9, y[i]));fflush(stdout);break;case 'u': a = R();U(a);break;
        }
    }
    return 0;
}
```


---

## 作者：TulipeNoire (赞：1)

对于主席树初学者来说是个不错的题。我们维护两个可持久化线段树，一个表示优先级上的数量的权值线段树，还有是一个维护每个时刻上每个任务的优先级的可持久化数组。

很明显，如果我们使用动态开点，是可以开下的。全剧终。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,m,b[N],c[N],d[N],e[N],cnt[2],root[N][2];
string opt[N],s[N];
map<string,int>k;//处理字符串
struct segment_tree {
    int lc,rc,val;
}tr[N*155][2];//开大一点。0是权值线段树，1是可持久化数组
int upd1(int now,int l,int r,int x,int d) {
    int p=++cnt[0];
    tr[p][0]=tr[now][0];
    if (l==r) {
        tr[p][0].val+=d;
        return p;
    }
    int mid=l+r>>1;
    if (x<=mid) tr[p][0].lc=upd1(tr[now][0].lc,l,mid,x,d);
    else tr[p][0].rc=upd1(tr[now][0].rc,mid+1,r,x,d);
    tr[p][0].val=tr[tr[p][0].lc][0].val+tr[tr[p][0].rc][0].val;
    return p;
}
int upd2(int now,int l,int r,int x,int d) {
    int p=++cnt[1];
    tr[p][1]=tr[now][1];
    if (l==r) {
        tr[p][1].val=d;
        return p;
    }
    int mid=l+r>>1;
    if (x<=mid) tr[p][1].lc=upd2(tr[now][1].lc,l,mid,x,d);
    else tr[p][1].rc=upd2(tr[now][1].rc,mid+1,r,x,d);
    return p;
}
int get(int p,int l,int r,int L,int R,int t) {
    if (L>R) return 0;
    if (L<=l&&r<=R) return tr[p][t].val;
    int mid=l+r>>1,res=0;
    if (L<=mid) res+=get(tr[p][t].lc,l,mid,L,R,t);
    if (R>mid) res+=get(tr[p][t].rc,mid+1,r,L,R,t);
    return res;
}
int main() {
    int CNT=0;
    scanf("%d",&m);
    for (int i=1;i<=m;i++) {
        cin>>opt[i];
        if (opt[i]=="set") {
            cin>>s[i]>>b[i];
            if (k[s[i]]) d[i]=k[s[i]];
            else d[i]=k[s[i]]=++CNT;
            int p=get(root[i-1][1],1,1e9,d[i],d[i],1);//注意上界是max_xi
            if (!p) root[i][0]=upd1(root[i-1][0],1,1e9,b[i],1);
            else {
                int x=upd1(root[i-1][0],1,1e9,p,-1);
                root[i][0]=upd1(x,1,1e9,b[i],1);
            }
            root[i][1]=upd2(root[i-1][1],1,1e9,d[i],b[i]);
        } else if (opt[i]=="remove") {
            cin>>s[i];
            if (k[s[i]]) d[i]=k[s[i]];
            else d[i]=k[s[i]]=++CNT;
            int p=get(root[i-1][1],1,1e9,d[i],d[i],1);
            if (p) root[i][0]=upd1(root[i-1][0],1,1e9,p,-1),root[i][1]=upd2(root[i-1][1],1,1e9,d[i],0);//亿些细节
            else root[i][0]=root[i-1][0],root[i][1]=root[i-1][1];
        } else if (opt[i]=="query") {
            cin>>s[i];
            if (k[s[i]]) d[i]=k[s[i]];
            else d[i]=k[s[i]]=++CNT;
            root[i][0]=root[i-1][0];//注意复制版本
            root[i][1]=root[i-1][1];
            int p=get(root[i][1],1,1e9,d[i],d[i],1);
            if (!p) {
                cout<<-1<<endl;
                continue;
            }
            int res=get(root[i][0],1,1e9,1,p-1,0);
            cout<<res<<endl;
        } else {
            cin>>e[i];
            root[i][0]=root[i-e[i]-1][0];
            root[i][1]=root[i-e[i]-1][1];
        }
    }
    return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# 题意

> 维护一个数据结构，支持以下几种操作：
> - `set ai xi`：设置任务 $a_i$ 的优先级为 $x_i$，如果该列表中没有出现则加入该任务。
> - `remove a_i`：删除该任务。
> - `query a_i`：求优先级比 $a_i$ 小的任务个数，如果没有则输出 $-1$。
> - `undo sum`：删除此次操作之前的 $sum$ 次操作。

# 分析

前三个操作是非常典型的平衡树操作，考虑使用平衡树或者动态开点线段树。

第四个带撤回，考虑使用可持久化数据结构。

本篇题解使用可持久化动态开点线段树解决。

维护两棵线段树，一棵维护区间和用于记录优先级，一棵维护某任务是否存在。

注意本题强制在线，其他的内容就是板子。

[AC 记录](https://codeforces.com/contest/916/submission/278211662)

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

namespace SegT
{
    struct node
    {
        int sum;
        node *lc, *rc;
        node() {memset(this, 0, sizeof *this);}
        void push_up() 
        {
            sum=0;
            if(lc) sum+=lc->sum;
            if(rc) sum+=rc->sum;
        }
    };

    #define lc(x) (x?x->lc:0)
    #define rc(x) (x?x->rc:0)
    #define mid ((l+r)>>1)
    #define lson x->lc, l, mid
    #define rson x->rc, mid+1, r

    void modify(node *pre, node *&x, int l, int r, int p, int v)
    {
        x=pre?new node(*pre):new node;
        if(l==r) return x->sum+=v, void();
        if(p<=mid) modify(lc(pre), lson, p, v);
        if(p>mid)  modify(rc(pre), rson, p, v);
        x->push_up();
    }

    int query(node *x, int l, int r, int L, int R)
    {
        if(!x) return 0;
        if(L<=l&&r<=R) return x->sum;
        int ret=0;
        if(L<=mid) ret+=query(lson, L, R);
        if(R>mid)  ret+=query(rson, L, R);
        return ret;
    }
}

namespace SegT2
{
    struct node
    {
        int v;
        node *lc, *rc;
        node() {memset(this, 0, sizeof *this);}
    };

    void build(node *&x, int l, int r)
    {
        x=new node;
        if(l==r) return;
        build(lson);
        build(rson);
    }

    void modify(node *pre, node *&x, int l, int r, int p, int v)
    {
        x=new node(*pre);
        if(l==r) return x->v=v, void();
        if(p<=mid) modify(pre->lc, lson, p, v);
        if(p>mid)  modify(pre->rc, rson, p, v);
    }

    int query(node *x, int l, int r, int p)
    {
        if(l==r) return x->v;
        if(p<=mid) return query(lson, p);
        if(p>mid)  return query(rson, p);
    }
}

unordered_map<string, int> ids;

SegT::node *rt[100005];
SegT2::node *exist[100005];

int main()
{
    ios::sync_with_stdio(0);
    int q, xi;
    const int n=1e9, m=1e5;
    cin>>q;
    string s, op;
    build(exist[0], 1, m);
    for(int i=1;i<=q;i++)
    {

        rt[i]=rt[i-1];
        exist[i]=exist[i-1];
        cin>>op;
        if(op[0]=='u')
        { 
            cin>>xi;
            rt[i]=rt[i-1-xi];
            exist[i]=exist[i-1-xi];
        }
        else
        {
            cin>>s;
            if(!ids.count(s)) ids[s]=ids.size()+1;
            int a=ids[s];
            if(op[0]=='s') 
            {
                cin>>xi;
                int va=query(exist[i], 1, m, a);
                if(va) modify(rt[i], rt[i], 1, n, va, -1);
                modify(exist[i], exist[i], 1, m, a, xi);
                modify(rt[i], rt[i], 1, n, xi, 1);
            }
            if(op[0]=='q') 
            {
                int ans=0;
                int va=query(exist[i], 1, m, a);
                if(va>1) ans=query(rt[i], 1, n, 1, va-1);
                if(!va) ans=-1;
                cout<<ans<<endl;
            }
            if(op[0]=='r') 
            {
                int va=query(exist[i], 1, m, a);
                if(!va) continue;
                modify(rt[i], rt[i], 1, n, va, -1);
                modify(exist[i], exist[i], 1, m, a, 0);
            }
        }
    }
}
```

---

## 作者：Akiyama_mzk (赞：0)

# Preface

## 前置芝士：主席树

安利[博客](https://www.luogu.com.cn/user/954640#article)与[大号](https://www.luogu.com.cn/user/954640#main)。

## 题意

你需要维护一个任务列表，有 $q$ 次操作，四种操作形如以下：

`set a x`：设置任务 $a$ 的优先级为 $x$，如果任务列表中没有 $a$ 则加进来。

`remove a`：将任务 $a$ 移除出列表。

`query a`：求出有多少个任务的优先级比 $a$ 小，如果 $a$ 不在列表里输出 $-1$。

`undo d`：撤销这次操作之前的 $d$ 个操作。

# Introduction

看到撤销操作想到持久化数据结构。

$query$ 维护一棵可持久化权值线段树，$set$ 操作维护一个可持久化数组（废话）。

我们需要先了解 [P3919 【模板】可持久化线段树 1（可持久化数组）](https://www.luogu.com.cn/problem/P3919)。

题面为在某个历史版本上修改某一个位置上的值，并访问某个历史版本上的某一位置的值。

主席树的基本思想就是只对进行修改的结点进行复制，以减少空间的消耗，让我们不必复制每个版本所有节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/doih9i5f.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

易得，每次添加的节点数为 $\log(n)$ 个，可持久化线段树有很多根，对于每一个根都可以构成一棵完整的线段树。

所以我们知道，主席树只会对部分节点进行复制，我们每一次想询问一个版本的线段树，就可以在那个版本的根构成的线段树中询问。

我们直接开一块内存池存新节点。编号为此时总节点数个数 $+1$。开结构体存节点编号。根要另外开个数组存。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
inline long long read(){
	long long x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(long long x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int n,m,dfn;
int root[1000001],a[1000001];
struct president_tree{
	struct node{
		int lson,rson,val;
	}t[25000001];
	void build(int &x,int l,int r){
		x=++dfn;
		if(l==r){
			t[x].val=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(t[x].lson,l,mid);
		build(t[x].rson,mid+1,r);
	}
	void update(int idx,int &id,int l,int r,int x,int d){
		id=++dfn;
		t[id]=t[idx];
		if(l==r){
			t[id].val=d;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			update(t[idx].lson,t[id].lson,l,mid,x,d);	
		}
		else{
			update(t[idx].rson,t[id].rson,mid+1,r,x,d);
		}
	}
	int query(int x,int l,int r,int pos){
		if(l==r){
			return t[x].val;
		}
		int mid=(l+r)>>1;
		if(pos<=mid){
			return query(t[x].lson,l,mid,pos);
		}
		else{
			return query(t[x].rson,mid+1,r,pos);
		}
	}
}tree;
signed main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	tree.build(root[0],1,n);
	for(int i=1;i<=m;i++){
		int loc=read();
		int op=read();
		if(op==1){
			int locate=read();
			int value=read();
			tree.update(root[loc],root[i],1,n,locate,value);
		}
		if(op==2){
			int locate=read();
			write(tree.query(root[loc],1,n,locate));
			printf("\n");
			root[i]=root[loc];
		}
	}
	return 0;
}
```
接下来讲讲 [P3834 【模板】可持久化线段树 2（可持久化权值线段树）](https://www.luogu.com.cn/problem/P3834)。

题面为在区间 $[l,r]$ 查询其区间内的第 $k$ 小值。

思想是每个位置都维护一个线段树，线段树的节点是值的范围，然后第 $i$ 个线段树中某个区间 $[x,y]$ 维护的是 $1$ 至 $i$ 的数字在 $[x,y]$ 范围内的个数。利用到了前缀和的思想。

建树时首先需要建一棵空的线段树，即最原始的主席树，此时主席树只含有一个空的节点，之后依次对原序列按某种顺序更新，将原序列加入到相应的位置。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline long long read(){
	long long x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(long long x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int n,m,a[200001],lsh[200001],root[200001],rnk[200001],dfn;
struct president_tree{
	struct node{
		int lson,rson,val,l,r;
	}t[25000001];
	void push_up(int x){
		t[x].val=t[t[x].lson].val+t[t[x].rson].val;
	}
	void build(int &x,int l,int r){
		x=++dfn;
		t[x].l=l;
		t[x].r=r;
		if(l==r){
			return;
		} 
		int mid=(l+r)>>1;
		build(t[x].lson,l,mid);
		build(t[x].rson,mid+1,r);
	}
	void update(int idx,int &id,int x){
		id=++dfn;
		t[id]=t[idx];
		if(t[id].l==t[id].r){
			t[id].val++;
			return;
		}
		if(x<=t[t[idx].lson].r){
			update(t[idx].lson,t[id].lson,x);
		}
		else{
			update(t[idx].rson,t[id].rson,x);
		}
		push_up(id);
	}
	int query(int idx,int id,int x){
		if(t[id].l==t[id].r){
			return t[id].l;
		}
		int lsize=t[t[id].lson].val-t[t[idx].lson].val;
		if(lsize>=x){
			return query(t[idx].lson,t[id].lson,x);
		}
		else{
			return query(t[idx].rson,t[id].rson,x-lsize);
		}
	}
}tree;
signed main(){
	n=read();
	m=read();
	tree.build(root[0],1,n);
	for(int i=1;i<=n;i++){
		a[i]=read();
		lsh[i]=a[i];
	}
	sort(lsh+1,lsh+1+n);
	int tot=unique(lsh+1,lsh+1+n)-lsh-1;
	for(int i=1;i<=n;i++){
		rnk[i]=upper_bound(lsh+1,lsh+1+tot,a[i])-lsh-1;
	}
 	for(int i=1;i<=n;i++){
 		tree.update(root[i-1],root[i],rnk[i]);
	}
	for(int i=1;i<=m;i++){
		int l=read();
		int r=read();
		int k=read();
		write(lsh[tree.query(root[l-1],root[r],k)]);
		printf("\n");
	}
	return 0;
}
```

因此，本题分别用两棵可持久化线段树实现即可（模板拼接）。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
	long long x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(long long x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
const int dacty=3e5+1;
const int range=1e9;
long long cnt,cntt,tot;
map<string,int> mp;
string op,x;
int n,m,a[300001],lsh[300001],root[300001],root1[300001],dfn;
struct president_tree{
	struct node{
		int lson,rson,l,r;
		long long val;
	}t[25*dacty],tr[25*dacty];
	void push_up(int x){
		t[x].val=t[t[x].lson].val+t[t[x].rson].val;
	}
	void update(int idx,int &id,int l,int r,int x,long long d){
		id=++dfn;
		t[id]=t[idx];
		if(l==r&&l==x){
			t[id].val+=d;
			return;
		}
		else if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			update(t[idx].lson,t[id].lson,l,mid,x,d);
		}
		else{
			update(t[idx].rson,t[id].rson,mid+1,r,x,d);
		}
		push_up(id);
	}
	void modify(int idx,int &id,int l,int r,int x,long long d){
		id=++cnt;
		tr[id]=tr[idx];
		tr[id].l=l;
		tr[id].r=r;
		if(l==r&&l==x){
			tr[id].val=d;
			return;
		}
		else if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			modify(tr[idx].lson,tr[id].lson,l,mid,x,d);
		}
		else{
			modify(tr[idx].rson,tr[id].rson,mid+1,r,x,d);
		}
	}
	void revise(int idx,int &id,int l,int r,int x,long long d){
		if(id<root[tot]){
			id=++dfn;
			t[id].l=l;
			t[id].r=r;
			t[id]=t[idx];
		}
		if(l==r&&l==x){
			t[id].val+=d;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			revise(t[idx].lson,t[id].lson,l,mid,x,d);
		}
		else{
			revise(t[idx].rson,t[id].rson,mid+1,r,x,d);
		}
		push_up(id);
	}
	int query(int x,int l,int r,int ll,int rr){
		if(l>=ll&&r<=rr){
			return t[x].val;
		}
		int mid=(l+r)>>1;
		int res=0;
		if(ll<=mid){
			res+=query(t[x].lson,l,mid,ll,rr);
		} 
		if(rr>=mid+1){
			res+=query(t[x].rson,mid+1,r,ll,rr);
		}
		return res;
	}
	int scepticism(int id,int l,int r,int x){
		if(!id){
			return -1;
		}
		if(l==r&&l==x){
			return tr[id].val;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			return scepticism(tr[id].lson,l,mid,x);
		}
		else{
			return scepticism(tr[id].rson,mid+1,r,x);
		}
	}
}tree;
signed main(){
	m=read();
	while(m--){
		++tot;
		cin>>op;
		if(op=="set"){
			cin>>x;
			int y=read();
			tree.update(root[tot-1],root[tot],0,range,y,1);
			int now=tree.scepticism(root1[tot-1],0,range,mp[x]);
			if(now!=-1){
				tree.revise(root[tot-1],root[tot],0,range,now,-1);
			}
			else if(!mp[x]){
				mp[x]=++cntt;
			}
			tree.modify(root1[tot-1],root1[tot],0,range,mp[x],y);
		}
		if(op=="remove"){
			cin>>x;
			int now=tree.scepticism(root1[tot-1],0,range,mp[x]);
			tree.update(root[tot-1],root[tot],0,range,now,-1);
			tree.modify(root1[tot-1],root1[tot],0,range,mp[x],-1);
		}
		if(op=="query"){
			cin>>x;
			root[tot]=root[tot-1];
			root1[tot]=root1[tot-1];
			int now=tree.scepticism(root1[tot],0,range,mp[x]);
			if(now==-1){
				write(-1);
				printf("\n");
				continue;
			}
			else if(!now){
				write(0);
				printf("\n");
				continue;
			}
			int pre=tree.query(root[tot],0,range,0,now);
			if(pre==1||pre==1){
				write(0);
				printf("\n");
			}
			else {
				write(tree.query(root[tot],0,range,0,now-1));
				printf("\n");
			}
		}
		if(op=="undo"){
			int y=read();
			root[tot]=root[tot-1-y];
			root1[tot]=root1[tot-1-y];
		}
	}
	return 0;
}
```

---

## 作者：ExplodingKonjac (赞：0)

### [【原题链接】](https://www.luogu.com.cn/problem/CF916D)

题解区好像没有可持久化 $\text{Trie}+\text{FHQ-Treap}$ 的题解。。

## 题目分析

每个字符串对应一个权值。有添加/修改操作、查询排名、撤销操作。

字符串查找？使用 $\text{Trie}$。查询排名？大力平衡树。

因为有撤销操作，所以要可持久化处理。假设当前为版本 $i$，撤销掉 $sum$ 次操作就是回退到版本 $i-sum-1$。

$\text{Trie}$ 的可持久化是很容易的，但是平衡树呢？

很多平衡树像 $\text{Splay, AVL}$ 都是通过旋转来保证平衡的，但这样也使得大多数平衡树不支持可持久化操作。

但是有一种平衡树叫做 $\text{FHQ-Treap}$，它使用了分裂和合并，而不是旋转来保证平衡。于是它支持可持久化。

## 可持久化 $\text{FHQ-Treap}$

首先您得了解一下 $\text{Treap}$。$\text{FHQ-Treap}$ 利用堆的性质以及随机附加权值保证了复杂度，但是操作不像传统的二叉查找树一样，而是借助 split 和 merge 实现。

### 节点的储存

```cpp
struct TreapNode
{
	int val; //保存的值
	int pri,cnt,siz; //附加权值、重复计数器、子树大小
	TreapNode *lc,*rc; //左右儿子
	TreapNode(int v): val(v),cnt(1),siz(1) // 构造函数
		{ pri=rand(),lc=rc=nullptr; }
}*rt;
typedef TreapNode *pNode
```


### 分裂：split

一般是将小于等于 $k$ 的分到一棵树中，大于 $k$ 的分到另一棵树中。当然也可以通过排名分裂（一般是在维护序列时），但这里不给出代码。

```cpp
void split(pNode i,int k,pNode &x,pNode &y)
{
	if(!i)	x=y=nullptr; //节点不存在
	else if(i->val<=k) //若小于等于k，该节点属于x
		x=i,split(i->rc,k,x->rc,y),pushup(x);
	else // 否则，该节点属于y
		y=i,split(i->lc,k,x,y->lc),pushup(y);
}
```

### 合并：merge

将两棵树 $x,\ y$ 合并为一棵，返回新树的根。合并要求 $x$ 中元素全部小于等于 $y$ 中元素。合并后的树的附加权值满足堆的性质，正是这里保证了复杂度。

这里的实现用了小根堆，当然大跟堆也没问题的。

```cpp
pNode merge(pNode x,pNode y)
{
	if(!x || !y)	return x?x:(y?y:nullptr); //有一棵为空或都为空，直接返回
	else if(x->pri<y->pri) //x附加权值小，x作为根
		return x->rc=merge(x->rc,y),pushup(x),x;
	else //否则y作为根
		return y->lc=merge(x,y->lc),pushup(y),y;
}
```

### 插入与删除：insert & remove

要找到权值为 $v$ 的节点，基本方法是先 $split(rt,v,x,z)$，再 $split(x,v-1,x,y)$，得到的 $y$ 的权值就是 $v$。

完成操作后记得把它们合并回去：$rt\gets merge(merge(x,y),z)$。

```cpp
void insert(int v)
{
	pNode x,y,z;split(rt,v,x,z),split(x,v-1,x,y);
	if(y)	y->cnt++,y->siz++; //如果存在，数量+1
	else	y=new TreapNode(v); //否则新建节点
	rt=merge(merge(x,y),z);
}
void remove(int v)
{
	pNode x,y,z;split(rt,v,x,z),split(x,v-1,x,y);
	if(y)
	{
		y->cnt--,y->siz--; //数量-1
		if(!y->cnt)	{ delete y;y=nullptr; }
		//删除掉空的节点
	}
	rt=merge(merge(x,y),z);
}
```
其它的操作如根据数值查排名、根据排名查数值、前驱后继等，操作和普通二叉搜索树一样，不再赘述。

### 支持可持久化

我们发现，真正修改的只有在 split 操作中，而且修改的只有一条链，所以可以直接复制原节点

我们将 split 函数内的 `x=i`、`y=i`，改为 `x=new TreapNode(*i)`、`y=new TreapNode(*i)` 即可。

## 代码实现

**请注意本题每输出一行后要 `fflush(stdout)` 清空输出缓存区，否则会 Idleness Limit Exceeded。**

这道题还是相当模板的。

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
  省略100多行的快读快写模板
  即下面的qin、qout
*/

int n;

class Trie
{
 private:
	struct TrieNode
	{
		int val;
		TrieNode *ch[26];
		TrieNode(): val(0)
			{ memset(ch,0,sizeof(ch)); }
	}*rt;
	typedef TrieNode *pNode;
 public:
	Trie(): rt(nullptr){}
	inline void copy(const Trie &t)	{ rt=t.rt; }
	void insert(const char *s,int x)
	{
		if(!rt)	rt=new TrieNode;
		else	rt=new TrieNode(*rt);
		pNode i=rt;char c;
		while(*s)
		{
			c=*(s++)-'a';
			if(!i->ch[c])	i->ch[c]=new TrieNode;
			else	i->ch[c]=new TrieNode(*i->ch[c]);
			i=i->ch[c];
		}
		i->val=x;
	}
	int query(const char *s)
	{
		pNode i=rt;
		while(*s)
		{
			if(!i)	return 0;
			i=i->ch[*(s++)-'a'];
		}
		return i?i->val:0;
	}
}tri[100005];

class Treap
{
 private:
	struct TreapNode
	{
		int val;
		int pri,cnt,siz;
		TreapNode *lc,*rc;
		TreapNode(int v): val(v),cnt(1),siz(1)
			{ pri=rand(),lc=rc=nullptr; }
	}*rt;
	typedef TreapNode *pNode;
	inline void pushup(pNode i)
	{
		i->siz=i->cnt;
		if(i->lc)	i->siz+=i->lc->siz;
		if(i->rc)	i->siz+=i->rc->siz;
	}
	void split(pNode i,int k,pNode &x,pNode &y)
	{
		if(!i)	x=y=nullptr;
		else if(i->val<=k)
			x=new TreapNode(*i),split(i->rc,k,x->rc,y),pushup(x);
		else
			y=new TreapNode(*i),split(i->lc,k,x,y->lc),pushup(y);
	}
	pNode merge(pNode x,pNode y)
	{
		if(!x || !y)	return x?x:(y?y:nullptr);
		else if(x->pri<y->pri)
			return x->rc=merge(x->rc,y),pushup(x),x;
		else
			return y->lc=merge(x,y->lc),pushup(y),y;
	}
 public:
	Treap(): rt(nullptr){}
	inline void copy(const Treap &t)	{ rt=t.rt; }
	void insert(int v)
	{
		pNode x,y,z;split(rt,v,x,z),split(x,v-1,x,y);
		if(y)	y->cnt++,y->siz++;
		else	y=new TreapNode(v);
		rt=merge(merge(x,y),z);
	}
	void remove(int v)
	{
		pNode x,y,z;split(rt,v,x,z),split(x,v-1,x,y);
		if(y)
		{
			y->cnt--,y->siz--;
			if(!y->cnt)	{ delete y;y=nullptr; }
		}
		rt=merge(merge(x,y),z);
	}
	int getRank(int v)
	{
		pNode i=rt;
		int res=1;
		while(i)
			if(v<=i->val)	i=i->lc;
			else	res+=(i->lc?i->lc->siz:0)+i->cnt,i=i->rc;
		return res;
	}
}trp[100005];

int main()
{
	srand(19491001);
	qin>>n;
	char opt[10],s[30];
	int x,y;
	for(int i=1;i<=n;i++)
	{
		tri[i].copy(tri[i-1]),trp[i].copy(trp[i-1]);
		qin>>opt;
		if(opt[0]=='s')
		{
			qin>>s>>x;
			trp[i].remove(tri[i].query(s));
			tri[i].insert(s,x),trp[i].insert(x);
		}
		else if(opt[0]=='r')
		{
			qin>>s;
			trp[i].remove(tri[i].query(s));
			tri[i].insert(s,0);
		}
		else if(opt[0]=='q')
		{
			qin>>s,y=tri[i].query(s);
			qout.writeln(y?(trp[i].getRank(y)-1):-1);
		}
		else
			qin>>x,tri[i].copy(tri[i-x-1]),trp[i].copy(trp[i-x-1]);
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：PragmaGCC (赞：0)

# 题目大意

您需要维护一个数据结构，支持以下操作：

- `set s x`  将字符串 $s$ 的权值设为 $x$ ，如果没有则加入 $s$ 。
- `remove s`  删除 $s$ 。
- `query s `  查询有多少个字符串的权值小于 $s$ 。如果 $s$ 不存在则输出 `-1`。
- `undo x` 撤销之前的 $x$ 次操作。

# 题解

一看到撤销就知道要可持久化。

首先用`map`将字符串映射为整数。

在没有`undo`操作的情况下，用数组维护权值，权值线段树进行查询即可。

加入`undo`后就将上面两个东西可持久化就可以了。

tips：不要混用`cin`和`puts`，会`ILE`。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
#define int long long
const int N = 1e5 + 5, INF = 1e9;
int n, id;
map<string, int> mp;
int getid(string s) {
    if (mp.count(s)) return mp[s];
    else return mp[s] = ++id;
}
struct node {
    int ls, rs;
    int sum;
} t[N<<7];
int rt1[N<<1], rt2[N<<1], tot;
#define ls(k) t[k].ls
#define rs(k) t[k].rs
void pushup(int k) { t[k].sum = t[ls(k)].sum + t[rs(k)].sum; }
int update(int k, int l, int r, int x, int v) {
    int p = ++tot, mid = l + r >> 1;
    t[p] = t[k];
    if (l == r) {
        t[p].sum += v;
        return p;
    }
    if (x <= mid) ls(p) = update(ls(k), l, mid, x, v);
    else rs(p) = update(rs(k), mid+1, r, x, v);
    pushup(p);
    return p;
}
int query(int k, int l, int r, int ql, int qr) {
    if (l >= ql && r <= qr) return t[k].sum;
    int mid = l + r >> 1, res = 0;
    if (ql <= mid) res += query(ls(k), l, mid, ql, qr);
    if (qr > mid) res += query(rs(k), mid+1, r, ql, qr);
    // printf("rres=%d\n", res);
    return res;
}
string s, op;
signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin>>n;
    for (int i=1, num, x; i<=n; i++) {
        cin>>op;
        rt1[i] = rt1[i-1], rt2[i] = rt2[i-1];
        if (op[0] == 's') {
            cin>>s>>num;
            x = getid(s);
            int res = query(rt1[i], 1, INF, x, x);
            if (res) rt2[i] = update(rt2[i], 1, INF, res, -1);
            rt2[i] = update(rt2[i], 1, INF, num, 1);
            rt1[i] = update(rt1[i], 1, INF, x, num-res);
        } else if (op[0] == 'r') {
            cin>>s;
            x = getid(s);
            int res = query(rt1[i], 1, INF, x, x);
            rt1[i] = update(rt1[i], 1, INF, x, -res);
            if (res) rt2[i] = update(rt2[i], 1, INF, res, -1);
        } else if (op[0] == 'q') {
            cin>>s;
            x = getid(s);
            int res = query(rt1[i], 1, INF, x, x);
            if (res == 0) cout<<"-1"<<endl;
            else if (res == 1) cout<<"0"<<endl;
            else cout<<query(rt2[i], 1, INF, 1, res-1)<<endl;
        } else {
            cin>>num;
            rt1[i] = rt1[i-num-1], rt2[i] = rt2[i-num-1];
        }
        cout<<flush;
    }
    return 0;
}
```



---

## 作者：shao0320 (赞：0)

#### CF916D

写一个数据结构支持一下几种操作

1、$set\space a\space  x$:将字符串$a$插入集合，将其权值置为$x$。

2、$remove$ $a$:将字符串$a$移出集合

3、$query \space a$:询问集合中有几个字符串权值小于$a$的权值

4、$Undo \space x$撤销前$x$步操作。

看到$Undo$操作，考虑拿主席树维护。

字符串实际上是没用的，只需要拿$map$搞个映射就可以把字符串转化成整数的。

考虑没有$Undo$操作，对于一个字符串$a$，我们只需拿一个数组维护每个字符串的权值，并且用一棵权值线段树维护每个权值有多少个字符串即可。

考虑有$Undo$操作，容易想到把权值线段树改为主席树。

但我们发现字符串权值也需要支持可持久化，因此拿另外一棵线段树维护每个时刻每个字符串权值即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define N 10000005
#define MAXN 100005
#define MAXS 1000000005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
struct Trump_Tree
{
	int rt[N],lc[N],rc[N],cnt,sum[N];
	int modify(int l,int r,int k,int x,int val)
	{
		int u=++cnt,mid=(l+r)>>1;lc[u]=lc[k];rc[u]=rc[k];
		if(l==r){sum[u]=max(0,sum[k]+val);return u;}
		if(x<=mid)lc[u]=modify(l,mid,lc[k],x,val);
		else rc[u]=modify(mid+1,r,rc[k],x,val);
		sum[u]=sum[lc[u]]+sum[rc[u]];
		return u;
	}
	int query(int l,int r,int k,int x,int y)
	{
		if(l>=x&&r<=y)return sum[k];
		int mid=(l+r)>>1,res=0;
		if(x<=mid)res+=query(l,mid,lc[k],x,y);
		if(y>mid)res+=query(mid+1,r,rc[k],x,y);
		return res;
	}
	void Undo(int now,int lst){rt[now]=rt[lst];}
}S;
struct node
{
	int rt[N],lc[N],rc[N],v[N],cnt;
	int modify(int l,int r,int k,int x,int val)
	{
		int u=++cnt,mid=(l+r)>>1;lc[u]=lc[k];rc[u]=rc[k];
		if(l==r){v[u]=val;return u;}
		if(x<=mid)lc[u]=modify(l,mid,lc[k],x,val);
		else rc[u]=modify(mid+1,r,rc[k],x,val);
		return u;
	}
	int query(int l,int r,int k,int x)
	{
		if(l==r)return v[k];
		int mid=(l+r)>>1;
		if(x<=mid)return query(l,mid,lc[k],x);
		else return query(mid+1,r,rc[k],x);
	}
	void Undo(int now,int lst){rt[now]=rt[lst];}
}T;
map<string,int>mp;
string opt,x;
int tot,beS[N],beT[N],allS,allT;
int main()
{
	//freopen("A.out","w",stdout);
	int q;cin>>q;
	for(int i=1;i<=q;i++)
	{
		int tmp;cin>>opt;
		beS[i]=allS;beT[i]=allT;
		if(opt[0]=='u')
		{
			cin>>tmp;allS++;allT++;
			T.Undo(allT,beT[i-tmp]);
			S.Undo(allS,beS[i-tmp]);
			continue;
		}
		cin>>x;
		if(mp[x]==0)mp[x]=++tot;
		int pos=mp[x];
		if(opt[0]=='s')
		{
			cin>>tmp;
			int xx=T.query(1,MAXN,T.rt[allT],pos);
			if(xx){allS++;S.rt[allS]=S.modify(1,MAXS,S.rt[allS-1],xx,-1);}
			allS++;S.rt[allS]=S.modify(1,MAXS,S.rt[allS-1],tmp,1);
			allT++;T.rt[allT]=T.modify(1,MAXN,T.rt[allT-1],pos,tmp);
		}
		else if(opt[0]=='q')
		{
			int xx=T.query(1,MAXN,T.rt[allT],pos);
			if(xx==1){puts("0");continue;}
			printf("%d\n",xx==0?-1:S.query(1,MAXS,S.rt[allS],1,xx-1));
		}
		else if(opt[0]=='r')
		{
			int xx=T.query(1,MAXN,T.rt[allT],pos);
			if(!xx)continue;
			allT++;T.rt[allT]=T.modify(1,MAXN,T.rt[allT-1],pos,0);
			allS++;S.rt[allS]=S.modify(1,MAXS,S.rt[allS-1],xx,-1);
		}
	}
	return 0;
}
```



---

