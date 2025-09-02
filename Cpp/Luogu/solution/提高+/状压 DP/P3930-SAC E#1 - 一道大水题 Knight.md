# SAC E#1 - 一道大水题 Knight

## 题目背景

毒奶色和F91是好朋友。


## 题目描述

他们经常在一起玩一个游戏，不，不是星际争霸，是国际象棋。

毒奶色觉得F91是一只鸡。他在一个n×n的棋盘上用黑色的城堡（车）、骑士（马）、主教（象）、皇后（副）、国王（帅）、士兵（卒）摆了一个阵。

然而F91觉得毒奶色是一只鸡。他发起了挑战：他要操纵一个白色骑士，不经过任何一个棋子的攻击范围（F91可以连续行动，而毒奶色的棋子不会动，除非白骑士进入了对方的攻击范围），并击杀毒奶色的国王（即进入黑国王所在的位置）。

请告诉F91他最少需要多少步骤来完成这一项壮举。


注意：

1.当F91的白骑士走到毒奶色的棋子所在的格子上的时候，会击杀（吃掉）该棋子。这个棋子也就不再对F91的白骑士有威胁了。

2.如果白骑士开场就在黑子的攻击范围内，则立刻被击杀、F91立刻失败。

3.即使白骑士在攻击王的瞬间进入了其他棋子攻击范围（即其他棋子“看护”着王所在的格子），依然算F91获胜。


攻击范围：


城堡：横、竖方向所有位置，直到被一个其他棋子阻拦。

```cpp
..#..
..#..
##C##
..#..
..#..
```

骑士：横2竖1或者横1竖2的所有位置（最多8个，类似日字）。

```cpp
.#.#.
#...#
..K..
#...#
.#.#.
```

主教：斜向（45°）所有位置，直到被一个其他棋子阻拦。

```cpp
#...#
.#.#.
..B..
.#.#.
#...#
```

皇后：城堡和主教的结合体（既能横/竖向攻击，也能45°角斜向攻击，直到被其他棋子阻挡）。

```cpp
#.#.#
.###.
##Q##
.###.
#.#.#
```

国王：身边8连通位置的8个格子。

```cpp
.....
.###.
.#X#.
.###.
.....
```

士兵：左下方/右下方（45°）的格子（最多2个）。

`````
.....
.....
..P..
.#.#.
.....
```

其中字母表示棋子类型，参考输入格式。

‘#’表示可攻击范围。


## 说明/提示

**输入最多包含5组数据。**

对于20%的数据，毒奶色只有国王。n <= 8。

对于30%的数据，毒奶色只有国王、骑士。n <= 8。

对于60%的数据，毒奶色只有国王、骑士、王后。n <= 50。

对于100%的数据，毒奶色可以有全套16颗棋子（2城堡，2骑士，2主教，1后，1王，8兵）。n <= 50。


温馨提示：

时间限制可能比想象之中还要更紧一点，请注意实现细节以保证性能。



样例2解释：

一种可行的做法是：

```cpp
......X.
.3..6...
.O5.....
4.2P.Q.C
1....B..
........
...K....
........
```

## 样例 #1

### 输入

```
8
...X....
........
........
........
........
........
........
......O.```

### 输出

```
4```

## 样例 #2

### 输入

```
8
......X.
........
.O......
...P.Q.C
.....B..
........
...K....
........```

### 输出

```
7```

# 题解

## 作者：c201904 (赞：6)

这道题，其实完全不需要你去你用什么高级算法，其实需要你的，是耐心地爆搜，像2015年斗地主一样了，但有一个坑，我没注意到，于是得了80分，那就是：因为进攻方是骑士，所以进攻方是不可能吃到骑士的。大体呢就是先把开始点和结束点记录下来，然后开结构体，结构体里面要有它当时棋盘的状态和进攻方所在位置，然后把那些敌方的记录下来，每次往8个方向枚举，符合条件(就是没跳出棋盘，不会被地方吃到) 。因为宽搜要快一些，所以我们用宽搜，要开一个队列，搜到了第一个吃到国王的就跳出来，返回步数。搜完后还不行，就返回1.

注意：如果跳到了敌方的一个棋子上，就要把那颗棋子去掉！

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;
const int inf=0x3f3f3f3f;
struct wo{
    char b[60][60];//棋盘状态
    int x,y;//
};
queue<wo>p;
char a[60][60];
int vis[60][60];//记录有多少颗敌方棋子能吃到自己 
int step[60][60];//记录到达当前点至少要用多少步 
int n;
int dx[8]={1,1,-1,-1,2,2,-2,-2};//八个方向 
int dy[8]={2,-2,2,-2,1,-1,1,-1};//八个方向 
int startx,starty,endx,endy;//开始点和结束点 
int judge(int x,int y){
    if(x<=0||x>n)return 0;
    if(y<=0||y>n)return 0;
    if(vis[x][y])return 0;
    return 1;
}
void queen(int x,int y){//皇后攻击范围内的 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i==x)||(j==y)||((i+j)==(x+y))||((i-j)==(x-y)))//横坐标一样，竖坐标一样，或者在同一条斜线上 
            vis[i][j]++;//能攻击到这一点 
        }
    }
    vis[x][y]--;//自己攻击不了自己！ 
}
void castle(int x,int y){//城堡攻击范围 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i==x)||(j==y))//横坐标一样或竖坐标一样 
            vis[i][j]++;//能攻击到这一点 
        }
    }
    vis[x][y]--;//自己攻击不了自己！ 
}
void B(int x,int y){//主教攻击范围 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(((i+j)==(x+y))||((i-j)==(x-y)))//在同一条斜线上 
            vis[i][j]++;//就吃得到 
        }
    }
    vis[x][y]--;//自己攻击不了自己！ 
}
void knight(int x,int y){ 
    for(int i=0;i<8;i++){
        if(judge(x+dx[i],y+dy[i])){//在骑士的8个方向上，且在棋盘上 
            vis[x+dx[i]][y+dy[i]]++;//就吃得到
        }
    }
    //因为攻击方也是骑士，所以攻击方吃不了 
}
void solider(int x,int y){
    vis[x+1][y-1]++;vis[x+1][y+1]++;//士兵只能攻击到两个点 
}
void king(int x,int y){
     for(int i=1;i<=n;i++){
         for(int j=1;j<=n;j++){
             if(abs(x-i)<=1&&abs(y-j)<=1)vis[i][j]++;//国王的8个方向内能被吃到 
         }
     }
     vis[x][y]=0; //自己攻击不了自己！    
}
void me(int x,int y){
    startx=x,starty=y;//记录开始坐标 
}
int solve(){
    while(p.size())p.pop();
     wo help;
     wo save;
     help.x=startx;
     help.y=starty;
     step[startx][starty]=0;
     memset(vis,0,sizeof(vis));
     for(int i=1;i<=n;i++){
          for(int j=1;j<=n;j++){
              help.b[i][j]=a[i][j];
         }
     }
    for(int i1=1;i1<=n;i1++){
        for(int j1=1;j1<=n;j1++){//一个一个地找敌方棋子，敌方棋子攻击范围内的就不能到 
            if(help.b[i1][j1]=='C')castle(i1,j1);
            else if(help.b[i1][j1]=='K')knight(i1,j1);
            else if(help.b[i1][j1]=='B')B(i1,j1);
            else if(help.b[i1][j1]=='Q')queen(i1,j1);
            else if(help.b[i1][j1]=='X')king(i1,j1);
            else if(help.b[i1][j1]=='P')solider(i1,j1);
        }
    }vis[endx][endy]=0;//毕竟吃到国王就赢了，不需考虑其它 
    if(judge(help.x,help.y)==0)return -1;
     p.push(help);
     while(p.size()){
           help=p.front();p.pop();
           if(step[endx][endy]!=inf){
               return step[endx][endy];
          }
          for(int i=0;i<8;i++){
                    memset(vis,0,sizeof(vis)); 
              for(int i1=1;i1<=n;i1++){
                    for(int j1=1;j1<=n;j1++){//一个一个地找敌方棋子，敌方棋子攻击范围内的就不能到 
                    if(help.b[i1][j1]=='C')castle(i1,j1);
                    else if(help.b[i1][j1]=='K')knight(i1,j1);
                   else if(help.b[i1][j1]=='B')B(i1,j1);
                  else if(help.b[i1][j1]=='Q')queen(i1,j1);
                    else if(help.b[i1][j1]=='X')king(i1,j1);
                  else if(help.b[i1][j1]=='P')solider(i1,j1);
                 }
             }vis[endx][endy]=0;
                if(judge(help.x+dx[i],help.y+dy[i])){//重点开始 ，如果跳到了棋盘上且不会被吃 
                  if(step[help.x+dx[i]][help.y+dy[i]]>step[help.x][help.y]+1){//是走到当前点最优策略才行 
                    step[help.x+dx[i]][help.y+dy[i]]=step[help.x][help.y]+1;
                    save.x=help.x+dx[i];save.y=help.y+dy[i];
                    for(int ii=1;ii<=n;ii++){
                        for(int jj=1;jj<=n;jj++){
                            save.b[ii][jj]=help.b[ii][jj];//继承状态 
                        }
                    }
                    save.b[save.x][save.y]='.';//把被“我”吃到的变成点 
                    p.push(save);
```
}//重点结束
```cpp
              }
          } 
     }
     return -1;
}
int main()
{
   while(scanf("%d",&n)!=EOF){
    memset(step,inf,sizeof(step));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            if(a[i][j]=='O')me(i,j);
            if(a[i][j]=='X'){
                endx=i,endy=j;//记录国王位置 
            }
        }
    }
    printf("%d\n",solve());
  }
return 0;
}
```

---

## 作者：GuessYCB (赞：6)

给大家提供一下除了正解DP以外另一种AC的思路吧（考试的时候打了好久）

我的做法是状态压缩+搜索（BFS）。

相信大家都一定做过钥匙类的搜索题吧（例如 拯救公主 “大火题”）

那么这里也是一样的啦。 观察到王、后、车......乱七八糟的最多只有15个旗子

然后一看空间范围512MB.....这..这不是完美吗。。。

我们用二进制的一个数来表示某个棋子是否存在。那么每次BFS从队首取出一个元素，就建一次图。

然后用这个新建的图像8个方向扩展新的元素，如果是吃掉了某个子，我们只需要改变一下状压内容就行了。

这样搜索，看起来很慢，其实跑的飞快的（因为你建图暴力搞其实也是不需要多少时间的）。

考试的时候，数组开小了一点，就直接从100跌到了30（n<=8）分了（泪奔：T\_T T\_TT\_T）。

具体的实现方法看我的代码吧。

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<set>
#include<vector>
#define ll long long
#define IL inline
#define RG register
using namespace std; 

IL int gi()
{
    RG int date = 0,m = 1; RG char ch = 0;
    while(ch!='-'&&(ch<'0'||ch>'9'))ch = getchar();
    if(ch == '-'){m = -1; ch = getchar();}
    while(ch>='0' && ch<='9'){
        date = date*10+ch-'0';
        ch = getchar();
    }return date*m;
}
IL void write(int ac)
{
    if(ac<0){ac = -ac;putchar('-');}
    if(ac>9)write(ac/10); putchar(ac%10+'0');
}
/* 
O表示白骑士
C表示黑城堡(3,4)
K表示黑骑士(0,1)
B表示黑主教(5,6)
Q表示黒皇后(2)
X表示黑国王(15)
P表示黑士兵(7,8,9,10,11,12,13,14)
*/

int posx[100],posy[100],N,stx,sty;
struct Node{int x,y,key,step;}; bool vis[(1<<16)][63][63];
queue<Node>Q; int Mp[103][103],Dc[103][103];
int mx[8] = {1,2,2,1,-1,-2,-2,-1},my[8] = {2,1,-1,-2,-2,-1,1,2};
int Kx[8] = {0,1,1,1,0,-1,-1,-1},Ky[8] = {1,1,0,-1,-1,-1,0,1};
/* 
void Portray(){
    for(int i = 1; i <= N ; i ++){
            for(int j = 1; j <= N ;j ++)cout<<Mp[i][j];cout<<endl;
        }cout<<endl;
}
*/
//建图啦（想怎么暴力就怎么暴力，反正炸不了）
void Build_Map(int x,int y,int tr)
{
    for(int i = 1; i <= N ; i ++)
       for(int j = 1; j <= N ; j++)Mp[i][j] = Dc[i][j] = 0;
    for(int i = 0 ; i <= 15; i ++)
      if((1<<i)&tr)Dc[posx[i]][posy[i]] = 1;
    for(int i = 0; i <= 15; i ++)
    {
        int nw = 1<<i;
        int ggx = posx[i],ggy = posy[i]; 
        if(!posx[i]||!posy[i])continue;
        if(0<=i && i<=1 && (tr&nw))
        {
            for(int j = 0 ; j <= 7; j ++)
            {
                int xx = ggx+mx[j],yy = ggy+my[j];
                if(xx<1 || yy<1 || xx>N || yy>N)continue;
                Mp[xx][yy]++;
            }
        }
        else if(i == 2 && tr&nw)
        {
            for(int i = 1; ;i++){if(ggx+i>N)break; Mp[ggx+i][ggy]++; if(Dc[ggx+i][ggy])break;}
            for(int i = -1; ;i--){if(ggx+i<1)break; Mp[ggx+i][ggy]++; if(Dc[ggx+i][ggy])break;}
            for(int i = 1; ;i++){if(ggy+i>N)break; Mp[ggx][ggy+i]++; if(Dc[ggx][ggy+i])break;}
            for(int i = -1; ;i--){if(ggy+i<1)break; Mp[ggx][ggy+i]++;if(Dc[ggx][ggy+i])break;}
            for(int i = 1,j = 1;;i++,j++){if(ggx+i>N||ggy+j>N)break; Mp[ggx+i][ggy+j]++;if(Dc[ggx+i][ggy+j])break;}
            for(int i = 1,j = -1;;i++,j--){if(ggx+i>N||ggy+j<1)break; Mp[ggx+i][ggy+j]++;if(Dc[ggx+i][ggy+j])break;}
            for(int i = -1,j = 1;;i--,j++){if(ggx+i<1||ggy+j>N)break; Mp[ggx+i][ggy+j]++;if(Dc[ggx+i][ggy+j])break;}
            for(int i = -1,j = -1;;i--,j--){if(ggx+i<1||ggy+j<1)break; Mp[ggx+i][ggy+j]++;if(Dc[ggx+i][ggy+j])break;}
        }
        else if(3<=i && i<=4 && tr&nw)
        {
            for(int i = 1; ;i++){if(ggx+i>N)break; Mp[ggx+i][ggy]++; if(Dc[ggx+i][ggy])break;}
            for(int i = -1; ;i--){if(ggx+i<1)break; Mp[ggx+i][ggy]++; if(Dc[ggx+i][ggy])break;}
            for(int i = 1; ;i++){if(ggy+i>N)break; Mp[ggx][ggy+i]++; if(Dc[ggx][ggy+i])break;}
            for(int i = -1; ;i--){if(ggy+i<1)break; Mp[ggx][ggy+i]++; if(Dc[ggx][ggy+i])break;}
            //Portray();
        }
        else if(5<=i && i<=6 && tr&nw)
        {
            for(int i = 1,j = 1;;i++,j++){if(ggx+i>N||ggy+j>N)break; Mp[ggx+i][ggy+j]++;if(Dc[ggx+i][ggy+j])break;}
            for(int i = 1,j = -1;;i++,j--){if(ggx+i>N||ggy+j<1)break; Mp[ggx+i][ggy+j]++;if(Dc[ggx+i][ggy+j])break;}
            for(int i = -1,j = 1;;i--,j++){if(ggx+i<1||ggy+j>N)break; Mp[ggx+i][ggy+j]++;if(Dc[ggx+i][ggy+j])break;}
            for(int i = -1,j = -1;;i--,j--){if(ggx+i<1||ggy+j<1)break; Mp[ggx+i][ggy+j]++;if(Dc[ggx+i][ggy+j])break;}
            //Portray();
        }
        else if(7<=i && i<=14 && tr&nw){if(ggx+1>N)break; if(ggy+1<=N)Mp[ggx+1][ggy+1]++; if(ggy-1>=1)Mp[ggx+1][ggy-1]++;}
        else if(i == 15)for(int i = 0; i <= 7; i ++){int xx=ggx+Kx[i],yy=ggy+Ky[i]; if(xx>0&&yy>0&&xx<=N&&yy<=N)Mp[xx][yy]++;}
    }if(Mp[posx[15]][posy[15]])Mp[posx[15]][posy[15]] = 0;
}
//正经的BFS部分。。。。
int BFS()
{
    int PrKey = 0; memset(vis,false,sizeof(vis));
    for(int i = 0 ; i <= 14; i ++)if(posx[i]!=0)PrKey = PrKey|(1<<i);
    while(!Q.empty())Q.pop();
    Q.push((Node){stx,sty,PrKey,0});vis[PrKey][stx][sty] = true;
    while(!Q.empty())
    {
        Node tp = Q.front(); Q.pop();
        int x = tp.x,y = tp.y,key = tp.key,St = tp.step;
        Build_Map(x,y,key);
        if(Mp[x][y])return -1;
        for(int i = 0 ; i <= 7 ; i ++)
        {
            int xx = x+mx[i],yy = y+my[i],Nwkey,ps = -1;
            if(xx<1 || yy<1 || xx>N || yy>N)continue;
            if(Mp[xx][yy]!=0)continue;
            if(xx == posx[15] && yy == posy[15])return St+1;
            for(int i = 0; i <= 14;i ++)if(xx == posx[i]&&yy == posy[i]){ps = i;break;}
            if(ps == -1)Nwkey = key;                        //本轮没有吃子
            else Nwkey = (key^(1<<ps));                  //吃了子，修改状压内容
            if(vis[Nwkey][xx][yy])continue;//Lcout<<xx<<" "<<yy<<endl;
            vis[Nwkey][xx][yy] = true; Q.push((Node){xx,yy,Nwkey,St+1});
        }
    }return -1;
}

int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        memset(posx,0,sizeof(posx));memset(posy,0,sizeof(posy));
        for(int i = 1; i <= N ; i ++)
           for(int j = 1; j <= N ; j ++)
           {
                  char ch = getchar();
                  while(ch!='.'&&ch!='O'&&ch!='C'&&ch!='K'&&ch!='B'&&ch!='Q'&&ch!='X'&&ch!='P')ch = getchar();
                  if(ch == '.')continue;
                  if(ch == 'O'){stx = i;sty = j;continue;}
                  if(ch == 'C'){int tt = 3;while(posx[tt]!=0)tt++; posx[tt] = i; posy[tt] = j;}
                  if(ch == 'K'){int tt = 0;while(posx[tt]!=0)tt++; posx[tt] = i; posy[tt] = j;}
                  if(ch == 'B'){int tt = 5;while(posx[tt]!=0)tt++; posx[tt] = i; posy[tt] = j;}
                  if(ch == 'Q'){posx[2] = i; posy[2] = j;} 
                  if(ch == 'X'){posx[15] = i; posy[15] = j;}
                  if(ch == 'P'){int tt = 7;while(posx[tt]!=0){tt++;} posx[tt] = i; posy[tt] = j;}
           }//cout<<stx<<" "<<sty<<endl;
           if(stx == posx[15] && sty == posy[15]){cout<<"0"<<endl;continue;} 
           int Ans = BFS(); write(Ans); putchar('\n');
    }return 0;
}
```
T\_T--T\_T--T\_T--T\_T


---

## 作者：OneLeft (赞：1)

## 题意
场上有若干黑棋，你需要操纵一个白骑士吃掉黑国王，**你不能走进对方的攻击范围（除非已经吃掉了黑国王）**，求最小步数。

## 思路
不难发现，这道题只需要 BFS 便可解决，但是还需要处理对方棋子是否被吃的情况，以及可以发现题目中的棋子数 $\le 16$，所以采用状压。

用 $Map$ 变量存每个棋子是否被吃，$flag_{Map_{x_y}}$ 存是否吃棋为 $Map$，走到 $(x,y)$ 的情况是否出现过。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=85;
struct node
{
	int Map,x,y,cost;
};
struct chess
{
	char lei;
	int x,y;
}b[25];
bool flag[(1<<16)+50][N][N],Flag[N][N];
char a[N][N];
int n,m,x,y,u,v; 
int bx[9]={0,-2,-2,-1,-1,1,1,2,2};
int by[9]={0,-1,1,-2,2,-2,2,-1,1};
int Bx[9]={0,-1,-1,-1,0,0,1,1,1};
int By[9]={0,-1,0,1,-1,1,-1,0,1};
queue<node>que;
bool check(int x,int y,char a[N][N]) //判断当地图为 a 时，位置 (x,y) 是否是安全的
{
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		if(a[i][j]=='C') //判断城堡
		{
			for(int k=i-1;k>=1;k--)
			{
				if(k==x&&j==y)return false;
				if(a[k][j]!='.')break;
			}
			for(int k=i+1;k<=n;k++)
			{
				if(k==x&&j==y)return false;
				if(a[k][j]!='.')break;
			}
			for(int k=j-1;k>=1;k--)
			{
				if(i==x&&k==y)return false;
				if(a[i][k]!='.')break;
			}
			for(int k=j+1;k<=n;k++)
			{
				if(i==x&&k==y)return false;
				if(a[i][k]!='.')break;
			}
		}
		if(a[i][j]=='K'&&(abs(x-i)==2&&abs(y-j)==1||abs(x-i)==1&&abs(y-j)==2)) //判断骑士
			return false;
		if(a[i][j]=='B') //判断主教
		{
			for(int k=i-1,l=j-1;k>=1,l>=1;k--,l--)
			{
				if(k==x&&l==y)return false;
				if(a[k][l]!='.')break;
			}
			for(int k=i-1,l=j+1;k>=1,l<=n;k--,l++)
			{
				if(k==x&&l==y)return false;
				if(a[k][l]!='.')break;
			}
			for(int k=i+1,l=j-1;k<=n,l>=1;k++,l--)
			{
				if(k==x&&l==y)return false;
				if(a[k][l]!='.')break;
			}
			for(int k=i+1,l=j+1;k<=n,l<=n;k++,l++)
			{
				if(k==x&&l==y)return false;
				if(a[k][l]!='.')break;
			}
		}
		if(a[i][j]=='Q') //判断皇后（城堡+主教）
		{
			for(int k=i-1;k>=1;k--)
			{
				if(k==x&&j==y)return false;
				if(a[k][j]!='.')break;
			}
			for(int k=i+1;k<=n;k++)
			{
				if(k==x&&j==y)return false;
				if(a[k][j]!='.')break;
			}
			for(int k=j-1;k>=1;k--)
			{
				if(i==x&&k==y)return false;
				if(a[i][k]!='.')break;
			}
			for(int k=j+1;k<=n;k++)
			{
				if(i==x&&k==y)return false;
				if(a[i][k]!='.')break;
			}
			for(int k=i-1,l=j-1;k>=1,l>=1;k--,l--)
			{
				if(k==x&&l==y)return false;
				if(a[k][l]!='.')break;
			}
			for(int k=i-1,l=j+1;k>=1,l<=n;k--,l++)
			{
				if(k==x&&l==y)return false;
				if(a[k][l]!='.')break;
			}
			for(int k=i+1,l=j-1;k<=n,l>=1;k++,l--)
			{
				if(k==x&&l==y)return false;
				if(a[k][l]!='.')break;
			}
			for(int k=i+1,l=j+1;k<=n,l<=n;k++,l++)
			{
				if(k==x&&l==y)return false;
				if(a[k][l]!='.')break;
			}
		}
		if(a[i][j]=='X'&&abs(x-i)<=1&&abs(y-j)<=1) //判断国王
			return false;
		if(a[i][j]=='P'&&x==i+1&&abs(y-j)==1) //判断士兵
			return false;
	}
	return true;
}
int BFS(int x,int y) //BFS 找最短路径
{
	memset(flag,false,sizeof flag);
	while(!que.empty())que.pop(); //多测不清空，保龄两行泪
	que.push((node){(1<<m)-1,x,y,0}); //初始状况入队
	if(!check(x,y,a))return -1; //位置 (x,y) 会被吃
	while(!que.empty())
	{
		node tmp=que.front();
		que.pop();
		int xht[N][N];
		char Map[N][N];
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			Map[i][j]='.';
		for(int i=1;i<=m;i++)
		{
			int t=1<<(i-1);
			if((t&tmp.Map)==t)
				Map[b[i].x][b[i].y]=b[i].lei,xht[b[i].x][b[i].y]=i;
		} //地图初始化
		for(int i=1;i<=8;i++)
		{
			node t=(node){tmp.Map,tmp.x+bx[i],tmp.y+by[i],tmp.cost+1};
			if(t.x>=1&&t.x<=n&&t.y>=1&&t.y<=n) //判断是否出界
			{
				if(Map[t.x][t.y]=='X')return t.cost; //判断是否吃掉国王
				if(Map[t.x][t.y]!='.')t.Map-=1<<(xht[t.x][t.y]-1); //判断是否吃棋
				if(!flag[t.Map][t.x][t.y]&&check(t.x,t.y,Map)) //判断当前情况是否出现过，位置 (x,y) 是否是安全的
					flag[t.Map][t.x][t.y]=true,que.push(t);
			}
		}
	}
	return -1;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	while(cin>>n)
	{
		m=0;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='X')u=i,v=j;
			if(a[i][j]=='O')a[i][j]='.',x=i,y=j;
			else if(a[i][j]!='.')b[++m]=(chess){a[i][j],i,j};
		}
		cout<<BFS(x,y)<<'\n';
	}
	return 0;
}
```

---

## 作者：star_city (赞：1)

洛谷不能自动识别代码了？

这道题我做的时候担心会wa或者t——结果ce了。

最后发现题目数据特别水，加个特判就能ac。0ms。中间有一些判断棋子会不会死的技巧，所以快一些。

然后吐槽下数据，虽然数据水，但也不能造谣啊，为啥n出现了55？幸亏我一开始就开的60的数组。
```
#include <iostream>
#include <cstdio>
#include <cstring> //一开始没加但xcode编译的过，结果交上去就ce
#include <queue>

using namespace std;

int n;
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, 2, 1, -1, -2}; //骑士周围八个点
int dx2[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy2[8] = {-1, 0, 1, -1, 1, -1, 0, 1}; //国王周围八个点
int qx, qy; //起点坐标
int board[60][60]; //判断单点是否死亡，适用于骑士、国王、士兵的攻击范围
int vis[60][60]; //判断是否访问
int r[60]; //判断棋子所在行是否会受到攻击，适用于皇后、城堡的攻击范围
int c[60]; //这个是判断列，和行基本一样
int le[120];
int ri[120]; //判断两条对角线，适用于皇后和主教
//以上判断变量的含义是该行、列、对角线、单点受到威胁的数量，比如两个城堡同时看守着第i行，那么r[i] = 2
char a[60][60]; //存储棋盘

queue <int> q1;
queue <int> q2;
queue <int> q3;

bool able(int x, int y)
{
    if (r[x] || c[y] || le[x+y] || ri[x-y+n] || board[x][y]) return 0; //判断棋子所在位置是否安全，即行、列等是否有威胁。
    return 1; //没有威胁就是安全
}

void init()
{
    memset(a, 0, sizeof(a));
    memset(r, 0, sizeof(r));
    memset(c, 0, sizeof(c));
    memset(le, 0, sizeof(le));
    memset(ri, 0, sizeof(ri));
    memset(vis, 0, sizeof(vis));
    memset(board, 0, sizeof(board));
    while (!q1.empty()) { q1.pop(); q2.pop(); q3.pop(); }
} //全清空

void bfs()
{
    q1.push(qx); //起点横坐标
    q2.push(qy); //起点纵坐标
    q3.push(1); //到达这个点再走一步所需的步数，初始为1
    while (!q1.empty()) {
        int x = q1.front();
        int y = q2.front();
        if (vis[x][y]) { //不走回头路，但这样的话其实可以有数据卡掉
            q1.pop();
            q2.pop();
            q3.pop();
            continue;
        }
        vis[x][y] = 1; //标为已访问
        for (int i = 0; i < 8; i++) { //向周围8个点扩展
            int xx = x+dx[i];
            int yy = y+dy[i];
            if (xx > n || xx < 1 || yy > n || yy < 1) continue; //不能跳出棋盘
            if (vis[xx][yy]) continue;
            if (a[xx][yy] == 'C')
                if (able(xx, yy)) { //吃掉之后仍然不受威胁就吃
                    r[xx]--;
                    c[yy]--; //威胁-1
                    q1.push(xx);
                    q2.push(yy);
                    q3.push(q3.front()+1); //入栈，步数+1
                    continue;
                }
            if (a[xx][yy] == 'K')
                if (able(xx, yy)) {
                    for (int k = 0; k < 8; k++) board[xx+dx[k]][yy+dy[k]]--;
                    q1.push(xx);
                    q2.push(yy);
                    q3.push(q3.front()+1);
                    continue;
                } //骑士同理
            if (a[xx][yy] == 'B')
                if (able(xx, yy)) {
                    le[xx+yy]--;
                    ri[xx-yy+n]--;
                    q1.push(xx);
                    q2.push(yy);
                    q3.push(q3.front()+1);
                    continue;
                } //主教同理
            if (a[xx][yy] == 'Q')
                if (able(xx, yy)) {
                    r[xx]--;
                    c[yy]--;
                    le[xx+yy]--;
                    ri[xx-yy+n]--;
                    q1.push(xx);
                    q2.push(yy);
                    q3.push(q3.front()+1);
                    continue;
                } //皇后同理，只是威胁减少的更多
            if (a[xx][yy] == 'X') {
                cout << q3.front() << endl;
                return;
            } //吃掉国王就输出步数并退出
            if (a[xx][yy] == 'P')
                if (able(xx, yy)) {
                    board[xx+1][yy-1]--;
                    board[xx+1][yy+1]--;
                    q1.push(xx);
                    q2.push(yy);
                    q3.push(q3.front()+1);
                    continue;
                } //士兵同理
            if (able(xx, yy)) { //如果这个格子以上都不是，那就是空的格子，判断一下就能不能走就好了
                q1.push(xx);
                q2.push(yy);
                q3.push(q3.front()+1);
            }
        }
    }
    cout << -1 << endl; //最后没吃掉国王就输出-1
}

int main(void)
{
    while (cin >> n) { //多组数据
        init(); //初始化
        for (int i = 1; i <= n; i++) {
            scanf("%s", a[i]+1); //输入技巧，以字符串形式读入
            for (int j = 1; j <= n; j++) {
                if (a[i][j] == 'O') { qx = i; qy = j; } //起点
                if (a[i][j] == 'C' || a[i][j] == 'Q') { r[i]++; c[j]++; } //城堡、皇后所在行列威胁+1
                if (a[i][j] == 'K') for (int k = 0; k < 8; k++) board[i+dx[k]][j+dy[k]]++; //骑士周围8个点威胁+1
                if (a[i][j] == 'B' || a[i][j] == 'Q') { le[i+j]++; ri[i-j+n]++; } //主教、皇后所在对角线威胁+1
                if (a[i][j] == 'X') for (int k = 0; k < 8; k++) board[i+dx2[k]][j+dy2[k]]++; //国王周围8个点威胁+1
                if (a[i][j] == 'P') { board[i+1][j-1]++; board[i+1][j+1]++; } //士兵下面两个点威胁+1
            }
        }
        if (!able(qx, qy)) { cout << -1 << endl; continue; } //如果一开始就受到威胁，就要死。我改掉ce之后因为忘加这个特判wa成80分
        bfs(); //实际上应该深搜才不会被卡，但会t。所以广搜——数据好一点其实可以卡掉广搜
    }
    
    return 0;
}
```

---

## 作者：hjbh (赞：0)

这是一道 BFS 的模拟题。主要难点在于各种棋子攻击范围的标记和数据的反复读入。所以我建议将每个棋子的攻击范围都用一个函数来标记。这样会使得代码既简洁又方便阅读。

在读入数据时进行特判。并在标记数组上进行标记。要特别注意的是，你（白骑士）无法吃到对方的黑骑士。并且要判断每一步是否在对方的攻击范围内。然后本题的一个坑点在于你其实一共有八种走法。所以，我们需要用数组将骑士的八个方向的 $x$ 坐标和 $y$ 坐标的变化储存起来。

![](https://cdn.luogu.com.cn/upload/image_hosting/6nlmbewx.png)

最后，因为数据是 $10^4$，Dfs 会 TLE。如果你可以做到我上面说的那些，AC 这道题对你来说想必也是十分简单的。
# 代码
```cpp
#include<bits/stdc++.h>//第一种方法
using namespace std;
int n,vis[114][114],sx,sy,ex,ey;
char a[114][114];
int nx[16][2]={{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}};
struct node{
	int x,y,sum;
};

void X(int x,int y){//国王。
     for(int i=1;i<=n;i++){
         for(int j=1;j<=n;j++){
             if(abs(x-i)<=1&&abs(y-j)<=1){
             	vis[i][j]=1;
			 } 
         }
     }
     vis[x][y]=0;   
}
void Q(int x,int y){//皇后。
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i==x)||(j==y)||((i+j)==(x+y))||((i-j)==(x-y))){
            	vis[i][j]=1;
			}
        }
    }
    vis[x][y]=0; 
}
void C(int x,int y){ //城堡。
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i==x)||(j==y)){
            	vis[i][j]=1;
			}
        }
    }
    vis[x][y]=0;
}
void K(int x,int y){//骑士。
    for(int i=0;i<8;i++){
        if(nx[i][0]+x>=1&&nx[i][0]+x<=n&&nx[i][1]+y>=1&&nx[i][1]+y<=n){
            vis[nx[i][0]+x][nx[i][1]+y]=1;
        }
    }
}
void B(int x,int y){//主教。
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(((i+j)==(x+y))||((i-j)==(x-y))){
            	vis[i][j]=1;
			}
        }
    }
    vis[x][y]=0;
}
void P(int x,int y){//士兵。
    vis[x+1][y-1]=vis[x+1][y+1]=1;
}
void bfs(){//bfs函数。
	queue<node>q;
	node temp={sx,sy,0};
	q.push(temp);
	while(!q.empty()){
		if(q.front().x==ex&&q.front().y==ey){
			cout<<q.front().sum<<endl;
		}
		for(int i=0;i<8;i++){
			int tx=nx[i][0]+q.front().x,ty=nx[i][1]+q.front().y;
			if(tx>=1&&tx<=n&&ty>=1&&ty<=n&&!vis[tx][ty]){
				vis[tx][ty]=1;
				node tp={tx,ty,q.front().sum+1};
				q.push(tp);
			}
		}
		q.pop();
	}
}
int main(){
	while(cin>>n){//反复读入数据。
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>a[i][j];
				if(a[i][j]=='X'){//特判国王。
					ex=i,ey=j;//标记终点
					X(i,j);
				}
				if(a[i][j]=='O'){//特判骑士。
					sx=i,sy=j;//标记起点
				}
				if(a[i][j]=='Q'){//特判皇后。
					Q(i,j);
				}
				if(a[i][j]=='C'){//特判城堡。
					C(i,j);
				} 
				if(a[i][j]=='K'){//特判骑士。
					K(i,j);
				} 
				if(a[i][j]=='B'){//特判主教。
					B(i,j);
				} 
				if(a[i][j]=='P'){//特判士兵。
					P(i,j);
				}
			}
		}
		if(vis[sx][sy]==1){//如果出发就死就直接输出零。
			cout<<-1<<endl;
			continue;
		}
		else{
			bfs();	
		}
	}
}


``````
#
#
#
```cpp
#include<bits/stdc++.h>//第二种方法。
using namespace std;//这种方法速度比第一种快很多。
char mp[60][60];
int vis[60][60],vit[60][60];
int nx[]={2,1,-1,-2,2,1,-1,-2};
int ny[]={-1,-2,-2,-1,1,2,2,1};
int bx[]={1,1,-1,-1};
int by[]={-1,1,-1,1};
int rx[]={1,0,-1,0};
int ry[]={0,1,0,-1};
struct node{
	int x,y,dis;
};
int main(){
	int n;
	while(cin>>n){//反复读入数据
		int sx,sy,tx,ty;//起点的x坐标y坐标和终点的x坐标y坐标
		for(register int i=1;i<=n;i++){
			scanf("%s",mp[i]+1);
			for(register int j=1;j<=n;j++){
				if(mp[i][j]=='O'){//记录起点
					sx=i;
					sy=j;
				}
				if(mp[i][j]=='X'){//记录终点
					tx=i;
					ty=j;
				}
			}
		}
		memset(vis,0,sizeof(vis));
		for(register int x=1;x<=n;x++){
			for(register int y=1;y<=n;y++){
				if(mp[x][y]=='P'){//士兵只能攻击到两个点 
					if(x==8)continue;
					if(y>1)vis[x][y-1]++;
					if(y<8)vis[x][y+1]++;
				}else if(mp[x][y]=='K'){
					for(register int i=0;i<8;i++){
						int ax=x+nx[i],ay=y+ny[i];
						if(ax<1 || ax>n || ay<1 || ay>n)continue;
						vis[ax][ay]+=2;
					}
				}else if(mp[x][y]=='B'){//主教攻击范围
					for(register int i=0;i<4;i++){
						int ax=x+bx[i],ay=y+by[i];
						while(!(ax<1 || ax>n || ay<1 || ay>n)){
							vis[ax][ay]+=4;
							ax+=bx[i];
							ay+=by[i];
						}
					}
				}else if(mp[x][y]=='C'){//城堡攻击范围 
					for(register int i=0;i<4;i++){
						int ax=x+rx[i],ay=y+ry[i];
						while(!(ax<1 || ax>n || ay<1 || ay>n)){
							vis[ax][ay]+=8;
							ax+=rx[i];
							ay+=ry[i];
						}
					}
				}else if(mp[x][y]=='Q'){//皇后攻击范围内的 
					for(register int i=0;i<4;i++){
						int ax=x+rx[i],ay=y+ry[i];
						while(!(ax<1 || ax>n || ay<1 || ay>n)){
							vis[ax][ay]+=16;
							ax+=rx[i];
							ay+=ry[i];
						}
					}
					for(register int i=0;i<4;i++){
						int ax=x+bx[i],ay=y+by[i];
						while(!(ax<1 || ax>n || ay<1 || ay>n)){
							vis[ax][ay]+=16;
							ax+=bx[i];
							ay+=by[i];
						}
					}
				}else if(mp[x][y]=='X'){
					for(register int i=0;i<4;i++){//国王的//皇后攻击范围内的 
						int ax=x+rx[i],ay=y+ry[i];
						if(!(ax<1 || ax>n || ay<1 || ay>n))vis[ax][ay]+=32;
					}
					for(register int i=0;i<4;i++){
						int ax=x+bx[i],ay=y+by[i];
						if(!(ax<1 || ax>n || ay<1 || ay>n))vis[ax][ay]+=32;
					}
				}
			}
		}
		if(vis[sx][sy]){
			puts("-1");
			continue;
		}
		memset(vit,0,sizeof(vit));//初始化
		queue<node> q;
		q.push(node{sx,sy,0});
		vit[sx][sy]=1;
		while(!q.empty()){//开始进行广度优先搜索
			node f=q.front();
			q.pop();
			int x=f.x,y=f.y,dis=f.dis;
			if(x==tx && y==ty){
				cout<<dis<<endl;
				break;
			}
			for(register int i=0;i<8;i++){
				int ax=x+nx[i],ay=y+ny[i];
				if(ax<1 || ax>n || ay<1 || ay>n)continue;
				if(vit[ax][ay])continue;
				vit[ax][ay]=1;
				if(ax==tx && ay==ty){
					q.push(node{ax,ay,dis+1});
					break;
				}
				if(vis[ax][ay])continue;
				if(mp[ax][ay]=='P'){//如果下一步是士兵
					mp[ax][ay]='.';
					if(ax<8){
						if(ay>1)mp[ax][ay-1]--;
						if(ay<8)mp[ax][ay+1]--;
					}
				}else if(mp[ax][ay]=='K'){//如果下一步是骑士
					mp[ax][ay]='.';
					for(register int i=0;i<8;i++){
						int cx=ax+nx[i],cy=ay+ny[i];
						if(cxk<1 || cxk>n || cy<1 || cy>n)continue;
						vis[cxk][cy]-=2;
					}
				}else if(mp[ax][ay]=='B'){//如果下一步是主教
					mp[ax][ay]='.';
					for(register int i=0;i<4;i++){
						int cx=ax+bx[i],cy=ay+by[i];
						while(!(cx<1 || cx>n || cy<1 || cy>n){
							vis[cx][cy]-=4;
							cx+=bx[i];
							cy+=by[i];
						}
					}
				}else if(mp[ax][ay]=='C'){//如果下一步是城堡
					mp[ax][ay]='.';
					for(register int i=0;i<4;i++){
						int cx=ax+rx[i],cy=ay+ry[i];
						while(!(cx<1 || cx>n || cy<1 || cy>n){
							vis[cx][cy]-=8;
							cx+=rx[i];
							cy+=ry[i];
						}
					}
				}else if(mp[ax][ay]=='Q'){//如果下一步是皇后
					mp[ax][ay]='.';
					for(register int i=0;i<4;i++){
						int cx=ax+bx[i],cy=ay+by[i];
						while(!(cx<1 || cx>n || cy<1 || cy>n){
							vis[cx][cy]-=16;
							cx+=bx[i];
							cy+=by[i];
						}
					}
					for(register int i=0;i<4;i++){
						int cx=ax+rx[i],cy=ay+ry[i];
						while(!(cx<1 || cx>n || cy<1 || cy>n){
							vis[cx][cy]-=16;
							cx+=rx[i];
							cy+=ry[i];
						}
					}
				}
				q.push(node{ax,ay,dis+1});
			} 
		}
	}
	return 0;//可有可无
}
``````
**${\color{red}题解仅供学习参考使用}$**

---

## 作者：T_TLucas_Yin (赞：0)

加上多组数据后一遍就过了并最优解第五很高兴，写一篇题解。

本题解优点在于较详细的搜索步骤解释。

每组数据的核心思路：

1. 对数据进行初始化，输入棋盘，记下起点（`O`）和终点（`X`）的位置。
2. 采用广搜。建立优先队列，将起点入队。
3. 取出队首节点（出队）。
4. 判断如果是终点，则输出当前的步数并直接结束该组数据。
5. 判断如果有未吃掉的敌方棋子能吃掉该格的马，则回到第三步。
6. 判断如果该格有敌方棋子，则标记该棋子为被吃掉状态。
7. 遍历马的方向数组，把该节点能通向的未走过节点全部入队。（很板子的广搜思想）
8. 回到第三步。

其中最难写的部分其实是“判断有没有未吃掉的敌方棋子能吃掉该格的马”。该步骤的方法是遍历敌方的所有棋子，看白马是否在它们的攻击范围内。如果白马在其中任何一枚棋子的攻击范围内，它就会失败。

接下来说说每一种棋子分别应该怎么判断。

#### 城堡（车）

如果白马与车在同一行，则沿列从车开始先后向两侧遍历。如果任意方向碰到了白马，则返回白马被吃掉。如果遇到了其他敌方棋子，则视为攻击被打断，跳出循环。

如果白马与车在同一列，则沿行遍历，其余同上。

#### 骑士（马）

借用广搜使用的马的方向数组。如果黑马往任何一个方向跳时碰到了白马，则返回白马被吃掉。

#### 主教（象）

依次遍历四个方向：行列坐标同时减；行坐标减且列坐标加；行坐标加且列坐标减；行列坐标同时加。如果一个方向上碰到了白马，则返回白马被吃掉。如果碰到了其他黑子，则跳出该方向。

#### 皇后（后）

先按照车的方式判断，再紧接着按照象的方式判断。是的，没什么好改的。

#### 国王（王）

为它单独开一个 $8$ 位的方向数组，然后遍历每一个方向，如果一个方向上碰到了白马，则返回白马被吃掉。

#### 士兵（兵）

直接判断它下一行左一列、下一行右一列两个方向上是否碰到了白马即可。

以上本题的难点就结束了。其实写起来代码只是看着长，并没有很难。

代码中也有必要的注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,top,sx,sy,ex,ey;
struct node{
	bool flag[65];//每一个敌方棋子是否被吃掉了
	int x,y,k;//坐标，步数
	bool operator <(const node &b) const{
		return k>b.k;
	}
}a;
struct chess{
	char c;
	int x,y;
}f[65];
map<pair<int,int>,int> ma;
char c[65][65];
bool fl[65][65];
priority_queue<node> q;
int dx[8]={1,1,-1,-1,2,2,-2,-2},dy[8]={2,-2,2,-2,1,-1,1,-1};
bool in(int x,int y){
	if(x<1||x>n) return 0;
	if(y<1||y>n) return 0;
	return 1;
}
bool check(node t){
	int sx=t.x,sy=t.y;
	for(int i=1;i<=top;i++){//遍历所有棋子
		if(t.flag[i]) continue;
		if(f[i].c=='C'){//车
			int x=f[i].x,y=f[i].y;
			if(x==sx){
				for(int j=y-1;j>=1;j--){//在左边
					if(j==sy) return 1;
					if(ma.count({x,j})&&!t.flag[ma[{x,j}]]) break;//遇到别的棋子就打断攻击范围
				}
				for(int j=y+1;j<=n;j++){//在右边
					if(j==sy) return 1;
					if(ma.count({x,j})&&!t.flag[ma[{x,j}]]) break;
				}
			}
			if(y==sy){
				for(int j=x-1;j>=1;j--){//在上边
					if(j==sx) return 1;
					if(ma.count({j,y})&&!t.flag[ma[{j,y}]]) break;
				}
				for(int j=x+1;j<=n;j++){//在下边
					if(j==sx) return 1;
					if(ma.count({j,y})&&!t.flag[ma[{j,y}]]) break;
				}
			}
		}
		else if(f[i].c=='K'){//马
			int x=f[i].x,y=f[i].y;
			for(int j=0;j<8;j++){//8个方向，找到了就能杀
				int xx=x+dx[j],yy=y+dy[j];
				if(in(xx,yy)&&sx==xx&&sy==yy) return 1;
			}
		}
		else if(f[i].c=='B'){//象
			int x=f[i].x,y=f[i].y;
			for(int k=1;x-k>=1&&y-k>=1;k++){//左上方
				if(x-k==sx&&y-k==sy) return 1;
				if(ma.count({x-k,y-k})&&!t.flag[ma[{x-k,y-k}]]) break;
			}
			for(int k=1;x+k<=n&&y-k>=1;k++){//左下方
				if(x+k==sx&&y-k==sy) return 1;
				if(ma.count({x+k,y-k})&&!t.flag[ma[{x+k,y-k}]]) break;
			}
			for(int k=1;x-k>=1&&y+k<=n;k++){//右上方
				if(x-k==sx&&y+k==sy) return 1;
				if(ma.count({x-k,y+k})&&!t.flag[ma[{x-k,y+k}]]) break;
			}
			for(int k=1;x+k<=n&&y+k<=n;k++){//右下方
				if(x+k==sx&&y+k==sy) return 1;
				if(ma.count({x+k,y+k})&&!t.flag[ma[{x+k,y+k}]]) break;
			}
		}
		else if(f[i].c=='Q'){//后
			int x=f[i].x,y=f[i].y;
			//车的部分
			if(x==sx){
				for(int j=y-1;j>=1;j--){//在左边
					if(j==sy) return 1;
					if(ma.count({x,j})&&!t.flag[ma[{x,j}]]) break;//遇到别的棋子就打断攻击范围
				}
				for(int j=y+1;j<=n;j++){//在右边
					if(j==sy) return 1;
					if(ma.count({x,j})&&!t.flag[ma[{x,j}]]) break;
				}
			}
			if(y==sy){
				for(int j=x-1;j>=1;j--){//在上边
					if(j==sx) return 1;
					if(ma.count({j,y})&&!t.flag[ma[{j,y}]]) break;
				}
				for(int j=x+1;j<=n;j++){//在下边
					if(j==sx) return 1;
					if(ma.count({x,j})&&!t.flag[ma[{j,y}]]) break;
				}
			}
			//象的部分
			for(int k=1;x-k>=1&&y-k>=1;k++){//左上方
				if(x-k==sx&&y-k==sy) return 1;
				if(ma.count({x-k,y-k})&&!t.flag[ma[{x-k,y-k}]]) break;
			}
			for(int k=1;x+k<=n&&y-k>=1;k++){//左下方
				if(x+k==sx&&y-k==sy) return 1;
				if(ma.count({x+k,y-k})&&!t.flag[ma[{x+k,y-k}]]) break;
			}
			for(int k=1;x-k>=1&&y+k<=n;k++){//右上方
				if(x-k==sx&&y+k==sy) return 1;
				if(ma.count({x-k,y+k})&&!t.flag[ma[{x-k,y+k}]]) break;
			}
			for(int k=1;x+k<=n&&y+k<=n;k++){//右下方
				if(x+k==sx&&y+k==sy) return 1;
				if(ma.count({x+k,y+k})&&!t.flag[ma[{x+k,y+k}]]) break;
			}
		}
		else if(f[i].c=='X'){//王
			int x=f[i].x,y=f[i].y;
			int ddx[8]={-1,-1,-1,0,1,1,1,0},ddy[8]={-1,0,1,1,1,0,-1,-1};
			for(int j=0;j<8;j++){//身边八个格子，找到了就能杀
				if(in(x+ddx[j],y+ddy[j])&&x+ddx[j]==sx&&y+ddy[j]==sy) return 1;
			}
		}
		else if(f[i].c=='P'){//兵
			int x=f[i].x,y=f[i].y;
			if(in(x+1,y-1)&&x+1==sx&&y-1==sy) return 1;
			if(in(x+1,y+1)&&x+1==sx&&y+1==sy) return 1;//左右下方两个格子
		}
	}
	return 0;
}
int main(){
	while(cin>>n){
		while(!q.empty()) q.pop();
		ma.clear(),top=0;//初始化
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
			cin>>c[i][j];
			if(c[i][j]=='X') ex=i,ey=j;//存终点
			if(c[i][j]=='O') a.x=i,a.y=j;//存起点
			else if(c[i][j]!='.') f[++top]={c[i][j],i,j},ma[{i,j}]=top;//存入敌方棋子
			fl[i][j]=0;//初始化
		}
		a.k=0;
		for(int i=1;i<=55;i++) a.flag[i]=0;//初始化
		q.push(a);//起点带着它的一大坨信息入队
		bool flag=0;
		while(!q.empty()){
			node t=q.top();q.pop();
			if(t.x==ex&&t.y==ey){//到终点了
				cout<<t.k<<"\n";
				flag=1;
				break;
			}
			if(check(t)) continue;//被棋子吃掉
			t.k++;
			if(ma.count({t.x,t.y})) t.flag[ma[{t.x,t.y}]]=1;//吃掉棋子
			for(int i=0;i<8;i++){//下一步走法
				t.x+=dx[i],t.y+=dy[i];
				if(in(t.x,t.y)&&!fl[t.x][t.y]){//能走且没走过
					fl[t.x][t.y]=1,q.push(t);
				}
				t.x-=dx[i],t.y-=dy[i];
			}
		}
		if(!flag) cout<<-1<<"\n";//不可能
	}
	return 0;
}

```

---

## 作者：Error_Mean_Correct (赞：0)

### 思路
先遍历每个白骑士可以到的格子，push 进队列。
```
.#.#.
#...#
..K..
#...#
.#.#.
```
然后看看可怜的黑国王是否能被白骑士做掉，最后遍历所有黑国王的手下的攻击范围，如果恰巧其中白骑士的移动范围，就把它 pop 出队列。

对了，还要记得特判白骑士开始即失败的情况哦。
### 关键代码
城堡范围如下：
```cpp
book[i][j]=++tmp;
for(int k=i-1;k>=1;k--)//向下
{
	mp[k][j]++;//去不了
	q[book[i][j]].push(pair<int,int>(k,j));
	if(s[k][j]!='.')//被挡住
		break;
}
for(int k=i+1;k<=n;k++)//向上
{
	mp[k][j]++;//去不了
	q[book[i][j]].push(pair<int,int>(k,j));
	if(s[k][j]!='.')//被挡住
		break;
}
for(int k=j-1;k>=1;k--)//向左
{
	mp[i][k]++;//去不了
	q[book[i][j]].push(pair<int,int>(i,k));
	if(s[i][k]!='.')//被挡住
		break;
}
for(int k=j+1;k<=n;k++)//向右
{
	mp[i][k]++;//去不了
	q[book[i][j]].push(pair<int,int>(i,k));
	if(s[i][k]!='.')//被挡住
		break;
}
```
骑士范围如下：
```cpp
book[i][j]=tmp+1;
tmp++;
if(i-2>=1&&j-1>=1)
    	mp[i-2][j-1]++,q[book[i][j]].push(pair<int,int>(i-2,j-1));
if(i-1>=1&&j-2>=1)//八向暴搜
	mp[i-1][j-2]++,q[book[i][j]].push(pair<int,int>(i-1,j-2));
if(i-2>=1&&j+1<=n)
	mp[i-2][j+1]++,q[book[i][j]].push(pair<int,int>(i-2,j+1));
if(i-1>=1&&j+2<=n)
	mp[i-1][j+2]++,q[book[i][j]].push(pair<int,int>(i-1,j+2));
if(i+1<=n&&j-2>=1)
	mp[i+1][j-2]++,q[book[i][j]].push(pair<int,int>(i+1,j-2));
if(i+2<=n&&j-1>=1)
	mp[i+2][j-1]++,q[book[i][j]].push(pair<int,int>(i+2,j-1));
if(i+1<=n&&j+2<=n)
	mp[i+1][j+2]++,q[book[i][j]].push(pair<int,int>(i+1,j+2));
if(i+2<=n&&j+1<=n)
	mp[i+2][j+1]++,q[book[i][j]].push(pair<int,int>(i+2,j+1));
```
主教范围如下：
```cpp
book[i][j]=++tmp;
for(int k=1;k<=n;k++)//左上
{
	if(i-k<1||j-k<1)
		break;
	mp[i-k][j-k]++;
	q[book[i][j]].push(pair<int,int>(i-k,j-k));
	if(s[i-k][j-k]!='.')
		break;
}
for(int k=1;k<=n;k++)//右下
{
	if(i+k>n||j+k>n)
		break;
	mp[i+k][j+k]++;
	q[book[i][j]].push(pair<int,int>(i+k,j+k));
	if(s[i+k][j+k]!='.')
		break;
}
for(int k=1;k<=n;k++)//左下
{
	if(i+k>n||j-k<1)
		break;
	if(s[i+k][j-k]!='.')
		break;
	mp[i+k][j-k]++;
	q[book[i][j]].push(pair<int,int>(i+k,j-k));
}
for(int k=1;k<=n;k++)//右上
{
	if(i-k<1||j+k>n)
		break;
	mp[i-k][j+k]++;
	q[book[i][j]].push(pair<int,int>(i-k,j+k));
	if(s[i-k][j+k]!='.')
		break;
}
```
皇后（站在城堡上的主教）：
```cpp
book[i][j]=++tmp;
for(int k=1;k<=n;k++)//左上
{
	if(i-k<1||j-k<1)
		break;
	mp[i-k][j-k]++;
	q[book[i][j]].push(pair<int,int>(i-k,j-k));
	if(s[i-k][j-k]!='.')
		break;
}
for(int k=1;k<=n;k++)//右下
{
	if(i+k>n||j+k>n)
		break;
	mp[i+k][j+k]++;
	q[book[i][j]].push(pair<int,int>(i+k,j+k));
	if(s[i+k][j+k]!='.')
		break;
}
for(int k=1;k<=n;k++)//左下
{
	if(i+k>n||j-k<1)
		break;
	if(s[i+k][j-k]!='.')
		break;
	mp[i+k][j-k]++;
	q[book[i][j]].push(pair<int,int>(i+k,j-k));
}
for(int k=1;k<=n;k++)//右上
{
	if(i-k<1||j+k>n)
		break;
	mp[i-k][j+k]++;
	q[book[i][j]].push(pair<int,int>(i-k,j+k));
	if(s[i-k][j+k]!='.')
		break;
}
book[i][j]=++tmp;
for(int k=i-1;k>=1;k--)//向下
{
	mp[k][j]++;//去不了
	q[book[i][j]].push(pair<int,int>(k,j));
	if(s[k][j]!='.')//被挡住
		break;
}
for(int k=i+1;k<=n;k++)//向上
{
	mp[k][j]++;//去不了
	q[book[i][j]].push(pair<int,int>(k,j));
	if(s[k][j]!='.')//被挡住
		break;
}
for(int k=j-1;k>=1;k--)//向左
{
	mp[i][k]++;//去不了
	q[book[i][j]].push(pair<int,int>(i,k));
	if(s[i][k]!='.')//被挡住
		break;
}
for(int k=j+1;k<=n;k++)//向右
{
	mp[i][k]++;//去不了
	q[book[i][j]].push(pair<int,int>(i,k));
	if(s[i][k]!='.')//被挡住
		break;
}
```
国王范围如下：
```cpp
book[i][j]=++tmp;
if(i-1>=1&&j-1>=1)//左上
	mp[i-1][j-1]++,q[book[i][j]].push(pair<int,int>(i-1,j-1));
if(i-1>=1)//上
	mp[i-1][j]++,q[book[i][j]].push(pair<int,int>(i-1,j));
if(i-1>=1&&j+1<=n)//右上
	mp[i-1][j+1]++,q[book[i][j]].push(pair<int,int>(i-1,j+1));
if(j-1>=1)//左
	mp[i][j-1]++,q[book[i][j]].push(pair<int,int>(i,j-1));
if(j+1<=n)//右		
	mp[i][j+1]++,q[book[i][j]].push(pair<int,int>(i,j+1));
if(i+1<=n&&j-1>=1)//左下
	mp[i+1][j-1]++,q[book[i][j]].push(pair<int,int>(i+1,j-1));
if(i+1<=n)//下		
	mp[i+1][j]++,q[book[i][j]].push(pair<int,int>(i+1,j));
if(i+1<=n&&j+1<=n)//右下
	mp[i+1][j+1]++,q[book[i][j]].push(pair<int,int>(i+1,j+1));
```
士兵范围如下：
```cpp
book[i][j]=++tmp;
if(i+1<=n&&j-1>=1)//左下
	mp[i+1][j-1]++,q[book[i][j]].push(pair<int,int>(i+1,j-1));
if(i+1<=n&&j+1<=n)//右下
	mp[i+1][j+1]++,q[book[i][j]].push(pair<int,int>(i+1,j+1));
```

---

## 作者：wcyares (赞：0)

# 暴力bfs中的细节
刚刚练完此题，从30分一直走到AC的蒟蒻深知此题的~~精髓~~（细节）所在，所以这里补充几个细节。


------------
## bfs大意：
n如此小，可以看出是暴搜（证明方法：显然），所以先大概把bfs的框架好：

因为可以吃子，所以我们用结构体中套数组的方式来模拟棋盘上哪些点不能走，然后走到那个点上时我们就可以把那个点对棋盘的影响取消掉再用相当于bfs模板的方法来求解。

~~问题出就出在结构体中套数组和添加取消影响这里~~

------------

## bfs中~~不为人知~~的细节
1. 对于结构体队列的插入，本蒟蒻不知道为什么不能用这个东西：

		q.push((ss){sx,sy,0,ks});（ks表示上面说的那个看能不能走的棋盘）
	emmm所以我就新建一个结构体，然后把ks的每一个值都复制给它，然后再插入这个结构体。挺麻烦的，~~但是不是很耗时间~~
1. 然后就是那几个棋子的处理问题。题上说只要碰到棋子就停，这是一个比较小的细节，取消影响的时候也可以只取消到原来的那个棋子上，这样就比较方便，因为添加和取消就可以用一个函数来完成。特别地，皇后的函数就可以看成车和象函数的组合。
1. 踩到王直接输出，不管它在不在攻击范围
1. 如果它一开始就在攻击范围，就直接死掉，这点看题就行，没判断的话80分（惨痛的领悟）
1. 不要以为王不需要添加影响（不过可能就我一个这么以为）

emmm，这样就差不多了（bushi），具体的可以看代码注释（码风不好见谅）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=70;
int dx[9]={0,-1,-1,-2,-2,2,2,1,1};
int dy[9]={0,2,-2,1,-1,1,-1,2,-2};
int sx,sy,zx,zy,n;
int  mp[N][N];
bool chong[N][N];
struct ss{
	int x,y,st;
	bool zou[N][N];
};
int ks[N][N];
void C(int x,int y,int k){ 
	int xx=x,yy=y;
	while(xx>0&&xx<=n&&mp[xx][yy]==0||xx==x)
		{xx-=k;ks[xx][yy]+=k;}xx=x;yy=y;
	while(xx>0&&xx<=n&&mp[xx][yy]==0||xx==x)
		{xx+=k;ks[xx][yy]+=k;}xx=x;yy=y;
	while(yy>0&&yy<=n&&mp[xx][yy]==0||yy==y)
		{yy-=k;ks[xx][yy]+=k;}xx=x;yy=y;
	while(yy>0&&yy<=n&&mp[xx][yy]==0||yy==y)
		{yy+=k;ks[xx][yy]+=k;}xx=x;yy=y;
} 
void K(int x,int y,int k){
	for(int i=1;i<=8;i++) ks[x+dx[i]][y+dy[i]]+=k;
}
void X(int x,int y){
	ks[x-1][y-1]++;ks[x-1][y]++;ks[x-1][y+1]++;ks[x][y-1]++;
	ks[x][y+1]++;ks[x+1][y-1]++;ks[x+1][y]++;ks[x+1][y+1]++;
}
void B(int x,int y,int k){
	int xx=x,yy=y;
	while(xx>0&&xx<=n&&yy>0&&yy<=n&&mp[xx][yy]==0||xx==x)
		{xx-=k;yy+=k;ks[xx][yy]+=k;}
	xx=x;yy=y;
	while(xx>0&&xx<=n&&yy>0&&yy<=n&&mp[xx][yy]==0||xx==x)
		{xx+=k;yy+=k;ks[xx][yy]+=k;}
	xx=x;yy=y;
	while(xx>0&&xx<=n&&yy>0&&yy<=n&&mp[xx][yy]==0||xx==x)
		{xx-=k;yy-=k;ks[xx][yy]+=k;}
	xx=x;yy=y;
	while(xx>0&&xx<=n&&yy>0&&yy<=n&&mp[xx][yy]==0||xx==x)
		{yy-=k;xx+=k;ks[xx][yy]+=k;}
}
void P(int x,int y,int k){ks[x+1][y-1]+=k;ks[x+1][y+1]+=k;}
void bfs(){
	queue <ss> q;
	ss wcy;
	wcy.x=sx;wcy.y=sy;wcy.st=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			wcy.zou[i][j]=ks[i][j];
	//构建结构体
	q.push(wcy);
	while(!q.empty()){
		ss u=q.front();q.pop();ss t;
		//cout<<u.x<<" "<<u.y<<endl;
		for(int i=1;i<=8;i++){
			t.x=u.x+dx[i],t.y=u.y+dy[i];t.st=u.st+1;
			if(t.x<=0||t.y<=0||t.x>n||t.y>n||chong[t.x][t.y])continue;
			if(t.x==zx&&t.y==zy) {cout<<t.st<<endl;return ;}
			//踩到王直接输出，不管它在不在攻击范围
			int num=u.zou[t.x][t.y];
			if(num==0){
			  	for(int i=1;i<=n;i++)
						for(int j=1;j<=n;j++)
							ks[i][j]=u.zou[i][j];
				chong[t.x][t.y]=1;
				if(mp[t.x][t.y]<=0&&mp[t.x][t.y]!='O'){
					char ch=mp[t.x][t.y];
					if(ch=='C') C(t.x,t.y,-1);
					if(ch=='K') K(t.x,t.y,-1);
					if(ch=='B') B(t.x,t.y,-1);
					if(ch=='Q') {C(t.x,t.y,-1),B(t.x,t.y,-1);}
					if(ch=='P') P(t.x,t.y,-1);
					//-1代表影响减一（这个好像都知道）
				}
				for(int i=1;i<=n;i++){
					for(int j=1;j<=n;j++){
						t.zou[i][j]=ks[i][j];
					}
				}//重新赋值，上面有讲过
				q.push(t);
			}
		}
	}
	cout<<-1<<endl;
	//到最后出不来就不能出来了
}
int main (){
	while(cin>>n){
		//cout<<n<<endl;
		getchar();
		memset(ks,0,sizeof(ks));
		memset(chong,0,sizeof(chong));
		memset(mp,0,sizeof(mp));
		//初始化
		for(int i=1;i<=n;i++){
			char ch;
			for(int j=1;j<=n;j++){
				ch=getchar();
				if(ch!='.') mp[i][j]=ch;
				if(ch=='O') sx=i,sy=j;
				if(ch=='X') zx=i,zy=j,X(i,j);
			}getchar();
		}
		//getchar读入更快（
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				char ch=mp[i][j];
				if(ch=='C') C(i,j,1);
				if(ch=='K') K(i,j,1);
				if(ch=='B') B(i,j,1);
				if(ch=='Q') {C(i,j,1),B(i,j,1);}
				if(ch=='P') P(i,j,1);
			}
		}
		if(ks[sx][sy]) cout<<-1<<endl;
		//如果它一开始就在攻击范围，就直接死掉
		else bfs();
	}
	return 0;
}
```


---

## 作者：未见堇开 (赞：0)

这里是一个学`DFS`学傻了，忘了如何写`BFS`的蒟蒻的记搜题解。

看到最小步数，考虑`IDDFS`。

棋子的攻击范围可以直接覆盖并叠加，在吃掉棋子后暴力消除覆盖即可。

直接记录剩余`i`步时在$(x,y)$能否杀王以实现记搜，空间开销不大，可以接受。

代码很长，请酌情阅读。
```cpp
#include<cstdio>
#include<cstring>
#define reg register
#define MAXN 60
using namespace std;

const int dx[8]={1,1,2,2,-1,-1,-2,-2};
const int dy[8]={2,-2,1,-1,2,-2,1,-1};
int ban[MAXN][MAXN],dp[MAXN][MAXN][505];//dp记搜，ban记录覆盖情况
char map[MAXN][MAXN];
int n,x,y,ex,ey;

inline bool inmap(char ch)
{return(ch=='.'||ch=='O'||ch=='C'||ch=='K'||ch=='B'||ch=='Q'||ch=='X'||ch=='P');}

inline bool out(int x,int y)//越界
{return(x<1||x>n||y<1||y>n);}

inline int trans(char ch)
{
	if(ch=='C')
		return(1);
	if(ch=='K')
		return(4);
	if(ch=='X')
		return(5);
	if(ch=='B')
		return(2);
	if(ch=='Q')
		return(3);
	if(ch=='P')
		return(6);
	return(7);
}

inline void cover(int type,int px,int py,int val)
{
	if(type>6)
		return;
	if(type==6)//兵
	{
		if(!out(px+1,py-1))
			ban[px+1][py-1]+=val;
		if(!out(px+1,py+1))
			ban[px+1][py+1]+=val;
		return;
	}
	if(type==5)//王
	{
		if(!out(px+1,py-1))
			ban[px+1][py-1]+=val;
		if(!out(px+1,py+1))
			ban[px+1][py+1]+=val;
		if(!out(px+1,py))
			ban[px+1][py]+=val;
		if(!out(px-1,py+1))
			ban[px-1][py+1]+=val;
		if(!out(px-1,py-1))
			ban[px-1][py-1]+=val;
		if(!out(px-1,py+1))
			ban[px-1][py]+=val;
		if(!out(px,py-1))
			ban[px][py-1]+=val;
		if(!out(px,py+1))
			ban[px][py+1]+=val;
		return;
	}
	if(type==4)//马
	{
		if(!out(px-1,py-2))
			ban[px-1][py-2]+=val;
		if(!out(px-1,py+2))
			ban[px-1][py+2]+=val;
		if(!out(px+1,py-2))
			ban[px+1][py-2]+=val;
		if(!out(px+1,py+2))
			ban[px+1][py+2]+=val;
		if(!out(px-2,py-1))
			ban[px-2][py-1]+=val;
		if(!out(px-2,py+1))
			ban[px-2][py+1]+=val;
		if(!out(px+2,py-1))
			ban[px+2][py-1]+=val;
		if(!out(px+2,py+1))
			ban[px+2][py+1]+=val;
	}
	for(reg int i=1;i<=n;i++)//车、象和后，暴力覆盖
	{
		if(type&1)
		{
			if(!out(px-i,py))
				ban[px-i][py]+=val;
			if(!out(px+i,py))
				ban[px+i][py]+=val;
			if(!out(px,py-i))
				ban[px][py-i]+=val;
			if(!out(px,py+i))
				ban[px][py+i]+=val;
		}
		if(type&2)
		{
			if(!out(px-i,py-i))
				ban[px-i][py-i]+=val;
			if(!out(px+i,py+i))
				ban[px+i][py+i]+=val;
			if(!out(px+i,py-i))
				ban[px+i][py-i]+=val;
			if(!out(px-i,py+i))
				ban[px-i][py+i]+=val;
		}
	}
	return;
}

bool dfs(int rest,int px,int py)
{
	if(rest==0)
		return(px==ex&&py==ey);
	if(dp[px][py][rest])
		return(dp[px][py][rest]==2);
	bool res=false;
	for(reg int i=0;i<8;i++)
	{
		int qx=px+dx[i],qy=py+dy[i];
		if(out(qx,qy)||(ban[qx][qy]&&(qx!=ex||qy!=ey)))
			continue;
		char tmp=map[qx][qy];
		if(tmp!='.')
			map[qx][qy]='.';
		cover(trans(tmp),qx,qy,-1);
		res|=dfs(rest-1,qx,qy);
		cover(trans(tmp),qx,qy,1);
		map[qx][qy]=tmp;
		if(res)
			return(dp[px][py][rest]=2,true);
	}
	return(dp[px][py][rest]=res?2:1,res);
}

int main()
{
	while(scanf("%d",&n)!=EOF)//多组数据
	{
		memset(ban,0,sizeof(ban));
		memset(dp,0,sizeof(dp));
		for(reg int i=1,j=0;i<=n;i++)
		{
			char ch=getchar();
			while(!inmap(ch))
				ch=getchar();
			map[i][++j]=ch;
			if(ch=='O')
				x=i,y=j;
			if(ch=='X')
				ex=i,ey=j;
			cover(trans(ch),i,j,1);//覆盖
			if(j!=n)
				--i;
			else
				j=0;//结束本行读入
		}
		if(ban[x][y])
		{
			puts("-1");
			continue;
		}
		reg int res=1;
		for(;res<=500;++res)//IDDFS
		{
			if(dfs(res,x,y))
				break;
		}
		printf("%d\n",res==500?-1:res);
	}
	return(0);
}
```

---

## 作者：PPXppx (赞：0)

### 纯暴力模拟+$BFS$,不需要状压$!!!$

### $34ms$,跑进了最优解第一页$!!!$

### 分析:直接根据题意,把每种棋子能够攻击到的点暴力覆盖,记为$a[i][j]$,注意$a[i][j]$是可以叠加的,初始化为$0$.(注意那些所谓碰到第一个棋子就被阻挡的攻击类棋子,它们能够攻击到阻挡它们的第一个棋子)

### 同时,因为题目保证了攻击类棋子不超过$16$个,可以开$16$个$queue$或者$vector$存下每一个攻击棋子能够攻击到哪些点(方便之后撤销覆盖).

### 然后就可以把起点丢入队列跑$BFS$了,走到终点直接输出即可.(记得特判一下起点就在被攻击范围内的情况.)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#define ll long long
using namespace std;
const int N=60;
int n;char s[N][N];
int a[N][N],visit[N][N],dis[N][N],used[N][N];
int dx[8]={-2,-1,-2,-1,1,1,2,2},
	dy[8]={-1,-2,1,2,-2,2,-1,1};
int main(){
	while(scanf("%d",&n)!=EOF){
		memset(a,0,sizeof(a));memset(dis,0x3f,sizeof(dis));
		memset(visit,0,sizeof(visit));memset(used,0,sizeof(used));
		queue<pair<int,int> >q[20],Q;//多组数据初始化
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)cin>>s[i][j];
		int tot=0;//记录有多少个攻击棋子
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(s[i][j]=='C'){//判断是哪一种棋子,暴力覆盖能够攻击到的点,注意防止下标越界
					visit[i][j]=++tot;
					for(int k=i-1;k>=1;--k){
						++a[k][j];q[visit[i][j]].push(pair<int,int>(k,j));
						if(s[k][j]!='.')break;
					}
					for(int k=i+1;k<=n;++k){
						++a[k][j];q[visit[i][j]].push(pair<int,int>(k,j));
						if(s[k][j]!='.')break;
					}
					for(int k=j-1;k>=1;--k){
						++a[i][k];q[visit[i][j]].push(pair<int,int>(i,k));
						if(s[i][k]!='.')break;
					}
					for(int k=j+1;k<=n;++k){
						++a[i][k];q[visit[i][j]].push(pair<int,int>(i,k));
						if(s[i][k]!='.')break;
					}
				}
				if(s[i][j]=='K'){
					visit[i][j]=++tot;
					if(i-2>=1&&j-1>=1)++a[i-2][j-1],q[visit[i][j]].push(pair<int,int>(i-2,j-1));
					if(i-1>=1&&j-2>=1)++a[i-1][j-2],q[visit[i][j]].push(pair<int,int>(i-1,j-2));
					if(i-2>=1&&j+1<=n)++a[i-2][j+1],q[visit[i][j]].push(pair<int,int>(i-2,j+1));
					if(i-1>=1&&j+2<=n)++a[i-1][j+2],q[visit[i][j]].push(pair<int,int>(i-1,j+2));
					if(i+1<=n&&j-2>=1)++a[i+1][j-2],q[visit[i][j]].push(pair<int,int>(i+1,j-2));
					if(i+2<=n&&j-1>=1)++a[i+2][j-1],q[visit[i][j]].push(pair<int,int>(i+2,j-1));
					if(i+1<=n&&j+2<=n)++a[i+1][j+2],q[visit[i][j]].push(pair<int,int>(i+1,j+2));
					if(i+2<=n&&j+1<=n)++a[i+2][j+1],q[visit[i][j]].push(pair<int,int>(i+2,j+1));
				}
				if(s[i][j]=='B'){
					visit[i][j]=++tot;
					for(int k=1;k<=n;++k){
						if(i-k<1||j-k<1)break;
						++a[i-k][j-k];q[visit[i][j]].push(pair<int,int>(i-k,j-k));
						if(s[i-k][j-k]!='.')break;
					}
					for(int k=1;k<=n;++k){
						if(i+k>n||j+k>n)break;
						++a[i+k][j+k];q[visit[i][j]].push(pair<int,int>(i+k,j+k));
						if(s[i+k][j+k]!='.')break;
					}
					for(int k=1;k<=n;++k){
						if(i+k>n||j-k<1)break;
						if(s[i+k][j-k]!='.')break;
						++a[i+k][j-k];q[visit[i][j]].push(pair<int,int>(i+k,j-k));
					}
					for(int k=1;k<=n;++k){
						if(i-k<1||j+k>n)break;
						++a[i-k][j+k];q[visit[i][j]].push(pair<int,int>(i-k,j+k));
						if(s[i-k][j+k]!='.')break;
					}
				}
				if(s[i][j]=='Q'){
					visit[i][j]=++tot;
					for(int k=i-1;k>=1;--k){
						++a[k][j];q[visit[i][j]].push(pair<int,int>(k,j));
						if(s[k][j]!='.')break;
					}
					for(int k=i+1;k<=n;++k){
						++a[k][j];q[visit[i][j]].push(pair<int,int>(k,j));
						if(s[k][j]!='.')break;
					}
					for(int k=j-1;k>=1;--k){
						++a[i][k];q[visit[i][j]].push(pair<int,int>(i,k));
						if(s[i][k]!='.')break;
					}
					for(int k=j+1;k<=n;++k){
						++a[i][k];q[visit[i][j]].push(pair<int,int>(i,k));
						if(s[i][k]!='.')break;
					}
					for(int k=1;k<=n;++k){
						if(i-k<1||j-k<1)break;
						++a[i-k][j-k];q[visit[i][j]].push(pair<int,int>(i-k,j-k));
						if(s[i-k][j-k]!='.')break;
					}
					for(int k=1;k<=n;++k){
						if(i+k>n||j+k>n)break;
						++a[i+k][j+k];q[visit[i][j]].push(pair<int,int>(i+k,j+k));
						if(s[i+k][j+k]!='.')break;
					}
					for(int k=1;k<=n;++k){
						if(i+k>n||j-k<1)break;
						++a[i+k][j-k];q[visit[i][j]].push(pair<int,int>(i+k,j-k));
						if(s[i+k][j-k]!='.')break;
					}
					for(int k=1;k<=n;++k){
						if(i-k<1||j+k>n)break;
						//if(s[i-k][j+k]!='.')break;
						++a[i-k][j+k];q[visit[i][j]].push(pair<int,int>(i-k,j+k));
						if(s[i-k][j+k]!='.')break;
					}
				}
				if(s[i][j]=='X'){
					visit[i][j]=++tot;
					if(i-1>=1&&j-1>=1)++a[i-1][j-1],q[visit[i][j]].push(pair<int,int>(i-1,j-1));
					if(i-1>=1)++a[i-1][j],q[visit[i][j]].push(pair<int,int>(i-1,j));
					if(i-1>=1&&j+1<=n)++a[i-1][j+1],q[visit[i][j]].push(pair<int,int>(i-1,j+1));
					if(j-1>=1)++a[i][j-1],q[visit[i][j]].push(pair<int,int>(i,j-1));
					if(j+1<=n)++a[i][j+1],q[visit[i][j]].push(pair<int,int>(i,j+1));
					if(i+1<=n&&j-1>=1)++a[i+1][j-1],q[visit[i][j]].push(pair<int,int>(i+1,j-1));
					if(i+1<=n)++a[i+1][j],q[visit[i][j]].push(pair<int,int>(i+1,j));
					if(i+1<=n&&j+1<=n)++a[i+1][j+1],q[visit[i][j]].push(pair<int,int>(i+1,j+1));
				}
				if(s[i][j]=='P'){
					visit[i][j]=++tot;
					if(i+1<=n&&j-1>=1)++a[i+1][j-1],q[visit[i][j]].push(pair<int,int>(i+1,j-1));
					if(i+1<=n&&j+1<=n)++a[i+1][j+1],q[visit[i][j]].push(pair<int,int>(i+1,j+1));
				}
				if(s[i][j]=='O'){
					Q.push(pair<int,int>(i,j));dis[i][j]=0;used[i][j]=1;
				}
			}
		}
		int bj=0;
		while(Q.size()){
			int x=Q.front().first,y=Q.front().second;Q.pop();
			if(a[x][y])break;//特判起点就在被攻击范围内的情况
			for(int i=0;i<8;++i){
				int xx=x+dx[i],yy=y+dy[i];
				if(xx<1||xx>n||yy<1||yy>n)continue;//不能超出范围
				if(s[xx][yy]=='X'){//走到终点直接输出
					printf("%d\n",dis[x][y]+1);
					bj=1;break;
				}
				if(a[xx][yy]||used[xx][yy])continue;//该点不在被攻击范围内而且之前没走过
                used[xx][yy]=1;
				dis[xx][yy]=dis[x][y]+1;Q.push(pair<int,int>(xx,yy));//更新队列
				if(visit[xx][yy]){//如果该点是个攻击棋子,撤销之前的覆盖
					while(q[visit[xx][yy]].size()){
						--a[q[visit[xx][yy]].front().first][q[visit[xx][yy]].front().second];
						q[visit[xx][yy]].pop();
					}					
				}
			}
			if(bj)break;
		}
		if(!bj)puts("-1");
	}
    return 0;
}

```

---

## 作者：半仙胡小桃 (赞：0)

传送门

这题真的费劲！

我们用二进制来表示场上的剩下的黑棋子有哪些。

由于黑骑士我们吃不掉，国王吃了就GG。

所以最多的状态是有2^13个。

用s来表示状态

mp[s][x][y]来表示s状态下x，y是否被攻击到了

vis[s][x][y]来表示s状态下x，y是否走过了。

把所有的mp[s][x][y]预处理出来（要不你吃了棋子再还原太麻烦了啊）

然后用BFS转移就行啦！






```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int maxm=60;
struct node{
    int x,y;
};
node g[maxm],yx[maxm];
struct Node{
    int s,x,y,step;
};
int n,map[maxm][maxm],b[maxm][maxm],cnt,tot,ans;
bool vis[1<<14][maxm][maxm],mp[1<<14][maxm][maxm];
char s[maxm];
int gx,gy,qx,qy;
void hqs(int s,int x,int y)
{
    mp[s][x-1][y+2]=mp[s][x+1][y+2]=mp[s][x+2][y-1]=mp[s][x+2][y+1]=1;
    if(x-2>0) mp[s][x-2][y-1]=mp[s][x-2][y+1]=1;
    if(y-2>0) mp[s][x-1][y-2]=mp[s][x+1][y-2]=1;
}
void king(int s,int x,int y)
{
    mp[s][x-1][y-1]=mp[s][x-1][y]=mp[s][x-1][y+1]=1;
    mp[s][x][y-1]=mp[s][x][y+1]=1;
    mp[s][x+1][y-1]=mp[s][x+1][y]=mp[s][x+1][y+1]=1;
}
bool ok(int s,int x,int y)//当前的位置可不可行
{
    if(x<1||x>n||y<1||y>n) return 0;
    if(map[x][y]<=1) return 1;
    if(map[x][y]==2||map[x][y]==7) return 0;
    if(s&(1<<b[x][y]-1)) return 0;
}
void cb(int s,int x,int y)
{
    for(int i=x-1;i>=1;i--)
    {
        mp[s][i][y]=1;
        if(!ok(s,i,y)) break;
    }
    for(int i=x+1;i<=n;i--)
    {
        mp[s][i][y]=1;
        if(!ok(s,i,y)) break;
    }
    for(int i=y-1;i>=1;i--)
    {
        mp[s][x][i]=1;
        if(!ok(s,x,i)) break;
    }
    for(int i=y+1;i<=n;i--)
    {
        mp[s][x][i]=1;
        if(!ok(s,x,i)) break;
    }
}
void zj(int s,int x,int y)
{
    for(int i=1;i<min(x,y);i++)       if(ok(s,x-i,y-i)) mp[s][x-i][y-i]=1;else{mp[s][x-i][y-i]=1;break;}
    for(int i=1;i<=min(n-x,n-y);i++)  if(ok(s,x+i,y+i)) mp[s][x+i][y+i]=1;else{mp[s][x+i][y+i]=1;break;}
    for(int i=1;i<=min(x,n-y);i++)    if(ok(s,x-i,y+i)) mp[s][x-i][y+i]=1;else{mp[s][x-i][y+i]=1;break;}
    for(int i=1;i<=min(n-x,y);i++)    if(ok(s,x+i,y-i)) mp[s][x+i][y-i]=1;else{mp[s][x+i][y-i]=1;break;}
}
void wh(int s,int x,int y)
{
    zj(s,x,y);
    cb(s,x,y);
}
void sb(int s,int x,int y)
{
    mp[s][x+1][y-1]=mp[s][x+1][y+1]=1;
}
queue <Node> dl;
void tz(int s,int x,int y,int step)
{
    if(x<1||x>n||y<1||y>n) return;
    if(mp[s][x][y]||vis[s][x][y]) return;
    vis[s][x][y]=1;
    if(map[x][y]==2)
    {
        ans=step;
        return;
    }
    if(map[x][y]>=3&&map[x][y]<=6)
     if(s&(1<<(b[x][y]-1)))
       s^=(1<<(b[x][y]-1));//吃了
    vis[s][x][y]=1;
    dl.push((Node){s,x,y,step});
}
void get_ans()
{
    while(!dl.empty())
     dl.pop();
    dl.push((Node){(1<<tot)-1,qx,qy,0});
    vis[(1<<tot)-1][qx][qy]=1;
    while(!dl.empty())
    {
        Node d=dl.front();
        dl.pop();
        tz(d.s,d.x-2,d.y-1,d.step+1);tz(d.s,d.x-2,d.y+1,d.step+1);
        tz(d.s,d.x-1,d.y-2,d.step+1);tz(d.s,d.x-1,d.y+2,d.step+1);
        tz(d.s,d.x+1,d.y-2,d.step+1);tz(d.s,d.x+1,d.y+2,d.step+1);
        tz(d.s,d.x+2,d.y-1,d.step+1);tz(d.s,d.x+2,d.y+1,d.step+1);
        if(ans) break;
    }
    if(ans) printf("%d\n",ans);
    else printf("-1"); 
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        memset(map,0,sizeof(map));
        memset(vis,0,sizeof(vis));
        memset(b,0,sizeof(b));
        memset(mp,0,sizeof(mp));
        cnt=0,tot=0;
        ans=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%s",(s+1));
            for(int j=1;j<=n;j++)
            {
                if(s[j]=='K') cnt++,g[cnt].x=i,g[cnt].y=j,map[i][j]=7;//黑骑士 
                if(s[j]=='X') cnt++,g[cnt].x=i,g[cnt].y=j,map[i][j]=2,gx=i,gy=j;//国王
                if(s[j]=='O') qx=i,qy=j;//白骑士
                if(s[j]=='C') yx[tot].x=i,yx[tot].y=j,map[i][j]=3,b[i][j]=tot++;//城堡
                if(s[j]=='B') yx[tot].x=i,yx[tot].y=j,map[i][j]=4,b[i][j]=tot++;//主教
                if(s[j]=='Q') yx[tot].x=i,yx[tot].y=j,map[i][j]=5,b[i][j]=tot++;//王后
                if(s[j]=='P') yx[tot].x=i,yx[tot].y=j,map[i][j]=6,b[i][j]=tot++;//柿饼
            }
        }
        for(int s=0;s<(1<<tot);s++)
         {
            for(int i=1;i<=cnt;i++)
            if(map[g[i].x][g[i].y]==7)
            hqs(s,g[i].x,g[i].y);
            else
            king(s,g[i].x,g[i].y); 
            for(int i=0;i<tot;i++)
            if((1<<i)&s)
            {
                int x=yx[i].x;
                int y=yx[i].y;
                if(map[x][y]==3) cb(s,x,y);
                if(map[x][y]==4) zj(s,x,y);
                if(map[x][y]==5) wh(s,x,y);
                if(map[x][y]==6) sb(s,x,y);
            }
            mp[s][gx][gy]=0;
         }
        if(mp[(1<<tot)-1][qx][qy])
         printf("-1\n");//我方直接GG
        else
         get_ans();
    }
}
```

---

## 作者：bjrjk (赞：0)

打个我博客（这个题解）的广告：https://renjikai.com/luogu-p3930/

本来没想着这题能得分，结果这题月赛时竟然80分，后来出题人说有两个点错了，重测就100了。。。/捂脸

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
#include<list>
#include<cstring>
#include<cassert>
#include<cmath>
using namespace std;
int n;
char arr[60][60]; //存放棋子
bool attack[2][60][60]; //某点是否可以被攻击（第一维没有用处，只用了第一维的1）
int dp[60][60];
int O_x, O_y, X_x_pos, X_y_pos;
int K_x[8] = {1,2,2,1,-1,-2,-2,-1};
int K_y[8] = {2,1,-1,-2,-2,-1,1,2};
int X_x[8] = {-1,0,1,-1,1,-1,0,1};
int X_y[8] = {-1,-1,-1,0,0,1,1,1};
inline void render(int x, int y, int no){ //针对坐标为(x,y)的棋子在attack数组中绘制出攻击范围
    switch (arr[x][y]){
    case 'C'://城堡
        for (int i = x + 1; i <= n; i++){
            if (arr[i][y] == '.')attack[no][i][y] = true;
            else {
                attack[no][i][y] = true;
                break;
            }
        }
        for (int i = x - 1; i >= 1; i--){
            if (arr[i][y] == '.')attack[no][i][y] = true;
            else {
                attack[no][i][y] = true;
                break;
            }
        }
        for (int i = y + 1; i <= n; i++){
            if (arr[x][i] == '.')attack[no][x][i] = true;
            else {
                attack[no][x][i] = true;
                break;
            }
        }
        for (int i = y - 1; i >= 1; i--){
            if (arr[x][i] == '.')attack[no][x][i] = true;
            else {
                attack[no][x][i] = true;
                break;
            }
        }
        break;
    case 'K'://骑士
        for (int i = 0; i < 8; i++){
            if (x + K_x[i]>0 && x + K_x[i] <= n&&y + K_y[i] > 0 && y + K_y[i] <= n){
                attack[no][x + K_x[i]][y + K_y[i]] = true;
            }
        }
        break;
    case 'B'://主教
        for (int i = 1; y - i > 0 && x + i <= n; i++){//向右上角移动
            if (arr[x + i][y - i] == '.')attack[no][x + i][y - i] = true;
            else {
                attack[no][x + i][y - i] = true;
                break;
            }
        }
        for (int i = 1; y + i <= n && x + i <= n; i++){//向右下角移动
            if (arr[x + i][y + i] == '.')attack[no][x + i][y + i] = true;
            else{
                attack[no][x + i][y + i] = true;
                break;
            }
        }
        for (int i = 1; y + i <= n && x - i > 0; i++){//向左下角移动
            if (arr[x - i][y + i] == '.')attack[no][x - i][y + i] = true;
            else{
                attack[no][x - i][y + i] = true;
                break;
            }
        }
        for (int i = 1; y - i > 0 && x - i > 0; i++){//向左上角移动
            if (arr[x - i][y - i] == '.')attack[no][x - i][y - i] = true;
            else{
                attack[no][x - i][y - i] = true;
                break;
            }
        }
        break;
    case 'Q'://皇后
        //城堡
        for (int i = x + 1; i <= n; i++){
            if (arr[i][y] == '.')attack[no][i][y] = true;
            else {
                attack[no][i][y] = true;
                break;
            }
        }
        for (int i = x - 1; i >= 1; i--){
            if (arr[i][y] == '.')attack[no][i][y] = true;
            else {
                attack[no][i][y] = true;
                break;
            }
        }
        for (int i = y + 1; i <= n; i++){
            if (arr[x][i] == '.')attack[no][x][i] = true;
            else {
                attack[no][x][i] = true;
                break;
            }
        }
        for (int i = y - 1; i >= 1; i--){
            if (arr[x][i] == '.')attack[no][x][i] = true;
            else {
                attack[no][x][i] = true;
                break;
            }
        }
        //主教
        for (int i = 1; y - i > 0 && x + i <= n; i++){//向右上角移动
            if (arr[x + i][y - i] == '.')attack[no][x + i][y - i] = true;
            else {
                attack[no][x + i][y - i] = true;
                break;
            }
        }
        for (int i = 1; y + i <= n && x + i <= n; i++){//向右下角移动
            if (arr[x + i][y + i] == '.')attack[no][x + i][y + i] = true;
            else{
                attack[no][x + i][y + i] = true;
                break;
            }
        }
        for (int i = 1; y + i <= n && x - i > 0; i++){//向左下角移动
            if (arr[x - i][y + i] == '.')attack[no][x - i][y + i] = true;
            else{
                attack[no][x - i][y + i] = true;
                break;
            }
        }
        for (int i = 1; y - i > 0 && x - i > 0; i++){//向左上角移动
            if (arr[x - i][y - i] == '.')attack[no][x - i][y - i] = true;
            else{
                attack[no][x - i][y - i] = true;
                break;
            }
        }
        break;
    case 'X'://国王
        for (int i = 0; i < 8; i++){
            if (x + X_x[i]>0 && x + X_x[i] <= n&&y + X_y[i] > 0 && y + X_y[i] <= n){
                attack[no][x + X_x[i]][y + X_y[i]] = true;
            }
        }
        break;
    case 'P'://普通士兵
        if (x - 1 > 0 && x - 1 <= n&&y + 1 > 0 && y + 1 <= n){
            attack[no][x - 1][y + 1] = true;
        }
        if (x + 1 > 0 && x + 1 <= n&&y + 1 > 0 && y + 1 <= n){
            attack[no][x + 1][y + 1] = true;
        }
        break;
    }
}
inline void render_all(){//将地图上的所有点全部重绘
    memset(attack, false, sizeof(attack));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            switch (arr[i][j]){
            case 'O'://标记好白骑士的起始点
                O_x = i;
                O_y = j;
                break;
            case '.':
            case '\0':
                break;
            case 'X'://黑国王的终止点
                X_x_pos = i;
                X_y_pos = j;
            default:
                render(i, j, 1);
            }
        }
    }
}
void dfs(int x, int y,int step){//记忆化dfs
    if (x <= 0 || y <= 0 || x > n || y > n)return; //超出边界的情况
    if (arr[x][y] == 'X'){ //dfs到了黑国王
        if (step < dp[x][y])dp[x][y] = step;
        return;
    }
    if (attack[1][x][y])return; //刚跳到坐标x,y就被攻击了
    if (step>=dp[x][y])return; //注意，这里是重点，也是为什么DFS不会超时的原因，因为我写的这个DFS记忆化不满足无后效性，所以只要走到一点后，当前步数大于之前走到过这里的最小步数就可以退出了。
    dp[x][y] = step;
    if (arr[x][y] != '.'){ //该格子上有棋子
        char ch = arr[x][y];
        arr[x][y] = '.';
        render_all(); //把棋子吃掉以后重新绘制攻击情况
        for (int i = 0; i < 8; i++){
            if (x + K_x[i]>0 && x + K_x[i] <= n&&y + K_y[i] > 0 && y + K_y[i] <= n){
                dfs(x + K_x[i], y + K_y[i], step + 1);
            }
        }
        arr[x][y] = ch; //回溯
        render_all();
    }
    else{ //该格子上无棋子
        for (int i = 0; i < 8; i++){
            if (x + K_x[i]>0 && x + K_x[i] <= n&&y + K_y[i] > 0 && y + K_y[i] <= n){
                dfs(x + K_x[i], y + K_y[i], step + 1);
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false); //加快cin速度
    while (cin >> n){ //多组数据
        memset(arr, 0, sizeof(arr));
        memset(attack, false, sizeof(attack));
        memset(dp, 0x7f, sizeof(dp));
        for (int i = 1; i <= n; i++){
            cin >> arr[i] + 1;
        }
        render_all(); //先进行整幅地图攻击情况的绘制
        dfs(O_x, O_y, 0);
        if (dp[X_x_pos][X_y_pos] == 0x7f7f7f7f){
            cout << -1 << endl;
        }
        else{
            cout << dp[X_x_pos][X_y_pos] << endl;
        }
    }
    return 0;
}
```

---

## 作者：Edgration (赞：0)

# 暴力BFS

这个题的思维难度不大，**但是很考验代码能力**

我的思路是用BFS记录到（x，y）的步数和现在棋盘的状态（用一个1<<16二进制表示棋子现在死了没有）


判断是否到达的点合法，这里采取更暴力的思想，就是判断地图的所有没死的点能不能吃掉它，一次判断的复杂度 O ( n\*n+玄学 )


开一个vis[60][60][1<<16]记录bfs时这个点走过没有，反正n很小，最多16个棋子，随便乱搞就行

这样bfs的话，复杂度为O(n\*n\*(1<<16)\*check), 但是肯定不会把所有状态都搜一遍了，远远达不到这个复杂度，时间给了3s，虽然是多组数据，但是也可以A掉此题

**ps：50分的同学，看看是不是到达最后一个点的时候回被吃掉**

如这个数据，可以试试

```cpp
3
.O.
.P.
X..
```
我的代码虽然特别长，250多行，但有130+行是判断棋子的，虽然很长，有关键注释的，别觉得长就不看了，应该是比较清晰的吧（雾

```cpp
/*
.表示空 0
O表示白骑士1
C表示黑城堡2
K表示黑骑士3
B表示黑主教4
Q表示黒皇后5
X表示黑国王6
P表示黑士兵7
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
char s[60];int n;int sx,sy,ex,ey;
int pre[60][60];bool CAN_GO[60][60][70000];
int dx[]={0,1,1,-1,-1,2,2,-2,-2};
int dy[]={0,2,-2,2,-2,1,-1,1,-1};
int map[60][60];int Ctnum[60][60];int Ct=0;
struct node{
    int x,y;
    int type;
    node(int _x=0,int _y=0,int _type=0){
        x=_x;y=_y;type=_type;
    }
}chess[60];
struct Que{//BFS用的结构体 
    int x,y,zt;int step;
    Que(int _x,int _y,int _zt,int _s){
        x=_x;y=_y;zt=_zt;step=_s;
    }
};
inline int getint(char s){
    if(s=='.') return 0;
    if(s=='O') return 1;
    if(s=='C') return 2;
    if(s=='K') return 3;
    if(s=='B') return 4;
    if(s=='Q') return 5;
    if(s=='X') return 6;
    if(s=='P') return 7; 
    return 0;
}
#define mp make_pair

inline bool no_GG(int zt,int num){//判断num这个棋子是不是没死 
    if(zt&(1<<num)) return true;
    else return false;    
}
namespace CHESS{//下面的是判断(x,y)位子的棋子能不能吃掉(a,b)位子的棋子 
    inline bool C(int x,int y,int a,int b,int zt){
        if(a!=x&&b!=y) return true;
        if(b==y){
            for(int i=x-1;i>=1;i--){
                if(i==a&&y==b) return false;
                if(map[i][y]>1&&no_GG(zt,Ctnum[i][y])) break;    
            } 
            for(int i=x+1;i<=n;i++){
                if(i==a&&y==b) return false;
                if(map[i][y]>1&&no_GG(zt,Ctnum[i][y])) break;
            }    
        }
        else if(a==x){
            for(int i=y-1;i>=1;i--){
                if(a==x&&i==b) return false;
                if(map[x][i]>1&&no_GG(zt,Ctnum[x][i])) break;
            }
            for(int i=y+1;i<=n;i++){    
                if(a==x&&i==b) return false;
                if(map[x][i]>1&&no_GG(zt,Ctnum[x][i])) break;
            }
        }
        return true;
    }
    inline bool K(int x,int y,int a,int b,int zt){
        for(int i=1;i<=8;i++){
            if(a==x+dx[i]&&b==y+dy[i]) 
                return false;
        }
        return true;
    }
    inline bool B(int x,int y,int a,int b,int zt){
        for(int i=x+1,j=y+1;i<=n&&j<=n;i++,j++){
            if(i==a&&j==b) return false;
            if(map[i][j]>1&&no_GG(zt,Ctnum[i][j])) break;
        }
        for(int i=x-1,j=y-1;i>=1&&j>=1;i--,j--){
            if(i==a&&j==b) return false;
            if(map[i][j]>1&&no_GG(zt,Ctnum[i][j])) break;
        }
        for(int i=x+1,j=y-1;i<=n&&j>=1;i++,j--){
            if(i==a&&j==b) return false;
            if(map[i][j]>1&&no_GG(zt,Ctnum[i][j])) break;
        }
        for(int i=x-1,j=y+1;i>=1&&j<=n;i--,j++){
            if(i==a&&j==b) return false;
            if(map[i][j]>1&&no_GG(zt,Ctnum[i][j])) break;
        }
        return true;
        return true;
    }
    inline bool Q(int x,int y,int a,int b,int zt){
        if(b==y){
            for(int i=x-1;i>=1;i--){
                if(i==a&&y==b) return false;
                if(map[i][y]>1&&no_GG(zt,Ctnum[i][y])) break;    
            } 
            for(int i=x+1;i<=n;i++){
                if(i==a&&y==b) return false;
                if(map[i][y]>1&&no_GG(zt,Ctnum[i][y])) break;
            }    
        }
        else if(a==x){
            for(int i=y-1;i>=1;i--){
                if(a==x&&i==b) return false;
                if(map[x][i]>1&&no_GG(zt,Ctnum[x][i])) break;
            }
            for(int i=y+1;i<=n;i++){    
                if(a==x&&i==b) return false;
                if(map[x][i]>1&&no_GG(zt,Ctnum[x][i])) break;
            }
        }
        for(int i=x+1,j=y+1;i<=n&&j<=n;i++,j++){
            if(i==a&&j==b) return false;
            if(map[i][j]>1&&no_GG(zt,Ctnum[i][j])) break;
        }
        for(int i=x-1,j=y-1;i>=1&&j>=1;i--,j--){
            if(i==a&&j==b) return false;
            if(map[i][j]>1&&no_GG(zt,Ctnum[i][j])) break;
        }
        for(int i=x+1,j=y-1;i<=n&&j>=1;i++,j--){
            if(i==a&&j==b) return false;
            if(map[i][j]>1&&no_GG(zt,Ctnum[i][j])) break;
        }
        for(int i=x-1,j=y+1;i>=1&&j<=n;i--,j++){
            if(i==a&&j==b) return false;
            if(map[i][j]>1&&no_GG(zt,Ctnum[i][j])) break;
        }
        return true;
    }
    inline bool X(int x,int y,int a,int b,int zt){
        for(int i=x-1;i<=x+1;i++)
            for(int j=y-1;j<=y+1;j++)
                if(i==a&&j==b) return false;
        return true;
    }
    inline bool P(int x,int y,int a,int b,int zt){
        if((a==x+1&&b==y+1)||(a==x+1&&b==y-1))
            return false;
        return true;
    }
    inline bool solve(int x,int y,int zt){//暴力判断这个点在这个状态下是否合法 
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
        {
            if(!Ctnum[i][j]) continue;
            int num=Ctnum[i][j];
            if(!no_GG(zt,num)) continue; 
            int type=chess[num].type;
            if(type==2) 
                if(!C(i,j,x,y,zt)) return false;
            if(type==3) 
                if(!K(i,j,x,y,zt)) return false;
            if(type==4) {
                if(!B(i,j,x,y,zt)) return false;
            }
            if(type==5) {
                if(!Q(i,j,x,y,zt)) return false;
            }
            if(type==6) {
                if(!X(i,j,x,y,zt)) return false;
            }
            if(type==7) {
                if(!P(i,j,x,y,zt)) return false;
             }
        }
        return true;
    }
}
using namespace CHESS;
queue<Que>q;
inline bool in_map(int x,int y){//是不是在地图内 
    return (x>=1&&x<=n&&y>=1&&y<=n);
} 
inline void Work(){//主体部分 
    int zt=(1<<(Ct+1))-1;
    if(!solve(sx,sy,zt)) {printf("-1\n");return;}
    Que fr = Que(sx,sy,zt,0);
    q.push(fr);CAN_GO[sx][sy][zt]=1;
//    printf("(%d,%d) %d\n",sx,sy,0);
    while(!q.empty()){
        Que fr=q.front();q.pop();
        int x=fr.x;int y=fr.y;int zzt=fr.zt;int step=fr.step;
    
        for(int i=1;i<=8;i++){
            int Dx=x+dx[i];int Dy=y+dy[i];
            if(!in_map(Dx,Dy)) continue;
        //    printf("(%d,%d) %d\n",Dx,Dy,step+1);
            if(Ctnum[Dx][Dy]!=0){//这个位子以前有棋子 
                int num=Ctnum[Dx][Dy];
                if(Dx==ex&&Dy==ey){//终点 
                            printf("%d\n",step+1);
                            return;
                        }
                if(no_GG(zzt,num)){//没死 
                    int ppt=zzt^(1<<num);//把这个地方的棋子吃掉 
                    if(solve(Dx,Dy,ppt)&&!CAN_GO[Dx][Dy][ppt]){        
                        q.push(Que(Dx,Dy,ppt,step+1));
                        CAN_GO[Dx][Dy][ppt]=1;
                    }
                }
                else{//死了 
                    if(solve(Dx,Dy,zzt)&&!CAN_GO[Dx][Dy][zzt]){
                    
                        q.push(Que(Dx,Dy,zzt,step+1));
                        CAN_GO[Dx][Dy][zzt]=1;
                    }
                }
            }
            else if(solve(Dx,Dy,zzt)&&!CAN_GO[Dx][Dy][zzt]){//没有子，同死了的情况 
                        q.push(Que(Dx,Dy,zzt,step+1));
                        CAN_GO[Dx][Dy][zzt]=1;
            }
        } 
    }
    printf("-1\n");return;
}
inline void Clear(){//多组数据 
    memset(CAN_GO,0,sizeof(CAN_GO));
    Ct=0;
    memset(Ctnum,0,sizeof(Ctnum));
    ex=0;ey=0;sx=0;sy=0;
    memset(map,0,sizeof(map));
    while(q.size())q.pop();
} 
int main(){
    while(scanf("%d",&n)!=EOF){
        Clear();
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s+1);
            for(int j=1;j<=n;j++){ 
                map[i][j]=getint(s[j]);//读入，如果是有攻击性的棋子就存下来 
                if(map[i][j]==0) continue;
                else if(map[i][j]==1){sx=i;sy=j;}
                else if(map[i][j]==6){ex=i;ey=j;chess[++Ct]=node(i,j,map[i][j]);Ctnum[i][j]=Ct;}
                else {chess[++Ct]=node(i,j,map[i][j]);Ctnum[i][j]=Ct;}
            }
        }    
        Work();
    }
    return 0;
}
```

---

## 作者：浮尘ii (赞：0)

额题解说是状压DP，std给的是hash+BFS...

这里给出状压+BFS！

是目前提交的里面跑得最快的。（当然从下面就能看出至少有两个地方可以优化，懒得写了。）


思路大致就是对16个黑棋是否被打掉进行状态压缩，用二进制表示。

然后状态数理论上有2^16\*n\*n，但是根据题解，黑骑士无法被打掉（如果能打掉黑骑士，那么在前一位置就已经被黑骑士打掉），所以状态数变成了2^14\*n\*n，转移需要O(n)进行check，这里check需要结合状态进行判断。


一开始手写队列开小了RE开大了MLE，一气之下改成了STL的queue。

然后在去重的时候，由于2^16的vis数组开不下，又不想编号的时候把黑骑士给删掉，用了C++11的unordered\_set(hash表)，改成set也没有问题的。


还有就是要注意一下多组数据。


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <unordered_set>
#include <queue>

using namespace std;

const size_t    MaxN = 60;
const int    Dx[] = {1, 1, 2, 2, -1, -1, -2, -2}, Dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

struct QueTp {
    int    i, j, step, state;
} ;

queue<QueTp>        Q;
int            N, Si, Sj;
char            A[MaxN][MaxN];
int            ID[MaxN][MaxN], Tot;
unordered_set<int>    Vis[MaxN][MaxN];

bool Check(const int& state, const int& i, const int& j)
{
    if(Vis[i][j].count(state))
        return false;
    for(int x = i + 1; x <= N; ++x)
        if(A[x][j] != '.' && !((1 << ID[x][j]) & state)) {
            if(A[x][j] == 'C' || A[x][j] == 'Q')
                return false;
            break;
        }
    for(int x = i - 1; x > 0; --x)
        if(A[x][j] != '.' && !((1 << ID[x][j]) & state)) {
            if(A[x][j] == 'C' || A[x][j] == 'Q')
                return false;
            break;
        }
    for(int x = j + 1; x <= N; ++x)
        if(A[i][x] != '.' && !((1 << ID[i][x]) & state)) {
            if(A[i][x] == 'C' || A[i][x] == 'Q')
                return false;
            break;
        }
    for(int x = j - 1; x > 0; --x)
        if(A[i][x] != '.' && !((1 << ID[i][x]) & state)) {
            if(A[i][x] == 'C' || A[i][x] == 'Q')
                return false;
            break;
        }
    for(int x = i - 1, y = j - 1; x > 0 && y > 0; --x, --y)
        if(A[x][y] != '.' && !((1 << ID[x][y]) & state)) {
            if(A[x][y] == 'B' || A[x][y] == 'Q')
                return false;
            break;
        }
    for(int x = i - 1, y = j + 1; x > 0 && y <= N; --x, ++y)
        if(A[x][y] != '.' && !((1 << ID[x][y]) & state)) {
            if(A[x][y] == 'B' || A[x][y] == 'Q')
                return false;
            break;
        }
    for(int x = i + 1, y = j - 1; x <= N && y > 0; ++x, --y)
        if(A[x][y] != '.' && !((1 << ID[x][y]) & state)) {
            if(A[x][y] == 'B' || A[x][y] == 'Q')
                return false;
            break;
        }
    for(int x = i + 1, y = j + 1; x <= N && y <= N; ++x, ++y)
        if(A[x][y] != '.' && !((1 << ID[x][y]) & state)) {
            if(A[x][y] == 'B' || A[x][y] == 'Q')
                return false;
            break;
        }
    for(int t = 0; t != 8; ++t) {
        int    x = i + Dx[t], y = j + Dy[t];
        if(x > 0 && y > 0 && x <= N && y <= N && A[x][y] == 'K')
            return false;
    }
    if(i != 1 && ((j != N && A[i - 1][j + 1] == 'P' && !((1 << ID[i - 1][j + 1]) & state)) || (j != 1 && A[i - 1][j - 1] == 'P' && !((1 << ID[i - 1][j - 1]) & state))))
        return false;
    for(int x = i - 1; x <= i + 1; ++x) {
        if(x < 1 || x > N)
            continue;
        for(int y = j - 1; y <= j + 1; ++y)
            if(y > 0 && y <= N && A[x][y] == 'X')
                return false;
    }
    return true;
}
```




```cpp
void Work()
{
    Q = queue<QueTp>(), Tot = 0;
    memset(ID, -1, sizeof(ID));
    memset(A, 0, sizeof(A));
    for(int i = 1; i <= N; i++) {
        scanf("%s", A[i] + 1);
        for(int j = 1; j <= N; j++) {
            if(A[i][j] == 'O')
                Si = i, Sj = j, A[i][j] = '.';
            else if(A[i][j] == 'C' || A[i][j] == 'K' || A[i][j] == 'B' || A[i][j] == 'Q' || A[i][j] == 'X' || A[i][j] == 'P')
                ID[i][j] = Tot++;
            else
                A[i][j] = '.';
            Vis[i][j].clear();
        }
    }
    if(!Check(0, Si, Sj)) {
        puts("-1");
        return;
    }
    Vis[Si][Sj].insert(0);
    Q.push((QueTp) {Si, Sj, 0, 0});
    while(!Q.empty()) {
        for(int i = 0; i != 8; ++i) {
            int    x = Q.front().i + Dx[i], y = Q.front().j + Dy[i], state = Q.front().state;
            if(x < 1 || x > N || y < 1 || y > N)
                continue;
            if(A[x][y] == 'X') {
                printf("%d\n", Q.front().step + 1);
                return;
            }
            if(A[x][y] != '.')
                state |= 1 << ID[x][y];
            if(Check(state, x, y))
                Vis[x][y].insert(state), Q.push((QueTp) {x, y, Q.front().step + 1, state});
        }
        Q.pop();
    }
    puts("-1");
}
int main()
{
    while(cin >> N)
        Work();
    return 0;
}
```
```cpp

---

