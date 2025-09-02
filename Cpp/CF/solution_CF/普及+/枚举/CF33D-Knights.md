# Knights

## 题目描述

伯兰国不得不又一次面对黑♂暗势力的降临。邪恶领主~~Van♂De♂Mart~~范·德·马特正在计划征服整个王国。王国成立了由伯兰国王瓦莱丽领导的理事会。理事会由$n$个骑士组成。经过一番激烈的讨论，他们把整个国家分成了$n$个战略目标点，（如果黑暗势力控制了至少一个战略目标点，战争就失败了）

伯兰国可以被认为是由$m+1$个区域和$m$个栅栏组成的。同时，从一个区域到达另一个区域的唯一方法就是翻过栅栏。每个栅栏都是同一个平面上的圆，并且任意两个栅栏之间都没有交叉点，同时保证所有战略目标点都`不在`栅栏上。我们会给你$k$对整数$ai, bi$，对于每对整数，你都要解决：如果一个骑士想从战略控制点$ai$赶到$bi$，（为了防止范·德·马特突袭控制点bi），而每个骑士都骑着一匹马（把马从栅栏上扔过去太难了），那么，他最少爬过多少栅栏？

## 样例 #1

### 输入

```
2 1 1
0 0
3 3
2 0 0
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3 1
0 0
4 4
1 0 0
2 0 0
3 0 0
1 2
```

### 输出

```
3
```

# 题解

## 作者：FatOldEight (赞：6)

# 题目描述

你是一位OIer，今天教练刚讲了LCA，你看到了[CF33D Knights](https://www.luogu.com.cn/problem/CF33D)，打算做一下它。

你简化了问题：给你几个点的坐标和几个圆的坐标与半径（**任意两个圆都没有交叉点**），求一个点到另一个点最少经过几个圆。

# 思路

你想到了一个做法：如果圆 $A$ 包含圆 $B$ ，且$A$ 是**包含圆 $B$ 的圆**中**半径最小**的，则将 $A$ 、 $B$ 连边，容易证得得到的是一个**森林**，而**最外层**的圆自然地连接到了**虚根**0号结点。然后我们计算出每一个**点属于哪一个圆**（这里的属于定义为：圆 $A$ 包含点 $B$ ，且圆 $A$ 是**包含点 $B$ 的圆**中**半径最小**的），查询的时候就通过 **LCA** 和树的**深度**求得**点所属圆**在**树上的最短距离**。

# 代码处理

但是第一个问题出现了：如何判断圆 $A$ 是包含圆 $B$ 的圆中半径最小的？

你想了想，处理方案如下：

1.先将所有圆以**半径**为关键字**升序**排序；

2.以下标为序搜索每一个圆，代码如下：

~~~cpp
void df(int q)//搜索第q个圆//不要在意变量名
{
	if(v[q])return;//如果被搜索过了则return
	v[q]=1;//标记
	for(int i=1;i<=m;i++)//循环每一个圆
	{
		if(check(q,i)&&i!=q)//check(q,j)的意思是圆q能被圆i包含，下同
		{//如果圆q被圆i包含且i不等于q
			adde(q,i);
			adde(i,q);//加边
			df(i);//搜索地i个圆
			return;
		}
	}
}//这样就可以保证圆i是包含圆q的圆中半径最小的
~~~

第二个问题：怎么找到**最外层**的圆？

下面是处理方式+代码（不好叙述，具体讲解在代码中）：

~~~cpp
for(int i=1;i<=m;i++)//循环每一个圆
   {
    bool p=1;
    for(int j=i+1;j<=m;j++)
    {
        if(check(i,j))p=0;//如果i能被其他圆包含，则一定不是最外层的圆
    }
    if(p)adde(i,0),adde(0,i);//加边
}
~~~

你的一个朋友发表不同的意见：”其实可以加一个**无限大的圆**使**其它圆被它包含**“。

第三个问题：如何确定点属于哪一个圆？

处理方式+代码（不好叙述，具体讲解在代码中）：

~~~ cpp
for(int i=1;i<=m;i++)//循环圆
{
    for(int j=1;j<=n;j++)//循环点
    {
        if(!z[j]&&(判断点是否在圆内)/*代码很长且可读性较差，故不展示*/)z[j]=i;//建立关系
    }//因为圆是按半径排列的，所以如果圆i包含了点j，则圆i+1一定包含点j
}    //所以要判断点j是否已经建立关系，防止重复建立关系
for(int i=1;i<=n;i++)if(!z[i])z[i]=0;
//如果没有圆与这个点建立关系就代表这个点与虚根相连
//或者说这个点属于最外面的无限大的圆
~~~

# 主函数代码实现

~~~cpp
int main()
{
    scanf("%d%d%d",&n,&m,&T);
    for(int i=1;i<=n;i++)scanf("%d%d",&mp[i][1],&mp[i][2]);
    for(int i=1;i<=m;i++)scanf("%d%d%d",&O[i].r,&O[i].x,&O[i].y);//输入
    sort(O+1,O+m+1,cmp);//排序
    for(int i=1;i<=m;i++)
    {
        if(!v[i])df(i);
    }//问题一
    for(int i=1;i<=m;i++)
	{
        bool p=1;
        for(int j=i+1;j<=m;j++)
		{
            if(check(i,j))p=0;
        }
        if(p)adde(i,0),adde(0,i);
    }//问题二
    dfs(0,0);//LCA基本操作
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
		{
              if(!z[j]&&(long long)((long long)(O[i].x-mp[j][1])*(O[i].x-mp[j][1])+(long long)(O[i].y-mp[j][2])*(O[i].y-mp[j][2]))<=(long long)O[i].r*O[i].r)z[j]=i;
        }
    }
    for(int i=1;i<=n;i++)if(!z[i])z[i]=0;//问题三
    while(T--)
	{
        int q,w;
        scanf("%d%d",&q,&w);
        printf("%d\n",d[z[w]]+d[z[q]]-2*d[LCA(z[q],z[w])]);
        //找到最少次数并输出
    }
}
~~~

[完整代码](https://fat-old-eight.github.io/%E9%A2%98%E8%A7%A3/2022/02/12/solution-cf33d.html)

---

## 作者：MiRaciss (赞：6)

思路楼上的大佬已经说得很清楚了，这里提供一种Tarjan的算法
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct zz{
	int u,id;
}T[300005];

struct ss{
	int r;
	int x,y;
}a[1005],s[1005];
 
bool cmp(ss x,ss y){
	return x.r<y.r;
}

ll Dist(ss a,ss b){
	ll x,y,xx,yy;
	x=a.x,y=a.y;
	xx=b.x,yy=b.y;
	return (ll)(x-xx)*(x-xx)+(ll)(y-yy)*(y-yy);
}

int n,m,k;
ll ans=0;
vector<int> v[300005];
void Add(int x,int y){
	v[x].push_back(y);
	v[y].push_back(x);
}
vector<zz> sum[300005];
bool f[300005];
int pre[300005];
ll dist[300005];
int tot[3000005];

void Make_Set(){
	for(int i=1;i<=m;i++){
		pre[i]=i;
	}
}

int Find_Set(int x){
	if(pre[x]!=x)
		pre[x]=Find_Set(pre[x]);
	return pre[x];
}

void DFS(int p,int fa){
	dist[p]=dist[fa]+1;
    for(int i=0;i<v[p].size();i++){
    	int x=v[p][i];
    	if(x!=fa)
			DFS(x,p);
	}
}

void Tarjan(int x){
	f[x]=1;
	for(int i=0;i<v[x].size();i++){
		int y=v[x][i];
		if(f[y])
			continue;
		Tarjan(y);
		pre[y]=Find_Set(x);
	}
	for(int i=0;i<sum[x].size();i++){
		zz now=sum[x][i];
		if(!f[now.u])
			continue;
		tot[now.id]=Find_Set(now.u);
	}
}

int main(){
	cin>>n>>m>>k;
	Make_Set();
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&s[i].r,&s[i].x,&s[i].y);
	}
	s[0]=(ss){2147483600,0,0};
	sort(s,s+m+1,cmp);
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(Dist(a[i],s[j])<=(ll)s[j].r*(ll)s[j].r){
				a[i].r=j;
				break;
			}
		}
	}
	
	for(int i=0;i<=m;i++){
    	for(int j=i+1;j<=m;j++)
    		if(Dist(s[i],s[j])<(ll)s[j].r*s[j].r){
				Add(i,j);
				break;
			}
    }
	DFS(0,0);
	for(int i=1;i<=k;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		x=a[x].r;y=a[y].r;
		sum[x].push_back({y,i});
		sum[y].push_back({x,i});
		T[i].id=x;T[i].u=y;
	}
	Tarjan(0);
	for(int i=1;i<=k;i++){
		int x=T[i].id,y=T[i].u;
		cout<<abs(dist[x]+dist[y]-2*dist[tot[i]])<<endl;
	}
	return 0;
}

```

---

## 作者：白鲟 (赞：5)

### 做题之前
这道题的信息量比较大，需要我们逐字逐句地去理解题意，特别要注意题目中的细节。  
### 法1
首先我们发现，每个栅栏都是圆，并且任意两个栅栏**没有交叉点**。这是什么意思呢？这意味着这两个圆内含或外离。同时，这也给我们提供了另一个信息：目标点间的路径穿过栅栏的最少数量不会因为没有包含始终点的栅栏而增加，因为路径总可以通过弯曲绕过这些栅栏。由此我们可以进一步推断出，只有当一个圆**包含源点或终点**时，它才会影响本题的答案。  
那么，这个影响是怎样的呢？显而易见，每有一个包含着点的栅栏，骑士就要穿过一个栅栏。因此，我们只需要统计包含起点或源点的圆的个数，再加起来就可以了——这样做的后果是WA。事实上，并非所有这样的圆都应该被统计。如果**同时包含**了起点和源点，那么这个圆显然**不需要**被穿过。因此，我们要求的答案就是**只包括起点和源点当中一个点**的圆的个数。  
如何求一个点是不是在一个圆之内呢？我们知道，圆是到圆心的距离等于半径的所有点的集合。因此，我们求一个点是不是在一个圆之内，只需要求这个点**到圆心的距离**是否小于半径。距离可以使用**欧几里得距离**公式计算，即d=sqrt((x1-x2)2+(y1-y2)2)，为了**避免损失精度**，可以使用距离的**平方**来进行比较。  
最后有一个小细节，这道题题目中的**“直径”实为半径**。  
码风就这样了……请见谅……
```cpp
#include<cctype>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,k,a,b,r[1001],relationship[1001][1001],total[1001][1001];
struct point
{
	int x,y;
}target[1001],circle[1001];
void fastinput(int &t)
{
	char tmp;
	int signum=1;
	t=0;
	do
	{
		tmp=getchar();
		if(tmp=='-')
			signum=-1;
	}
	while(!isdigit(tmp));
	do
	{
		t=t*10+tmp-'0';
		tmp=getchar();
	}
	while(isdigit(tmp));
	t*=signum;
	return;
}
template<typename Type,typename ..._Type>
	void fastinput(Type &t,_Type &...temp)
	{
		fastinput(t);
		fastinput(temp...);
	}
void fastoutput(int t)
{
	if(t<0)
	{
		t=-t;
		putchar('-');
	}
	if(t>9)
		fastoutput(t/10);
	putchar(t%10+'0');
	return;
}
void fastoutputln(int t)
{
	fastoutput(t);
	putchar('\n');
	return;
}
template<typename Type,typename ..._Type>
	void fastoutputln(Type t,_Type ...temp)
	{
		fastoutputln(t);
		fastoutputln(temp...);
	}
long long distance_2(const point &t1,const point &t2)
{
	return (long long)(t1.x-t2.x)*(long long)(t1.x-t2.x)+(long long)(t1.y-t2.y)*(long long)(t1.y-t2.y);
}
bool in(int t_point,int t_circle)
{
	if(!relationship[t_point][t_circle])//记忆化
		relationship[t_point][t_circle]=(distance_2(target[t_point],circle[t_circle])<(long long)(r[t_circle])*(long long)(r[t_circle]))+1;//转换为long long避免乘法越界
	return relationship[t_point][t_circle]-1;
}
int answer(int x,int y)
{
	int result=total[x][y];
	if(!result)//记忆化
		for(int i=1;i<=m;++i)
			if(in(x,i)&&!in(y,i)||in(y,i)&&!in(x,i))
				++result;
	return result;
}
int main()
{
	fastinput(n,m,k);
	for(int i=1;i<=n;++i)
		fastinput(target[i].x,target[i].y);
	for(int i=1;i<=m;++i)
		fastinput(r[i],circle[i].x,circle[i].y);
	while(k--)
	{
		fastinput(a,b);
		fastoutputln(answer(a,b));
	}
	return 0;
}
```
### 法2
这里还有另外一种思路，并非使用暴力的枚举算法。将相邻的由圆分割得到的**区域连边**，边权为一，容易证得得到的是一个**森林**，而**最外层**的圆自然地连接到了**虚根**0号结点。然后我们计算出每一个**战略控制点属于哪一个区域**，查询的时候就通过**LCA**和树的**深度**求得**战略控制点所属区域**在**树上的最短距离**。  
代码跑了一个多小时了还在跑……所以不知道是对是错……就不上代码了……   


------------

**PS：**代码并非抄袭，学校考试的时候使用的是他人账号提交，所以和某位仁兄的代码相同……

---

## 作者：这有一只匿 (赞：4)

这是一个很暴力的想法……

首先很容易看出这些战略目标点能组成一组森林，我们只需要建立一个虚根，就可以把它转化为一颗有根树。而最少爬过多少栏杆则是问树上两点间的最短距离是多少。

那么方法就显而易见了，LCA。边权为1，虚根不影响答案，多次查询（如果只有一次其实可以暴力枚举，好像有这么个题233）。

代码如下
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int n,m,k;
struct hehe{
    int nx,nd;
}e[2000100];
struct kk{
    long long r,x,y;
}b[1010],a[1010];
int cnt,fi[1010],dep[1010],f[10001][21],lim;
bool cmp(const kk & p,const kk & q)
{
    return	p.r<q.r;
}
long long disk(kk p,kk q)
{
    return sqrt((p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y));
}
void add(int a,int b)
{
    e[++cnt]=(hehe){fi[a],b},fi[a]=cnt;
}
void dfs(int p,int fa){
    f[p][0]=fa;dep[p]=dep[fa]+1;
    for(int i=fi[p];i;i=e[i].nx)
    if(e[i].nd!=fa)dfs(e[i].nd,p);
}
int LCA(int u,int v)
{
    if(dep[u]>dep[v])swap(u,v);
    for(int i=lim;i>=0;i--)if(dep[u]<=dep[f[v][i]])v=f[v][i];
    if(u==v)return u;
    for(int i=lim;i>=0;i--)if(f[v][i]!=f[u][i])u=f[u][i],v=f[v][i];
    return f[u][0];
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    lim=log(n)/log(2)+1;
    for(int i=1;i<=n;i++)
    scanf("%lld%lld",&a[i].x,&a[i].y);
    for(int i=1;i<=m;i++)
    scanf("%lld%lld%lld",&b[i].r,&b[i].x,&b[i].y);
    b[0]=(kk){2147483647,0,0};
    sort(b,b+m+1,cmp);
    for(int i=1;i<=n;i++)
    {
    for(int j=0;j<=m;j++)
    {
    int dis=disk(a[i],b[j]);
    if(dis<b[j].r){a[i].r=j;break;}
    }
    }
    for(int i=0;i<=m;i++)
    {
    for(int j=i+1;j<=m;j++)
    if(disk(b[i],b[j])<b[j].r){add(i,j);add(j,i);break;}
    }
    dfs(m,m);
    for(int j=1;j<=lim;j++)
    for(int i=0;i<=m;i++)
    f[i][j]=f[f[i][j-1]][j-1];
    for(int i=1;i<=k;i++)
    {
        int p,q;
        scanf("%d%d",&p,&q);
        int lc=LCA(a[p].r,a[q].r);
        cout<<dep[a[p].r]+dep[a[q].r]-2*dep[lc]<<endl;
    }
}
```

---

## 作者：XL4453 (赞：3)

### $\text{Difficulty : 2000}$
---
### 解题思路：

暴力计算几何。

一个骑士需要跨过栅栏当且仅当一个城堡在栅栏内部，另一个在外面。

直接根据到圆心的距离和半径的大小关系计算出是否在园内，两个一比较就出来了。可以两边同时平方以免精度误差。

总复杂度 $O(mk)$，可以接受。有优化方案但是没有必要。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=10005;
int n,m,Q,x[MAXN],y[MAXN],xx[MAXN],yy[MAXN],r[MAXN],a,b,cnt;
bool check(int x1,int y1,int x2,int y2,int r){
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<=r*r;
}
signed main(){
	scanf("%I64d%I64d%I64d",&n,&m,&Q);
	for(int i=1;i<=n;i++)scanf("%I64d%I64d",&x[i],&y[i]);
	for(int i=1;i<=m;i++)scanf("%I64d%I64d%I64d",&r[i],&xx[i],&yy[i]);
	while(Q--){
		scanf("%I64d%I64d",&a,&b);
		cnt=0;
		for(int i=1;i<=m;i++)
		cnt+=check(x[a],y[a],xx[i],yy[i],r[i])^check(x[b],y[b],xx[i],yy[i],r[i]);
		printf("%I64d\n",cnt);
	}
	return 0;
}
```


---

## 作者：ты (赞：3)

【解析】

只需要搜索两个位置被不同的多少个栅栏包围即可。

【程序】

```cpp
#include<cstdio>
#include<cstring>
#define maxn1 1005
#define maxn2 1005
using namespace std;
int n,m,k;
int rad[maxn2];
int u[maxn2][maxn2];
int tot[maxn1][maxn1];
struct point{
	int x,y;
}a[maxn1],b[maxn2];
long long distance_2(const point &t1,const point &t2){
	return (long long)(t1.x-t2.x)*(long long)(t1.x-t2.x)+(long long)(t1.y-t2.y)*(long long)(t1.y-t2.y);
}
bool in(int x,int y){
	if(!u[x][y]){
		u[x][y]=(distance_2(a[x],b[y])<((long long)rad[y])*((long long)rad[y]))+1;
	}
	return u[x][y]-1;
}
bool judge(bool x,bool y){
	return (x&&!y)||(!x&&y);
}
int work(int x,int y){
	int i;
	if(!tot[x][y]){
		for(i=1;i<=m;i++){
			if(judge(in(x,i),in(y,i))){
				tot[x][y]++;
			}
		}
	}
	return tot[x][y];
}
int main(){
	memset(tot,0,sizeof(tot));
	int i,j,t1,t2;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++){
    	scanf("%d%d",&a[i].x,&a[i].y);
	}
	for(i=1;i<=m;i++){
    	scanf("%d%d%d",&rad[i],&b[i].x,&b[i].y);
	}
	for(i=1;i<=k;i++){
    	scanf("%d%d",&t1,&t2);
		printf("%d\n",work(t1,t2));
	}
	return 0;
}
```


---

## 作者：Erica_N_Contina (赞：1)

## 思路

题意理解：在一个平面上有 $m$ 个圆（空心圆），这些圆把平面分成 $m+1$ 个区域。圆之间没有交点（这时我们应该想到圆之间可能是**相离**或者**内含**的）。我们把平面上没有被任何圆包含的部分叫做“外部”。

假设我们从 $a_i$ 到 $b_i$ 要先经过外部，即我们要先达到所有圆的外面，然后再进入圆。或者说，没有一个圆同时包含了点 $a_i,b_i$。

那么这种情况我们只需要计算出有多少个圆包含了 $a_i$（记为 $cnt_a$）和有多少个圆包含了 $b_i$（记为 $cnt_b$），答案就是 $cnt_a+cnt_b$。

那么假设有一些圆同时包含了 $a_i,b_i$，首先可以直到这些圆一定在最外层。同时，这些圆我们是不需要经过的。或者换一种说法，这些圆是 $a_i,b_i$ 的**公共圆。**

### LCA做法

公共？那好办了。进入圆与圆之间只有全包含和不包含的关系，那么这就像极了树上祖先和后代的关系。

我们把平面看成根节点，那么我们根据圆的包含关系，构建一棵树出来。

如图。

![image.png](https://img1.imgtp.com/2023/09/17/cGcz28Va.png)

然后对于点 $a,b$，我们记录它们的圆 $ra,rb$，求出树上 $lca(ra,rb)$，然后答案就是 $dep_{ra}+dep_{rb}-2\times dep{lca(ra,rb)}$。

### 暴力做法

因为本题圆的个数不多，我们可以用二维数组来**记忆化**记录点 $a$ 与圆 $r$ 的关系，也允许了我们暴力扫描每一个圆来判定该点是否在这个圆中。

至于怎么样判定一个点是否在某个圆中，我们比较其到圆心的距离与半径即可。

注意暴力做法需要究极无敌常数优化（指快读快输）才能卡过哦。

## 代码（暴力做法）

为了代码短一点，代码里没加快读。

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=1e3+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,k,a,b;
int r[N],inc[N][N],mres[N][N];

struct node{
	int x,y;
}p[N],cir[N];

int dis(node t1,node t2){
	return (t1.x-t2.x)*(t1.x-t2.x)+(t1.y-t2.y)*(t1.y-t2.y);
}

bool judge(int x,int c){
	if(!inc[x][c])//记忆化
		inc[x][c]=(dis(p[x],cir[c])<r[c]*r[c])+1;
	return inc[x][c]-1;
}

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)
		cin>>p[i].x>>p[i].y;
	for(int i=1;i<=m;++i)
		cin>>r[i]>>cir[i].x>>cir[i].y;
	while(k--){	
		int x,y;
		cin>>x>>y;
		int res=mres[x][y];
		if(!res){//记忆化
			for(int i=1;i<=m;++i){//暴力枚举判断即可 
				if(judge(x,i)&&!judge(y,i)||judge(y,i)&&!judge(x,i))res++;
			}
		}
		cout<<res<<endl;
	}
	return 0;
}
```




---

## 作者：Civilight_Eterna (赞：0)

有 $n$ 个点， $m$ 个圆， $k$ 个询问，每个圆不交叉。 

一种纯 ? 暴力做法。 

对于每个询问 $a_i,b_i$ 暴力枚举每个圆，判断两个点相对于该圆的位置，如果都在或都不在，那么这个圆对答案无贡献 ( 自行思考，很简单啦 ) 。如果一个点在而另一个不在，那必然会跨过这个圆， ans+1 。

时间复杂度  $\Theta(T \times m)$ 。

更多细节见代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,k;
struct dian{//点
	int x,y;
}d[1003];
struct yuan{//圆
	int x,y;ll r;
}yu[1003];

inline ll dif(ll x,ll y,ll xx,ll yy){//距离的平方，记得long long
	return (x-xx)*(x-xx)+(y-yy)*(y-yy);
}
inline bool zyn(ll i,ll x){//i是圆的编号，x是点的编号。用距离判断点x是否在圆i内
	return dif(yu[i].x,yu[i].y,d[x].x,d[x].y)<=yu[i].r*yu[i].r;
}
int main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;int u,v;
	for(int i=1;i<=n;i++)
		cin>>d[i].x>>d[i].y;
	for(int i=1;i<=m;i++)
		cin>>yu[i].r>>yu[i].x>>yu[i].y;//以上为读入
	for(int i=1;i<=k;i++){
		cin>>u>>v;int ans=0;//注意清空ans的值
		for(int j=1;j<=m;j++){//暴力枚举每个圆
			if(zyn(j,u)^zyn(j,v)){
		//如果都不在一个圆或都在一个圆内，那么不需要跨过该圆的栅栏，否则必然会跨过这个圆
				ans++;
			}
		}cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：wujingfey (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF33D)

~~感觉可以降黄？~~

## 题解

由题意可以知道：

1. 任意两个圆之间没有交点。
2. 两点之间不一定走直线，可以绕路。

所以对于一个圆，如果起点和终点都不在圆内，那一定可以绕路相互抵达。所以这个圆不产生贡献。

相似的如果起点和终点都在圆内，也不会产生贡献。

而如果起点和终点中，有一个在圆内，一个在圆外，则路径一定要穿过圆。~~这个挺显然的。~~

然后看到数据范围，发现对于每个询问，可以暴力枚举所有栅栏，然后用距离公式算**点与圆的位置关系**：设圆心到某个点 $p$ 的距离为 $d$，圆的半径为 $r$，如果 $d<r$ 则点在圆内，$d>r$ 则点在圆外。

注意一点，因为 sqrt 开平方根有点慢，所以我们不比较 $d$ 和 $r$，而是比较 $d^2$ 和 $r^2$，省去了开根的复杂度。

## CODE:
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int n,m,k;
struct NODE{
	int x,y;
}a[N];
struct Circle{
	int r,x,y;
}b[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	for(int i=1;i<=m;i++){
		cin>>b[i].r>>b[i].x>>b[i].y;
	}
	for(int i=1;i<=k;i++){
		int a1,a2,ans=0; cin>>a1>>a2;
		int xx1=a[a1].x, yy1=a[a1].y;
		int xx2=a[a2].x, yy2=a[a2].y;
		for(int j=1;j<=m;j++){
			int xx3=b[j].x, yy3=b[j].y, rr=b[j].r*b[j].r;
			int d1=(xx1-xx3)*(xx1-xx3)+(yy1-yy3)*(yy1-yy3);
			int d2=(xx2-xx3)*(xx2-xx3)+(yy2-yy3)*(yy2-yy3);
			if(rr<d1 && rr<d2) continue;
			if(rr>d1 && rr>d2) continue;
			if(rr<d1 && rr>d2) ans++;
			if(rr>d1 && rr<d2) ans++;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

