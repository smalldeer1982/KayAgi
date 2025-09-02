# [GCJ 2009 Qualification] Watersheds

## 题目描述

地质学家有时会根据降雨流向将一片区域划分为不同的区域，这些区域被称为**流域**。

给定一张高程图（即一个二维的高度数组），请对地图进行标记，使得同属一个流域的区域具有相同的标记，并满足以下规则：

- 从每个格子出发，水最多只能流向其四个相邻格子中的一个。
- 对于每个格子，如果它的四个邻居中没有任何一个高度低于它自身，则水不会流动，该格子被称为**汇**。
- 否则，水会从该格子流向高度最低的邻居。
- 如果有多个邻居高度同为最低，则水会选择以下顺序中第一个最低的方向：北、 西、 东、 南。

所有直接或间接流向同一个汇的格子都属于同一个流域。每个流域应分配一个独特的小写字母作为标记，并且要保证：当将地图的所有行自上而下拼接成一个字符串时，所得字符串的字典序最小（特别地，最西北角的格子的流域标记总是 'a'）。


## 说明/提示

**样例说明**

在第 1 组数据中，右上角和左下角是汇。对角线上的水会流向左下角，因为那里高度较低（5 比 6 小）。

**限制条件**

- $T \leq 100$

**小数据集（10 分）**

- 时间限制：2 秒。
- $1 \leq H, W \leq 10$；
- $0 \leq \text{高度} < 10$；
- 最多有 2 个流域。

**大数据集（23 分）**

- 时间限制：3 秒。
- $1 \leq H, W \leq 100$；
- $0 \leq \text{高度} < 10,000$。
- 最多有 26 个流域。

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4
3 3
9 6 3
5 9 6
3 5 9
1 10
0 1 2 3 4 5 6 7 8 7
2 3
7 6 7
7 6 7
5 5
1 2 3 4 5
2 9 3 9 6
3 3 0 8 7
4 9 8 9 8
5 6 7 8 9```

### 输出

```
Case #1:
a b b
a a b
a a a
Case #2:
a a a a a a a a a b
Case #3:
a a a
b b b
Case #4:
a a a a a
a a b b a
a b b b a
a b b b a
a a a a a```

# 题解

## 作者：orson111 (赞：2)

# [P13429](https://www.luogu.com.cn/problem/P13429)

## 前言

为什麽这题满分 33 分？

## 正片

首先我们可以轻松算出每个点开始第一步流向哪。

然后就可以开始并查集啦！

合并完之后，我们从左上角扫到右下角，如果这个点的所属流域没有字母，那就给它一个，一直扫下去。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=109;
ll n,m,h[N][N];
ll fa[N*N],v[N*N];
ll id(ll x,ll y){return (x-1)*m+y;}
ll Find(ll x){return (fa[x]==x?x:(fa[x]=Find(fa[x])));}
ll dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
void upd(ll x,ll y){
    ll mn=1e18;
    for(ll i=0;i<4;i++){
        ll nx=x+dx[i],ny=y+dy[i];
        if(nx<1||nx>n||ny<1||ny>m) continue;
        mn=min(mn,h[nx][ny]);
    }
    if(mn>=h[x][y]) return;
    for(ll i=0;i<4;i++){
        ll nx=x+dx[i],ny=y+dy[i];
        if(nx<1||nx>n||ny<1||ny>m) continue;
        if(h[nx][ny]==mn){
            fa[Find(id(x,y))]=Find(id(nx,ny));
            break;
        }
    }
}
void solve(ll t){
    cin>>n>>m;
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++)
            cin>>h[i][j];
    for(ll i=1;i<=n*m;i++) fa[i]=i;
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++)
            upd(i,j);
    memset(v,0,sizeof(v));
    ll cnt=0;
    for(ll i=1;i<=n*m;i++)
        if(!v[Find(i)])
            v[Find(i)]=(++cnt);
    cout<<"Case #"<<t<<":\n";
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++)
            cout<<char('a'+v[Find(id(i,j))]-1)<<" \n"[j==m];
}
int main(){
    ll T;
    cin>>T;
    for(ll t=1;t<=T;t++) solve(t);
    return 0;
}
```

---

