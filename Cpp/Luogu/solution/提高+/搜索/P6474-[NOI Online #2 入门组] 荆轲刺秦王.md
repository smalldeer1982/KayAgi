# [NOI Online #2 入门组] 荆轲刺秦王

## 题目背景

本测试数据为脚造，欢迎提供 hack。

第 18 组数据卡了很多人，放于附件中供检查。

## 题目描述

时隔数年，刺客荆轲再次来到咸阳宫，试图刺杀嬴政。

咸阳宫的地图可以描述为一个 $n$ 行 $m$ 列的矩形。在这里，我们规定每一行中从左到右为 $x$ 轴正方向，每一列中从下到上为 $y$ 轴正方向，左下角的点坐标为 $(1,1)$。矩形中的点可以分为 $4$ 种：

1. 起点，也就是荆轲的所在点，在地图中用字符 `S` 代表。
2. 终点，也就是嬴政的所在点，在地图中用字符 `T` 代表。
3. 卫兵，在地图中用一个正整数 $a_{i,j}$ 代表。在这里，一个卫兵 $(i,j)$ 可以观察到与他曼哈顿距离小于 $a_{i,j}$ 的点。也就是卫兵 $(i,j)$ 可以观察到所有满足 $|x-i|+|y-j|<a_{i,j}$ 的点 $(x,y)$。
4. 空地，在地图中用字符 `.` 代表。

荆轲的正常移动方式为每秒向八连通的任意方向前进一格。如下图，中间的点为荆轲当前所在点，每一秒，他可以走向其余的八个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/9rnnpj4z.png)

需要注意的是，正常移动时，荆轲不能踏进任何一个有卫兵或者卫兵能观察到的格子。当然，他也不能走出咸阳宫，也就是说，无论何时，荆轲的坐标 $(x,y)$ 都必须满足 $1\le x\le m$ 且 $1\le y\le n$。

荆轲还有两种技能：隐身和瞬移。

1. 隐身：下一秒荆轲进入隐身状态，卫兵观察不到荆轲，荆轲可以进入卫兵的观察范围内，但仍然不能进入卫兵所在的格子。注意这个状态只能维持一秒。
2. 瞬移：荆轲下一秒移动的距离改为 $d$，但这时只能向上下左右四个方向移动。即可以移动到 
$(x+d,y)$，$(x-d,y)$，$(x,y+d)$，$(x,y-d)$。
在本题中，两种技能可以同时使用，而且不考虑冷却时间，即一次用完可以立即用下一次，两种技能都分别有使用次数限制，你也可以不用完所有次数。

现在给出咸阳城的地图，请计算荆轲到达秦王所在点所需的最短时间。此外，在所用时间相同情况下，荆轲希望使用的两种技能总次数尽可能少；在所用时间与技能次数相同情况下，荆轲希望使用的隐身次数尽可能少。

## 说明/提示

#### 样例 1 解释

起点为 $(1,2)$，荆轲可以依次走到 $(1,3)$, $(2,4)$, $(3,5)$ 到达终点。

#### 样例 2 解释

起点为 $(2,8)$，荆轲可以依次走到 $(2,5)$, $(2,2)$, $(5,2)$，需要注意的是，即使最后一步到达终点，但因为终点在卫兵的观察范围之内，所以仍然需要隐身进入。

#### 数据范围与提示


对于测试点 $1\sim 6$：$n$, $m\le 10$，$c_1=c_2=0$，保证所需的最短时间不超过 $5$ 或者无解。

对于测试点 $7\sim 10$：$n$, $m\le 20$，$c_1=c_2=0$，保证 `T` 的位置不在任何一个卫兵的观察范围之中。

对于测试点 $11\sim 12$：$n$, $m\le 20$，$c_1=0$

对于测试点 $13\sim 14$：$n$, $m\le 20$，$c_1$, $c_2 \le 5$。

对于测试点 $15\sim 16$：卫兵个数不超过 $350$。

对于所有测试点：$2\le n$, $m\le 350$，$1\le a_{i,j}\le 350$，$0\le c_1$, $c_2\le 15$，$1\le d\le 350$。

保证 `S` 的位置不在任何卫兵的观察范围中。

## 样例 #1

### 输入

```
5 4 0 0 5
. 1 T 1
. . . 2
. 1 . .
S . . .
1 . . .```

### 输出

```
3 0 0```

## 样例 #2

### 输入

```
8 6 2 3 3
. S . . . .
. . . . . .
. . . . . .
. . . . . .
. . . . . .
2 . 2 . 2 .
. . 1 . T .
3 . 1 . . 3
```

### 输出

```
3 1 3```

## 样例 #3

### 输入

```
8 6 5 5 2
. S . . . .
. . . . . .
. . . . . .
1 1 3 2 . 1
2 3 2 2 1 3 
3 2 4 1 4 3 
2 6 1 5 T 2 
8 1 6 3 2 10```

### 输出

```
-1```

# 题解

## 作者：yangrunze (赞：141)

做题之前，让我们先大喊两句：

$\bold{\sout\text{ 荆轲，你刺秦王的英勇事迹将会被全天下的OIers怀恨在心}}$

$\bold{\Large\xcancel\text{荆轲将会臭名昭著}}$



------------
好了，发泄完啦，让我们开始认真做题吧！

一看题目，像个**搜索**

再一看，像个**广度优先搜索**

既然是**BFS**，那我们首先要搞出一个（一堆）队列

那问题是队列里咱们存啥呢？？？

首先，按照广搜解决“迷宫问题”的国际惯例，肯定要先把**坐标**和**步数**存到里面！

可是，这似乎不大够？

遇到问题不要怕，~~微笑着面对它~~，从题目中找答案！

>荆轲还有两种技能：**隐身**和**瞬移**。

>1. 隐身：balabala……
>2. 瞬移：balabala……

>现在给出咸阳城的地图，请计算荆轲到达秦王所在点所需的**最短时间**。此外，在所用时间相同情况下，荆轲希望使用的**两种技能总次数尽可能少**；在所用时间与技能次数相同情况下，荆轲希望使用的**隐身次数尽可能少**。

emmmmm，还要把**隐身和瞬移的使用次数存下来**~

啊，要存这么多东西……这时候，**结构体**就要派上用场啦！

~~（结构体是哪位？不是哪位，是用这玩意写高精特别方便的那个结·构·体！）~~

```cpp
struct qwq{
	int x,y,yx,sy,s;
	//x,y——对应的坐标
	//s——走到这一步的步数
	//yx——隐形使用次数
	//sy——瞬移使用次数
	//（都是用拼音写的呢）
};
queue <qwq> q;//STL超级方便！就是常数大那么亿点
```
当然，我们要在茫茫多的方案中选择一个**最优解**——所以，我们要写一个函数（算是取min吧……），来选择一个最优解
```cpp
qwq minq(qwq a,qwq b){
	if(a.s!=b.s)return a.s<b.s?a:b;//优先选择步数更小的
	if(a.yx+a.sy!=b.yx+b.sy)return a.yx+a.sy<b.yx+b.sy?a:b;//如果步数相等，选择一个技能使用更少的
	return a.yx<b.yx?a:b;//都相等？！那就选一个隐身用的更少的吧
}
qwq ans=(qwq){0,0,233333333,233333333,233333333};//顺便把初始化的ans放出来，当然要挑个大的                                   
```


------------

所有结构体啥的准备工作都已经完成啦！接下来，咱们考虑一下main函数的框架：包括输入等细节的处理

especially，咱们来康康要输入要注意啥：

1. 输入的整个地图，既有诸如 `S` `T` `.` 之类的字符，还有表示卫兵监控范围的数，两个这么一整合——就**用string来输入**吧！
2. 由于S啊，T啊啥的随便换个数就行了，只要能标记上就OK，而地图上的数字是非常重要的，所以**地图我们用int类型存储**
3. 这应该也是每个字符串模拟题要注意的地方，**当输入到字符串里的数字$\ge10$的时候，我们要一位一位加上去，（写的时候可以照快读那样写）**，千万不要读完一位剩下的就不管了
4. 对于每种字符的特殊处理——**标记起点和终点**，遇到卫兵时，我们要**处理出卫兵的观察范围**

呼呼，大概就这么多啦~

```cpp
int n,m,c1,c2,d;//题目描述里的一堆东西
int map[355][355];//地图
int main(){
    ios::sync_with_stdio(false);//关闭流同步，让cin变得快快哒！
	cin>>n>>m>>c1>>c2>>d;//据说cin和scanf混用会出锅？统一用cin
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			string s;
			cin>>s;
			if(s[0]=='S'){//起点
				sx=i,sy=j;//找到起点坐标
				map[i][j]=-1;//标个记
				q.push((qwq){sx,sy,0,0,0});//放到队列里~！
				vis[i][j][0][0]=1;//起点的vis先变成1（vis为啥要开四维？待会再说！（可能大家都已经想到了））
			}
			else if(s[0]=='T'){//终点~
				ex=i,ey=j;//找坐标
				map[i][j]=-2;//标个记
			}
			else if(s[0]=='.')map[i][j]=0;//平凡的空地就不用处理啦
			else{//S，T和.都不是，那就是卫兵啦
				int x=0;//数字读进来
				for(int i=0;i<s.size();i++)
				x=(x<<1)+(x<<3)+(s[i]^'0');//类比快读的原理
				map[i][j]=x;//存到地图里
				lookaround(i,j,x-1);//处理出这只士兵的观察范围，待会讲（重点！）
			}
		}
	}
	bfs();//baidu_first_search（伦敦大雾）
	if(ans.s==233333333)printf("-1");//如果ans没变，那就走不通了
	else printf("%d %d %d",ans.s,ans.yx,ans.sy);//否则输出
	return 0;//功德圆满
}
```



------------
那接下来的问题来啦！如何处理每个士兵的监控范围呢？

$\large{\text{（前排提示：敲黑板，划重点！！！）}}$

暴力找周围曼哈顿距离$<a$的点？

时间复杂度$O(a^2)$，加上输入的循环$O(a^2mn)$，TLE警告……

那咋办呢？别急，正所谓“举例是理解的试金石”~~（话说我这是第几次用这句话了……反正好久没用了）~~，咱们先画个图！

下图就是$a=3$的情况，士兵可以观察到和它的曼哈顿距离$\le2$的点

![](https://cdn.luogu.com.cn/upload/image_hosting/52q3zu08.png)

（图中，$\bold{\text{黑色}}$点为士兵所在点，$\bold{\color{purple}\text{紫色}}$点为士兵的监控范围点）

我们惊奇地发现，覆盖区域是一个**实心**的**菱形**！

也就是说，士兵观察到的范围，对每一行/列来说，都是**一段连续的区间**！
处理范围，是一个**区间修改**问题！

提到区间修改，大家会想到什么呢？

线段树？……树状数组？……**差分**！

众所周知，差分在区间修改问题中有奇效，原因是它只需要改——**两个点**（不知道为啥？[翻我之前题解去](https://www.luogu.com.cn/blog/ravenclawyangrunze/solution-at2442)，you can also 翻我[小伙伴的题解](https://www.luogu.com.cn/blog/yuan-xin/solution-p3368)），
我们只需要**在左端点的位置$+1$，右端点$+1$的位置$-1$**


而且，既然区域是个菱形，我们可别忘了**菱形的对称性**，也就是说，我们找到一个点之后，**我们可以根据它的两条对称轴找到它的三个对应点**

也就是说，我们能在$O(a)$的时间内求出一个士兵的监控范围，处理这一块的总复杂度为$O(amn)$，不错不错~

我这里采用的是**从中心向四周扩展**的方式——也就是说**枚举当前点到中心的距离进行修改**

![](https://cdn.luogu.com.cn/upload/image_hosting/d6ftwm1m.png)

（图中，$\bold{\color{green}\text{绿色}}$点为修改的左端点，$\bold{\color{orange}\text{橙色}}$点为修改的右端点，为了符合我们OIer的坐标书写习惯，$x$轴正方向为下方，$y$轴正方向为右方）

结合着这个图，你就可以理解下方的代码惹~

在写代码之前，我再bb两句：

1. 差分修改时**右端点别忘了加1**！！！！！
2. 注意边界的问题，**如果超范围了，那就把修改加到边界上**（比如右端点为$n+3$，超范围了，那就把这一块的修改改成$n$，左端点同理）

```cpp
bool look[355][355];//look为能不能看到
int tag[355][355];//tag就是差分数组
void lookaround(int x,int y,int k){//x,y为士兵的坐标，k就是士兵的a值
	for(int i=0;i<=k;i++){//从里向外扩展（由于我们调用的时候已经把k减1了，所以我们这里就是<=k，这样很好写）
		//利用刚才找到的规律进行修改吧！
		//如果理解不了，自己再画图找规律
		tag[max(x-i,1)][max(y-(k-i),1)]++; 
		tag[max(x-i,1)][min(y+(k-i),m)+1]--;
		tag[min(x+i,n)][max(y-(k-i),1)]++;
		tag[min(x+i,n)][min(y+(k-i),m)+1]--;
		//最后别忘了：注 意 细 节
	}
}
```
那我们如何用tag数组判断一个点是否在士兵的监视范围之内呢？

别忘了：**差分的前缀和就是它本身**！（自己根据差分和前缀和的定义推一下？）

也就是说，我们对tag数组求一遍前缀和，只要这个和$>0$，就能被看到啦！

我们只需要在main函数里加上这几句：

```cpp
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=1;j<=m;j++){
			sum+=tag[i][j];	//就是一个前缀和
			if(sum>0)look[i][j]=1;	
		}
	}	
```


------------
接下来，就是我们的重头戏——**广搜**的过程啦！

其实只要注意一些细节啥的，广搜根本就不难写

（本题解沿用了vectorwyx同学提供的思路，让我们一起感谢他！）

起初，神创造**bfs**。

队列是空虚混沌，渊面黑暗；神的灵运行在**队首**上。
```cpp
while(!q.empty()){
		qwq fro=q.front();
		q.pop();
   		if(fro.s>ans.s)continue;//最优性剪枝！一定要加上不然会T
		if(fro.x==ex&&fro.y==ey){//找到重点
			ans=minq(ans,fro);//更新最优解
			continue;//之后就没必要搜啦
		}      
		//do something……
}
```

神说：“要有**方向数组**”，就有了方向数组。

```cpp
const int dx[8]={1,0,-1,0,1,-1,-1,1},dy[8]={0,1,0,-1,1,1,-1,-1};//八连通的方向数组
//为了方便瞬移操作，前四个是上下左右，后四个是斜线
```
神看**瞬移**是好的，就把**方向数组的前后**分开了。有晚上，有早晨，是第一日。

```cpp
		for(int i=0;i<8;i++){//不瞬移，按照八连通方向
        int nx=fro.x+dx[i];//沿着方向数组走
			int ny=fro.y+dy[i];
			//do something...
		}
		if(fro.sy+1>c2)continue;//在瞬移之前，先看看能不能再使用瞬移
		for(int i=0;i<4;i++){//瞬移只能走上下左右
     	  int nx=fro.x+dx[i]*d;//一次可以走d格
			 int ny=fro.y+dy[i]*d;   
			//do something...
		}
```
　神说，**士兵的监控范围内要隐身**，神就造出判断条件，将隐身的处理，不隐身的处理分开了。事就这样成了。
 
 ```cpp
 	if(look[nx][ny]){//如果要走的地方在士兵的监控范围内，需要隐身
		if(vis[nx][ny][fro.yx+1][fro.sy]||fro.yx+1>c1)continue;//如果这个状态到过了，或者超过了隐身使用次数，continue
		vis[nx][ny][fro.yx+1][fro.sy]=1;//vis变为1
		q.push((qwq){nx,ny,fro.yx+1,fro.sy,fro.s+1});//push进去的时候别忘了把隐身次数+1
	}
	else{//不需要隐身就不用判断隐身的使用次数，隐身数也不用+1
		if(vis[nx][ny][fro.yx][fro.sy])continue;
		vis[nx][ny][fro.yx][fro.sy]=1;
		q.push((qwq){nx,ny,fro.yx,fro.sy,fro.s+1});				
	}
   //瞬移的也如法炮制，只要记得把瞬移数+1就OK 
 ```
 神又加了**防止越界的措施**，有晚上，有早晨，是第二日。
 ```cpp
 	if(nx<1||nx>n||ny<1||ny>m||map[nx][ny]>0)continue;//如果越界了/这个位置是士兵，不能走
 ```
$\cdots\cdots$

不行了不行了我编不下去惹……咱们直接来看完整代码吧！

```cpp
void bfs(){
	while(!q.empty()){
		qwq fro=q.front();//取队首
		q.pop();//pop
		if(fro.s>ans.s)continue;//最优性剪枝
		if(fro.x==ex&&fro.y==ey){//判断终点
			ans=minq(ans,fro);//更新答案
			continue;
		} 
		for(int i=0;i<8;i++){
			int nx=fro.x+dx[i];
			int ny=fro.y+dy[i];
			if(nx<1||nx>n||ny<1||ny>m||map[nx][ny]>0)continue;
			if(look[nx][ny]){//不瞬移+隐身
				if(vis[nx][ny][fro.yx+1][fro.sy]||fro.yx+1>c1)continue;
				vis[nx][ny][fro.yx+1][fro.sy]=1;
				q.push((qwq){nx,ny,fro.yx+1,fro.sy,fro.s+1});
			}
			else{//不瞬移+不隐身
				if(vis[nx][ny][fro.yx][fro.sy])continue;
				vis[nx][ny][fro.yx][fro.sy]=1;
				q.push((qwq){nx,ny,fro.yx,fro.sy,fro.s+1});				
			}
		}
		if(fro.sy+1>c2)continue;
		for(int i=0;i<4;i++){
			int nx=fro.x+dx[i]*d;
			int ny=fro.y+dy[i]*d;
			if(nx<1||nx>n||ny<1||ny>m||map[nx][ny]>0)continue;
			if(look[nx][ny]){//瞬移+隐身
				if(vis[nx][ny][fro.yx+1][fro.sy+1]||fro.yx+1>c1)continue;
				vis[nx][ny][fro.yx+1][fro.sy+1]=1;
				q.push((qwq){nx,ny,fro.yx+1,fro.sy+1,fro.s+1});
			}
			else{//瞬移+不隐身
				if(vis[nx][ny][fro.yx][fro.sy+1])continue;
				vis[nx][ny][fro.yx][fro.sy+1]=1;
				q.push((qwq){nx,ny,fro.yx,fro.sy+1,fro.s+1});				
			}			
		}
	}
```


------------
所有的地方都讲完啦！我们来看看完整代码吧！

**注意：如果你的代码被卡常而TLE了，请用 C艹17 吸氧提交**

（据说是因为新版本的编译器用 STL 会更快？）

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct qwq{//qwq结构体
	int x,y,yx,sy,s;
};
qwq minq(qwq a,qwq b){//找最优解
	if(a.s!=b.s)return a.s<b.s?a:b;
	if(a.yx+a.sy!=b.yx+b.sy)return a.yx+a.sy<b.yx+b.sy?a:b;
	return a.yx<b.yx?a:b;
}
bool vis[355][355][20][20],look[355][355];//一堆杂七杂八的东西
int tag[355][355];
int n,m,c1,c2,d;
int map[355][355];
const int dx[8]={1,0,-1,0,1,-1,-1,1},dy[8]={0,1,0,-1,1,1,-1,-1};
void lookaround(int x,int y,int k){//处理看到的范围（差分数组tag）
	for(int i=0;i<=k;i++){
		tag[max(x-i,1)][max(y-(k-i),1)]++; 
		tag[max(x-i,1)][min(y+(k-i),m)+1]--;
		tag[min(x+i,n)][max(y-(k-i),1)]++;
		tag[min(x+i,n)][min(y+(k-i),m)+1]--;
	}
}
int sx,sy,ex,ey;
queue <qwq> q;//队列
qwq ans=(qwq){0,0,233333333,233333333,233333333};
void bfs(){//广搜
	while(!q.empty()){
		qwq fro=q.front();
		q.pop();
		if(fro.s>ans.s)continue;
		if(fro.x==ex&&fro.y==ey){
			ans=minq(ans,fro);
			continue;
		} 
		for(int i=0;i<8;i++){
			int nx=fro.x+dx[i];
			int ny=fro.y+dy[i];
			if(nx<1||nx>n||ny<1||ny>m||map[nx][ny]>0)continue;
			if(look[nx][ny]){
				if(vis[nx][ny][fro.yx+1][fro.sy]||fro.yx+1>c1)continue;
				vis[nx][ny][fro.yx+1][fro.sy]=1;
				q.push((qwq){nx,ny,fro.yx+1,fro.sy,fro.s+1});
			}
			else{
				if(vis[nx][ny][fro.yx][fro.sy])continue;
				vis[nx][ny][fro.yx][fro.sy]=1;
				q.push((qwq){nx,ny,fro.yx,fro.sy,fro.s+1});				
			}
		}
		if(fro.sy+1>c2)continue;
		for(int i=0;i<4;i++){
			int nx=fro.x+dx[i]*d;
			int ny=fro.y+dy[i]*d;
			if(nx<1||nx>n||ny<1||ny>m||map[nx][ny]>0)continue;
			if(look[nx][ny]){
				if(vis[nx][ny][fro.yx+1][fro.sy+1]||fro.yx+1>c1)continue;
				vis[nx][ny][fro.yx+1][fro.sy+1]=1;
				q.push((qwq){nx,ny,fro.yx+1,fro.sy+1,fro.s+1});
			}
			else{
				if(vis[nx][ny][fro.yx][fro.sy+1])continue;
				vis[nx][ny][fro.yx][fro.sy+1]=1;
				q.push((qwq){nx,ny,fro.yx,fro.sy+1,fro.s+1});				
			}			
		}
	}
}
int main(){//main函数
    ios::sync_with_stdio(false);
	cin>>n>>m>>c1>>c2>>d;
	for(int i=1;i<=n;i++){//输入+处理
		for(int j=1;j<=m;j++){
			string s;
			cin>>s;
			if(s[0]=='S'){
				sx=i,sy=j;
				map[i][j]=-1;
				q.push((qwq){sx,sy,0,0,0});
				vis[i][j][0][0]=1;
			}
			else if(s[0]=='T'){
				ex=i,ey=j;
				map[i][j]=-2;
			}
			else if(s[0]=='.')map[i][j]=0;
			else{
				int x=0;
				for(int i=0;i<s.size();i++)
				x=(x<<1)+(x<<3)+(s[i]^'0');
				map[i][j]=x;
				lookaround(i,j,x-1);
			}
		}
	}
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=1;j<=m;j++){
			sum+=tag[i][j];	//求出look数组（前缀和）
			if(sum>0)look[i][j]=1;	
		}
	}	
	bfs();//广搜
	if(ans.s==233333333)printf("-1");
	else printf("%d %d %d",ans.s,ans.yx,ans.sy);//最后输出
	return 0;
}
```


------------
$\huge{\mathscr{\color{magenta}THE}}$
$\huge{\mathscr{\color{springgreen}END}}$

（顺便祝大家开学快乐鸭www）


---

## 作者：hensier (赞：38)

本题的核心思想为 $\text{\color{red}{BFS + 差分}}$。

【基本思路】

这道题是一道 $\text{BFS}$ 题目，为了方便，我们不妨把队列设为结构体类型，同时保存横纵坐标，移动次数以及两个技能的次数（$30$ 分算法中保存的是剩余次数，其他的是使用次数）。

地图的输入可以用一个二维字符串数组实现。我们对于每一个字符串可进行判断：

![](https://cdn.luogu.com.cn/upload/image_hosting/cviiolgn.png)

特别地，对于一个士兵，我们可以新建另一个数组，每一个元素保存该位置是否被士兵控制。我们还可以再新建一个数组来保存士兵的范围（如果当前位置不是士兵就视为默认，即 $0$）。

接下来，我们就可以开始 $\text{BFS}$ 了。在进行若干次拓展之后，我们取其最优，然后输出结果。如果没有结果，则输出 `-1`即可。

以下的代码均以 `C++` 为主，`Pascal` 代码可以到本文底部获取，下面将不再赘述。

【$30$ 分算法】

先输入矩阵。对于士兵，进行一个 $\mathcal O(nm)$ 的外层循环寻找士兵，再进行一个 $\mathcal O(nm)$的内层循环，标记士兵范围。以下为内层循环的函数：

```cpp
void find(int x,int y,int z)
{
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
        {
            if(abs(i-x)+abs(j-y)<z)
            {
                newmap[i][j]="#";
                //标记为#就表示该处为士兵可观测范围，士兵本身用/标记
            }
        }
    }
}
```

维护一个队列并不断拓展，会有以下四种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/55wnu0w3.png)

事实上，上述的优先级是从上到下的——不使用技能是最好的，其次是瞬移、隐身和同时使用：

> 在所用时间相同情况下，荆轲希望使用的两种技能总次数尽可能少；在所用时间与技能次数相同情况下，荆轲希望使用的隐身次数尽可能少。

按照这个顺序，我们一一进行拓展即可，最终只要到了秦王所在的格子就输出结果。
该算法其实是存在很多问题的，因为最优结果不一定是最先找到的，所以这样会导致 $\text{WA}$。而 $\text{RE}$ 可能是因为数组元素量不够大导致的。$\text{TLE}$ 可能是由于多种因素导致的，我们要逐个解决。

【$95$ 分算法】

本算法需要改进的地方：

- 考虑最优情况，而不是最先遍历的情况

- 尽量减少程序运行的时间，进行有必要的剪枝

输入不提。我们可以考虑在士兵控制范围方面做一些改进，之前的内层循环是从 $1$ 到 $n$ ，从 $1$ 到 $m$ 的，但其实这都是不必要的。

注意，下图用平面直角坐标系演示，但本蒟蒻的所有程序均以从上到下从左到右来写，但下面均以平面直角坐标系的顺序为准。

假如一个士兵位于 $A(5,4)$，且数值为 $4$。则它的水平、竖直方向与其相差 $\lt 4$ 格的均可被其看到，而根据曼哈顿距离的性质，一个士兵最终的可视范围就是一个正方形，而且这个正方形的对角线长为 $2(x-1)$（以下称 $x$ 为其数值，即范围），而边长为 $\sqrt{2}(x-1)$（~~知道这些好像也没啥用~~）。

这个可以观测到的点就是在这个正方形内部（包括边和士兵本身），如下图所示的棕色区域：

![](https://cdn.luogu.com.cn/upload/image_hosting/5gb1jiin.png)

【从特殊到一般】

对于任意一个位于 $\text{city}_{i,j}$（以下称输入的地图为 $\text{city}$）的士兵，它所形成的正方形的四个点分别为（假如为 $B,C,D,E$）：

$$B(\max(1,i-x),j)$$
$$C(i,\max(1,j-x))$$
$$D(\min(n,i+x),j)$$
$$E(i,\min(m,j+x))$$

因为地图上的坐标不可能为非正，所以我们要进行特判，即用 $\max,\min$ 进行修正。

这样，我们就可以直接进行下列的循环：

```cpp
for(int x=max(1,i-d);x<=min(n,i+d);x++)
{
    for(int y=max(1,j-d);y<=min(m,j+d);y++)
    {
        if(abs(x-i)+abs(y-j)<d)
        {
            flag[x][y]=true;
        }
    }
}
```

考虑完这个之后，我们就直接进入搜索。我们不妨定义一个 $\text{ans}$ 的 $\text{node}$ 类型，使得：

```cpp
ans=(node){0,0,0x7fffff,0x7fffff,0x7fffff};
//x,y 坐标均为 0，步数、隐身和瞬移总使用次数均为 0x7fffff（即 int_max）
```

如果能到达就进行替换。最后只需判断 $\text{ans.x} $ 是否为 $0$ 即可知道是否能到达终点。

在搜索的过程中，我们可以将四种拓展情况进行改动，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/qeya26av.png)

当然，我们可以定义一个四维 $\text{visit}$ 数组，第一、二下标代表坐标，第三、四坐标分别表示隐身和瞬移的次数。如果重复就不到这个位置——这样能节省时间。

每一次到达终点 $T$ 后要检查一下是否可以替换掉当前的 $\text{ans}$：

```cpp
bool check(node a,node b)
{
    if(a.step!=b.step)return a.step<b.step;
    if(a.hide+a.move!=b.hide+b.move)return a.hide+a.move<b.hide+b.move;
    return a.hide<b.hide;
}
```

把细节注意好了之后（~~包括要把队列数组开到一千万以上~~），就可以[拿到 95 分](/record/33611827)了（一个点 $\text{TLE}$）。

【$100$ 分算法】

现在唯一可以优化的地方就是士兵观测范围了。这里要用到差分，我们用差分可以有效地解决曼哈顿距离的相关问题。当然下列数组的操作都在新维护的数组 $\text{dif}$ 中实现。

![](https://cdn.luogu.com.cn/upload/image_hosting/v60sldq5.png)

如上图，我们可以在红色正方形内进行操作。曼哈顿距离必定小于 $x$，所以我们不妨进行一个 $i∈[0,x)$ 循环，进行下列操作：

- 上方 $i$ 格，左方 $k-i-1$ 格的位置数值加 $1$

- 上方 $i$ 格，右方 $k-i$ 格的位置数值减 $1$

- 下方 $i$ 格，左方 $k-i-1$ 格的位置数值加 $1$

- 下方 $i$ 格，右方 $k-i$ 格的位置数值减 $1$

这样就能够快速地对周围的格子进行墨水扩散式的遍历，对于每一行，我们不停地求和，然后对于这一行中的每一个元素，如果当前的和大于 $0$，则该格处于观测范围以内：

![](https://cdn.luogu.com.cn/upload/image_hosting/19ya6r7t.png)

动画演示：

![](https://i.loli.net/2020/05/17/cuqpBHRhJPw7fNe.gif)

我们可以发现，可观测到的点恰位于正方形内（包括边）。

实现：

```cpp
void find(int x,int y,int k)
{
    for(int i=0;i<k;i++)
    {
        dif[max(1,x-i)][max(1,y-k+i+1)]++;
        dif[max(1,x-i)][min(m,y+k-i-1)+1]--;
        dif[min(n,x+i)][max(1,y-k+i+1)]++;
        dif[min(n,x+i)][min(m,y+k-i-1)+1]--;
    }
}
```

当然这个差分数组还需使用：

```cpp
for(int i=1;i<=n;i++)//对每一行进行操作
{
    int sum=0;//初始化和
    for(int j=1;j<=m;j++)
    {
        sum+=dif[i][j];//累加
        if(sum>0)flag[i][j]=true;//此时和若大于 0 则标记为真
    }
}
```

以下是本蒟蒻第一次 [AC](/record/33617923) 的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c1,c2,d,ex,ey,city[351][351],dif[351][351],dx[]={-1,0,0,1,-1,-1,1,1},dy[]={0,-1,1,0,-1,1,-1,1};
bool flag[351][351],visit[351][351][16][16];
//ex,ey 为结束点，city 保存士兵的范围（没有士兵则为 0），dif 为差分维护数组
//flag 为士兵观测数组，visit 为访问数组
struct node
{
    int x,y,step,hide,move;
}q[12500001],ans=(node){0,0,0x7fffffff,0x7fffffff,0x7fffffff};
//q 为队列，ans 为最终答案
void find(int x,int y,int k)//差分
{
    for(int i=0;i<k;i++)
    {
        dif[max(1,x-i)][max(1,y-k+i+1)]++;
        dif[max(1,x-i)][min(m,y+k-i-1)+1]--;
        dif[min(n,x+i)][max(1,y-k+i+1)]++;
        dif[min(n,x+i)][min(m,y+k-i-1)+1]--;
    }
}
void input()//输入
{
    cin>>n>>m>>c1>>c2>>d;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            string s;
            cin>>s;
            switch(s[0])
            {
                case 'S'://直接加入队首
                {
                    q[1].x=i;
                    q[1].y=j;
                    break;
                }
                case 'T'://标记终点
                {
                    ex=i;
                    ey=j;
                    break;
                }
                case '.':break;//初始化为 0，所以是点的话不需操作
                default:
                {
                    for(int pos=0;s[pos];pos++)city[i][j]=(city[i][j]<<3)+(city[i][j]<<1)+(s[pos]^'0');
                    find(i,j,city[i][j]);
                    //士兵操作：1、标记，2、差分
                }
            }
        }
    }
}
bool check(node a,node b)//check 函数，判断当前答案是否优于 ans
{
    if(a.step!=b.step)return a.step<b.step;
    if(a.hide+a.move!=b.hide+b.move)return a.hide+a.move<b.hide+b.move;
    return a.hide<b.hide;
}
void bfs()
{
    int front=1,rear=1;
    while(front<=rear)
    {
        node nf=q[front];
        if(nf.step>ans.step)//此步很重要！有剪枝的效果，可节约大量时间
        {
            front++;
            continue;
        }
        for(int i=0;i<8;i++)
        {
            int nx=nf.x+dx[i],ny=nf.y+dy[i];
            if(nx<1||ny<1||nx>n||ny>m||city[nx][ny])continue;//判断出边界或已访问
            if(flag[nx][ny])//隐身
            {
                if(nf.hide>=c1||visit[nx][ny][nf.hide+1][nf.move])continue;
                visit[nx][ny][nf.hide+1][nf.move]=true;
                q[++rear]=(node){nx,ny,nf.step+1,nf.hide+1,nf.move};//入队
                if(nx==ex&&ny==ey&&check(q[rear],ans))ans=q[rear];//替换答案
            }
            else//不用技能
            {
                if(visit[nx][ny][nf.hide][nf.move])continue;
                visit[nx][ny][nf.hide][nf.move]=true;
                q[++rear]=(node){nx,ny,nf.step+1,nf.hide,nf.move};
                if(nx==ex&&ny==ey&&check(q[rear],ans))ans=q[rear];
            }
        }
        for(int i=0;i<4;i++)
        {
            int nx=nf.x+dx[i]*d,ny=nf.y+dy[i]*d;
            if(nx<1||ny<1||nx>n||ny>m||city[nx][ny])continue;
            if(flag[nx][ny])//瞬移 + 隐身
            {
                if(nf.hide>=c1||nf.move>=c2||visit[nx][ny][nf.hide+1][nf.move+1])continue;
                visit[nx][ny][nf.hide+1][nf.move+1]=true;
                q[++rear]=(node){nx,ny,nf.step+1,nf.hide+1,nf.move+1};
                if(nx==ex&&ny==ey&&check(q[rear],ans))ans=q[rear];
            }
            else//瞬移
            {
                if(nf.move>=c2||visit[nx][ny][nf.hide][nf.move+1])continue;
                visit[nx][ny][nf.hide][nf.move+1]=true;
                q[++rear]=(node){nx,ny,nf.step+1,nf.hide,nf.move+1};
                if(nx==ex&&ny==ey&&check(q[rear],ans))ans=q[rear];
            }
        }
        front++;//队首下标加 1
    }
}
int main()
{
    input();
    for(int i=1;i<=n;i++)//差分
    {
        int sum=0;
        for(int j=1;j<=m;j++)
        {
            sum+=dif[i][j];
            if(sum>0)flag[i][j]=true;
        }
    }
    bfs();//搜索
    if(!ans.x)puts("-1");//没有答案就输出-1
    else printf("%d %d %d\n",ans.step,ans.hide,ans.move);//输出步数，隐身次数和瞬移次数
    return 0;
}
```

【动图演示】

动图中，`S` 表示荆轲。当 `S` 外有黑框时，则代表隐身。箭头代表瞬移操作。$\text{Impossible!}$ 表示无法成功刺杀秦王。查看动图：

样例 $1$：

![](https://i.loli.net/2020/05/31/9ZLE8NJsnDF5tau.gif)

样例 $2$：

![](https://i.loli.net/2020/05/16/WtATlN9QEg3a2nj.gif)

样例 $3$：

![](https://i.loli.net/2020/05/16/YuHKpcoNwjMTWLE.gif)

其余内容请看[此处](/paste/zarnp0th)。

---

## 作者：LanrTabe (赞：15)

[官方视频题解](https://mp.weixin.qq.com/s?__biz=MjM5MTY5ODE4OQ==&mid=2651461297&idx=3&sn=5a5f4a3dcb4bd2063e1e6e5c49d2b7c1)

[My Blog](https://www.cnblogs.com/LanrTabe/p/12781938.html)

设 $Dis[i][j][u1][u2]$ 表示起点到达点 $(i,j)$，使用了 $u1$ 次隐身，$u2$ 次瞬移的最短时间，$Sx,Sy,Tx,Ty$ 分别表示起点和终点的坐标。

那么起点就是 $(Sx,Sy,0,0)$，然后使用 BFS 求最短时间，每一次枚举下一个坐标，是否隐身及瞬移，最后在所有能够到达的 $(Tx,Ty,?,?)$中取最优即为答案。

### 预处理

在 BFS 的过程中我们需要知道一个点是否被卫兵所观察，如果每读入一个卫兵就暴力修改的话时间复杂度最坏可以达到 $O(nma^2)$，显然会超时，那么需要进行优化。

方案 1：（官方题解）观察到一个卫兵所能观察到的点一定是一个菱形，那么枚举菱形的每一行就是覆盖连续的一段，这个可以用差分+前缀和解决，时间复杂度 $O(nma)$。

方案 2：（考场做法）把所有卫兵放入优先队列，每次取出 $a$ 最大的卫兵向四周覆盖（插入一个 $a-1$ 的卫兵，若之前这个点已经被 $a$ 更大的士兵覆盖则跳过），就是一个类似最短路的过程，时间复杂度 $O(nm\log(nm))$？

方案 3：对方案 2 进行优化，因为 $a$ 最大只有 $350$，那么可以开 $O(a)$ 个桶来维护卫兵，从高往低扫，时间复杂度 $O(nm)$。

### BFS

如果直接做的话复杂度就是 $O(n\times m\times c1\times c2\times 24)\approx 7.5\times 10^8$，其中 $24$ 表示 BFS 中每个状态转移的复杂度，显然跑 3s 还是有点吃力（本机 8s，~~或许CCF少爷机能过？~~）

优化 1：最优性等剪枝（~~但我没试过不知道有没有用~~ 没加这个T成 $95$）

优化 2：直接检查是否需要隐身，不需要枚举，因为不隐身显然更优，这样可以减去一个 $2$ 的常数且减去一些无用状态（虽然这很显然 ~~但是当时我没想到~~）

优化 3：~~卡常~~ 我当时没想到上述优化就选择了大力卡常，将 BFS 中的每一个状态 $(x,y,u1,u2)$ 通过位运算压缩到一个 int 中，并且将 $Dis$ 数组压成了一维，然后就是喜闻乐见的 register 及手写队列之类的（本机破i5 5s）

复杂度 $O(n\times m\times c1\times c2\times 12)\approx 3.7\times 10^8$ 并且跑不满，~~大概能过~~

### 代码：

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#define cint const int
#define rint register int

const int Inf=0x3f3f3f3f,Dx[]={-1,-1,-1,0,1,1,1,0},Dy[]={-1,0,1,1,1,0,-1,-1};
int n,m,c1,c2,D,Sx,Sy,Tx,Ty,Md=Inf;
int s[355][355],ss[355][355],Dis[50000005],q[35000005],qh,qt;
//s[i][j]表示是否被卫兵观察，ss[i][j]表示是否有卫兵，Dis[i]表示最短时间，q[i]为BFS队列
char r[15];

struct Cr{int x,y,a;inline bool operator<(const Cr& o)const{return a<o.a;}};
#define H(a,b,c,d) (((a)<<17)|((b)<<8)|((c)<<4)|(d))
//状态压缩函数

int Get()//读入一个点
{
    scanf("%s",r);
    if(*r=='.')return 0;
    if(*r=='S')return -1;
    if(*r=='T')return -2;
    int a=0,l=strlen(r);
    for(int i=0;i<l;++i)a=a*10+(r[i]^48);
    return a;
}

void PCover()
//预处理，用的是优先队列的版本
{
    std::priority_queue<Cr> q;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(s[i][j]>0)
                q.push((Cr){i,j,s[i][j]});
    for(int x,y,a;!q.empty();)
    {
        x=q.top().x,y=q.top().y,a=q.top().a,q.pop();
        if(s[x][y]>a)continue;
        for(int i=1,nx,ny;i<8;i+=2)
        {
            nx=x+Dx[i],ny=y+Dy[i];
            if(nx<1||nx>n||ny<1||ny>m||s[nx][ny]>=a-1)continue;
            q.push((Cr){nx,ny,s[nx][ny]=a-1});
        }
    }
}

void BFS()
{
    memset(Dis,0x3f,sizeof Dis),Dis[q[0]=H(Sx,Sy,0,0)]=0;
    for(rint x,y,u1,u2,d,Nv,Wv;qh<=qt;)
    {
        Nv=q[qh++],x=Nv>>17,y=Nv>>8&0x1ff,u1=Nv>>4&0xf,u2=Nv&0xf,d=Dis[Nv];
        //取出队首并且解压缩
        if(d>=Md||ss[x][y]>0)continue;
        if(x==Tx&&y==Ty)Md=d;//最优性剪枝
        for(rint i=0,nx,ny,j;i<8;++i)
        {
            nx=x+Dx[i],ny=y+Dy[i];
            if(nx<1||nx>n||ny<1||ny>m)continue;
            j=s[nx][ny]>0;//是否需要隐身
            if(u1+j<=c1&&Dis[Wv=H(nx,ny,u1+j,u2)]>d+1)Dis[q[++qt]=Wv]=d+1;
            if(i&1)//瞬移技能
            {
                nx=x+Dx[i]*D,ny=y+Dy[i]*D;
                if(nx<1||nx>n||ny<1||ny>m)continue;
                j=s[nx][ny]>0;
                if(u1+j<=c1&&u2+1<=c2&&Dis[Wv=H(nx,ny,u1+j,u2+1)]>d+1)Dis[q[++qt]=Wv]=d+1;
            }
        }
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("bandit.out","w",stdout);
    scanf("%d%d%d%d%d",&n,&m,&c1,&c2,&D);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if((ss[i][j]=s[i][j]=Get())==-1)Sx=i,Sy=j;
            else if(s[i][j]==-2)Tx=i,Ty=j;
    PCover(),BFS();
    rint A1=Inf,A2=Inf,A3=Inf,d;
    for(rint i=0;i<=c1;++i)
        for(rint j=0;j<=c2;++j)
            if((d=Dis[H(Tx,Ty,i,j)])<A1||(d==A1&&i+j<A2+A3)||(d==A1&&i+j==A2+A3&&i<A2))
                A1=d,A2=i,A3=j;
    if(A1==Inf)puts("-1");
    else printf("%d %d %d\n",A1,A2,A3);
    return 0;
}
```

---

## 作者：Macesuted (赞：7)

[题面](https://www.luogu.com.cn/problem/P6474)

## 题目大意

给定一张$n*m$的地图，包含有一个起点及一个终点，询问从起点到终点的最优路线。

其中人物的运动方法有两种，第一可以用正常的走法，可以向八个方向移动一格；第二可以用瞬移，我们使用一次瞬移技能就可以向四个方向移动$d$格。

分析阻挡人物运动的因素，第一就是人物不能超出地图边界（如果你的瞬移会导致你的坐标超出边界，这一次瞬移并不会进行而不是会瞬移到墙边）；第二就是落地时不能站在守卫的头上（但是我们可以用瞬移从守卫头上飞过去）；第三就是如果你落地时所在方块处在守卫的视野中（不需要考虑多少守卫的视野中），你需要立即使用一次隐身技能。

## 分析

读完题目我们很自然就会想到BFS，或者是带有`priority_queue`的Dijkstra，在这方面上的处理并不困难，每一次只要对当前状态进行扩展（即人物移动）即可。

**但是我们同样遇到了一些难题。**

**第一**，士兵的视野范围处理。

由于按照题目描述，士兵的视野范围看的是曼哈顿距离，所以他的视野范围画出来大概是这样的（视野为4）
```
   *
  ***
 *****
***4***
 *****
  ***
   *
```
~~*小学时打了无数次的绘制图形题终于派上用场了*~~

我这里使用的是差分方法，对于每一行在开头处$+1$，结尾处$-1$，最后$O(n^2)$前缀和处理，直接访问数组就可以得知当前坐标是否在士兵视野中。

当然，如果暴力直接在数组上扫出整个图形应该也不会超时（~~没有试过~~）。

**第二**，输入

输入的$n*m$的矩阵，跟平常不同。这个矩阵中又有数字又有字符的，应该如何处理。

看到有人用`cin`来解决，可能会方便一点，我这里采用更快的`getchar`写法。对于字符，只需正常`getchar`，对于数字么，用高精度输入的方法处理就可以了。（~~代码略微繁琐~~）

## 代码

我使用的是Dijkstra，其中$visit[i][j]$存放的是在坐标为$(i,j)$时所剩技能最优的情况。因为我们用的是`priority_queue`，所以显然先出队的一定是更优的情况。如果此时堆顶状态比$visit[i][j]$更差或相同，而显然这个$visit[i][j]$在达到时用时比现在更少，显然当前状态一定劣于那时的状态，直接`continue`。

而且由于使用的`priority_queue`会使先出队的更优，所以在搜到答案时直接输出即可，因为当前状态一定是所有达到终点的状态中最优的。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> cmptype; //visit数组所保存的类型

struct type
{
    int x, y, st1, st2, t;
    inline bool operator>(type b) const //优先队列要用
    {
        return (t > b.t || (t == b.t && (st1 + st2) > (b.st1 + b.st2)) || (t == b.t && (st1 + st2) == (b.st1 + b.st2) && st1 > b.st1));
    }
};

//方向数组
const int wayx[4] = {0, 0, 1, -1}, wayy[4] = {1, -1, 0, 0};
const int walkx[8] = {-1, -1, -1, 0, 1, 1, 1, 0}, walky[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

char room[355][355], tree[355][355];                    //地图和守卫视线标记
int startx, starty, endx, endy;                         //起点和终点
int n, m, c1, c2, d;                                    //输入的五项
cmptype visit[355][355];                                //visit数组
priority_queue<type, vector<type>, greater<type> > que; //优先队列

int main()
{
    scanf("%d%d%d%d%d", &n, &m, &c1, &c2, &d);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            room[i][j] = getchar();
            while (room[i][j] != 'S' && room[i][j] != 'T' && room[i][j] != '.' && (room[i][j] < '1' || room[i][j] > '9'))
                room[i][j] = getchar(); //getchar读法
            if (room[i][j] == 'S')      //起点
            {
                startx = i;
                starty = j;
                room[i][j] = '.';
            }
            if (room[i][j] == 'T') //终点
            {
                endx = i;
                endy = j;
                room[i][j] = '.';
            }
            if (room[i][j] >= '1' && room[i][j] <= '9')
            { //高精输入
                int t = room[i][j] - '0';
                room[i][j] = '#';
                char c = getchar();
                while (c >= '0' && c <= '9')
                {
                    t = t * 10 + c - '0';
                    c = getchar();
                }
                for (int x = max(1, i - t + 1); x <= min(n, i + t - 1); x++)
                { //视野的标记（差分）
                    tree[x][max(1, j - t + 1 + abs(x - i))]++;
                    tree[x][min(m + 1, j + t - abs(x - i))]--;
                }
            }
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            tree[i][j] += tree[i][j - 1]; //对差分数组进行前缀和，使其正常
    memset(visit, 0x7f, sizeof(visit));
    que.push((type){startx, starty, 0, 0, 0}); //初始状态
    while (!que.empty())
    {
        type cac = que.top();
        que.pop();
        if (cac.st1 > c1 || cac.st2 > c2) //技能使用数量超过限制
            continue;
        if (cac.x == endx && cac.y == endy) //如果到达了终点
        {                                   //由于是优先队列，可以直接结束
            printf("%d %d %d\n", cac.t, cac.st1, cac.st2);
            return 0;
        }
        if (visit[cac.x][cac.y] <= (cmptype){cac.st1 + cac.st2, cac.st1}) //如果比上次访问到这里是方案更差，直接退出
            continue;
        visit[cac.x][cac.y] = (cmptype){cac.st1 + cac.st2, cac.st1};
        for (int i = 0; i < 8; i++)
        { //向八个方向运动一格
            int x = cac.x + walkx[i], y = cac.y + walky[i];
            if (x < 1 || x > n || y < 1 || y > m)
                continue;
            if (room[x][y] != '.')
                continue;
            bool inarea = tree[x][y] > 0;
            que.push((type){x, y, cac.st1 + inarea, cac.st2, cac.t + 1});
        }
        for (int i = 0; i < 4; i++)
        { //向四个方向瞬移d格
            int x = cac.x + wayx[i] * d, y = cac.y + wayy[i] * d;
            if (x < 1 || x > n || y < 1 || y > m)
                continue;
            if (room[x][y] != '.')
                continue;
            bool inarea = tree[x][y] > 0;
            que.push((type){x, y, cac.st1 + inarea, cac.st2 + 1, cac.t + 1});
        }
    }
    puts("-1"); //没有路径
    return 0;
}
```

---

## 作者：Meatherm (赞：7)

前言：

将题面中部分的定义进行了**修改**。$(x,y)$ 表示地图中**第 $x$ 行第 $y$ 列**的格子。$(1,1)$ 是**左上角**坐标而**不是**左下角。

----

### 1. 处理卫兵的观察范围

对于一个在 $(x,y)$ ，观察距离为 $a$ 的卫兵，其观察范围如图所示（这是一个在 $(3,3)$ 且 $a=3$ 的卫兵）：

![](https://cdn.luogu.com.cn/upload/image_hosting/gl384fc0.png)

容易发现，对于每一个 $x-a < k < x+a$ 且 $1 \leq k \leq n$ 的 $k$，该卫兵可以观察到第 $k$ 行的第 $[y-a+1+|k-x|,y+a-1-|k-x|]$ 个格子。

但注意到可能出现负数，所以实际的观察范围是 $[\max\{1,y-a+1+|k-x|\},\min\{m,y+a-1-|k-x|\}]$。

我们可以使用差分数组 $sum_{i,j}$ 来维护。第 $i$ 行的第 $l$ 到 $r$ 个格子被观察到可以转化为 $sum_{i,l}$ 加上 $1$，$sum_{i,r+1}$ 减去 $1$。

将所有卫兵处理完毕后，对于 $(i,j)$ 这个格子，如果 $\sum\limits_{k=1}^{j} sum_{i,k}>0$，则它可以被卫兵观察到。

另外，在读入的过程中，我们也可以顺便记录起点坐标 $(sx,sy)$ 和终点坐标 $(tx,ty)$。

### 2. BFS

接下来就可以开始 BFS 了。设 $(x,y,va,vb)$ 表示到达格子 $(x,y)$，且使用了 $va$ 次隐身和 $vb$ 次瞬移。最初队列只有一个元素 $(sx,sy,0,0)$。

对于 $(x,y,va,vb)$，我们可以拓展出以下状态：

不使用瞬移：


- $(x,y+1,va,vb)$（如果 $(x,y+1)$ 在地图内且无法被卫兵观察到）
- $(x,y+1,va+1,vb)$（如果 $(x,y+1)$ 在地图内，被卫兵观察到且仍然有隐身次数）
- 其余七个方向同理

使用瞬移：


- $(x,y+d,va,vb+1)$（如果 $(x,y+d)$ 在地图内，无法被卫兵观察到，且仍然有瞬移次数）
- $(x,y+d,va+1,vb+1)$（如果 $(x,y+d)$ 在地图内，被卫兵观察到，且仍然有瞬移次数和隐身次数）
- 其余三个方向同理（**注意，根据题意，使用瞬移只能向四个方向移动**）

当然，如果其中的某个状态已经被拓展过了，根据 BFS 的性质，再次拓展这个状态显然不会使答案变优。我们可以使用一个辅助数组 $vis_{x,y,va,vb}$ 来记录某个状态是否被拓展过。当然，也需要使用数组 $dis_{x,y,va,vb}$ 来记录达到某个状态的最小时间。

尝试加入一些优化。如果某个状态已经用时间 $t$ 到达了终点，则不需要继续搜索所用时间已经 $>t$ 的状态。在洛谷上必须使用该优化，否则测试点 #18 会 TLE。


### 3. 判断答案

在所有**被拓展过的**，到达了 $(tx,ty)$ 的状态中，我们优先选取时间最小的，时间相同的选取技能总次数最小的，技能总次数相同选取隐身次数最小的，就可以求出答案了。

### 4. 关于 TLE

- 尝试使用 O2 优化
- 尝试使用手写队列（亲测优化效果不明显，也许效果因人而异）
- 尝试使用 C++ 17（不太明白此举的意义，不过一个解释说 STL 过慢是因为编译器版本较老）

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=352,INF=0x3f3f3f3f;
struct Node{
	int x,y;
	int va,vb;
	int t;
};
bool vis[N][N][17][17];
int dis[N][N][17][17];
Node q[30000000];
int Hd,Tl;
int n,m,ca,cb,d;
int v[N][N]; // 某个格子的状态
// 0 表示空地
//1 表示被观察到
//-1 表示是卫兵 不可访问
char s[N][N];
int sx,sy;
int tx,ty;
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
int sum[N][N];
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
inline bool isvis(Node v){ // 判断一个状态是否被拓展过
	return vis[v.x][v.y][v.va][v.vb];
}
inline void draw(Node v){ // 将该状态标记为访问过
	vis[v.x][v.y][v.va][v.vb]=true;
	return;
}
inline bool check(Node v){ // 判断某个状态是否合法
	return (v.x>=1&&v.x<=n&&v.y>=1&&v.y<=m&&v.va<=ca&&v.vb<=cb);
}
int main(void){
	n=read(),m=read(),ca=read(),cb=read(),d=read();
	for(rr int i=1;i<=n;++i){
		for(rr int j=1;j<=m;++j){
			std::string x;
			std::cin>>x;
			if(x=="."){ // 是空地 没有任何用
				;
			}else if(x=="T"){ // 是终点 / 起点 记录下坐标
				tx=i,ty=j;
			}else if(x=="S"){
				sx=i,sy=j;
			}else{
				v[i][j]=-1; // 标记不可访问
				int p=0;
				for(rr int k=0;k<(int)x.size();++k){ // 求出观察范围
					p=p*10+(x[k]-'0');
				}
				for(rr int k=1;k<=n;++k){
					if(k<i-p+1||k>i+p-1){ // 超出范围
						continue;
					}
					int l=std::max(1,(j-p+1)+abs(k-i)),
                    r=std::min(m,(j+p-1)-abs(k-i));
					++sum[k][l],--sum[k][r+1]; // 差分
				}
			}
		}
	}
	for(rr int i=1;i<=n;++i){
		int temp=0;
		for(rr int j=1;j<=m;++j){
			temp+=sum[i][j];
			if(!v[i][j]&&temp>0){
				v[i][j]=1;
			}
		}
	}
	++Hd;
	q[++Tl]=(Node){sx,sy,0,0,0};
	draw((Node){sx,sy,0,0}); // 起始状态入队
	int minxans=INF;// 到达终点的最小时间
	while(Hd<=Tl){
		Node temp=q[Hd];
		++Hd;

		Node New;
		dis[temp.x][temp.y][temp.va][temp.vb]=temp.t;
		if(temp.t>minxans){ // 优化
			continue;
		}
		if(temp.x==tx&&temp.y==ty){ // 更新到达终点的最小时间
			minxans=temp.t;
		}		
		for(rr int gx=-1;gx<=1;++gx){ // 拓展不用瞬移的 8 个方向
			for(rr int gy=-1;gy<=1;++gy){
				New=temp;
				New.x+=gx,New.y+=gy;
				++New.t;
				if(check(New)){ 
					if(v[New.x][New.y]==0&&!isvis(New)){// 可以不用技能
						q[++Tl]=New;
						draw(New);
					}
				}
				New=temp;
				New.x+=gx,New.y+=gy;
				++New.t;
				++New.va;
				if(check(New)){ 
					if(v[New.x][New.y]==1&&!isvis(New)){// 需要隐身
						q[++Tl]=New;
						draw(New);
					}
				}
			}
		}
		for(rr int i=0;i<4;++i){ // 使用瞬移的 4 个方向
			New=temp;
			New.x+=d*dx[i];
			New.y+=d*dy[i];
			++New.t;
			++New.vb;
			if(check(New)){
				if(v[New.x][New.y]==0&&!isvis(New)){ // 瞬移但不隐身
					q[++Tl]=New;
					draw(New);
				}
			}
			++New.va;
			if(check(New)){
				if(v[New.x][New.y]==1&&!isvis(New)){// 瞬移且隐身
					q[++Tl]=New;
					draw(New);
				}
			}
		}
	}
	int t=INF,ps=INF,ys=INF; // 最小时间 总次数 隐身次数
	for(rr int i=0;i<=ca;++i){
		for(rr int j=0;j<=cb;++j){
			if(vis[tx][ty][i][j]){
				if(t>dis[tx][ty][i][j]){ // 时间更加优秀
					t=dis[tx][ty][i][j];
					ps=i+j;
					ys=i;
				}else if(t==dis[tx][ty][i][j]&&(i+j)<ps){ // 时间相同 总次数更加优秀
					ps=i+j;
					ys=i;
				}else if(t==dis[tx][ty][i][j]&&(i+j)==ps&&i<ys){ // 时间 总次数都相同 隐身次数更加优秀
					ps=i+j;
					ys=i;
				}
			}
		}
	}
	if(t==INF) // 无解
		printf("-1");
	else
		printf("%d %d %d",t,ys,ps-ys);
	return 0;
}
```

---

## 作者：Veranda (赞：6)

## 本题解没有大数组和复杂的算法

这道题就是一个搜索题，只不过略加了一点东西。


#### 1.地图的处理

关于地图怎么处理，有些做法挺复杂，但我这里就用一种简单的做法吧，就是用一个字符串输入当前的数据，然后将原来的地图转化成一种$bool$值的安全图，就是将$char$类型的$map_{i,j}$转化成$bool$类型的$safe_{i,j}$，这样既节省了空间，又可以在时间上简单地判断哪个点能不能走

**注意**：在输入时由于有可能是多位数，所以要用字符串然后判断这个字符串的长度


#### 2.走法

本题有八种走法，就把原来的四种走路方式改成八种就可以了

#### 3.技能的处理

这是最关键的点，我们把技能看成像上下左右正常走的走法即可

1. 隐身

隐身就是只能向四个方向走但是不用考虑$safe$数组的情况，就是在判断点的时候只判断越界和访问过了没有即可，再写一个判断函数就行
```cpp
bool checkshoo(int x, int y) {
	if (x<1 || x>n || y<1 || y>m || vis[x][y]) return false;
	return true;
}
```
2.瞬移

我们把瞬移其实也可以当作一种走法，多走几步，在走路的$run$数组中加几个就可以了
```cpp
int run[12][2] = { {1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1},{d,0},{-d,0},{0,d},{0,-d} };
```

#### 4.技能的计数

在每个点的结构体中增加两个变量，即两种技能分别还可以用多少次

#### 5.技能的使用

1. 只用隐身，把朴素的BFS的$check()$函数改成新的判断函数即可

```cpp
if (Ns.u1 != 0) {
	for (int i = 0; i < 8; i++) {
		node Nt = Ns;
		Nt.x += run[i][0];
		Nt.y += run[i][1];
		Nt.step++;
		Nt.u1--;
		if (checkshoo(Nt.x, Nt.y)) {
			q.push(Nt);
			vis[Nt.x][Nt.y] = 1;
		}
	}
}
```


2.只用瞬移，单独走一下那几步就行

```cpp
if (Ns.u2 != 0) {
	for (int i = 8; i < 12; i++) {
		node Nt = Ns;
		Nt.x += run[i][0];
		Nt.y += run[i][1];
		Nt.step++;
		Nt.u2--;
		if (check(Nt.x, Nt.y)) {
			q.push(Nt);
			vis[Nt.x][Nt.y] = 1;
		}
	}
}
```



3.同时用两种技能，就是把瞬移的特殊走法结合特殊的判断函数就行



```cpp
if (Ns.u1 != 0 && Ns.u2 != 0) {
	for (int i = 8; i < 12; i++) {
		node Nt = Ns;
		Nt.x += run[i][0];
		Nt.y += run[i][1];
		Nt.step++;
		Nt.u2--;
		Nt.u1--;
		if (checkshoo(Nt.x, Nt.y)) {
			q.push(Nt);
			vis[Nt.x][Nt.y] = 1;
		}
	}
}
```
### 附上代码
```cpp
#include<iostream>
#include<cmath>
#include<queue>
#include<cstdio>
#include<string>
using namespace std;
struct node {
	int x, y;
	int u1, u2;
	int step;
};
struct ans {
	int t, u1, u2;
};
bool safe[370][370];
bool vis[370][370];
int n, m, c1, c2, d, sx, sy, fx, fy;
queue<node> q;
ans bfs();
bool check(int, int);
bool checkshoo(int, int);
int main() {
	//freopen("bandit.in", "r", stdin);
	//freopen("bandit.out", "w", stdout);
	cin >> n >> m >> c1 >> c2 >> d;
	string c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> c;
			if(c.size() == 1){
				if (c[0] == 'S') {
					sx = i; sy = j;
				}
				else if (c[0] == 'T') {
					fx = i; fy = j;
				}
				else if (c[0] == '.') {
					safe[i][j] = 0;
				}
				else {
					vis[i][j] = 1;
					safe[i][j] = 1;
					for (int k = 1; k <= n; k++) {
						for (int l = 1; l <= m; l++) {
							if (abs(k - i) + abs(l - j) < (c[0] - '0')) safe[k][l] = true;
						}
					}
				}
			}
			else{
				int w=0;
       			for(int x=0;x<c.size();x++){
          			w=w*10+c[x]-'0';
       			}
       			vis[i][j] = 1;
				safe[i][j] = 1;
				for (int k = 1; k <= n; k++) {
					for (int l = 1; l <= m; l++) {
						if (abs(k - i) + abs(l - j) < w) safe[k][l] = true;
					}
				}
			}
		}
	}

	//	cout<<endl;
	//	for(int i=1;i<=n;i++) {
	//		for(int j=1;j<=m;j++){
	//			cout<<safe[i][j]<<" ";
	//		}
	//		cout<<endl;
	//	}
	//	cout<<endl;

	node start;
	start.x = sx;
	start.y = sy;
	start.u1 = c1;
	start.u2 = c2;
	start.step = 0;
	q.push(start);
	ans t = bfs();
	if (t.u1 == 0x3f3f3f3f && t.u2 == 0x3f3f3f3f) cout << "-1";
	else {
		cout << t.t << " " << t.u1 << " " << t.u2;
	}
	return 0;
}
ans bfs() {
	int run[12][2] = { {1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1},{d,0},{-d,0},{0,d},{0,-d} };
	while (!q.empty()) {
		node Ns = q.front();
		q.pop();
		if (Ns.x == fx && Ns.y == fy) {
			ans answer;
			answer.t = Ns.step;
			answer.u1 = c1 - Ns.u1;
			answer.u2 = c2 - Ns.u2;
			return answer;
		}
		for (int i = 0; i < 8; i++) {
			node Nt = Ns;
			Nt.x += run[i][0];
			Nt.y += run[i][1];
			Nt.step++;
			if (check(Nt.x, Nt.y)) {
				q.push(Nt);
				vis[Nt.x][Nt.y] = 1;
			}
		}
		if (Ns.u1 != 0) {
			for (int i = 0; i < 8; i++) {
				node Nt = Ns;
				Nt.x += run[i][0];
				Nt.y += run[i][1];
				Nt.step++;
				Nt.u1--;
				if (checkshoo(Nt.x, Nt.y)) {
					q.push(Nt);
					vis[Nt.x][Nt.y] = 1;
				}
			}
		}
		if (Ns.u2 != 0) {
			for (int i = 8; i < 12; i++) {
				node Nt = Ns;
				Nt.x += run[i][0];
				Nt.y += run[i][1];
				Nt.step++;
				Nt.u2--;
				if (check(Nt.x, Nt.y)) {
					q.push(Nt);
					vis[Nt.x][Nt.y] = 1;
				}
			}
		}
		if (Ns.u1 != 0 && Ns.u2 != 0) {
			for (int i = 8; i < 12; i++) {
				node Nt = Ns;
				Nt.x += run[i][0];
				Nt.y += run[i][1];
				Nt.step++;
				Nt.u2--;
				Nt.u1--;
				if (checkshoo(Nt.x, Nt.y)) {
					q.push(Nt);
					vis[Nt.x][Nt.y] = 1;
				}
			}
		}
	}
	ans answer;
	answer.u1 = 0x3f3f3f3f;
	answer.u2 = 0x3f3f3f3f;
	answer.t = -1;
	return answer;
}
bool check(int x, int y) {
	if (x<1 || x>n || y<1 || y>m || safe[x][y] || vis[x][y]) return false;
	return true;
}
bool checkshoo(int x, int y) {
	if (x<1 || x>n || y<1 || y>m || vis[x][y]) return false;
	return true;
}
```

如有错误评论区提醒一下定会改正\
解释挺详细的吧QwQ\
数据没出来，分数待定，思路仅供参考。


Update:修复bug 感谢@老子是白菜提醒


---

## 作者：suxxsfe (赞：6)

**update.**  
被评论区大佬指出了一个笔误，已经修改，所以重新交了一遍  
~~话说我以前居然把所有 update 都写成了 updata/jk~~  

[在我的blog中查看](https://www.cnblogs.com/suxxsfe/p/12794613.html)  

[P6474 [NOI Online #2 入门组] 荆轲刺秦王](https://www.luogu.com.cn/problem/P6474)  

bfs+差分+卡常  
本来我其实是场内选手，但是因为记错提交时间，晚了半小时才交，交不上了，就自动降级为了场外选手  

题面复杂，不简述了  

----------------  

首先定义状态 $dis(x,y,num1,num2)$ 表示当前坐标是 $(x,y)$，然后用了 $num1$ 次隐身，$num2$ 次瞬移，的最短时间  
答案就是 $\min(dis(tx,ty,[0,c1],[0,c2]))$，其中 $(tx,ty)$ 为终点坐标  

对于每个坐标，枚举 12 个方向  
分别是 8 个正常走路的方向，如果进入了卫兵监视范围，$num1$ 要加一，如果走到了卫兵的格子上，就不行  
还有 4 个是瞬移的方向，此时 $num2$ 要加一  
同样要考虑是否进入卫兵监视范围和是否走到了卫兵的格子上  

如果发现走到了最终格子，更新答案  
题目要求先最小化时间，再最小化技能次数和，再最小化隐身次数，按要求更新就好，稍显麻烦  
因此，也不能一搜到答案就退出，因为退出以后，后面可能还有花费同样时间，但技能次数小的方案  
如果搜到就直接退出了后面的就取不到了  

那么复杂度显然是 $O(n\times m\times c1\times c2)$，但肯定远远跑不满  

考虑怎么标记卫兵的防护范围，因为是曼哈顿距离，所以手动标记一下会观察出，防护范围就是一个斜着的正方形  
比较像[飞飞侠](https://www.luogu.com.cn/problem/P4473)这题里的每一步能走哪些格的描述，~~当然做法上和这个题没有任何关系~~  

直接标记是 $n^4$，不行  
因为是一个区间，很容易想到使用线段树，对每一行建线段树，然后区间修改，bfs 时单点查询  
但是这样多一个 $\log$，变成了 $O(n\times m\times c1\times c2\times 12\times \log m)\approx 2\cdot 10^9$，即使跑不满也够呛能过  
然后事实证明，~~跑的是非常不满~~，只 TLE 了一个点，下面介绍的差分做法在优化之前也是 TLE 一个  

所以因为查询是单点，所以可以使用差分  
比如要修改区间 $[x,y]$，让他们区间加一，设差分数组为 $t$，则让 $t_x$ 加一，$t_{y+1}$ 减一  
然后，在对 $t$ 做一个前缀和，就是原数组  

为什么？因为 $t_i$ 再做前缀和之前，表示的实际上是：$i$ 号位置的数，比 $i-1$ 位置的数大了多少  
$t_x$ 加一，就是 $x$ 位置在经过区间加以后，比 $x-1$ 位置的数，**又多大了 $1$**  
而 $[x+1,y]$ 之间的所有位置，并 **没有比它前面那个数多大或少大（相对大小没变）**，所以不用改变  
而 $t_{y+1}$ 减一，就是因为 $[x,y]$ 区间加以后，$y+1$ 位置的数比 $y$ 位置的数 **少大了 $1$**  

那么，$0$ 号位置是 $0$，所以 $1$ 号位置比它“多大了”多少，那么 $1$ 号位置就是多少  
$1$ 号位置确定了，$2$ 号位置比 $1$ 号位置“多大了”多少（在这里是“多大了”$t_2$），那 $2$ 号位置实际的值就是 $t_1+t_2$，因为 $t_1$ 在这里是相当于已经做过前缀和了，表示实际数值  
然后 $t_2$ 也就表示实际数值了，就一路前缀和到后面，算出了真实值  

卡常  
**不要用STL！！！**  
队列一定不要用STL的，慢到死，会被卡在第 18 个点  
还有，如果状态有很多维（比如这个题就是），不要偷懒把状态一个一个入队（我就经常这么做），太慢，最好是构建一个结构体  
以前做的题不卡常看不出来  
STL队列本机 10s+，改成手写本机+结构体 3s 多，但洛谷上还是过不了  

然后加一个最优性剪枝  
```cpp  
if(step>ans) continue;
```  
就是如果当前的步数已经大于当前记录下的最优答案了，就不再继续搜了  

然后本机 1s，洛谷 3s  

代码写的丑了，挺长  

```cpp  
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cmath>
#include<map>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
} 
int n,m,d,c1,c2;
int sx,sy,tx,ty;
int have[355][355],vis[355][355][17][17];
const int dx[8]={-1,-1,-1,0,0,1,1,1};
const int dy[8]={-1,0,1,-1,1,-1,0,1};
const int dxx[4]={-1,1,0,0};
const int dyy[4]={0,0,1,-1};
int t[355][355];
int ans=1e9,ans_num1,ans_num2;
inline int abs(int x){return x>0?x:-x;}
inline int min(int x,int y){return x>y?y:x;}
inline int max(int x,int y){return x>y?x:y;}
struct data{
	int x,y,step,num1,num2;
}q[30000006];
inline int bfs(){
	reg int head=1,tail=0;
	q[++tail]=(data){sx,sy,0,0,0};
	vis[sx][sy][0][0]=1; 
	reg int x,y,step,num1,num2;
	data data_;
	while(head<=tail){
		data_=q[head++];
		x=data_.x;
		y=data_.y;
		step=data_.step;
		num1=data_.num1;
		num2=data_.num2;
		if(step>ans) continue;
		for(reg int x_,y_,k=0;k<8;k++){
			x_=x+dx[k];y_=y+dy[k];
			if(x_<1||x_>m) continue;
			if(y_<1||y_>n) continue;
			if(have[x_][y_]) continue;
			if(t[y_][x_]){
				if(num1==c1) continue;
				if(vis[x_][y_][num1+1][num2]) continue;
				if(x_==tx&&y_==ty){
					if(step+1<ans) ans=step+1,ans_num1=num1+1,ans_num2=num2;
					else if(step+1==ans){
						if(num1+num2+1<ans_num1+ans_num2) ans_num1=num1+1,ans_num2=num2;
						else if(num1+num2+1==ans_num1+ans_num2){
							if(num1+1<ans_num1) ans_num1=num1+1,ans_num2=num2;
						}
					}
				}
				vis[x_][y_][num1+1][num2]=1;
				q[++tail]=(data){x_,y_,step+1,num1+1,num2};
			}
			else{
				if(vis[x_][y_][num1][num2]) continue;
				if(x_==tx&&y_==ty){
					if(step+1<ans) ans=step+1,ans_num1=num1,ans_num2=num2;
					else if(step+1==ans){
						if(num1+num2<ans_num1+ans_num2) ans_num1=num1,ans_num2=num2;
						else if(num1+num2==ans_num1+ans_num2){
							if(num1<ans_num1) ans_num1=num1,ans_num2=num2;
						}
					}
				}
				vis[x_][y_][num1][num2]=1;
				q[++tail]=(data){x_,y_,step+1,num1,num2};
			}
		}
		if(num2==c2) continue;
		for(reg int x_,y_,k=0;k<4;k++){
			x_=x+dxx[k]*d;y_=y+dyy[k]*d;
			if(x_<1||x_>m) continue;
			if(y_<1||y_>n) continue;
			if(have[x_][y_]) continue;
			if(t[y_][x_]){
				if(num1==c1) continue;
				if(vis[x_][y_][num1+1][num2+1]) continue;
				if(x_==tx&&y_==ty){
					if(step+1<ans) ans=step+1,ans_num1=num1+1,ans_num2=num2+1;
					else if(step+1==ans){
						if(num1+num2+2<ans_num1+ans_num2) ans_num1=num1+1,ans_num2=num2+1;
						else if(num1+num2+2==ans_num1+ans_num2){
							if(num1+1<ans_num1) ans_num1=num1+1,ans_num2=num2+1;
						}
					}
				}
				vis[x_][y_][num1+1][num2+1]=1;
				q[++tail]=(data){x_,y_,step+1,num1+1,num2+1};
			}
			else{
				if(vis[x_][y_][num1][num2+1]) continue;
				if(x_==tx&&y_==ty){
					if(step+1<ans) ans=step+1,ans_num1=num1,ans_num2=num2+1;
					else if(step+1==ans){
						if(num1+num2+1<ans_num1+ans_num2) ans_num1=num1,ans_num2=num2+1;
						else if(num1+num2+1==ans_num1+ans_num2){
							if(num1<ans_num1) ans_num1=num1,ans_num2=num2+1;
						}
					}
				}
				vis[x_][y_][num1][num2+1]=1;
				q[++tail]=(data){x_,y_,step+1,num1,num2+1};
			}
		}
	}
	return -1;
}
int main(){
//	std::freopen("bandit18.in","r",stdin);
//	std::freopen("bandit.out","w",stdout);
	n=read();m=read();c1=read();c2=read();d=read();
	reg char c;
	for(reg int i=1;i<=n;i++){
		for(reg int j=1;j<=m;j++){
			c=std::getchar();
			while(c!='S'&&c!='T'&&c!='.'&&(c<'0'||c>'9')) c=std::getchar();
			if(c=='S') sx=j,sy=i;
			else if(c=='T') tx=j,ty=i;
			else if(c>='0'&&c<='9'){
				reg int x=c^48;c=std::getchar();
				while(c>='0'&&c<='9') x=x*10+(c^48),c=std::getchar();
				have[j][i]=1;
				int tmp=std::min(n,i+x-1);
				for(reg int k=std::max(i-x+1,1);k<=tmp;k++)
					t[k][max(1,j-x+1+abs(i-k))]++,t[k][min(m,j+x-1-abs(i-k))+1]--;
			}
		}
	}
	for(reg int i=1;i<=n;i++)
		for(reg int j=1;j<=m;j++) t[i][j]+=t[i][j-1];
	bfs();
	if(ans==1e9) std::puts("-1");
	else std::printf("%d %d %d",ans,ans_num1,ans_num2);
	return 0;
}
```

---

## 作者：Harry27182 (赞：5)

首先看到这题，一看就是个 bfs 。那么，按照 bfs 的惯例，要开一个队列，因为荆轲可以隐身和瞬移，那么队列里要存坐标，步数，隐身和瞬移的使用次数。既然要存这么多东西，那最好用结构体来存。就是下面这个：

```cpp
struct node
{
	int x,y,ys,sy,cnt;
	node(int a,int b,int c,int d,int e):
		x(a),y(b),ys(c),sy(d),cnt(e){}
};
```
那么，因为他要求让技能次数最少，所以最先搜到的不一定是最优解，所以在 bfs 函数前就要加上这一段取最优解：
```cpp
        if(x==tx&&y==ty)
		{
			if(flag==false)
			{
				flag=true;
				ans1=cnt;
				ans2=u.ys;
				ans3=u.sy;
			} 
			else
			{
				if(cnt<ans1||(cnt==ans1&&u.ys+u.sy<ans2+ans3)||
				(cnt==ans1&&u.ys+u.sy==ans2+ans3&&u.ys<ans2))
			    {
			    	ans1=cnt;
					ans2=u.ys;
					ans3=u.sy;
			    }
			}
		}
		if(cnt>ans1&&flag==true)//步数大于最优解就不用搜了
		{
			cout<<ans1<<" "<<ans2<<" "<<ans3<<endl;
			exit(0);
		}
```

下面，重点来了，怎么处理那些点能被看见呢？

我们可以发现每个士兵的监控范围就是一个菱形，所以需要一个区间修改，那就用差分好了：

```cpp
void work(int x,int y,int d)
{
    for(int i=0;i<d;i++)
	{
        int l=max(1,x+i-d+1),r=min(m,x-i+d-1);
        int u=max(1,y-i),d=min(n,y+i);
        cf[u][l]++;
        cf[u][r+1]--;
        if(u==d)continue;
        cf[d][l]++;
        cf[d][r+1]--;
    }
}
```

完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[8]={-1,1,0,0,-1,1,-1,1};
int dy[8]={0,0,1,-1,1,-1,-1,1};
bool vis[360][360][16][16],b[360][360],p[360][360];
int cf[360][360],key[360][360];
int n,m,sx,sy,tx,ty,c1,c2,d,ans1,ans2,ans3;
string s;
bool flag;
struct node
{
	int x,y,ys,sy,cnt;
	node(int a,int b,int c,int d,int e):
		x(a),y(b),ys(c),sy(d),cnt(e){}
};
queue<node>q;
void work(int x,int y,int d)
{
    for(int i=0;i<d;i++)
	{
        int l=max(1,x+i-d+1),r=min(m,x-i+d-1);
        int u=max(1,y-i),d=min(n,y+i);
        cf[u][l]++;
        cf[u][r+1]--;
        if(u==d)continue;
        cf[d][l]++;
        cf[d][r+1]--;
    }
}
void bfs()
{
	q.push((node){sx,sy,0,0,0});
	vis[sx][sy][0][0]=true;
	while(!q.empty())
	{
		node u=q.front();
		q.pop();
		int x=u.x,y=u.y,cnt=u.cnt;
		if(x==tx&&y==ty)
		{
			if(flag==false)
			{
				flag=true;
				ans1=cnt;
				ans2=u.ys;
				ans3=u.sy;
			} 
			else
			{
				if(cnt<ans1||(cnt==ans1&&u.ys+u.sy<ans2+ans3)||
				(cnt==ans1&&u.ys+u.sy==ans2+ans3&&u.ys<ans2))
			    {
			    	ans1=cnt;
					ans2=u.ys;
					ans3=u.sy;
			    }
			}
		}
		if(cnt>ans1&&flag==true)
		{
			cout<<ans1<<" "<<ans2<<" "<<ans3<<endl;
			exit(0);
		}
		for(int i=0;i<8;i++)
		{
			int nx=x+dx[i],ny=y+dy[i];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&p[nx][ny]==false)
			{
				if(b[nx][ny]==false)
				{
					if(vis[nx][ny][u.ys][u.sy]==false)
					{
						vis[nx][ny][u.ys][u.sy]=true;
						q.push((node){nx,ny,u.ys,u.sy,cnt+1});
					}
				}
				else
			    {
			    	if(u.ys+1<=c1&&vis[nx][ny][u.ys+1][u.sy]==false)
			    	{
			    		vis[nx][ny][u.ys+1][u.sy]=true;
			    		q.push((node){nx,ny,u.ys+1,u.sy,cnt+1});
			    	}
			    }
			}
		}
		if(u.sy+1<=c2)
		{
			for(int i=0;i<4;i++)
			{
				int nx=u.x+dx[i]*d,ny=u.y+dy[i]*d;
				if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&p[nx][ny]==false)
				{
					if(b[nx+dx[i]][ny+dy[i]]==false)
					{
						if(vis[nx][ny][u.ys][u.sy+1]==false)
						{
							vis[nx][ny][u.ys][u.sy+1]=true;
							q.push((node){nx,ny,u.ys,u.sy+1,cnt+1}); 
						}
					}
					else
					{
						if(u.ys+1<=c1&&vis[nx][ny][u.ys+1][u.sy+1]==false)
						{
							vis[nx][ny][u.ys+1][u.sy+1]=true;
							q.push((node){nx,ny,u.ys+1,u.sy+1,cnt+1}); 
						}
					}
				}
			}
		}
	}
	if(flag==true)
	{
		cout<<ans1<<" "<<ans2<<" "<<ans3<<endl;
		exit(0);
	}
}
int main()
{
	cin>>n>>m>>c1>>c2>>d;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>s;
			if(s[0]=='S')
			{
				sx=i;
				sy=j;
			}
			else if(s[0]=='T')
			{
				tx=i;
				ty=j;
			}
			else if(s[0]=='.')continue;
			else
			{
				p[i][j]=true;
				int x=0;
				for(int k=0;k<s.length();k++)
				{
					x*=10;
					x+=s[k]-'0';
				}
				work(j,i,x);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			key[i][j]=key[i][j-1]+cf[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			b[i][j]=(bool)key[i][j];
		}
	}
    bfs();
    cout<<-1<<endl;
	return 0;
}
```


---

## 作者：Perfonster (赞：5)

**本菜鸡的提交记录（AC提交仅一次）为2020.11.21之前的最优解，大大领先第二、第三的巨佬。您还不来康康这篇题解吗？**

![](https://i.loli.net/2020/11/21/Rjqu3xVQLkiJPFe.png)

### 〇.简介

这题运用了一个比较复杂的广搜，每个节点的状态比较多。用$(x,y,p,q,t)$描述荆轲的状态，表示他用了$p$次隐身，$q$次瞬移，来到了$(x,y)$，共花费时间$t$。这个状态用结构体类型$node$存储。另外，用$edx$与$edy$记录终点位置$(x,y)$，用$kk$表示一个士兵的观察范围，用$(anst,ansp,ansq)$表示答案为花费$anst$时间，使用$ansp$次隐身，$ansq$次瞬移，使用$node$类型结构体数组$e[i][j]$表示点$(i,j)$当前的最优解。

### 一.数据读入

对于每一个点$(i,j)$，我们读入一个字符串$c$，若$c$为$S$，则把$(node)\{i,j,0,0,0\}$压入队列。为$T$则令$edx=i$，$edy=j$。否则如果不是$·$，则说明是用数字代表的士兵，用语句$\text{sscanf(c,"\%d",\&kk);}$即可把字符串$c$转化为代表士兵观察范围的数字赋给$kk$。

### 二.士兵观察位置预处理

首先，格子上有卫兵和格子被卫兵观察到是不同的概念。前者荆轲即使隐身也会被发现，后者荆轲隐身就不会被发现。因此我们开一个数组$b$，$b[i][j]$为$true$表示位置$(i,j)$有士兵，荆轲无法到达。

注意到一个士兵的观察范围是一个斜着的正方形（实际上是一个到定整点的曼哈顿距离$\leqslant$定值的整点集）。观察范围的覆盖等价于在差分数组上进行区间加，因此我们对每一行建立一个差分数组$a$，然后枚举士兵观察的每行。计算出该行能观察的列的范围$[l,r]$，然后区间加一，最后再分别对每行求前缀和即可。此时若$a[i][j]>0$则说明被观察到，否则不被。

### 三.BFS

显然：若$(nx,ny)$不会被发现，则荆轲不需要使用隐身技能就能到达。

- 若荆轲不使用瞬移来到$(nx,ny)$，且$(nx,ny)$不会被发现（不使用隐身），则进行$(x,y,p,q,t)$到$(nx,ny,p,q,t+1)$的转移。
- 若荆轲不使用瞬移来到$(nx,ny)$，且$(nx,ny)$会被发现（使用隐身），则进行$(x,y,p,q,t)$到$(nx,ny,p+1,q,t+1)$的转移。
- 若荆轲使用瞬移来到$(nx,ny)$，且$(nx,ny)$不会被发现（不使用隐身），则进行$(x,y,p,q,t)$到$(nx,ny,p,q+1,t+1)$的转移。
- 若荆轲使用瞬移来到$(nx,ny)$，且$(nx,ny)$会被发现（使用隐身），则进行$(x,y,p,q,t)$到$(nx,ny,p+1,q+1,t+1)$的转移。

若转移到的点为终点$(edx,edy)$，则更新答案。显然答案的$anst$大于$0$。则$BFS$结束时若$anst$为$0$则无解输出$-1$，否则输出$\text{anst ansp ansq}$。

### 四.代码+注释

```cpp
#include<bits/stdc++.h>
#define maxn 359
#define rr register
using namespace std;
int n,m,c1,c2,d,kk,edx,edy,anst,ansp,ansq;
int a[maxn][maxn],dx[8]={-1,-1,0,1,1,1,0,-1},dy[8]={0,1,1,1,0,-1,-1,-1};//dx，dy为方向数组 
char c[9];
bool b[maxn][maxn],vis[maxn][maxn];//vis[i][j]=true代表(i,j)已经访问过 
struct node{
	int x,y,p,q,t;
}e[maxn][maxn];
queue<node>q;//队列 
int main(){
	scanf("%d%d%d%d%d",&n,&m,&c1,&c2,&d);
	//读入数据 
	for(rr int i=1;i<=n;++i){
		for(rr int j=1;j<=m;++j){
			scanf("%s",c);
			if(c[0]=='S')q.push((node){i,j,0,0,0});//压入初始状态 
			else if(c[0]=='T'){//记录终点位置 
				edx=i; edy=j;
			}
			else if(c[0]!='.'){
				sscanf(c,"%d",&kk);//得到观察范围 
				b[i][j]=true;//(i,j)有士兵 
				for(rr int k=max(1,i-kk+1);k<=min(n,i+kk-1);++k){
					//计算观察矩形的差分值，第k行区间加的左端点为max(1,j-kk+1+abs(i-k))，右端点为min(m,j+kk-1-abs(i-k))
					//根据差分特性，在右端点+1处-1 
					//加入max、min是为了处理观察范围超出地图的情况 
					a[k][max(1,j-kk+1+abs(i-k))]++; a[k][min(m+1,j+kk-abs(i-k))]--;
				}
			}
		}
	}	
	for(rr int i=1;i<=n;++i){
		for(rr int j=1;j<=m;++j)a[i][j]+=a[i][j-1];//前缀和求出每个位置是否被士兵观察到 
	}
	//BFS 
	while(q.size()){
		node l=q.front();//取出队首 
        q.pop();
		if(l.t>anst&&anst>0)continue;//如果当前状态耗时比anst大，并且anst!=0（已经有解了），则当前肯定不是最优解，跳过 
        if(!vis[l.x][l.y]){//初次访问(l.x,l.y)，那么肯定成为e[l.x][l.y]的最优解 
        	vis[l.x][l.y]=true;
        	e[l.x][l.y]=(node){l.x,l.y,l.p,l.q,l.t};
		}
		else{//如果已经访问过了，那么要考虑此时的解是否比原来的解更优 
			//后访问耗时肯定>=先访问耗时，但不代表后访问不能成为最优解（可能先访问的使用太多技能导致它实际无法到达终点） 
			if(l.p+l.q<e[l.x][l.y].p+e[l.x][l.y].q){//首先保证技能使用次数和最小 
				e[l.x][l.y].p=l.p; e[l.x][l.y].q=l.q;
			}
			else if(l.p+l.q==e[l.x][l.y].p+e[l.x][l.y].q&&l.p<e[l.x][l.y].p){//技能使用次数和相同时，再考虑使用较少的隐身 
				e[l.x][l.y].p=l.p; e[l.x][l.y].q=l.q;
			}
			else continue;//如果以上情况都不满足，加之后访问耗时>=先访问耗时，当前情况一定不更优，不考虑 
		}
        if(l.x==edx&&l.y==edy){//找到答案，更新 
    		anst=l.t; ansp=l.p; ansq=l.q;
			continue;
		}		
        if(l.q+1<=c2){//若当前还可以使用瞬移 
        	for(rr int i=0;i<8;i+=2){//更新瞬移并且不隐身的答案 
        		int xx=l.x+dx[i]*d,yy=l.y+dy[i]*d;
				if(xx>=1&&xx<=n&&yy>=1&&yy<=m){
					if(b[xx][yy])continue;
					if(!a[xx][yy])q.push((node){xx,yy,l.p,l.q+1,l.t+1});
				}
			}
		}		
        for(rr int i=0;i<8;++i){//更新不瞬移并且不隐身的答案 
			int xx=l.x+dx[i],yy=l.y+dy[i];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&b[xx][yy]==false){
				if(!a[xx][yy])q.push((node){xx,yy,l.p,l.q,l.t+1});
			}
        }
        if(l.q+1<=c2){//若当前还可以使用瞬移 
        	for(rr int i=0;i<8;i+=2){//更新瞬移并且隐身的答案
        		int xx=l.x+dx[i]*d,yy=l.y+dy[i]*d;
				if(xx>=1&&xx<=n&&yy>=1&&yy<=m){
					if(b[xx][yy])continue;
					if(a[xx][yy]&&l.p+1<=c1)q.push((node){xx,yy,l.p+1,l.q+1,l.t+1});
				}
			}
		}			
        for(rr int i=0;i<8;++i){//更新不瞬移并且隐身的答案
			int xx=l.x+dx[i],yy=l.y+dy[i];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&b[xx][yy]==false){
				if(a[xx][yy]&&l.p+1<=c1)q.push((node){xx,yy,l.p+1,l.q,l.t+1});
			}
        }	
	}
	//输出 
	if(anst)printf("%d %d %d\n",anst,ansp,ansq);//anst>0说明有解 
	else printf("-1\n");//否则无解 
	return 0;
}
```

点个赞再走呗~






---

## 作者：happy_dengziyue (赞：2)

### 1 思路

一看这道题，你有没有发现，这就是**BFS**啊！

怎么用呢？

1. 我们得要输入前5个变量；

2. 绘制好地图，注意存储该位置类型（起点、终点、空地、卫兵）和该位置能否被探测；

3. 开始BFS。

接下来，我将详解BFS过程。

1. 先将 $ans$ 变量的时间花费、隐身次数、瞬移次数设大一点，同时在 $way$ 队列里加入一个路径点；

2. 弹出 $way$ 队列的队首，设它为 $fro$ 以此路径点为基准探测；

3. 如果 $fro$ 路径点刚好是结束点：

	看一下它是否是更优解，如果可以就更新 $ans$ 变量；
    
   回到第2步；
   
4. 如果 $fro$ 路径点的时间花费超过了 $ans$ 变量：

	直接结束BFS，因为越往后时间越大。
    
   这就是最优性剪枝。
   
5. 枚举普通移动的可能：
	
	如果满足要求（即，没有越界，这个访问方式不同于目标点已有的访问方式，若是需要隐身则隐身次数又要足够）：
    
   将这个路径点入队。
   
6. 瞬移同理，记得看看瞬移次数够不够用。

7. 回到第2步。

现在，我们离开了BFS，就可以输出答案了：

如果 $ans$ 变量明显没有经过修改，就输出 “$-1$” ；

否则输出 $ans$ 变量。

### 2 代码与提交记录

```cpp
//本代码使用 BFS+差分 算法，可以改善时间复杂度
//靓丽的开头
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
//一堆杂七杂八的变量
const int max_n=350;//地图尺寸最大值
const int max_magic=15;//魔法使用次数最大值
int n,m;//地图尺寸
int c1,c2;//魔法限制
int d;//瞬移距离
struct G{//地图结构体
	int k;//种类
	//0 空地  1 荆轲  2 嬴政  3 卫兵
	bool s;//是否被探测
}gra[max_n+2][max_n+2];//地图
int sx,sy,ex,ey;//起点与终点的坐标
int so[max_n+2][max_n+2];//士兵探测
char ty[5];//用于输入
struct S{//消耗结构体
	int t;//时间
	int m1,m2;//各种魔法使用次数
}ans;//最终答案
struct W{//路径结构体
	int x,y;//坐标
	S s;//走到这一步的消耗
}fro;//取队首
queue<W> way;
int dx[8]={-1,1,0,0,-1,-1,1,1};//方向数组：行
int dy[8]={0,0,-1,1,-1,1,-1,1};//方向数组：列
	//0 上  1 下  2 左  3 右  4 左上  5 右上  6 左下  7 右下
bool vis[max_n+2][max_n+2][max_magic+2][max_magic+2];//访问与否
//main函数
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P6474_3.in","r",stdin);
	freopen("P6474_3.out","w",stdout);
	#endif
	//输入基本的数据
	scanf("%d%d%d%d%d",&n,&m,&c1,&c2,&d);
	//地图布置
	for(int i=1,s,l;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%s",ty);
			if(ty[0]=='.'){//空地
				gra[i][j].k=0;
				continue;
			}
			if(ty[0]=='S'){
				gra[i][j].k=1;
				sx=i;
				sy=j;
				continue;
			}
			if(ty[0]=='T'){
				gra[i][j].k=2;
				ex=i;
				ey=j;
				continue;
			}
			gra[i][j].k=3;
			s=0;
			l=strlen(ty);
			for(int k=0;k<l;++k){
				s*=10;
				s+=(ty[k]-'0');
			}
			for(int k=-s+1,x,y;k<s;++k){
				x=i+k;
				if(x>=1&&x<=n){
					y=j-s+abs(k)+1;
					if(y>=1){
						++so[x][y];
					}
					else{
						++so[x][1];
					}
					y=j+s-abs(k);
					if(y<=m){
						--so[x][y];
					}
				}
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1,s=0;j<=m;++j){
			s+=so[i][j];
			gra[i][j].s=(bool)s;
		}
	}
	//开始进行BFS
	way.push((W){sx,sy,(S){0,0,0}});
	ans=(S){12345678,12345678,12345678};
	while(!way.empty()){
		fro=way.front();//取队首
		way.pop();//删除队首
		if(fro.s.t>ans.t){//最优性剪枝
			break;
		}
		if(fro.x==ex&&fro.y==ey){//到达终点
			if(fro.s.m1<=c1&&fro.s.m2<=c2){//满足魔法使用次数要求
				if(fro.s.t<ans.t){//时间最短
					ans=fro.s;
				}
				else{
					if(fro.s.t==ans.t){//时间一样
						if(fro.s.m1+fro.s.m2<ans.m1+ans.m2){//技能总次数最少
							ans=fro.s;
						}
						else{
							if(fro.s.m1+fro.s.m2==ans.m1+ans.m2){//技能总次数一样
								if(fro.s.m1<ans.m1){//隐身次数最少
									ans=fro.s;
								}
							}
						}
					}
				}
			}
			continue;
		}
		for(int i=0,nx,ny;i<8;++i){
			nx=fro.x+dx[i];
			ny=fro.y+dy[i];
			if(nx<1||nx>n||ny<1||ny>m){//越过边界
				continue;
			}
			if(gra[nx][ny].k==3){//前方卫兵
				continue;
			}
			if(gra[nx][ny].s){//被探测到了
				if(vis[nx][ny][fro.s.m1+1][fro.s.m2]||fro.s.m1>=c1){//已经访问或隐身次数不够
					continue;
				}
				vis[nx][ny][fro.s.m1+1][fro.s.m2]=true;
				way.push((W){nx,ny,(S){fro.s.t+1,fro.s.m1+1,fro.s.m2}});
			}
			else{
				if(vis[nx][ny][fro.s.m1][fro.s.m2]){//已经访问
					continue;
				}
				vis[nx][ny][fro.s.m1][fro.s.m2]=true;
				way.push((W){nx,ny,(S){fro.s.t+1,fro.s.m1,fro.s.m2}});
			}
		}
		if(fro.s.m2>=c2){//瞬移次数不够
			continue;
		}
		for(int i=0,nx,ny;i<4;++i){
			nx=fro.x+dx[i]*d;
			ny=fro.y+dy[i]*d;
			if(nx<1||nx>n||ny<1||ny>m){//越过边界
				continue;
			}
			if(gra[nx][ny].k==3){//前方卫兵
				continue;
			}
			if(gra[nx][ny].s){//被探测到了
				if(vis[nx][ny][fro.s.m1+1][fro.s.m2+1]||fro.s.m1>=c1){//已经访问或隐身次数不够
					continue;
				}
				vis[nx][ny][fro.s.m1+1][fro.s.m2+1]=true;
				way.push((W){nx,ny,(S){fro.s.t+1,fro.s.m1+1,fro.s.m2+1}});
			}
			else{
				if(vis[nx][ny][fro.s.m1][fro.s.m2+1]){//已经访问
					continue;
				}
				vis[nx][ny][fro.s.m1][fro.s.m2+1]=true;
				way.push((W){nx,ny,(S){fro.s.t+1,fro.s.m1,fro.s.m2+1}});
			}
		}
	}
	//输出，完成
	if(ans.t==12345678&&ans.m1==12345678&&ans.m2==12345678){//明显无法到达
		printf("-1\n");
		return 0;
	}
	printf("%d %d %d\n",ans.t,ans.m1,ans.m2);
	return 0;
}

```

[记录传送门](https://www.luogu.com.cn/record/50734116)

---

## 作者：良心WA题人 (赞：2)

# 简洁题意：
从 S 到 T，单位时间可以走格子周围的八个格子，有些格子不能走，这些格子周围距离小于等于 $a(i,j)$ 的格子只能用一次技能一才能走。每个时刻可以用技能二，单位时间向上下左右走 d 格。问最快多久，若多种方案则希望技能用得少，技能用的一样多则希望少用技能一，无解输出-1，反之输出时间和各个技能用的数量。
# 分析：
数据范围不大，可以用 bfs，直到答案大于当前答案或者不能走就停止，到达 T 后对比答案并更新，周围能观察到的点就搜索覆盖。但是这样仍然会超时，因为我们处理一个点所能影响的周围的点太慢了。不难发现这个是一个菱形，可以针对每一个菱形的每一行进行差分，最后统一处理。注意在处理字符时 $a(i,j)$ 有可能有两位。

差分最后统计的时间复杂度是 $\Theta(nm)$ 的，bfs 每个点都出入队一次，时间复杂度$\Theta(nm)$，总共最多枚举 $n^2m^2$ 条边，所以总的时间复杂度是 $O(n^2m^2)$ 的。这样时间会刚好超一点，但是实际使用起来是不可能出现每两个点之间都可以互相到达的情况，$n^2m^2$ 条边也不可能都用了，大大达不到上界时间复杂度。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=354,dx[8]={1,-1,0,0,1,-1,1,-1},dy[8]={0,0,1,-1,1,1,-1,-1};
int n,m,c1,c2,d,sta[NN][NN],num[NN][NN];
bool can[NN][NN],vis[NN][NN][20][20];
struct node
{
    int x,y,d,c1,c2;
}q[30000004],ans=(node){0,0,1e9,1e9,1e9};
void cover(int x,int y,int k)
{
    for(int i=0;i<k;i++)
	{
	    num[max(1,x-i)][max(1,y-k+i+1)]++;
	    num[max(1,x-i)][min(m,y+k-i-1)+1]--;
	    num[min(n,x+i)][max(1,y-k+i+1)]++;
	    num[min(n,x+i)][min(m,y+k-i-1)+1]--;
	}
}
bool check(node x,node y)
{
    if(x.c1+x.c2!=y.c1+y.c2)
		return x.c1+y.c2<y.c1+y.c2;
    return x.c1<y.c1;
}
void bfs(pair<int,int>st,pair<int,int>ed)
{
    int h=1,t=0;
	q[++t]=(node){st.first,st.second};
    while(h<=t)
	{
	    node u=q[h++];
	    if(u.d>=ans.d)
		    break;
	    for(int i=0;i<8;i++)
		{
		    int nx=u.x+dx[i],ny=u.y+dy[i];
		    if(nx<1||ny<1||nx>n||ny>m||sta[nx][ny])
				continue;
		    if(!can[nx][ny])
			{
			    if(vis[nx][ny][u.c1][u.c2])
					continue;
			    vis[nx][ny][u.c1][u.c2]=true;
			    q[++t]=(node){nx,ny,u.d+1,u.c1,u.c2};
			    if(nx==ed.first&&ny==ed.second&&check(q[t],ans))
					ans=q[t];
			}
		    else
			{
			    if(u.c1>=c1||vis[nx][ny][u.c1+1][u.c2])
					continue;
			    vis[nx][ny][u.c1+1][u.c2]=true;
			    q[++t]=(node){nx,ny,u.d+1,u.c1+1,u.c2};
			    if(nx==ed.first&&ny==ed.second&&check(q[t],ans))
					ans=q[t];
			}
		}
	    for(int i=0;i<4;i++)
		{
		    int nx=u.x+dx[i]*d,ny=u.y+dy[i]*d;
		    if(nx<1||ny<1||nx>n||ny>m||sta[nx][ny])
				continue;
		    if(!can[nx][ny])
			{
			    if(u.c2>=c2||vis[nx][ny][u.c1][u.c2+1])
					continue;
			    vis[nx][ny][u.c1][u.c2+1]=true;
			    q[++t]=(node){nx,ny,u.d+1,u.c1,u.c2+1};
			    if(nx==ed.first&&ny==ed.second&&check(q[t],ans))
					ans=q[t];
			}
		    else
			{
			    if(u.c1>=c1||u.c2>=c2||vis[nx][ny][u.c1+1][u.c2+1])
					continue;
			    vis[nx][ny][u.c1+1][u.c2+1]=true;
			    q[++t]=(node){nx,ny,u.d+1,u.c1+1,u.c2+1};
			    if(nx==ed.first&&ny==ed.second&&check(q[t],ans))
					ans=q[t];
			}
		}
	}
}
int main()
{
    scanf("%d%d%d%d%d",&n,&m,&c1,&c2,&d);
    pair<int,int>st,ed;
    for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
		{
		    char s[10];
		    scanf("%s",s);
		    if(s[0]=='S')
			{
			    st.first=i;
			    st.second=j;
			}
		    else if(s[0]=='T')
			{
				ed.first=i;
				ed.second=j;
			}
		    else if(s[0]!='.')
			{
				for(int k=0;s[k];k++)
					sta[i][j]=(sta[i][j]<<3)+(sta[i][j]<<1)+(s[k]-'0');
			    cover(i,j,sta[i][j]);
			}
		}
    for(int i=1;i<=n;i++)
	{
	    int sum=0;
	    for(int j=1;j<=m;j++)
		{
		    sum+=num[i][j];
		    if(sum>0)
				can[i][j]=true;
		}
	}
    bfs(st,ed);
    if(!ans.x)
		printf("-1");
    else
		printf("%d %d %d",ans.d,ans.c1,ans.c2);
    return 0;
}
```

---

## 作者：Viktley (赞：0)

bfs+差分+卡常

本来我其实是场内选手，但是因为记错提交时间，晚了半小时才交，交不上了，就自动降级为了场外选手

题面复杂，不简述了

------------

首先定义状态 dis(x,y,num1,num2) 表示当前坐标是 (x,y)，然后用了 num1 次隐身，num2 次瞬移，的最短时间
答案就是 min(dis(tx,ty,[0,c1],[0,c2]))，其中 (tx,ty) 为终点坐标

对于每个坐标，枚举 12 个方向
分别是 8 个正常走路的方向，如果进入了卫兵监视范围，num1 要加一，如果走到了卫兵的格子上，就不行
还有 4 个是瞬移的方向，此时 num2 要加一
同样要考虑是否进入卫兵监视范围和是否走到了卫兵的格子上

如果发现走到了最终格子，更新答案
题目要求先最小化时间，再最小化技能次数和，再最小化隐身次数，按要求更新就好，稍显麻烦
因此，也不能一搜到答案就退出，因为退出以后，后面可能还有花费同样时间，但技能次数小的方案
如果搜到就直接退出了后面的就取不到了

那么复杂度显然是 O(n×m×c1×c2)，但肯定远远跑不满

考虑怎么标记卫兵的防护范围，因为是曼哈顿距离，所以手动标记一下会观察出，防护范围就是一个斜着的正方形
比较像飞飞侠这题里的每一步能走哪些格的描述，当然做法上和这个题没有任何关系

直接标记是 $n^4$，不行
因为是一个区间，很容易想到使用线段树，对每一行建线段树，然后区间修改，bfs 时单点查询
但是这样多一个 log，变成了 O(n×m×c1×c2×12×logm)≈2⋅109，即使跑不满也够呛能过
然后事实证明，跑的是非常不满，只 TLE 了一个点，下面介绍的差分做法在优化之前也是 TLE 一个

所以因为查询是单点，所以可以使用差分
比如要修改区间 [x,y]，让他们区间加一，设差分数组为 t，则让 tx 加一，ty+1 减一
然后，在对 t 做一个前缀和，就是原数组

为什么？因为 ti 再做前缀和之前，表示的实际上是：i 号位置的数，比 i−1 位置的数大了多少
tx 加一，就是 x 位置在经过区间加以后，比 x−1 位置的数，又多大了 1
而 [x+1,y] 之间的所有位置，并 没有比它前面那个数多大或少大（相对大小没变），所以不用改变
而 ty+1 减一，就是因为 [x,y] 区间加以后，y+1 位置的数比 y 位置的数 少大了 1

那么，0 号位置是 0，所以 1 号位置比它“多大了”多少，那么 1 号位置就是多少
1 号位置确定了，2 号位置比 1 号位置“多大了”多少（在这里是“多大了”t2），那 2 号位置实际的值就是 t1+t2，因为 t1 在这里是相当于已经做过前缀和了，表示实际数值
然后 t2 也就表示实际数值了，就一路前缀和到后面，算出了真实值

卡常
不要用STL！！！
队列一定不要用STL的，慢到死，会被卡在第 18 个点
还有，如果状态有很多维（比如这个题就是），不要偷懒把状态一个一个入队（我就经常这么做），太慢，最好是构建一个结构体
以前做的题不卡常看不出来
STL队列本机 10s+，改成手写本机+结构体 3s 多，但洛谷上还是过不了

然后加一个最优性剪枝

```cpp
if(step>ans) continue;
```
------------

**Final Code:**

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cmath>
#include<map>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
} 
int n,m,d,c1,c2;
int sx,sy,tx,ty;
int have[355][355],vis[355][355][17][17];
const int dx[8]={-1,-1,-1,0,0,1,1,1};
const int dy[8]={-1,0,1,-1,1,-1,0,1};
const int dxx[4]={-1,1,0,0};
const int dyy[4]={0,0,1,-1};
int t[355][355];
int ans=1e9,ans_num1,ans_num2;
inline int abs(int x){return x>0?x:-x;}
inline int min(int x,int y){return x>y?y:x;}
inline int max(int x,int y){return x>y?x:y;}
struct data{
	int x,y,step,num1,num2;
}q[30000006];
inline int bfs(){
	reg int head=1,tail=0;
	q[++tail]=(data){sx,sy,0,0,0};
	vis[sx][sy][0][0]=1; 
	reg int x,y,step,num1,num2;
	data data_;
	while(head<=tail){
		data_=q[head++];
		x=data_.x;
		y=data_.y;
		step=data_.step;
		num1=data_.num1;
		num2=data_.num2;
		if(step>ans) continue;
		for(reg int x_,y_,k=0;k<8;k++){
			x_=x+dx[k];y_=y+dy[k];
			if(x_<1||x_>m) continue;
			if(y_<1||y_>n) continue;
			if(have[x_][y_]) continue;
			if(t[y_][x_]){
				if(num1==c1) continue;
				if(vis[x_][y_][num1+1][num2]) continue;
				if(x_==tx&&y_==ty){
					if(step+1<ans) ans=step+1,ans_num1=num1+1,ans_num2=num2;
					else if(step+1==ans){
						if(num1+num2+1<ans_num1+ans_num2) ans_num1=num1+1,ans_num2=num2;
						else if(num1+num2+1==ans_num1+ans_num2){
							if(num1+1<ans_num1) ans_num1=num1+1,ans_num2=num2;
						}
					}
				}
				vis[x_][y_][num1+1][num2]=1;
				q[++tail]=(data){x_,y_,step+1,num1+1,num2};
			}
			else{
				if(vis[x_][y_][num1][num2]) continue;
				if(x_==tx&&y_==ty){
					if(step+1<ans) ans=step+1,ans_num1=num1,ans_num2=num2;
					else if(step+1==ans){
						if(num1+num2<ans_num1+ans_num2) ans_num1=num1,ans_num2=num2;
						else if(num1+num2==ans_num1+ans_num2){
							if(num1<ans_num1) ans_num1=num1,ans_num2=num2;
						}
					}
				}
				vis[x_][y_][num1][num2]=1;
				q[++tail]=(data){x_,y_,step+1,num1,num2};
			}
		}
		if(num2==c2) continue;
		for(reg int x_,y_,k=0;k<4;k++){
			x_=x+dxx[k]*d;y_=y+dyy[k]*d;
			if(x_<1||x_>m) continue;
			if(y_<1||y_>n) continue;
			if(have[x_][y_]) continue;
			if(t[y_][x_]){
				if(num1==c1) continue;
				if(vis[x_][y_][num1+1][num2+1]) continue;
				if(x_==tx&&y_==ty){
					if(step+1<ans) ans=step+1,ans_num1=num1+1,ans_num2=num2+1;
					else if(step+1==ans){
						if(num1+num2+2<ans_num1+ans_num2) ans_num1=num1+1,ans_num2=num2+1;
						else if(num1+num2+2==ans_num1+ans_num2){
							if(num1+1<ans_num1) ans_num1=num1+1,ans_num2=num2+1;
						}
					}
				}
				vis[x_][y_][num1+1][num2+1]=1;
				q[++tail]=(data){x_,y_,step+1,num1+1,num2+1};
			}
			else{
				if(vis[x_][y_][num1][num2+1]) continue;
				if(x_==tx&&y_==ty){
					if(step+1<ans) ans=step+1,ans_num1=num1,ans_num2=num2+1;
					else if(step+1==ans){
						if(num1+num2+1<ans_num1+ans_num2) ans_num1=num1,ans_num2=num2+1;
						else if(num1+num2+1==ans_num1+ans_num2){
							if(num1<ans_num1) ans_num1=num1,ans_num2=num2+1;
						}
					}
				}
				vis[x_][y_][num1][num2+1]=1;
				q[++tail]=(data){x_,y_,step+1,num1,num2+1};
			}
		}
	}
	return -1;
}
int main(){
	n=read();m=read();c1=read();c2=read();d=read();
	reg char c;
	for(reg int i=1;i<=n;i++){
		for(reg int j=1;j<=m;j++){
			c=std::getchar();
			while(c!='S'&&c!='T'&&c!='.'&&(c<'0'||c>'9')) c=std::getchar();
			if(c=='S') sx=j,sy=i;
			else if(c=='T') tx=j,ty=i;
			else if(c>='0'&&c<='9'){
				reg int x=c^48;c=std::getchar();
				while(c>='0'&&c<='9') x=x*10+(c^48),c=std::getchar();
				have[j][i]=1;
				int tmp=std::min(n,i+x-1);
				for(reg int k=std::max(i-x+1,1);k<=tmp;k++)
					t[k][max(1,j-x+1+abs(i-k))]++,t[k][min(m,j+x-1-abs(i-k))+1]--;
			}
		}
	}
	for(reg int i=1;i<=n;i++)
		for(reg int j=1;j<=m;j++) t[i][j]+=t[i][j-1];
	bfs();
	if(ans==1e9) std::puts("-1");
	else std::printf("%d %d %d",ans,ans_num1,ans_num2);
	return 0;
}
```


---

## 作者：vectorwyx (赞：0)

## 建虚点+bfs+强有力的两个最优性剪枝，不需要卡常，跑的飞快

本篇题解采用建虚点+bfs的方法，用 $step[x][y][i][j]$ 表示走到 $(x,y)$，用了 $i$ 次隐身，$j$ 次瞬移，然后直接bfs。

输入、差分、bfs什么的其他巨佬已经讲得很明白了，这里只提供两个最优性剪枝。

第一个就是所有题解都已经提到了的，如果走到当前状态的步数已经大于目前找到的最优解，那就直接continue，不需要进行拓展。

第二个是我独创的（至少这几篇题解里没有一个提到），就是说当我们已经拓展出了 $step[x][y][i][j]$ 时，没有必要再去拓展 $step[x][y][k1][k2](k1\ge i,k2\ge j)$，于是我们直接暴力地把标记数组 $vis[x][y][k1][k2](k1\ge i,k2\ge j)$ 赋为 $1$，这样接下来在拓展状态的时候遇到它们直接跳过就行了。亲测只用第二个剪枝不需要任何卡常就能通过（[Link](https://www.luogu.com.cn/record/39863912)），两个剪枝一起用跑的飞快（[Link](https://www.luogu.com.cn/record/39864651)），吸氧后拿到了最优解的第4（[Link](https://www.luogu.com.cn/record/39864687)）。


------------

代码如下：（~~你可以看到我几乎用了所有大常数的写法，但还是跑的比大多数人的卡常代码快~~）
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

const int maxn=355;
int step[maxn][maxn][16][16],a[maxn][maxn],mp[maxn][maxn],n,m,c1,c2,d,vis[maxn][maxn][16][16];

void look_around(int x,int y,int dis){
	fo(i,1,dis){
		if(x<=i) break;
		a[x-i][max(1,y-dis+i)]++,a[x-i][min(m,y+dis-i)+1]--;
	} 
	fo(i,0,dis){
		if(x+i>n) break;
		a[x+i][max(1,y-dis+i)]++,a[x+i][min(m,y+dis-i)+1]--;
	} 
}

struct Node{//存储状态的结构体 
	int x,y,c1,c2;
	Node(){}
	Node(int a,int b,int c,int d){
		x=a;
		y=b;
		c1=c;
		c2=d;
	}
};

int dx[]={-1,-1,-1,1,1,1,0,0,0,1,0,-1};//方向数组 
int dy[]={1,0,-1,-1,0,1,1,-1,1,0,-1,0};
int st=1e9;

void bfs(){
	int sx,sy;
	fo(i,1,n) fo(j,1,m) if(mp[i][j]==2){
		sx=i;
		sy=j;
		break;
	}
	queue<Node> q;
	step[sx][sy][0][0]=1;//将起点设为1避免memset 
	q.push(Node(sx,sy,0,0));
	Node t;
	while(!q.empty()){
		t=q.front();q.pop();
		if(step[t.x][t.y][t.c1][t.c2]>st) continue;//第一个剪枝 
		if(mp[t.x][t.y]==1) st=min(st,step[t.x][t.y][t.c1][t.c2]);
		fo(i,0,7){
			int tx=t.x+dx[i],ty=t.y+dy[i],_c1,_c2;
			if(tx<=0||tx>n||ty<=0||ty>m||mp[tx][ty]==-1) continue;
			_c1=t.c1+(a[tx][ty]>0),_c2=t.c2;
			if(_c1<=c1&&_c2<=c2&&vis[tx][ty][_c1][_c2]==0){
				q.push(Node(tx,ty,_c1,_c2));
				fo(i,_c1,c1) fo(j,_c2,c2){//第二个剪枝 
					if(vis[tx][ty][i][j]==1) goto T;
					vis[tx][ty][i][j]=1;
				}
				T:
				step[tx][ty][_c1][_c2]=step[t.x][t.y][t.c1][t.c2]+1;
			}
		}
		fo(i,8,11){
			int tx=t.x+dx[i]*d,ty=t.y+dy[i]*d,_c1,_c2;
			if(tx<=0||tx>n||ty<=0||ty>m||mp[tx][ty]==-1) continue;
			_c1=t.c1+(a[tx][ty]>0),_c2=t.c2+1;
			if(_c1<=c1&&_c2<=c2&&vis[tx][ty][_c1][_c2]==0){
				q.push(Node(tx,ty,_c1,_c2));
				fo(i,_c1,c1) fo(j,_c2,c2){//第二个剪枝 
					if(vis[tx][ty][i][j]==1) goto H;
					vis[tx][ty][i][j]=1;
				}
				H:
				step[tx][ty][_c1][_c2]=step[t.x][t.y][t.c1][t.c2]+1;
			}			
		}
	}
}

int main(){
	cin>>n>>m>>c1>>c2>>d;
	//mp[i][j] -1:卫兵，不能走 0:空地 1终点 2起点 
	fo(i,1,n)
		fo(j,1,m){//输入特殊处理 
			char ch=getchar();
			while(!isdigit(ch)&&(ch!='S'&&ch!='T'&&ch!='.')) ch=getchar();
			if(isdigit(ch)){
				int x=ch^48;
				ch=getchar();
				while(isdigit(ch)){
					x=(x<<1)+(x<<3)+(ch^48);
					ch=getchar();
				}
				mp[i][j]=-1;
				look_around(i,j,x-1);//差分 
			}else mp[i][j]=(ch=='S')?2:(ch=='T');
		}
	fo(i,1,n)
		fo(j,1,m) a[i][j]+=a[i][j-1];
	bfs();//bfs 
	int ans=1e9,ans_c1,ans_c2;
	fo(i,1,n)
		fo(j,1,m) if(mp[i][j]==1){
			fo(k,0,c1+c2)//保证优先级 
				fo(w,0,min(k,c1)) if(ans>step[i][j][w][k-w]&&step[i][j][w][k-w]>0){
					ans=step[i][j][w][k-w];
					ans_c1=w;
					ans_c2=k-w;
				}
			break;
		}
	if(ans==1e9) cout<<-1;
	else printf("%d %d %d\n",ans-1,ans_c1,ans_c2);
	return 0;
}
```


---

