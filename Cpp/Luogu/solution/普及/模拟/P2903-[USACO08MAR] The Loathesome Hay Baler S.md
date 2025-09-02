# [USACO08MAR] The Loathesome Hay Baler S

## 题目描述

Farmer John 新买的干草打包机的内部结构大概算世界上最混乱的了，它不像普通的机器一样有明确的内部传动装置，而是 $N$ 个齿轮互相作用，每个齿轮都可能驱动着多个齿轮。 FJ 记录了对于每个齿轮 $i$，记录了它的 $3$ 个参数，以一个三元组 $(x,y,r)$ 表示，$x$ 和 $y$ 表示齿轮中心的位置坐标，$r$ 表示该齿轮的半径。

驱动齿轮的位置为 $(0,0)$，并且 FJ 也知道最终的工作齿轮位于 $(X_t,Y_t)$。 驱动齿轮顺时针转动，转速为 $10,000$ 转/小时。你的任务是，确定传动序列中所有齿轮的转速。传动序列的定义为，能量由驱动齿轮传送到工作齿轮的过程中用到的所有齿轮的集合。对能量传送无意义的齿轮都应当被忽略。

在一个半径为 $R_d$，转速为 $S$ 转/每小时的齿轮的带动下，与它相接的半径为 $R_x$ 的齿轮的转速将为 $-S\times \frac{R_d}{R_x}$ 转/小时。$S$ 前的负号的意思是，一个齿轮带动的另一个齿轮的转向会与它的转向相反。

FJ 只对整个传动序列中所有齿轮速度的绝对值之和感兴趣，你的任务也就相应转化成求这个值。机器中除了驱动齿轮以外的所有齿轮都被另外某个齿轮带动，并且不会出现 $2$ 个不同的齿轮带动同一个齿轮的情况。

## 样例 #1

### 输入

```
4 32 54 
0 0 10 
0 30 20 
32 54 20 
-40 30 20 
```

### 输出

```
20000 
```

# 题解

## 作者：HiJ1m (赞：12)

这个题数据范围N<=1050 ， O(N²)的BFS，每次逐个计算两个齿轮的距离 ，实现过程很容易。

具体细节见代码注释。

P.S. 齿轮转的方向和结果好像没什么关系，于是我算的时候就没取相反数。

```cpp
//Bzoj1615 麻烦的干草打包机
#include<bits/stdc++.h>
#define MAXN 1084
struct cycle{
    int x,y,r;
}a[MAXN];
using namespace std;
int N,xt,yt,st,ed,p[MAXN];
double s[MAXN],ans;
bool vis[MAXN];
void BFS()
{
    queue<int>q;    
    vis[st]=1,s[st]=10000;                    //初值
    q.push(st);
    while(!q.empty())
    {
        int tmp=q.front();q.pop();
        for(int i=1;i<=N;i++)
        {
            if(vis[i])continue;
            if((a[tmp].x-a[i].x)*(a[tmp].x-a[i].x)+(a[tmp].y-a[i].y)*(a[tmp].y-a[i].y)==(a[i].r+a[tmp].r)*(a[i].r+a[tmp].r))
            {                                 //上面这行是判断  距离的平方 是否等于 两齿轮半径和的平方         
                vis[i]=1;
                double t=a[tmp].r*1.0/a[i].r;                //计算
                s[i]=s[tmp]*t; 
                p[i]=tmp;                                                         //这里说一下这个p数组是记路径用的，方便加和。
                if(i==ed)return ;                                              //跳出
                q.push(i);
            } 
        }
    }
}
int main()
{
    scanf("%d%d%d",&N,&xt,&yt);
    for(int i=1;i<=N;i++){
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].r);
        if(a[i].x==0&&a[i].y==0)st=i;
        if(a[i].x==xt&&a[i].y==yt)ed=i;    //存一下开始和结尾的位置
    }
    BFS();
    for(int i=ed;i;i=p[i])
        ans+=s[i];
    printf("%d",(int)ans);                               //这个地方要取整，四舍五入会WA30
    return 0;
} 
博客链接http://www.cnblogs.com/Elfish/p/7634159.html
```

---

## 作者：jijiaze (赞：9)

还记得[我的第一篇题解](https://www.luogu.com.cn/blog/jijiaze/p2903)吗？

我觉得还是有点不足之处，比如 a\[ \]的用法没有细讲。

### 注意，a\[ \]是用来记路径用的。

![](https://cdn.luogu.com.cn/upload/image_hosting/jwlvvl0j.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在上面这个例子中，A 是驱动轮（起始轮），C 是工作轮（终止轮），那么 a\[B\]=a\[C\]=a\[D\]=A，而计算时，只用到 a\[C\]=A（还有 a\[A\]=0）。

让我们再加一些齿轮。

![](https://cdn.luogu.com.cn/upload/image_hosting/9n5ploc6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在这里，A 是驱动轮（起始轮），U 是工作轮（终止轮），那么 a\[P\]=a\[Q\]=C，a\[R\]=a\[S\]=P，a\[T\]=a\[U\]=R。但是，程序运行时，i 从 U 开始，一直到 0 结束。（参见下表）

| i | a\[i\] |
| :----------: | :----------: |
| U | R |
| R | P |
| C | A |
| A | 0 |

这样就可以解决路径问题了。


最后附上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define l 1111//数组长度
double jl(int _x1,int _y1,int _x2,int _y2){
    return sqrt(pow((_x1-_x2)*1.0,2)+pow((_y1-_y2)*1.0,2));
}//计算平面上两点的距离
struct chilun{
    int x,y,r;
    double v;
    void input(){
        cin>>x>>y>>r;
    }//输入简化
    bool operator!=(const chilun o) const{
        return x!=o.x || y!=o.y;
    }//判断两个chilun类型的是否不等
    bool operator==(const chilun o) const{
        return x==o.x && y==o.y;
    }//判断两个chilun类型的是否相等
}cl[l];//结构体—齿轮
/*
x和y表示该齿轮的中心在点(x,y)
r表示齿轮的半径
v表示齿轮的转速
*/
bool check(int _i,int _j){
    if(cl[_i].r+cl[_j].r==jl(cl[_i].x,cl[_i].y,cl[_j].x,cl[_j].y)) return true;
    return false;
}
bool check(chilun a,chilun b){
    if(a.r+b.r==jl(a.x,a.y,b.x,b.y)) return true;
    return false;
}
//这两个函数是用来判断两个齿轮是否能连接（我用了重载）
int n,xt,yt,k,w,vis[l],a[l];
/*
n、xt、yt如题
k和w分别是用来标记起始齿轮和终点齿轮的
vis[i]表示齿轮i是否被搜过（1表搜过，0表没有）
a[]标记路径
*/
double s=0;//速度和
queue<int> q;//bfs专属队列
void bfs(int d){
    cl[d].v=10000.0;
    vis[d]=1;
    q.push(d);//将cl[d]入队
    while(!q.empty()){//当队列非空时做
        int p=q.front();
        q.pop();
        for(int i=1;i<=n;i++){
            if(vis[i]) continue;//剪枝
            if(check(p,i)){
                vis[i]=1;//标记
                cl[i].v=cl[p].r*cl[p].v*1.0/cl[i].r;//计算转速
                a[i]=p;//记录路径
                if(i==w) return;//搜到了直接返回
                q.push(i);//入队
            }//如果队头结点（齿轮p）和齿轮i能连接时做
        }
    }
}
int main() {
    memset(vis,0,sizeof(vis));
    memset(a,0,sizeof(a));//初始化
    cin>>n>>xt>>yt;//输入
    for(int i=1;i<=n;i++){
        cl[i].input();//输入—见上
        if(cl[i].x==0 && cl[i].y==0) k=i;
        if(cl[i].x==xt && cl[i].y==yt) w=i;
        //标记
    }
    bfs(k);//搜索起始齿轮
    for(int i=w;i;i=a[i]) s+=cl[i].v;//求和
    cout<<(int)s;//取整输出答案
    return 0;//完美结束
}
```

---

## 作者：封禁用户 (赞：6)

update：2022/11/25 优化 $\LaTeX$，行末加上句号，给读者更好的阅读体验。

题解区大多是 bfs 欸，我发个 dfs 吧。

前置知识：基础搜索。

注意到一点，齿轮的方向与结果无关，这样就不用去管方向，直接 dfs。

思路就是计算齿轮之间的距离，进行 dfs。时间复杂度 $O(n^2)$。

具体注意点：

1. 如何判断两个齿轮相切？

我们知道，如果两个齿轮的距离小于等于它们半径之和，就说明它们相切。

具体代码：

```cpp
bool check(int x_1,int y_1,int r_1,int x_2,int y_2,int r_2){//计算两齿轮是否相切 
	if((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)<=(r_1+r_2)*(r_1+r_2)) return true;
	else return false;
}
```

2. 具体如何 dfs？

首先，设定递归边界。如果搜到了题目中代表结束的齿轮，即 $x=x_t,y=y_t$，那么代表搜到了终点，结束递归。

然后，逐个判断两齿轮是否相切。如果相切，就递归 dfs。

主函数中具体从哪里调用呢？要从起始齿轮开始搜索，即 $x=0,y=0$ 的齿轮。

具体代码：

```cpp
void dfs(int p){//深搜 
	if(p==ed) return;//找到工作齿轮，退出 
	for(int i=1;i<=n;i++){
		if(check(c[p].x,c[p].y,c[p].r,c[i].x,c[i].y,c[i].r)==true&&(!vis[i]))//如果相切并且为搜到 
		{
			vis[i]=1;//把下一个要搜的点堵住 
			v[i]=v[p]*c[p].r/c[i].r;//计算 
            ans[i]=ans[p]+v[i];
            dfs(i);//递归搜索 
            vis[i]=0;//搜完了，解封 
		}
	}
}
```

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1100;

struct node{//齿轮结构体 
	int x,y,r;
}c[maxn];

double v[maxn],ans[maxn];//齿轮距离数组和答案数组 
bool vis[maxn];//bool数组用来判重 
int n,xt,yt,st,ed;

bool check(int x_1,int y_1,int r_1,int x_2,int y_2,int r_2){//计算两齿轮是否相切 
	if((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)<=(r_1+r_2)*(r_1+r_2)) return true;
	else return false;
}
void dfs(int p){//深搜 
	if(p==ed) return;//找到工作齿轮，退出 
	for(int i=1;i<=n;i++){
		if(check(c[p].x,c[p].y,c[p].r,c[i].x,c[i].y,c[i].r)==true&&(!vis[i]))//如果相切并且为搜到 
		{
			vis[i]=1;//把下一个要搜的点堵住 
			v[i]=v[p]*c[p].r/c[i].r;//计算 
            ans[i]=ans[p]+v[i];
            dfs(i);//递归搜索 
            vis[i]=0;//搜完了，解封 
		}
	}
} 
int main(){
	cin>>n>>xt>>yt;//读入 
	for(int i=1;i<=n;i++){
		cin>>c[i].x>>c[i].y>>c[i].r;
		if((!c[i].x)&& (!c[i].y==0)) st=i;//找到了原始齿轮 
		if(c[i].x==xt && c[i].y==yt) ed=i;//找到了工作齿轮 
	}
	v[st]=10000;
	ans[st]=10000;
	vis[st]=1;
	dfs(st);
	cout<<(int)ans[ed];//答案只要输出整数部分哦 
} 
```

---

## 作者：jijiaze (赞：5)

这题数据范围$n \leq 1050$，基本 dfs 搞定。~~但我还是用了 bfs 。~~

判断每个齿轮是否能连接。

用了楼上两位大佬的——不取相反数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define l 1111//数组长度
double jl(int _x1,int _y1,int _x2,int _y2){
	return sqrt(pow((_x1-_x2)*1.0,2)+pow((_y1-_y2)*1.0,2));
}//计算平面上两点的距离
struct chilun{
	int x,y,r;
	double v;
	void input(){
		cin>>x>>y>>r;
	}//输入简化
	bool operator!=(const chilun o) const{
		return x!=o.x || y!=o.y;
	}//判断两个chilun类型的是否不等
	bool operator==(const chilun o) const{
		return x==o.x && y==o.y;
	}//判断两个chilun类型的是否相等
}cl[l];//结构体—齿轮
/*
x和y表示该齿轮的中心在点(x,y)
r表示齿轮的半径
v表示齿轮的转速
*/
bool check(int _i,int _j){
	if(cl[_i].r+cl[_j].r==jl(cl[_i].x,cl[_i].y,cl[_j].x,cl[_j].y)) return true;
	return false;
}
bool check(chilun a,chilun b){
	if(a.r+b.r==jl(a.x,a.y,b.x,b.y)) return true;
	return false;
}
//这两个函数是用来判断两个齿轮是否能连接（我用了重载）
int n,xt,yt,k,w,vis[l],a[l];
/*
n、xt、yt如题
k和w分别是用来标记起始齿轮和终点齿轮的
vis[i]表示齿轮i是否被搜过（1表搜过，0表没有）
a[]标记路径
*/
double s=0;//速度和
queue<int> q;//bfs专属队列
void bfs(int d){
	cl[d].v=10000.0;
	vis[d]=1;
	q.push(d);//将cl[d]入队
	while(!q.empty()){//当队列非空时做
		int p=q.front();
		q.pop();
		for(int i=1;i<=n;i++){
			if(vis[i]) continue;//剪枝
			if(check(p,i)){
				vis[i]=1;//标记
				cl[i].v=cl[p].r*cl[p].v*1.0/cl[i].r;//计算转速
				a[i]=p;//记录路径
				if(i==w) return;//搜到了直接返回
				q.push(i);//入队
			}//如果队头结点（齿轮p）和齿轮i能连接时做
		}
	}
}
int main() {
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));//初始化
	cin>>n>>xt>>yt;//输入
	for(int i=1;i<=n;i++){
		cl[i].input();//输入—见上
		if(cl[i].x==0 && cl[i].y==0) k=i;
		if(cl[i].x==xt && cl[i].y==yt) w=i;
		//标记
	}
	bfs(k);//搜索起始齿轮
	for(int i=w;i;i=a[i]) s+=cl[i].v;//求和
	cout<<(int)s;//取整输出答案
	return 0;//完美结束
}
```

---

## 作者：_caiji_ (赞：4)

首先输入，记录一下哪个齿轮的位置在 $(0,0)$，哪个在 $(x_t,y_t)$。

接着，为了避免多次判断两个齿轮相切而超时，我们可以预处理一个 $link_{i,j}$，表示第 $i$ 个齿轮是否和第 $j$ 个齿轮相切。

这部分直接 $O(n^2)$ 暴力即可，注意 $link_{i,i}$ 要 $=0$，不然 bfs 时会重复搜自己。

怎么判断两个齿轮是否相切？我们小学二年级都学过一种距离，叫「[欧几里得距离](https://baike.baidu.com/item/欧几里得度量/1274107?fromtitle=欧几里得距离&fromid=2701459&fr=aladdin)」。设两个点分别在 $(x_1,y_1)$ 和 $(x_2,y_2)$，那它们的距离就是：

$$dis=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$$

怎么把它运用到这道题上呢？很简单，如果两个齿轮的圆心的距离等于这两个齿轮的半径之和，就说这两个齿轮相切。

实际运用时，为了防止被卡精度，一般对等式两边开平方，也就是：

$$(x_1-x_2)^2+(y_1-y_2)^2=(r_1+r_2)^2$$

处理完 $link_{i,j}$，就可以直接暴力 bfs 了。

bfs 的结点记录三个东西：当前是哪一个齿轮，当前齿轮的速度，当前经过齿轮的总速度。

题目要求「绝对值之和」，那就忽视计算速度这个负号。

每次扩展结点时，要选没扩展过而且与它相切的齿轮。

这样的 bfs，每个结点只会搜一次，每个结点要遍历一次 $1$ 到 $n$，时间复杂度为 $O(n^2)$。

最后输出答案要注意，直接向下取整，而不是四舍五入。

代码实现：
```cpp
#include <queue>
#include <cstdio>
using namespace std;
int f(int a){return a*a;}//开平方函数，用 define 会计算很多次，不推荐
struct Roller{
    int x,y,r;
    Roller(int a=0,int b=0,int c=0):x(a),y(b),r(c){}
    friend bool check(Roller a,Roller b){
    	return f(a.x-b.x)+f(a.y-b.y)<=f(a.r+b.r);//判断相切
    }
    friend bool operator==(Roller a,Roller b){
    	return a.x==b.x&&a.y==b.y;//判断相等
    }
} a[1060];
int n,si,ei,ex,ey;
bool vis[1060],link[1060][1060];//vis 记录这个齿轮有没有被扩展过
struct Node{
	int i;
    double v,tot;//float 已死
    Node(int a,double c,double d):i(a),v(c),tot(d){}
};
queue<Node> q;
int bfs(){
    q.push(Node(si,10000.0,10000.0));
    vis[si]=1;//搜索记得标记起点
    while(!q.empty()){
        Node now=q.front();q.pop();
        if(now.i==ei) return (int)now.tot;//向下取整
        for(int i=1;i<=n;i++){
            if(!vis[i]&&link[now.i][i]){
                vis[i]=1;
                double v=now.v*(1.0*a[now.i].r/a[i].r);//计算扩展的齿轮的速度，注意 *1.0
                q.push(Node(i,v,now.tot+v));
            }
        }
    }
    return -1;
}
int main(){
    scanf("%d%d%d",&n,&ex,&ey);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].r);
        if(a[i]==Roller(0,0)) si=i;
        if(a[i]==Roller(ex,ey)) ei=i;//记录头尾
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(check(a[i],a[j])) link[i][j]=link[j][i]=1;//预处理link[i][j]
        }
    }
    printf("%d",bfs());
    return 0;
}
```


---

## 作者：IcyFoxer_XZY (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P2903)

### 思路：
题目中有“不会出现2个不同的齿轮带动同一个齿轮的情况”，所以搜索可过，bfs时满足。

$\therefore (x[i]-x[j])^2+(y[i]-y[j])^2=(r[i]+r[j])^2$ 即可。

速度公式如下：

$v[i]=v[now] \times r[now] \div r[i]$ ， $ans[i]=ans[now]+v[i]$ 。

**code：**
```cpp
#include<stdio.h>
#include<queue>
#include<cmath>
#define N 1055
using namespace std;
int n;
int x[N],y[N],r[N];
double v[N],ans[N];
int tx,ty; 
int t;
queue<int> q;
int vis[N];
bool ok(int i,int j){
    return pow(x[i]-x[j],2)+pow(y[i]-y[j],2)==pow(r[i]+r[j],2);
}
void bfs(){//广搜 
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(register int i=1;i<=n;++i){
        	if(!ans[i]&&ok(i,now)){
                v[i]=v[now]*r[now]/r[i];
                ans[i]=ans[now]+v[i];
                q.push(i);//加入队列 
       		}
		}
    }
    printf("%d",(int)ans[t]);
}
int main(){
    scanf("%d%d%d",&n,&tx,&ty);
    for(register int i=1;i<=n;++i){
        scanf("%d%d%d",&x[i],&y[i],&r[i]);
        if(x[i]==tx&&y[i]==ty)t=i;
        if(x[i]==0&&y[i]==0){
            vis[i]=1;
            q.push(i);//加入队列 
            v[i]=10000,ans[i]=10000;//重新赋值 
        }
    }
    bfs();
    return 0;
}
```
Bye！

---

## 作者：N_o_N_a_m_e (赞：2)

普通的bfs

先判断每个齿轮能连接的齿轮然后bfs

用了楼上大佬的不取相反数

```cpp
#include<iostream>
#include<queue>
#include<cmath>
using namespace std;

int n,fx,fy,x[1055],y[1055],r[1055],sNo,fNo,Map[1055][1055],num[1055];
/*fx,fy是目标齿轮的坐标,sNo是初始齿轮下标,fNo是目标齿轮下标
Map[i][j]是下标为i的齿轮所连接的第j个齿轮,num[i]是下标为i的齿轮所连接的齿轮个数*/
bool vis[1055];

struct Node
{
	int No;//齿轮号 
	double v,sum;//齿轮速度,当前速度和 
};

queue<struct Node> que;

void judge()
{
	for(int i=1;i<=n;i++)//从第1个齿轮到最后一个齿轮 
	{
		for(int j=i+1;j<=n;j++)//i+1之前的已经处理了,从第i+1个开始 
		{
			int dis=0;//每次必须先赋值为0 
			double dist;
			dis+=(x[i]-x[j])*(x[i]-x[j]);//dis加i,j的x差的平方 
			dis+=(y[i]-y[j])*(y[i]-y[j]);//dis加i,j的y差的平方 
			dist=sqrt(dis);
			if(r[i]+r[j]>=dist)//如果i的半径加j的半径大于两点之间的距离 
			{
				num[i]++;//第i个齿轮连接的齿轮总数+1 
				num[j]++;//第j个齿轮连接的齿轮总数+1 
				Map[i][num[i]]=j;//第i个齿轮连接的齿轮加上j 
				Map[j][num[j]]=i;//第j个齿轮连接的齿轮加上i 
			}
		}
	}
}

void bfs()//普通bfs 
{
	struct Node now;
	now.No=sNo,now.v=10000,now.sum=10000;
	que.push(now);
	vis[sNo]=true;
	while(!que.empty())
	{
		struct Node now;
		now=que.front();
		que.pop();
		if(now.No==fNo)
		{
			cout<<(int)now.sum;
			return;
		}
		for(int i=1;i<=num[now.No];i++)
		{
			if(vis[Map[now.No][i]]) continue;
			struct Node next;
			next.No=Map[now.No][i];
			next.v=now.v*r[now.No]/r[Map[now.No][i]];//不用取相反数 
			next.sum=now.sum+next.v;
			que.push(next);
			vis[Map[now.No][i]]=true;
		}
	}
}

int main()
{
	cin>>n>>fx>>fy;//n个齿轮,fx,fy结束位置 
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i]>>r[i];
		if(!x[i]&&!y[i]) sNo=i;//找出开始位置,存入sNo 
		if(x[i]==fx&&y[i]==fy) fNo=i;//找出结束位置,存入fNo 
	}
	judge();//把能连接的齿轮连接 
	bfs();//广搜 
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很明显，各种齿轮看成是结点，驱动关系看成是边，那么最后这就是个森林，其中起点和终点在一棵树上。

我们只需要将起点设为根结点，进行深搜，就可以构造出这棵树。这里的时间复杂度是 $O(n^2)$。

然后，从终点往起点一步步向上爬，累加答案，最后不要四舍五入直接转 `int` 输出即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
#define max_n 1050
#define eps 1e-6
int n;
double ex,ey;
struct L{
	double x,y,r,v;
}a[max_n+2];
int s;
int t;
int fa[max_n+2];
double ans=0.00;
inline bool equal(double a,double b){
	return!(a-b>eps||b-a>eps);
}
inline double askdis(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void dfs(int u,int f){
	fa[u]=f;
	a[u].v=a[f].v*a[f].r/a[u].r;
	for(int v=1;v<=n;++v){
		if(askdis(a[u].x,a[u].y,a[v].x,a[v].y)<=a[u].r+a[v].r+eps&&v!=u&&v!=f)dfs(v,u);
	}
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P2903_1.in","r",stdin);
	freopen("P2903_1.out","w",stdout);
	#endif
	scanf("%d%lf%lf",&n,&ex,&ey);
	for(int i=1;i<=n;++i){
		scanf("%lf%lf%lf",&a[i].x,&a[i].y,&a[i].r);
		if(equal(a[i].x,0.00)&&equal(a[i].y,0.00))s=i;
		if(equal(a[i].x,ex)&&equal(a[i].y,ey))t=i;
	}
	memset(fa,0,sizeof(fa));
	a[0].r=a[s].r;
	a[0].v=10000.00;
	dfs(s,0);
	for(int u=t;u;u=fa[u])ans+=a[u].v;
	printf("%d\n",(int)ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/58870527)

By **dengziyue**

---

