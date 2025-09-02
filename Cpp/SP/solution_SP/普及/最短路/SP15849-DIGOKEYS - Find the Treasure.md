# DIGOKEYS - Find the Treasure

## 题目描述

一个喜欢玩锁和钥匙游戏并且逻辑很好的通灵者 Digo 有一天买了一套包含 $N$ 个盒子的装置，每个盒子都有一个从 $1$ 到 $N$（包括 $1$ 和 $N$）之间的唯一编号。除了第 $N$ 个盒子装有宝藏外，其他每个盒子里都有一把钥匙。由于制造缺陷，大多数钥匙可以打开多个盒子。

规则是每把钥匙只能用来打开一个盒子。除了第一个盒子外，所有盒子都是上锁的。Digo 急于得到宝藏，请求你找到一种方法，从第一个盒子里的钥匙开始，以最少的步骤打开最后一个盒子。

## 说明/提示

- $1 \le T \le 10$
- $2 \le N \le 100000$
- $1 \le M_i \le 10$

**样例输入**

```
2

3

1 2

1 3

4

2 2 3

1 1

2 2 4
```

**样例输出**

```
2

1 2

2

1 3
```

# 题解

## 作者：_maple_leaf_ (赞：0)

由于一些恶心原因，我调了好久。。。
## 题意
简化版：给你一个 $N-1$ 个点 $\sum^{N-1}_{i=1}M_i$ 条权值为 $1$ 的边的有向图，让你求出从 $1$ 点到 $n$ 点的最短路长度与字典序最小的最短路径，若无法到达 $N$ 点，输出 $-1$。有多组数据，共 $T$ 组。

## 思路
一个简单最短路。

求最短路是简单的，很多方法都可以，我使用的是 dijkstra，记录路径和 [SP3405](https://www.luogu.com.cn/article/as5bd2ft) 一样，直接记录转移路径即可，但在中间不用标记边（与 SP3405 相比），而是将所有最短路径中经过的点倒序记录下来（不记录终点，即 $N$ 节点），最后比较字典序大小，找出最小的，然后输出最短路长度与找出的字典序最小最短路径即可。

## 代码
```cpp
//by _maple_leaf_ uid:964876
#include<bits/stdc++.h>
#define int long long
#define FAST true
#define FIO true
#define DEBUG false
using namespace std;
#if FIO
void fio(string s,int i=0){
    freopen(((s+(i?to_string(i):""))+".in").c_str(),"r",stdin);
    freopen(((s+(i?to_string(i):""))+".out").c_str(),"w",stdout);
}
#endif
//#define int long long
//#define int unsigned int
//#define int __int128
//#define mod
#define pii pair<int,int>
#if DEBUG
bool Memory_start;
void debug();
#endif
#if FAST
inline int read(){
    char c=getchar();
    int ret=0,f=1;
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }\
    while(c>='0'&&c<='9'){
        ret=(ret<<3)+(ret<<1)+c-'0';
        c=getchar();
    }return ret*f;
}
inline void write(int x,int op=0){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10,0);
    putchar((char)(x%10+'0'));
    if(op){
        if(op>0)puts("");
        if(op<0)putchar(' ');
        if(op==0)puts("114514");
    }
}
#endif
const int N=1e6+10;
int T;
int n;
struct node{
    int v,n;
}e[N*10];
int head[N],cnt;
void add(int u,int v){
    e[++cnt]={v,head[u]};
    head[u]=cnt;
}
priority_queue<pii,vector<pii>,greater<pii>>q;
int dis[N];
vector<int>la[N];
vector<int>ans;
vector<int>tmp;
void dfs(int nw){
    if(nw!=n)tmp.push_back(nw);//记录路径
    if(nw==1){
        reverse(tmp.begin(),tmp.end());//反转
        if(ans.empty())ans=tmp;
        else if(tmp<ans)ans=tmp;
        reverse(tmp.begin(),tmp.end());//转回来
        tmp.pop_back();//撤回
        return ;
    }
    for(auto to:la[nw])dfs(to);
    if(nw!=n)/*就是这个if忘加了*/tmp.pop_back();//撤回
}
void dij(){
    memset(dis,0x7f,sizeof dis);
    dis[1]=0;
    q.push({0,1});
    while(!q.empty()){
        int nw=q.top().second;q.pop();
        if(nw==n){
            write(dis[nw],1);
            dfs(n);
            for(auto i:ans)write(i,-1);//输出
            if(T){
                puts("");
                puts("");
            }
            return ;
        }
        for(int i=head[nw];i;i=e[i].n){
            int to=e[i].v;
            if(dis[to]>dis[nw]+1){
                dis[to]=dis[nw]+1;
                la[to].clear();
                la[to].push_back(nw);
                q.push({dis[to],to});
            }else if(dis[to]==dis[nw]+1){
                la[to].push_back(nw);
            }
        }
    }putchar('-');
    putchar('1');
    if(T)puts(""),puts("");//无解
}
signed main(){
    T=read();
    while(T--){
        ans.clear();
        memset(la,0,sizeof la);
        memset(head,0,sizeof head);//清空（这个我也调了好久。。。）
        cnt=0;
        n=read();
        for(int i=1;i<n;i++){
            int m=read();
            for(int j=1;j<=m;j++){
                int v=read();
                add(i,v);//建边
            }
        }
        dij();//跑最短路
    }
#if DEBUG
    debug();
#endif
    return 0;
}//~*完结撒花*~
#if DEBUG
bool Memory_end;
void debug(){
    cerr<<"Time: "<<clock()<<" ms\n";
    cerr<<fixed<<setprecision(6)<<"Memory: "<<abs(&Memory_start-&Memory_end)/1024.0/1024.0<<" MB";
}
#endif
```

---

