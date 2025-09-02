# Knightmare (easy)

## 题目描述

本题与下一题仅在数据范围上有所不同。

这是一个交互题。

Alice 和 Bob 在一个 $n \times m$ 的棋盘上玩游戏，其中 $n$ 和 $m$ 都是偶数。棋盘的行编号为 $1$ 到 $n$，列编号为 $1$ 到 $m$。棋盘上有两个骑士，一个白骑士初始位于 $(x_1, y_1)$，一个黑骑士初始位于 $(x_2, y_2)$。Alice 将选择一个骑士进行游戏，Bob 使用另一个骑士。

Alice 和 Bob 轮流行动，控制白骑士的一方先手。在每一回合，玩家必须按照国际象棋的规则移动自己的骑士。即，如果骑士当前在 $(x, y)$，则可以移动到以下任意位置（前提是仍在棋盘内）：

$(x+1, y+2)$，$(x+1, y-2)$，$(x-1, y+2)$，$(x-1, y-2)$，$(x+2, y+1)$，$(x+2, y-1)$，$(x-2, y+1)$，$(x-2, y-1)$。

众所周知，骑士在棋盘中央最强大。两个骑士各自有一个目标位置：

- 白骑士的拥有者获胜的条件是：吃掉黑骑士，或者白骑士到达 $(n/2, m/2)$，且此时该位置不在黑骑士的攻击范围内；
- 黑骑士的拥有者获胜的条件是：吃掉白骑士，或者黑骑士到达 $(n/2+1, m/2)$，且此时该位置不在白骑士的攻击范围内。

形式化地说，吃掉对方骑士的一方获胜。到达自己的目标格子且该位置不在对方骑士攻击范围内的一方也获胜。

如果某个位置可以被骑士一步到达，则称该位置处于该骑士的攻击范围内。吃掉对方骑士指的是将自己的骑士移动到对方骑士所在的格子。

如果 Alice 已经走了 $350$ 步且无人获胜，则判为平局。

Alice 对自己的棋艺没有信心，于是请求你帮她选择一个骑士并帮助她获胜。你需要选择一个骑士并为她赢得比赛。可以证明，Alice 总有必胜策略。

## 说明/提示

在第一个样例中，白骑士可以一步到达目标格子。

在第二个样例中，无论白骑士如何移动，黑骑士都能获胜。

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

下面只讨论 E2 的做法。

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

## 作者：hz2016 (赞：1)

~~(虽然这是道Easy版，但是我还是wa了两次，原因就是因为我不想吃对面棋子但是一定要吃)~~

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

