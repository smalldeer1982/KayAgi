# Igor In the Museum

## 题目描述

Igor is in the museum and he wants to see as many pictures as possible.

Museum can be represented as a rectangular field of $ n×m $ cells. Each cell is either empty or impassable. Empty cells are marked with '.', impassable cells are marked with '\*'. Every two adjacent cells of different types (one empty and one impassable) are divided by a wall containing one picture.

At the beginning Igor is in some empty cell. At every moment he can move to any empty cell that share a side with the current one.

For several starting positions you should calculate the maximum number of pictures that Igor can see. Igor is able to see the picture only if he is in the cell adjacent to the wall with this picture. Igor have a lot of time, so he will examine every picture he can see.

## 样例 #1

### 输入

```
5 6 3
******
*..*.*
******
*....*
******
2 2
2 5
4 3
```

### 输出

```
6
4
10
```

## 样例 #2

### 输入

```
4 4 1
****
*..*
*.**
****
3 2
```

### 输出

```
8
```

# 题解

## 作者：black_trees (赞：5)

### 这题难点不在搜索，而是读题……
-----

我先解读一下题目意思：

给你一个 $n\times m$ 的矩阵。

对于每次询问。输出所询问点所在联通块的**所有** `.` 周围的 `*` 个数。

看到没有？是所有！举个例子：

~~~
* * * *
* . . *
* . * *
* * * *

~~~

我们如果只看**整个**联通块周围的 `*` 的话……

那就只有 $7$ 个 `*` 了。

但是，我们很明显的看到：样例 $2$ 里面，最后的答案是 $8$ ！

仔细的读了一下英文题面之后，我发现：

这一道题实际上要求的是联通块里所有 `.` 的周围有的 `*` 的个数！

是不是还是有点昏？

简单的来说：

每访问到一个 `.` ，我们都需要在它四个方向上查找 `*` ，也就是可以有**重复**的计算！。

很好，现在大家应该可以读懂这道题了。

重新回到刚刚的样例：

~~~
* * * *
* . . *
* . * *
* * * *

~~~

这时候，我们已经可以明显的发现：

联通块右上方的 `.` 和左下方的 `.` 是有重复的 `*` 出现的。

我现在把这个重复的 `*` 改成 `@` 。

~~~
* * * *
* . . *
* . @ *
* * * *

~~~

清楚了么？

-------

那现在，我们只需要在每次询问时搜出询问位置所在的联通块，然后把这个联通块里所有元素的周围走一遍。

访问到 `*` 的时候计数器++就可以了。

(具体代码实现就不细说了，这有很多种实现方法，我的代码放上来简单讲讲实现（见代码的注释）) 。

[AC record](https://www.luogu.com.cn/record/35492193)

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int si=1006;//数组大小不解释

int n,m,k;
int tmp=0;
int ans[si*si];//这里ans数组用来存储答案，我的做法是用一维数组来储存，直接用pre数组的下标来访问，所以要开n^2的空间
int pre[si][si];//
char d[si][si];//地图，不解释
int dx[]={0,0,0,1,-1};
int dy[]={0,-1,1,0,0};//方向数组，不解释

void dfs(int x,int y){//深搜
	pre[x][y]=tmp;//tmp表示第tmp次询问（区分答案用的）
	for(register int i=1,nx,ny;i<=4;++i){
		nx=x+dx[i];
		ny=y+dy[i];
		if(nx<1||ny<1||nx>n||ny>m){
			continue;
		}//边界，搜出去就continue掉
		if(pre[nx][ny]){
			continue;
		}//如果pre数组被修改过了（已经有答案储存在ans数组了），那也continue掉
		if(d[nx][ny]=='*'){
			ans[tmp]++;
		}//搜到*，计数器+（答案）+
		else{
			dfs(nx,ny);//继续递归搜索
		}
	}
}

int sx;
int sy;//开始的坐标。

int main(){
	cin>>n>>m>>k;
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=m;++j){
			cin>>d[i][j];
		}
	}
	for(register int i=1;i<=k;++i){
		cin>>sx>>sy;
		tmp++;//tmp只是一个区分答案的指针罢了
		if(!pre[sx][sy]){
			dfs(sx,sy);
		}//pre没有被修改过，也就是说它之前还没搜过，搜一遍。（如果之前搜过，那ans里一定会有答案，直接输出就好了）
		cout<<ans[pre[sx][sy]]<<endl;//输出
	}
	return 0;
}
```


本蒟蒻写题解是为了让自己和别人能更好理解题目，管理员大大求过QAQ

---

## 作者：durex_com (赞：5)

# 纯搜索
题意：
就是询问当前点所在的联通块，可以拍多少张照（墙，能拍的只能是四周的）。

运用了时间戳存答案的优化，感觉效果不是一般的好。

具体做法看代码就懂了。

很简单。

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
int ans[1001*1001],map[1001][1001],vis[1001][1001];
int dir1[4]={0,1,-1,0};
int dir2[4]={1,0,0,-1};
int n,m,q;
int xx,yy;
int tro=0;
int check(int x,int y)
{
	return x>=0&&x<=n&&y>=0&&y<=m;
}
int sum=0;
void dfs(int x,int y)
{
	vis[x][y]=tro;
	for(int i=0;i<4;i++)
	{
		xx=x+dir1[i];
		yy=y+dir2[i];
		if (check(xx,yy)&&!vis[xx][yy])
		{
		if (map[xx][yy]==1) sum++;
		else {dfs(xx,yy);}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	char c;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{	
	   cin>>c;
	   if (c=='*') map[i][j]=1;
	}
	int a,b;
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		if (ans[vis[a][b]]) printf("%d\n",ans[vis[a][b]]);
		else {tro++;sum=0;dfs(a,b);ans[tro]=sum;printf("%d\n",sum);}
	}
}
```

---

## 作者：Tyyyyyy (赞：3)

# 翻译又又又又又坑死了人
这题真正的坑点在于理解题意。
翻译告诉我们：求“.”的连通块周围有多少个‘*’。
### 于是就会产生这样的经典错解：
dfs函数里标记了查过的‘*’，不再重复查。
然后你就会发现样例都过不了并很疑惑......
### 我们来仔细的读一下原文！
本题原意是：一个人到博物馆里看画，‘.’表示可以走的房间，‘*’表示墙。每面墙上贴有一幅画，现在给出这个人的位置，求他最多看到多少幅画？
### 也就是说——这里的‘*’可以重复计算！！！
那么这题就很简单了：对于每个查找数据，通过dfs不断扩展连通块，每扩展一个，便计数它四周所有的‘*’。
## AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,vis[1001][1001],ans[1001001],sum,mp[1001][1001];
int dx[4]={0,0,1,-1};//方向数组
int dy[4]={1,-1,0,0};
bool can(int a,int b)//封装一个函数，判断是否越界
{
	if(a>=0&&b>=0&&a<=n&&b<=m)return 1;
	return 0;
}
void dfs(int a,int b)//深搜
{
	vis[a][b]=1;//已经搜过的‘.’做标记
	for(int i=0;i<4;i++)//向每个方向搜索
	{
		int na=a+dx[i],nb=b+dy[i];
		if(!vis[na][nb]&&can(na,nb))
		{
			if(mp[na][nb]==1)sum++;//如果是‘*’计数
			else dfs(na,nb);//若是‘.’继续搜索
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	char l;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>l;//字符类型的读入还是cin比较保险
			if(l=='*')mp[i][j]=1;
		}
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&x,&y);
		if (ans[vis[x][y]]) printf("%d\n",ans[vis[x][y]]);//如果之前已经查过该点则直接输出省时间
		else
        	{
            		sum=0;//计数
                	dfs(x,y);//搜索
                    	ans[t]=sum;//存储结果
                        printf("%d\n",sum);//每次输出答案（记得换行！）
                 }
	}
	return 0;
}
```


---

## 作者：L7_56 (赞：1)

要找出题目给定的连通块周围有多少个'*'

但是这题有点特殊

看一下原题的背景可以发现，这题找的是博物馆中的展品个数

可以想象一下，人站在同一个位置，向四个方向看，如果有墙就会有一个藏品

所以在本题中需要对每一个遍历的点的四个方向搜索一次，有墙计数器就要加一

也就是**可以重复**

另外由于有多组数据，需要用一个数组存储结果，免得每一次都重新搜

直接全部预处理应该也是可以的，没试过

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;

int n,m,k;
char mp[1010][1010];
int ans[1010][1010];
bool vis[1010][1010];

int xx[]={1,0,-1,0};
int yy[]={0,1,0,-1};

queue<int>q[2];
queue<int>p[2];
void bfs(int sx,int sy){
	q[0].push(sx);q[1].push(sy);
	p[0].push(sx);p[1].push(sy);
	vis[sx][sy]=1;
	int sum=0;
	while(!q[0].empty()){
		int dx=q[0].front();
		int dy=q[1].front();
		q[0].pop();q[1].pop();
		for(int k=0;k<4;++k){
			int cx=dx+xx[k];
			int cy=dy+yy[k];
			if(cx<1||cx>n||cy<1||cy>m||vis[cx][cy]) continue;
			if(mp[cx][cy]=='*') sum++;
			else{
				q[0].push(cx);q[1].push(cy);
				p[0].push(cx);p[1].push(cy);
				vis[cx][cy]=1;
			}
		}
	}
	while(!p[0].empty()){
		int dx=p[0].front();
		int dy=p[1].front();
		ans[dx][dy]=sum;
		p[0].pop();p[1].pop();
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i=1;i<=n;++i){
		getchar();
		for(int j=1;j<=m;++j)
	 	 mp[i][j]=getchar();
	}
	for(int i=1;i<=k;++i){
		int fdx,fdy;
		scanf("%d%d", &fdx, &fdy);
		if(!ans[fdx][fdy]) bfs(fdx,fdy);
		printf("%d\n", ans[fdx][fdy]);
	}
	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给出一个 $n \times m$ 的长方形，‘$.$’表示空地，‘$*$’表示不可走到的地方。每个空地旁如果连着不可走到的地方则挂着一副画，给出多个坐标 $(x,y)$，每次回答通过移动至相邻空地，最多能看到多少幅画。

## 思路

把题面大概翻译一下就是要你先找到坐标 $(x,y)$ 所在的连通块，然后看这个连通块里的每个点旁有多少个‘$*$’，求出总和即可。注意每个‘$*$’可能会被计算多次，但并不需要删去，因为是在这个格子的不同面上，要特别小心这一点！

由于问题的坐标个数可能达到 $10^5$，因此对于每一个询问我们都需要在 $O(1)$ 的时间内进行解答。因此除了简单的搜索，我们还需要做一些记录。

bfs 记忆化搜索，找出每一个连通块，对于每一个连通块，我们都要求出那个连通块里画的数量，我们可以边找边计算，对于每一次找到一个新的点，都加上其四周画的数量，将其存入 $size$ 数组里面，然后，我们把每一个连通块用 $id$ 数组，都标记成同一个数字，这样 $size_i$ 就表示编号为 $i$ 的点所在的连通块的画的幅数。

输出时，对于每次给出的坐标 $(x,y)$，那么 $id[x][y]$ 就是其所在连通块的编号，因此直接可以输出 $size[id[x][y]]$ 就是答案了。

## 代码

接下来放上我的代码，标准的搜索。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
int n,m,k,cnt=1,id[1005][1005],sz[1000000];
int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
char a[1005][1005];
void bfs(int x,int y){
    queue<pii>q;
    q.push(make_pair(x,y));
    int sum=0;
    for(int i=0;i<4;i++){
	if(a[x+dx[i]][y+dy[i]]=='*')sum++;
    }
    id[x][y]=cnt;
    while(!q.empty()){
	pii p=q.front();
	q.pop();
	for(int i=0;i<4;i++){
	    int r=p.first+dx[i],c=p.second+dy[i];
            if(r>n||c>m||r<1||c<1||a[r][c]!='.'||id[r][c]!=0)continue;
	    for(int j=0;j<4;j++){
		if(a[r+dx[j]][c+dy[j]]=='*')sum++;
	    }
            id[r][c]=cnt;
            q.push(make_pair(r,c));
	}
    }
    sz[cnt]=sum;
    cnt++;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++)cin>>a[i][j];
    }
    for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
	    if(a[i][j]=='#')id[i][j]=-1;
	}
    }
    for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
	    if(a[i][j]=='.'&&id[i][j]==0)bfs(i,j);
	}
    }
    for(int i=1;i<=k;i++){
	int x,y;
	cin>>x>>y;
	cout<<sz[id[x][y]]<<"\n";
    }
    return 0;
}
```


---

## 作者：pengzy (赞：0)

前言：此题翻译真的是非常令人感动（

### 题意：

有一个 $n\times m$ 的地图和 $k$ 次询问。每次询问给你一个坐标为 $(x,y)$ 的 “.” ，需要你求出 **这个点所在的联通块中所有 $.$ 周围 $*$ 的个数**。

### 思路：

朴素想法就是对于每一次询问，让此点去跑一次 $dfs$。$dfs$ 的规则就是如果周围的点是 $ * $ 就累计一下，否则就说明周围那个点是 $.$，让他接着 $dfs$ 递归。

上述做法的结果应该是超时的，考虑优化。

可以用一个数组记录 **已经搜索过的联通块的答案**，用一个变量记录这是第几次询问时的答案。如果接下来重复输入了一次该数据，则直接输出记录好的答案，不用再跑一遍暴力 $dfs$ 了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
const int MAX=1005;
int n,m,k,cnt=0,vis[MAX][MAX],ans[MAX*MAX],a[MAX][MAX];
//cnt 记录是第几次询问的 x,y 答案，vis 标记走没走过，ans 记录答案，a 表示能不能走
int dx[4]={0,0,+1,-1},dy[4]={+1,-1,0,0};
char c;
bool check(int a,int b)
{
	return a>=1&&a<=n&&b>=1&&b<=m;
}
void dfs(int x,int y)
{
	vis[x][y]=cnt;//标记为走过的同时记录这是第几次询问走过的
	for(int i=0;i<4;i++) {
		int xx=x+dx[i],yy=y+dy[i];
		if(!vis[xx][yy]&&check(xx,yy))
			if(!a[xx][yy])ans[cnt]++;//计数
			else dfs(xx,yy);
	}
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++) {
	        cin>>c;
	        if(c=='.')a[i][j]=1;
	    }
	for(int i=1,x,y;i<=k;i++) {
		x=read(),y=read();
		cnt++;//每一次询问结束记录是第几次询问的变量要加一
		if(!vis[x][y])dfs(x,y);
		cout<<ans[vis[x][y]]<<endl;
	}
	return 0;
}
```

有什么不会的欢迎在下方评论，我一定会回复的。

---

## 作者：hxhhxh (赞：0)

## 大意

给定一个只有`.`，`*`的矩阵，有 $ m $ 个查询操作，询问

$$ \sum_{(i,j)\text{与}(x_i,y_i)\text{联通}} (i,j)\text{上下左右的}*\text{数} $$

## 思路

首先，查询是针对整个连通块进行的，所以可以考虑并查集。 
$ \tiny{\text{二维的并查集很烦人。}} $

然后，这道题可以重复计算单个`*`，所以不用考虑算重的问题。又因为单个 $ (i,j) $ 上下左右的`*`数很好统计，所以可以用带权并查集。 $ \tiny{\text{二维的带权并查集更烦人了！}} $

每一次遇到两个相邻的`.`，将两个连通块合并。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,sid[1005][1005];
char ch[1005][1005];
struct st{
    int x,y;
    bool operator==(const st&b)const{
		return x==b.x&&y==b.y;
	}
}f[1005][1005],p;
st find(st x){
	if(x==f[x.x][x.y]) return x;
	return f[x.x][x.y]=find(f[x.x][x.y]);
}
void mrg(int ax,int ay,int bx,int by){
    st aa=find(f[ax][ay]),bb=find(f[bx][by]);
    if(aa==bb) return;
    f[bb.x][bb.y]=aa;
    sid[aa.x][aa.y]+=sid[bb.x][bb.y];
    sid[bb.x][bb.y]=0;
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) scanf("%s",ch[i]+1);
    for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
	        f[i][j]=(st){i,j};
	        if(ch[i][j]=='*') continue;
	        if(ch[i-1][j]=='*') sid[i][j]++;
	        if(ch[i+1][j]=='*') sid[i][j]++;
	        if(ch[i][j-1]=='*') sid[i][j]++;
	        if(ch[i][j+1]=='*') sid[i][j]++;
	        if(ch[i-1][j]=='.') mrg(i-1,j,i,j);
	        if(ch[i][j-1]=='.') mrg(i,j-1,i,j);
	    }
	}
    for(int i=1;i<=k;i++){
        scanf("%d %d",&p.x,&p.y);
        p=find(p);
        printf("%d\n",sid[p.x][p.y]);
    }
    return 0;
}
```

---

## 作者：TLMPEX (赞：0)

这道是个dfs搜索题，题意楼上说的很清楚了，就不在多说了，思路详见代码。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
char r[1001][1001];
int vis[1001][1001],s[1000001];
int a[4]={-1,0,0,1},b[4]={0,-1,1,0};//方向
int dfs(int x,int y,int z){
	vis[x][y]=z;//表示（x,y）是第z个连通块里的一个
	for(int i=0;i<4;i++){
		int nx=x+a[i],ny=y+b[i];//下一步将要走的位置
		if(r[nx][ny]=='.'&&!vis[nx][ny])
			dfs(nx,ny,z);//如果可以走，就搜下一个位置
		else if(r[nx][ny]=='*')s[z]++;//如果是“*”，则第z个连通块周围的“*”数加一
	}
}
int main(){
	int i,j,x,y,z=1;
	cin>>n>>m>>k;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			cin>>r[i][j];
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(!vis[i][j]&&r[i][j]=='.'){
				dfs(i,j,z);//编号
				z++;
			}
	for(i=1;i<=k;i++){
		cin>>x>>y;
		cout<<s[vis[x][y]]<<endl;//输出
	}
}
```


---

## 作者：Timon080923 (赞：0)

我们可以给每一个连通块上色，并且求每个连通块周围'\*'数量。  
用一个dfs可以遍历连通块，完成以上两个操作。  
这样输出时就可以直接调用数组。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,dx[]={0,-1,0,1},dy[]={-1,0,1,0},u,f[1002][1002],v[1000002],x,y;
string s[1002];
int dfs(int i,int j,int u){//求连通块周围'*'的数量 
	if(s[i][j]=='*'||f[i][j])return 0; 
	f[i][j]=u;//填色 
	int g=0;
	for(int k=0;k<4;k++)g+=s[i+dx[k]][j+dy[k]]=='*';//'*'的数量 
	for(int k=0;k<4;k++)g+=dfs(i+dx[k],j+dy[k],u);//遍历连通块 
	return g;
}
int main(){
	cin>>n>>m>>k;
	for(int i=0;i<n;i++)cin>>s[i];
	for(int i=0;i<n;i++){//预处理 
		for(int j=0;j<m;j++){
			if(s[i][j]=='.'&&!f[i][j]){//新的连通块 
				u++;//新颜色 
				v[u]=dfs(i,j,u);//求连通块周围'*'的数量 
			}
		}
	}
	while(k--){
		cin>>x>>y;
		cout<<v[f[x][y]]<<endl;//该颜色连通块周围'*'的数量 
	}
	return 0;
}
```
谢谢观赏！

---

