# [USACO08DEC] Jigsaw Puzzles S

## 题目描述

The cows have taken up alphabetical jigsaw puzzles. In these puzzles with R (1 <= R <= 10) rows and C (1 <= C <= 10) columns, the edges are not funny-shaped cardboard shapes but rather are letters.

Each piece has a serial number and 4 letters (or borders) that must be aligned as in a regular jigsaw puzzle. The pseudo-letter '0' (the digit 0) will represent a border (and a piece can have several borders if it is a corner piece or even the top of column in a, e.g., 4x1 puzzle).  Below is a set of six pieces (the borders are marked with lines instead of '0's) assembled in one way (of many) that completes the puzzle:

+---+  +---+  +---+

| 1 c  c 3 d  d 5 | 
+-d-+  + a +  +-e-+

+-d-+  +-a-+  +-e-+

| 2 b  b 4 b  b 6 | 
+---+  +---+  +---+

Note that each edge letter of each piece matches the border letter of the piece adjacent to it; the borders appear properly on the top, bottom, and sides.

Pieces are represented by a serial number and a clockwise list of their four edges (where edges are the letters a..z and 0). Pieces might require rotation when placed in the puzzle.

Given a set of pieces, find at least one way to assemble them into a puzzle. Test data for puzzles with larger R and C are easier to solve because they have a more varied set of edge letters.

奶牛们在玩按字母表顺序排列的拼图谜题.每道谜题有R(1≤R≤10)列C(1≤C≤10)行的拼图块,它们边缘是由字母或封闭边界组成,完成后的整副拼图外围是边界线,中间的边界是字母.

每块拼图块都有一个序列号和4个字母或者数字表示边界线(顺序为上右下左),在输入中,数字充当边界线.

拼图可以换位和旋转,完成后的拼图在边缘的块上靠近外围的是边界线,拼图完成后,一块拼图若与另一块相邻,它们的边界字母必须相同,以下是一系列已经成功完成的拼图谜题共6块.


## 说明/提示

Describes the input puzzle although with some of the pieces rotated compared to the sample solution.


As shown in the diagram in the task text. Other solutions (like reflections) are possible; a grading program will check your answer.


## 样例 #1

### 输入

```
2 3 
1 c d 0 0 
2 0 d b 0 
3 c 0 d a 
4 b a b 0 
5 d 0 0 e 
6 0 0 b e 
```

### 输出

```
1 0 c d 0 
3 0 d a c 
5 0 0 e d 
2 d b 0 0 
4 a b 0 b 
6 e 0 0 b 
```

# 题解

## 作者：do_while_false (赞：2)

[题目](https://www.luogu.com.cn/problem/P2927)

此题可以直接用暴力搜索过，但注意代码里有许多细节，要注意，代码还是比较长的，要注意细节。

我们只要先将输入的数据按字母表顺序排序一遍，然后再跑一遍dfs即可，具体的说明都在代码里。

代码如下：

```cpp
#include<bits/stdc++.h>//万能头 
#define MAXN 100 + 10 //数组的最大范围 
using namespace std;//标准命名空间 
int n,m,ans,visit[MAXN],id[MAXN][MAXN],v[MAXN][MAXN],sum[MAXN][MAXN],f[MAXN][MAXN];
int fx[5]={0,-1,0,1,0},fy[5]={0,0,1,0,-1},which[5]={0,3,4,1,2};//用于dfs的方向数组 
char s[10];//用于输入 
struct node {
	int x;
	char c[5][5];
}a[MAXN];//用于储存 
bool cmp(node x,node y) {//比较函数 
	return x.x<y.x;
}
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
void dfs(int x,int y) {//暴力搜索 
	if(ans) return;//边界条件 
	if(x==n+1&&y==1) {//边界条件2 
		if(ans==0) {//边界条件3
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					sum[i][j]=id[i][j],f[i][j]=v[i][j];
			ans=1;//使其不满足条件，退出循环 
		}
		return;
	}
	int xx,yy,nx,ny;
	if(y+1<=m) nx=x,ny=y+1;//初始化
	else nx=x+1,ny=1;//初始化
	bool bk;
	for(int i=1;i<=n*m;i++) {
		if(visit[i]) continue;//访问过了，进入下一次循环 
		for(int j=1;j<=4;j++) {
			bk=1;//初始化 
			for(int k=1;k<=4;k++) {
				xx=x+fx[k];//下一轮搜索的下标 
				yy=y+fy[k];//下一轮搜索的下标 
				if(xx>=1&&yy>=1&&xx<=n&&yy<=m) {//判断是否越界 
					int o=id[xx][yy],q=v[xx][yy];//下一轮搜索的值 
					if(o&&q&&a[i].c[j][k]!=a[o].c[q]//判断是否可以拼在一起[which[k]]) {
						bk=0;break;//退出循环 
					}
				}
				else if(a[i].c[j][k]!='0') {//否则就直接返回 
					bk=0;break;//退出循环 
				}
			}
			if(bk) {//符合条件，继续搜索 
				id[x][y]=i;v[x][y]=j;visit[i]=1;//标记访问 
				dfs(nx,ny);//继续搜索 
				id[x][y]=0;v[x][y]=0;visit[i]=0;//回溯 
			}
		}
	}	
}

int main(void) {
	n=read();m=read();//输入 
	for(int i=1;i<=n*m;i++) {
		a[i].x=read();//输入 
		for(int j=1;j<=4;j++) {
			scanf("%s",s);//输入 
			a[i].c[1][j]=s[0];//赋值 
		}
		for(int j=2;j<=4;j++)
			for(int k=1;k<=4;k++) 
				a[i].c[j][k]=a[i].c[j-1][(k-1==0)?4:k-1];//储存 
	}
	sort(a+1,a+1+n*m,cmp);//排序 
	memset(v,0,sizeof(v));//初始化 
	memset(id,0,sizeof(id));//初始化 
	memset(visit,0,sizeof(visit));//初始化 
	ans=0;//初始化 
	dfs(1,1);//开始搜索 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			printf("%d ",a[sum[i][j]].x);//输出答案 
			for(int k=1;k<=4;k++) {
				printf("%c ",a[sum[i][j]].c[f[i][j]][k]);//输出答案 
			}
			printf("\n");//输出答案 
		}
	return 0;
}
```

管理员求过，QWQ。

---

## 作者：swkyccbb (赞：2)

这一道题小编本人为了找出一个较优的方案花了十分钟，最后发现直接爆搜就可以过了。代码量稍稍有些大，但思路还是比较清晰的。

附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int num,ax[5];
} t[102];
int r,c;
char s[0];
int w[15][15],b[15][15];
bool vis[102];
bool cmp(node x,node y) {
	return x.num<y.num;
}
void print(){			//输出答案 
	for(int i=1; i<=r; i++)
		for(int j=1; j<=c; j++) {
			printf("%d ",t[b[i][j]].num);
			for(int k=0; k<4; k++) {
				int x=t[b[i][j]].ax[(k+w[i][j])%4];
				if(x==0) printf("0 ");
				else printf("%c ",x+'a'-1);
			}
			printf("\n");
		}
}
bool sigh=0;
void dfs(int x,int y) {
	if(x==r+1) {
		print();
		sigh=1;
		return;
	}
	if(y==c+1) {
		dfs(x+1,1);
		return;
	}
	for(int i=1; i<=r*c; i++){ 
		if(!vis[i]) {
			for(int k=0; k<4; k++){ 
				if(t[i].ax[k]==t[b[x-1][y]].ax[(w[x-1][y]+2)%4] && t[i].ax[(k+3)%4]==t[b[x][y-1]].ax[(w[x][y-1]+1)%4]) {
					if(y==c&&t[i].ax[(k+1)%4]!=0) continue;
					if(y!=c&&t[i].ax[(k+1)%4]==0) continue;
					if(x!=r&&t[i].ax[(k+2)%4]==0) continue;
					if(x==r&&t[i].ax[(k+2)%4]!=0) continue;		//判断是否可以拼在一起 
					w[x][y]=k;
					b[x][y]=i;
					vis[i]=1;
					dfs(x,y+1);
					vis[i]=0;		//回溯
					if(sigh==1) return;
				}
			} 
		}
	} 
}

int main() {
	scanf("%d%d",&r,&c);
	for(int i=1; i<=r*c; i++) {
		scanf("%d",&t[i].num);
		for(int k=0; k<4; k++) {
			scanf("%s",s);
			if(s[0]=='0') t[i].ax[k]=0;
			else t[i].ax[k]=s[0]-'a'+1;		//转化
		}
	}
	memset(vis,0,sizeof(vis));
	memset(b,0,sizeof(b));
	memset(w,0,sizeof(w));		//初始化 
	for(int i=0; i<4; i++) t[0].ax[i]=0;
	sort(t+1,t+1+r*c,cmp);		//排序
	dfs(1,1);
	return 0;
}
```


---

