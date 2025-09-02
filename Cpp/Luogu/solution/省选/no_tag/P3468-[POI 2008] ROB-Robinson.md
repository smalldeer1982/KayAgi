# [POI 2008] ROB-Robinson

## 题目描述

Tossed by the storm on a deserted island, Robinson built himself a boat    so that he could go out to the sea and seek out human domicile.

He is an experienced sailor, therefore he built the boat with accordance to the rules    of craftsmanship: it has a longitudinal axis of symmetry and an appropriate    shape. The boat's prow is thin, and it widens gradually towards the boat's centre,    only to gradually narrow once again towards the stern.

In particular, at some point in the middle the boat is wider than both at the    prow and stern.

Unfortunately, Robinson has launched his boat in a most improper space: there    is extremely thick reed all around. It is, moreover, so stiff that the boat    cannot break through. Perhaps Robinson can get to the high seas by carefully    manoeuvring between the reed.

Due to lack of manoeuvrability, the boat can move forward and backward and    even sidewards (leftward or rightward), but it cannot turn.

It is thus allowed, and may be in fact necessary, that the boat moves with    its stern or broadside to the front.

You are to judge if Robinson can get to the high seas.

To make your task easier the island and its surroundings will be    represented by a square map divided into square unit fields, each    occupied by either water, part of Robinson's boat or an obstacle, eg.

land or reed. Initially the boat is set parallel to one of the cardinal    directions, ie. its longitudinal axis of symmetry is parallel to this    direction and the axis bisects the unit fields it is covered with.

We assume that the high seas starts where the map ends.

Hence Robinson may get to the high seas if his boat can leave    the area depicted in the map.

A single move consists in moving the boat to a side-adjacent    field in a chosen direction (north, south, east or west).

The move is permissible if both before and after it the boat    remains entirely in water (it does not occupy a field with an    obstacle).

Task      You are to write a programme that                        reads the map's description from the standard input,                      calculates the minimum possible number of boat's moves that          suffice to completely leave the area depicted in the map,                      writes out this number to the standard output.

被风暴抛弃在荒岛上的鲁滨逊（又译鲁滨孙）自己造了一条船，这样他就可以出海去寻找有人类居住的地方。

他是一位经验丰富的水手，因此他根据技术规程建造了它。它有一条纵向的对称轴，以及适于航行的外形：船头较尖，向船中逐渐扩宽，到船尾又逐渐收窄。

特别的是，船中的一些点比船头和船尾都宽。

可是很不幸，鲁滨逊在最不合适的位置让他的船下了水：周围有极其厚的芦苇。此外，这条船太僵硬以至于它无法突破芦苇。不过或许鲁滨逊可以通过在芦苇中小心翼翼地操纵船去往公海。

由于船太不灵活，船可以前进、后退甚至横着（向左或向右）移动，但它不能掉头。

允许船的船尾或者船舷在前进行移动，事实上这可能是必要的。

你需要判断鲁滨逊是否可以到达公海。

为了简化你的工作，岛屿和周围的环境将由一张划分成方格的正方形地图表示，每格只可能是水、鲁滨逊船的一部分或障碍物（比如说岛屿和芦苇）。最初船平行于一个主要方向（换句话说，即其纵向对称轴平行于此方向且其平分其覆盖的方格）

我们假定地图之外就是公海。

因此，如果他的船可以离开地图描绘的区域，鲁滨逊也许就能到达公海了。

一步表现为船往选定的方向（北，南，东或西）移动一格。

如果移动前后的船保持整个在水中（不占据任何有障碍物的格子），那么这个移动是合法的。

你的任务是编写一个程序，从标准输入中读取地图的描述，计算船离开地图描述的区域的最少步数，并输出至标准输出。


## 样例 #1

### 输入

```
10
..........
..........
..r.......
.rrrX.....
rrrrr.....
.rrr......
X.r.......
.Xr.......
..........
..........```

### 输出

```
10```

# 题解

## 作者：kczno1 (赞：7)

求出对于船的左上角，在哪些点是合法的，那么$bfs$即可。(注意左上角有可能超出地图，即坐标有可能为负)


但要求船全部合法比较麻烦，可以只考虑各个边界的合法。


比如从上往下走时，就只用考虑移动后下边界的合法，因为其他的点都是和原来的船体重叠的。


考虑在$(x,y)$处下边界合法就是$s[x+d_{i}][y+i]=0(i=0..k)$，其中$d_{i}$表示船体从左往右第$i$列下边界的行，$k$表示船宽。


那么枚举列，将其他列分别移动$d_{i}$位再$or$起来，就得到了这一列的答案。


用$bitset$实现，时间$O(n^3/32)$

```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
    if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
    if(x<y)x=y;
}
typedef unsigned int ui;
#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=2000+5;
int n,u;
template <int N>
struct BITSET
{
static const int U=N/32+2;
ui a[U];
void set1(int x)
{
    a[x/32]|=1<<(x&31);
}
bool operator [](int x)
{
    return a[x/32]&(1<<(x&31));
}
};
void or_left_move(ui *a,ui *b,int x)//a|=b<<x  b[0..u]
{
    int dk=x/32,dl=x&31;
    if(!dl)
    {
        rep(i,0,u)a[i+dk]|=b[i];
        return ;
    }
    rep(i,0,u)
    {
        a[i+dk]|=b[i]<<dl;
        a[i+dk+1]|=b[i]>>32-dl; 
    }
}
struct F
{
char s[N][N];
BITSET<N>a[N];
BITSET<N*2>cant[N*2];
int x0,y0;//left up
int x1,y1;//right down
int d[N];
void init()
{
    x0=y0=n;
    rep(i,1,n)
    rep(j,1,n)
    if(s[i][j]=='X')
     a[j].set1(i);
    else
    if(s[i][j]=='r')
    {
        chmin(x0,i);chmin(y0,j);
        chmax(x1,i);chmax(y1,j);
        chmax(d[j],i);
    }
    rep(j,-n,n)
    rep(j2,max(1,j),min(n,j+y1-y0))
    if(d[y0+j2-j]) or_left_move(cant[N+j].a,a[j2].a,N-(d[y0+j2-j]-x0)); 
}
bool judge(int x,int y)
{
    return !cant[N+y][x+1+N];
}
};
F f[4];//f[0] judge if can move down;f[1] up;f[2] right;f[3] left;
int g[N*2][N*2];
struct point
{
    short x,y;
};
point q[N*N*2*2];int tail;
int dis;
void out()
{
    cout<<dis;exit(0);
}
void push(short x,short y)
{
    q[++tail]=(point){x,y};g[N+x][N+y]=dis;
}

int main()
{
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    cin>>n;u=n/32;
    rep(i,1,n)scanf("%s",f[0].s[i]+1);
    rep(i,1,n)
    rep(j,1,n)f[1].s[n-i+1][n-j+1]=f[2].s[j][n-i+1]=f[3].s[n-j+1][i]=f[0].s[i][j];
    rep(i,0,3)f[i].init(); 
    memset(g,-1,sizeof(g));
    push(f[0].x0,f[0].y0);
    rep(head,1,tail)
    {
        short x=q[head].x,y=q[head].y;
        dis=g[N+x][N+y]+1;
        if(g[N+x+1][N+y]==-1&&f[0].judge(x,y))
        {
            if(x==n) out();
            push(x+1,y);
        }
        int _x=x+f[0].x1-f[0].x0,_y=y+f[0].y1-f[0].y0;
        //(_x,_y)
        if(g[N+x-1][N+y]==-1&&f[1].judge(n-_x+1,n-_y+1))
        {
            if(_x==1) out();
            push(x-1,y); 
        }
        //(_x,y)
        if(g[N+x][N+y+1]==-1&&f[2].judge(y,n-_x+1))
        {
            if(y==n) out();
            push(x,y+1);
        }
        //(x,_y)
        if(g[N+x][N+y-1]==-1&&f[3].judge(n-_y+1,x))
        {
            if(_y==1) out();
            push(x,y-1);
        }
    }
    puts("NIE");
}
```

---

