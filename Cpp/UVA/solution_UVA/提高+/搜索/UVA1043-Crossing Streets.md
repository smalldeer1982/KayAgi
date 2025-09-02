# Crossing Streets

## 题目描述

Peter 要从家到学校，他想要规划穿过马路条数最少的路线。

给定 $n$ 条马路的起始点与终点坐标（马路一定与坐标轴平行），以及 Peter 家和大学所在位置坐标。求 Peter 从家到大学的任意路径下最少穿过多少条马路。特别地，Peter 不能穿过马路之间的交点。

## 说明/提示

$1\le n\le 500$，所有输入的坐标绝对值不大于 $2\times 10^9$。

Translated by HYdroKomide.

## 样例 #1

### 输入

```
8
6 0 24 0
24 0 24 4
24 4 6 4
6 4 6 0
12 1 26 1
26 1 26 6
26 6 12 6
12 6 12 1
0 1 17 3
1
10 10 20 10
1 1 30 30
0```

### 输出

```
City 1
Peter has to cross 2 streets
City 2
Peter has to cross 0 streets```

# 题解

## 作者：HYdroKomide (赞：5)

### 题意：

求一条起点到终点的路径至少要跨过几条线段。

### 思路：

首先，观察到坐标值域比较大，但 $n$ 很小，所以需要离散化。

然后，我们化点为格，将每个单位方格的右上角坐标定为其坐标。对于每条马路，遍历它经过的每个坐标，将其两旁的方格的对应方向设为被阻断状态。

现在，对于每个方格，我们都存下了它上下左右是否被马路截断。由此，进行第一步染色 dfs，使用洪泛的思路，将所有没有被阻断的方格染成同一颜色。

接着，使用 bfs，从起点开始遍历，找到附近的相同颜色的方格就直接加入队首，不同颜色方格放入队尾并将存入双端队列的距离增大 $1$。

由于进行了离散化，整体复杂度为 $O(n^2)$，常数略大但无伤大雅。

### 程序如下：
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<cstring>
#include<vector>
#include<deque>
using namespace std;
const int N=2e3+5;
int n,t,x1[N],y1[N],x2[N],y2[N],bx[N],by[N],xh,yh,xu,yu,cntx,cnty,col[N][N],cnt,dis[N][N];
bool vis[N][N];
map<int,int>mpx,mpy;
struct BLOCK{bool up,dn,lf,rt;}stat[N][N];
struct NODE{int x,y,dis;};
deque<NODE>q;
void dfs(int x,int y,int cur){
    if(x<0||y<0||x>cntx+2||y>cnty+1)return;
    if(vis[x][y])return;
    if(cur==0)cur=++cnt;
    col[x][y]=cur;
    vis[x][y]=true;
    if(!stat[x][y].up)dfs(x,y+1,cur);//向四周没有马路的方向直接进行洪泛
    if(!stat[x][y].dn)dfs(x,y-1,cur);
    if(!stat[x][y].lf)dfs(x-1,y,cur);
    if(!stat[x][y].rt)dfs(x+1,y,cur);
}
void bfs(){
	q.push_front({xh,yh,0});
	while(!q.empty()){
		int x=q.front().x,y=q.front().y,d=q.front().dis;
		q.pop_front();
		if(vis[x][y]||x<0||y<0||x>cntx+2||y>cnty+2)continue;
		vis[x][y]=true;
		dis[x][y]=d;
		if(x!=0&&col[x-1][y]==col[x][y])q.push_front({x-1,y,d});//相同的放入对首
		if(x!=cntx+1&&col[x+1][y]==col[x][y])q.push_front({x+1,y,d});
		if(y!=0&&col[x][y-1]==col[x][y])q.push_front({x,y-1,d});
		if(y!=cnty+1&&col[x][y+1]==col[x][y])q.push_front({x,y+1,d});
		q.push_back({x-1,y,d+1});//其余放入队尾，不用担心重复问题因为有vis数组判断
		q.push_back({x+1,y,d+1});
		q.push_back({x,y-1,d+1});
		q.push_back({x,y+1,d+1});
	}
}
int main(){
    while(scanf("%d",&n)){
    	t++;
        if(n==0)break;
        cntx=0,cnty=0,cnt=0;
        memset(stat,0,sizeof(stat));
        memset(vis,false,sizeof(vis));
        memset(col,0,sizeof(col));
        for(int i=1;i<=n;i++){
            scanf("%d%d%d%d",&x1[i],&y1[i],&x2[i],&y2[i]);
            bx[++cntx]=x1[i],bx[++cntx]=x2[i];
            by[++cnty]=y1[i],by[++cnty]=y2[i];
        }
        scanf("%d%d%d%d",&xh,&yh,&xu,&yu);
        bx[++cntx]=xh,bx[++cntx]=xu;
        by[++cnty]=yh,by[++cnty]=yu;
        sort(bx+1,bx+cntx+1);
        sort(by+1,by+cnty+1);
        cntx=unique(bx+1,bx+cntx+1)-bx-1;
        cnty=unique(by+1,by+cnty+1)-by-1;
        for(int i=1;i<=cntx;i++)mpx[bx[i]]=i;
        for(int i=1;i<=cnty;i++)mpy[by[i]]=i;//使用map离散化
        for(int i=1;i<=n;i++){
            x1[i]=mpx[x1[i]],x2[i]=mpx[x2[i]];
            y1[i]=mpy[y1[i]],y2[i]=mpy[y2[i]];
            if(y1[i]==y2[i]){
                if(x1[i]>x2[i])swap(x1[i],x2[i]);
                for(int j=x1[i]+1;j<=x2[i];j++){
                    stat[j][y1[i]].up=true;
                    stat[j][y1[i]+1].dn=true;
                }
            }
            else{
                if(y1[i]>y2[i])swap(y1[i],y2[i]);
                for(int j=y1[i]+1;j<=y2[i];j++){
                    stat[x1[i]][j].rt=true;
                    stat[x1[i]+1][j].lf=true;
                }//更新方格四周的马路阻拦情况
            }
        }
        xh=mpx[xh],xu=mpx[xu];
        yh=mpy[yh],yu=mpy[yu];
        for(int i=0;i<=cntx+1;i++)
            for(int j=0;j<=cnty+1;j++)
                dfs(i,j,0);
        memset(vis,false,sizeof(vis));
        memset(dis,0,sizeof(dis));
        bfs();
        printf("City %d\n",t);
		printf("Peter has to cross %d streets\n",dis[xu][yu]);
    }
    return 0;
}
```

### THE END

---

