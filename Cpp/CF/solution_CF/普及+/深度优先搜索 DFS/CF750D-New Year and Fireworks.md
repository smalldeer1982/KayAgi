# New Year and Fireworks

## 题目描述

One tradition of welcoming the New Year is launching fireworks into the sky. Usually a launched firework flies vertically upward for some period of time, then explodes, splitting into several parts flying in different directions. Sometimes those parts also explode after some period of time, splitting into even more parts, and so on.

Limak, who lives in an infinite grid, has a single firework. The behaviour of the firework is described with a recursion depth $ n $ and a duration for each level of recursion $ t_{1},t_{2},...,t_{n} $ . Once Limak launches the firework in some cell, the firework starts moving upward. After covering $ t_{1} $ cells (including the starting cell), it explodes and splits into two parts, each moving in the direction changed by $ 45 $ degrees (see the pictures below for clarification). So, one part moves in the top-left direction, while the other one moves in the top-right direction. Each part explodes again after covering $ t_{2} $ cells, splitting into two parts moving in directions again changed by $ 45 $ degrees. The process continues till the $ n $ -th level of recursion, when all $ 2^{n-1} $ existing parts explode and disappear without creating new parts. After a few levels of recursion, it's possible that some parts will be at the same place and at the same time — it is allowed and such parts do not crash.

Before launching the firework, Limak must make sure that nobody stands in cells which will be visited at least once by the firework. Can you count the number of those cells?

## 说明/提示

For the first sample, the drawings below show the situation after each level of recursion. Limak launched the firework from the bottom-most red cell. It covered $ t_{1}=4 $ cells (marked red), exploded and divided into two parts (their further movement is marked green). All explosions are marked with an 'X' character. On the last drawing, there are $ 4 $ red, $ 4 $ green, $ 8 $ orange and $ 23 $ pink cells. So, the total number of visited cells is $ 4+4+8+23=39 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750D/958e71e20888e0f3c92e01fa2be2e012117f122b.png)For the second sample, the drawings below show the situation after levels $ 4 $ , $ 5 $ and $ 6 $ . The middle drawing shows directions of all parts that will move in the next level.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750D/c21fe29a69f3371f920085202e17e34b6a0270b1.png)

## 样例 #1

### 输入

```
4
4 2 2 3
```

### 输出

```
39
```

## 样例 #2

### 输入

```
6
1 1 1 1 1 3
```

### 输出

```
85
```

## 样例 #3

### 输入

```
1
3
```

### 输出

```
3
```

# 题解

## 作者：FreedomKing (赞：1)

### 思路

很明显的可以发现这个烟花的飞行过程就很像广搜，又因为 $n\le 30,t_i\le 5$，那么烟花经过的矩阵最大也不会超过 $30\times 5\times 2=300$，就直接确定了使用广搜模拟整个烟花发散过程的做法。

首先，需要用到两个移动数组，每次朝某个方向移动时 $x,y$ 只需要分别加上对应的数组中对应方向的指就能向对应方向移动。

```cpp
const int dx[8]={0,-1,-1,-1,0,1,1,1};
const int dy[8]={1,1,0,-1,-1,-1,0,1};
```

然后剩下的就是在矩阵上的广搜模板了详见代码注释。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid (N>>1)
using namespace std;
const int dx[8]={0,-1,-1,-1,0,1,1,1};
const int dy[8]={1,1,0,-1,-1,-1,0,1};
const int N=3e2+5;
int a[N],f[N][N],n,m,t,k,ans;
bool vis[N][N][N][8];
struct node{int x,y,depth,dir;};//结构体，用来存储移动到每个点时的信息
void bfs(){
	queue<node>q;//队列，用来存下次移动的信息
	q.push({mid,mid,1,2});//存下起点
	while(!q.empty()){//只要还有要走的，就不停歇地循环下去
		int x=q.front().x,y=q.front().y,dep=q.front().depth,dir=q.front().dir;//把队头的信息取出
		q.pop();//用完就可以直接推出队列了
		if(vis[x][y][dep][dir]||dep>n) continue;//剪枝
		vis[x][y][dep][dir]=true;//标记剪枝
		for(int i=1;i<=a[dep];i++){
			x+=dx[dir];//移动
			y+=dy[dir];
			f[x][y]=1;//标记已被经过
		}
		q.push({x,y,dep+1,(dir+1)%8});//向下两个方向广搜
		q.push({x,y,dep+1,(dir+7)%8});
	}
	return;
}
inline int qread(){//快速读入
#define qr qread()
	int x=0,c=getchar(),t=1;
	while(!(c>='0'&&c<='9')){
		t^=(c=='-');
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return (t?x:-x);
}
signed main(){
	n=qr;
	for(int i=1;i<=n;i++) a[i]=qr;
	bfs();
	for(int i=1;i<N;i++) for(int j=1;j<N;j++) if(f[i][j]) ans++;//统计有多少点被经过
	cout<<ans;
	return 0;
}
```

---

## 作者：crh1272336175 (赞：1)

看见下边的大佬写的是dfs，本蒟蒻来写一个bfs

首先，不难看出，最多只有300*300个点，所以搜索量并不是很大

对于每一个点，我们要记录4个信息
```cpp
struct node
{
	int x,y,depth,dir;
};
```
其中x,y是坐标，depth是当前点的深度，以及当前点的方向

对于每一个点，我们如果搜索到过这个点，则用v数组标记，最后统计答案的时候只要这样
```cpp
for(int i=1; i<=300; i++)
	    for(int j=1; j<=300; j++)
	        if(v[i][j]) ans++;
printf("%d",ans); 
```
至此，看似完美的bfs框架已经呈现


but！！！！！！

这题仅仅这样，会TLE，我们需要对当前的走法做记忆化

也可以称之为判重

最终的AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=305,N=35;
int n,ans;
int a[N],v[M][M],mp[M][M][N][8];
int dx[8]={0,-1,-1,-1,0,1,1,1};
int dy[8]={1,1,0,-1,-1,-1,0,1};
struct node
{
	int x,y,depth,dir;
};
queue<node> q;
void bfs()
{
	q.push({152,152,1,2});//起先向上移动,dir=2
	while(!q.empty())
	{
		node now=q.front(); q.pop();
		if(mp[now.x][now.y][now.depth][now.dir] || now.depth>n) continue;
		mp[now.x][now.y][now.depth][now.dir]=1;
		for(int i=1; i<=a[now.depth]; i++)
		{
			now.x+=dx[now.dir];
			now.y+=dy[now.dir];
			v[now.x][now.y]=1;
		}
		q.push({now.x,now.y,now.depth+1,(now.dir+1)%8});
		q.push({now.x,now.y,now.depth+1,(now.dir+7)%8});
	} 
}
int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	bfs();
	for(int i=1; i<=300; i++)
	    for(int j=1; j<=300; j++)
	        if(v[i][j]) ans++;
	printf("%d",ans); 
	return 0;
}
```



---

## 作者：JACK_POT (赞：0)

# **暴力+搜索**
#### ~~手动打表它不香吗~~【逃~~


------------
首先想到用dfs来遍历烟花分支，用一张表来标记是否经过点，烟花一共有8个方向，而且很容易想到每一个方向过后都只有两个固定的方向可以选择，因此本题可以列举8个方向之后的2种可能来解决。

烟花可能会向四面八方绽开，如果原点为[0,0]，坐标可能会有负数，因此我们需要每次在表上操作时对坐标加一个偏移值。因为n<=30,ti<=5,所以最多向一个方向移动150个单位，偏移值为150，标记表开为300*300

需要注意的是，可能有同时在同一位置，同一方向的分支产生，这时需要记忆化，否则会超时~~QAQ~~

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=150;
int n,a[35],Map[305][305],ans,f[35][305][305][3][3];
void dfs(int step,int x,int y,int p,int q){//当前是第step层，开始坐标为[x,y]
//x轴方向为p，y轴方向为q(用-1，1，0表示，x轴和y轴方向是数组存储顺序)
	if(f[step][x][y][p+1][q+1]) return;
	f[step][x][y][p+1][q+1]=1;//记忆化剪枝
	if(step>n) return;//层数到n+1退出
	int len=a[step];//每次走的长度
	for(int i=1;i<=len;i++){
		x+=p; y+=q;//坐标更新
		Map[x][y]=1;//每一步都标记
	}
	int xx,yy;//表示下一步的方向
	if(p==-1&&q==0) xx=-1,yy=-1;
	else if(p==-1&&q==-1) xx=0,yy=-1;
	else if(p==0&&q==-1) xx=1,yy=-1;
	else if(p==1&&q==-1) xx=1,yy=0;
	else if(p==1&&q==0) xx=1,yy=1;
	else if(p==1&&q==1) xx=0,yy=1;
	else if(p==0&&q==1) xx=-1,yy=1;
	else if(p==-1&&q==1) xx=-1,yy=0;
	dfs(step+1,x,y,xx,yy);//分支1
	
	if(p==-1&&q==0) xx=-1,yy=1;
	else if(p==-1&&q==1) xx=0,yy=1;
	else if(p==0&&q==1) xx=1,yy=1;
	else if(p==1&&q==1) xx=1,yy=0;
	else if(p==1&&q==0) xx=1,yy=-1;
	else if(p==1&&q==-1) xx=0,yy=-1;
	else if(p==0&&q==-1) xx=-1,yy=-1;
	else if(p==-1&&q==-1) xx=-1,yy=0;
	dfs(step+1,x,y,xx,yy);//分支2
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	dfs(1,M,M,-1,0);//注意起始坐标为[M,M]
	for(int i=0;i<=300;i++)
	for(int j=0;j<=300;j++)
	ans+=Map[i][j];//遍历标记表
	printf("%d",ans);
	return 0;
} 
```


---

## 作者：MuYC (赞：0)

## 这道题是个记忆化搜索好题
## 题意
### 首先理解题意上面，我们可以想象为一这是一只只虫子在迁徙，他们的寿命有限，到了一定的时间就会繁殖然后子嗣会继续爬（好像没有目的地，不过没关系）
### 题目大意就是给出了每一层烟花可以持续的时间（我就在这里先说为是每一代虫子可以存活的时间），烟花消散后（寿命耗尽后）就会分裂成两段，这两段就会朝原方向的４５°偏角进发，你可以想象成是它是一个角平分线，直接上图！这就是方向，Ｘ表示的就是烟花散开的地方
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750D/958e71e20888e0f3c92e01fa2be2e012117f122b.png)

### 人工解释是这样的：
↑变成↖＋↗

↓变成↙＋↘

←变成↖＋↙

→变成↗＋↘

## 做法详解
首先我们根据数据范围分析这个虫子最远能到达的地方与起始点的曼哈顿距离肯定小于等于１５０，所以说我们就可以开一个５００＊５００的数组来记录虫子有没有经过这个点，就ＯＫ了，然后肯定我们初始这只祖先虫子的坐标肯定是位于地图中央的，这样比较好！

１．首先可以自行脑补设置数字代替符合↑↓←→↖↙↗↘（我是用１～８实现的）

２．再者，进行深搜模拟过程，根据模拟进行这个过程就可以　　　　　　　　　

３．开一个四维数组记录状态，出生坐标[ｘ，ｙ]，这只虫子的寿命（也就是第几代虫子），它将去往的方向　　　　　　　　　　　　　　　　　　　　　　　　

４．进行记忆化剪枝（你可以想象一下，两只寿命一样长的虫子在同一个地方出生，向同一个方向去，走的速度都是一样的，他们走过的路线一样）

### 这是本蒟蒻考试的题目，本来就是想打暴力过几个点拿点分的，于是我就开始广搜．（蒟蒻的脑残想法），然后全部ＲＥ０分，数据良心！，实际上应该深搜，这道题空间吃紧，很显然应该用时间换空间！
### 细节部分：
每次虫子繁殖的出生地是对于先辈的死亡地朝向它将移动的方向移动一格，例如第一只虫子死后应该繁殖出来的虫子在他左上以及右上，相对于第一只虫子的位置与那两只繁殖出来的虫子需要行进的方向一致，每只虫子的寿命需要算上出生格！

## ＣＯＤＥ

讲一讲广搜思路：存下每一只虫子，然后模拟它的运动，存在一个队列中，然后扩展，每次繁殖后就加上一只

```cpp
#include <bits/stdc++.h>
using namespace std;
int book[1050][1050];
int t[35];
struct warm{int x,y,f,t;}c[2097155];
int total=0,head=0,res=0,flag=0;
int main(){
    int n;
    cin>>n;
    for (int i = 1 ; i <= n ; i ++)cin>>t[i],t[i]--;
    total++,c[total].x=500,c[total].y=500,c[total].f=1,c[total].t=1;
    while(head < total){
        head++;
        int tim,x,y,f;
        tim=t[c[head].t],x=c[head].x,y=c[head].y,f=c[head].f;
        book[x][y]=1;
        while(tim > 0){
            if(f == 1)x--;if(f == 2)x++;
            if(f == 3)y--;if(f == 4)y++;
            if(f == 5)x--,y--;
            if(f == 6)x++,y--;
            if(f == 7)x--,y++;
            if(f == 8)x++,y++;
            book[x][y]=1;
            tim--;
        }
        if(c[head].t < n){
            if(f==1){
                total++;
                c[total].x=x-1,c[total].y=y-1,c[total].f=5,c[total].t=c[head].t+1;//5
                c[total+1].x=x-1,c[total+1].y=y+1,c[total+1].f=7,c[total+1].t=c[total].t;//7
                total++;
            }
            if(f==2){
                total++;
                c[total].x=x+1,c[total].y=y-1,c[total].f=6,c[total].t=c[head].t+1;//6
                c[total+1].x=x+1,c[total+1].y=y+1,c[total+1].f=8,c[total+1].t=c[total].t;//8
                total++;
            }
            if(f==3){
                total++;
                c[total].x=x-1,c[total].y=y-1,c[total].f=5,c[total].t=c[head].t+1;//5
                c[total+1].x=x+1,c[total+1].y=y-1,c[total+1].f=6,c[total+1].t=c[total].t;//6
                total++;
            }
            if(f==4){
                total++;
                c[total].x=x+1,c[total].y=y+1,c[total].f=8,c[total].t=c[head].t+1;
                c[total+1].x=x-1,c[total+1].y=y+1,c[total+1].f=7,c[total+1].t=c[total].t;//7
                total++;
            }
            if(f==5){
                total++;
                c[total].y=y-1,c[total].x=x,c[total].f=3,c[total].t=c[head].t+1;//←
                c[total+1].x=x-1,c[total+1].y=y,c[total+1].f=1,c[total+1].t=c[total].t;//↑
                total++;
            }
            if(f==6){
                total++;
                c[total].y=y-1,c[total].x=x,c[total].f=3,c[total].t=c[head].t+1;//←
                c[total+1].x=x+1,c[total+1].y=y,c[total+1].f=2,c[total+1].t=c[total].t;//↓
                total++;
            }
            if(f==7){
                total++;
                c[total].y=y+1,c[total].x=x,c[total].f=4,c[total].t=c[head].t+1;//→
                c[total+1].x=x-1,c[total+1].y=y,c[total+1].f=1,c[total+1].t=c[total].t;//↑
                total++;
            } 
            if(f==8){
                total++;
                c[total].y=y+1,c[total].x=x,c[total].f=4,c[total].t=c[head].t+1;//→
                c[total+1].x=x+1,c[total+1].y=y,c[total+1].f=2,c[total+1].t=c[total].t;//↓
                total++;
            }        
        }
    }
    for (int i = 0 ; i <= 1024 ; i ++){
        for (int j = 0 ; j <= 1024 ; j ++)
        if( book[i][j] == 1)res++;
    }
    cout<<res;
    return 0;
}
//↑１
//↓２
//←３
//→４
//↖５
//↙６
//↗７
//↘８
```

然后是裸的深搜，全部ＴＬＥ，０分
```cpp
#include <bits/stdc++.h>
using namespace std;
int book[1050][1050];
int t[35],n;
int dfs(int x,int y,int f,int t1){
    int tim=t[t1];
    book[x][y]=1;
    while(tim){
            if(f == 1)x--;if(f == 2)x++;
            if(f == 3)y--;if(f == 4)y++;
            if(f == 5)x--,y--;
            if(f == 6)x++,y--;
            if(f == 7)x--,y++;
            if(f == 8)x++,y++;
            book[x][y]=1;
            tim--;
        }
    if(t1 +1 <= n){
      if(f == 1)dfs(x-1,y-1,5,t1+1),dfs(x-1,y+1,7,t1+1);
      if(f == 2)dfs(x+1,y-1,6,t1+1),dfs(x+1,y+1,8,t1+1);
      if(f == 3)dfs(x-1,y-1,5,t1+1),dfs(x+1,y-1,6,t1+1);
      if(f == 4)dfs(x-1,y+1,7,t1+1),dfs(x+1,y+1,8,t1+1);
      if(f == 5)dfs(x,y-1,3,t1+1),dfs(x-1,y,1,t1+1);
      if(f == 6)dfs(x,y-1,3,t1+1),dfs(x+1,y,1,t1+1);
      if(f == 7)dfs(x,y+1,4,t1+1),dfs(x-1,y,1,t1+1);
      if(f == 8)dfs(x,y+1,4,t1+1),dfs(x+1,y,1,t1+1);
    }
}
int total=0,head=0,res=0,flag=0;
int main(){
    cin>>n;
    for (int i = 1 ; i <= n ; i ++)cin>>t[i],t[i]--;
    dfs(500,500,1,1);
    for (int i = 0 ; i <= 1024 ; i ++){
        for (int j = 0 ; j <= 1024 ; j ++)
        if( book[i][j] == 1)res++;
    }
    cout<<res;
    return 0;
}
//↑１
//↓２
//←３
//→４
//↖５
//↙６
//↗７
//↘８
```

以上内容可以自行省略．

### AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int book[1002][1002];
bool b[1000][1000][10][31];
int t[35],n,total=0;
int dfs(int x,int y,int f,int t1){
    int tim=t[t1];
    book[x][y]=1;
    if(b[x][y][f][t1]==1)return 0;
    b[x][y][f][t1]=1;
    while(tim){
            if(f == 1)x--;if(f == 2)x++;
            if(f == 3)y--;if(f == 4)y++;
            if(f == 5)x--,y--;
            if(f == 6)x++,y--;
            if(f == 7)x--,y++;
            if(f == 8)x++,y++;
            book[x][y]=1;
            tim--;
     }
    if(t1 +1 <= n){
      if(f == 1)dfs(x-1,y-1,5,t1+1),dfs(x-1,y+1,7,t1+1);
      if(f == 2)dfs(x+1,y-1,6,t1+1),dfs(x+1,y+1,8,t1+1);
      if(f == 3)dfs(x-1,y-1,5,t1+1),dfs(x+1,y-1,6,t1+1);
      if(f == 4)dfs(x-1,y+1,7,t1+1),dfs(x+1,y+1,8,t1+1);
      if(f == 5)dfs(x,y-1,3,t1+1),dfs(x-1,y,1,t1+1);
      if(f == 6)dfs(x,y-1,3,t1+1),dfs(x+1,y,2,t1+1);
      if(f == 7)dfs(x,y+1,4,t1+1),dfs(x-1,y,1,t1+1);
      if(f == 8)dfs(x,y+1,4,t1+1),dfs(x+1,y,2,t1+1);
    }
}
int res=0;
int main(){
    cin>>n;
    for (int i = 1 ; i <= n ; i ++)cin>>t[i],t[i]--;
    dfs(500,500,1,1);
    for (int i = 0 ; i <= 1000 ; i ++){
        for (int j = 0 ; j <= 1000 ; j ++)
        if( book[i][j] == 1)res++;
    }
    cout<<res;
    return 0;
}
//↑１
//↓２
//←３
//→４
//↖５
//↙６
//↗７
//↘８
```

## 总结
记忆化搜索实际上就是类似于动态规划的刷表法一样，它通过记录下已有的状态，对于以后如果出现此种相同已经出现过的状态时，就可以直接跳过，然后进行刷新



---

