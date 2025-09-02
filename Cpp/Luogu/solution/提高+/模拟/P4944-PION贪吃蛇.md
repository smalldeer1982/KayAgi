# PION贪吃蛇

## 题目背景

NOIP2018原创模拟题 T3

NOIP DAY1 T3 or DAY 2 T2 难度

贪吃蛇大家都玩过吧，当然不同版本有不同规则。下面介绍PION贪吃蛇。

## 题目描述

![图A](https://cdn.luogu.com.cn/upload/pic/31298.png)

***表示方法：***

该题中贪吃蛇存在于一个n行m列的矩形中，用 ‘.’ 表示空地，用 '#’ 表示蛇身，用 ‘@’表示蛇头，用‘&’表示食物
例如：图一表示 $5*6$ 的矩形，有一条蛇，蛇长度为 $7$，有两个食物

***基本规则：***

1.蛇头每一秒就会移动一格，身体自然会跟着移动，用W表示向上，S表示向下，A表示向左，D表示向右

2.蛇每吃一个食物就长度就会加一，而增加的长度体现在食物所在的地方，你可以把吃食物理解成食物变成了蛇头，之前的蛇头变成了蛇身，这一秒不移动

例如：图二的三幅图展示了第一秒，第二秒，和第三秒的情况

3.蛇如果死亡，身体（包括头）一定会全部变成食物

4.PION贪吃蛇的蛇头碰到自己或别的蛇的身体就会死亡

例如：图三的三幅图展示了第二条蛇撞在别人身体上死亡的过程

5.蛇头撞在边界上也会引起死亡，但蛇头刚好现在边界上不会

例如：图四第二幅图虽然蛇头在边界上，但是只是刚好，如果此时进行D操作蛇就会死亡，如果进行W或S就不会

6.如果有操作使蛇头向相反方向运动，之后如果与身体重合蛇也会死亡（比如：图二第一幅图使用A操作,蛇就会死亡，此时在原地成为三个食物，你也可以理解为蛇下一秒不行动而自杀了）

7.两条蛇蛇头相撞，主动撞上的死亡

8.蛇的移动按编号由小到大进行（编号的含义见下文）


## 说明/提示

***样例说明：***

![图B](https://cdn.luogu.com.cn/upload/pic/31357.png)

图五，图六展示了从第 $0$ 秒开始之后每一秒地图的状态，请看图理解（样例二图四有点小错误）

***数据范围：***

$10\%$ 数据满足 $n,m\leq 5,c=1,k\leq3$

$30\%$ 数据满足 $n,m\leq 10,c\leq 2,k\leq 5$

$50\%$ 数据满足 $n,m\leq 50,c\leq 5,k\leq 20$

$70\%$ 数据满足 $n,m\leq 100,c\leq 7,k\leq 50$

$100\%$ 数据满足 $n,m\leq 200,c\leq 20,k\leq 100$，且图中的蛇不会引起混淆（对于任意蛇头，最多只有一块蛇身于其相连，而蛇身最多为二连块）,且数据保证图中的蛇均可以判断身体与头的对应关系，不会造成蛇身形态多解

## 样例 #1

### 输入

```
5 7 6
.&...&.
..##@..
.&...&.
..##@..
.&...&.
DWAAAA
WDDDDD```

### 输出

```
5 1
0 2
7```

## 样例 #2

### 输入

```
9 9 4
.........
.#######.
.......#.
.@#.&@.#.
&.#.&&.#.
&&######.
.&.......
..@####..
.........
ASSD
ASDD
WASD```

### 输出

```
22 1
4 2
0 3
6```

# 题解

## 作者：liangbowen (赞：18)

### 前言
[题目传送门！](https://www.luogu.com.cn/problem/P4944)

[或许更好的阅读体验？](https://www.luogu.com.cn/blog/liangbowen/solution-P4944)

这题算是一道中模拟？

码量不会很高，大概只有 $100$ 至 $150$ 行。

### 思路

1. 输入地图。

	注意，还不能读入蛇的行动指令，因为我们不知道**有几条蛇**。
    
2. 使用广搜得出每条蛇的信息。

	这个就是**搜连通块**，惟一不同的是，要使用队列存下这条蛇。
    
3. 写一个死亡函数，处理蛇死亡后的信息。
    
    这个并不困难，只要将队列清空，顺便将整条蛇蛇**变成食物**。
    
4. 写移动函数，这里要分几种情况考虑。

	+ 移动后撞上墙，死掉。

	+ 移动后撞上身体（当然也包括头），死掉。
    
    	此处的『撞上身体』既包括别人的身体，也包括自己的身体。
        
   	+ 移动后有食物。
    
    	我们可以让其他部位保持不动，蛇头向食物处扩充一格。
        
   + 移动后，什么都没有，是平地。
   
   		我们可以做两件事达到效果：
        
      首先扩充蛇头。
      
      然后消除蛇尾。
      
      用普通的队列难以达到这种效果，因此可以使用**双端队列**。
      
5. 读入蛇的行动指令，并移动。
      
6. 最后输出。

	由于题目让我们**按顺序输出**，所以我们需要排序。
    
   然后还要再扫一遍地图，记录食物数量。
   
### 坑点

这些坑点指，题目并没有说清楚的地方，更多细节请查看代码。

1. 很多人都有疑问，为什么可以直接**搜连通块**分辨每条蛇。

	很多人都忽略了一个细节，题目保证了：

	> 图中的蛇不会引起混淆（对于任意蛇头，最多只有一块蛇身于其相连，而**蛇身最多为二连块**）。

	因此，直接搜连通块是可行的。
    
2. 蛇的移动顺序。

	蛇是按照**回合制**移动的，每一回合，编号小的蛇优先行动。
    
### 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <queue> //包含 queue 与 deque 两种数据类型。 
#include <algorithm>  //用于 sort 排序。 
#define N 205
#define C 25
using namespace std;
int n, m, k;
int cur; //表示蛇的数量。 
char a[N][N];  //表示地图。 
int who[N][N]; //表示当前格子属于那一条蛇。
//后来发现这个 who 数组完全没使用到，所以不写也行。 
string order[C]; //代表蛇的行动指令。 
struct node
{
	int x, y;
};
deque <node> snake[C];  //模拟当前的蛇。
void Input1(); //输入地图，不解释。 
void bfs();   //搜索得出蛇的位置。 
void debug();  //调试工具。
void die(int id); //第 id 条蛇死亡了。 
void move(int id, char op); //对第 id 条蛇执行 op 指令。
void Input2(); //输入蛇的运行指令，但顺便利用 move() 函数移动处理。
void Output(); //输出答案。 
int main()
{
	Input1();
	bfs();
	//debug();
	Input2();
	//debug();
	Output();
	return 0;
}

void Input1() //实际输入只能输入一部分，因为必须 bfs 得出蛇的数量后，再输入指令。 
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
}
int dict[5][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
void bfs() //爆搜，没什么技巧。 
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (a[i][j] == '@')
			{
				cur++;
				queue <node> Q;
				Q.push( (node){i, j} );
				while (!Q.empty())
				{
					int x = Q.front().x, y = Q.front().y;
					who[x][y] = cur;
					snake[cur].push_back( (node){x, y} );
					Q.pop();
					for (int i = 0; i <= 3; i++)
					{
						int dx = x + dict[i][0], dy = y + dict[i][1];
						if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
						if (who[dx][dy] == cur) continue;
						if (a[dx][dy] == '#') Q.push( (node){dx, dy} );
					}
				}
			}
}
void debug()
{
	for (int i = 1; i <= cur; i++)
	{
		printf("\ni = %d:\n", i);
		deque <node> Q = snake[i];
		while (!Q.empty())
		{
			printf("(%d %d) ", Q.front().x, Q.front().y);
			Q.pop_front();
		}
	}
}
void die(int id)
{
	while (!snake[id].empty())
	{
		int x = snake[id].front().x, y = snake[id].front().y;
		who[x][y] = 0;  //消除标记。 
		a[x][y] = '&';  //变成食物。
		snake[id].pop_front(); //把蛇给消除。 
	}
}
void move(int id, char op)
{
	int x = snake[id].front().x, y = snake[id].front().y;
	if (op == 'W') x--; //往上。
	if (op == 'S') x++; //往下。
	if (op == 'A') y--; //往左。
	if (op == 'D') y++; //往右。
	
	if (x < 1 || x > n || y < 1 || y > m) //撞边界上了，死亡。 
	{
		die(id);
		return;
	}
	if (a[x][y] == '#' || a[x][y] == '@') //撞身体上了，死亡。
	{
		die(id);
		return;
	}
	int head_x = snake[id].front().x, head_y = snake[id].front().y; //原先的蛇头。
	int tail_x = snake[id].back().x, tail_y = snake[id].back().y; //原先的蛇尾。
	if (a[x][y] == '&') //吃到食物，直接扩充蛇。
	{
		snake[id].push_front( (node){x, y} );
		a[x][y] = '@'; //食物处变成蛇头。
		a[head_x][head_y] = '#';  //曾经的蛇头变成蛇身。
		who[x][y] = id; //标记蛇。 
	}
	if (a[x][y] == '.') //是平路，蛇头扩充，蛇尾消除。 
	{
		//蛇头扩充。 
		snake[id].push_front( (node){x, y} );
		a[x][y] = '@';
		a[head_x][head_y] = '#';
		who[x][y] = id;
		//蛇尾消除。 
		snake[id].pop_back();
		a[tail_x][tail_y] = '.';
		who[tail_x][tail_y] = 0;
	}
}
void Input2()
{
	for (int i = 1; i <= cur; i++) cin >> order[i];
	for (int j = 0; j < k; j++)
		for (int i = 1; i <= cur; i++)
			if (!snake[i].empty()) //需要注意，只有蛇没有死亡，才可以移动。 
				move(i, order[i][j]);
}
struct Snake
//存储每条蛇的信息。 
{
	int len, id;
}p[C];
bool cmp(Snake x, Snake y)
{ 
	if (x.len != y.len) return x.len > y.len;
	return x.id < y.id;
}
void Output()
{
	//计算每条蛇的信息。 
	for (int i = 1; i <= cur; i++)
	{
		p[i].id = i;
		deque <node> Q = snake[i];
		while (!Q.empty())
		{
			p[i].len++;
			Q.pop_back();
		}
	}
	sort(p+1, p+cur+1, cmp);  //按题目所述排序。
	for (int i = 1; i <= cur; i++) printf("%d %d\n", p[i].len, p[i].id);
	//计算食物数量并输出。
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (a[i][j] == '&')
				cnt++;
	printf("%d", cnt); 
}
```

---

## 作者：communist (赞：9)

### 简单模拟题

用一个数据结构存储这条蛇

考虑蛇的移动

1，如果死了，就把整个蛇清空，所有位置标记为食物

2，如果吃了东西，把这个位置更新为蛇头

3，如果正常走路，这个位置设为蛇头，同时删掉尾巴

蛇的存储？观察到我们涉及的所有操作，双端队列无疑是$The~~Best~~Choice$

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
//q.front -> head
//q.back -> tail
//mp{
// 0 -> square ; 1 -> edge ; 2-> food
//}
const int dx[]={1,-1,0,0};
const int dy[]={0,0,-1,1};
struct pos{
    int x,y;
};
struct length{
    int id,len;
}ans[30];
map<char,int>to;
deque<pos>sk[30];
int n,m,k,mp[210][210],cnt;
char s[210][210],op[30][110];
void bfs(int id,int x,int y)
{
    queue<pos>q;
    q.push((pos){x,y});
    while(!q.empty())
    {
        pos u=q.front();
        sk[id].push_back(u);
        mp[u.x][u.y]=1;
        q.pop();
        for(int i=0;i<4;i++)
        {
            pos th;
            th.x=u.x+dx[i];
            th.y=u.y+dy[i];
            if(s[th.x][th.y]=='#')
                q.push(th),s[th.x][th.y]='.';
        }
    }
}
void work(int x)
{
    for(int i=1;i<=cnt;i++)
    {
        if(!sk[i].size())
            continue;
        pos th;
        th.x=sk[i].front().x+dx[to[op[i][x]]];
        th.y=sk[i].front().y+dy[to[op[i][x]]];
        if(mp[th.x][th.y]==2)
            sk[i].push_front(th),mp[th.x][th.y]=1;
        else if(mp[th.x][th.y]==1)
            while(!sk[i].empty())
            {
                mp[sk[i].front().x][sk[i].front().y]=2;
                sk[i].pop_front();
            }
        else
        {
            mp[sk[i].back().x][sk[i].back().y]=0,mp[th.x][th.y]=1;
            sk[i].push_front(th),sk[i].pop_back();
        }
    }
}
bool cmp(const length &x,const length &y)
{
    return x.len==y.len?x.id<y.id:x.len>y.len;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    to['W']=1,to['S']=0,to['A']=2,to['D']=3;
    for(int i=1;i<=n;i++)
        mp[i][0]=mp[i][m+1]=1;
    for(int i=1;i<=m;i++)
        mp[0][i]=mp[n+1][i]=1;
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(s[i][j]=='&')
                mp[i][j]=2;
            else if(s[i][j]=='@')
                bfs(++cnt,i,j);
    for(int i=1;i<=cnt;i++)
        scanf("%s",op[i]+1);
    for(int i=1;i<=k;i++)
        work(i);
    for(int i=1;i<=cnt;i++)
        ans[i].len=sk[i].size(),ans[i].id=i;
    sort(ans+1,ans+cnt+1,cmp);
    for(int i=1;i<=cnt;i++)
        printf("%d %d\n",ans[i].len,ans[i].id);
    int res=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]==2)
                res++;
    printf("%d\n",res);
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：8)

首先第一步，我们需要识别每一条蛇。因为不可能出现多种解法，所以这一步十分简单。我们每扫到一个 `@`，就每一次向四个方向枚举一遍，看哪边是 `#` 并且不是从上一个 `#` 过来的，沿着蛇身的方向走就可以了。

因为我们以后操作的时候，可能就会出现蛇身形态多解的问题（比如蛇身在一个 $2\times2$ 的块里），所以我们在识别蛇的过程中，把每一个蛇身都标记上它前面的蛇身（或蛇头）在它的什么方向。这样也能便于我们以后操作时更新蛇尾的位置。举个例子，当原来的蛇是这样时：

```
@..#
####
```

则我们可以把蛇更改为这个样子：

```
@..S
WAAA
```

我们还要记录下编号。可以顺便记录下蛇头、蛇尾的位置和蛇身的长度，以便于以后的操作。

---

第二步，我们就可以模拟操作了。先按照每一步的顺序操作，每步里面再按照编号从小到大的顺序操作。模拟的时候主要有以下几个过程：

1. 当前这条蛇已经死了，跳过。
1. 操作越界，那么这条蛇死了，跳过。
1. 撞到自己或别人、向相反方向运动，那么这条蛇死了，跳过。
1. 如果目标位置是空地：原先的蛇头变为蛇身；目标位置变成蛇头并更新蛇头位置；原先的蛇尾变成空地并更新蛇尾位置。
1. 如果目标位置是食物：长度加一；原先的蛇头变为蛇身；目标位置变成蛇头并更新蛇头位置。

---

最后随便把蛇按照长度为第一关键字、编号为第二关键字排序一下输出就行了。代码如下：

```cpp
#include<iostream>
using namespace std;
char a[210][210];//地图
int dx[]={0,-1,0,1,0};
int dy[]={0,0,-1,0,1};
//WASD 的方向
int hx[30],hy[30],tx[30],ty[30],l[30],num[30];
//头坐标，尾坐标，长度（排序用），编号
bool vis[210][210];//有没有识别到过这个格子
char b[30][110];//每一步操作
void dead(int id)//蛇死了之后进行的操作
{
    l[id]=0;
    int x=tx[id],y=ty[id];
    while(1)
    {
        char c=a[x][y];
        a[x][y]='&';
        if(x==hx[id]&&y==hy[id])return;
        if(c=='W')x--;
        if(c=='A')y--;
        if(c=='S')x++;
        if(c=='D')y++;
    }
}
int main()
{
    int n,m,k,c=0;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]=='@')//识别一条蛇
            {
                c++;
                int len=0;
                hx[c]=i,hy[c]=j,vis[i][j]=1;
                int x=i,y=j;
                while(1)
                {
                	len++;
                    bool flag=0;
                    for(int i=1;i<=4;i++)
                    {
                        int nx=x+dx[i],ny=y+dy[i];
                        if(nx<1||nx>n||ny<1||ny>m)continue;
                        if(a[nx][ny]!='#')continue;
                        if(vis[nx][ny])continue;
                        vis[nx][ny]=1;
                        flag=1,x=nx,y=ny;
                        if(i==1)a[nx][ny]='S';
                        if(i==2)a[nx][ny]='D';
                        if(i==3)a[nx][ny]='W';
                        if(i==4)a[nx][ny]='A';
                        break;
                    }
                    if(!flag)
                    {
                        tx[c]=x,ty[c]=y;
                        break;
                    }
                }
                l[c]=len;
            }
    for(int i=1;i<=c;i++)num[i]=i;
    for(int i=1;i<=c;i++)
        for(int j=1;j<=k;j++)
            cin>>b[i][j];
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=c;j++)
        {
            //蛇已经死了
        	if(l[j]==0)continue;
            //计算目标位置
            int nx,ny;
            if(b[j][i]=='W')nx=hx[j]-1,ny=hy[j];
            if(b[j][i]=='A')nx=hx[j],ny=hy[j]-1;
            if(b[j][i]=='S')nx=hx[j]+1,ny=hy[j];
            if(b[j][i]=='D')nx=hx[j],ny=hy[j]+1;
            //越界
            if(nx<1||nx>n||ny<1||ny>m){dead(j);continue;}
            //撞到自己或别人、朝相反方向运动
            if(a[nx][ny]=='@'||(a[nx][ny]>='A'&&a[nx][ny]<='Z'&&(nx!=hx[j]||ny!=hy[j])))
                {dead(j);continue;}
            if(a[nx][ny]=='.')//目标位置是空地
            {
                //蛇头移动
                a[hx[j]][hy[j]]=b[j][i];
                hx[j]=nx,hy[j]=ny;
                a[hx[j]][hy[j]]='@';
                //蛇尾移动
                int nnx=tx[j],nny=ty[j];
                if(a[tx[j]][ty[j]]=='W')tx[j]--;
                else if(a[tx[j]][ty[j]]=='A')ty[j]--;
                else if(a[tx[j]][ty[j]]=='S')tx[j]++;
                else if(a[tx[j]][ty[j]]=='D')ty[j]++;
                a[nnx][nny]='.';
            }
            else//目标位置是食物
            {
                l[j]++;//改变长度
                //蛇头移动
                a[hx[j]][hy[j]]=b[j][i];
                hx[j]=nx,hy[j]=ny;
                a[hx[j]][hy[j]]='@';
            }
        }
    }
    //因为懒得改成结构体，所以就用选择排序了。
    for(int i=1;i<=c;i++)
        for(int j=i+1;j<=c;j++)
            if(l[j]>l[i]||(l[j]==l[i]&&num[j]<num[i]))
            {
                swap(l[i],l[j]);
                swap(num[i],num[j]);
            }
    for(int i=1;i<=c;i++)
        cout<<l[i]<<" "<<num[i]<<endl;
    int food=0;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		food+=(a[i][j]=='&');
    cout<<food<<endl;
    return 0;
}
```

---

## 作者：liruixiong0101 (赞：7)

~~本题很水，只能算上中模拟吧。~~  
第一步就是选一个合适的数据结构存储蛇身，毫无疑问 deque 双端队列是最好的选择，因为这样移动会更方便。   
下一步要输入地图找蛇和蛇的头，找蛇头很好找，遍历一遍数组即可，而找蛇可以用 dfs 找连通块，但有人会有疑问为什么可以用连通块扫蛇身呢，不会混淆吗？  
**不会的。**  
因为题目保证了：  
> ### 图中的蛇不会引起混淆（对于任意蛇头，最多只有一块蛇身于其相连，而蛇身最多为二连块）,且数据保证图中的蛇均可以判断身体与头的对应关系，不会造成蛇身形态多解。  
这很重要，所以可以用 dfs 连通块求蛇身。

```cpp
int n , m , k;
int cnt_snack , cnt_food;//分别是蛇的数量和事物的数量
int dx[4] = {0 , 0 , 1 , -1} , dy[4] = {1 , -1 , 0 , 0};
bool vis[205][205];
char c[205][205] , d[205][205];//地图和输入的操作
struct node{
	int x , y;
};
deque <node> q[25];
void dfs(int x , int y){
	vis[x][y] = 1;
	q[cnt_snack].push_back((node){x , y});//存储进双端队列首
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i] , ny = y + dy[i];
		if(c[nx][ny] == '#' && !vis[nx][ny])// 是#并且没有遍历过
			dfs(nx , ny);
	}
}
```
 
而移动就需要判断是否碰壁，是否吃到食物等等，细节很多，代码如下：
```cpp
void died(deque <node> &q){//蛇无了
	while(!q.empty()){
		cnt_food++;//食物++
		c[q.front().x][q.front().y] = '&';//变成食物
		q.pop_front();
	}
	return;
}
void eat(deque <node> &q , int x , int y){//吃食物
    cnt_food--;//食物减少
    c[x][y] = '@';//蛇头移动
    c[q.front().x][q.front().y] = '#';//蛇身移动
    q.push_front((node){x , y});//加入队首
    return;
}
void dir(deque <node> &q , int num , int dx , int dy){//移动
	int headx = q.front().x + dx , heady = q.front().y + dy;//下一步到的位置
	if(c[headx][heady] != '.' && c[headx][heady] != '&') died(q);//蛇撞到了墙或蛇
	else if(c[headx][heady] == '&') eat(q , headx , heady);//蛇撞到了食物
   else{//否则正常移动
		c[q.back().x][q.back().y] = '.';
		if(q.size() != 1) c[q.front().x][q.front().y] = '#';
		q.pop_back();
		q.push_front((node){headx , heady});
		c[headx][heady] = '@';
   }
   return;
}

```
最后移动完了，排序后输出。
```cpp
struct snack{
	int id , len;
}Snack[25];
bool cmp(snack x , snack y){
    if(x.len != y.len) return x.len > y.len;
    else return x.id < y.id;
    //按长度由大到小排序（长度相同按编号由小到大排序）
}
int main(){
	......
	for(int i = 1; i <= cnt_snack; i++){//存蛇的长度
	    int len = q[i].size();
	    Snack[i] = (snack){i , len};
	}
	sort(Snack + 1 , Snack + 1 + cnt_snack , cmp);//排序
	for(int i = 1; i <= cnt_snack; i++){//输出蛇的信息
	    cout << Snack[i].len << " " << Snack[i].id << "\n";
	}
	cout << cnt_food;//输出食物个数
	return 0;
}
```
# AC CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , m , k , cnt_food , cnt_snack;
int dx[4] = {0 , 0 , 1 , -1} , dy[4] = {1 , -1 , 0 , 0};
char c[205][205] , d[25][105];
bool vis[205][205];
struct node{
	int x , y;
};
struct snack{
	int id , len;
}Snack[25];
bool cmp(snack x , snack y){
    if(x.len != y.len) return x.len > y.len;
    else return x.id < y.id;
}
deque <node> q[25];
void dfs(int x , int y){
	vis[x][y] = 1;
	q[cnt_snack].push_back((node){x , y});
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i] , ny = y + dy[i];
		if(c[nx][ny] == '#' && !vis[nx][ny])
			dfs(nx , ny);
	}
}
void died(deque <node> &q){
	while(!q.empty()){
		cnt_food++;
		c[q.front().x][q.front().y] = '&';
		q.pop_front();
	}
	return;
}
void eat(deque <node> &q , int x , int y){
    cnt_food--;
    c[x][y] = '@';
    c[q.front().x][q.front().y] = '#';
    q.push_front((node){x , y});
    return;
}
void dir(deque <node> &q , int num , int dx , int dy){
	int headx = q.front().x + dx , heady = q.front().y + dy;
	if(c[headx][heady] != '.' && c[headx][heady] != '&') died(q);
	else if(c[headx][heady] == '&') eat(q , headx , heady);
    else{
        c[q.back().x][q.back().y] = '.';
        if(q.size() != 1) c[q.front().x][q.front().y] = '#';
        q.pop_back();
	    q.push_front((node){headx , heady});
	    c[headx][heady] = '@';
    }
    return;
}
int main(){
	memset(c , 'x' , sizeof(c));
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> c[i][j];
			if(c[i][j] == '&') cnt_food++;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(c[i][j] == '@'){
				cnt_snack++;
				dfs(i , j);
			}
		}
	}
	for(int i = 1; i <= cnt_snack; i++){
		for(int j = 1; j <= k; j++){
			cin >> d[i][j];
		}
	}
	for(int t = 1; t <= k; t++){
		for(int i = 1; i <= cnt_snack; i++){
			char direction = d[i][t];
			if(q[i].empty()) continue;
			if(direction == 'A') dir(q[i] , i , 0 , -1);
			if(direction == 'S') dir(q[i] , i , 1 , 0);
			if(direction == 'D') dir(q[i] , i , 0 , 1);
			if(direction == 'W') dir(q[i] , i , -1 , 0);
		}
	}
	for(int i = 1; i <= cnt_snack; i++){
	    int len = q[i].size();
	    Snack[i] = (snack){i , len};
	}
	sort(Snack + 1 , Snack + 1 + cnt_snack , cmp);
	for(int i = 1; i <= cnt_snack; i++){
	    cout << Snack[i].len << " " << Snack[i].id << "\n";
	}
	cout << cnt_food;
    return 0;
}
```

---

## 作者：wuyuema (赞：5)

哇看了一下，开O2以后以23ms拿到了提交排行榜rank1，激动之下写了这篇题解！！

所以说相比其他人，我的代码快在哪里呢？

答案是：链表。

写这个题解，其实是为了向大家普及stl::list

这里用到了最基本的list操作：  push()  和  pop()  ，它们都有两种子操作：

1.  push_front()，push_back()

2.  pop_front(), pop_back()

其实类似  deque  ，但是能优化一部分时间！

需要注意的是使用  end()  时需要减1，否则会RE。

还需要注意的是，stl::list、stl::queue、stl::stack的迭代器都不支持直接加减。这里要用到  end() - 1  的话就用  --end()  就行了awa

小坑写在代码里面了，请自行收看吧~~

```cpp
#include <cstdio>
#include <list>
#include <cstring>
#include <queue>
using namespace std;
const int st[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
int n, m, k;
int a[205][205];
bool b[205][205];
int cmd[21][105];
struct node {
	int x, y;
	node(int x, int y) : x(x), y(y) {}
};
list<node> sn[21]; // a list to record the snakes 
//sn[i].size == 0 refers that Snake I is dead
int cnt; // the number of the snakes 

void find(node s) {
	memset(b, 0, sizeof(b));
	sn[++cnt].push_back(s);
	queue<node> q;
	q.push(s);
	while (!q.empty()) {
		node u = q.front();
		q.pop();
		b[u.x][u.y] = 1;
		for (int i = 0; i < 4; i++) {
			int tx = u.x + st[i][0], ty = u.y + st[i][1];
			if (!b[tx][ty] && a[tx][ty] == '#' && tx >= 1 && tx <= n && ty >= 1 && ty <= m) {
				sn[cnt].push_back(node(tx, ty)); // recording the node of the snake
				b[tx][ty] = 1;
				q.push(node(tx, ty)); // to record the current searching state
				break;
			}
		}
	}
}

inline void move(int sid, int d) {
	if (!sn[sid].size() || d == -1) return;
	register node head = *sn[sid].begin();
	int tx = head.x + st[d][0], ty = head.y + st[d][1];
	if (a[tx][ty] == '#' || a[tx][ty] == '@') { // gg
		while (!sn[sid].empty()) {
			register node u = sn[sid].front();
			sn[sid].pop_front();
			a[u.x][u.y] = '&';
		}
		return;
	}
	if (a[tx][ty] != '&') { // not eating 
		register node tail = *--sn[sid].end();
		a[tail.x][tail.y] = '.';
		sn[sid].pop_back();
	}
	if (sn[sid].size()) a[head.x][head.y] = '#';
	a[tx][ty] = '@';
	sn[sid].push_front(node(tx, ty));
}

// to debug
inline void disp() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) printf("%c", a[i][j]);
		printf("\n");
	}
	printf("\n");
}

// to assist the priority_queue below OvO
struct op {
	int sz, id;
	bool operator <(const op b) const {if (sz != b.sz) return sz < b.sz; else return id > b.id;}
};

int main() {
	scanf("%d%d%d", &n, &m, &k);
	char buf[256];
	fgets(buf, sizeof(buf), stdin);
	// establishing the boarder
	for (int i = 0; i <= n + 1; i++) 
		a[i][0] = a[i][m + 1] = '#';
	for (int j = 0; j <= m + 1; j++) 
		a[0][j] = a[n + 1][j] = '#';
		
	for (int i = 1; i <= n; i++) {
		fgets(buf, sizeof(buf), stdin);
		for (int j = 1; j <= m; j++) {
			a[i][j] = buf[j - 1];
		}
	}
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) 
		if (a[i][j] == '@') find(node(i, j));
	
/*
	printf("\n");
	for (int i = 1; i <= n; i++) {
手		int count = 0;
动		for (list<node>::iterator it = sn[i].begin(); it != sn[i].end(); it++) {
滑			a[it->x][it->y] = count++ + 'A';
姬		}
	}
*/
	
	memset(cmd, -1, sizeof(cmd));
	for (int i = 1; i <= cnt; i++) {
		fgets(buf, sizeof(buf), stdin);
		for (int j = 0; j < k; j++) {
			if (buf[j] == 'S') cmd[i][j + 1] = 0;
			if (buf[j] == 'D') cmd[i][j + 1] = 1;
			if (buf[j] == 'A') cmd[i][j + 1] = 2;
			if (buf[j] == 'W') cmd[i][j + 1] = 3;
		}
	}
	for (int i = 1; i <= k; i++) 
		for (int j = 1; j <= cnt; j++) 
			move(j, cmd[j][i]);
			
	int food = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) food += a[i][j] == '&';
	}
	
	//P.S. it is required to output the answers from longer snakes to shorter ones
	// I was stuck to 20 points because I have ignored this demand
	priority_queue<op> qq;
	for (int i = 1; i <= cnt; i++) qq.push((op){sn[i].size(), i});
	while (!qq.empty()) {
		printf("%d %d\n", qq.top().sz, qq.top().id);
		qq.pop();
	}
	printf("%d", food);
	return 0;
}

```

---

## 作者：Mr_Eight (赞：4)

这题感觉难度并不那么大，直接上代码。
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <queue>
using namespace std;
int n,m,k,c,ans;
char map[202][202],oper[202][202];
bool vis[202][202],die[202];//die[i]表示编号为i的蛇已经死了
queue< pair<int,int> >snake[202];//用队列模拟蛇，pair中两个int分别指x,y坐标
pair<int,int>answer[202];
string str;
void read() {
	cin>>n>>m>>k;
	getchar();
	for(int i=1; i<=n; i++) {
		cin>>str;
		for(int j=1; j<=m; j++) {
			map[i][j]=str[j-1];
		}
	}
	int temp=0;
	while(cin>>str) {
		temp++;
		for(int i=1; i<=k; i++) {
			oper[temp][i]=str[i-1];
		}
	}
}
void Snake(int x,int y,int c) {
	if(!vis[x][y]&&map[x][y]=='#') {
		vis[x][y]=1;
		Snake(x-1,y,c);
		Snake(x+1,y,c);
		Snake(x,y-1,c);
		Snake(x,y+1,c);
		snake[c].push(make_pair(x,y));
	}
}
void search_snake() {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(map[i][j]=='@') {
				c++;
				map[i][j]='#';
				Snake(i,j,c);
			}
		}
	}
}
bool cmp(pair<int,int>x,pair<int,int>y) {//排序规则
	if(x.first!=y.first)return x.first>y.first;
	else return x.second<y.second;
}
int main() {
	read();//读入地图
	search_snake();//找蛇
	for(int i=1; i<=k; i++) {
		for(int j=1; j<=c; j++) {
			if(die[j])continue;//这条蛇已经死了，无需处理。
			int x,y;//找出移动到的坐标
			if(oper[j][i]=='W')x=snake[j].back().first-1,y=snake[j].back().second;
			if(oper[j][i]=='S')x=snake[j].back().first+1,y=snake[j].back().second;
			if(oper[j][i]=='A')x=snake[j].back().first,y=snake[j].back().second-1;
			if(oper[j][i]=='D')x=snake[j].back().first,y=snake[j].back().second+1;
			if(map[x][y]=='.') {//是空地
				snake[j].push(make_pair(x,y));
				map[x][y]='#';
				map[snake[j].front().first][snake[j].front().second]='.';
				snake[j].pop();
			} else if(map[x][y]=='&') {//是食物
				snake[j].push(make_pair(x,y));
				map[x][y]='#';
			} else {//撞到边界或别的蛇，挂了。。。
				while(!snake[j].empty()) {
					map[snake[j].front().first][snake[j].front().second]='&';
					snake[j].pop();
				}
				die[j]=1;
			}
		}
	}
	for(int i=1; i<=c; i++) {
		answer[i].first=snake[i].size();
		answer[i].second=i;
	}
	sort(answer+1,answer+c+1,cmp);//排序，准备输出
	for(int i=1; i<=c; i++) {
		cout<<answer[i].first<<' '<<answer[i].second<<endl;
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(map[i][j]=='&')ans++;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：醉里挑灯看剑 (赞：4)

    模拟好题！
    大佬们都用的stl库，蒟蒻的我只会数组模拟。
    代码比较难看，不过应该是挺好理解的，如果用什么问题请及时联系
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e5+7;//用inf标记张碍物 
const int shiwu=1e7+2;//用shiwu标记食物 
struct snake{int x,y;}h[1001][21];
int dx[5]={0,0,0,1,-1},dy[5]={0,1,-1,0,0};
int n,m,t,q,tot,k,j,i,mp[201][201],head[21],tail[21],flag[21];//head记录头结点，tail记录为尾节点 
char a[201][201]; 
void zhaoshe(int x,int y){
	mp[x][y]=tot;//mp标记某一条蛇的位置，tot为蛇的编号 
	h[head[tot]][tot].x=x,h[head[tot]][tot].y=y;
	mp[x][y]=inf;
	for(int i=1;i<=4;i++)
	{
		int xx=dx[i]+x,yy=dy[i]+y;
		if(xx<=m&&yy<=n&&xx>=1&&yy>=1&&a[xx][yy]=='#')
		{
			head[tot]++;
		  zhaoshe(xx,yy);
		} 
	}
}
void work1()
{
	if(mp[h[head[j]][j].x][h[head[j]][j].y-1]==shiwu){
	h[++head[j]][j].x=h[head[j]-1][j].x;
	h[++head[j]][j].y=h[head[j]-1][j].y-1;
   mp[h[head[j]][j].x][h[head[j]][j].y]=inf;
	}
	else if(mp[h[head][j].x][h[head][j].y-1]==inf||h[head][j].x>m||h[head][j].x<1||h[head][j].y-1>n||h[tail][j].y-1<1){//这条蛇挂了 
	for(int i=tail[j];i<=head[j];i++)
  mp[h[i][j].x][h[i][j].y]=shiwu;
  flag[j]=1;//标记 
  }
  else{
  	h[++head[j]][j].x=h[head[j]-1][j].x-1;
	h[++head[j]][j].y=h[head[j]-1][j].y;
   mp[h[head[j]][j].x]][h[head[j]][j].y]=inf;
   tail[j]++;
   mp[h[tail[j]][j].x]][h[tail[j]][j].y]=0;//走过去后取消障碍 
  }
}
void work2()
{
	if(mp[h[head[j]][j].x-1][h[head[j]][j].y]==shiwu){
	h[++head[j]][j].x=h[head[j]-1][j].x-1;
	h[++head[j]][j].y=h[head[j]-1][j].y;
   mp[h[head[j]][j].x]][h[head[j]][j].y]=inf;
	}
	else if(mp[h[head][j].x-1][h[head][j].y]==inf||h[head][j].x-1>m||h[head][j].x-1<1||h[head][j].y>n||h[head][j].y<1){
	for(int i=tail[j];i<=head[j];i++)
  mp[h[i][j].x][h[i][j].y]=shiwu;
  flag[j]=1;
  }
  else{
  	h[++head[j]][j].x=h[head[j]-1][j].x-1;
	h[++head[j]][j].y=h[head[j]-1][j].y;
   mp[h[head[j]][j].x]][h[head[j]][j].y]=inf;
   tail[j]++;
   mp[h[tail[j]][j].x]][h[tail[j]][j].y]=0;//走过去后取消障碍 
  }
}
void work3()
{
	if(mp[h[head[j]][j].x][h[head[j]][j].y+1]==shiwu){
	h[++head[j]][j].x=h[head[j]-1][j].x;
	h[++head[j]][j].y=h[head[j]-1][j].y+1;
   mp[h[head[j]][j].x]][h[head[j]][j].y]=inf;
	}
	else if(mp[h[head][j].x][h[head][j].y+1]==inf||h[head][j].x>m||h[head][j].x<1||h[head][j].y+1>n||h[head][j].y+1<1){
	for(int i=tail[j];i<=head[j];i++)
  mp[h[i][j].x][h[i][j].y]=shiwu;
  flag[j]=1;
  }
  else{
  	h[++head[j]][j].x=h[head[j]-1][j].x;
	h[++head[j]][j].y=h[head[j]-1][j].y+1;
   mp[h[head[j]][j].x]][h[head[j]][j].y]=inf;
   tail[j]++;
   mp[h[tail[j]][j].x]][h[tail[j]][j].y]=0;//走过去后取消障碍 
  }
}
void work4()
{
	if(mp[h[head[j]][j].x+1][h[head[j]][j].y]==shiwu){
	h[++head[j]][j].x=h[head[j]-1][j].x+1;
	h[++head[j]][j].y=h[head[j]-1][j].y;
   mp[h[head[j]][j].x]][h[head[j]][j].y]=inf;
	}
	else if(mp[h[head][j].x+1][h[head][j].y]==inf||h[head][j].x+1>m||h[head][j].x+1<1||h[head][j].y>n||h[head][j].y<1){//这条蛇挂了 
	for(int i=tail[j];i<=head[j];i++)
  mp[h[i][j].x][h[i][j].y]=shiwu;
  flag[j]=1;
  }
  else{
  	h[++head[j]][j].x=h[head[j]-1][j].x-1;
	h[++head[j]][j].y=h[head[j]-1][j].y;
   mp[h[head[j]][j].x]][h[head[j]][j].y]=inf;
   tail[j]++;
   mp[h[tail[j]][j].x]][h[tail[j]][j].y]=0;//走过去后取消障碍 
  }
}

int main()
{
  cin>>n>>m>>k; 
  memset(head,1,sizeof(head));
  for(i=1;i<=n;i++)
  for(j=1;j<=m;j++)
  {
  cin>>a[i][j];
  if(a[i][j]=='.')mp[i][j]=0;
  else if(a[i][j]=='&')mp[i][j]=shiwu;
  else if(a[i][j]=='@')tot++,zhaoshe(i,j);
	}
	for(j=1;j<=tot;j++)
	{
		char ch[1001];
		cin>>ch;
		for(int i=0;i<k;i++)
		{
			if(flag[j])break;
			if(ch[i]=='W')work1();
			if(ch[i]=='A')work2();
			if(ch[i]=='S')work3();
			if(ch[i]=='D')work4();
		}
	}
	for(int i=1;i<=tot;i++){
	if(flag[i])continue ;
	else cout<<head[i]-tail[i]<<' '<<i<<endl;	
}
  int ans=0;
  for(int i=1;i<=n;i++)
  for(int j=1;j<=m;j++)
  if(mp[i][j]==shiwu)ans++;
  cout<<ans<<endl;
  return 0;
} 

```

---

## 作者：wwwwwza (赞：3)

这还是本蒟蒻第一次写紫题的题解。   
这道题一看就是大模拟~~直接跳过~~，先仔细审题，分析题目，就是让我们模拟几条贪吃蛇的移动路径。  
**思路：**  
1.输入。直接输入即可。  
2.储存。可以使用双端队列存储每一条蛇的每个身体碎片所在的坐标和数据输入的字符图存储整个图。  
3.操作。一共有三种操作，分别为删除、进食和移动。  
删除操作：将存储该蛇的双端队列中所有坐标对应的点在字符图中标记为食物，并删除该队列，标记该蛇已被删除。  
进食操作：将该蛇原来的头部改为身体，将对应食物的坐标改成该蛇头部，就是在该蛇对应的双端队列中从前面插入该食物的在坐标即可，在字符图上同步更新。  
移动操作：将该蛇的最后一位删除，补充到前面。对应着更新双端队列和字符图。
4.输入。按照题目的要求输出每条蛇的信息。再遍历一遍字符图，求出之中食物的数量，输出即可。  
~~此题较水，也就100+行而已。~~  
**代码：**  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int xx[4]={0,0,1,-1},yy[4]={1,-1,0,0};
int n,m,k,cnt=0,sum=0;
char ch[205][205],dir[25][105];
struct node{
	int x,y;
};
deque<node>q[25];
bool vis[205][205],over[25];
int rec(char c){
	if(c=='D')return 0;
	if(c=='A')return 1;
	if(c=='S')return 2;
	if(c=='W')return 3;
}
void del(int i){//删除 
	over[i]=1;
	while(!q[i].empty()){
		int nx=q[i].front().x,ny=q[i].front().y;
		ch[nx][ny]='&';
		q[i].pop_front();
	}
}
void eat(int i,int turn){//进食 
	int nx=q[i].front().x,ny=q[i].front().y;
	ch[nx][ny]='#';
	nx+=xx[turn];
	ny+=yy[turn];
	ch[nx][ny]='@';
	q[i].push_front({nx,ny});
}
void move(int i,int turn){//移动 
	int nx=q[i].front().x,ny=q[i].front().y;
	ch[nx][ny]='#';
	int mx=q[i].back().x,my=q[i].back().y;
	ch[mx][my]='.';
	q[i].pop_back();
	nx+=xx[turn];
	ny+=yy[turn];
	ch[nx][ny]='@';
	q[i].push_front({nx,ny});
}
struct poin{
	int len,pos;
}ans[25];
bool cmp(poin a,poin b){
	if(a.len==b.len)return a.pos<b.pos;
	return a.len>b.len;
}
signed main(){
	cin >>n>>m>>k;//输入 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin >>ch[i][j];
			if(ch[i][j]=='@'){
				cnt++;
				q[cnt].push_front({i,j});
			}
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=k;j++){
			cin >>dir[i][j];
		}
	}
	for(int i=1;i<=cnt;i++){//录入各蛇的基本信息 
		int nx=q[i].front().x,ny=q[i].front().y;
		bool flag=true;
		while(flag){
			flag=false;
			for(int j=0;j<4;j++){
				int mx=nx+xx[j],my=ny+yy[j];
				if(mx<=0||mx>n||my<=0||my>m||vis[mx][my]||ch[mx][my]!='#')continue;
				nx=mx;ny=my;
				vis[nx][ny]=1;
				q[i].push_back({nx,ny});
				flag=true;
			}
		}
	}
	for(int j=1;j<=k;j++){//按题目操作 
		for(int i=1;i<=cnt;i++){
			if(over[i])continue;
			int turn=rec(dir[i][j]);
			int nx=q[i].front().x+xx[turn],ny=q[i].front().y+yy[turn];
			if(nx<=0||nx>n||ny<=0||ny>m||ch[nx][ny]=='#'||ch[nx][ny]=='@'){
				del(i);
			}else if(ch[nx][ny]=='&'){
				eat(i,turn);
			}else if(ch[nx][ny]=='.'){
				move(i,turn);
			}
		}
	}
	for(int i=1;i<=cnt;i++){//输出 
		ans[i].len=q[i].size();
		ans[i].pos=i;
	}
	sort(ans+1,ans+1+cnt,cmp);
	for(int i=1;i<=cnt;i++){
		cout <<ans[i].len<<" "<<ans[i].pos<<endl;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='&')sum++;
		}
	}
	cout <<sum;
	return 0;
}
```

---

## 作者：Macesuted (赞：3)

[题面](https://www.luogu.com.cn/problem/P4944)

`Time:23 ms,Memory:756.00 KB,Code:3.07KB`

不加 O2，发此篇题解的时候是最优解 rk1。
# 题意
给出一个地图，地图上初始有 $c$ 条贪吃蛇和一些食物。

接下来会给出 $k$ 秒内每条贪吃蛇的移动规则，你需要输出 $k$ 秒后所有蛇的信息。
# 分析&代码
写一个 `Snake` 类，来存放所有有关蛇的操作。
```cpp
struct node {  //结点
    int x, y;
};

class Snake {
   private:
    std::deque<node> body;  //蛇

    void die(void) { //清除蛇身
        live = false; 
        len = 0;
        while (!body.empty()) {
            node cac = body.front();
            body.pop_front();
            map[cac.x][cac.y] = '&', restFood++;
        }
        return;
    }

   public:
    Snake(int x, int y, int id) {  //BFS 寻找蛇身
        this->id = id;
        len = 0;
        live = true;
        static std::queue<node> que;
        que.push((node){x, y});
        while (!que.empty()) {
            node cac = que.front();
            vis[cac.x][cac.y] = true;
            body.push_back(cac), len++;
            que.pop();
            for (int i = 0; i < 4; i++) {
                int tx = cac.x + way[0][i], ty = cac.y + way[1][i];
                if (tx >= 1 && tx <= n && ty >= 1 && ty <= m &&
                    !vis[tx][ty] && map[tx][ty] == '#') que.push((node){tx, ty});
            }
        }
        return;
    }
    ~Snake(void) {
        body.clear();
        return;
    }

    bool live;
    int id, len;

    void move(char way) {
        node to = body.front();
        map[to.x][to.y] = '#';   //删除蛇头
        if (way == 'W') to.x--;  //四个方向
        if (way == 'S') to.x++;
        if (way == 'A') to.y--;
        if (way == 'D') to.y++;
        if (to.x < 1 || to.x > n || to.y < 1 || to.y > m ||
            map[to.x][to.y] == '#' || map[to.x][to.y] == '@') return die();  //如果撞到蛇身或者边界
        body.push_front(to), len++;
        if (map[to.x][to.y] == '&') return restFood--, void(map[to.x][to.y] = '@');  //吃食物
        map[to.x][to.y] = '@';
        map[body.back().x][body.back().y] = '.';  //删除尾部，增加新的头部
        return len--, body.pop_back();
    }

    inline bool operator<(const Snake& oth) const {
        return this->len > oth.len || this->len == oth.len && this->id < oth.id;
    }
};
```
其中构造函数负责 BFS 初始化蛇身，`move(char)` 函数负责让蛇向指定方向移动。此时如果蛇死了会直接调用 `die(void)` 清除蛇身。

这里有一点巧的就是在蛇吃掉食物后，只要让食物变成新蛇头就可以了。

如果蛇没有吃掉食物，删除蛇尾并且在前方标记新头即可。

---
上面的类定义完之后，面向对象模拟题意即可。
```cpp
int main() {
    std::ios::sync_with_stdio(false);
    int k, c;
    std::cin >> n >> m >> k;
    restFood = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            std::cin >> map[i][j];
            if (map[i][j] == '&') restFood++;
        }
    c = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (map[i][j] == '@') snakes.push_back((Snake){i, j, ++c});  //通过蛇头直接初始化蛇身
    for (int i = 0; i < c; i++)
        for (int j = 1; j <= k; j++)
            std::cin >> cmd[i][j];
    for (int tim = 1; tim <= k; tim++)
        for (int p = 0; p < c; p++) {
            if (!snakes[p].live) continue;
            snakes[p].move(cmd[p][tim]);  //让蛇向指定方向移动一格
        }
    std::sort(snakes.begin(), snakes.end());
    for (std::vector<Snake>::iterator i = snakes.begin(); i != snakes.end(); i++)
        std::cout << i->len << ' ' << i->id << std::endl;
    std::cout << restFood << std::endl;
    return 0;
}
```
[完整代码](https://macesuted.blog.luogu.org/Code-P4944)

---

## 作者：Wy_x (赞：2)

题目传送门：[P4944 PION贪吃蛇](https://www.luogu.com.cn/problem/P4944)


------------

## 题目描述：

有一个 $n \times m$ 的字符矩阵，其中，用 `.` 表示空地，用 `#` 表示蛇身，用 `@` 表示蛇头，用 `&` 表示食物。

对于每条蛇，有 $k$ 个操作，操作时需要遵守 $8$ 条基本规则。

操作完后，按顺序（题目的输出格式中有描述）输出蛇的长度和编号。

最后，输出食物总个数。

## 蛇身的存储：

- **输入地图时**：
>1. 对于任意蛇头，最多只有一块蛇身于其相连（可以只有一个蛇头），且蛇身最多为二连块。
>2. 输入数据保证图中的蛇均可以判断身体与头的对应关系，不会造成蛇身形态多解。

- **操作中**：
> 1. 可能会出现一个蛇头与多个蛇身相连，或蛇身出现环的情况。此时，在地图上模拟已无法满足要求，可以用队列存储蛇身。
> 2. 操作时可能会**在队列前加点**（蛇头走到了一个有食物的格子里，原来的蛇头变成蛇身，这个食物变成了蛇头），此时，用双端队列存储较好。

综上所述，可以判断蛇身用**双端队列**存储。

## 解决方案：

1. 先读入地图，判断地图中有几条蛇，再读入每条蛇的移动操作。

2. 第 $i$ 条蛇的的身体用**双端队列** `q[i]` 存储。其中，`q[i].front()` 表示蛇头的位置，`q[i].back()` 表示蛇尾的位置。

- 蛇的编号按题目要求计算（题目的输入格式中有描述）。

3. 按照题意模拟蛇的移动，此代码使用的是双端队列与地图模拟相结合的方式，即：

> - 双端队列存储蛇坐标，每次用队头（存的是蛇头的坐标）进行移动模拟。
> - 地图模拟用来判断移动后蛇头是否会撞到另一条蛇，即蛇移动后是否会死亡；

4. 按题意输出。

## 注意：

1. 检查 `freopen` 是否注释。

2. 检查移动函数中有没有重复判断情况，即一个 `if` 成立后另一个 `if` 也成立，这里推荐用 `if-else` 语句或 `switch`语句判断，防止重复。

## 代码：

- 一行代码的注释要么在这一行代码的后面，要么在下一行。若多行注释，则使用下面的格式：

```txt
/*
	...
    ...
*/
```

- **建议最大化窗口观看**。

[无注释代码](https://www.luogu.com.cn/paste/zcqx4md2)

```cpp
#include<iostream>//cin+cout
#include<cstring> 
#include<cstdio> //freopen
#include<deque>  //双端队列的头文件 
#include<algorithm> //sort 
#define int long long 
using namespace std; 

int fx[1001],fy[1001];//向上下左右移动函数 
bool vis[1005][1005]; //记录一条蛇的身体是否被搜过（仅在 input() 函数中使用） 
char map[1005][1005]; //存储地图 
int c[1005][1005];    //存储 int 类型的操作 

struct P { int l,id; } ans[1<<17]; //记录移动操作后每条蛇的长度及编号 
bool cmp(P a,P b) { return a.l>b.l||(a.l==b.l&&a.id<b.id); }
//按题意，写出 sort 中的排序函数 cmp
//输出按长度由大到小排序（长度相同按编号由小到大排序） 

deque<pair<int,int> >a[25];
/*
	c<=20，双端队列开 20 个足够。 
	
	a[i] 存储一条蛇的坐标， 
	其中，
	a[i].front() 表示蛇头 
	a[i].back() 表示蛇尾 
	
	对于每一个 pair(x,y)
	first 表示横坐标 x
	second 表示纵坐标 y 
*/

int n,m,k,food,cnt;
/*
	地图 n 行 m 列 
	有 k 次操作
	地图中共有 food 个食物
	地图中共有 cnt 条蛇 
*/

//void output_map(); //输出地图（调试用） 

void input()
{
	fx[1]=0;fy[1]=-1;//向左 
	fx[2]=0;fy[2]=1; //向右 
	fx[3]=-1;fy[3]=0;//向上
	fx[4]=1;fy[4]=0; //向下 
	
	//为在输入地图后搜索蛇身，
	//初始化搜索函数 fx[1]~fx[4],fy[1]~fy[4] 
	
	fx['A']=0;fy['A']=-1;//向左 
	fx['D']=0;fy['D']=1; //向右 
	fx['W']=-1;fy['W']=0;//向上 
	fx['S']=1;fy['S']=0; //向下 
	
	//对于操作 'A','D','W','S',
	//初始化移动函数
	
	//两个初始化不会引起冲突：(int)'A'>4 
	
	cin>>n>>m>>k;
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		cin>>map[i][j];
		food+=map[i][j]=='&'; //计算输入图中的食物数量 
		if(map[i][j]=='@') //如果发现一条蛇的蛇头 
		{
			cnt++; //蛇数量加一 
			a[cnt].push_back(make_pair(i,j)); //双端队列里加入蛇头坐标 (i,j)
			vis[i][j]=1;
		}
	}
	
//	output_map(); //输出地图（调试用） 
	
//	printf("\n------------------\n");
	
	char cc; //存储 char 类型的操作 
	for(int i=1;i<=cnt;i++)
	for(int j=1;j<=k;j++)
	cin>>cc,c[i][j]=cc; //cc 作为中介，把 char 类型的移动操作转换成 int 类型的移动操作  
	
	for(int i=1;i<=cnt;i++) //枚举每条蛇，存储每条蛇蛇身坐标
	{
		while(true) //广搜，用来搜索蛇身（深搜也可） 
		{	
			bool f=1; //标记此次扩展中队尾有没有加入新的节点
			int x=a[i].back().first,y=a[i].back().second;
			//a[i].back() 为当前蛇尾的坐标 (x,y)
			
			for(int k=1;k<=4;k++) //从当前节点向上下左右四个方向扩展 
			{
				int xx=x+fx[k],yy=y+fy[k]; //扩展节点的坐标 
				if(vis[xx][yy]) continue; //搜索过这个点，继续循环 
				if(map[xx][yy]=='#') //如果这个点是蛇身 
				a[i].push_back(make_pair(xx,yy)),f=0,vis[xx][yy]=1;
				/*
					向队尾中加入当前新的蛇尾坐标 (xx,yy) 
					f=0，记录队尾加入了新节点
					vis[xx][yy]=1，标记点 (xx,yy) 已被搜索过 
				*/
			}
			
			if(f) break;
			/*
				若 f=1，则此次扩展中队尾没有加入新的节点， 
				则这条蛇的身体已经被搜完了，就结束循环，去记录下一条蛇的坐标 
			*/ 
		}
	}
}

void clear(int nw) //从队列和地图中清除编号为 nw 的蛇 
{
	while(a[nw].size()) //遍历这条蛇的节点 
	{
		int x=a[nw].front().first,y=a[nw].front().second;
		//从队首开始清除这条蛇，当前清除到的节点坐标为 (x,y)
		a[nw].pop_front(); //弹出队首坐标 
		map[x][y]='&'; //地图中这个节点变为食物 
		food++; //总食物 food 加一 
	}
}

void move(int nw,int t) //第 nw 条蛇的第 t 个操作 
{
	if(a[nw].empty()) return;
	//如果这条蛇的长度为 0，即这条蛇死亡，此次操作忽略 
	
	int x1=a[nw].front().first,x2=a[nw].back().first;
	int x=x1+fx[c[nw][t]];
	int y1=a[nw].front().second,y2=a[nw].back().second;
	int y=y1+fy[c[nw][t]];
	/*
		坐标 (x1,y1)：移动前蛇头坐标 
		坐标 (x2,y2)：移动前蛇尾坐标 
		坐标 (x,y)：移动后蛇头坐标 
	*/ 
	
	//移动后的情况判断： 
	if(x<1||y<1||x>n||y>m) clear(nw);//蛇头超出边界，这条蛇死亡（详见题目基本规则中的第 5 条） 
	else if(map[x][y]=='#'||map[x][y]=='@') clear(nw);//蛇头撞上一头蛇，这条蛇死亡（详见题目基本规则中的第 4、6、7 条） 
	else if(map[x][y]=='&') a[nw].push_front(make_pair(x,y)),food--,map[x1][y1]='#',map[x][y]='@';
	/*
		移动后蛇吃到了一个食物：
			移动后食物变成了蛇头，移动前的蛇头变成了蛇身
			即在队首加入此食物的坐标，队尾不变，同时食物总数量 food 减一
		
		修改地图：
			坐标 (x1,y1)：为蛇身
			坐标 (x2,y2)：为蛇身
			坐标 (x,y)：为蛇头
		（详见题目基本规则中的第 2 条）
	*/ 
	else if(map[x][y]=='.') a[nw].push_front(make_pair(x,y)),a[nw].pop_back(),map[x1][y1]='#',map[x][y]='@',map[x2][y2]='.';
	/*
		普通移动操作：
			在队首加入坐标 (x,y)，弹出队尾
			
		修改地图：
			坐标 (x1,y1)：为蛇身
			坐标 (x2,y2)：为空地
			坐标 (x,y)：为蛇头
		（详见题目基本规则中的第 1 条）
	*/
}

/*

void output_map()  //输出地图（调试用） 
{
	for(int i=1;i<=n;i++ , puts(""))
	for(int j=1;j<=m;j++) putchar(map[i][j]);
	puts("--------------------\n\n");
}

*/

signed main()
{
//	freopen("a.in","r",stdin);
	
	input(); //输入，存储每一条蛇的坐标 
	
	for(int i=1;i<=k;i++) //k 次操作
	{
		for(int j=1;j<=cnt;j++) //cnt 条蛇 
		move(j,i); //第 j 条蛇的第 i 个操作 
		
//		output_map(); //输出地图（调试用） 
	}
	
	for(int i=1;i<=cnt;i++) //共有 cnt 条蛇 
	ans[i].l=a[i].size(),ans[i].id=i; //存储操作后每一套蛇的长度及编号 
	
	sort(ans+1,ans+1+cnt,cmp); //排序 
	
	for(int i=1;i<=cnt;i++) //共有 cnt 条蛇 
	cout<<ans[i].l<<" "<<ans[i].id<<endl; //输出排序后的蛇的长度和编号 
	
	cout<<food; //输出操作后的食物总个数 
	
	return 0;
}
```


---

## 作者：ZXZ_ (赞：2)

这是一道比较简单的模拟题（就打了五个小时）

思路：

1. 用链储存蛇。

2. 蛇撞上"#" or "@" or 越界就 die 掉。

3. 如果蛇死了，蛇头和蛇身更新为食物。

4. 如果吃了东西，把食物位置更新为蛇头，原来的蛇头更新为蛇身（链表插入操作）

注意：

1. 题目保证：“图中的蛇不会引起混淆（对于任意蛇头，最多只有一块蛇身于其相连，而蛇身最多为二连块”。

2. 蛇的移动可以理解为回合制编号小的先走（所以蛇头相撞是后走的蛇为主动

详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=201,dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};
char mp[N][N];
int n,m,k,cnt,ans[N*N],head[N*N],tot,ans1=1;
char zl[N*N][N];
bool bz=true,bz1[N][N],bz2[N];
struct node{
    int x,y,nxt;
    //x,y 是蛇身/头的坐标
    //nxt 指向同一条蛇内的下一节，蛇尾指向空即nxt=0
}se[N*N];
struct hzq{
    int num,s;
}pr_ans[N*N];   
bool cmp(hzq x,hzq y){
    if(x.s==y.s)
        return x.num<y.num;
    else return x.s>y.s;
}
void fd(int x,int y,int last_cnt){//找蛇
    if(bz==false)return;
    for(int i=1;i<=4;i++){
        int xx=x+dx[i],yy=y+dy[i];
        if(mp[xx][yy]=='#'&&bz1[xx][yy]!=true){
            bz1[xx][yy]=true;
            ans[tot]++;
            se[++cnt].x=xx;
            se[cnt].y=yy;
            se[last_cnt].nxt=cnt;//指向下一节
            fd(xx,yy,cnt);
        }
    }
    bz=false;
}
void run(int t,int x,int y,int cnt1){//行走函数
    if(se[cnt1].nxt==0){
        mp[x][y]='.';
        return;
    }
    mp[x][y]=mp[se[se[cnt1].nxt].x][se[se[cnt1].nxt].y];
    run(1,se[se[cnt1].nxt].x,se[se[cnt1].nxt].y,se[cnt1].nxt);//遍历整条蛇
     se[se[cnt1].nxt].x=x;
    se[se[cnt1].nxt].y=y;
}
void die(int x,int y,int cnt1){//死亡函数
    mp[x][y]='&';
    if(se[cnt1].nxt==0)return;
    else die(se[se[cnt1].nxt].x,se[se[cnt1].nxt].y,se[cnt1].nxt);
}
void len(int cnt1){
    if(se[cnt1].nxt!=0){
        ans1++;
        len(se[cnt1].nxt);
    }
    else return;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>mp[i][j];//读入地图
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='@'){//找到蛇头就去找蛇身
                ++cnt;
                se[cnt].x=i;
                se[cnt].y=j;
                head[++tot]=cnt;
                fd(i,j,cnt);
                bz=true;
            }
    for(int j=1;j<=tot;j++)//枚举蛇的数量
        for(int i=1;i<=k;i++)cin>>zl[j][i];//读入指令
    for(int i=1;i<=k;i++)
        for(int j=1;j<=tot;j++)
            if(zl[j][i]=='W'&&bz2[j]==false){
                if(se[head[j]].x-1<1||mp[se[head[j]].x-1][se[head[j]].y]=='#'||mp[se[head[j]].x-1][se[head[j]].y]=='@')bz2[j]=true,die(se[head[j]].x,se[head[j]].y,head[j]);
                else{
                    se[head[j]].x-=1;
                    if(mp[se[head[j]].x][se[head[j]].y]=='&'){
                        mp[se[head[j]].x+1][se[head[j]].y]='#';
                        mp[se[head[j]].x][se[head[j]].y]='@';
                        se[++cnt].x=se[head[j]].x+1;
                        se[cnt].y=se[head[j]].y;
                        se[cnt].nxt=se[head[j]].nxt;
                        se[head[j]].nxt=cnt;
                        ans[j]++;
                    }
                    else{
                        mp[se[head[j]].x][se[head[j]].y]='@';
                        run(1,se[head[j]].x+1,se[head[j]].y,head[j]);
                    }
                    
                }
            }
            else if(zl[j][i]=='S'&&bz2[j]==false){
                if(se[head[j]].x+1>n||mp[se[head[j]].x+1][se[head[j]].y]=='#'||mp[se[head[j]].x+1][se[head[j]].y]=='@')bz2[j]=true,die(se[head[j]].x,se[head[j]].y,head[j]);
                else{
                    se[head[j]].x+=1;
                    if(mp[se[head[j]].x][se[head[j]].y]=='&'){
                        mp[se[head[j]].x-1][se[head[j]].y]='#';
                        mp[se[head[j]].x][se[head[j]].y]='@';
                        se[++cnt].x=se[head[j]].x-1;
                        se[cnt].y=se[head[j]].y;
                        se[cnt].nxt=se[head[j]].nxt;
                        se[head[j]].nxt=cnt;
                    }
                    else{
                        mp[se[head[j]].x][se[head[j]].y]='@';
                        run(1,se[head[j]].x-1,se[head[j]].y,head[j]);
                    }
                    
                }
            }
            else if(zl[j][i]=='D'&&bz2[j]==false){
                if(se[head[j]].y+1>m||mp[se[head[j]].x][se[head[j]].y+1]=='#'||mp[se[head[j]].x][se[head[j]].y+1]=='@')bz2[j]=true,die(se[head[j]].x,se[head[j]].y,head[j]);
                else{
                    se[head[j]].y+=1;
                    if(mp[se[head[j]].x][se[head[j]].y]=='&'){
                        mp[se[head[j]].x][se[head[j]].y-1]='#';
                        mp[se[head[j]].x][se[head[j]].y]='@';
                        se[++cnt].y=se[head[j]].y-1;
                        se[cnt].x=se[head[j]].x;
                        se[cnt].nxt=se[head[j]].nxt;
                        se[head[j]].nxt=cnt;
                    }
                    else{
                        mp[se[head[j]].x][se[head[j]].y]='@';
                        run(1,se[head[j]].x,se[head[j]].y-1,head[j]);
                    }
                }
            }
            else if(zl[j][i]=='A'&&bz2[j]==false){
                if(se[head[j]].y-1<1||mp[se[head[j]].x][se[head[j]].y-1]=='#'||mp[se[head[j]].x][se[head[j]].y-1]=='@')bz2[j]=true,die(se[head[j]].x,se[head[j]].y,head[j]);
                else{
                    se[head[j]].y-=1;
                    if(mp[se[head[j]].x][se[head[j]].y]=='&'){
                        mp[se[head[j]].x][se[head[j]].y+1]='#';
                        mp[se[head[j]].x][se[head[j]].y]='@';
                        se[++cnt].y=se[head[j]].y+1;
                        se[cnt].x=se[head[j]].x;
                        se[cnt].nxt=se[head[j]].nxt;
                        se[head[j]].nxt=cnt;
                    }
                    else{
                        mp[se[head[j]].x][se[head[j]].y]='@';
                        run(1,se[head[j]].x,se[head[j]].y+1,head[j]);
                    }
                }
            }
    for(int i=1;i<=tot;i++){
        pr_ans[i].num=i;
        if(!bz2[i]){
            len(head[i]);//计算蛇身长度
            pr_ans[i].s=ans1;
            ans1=1;
        }
    }
    sort(pr_ans+1,pr_ans+tot+1,cmp);
    for(int i=1;i<=tot;i++)cout<<pr_ans[i].s<<" "<<pr_ans[i].num<<endl;
    int ans2=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='&')ans2++;//输出
    cout<<ans2;
}
```

---

## 作者：FallingFYC_ (赞：2)

# [原题](https://www.luogu.com.cn/problem/P4944)
又是蒟蒻最爱的大模拟！但感觉这评级太高了吧（因为是 NOIP 题？）。

---
### 分析
别看他题目复杂，题解代码一百多行，其实很简单的！

1. 关于蛇的身体

	有两个问题：
   1. 用什么数据结构存储。
   	  
      根据题中的所有要求，双端队列是最好的选择！
      
      对于一条蛇，我们可用一个结构体存储所有的信息，有：
      	1. 蛇头坐标
		2. 编号
     	3. 长度
     	4. 所有蛇身坐标
   2. 怎么得到蛇身。
   
   		用 `dfs` 搜连通块即可。

2. 关于食物
	
    用一个变量存储还剩多少食物，在输入时顺便统计输入的盘面上有多少食物，在游戏过程中进行加减。

3. 关于移动

	1. 普通移动（无事发生）
    
    	步骤：
        1. 将移动前的蛇头替换成蛇身。
        2. 将蛇尾替换成空白区域。
        3. 将当前蛇头显示出来（将空地替换成蛇头）。
        4. 在存储蛇身的双端队列中添加蛇头并删除蛇尾。
        5. 将蛇头坐标更新。
   2. 吃食物
   
   		步骤：
        1. 将食物总数减 $1$。
        1. 将蛇的长度加 $1$。
        2. 将移动前的蛇头替换成蛇身。
        3. 将当前蛇头显示出来（将食物替换成蛇头）。
        4. 在存储蛇身的双端队列中添加蛇头。
        5. 将蛇头坐标更新。
   3. 死亡：
   		
      我用了一个数组记录每只蛇是否存活。
      
    	情况：
        1. 主动撞上蛇头或蛇身（包括自己的）。
        2. 撞上边界。
        
   以上是移动后所有的可能性，我用了一组坐标来存储移动后的坐标，再查看这组坐标所对应的格子进行相应的操作。
   
4. 关于死亡

    步骤：
    	
   1. 清空存储蛇身的双端队列，并将所有蛇身的坐标所对应的格子替换成食物。
   2. 将食物总数加上蛇的长度。
   3. 将蛇的长度归零。
   4. 更新蛇是否存活的数组。
   
5. 关于移动操作
	   
   我们要按蛇的输入顺序操作，而输入操作时是将每只蛇的所有移动操作先输入的。所以我用了一个二维数组记录所有操作（将一条蛇的操作记录到一列上），并在操作时一行一行的执行里面的操作。

6. 输出
	用结构体排序得到输出顺序，在根据题目要求输出就可以辣！

PS：这题我抢到了最优解（在近 400 条记录里）！！！

[最优解记录](https://www.luogu.com.cn/record/109753772)

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int nx[] = {0 , 1 , 0 , -1};
const int ny[] = {1 , 0 , -1 , 0};
//存储坐标，这个之前没提到
struct Node
{
	int x , y;
};
//存储蛇的结构体
struct Snake
{
	Node h;
	int id , len;
	deque<Node> s;
}snake[21];
int n , m , k , c , f , book[201][201] , alive[21];
char mp[201][201] , opr[101][21]/*存储操作，如上所述*/;

//得到蛇的身体的所有坐标
void getSnake(Node now)
{
	snake[c].s.push_back(now); snake[c].len++;
	book[now.x][now.y] = 1;
	for (int i = 0 ; i < 4 ; i++)
	{
		int tx = now.x + nx[i] , ty = now.y + ny[i];
		if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && !book[tx][ty] && mp[tx][ty] == '#')
			getSnake((Node){tx , ty});
	}
	return;
}

//蛇死后的操作
void died(int num)
{	
	Node ns = snake[num].s.front(); snake[num].s.pop_front();
	while (!snake[num].s.empty())
	{
		mp[ns.x][ns.y] = '&';
		ns = snake[num].s.front();
		snake[num].s.pop_front();
	}
	f += snake[num].len; snake[num].len = 0;
	alive[num] = 1;
	return;
}

//进行移动
void operate(int num , char o)
{
	Node now = {snake[num].h.x , snake[num].h.y};
	if (o == 'W') now.x--;
	else if (o == 'S') now.x++;
	else if (o == 'A') now.y--;
	else now.y++;
	
	if (now.x < 1 || now.x > n || now.y < 1 || now.y > m) died(num);
	else if (mp[now.x][now.y] == '#' || mp[now.x][now.y] == '@') died(num);
	else if (mp[now.x][now.y] == '&')
	{
		snake[num].len++; f--;
		mp[snake[num].h.x][snake[num].h.y] = '#';
		snake[num].s.push_front(now); snake[num].h = now;
		mp[now.x][now.y] = '@';
	}
	else 
	{
		mp[snake[num].h.x][snake[num].h.y] = '#';
		mp[snake[num].s.back().x][snake[num].s.back().y] = '.';
		snake[num].s.push_front(now); snake[num].s.pop_back();
		snake[num].h = now;
		mp[now.x][now.y] = '@';
	}
	return;
}

bool cmp(Snake a , Snake b)
{
	if (a.len == b.len) return a.id < b.id;
	else return a.len > b.len;
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++)
			cin >> mp[i][j];
			
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++)
		{
			if (mp[i][j] == '@')//按输入顺序存储每一条蛇
			{
				c++;
				snake[c].h = (Node){i , j}; snake[c].id = c;
				getSnake(snake[c].h);
			}
			else if (mp[i][j] == '&') f++;
		}
	
   //注意操作的输入格式！
	for (int i = 1 ; i <= c ; i++)
		for (int j = 1 ; j <= k ; j++)
			cin >> opr[j][i];
	
	for (int i = 1 ; i <= k ; i++)
		for (int j = 1 ; j <= c ; j++)
			if (!alive[j])
				operate(j , opr[i][j]);
	
   //输出！
	sort(snake + 1 , snake + c + 1 , cmp);
	for (int i = 1 ; i <= c ; i++)
		cout << snake[i].len << " " << snake[i].id << endl;
	cout << f;
	return 0;
}
```
[不太悲惨的记录](https://www.luogu.com.cn/record/list?pid=P4944&user=923403&page=1)（80分是因为我把 `=` 写成了 `==` qwq）

---

## 作者：TheSky233 (赞：2)

## Description

[题目传送门](https://www.luogu.com.cn/problem/P4944)。

给定一个贪吃蛇游戏的原始盘面和每条蛇的操作，求最后的结果。

## Solution

### Part 1：判断蛇头和蛇身的对应关系

数据范围中说：

> 且图中的蛇不会引起混淆（对于任意蛇头，最多只有一块蛇身于其相连，而蛇身最多为二连块），且数据保证图中的蛇均可以判断身体与头的对应关系，不会造成蛇身形态多解。

于是对于每一块蛇头，`bfs` 求解即可。

### Part 2：蛇身的存储

因为蛇身要经常伸长和改变，且每次改变均是从头和尾改变，所以我们这里可以选用 `deque`。

### Part 3：模拟游戏过程

注意以下几点：

1. 按照编号从小到大进行操作。

2. 蛇头出边界会死亡，但蛇头在边界不会。

3. 两只蛇头撞上时，主动撞的那一方死亡。

根据以上几点，我们可以列出一份移动原则：

- 当移动到空地（`.`）上时，新的队头位置进队，队尾出队。

- 当移动到食物（`&`）上时，新的队头位置进队，并把当前食物（`&`） 改为空地（`.`）。

- 当移动到蛇身（`#`）上或非法移动时，全部出队，把所有位置换成食物。

### Part 4：输出

注意题面中说的输出按**长度由大到小**排序（长度相同按**编号由小到大排序**）。

## Code

因为上文说的很清楚，且代码变量名也比较明确，因此代码不做注释。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node{
	int x,y,id;
};

struct Node{
	int id,len;
};

namespace GreedySnake{
	#define F(i,a,b) for(int i=(a); i<=(b); ++i)
	#define fi first
	#define se second
	#define mkp make_pair
	#define pb emplace_back
	#define N 205

	int n,m,k,SnakeCount;
	char ch[N][N],Map[N][N];
	const int dx[]={-1,1,0,0};
	const int dy[]={0,0,-1,1};
	int dead[25],len[25];
	
	Node out[25];
	map<char,int> ch_to_int={{'W',0},{'S',1},{'A',2},{'D',3}};
	vector<char> Op[25];
	deque<node> dq[25]; 
	
	void ReadIn(){
		cin>>n>>m>>k;
		F(i,1,n) F(j,1,m){
			cin>>ch[i][j];
			if(ch[i][j]=='@') ++SnakeCount;
		}
		F(i,1,SnakeCount) F(j,1,k){
			char c;
			cin>>c;
			Op[i].pb(c);
		}  
	}
	
	void Bfs(){
		bool vis[N][N];
    	int tot=0;
    	F(i,1,n) F(j,1,m){
    		if(ch[i][j]=='@'){
    			++tot;
    			queue<node> q;
    			q.push((node){i,j,0});
    			vis[i][j]=1;
    			Map[i][j]=tot;
    			dq[tot].push_back((node){i,j,tot});
    			while(!q.empty()){
    				node f=q.front(); q.pop();
					F(i,0,3){
						int xx=f.x+dx[i],yy=f.y+dy[i];
						if(ch[xx][yy]=='#' && !vis[xx][yy]){
							Map[xx][yy]=tot;
							q.push((node){xx,yy,0});
							dq[tot].push_front((node){xx,yy,tot});
							vis[xx][yy]=1;
						}
					} 
				}
			}
		}
		
		F(i,1,SnakeCount){
			dead[i]=0, len[i]=dq[i].size();
		}
	}
	
	void Initalize(){
		F(i,1,n) F(j,1,m){
			if(ch[i][j]!='&') ch[i][j]='.';
		}
	}
	
	void Play(){
		F(t,0,k-1){
			F(i,1,SnakeCount){
	    		if(dead[i]) continue;
	    		int xx=dq[i].back().x+dx[ch_to_int[Op[i][t]]],yy=dq[i].back().y+dy[ch_to_int[Op[i][t]]];
				if(xx<1 || xx>n || yy<1 || yy>m || Map[xx][yy]){
					while(!dq[i].empty()){
						ch[dq[i].front().x][dq[i].front().y]='&';
						Map[dq[i].front().x][dq[i].front().y]=0;
						dq[i].pop_front();
					}
					dead[i]=1;
				}
				else if(ch[xx][yy]=='&'){
					ch[xx][yy]='.';
					dq[i].push_back((node){xx,yy,i});
					Map[xx][yy]=i;
					len[i]++;
				}
				else {
					Map[dq[i].front().x][dq[i].front().y]=0;
					Map[xx][yy]=i;
					dq[i].pop_front();
					dq[i].push_back((node){xx,yy,i});
				}
			}
		}
	}
	
	void GameOver(){
		F(i,1,SnakeCount) out[i]=(Node){i,(dead[i]?0:len[i])};
		sort(out+1,out+SnakeCount+1,[](Node a,Node b){
			if(a.len==b.len) return a.id<b.id;
			return a.len>b.len;
		});
		F(i,1,SnakeCount) printf("%d %d\n",out[i].len,out[i].id);
		int sum=0;
		F(i,1,n) F(j,1,m) if(ch[i][j]=='&') sum++;
		printf("%d",sum);
	}
}

int main(){
	GreedySnake::ReadIn();
	GreedySnake::Bfs();
	GreedySnake::Initalize();
	GreedySnake::Play();
	GreedySnake::GameOver();
	return 0;
}
```

---

## 作者：Terraria (赞：2)

一道~~恶心的~~大模拟，害得我调了一个中午加一个晚上。

做这道题，需要如下几步：

- 输入~~废话~~。

- 储存蛇的信息。

- 根据蛇移动到的不同的地方来更改蛇的信息。

- 输出~~又是废话~~。

### 第一部分：输入

这部分没有什么好说的，直接上代码：

```cpp
void work(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];//储存地图
		}
	}
	get_snake();//开局前蛇的信息储存
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=k;j++) cin>>s[i][j];
	}
	play();//开始游戏
	write();//输出对应信息
}
```

### 第二部分：储存蛇的信息

注意到题解区里大部分用的是 $bfs$ 来寻找蛇，我这里用的是 $dfs$。

那么有个问题来了：怎么储存蛇身所在的格子？

一开始我用的是数组，结果自然是调爆了。考虑到蛇身有以下几种可能：

- 将吃到的食物更改为蛇头。

- 如果是正常移动，则将蛇尾删去。

因此，又要处理头又要处理尾，当然是用：

**双端队列**啦！

因此在储存蛇身时我用的是双端队列（即```deque```）。

```cpp

struct w{
	int x;
	int y;
};
struct snake{
	bool die=false;
	int id;
	int len;
	deque<w> body;
}a[209];
void dfs(int id,int x,int y,int l){//id表示第几条蛇，l表示目前蛇的长度
	a[id].len=max(a[id].len,l);//更新一下蛇的长度
	w aa;
	aa.x=x,aa.y=y;
	a[id].body.push_back(aa);//将当前的格子作为蛇身，从蛇头到蛇尾一次存储
	for(int i=1;i<=4;i++){
		int xx=dx[i]+x;
		int yy=dy[i]+y;
		if(xx<1||xx>n||yy<1||yy>m||vis[xx][yy]||mp[xx][yy]=='.'||mp[xx][yy]=='&') continue;
		if(mp[xx][yy]=='#'){
			vis[xx][yy]=true;
			dfs(id,xx,yy,l+1);
		}
	}
}
void clear(){
	for(int i=0;i<=200;i++){
		for(int j=0;j<=200;j++) vis[i][j]=false;
	}
}
void get_snake(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='@'){//如果是蛇头
				cnt++;//蛇数+1
				a[cnt].id=cnt;
				a[cnt].len=1;//一定要先赋予初始长度为1！
				clear();//因为我用的是dfs，因此可能会搜到重复的格子；在搜完一条蛇后要更新vis数组
				vis[i][j]=true;//蛇头已经搜过了
				dfs(cnt,i,j,1);
			}
		}
	}
}
```

### 第三部分：根据蛇移动到的不同的地方来更改蛇的信息

蛇一共只有可能移到如下几个位置：

- 空地。此时需要从队尾弹出蛇尾，从队头拉入新的蛇头。

- 食物。此时只需要将有食物的地方更新为新的蛇头**并将蛇的长度加一**。

- 走出格子、走到```#```（蛇身）或者```@```（蛇头），蛇死亡。

因此，依照这些要点模拟即可。

```cpp
void deal(int id){//处理蛇死亡后，所有蛇身和蛇头变为食物
	while(!a[id].body.empty()){
		mp[a[id].body.front().x][a[id].body.front().y]='&';
		a[id].body.pop_front();
	}
}

void play(){
	for(int i=1;i<=k;i++){//注意是先循环k再是cnt条蛇！
		for(int j=1;j<=cnt;j++){//表示第j条蛇的第i次操作
			if(a[j].die==true) continue;//如果已经死了就跳过
			int tox=a[j].body.front().x;
			int toy=a[j].body.front().y;
			int nowx=a[j].body.front().x;
			int nowy=a[j].body.front().y;
			if(s[j][i]=='W') tox--;
			if(s[j][i]=='S') tox++;
			if(s[j][i]=='A') toy--;
			if(s[j][i]=='D') toy++;
			//(tox,toy)表示下一步蛇头的位置
			if(mp[tox][toy]=='&'){//如果是食物
				mp[nowx][nowy]='#';
				mp[tox][toy]='@';
				a[j].len++;
				w aa;
				aa.x=tox;
				aa.y=toy;
				a[j].body.push_front(aa);
				continue;
			}
			if(mp[tox][toy]=='@'||mp[tox][toy]=='#'||tox<1||tox>n||toy<1||toy>m){//如果蛇满足死亡条件
				a[j].die=true;
				deal(j);
				a[j].len=0;
				continue;
			}
			//其余情况即为蛇走到了空地上
			mp[nowx][nowy]='#';
			mp[tox][toy]='@';
			mp[a[j].body.back().x][a[j].body.back().y]='.';
			w aa;
			aa.x=tox;
			aa.y=toy;
			a[j].body.push_front(aa);
			a[j].body.pop_back();
		}
	}
}
```
### 第四部分：输出

依照题目，按照以蛇身长度为第一关键字、以蛇的编号为第二关键字排序后输出，同时暴力枚举地图的格子，如果有食物就将答案加一。

代码：

```cpp
bool cmp(snake x,snake y){
	if(x.len==y.len) return x.id<y.id;
	return x.len>y.len;
}
void write(){
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;i++) cout<<a[i].len<<" "<<a[i].id<<endl;
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='&') ans++;
		}
	}
	cout<<ans;
}
```
至此，我们就成功将这道题解决啦！

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct w{
	int x;
	int y;
};
struct snake{
	bool die=false;
	int id;
	int len;
	deque<w> body;
}a[209];

char mp[209][209];
char s[209][209];
bool vis[209][209];
int n,m,k;
int cnt=0;//记录目前是第几条蛇

int dx[5]={0,0,1,0,-1};
int dy[5]={0,1,0,-1,0};

void dfs(int id,int x,int y,int l){//id表示第几条蛇
	a[id].len=max(a[id].len,l);
	w aa;
	aa.x=x,aa.y=y;
	a[id].body.push_back(aa);
	for(int i=1;i<=4;i++){
		int xx=dx[i]+x;
		int yy=dy[i]+y;
		if(xx<1||xx>n||yy<1||yy>m||vis[xx][yy]||mp[xx][yy]=='.'||mp[xx][yy]=='&') continue;
		if(mp[xx][yy]=='#'){
			vis[xx][yy]=true;
			dfs(id,xx,yy,l+1);
		}
	}
}
void clear(){
	for(int i=0;i<=200;i++){
		for(int j=0;j<=200;j++) vis[i][j]=false;
	}
}
void deal(int id){
	while(!a[id].body.empty()){
		mp[a[id].body.front().x][a[id].body.front().y]='&';
		a[id].body.pop_front();
	}
}

void play(){
	for(int i=1;i<=k;i++){
		for(int j=1;j<=cnt;j++){//表示第j条蛇的第i次操作
			if(a[j].die==true) continue;//如果已经死了就跳过
			int tox=a[j].body.front().x;
			int toy=a[j].body.front().y;
			int nowx=a[j].body.front().x;
			int nowy=a[j].body.front().y;
			
			if(s[j][i]=='W') tox--;
			if(s[j][i]=='S') tox++;
			if(s[j][i]=='A') toy--;
			if(s[j][i]=='D') toy++;
			//(tox,toy)表示下一步蛇头的位置
			if(mp[tox][toy]=='&'){
				mp[nowx][nowy]='#';
				mp[tox][toy]='@';
				a[j].len++;
				w aa;
				aa.x=tox;
				aa.y=toy;
				a[j].body.push_front(aa);
				continue;
			}
			if(mp[tox][toy]=='@'||mp[tox][toy]=='#'||tox<1||tox>n||toy<1||toy>m){
				a[j].die=true;
				deal(j);
				a[j].len=0;
				continue;
			}
			
			mp[nowx][nowy]='#';
			mp[tox][toy]='@';
			mp[a[j].body.back().x][a[j].body.back().y]='.';
			w aa;
			aa.x=tox;
			aa.y=toy;
			a[j].body.push_front(aa);
			a[j].body.pop_back();
		}
	}
}
void get_snake(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='@'){
				cnt++;
				a[cnt].id=cnt;
				a[cnt].len=1;
				clear();
				vis[i][j]=true;
				dfs(cnt,i,j,1);
			}
		}
	}
}
bool cmp(snake x,snake y){
	if(x.len==y.len) return x.id<y.id;
	return x.len>y.len;
}
void write(){
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;i++) cout<<a[i].len<<" "<<a[i].id<<endl;
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='&') ans++;
		}
	}
	cout<<ans;
}
void work(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
		}
	}
	get_snake();
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=k;j++) cin>>s[i][j];
	}
	play();
	write();
}
int main(){
	work();
}
```


---

