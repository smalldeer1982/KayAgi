# Dating

## 题目描述

This story is happening in a town named BubbleLand. There are $ n $ houses in BubbleLand. In each of these $ n $ houses lives a boy or a girl. People there really love numbers and everyone has their favorite number $ f $ . That means that the boy or girl that lives in the $ i $ -th house has favorite number equal to $ f_{i} $ .

The houses are numerated with numbers $ 1 $ to $ n $ .

The houses are connected with $ n-1 $ bidirectional roads and you can travel from any house to any other house in the town. There is exactly one path between every pair of houses.

A new dating had agency opened their offices in this mysterious town and the citizens were very excited. They immediately sent $ q $ questions to the agency and each question was of the following format:

- $ a\ b $ — asking how many ways are there to choose a couple (boy and girl) that have the same favorite number and live in one of the houses on the unique path from house $ a $ to house $ b $ .

Help the dating agency to answer the questions and grow their business.

## 说明/提示

In the first question from house $ 1 $ to house $ 3 $ , the potential couples are $ (1,3) $ and $ (6,3) $ .

In the second question from house $ 7 $ to house $ 5 $ , the potential couples are $ (7,6) $ , $ (4,2) $ and $ (4,5) $ .

## 样例 #1

### 输入

```
7
1 0 0 1 0 1 0
9 2 9 2 2 9 9
2 6
1 2
4 2
6 5
3 6
7 4
2
1 3
7 5
```

### 输出

```
2
3
```

# 题解

## 作者：Alex_Eon (赞：1)

#### [$\color{red}博客内食用效果更佳（点我）$](https://www.luogu.com.cn/blog/Ksy/solution-cf852i)
### 题外话
考场上写的第一次树上莫队，运气比较好过了，写题解记录一下。  
后续可能在博客中补上莫队的部分。
### 主体思路：树上莫队
### 复杂度：$O(m\sqrt n)$
### 完整思路
简单说一下树上莫队的基本实现方式，若不会莫队请去学习莫队。

考虑 DFS 记录每个点的入栈出栈序，在序列上实现莫队。（画图是最直观的，如果不懂自己画画模拟一下就好了。）

可以理解为将莫队左右端点在**树上的移动**转换为在**出栈入栈序列上的移动**，当维护区间在出栈入栈序列上移动时，可以对应 DFS 的**递归、回溯**。每碰到一个点，若其已经被维护，则将其删除（对应回溯），若其未被维护，则将其维护（对应递归）。

考虑如何将询问点对转化为区间：

- 当询问两点**具有祖先关系**的时候，两个点的出栈入栈区间是**具有包含关系**的，此时我们以祖先入栈为左端点，子代节点入栈作为右端点建立询问区间，刚好可以维护一条整链。
- 类似的，对于**不具有祖先关系**的两点，入栈出栈区间**没有交集**，我们以入栈较早的出栈时间戳作为左端点，另一点的入栈作为右端点建立询问区间。特殊地，这个询问区间**无法维护到两点的 LCA**，我们在每次统计时特殊加入两点 LCA 即可。

接下来考虑本题需要维护什么，离散化后对于男女各开一个桶，每次加入时记录一下贡献即可，删除同理。

### 具体实现

这里介绍实现的过程以及一些细节。

1. 读入树后进行离散化，并且 DFS 预处理出出栈入栈序列，每个点也要存下来自己的时间戳。
2. 处理询问，根据祖先关系分类讨论，建立询问区间，特殊处理不具有祖先关系点对的 LCA，具有祖先关系留空即可（用 ST 表或其他求法）。
3. 处理分块并对询问排序（可以采用奇偶优化排序）。
4. 用异或操作标记一个点经过次数来判断需要加入还是删除，进行平跑莫队即可。

### 代码实现需要注意的地方：

- 也需要开 **long long**，防炸。
- 出栈入栈数组要开双倍空间。
- 莫队时先扩展左右端点在收缩左右端点（莫队常识）。

### 参考代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define UN unsigned
using namespace std;
//--------------------//
//IO
inline int rd()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
//--------------------//
const int N=1e5+5,M=2e5+5;

int n,m;
//--------------------//
struct Edge
{
    int to,nex;
}edge[M];
int tot,head[N];
void add(int from,int to)
{
    edge[++tot]={to,head[from]};
    head[from]=tot;
    return;
}
struct Poi
{
    int sex,val;
    int st,ed;//出栈入栈时间戳
    int fa,dep;//求 LCA 时需要用到的
    bool v;
}p[N];
int ecnt,el[M];//出栈入栈序列
void DFS(int now,int fa)
{
    p[now].fa=fa,p[now].dep=p[fa].dep+1;
    el[++ecnt]=now;//打时间戳
    p[now].st=ecnt;
    for(int to,i=head[now];i;i=edge[i].nex)
    {
        to=edge[i].to;
        if(to==fa)
            continue;
        DFS(to,now);
    }
    el[++ecnt]=now;
    p[now].ed=ecnt;
    return;
}
const int LG=30;
struct ST//ST 表求 LCA
{
    int stv[M][LG],lg[M];
    void init()
    {
        for(int i=2;i<=2*n;i++)
            lg[i]=lg[i-1]+((1<<(lg[i-1]+1))==i);
        for(int i=1;i<=2*n;i++)
            stv[i][0]=el[i];
        for(int j=1;j<=lg[2*n];j++)
            for(int i=1;i<=2*n&&lg[2*n-i+1]>=j;i++)
                stv[i][j]=p[stv[i][j-1]].dep<p[stv[i+(1<<(j-1))][j-1]].dep?stv[i][j-1]:stv[i+(1<<(j-1))][j-1];
        return;
    }
    int query(int l,int r)
    {
        int lg_len=lg[r-l+1];
        return p[stv[l][lg_len]].dep<p[stv[r-(1<<lg_len)+1][lg_len]].dep?stv[l][lg_len]:stv[r-(1<<lg_len)+1][lg_len];
    }
}S;

struct Que
{
    int l,r,id,tp;
}que[N];
int len,bl[M];
bool cmp(Que x,Que y){return (bl[x.l]^bl[y.l])?bl[x.l]<bl[y.l]:((bl[x.l]&1)?x.r<y.r:x.r>y.r);}//奇偶优化排序
LL ans[N];

void init()//分块的预处理
{
    len=sqrt(2*n);
    for(int i=1;i<=2*n;i++)
        bl[i]=bl[i-1]+(bl[i-1]*len+1==i);
    return;
}

LL res;
int t[2][N];
void ins(int x)//加入
{
    t[p[x].sex][p[x].val]++;//桶
    res+=t[p[x].sex^1][p[x].val];//加入贡献
    return;
}
void del(int x)//删除
{   
    t[p[x].sex][p[x].val]--;
    res-=t[p[x].sex^1][p[x].val];//删除贡献
    return;
}
void work(int x)
{
    if(p[el[x]].v)//判断经过次数，奇数次加入，偶数次删除
        del(el[x]);
    else
        ins(el[x]);
    p[el[x]].v^=1;//打标记
    return;
}
int tcnt,tem[N];//离散化数组
//--------------------//
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].sex);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].val),tem[++tcnt]=p[i].val;

    //离散化
    sort(tem+1,tem+tcnt+1);
    tcnt=unique(tem+1,tem+tcnt+1)-tem-1;
    for(int i=1;i<=n;i++)
        p[i].val=lower_bound(tem+1,tem+tcnt+1,p[i].val)-tem;
    for(int from,to,i=1;i<n;i++)
        scanf("%d%d",&from,&to),add(from,to),add(to,from);

    //初始化
    DFS(1,0);
    S.init();
    scanf("%d",&m);

    //处理询问区间
    for(int x,y,i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        if(p[x].st>p[y].st)
            swap(x,y);
        if(p[x].ed<p[y].st)
            que[i]={p[x].ed,p[y].st,i,p[S.query(p[x].ed,p[y].st)].fa};
        else
            que[i]={p[x].st,p[y].st,i,0};
    }

    //分块、排序
    init();
    sort(que+1,que+m+1,cmp);
    int nowl=1,nowr=0;//注意初值设置
    for(int i=1;i<=m;i++)
    {
        //莫队主要部分
        while(nowl>que[i].l)
            work(--nowl);
        while(nowr<que[i].r)
            work(++nowr);
        while(nowl<que[i].l)
            work(nowl++);
        while(nowr>que[i].r)
            work(nowr--);
        ans[que[i].id]=res;
        if(que[i].tp)
            ans[que[i].id]+=t[p[que[i].tp].sex^1][p[que[i].tp].val];
    }
    for(int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
```


---

## 作者：wishapig (赞：1)

### 奇怪树分块实现的（真的在树上走的）树上莫队

分块方式需要满足块个数有保证，每个块的直径有保证。

#### 块的构造：

考虑 dfs，对点 $u$，dfs 它的儿子 $v$，把传上来的没用过的节点**顺序**接成一个大的 $\rm vector$，再加入点 $u$。

然后在这个 $\rm vector$ 内以 $\sqrt{n}$ 个为一组进行分块，剩下的部分传上去。

最后传出的所有点分成一个块。

注意这种分块方式可以满足上面的要求，但它并不保证每个块是连通的。

#### 莫队：

排序方式：询问点对 $(u,v)$，先以 $u$ 所在块的编号从小到大排，相同的再按照 $\operatorname{dfn}[y]$ 从小到大排。

移动：目前在链 $(x,y)$，要把 $x$ 移到点 $z$，找到 $x,y$ 路径上与点 $z$ 最近的的一个点 $u$（也就是以 $z$ 为根，$x$与$y$ 的 LCA），注意到这个点为 $x,y,z$ ”三者交汇“之处，同时，它等于 $(x,y),(x,z),(y,z)$ 形成的三个 $\rm LCA$ 中深度最大的那个。

抓出 $x$ 到 $z$ 的路径，$u$ 之前的点删掉，$u$ 之后的点加上。

注意到移动过程中始终不会出现“删空”的情况。

常数挺大的。

```c++
const int N=1e5+5;
int s[N],c[N],_[N],dep[N],dfn[N],fa[17][N],pos[N],seq[N],cnt[N][2],n,q,B,blo,u,v,tim;
vector<int> G[N];
long long ans[N],res;
struct Ques{ int F,S,id; } qry[N];
bool operator < (const Ques& a, const Ques& b){ return pos[a.F]==pos[b.F]?dfn[a.S]<dfn[b.S]:pos[a.F]<pos[b.F]; }
inline int LCA(int x, int y){
	if (x==y) return x;
	if (dep[x]<dep[y]) swap(x,y);
	int d=dep[x]-dep[y];
	for (int i=16; ~i; i--)
		if (d&(1<<i)) x=fa[i][x];
	if (x==y) return x;
	for (int i=16; ~i; i--)
		if (fa[i][x]^fa[i][y]) x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
inline void modify(int u, int x){
	res-=1ll*cnt[c[u]][0]*cnt[c[u]][1];
	cnt[c[u]][s[u]]+=x;
	res+=1ll*cnt[c[u]][0]*cnt[c[u]][1];
}
inline void Move(int x, int y, int z){
	int L1=LCA(x,y),L2=LCA(y,z),L3=LCA(x,z),u=L1,v=-1,len=0;
	u=dep[u]>dep[L2]?u:L2;
	u=dep[u]>dep[L3]?u:L3;
	for (int i=x; i!=L3; i=fa[0][i]) i==u?v=1:(modify(i,v),0);
	L3==u?v=1:(modify(L3,v),0);
	for (int i=z; i!=L3; i=fa[0][i]) seq[++len]=i;
	for (int i=len; i>=1; i--) seq[i]==u?v=1:(modify(seq[i],v),0);
}
vector<int> dfs(int u, int f){
	dfn[u]=++tim,dep[u]=dep[f]+1,fa[0][u]=f;
	for (int i=1; i<=16; i++) fa[i][u]=fa[i-1][fa[i-1][u]];
	vector<int> tmp,ret;
	for (int v:G[u])
		if (v!=f){
			auto p=dfs(v,u);
			tmp.insert(tmp.end(),p.begin(),p.end());
		}
	tmp.push_back(u); int s=tmp.size(),now=0;
	for (; now+B<=s; now+=B){
		blo++; for (int i=now; i<now+B; i++) pos[tmp[i]]=blo;
	}
	ret.resize(s-now);
	for (int i=now; i<s; i++) ret[i-now]=tmp[i];
	return ret;
}
int main(){
	scanf("%d",&n); B=sqrt(n);
	for (int i=1; i<=n; i++) scanf("%d",&s[i]);
	for (int i=1; i<=n; i++) scanf("%d",&c[i]),_[i]=c[i];
	sort(_+1,_+1+n); int _c=unique(_+1,_+1+n)-_-1;
	for (int i=1; i<=n; i++) c[i]=lower_bound(_+1,_+1+_c,c[i])-_;
	for (int i=1; i<n; i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	auto R=dfs(1,0);
	if (!R.empty()){ blo++; for (int v:R) pos[v]=blo; }
	scanf("%d",&q);
	for (int i=1; i<=q; i++) scanf("%d%d",&qry[i].F,&qry[i].S),qry[i].id=i;
	sort(qry+1,qry+1+q);
	qry[0]={qry[1].F,qry[1].F,0}; cnt[c[qry[1].F]][s[qry[1].F]]=1;
	for (int i=1; i<=q; i++){
		Move(qry[i-1].F,qry[i-1].S,qry[i].F);
		Move(qry[i-1].S,qry[i].F,qry[i].S);
		ans[qry[i].id]=res;
	}
	for (int i=1; i<=q; i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：xzggzh1 (赞：0)

题意：

给定 $n$ 个节点的树，每个节点有一个男生和女生。每个人都有一个喜欢的数字。

然后 $m$ 次询问，每次询问树上从 $a$ 到 $b$ 的路径中，有多少对男女喜欢的数字相同。

$n,m\leq 10^5$。

---

树上序列询问，可以考虑树上莫队，$n,m$ 在 $10^5$ 根号算法完全能过。

由于 [这个题SP10707](https://www.luogu.com.cn/problem/SP10707) 才是树上莫队“公认”的板子题，本题直接套用模板即可，所以本题解里将会略去对模板的解释。

要求多少对男女喜欢的数字相同，要男女分开记录，分开算。

记录男和女分别喜欢某个数字的人数，当加入一个点时，答案增加该点异性相同数字的人数，删除时，答案减少该点异性相同数字的人数。

---

核心代码：（板子略去）

```cpp

struct edge{int to,next;}e[N*2];
struct que{int l,r,id,lc;}q[N];
bool cmp(que x,que y){if (bl[x.l]==bl[y.l])return x.r<y.r;return bl[x.l]<bl[y.l];}
void add(int x,int y){;}void dfs(int x){;}int lca(int x,int y){;}
void work(int x){
	int v=f[x];
	if (!in[x]){
		if (b[x]) now+=cntg[v],cntb[v]++;
		else now+=cntb[v],cntg[v]++;
	}
	else{
		if (b[x]) now-=cntg[v],cntb[v]--;
		else now-=cntb[v],cntg[v]--;
	}
	in[x]^=1;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	for (int i=1;i<=n;i++) scanf("%d",&f[i]),num[i]=f[i];
	sort(num+1,num+n+1);
	for (int i=1;i<=n;i++) f[i]=lower_bound(num+1,num+n+1,f[i])-num;
	for (int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfs(1);int sz=666*2;
	for (int i=1;i<=T;i++)bl[i]=(i-1)/sz+1;
	int Q; scanf("%d",&Q);
	for (int i=1;i<=Q;i++){
		int x,y; scanf("%d%d",&x,&y);
		if (st[x]>st[y]) swap(x,y);
		q[i]=(que){st[x]+1,st[y],i,lca(x,y)};
	}
	sort(q+1,q+Q+1,cmp);
	int l=1,r=0;
	for (int i=1;i<=Q;i++){
		for (;r<q[i].r;work(dfn[++r]));
		for (;r>q[i].r;work(dfn[r--]));
		for (;l<q[i].l;work(dfn[l++]));
		for (;l>q[i].l;work(dfn[--l]));
		work(q[i].lc);
		ans[q[i].id]=now;
		work(q[i].lc);
	}
	for (int i=1;i<=Q;i++)printf("%I64d\n",ans[i]);
} 

```

---

