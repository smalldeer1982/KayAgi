# Knightmare (hard)

## 题目描述

这是一个交互题。

Alice 和 Bob 在一个 $n \times m$ 的国际象棋棋盘上玩游戏，其中 $n$ 和 $m$ 都是偶数。棋盘的行编号为 $1$ 到 $n$，列编号为 $1$ 到 $m$。棋盘上有两个马，一个白马最初在位置 $(x_1, y_1)$，一个黑马最初在位置 $(x_2, y_2)$。Alice 将选择其中一个马来操作，Bob 则操作另一个马。

Alice 和 Bob 轮流行动，控制白马的玩家先手。在每一回合，玩家必须按照国际象棋规则移动自己的马。也就是说，如果马当前在 $(x, y)$，它可以移动到以下任意位置（前提是仍在棋盘内）：

$$(x+1, y+2),\ (x+1, y-2),\ (x-1, y+2),\ (x-1, y-2),\ (x+2, y+1),\ (x+2, y-1),\ (x-2, y+1),\ (x-2, y-1)$$

众所周知，马在棋盘中央最强。每个马都有一个唯一想要到达的位置：

- 白马的拥有者获胜的条件是：吃掉黑马，或者白马到达 $(n/2, m/2)$，且此时该位置没有被黑马攻击；
- 黑马的拥有者获胜的条件是：吃掉白马，或者黑马到达 $(n/2+1, m/2)$，且此时该位置没有被白马攻击。

形式化地说，吃掉对方的马即获胜。若某一方的马到达自己的目标格子（白马为 $(n/2, m/2)$，黑马为 $(n/2+1, m/2)$），且该位置没有被对方马攻击，也算获胜。

如果一个马可以一步走到某个位置，则称该位置被该马攻击。吃掉对方马指的是将自己的马移动到对方马所在的格子。

如果 Alice 已经走了 $350$ 步，仍无人获胜，则判为平局。

Alice 对自己的棋艺没有信心，于是请求你帮她选择一个马，并为她赢下比赛。可以证明，Alice 总有必胜策略。

## 说明/提示

在第一个样例中，白马可以一步到达自己的目标格子。

在第二个样例中，无论白马如何移动，黑马都能获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8 8
2 3 1 8
```

### 输出

```
WHITE
4 4
```

## 样例 #2

### 输入

```
6 6
4 4 2 2
6 3```

### 输出

```
BLACK
4 3
```

# 题解

## 作者：EuphoricStar (赞：1)

orz Charlie/bx.

考虑对棋盘染色，那么马移动到的格子和原来的格子异色。

进而发现若两个马初始异色，那么只有白马可以吃黑马，否则只有黑马可以吃白马。

下面只讨论初始异色的情况，同色是对称的。下文令 $W, B, T_W, T_B$ 分别为白马起点，黑马起点，白马终点，黑马终点。

考虑若白马能比黑马早到终点，即 $\text{dis}(W, T_W) \le \text{dis}(B, T_B)$，那么白马直接不管黑马冲到终点就行了，反正黑马也吃不掉它。

否则白马比速度肯定比不过了，就要想办法吃掉黑马。发现如果白马能比黑马早到 $T_B$ 白马才有可能吃掉黑马。因为题目说另一只马到了终点再吃也算吃掉，所以这里的早到定义为 $\text{dis}(W, T_B) \le \text{dis}(B, T_B) + 1$。

那么白马到了 $T_B$ 后如果还没吃掉黑马，那么此时白马和黑马的距离一定至少为 $2$（因为两只马此时位置同色）。黑马肯定不能移动使得它与白马的距离为 $1$，否则白马就吃掉它了。所以黑马只能移动使得它与白马的距离为 $3$。又因为 $\text{dis}(T_W, T_B) = 3$，所以白马直接冲到终点就结束了。

如果不满足 $\text{dis}(W, T_B) \le \text{dis}(B, T_B) + 1$ 那么白马无法吃掉黑马。这种情况黑马直接冲到终点就能赢，不用管白马。

直接模拟上面的分析过程即可。实现时需要以 $W, B$ 为起点跑最短路并且记录一下前驱。

[code](https://codeforces.com/problemset/submission/1201/242873689)

---

## 作者：Milmon (赞：0)

对格子进行二间隔染色。

首先观察吃子这一操作，有如下发现：

- 当双方初始位置同色时，每次轮到白方走时双方位置都同色，所以只有黑方可以吃白方；
- 当双方初始位置异色时，每次轮到黑方走时双方位置都同色，所以只有白方可以吃黑方。

两种情况相似，所以下面只介绍第一种情况的做法，第二种情况同理。

同时我们需要发现一个重要性质：**双方的目标格之间的距离（指的是走马步的最少步数，下同）为 $3$。**

下面进行分析。当只有黑方能吃白方时，白方必胜的充要条件就是直接走向终点且能保证不被吃掉。容易发现白方能被黑方吃掉的充要条件是黑方能领先白方到达白方的目标格子。黑方到达白方目标格子时，双方位置同色，所以距离至少为 $2$，下一步白方走，距离只能变成 $1$ 或 $3$，若变成 $1$ 则黑方可以直接吃掉白方，否则，黑方只需要在 $3$ 步之内直接走向自己的目标格即可。

根据上述分析，下面对第一种情况的分类进行总结：

- 若黑方能比白方更快到达自己的目标，就直接走向目标，由于白方不能吃黑方，所以黑方必胜；
- 若黑方能比白方更快到达白方的目标，就走向白方的目标，然后根据白方反应做出吃掉白方或者用 $3$ 步走到自己目标的决定，黑方必胜；
- 否则，白方直接走向自己的目标，黑方能胜的情况已被前两种情况排除，所以白方必胜。

第二种情况同理。实现细节上：

- 用 `bfs` 求出黑白初始位置到黑白目标位置两两之间的距离和路径；
- 注意交互细节，例如若选择黑方先手要先读入一次白方的坐标，若能吃掉对方就直接吃掉并结束程序；
- 注意每一处步数的比较是否取等都需要仔细思考。

时间复杂度 $O(nm)$。

```cpp
/**
 * @date: 2024.01.23
 * @problem: CF1202E2
 * @tags: 博弈论
 */

#include<bits/stdc++.h>
using namespace std;
const int dx[8]={-2,-2,-1,-1,1,1,2,2};
const int dy[8]={-1,1,-2,2,-2,2,-1,1};

int n,m;

struct Point{
    int x,y;
    inline void read(){
        cin>>x>>y;
    }
    inline void print(){
        cout<<x<<' '<<y<<endl;
    }
    inline int type(){
        return (x+y)&1;
    }
    inline bool operator==(Point t)const{
        return x==t.x&&y==t.y;
    }
    inline Point to(int method){
        return{x+dx[method],y+dy[method]};
    }
    inline bool isOnlyOneStepTo(Point other){
        if(abs(x-other.x)+abs(y-other.y)!=3)return false;
        return x!=other.x&&y!=other.y;
    }
}W,B,tarW,tarB,other,myTar;

void chooseWhite(){
    cout<<"WHITE"<<endl;
    myTar=tarW;
}
void chooseBlack(){
    cout<<"BLACK"<<endl;
    myTar=tarB;
}

struct Queue{
    bool vis[1001][1001];
    Point v[1000001];
    int pre[1000001];
    int step[1000001];
    int head,tail;

    inline void clear(){
        memset(vis,0,sizeof vis);
        head=1,tail=0;
    }
    inline void push(Point x,int prev,int s){
        vis[x.x][x.y]=true;
        v[++tail]=x,step[tail]=s,pre[tail]=prev;
    }
    inline Point pop(){
        return v[head++];
    }

    void print(int id){
        if(pre[id])print(pre[id]);
        else return;
        v[id].print();
        if(other==v[id])exit(0);
        if(v[id]==myTar)exit(0);
        other.read();
    }
    inline void print(){
        print(this->head);
    }

    inline int bfs(Point S,Point T){
        this->clear();
        this->push(S,0,0);
        while(head<=tail){
            Point x=v[head];
            int s=step[head];
            if(x==T)return s;
            for(int i=0;i<8;i++){
                Point nxt=x.to(i);
                if(nxt.x<1||nxt.x>n||nxt.y<1||nxt.y>m)continue;
                if(vis[nxt.x][nxt.y])continue;
                this->push(nxt,head,s+1);
            }
            this->pop();
        }
        assert(false);
    }
}QW,QB,QWB,QBW,Qtar;

int main(){
    cin>>n>>m;
    tarW={n/2,m/2},tarB={n/2+1,m/2};
    W.read(),B.read();
    int wdis=QW.bfs(W,tarW);
    int bdis=QB.bfs(B,tarB);
    int wbdis=QWB.bfs(W,tarB);
    int bwdis=QBW.bfs(B,tarW);
    if(W.type()!=B.type()){
        // It means that only white can eat black
        if(wdis<=bdis){
            chooseWhite();
            QW.print();
            return 0;
        }
        if(wbdis<=bdis+1){
            chooseWhite();
            QWB.print();
            if(other.isOnlyOneStepTo(tarB))other.print();
            else{
                Qtar.bfs(tarB,tarW);
                Qtar.print();
            }
            return 0;
        }
        chooseBlack();
        other.read();
        QB.print();
    }
    else{
        // It means that only black can eat white
        if(bdis<wdis){
            chooseBlack();
            other.read();
            QB.print();
            return 0;
        }
        if(bwdis<=wdis){
            chooseBlack();
            other.read();
            QBW.print();
            if(other.isOnlyOneStepTo(tarW))other.print();
            else{
                Qtar.bfs(tarW,tarB);
                Qtar.print();
            }
            return 0;
        }
        chooseWhite();
        QW.print();
    }
    return 0;
}
```

---

## 作者：hz2016 (赞：0)

则虽然是CF Div.2的最后一道题，看上去很难，但是其实并不难。

~~(其实一开始就没想要开这一题的，一不小心提交了个错误的代码，看不惯红色错误标签，所以就硬着头皮做了)~~
这题我们可以知道就是两个骑士在棋盘上走，你选择其中一个，你要获得胜利。

胜利我们指：

	1. 一个棋子到达了它的目标点，另一个棋子不能攻击到其目标点

	2. 一个棋子可以一步走到另外一个棋子所在的位置（就是吃掉别人啦）
那么，我们可以有如下方案。

方案一：

当一个棋子可以走到目标点且另一个棋子无法在两步之内到达其目标点（就是无法在目标点或者必经之路设防）我们选择该棋子，并且移动直接走向目标点
方案二：

我们可以把棋盘化成黑白相间的格子，如果两个棋子在同一个颜色的格子上那么只有后手可以吃先手，不同颜色则之后后手可以吃先手，那么我们可以选择可以吃别人的那个棋子，先走到对方的目标点，因为对方不能靠近你，所以对方会向外跳一步，所以到目标点需要三步远。而你仅需三步，就可以从别人的目标点跳跃到自己的目标点，刚好获得胜利。

步数总计不超过339步，符合题目要求。

那我们可以做四次bfs来求出起始点到目标点的距离，利用类链表记录路径，时间复杂度为$O\left(k\ast n^2\right)$

但是还有个很滞涨的问题，就是电脑会把棋子下到你可以吃的地方，你一定要吃了它，不然会Wa掉，所以每次输出都要判断一下，如果可以吃就吃（反正吃掉也是赢了嘛

```cpp
#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define qread(x) x=read()
#define Maxn 1000
#define mes(x,y) memset(x,y,sizeof(x))
#define INF 2147483647
inline int read(){
	int f=1,x=0;char ch=getchar();
	while(!(ch>='0'&&ch<='9')){if(ch=='-')f*=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return f*x;
}
int dx[8]={1,1,-1,-1,2,2,-2,-2};
int dy[8]={2,-2,2,-2,1,-1,1,-1}; 
struct Point{
	int x,y,c,fa;
	friend bool operator ==(Point a,Point b){
		return (a.x==b.x&&a.y==b.y);
	}
}w[2],b[2],other,list[4][Maxn*Maxn+1];
void readother(){
	std::cin>>other.x>>other.y; 
}
bool check(Point a,Point b){
	int x=abs(a.x-b.x),y=abs(a.y-b.y);
	if(x<=2&&y<=2&&x+y==3){
		printf("%d %d\n",b.x,b.y);
		return true;
	}
	return false;
}
int otherx,othery;bool bk=false;
void printlist(int k,Point a){
	if(a.fa==-1||bk==true)return;
	if(a.fa!=1)printlist(k,list[k][a.fa]);
	if(check(a,other)==true)bk=true;
	if(bk==true)return;
	printf("%d %d\n",a.x,a.y);
	readother();
}
int n,m,head,tail,v[4][Maxn+1][Maxn+1];
void closer(int k,Point st,Point ed){
	Point a,b;
	head=tail=1;
	mes(v[k],0);v[k][st.x][st.y]=head;
	list[k][head]=st,list[k][head].c=0,list[k][head].fa=-1;
	if(st==ed)return;
	while(head<=tail){
		a=list[k][head];
		for(int i=0;i<8;i++){ 
			b=a,b.x+=dx[i],b.y+=dy[i],b.c++;
			if(b.x<1||b.y<1||b.x>n||b.y>m||v[k][b.x][b.y]!=0)continue;
			tail++; 
			v[k][b.x][b.y]=tail;
			b.fa=head;
			list[k][tail]=b;
			if(b==ed)return;
		}
		head++;
	}
}
void printlast(int k){
	Point a;
	if(k==0){
		a=b[0];
		if(check(a,other)==false){
			a=b[0],a.x-=1,a.y+=2;
			printf("%d %d\n",a.x,a.y),readother();
		}
		else return;
		if(check(a,other)==false){
			a=b[0],a.x-=3,a.y+=1;
			printf("%d %d\n",a.x,a.y),readother();
		}
		else return;
		if(check(a,other)==false){
			a=b[0],a.x-=1;
			printf("%d %d\n",a.x,a.y),readother();
		}
		else return;
	}
	else{
		a=w[0];
		if(check(a,other)==false){
			a=w[0],a.x+=1,a.y+=2;
			printf("%d %d\n",a.x,a.y),readother();
		}
		else return;
		if(check(a,other)==false){
			a=w[0],a.x+=3,a.y+=1;
			printf("%d %d\n",a.x,a.y),readother();
		}
		else return;
		if(check(a,other)==false){
			a=w[0],a.x+=1;
			printf("%d %d\n",a.x,a.y),readother();
		}
		else return;
    }
}
bool choose;
int main(){
	qread(n),qread(m),
	qread(w[1].x),qread(w[1].y),qread(b[1].x),qread(b[1].y);
	w[0].x=n/2,w[0].y=m/2,b[0].x=n/2+1,b[0].y=m/2;
	closer(0,w[1],w[0]),closer(1,b[1],b[0]);
	closer(2,w[1],b[0]);
	closer(3,b[1],w[0]);
	if((w[1].x+w[1].y)%2!=(b[1].x+b[1].y)%2){
        if(list[0][v[0][w[0].x][w[0].y]].c<=list[1][v[1][b[0].x][b[0].y]].c)
			printf("WHITE\n"),other=b[1],printlist(0,list[0][v[0][w[0].x][w[0].y]]);
        else if(list[2][v[2][b[0].x][b[0].y]].c>=list[1][v[1][b[0].x][b[0].y]].c+2)
			printf("BLACK\n"),readother(),printlist(1,list[1][v[1][b[0].x][b[0].y]]);
        else printf("WHITE\n"),other=b[1],printlist(2,list[2][v[2][b[0].x][b[0].y]]),printlast(0);
    }
	else{
        if(list[1][v[1][b[0].x][b[0].y]].c<list[0][v[0][w[0].x][w[0].y]].c)
			printf("BLACK\n"),readother(),printlist(1,list[1][v[1][b[0].x][b[0].y]]);
        else if(list[3][v[3][w[0].x][w[0].y]].c>list[0][v[0][w[0].x][w[0].y]].c)
			printf("WHITE\n"),other=b[1],printlist(0,list[0][v[0][w[0].x][w[0].y]]);
        else printf("BLACK\n"),readother(),printlist(3,list[3][v[3][w[0].x][w[0].y]]),printlast(1);
    }
}
```


---

