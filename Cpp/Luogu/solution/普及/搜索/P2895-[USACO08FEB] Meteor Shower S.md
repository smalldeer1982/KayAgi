# [USACO08FEB] Meteor Shower S

## 题目描述

贝茜听说一场特别的流星雨即将到来：这些流星会撞向地球，并摧毁它们所撞击的任何东西。她为自己的安全感到焦虑，发誓要找到一个安全的地方（一个永远不会被流星摧毁的地方）。

如果将牧场放入一个直角坐标系中，贝茜现在的位置是原点，并且，贝茜不能踏上一块被流星砸过的土地。

根据预报，一共有 $M$ 颗流星 $(1\leq M\leq 50,000)$ 会坠落在农场上，其中第 $i$ 颗流星会在时刻 $T_i$（$0 \leq T _ i \leq 1000$）砸在坐标为 $(X_i,Y_i)(0\leq X_i\leq 300$，$0\leq Y_i\leq 300)$ 的格子里。流星的力量会将它所在的格子，以及周围 $4$ 个相邻的格子都化为焦土，当然贝茜也无法再在这些格子上行走。

贝茜在时刻 $0$ 开始行动，她只能在会在横纵坐标 $X,Y\ge 0$ 的区域中，平行于坐标轴行动，每 $1$ 个时刻中，她能移动到相邻的（一般是 $4$ 个）格子中的任意一个，当然目标格子要没有被烧焦才行。如果一个格子在时刻 $t$ 被流星撞击或烧焦，那么贝茜只能在 $t$ 之前的时刻在这个格子里出现。 贝茜一开始在 $(0,0)$。

请你计算一下，贝茜最少需要多少时间才能到达一个安全的格子。如果不可能到达输出 $−1$。

## 样例 #1

### 输入

```
4
0 0 2
2 1 2
1 1 2
0 3 5
```

### 输出

```
5
```

# 题解

## 作者：翼德天尊 (赞：1424)

### update:

1. 将某些口误修正。（感谢@0p9o8i7u 的提醒）


------------


#### 前言：这道题……怎么说呢……完全是一道很普通的广搜外加不普通的坑点……


------------
### 1.介绍坑点：
1.坐标不能低于0，但可以超300！

2.流星定时砸下；

3.**流星砸下时间已最早的那个为准！**

4.**如果出不去还要输出-1！**

你，有没有被坑到呢？



------------
### 2.关于这道题
首先，是一道明显的bfs题，要求最短时间，所以用队列记录；

陨石地图用一个二维数组记录，内容为砸下时间，以时间早为标准；再用一个二维数组记录每个点最短时间；

终止条件：如果搜到一个点永远不会被陨石砸到，输出该点时间，或者直到搜索结束也没有出去，输出-1（**翻译竟然没有翻出来我无语了……**


------------

## 3.代码实现+具体讲解

当然，前面讲的可能还不够令你听懂，那么下面，我会具体为大家讲解。

### 奉上AC代码：
```c
#include<bits/stdc++.h> //美丽的万能头文件
using namespace std;
int n,ma[305][305],v[305][305],sx,sy,st,ans[305][305];//分别为陨石数量，陨石砸落地图，记录是否走过地图，陨石x,y坐标及砸落时间，每个点的最少时间图。
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};//方便移动和处理陨石砸落
int ch(int a){
	if (a==-1) return 99999;
	else return a;
}//判断路过该点时是否陨石已经砸落，如果是没有陨石，相当于n年后砸落
int main(){
    scanf("%d",&n);
    for (int i=0;i<305;i++){
    	for (int j=0;j<305;j++){
    		ma[i][j]=-1;
		}
	}//陨石初始化为-1
    for (int i=1;i<=n;i++){
    	scanf("%d%d%d",&sx,&sy,&st);//输入陨石
		for (int j=0;j<5;j++){//上下左右中标记陨石
			if (sx+dx[j]>=0&&sy+dy[j]>=0&&(ma[sx+dx[j]][sy+dy[j]]==-1||ma[sx+dx[j]][sy+dy[j]]>st))//如果该标记x,y坐标大于0且该点没有被陨石砸落或已标记时间没有该时间早，标记陨石
				ma[sx+dx[j]][sy+dy[j]]=st;
		} 
	}
	queue<int> q[2];//构造队列，存储将处理点x,y坐标
	v[0][0]=1;//初始点设为已走过
	q[0].push(0);q[1].push(0);//初始点放入队列
	while (!q[0].empty()){//只要队列不为空
		int x=q[0].front(),y=q[1].front();//提取将处理点x,y坐标
		q[0].pop();q[1].pop();//删除已处理点
		int s=ans[x][y]+1;//即将标记的点时间是现在点的下一个单位
		if (ma[x][y]==-1){ //如果该点安全，输出即将标记的点的时间-1
			printf("%d\n",s-1);
			return 0;
		}
		for (int i=1;i<=4;i++){
			int xx=x+dx[i],yy=y+dy[i];//提取将处理点的坐标
			if (xx>=0&&yy>=0&&s<ch(ma[xx][yy])&&v[xx][yy]==0){//将处理点需要x,y坐标大于等于0且该点没有走过并且陨石降落时间小于现时间
				q[0].push(xx);q[1].push(yy);//放入将处理队列
				v[xx][yy]=1;//标记已走过
				ans[xx][yy]=s;//将该点时间放入数组
			}
		}
	}
	printf("-1\n");//如果出不了陨石区，输出-1
	return 0;
}
```


------------

### 4.完结撒花
看我这么用心的把代码分析了一遍，你也辛苦看完了，不顺手点个赞纪念一下吗？谢谢了！


---

## 作者：dz_ice (赞：134)

本题的细节十分的多，需要特别注意一下。

1.由于流星可能砸到从（0,0）到（300,300）的所有坐标，所以bessie有可能走到300外的点，开数组的时候不能开小了。

2.bessie有可能在走到一个格子的时候被一个流星砸死

3.
# **注意！！！**

假如有一组数据为（实际情况如图所示）

1 1 1

1 2 2

![](https://cdn.luogu.com.cn/upload/pic/65145.png)

这是需要判断一下，只有当这颗流星到达的时间小于前面流星到达的时间，才能把时间赋值给数组，而不能直接覆盖（如果没有考虑到的话你只能拿到35分）~~我因为这个想了好久~~

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y,time;
} p; //x,y存坐标，time存当前的时间 
int m,x,y,t,nx,ny,time1[305][305],c[305][305]; //time1数组存这个格子流星最早到达的时间，c存是否到过这个格子，数组开大点！！！！ 
int b1[4]= {0,0,1,-1},b2[4]= {1,-1,0,0};
queue<node>q;
int main()
{
	cin>>m;
	for(int i=0; i<=302; i++)
		for(int j=0; j<=302; j++)
			time1[i][j]=-1; //先都赋初值为-1 
	for(int i=1; i<=m; i++)
	{
		cin>>x>>y>>t;
		if(t<time1[x][y]||time1[x][y]==-1) //这颗流星到达的时间必须小于前面流星或焦土到达的时间，或者还暂时没有流星及焦土 
		time1[x][y]=t; 
		for(int i=0; i<4; i++)
		{
			nx=x+b1[i],ny=y+b2[i];
			if(nx>=0&&ny>=0&&(time1[nx][ny]==-1||t<time1[nx][ny]))
				time1[nx][ny]=t;  //枚举焦土 
		}
	}
	p.x=0,p.y=0,p.time=0,c[0][0]=1;
	q.push(p);  
	while(!q.empty())
	{
		p=q.front();q.pop();
		for(int i=0; i<4; i++)
		{
			nx=p.x+b1[i],ny=p.y+b2[i];
			if(nx>=0&&ny>=0&&c[nx][ny]==0&&(time1[nx][ny]==-1||p.time+1<time1[nx][ny])) //没有流星到过或者bessie到这个格子的时候流星还没有到达 
			{
				node txt;
				txt.x=nx,txt.y=ny,txt.time=p.time+1,c[nx][ny]=1; //扩展节点 
				q.push(txt);
				if(time1[nx][ny]==-1) //判断当前的格子是否安全 
				{
					cout<<txt.time<<endl; //输出答案 
					return 0;
				}
			}
		}
	}
	cout<<-1<<endl; //到不了安全的格子就输出-1 
	return 0;
}
```

谢谢观看！


---

## 作者：sinsop90 (赞：111)

好久没有写题解了,所以来蹭一篇题解~~~

这道题我整整调了1天,所以有很多不起人注意的细节在这道题目里。

那么废话不多说,先祝大家新年快乐(~~说好的废话不多说呢~~)

与其他题解不同的是,这道题在不同时间点会有不同的流星降落.

所以我开了一个三维数组来记录每时每刻不能走的位置的情况。

vis[time][x][y]

值得注意的是,在x-1时间点的不能走的地方在x时间点也不能走

再看题目,贝茜是在原点也就是(0,0)

我们可以分析一下样例（~~图画得有点丑~~）

当时间是0时,啥都没有发生![](https://i.loli.net/2020/01/16/36aJ7mBntKSPQ1q.png)

当时间是2时,![](https://i.loli.net/2020/01/16/MIywh1Dr4ZxP5HX.png)

时间是5时,![](https://i.loli.net/2020/01/16/j4RKAPSVWhtsDTc.png)

别喷我的画图强大技术······

所以小贝的最短路径应该是（0,0）-（1,0）-（2,0）-（3，0）-（3,1）-（3,2）

这样不会被流星砸到。

所以除了最正常的越界判断以外还要判断在小贝走到(x,y)点时这个点有没有被砸过或者在这个时间点有没有流星砸到这个点

这道题实际上也可以用dfs(Ender_32k应该会写dfs的题解),但我个人用的是bfs

STL队列不用解释吧

开个结构体

struct node{
	int x;
   int y;
   int steps;
}

bfs里面实际上个之前的一样只不过是每一次的判断是否成功需要判断的是在maxtime(最大时间)的地图(上面的t5,第三张图片)的(x,y)是否可以行走

于是就有了

```
bool check(int xx,int yy,int zz){
	if(xx>=0 && yy>=0 && vis[zz][xx][yy]==false && visk[xx][yy]==false){//越界操作
		return true;
	}
	return false;
}
void bfs(int x,int y){
	node tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.step = 0;
	Q.push(tmp);
	while(!Q.empty()){
		node _tmp = Q.front();
		for(int i=0;i<=3;i++){
			int xx = _tmp.x+fx[i][0];
			int yy = _tmp.y+fx[i][1];
			if(check(xx,yy,_tmp.step+1)){
				visk[xx][yy] = true;
				node t;
				t.x = xx;
				t.y = yy;
				t.step = _tmp.step+1;
				Q.push(t);
				if(vis[maxt][xx][yy]==false){
					flag = true;
					ans = t.step;
					return;
				}//判断是否成功
			}
		}
		Q.pop();
	}
}
```

主函数同样也要注意

当我们将vis[1][x][y]设为true时

后面时间点的(x,y)也要设为true

就有了这个

```
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i].x>>l[i].y>>l[i].time;
		maxt = max(maxt,l[i].time);
		maxx = max(maxx,l[i].x);
		maxy = max(maxy,l[i].y);
		vis[l[i].time][l[i].x][l[i].y] = true;
		for(int j=0;j<=3;j++){ 
			int xx = l[i].x+fx[j][0];
			int yy = l[i].y+fx[j][1];
//			cout<<xx<<" "<<yy<<" "<<fx[j][0]<<" "<<fx[j][1]<<endl;
			if(xx>=0 && yy>=0){
				vis[l[i].time][xx][yy] = true;
			}
		}
	}
	for(int i=0;i<=maxt-1;i++){
		for(int j=0;j<=maxx+1;j++){
			for(int k=0;k<=maxy+1;k++){
				if(vis[i][j][k]==1 && vis[i+1][j][k]==0) vis[i+1][j][k] = 1;
			}
		}
	}
	visk[0][0] = true;
	bfs(0,0);
	if(flag) cout<<ans<<endl;
	else cout<<-1<<endl;
	return 0;
}
```

完整AC代码

```
#include<bits/stdc++.h>
using namespace std;
int n;
bool vis[1005][305][305];
int fx[4][2] = {0,1,0,-1,1,0,-1,0};
int maxt = -21000,maxx = -21000,maxy = -21000;
struct lx{
	int x;
	int y;
	int time;
}l[100005];
struct node{
	int x;
	int y;
	int step;
};
bool visk[305][305];
queue<node> Q;
bool check(int xx,int yy,int zz){
	if(xx>=0 && yy>=0 && vis[zz][xx][yy]==false && visk[xx][yy]==false){
		return true;
	}
	return false;
}
bool flag = false;
int ans = 0;
void bfs(int x,int y){
	node tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.step = 0;
	Q.push(tmp);
	while(!Q.empty()){
		node _tmp = Q.front();
		for(int i=0;i<=3;i++){
			int xx = _tmp.x+fx[i][0];
			int yy = _tmp.y+fx[i][1];
			
			if(check(xx,yy,_tmp.step+1)){
				visk[xx][yy] = true;
				node t;
				t.x = xx;
				t.y = yy;
				t.step = _tmp.step+1;
				Q.push(t);
				if(vis[maxt][xx][yy]==false){
					flag = true;
					ans = t.step;
					return;
				}
			}
		}
		Q.pop();
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i].x>>l[i].y>>l[i].time;
		maxt = max(maxt,l[i].time);
		maxx = max(maxx,l[i].x);
		maxy = max(maxy,l[i].y);
		vis[l[i].time][l[i].x][l[i].y] = true;
		for(int j=0;j<=3;j++){ 
			int xx = l[i].x+fx[j][0];
			int yy = l[i].y+fx[j][1];
			if(xx>=0 && yy>=0){
				vis[l[i].time][xx][yy] = true;
			}
		}
	}
	for(int i=0;i<=maxt-1;i++){
		for(int j=0;j<=maxx+1;j++){
			for(int k=0;k<=maxy+1;k++){
				if(vis[i][j][k]==1 && vis[i+1][j][k]==0) vis[i+1][j][k] = 1;
			}
		}
	}
	visk[0][0] = true;
	bfs(0,0);
	if(flag) cout<<ans<<endl;
	else cout<<-1<<endl;
	return 0;
}
```

点个赞再走嘛

---

## 作者：很简单 (赞：42)

~~看到楼下都说细节很坑，但我感觉这就是个普通的BFS~~

AC代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;//无限大
int mp[302][302];//表示流星到达时间
bool v[302][302];//有无走过
struct point {
	int x,y,step;//步数也就是时间
};
int dx[]= {0,0,-1,1},dy[]= {-1,1,0,0};//四个方向 
int BFS(point a) {
	queue<point>q;
	q.push(a);
	v[a.x][a.y]=1;//标记为走过
	while(!q.empty()) {
		point b=q.front();
		q.pop();
		for(int d=0; d<4; ++d) {
			point c;
			c.x=b.x+dx[d],c.y=b.y+dy[d],c.step=b.step+1;
			if(c.x==-1||c.y==-1)continue;//判边界
			if(mp[c.x][c.y]==inf)return c.step;//永远不会有流星
			if(c.step<mp[c.x][c.y]&&!v[c.x][c.y]) {//在流星到达之前并且没走过
				q.push(c);
				v[c.x][c.y]=1;//标记为走过
			}
		}
	}
	return -1;
}
int main() {
	int m;
	scanf("%d",&m);
	memset(mp,0x3f,sizeof(mp));//由于是按字节赋值，刚好是mp[?][?]=inf
	for(int i=1,x,y,t; i<=m; ++i) {
		scanf("%d%d%d",&x,&y,&t);
		mp[x][y]=min(mp[x][y],t);
		for(int d=0; d<4; ++d) {
			if(x+dx[d]==-1||y+dy[d]==-1)continue;//判边界
			mp[x+dx[d]][y+dy[d]]=min(mp[x+dx[d]][y+dy[d]],t);
			//更新此位置流星最早到达时间
		}
	}
	printf("%d",BFS((point) {
		0,0,0
	}));
	//相当于
	//point a;
	//a.x=a.y=a.step=0;
	//printf("%d",BFS(a));
	return 0;
}
```

谢谢观赏 

---

## 作者：D愚者 (赞：34)

看了一下题解，竟然没有dfs，小蒟蒻的机会来了！

- 前言：首先，这道题可以用bfs和dfs做；
 

------------
**做法**


 - 用map数组记录流星砸到的地方，初始化，每次要选最小的time，不然会重复记录，影响答案。 
 - 进入深搜，f[x][y]数组用来优化，记忆化搜索，不加妥妥的TLE,~~亲身经历，非常惨痛~~
- 注意判断边界。

------------
- Code：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int m,map[350][350],f[350][350],ans=2147483647;
void dfs(int x,int y,int t){
	if(map[x][y]<=t||t>=ans||t>=f[x][y])//优化
		return ;
	f[x][y]=t;
	if(map[x][y]>2100000000){
		ans=min(t,ans);
		return;
	}
	dfs(x+1,y,t+1);
	if(x-1>=0)	dfs(x-1,y,t+1);//判断边界
	dfs(x,y+1,t+1);
	if(y-1>=0)	dfs(x,y-1,t+1);
}
int main(){
//	freopen("meteor.in","r",stdin);
//	freopen("meteor.out","w",stdout);
	memset(map,0x7f,sizeof(map));
	memset(f,0xa7f,sizeof(f));
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int x,y,t;
		scanf("%d %d %d",&x,&y,&t);
		map[x][y]=min(map[x][y],t);
		map[x+1][y]=min(map[x+1][y],t);//取最小的time
		if(x-1>=0)//判断边界
			map[x-1][y]=min(map[x-1][y],t);
		map[x][y+1]=min(map[x][y+1],t);
		if(y-1>=0)
			map[x][y-1]=min(map[x][y-1],t);
	}
	dfs(0,0,0);
	if(ans==2147483647)//如果没有逃脱
		printf("-1");
	else
		printf("%d",ans);
	return 0;
}
```


---

## 作者：houzhiyuan (赞：32)

# P2895 [USACO08FEB]Meteor Shower S

算法：BFS 适合初学者练习，细节比较多。

首先，这题BFS过程中，必须要记录三个元素：x轴，y轴和时间；

x轴和y轴的处理都是BFS的基础，这里主要讲时间的处理。

### 关于时间初始化

如果每种情况都暴力枚举每一个陨石，比如会TLE，考虑进行初始化。

**因为每个方格一旦被陨石砸到，就永远都走不了，所以要在所有陨石时间中取最小。**

如果时间是正无穷的就表示是安全的地方，代码：
```cpp
for(i=1; i<=n; i++) {
		cin>>x>>y>>t;//陨石砸的点和周边四个点都是不能走的。
		f[x][y]=min(f[x][y],t);
		if(x-1>=0) {
			f[x-1][y]=min(f[x-1][y],t);
		}
		f[x+1][y]=min(f[x+1][y],t);
		if(y-1>=0) {
			f[x][y-1]=min(f[x][y-1],t);
		}
		f[x][y+1]=min(f[x][y+1],t);
}
```
### 关于方向数组

因为走到一个点，尽量早一点走到，容易想到只要向上，右走。

但一提交，63分QWQ。

细细一想，可能最短路线被陨石挡住，可能可以绕过陨石区域而走到安全的地方，所以需要四个方向

另外，一定要注意数组的边界

下面是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[500][500]={},i,x,y,t,dp[500][500]={},sum[500][500]={},fx[170000]={},fy[170000]={},tail=1,j;
int q[4]={1,0,-1,0};
int w[4]={0,1,0,-1};
int main() {
	cin>>n;
	memset(f,10,sizeof(f));
	for(i=1; i<=n; i++) {//初始化
		cin>>x>>y>>t;
		f[x][y]=min(f[x][y],t);
		if(x-1>=0) {
			f[x-1][y]=min(f[x-1][y],t);
		}
		f[x+1][y]=min(f[x+1][y],t);
		if(y-1>=0) {
			f[x][y-1]=min(f[x][y-1],t);
		}
		f[x][y+1]=min(f[x][y+1],t);
	}
    dp[0][0]=1;//dp是标记当前点已经走过
    sum[0][0]=0;//sum是走到当前点的最短时间
    fx[1]=0;//分别表示x轴和y轴
    fy[1]=0;
    for(i=1;i<=tail;i++){//蒟蒻太菜了，只会手打队列
    	if(f[fx[i]][fy[i]]>9999999){//如果到了安全的地方
    		cout<<sum[fx[i]][fy[i]];
    		return 0;
		}
    	for(j=0;j<=3;j++){
    		int xx=fx[i]+q[j];
    		int yy=fy[i]+w[j];
    		if(xx>=0&&yy>=0&&dp[xx][yy]==0&&sum[fx[i]][fy[i]]+1<f[xx][yy]){//如果没走过，而且是安全的
    			dp[xx][yy]=1;//都标记一下
    			sum[xx][yy]=sum[fx[i]][fy[i]]+1;
    			fx[++tail]=xx;
    			fy[tail]=yy;
			}
		}
	}
	cout<<-1; 
	return 0;
}
```


---

## 作者：HuangBo (赞：12)

**自己写了一份，代码风格极其#%&*^……**

不过还好大家思路都是差不多的~.~

2333……
```cpp
/*
机翻（其实已经很清晰了）： 
贝西听到一场非同寻常的流星雨即将来临；有报道称，这些流星将撞击地球并摧毁它们所撞上的任何东西。出于对自己安全的担忧，她发誓要找到一个安全的地方(一个永远不会被流星摧毁的地方)。她目前正在坐标平面的原点吃草，她想转移到一个新的、更安全的地方，同时避免在途中被流星摧毁。
报道称，M流星(1≤M≤50，000)将撞击，流星I将在时间Ti(0≤Ti≤1，000)上撞击点(0≤xi≤300；0≤Ii≤300)。每一颗流星都摧毁了它撞击的点以及四个直线相邻的点阵点。
贝西在时间为0时离开原点，并能在第一象限中以每秒一段距离单位的速度与轴平行运动，到达尚未被流星摧毁的(通常为4)相邻的直线点。她不能在任何时间超过或等于它被摧毁的时间点上定位)。
确定贝西到达安全地点所需的最短时间。
*/
#include<cstdio>
#include<algorithm>
using namespace std;
#define inf 200000000
int dx[]={0,0,-1,1},dy[]={1,-1,0,0};//移动方式;
int n,x,y,t,map[310][310],f[310][310];
struct data{int x,y,t;}q[50010];
void bfs()
{
    int t=0,w=1;
    f[0][0]=1;
    if(map[0][0]==inf)
    {
    	puts("0");
        return;
    }
    while(t<w)
    {
        int x=q[t].x,y=q[t].y,time=q[t].t;
        t++;
        for(int i=0;i<4;i++)
        {
            int nx=x+dx[i],ny=y+dy[i];
            if(f[nx][ny]||nx<0||ny<0||time+1>=map[nx][ny]) continue;
            if(map[nx][ny]==inf)//如果到了安全的地方，输出 
            {
                printf("%d",time+1);//还是少用time的好，以免关键字冲突;
                return;
            }
            q[w].x=nx,q[w].y=ny,q[w++].t=time+1;
            f[nx][ny]=1;//标记能走 
        }
    }
	puts("-1");
}
int main()
{
	while(1);//2333
    for(int i=0;i<=303;i++)//初始化;
        for(int j=0;j<=303;j++)
            map[i][j]=inf;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&x,&y,&t);
        map[x][y]=min(map[x][y],t);
        for(int j=0;j<4;j++)
        {
            int nx=x+dx[j],ny=y+dy[j];
            if(nx<0 || ny<0) continue;
            map[nx][ny]=min(map[nx][ny],t);//记录最先砸到的时间 
        }
    }
    bfs();
    return 0;
}
```
为了防止 _抄袭_ 等行为……

请勿抄袭~~(当然你要“借鉴”我也没有办法[后果自负])~~

安利一下别人家的(精华)博客:

https://blog.csdn.net/qq_36100991/article/details/78084397

https://blog.csdn.net/Regina8023/article/details/44567335

---

## 作者：yashem66 (赞：11)

关于这道题的翻译：根据预报，一共有M颗流星(1 <= M <= 50,000)会坠落在农场上，其中第i颗流星会在时刻T\_i (0 <= T\_i <= 1,000)砸在坐标为(X\_i, Y\_i) (0 <= X\_i <= 300；0 <= Y\_i <= 300)的格子里。流星的力量会将它所在的格子，以及周围4个相邻的格子都化为焦土，当然贝茜也无法再在这些格子上行走。

贝茜在时刻0开始行动，它只能在第一象限中，平行于坐标轴行动，每1个时刻中，她能移动到相邻的（一般是4个）格子中的任意一个，当然目标格子要没有被烧焦才行。如果一个格子在时刻t被流星撞击或烧焦，那么贝茜只能在t之前的时刻在这个格子里出现。

请你计算一下，贝茜最少需要多少时间才能到达一个安全的格子。


每次走到某个点的时候判断是否可走有一些麻烦，我们可以预处理出一个Map数组来表示该格点在Map[i][j]之后即为不可走。然后进行正常的广搜即可。


```cpp
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<cstring>
#include<iostream>
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
struct Node
{
    int x,y;
    int t;
    Node() {x=y=t=0;}
}que[200000];
int m;
int Map[400][400];
bool u[400][400];
int f=0,r=1;
int dir[5][2]={{-1,0},{1,0},{0,1},{0,-1},{0,0}};
int main()
{
    freopen("meteor.in","r",stdin);
    freopen("meteor.out","w",stdout);
    scanf("%d",&m);
    memset(Map,-1,sizeof Map);
    for(int i=1;i<=m;i++)
    {
        int x,y,t;
        scanf("%d%d%d",&x,&y,&t);
        for(int k=0;k<5;k++)
        {
            int a=x+dir[k][0];
            int b=y+dir[k][1];
            if(a<0 || b<0) continue;
            if(Map[a][b]!=-1) Map[a][b]=min(Map[a][b],t);
            else Map[a][b]=t;
        }
    }
    que[r].t=0;
    que[r].x=0;
    que[r++].y=0;
    u[0][0]=1;
    while(r-f>1)
    {
        f++;
        for(int k=0;k<4;k++)
        {
            int a=que[f].x+dir[k][0];
            int b=que[f].y+dir[k][1];
            if(a<0 || b<0) continue;
            if(Map[a][b]==-1)
            {
                printf("%d",que[f].t+1);
                return 0;
            }
            if(u[a][b] || que[f].t+1>=Map[a][b]) continue;
            que[r].t=que[f].t+1;
            que[r].x=a;
            que[r++].y=b;
            u[a][b]=1;
        }
    }
    printf("-1");
    fclose(stdin);
    fclose(stdout);
    return 0;
}

```

---

## 作者：子归 (赞：8)

# 数组模拟队列+预处理
一开始看见陨石时间就觉得有点麻烦，于是就想到了预处理，把矩阵赋成陨石下落的时间，这样就可以灵活的处理这个麻烦的东西了，其他的就都是广搜。
## 关于预处理
  ![](https://i.loli.net/2019/03/27/5c9b62370f8d5.png)
  ~~这个图是真的难画~~  
  就这样预处理，把陨石将要落下的点一一赋值，因为只有第一象限，这个图像上下颠倒是没有关系的。
  ## 初始时间
  把每一个点的初始时间都赋为inf，因为我们比较是否到了陨石砸地的时间是比较目前时间与数组上那个点的大小，如果大了，就说明不能走，那么如果我们给他的初始值为0的话，他无论怎样就都是大的。
  ## 判断
  判断时间的时候是要把t加1与目标点比较，这我相信大家都能懂。每入队一个点要标记。
  ## 上代码吧
  ```c
#include<bits/stdc++.h>
using namespace std;
#define N 50005
#define inf 0x3f3f3f3f//最大值. 
int n,l=1;
int xi[N],yi[N],ti[N];
int dx[4]= {1,-1,0,0},dy[4]= {0,0,1,-1};
int a[500][500];
int bj[500][500];
struct edge {
	int x;
	int y;
	int t;
} aa[N];//结构体存入坐标和时间。 
void cl(int x,int y,int t) {//预处理，将每一个点都赋为陨石来临时的时间，取小。 
	if((a[x][y]>t||a[x][y]==inf))
		a[x][y]=t;//如果之前没有被砸，就赋值，或者如果之前赋过了但是比这次时间长就改变值。 
	for(int i=0; i<4; i++) {
		int xx=x+dx[i],yy=y+dy[i];//四周赋值。 
		if(xx<0||yy<0)
			continue;
		if((a[xx][yy]>t||a[xx][yy]==inf))
			a[xx][yy]=t;
	}
}
void xz(int x,int y,int t) {//数组模拟队列。 
	int f,r;
	f=r=0;
	aa[++r].x=x;
	aa[r].y=y;
	aa[r].t=t;//入队。 
	while(f<r) {
		f++;
		int xx=aa[f].x;
		int yy=aa[f].y;
		int tt=aa[f].t;//出队。 
		for(int i=0; i<4; i++) {
			int xxx=xx+dx[i],yyy=yy+dy[i];
			if(xxx<0||yyy<0)
				continue;//只能在第一象限。 
			if(a[xxx][yyy]==inf) {
				l=0;//如果到了一个永远安全的点，就返回了,并改变标记变量。 
				printf("%d",tt+1);
				return ;
			}
			if(xxx>=0&&yyy>=0&&!bj[xxx][yyy]&tt+1<a[xxx][yyy]) {//判断时间是否充裕。 
				aa[++r].x=xxx;
				aa[r].y=yyy;
				aa[r].t=tt+1;
				bj[xxx][yyy]=1;
			}
		}
	}
}
int main() {
	scanf("%d",&n);
	memset(a,inf,sizeof(a));//每个点的时间都赋为最大，因为用时间的话，每一个都是大于0的。 
	for(int i=1; i<=n; i++) {
		scanf("%d%d%d",&xi[i],&yi[i],&ti[i]);
		cl(xi[i],yi[i],ti[i]);//处理陨石。 
	}
	bj[0][0]=1;//标记初始点。 
	if(a[0][0]==inf) {//如果初始点没有陨石，就是0秒。 
		printf("0");
		return 0;
	}
	xz(0,0,0);
	if(l)//永远都走不到安全的地方。 
		printf("-1");
}
```


---

## 作者：NKL丶 (赞：6)

## ~~首先吐槽一句，这题不注意细节真的十分坑~~
推荐在做这一道题目前先做一下 **[3395 路障](https://www.luogu.org/problemnew/show/P3395)** 这一道题目，这样子的话你做这一道题目更有把握一点点。

首先这一道题目很明显是搜索，不难发现这一题用BFS会好一些。我们可以将流星坠落的时间进行预处理。假如Bessie在走到这一个格子的时候，所用的步数大于等于坠落的时间，也就是说，Bessie会被砸死或者被流星的坑烧死，即不能走在这一个格子上，反之就可以走。注意一点，流星坠落之后范围是 **上下左右中** 这五个方向，所以在预处理的时候需要注意一下。

## 注意一个点：Bessie的x坐标和y坐标并不是局限于300，而是可以往300外面走的，同理流星的坠落波也可以出去300，不判你就只有92分了。
给出代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,vis[315][315],x[95005],y[95005],step[95005],a,b,c,ans=4<<15;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
void debugs()//调试 
{
    for(int i=0;i<=10;i++)
    {
    for(int j=0;j<=10;j++)if(vis[i][j]!=2139062143)printf("%3d",vis[i][j]);else printf("  0");
    cout<<endl;
    }
    cout<<endl<<endl;
}
int min(int a1,int b1){return a1<b1?a1:b1;}
void BFS()
{
    int head=1,tail=1;
    if(vis[0][0]==2139062143)//幸运 
    {
        cout<<0<<endl;//不用走 
        return;
    }
    while(head<=tail)
    {
        for(int i=0;i<4;i++)
        {
            int xx=x[head]+dx[i];
            int yy=y[head]+dy[i];
            if(xx>-1&&yy>-1&&xx<=303&&yy<=303&&step[head]+1<vis[xx][yy])//可走 
            {
                tail++;//入队 
                x[tail]=xx;
                y[tail]=yy;
                step[tail]=step[head]+1;
                if(vis[xx][yy]==2139062143)//安全的地方 
                    ans=min(ans,step[head]+1);//更新答案 
                vis[xx][yy]=1;//标记 
            //	debugs();
            }
        }
        head++;
    }
    if(ans!=4<<15)cout<<ans<<endl;//可以存活下来 
    else
    cout<<-1<<endl;//不能 
}
int main()
{
    memset(vis,127,sizeof(vis));//初始化 
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b>>c;
        vis[a][b]=min(vis[a][b],c);//砸下来 
        for(int i=0;i<4;i++)//分散 
        {
            int xx=a+dx[i];
            int yy=b+dy[i];
            if(xx>-1&&yy>-1&&xx<=305&&yy<=305)
            vis[xx][yy]=min(vis[xx][yy],c);
        }
        if(vis[0][0]==0)//一出场就死 
        {
            cout<<-1<<endl;
            return 0;
        }
    }
    //debugs();
    BFS();
    return 0;
}
```



---

## 作者：RioBlu (赞：5)

一个比较难的题目
___
思路：从0,0开始，广度搜索

我首先把时间排序，sort了一下

然后有一个叫aq的二位布尔数组储存这里是否真正的安全，安全为0

然后开始比较熟知的广度搜索

while(还有东西)

{

1.出队

2.然后判断这里是否真正的安全，如果真正安全就输出时间，然后结束程序

3.看看现在有没有流星掉下来

4.发现这里已经被流星影响了就continue

5.如果四周有没走过的且没被流星影响的就加入队列

}

```
#include<bits/stdc++.h>
using namespace std;
struct hong
{
	int x,y,ti;//x第几列 y第几行 
}o[50005];
long long a,b,c,d,e,f,now,nx[4]={-1,1,0,0},ny[4]={0,0,1,-1},last,tou,wei,x[305*305],y[305*305],nt[305*305];//x,y,nt都是队列,nt存时间

bool aq[400][400],nmap[400][400],vi[400][400];//aq:判断现在是否真正的安全(0为真正的安全)，nmap:现在的地图（1为被流星影响）,vi:是否访问过
void push1(int x1_,int y1_,int nt1)//加入队列
{
	x[wei]=x1_;
	y[wei]=y1_;
	nt[wei]=nt1;
	wei++;//尾巴指针++
	vi[x1_][y1_]=1;//标记
}
bool cmp(hong x1,hong x2)//结构体排序用的
{
	return x1.ti<x2.ti;
}
int main()
{
//	freopen("2713.out","w",stdout);
//	freopen("2713.in","r",stdin);
	cin>>a;
	for(int s=0;s<a;s++)
	{
		cin>>o[s].x>>o[s].y>>o[s].ti;
		aq[o[s].x][o[s].y]=1;
		aq[o[s].x+1][o[s].y]=1;
		aq[o[s].x-1][o[s].y]=1;
		aq[o[s].x][o[s].y-1]=1;
		aq[o[s].x][o[s].y+1]=1;
	}
	sort(o,o+a,cmp);//排序
	push1(0,0,0);
	while(tou<wei)
	{
		b=x[tou];
		c=y[tou];
		d=nt[tou];
		tou++;//出队列
		if(aq[b][c]==0)//这里是真正的安全！
		{
			cout<<d<<endl;
			return 0;
		}
		while(d==o[now].ti)//看看现在有没有流星落地
		{
			nmap[o[now].x][o[now].y]=1;
			nmap[o[now].x][o[now].y+1]=1;
			nmap[o[now].x][o[now].y-1]=1;
			nmap[o[now].x-1][o[now].y]=1;
			nmap[o[now].x+1][o[now].y]=1;
			now++;
		}
		if(nmap[b][c]==1)continue;//被流星影响
		for(int s=0;s<4;s++)//向四周扩散
		{
			e=b+nx[s],f=c+ny[s];
			if(e<0||f<0)continue;//越界
			if(nmap[e][f]==0&&vi[e][f]==0)
			{
				push1(e,f,d+1);
			}
		}
	}
	cout<<-1<<endl;//无论如何也逃离不了，输出-1
	return 0;
}

```

---

## 作者：Arghariza (赞：4)

好久都没有写题解了

（~~是完全没有写过吧？~~）

------------

首先我们看看这道水题

大家大多都是用bfs做的，~~谁说dfs做不了？~~

~~bfs做需要80几行，但是~~用dfs做只用30多行！

```c
#include<bits/stdc++.h>
using namespace std;
int m, maps[1001][1001], f[1001][1001], ans = 2147483647;
void dfs(int x, int y, int k) {
    if(maps[x][y] <= k || k >= ans || k >= f[x][y]) return;
    f[x][y] = k;
    if(maps[x][y] > 2100000000) {
        ans = min(k, ans);
        return;
    } else {
        dfs(x + 1, y, k + 1);
        if(x >= 1) dfs(x - 1, y, k + 1);
        dfs(x, y + 1, k + 1);
        if(y >= 1) dfs(x, y - 1, k + 1);
    }
}
int main(){
    memset(maps, 0x7f, sizeof(maps));
    memset(f, 0xa7f, sizeof(f));
    cin >> m;
    for(int i = 1; i <= m; i++) {
        int x, y, k;
        cin >> x >> y >> k;
        maps[x][y] = min(maps[x][y], k);
        maps[x + 1][y] = min(maps[x + 1][y], k);
        if(x >= 1) maps[x - 1][y] = min(maps[x - 1][y], k);
        maps[x][y + 1] = min(maps[x][y + 1], k);
        if(y >= 1) maps[x][y - 1] = min(maps[x][y - 1], k);
    }
    dfs(0, 0, 0);
    if(ans == 2147483647) cout << -1;
    else cout << ans;
    return 0;
}
```

值得注意的是，初始化maps,f数组时必须赋值成0x7f和0x7af~~其实是调了0.5h后看到某大佬的题解恍然大悟~~

---

## 作者：Aleph1022 (赞：3)

WA了几次，原因千奇百怪

参考前面的题解，我使用数组标记了某一个点无法通行的时间

不同的是我用了STL的queue。

看到这道题，是用bfs搜出来的，然后看到了Meteor以为是科幻的，没想到……反正进来了就做到底，顺便复习下bfs
```cpp
#include <bits/stdc++.h>
using namespace std;
const int nx[4] = {-1, 0, 1, 0};
const int ny[4] = { 0,-1, 0, 1};
struct note
{
    note(){}
    note(int a,int b):x(a),y(b){}
    note(int a,int b,int c):x(a),y(b),cnt(c){}
    int x,y,cnt;
};
int mtr[310][310],vis[310][310],m;
int minn;
queue<note> q;
int main()
{
    memset(mtr,-1,sizeof mtr);
    cin >> m;
    for(int i = 1;i <= m;i++)
    {
        int x,y,t;
        cin >> x >> y >> t;
        mtr[x][y] = mtr[x][y] != -1 ? min(mtr[x][y],t) : t;
        for(int i = 0;i < 4;i++)
            if(x + nx[i] >= 0 && y + ny[i] >= 0) mtr[x + nx[i]][y + ny[i]] = mtr[x + nx[i]][y + ny[i]] != -1 ? min(mtr[x + nx[i]][y + ny[i]],t) : t;
    }
    q.push(note(0,0,0));
    vis[0][0] = 1;
    while(!q.empty())
    {
        note cur = q.front();
        if(mtr[cur.x][cur.y] == -1)
        {
            cout << cur.cnt << endl;
            return 0;
        }
        q.pop();
        for(int i = 0;i < 4;i++)
        {
            int dx = cur.x + nx[i];
            int dy = cur.y + ny[i];
            if(dx < 0 || dy < 0 || vis[dx][dy] || (cur.cnt + 1 >=/*注意了是>=>=>=>=*/ mtr[dx][dy] && mtr[dx][dy] != -1))
                continue;
            vis[dx][dy] = 1;
            q.push(note(dx,dy,cur.cnt + 1));
        }
    }
    puts("-1");
}
```

---

## 作者：Tsumi (赞：3)

## 蒟蒻の题解
天啊这题怎么这么坑QWQ
我用的方法是酱紫的：

开一个数组记录是否可走

开另一个记录陨石砸下的时间

如果时间比陨石砸下的时间还多了1，push进入队列

```cpp
#include<bits/stdc++.h>
using namespace std;
#define QAQ return 0
struct qwq{
    int x,y,time;
};
queue<qwq> bfs;
bool a[500][500];
int boom[500][500];
int dx[5]={1,0,0,-1,0};
int dy[5]={0,1,-1,0,0};
int n;
int xx,yy,tt;
int main() {
    cin>>n;
    memset(boom,-1,sizeof(boom));
    //初始化boom数组，记录陨石boom地砸下的时间
    for(int i=1;i<=n;i++){
        cin>>xx>>yy>>tt;
         for(int j=0;j<5;j++){
         	if(xx+dx[j]<0||yy+dy[j]<0) continue;
            if(boom[xx+dx[j]][yy+dy[j]]!=-1){
            	boom[xx+dx[j]][yy+dy[j]]=min(boom[xx+dx[j]][yy+dy[j]],tt);
			} 
            //坑死我了QWQ
            
            //之前原位置没有取最小值，看了好久...
            
            else boom[xx+dx[j]][yy+dy[j]]=tt;
        }

    }
    bfs.push({0,0,0});
    a[0][0]=1;
    QAQ;//防抄袭
    //从0,0开始走，因为是第一象限
    while(!bfs.empty()){
        qwq head=bfs.front();
        if(boom[head.x][head.y]==-1){
            cout<<head.time<<endl;
            return 0;
        }
		bfs.pop();
        for(int i=0;i<4;i++){
            int tx=head.x+dx[i],ty=head.y+dy[i];
            if(tx<0||ty<0||a[tx][ty]==1) continue;
            //如果走过了or出界，continue
            if(head.time>=boom[tx][ty]-1 && boom[tx][ty]!=-1) continue;
            //如果砸过了 and 此处不为陨石坑，continue
        	a[tx][ty]=1;
            bfs.push({tx,ty,head.time+1});
        }
    }
    cout<<-1;
    
    return 0;
}
```

#### QWQ还是挺水的，只能是我太蒻了

---

## 作者：_•́へ•́╬_ (赞：3)

```cpp
#include<bits/stdc++.h>//懒人专用头文件
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define rpt(n) for(register int ttxyc=0;ttxyc<n;++ttxyc)//宏定义
using namespace std;
inline int read()//快读
{
	register int x=0,t=0;register char c=getchar();for(;c<'0'||c>'9';t|=c=='-',c=getchar());
	for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=getchar());return t?-x:x;
}
struct node{int x,y,step;};
int m,x,y,t,dx[5]={1,-1,0,0,0},dy[5]={0,0,1,-1,0},α[302][302];queue<node>q;
main()
{
	for(register int i=0;i<302;++i)for(register int j=0;j<302;++j)α[i][j]=0xAC66666;//memset
	m=read();
	rpt(m)
	{
		x=read();y=read();t=read();
		for(register int i=0;i<5;++i)//摧毁的5个点
		{
			if(x+dx[i]<0||y+dy[i]<0)continue;
			α[x+dx[i]][y+dy[i]]=min(α[x+dx[i]][y+dy[i]],t);
		}//α[x][y]表示(x,y)这个点最后会在什么时候被摧毁
	}//预处理α数组
	if(α[0][0]==0xAC66666){puts("0");return 0;}//原点即安全
	for(q.push((node){0,0,0});q.size();q.pop())
	{
		x=q.front().x;y=q.front().y;
		for(register int i=0;i<4;++i)//只有4种走法，不能停留（因为不是最优解）
			if(x+dx[i]>=0&&y+dy[i]>=0&&α[x+dx[i]][y+dy[i]]>q.front().step+1)
			{
				if(α[x+dx[i]][y+dy[i]]==0xAC66666)
					{printf("%d",q.front().step+1);return 0;}//马上就要到安全的地方辣！
				q.push((node){x+dx[i],y+dy[i],q.front().step+1});//入队
				α[x+dx[i]][y+dy[i]]=-1;//设置成不可走，避免从另一个地方再走一遍
			}
	}
	puts("-1");//无解
}/**/
```

---

## 作者：shihao (赞：3)

这道题直接使用宽搜就可以，但是队列更快
先给宽搜的（这个是用数组模拟队列）
```
#include <stdio.h>
#include <string.h>
#include <iostream>
#define INF 100000000
#define le 302
#define lne 50005
using namespace std;
const int elem = 301;
typedef struct{
    int r,c,dis;
}re;
re q[le * le];
int der[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int vis[le][le];
int map[le][le];
int m;
void init(){
    int i,j;
    for(i = 0 ; i < le ; i++)
        for(j = 0 ; j < le ; j++)
            map[i][j] = INF;
}
 
void input(){
    int i,u,v,w;
    init();
    for(i = 0 ; i < m ; i++)
	{
        scanf("%d%d%d",&u,&v,&w);
        if(w < map[u][v]) map[u][v] = w;
        if(u > 0){
            if(map[u-1][v] > w) map[u-1][v] = w;
        }
        if(map[u+1][v] > w) map[u+1][v] = w;
        if(v > 0){
            if(map[u][v-1] > w) map[u][v-1] = w;
        }
        if(map[u][v+1] > w) map[u][v+1] = w;
    }
}
int BFS()
{
    int front = 0 , rear = 1 , i;
    re tem , g;
    if(map[0][0] == INF) return 0;
    if(map[0][0] == 0) return -1;
    memset(vis , 0 , sizeof(vis));
    tem.r = 0; tem.c = 0; tem.dis = 0;
    q[front] = tem;
    vis[0][0] = 0;
    while(front != rear){
        tem = q[front++];
        if(front == lne) front = 0;
        for(i = 0 ; i < 4 ; i++){
            g.r = tem.r + der[i][0];
            g.c = tem.c + der[i][1];
            g.dis = tem.dis + 1;
            if(g.r >= 0 && g.r <= elem && g.c >= 0 && g.c <= elem)
                if(!vis[g.r][g.c] && map[g.r][g.c] > g.dis){
                    if(map[g.r][g.c] == INF){
                        return g.dis;
                    }
                    vis[g.r][g.c] = 1;
                    q[rear++] = g;
                    if(rear == lne) rear = 0;
                }
        }
    }
    return -1;
}
void deal()
{
    int ans = BFS();
    printf("%d\n",ans);
}
int main(void)
{
    while(scanf("%d",&m) == 1)
	{
        input();
        deal();
    }
    return 0;
}

```
这个是队列的
```
#include <cstdio>   
#include <queue>  
#include <cstring>  
using namespace std;  
#define INT_MAX 1 << 30  
#define MAX 400  
typedef long long ll;  
int n;  
struct node{  
    int x;  
    int y;  
    int t;  
}s,current;  
queue<node>q;//寻找最短时间时层层推进  
int map[MAX][MAX];//存储时间  
int dir[5][2] = {{0,0},{0,1},{0,-1},{1,0},{-1,0}};//坐标的拓展  
int bfs()//从坐标原点到MAX处层层前进  
{  
    if(map[0][0] == 0)  return -1;  
    if(map[0][0] == -1) return 0;  
    s.x = s.y = s.t = 0;  
    q.push(s);  
    while (!q.empty()){  
        current = q.front();  
        q.pop();  
        for (int i = 0; i < 5; i += 1){//故伎重演，扩展每一层  
            s.x = current.x+dir[i][0];  
            s.y = current.y+dir[i][1];  
            s.t = current.t+1;  
            if(s.x < 0||s.x > MAX||s.y < 0||s.y > MAX)  continue;  
            if(map[s.x][s.y] == -1) return s.t;  
            if(s.t >= map[s.x][s.y])  continue;  
            map[s.x][s.y] = s.t;  
            q.push(s);  
        }  
    }  
    return -1;  
}  
void in()  
{  
    memset(map,-1,sizeof(map));  
    scanf("%d",&n);  
    while(n--){  
        int x,y,t;  
        scanf("%d%d%d",&x,&y,&t);  
        for (int i = 0; i < 5; i += 1){//扩展功能，map存放每个流星落点附近点的时间最小值  
            int x1 = x+dir[i][0];  
            int y1 = y+dir[i][1];  
            if(x1 < 0||x1 >= MAX||y1 < 0||y1 >= MAX)  continue;  
            if(map[x1][y1] == -1)    map[x1][y1] = t;  
            else   map[x1][y1] = min(map[x1][y1],t);  
        }  
    }  
}  
int main()  
{  
    in();  
    printf("%d\n",bfs());  
    return 0;  
}
```
别借鉴太多=）

---

## 作者：Jameswood (赞：3)

[原题链接](https://www.luogu.org/problem/show?pid=2895)

此处翻译有巨坑，强烈抗议！！

推荐翻译：[（人家机翻都比原题好）](https://www.luogu.org/discuss/show?postid=18217)

题目大意：

现有一个平面直角坐标系，牛的初始位置为（0，0），且可以在 x、y 的正半轴以及第一象限内活动。在左下角为（0，0），右上角为（300，300）的区域中会陆续出现面积为 4 的十字形路障，求最短的通向永无路障的点的步数。若无法走到输出-1。

相似题目：[P1332 血色先锋队](https://www.luogu.org/problemnew/show/P1332)

我的做法：

这是一道稍有特殊的 BFS 题目（也就是不是特别特殊 QAQ ），数据读入之后将它的十字型区域赋值为时间（如果重复取最小值），做这一步时要注意边界，容易RE。

BFS 初始不变，在判定边界的时候加一个条件，如果当前的步数大于当前区域的值，就跳过（即此时流星已经砸下）。

要加一个 bool 数组，走过的点不能走，不然会超时 [QAQ](https://www.luogu.org/record/show?rid=8903433)

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
const int SIZE=305;
struct node{
    int x,y,s;
}p,t;
int m,a[SIZE][SIZE],dir[4][2]={0,1,0,-1,1,0,-1,0},ans=1<<30;
bool tu[SIZE][SIZE];
queue <node> q;
int main(){
    int x,y,time;
    scanf("%d",&m);
    for(int i=0;i<305;i++)
        for(int j=0;j<305;j++){
            a[i][j]=1<<30;tu[i][j]=0;
        }
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&x,&y,&time);
        if(x!=0) a[x-1][y]=min(time,a[x-1][y]);
        if(y!=0) a[x][y-1]=min(time,a[x][y-1]);
        a[x+1][y]=min(time,a[x+1][y]);a[x][y+1]=min(time,a[x][y+1]); 
        a[x][y]=min(time,a[x][y]);
    }
    p.x=0;p.y=0;p.s=0;
    q.push(p);
    while(!q.empty()){
        t=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            p.x=t.x+dir[i][0];
            p.y=t.y+dir[i][1];
            if(p.x<0||p.x>=305||p.y<0||p.y>=305||t.s+1>=a[p.x][p.y]||tu[p.x][p.y]==1) continue;
            p.s=t.s+1;tu[p.x][p.y]=1;
            if(a[p.x][p.y]==1<<30){
                ans=p.s;break;
            }
            q.push(p);
        }
        if(ans!=1<<30){
            printf("%d\n",ans);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
```

流星雨最好看了，期待有朝一日能看到 QAQ ！

![](https://cdn.luogu.com.cn/upload/pic/25068.png )

---

