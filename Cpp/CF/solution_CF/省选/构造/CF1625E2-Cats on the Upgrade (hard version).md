# Cats on the Upgrade (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the easy and the hard versions are removal queries, they are present only in the hard version.

"Interplanetary Software, Inc." together with "Robots of Cydonia, Ltd." has developed and released robot cats. These electronic pets can meow, catch mice and entertain the owner in various ways.

The developers from "Interplanetary Software, Inc." have recently decided to release a software update for these robots. After the update, the cats must solve the problems about bracket sequences. One of the problems is described below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1625E2/ad865cfdf37d1aee9e7ac138cc3da0f92a8cbe90.png)First, we need to learn a bit of bracket sequence theory. Consider the strings that contain characters "(", ")" and ".". Call a string regular bracket sequence (RBS), if it can be transformed to an empty string by one or more operations of removing either single "." characters, or a continuous substring "()". For instance, the string "(()(.))" is an RBS, as it can be transformed to an empty string with the following sequence of removals:

 "(()(.))" $ \rightarrow $ "(()())" $ \rightarrow $ "(())" $ \rightarrow $ "()" $ \rightarrow $ "". We got an empty string, so the initial string was an RBS. At the same time, the string ")(" is not an RBS, as it is not possible to apply such removal operations to it.

An RBS is simple if this RBS is not empty, doesn't start with ".", and doesn't end with ".".

Denote the substring of the string $ s $ as its sequential subsegment. In particular, $ s[l\dots r] = s_ls_{l+1}\dots s_r $ , where $ s_i $ is the $ i $ -th character of the string $ s $ .

Now, move on to the problem statement itself. You are given a string $ s $ , initially consisting of characters "(" and ")". You need to answer the following queries:

1. Given two indices, $ l $ and $ r $ ( $ 1 \le l < r \le n $ ). It's guaranteed that the $ l $ -th character is equal to "(", the $ r $ -th character is equal to ")", and the characters between them are equal to ".". Then the $ l $ -th and the $ r $ -th characters must be set to ".".
2. Given two indices, $ l $ and $ r $ ( $ 1 \le l < r \le n $ ), and it's guaranteed that the substring $ s[l\dots r] $ is a simple RBS. You need to find the number of substrings in $ s[l\dots r] $ such that they are simple RBS. In other words, find the number of index pairs $ i $ , $ j $ such that $ l \le i < j \le r $ and $ s[i\dots j] $ is a simple RBS.

You are an employee in "Interplanetary Software, Inc." and you were given the task to teach the cats to solve the problem above, after the update.

## 说明/提示

Consider the example test case.

The answer to the first query is $ 3 $ , as there are three suitable substrings: $ s[3\dots6] $ , $ s[3\dots4] $ and $ s[5\dots6] $ .

The answer to the second query is $ 4 $ . The substrings are $ s[3\dots6] $ , $ s[3\dots4] $ , $ s[5\dots6] $ and $ s[2\dots7] $ .

After the third query, the string becomes ")(..())()".

The answer to the fourth query is $ 2 $ . The substrings are $ s[5\dots6] $ and $ s[2\dots7] $ . Note that $ s[3\dots6] $ is not a simple RBS anymore, as it starts with ".".

The answer to the fifth query is $ 4 $ . The substrings are $ s[5\dots6] $ , $ s[2\dots7] $ , $ s[8\dots9] $ and $ s[2\dots9] $ .

After the sixth query, the string becomes ")(....)()".

After the seventh query, the string becomes ")......()".

The answer to the eighth query is $ 1 $ . The substring is $ s[8\dots9] $ .

## 样例 #1

### 输入

```
9 8
)(()())()
2 3 6
2 2 7
1 3 4
2 2 7
2 2 9
1 5 6
1 2 7
2 8 9```

### 输出

```
3
4
2
4
1```

# 题解

## 作者：suxxsfe (赞：10)

我的博客：https://www.cnblogs.com/suxxsfe/p/15907152.html  

https://www.luogu.com.cn/problem/CF1625E2  

考虑把括号序列对应的树形结构建出来（按照在串中出现的顺序，给一个点所有儿子也定一个顺序）  
设 $u$ 有 $son_u$ 个儿子，则如果不考虑只取某个儿子中的一部分作为一个合法字串的情况（也就是必须取某几个连续的儿子），那么方案数是 $f_u=\dfrac{son_u\cdot (son_u+1)}{2}$  
再加上只取某个儿子的一部分的情况，则 $u$ 对应的答案就是 $\sum_{x\in \operatorname{subtree}(u)} f_x$  
那么整个询问就是求一段连续的儿子的子树 $f$ 值和，若共有 $p$ 个儿子，就在加上 $\frac{p*(p+1)}{2}$  

修改的时候对 $f$ 的影响只体现在修改点的父亲上，放在 dfs 序上就变成了单点修改区间查询，树状数组即可  
考虑询问时如何确定两个兄弟节点之间有多少节点（就是求上面的 $p$）  
对每个结点再开一个树状数组，大小为儿子个数，一开始每个儿子处都插入 $1$，每删掉一个儿子就把它在父亲的树状数组中的位置标成 $0$，区间查询即可  

如果把维护 $f$ 的树状数组换成线段树来支持区间赋值为 $0$，这个做法可以做修改时 $s[l\cdots r]$ 中间不保证全为 `.` 的情况  

```cpp  
#define N 300006
#define M 600006
struct Graph{
	int fir[N],nex[M],to[M],tot;
	inline void add(int u,int v){
		to[++tot]=v;
		nex[tot]=fir[u];fir[u]=tot;
	}
	inline void clear(){std::memset(fir,0,sizeof fir);tot=0;}
}G;
int n,m;
char s[N];
int stack[N],top;
int left[N],right[N];
int L[N],R[N],id[N],tot;
void build(int u,int l,int r){
	for(int i=l+1;i<r;i++)if(right[i]){
		G.add(u,++tot);
		L[tot]=i;R[tot]=right[i];id[i]=id[right[i]]=tot;
		build(tot,i,right[i]);
		i=right[i];
	}
}
struct BIT{
	int n;
	long long *tree;
	inline void init(int size){n=size;tree=new long long[size+1];std::memset(tree,0,(size+1)*sizeof tree[0]);}
	#define lowbit(x) (x&(-x))
	inline void add(int pos,long long k){for(;pos<=n;pos+=lowbit(pos)) tree[pos]+=k;}
	inline long long ask(int pos){
		long long ret=0;
		for(;pos;pos-=lowbit(pos)) ret+=tree[pos];
		return ret;
	}
	#undef lowbit
}S,T[N];
int dfn[N],dfscnt,end[N];
int num[N],son[N],fa[N];
void dfs(int u){
	dfn[u]=++dfscnt;
	for(int i=G.fir[u];i;i=G.nex[i]) num[G.to[i]]=++son[u],fa[G.to[i]]=u,dfs(G.to[i]);
	end[u]=dfscnt;
	S.add(dfn[u],(long long)son[u]*(son[u]+1)/2);
	T[u].init(son[u]);
	for(int i=G.fir[u];i;i=G.nex[i]) T[u].add(num[G.to[i]],1);
}
int main(){
	n=read();m=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='(') stack[++top]=i;
		else if(s[i]==')'&&top) left[i]=stack[top],right[stack[top--]]=i;
	}
	tot=1;//root=1
	for(int i=1;i<=n;i++)if(right[i]){
		G.add(1,++tot);
		L[tot]=i;R[tot]=right[i];id[i]=id[right[i]]=tot;
		build(tot,i,right[i]);i=right[i];
	}
	S.init(tot);
	dfs(1);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1){
			op=fa[id[l]];
			S.add(dfn[op],(long long)son[op]*(son[op]-1)/2-(long long)son[op]*(son[op]+1)/2);
			son[op]--;
			T[op].add(num[id[l]],-1);
		}
		else{
			l=id[l];r=id[r];op=fa[l];
			long long numl=T[op].ask(num[l]),numr=T[op].ask(num[r]);
			printf("		%lld\n",S.ask(end[l])-S.ask(dfn[r]-1)+(long long)(numl-numr+1)*(numl-numr+2)/2);
		}
	}
	return 0;
}
```

---

## 作者：RainFestival (赞：3)

$\rm rating = \color{red}2800$ 为啥这么高？

我们先把括号序列极长的能匹配括号子串拿出来，按照如下的方法建立一棵树。

对于这些子串，我们把它们去掉最左边最右边的括号，结果会剩余许多并列的括号子串，把他们的父亲设置为大的串。

记树上一个点 $x$ 的答案 $s_x=$ 只选择这个点的儿子节点的答案，$p_x$ 为 $x$ 的儿子数量，则 $s_x=\frac{p_x\times (p_x+1)}{2}$。

对于一个查询区间 $[l,r]$，可以把它划分成许多树上同层的节点，这个节点集合记为 $A$。

则答案就是：

所有以 $A$ 中点为祖先的点 $x$ 的 $s_x$ 的和 $ +\frac{|A|\times (|A|+1)}{2}$。

我们把树每个节点赋一个权值 $id$，使得这个权值的大小关系就是 $\tt dfs$ 序的大小关系，容易发现，对于一个表示区间 $[l,r]$ 的点 $x$，$id_x=l$ 就行了。记 $f_i$ 为 $id_x=i$ 的 $x$ 的 $s_x$，如果 $x$ 不存在，定义 $f_i=0$。

第一部分的权值 $=\sum\limits_{i=l}^{r} f_i$.

第二部分的权值是 $\frac{|A|\times (|A|+1)}{2}$,我们需要求出 $|A|$。

将每一层 $d$ 的所有节点 $x$ 按照 $id_x$ 递增的顺序放进一个数组 $g_d$ 里。

我们发现 $|A|=~(~g_d$ 中 $r$ 的排名 $-g_d$ 中 $l-1$ 的排名 $)$ 。

对于每一次修改，我们都要删除一个节点，容易发现，我们删除的是叶子节点。

删除节点时，假设这个节点为 $x$，他的父亲为 $y$，删除操作只会对 $s_y,p_y,f_{id_x},f_{id_y}$，还有 $x$ 那一层的 $g$。

然后我们对于 $f$ 用树状数组维护，$g$ 用平衡树维护。

然后就可以解决了。

**Something fun:** I was hacked because of "long long".

代码如下：

```cpp
#include<cstdio>
#include<vector>
#include<assert.h>
#include<random>
#include<stack>
std::mt19937 seed(*new int);
int getrd(int l,int r)
{
	std::uniform_int_distribution<int> rd(l,r);
	return rd(seed);
}
namespace node_pool
{
	struct node
	{
		int son[2],sz,s,p;
		node(int s=0){this->s=s,this->son[0]=this->son[1]=this->sz=this->p=0;}
	};
	node a[10000005];
	int cnt;
	int makenode(int s)
	{
		int x=++cnt;
		a[x]=node(s);
		a[x].sz=1;
		a[x].p=getrd(1,1000000000);
		return x;
	}
}
struct tree
{
	int rt;
	void pushup(int k)
	{
		using namespace node_pool;
		a[k].sz=a[a[k].son[0]].sz+a[a[k].son[1]].sz+1;
	}
	void split(int k,int &x,int &y,int val)
	{
		using namespace node_pool;
		if (!k) return x=y=0,void();
		if (a[k].s<=val) return x=k,split(a[k].son[1],a[x].son[1],y,val),pushup(x),void();
		else return y=k,split(a[k].son[0],x,a[y].son[0],val),pushup(y),void();
	}
	int merge(int x,int y)
	{
		using namespace node_pool;
		if (!x||!y) return x+y;
		if (a[x].p<a[y].p) return a[x].son[1]=merge(a[x].son[1],y),pushup(x),x;
		else return a[y].son[0]=merge(x,a[y].son[0]),pushup(y),y;
	}
	void insert(int val)
	{
		using namespace node_pool;
		int x=0,y=0;
		split(rt,x,y,val);
		rt=merge(x,merge(makenode(val),y));
	}
	void erase(int val)
	{
		using namespace node_pool;
		int x=0,y=0,z=0;
		split(rt,y,z,val);
		split(y,x,y,val-1);
		rt=merge(x,z);
	}
	int getrk(int k)
	{
		using namespace node_pool;
		int x=0,y=0;
		split(rt,x,y,k-1);
		int s=a[x].sz;
		rt=merge(x,y);
		return s;
	}
};
struct bit
{
	int n;
	long long s[500005];
	int lowbit(int x){return x&(-x);}
	void update(int k,long long w)
	{
		for (;k<=n;k=k+lowbit(k)) s[k]=s[k]+w;
	}
	long long ask(int k)
	{
		long long ans=0;
		for (;k>=1;k=k-lowbit(k)) ans=ans+s[k];
		return ans;
	}
	long long ask(int l,int r)
	{
		long long ans=0;
		if (l>1) ans=ans-ask(l-1);
		ans=ans+ask(r);
		return ans;
	}
	bit(int n=0){this->n=n;}
};
bit t0;
tree p[300005];
int tr(char x)
{
	if (x=='(') return 1;
	if (x==')') return -1;
	return 0;
}
int read()
{
	char ch=0;
	while (ch!='('&&ch!=')') ch=getchar();
	return ch;
}
int n,q,s[300005],fa[300005],son[300005],col[300005];
char f[300005];
std::vector<int> a[300005];
long long val[300005];
void add(int x,int y){a[x].push_back(y);}
long long calc(int x){return 1ll*x*(x+1)/2;}
void make(int l,int r)
{
	for (int i=l;i<=r;i++) s[i]=(i==l?0:s[i-1])+tr(f[i]);
	for (int i=l;i<=r;i++) if (tr(f[i])==1) p[s[i]].insert(i);
	std::stack<int> st;
	st.push(0);
	for (int i=l;i<=r;i++)
	{
		if (tr(f[i])==-1) st.pop();
		else if (tr(f[i])==1) add(st.top(),i),fa[i]=st.top(),++son[st.top()],st.push(i);
	}
	for (int i=l;i<=r;i++) val[i]=calc(son[i]),t0.update(i,val[i]);
}
void del(int k)
{
	p[s[k]].erase(k);
	if (fa[k]!=0)
	{
		--son[fa[k]];
		long long w=calc(son[fa[k]]);
		t0.update(fa[k],w-val[fa[k]]);
		val[fa[k]]=w;
	}
}
long long ask(int l,int r)
{
	long long ans=0;
	ans=ans+t0.ask(l,r);
	int d=s[l],cnt=p[d].getrk(r)-p[d].getrk(l-1);
	ans=ans+calc(cnt);
	return ans;
}
int main()
{
	scanf("%d%d",&n,&q);
	t0=bit(n);
	for (int i=1;i<=n;i++) f[i]=read();
	std::stack<int> st;
	for (int i=1;i<=n;i++)
		if (tr(f[i])==1) st.push(i);
		else if (tr(f[i])==-1)
		{
			if (st.empty()) continue;
			col[st.top()]=col[i]=1;
			st.pop();
		}
	int ll=1;
	for (int i=1;i<=n;i++)
		if (!col[i])
		{
			if (ll<=i-1) make(ll,i-1);
			ll=i+1;
		}
	if (ll<=n) make(ll,n);
	while (q--)
	{
		int opt,l,r;
		scanf("%d%d%d",&opt,&l,&r);
		if (opt==1) del(l);
		else if (opt==2) printf("%lld\n",ask(l,r));
	}
	return 0;
}
```

时间 $\tt 18.93s$，内存 $\tt 212.13MB$，代码长度 $\tt 3.61KB$。

---

## 作者：_Cheems (赞：1)

先说 $E1$ 的做法。

显然对每个右括号求出其对应的左括号下标 $lst_i$，$[lst_i,i]$ 是一段合法的括号子串，叫它们大串吧。

然后题目保证询问 $[l,r]$ 可拆成若干个大串，答案就是这些大串拼成的方案数 $+$ 大串内部的方案数。

这是个分治的形式，递推计算就好了。具体地，暴力找到 $[lst_i,i]$ 内部的大串然后计算，预处理前缀和即可。

因为每个大串至多被算一次，所以复杂度 $O(n)$。

接着是 $E2$ 的做法。

容易发现分治的过程呈树状。令 $f_u$ 表示 $[lst_u,u]$ 对应的大串内部方案数，不包括 $u$ 本身。$son_u$ 是 $u$ 儿子集合。有转移 $f_u=\frac {son_u\times(son_u+1)}2+\sum\limits_{v\in son_u} f_v$。

那么修改是删除叶子，查询是求两个兄弟节点构成区间的方案数。

但是发现这玩意不好维护啊，如果树剖维护 $f$，那查询怎么办？

由于一次修改至多改变一个 $son_u$ 是个很强的限制，所以将 $f$ 展开，化成对 $son$ 求和的形式方便处理。对于子树内节点 $v$，$f_u=\sum \frac{son_v\times(son_v+1)}2$。

用树状数组，修改操作是单点改，查询 $f_u$ 是区间和。最后还要维护兄弟节点间有多少节点，再开个树状数组统计即可。

复杂度 $O(n\log n)$。

总结：主要难度在转化成树上问题、以及树上信息的维护，需要一定计数技巧。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;
int n, q, lst[N], nxt[N], stk[N], tp, opt, l, r;
int son[N], dfn[N], df, ed[N], _dfn[N], _df, fa[N], br[N];
char c[N];
vector<int> to[N];

struct BIT{
	int t[N];
	inline void init() {memset(t, 0, sizeof t);}
	inline void upd(int a, int k) {for(; a < N; a += a & -a) t[a] += k;}
	inline int qry(int a) {int res = 0; for(; a; a -= a & -a) res += t[a]; return res;}
	inline int fid(int l, int r) {if(l > r) return 0; return qry(r) - qry(l - 1);}
}A, B;
inline void dfs(int u){
	dfn[u] = ++df;
	for(auto v : to[u]) ++son[u], A.upd(_dfn[v] = ++_df, 1);
	for(auto v : to[u])	fa[v] = u, br[v] = df + 1, dfs(v);
	ed[u] = df, B.upd(dfn[u], son[u] * (son[u] + 1) / 2); 
}
signed main(){
	scanf("%lld%lld%s", &n, &q, c + 1);
	for(int i = 1; i <= n; ++i)
		if(c[i] == '(') stk[++tp] = i;
		else if(tp){
			lst[i] = stk[tp--], nxt[lst[i]] = i;
			int j = i - 1;
			while(j > lst[i]) to[i].push_back(j), j = lst[j] - 1;
			reverse(to[i].begin(), to[i].end());
		}
	for(int i = n, p = n + 1; i; --i) if(i <= p && lst[i]) p = lst[i], to[n + 1].push_back(i);
	reverse(to[n + 1].begin(), to[n + 1].end());
	dfs(n + 1);
	
	while(q--){
		scanf("%lld%lld%lld", &opt, &l, &r);
		if(opt == 1){
			A.upd(_dfn[r], -1);
			B.upd(dfn[fa[r]], son[fa[r]] * (son[fa[r]] - 1) / 2 - son[fa[r]] * (son[fa[r]] + 1) / 2), --son[fa[r]];
		}
		else{
			int res = B.fid(br[nxt[l]], ed[r]), cnt = A.fid(_dfn[nxt[l]], _dfn[r]);
			res += cnt * (cnt + 1) / 2;
			printf("%lld\n", res);
		}
	}
	return 0;
} 
```

---

## 作者：lory1608 (赞：1)

非常巧妙的一道题目。

首先考虑easy version，发现我们每次询问都是对于一个**合法的括号序列**来进行操作。

那么我们可以建立出括号树，**注意有些部分的括号并不合法，需要去除掉**。

对于一次询问，我们考虑一个括号区间所在的位置一定是树上点 $u$ 所在子树儿子的一个连续段（如果我们按照从左到右的顺序从小到大安排对应的括号的情况下）。

那么我们先DP出一个子树的贡献和，这部分是很简单的。

然后对于每个点维护一个树状数组维护他的儿子的贡献和。

每次对于一个询问 $[l,r]$ ，我们先定位，然后找出他们的父亲，在父亲的对应儿子的`vector`上二分出这两个点对应的编号，然后差分一下就行了。

复杂度 $O((n+q)\log n)$ 。

当然，对于easy version，前缀和即可。

现在想来其实不用二分，只有对每一个点 $u$ 维护一个标号，表示他在父亲的儿子中的编号即可。

这样复杂度 $O(n+q)$ 。

对于hard version，每次删除一个叶子结点。

显然他不仅会对他的父亲有贡献（删去这个点的贡献），而且还会对整条链产生影响，我们额外再用一个树状数组维护即可（**链加单点查可以做到**  $O(n\log n)$）。

这样复杂度就是 $O((n+q)\log n)$ 。

在打的时候，我把二分的上界写错了，然后一直调不出来。

我好想不太会官方题解中的 $O((n+q)\sqrt n)$ 的做法。

bouns：如果删除的是一对匹配的括号对，而不是中间全空的括号对怎么做？

---

## 作者：int08 (赞：0)

## 前言
不看特殊条件直接开做，就得到了全场最劣的复杂度。
# Solution
### E1

看到括号序列的一个固定考虑方向是考虑树形结构。

然后根据括号序列建出对应的树：也就是 `(` 就进入一个新的儿子，`)` 就回溯。并记录一个数组 $a_i$ 表示考虑完字符串的前 $i$ 项之后当且位于树上哪个结点。

关于整个序列不一定匹配，有两种解决方案：一是在前面手动补充一些 `(`，二是如果栈空了还在回溯就手动给栈里加一个新的元素，具体详见代码：

```cpp
a[0]=cnt=1;sta.push(1);
for(auto x:s)
{
	if(x=='(') a[++i]=++cnt,sta.push(cnt);
	else
	{
		sta.pop();
		if(sta.empty()) sta.push(++cnt);
		a[++i]=sta.top();
	}
}
```

建完了树之后发现一个重要性质：$[l,r]$ 是合法括号序列的充要条件是 $a_{l-1}=a_r$，证明略。

于是询问变成了 $[x-1,y]$ 之间有多少 $l,r(l<r)$ 满足 $a_l=a_r$，这是经典的数颜色问题，莫队即可。

正解（口胡）：发现条件里的保证 $[l,r]$ 是合法括号串，于是在树上去过的结点形如一个子树中的一部分，而且除根之外的节点在询问区间外不会再去，于是把贡献挂在最后一次出现的位置，计算一下根的贡献即可。

### E2

加上了修改，怎么办？

发现修改的条件也很厉害，如果挪到树上，由于中间全是 `.`，换句话说它只删去树的叶子，不影响树的整体结构。

于是每次修改形如删去 $a_l,a_r$ 的颜色（也就是改成不重复的极大值）。

考虑带修莫队，就好了，复杂度 $O(n^{\frac{5}{3}})$。

另外有一个细节：发现如果 $s_{l-1}$ 是 `.`，以 $l$ 为起点的字符串就爆炸了，所以要把端点挪到 $l$ 往前的第一个非 `.` 字符才对。

## AC Code
我觉得我的带修莫队写得太丑了，就不放了。

# The End.

---

