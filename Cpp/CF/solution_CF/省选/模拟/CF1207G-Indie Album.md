# Indie Album

## 题目描述

Mishka 最喜欢的实验独立乐队最近发布了一张新专辑！这张专辑中的歌曲名有一个共同的特点。每个名字 $s_i$ 都属于以下两种类型之一：

- $1~c$ —— 一个小写拉丁字母；
- $2~j~c$ —— 将第 $j$ 首歌的名字 $s_j$（$1 \le j < i$）末尾添加一个小写拉丁字母得到。

歌曲编号从 $1$ 到 $n$。保证第一首歌一定是类型 $1$。

Vova 对新专辑很感兴趣，但他实在没有时间全部听完。因此他向 Mishka 提出了一些问题，以判断某首歌是否值得一听。问题的格式如下：

- $i~t$ —— 统计字符串 $t$ 在第 $i$ 首歌的名字 $s_i$ 中作为连续子串出现的次数，$t$ 只包含小写拉丁字母。

Mishka 并不质疑这些信息的用途，但他很难回答这些问题。你能帮 Mishka 回答所有 Vova 的问题吗？

## 说明/提示

第一个样例的歌曲名如下：

1. d
2. da
3. dad
4. dada
5. dadad
6. dadada
7. dadadad
8. dadadada
9. d
10. do
11. dok
12. doki
13. dokid
14. dokido
15. dokidok
16. dokidoki
17. do
18. dok
19. doki
20. dokidoki

因此，每个问题字符串的出现位置如下：

1. 字符串 "da" 在 "dadadada" 中出现在位置 $[1, 3, 5, 7]$；
2. 字符串 "dada" 在 "dadadada" 中出现在位置 $[1, 3, 5]$；
3. 字符串 "ada" 在 "dadadada" 中出现在位置 $[2, 4, 6]$；
4. 字符串 "dada" 在 "dadada" 中出现在位置 $[1, 3]$；
5. 字符串 "dada" 在 "dad" 中没有出现；
6. 字符串 "doki" 在 "doki" 中出现在位置 $[1]$；
7. 字符串 "ok" 在 "doki" 中出现在位置 $[2]$；
8. 字符串 "doki" 在 "dokidoki" 中出现在位置 $[1, 5]$；
9. 字符串 "doki" 在 "dokidok" 中出现在位置 $[1]$；
10. 字符串 "d" 在 "d" 中出现在位置 $[1]$；
11. 字符串 "a" 在 "d" 中没有出现；
12. 字符串 "doki" 在 "dokidoki" 中出现在位置 $[1, 5]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
20
1 d
2 1 a
2 2 d
2 3 a
2 4 d
2 5 a
2 6 d
2 7 a
1 d
2 9 o
2 10 k
2 11 i
2 12 d
2 13 o
2 14 k
2 15 i
2 1 o
2 17 k
2 18 i
2 15 i
12
8 da
8 dada
8 ada
6 dada
3 dada
19 doki
19 ok
16 doki
15 doki
9 d
1 a
20 doki
```

### 输出

```
4
3
3
2
0
1
1
2
1
1
0
2
```

# 题解

## 作者：Alex_Wei (赞：7)

> [CF1207G Indie Album](https://www.luogu.com.cn/problem/CF1207G)

> 题意简述：有 $n$ 种操作，给出整数，整数和字符 $op,j(op=2),c$。若 $op=1$ 则 $s_i=c$；否则 $s_i=s_j+c$。$m$ 次询问给出 $i,t$，求 $t$ 在 $s_i$ 中的出现次数。

> 本文节选自 [ACAM 乱做 IV.](https://www.cnblogs.com/alex-wei/p/ACAM.html)

~~以前打过这场比赛，要是我当时会 ACAM 多好啊。~~

---

注意到如果我们对操作串 $s$ 建出 ACAM 需要动态修改 fail 树的结构，不太可行。那么换个思路，考虑对所有询问串 $t$ 建出 ACAM。那么这样就是在 ACAM 上跑 $s_i$，求出有多少个跑到的节点在 fail 树上以 $t$ 的终止节点的子树中。这个可以对 fail 树进行一遍 dfs，用每个节点的 dfs 序和 size 维护。这样就是单点修改，区间查询，用树状数组即可。

可是 $s_i$ 的总长度可能会很大。不难发现每个 $s_i$ 形成了一个依赖关系，建出树，我们只需要再对这个 “操作树” 进行 dfs，先计算贡献（位置 $son_{p,c_i}$ 加上 $1$），再更新并下传跑到的位置 $p=son_{p,c_i}$，最后撤销贡献即可。

时间复杂度 $\mathcal{O}((n+m)\log \sum|t|)$。 

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

//#pragma GCC optimize(3)
//#define int long long

#define pb emplace_back

const int N=4e5+5;

int n,m,ans[N];
int cnt,dn,son[N][26],ed[N],fa[N],sz[N],dfn[N];
vector <int> e[N],f[N],ft[N];
char ad[N];
void ins(int id,string s){
	int p=0;
	for(char it:s){
		if(!son[p][it-'a'])son[p][it-'a']=++cnt;
		p=son[p][it-'a'];
	} ed[id]=p;
} void build(){
	queue <int> q;
	for(int i=0;i<26;i++)if(son[0][i])q.push(son[0][i]);
	while(!q.empty()){
		int t=q.front(); q.pop();
		for(int i=0;i<26;i++)
			if(son[t][i])q.push(son[t][i]),fa[son[t][i]]=son[fa[t]][i];
			else son[t][i]=son[fa[t]][i];
		ft[fa[t]].pb(t);
	}
} void dfs(int id){
	dfn[id]=++dn,sz[id]=1;
	for(int it:ft[id])dfs(it),sz[id]+=sz[it];
}

int c[N];
void add(int x,int v){while(x<=dn)c[x]+=v,x+=x&-x;}
int query(int x){int ans=0; while(x)ans+=c[x],x-=x&-x; return ans;}
int query(int l,int r){return query(r)-query(l-1);}
void cal(int id,int p){
	if(id)p=son[p][ad[id]-'a'],add(dfn[p],1);
	for(int it:e[id])ans[it]=query(dfn[ed[it]],dfn[ed[it]]+sz[ed[it]]-1);
	for(int it:f[id])cal(it,p);
	add(dfn[p],-1);
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int tp,p=0; cin>>tp;
		if(tp==2)cin>>p;
		f[p].pb(i),cin>>ad[i];
	} cin>>m;
	string q;
	for(int i=1,id;i<=m;i++)
		cin>>id>>q,e[id].pb(i),ins(i,q);
	build(),dfs(0),cal(0,0);
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：EM_LGH (赞：7)

这里给出一个后缀自动机的做法. 


假设每次询问 $t$ 在所有 $s$ 中的出现次数，那么这是非常简单的： 


直接对 $s$ 构建后缀自动机，随便维护一下 $endpos$ 大小就可以. 


然而，想求 $t$ 在 $trie$ 树中一个节点到根的字符串中的出现次数就难了很多. 


我们慢慢讲： 


首先，我们对题中给的 $trie$ 树（即所有 $s$ 串）构建广义后缀自动机. 


因为后缀自动机能识别所有的子串，所以可以直接将 $t$ 在自动机上匹配. 


假设匹配成功，即得到终止节点 $p$. 


那么我们想求 $s_{i}$ 中包含 $p$ 的个数. 


令 $s_{i}$ 对应到 $trie$ 树的终止节点为 $end(i)$ ，那么将 $end(i)$ 到根节点的所有字符都插入后缀自动机之后，对答案有贡献的就是 $trie$ 中 $end(i)$ 到根中后缀包含 $t$ 的节点个数. 


而巧妙的是，对 $s_{i}$ 有贡献的所有 $trie$ 中的节点之间的位置关系是链的关系. 


即他们都在 $end(i)$ 到根节点这条路径上. 


于是，我们就联想，什么数据结构，能让深度递增的节点编号连续呢？


——树链剖分. 


没错，我们对 $trie$ 来一遍树剖求解每个点的树剖序. 


对后缀自动机每一个节点建一个线段树，维护的是后缀树中该节点为根子树中所有树剖序的所有标号种类.  


对于这个，我们可以在扩展 $trie$ 树字符的时候就在自动机中新建节点插入该点的树剖序，然后扩展完 $trie$ 树后再来一遍线段树合并. 


最后，只需暴力跳重链，并查询 $dfn[top[x]]$~$dfn[x]$ 在 $p$ 节点所在线段树中有几个出现. 


时间复杂度为 $O(nlog^2n)$，常数巨大，远没有 AC 自动机好写，运行快. 


不过，这确实是一道练习后缀自动机的好题. 


```cpp
#include <map>
#include <vector> 
#include <queue> 
#include <cstdio>  
#include <cstring> 
#include <algorithm>
#define N 400003 
#define setIO(s) freopen(s".in","r",stdin) 
using namespace std;  
char S[N]; 
int n,m,rt[N<<1];   
namespace Trie {
	int id[N],tim; 
	struct Node {    
		map<int,int>ch;   
		int siz,dfn,top,son,fa;     
	}t[N];  
	void dfs1(int u) { 
		t[u].siz=1; 
		for(int i=0;i<27;++i) 
			if(t[u].ch.count(i)) {    
				int v=t[u].ch[i]; 
				t[v].fa=u,dfs1(v),t[u].siz+=t[v].siz;   
				if(!t[u].son||t[v].siz>t[t[u].son].siz) t[u].son=v;    
			}
	} 
	void dfs2(int u,int tp) {
		t[u].top=tp; 
		t[u].dfn=++tim;   
		if(t[u].son) dfs2(t[u].son,tp); 
		for(int i=0;i<27;++i) 
			if(t[u].ch.count(i)) { 
				int v=t[u].ch[i]; 
				if(v!=t[u].son) 
					dfs2(v,v); 
			} 
	}
	void build_tree() {  
		dfs1(0), dfs2(0,0);    
	}
}; 
namespace seg { 
	#define ls t[x].lson 
	#define rs t[x].rson
	int tot; 
	struct Node { 
		int lson,rson,sum; 
	}t[N*50]; 
	void pushup(int x) {
		t[x].sum=t[ls].sum+t[rs].sum;    
	}
	void update(int &x,int l,int r,int p,int v) {
		if(!x) 
			x=++tot; 
		if(l==r) {
			t[x].sum=v; 
			return;
		} 
		int mid=(l+r)>>1;    
		if(p<=mid) update(ls,l,mid,p,v); 
		else update(rs,mid+1,r,p,v); 
		pushup(x);  
	}
	int query(int x,int l,int r,int L,int R) {
		if(!x) return 0; 
		if(l>=L&&r<=R) return t[x].sum; 
		int mid=(l+r)>>1,re=0; 
		if(L<=mid) re+=query(ls,l,mid,L,R); 
		if(R>mid) re+=query(rs,mid+1,r,L,R);  
		return re; 
	}
	int merge(int l,int r,int x,int y,int tt) { 
		if(!x||!y) 
			return x+y;  
		int oo=++tot;      
		if(l==r) 
			t[oo].sum=1;                 
		else { 
			int mid=(l+r)>>1; 
			t[oo].lson=merge(l,mid,t[x].lson,t[y].lson,tt); 
			t[oo].rson=merge(mid+1,r,t[x].rson,t[y].rson,tt); 
			pushup(oo);   
		} 
		return oo; 
	}
	#undef ls
	#undef rs
}; 
namespace SAM {  
	int tot,id[N<<1],tax[N<<1],rk[N<<1];      
	struct Node {  
		map<int,int>ch; 
		int len,pre; 
	}t[N<<1];            
	struct Edge { 
		int from,c;      
		Edge(int from=0,int c=0):from(from),c(c){} 
	};             
	queue<int>q; 
	int extend(int lst,int c,int i) {      
		int p=lst; 
	    if(t[p].ch.count(c)) { 
	    	int q=t[p].ch[c]; 
	    	if(t[q].len==t[p].len+1) seg::update(rt[q],1,Trie::tim,i,1),lst=q; 
	    	else { 
	    		int nq=++tot; 
	    		t[nq].len=t[p].len+1;  
	    		t[nq].pre=t[q].pre,t[q].pre=nq;     
	    		t[nq].ch=t[q].ch; 
	    		seg::update(rt[nq],1,Trie::tim,i,1);      
	    		for(;p&&t[p].ch.count(c)&&t[p].ch[c]==q;p=t[p].pre) t[p].ch[c]=nq;      
	    		lst=nq;            
	    	}
	    } 
	    else { 
	    	int np=++tot;  
	    	t[np].len=t[p].len+1;  
	    	seg::update(rt[np],1,Trie::tim,i,1);    
	    	for(;p&&!t[p].ch.count(c);p=t[p].pre) t[p].ch[c]=np;   
	    	if(!p) t[np].pre=1;  
	        else {
	        	int q=t[p].ch[c]; 
	        	if(t[q].len==t[p].len+1) t[np].pre=q;     
	        	else { 
	        		int nq=++tot; 
	        		t[nq].len=t[p].len+1; 
	        		t[nq].pre=t[q].pre,t[q].pre=t[np].pre=nq;         
	        		t[nq].ch=t[q].ch; 
	        		for(;p&&t[p].ch.count(c)&&t[p].ch[c]==q;p=t[p].pre) t[p].ch[c]=nq;  
	        	}
	        }
	        lst=np; 
	    }  
	    return lst;  
	}  
	void construct() {
		int i,j; 
		id[0]=tot=1;   
		q.push(0);    
		while(!q.empty()) {
			int u=q.front();q.pop(); 
			for(i=0;i<27;++i) {
				if(Trie::t[u].ch.count(i)) { 
					int v=Trie::t[u].ch[i];   
					q.push(v);               
					id[v]=extend(id[u],i,Trie::t[v].dfn);        
				}
			}
		} 
		for(i=1;i<=tot;++i) tax[i]=0; 
		for(i=1;i<=tot;++i) ++tax[t[i].len];    
		for(i=1;i<=tot;++i) tax[i]+=tax[i-1];        
		for(i=1;i<=tot;++i) rk[tax[t[i].len]--]=i;   
		for(i=tot;i>1;--i) { 
			int u=rk[i];     
			int ff=t[u].pre;   
			if(ff>1) 
				rt[ff]=seg::merge(1,Trie::tim,rt[u],rt[ff],0); 
		}
	} 
}; 
void solve(int x) { 
	int p=1,i,len=strlen(S+1),re=0; 
	for(i=1;i<=len;++i) {
		int c=S[i]-'a'; 
		if(SAM::t[p].ch.count(c)) 
			p=SAM::t[p].ch[c]; 
		else {
			printf("0\n"); 
			return; 
		}
	}    
	for(x=Trie::id[x];x;x=Trie::t[Trie::t[x].top].fa) {  
	    re+=seg::query(rt[p],1,Trie::tim,Trie::t[Trie::t[x].top].dfn,Trie::t[x].dfn);       
	}
	printf("%d\n",re);     
}
int main() {
	int i,j; 
	// setIO("input"); 
	scanf("%d",&n); 
	for(i=1;i<=n;++i) {
		int op,lst=0; 
		char str[3];  
		scanf("%d",&op);      
		if(op==2) scanf("%d",&lst),lst=Trie::id[lst]; 
		scanf("%s",str);   
		if(!Trie::t[lst].ch.count(str[0]-'a')) {  
			Trie::t[lst].ch[str[0]-'a']=i; 
			Trie::id[i]=i;        
		}
		else Trie::id[i]=Trie::t[lst].ch[str[0]-'a'];   
	} 
	Trie::build_tree();   
	SAM::construct();     
	scanf("%d",&m);   
	for(i=1;i<=m;++i) 
		scanf("%d%s",&j,S+1), solve(j);       
	return 0; 
}
```


---

## 作者：BlankAo (赞：6)

$\Large\natural$ **CF1207G Indie Album \ [原题链接](https://www.luogu.com.cn/problem/CF1207G) \ [更好阅读体验](https://www.cnblogs.com/BlankAo/p/14375202.html)**

## 解法

这种题算是比较套路的了，我们看见这种多字符串匹配，会想到**AC自动机**。

如果不会**AC自动机**的可以看看 [我的博客](https://www.cnblogs.com/BlankAo/p/14373027.html) ，希望能给您带来帮助。

那么如果我们对于所有字典树节点连边 $i-fail_i$（根节点没有 $fail$，不连边），那么就得到了一棵 **Fail树**。

那么，如果一号点为根节点，那所有 $fail$ 直接或间接指向 $i$ 号点的节点，都在 $i$ 的子树中。

所以查询字符串 $X$ 在字符串 $Y$ 中出现几次，等价于建出 **Trie** 和 **Fail树** 后，在 **Fail树中** 以 “$X$的结束节点”（设为 $i$） 为根的子树中有多少个 $Y$ 包含的节点。

不理解可以看这解释：比如 $j$ 号点是 $Y$ 所包含的，是 $Y$ 的第 $id$ 个节点，那么代表在 $Y$ 查询时，$j$ 跑 $fail$ 可以跑出 $X$，所以 $X$ 是 $Y$ 中 $1\sim id$ 这个子串的后缀。 

对于这道题，我们可以类比 [阿机的打字狸](https://www.luogu.com.cn/problem/P2414) ：

设询问的字符串为 $T$，则显然有这样一个方法：让 $T$ 在 **Trie** 上跑，经过的点对于的 **Fail树节点**权值加一。然后我们查询 $S$ 在 **Trie** 的结尾节点 $G$，对应的 **Fail树节点** ，的子树和（可能有点绕）。最后我们再把那些加一的点再减一，复原原来的树。

把答案离线后，我们可以在 **Trie树** 上 **DFS**，来到一个点，这个点对于的 **Fail树节点** 权值加一；离开一个点，同样地权值减一。这样当我们到达某个字符串的末尾时，我们可以保证**有且仅有**这个字符串的点上有值。然后我们调出在这个点上的每一个询问，查询它们对应的 **Fail树节点** 的子树和即可。

所以我们需要支持单点加值，以及查询一个点的子树和，可以用 **DFS序** 解决。

因为一个点的子树在 **DFS序** 上是连续的，所以我们只用**区间查询（给子树查询）、单点加值（ 在 Trie 跑上 DFS 时加减）**就行了，显然套树状数组模板即可。

## 代码

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define mar(o) for(int E=fst[o];E;E=e[E].nxt)
#define v e[E].to
using namespace std;
const int n7=401234,m7=801234,z7=1601234;
struct dino{int to,nxt;}e[z7];
struct lyca{int z,id;};
int n,T,cnt=1,tre[m7][26],fail[m7],poi[n7],head,tail,que[m7];
int ecnt,fst[m7],t,atre[n7],L[n7],R[n7],ans[n7];
char cr[n7];bool tru[m7][26];
vector <lyca> vec[m7];

int rd(){
   int shu=0;char ch=getchar();
   while(!isdigit(ch))ch=getchar();
   while(isdigit(ch))shu=(shu<<1)+(shu<<3)+(ch^48),ch=getchar();
   return shu;
}

void edge(int sta,int edn){
	ecnt++;
	e[ecnt]=(dino){edn,fst[sta]};
	fst[sta]=ecnt;
}

void insert1(){
	rep(i,1,n){
		int sys=rd(),las=1;
		if(sys==2)las=poi[ rd() ];
		char ch=getchar()-'a';
		if(!tre[las][ch]){
			cnt++,tre[las][ch]=cnt;
		}
		poi[i]=tre[las][ch];
	}
}

void insert2(int z){
	int len=strlen(cr+1),now=1;
	rep(i,1,len){
		int ch=cr[i]-'a';
		if(!tre[now][ch]){
			cnt++,tre[now][ch]=cnt;
		}
		now=tre[now][ch];
	}
	poi[z]=now;
}

void Gfail(){
	head=1,tail=1,que[1]=1;
	rep(i,0,25)tre[0][i]=1;
	while(head<=tail){
		int now=que[head];
		rep(i,0,25){
			int edn=tre[ fail[now] ][i];
			if(tre[now][i]){
				fail[ tre[now][i] ]=edn;
				edge(edn,tre[now][i]);
				tail++,que[tail]=tre[now][i];
				tru[now][i]=1;
			}
			else tre[now][i]=edn;
		}
		head++;
	}
}

#define lb(z) (z&-z)
void updat(int z,int id){
	while(id<=cnt)atre[id]+=z,id+=lb(id);
}
int Dquery(int id){
	int tot=0;
	while(id)tot+=atre[id],id-=lb(id);
	return tot;
}
int query(int l,int r){
	return Dquery(r)-Dquery(l-1);
}

void dfs1(int o){
	t++,L[o]=t;
	mar(o)dfs1(v);
	R[o]=t;
}

int fimd(){
	int len=strlen(cr+1),now=1;
	rep(i,1,len)now=tre[now][ cr[i]-'a' ];
	return now;
}

void dfs2(int o){
	updat(1,L[o]);
	int wal=vec[o].size()-1;
	rep(i,0,wal){
		int ll=L[ vec[o][i].z ];
		int rr=R[ vec[o][i].z ];
		ans[ vec[o][i].id ]=query(ll,rr);
	}
	rep(i,0,25){
		if(tru[o][i])dfs2(tre[o][i]); 
	}
	updat(-1,L[o]);
}

int main(){
	n=rd(),insert1(),T=rd();
	rep(i,1,T){
		int z=rd();scanf("%s",cr+1);
		insert2(i+n);
		vec[ poi[z] ].push_back( (lyca){poi[i+n],i} );
	}
	Gfail(),dfs1(1),dfs2(1);
	rep(i,1,T)printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：一扶苏一 (赞：6)

## 【ACAM】【CF1207G】 Indie Album

### Analysis

cf 竟然出[原题](https://www.luogu.com.cn/problem/P2414)（

考虑把询问串和原串都插入到 AC 自动机里，进行一次询问 $i, t$ 时，答案就是 $s_i$ 的所有前缀中，在 fail 树上是 $t$ 的后代的结点个数。

查询某节点是另一节点的后代的套路操作是求出 dfs 序和子树 size，如果 $v$ 是 $u$ 的后代，那么 $dfn_u \leq v \leq dfn_u + size_u$，其中 $dfn$ 表示 dfs 序，$size$ 表示子树大小。

把询问离线，挂到 $s_i$ 在 Trie 树上对应的节点上，遍历 Trie 树，同时维护当前节到根的所有节点的 dfs 序的权值树状数组，即可 $O(\log |s| + |t|)$ 求出答案。

### Code

```cpp
namespace Fusu {

const int maxt = 26;
const int maxn = 1000006;

void Init();
void Build();
void Query();

void Main() {
  Init();
  Build();
  Query();
}

int vistime;
struct Node {
  int sz, dfn;
  Node *fail, *fa;
  Node *son[maxt];
  std::vector<Node*> fson;
  std::vector<int> qid;

  void dfs() {
    dfn = ++vistime;
    sz = 1;
    for (auto v : fson) {
      v->dfs();
      sz += v->sz;
    }
  }
};
Node Mem[maxn], *pool = Mem + 1, *rot = Mem;
Node* New() {
  return pool++;
}

int n, m;
char s[maxn];
Node *eid[maxn];
std::pair<int, int> querys[maxn];
void Init() {
  qr(n);
  for (int i = 1, op, j; i <= n; ++i) {
    qr(op);
    auto u = rot;
    if (op == 2) {
      qr(j); u = eid[j];
    }
    qrs(s);
    int k = *s - 'a';
    auto v = u->son[k] ? u->son[k] : (u->son[k] = New());
    v->fa = u; eid[i] = u = v;
  }
  qr(m);
  for (int i = 1, j, k; i <= m; ++i) {
    qr(j); k = qrs(s + 1);
    auto u = rot;
    for (int ii = 1, x = s[ii] - 'a'; ii <= k; x = s[++ii] - 'a') {
      auto v = u->son[x] ? u->son[x] : (u->son[x] = New());
      v->fa = u; u = v;
    }
    eid[k = i + n] = u;
    querys[i] = std::make_pair(j, k);
  }
}

std::queue<Node*> Q;
void Build() {
  for (auto &v : rot->son) if (v != nullptr) {
    Q.push(v); v->fail = rot;
  } else {
    v = rot;
  }
  for (Node *u, *v; !Q.empty(); Q.pop()) {
    u = Q.front();
    u->fail->fson.push_back(u);
    for (int i = 0; i < maxt; ++i) if ((v = u->son[i]) != nullptr) {
      v->fail = u->fail->son[i]; Q.push(v);
    } else {
      u->son[i] = u->fail->son[i];
    }
  }
  rot->dfs();
}

struct BIT {
  int tr[maxn];

  inline int lowbit(const int x) { return x & -x; }
  inline void upd(int p, const int v) { do tr[p] += v; while ((p += lowbit(p)) <= vistime); }
  inline int qry(int p) { int ret = 0; do ret += tr[p]; while (p -= lowbit(p)); return ret; }
};
BIT bit;

int ans[maxn];
void dfs(Node *const u) {
  bit.upd(u->dfn, 1);
  for (auto v : u->qid) {
    auto yzy = eid[querys[v].second];
    int l = yzy->dfn - 1, r = yzy->dfn + yzy->sz - 1;
    ans[v] = bit.qry(r) - bit.qry(l);
  }
  for (auto v : u->son) if (v->fa == u) {
    dfs(v);
  }
  bit.upd(u->dfn, -1);
}

void Query() {
  for (int i = 1; i <= m; ++i) {
    eid[querys[i].first]->qid.push_back(i);
  }
  dfs(rot);
  qwa(ans + 1, m, '\n', '\n');
}

} // namespace Fusu
```





---

## 作者：qiyue7 (赞：5)

题目中给出了个trie，询问给定前缀中询问串出现了多少次。如果我们能维护一个SA，那么我们就可以对每个询问O（|S|logn）回答。单独构建每个前缀的后缀数组的时间复杂度显然无法承受，但是我们可以注意到每个前缀都是由其祖先在尾部追加一个字符构成的新的后缀数组（即只添加一个后缀），那么我们考虑用平衡树维护后缀数组，dfs时进入一个新节点即插入一个后缀，回退时删除该后缀即可。复杂度O（nlogn）。

参考资料 陈立杰 《重量平衡树和后缀平衡树在信息学奥赛中的应用》

AC主代码：

```cpp
vector<int> query[410000];
vector<int> edge[410000];
int ans[410000];
int str[410000];
char vet[410000];
string s2[410000];
void dfs(int cur)
{
	sbt.push_back(vet[cur]);
	if (!query[cur].empty())
	{
		for (auto &p : query[cur])
		{
			int nn = s2[p].size();
			for (int i = 0; i < nn; ++i)
				str[nn-i] = s2[p][i];
			str[nn + 1] = 123456;
			ans[p] = sbt.query(str,nn);
		}
	}
	for (auto &p : edge[cur])
		dfs(p);
	sbt.pop_back();
}
int main()
{
	int n, q,q2,opt;
	char p;
	string ss;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> opt;
		if (opt == 1)
		{
			cin >> p;
			edge[0].emplace_back(i);
		}
		else
		{
			cin >>q2>> p;
			edge[q2].emplace_back(i);
		}
		vet[i] = p;
	}
	cin >> q;
	for (int i = 1; i <= q; ++i)
	{
		cin >> q2 >> s2[i];
		query[q2].emplace_back(i);
	}
	dfs(0);
	for (int i = 1; i <= q; ++i)
		cout << ans[i] << endl;
	return 0;
}
```


---

## 作者：Hoks (赞：4)

## 前言
感觉，这题和 [P2414 [NOI2011] 阿狸的打字机](https://www.luogu.com.cn/problem/P2414)挺像的，但是多了一步思路的转化。
## 思路分析
首先观察题面，我们会发现这道题最开始的串 $s$ 他是不断增加的，如果考虑造 fail 树的话就要动态，非常麻烦。

但是仔细一看会发现我们查询的串是固定的，所以考虑对查询的串建 ACAM，然后无脑 fail 树也建上。

然后类比前面那道题的做法，就相当于是把 $s_i$ 在 fail 树上跑，答案就是询问串子树的权值和，选择树状数组子树加，单点查询。

因为 $s_i$ 是逐位加上来的，所以形成了一颗树的关系，那么把 $s_i$ 拿来跑就可以通过遍历 $s_i$ 形成的树的方式。

Tips：记得撤销贡献。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=400010,INF=0x3f3f3f3f3f3f3f3f;
int n,m,cntt,dfn[N],ed[N],ans[N],id[N];char s[N],t[N];vector<int>e[N],g[N],q[N];
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    inline void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    inline int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
    inline void mdf(int l,int r,int v){modify(l,v),modify(r+1,-v);}
}tt;
inline void add(int u,int v){e[u].emplace_back(v);}
struct ACAM
{
	struct node{int nxt,ed,v[26];}t[N];int tot=0;
	inline void insert(char s[],int n,int j)
	{
		int u=0;
		for(int i=1;i<=n;i++){if(!t[u].v[s[i]-'a']) t[u].v[s[i]-'a']=++tot;u=t[u].v[s[i]-'a'];}
		id[j]=u;
	}
	inline void build()
	{
		queue<int>q;
		for(int i=0;i<26;i++) if(t[0].v[i]) add(0,t[0].v[i]),t[t[0].v[i]].nxt=0,q.push(t[0].v[i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<26;i++)
				if(t[u].v[i]) t[t[u].v[i]].nxt=t[t[u].nxt].v[i],add(t[t[u].v[i]].nxt,t[u].v[i]),q.push(t[u].v[i]);
				else t[u].v[i]=t[t[u].nxt].v[i];
		}
	}
}ac;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
}
using namespace Fast_IO;
namespace KMP
{
	inline bool chk(char c) { return !(c>='a'&&c<='z'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace KMP;
void dfs(int u){dfn[u]=++cntt;for(auto v:e[u]) dfs(v);ed[u]=cntt;}
void calc(int u,int v)
{
	if(u) v=ac.t[v].v[s[u]-'a'],tt.modify(dfn[v],1);
	for(int i:q[u]) ans[i]=tt.query(ed[id[i]])-tt.query(dfn[id[i]]-1);
	for(int i:g[u]) calc(i,v);tt.modify(dfn[v],-1);
}
signed main()
{
	n=read();
	for(int i=1,op,u;i<=n;i++)
	{
		op=read();u=0;if(op==2) u=read();s[i]=getchar();
		g[u].emplace_back(i);while(chk(s[i])) s[i]=getchar();
	}m=read();
	for(int i=1,u;i<=m;i++) u=read(),n=0,rd(t,n),q[u].emplace_back(i),ac.insert(t,n,i);
	ac.build();dfs(0);tt.n=cntt;calc(0,0);
	for(int i=1;i<=m;i++) print(ans[i]),puts("");
    return 0;
}
```

---

## 作者：kai586123 (赞：4)

AC自动机。

把所有的询问串加入AC自动机。把加入新字符的操作建成树，把询问挂在树的节点上。在树上DFS，某节点的串即根到它的一段。

由AC自动机的知识可知，走到自动机的某个点的时候，Fail树上它到根的点全部被匹配到了。

问题转化为单点加，子数内求和，线段树维护即可。$O(nlogn)$。

```cpp
#include <bits/stdc++.h>

const int N = 5e5 + 233;

int ch[N][26], fail[N], end[N], tot;

void insert(char str[], int id) {
    int now = 0, len = strlen(str + 1);
    for (int i = 1; i <= len; ++i) {
        int c = str[i] - 'a';
        if (!ch[now][c])
            ch[now][c] = ++tot;
        now = ch[now][c];
    }
    end[id] = now;
}

void build_acam() {
    std::queue<int> que;
    for (int i = 0; i < 26; ++i)
        if (ch[0][i])
            que.push(ch[0][i]);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for (int i = 0; i < 26; ++i) {
            if (ch[x][i]) {
                fail[ch[x][i]] = ch[fail[x]][i];
                que.push(ch[x][i]);
            } else
                ch[x][i] = ch[fail[x]][i];
        }
    }
}

std::vector<int> fson[N];

void build_tree() {
    for (int i = 1; i <= tot; ++i)
        fson[fail[i]].push_back(i);
}

int id[N], num, size[N];

void dfs_tree(int x) {
    id[x] = ++num; size[x] = 1;
    for (auto y : fson[x]) {
        dfs_tree(y);
        size[x] += size[y];
    }
}

int sum[N * 4];

#define ls(p) p << 1
#define rs(p) p << 1 | 1

void add(int p, int x, int y, int L, int R) {
    if (L == R) return (void)(sum[p] += y);
    int mid = (L + R) >> 1;
    if (x <= mid) add(ls(p), x, y, L, mid);
    else add(rs(p), x, y, mid + 1, R);
    sum[p] = sum[ls(p)] + sum[rs(p)];
}

int ask(int p, int l, int r, int L, int R) {
    if (l <= L && r >= R) return sum[p];
    int mid = (L + R) >> 1, ret = 0;
    if (l <= mid) ret = ask(ls(p), l, r, L, mid);
    if (r > mid) ret += ask(rs(p), l, r, mid + 1, R);
    return ret;
}

int n, m, ans[N]; char str[N];

struct Edge {
    int to; char c;
};
std::vector<Edge> son[N];

std::vector<int> qu[N];

void solve(int x, int now) {
    add(1, id[now], 1, 1, num);
    for (auto i : qu[x])
        ans[i] = ask(1, id[end[i]], id[end[i]] + size[end[i]] - 1, 1, num);
    for (auto i : son[x])
        solve(i.to, ch[now][i.c - 'a']);
    add(1, id[now], -1, 1, num);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int op, lst = 0; char c;
        scanf("%d", &op);
        if (op == 2) scanf("%d", &lst);
        scanf(" %c", &c);
        son[lst].push_back({ i, c });
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        int id; scanf("%d%s", &id, str + 1);
        insert(str, i); qu[id].push_back(i);
    }
    build_acam();
    build_tree();
    dfs_tree(0);
    solve(0, 0);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：Reunite (赞：2)

## 一
---

模式匹配，统计次数，后缀加一些字符，都提示我们使用 ACAM。

首先我们要清楚，在一个串的末尾添加 $len$ 个字符，那这个串在 ACAM 上跑的路径也只会在末尾增加 $O(len)$ 个点，也就是说，如果我们按照不断末尾加元素的顺序去跑 ACAM，那么复杂度是有保证的。（删去同理，就像[阿狸的打字机](https://www.luogu.com.cn/problem/P2414)那样）。

按照处理多模式串匹配的一般思路，我们先把所有询问串建成 ACAM，再构建出 fail 树，这样我们让文本串跑 ACAM 的时候只需要简单的单点加，子树求和即可。现在问题是每次跑文本串的复杂度太高了，考虑优化。

注意到文本串的给出方式其实是一颗森林，我们建一个虚拟点连成一颗树。发现有大量的前缀关系，而真正变化的后缀长度总和只有 $|t|$，换句话说，如果我们树上的每个儿子从父节点在 ACAM 上的终止节点继续跑，那么复杂度就是 $O(|t|)$ 的。

于是这题就被解决了，具体地，我们把文本串的给出建成一颗树，树边上存父亲到儿子加入了什么后缀。直接 dfs，递归前保留父亲跑到了 ACAM 上的哪个点，然后接着在 ACAM 上跑边上增加的后缀，同时用树状数组维护贡献。递归后再还原即可。

同时我们要把所有的询问挂在树上，dfs 的同时求解。

## 二
---

建 ACAM 的复杂度是 $O(|t||\sum|)$，dfs 的复杂度是 $O(n+|t| \log_2 |t|)$。总复杂度是 $O(n+m+|t||\sum|+|t|\log_2|t|)$。

```cpp

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n,tot,m,cnt,tm;
char c[400005];
char s[400005];
int it[400005];
int ans[400005];
int dfn[400005];
int sz[400005];
int fail[400005];
int son[400005][26];
struct node{int v,l,r;};
vector <node> g[400005];
vector <int> ed[400005];
vector <int> q[400005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int insert(){
	int len=strlen(c+1),u=0;
	for(int i=1;i<=len;i++){
		if(!son[u][c[i]-'a']) son[u][c[i]-'a']=++tot;
		u=son[u][c[i]-'a'];
	}
	return u;
}

inline void build(){
	queue <int> q;
	for(int i=0;i<26;i++)
		if(son[0][i]) fail[son[0][i]]=0,q.push(son[0][i]);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		int fil=fail[u];
		for(int i=0;i<26;i++){
			int v=son[u][i];
			if(!v) son[u][i]=son[fil][i];
			else fail[v]=son[fil][i],q.push(v);
		}
	}

	return ;
}

inline void init(int u){dfn[u]=++tm,sz[u]=1;for(int v:ed[u]) init(v),sz[u]+=sz[v];}

int pos;
int t[400005];
inline void add(int x,int k){while(x<=tm) t[x]+=k,x+=x&-x;return ;}
inline int ask(int x){int s=0;while(x) s+=t[x],x^=x&-x;return s;}

inline void dfs(int u){
	for(int v:q[u]) ans[v]=ask(dfn[it[v]]+sz[it[v]]-1)-ask(dfn[it[v]]-1);
	for(auto tmp:g[u]){
		int laspos=pos;
		for(int i=tmp.l;i<=tmp.r;i++) pos=son[pos][s[i]-'a'],add(dfn[pos],1);
		dfs(tmp.v);
		pos=laspos;
		for(int i=tmp.l;i<=tmp.r;i++) pos=son[pos][s[i]-'a'],add(dfn[pos],-1);
		pos=laspos;
	}
	return ;
}

int main(){
	in(n);
	for(int i=1;i<=n;i++){
		int op,u=0;
		in(op);
		if(op==2) in(u);
		scanf("%s",c+1);
		int l=cnt+1,len=strlen(c+1);
		for(int j=1;j<=len;j++) s[++cnt]=c[j];
		g[u].push_back({i,l,cnt});
	}
	in(m);
	for(int i=1;i<=m;i++){
		int x;
		in(x);
		scanf("%s",c+1);
		it[i]=insert();
		q[x].push_back(i);
	}
	build();
	for(int i=1;i<=tot;i++) ed[fail[i]].push_back(i);
	init(0);
	dfs(0);
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);

	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

经典送分 ACAM 题。

考虑给你一个文本串，如何快速求出多个模式串在其中出现的次数。

我们考虑把文本串在 ACAM 上匹配的过程中，想要匹配上某个模式串，必须不断跳 fail 指针。那么相当于把 fail 树上一条到根的链上的所有点的权值加一。这个转化为 DFS 序之后变成数据结构问题。（并不是用树链剖分加上，而是算贡献，给每个被匹配到的节点权值加一，查询的时候求 fail 树某个子树内所有点的权值和）可以用树状数组解决。

那么考虑本题。我们把题目中的两种字符串的生成方式看做和原始节点连边（特别地，$0$ 节点是空字符串。）那么我们把询问离线下来之后在操作树上遍历即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=4e5+10;
int n,m,tot,dfns,ar[MAXN],ans[MAXN],dfn[MAXN],sze[MAXN],fail[MAXN],tr[MAXN][27];
vector<pair<int,char>> G[MAXN];
vector<int> T[MAXN];
vector<pair<int,int>> qr[MAXN];
int insert(string S) {
	int u=0;
	for(auto ch:S) {
		if(tr[u][ch-'a']==0) tr[u][ch-'a']=++tot;
		u=tr[u][ch-'a'];
	}
	return u;
}
void build(void) {
	queue<int> q;
	ffor(i,0,25) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()) {
		int u=q.front(); q.pop();
		T[fail[u]].push_back(u);
		ffor(i,0,25) if(tr[u][i]) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
		else tr[u][i]=tr[fail[u]][i];	
	}
	return ;
}
void dfs(int u) {
	dfn[u]=++dfns,sze[u]=1;
	for(auto v:T[u]) dfs(v),sze[u]+=sze[v];
	return ;	
}
void update(int pos,int v) {
	while(pos<=dfns) ar[pos]+=v,pos+=pos&(-pos);
	return ;	
}
int query(int pos) {
	int ans=0; while(pos) ans+=ar[pos],pos-=pos&(-pos);
	return ans;
}
void solve(int u,int nd) {
	update(dfn[nd],1);
	for(auto pr:qr[u]) {
		int id=pr.second,v=pr.first;
		ans[id]=query(dfn[v]+sze[v]-1)-query(dfn[v]-1);
	}
	for(auto pr:G[u]) {
		int to=pr.first; char ch=pr.second;
		int Nd=tr[nd][ch-'a'];
		solve(to,Nd);
	}
	update(dfn[nd],-1);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {
		int op,id; char ch;
		cin>>op;
		if(op==1) cin>>ch,G[0].push_back({i,ch});
		else cin>>id>>ch,G[id].push_back({i,ch});
	}
	cin>>m;
	ffor(i,1,m) {
		int q; string S;
		cin>>q>>S;
		int id=insert(S);
		qr[q].push_back({id,i});
	}
	build(),dfs(0);
	solve(0,0);
	ffor(i,1,m) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：GavinZheng (赞：1)

# CF1207G Indie Album

一道很有意思的AC自动机好题。

AC自动机的本质是记录了一棵字典树上所有字符串的所有后缀，所以这道题我们可以充分利用这个性质。

这道题与板子题的不同之处就在于：文本串在不停的变化，每次增加一个字符。

我们先来复习一下AC自动机模版题的流程

1. 遍历文本串的所有前缀。
2. 将所有是这个前缀的后缀的模式串出现次数+1。（即沿着fail指针一直走到根，沿途的所有节点都是符合条件的）

而对于这道题，因为文本串每次只会添加一个字符。所以我们在上一个文本串的基础上，加入以当前节点到根组成的字符串的贡献即可。

那这道题的解决方案就比较清晰了：

我们将字符串$s$定义为当前字典树节点到根的所有节点组成的字符串，文本串$s$对应的模式串出现次数的记为$t[s]$，将文本串$s$对应的答案记为$ans[s]$

1. 建出一个文本串组成的字典树。
2. 对字典树进行DFS，每走到一个节点，将所有为s后缀的字符串的出现次数$t$加1。
3. 记录答案$ans[s]=t[s]$。
4. DFS回溯时，将所有为s后缀的字符串的出现次数$t$减1。

因为所有字符串长度和$T$的大小关系，$T^2$算法是过不了的。但是因为累计答案是在$fail$指针构成的树，所以我们可以用数据结构来维护这个东西。复杂度变成了$T\log T$。

个人感觉这道题的关键在于利用AC自动机“求解单文本串问题时会遍历文本串的所有前缀”这个性质，从而求解特殊的多文本串问题。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#define ll long long
#define maxn (int)(4*1e5+1000)
using namespace std;
int ans[maxn],ch[maxn][30],tr[maxn][30],c[maxn],queue[maxn],n,m,now_insert,tcnt,acnt,fcnt,ver_tr[maxn],fail[maxn],size[maxn],id[maxn];//id指在ac自动机上的点在fail树上的编号
bool is_end[maxn];
char s[10];
struct gg{
    int lo,id,mod_ed;string add;//版本和询问的模式串,以及模式串结尾位置在AC自动机上的编号
}query[maxn];
vector<int>tr_ver[maxn],fail_son[maxn];
vector<gg>so[maxn];//记录每个版本的询问
void change(int now,int num) {
    for(int i=now;i<=fcnt;i+=i&-i){c[i]+=num;}
}
int sum(int now) {
    int re=0;for(int i=now;i>=1;i-=i&-i){re+=c[i];}return re;
}
int insert_ac(string data) {
    int now=0;
    for(int i=0;i<data.size();i++) {
        int cha=data[i]-'a';
        if(!ch[now][cha])ch[now][cha]=++acnt;
        now=ch[now][cha];
    }
    is_end[now]=1;return now;
}
void build_ac() {
    int l=1,r=0;
    for(int i=0;i<30;i++)if(ch[0][i]){queue[++r]=ch[0][i];fail_son[0].push_back(ch[0][i]);}
    while(l<=r) {
        int now=queue[l];l++;
        for(int i=0;i<30;i++) {
            if(ch[now][i]) {
                queue[++r]=ch[now][i];
                fail[ch[now][i]]=ch[fail[now]][i];
                fail_son[ch[fail[now]][i]].push_back(ch[now][i]);
            }
            else ch[now][i]=ch[fail[now]][i];
        }
    }
}
void dfs1(int now) {
    id[now]=++fcnt;size[id[now]]=1;
    for(int i=0;i<fail_son[now].size();i++){dfs1(fail_son[now][i]);size[id[now]]+=size[id[fail_son[now][i]]];}
}
void update(int now,int num) {//更改AC自动机上now点所有儿子
    change(id[now],num);
}
void get_ans(gg data,int fail_now) {
    ans[data.id]=sum(fail_now+size[fail_now]-1)-sum(fail_now-1);
}
void dfs2(int tr_now,int ac_now) {
    if(tr_now) {
        update(ac_now, 1);//所有匹配的模式串加上1。
        for (int i = 0; i < tr_ver[tr_now].size(); i++) {//枚举以当前点结尾的所有版本
            int now_ver = tr_ver[tr_now][i];//现在的处理版本
            for (int j = 0; j < so[now_ver].size(); j++) {
                gg now_qu = so[now_ver][j];//现在处理的询问
                get_ans(now_qu,id[now_qu.mod_ed]);
            }
        }
    }
    for(int i=0;i<30;i++) {
        if(tr[tr_now][i]) {
            dfs2(tr[tr_now][i],ch[ac_now][i]);
        }
    }
    if(tr_now) {
        update(ac_now,-1);
    }
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        int ty;scanf("%d",&ty);
        if(ty==1) {
            scanf("%s",s);
            now_insert=0;
        }
        else {
            scanf("%d",&now_insert);now_insert=ver_tr[now_insert];scanf("%s",s);
        }
        int tar=s[0]-'a',now;
        if(!tr[now_insert][tar])tr[now_insert][tar]=++tcnt;
        now=tr[now_insert][tar];
        tr_ver[now].push_back(i);
        ver_tr[i]=now;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++) {
        scanf("%d",&query[i].lo);cin>>query[i].add;query[i].mod_ed=insert_ac(query[i].add);query[i].id=i;
        so[query[i].lo].push_back(query[i]);
    }
    build_ac();
    dfs1(0);
    dfs2(0,0);
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
}
```



---

