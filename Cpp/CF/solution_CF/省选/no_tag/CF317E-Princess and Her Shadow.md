# Princess and Her Shadow

## 题目描述

Princess Vlada enjoys springing in the meadows and walking in the forest. One day — wonderful, sunny day — during her walk Princess found out with astonishment that her shadow was missing! "Blimey!", — she thought and started her search of the shadow in the forest.

Normally the Shadow is too lazy and simply sleeps under the Princess. But at this terrifically hot summer day she got bored of such a dull life, so she decided to play with Vlada.

The forest, where our characters entertain themselves, may be represented as a set of integer cells in the plane, where the Shadow and the Princess can move only up, down, left and right by $ 1 $ . Some cells (as it happens in decent forests) are occupied by trees. The Shadow and the Princess are not allowed to enter a cell occupied by a tree. Unfortunately, these are the hard times for the forest, so there are very few trees growing here...

At first the Princess was walking within the cell ( $ v_{x} $ , $ v_{y} $ ), while the Shadow hid from the Princess in the cell ( $ s_{x} $ , $ s_{y} $ ). The Princess, The Shadow and the trees are located in the different cells.

The Shadow is playing with the Princess. As soon as the Princess moves by $ 1 $ in some direction, the Shadow simultaneously flies by $ 1 $ in the same direction, if it is possible (if the cell to fly to is not occupied by some tree); otherwise, the Shadow doesn't move. The Shadow is very shadowy, so our characters do not interfere with each other.

We say that the Shadow is caught by the Princess if after some move both of them are located in the same cell. Vlada managed to catch her Shadow! Can you?

## 说明/提示

Below the pictures for the samples are given (Princess, Shadow and the trees are colored in pink, gray and black correspondingly; the blue dot marks the lattice center).

In the first case the Princess may make two left steps, one step upwards and one right step: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317E/c17fd073689157dd9f4b4dfb341b1aefa7c3e39b.png)

In the following case the Princess cannot catch the Shadow: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317E/9d4b83f9e647e92f9c9ee925fd23e5ddb98b9e72.png)

In the last sample the Princess may make two left steps and one down step (in any order): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF317E/3dacea5b4da1bcdd6fc8142ab9fe5922397b3596.png)

## 样例 #1

### 输入

```
0 0 1 0 1
0 1
```

### 输出

```
LLUR
```

## 样例 #2

### 输入

```
5 0 3 0 8
2 -1
2 0
2 1
3 -1
4 1
4 0
3 1
4 -1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 2 1 1 3
0 1
1 0
0 0
```

### 输出

```
DLL```

# 题解

## 作者：jun头吉吉 (赞：6)

## 题意
**平面直角坐标系**上，有一个公主和她的影子，还有 $m$ 棵树，公主在 $(v_x,v_y)$,影子在 $(s_x,s_y)$ 。
公主要去追影子。
公主向右走，影子就会向右走；公主向左走，影子就会向左走；公主向上走，影子就会向上走；公主向下走，影子就会向下走。
如果影子前进的方向是一棵树，影子就不会动。公主不能撞树。
求一组公主的行动方案，让公主抓到影子，要求方案长度不能超过 $10^6$。若无解，输出 $-1$

$0\le m\le 400,-200\le\text{坐标}\le200$
## 题解

退役后一血，在$\rm\color{black}W\color{red}YH$ 的帮助下想出了 $3100$（恶评题）。

非常 【】，直接猜结论即可。

给个比较菜的方法。

考虑 $400$ 棵树能否把公主和影子围起来。

如果两者皆不封闭，那么一定可以把两者都移到外面，都移到外面之后就一定有解，这部分可以手玩一下。由于比较菜，代码里直接分类讨论了。

如果一个封闭一个不封闭，显然无解。

如果两个都封闭，那么联通就必定有解。我们数学课刚刚讲过芝诺追乌龟，借鉴追乌龟的方法把公主移到影子在的地方，然后继续搜索。应该可以证明不会更劣，由于是 $\rm OI$ 就不证明了。

可能有更高妙的做法但不太会。

加粗**平面直角坐标系**是因为一开始看反了。

## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pii pair<int,int>
#define ppp pair<pii,pii>
#define L 0
#define R 1
#define D 2
#define U 3
#define vvx now.first.first
#define vvy now.first.second
#define ssx now.second.first
#define ssy now.second.second
#define mnx min(vvx,ssx)
#define mxx max(vvx,ssx)
#define mny min(vvy,ssy)
#define mxy max(vvy,ssy)
using namespace std;
int vx,vy,sx,sy,m;
int vis[450][450];
int flag[450][450];
int x[450],y[450];
const int dx[4]={0,0,-1,1};
const int dy[4]={-1,1,0,0};
const char ch[4]={'L','R','D','U'};
bool In(int x,int y){return x>=5&&x<=440&&y>=5&&y<=440;}
bool Not(int x,int y){
	if(!In(x,y))return false;
	return vis[x][y];
}
bool fb(int x,int y){
	memset(flag,0,sizeof flag);
	queue<pii>q;q.push(mp(x,y));flag[x][y]=1;
	while(q.size()){
		auto [x,y]=q.front();q.pop();
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(!In(xx,yy))return false;
			if(vis[xx][yy])continue;
			if(flag[xx][yy])continue;
			flag[xx][yy]=1;
			q.push(mp(xx,yy));
		}
	}return true;
}
ppp work(ppp A,int dir){
	auto [x,y]=A.first;auto [xx,yy]=A.second;
	if(Not(x+dx[dir],y+dy[dir]))exit(-1);
	x+=dx[dir],y+=dy[dir];
	if(!Not(xx+dx[dir],yy+dy[dir]))xx+=dx[dir],yy+=dy[dir];
	putchar(ch[dir]);
	if(x==xx&&y==yy)exit(0);
	return mp(mp(x,y),mp(xx,yy));
} 
ppp work(ppp A,int dir,int times){
	while(times--)
		A=work(A,dir);
	return A;
}
ppp now;
void dfs(int x,int y){
	//printf("%d %d\n",x-210,y-210);
	if(flag[x][y]!=-10){
		int dir=flag[x][y]^1;
		dfs(x+dx[dir],y+dy[dir]);
	}else return;
	now=work(now,flag[x][y]);
}
signed main(){
	//freopen("1.out","w",stdout);
	scanf("%d%d%d%d%d",&vx,&vy,&sx,&sy,&m);
	if(!m){
		if(vx==sx&&vy==sy)return 0;
		return puts("-1"),0;
	}
	vx+=210,vy+=210,sx+=210,sy+=210;
	swap(vx,vy);swap(sx,sy);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&y[i],&x[i]);
		x[i]+=210;y[i]+=210;
		vis[x[i]][y[i]]=1;
	}
	bool V=fb(vx,vy);
	bool S=fb(sx,sy);
	if(V^S)
		return puts("-1"),0;
	if(V&&S){
		{
			memset(flag,0,sizeof flag);
			queue<pii>q;q.push(mp(vx,vy));flag[vx][vy]=0;
			while(q.size()){
				auto [x,y]=q.front();q.pop();
				for(int i=0;i<4;i++){
					int xx=x+dx[i],yy=y+dy[i];
					if(vis[xx][yy])continue;
					if(flag[xx][yy])continue;
					if(xx==sx&&yy==sy)
						goto loop;
					flag[xx][yy]=1;
					q.push(mp(xx,yy));
				}
			}
		}
		return puts("-1"),0;
		loop:;
		for(;;){
			memset(flag,0xff,sizeof flag);
			//flag记录dir 
			flag[vx][vy]=-10;
			queue<pii>q;q.push(mp(vx,vy));
			while(q.size()){
				auto [x,y]=q.front();q.pop();
				for(int i=0;i<4;i++){
					int xx=x+dx[i],yy=y+dy[i];
					if(vis[xx][yy])continue;
					if(flag[xx][yy]!=-1)continue;
					flag[xx][yy]=i;
					if(xx==sx&&yy==sy)
						goto out;
					q.push(mp(xx,yy));
				}
			}
			out:;
			now=mp(mp(vx,vy),mp(sx,sy));
			
			dfs(sx,sy);
			//putchar('\n');
			vx=now.first.first;
			vy=now.first.second;
			
			sx=now.second.first;
			sy=now.second.second;
			if(vx==sx&&vy==sy)
				return 0;
		}
	}
	memset(flag,0xff,sizeof flag);
	//flag记录dir 
	int ex,ey;
	flag[vx][vy]=-10;
	queue<pii>q;q.push(mp(vx,vy));
	while(q.size()){
		auto [x,y]=q.front();q.pop();
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(vis[xx][yy])continue;
			if(flag[xx][yy]!=-1)continue;
			flag[xx][yy]=i;
			if(!In(xx,yy)){
				ex=xx,ey=yy;
				goto out2;
			}
			q.push(mp(xx,yy));
		}
	}
	out2:;
	now=mp(mp(vx,vy),mp(sx,sy));
	dfs(ex,ey);
	
	if(ex==441)now=work(now,L,500),now=work(now,D,500);
	else now=work(now,D,500),now=work(now,L,500);
	now=work(now,D,500),now=work(now,L,500);
	
	sx=now.second.first;
	sy=now.second.second;
	if(In(sx,sy)){
		int ex,ey;
		memset(flag,0xff,sizeof flag);
		flag[sx][sy]=-10;
		while(q.size())q.pop();
		q.push(mp(sx,sy));
		while(q.size()){
			auto [x,y]=q.front();q.pop();
			for(int i=0;i<4;i++){
				int xx=x+dx[i],yy=y+dy[i];
				if(vis[xx][yy])continue;
				if(flag[xx][yy]!=-1)continue;
				flag[xx][yy]=i;
				if(!In(xx,yy)){
					ex=xx,ey=yy;
					goto out3;
				}
				q.push(mp(xx,yy));
			}
		}
		out3:;
		dfs(ex,ey);
		
		if(ex==441)now=work(now,L,500),now=work(now,D,500);
		else now=work(now,D,500),now=work(now,L,500);
	}
	if(ssx>=vvx&&ssy>=vvy){
		int mn=0x3f3f3f3f;
		for(int i=1;i<=m;i++)mn=min(mn,x[i]);
		while(ssx!=mn)
			now=work(now,U);
		while(!Not(ssx+dx[R],ssy+dy[R]))
			now=work(now,R);
		while(vvy!=ssy)
			now=work(now,R);
		now=work(now,D);
		now=work(now,R);
		while(1)now=work(now,U);
	}
	if(ssx>=vvx&&ssy<=vvy){
		while(ssy<=440)now=work(now,R);
		int mn=0x3f3f3f3f;
		for(int i=1;i<=m;i++)mn=min(mn,x[i]);
		while(ssx!=mn)
			now=work(now,U);
		while(!Not(ssx+dx[L],ssy+dy[L]))
			now=work(now,L);
		while(vvy!=ssy)
			now=work(now,L);
		now=work(now,D);
		now=work(now,L);
		while(1)now=work(now,U);
	}
	if(ssx<=vvx&&ssy<=vvy){
		while(ssy<=440)now=work(now,R);
		int mx=-0x3f3f3f3f;
		for(int i=1;i<=m;i++)mx=max(mx,x[i]);
		while(ssx!=mx)
			now=work(now,U);
		while(!Not(ssx+dx[L],ssy+dy[L]))
			now=work(now,L);
		while(vvy!=ssy)
			now=work(now,L);
		now=work(now,U);
		now=work(now,L);
		while(1)now=work(now,D);
	}
	if(ssx<=vvx&&ssy>=vvy){
		int mx=-0x3f3f3f3f;
		for(int i=1;i<=m;i++)mx=max(mx,x[i]);
		while(ssx!=mx)
			now=work(now,U);
		while(!Not(ssx+dx[R],ssy+dy[R]))
			now=work(now,R);
		while(vvy!=ssy)
			now=work(now,R);
		now=work(now,U);
		now=work(now,R);
		while(1)now=work(now,D);
	}
}
```

---

