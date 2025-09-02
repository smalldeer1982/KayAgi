# 「WWOI R1」WSM 游戏

## 题目背景

[$\texttt{WSM}$](https://gitblock.cn/Projects/769996) 是一款冒险游戏，WSM 是这个游戏的主角。

## 题目描述

有一个由 $n$ 行 $m$ 列格子构成的地图。WSM 要从地图的左上角坐标为 $(1,1)$ 的格子出发，到达坐标为 $(a,b)$ 的格子。 

地图上有 $k$ 个带有密码的锁和 $t$ 个带有密码的钥匙。  
当 WSM 到达密码为 $r$ 的钥匙所在的格子，密码为 $r$ 的锁就会立刻消失。     
任何一个时刻，WSM 都必须在地图内，且所处的格子必须**没有锁**。  
如果某个格子中既有密码为 $r$ 的锁又有密码为 $r$ 的钥匙，那么 WSM 可以进入到这个格子。  

地图上还存在着 $p$ 个普通道具和 $q$ 个魔法物品。WSM 可以消耗步数来使用地图上的普通道具和魔法物品。所有的道具和魔法物品均可重复使用。  

---

道具很原始，WSM 只能使用和自己在同一格的道具。  
假设 WSM 当前位置为 $(x,y)$，使用道具后移动到 $(x',y')$。  
|道具编号|移动后位置|
|:-:|:-:|
$1$|WSM 向上走一格，即 $(x',y')=(x-1,y)$|
$2$|WSM 向下走一格，即 $(x',y')=(x+1,y)$|
$3$|WSM 向左走一格，即 $(x',y')=(x,y-1)$|
$4$|WSM 向右走一格，即 $(x',y')=(x,y+1)$|

---

魔法物品很脆弱，当 WSM 和某一个魔法物品处在同一格时，这个魔法物品会**永久消失**。   
魔法物品很强大，WSM 可以使用地图上任意一个魔法物品。  
假设 WSM 当前位置为 $(x,y)$，魔法物品的位置为 $(x_0,y_0)$，使用魔法物品后移动到 $(x',y')$。  
|魔法物品编号|移动后位置|
|:-:|:-:|
$1$|$\frac{x+x'}{2}=x_0$，$\frac{y+y'}{2}=y_0$|
$2$|$x'=x$，$\frac{y+y'}{2}=y_0$|
$3$|$\frac{x+x'}{2}=x_0$，$y'=y$|


WSM 每一步可以使用一个道具或一个魔法物品。请问至少需要多少步才能从坐标为 $(1,1)$ 的格子到达坐标为 $(a,b)$ 的格子？

## 说明/提示

### 【样例 $1$ 解释】
  
花费最小步数的路线为：

$\def\f#1{\xrightarrow{\bf 道具#1}} (1,1) \f{2} (2,1) \f{4} (2,2)$。


### 【数据范围】

**本题采用捆绑测试。**

请注意：任意一个格子内可能**同时存在**多个锁、钥匙、道具和魔法道具。

对于所有测试数据，保证：
* $1\le n,m\le400$，$1\le a\le n$，$1\le b\le m$。
* $1\le k \le 10^3$，$0\le t\le 3$，$1\le p\le 5\times 10^5$，$0\le q\le 3$。
* 对于所有的锁、钥匙、道具、魔法物品，均有 $1\le x\le n$，$1\le y\le m$。
* 对于所有的锁，均有 $1\le r\le 10^9$。
* 对于所有的钥匙，均有 $1\le r\le 10^9$。
* 对于所有的道具，均有 $id\in\{1,2,3,4\}$。
* 对于所有的魔法物品，均有 $id\in\{1,2,3\}$。

| 子任务编号 |$n,m\le$|$k\le$|$t\le$|$p\le$|$q\le$|分数|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$2$|$0$|$0$|$13$|$0$|$10$|
|$2$|$10$|^|^|$300$|$3$|$10$|
|$3$|^|$100$|$3$|^|^|$20$|
|$4$|$400$|$0$|$0$|$5\times10^5$|$0$|$10$|
|$5$|^|$3$|$3$|^|$3$|$25$|
|$6$|^|$10^3$|^|^|^|$25$|

## 样例 #1

### 输入

```
2 2 2 2
0 0 8 0
1 2 4
1 1 2
2 2 1
1 1 4
2 2 4
2 1 4
1 2 3
2 1 1```

### 输出

```
2```

# 题解

## 作者：WsW_ (赞：3)

### 前言
这是出题人题解。

---
### 思路
当没有魔法物品和钥匙时，只需要跑 bfs 最短路即可。  
当有魔法物品和钥匙时，魔法物品是否存在，某个密码的钥匙是否已获得，都可能影响之后的路径，所以要把这些信息记录下来。  
魔法物品和钥匙的数量很少，可以利用状态压缩的方法来记录这些信息。将某个魔法物品是否存在，分别定义为状态 $1$ 和 $0$；将某个密码的钥匙是否获得，分别定义为状态 $1$ 和 $0$。这样这些状态就成了一个 $01$ 串，若将这个 $01$ 串看作一个二进制数，那么这些状态就被压缩成了一个整数。  
如果把压缩出的状态看作层，那么本质上就是分层图最短路。由于每次操作花费均为 $1$，所以只需要使用 bfs 求解最短路。  

特别地，由于锁的编号数量很多，但有可能消失的锁的编号很少，我们需要对进行锁预处理，包括：
- 将不可能消失的锁所在格子标记为不可到达。
- 将可能消失的锁与其对应钥匙联系起来。

时间复杂度为 $O(k+t+p+q+nm2^{t+q})$。  

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef unsigned int ui;
int n,m,a,b;
int k,t,q,p;
struct node{
	int x,y,r;
};
vector<pii>edg[403][403];
int itto[5][2]={0,0,-1,0,1,0,0,-1,0,1};
vector<node>mag;
vector<node>lck;
vector<node>key;
vector<int> keyr;
int fans;
bool lcked[403][403];
vector<int>lckr[403][403];

int dis[403][403][67];
queue<node>que;

bool cmp(node X,node Y){
	return (X.x>Y.x)||(X.x==Y.x&&X.y>Y.y)||(X.x==Y.x&&X.y==Y.y&&X.r>Y.r);
}
bool check(int X,int Y){return X<1||X>n||Y<1||Y>m||lcked[X][Y];}
int get(int r){
	for(ui i=0;i<keyr.size();i++)if(r==keyr[i])return i;
	return -1;
}
void gto(int x,int y,int tox,int toy,int stt){
	if(check(tox,toy))return;
	int tost=stt;
	for(ui i=0;i<key.size();i++){
		if(key[i].x==tox&&key[i].y==toy)tost|=1<<key[i].r;//注意r可能相同，不能直接写i 
	}
	for(auto i:lckr[tox][toy]) if((tost&(1<<i))==0)return;
	for(ui i=0;i<mag.size();i++)
		if(mag[i].x==tox&&mag[i].y==toy)tost|=(1<<(i+3));
	if(dis[tox][toy][tost]<=dis[x][y][stt]+1)return;
	dis[tox][toy][tost]=dis[x][y][stt]+1;
	que.push({tox,toy,tost});
}
void bfs(){
	memset(dis,0x3f,sizeof(dis));
	dis[1][1][0]=0;
	que.push({1,1,0});
	while(!que.empty()){
		int x=que.front().x,y=que.front().y,stt=que.front().r;
		if(x==a&&y==b&&!fans){
			fans=dis[x][y][stt];
		}
		que.pop();
		for(auto to:edg[x][y])gto(x,y,to.first,to.second,stt);
		for(ui i=0;i<mag.size();i++){
			if(stt&(1<<(i+3)))continue;
			int tox=x,toy=y;
			if(mag[i].r==1||mag[i].r==2)toy=(mag[i].y<<1)-toy;
			if(mag[i].r==1||mag[i].r==3)tox=(mag[i].x<<1)-tox;
			gto(x,y,tox,toy,stt);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>a>>b;
	cin>>k>>t>>p>>q;
	for(int i=1;i<=k;i++){
		int x,y,r; cin>>x>>y>>r;
		lck.push_back({x,y,r});
	}
	for(int i=1;i<=t;i++){
		int x,y,r; cin>>x>>y>>r;
		key.push_back({x,y,r});
		keyr.push_back(r);
	}
	sort(keyr.begin(),keyr.end());
	keyr.erase(unique(keyr.begin(),keyr.end()),keyr.end());
	for(int i=0;i<t;i++)key[i].r=get(key[i].r);
	sort(lck.begin(),lck.end(),cmp);
	
	for(ui i=0;i<lck.size();i++){
		int f=get(lck[i].r);
		if(f==-1)lcked[lck[i].x][lck[i].y]=1;
		else lckr[lck[i].x][lck[i].y].push_back(f);
	}
	for(int i=1;i<=p;i++){
		int x,y,id; cin>>x>>y>>id;
		edg[x][y].push_back({x+itto[id][0],y+itto[id][1]});
	}
	for(int i=1;i<=q;i++){
		int x,y,id; cin>>x>>y>>id;
		mag.push_back({x,y,id});
	}
	bfs();
    if(fans)cout<<fans;
	else cout<<-1;
	return 0;
}
```

---

## 作者：tzhengqing (赞：2)

场上 2h 没切掉一个蓝，故写题解纪念。
### 题目大意
~~好长好长啊~~  
在 $n$ 行 $m$ 列的网格中游走，每个网格给出是否可以往**四联通**的某个方向走。  
有 $k$ 个有编号的锁，拿到对应编号的钥匙即可删除这个锁。如果没有拿到，则不能往这个格子上走。  
还有 $q$ 个魔法物品，随时可以使用，可以使自己的位置相对魔法物品的位置做轴对称变换。特别地，如果踩在某个魔法物品上，这个魔法物品会被删除。  
问从 $(1,1)$ 到达 $(a,b)$ 的最小步数。有可能存在无解，此时输出 $-1$。
### 解题思路
初看起来，本题比较复杂，而且直接搜索可能难以处理存在**钥匙和魔法物品**的情况。  
如果只记录 $dis_{i,j}$ 表示 $(1,1)$ 到 $(i,j)$ 的最小步数，可能在面前碰见了一个锁，需要回去找钥匙，但是在来时顺路拿到钥匙就会更优。也就是说，$dis_{i,j}$ 只能存下**局部最优**，可能不是全局最优。同理，如果你在来时破坏了一些魔法物品，也可能不是最优解。  
我们考虑化解这种情况。最暴力的方法是，直接把每个点的钥匙和魔法物品的不同情况的最短路分别存下来。具体地，我们设 $dis_{key,obj,i,j}$ 表示从 $(1,1)$ 到 $(i,j)$ 时钥匙获取情况为 $key$，魔法物品破坏情况为 $obj$ 的最短路。  
对于 $key$ 和 $obj$，看似不好存储，实则可以用状压解决。注意到 $t,q \le 3$，因此状压之后复杂度也可以接受。  
对于转移，由于边权全为 $1$，可以采用 BFS 实现。  
遍历所有状态，时空复杂度 $O(p+nm2^{t+q})$，可以通过。
#### 警示后人
由于本题细节极多，这一段用来介绍几个可能遇到的错误。  

- 同一个点可能会有重复的物品和锁，状压的时候要记得判断没有之后再加上去，否则就会进位，导致挂掉。
- 密码的编号 $r \le 10^9$，离散化之后再状压。考虑那些没有密码的锁，直接标记为不可达即可。
- 钥匙和魔法物品的处理方式不一样！！魔法物品的 $id$ 是用来存行动方式的，不是用来判断是第几个物品的。
### 代码实现
在 ``inf`` 个细节上挂分后，看看我们的 AC code！
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1000010299,M=8;//010299qwq
int n,m,a,b,k,t,p,q;
//输入
int dis[16][8][405][405],loc[405][405],key[405][405],a1[405][405],a2[405][405];
//dis 表示距离，loc 表示锁，key 表示钥匙，a1 表示普通物品，a2 表示魔法物品
int x2[3],y2[3],id2[3],dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
//x2,y2,id2 表示魔法物品的信息，dx 和 dy 表示编号为 i 的普通物品的位移情况
int xx[1005],yy[1005],idd[1005],idd2[3];
//离散化用的临时数组
map<int,int>mp;//懒人专属离散化工具
struct node{int ky,w2,x,y;};//扔进 queue 的结构体，ky 钥匙，w2 魔法物品，(x,y) 是坐标
void bfs(){
	for(int i=0;i<M*2;i++)for(int j=0;j<M;j++)for(int k=0;k<=n;k++)for(int l=0;l<=m;l++)
		dis[i][j][k][l]=inf;//初始化，有点丑陋
	dis[key[1][1]][a2[1][1]][1][1]=0;//似乎写成 dis[0][0][1][1] 不会挂，数据还得练
	queue<node>q1;q1.push((node){key[1][1],a2[1][1],1,1});
	while(!q1.empty()){
		node u=q1.front();q1.pop();
		for(int i=0;i<4;i++){
			if((a1[u.x][u.y]&(1<<i))==0)continue;//这个方向不合法就跳过
			int x=u.x+dx[i],y=u.y+dy[i],ky=u.ky|key[x][y],w2=u.w2|a2[x][y];//转移后的状态
			if(x<1||x>n||y<1||y>m)continue;//坐标是否合法
			int tag=0;
			for(int f=0;f<4;f++)
				if(((loc[x][y]&(1<<f))!=0)&&((ky&(1<<f))==0))tag=1;//是否还有锁没打开
			if(tag||dis[ky][w2][x][y]!=inf)continue;//处理过或者不合法则跳过
			dis[ky][w2][x][y]=dis[u.ky][u.w2][u.x][u.y]+1;//更新
			q1.push((node){ky,w2,x,y});//继续搜索
		}
		for(int i=0;i<q;i++){
			if(((1<<i)&u.w2)!=0)continue;//这个魔法物品被踩爆了就跳过
			//以下注释同上
			int x=(id2[i]==1?u.x:2*x2[i]-u.x),y=(id2[i]==2?u.y:2*y2[i]-u.y);
			int ky=u.ky|key[x][y],w2=u.w2|a2[x][y];
			if(x<1||x>n||y<1||y>m)continue;
			int tag=0;
			for(int f=0;f<4;f++)
				if(((loc[x][y]&(1<<f))!=0)&&((ky&(1<<f))==0))tag=1;
			if(tag||dis[ky][w2][x][y]!=inf)continue;
			dis[ky][w2][x][y]=dis[u.ky][u.w2][u.x][u.y]+1;
			q1.push((node){ky,w2,x,y});
		}
	}
}
int main(){
	cin>>n>>m>>a>>b>>k>>t>>p>>q;
	for(int i=0;i<k;i++){
		cin>>xx[i]>>yy[i]>>idd[i];
	}
	for(int i=0;i<t;i++){
		cin>>xx[i+k]>>yy[i+k]>>idd[i+k];
		idd2[i]=idd[i+k];
	}
	for(int i=0;i<t;i++)mp[idd2[i]]=i+1;
	for(int i=0;i<k;i++){
		int x=xx[i],y=yy[i],id=mp[idd[i]];
		if(id==0)id=4;//没有钥匙则标记不可行
		if((loc[x][y]&(1<<(id-1)))==0)
			loc[x][y]+=1<<(id-1);
	}
	for(int i=0;i<t;i++){
		int x=xx[i+k],y=yy[i+k],id=mp[idd[i+k]];
		if((key[x][y]&(1<<(id-1)))==0)
			key[x][y]+=1<<(id-1);
	}
	for(int i=0;i<p;i++){
		int x,y,id;cin>>x>>y>>id;
		if((a1[x][y]&(1<<(id-1)))==0)
			a1[x][y]+=1<<(id-1);
	}
	for(int i=0;i<q;i++){
		int x,y,id;cin>>x>>y>>id;
		x2[i]=x;y2[i]=y;id2[i]=id-1;
		if((a2[x][y]&(1<<i))==0)
			a2[x][y]+=1<<i;
	}
	bfs();int ans=inf;
	for(int i=0;i<M*2;i++)for(int j=0;j<M;j++)
		ans=min(ans,dis[i][j][a][b]);//遍历所有可能情况
	cout<<(ans==inf?-1:ans);//无解输出 -1
	return 0;
}
```

---

