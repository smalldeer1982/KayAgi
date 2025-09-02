# 油田 Oil Deposits

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=513

[PDF](https://uva.onlinejudge.org/external/5/p572.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/ce90a5dd1ff852d09612a3d726a859f2f238d409.png)

## 样例 #1

### 输入

```
1 1
*
3 5
*@*@*
**@**
*@*@*
1 8
@@****@*
5 5
****@
*@@*@
*@**@
@@@*@
@@**@
0 0```

### 输出

```
0
1
2
2```

# 题解

## 作者：EarthGiao (赞：17)

# 这个其实很简单的
我是一只卡在了结束条件这里所以一直听取WA声一片，详细解释代码里见
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<algorithm>
using namespace std;
char f[501][501];//霸气的开始潇洒自信
int js=0;
int n=-1,m=-1;
void ac(int x,int y)
{
	if(x<0 || y<0 || x>n || y>m)//发现是边界就返回上一层 
	return;//边界 
	
	f[x][y]='*';
	if(f[x+1][y+1]=='@'){ac(x+1,y+1);}//八个方向各个开始寻找 
	if(f[x-1][y-1]=='@'){ac(x-1,y-1);}//找到就继续从找的的开始找 
	if(f[x+1][y-1]=='@'){ac(x+1,y-1);}
	if(f[x-1][y+1]=='@'){ac(x-1,y+1);}
	if(f[x][y+1]=='@'){ac(x,y+1);}
	if(f[x][y-1]=='@'){ac(x,y-1);}
	if(f[x+1][y]=='@'){ac(x+1,y);}
	if(f[x-1][y]=='@'){ac(x-1,y);}
}
int main()
{
	while(cin>>n>>m)
	{
		memset(f,0,sizeof(f));//因为不去定有多少组数所以用这个 
		js=0;//必须清零不然上一层的结果会影响现在的 
		if(n==0 && m==0)//结束条件 
		{
			return 0;
		}
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
			{
				cin>>f[i][j];//超级正常的输入 
			}
		}
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
			{
				if(f[i][j]=='@')//找到第一个就开始从这个开始找 
				{
					js++;//油区数量加一 
					ac(i,j);
				}
			}
		}
		cout<<js<<endl;//输出 
	}
	return 0;//完美的结束潇洒自信
}
```


---

## 作者：dessert (赞：7)

# 思路 

蒟蒻表示不会广搜，只能用深搜，搜索每个油田的联通块，标记一下。 永远记住了那个坑，花了我两个小时
# 题解
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b[100][100],sum;
int xx[9]={1, -1, 0, 0, -1, 1, 1, -1};     //八个方向
int yy[9]={0, 0, 1, -1, 1, 1, -1, -1};  
char a[101][101];
int dfs(int x,int y){             //搜索油田的联通块，防止又找了一遍 

	   b[x][y]=1;
	   for(int i=0;i<8;i++){
		   int ax=x+xx[i],ay=y+yy[i];
		    if(ax<n&&ax>=0&&ay>=0&&ay<m&&b[ax][ay]==0&&a[ax][ay]=='@')
		       dfs(ax,ay);
	      }
}
int main(){

	    scanf("%d %d",&n,&m);
	    while(n!=0&&m!=0){
	    for(int i=0;i<n;i++)
	        for(int j=0;j<m;j++)
	             cin>>a[i][j];
	     memset(b,0,sizeof(b));  //一定要记住，蒟蒻我就是在这被坑了。一定要循环完一遍后重新赋值成0 
	     sum=0;
	    for(int i=0;i<n;i++)
	        for(int j=0;j<m;j++)
	    	    if(b[i][j]==0&&a[i][j]=='@'){
	    		    sum++;                       //判断有没有油田，进行搜索 sum++;
	    	        dfs(i,j);
			  }
	      cout<<sum<<endl;
	      scanf("%d %d",&n,&m);
	      return 0;
   }
```

---

## 作者：МiсDZ (赞：6)

## 用DFS求联通块
【分析】图也可以有dfs，bfs遍历。由于dfs更容易编写，一般用dfs找联通块：从每个'@'格子出发，递归遍历它周围的'@'格子每一次访问到一个就给它写上“联通分量编号”即下面的idx数组。这样就可以在访问之前知道是否已经被访问过，从而避免一个格子被访问多次。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100+5
char pic[maxn][maxn];//存图
int m,n,idx[maxn][maxn];
void dfs(int r,int c,int id){
    if(r<0||r>=m||c<0||c>=n)return ;//出界的格子
    if(idx[r][c]>0||pic[r][c]!='@')return ;//不是'@'或已经被访问过
    idx[r][c]=id;//将点记录下来
    for(int dr=-1;dr<=1;dr++)
        for(int dc=-1;dc<=1;dc++)
            if(dr!=0||dc!=0)dfs(r+dr,c+dc,id);//向四个方向搜索·
}
int main()
{
    while(scanf("%d%d",&m,&n)==2&&m&&n){
        for(int i=0;i<m;i++)scanf("%s",pic[i]);
        memset(idx,0,sizeof(idx));
        int cnt=0;
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)//每一次扫描所有为id的方格
                if(idx[i][j]==0&&pic[i][j]=='@')dfs(i,j,++cnt);
        printf("%d\n",cnt);
    }
    return 0;
}
```
上面的代码用一个二重循环来找当前各子相邻的格子也可以用常量数组或8条dfs调用，可以根据自己喜好使用。这种算法还有个很好听的名字：种子填充(floodfill)
![](http://img.blog.csdn.net/20130825153228078)

~~刘汝佳《算法竞赛入门经典（第二版）》P162~~

---

## 作者：由比滨丶雪乃 (赞：3)

# UVA572 油田 Oil Deposits

- [题目链接](https://www.luogu.org/problem/UVA572)

- [更好的阅读体验](https://www.luogu.org/blog/Hikigaya/uva572-you-tian-oil-deposits-ti-xie)

### 题目大意

给定一个n * m 的矩阵，求它的连通块个数qwq


方法很简单，朴素的dfs求连通块：从每一个 "@" 出发，往周围搜，搜到的"@"全都标记为 "."，ans++



Code（~~我知道你们只看这个qwq~~）

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>//卑微的头文件QAQ

using namespace std;

int dx[9]={0,1,1,0,-1,-1,-1,0,1};//8个方向
int dy[9]={0,0,1,1,1,0,-1,-1,-1};
char chess[105][105];
bool check[105][105];
int t,ans;
int n,m;

void dfs(int x,int y)
{//dfs
	for(int i=1;i<=8;i++)
	{
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(nx>=1&&ny>=1&&nx<=n&&ny<=m&&check[nx][ny])//防止越界
		{
			check[nx][ny]=false;//搜到了就标记为“.”
			dfs(nx,ny);
		}
	}
}

int main()
{
	while(cin>>n>>m)
	{
		if(m==0&&n==0) break;
		ans=0;//注意多组数据，记得清零
		memset(check,false,sizeof(check));	//同上
		for(int i=1;i<=n;i++)
		   for(int j=1;j<=m;j++)
		   {
		   	   cin>>chess[i][j];
		   	   if(chess[i][j]=='@') check[i][j]=true;
		   }
		for(int i=1;i<=n;i++)
		   for(int j=1;j<=m;j++)
		   {
		   	   if(check[i][j])//求连通块
		   	   {
		   	   	     ans++;
		   	   	     dfs(i,j);
				  }
		   }
		printf("%d\n",ans);
	}
	return 0;//AC  (●ˇ∀ˇ●)
}
```




---

## 作者：zhangyiming (赞：2)

## 看到各位**大佬**都在用**BFS**和**联通块**
## 本**蒟蒻**深感无奈，只好默默地敲起了**DFS**
# 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>//头文件不解释
using namespace std;
char a[1001][1001];//建图
int s=0;
int dir[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,1},{1,1},{-1,-1},{1,-1}};//坐标增减
void dfs(int x,int y){
    if(x < 0 || y < 0 || x > n || y > m)
    return;
    a[x][y]='*';
    for(int i = 0;i < 8;i++){
	    int dx=x+dir[i][0],dy=y+dir[i][1];//改变坐标
	    if(a[dx][dy]=='@')//判断
	    dfs(dx,dy);
	}
}
int main(){
    while(cin>>n>>m){
        memset(a,0,sizeof(a));
        s=0;//清零
        if(n==0 && m==0)
        {
            return 0;
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j)
            {
                cin>>a[i][j];
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j)
            {
                if(a[i][j]=='@'){
                    s++;
                    dfs(i,j);//调用
                }
            }
        }
        cout<<s<<endl;//完美输出
    }
    return 0;
}
```

---

## 作者：Leaved_ (赞：2)

# BFS求联通块

~~多组数据再不初始化我就AFO！~~

我用的手写队列+ pair ...


代码:
```cpp
#include <bits/stdc++.h>

using namespace std;

int go[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,1},{-1,-1},{1,-1}};//二维数组记八连通 
char ma[10001][10001];
int n,m,ans;
int head=1,tail=1;//首位 
pair <int,int> q[100010];// pair 的队列 

void input() {
	memset(ma,'*',sizeof(ma));//地图初始化 
	memset(q,0,sizeof(q));//队列初始化 
	head=tail=1;
	ans=0;//答案初始化！！！ 
}

void bfs(int x,int y) {
	ma[x][y]='*';//渲染 
	q[head].first=x;
	q[head].second=y;
	while(head<=tail) {
		int x2=q[head].first;
		int y2=q[head].second;
		head++;
		//8联通 
		for (int i=0;i<8;i++) {
			int x1=x2+go[i][0];
			int y1=y2+go[i][1];
			if (ma[x1][y1]=='*'||x1<1||x1>n||y1<1||y1>m) continue;//判断边界 
			ma[x1][y1]='*';//渲染 
			tail++;//入队 
			q[tail].first=x1;
			q[tail].second=y1;
		}
	}
}

int main() {
	while(1) {
		cin>>n>>m;
		if(n==0 and m==0) break;
		input();//初始化！！！ 
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {
				cin>>ma[i][j];//输入地图 
			}
		}
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {
				if(ma[i][j]!='*') {
					ans++;//找到一个块 
					head=tail=1;//初始化 
					bfs(i,j);//搜 
				}
			}
		}
		cout<<ans<<endl;//输出答案 
	}
	return 0;
}
```

# ~~又 AC 了一道水题~~


---

## 作者：__Watcher (赞：2)

### 好吧这里写一篇比较正统的广搜

题目的意思很简单，就是求有多少个联通块
传统的做法是深搜，但~~深搜的题解太多了，我怕通过不了~~

注意点（细节）：

1、队列最多可有n*m个点，所以要开10000以上

2、mp要从1开始存，不然会RE

3、mp,qx,qy,ans都要重置

一边看代码一边讲吧
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,qx[10005],qy[10005],ans,f[105][105];
char mp[105][105];
int dx[]={1,1,1,0,0,-1,-1,-1};
int dy[]={1,0,-1,1,-1,1,0,-1};//八个方向
void bfs(){//广搜
	int i=1,j=1;
	for(;i<=j;i++){//队列不为空
		int x=qx[i];
		int y=qy[i];//出队
		f[x][y]=1;
		for(int k=0;k<8;k++){
			int xx=x+dx[k];
			int yy=y+dy[k];//下一个点
			if(mp[xx][yy]=='@'&&f[xx][yy]==0){
				j++;
				qx[j]=xx;
				qy[j]=yy;//入队
			}
		}
	}
}
int main(){
	while(cin>>n>>m){
		if(!(n+m))return 0;
		int k=0;
		memset(mp,'*',sizeof(mp));//记得重置
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>mp[i][j];
			}
		}
		memset(f,0,sizeof(f));
		ans=0;//记录联通块个数
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(mp[i][j]=='@'&&f[i][j]==0){//已经搜过就不在搜了
					memset(qx,0,sizeof(qx));
					memset(qy,0,sizeof(qy));//重置队列
					qx[1]=i;
					qy[1]=j;//搜到@入队
					bfs();
					ans++;//多了一个联通块
				}
			}
		}
		cout<<ans<<endl;
	}
}

```


---

## 作者：_•́へ•́╬_ (赞：2)

# 楼下DFS dalao都用了一个标志数组，我根本没用！
```cpp
#include<bits/stdc++.h>//懒人专用头文件
#define rpt(n) for(register int ttxyc=0;ttxyc<n;ttxyc++)//宏
using namespace std;
int n,m,ans;char a[100][100];
void find(int i,int j)
{
	int k,d1[8]={-1,-1,0,1,1,1,0,-1},d2[8]={0,1,1,1,0,-1,-1,-1};
	a[i][j]='*';//不用标志数组
	for(k=0;k<8;k++)
	{
		if(i+d1[k]<0||i+d1[k]>=n)continue;//越界
		if(j+d2[k]<0||j+d2[k]>=m)continue;//越界
		if(a[i+d1[k]][j+d2[k]]=='@')find(i+d1[k],j+d2[k]);//在同一联通块，继续找
	}
}

main()
{
    for(;scanf("%d%d",&n,&m),n||m;)
    {
    	rpt(n)scanf("%s",a+ttxyc);//一行一起输入
    	ans=0;//ans要清零
    	for(int i=0;i<n;i++)for(int j=0;j<m;j++)
    		if(a[i][j]=='@')//找到了一个新油田
    		{
    			ans++;//统计
    			find(i,j);
			}
    	printf("%d\n",ans);//输出
	}
}/**/
```

---

## 作者：yuhooo (赞：1)

```cpp
//整体的思路是，从一块油田出发并将它碾成平地，即'@'->'*'
//dfs，把和它相邻的油田再进行这样的操作
//直到所有油田都被碾成平地
#include <iostream>
const int maxn=100;
using namespace std;
char graph[maxn+1][maxn+1]; //图记录油田
int m,n; 					//m行n列
void dfs(int x,int y){
	graph[x][y]='*'; 		
	for(int i=-1;i<=1;++i)
		for(int j=-1;j<=1;++j){
			int dx=x+i;    //在九宫格内内搜索是否还有油田
            int dy=y+j;
            //注意的是不能超出边界
			if(dx>=0&&dx<m&&dy>=0&&dy<n&&graph[dx][dy]=='@') dfs(dx,dy);
		}
}
int main() {
	while(cin>>m>>n){
		if(m==0&&n==0)	break;
		for(int i=0;i<m;++i)
			for(int j=0;j<n;++j)
				cin>>graph[i][j];
		int ans=0;
		for(int i=0;i<m;++i)
			for(int j=0;j<n;++j)
				if(graph[i][j]=='@'){
					dfs(i,j);
					ans++;
				}
		cout<<ans<<endl;
	}
}

```


---

## 作者：封禁用户 (赞：1)

**地图题居然没有人发pair做法？**

那我这个STL重度依赖症患者正好来捡个漏。

---
### Part 1 准备工作

可以发现，这个地图每个格子只有两种状态，油田‘@’或者空地‘*’。那么这样的话我们毫不犹豫选择Boolean类型数组存储地图。

然后，pair上场。

对于地图上每一个位置（有序整数对），用pair存储简直是量身定制：first是x坐标，second是y坐标。惯用套路。

在BFS时，我们可以定义Next数组来表示所有从当前位置到可转移位置的坐标之差，这样对于任意一个状态，只要加上这个差值就可以得到下一个状态。
```cpp
const pair<int, int> Next[]{ 
make_pair(-1,-1),make_pair(-1,0),make_pair(-1,1),make_pair(0,1),
make_pair(0,-1),make_pair(1,-1),make_pair(1,0),make_pair(1,1) 
};

```

这时有一个问题，pair不能直接相加减，那么需要重载一下运算符。

```cpp
template<typename T1, typename T2>
inline const pair<T1, T2> operator + (const pair<T1, T2> &a, const pair<T1, T2> &b)
{
	return make_pair(a.first + b.first, a.second + b.second);
}
```

### Part 2 愉快地BFS

使用pair的bfs看起来就很简洁对吧？

```cpp
void bfs(pair<int, int> s)	//只有一个参数的BFS看起来很高端
{
	queue<pair<int, int> > que;
	que.push(s);
	while (!que.empty())
	{
		static pair<int, int> cur = make_pair(0, 0);
		cur = que.front();
		map[cur.first][cur.second] = false;		//置false
		que.pop();	//十年OI一场空，忘加pop()见祖宗
		for (auto x : Next)
		{
			static pair<int, int> temp = make_pair(0, 0);
			temp = cur + x;		//状态转移
			if (map[temp.first][temp.second])
			{
				que.push(temp);
			}
		}
	}
}
```

---

### Part 3 全部代码

高清无码，清楚明白。

```cpp
#include <iostream>
#include <utility>
#include <queue>

using namespace std;

#define MAX 101

bool map[MAX][MAX];
int m, n, ans;
const pair<int, int> Next[]{ make_pair(-1,-1),make_pair(-1,0),make_pair(-1,1),make_pair(0,1),make_pair(0,-1),make_pair(1,-1),make_pair(1,0),make_pair(1,1) };

void bfs(pair<int, int> s);
template<typename T1, typename T2>
inline const pair<T1, T2> operator + (const pair<T1, T2> &a, const pair<T1, T2> &b)
{
	return make_pair(a.first + b.first, a.second + b.second);
}

int main(void)
{
	char ch;
	while (cin >> m >> n && m)
	{
		ans = 0;
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				cin >> ch;
				map[i][j] = ch == '*' ? false : true;
			}
		}
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (map[i][j])
				{
					bfs(make_pair(i, j));
					ans++;
				}
			}
		}
		cout << ans << endl;
	}
	//system("pause");
	return 0;
}

void bfs(pair<int, int> s)
{
	queue<pair<int, int> > que;
	que.push(s);
	while (!que.empty())
	{
		static pair<int, int> cur = make_pair(0, 0);
		cur = que.front();
		map[cur.first][cur.second] = false;
		que.pop();
		for (auto x : Next)
		{
			static pair<int, int> temp = make_pair(0, 0);
			temp = cur + x;
			if (map[temp.first][temp.second])
			{
				que.push(temp);
			}
		}
	}
}

```



---

## 作者：Hiraeth (赞：1)

~~为什么第一篇题解跟紫书上面一个字不差？？？~~

根据上一篇题解学到了一个神奇的东西 

原来我们一直用的东东叫 [floodfill算法](https://en.wikipedia.org/wiki/Flood_fill)

连通块计数问题

针对该问题一般有三种解法：

1.dfs计数删块

2.bfs拓展

3.并查集法 合并+路径压缩

~~本人比较喜欢dfs~~ 因为不容易打错 而且思维简易 容易理解

读入该组元素所有信息 如果是@ 则更新为1

遍历所有元素 如果发现油田 ans++ 然后以该节点为dfs起点 删除

与其相邻所有联通块

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
char p;
int n,m,f[105][105],ans,px,py;
int dx[]={0,0,1,1,1,-1,-1,-1};
int dy[]={1,-1,0,1,-1,0,1,-1};
void dfs(int x,int y){
	f[x][y]=0;
	for (int i=0;i<8;i++)
		{
			px=x+dx[i];
			py=y+dy[i];
			if (px>0&&px<=m&&py>0&&py<=n&&f[px][py]==1) dfs(px,py);
		}
	return;
}
int main(){
	while (scanf("%d%d",&m,&n)==2&&n&&m){
		memset(f,0,sizeof(f));
		ans=0;
		for (int i=1;i<=m;i++)
			for (int j=1;j<=n;j++){
				cin>>p;
				if (p=='@') f[i][j]=1;
			} 
		for (int i=1;i<=m;i++)
			for (int j=1;j<=n;j++){
				if (f[i][j]==1) {
					ans++;
					dfs(i,j);
				}
			}
		printf("%d\n",ans);
	}
	return 0;
} 
```



---

## 作者：Selfish_2U (赞：1)

看见楼下各位大佬还没有用并查集求联通块的，所以本蒟蒻决定水一波并查集

~~（其实思路跟BFS、DFS差不多）~~

以下是本蒟蒻的解法：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,i,j,o;
long long ans;
char c[10002];//把二维数组转换为了一维，好用并查集
long long fa[10002];//并查集数组
long long d[4];//分别是判断是否合并的4个方向
//分别是向左、左下、向下、右下
long long find(long long x)//并查集（查找）
{
    if(fa[x]!=x)
    {
        fa[x]=find(fa[x]);
    }
    return fa[x];
}
void merge(long long x,long long y)//并查集（合并）
{
    x=find(x);
    y=find(y);
    if (x!=y) 
    {
        fa[x]=y;
    }
    return;
}
void init()//并查集（初始化）
{
    for (o=1;o<=a*b;o++)
    {
        if (c[o]=='@')//其实这个判断可以省去，因为后面也有判断
        {
            fa[o]=o;
        }
    }
    return;
}
int main()
{
    while (cin>>a>>b)
    {
        if (a==0&&b==0)//直到输入的两数都为0才停止
        {
            return 0;
        }
        for (i=1;i<=a*b;i++)
        {
            cin>>c[i];
        }
        d[0]=1;
        d[1]=b+1;
        d[2]=b;
        d[3]=b-1;//赋予方向数组初值
        ans=0;
        init();//并查集fa数组初始化
        for (i=1;i<=a*b;i++)
        {
            if (c[i]=='@')
            {
                for (j=0;j<=3;j++)
                {
                    if (j==0)
                    {
                        if (i+d[j]<=a*b&&c[i+d[j]]=='@'&&i%b!=0)
                        {
                            merge(i,i+d[j]);//满足条件，合并
                        }
                    }
                    if (j==1)
                    {
                        if (i+d[j]<=a*b&&c[i+d[j]]=='@'&&i%b!=0)
                        {
                            merge(i,i+d[j]);//满足条件，合并
                        }
                    }
                    if (j==2)
                    {
                        if (i+d[j]<=a*b&&c[i+d[j]]=='@')
                        {
                            merge(i,i+d[j]);//满足条件，合并
                        }
                    }
                    if (j==3)
                    {
                        if (i+d[j]<=a*b&&c[i+d[j]]=='@'&&i%b!=1)
                        {
                            merge(i,i+d[j]);//满足条件，合并
                        }
                    }
                    //每个方向的要求会根据方向而有些小变动，因为要考虑特殊情况
                }
            }
        }
        for (i=1;i<=a*b;i++)
        {
            if (c[i]=='@'&&fa[i]==i)
            {
                ans++;//每找到一个联通块，ans++
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：CreeperLordVader (赞：1)

**用代码证明BFS也可以求连通块**

个人认为思路~~更好懂~~

因此我偏不用DFS~~（实际上我也不太会）~~
```cpp
#include<bits/stdc++.h>
using namespace std;
char dt[300][300];
int m,n,ans;
int dx[]= {0,-1,1,0,0,1,-1,1,-1};//x方向上的移动 
int dy[]= {0,0,0,-1,1,1,-1,-1,1};//y方向上的移动，x和y都不等于0时是斜向移动 
bool b[300][300];//判断能不能走 
struct node {
	int x,y;
} fa,start;
queue<node>q;
void bfs(int x,int y) //常规BFS 
{
while(!q.empty()) /*不需要判断终点，一个连通块遍历完以后*/ 
	{              /* 不会再有新的儿子进入队列，队列会弹空，函数退出*/ 
		fa=q.front();
		q.pop();
		for(int i=1; i<=8; i++) 
		{
			int nx=fa.x+dx[i];
			int ny=fa.y+dy[i];//在当前点的基础上向八个方向拓展 
			if(!b[nx][ny]&&nx>0&&nx<=m&&ny>0&&ny<=n) 
			{
				node son;
				son.x=nx;
				son.y=ny;
				b[nx][ny]=1;//标记已经走过不再走 
				q.push(son);//儿子进队列 
			}
		}
	}
	ans++;//每搜一次就对应有一个连通块 
}
int main() 
{
	while(scanf("%d%d",&m,&n)==2&&m&&n)
	{
		ans=0;
		for(int i=1; i<=m; i++)
			for(int j=1; j<=n; j++) 
			{
				b[i][j]=0;//初始化 
			}
			for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
			{
				cin>>dt[i][j];
				if(dt[i][j]=='*')b[i][j]=1;//不是油田标记为不能走 
					
					
			}
			for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
			{
			    if(!b[i][j])//如果这个点是油田而且没搜过，以这个点为起点BFS 
				{
				start.x=i;
				start.y=j;
				b[start.x][start.y]=1;
				q.push(start);
				bfs(i,j);
				}
			}
			cout<<ans<<endl;
	}
	
}
```

---

## 作者：SmartBoy (赞：0)

# [](https://www.luogu.org/problem/UVA572)题目传送门
这次来一道**连通块**的题解！！！
orzorzorz




------------

## 题目思路
非常的简单，这道题就是深搜嘛（~~其实是因为广搜代码太长懒得写~~）每次dfs的就是去判断对于一个位置，其八个方位即上下左右，左上，左下，右上，右下这八个位置是否与初始判断的位置相同，就是说是否同样等于“@”，这样对每一个位置判断，就能找出连通块个数。
## 说一下伪代码吧！！


------------
```
x----行
y----列
id---油田编号
dfs(int x,int y,int id)
{
	终止条件：越界；不是油田；已经有标记
	做标记---不要再地图上直接做标记
	for(i:0~7)
	{
		计算nx、ny
		dfs(nx,ny,id)
	}
}
int main()
{
	id=0
	输入---转换；地图
	for(i：行)
	{
		for(j:列)
		{
			if(是油田；没有标记)
			{
				id++;
				dfs(i,j,id)
			}			
		}
	}
}
```


上面是伪代码，看看思路你就会发现  ~~很简单~~  真的是：

**难上加难 我太难了！！**

废话不多说
## 接下来就是你们最喜欢的代码！
（注意：这个代码里面有bag，请勿抄袭）
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
char map[15][15];
int map_copy[15][15];
int N,M,ans=0;
int dx[8]={-1,-1,-1,0,1,1,1,0};
int dy[8]={-1,0,1,1,1,0,-1,-1};
using namespace std;
void dfs(int x,int y,int id)
{
	if(x>N||x<1||y>M||y<1||map[x][y]=='*'||map_copy[x][y]!=0)
	{
		return;
	}
	map_copy[x][y]=id;
	int nx,ny;
	for(int i=0;i<=7;i++)
	{
		nx=x+dx[i];
		ny=y+dy[i];
		dfs(nx,ny,id);
	}
}
int main()
{
	int id=0;
	memset(map,0,sizeof(map));
	memset(map_copy,0,sizeof(map_copy));
	cin>>N>>M;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
		{
			cin>>map[i][j];
		}
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
		{
			if(map[i][j]=='@'&&map_copy[i][j]==0)
			{
				id++;
				dfs(i,j,id);
			}
		}
	}
	cout<<id<<endl;
	return 0;
}
```
（真的不想再写了！）
## 祝各位巨佬天天AC！

---

## 作者：哈哈哈哈。 (赞：0)

# 裸裸的DFS
最近迷上了**刷DFS**，这道题也是典型的**DFS求连通块**问题，就是输入有点~~小麻烦~~。

------------
值得的是油田扩张的方向有八个：

------------

```cpp
int dir[8][2]={{1,1},{-1,-1},{1,-1},{-1,1},{1,0},{-1,0},{0,1},{0,-1}};
//这样可能会好理解一些，一个大括号内，存储一次扩展方向对下x,y坐标产生的影响;
```

------------

然后就处理搜索，感觉没有必要开bool数组存搜索状态，其实在满足条件的同时，只要是搜过的油田，直接填充成 **土** 就好了：

------------

```cpp
if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&a[tx][ty]=='@')//满足搜索条件;
		{
			a[tx][ty]='.';//填充操作;
			dfs(tx,ty);//继续搜索;
		}
```
------------
Ps：因为是求连通块，所以不存在有结束搜索的条件，填充完了，自然停止;


贴一手代码：

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int dir[8][2]={{1,1},{-1,-1},{1,-1},{-1,1},{1,0},{-1,0},{0,1},{0,-1}};
int sum[1001];
char a[1001][1001];
void dfs(int x,int y)
{
	for(int i=0;i<8;i++)
	{
		int tx=x+dir[i][0];
		int ty=y+dir[i][1];
		if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&a[tx][ty]=='@')
		{
			a[tx][ty]='.';
			dfs(tx,ty);
		}
	}
}
int main()
{
	int v=1;
	while(cin>>n>>m,n!=0)//处理输入不为0，否则停止;
	{
		int ans=0;//处理答案用的;
		for(int i=1;i<=n;i++)
		    for(int j=1;j<=m;j++)
		    {
		    	cin>>a[i][j];
			}
		for(int i=1;i<=n;i++)
		    for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='@')
				{
					dfs(i,j);
					a[i][j]='.';//填充自己;
					ans++;//因为求连通块，每搜索到的都已经处理了连通块，所以每次搜到油田，则ans++;
				}
			} 
		sum[v]=ans;//存进数组，不过好像没用，可以直接输出的;
		v++;//
	}
	for(int i=1;i<v;i++)
	{
		cout<<sum[i]<<endl;
	}
	return 0;
} 
```
------------

### 其实这道题就这么~~简单~~


---

## 作者：清风我已逝 (赞：0)

用DFS求连通块

我的代码：

```
#include<iostream>
#include<cstdio>

using namespace std;

int n,m,ans;
char a[105][105];

int dx[]={0,0,-1,-1,-1,1,1,1},
	dy[]={1,-1,0,1,-1,0,1,-1};

bool check(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}

void dfs(int x,int y){
	for(int i=0;i<8;i++){
		int tx=x+dx[i],ty=y+dy[i];
		if(check(tx,ty)&&a[tx][ty]=='@'){
			a[tx][ty]='*';
			dfs(tx,ty);
		}
	}
}

int main()
{
	while(cin>>n>>m){
		if(!n&&!m) break;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>a[i][j];
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]=='@') ++ans,dfs(i,j);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

算法竞赛入门经典上的代码：
值得借鉴的地方：判断出界以及八方向

```
#include<cstdio>
#include<cstring>
const int maxn = 100 + 5;
char pic[maxn][maxn];
int m, n, idx[maxn][maxn];
void dfs(int r, int c, int id) {
	if(r < 0 || r >= m || c < 0 || c >= n) return;
//"出界"的格子
	if(idx[r][c] > 0 || pic[r][c] != '@') return;
	//不是"@"或者已经访问过的格子
	idx[r][c] = id; //连通分量编号
	for(int dr = -1; dr <= 1; dr++)
		for(int dc = -1; dc <= 1; dc++)
			if(dr != 0 || dc != 0) dfs(r+dr, c+dc, id);
}
int main( ) {
	while(scanf("%d%d", &m, &n) == 2 && m && n) {
		for(int i = 0; i < m; i++) scanf("%s", pic[i]);
		memset(idx, 0, sizeof(idx));
		int cnt = 0;
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				if(idx[i][j] == 0 && pic[i][j] == '@')
					dfs(i, j, ++cnt);
		printf("%d\n", cnt);
	}
	return 0;
}
```

---

