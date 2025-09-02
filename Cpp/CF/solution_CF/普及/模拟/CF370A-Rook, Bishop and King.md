# Rook, Bishop and King

## 题目描述

佩蒂亚正在学习国际象棋。他已经学会如何移动王、车和象。让我们提示你如何移动国象棋子。棋盘有$64$个棋格，呈$8\times8$正方形。一个格子可以用$(r,c)$来表示——$r$指行，$c$指列（虽然在经典棋局中用字母和数字一起表示）。每一个棋子占用一个棋格。一次合法的棋步就是执行如下之一：

- 车可以横向或纵向移动任意格。
- 象可以斜着移动任意格。
- 王可以任意方向移动一格——横着或者斜着。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF370A/56990885d6c1103e4bcb4658b8f866fa3cac82a1.png)

佩蒂亚在想，从$(r_1,c_1)$移动到$(r_2,c_2)$所需的最少步数是多少？我们假设在棋盘上只有一枚棋子。帮他解决问题。

## 样例 #1

### 输入

```
4 3 1 6
```

### 输出

```
2 1 3
```

## 样例 #2

### 输入

```
5 5 5 6
```

### 输出

```
1 0 1
```

# 题解

## 作者：sxtm12138 (赞：3)

本题是一道模拟题，下过国际象棋的人都知道，没有阻拦时，车可以在2步之内到达任意点，只要确定目标点和出发点是否在同行或同列，就知道了车所需的步数，所以我就只讲象和王的判定。

象：象可以一步到达所处格子对角线上的任意点，或两步到达所有一步可达点的对角线上的任意点。我们可以发现，当象移动直线斜率为1时，设y=x+k，则同一直线上y-x为定值；当斜率为-1时，设y=k-x，则同一直线上x+y为定值，故只要判断两点y-x和x+y是否相同，就能确定是否一步可达。我们还能发现，白格象只能移动到白格，而黑白格是相邻的，不妨大胆猜测：象能到达的点与横纵坐标的奇偶性有关。

证明：由于象可两步到达所有一步可达点的对角线上的任意点，故该点的y-x或x+y与象所在对角线上的一个点相同，且该点y+x或x-y与象相同。又因为y-x与y+x的奇偶性必然相同，故象只能到达横纵坐标之和的奇偶性与其所在格相同的格子。

王：王可到达周围八格中的任意一格，但1次最多只能移动1行或1列，故王至少要走的步数为目标点与出发点横纵坐标之差中较大的一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x,y;//定义目标点与出发点的横纵坐标
int main()
{cin>>a>>b>>x>>y;//读入
 if(a==x||b==y) cout<<"1 ";//判断是否同行或同列
 else cout<<"2 ";//计算车的步数
 if(x+y==a+b||x-y==a-b) cout<<"1 ";//判断是否在同条对角线上
 else if((x+y)%2!=(a+b)%2) cout<<"0 ";//奇偶性不同则不可达 
      else cout<<"2 ";//否则两步可达
 cout<<max(abs(x-a),abs(y-b));//王至少要走的步数
 return 0;
}
```

---

## 作者：晨曦墨凝 (赞：2)

[题目传送门 $Luogu$](https://www.luogu.com.cn/problem/CF370A)

[题目传送门 $Codeforces$](https://codeforces.com/problemset/problem/370/A)

本题是一道思维题

------------
### 车：
很简单，最多两步。若不同行，那就走一步到达同一行，若不同列，那就走一步到达同一列。

------------

### 象：
有点难度，先粘出来张棋盘，再接着讲
![如果你看到这行字说明我粘出来的棋盘图挂了，自己搜一张国际棋盘图吧](https://cdn.luogu.com.cn/upload/image_hosting/nblhofdc.png)
请各位随便用鼠标在上面模拟象棋走一走，注意观察颜色，发现什么了吗？

没错，象棋所到达的终点格子的颜色和起点格子的颜色一样！如果是黑色格子，则其横纵坐标奇偶性相同；如果是白色格子，则其横纵坐标奇偶性不同。

需要注意的是，象也可以转弯（细品）。

易得，象若能到达终点，则最多需要两步。

------------

### 王：
很简单，按照贪心的思想，能斜着走就斜着走，然后再直着走。

然后再简单地把公式解出来并化简一下即可（具体公式看代码）

------------

$Code$
```
void solve_car()
{
	int ans;
	if (x_1 != x_2) ++ans;
	if (y_1 != y_2) ++ans;
	printf("%d ", ans);
}

void solve_elp()
{
	if (abs(x_1 - x_2) == abs(y_1 - y_2)) 	//在同一斜行 
		printf("1 ");
	else if ((x_1 % 2 + y_1 % 2) == (x_2 % 2 + y_2 % 2) || ((x_1 % 2 == y_1 % 2) && (x_2 % 2 == y_2 % 2)))
		printf("2 ");
	/*
	(x_1 % 2 + y_1 % 2) == (x_2 % 2 + y_2 % 2):
	[不计顺序]
	①(1 + 0) == (1 + 0) 		一奇一偶 	白 
	②(1 + 1) == (1 + 1)		双奇		黑 
	③(0 + 0) == (0 + 0)		双偶		黑 
	
	(x_1 % 2 == y_1 % 2) && (x_2 % 2 == y_2 % 2)
	(0 == 0) && (1 == 1)		一个双奇另一个双偶 黑 
	*/ 
	else printf("0 ");
}

void solve_king()
{
	int ans = max(abs(x_1 - x_2), abs(y_1 - y_2));
	printf("%d", ans);
}
```

---

## 作者：YangXiaopei (赞：1)

## Solution:
~~这是一道数学题~~。

三种棋子分别来看：

* 车：只要不在原点，否则定为 $2$ 次。

* 王：王可到达周围八格中的任意一格，但 $1$ 次最多只能移动 $1$ 行或 $1$ 列，所以王至少要走的步数为目标点与出发点横纵坐标之差中较大的一个。

* 象：象可两步到达所有一步可达点的对角线上的任意点，所以该点的 $y-x$ 或 $x+y$ 与象所在对角线上的一个点相同，且该点 $y+x$ 或 $x-y$ 与象相同。又因为 $y-x$ 与 $y+x$ 的奇偶性必然相同，所以象只能到达横纵坐标之和的奇偶性与其所在格相同的格子。

明白了证明，按证明来写即可。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int che(int a, int b, int x, int y){//车
	if(a == x || b == y){
 		return 1;
	}
 	else{
 		return 2;
	}
}
int wang(int a, int b, int x, int y){//王
	return max(abs(x - a), abs(y - b));
}
int xiang(int a, int b, int x, int y){//象
	if(x + y == a + b || x - y == a - b){
		return 1;
	}
 	else if((x + y) % 2 != (a + b) % 2){
 		return 0;
	}
    return 2;
}
int a, b, x, y;
int main(){
	cin >> a >> b >> x >> y;
	cout << che(a, b, x, y) << " " << xiang(a, b, x, y) << " " << wang(a, b, x, y)
 	return 0;
}
```
## 完结撒花。

---

## 作者：hensier (赞：1)

~~由于该题是本蒟蒻翻译的，因此不如也配一个题解~~

这道题需要进行全面分析。对于车，我们可以得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/nld9z9u3.png)

我们任选一个格子为出发点。我们可以很容易地注意到，$STEP_{rook}∈\{1,2\}$。如果出发点和目的地点的行、列有一者相同，则称为可以“直达”，因为这时车可以直接过去，否则车就需要中转。例如上图中，车如果要从$g8$到$a1$，则它可以走$g8->a8->a1$或$g8->g1->a1$。

对于象：

![](https://cdn.luogu.com.cn/upload/image_hosting/ngek2eix.png)

下过国象的大佬们都知道，经典棋局中，每一方都有两个象——它们可以通过格子的颜色进行区分——因为一个象的出发格和目的地格的格子颜色永远是一样的。因此，这里我们先做出特判——如果格子颜色不同直接输出$0$，否则继续判断。我们同样能够注意到：$STEP_{bishop}∈\{0,1,2\}$。如果出发点和目的地格在同一主/副对角线上，则$STEP_{bishop}=1$，否则$STEP_{bishop}=2$。

对于王：

![](https://cdn.luogu.com.cn/upload/image_hosting/my3q2foj.png)

$STEP_{king}∈\{1,...,14\}$。我们可以发现，王先斜移、再横/竖移的步数最少。如果出发点和目的地分别为$(a,b),(c,d)$，则可以有$(a,b)->(c,c-a)->(c,d)$。这可以转化为$max(abs(a-c),abs(b-d))$。加$max$的原因是，无论$b-d$为多少，只要$a-c>b-d$（这里假设$a>c,b>d$），就一定有步数为上述公式。举一个最容易理解的例子——国王要从$a1$移动到$h$这一排。我们发现，无论如何，最短的路径也都满足这个公式。

根据多次实验和严密推导，我们可以得到下列的答案：

![](https://cdn.luogu.com.cn/upload/image_hosting/j1nkmbow.png)

~~（公式无法在题解页面兼容，因此本蒟蒻截了一张图）~~

通过上述结论，我们可以得到：（只要情况都全面，代码不是特别难，因此就不加注释了）

```cpp
#include<cstdio>
#define max(a,b) a>b?a:b
inline int abs(int a){if(a>0)return a;return -a;}
int r1,c1,r2,c2;
int main()
{
    scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
    if(r1==r2||c1==c2)printf("1");
    else printf("2");
    if((r1+c1)%2-(r2+c2)%2)printf(" 0 ");
    else if(r1+c1==r2+c2||r1-c1==r2-c2)printf(" 1 ");
    else printf(" 2 ");
    printf("%d",max(abs(r1-r2),abs(c1-c2)));
}
```

---

## 作者：fish_shit (赞：0)

## 分析
车：如果在同一行或同一列，$1$ 步就可到达目标点；否则需要 $2$ 步。

象：如果在同 $1$ 对角线上，仅需一步；如果在不同颜色的格上（两点的 $x$ 和 $y$ 的加和模 $2$ 的结果不同），就无法到达；如果二者都不满足，$2$ 步即可到达。

王：目标点与起始点的 $x$ 和 $y$ 的差中的较大的那一个。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int r1,r2,c1,c2;
	cin>>r1>>r2>>c1>>c2;
	//车 
	if(r1==c1||r2==c2){
		cout<<1<<'\n';
	}
	else{
		cout<<2<<'\n';
	}
	//象
	if(abs(r1-c1)==abs(r2-c2)){
		cout<<1<<'\n';
	} 
	else if((r1+r2)%2!=(c1+c2)%2){
		cout<<0<<'\n';
	}
	else{
		cout<<2<<'\n';
	}
	//王 
	cout<<max(abs(r1-c1),abs(r2-c2))<<'\n';
	return 0;
}

```


---

## 作者：InversionShadow (赞：0)

## 车：

+ $r_1=r_2$，那么只需一步移到 $(c_1,c_2)$，$c_1=c_2$ 同理。

+ 令当前列为 $a=r_1$，行为 $b=c_1$，那么先要移到 $a=r_2,b=c_1$，再移到 $a=r_2,b=c_2$，需要两步。

## 象：

+ $|r_1-r_2|=|c_1-c_2|$，即再同一对角线上，只需一步即可。

+ $(r_1+c_1) \bmod 2 \neq (r_2+c_2) \bmod 2$，即两个地方不在同一颜色内，象不可能到达，输出 `0`。

+ 否则输出 `2`。

## 王：

+ $r_1=r_2$，即在同一列上，需要 $|c_1-c_2|$ 步。

+ $c_1=c_2$，即在同一行上，需要 $|r_1-r_2|$ 步。

+ 王 $1$ 次可以改变 $1$ 行或 $1$ 列，所以王至少要走的步数为目标点与出发点横纵坐标之差中较大的一个，也就是 $\max\{|r_1-r_2|,|c_1-c_2|\}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int r1, c1, r2, c2;

int main() {
  cin >> r1 >> c1 >> r2 >> c2;
  if (r1 == r2 || c1 == c2) {
    cout << "1 ";
  } else {
    cout << "2 ";
  }
  if (abs(r1 - r2) == abs(c1 - c2)) {
    cout << "1 ";
  } else if ((r1 + c1) % 2 != (r2 + c2) % 2) {
    cout << "0 "; 
  } else {
    cout << "2 ";
  }
  if (r1 == r2) {
    cout << abs(c1 - c2);
    return 0;
  } else if (c1 == c2) {
    cout << abs(r1 - r2);
    return 0;
  }
  cout << max(abs(r1 - r2), abs(c1 - c2));
  return 0;
}
```

---

## 作者：asas111 (赞：0)

## 思路
首先考虑车。
- 如果起点和终点在同 $1$ 行或同 $1$ 列，车就可以只用 $1$ 次移动过去。

- 否则需要移动 $2$ 次，分别要移动行和列。

然后考虑象。
- 象只能移动到和它所在位置同色的格子，所以需要判断两格是否在同色的格子上。再经过观察，可以发现黑格行和列的奇偶性不同，白格行和列的奇偶性相同，分别将这两种格的行和列相加，如果发现它们的奇偶性不同，这时答案为 $0$。

- 接下来再判断答案为 $1$ 的情况，即两格在同一条斜线上。棋盘的对角线有 $2$ 条，第 $1$ 条是左下角连右上角，平行于这一条对角线的斜线上两格的行和列之和是相同的；第 $2$ 条是左上角连右下角，平行于这一条对角线的斜线上两格的行和列之差是相同的，判断这 $2$ 种情况就可以了。

- 其余的情况答案为 $2$，因为象一定可以移动到和终点同一条斜线上的格。

最后考虑王。

- 王一次最多只能走一行一列，所以至少要走两格行坐标之差和列坐标之差中较大的一个。另一个差不会比它大，所以可以斜着走过去。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main(){
	cin>>a>>b>>c>>d;
	if(a==c||b==d)cout<<1<<" ";
	else cout<<2<<" ";
	if((a+b)%2!=(c+d)%2)cout<<0<<" ";
	else if(a+b==c+d||a-b==c-d)cout<<1<<" ";
	else cout<<2<<" ";
	cout<<max(abs(a-c),abs(b-d));
	return 0;
}
```


---

## 作者：Fa1thful (赞：0)

### 一、题意
给你三种走法的棋子，问最少多少步能从起点走到终点。

### 二、分析
首先三种走法，棋盘只有 $8\times8$，所以一种思路就是考虑用三个 `dfs`，模拟每个棋子的走法。但是因为对于每个棋盘上的点都会有一个状态，所以这个算法的复杂度是 $64^8$。很显然数据会炸掉，所以显而易见这个算法并不高效，所以我们分析一下每种棋的路径。

首先车可以两次到达棋盘中任意一点，如果在同一行或者同一列，那么就可以一步到达。

其次是象，玩过国际象棋的都知道国际象棋棋盘上的黑白格就是为了皇后（象）设计的，在白格子里的皇后到不了黑格子，在黑格子里的皇后到不了白格子。其次就与车的走法相同了。

最后是王，王可以走向周围的一圈，这就是一个最基础的 `bfs`，所以直接模拟。

### 三、代码
```cpp
# include <bits/stdc++.h>
# define int long long 
using namespace std;
const int N = 1005;
const int M = 15;
int r1, c1, r2, c2;
int ans = INT_MAX; 
int dx[M] = {0, -1, 0, 1, -1, -1, 1, 1};
int dy[M] = {-1, 0, 1, 0, -1, 1, -1, 1};
bool vis[N][N];
struct node
{
	int x, y, cnt;    //x,y描述了位置,cnt描述了到当前的点最少需要多少步 
};
void bfs(int x, int y)
{
	vis[x][y] = 1;    //当前访问的节点 
	queue <node> q;   //队列 
	q.push((node){x, y, 0});   //状态入队 
	while (q.size())
	{
		node u = q.front();    //取队手 
		q.pop();
		if (u.x == r2 && u.y == c2)   //如果状态到了终点 
		{
			ans = u.cnt;   //记录答案，因为广搜是从一个点往外一直扩散，所以可以理解为广搜搜到的点一定是最少的步数到达的。 
			return;
		}
		for (int i = 0; i < 8; i++)
		{
			int xx = u.x + dx[i];
			int yy = u.y + dy[i];    //往旁边走 
			if (xx < 1 || xx > 8 || yy < 1 || yy > 8 || vis[xx][yy]) continue;//如果访问过或者出界了 
			vis[xx][yy] = 1;   //状态标记入队 
			q.push((node){xx, yy, u.cnt + 1}); //状态入队    
		}
	}
}
signed main() 
{
	memset(vis, 0, sizeof(vis));
	cin >> r1 >> c1 >> r2 >> c2;   //输入起点终点 
	if (r1 == r2 || c1 == c2) cout << 1 << " ";    //如果起点终点在同一行或者同一列，那么车可以一次到达 
	else if (r1 == r2 && c1 == c2) cout << 0 << " ";  //如果起点终点相同，直接到达 
	else cout << 2 << " ";   //其他情况车都可以两次到达 
	if (r1 + c1 == r2 + c2 || r1 - c1 == r2 - c2) cout << 1 << " ";    //在同一斜行 
	else if ((r1 + c1) % 2 != (r2 + c2) % 2) cout << 0 << " ";   //在不同颜色的格子 
	else cout << 2 << " ";   //其他情况象两次就可以到达 
	bfs(r1, c1);   //bfs王的情况 
	cout << ans << endl;    //输出最后的最少步数 
	return 0;
}
```

谢谢观赏

---

## 作者：TLMPEX (赞：0)

思路：这道题有三个棋子，可以用三个BFS来写。具体看代码。

上代码。
```c
#include<queue>
#include<iostream>
#include<string.h>
using namespace std;
int x1,y1,x2,y2,vis[10][10];
int a1[4]={-1,0,0,1},b1[4]={0,-1,1,0};//车的方向数组
int a2[4]={-1,-1,1,1},b2[4]={-1,1,-1,1};//象的方向数组
int a3[8]={-1,0,0,1,-1,-1,1,1},b3[8]={0,-1,1,0,-1,1,-1,1};//王的方向数组
struct node{
	int x,y,z;//x和y为坐标z为走的步数
};
queue<node> q;
int pd(int x,int y){//判断这个坐标是否越出8×8的棋盘
	return x>=1&&y>=1&&x<=8&&y<=8;
}
int BFSA(){//车最少走多少步
	node t;
	t.x=x1,t.y=y1,t.z=0;//初始化
	q.push(t);
	while(!q.empty()){
		node f=q.front();
		q.pop();
		if(f.x==x2&&f.y==y2)return f.z;//如果到了目标地点，则返回当前步数
		for(int i=0;i<4;i++){
			int nx=f.x+a1[i],ny=f.y+b1[i];
			while(pd(nx,ny)){//判断是否在棋盘的范围以内
				if(!vis[nx][ny]){//判断是否标记
					node t;
					t.x=nx,t.y=ny,t.z=f.z+1;
					q.push(t);//入队列
					vis[nx][ny]=1;//标记
				}
				nx+=a1[i],ny+=b1[i];//更新下一个位置
			}
		}
	}
	return 0;//如果到不了，则返回0
}
int BFSB(){
	node t;
	t.x=x1,t.y=y1,t.z=0;//初始化
	q.push(t);
	while(!q.empty()){
		node f=q.front();
		q.pop();
		if(f.x==x2&&f.y==y2)return f.z;//如果到了目标地点，则返回当前步数
		for(int i=0;i<4;i++){
			int nx=f.x+a2[i],ny=f.y+b2[i];
			while(pd(nx,ny)){//判断是否在棋盘的范围以内
				if(!vis[nx][ny]){//判断是否标记
					node t;
					t.x=nx,t.y=ny,t.z=f.z+1;
					q.push(t);//入队列
					vis[nx][ny]=1;//标记
				}
				nx+=a2[i],ny+=b2[i];//更新下一个位置
			}
		}
	}
	return 0;//如果到不了，则返回0
}
int BFSC(){
	node t;
	t.x=x1,t.y=y1,t.z=0;//初始化
	q.push(t);
	while(!q.empty()){
		node f=q.front();
		q.pop();
		if(f.x==x2&&f.y==y2)return f.z;//如果到了目标地点，则返回当前步数
		for(int i=0;i<8;i++){
			int nx=f.x+a3[i],ny=f.y+b3[i];
			if(pd(nx,ny)&&!vis[nx][ny]){//判断是否在棋盘范围以内且没有走过
				vis[nx][ny]=1;//标记
				node t;
				t.x=nx,t.y=ny,t.z=f.z+1;
				q.push(t);//入队列
			}
		}
	}
	return 0;//如果到不了，则返回0
}
int main(){
	cin>>x1>>y1>>x2>>y2;	
	int a=BFSA();//车要走多少步
	while(!q.empty())q.pop();//每次清空队列
	memset(vis,0,sizeof(vis));//每次把标记数组清0
	int b=BFSB();//象要走多少步
	while(!q.empty())q.pop();
	memset(vis,0,sizeof(vis));
	int c=BFSC();//王要走多少步
	cout<<a<<" "<<b<<" "<<c;
}
```

---

## 作者：Franka (赞：0)

### **题目**
给出四个数$r1,c1,r2,c1$，分别表示**起点**和**终点**，求**车、象、王**从$(r1,c1)$到$(r2,c2)$最少要几步。
### **思路**
先看看车、象、王的行走方法。
#### 车：

* 第一种情况

![](https://s1.ax1x.com/2020/05/09/YlHEQI.png)

* 第二种情况

![](https://s1.ax1x.com/2020/05/09/YlHVyt.png)

* 第三种情况

![](https://s1.ax1x.com/2020/05/09/YlHuTS.png)

可以发现，如果是在同一行或同一列，那就是1次，其他的就是两次。

#### 象：

* 第一种情况

![](https://cdn.luogu.com.cn/upload/image_hosting/yoykdsjk.png)

* 第二种情况

![](https://cdn.luogu.com.cn/upload/image_hosting/jiymo092.png)

* 第三种情况

![](https://s1.ax1x.com/2020/05/09/YlHnw8.png)

可以发现如果这两个坐标的差相等或和相等，次数为1；如果两个坐标的和的奇偶性不同，则不能到达；其他情况次数则为2.

#### 王：
次数为$max(abs(r1-r2),abs(c1-c2))$

### 代码

![](https://cdn.luogu.com.cn/upload/image_hosting/lktggsj3.png)

---

