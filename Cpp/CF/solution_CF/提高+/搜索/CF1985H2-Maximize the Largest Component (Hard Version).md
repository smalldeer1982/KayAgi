# Maximize the Largest Component (Hard Version)

## 题目描述

简单版本和困难版本实际上是不同的问题，因此请完整仔细地阅读两个问题的陈述。两个版本之间的唯一区别是操作。
Alex有一个由 $ n $ 行和 $ m $ 列组成的网格，由“.”和“#”字符组成。如果从该组中的任何单元格开始，通过仅移动到该组中共享一个共同边的另一个单元格，就可以到达该组中的任何其他单元格，则一组“#”单元格形成一个连通分量。连通分量的尺寸是该组中的单元格数量。
在一次操作中，Alex选择任意行$ r $（$ 1 \le r \le n $）和任意列$ c $（$ 1 \le c \le m $），然后将行$ r $和列$ c $中的每个单元格设置为“＃”。帮助Alex找到他在最多执行一次操作后，可以实现的“＃”个单元格的最大连通分量的最大可能大小。

## 说明/提示

在第四个测试用例中，Alex将第4行和第2列的所有单元格设置为“#”是最优的。这样做将导致“#”的最大连通分量大小为16。
在第五个测试用例中，Alex将第2行和第4列的所有单元格设置为“#”是最优的。这样做将导致“#”的最大连通分量大小为22。

## 样例 #1

### 输入

```
6
1 1
.
4 2
..
#.
#.
.#
3 5
.#.#.
..#..
.#.#.
5 5
#...#
....#
#...#
.....
...##
6 6
.#..#.
#..#..
.#...#
#.#.#.
.#.##.
###..#
6 8
..#....#
.####.#.
###.#..#
.##.#.##
.#.##.##
#..##.#.```

### 输出

```
1
7
11
16
22
36```

# 题解

## 作者：BrotherCall (赞：8)

## 题意

给定一个由 `#` 和 `.` 组成的 $n \times m$ 的网格，请进行以下的操作**一次**，使图中由 `#` 构成的连通块最大。

操作：选定一行**和**一列，将其全部变为 `#`。

输出操作后最大连通块点数。

## 思路

如果使用 [Easy Version](https://www.luogu.com.cn/article/ie390jho) 的思路，复杂度是 $O(n^2m^2)$ 的，无法接受。

由于选一行一列会有交集的连通块，所以无法单独考虑行或列再计算答案。

因此还是考虑枚举行和列，到这复杂度为 $O(nm)$。

既然暴力计算答案不行，那么我们就想想能不能预处理出答案。

对于一个连通块，向上延伸到 $l_1$ 行，向下延伸到 $r_1$ 行，向左延伸到 $l_2$ 列，向右延伸到 $r_2$ 列，那么它将对 $l_1 - 1$ 到 $r_1 + 1$ 行和 $l_2 - 1$ 到 $r_2 + 1$ 列有贡献。

这个贡献，我们用差分数组记录，比如行差分数组 $s_1$ 和连通块大小 $c$，我们将 $s_1$ 的 $l_1 - 1$ 的位置 $+c$，$r_1 + 2$ 的位置 $-c$，在差分数组构造完之后前缀和一下就行了。

列差分数组也是同理。

做到这里会发现枚举行列的话，会有连通块被重复计算了一次。那么考虑怎么减掉这个贡献。

再整一个二维数组 $S_{i,j}$，代表第 $i$ 行和第 $j$ 列重复计算的连通块贡献的差分数组。一个连通块有重复贡献的部分为左上角为 $(l_1 - 1,l_2 - 1)$，右下角为 $(r_1 + 1，r_2 + 1)$ 的矩形，把这个矩形二维差分的形式存在 $S$ 里，然后再转回来即可。

时间复杂度 $O(nm)$。

## 代码

[Link.](https://codeforces.com/contest/1985/submission/265564113)

---

## 作者：YFF1 (赞：1)

## 思路：
首先这道题是和它的弱化版不一样的。必须用到预处理。经过推理发现每个由井号组成的连通块有一个规律：画一个刚好能够框住该连通块的矩形，再以该矩形为重叠部分画一个十字，该十字所覆盖的面积即为这个连通块会波及到的区域。对于这样的面积我们用二维差分求解。连通块的部分用并查集，然后每次合并更新新的连通块的疆域。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e6+5;
int t,n,m,fa[N],dx[5]={1,0,-1,0},dy[5]={0,1,0,-1},sz[N],ans,a[N],d[N];
int nor[N],wes[N],eas[N],sou[N],hang[N],lie[N];
char c[N];
bool vis[N];
int change(int x,int y){
    return (x-1)*m+y;
}
bool check(int x,int y){
    return x>=1&&x<=n&&y>=1&&y<=m&&c[change(x,y)]=='#';
}
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
void merge(int u,int v){
    u=find(u),v=find(v);
    if(u==v)return ;
    nor[v]=min(nor[v],nor[u]),sou[v]=max(sou[v],sou[u]),wes[v]=min(wes[v],wes[u]),eas[v]=max(eas[v],eas[u]);
    fa[u]=v,sz[v]+=sz[u];
}//给集合扩展疆域 
void init(int sx,int tx,int sy,int ty,int sum){
    d[change(sx,sy)]+=sum,d[change(tx+1,sy)]-=sum,d[change(sx,ty+1)]-=sum,d[change(tx+1,ty+1)]+=sum;
}//差分处理 
signed main () {
    cin>>t;
    while(t--){
        scanf("%lld%lld",&n,&m);
        ans=0;
        for(int i=1;i<=max(n,m);i++)hang[i]=0,lie[i]=0;
        for(int i=1;i<=n*m;i++){
            fa[i]=i,vis[i]=0,sz[i]=1,d[i]=0;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                nor[change(i,j)]=sou[change(i,j)]=i;
                wes[change(i,j)]=eas[change(i,j)]=j;
            }
        }//四个数组记录每个集合的疆域 ，上下左右四个方向分别到哪里 
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)cin>>c[change(i,j)];
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(c[change(i,j)]=='.'){
                    hang[i]++,lie[j]++;
                    continue;//行列统计 
                }
                for(int k=0;k<4;k++){
                    int nx=i+dx[k];
                    int ny=j+dy[k];
                    if(check(nx,ny))merge(change(i,j),change(nx,ny));
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int pos=(i-1)*m+j;
                if(c[pos]=='#'){
                    pos=find(pos);
                    if(vis[pos])continue;
                    vis[pos]=1;
                    nor[pos]=max(1ll,nor[pos]-1),sou[pos]=min(n,sou[pos]+1);
                    wes[pos]=max(1ll,wes[pos]-1),eas[pos]=min(m,eas[pos]+1);//防止越界的操作 
                    init(1,nor[pos]-1,wes[pos],eas[pos],sz[pos]);
                    init(nor[pos],sou[pos],1,m,sz[pos]);
                    init(sou[pos]+1,n,wes[pos],eas[pos],sz[pos]);//把差分的面积（十字型）分3块处理 
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                d[change(i,j)]+=d[change(i-1,j)]+d[change(i,j-1)]-d[change(i-1,j-1)];//差分回来 
                ans=max(ans,d[change(i,j)]+hang[i]+lie[j]-(c[change(i,j)]=='.'));
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

