# Tree Requests

## 题目描述

Roman planted a tree consisting of $ n $ vertices. Each vertex contains a lowercase English letter. Vertex $ 1 $ is the root of the tree, each of the $ n-1 $ remaining vertices has a parent in the tree. Vertex is connected with its parent by an edge. The parent of vertex $ i $ is vertex $ p_{i} $ , the parent index is always less than the index of the vertex (i.e., $ p_{i}\lt i $ ).

The depth of the vertex is the number of nodes on the path from the root to $ v $ along the edges. In particular, the depth of the root is equal to $ 1 $ .

We say that vertex $ u $ is in the subtree of vertex $ v $ , if we can get from $ u $ to $ v $ , moving from the vertex to the parent. In particular, vertex $ v $ is in its subtree.

Roma gives you $ m $ queries, the $ i $ -th of which consists of two numbers $ v_{i} $ , $ h_{i} $ . Let's consider the vertices in the subtree $ v_{i} $ located at depth $ h_{i} $ . Determine whether you can use the letters written at these vertices to make a string that is a palindrome. The letters that are written in the vertexes, can be rearranged in any order to make a palindrome, but all letters should be used.

## 说明/提示

String $ s $ is a palindrome if reads the same from left to right and from right to left. In particular, an empty string is a palindrome.

Clarification for the sample test.

In the first query there exists only a vertex 1 satisfying all the conditions, we can form a palindrome "z".

In the second query vertices 5 and 6 satisfy condititions, they contain letters "с" and "d" respectively. It is impossible to form a palindrome of them.

In the third query there exist no vertices at depth 1 and in subtree of 4. We may form an empty palindrome.

In the fourth query there exist no vertices in subtree of 6 at depth 1. We may form an empty palindrome.

In the fifth query there vertices 2, 3 and 4 satisfying all conditions above, they contain letters "a", "c" and "c". We may form a palindrome "cac".

## 样例 #1

### 输入

```
6 5
1 1 1 3 3
zacccd
1 1
3 3
4 1
6 1
1 2
```

### 输出

```
Yes
No
Yes
Yes
Yes
```

# 题解

## 作者：畿王 (赞：50)

## 题意
一棵以1为根的树，每个节点上都有1个字母，有m个询问。每次询问v对应的子树中，深度为h的这层节点的字母，能否打乱重排组成回文串。根的深度为1，每个点的深度为到根的距离。
## 思路
一层结点的字母是否能组成回文串，只需观察每个字母出现次数要么都是偶数，要么只有一个字母奇数次出现。
### 解法一
> DSU

二进制优化，每次都异或上字母对应的二进制位，只需记录答案1位是否<2即可。
### 代码1
```c++
#include<bits/stdc++.h>
#define M 500005
using namespace std;
struct query {
	int de,id;
};
int n,m;
vector<int>G[M];
vector<query>Q[M];
int L[M],R[M],ID[M],T;
int dep[M],son[M],sz[M];
int check[M],ans[M];
char A[M];
void dfs(int v,int d) {
	L[v]=++T;
	ID[T]=v;
	dep[v]=d,son[v]=0,sz[v]=1;
	for(int i=0; i<G[v].size(); i++) {
		int u=G[v][i];
		dfs(u,d+1);
		if(sz[u]>sz[son[v]])son[v]=u;
		sz[v]+=sz[u];
	}
	R[v]=T;
}
void Add_point(int x,int a) {
	int r=A[x]-'a',d=dep[x];
	check[d]^=(1<<r);//二进制优化
}
void Add_tree(int x,int a) {
	for(int i=L[x]; i<=R[x]; i++)Add_point(ID[i],a);
}
void Solve(int v) {
	for(int i=0; i<G[v].size(); i++) {
		int u=G[v][i];
		if(u==son[v])continue;
		Solve(u);
		Add_tree(u,-1);
	}
	if(son[v])Solve(son[v]);
	for(int i=0; i<G[v].size(); i++) {
		int u=G[v][i];
		if(u==son[v])continue;
		Add_tree(u,1);
	}
	Add_point(v,1);
	for(int i=0; i<Q[v].size(); i++){
		int d=Q[v][i].de,r=check[d],id=Q[v][i].id;
		ans[id]=(r==(r&-r));
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=2,f; i<=n; i++) {
		scanf("%d",&f);
		G[f].push_back(i);
	}
	dfs(1,1);
	scanf("%s",A+1);
	for(int i=1; i<=m; i++) {
		int x,d;
		scanf("%d%d",&x,&d);
		Q[x].push_back((query) {d,i});
	}
	Solve(1);
	for(int i=1; i<=m; i++)
		if(ans[i])puts("Yes");
		else puts("No");
	return 0;
}

```
### 解法二
> dfs作差

同样是二进制，每次进结点时记录原先的二进制数，出结点时再用更新过的数据异或上原来的即为答案。
### 代码二
```c++
#include<bits/stdc++.h>
#define M 500005
using namespace std;
struct query{
	int de,id;
};
int n,m;
vector<int>G[M],tmp[M];
vector<query>Q[M];
int cnt[M],ans[M];
char A[M];
void dfs(int v,int d){
	cnt[d]^=1<<A[v]-'a';
	for(int i=0;i<Q[v].size();i++)
		tmp[v].push_back(cnt[Q[v][i].de]);
	for(int i=0;i<G[v].size();i++)
		dfs(G[v][i],d+1);
	for(int i=0;i<Q[v].size();i++)
		ans[Q[v][i].id]=(tmp[v][i]^cnt[Q[v][i].de]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=2,f;i<=n;i++){
		scanf("%d",&f);
		G[f].push_back(i);
	}
	scanf("%s",A+1);
	for(int i=1;i<=m;i++){
		int x,d;
		scanf("%d%d",&x,&d);
		Q[x].push_back((query){
			d,i
		});
	}
	dfs(1,1);
	for(int i=1;i<=m;i++)
		puts(ans[i]==(ans[i]&-ans[i])?"Yes":"No");
	return 0;
}
```
### 解法三
> 在线 异或前缀和

只需将每个深度的结点按照dfs序排到一个vector里，同时记录每个对应的异或前缀和，则对于一个询问x，只需在给定深度里找比L[x]大的和比R[x]小的两个端点即可，再异或一下前缀和即可。
### 代码三
```c++
#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,m;
vector<int>G[M],deep[M],Xor[M];
int L[M],R[M],ID[M],T,mxdep;
int dep[M];
char A[M];
void dfs(int v,int d) {
	L[v]=++T;
	ID[T]=v,dep[v]=d;
	mxdep=max(mxdep,d);
	deep[d].push_back(L[v]);
	for(int i=0; i<G[v].size(); i++) {
		int u=G[v][i];
		dfs(u,d+1);
	}
	R[v]=T;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=2,f; i<=n; i++) {
		scanf("%d",&f);
		G[f].push_back(i);
	}
	scanf("%s",A+1);
	dfs(1,1);
	for(int i=1;i<=mxdep;i++){
		Xor[i].push_back(1<<(A[ID[deep[i][0]]]-'a'));
		for(int j=1;j<deep[i].size();j++)//异或前缀和
			Xor[i].push_back(Xor[i][j-1]^(1<<(A[ID[deep[i][j]]]-'a')));
	}
	while(m--){
		int x,d,ans=0;
		scanf("%d%d",&x,&d);
		int l=lower_bound(deep[d].begin(),deep[d].end(),L[x])-deep[d].begin();
		int r=upper_bound(deep[d].begin(),deep[d].end(),R[x])-deep[d].begin()-1;
		//在当前深度找xdfs序之内的点
		if(r<0)puts("Yes");
		else {
			if(l==0)ans=Xor[d][r];//处理前缀和
			else ans=Xor[d][r]^Xor[d][l-1];
			if(ans==(ans&-ans))puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
```

---

## 作者：UltiMadow (赞：19)

既然是dsu的板子，那就来一个详细的dsu讲解

前置芝士：
+ 暴力
+ 没了
+ 真的没了

如果您不会暴力，那……还是提一下吧（

暴力思路很简单，对于一个节点，统计它的子树中所有深度的节点的颜色情况，询问的时候只要检查这个节点的子树中指定深度的节点颜色出现次数是否有 $\le 1$ 个奇数即可

然后发现空间复杂度达到了 $\Theta(n^2)$，显然不可以接受

于是我们可以把所有询问离线下来，根据节点编号分类（换句话说就是把一个关于 $u$ 节点的询问挂到 $u $ 上，dfs的时候一起处理）

接下来我们每处理一个节点的时候只需要把前面统计的东西清空，全部暴力统计一遍

然后发现时间复杂度达到了 $\Theta(n^2)$，还是不可以接受

我们发现在清空之前的统计数据的时候造成了很大的浪费，于是想到如何最小化这个浪费

有一个解决这种暴力问题的方法叫做启发式合并，即保留较多的信息，把其他零散的信息暴力地往上面合并

这里也采用这种思路，我们每次处理的时候把重儿子的信息留着，把轻儿子的信息删去，最后再暴力地把轻儿子合并到留下的信息里面

如果你不知道轻重儿子是啥，可以去[这里](https://www.luogu.com.cn/problem/P3384)学一些概念

由于每个轻儿子最多会被合并 $\log n$ 次，所以总时间复杂度为 $\Theta(n\log n)$

一些代码实现的细节：
1. 使用 dfn 序代替 dfs 进行合并（大概可以优化一下常数）
2. 清空信息的时候不要 memset，不然时间复杂度飙升到 $\Theta(n^2)$
3. 题意中深度是指以 1 为根时的深度，别被题意杀了（我被杀了两次，然后检查了15min）

code:

```cpp
#include<bits/stdc++.h>
#define MAXN 500010
#define uint unsigned int
using namespace std;
int n,m,son[MAXN],bro[MAXN];//有根树，兄弟儿子表示法会比较方便
struct qnode{int id,d;};
vector<qnode>que[MAXN];//离线询问
int cnt[MAXN][30],ans[MAXN];
char col[MAXN];
//cnt[dep][col]指深度为dep的节点中col出现的次数
bool check(int d)
{
	int ret=0;
	for(int i=1;i<=26;i++)
		ret+=(cnt[d][i]&1);
	return ret<=1;
}//检查第 d 层是否珂以构成回文
int in[MAXN],out[MAXN],tot,id[MAXN];
int sz[MAXN],dep[MAXN],hev[MAXN];
//in,out指进dfs序和出dfs序
void dfs1(int u)
{
	in[u]=++tot;id[tot]=u;sz[u]=1;int heavy=-1926;
	for(int v=son[u];v;v=bro[v])
	{
		dep[v]=dep[u]+1;dfs1(v);sz[u]+=sz[v];
		if(sz[v]>heavy)heavy=sz[v],hev[u]=v;
	}out[u]=tot;
}
void add(int u){cnt[dep[u]][col[u]-'a'+1]++;}//加一个节点
void update(int u){for(int i=in[u];i<=out[u];i++)add(id[i]);}//加一棵子树
void del(int u){cnt[dep[u]][col[u]-'a'+1]=0;}//删一个节点
void erase(int u){for(int i=in[u];i<=out[u];i++)del(id[i]);}//删一棵子树
void dfs2(int u,int tag)//tag指是轻儿子还是重儿子
{
	for(int v=son[u];v;v=bro[v])
	{
		if(v==hev[u])continue;
		dfs2(v,0);//轻儿子
	}if(hev[u])dfs2(hev[u],1);//重儿子
	for(int v=son[u];v;v=bro[v])
	{
		if(v==hev[u])continue;
		update(v);//加轻儿子的子树
	}add(u);//加自身节点
	for(uint i=0;i<que[u].size();i++)
		ans[que[u][i].id]=check(que[u][i].d);//统计答案
	if(tag)return;erase(u);//如果是轻儿子就删除信息
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++)
	{
		int fa;scanf("%d",&fa);
		bro[i]=son[fa];son[fa]=i;
	}scanf("%s",col+1);
	for(int i=1;i<=m;i++)
	{
		int u,x;scanf("%d%d",&u,&x);
		que[u].push_back((qnode){i,x});
	}dep[1]=1;dfs1(1);dfs2(1,0);
	for(int i=1;i<=m;i++)printf("%s\n",ans[i]?"Yes":"No");
	return 0;
}
```

---

## 作者：牛蛙丶丶 (赞：8)

#### dsu on tree 练习题

首先，因为是以a为根的子树内深度为b的节点上的字母重新排列之后是否能构成回文串，要排列后成为回文串，所以在符合条件的所有字母之中必须至多只有一种字母的数量为奇数种。

然后，就是基本的 dsu on tree  的操作了，先将所有的询问以离线的方式存储下来，这样子做可以让我们一边dfs，一边解决所有的询问，之后统计所有深度字母的出现次数以便我们的 check ，再将轻边子树的信息保留到重链之上进行一个答案的统计。

#### code

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#define N 500070

struct Tree{
	int to,nxt;
}e[N<<1];
struct Rec{
	int k,id;
};
int n,m,cnt;
int head[N],sz[N],sum[N],son[N],dep[N],ans[N],tot[N][26];
bool vis[N];
std::vector<Rec>q[N];
char s[N];

void add(int from,int to){e[++cnt].to=to,e[cnt].nxt=head[from],head[from]=cnt;}
void dfs(int x,int fa){
	sz[x]=1,dep[x]=dep[fa]+1;
	for(int i=head[x],v;i;i=e[i].nxt){
		v=e[i].to;if(v==fa) continue;
		dfs(v,x),sz[x]+=sz[v];
		if(!son[x]||sz[v]>sz[son[x]]) son[x]=v;
	}
}
void calc(int x,int fa,int val){
	tot[dep[x]][s[x]-'a']+=val;
	for(int i=head[x],v;i;i=e[i].nxt){
		v=e[i].to;if(v==fa||vis[v]) continue;
		calc(v,x,val);
	}
}
bool check(int s[]){
	int r=0;
	for(int i=0;i<26;++i){
		if(s[i]&1) ++r;
		if(r>1) return 0;
	}
	if(r>1) return 0;
	return 1;
}
void dfs2(int x,int fa,int keep){
	for(int i=head[x],v;i;i=e[i].nxt){
		v=e[i].to;if(v==fa||v==son[x]) continue;
		dfs2(v,x,0);
	}
	if(son[x]) dfs2(son[x],x,1),vis[son[x]]=1;
	calc(x,fa,1),vis[son[x]]=0;
	for(int i=0;i<q[x].size();++i) ans[q[x][i].id]=check(tot[q[x][i].k]);
	if(!keep) calc(x,fa,-1);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=2,u;i<=n;++i){
		scanf("%d",&u);
		add(u,i),add(i,u);
	}
	scanf("%s",s+1);
	dfs(1,0);
	for(int i=1,a,b;i<=m;++i){
		scanf("%d%d",&a,&b);
		q[a].push_back((Rec){b,i});
	}
	dfs2(1,0,0);
	for(int i=1;i<=m;++i)
		puts(ans[i]?"Yes":"No");
}
```



---

## 作者：Fading (赞：5)

状压+动态开点线段树。

还是很裸的一题啊为什么大家都用什么 dsu on a tree。。。

先是把每一个字母状压掉

然后等价于判断深度等于$K$且在子树内的点的状态异或和是否只存在一个$1$或不存在$1$

我们对每一个深度都开一棵线段树，以 dfs 序为下标，维护区间异或值。

对于一个询问直接在子树的 dfs 序区间内求异或和就好了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct SEG{
    int l,r,mn;
}seg[10000001];
struct edge{
    int to,next;
}g[1200001];
int n,secnt,tcnt,m,head[520001],root[520001],tot,a[520001],mxdep,tpos[520001],pre[520001],size[520001],dep[520001],las;
vector <int> Dep[520001]; 
inline void made(int from,int to){
    g[++tot].to=to;g[tot].next=head[from];head[from]=tot;
}
void dfs(int u,int fa){
    tpos[u]=++tcnt;pre[tcnt]=u;size[u]=1;dep[u]=dep[fa]+1;
    for (int i=head[u];i;i=g[i].next){
        int v=g[i].to;
        if (v==fa) continue;
        dfs(v,u);
        size[u]+=size[v];
    }
    mxdep=max(mxdep,dep[u]);
    Dep[dep[u]].push_back(u);
}
#define mid ((lb+rb)>>1)
void update(int &rt,int lb,int rb,int pos){
    seg[++secnt]=seg[rt];rt=secnt;seg[rt].mn=seg[rt].mn^a[pre[pos]];
    if (lb==rb) return;
    if (pos<=mid) update(seg[rt].l,lb,mid,pos);
    else update(seg[rt].r,mid+1,rb,pos);
}
int query(int rt,int l,int r,int lb,int rb){
    if (lb>r||rb<l||!rt) return 0;
    if (lb>=l&&rb<=r) return seg[rt].mn;
    return query(seg[rt].l,l,r,lb,mid)^query(seg[rt].r,l,r,mid+1,rb);
}
inline int read(){
    register int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
}
int main(){
    n=read(),m=read();
    for (int i=1;i<n;i++){
        int x=read();
        made(i+1,x);made(x,i+1);
    }
    for (int i=1;i<=n;i++){
        char ch=getchar();
        while (!isalpha(ch)) ch=getchar();
        a[i]=(ch-'a');
        a[i]=(1<<a[i]);
    }
    dfs(1,0);secnt=1;
    for (int i=1;i<=mxdep;i++){
        int X=Dep[i].size();
        for (int j=0;j<X;j++){
            int y=Dep[i][j];
            update(root[i],1,n,tpos[y]);
        }
    }
    while (m--){
        int x=read(),K=read();
        int fff=0,fk=query(root[K],tpos[x],tpos[x]+size[x]-1,1,n);
        if (!fk){printf("Yes\n");continue;}
        while (fk){
        	if (fk&1) fff++;
        	fk>>=1;
        }
        if (fff<=1) printf("Yes\n");
        else printf("No\n");
    }
}
```

---

## 作者：chen_qian (赞：4)

一种极为暴力的办法。

当我们在处理静态树上问题时，我们有时会遇见将子树信息合并到父节点上。我们可以对于每一个树上节点都开一个桶来维护。但是可能空间会开不下。

所以我们只能开一个全局桶，每次都要把桶清空，然后暴力统计子树里面所有信息。

这样对于每一个节点，我们都需要将其所有子树的所有节点全部遍历，可能会有超时风险。

但是我们发现，在用$dfs$进行遍历时，我们可以优先计算子节点再计算父节点，这就意味着对于每个节点$x$,我们都可以保留一个子树$y$的信息，让其直接继承到$x$的信息，这样，选那一个子树就成为了我们要解决的问题。

一个很简单的贪心是，我们选节点数最多的那个，这样继承到的信息更多，节省的时间也就越多。

那么就有一个类似重链剖分的操作。遍历整棵树，并记录下他的重儿子。

那么接下来就是暴力的思路了，具体实现看一个例题。

一棵有根树，以1为根。每个点只有一个颜色，请你求出每个点的子树的出现次数最多的颜色。
有多个颜色出现次数相同时，输出最小的解。

来源：bsoj6750

本题我们直接开一个桶$t[x]$表示子树中颜色为$x$的个数，然后在找到重儿子的情况下，对于每一个节点我们重复以下步骤。

1. 优先递归计算非重子节点信息

2. 计算重子节点信息

3. 再次递归计算非重子节点信息，并将信息合并到重子节点的信息

4. 加入当前节点的信息，更新答案

5. 加入当前节点不是父节点重子节点，清空桶

```
#include<bits/stdc++.h>
#define N 300005
using namespace std;
int n,w[N],size[N],tmp[N],son[N];
int head[N],idx,t[N],seg[N],rev[N],cnt,fs[N],MAXN;
int ans[N];
struct edge{
	int v,next;
}e[2*N];
void add(int u,int v){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
}
void dfs1(int x,int f){
	size[x]=1;
	seg[x]=++cnt;//类似树链剖分的操作 
	rev[cnt]=x;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==f) continue;
		dfs1(y,x);
		size[x]+=size[y];
		if(size[y]>size[son[x]]) son[x]=y;
	}
}
void dfs2(int x,int f,int type){//type表示x是不是重儿子 
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==son[x]||y==f) continue;
		dfs2(y,x,1);
	}
	if(son[x]) dfs2(son[x],x,0);
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==f||y==son[x]) continue;
		for(int j=seg[y];j<=seg[y]+size[y]-1;j++) t[w[rev[j]]]++;//遍历子树 
	}
	t[w[x]]++;
//	cout<<x<<": ";
//	for(int i=1;i<=MAXN;i++) cout<<t[i]<<' ';
//	cout<<endl;
	int mx=0;
	for(int i=1;i<=MAXN;i++){
		if(t[i]>mx){
			mx=t[i];
			ans[x]=i;
		}
	}
	if(type) for(int i=1;i<=MAXN;i++) t[i]=0;//清零计数数组 
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
		tmp[i]=w[i];
	}
	sort(tmp+1,tmp+n+1);
	int len=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++){
		int tmpp=lower_bound(tmp+1,tmp+len+1,w[i])-tmp;
		fs[tmpp]=w[i];
		w[i]=tmpp;
		MAXN=max(tmpp,MAXN);
		//cout<<w[i]<<' ';
	}
	//cout<<endl;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	for(int i=1;i<=n;i++) printf("%d\n",fs[ans[i]]);
	return 0;
}
```
[CF375D](https://www.luogu.com.cn/problem/CF375D)

本题同样也是类似上题的问题。

只需额外计算$d[k]$表示子树中出现数量大于等于$k$的颜色的个数。

但是这样来想似乎就需要计算前缀和了？

实际上不用，对于一个出现$k$次的颜色，他只对于$d[i],i<=k$的答案有贡献，而我们得到$k$这个答案时，是从$0$依次加上来的那么我们只需每加一次就将答案$+1$即可。

```
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m;
int head[N],idx,c[N];
int t[N],size[N],son[N];
bool vis[N];
struct query{
	int k,id; 
};
int ans[N],d[N];
struct edge{
	int v,next;
}e[N<<1];
vector<query> q[N];
void add(int u,int v){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
}
void dfs1(int x,int f){
	size[x]=1;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==f) continue;
		dfs1(y,x);
		size[x]+=size[y];
		if(size[y]>size[son[x]]) son[x]=y;
	}
}
void solve(int x,int f,int p){
	if(p==-1)
        d[t[c[x]]]+=p;
    t[c[x]]+=p;
    if(p==1)
        d[t[c[x]]]+=p;
    for(int i=head[x];i;i=e[i].next){
    	int y=e[i].v;
        if(y==f||vis[y])
            continue;
        solve(y,x,p);
    }
}
void dfs2(int x,int f,int type){
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==f||y==son[x]) continue;
		dfs2(y,x,1);
	}
	if(son[x]){
		dfs2(son[x],x,0);
		vis[son[x]]=1;
	}
	solve(x,f,1);
	//for(int i=1;i<=10;i++) cout<<d[i]<<' ';
	//cout<<endl;
	for(int i=0;i<q[x].size();i++)
		ans[q[x][i].id]=d[q[x][i].k];
	if(son[x]) vis[son[x]]=0;
	if(type) solve(x,f,-1);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=m;i++){
		int u;
		query x;
		scanf("%d%d",&u,&x.k);
		x.id=i;
		q[u].push_back(x);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```

注意本题我们用到了离线算法，另外这里我是用递归实现的计数与清空


[CF570D](https://www.luogu.com.cn/problem/CF570D#submit)

显然我们可以知道的是假如说一串字符重拍后能够成回文串，那么其至多有一个出现奇数次的字符。

再加上体面说的深度$k$是对于统一的根节点$1$来讲的，那么很容易想到的$t[x]$来进行状态压缩，$t[x]$的二进制下的$i$位为$0$表示字母$i$出现偶数次，否则出现奇数次。

然后用$check()$来计算出现了几个出现奇数次的字母。

```
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int n,m;
int head[N],idx,w[N];
int size[N],son[N],dep[N];
int t[N];
bool vis[N],ans[N];
struct query{
	int k,id; 
};
struct edge{
	int v,next;
}e[N<<1];
vector<query> q[N];
void add(int u,int v){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
}
void dfs1(int x,int f){
	size[x]=1;
	dep[x]=dep[f]+1;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		dfs1(y,x);
		size[x]+=size[y];
		if(size[y]>size[son[x]]) son[x]=y;
	}
}
bool check(int x){
	bool f=0;
	while(x){
		if(x&1){
			if(f==1) return false;
			f=1;
		}
		x>>=1;
	}
	return true;
}
void solve(int x){
	t[dep[x]]^=(1<<w[x]);
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(vis[y]) continue;
		solve(y);
	}
}
void dfs2(int x,int type){
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==son[x]) continue;
		dfs2(y,1);
	}
	if(son[x]){
		dfs2(son[x],0);
		vis[son[x]]=1;
	}
	solve(x);
	for(int i=0;i<q[x].size();i++) ans[q[x][i].id]=check(t[q[x][i].k]);
	if(son[x]) vis[son[x]]=0;
	if(type) solve(x);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++){
		int f;
		scanf("%d",&f);
		add(f,i); 
	}
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++)
		w[i+1]=s[i]-'a';
	for(int i=1;i<=m;i++){
		int u;
		query x;
		scanf("%d%d",&u,&x.k);
		x.id=i;
		q[u].push_back(x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=m;i++){
		if(ans[i]==1) puts("Yes");
		else puts("No");
	}
	return 0;
}
```


---

## 作者：Natsume_Rin (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF570D)

### 题意：

给出一个有着 $n$ 个节点的树，以 $1$ 号点为根，每一个节点上有一个字母。再给出 $q$ 组询问，每次询问以 $a$ 为根节点的子树中深度为 $b$ 的节点上的字母是否能组成回文串。

$\texttt{Range}$：$n,q \leq 5\times10^5$。

------------------------------------------------

### 解法

~~蒟蒻来写线段树合并的题解了。~~

首先观察到回文串有一种对称的性质，也就是说，只要使得所有字母中出现奇数次的字母数量 $\leq 1$ 即可，由此 **我们只需要保存每一个字母出现次数的奇偶性就行了**。**所以可以通过异或 ($\oplus$) 来记录每一个字母出现次数奇偶性**。

解决了第一个问题，现在是第二个问题：怎么快速回答每一个询问？

因为题目并没有强制在线，所以可以 **先把询问离线**，用链表存储在对应的点上，代码实现大概长这样：

```cpp
void addQ(int a, int b){
     ++cnt;//当前处理到第 cnt 个询问。
     Qask[cnt]=b;//记录询问的深度。
     next_[cnt]=head[a];//链表处理。
     head[a]=cnt;//链表处理。
     id[cnt]=cnt;//记录当前处理的询问编号，不过似乎这一个没什么用。
     return ;
}
```

接下来，考虑线段树合并，从 $1$ 号点开始 $\text{dfs}$，不断将一个点的子节点并入自己，再处理和自己这一个节点的相关询问。

代码大概长这样：

```cpp
de[x]=de[fath]+1;
buildtree(1,n,de[x],rt[x],ch[x-1]-'a'+1);
for(RI i=headl[x];i;i=ne[i]){
	if(to[i]==fath) continue;
	dfs(to[i],x);
	rt[x]=merge(rt[x],rt[to[i]],1,n);
}//套路线段树合并。
RI cntp;//用了register int(RI)，cntp表示当前得到答案的二进制中1的个数。
for(RI i=head[x];i;i=next_[i]){// 遍历和x节点相关的询问。
	cntp=0;
	ans[id[i]]=ask(rt[x],1,n,Qask[i]);//ask直接在线段树上找到深度为Qask[i]的点代表的数字。
	while(ans[id[i]]){
		if(ans[id[i]]&1) cntp++;//统计。
		ans[id[i]]>>=1;
	}
	ans[id[i]]=cntp;//保存答案，如果cntp<=1，直接输出 Yes，否则输出 No。
}
```

然后再套一个线段树合并的板子，就可以 $\color{green}\texttt{AC}$ 这一道题目了。时间复杂度 $\mathcal O((n+q)\log n)$。

完整代码：

```cpp
#include<bits/stdc++.h>//爱用万能头。
#define RI register int
using namespace std;
const int MAXN = 5e5+50;
int n, q;
int de[MAXN];
char ch[MAXN];
int par, head[MAXN], ne[MAXN<<1], to[MAXN<<1], cnt;
int headl[MAXN], nel[MAXN<<1], tol[MAXN<<1], weight[MAXN<<1];
int newnode;
int lc[MAXN*20], rc[MAXN*20], tree[MAXN*20];
int tot;
int rt[MAXN];
int ans[MAXN];
inline void add(int x, int y){
	++cnt;
	to[cnt]=y;
	ne[cnt]=head[x];
	head[x]=cnt;
	return ;
}//加边。
inline void addQ(int x, int y){
	++tot;
	tol[tot]=y;
	nel[tot]=headl[x];
	headl[x]=tot;
	weight[tot]=tot;
	return ;
}//加询问。
inline void buildtree(int l, int r, int pos, int &root, int val){
	root=++newnode;
	if(l==r){
		tree[root]=(1<<val);
		return ;
	}
	RI mid=(l+r)>>1;
	if(pos<=mid) buildtree(l,mid,pos,lc[root],val);
	else buildtree(mid+1,r,pos,rc[root],val);
	tree[root]=tree[lc[root]]^tree[rc[root]];
	return ;
}
inline int merge(int x, int y, int l, int r){
	if(!x || !y) return x^y;
	if(l==r){//可能出现深度相同的点，合并这两个点。
		tree[x]^=tree[y];
		return x;
	}
	RI mid=(l+r)>>1;
	lc[x]=merge(lc[x],lc[y],l,mid);//合并左子树。
	rc[x]=merge(rc[x],rc[y],mid+1,r);//合并右子树。
	tree[x]=tree[lc[x]]^tree[rc[x]];//更新。
	return x;
}
inline int ask(int root, int l, int r, int rk){
	if(l==r) return tree[root];
	RI mid=(l+r)>>1;
	if(rk<=mid) return ask(lc[root],l,mid,rk);
	else return ask(rc[root],mid+1,r,rk);
   //这个就相当于线段树的单点查询。
}
inline void dfs(int x, int fath){
	de[x]=de[fath]+1;//记录深度。
	buildtree(1,n,de[x],rt[x],ch[x-1]-'a'+1);//建树。
	for(RI i=head[x];i;i=ne[i]){
		if(to[i]==fath) continue;
		dfs(to[i],x);//遍历子节点
		rt[x]=merge(rt[x],rt[to[i]],1,n);//合并。
	}
	RI cntp;
	for(RI i=headl[x];i;i=nel[i]){
		cntp=0;
		ans[weight[i]]=ask(rt[x],1,n,tol[i]);
		while(ans[weight[i]]){
			if(ans[weight[i]]&1) cntp++;
			ans[weight[i]]>>=1;
		}
		ans[weight[i]]=cntp;
	}
}
int x, y;
int main(){
	scanf("%d%d",&n,&q);
	for(RI i=2;i<=n;++i){
		scanf("%d",&par);
		add(par,i);
	}
	scanf("%s",&ch);
	for(RI i=1;i<=q;++i){
		scanf("%d%d",&x,&y);
		addQ(x,y);
	}
	dfs(1,0);
	for(RI i=1;i<=q;++i){
		if(ans[i]<=1) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

完结，望点完赞再走。

---

## 作者：legendgod (赞：3)

### [CF570D Tree Requests](https://www.luogu.com.cn/problem/CF570D)

首先我们考虑对于本题求的是在一个子树中同一深度的节点，那么我们比较容易想到用 dfs 序来维护。

之后我们考虑到一个串是回文的，有两种情况：

> $Case\ 1:$ 有且仅有一个字符出现了一次。

> $Case \ 2:$ 没有字符出现一次。

发现只有 26 个字符，完全可以状压。

对于深度不好处理，那么我们直接对每一个深度都建立一个权值线段树，其下标维护的是 dfs 序。每一个节点保存的值就是状压有几个字符。

具体来说如果要增加一个节点 x，我们只需要在 $l = r = dfn[x]$ 的区间上的节点 $t[p]$，异或上当前当前节点的状态 $t[p] xor \ sta[hdfn[x]]$， 其中 $hdfn[x]$ 表示 dfs 序为 x 的节点原来的值。


----
$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}

const int maxn = 5e5 + 5;
const int maxm = maxn << 1;
int n, m;
typedef int room[maxn];
room a, dep, siz, dfn, hdfn;
struct Edge{
	int to, next;
}edg[maxn << 1];
int head[maxn], cnt;
void add(int u,int v) {
	edg[++ cnt] = (Edge) {v, head[u]}, head[u] = cnt;
}
int num(0);
vector<int> vc[maxn];
int mx(0);
void dfs(int p,int f) {
	dep[p] = dep[f] + 1;
	siz[p] = 1;
	dfn[p] = ++ num;
	hdfn[num] = p;
	if(mx < dep[p]) mx = dep[p];
	vc[dep[p]].push_back(p);
	for(int i = head[p];i;i = edg[i].next) {
		int to = edg[i].to;
		if(to == f) continue;
		dfs(to, p);
		siz[p] += siz[to];
	}
}
int rt[maxn];
struct Seg {
	int num;
	struct Node {
		int val, l, r;
	}t[maxn * 40];
	Seg(void) : num(0) {}
	#define mid ((l + r) >> 1)
	void pushup(int p) {
		t[p].val = t[t[p].l].val ^ t[t[p].r].val;
	}
	void Insert(int &p,int l,int r,int pos) {
		if(!p) p = ++ num;
		if(l == r) return t[p].val ^= a[hdfn[pos]], void();
		if(pos <= mid) Insert(t[p].l, l, mid, pos);
		else Insert(t[p].r, mid + 1, r, pos);
		pushup(p);
	}
	int ask(int p,int l,int r,int ll,int rr) {
		if(!p) return 0;
		if(ll <= l && r <= rr) return t[p].val;
		int res(0);
		if(ll <= mid) res ^= ask(t[p].l, l, mid, ll, rr);
		if(mid < rr) res ^= ask(t[p].r, mid + 1, r, ll, rr); 
		return res;
	}
}T;
signed main() {
	int i, j;
	r1(n), r1(m);
	for(i = 2;i <= n; ++ i) {
		int x;
		r1(x);
		add(i, x), add(x, i);
	} 
	for(i = 1;i <= n; ++ i) {
		char c;
		cin >> c;
		a[i] = (1 << (c - 'a'));
	}
	dfs(1, 0);
	for(i = 1;i <= n; ++ i) {
		for(int j = 0; j < vc[i].size(); ++ j) {
			int to = vc[i][j];
			T.Insert(rt[i], 1, n, dfn[to]);
		}
	}
	while(m --) {
		int u, b;
		r1(u), r1(b);
		int ans = T.ask(rt[b], 1, n, dfn[u], dfn[u] + siz[u] - 1);
		ans -= (ans & (-ans));
		if(!ans) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

```


---

## 作者：Guess00 (赞：3)

## 题解 $\text{CF570D\ Tree Requests}$

#### 本题思路:dfs序+二分

一句话题意:一棵有根树上每个点有一个字母，每次查询点$x$的所有$\text{K-son}$上的字母能否重组成回文串。

如果没有做过[CF208E](https://www.luogu.com.cn/problem/CF208E)的可以先去做一下，是本题的简化版。[这](https://www.luogu.com.cn/blog/Guess00/solution-CF208E)是我的做法。

CF208E是求$\text{K-son}$的个数，而本题是是求$\text{K-son}$的字母能否重组成回文串。下面考虑如何判断能否重组成回文串。考虑回文串的性质:至多有一个字母出现奇数次。同CF208E,可以二分出$\text{K-son}$的最左边$l$和最右边$r$。明显，得到$l$和$r$后，需要快速地判断出有几个字母出现了奇数次。这个东西可以先差分，分成$0$~$r$**减**$0$~$l$(这个**减**请自行感性理解)。不难发现字母一共只有26个，于是考虑状态压缩。再对每层开一个$\text{vector},$维护前缀状态(细节详见代码)。

时间复杂度:$\Theta(n\log n)$

$\mathbb{CODE:}$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=500005;
vector<int> G[MAXN],a[MAXN],b[MAXN],inn[MAXN];
//G是邻接向量,a维护每层的点,b维护每层前缀状态,inn维护每层dfs序 
int n,m,i,j,x,y,z,cnt,maxd,f[MAXN],dep[MAXN],in[MAXN],out[MAXN];
char ch[MAXN];
inline void read(int &x)   //快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)   //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
inline int lowbit(int x){return x&(-x);}
inline void dfs(int u)
{
	dep[u]=dep[f[u]]+1; 
	in[u]=++cnt;
	maxd=max(maxd,dep[u]);
	a[dep[u]].push_back(u);
	inn[dep[u]].push_back(in[u]);
	for (int i=0;i<G[u].size();i++)
		dfs(G[u][i]);
	out[u]=cnt;
}
signed main(void)
{
	read(n),read(m);
	for (i=2;i<=n;i++)
	{
		read(f[i]);
		G[f[i]].push_back(i);
	}
	for (i=1;i<=n;i++)
	{
		ch[i]=getchar();
		while (!('a'<=ch[i] && ch[i]<='z'))  //个人习惯 
			ch[i]=getchar();
	}
	dfs(1);
	for (i=1;i<=maxd;i++)  //枚举每层,计算前缀状态 
		for (y=j=0;j<a[i].size();j++)
		{
			x=ch[a[i][j]]-'a';  //将字母转成0-25中一个数 
			y^=(1<<x);   //对于每个字母0表示偶数,1表示奇数,异或进行翻转 
			b[i].push_back(y);  //扔进vector中 
		}
	while (m--)
	{
		read(x),read(y);
		int l,r;
		l=lower_bound(inn[y].begin(),inn[y].end(),in[x])-inn[y].begin();
		r=upper_bound(inn[y].begin(),inn[y].end(),out[x])-inn[y].begin()-1;
		//二分出最左边和最右边 
		if (r<0)  //特判一下(这个点是叶子节点) 
		{
			printf("Yes\n");
			continue;
		}
		z=l<1?b[y][r]:b[y][r]^b[y][l-1];
		//l如果等于0,-1后下标越界,要判断一下(关于为什么-1会差分基本都知道吧) 
		z-=lowbit(z);//lowbit都会吧 
		//至多一个奇数,就是状态中至多一个1,将这个1减掉,如果为全为0说明可以
		printf(!z?"Yes\n":"No\n");
	}
	return 0;
}
```

---

## 作者：Farkas_W (赞：2)

### 思路：

$\quad$ $Dsu$ $on$ $Tree$模板题，没有做过的可以做做[CF600E Lomsat gelral](https://www.luogu.com.cn/problem/CF600E)，也是一道模板题，下面就简单讲讲树上启发式合并 ($DSU$ $on$ $Tree$)算法，如果有不懂的可以提出来。

$$\text{前置知识}$$

$\quad$学这个之前需要对树上操作、 $dfs$ 序和轻重链剖分等知识有一定了解，最好已经掌握了树链剖分。

$$\text{算法思想}$$

$\quad$树上启发式合并 ($DSU$ $on$ $Tree$)，是一个在 $O(nlogn)$ 时间内解决许多树上问题的有力算法，对于某些树上离线问题可以速度大于等于大部分算法且更易于理解和实现。

$\quad$先想一下暴力算法，对于每一次询问都遍历整棵子树，然后统计答案，最后再清空cnt数组，最坏情况是时间复杂度为 $O(n^2)$ ，对于 $10^5$ 的数据肯定是过不去的。

$\quad$现在考虑优化算法，暴力算法跑得慢的原因就是多次遍历，多次清空数组，一个显然的优化就是将询问同一个子树的询问放在一起处理，但这样还是没有处理到关键，最坏情况时间复杂度还是 $O(n^2)$ ，考虑到询问 $x$ 节点时， $x$ 的子树对答案有贡献，所以可以不用清空数组，先统计 $x$ 的子树中的答案，再统计 $x$ 的答案，这样就需要提前处理好 $dfs$ 序。

$\quad$然后我们可以考虑一个优化，遍历到最后一个子树时是不用清空的，因为它不会产生对其他节点影响了，根据贪心的思想我们当然要把节点数最多的子树（即重儿子形成的子树）放在最后，之后我们就有了一个看似比较快的算法，先遍历所有的轻儿子节点形成的子树，统计答案但是不保留数据，然后遍历重儿子，统计答案并且保留数据，最后再遍历轻儿子以及父节点，合并重儿子统计过的答案。

$\quad$其实树上启发式合并的基本思路就是这样，可以看一下代码理解。

```
il int check(int x)//统计答案
{
  int num=0,ret=0;
  for(re i=1;i<=n;i++)
    {
      if(cnt[i]==num){ret+=i;}
      else if(cnt[i]>num){num=cnt[i],ret=i;}
    }
  return ret;
}
il void add(int x){cnt[col[x]]++;}//单点增加
il void del(int x){cnt[col[x]]--;}//单点减少
il void raise(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)add(rev[i]);}//增加x子树的贡献
il void clear(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)del(rev[i]);}//清空x子树的贡献
il void dfs1(int x,int fa)
{
  dep[x]=dep[fa]+1;father[x]=fa;//处理深度，父亲
  seg[x]=++seg[0];rev[seg[x]]=x;size[x]=1;//子树大小，dfs序
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;//重儿子
    }
}
il void dfs2(int x,int flag)//flag表示是否为重儿子，1表示重儿子，0表示轻儿子
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x]||y==father[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }
  if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x]||y==father[x])continue;
      raise(y);//更新轻儿子的贡献
    }add(x);//加上x结点本身的贡献
  ans[x]=check(x);//更新答案
  if(!flag)clear(x);//如果是轻儿子，就清空
}
```
$\quad$上面的只是模板的代码，此题的完整代码在下面。
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
#define re register int
#define LL long long
#define il inline
#define pc putchar('\n')
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=5e5+5;
int n,m,next[N],head[N],go[N],tot,s[N],father[N],cnt[N][28];
int dep[N],size[N],son[N],seg[N],rev[N];
bool ans[N];
struct node{
  int x,y;};
vector<node>q[N];
il void Add(int x,int y)
{
  next[++tot]=head[x];
  head[x]=tot;go[tot]=y;
}
il void dfs1(int x,int fa)
{
  dep[x]=dep[fa]+1;size[x]=1;seg[x]=++seg[0];rev[seg[x]]=x;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      dfs1(y,x);size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;//重儿子
    }
}
il bool check(int x)//统计答案
{
  int ret=0;
  for(re i=1;i<=26;i++)if(cnt[x][i]&1)ret++;
  return ret<=1;
}
il void add(int x){cnt[dep[x]][s[x]]++;}//单点增加
il void update(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)add(rev[i]);}//增加x子树的贡献
il void del(int x){cnt[dep[x]][s[x]]=0;}//单点减少
il void out(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)del(rev[i]);}//清空x子树的贡献
il void dfs2(int x,int flag)//flag表示是否为重儿子，1表示重儿子，0表示轻儿子
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }
  if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x])continue;
      update(y);//更新轻儿子的贡献
    }add(x);//加上x结点本身的贡献
  for(re i=0;i<q[x].size();i++)
    ans[q[x][i].y]=check(q[x][i].x);//更新答案
  if(!flag)out(x);//如果是轻儿子，就清空
}
signed main()
{
  n=read();m=read();
  for(re i=2;i<=n;i++){re x=read();father[i]=x,Add(x,i);}
  string ss;cin>>ss;
  for(re i=1;i<=n;i++)s[i]=ss[i-1]-'a'+1;
  for(re i=1,x,y;i<=m;i++)x=read(),y=read(),q[x].push_back((node){y,i});//vector存储询问，将询问同一颗子树的放一起
  dfs1(1,0);dfs2(1,0);
  for(re i=1;i<=m;i++)ans[i]?puts("Yes"):puts("No");
  return 0;
}
```

---

## 作者：Taduro (赞：2)

这里是没有dsu on tree的做法，而且跑的比$dsu\ on\ tree$快。

看子树中某个深度的点能不能重拍成回文，就是看出现奇数次的字符的个数是否小于等于一，首先这个才26个字母，可以状压一下。

然后就是想办法把树上问题转到序列的一个连续区间上，dfs序上子树内节点连续，bfs序上深度递增，所以我们必须有所取舍。然而bfs序的另一个性质就是深度相同的连续一段节点的dfs序也是递增的（显然，且不会证）。

所以就有一个在bfs序上找到x的子树内深度为y的节点的做法。先预处理好深度为y的一个区间，之后二分出这个区间里dfs序在$[dfn[x],dfn[x]+size[x]-1]$中的区间。这个区间里的点就是我们所要处理的点。

对于这题，状压一下每个字符的出现次数奇偶性，就可以随便判什么回文了。

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	int next,to;
}w[500001];
int head[500001],tail,bfn[500001],val[500001],p[500001],n,num;
int deep[500001],heap,idx[500001],ed[500001],rf[500001],m,cnt;
char ch[500001];
inline void add(int x,int y){
	w[++cnt].next=head[x];
	w[cnt].to=y; head[x]=cnt;
}
void bfs(){
	heap=tail=1; bfn[tail]=1; deep[1]=1;
	while (heap<=tail){
		int x=bfn[heap]; p[heap]=idx[x]; rf[deep[x]]=heap;
		for (int i=head[x]; i; i=w[i].next){
			deep[w[i].to]=deep[x]+1;
			bfn[++tail]=w[i].to;
		}
		heap++;
	}
}
void dfs(int x){
	idx[x]=++num;
	for (int i=head[x]; i; i=w[i].next)
		dfs(w[i].to);
	ed[x]=num;
}
int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for (int i=2; i<=n; i++)
		scanf("%d",&x),add(x,i);
	dfs(1); bfs(); rf[deep[bfn[n]]+1]=n+1;
	// for (int i=1; i<=n; i++) printf("%d ",bfn[i]); puts("");
	// for (int i=1; i<=deep[bfn[n]]; i++) printf("%d ",rf[i]); puts("");
	scanf("%s",ch+1);
	for (int i=1; i<=n; i++){
		val[i]=(1<<(ch[bfn[i]]-'a'));
		val[i]^=val[i-1];
	}
	// for (int i=1; i<=n; i++) printf("%d ",val[i]); puts("");
	int l,r,u;
	for (int i=1; i<=m; i++){
		scanf("%d%d",&x,&y);
		if (y<deep[x]||y>deep[bfn[n]]){puts("Yes"); continue;}
		l=lower_bound(p+rf[y-1]+1,p+rf[y]+1,idx[x])-p;
		r=lower_bound(p+rf[y-1]+1,p+rf[y]+1,ed[x]+1)-p-1;
		// printf("%d %d %d %d\n",rf[y-1]+1,rf[y],idx[x],ed[x]+1);
		// printf("%d %d\n",l,r);
		if (l>r){puts("Yes"); continue;}
		u=val[r]^val[l-1];
		if ((u&(u-1))==0) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：foreverlasting (赞：2)

[题面](https://www.luogu.org/problemnew/show/CF570D)

dsu on tree.

开个桶维护一下每个深度的字符，判断回文就是不能出现两个奇数，复杂度是$O(nlogn*26)$，暴力$dsu$ $on$ $tree$统计就好了。

code:
```
//2018.10.24 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=5e5+10;
namespace MAIN{
    int n,m;
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N];
    int head[N],cnt;
    inline void addedge(const res &u,const res &v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
    }
    int dep[N],son[N],siz[N],fa[N];
    void Dfs(const res &x,const res &depx){
        dep[x]=depx,siz[x]=1;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            Dfs(tox,depx+1);
            siz[x]+=siz[tox];
            if(siz[tox]>siz[son[x]])son[x]=tox;
        }
    }
    char p[N];
    typedef pair<int,int> Pair;
    vector<Pair> vec[N];
#define pb push_back
#define mp make_pair
#define fi first
#define se second
    bool vis[N],ans[N];
    int tot[N][26];
    inline bool check(res *a){
        bool flag=0;
        for(res i=0;i<26;i++)
            if(a[i]&1){
                if(flag)return 1;
                flag=1;
            }
        return 0;
    }
    void update(const res &x,const res &va){
        tot[dep[x]][p[x]-'a']+=va;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(!vis[tox])update(tox,va);
        }
    }
    void dfs(const res &x,const res &flag){
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox!=son[x])dfs(tox,0);
        }
        if(son[x])dfs(son[x],1),vis[son[x]]=1;
        update(x,1);
        for(res i=0,siz=vec[x].size();i<siz;i++)ans[vec[x][i].fi]=check(tot[vec[x][i].se]);
        vis[son[x]]=0;
        if(!flag)update(x,-1);
    }
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        n=read(),m=read();
        for(res i=2;i<=n;i++)fa[i]=read(),addedge(fa[i],i);
        Dfs(1,1);
        scanf("%s",p+1);
        for(res i=1;i<=m;i++){
            res a=read(),b=read();
            vec[a].pb(mp(i,b));
        }
        dfs(1,0);
        for(res i=1;i<=m;i++)puts(ans[i]?"No":"Yes");
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：忘怀星 (赞：1)

~~逛了一圈题解区都没有长链剖分的题解啊。~~

题目询问是一个字符的集合能否经过重新排列形成回文串。可以知道当且仅当这个字符集合里出现奇数次的字符至多为一的时候可以重排为回文串。

考虑异或操作，可以把已经成双的消掉，正好对应异或操作里  `1^1=0` 。字符集大小只有 $26$ 可以考虑状态压缩。

根据上面可以知道一个状态 $x$ 可以排列成回文串当且仅当 `x == (x&-x)` 。

我们定义 dp 数组 $g[i][j]$ 表示对于点 $i$ ，往下走 $j$ 个点的点集的状态。容易得到状态转移方程 `dp[u][i+1] ^= dp[v][i]` ，这里 $v$ 是 $u$ 的儿子。

显然这个转移的复杂度是 $n^2$ 的，观察到这个状态以深度为下标，可以使用长链剖分进行优化。

给出长链剖分的代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int read()
{
	int a = 0,x = 1;char ch = getchar();
	while(ch > '9' || ch < '0') {if(ch == '-') x = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9') {a = a*10 + ch-'0';ch = getchar();}
	return a*x;
}
const int N=1e6+7;
int n,m,head[N],nxt[N],go[N],cnt,d[N],dep[N],fa[N],son[N];
int *g[N],o[N<<2],*p,q1[N],q2[N],ans[N];
char s[N];
vector<int>vec[N];
void add(int u,int v)
{
	go[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}

void dfs1(int u)
{
	dep[u] = dep[fa[u]] + 1;
	for(int e = head[u];e;e = nxt[e]) {
		int v = go[e];dfs1(v);
		if(d[v] > d[son[u]]) son[u] = v;
	}
	d[u] = d[son[u]] + 1;
}

void dp(int u)
{
	if(son[u]) {
		g[son[u]] = g[u] + 1;
		dp(son[u]);
	}
	for(int e = head[u];e;e = nxt[e]) {
		int v = go[e];if(v == son[u]) continue;
		g[v] = p,p += d[v] << 1;dp(v);
		for(int i = 0;i < d[v];i ++) g[u][i+1] ^= g[v][i];
	}
	g[u][0] ^= 1<<(s[u]-'a');
	for(int i = 0;i < vec[u].size();i ++) {
		ans[vec[u][i]] = (dep[u] > q2[vec[u][i]] || q2[vec[u][i]] >= dep[u]+d[u]) || (g[u][q2[vec[u][i]]-dep[u]] == (g[u][q2[vec[u][i]]-dep[u]]&-g[u][q2[vec[u][i]]-dep[u]]));
	}
}

int main()
{
	n = read(), m = read();
	for(int i = 2;i <= n;i ++) {
		fa[i] = read();add(fa[i],i);
	}
	scanf("%s",s+1);
	for(int i = 1;i <= m;i ++) {
		q1[i] = read(),q2[i] = read();
		vec[q1[i]].push_back(i);
	}
	dfs1(1);g[1] = p = o;p += d[1]<<1;
	dp(1);for(int i = 1;i <= m;i ++) puts(ans[i]?"Yes":"No");
	return 0;
}
```

---

## 作者：zyx10 (赞：0)

这是一个不用树上启发式合并的题解  
## Description
[传送门](https://www.luogu.com.cn/problem/CF570D)  
给定一个以 1 为根的 $n$ 个节点的树，每个点上有一个字母 $(a-z)$ ，每个点的深度定义为该节点到 1 号节点路径上的点数.每次询问 $(a,b)$ 查询以 $a$ 为根的子树内深度为 $b$ 的节点上的字母重新排列之后是否能构成回文串.

## Solution——dfs+作差
一堆字符能拼成回文串当且仅当最多只有一个字符出现过奇数次。  
考虑如何消除一棵子树对另一棵子树的影响。  
把 26 个字母压成一个二进制串，如果某一位有 1 说明这个字符出现了奇数次，这样就能很方便处理多个子树之间的关系：用遍历子树之后的状态减去遍历子树之前的状态 **（这里的减去的意思不是‘-’，而是利用异或的性质得到当前状态）**。  
那用 vector 存下遍历某一颗子树时需要查询的答案，就能方便地得出答案了。

## Code
```
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<utility>
#define sz(x) (int)x.size()//这样定义在Ubuntu下就不会warning
#define fi first
#define se second
#define mk make_pair
using namespace std;
const int N=5e5+5;
int n,m,dep[N],t[N];
vector<int> e[N],ans[N];
vector<pair<int,int> > ask[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >res;
char tmp[N];

inline void dfs (int x) {
	t[dep[x]]^=(1<<(tmp[x]-'a'));
	for (int i=0;i<sz(ask[x]);i++) ans[x][i]=t[ask[x][i].fi];//存下遍历之前的答案
	for (int i=0;i<sz(e[x]);i++) {
		int v=e[x][i];
		dep[v]=dep[x]+1;
		dfs(v);
	}
	for (int i=0;i<sz(ask[x]);i++) {
		int bef=ans[x][i];
		int now=t[ask[x][i].fi];
		now^=bef;//再用后来的答案异或之前的就能得出答案
		now^=now&(-now);//lowbie，能异或掉now的存在的最低位的1
		if (now) res.push(mk(ask[x][i].se,0));
		else res.push(mk(ask[x][i].se,1));
	}
}

inline int read () {
	int res=0,fl=1;
	char ch;
	while ((ch=getchar())&&(ch<'0'||ch>'9'))	if (ch=='-') fl=-1;
	res=ch^48;
	while ((ch=getchar())&&ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch^48);
	return res*fl;
}

int main () {
	n=read();m=read();
	for (int i=2,x;i<=n;i++) {
		x=read();
		e[x].push_back(i);
	}
	scanf("%s",tmp+1);
	for (int i=1,v,h;i<=m;i++) {
		v=read();h=read();
		ask[v].push_back(mk(h,i));//要把id存下以存储答案
		ans[v].push_back(0);//要提前放入，不能在用的时候直接用数组方式定义，否则会出错
	}
	dep[1]=1;
	dfs(1);
	while (!res.empty()) {
		int ty=res.top().se;res.pop();
		if (ty) puts("Yes");
		else puts("No");
	}
	return 0;
}

---

## 作者：寒冰大大 (赞：0)

坑啊，没这个节点也算回文也要输出 `Yes`

貌似没见着用重链剖分的写的，于是就来写一波

按照套路设 $f[i][j][k]$ 表示 $i$ 的子树内深度为 $j$ 的字母 $k$ 的个数

然后判断能否有回文只需看是否有两个及以上的字母出现次数为奇数次即可

另外像上面那样开数组的话用指针估计有点难受，建议 $j,k$ 压成一维

~~一定不要想我作死先判断不合法的情况~~


```cpp
#include<touwenjian.h>

using namespace std;

const int maxn=500500;

int *f[maxn],tmp[maxn*30],*st=tmp;
int n,m,head[maxn],vnum[maxn];
int size,son[maxn],dis[maxn],ans[maxn];
int ls[maxn];

vector <pair<int,int> > q[maxn];

struct edge{
	int next,to;
}e[maxn]; 

inline void addedge(int next,int to)
{
	e[++size].to=to;
	e[size].next=head[next];
	head[next]=size;
}

void dfs1(int t,int fat)
{
	int i,j;
	for(i=head[t];i;i=e[i].next)
	{
		j=e[i].to;
		ls[j]=ls[t]+1;
		dfs1(j,t);
		if(dis[j]>dis[son[t]]) son[t]=j;
	}
	dis[t]=dis[son[t]]+1;
}


void dfs2(int t,int fat)
{
	f[t][vnum[t]]=1;
	if(son[t])
	{
		f[son[t]]=f[t]+27;
		dfs2(son[t],t);
	} 
	int i,j;
	int k,l;
	for(i=head[t];i;i=e[i].next)
	{
		j=e[i].to;
		if(j==son[t]) continue;
		f[j]=st; 
		st+=dis[j]*27; 
		dfs2(j,t);
		for(k=1;k<=dis[j];k++)
		for(l=1;l<=26;l++)
		f[t][k*27+l]+=f[j][(k-1)*27+l];
	}
	for(i=0;i<q[t].size();i++)
	{	
		int looker=0;
		int tmph=q[t][i].first-ls[t];	
		int tbh=q[t][i].second;
		if(tmph>=dis[t]||tmph<0)
		{
			ans[tbh]=1;
			continue;
		}
		for(j=1;j<=26;j++)
		{
			if(f[t][tmph*27+j]&1) looker++;
		}
		if(looker==1||!looker) ans[tbh]=1;
	}
}

int main()
{
	//ios::sync_with_stdio(false);
	register int i,j;
	scanf("%d %d",&n,&m);
	int t1,t2;
	for(i=2;i<=n;i++)
	{
		scanf("%d",&t1);
		addedge(t1,i); 
	}
	char t;
	scanf("\n");
	for(i=1;i<=n;i++)
	{
		scanf("%c",&t);
		vnum[i]=(t-'a'+1);
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d %d",&t1,&t2);
		q[t1].push_back(make_pair(t2,i));
	}
	ls[1]=1;
	dfs1(1,1);
	f[1]=st; st+=dis[1]*27;
	dfs2(1,1);
	for(i=1;i<=m;i++) 
	{
		if(ans[i]) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

```


---

## 作者：柳苏明 (赞：0)

# 题意

给定一棵以$1$为根的树，每个点有一个小写字母。每次询问以一个点为根的子树内深度为$d$的所有点构成的字母集能不能重排为一个回文串。

# 解法

容易发现一个字母集可以重排为回文串，当且仅当小于等于一个字母出现奇数次。于是问题转化为以一个点为根的子树内深度为$d$的所有点出现奇数次的字母有几个。

考虑二进制数$x$，其第$i$位表示字母`char('a' + i)`是否出现奇数次。如果$popcount(x) \le 1$则它可以重排为回文串。对于每棵子树维护一颗线段树，其下标为深度，节点权值为深度区间字母集的二进制数。`pushup`时将左右儿子异或起来即可。

考虑如何优化时空，使用线段树合并。每个节点继承它子节点的线段树，对于$u$节点的询问在dfs到它时离线回答即可。

这里使用了线段树合并的在线方法。当两颗线段树合并时，新建一颗线段树继承这两颗线段树合并后的信息，并保留原线段树。这样dfs完以后也保留了每个节点的线段树，对于`u`的询问可以直接在它的线段树上查。这个大概可以看作线段树合并的可持久化。

注意亿些细节，比如$h\le n$，在dfs是要先合并再修改，否则空间常数将增大一倍。

时空复杂度$\mathcal{O}(nlogn)$。

# 代码

```cpp
const int maxn(5e5+10);
int n,m;
char s[maxn];

struct Edge {
	int v,next;
	Edge(const int &v,const int &next) :v(v),next(next) {}
	Edge() {}
}e[maxn];
int head[maxn],cnt;
inline void AddEdge(const int &u,const int &v) {
	e[++cnt]=Edge(v,head[u]);
	head[u]=cnt;
}

int MaxDepth;
namespace SegmentTree {
	int val[maxn<<5],lc[maxn<<5],rc[maxn<<5],Node_Cnt;
	inline void pushup(const int &a) {
		val[a]=val[lc[a]]^val[rc[a]];
	}
	void Modify(const int &p,const int &k,int &a,const int &l=1,const int &r=MaxDepth) {
		if(!a) a=++Node_Cnt;
		if(l==r) return void(val[a]^=k);
		int mid((l+r)>>1);
		if(p<=mid) Modify(p,k,lc[a],l,mid);
		else Modify(p,k,rc[a],mid+1,r);
		pushup(a);
	}
	int Query(const int &p,const int &a,const int &l=1,const int &r=MaxDepth) {
		if(!a) return 0;
		if(l==r) return val[a];
		int mid((l+r)>>1);
		if(p<=mid) return Query(p,lc[a],l,mid);
		else return Query(p,rc[a],mid+1,r);
	}
	int Merge(const int &a,const int &b,const int &l=1,const int &r=MaxDepth) {
		if(!a||!b) return a|b;
		int now(++Node_Cnt);
		if(l==r) val[now]=val[a]^val[b];
		else {
			int mid((l+r)>>1);
			lc[now]=Merge(lc[a],lc[b],l,mid);
			rc[now]=Merge(rc[a],rc[b],mid+1,r);
			pushup(now);
		}
		return now;
	}
}
int root[maxn],depth[maxn];
void Dfs1(const int &u=1,const int &fa=0) {
	depth[u]=depth[fa]+1;MaxDepth=max(MaxDepth,depth[u]);
	for(int i(head[u]);i;i=e[i].next) {
		const int &v(e[i].v);
		Dfs1(v,u);
	}
}
void Dfs2(const int &u=1) {
	for(int i(head[u]);i;i=e[i].next) {
		const int &v(e[i].v);
		Dfs2(v);
		root[u]=SegmentTree::Merge(root[u],root[v]);
	}
	SegmentTree::Modify(depth[u],1<<(s[u]-'a'),root[u]);
}

int main(void) {
	cin>>n>>m;
	for(int i(2);i<=n;i++) {
		int x;cin>>x;
		AddEdge(x,i);
	}
	cin>>(s+1);
	Dfs1();Dfs2();
	for(int i(1);i<=m;i++) {
		int v,h;
		cin>>v>>h;
		if(h>MaxDepth) {
			cout<<"Yes\n";
			continue;
		}
		int res(SegmentTree::Query(h,root[v]));
		if(res==(res&-res)) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 114514191810;
}
```



---

