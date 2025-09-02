# Mirror Room

## 题目描述

Imagine an $ n×m $ grid with some blocked cells. The top left cell in the grid has coordinates $ (1,1) $ and the bottom right cell has coordinates $ (n,m) $ . There are $ k $ blocked cells in the grid and others are empty. You flash a laser beam from the center of an empty cell $ (x_{s},y_{s}) $ in one of the diagonal directions (i.e. north-east, north-west, south-east or south-west). If the beam hits a blocked cell or the border of the grid it will reflect. The behavior of the beam reflection in different situations is depicted in the figure below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF274E/b39481b94e1363a19d54d5d4b6abfa8c6904b83d.png)After a while the beam enters an infinite cycle. Count the number of empty cells that the beam goes through at least once. We consider that the beam goes through cell if it goes through its center.

## 样例 #1

### 输入

```
3 3 0
1 2 SW
```

### 输出

```
6
```

## 样例 #2

### 输入

```
7 5 3
3 3
4 3
5 3
2 1 SE
```

### 输出

```
14
```

# 题解

## 作者：Ignotus (赞：12)

题意大概是说给你一个 $n\times m$ 的平面，其中有 $k$ 个格子是障碍物，有一束激光从某一个空格子中央出发沿某一对角线前行，遇到边界或者障碍物就按题意的要求反射。问这束激光如果无限反射下去会经过多少个空格子。  

解决这个问题，我们首先需要发现一些性质：

+ 性质 $1$：激光在走过一段路程后会发生循环，即再一次走到其一开始的位置且沿着开始的方向。发生这种循环之前激光反射的次数为 $\Theta(n+m+k)$。  
证明： 对于一个空的 $n\times m$ 的网格，共有 $\Theta(n+m)$ 条对角线，而每个障碍将原先过障碍点的对角线分成了两部分，相当于斜向线段的数量增加 $2$。所以共有 $\Theta(n+m+k)$ 条斜向线段，激光反射的次数也为 $\Theta(n+m+k)$。  

+ 性质 $2$：激光不会穿过同一格子的两条对角线。  
证明：将格子黑白染色，可以发现激光穿过主对角线时总是经过同一种颜色的格子，经反射后在次对角线上又总是经过另一种颜色的格子，如果激光正在经过的主/次对角线互换，格子的颜色也一定互换。所以同一个格子不可能被激光经过两次。

利用性质 $1$，我们可以模拟激光的轨迹，每次跳到激光下一次反射的位置，直到循环为止。考虑用 map 记录添加的障碍物，用 set 记录每条对角线上的障碍物，每次查找按当前方向行走遇到的第一个障碍物即可。

一些细节：  
+ 一个格子的其中一条对角线有可能被正反方向经过两次。不难发现在这种情况下所有激光会经过的格子在循环前都会被经过两次，将答案除以 $2$ 即可。  
+ 考虑边界时直接将边界也看作障碍物加进 set 中即可。  
+ 在一开始可以先将激光移动到第一个障碍物上，然后将再回到第一个障碍物的时候视为完成了一个循环，方便统计答案。

代码：  
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <map>
#include <set>

#define int long long
using namespace std;

const int N = 2e5 + 10;
const int dx[] = {-1, -1, 1, 1};
const int dy[] = {1, -1, -1, 1};

int rd(){
    int a = 0, f = 1;
    char c = getchar();
    while(!isdigit(c)){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(isdigit(c)) a = a * 10 + c - '0', c = getchar();
    return a * f;
}

int n, m, k;
int x, y, d, tx, ty, td, revis = 1; // revis 代表这个格子在一次循环中被经过了多少次
int ans;
char dir[5];

map <int, int> mp[N]; // 存障碍物
set <pair<int, int> > s[2][N]; // 存对角线，0 代表次对角线，1 代表主对角线

void add(int x, int y){ // 添加障碍物
    mp[x][y] = 1;
    s[0][x + y].insert(make_pair(x, y));
    s[1][x - y + m + 1].insert(make_pair(x, y));
}

void work(int op){ // 寻找下一个反射的位置
    auto it = s[d & 1][d & 1 ? x - y + m + 1 : x + y].lower_bound(make_pair(x, y));
    if(d < 2) --it;
    if(op) ans += abs(x - (*it).first); // *it 优先级低，要加括号！
    x = (*it).first - dx[d];
    y = (*it).second - dy[d];
    int cnt = mp[x + dx[d]].count(y) + mp[x].count(y + dy[d]);
    if(!cnt || cnt == 2) d = (d + 2) % 4, revis = 2;
    else if(mp[x + dx[d]].count(y)) y += dy[d], d ^= 3;
    else x += dx[d], d ^= 1;
}

signed main(){
    n = rd(), m = rd(), k = rd();
    for(int i = 0; i <= n + 1; ++i) add(i, 0), add(i, m + 1);
    for(int i = 0; i <= m + 1; ++i) add(0, i), add(n + 1, i);
    for(int i = 1, u, v; i <= k; ++i){
        u = rd(), v = rd();
        add(u, v);
    }
    x = rd(), y = rd();
    scanf("%s", dir);
    if(dir[0] == 'N' && dir[1] == 'E') d = 0;
    if(dir[0] == 'N' && dir[1] == 'W') d = 1;
    if(dir[0] == 'S' && dir[1] == 'W') d = 2;
    if(dir[0] == 'S' && dir[1] == 'E') d = 3;

    work(0);
    tx = x, ty = y, td = d;
    work(1);
    while(x != tx || y != ty || d != td) work(1); // 一直统计答案到产生循环为止

    printf("%lld\n", ans / revis);
    return 0;
}
```


---

## 作者：Porsche (赞：6)

好像没有人发题解？！？

   光线只有遇上边界或堵塞的格子才会改变方向，所以改变方向的位置是有限的，光线的方向又最多只有四种，所以光线在循环之前改变方向的次数是O（n+m+k）级别的。我们可以模拟光线的移动。已知光线位置和光线的方向，使用二分的方法可以在O（log k）的时间复杂度内求出即将改变方向的位置和改变后的方向。

   我们暂把光线的位置和方向称为光线的状态。一种状态能转移到一种且仅有一种状态。如果从状态a能转移到状态b，那么b反向后的状态能转移到a反向后的状态。所以一种状态能从一种且仅有一种状态转移而来。这就像是一种置换，所以从初始状态出发，必定会回到初始状态，并且回到初始状态之前不会重复经过某种状态。

   我们对网格进行染色，有邻边的格子颜色不同，形成一个二分图。根据题目中光线反射的方式，可以发现，每当光线沿西北、东南方向前进时，只会经过一种颜色的网格，每当光线沿东北、西南方向前进时，只会经过另一种颜色的网格。所以光线在某一个格子中心时，要么只会是西北、东南方向之一，要么只会是东北、西南方向之一。

   这样，如果一次循环内一个格子被重复经过，只有可能是光线以相反的两个方向进入，并且一次循环内一个格子最多被经过两次。一个格子被经过两次，所有被光线经过的格子都会被经过两次。易知，如果光线在前进过程中出现过如下两种反射，所有格子就会被经过两次。只需在模拟的过程中记录是否出现过这两种情况即可。
   
   代码有点恶心
```cpp
#include<bits/stdc++.h>
using namespace std;
struct rec{int x,y,d;};
int n,m,k;
long long ans;
set<int>s1[200010],s2[200010];
map<pair<int,int>,bool>mp;
int getid(int x,int y,int d){return d==1?x-y+m+1:x+y;}
bool same(rec a,rec b){if(a.x==b.x&&a.y==b.y&&a.d==b.d)return 1;return 0;}
bool check(int x,int y){return mp[make_pair(x,y)];}
void add(int x,int y)
{
    s1[getid(x,y,1)].insert(x);
    s2[getid(x,y,2)].insert(x);
    mp[make_pair(x,y)]=1;
}
pair<rec,int> dfs(rec u)
{
    rec re;
    set<int>::iterator it;
    if(u.d==1)
    {
        it=s1[getid(u.x,u.y,1)].lower_bound(u.x);it--;
        re.x=u.x-(abs(*it-u.x)-1);
        re.y=u.y-(abs(*it-u.x)-1);
        if(check(re.x-1,re.y)&&check(re.x,re.y-1))re.d=3;
        else if(check(re.x-1,re.y)){re.y--;re.d=4;}
        else if(check(re.x,re.y-1)){re.x--;re.d=2;}
        else re.d=3;
    }
    if(u.d==2)
    {
        it=s2[getid(u.x,u.y,2)].lower_bound(u.x);it--;
        re.x=u.x-(abs(*it-u.x)-1);
        re.y=u.y+(abs(*it-u.x)-1);
        if(check(re.x-1,re.y)&&check(re.x,re.y+1))re.d=4;
        else if(check(re.x-1,re.y)){re.y++;re.d=3;}
        else if(check(re.x,re.y+1)){re.x--;re.d=1;}
        else re.d=4;
    }
    if(u.d==3)
    {	
        it=s1[getid(u.x,u.y,1)].lower_bound(u.x);
        re.x=u.x+(abs(*it-u.x)-1);
        re.y=u.y+(abs(*it-u.x)-1);
        if(check(re.x+1,re.y)&&check(re.x,re.y+1))re.d=1;
        else if(check(re.x+1,re.y)){re.y++;re.d=2;}
        else if(check(re.x,re.y+1)){re.x++;re.d=4;}
        else re.d=1;
    }
    if(u.d==4)
    {
        it=s2[getid(u.x,u.y,2)].lower_bound(u.x);
        re.x=u.x+(abs(*it-u.x)-1);
        re.y=u.y-(abs(*it-u.x)-1);
        if(check(re.x+1,re.y)&&check(re.x,re.y-1))re.d=2;
        else if(check(re.x+1,re.y)){re.y--;re.d=1;}
        else if(check(re.x,re.y-1)){re.x++;re.d=3;}
        else re.d=2;
    }
    return make_pair(re,abs(*it-u.x));
}
bool judge(rec u)
{
    rec re=u;
    do
    {
        pair<rec,int> cur=dfs(u);
        ans+=(long long)cur.second;
        switch(cur.first.d)
        {
        	case 1:if(u.d==3)return 0;break;
        	case 2:if(u.d==4)return 0;break;
        	case 3:if(u.d==1)return 0;break;
        	case 4:if(u.d==2)return 0;break;
        }
        u=cur.first;
    }while(!same(re,u));
    return 1;
}
void pre_build()
{
    for(int i=0;i<=m+1;i++)
    {
        add(0,i);
        add(n+1,i);
    }
    for(int i=1;i<=n;i++)
    {
        add(i,0);
        add(i,m+1);
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    pre_build();
    for(int i=1;i<=k;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    int x,y,d;
    char ch[5];
    scanf("%d%d%s",&x,&y,ch+1);
    if(ch[1]=='N'&&ch[2]=='W')d=1;
    if(ch[1]=='N'&&ch[2]=='E')d=2;
    if(ch[1]=='S'&&ch[2]=='E')d=3;
    if(ch[1]=='S'&&ch[2]=='W')d=4;
    rec st={x,y,d};
    st=dfs(st).first;
    if(!judge(st))
    {
        ans--;
        switch(st.d)
        {
        	case 1:st.d=3;break;
        	case 2:st.d=4;break;
        	case 3:st.d=1;break;
        	case 4:st.d=2;break;
        }
        judge(st);
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Polaris_Australis_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF274E)

## 题意

$n \times m$ 的平面，有 $k$ 个障碍物，激光碰到障碍物后会反射，给定激光初始位置和方向，求激光能经过多少障碍物。

## 解法

首先需要证明两个性质：

1. 激光反弹次数为 $O(n+m+k)$ 级别。

* 证明：对角线级别为 $O(n+m)$，有 $k$ 个障碍物把这些对角线分为 $O(k)$ 份，总数为 $O(n+m+k)$。

2. 同一个方格不会经过交叉激光。

* 证明：类似黑白染色，把相邻的染成不同颜色，然后发现，同一方向上的路径所经过的放格颜色总相同，因为每次转向一定会变换到相邻的颜色不同的格子。

根据第一个性质，可以想到快速找到下一次碰到障碍的位置，可以利用 set 存对角线上的点，每次 $ans$ 累加移动距离，由于性质二，不会有交叉算重的情况，如果反向了怎么办？

处理方法：从当前点能够到达的某个边界（或障碍物附近）开始运行代码，过程中如果出现走反向边的情况标记一下，容易证明，一旦走到反向边，激光会按照原路返回，所以每个点会被恰好计算两次，除以二即可，如果没有经过反向，则每个点只会经过一次（因为既没有交叉，又没有反向），所以，每个点只会经过一次。

一些细节：边界也要算作障碍。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Std{
    int n,m,k,x,y,d,tx,ty,td,cs=1,ans;
    set<pair<int,int> >cset[2][200010];
    unordered_map<int,int>cmap[100010];
    const int dx[] = {1, -1, -1, 1},dy[] = {-1, -1, 1, 1};
    char s[5];
    inline void add(int a,int b){
        cmap[a][b]=1;
        cset[0][a+b].insert(make_pair(a,b));
        cset[1][b-a+n].insert(make_pair(a,b));
    }
    void work(bool opt){
        auto it=cset[d&1][d&1?y-x+n:x+y].lower_bound(make_pair(x,y));
        if(d==1||d==2)it--;
        if(opt)ans+=abs(x-(*it).first);
        x=(*it).first-dx[d],y=(*it).second-dy[d];
        int cnt=cmap[x+dx[d]].count(y)+cmap[x].count(y+dy[d]);
        if((!cnt)||cnt==2){
            cs=2;
            d^=2;
        }
        else if(cmap[x+dx[d]].count(y)){
            y+=dy[d];
            d^=1;
        }
        else{
            x+=dx[d];
            d^=3;
        }
    }
    int main(){
        scanf("%lld%lld%lld",&n,&m,&k);
        int a,b;
        for(int i=1;i<=k;++i){
            scanf("%lld%lld",&a,&b);
            add(a,b);
        }
        for(int i=1;i<=n;++i){
            add(i,0);
            add(i,m+1);
        }
        for(int i=1;i<=m;++i){
            add(0,i);
            add(n+1,i);
        }
        scanf("%lld%lld",&x,&y);
        scanf("%s",s+1);
        if(s[1]=='S')d+=2;
        if((s[1]=='S'&&s[2]=='E')||(s[1]=='N'&&s[2]=='W'))++d;
        add(0,0);
        add(0,m+1);
        add(n+1,0);
        add(n+1,m+1);
        work(false);
        tx=x;
        ty=y;
        td=d;
        work(true);
        while(x!=tx||y!=ty||d!=td)
        {
            work(true);
        }
        printf("%lld\n",ans/cs);
        return 0;
    }
}
#undef int
int main(){
    return Std::main();
}
```


---

