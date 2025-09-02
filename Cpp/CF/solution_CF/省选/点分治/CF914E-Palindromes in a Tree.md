# Palindromes in a Tree

## 题目描述

#### 题意

给你一颗 $n$ 个顶点的树（连通无环图）。顶点从 $1$ 到 $n$ 编号，并且每个顶点对应一个在 `a` 到 `t` 的字母。
树上的一条路径是回文是指至少有一个对应字母的排列为回文。

对于每个顶点，输出通过它的回文路径的数量。

注意：从 $u$ 到 $v$ 的路径与从 $v$ 到 $u$ 的路径视为相同，只计数一次。

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
3 5
abcbb
```

### 输出

```
1 3 4 3 3 
```

## 样例 #2

### 输入

```
7
6 2
4 3
3 7
5 2
7 2
1 4
afefdfs
```

### 输出

```
1 4 1 1 2 4 2 
```

# 题解

## 作者：Alex_Wei (赞：7)

> [CF914E Palindromes in a Tree 题目传送门](https://www.luogu.com.cn/problem/CF914E)。
>
> 题意简述：给一棵树，节点上有字符。对于每个点，求有多少条经过该点的路径满足该路径上出现奇数次的字符最多有 $1$ 个。
>
> $n\leq 2\times 10^5$，字符集大小为 $20$。
>
> 摘自 [简单树论](https://www.cnblogs.com/alex-wei/p/Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree.html) 点分治部分例题 VII。

话说这个标题有点误导人，一开始想严格意义上的回文串觉得很不可做。

---

树上路径统计，不难想到点分治，而判断最多有一个字符出现奇数次可以用状压。具体地，对于一个分治中心 $r$，用一个 $20$ 位二进制数统计它的所有子节点 $u$ 到 $r$（不包括 $r$）的路径上每个字符的出现次数的奇偶性，记为 $msk_u$。

同时，如果我们知道了有多少条路径以端点 $u$ 结尾并经过分治中心，设为 $p_u$，那么从 $u$ 到 $r$ 上的所有点（除了 $r$ 需要单独处理）都要加上 $p_u$。由于是离线所以使用树上差分即可。

对于每个 $u$，我们将**只到分治中心**的路径和**跨过分治中心**的路径分开来考虑，因为在**根节点** $r$ 处，**前者只会被计算一次，而后者会被计算两次**。记 $c=msk_u\oplus 2^{s_r}$。

- 只到分治中心：如果存在 $k$ 使得 $c\oplus 2^k=0$ 或 $c$ 本身就为 $0$，那么路径 $(u,r)$ 是合法的。将 $p_u$ 和 $ans_r$ 增加 $1$。
- 跨过分治中心：枚举出现次数为奇数的字符 $k$，对于所有使得 $c\oplus 2^k\oplus msk_v=0$（**即 $c\oplus 2^k=msk_v$**）的 $v$，$(u,v)$ 都是一条合法路径，可以通过用**两个桶**分别记录**在整棵 $r$ 的子树内 和 在当前点 $u$ 所在的子树中**（为了除去不经过分治中心的答案）$msk_v=x$ 的 $v$ 数量，分别记为 $buc1_x$ 和 $buc2_x$，那么 $v$ 的数量即为 $buc1_{c\oplus k}-buc2_{c\oplus k}$。不要忘记考虑没有出现次数为奇数的情况。

综上，我们有了一个 $\mathcal{O}(n\log n\mathbf|Σ|)$ 的算法：点分治，统计答案时枚举 $i=0$ 和 $i=2^k$，记 $c=msk_u\oplus 2^{s_r}\oplus i$。若 $c=0$，则将标记记为 $1$。同时将 $p_u$ 加上 $buc1_c-buc2_c$。枚举结束后，若标记为 $1$，则将 $p_u$ 和 $ans_r$ 都加上 $1$。最后使用树上差分统计**非分治中心的所有节点**对答案的贡献。

记得将桶清零。此外，不需要在一开始将 $buc1_0$ 设为 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define db double
#define ll long long
#define ld long double
#define ull unsigned long long

#define pii pair <int,int>
#define fi first
#define se second
#define pb emplace_back
#define mem(x,v,s) memset(x,v,sizeof(x[0])*(s))
#define cpy(x,y,s) memcpy(x,y,sizeof(x[0])*(s))

const int N=2e5+5;
const int S=20;

int n,vis[N];
char s[N];
vector <int> e[N];

ll ans[N],buc[1<<S],insi[1<<S],p[N];
vector <pii> res[N];
int root,mx[N],sz[N];

void findr(int id,int f,int tot){
	mx[id]=sz[id]=1;
	for(int it:e[id])
		if(it!=f&&!vis[it]){
			findr(it,id,tot),sz[id]+=sz[it];
			mx[id]=max(mx[id],sz[it]);
		}
	mx[id]=max(mx[id],tot-sz[id]);
	if(mx[id]<mx[root])root=id;
}
void presum(int id,int f){
	for(int it:e[id])
		if(it!=f&&!vis[it])
			presum(it,id),
			p[id]+=p[it];
	if(f)ans[id]+=p[id];
}
void calc(int id,int f,int pre,int anc){
	res[anc].pb((pii){pre^=(1<<s[id]-'a'),id}),p[id]=0;
	for(int it:e[id])if(it!=f&&!vis[it])calc(it,id,pre,anc);
}
void divide(int id){
	int msk=1<<s[id]-'a';
	vis[id]=1,p[id]=0;
	for(int it:e[id])
		if(!vis[it]){
			res[it].clear(),calc(it,id,0,it);
			for(pii c:res[it])buc[c.fi]++;
		}
	ll sum=0;
	for(int it:e[id]){
		if(vis[it])continue;
		for(pii c:res[it])insi[c.fi]++;
		for(pii c:res[it]){
			bool have=0;
			for(int k=-1;k<20;k++){
				int msk2=(k<0?0:1<<k),r=c.fi^msk^msk2;
				if(!r)have=1;
				ll d=buc[r]-insi[r];
				sum+=d,p[c.se]+=d;
			} if(have)p[c.se]++,ans[id]++;
		} for(pii c:res[it])insi[c.fi]=0;
	} presum(id,0),ans[id]+=sum>>1,assert(sum%2==0);
	for(int it:e[id])for(pii c:res[it])buc[c.fi]=0;
	for(int it:e[id])if(!vis[it])root=0,findr(it,id,sz[it]),divide(root);
}


int main(){
	cin>>n,mx[0]=n+1;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		e[u].pb(v),e[v].pb(u);
	} scanf("%s",s+1);
	findr(1,0,n),divide(root);
	for(int i=1;i<=n;i++)cout<<ans[i]+1<<" ";
	cout<<endl;
	return 0;
}
```





---

## 作者：Masterwei (赞：2)

题解怎么都是点分治，来一个 `dsu on tree`。

由于字符可以重排，所以显然一条路径是回文路径的充要条件是至多只有一种字符出现的次数为奇数。

由于字符集只有 $20$，所以可以直接状压。

接着考虑 `dsu on tree`，假设我们在点 $u$，那么对于 $u$ 的轻儿子的子树中的点，我们可以直接暴力去算贡献并差分，难点在于重儿子的贡献怎么办。

其实每个轻儿子的子树中的点都对应着至多 $21$ 种权值与其产生贡献。那么我们直接再次差分，开个 vector 将贡献挂在重儿子上即可。

我常数写得并不优秀，但是单个测试点依旧可以比普通点分治做法快 $1$ 秒以上。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
  int x=0;bool f=0;char ch=getchar();
  while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
  while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
  return f?-x:x;
}
const int Maxn=2e5+5;
int n;
int head[Maxn],to[Maxn<<1],nxt[Maxn<<1],cnt1;
inline void add(int u,int v){
	to[++cnt1]=v;nxt[cnt1]=head[u];
	head[u]=cnt1;
}
char s[Maxn];
int f[Maxn];
int a[Maxn],b[Maxn];
ll sum[(1<<20)+5];
ll ans[Maxn];

struct node{
	ll cnt,val;
};
vector<node>cf[Maxn];
int si[Maxn],dfn[Maxn],cnt2,son[Maxn];
void dfs1(int u,int v){
	f[u]=v;
	dfn[u]=++cnt2;si[u]=1;
	a[u]=(a[v]^(1<<(s[u]-'a')));
	b[cnt2]=u;
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v)continue;
		dfs1(y,u);if(si[son[u]]<si[y])son[u]=y;
		si[u]+=si[y];
	}
}
inline void calc(int u,int val){//dui yu zhong erzi dan du suan
	if(!son[u])return;
	int tp=(1<<(s[u]-'a'));
	for(int i=0;i<20;i++){
		if(!sum[(val^(1<<i)^tp)])continue;
		cf[son[u]].push_back({1,(val^(1<<i)^tp)});
		ans[u]-=sum[(val^(1<<i)^tp)];
	}
	if(!sum[(val^tp)])return;
	cf[son[u]].push_back({1,(val^tp)});
	ans[u]-=sum[(val^tp)];
}
inline void add_1(int u,int x){
	ll tp=0,tpp=(1<<(s[u]-'a'));
	for(int i=0;i<20;i++)tp+=sum[(a[x]^(1<<i)^tpp)];
	tp+=sum[(a[x]^tpp)];
	ans[x]+=tp;
	ans[u]-=tp;
}
inline void add_1_(int u,int x){
	ll tp=0,tpp=(1<<(s[u]-'a'));
	for(int i=0;i<20;i++)tp+=sum[(a[x]^(1<<i)^tpp)];
	tp+=sum[(a[x]^tpp)];
	ans[x]-=tp;
	ans[u]+=tp;
}
inline void add_2(int u,int x){
	ll tp=0,tpp=(1<<(s[u]-'a'));
	for(int i=0;i<20;i++)tp+=sum[(a[x]^(1<<i)^tpp)];
	tp+=sum[(a[x]^tpp)];
	ans[x]+=tp;
	ans[f[u]]-=tp;
}
void dfs(int u,int v,int op){
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v||y==son[u])continue;
		dfs(y,u,0);
	}if(son[u])dfs(son[u],u,1);
	calc(u,a[u]);
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==son[u]||y==v)continue;
		for(int j=dfn[y];j<dfn[y]+si[y];j++)calc(u,a[b[j]]),add_1_(u,b[j]);
	}
	add_1(u,u);sum[a[u]]++;
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==son[u]||y==v)continue;
		for(int j=dfn[y];j<dfn[y]+si[y];j++)add_1(u,b[j]);
		for(int j=dfn[y];j<dfn[y]+si[y];j++)sum[a[b[j]]]++;
	}
	sum[a[u]]--;add_2(u,u);
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==son[u]||y==v)continue;
		for(int j=dfn[y];j<dfn[y]+si[y];j++)sum[a[b[j]]]--;
		for(int j=dfn[y];j<dfn[y]+si[y];j++)add_2(u,b[j]);
	}
	if(!op){
		for(int i=dfn[son[u]];i<dfn[son[u]]+si[son[u]];i++)sum[a[b[i]]]--;
	}
	else{
		sum[a[u]]++;
		for(int i=head[u];i;i=nxt[i]){
			int y=to[i];if(y==son[u]||y==v)continue;
			for(int j=dfn[y];j<dfn[y]+si[y];j++)sum[a[b[j]]]++;
		}
	}
}
void dfs2(int u,int v){
	for(node it:cf[u])sum[it.val]+=it.cnt;
	ans[u]+=sum[a[u]];
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v)continue;
		dfs2(y,u);ans[u]+=ans[y];
	}
	for(node it:cf[u])sum[it.val]-=it.cnt;
}
signed main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}scanf("%s",s+1);
	dfs1(1,0);
	dfs(1,0,0);
	memset(sum,0,sizeof sum);
	dfs2(1,0);
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]+1);puts("");
	return 0;
}
```

---

## 作者：luckydrawbox (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF914E)

## 题意

转化版题意。

>给你一颗 $n$ 个顶点的树，顶点从 $1$ 到 $n$ 编号，并且每个顶点对应一个在 ``a`` 到 ``t`` 的字母。 求经过每个节点的至多有一个字母的数量为奇数的路径的个数。
>
>注意：从 $u$ 到 $v$ 的路径与从 $v$ 到 $u$ 的路径视为相同，只计数一次。

## 分析

``a`` 到 ``t`` 有 $20$ 个字母，于是我们可以状压一下，每一位代表该字母数量是奇是偶，而维护路径的个数不难想到点分治，设 $d_x$ 表示当前分治中心 $pos$ 到点 $x$ 的路径上的字母数量状压后的结果，则一条路径 $x \Leftrightarrow y$ 符合要求仅当 $d_x\oplus d_y \oplus d_{pos}=0\lor2^j(0\le j<20)$。

对于一条路径，我们把它拆成 $x \Leftrightarrow pos,pos \Leftrightarrow y$ 两部分，这样我们只要对半边的路径计数即可，具体地，计算 $x \Leftrightarrow pos$ 的贡献时，给 $x \Leftrightarrow pos$ 上的每一个点加上当前分治中心的全局中 $(d_y=2^j\oplus d_x \oplus d_{pos}) \lor (d_y=0 \oplus d_x \oplus d_{pos})$ 的数量，但这样统计会重复加上当前子树中 $(d_y=2^j\oplus d_x \oplus d_{pos}) \lor (d_y=0 \oplus d_x \oplus d_{pos})$ 的数量，所以再统计当前子树中的数量，提前减去即可。

但是还是有缺陷，首先，路径端点在分治中心的不同子树时分治中心 $pos$ 的答案会被算两次，最后特判下除以 $2$ 即可；其次，这样的做法只统计了路径端点在分治中心的不同子树时的答案，但还有以分治中心为端点，另一端在子树内的答案和整个路径只有分治中心的答案，对于前者，特判计算即可，对于后者，最后输出答案时加 $1$ 即可。

但值得注意的是，分治中心的答案除以 $2$ 时不能把以分治中心为端点的除了，于是要在前面的特判中多记一个变量表示以分治中心为端点的路径的个数，对分治中心的答案加上此再除以 $2$ 就没问题了。

分治过程中涉及到树上路径增加的操作，用树上差分就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=2e5+10,M=4e5+10,K=1.2e6+10;
int head[M],ver[M],nxt[M],tot,Fa[N];
int n,pos,mx,sze[N],v1[N],d[N],f[K],f2[K],e1[N],e2[N],t1,t2;
ll sum[N],sum2;
ll ans[N],rans[N];
string s;
void add(int x,int y){
	ver[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int S){
	v1[x]=sze[x]=1;
	int mx_part=0;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(v1[y]==1||v1[y]==3)
			continue;
		dfs(y,S);
		sze[x]+=sze[y];
		mx_part=max(mx_part,sze[y]);
	}
	mx_part=max(mx_part,S-sze[x]);
	if(mx_part<mx){
		mx=mx_part;
		pos=x;
	}
}
void dfs2(int x,int fa){
	v1[x]=2;
	Fa[x]=fa;
	d[x]=d[fa]^(1<<(s[x-1]-'a'));
	e2[++t2]=x;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(v1[y]==2||v1[y]==3)
			continue;
		dfs2(y,x);
	}
}
void dfs3(int x,int F){
	v1[x]=0;
	sum[x]=rans[x];
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(!v1[y]||v1[y]==3)
			continue;
		dfs3(y,0);
		sum[x]+=sum[y];
	}
	if(F)
		sum[x]=(sum[x]+sum2)/2;
	ans[x]+=sum[x];
}
void add(int x,int y,int v){
	rans[Fa[x]]-=v;
	rans[y]+=v;
}
void calc(int x){
	t1=sum2=Fa[x]=0;
	v1[x]=2;
	d[x]=(1<<(s[x-1]-'a'));
	for(int i=head[x];i;i=nxt[i]){
		if(v1[ver[i]]==3)
			continue;
		t2=0;
		dfs2(ver[i],x);
		for(int j=1;j<=t2;j++){
			e1[++t1]=e2[j];
			f[d[e2[j]]]++;
			f2[d[e2[j]]]++;
		}
		for(int j=1,a;j<=t2;j++){
			a=0;
			a+=f2[d[e2[j]]^d[x]];
			for(int u=0;u<20;u++)
				a+=f2[d[e2[j]]^(1<<u)^d[x]];
			add(x,e2[j],-a);
			
		}
		for(int j=1;j<=t2;j++)
			f2[d[e2[j]]]--;
	}
	for(int i=1,a;i<=t1;i++){
		a=0;
		a+=f[d[e1[i]]^d[x]];
		if(!d[e1[i]])
			a++,sum2++;
		for(int j=0;j<20;j++){
			a+=f[d[e1[i]]^(1<<j)^d[x]];
			if(d[e1[i]]==(1<<j))
				a++,sum2++;
		}
		add(x,e1[i],a);
	}
	dfs3(x,1);
	rans[0]=v1[x]=0;
	for(int i=1;i<=t1;i++){
		f[d[e1[i]]]--;
		rans[e1[i]]=0;
	}
}
void DFZ(int x,int S){
	mx=1e9;pos=0;
	dfs(x,S);
	int mxpos=pos;
	calc(pos);
	v1[pos]=3;
	for(int i=head[mxpos];i;i=nxt[i]){
		int y=ver[i];
		if(v1[y]==3)
			continue;
		DFZ(y,sze[y]);
	}
}
int main(){
	n=read();
	for(int i=1,u,v;i<n;i++){
		u=read();v=read();
		add(u,v);
		add(v,u);
	}
	cin>>s;
	DFZ(1,n);
	for(int i=1;i<=n;i++){
		write(ans[i]+1);
		putchar(' ');
	}
	return 0;
}
```


---

## 作者：yqr123YQR (赞：2)

### 分析
由于字符集大小只有 $20$，考虑状压。

统计路径信息，考虑点分治。

假设已经求好其余点分别到当前重心 $rt$ 的路径异或和，并存在 `dist` 中。考虑路径经过 $rt$ 的贡献如何算：

1. $rt$ 为一端点

   直接将满足 $\operatorname{popcount}(dist_i)\leqslant1$ 的 $i$ 的个数统计，单独加在 $rt$ 上。
2. $rt$ 非端点

   容易想到，在挨个遍历子树时，对于每个子树，算出子树内的 `dist[i]` 与之前的子树的 `dist` 匹配的方案数，加在路径 $i\rightsquigarrow rt$ 上。
   
   但是，这会导致前面的路径若被后面的路径匹配，其贡献并没有计算在内。类似地，我们可以倒序遍历，以同样的方法计算。

最后说统计贡献的问题：题目中的贡献为“链加单点查”，且只在最后输出，满足树上差分的要求。

### 注意事项
不知为何，直接倒序遍历，第 $5$ 个点就会 `TLE`，但别的题解就不会。此时可以将各子树的 `dist` 合并，并用 `vector<int> p` 记录分割点，倒叙时就不必再次求 `dist` 了。
### 代码
```cpp
//......
void calcsize(int k, int fa, int mode) {}//算子数大小及重心
void calcdist(int k, int fa, int value) {}//求出上文的 dist
void devide(int k)
{
	del[k] = true;
	ll tot = 0;
	int lastcnt = 0;
	for(int i : g[k])
	{
		if(del[i]) continue;
		calcdist(i, -1, (1 << s[i]) ^ (1 << s[k]));
		for(int j = lastcnt + 1; j <= cnt; j++)
		{
			if(popcount(dist[j]) <= 1) modify(st[j], k, 1);//, printf("I %d to %d:1\n", st[j], k, 1);
			ll tmp = vis[dist[j] ^ (1 << s[k])];
			for(int p = 0; p < 20; p++) tmp += vis[(1 << p) ^ (1 << s[k]) ^ dist[j]];
			modify(st[j], k, tmp), tot += tmp;//, printf("II %d to %d:%d\n", st[j], k, tmp);
		}
		for(int j = lastcnt + 1; j <= cnt; j++) vis[dist[j]]++;
		p.push_back(lastcnt + 1);//记录分割点
		lastcnt = cnt;
	}
	modify(k, k, -tot);//单独为 rt 累加贡献
	for(int i = 1; i <= cnt; i++) vis[dist[i]]--;
	int en = cnt;
	for(int ii = (int) p.size() - 1; ~ii; ii--)
	{
		int i = p[ii];
		for(int j = i; j <= en; j++)
		{
			int tmp = vis[dist[j] ^ (1 << s[k])];
			for(int p = 0; p < 20; p++) tmp += vis[(1 << p) ^ (1 << s[k]) ^ dist[j]];
			modify(st[j], k, tmp);//, printf("II %d to %d:%d\n", st[j], k, tmp);
		}
		for(int j = i; j <= en; j++) vis[dist[j]]++;
		en = i - 1;
	}
	for(int i = 1; i <= cnt; i++) vis[dist[i]]--;
	cnt = 0;
	p.clear();
	for(int i : g[k])
	{
		if(del[i]) continue;
		rtmx = nown = sz[i];
		calcsize(i, -1, 1);
		calcsize(rt, -1, 0);
		devide(rt);
	}
}
int main()
{
	//init......
	calcsize(1, -1, 1);
	calcsize(rt, -1, 0);
	devide(rt);
	query(1);
	for(int i = 1; i <= n; i++) printf("%lld ", sum[i] + 1);//+1 是因为包含单点的情况
	return 0;
}
```

---

## 作者：Styx (赞：2)

首先是一个结论   
本题要求路径的某个排列为回文串，很显然，路径上最多有一个字母出现奇数次。只需要记录奇偶性显然可以用状压去解决。  
根据这个结论，我们可以推出对于一个点u，他到某个点v的路径如果满足条件，显然状压的数字等于0或者1<<i(i<=19)，这个时候可以考虑搞出一个中点k，于是问题等价于dis(u,k)^dis(v,k)等于0或者1<<i(i<=19)   
这显然是点分治的思路   
考虑点分治中的暴力怎么写：首先对于重心进行dfs，求出所有点到重心的dis，dis表示路径上个字母的奇偶性，并且记录$dis_i$的数量。   
接着对于每棵子树将该子树对所有dis的数量贡献全部去掉，再对该子树进行dfs，对于每个点的dis，统计与他异或等于0或者1<<i(i<=19)的数量，即为该点贡献答案，值得注意的是，经过该点的路径一定经过其父节点，因为是从另一颗子树中跑过来的，所以在dfs返回的时候应该给父节点加上子节点的贡献。接着把该子树的dis全部加回去跑下一棵子树。  
因为每个点本身都是一个回文串，所以最后答案要加一。
代码如下：

```CPP
#include<map>
#include<set>
#include<queue>
#include<cmath>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define poi void
#define int long long
using namespace std;

vector<int> g[200010];
char c[200010];
int n,ans[200010],a[200010],size[200010],vis[200010],f[200010],tmp[(1<<20)|10]; 

poi get_size(int now,int fa)
{
	size[now]=1;
	f[now]=fa;
	for(int i=0;i<g[now].size();i++)
	{
		if(vis[g[now][i]]||g[now][i]==fa) continue;
		get_size(g[now][i],now);
		size[now]+=size[g[now][i]];
	}
}

int get_zx(int now,int fa)
{
	if(size[now]==1) return now;
	int son,maxson=-1;
	for(int i=0;i<g[now].size();i++)
	{
		if(vis[g[now][i]]||g[now][i]==fa) continue;
		if(maxson<size[g[now][i]])
		{
			maxson=size[g[now][i]];
			son=g[now][i];
		}
	}
	int zx=get_zx(son,now);
	while(size[zx]<2*(size[now]-size[zx])) zx=f[zx];
	return zx;
}

poi get(int now,int fa,int sta,int kd)
{ 
    sta^=(1<<a[now]);
	tmp[sta]+=kd;
	for(int i=0;i<g[now].size();i++)
	{
		if(vis[g[now][i]]||g[now][i]==fa) continue;
		get(g[now][i],now,sta,kd);
	}
}

int calc(int now,int fa,int sta)
{
	sta^=(1<<a[now]);
	int num=tmp[sta];
	for(int i=0;i<=19;i++)
	{
		num+=tmp[sta^(1<<i)];
	}
	for(int i=0;i<g[now].size();i++)
	{
		if(vis[g[now][i]]||g[now][i]==fa) continue;
		num+=calc(g[now][i],now,sta);
	}
	ans[now]+=num;
	return num;
}

poi solve(int now)
{
	vis[now]=1;
	get(now,0,0,1);
	long long num=tmp[0];
	for(int i=0;i<=19;i++)
	{
		num+=tmp[1<<i];
	}
	for(int i=0;i<g[now].size();i++)
	{
		if(vis[g[now][i]]) continue;
		get(g[now][i],0,1<<a[now],-1);
		num+=calc(g[now][i],0,0);
		get(g[now][i],0,1<<a[now],1);
	}
	ans[now]+=num/2;
	get(now,0,0,-1);
	for(int i=0;i<g[now].size();i++)
	{
		if(vis[g[now][i]]) continue;
		get_size(g[now][i],0);
		int zx=get_zx(g[now][i],0);
		solve(zx);
	}
}

signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
	{
		int from,to;
		scanf("%lld%lld",&from,&to);
		g[from].push_back(to);
		g[to].push_back(from);
	}
	scanf("%s",c+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=c[i]-'a';
	}
	solve(1);
	for(int i=1;i<=n;i++)
	{
		printf("%lld ",ans[i]+1);
	}
}

```

---

## 作者：Zhangikun (赞：1)

## 思路
根据回文串的性质，我们把路径的要求转换为：

路径上每种点权最多一种点权数量为奇数个。

例如：$3$ 个 `x`，$4$ 个 `y` 是合法的，$2$ 个 `x`，$6$ 个 `y` 是合法的,$3$ 个 `x`，$5$ 个 `y` 是不合法的。

暴力一点的做法：使用点分治，对于分治中心 $cur$，深搜递归到点 $x$ 时，有以下几种答案统计。

假如我们走到 $x$ 会用一个桶 $cnt$，$cnt_i$ 表示 `a~z` 中第 $i+1$ 个字母的个数模上 $2$。

1. 如果从 $cur$ 递归到点 $y$ 时的 $cnt$ 内值和递归到 $x$ 时的 $cnt$ 一样，那么 $(x,y)$ 是我们要找的路径。
2. 如果从 $cur$ 递归到点 $y$ 时的 $cnt$ 内值和递归到 $x$ 时的 $cnt$ 只存在一个 $cnt_i$ 不同，那么 $(x,y)$ 也是我们要找的路径。
3. 如果从 $cur$ 递归到 $x$，$cnt$ 内部全是 $0$，那么 $(cur,x)$ 是我们要找的路径。
4. 如果从 $cur$ 递归到 $x$，$cnt$ 内部只有一个 $cnt_i=1$，那么 $(cur,x)$ 也是我们要找的路径。

但是这题问的并非合法路径数，而是问经过每个点的合法路径数，所以我们要用另一种技术方法：

我们假定变量 $ans$ 为合法路径数，假如从分治中心 $cur$ 递归到点 $now$，在 $now$ 递归下去之前会给方案数加上以上 $4$ 种贡献，对吧。

我们在它加上贡献前，定义变量 $lst$ 作为 $now$ 算贡献前的 $ans$，那么在递归之后，$ans$ 会随着 $now$ 的后代 $nxt$ 变化，此时经过 $now$ 的路径数会加上 $ans-lst$。

但是这样有问题：

1. 我怎么知道哪些 $cnt$ 和当前一样或不一样？

我们注意到这题仅有 $20$ 种字母，我们可以把 $cnt_i$ 抽象成一个二进制数 $val$ 的第 $i+1$ 位，这一位的单位是 $2^i$。那么我们就可以把 $val$ 用桶存起来比较啦，说得专业点就是状态压缩。

2. 我们点分治时，每个 $cur$ 得子树的贡献都来自前面，那么前面作贡献的子树不就会少算答案吗？

确实是这样的，所以我们做两遍：一遍正着算，一遍反着算。

**但不是所有贡献都要算两遍的！！！**

第 $3$ 和第 $4$ 种贡献是不能算两遍的，否则答案会多算（这个很好理解吧）。

最后，最重要的：
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int cxk=2e5+5,cln=(1<<21);
int cnt[cln],tot,tot2=1,dis[cxk],n,k,sz[cxk],ctr,ans,out[cxk];
//cnt[i]表示文中的一种cnt在状压状态下作下标i（即val）的数量
//out[i]表示通过自己的合法路径数 
bool del[cxk];//del[cur]表示cur是否被删去（点分治专用） 
char c[cxk];//点权 
vector<int>nbr[cxk];//邻接表 
void dfs(int cur,int fa)//找重心 
{
	sz[cur]=1;
	int maxi=0;
	for(int nxt:nbr[cur])
	{
		if(nxt==fa||del[nxt])
			continue;
		dfs(nxt,cur);
		if(ctr!=-1)
			return;
		maxi=max(maxi,sz[nxt]);
		sz[cur]+=sz[nxt];
	}
	maxi=max(maxi,n-sz[cur]);
	if(maxi<=n/2)
	{
		ctr=cur;
		sz[fa]=n-sz[cur];
	}
}
void dfs2(int cur,int fa,int val,int gr)//统计答案 
{//val是路径(cur,x)，所以需要(cur的儿子兼y的祖先,y)来凑 
	int lst=ans;
	for(int i=0;i<20;i++)
		ans+=cnt[val^(1<<i)];
	dis[++tot]=(val^(1<<(c[gr]-'a')));//删去分治中心的点权 
	ans+=cnt[val];
	for(int nxt:nbr[cur])
	{
		if(nxt==fa||del[nxt])
			continue;
		dfs2(nxt,cur,val^(1<<(c[nxt]-'a')),gr);
	}
	out[cur]+=ans-lst;
}
void run(int cur)
{
	cnt[0]=1;//如果cnt[0]=1，那么第3、4种贡献会加上 
	int lst=ans;
	for(int nxt:nbr[cur])//正序递归 
	{
		if(del[nxt])
			continue;
		dfs2(nxt,cur,(1<<(c[nxt]-'a'))^(1<<(c[cur]-'a')),cur);
		for(;tot2<=tot;tot2++)
			cnt[dis[tot2]]++;
	}
	for(int i=1;i<=tot;i++)
		cnt[dis[i]]--;
	tot=0;
	tot2=1;
	out[cur]+=ans-lst;
	ans=lst;
	cnt[0]=0;//如果cnt[0]=0，那么第3、4种贡献不会加上 
	for(int i=nbr[cur].size()-1;i>=0;i--)//倒叙递归 
	{
		int nxt=nbr[cur][i];
		if(del[nxt])
			continue;
		dfs2(nxt,cur,(1<<(c[nxt]-'a'))^(1<<(c[cur]-'a')),cur);
		for(;tot2<=tot;tot2++)
			cnt[dis[tot2]]++;
	}
	for(int i=1;i<=tot;i++)
		cnt[dis[i]]--;
	tot=0;
	tot2=1;
	del[cur]=1;
	for(int nxt:nbr[cur])//找别的分治中心 
	{
		if(del[nxt])
			continue;
		n=sz[nxt];
		ctr=-1;
		dfs(nxt,0); 
		run(ctr);
	}
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	int n1=n;
	for(int i=1,x,y;i<n;i++)
	{
		cin>>x>>y;
		nbr[x].push_back(y);
		nbr[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		cin>>c[i];
	ctr=-1;
	dfs(1,0);
	run(ctr);
	for(int i=1;i<=n1;i++)
		cout<<out[i]+1<<" ";//可以自己连自己，所以+1 
}
```

---

## 作者：happybob (赞：1)

一个经典套路是，一个字符串如果重排后可以变成回文，那么其充要条件是出现次数为奇数的字符不超过 $1$ 个。证明显然。

注意到题目的字符集是 a 到 t，这之间总共 $20$ 个字符。我们只关心一个字符的出现次数的奇偶性，而非具体值。也就是说，$3$ 和 $5$ 本质等价。不妨考虑状态压缩，每一位储存这个字符出现次数取模 $2$ 的结果。

然后就可以愉快点分治了。设 $dis_u$ 表示 $u$ 到分治中学的路径的上述状态压缩的结果。容易发现，两条路径拼接相当于两个值异或，对于 $a \oplus b = c$，那么 $b = c \oplus a$。对于每个点，枚举 $c$，容易知道 $c$ 是 $popcount(c) \leq 1$ 的所有数，可以约 $20$ 次暴力枚举。然后套上两点路径上每个点点权 $+k$ 的做法，就可以做到 $O(n \log^2 n)$。

注意两条路径合并，分治重心是唯一一个贡献错误的点，需要重新计算。

```cpp
// LUOGU_RID: 123808133
#pragma GCC optimize("-Ofast,fast-math,-inline")
#pragma GCC target("avx,sse,sse2,sse3,popcnt")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
using namespace std;

#ifndef ONLINE_JUDGE
#define __builtin_popcount __popcnt

#endif // !ONLINE_JUDGE

const int N = 2e5 + 5, M = 2e6 + 5;

char c[N];
int n;
vector<int> G[N];

class SegmentTree
{
public:
	long long cf[N], ans[N];
	void update(int l, int r, long long v)
	{
		cf[l] += v;
		cf[r + 1] -= v;
	}
	void getans()
	{
		for (int i = 1; i <= n; i++) ans[i] = ans[i - 1] + cf[i];
	}
};

class TreeCut
{
public:
	int dep[N], fa[N], sz[N], son[N], top[N], id[N], idx;
	SegmentTree sgt;
	void dfs1(int u, int f)
	{
		dep[u] = dep[f] + 1;
		fa[u] = f;
		sz[u] = 1;
		for (auto& j : G[u])
		{
			if (j ^ f)
			{
				dfs1(j, u);
				sz[u] += sz[j];
				if (sz[son[u]] < sz[j]) son[u] = j;
			}
		}
	}
	void dfs2(int u, int f)
	{
		top[u] = f;
		id[u] = ++idx;
		if (!son[u]) return;
		dfs2(son[u], f);
		for (auto& j : G[u])
		{
			if ((j ^ son[u]) && (j ^ fa[u])) dfs2(j, j);
		}
	}
	void build()
	{
		dfs1(1, 1);
		dfs2(1, 1);
		//sgt.build(1, 1, n);
	}
	void update(int u, int v, long long k)
	{
		//cout << "!!: " << u << " " << v << " " << k << "\n";
		if (!k) return;
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			sgt.update(id[top[u]], id[u], k);
			u = fa[top[u]];
		}
		if (dep[u] > dep[v]) swap(u, v);
		sgt.update(id[u], id[v], k);
	}
}tc;

int p[N];
long long cnt[M];
int cur;
vector<int> v[N], vv[N];

int sz[N];
bool del[N];
int tot, wc;

void get_size(int u, int f)
{
	sz[u] = 0;
	if (del[u]) return;
	sz[u] = 1;
	for (auto& j : G[u])
	{
		if (j ^ f) get_size(j, u), sz[u] += sz[j];
	}
}

void calc_wc(int u, int f)
{
	if (del[u]) return;
	int maxn = tot - sz[u];
	for (auto& j : G[u])
	{
		if (j ^ f)
		{
			calc_wc(j, u);
			maxn = max(maxn, sz[j]);
		}
	}
	if (maxn <= (tot >> 1)) wc = u;
}

long long nc = 0;

void dfs(int u, int f)
{
	if (del[u]) return;
	p[u] = p[f] ^ (1 << (c[u] - 'a'));
	cnt[p[u]]++;
	v[cur].emplace_back(u);
	if (v[cur].size() == 1) vv[cur].emplace_back(u);
	for (auto& j : G[u])
	{
		if (j ^ f) dfs(j, u);
	}
}

long long res[N];

void solve(int u)
{
	if (del[u]) return;
	get_size(u, 0);
	nc = 0;
	tot = sz[u];
	cur = 0;
	wc = 0;
	calc_wc(u, 0);
	u = wc;
	del[u] = 1;
	p[u] = (1 << (c[u] - 'a'));
	//cnt[p[u]]++;
	for (auto& j : G[u])
	{
		if (del[j]) continue;
		cur++;
		v[cur].clear();
		vv[cur].clear();
		dfs(j, u);
	}
	int ncur = 0;
	for (auto& j : G[u])
	{
		if (del[j]) continue;
		ncur++;
		for (auto& j : v[ncur])
		{
			cnt[p[j]]--;
		}
		for (auto& j : v[ncur])
		{
			if (__builtin_popcount(p[j]) <= 1)
			{
				tc.update(u, j, 1LL);
			}
			for (int i = 0; i < 20; i++)
			{
				int g = (1 << i);
				int k = (g ^ p[j]) ^ (1 << (c[u] - 'a'));
				if (cnt[k] > 0)
				{
					nc += cnt[k];
					tc.update(vv[ncur][0], j, cnt[k]);
				}
			}
			int g = 0;
			int k = (g ^ p[j]) ^ (1 << (c[u] - 'a'));
			if (cnt[k] > 0)
			{
				nc += cnt[k];
				tc.update(vv[ncur][0], j, cnt[k]);
			}
		}
		for (auto& j : v[ncur])
		{
			cnt[p[j]]++;
		}
	}
	for (int i = 1; i <= cur; i++)
	{
		for (auto& j : v[i]) cnt[p[j]] = 0;
	}
	tc.update(u, u, (nc >> 1LL));
	for (auto& j : G[u]) solve(j);
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; i++) cin >> c[i];
	tc.build();
	solve(1);
	tc.sgt.getans();
	for (int i = 1; i <= n; i++) cout << tc.sgt.ans[tc.id[i]] + 1LL << " ";
	return 0;
}
```


---

## 作者：OIer_ACMer (赞：1)

~~就这？！~~

------------
## 内心独白：
这道题，可以说，是我做过的最简单的点分治题目了，真的，毫无难度。

------------
## 大致思路：
这道题毫无疑问，与点分治脱不开关系，所以让我们来分析一下这道题该怎么做。

首先，老规矩，我们先输入这道题的树的点边关系，同时，题目要求我们求出经过每个点的**回文路径**数量，这时，我们又发现，这个回文使用**字符串**输入的，看到字符串处理的问题，毫无疑问肯定要用**哈希**（尽管我觉得我用的也不是正宗的哈希），定义 $s$ 数组将 $a$ 字符串的每一个字符用数字的形式存入该数组，为之后的点分治处理回文做好准备。

接着，我们到了点分治老生常谈的环节——寻找树的重心，这段内容请各位看我的代码自己理解~~说实话能点进来这道题的大佬多半已经把点分治玩得很溜了~~，同时，在 dfs 完成后，我们要把重心放在 $rt$ 数组里。

然后，就是点分治最重要的分治环节，很显然，**回文路径上最多有一个字母出现奇数次**。只需要记录奇偶性显然可以用状压去解决。我们先预处理每一条**单独的链**它们的字母奇偶性，这个奇偶性的处理我们可以再在 dfs 遍历中处理出来，只不过要注意递归别写错~~不然就像我一样要调试半天~~。之后，我们在程序中进行第二次递归，分两种情况：往左儿子走和往右儿子走。并用 $cnt$ 数组记录路径条数，至于怎么计算，和一开始的判断奇偶性差不多，只不过这一次书已经处理好了的直接调用就可以了。在处理完之后，我们经过手推可以发现：**一条路径总是被经过两次**，因为它是深度优先搜索递归，**两种情况的判断叠在一起就会出现计算两次路径**。因此我们在结束之前要提前将 $cnt$ 除以 $2$ 再加入 $ans$ 数组中对应的容器。

最后一个点处理完后，向下递归抵达另外一个点，并重复之前的操作。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 200009
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
struct node
{
    int to, next;
} edge[N << 1];
int head[N], cnt;
inline void add(int x, int y)
{
    edge[++cnt].to = y;
    edge[cnt].next = head[x];
    head[x] = cnt;
}
int sum, f[N], siz[N], rt;
bool vis[N];
void getroot(int u, int fa) // 找重心
{
    siz[u] = 1;
    f[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == fa || vis[v])
        {
            continue;
        }
        getroot(v, u);
        f[u] = max(f[u], siz[v]);
        siz[u] += siz[v];
    }
    f[u] = max(f[u], sum - siz[u]);
    if (f[rt] > f[u])
    {
        rt = u;
    }
    return;
}
char a[N];
int s[N], t[10050000];
void dfs(int x, int fa, int p, int S)
{
    t[S ^= (1 << s[x])] += p;
    for (int i = head[x]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == fa || vis[v])
        {
            continue;
        }
        dfs(v, x, p, S);
    }
}
int ans[N];
int calc(int x, int fa, int S)
{
    S ^= (1 << s[x]);
    int cnt = t[S];
    for (int i = 0; i < 20; i++)
    {
        cnt += t[S ^ (1 << i)];
    }
    for (int i = head[x]; i; i = edge[i].next) // 向下递归，搜索之前可以的路径
    {
        int v = edge[i].to;
        if (v == fa || vis[v])
        {
            continue;
        }
        cnt += calc(v, x, S);
    }
    ans[x] += cnt;
    return cnt;
}
void sol(int x)
{
    vis[x] = 1;
    dfs(x, 0, 1, 0);
    int cnt = t[0];
    for (int i = 0; i < 20; i++)
    {
        cnt += t[1 << i];
    }
    // 单个的一条路径
    for (int i = head[x]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (vis[v])
        {
            continue;
        }
        dfs(v, x, -1, 1 << s[x]);
        cnt += calc(v, x, 0);
        dfs(v, x, 1, 1 << s[x]);
    }
    dfs(x, 0, -1, 0);
    ans[x] += cnt / 2; // 算了两次啦
    for (int i = head[x]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (vis[v])
        {
            continue;
        }
        sum = siz[v];
        rt = 0;
        getroot(v, 0);
        sol(rt);
    }
    return;
}
signed main()
{
    int n;
    n = read();
    for (int i = 1; i < n; i++)
    {
        int x, y;
        x = read();
        y = read();
        add(x, y);
        add(y, x);
    }
    cin >> a;
    for (int i = 0; i < n; i++)
    {
        s[i + 1] = a[i] - 'a'; // 哈希操作
    }
    f[0] = sum = n;
    rt = 0;
    getroot(1, 0);
    sol(rt);
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] + 1 << ' ';
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121733217)

---

## 作者：Taduro (赞：1)

首先虽然这个题说的很不清楚，但它的回文串和我们一般说的回文串是不一样的，在这个题里，一个串是回文的当且仅当其中至多一个字母出现次数为奇数。同时，如果你不像我一样傻叉的话，你会发现'a'到't'一共有19个字母。

那么我们可以状压存一个串每个字母的奇偶性，然后上点分治。

点分治的具体实现方法就是先把一个分治中心子树中所有串状压开个桶存下来，然后枚举每个子树，把其中的串在桶中删去。dfs这个子树计算贡献，由于问的是在回文串上点的个数，所以每次统计一个点要加上**这次统计**中这个点儿子的答案。这样分治中心会被$u->v$的路径和$v->u$的路径算两次，所以分治中心统计的时候除个2。以及单个字符也是个回文串，所以每个点的答案再加一。

关于具体计数的实现见代码。

```c++
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
struct node{
	int next,to;
}w[400001];
int size[200001],head[200001],vis[200001];
int maxn[200001],all,rt,a[200001],n,cnt;
ll o[1<<20],ans[200001];
char ch[200001];
inline void add(int x,int y){
	w[++cnt].next=head[x];
	w[cnt].to=y; head[x]=cnt;
}
void get_rt(int x,int fa){
	size[x]=1; maxn[x]=0;
	for (int i=head[x]; i; i=w[i].next){
		if (w[i].to!=fa&&!vis[w[i].to]){
			get_rt(w[i].to,x);
			size[x]+=size[w[i].to];
			maxn[x]=max(maxn[x],size[w[i].to]);
		}
	}
	maxn[x]=max(maxn[x],all-size[x]);
	if (maxn[x]<maxn[rt]) rt=x;
}
void dfs(int x,int fa,int y,int dis){
	dis^=(1<<a[x]); o[dis]+=y;
	for (int i=head[x]; i; i=w[i].next)
		if (w[i].to!=fa&&!vis[w[i].to])
			dfs(w[i].to,x,y,dis);
}
ll get_dis(int x,int fa,int l){
	l^=(1<<a[x]); ll num=o[l];
	for (int i=0; i<=19; i++) num+=o[l^(1<<i)];
	for (int i=head[x]; i; i=w[i].next){
		if (w[i].to!=fa&&!vis[w[i].to]){
			num+=get_dis(w[i].to,x,l);
		}
	}
	ans[x]+=num;
	return num;
}
void calc(int x){
	vis[x]=1;
	dfs(x,0,1,0);
	// for (int i=head[x]; i; i=w[i].next){
	// 	if (vis[w[i].to]) continue;
	// 	dfs(w[i].to,x,1,1<<a[w[i].to]);
	// }
	ll num=o[0];
	for (int i=0; i<=19; i++) num+=o[1<<i];
	for (int i=head[x]; i; i=w[i].next){
		if (vis[w[i].to]) continue;
		dfs(w[i].to,x,-1,1<<a[x]);
		num+=get_dis(w[i].to,x,0);
		dfs(w[i].to,x,1,1<<a[x]);
	}
	dfs(x,0,-1,0); ans[x]+=num/2;
}
void solve(int x){
	calc(x);
	for (int i=head[x]; i; i=w[i].next){
		if (vis[w[i].to]) continue;
		rt=0; all=size[w[i].to];
		get_rt(w[i].to,0); solve(rt);
	}
}
int main(){
	int x,y;
	scanf("%d",&n);
	for (int i=1; i<n; i++){
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	scanf("%s",ch+1);
	for (int i=1; i<=n; i++) a[i]=ch[i]-'a';
	maxn[0]=1e9; all=n; get_rt(1,0);
	solve(rt);
	for (int i=1; i<=n; i++) printf("%I64d ",ans[i]+1);
	return 0;
}

```



---

## 作者：hh弟中弟 (赞：0)

所求与 [CF741D](https://www.luogu.com.cn/problem/CF741D) 一样，只不过是找路径，所以采用点分治，对于偶回文串，要求每个字母的出现次数为偶数，对于奇回文串，要求有且仅有一个字母的出现次数为奇数次，这个可以拿二进制记录状态，然后就是正常的点分治操作。\
统计答案是就是对 $x$ 到分治中心 $rt$ 这条链加，打个 $tag$ 最后统计即可。\
[record](https://codeforces.com/problemset/submission/914/300522410)

---

## 作者：Purslane (赞：0)

# Solution

简单点分治。

如果只让你求“回文路径”的总数，只需要基础点分治+状压。

那么如何把每条路径扔到经过的点上呢？

考虑边 $l \to x \to u \to y \to r$，发现我们扫描 $r$ 的时候容易把答案加到 $y \to r$ 这条链上。

所以只需要正反扫两遍。特判 $u$ 的贡献。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MAXM=2e6+10;
int n,mx[MAXN],sze[MAXN],flg[MAXN],ans[MAXN],add[MAXN],pre[MAXN],cnt[MAXM],tp[MAXN];
vector<int> G[MAXN]; string S; 
void dfs(int u,int f) {
	sze[u]=1,mx[u]=0,pre[u]=pre[f]^(1<<tp[u]);
	for(auto v:G[u]) if(!flg[v]&&v!=f) dfs(v,u),sze[u]+=sze[v],mx[u]=max(mx[u],sze[v]);
	return ;
}
int find_core(int u,int f,int al) {
	if(max(mx[u],al-sze[u])<=al/2) return u;
	for(auto v:G[u]) if(!flg[v]&&v!=f) {
		int tans=find_core(v,u,al);
		if(tans!=-1) return tans;
	}
	return -1;
}
void add_upd(int u,int f,int mul,int anc) {
	add[u]=0,cnt[pre[u]^(1<<tp[anc])]+=mul;
	for(auto v:G[u]) if(!flg[v]&&v!=f) add_upd(v,u,mul,anc);
	return ; 
}
int calc(int u) {
	int ans=cnt[u];
	ffor(i,0,19) ans+=cnt[u^(1<<i)];
	return ans;	
}
void add_qr(int u,int f) {
	add[u]=calc(pre[u]);
	for(auto v:G[u]) if(!flg[v]&&v!=f) add_qr(v,u),add[u]+=add[v];
	ans[u]+=add[u];
	return ;
}
void solve(int u) {
	dfs(u,0),u=find_core(u,0,sze[u]),dfs(u,0);
	cnt[0]=1; int sum=0;
	for(auto v:G[u]) if(!flg[v]) add_qr(v,u),sum+=add[v],add_upd(v,u,1,u);
	cnt[0]--,ans[u]+=sum+1;
	for(auto v:G[u]) if(!flg[v]) add_upd(v,u,-1,u);
	reverse(G[u].begin(),G[u].end());
	for(auto v:G[u]) if(!flg[v]) add_qr(v,u),add_upd(v,u,1,u);
	for(auto v:G[u]) if(!flg[v]) add_upd(v,u,-1,u);
	flg[u]=1;
	for(auto v:G[u]) if(!flg[v]) solve(v);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	cin>>S;
	ffor(i,1,n) tp[i]=S[i-1]-'a';
	solve(1);
	ffor(i,1,n) cout<<ans[i]<<' '; cout<<'\n';
	return 0;
}
```

---

## 作者：CWzwz (赞：0)

### [CF914E](https://www.luogu.com.cn/problem/CF914E) 题解

------------


题面有点不清晰，翻译一下。

> 给定一棵树，每个点上面有一个字母。定义一条简单路径回文，当且仅当路径上的字母**任意排列后**可能成为回文串。对于每个节点，求经过它的回文路径数量。**一个点也构成一条回文路径**。

容易想到，路径上字母出现次数全为偶数时满足条件，有一种字母为奇数时也满足。树上路径统计，考虑点分治。

对于一个分治中心 $u$，分 $4$ 种情况讨论。

1. 路径两端位于 $u$ 的不同子树内，开桶统计。

2. 路径两端位于 $u$ 的同一子树内，递归处理，不关 $u$ 的事。

3. 路径一端就是 $u$，这个单独处理，遍历分治树统计。

4. 路径就只有一个点 $u$。最后加一即可。

------------

以下 $u$ 表示当前分治中心。

$Dist_i$ 表示 $u$ 到 $i$ 的路径异或和，可以深搜得出。

$Count_x$ 作为桶，统计分治树中 $Dist$ 为 $x$ 的节点数。不含 $u$。

首先处理 $Dist$ 和 $Count$。

对于 $u$ 的每棵子树，先遍历一下，将子树中的 $Dist$ 从 $Count$ 里减掉，防止重复，避免了容斥（当然容斥会快一些，但是有点麻烦），然后统计答案。

最后将子树 $Dist$ 加回 $Count$ 里。

维护路径加，离线单点查询，考虑差分。这里求 $lca$ 用的树剖，倍增常数大且疑似被卡，第 81 个点会超时。

时间复杂度 $O(C\cdot n\log^2n)$，其中 $C = 20$，字母个数。常数较小，可过，跑了两秒（

空间 $O(2^C+n)$。

考虑优化，$lca$ 带来了一个 $\log$。可以在每次点分时，维护以 $u$ 而不是 $1$ 为根的差分数组，并在点分完成时直接将这次的变动加到另一个 $ans$ 数组中，具体见 Daniel_lele 大佬的题解。可以 $O(C\cdot n\log n)$ 解决。%%%

[Submission](https://codeforces.com/contest/914/submission/234347144)

------------

这是 $O(C\cdot n\log^2n)$ 解法。有注释。

```cpp
//Problem: CF914E
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define i32 INT_MAX
#define i64 LONG_LONG_MAX
#define pii pair<int, int>
#define pll pair<long long, long long>
#define pb push_back
#define fore(i,u,v) for(int i=head[u],v;i;i=e[i].nxt)
typedef long long ll;
const int N = 2e5 + 10, Num = 1.1e6; // 2^20
ll read(){ll x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}return x*f;}
void print(ll x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10+48);}
char gc(){char c=getchar();while(c==' '||c=='\n')c=getchar();return c;}
void pc(char Char){std::putchar(Char);}
 
int n, cnte;
int head[N], fa[N], d[N], top[N], son[N], siz[N]; // 树剖的
int a[N], Count[Num], vst[N], Dist[N]; // 点分的
 
int GetLca(int u, int v);
 
struct edge {
    int v, nxt;
} e[N << 1];
struct Diffrence { // 实现树上差分
    ll Diff[N];
    void add(int u, int v, ll val) {
        if(val == 0) return;
        int lca = GetLca(u, v);
        Diff[u] += val;
        Diff[v] += val;
        Diff[lca] -= val;
        Diff[fa[lca]] -= val;
    }
    void push(int u, int f) {
        fore(i, u, v) {
            v = e[i].v;
            if(v == f) continue;
            push(v, u);
            Diff[u] += Diff[v];
        }
    }
} D;

void dfs1(int u, int f) {
    fa[u] = f;
    d[u] = d[f] + 1;
    siz[u] = 1;
    fore(i, u, v) {
        v = e[i].v;
        if(v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[son[u]] < siz[v]) son[u] = v;
    }
}
void dfs2(int u, int f) {
    top[u] = f;
    if(!son[u]) return;
    dfs2(son[u], f);
    fore(i, u, v) {
        v = e[i].v;
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
} // 树剖预处理
int GetLca(int u, int v) { 
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]]) u ^= v ^= u ^= v;
        u = fa[top[u]];
    }
    if(d[u] < d[v]) return u;
    return v;
} // 树剖lca
void adde(int u, int v) {
    e[++cnte] = (edge){v, head[u]};
    head[u] = cnte;
}
int GetRoot(int u, int f, int Total, int &rt) {
    int Size = 1, MaxSize = 0;
    fore(i, u, v) {
        v = e[i].v;
        if(v == f || vst[v]) continue;
        int Temp = GetRoot(v, u, Total, rt);
        Size += Temp;
        MaxSize = std::max(MaxSize, Temp);
    }
    MaxSize = std::max(MaxSize, Total - Size);
    if(MaxSize <= Total / 2) rt = u;
    return Size;
}
int GetSize(int u, int f) {
    int Size = 1;
    fore(i, u, v) {
        v = e[i].v;
        if(v == f || vst[v]) continue;
        Size += GetSize(v, u);
    }
    return Size;
}
void Get_Count_Dist(int u, int f, int Xor) { // 处理Count[], Dist[]
    Dist[u] = Xor;    // Xor表示 根到u的异或和
    Count[Xor]++; // 扔进桶里
    fore(i, u, v) {
        v = e[i].v;
        if(v == f || vst[v]) continue;
        Get_Count_Dist(v, u, Xor ^ (1 << a[v]));
    }
}
void Update(int u, int f, int val) { // 更改桶，val决定增还是减
    Count[Dist[u]] += val;
    fore(i, u, v) {
        v = e[i].v;
        if(v == f || vst[v]) continue;
        Update(v, u, val);
    }
}
void Get_Answer(int u, int f, int SubTree_Root, int rt) { // 统计答案
    for(int k = 0; k <= 20; k++) {
        int Temp = 1 << k; if(k == 20) Temp = 0; // 枚举合法的异或值Temp
        D.add(SubTree_Root, u, Count[Dist[u] ^ (1 << a[rt]) ^ Temp] * 2);
        D.add(rt, rt, Count[Dist[u] ^ (1 << a[rt]) ^ Temp]);
        // 根节点会被算两次，因此只加一半。
        // 这里为了方便全都乘了2，最后除以2即可。
    }
    fore(i, u, v) {
        v = e[i].v;
        if(v == f || vst[v]) continue;
        Get_Answer(v, u, SubTree_Root, rt);
    }
}
void Calc(int u, int f, int rt) { // 单独处理路径一端为根的情况
    if(__builtin_popcount(Dist[u]) < 2) D.add(rt, u, 2); // 这个2也是，为了方便把1乘了二
    fore(i, u, v) {
        v = e[i].v;
        if(v == f || vst[v]) continue;
        Calc(v, u, rt);
    }
}
void Devide(int u) {
    GetRoot(u, 0, GetSize(u, 0), u);
    vst[u] = 1;
    fore(i, u, v) {
        v = e[i].v;
        if(vst[v]) continue;
        Get_Count_Dist(v, 0, (1 << a[u]) ^ (1 << a[v]));
    }
    fore(i, u, v) {
        v = e[i].v;
        if(vst[v]) continue;
        Update(v, 0, -1);
        Get_Answer(v, 0, v, u);
        Update(v, 0, 1);
    }
    fore(i, u, v) {
        v = e[i].v;
        if(vst[v]) continue;
        Update(v, 0, -1);
        Calc(v, 0, u);
    }
    fore(i, u, v) {
        v = e[i].v;
        if(vst[v]) continue;
        Devide(v);
    }
}

int main() {
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        adde(u, v);
        adde(v, u);
    }
    for(int i = 1; i <= n; i++) a[i] = gc() - 'a';
    dfs1(1, 0);
    dfs2(1, 1);
    Devide(1);
    D.push(1, 0);
    for(int i = 1; i <= n; i++) {
        print(D.Diff[i] / 2 + 1); // 1是路径只有一个点的情况
        pc(' ');
    }
    return 0;
}
```

---

## 作者：dAniel_lele (赞：0)

点分治。

有排列是回文等价于最多有一个字母出现次数为奇数。

考虑点分治，点分的时候维护每个位置到目前的根每种字母出现次数奇偶性，合并是平凡的。

考虑如何给路径上的每个点都加上 $1$ 的贡献，不难发现可以差分统计。

子树内节点到根的路径有所不同，简单特判即可。

复杂度 $O(n\log nV)$，其中 $V$ 是字母数量，这里为 $20$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
using namespace std;
vector<int> vc[200005];
int siz[200005],vis[200005],rt,askm,ans[200005],pre[200005],cnt[1200005],p[200005],pp;
void dfs0(int now,int fa){
	siz[now]=1;
	for(auto v:vc[now]){
		if(v==fa||vis[v]) continue;
		dfs0(v,now);
		siz[now]+=siz[v];
	}
	if(siz[now]>=askm) if(siz[rt]>siz[now]) rt=now;
}
void qroot(int st,int tsiz){
	rt=0,askm=tsiz/2;
	dfs0(st,0);
}
void add1(int now,int fa,int val){
	val^=(1<<p[now]); 
	pre[now]+=cnt[val^(1<<pp)];
	for(int i=0;i<20;i++) pre[now]+=cnt[val^(1<<i)^(1<<pp)];
	for(auto v:vc[now]){
		if(v==fa||vis[v]) continue;
		add1(v,now,val);
	}
}
void add2(int now,int fa,int val){
	val^=(1<<p[now]);
	cnt[val]++;
	for(auto v:vc[now]){
		if(v==fa||vis[v]) continue;
		add2(v,now,val);
	}
}
void del(int now,int fa,int val){
	val^=(1<<p[now]);
	cnt[val]--;
	for(auto v:vc[now]){
		if(v==fa||vis[v]) continue;
		del(v,now,val);
	}
}
void addup(int now,int fa){
	for(auto v:vc[now]){
		if(v==fa||vis[v]) continue;
		addup(v,now);
		pre[now]+=pre[v];
	}
}
void toans(int now,int fa){
	ans[now]+=pre[now],pre[now]=0;
	for(auto v:vc[now]){
		if(v==fa||vis[v]) continue;
		toans(v,now);
	}
}
void dfs1(int now){
//	cout<<now<<" ";
	qroot(now,0);
	pp=p[now];
	vis[now]=1;
	for(auto v:vc[now]){
		if(vis[v]) continue;
		add2(v,now,(1<<p[now]));
	}
	for(auto v:vc[now]){
		if(vis[v]) continue;
		del(v,now,(1<<p[now]));
		add1(v,now,(1<<p[now]));
		add2(v,now,(1<<p[now]));
	}
	for(auto v:vc[now]){
		if(vis[v]) continue;
		del(v,now,(1<<p[now]));
	}
	addup(now,0);
	pre[now]/=2;
	toans(now,0);
	cnt[1<<p[now]]=1;
	for(auto v:vc[now]){
		if(vis[v]) continue;
		add1(v,now,(1<<p[now]));
	}
	cnt[1<<p[now]]=0;
	addup(now,0);
	toans(now,0);
//	for(int i=1;i<=5;i++) cout<<ans[i]<<" ";
//	cout<<"\n";
	for(auto v:vc[now]){
		if(vis[v]) continue;
		qroot(v,siz[v]);
		dfs1(rt);
	} 
}
signed main(){
	siz[0]=1145141919;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		char c; cin>>c;
		p[i]=c-'a';
	}
	qroot(1,n);
	dfs1(rt);
	for(int i=1;i<=n;i++) cout<<ans[i]+1<<" ";
	return 0;
}

```

---

