# Fairy

## 题目描述

很久很久以前，有一只可爱的星族猫 A。

一天，一只野心勃勃的可爱小猫 B 来找他，请 A 预测他的未来。

A 掐爪一算，说：“你以后会成为族长。”

B 很高兴，然而 A 接着说：“但是，这个预言不一定会成真。”A 在地上画了若干个点，把其中一些点用线段连起来，“如果你能够擦掉一条边，使得你可以把所有的点分为‘猫点’和‘猎物点’两种，任意两个‘猫点’都不相邻，任意两个‘猎物点’也都不相邻，那么预言就会成真。”

B 很想当族长。于是他请来了你——全族群中最聪明的猫来帮他算一算，他所有能够使得预言成真的擦边方案数。

## 说明/提示

$1 \le n \le 10^4, 0 \le m \le 10^4, \forall 1 \le i \le m, 1 \le u_i,v_i \le n$。

## 样例 #1

### 输入

```
4 4
1 2
1 3
2 4
3 4
```

### 输出

```
4
1 2 3 4 ```

## 样例 #2

### 输入

```
4 5
1 2
2 3
3 4
4 1
1 3
```

### 输出

```
1
5 ```

# 题解

## 作者：command_block (赞：76)

**题意** ： 给出一张无向图，求删除一条边后此图变成二分图的所有方案。

$n,m\leq 10^4$ ，时限$\texttt{1.5s}$。

------------

本题数据范围较弱，但存在线性做法。

考虑二分图的充要条件 ： 不存在奇环。

若原图本就为二分图，显然随意删除都可行。

否则，图中存在奇环，我们需要删一条边破坏图中所有的奇环。

显然，答案是**所有奇环的交集中的边**。

但是，奇环的个数可能非常多，不可能实际求解交集。

接下来的思路受到 [P4151 [WC2011]最大XOR和路径](https://www.luogu.com.cn/problem/P4151) 的启发。

一个自交的奇环必然引出一个简单奇环，所以我们只需要考虑**简单环**。

对于图中的一个连通块，先求出任意一个生成树，然后查看非树边。

此时容易处理只含有一条非树边的环，且每条非树边恰好对应一个这样的环，我们把这种环叫做**本原环**。

- **树边**

若某条非树边形成的本原环是奇环，则这条边是坏边，否则是好边。

对于一条非树边，称其本原环中的树边被其覆盖。

- **性质①** ： 答案边 $\Rightarrow$ 被所有坏边覆盖

  考虑每个坏边形成的奇环，显然。
  
- **性质②** ： 答案边不会被好边覆盖

  ![](https://cdn.luogu.com.cn/upload/image_hosting/6uok4em0.png)
  
  图中黑色为树边。

  （反证）一条答案边（紫色）肯定被某条坏边（绿色）覆盖。
  
  然而，该坏边和好边（红色）的本原环异或并一定能组成一个奇环（蓝色）。
  
  原因 ： 奇环 + 偶环 - 消去两次的公共部分 = 奇环
  
  这个奇环一定不包含刚才提到的答案边，矛盾。
  
- **性质③** ： 不被任何好边覆盖，且被所有坏边覆盖的边，就是答案边。

  对于某个简单环，将其中所有非树边的本原环进行异或并，能得到它本身。
  
  若非树边中有奇数个坏边，则形成奇环，否则是偶环。
  
  对于一条不被任何好边覆盖的边，其在异或并中是否出现取决于坏边对其覆盖的次数。
  
  若改变被所有坏边覆盖，则在此时恰好被覆盖奇数次，总是被包含在异或并中。
  
根据性质③，容易想到如下算法。

我们统计只含有一条非树边的奇环数量，设为 $cnt$。

对于坏边，则将其覆盖的边 $+1$ ，好边则将其覆盖的边 $-1$。

最后边权为 $cnt$ 的边即为答案。

朴素的链加处理方法——树上差分需要求 $\rm lca$ ，复杂度带 $\log$。

但是，注意到我们进行操作的是非树边，在 $\rm dfs$ 的过程中，所有非树边都是返祖边，所以容易 $O(1)$ 实现差分。

- **非树边**

若 $cnt=1$ ，则可以删除唯一的一条坏边，否则坏边不可删除。

------------

注意，本题没有 $\rm SPJ$ ,需要将边的编号排序。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define pb push_back
#define MaxN 10500
using namespace std;
vector<int> g[MaxN],p[MaxN];
int cnt,s[MaxN],sp,ans[MaxN],tn;
bool dis[MaxN],vis[MaxN],e[MaxN];
void pfs(int u)
{
  vis[u]=1;
  for (int i=0,v;i<g[u].size();i++)
    if (!vis[v=g[u][i]]){
      dis[v]=dis[u]^1;
      e[p[u][i]]=1;
      pfs(v);
    }else if (!e[p[u][i]]){
      e[p[u][i]]=1;
      if (dis[u]==dis[v]){
        cnt++;s[u]++;s[v]--;
        sp=p[u][i];
      }else {s[u]--;s[v]++;}
    }
}
void dfs(int u)
{
  vis[u]=1;
  for (int i=0,v;i<g[u].size();i++)
    if (!vis[v=g[u][i]]){
      dfs(v);
      if (s[v]==cnt)ans[++tn]=p[u][i];
      s[u]+=s[v];
    }
}
int n,m;
int main()
{
  scanf("%d%d",&n,&m);
  for (int i=1,u,v;i<=m;i++){
    scanf("%d%d",&u,&v);
    g[u].pb(v);p[u].pb(i);
    g[v].pb(u);p[v].pb(i);
  }
  for (int i=1;i<=n;i++)
    if (!vis[i])pfs(i);
  if (!cnt){
    printf("%d\n",m);
    for (int i=1;i<=m;i++)
      printf("%d ",i);
    return 0;
  }
  for (int i=1;i<=n;i++)vis[i]=0;
  for (int i=1;i<=n;i++)
    if (!vis[i])dfs(i);
  if (cnt==1)ans[++tn]=sp;
  printf("%d\n",tn);
  sort(ans+1,ans+tn+1);
  for (int i=1;i<=tn;i++)
    printf("%d ",ans[i]);
  return 0;
}
```


---

## 作者：Makasukaka (赞：22)

### 题意：
         给出一张无向图，求删除一条边后此图变成二分图的所有删边种类。
### 分析：
1：一个图是二分图当且仅当它没有奇环。

2：如果一个图已经是二分图，那么删除任意一条边都还是二分图。

3：考虑随便求出一棵生成树。那么我们把非树边都拿出来。求出它们两个点的LCA和距离dis。这样，我们可以尝试一条条把非树边放在树上，看是否会构成奇环，统计奇环条数flag。

4：为了以下叙述方便，把会构成奇环的非树边叫做矛盾边，不会构成奇环的非树边叫做合法边。一条树上边被非树上边(u,v)“覆盖”，即这条树上边在u-v的树上路径上。

5：如果flag为0，即没有奇环。由2，只要把所有边序号输出即可。

6：如果flag为1，即有一个奇环。那么我们的一个选择是把该条矛盾边删掉，或者是在该矛盾边(u,v)的树上路径上找一些边，满足这些边不被合法边覆盖。至于为什么要让其不被合法边覆盖，大家可以画一个图。这样可以保证该矛盾边不会与其他非矛盾边再形成奇环。

7：如果flag>1，即有若干个奇环。那么我们只能选择删除树上那些，被所有矛盾边覆盖，且不被非矛盾边覆盖的边了。如何判断呢？我们可以利用树上差分的思想，记d[x]为x和其父亲构成的边上的差分值，把矛盾边的路径+1,非矛盾边的路径上-1。那么最后树上的点x如果满足d[x]==flag，那么它与它的父亲组成的边就是我们所求的。详细可见代码。

8：注意可能此图并不连通。

### Codes:
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=3e4+5;
int v[N<<1],head[N],nxt[N<<1],tot;
int vq[N<<1],nxtq[N<<1],headq[N],w[N<<1],totq;
int f[N],las[N],fa[N],dis[N],d[N],tag[N],ans[N],w2[N],w3[N],w4[N];
int vis1[N],vis2[N];
int n,m,cnt,flag,ansn,tht,endd,sta,turn,tot4;
struct edge{
    int x,y,id,lca;
}a[N],b[N],c[N];
inline int getf(int x){return fa[x]==x?x:fa[x]=getf(fa[x]);}
inline int getf1(int x){return f[x]==x?x:f[x]=getf1(f[x]);}
inline void merge(int x,int y){
    int f1=getf(x),f2=getf(y);
    fa[f1]=f2;
}
inline void add(int x,int y,int z){
    v[++tot]=y;w4[tot]=z;
    nxt[tot]=head[x];
    head[x]=tot;
}
inline void addq(int x,int y,int z){
    vq[++totq]=y;w[totq]=z;
    nxtq[totq]=headq[x];
    headq[x]=totq;
}
inline void tarjan(int x){
    f[x]=x;vis1[x]=x;
    for(int i=head[x];i;i=nxt[i]){
        int y=v[i];
        if(!f[y]){
            dis[y]=dis[x]+1;
            w3[y]=w4[i];
            w2[y]=w[i];
            tarjan(y);
            f[y]=x;
            las[y]=x;
        }
    }
    for(int i=headq[x];i;i=nxtq[i]){
        int y=vq[i],c=w[i];
        if(f[y])b[c].lca=getf1(y);
    }
}
inline void dfs(int x,int fa){
    vis2[x]=1;
    for(int i=head[x];i;i=nxt[i]){
        int y=v[i];
        if(y!=fa){
            dfs(y,x);
            d[x]+=d[y];
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)scanf("%d%d",&a[i].x,&a[i].y),a[i].id=i;
    for(int i=1;i<=n;++i)fa[i]=i;
    for(int i=1;i<=m;++i){
        int x=a[i].x,y=a[i].y;
        if(getf(x)!=getf(y)){//生成树
            merge(x,y);
            add(x,y,i);add(y,x,i);
        }
        else{
            b[++cnt].x=x;b[cnt].y=y;
            b[cnt].id=a[i].id;
            addq(x,y,cnt);addq(y,x,cnt);
        }
    }
    for(int i=1;i<=n;++i)if(!vis1[i])tarjan(i);//tarjan求lca,dis等
    for(int i=1;i<=cnt;++i){
        int x=b[i].x,y=b[i].y,p=b[i].lca,delta=1,curd;
        curd=dis[x]+dis[y]-2*dis[p];
        if(curd&1)delta=-1;//偶环
        else {
            flag++;endd=y;
            sta=x;turn=p;tht=b[i].id;
        }//奇环
        d[x]+=delta;d[y]+=delta;d[p]-=2*delta;//差分
    }
    for(int i=1;i<=n;++i)if(!vis2[i])dfs(i,i);//求d的字树和
    if(!flag){//无奇环
        printf("%d\n",m);
        if(m){
            for(int i=1;i<m;++i)printf("%d ",i);
            printf("%d\n",m);
        }
    }
    else if(flag==1){//一奇环
        int tot3=0;
        for(int i=endd;i!=turn;i=las[i]){
            if(d[i]==1)//只被这一条边覆盖
            ans[++tot3]=w3[i];
        }
        for(int i=sta;i!=turn;i=las[i]){
            if(d[i]==1)//只被这一条边覆盖
            ans[++tot3]=w3[i];
        }
        ans[++tot3]=tht;//别忘了加上该矛盾边
        sort(ans+1,ans+1+tot3);
        printf("%d\n",tot3);
        if(tot3){
            for(int i=1;i<tot3;++i)printf("%d ",ans[i]);
            printf("%d\n",ans[tot3]);
        }
    }
    else{//多个奇环
        for(int i=1;i<=n;++i)if(d[i]==flag)ans[++tot4]=w3[i];
        sort(ans+1,ans+1+tot4);
        printf("%d\n",tot4);
        if(tot4){
            for(int i=1;i<tot4;++i)printf("%d ",ans[i]);
            printf("%d\n",ans[tot4]);
        }
    }
    return 0;
}

```

### 后记：
		由于我实在是太弱太弱了，所以代码写的非常丑，还陆陆续续写了一个星期，还T,WA了无数发。在此引以为戒。要膜一下机房大佬laduiw。




---

## 作者：HomuraCat (赞：15)

一道妙题QAQ

首先我们知道判定是否为二分图的充要条件是有无奇环(很容易证的)，然后我们只要统计每个边在多少个奇环上就行了。

我们可以先按dfs序跑一棵树，因为dfs序跑的时候只可能会跑到返祖边(横叉边跑不到，可以反证)，于是我们就可以在树上跑来跑去，跑到返祖边的时候看一下当前环是奇还是偶，然后把环上的所有边的记录相应的环的种类都+1。

以上过程可以用差分做到$O(n)$

判定的时候，如果是dfs树上的边，直接数经过它的奇环个数是否=奇环总个数，并且不能有偶环经过否则这条边就一定不能删。如果是dfs树上的返祖边，那它就至多有一个树上奇环经过它，判断一下它的奇环个数和总奇环个数是否都=1即可

```cpp
#include<bits/stdc++.h> 
#define fo(i, a, b) for (int i = (a); i <= (b); ++i)
#define fd(i, a, b) for (int i = (a); i >= (b); --i)
#define edge(i, u) for (int i = head[u], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
#define N 10005
#define pb push_back
#define F first
#define S second
#define ll long long
#define inf 1000000007
#define mp std::make_pair
#define lowbit(x) (x & -x)
#define ls (k << 1)
#define rs (k << 1 | 1)
#define mod 100000007
#define eps 1e-4
#define itset std::set<node>::iterator
#define lb lower_bound
int head[N], u, v, n, m, ans[N], cans, p[N], fl[N];
struct edge{
    int nxt, v, id;
}e[N << 1];
int tot = 1, d[N];
int c1[N], c2[N], cnt;
inline void addedge (int u, int v, int id)
{
    e[++tot] = (edge) {head[u], v, id};
    head[u] = tot;
}
inline void dfs (int u, int fa, int pre)
{
    d[u] = d[fa] + 1; p[u] = e[pre].id;
    edge (i, u)
    {
        if ((i ^ pre) == 1) continue;
        if (!d[v])
        {
            dfs(v, u, i);
            fl[e[i].id] = 1;
            c1[e[pre].id] += c1[e[i].id]; c2[e[pre].id] += c2[e[i].id];
        }
        else
        {
            if (u == v && i & 1)
            {
                ++c1[e[i].id]; ++cnt;
            }
            else
            {
                if (d[u] > d[v])
                if ((d[u] - d[v]) & 1)
                {
                    ++c2[e[i].id];
                    ++c2[e[pre].id];
                    --c2[p[v]];
                }
                else
                {
                    ++c1[e[i].id];
                    ++c1[e[pre].id];
                    --c1[p[v]];
                    ++cnt;
                }
            }
        }
    }
}
int main ()
{
    scanf("%d %d", &n, &m);
    fo (i, 1, m)
    {
        scanf("%d %d", &u, &v);
        addedge(u, v, i);
        addedge(v, u, i);
    }
    fo (i, 1, n)
        if (!d[i]) dfs(i, 0, 0);
    if (!cnt)
        fo (i, 1, m)
            ans[++cans] = i;
    else
    fo (i, 1, m)
        if (fl[i])
        {
            if (c1[i] == cnt && !c2[i])
            {
                ans[++cans] = i;
            }
        }
        else
        {
            if (cnt == 1 && c1[i] == 1)
                ans[++cans] = i;
        }
    printf("%d\n", cans);
    fo (i, 1, cans)
        printf("%d ", ans[i]);
    return 0;
}
```

---

## 作者：hehelego (赞：8)

# CF19E Fairy 题解:

**本题关键词** :分治,逼近,撤销代替删除.

**相关题目** : 消失之物(不允许使用物品$x\in [1,n]$的情况下,背包计数)

----


萌新刚开始写分治 ~~请问线段树分治MLE怎么救~~   



本题有$O(n)$时间复杂度的优秀std ~~但是作为一个睿智选手.~~ 
一看256MB的ML和$n,m\leq 10^4$果断写一个$O(nlog^2n)$的水过去.


题目意思:给一无向图,找出那些删掉后能使原图黑白染色,同色不相邻.的边.  



就是问删了边之后是不是二分图...这个bzoj上面有个题,每条边$e(u,v)$寻在于时间$[l,r]$内,问哪些时刻是二分图....那个题目的数据比本题多个$0$...写个线段树分治+LCT就能水过去了....  所以本题我们也套用这个做法,令每条边$e_i(u,v)$的存在区间为$[0,i)\ \cup (i,m)$,这里采用$[0,m)$的编号..~~然后套个板子就可以MLE了~~发现和之前的问题一样呢qwq.

线段树分治是啥不知道的话,可以做[LOJ:(离线)动态图联通性](https://loj.ac/problem/121).


----


上面都是闲扯,我们下面进入正题, **分治逼近与可撤销**

考虑二分图判定,这里由于是一个动态加删边的东西,所以bfs/dfs染色构造的方法并不方便,我们考虑一个有趣的做法来判定二分图.  

考虑加$(u,v)$前,$u,v$不连通,在两个连通块中.假设$u,v$都是黑色的,所在连通块也已经分别黑白不相邻染色成功了,我们连接$(u,v)$合并联通块,如果保留$v$是黑色,那么$u$所在的集合要进行一个反色操作就可以满足同色不相邻了.  

$(u,v)$加入前连通并且颜色相同,则这条边破坏了同色不相邻,已经不是二分图了,再加入也不会是二分图了.


这个反色操作,0/1之类的,集合并...一看是不是就想用bitset啊?别搞事啊小老弟...$O(\frac{n}{w})$不是闹着玩的啊....不要真的以为$O(\frac{n^2}{64})$(不规范写法....)可以随便跑1e5啊...这思想很危险...  我们考虑一个复杂度正确的反色玩法.  

记录一个二分图的 **生成树** 我们知道(钦定)根的颜色就可推出所有(联通块内)点的颜色了!连边就直接把生成树的根连接,不就OK了吗?然后还要支持查询链长度,上个LCT就OK了.

---


考虑优化常数.我们注意到,只需要查询链上边数模2即可.模2意义下的加即为xor运算.并且考虑$(u,v)$在生成树上链,和$u$的根链+$v$的根链,长度模2意义下必然想等(也可以考虑$x\, xor\,x=0$,LCA之上的部分贡献为0).这样的话,一个并查集就行了,维护$x$和$fa_x$是否同色即可.插叙爬到根!. 这被称为带权并查集,在NOIP一题关押罪犯中,可以使用这个技巧得到贪心的做法.NOI一题食物链中也有相似的玩法.


----

稍作整理,我们考虑动态加边并判定二分图,如果连边前不连通,那么通过反色操作可以构造出新的染色方案,如果连通,查询是否颜色不同,这可以通过维护一个生成树并查询两点间的边数模2来完成,更进一步地,这个可以使用并查集这个入门数据结构来完成.  


回到本题,我们如果每次考虑一条边,加入其它所有边之后进行判定,复杂度一定会到达$\Omega(n^2)$不可能通过本题,考虑分别删掉$e_i$和$e_j$剩余的图有大量相同边,我们通过一个 **移动而非重构** (类似莫队转移)的操作,可以降低复杂度( **但是加删边次数仍然没有良好的上界** ),但是有删边的话,不论是UFS还是LCT都不容易实现, ~~你当然可以ETT打过去~~ 我们考虑用撤销代替删除,LCT维护生成树撤销加边是trivial的,UFS维护如果使用按size/height合并,每次合并改变的边数是$O(1)$的,可以快速撤销.


----


最后,我们考虑控制加边/撤销的次数.使用这样一个技巧.
```python

solve [l,r),f:
    if len([l,r)) <= 1:
        return qwq(f)
        
    g=f.apply(a[l,mid))
    solve[l,mid),g
    
    g=f.apply(a[mid,r))
    solve[mid,r),g
    
```

考虑一个$a_i$被加入的次数,是$O(logn)$的,为什么呢?考虑solve的递归树上叶子$i$到根的链,solve走到这上面的节点,才会apply一次$a_i$,每次区间长度减半,树高是$O(logn)$的,(线段树分治其实和这个说的一回事...)

考虑一次solve中的两次apply,如果我们用可持久化数据结构复制f,那么直接得到时间复杂度正确的算法(可持久化LCT比较麻烦需要去掉均摊,但是可持久化并茶集很容易实现.).但是我们有撤销代替删除. 
考虑递归过程,退栈return 的时候,需要撤销的边一定是进入下一层前加入的,反向按顺序撤销完全没有问题.  

最后我们简略地考虑算法正确性,发现进入$[l,r]$时,$[0,l)\cup (r,m)$ 的元素都已经被apply了. 
为什么呢?考虑递归树的根,显然成立,后面的区间是空的...如果在$[l,r)$处成立,那么进入$[l,mid)$时,还需要apply的部分正是$[mid,r)$ 对于$[mid,r)$同理. 这个性质能够一直保持,所以到达递归树的叶子$[l,l+1)$时,只有$a_i$没有被加入,符合我们的需要.


---


终于讲解完了,我们稍作整理来看代码.

- 用并查集(带权技巧,维护父子间边的权,爬parent时累积)维护染色方案,(我在代码中使用了按子树size和并,但是并没有进行重构保证树高为$O(1)$因为那样不方便撤销,稍作分析这样复杂度仍然是优秀的单次$O(logn)$)  
- (离线情况下)用撤销代替 删除/重构 让我们只需要写一个简单的UFS.(当然可以写LCT啦...)就可以维护动态图.
- 分治保证插入/撤销 次数,维持 **外部贡献全部计算** 的性质,到达叶子即可计算答案.

最后说一下复杂度,空间$O(n)$时间$O(nlog^2n)$.

简单计算,考虑递归过程,第$i$层保存$\frac{n}{2^i}$个加入的边,退栈进入另一半时可以扔掉之前的空间.共$O(n)$.
时间复杂度,考虑一条边被插入$O(logn)$次,我实现的并查集是单次$O(logn)$的.然后就没了.

最后给出我的代码,第一次MLE是没判空区间....现在可以正常AC.您可以尝试用可持久化并查集进行复制而非撤销 ~~和我比一比~~ 或者使用LCT维护生成树都可以通过本题.


```cpp
// 我是个懒人23333,听说BJOI2019在NOI linux上完,这个可以放心用了.
#include <bits/stdc++.h>
int read(){
	int x=0;char c;
	do{c=getchar();}while(!isdigit(c));
	do{x=x*10+c-'0';c=getchar();}while(isdigit(c));
	return x;
}
const int N=10000+10;
// 存答案用的...
std::vector<int> ans;
int n,m;
struct E{ int u,v; }e[N];

// 这里带权并查集.dis[x]表示fa[x]与x是否同色.
int fa[N],size[N],dis[N];
int getpar(int x){
	while(fa[x]!=x) x=fa[x];
	return x;
}
// 这里的xor就是(a+b)%2.画个真值表就知道正确性了.
int getdis(int x){
	int y=0;
	while(fa[x]!=x){ y^=dis[x]; x=fa[x]; }
	return y;
}
// 记录合并过程用的.
// merged (from->to),  from.size=fsz;
struct P{
	int from,to,fsz;
	P(int a,int b,int c){ from=a; to=b; fsz=c; }
};
// 就是apply.
P use(int eid,int &flag){
	int fx=getpar(e[eid].u),dx=getdis(e[eid].u);
	int fy=getpar(e[eid].v),dy=getdis(e[eid].v);
    
    // 我不会按height合并啊QAQ...
	if(size[fx]>size[fy]){
		std::swap(fx,fy);
		std::swap(dx,dy);
	}
	// s[x]<s[y]: x->y;
    
    // case1:在同一个集合中,判定可行.
	if(fx==fy){
		if(dx==dy) flag=1;
		return P(0,0,0);
	}
    // case2:之前并不连通,反色必定得到可行方案.
	size[fy]+=size[fx];
	fa[fx]=fy;
	dis[fx]=(dx^dy^1);
    
    // 记录合并过程.
	return P(fx,fy,size[fx]);
}
// 简易撤销...没的说
void back(const P& p){
	if(p.from==0) return ;
	int x=p.from,y=p.to,q=p.fsz;
	fa[x]=x;dis[x]=0; size[y]-=q;
}

// check e \in [l,r) 
// 我永远喜欢左闭右开.
void solve(int l,int r,int f=0){
	if(l>=r) return ;
	if(r-l==1){
		if(f==0) ans.push_back(l);
		return ;
	}
    // 这个stack你可以放外边去...反正CF会开栈空间爆不了..
    // 考虑递归过程撤销是有序的,共用一个stack完全没问题.
	std::stack<P> stk;
	int mid=(l+r)>>1,g=0;

	// apply右边,向左边逼近
	g=f;
	for(int i=mid;i<r;i++) stk.push(use(i,g));
	solve(l,mid,g);
	while(!stk.empty()){ back(stk.top()); stk.pop(); }

	// 同理...
	g=f;
	for(int i=l;i<mid;i++) stk.push(use(i,g));
	solve(mid,r,g);
	while(!stk.empty()){ back(stk.top()); stk.pop(); }
}


int main(){
	//freopen("in","r",stdin);
	n=read();m=read();
	for(int i=0;i<m;i++){
		e[i].u=read();e[i].v=read();
	}
	for(int i=1;i<=n;i++) size[fa[i]=i]=1;
	solve(0,m);
	printf("%d\n",ans.size());
	for(auto x:ans) printf("%d ",x+1);
	printf("\n");

	return 0;
}


``` 	



完结撒花.
~~bjoi2019 rp++~~



---

## 作者：i207M (赞：8)

## 题意

给一张无向图，求删掉哪几条边可以变成二分图；

## 方法

如果没有奇环，任何边都可以删；

如果只有一个奇环，那么奇环上的边都可以被删；

如果多于1个，必须选在所有奇环且不在偶环上的点；

根据树上差分的方法，应该在两个端点+1，LCA-2，而**DFS树无横叉边**，所以LCA就是深度较浅的点，将它+1-2即可；

统计tag==n的点，其父边就是ans；

## 代码

```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define gc getchar
#define pb push_back
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
void out(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
}
#define N 10010
#define M N<<2
int n, m;
int v[M], u[M], nx[M], k[M];
int cnt = 1, head[N];
il void add(int uu, int vv) {
    u[++cnt] = uu, v[cnt] = vv, nx[cnt] = head[uu];
    head[uu] = cnt;
    k[cnt] = (cnt >> 1);
}
int dep[N];
bool vis[N];
int tag[N];
int zt;
vector<int>ans;
int lst;
void dfs(int x, int f, int d) {
	//printf("V %d\n",x);
    dep[x] = d;
    vis[x] = 1;
    for (ri i = head[x]; i; i = nx[i]) {
        if (i == f) continue;
        if (!vis[v[i]]) {
            dfs(v[i], i ^ 1, d + 1);
        }
        else {
            if (dep[v[i]] < dep[x]) continue;
            if ((dep[v[i]] - dep[x] + 1) & 1) {
                tag[x]--;  // in fact +1 -2
                tag[v[i]]++;
                zt++;
                lst=k[i];
            }
            else {
                tag[x]++;
                tag[v[i]]--;
            }
        }
    }
}
int dfs2(int x, int f) {
    vis[x] = 1;
    int res = tag[x];
    for (ri i = head[x]; i; i = nx[i]) {
        if (vis[v[i]]) continue;
        res += dfs2(v[i], i);
    }
    if (res == zt) ans.pb(k[f]);
    //printf("T %d %d %d\n",x,res,tag[x]);
    return res;
}
signed main() {
    in(n), in(m);
    for (ri i = 1, a, b; i <= m; ++i) {
        in(a), in(b);
        add(a, b);
        add(b, a);
    }
    for (ri i = 1; i <= n; ++i) {
        if (!vis[i]) dfs(i, 0, 0);
    }
    if (zt == 0) {
        //cout << "A";
        printf("%d\n", m);
        for (ri i = 1; i <= m; ++i) printf("%d ", i);
        return 0;
    }
    if(zt==1) ans.pb(lst);
    //cout<<zt;
    mem0(vis);
    for (ri i = 1; i <= n; ++i) {
        if (!vis[i]) dfs2(i, 0);
    }
    sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for (ri i = 0; i < ans.size(); ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}
```

---

## 作者：Computer1828 (赞：6)

先吐槽一下本题翻译，这是机翻吧。。。

### 题意：

给你一个 $n$ 个点、 $m$ 条边的无向图，可以从图中删除一条边，问删除哪些边可以使图变成一个二分图。

### 先说一下什么是二分图：

二分图的节点由两个集合组成，而且两个集合内部没有边。

换言之，如果这是一个二分图，那么一定会存在一种方案，将节点划分成满足以上性质的两个集合。    ——以上摘自OI Wiki，有删改。

### 不难发现二分图的一些性质：

1. 二分图不存在奇环；
2. 一棵树一定是二分图；
3. 一个二分图删掉一条边也是二分图；
4. 假设现在有一棵树，在树上取两个节点 u 和 v ，如果 u 和 v 的最短路是奇数，连接 u , v ，则出现偶环（长度为偶数的环）；如果 u 和 v 的最短路是偶数，连接 u , v ，则出现奇环（长度为奇数的环）；
5. 如果将两个集合的点分别染成黑色和白色，则每一条边一定连接着一个黑色点和白色点。

### 暴力：

考虑枚举每一条边，将其删去，然后做一次dfs或bfs，给每个点染色，最后判断有没有两个相邻的点颜色相同。

代码略。~~懒~~

### 正解：

对于性质二，我们随意求出一棵生成树，然后由性质四，我们可以把剩下的边一条条地放在树上，判断这条边会不会构成奇环，并统计奇环个数 sum 。

以下把会构成奇环的边叫做 A 类边，不会构成奇环的边叫做 B 类边，其中 A 类边和 B 类边都不是树上的边。

定义非树上边 (u,v) 包含树上的一条边 (uu,vv) ，当且仅当 u 到 v 的最短路上有边 (uu,vv) 。

由性质三，如果 sum = 0 ，输出每一条边即可。

再多举几个例子，我们可以发现，如果 sum = 1 ，那就是只有一条 A 类边，则要么删掉 A 类边，要么在 A 类边包含的树上边找一条 B 类边不包含的边并删掉。

如果 sum >= 2 ，那只能在树上删除那些被所有 A 类边包含且不被任何一条 B 类边包含的边了。考虑用树上差分进行维护，定义 $s[i]$ 表示节点 i 和它父亲的差分，如果找到一条 A 类边 (u,v) ，则把 (u,v) 的树上最短路经过的点+1；如果找到一条 B类边 (u,v) ， 则把 (u,v) 的树上最短路经过的点-1。用差分来维护就是 $s[u]++$ ， $s[v]++$ ， $s[lca(u,v)]-=2$ 。

注意，题目没有说明图的其他性质，所以记住，可能有自环，可能有重边，可能不连通

```cpp
#include<stdio.h>
#include<algorithm>
#include<map>
#define pii pair<int,int>
#define N 100000
#define M 200000
using namespace std;
int n,m;
struct edge{
	int to,nxt;
}e1[M+5],e2[M+5];//树边，除了树的边

int hed1[M+5],cnt1;
int hed2[M+5],cnt2;
inline void add1(int u,int v){
	e1[++cnt1].to = v,e1[cnt1].nxt = hed1[u];
	hed1[u] = cnt1;
}

inline void add2(int u,int v){
	e2[++cnt2].to = v,e2[cnt2].nxt = hed2[u];
	hed2[u] = cnt2;
}

struct node{
	int u,v,id;
}a[100005],ano[100005];//题目给出的图，除了树的边 
int tot;

int fa[100005];
inline int getf(int x){return (x == fa[x])?x:fa[x] = getf(fa[x]);}
inline void merge(int u,int v){
	int U = getf(u),V = getf(v);
	fa[V] = U;
}//并查集

int lg[100005];//常数优化
int f[100005][25];//倍增求LCA
int dep[100005],dis[100005];
bool vis1[100005];//因为图可能不连通，所以要用vis记录每个点是否经过
inline void dfs(int u,int fa){
	dep[u] = dep[fa]+1,f[u][0] = fa;
	vis1[u] = true;
	for(int i = 1;(1<<i)<=dep[u];++i){
		f[u][i] = f[f[u][i-1]][i-1];
	}
	for(int i = hed1[u];i;i = e1[i].nxt){
		int v = e1[i].to;
		if(v != fa) dis[v] = dis[u]+1,dfs(v,u);
	}
}

inline int lca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	while(dep[x] > dep[y]) x = f[x][lg[dep[x]-dep[y]]-1];
	if(x == y) return x;
	for(int i = lg[dep[x]];i>=0;--i){
		if(f[x][i] != f[y][i]){
			x = f[x][i],y = f[y][i];
		}
	}
	return f[x][0];
}

int sum;//奇环个数 
map<pii,int> mp;//记录边(u,v)是第几条边
inline void _readin_(){//读入
	scanf("%d%d",&n,&m);
	int u,v;
	int sum_of_edge = 0;
	for(int i = 1;i<=m;++i){
		scanf("%d%d",&u,&v);
		if(u != v){//处理自环
			a[++sum_of_edge].u = u,a[sum_of_edge].v = v,a[sum_of_edge].id = sum_of_edge;
			pii add_in1 = make_pair(u,v),add_in2 = make_pair(v,u);//双向边
			mp[add_in1] = sum_of_edge;
			mp[add_in2] = sum_of_edge;
		}
	}
	m = sum_of_edge;
}

inline void _init_(){//初始化
	for(int i = 1;i<=n;++i) fa[i] = i;
	for(int i = 1;i<=N+1;++i) lg[i] = lg[i-1]+(1<<lg[i-1] == i);//常数优化 
}

int s[N+5];//i与它父亲的差分值

int ans[N+5],cnt;//答案数组和答案数组的大小

bool vis2[N+5];

inline void bfs(int u,int fa){//求差分和 
	vis2[u] = true;
	for(int i = hed1[u];i;i = e1[i].nxt){
		int v = e1[i].to;
		if(v == fa) continue;
		bfs(v,u);
		s[u]+=s[v];
	}
}
int main(){
	_readin_();
	_init_();
	
	for(int i = 1;i<=m;++i){
		int x = a[i].u,y = a[i].v,tp = a[i].id;
		int X = getf(x),Y = getf(y);
		if(getf(x) != getf(y)){
			merge(x,y);
			add1(x,y),add1(y,x);//随意求出一棵生成树
		}else{
			ano[++tot].u = x,ano[tot].v = y,ano[tot].id = tp;//除了树的边
			add2(x,y),add2(y,x);
		}
	}
	for(int i = 1;i<=n;++i) if(!vis1[i]) dfs(i,i);//LCA
	int st,mid,ed,op;//如果有一个奇环，u，LCA(u,v)，v，A类边编号 
	for(int i = 1;i<=tot;++i){
		int x = ano[i].u,y = ano[i].v,tp = ano[i].id;
		int LCA = lca(x,y);
		int dist = dis[x]+dis[y]-2*dis[LCA];//两个点之间的最短路
		if(dist%2 == 0){//奇环 
			sum++;
			st = x,mid = LCA,ed = y,op = tp;
			s[x]++,s[y]++,s[LCA]-=2;
		}else{
			s[x]--,s[y]--,s[LCA]+=2;
		}
	}
	
	for(int i = 1;i<=n;++i) if(!vis2[i]) bfs(i,i);//处理差分
	if(sum == 0){
		printf("%d\n",m);
		if(m) for(int i = 1;i<=m;++i) printf("%d ",i);
	}else if(sum == 1){
		pii que_in;
		for(int i = st;i!=mid;i = f[i][0]){//树上每条边都要找一遍
			if(s[i] == 1){
				que_in = make_pair(i,f[i][0]);
				ans[++cnt] = mp[que_in];
			}
		}
		
		for(int i = ed;i!=mid;i = f[i][0]){
			if(s[i] == 1){
				que_in = make_pair(i,f[i][0]);
				ans[++cnt] = mp[que_in];
			}
		}
		
		ans[++cnt] = op;
		
		sort(ans+1,ans+cnt+1);
		printf("%d\n",cnt);
		if(cnt) for(int i = 1;i<=cnt;++i) printf("%d ",ans[i]);
	}else{
		pii que_in;
		for(int i = 1;i<=n;++i){
			if(s[i] == sum){
				que_in = make_pair(i,f[i][0]);
				ans[++cnt] = mp[que_in];
			}
		}
		sort(ans+1,ans+cnt+1);
		printf("%d\n",cnt);
		if(cnt) for(int i = 1;i<=cnt;++i) printf("%d ",ans[i]);
	}
	return 0;
}
```


---

## 作者：hicc0305 (赞：3)

听说可以用LCT做。。。可是蒟蒻不会LCT。。。

首先，一个图一定是由一堆环和一堆链组成的。根据这道题，我们可以发现一个很好的性质，那就是，每一条链必然是一个二分图，每一个偶环，也必然是一个二分图，所以。。只剩下奇环。。不是二分图了。。

因此，我们要找的边是，被所有奇环覆盖的并且没有被偶环覆盖的边，因为,删掉这条边，原来的偶环变成了奇数条边，奇环变成了偶数条边，这两个环练了起来，又~~tm~~合成了一个奇环orz

也就是说我们要记录一条边被奇环和偶环覆盖的次数。覆盖的次数？怎么这么像运输计划。。因此我们想到了用树上差分来解决这个问题。

另外，这道题非常坑人，注意以下几点：

1.如果没有奇环，删那条边都可以，所以输出m条边

2.如果只有一个奇环，那么返祖边也要被算进答案。因为我们是用差分来求覆盖次数的，所以我们是从叶子节点往上，求子树和的，因此我们并不能遍历到返祖边，并没有把他算进答案。在有多个奇环的时候，返祖边是不可能能被算进答案的，因为返祖边只能覆盖自己的奇环（你可以在树上画画看），所以在有多个奇环的情况下，我们根本不用去管他。而在只有一个奇环的时候，他也要算进去了，做一个特判即可。当然，你把所有边领出来一起差分，把返祖边也差分到，是不用考虑这种情况的，这种情况只是针对在dfs的时候一起做差分的程序，这种程序是差分不到返祖边的（就像我）。

3.然后。。这道题其实还要考虑重边、自环。。。但是介于数据太水，你不去管也能过。。。

那么。。代码

```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int fa[2000010],tago[2000010],tage[2000010],dep[2000010];//tag是差分数组，dep记录深度，回到深度小的就是返祖边了
int fr[2000010],eve[2000010],odd[2000010],f[2000010]，fz;//eve记录偶环差分和，odd记录奇环差分和，fz是对于只有一个奇环时，存返祖边的编号
int n,m,num;//num记录的是奇环个数
vector < pair<int,int> > to[2000010];
vector <int> ans;
void dfs(int u)
{
    for(int i=0;i<to[u].size();i++)
    {
    	int v=to[u][i].first;
    	if(v==fa[u]) continue;
		if(!dep[v])
		{
		    dep[v]=dep[u]+1;
		    fa[v]=u,fr[v]=to[u][i].second;
		    dfs(v);
		    eve[u]+=eve[v],odd[u]+=odd[v];
		}
		else if(dep[v]<=dep[u])//不要写成<，因为有自环情况要考虑（尽管这些数据是不会WA的）
		{
		    if((dep[v]-dep[u])&1) tage[u]++,tage[v]--;//偶环情况
		    else num++,tago[u]++,tago[v]--,fz=to[u][i].second;//奇环情况
		}
	}
    eve[u]+=tage[u];
    odd[u]+=tago[u];
}
int solve()
{
    int cnt=0;
    if(!numoddn)//没有奇环
    {
        for(int i=1;i<=m;i++)
        	ans.push_back(i);
        return m;
    }
    for(int i=1;i<=n;i++)
		if(odd[i]==num && !eve[i])
		{
			cnt++;
			ans.push_back(fr[i]);
		}
    if(num==1)//一个奇环
    {
    	cnt++;
		ans.push_back(fz);//加上返祖边
    }
    return cnt;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
    	int x,y;
        scanf("%d%d",&x,&y);
        int flag=1,it;
        for(int j=0;j<to[x].size();j++)
        	if(to[x][j].first==y) flag=0,it=j;
		if(flag)
		{
			if(x==y) to[x].push_back(make_pair(y,i));//处理自环
			else to[x].push_back(make_pair(y,i)),to[y].push_back(make_pair(x,i));
		}
        else f[to[x][it].second]=1;//有重边就做标记
    }
    for(int i=1;i<=n;i++)
		if(!dep[i])
		{
			dep[i]=1;
			dfs(i);
		}
    int num=solve();
    for(int i=0;i<ans.size();i++)
    	if(f[ans[i]]) ans.erase(ans.begin()+i),num--,i--;//如果选中的边中有重边，删掉
    printf("%d\n",num);
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)
    	printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：C20203030 (赞：3)

纪念一下我逝去的语文（110的蒟蒻膜拜AK的大佬）

## 一、题目

[传送门](https://www.luogu.org/problem/CF19E)

**题意:**

对于一个图进行二染色，求删去哪些边可以是得染色成功（一定有解），输出可能的边数及可能边的编号（输入顺序）。

**数据范围：**

$1\leq n\leq 10^{4},0\leq m\leq 10^{4}$

## 二、解法

**0x01 前置芝士**

先给出一个结论：一个图能染色成功的充要条件是该图中不存在奇环（边数为奇数的环）。

怎么理解这个结论呢？我们先建一颗搜索树，我们把边慢慢加 ，新加入的边会让搜索树构成环，如果此环为奇环，那么树上路径的边数为偶数，两点的颜色一样，故不能有奇环，详细证明需要讨论链式和弯折式的情况。

**0x02 分析**

我们先建一颗生成树，把没有出现过得边加入。

首先如果没有奇环，直接输出所有边即可。

如果有一个奇环，我们删去环上任意一条边即可。

我们考虑多个奇环的情况，由于要同时破环所有奇环，我们考虑把每次加入边所对应的树上路径全部加1，最后统计所有权值等于奇环数的树边，树上差分可以做到$O(n)$。

当这里还存在一个难以解决的问题，形成偶环的边可能回和形成奇环的边组合成奇环，而我们并没有统计到，我们尝试对组合的情况进行讨论。

设奇环树上边数为J，偶环树上边数为O。

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3Uub3JnL3VwbG9hZC9pbWFnZV9ob3N0aW5nL2MxcTB0NXhxLnBuZw?x-oss-process=image/format,png)

第一种情况（两边路径均有交集），我们发现第一条红线组成了一个奇环，第二条红线组成了一个偶环，如果删去树上边的环，剩下的两个红边组成的环的数量为$O-J+2$，易得改换为奇环，所以不能删去树上边。

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3Uub3JnL3VwbG9hZC9pbWFnZV9ob3N0aW5nLzVoajlpb3J2LnBuZw?x-oss-process=image/format,png)

第二种情况，若删去树边，则能组成的新环边数为$O-s_1+s_2+2$，$s_1,s_2$为奇环树上的两边边数，所以$s_1,s_2$同奇同偶，易得该新环为奇环，故该树边不能选。

这两种情况是最基本的，可以衍生出其他情况，我们可以发现偶环的树上路径都是不能选的，这个也可以通过树上差分实现。

**0x03 代码**


```cpp
#include <cstdio>
#include <algorithm>
using namespace std; 
const int MAXN = 10005;
int read()
{
    int num=0,flag=1;
    char c;
    while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;
    while(c>='0'&&c<='9')num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num*flag;
}
int n,m,k,cnt,tot,thm,flag,num[MAXN],c[MAXN],f[MAXN],p[MAXN],dep[MAXN],ans[MAXN],fa[MAXN][20];
bool vis[MAXN];
struct node
{
	int u,v,id;
}a[MAXN],b[MAXN];
struct edge
{
	int v,next,id;
}e[MAXN*2];
int findSet(int x)
{
	if(p[x]^x) p[x]=findSet(p[x]);
	return p[x];
}
void dfs(int u,int par)
{
	fa[u][0]=par;
	dep[u]=dep[par]+1;
	for(int i=1;i<20;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=f[u];i;i=e[i].next)
		if(e[i].v^par)
		{
			num[e[i].v]=e[i].id;
			dfs(e[i].v,u);
		}
}
int Lca(int u,int v)
{
	for(int i=19;i>=0;i--)
	{
		if(dep[fa[u][i]]>=dep[v])
			u=fa[u][i];
		if(dep[fa[v][i]]>=dep[u])
			v=fa[v][i];
	}
	if(u==v) return u;
	for(int i=19;i>=0;i--)
		if(fa[u][i]^fa[v][i])
			u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
void make(int u,int par)
{
	vis[u]=1;
	for(int i=f[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==par) continue;
		make(v,u);
		c[u]+=c[v];
	}
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		p[i]=i;
	for(int i=1;i<=m;i++)
		a[i]=node{read(),read(),i};
	for(int i=1;i<=m;i++)
	{
		int x=findSet(a[i].u),y=findSet(a[i].v);
		if(x^y)
		{
			p[x]=y;
			e[++tot]=edge{a[i].u,f[a[i].v],a[i].id},f[a[i].v]=tot;
			e[++tot]=edge{a[i].v,f[a[i].u],a[i].id},f[a[i].u]=tot;
		}
		else
			b[++k]=a[i];
	}
	for(int i=1;i<=n;i++)
		if(!dep[i]) dfs(i,0);
	for(int i=1;i<=k;i++)
	{
		int u=b[i].u,v=b[i].v,lca=Lca(u,v);
		int len=dep[u]+dep[v]-dep[lca]*2,delta=1;
		if(len&1) delta=-1;
		else flag++,thm=b[i].id;
		c[u]+=delta,c[v]+=delta,c[lca]-=2*delta;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]) make(i,0);
	if(!flag)
		for(int i=1;i<=m;i++)
			ans[++cnt]=i;
	else 
		for(int i=1;i<=n;i++)
			if(c[i]==flag)
				ans[++cnt]=num[i];
	if(flag==1) ans[++cnt]=thm;
	sort(ans+1,ans+1+cnt);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",ans[i]); 
}
```


---

## 作者：foreverlasting (赞：3)

[题面](https://www.lydsy.com/JudgeOnline/problem.php?id=4424)

$CDQ$分治。

$O(n)$的正解完全不会哎。发现这题缺少物品然后证明是否是二分图，所以就可以用$CDQ$分治啦。二分图用并查集去维护，撤回的时候用个栈去存就好啦！

code:
```
//2018.9.24 by ljz
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
const int N=1e6+10;
namespace MAIN{
    int n,m;
    struct E{
        int u,v;
        E() {}
        E(res u,res v):u(u),v(v) {}
    }edge[N];
    bool jh,dis[N];
    int ans[N],cnt;
    int fa[N],dep[N],top;
    inline int find(res x){
        while(x!=fa[x])x=fa[x];
        return x;
    }
    inline int fdis(res x){
        res ret=0;
        while(x!=fa[x])ret^=dis[x],x=fa[x];
        return ret;
    }
    struct St{
        int x,y,hx,hy;
        St() {}
        St(res x,res y,res hx,res hy):x(x),y(y),hx(hx),hy(hy) {}
    }S[N];
    inline void merge(const res &id){
        if(jh)return;
        res fu=find(edge[id].u),fv=find(edge[id].v),du=fdis(edge[id].u),dv=fdis(edge[id].v);
        if(fu==fv){if(du==dv)jh=1;return;}
        if(dep[fu]<dep[fv])_swap(fu,fv);
        S[++top]=St(fu,fv,dep[fu],dep[fv]);
        fa[fv]=fu;
        dis[fv]=1^du^dv;
        if(dep[fu]==dep[fv])dep[fu]++;
    }
    inline void cut(const res &id){
        fa[S[id].x]=S[id].x,dep[S[id].x]=S[id].hx,dis[S[id].x]=0;
        fa[S[id].y]=S[id].y,dep[S[id].y]=S[id].hy,dis[S[id].y]=0;
    }
    void CDQ(const res &L,const res &R){
        if(L==R){if(!jh)ans[++cnt]=L;return;}
        res mid=(L+R)>>1,tmptop=top,tmpjh=jh;
        for(res i=mid+1;i<=R;i++)merge(i);
        if(!jh)CDQ(L,mid);
        jh=tmpjh;
        while(top>tmptop)cut(top--);
        for(res i=L;i<=mid;i++)merge(i);
        if(!jh)CDQ(mid+1,R);
        jh=tmpjh;
        while(top>tmptop)cut(top--);
    }
    inline void MAIN(){
        n=read(),m=read();
        for(res i=1;i<=m;i++){
            res u=read(),v=read();
            edge[i]=E(u,v);
        }
        for(res i=1;i<=n;i++)fa[i]=i,dep[i]=1;
        CDQ(1,m);
        printf("%d\n",cnt);
        for(res i=1;i<=cnt;i++)printf("%d ",ans[i]);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：破壁人五号 (赞：2)

题目链接：[Codeforces](https://codeforces.com/problemset/problem/19/E)

## 题目大意
给一个无向图，要求删去一条边，让它变为二分图。问哪些边符合要求？

## 题解
（这题考试时拿来加强了一波，要求线性。结果我分部分分写，暴力挂了正解对了）

首先二分图的充要条件是没有奇环，着重考虑有奇环的情况（没有奇环则所有边都可行。）：

显然这条边必须在同时所有奇环上，于是我们先找到一个奇环，记它为环 $A$。BFS+染色就能实现。把环上的点和边记录下来。

接着考虑剩下的奇环：

- 若这个奇环没有边在 $A$ 上，则没有边符合要求。
- 若这个奇环有一些边在 $A$ 上，则这些边以外的边都不可行

所以将环上所有边去掉（打个标记），简单判断第一种情况，然后依次从环上的点开始 BFS，寻找环上的点到另一个点的各个路径，每个路径都可以与 $A$ 的连续一段构成奇环。如下图，$\color{#0080FF}\text{深蓝色}$的环即环 $A$，$\color{#66CCFF}\text{浅蓝色}$（及$\color{#66FFFF}\text{绿色}$）的边与环上用对应颜色虚线标明的部分构成奇环。用$\color{#EE0000}\text{红色}$圈出的边即符合要求的边。

![栗子](https://cdn.luogu.com.cn/upload/image_hosting/m08nuy8p.png)

考虑怎么维护环上哪些边符合要求。记录序列 $a$（每个元素对应 $A$ 的一条边）与变量 $cnt=0$。每次找到有边在 $A$ 上的环，便将 $cnt$ 加一，$A$ 上的这一段边在 $a$ 上对应的值也加一。由于这一段边一定是连续的（把环拆开成链后至多分成两段），可以用差分数组维护。最后 $O(N)$ 扫一遍，$a_i=cnt$ 者即符合要求。

时间复杂度为 $O(N+M+k\log k)$（$k$ 为答案数量）

```cpp#include<bits/stdc++.h>
using namespace std;
int getint(){
	int ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ans=ans*10+c-'0';
		c=getchar();
	}
	return ans*f;
}
const int N=2000010,M=N<<1;
struct bian{
	int e,n;
	bool on;
};
bian b[M];
int s[N],tot=1;
void add(int x,int y){
	tot++;
	b[tot].e=y;
	b[tot].n=s[x];
	s[x]=tot;
}
int n,m;

int col[N],dis[N];//col: 染色; dis: 离 BFS 起点的距离
int pre[N],preb[N];//pre: BFS 时的前驱; preb: BFS 时的前一条边
int huan[N],num[N];//huan: 环上第 i 个点; num: 点在环上的编号
int huanb[N];//haunb: 环上的第 i 条边
int a[N];//a: 题解中的 a 的差分数组
int len,cnt=0;

void record(int x,int y,int xtoy){//记录奇环
	int x_=x,y_=y;
	while(dis[y]>dis[x]){
		b[preb[y]].on=b[preb[y]^1].on=1;
		y=pre[y];
	}
	while(x!=y){
		b[preb[y]].on=b[preb[y]^1].on=1;
		y=pre[y];
		b[preb[x]].on=b[preb[x]^1].on=1;
		x=pre[x];
	}
	int lca=x;
	x=x_,y=y_;
	len=dis[x]+dis[y]-dis[lca]*2+1;
	while(x!=lca){
		huan[dis[x_]-dis[x]+1]=x;
		num[x]=dis[x_]-dis[x]+1;
		huanb[num[x]]=preb[x]>>1;
		x=pre[x];
	}
	huan[dis[x_]-dis[x]+1]=x;
	num[x]=dis[x_]-dis[x]+1;
	while(y!=lca){
		huan[len-dis[y_]+dis[y]]=y;
		num[y]=len-dis[y_]+dis[y];
		huanb[num[y]-1]=preb[y]>>1;
		y=pre[y];
	}
	huanb[len]=xtoy>>1;
	b[xtoy^1].on=b[xtoy].on=1;
}
bool find_jihuan(int st){//找奇环，返回是否找到
	queue<int>q;
	q.push(st);
	col[st]=1;
	while(q.size()){
		int f=q.front();
		q.pop();
		for(int i=s[f];i;i=b[i].n){
			if(col[b[i].e]==col[f]){
				record(f,b[i].e,i);
				return 1;
			}
			if(!col[b[i].e]){
				col[b[i].e]=3-col[f];
				pre[b[i].e]=f;
				preb[b[i].e]=i;
				dis[b[i].e]=dis[f]+1;
				q.push(b[i].e);
			}
		}
	}
	return 0;
}
bool bfs(int x){//从环上的点开始 BFS，返回是否**没有**其他奇环
	queue<int>q;
	q.push(x);
	col[x]=1;
	while(q.size()){
		int f=q.front();
		q.pop();
		for(int i=s[f];i;i=b[i].n){
			if(b[i].on)continue;
			if(col[b[i].e]==col[f]){
				return 0;
			}
			if(!col[b[i].e]){
				col[b[i].e]=3-col[f];
				q.push(b[i].e);
				if(num[b[i].e]){
					cnt++;
					if((col[x]+col[b[i].e]+num[x]+num[b[i].e])%2==1){
						int u=x,v=b[i].e;
						if(num[u]>num[v])swap(u,v);
						a[num[u]]++;
						a[num[v]]--;
					}else{
						int u=x,v=b[i].e;
						if(num[u]>num[v])swap(u,v);
						a[1]++;
						a[num[u]]--;
						a[num[v]]++;
						a[len+1]--;
					}
				}
			}
		}
	}
	return 1;
}


int main(){
	n=getint(),m=getint();
	for(int i=0;i<m;i++){
		int x=getint(),y=getint();
		add(x,y);
		add(y,x);
	}
	bool found=0;
	for(int i=1;i<=n;i++){
		if(!col[i]&&find_jihuan(i)){
			found=1;
			break;
		}
	}
	if(!found){
		printf("%d\n",m);
		for(int i=1;i<=m;i++){
			printf("%d ",i);
		}
		return 0;
	}
	memset(col,0,sizeof(col));
	for(int i=1;i<=len;i++){
		if(!col[huan[i]]){
			if(!bfs(huan[i])){
				puts("0");
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!col[i]){
			if(find_jihuan(i)){
				puts("0");
				return 0;
			}
		}
	}
	int sum=0;
	vector<int>ans;
	for(int i=1;i<=len;i++){
		sum+=a[i];
		if(sum==cnt)ans.push_back(huanb[i]);
	}
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

