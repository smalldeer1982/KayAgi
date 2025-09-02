# [USACO16DEC] Moocast S

## 题目描述

约翰农场主的 $N$ 头奶牛想建立一个紧急情况下的“哞哞广播”系统，这样它们就可以在自己中间广播重要信息。

奶牛们想让每头牛装备上一个对讲机，而不是在长距离中向另一头奶牛“哞哞”乱叫。这些对讲机每台都有各自的有效传输半径——一个拥有 $P$ 能量的对讲机只能向距离在 $P$ 以内的牛发送信息（注意可能出现 $A$ 牛对讲机的能量比 $B$ 牛的大，而 $A$ 牛可以给 $B$ 牛发送信息，但 $B$ 牛不能传回信息）。幸运的是，奶牛们可以通过其他奶牛中继，沿着一条跳跃的路径传递信息，因此每个奶牛不必要直接向每个其他奶牛传播。

由于对讲机的费堆成性质，来自一些奶牛的广播可能比其他奶牛的广播能够达到更多的接受者（考虑中继的情况）的能力更有效。请帮助奶牛确定来自单个奶牛的广播可以达到的奶牛的最大数量。

## 说明/提示

对于 $100\%$ 的数据，$N\le200$，$\forall i \in [1,N]$，$0\le x_i,y_i\le25000$。

## 样例 #1

### 输入

```
4
1 3 5
5 4 3
7 2 1
6 1 1```

### 输出

```
3```

# 题解

## 作者：OfstAutomataMachine (赞：13)

个人认为没有DFS的必要。

由于数据很小，所以不需要担心被卡，$O(n^3)$绰绰由余。

第一遍二重循环存边，第二遍Floyd，第三遍统计结果。（主要注释见代码）

第二遍和第三遍好像可以合起来，留作读者自行思考。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
struct pos{
	double x,y,p;//建议用double保留精度
} cow[201];
double dis(pos a,pos b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));//求两点的欧几里得距离
}
int n,ans,con[201][201];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>cow[i].x>>cow[i].y>>cow[i].p;
	for(int i=1;i<=n;i++)
		for(int l=1;l<=n;l++)
			con[i][l]=(dis(cow[i],cow[l])<=cow[i].p);//直接计算结果，返回1或0
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int l=1;l<=n;l++)
				con[i][l]=con[i][l]||con[i][k]&&con[k][l];//可以直接这样写，偷懒利器
	for(int i=1;i<=n;i++)
	{
		int vis=0;
		for(int l=1;l<=n;l++)
			vis+=con[i][l];
		ans=max(ans,vis);//统计结果，更新ans
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：MVP_Harry (赞：5)

一道并不是很难的题。观察到$n \le 200$，所以各种暴力都可以过。唯一要注意的一点就是A到B并不能保证B也到A，所以无法使用并查集，我用的是dfs，注释见代码。

```
#include<bits/stdc++.h>
using namespace std;

const int maxn = 205;
int ans, n;
int vis[maxn];

//结构体
struct node {
	int x, y, p;
}a[maxn];

//返回两点距离
double dis(node a, node b) { 
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

//搜索
void dfs(int cur) { //cur代表目前的位置
	for (int i = 1; i <= n; i++) {
		if (dis(a[cur], a[i]) <= a[cur].p && !vis[i]) { //判断条件：如果下一个顶点可以被达到，而且以前没有被达到过
			vis[i] = 1; //标记
			dfs(i); //递归
		}
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y >> a[i].p; //输入
	}
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		memset(vis, 0, sizeof(vis)); //别忘记清零
		vis[i] = 1;
		dfs(i);
		for (int j = 1; j <= n; j++) 
			if (vis[j]) cnt++;
		ans = max(ans, cnt);
	}
	cout << ans << endl;
	return 0;
}

---

## 作者：sxyugao (赞：4)

**题意**

求从一个点出发最多可以访问到的点数

**算法**

1、Floyd。

此解法详见其他题解。

2、DFS（我的方法）

不要轻视DFS，在本题中TA的效率为O(n^2)，而Floyd的效率仅为O(N^3)，碾压。

方法为从一个点出发DFS，搜到点就tot++，比较tot和ans。

存边时我采用的是邻接表，为了在DFS中减少循环。

至于处理能否到达，可以用一个巧妙的方法：

题目意思是如果sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]))<=p[i]成立，则 i 可以到 j，但小数运算十分讨厌，我们可以两边同时平方来处理，转变为sqr(x[i]-x[j])+sqr(y[i]-y[j])<=p[i]*p[i]。

以下为代码：
```cpp
#include<cstdio>
int n,ans,tot,x[205],y[205],p[205],edge[205][205];
bool v[205];
inline int sqr(int x){return x*x;}
void dfs(int k){
	if(v[k])return;
	v[k]=1;tot++;
	for(register int i=1;i<=edge[k][0];i++)dfs(edge[k][i]);
}
int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)scanf("%d%d%d",x+i,y+i,p+i);
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			if(sqr(p[i])>=sqr(x[i]-x[j])+sqr(y[i]-y[j]))
				edge[i][++edge[i][0]]=j;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++)v[j]=0;
		tot=0;
		dfs(i);
		if(tot>ans)ans=tot;
	}
	printf("%d",ans);
}
```

---

## 作者：yezl (赞：2)

[$ \color{orange}\text{博客食用效果更佳哦} $](https://www.luogu.com.cn/blog/into-the-unknow/solution-p3416)

### 题目大意：
有 $ N $ 头奶牛，第 $ i $ 头奶牛在坐标 $(x_i,y_i) $ 上，可以广播到半径 $ p_i $ 内的奶牛，且奶牛的广播可以传递。情况如图：[![](https://s3.ax1x.com/2020/11/20/DlE9ZF.png)](https://www.luogu.com.cn/user/318004)  
$ A $ 点的奶牛可以通过 $ B $ 点间接地广播到 $ C $ 点。给你这 $ N $ 头奶牛的坐标及其对应的广播距离 $ p $ ，要你求来自单个奶牛的广播可以达到的奶牛的最大数量。

### 思路分析：

对于这道题，首先看数据范围 $ N\le 200 $ 可谓非常小，只要你不天才地弄出一个 $ O(n!) $ 或 $ O(n^4) $ 的程序什么暴力算法都能过[~~（某蒟蒻的翻车日常）~~](https://www.luogu.com.cn/record/42249892)
，所以我们这里就直接用 $ \color{skyblue}\mathcal{dfs} $ 记忆化搜索跑一遍或者像其它巨佬一样打个 $ \color{skyblue}\mathcal{Floyd} $ 也可以，本蒟蒻这里就直接讲 $ \color{skyblue}\mathcal{dfs} $ 的啦：  
我们使用 $ v $ 数组对第 $ i $ 头奶牛能广播到的所有奶牛都标记为 $ \tt{true} $ ，标记完后统计一下，然后重置数组并对第 $ i+1 $ 头奶牛做同样的统计，每次统计完用 $ ans $ 取最大值就好啦。但是怎么计算两点之间的距离呢？~~有上过小学应该都知道~~，点 $ A $ 位于坐标 $ (x_1,y_1) $ ，点 $ B $ 位于坐标 $ (x_2,y_2) $ ，则 $ A,B $ 两点的距离为：
$$ range=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}  $$ 
对于实在不懂的同学，这里我就再画一个图吧（真的累QAQ）。
[![](https://cdn.luogu.com.cn/upload/image_hosting/mx61rguo.png)](https://www.luogu.com.cn/record/42249892)

不难看出这里A、B两点的距离直接根据[勾股定理](https://baike.baidu.com/item/%E5%8B%BE%E8%82%A1%E5%AE%9A%E7%90%86/91499?fr=aladdin)可以算出为 $ \sqrt{(7-3)^2+(5-2)^2}=5 $ 这下理解了吧。

那么话不多说，我就直接上程序啦。

 $ \mathcal{\Large My\;Code:} $


 ```c
#include<iostream>
#include<cstdio>
#include<cstring>//有memset用于初始化 
#include<cmath>//有sqrt(根号)函数
#include<algorithm>//有max用于取大的数 
using namespace std;//当然，上面头文件懒得打的可以直接用<bits/stdc++.h> 
const int N=205;//定义常变量 
int n,ans,sum,x[N],y[N],p[N];
bool v[N];//用于记录第 v[i] 头奶牛是否可以被广播到 
inline int read()//快读（但数据较小，貌似没什么用qwq） 
{
    int num=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        num=(num<<1)+(num<<3)+ch-'0';
        ch=getchar();
    }
    return num;
}
double range(int a,int b,int c,int d)//计算距离函数啦 
{
	return sqrt((a-b)*(a-b)+(c-d)*(c-d));
}
void dfs(int u)//u表示当前广播（传递）到的奶牛
{
	for(int i=1;i<=n;i++)
	{
		double len=range(x[u],x[i],y[u],y[i]);
		if(p[u]>=len && !v[i])//如果这个点在广播范围内并且还没被标记 
		{
			v[i]=true;//那么标记为 true 
			dfs(i);//以这个点开始往下递归，看可以传递到哪 
		}
	}
}
int main()
{
	n=read();//读入 
	for(int i=1;i<=n;i++)
		x[i]=read(),y[i]=read(),p[i]=read();
	for(int i=1;i<=n;i++)
	{
		v[i]=true,dfs(i);//它自己肯定先标记一下，然后开始递归 
		for(int j=1;j<=n;j++)//枚举每个点 
			if(v[j]==true)//如果可以被广播到 
				sum++;//当前奶牛可以广播到的奶牛数+1 
		ans=max(ans,sum);//每次循环完取一次最大值 
		sum=0,memset(v,0,sizeof(v)); //循环完记得要初始化哦 
	}
	printf("%d",ans);//输出 
	return 0;
}
```

谢谢观赏，希望可以帮到大家。

 $ \color{gray}\small\text{更新日志：2020.11.21\;\;及时发现并排除公式及语法错误} $ 

---

## 作者：qzcbw (赞：2)

## 题目分析
##### 思路1. 图论
~~（不用说了吧）~~
先判断如果可以直接到达，就将边设为1。
第二遍判断两点之间是否可以到达。
最后统计答案。
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,t,ans,f[201][201];
struct node{
	int x,y,w;
}a[201];
inline double js(node a,node b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main(){
	register int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(js(a[i],a[j])<=a[i].w) f[i][j]=1;
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(i!=j&&i!=k&&j!=k&&f[i][k]&&f[k][j]) f[i][j]=1;
	for(i=1;i<=n;i++){
		t=0;
		for(j=1;j<=n;j++)
			t+=f[i][j];
		ans=max(ans,t);
	}
	printf("%d",ans);
	return 0;
}
```
##### 思路2.dfs
其实思路不难，搜索后统计就行了。
关键点是在判断当下一个顶点可以被达到，而且以前没有被达到过时，就可以标记并递归。
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,t,ans,vis[201];
struct node{
	int x,y,w;
}a[201];
inline double js(node a,node b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline void dfs(register int x){
	register int i;
	for(i=1;i<=n;i++)
		if(js(a[x],a[i])<=a[x].w&&!vis[i]){
			vis[i]=1;
			dfs(i);
		}
}
int main(){
	scanf("%d",&n);
	register int i,j;
	for(i=1;i<=n;i++)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
	for(i=1;i<=n;i++){
		t=0;
		memset(vis,0,sizeof(vis));
		vis[i]=1;
		dfs(i);
		for(j=1;j<=n;j++)
			if(vis[j]) t++;
		ans=max(ans,t);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Viktley (赞：1)

**题目大意：**

有 $N$ 头奶牛，每一头有一个广播半径，问从任意一头牛开始最多能广播的头数！

------------

**思路：**

首先必须明白对于在二维空间中任意两点的距离用[欧氏距离](https://baike.so.com/doc/5347382-5582829.html)

那就转换成了一个求两点之间距离是否在范围之内的问题。

------------

**Code：**

```cpp
#include <cstdio> 
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e2 + 10;
int n, x[N], y[N], p[N], ans, tot;
bool e[N][N], vis[N];
void dfs(int u)  //模拟传播过程
{
	for(int i = 1; i <= n; i++)
		if(!vis[i] && e[u][i]) vis[i] = 1, tot++, dfs(i);
     //是否传播过，是否在当前点u的传播范围内
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &x[i], &y[i], &p[i]);
		for(int j = 1; j < i; j++)
		{
			double temp = sqrt((x[i] - x[j]) * (x[i] - x[j]) * 1.0 + (y[i] - y[j]) * (y[i] - y[j]) * 1.0);  //两点之间欧氏距离
			if(temp <= p[i] * 1.0) e[i][j] = 1; if(temp <= p[j] * 1.0) e[j][i] = 1;  //判断是否在范围内，注意是单向的
		}
	}
	for(int i = 1; i <= n; i++)  //枚举每个点为起点的情况
	{  
		memset(vis, 0, sizeof(vis));  //标记是否已广播过
		vis[i] = 1, tot = 1, dfs(i);	
		ans = max(ans, tot);  //打擂台求最优解
	}
	printf("%d", ans);  //输出答案
	return 0;   //撒花......
}
```

**PS：**
 1. 开始的牛也包括在这个数量中
 2. 不是在二维空间中有多少头牛能接收广播

---

## 作者：Hanriver (赞：1)

## 题面
[题面传送门](luogu.com.cn/probiem/P3416)
## 分析
用欧几里得两点间距离公式枚举每两头牛之间能否传输到，如果能的话连一条单向边，然后跑n遍dfs找到最大值即可。
## 代码实现
代码丑，将就着看吧（
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[201],y[201],k[201];//x,y存坐标,k存半径
bool b[201];//记录是否搜过
int maxn=0,s=1;
vector<int> q[201];
void dfs(int x)//经典图上深搜
{
	for(int i=0;i<q[x].size();i++)
	if(!b[q[x][i]])
	{
		b[q[x][i]]=1;
		s++;
		dfs(q[x][i]);
	}
	maxn=max(maxn,s);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&x[i],&y[i],&k[i]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		if(i!=j)//避免和自己连边增加复杂度
		{
			if(sqrt((double)(x[j]-x[i])*(double)(x[j]-x[i])+(double)(y[j]-y[i])*(double)(y[j]-y[i]))<=k[i])
			q[i].push_back(j);
		}
	}
	for(int i=1;i<=n;i++) 
	{
		b[i]=1;
		dfs(i);
		memset(b,0,sizeof(b));
		s=1;//注意初始化，要算上自己
	}
	printf("%d",maxn);
	return 0;
}
```


---

## 作者：羚羊WANG (赞：0)

相信大家看到这里的时候，对题目意思已经有了深刻的理解

题目让我们求一头奶牛到其它奶牛的路径和的最大值

**嗯？**

**这似乎好像就是一个floyd**

再看一眼数据

**$N \leq 200$**

妙啊

我们可以考虑用两个点之间的距离（哈夫曼距离），来预处理
出两个点之间的距离

再用一个$floyd$来跑图

最后枚举每一个点，求最大值即可

时间复杂度：$O(n^3)$

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
struct node{
	int x,y;
	int val;
}e[210];
double dis[210][210];
int f[210][210];
inline double check(int id_1,int id_2){
	return sqrt((e[id_1].x-e[id_2].x)*(e[id_1].x-e[id_2].x)+(e[id_1].y-e[id_2].y)*(e[id_1].y-e[id_2].y));
}
inline bool check1(int i,int j,int k){
	if(i==j || j==k || k==i)
		return false;
	return true;
}
int ans;
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		{
			e[i].x=read();
			e[i].y=read();
			e[i].val=read();
		}
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			dis[i][j]=check(i,j);
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			if(dis[i][j]<=e[i].val)
				f[i][j]=1;
	for(register int k=1;k<=n;++k)
		for(register int i=1;i<=n;++i)
			for(register int j=1;j<=n;++j)
				if(check1(i,j,k) && f[i][k] && f[k][j])
					f[i][j]=1;
	for(register int i=1;i<=n;++i)
		{
			int sum=0;
			for(register int j=1;j<=n;++j)
				if(f[i][j])
					sum++;
			ans=max(ans,sum);
		}
	write(ans);
	return 0;
}

```


---

## 作者：ConvaChen (赞：0)

第一篇题解qaq

看到没有JAVA题解于是就来提交一遍AC代码

AC代码 简单易懂 DFS

之前已经有大神解释过DFS，苣蒻就不多解释了，方便看不懂C++代码的JAVA同学观看

```java
import java.util.*;
public class TeleportationS {
	static int n;
	static int[][] C;
	static int[] M;
	static int ans;
	static double dis(int i, int j) {
		//计算欧式距离
		double dis = Math.pow((C[i][0]-C[j][0]), 2)+
				 Math.pow((C[i][1]-C[j][1]), 2);
		return Math.sqrt(dis);
	}
	static void dfs(int j) {
		//深度有限搜索，传进来一个j，然后看能牛j能不到牛i
		for(int i=0;i<n;i++) {
			if(dis(j,i)<=C[j][2]
					&&
					M[i]==0){
				M[i]=1;
				dfs(i);
			}
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		n = in.nextInt();
		C = new int[n][3];
		M = new int[n];
		for(int i=0;i<n;i++) {
			for(int j=0;j<3;j++) {
				C[i][j] = in.nextInt();
			}
		}
		for(int i=0;i<n;i++) {
			int cnt = 0;
			for(int j=0;j<n;j++) {
				M[j]=0;
			}
			M[i]=1;
			dfs(i);
			for(int j=0;j<n;j++) {
				if(M[j]==1) {
					cnt++;
				}
			}
			ans = Math.max(ans, cnt);
		}
		System.out.println(ans);
	}
	

}
```


---

## 作者：sycqwq (赞：0)

分析：

这是一道暴力的题

只要知道两点之间距离公式：

$(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)$

暴力枚举即可

第一遍枚举找到可以直接传输的奶牛

第二遍找可以间接传输的

第二遍有点Floyd的思想

```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int n;
struct
{
	int x,y,p;
}a[maxn];
int b[205][205];
int main(){
//	freopen("moocast.in","r",stdin);
//	freopen("moocast.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
        b[i][i]=1;
		cin>>a[i].x>>a[i].y>>a[i].p;
	}
	int s=0;
	for(int i=1;i<=n;i++)//第一遍
	{
		int t=0;
		for(int j=1;j<=n;j++)
		{
				int x1=a[i].x,y1=a[i].y,x2=a[j].x,y2=a[j].y;
//				cout<<sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)))<<' '<<a[i].p<<' ';
				if(ceil(sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))))<=a[i].p)//不知道不要向上取证会不会错，反正我加了
				{
					b[i][j]=1;
				}
		}
//		cout<<endl;
		s=max(s,t);
	}
	for(int i=1;i<=n;i++)//间接
	{
		int t=0;
		for(int j=1;j<=n;j++)//通过奶牛j
		{
            for(int k=1;k<=n;k++)//传输到奶牛k
                if(i!=j&&j!=k&&i!=k&&b[j][k]&&b[i][j])
                {
                   
                        b[i][k]=1;
                }
		}
        for(int j=1;j<=n;j++)
            t+=b[i][j];
//		cout<<endl;
		s=max(s,t);
	}
	cout<<s;
	return 0;
}
```

---

## 作者：Zenith_Yeh (赞：0)

看到范围 $1 \leq N \leq 200$，所以我们只需要用 $n^2$ 来看每两头奶牛能不能连边，再用 $Floyd$ 算最短路，最后看一头奶牛与其他奶牛的最短路可到达即可。

**上菜：**
```cpp
#include<bits/stdc++.h>
#define int long long//由于我们用的是平方比较，所以要开long long
#define read() Read<int>()
namespace pb_ds{//优美的快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
struct bb
{	int x,y,r;
}op[205];
int n,dis[205][205],maxn;
signed main()
{	memset(dis,0x3f,sizeof(dis));//初始化
	n=read();
	for(register int i=1;i<=n;++i)
	{	op[i].x=read(),op[i].y=read(),op[i].r=read();
		for(register int j=1;j<i;++j)
		{	int jl=(op[i].x-op[j].x)*(op[i].x-op[j].x)+(op[i].y-op[j].y)*(op[i].y-op[j].y);
			if(jl<=op[i].r*op[i].r)dis[i][j]=0;//判断是否能连边
			if(jl<=op[j].r*op[j].r)dis[j][i]=0;
		}
	}
	for(register int i=1;i<=n;++i)dis[i][i]=0;
	for(register int k=1;k<=n;++k)//Floyd
		for(register int i=1;i<=n;++i)
			for(register int j=1;j<=n;++j)
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
	for(register int i=1;i<=n;++i)
	{	int ans=0;
		for(register int j=1;j<=n;++j)//看最大连边奶牛
			if(dis[i][j]==0)ans++;
		maxn=max(maxn,ans);//取max
	}
	cout<<maxn;
	return 0;
}

```


---

## 作者：Ezis (赞：0)

首先我们从题目中得知，每头牛的对讲机的有效传输半径为一个圆心为 $\left(x[i],y[i]\right)$ 半径为 $p[i]$ 的圆。

这样我们就可以进行 $BFS$ 去查找当前位置上的牛所能传出到的所有牛了。

当然，也可以理解为这是一个 **变种** 的连通块，每次可以跳到一个与当前点的 **欧几里得距离** $ \leq p[i]$ 的位置。

执行 $n$ 次，每次更新最大值即可。

#### 注意：每次操作前要清空队列和vis数组，还要将 $sum$ 初始化为 $1$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int h,l,zhi;
};
queue<node>q;
int n,sum,ans;
int x[205],y[205],p[205];

bool vis[205];
//因为存坐标的二维数组开不下，所以这里的vis是来存位置的（第几个）

void bfs(int x1,int y1,int p1,int t1){
	while(!q.empty())
		q.pop();
	node t;
	t.l=x1;
	t.h=y1;
	t.zhi=p1;
	q.push(t);
	vis[t1]=true;
	while(!q.empty()){
		node now=q.front();
		q.pop();
		for(int i=1;i<=n;i++)
			if(vis[i]==false){
				double pd=sqrt((x[i]-now.l)*(x[i]-now.l)+(y[i]-now.h)*(y[i]-now.h));
				if(pd<=now.zhi){
					sum++;
					node tmp;
					tmp.l=x[i];
					tmp.h=y[i];
					tmp.zhi=p[i];
					vis[i]=true;
					q.push(tmp);
				}
			}
	}
}
//简单的BFS操作

signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld%lld",&x[i],&y[i],&p[i]);
	for(int i=1;i<=n;i++){
		sum=1;
		memset(vis,false,sizeof(vis));
		bfs(x[i],y[i],p[i],i);
		ans=max(ans,sum);	//每次更新ans
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Blue_wonders (赞：0)

## BFS搜索AC
#### 本来想spfa的，做着做着就感觉一点都用不着，就去了好多部分只剩下bfs了
#### 这个题本来用queue也队列做，但是deque双端队列内容更丰富，所以这里就用了deque
这里是queue队列和deque队列的一些用法
| 用法 | deque | queue |
| -----------: | -----------: | -----------: |
| 在前面插入 | g.push_front() |  |
| 在后面插入 | g.push_back() | g.push() |
| 读取第一个 | g.front() | g.front() |
| 读取最后一个 | g.back() | g.back() |
| 删除第一个 | g.pop_front() | g.pop() |
| 删除最后一个 | g.pop_back() |  |
| 判断非空 | g.empty | g.empty |
| 清除队列 | g.clear |  |
| 队列元素 | g.size() | g.size() |
#### 算法思路
这道题类似“聪明的猴子”
1. 先是输入，并且将能量平方(平方是为了在下一步两点距离的时候转化不会出现小数直接平方和平方比较)
2. 然后每条边的长度算出来，和起点的能量比较(平方)如果能量大就说明能到，记录这条边
3. 后面bfs去搜索所有边的条数(vis数组判重)
4. 输出结果 
#### AC代码[代码详情](https://www.luogu.org/recordnew/show/17714428)
```cpp
#include<bits/stdc++.h>
using namespace std;
struct point{
    int a,b,c;
} p[201];
vector<int>h[40010];
int n,all=0;
int vis[201],ans;
int search(int s){//对于这个点 
    deque<int>g;//建立队列 
    g.clear();//(其实这里不用，在函数内部重新定义每次都是空的) 
    memset(vis,0,sizeof(vis));//vis数组清零 
    ans=1;vis[s]=1;//起点做标记 
    g.push_front(s);//起点进入队列 
    while(!g.empty()){
        int p=g.front();g.pop_front();//出队列 
        for(int i=0;i<h[p].size();i++){//对于能连接点的边都bfs搜索一遍 
            if(vis[h[p][i]]==0){//如果没有搜索过就进入队列 
                vis[h[p][i]]=1;//标记 
                ans++;// 答案加一 
                g.push_back(h[p][i]);//进入队列 
            }
        }
    }
    return ans;//返回答案 
}
int main(){
    cin>>n;//输入 
    for(int i=1;i<=n;i++){
        cin>>p[i].a>>p[i].b>>p[i].c;//记录x，y坐标 
        p[i].c=p[i].c*p[i].c;//对于能量进行平方处理，避免在求两点之间距离是出现实数 
    } 
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            int u=pow(p[i].a-p[j].a,2)+pow(p[i].b-p[j].b,2);//对于每两个点求距离的平方 
            if(p[i].c>=u)h[i].push_back(j);//和能量的平方进行比较如果能量大就说明能发送过去，就记录边 
            if(p[j].c>=u)h[j].push_back(i);//单向边，所以判断两次 
        }
    }
    for(int i=1;i<=n;i++)all=max(all,search(i));//对于每一个点进行判断，取最大值 
    cout<<all;//输出最大值 
    return 0;
} 
```
！！！

---

## 作者：ARZhu (赞：0)

# 需要翻译的童鞋先看看翻译

## 题目描述

约翰农场主的N(1<=N<=200)头奶牛想建立一个紧急情况下的“哞哞广播”系统，这样它们就可以在自己中间广播重要信息。

奶牛们想让每头牛装备上一个对讲机，而不是在长距离中向另一头奶牛“哞哞”乱叫。这些对讲机每台都有各自的有效传输半径——一个拥有P能量的对讲机只能向距离在P以内的牛发送信息（注意可能出现A牛对讲机的能量比B牛的大，而A牛可以给B牛发送信息，但B牛不能传回信息）。幸运的是，奶牛们可以通过其他奶牛中继，沿着一条跳跃的路径传递信息，因此每个奶牛不必要直接向每个其他奶牛传播。

由于对讲机的费堆成性质，来自一些奶牛的广播可能比其他奶牛的广播能够达到更多的接受者（考虑中继的情况）的能力更有效。请帮助奶牛确定来自单个奶牛的广播可以达到的奶牛的最大数量。


## 输入输出格式

### 输入格式：

第一行输入包括N。

下面的N行，每一行都包括了一只牛的坐标(x,y),（x,y为整数并且在0...25,000的范围内）和这只牛所持有对讲机的能量P。

### 输出格式：

输出一行，表示从来自单个奶牛的广播可以达到的奶牛的最大数量。开始的牛也包括在这个数量中。


这道题很明显，是一道图论题。先构造一个邻接矩阵，如果可以直接到达，那么这条边设为一。接下来就是跑一遍三重循环（有点像Floyd），看看两个点之间是否可以到达。最后再验证答案。

不说了，上代码。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline int read(){//读入优化
    int x=0,tmp=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if (ch=='-') tmp=-1; ch=getchar();}
    while(ch>='0' && ch<='9'){x=x*10+ch-'0'; ch=getchar(); }
    return x*tmp;
}
inline void write(int k){//输出优化
    if (k<0) {putchar('-'); k=-k;}
    if (k>9) write(k/10);
    putchar(k%10+'0');
}
int c[210][3],N;
inline int distant(int i,int j){
    return ((c[i][0]-c[j][0])*(c[i][0]-c[j][0])+(c[i][1]-c[j][1])*(c[i][1]-c[j][1]));
}//返回距离
bool edge[210][210];
bool f[210][210];
int main(){
    //freopen("moocast.in","r",stdin);
    //freopen("moocast.out","w",stdout);
    N=read();
    for(int i=1;i<=N;++i){
        c[i][0]=read(),c[i][1]=read(),c[i][2]=read();
        c[i][2]=c[i][2]*c[i][2];//将信号平方，易于和距离比较
    }
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            if (distant(i,j)<=c[i][2]) f[i][j]=1;
    for(int k=1;k<=N;++k)
        for(int i=1;i<=N;++i)
            for(int j=1;j<=N;++j)
                if(i!=j && i!=k && j!=k && f[i][k] && f[k][j]) f[i][j]=1;
    int ans=0;
    for(int i=1;i<=N;++i){
        int t=0;
        for(int j=1;j<=N;++j) if (f[i][j]) t++;
        if (t>ans) ans=t;
    }
    write(ans);

    return 0;
}

```

---

