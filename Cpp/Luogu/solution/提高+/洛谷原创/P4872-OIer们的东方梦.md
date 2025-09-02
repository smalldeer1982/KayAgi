# OIer们的东方梦

## 题目背景

**#11,#12 两组 Hack 数据由 uid=20285 提供**

OIer 们做~~魂魄妖~~梦都想去幻想乡玩一下。这一次，他们在睡~~古明地~~觉时在梦中穿越去了幻想乡，幻想乡有很多的少(ju)女(ruo)，但是他们被~~老太婆~~少女的美色~~和蒟蒻的美味~~所吸引，在幻想乡中迷失了方向。

勇敢的~~死肥宅~~少年啊，现在你手里有一份幻想乡人间之里的地图，你知道 OIer 们的位置，你可以远程给OIer们传递信息，请你带领迷路的 OIer 们走进回到现实生活的祭坛吧！

## 题目描述

给你一个 $N\times M$ 的地图，如图所示：              
```
5400000S01     
1111101101     
000003X301      
3111111101     
E000300031      
1111X30001     
```

其中有很多稀奇古怪的东西：  
     
* $S$ 表示出发点，$E$ 表示终点。      
* $0$ 表示空地，你想怎么走就怎么走，走一格需要 $1s$。            
* $1$ 表示墙，你无法通行（~~除非你受到了**风神少女**的庇护~~）。   
* $2$ 表示小妖怪，你需要 $3s$ 的时间去消灭小妖怪，才能经过该位置。（PS: 妖怪被消灭后只要离开当前格子立刻复活）  
* $3$ 表示大妖怪，你需要 $8s$ 的时间去消灭大妖怪，才能经过该位置。   
* $4$ 表示太阳花田，到达该位置可以获得太阳花，获得太阳花后遇到妖怪时可**直接**通过该妖怪的位置。  
* $5$ 表示楼观剑（科普君：楼观剑，英文名 $Louguan\ is\ very\ jian$，是妖怪做的剑，楼观剑斩不断的东西几乎没有)，到达该位置可以花费 $5s$ 获得它，获得它后可以砍墙砍妖怪将其变成空地（当然也可以不砍，砍墙砍妖怪不需要时间，楼观剑可以一直使用**不会损坏**，有了楼观剑依然可以使用隙间，但是楼观剑不能砍隙间~~和一点用都没有的麻薯，麻薯妖梦UUZ是一家嘛~~）       
* $M$ 表示麻薯（是 $mashu$ 不是 $mafu$~~不知道麻薯是什么的一把楼观剑给你砍过来~~)，碰到麻薯后你可以把它吃了(路人甲：那你为什么还要加这个东西? 出题人：有 $S$ 肯定要有 $M$ 啊。路人乙：我就是死外边，从隙间中跳下去，也不会吃麻薯！嗯~真香！）            
* $X$ 表示紫妈的隙间，碰到隙间后会传送至其他的任意一个隙间(数据**不**保证只有 0 或 2 个隙间，**就是说可以有很多隙间乱传**)，每次传送耗时 $1s$。(经过当前格子时可以不经过隙间)       
      
答案输出 OIer 们到达终点所需最短时间。如果无法到达，输出 "We want to live in the TouHou World forever"。     
翻译：此生无悔入东方，来世~~睡遍~~愿生幻想乡。   
    
**温馨提示：不排除存在可以往回走等稀奇古怪的最优走法**

## 说明/提示

对于 $30\%$ 的数据，$1\leq N,M\leq 50$。       
对于 $50\%$ 的数据，$1\leq N,M\leq 100$。       
对于 $100\%$ 的数据，$1\leq N,M\leq 1000$。

保证有一组数据答案为 "We want to live in the TouHou World forever"，数据有梯度。

### 样例解释

**样例 1**：在 $7s$ 时到达楼观剑，在 $12s$ 时获得楼观剑，一路向下砍到达终点。                   
**样例 2**：在 $10s$ 时到达 $(3,3)$，在 $32s$ 时到达$(3,10)$，向上进入隙间后到达终点。          
**样例 3**：这个就不用解释了吧(出题人放飞自我)。

## 样例 #1

### 输入

```
6 10
5400000S01
1111101101
000003X301
3111111101
E000300031
1111X30001```

### 输出

```
16```

## 样例 #2

### 输入

```
5 10
S23323323X
2032332333
1202202202
1111111111
11111111XE```

### 输出

```
44```

## 样例 #3

### 输入

```
9 10
SX1X0X1X1X
2332332333
5205205200
XXXXXXXXXX
2222222222
3333333333
3333333333
XXXXXXXXXX
XXXXXXXXXE```

### 输出

```
3```

# 题解

## 作者：Flandre_495 (赞：20)

调了一天，终于过了~写篇题解纪念一下~

#### ~~感觉我的代码比起其他人的可读性要高许多。。。~~

感谢disangan233提供神仙题面，感谢上海爱丽丝幻乐团提供信仰，~~能有信心磕这道题的估计大部分是車万党吧。。。~~

#### 废话不多说：我们先来分析一下题：

这题细节很多，过样例却WA掉的可以看看代码中的具体注释。

我采用了优先队列BFS的方法，于是每个点有几个属性：坐标，dis值，是否~~抢剑~~，是否~~偷花~~。

我们再定义一个NB值，什么都没有时NB=0，有花时NB=1，有剑时NB=2.

#### 分析每个字符：


```
0,1,2,3都好说，就是NB值不一样时距离不同。

4:偷花不需要时间，可以直接修改属性。

5:注意可以不要剑，所以要考虑要和不要两种情况。

M:关于麻薯。。。藏起来就好，别让幽幽子看到。

X:最麻烦的一个，可以满地图乱窜，每次都枚举复杂度是不行的，但是你发现每个NB值状态下最多只用传送一次就行，没必要传来传去，直接传到最后一次的位置不就行了。除非你专程去偷花或抢剑，那样会使你的NB值增加，所以每个NB值下都可以考虑传送，传送过就可以忽略X了。
```

那就看代码吧：具体操作都在代码里了~

~~自我感觉可读性良好。。。~~


```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define QWQ cout<<"QwQ"<<endl;
#define ll long long 
#include<vector>
#include<queue>
#include<stack>
#include<map>
using namespace std;
const int N=101010;
const int qwq=303030;
const int inf=0x3f3f3f3f;
int n,m;
int g,h,s,t;                         //起点和终点的坐标 
char z[1234][1234];
int dis[1234][1234][3];              //每个NB值状态下的dis值 
bool bayunzi[4];                     //在这个NB值状态下是否用过间隙 
int ff[] = {1,0,0,-1};
int gg[] = {0,1,-1,0};               //4个方向 
struct E{
	int d;
	int i,j; 
	bool lou,hua;                    //lou：是否有楼观剑，hua：是否抢过花 
};
priority_queue <E> q;                //优先队列，对d优先 
inline bool operator < (E aa,E bb) { return aa.d > bb.d; }

inline int getNB(E v) {             //获得NB值 
	if(v.lou) return 2;
	if(v.hua) return 1;
	return 0;
}

inline void check(E v) {            //更新dis值，并压入队列 
	int NB = getNB(v);
	if(v.d >= dis[v.i][v.j][NB]) return ;
	dis[v.i][v.j][NB] = v.d;     q.push(v);
}

void jian_xi(E u) {                     //从间隙往别的间隙走 
	int NB = getNB(u);
	if(bayunzi[NB]) return ; bayunzi[NB] = 1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) {
		if(z[i][j]!='X') continue;
		E v = (E){u.d+1, i, j, u.lou, u.hua};
		check(v);
	}
}

int BFS() {
	memset(dis,0x3f,sizeof(dis));
	q.push( (E){0,g,h,0,0} );
	while(!q.empty()) {
		E u = q.top(); q.pop();
		if(u.i==s && u.j==t) return u.d;    //终于到终点了！
		for(int k=0;k<4;k++) {              //4个方向 
			E v; 
			v.lou = u.lou; 
			v.hua = u.hua;
			v.i = u.i + ff[k];
			v.j = u.j + gg[k];             //下一个点的信息 
			int NB = getNB(v);
			if(v.i<0 || v.j<0 || v.i>n || v.j>m) continue;  //边界 
			int cl = z[v.i][v.j];           
			if(cl=='1') {
				v.d = u.d + 1;
				if(NB==2) check(v);         //楼观剑砍墙 
			}
			if(cl=='0' || cl=='X') {        //注意：‘X’是可以穿的！
				v.d = u.d + 1;
				check(v);
			}
			if(cl=='2') {
				if(NB!=0) v.d = u.d + 1;
				else      v.d = u.d + 4;    //不同NB值状态下距离不同。 
				check(v);
			}
			if(cl=='3') {
				if(NB!=0) v.d = u.d + 1;
				else      v.d = u.d + 9; 
				check(v);
			}
			if(cl=='4') {
				v.d = u.d + 1; v.hua = 1;   //偷花。
				check(v);
			}
			if(cl=='5') {                   //注意楼观剑要check两次，因为可以不选。 
				v.d = u.d + 1; 
				check(v); 
				if(!v.lou) v.lou = 1, v.d += 5;           //获得需5秒 
				check(v);
			}
		}
		if(z[u.i][u.j]=='X') jian_xi(u);                  //从间隙飞 
	}
	return -1;
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",z[i]+1);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) {
		if(z[i][j]=='M') z[i][j] = '0';                  //把麻薯变成0藏起来，别让幽幽子吃了。 
		if(z[i][j]=='S') g = i, h = j, z[i][j] = '0';    //注意起点是可以走好几次的，它的属性改成0。
		if(z[i][j]=='E') s = i, t = j, z[i][j] = '0';    
	}
	int ans = BFS();
	if(ans!=-1) printf("%d",ans);
	else printf("We want to live in the TouHou World forever");    //此生无悔入东方，来世炸了幻想乡。 
	return 0;
}

```

看起来长，其实很瘦的，压下行就短了:)

---

## 作者：disangan233 (赞：9)

这个题就是水题一道，以下是两种主流做法： 

### Sol 1：BFS

首先对于一般的 BFS 来说，它们都是要求输出步数(或者输出时间，且每走一步需要 $1s$)。

但是这个题目中很多的特殊位置，比如大妖怪小妖怪等，进过当前格子时需花费时间。如果仅仅按照一般的队列去 BFS 的话，无法保证最到达终点的情况就是时间最优的情况。

所以显然此题不能用一般的 BFS 去做不然会 WA。(且会 TLE)

根据上面我们可以在普通 BFS 的框架中添加优化，因为普通 BFS 是使用的普通队列，然而想要保证时间最优解的话必须让每一次的队首为当前队列中时间最小的情况。

#### 1：每次BFS前sort一次  

显然这样是不够优秀的，因为这种疯狂 $sort$ 的算法的时间复杂度在最坏的条件下会达到 $O(n^2 m^2\log (nm))$。

#### 2：用map实现判重，如果有不一样的时间入队就sort一次

显然这样还是不够优秀，这种算法的时间复杂度会达到 $O(n^2m^2 \log^2(nm))$。

~~所以这个优化没什么用处，反而提高了复杂度。~~   

#### 3：用优先队列替代一般队列  

采用 `priority_queue` 可以使代码时间复杂度降低至 $O(nmlog(nm))$，可以AC本题。  

PS：尽管此题 $n\times m\leq 10^6$，但是 $O(nm\log (nm))$ 的复杂度仅仅为最坏情况 (懒得卡)，可以 AC 此题。 

优先队列参考代码：  

```cpp
struct did{
    int x,y,f,l,t;//f:太阳花 l:楼观剑 t:时间    
    bool operator <(did a) const
    {
    	return t<a.t;
    }
    bool operator >(did a) const
    {
    	return t>a.t;
    }
};
priority_queue<did,vector<did>,greater<did> >q;
```

考虑如何在 BFS 中判重。仔细阅读题目即可发现，到达每一个点最多有 4 种情况(楼观剑和太阳花)，且楼观剑的优先级大于太阳花，所以可以处理为 3种情况。我们可以用一个数组 `tag[maxn][maxm][2][2]` 或者 `tag[maxn][maxm][3]` 来表示每一种情况。


### Sol2：分层图最短路

上面的 **Sol1**等效替代一下就是堆优化Dijkstra。

采用分层图+堆优化Dijkstra也可 AC 此题，代码时间复杂度同上为$O(nm\log(nm))$。  

### AC代码 (BFS+优先队列)

因为原来的 code 太丑，已经于 2019/09/06 略微修(ya)改(hang)。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register int
char mp[1005][1005];
int n,m,cnt,ex,ey,ans=-1;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0},vis[1005][1005];
struct did{
    int x,y,f,l,t;
    bool operator <(did a) const {return t>a.t;}
};
priority_queue<did>q;
int tag[1005][1005][2][2];
struct diddd{int x,y;}poi[2000005];
void bfs()
{
    re js=0;
    while(!q.empty())
    {
        re nx=q.top().x,ny=q.top().y,nt=q.top().t,nf=q.top().f,nl=q.top().l;
        js++;q.pop();
        if(nx==ex&&ny==ey) return ans=nt,void();
        for(re i=0;i<=3;i++)
        {
        	#define nmp mp[xx][yy]
        	#define ntag tag[xx][yy][lll][ff]
            re xx=nx+dx[i],yy=ny+dy[i],tt=nt+1,ff=nf,lll=nl,bj=0,chen_zhe=0;
            if(!(xx>=1&&xx<=n&&yy>=1&&yy<=m)) continue;
            if((nl&&nmp!='X')||((nmp=='2'||nmp=='3')&&nf)||nmp=='0'||nmp=='E'||nmp=='S') bj=1;
            else if(nmp=='4') bj=ff=1;
            else if(nmp=='5') tt+=5,bj=lll=1,chen_zhe=1;
            else if(nmp=='2') tt+=3,bj=1;
            else if(nmp=='3') tt+=8,bj=1;
            else if(nmp=='X'&&!ntag) bj=2;
            if(bj&&!ntag) q.push(did{xx,yy,ff,lll,tt}),ntag=1;
            if(chen_zhe&&!tag[xx][yy][0][ff]) q.push(did{xx,yy,ff,0,tt-5}),tag[xx][yy][0][ff]=1;
			if(bj==2)
            {
                tt++;
                for(re j=1;j<=cnt;j++) if(!(poi[j].x==xx&&poi[j].y==yy)&&!tag[poi[j].x][poi[j].y][lll][ff])
                q.push(did{poi[j].x,poi[j].y,ff,lll,tt}),tag[poi[j].x][poi[j].y][lll][ff]=1;
			}
        }
    }
}
int main()
{
    scanf("%d %d",&n,&m);
    for(re i=1;i<=n;i++) for(re j=1;j<=m;j++)
    {
        mp[i][j]=getchar();
        while(!isdigit(mp[i][j])&&!isalpha(mp[i][j])) mp[i][j]=getchar();
        switch(mp[i][j])
        {
            case 'S': q.push(did{i,j,0,0,0});break;
            case 'E': ex=i;ey=j;break;
            case 'X': poi[++cnt].x=i;poi[cnt].y=j;break;
        }
    }
    bfs();
    if(ans!=-1) cout<<ans<<endl;
    else cout<<"We want to live in the TouHou World forever"<<endl;
    return 0;
}
```  

### 蒟蒻两次被hack的地方  
* 楼观剑可以不取，起点可以经过多次。  


---

## 作者：古明地觉 (赞：6)

# 一句话：分层图最短路

   先将原图复制为三层，第一层为原图，第二层为太阳花图，将所有2，3，4改为0。
第三层为lg剑图，将所有1，2，3，4，5改为0。

   接下来从第一层起点开始跑最短路，当遇到4时将该点第二层压入优先队列，5则将第三层压入，隙间则比较当前dis是否小于该层记录的值，然后将所有X压入队列，然后向上下左右扩展。当x，y等于终点xy时（不管在几层），输出结果结束程序。同时注意边界。

AC代码：
```cpp
#include<bits/stdc++.h>
#define INF 707406378
using namespace std;
struct node{
	short x,y;
	int sum;
	char cn;
};
bool operator>(const node&l,const node&r){
	return l.sum>r.sum;
}
void readchar(char &c){
	c=getchar(); 
	while(c==' '||c=='\n'||c=='\r')c=getchar();
} 
vector<pair<short,short> >vx;
int m,n;
int dis[1010][1010][3];
char s[1010][1010][3];
int xijian[3]; 
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int ex,ey,sx,sy;
bool vis[1010][1010][3];
priority_queue<node,deque<node>,greater<node> >que;
int main(){
	memset(xijian,127/3,sizeof(xijian));
	memset(dis,127/3,sizeof(dis));
	//cout<<dis[1][1][1];
	memset(s,'U',sizeof(s));
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			readchar(s[i][j][0]);
			if(s[i][j][0]=='S')sx=i,sy=j;
			if(s[i][j][0]=='E')ex=i,ey=j;
			if(s[i][j][0]=='X')vx.push_back(make_pair(i,j));
			if(s[i][j][0]=='M')s[i][j][0]=0;
			switch(s[i][j][0]){
				case '2':case '3':case '4':s[i][j][1]=0;break;
				default:s[i][j][1]=s[i][j][0];break;
			}
			switch(s[i][j][1]){
				case '1':case '5':s[i][j][2]=0;break;
				default:s[i][j][2]=s[i][j][1];break;
			}
		}
	
	que.push(node{sx,sy,0,0});
	while(!que.empty()){
		node x=que.top();
		que.pop();
		//cerr<<que.size()<<endl;
		if(x.x==ex&&x.y==ey){
			cout<<x.sum<<endl;
			return 0;
		}
		if(vis[x.x][x.y][x.cn])continue;
		vis[x.x][x.y][x.cn]=1;
		dis[x.x][x.y][x.cn]=x.sum;
		if(s[x.x][x.y][x.cn]=='X'&&xijian[x.cn]>x.sum){
			xijian[x.cn]=x.sum;
			for(int i=0;i<vx.size();++i){
				//cerr<<vx[i].first<<" "<<vx[i].second<<endl;
				if(!vis[vx[i].first][vx[i].second][x.cn])
					que.push(node{vx[i].first,vx[i].second,x.sum+1,x.cn});
			}
			//cerr<<endl;
		}
		if(s[x.x][x.y][x.cn]=='4'){
			que.push(node{x.x,x.y,x.sum,1});
		}
		if(s[x.x][x.y][x.cn]=='5'){
			que.push(node{x.x,x.y,x.sum+5,2});
		}
		for(int i=0;i<4;++i){
			short cx=x.x+dx[i],cy=x.y+dy[i];
			if(vis[cx][cy][x.cn]||s[cx][cy][x.cn]=='U')continue;
			switch(s[cx][cy][x.cn]){
				case '1':break;
				case '2':que.push(node{cx,cy,x.sum+4,x.cn});break;
				case '3':que.push(node{cx,cy,x.sum+9,x.cn});break;
				default:que.push(node{cx,cy,x.sum+1,x.cn});break;
			}
		}
		
	}
	cout<<"We want to live in the TouHou World forever";
	return 0;
}

```
感谢**上海爱丽丝幻乐团**提供信仰加成。

---

## 作者：Expert_Dream (赞：2)

## 前言
一个下午，一个晚上，一个早上，可以算是一天了吧，终于调出了这道题，纪念一下吧！！！

[食用更佳](https://www.luogu.com.cn/blog/gsczl71/solution-p4872)。

这道题其实就是一道简简单单的 BFS 模（du）板（liu）题。

说难不难，简单不简单，虽然没有难的算法，但是就是码量一百多行，比较难调。

题目难度绿，思维难度橙，代码难度蓝。真是个~~绝世好题~~。
## 题目意思

就是一个最短路问题，开个优先队列跑 BFS。有很多种路，需要逐个 ```if``` 判断过去。

为了后面讲解，我们设置一个 ```id``` 代表拿的太阳花或者剑的状态（具体见代码）。

如果你逐个查找每个传送门会卡成 $O(N^4)$。如果我们要去间隙传送门，那么必然是为了一次性传送，或者传去其他地方拿个太阳花或者剑之类的。所以这样暴力的算法就会使其有可能会从这个传送门跳到另一个传送门，然后什么东西也没拿就跳回又另一个传送门。然后我们会发现因为你每次到的都是 ```step``` 最小的点，所以只要你有一次跳到了这个点传送门，那么在当前的 ```id``` 下乱跳间隙的 ```step``` 是最优的，所以代码中再开一个 ```vis2``` 数组来表示 ```id``` 下是否记录了这些传送门的点。因为 ```id``` 最多是 $3$，是个小常数，可以忽略，因此复杂度降到 $O(N^2)$。

## 注意事项

本题有很多细节需要注意。

- BFS 开始 ```vis``` 数组没有初始化起点（一般人应该也不会有这个问题）~~但我经常这样~~。
- ```X```、```S```、```E```在判断的时候是相当于空地的，是可以直接走过的，不要忽略。
- 重载函数别写错了。

### 本人犯的最大错误
因为整个程序都是依靠着优先队列实现最优解的保持，但是由于本人结构体重载函数学的不好，所以把符号写反了 ~~（尽管嘲讽~~。

接下来讲一下结构体重载函数的写法。
```cpp
struct data{
	int x,y;
}a[N];
```
以上是一个结构体标准写法。如果我们想对 ```a``` 排序，按照 ```x``` 从小到大排序，那么我们可以写一个 ```cmp``` 函数。
```cpp
bool cmp(data a,data b) {
	return a.x<b.x;
}
```
但是优先队列等无法写自定义函数的时候，就得用到结构体重载函数，就是在结构体内部定义函数。下面介绍其中一种写法。
```cpp
struct data{
	int x,y;
   friend bool operator<(const struct data &a,const struct data &b){
		return a.step > b.step;
	}
}a[N];

```
反正 ```friend``` 开头那一行就背下来就好了，~~虽然我不知道为什么~~。就是觉 C++ 创始人很奇怪，这还要加 ```const```，```struct```…… 注意了，还要加取地址符。

感觉很奇怪！

然后函数里的内容就要跟 ```cmp``` 写法基本一样了，但是重点是：**他的符号跟 ```cmp``` 是反的！**，所以从小到大排序要用大于符号！~~（我就挂在这了）~~。

最后，附上 **AC code**：~~（注释齐全，自认马蜂良好，容易理解）~~。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define endl "\n"
using namespace std;
const int N = 1005;
int n,m;
string c[N];
int vis[N][N][3],vis2[3];
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
struct node{
	int x,y,step;
	bool sun;//是否遇到过太阳花
	bool jian;//是否有楼观剑
	friend bool operator<(const struct node &a,const struct node &b){
		return a.step > b.step;
	}
};
struct data{
	int x,y;
}s[N*N];int si;
int bx,by,ex,ey;//设置起点和终点
bool check(int x,int y){//判断边界情况
	if(x<1||x>n||y<1||y>m)return true;
	return false;
}
int getid(node x){
	if(x.jian) return 2;
	if(x.sun) return 1;
	return 0;
}
int main(){
	memset(vis,0x3f,sizeof vis);
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		cin >> c[i];
		c[i]=' '+c[i];
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(c[i][j]=='M')c[i][j]='0';//麻薯都说吃了没用，还不如不吃！
			else if(c[i][j]=='S')bx=i,by=j,c[i][j]='0';
			else if(c[i][j]=='E')ex=i,ey=j,c[i][j]='0';
			else if(c[i][j]=='X')s[++si].x=i,s[si].y=j;
		}
	}
	priority_queue<node> q;
	vis[bx][by][0]=0;
	q.push({bx,by,0,0,0});
//	cout<<bx<<" "<<by<<endl;
	while(!q.empty()){
		node f=q.top();
		q.pop();
//		cout<<f.x << " "<< f.y<<endl;
		if(f.x==ex && f.y==ey) {
			cout<<f.step;
			return 0;
		}
		int nowid = getid(f);
		for(int i = 0 ;i < 4;i++){
			int xx=f.x + dx[i];
			int yy=f.y + dy[i];
			if(check(xx,yy)) continue;
			if(c[xx][yy] == '0' || c[xx][yy]=='X'){//是空地
				if(vis[xx][yy][nowid] > f.step+1){//如果比最短路径短，那么就走
					vis[xx][yy][nowid] = f.step+1;
					q.push({xx,yy,f.step+1,f.sun,f.jian});
				}
			}else if(c[xx][yy]=='1'){//是墙
				if(f.jian){//有jian才能走
					if(vis[xx][yy][nowid] > f.step+1){
						vis[xx][yy][nowid] = f.step+1;
						q.push({xx,yy,f.step+1,f.sun,f.jian});
					}	
				}
			}else if(c[xx][yy]=='2'){//是little 妖怪
				if(f.jian||f.sun){//有剑或太阳花，把你斩了
					if(vis[xx][yy][nowid] > f.step+1){
						vis[xx][yy][nowid] = f.step+1;
						q.push({xx,yy,f.step+1,f.sun,f.jian});
					}	
				}else{//没剑，花3s把你干了，再加上1s移动时间
					if(vis[xx][yy][nowid] > f.step+4){
						vis[xx][yy][nowid] = f.step+4;
						q.push({xx,yy,f.step+4,f.sun,f.jian});
					}						
				}		
			}else if(c[xx][yy]=='3'){//big 妖怪
				if(f.jian||f.sun){//有剑或太阳花，把你斩了
					if(vis[xx][yy][nowid] > f.step+1){
						vis[xx][yy][nowid] = f.step+1;
						q.push({xx,yy,f.step+1,f.sun,f.jian});
					}	
				}else{//没剑，花8s把你干了，再加上1s移动时间
					if(vis[xx][yy][nowid] > f.step+9){
						vis[xx][yy][nowid] = f.step+9;
						q.push({xx,yy,f.step+9,f.sun,f.jian});
					}						
				}		
			}else if(c[xx][yy]=='4'){//太阳花
				if(vis[xx][yy][max(1,nowid)] > f.step+1){
					vis[xx][yy][max(1,nowid)] = f.step+1;
					q.push({xx,yy,f.step+1,1,f.jian});
				}
			}else if(c[xx][yy]=='5'){//是jian
				if(vis[xx][yy][2] > f.step+1){
					vis[xx][yy][2] = f.step+1;
					q.push({xx,yy,f.step+1,f.sun,f.jian});
				}
				if(vis[xx][yy][nowid] > f.step+6){
					vis[xx][yy][nowid] = f.step+6;
					q.push({xx,yy,f.step+6,f.sun,1});
				}								
			}
		}
		int xx=f.x,yy=f.y;
		if(c[xx][yy]=='X'){
			if(vis2[getid(f)])continue;vis2[getid(f)]=1;
			for(int i = 1;i <= si;i++){
				if(s[i].x==xx&&s[i].y==yy) continue;
				if(vis[s[i].x][s[i].y][nowid] > f.step+1){
					vis[s[i].x][s[i].y][nowid] = f.step+1;
					q.push({s[i].x,s[i].y,f.step+1,f.sun,f.jian});
				}					
			}
		}
	}
	cout<<"We want to live in the TouHou World forever";
	return 0;
}
```

[广告](https://www.luogu.com.cn/blog/gsczl71/)。

---

## 作者：chenxinyang2006 (赞：2)

~~只有两篇题解，我也来水一下~~

首先，不要被什么往回走给骗了，如果往回走是最优解，那么这次肯定是专程去拿楼观剑/太阳花。

所以把vis开三维，分别表示有剑时/有花时/都没有时每个点是否访问过。这样这个最大的难点就解决了

另外，因为每次隙间传送到达的点相同，所以只有在拿到新道具的时候有传送的必要，如果一碰到隙间就传应该会被卡

最后，楼观剑可以不拿,不要把楼观剑覆盖成太阳花


code：
```cpp
#include <cstdio>
#include <queue>
using namespace std;
int n,m,sx,sy;
char map[1005][1005];
char str[1005];
int vis[3][1005][1005];
int gx[1000005],gy[1000005],it[3],cnt;
int mx[4] = {0,1,0,-1};
int my[4] = {1,0,-1,0};

struct node{
	int x,y,steps,lv;
	bool operator <( const node &x )const{
        return x.steps < steps;
    }
};

priority_queue <node> que;

void bfs(){
	node pre,nex;
	pre.x = sx;
	pre.y = sy;
	vis[0][sx][sy] = 0;
	pre.steps = 0;
	pre.lv = 0;
	que.push(pre);
	while(!que.empty()){
		pre = que.top();
		que.pop();
		for(int i = 0;i < 4;i++){
			nex.x = pre.x + mx[i];
			nex.y = pre.y + my[i];
			nex.steps = pre.steps + 1;
			nex.lv = pre.lv;
			if(nex.x < 1 || nex.x > n || nex.y < 1 || nex.y > m){
				continue;
			}
            if(map[nex.x][nex.y] == '1' && nex.lv != 2){
				continue;
			}else if(map[nex.x][nex.y] == '2' && nex.lv == 0){
				nex.steps += 3;
			}else if(map[nex.x][nex.y] == '3' && nex.lv == 0){
				nex.steps += 8;
			}else if(map[nex.x][nex.y] == '4'){
				nex.lv = max(nex.lv,1);
			}else if(map[nex.x][nex.y] == '5' && nex.lv < 2){
				que.push(nex);
				nex.lv = 2;
				nex.steps += 5;
			}else if(map[nex.x][nex.y] == 'E'){
				printf("%d\n",nex.steps);
				return;
			}
			if(!vis[nex.lv][nex.x][nex.y]){
				vis[nex.lv][nex.x][nex.y] = 1;
				que.push(nex);
			}
			if(map[nex.x][nex.y] == 'X' && it[nex.lv] == 0){
				it[nex.lv] = 1;
				nex.steps++;
				for(int i = 1;i <= cnt;i++){
					nex.x = gx[i];
					nex.y = gy[i];
					if(!vis[nex.lv][nex.x][nex.y]){
						vis[nex.lv][nex.x][nex.y] = 1;
						que.push(nex);
					}
				}
			}
		}
	}
	printf("We want to live in the TouHou World forever\n");
}


int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%s",&map[i][1]);
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(map[i][j] == 'S'){
				sx = i;
				sy = j;
			}
			if(map[i][j] == 'X'){
				gx[++cnt] = i;
				gy[cnt] = j;
			}
		}
	}
	bfs();
	return 0;
}
```


---

## 作者：tzl_Dedicatus545 (赞：1)

## 1.分析

这道题显然可以用搜索解决，但是要注意如下几点：

- 消灭小妖怪，大妖怪时，$3\text{s}$ 和 $5\text{s}$ 只是打怪时间，具体通过时间还要 $+1$ 。
- 紫妈的隙间在使用之前最好先排一遍序，可以加快查找速度。
- `bfs` 时要是用优先队列，否则无法保证先出队的一定是最小的的性质。
- 楼观剑和太阳花同时使用时只要保留一个状态即可，节省空间。
- 剑可以不要，紫妈的隙间可以不用。

注意以上几点，就很简单了。

## 2.AC Code

```cpp
//By: Luogu@⚡炭治郎⚡(a.k.a. Kamado_Tanjiro)(LuoguID:308854)
#include <bits/stdc++.h>

using namespace std;

const int INF=(sizeof(int)==4?0x3f3f3f3f:0x3f3f3f3f3f3f3f3f);
const int MOD=998244353;

char Map[1010][1010];
int ex,ey;
struct Point
{
	int x,y;

	bool operator<(const Point &xx) const
	{
		return pow(x-ex,2)+pow(y-ey,2)<pow(xx.x-ex,2)+pow(xx.y-ey,2);
	}
};
struct Status
{
	short nowItem;				//0 for none,1 for flower,2 for Sword.
	int time;
	Point point;

	const bool operator<(const Status &x) const
	{
		if(time==x.time)
		{
			if(nowItem==x.nowItem)
				return pow(point.x-ex,2)+pow(point.y-ey,2)>pow(x.point.x-ex,2)+pow(x.point.y-ey,2);

			return nowItem<x.nowItem;
		}

		return time>x.time;
	}
};

bool visited[1010][1010][3];	//0 for none,1 for flower,2 for Sword.
vector<Point> sukima;
int n,m;

int bfs(int sx,int sy)
{
	int dx[4]={1,-1,0,0};
	int dy[4]={0,0,1,-1};
	priority_queue<Status> q;

	q.push({0,0,{sx,sy}});

	while(!q.empty())
	{
		Status Now=q.top();

		q.pop();

		if(Map[Now.point.x][Now.point.y]=='E')
			return Now.time;

		for(int i=0;i<4;i++)
		{
			int nx=Now.point.x+dx[i],ny=Now.point.y+dy[i];

			if(nx<1 || nx>n || ny<1 || ny>m || visited[nx][ny][Now.nowItem])
				continue ;

			//cout<<nx<<" "<<ny<<endl;

			visited[nx][ny][Now.nowItem]=true;

			switch(Now.nowItem)
			{
			case 0:
				switch(Map[nx][ny])
				{
				case '1':
					break ;
				case 'S':
				case 'E':
				case 'M':
				case '0':
					q.push({0,Now.time+1,{nx,ny}});

					break;
				case '2':
					q.push({0,Now.time+4,{nx,ny}});

					break;
				case '3':
					q.push({0,Now.time+9,{nx,ny}});

					break;
				case '4':
					q.push({1,Now.time+1,{nx,ny}});

					break;
				case '5':
					q.push({2,Now.time+6,{nx,ny}});
					q.push({0,Now.time+1,{nx,ny}});

					break;
				case 'X':
					q.push({0,Now.time+1,{nx,ny}});

					for(int i=0;i<sukima.size();i++)
					{
						if(nx==sukima[i].x && ny==sukima[i].y)
							continue ;

						if(visited[sukima[i].x][sukima[i].y][Now.nowItem])
							continue ;

						if(Map[sukima[i].x][sukima[i].y]=='E')
						{
							return Now.time+2;
						}

                        visited[sukima[i].x][sukima[i].y][Now.nowItem]=1;

						q.push({0,Now.time+2,{sukima[i].x,sukima[i].y}});
					}

					break ;
				default:
					cout<<"TouHou World is broken!"<<endl;
					exit(-1);
				}

				break ;
			case 1:
				switch(Map[nx][ny])
				{
				case '1':
					break ;
				case 'S':
				case 'E':
				case 'M':
				case '0':
				case '2':
				case '3':
				case '4':
					q.push({1,Now.time+1,{nx,ny}});

					break;
				case '5':
					q.push({2,Now.time+6,{nx,ny}});
					q.push({1,Now.time+1,{nx,ny}});

					break;
				case 'X':
					q.push({1,Now.time+1,{nx,ny}});

					for(int i=0;i<sukima.size();i++)
					{
						if(nx==sukima[i].x && ny==sukima[i].y)
							continue ;

						if(visited[sukima[i].x][sukima[i].y][Now.nowItem])
							continue ;

						if(Map[sukima[i].x][sukima[i].y]=='E')
						{
							return Now.time+2;
						}

                        visited[sukima[i].x][sukima[i].y][Now.nowItem]=1;

						q.push({1,Now.time+2,{sukima[i].x,sukima[i].y}});
					}

					break ;
				default:
					cout<<"TouHou World is broken!"<<endl;
					exit(-1);
				}

				break ;
			case 2:
				switch(Map[nx][ny])
				{
				case '1':
				case 'S':
				case 'E':
				case 'M':
				case '0':
				case '2':
				case '3':
				case '4':
				case '5':
					q.push({2,Now.time+1,{nx,ny}});

					break;
				case 'X':
					q.push({2,Now.time+1,{nx,ny}});

					for(int i=0;i<sukima.size();i++)
					{
						if(nx==sukima[i].x && ny==sukima[i].y)
							continue ;

						if(visited[sukima[i].x][sukima[i].y][Now.nowItem])
							continue ;

						if(Map[sukima[i].x][sukima[i].y]=='E')
						{
							return Now.time+2;
						}

                        visited[sukima[i].x][sukima[i].y][Now.nowItem]=1;

						q.push({2,Now.time+2,{sukima[i].x,sukima[i].y}});
					}

					break ;
				default:
					cout<<"TouHou World is broken!"<<endl;
					exit(-1);
				}


				break ;
			default:
				cout<<"TouHou World is broken!"<<endl;
				exit(-1);
			}
		}
	}

	cout<<"We want to live in the TouHou World forever\n";

	exit(0);
}

signed main()
{
    ios::sync_with_stdio(0);

	int sx,sy;

	cin>>n>>m;

	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>Map[i][j];

			if(Map[i][j]=='X')
				sukima.push_back({i,j});
			if(Map[i][j]=='S')
				sx=i,sy=j;
			if(Map[i][j]=='E')
				ex=i,ey=j;
		}

	sort(sukima.begin(),sukima.end());

	cout<<bfs(sx,sy);

	return 0;
}

```

---

## 作者：huangxianghui (赞：1)

~~这道题说实话在各种大模拟中算简单的一类~~

## Solution
首先对地图进行处理（~~话说我的代码里面并没有大段处理地图的代码块~~）

当然只需要处理起点终点的位置~~以及没用的麻薯~~

注意千万不要尝试记录各个隙间的位置，这道题目时间放的比空间开，再加上$n*m\le10^{5}$，这边建议直接放心大胆地暴力搜索隙间，不会炸的。如果记录了隙间反而会MLE

然后主代码就是BFS了，然而由于本题的特性（BFS时最先到的不一定是用时最短的），我们要把队列换成优先队列来保证时间依次排列

特殊元素处理：

大小妖怪：有剑有花直接走，但仍然消耗一点时间，记得把时间加上去

楼观剑：注意一下可以不用拿，如果拿的话直接拿来覆盖太阳花的状态就可以了，效果是一样的

太阳花：偷花不用时间，拿了就完事

隙间：注意到每个隙间在无剑无花，有剑，只有花三个状态里都只需要传送一次（同一个状态不需要传两次，因为之前肯定BFS过），所以记录一下当前状态有没有传过隙间就可以了，另外是可以不穿隙间的。

代码如下：
```
#include<bits/stdc++.h>
#define ll long long
#define f(i,a,b) for (ll i=a;i<=b;i++)
#define fx(i,a,b) for (ll i=a;i>=b;i--)
using namespace std;
const int maxn=1010;
int jx[4]= {0,1,0,-1},jy[4]= {1,0,-1,0};
int n,m,sx,sy,ex,ey;
char c[maxn][maxn];
bool l[maxn][maxn][3];//记录每个位置的状态
struct node
{
	int t,x,y,num;
	bool l;
};
struct cmp
{
	bool operator ()(node x,node y)
	{
		return x.t>y.t;
	};
};
priority_queue<node,vector<node>,cmp> q;//优先队列排序
inline ll read()
{
	ll l=0,f=1;
	char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) l=(l<<3)+(l<<1)+(c^48),c=getchar();
	return l*f;
}
signed main()
{
	n=read(),m=read();
	f(i,1,n)
	{
		f(j,1,m)
		{
			cin>>c[i][j];
			if (c[i][j]=='S') sx=i,sy=j,c[i][j]='0';
			if (c[i][j]=='E') ex=i,ey=j,c[i][j]='0';
			if (c[i][j]=='M') c[i][j]='0';//麻薯吃掉
		}
	}
	node a1;
	a1.t=0,a1.x=sx,a1.y=sy,a1.num=0,q.push(a1);
	while (!q.empty())
	{
		a1=q.top(),q.pop();
		if (l[a1.x][a1.y][a1.num]) continue;//当前状态BFS过了就不用走了
		else l[a1.x][a1.y][a1.num]=1;
		if (a1.x==ex && a1.y==ey)
		{
			printf("%d",a1.t);
			return 0;
		}
		f(i,0,3)
		{
			int xx=a1.x+jx[i],yy=a1.y+jy[i];
			if (xx>0 && xx<=n && yy>0 && yy<=m)
			{
				node a2=a1;
				a2.t=a1.t+1,a2.x=xx,a2.y=yy;
				switch (c[xx][yy])
				{
					case '0':
						q.push(a2);
						break;
					case '1':
						if (a1.num==2) c[xx][yy]='0',q.push(a2);//砍墙
						break;
					case '2'://小妖怪
						if (a1.num==2) c[xx][yy]='0',q.push(a2);//砍妖怪
						else if (a1.num==1) q.push(a2);//有花
						else a2.t+=3,q.push(a2);//加上时间
						break;
					case '3'://大妖怪同上
						if (a1.num==2) c[xx][yy]='0',q.push(a2);
						else if (a1.num==1) q.push(a2);
						else a2.t+=8,q.push(a2);
						break;
					case '4':
						if (!a1.num) a2.num=1,a2.l=0;//重置状态
						q.push(a2);
						break;
					case '5':
						q.push(a2);//不拿剑
						if (a1.num!=2) a2.t+=5,a2.num=2,a2.l=0,q.push(a2);//拿剑并重置状态
						break;
					case 'X'://隙间
						if (!a2.l)
						{
							a2.l=1,a2.t++;
							f(j,1,n)
								f(p,1,m)
								{
									if (c[j][p]=='X') a2.x=j,a2.y=p,q.push(a2);
								}
						}//暴力找每个隙间
						else q.push(a2);//留在原地
						break;
				}
			}
		}
	}
	printf("We want to live in the TouHou World forever");
	return 0;
}
```
tip：不要被题面的所谓“稀奇古怪的解法”骗到，要走回头路必然是拿花或拿剑，然而如果可以拿花或拿剑你前面已经走过了。

---

## 作者：Presentation_Emitter (赞：1)

~~猪国杀弱化版+搜索/图论（确信）~~

本题有亿点点细节，这里采用了记忆化BFS的方式。

首先，由于地图中要素过多，所以我们要先对这些要素进行处理

```cpp
for(int i=1;i<=n;++i)
{
	for(int j=1;j<=m;++j)
	{
		cin>>ch;
		switch(ch)
		{
			case 'S'://起点，可通行
				mp[i][j]=0;//mp[i][j]表示(i,j)的状态
				sx=i;
				sy=j;
				break;
			case 'E'://终点，可通行
				mp[i][j]=0;
				fx=i;
				fy=j;
				break;
			case '0':case '1':case '2':case '3':case '4':case '5':
				mp[i][j]=ch&15;//0~5，参照题意
				break;
			case 'M':
				mp[i][j]=0;//看到麻薯直接藏起来
				break;
			case 'X':
				mp[i][j]=age;//隙间（age是一个很大的数）
				xs.push_back((xnode){i,j});//存储隙间
				break;
			case '9':
				mp[i][j]=9;//看讨论区里面有9就加进去了，视为不可通行
				//printf("⑨baka\n");
				break;
			default:
				mp[i][j]=0;//装饰用
				break;
		}
	}
}
```

接下来我们就可以搜索了。

因为不同的格子通过时间不同，因此简单的BFS明显不行。我们需要使用优先队列优化。根据数据范围，显然需要使用记忆化搜索。

```cpp
#define ll long long
#define pos mp[curr.x][curr.y]
#define age 0x3f3f3f3f3f3f3f3fll
struct xnode
{
	ll x,y;
	xnode(ll a,ll b){x=a,y=b;}
};
struct node
{
	ll x,y,ti;//位置和时间
	bool lgs,sun;//有无楼观剑和太阳花
	bool operator> (const node _cmp)const
	{
		return ti>_cmp.ti;
	}
	node(ll a,ll b,ll c,bool d,bool e){x=a,y=b,ti=c,sun=d,lgs=e;}
	void out(bool flag)
	{
		cout<<x<<' '<<y<<' '<<ti<<' '<<sun<<lgs;
		if(flag)cout<<endl;
	}
};
inline int getstat(node nd)//获取当前状态。由于楼观剑有太阳花的一切特性，所以在有楼观剑时不区分是否有太阳花
{
	if(nd.lgs)return 2;
	if(nd.sun)return 1;
	return 0;
}
inline void daisuke(node mgd)//插入节点
{
	if(mgd.ti>=val[mgd.x][mgd.y][getstat(mgd)])return;
	val[mgd.x][mgd.y][getstat(mgd)]=mgd.ti;
	q.push(mgd);
}
inline ll bfs(ll sx,ll sy)
{
	while(!q.empty())q.pop();
	q.push((node){sx,sy,0,0,0});
	while(!q.empty())
	{
		node t=q.top();
		q.pop();
		if(t.x==fx&&t.y==fy)return t.ti;//睡够回家
		for(int i=0;i<4;++i)
		{
			node curr=t;
			curr.x=t.x+mov[i][0];
			curr.y=t.y+mov[i][1];//移动
			if(curr.x<=0||curr.x>n||curr.y<=0||curr.y>m)continue;
			if(pos==(9)||pos==1&&!t.lgs)continue;//无法通行
			if(pos==age)
			{
				for(int j=0;j<xs.size();++j)
				{
					if(xs[j].x==curr.x&&xs[j].y==curr.y)continue;
					daisuke((node){xs[j].x,xs[j].y,t.ti+2,t.sun,t.lgs});//移动1s，传送1s
				}
			}
			if(!curr.sun&&!curr.lgs&&(pos==2||pos==3))curr.ti=t.ti+pos*pos;
			else curr.ti=t.ti+1;
			if(pos==4&&!curr.sun)curr.sun=1;//抢花（因为不需要时间）
			if(pos==5&&!curr.lgs)daisuke(node(curr.x,curr.y,t.ti+6,curr.sun,1));//拿剑（可以取也可以不取）
			daisuke(curr);
		}
	}
	return -1;
}
```

接下来我们就可以提交了。这是[提交记录](https://www.luogu.com.cn/record/40211093)

我们看到，仍然有2个点TLE了。接下来我们看向此处。

```cpp
if(pos==age)
{
	for(int j=0;j<xs.size();++j)
	{
		if(xs[j].x==curr.x&&xs[j].y==curr.y)continue;
		daisuke((node){xs[j].x,xs[j].y,t.ti+2,t.sun,t.lgs});
	}
}
```

若当前状态（即是否拿到太阳花，楼观剑）下已经使用过一次隙间，那么之后就没有必要使用隙间了（除非状态改变）。可以对使用隙间的情况进行标记。

在加上一堆要素后，我们得到了以下代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#define QAQ ;
#define ll long long
#define fujin_rumble 0//风神
#define pos mp[curr.x][curr.y]
#define age 0x3f3f3f3f3f3f3f3fll
#define hidemafu(x,y) mp[x][y]=0//藏麻薯
#define getstat(s) rubbish_sorting(s)
#define I_dont_know_what_to_do break
#define dont_know_what_is_mafu luogu=1
#define We_want_to_live_in_the_TouHou_World_forever -1
using namespace std;
ll val[1010][1010][3];
ll sx,sy,fx,fy,mp[1010][1010],n,m;
const ll cyanine[4][2]={{-1,0},{1,0},{0,-1},{0,1}}; 
bool baka;
struct xnode
{
	ll x,y;
	xnode(ll a,ll b){x=a,y=b;}
};
struct node
{
	ll x,y,ti;
	bool luogu,sun;//浴谷在手OI我有
	bool operator> (const node _cmp)const
	{
		return ti>_cmp.ti;
	}
	node(ll a,ll b,ll c,bool d,bool e){x=a,y=b,ti=c,sun=d,luogu=e;}
	void out(bool flag)
	{
		cout<<x<<' '<<y<<' '<<ti<<' '<<sun<<luogu;
		if(flag)cout<<endl;
	}
};
vector<xnode> xs;
priority_queue<node,vector<node>,greater<node> >q;
inline int rubbish_sorting(node whereisat)
{
	if(whereisat.luogu)return 2;
	if(whereisat.sun)return 1;
	return 0;
}
inline void daisuke(node mgd)
{
	if(mgd.ti>=val[mgd.x][mgd.y][getstat(mgd)])return QAQ
	val[mgd.x][mgd.y][getstat(mgd)]=mgd.ti QAQ
	q.push(mgd) QAQ
}
inline ll bfs(ll sx,ll sy)
{
	while(!q.empty())q.pop();
	q.push((node){sx,sy,0,0,0});
	val[sx][sy][0]=0;
	while(!q.empty())
	{
		node t=q.top();
		q.pop();
		if(t.x==fx&&t.y==fy)return t.ti;
		for(int i=0;i<4;++i)
		{
			node curr=t;
			curr.x=t.x+cyanine[i][0];
			curr.y=t.y+cyanine[i][1];
			if(curr.x<=0||curr.x>n||curr.y<=0||curr.y>m)continue;
			if(pos==(9)||pos==1&&!t.luogu)continue;
			if(pos==age)
			{
				for(int j=0;j<xs.size();++j)
				{
					if(xs[j].x==curr.x&&xs[j].y==curr.y)continue;
					daisuke((node){xs[j].x,xs[j].y,t.ti+2,t.sun,t.luogu});
				}
			}
			if(!curr.sun&!curr.luogu&&(pos==2||pos==3))curr.ti=t.ti+pos*pos;
			else curr.ti=t.ti+1;
			if(pos==4&&!curr.sun)curr.sun=1;
			if(pos==5&&!curr.luogu)daisuke(node(curr.x,curr.y,t.ti+6,curr.sun,1));
			daisuke(curr);
		}
	}
	return We_want_to_live_in_the_TouHou_World_forever QAQ
}
int main()
{
	cin>>n>>m;
	char ch;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			val[i][j][0]=val[i][j][1]=val[i][j][2]=age;
			cin>>ch;
			switch(ch)
			{
				case 'S':
					mp[i][j]=0;
					sx=i;
					sy=j;
					break;
				case 'E':
					mp[i][j]=0;
					fx=i;
					fy=j;
					break;
				case '0':case '1':case '2':case '3':case '4':case '5':
					mp[i][j]=ch&15;
					break;
				case 'M':
					hidemafu(i,j) QAQ
					break;
				case 'X':
					mp[i][j]=age;
					xs.push_back((xnode){i,j});
					break;
				case '9':
					mp[i][j]=9;
					baka=1;
					break;
				default:
					I_dont_know_what_to_do QAQ
			}
		}
	}
	register ll ans=bfs(sx,sy);
	if(ans!=We_want_to_live_in_the_TouHou_World_forever)cout<<ans<<endl;
	else cout<<"We want to live in the TouHou World forever"<<endl QAQ
	return 0;
}
```

---

## 作者：WanderingTrader (赞：1)

这题可真毒瘤啊，我提交了10遍才过，发个题解纪念一下。
### 题目分析
第一眼看上去是一个矩阵地图上的最短路，应该用BFS算法。

但是我们发现边与边之间的权值不一样。

这个问题用一个小优化就可以解决：把BFS中的队列换成优先队列。根据当前结点到起点的距离从小到大排序。(本质上就是隐式图上的dijkstra)

于是这道题的基本思路就定下来了。但是还是有很多细节需要注意。
### 代码
首先我们用一个二维字符数组来保存地图，做一下初始化：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000+5;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
char M[maxn][maxn];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	return 0;
}
```
接下来定义结点：一个x,y表示位置，一个dis表示距离，一个p表示模式。这里对模式的定义是：如果到当前结点位置已经获得楼观剑，p=2，如果没有楼观剑但有太阳花，p=1，如果两者都没有，p=0。所以p本质上就是一个一位三进制数（就像一位二进制数可以表示一个状态一样）。
```cpp
struct Node 
{
	int x,y,dis,p;
	bool operator<(const Node& a)const{return dis>a.dis;}
};
```
vis数组开三维，最后一维大小为3，代表模式：
```cpp
bool vis[maxn][maxn][3];
```
然后开一个优先队列，类型为Node。
```cpp
Node t;
priority_queue <Node> Q;
```
接下来我们跑一遍整张地图，如果碰到`S`就把结点放入优先队列，如果碰到`X`就把结点加入传送门列表。

为了节省空间，传送门列表用两个vector即可：
```cpp
vector <int> a,b;
```
```cpp
for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
		if(M[i][j]=='S')
			Q.push((Node){i,j,0,0});
		else if(M[i][j]=='X')
		{
			a.push_back(i);
			b.push_back(j);
			++cnt;
		}
```
接下来就是BFS了，我们先把必要的模板写上：
```cpp	
while(!Q.empty())
{
	t=Q.top();Q.pop();
	if(M[t.x][t.y]=='E')
	{
		printf("%d\n",t.dis);
		return 0;
	}
}
puts("We want to live in the TouHou World forever");
```
遍历上下左右四个位置。把原结点的信息拷贝一份，然后修改x,y的值，再把dis+1（即走了这一步）。顺便也判断一下位置是否合法。
```cpp
for(int i=0;i<4;++i)
{
	Node now=t;
	now.x+=dx[i];now.y+=dy[i];++now.dis;
	if(now.x<1||now.x>n||now.y<1||now.y>m)
		continue;
}
```
为了节省空间，我们要确保每次在队列中放入结点时都没有重复（而不是弹出时再判断）。所以我们写一个函数：
```cpp
inline void add(const Node& tmp)
{
	if(!vis[tmp.x][tmp.y][tmp.p])
	{
		vis[tmp.x][tmp.y][tmp.p]=true;
		Q.push(tmp);
	}
}
```
如果此格子是`5`，由于拿宝剑会浪费5点权值，所以我们需要分类，即拿与不拿两种：
```cpp
if(M[now.x][now.y]=='5')
{
	add(now);
	now.dis+=5;
	now.p=2;
}
add(now);
```
如果此格子是`4`，由于获取太阳花不需要时间，所以拿肯定比不拿要优，无需分类。判断p，如果p是0，那么把p变为1，否则p不变：
```cpp
else if(M[now.x][now.y]=='4')
{
	if(!now.p)
		now.p=1;
}
```
注意这里要加上大括号，否则里面的if会和接下来的else if连在一起。

如果格子是`3`，那么如果p=0，那么乖乖给dis加上8，否则直接忽略：
```cpp
else if(M[now.x][now.y]=='3')
{
	if(!now.p)
		now.dis+=8;
}
```
同样，如果格子是`2`，那么如果p=0，dis加上3，否则直接忽略：
```cpp
else if(M[now.x][now.y]=='2')
{
	if(!now.p)
		now.dis+=3;
}
```
如果格子是`1`，而且p不是2，那么这个格子无法通行，下一个：
```cpp
else if(M[now.x][now.y]=='1'&&now.p<2)
	continue;
```
其他情况（格子是`0`,`X`,`M`,`S`,`E`），均不需要额外处理。

跑完上下左右四个格子以后，我们再判断一下，如果当前格子是`X`，那么就使用传送门：
```cpp
if(M[t.x][t.y]=='X')
	addx(t);
```
addx函数：
```cpp
void addx(const Node& tmp)
{
	for(int i=0;i<cnt;++i)
		if(a[i]!=tmp.x||b[i]!=tmp.y)
			add((Node){a[i],b[i],tmp.dis+1,tmp.p});
}
```
遗憾的是，如果addx函数这样写是会TLE的。

试想：如果两次进入addx函数的时候，当前的p都是一样的，那两次的结果就会完全一样，不仅浪费了大量的时间，也会增加空间的开销。所以我们写一个vst函数来存放是否已经用过每个模式的传送门：
```cpp
bool vst[4]; 
void addx(const Node& tmp)
{
	if(vst[tmp.p]) return;
	vst[tmp.p]=true;
	for(int i=0;i<cnt;++i)
		if(a[i]!=tmp.x||b[i]!=tmp.y)
			add((Node){a[i],b[i],tmp.dis+1,tmp.p});
}
```
这样，整个搜索部分就结束了

全部代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000+5;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
char M[maxn][maxn];
bool vis[maxn][maxn][3];
bool vst[4]; 
struct Node 
{
	int x,y,dis,p;
	bool operator<(const Node& a)const{return dis>a.dis;}
};
int n,m,cnt;
vector <int> a,b;
Node t;
priority_queue <Node> Q;
inline void add(const Node& tmp)
{
	if(!vis[tmp.x][tmp.y][tmp.p])
	{
		vis[tmp.x][tmp.y][tmp.p]=true;
		Q.push(tmp);
	}
}
void addx(const Node& tmp)
{
	if(vst[tmp.p]) return;
	vst[tmp.p]=true;
	for(int i=0;i<cnt;++i)
		if(a[i]!=tmp.x||b[i]!=tmp.y)
			add((Node){a[i],b[i],tmp.dis+1,tmp.p});
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(M[i][j]=='S')
				Q.push((Node){i,j,0,0});
			else if(M[i][j]=='X')
			{
				a.push_back(i);
				b.push_back(j);
				++cnt;
			}
	while(!Q.empty())
	{
		t=Q.top();Q.pop();
		if(M[t.x][t.y]=='E')
		{
			printf("%d\n",t.dis);
			return 0;
		}
		for(int i=0;i<4;++i)
		{
			Node now=t;
			now.x+=dx[i];now.y+=dy[i];++now.dis;
			if(now.x<1||now.x>n||now.y<1||now.y>m)
				continue;
			if(M[now.x][now.y]=='5')
			{
				add(now);
				now.dis+=5;
				now.p=2;
			}
			else if(M[now.x][now.y]=='4')
			{
				if(!now.p)
					now.p=1;
			}
			else if(M[now.x][now.y]=='3')
			{
				if(!now.p)
					now.dis+=8;
			}
			else if(M[now.x][now.y]=='2')
			{
				if(!now.p)
					now.dis+=3;
			}
			else if(M[now.x][now.y]=='1'&&now.p<2)
				continue;
			add(now);
		}
		if(M[t.x][t.y]=='X')
			addx(t);
	}
	puts("We want to live in the TouHou World forever");
	return 0;
}
```
$$\texttt{The End.}$$

---

## 作者：happy_dengziyue (赞：1)

### 1 思路

观察题目，不难想到用BFS做，但是此题有很多坑点。

接下来讲解代码逻辑

1. 定义一大堆变量，主要的有：

	1. 变量 $n$ 和 $m$，表示地图尺寸；
    
   2. 二维数组 $gra$，描述地图（数字意义可以参照注释）；
   
   3. 三维数组 $vis$，记录访问它的最少时间（可以参照注释），初始化为一个很大的数；
   
   4. 变量 $sx$，$sy$，$ex$，$ey$ 记录起点和终点坐标信息；
   
   5. 方向数组；
   
   6. 一维数组 $xj$，记录所有隙间坐标，~~拼音看得懂吧~~；
   
   7. 一维数组 $visx$，记录隙间访问过与否（可以参照注释）； 
   
   8. 优先队列 $way$，记录BFS过程；
   
   	优先队列可以确保最早找到的答案就是最优解；
   
   9. 变量 $ans$，记录到终点最快的时间。

2. 绘制地图；

3. 开始BFS：
	
   在这里：
    
	我们定义“路径点”，指一条路径走到某处的一个点，里面记录了坐标、能力值和耗费时间信息。我们会基于一个路径点向四周扩展，直至达到终点。

	1. 插入起点，记录访问；
    
   2. 进入循环；
   
   3. 取出队首；
   
   4. 如果自己是终点，记录答案，退出循环；
   
   5. 如果自己是隙间：
   
   	如果没有能力值大于等于自己的路径点访问，就将所有隙间都传送一遍。因为，多次隙间传送，是为了增加能力值，如果增加不了，那就没有意义。
    
   6. 向四周扩展路径：
   
		1. 如果该点是空地或隙间，且该点的访问最短时间更大，就可以扩展路径，注意更新最短时间。
        
		2. 如果该点是小妖怪或大妖怪，自己计算所需时间（代码注释认真看），和空地的处理一样，比较当前时间与之前的最短时间。
      
		3. 如果该点是太阳花，在能力值为 $0$ 的情况下必须拿，反正没有额外的代价。
      
		4. 如果该点是楼观剑：
      
			1. 如果自己没有剑，同时入队拿和不拿两种情况，因为**楼观剑可以不拿**。
            
				其实太阳花也可以不拿，只是拿太阳花没有额外代价，拿楼观剑有。
            
			2. 如果自己有剑，千万别拿。
            
   7. 回到“2”处。

4. 输出答案，顺利AC。

### 2 代码与记录

如果有不懂的地方，看代码注释。

一定要细心理解代码！

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int max_size=1000;//最大尺寸
const int max_pw=2;//最大能力值
	//定义能力值为：0 无花无剑  1 有花无剑  2 有剑
const int max_num=12345678;//设置极大值
int n,m;//地图尺寸
int gra[max_size+2][max_size+2];//地图
	//0 空地  1 墙  2 小妖怪  3 大妖怪  4 太阳花  5 楼观剑  6 隙间
int vis[max_size+2][max_size+2][max_pw+1];//vis[a][b][c]指能力值恰好为c时到达这个点最少需要多少时间
char ty[max_size+2];//只是用来输入的
int sx,sy;//起点坐标
int ex,ey;//终点坐标
int nx,ny;//当前坐标（待会会用）
int nt;//当前花费时间（待会会用）
int dx[4]={-1,1,0,0};//方向数组—行
int dy[4]={0,0,-1,1};//方向数组—列
	//0 上  1 下  2 左  3 右
struct P{//坐标结构体
	int x,y;
};
P xj[max_size*max_size+2];//隙间信息
int xj_i=0;//隙间数量
bool visx[max_pw+1];//visx[a]指在能量值为a的情况下用没用过隙间
struct W{//路径结构体
	P p;//坐标
	int pw;//能力值
	int t;//花费时间
};
priority_queue<W> way;
inline bool operator < (W a,W b){
	return a.t>b.t;//优先队列是反的
}
W fro;
int ans=max_num;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P4872_1.in","r",stdin);
	freopen("P4872_1.out","w",stdout);
	#endif
	//输入基本信息，绘制地图的工作
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%s",ty+1);
		for(int j=1;j<=m;++j){
			for(int k=0;k<=max_pw;++k){
				vis[i][j][k]=max_num;
			}
			if(ty[j]=='S'){//起点
				sx=i;
				sy=j;
				gra[i][j]=0;
				continue;
			}
			if(ty[j]=='E'){//终点
				ex=i;
				ey=j;
				gra[i][j]=0;
				continue;
			}
			if(ty[j]=='M'){//麻薯
				gra[i][j]=0;
				continue;
			}
			if(ty[j]=='X'){//隙间
				gra[i][j]=6;
				++xj_i;
				xj[xj_i].x=i;
				xj[xj_i].y=j;
				continue;
			}
			//接下来就可以用一行代码绘制其它情况
			gra[i][j]=ty[j]-'0';
		}
	}
	//BFS 环节
	way.push((W){(P){sx,sy},0,0});
	vis[sx][sy][0]=0;
	while(!way.empty()){
		//取出队首
		fro=way.top();
		way.pop();
		//到达终点
		if(fro.p.x==ex&&fro.p.y==ey){
			ans=fro.t;
			break;
		}
		//遇到隙间
		if(gra[fro.p.x][fro.p.y]==6){
			bool ok=true;
			for(int i=fro.pw;i<=max_pw;++i){
				if(visx[i]){
					ok=false;
					break;
				}
			}
			if(ok){
				nt=fro.t+1;
				for(int i=1;i<=xj_i;++i){//遍历一遍所有隙间
					if(xj[i].x!=fro.p.x||xj[i].y!=fro.p.y){//这肯定是另一个隙间，不是自己
						bool ok=true;
						for(int j=fro.pw;j<=max_pw;++j){//如果隙间被比自己能力值大又时间更早的访问了，就不用传了
							if(vis[xj[i].x][xj[i].y][j]<=nt){
								ok=false;
								break;
							}
						}
						if(ok){
							way.push((W){(P){xj[i].x,xj[i].y},fro.pw,nt});
							vis[xj[i].x][xj[i].y][fro.pw]=nt;
						}
					}
				}
				visx[fro.pw]=true;
			}
		}
		//正常行走
		for(int d=0;d<4;++d){
			//计算下一步坐标
			nx=fro.p.x+dx[d];
			ny=fro.p.y+dy[d];
			//做一些排除
			if(nx<1||nx>n||ny<1||ny>m){//越界
				continue;
			}
			if(gra[nx][ny]==1&&fro.pw<2){//不能通过墙的时候
				continue;
			}
			//分类讨论开始
			if(gra[nx][ny]==0||gra[nx][ny]==6){//空地或隙间，其实处理起来一样
				nt=fro.t+1;
				bool ok=true;
				for(int j=fro.pw;j<=max_pw;++j){
					if(vis[nx][ny][j]<=nt){//有更早的人访问过了
						ok=false;
						break;
					}
				}
				if(ok){
					way.push((W){(P){nx,ny},fro.pw,nt});
					vis[nx][ny][fro.pw]=nt;
				}
				continue;
			}
			if(gra[nx][ny]==1){//墙，注意，代码能运行到此时，说明自己有剑
				nt=fro.t+1;
				if(vis[nx][ny][2]>nt){//这行和下面2行中的“2”都代指自己的能力值（保证能力值为2）
					way.push((W){(P){nx,ny},2,nt});
					vis[nx][ny][2]=nt;
				}
				continue;
			}
			if(gra[nx][ny]==2){//小妖怪
				if(fro.pw==0){//需要打妖怪
					nt=fro.t+4;//注意，这里需要（3+1）秒，包括了走路和打妖怪，下一个妖怪的9秒同理。
				}
				else{//直接通过
					nt=fro.t+1;
				}
				bool ok=true;
				for(int j=fro.pw;j<=max_pw;++j){
					if(vis[nx][ny][j]<=nt){//有更早的人访问过了
						ok=false;
						break;
					}
				}
				if(ok){
					way.push((W){(P){nx,ny},fro.pw,nt});
					vis[nx][ny][fro.pw]=nt;
				}
				continue;
			}
			if(gra[nx][ny]==3){//大妖怪
				if(fro.pw==0){//需要打妖怪
					nt=fro.t+9;//注意，这里需要（8+1）秒，包括了走路和打妖怪，上一个妖怪的4秒同理。
				}
				else{//直接通过
					nt=fro.t+1;
				}
				bool ok=true;
				for(int j=fro.pw;j<=max_pw;++j){
					if(vis[nx][ny][j]<=nt){//有更早的人访问过了
						ok=false;
						break;
					}
				}
				if(ok){
					way.push((W){(P){nx,ny},fro.pw,nt});
					vis[nx][ny][fro.pw]=nt;
				}
				continue;
			}
			if(gra[nx][ny]==4){//太阳花田
				nt=fro.t+1;
				if(fro.pw==0){//没有花，去一下吧
					way.push((W){(P){nx,ny},1,nt});//注意，能力值要改成1，下一行的“1”同理
					vis[nx][ny][1]=nt;
					continue;
				}
				//有花了就不一定要去了，但也可以去
				bool ok=true;
				for(int j=fro.pw;j<=max_pw;++j){
					if(vis[nx][ny][j]<=nt){//有更早的人访问过了
						ok=false;
						break;
					}
				}
				if(ok){
					way.push((W){(P){nx,ny},fro.pw,nt});
					vis[nx][ny][fro.pw]=nt;
				}
				continue;
			}
			if(gra[nx][ny]==5){
				if(fro.pw<2){//没有剑，去一下吧
					nt=fro.t+6;
					way.push((W){(P){nx,ny},2,nt});//注意，能力值要改成2，下一行的“2”同理
					vis[nx][ny][2]=nt;
				}
				//没有剑也不一定要用
				nt=fro.t+1;
				bool ok=true;
				for(int j=fro.pw;j<=max_pw;++j){
					if(vis[nx][ny][j]<=nt){//有更早的人访问过了
						ok=false;
						break;
					}
				}
				if(ok){
					way.push((W){(P){nx,ny},fro.pw,nt});
					vis[nx][ny][fro.pw]=nt;
				}
				continue;
			}
		}
	}
	if(ans==max_num){
		printf("We want to live in the TouHou World forever\n");//此生无悔入东方
	}
	else{
		printf("%d\n",ans);//来世炸了幻想乡
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51498079)

By **dengziyue**


---

