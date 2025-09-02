# [USACO19JAN] Icy Perimeter S

## 题目背景

USACO 一月月赛银组第二题

## 题目描述

Farmer John 要开始他的冰激凌生意了！他制造了一台可以生产冰激凌球的机器，然而不幸的是形状不太规则，所以他现在希望优化一下这台机器，使其产出的冰激凌球的形状更加合理。
机器生产出的冰激凌的形状可以用一个 $N \times N$（$1 \leq N \leq 1000$）的矩形图案表示，例如：

```
##....
....#.
.#..#.
.#####
...###
....##
```

每个 `.` 字符表示空的区域，每个 `#` 字符表示一块 $1 \times 1$ 的正方形格子大小的冰激凌。

不幸的是，机器当前工作得并不是很正常，可能会生产出多个互不相连的冰激凌球（上图中有两个）。一个冰激凌球是连通的，如果其中每个冰激凌的正方形格子都可以从这个冰激凌球中其他所有的冰激凌格子出发重复地前往东、南、西、北四个方向上相邻的冰激凌格子所到达。

Farmer John 想要求出他的面积最大的冰激凌球的面积和周长。冰激凌球的面积就是这个冰激凌球中 `#` 的数量。如果有多个冰激凌球并列面积最大，他想要知道其中周长最小的冰激凌球的周长。在上图中，小的冰激凌球的面积为 $2$，周长为 $6$，大的冰激凌球的面积为 $13$，周长为 $22$。

注意一个冰激凌球可能在中间有“洞”（由冰激凌包围着的空的区域）。如果这样，洞的边界同样计入冰激凌球的周长。冰激凌球也可能出现在被其他冰激凌球包围的区域内，在这种情况下它们计为不同的冰激凌球。例如，以下这种情况包括一个面积为 $1$ 的冰激凌球，被包围在一个面积为 $16$ 的冰激凌球内：

```
#####
#...#
#.#.#
#...#
#####
```

同时求得冰激凌球的面积和周长十分重要，因为 Farmer John 最终想要最小化周长与面积的比值，他称这是他的冰激凌的“冰周率”。当这个比率较小的时候，冰激凌化得比较慢，因为此时冰激凌单位质量的表面积较小。


## 样例 #1

### 输入

```
6
##....
....#.
.#..#.
.#####
...###
....##```

### 输出

```
13 22```

# 题解

## 作者：Swire (赞：25)

这道题个人认为用dfs比较好理解

但是dfs有可能或爆栈

所以一下代码仅供参考

冰淇淋的面积用dfs很好求

只要算出每个联通块中'#'的个数即可

难点(?)在于求联通快的周长

其实也很好想

观察一下样例
发现周长就是每个'#'周围'.'或超过边界的方块个数

解决这一问题后这道题几乎就是一道dfs裸题了

```cpp
#pragma GCC optimize("no-stack-protector")//对堆栈的一点优化(或许可以防止爆栈)
#include<iostream>
#define HAND
const int MAXN=1e3+7;
const int dx[]= {0,1,0,-1},dy[]= {1,0,-1,0};
int n,S,C,mxs,mic;//S是面积 C是周长
char ice[MAXN][MAXN];
bool vis[MAXN][MAXN];
void dfs(int x,int y) {
	if(vis[x][y])
		return ;
	vis[x][y]=true;
	S++;
	for(int d=0; d<4; d++) {
		int xx=x+dx[d],yy=y+dy[d];
		if(xx<1||xx>n||yy<1||yy>n||ice[xx][yy]=='.')//注意周长条件处理
			C++;
		if(ice[xx][yy]=='#')
			dfs(xx,yy);
	}
	return ;
}
void solve(void) {
	std::cin>>n;
	for(int i=1; i<=n; i++)
		std::cin>>ice[i]+1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if(ice[i][j]=='#'&&!vis[i][j]) {
				S=C=0;
				dfs(i,j);
				if(S>mxs) {
					mxs=S;
					mic=C;
				} else if(S==mxs)
					mic=std::min(mic,C);
			}
		}
	}
	std::cout<<mxs<<' '<<mic;
}
int main(void) {
#ifdef HANDIN
	freopen("perimeter.in","r",stdin);
	freopen("perimeter.out","w",stdout);
#endif
	solve();
	return 0;
}
```


---

## 作者：YyunSu (赞：24)

# 哇塞，好激动，AC了一道蓝题

在学校听大佬说这是一道纯搜索，于是我屁颠屁颠的做了一晚上，

~~没做出来~~，还好有大佬为我指明道路

在此感谢[贞白徐晟](https://www.luogu.org/space/show?uid=66319)，~~不要管大佬的名字颜色~~

看见好多大佬用广搜做，但是本蒟蒻自认为此题深搜更简洁易懂

话不多说，贴代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
char a[1005][1005];
int vis[1005][1005];
int dir[4][2] = {0,1,0,-1,1,0,-1,0}//方向数组，大佬们应该都知道吧...
int n,step = 0,step1 = 0;
int mmp (int r1, int r2) //不用在意函数名，不是我改的...qwq
{
	int k = 0;
	for (int w = 0; w < 4; w++){
		int xx = r1 + dir[w][0];
		int yy = r2 + dir[w][1];
		if (a[xx][yy] == '.') k++;
	}
	return k; 
} //求出上下左右“.”的数量，分开写更直观吧
void dfs(int x,int y) {
	vis[x][y] = step;//标记数组存步数，其实存什么无所谓...
	for(int i = 0; i < 4; i++) {
		int xx = x + dir[i][0];// 求上下左右的横坐标
		int yy = y + dir[i][1];//这个就是纵坐标喽
		if(xx >= 1 && xx <= n && yy >= 1 && yy <= n && !vis[xx][yy] && a[xx][yy] == '#') { // 判断边界以及是否被访问过
			step++;//存此时搜出来的冰淇淋大小
			step1 += mmp (xx, yy);//算一次四周的“.”的个数
			dfs(xx,yy);//递归走起
		}
	}
}
int main()
{
	int maxn = -9999,maxn1 = -9999;//一个存最大的冰淇淋的大小，另一个是“.”
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i <= n + 1; i++){
		a[0][i] = '.';
		a[n + 1][i] = '.';
		a[i][0] = '.';
		a[i][n + 1] = '.';
	}//灵魂代码，把周围的边界全部弄成"." 鸣谢徐大佬的提醒
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if (a[i][j] == '#'){
				step = 1;
				step1 = mmp (i, j);
				dfs(i,j);
				if(maxn < step) maxn = step, maxn1 = step1;//每出一个答案就要比一次，是不是最大
				if(maxn == step)
					if (maxn1 > step1) maxn1 = step1; //同理 同上
			}	
		}
	}
	cout << maxn << ' '<< maxn1 <<endl;
	return 0;//完美结束（So beautiful!!!）
}
```
看完了的老爷们点个赞再走啊~~~

---

## 作者：OnlyU (赞：7)

这道题虽然是蓝题，但十分的水。只要读懂题意就可以发现，这道题就是让我们求最大连通块的面积和周长。面积很简单，就是这个冰激凌球中'#'的数量。而周长我们可以轻而易举地推出是这个冰激凌球中'#'上下左右四个方向‘.’的个数。这样这道题就很好做了。
下为AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maze[1001][1001]= {0},v[1001][1001];
int dx[4]= {-1,1,0,0},dy[4]= {0,0,1,-1};//四个方向 
struct bfc {
	int x,y;
} a,b,c,d;
int ans1,ans2;//ans1是面积，ans2是周长 
void bfs(int sx,int sy) {
	queue<bfc>que;
	a.x=sx;
	a.y=sy;
	int num1=1,num2=0; //num1是面积，num2是周长 
	for(int i=0; i<4; i++) {
		c.x=a.x+dx[i];
		c.y=a.y+dy[i];
		if(maze[c.x][c.y]==-1)
			num2++;
	}
	v[sx][sy]=1;
	que.push(a);
	while(!que.empty()) {
		b=que.front();
		que.pop();
		for(int i=0; i<4; i++) {
			c.x=b.x+dx[i];
			c.y=b.y+dy[i];
			if(c.x>=1&&c.x<=n&&c.y>=1&&c.y<=n&&v[c.x][c.y]==0&&maze[c.x][c.y]==1) {
				num1++;
				v[c.x][c.y]=1;
				for(int j=0; j<4; j++) {
					d.x=c.x+dx[j];
					d.y=c.y+dy[j];
					if(maze[d.x][d.y]==-1)
						num2++;
				}
				que.push(c);
			}
		}
	}
	if(num1>ans1) {
		ans1=num1;
		ans2=num2;
	} else if(num1==ans1) {
		if(num2<ans2) {
			ans2=num2;
		}
	}
	return;
}
void solve() {
	cin>>n;
	for(int i=0; i<=n+1; i++) {
		for(int j=0; j<=n+1; j++) {
			maze[i][j]=-1;
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			char x;
			cin>>x;
			if(x=='#')
				maze[i][j]=1;
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if(maze[i][j]==1&&v[i][j]==0)//每遇到“#”搜一遍 
				bfs(i,j);
		}
	}
	cout<<ans1<<" "<<ans2;
}
int main() {
//	freopen("perimeter.in","r",stdin);
//	freopen("perimeter.out","w",stdout);
	solve();
//	fclose(stdin);
//	fclose(stdout);
}
```


---

## 作者：Schwarzkopf_Henkal (赞：5)

单纯求联通块的一道题，种子填充算法可以简单的解决。

种子填充就不介绍了，这个都不知道还敢做蓝题……

然后是不好搞的求周长部分，对于递归中的每个点，如果周围是未编号节点，大小加一并且进入该点，如果周围是空地，周长加一。

代码很简单，仅供参考。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,siz,len,anss,ansl;//len与siz为当前联通块周长和大小，anss和ansl为最终联通块大小和周长
char inp;
bool pic[1005][1005],mk[1005][1005];//pic数组存储图，mk数组储存某点是否被遍历过
void dfs(int a,int b){
    mk[a][b]=1;
    siz++;
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
            if(abs(i)!=abs(j)){
                if(pic[a+i][b+j]==1&&!mk[a+i][b+j])//如果是个未编号节点，递归进入。
                    dfs(a+i,b+j);
                if(pic[a+i][b+j]==0)//如果是个空节点，周长加一
                    len++;
            }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            cin>>inp;
            if(inp=='#')
                pic[i][j]=1;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(!mk[i][j]&&pic[i][j]){
                siz=0;
                len=0;
                dfs(i,j);
                // cout<<siz<<" "<<len<<'\n';
                if(siz>anss){//对大小和周长做最大值处理
                    anss=siz;
                    ansl=len;
                }
                else if(siz==anss)
                    ansl=min(ansl,len);
            }
    cout<<anss<<' '<<ansl;
}
```
但是，接下来是关键部分。

我们发现当前情况下递归的层数最大达到了$10^6$，虽然洛谷让你过了，可是万一在某些少爷机上突然爆栈了……（爆零的恐惧）

接下来我们学习如何防止在递归过程中爆栈。

在代码开头添加如下片段：
```cpp
#pragma comment(linker, "/STACK:102400000,102400000") 
```
和/或
```cpp
#pragma GCC optimize("no-stack-protector")
```
即可！

### ~~完~~

好吧我们接下来来学习如何手动模拟递归过程以求不使用递归完成dfs。

在数据结构基础上我们学过递归的原理是利用栈空间来完成数据的传输。

然而，这个栈空间的大小（只有几M）远远小于堆空间的大小（总体可调用的在G以上），于是我们手写数据结构把栈移到堆里头。具体实现见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,siz,len,anss,ansl,top;//len与siz为当前联通块周长和大小，anss和ansl为最终联通块大小和周长
pair<int,int> sta[1000005];//Stack! first存储行,second存储列
char inp;
bool pic[1005][1005],mk[1005][1005],lmk[1005][1005][3][3];//pic数组存储图，mk数组储存某点是否被遍历过
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            cin>>inp;
            if(inp=='#')
                pic[i][j]=1;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(!mk[i][j]&&pic[i][j]){
                siz=1;
                len=0;
                int a,b,p;
                sta[++top]=make_pair(i,j);
                mk[i][j]=1;
                while(top){
                    a=sta[top].first;
                    b=sta[top].second;//传入栈中的值
                    p=1;
                    bool flag=0;
                    for(int k=-1;k<=1;k++){
                        for(int l=-1;l<=1;l++)
                            if(abs(k)!=abs(l)){
                                if(pic[a+k][b+l]&&!mk[a+k][b+l]){
                                    sta[++top]=make_pair(a+k,b+l);//这是难点，将递归参数写进栈里面
                                    mk[a+k][b+l]=1;
                                    siz++;
                                    flag=1;//这是难点，如何暂停当前循环并且在完成下层之后使之恢复原状态
                                    break;
                                }
                                if(pic[a+k][b+l]==0&&!lmk[a][b][k+1][l+1]){
                                    len++;
                                    lmk[a][b][k+1][l+1]=1;
                                }
                            }
                        if(flag)
                            break;
                    }
                    if(flag)
                        continue;
                    top--;
                }
                if(siz>anss){//对大小和周长做最大值处理
                    anss=siz;
                    ansl=len;
                }
                else if(siz==anss)
                    ansl=min(ansl,len);
            }
    cout<<anss<<' '<<ansl;
}
```
比直接递归麻烦的不是一点半点，效率上同样有差别，但不是太大。

关键点就是如何暂停当前层的循环并且在完成它的子层循环后使之恢复到原状态。我采取的方法是这样，对于已经处理过的地方打上标记，在处理完子层循环后对于已经标记过的地方不做处理，以使之只处理上一次处理过的位置的下一个。

配上Submit截图：

递归
![递归](https://cdn.luogu.com.cn/upload/image_hosting/t7nz3bht.png)

非递归
![非递归](https://cdn.luogu.com.cn/upload/image_hosting/5bqnpd21.png)

好吧最后说句题外话，对于这些保证需要全部遍历图的的搜索，推荐使用BFS以避免爆栈，然而楼上大佬写过了我就不写了。

推销一下我的博客！本文会在博客园同步更新。
[Blog of Schwarzkopf-Henkal](https://www.cnblogs.com/Schwarzkopf-Henkal/)

#### 完（是真的）

I'm Schwarzkopf Henkal.

---

## 作者：Star1_3st (赞：5)

题目不难，只用BFS就可以AC。第一次我开小了数组RE了（开的1001\*1001，我也不知道为什么RE），第二次就AC了。实现不难。

BFS适用于向多个方向同时扩展，像这种在矩阵中求联通块的问题用BFS思维和代码难度都不高。用DFS多半也可以，但是我懒而且弱，故只写BFS。这类题有一个模板：[求细胞数量](https://www.luogu.org/problem/P1451)。本题相对仅多一个求周长的步骤，也可以用裸BFS解决，还是比较水的。

具体实现上我建了三个数组用于BFS，见代码。求面积详见P1451。求周长时遍历每个点，看它周围有几个空格，并将空格数加入答案。

```cpp
#include<bits/stdc++.h>
int n,max,ans,ax,ay,d=0x7fffffff,book[5001][5001],s[5001][5001],s1[5001][5001],step[5][3]={{0,0,0},{0,0,1},{0,1,0},{0,-1,0},{0,0,-1}};
std::queue<std::pair<int,int> > b;//STL
inline int find(int x,int y)
{
	int dis=0;
	s1[x][y]=0;
	b.push(std::make_pair(x,y));
	while(!b.empty())
	{
		int x1=b.front().first,y1=b.front().second;
		b.pop();
		for(register int i=1;i<=4;i=-~i)
			if(!s[x1+step[i][1]][y1+step[i][2]])
				dis=-~dis;//在此统计周长
		for(register int i=1;i<=4;i=-~i)
			if(s1[x1+step[i][1]][y1+step[i][2]])
			{
				s1[x1+step[i][1]][y1+step[i][2]]=0;
				b.push(std::make_pair(x1+step[i][1],y1+step[i][2]));
			}//同求面积函数的BFS
	}
	
	return dis;
}

inline void Breadth_First_Search(int x,int y)
{
	int res=0,f=find(x,y);//find求周长，这个函数主要负责求面积，顺便统计答案
	book[x][y]=0;
	b.push(std::make_pair(x,y));
	while(!b.empty())
	{
		int x1=b.front().first,y1=b.front().second;
		b.pop();
		res=-~res;
		for(register int i=1;i<=4;i=-~i)
		{
			if(book[x1+step[i][1]][y1+step[i][2]])
			{
				book[x1+step[i][1]][y1+step[i][2]]=0;
				b.push(std::make_pair(x1+step[i][1],y1+step[i][2]));
			}//step是扩展方向，这里向四个方向扩展并统计面积
		}
	}
	
	
	if(res>ans||!(res^ans)&&f<d)
	{
		ans=res;
		ax=x;
		ay=y;
		d=f;
	}//按题目的要求，求出最优解。f是前面求出的周长。
	
	return;
}

int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i=-~i)
		for(register int j=1;j<=n;j=-~j)
		{
			char c;
			scanf("%c",&c);
			while(c=='\n')
				scanf("%c",&c);
			s[i][j]=book[i][j]=s1[i][j]=!(c^'#')?1:0;//赋值，3个数组
		}
		
	for(register int i=1;i<=n;i=-~i)
		for(register int j=1;j<=n;j=-~j)
			if(book[i][j])
				Breadth_First_Search(i,j);//这里枚举每个点，对存在冰激凌的点进行BFS，并在BFS时删去本联通块
	printf("%d %d",ans,d);
	return 0;
}
```

---

## 作者：Sundial (赞：2)

康了一眼，觉得就是DFS就可以了。

首先题目要求最大面积，很好做。我们把图读进来，然后备份一张图。
这张图有什么用呢？我们想啊，我们在一张图上进行查找，找到一个'#'之后，就对它进行DFS，这样就可以在DFS过程中求出面积了，当然为了避免一个联通块内的点被多次DFS，我们对于每个联通块，在DFS之后将其变为 '.' 就可以了。但是我们在进行判断的时候要乱搞一些事，为了避免判断错误，所以我们要备份一张图。而且这种做法不需要特殊考虑联通块内有联通块的情况，所以十分好写。

其次就是周长了，同样很简单，在DFS的时候，我们每到一个点，就在原图上向其四个方向进行搜索，如果有 '.' 就周长++即可。

最后我们把每个联通块的信息储存一下，再排一下序输出就好了。

另外存图的时候一定要从1开始存，这样计算周长时才能正确的将位于边界上的周长计入。

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 7;
int n, cnt;
int a[N][N], s[N][N];
//a[][]是原图,s[][]是要修改的图 
struct ice_cream{//每个冰激凌的信息 
	int s, c;
	bool operator < (ice_cream b) {//重载运算符比较 
		if (s == b.s) return c > b.c;
		return s < b.s;
	}
}t[N * N];//注意数组的大小,最多有N * N个点 
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool in(int x, int y) {
	return 0 <= x && x <= n + 1 && 0 <= y && y <= n + 1;
	//这里判边界的时候要注意,算周长的时候才会正确计数 
}
void dfs(int r, int c) {
	s[r][c] = 0;//修改 
	t[cnt].s++;//面积++ 
	for (int i = 0; i < 4; i++) {
		int nr = r + dx[i];
		int nc = c + dy[i];
		if (in(nr, nc) && !a[nr][nc]) {
			t[cnt].c++;//如果四周有'.'就周长++ 
		}
	}
	for (int i = 0; i < 4; i++) {
		int nx = r + dx[i];
		int ny = c + dy[i];
		if (in(nx, ny) && s[nx][ny] == 1) {
			dfs(nx, ny);//继续DFS 
		}
	}
}
int main () {
	scanf("%d", &n);
	char o;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf(" %c", &o);//读入非空字符要用 空格%c 
			a[i][j] = s[i][j] = o == '#' ? 1 : 0;
			//直接转化为0 1 
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (s[i][j] == 1) {//发现新的冰激凌 
				cnt++;
				dfs(i, j);
			}
		}
	}
	sort(t + 1, t + 1 + cnt);//排序 
	printf("%d %d\n", t[cnt].s, t[cnt].c);
	return 0;
}
```

康了下其它题解，说可能会爆栈，我想可能是因为编译器的锅吧，DEV默认的栈还是比较小的

大家可以打开DEV -> 工具 -> 编译选项 -> 在编译时加入一下命令

粘贴以下代码

-Wl,--stack=67108864  (注意先打个空格)

这是将栈空间改为64MB的意思

感谢观赏

---

## 作者：QHhee004 (赞：2)

		照我的感觉这题考得是搜索，我用的是dfs，bfs也能打.
    
    	思路是，像走迷宫似的记面积，如果所在格子相邻无冰激凌，一个
        就周长++。
     
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,S,C,mx,mi=1e9;//S 面积，C 周长
bool mk[1005][1005],f[1005][1005];//mk有无走过 f 0 无冰激凌 1 有
const int dx[]= {0,1,0,-1},dy[]= {1,0,-1,0};
void dfs(int x,int y) {
	if(!f[x][y]||mk[x][y]) return;//如果没有冰激凌 或走过return
	mk[x][y]=1;
	S++;
	for(int i=0; i<4; i++) {
		if(f[x+dx[i]][y+dy[i]]) dfs(x+dx[i],y+dy[i]);
		else C++;//如果没有被其它冰激凌遮挡
	}
}
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			char a;
			cin>>a;
			if(a=='#') f[i][j]=1;
		}
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(f[i][j]&&!mk[i][j]) {
				S=C=0;//初始化
				dfs(i,j);
				if(S>mx) mx=S,mi=C;//找面积最大
				else if(S==mx) mi=min(C,mi);//找面积最大，周长最小
			}
	cout<<mx<<" "<<mi;
	return 0;
}
```


---

## 作者：hgoicjl (赞：2)

**~~就这么简单一道题，我还硬要用DFS卡过去~~**

**~~我被卡了3天~~**
 
---
### 题意:

给定一个表(可以想象成0 1)

求最多连通的1的个数及周长

若有多个个数相同的连通块，则输出周长最小的那个

---
### DFS基本思想:

对于每个点(也可以是每块冰淇淋) 向四周(上下左右)搜索，遇到 $#$ 则面积++，并且标记(防止多次记录)

遇到 $.$ 表示该个冰淇淋的某一边是边界，周长++

按照要求求出面积最大且周长最小的冰淇淋即可

更详细的思路详见代码

---

为什么DFS我会一直T掉：

~~我也不知道为啥我会写sort函数进去~~

---
### AC Code：
```
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int n,num=0,ices,icec/*记录当前冰淇淋的数据*/,maxices=0,minicec=0/*记录所有冰淇淋中面积最大中周长最小的数据*/;
struct node
{
    int biaoji;
    char m;
}map1[1005][1005];
int side(int i,int j)//用这个函数来判断该条边是否属于周长上的一条边
{
    if(i<1||j<1||i>n||j>n)
        return 1;
    if(map1[i][j].m=='.')
        return 1;
    return 0;
}
int ss(int i,int j)//DFS
{
    if(i<1||j<1||i>n||j>n)//超过边界
        return 0;
    if(map1[i][j].m=='.')//不是冰淇淋
        return 0;
    if(map1[i][j].biaoji!=0)//改点已经处理过
        return 0;
    map1[i][j].biaoji=1;//对当前的冰淇淋标记
    ices++;//面积+1
    ss(i+1,j,1);//DFS向四个方向搜索
    ss(i-1,j,1);
    ss(i,j+1,1);
    ss(i,j-1,1);
    icec+=side(i,j+1);
    icec+=side(i,j-1);
    icec+=side(i+1,j);
    icec+=side(i-1,j);//判断该条边是否属于冰淇淋的周长
    return 0;
}
int main()
{
    ios::sync_with_stdio(false);//快速输入输出
    cin>>n;
    memset(map1,0,sizeof(map1));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>map1[i][j].m;//输入冰淇淋
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)//对每个点都DFS一遍(其实可以更优化)
        {
        	ices=0;
        	icec=0;
            ss(i,j);
            if(ices>maxices)//如果冰淇淋面积更大，直接替换
            {
            	maxices=ices;
            	minicec=icec;
			}
			else if(ices==maxices&&icec<minicec)//面积一样的情况下求周长最小的
            		minicec=icec;
        }
    cout<<maxices<<' '<<minicec<<endl;
    return 0;
}
```

---

## 作者：SUNCHAOYI (赞：2)

# 这是一道经典的搜索题

### 直接看代码（代码里有注释）
```
#include<iostream>
#include<algorithm>
using namespace std;
const int MAX=1000;
struct node
{
	int s=0,c=0;//面积与周长
}ans[MAX*MAX];
int n;char a[MAX][MAX];
void bfs(int i,int j,int k);
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)cin>>a[i][j];
	int k=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(a[i][j]=='#')//如果是#号开始搜索 
			{
				bfs(i,j,k);
				k++;//答案数量+1，用于找最小周长 
			}
		}
	}
	int anss=0,ansc=999999;
	for(int i=0;i<k;i++)
	{
		if(ans[i].s>anss)//更新答案 
		{
			anss=ans[i].s;
			ansc=ans[i].c;
		}
		else if(ans[i].s==anss)ansc=min(ans[i].c,ansc);//取最小的周长 
	}
	cout<<anss<<" "<<ansc<<endl;//输出 
	return 0;
}
void bfs(int i,int j,int k)
{
	ans[k].s++;//面积加一 
	a[i][j]='o';//表示已被访问了
	if(i-1<0)ans[k].c++; if(j-1<0)ans[k].c++; if(i+1>=n)ans[k].c++; if(j+1>=n)ans[k].c++;//如果旁边已经出界（无东西），则周长直接加一 
	if(a[i+1][j]=='.'&&i+1<n)ans[k].c++; if(a[i-1][j]=='.'&&i-1>=0)ans[k].c++; if(a[i][j+1]=='.'&&j+1<n)ans[k].c++; if(a[i][j-1]=='.'&&j-1>=0)ans[k].c++;//没有出界，如果旁边是"."，周长加一 
	//继续往四个方向进行搜索 
	if(i-1>=0&&a[i-1][j]=='#')bfs(i-1,j,k);
	if(i+1<n&&a[i+1][j]=='#')bfs(i+1,j,k);
	if(j-1>=0&&a[i][j-1]=='#')bfs(i,j-1,k);
	if(j+1<n&&a[i][j+1]=='#')bfs(i,j+1,k);
}
```


---

## 作者：Polarnova (赞：2)

可以不用搜索，考虑建立一个并查集，按顺序遍历并维护同一连通块的信息。   
注意 合并点 和合并 点的信息 的顺序之类的细节。
```cpp
#include<cstdio>
#include<iostream>

int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
int n,tot,m[1003][1003],edge[1000009],fa[1000009],area[1000009],maxarea,minedge=0x3f3f3f3f;

int get(int x) {return ((x==fa[x])?x:fa[x]=get(fa[x]));}
void merge(int x,int y) {fa[get(x)]=get(y);}

int main() {
	scanf("%d\n",&n);
	char ch;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			scanf("%c",&ch);
			if(ch=='#')m[i][j]=++tot;
		}
		if(ch==EOF)break;
		getchar();
	}
	for(int i=1,n2=n*n;i<=n2;i++){fa[i]=i;area[i]=1;}
	for(int x=1;x<=n;x++) {
		for(int y=1;y<=n;y++) {
			if(m[x][y]==0)continue;
			for(int p=0;p<2;p++) {
				if(m[x+dx[p]][y+dy[p]]==0)continue;
				if(get(m[x+dx[p]][y+dy[p]])!=get(m[x][y])) {	
					area[get(m[x][y])]+=area[get(m[x+dx[p]][y+dy[p]])];
					edge[get(m[x][y])]+=edge[get(m[x+dx[p]][y+dy[p]])];
					merge(m[x+dx[p]][y+dy[p]],m[x][y]);
				}
			}
			int edgex=4;
			for(int p=0;p<4;p++) if(m[x+dx[p]][y+dy[p]])edgex--;
			edge[get(m[x][y])]+=edgex;
			if(maxarea<area[get(m[x][y])]) {
				maxarea=area[get(m[x][y])];
				minedge=edge[get(m[x][y])];
			} else if(maxarea==area[get(m[x][y])]) {
				minedge=std::min(edge[get(m[x][y])],minedge);
			}
		}
	}
	printf("%d %d\n",maxarea,minedge);
	return 0;
}
```

---

## 作者：天南地北 (赞：2)

#### 这道题其实不难，纯搜索

这道题很明显是BFS，但是可能有人是利用DFS卡过。

虽然可以卡过，但是我们需要对BFS的写法进行复习，新学BFS的蒟蒻来挑战一下自己。

DFS和BFS模板我就不写了,做这道题的一般都是学过搜索的，但是**求周长和面积**我还是会简单讲一下。

#### 整体想法：

1、全图寻找#号，保证之前的搜索里没有搜索过当前的点

2、找到点后，对这个点进行DFS或BFS

#### 求面积

一般来说，求面积一般是在搜索里找到题目特定的一些符号，然后拿个变量统计罢了

#### 求周长

通过题目样例，其实我们能发现，对于当前这个点，只需要看周围有多少个点号就好了，注意，周围指的是上、下、左、右。

#### 这是我的程序：

```cpp
//防伪标识（MKM_K神）
#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=1000+10;
const int dx[4]={0,0,-1,+1};
const int dy[4]={-1,+1,0,0};//这是四个方向
int n,m,S,L;
char ch;
int s[maxn][maxn];
int map[maxn][maxn];
int minx,miny,maxx,maxy;
int maxS,maxL;
struct data
{
	int x,y,t;
}queue[maxn*maxn];
int BFS(int x,int y)//BFS，一般来说使用void的，但是这里是为了得到i,j这一片的面积，所以使用了int类型
{
	int head=0,tail=1,ans=1,nx,ny,nt;
	queue[0].x=x,queue[0].y=y,queue[0].t=1;
	map[x][y]=1;
	L+=4-(s[x-1][y]+s[x+1][y]+s[x][y-1]+s[x][y+1]);//起始点的周长，不要忘记算
	while(head!=tail)//循环队列
	{
		for(int i=0;i<4;i++)//四种方向全都搜
		{
			nx=queue[head].x+dx[i],ny=queue[head].y+dy[i];
			nt=queue[head].t+1;//以x,y点移动后能地点，nt是手残写的，只是一些题在搜索的后，要求最短时间才会写
			if(nx<1||nx>n||ny<1||ny>n||map[nx][ny]||!s[nx][ny])continue;//这个点越界了，别搜了，会死循环的。
			ans++;//这个点符合要求，方案数增加
			map[nx][ny]=true;//标记这个点已加到队列，我已经搜过
			L+=4-(s[nx-1][ny]+s[nx+1][ny]+s[nx][ny-1]+s[nx][ny+1]);//求此点周长
			queue[tail].x=nx,queue[tail].y=ny,queue[tail].t=nt;//相关信息存入队列
			tail++;
			tail%=10000000;//循环队列，队列尾往后移动
		}
		head++;
		head%=10000000;//循环队列，弹出一个点，因为已经这个店搜索过了
	}
	return ans;//返回这个点的答案
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
        	cin>>ch;
        	if(ch=='#')s[i][j]=1;
        }//转数值
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
        	if(!map[i][j]&&s[i][j])//保证我能搜索，并且此次搜索不乱花时间（即没有搜索过）
        	{
        		S=0,L=0;//初始化
        		S=BFS(i,j);//得到答案
        		if(S>maxS||S==maxS&&L<maxL)maxS=S,maxL=L;//找最好答案
        	}
        }
    cout<<maxS<<" "<<maxL;//输出答案
    return 0;
}

```
若有问题的，请私信我，我会及时改正，谢谢每一个看我题解的人

希望大家向我一样，一写就AC。

---

## 作者：Priori_Incantatem (赞：1)

### 题目大意
给出一个由`.`和`#`组成的二维矩阵，每一个连通块都有一个面积 和 周长，求面积最大的连通块的面积和周长，若有多个面积一样大的，输出周长最小的那个

根据题意，我们需要求出每个连通块的面积和周长，面积就不用说了，难点在求周长  
我们使用bfs，设当前出队的点为$x$。在点$x$向四周寻找遍历的下一个点$y$时，若$y$不是冰淇淋格或者在地图之外，说明点$x,y$之间的缝隙是连通块的边缘，所以周长++  
若冰淇淋含有洞，以上方法仍然适用
```cpp
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
const int Maxn=1010,inf=0x3f3f3f3f;
const int dx[]={1,-1,0,0},dy[]={0,0,-1,1};
bool a[Maxn][Maxn],vis[Maxn][Maxn];
int n,ans,tot=inf;
struct node{
	int x,y;
	node(int u,int v)
	{
		x=u,y=v;
	}
};
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
bool check(int x,int y)
{
	return x<1 || y<1 || x>n || y>n || a[x][y];
}
void bfs(int sx,int sy)
{
	queue <node> q;
	vis[sx][sy]=1;
	int size=0,cir=0;  // 维护面积和周长
	q.push(node(sx,sy));
	while(q.size())
	{
		int x=q.front().x,y=q.front().y;
		q.pop();
		size++;
		for(int i=0;i<4;++i)
		{
			int u=x+dx[i],v=y+dy[i];
			if(check(u,v)){cir++;continue;}
			if(vis[u][v])continue;
			vis[u][v]=1;
			q.push(node(u,v));
		}
	}
	if(size>ans || (size==ans) && cir<tot)
	ans=size,tot=cir;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("perimeter.in","r",stdin);
//	freopen("perimeter.out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
	{
		char ch;
		cin>>ch;
		if(ch=='.')a[i][j]=1;
		else a[i][j]=0;
	}
	
	for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
	if(!vis[i][j] && !a[i][j])bfs(i,j);
	
	printf("%d %d\n",ans,tot);
	
	return 0;
}
```

---

## 作者：ez_lcw (赞：1)

# dfs

看大家有广搜，有并查集，没人用深搜，蒟蒻就只能来个深搜了。

**思路很简单：每一次找到还没搜索过的'#'（冰淇淋），开始深搜，遇到'.'（空地）就回溯。**

**计算面积的实现：每搜索到一个节点，面积++。**

**计算周长的实现：每搜到一个节点，寻找它的上下左右，某个方向是'.'（空地），周长++（证明这个方向是冰淇淋的边界了）。**

对于面积与周长的存储，我是用$pair<\text{面积}\ ,\text{周长}>$实现的。

具体代码如下：

```cpp
#include<bits/stdc++.h>

#define N 1001

using namespace std;

int n;
int fx[]={-1,0,1,0},fy[]={0,1,0,-1};
bool vis[N][N];
char ch[N][N];

pair<int,int>ans(0,0);//记得初始化

bool right(int x,int y)//判断边界
{
	return x>=1&&x<=n&&y>=1&&y<=n;
}

pair<int,int> dfs(int x,int y)
{
	vis[x][y]=true;
	pair<int,int>ans(1,0);
	for(int i=0;i<4;i++)
	{
		int xi=x+fx[i];
		int yi=y+fy[i];
		if(vis[xi][yi])continue;//如果访问过了（也就是这个点是它粑粑），我们就continue
		if(right(xi,yi)&&ch[xi][yi]=='#')
		{
			pair<int,int>now=dfs(xi,yi);//继续深搜
			ans.first+=now.first;
			ans.second+=now.second;
		}
		else ans.second++;//否则就将边长++
	}
	return ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%s",ch[i]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(!vis[i][j]&&ch[i][j]=='#')
			{
				pair<int,int>p=dfs(i,j);
				if(p.first>ans.first)ans=p;//取最优解
				else if(p.first==ans.first)ans.second=min(p.second,ans.second);
			}
		}
	}
	printf("%d %d\n",ans.first,ans.second);
	return 0;
}
```

---

## 作者：zylll (赞：1)

一个大广搜。表示并没有用并查集做qwq，可以过。

至于联通快的个数，比较简单。

至于周长，我们只需要设置一个变量初值为4，然后循环一遍，判断一下周围是否有块，如果有，那么这条边只对面积有贡献；反之则对两个都有益，最后多关键字排序输出即可。

```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>
#include <algorithm>
static const int MAXN=1005;
static const int dirx[5]={-1,1,0,0};
static const int diry[5]={0,0,-1,1};
using namespace std;
struct node
{
    int m,z;
}s[MAXN*MAXN];
struct node1
{
    int x,y;
}q[MAXN*MAXN];
int n,cnt,head,tail;
bool b[MAXN][MAXN],vis[MAXN][MAXN];
char a[MAXN][MAXN];
inline bool cmp(node a,node b)
{
    if(a.m==b.m) return a.z<b.z;
    return a.m>b.m;
}
inline bool check(int x,int y){return x<1||x>n||y<1||y>n?true:false;}
inline void bfs(int x,int y)
{
    vis[x][y]=true;
    cnt++;
    head=tail=0;
    q[head]=(node1){x,y};
    while(head<=tail)
    {
        node1 now=q[head];
        s[cnt].m++;
        int num=4;
        for(int i=0;i<4;i++) if(b[now.x+dirx[i]][now.y+diry[i]]) num--;
        s[cnt].z+=num;
        for(int i=0;i<4;i++)
        {
            int dx=now.x+dirx[i],dy=now.y+diry[i];
            if(vis[dx][dy]||check(dx,dy)||!b[dx][dy]) continue;
            vis[dx][dy]=true;
            q[++tail]=(node1){dx,dy};
        }
        head++;
    }
}
int main()
{
    freopen("perimeter.in","r",stdin);
    freopen("perimeter.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",a[i]+1);
        for(int j=1;j<=n;j++) if(a[i][j]=='#') b[i][j]=true;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
          if(!vis[i][j]&&b[i][j]) bfs(i,j);
    }
    sort(s+1,s+cnt+1,cmp);
    printf("%d %d\n",s[1].m,s[1].z);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```
[分享一波自己的博客qwq，USACO 2019 January Contest, Silver](https://beyondlimits.site/1118.html)

---

## 作者：亚由亚由 (赞：1)

仔细读题后可以发现:

显然可以把每一个#向四周的#建一条边,然后把每一个块的面积dfs
~~(我一开始还写的tarjan)~~
处理出来,
再找周长.

而且找周长也只要全部遍历一遍,遇到一个#,就看它的前后左右,有一个不是#就把它所在的块周长++即可.

Code:
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm> 
using namespace std;
int n,m,qwq[1000005],QAQ,tot,cnt,h[1000005],b[1000005],s,k[1000005],mx,C[1000005],an=0x7fffffff,dfn[1000005],low[1000005],v[1000005];
char c[1005][1005];
struct ll
{
	int nx;
	int to;
}a[8000005];
void ad(int x,int y)
{
	a[++cnt].nx=h[x];
	a[cnt].to=y;
	h[x]=cnt;
}
void dfs(int x)
{
	int i,j;
	++k[tot];//每个块的面积
	b[x]=tot;//每个#所在的块
	v[x]=1;
	for(i=h[x];i;i=a[i].nx)
	{
		j=a[i].to;
		if(v[j])
		continue;
		dfs(j);
	}
}
int main()
{
	int i,j,x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
	scanf("%s",c[i]+1);
	for(i=1;i<=n;++i)
	for(j=1;j<=n;++j)
	if(c[i][j]=='#')
	{
		qwq[(i-1)*n+j]=++QAQ;//给每一个#编号同时记录
		if(c[i-1][j]=='#'&&i-1)
		{//每一个#只需看它左和上的点建双向边
			ad(qwq[(i-2)*n+j],QAQ);
			ad(QAQ,qwq[(i-2)*n+j]);
		}
		if(c[i][j-1]=='#'&&j-1)
		{
			ad(qwq[(i-1)*n+j-1],QAQ);
			ad(QAQ,qwq[(i-1)*n+j-1]);
		}
	}
	for(i=1;i<=QAQ;++i)//dfs找每一个块的点
	if(!v[i])
	{
		++tot;
		dfs(i);
		mx=max(mx,k[tot]);//最大面积
	}
	for(i=1;i<=n;++i)
	for(j=1;j<=n;++j)
	if(c[i][j]=='#')
	{
		if(c[i-1][j]!='#')//求周长
		++C[b[qwq[(i-1)*n+j]]];
		if(c[i+1][j]!='#')
		++C[b[qwq[(i-1)*n+j]]];
		if(c[i][j-1]!='#')
		++C[b[qwq[(i-1)*n+j]]];
		if(c[i][j+1]!='#')
		++C[b[qwq[(i-1)*n+j]]];
	}
	for(i=1;i<=tot;++i)
	if(k[i]==mx)
	an=min(an,C[i]);
	printf("%d %d",mx,an);
	return 0;
}
```


---

## 作者：hetangxin (赞：0)

一道搜索题，我用的广搜过的，思路很简单，for循环遍历每个点，如果是‘#’并且没有被搜索过，则入队搜索一遍，每次能搜到一个联通的‘#’则面积加1，周长则再用一个for循环来判断边界，如果为‘.’则周长加1.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 7;
struct Node{
	int x, y;
	Node(int xx = 0, int yy = 0) {
		x = xx, y = yy;
	}
};
int n;
queue<Node> q;
char Map[MAXN][MAXN];
int vis[MAXN][MAXN];
int dx[5] = {1, -1, 0, 0, 0};
int dy[5] = {0, 0, 1, -1, 0};
pair<int, int> ans;
pair<int, int> bfs() {
	ans.first = ans.second = 0;
	while(!q.empty()) {
		Node now = q.front();
		q.pop();
		for(int i = 0; i < 5; ++i) {
			int fx = now.x + dx[i];
			int fy = now.y + dy[i];
			if(fx >= 1 && fx <= n && fy >= 1 && fy <= n && Map[fx][fy] != '.' && !vis[fx][fy]) {
				++ans.first;
				for(int i = 0; i < 5; ++i) {
					int x = fx + dx[i];
					int y = fy + dy[i];
					if(Map[x][y] == '.' || x > n || y > n || x < 1 || y < 1) {
						++ans.second;
					}
				}
				q.push(Node(fx, fy));
				vis[fx][fy] = 1;
			}
		}
	}
	return ans;
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			cin >> Map[i][j];
		}
	}
	pair<int, int> res, tmp;
	res.first = 0, res.second = 0x3f3f3f3f;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(Map[i][j] == '#' && !vis[i][j]) {
				while(!q.empty()) {
					q.pop();
				}
				q.push(Node(i, j));
				tmp = bfs();
				if(tmp.first >= res.first) {
					if(tmp.first == res.first) {
						if(tmp.second <= res.second) {
							res = tmp;
						}
					}
					else {
						res = tmp;
					}
				}
			}
		}
	}
	cout << res.first << ' ' << res.second << endl;
	return 0;
}
```

---

