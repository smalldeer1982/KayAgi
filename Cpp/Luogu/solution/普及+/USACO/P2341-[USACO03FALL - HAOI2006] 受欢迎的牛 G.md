# [USACO03FALL / HAOI2006] 受欢迎的牛 G

## 题目背景

本题测试数据已修复。

## 题目描述

每头奶牛都梦想成为牛棚里的明星。被所有奶牛喜欢的奶牛就是一头明星奶牛。所有奶牛都是自恋狂，每头奶牛总是喜欢自己的。奶牛之间的“喜欢”是可以传递的——如果 $A$ 喜欢 $B$，$B$ 喜欢 $C$，那么 $A$ 也喜欢 $C$。牛栏里共有 $N$ 头奶牛，给定一些奶牛之间的爱慕关系，请你算出有多少头奶牛可以当明星。

## 说明/提示

只有 $3$ 号奶牛可以做明星。

【数据范围】

对于 $10\%$ 的数据，$N\le20$，$M\le50$。

对于 $30\%$ 的数据，$N\le10^3$，$M\le2\times 10^4$。

对于 $70\%$ 的数据，$N\le5\times 10^3$，$M\le5\times 10^4$。

对于 $100\%$ 的数据，$1\le N\le10^4$，$1\le M\le5\times 10^4$。

## 样例 #1

### 输入

```
3 3
1 2
2 1
2 3```

### 输出

```
1```

# 题解

## 作者：来日方长 (赞：338)

由题可得，受欢迎的奶牛只有可能是图中唯一的出度为零的强连通分量中的所有奶牛，所以若出现两个以上出度为0的强连通分量则不存在明星奶牛，因为那几个出度为零的分量的爱慕无法传递出去。那唯一的分量能受到其他分量的爱慕同时在分量内相互传递，所以该分量中的所有奶牛都是明星。

ac代码：

```cpp
    #include<bits/stdc++.h>
    #define N 10050
    using namespace std;
    struct EDGE{
        int next,to;
    }edge[N*20];
    int head[20*N],dfn[N],low[N];
    int du[N],id[N],all[N];
    bool insta[N];int cnt,tot,gg,n,m;
    stack<int>s;
    inline void add(int x,int y){
        cnt++;
        edge[cnt].to=y;
        edge[cnt].next=head[x];
        head[x]=cnt;
    }
    void in(int &read){
        int x=0,f=1;char ch;
        for(ch=getchar();(ch<'0'||ch>'9')&&ch!='-';ch=getchar());
        if(ch=='-'){f=-1;ch=getchar();}
        while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
        read=x*f;//可以处理负数的读入优化
    }
    void tarjan(int x){
        dfn[x]=low[x]=++tot;
        s.push(x);insta[x]=true;
        for(int i=head[x];i;i=edge[i].next){
            int u=edge[i].to;
            if(!dfn[u]){
                tarjan(u);
                low[x]=min(low[x],low[u]);
            }
            else if(insta[u])low[x]=min(low[x],dfn[u]);
        }//tarjan模板
        int k;
        if(low[x]==dfn[x]){
            ++gg;
            do{
                k=s.top();s.pop();
                insta[k]=false;
                id[k]=gg;all[gg]++;//将一个分量中的元素染成一色
            }while(x!=k);
        }
    }
    int main(){
        in(n);in(m);
        int a,b;
        for(register int i=1;i<=m;i++){
            in(a);in(b);
            add(a,b);
        }
        for(register int i=1;i<=n;i++)
            if(!dfn[i])tarjan(i);
        for(register int w=1;w<=n;w++){
            for(int i=head[w];i;i=edge[i].next){
                int u=edge[i].to;
                if(id[w]!=id[u]){
                    du[id[w]]++;//遍历每一个点并记录出度
                }
            }
        }
        int tt=0;
        for(register int i=1;i<=gg;i++)
            if(!du[i]){
            if(tt){puts("0");return 0;}//两次出现出度为0直接输出0
            tt=i;//记录出度为零的分量的边号
        }
        printf("%d\n",all[tt]);
        return 0;
}
```

---

## 作者：zybnxy (赞：327)

[题目传送门](https://www.luogu.org/problemnew/show/P2341)

标签：$tarjan$求强联通分量

### 何为强联通分量

有向图强连通分量：在有向图$G$中，如果两个顶点$V_i,V_j$间（$V_i>V_j$）有一条从$V_i$到$V_j$的有向路径，同时还有一条从$V_i$到$V_j$的有向路径，则称两个顶点强连通。如果有向图$G$的每两个顶点都强连通，称$G$是一个强连通图。有向图的极大强连通子图，称为强连通分量。 ——百度百科
                          
事实上，你大概可以理解为：如果一个图的子图中，任意两点可以相互到达，那么这就组成了一个强联通分量。

如果还不理解怎么办？没关系，我们上图像来理解

![](http://www.th7.cn/d/file/p/2015/03/16/37f854f9c53856f0bf6d323e36e942d3.png)

如图，在这个有向图中，一共有$\{1,2,3,4\},\{5\},\{6\}$三个强联通分量

### 如何求强联通分量

我们需要两个非常重要的数组，在这里先说明一下

$1.dfn$，表示这个点在$dfs$时是第几个被搜到的。

$2.low$，表示这个点以及其子孙节点连的所有点中$dfn$最小的值

$3.stack$，表示当前所有可能能构成是强连通分量的点。

$4.vis$，表示一个点是否在$stack$数组中。

我们使用$tarjan$的方法
(1)、首先初始化$dfn[u]=low[u]=$第几个被$dfs$到

(2)、将$u$存入$stack[ ]$中，并将$vis[u]$设为$true$

(3)、遍历$u$的每一个能到的点，如果这个点$dfn[ ]$为$0$，即仍未访问过，那么就对点$v$进行$dfs$，然后$low[u]=min\{low[u],low[v]\}$

(4)、假设我们已经$dfs$完了$u$的所有的子树那么之后无论我们再怎么$dfs$，$u$点的$low$值已经不会再变了。

至此，$tarjan$完美结束

那么如果$dfn[u]=low[u]$这说明了什么呢？

再结合一下$dfn$和$low$的定义来看看吧

$dfn$表示$u$点被$dfs$到的时间，$low$表示$u$和$u$所有的子树所能到达的点中$dfn$最小的。

这说明了$u$点及$u$点之下的所有子节点没有边是指向u的祖先的了，即我们之前说的$u$点与它的子孙节点构成了一个最大的强连通图即强连通分量

此时我们得到了一个强连通分量，把所有的u点以后压入栈中的点和u点一并弹出，将它们的$vis[ ]$置为$false$，如有需要也可以给它们打上相同标记（同一个数字）


------------


$Q:$ $dfn$可以理解，但为什么$low$也要这么做呢？

$A:$因为low的定义如上，也就是说如果没有子孙与u的祖先相连的话，$dfn[u]$一定是它和它的所有子孙中$dfn$最小的（因为它的所有子孙一定比他后搜到）。

$Q:$ $stack[]$有什么用？

$A:$如果$u$在$stack$中，$u$之后的所有点在$u$被回溯到时$u$和栈中所有在它之后的点都构成强连通分量。

$Q:$ $low[ ]$有什么用？

$A:$应该能看出来吧，就是记录一个点它最大能连通到哪个祖先节点（当然包括自己）

如果遍历到的这个点已经被遍历到了，那么看它当前有没有在$stack[ ]$里,如果有那么$low[u]=min\{low[u],low[v]\}$

如果已经被弹掉了，说明无论如何这个点也不能与$u$构成强连通分量，因为它不能到达$u$

如果还在栈里，说明这个点肯定能到达$u$，同样$u$能到达他，他俩强联通。

接下来，就是非$(sang)$常$(xin)$简$(bing)$单$(kuang)$的手$\%$过程了

从节点$1$开始$DFS$，把遍历到的节点加入栈中。搜索到节点$u=6$时，$DFN[6]=LOW[6]$，找到了一个强连通分量。退栈到$u=v$为止，$\{6\}$为一个强连通分量。

![](http://www.th7.cn/d/file/p/2015/03/16/d8aa8e62b42fd3d5da5ade0fe90cffa6.png)

之后返回节点$5$,发现$DFN[5]=LOW[5]$，于是我们又找到了一个新的强联通分量$\{5\}$

![](http://www.th7.cn/d/file/p/2015/03/16/ce2022b95cc040b0fbb2109df448dbbd.png)

返回节点$3$，继续搜索到节点$4$，把$4$加入堆栈。发现节点$4$向节点$1$有后向边，节点$1$还在栈中，所以$LOW[4]=1$。节点$6$已经出栈，$(4,6)$是横叉边，返回$3$，$(3,4)$为树枝边，所以$LOW[3]=LOW[4]=1$。

![](http://www.th7.cn/d/file/p/2015/03/16/7d6d8c0516311035c8fe6f897eb7b911.png)

继续回到节点$1$，最后访问节点$2$。访问边$(2,4)$，$4$还在栈中，所以$LOW[2]=DFN[4]=5$。返回$1$后，发现$DFN[1]=LOW[1]$，把栈中节点全部取出，组成一个连通分量$\{1,3,4,2\}$。

![](http://www.th7.cn/d/file/p/2015/03/16/b962e2b6b609aaf75d5e096d510a4251.png)

至此，$tarjan$算法结束，我们找到了全部的$3$个强联通分量$\{1,2,3,4\},\{5\},\{6\}$

程序实现代码如下
```cpp
inline int tarjan(int u) 
{
	low[u]=dfn[u]=++dfn_sum;
	stack[top++]=u;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(dfn(v))
			low[u]=min(low[u],dfn[v]);
		else
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
	}
	if(low[u]==dfn[u])
	{
		int now=stack[--top];s_sum++;
		s[u]+=s_sum;
		while(now!=u)
		{
			s[now]=s_num;
			now=s[--top];
		}
	}
}
```

所以，我们再来分析一下这道题。

首先，不难发现，如果这所有的牛都存在同一个强联通分量里。那么它们一定互相受欢迎。

那么，我们怎么来找明星呢。

很简单，找出度为$0$的强联通分量中的点。这样可以保证所有的人都喜欢它，但是它不喜欢任何人，所以说不存在还有人事明星。

此题还有一个特殊情况：

如果有两个点分别满足出度为零的条件，则没有明星，这样无法满足所有的牛喜欢他。

有了上边的解释，题目就不是那么难了，代码如下
```cpp
#include<bits/stdc++.h>
#define ri register int
using namespace std;
const int maxn=1e4+5;
const int maxm=5e4+5;
int to[maxm],nex[maxm],fir[maxn];
int col,num,dfn[maxn],low[maxn],de[maxn],si[maxn];
int tot=0,co[maxn],n,m;
int top,st[maxn];
template<class T> inline void read(T &x)
{
    x=0;
    register char c=getchar();
    register bool f=0;
    while (!isdigit(c)) f ^=c=='-',c=getchar();
 	while (isdigit(c)) x=x*10+c-'0',c=getchar();
    if(f)x=-x;
}
template <class T> inline void print(T x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar('0'+x%10);
}
inline void ins(int x,int y)
{
    to[++tot]=y;
    nex[tot]=fir[x];
    fir[x]=tot;
}
void Tarjan(int u)
{
    dfn[u]=low[u]=++num;
    st[++top]=u;
    for(int i=fir[u];i;i=nex[i])
    {
        int v=to[i];
        if(!dfn[v])
        {
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!co[v])low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        co[u]=++col;
        ++si[col];
        while(st[top]!=u)
        {
            ++si[col];
            co[st[top]]=col;
            --top;
        }
        --top;
    }
}
int main()
{
    int x,y;
    read(n);read(m);
    for(ri i=1;i<=m;i++)
    {
        read(x);read(y);
        ins(y,x);
    }
    for(ri i=1;i<=n;i++)
        if(!dfn[i])Tarjan(i);
    for(ri i=1;i<=n;i++)
        for(ri j=fir[i];j;j=nex[j])
            if(co[i]!=co[to[j]])de[co[to[j]]]++;
    int ans=0,u=0;
    for(ri i=1;i<=col;i++)if(!de[i])ans=si[i],u++;
    if(u==1)print(ans);
     else print(0);
 	return 0;
}
```

---

## 作者：小菠萝 (赞：63)

#本蒟蒻逛了一圈发现dalao们用的都是tarjan，好吧，其实这道题用kosaraju思路也是很简单的

##大体思路就是缩点，缩到最后的的那个强连通分量就是被喜欢的最多的牛牛们。

这就是kosaraju的过程，一个反图，这样的话就从最后那个强连通分量中随便找一个点，然后进行反图便利

如果所有的点都被访问过了，证明最后一个强连通分量中的点都是明星牛，如果访问不到，则说明没有牛是明星

（因为最后一个强连通分量就已经是被最多的喜欢的牛了麻）

这样的话我们就需要在kosaraju的模板上在加一个DFS即可；

###
        
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 10010
int m,n,nl,mmp,sum;
vector<int> G[maxn];
vector<int> RG[maxn];
vector<int> vs;
bool used[maxn];
int cmp[maxn];
void add(int a,int b)//两个邻接表存储 
{
    G[a].push_back(b);//正图 
    RG[b].push_back(a);//反图 
}
void dfs(int v)//第一遍搜索； 
{
    used[v]=1;
    for(int i=0;i<G[v].size();i++)
    {
        if(!used[G[v][i]])
        dfs(G[v][i]);
    }
    vs.push_back(v);
}
void rdfs(int v,int k)//第二遍搜索 
{
    used[v]=1;
    cmp[v]=k;
    for(int i=0;i<RG[v].size();i++)
    {
        if(!used[RG[v][i]])
        rdfs(RG[v][i],k);
    }
}
int scc()
{
    memset(used,0,sizeof(used));
    vs.clear();
    for(int i=1;i<=n;i++)
    if(!used[i])
    dfs(i);
    memset(used,0,sizeof(used));
    int k=0;
    for(int i=vs.size()-1;i>=0;i--)
    if(!used[vs[i]])
    rdfs(vs[i],k++);
    return k;
}
int DFS(int haha)//其实这个搜索可以直接用第二个（rdfs）替代，不过这样看起来比较清楚。。。。。。 
{
    used[haha]=1;
    for(int i=0;i<RG[haha].size();i++)
    {
        if(!used[RG[haha][i]])
        DFS(RG[haha][i]);
    }
}
int main()
{
    int u,p;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    cin>>u>>p,add(u,p);
    int ans=scc();
    //cout<<ans<<endl;
    for(int i=1;i<=n;i++)
    {
    if(cmp[i]==ans-1)//注意这里ans要减一； 
        {
            mmp=i;
            sum++;
        }
    }
    memset(used,0,sizeof(used));
    rdfs(mmp,1);
    for(int i=1;i<=n;i++)//看一下是否所有点都被访问过了 
    {
        if(!used[i])
        {
            cout<<0<<endl;
            return 0;
        }
    }
    cout<<sum<<endl;//如果都被访问过了则最后一个强连通分量里的牛牛都是明星，输出即可； 
    return 0;
}
```

---

## 作者：BinDir0 (赞：51)

### 经典的tarjan缩点题qwq

先把爱慕关系构一个有向图，因为爱慕关系可继承，所以**在同一个强连通分量中的所有牛都互相爱慕**

因此我们可以利用tarjan进行缩点，将那些互相爱慕的牛们看做一头牛。

缩点后的奶牛们就不会有互相爱慕的关系了，因此我们可以分析出**只有不爱慕他人的牛才可能当明星（噗**

于是我们就找缩点后出度为0的点。

但如果有多个点出度为0，那么它们都当不了明星（它们没有受到对方的爱慕—>它们没有受到所有牛的爱慕）。

得出结论:

### 1.缩点后，若只有一个出度为0的点，那么明星牛的个数即那个强连通分量包含的点的个数；

### 2.缩点后，若有多个出度为0的点或无出度为0的点，那么明星牛的个数即为0。

代码奉上qwq

```cpp
//Author:502BadGTway
#include<bits/stdc++.h>
using namespace std;
int n,m,fst[10010],v[100010],nex[100010],a,b,dfn[10010],low[10010];
int scc[10010],t,cnt,size[10010],minn[10010],out[10010],cont,ans;
bool f[10010];
stack<int> s;
void tarjan(int k)
{
    low[k]=dfn[k]=++t;
    f[k]=true;
    s.push(k);
    for(int i=fst[k];i!=-1;i=nex[i])
    {
        if(!dfn[v[i]])
        {
            tarjan(v[i]);
            low[k]=min(low[k],low[v[i]]);
        }
        else 
        {
            if(f[v[i]])
            low[k]=min(low[k],dfn[v[i]]);
        }
    }
    if(low[k]==dfn[k])
    {
        f[k]=false;
        scc[k]=++cnt;
        size[cnt]=1;
        while(s.top()!=k)
        {
            scc[s.top()]=cnt;
            f[s.top()]=false;
            size[cnt]++;
            s.pop();
        }
        s.pop();
    }
    return ;
}
int main()
{
    cin>>n>>m;
    memset(fst,-1,sizeof(fst));
    memset(low,0x7f/3,sizeof(low));
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        nex[i]=fst[a];
        v[i]=b;
        fst[a]=i;
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            t=0;
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=fst[i];j!=-1;j=nex[j])
        {
            if(scc[i]!=scc[v[j]])
            out[scc[i]]++;
 		}
    }
    for(int i=1;i<=cnt;i++)
    {
        if(out[i]==0)
        {
            cont++;
            ans+=size[i];
        }
    }
    if(cont==1)
    {
        cout<<ans;
    }
    else
    cout<<0;
    return 0;
}
```


---

## 作者：Steven_Meng (赞：47)

这道题有可以用暴力水过，不用tarjan

思路：将奶牛看成节点，反向建边，对于一只奶牛，跑一边暴力dfs，判断能不能到达其他所有奶牛，然后加一些小小的剪枝就可以过了。

```cpp
//n方过百万，暴力碾标算
//我相信：暴力出奇迹 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAXN 10005
using namespace std;
int vis[MAXN];
int is_all[MAXN];//是否全部被欢迎:-1不确定，1：全部被欢迎，0：不全部被欢迎 
int sz[MAXN];
int haveans;
vector<int>G[MAXN];
void dfs(int u){
    if (haveans==1){
        return ;
    }
    for (register int i=0;i<sz[u];++i){
        if (!vis[G[u][i]]){
            vis[G[u][i]]=true;
            if (is_all[G[u][i]]==1){//剪枝1：当搜索到一只奶牛，从它出发能到达所有奶牛，则从这只奶牛出发能够到达所有奶牛
                haveans=is_all[G[u][i]];
                return ;
            }
            dfs(G[u][i]);
        }
    }
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (register int i=0;i<m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        vis[u]=true,vis[v]=true;
        G[v].push_back(u);
    }
    bool flag=false;
    for (register int i=1;i<=n;++i){
        if (vis[i]==0){
            flag=true;
            break;
        }
    }
    if (flag==true){//第二个剪枝，如果有奶牛没有在图中，则答案为0
        printf("0\n");
        return 0;
    }
    for (register int i=1;i<=n;++i){
        sort(G[i].begin(),G[i].end());
        sz[i]=unique(G[i].begin(),G[i].end())-G[i].begin();
    }
    int sum=0;
    memset(is_all,-1,sizeof(is_all));
    for (register int i=1;i<=n;++i){
        if (is_all[i]==0){//无法到达所有奶牛
            continue;
        }
        haveans=-1;
        memset(vis,0,sizeof(vis));
        vis[i]=true;
        dfs(i);
        if (haveans==1){
            is_all[i]=1;
            sum++;
        }
        else if (haveans==-1){
            bool flag=false;
            for (register int j=1;j<=n;++j){
                if (vis[j]==0){
                    flag=true;
                    break;
                }
            }
            if (flag==false){
                is_all[i]=1;
                sum++;
            }
            else {
                for (register int j=1;j<=n;++j){
                    if (vis[j]) is_all[j]=0;
                }
                //这个剪枝很重要，如果此奶牛无法到达所有奶牛，那么此奶牛能够到达的所有奶牛无法到达所有奶牛(有点绕口qwq)
            }
        }
    }
    printf("%d\n",sum);
}
```

然后就可以水过了，膜拜各个大佬的tarjan

---

## 作者：Masterchief (赞：42)

#Tarjan正解，自己的大数据已过

~~这道题洛谷上的数据比较水~~，所以好像floyd也能过，我带来的是tarjan版~~犇犇勿喷~~

下面我们说说这道题的解法，我们看下面这张图，a仰慕b,b仰慕c,c仰慕d，d仰慕b

 ![](https://cdn.luogu.com.cn/upload/pic/9420.png) 

不难发现，b,c,d是一个强连通分量，如果这个分量中的任意一个点被仰慕，那么说明这个分量中的所有的牛都会被仰慕，那么我们就把这个图全部缩成强连通分量，这个图就变成了有向无环图，这时我们会发现，被所有牛仰慕的牛出度一定是为0的，因为是有向无环图，如果被所有牛仰慕，自己又仰慕别人，那么就会产生一个环。

**因为我们只关注一个分量的出度是否为0，所以不用判断两个分量间的边是否重复统计**

其次，如果这个图存在一个以上出度为0的强连通分量，这个图就会变成非连通图，就不存在被所有牛仰慕的牛，直接输出0，下面我们看看代码

```cpp
#include<bits/stdc++.h>
#define maxn 1000000
using namespace std;
int Next[maxn],a=0,F[maxn],Head[maxn],cmpi[maxn],out[maxn],E[maxn],cmp[maxn],s[maxn],dfn[maxn],low[maxn],top=0,cmpid=0,tim=0;
bool V[maxn],D[maxn];
void ins(int x,int y,int i)
{
    E[i]=y;
    Next[i]=Head[x];
    Head[x]=i;
}//链式前向星
int find()
{
    int ans=0;
    for(int i=1;i<=a;i++)
    {
        for(int p=Head[F[i]];p;p=Next[p])//列举这个点的所有邻接点
        {
            if(!D[E[p]])ans++;//如果这个点的邻接点不和他在一个强联通分量的话，那么我们就发现他所在的分量有了出度
        }
    }
    return ans;
}//找一组强连通分量的出度
void tarjan(int u)
{
    dfn[u]=low[u]=++tim;
    s[++top]=u;
    V[u]=true;
    for(int p=Head[u];p;p=Next[p])
    {
        int y=E[p];
        if(!dfn[y])
        {
            tarjan(y);
            low[u]=min(low[y],low[u]);
        }
        else
        {
            if(V[y])low[u]=min(low[u],dfn[y]);
        }
    }
    if(dfn[u]==low[u])
    {
        int y;
        cmpid++;
        do
        {
            y=s[top--];
            V[y]=false;
            F[++a]=y;//将这个点存入暂时数组
            D[y]=true;
            cmpi[cmpid]++;
        }while(y!=u);
        cmp[cmpid]=find();//cmp存储他的出度
        a=0;
        memset(D,false,sizeof(D));//D数组表示这个点在不在这个强连通分量
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        ins(a,b,i);
    }
    for(int i=1;i<=n;i++)
       if(!dfn[i])tarjan(i);
    int c=0,ans;
    for(int i=1;i<=cmpid;i++)
      if(!cmp[i])c++,ans=i;//检查图是否连通
    if(c==1)printf("%d",cmpi[ans]);//输出
    else printf("0");
    return 0;
} 
```

---

## 作者：zhy_ (赞：32)

[题目：受欢迎的牛](https://www.luogu.org/problem/P2341)

## 什么是强连通分量？？？

 1,强连通：在一个有向图中，如果两个点可以互相到达，就称为这两个点强连通。
 
 2,强连通图：在一个有向图中，如果任意两个点强连通，就把这个图称为强连通图。
 
 3,强连通分量：在一个非强连通图中的最大强连通子图，称为强连通分量。
 
 至此，关于强连通分量的基本知识已经介绍完了，那么，Tarjan算法到底是什么东东？？？
 
##  Tarjan算法

tarjan算法是通过一次深度优先遍历来实现的，其中有几个重要的数组

1, dfn[]:表示结点i是第几个被搜索到的。

2，low[]:与结点i连接的所有点中dfn[]值最小的一个。

3,stack[]:栈里的元素。

4,flag[]:判断结点i是否在栈里。

因为连通分量里的任意两个点都是强连通的，当存在一个连通分量的时候，点u一定会与它的祖先连通。因为low值代表的是它儿子中dfn[]值最小的，所以它的low值就会更新，从而小于它的dfn[]的值。

当一个点的low[]值等于它的dfn[]的值的时候，说明u点的儿子们没有指向他们祖先的了，所以此时u点与它的子孙们构成了一个连通分量。

## 缩点
接下来缩点这个步骤就是这题的关键。

首先我们得知道什么是缩点，当我们找到一个连通分量的时候，因为这个连通分量里的点都是强连通的，所以我们可以把它们看成一个点。

当我们把每一个连通分量都进完缩点时，我们只需要在剩下的这张图中找明星就行了，如果这张图里的每一个点都是强连通，那么显然这张图里的牛都是明星。否则我们可以找到出度为0的牛，这样可以保证其他所有的牛都喜欢它，但是如果有2个以上的出度为0的牛，那么很显然这张图里是不存在明星的。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int w[10003],c[10003];
struct node{          //链式前项型存图 
	int from;
	int to;
	int next;
}a[100003];
int head[190003],Dfn[100003],Low[100003],fl[100003],stack[100003],color[100003],cnt[100003],du[100003],t,tot,k;
//stack[]记录栈里的元素 
//fl[]为记录当前节点是否在栈里
//color[]就是把所有的连通分量都变成一个颜色，也就是缩点
//cnt[]记录每个连通分量里的元素个数
//du[]就是在缩完点之后，记录每个点的出度为多少 
void dfs(int i)
{
	Dfn[i]=Low[i]=++tot;         //表示点i是第几个被遍历到的，把low[i]的值先赋值为dfn[i]的值 
	stack[++k]=i;                //点i入栈 
	fl[i]=1;                     //入栈所以点i变为1 
	for(int j=head[i]; j; j=a[j].next)     //遍历与这个点相连的所有点 
	{
		if(!Dfn[a[j].to]) dfs(a[j].to),Low[i]=min(Low[i],Low[a[j].to]);     //如果与它相连的这个点没有被遍历过，就往下遍历，并比较它和子孙的low[]值 
		else if(fl[a[j].to]) Low[i]=min(Low[i],Dfn[a[j].to]);               //否则如果这个点在栈中，表示他们都在一个连通分量里 
	}
	if(Low[i]==Dfn[i])           
	{
		t++;      //每个连通分量的标号 
		do{
			color[stack[k]]=t; cnt[t]++;           //cnt记录每个强连通分量里有多少个数 
			fl[stack[k]]=0;                       //出栈 
			k--;
		}while(i!=stack[k+1]);
	}
}
int main(){
	int n,m,x,y;
	cin>>n>>m;
	for(int i=1; i<=m; ++i)
	{
		cin>>a[i].from>>a[i].to;
		a[i].next=head[a[i].from];
		head[a[i].from]=i;
	}
	for(int i=1; i<=n; ++i)
	if(!Dfn[i]) dfs(i);
	for(int i=1; i<=n; ++i)
	{
		for(int j=head[i]; j; j=a[j].next)
		{
			if(color[i]!=color[a[j].to])            //缩完点之后判断每种颜色的出度为多少 
			{
				du[color[i]]++;
			}
		}
	}
	int ans=0;
	for(int i=1; i<=t; ++i)
	{
		if(du[i]==0)   //找到度为0的点 
		{
			if(ans) {cout<<0; return 0;
			}
			ans=i;
		}
	}
	cout<<cnt[ans];
	return 0;
}
```


---

## 作者：GoldenPotato137 (赞：15)

蒟蒻博客：[QAQ](https://www.cnblogs.com/GoldenPotato/p/9140872.html)



------------
### Solution
前排提示，本蒟蒻做法既奇葩又麻烦

.

 

我们先可以把题目转换一下。

可以把一头牛喜欢另外一头牛理解为另外一头牛被一头牛喜欢。

我们把被喜欢的关系建边，**即B被A喜欢，从B向A连一条有向边**。

显然，一个点若能到达其他所有节点，它就是题目中的明星牛。

 
 .
 

接下来，我们可以考虑一个类似于DP的做法。

即一个点能访问到的点，等同于它的儿子们访问的到的点加上它自己。

显然，这种特性要在DAG（有向无环图）上才能方便的使用。

 .
 

所以说，我们第一步要对题目做的是缩点。

 .

缩完点之后，我们就可以进行图上DP了。

我们可以用一个01数组f[i][j]表示i能具体能到达的点为j（用010101数列表示）。

显然 f[i] |= f[k] （或运算）（k为i直接相连的点）

答案为f[i][j] j=11111111.... 的点 

.

 

当然，这样做有一个问题。

点的最大数目为n，我们这样做是O(n^2)的，在最坏条件（没有一个点能缩在一起）的情况下，会T。

我们这时候就得请出bitset。

bitset的食用方法：[借用胡小兔dalao的博客](https://www.cnblogs.com/RabbitHu/p/bitset.html)

使用bitset后，我们计算一个点能到达其他的点的复杂度一下子降为了**O(n/32)**

**总复杂度为O(n^2/32) **

 

 

 .
 
 .
 

然后就可以过啦。


------------
### Code
```cpp
//Luogu P2341 [HAOI2006]受欢迎的牛
//June,5th,2018
//缩点+（完全没必要的）bitset
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<bitset>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int  N=10000+100;
vector <int> e[N],e2[N];
int n,m,belong[N],nd_tot,dfn[N],mcount,low[N],cnt[N];
bool InStack[N];
stack <int> s;
bitset <N> arrival[N]; 
void Tarjan(int now)
{
    InStack[now]=true;
    s.push(now);
    dfn[now]=low[now]=++mcount;
    for(int i=0;i<int(e[now].size());i++)
        if(dfn[e[now][i]]==0)
        {
            Tarjan(e[now][i]);
            low[now]=min(low[now],low[e[now][i]]);
        }
        else if(InStack[e[now][i]]==true)
            low[now]=min(low[now],low[e[now][i]]);
    if(low[now]==dfn[now])
    {
        nd_tot++;
        while(s.empty()==false)
        {
            int temp=s.top();
            s.pop();
            InStack[temp]=false;
            belong[temp]=nd_tot;
            cnt[nd_tot]++;
            if(temp==now) break;
        }
        arrival[nd_tot][nd_tot]=true;
    }
}
bool vis[N];
int ans=0;
void dfs(int now)
{
    vis[now]=true;
    for(int i=0;i<int(e2[now].size());i++)
    {
        if(vis[e2[now][i]]==false)
            dfs(e2[now][i]);
        arrival[now]|=arrival[e2[now][i]];
    }
    if(int(arrival[now].count())==nd_tot)
        ans+=cnt[now];
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        e2[i].reserve(4),
        e[i].reserve(4);
    for(int i=1;i<=m;i++)
    {
        int s=read(),t=read();
        e[t].push_back(s);
    }
    
    for(int i=1;i<=n;i++)
        if(dfn[i]==0)
            Tarjan(i);
    for(int i=1;i<=n;i++)
        for(int j=0;j<int(e[i].size());j++)
            if(belong[i]!=belong[e[i][j]])
                e2[belong[i]].push_back(belong[e[i][j]]);
    for(int i=1;i<=nd_tot;i++)
        if(vis[i]==false)
            dfs(i);
        
    printf("%d",ans);
    return 0;
}

```



---

## 作者：WanchengNotWildMan (赞：13)

既然爱慕关系可以传递，那么将互相可达的某几个点缩成一个点，就能简化原图了，

那么很自然想到tarjan求强连通分量

那么就只需找到可以被所有缩点遍历到的那个缩点

再输出它所含的点数就行了

本题需要用到一个很巧妙的结论：

在有向图中，如果有且仅有一个点的出度为0 （没有指向其他点的边），那么该点可以被所有点遍历到；反之，该图中没有可以被所有点遍历到的点

在有向图中，如果一个点可以被所有点遍历到，那么这个点的出度为0

可用反证法证明，







            



```cpp
#include<bits/stdc++.h>
using namespace std;
stack<int>sta;
int e=0,f=0,low[10004],nscc[10004],dfn[10004],head[10004],head2[10004],dfs_clock,sccno[10004],sccw[10004],scc_cnt,w[10004],dp[10004],ans,n,m;
bool vis[10004];
struct node {
    int v,next;
} a[100004],b[100004];
void insert(int u,int v) {
    a[++e].v=v;
    a[e].next=head[u];
    head[u]=e;
}
void insert2(int u,int v) {
    b[++f].v=v;
    b[f].next=head2[u];
    head2[u]=f;
}
void tarjan(int u) {
    low[u]=dfn[u]=++dfs_clock;
    sta.push(u);
    for(int p=head[u]; p!=0; p=a[p].next) {
        int v=a[p].v;
        if(!dfn[v]) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        } else if(!sccno[v]) {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]) {
        scc_cnt++;
        int x=0;
        for(;;) {
            x=sta.top();
            sta.pop();
            sccno[x]=scc_cnt;
            nscc[scc_cnt]++;//nscc[i]记录强连通分量i所含的点的个数 
            if(x==u)break;
        }
    }
}
int main() {
    cin>>n>>m;
    //for(int i=1; i<=n; i++)scanf("%d",&w[i]);
    for(int i=1; i<=m; i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        insert(u,v);
        //    insert2(v,u);
    }
    for(int i=1; i<=n; i++) {
        if(!dfn[i])tarjan(i);
    }
    bool flag[scc_cnt+10][scc_cnt+10];
    for(int i=1; i<=n; i++)//遍历所有的点 
        for(int p=head[i]; p; p=a[p].next) {//遍历每个点的边 
            if(!flag[sccno[i]][sccno[a[p].v]]&&sccno[i]!=sccno[a[p].v]) {//若i点所在的强连通分量缩点与它的子节点所在的强连通分量缩点之间没有连接， 
                insert2(sccno[i],sccno[a[p].v]);//则连接两个缩点 
                flag[sccno[i]][sccno[a[p].v]]=1;
            }
        }
    int po=0,starscc=0;
    //po记录出度为0的点的数量 
    for(int i=1; i<=scc_cnt; i++)
    if(!head2[i]) {//若i点没有儿子，则该点没有出边 
            po++;
            starscc=i;
    }
    if(po==1) {
        cout<<nscc[starscc]<<endl;
        return 0;
    }
    cout<<0<<endl;
}
```

---

## 作者：Kevin_F (赞：11)

这是一个tarjan强连通分量与出度结合的例题。

先明确一下题意，如果这个点（缩点之后的）没有出度，这个点才能成为明星牛（明星牛的定义是：所有牛都喜欢他才可以）。

由于我们进行了缩点，所以我就另外开一个数组num[i]:表示这个强连通分量中有多少个点。

```cpp
	int sum = 0;
	for(int i=1;i<=cnt;i++)
	  if(!chu[i])  ans = num[i] , sum++;
	if(sum >= 2)  printf("0");
	else printf("%d",ans);
```

以上就是怎样处理最后的答案：

如果我们有两个或以上出度为 0 点（缩点后的），说明这几个出度为 0 的点（缩点后）互相不喜欢，所以没有明星牛。

否则就有明星牛（明星牛的个数就是出度为 0 的那个强连通分量中点的个数），很好想吧：那个强连通分量中的牛互相喜欢，而其他强连通分量中的牛也喜欢他们，等量代换所有牛都喜欢他


首先是tarjan缩点中的几个数组：

     dfn[i]:i点的时间戳

     low[i]，表示这个点以及其子孙节点连的所有点中dfn最小的值

     stack[]，表示当前所有可能能构成是强连通分量的点。

     ins[i]，表示 i 是否在stack[ ]数组中

     num[i],表示第 i 个强连通分量中有多少个点

     belong[i],表示第 i 点在哪一个强连通分量里
     
下面就是AC代码了

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 4;
const int maxm = 5e4 + 4;

int n,m,u,v;
int head[maxn],tot;
int dfn[maxn],low[maxn],ind;
int stack[maxn],top,num[maxn],belong[maxn],cnt;
bool ins[maxn];
int chu[maxn],ans;
struct Edge{
	int from,to,next;
}edge[maxm];

void add(int u,int v){
	edge[++tot].from = u;
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
}

int read(){
	char ch = getchar();
	int f = 1 , x = 0;
	while(ch > '9' || ch < '0'){
		if(ch == '-')  f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = x * 10 + ch - '0';
		ch = getchar(); 
	}
	return x * f;
}

void tarjan(int x){
	dfn[x] = low[x] = ++ind;
	stack[++top] = x;
	ins[x] = true;
	for(int i=head[x];i;i=edge[i].next){
		int v = edge[i].to;
		if(ins[v]) low[x] = min(low[x] , dfn[v]);
		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x] , low[v]);
		}
	}
	int k = 0;
	if(dfn[x] == low[x]){
		cnt++;
		do{
			k = stack[top];
			num[cnt]++;
			top--;
			ins[k] = false;
			belong[k] = cnt;
		} while(k != x);
	}
} 

int main(){
	n = read();  m = read();
	for(int i=1;i<=m;i++){
		u = read();  v = read();
		add(u , v);
	}
	for(int i=1;i<=n;i++)
	  if(!dfn[i])  tarjan(i);
	for(int i=1;i<=m;i++){
		if(belong[edge[i].from] != belong[edge[i].to]){
			chu[belong[edge[i].from]]++;
		}
	}
	int sum = 0;
	for(int i=1;i<=cnt;i++)
	  if(!chu[i])  ans = num[i] , sum++;
	if(sum >= 2)  printf("0");
	else printf("%d",ans);
	return 0;
}
```

---

## 作者：残血夕阳 (赞：5)

就像第一篇题解讲到，本题就是要找出 出度为0的强连通分量，很容易想到用tarjan找出强连通分量；
标程：
```cpp
void tarjan(int u){
	dfn[u]=low[u]=++ti;
	stack[++top]=u;
	for (int i=head[u];i;i=next[i]){
		int v=to[i];
		if (!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if (!col[v]) low[u]=min(low[u],dfn[v]);
	}
	if (low[u]==dfn[u]){
		col[u]=++co;
		si[co]++;
		while (stack[top]!=u){
			col[stack[top--]]=co;
			si[co]++;
		}
		top--;
	}
	return;
}
```
接下来就是要计算各强连通分量的出度，我的方法是遍历每一条边；
```
for (int i=1;i<=n;i++){
		for (int j=head[i];j;j=next[j]){
			if (col[i]==col[to[j]])continue;
			col_out[col[i]]++;
		}
	}
```
最后就是得出答案了，
但这里有一个坑，若对于该图，存在两个及以上出度为0的强连通分量，则表明该图并不连通则不存在“明星牛”，
即答案为0；
完整代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
inline int read(){
	int x=0,f=1;
	char s=getchar();
	while (s<'0' or s>'9'){
		if (s=='-') f=-1;
		s=getchar();
	}
	while (s>='0'and s<='9'){
		x=(x<<3)+(x<<1)+s-'0';
		s=getchar(); 
	}
	return x*f;
}
const int N=100000;
const int M=100000;
int head[N],to[M],next[M];
int stack[N],top,ti,dfn[N],low[N];
int col[N],col_out[N],co,si[N];
int n,m;
void tarjan(int u){
	dfn[u]=low[u]=++ti;
	stack[++top]=u;
	for (int i=head[u];i;i=next[i]){
		int v=to[i];
		if (!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if (!col[v]) low[u]=min(low[u],dfn[v]);
	}
	if (low[u]==dfn[u]){
		col[u]=++co;
		si[co]++;
		while (stack[top]!=u){
			col[stack[top--]]=co;
			si[co]++;
		}
		top--;
	}
	return;
}
int main(){
	n=read();
	m=read();
	int a,b;
	for (int i=1;i<=m;i++){
		a=read();
		b=read();
		to[i]=b;
		next[i]=head[a];
		head[a]=i;
	}
	for (int i=1;i<=n;i++){
		if (col[i])continue;
		tarjan(i);
	}
	for (int i=1;i<=n;i++){
		for (int j=head[i];j;j=next[j]){
			if (col[i]==col[to[j]])continue;
			col_out[col[i]]++;
		}
	}
//	for (int i=1;i<=n;i++){
//		cout<<i<<" "<<col[i]<<" "<<col_out[col[i]]<<endl;
//	}
	int ans=0;
	for (int i=1;i<=co;i++){
		if (col_out[i]==0){
			if (ans==0) ans=si[i];
			else{
				cout<<0<<endl;
				return 0;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：NIMNIM (赞：4)

## **Tarjan 算法**

传送门：[P2341 [HAOI2006]受欢迎的牛|【模板】强连通分量](https://www.luogu.org/problem/P2341)

这真的简（du）单（liu）

好吧
### $\color{green}\texttt{这个东西好恶心好恶心好恶心}$ 

先记录几个blog讲解（我不知道要不要版权，如果博主看见我的这篇文章了可以在洛谷私信我，我的ID是144762）

1.[tarjan求强连通分量+缩点+割点/割桥（点双/边双）以及一些证明](https://www.cnblogs.com/stxy-ferryman/p/7779347.html)

2.[[洛谷日报第23期]初探tarjan算法 ](http://sohu.com/a/245954819_100201031)

3.找不到了，到时我会补上的。。。

------------------------------------------------------------

这个算法呢，已发题解本来已经有很多讲解了~~但是我就是没AC~~，但是我太蠢了，犯下了许多小错误，所以才弄了一个多月才初步打出这个算法的代码。

至于这道题，我们可以发现几点：

------------------------------------------------------------

#### 1.如果有一头牛受到且仅受到x头其他牛的爱戴，并且它与p牛相互爱戴，那么p牛受到且仅受到x头牛的爱戴。

#### 这样一看，就相当于：如果点A可以且仅可以被x个点走到，并且A和B相互通达，那么B也可以且仅可以被x点走到，所以我们可以把互相爱戴的一群牛看成新的一头牛，这就是所谓的“缩点”。（至此，一下的一头牛意思都可以理解为一群牛）

------------------------------------------------------------

#### 2.如果有两头牛，他们都没有爱戴的对象，这说明其他的每一头牛都受不到这两头牛的爱戴，而这两头牛都不受到对方的爱戴，所以这种情况下没有明星，可以直接输出0。

------------------------------------------------------------

#### 3.在只有一头牛不爱戴其他任何人（出度为0），并且没有情况2的时候，这说明所有牛都直接或间接地爱戴这一头牛，所以这一头牛就是明星。（事实上是这一群牛）

------------------------------------------------------------

然后有的萌新（$\color{blue}\texttt{像我}$ ）就有个问题——怎么缩点

对于缩点，我们可以先用基本Tarjan“染色”，也就是找到每个点浓缩后属于哪个点，同时统计这个缩点后的点所包含的原有点的数量，然后枚举每个点，根据旧的联系，在新的图上加边（记得判重）。

这就（cai）把这道题弄得比较简单了。。。。

代码如下（还不是很懂的可以看注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
int n,m,t=0,c=0;
int dfn[MAXN]={},low[MAXN],bel[MAXN],ct[MAXN]={};
map <int,bool> mm;//map判重 
vector <int> vec[MAXN];
vector <int> vec2[MAXN];
deque<int> que;
void tarjan(int p)//Tarjan
{
	dfn[p]=low[p]=++t;que.push_back(p);
	for(int i=0;i<vec[p].size();i++)
	{
		if(dfn[vec[p][i]])
			low[p]=min(low[p],dfn[vec[p][i]]);
		else
		{
			tarjan(vec[p][i]);
			low[p]=min(low[p],low[vec[p][i]]);
		}
	}
	if(dfn[p]==low[p])//找到返祖边，开始染色 
	{
		c++;
		while(que.back()!=p)
		{
			bel[que.back()]=c;
			que.pop_back();
			ct[c]++;//统计 
		}
		bel[que.back()]=c;
		ct[c]++; //统计 
		que.pop_back();
	}
}

int main ( )
{
	int shi,shou,ans=0,pos=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&shi,&shou);
		vec[shi].push_back(shou);//加边 
	}
	for(int i=1;i<=n;i++)
		if(dfn[i]==0)
			tarjan(i);
	for(int i=1;i<=n;i++)//现在开始建立缩点后的图 
	{
		for(int j=0;j<vec[i].size();j++)
		{
			int r=bel[vec[i][j]];
			if(r!=bel[i]&&!mm.count(bel[i]*99+r*9))//bel[i]*99+r*9 这是我自己的判重方式 
			{								//读者可以自己设置，我的比较玄学 
				vec2[bel[i]].push_back(r);
				mm[bel[i]*99+r*9]=true;//判重，其实我这里本来是数组，然后RE了 
			}
		}
	}
	for(int i=1;i<=c;i++)
	{
		if(vec2[i].size()==0)
		{
			ans++;
			pos=ct[i];
		}
		if(ans>1)//若果有两个强联通分量出度为 0 
		{
			cout<<'0';//直接输出 0 
			return 0;
		}
	}
	cout<<pos;
	return 0;
}
```
PS:大家可以查查我的记录，汲取教训，我的ID在文章开头已经给出

PS2：管理大大觉得不好，没必要给通过，我主要是自我反思一下qwq

---

## 作者：chihik (赞：4)

这道题一看就是一道强连通分量的题，不会的可以参考我的[博客](https://www.luogu.org/blog/chihik/qiang-lian-tong-fen-liang)。

当我们用$Tarjan$缩点之后，记新图点的个数为$cnt$。我们枚举原图的每一条边，计算新图中的点的出度。对于点$i$，我们把它的出度记为$Out[i]$。那么，会有以下几种情况：

1.没有一个$Out[i]$为0，说明每一个点至少有一条连向其他边的有向边，那么新图至少有$cnt$条边，一定会有一个环(因为$cnt-1$条边是一棵树，无论如何加边都会构成环)，但缩点后不可能有环，矛盾。

2.只有一个$Out[i]$为0，那么这个点一定受到所有奶牛的膜拜，（其他奶牛出度不为0，会膜拜其他奶牛，这样膜来膜去一定会汇集到出度为0的奶牛上，~~不理解的自行脑补一下~~）

3.有两个及以上的$Out[i]$为0，那么每个人至少得不到一群奶牛（已经缩点，可能不止一头）的支持。直接输出0。


综合以上三点，我们就可以写出正解了：

```cpp
#include <cstdio>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

const int MAXN = 10000;
int n,m,x,y;
vector< int > Graph[ MAXN + 5 ];
vector< int > lit_Graph[ MAXN + 5 ];
stack< int > s;

int dfn[ MAXN + 5 ] , low[ MAXN + 5 ] , depth , cnt;
int belong[ MAXN + 5 ] , num[ MAXN + 5 ] , Out[ MAXN + 5 ];
bool is[ MAXN + 5 ];
void Tarjan( int u ) {
    dfn[ u ] = low[ u ] = ++ depth;
    is[ u ] = 1 , s.push( u );

    int v;
    for( int i = 0 ; i < Graph[ u ].size( ) ; i ++ ) {
        v = Graph[ u ][ i ];
        if( !dfn[ v ] ) {
            Tarjan( v );
            low[ u ] = min( low[ u ] , low[ v ] );
        }
        else if( is[ v ] )
            low[ u ] = min( low[ u ] , dfn[ v ] );
    }
    if( dfn[ u ] == low[ u ] ) {
        cnt ++;
        do{
            v = s.top( );
            is[ v ] = 0 , s.pop( );
            belong[ v ] = cnt;
            num[ cnt ] ++;
        }while( u != v );
    }
}

int main( ) {
    scanf("%d %d",&n,&m);
    for( int i = 1 ; i <= m ; i ++ ) {
        scanf("%d %d",&x,&y);
        Graph[ x ].push_back( y );
    }
    for( int i = 1 ; i <= n ; i ++ )
        if( !dfn[ i ] ) Tarjan( i );
    for( int i = 1 ; i <= n ; i ++ )
        for( int j = 0 ; j < Graph[ i ].size( ) ; j ++ ) {
            int u = belong[ i ] , v = belong[ Graph[ i ][ j ] ];
            if( u != v ) {
                lit_Graph[ u ].push_back( v );
                Out[ u ] += num[ v ];
            }
        }
    int Ans = 0 , tot = 0;
    for( int i = 1 ; i <= cnt ; i ++ )
        if( Out[ i ] == 0 ) Ans += num[ i ] , tot ++;
    printf("%d",tot >= 2 ? 0 : Ans);
    return 0;
}
```


---

## 作者：panda_2134 (赞：4)

## 记忆化搜索+Tarjan

首先我们想想暴力： $O[N(N+m)]$ 显然炸了

于是想到强连通分量：题目给出的是一个等价关系，而显然同一个SCC里面的奶牛都可达，于是我们先缩点，同时记录每个点包括多少奶牛，再取反图，这样问题就变成了找一个点可以到所有点。

整张图现在是个DAG，于是我们可以证明：此时只有一个点满足其他点都可以到达。

**证明:** 假设存在两个这样的点A和B，那么由于其他点都可以到A，自然B也可以到A；同理A也可以到B，因此A和B应该属于同一个强连通分量。但是它们在缩点后是两个点，与上述矛盾，于是假设不成立，不存在两个点，满足其他所有店都可以到它们。

既然是DAG，不妨设$f(i):$由i可以到几个点（包括i），直接记忆化搜索即可。注意判断：如果图上能到的点的数目最大值都没有达到SCC数目，要输出0.

复杂度：$O(N+M)$


附代码：

```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <stack>
#include <algorithm>
using namespace std;
const int MAXN = 10000, MAXM = 50000;
struct Edge{
    int v,next;
};
struct AdjTable{
    int e_ptr=1,head[MAXN+10];
    Edge E[MAXM*2+10];
    void addedge(int u,int v){
        E[e_ptr]=(Edge){v,head[u]};head[u]=e_ptr++;
    }
}; 
inline int readint() {
    register int f=1,r=0;
    register char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
    while(isdigit(c)){r=r*10+c-'0'; c=getchar();}
    return f*r;
}

int N,M,maxp,maxv,W[MAXN+10],scc_cnt,dfs_clock,dfn[MAXN+10],low[MAXN+10],sccno[MAXN+10],opt[MAXN+10];
stack<int> S; AdjTable G1,G2; 

void dfs(int u) {
    low[u]=dfn[u]=++dfs_clock;
    S.push(u);
    for(int j=G1.head[u];j;j=G1.E[j].next) {
        int v=G1.E[j].v;
        if(!dfn[v]) {
            dfs(v); low[u]=min(low[u],low[v]);
        } else if(!sccno[v]) 
            low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]) {
        ++scc_cnt;
        int v;
        do {
            v=S.top();
            sccno[v]=scc_cnt;
            W[scc_cnt]++;
            S.pop();
        } while(u!=v);//!
    }
}

void Tarjan(){
    for(int i=1;i<=N;i++)
        if(!dfn[i]) dfs(i);
}

void Rebuild() {
    for(int u=1;u<=N;u++) {
        for(int j=G1.head[u];j;j=G1.E[j].next) {
            int v=G1.E[j].v;
            if(sccno[u]!=sccno[v])
                G2.addedge(sccno[v],sccno[u]);
        }
    }
}

int dp(int u) {
    if(opt[u]>0) return opt[u];
    opt[u]=1;
    for(int j=G2.head[u];j;j=G2.E[j].next) {
        int v=G2.E[j].v;
        opt[u]+=dp(v);
    }
    return opt[u];
}

int main() {
    N=readint(); M=readint();
    for(int i=1;i<=M;i++) {
        int a,b;a=readint();b=readint();
        G1.addedge(a,b);
    }
    Tarjan(); 
    Rebuild();
    for(int i=1;i<=scc_cnt;i++)
        if(dp(i)>maxv) {
            maxv=dp(i);maxp=i;
        }
    if(maxv == scc_cnt)
        printf("%d",W[maxp]);
    else printf("0");
}
```

---

## 作者：Manjusaka丶梦寒 (赞：3)

推荐博客：https://www.cnblogs.com/rmy020718/p/9440593.html

如果A喜欢B，那么A->B连边，那么整个图储存下来，如果有好多个牛是受欢迎的，那么他们一定会在一个环中，所以我们先跑一边 tarjan缩点，那么受欢迎的牛群所在的这个点(缩完)，其出度为0。

证：若其出度不为0，则表明对外有连边，因为牛群是受欢迎的则外来点对其也应该有连边，那么他们这就会在一个环中。

所以缩完点后，统计一下每个强联通分量中有多少个点，记录每个点有多少出度，若会存在有两个及以上出度为0的点，那么表明图不连通，则输出0就好了。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn int(1e2+2)
#define N int(1e4+2)
#define M int(5e4+2)
using namespace std;
int n,m,ans[N],sum[N];
struct ahah{
    int nxt,to;
}edge[M];
int head[N],tot;
void add(int x,int y)
{
    edge[++tot].nxt=head[x],edge[tot].to=y,head[x]=tot;
}
bool in[N];
int dfn[N],low[N],indx;
int stack[N],top;
int belong[N],cnt;
void tarjan(int s)
{
    dfn[s]=low[s]=++indx;
    in[s]=1,stack[++top]=s;
    for(int i=head[s];i;i=edge[i].nxt)
    {
        int v=edge[i].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[s]=min(low[v],low[s]);
        }
        else if(in[v]&&low[s]>dfn[v])low[s]=dfn[v];
    }
    if(dfn[s]==low[s])
    {
        int p;
        belong[s]=++cnt;
        do
        {
            p=stack[top--];
            in[p]=0;
            belong[p]=cnt;
        }while(p!=s);
    }
}
int main()
{
    int x,y;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)scanf("%d%d",&x,&y),add(x,y);
    for(int i=1;i<=n;i++)
        if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)
    {
        ans[belong[i]]++;
        for(int j=head[i];j;j=edge[j].nxt)
            if(belong[i]!=belong[edge[j].to])sum[belong[i]]++;
    }
    int p=0;
    for(int i=1;i<=cnt;i++)
    {
        if(!sum[i])
        {
            if(p)
            {
                printf("0");
                return 0;
            }
            p=i;
        }
    }
    printf("%d",ans[p]);
}
```

---

## 作者：redegg (赞：3)

~~这是我写过最长的非模拟题代码了~~

思路就是强连通，缩点，随后找到唯一一个出度为0的联通块（如果不唯一则就无解，输出0），输出这个点里的奶牛数即可。

我不会tarjan，于是代码又长又乱，后来缩点连边时的操作有个小错误一直没发现，45分困扰了很久，然后心态崩盘。

其实我一开始的想法是拓扑排序，是可行的，但是我现在的代码比拓扑排序短很多，因为后来发现拓扑排序是不必要的，可以直接判断出答案。

贴上令人发慌的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,mm;
int op;
struct ha
{
    int id,s;
}a[100000];
bool b[100000];
int dis[100000];

bool cmp(const ha &aa,const ha &bb)
{
    return aa.s>bb.s;
}

vector<int> q[60000];
vector<int> rq[60000];

int r[100000];
vector<int> m[60000];

bool ok[100000];
bool oo[100000];
int an[100000];
int ans[100000];

int d;

void dfs(int x)
{
    for(int i=0;i<q[x].size();i++)
    {
        int nx=q[x][i];
        if(b[nx])continue;
        b[nx]=1;
        dfs(nx);
    }
    op++;
    a[x].id=x;
    a[x].s=op;
}

void di(int x)
{
    dis[x]=op;
    for(int i=0;i<rq[x].size();i++)
    {
        int nx=rq[x][i];
        if(dis[nx]!=0)continue;
        di(nx);
    }
}

void ddd(int x,int k)
{
    for(int i=0;i<q[x].size();i++)
    {
        int nx=q[x][i];
        if(ok[dis[nx]]||oo[nx])continue;
        oo[nx]=1;
        if(dis[nx]==k)
        {
            ddd(nx,k);
        }
        if(dis[nx]!=k)
        {
            ok[dis[nx]]=1;
            r[dis[nx]]++;
            an[k]++;
            m[k].push_back(dis[nx]);
        }
    }
}

int main()
{
    scanf("%d%d",&n,&mm);
    for(int i=1;i<=mm;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        q[x].push_back(y);
        rq[y].push_back(x);
    }

    for(int i=1;i<=n;i++)
    {
        if(b[i])continue;
        b[i]=1;
        dfs(i);
        op++;
        a[i].id=i;
        a[i].s=op;
    }

    sort(a+1,a+1+n,cmp);
    op=0;

    for(int i=1;i<=n;i++)
    {
        if(dis[a[i].id]!=0)continue;
        op++;
        di(a[i].id);
    }


    memset(b,0,sizeof(b));
    for(int i=1;i<=n;i++)
    {
        ans[dis[i]]++;
        if(b[dis[i]])continue;
        memset(oo,0,sizeof(oo));
        memset(ok,0,sizeof(ok));
        b[dis[i]]=1;
        ddd(i,dis[i]);
    }

    for(int i=1;i<=op;i++)
    {
        if(an[i]==0)
        {
            if(d>0)
            {
                printf("0\n");
                return 0;
            }
            d+=ans[i];
        }
    }
    printf("%d\n",d);

    return 0;
}

```

---

## 作者：取名最烦 (赞：2)

逛了一圈发现没有Pascal的题解，所以来发一个。本人蒟蒻，如有不妥之处，各位神犇敬请谅解。

我们把每头奶牛视作一个点，把所以“同意关系”视作一条有向边。这样建立了一个有向图。

然后使用Tarjan求出图中的所有强连通分量，同时记录每个分量中的点的个数（用于以后统计），缩点以后统计新图（保证是一个有向无环图）中有几个点（就是旧图中的强连通分量）出度为零。如果只有唯一一个点出度为零，那么它所包含的旧点数量就是答案。如果大于1，那么输出0（有两拨甚至更多拨奶牛在互怼)。因为新图是有向无环图，所以出度为零的点至少有一个。

~~我的代码可能有点丑，大家忍忍~~
```cpp
uses math;
var i,j,k,l,m,n,s,t,x,y,z,c,r,ans,s1,s2,s3,top:longint;
hd,u,v,p,dfn,low,q,id,num,xp,yp,outp:array[0..200009]of longint;
procedure into(x,y:longint);
begin
 inc(t);
 u[t]:=y;
 v[t]:=hd[x];
 hd[x]:=t;
end;
procedure tarjan(x:longint);//求强连通分量
var i,j:longint;
begin
 inc(t);
 dfn[x]:=t;
 low[x]:=t;
 inc(top);
 q[top]:=x;
 p[x]:=1;
 i:=hd[x];
 if hd[x]<>0 then
  repeat
   if dfn[u[i]]=0 then
   begin
    tarjan(u[i]);
    low[x]:=min(low[x],low[u[i]]);
   end else if p[u[i]]=1 then low[x]:=min(low[x],dfn[u[i]]);
   i:=v[i];
  until i=0;
 if low[x]=dfn[x] then
 begin
  inc(s);
  repeat
   id[q[top]]:=s;
   //p[q[top]]:=0;
   dec(top);
   inc(num[s]);
  until q[top+1]=x;
 end;
end;
begin
 read(n,m);
 for i:=1 to m do
 begin
  read(xp[i],yp[i]);
  into(xp[i],yp[i]);
 end;
 t:=0;
 s:=0;
 for i:=1 to n do
  if p[i]=0 then tarjan(i);
 for i:=1 to m do
  if id[xp[i]]<>id[yp[i]] then inc(outp[id[xp[i]]]);
 t:=0;
 for i:=1 to s do
  if outp[i]=0 then
  begin
   inc(k,num[i]);
   inc(t);
  end;
 case t of
  1:writeln(k);
  2:writeln(0);
 end;
end.
```

---

## 作者：zzlzk (赞：2)

- 一道比较裸的缩点


- 先跑一遍Tarjan求出强连通分量，然后缩点，统计每个点的出度


- 如果只有一个点的出度为 $0$ ，那图大概是这样的


![qwq](http://images.cnblogs.com/cnblogs\_com/NuclearSubmarines/1013327/o\_radsasasd.png)


- 这样 $E$ 这个点的奶牛就被所有的奶牛喜欢啦，所以他们他们都是明星，直接输出 $E$ 这个点包含多少奶牛


- 如果不止一个点的出度为 $0$，那图大概是这样的


![qwq](http://images.cnblogs.com/cnblogs\_com/NuclearSubmarines/1013327/o\_gsdfadsf.png)


- 这样没有奶牛被所有的奶牛喜欢，应该直接输出 $0$


----

###code


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename ____>
void _____(____ &___) {//听说这么写读入优化会增加代码有bug的几率qwq
    ___=0; ____ __=1;
    register char _=getchar();
    for(;_<'0'||_>'9';_=getchar())
        if(_=='-') __=-1;
    for(;_>='0'&&_<='9';_=getchar())
        ___=___*10+_-'0';
    ___*=__;
    return;
}

#define MAXN 10010
#define MAXM 50010

struct Edge {
    int u,v,next;
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
};

Edge edge[MAXM];
int head[MAXN],cnt;

void addedge(int u,int v) {
    edge[++cnt]=Edge(u,v,head[u]);
    head[u]=cnt;
    return;
}

int dfn[MAXN],low[MAXN],timee;
int st[MAXN],top;
int col[MAXN],numcolor;
bool vis[MAXN],ins[MAXN];
int num[MAXN];

void dfs(int now) {
    dfn[now]=low[now]=++timee;
    st[++top]=now;
    vis[now]=ins[now]=true;
    for(int i=head[now];i;i=edge[i].next) {
        int v=edge[i].v;
        if(ins[v]) low[now]=min(low[now],dfn[v]);
        else if(!vis[v]) {
            dfs(v);
            low[now]=min(low[now],low[v]);
        }
    }
    if(dfn[now]==low[now]) {
        col[now]=++numcolor;
        num[numcolor]++;
        while(st[top]!=now) {
            col[st[top]]=numcolor;
            num[numcolor]++;
            ins[st[top--]]=false;
        }
        ins[now]=false;
        top--;
    }
    return;
}


int outdeg[MAXN];

int main() {
    int n,m;
    _____(n),_____(m);
    for(int i=1,A,B;i<=m;i++) {
        _____(A),_____(B);
        addedge(A,B);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i]) dfs(i);
    for(int u=1;u<=n;u++)
        for(int i=head[u];i;i=edge[i].next)
            if(col[u]!=col[edge[i].v])
                outdeg[col[u]]++;
    int sum=0,color;
    for(int i=1;i<=numcolor;i++)
        if(outdeg[i]==0) sum++,color=i;
    if(sum==1) printf("%d\n",num[color]);
    else printf("0");
    return 0;
}

```

看完题解来逛一下[blog](http://blog.csdn.net/NuclearSubmarines/article/details/78207910)也是不错的呢


---

## 作者：winmt (赞：2)

好久不刷luogu发题解了，这题好水～一个tarjan模板。。。这种水题就直接vector上了，勿喷！

**这题要缩点的思路，但不需要真正意义上的缩圈成点。**

**具体是找出SCC分解缩点，然后对于重构的图，出度为0的点若不是有且仅有一个，就说明没有最受欢迎的牛，反之就是此强连通分量里节点个数为ans。自己体会下。**


  
  
      
      
  
      
      
      

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
struct node
{
    int num,par;
}p[50005];
int n,m,index=1,x,y,cnt,ans;
vector<int>v[50005];
bool vis[50005];
int ind[50005];
stack<int>s;
bool in_stack[50005];
int belong[50005],sum[50005],cntx[50005];
void tarjan(int x)
{
    p[x].num=index;
    p[x].par=p[x].num;
    index++;
    vis[x]=1;
    in_stack[x]=1;
    s.push(x);
    for(int i=0;i<v[x].size();i++)
    {
        if(!vis[v[x][i]])
        {
            tarjan(v[x][i]);
            p[x].par=min(p[x].par,p[v[x][i]].par);
        }
        else if(in_stack[v[x][i]])
        {
            p[x].par=min(p[x].par,p[v[x][i]].num);
        }
    }
    if(p[x].num==p[x].par)
    {
        ++cnt;
        int k;
        do
        {
            k=s.top();
            s.pop();
            belong[k]=cnt;
            cntx[cnt]++;
            in_stack[k]=0;
        }while(k!=x);
    }
}
int main()
{  
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])tarjan(i);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<v[i].size();j++)
        {
            if(belong[v[i][j]]!=belong[i])
            {
                sum[belong[i]]++;
            }
        }
    }
    int kkk=0;
    for(int i=1;i<=cnt;i++)
    {
        if(!sum[i])
        {
            kkk++;
            ans=cntx[i];
        }
    }
    if(kkk!=1)printf("%d\n",0); else printf("%d\n",ans);
    return 0;
}
滚去复习文化课期中考试了。。。
```

---

## 作者：ღ﹏ﻬ北❦栀 (赞：2)

## tarjan模板题
这道tarjan模板题，统计一下入度，缩点统计一下该强连通分量内含点个数，答案就差不多搞出来了
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+5;
const int maxm=5e4+5;
int to[maxm],nex[maxm],fir[maxn];
int col,num,dfn[maxn],low[maxn],de[maxn],si[maxn];
int tot=0,co[maxn],n,m;
int top,st[maxn];
inline void ins(int x,int y)//添加一条x->y的边； 
{
	to[++tot]=y;
	nex[tot]=fir[x];
	fir[x]=tot;
 }
 void tarjan(int u)//tarjan缩点 
 {
 	dfn[u]=low[u]=++num;
 	st[++top]=u;
 	for(int i=fir[u];i;i=nex[i])
 	{
 		int v=to[i];
 		if(!dfn[v])
 		{
 			tarjan(v);
 			low[u]=min(low[u],low[v]);
		 }
		 else
		 if(!co[v])//注意判断是否在栈中 
		 low[u]=min(low[u],dfn[v]);
	 }
	 if(low[u]==dfn[u])
	 {
	 	co[u]=++col;
	 	++si[col];
	 	while(st[top]!=u)
	 	{
	 		++si[col];
	 		co[st[top]]=col;
	 		--top;
		 }
		 --top;
	 }
 }
 int main()
 {
 	cin>>n>>m;
 	for(int i=1,x,y;i<=m;++i)
 	{
 		cin>>x>>y;
 		ins(y,x);//这里直接 反向建边，题解中的统计出度就变成了统计入度 
	 }
	 for(int i=1;i<=n;++i)
	 if(!dfn[i])
	 tarjan(i);
	 for(int i=1;i<=n;++i)
	 for(int j=fir[i];j;j=nex[j])//统计入度 
	 if(co[i]!=co[to[j]])
	 de[co[to[j]]]++;
	 int ans=0,u=0;
	 for(int i=1;i<=col;++i)
     if(!de[i])
     ans=si[i],u++;
     if(u==1)
     cout<<ans<<endl;
     else cout<<0;
     return 0;
 }
```


------------
如果大佬有更好的解法，可以给我提出点建议。Thanks♪(･ω･)ﾉ


---

## 作者：寒鸽儿 (赞：1)

到现在才来学强连通分量QaQ(作为没有教练学校不搞OI的蒟蒻技能树完全不平衡)  
注意理解非树边对low的更新:  
只有返祖边入点的dfn和入点未划到强连通分量里的横叉边才是合理的更新low。其他非树边均不可。然后根据dfs的性质,应当判断非树边指向的点有没有加入强连通分量。  
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 12345, M = 56789;
int head[N], ver[M], nex[M], my[M], tot;
inline void addedge(int u, int v) {
	ver[tot] = v; nex[tot] = head[u]; my[tot] = u; head[u] = tot++;
}

int dfn[N], low[N], cl[N], sta[N], outd[N], num[N], top = 0, dfs_clock = 1, col = 1;
void dfs(int cur) {
	dfn[cur] = low[cur] = dfs_clock++;
	sta[top++] = cur;
	for(int i = head[cur]; ~i; i = nex[i]) {
		if(!dfn[ver[i]]) {
			dfs(ver[i]);
			low[cur] = min(low[cur], low[ver[i]]);
		} else if(!cl[ver[i]]) {
			low[cur] = min(low[cur], dfn[ver[i]]);
		}
	}
	if(dfn[cur] == low[cur]) {
		--top;
		while(sta[top] != cur) {
			cl[sta[top]] = col;
			++num[col];
			--top;
		}
		cl[cur] = col;
		++num[col];
		++col;
	}
}

int main() {
	memset(head, -1, sizeof(head));
	int n, m, u, v, tms = 0, ans;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d %d", &u, &v);
		addedge(u, v);
	}
	for(int i = 1; i <= n; ++i) if(!dfn[i]) 
		dfs(i);
	for(int i = 0; i < tot; ++i) {
		if(cl[my[i]] != cl[ver[i]]) {
			++outd[cl[my[i]]];
		}
	}
	for(int i = 1; i < col; ++i)
		if(!outd[i]) {
			++tms;
			ans = num[i];
		}
	if(tms == 1) {
		printf("%d\n", ans);
	} else {
		printf("0\n");
	}
	return 0;	
}
```

---

## 作者：xlxl (赞：1)

## 化简题目：
## 强联通块的出度为0的为1块时，
## 输出那块的节点数

#### 扔代码：
```
#include<bits/stdc++.h>//（+缩点） 
//忘了强连通分量是什么就度娘 
using namespace std;
int n,m,x,y,cnt,tot,ans,num;
int head[10001],dfn[10001],vis[10001],zhan[10001],low[10001],s[10001],du[10001];
//tot:dfs的次数 
//cnt,zhan[cnt]:模拟栈 
//dfn[i]:i的dfs的次数 
//low[i]:i的子树中与i相连的值dfn[]最小的 
//s数组存输出 
//du[i]:i连通块的出度 
//ans:连通块个数 
struct Edge{
    int to,next;
}a[50001];
void addEdge(int from,int to){
    num++;
    a[num].to=to;
    a[num].next=head[from];
    head[from]=num;
} 
//图论基础 ，忘了就复制一下 
void tarjan(int x){
    tot++;
    cnt++;
    dfn[x]=low[x]=tot;//初始值 
    zhan[cnt]=x;//进栈 
    for(int i=head[x];i;i=a[i].next){//枚举每一条边 
        y=a[i].to; 
        if(dfn[y]==0){//如果没有访问过 
            tarjan(y);
            low[x]=min(low[x],low[y]);//不好解释见博客模拟 
            //回溯时更新low[x]，取最小值
        }
        else if(vis[y]==0){//如果访问过，但是在栈中 
            low[x]=min(low[x],dfn[y]);
        }
    } 
    if(low[x]==dfn[x]){//没有被更新 
    	ans++;
    	vis[x]=ans;
    	s[ans]++;//输出标记，ans连通块，用于输出 
        while(x!=zhan[cnt]){//x之后的全部删除(出栈) 
            s[ans]++;
            vis[zhan[cnt]]=ans; 
            cnt--; 
        } 
        cnt--;
    } 
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        addEdge(y,x);//邻接表存图,反向建边 
    }
    //日常输入 
    for(int i=1;i<=n;i++){
        if(dfn[i]==0)//如果没有访问过，访问 
            tarjan(i);
    }
    for(int i=1;i<=n;i++){
    	for(int j=head[i];j;j=a[j].next){
    		int hh=vis[a[j].to];
    		if(vis[i]!=hh){
    			du[hh]++; 
			}
		}
	} 
	cnt=0,tot=0;
	//tot存出度个数 
	//cnt存连通块内的个数 
	for(int i=1;i<=ans;i++){
		if(du[i]==0){
			cnt=s[i];
			tot++;
		}
	}
	if(tot==0)//如果所有点的出度不为0 
		cout<<n;//所有牛都是明星 
	else if(tot==1)//玄学证明 
		cout<<cnt;
		else
			cout<<0;
	//日常输出 
    return 0;
}

```
当然，为了防止抄题解，代码是不可能A的（~~其实是我没改出来~~）

#### 如果真的理解，就一定能对的

---

## 作者：贞白周逸民 (赞：1)

## 引导：

首先，我们读题可以发现到一条很重要的信息：**被所有奶牛喜欢的奶牛就是一头明星奶牛**并且**喜欢是可以传递的**。这是我们解题的关键，这时候我们就可以想，我们该怎么办？ 思考！


------------

## 思路：

1. 看到这道题有些人可能会说，这不是构建图吗？然后只需要将我们构建的图遍历一遍，观察我们构建的图，发现喜欢无非就是将两个图连在一起，这不就是强联通分量吗？

1. 只有那些被所有奶牛喜欢的强联通块才可能当明星。用Tarjan求强联通块（及将两个分开的集合通过喜欢相连成一个集合），缩点，何谓缩点？就是将一个大集合看成一个点，这里详解请看代码，求出度？当出度为0时，那么这个集合里的所有奶牛都是明星奶牛（为什么呢？自己思考下。。。很容易想到的）。时间复杂度为O(N)。

1. 这道题我是使用链式前向星来构建图的，各位可以使用  **vector** 或者 **领接表** 来也是可以的。不过链式前向星的速度回快很多（[我在这道题吃到了苦](https://www.luogu.org/problemnew/show/P3379)）。

**神奇的传送门：**

[关于Trajan算法](https://www.byvoid.com/zhs/blog/scc-tarjan)

[关于链式前向星](https://blog.csdn.net/Courage_kn/article/details/77015183)

------------

## 个人建议：
这道题请勿直接COPY代码，通过自己画图，好好地跟着自己的思维走一遍，并且深刻的理解Trajan的奥秘，你会发现图论的魅力。

**详解见代码：**

```c
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<stack>
using namespace std;
//head
//时间复杂度：O（N）
const int MAXN=200005;
int out[MAXN];
int dfn[MAXN], low[MAXN], instk[MAXN], sz[MAXN], belong[MAXN];      //tarjan模板中必备的几个数组
int p[MAXN], eid;                           //邻接表存储图
struct edge{
    int v, next;
}e[MAXN<<1];
stack<int>stk;
int n, m, x, ans, idx, scc;
void init(){
    memset(p, -1, sizeof p);
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(instk, 0, sizeof instk);
    while(stk.size()) stk.pop();
    ans=MAXN;
    eid=0;
    idx=0;
}
//连边
void insert(int u, int v){
    e[eid].v=v;
    e[eid].next=p[u];
    p[u]=eid++;
}
//tarjan模板
void tarjan(int u){
    low[u] = dfn[u] = ++idx; //记录时间戳
    instk[u]=1;             //记录一个点是否在栈中
    stk.push(u);
    for(int i=p[u]; i!=-1; i=e[i].next){
        int v=e[i].v;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u], low[v]);
        }else if(instk[v]) low[u]=min(low[u], dfn[v]);
    }
    //缩点模板 
    if(dfn[u]==low[u]){
        int cnt=0, v;
        ++scc;
        do{
            v=stk.top();
            stk.pop();
            instk[v]=0;
            cnt++;
            belong[v] = scc;            //记录每个点属于哪个强联通分量
        }while(u!=v);
        sz[scc] = cnt;      //记录该强联通分量中点的个数
    }
    
}
int main(){
    init();                     //初始化
    scanf("%d%d", &n, &m);
    for(int i=1; i<=m; ++i){
        int u, v;
        scanf("%d%d", &u, &v);
        insert(u, v);           //连边
    }
    for(int i=1; i<=n; ++i){
        if(!dfn[i]) tarjan(i);
    }
    for(int i = 1; i <= n; ++i){
        for(int j = p[i]; ~j; j = e[j].next){ // ~j 的意思是  j ！= -1 
            int v = e[j].v;
            if(belong[i] != belong[v]){
                out[belong[i]]++;           //为缩点后的强联通分量连边，记录出度
            }
        }
    }
    int ans = 0, num = 0;
    for(int i = 1; i <= scc; ++i){
        if(out[i] == 0){
            ans = sz[i];            //出度为0的强联通块中的奶牛都是明星
            num++;
        }
    }
    printf("%d\n", num == 1 ? ans : 0);        //直接输出最小的强联通中的点的数量
    return 0;
}
```

---

## 作者：vivarock (赞：1)

大佬们都用的是tarjan，标签也是

并未说是kosaraju

#但蒟蒻用kosaraju也写出来了



------------

# 思路：求取强连通分量，缩点




------------

如何求强连同分量？

[强连通分量 —Kosaraju | Tarjan | Gabow](https://juruo-oier.blog.luogu.org/qiang-lian-tong-fen-liang-kosaraju-tarjan-gabow)





还有，求出强连通分量后如何判断出度为0的点？

其实可以再第二遍dfs时，由于是逆图，所以该的出度就等于入读

利用这一点可以打出代码，还有一些细节看下方


------------

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
#define MAXV 10010
#define MAXE 50010
#define For(i,j,n) for(int i=(j);i<=(n);++i)
//宏定义
int head[MAXV],n,m,top[MAXV],topsort,rhead[MAXV],ans[MAXV],cdans[MAXV];
bool book[MAXV];
stack<int>s;
struct E{int next,to;}e[MAXE],re[MAXE];
//初始化
void dfs(int i){
	if(book[i])return ;
	book[i]=1;
	int k=head[i];
	while(e[k].to){dfs(e[k].to);k=e[k].next;}
	s.push(i);
}
//kosrarju第一遍求图的逆后续排列
void rdfs(int i){
	if(book[i])return ;
	book[i]=1;top[i]=topsort;ans[topsort]++;
	int k=rhead[i];
	while(re[k].to){
		if(top[re[k].to]!=top[i]&&book[re[k].to])cdans[top[re[k].to]]++;
		else rdfs(re[k].to);
		k=re[k].next;
	}
}
//第二遍求强连通分量+缩点+求取强连通分量的出度
int main(){
	cin>>n>>m;
	For(i,1,m){
		int a,b;
		cin>>a>>b;
		e[i].to=b;e[i].next=head[a];head[a]=i;
		re[i].to=a;re[i].next=rhead[b];rhead[b]=i;
	}
	For(i,1,n)dfs(i);
	memset(book,0,sizeof(book));
	while(!s.empty()){
		if(!book[s.top()])topsort++;
		rdfs(s.top());
		s.pop();
	}
	int ansl=0;
	For(i,1,topsort)
		if(cdans[i]==0)
			if(ansl!=0){printf("0");return 0;}
            //如果有2个出度为0的点则，不可能
			else ansl=i;
    
	cout<<ans[ansl];
	return 0;
}
```

------------


---

## 作者：陈新月 (赞：1)

思路：

题目的要求是求受欢迎的牛的数量，其实就是将题目给出的图经过缩点后求出度为0的强连通分量编号里面点的个数，在这有一些需要特判的情况，即当经缩点后出度为0的点的个数大于1时是不符合条件的（因为如果这样就不是大家都喜欢的牛了），所以这种情况应该输出0。其他地方就没有什么该注意的地方了。


下面贴出代码，重要部分已注释，有问题可以给我留言。












```cpp
#include<cstdio>
#include<algorithm>
#define N  10009
#define M  50009
using namespace std;
int en,en1,n;
struct edge{                            //前向星存边 
    int e;
    edge *next;
}*v[N],*v1[N],ed[M],ed1[M];
void add_edge(int s,int e){                //一开始的图 
    en++;
    ed[en].next = v[s],v[s] = ed+en,v[s]->e = e;
}
void add_edge1(int s,int e){            //缩点后的图 
    en1++;
    ed1[en1].next = v1[s],v1[s] = ed1+en1,v1[s]->e =e;
}
int t,cnt,low[N],dfn[N],belong[N],siz[N],out[N],sta[N],stop = 1;
bool instack[N];
void dfs(int now){                            //tarjan主过程 
    t++;
    low[now] = dfn[now] = t;
    instack[now] = true;
    sta[++stop] = now;
    for(edge *e = v[now];e;e=e->next)
      if(!dfn[e->e]){
            dfs(e->e);
            low[now] = min(low[now],low[e->e]);
      }
      else if(instack[e->e])low[now] = min(low[now],dfn[e->e]);
    if(dfn[now] == low[now]){
        cnt++;
        int si = 0;
        while(sta[stop] != now){
            int j  = sta[stop];
            belong[j] = cnt;
            instack[j] = false;
            stop--;
            si++;
        }
        si++;
        stop--;
        instack[now] = false;
        belong[now] = cnt;
        siz[cnt] = si;
    }
}
int  tarjan(){
    for(int a = 1; a <= n; a++)
       if(!dfn[a])dfs(a);
    for(int a =  1; a <= n; a++)
      for(edge *e = v[a];e;e=e->next)
        if(belong[a] != belong[e->e])                //缩点 
           add_edge1(belong[a],belong[e->e]);
    for(int a = 1; a <= cnt; a++)
      for(edge *e =v1[a];e;e=e->next)                //统计出度 
        out[a]++;
    int ans = 0,b_hao = 0;
    for(int a = 1; a<= cnt; a++)
      if(out[a] == 0){
            if(b_hao != 0){                        //当编号不为0时说明出度为0的点个数是大于1的，应直接退出循环将答案设置为0 
                ans = 0;
                break;
            }
            ans += siz[a];
            b_hao = a;
      }
    return ans;
}
int read(){                                    //读入优化 
    int x = 0;
    char ch  =getchar();
    while(ch < '0' || ch > '9')ch = getchar();
    while(ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
int main(){
    int m;
    n = read(),m = read();
    for(int a = 1;a <= m; a++){
        int u = read(),v = read();
        add_edge(u,v);                            //存图 
    }
    int ans = tarjan();
    printf("%d\n",ans);                          //输出 
    return 0;
}
```

---

## 作者：gwj12345 (赞：1)

其实就是强连通分量的模板题差不多


我要写题解啊啊啊，，楼下全部都是tarjan，没有kosaraju，我来水一发


发了那么多题解才发现luogu的markdown贴代码不能用c++要用cpp

每次都是排版不整齐qaq


```cpp
//kosaraju
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#define maxn 200010
using namespace std;
vector<int>G[maxn], rG[maxn];
vector<int>vs, cmp[maxn];
int vis[maxn], book[maxn], cnt, flag;
void dfs(int u){
    if(vis[u])return ;
    vis[u] = 1;
    for(int i = 0; i < G[u].size(); i++)dfs(G[u][i]);
    vs.push_back(u);
}
void rdfs(int u){
    if(book[u])return ;
    book[u] = cnt;
    if(!flag)cmp[cnt].push_back(u);
    for(int i = 0; i < rG[u].size(); i++)rdfs(rG[u][i]);
}
int main(){
    int n, m;   cin>>n>>m;
    for(int i = 1; i <= m; i++){
        int x, y;  cin>>x>>y;
        G[x].push_back(y);
        rG[y].push_back(x);
    }
    for(int i = 1; i <= n; i++)dfs(i);
    for(int i = n-1; i >= 0; i--){
        if(!book[vs[i]]){
            ++cnt;
            rdfs(vs[i]);
        }
    }
    flag = 1;
    memset(book, 0, sizeof book);
    rdfs(cmp[cnt][0]);
    for(int i = 1; i <= n; i++)
        if(!book[i])cmp[cnt].resize(0);
    cout<<cmp[cnt].size()<<"\n";
    return 0;
}
```


---

## 作者：NishikinoMaki (赞：1)

一上来只想出了暴力。。。

写代码40min,得了49分

然后写正解2h,各种边界、数组之类的细节处理了好久,终于A了

正解就是Tarjan加缩点，楼下dalao写得很好了

这里重点讲暴力

一个优美的暴力能帮你骗好多分~~~

暴力其实很好想

枚举各个点，如果它被所有奶牛崇拜，那就让ans++，最后输出ans

怎样知道它被哪头奶牛崇拜呢？

如果a崇拜b，由b向a指一条有向边

如果从某个点可以遍历整张图，那它就被所有奶牛崇拜

愉快的dfs好了~~~

话说某同学写了弗洛伊德的暴力只有16，可见会写优美的暴力是多么重要

暴力代码如下（会有注释）

```cpp
#include <cstdio>
using namespace std;

inline long long read()
{
    long long n = 0,k = 1;
    char ch = getchar();
    while ((ch > '9' || ch < '0') && ch != '-')  ch = getchar();
    if(ch == '-') k = -1, ch = getchar();
    while (ch <= '9' && ch >= '0')
      {
          n = n * 10 + ch - '0';
          ch = getchar();
     }
    return n * k;
}

inline void print(long long n)
{
    if(n < 0) {putchar('-'); n = -n;}
    if(n > 9) print(n / 10);
    putchar(n % 10 + '0');
    return ;
}//快读快输不解释 

int N, M, ans;
struct Edge
{
    int to, nxt;
}edge[50050];
int edge_head[10010], edge_num;//邻接表固定套路 
int vis_num[10010];//i可以遍历几个点 
bool vis[10010];//i有没有被遍历 

void add_edge(int a, int b)
{
    edge[++edge_num] = (Edge){b, edge_head[a]};
    edge_head[a] = edge_num;
    return ;
}//建边，邻接表固定套路

void dfs(int s, int root)//root记录最初的点 
{
    int p = edge_head[s];
    while(p)
    {
        int v = edge[p].to;//遍历s的下一个点 
        if(vis[v] == 0)//没被遍历 
        {
            vis[v] = 1;
            vis_num[root]++;//崇拜root的点++ 
            dfs(v, root);//接着dfs。。。实在是太裸的dfs了。。。 
            vis[v] = 0;
        }
        p = edge[p].nxt;
    }
}

bool OK(int s)//第s个点能遍历多少 
{
    for(register int i = 1; i <= N; i++)
        vis[i] = 0;//赋初值 
    vis[s] = 1;
    vis_num[s] = 1;//自己崇拜自己 
    dfs(s, s);
    if(vis_num[s] == N)//如果n个都崇拜s，s就合题意 
        return 1;
    return 0;
}

int main()
{
    N = read();
    M = read();
    for(register int i = 1; i <= M; i++)
    {
        int a = read(), b = read();
        add_edge(b, a);//反向建图 
    }
    for(register int i = 1; i <= N; i++)
        if(OK(i))
            ans++;
    print(ans);
    return 0;
}
``` 
正解如下（dalao讲的很详细了，不想细讲了，贴个代码而已）

```cpp 
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

inline long long read()
{
    long long n = 0,k = 1;
    char ch = getchar();
    while ((ch > '9' || ch < '0') && ch != '-')  ch = getchar();
    if(ch == '-') k = -1, ch = getchar();
    while (ch <= '9' && ch >= '0')
     {
          n = n * 10 + ch - '0';
          ch = getchar();
    }
    return n * k;
}

inline void print(long long n)
{
    if(n < 0) {putchar('-'); n = -n;}
    if(n > 9) print(n / 10);
    putchar(n % 10 + '0');
    return ;
}

int N, M, ans, pos;
vector <int> In[10010];
vector <int> Out[10010];
set <int> To[10010];
int DFN[10010], LOW[10010];
int Point, Time, Top;
int Stack[10010], Belong[10010], Point_num[10010];
bool instack[10010];

inline void tarjan(int u)
{
    int v;
    DFN[u] = LOW[u] = ++Time;
    Stack[++Top] = u;
    instack[u] = 1;
    int Size = In[u].size();
    for(register int i = 0; i < Size; i++)
    {
        v = In[u][i];
        if(!DFN[v])
        {
            tarjan(v);
            if(LOW[v] < LOW[u])
                LOW[u] = LOW[v];
        }
        else if(instack[v] && DFN[v] < LOW[u])
            LOW[u] = DFN[v];
    }
    if(DFN[u] == LOW[u])
    {
        Point++;
        do
        {
            v = Stack[Top--];
            instack[v] = 0;
            Belong[v] = Point;
            Point_num[Point]++;
        }while(u != v);
    }
    return ;
}

int main()
{
    N = read();
    M = read();
    for(register int i = 1; i <= M; i++)
    {
        int a = read(), b = read();
        Out[b].push_back(a);
        In[a].push_back(b);
    }
    
    for(register int i = 1; i <= N; i++)
    {
        if(In[i].empty() && Out[i].empty())
        {
            putchar('0');
            return 0;
        }    
    }
    
    for(register int i = 1; i <= N; i++)
        if(!DFN[i])
            tarjan(i);
    for(register int i = 1; i <= N; i++)//缩完点后枚举所有边，若某边的两端在不同的联通分量里，这两个分量就有一条边相连，用set建图防重边
    {
        int Size = In[i].size();
        for(register int j = 0; j < Size; j++)
        {
            int v = In[i][j];
            if(Belong[i] != Belong[v])
            {
                To[Belong[i]].insert(Belong[j]);
            }
        }
    }
    
    for(register int i = 1; i <= Point; i++)
        if(To[i].empty())
            ans++, pos = i;
    
    if(ans == 1)
        print(Point_num[pos]);
    else
        putchar('0');
    return 0;
}
```
考试时能迅速的写一个暴力才是王道~~~


---

## 作者：piggy (赞：1)

方法和前面差不多，大同小异吧，不过时间我是 11ms(或许当时提交的人少，机子跑得飞快)，感觉还挺快的，而且做题过程中也总结出了几个点，分享一下——


\* 首先就是题目中没有“明星牛”的情况，我开始没考虑，但在其它地方交了没错，在这里交了才发现了问题。说明要好好读题

\* 还有求缩完点后每个点的出边的时候，我是直接把每条已给边的端点转化成缩完的点，完了用了个 `f` 来记录出当前点外其它点是否弄过，这样的话每次都要将 `f` 清空。

\* 最慢的，你每次 memset f，我没试过，不过应该也能过吧。

\* 其次，我每次跑两遍，第一遍用来算当前点的出度 `chu[]`，第二遍把 `f` 再赋值回0，这样能保证总的时间不超过边数的两倍 (2\*m)。

\* 最后，我才想起来，其实第二次都不用跑， `f[]` 的值不一定只能为“1或0”，于是就有了我程序中那样的写法。时间为 m。

\* 的确，用第二种方法 23ms，最后那种11ms，差不多就是一半。

\* 还有一点，我不知道它的正确性，就是我发现正常的 Tarjan 模板上每次遍历后都要分两类，一个是 `!dfn[o]`，更新low[x] 用的是 `low[o]`，第二种还要判断 ·o· 是否在栈中，用 `dfn[o]` 来更新 `low[x]`，（我的o是x所能到距离为1的点）可是我一直到现在，这种只是单纯求强连通分量的题，我都没分这两类，直接用 `low[o]`  来更新，也没有判断 `o` 是否在栈中，却都没有出过错误，请教一下在单纯求强连通分量时这样做有没有错呢？


[我的博客](http://blog.csdn.net/jackypigpig/article/details/76218135)（点击即可进入，卖个广告）


附上我的代码

```cpp
#include <cstdio>
#define N 10000
#define M 50000
#define add(x,y) (to[++cnt]=head[x],head[x]=cnt,V[cnt]=y)
#define For(x) for(int h=head[x],o=V[h]; h; o=V[h=to[h]])
int head[N+5],to[M+5],V[M+5],u[M+5],v[M+5],cnt;
int F,n,m,num,ans,dep,Top,s[N+5],low[N+5],dfn[N+5],f[N+5],t[N+5],q[N+5],ru[N+5],chu[N+5];
int min(int x,int y){return x>y?y:x;}

void Tarjan(int x){
    low[x]=dfn[x]=++dep;
    q[++Top]=x;
    For(x){
        if (!dfn[o]) Tarjan(o);
        low[x]=min(low[x],low[o]);
    }
    if (dfn[x]==low[x])
        for(num++; q[Top+1]!=x; Top--) t[q[Top]]=num,s[num]++;
}

void work(){
    cnt=0;
    for (int i=1; i<=num; i++) head[i]=0;
    for (int i=1; i<=m; i++) if (t[u[i]]!=t[v[i]]) add(t[u[i]],t[v[i]]);
    for (int i=1; i<=num; i++)
        For(i) if (f[o]!=i) chu[i]++,f[o]=i; //这就是我所说的第二点中第三种方法
    for (int i=1,o=num-1; i<=num; i++)
        if (chu[i]==0) ans+=s[i],F++;
    if (F>1) ans=0;
}

int main(){
    freopen("1.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for (int i=1; i<=m; i++){
        scanf("%d%d",&u[i],&v[i]);
        add(u[i],v[i]);
    }
    for (int i=1; i<=n; i++) if (!dfn[i]) dep=0,Tarjan(i);
    work();
    printf("%d",ans);
}
```

---

## 作者：我不是柳橙汁 (赞：1)

这题是一道标准的强连通分量题，运用缩点的方法来做。 ~~其实我也花了很多时间弄懂这个瓜皮算法~~

如果**只有一个缩点**的出度为0，就可以判断该缩点内的所有奶牛均为明星奶牛

如果**有两个以上的缩点**出度为0，那说明这两个缩点互不喜欢，所以没有奶牛是明星奶牛

**最后吐槽一句，图论的题目定级为何这么高233**

···cpp


```cpp
#include<cstdio>
#include<stack>
using namespace std;
struct node{
    int next;
    int from,to;
}edge[50010];//邻接表存储有向边 
int len=0;//len表示邻接表的大小 
int n,m,sum=0;//sum是dfn的大小 
int head[10010],dfn[10010],low[10010],sin[10010],vis[10010];//head与邻接表有关，dfn是搜索的顺序，low是搜索到的点顺序的最小值，sin[x]表示x是否在栈内，vis[x]表示x是否搜索过 
int colsize,scl[10010],col[10010],ind[10010];//colsize是缩点数组的数量，scl是每个缩点的大小，col[x]表示x属于哪个缩点，ind说明col的入度 
stack <int> s;//栈 
int rin(){//标准读入优化 
    int sum=0;
    char ch=getchar();
    while (ch>'9'||ch<'0') ch=getchar();
    while (ch<='9'&&ch>='0'){
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum;
}
int fmin(int a,int b){return a<b?a:b;}//min函数 
void add(int u,int v){//增加有向边 
    edge[++len].from=u;
    edge[len].to=v;
    edge[len].next=head[u];
    head[u]=len;
}
void tarjan(int u){//tarjan算法 
    dfn[u]=low[u]=++sum;
    s.push(u);
    sin[u]=vis[u]=1;
    for (int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if (vis[v]==0){
            tarjan(v);
            low[u]=fmin(low[u],low[v]);
        }
        else if (sin[v]==1)
            low[u]=fmin(low[u],dfn[v]);
    }
    if (dfn[u]==low[u]){
        scl[col[u]=++colsize]=1; 
        while (s.top()!=u){
            scl[col[s.top()]=colsize]++;
            sin[s.top()]=0;
            s.pop();
        }
        sin[u]=0;
        s.pop();
```
}//最后处理完scl是该缩点的大小，然后栈内包括u的缩点的点退栈，col存储的是点属于哪一个缩点


```cpp
    return;
}
void inpt(){//输入处理 
    n=rin();
    m=rin();
    for (int i=1;i<=n;i++) head[i]=-1; 
    for (int i=1;i<=m;i++){
        int a=rin(),b=rin(); 
        add(b,a);//将有向边加入邻接表，但是这里边是反的方便处理出度将出度变为入度 
    }
}
void work(){//主要处理 
    for (int i=1;i<=n;i++)
        if (vis[i]==0) tarjan(i);//如果这个点没有访问过就tarjan 
    for (int i=1;i<=n;i++)
        for (int j=head[i];j!=-1;j=edge[j].next)
            if (col[i]!=col[edge[j].to]) ind[col[edge[j].to]]++;//如果这个缩点有入边就增加该缩点的入度 
}
void outp(){//输出处理 
    int ans=0;
    for (int i=1;i<=colsize;i++){ 
        if (ind[i]==0&&ans==0) ans=scl[i];//如果该缩点入度（出度）等于0并且只有一种这样的情况就代表该缩点里都是明星奶牛 
        else if(ind[i]==0) ans=-1;//否则就没有明星奶牛 
    }
    printf("%d\n",ans==-1?0:ans);
}
int main(){
    inpt();
    work();
    outp();
    return 0;
}
···
```

---

## 作者：Kwork (赞：1)

这里给他家介绍一种玄学算法，说是玄学其实也不算，有依据。

---下面是题意简析--------------------

给你一个有向图，请你求出可以满足条件的点的个数。条件：从除自己外任意一点出发可以到达自己。

---下面是算法分析--------------------

首先我们对图缩点得到DAG，那么，满足条件的连通分量一定是在DAG的拓扑序的末端。知道这一点我们我们只需要将DAG的逆向图从拓扑序末端的点向起点做一遍dfs，如果存在无法到达的点，那么输出0，否则输出末端表示的强连通分量中点的数量。

--- **普及小的技巧** ----------------------

用tarjan或者(dfs+rdfs)算法分解强连通分量，得到强连通分量序号，是按照拓扑序或者拓扑的倒序，所以我们在O(1)时间内得到了强连通分量的末端。

-----------------------------------------------------------------------------------------------------------------------------





```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;
const int maxn=10000+20;
vector<int>G[maxn];
vector<int>graph[maxn];
int n,m,in_degree[maxn];
int dfn[maxn],low[maxn],cmp[maxn],ins[maxn],s[maxn],cnt=0,Index=0,top=0;
inline void read(int &n){
    n=0;int f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    do{
        n=n*10+ch-'0';
        ch=getchar();
    }while(ch>='0' && ch<='9');
    n=n*f;
    return;
}
inline void write(int n){
    if(n<0){
        putchar('-');
        n=0-n;
    }
    if(n>=10) write(n/10);
    putchar((n % 10)+'0');
    return;
}
inline void add_edge(int u,int v){
    G[u].push_back(v);
    return;
}
void init(){
    read(n),read(m);
    for(int i=0;i<m;i++){
        int u,v;
        read(u),read(v);
        add_edge(u,v);
    }
    return;
}
void tarjan(int u){
    ins[u]=1;
    s[top++]=u;
    dfn[u]=low[u]=++Index;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else{
            if(ins[v])
                low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        cnt++;
        int i;
        do{
            i=s[--top];
            ins[i]=0;
            cmp[i]=cnt;
        }while(i!=u);
    }
    return;
}
void scc(){
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(ins,0,sizeof(ins));
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    return;
}
inline void add_new_edge(int u,int v){
    graph[u].push_back(v);
    return;
}
void build_new_graph(){
    for(int u=1;u<=n;u++){
        for(int i=0;i<G[u].size();i++){
            int v=G[u][i];
            if(cmp[u]!=cmp[v]){
                add_new_edge(cmp[v],cmp[u]);
                //++in_degree[cmp[v]];
            }
        }
    }
    return;
}
void test(){
    for(int i=1;i<=n;i++){
        write(i);
        putchar(':');
        write(cmp[i]);
        putchar('\n');
    }
    return;
}
void dfs(int u){
    ins[u]=1;
    for(int i=0;i<graph[u].size();i++){
        int v=graph[u][i];
        if(!ins[v]){
            dfs(v);
        }
    }
    return;
}
void work(){
    memset(ins,0,sizeof(ins));
    dfs(1);
    for(int i=1;i<=cnt;i++){
        if(!ins[i]){
            write(0);
            return;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(cmp[i]==1) ++ans;
    write(ans);
    return;
}
void solve(){
    scc();
    build_new_graph();
    //test();
    work();
    return;
}
int main(){
    init();
    solve();
    return 0;
}

```

---

## 作者：Paranoid丶离殇 (赞：1)

## **题目背景**

本题测试数据已修复。

## **题目描述**

每头奶牛都梦想成为牛棚里的明星。被所有奶牛喜欢的奶牛就是一头明星奶牛。所有奶

牛都是自恋狂，每头奶牛总是喜欢自己的。奶牛之间的“喜欢”是可以传递的——如果A喜

欢B，B喜欢C，那么A也喜欢C。牛栏里共有N 头奶牛，给定一些奶牛之间的爱慕关系，请你

算出有多少头奶牛可以当明星。

**输入格式：**

 第一行：两个用空格分开的整数：N和M

 第二行到第M + 1行：每行两个用空格分开的整数：A和B，表示A喜欢B

 **输出格式：**

 第一行：单独一个整数，表示明星奶牛的数量

**输入样例**

```
3 3
1 2
2 1
2 3
```

**输出样例**

```
1 
```

## **说明**

只有 3 号奶牛可以做明星

**【数据范围】**

10%的数据N<=20, M<=50

30%的数据N<=1000,M<=20000

70%的数据N<=5000,M<=50000

100%的数据N<=10000,M<=50000

**题解：**

本题利用结论：在DAG中， 如果 **有且仅有** 一个点的出度为0 ，那么该点可以被所有点遍历到；反之，该图中没有可以被所有点遍历到的点。

至于证明，我不会 利用用反证法证明；

```cpp
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;
const int N = 1e4 + 5;
int n, m, ans;
struct edge { int to, nxt; } e[50005];
int cnt, head[N], chu[N], size[N];
void add(int from, int to) {
    e[++ cnt].to = to;
    e[cnt].nxt = head[from];
    head[from] = cnt;
}
stack <int> s;
int dfn[N], low[N], tot, scc, tar[N];
void tarjan(int x) {
    dfn[x] = low[x] = ++ tot;
    s.push(x);
    for(int i = head[x]; i ;i = e[i].nxt) {
        int to = e[i].to;
        if(! dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        }
        else if(! tar[to])
            low[x] = min(low[x], dfn[to]);
    }
    if(dfn[x] == low[x]) {
        scc ++;
        while(1) {
            int y = s.top(); s.pop();
            tar[y] = scc; size[scc] ++;
            if(y == x) break;
        };
    }
}
int main() {
    cin >> n >> m;
    for(int i = 1, x, y;i <= m;i ++) cin >> x >> y, add(x, y);
    for(int i = 1;i <= n;i ++) if(! low[i]) tarjan(i);
     for(int x = 1;x <= n;x ++) {
        for(int i = head[x]; i ;i = e[i].nxt) {
            int y = e[i].to;
            if(tar[x] == tar[y]) continue;
            chu[tar[x]] ++;
        }
    }
    for(int i = 1;i <= scc;i ++) {
        if(chu[i] == 0) {
            if(ans) { ans = 0; break; }
            ans += size[i];
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：yang23 (赞：1)

最受欢迎的牛








```cpp
#include<bits/stdc++.h>
using namespace std;
int dfn[10010],low[10010],head[10010],ans[10010],instack[10010],cnt,L,S,n,m,aa,bb;
int vis[10010],vis1[10010],vis2[10010],sum[10010],num[10010],tmp;
stack<int> a;
struct Edge{
    int to,next;
}edge[50010];
void add(int u,int v){
    edge[++cnt]=(Edge){v,head[u]};
    head[u]=cnt;
}
void tarjan(int u){
    dfn[u]=low[u]=++L;
    vis[u]=instack[u]=1,a.push(u);
    for(int k=head[u];k;k=edge[k].next){
        int v=edge[k].to;
        if(!vis[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if(instack[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]) {
        S++;
        while(a.top()!=u) ans[a.top()]=S,sum[S]++,instack[a.top()]=0,a.pop();
        ans[u]=S,sum[S]++,instack[u]=0,a.pop();
    }
}
void go(int n,int m){
    vis[n]=1;
    if((ans[n]!=m)&&(!vis2[ans[n]])) num[ans[n]]++,vis2[ans[n]]=1;
    for(int k=head[n];k;k=edge[k].next){
        int v=edge[k].to;
        if(!vis[v]) go(v,m);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&aa,&bb),add(aa,bb);
    for(int i=1;i<=n;i++) if(!vis[i]) tarjan(i);
    for(int i=1;i<=n;i++) if(!vis1[ans[i]]){     
        memset(vis,0,sizeof(vis));
        memset(vis2,0,sizeof(vis2));
        go(i,ans[i]);
        vis1[ans[i]]=1;
    }
    for(int i=1;i<=n;i++) if(num[ans[i]]==S-1) {
        printf("%d",sum[ans[i]]);
        return 0;
    }
    puts("0");
}
```
可爱牛牛们貌似又不安分了，摇身一变又来使善良的OIer们GG了。

正经的题解从这里开始：


1.建图：


一看数据，就要用到链式前项星（虽然本人特别反感）


2.求连通块（专业的人说是强联通分量）


不少人GG在应该以哪个点为根节点


本人果断暴力，以任意节点为根，做Tarjan


然后用ans[i]存储联通情况，即编号为i（这里用dfs序作为点的编号）的点属于第ans[i]个连通块


同时用sum[j]表示编号为j的连通块共包含sum[j]个节点


3.统计答案


很容易知道答案是联通所有连通块的连通块（好吧有点绕）所包含的节点个数，容易想到再做一次dfs(即go函数）


具体操作是：


定义num数组，用num[r]表示第r个连通块可以连通的异于它本身连通块的数量


先锁定一个节点的连通块（v)，然后遍历这个节点所联通的节点，如果发现可以到达另外的连通块


注意：

num[新节点的连块编号]++;

不是num[已锁定连通块编号]++;

完成这一步之后，只需遍历每个连通块的num，直到找到一个num[i]==S(连通块总数）-1，输出sum[i]，可以直接结束程序。


然后补一句输出0，就完美了


---

## 作者：maple_tzc (赞：1)

差不多都是trajan吧，这道题套模板，就可以过，但还是WA了几遍，，写这种题一定要小心小心再小心，坑，一个字母的错，坑了我5次，

世界上最遥远的距离是，明明两个程序那么像，一个A了，一个WA了




```cpp
#include <cstdio>
#include<iostream> 
#include <algorithm>
using namespace std;
const int maxn=10010,maxm=50050;
struct {
    int s,e,next;//建立目录，开始，结束和上一个；
} v[maxm];//使v这个数组能动用这个目录；
int n,m,ans,group,cnt,top,total;
int belong[maxn],du[maxn],first[maxn],dfn[maxn],low[maxn],st[maxn];
inline int Get() {
    char c=getchar();
    int res=0;
    while ((c<'0')||('9'<c)) c=getchar();
    while (('0'<=c)&&(c<='9')) res=res*10+(int)(c-'0'),c=getchar();
    return res;
}
void Tarjan(int k) {
    dfn[k]=++cnt; //标号自加； 第i个点；
    low[k]=cnt; //把标号给离自己最近的数 ；
    st[++top]=k;//i的标号给st【i】；
    int ttt=top;//标号自加；
    for (int p=first[k]; p; p=v[p].next)  //不断去寻找自己的上一个直到找不到为止；
        if (!belong[v[p].e]) 
        { //如果标号当中的某一点p的结束点的值在出度的标号为0；
            if (!dfn[v[p].e]) Tarjan(v[p].e);//如果dfn，p结束点的标号为0；就再去以这个点去寻找另一个点；
            low[k]=min(low[k],low[v[p].e]);//把这个阶段的值全部赋值给最近的标号；
        }
    if (dfn[k]==low[k]) {//如果我的最近的最前面的标号与我目前的点的标号相等就说明一定是有自环了
        ++total;//数量加一；
        for (int i=ttt; i<=top; ++i) { //数出到底有多少个连续的low【k】
            belong[st[i]]=total;
        }
        top=ttt-1;
    }
}
int main() {
    n=Get();//输入牛的个数
    m=Get();//输入边的个数
    for (int i=1; i<=m; ++i) {
        v[i].s=Get();//输入开始点
        v[i].e=Get();//输入结束点
        v[i].next=first[v[i].s];//把上一个得值改变成现在这个的值，使他成为下一个的上一个；
        first[v[i].s]=i;//把目前的标号给first，代表的是上一个的编号是多少；
    }
    for (int i=1; i<=n; ++i)
        if (!belong[i])  //判断一下这个出度是不是为0，不为0的话 就开始tarjan；这个还不熟悉； 
            Tarjan(i);      //从每一个点开始遍历；
    for (int i=1; i<=m; ++i)// 枚举边；
        if (belong[v[i].s]!=belong[v[i].e])// 如果我结束点的和自己的开始点相同就说明这是个自环
            ++du[belong[v[i].s]];//那么du的这个标号就得加1； 
    for (int i=1; i<=total; ++i)
        if (!du[i]) ++ans,group=i;//如果du的i为0，ans就加一，记录这个编号， 
    if (ans!=1) printf("0\n");//ans不是为一，也有可能有多个数，就输出0因为一个图里不可能出现多个出度为0的点； 
    else {
        ans=0; 
        for (int i=1; i<=n; ++i)
            if (belong[i]==group) ++ans;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：abandentsky (赞：0)

题意：如果所有的点都能到达这个点就计数加一。这样我们就可以使用tarjain算法求出强连通分量。缩点以后不用重新建图，直接进行统计。当且仅当出度唯0的点有一个时，有解。没有解直接输出0，如果有解我们找到这个强连通分量然后看看这个强连通分量里有几个点就好了。
```c
#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<iostream>
#define MAXN 10005
#define INF 0x3f3f3f3f
using namespace std;

struct Edge
{
    int from,to;
    Edge(int from=0,int to=0):from(from),to(to){};
};
vector<Edge> edges;
vector<int> G[MAXN];
//vector<Edge> mmp;                //重新构图
//vector<int> Map[MAXN];     //重新建图
stack<int> S;
int pre[MAXN],sccno[MAXN],lowlink[MAXN],out[MAXN];
int dfs_clock,scc_cnt;
int n,m;

void dfs(int u)
{
    S.push(u);
    pre[u]=lowlink[u]=++dfs_clock;
    for(int i=0;i<G[u].size();i++)
    {
        Edge &e=edges[G[u][i]];
        int v=e.to;
        if(!pre[v])
        {
            dfs(v);
            lowlink[u]=min(lowlink[u],lowlink[v]);
        }
        else if(!sccno[v])
        {
            lowlink[u]=min(lowlink[u],pre[v]);
        }
    }
    if(pre[u]==lowlink[u])
    {
        ++scc_cnt;
        for(;;)
        {
            int x=S.top();
            S.pop();
            sccno[x]=scc_cnt;
            if(u==x)
                break;
        }
    }
}

void Find_Scc(int n)
{
    scc_cnt=dfs_clock=0;
    memset(sccno,0,sizeof(sccno));
    memset(pre,0,sizeof(pre));
    memset(out,0,sizeof(out));              //用来统计缩点后的出度
    for(int i=1;i<=n;i++)
    {
        if(!pre[i])
           dfs(i);
    }
    for(int i=0;i<edges.size();i++)
    {
        int xx=edges[i].from;
        int yy=edges[i].to;
        if(sccno[xx]!=sccno[yy])
        {
            out[sccno[xx]]++;                          //出度加一
            //mmp.push_back({sccno[xx],sccno[yy]});
            //printf("test:%d->%d %d\n",sccno[xx],sccno[yy],edges[i].dist);
            //int mm=mmp.size();
            //Map[sccno[xx]].push_back(mm-1);
        }
    }
    int sum=0;
    int pos;
    for(int i=1;i<=scc_cnt;i++)
        if(out[i]==0)
        {
            sum++;
            pos=i;                         //判定是哪个强连通分量
        }
    if(sum==1)
    {
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            if(sccno[i]==pos)     //是这个强连通分量（出度为0)就加一
                cnt++;
        }
        printf("%d\n",cnt);
    }
    else
    {
        printf("%d\n",0);
    }
}


int main()
{
    scanf("%d %d",&n,&m);
    int u,v;
    for(int i=0;i<m;i++)
    {
        scanf("%d %d",&u,&v);
        if(u==v)
            continue;
        edges.push_back({u,v});
        int mm=edges.size();
        G[u].push_back(mm-1);
    }
    Find_Scc(n);
    return 0;
}

```


---

## 作者：FC_Barcelona (赞：0)

 ###   _一个挺裸的tarjan缩点呀QAQ_ 

我们可以将每个强连通分量缩成一个点，这样就能得到一个有向无环图。

考虑图中这些点的出度：如果一个点u出度不为零，说明它至少连向一个点，而它与相连的点v显然不是强联通的，也就是说不是所有牛都喜欢u。所以我们只需要找出唯一的出度为零的点（如果有多个出度为0的点，当然就没有明星奶牛啦）

~~然后，，，然后就AC了呀QAQ~~

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>          //vector存边
using namespace std;
vector <int> edge[10005];
queue <int> q;
int n,m,u,v,step,top,cnt,stack[10005],vis[10005],dfn[10005],low[10005];
int belong[10005],outde[10005],sum[10005],ans;
inline int read()
{
	int num=0;
	char ch=getchar();
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9')
	{
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar();
	}
	return num;
}
inline void tarjan(int u)
{
	dfn[u]=low[u]=++step;
	stack[++top]=u;
	for (int i=0;i<edge[u].size();i++)
	{
		int v=edge[u][i];
		if (!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if (!vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]==low[u])
	{
		cnt++;
		for (top;(v=stack[top])!=u;top--)
		{
			belong[v]=cnt;
			vis[v]=1;
			sum[cnt]++;
		}
		top--;
		belong[u]=cnt;
		vis[u]=1;
		sum[cnt]++;
	}
}
inline void shrink()
{
	for (int i=1;i<=n;i++)
	    for (int j=0;j<edge[i].size();j++)
	    {
	    	int v=edge[i][j];
	    	if (belong[i]!=belong[v]) outde[belong[i]]++; 
	    }
}
int main()
{
	n=read();
	m=read();
	for (int i=1;i<=m;i++)
	{
		u=read();
		v=read();
		edge[u].push_back(v);
	}
	for (int i=1;i<=n;i++)
        if (!dfn[i]) tarjan(i);  //tarjan大家应该会吧，几位大佬讲得挺详细的
	shrink();        //缩点
	for (int i=1;i<=cnt;i++)
	    if (!outde[i])
	    {
	    	if (ans)
	    	{
	    		printf("0");
	    		return 0;
	    	}
	    	ans=sum[i];
	    }
	printf("%d",ans);
}
```


---

## 作者：EmpyreanCz (赞：0)

今天学了强连通分量的Tarjan算法，做了这道类似于板子题的题（尽管我调了

1.5h）。主要的思路是用Tarjan缩点之后，求每个点的入度（实际上是出度，

因为我是反着连边的）。如果有且只有一个点的入度大于零，那个强连通分

量里有的点的个数就是答案。具体实现见代码：


### 注释版代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 10010
#define maxm 50010
using namespace std;
int dfn[maxn],low[maxn],st[maxn],inn[maxn],head[maxm];
int de[maxn],si[maxn];
int n,m,cnt,top,inl,num;
struct node
{
	int u,v,nex;
}edge[maxm];
inline int read() 
{
    int x=0;
    bool f=1;
    char c=getchar();
    for(; !isdigit(c); c=getchar()) if(c=='-') f=0;
    for(; isdigit(c); c=getchar()) x=(x<<3)+(x<<1)+c-'0';
    if(f) return x;
    return 0-x;
}
inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
inline void add(int x,int y)
{
	cnt++;
	edge[cnt].u=x;
	edge[cnt].v=y;
	edge[cnt].nex=head[x];
	head[x]=cnt;
}
inline void Tarjan(int from)//用Tarjan缩点 
{
	dfn[from]=low[from]=++num;
	st[++top]=from;
	for(int i=head[from];i!=-1;i=edge[i].nex)
	{
		int to=edge[i].v;
		if(!dfn[to])
		{
			Tarjan(to);
			low[from]=min(low[from],low[to]);
		}
		else if(!inn[to])
		    low[from]=min(low[from],dfn[to]);
	}
	if(low[from]==dfn[from])
	{
		inn[from]=++inl;
		++si[inl];//记录每个强连通分量里有多少个点 
		while(st[top]!=from)
		{
			++si[inl];//同上 
			inn[st[top]]=inl;
			--top;
		}
		--top;
	}
}
int main()
{
	memset(head,-1,sizeof(head));
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=read();y=read();
		add(y,x);//反着连边，这样就可以求入度而不是出度了 
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
		    Tarjan(i);//缩点 
	for(int i=1;i<=n;i++)
	   for(int j=head[i];j!=-1;j=edge[j].nex)
	       if(inn[i]!=inn[edge[j].v]) de[inn[edge[j].v]]++;//更新入度 
	int ans=0,u=0;
	for(int i=1;i<=inl;i++)
	{
		if(!de[i])//如果入度大于零 
		{
			ans=si[i];//赋值 
			u++;//记录有几个点符合条件 
		}
	}
	if(u==1)//判断是否有且仅有一个入度大于零的点 
	    write(ans);
	else 
	    write(0);//否则输出无解 
	return 0;
}
/*
9 12
1 2
2 4
4 5
5 3
3 2
1 6
6 9
9 5
6 8
8 7
8 9
7 6
*/
//一组很不错的数据，可以试试 
```

### 正常版

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 10010
#define maxm 50010
using namespace std;
int dfn[maxn],low[maxn],st[maxn],inn[maxn],head[maxm];
int de[maxn],si[maxn];
int n,m,cnt,top,inl,num;
struct node
{
    int u,v,nex;
}edge[maxm];
inline int read() 
{
    int x=0;
    bool f=1;
    char c=getchar();
    for(; !isdigit(c); c=getchar()) if(c=='-') f=0;
    for(; isdigit(c); c=getchar()) x=(x<<3)+(x<<1)+c-'0';
    if(f) return x;
    return 0-x;
}
inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
inline void add(int x,int y)
{
    cnt++;
    edge[cnt].u=x;
    edge[cnt].v=y;
    edge[cnt].nex=head[x];
    head[x]=cnt;
}
inline void Tarjan(int from)
{
    dfn[from]=low[from]=++num;
    st[++top]=from;
    for(int i=head[from];i!=-1;i=edge[i].nex)
    {
        int to=edge[i].v;
        if(!dfn[to])
        {
            Tarjan(to);
            low[from]=min(low[from],low[to]);
        }
        else if(!inn[to])
            low[from]=min(low[from],dfn[to]);
    }
    if(low[from]==dfn[from])
    {
        inn[from]=++inl;
        ++si[inl];
        while(st[top]!=from)
        {
            ++si[inl];
            inn[st[top]]=inl;
            --top;
        }
        --top;
    }
}
int main()
{
    memset(head,-1,sizeof(head));
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        int x,y;
        x=read();y=read();
        add(y,x);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            Tarjan(i);
    for(int i=1;i<=n;i++)
       for(int j=head[i];j!=-1;j=edge[j].nex)
           if(inn[i]!=inn[edge[j].v]) de[inn[edge[j].v]]++;
    int ans=0,u=0;
    for(int i=1;i<=inl;i++)
    {
        if(!de[i])
        {
            ans=si[i];
            u++;
        }
    }
    if(u==1)
        write(ans);
    else 
        write(0);
    return 0;
}
```

请各位大佬斧正~~（反正我不认识斧正是什么意思）~~

---

## 作者：碎星小左轮 (赞：0)

萌新的第一篇题解 tarjan例题

如果牛A喜欢牛B，我们就连一条A到B的有向边
然后使用tarjan缩点，将原图变为DAG。**（然而并不用建新图）**

显而易见得：一头牛被所有的牛喜欢时，那么在新建的DAG上，有且仅有那头牛所在的强联通分量的出度为0，且此时那头牛所在的强连通分量都是明星。

**注意：如果DAG上存在超过一个出度为0的点，那么这两个点上的牛无法将自己的喜欢传递出去，答案是0。**


剩下的就是tarjan板子了...
~~然而还是错了两次~~

## 上代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m;
const int maxn = 10010;
const int maxm = 50010;
struct edge{
	int to, nt;
	inline void set(int n, int t){
		to = t, nt = n;
	}
}e1[maxm], e2[maxm];//然后发现并不用连缩点之后的图。。。
int t1, t2, h1[maxn], h2[maxn];
int adde1(int a, int b){
	e1[++t1].set(h1[a], b);
	h1[a] = t1;
}
int adde2(int a, int b){
	e2[++t2].set(h2[a], b);
	h2[a] = t2;
}

int vis[maxn], dfn[maxn], low[maxn], bel[maxn], num[maxn], stc[maxn], top, cnt, cc;
void tarjan(int now, int pre){//标准tarjan过程
	vis[now] = 1;
	dfn[now] = low[now] = ++cnt;
	stc[++top] = now;
	for(int i = h1[now]; i; i = e1[i].nt){
		int nex = e1[i].to;
		if(!dfn[nex]){
			tarjan(nex, now);
			low[now] = min(low[nex], low[now]);
		}
		else if(vis[nex]){
			low[now] = min(low[nex], low[now]);
		}
	}
	if(dfn[now] == low[now]){
		int tmp;
		++cc;
		do{
			tmp = stc[top--];
			vis[tmp] = 0;
			bel[tmp] = cc;
			num[cc]++;
		}while(top > 0 && tmp != now);
	}
	return ;
}
int du[maxn];
void rebuild(){//查找出度为0的点
	for(int i = 1; i <= n; ++i){
		for(int j = h1[i]; j; j = e1[j].nt){
			int k = e1[j].to;
			//cout<<i<< " "<<k<<endl;
			int bi = bel[i], bj = bel[k];
			//cout<<bi<< " "<<bj<<endl;
			if(bi != bj){
				//adde2(bi, bj);
				du[bi]++;
			}
		}
	}
	return ;
}
void check(){
	/*for(int i = 1; i <= n; ++i){
		cout<<i<< " "<<bel[i]<<endl;
	}*/
	int ans = 0, flag = 0;
	for(int i = 1; i <= cc; ++i){
		//cout<<du[i]<<endl;
		if(du[i] == 0)flag++, ans = num[i];
	}
	if(flag == 1)cout<<ans<<endl;
	else cout<<0<<endl;
	return;
}
int main(){
	scanf("%d%d", &n, &m);
	int x, y;
	for(int i = 1; i <= m; ++i){
		scanf("%d%d", &x, &y);
		adde1(x, y);
	}
	for(int i = 1; i <= n; ++i){
		if(!dfn[i])tarjan(i, 0);
	}
	rebuild();
	check();
	return 0;
}
```

---

## 作者：蒟蒻初音ミク (赞：0)

其实就是一道找强连通分量的一道水题。和P3387没有多大的区别。

但是这么水为什么还是提高+/省选-呢？？？~~因为那时候的题都这么垃圾~~

好，进入正题。首先求出所有的强连通分量，并且维护好他们的信息，这个很简单，直接看代码。（以下我把强连通分量成为缩点后的“大点”，比较形象）

````cpp
for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
```

```cpp
void tarjan(int u)
{
	low[u]=dfn[u]=++t;instack[u]=1;s.push(u);
	int v;
	for(int i=head[u];i;i=edge[i].next)
	{
		v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(instack[v])low[u]=min(low[u],low[v]);
	}
	if(low[u]==dfn[u])
	{
		ans++;//缩点之后的大点数量+1
		member[ans]=0;
		while(s.top()!=u)
		{
			id[s.top()]=ans;
			instack[s.top()]=0;
			member[ans]++;
			s.pop();
		}
		id[s.top()]=ans;
		instack[s.top()]=0;
		member[ans]++;
		s.pop();
	}
}
```

可能有些朋友要问了：里面的member数组拿来干嘛啊？算成员数啊？本题明明就是求明星牛的数量啊！

好，这就是本题的难点了——如何判断一个大点能否当明星。

大家可以先把样例画成一个图，就在草稿纸上。然后会发现——1结点和2结点可以合并成一个大点，且3号结点自己就是一个大点。然后又会发现，3号结点没有爱慕的结点了，于是统计一下，输出1。

过程就是这么简单，但是我们推出了一个至关重要的结论——**最后那个没有出度的大点里的成员，都是明星牛（因为其它的牛都爱慕它们，而它们不爱慕任何牛）！！！**

但是又有老铁要问了~~（有那么多老铁吗~~）~~：如果有一个大点不喜欢其它任何的点，且没有一个大点喜欢它呢？

所以，不是所有的无出度的大点都是明星~~（不是所有的牛奶都叫特仑苏）~~

判断条件呢，咳咳~~，看代码吧——

```
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<stack>
#include<queue>
#include<iostream>
#include<algorithm>
#define N 10000
#define M 50000
using namespace std;
struct ed{//邻接表存储 
	int to,next;
}edge[M+10];
struct bian{//存储每一条边的信息 
	int u,v;
}e[M+10];
int n,m,head[N+10],k=0,dfn[N+10],low[N+10],t=0,ans=0,du[N+10],cnt=0;
//先不要管这些变量表示什么，也不要管这些自定义函数，直接看主函数，你就懂了 
bool instack[N+10];
int member[N+10],id[N+10];//member表示大点的成员数量，id表示该小点属于的大点 
stack<int>s;
void add(int u,int v)
{
	edge[++k].to=v;
	edge[k].next=head[u];
	head[u]=k;
}
void tarjan(int u)
{
	low[u]=dfn[u]=++t;instack[u]=1;s.push(u);//入栈，要标记一下 
	int v;
	for(int i=head[u];i;i=edge[i].next)
	{
		v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(instack[v])low[u]=min(low[u],low[v]);
	}//标准tarjan 
	if(low[u]==dfn[u])
	{
		ans++;//缩点之后的大点数量+1
		member[ans]=0;
		while(s.top()!=u)
		{
			id[s.top()]=ans;
			instack[s.top()]=0;
			member[ans]++;//这个大点里的成员数+1 
			s.pop();
		}
		id[s.top()]=ans;
		instack[s.top()]=0;
		member[ans]++;
		s.pop();
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	int x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		e[i].u=x;e[i].v=y;
		add(x,y);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=m;i++)
	if(id[e[i].u]!=id[e[i].v])du[id[e[i].u]]++;//计算新的大点的度 
	int temp=0;
	for(int i=1;i<=ans;i++)
	{
		if(du[i]==0)
		{
			if(temp==0)temp=i;
			else{printf("0");return 0;}//如果无出度的大点不止一个，则无解 
		}
	}
	printf("%d",member[temp]);
	return 0;
}
```

---

## 作者：L_M_ (赞：0)

~~我要疯了

d了两个小时，结果因为v=e[j].next写成v=e[i].next只拿七十分（为什么我还能玄学般地拿七十分？？？？）~~

看完题之后能想到tarjan缩点，我们来考虑考虑缩完之后的情况

缩点之后，整个图就是一个DAG，我们要找能被所有奶牛喜欢的点（一群牛），就是要找一个出度为0的点，输出其中牛的数量即可

为什么要出度为0？可以反证：如果一个点u出度不为0，设这个点到v有一条边。因为缩点之后图中不存在环，故不存在从v到u的路径，即u不可能被v喜欢

如果同时有两个出度为0的点a,b，a是不可能喜欢b的，这种情况下也无解

统计出度比较麻烦，我们可以反向建边，统计入度**

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e5+5;
struct edge
{
	int to,next;
}e[5*maxn];
bool instack[maxn];
int fir[maxn],alloc;
void adde(int u,int v)
{
	e[++alloc].next=fir[u];
	fir[u]=alloc;
	e[alloc].to=v;
}
int st[maxn],id[maxn],dfn[maxn],low[maxn],in[maxn],num[maxn],tim=0,top=0,cnt=0;
void tarjan(int u)
{
	dfn[u]=low[u]=++tim;
	st[++top]=u;
	instack[u]=1;
	for(int i=fir[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(instack[v]) low[u]=min(low[u],dfn[v]);
	}
		if(low[u]==dfn[u])
		{
			id[u]=++cnt;
			num[cnt]++;
			while(st[top]!=u)
			{
				id[st[top]]=cnt;
				instack[st[top]]=0;
				top--;
				num[cnt]++;
			}
			instack[u]=0;
			top--;
		}
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)   
	{
		int u,v;
		scanf("%d%d",&u,&v);
		adde(v,u);//反向建边
	} 
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++)
		for(int j=fir[i];j;j=e[j].next)
		{
			int v=e[j].to;
			if(id[i]!=id[v]) in[id[v]]++;
		}
	int ans=0,flag=0;
	for(int i=1;i<=cnt;i++)
		if(!in[i]) { ans=num[i]; flag++;} 
	if(flag==1) printf("%d\n",ans);
	else printf("0");
}
	
		
			
```

---

## 作者：睿屿青衫 (赞：0)

#卡了两个半小时，（floyd半小时+不熟的tarjan2小时）

#你们是不是不太理解为什么会用floyd？其实做之前我先看了看数据范围，显然弗洛伊德40分左右，但今年就要退役了，部分分还是要拿一拿的，tarjan代码楼下很多，加上我也不熟，就不多说，大家主要还是看一看我的floyd（学长去年并查集32分你们也看一下思路）

#数据还是有点水的，提交了一遍tarjan41分，发现忘记调用tarjan(v)了，详看代码

##floyd代码（50当然如果你们再适当提高那么一点点maxn的大小，再过一个点也说不定）

###循环一次，自己喜欢自己，再输入更新喜欢的，一遍弗洛伊德更新题意（A喜欢B，B喜欢C，那么A喜欢C），然后枚举，如果有不连通的，答案（初始化为n）减一，枚举完输出

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 3000
using namespace std;
int n,m,f[maxn][maxn],ans;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;ans=n;
    for(int i=1;i<=m;++i)
     {
         int a,b;
         cin>>a>>b;
         f[a][b]=1;
     }
    for(int i=1;i<=n;++i)
     f[i][i]=1;
    for(int k=1;k<=n;++k)
     for(int i=1;i<=n;++i)
      for(int j=1;j<=n;++j)
       if(f[i][k]&&f[k][j])
        f[i][j]=1;
    for(int i=1;i<=n;++i)
     for(int j=1;j<=n;++j)
      {
          if(!f[j][i])
           {
           ans--;break;
           }
      }
    printf("%d",ans);
    return 0;
}
```
##tarjan
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 2000000
using namespace std;
int stack[maxn],qr,rq,top,tot,dfn[maxn],low[maxn],ans[maxn];
int n,m,head[maxn],vis[maxn],num,color[maxn],c[maxn],maxx;
struct EDGE
{
    int from;
    int next;
    int to;
}edge[maxn*3];
void add(int from,int to)
{
    edge[++qr].next=head[from];
    edge[qr].from=from;
    edge[qr].to=to;
    head[from]=qr;
}
void tarjan(int x)
{
    low[x]=dfn[x]=++rq;
    vis[x]=1;stack[++top]=x;
    for(int i=head[x];i;i=edge[i].next)
     {
         int v=edge[i].to;
         if(!dfn[v])
          {
              tarjan(v);
              low[x]=min(low[x],low[v]);
          }
        else if(vis[v])
         low[x]=min(low[x],dfn[v]);
     }
    if(dfn[x]==low[x])
     {
         vis[x]=0;
         tot++;
         color[x]=tot;
         while(stack[top+1]!=x)
          {
              vis[stack[top]]=0;
              color[stack[top]]=tot;
              ans[tot]++;
              top--;
          }
     }
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=m;++i)
     {
         int a,b;
         cin>>a>>b;
         add(a,b);
     }
    for(int i=1;i<=n;++i)
     if(!dfn[i]) tarjan(i);
    for(int i=1;i<=qr;++i)
     if(color[edge[i].from]!=color[edge[i].to])
      c[color[edge[i].from]]++;
    for(int i=1;i<=tot;++i)
     if(!c[i])
      num++,maxx=ans[i];
    if(num==1)
     {
         printf("%d",maxx);
         return 0;
     }
    else printf("0");
    return 0;
}
```
##学长的并查集
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,m,f[23333];
int find(int x)
{
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}
void merge(int x,int y)
{
    int a=find(x);
    int b=find(y);
    if(a!=b) f[x]=y;
}
int main()
{
    scanf("%d%d",&n,&m);
    int ans=0;
    for(int i=1;i<=n;i++)
     f[i]=i;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        merge(x,y);
    }
    for(int i=1;i<=n;i++)
    if(f[i]==i) ans++;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：QwQ_operator (赞：0)

思路：来自我的博客：http://www.cnblogs.com/z360/p/7044446.html

这道题和刻录光盘的思路是一样的，我们先找这个图中的强连通分量，然后缩点，然后判断出读为0的点的个数。

我们可以这样想：如果一个点的出度为零，这样的话这个点是不是一定不会喜欢别的牛？！

【在这往后提的每个牛的出度均为缩点后的出度】

如果有两个（及两个以上）的牛都不喜欢别的牛的话，那么是不是说明这群牛一定不会有每个牛都喜欢？

这样的话，是不是就没有符合上述条件的牛，那就输出0

如果是只有一个牛的出度为零，是不是就说明这些牛一定有被所有牛都喜欢的。

被所有牛都喜欢的牛的个数为：出度为零的强连通分量中点的个数。

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 110000
using namespace std;
bool vis[N];
int n,s,m,x,y,ans,tot,tim,top,sum;
int out[N],dfn[N],low[N],head[N],belong[N],stack[N],point[N];
int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
struct Edge
{
    int to,next,from;
}edge[N];
int add(int x,int y)
{
    tot++;
    edge[tot].to=y;
    edge[tot].next=head[x];
    head[x]=tot;
}
int tarjan(int now)
{
    dfn[now]=low[now]=++tim;
    vis[now]=true;stack[++top]=now;
    for(int i=head[now];i;i=edge[i].next)
    {
        int t=edge[i].to;
        if(vis[t]) low[now]=min(low[now],dfn[t]);
        else if(!dfn[t]) tarjan(t),low[now]=min(low[now],low[t]);
    }
    if(low[now]==dfn[now])
    {
        sum++;belong[now]=sum;point[sum]++;
        for(;stack[top]!=now;top--)
         vis[stack[top]]=false,belong[stack[top]]=sum,point[sum]++;
        vis[now]=false; top--;
    }
}
int shrink_point()
{
    for(int i=1;i<=n;i++)
     for(int j=head[i];j;j=edge[j].next)
         if(belong[i]!=belong[edge[j].to])
          out[belong[i]]++;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
     x=read(),y=read(),add(x,y);
    for(int i=1;i<=n;i++)
     if(!dfn[i]) tarjan(i);
    shrink_point();
    for(int i=1;i<=sum;i++)
     if(!out[i]) s++,ans=point[i];
    if(s!=1) ans=0; 
    printf("%d",ans);
    return 0;
}
```

---

## 作者：何卓然 (赞：0)

Tarjan 好题！

我们发现，奶牛中的崇拜关系是一个单向的关系，而且如果崇拜的传递关系正符合路径的延长性质。根据这个关系建图，题目转化为：求有多少个点，使得所有其他点都有一条到它的路径。

我们对这个有向图上用 Tarjan 跑一遍 SCC ，缩点之后整张图变成一个 DAG，就非常好操作了。


复杂度是 n + m 的。


**Code**









    
            
            
```cpp
#include<bits/stdc++.h>
using namespace std;
#define REP(i,a,b) for (int i=(a);i<(b);i++)
#define N 10005
int src = 0, cnt = 0, p = -1, zero_degree = 0;
int dfn[N],low[N],tag[N],out_degree[N],in_degree[N];
bool in_stack[N],vis[N],ok[N];
vector<vector<int> > v(N);
vector<vector<int> > edges(N);
vector<vector<int> > graph(N);
stack<int> st;
int n,m,fm,to,ans;
void tarjan(int u){
    dfn[u] = low[u] = src++;
    st.push(u);
    vis[u] = true;
    in_stack[u] = true;
    REP(i,0,v[u].size()){
        if (!vis[v[u][i]]){
            tarjan(v[u][i]);
            low[u] = min(low[u],low[v[u][i]]);
        }
        else if (in_stack[v[u][i]]){
            low[u] = min(low[u],dfn[v[u][i]]);
        }
    }
    if (dfn[u] == low[u]){
        int temp = st.top();
        cnt++;
        do{
            temp = st.top();
            tag[temp] = cnt;
            st.pop();
        }while(u != temp);
    }
}
void dfs(int cur){
    ok[cur] = true;
    REP(i,0,graph[cur].size()){
        if (!ok[graph[cur][i]]){
            dfs(graph[cur][i]);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    REP(i,0,m){
        scanf("%d%d",&fm,&to);
        v[fm].push_back(to);
    }
    REP(i,1,n+1) if (!tag[i]) tarjan(i);
    REP(i,1,n+1){
        REP(j,0,v[i].size()){
            if (tag[i] != tag[v[i][j]]){
                edges[tag[i]].push_back(tag[v[i][j]]);
                graph[tag[v[i][j]]].push_back(tag[i]);
                out_degree[tag[i]]++;
                in_degree[tag[v[i][j]]]++;
            }
        }
    }
    REP(i,1,cnt+1)
        if (out_degree[i] == 0){
            zero_degree++;
            p = i;
        }
    if (zero_degree >= 2){
        printf("0");
        return 0;
    }
    else
    {
        dfs(p);
        REP(i,1,cnt+1)
            if (in_degree[i] == 0)
                if (!ok[i]){
                    printf("0");
                    return 0;
                }
        REP(i,1,n+1) if (tag[i] == p) ans++;
        printf("%d",ans);
    }
    return 0;
}
```

---

## 作者：sunyt (赞：0)

楼下dalao们用tarjan的很多，但好像没有用并查集+tarjan的，那我就讲讲我的思路吧。

Tarjan算法预处理强连通分量，缩点处理，然后得到一张新图，且这张图为有向无环图，然后利用并查集查找从任何节点出发都可以抵达的节点个数即可，用一个数组查询父亲节点为i的个数，但是要注意unionn的操作时，fa[xx]=fy，而不是原来的样子，也就是说我们需要操作的是让边上一个节点与另一个节点的根节点直接连接，可以称之为伪unionn操作吧，然后在每一个符合题意的新图的大节点中分别去计算小节点个数（当然也可以预处理直接实现），最后输出。

代码比较长，但是思路并不是很难想，只是细节较多（大概这四次有效过题得分是48,49,93，AC）分数的分配也是醉了。

推介一波博客<http://blog.csdn.net/Stockholm\_Sun>，欢迎来踩，如有问题请赐教！


```cpp
#include<iostream>
using namespace std;
int i,j,n,m;
bool b[100001];
int color[100001],colorn;
int stack[100001],top;//数组模拟栈 
int s,e,temp,index,ans,bb[100001];
int dfn[100001],low[100001];
int head[100001],rd[100001],fa[100001];
int gs[100001];
struct data
{
    int v,u;
    data *nxt;
}a[1000001];

int r()
{
    char ch=getchar();
    int ans=0;
    while(ch<'0'||ch>'9')
    {
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        ans*=10;
        ans+=ch-'0';
        ch=getchar();
    }
    return ans;
}

int ins(int ss,int ee)
{
    temp++;
    a[temp].nxt=&a[head[ss]];
    a[temp].u=ss;
    head[ss]=temp;
    a[temp].v=ee;
}

int findd(int xx)
{
    if(fa[xx]==xx) return fa[xx];
    return fa[xx]=findd(fa[xx]);
}

void unionn(int xx,int yy)
{
    int fy=findd(yy);
    fa[xx]=fy;
}

void tarjan(int x)
{
    dfn[x]=++index;
    low[x]=index;
    b[x]=1,bb[x]=1;
    stack[++top]=x;
    data *p=&a[head[x]];
    while(p->v!=0)
    {
        int vv=p->v;
        if(!dfn[vv])
        {
            tarjan(vv);
            low[x]=min(low[x],low[vv]);
        }
        else if(b[vv])
        {
            low[x]=min(low[x],dfn[vv]);
        }
        p=p->nxt;
    }
    if(dfn[x]==low[x])
    {
    b[x]=0;
    color[x]=++colorn;
    while(stack[top]!=x)
    {
        color[stack[top]]=colorn;
        b[stack[top--]]=0;
    }
    top--;
    }
}

int main()
{
    n=r(),m=r();
    for(i=1;i<=n;i++)
    rd[i]=1;
    for(i=1;i<=m;i++)
    {
        s=r(),e=r();
        ins(s,e);
    }
    for(i=1;i<=n;i++)
    if(!bb[i])
    tarjan(i);
    for(i=1;i<=colorn;i++)
    fa[i]=i;
    for(i=1;i<=m;i++)
    {
        if(color[a[i].v]!=color[a[i].u])
        unionn(color[a[i].u],color[a[i].v]);
    }
    for(i=1;i<=colorn;i++)
    findd(i);
    for(j=1;j<=colorn;j++)
    for(i=1;i<=colorn;i++)
    if(fa[i]==j)
    gs[j]++;
    
    for(i=1;i<=colorn;i++)
    {
        if(gs[i]==colorn)
        for(j=1;j<=n;j++)
        if(color[j]==i)
        ans++;
    }
    cout<<ans;
}
```

---

## 作者：沧澜 (赞：0)

**水题**tarjn的缩点模板题。

画几个图，模拟一下，就会发现一个显而易见的规律：

**缩完点后，如果有多个出度为零的点，那就没有最受欢迎的妞，因为那几个出度为0的缩点内的各点不可能联通。**

由此可见，这个题目的思路就是：找出度为零的缩点，若有一个，则输出该缩点中点的个数，否则输出0；

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 500000+15
using namespace std;
struct nond{
    int x,y,next;
    nond(int x=0,int y=0,int next=0):
        x(x),y(y),next(next) {}
}edge[maxn];
int n,m,sumedge,head[maxn],x,y;
int top,stack[maxn],dfn[maxn],low[maxn],tim;
int vis[maxn],visstack[maxn],colur[maxn],sumcol;
int num[maxn],bns[maxn];
int add(int a,int b){
    edge[++sumedge]=nond(a,b,head[x]);
    return head[x]=sumedge;
}
int dfs(int now){
    low[now]=dfn[now]=++tim;
    stack[++top]=now;
    vis[now]=1;
    visstack[now]=1;
    for(int u=head[now];u;u=edge[u].next)
        if(visstack[edge[u].y])
            low[now]=min(low[now],dfn[edge[u].y]);
        else if(!vis[edge[u].y]){
            dfs(edge[u].y);
            low[now]=min(low[now],low[edge[u].y]);
        }
    if(low[now]==dfn[now]){
        sumcol++;
        colur[now]=sumcol;
        while(stack[top]!=now){
            colur[stack[top]]=sumcol;
            visstack[stack[top]]=0;
            top--;
            bns[sumcol]++;
        }
        visstack[now]=0;
        bns[sumcol]++;
        top--;
    }
    return 0;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        add(x,y);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])    dfs(i);
    for(int i=1;i<=m;i++)
        if(colur[edge[i].x]!=colur[edge[i].y])
            num[colur[edge[i].x]]++;
    int chudu=0,ans=0;
    for(int i=1;i<=sumcol;i++)
        if(num[i]==0){
            chudu++;
            ans=i;
        }
    if(chudu!=1)    cout<<"0";
    else    cout<<bns[ans];
}
```

---

## 作者：XZYQvQ (赞：0)

没人写kosaraju算法么？其实个人觉得kosaraju易懂一些（~~而且名称和我的昵称有几分相似~~）。

思路网上都有啦，就是缩点后找出度为0的强连通分量有几个，有多个则输出0，只有一个则输出那个强连通分量的大小。

kosaraju代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,cnt,scc[10005],out[10005],siz[10005],ans;
bool book[10005];
vector<int> g[2][10005];
stack<int> sta;
void initdfs(int u)
{
    book[u]=1;
    for(vector<int>::iterator i=g[0][u].begin();i!=g[0][u].end();i++)
        if(!book[*i])initdfs(*i);
    sta.push(u);
}
void dfs(int u)
{
    book[u]=1,scc[u]=cnt,siz[cnt]++;
    for(vector<int>::iterator i=g[1][u].begin();i!=g[1][u].end();i++)
        if(!book[*i])dfs(*i);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++)
        scanf("%d%d",&a,&b),g[0][a].push_back(b),g[1][b].push_back(a);
    for(int i=1;i<=n;i++)if(!book[i])initdfs(i);
    memset(book,0,sizeof(book));
    while(!sta.empty())
    {
        int i=sta.top();sta.pop();
        if(!book[i])cnt++,dfs(i);
    }
    for(int u=1;u<=n;u++)
        for(vector<int>::iterator i=g[0][u].begin();i!=g[0][u].end();i++)
            if(scc[u]!=scc[*i])out[scc[u]]++;
    for(int i=1;i<=cnt;i++)
        if(!out[i])
        {
            if(ans){printf("0\n");return 0;}
            else ans=i;
        }
    printf("%d\n",siz[ans]);
    return 0;
}
```

---

## 作者：QwQ2000 (赞：0)

其实并不需要什么拓扑序嘛QwQ

只需要找出所有缩点以后的反图上入度为零的点 然后在这些点上跑bfs看看能不能到达所有点就可以了

记得tarjan的时候统计每一个强连通分量的大小嗯

强连通分量裸题 真的挺水的 我1A了hhh

[codec]











```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=10005,M=50005;
int n=0,m=0;
int head[N],to[M],next[M],edge=0;
int dfn[N],inS[N],idx=1,low[N];
int stk[N],top=0;
int comp[N],n2=0,cnt[N];
int in[N];
int head2[N],to2[M],next2[M],edge2=0;
int q[N*233],front=0,back=0,vis[N];
inline void addEdge(int u,int v) {
    to[edge]=v,next[edge]=head[u],head[u]=edge++;
}
void tarjan(int x) {
    dfn[x]=low[x]=idx++;
    stk[top++]=x;
    inS[x]=1;
    for (int e=head[x];~e;e=next[e]) {
        int& v=to[e];
        if (!dfn[v]) {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        } else if (inS[x]) 
            low[x]=min(low[x],dfn[v]);
    }
    if (dfn[x]==low[x]) {
        ++n2;
        int u=0;
        do {
            u=stk[--top];
            comp[u]=n2;
            inS[u]=0;
            ++cnt[n2];
        } while (u!=x);
    }
}
inline void addEdge2(int u,int v) {
    ++in[v];
    to2[edge2]=v,next2[edge2]=head2[u],head2[u]=edge2++;
}
inline void build() {
    for (int i=1;i<=n;++i)
        for (int e=head[i];~e;e=next[e]) {
            int &u=comp[i],&v=comp[to[e]];
            if (u!=v)
                addEdge2(v,u);
        }
}
inline int bfs(int s) {
    front=back=0;
    memset(vis,0,sizeof(vis));
    q[back++]=s;
    vis[s]=1;
    while (front<back) {
        int x=q[front++];
        for (int e=head2[x];~e;e=next2[e]) {
            int& v=to2[e];
            if (!vis[v]) {
                q[back++]=v;
                vis[v]=1;
            }
        }
    }
    for (int i=1;i<=n2;++i)
        if (!vis[i])
            return 0;
    return 1;
}
int main(void) {
    memset(head,-1,sizeof(head));
    scanf("%d %d",&n,&m);
    while (m--) {
        int u=0,v=0;
        scanf("%d %d",&u,&v);
        addEdge(u,v);
    }        
    for (int i=1;i<=n;++i)
        if (!dfn[i])
            tarjan(i);
    //建缩点以后的反图 就所有入度为0的点bfs
     memset(head2,-1,sizeof(head2));
     build();
     int ans=0;
     for (int i=1;i<=n2;++i)
         if (!in[i])
             if (bfs(i))
                 ans+=cnt[i];
    printf("%d\n",ans);
    return 0;
} 
[/codec]
```

---

## 作者：封禁用户 (赞：0)

这题的思路是tarjan求强联通分量

题意为对于一张有向图，找出一些点，使得所有点均能到达该点，求出这些点的数量

首先我们求出所有强联通分量

显然，若1能到达2，（2，3，4）是一个强联通分量，

那么1肯定能到达2，3，4所有点。

于是我们可以将此题简化成：

找出一个强联通分量，使得所有强联通分量均能到达强联通分量，求出此强联通分量的元素个数

易证明只有一个强联通分量满足要求

那么满足条件的分量是哪个呢？其实这不需要用搜索

只要满足入度为0的强联通分量不超过1，那么tarjan求得最远的强联通分量就是所求解

以下是代码：




    

        
        

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int i,j,k,m,n;
int top=0,cnt=0,num=0;
int First[100001],Next[100001],Last[100001],a[100001],pe[100001],pupuvovovovo[100001];
bool b[100001],b2[100001];
int q[100001],dfn[100001],low[100001],fa[100001];
void add(int x,int y)
{
    k++;a[k]=y;
    if(First[x]==0)First[x]=k;
    else Next[Last[x]]=k;
    Last[x]=k;
}
void tarjan(int x)
{
    top++;cnt++;
    dfn[x]=low[x]=cnt;
    q[top]=x;
    b[x]=true;
    int t=First[x];
    while(t!=0)
    {
        int v=a[t];
        if(dfn[v]==0)
        {
            tarjan(v);
            if(low[v]<low[x])
            low[x]=low[v];
        }
        else if(b[v]&&dfn[v]<low[x])
        low[x]=dfn[v];
        t=Next[t];
    }
    if(dfn[x]==low[x])
    {
        n++;
        while(q[top+1]!=x)
        {
            pe[n]++;
            fa[q[top]]=n;
            b[q[top]]=false;
            top--;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    int x,y;
    k=0;
    for(i=1;i<=m;i++)
    {
        scanf("%d %d",&x,&y);
        add(x,y);
    }
    int m=n+1;
    for(i=1;i<=m-1;i++)
    {
        if(dfn[i]==0)
        tarjan(i);
    }
    for(i=1;i<=m-1;i++)
    {
        for(int o=First[i];o;o=Next[o])
        if(fa[i]!=fa[a[o]])
        pupuvovovovo[fa[i]]++;
    }
    int pp=0;
    for(i=m;i<=n;i++)
    if(pupuvovovovo[i]==0)pp++;
    if(pp==1)
    cout<<pe[m];
    else cout<<0;
}
```

---

