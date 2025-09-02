# [USACO12OPEN] Unlocking Blocks S

## 题目描述

一个鲜为人知的事实是，奶牛非常喜欢解谜！为了庆祝贝西的生日，农夫约翰给了她一个有趣的机械谜题让她来解决。这个谜题由三个实心物体组成，每个物体都是由 1x1 的单位正方形粘合在一起构成的。每个物体都是一个「连通」的形状，也就是说，你可以通过在物体上的正方形向北、南、东或西移动，从物体上的一个正方形到达另一个正方形。

一个物体可以通过不断地向北、南、东或西滑动一个单位来移动。谜题的目标是移动这些物体，使它们分开——即它们的边界框不再有任何正重叠。给定三个物体的形状和位置，你的任务是帮助贝西决定分开这些物体所需的最少滑动次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/flelqdzu.png)



## 说明/提示

物体 1 由 12 个正方形组成，物体 2 由 3 个正方形组成，物体 3 由 5 个正方形组成。物体的形状如上图所示。

如果我们将物体 3 向东滑动一个位置，然后将物体 2 向北滑动一个位置，然后将物体 1 向西滑动三个位置，那么三个物体的边界框将不再有任何重叠。

物体 1 由 12 块小正方体制成，物体 2 由 3 块小正方体制成，物体 3 由 5 块小正方体制成。最后的图像如上所示。（吃图？！）

```cpp
A：物体 1 方块 B：物体 2 方块 C：物体 3 方块 *：什么都没有
A A A A C
A * C C C
A B B * C
A * B A *
A A A A *
```
假如我们把物体 3 向东移一个单位，然后把物体 2 向北移一个单位，然后把物体 1 向西移三个单位，就满足了条件。

感谢 @姚起龙 提供翻译
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
12 3 5 
0 0 
1 0 
2 0 
3 0 
3 1 
0 1 
0 2 
0 3 
0 4 
1 4 
2 4 
3 4 
2 1 
2 2 
1 2 
2 3 
3 3 
4 3 
4 4 
4 2 
```

### 输出

```
5 
```

# 题解

## 作者：wleagle (赞：1)

**P3053 [USACO12OPEN] Unlocking Blocks S （DFS剪枝）**
## 题意

在 $0$ 到 $9$ 的 $10 \times 10$ 方格内给出 $3$ 个由小正方形拼出的块。这些块每次只能够上下左右移动 $1$ 格，不能重叠。问最小需要多少步才能让 $3$ 个块所在的最小矩形互不重叠。

## 解题思路

前两篇题解都是 BFS，因为每个块每步只有四个移动方向，而总移动步数直观的感觉就比较小，所以用自然就能想到用广搜找到第一个解即可。而如果用 DFS，总的状态空间随着步数是指数增长的，并且要遍历所有状态才能找到最短的解决办法，显然不是首选算法。但作为一个执（犟）着（种）的人，非要用深搜来写写看。

### 基本考虑

和其它题解类似，由于没有绝对坐标会出现负数，以及三个块会一起跑的问题，所以让一个块坐标不变，当需要让这个块移动，就让另外两个一起反向移动，效果一样。形状的重叠判断遍历一下就好，矩形的重叠用长宽和位置算一下就好。这些其它题解都说了，不赘述。

### 剪枝优化

DFS 既然要遍历，就需要充分剪枝：

1. 迭代过程中到达同一个状态，如果步数等于或大于当前记录的步数就返回。（基本操作）
2. 每个块的总步数不能超过 9，因为如果原来两个块在某个方向有 10 的重叠，那它们就不可能在另一个方向也有 10 的重叠，否则形状就重叠了。（几何约束）
3. 每个块所在矩形与不动的那个块，坐标差距不能超过 10，因为最终状态三个矩形一定是紧贴的（最小步数）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n[4], dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0}, ans = INT_MAX;
int iter;

struct block{
    vector<pair<int,int>>p;  // 每个点坐标
    int ox, oy, wid, hei;  // 所在矩形左下角坐标和宽、高
}blks[4];

int hashpos(int t1, int t2){  // 离散每个坐标
    return (t1 + 50)*100 + (t2 + 50);
}

int hashstat(){    // 离散2、3和1的相对位置，表示三个块的位置状态
    int ret = 0;
    ret += blks[2].ox - blks[1].ox + 50; 
    ret += (blks[2].oy - blks[1].oy + 50)*100;
    ret += (blks[3].ox - blks[1].ox + 50)*10000;
    ret += (blks[3].oy - blks[1].oy + 50)*1000000;
    return ret;
}

unordered_map<int, int> mp;  //记录实际形状所占据位置
unordered_map<int, int>vis;  //记录状态是否达到过，以及达到的步数


int check(int i, int dir){  // 判断形状能否移动
    bool flag = true;
    for(auto tp : blks[i].p){
        int newx = tp.first + dx[dir];
        int newy = tp.second + dy[dir];
        if(mp[hashpos(newx, newy)] && mp[hashpos(newx, newy)] != i){ // 看看新位置有没有被占据
            flag = false;
        }
    }
    return flag;
}

int check2(int dir){  // 判断2个形状一起能否移动 
    bool flag = true;
    for(auto tp : blks[2].p){
        int newx = tp.first + dx[dir];
        int newy = tp.second + dy[dir];
        if(mp[hashpos(newx, newy)] && mp[hashpos(newx, newy)] == 1){ // 看看2的新位置是否与1冲突
            flag = false;
        }
    }
    for(auto tp : blks[3].p){
        int newx = tp.first + dx[dir];
        int newy = tp.second + dy[dir];
        if(mp[hashpos(newx, newy)] && mp[hashpos(newx, newy)] == 1){ // 看看3的新位置是否与1冲突
            flag = false;
        }
    }
    return flag;
}

void mov(int i, int dir){  // 移动形状
    int tmp[100][100];
    memset(tmp, 0, sizeof(tmp));
    for(auto &tp : blks[i].p){
        if(!tmp[tp.first + 50][tp.second + 50])
            mp[hashpos(tp.first, tp.second)] = 0;
        tp.first += dx[dir];
        tp.second += dy[dir];
        mp[hashpos(tp.first, tp.second)] = i;
        tmp[tp.first + 50][tp.second + 50] = true; // 移动的新位置，不会被改零
    }
    blks[i].ox += dx[dir]; // 更新定位坐标
    blks[i].oy += dy[dir];
    return;
}

void mov2(int dir){  // 移动2,3
    int tmp[100][100];
    memset(tmp, 0, sizeof(tmp));
    for(auto &tp : blks[2].p){
        if(!tmp[tp.first + 50][tp.second + 50])
            mp[hashpos(tp.first, tp.second)] = 0;
        tp.first += dx[dir];
        tp.second += dy[dir];
        mp[hashpos(tp.first, tp.second)] = 2;
        tmp[tp.first + 50][tp.second + 50] = true; // 移动的新位置，不会被改零
    }
    for(auto &tp : blks[3].p){
        if(!tmp[tp.first + 50][tp.second + 50])
            mp[hashpos(tp.first, tp.second)] = 0;
        tp.first += dx[dir];
        tp.second += dy[dir];
        mp[hashpos(tp.first, tp.second)] = 3;
        tmp[tp.first + 50][tp.second + 50] = true; // 移动的新位置，不会被改零
    }
    blks[2].ox += dx[dir]; // 更新定位坐标
    blks[2].oy += dy[dir];
    blks[3].ox += dx[dir]; 
    blks[3].oy += dy[dir];
    return;
}

bool checkov(){  // 检查矩形是否无重叠
    bool ret = true;
    for(int i = 1; i <= 3; i ++){
        int nexti = i + 1 > 3? i - 2: i + 1;
        ret = (blks[i].ox > blks[nexti].ox ? blks[i].ox - blks[nexti].ox >= blks[nexti].wid : blks[nexti].ox - blks[i].ox >= blks[i].wid) || 
        (blks[i].oy > blks[nexti].oy ? blks[i].oy - blks[nexti].oy >= blks[nexti].hei : blks[nexti].oy - blks[i].oy >= blks[i].hei);
        if(!ret) return false;
    }
    return ret;
}


void dfs(int x1, int x2, int x3){  // 参数为每个块移动的步数
    if(x1 + x2 + x3 >= ans || x1 > 9 || x2 > 9 || x3 > 9) return;  //  大于等于已有结果就剪枝，每个块移动不超过9步，总数不超过9步。
    if(vis[hashstat()] && x1 + x2 + x3 >= vis[hashstat()]){   
        return;  // 如果有过同样相对位置，并且步数更大，舍弃
    }else{
        vis[hashstat()] = x1 + x2 + x3;
    }
    if(abs(blks[2].ox - blks[1].ox) > 10 || abs(blks[2].oy - blks[1].oy) > 10 ||
        abs(blks[3].ox - blks[1].ox) > 10 || abs(blks[3].oy - blks[1].oy) > 10 ) 
        return;  // 如果和1号坐标差大于10，舍弃
    if(checkov()){
        ans = min(ans, x1 + x2 + x3); // 更新ans
        return;
    }
    for(int i = 1; i <= 3; i++){
        for(int dir = 0; dir < 4; dir++){
            int cdir = (dir + 2 > 3? dir - 2: dir + 2); //反向
            if(i == 1){  // 1号不动，反向移动两个，固定1号确保三个不会一起跑
                if(check2(cdir)){
                    mov2(cdir);
                    dfs(x1 + 1, x2, x3);
                    mov2(dir);
                }
            }else{
                if(check(i, dir)){
                    mov(i, dir);
                    dfs(x1, x2 + (i == 2), x3 + (i == 3));
                    mov(i, cdir);
                }
            }
        }
    }
    return;
}

int main() {
    cin >> n[1] >> n[2] >> n[3];
    for(int i = 1; i <= 3; i++){
        int minx = INT_MAX, miny = INT_MAX, maxx = 0, maxy = 0;
        for(int j = 1 ; j <= n[i]; j++){
            int rx, ry;
            cin >> rx >> ry;
            blks[i].p.push_back({rx, ry});
            minx = min(minx, rx);
            miny = min(miny, ry);
            maxx = max(maxx, rx);
            maxy = max(maxy, ry);
            mp[hashpos(rx, ry)] = i;
        }
        blks[i].ox = minx;
        blks[i].oy = miny;
        blks[i].wid = maxx - minx + 1;
        blks[i].hei = maxy - miny + 1;
    }
    dfs(0, 0, 0);
    if(ans == INT_MAX) cout << "-1";
    else cout << ans;
    return 0;
}
```

---

## 作者：曹老师 (赞：1)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco12open-ub.html)

真的只是一个$BFS$！！！~~一个氧气都救不了的程序（快读+快写还$TLE$了一个点）~~

大体思路：对于每一种状态，我们枚举三个模块是否可以向左向右向上向下移动，如果可以移动，入队，继续搜索，队列中存整张图。**处理方法：对于队列中的图，不需要每一个点都存储。在输入的时候，我们可以根据点之间的相对位置求出这个模块的形状，存起来，这样队列中只需要对每一个模块存一个位置就可以，我们把这个位置叫做模块的代表点，这样就能推出其他的位置。**

关键的地方在于**如何判断是否已经入过队。**用集合配合类似哈希来处理，因为我们存储的只有三个点，六个值，第一感觉就是六维数组，然而六维数组会$MLE$。为什么呢？因为我们存储的不只是一个$10×10$的矩阵，而是$30×30$，我们也需要把看不到的地方存起来，这样的六维数组会变得很大，因此会$MLE$。

因为我们只是存了六个数，即三个模块的代表点的横纵坐标，所以就可以将这六个值哈希为一个六位数的值，放入集合，（突然想到这里好像可以用一位数组，请自行尝试）。

还需要两个很长很长的判断，**一个是判断当前状态是否就是答案，另一个是每一个模块的每一个方向是否可以移动。**这两个判断还是很好写的，不多说了。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<set>
#include<cstring>
using namespace std;

struct Node {
    int x , y;
};
Node shape[5][105] , sta[5];
struct Que {
    Node n[4];
    int cnt;
    Que(){};
    Que(Node nn1 , Node nn2 , Node nn3 , int ccnt) {
        n[1] = nn1 , n[2] = nn2 , n[3] = nn3 , cnt = ccnt;
    }
};
set<int>s;
queue<Que>q;
int n[4] , dx[4] = {0,0,-1,1} , dy[4] = {1,-1,0,0};
inline int mymin(int a , int b) { return a<b?a:b; }
inline int mymax(int a , int b) { return a>b?a:b; }

void read(int &x)
{
    char c = getchar(); x = 0;
    while(c < '0' || c > '9') c = getchar();
    while(c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
}

void put(int x)  
{  
    int num = 0; char c[15];
    while(x) c[++num] = (x%10)+48, x /= 10;
    while(num) putchar(c[num--]);
    putchar('\n'); 
}

int jud(Que x) {
    int hin[4] , hax[4] , zin[4] , zax[4] , map[35][35];
    memset(map , 0 , sizeof(map));
    for(int i=1; i<=3; i++) {
        hin[i] = zin[i] = 0x3f;
        hax[i] = zax[i] = 0;		
    }
    for(int i=1; i<=3; i++)
        for(int j=1; j<=n[i]; j++) {
            int xx , yy;
            xx = x.n[i].x + shape[i][j].x;
            yy = x.n[i].y + shape[i][j].y;
            hin[i] = mymin(hin[i] , xx);
            hax[i] = mymax(hax[i] , xx);
            zin[i] = mymin(zin[i] , yy);
            zax[i] = mymax(zax[i] , yy);
        }
    for(int i=1; i<=3; i++)
        for(int j=zin[i]; j<=zax[i]; j++)
            for(int k=hin[i]; k<=hax[i]; k++) {
                if(map[j+10][k+10])
                    return 0;
                map[j+10][k+10] = 1;	
            }
    return 1;
}

int mov(int x , int d , Que t) {
    int map[35][35];
    memset(map , 0 , sizeof(map));
    for(int i=1; i<=3; i++) {
        if(i == x) {
            t.n[i].x += dx[d];
            t.n[i].y += dy[d];
        }
        for(int j=1; j<=n[i]; j++) {
            int xx , yy;
            xx = t.n[i].x + shape[i][j].x;
            yy = t.n[i].y + shape[i][j].y;
            if(map[xx+10][yy+10])
                return 0;
            map[xx+10][yy+10] = 1;
        }
    }
    return 1;
}

void update(int &a , Que b) {
	a = b.n[1].x*100000+b.n[1].y*10000+b.n[2].x*1000+b.n[2].y*100+b.n[3].x*10+b.n[3].y;
}

int main() {
	read(n[1]) , read(n[2]) , read(n[3]); 
    for(int i=1; i<=3; i++) {
        Node a;
        read(a.x) , read(a.y);
        sta[i] = a;
        shape[i][1] = (Node){0,0};
        for(int j=2; j<=n[i]; j++) {
            int x , y;
            read(x) , read(y);
            shape[i][j] = (Node){x-a.x,y-a.y};
        }
    }
    q.push(Que(sta[1],sta[2],sta[3],0));
    s.insert(sta[1].x*100000+sta[1].y*10000+sta[2].x*1000+sta[2].y*100+sta[3].x*10+sta[3].y);
    while(!q.empty()) {
        Que u = q.front() , v;
        q.pop();
        if(jud(u)) {
        	put(u.cnt);
            return 0;
        }
        u.cnt++;
        for(int i=0; i<4; i++)
            for(int j=1; j<=3; j++)
                if(mov(j,i,u)) {
                    v = u;
                    Node t;
                    int m;
                    t.x = v.n[j].x + dx[i];
                    t.y = v.n[j].y + dy[i];
                    v.n[j] = t;
					update(m,v);
					if(s.find(m)==s.end()) {
						s.insert(m);
						q.push(v);
					}
                }
    }
    printf("-1");
    return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3053

---

## 作者：YCSluogu (赞：0)

## 这道题的 x 和 y 与一般的网格图不一样，这是数学概念上的坐标系！！！！

~~你这代码保AC吗~~  
~~那当然~~

#### 题意

就是给你三个拼图上，每一个方格所对应的坐标。要求你求出让三个拼图分开的最小步数。而相互离开也就是成功的条件是三个拼图所对应的矩形互不重合。
例如下图拼图：

![5Kg63t.png](https://z3.ax1x.com/2021/10/13/5Kg63t.png)

其对应的矩形就是红色框所包括的范围（原谅我的图画的丑）

没错这其实就是一道 `BFS` 的暴力搜索。对于每一步的状态转移判断稍微有点点麻烦而已。

首先考虑这道题目的状态设计，或许有人会考虑用 $(x_1, y_1, x_2, y_2, x_3, y_3, cost)$ 来表示三个拼图坐标偏移量与操作次数。不过需要考虑，偏移量可能为 __负数__ 且至多为 __$|10|$__ ，所以需要一个偏移量来防止负数下标
其时间复杂度和空间复杂度直接爆炸到 $O(46656000000)$
~~(计算机：看看这是人淦的嘛)~~，但是不难想到，我们可以固定其中一个拼图的位置，只对另外两个拼图坐标偏移量进行转移。

对于那个固定的拼图的移动，我们可以同时操作另外两个拼图进行反方向的移动。对于每个状态 $(x_1, y_1, x_2, y_2, cost)$，需要同时转移至
$(x_1 + fy_i, y_1 + fx_i, x_2, y_2, cost + 1)$ 与
$(x_1, y_1, x_2 + fx_i, y_2 + fy_i, cost + 1)$， 还有 $(x_1 - fx_i, y_1 - fy_i, x_2 - fx_i, y_2 - fy_i, cost + 1)$ (其实你把 `+` 改成 `-` 也不会有事)


code:

``` cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <queue>
#include <climits>
// #define int long long 

using namespace std;

// 防负数下标
const int P = 30;
const int fx[4] = {1, -1, 0, 0}, fy[4] = {0, 0, 1, -1};

inline int read() {
    char ch = getchar();
    int num = 0, w = 1;
    while (ch < '0' || ch > '9') w = ch == '-' ? -1 : 1, ch = getchar();
    while (ch >= '0' && ch <= '9') num = num * 10 + ch - '0', ch = getchar();
    return num * w;
};

struct node {
    int x, y;
    node() : x(0), y(0) { };
    node(int x_, int y_) : x(x_), y(y_) { };
};

struct box_t {
    int top = -INT_MAX, left = INT_MAX, down = INT_MAX, right = -INT_MAX;
    vector<node> c;
};

int n1, n2, n3;
box_t box[4];
int d[65][65][65][65];
bool has[65][65];
bool box3[65][65];
queue<node> q1, q2;

// 判断当前状态是否ok
bool ok(int x1, int y1, int x2, int y2) {
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (i == j) continue;
            int top = box[j].top, right = box[j].right, down = box[j].down, left = box[j].left;
            if (j == 1) top += y1, right += x1, down += y1, left += x1;
            if (j == 2) top += y2, right += x2, down += y2, left += x2;
            for (node n : box[i].c) {
                if (i == 1) n.x += x1, n.y += y1;
                if (i == 2) n.x += x2, n.y += y2;
                if (top >= n.y && n.y >= down && left <= n.x && n.x <= right) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 判断这样的偏移量是否可以
bool check(int x1, int y1, int x2, int y2) {
    int x, y;
    memset(has, false, sizeof(has));
    for (node i : box[1].c) {
        x = i.x + x1 + P, y = i.y + y1 + P;
        if (x < 1 || x > 60 || y < 1 || y > 60) return false;
        if (box3[y][x] || has[y][x]) {
            return false;
        }
        has[y][x] = true;
    }
    for (node i : box[2].c) {
        x = i.x + x2 + P, y = i.y + y2 + P;
        if (x < 1 || x > 60 || y < 1 || y > 60) return false;
        if (box3[y][x] || has[y][x]) {
            return false;
        }
        has[y][x] = true;
    }
    return true;
}

// 此处 x y 存储的是偏移量
void Record(int x1, int y1, int x2, int y2, int d_) {
    if (!check(x1, y1, x2, y2) || ~d[y1 + P][x1 + P][y2 + P][x2 + P]) {
        return ;
    }
    d[y1 + P][x1 + P][y2 + P][x2 + P] = d_;
    q1.push({x1, y1}), q2.push({x2, y2});
}

int bfs() {
    for (node i : box[3].c) {
        box3[i.y + P][i.x + P] = true;
    }
    Record(0, 0, 0, 0, 0);
    while (!q1.empty()) {
        int x1 = q1.front().x, y1 = q1.front().y,
            x2 = q2.front().x, y2 = q2.front().y;
        if (ok(x1, y1, x2, y2)) {
            return d[y1 + P][x1 + P][y2 + P][x2 + P];
        }
        for (int i = 0; i < 4; i++) {
            Record(x1 + fx[i], y1 + fy[i], x2, y2, d[y1 + P][x1 + P][y2 + P][x2 + P] + 1);
            Record(x1, y1, x2 + fx[i], y2 + fy[i], d[y1 + P][x1 + P][y2 + P][x2 + P] + 1);
            Record(x1 + fx[i], y1 + fy[i], x2 + fx[i], y2 + fy[i], d[y1 + P][x1 + P][y2 + P][x2 + P] + 1);
        }
        q1.pop(), q2.pop();
    }
    return -1;
}

int main() {
    int n[4];
    memset(d, -1, sizeof(d));
    n[1] = read(), n[2] = read(), n[3] = read();
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= n[i]; j++) {
            int x = read(), y = read();
            box[i].c.push_back({x, y});
            box[i].top  = max(box[i].top, y);
            box[i].left = min(box[i].left, x);
            box[i].right= max(box[i].right, x);
            box[i].down = min(box[i].down, y);
        }
    }
    cout << bfs();
    return 0;
}
```

~~管理辛苦了~~

---

