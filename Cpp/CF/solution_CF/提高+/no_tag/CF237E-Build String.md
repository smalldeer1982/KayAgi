# Build String

## 题目描述

# 题目大意：
你需要使用一些字符串$s_1$，$s_2$，......，$s_n$来构建字符串t，你可以执行$|t|$ （$|t|$是字符串t的长度）次操作:
1. 从字符串$s_1$，$s_2$，......，$s_n$中选择一个非空字符串；
2. 从所选字符串中选择一个字符并将其写在纸上；
3. 从所选字符串中删除所选字符。

注意：执行上述操作后，字符串$s_1$，$s_2$，......，$s_n$中的字符总数减少1。

我们认为构建出了字符串t，当且仅当写在纸上的字符按顺序连起来为t。

但是还有其他限制：对于每个字符串$s_i$，有$a_i$为允许从字符串$s_i$中删除的最大字符数。

而且，从字符串$s_i$中每个删除字符的操作都需要一些代价。对于$s_i$，从中删除1个字符需要花费i的代价。

你的任务是计算根据给定规则构建字符串t所需的最小代价。

## 说明/提示

### 第一个样例：
1. 第一个字符串中取字符“b”和“z”；
2. 第二个字符串中取字符“a”，“e”和“b”。

在这种方案下，字符串t的代价是$2*1+3*2=8$。
### 第二个样例
1. 第一个字符串中取两个字符“a”；
2. 第二个字符串中取字符“c”；
3. 第三个字符串中取两个字符“a”；
4. 第四个字符串中取两个字符“b”。

在这种方案下，字符串t的代价是$2*1+1*2+2*3+2*4=18$。
### 第三个样例
无解，因为给定字符串中没有字符“y”。
输入中的所有字符串仅由小写英文字母组成。

$1≤|t|,|s_i|≤100$，$1≤n≤100$

## 样例 #1

### 输入

```
bbaze
3
bzb 2
aeb 3
ba 10
```

### 输出

```
8
```

## 样例 #2

### 输入

```
abacaba
4
aba 2
bcc 1
caa 2
bbb 5
```

### 输出

```
18
```

## 样例 #3

### 输入

```
xyz
4
axx 8
za 1
efg 4
t 1
```

### 输出

```
-1
```

# 题解

## 作者：酒笙青栀 (赞：3)

题意：给出一个字符串 str，然后有 n 个可供使用的字符串，现在在 n 个可用字符串中选取一定的字符组成字符串 str，从第 i 个串中拿一个字符的代价是 i 且最多拿 num[i] 个，求组成目标字符串的最小花费

**思路：最小费用流**

设置一个超级源点与超级汇点，从源点到 26 个字符建边，容量记为字符串 str 的个数，费用为 0，然后将每个字符向 n 个字符串建边，对于第 i 个串来说，容量为该串中相应字符的个数，费用为 i，最后对每个模式串向汇点建边，容量为 num[i]，费用为 0

AC代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
struct Edge{
    int from,to;
    int cap,flow;
    int cost;
    int next;
}edge[10001];
int head[10001],tot,n;
char str[10001];
int bucket[27];//str串中字符个数
int G[10001][27];//n个字符串每串的字符个数
int num[10001];//n个字符串每串最多取的个数
int pre[10001];//记录从S到i的最小费用路径上的最后一条弧编号
int dis[10001];
bool vis[10001];
bool SPFA(int S,int T) {
    queue<int> Q;
    memset(dis,INF,sizeof(dis));
    memset(vis,false,sizeof(vis));
    memset(pre,-1,sizeof(pre));
    dis[S]=0;
    Q.push(S);
    while(!Q.empty()) {
        int x=Q.front();
        Q.pop();
        vis[x]=false;
        for(int i=head[x];i!=-1;i=edge[i].next) {
            int y=edge[i].to;
            int cost=edge[i].cost;
            int cap=edge[i].cap;
            int flow=edge[i].flow;
            if(dis[y] > dis[x]+cost&&cap > flow) {
                dis[y]=dis[x]+cost;
                pre[y]=i;
                if(!vis[y]){
                    vis[y]=true;
                    Q.push(y);
                }
            }
        }
    }
    return pre[T]!=-1;
}
void MCMF(int S,int T,int &flow,int &cost){
    flow=0;
    cost=0;
    while(SPFA(S,T)){//每次寻找花销最小的路径
        int minn=INF;
        for(int i=pre[T];i!=-1;i=pre[edge[i^1].to])//寻找最小增广流
            minn=min(minn,edge[i].cap-edge[i].flow);
        for(int i=pre[T];i!=-1;i=pre[edge[i^1].to]) {
            edge[i].flow += minn;
            edge[i^1].flow-=minn;
            cost += edge[i].cost*minn;//增广流的花销
        }
        flow += minn;//总流量增加
    }
}
void addEdge(int from,int to,int cap,int flow,int cost){
    edge[tot].from=from;
    edge[tot].to=to;
    edge[tot].cap=cap;
    edge[tot].flow=flow;
    edge[tot].cost=cost;
    edge[tot].next=head[from];
    head[from]=tot++;
}
int main(){
    scanf("%s",str);
    int len=strlen(str);
    for(int i=0;i<len;i++)//统计str串中字符的个数
        bucket[str[i]-'a'+1]++;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        char temp[10001];
        scanf("%s%d",temp,&num[i]);
        int length=strlen(temp);
        for(int j=0;j<length;j++)
            G[i][temp[j]-'a'+1]++;//统计第i个字符串中字符的个数
    }
    tot=0;
    memset(head,-1,sizeof(head));
    int S=0,T=26+n+1;
    for(int i=1;i<=26;i++){
        if (bucket[i] == 0) continue;
        //源点到26个字符
        addEdge(S,i,bucket[i],0,0);//正向边
        addEdge(i,S,0,0,0);//反向边
        for(int j=1;j<=n;j++){
            if (G[j][i] == 0) continue;
            //26个字符到n个字符串
            addEdge(i,26+j,G[j][i],0,j);//正向边
            addEdge(26+j,i,0,0,-j);//反向边
        }
    }
    for(int i=1;i<=n;i++){//n个字符串到汇点
        addEdge(26+i,T,num[i],0,0);//正向边
        addEdge(T,26+i,0,0,0);//反向边
    }
    int flow,cost;
    MCMF(S,T,flow,cost);
    if (flow != len)//不满流
        printf("-1\n");
    else//满流
        printf("%d\n",cost);
    return 0;
}

```

---

## 作者：Jerrywang09 (赞：0)

比较简单的费用流。

对源字符串和字母建点。

对于目标字符串中的每个字符 $c$，建边 $(c, t)$，容量为 $1$，费用为 $0$。

然后考虑源字符串，计算费用。对于字符串 $i$ 中的每个字符 $c$，建边 $(i, c)$，容量为 $1$，费用为 $i$。

最后考虑限制，限制字符串 $i$ 最多取 $x$ 个字符，相当于建边 $(s, i)$，容量为 $x$，费用为 $0$。

```cpp
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=100010, inf=1e9;
using namespace std;

struct edge
{
    int v, c, w, n;
} e[N]; int hd[N], tot=1, n, m, s, t, siz;
void add(int u, int v, int c, int w)
{
    e[++tot]={v, c,  w, hd[u]}, hd[u]=tot;
    e[++tot]={u, 0, -w, hd[v]}, hd[v]=tot;
}
int d[N], in[N], f[N], pre[N];
bool spfa()
{
    rep(i, 1, t) d[i]=inf, in[i]=0;
    queue<int> q; q.push(s);
    d[s]=0, in[s]=1; f[s]=inf;
    while(q.size())
    {
        int u=q.front(); q.pop(); in[u]=0;
        for(int i=hd[u]; i; i=e[i].n)
        {
            int v=e[i].v, c=e[i].c, w=e[i].w;
            if(c && d[u]+w<d[v])
            {
                d[v]=d[u]+w;
                f[v]=min(f[u], c); pre[v]=i;
                if(!in[v]) in[v]=1, q.push(v);
            }
        }
    }
    return d[t]<inf;
}
int EK()
{
    int res=0, flow=0;
    while(spfa())
    {
        int u=t;
        while(u!=s)
        {
            int i=pre[u];
            e[i].c-=f[t], e[i^1].c+=f[t];
            u=e[i^1].v;
        }
        res+=f[t]*d[t], flow+=f[t];
    }
    if(flow<siz) res=-1;
    return res;
}
char a[N];
int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    scanf("%s%d", a+1, &n);
    s=n+26+1, t=s+1;
    siz=strlen(a+1); int x;
    rep(j, 1, siz)
    {
        x=a[j]-'a'+1;
        add(n+x, t, 1, 0);
    }
    rep(i, 1, n)
    {
        scanf("%s%d", a+1, &x);
        add(s, i, x, 0);
        m=strlen(a+1);
        rep(j, 1, m)
        {
            x=a[j]-'a'+1;
            add(i, n+x, 1, i);
        }
    }
    printf("%d", EK());
    
    return 0;
}
```

---

