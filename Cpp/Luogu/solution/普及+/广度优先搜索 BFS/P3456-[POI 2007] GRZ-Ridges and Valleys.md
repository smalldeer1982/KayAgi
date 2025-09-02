# [POI 2007] GRZ-Ridges and Valleys

## 题目描述

**译自 POI 2007 Stage 2. Day 0「[Ridges and Valleys](https://szkopul.edu.pl/problemset/problem/rd6H05Dm8ME79sO3U9_f_ga_/site/?key=statement)」**

给定一个 $n \times n$ 的网格状地图，每个方格 $(i,j)$ 有一个高度 $w_{ij}$。如果两个方格有公共顶点，则它们是相邻的。

定义山峰和山谷如下：
* 均由地图上的一个连通块组成；
* 所有方格高度都相同；
* 周围的方格（即不属于山峰或山谷但与山峰或山谷相邻的格子）高度均大于山谷的高度，或小于山峰的高度。

求地图内山峰和山谷的数量。特别地，如果整个地图方格的高度均相同，则整个地图既是一个山谷，也是一个山峰。

## 样例 #1

### 输入

```
5
8 8 8 7 7
7 7 8 8 7
7 7 7 7 7
7 8 8 7 8
7 8 8 8 8```

### 输出

```
2 1```

## 样例 #2

### 输入

```
5
5 7 8 3 1
5 5 7 6 6
6 6 6 2 8
5 7 2 5 8
7 1 0 1 7```

### 输出

```
3 3```

# 题解

## 作者：李尧 (赞：46)

其实写完后看了一下别的大佬的方法，

好像还有点麻烦啊，是我想得简单了吗？？？

我是不会告诉你们我WA5次的

在次提醒一下，首先，你得看清楚是八个点（就我没看到打成四个点了吗？？？），然后，注意有0，别像我90调半天（如果你第二个点WA，那么请从0上找）

还有最重要的一点，注意，如果一个模块附近有比它大的，有比它小的，那么它不是山谷，也不是山峰！！！

主要就是判断这个，所以怎么办呢？？

其实很好想，只要一个模块中所有的点其周围的点都符合比这个模块大或者比这个模块小就可以了，判定我们可以放到bfs里面

好啦放代码啦，不要复制哦

```
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int x,y;
    Node(int i=0,int j=0){
        x=i;y=j;    
}
};
queue <Node> q;
int dx[10]={0,0,1,1,1,-1,-1,-1},dy[10]={1,-1,0,-1,1,0,-1,1},sf,sg,p,n;
int a[1007][1007],ans;
bool v[1007][1007],flag;
void bfs(int sx,int sy){
    int col=a[sx][sy];//记录一下板块的颜色
    q.push(Node(sx,sy));
    for(int j=0;j<8;j++){//起点也要判定
        int xx=sx+dx[j];//判定周围八个点，这主要是来判断既不是山峰也不是山谷的情况
        int yy=sy+dy[j];
        if(xx>=1&&xx<=n&&yy>=1&&yy<=n&&a[xx][yy]!=col){//如果颜色不同，那么这就是这个板块“周围的点”
                if(p==-1) p=a[xx][yy];//如果还没有找到一个这样的点的话（-1是初始化），那么直接赋值
                else if((p-col>0&&a[xx][yy]-col<0)||(p-col<0&&a[xx][yy]-col>0)) {//如果这个板块周围出现既有比它大，又有比它小的情况，那么它就不是山峰或山谷，直接赋true
                flag=true;
                break;
            }
    }
}
    while(!q.empty()){
        Node cur=q.front();
        for(int i=0;i<8;i++){
            int nx=cur.x+dx[i];
            int ny=cur.y+dy[i];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&!v[nx][ny]&&a[nx][ny]==col){
                v[nx][ny]=true;
                q.push(Node(nx,ny));
                if(!flag)//如果我们已经发现它既不是山峰又不是山谷的话，那么直接淘汰，一心灌水就行了，不要傻乎乎地继续判定了
                    for(int j=0;j<8;j++){//判定和上面相同
                        int xx=nx+dx[j];
                        int yy=ny+dy[j];
                        if(xx>=1&&xx<=n&&yy>=1&&yy<=n&&a[xx][yy]!=col){
                            if(p==-1) p=a[xx][yy];
                            else if((p-col>0&&a[xx][yy]-col<0)||(p-col<0&&a[xx][yy]-col>0)) {
                                flag=true;
                                break;
                            }
                        }
                    }
            }           
        }
        q.pop();    
    }
    if(flag) return;//不是山峰也不是山谷的情况
    if(p<col) sf++;//如果周边的点比它小，山峰，反之，山谷
    else sg++;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(!v[i][j]){
                v[i][j]=true;
                p=-1;flag=false;//初始p为-1，代表还没找到一个周围的点，p就是记录周围的点的，只要去记录第一个点，就能确定它是山峰还是山谷，或者啥也不是
                bfs(i,j);
                ans++;
            }   
    if(ans==1) printf("1 1");//注意特判，题目有说
    else printf("%d %d",sf,sg);
    return 0; 
}
```

---

## 作者：采薇 (赞：13)

可以写深搜 从一个没搜过的点开始深搜周围与它相邻的同高度的点

并标记搜过 同时记录这个区域是谷还是峰 所有高度相等情况特判


```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int n,hei[1010][1010],w;bool g[1010][1010];//w==1谷w==2峰 
int mx[9]={0,-1,-1,-1,0,0,1,1,1},a=0,b=0;//a为山谷数 b为山峰数
int my[9]={0,-1,0,1,-1,1,-1,0,1};
void search(int posx,int posy)
{
    for(int i=1;i<=8;i++)
    {
//搜索与当前点相邻的3~8个点
        int xx=posx+mx[i],yy=posy+my[i];
        if(!(xx>=1&&xx<=n&&yy>=1&&yy<=n))
            continue;
        if(hei[xx][yy]==hei[posx][posy]&&g[xx][yy]==0)
            g[xx][yy]=1,search(xx,yy);
        else if(hei[xx][yy]<hei[posx][posy]&&w==1)
            w=-1;
        else if(hei[xx][yy]>hei[posx][posy]&&w==2)
            w=-1;
//如果这个区域周围既有比它高的又有比它低的 则它什么也不是
//为了区分什么都不是的区域与没确定是是峰还是谷
// 前者为-1 后者为0
        else if(w==0)
        {
            if(hei[xx][yy]<hei[posx][posy])
                w=2;
            if(hei[xx][yy]>hei[posx][posy])
                w=1;
        }
    }
//搜到与当前搜索高度不同的点 暂且标记当前搜索区域是峰还是谷
}
int main()
{
    scanf("%d",&n);    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&hei[i][j]);
    int x=hei[1][1];    w=1;
    for(int i=2;i<=n;i++)
        if(hei[1][i]!=x)
            w=0;
    if(w==1)
        for(int i=2;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(hei[i][j]!=x)
                    w=0;
    if(w==1)
    {
        cout<<"1 1";
        return 0;
//特判 若所有高度相同 则山峰数=1 山谷数=1
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(g[i][j]==0)
            {
//找到一个没搜过的点开始搜索
                w=0;
                g[i][j]=1;
                search(i,j);
                if(w==1)
                    a++;
                else if(w==2)
                    b++;
            }    
        }    
    }    
    printf("%d %d",b,a);
//输出答案
    return 0;
}

```

---

## 作者：lhhh (赞：10)

###  新评测机后dfs会爆栈！！！ #2 #9 点都过不了！调了一下午过不了一直RE，只好转bfs了，发现没有bfs的题解水一发，注释在代码里

### 题意里有一个小小的坑，就是当前坡相邻块即有高的也有低的，那它是一个山坡，不计入答案

### bfs求一下联通块判断答案是否贡献加一下就好了

```cpp
#include <cstdio>
#include <iostream>
#include <queue>
//可爱的头文件
#define DEBUG(x) std::cerr << #x << "=" << x << std::endl
//DEBUG专用
const int MAXN = 1000 + 10;

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
//8联通
struct Node {
    int x, y;
};
//结构体存点
int n, ridge, valley;
int map[MAXN][MAXN], vis[MAXN][MAXN];
bool sg, sf;
std::queue<Node> q;
//全局变量
void bfs(int x, int y) {
    Node start;	//初始值
    start.x = x, start.y = y;
    vis[x][y] = 1;
    q.push(start);
    while (!q.empty()) {
        Node temp = q.front(); q.pop();	//队首
        for (int i = 0; i <= 7; i++) {//八方向
            int nx = temp.x + dx[i];
            int ny = temp.y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;	//越界
            if (map[nx][ny] == map[temp.x][temp.y] && !vis[nx][ny]) {	// 高度相等打上标记接着搜
                vis[nx][ny] = 1;
                q.push((Node){nx, ny});
            }
            else {	// 山峰山谷是否成立
                if (map[nx][ny] > map[temp.x][temp.y]) sf = 0;
                if (map[nx][ny] < map[temp.x][temp.y]) sg = 0;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    bool flag = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &map[i][j]);
            if (map[i][j] != map[1][1]) flag = 1;
        }
    if (!flag) {	// 判断是否全部高度相等
        printf("1 1");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (!vis[i][j]) { //如果是新的联通块
                sf = 1, sg = 1;
                bfs(i, j);
                ridge += sf;
                valley += sg;
            }
        }
    printf("%d %d\n", ridge, valley);
    return 0;
}

```

---

## 作者：ZhouSong (赞：10)

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001][1001],b[1001][1001],c[9]= {0,0,0,1,1,1,-1,-1,-1},v[9]= {0,1,-1,0,1,-1,0,1,-1},sg,sf,n,i,j;
int search(int x,int y) {
    if(x>=1&&x<=n&&y>=1&&y<=n&&b[x][y]!=a[i][j]) { //判断是否已经搜过或超出边界
        b[x][y]=a[i][j]; //标记已经搜过
        for(int k=1; k<=8; ++k) if(x+c[k]>=1&&x+c[k]<=n&&y+v[k]>=1&&y+v[k]<=n) { //向周围八个方向搜索
                if(a[x+c[k]][y+v[k]]==a[i][j]) {
                    search(x+c[k],y+v[k]); //高度相同则视为同一块，往下搜
                } else {
                    if(a[x+c[k]][y+v[k]]>a[i][j]) sg=1; //如果周围的某一个块比它高则它可能是山谷
                    if(a[x+c[k]][y+v[k]]<a[i][j]) sf=1; //如果周围的某一个块比它低则它可能是山峰
                }
            }
    }
    return 1;
}
int main() {
    int sfs=0,sgs=0;
    bool ttt=1;
    scanf("%d",&n);
    memset(b,-1,sizeof(b));
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) {
            scanf("%d",&a[i][j]);
            if(a[i][j]!=a[1][1]) ttt=0;
        }
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j)
            if(ttt) { //特判，所有高度相同则山谷数=1，山峰数=1
                printf("1 1");
                return 0;
            }
    for(i=1; i<=n; ++i) for(j=1; j<=n; ++j) {
            search(i,j);
            if(sg==1&&sf==0) ++sgs; //是山谷而不是山峰，山谷数++
            if(sg==0&&sf==1) ++sfs; //是山峰而不是山谷，山峰数++
            sg=sf=0; //还原 
        }
    printf("%d %d",sfs,sgs);
    return 0;
}
//第一次发题解，管理员大大求过
```

---

## 作者：qingfengwuhui (赞：5)

写的时候，总感觉是管理员设错了。

这是一道非常非常普通的bfs。

接下来让我们来仔细的分析一下。

-----
## First

先看题干，题目中的意思是输入一张 n * n 的地图，让我们输出地图中的山峰和山谷。

题中的山峰和山谷内的任意一块一定是相平的。
那么，这题的目的也就清楚了。这是一道搜地图中的连通块的模板题。

不过要注意：
	
    1.每个连通块不一定是山峰或山谷，也可能什么也不是。我们要及时判断。
    
    2.每一次扩展需要探索的点时，要注意为8个方向，代码实现时要小心，不能思维定式。
--------------
对于 1. 我们的解决办法是在搜连通块时，如果要扩展的地方低于 或 高于当前的位置时，分别用变量记录，但并不放入搜索队列中。

对于 2. 我们的解决办法就轻松多了，只要在定义方向数组时横纵坐标都为8就行了

------------
### 好了，
我们已经将题干中的信息都提取出来了，算法也清晰了，接下来就是代码的实现问题了。

在代码中的注意点也会标出
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[10001][10001];
int dep[10001][10001];//这个数组主要表明地图中已经走过的位置 对代码的优化有很大帮助 但是要注意 在比赛中前往不要定义这么大，会爆的（~~我已经有深刻的体会了~~）
struct xi{
	int x , y;
}c[1000001];//这里的队列使用一个struct来表示当前要搜的位置的横纵坐标
int h = 1 , t = 1;
/*这里的队列是我手打的习惯了STL的小伙伴可能会不习惯，
但是我还是要说一声 head 为 t ， tail 为 h ，千万不要看错*/
int ans1 = 0 , ans2 = 0;//表示山峰 和 山谷的数量 
int ax[8] = {-1 , -1 , -1 , 0 , 1 , 1 , 1 , 0};
int ay[8] = {-1 , 0 , 1 , 1 , 1 , 0 , -1 , -1};//方向数组要小心定义 ， 弄清楚各个方向
void bfs(int x , int y){
	int xa = 0 , ya = 0;//表示当前的平地的周围是否有低地 或 高地
	h ++;//当上一次while退出时 ， h == t ，所以此时要++
	c[t].x = x , c[t].y = y;//把起始位置附入队列的头
	do{
//		cout << c[t].x << " " << c[t].y << endl; 
//		dep[c[t].x][c[t].y] = 1;检查代码 可以忽略 但是大家在比赛中的调试代码千万不要留下
		for(int i = 0;i < 8;i ++){//搜8个方向
			int xx = c[t].x + ax[i] , yy = c[t].y + ay[i]; 
			if(xx <= 0 || xx > n || yy <= 0 || yy > n)continue;//越界跳过
			if(a[xx][yy] < a[c[t].x][c[t].y]){//表示目标位置低于当前位置 即 当前的平地周围有低地 
				xa = 1;
			}
			else if(a[xx][yy] > a[c[t].x][c[t].y]){//表示目标位置高于当前位置 即 当前的平地周围有高地 
				ya = 1;
			}
			if(dep[xx][yy])continue;//这里要注意 判断是否搜过要在判断目标位置之后。
//不懂得小伙伴可以调换一下，测试一下 一定会出错
			if(a[xx][yy] == a[c[t].x][c[t].y]){//表示目标位置等于当前位置 即 目标位置是当前的平地的一部分可以入队 
				c[h].x = xx;
				c[h].y = yy;
				dep[c[h].x][c[h].y] = 1;
				h ++;//入队操作
			}
		}
//		cout << " 1 " << endl;
		t ++;
	}while(h > t);
	if(xa == 1){
		if(ya == 0)//表示当前的平地周围都较低 当前的平地为为山峰 
		{
			ans1 ++;
		}
	}
	else if(ya == 1){
//表示当前的平地周围都较高 当前的平地为山谷 
			ans2 ++;
	}//这就是解决注意 1. 的方法
	return ;
}
void print(){
/*这里要说一声 当整个地图都为同一高度时 
它既是一个山峰 也是一个山谷 
所以在输出是要把整张地图都遍历一遍*/
	if(ans1 || ans2){
		cout << ans1 << " " << ans2 << endl;
		return ;
	}
	int x = 0;
	for(int i = 2;i <= n;i ++)
	 for(int j = 2;i <= n;i ++){
	 	if(a[i][j] != a[i - 1][j])
	 	x = 1;
	 }
	for(int i = 2;i <= n;i ++)
	if(a[i][1] != a[i - 1][1])
	x = 1;
	if(x){
		cout << ans1 << " " << ans2 << endl;
		return ;
	}
	cout << 1 << " " << 1 << endl;
	return ;
}
int main(){
//	freopen("hill.in" , "r" , stdin);
//	freopen("hill.out" , "w" , sdtout);
//考试的时候 freopen一定不要忘记取消注释
	cin >> n;
	for(int i = 1;i <= n;i ++)
	 for(int j = 1;j <= n;j ++)
	 cin >> a[i][j];
	/*	
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++)
		cout << a[i][j] << " ";
		cout << endl;
	}
	*///个人习惯
    for(int i = 1;i <= n;i ++)
	 for(int j = 1;j <= n;j ++)
	 if(!dep[i][j]){
//	 cout << i << " " << j << endl;
	 	dep[i][j] = 1;
	 	bfs(i , j);
	 }
	print(); 
	return 0;
} 
```
以上为完整的代码。
（~~如果你还没看懂，就再看一遍吧！~~）

------

## END

###### （~~写的不好，大佬勿喷~~）

---

## 作者：FCBM71 (赞：5)

赤裸裸滴bfs吖，翻了翻楼下的大佬都加了各种各样的特判，但是似乎并不用这样（感觉这题应该是黄）

$\ $

##  核心思路

怎么bfs想必大家都知道，我也不多赘述，在这里主要介绍一下怎么简单地判断山峰和山谷。如果一个区域是山峰，那么他周围一圈的点的高度都应该比他低；同理，如果一个点是山谷，那个他周围一圈的点的高度都应该比他的高。

我们知道，对于每一个点都有八个联通的点，如果它们的高度相等，那个它们同属于一个区域，入队。**如果周围某一个点高度比他高，那么这片区域不可能是山峰；同理，如果周围某一个点高度比他低，那么这片区域不可能是山谷**。因此我们可以对每一个区域都声明两个布尔变量`ifhigh`和`iflow`（分别表示是否有更高的、更矮的，初值均为1），**如果目标点高度小于当前点，`iflow=0`；如果目标点的高度大于当前点，`ifhigh=1`。**当对某一个区域搜索完成之后，如果iflow为1，则它为山谷；如果ifhigh为1，则它为山峰

于是附上这一部分的代码
```cpp
void bfs(int p,int q){
	vis[p][q]=1;
	queue<int>x,y;
	x.push(p);y.push(q);
	bool ifhigh=1,iflow=1;   //起点初始化
	while(!x.empty()){
		rg int xs=x.front();
		rg int ys=y.front();
		for(rg int i=0;i<=7;++i){
			rg int xf=xs+dx[i];
			rg int yf=ys+dy[i];     //枚举联通的目标点
			if(xf>0&&xf<=n&&yf>0&&yf<=n){
				if(a[xf][yf]==a[xs][ys]){
					if(!vis[xf][yf]){
						x.push(xf);y.push(yf);
						vis[xf][yf]=1;        //同区域入队
					}
				}
				if(a[xf][yf]<a[xs][ys])iflow=0;  //是否有更低？
				if(a[xf][yf]>a[xs][ys])ifhigh=0; //是否有更高？
			}
		}
		x.pop();y.pop();
	}
	if(ifhigh)++ans1;
	if(iflow)++ans2;    //更新答案
} 
```

---

完整代码？自己动手，丰衣足食

---

## 作者：御坂10027号 (赞：1)

#### ~~一开始认为是dp，后来又觉得是BFS，但是我不会打，所以打了个DFS~~

~~学校的优秀Window3卡了我三个点QWQ~~

文化课期中考试前MRYang给hszz的oier们来了几道题来缓解一下文化课备考的紧张气氛（QWQ）

~~T1就是这道坑题~~

首先附上我第一次打的错误代码QWQ

```cpp
int main() {
	freopen("mpv.in", "r", stdin);
	freopen("mpv.out", "w", stdout);
	memset(w, -1, sizeof(w));
	n = read();
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			w[i][j] = read();
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			flag = false;
			if(maxx < w[i][j]) {
				maxx = w[i][j];
				fe = 0;
			}
			if(minn > w[i][j]) {
				minn = w[i][j];
				gu = 0;
			}
			if(maxx == w[i][j] && !mp[i][j]) {
				dfs(i, j, 0);
				fe++;
			}
			if(minn == w[i][j] && !mp[i][j]) {
				dfs(i, j, 0);
				gu++;
			}
		}
	}
	cout << fe << " " << gu;
	fclose(stdin); fclose(stdout);
	return 0;
}
```

~~代码不全，没有保存~~

误的思路浪费了我一个多小时QWQ

注意是判断比周围的山的高度大或小

不是求全部的MAX和MIN的数量 

QWQ 

接下来是AC代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n;
ll fe, gu, w[1010][1010];
//fe为山峰总数 gu为山谷总数 
ll maxx, minn = 1e9;
bool mp[1010][1010], flag1[1010][1010], flag2[1010][1010], f, g;
//flag1[]表示每个点是否为山峰
//flag2[]表示每个点是否为山谷


inline ll read() {
	ll w = 0, e = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		e = ch =='-' ? -1 : 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		w = (w << 3) + (w << 1) + (ch ^ 48);
		ch = getchar();
	}
	return w * e;
}

void dfs(int x, int y, int fl) {
	if(mp[x][y]) return;//若已经扫过，直接返回 
	mp[x][y] = true;//标记 
	if(flag1[x][y]) f = true;//不为山峰 
	if(flag2[x][y]) g = true;//不为山谷 
	if(fl != 1 && w[x - 1][y] == w[x][y]) dfs(x - 1, y, 2);//上 
	if(fl != 2 && w[x + 1][y] == w[x][y]) dfs(x + 1, y, 1);//下 
	if(fl != 3 && w[x][y - 1] == w[x][y]) dfs(x, y - 1, 4);//左 
	if(fl != 4 && w[x][y + 1] == w[x][y]) dfs(x, y + 1, 3);//右 
	if(fl != 5 && w[x - 1][y - 1] == w[x][y]) dfs(x - 1, y - 1, 6);//左上 
	if(fl != 6 && w[x + 1][y + 1] == w[x][y]) dfs(x + 1, y + 1, 5);//右下 
	if(fl != 7 && w[x + 1][y - 1] == w[x][y]) dfs(x + 1, y - 1, 8);//左下 
	if(fl != 8 && w[x - 1][y + 1] == w[x][y]) dfs(x - 1, y + 1, 7);//右上 
}

int main() {
	freopen("mpv.in", "r", stdin);
	freopen("mpv.out", "w", stdout);
	/*memset(w, -1, sizeof(w));
	n = read();
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			w[i][j] = read();
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			flag = false;
			if(maxx < w[i][j]) {
				maxx = w[i][j];
				fe = 0;
			}
			if(minn > w[i][j]) {
				minn = w[i][j];
				gu = 0;
			}
			if(maxx == w[i][j] && !mp[i][j]) {
				dfs(i, j, 0);
				fe++;
			}
			if(minn == w[i][j] && !mp[i][j]) {
				dfs(i, j, 0);
				gu++;
			}
		}
	}
	cout << fe << " " << gu;*/
	//错误的思路浪费了我一个多小时QWQ
	/*
		注意是判断比周围的山的高度大或小
		不是求全部的MAX和MIN的数量 
		QWQ 
	*/ 
	memset(w, -1, sizeof(w));//把所有的都标记为-1代替特判 
	n = read();
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			w[i][j] = read();
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if((w[i][j] > w[i - 1][j] && w[i - 1][j] != -1) || (w[i][j] > w[i + 1][j] && w[i + 1][j] != -1) || (w[i][j] > w[i][j - 1] && w[i][j - 1] != -1) || (w[i][j] > w[i][j + 1] && w[i][j + 1] != -1) || (w[i][j] > w[i - 1][j - 1] && w[i - 1][j - 1] != -1) || (w[i][j] > w[i + 1][j + 1] && w[i + 1][j + 1] != -1) || (w[i][j] > w[i + 1][j - 1] && w[i + 1][j - 1] != -1) || (w[i][j] > w[i - 1][j + 1] && w[i - 1][j + 1] != -1)) flag2[i][j] = true;
			//一定要注意把-1的除去 
			if(w[i][j] < w[i - 1][j] || w[i][j] < w[i + 1][j] || w[i][j] < w[i][j - 1] || w[i][j] < w[i][j + 1] || w[i][j] < w[i - 1][j - 1] || w[i][j] < w[i + 1][j + 1] || w[i][j] < w[i + 1][j - 1] || w[i][j] < w[i - 1][j + 1]) flag1[i][j] = true;
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			f = g = false;
			if(!mp[i][j]){
				dfs(i, j, 0);
				if(!f) fe++;
				if(!g) gu++;
			}
		}
	}
	cout << fe << " " << gu << endl;
	fclose(stdin); fclose(stdout);
	return 0;
}
```


---

## 作者：sounds_666 (赞：1)

虽然看到了非常多思路一样的题解，但还是想发一下这篇题解，因为想讲一些细节

大概题意：在一个的连通块所有单元格中，比四周都高的是山峰，比四周低的是山谷。

思路：暴力bfs,找到所有联通块，做标记。

细节的话就看代码吧：

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define mk make_pair
#define gc getchar()
int n,ansh,ansl; 
int mapp[1010][1010];
bool vis[1010][1010];
queue<pair<int,int> >q; 
const int dx[8]={1,1,1,-1,-1,-1,0,0},dy[8]={-1,0,1,-1,0,1,-1,1};//听说先往搜右边更快
inline int read(){
	char ch=gc;int s=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=gc;}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0',ch=gc;}
	return f*s;
}
bool rule(int x,int y){
	if(x<1||x>n||y<1||y>n)return 1;
	return 0;
}
bool bfs(int pp,int qq){
	bool flag=1;
	q.push(mk(pp,qq));
	vis[pp][qq]=1;
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;
		q.pop();
		for(int i=0;i<8;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(rule(nx,ny))continue;//一定要判越界
			if(mapp[nx][ny]>mapp[x][y])flag=0;
        //这里不要直接return，会挂掉，一定要让他搜完，找到完整连通块
			else if(!vis[nx][ny]&&mapp[x][y]==mapp[nx][ny]){
				vis[nx][ny]=1;
				q.push(mk(nx,ny));
			}
		}
	}
	if(flag)return 1;
	else return 0;
}
bool bfs_(int pp,int qq){
	bool flag=1;
	q.push(mk(pp,qq));
	vis[pp][qq]=1;
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;
		q.pop();
		for(int i=0;i<8;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(rule(nx,ny))continue;
			if(mapp[nx][ny]<mapp[x][y])flag=0;
			else if(!vis[nx][ny]&&mapp[x][y]==mapp[nx][ny]){
				vis[nx][ny]=1;
				q.push(mk(nx,ny));
			}
		}
	}
	if(flag)return 1;
	else return 0;
}
int main(){
//	freopen("mountain.in","r",stdin);
//	freopen("mountain.out","w",stdout);	
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			mapp[i][j]=read();
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(vis[i][j])continue;
        //一个优化，这个点已经被其他点搜到过，就不搜，因为已经找到了完整连通块
			while(!q.empty())q.pop();
			if(bfs(i,j))ansh++;//puts("SS");
		}
	}
	memset(vis,0,sizeof(vis))//及得清空数组
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(vis[i][j])continue;
			while(!q.empty())q.pop();
			if(bfs_(i,j))ansl++;
		}
	}
	printf("%d %d\n",ansh,ansl);
	return 0;
}
```


---

