# [NOI Online #3 入门组] 观星

## 题目背景

脚造数据一组，欢迎hack

## 题目描述

Jimmy 和 Symbol 约好一起看星星，浩瀚的星空可视为一个长为 $N$、宽为 $M$ 的矩阵，矩阵中共有 $N\times M$ 个位置，一个位置可以用坐标 $(i,j)$（$1\le i\le N$，$1\le j\le M$）来表示。每个位置上可能是空的，也可能有一个星星。

对于一个位置 $(i,j)$，与其相邻的位置有左边、左上、上面、右上、右边、右下、下面、左下 8 个位置。相邻位置上的星星被视为同一个星座，这种关系有传递性，例如若 $(1,1),(1,2),(1,3)$ 三个
位置上都有星星，那么这三个星星视为同一个星座。包含的星星数量相同的星座被视为一个星系（一个星系中的星座不一定相邻），星系的大小为星系中包含的所有星星数量。

由于 Symbol 太喜欢星系了，他就想考一考 Jimmy，让 Jimmy 求出星空中有多少个星系，他还想知道，最大的星系有多大。

## 说明/提示

对于 $20\%$ 的数据，$N,M\le 20$，最大星系大小不超过 200。

对于 $50\%$ 的数据，$N,M\le 400$。

对于 $70\%$ 的数据，$N,M\le 1100$。

对于 $100\%$ 的数据，$2\le N,M\le 1500$，最大星系大小不超过 100000。

## 样例 #1

### 输入

```
5 7
*......
..**..*
.*...*.
...*...
....*..```

### 输出

```
3 4```

## 样例 #2

### 输入

```
10 10
**..**.**.
***....*..
*...**.**.
...*..*...
..........
**...**.*.
..*.*....*
..........
***..*.*..
.***..*...```

### 输出

```
4 12```

# 题解

## 作者：zhangjingzhuo (赞：68)

## 其实这不是一道特别难的题……
这道题可以直接用DFS过。关键是要先读懂题目，分清“星系”和“星座”的意思。

难点是如何把星星数相同的星座划入同一星系。可以用一个数组把星星数相同的星座存入一个变量中。在此代码中，galaxy[ i ]用于存储有i颗星星的星座有多少个，易知i×galaxy[ i ]就是该星系的星星个数。（i就表示星系中每个星座星星的数量）

代码如下：
```cpp
#include<bits/stdc++.h>
#define N 1502
using namespace std;
int n,m,dx[8]={0,0,1,1,1,-1,-1,-1},dy[8]={1,-1,1,0,-1,1,0,-1};//dfs八个方向的模板
int galaxy[N*N],sum,Max;
bool star[N][N];//用于存储每个坐标是否有星星
void Search(int x,int y){//dfs
	sum++;//储存搜索到的这个星座的星星数量
	star[x][y]=false;//设为已访问过
	for(int i=0;i<8;i++){//八个方向
		int xx=x+dx[i],yy=y+dy[i];
		if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&star[xx][yy])
			Search(xx,yy);
	}
}
int main(){
//	freopen("star.in","r",stdin);
//	freopen("star.out","w",stdout);
	char c;
	cin>>n>>m;
	for(int i=1;i<=n;i++){//将输入结果存入star数组
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='*')star[i][j]=true;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(star[i][j]){
				Search(i,j);
				galaxy[sum]++;
				if(sum*galaxy[sum]>Max)Max=sum*galaxy[sum];//用于计算最大的星系，sum*galaxy[sum]的意义详见上面
				sum=0;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n*m;i++){
		if(galaxy[i])ans++;//用于计算星系的数量
	}
	cout<<ans<<' '<<Max;
	return 0;
}
```
#### Thanks for your reading!And please don't be a cheater!

---

## 作者：PersistentLife (赞：16)

### 题目分析

我们先找到一个 `*`，然后对其进行 BFS，并将所有访问过的 `*` 标记为 `.`，在进行 BFS 的同时记录下目前的 `*` 数量。

当一次 BFS 结束后，我们将统计的数量放入之前开好的桶中，即将 $h_{res}+1$。

如果此时 $h_{res}$ 为 $0$，则将星系数量加上 $1$ 并更新此时最大的星系，因为只有 $h_{res}$ 改变了，所以只需要将 $h_{res}$ 和 $max$ 比较。

结束后再找到一个没有被访问过的 `*`，然后重复上述过程，直到所有 `*` 被访问。

### 代码实现

> 注：具体做法见代码注释。

先定义变量。

```cpp
char g[1567][1567];//星空
int n,m,h[12345678],maxx,tots,cnts,cntg;
//行 列 桶 最大星系大小 星星数量 已经被访问的星星数量 总共的星系数
struct node
{
	int x,y;
};//一个位置
queue <node> q;//BFS队列
int dx[8]={0,0,-1,1,1,-1,-1,1};
int dy[8]={1,-1,0,0,1,1,-1,-1};//枚举八个方向
```

然后构建主函数，先读入并统计星星数。

```cpp
scanf("%d%d",&n,&m);
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=m;j++)
	{
		cin>>g[i][j];
		if(g[i][j]=='*') tots++;
	}
}
```

然后枚举每一个点进行 BFS。

```cpp
while(cnts<tots)//还有星星没访问
{
	int ii,jj;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(g[i][j]=='*')//找到星星
			{
				ii=i;
				jj=j;
				bfs(ii,jj);//BFS
			}
		}
	}
}
```

接着完成 BFS 函数。

```cpp
void bfs(int fx,int fy)
{
	node no;
	no.x=fx;no.y=fy;
	q.push(no);//放入队列
	int res=1;//统计星星数，因为起点也算，所以初始值为1
	g[no.x][no.y]='.';//标记
	while(!q.empty())
	{
		node fr=q.front();
		for(int i=0;i<=7;i++)
		{
			if(g[fr.x+dx[i]][fr.y+dy[i]]=='*')
			{
				no.x=fr.x+dx[i];no.y=fr.y+dy[i];
				q.push(no);//放入队列
				g[fr.x+dx[i]][fr.y+dy[i]]='.';//标记
				res++;//星星数加1
			}
		}
		q.pop();//弹出队列
	}
	if(h[res]==0) cntg++;//统计星系数
	h[res]++;//放入桶中
	maxx=max(maxx,h[res]*res);//更新最大星系
	cnts+=res;//加上被访问的星星数
}
```

最后是完整代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
char g[1567][1567];
int n,m,h[12345678],maxx,tots,cnts,cntg;
struct node
{
	int x,y;
};
queue <node> q;
int dx[8]={0,0,-1,1,1,-1,-1,1};
int dy[8]={1,-1,0,0,1,1,-1,-1};
void bfs(int fx,int fy)
{
	node no;
	no.x=fx;no.y=fy;
	q.push(no);
	int res=1;
	g[no.x][no.y]='.';
	while(!q.empty())
	{
		node fr=q.front();
		for(int i=0;i<=7;i++)
		{
			if(g[fr.x+dx[i]][fr.y+dy[i]]=='*')
			{
				no.x=fr.x+dx[i];no.y=fr.y+dy[i];
				q.push(no);
				g[fr.x+dx[i]][fr.y+dy[i]]='.';
				res++;
			}
		}
		q.pop();
	}
	if(h[res]==0) cntg++;
	h[res]++;
	maxx=max(maxx,h[res]*res);
	cnts+=res;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>g[i][j];
			if(g[i][j]=='*') tots++;
		}
	}
	while(cnts<tots)
	{
		int ii,jj;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(g[i][j]=='*')
				{
					ii=i;
					jj=j;
					bfs(ii,jj);
				}
			}
		}
	}
	printf("%d %d",cntg,maxx);
	return 0;
}
```


---

## 作者：XianChanting (赞：15)

本题的难度有点**名不副实**

如果觉得这道题有点难的话，请移步 [P1596 Lake Counting S](https://www.luogu.com.cn/problem/P1596)相信你做对了就会发现这道题可以轻轻松松**AC**了

## __思路__：

1. 用一个字符数组a来存储每一个点所对应的值
2. 用一个数组xz来存储对应的星系数量
3. 用dfs搜索出每一个星座的值
4. 用sort排序，这样$xz[0]$就是最大值了（也可以用 $O(n)$ 的朴素算法或者 $O(log n)$ 的二分算法来查找最大值这里就不一一列举了， ~~因为我懒~~ 给各位更多的思考余地）
5. 用ans统计数量

## __实现__：
* DFS代码

```cpp
int dfs(int x,int y) {
	int sum=0;
	a[x][y]='.';
	int dx,dy;
	for(int i=-1; i<=1; i++) {
		for(int j=-1; j<=1; j++) {//八个方向移步
			dx=x+i;
			dy=y+j;
			if(dx>=0&&dx<n&&dy>=0&&dy<m&&a[dx][dy]=='*')
				sum+=dfs(dx,dy);
		}
	}
	return 1+sum;
}
```
* 计算星系的数量公式 $xz[i]=xz[i] \times i$

* 统计星系
```cpp
for(int i=0; i<n; i++) {
	for(int j=0; j<m; j++) {
		if(a[i][j]=='*') {
			int temp=dfs(i,j);
			if(temp!=0)++xz[temp];//不为0就增加（虽然0×任何数都是0，保险起见）
		}
	}
}
```

* 处理星系数量 **必须在枚举数量与处理最大值之前处理，否则得出来的答案可能是错误的**

```cpp
for(register int i=0; i<100002; ++i)
	xz[i]=xz[i]*i;//处理星系数量 注意：可以同时统计，不过得多加一个f数组，还是我懒
```

* 枚举数量

```cpp
for(register int i=0; i<100002; ++i)
	if(xz[i])++ans;//等价于if(xz[i]>0)++ans;
```

* 处理最大值

$O(nlogn)$ 算法
```cpp
sort(xz,xz+100001,cmp);//排个序，这样xz[0]里面就存储的是最大星座（同样也是懒）
```
$O(n)$ 算法（注意输出的时候得用Max，而不是$xz[0]$）
```cpp
int Max=0;
for(register int i=0; i<100002; ++i)
	if(xz[i]>Max) Max=xz[i];

```
$O(logn)$ 算法：二分，在这里就不赘述了
## 下面上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1501][1501];//a数组存储每一个点所对应的值
int ans;//ans统计星系数量
int n,m;
int xz[100005];//统计每一个星系的数量即星系的星星数量为xz[i]*i;
int dfs(int x,int y) { //简单的 DFS
	int sum=0;
	a[x][y]='.';
	int dx,dy;
	for(int i=-1; i<=1; i++) {
		for(int j=-1; j<=1; j++) {
			dx=x+i;
			dy=y+j;
			if(dx>=0&&dx<n&&dy>=0&&dy<m&&a[dx][dy]=='*')
				sum+=dfs(dx,dy);
		}
	}
	return 1+sum;
}
bool cmp(int x,int y) { //从大到小排序
	return x>y;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++)scanf("%s",a[i]); //读数
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			if(a[i][j]=='*') { //统计星系
				int temp=dfs(i,j);
				if(temp!=0)++xz[temp];//不为0就增加（虽然0×任何数都是0，保险起见还是这样）
			}
		}
	}
	for(register int i=0; i<100002; ++i)
		xz[i]=xz[i]*i;//处理星系数量 注意：可以同时统计，不过得多加一个f数组，还是我懒
	sort(xz,xz+100001,cmp);//排个序，这样xz[0]里面就存储的是最大星座（同样也是懒）
	for(register int i=0; i<100002; ++i) //枚举数量
		if(xz[i])++ans;//等价于if(xz[i]>0)++ans;
	printf("%d %d",xz[0],ans);//注意输出顺序反了，应该是 printf("%d %d",ans,xz[0]);
	return 0;
}
```

完结撒花%>_<%


---

## 作者：Diamiko (赞：13)

这题还是比较水的。

直接深搜就能处理出不同的星座及其数量。

遍历矩阵，每遇到一个星星就深搜标记所有相邻星星。

包含星星个数相同的星座就是一个星系，那么只要对星座里的星星数量排序，相邻且相同的就处于一个星座。那么答案呼之欲出了。

代码中的res表示每次深搜记录的星星个数，stars表示每个星座的星星个数，xingzuo表示星座个数，num表示每个星系的星星个数。

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[1505][1505];
int n,m,xx,yy;
const int dx[8]={0,1,0,-1,1,-1,1,-1};
const int dy[8]={1,0,-1,0,1,-1,-1,1};//方向数组
int res;
void dfs(int x,int y)
{
	c[x][y]='.';//改成点，以后不搜了
	res++;//星星数量自增
	for(register int i(0);i<8;++i)
	{
		xx=x+dx[i];
		yy=y+dy[i];
		if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&c[xx][yy]=='*')
		{
        		//注意判断越界
			dfs(xx,yy);
		}
	}
}
int stars[3000005];
int cnt;
int xingzuo(1);//至少得有一个星座吧
int num[3000005];
int main()
{
	freopen("star.in","r",stdin);
	freopen("star.out","w",stdout);
	cin>>n>>m;
	for(register int i(1);i<=n;++i)
	{
		for(register int j(1);j<=m;++j)
		{
			cin>>c[i][j];
		}
	}
	for(register int i(1);i<=n;++i)
	{
		for(register int j(1);j<=m;++j)
		{
			if(c[i][j]=='*')
			{
				res=0; //万万不要忘记清零
				dfs(i,j);
				stars[++cnt]=res;
			}
		}
	}
	sort(stars+1,stars+1+cnt);
	for(register int i(1);i<cnt;++i)
	{
		num[xingzuo]+=stars[i];
		if(stars[i]!=stars[i+1])
		{
			xingzuo++;
		}
	}
	num[xingzuo]+=stars[cnt];
	cout<<xingzuo<<' ';
	sort(num+1,num+xingzuo+1);
	cout<<num[xingzuo]<<endl;
	return 0;
}
```

---

## 作者：修罗海神王 (赞：11)

听说好多人这次都 $AK$ 了，~~我好惭愧呀（第三题全*wa*）。~~

好的，絮絮叨叨的话题结束了。我们要开始严肃的讲解了。

但在此之前，需要有几个问题向大家明确：

1、题目输入的是 _**星星**_ ，而不是 _**星座**_ 

2、看清题目描述，左边、左上、上面、右上、右边、右下、下面、左下 8 个位置的 _**星星**_为_**星座**_。

3、包含的 _**星星**_ 数量相同的 _**星座**_ 被视为一个 _**星系**_ （一个 _**星系**_ 中的 _**星座**_ 不一定相邻）， _**星系**_ 的大小为 _**星系**_ 中包含的所有 _**星星**_ 数量。

4、问题求的是星空中有多少个 _**星系**_ ，_**星星**_或_**星座**_；以及最大的 _**星系**_ 有多大，而不是 _**星星**_  或 _**星座**_ 的面积。

好了，明确了这几个项，就可以来做题了。

一眼就可以看出，这道题最简单的做法是$BFS$,因为文中提到了八方向。所以，我们可以利用广搜求出星座的数量以及每一个星座的面积，存入$a$数组。

再用桶数组存每个面积星座的数量，然后根据最大值累加星系的数量，并求出最大的面积星座，注意可以用 $bb[i]*i$
计算，最后输出。

我们重点来讲一讲广搜：

代码加注释：
```cpp
void bfs(int x,int y)//由一点计算出星座的面积
{
	int h=0,t=1,cx,cy;//和往常一样哦
	c[1][1]=x;c[1][2]=y;a[++xx]=1;//用c[1][1]标记行，用c[1][2]标记列,统计新星座的面积。
	b[x][y]=0;//把这个点标记为0，变为走过。
	while(h<=t)
	{
		h++;
		for(int i=1;i<=8;i++)//八方向
		{
			cx=c[h][1]+dx[i];
			cy=c[h][2]+dy[i];//计算一下通过八方向的行和列。
			if(cx<1||cy<1||cx>n||cy>m||b[cx][cy]==0) continue;//越界或走过就下一个循环
			t++;
			c[t][1]=cx;c[t][2]=cy;//标记
			b[cx][cy]=0;a[xx]++;//这个点标记，星座的面积增加
		}
	}
}
```

好了，这里是  **~~全~~** 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,xx,a[150000],c[1500*1500+100][5],b[1600][1600],weimx,ans,bb[100010];
int mx;
string st;
char ch;
const int dx[]={0,1,1,0,-1,-1,-1,0,1};
const int dy[]={0,0,1,1,1,0,-1,-1,-1};
void bfs(int x,int y)
{
	int h=0,t=1,cx,cy;
	c[1][1]=x;c[1][2]=y;a[++xx]=1;
	b[x][y]=0;
	while(h<=t)
	{
		h++;
		for(int i=1;i<=8;i++)
		{
			cx=c[h][1]+dx[i];
			cy=c[h][2]+dy[i];
			if(cx<1||cy<1||cx>n||cy>m||b[cx][cy]==0) continue;
			t++;
			c[t][1]=cx;c[t][2]=cy;
			b[cx][cy]=0;a[xx]++;
		}
	}
}
int main()
{
	cin>>n>>m;
	getline(cin,st);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			ch=getchar();
			if(ch=='*') b[i][j]=1;
		}
		getline(cin,st);
	}
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	      if(b[i][j]) bfs(i,j);
	sort(a+1,a+xx+1);//这一段其实不用
	for(int i=1;i<=xx;i++)
	{
		bb[a[i]]++;
		weimx=max(weimx,a[i]);
	}//统计b数组
	for(int i=1;i<=weimx;i++)
	{
		if(bb[i]) ans++;
		mx=max(mx,bb[i]*i);
	}//求问题
	cout<<ans<<" "<<mx<<"\n";
	return 0;
}
```

认真写题解的我给认真看题解的你们一个赞$o$  $!$

---

## 作者：_jimmywang_ (赞：7)

### $[NOI Online $#$3$ 入门组$]T2$观星 解题报告：

此题，有点学过$dfs$的同鞋一定能马上看出来：不就是个求联通快吗？$dfs$上来就刚。

然鹅，事情没那么简单。。。

我们再读读题目：

>包含的星星数量相同的星座被视为一个星系，星系的大小为星系中包含的所有星星数量

仔细看看？

>**包含的星星数量相同**的**星座**被视为一个**星系**

$emm...$于是我们好像需要记录每个联通快的大小了。。。

不仅如此，还要知道那几个星座是大小相同的。。。

我们想想看：在$dfs$的时候，每经过一个点，就要找与它相邻的$8$个点，然后去找那个点，再重复。

那么经过一个点，就把当前联通快编号的$size+1$不就好了？

顺便开一个数组记录大小为$i$的联通快有多少个~完事！

$the$_$code$:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll r() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	if(c=='-')f=-1,c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d r()
ll n,m;
char c[2010][2010];
bool a[2010][2010];
ll sum[1000010],k,mx;
ll dx[8]={0,1,0,-1,1,1,-1,-1};
ll dy[8]={1,0,-1,0,1,-1,1,-1};
ll ans,mxx,siz;
void dfs(ll ii,ll jj){
	siz++;
	a[ii][jj]=1;
	f(i,0,7){
		ll x=ii+dx[i],y=jj+dy[i];
		if(x<=0||x>n||y<=0||y>m)continue;
		if(c[x][y]=='*'&&!a[x][y])dfs(x,y);
	}
}
int main(){
	//freopen("star.in","r",stdin);
	//freopen("satr.out","w",stdout);
	n=d,m=d;
	f(i,1,n)f(j,1,m)cin>>c[i][j];
	f(i,1,n)f(j,1,m)if(c[i][j]=='*'&&!a[i][j])siz=0,dfs(i,j),sum[siz]++,mx=max(mx,siz),k++;
	f(i,1,mx)if(sum[i])ans++,mxx=max(mxx,sum[i]*i);
	printf("%lld %lld",ans,mxx);
	return 0;
}


```


---

## 作者：zmxqs (赞：6)

没人写题解？

我来写题解了，我的做法还是很不错的。

虽然自带了点大常数，不过在目前做法能够排在第一页最优解

做法：dfs（deep first search）（当然bfs也可以，但是在这里效率没有显著的变化。如果要用的话，**尽量**手写队列或者STL queue+O2）+ map

先说一下如何求每个星座的数量，跑朴素的连通块就行

```

const int dx[] = {1 , 0,-1, 0,-1, 1, 1,-1} ;
const int dy[] = {0 ,-1, 0, 1,-1,-1, 1, 1} ;

void dfs(int x,int y) {
	if(a[x][y] == false) {
		return ;
	}//边界
	a[x][y] = false ;//标记已经走过
	
	++ cnt ;//计数
	
	for(int i=0;i<8;++i) {//遍历八方向
		dfs(x + dx[i] , y + dy[i] ) ;
	}
	
	return ;
}

```

注意是八方向，为了简化代码，我们可以使用数组+循环替代多

然后是如何统计星系，根据题目的定义，有以下几个方法

+ 数组（开大容易挂，毕竟$n^2$的遍历不是开玩笑的）

+ 哈希（正确性可能会有些偏差，但是比普通数组更加省时省力，代码实现程度略高）

+ STL map，利用map的几个功能，不仅不用担心遍历过多的问题，代码还很简单。不过在时间复杂度上可能会比哈希略低（插入，遍历还是比哈希快）

用法嘛，像数组一样，可以
```cpp

map<int,int> m ;
m[number] ++ ;

```

不过 map 不支持数组下标访问整个容器，需要使用迭代器

```cpp

map<int,int> :: iterator it = m.begin() ;
for(;it != m.end();++it) {
	// To do
}

```

统计答案，星座的数量和每座星系的数量相乘就行

```cpp


inline int Max_Galaxy(map <int,int> type) {
	int ans = 0 ;
	for(map<int,int> :: iterator it = type.begin(); it != type.end() ; ++ it) {
		pair<int,int> temp = (*it) ;
		ans = Max(ans , temp.fi * temp.se) ;
	}
	return ans ; 
}

```

### Main：

应该没有什么难理解的了吧

```cpp

int main() {
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
	cout.tie(0) ;
	
	cin >> n >> m ;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			char c ;
			cin >> c ;
			a[i][j] = c == '*' ? true : false ;
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {				
			if(a[i][j] == true) {
				cnt = 0 ;
				dfs(i,j) ;
				++ Galaxy[cnt] ;
			}
		}	
	}
	
	cout << Galaxy.size() << ' ' << Max_Galaxy(Galaxy) << '\n' ; 
	return 0 ;
}

```

#### 最终程序：

```cpp
#include<bits/stdc++.h>
#define Max(a,b) ((a) > (b) ? (a) : (b))
#define N 1505
#define M 1505 
#define sqr(x) ((x) * (x))
#define se second
#define fi first

using namespace std;

int n,m;
bool a[N][M] ;

map <int,int> Galaxy ;


//bool operator < (const pair <int,int> x , const pair <int,int> y) {
//	return x.se < y.se ;
//}

int cnt = 0 ;

const int dx[] = {1 , 0,-1, 0,-1, 1, 1,-1} ;
const int dy[] = {0 ,-1, 0, 1,-1,-1, 1, 1} ;

void dfs(int x,int y) {
	if(a[x][y] == false) {
		return ;
	}
	a[x][y] = false ;
	
	++ cnt ;
	
	for(int i=0;i<8;++i) {
		dfs(x + dx[i] , y + dy[i] ) ;
	}
	
	return ;
}

inline int Max_Galaxy(map <int,int> type) {
	int ans = 0 ;
	for(map<int,int> :: iterator it = type.begin(); it != type.end() ; ++ it) {
		pair<int,int> temp = (*it) ;
		ans = Max(ans , temp.fi * temp.se) ;
	}
	return ans ; 
}
int main() {
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
	cout.tie(0) ;
	
	cin >> n >> m ;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			char c ;
			cin >> c ;
			a[i][j] = c == '*' ? true : false ;
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {				
			if(a[i][j] == true) {
				cnt = 0 ;
				dfs(i,j) ;
				++ Galaxy[cnt] ;
			}
		}	
	}
	
	cout << Galaxy.size() << ' ' << Max_Galaxy(Galaxy) << '\n' ; 
	return 0 ;
}

```

By SteveFang



---

## 作者：monstersqwq (赞：5)

~~这是一个考场上莫名其妙开了个无意义的数组然后还开小了导致没有满分的弱智的题解。~~

进入正题：

这题很多人把题面看错了，是输出星系的数量和最大星系的大小（星系的定义题面说的很清楚），不是输出星座数量和最大星座的大小，当时很多人发帖问。

看完题面，主要可以把此题分成两部分：寻找星座（我使用 dfs）、统计星系。

### 1.寻找星座

先介绍一下我使用的几个数组吧：$ma_{i,j}$ 表示 $(i,j)$ 点上有没有星星，有为 $1$，没有为 $0$，在输入时处理。（可以开 bool，赛场上没开，懒得换了）

bool 数组 $vi_{i,j}$ 表示 $(i,j)$ 点上在之前有没有被星座占领，有为 true，没有为 false。（分析发现应该就是只防止了搜索回当前正在搜索的星座的其它星星）

还有就是 $dx,dy$ 两个数组，是 dfs 的必备数组，简化向四周搜索的代码，dfs 老选手应该都知道。

最后有一个变量 $cntt$，记录当前星座的星星数量。（记得开全局，每次搜索新的星座要清零）

然后就可以按照 dfs 的标准过程来搜索了：

1.出界返回

2.符合条件的把 $v_{x,y}$ 标记成 $true$，把当前的星星数量 $cntt=cntt+1$。

3.使用 $dx,dy$ 来搜索周围的星星。

寻找星座的工作就这样结束了。

### 2.统计星系

可能有人会问：你这样统计每个星座的星星数量会重复覆盖啊？这还怎么统计星系？

我使用了一个桶来统计，$xingxi_i$ 表示星星数量为 $i$ 的星座的数量，是星系的判断就是 $xingxi_i>0$，星系大小就是 $xingxi_i \times i$，在每次搜索完后统计。（数组只用开 $1 \times 10^5$，因为数据范围内说了最大的星系最大只有这么大，那么最大的星座也最大这么大）

那么最后统计两个答案的过程就很简单了，具体可以看我代码理解。

复杂度：读入 $O(NM)$，搜索 $O(NM)$（因为每个点只经过一次），统计答案 $O(1 \times 10^5)$（可以不加）。

则总复杂度就是 $O(NM)$，妥妥跑过。

附上代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

using namespace std;
int n,m,cnt,cntt;
int ma[1505][1505];
bool vi[1505][1505];
int xingxi[100005];
int dx[8]={-1,1,-1,1,0,0,-1,1};
int dy[8]={1,-1,-1,1,1,-1,0,0};
void dfs(int x,int y)
{
	if(x<1||y<1||x>n||y>m) return;
	if(vi[x][y]==false&&ma[x][y]==1)
	{
		vi[x][y]=true;
		cntt++;
		for(int i=0;i<=7;i++)
		{
			dfs(x+dx[i],y+dy[i]);
		}
	}
}
int main()
{
	//freopen("star.in","r",stdin);
	//freopen("star.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		string tmp;
		cin>>tmp;
		for(int j=0;j<m;j++)
		{
			if(tmp[j]=='*') ma[i][j+1]=1;
			else ma[i][j+1]=0;
		}
	}//读入的处理 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(ma[i][j]==1&&vi[i][j]==0)
			{
				cntt=0;
				dfs(i,j);
				xingxi[cntt]++;
			}
		}
	}//搜索 
	int ans=0,cnt=0;
	for(int i=1;i<=100000;i++)
	{
		if(xingxi[i]>0)
		{
			cnt++;
			ans=max(ans,xingxi[i]*i);
		}
	}//统计答案 
	cout<<cnt<<" "<<ans;
    return 0;
}
```


---

## 作者：irosalies (赞：3)

说实话，此题并不难

搞清楚星座和星系的区别，深搜走一遍就可以了

具体的思路放在代码里面
```c
#include<bits/stdc++.h>
using namespace std;
int n,m,mapp[1505][1505],ccount,xx[1505*1505],ma;//mapp是地图，xx代表的是星系数量，ccount代表的是每一次深搜星星的个数，ma是max（最大值）
int d[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
char c;
void dfs(int x,int y){
	mapp[x][y]=0;//深搜过了就把这个点赋值成0，以防把星系数重复了
	ccount++;//把计数器++（就是星星个数++）
	for(int i=0;i<8;i++){
		int xx=x+d[i][0],yy=y+d[i][1];//（常规深搜）
		if(xx>0&&xx<=n&&yy>0&&yy<=m&&mapp[xx][yy])dfs(xx,yy);//判断没有越界和没有访问过就访问一遍
	}
}
int main(){
	cin>>n>>m;//读入m,n
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;//读入每一个点
			if(c=='.')mapp[i][j]=0;//这句话可以删去，但是本人喜欢不删，看着比较舒服
			if(c=='*')mapp[i][j]=1;//如果是星星就把地图上的点赋值成1，不是则赋值成0
		}
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mapp[i][j]==1){//如果这个点是星星就开始深搜
				dfs(i,j);//看上面dfs代码
				xx[ccount]++;//把有ccount个数的星系数量++
				if(ccount*xx[ccount]>ma)ma=ccount*xx[ccount];//如果这个星系的大小（星系里面星星的数量）最大的话，就把ma（max）重新赋值
				ccount=0;//清零
			}
		}
	}
	int ans=0;//ans是存储星系最多的数量
	for(int i=0;i<=n*m;i++){//这里的m*n是把地图上每一个点都过一遍
		if(xx[i])ans++;//判断此点上有无星系，有的话就++
	}
	cout<<ans<<' '<<ma;//输出最多的星系数量和最大星系的大小
	return 0;
}

```
望通过


---

## 作者：ChenZhengJie (赞：2)

一道简单的dfs暴搜题(这次NOI网上测试太良心了！)

通过dfs寻找星座,根据星座大小归到相应星系中
```cpp
#include <iostream>
using namespace std;
int n,m;
//矩阵 
char c[1505][1505];
//标志数组(是否访问) 
bool vis[1505][1505];
//f[i]:星座中星星个数为i的数量 
int f[2250005];
//判断是否越界 
bool pd(int i,int j){
	return i>=1&&i<=n&&j>=1&&j<=m;
}
//方向数组 
int dx[8]={0,1,0,-1,1,-1,1,-1};
int dy[8]={1,0,-1,0,1,-1,-1,1};
int s=1;//星座中星星数量 
//dfs搜索 
void dfs(int x,int y){
	//八个方向 
	for(int i=0;i<=7;i++){
		int xx=x+dx[i],yy=y+dy[i];
		//满足三个条件(不越界,有星星,未访问) 
		if(pd(xx,yy)&&c[xx][yy]=='*'&&!vis[xx][yy]){
			vis[xx][yy]=1;
			s++;dfs(xx,yy);
		}
	}
}
int main(){
	//freopen("star.in","r",stdin);
	//freopen("star.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	cin>>c[i][j];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		//寻找起始搜索点 
		if(c[i][j]=='.'||vis[i][j])continue;
		vis[i][j]=1;
		s=1;
		dfs(i,j);
		f[s]++;//星系计数(星座中星星个数为s的) 
	}
	int sum=0,ans=0;
	//计算星系数和最大星系大小 
	for(int i=1;i<=n*m;i++){
		if(f[i]){sum++;ans=max(ans,f[i]*i);}
	}
	cout<<sum<<' '<<ans;
}
```


---

## 作者：LiveZoom (赞：2)

# 题解 P6566 [NOI Online #3 入门组]观星
先看我的考场代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

int n, m, num[300005], tot[100005], cnt, x[300005], y[300005];
int ans;
char star[1505][1505];

int BFS (int fx, int fy) {
	star[fx][fy] = '.';
	int ans = 1;
	int h = 0, t = 1;
	x[1] = fx, y[1] = fy;
	while (h < t) {
		++h;
		for (int i = 0; i < 8; ++i) {
			int nx = x[h] + dx[i], ny = y[h] + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && star[nx][ny] == '*') {
				++t;
				x[t] = nx, y[t] = ny;
				star[nx][ny] = '.';
				++ans;
			}
		}
	}
	return ans;
}

int main() {
	freopen("star.in","r",stdin);
	freopen("star.out","w",stdout);
	int maxn = -1;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> star[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (star[i][j] == '*') {	
				num[++cnt] = BFS(i, j);
				++tot[num[cnt]];
				maxn = max(maxn, num[cnt]);
				if (tot[num[cnt]] == 1) ++ans;
			}
		}
	}
	cout << ans << " ";
	ans = 0;
	for (int i = 1; i <= cnt; ++i) {
		ans = max(tot[num[i]] * num[i], ans);
	}
	cout << ans << endl;
	return 0;
}
/*
5 7
*......
..**..*
.*...*.
...*...
....*..
*/
```
虽然很丑，但自测是通过的。

- ## 原题链接

<https://www.luogu.com.cn/problem/P6566>

- ## 大体思路

由于看到```包含的星星数量相同的星座被视为一个星系（一个星系中的星座不一定相邻），星系的大小为星系中包含的所有星星数量。```这一句话发现要求星系的大小/数量 都是要先求出星座的的数量和星座里的星星个数，所以我们先来考虑怎么求关于星座的东西。

- ### 怎么求星座的星星个数

我们读完题发现星座的星星个数就是一群八连通的星星“合成的”，于是我们就想到求星座的星星个数就是来求八连通的连通块中的节点个数。

那么怎么求连通块中的节点个数呢？

我们想到了BFS（不会BFS的朋友[戳这里](https://blog.csdn.net/qq_35323001/article/details/52456557)）。

那么求连通块中的节点个数，我们可以：

1. 定义一个整数ans，充当计算节点个数的计数器，但是ans的初始值一定要置1，因为广搜时是不会扫到起点的，而起点也是这个连通块中的一部分。而且每次拓展到一个节点ans就加1。

2. 但是你要记住这个题目是八连通，所以你不要习以为常的写成四连通哦。

3. ~~没有别的需要特别注意的了~~

就这样，我们求出了星座的星星个数。

- ### 怎么求星座的数量

我们可以用一个字符类型的二维数组$\operatorname{star}$，$\operatorname{star}[i][j]$就是第$i$行第$j$列的字符（就是输入给出的那个图），后面广搜的时候扫到了这个$(i,j)$我们就将$\operatorname{star}[i][j]$置成`.`。然后我们一个一个枚举$i$和$j$($1\leq i\leq n,1\leq j\leq m$)，那么如果$\operatorname{star}[i][j]$还是`*`的话，就以$i,j$为起点广搜。

广搜代码：

```cpp
int BFS (int fx, int fy) {
	star[fx][fy] = '.';
	int ans = 1;
	int h = 0, t = 1;//由于怕用STL-queue出一些问题，所以用的手写队列（但貌似这里不会出问题）
	x[1] = fx, y[1] = fy;//x和y数组定义成了全局变量，又是因为怕MLE
	while (h < t) {//后面的基本上是广搜模板了
		++h;
		for (int i = 0; i < 8; ++i) {
			int nx = x[h] + dx[i], ny = y[h] + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && star[nx][ny] == '*') {
				++t;
				x[t] = nx, y[t] = ny;
				star[nx][ny] = '.';
				++ans;
			}
		}
	}
	return ans;
}
```

另外还有八连通方向的数组：

```cpp
const int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};//细心一点枚举应该不会写错
```

- ### 怎么求星系的数量

我们用类似桶排序的思想来做（因为这里的星座星星数是不超过100000）：

我们用一个数组tot来作桶，```tot[i]```表示星座星星数为```i```的星座数量。然后定义一个整型变量cnt和一个数组num，每次发现可以BFS时加1，然后将```num[cnt]```置为```BFS(x,y)```（简单来说```num[cnt]```就是星星数为```cnt```编号为```cnt```的星座星星数量）。

- ### 怎么求最大星系的大小

我们在求星系数量的操作做完后，定义maxn，maxn就是最大星系的大小。

- maxn怎么求

$$\operatorname{maxn} = \max_{i=1}^{n}{num_i\times tot_{num_{i}}}$$
这里的num和tot就是上文中的意思。

- ### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

int n, m, num[300005], tot[100005], cnt, x[300005], y[300005];
int ans;
char star[1505][1505];

int BFS (int fx, int fy) {//广搜部分
	star[fx][fy] = '.';
	int ans = 1;
	int h = 0, t = 1;
	x[1] = fx, y[1] = fy;
	while (h < t) {
		++h;
		for (int i = 0; i < 8; ++i) {
			int nx = x[h] + dx[i], ny = y[h] + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && star[nx][ny] == '*') {
				++t;
				x[t] = nx, y[t] = ny;
				star[nx][ny] = '.';
				++ans;
			}
		}
	}
	return ans;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> star[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (star[i][j] == '*') {	
				num[++cnt] = BFS(i, j);//将num[cnt]置为BFS(i, j)
				++tot[num[cnt]];
				if (tot[num[cnt]] == 1) ++ans;
			}
		}
	}
	cout << ans << " ";
	ans = 0;//由于懒得定义一个新的maxn，就将现有的ans置为0，循环利用
	for (int i = 1; i <= cnt; ++i) {
		ans = max(tot[num[i]] * num[i], ans);
	}
	cout << ans << endl;//输出
	return 0;
}
```

# The end

---

## 作者：__Watcher (赞：1)

实在想不通为什么第二题能和第三题一个难度，这题明显简单好吧~

---

全局思路：模拟 

局部思路：并查集+桶

---

全局思路：

将位于一个星座内的星星合并，这样子就得到了每一个星座内星星的数量。再把包含星星数量的星座合并，就能得到包含 $k$ 颗星星的星座数 $p(k)$。统计所有 $p(k)\ne0$ 的 $k$ 的数量，并求出 $p(k)\times k$ 的最大值。（这就是星系内星星数量）。

---

局部思路1：并查集

将所有位于同一个星座内的星星合并到其中一个节点上，并且只需维护星座内的星星数量，可以考虑使用并查集。

下面给吃并查集部分的代码，学过并查集的同学很容易理解：

```cpp
int dx[]={1, 1, 1, 0, 0, -1, -1, -1};
int dy[]={1, 0, -1, 1, -1, 1, 0, -1};

int find(int x) {
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}

int main() {
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(c[i][j]!='*') continue;
			for(int k=0;k<8;k++) {
				int xx=i+dx[k];
				int yy=j+dy[k];
				if(xx<1||yy<1||xx>n||yy>m||c[xx][yy]!='*') continue;
           			//g(x,y)：一个二维坐标到整数的映射
				int x=find(g(i,j)), y=find(g(xx,yy));
				if(x!=y) f[x]=y;
			}
		}
	}
}
```

---

局部思路2：桶

并查集后我们得出了以星座标号为关键字，星星数量为元素的一个桶。我们要求出以星星数量为关键字，星座数量为元素的桶。这种转换，通常需要一个辅助数组。这一部分思维难度较低，实现难度较高 ~~（其实也很低）~~。建议写不出来再来这里瞄代码。

```cpp
for(int i=1;i<=n;i++) {
	for(int j=1;j<=m;j++) {
		if(c[i][j]!='*') continue;
		cnt[f[g(i,j)]]++;//以星座标号为关键字，星星数量为元素的一个桶
	}
}
for(int i=1;i<=n;i++) {
	for(int j=1;j<=m;j++) {
		if(c[i][j]!='*') continue;
		if(f[g(i,j)]!=g(i,j)) continue;
		p[cnt[g(i,j)]]++; //以星星数量为关键字，星座数量为元素的桶
		maxn=max(maxn, cnt[g(i,j)]);
	}
}	
int ans=0;
for(int i=1;i<=maxn;i++) {
	if(p[i]) tot++;
	ans=max(ans, p[i]*i);
}
```

---

整体实现技巧：

二维左边映射成整数

方向数组（即 $dx,dy$）的建立

---
 
完整代码，仅供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int read() {
	int x=0, f=1; char ch=' ';
	while(!isdigit(ch)) {ch=getchar(); if(ch=='-') f=-1;}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x*f;
}
int n, m, f[3000000], cnt[3000000], tot, maxn, p[3000000];
int dx[]={1, 1, 1, 0, 0, -1, -1, -1};
int dy[]={1, 0, -1, 1, -1, 1, 0, -1};
int g(int x, int y) {
	return (x-1)*m+y-1;
}
int find(int x) {
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
char c[1505][1505];
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		scanf("%s", c[i]+1);
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			f[g(i,j)]=g(i,j);
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(c[i][j]!='*') continue;
			for(int k=0;k<8;k++) {
				int xx=i+dx[k];
				int yy=j+dy[k];
				if(xx<1||yy<1||xx>n||yy>m||c[xx][yy]!='*') continue;
				int x=find(g(i,j)), y=find(g(xx,yy));
				if(x!=y) f[x]=y;
			}
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			f[g(i,j)]=find(g(i,j));
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(c[i][j]!='*') continue;
			cnt[f[g(i,j)]]++;
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(c[i][j]!='*') continue;
			if(f[g(i,j)]!=g(i,j)) continue;
			p[cnt[g(i,j)]]++; 
			maxn=max(maxn, cnt[g(i,j)]);
		}
	}
	int ans=0;
	for(int i=1;i<=maxn;i++) {
		if(p[i]) tot++;
		ans=max(ans, p[i]*i);
	}
	cout<<tot<<" "<<ans;
}

```


---

## 作者：pengyule (赞：1)

这道题考察的知识点是 BFS，宽度优先搜索，基本上可以算是模板题了吧。分支是连通块，这道题的核心，在于求连通块的大小。

### 简述 DFS 思路
如果你用的是 DFS，那么正确的思路应该是：
- 找到一个星星，想办法去找到他所在的星座，把星座中的每一个星星都标记一下。以后，重复这一步的时候，如果你找到的星星已经被标记过了，那么你就可以跳过这颗星星了，否则会把同一个星座算两次。
- 建立一个数组，$Stars_i$ 表示在当前，星座中星星总数为 $i$ 的星座数有 $Stars_i$ 个。这样，$i\times Stars_i$ 就可以代表一个星系的星星数量，其中这个星系含有 $Stars_i$ 个星星数为 $i$ 的星座。
- 对每一个星系的星星个数取 $\max$，可以得到最大星系的星星个数；逐一枚举星系的星星个数，判断这样的星系是否存在，如果存在则计数一次，那么可以得出星系的数量。因为给出了星系大小的数据范围，我们可以从 $1$ 到 $100000$ 枚举，且不会超时。
- 在寻找星座大小的时候，往找到的这个星星的八连通方向按一定的次序分别尝试，知道走不了了再回头找其他的出路，把每一个经过的点标记一次，以免后面重复计数，统计所有走过的点，可以得出星座的大小。

### BFS 解法
其实，连通块用 BFS 更好一些。前面的思路与 DFS 思路相同，对于这个找到的星星，我们把他的八连通的坐标分别加入队列，再根据这八个点继续去把他们的八连通拿出来，再对这些点继续这样操作……直到发现八连通不再是星星。每取出一个点，说明它是这个星座中的一个星星，我们需要计数一次。最后计数到的数量，就是星座中的星星个数。其余与上面的相同，不再赘述。

### BFS 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>//避免万能头文件被卡
using namespace std;
int n,m,cnt=0;
long long ans=0;//避免超出int范围
char a[1510][1510];//用来存星空
int book[1510][1510];//用来标记那些星星我们已经找过他的星座了
int Stars[100010];//如题所述，统计大小为i的星座有多少个
struct node
{
	int x,y;//BFS的结构体，所在第几行，第几列
}q[2250010],temp;
int dx[8]={1,-1,0,0,1,-1,1,-1};
int dy[8]={0,0,1,-1,1,-1,-1,1};
  //方向数组，往八连通扩展
int bfs(int p0,int q0)//找到的这一颗星星的坐标是(p0,q0)
{
	int head=1,tail=1,Size_=0;
	q[tail].x=p0,q[tail].y=q0;
	book[p0][q0]=1;
	tail++;//把这颗小星星标记，并加入队列
	while(head<tail)
	{
		Size_++;//星座的大小加一
		temp=q[head];
		for(int i=0;i<8;i++)
		{
			if(temp.x+dx[i]>=1 && temp.x+dx[i]<=n && temp.y+dy[i]>=1 && temp.y+dy[i]<=m//不能越界
			 && a[temp.x+dx[i]][temp.y+dy[i]]=='*' && book[temp.x+dx[i]][temp.y+dy[i]]==0)//要是星星，且不重复加入队列
			{
				book[temp.x+dx[i]][temp.y+dy[i]]=1;
				q[tail].x=temp.x+dx[i],q[tail].y=temp.y+dy[i];
				tail++;
			}
		}
		head++;//把当前操作的星星出队，不然死循环
	}
	return Size_;//返回星座大小
}
int main()
{
	//freopen("star.in","r",stdin);
	//freopen("star.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		getchar();
		for(int j=1;j<=m;j++)
			a[i][j]=getchar();
	}//读入，注意要把换行符getchar()掉
	int w;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='*' && book[i][j]==0)
			{//如果是星星，并且没有找过他
				w=bfs(i,j);//获取到星座大小
				Stars[w]++;//又多了一个大小是w的星座
			}
		}
	}
	for(int i=1;i<=100000;i++)
		if(Stars[i]!=0)//如果存在大小是i的星座
		{
			cnt++;//那么他们可以组成一个星系
			ans=max(ans,(long long)(i*Stars[i]));
  //更新最大星系
		}
	printf("%d %d",cnt,ans);
	return 0;
}
```
希望对你有帮助，谢谢观看！

---

## 作者：oimaster (赞：1)

## Part1 前言

NOI Online3 比 NOI Online2 良心！

## Part2 题面

这道题的题面有点绕，我来再总结一下：

- 一颗星星旁边所有的星星跟这颗星星是同一个星座。
- 同样大小（星星数量相同）的星座叫做星系，这些星座不必连接。
- 求出一共有多少个星系和最大的星系大小。

## Part3 思路

数据范围很小，天空最大有 $1500 \times 1500$，可以使用搜索的方法来做。深搜的方法可以是递归，每次扫描这个星星周围的所有星星，当旁边所有的地方都不是星星或已经扫过了，就停止。宽搜其实就是队列，“拉网式搜索”，跟深搜差不多，扫描周围的星星，当有一颗没扫描过的星星就放入队列。

我们发现，深搜的层数与宽搜队列长度仅有 $100000$，不可能得到 `MLE` 的结果。然后再看时间。深搜与宽搜最惨**总时间复杂度**为 $\operatorname{O}\left(NM\right)$，也就是 $1500 \times 1500$，不会超。外部套一个枚举起始点，对时间复杂度没有影响。

## Part4 代码

给出深搜的代码（宽搜作者其实不太熟，怕被喷就不挂上了）：

```cpp
#include<iostream>
#include<cstdio> 
#include<set>
#include<map>
using namespace std;
int n,m;
char c[1501][1501];
int cnt;
int mo[3][9]={{0,0,0,0,0,0,0,0,0},{0,1,1,1,0,-1,-1,-1,0},{0,-1,0,1,1,1,0,-1,-1}};
void dfs(int i,int j){
	++cnt;
	c[i][j]='.';
	for(int k=1;k<=8;++k){
		int nx=i+mo[1][k];
		int ny=j+mo[2][k];
		if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&c[nx][ny]=='*')
			dfs(nx,ny);
	}
}
int main(){
	freopen("star.in","r",stdin);
	freopen("star.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			cin>>c[i][j];
	int maxv=0;
	set<int>s;
	map<int,int>ma;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(c[i][j]=='*'){
				cnt=0;
				dfs(i,j);
				ma[cnt]+=cnt;
				maxv=max(maxv,ma[cnt]); 
				s.insert(cnt);
			}
	cout<<s.size()<<' '<<maxv<<endl;
	return 0;
}
```

不要喷我qwq

## Part5 结语

其实，看到这道题的时候数据范围小，只管爆搜。接下来，我给大家赠上一个给大家参考的数据范围与算法关系的表：

| 100以下 | 100~500                            | 501~8000                           | 8001~500000                            | 500000以上                                                   |
| ------- | ---------------------------------- | ---------------------------------- | -------------------------------------- | ------------------------------------------------------------ |
| 搜索    | $\operatorname{O}\left(N^3\right)$ | $\operatorname{O}\left(N^2\right)$ | $\operatorname{O}\left(N\log N\right)$ | $\operatorname{O}\left(N\right)$ 或 $\operatorname{O}\left(1\right)$ |

---

