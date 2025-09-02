# May Holidays

## 题目描述

It's May in Flatland, and there are $ m $ days in this month. Despite the fact that May Holidays are canceled long time ago, employees of some software company still have a habit of taking short or long vacations in May.

Of course, not all managers of the company like this. There are $ n $ employees in the company that form a tree-like structure of subordination: each employee has a unique integer id $ i $ between $ 1 $ and $ n $ , and each employee with id $ i $ (except the head manager whose id is 1) has exactly one direct manager with id $ p_i $ . The structure of subordination is not cyclic, i.e. if we start moving from any employee to his direct manager, then we will eventually reach the head manager. We define that an employee $ u $ is a subordinate of an employee $ v $ , if $ v $ is a direct manager of $ u $ , or the direct manager of $ u $ is a subordinate of $ v $ . Let $ s_i $ be the number of subordinates the $ i $ -th employee has (for example, $ s_1 = n - 1 $ , because all employees except himself are subordinates of the head manager).

Each employee $ i $ has a bearing limit of $ t_i $ , which is an integer between $ 0 $ and $ s_i $ . It denotes the maximum number of the subordinates of the $ i $ -th employee being on vacation at the same moment that he can bear. If at some moment strictly more than $ t_i $ subordinates of the $ i $ -th employee are on vacation, and the $ i $ -th employee himself is not on a vacation, he becomes displeased.

In each of the $ m $ days of May exactly one event of the following two types happens: either one employee leaves on a vacation at the beginning of the day, or one employee returns from a vacation in the beginning of the day. You know the sequence of events in the following $ m $ days. Your task is to compute for each of the $ m $ days the number of displeased employees on that day.

## 说明/提示

In the first sample test after employee with id 2 leaves for a vacation at the first day, the head manager with id 1 becomes displeased as he does not want any of his subordinates to go for a vacation. At the fourth day employee with id 5 becomes displeased as his last remaining employee with id 7 leaves for a vacation. At the fifth day employee with id 2 returns from the vacation, but it does not affect the number of displeased employees as the employees 5 and 1 are still displeased. At the sixth day employee with id 3 returns back from the vacation, preventing the employee with id 5 from being displeased and at the last day the head manager with id 1 leaves for a vacation, leaving the company without the displeased people at all.

## 样例 #1

### 输入

```
7 8
4 5 1 1 5 5
0 0 0 1 2 0 0
2 6 3 7 -2 4 -3 1
```

### 输出

```
1 1 1 2 2 2 1 0
```

## 样例 #2

### 输入

```
5 6
1 2 3 4
4 0 0 1 0
1 5 2 3 -5 -1
```

### 输出

```
0 2 1 0 0 0
```

# 题解

## 作者：Owen_codeisking (赞：7)

一道小清新数据结构题。

此题 $\text{std}$ 用的是 $O(n\sqrt n)$ 的虚树+询问分块，我提供一个好写常数又小的 $O(n\sqrt n\log n)$ 的分块做法。（感谢 foreverlasting 提供做法）

做法跟 [【集训队作业2018】Simple Tree](http://uoj.ac/problem/435) 有点像。

我们先对 $\text{dfs}$ 序分块，然后每个块维护整体加标记 $\text{add}$ 和 $\text{sum}[i]$，我们先将每个点都减去 $t_i$，这样的话我们只需要统计一段区间内 $>0$ 的个数。树剖以后，我们每次加的权值一定是 $\pm 1$，所以整块的指针也只会移动 $1$ 次，零散的部分暴力更新。

还有就是一些细节，比如 $\text{sum}[i]$ 要开到 $2n$ 之类的。注意不要 $\text{MLE}$。

时间 $O(n\sqrt n\log n)$，空间 $O(n\sqrt n)$。

$\text{Code\ Below:}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int B=500;
int n,m,a[maxn],_a[maxn],pos[maxn],L[maxn],R[maxn],add[maxn/B+10],sum[maxn/B+10][maxn<<1],head[maxn],to[maxn],nxt[maxn],tot,ans;
int top[maxn],dep[maxn],siz[maxn],son[maxn],fa[maxn],id[maxn],mp[maxn],tim; bool col[maxn];
inline void addedge(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs1(int x,int f)
{
	siz[x]=1,fa[x]=f,dep[x]=dep[f]+1;
	int maxson=-1;
	for(int i=head[x],y;i;i=nxt[i])
		if((y=to[i]) && y!=f)
		{
			dfs1(y,x),siz[x]+=siz[y];
			if(siz[y]>maxson)
				maxson=siz[y],son[x]=y;
		}
}
void dfs2(int x,int topf)
{
	id[x]=++tim,mp[tim]=x,top[x]=topf;
	if(son[x]) dfs2(son[x],topf);
	for(int i=head[x],y;i;i=nxt[i])
		if((y=to[i]) && y!=fa[x] && y!=son[x])
			dfs2(y,y);
}
inline void change(int x,int y)
{
	col[x]^=1;
	if(a[x]>=n+1-add[pos[x]]) ans-=y;
	sum[pos[x]][a[x]]-=y;
}
inline void modify(int l,int r,int v)
{
	for(int i=l,p=pos[i];i<=r;i++)
	{
		if(!col[i] && a[i]>=n+1-add[p]) ans--;
		if(!col[i]) sum[p][a[i]]--;
		a[i]+=v;
		if(!col[i]) sum[p][a[i]]++;
		if(!col[i] && a[i]>=n+1-add[p]) ans++;
	}
}
inline void update(int l,int r,int v)
{
	int p=pos[l],q=pos[r];
	if(p==q) { modify(l,r,v); return; }
	modify(l,R[p],v),modify(L[q],r,v);
	for(int i=p+1;i<q;i++)
	{
		if(v==1) add[i]++,ans+=sum[i][n+1-add[i]];
		else ans-=sum[i][n+1-add[i]],add[i]--;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++)
		scanf("%d",&fa[i]),addedge(fa[i],i);
	for(int i=1;i<=n;i++) scanf("%d",&_a[i]);
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;i++)
	{
		pos[i]=(i-1)/B+1;
		if(pos[i]!=pos[i-1])
			L[pos[i]]=i,R[pos[i-1]]=i-1;
	}
	R[pos[n]]=n;
	for(int i=1;i<=n;i++) a[id[i]]=n-_a[i];
	for(int i=1;i<=n;i++) sum[pos[i]][a[i]]++;
	int x,y;
	while(m--)
	{
		scanf("%d",&x);
		y=(x>0)?1:-1,x=abs(x);
		change(id[x],y);
		for(;x;x=fa[top[x]])
			update(id[top[x]],id[x],y);
		printf("%d ",ans);
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：mrsrz (赞：6)

[可能更好的体验](https://mrsrz.github.io/2019/12/01/CF925E/)

提供一种时间复杂度 $O(n\sqrt n)$，空间复杂度 $O(n)$ 的在线分块做法。

~~虽然因为常数大了点跑不过 $O(n\sqrt n\log n)$ 的做法了呐不过空间完爆它哇~~

我们转化一下问题：

每次修改一个节点的颜色，相当于把它到根路径上的所有点的点权 $-1/+1$，然后把自己这个点本身的点权变为无穷大/变回来。然后询问树上点权为负的点的个数。

一个非常简单的思路是对树进行树链剖分后对 dfs 序进行分块，每个块里按节点的点权进行排序。

然后整个块 $+1/-1$ 操作直接打标记，答案二分更新。单点赋值和边界修改的话，暴力改然后重新排序即可。

设块大小为 $S$，那么单次修改的复杂度为 $O(S\log^2 n+\frac{n}{S}\log n)$，这个东西只能平衡到 $O(n\sqrt{n\log n}\log n)$，非常不优秀。

开始对其进行优化。

从边角的暴力修改开始。由于块内本身就排好序了，我们直接在那个排好序的数组里把要修改的数和不用修改的数拿出来，那么此时两个数组依然是有序的。而那些要修改的数，同时增加相同的值，其大小关系不变，仍然有序。然后就是将两个有序数组合并，归并即可。那么单次复杂度就是 $O(S)$。

此时我们已经将单次复杂度优化为 $O(S\log n+\frac{n}{S}\log n)$，可以平衡至 $O(n\sqrt n\log n)$。

开始对整块修改进行优化。我们发现，整块修改时，每次只会增减 $1$。再观察可以发现，本题点权的值域是 $O(n)$ 的，那么一个思路就是把答案扔桶里，每次移动一个位置，然后更新当前答案。这样确实把单次时间复杂度优化至了 $O(\frac n S)$，但其空间复杂度变为了 $O(\frac{n^2}S)$。

考虑如果是一个有序数组，为什么不能记录答案所在的那个点，然后暴力移动？因为会有重复，导致移动的复杂度是错误的。那么我们把重复的缩起来就好了嘛。就是对每个出现过的点权，再记录点权的出现次数，然后就可以记录一个位置，每次 $O(1)$ 移动了。

那么这里就和上面的边角暴力矛盾了：把点权缩起来，怎么知道哪些点要变化？事实上，我们并不关心变化的点的编号，而只想知道变化的点的点权。我们事先开一个桶，记录哪些点权要变化，这个点权有多少个数要变化。然后再扫描排好序的数组，把要变化的位置对应变化的量提取出来。这也是个有序的数组，然后就可以合并辣。注意合并的时候删掉出现次数为 $0$ 的，把点权相同的元素并成一个元素。这样的复杂度还是原来的复杂度。

至此，我们单次的时间复杂度优化至 $O(S\log n+\frac n S)$，总复杂度可平衡至 $O(n\sqrt{n\log n})$。

这玩意还不够优！

考虑利用树链剖分的性质。我们从上往下考虑。每次从重链的某处切换到另一条重链顶的时候，子树大小至少缩小一半。而这条重链长不超过子树大小。

对一条长度为 $k$ 的重链，我们对其进行一次操作的复杂度为 $O(S+\frac k S)$，如果仅就这个 $k$ 而言，其复杂度可以平衡至 $O(\sqrt k)$。

那我们如果对不同的重链，根据其重链长度，使用不同的块大小分块，那么单次操作的复杂度就是 $O(\sqrt n+\sqrt{\frac n 2}+\sqrt{\frac n 4}+\sqrt{\frac n 8}+\dots)=O(\sqrt n)$ 的。

所以总的时间复杂度 $O(n\sqrt n)$，空间复杂度 $O(n)$。

而上述空间复杂度 $O(n\sqrt n)$ 的做法虽然有更小的常数，但无法把那个 $\log$ 卡下来，因为按照上述分法，分成的块的个数是 $O(n)$ 的，你就需要 $O(n^2)$ 的空间复杂度，这显然不能接受。

## Code：

```cpp
#include<iostream>
#include<vector>
#include<cmath>
#include<utility>
#include<algorithm>
using namespace std;
const int N=1e5+5;
struct edge{
	int to,nxt;
}e[N];
bool col[N];
int n,m,fa[N],head[N],cnt,dfn[N],idx,top[N],sz[N],son[N],dep[N],bel[N],idfn[N],tail[N];
int t[N];
int all,blocks;
vector<int>tmp;
int tot[600005];
struct Block{
	int L,R,len,tag;
	vector<int>a;
	vector<pair<int,int> >b;
	int it,ans;
	void re(){
		tmp=a;
		sort(tmp.begin(),tmp.end());
		b.clear();
		int v=tmp[0],x=1;
		for(int i=1;i<tmp.size();++i)
		if(tmp[i]!=v)b.push_back(make_pair(v,x)),x=1,v=tmp[i];else ++x;
		b.push_back(make_pair(v,x));
		for(int i=1;i<b.size();++i)b[i].second+=b[i-1].second;
		it=upper_bound(b.begin(),b.end(),make_pair(-tag,0x3fffffff))-b.begin();
		ans=it?b[it-1].second:0;
	}
	void init(int l,int r){
		L=l,R=r;
		for(int i=l;i<=r;++i)a.push_back(t[idfn[i]]);
		re();
	}
	void _erase(int val){
		vector<pair<int,int> >::iterator pos=lower_bound(b.begin(),b.end(),make_pair(val,0));
		for(vector<pair<int,int> >::iterator i=pos+1;i<b.end();++i)--i->second;
		--pos->second;
		if((pos==b.begin()&&!pos->second)||pos->second==(pos-1)->second)b.erase(pos);
	}
	void _insert(int val){
		vector<pair<int,int> >::iterator pos=lower_bound(b.begin(),b.end(),make_pair(val,0));
		for(vector<pair<int,int> >::iterator i=pos;i<b.end();++i)++i->second;
		if(pos==b.end()||pos->first!=val){
			int ct=(pos==b.begin()?1:(pos-1)->second+1);
			b.insert(pos,make_pair(val,ct));
		}
	}
	void add(int id,int x){
		all-=ans;
		id=id-L;
		_erase(a[id]);
		_insert(a[id]+=x);
		it=upper_bound(b.begin(),b.end(),make_pair(-tag,0x3fffffff))-b.begin();
		ans=it?b[it-1].second:0;
		all+=ans;
	}
	void dec(int l,int r){
		all-=ans;
		l=max(l,L),r=min(r,R);
		if(L==l&&r==R){
			--tag;
			if(it<b.size()&&b[it].first+tag<=0)++it;
			ans=it?b[it-1].second:0;
			all+=ans;
			return;
		}else{
			static pair<int,int>t1[N],t2[N];int top1=0,top2=0;
			for(int i=l;i<=r;++i){
				int&x=a[i-L];
				++tot[200001+x];
				--x;
			}
			for(int i=b.size()-1;i;--i)b[i].second-=b[i-1].second;
			for(int i=0;i<b.size();++i)
			if(tot[200001+b[i].first]){
				int&x=tot[200001+b[i].first];
				t1[++top1]=make_pair(b[i].first-1,x);
				b[i].second-=x,x=0;
			}
			int it1=0,it2=1;
			while(it1<b.size()&&it2<=top1)
			if(b[it1].first==t1[it2].first){
				int x=b[it1].second+t1[it2].second;
				if(x)t2[++top2]=make_pair(b[it1].first,x);
				++it1,++it2;
			}else
			if(b[it1].first<t1[it2].first){
				int x=b[it1].second;
				if(x)t2[++top2]=make_pair(b[it1].first,x);
				++it1;
			}else{
				int x=t1[it2].second;
				if(x)t2[++top2]=make_pair(t1[it2].first,x);
				++it2;
			}
			while(it1<b.size()){
				int x=b[it1].second;
				if(x)t2[++top2]=make_pair(b[it1].first,x);
				++it1;
			}
			while(it2<=top1){
				int x=t1[it2].second;
				if(x)t2[++top2]=make_pair(t1[it2].first,x);
				++it2;
			}
			b.clear();
			for(int i=1;i<=top2;++i)t2[i].second+=t2[i-1].second,b.push_back(t2[i]);
			it=upper_bound(b.begin(),b.end(),make_pair(-tag,0x3fffffff))-b.begin();
			ans=it?b[it-1].second:0;
			all+=ans;
		}
	}
	void inc(int l,int r){
		all-=ans;
		l=max(l,L),r=min(r,R);
		if(L==l&&r==R){
			++tag;
			if(it&&b[it-1].first+tag>0)--it;
			ans=it?b[it-1].second:0;
			all+=ans;
			return;
		}else{
			static pair<int,int>t1[N],t2[N];int top1=0,top2=0;
			for(int i=l;i<=r;++i){
				int&x=a[i-L];
				++tot[200001+x];
				++x;
			}
			for(int i=b.size()-1;i;--i)b[i].second-=b[i-1].second;
			for(int i=0;i<b.size();++i)
			if(tot[200001+b[i].first]){
				int&x=tot[200001+b[i].first];
				t1[++top1]=make_pair(b[i].first+1,x);
				b[i].second-=x,x=0;
			}
			int it1=0,it2=1;
			while(it1<b.size()&&it2<=top1)
			if(b[it1].first==t1[it2].first){
				int x=b[it1].second+t1[it2].second;
				if(x)t2[++top2]=make_pair(b[it1].first,x);
				++it1,++it2;
			}else
			if(b[it1].first<t1[it2].first){
				int x=b[it1].second;
				if(x)t2[++top2]=make_pair(b[it1].first,x);
				++it1;
			}else{
				int x=t1[it2].second;
				if(x)t2[++top2]=make_pair(t1[it2].first,x);
				++it2;
			}
			while(it1<b.size()){
				int x=b[it1].second;
				if(x)t2[++top2]=make_pair(b[it1].first,x);
				++it1;
			}
			while(it2<=top1){
				int x=t1[it2].second;
				if(x)t2[++top2]=make_pair(t1[it2].first,x);
				++it2;
			}
			b.clear();
			for(int i=1;i<=top2;++i)t2[i].second+=t2[i-1].second,b.push_back(t2[i]);
			it=upper_bound(b.begin(),b.end(),make_pair(-tag,0x3fffffff))-b.begin();
			ans=it?b[it-1].second:0;
			all+=ans;
		}
	}
}G[N];
void dfs(int now){
	sz[now]=1,son[now]=0;
	for(int i=head[now];i;i=e[i].nxt){
		dep[e[i].to]=dep[now]+1;
		dfs(e[i].to);
		sz[now]+=sz[e[i].to];
		if(!son[now]||sz[son[now]]<sz[e[i].to])son[now]=e[i].to;
	}
}
void dfs2(int now){
	idfn[dfn[now]=++idx]=now;
	if(son[now])top[son[now]]=top[now],dfs2(son[now]);else tail[top[now]]=now;
	for(int i=head[now];i;i=e[i].nxt)
	if(e[i].to!=son[now])dfs2(top[e[i].to]=e[i].to);
	if(top[now]==now){
		int l=dfn[now],r=dfn[tail[now]],siz=0.7*sqrt(r-l+1);
		if(siz<1)siz=1;
		for(int i=l;i<=r;i+=siz){
			const int L=i,R=min(i+siz-1,r);
			G[++blocks].init(L,R);
			for(int j=L;j<=R;++j)bel[j]=blocks;
			all+=G[blocks].ans;
		}
	}
}
void erase(int x){
	int id=dfn[x];
	if(col[x])return;
	col[x]=1;
	G[bel[id]].add(id,100001);
	for(x=fa[x];x;x=fa[top[x]]){
		int L=dfn[top[x]],R=dfn[x];
		const int bL=bel[L],bR=bel[R];
		for(int i=bL;i<=bR;++i)G[i].dec(L,R);
	}
}
void add(int x){
	int id=dfn[x];
	if(!col[x])return;
	col[x]=0;
	G[bel[id]].add(id,-100001);
	for(x=fa[x];x;x=fa[top[x]]){
		int L=dfn[top[x]],R=dfn[x];
		const int bL=bel[L],bR=bel[R];
		for(int i=bL;i<=bR;++i)G[i].inc(L,R);
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=2;i<=n;++i){
		cin>>fa[i];
		e[++cnt]=(edge){i,head[fa[i]]},head[fa[i]]=cnt;
	}
	for(int i=1;i<=n;++i)cin>>t[i],++t[i];
	dfs(dep[1]=1);
	dfs2(top[1]=1);
	while(m--){
		int k;
		cin>>k;
		if(k>0)erase(k);else add(-k);
		cout<<all<<' ';
	}
	return 0;
}
```

---

## 作者：天命之路 (赞：4)

这里给出一个时间 $O(n\sqrt {n \log n})$ ，空间 $O(n)$ ，的做法，时间上介于正常树剖分块和神奇树剖分块之间，空间上没有问题。

转换一下题意，就是每次对于一条根节点到某个点的路径 $+1/-1$，并对该节点反色，并每次询问权值大于 $0$ 的白色点个数。

看到这道题的第一眼，就有一个 $O(nq)$ 的做法，然而过不去。

但注意到如果我们不做 $O(nq)$，而是找一个数 $B$，来做 $O(B^2)$，做 $\frac{q}{B}$ 次，那么总时间复杂度就是 $O(qB)$ 的。

这就是询问分块的思想。

考虑阈值 $B$，把每 $B$ 个询问分作一块。

如果对于每个询问继续暴力处理，时间复杂度依旧是 $O(B \times n \times \frac{n}{B}) = O(n^2)$。

但注意到 $B$ 个询问只涉及最多 $B$ 个点。

如果我们只考虑这 $B$ 个点，向上跳，我们至多只会修改 $O(B)$ 个点。

但这 $B$ 个点不一定成一棵树，所以我们要 **建虚树**。

建完虚树后，我们在虚树上跳，就至多会跳到 $O(B)$ 个点。

但询问分块的思路依旧要求我们对于每个点，$O(1)$ 修改信息。

而此时，每条虚边已经覆盖了原树上的一条链了，我们无法简单地按照暴力那样修改信息。

一个很重要的性质在于：**每条虚边在每个时刻，被加的值都是相同的**。

所以我们对于每条虚边 $(u,v)$ （其中 $u$ 是 $v$ 的祖先，都可以把这条边上的点权挂在 $v$ 上（不包括 $u$，否则会算重，并打一个 $add$ 标记。

考虑修改操作时怎么办。

先把挂在每个虚点上的点权从大到小排序。

注意到每次 $add$ 变化量为 1。

对每个虚点记录一个指针 $poi$，表示 $poi$ 及其前面的都 $>0$。

如果点权互不相同，$poi$ 至多移动一位。

而点权相同时可以去重，在点权外额外记录出现次数。

这样单次修改复杂度就是 $O(1)$ 的。

另一个棘手的问题是颜色怎么办。

第一，我们记录“出现次数，只能记录**白色点**的出现次数。

第二，我们修改颜色时，修改的肯定是个虚点，所以我们只要在它身上的信息中二分查找到该点权所在的位置,修改出现次数即可。

注意到如果位置在 $poi$ 及其之前，还要修改答案。


好了，对于每一块我们就做完了。

还有一点，每一块答案的正确，依赖的是前一块信息维护的正确，但我们只建了这一块的虚树。

所以我们在每一块结束后，要把 $add$ 标记下放到点权上，清空标记和挂载在上面的信息，这就是询问分块的 **定期重构** 步骤。


算法讲解完毕，我们来考虑 $B$ 的取值以及复杂度。

总共有 $\frac{q}{B}$ 块，每块内是 $O(n\log n + B^2)$ 的(因为有排序的复杂度）。

所以总复杂度为 $O(\frac{nq\log n}{B} + qB)$，假设 $n,q$ 同阶，取 $B = \sqrt {n \log n}$ 就可以的得到 $O(n \sqrt {n \log n})$ 的时间复杂度。

如果使用基数排序，可以做到 $O(n \sqrt n)$ 。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int fir[N],nxt[N<<1],to[N<<1],ect = 0,n,q;
int fa[N];
inline void addedge(int u1,int v1)
{
	nxt[++ect] = fir[u1];fir[u1] = ect;to[ect] = v1;
}
namespace LCA{
	int ST[N*2][20],fst[N],dep[N],dfn[N];
	int dfstime,lg[N*2];
	void dfs(int x,int fa)
	{
		dep[x] = dep[fa] + 1;
		ST[fst[x] = ++dfstime][0] = x;
		for(int i = fir[x],y;y=to[i],i;i=nxt[i])
		{
			if(y == fa) continue;
			dfs(y,x);
			ST[++dfstime][0] = x;
		}
	}
	void dfs_dfs(int x,int fa)
	{
		dfn[x] = ++dfstime;
		for(int i = fir[x],y;y=to[i],i;i=nxt[i])
			if(y != fa) dfs_dfs(y,x);

	}
	inline int cmp(int x,int y) { return dep[x] < dep[y] ? x : y;}
	void init()
	{
		dfs_dfs(1,0);
		dfstime = 0;
		dfs(1,0);lg[0] = -1;
		for(int i = 1;i <= dfstime;i++) lg[i] = lg[i >> 1] + 1;
		for(int j = 1;j <= 19;j++)
			for(int i = 1;i + (1 << j) - 1 <= dfstime;i++)
				ST[i][j] = cmp(ST[i][j-1],ST[i+(1<<j-1)][j-1]);
	}
	inline int lca(int x,int y)
	{
		x = fst[x];y = fst[y];
		if(x > y) swap(x,y);
		int k = lg[y-x+1];
		return cmp(ST[x][k],ST[y-(1<<k)+1][k]);
	}
}
int Pos[N];
vector<int> G[N];
inline bool cmp(int x,int y) { return LCA::dfn[x] < LCA::dfn[y];}
int stk[N],top;
inline void addvir(int x,int y)
{
	G[x].push_back(y);
	G[y].push_back(x);
}
inline void build_tr(int &num)
{
	G[1].clear();
	stk[top = 1] = 1;
	sort(Pos + 1,Pos + num + 1,cmp);
	num = std::unique(Pos + 1,Pos + num + 1) - Pos - 1;

	for(int i = 1;i <= num;i++)
	{
		if(Pos[i] == 1) continue;
		int l = LCA::lca(Pos[i],stk[top]);
		if(l != stk[top])
		{
			while(LCA::dfn[l] < LCA::dfn[stk[top-1]])
				addvir(stk[top-1],stk[top]),--top;
			if(LCA::dfn[l] != LCA::dfn[stk[top-1]])
				G[l].clear(),addvir(l,stk[top]),stk[top] = l;
			else addvir(l,stk[top--]);
		}
		G[Pos[i]].clear();stk[++top] = Pos[i];
	}
	for(int i = 1;i < top;i++) addvir(stk[i],stk[i+1]);
}
int a[N],Q[N];
vector<pair<int,int> > W[N];
typedef vector<pair<int,int> > :: iterator Iter;
int virfa[N];
int add[N],Poi[N];
int col[N];
int ans = 0;
void dfs1(int x,int f)
{
	int now = x;
	virfa[x] = f;
	vector<pair<int,int> > tmp;
	while(now != f)
	{
		tmp.push_back(make_pair(a[now],now));
		now = fa[now];
	}
	sort(tmp.begin(),tmp.end(),greater<pair<int,int> >());
	W[x].clear();
	for(int i = 0;i < (int)tmp.size();i++)
	{
		if(W[x].empty()) {W[x].push_back(make_pair(tmp[i].first,!col[tmp[i].second]));continue;}
		if(W[x].back().first != tmp[i].first)
			W[x].push_back(make_pair(tmp[i].first,!col[tmp[i].second]));
		else W[x][W[x].size()-1].second += !col[tmp[i].second];
	}

	add[x] = 0;
	Poi[x] = -1;
	while(Poi[x] < (int)W[x].size() - 1 && W[x][Poi[x] + 1].first > 0) ++Poi[x];

	for(int i = 0;i < (int)G[x].size();i++)
	{
		int y = G[x][i];
		if(y == f) continue;
		dfs1(y,x);
	}
}
inline bool tmpcmp(const pair<int,int> &x,const pair<int,int> &y) { return x > y;}
inline void change(int x)
{
	col[x] ^= 1;
	if(col[x] == 0) //Add
	{
		Iter it = lower_bound(W[x].begin(),W[x].end(),make_pair(a[x],1e9),tmpcmp);
		assert(it->first == a[x]);
		it->second += 1;
		if(it - W[x].begin() <= Poi[x]) ++ans;
	}
	else
	{
		Iter it = lower_bound(W[x].begin(),W[x].end(),make_pair(a[x],1e9),tmpcmp);
		assert(it -> first == a[x]);
		it->second -= 1;
		if(it - W[x].begin() <= Poi[x]) --ans;
	}
}
void modify(int x,int v)
{
	int now = x;
	while(now)
	{
		if(v == 1)
		{
			add[now]++;
			if(Poi[now] < (int)W[now].size() - 1 && W[now][Poi[now] + 1].first + add[now] >= 1)
				ans += W[now][++Poi[now]].second;
		}
		else
		{
			add[now]--;
			if(Poi[now] >= 0 && W[now][Poi[now]].first + add[now] < 1)
				ans -= W[now][Poi[now]--].second;
		}
		now = virfa[now];
	}
}
int readd[N];
void dfs2(int x,int fa)
{
	for(int i = fir[x],y;y=to[i],i;i=nxt[i])
	if(y != fa) dfs2(y,x),readd[x] += readd[y]; 
	a[x] += readd[x];
}
inline void rebuild(int l,int r)
{
	for(int i = 1;i <= n;i++) readd[i] = 0;
	for(int i = l;i <= r;i++)
	{
		if(Q[i] > 0) readd[Q[i]] += 1;
		else readd[-Q[i]] -= 1;
	}
	dfs2(1,0);
	// ans = 0;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i = 2;i <= n;i++)
		scanf("%d",&fa[i]),addedge(fa[i],i),addedge(i,fa[i]);
	LCA::init();
	for(int i = 1,x;i <= n;i++)
		scanf("%d",&x),a[i] = -x;
	for(int i = 1;i <= q;i++)
		scanf("%d",&Q[i]);
	int B = sqrt(1.0*q*log2(n));

	for(int l = 1;l <= q;l += B)
	{
		int r = min(l + B - 1,q);
		int num = 0;
		for(int i = l;i <= r;i++)
			Pos[++num] = abs(Q[i]);
		build_tr(num);
		// dfs0(1,0);
		dfs1(1,0);
		for(int i = l;i <= r;i++)
		{
			int x = abs(Q[i]),y = Q[i] > 0 ? 1 : -1;
			change(x);
			modify(x,y);
			printf("%d ",ans);
		}
		rebuild(l,r);
	}
	return 0;
}
```



---

## 作者：KellyWLJ (赞：1)

唉，卡常题，$O(n\sqrt n)$ 跑的没有 $O(n\sqrt n\log n)$ 快……

不太能 $\mathrm{polylog}$ 的样子，考虑分块。

发现重构比较方便，而且 $O(nq)$ 暴力显然，计算每次修改带来的影响简单。

考虑询问分块，每 $B$ 个询问一组。

此时前面我们已经得到了一棵有黑点也有白点的树，记每个点 $lim_i=t_i+1-siz_i$，看作是这一组中新的限制，每次修改可以看作是把它到根的路径上的点的 $lim-1$，当 $lim$ 为 $0$ 且是白点时计入答案。

我们维护当前询问与上一次询问的变化量 $sum_x$，那么一次修改，会导致此时阈值为 $1/-1$ 的白点变化，如果计算出此时每个点已经被加的值 $del_i$，那么对于修改点到根路径上 $lim_i=-del_i/-del_i+1$ 的点，这次修改完状态会变。

$B$ 个询问点组成的虚树大小为 $O(B)$，意味着不同的 $del$ 段只有 $O(B)$ 段，我们可以把询问拆到每一段上，求这一段中 $lim_i=x$ 的点的数量，转化为求到根路径上的数量再前缀和相减，重构时 dfs 离线求出，用桶记录，对每一段的每个询问是 $O(1)$ 的。

我们统计时，先只看原来的颜色，只统计原来是白色的，但一组中可能某个合法的白点变黑了就不能计算，也可能某个黑点变白了之后就应该计算，重构时暴力把每次修改颜色的那个点对后面询问 $sum$ 的影响撤销，具体是分类讨论，如果原来是白点，那么讨论在它变黑和变回白的瞬间产生的变化以及把所有黑色时产生变化的瞬间撤销，黑点同理。

这部分细节很多，具体看代码。

重构则暴力修改颜色并计算出新的 $lim$，比较平凡。

时间复杂度 $O(\frac q B (B^2+n)+qB)$，取 $B=\sqrt n$ 时最优，复杂度为 $O((n+q)\sqrt n)$。

实现时被常数折磨，如果每次询问存到 `vector` 中，`vector` 不析构释放空间的话空间复杂度会退化为 $O(n\sqrt n)$，会 MLE，析构释放空间后空间复杂度为 $O(n\log n)$，瓶颈是 ST 表。但是 `vector` 析构常数较大，因此我后来块长 $B=1200$ 最快（析构次数不多），但还是卡不过去，于是把 `vector` 换成了指针分配内存，这样就直接预留好了内存，减少了 `push_back` 和析构的常数，卡过去了。

[核心代码](https://www.luogu.com.cn/paste/i2hfcncd)

---

## 作者：Reunite (赞：1)

怎么也没想到分块啊。

显然可以令 $a_i=-t_{dfn_i}$，操作可以转化为到根链 $\pm 1$，单点反转颜色，求所有白色的 $a_i>0$ 的点数。

这个是强于区间 $\pm 1$，区间 $>0$ 的个数的，所以感觉不能 poly log 的。那至少先得拍到 dfs 序上，转化为区间问题。考虑重链剖分，然后我们就只需要解决上述问题了。

设阈值为 $B$，每 $B$ 个分一块，散块暴力重构修改，对于整块，记 $s_{i,j}$ 为第 $i$ 个块，只考虑黑色点的 $a_i=j$ 的点个数。$tg_i$ 为第 $i$ 个块的加法标记。整块修改就暴力打 tag，考虑整块的贡献，只有 $a_i+tg_{bl_i}=0/1$ 的点在一次修改的时候可能会影响答案，然后就直接记录一下就行了。

注意重构的时候要重构 $s$，且单点反转颜色的时候要注意一点细节。平衡一下单次操作可以做到 $O(\sqrt n)$，但是一次树剖往上跳会到 $O(\log)$ 个区间，所以复杂度为 $O(q\sqrt n\log n)$。

分析一下最优块长，发现 $O(\log)$ 次修改，整块修改总和也不会超过 $O(nB^{-1})$，因为修改区间不交，但是散块修改是会卡满 $O(B\log n)$ 的，所以其实可以平衡到 $O(q\sqrt{n\log n})$。

空间要开到 $O(n^2B^{-1})$，看起来会爆，但是注意到一个块内最多只有 $B$ 个数，所以只需要开 short 类型就够了。

---

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define pi 100000
using namespace std;

int n,m,tm,B=170,ans;
int fa[100005];
int sz[100005];
int it[100005];
int son[100005];
int dfn[100005];
int top[100005];
vector <int> g[100005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void dfsfind(int u){
	sz[u]=1;
	for(int v:g[u]){
		dfsfind(v);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	}
	return ;
}

inline void dfstime(int u,int tp){
	top[u]=tp;
	it[dfn[u]=++tm]=u;
	if(son[u]) dfstime(son[u],tp);
	for(int v:g[u]){
		if(v==son[u]) continue;
		dfstime(v,v);
	}
	return ;
}

int a[100005];
int b[100005];
int tg[100005];
int bl[100005];
int lf[100005];
int rt[100005];
int col[100005];
short s[605][200005];

inline void upd(int l,int r,int x){
	for(int i=lf[bl[l]];i<=rt[bl[r]];i++){
		if(!col[i]) s[bl[i]][a[i]]--;
		a[i]+=tg[bl[i]];
		if(!col[i]) s[bl[i]][a[i]]++;
	}
	tg[bl[l]]=tg[bl[r]]=0;
	for(int i=l;i<=r;i++){
		if(!col[i]){
			s[bl[i]][a[i]]--;
			a[i]+=x;
			s[bl[i]][a[i]]++;
			if(a[i]==pi&&x<0) ans--;
			if(a[i]==pi+1&&x>0) ans++;
		}
		else a[i]+=x;
	}
	return ;
}

inline void updata(int l,int r,int x){
	if(bl[l]+1>=bl[r]){upd(l,r,x);return ;}
	upd(l,rt[bl[l]],x);
	upd(lf[bl[r]],r,x);
	for(int i=bl[l]+1;i<=bl[r]-1;i++){
		tg[i]+=x;
		if(x>0) ans+=s[i][1-tg[i]+pi];
		if(x<0) ans-=s[i][-tg[i]+pi];
	}
	return ;
}

int main(){
	in(n),in(m);
	for(int i=2;i<=n;i++){
		in(fa[i]);
		g[fa[i]].emplace_back(i);
	}
	for(int i=1;i<=n;i++) in(b[i]);
	dfsfind(1);
	dfstime(1,1);
	for(int i=1;i<=n;i++) a[dfn[i]]=pi-b[i];
	for(int i=1;i<=n;i++) bl[i]=(i+B-1)/B;
	for(int i=1;i<=n;i++) rt[bl[i]]=i;
	for(int i=n;i>=1;i--) lf[bl[i]]=i;
	for(int i=1;i<=n;i++) s[bl[i]][a[i]]++;
	while(m--){
		int u,k,x;
		in(u);
		k=dfn[u];
		if(col[k]){
			col[k]=0;
			s[bl[k]][a[k]]++;
			ans+=(a[k]+tg[bl[k]]>pi);
			x=-1;
		}
		else{
			col[k]=1;
			s[bl[k]][a[k]]--;
			ans-=(a[k]+tg[bl[k]]>pi);
			x=1;
		}
		u=fa[u];
		while(u){
			updata(dfn[top[u]],dfn[u],x);
			u=fa[top[u]];
		}
		printf("%d ",ans);
	}

	return 0;
}

```

---

## 作者：shao0320 (赞：1)

#### CF925E May Holidays

数据结构好题。

考虑修改一个点的影响，假设修改的点为$x$，那么显然是只会影响到从$1$节点到$x$的链上的点。

考虑树链剖分后维护每个点子树中黑色结点的个数，注意到这个东西即使可以维护也不太好统计答案，不难发现可以将其转换为每个节点初始权值为$-T_i$，多一个黑色节点就加$1$，最终结果就是全局权值大于$0$的点的个数。

这个东西用线段树平衡树等数据结构依旧非常难搞，我们考虑分块。

考虑一条重链上的点，他们的$dfs$序必定连续，那么我们直接将其$dfs$序分块。

我们发现一个比较优秀的性质是每次修改只有$1$，那么需要加（减）的点数可以$O(1)$算。

对于散数，我们直接维护权值并统计答案即可，对于整块，我们给它打上标记，表示这个整块上每一个数都有$tag$的次数没有加，同时设$sum(i,j)$表示第$i$个块中权值为$j$的点的数量，注意到$j$有可能是负数，因此需要加上$n$，避免负数下标。注意对被改的点特殊处理一下。

注意块的大小要根据内存来搞，不能直接$\sqrt n$，会MLE。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define pb push_back
#define N 100005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,fa[N],id[N],dfstime,top[N],son[N],siz[N],t[N],a[N],ans,blo,ll[N],rr[N],col[N],tag[N/505+10],sum[N/505+10][N*2],p[N];
vector<int>G[N];
void dfs1(int x)
{
	siz[x]=1;int sizz=G[x].size();
	for(int i=0;i<sizz;i++)
	{
		int v=G[x][i];
		if(v==fa[x])continue;
		dfs1(v);
		siz[x]+=siz[v];
		if(siz[v]>siz[son[x]])son[x]=v;
	}
}
void dfs2(int x,int fath)
{
	top[x]=fath;id[x]=++dfstime;
	if(son[x])dfs2(son[x],fath);int sizz=G[x].size();
	for(int i=0;i<sizz;i++)
	{
		int v=G[x][i];
		if(v==fa[x]||v==son[x])continue;
		dfs2(v,v);
	}
}
void doit(int l,int r,int v)
{
	for(int i=l;i<=r;i++)
	{
		int Id=col[i];
		if(!p[i]&&a[i]>=n-tag[Id])ans--;
		if(!p[i])sum[Id][a[i]]--;
		a[i]+=v;
		if(!p[i])sum[Id][a[i]]++;
		if(!p[i]&&a[i]>=n-tag[Id])ans++;
	}
}
void modify(int l,int r,int v)
{
	int x=col[l],y=col[r];
	if(x==y){doit(l,r,v);return;}
	doit(l,rr[x],v);doit(ll[y],r,v);
	for(int i=x+1;i<y;i++)
	{
		if(v==1)tag[i]++,ans+=sum[i][n-tag[i]];
		else ans-=sum[i][n-tag[i]],tag[i]--;
	}
}
int main()
{
	n=read();m=read();
	for(int i=2;i<=n;i++)
	{
		fa[i]=read();
		G[fa[i]].pb(i);
	}
	for(int i=1;i<=n;i++)t[i]=read()+1;
	dfs1(1);dfs2(1,1);
	//puts("!!!!!!!!!!!!");
	blo=505;
	for(int i=1;i<=n;i++)
	{
		col[i]=(i-1)/blo+1;
		if(col[i]!=col[i-1])rr[col[i-1]]=i-1,ll[col[i]]=i;
	}
	rr[col[n]]=n;
	for(int i=1;i<=n;i++)a[id[i]]=n-t[i];
	for(int i=1;i<=n;i++)sum[col[i]][a[i]]++;
	//for(int i=1;i<=n;i++)printf("%d ",top[i]);
	//puts("");
	while(m--)
	{
		int x=read(),val;
		val=(x>0)?1:-1;
		if(x<0)x=-x;
		p[id[x]]^=1;
		if(a[id[x]]>=n-tag[col[id[x]]])ans-=val;
		sum[col[id[x]]][a[id[x]]]-=val;
		while(x)modify(id[top[x]],id[x],val),x=fa[top[x]];
		printf("%d ",ans);
	}
	return 0;
}
/*
7 8
4 5 1 1 5 5
0 0 0 1 2 0 0
2
6
3
7
-2
4
-3
1
*/
```

---

