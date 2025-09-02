# [GCJ 2021 #2] Retiling

## 题目描述

Cody-Jamal 最新的艺术装置是一个可以重新铺设不同图案的厨房瓷砖地面。地面由 $\mathbf{R}$ 行 $\mathbf{C}$ 列的正方形瓷砖组成。每块瓷砖都是双面的，一面是品红色（M），另一面是绿色（G）。

要重新铺设厨房地面，允许进行以下两种操作：
* **翻转**一块瓷砖，将其可见面从品红色变为绿色，或反之，每次操作花费 $\mathbf{F}$ 枚硬币；
* **交换**两块相邻的瓷砖（水平或垂直相邻，不包括对角线相邻），不翻转任何瓷砖，每次操作花费 $\mathbf{S}$ 枚硬币。

观看 Cody-Jamal 的艺术地面是免费的，但与之互动需要花费硬币。已知地面的当前状态和目标图案，求最少需要花费多少枚硬币才能将地面从当前状态转变为目标图案。

## 说明/提示

**样例解释**

在样例 #1 中：
- 当前状态与目标图案有 5 处颜色不同；
- 最少需要 3 次操作（每次操作最多改变 2 处颜色）；
- 一种最优方案：
  1. 交换第一行最左两块瓷砖；
  2. 交换第一行最右两块瓷砖；
  3. 翻转右下角瓷砖。

![](https://cdn.luogu.com.cn/upload/image_hosting/lnckx68s.png)

在样例 #2 中：
- 有 6 处颜色需要改变；
- 由于只能通过交换同时改变两处颜色，最少需要 4 次操作；
- 一种最优方案：
  1. 交换中间列最上两块瓷砖；
  2. 翻转右上角瓷砖；
  3. 交换最右列最下两块瓷砖；
  4. 翻转最左列中间瓷砖。

![](https://cdn.luogu.com.cn/upload/image_hosting/yholjw9b.png)

测试集 2 的样例中：
- 翻转操作非常昂贵，应尽量避免；
- 由于目标图案比当前状态多 1 块品红色瓷砖，必须至少进行 1 次翻转；
- 最优方案（花费 1003 枚硬币）：
  1. 交换最左两块瓷砖；
  2. 翻转最右瓷砖；
  3. 交换左数第二和第三块瓷砖；
  4. 交换左数第三和第四块瓷砖。

![](https://cdn.luogu.com.cn/upload/image_hosting/7c22w7hy.png)

**限制条件**

- $1 \leq \mathbf{T} \leq 100$；
- $1 \leq \mathbf{R} \leq 10$；
- $1 \leq \mathbf{C} \leq 10$。

**测试集 1（11 分，可见判定）**

- $\mathbf{F}=1$；
- $\mathbf{S}=1$。

**测试集 2（23 分，隐藏判定）**

- $1 \leq \mathbf{F} \leq 10^{6}$；
- $1 \leq \mathbf{S} \leq 10^{6}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
2 4 1 1
MGMG
MMMG
GMGM
MMMM
3 3 1 1
MGG
GMG
MMM
MMM
MGM
MMG```

### 输出

```
Case #1: 3
Case #2: 4```

## 样例 #2

### 输入

```
1
1 5 1000 1
MGGGG
GGGMM```

### 输出

```
Case #1: 1003```

# 题解

## 作者：_LiWenX_ (赞：1)

不知道为啥我想了这么久/tuu。

首先考虑如果去掉操作一怎么做，只有交换乍一看还有点难度。

不过你会发现两个很显然的东西：

1. 连续翻转一条路径，相当于是平移路径，然后把第一个位置放到最后面。
2. 我不可能交换两个一样的位置。

所以基本的操作是，对于 011..111，变成 11..1110，然后你发现，你可以以路径长度的代价交换两个数字了。

所以没有操作一做法是简单的，直接把要修改的红点和要修改的绿点建二分图，边权是两个点的曼哈顿距离乘 $S$，跑费用流就好了。

如果有操作一，注意到操作一与操作二不交，比较感性的理解是，对于 00，你想把他变成 01，绝对是直接对第二个 0 做操作一，而不是对第一个位置操作一再交换他们。

所以做法呼之欲出，设要修改的数量为 $k$，如果使用操作二的方法，满足了 $2t$ 个点的限制，那么操作一的次数一定是 $k-2t$，所以直接跑费用流，每做一轮 EK，就用这个式子动态更新答案即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,F,S;
struct edge{
    int from,to,val,w;
}e[105*105*2];int head[105],siz=1;
void adde(int x,int y,int z,int w){
    e[++siz].to=y,e[siz].val=z,e[siz].w=w;
    e[siz].from=head[x],head[x]=siz;
}
void addedge(int x,int y,int z,int w){
    adde(x,y,z,w),adde(y,x,0,-w);
}
char a[105][105],b[105][105];
int id[105][105];
int dis[105],vis[105],pre[105];
bool spfa(int s,int t){
    for(int i=1;i<=t;i++) dis[i]=1e18,vis[i]=0,pre[i]=0;
    queue<int> q;q.push(s);
    dis[s]=0;
    while(!q.empty()){
        int now=q.front();q.pop();
        vis[now]=0;
        for(int i=head[now];i;i=e[i].from){
            int u=e[i].to;
            if(!e[i].val) continue;
            if(dis[u]>dis[now]+e[i].w){
                dis[u]=dis[now]+e[i].w;
                pre[u]=i;
                if(!vis[u]){
                    vis[u]=1;
                    q.push(u);
                }
            }
        }
    }return dis[t]<1e18;
}
int tid;
void solve(){
    cin>>n>>m>>F>>S;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            id[i][j]=0;
        }
    }
    int tot=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>b[i][j];
            if(a[i][j]!=b[i][j]){
                id[i][j]=++tot;
            }
        }
    }
    int s=tot+1,t=s+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!id[i][j]) continue;
            if(a[i][j]=='M') addedge(s,id[i][j],1,0);
            else addedge(id[i][j],t,1,0);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!id[i][j]) continue;
            if(a[i][j]!='M') continue;
            for(int x=1;x<=n;x++){
                for(int y=1;y<=m;y++){
                    if(!id[x][y]) continue;
                    if(a[x][y]=='M') continue;
                    addedge(id[i][j],id[x][y],1,(abs(i-x)+abs(j-y))*S);
                }
            }
        }
    }
    int ans=tot*F;
    int sum=0;
    while(spfa(s,t)){
        sum+=dis[t];tot-=2;ans=min(ans,sum+tot*F);
        int x=t;
        while(x!=s){
            e[pre[x]].val--,e[pre[x]^1].val++;
            x=e[pre[x]^1].to;
        }
    }cout<<"Case #"<<++tid<<": "<<ans<<'\n';

    for(int i=1;i<=t;i++) head[i]=0;
    for(int i=1;i<=siz;i++) e[i].from=e[i].to=e[i].val=e[i].w=0;
    siz=1;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tt;cin>>tt;
    while(tt--) solve();
}
```

---

