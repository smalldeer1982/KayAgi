# 贪婪的Copy

## 题目描述

Copy 从卢牛那里听说在一片叫 yz 的神的领域埋藏着不少宝藏，于是 Copy 来到了这个被划分为 $n$ 个区域的神地。卢牛告诉了Copy这里共有 $n$ 个宝藏，分别放在第 $P_i$ 个 $(1\le P_i\le N)$ 区域。Copy还得知了每个区域之间的距离。现在 Copy 从 $1$ 号区域出发，要获得所有的宝藏并到 $n$ 号区域离开。Copy 很懒，只好来找你为他寻找一条合适的线路，使得他走过的距离最短。


## 说明/提示

- 对 $30\%$ 的数据，$1\le n\le 15$，其余如题所述。
- 对 $100\%$ 的数据，全部数据范围如题所述。


## 样例 #1

### 输入

```
2
0 4
5 0
2
1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
0 2 6
1 0 4
7 10 0
1
2
```

### 输出

```
6
```

# 题解

## 作者：kkksc03 (赞：111)

官方题解

（kkksc03的吐槽：就这样？）

floyd算出每个点距离，然后p!枚举。

请思考当p、n加大时，有什么方法。


---

## 作者：The_Key (赞：42)

如下面kkk所说“floyd算出每个点距离，然后p!枚举。”枚举时可以用next\_permutation，好写省事

附上代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,sum,ans=0x7fffffff,po[12],mp[105][105];//mp存的是矩阵，po存的是宝藏的位置，ans为最终结果
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    cin>>mp[i][j];
    cin>>m;
    for(int i=1;i<=m;i++)
    cin>>po[i];
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);//Floyd预处理每个点之间的距离
    sort(po+1,po+m+1);//从小到大排序，方便调用next_permutation函数
    do
    {
        sum=0;
        sum+=mp[1][po[1]]+mp[po[m]][n];//先加上第一个点到第一处宝藏以及最后一处宝藏到n的距离
        for(int i=1;i<m;i++)//枚举更新
        sum+=mp[po[i]][po[i+1]];
        ans=min(ans,sum);//更新答案
    }while(next_permutation(po+1,po+m+1));
    cout<<ans;
    return 0;
}//鄙人代码不精，大神勿喷
```

---

## 作者：αnonymous (赞：25)

给不会用stl的C++党发福利了

第一眼看到数据大小：n<=100  我就想到这题肯定要用**Floyed**

然后再用**dfs**一个一个搜出经过所有点的路径长度（dfs大法好）
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int n,a[101][101],p,b[11];
bool f[11];
long long ans=0x7ffffff;
void dfs(int now,int m,long long sum){
	if(m==0)//当每个点都走过
		ans=min(ans,sum+a[now][n]);//记得加上到n的距离
	else{
		for(int i=1;i<=p;i++){
			if(!f[i]){//如果没去过
				f[i]=1;
				dfs(b[i],m-1,sum+a[now][b[i]]);
				f[i]=0;//回溯
			}
		}
	}
}
int main(){
	int i,j;
	long long k;
	cin>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cin>>a[i][j];
	cin>>p;
	for(i=1;i<=p;i++)
		cin>>b[i];
	for(k=1;k<=n;k++)//Floyed
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(a[i][k]!=0&&a[k][j]!=0)//防止i到j距离为0
					a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
	dfs(1,p,0);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：2021_03_21 (赞：10)

## 此题~~明显~~是一道 $floyd$ 板子题。
 为啥要用 $floyd$ 呢？
1. 数据短小精悍 ($1\le N \le100$)。
2. $floyd$ 可求出任意两点间的最短路。

 $floyd$ 板子如下：

```cpp
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(i!=j!=k)
    t[i][j]=min(t[i][j],t[i][k]+t[k][j]);//更新最短路径。
```

 解决了最短路，我们可以使用 $DFS$ 来暴力枚举经过所有宝藏的路径。

$dfs$ 写法如下：

```cpp
void dfs(int now,int m1,long long sum){//三个参数分别代表当前位置、剩余宝藏位置、路径长度。
    if(!m1){
        ans=min(ans,sum+t[now][n]);//更新最小答案。
        return;
	}
    for(int i=1;i<=m;i++){
        if(!flag[i]){
            flag[i]=1;
            dfs(k[i],m1-1,sum+t[now][k[i]]);
            flag[i]=0;
        }
    }
}
```

## 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t[1001][1001],m,k[1001];
bool flag[1001];
long long ans=pow(10,18);//答案初始化为无穷大。
void dfs(int now,int m1,long long sum){//深搜。
    if(!m1){
        ans=min(ans,sum+t[now][n]);
        return;
	}
    for(int i=1;i<=m;i++){
        if(!flag[i]){
            flag[i]=1;//更新标记数组。
            dfs(k[i],m1-1,sum+t[now][k[i]]);
            flag[i]=0;//回溯。
        }
    }
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	cin>>t[i][j];//建单向边。
	cin>>m;
	for(int i=1;i<=m;i++)
	cin>>k[i];
    //Floyd最短路。
	for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(i!=j!=k)
    t[i][j]=min(t[i][j],t[i][k]+t[k][j]);
    dfs(1,m,0);
	cout<<ans;//输出。
    //本人第一次提交题解，如有不当之处请指出。
}
```


---

## 作者：DDOSvoid (赞：7)

这个题可以看作是TSP问题(旅行商问题)的变形。注意1<=p<=10，p最大才取到10，所以可以使用状压DP，把带宝藏的区域压成二进制，因为每个点都可以经过无限次，所以可以用Floyd预处理出两个点之间的最短距离，然后DP即可。

复杂度是O(2^p\*p^2) 实际上就是楼下说的状压，这里给出代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxm 11
#define maxn 101
#define INF 1000000000
using namespace std;
int f[1<<maxm][maxn];//f[i][j]，i为二进制，表示已经经过了哪些带宝藏的区域，j为上一个经过的点，注意第二维大小要开到101 
int map[maxn][maxn],a[maxm];
int n,m;
int main(){
    memset(f,10,sizeof(f));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&map[i][j]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(k!=i && k!=j && i!=j)
                    map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
    int M=(1<<m)-1;
    for(int i=1;i<=m;i++)f[1<<i-1][a[i]]=map[1][a[i]];//初始化出1到每个带宝藏的区域的距离 
    for(int i=1;i<=M;i++)
        for(int j=1;j<=m;j++)
            if(i&(1<<j-1))//如果状态i中包含j 
                for(int k=1;k<=m;k++)
                    if(!(i&(1<<k-1)))//如果状态i中不包含k 
                        f[i|(1<<k-1)][a[k]]=min(f[i|(1<<k-1)][a[k]],f[i][a[j]]+map[a[j]][a[k]]);//转移 
    int ans=INF;
    for(int i=1;i<=m;i++)
        ans=min(ans,f[M][a[i]]+map[a[i]][n]);//因为要在n结束，所以还要加上到n的距离 
    cout<<ans;
    return 0;
}
```

---

## 作者：usqwedf (赞：4)

野生题解 QAQ

-------------------------

[1]
看清题目。。其实本质是最短路径。。

[2]
枚举所有顺序，可以得到所有顺序的最短路径的最短。

[3]
两点之间最短路径可以预处理，Floyed等算法可用 n^3 时间求得

搜索全排列更新最短即可。

[4]
时间复杂度 O(m\*m!+n^3)

空间复杂度 O(n^2)

[5]
不需要代码了吧。。

---------------------------

我是蒟蒻 >\_<


---

## 作者：king_xbz (赞：3)

**前排提醒：在函数中千万不要使用++y之类的操作不然会像我一样死的很惨**

这道题是一道历史悠久的最短路问题，题解区的题解最早的甚至是在2013年！！！

解决这道题的方法也同样和这道题的历史一样古老，由于题目**数据范围**是$(1<=N<=100)$,$(0<=P<=10)$,所以我们可以不用那些复杂难懂的算法（如dijkstra，	SPFA等），只需要简单的四行**Floyd**求出各点间的最短路，然后**暴力**扫一遍求出**从1号区域出发**，要获得**所有的宝藏**并到**n号区域离开**的最短距离即可，我们可以考虑用**DFS**来完成枚举。

- 接下来是主干部分

先是最短路Floyd，复杂度$O(n^3)$，[点此了解该算法](https://baike.baidu.com/item/Floyd算法/291990?fromtitle=floyd&fromid=23665947&fr=aladdin)
```cpp
for(fint k=1;k<=n;k++)
for(fint i=1;i<=n;i++)
for(fint j=1;j<=n;j++)
f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//简单粗暴的四行floyd
```
接下来我们对爆搜进行预处理
```cpp
m=read();
for(fint i=1;i<=m;i++)
num[i]=read();
sort(num+1,num+m+1);//对标号数组进行排序便于求出最优解（贪心）
for(fint i=1;i<=n;i++)
a[i]=f[i][n];//预处理每个点到终点的距离，方便一会爆搜
```
然后是搜索与回溯，不了解DFS和回溯的同学可以先看看这道题->[八皇后](https://www.luogu.com.cn/problem/P1219)
```cpp
dfs(1,0);//从第一个区域开始搜，此时已经找到0个宝藏

void dfs(int x,int y)
{
	if(y==m)
	ans=min(now+a[x],ans);
   //如果已经把宝藏找完了，就去这次走的路和之前答案的最小值。
   //由于我们需要走到n点所以这里需要加上x到n的距离（此前已经预处理过了）
	else
	for(fint i=1;i<=m;i++)
	if(!vis[i])//如果没有访问过
	vis[i]=1,now+=f[x][num[i]],dfs(num[i],y+1),go_back(i,x);
   //那么临时存储器now就更新，然后往下搜，搜完记得回溯
	return ;
}

inline void go_back(int x,int y)//回溯函数
{
	vis[x]=0,now-=f[y][num[x]];
	return ;
}
```
那么这道题就基本完成了，最后再次提醒大家dfs函数中的y+1千万不能写成++y

如果需要完整代码[点我获取](https://www.luogu.com.cn/paste/m3853c8n)

最后，祝大家AC愉快！

---

## 作者：AKB48 (赞：3)

所谓带限制条件的最短路径是指满足用户约束条件的最短路径.用户的约束条件是:给定起始节点(start)和目标节点(end)以及该路径上的避开节点列B={B1,B2,…,Bn}和必经节点列J={J1,J2,…,Jn.

若要避开某些节点,则可在改进的Dijkstra算法中加入判断语句,即当从堆中抽出具有最小D值的点并标记已访问时,判断该点是否是避开节点列中的点,若是则不入红点集.

若需经过某些节点,则利用分段求最短路径的方法求出总的最短路径.可将J存成一个数组,用改进的Dijkstra算法先算起始节点start与J[0]的最短路径,然后对数组下标i进行循环,判断下一个节点是否是已经过节点,若是继续数组下一个节点,否则调用Dijkstra算法计算J[i]与该节点的最短路径,然后再以该节点为起始节点重复上述判断直到数组最后一个元素,最后计算它与终点end的最短路径,再将所求得最短路径值相加即得总最短路径值.要值得注意的是每次在调用Dijkstra算法之前,要重新将所有的点设置为未访问过(UNVISTED),因为算法结束时很多点都已访问过(VISITED).而且要把各段所计算出的最短路径D值以及经过的点保存起来.

本题中仅用到了必经节点的最短路径


---

## 作者：操作！ (赞：3)

# 本题数据福利大警告！！！
### 依题意，n<=100
### 锵锵锵！万能的floyd登场！~~还有dfs~~


你们最喜欢的全代码~~

```
#include<bits/stdc++.h>
using namespace std;
int n,f[200][200],p1,p[50],ans=1e8,sum;
bool used[200];
void find1(int place,int tot)//寻宝程序
{
	if(tot==0)//如果都找到了
	{
		ans=min(ans,sum+f[place][n]);//选一个最佳答案
		return;
	}
	for(register int i=1;i<=p1;i++)
	{
		if(!used[i])//还没有找过
		{
			used[i]=true;//标记为找过
			sum+=f[place][p[i]];
			find1(p[i],tot-1);
			used[i]=false;//取消标记
			sum-=f[place][p[i]];
		}//回溯
	}
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	for(register int j=1;j<=n;j++)
	scanf("%d",&f[i][j]);
	scanf("%d",&p1);
	for(register int i=1;i<=p1;i++)
	scanf("%d",&p[i]);
	sort(p+1,p+1+p1);
	for(register int k=1;k<=n;k++)
	for(register int i=1;i<=n;i++)
	for(register int j=1;j<=n;j++)
	f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//无敌的Floyd！！！
	find1(1,p1); //开始寻宝~~~
	printf("%d",ans);
	return 0;
}
```
另外再说一句
# 养成用register int 加速的好习惯呦

---

