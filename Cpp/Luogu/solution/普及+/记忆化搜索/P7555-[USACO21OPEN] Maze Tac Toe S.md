# [USACO21OPEN] Maze Tac Toe S

## 题目描述

奶牛 Bessie 喜欢玩走迷宫。她同样喜欢玩井字棋（更准确地说，奶牛版的井字棋，马上会进行介绍）。Farmer John 找到了一种全新的方式，可以使她同时玩到这两种游戏！

首先，奶牛井字棋：与在 $3 \times 3$ 棋盘内放置 `X` 和 `O` 不同，奶牛当然是在 $3 \times 3$ 棋盘内放置 `M` 和 `O`。在一方的回合内，玩家可以选择将一个 `M` 或一个 `O` 放在任意一个空格内（这是另一个与标准井字棋的不同之处，标准的井字棋中一名玩家始终放 `X` 而另一名玩家始终放 `O`）。奶牛井字棋的胜利方是首位拼出 `MOO` 的玩家，可以是同行、同列或对角线。倒着拼出也是可以的，例如一名玩家在棋盘的一行内拼出 `OOM` 也可以获胜。如同标准井字棋一样，有可能最后没有玩家取得胜利。奶牛井字棋的一次行动通常用 3 个字符表示，`Mij` 或 `Oij`，其中 $i$ 和 $j$ 在范围 $1 \ldots 3$ 之间，表示放置 `M` 或 `O` 的行与列。

为了给 Bessie 增加一些挑战，Farmer John 设计了一个由 $N \times N$ 个方格组成的正方形迷宫（$3 \leq N \leq 25$）。某些方格，包括所有的边界方格，有巨大的草堆，使得 Bessie 不能移动到这些方格。Bessie 可以沿东南西北四个方向在迷宫内的所有其他方格内自由行动。某些方格内有一张纸，上面写有奶牛井字棋的一次行动。当 Bessie 在迷宫中移动时，任何时刻她停留在这样的方格上，她都必须于迷宫中移动之时在同时进行的奶牛井字棋游戏内做出对应的行动（除非奶牛井字棋中对应的方格已经被填上了，在这种情况下她不进行行动）。在奶牛井字棋游戏内没有与她对阵的玩家，但迷宫中的某些方格可能会不利于她最终拼出 `MOO`。

如果 Bessie 在获胜之时就会立刻停止奶牛井字棋，请求出她可以通过适当的方式在迷宫中移动而完成的不同的胜利状态棋盘数量。

## 说明/提示

#### 样例说明

在这个样例中，Bessie 最终可能达成 $8$ 种胜利的棋盘状态：

```plain
O.M
.O.
MOM

O..
.O.
.OM

O.M
.O.
.OM

O..
.O.
MOM

O..
...
OOM

..M
.O.
OOM

...
.O.
OOM

...
...
OOM
```

对其中一种情况进行说明：

```plain
O..
...
OOM
```

在这里，Bessie 可以先移动到 `O11` 方格，然后移动到下方并通过 `O32`、`M33` 和 `O31`。此时游戏结束，因为她获得了胜利（例如她不能再前往位于她当前所在的 `O31` 方格北面的 `M11` 方格）。

#### 说明

供题：Brian Dean

## 样例 #1

### 输入

```
7
#####################
###O11###...###M13###
###......O22......###
###...######M22######
###BBB###M31###M11###
###...O32...M33O31###
#####################```

### 输出

```
8```

# 题解

## 作者：tiger2005 (赞：8)

建议读懂题目后再阅读下面的内容。

首先我们发现，可以使用一个 $3^9$ 大小的数字储存下一个井字棋状态。由于 $3^9 \leq 2*10^5$，所以我们可以考虑 $O(3^9N^2)$ 的方法。

考虑进行深度优先搜索。使用 `bool hav[N][N][3**9]` 记录下这个状态是否出现过（位置和井字棋的状态），防止重复搜索。如果没有被搜索过，首先判断这个位置上要不要填入棋子，需要的话改变状态。然后判断这个状态是否胜利，是的话记录并且退出。最后想四个方向进行搜索即可。

对于可行状态，可以直接转换成 `3*3` 的数组，然后暴力判断。建议先预处理出所有状态的可行性。


```cpp
#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;
int N;
char Maz[30][100];
int pw[10];
int fang[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
bool dp[30][30][20010];
bool pd[20010];
bool isP[20010];
char mp[5][5];
inline bool isWin(int k){
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++){
			mp[i][j]=k%3;
			if(mp[i][j]==0)	mp[i][j]='.';
			else if(mp[i][j]==1)	mp[i][j]='M';
			else	mp[i][j]='O';
			k/=3;
		}
	string p="";
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++)
			p+=mp[i][j];
		if(p=="MOO" || p=="OOM")	return true;
		p="";
	}
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++)
			p+=mp[j][i];
		if(p=="MOO" || p=="OOM")	return true;
		p="";
	}
	for(int i=1;i<=3;i++)
		p+=mp[i][i];
	if(p=="MOO" || p=="OOM")	return true;
	p="";
	for(int i=1;i<=3;i++)
		p+=mp[i][4-i];
	if(p=="MOO" || p=="OOM")	return true;
	return false;
}
int Draw(int k,char q,int x,int y){
	x=3*x+y;
	int u=(k/pw[x])%3;
	if(u!=0)	return k;
	return k+(q=='M'?1:2)*pw[x];
}
int ans;
void dfs(int x,int y,int k){
	if(Maz[x][3*y+1]=='M' || Maz[x][3*y+1]=='O')
		k=Draw(k,Maz[x][3*y+1],Maz[x][3*y+2]-'1',Maz[x][3*y+3]-'1');
	if(dp[x][y][k])	return;
	dp[x][y][k]=true;
	if(isP[k]){
		ans+=!pd[k];
		pd[k]=true;
		return;
	}
	for(int i=0,xx,yy;i<4;i++){
		xx=x+fang[i][0],yy=y+fang[i][1];
		if(Maz[xx][3*yy+1]!='\0' && Maz[xx][3*yy+1]!='#')
			dfs(xx,yy,k);
	}
}
int main(){
	pw[0]=1;
	for(int i=1;i<=9;i++)	pw[i]=pw[i-1]*3;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf(" %s",Maz[i]+1);
	for(int i=0;i<pw[9];i++)	isP[i]=isWin(i);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			if(Maz[i][3*j+1]=='B')
				dfs(i,j,0);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：NDFS (赞：3)

这题思维难度较低，主要考的是写代码和调试能力。

发现数据范围很小，$N \leq 25$，考虑搜索，把井字棋棋盘压成三进制，记忆化深搜。

具体步骤：搜到某个点改变状态后，判断是否有出现过这个状态，标记当前状态，判断是否胜利，向上下左右继续搜索。

时间复杂度大概是 $O(N^2)$，还要算上一些三进制转换的小常数。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,px[26][26],py[26][26],sx,sy,sum=0,a[26][26],num[10],bz;
bool pd[20005],v[26][26][20005];
char s[110];
void transfrom(int temp)//从三进制到十进制
{
	for(int i=9;i>=1;i--)num[i]=temp%3,temp/=3;
}
int ksm(int a,int b)//快速幂
{
	int c=1;
	while(b)
	{
		if(b&1)c=c*a;
		a=a*a,b>>=1;
	}
	return c;
}
int transto()//从十进制到三进制
{
	int temp=0;
	for(int i=9;i>=1;i--)temp+=num[i]*ksm(3,9-i);
	return temp;
}
void dfs(int x,int y,int temp)
{
	if(a[x][y]==-1)return;
	transfrom(temp);
	if(a[x][y]&&!num[(px[x][y]-1)*3+py[x][y]])num[(px[x][y]-1)*3+py[x][y]]=a[x][y],temp=transto();//更改状态
	if(v[x][y][temp])return;
	v[x][y][temp]=1,bz=0;
	//判断是否胜利
	for(int i=1;i<=3;i++)
	{
		if(num[(i-1)*3+1]==2&&num[(i-1)*3+2]==1&&num[(i-1)*3+3]==1)bz=1;
		if(num[(i-1)*3+3]==2&&num[(i-1)*3+2]==1&&num[(i-1)*3+1]==1)bz=1;
	}
	for(int i=1;i<=3;i++)
	{
		if(num[i]==2&&num[i+3]==1&&num[i+6]==1)bz=1;
		if(num[i+6]==2&&num[i+3]==1&&num[i]==1)bz=1;
	}
	if(num[5]==1)
	{
		if((num[1]==2&&num[9]==1)||(num[9]==2&&num[1]==1))bz=1;
		if((num[3]==2&&num[7]==1)||(num[7]==2&&num[3]==1))bz=1;
	}
	if(bz)
	{
		sum+=!pd[temp],pd[temp]=1;return;
	}
	dfs(x+1,y,temp),dfs(x,y+1,temp),dfs(x-1,y,temp),dfs(x,y-1,temp);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=3;j<=3*n;j+=3)
		{
			if(s[j]=='#')a[i][j/3]=-1;
			else if(s[j]=='.')a[i][j/3]=0;
			else if(s[j]=='B')sx=i,sy=j/3;
			else
			{
				if(s[j-2]=='O')a[i][j/3]=1;
				else a[i][j/3]=2;
				px[i][j/3]=s[j-1]-'0',py[i][j/3]=s[j]-'0';
			}
		}
	}
	dfs(sx,sy,0);
	printf("%d",sum);
	return 0;
}
```

---

## 作者：打程序的咸鱼 (赞：2)

## 前言

希望审核能给我过了这篇题解 。

## 题目

[题目传送门](https://www.luogu.com.cn/problem/P7555)
## 题意
这个题目是说有一个迷宫，Bessie 在上面行走
然后有一个 $3 \times 3$ 的方格举证，用来玩奶牛版的井字棋
就是要在这些方格直线，竖线，或者斜线摆出一个 MOO 或者 OOM 
问你胜利的时候有多少种状态。
## 题解
这里我们可以使用状态压缩。

举一个例子：
- - - 
1	2	3
- - - 
4	5	6
- - - 
7	8	9
- - - 
上面的编号是这个九宫格各个点的编号，然后使用状态压缩。

就是把第一个乘以 3 的 0 次方，以此类推，第 i 个乘以 3 的 i - 1 次方。

然后把这个数据存在一个变量 k 里面，这样就可以把这个方格矩阵压缩为 k 。

其中为什么要使用 3 进制压缩的原因如下：

0 可以代表空地， 1 代表 M ， 2 代表 O ，$k % 3$可以解压得到。

还有，这里的进制必须尽量小，否则存的空间就会大。

关于如何解压这个 k ，首先遍历每一个方格：（这里先用二维数组存，用一维也可）

- - - 

For i 1-3

For j 1-3
    
这个 $t_{i,j}$ 代表第 i 行第 j 列的数字（或者字符）是什么。

For i 1-3

For j 1-3

这里将这一位的余数取出来 ： $x=k \bmod 3$

然后这里再判断一下 x 代表的是什么？（ 0 为空， 1 为 M ， 2 为 O ）

然后把 $k\div3$ ，这样跳过下一位。

这个 t 数组就是解压的结果。

- - - 

这一道题目可以有一个优化：设一个数组 vis 代表当前状态有没有被选。

如果有的话，就直接返回。

然后过程可以使用 dfs 进行搜索，然后使用状态压缩进行优化。

Ps ： 这里也许还有一些优化点我没有使用，但是我是过了的。
你们可以使用一些优化 。 ~~（这不是我的错吧？）~~

时间复杂度： $((N-2)^2)*(3^9)*4*9$

（~~如果有大佬发现不对，请评论区指出~~）

```cpp
#include <cstdio>
#include <set>
using namespace std;
 
int N;
char board[25][25][3];
set<int> answers;
bool beenthere[25][25][19683];
int pow3[10];
 
bool test_win(int b)
{
  int cells[3][3];
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++) {
      cells[i][j] = b%3;
      b /= 3;
    }
  for (int r=0; r<3; r++) {
    if (cells[r][0] == 1 && cells[r][1] == 2 && cells[r][2] == 2) return true;
    if (cells[r][0] == 2 && cells[r][1] == 2 && cells[r][2] == 1) return true;
  }
  for (int c=0; c<3; c++) {
    if (cells[0][c] == 1 && cells[1][c] == 2 && cells[2][c] == 2) return true;
    if (cells[0][c] == 2 && cells[1][c] == 2 && cells[2][c] == 1) return true;
  }
  if (cells[0][0] == 1 && cells[1][1] == 2 && cells[2][2] == 2) return true;
  if (cells[0][0] == 2 && cells[1][1] == 2 && cells[2][2] == 1) return true;
  if (cells[2][0] == 1 && cells[1][1] == 2 && cells[0][2] == 2) return true;
  if (cells[2][0] == 2 && cells[1][1] == 2 && cells[0][2] == 1) return true;
  return false;
}
 
void dfs(int i, int j, int b)
{
  if (beenthere[i][j][b]) return;
  beenthere[i][j][b] = true;
  if (board[i][j][0]=='M' || board[i][j][0]=='O') {
    int r = board[i][j][1]-'1', c = board[i][j][2]-'1', idx = r*3+c;
    int current_char = (b / pow3[idx]) % 3;
    if (current_char == 0) {
      int new_char = board[i][j][0]=='M' ? 1 : 2;
      b = (b % pow3[idx]) + new_char * pow3[idx] + (b - b % pow3[idx+1]);
      if (!beenthere[i][j][b] && test_win(b)) { answers.insert(b); return; }
      beenthere[i][j][b] = true;
    }
  }
  if (board[i-1][j][0] != '#') dfs(i-1,j,b);
  if (board[i+1][j][0] != '#') dfs(i+1,j,b);
  if (board[i][j-1][0] != '#') dfs(i,j-1,b);
  if (board[i][j+1][0] != '#') dfs(i,j+1,b);
}
 
int main(void)
{
  int bess_i, bess_j, bstate = 0;
  pow3[0] = 1;
  for (int i=1; i<=9; i++) pow3[i] = pow3[i-1]*3;
  scanf ("%d", &N);
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++) {
      scanf (" %c%c%c", &board[i][j][0], &board[i][j][1], &board[i][j][2]);
      if (board[i][j][0] == 'B') { bess_i = i; bess_j = j; }
    }
  dfs(bess_i, bess_j, bstate);
  printf ("%d\n", (int)answers.size()); 
}

```
### 最后希望这篇题解能帮到屏幕前的你 ， 但是不要抄袭哦 ！

---

## 作者：CrTsIr400 (赞：1)

https://blog.csdn.net/STJqwq/article/details/119718617

题目其实没有什么思维难度，就是代码难度比较大。

设状态 $bz[S][i][j]$ 为当前在 $(i,j)$ 点而井字棋状态为 $S$ （三进制数）是否从起点可达。

那么考虑状态压缩，代码码量就在判定和状态压缩上了。

判定很好写，判断行列对角线；

状态压缩常数略大，因为是三进制不好写。

具体细节看代码。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int inf=1073741823;typedef long long LL;int FL;char CH;template<typename T>bool in(T&a){if(CH==EOF)return 0;for(FL=1,CH=getchar(),a=0;(CH<'0'||CH>'9')&&CH!=EOF;CH=getchar())if(CH=='-')FL=-1;for(;CH>='0'&&CH<='9'&&CH!=EOF;CH=getchar())a=a*10+CH-'0';return a*=FL,1;}template<typename T,typename...Args>int in(T&a,Args&...args){return in(a)+in(args...);}
bool f[20000][26][26],ish[20000];
int n,pw3[10]={1};
int acnt,ox[626],oy[626],op[626],BX,BY;
char ss[4];
int a[26][26],len; 
void Get(int x,int y){//输入时预处理
	CH=getchar();
	while(!isgraph(CH))CH=getchar();
	ss[1]=CH;CH=getchar();
	ss[2]=CH;CH=getchar();
	ss[3]=CH;
	if(ss[1]=='#'){a[x][y]=-1;return;}
	if(ss[1]=='.'){a[x][y]=0;return;}
	if(ss[1]=='O'||ss[1]=='M'){
		a[x][y]=++acnt;
		op[acnt]=(ss[1]=='O')?1:2;
		ox[acnt]=ss[2]-'0';
		oy[acnt]=ss[3]-'0';
		return;
	}if(ss[1]=='B')BX=x,BY=y;
}
int X[625*20000],Y[625*20000],SQ[625*20000],l,r;
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}},num[10];
bool chk(int S){//判定
	for(RI i=1;i<=9;++i)num[i]=S%3,S/=3;
	for(RI i=1;i<=3;++i){
		if(num[i]==1&&num[i+3]==1&&num[i+6]==2)return 1;//竖列
		if(num[i]==2&&num[i+3]==1&&num[i+6]==1)return 1;
	}for(RI i=1;i<=9;i+=3){
		if(num[i]==1&&num[i+1]==1&&num[i+2]==2)return 1;//横行
		if(num[i]==2&&num[i+1]==1&&num[i+2]==1)return 1;
	}if(num[1]==2&&num[5]==1&&num[9]==1)return 1;//对角线
	if(num[1]==1&&num[5]==1&&num[9]==2)return 1;
	if(num[3]==2&&num[5]==1&&num[7]==1)return 1;//对角线
	if(num[3]==1&&num[5]==1&&num[7]==2)return 1;
	return 0;
}
int nws(int S,int nmp){//到了新的节点，产生新状态
	if(!nmp)return S;
	int res=0,ps;
	for(RI i=1;i<=9;++i)num[i]=S%3,S/=3;
	ps=(ox[nmp]-1)*3+oy[nmp];
	if(!num[ps])num[ps]=op[nmp];
	for(RI i=9;i;--i)res=res*3+num[i];
	return res;
}
void print(int S){//调试输出
	for(RI i=1;i<=9;++i)putchar(S%3+'0'),S/=3;
}
void ext(int ST,int sx,int sy){//扩展
	l=1,r=0;
	X[++r]=sx;Y[r]=sy;SQ[r]=ST;ish[ST]=1;
	while(l<=r){
		int x=X[l],y=Y[l],S=SQ[l],xx,yy;++l;
		for(RI i=0;i<=3;++i){
			xx=x+dir[i][0];//扩展终点
			yy=y+dir[i][1];
			if(a[xx][yy]==-1)continue;
			RI SS=nws(S,a[xx][yy]);
			if(f[SS][xx][yy])continue;
			f[SS][xx][yy]|=f[S][x][y];ish[SS]|=f[SS][xx][yy];
			if(chk(SS))continue;//如果到达终点就不要继续了
			X[++r]=xx;Y[r]=yy;SQ[r]=SS;
		}
	}
	int ans=0;
	for(RI i=1;i<=pw3[9];++i)if(ish[i]&&chk(i))++ans;//计算合法的终点个数
	printf("%d\n",ans);
}
int main(){
	in(n);
	for(RI i=1;i<=n;++i)
	for(RI j=1;j<=n;++j)Get(i,j);
	for(RI i=1;i<=9;++i)pw3[i]=pw3[i-1]*3;
	f[0][BX][BY]=1;
	ext(0,BX,BY);
	return 0;
}
```

---

