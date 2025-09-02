# サッカー (Soccer)

## 题目描述

平面直角坐标系上，有一个足球场，横坐标范围 $[0,X]$，纵坐标范围 $[0,Y]$。

开始时，球场上站了 $N$ 个球员，坐标分别为 $(x_i,y_i)$。

球在开始时 $1$ 号球员的位置上，你希望让这
个球到开始时 $N$  号球员的位置上。

你可以指挥任一球员进行下列某一操作，但某些操作会提升球员的疲劳度。指挥次数不限但应当有
明确的先后顺序。

已知每个球员有两种状态：控球和没有控球。
你可以指挥控球的球员进行如下操作：

• 踢球。在上下左右四个方向中任选一个，并指定一个正整数 $p$ ，该球员将球朝指定方向踢出恰好 $p$
个单位。该球员不会移动，且自动停止控球，疲劳度上升$A×p+B$。

• 运球。在上下左右四个方向中任选一个，该球员带球，朝指定方向移动 $1$ 个单位。疲劳度上升
$C$。

• 停止控球。该球员的疲劳度不改变。

你可以指挥没有控球的球员进行如下操作：

• 移动。在上下左右四个方向中任选一个，该球员朝指定方向移动 $1$ 个单位，疲劳度上升 $C$。

• 控球。如果该球员所在的位置恰好有球，且没有其他球员控球，该球员才能控球。该球员的疲劳
度不改变。

**球员和球有可能跑出场外，一个位置上可能有多个球员。
球员可视作质点，因此球滚动和运球时都不会因为碰到球员而停下。**

让球滚到指定位置的过程中，求所有球员上升的疲劳度之和的最小值。

## 样例 #1

### 输入

```
6 5
1 3 6
3
1 1
0 4
6 5```

### 输出

```
26```

## 样例 #2

### 输入

```
3 3
0 50 10
2
0 0
3 3```

### 输出

```
60```

## 样例 #3

### 输入

```
4 3
0 15 10
2
0 0
4 3```

### 输出

```
45```

## 样例 #4

### 输入

```
4 6
0 5 1000
6
3 1
4 6
3 0
3 0
4 0
0 4```

### 输出

```
2020```

# 题解

## 作者：sky_landscape (赞：0)

题目询问两个点之间的对小代价，自然想到最短路。

我们发现当球在同一个点上的时候其实状态是不一样的。

如果是一个球员运球到这个点，那么可以向四个方向运球。但是如果是这个球在踢球的过程中，是改变不了方向的。

所以需要把一个点拆成五个点，分别表示在运球，向上，下，左，右踢球。

连边有以下几种：

运球点向相邻的运球点连双向边，边权为 $C$。

四个踢球点分别与相邻对应的点连单向边（例如向左踢球连左边点拆出来的向左踢球），边权为 $A$。

考虑踢球与运球之间的转换。首先运球点连单向边到踢球点，因为疲劳度计算中有一个常数 $B$，所以边权为 $B$。

最后是四个踢球点到运球点，需要最近的球员跑过来，所以用 $BFS$ 预处理一下每个点离最近的球员的距离 $dis$，连单向边，边权为 $dis\times C$。

解释一下为什么最后一种连边是对的。因为题目中球员跑动和运球的疲劳度都是 $C$，不存在一个球员去接两次球的情况，因为直接带球过去肯定不劣。

建完边跑最短路就行。

有一些小点要注意，横纵坐标从零开始，所以其实可以认为 $n,m\le 501$，不要开小空间。

还有行末要输出一个换行，不然会被判错。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=260000;
const int MAXN=5*N;
const int INF=1e18;
int dis[N],ans[MAXN];
struct node{
    int to,val;
};
vector<node> v[MAXN];
int n,m;
int a,b,c;
int man_what_can_i_say;
bool vis[N];

struct stu{
    int s,t;
}q[N];

int get_pla(int x,int y){
    return (x-1)*m+y;
}

inline int read(){
    char ch=getchar();int x=0;bool f=false;
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=true;
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    if(f) x=-x;
    return x;
}

struct nnd{
    int pla,val;
    bool operator<(const nnd &aa)const{
        return val>aa.val;
    }
};
priority_queue<nnd> qe;

void bfs(){
    while(qe.size()){
        nnd x=qe.top();
        //cout<<x.pla<<" "<<x.val<<"\n"; 
        qe.pop();
        int i=x.pla/m,j=x.pla%m;
        i++;
        if(!j) j=m,i--;
        //cout<<"shit: "<<i<<" "<<j<<"\n";
        if(i>1 && !vis[get_pla(i-1,j)]){
            vis[get_pla(i-1,j)]=true;
            dis[get_pla(i-1,j)]=x.val+c;
            qe.push({get_pla(i-1,j),dis[get_pla(i-1,j)]});
        }
        if(i<n && !vis[get_pla(i+1,j)]){
            vis[get_pla(i+1,j)]=true;
            dis[get_pla(i+1,j)]=x.val+c;
            qe.push({get_pla(i+1,j),dis[get_pla(i+1,j)]});
        }
        if(j>1 && !vis[get_pla(i,j-1)]){
            vis[get_pla(i,j-1)]=true;
            dis[get_pla(i,j-1)]=x.val+c;
            qe.push({get_pla(i,j-1),dis[get_pla(i,j-1)]});
        }
        if(j<m && !vis[get_pla(i,j+1)]){
            vis[get_pla(i,j+1)]=true;
            dis[get_pla(i,j+1)]=x.val+c;
            qe.push({get_pla(i,j+1),dis[get_pla(i,j+1)]});
        }
    }
}

void init(){
    n=read(),m=read();
    n++,m++;
    a=read(),b=read(),c=read();
    man_what_can_i_say=read();
    for(int i=1;i<=n*m;i++) dis[i]=INF;
    for(int i=1;i<=man_what_can_i_say;i++){
        q[i].s=read(),q[i].t=read();
        q[i].s++,q[i].t++;
        vis[get_pla(q[i].s,q[i].t)]=true;
        dis[get_pla(q[i].s,q[i].t)]=0;
        qe.push({get_pla(q[i].s,q[i].t),0});
    }
    bfs();
}

void pre(){
    /*for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<dis[get_pla(i,j)]<<" ";
        }
        cout<<"\n";
    }*/
    int plus=get_pla(n,m);
    //cout<<"plus: "<<plus<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int now=get_pla(i,j);
            int up,nowu,down,nowd,lef,nowl,right,nowr;
            up=now+plus,down=up+plus,lef=down+plus,right=lef+plus;
            nowu=get_pla(i-1,j),nowd=get_pla(i+1,j),nowl=get_pla(i,j-1),nowr=get_pla(i,j+1);
            v[now].push_back({up,b});
            v[now].push_back({down,b});
            v[now].push_back({lef,b});
            v[now].push_back({right,b});
            v[up].push_back({now,dis[now]});
            v[down].push_back({now,dis[now]});
            v[lef].push_back({now,dis[now]});
            v[right].push_back({now,dis[now]});
            /*if(i==2 && j==2){
                cout<<nowu<<" "<<nowd<<" "<<nowl<<" "<<nowr<<"\n";
            }*/
            if(i>1){
                int cha=nowu-now;
                v[now].push_back({now+cha,c});
                v[up].push_back({up+cha,a});
            }
            if(i<n){
                int cha=nowd-now;
                v[now].push_back({now+cha,c});
                v[down].push_back({down+cha,a});
            }
            if(j>1){
                int cha=nowl-now;
                v[now].push_back({now+cha,c});
                v[lef].push_back({lef+cha,a});
            }
            if(j<m){
                int cha=nowr-now;
                v[now].push_back({now+cha,c});
                v[right].push_back({right+cha,a});
            }
        }
    }
}

void dij(){
    for(int i=1;i<=5*n*m;i++){
        ans[i]=INF;
    }
    //cout<<1<<"\n";
    priority_queue<nnd> que;
    que.push({get_pla(q[1].s,q[1].t),0});
    ans[get_pla(q[1].s,q[1].t)]=0;
    int used=0;
    while(que.size()){
        //cout<<que.size()<<"\n";
        nnd x=que.top();
        //cout<<x<<"\n";
        que.pop();
        for(int i=0;i<v[x.pla].size();i++){
            used++;
            int to=v[x.pla][i].to;
            //cout<<"to: "<<to<<"\n";
            if(ans[to]>ans[x.pla]+v[x.pla][i].val){
                ans[to]=(ans[x.pla]+v[x.pla][i].val);
                que.push({to,ans[to]});
            }
        }
    }
    //cout<<"used: "<<used<<"\n";
    return;
}

signed main(){
    init();
    //cout<<"shit"<<"\n";
    pre();
    //cout<<"fuck"<<"\n";
    dij();
    //cout<<"caonima"<<"\n";
    int ot=INF;
    int plus=get_pla(n,m),pla=get_pla(q[man_what_can_i_say].s,q[man_what_can_i_say].t);
    //cout<<pla<<" "<<plus<<"\n";
    ot=min(ot,ans[pla]);
    ot=min(ot,ans[pla+plus]);
    ot=min(ot,ans[pla+2*plus]);
    ot=min(ot,ans[pla+3*plus]);
    ot=min(ot,ans[pla+4*plus]);
    cout<<ot<<"\n";
    return 0;
}
```

---

