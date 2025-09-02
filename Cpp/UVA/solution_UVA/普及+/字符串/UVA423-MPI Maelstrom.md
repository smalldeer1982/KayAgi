# MPI Maelstrom

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=364

[PDF](https://uva.onlinejudge.org/external/4/p423.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA423/620b48e988d4826466e382f01c3dcee7d7e821bf.png)

## 样例 #1

### 输入

```
5
50
30 5
100 20 50
10 x x 10```

### 输出

```
35```

# 题解

## 作者：Silence_water (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/UVA423)

------------
### Description

> $n$ 个机器之间传递信息，求每个机器到 $1$ 号机的最短传递时间的最大值。


------------

### Analyse

首先我们要求每个机器到 $1$ 号机的最短传递时间，所以是一个单源最短路问题，这里我使用的是 SPFA 算法。


------------

### Pay attention

- 由于输入可能是 `int` 类型，也可能是 `char` 类型的  $x$，所以我们可以统一当成字符串，然后用 `atoi` 将不是  $x$ 的字符串转为 `int` 类型。

- 输入的是半矩阵，所以要存双向边。


------------

### Code

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<utility>
using namespace std;
typedef pair<int,int> pii;
const int M=105;
int n,dis[M],ans;
bool vis[M];
vector<pii> e[M];

void clear(int s)
{
	memset(dis,0x3f,sizeof(dis));
	memset(vis,false,sizeof(vis));
	dis[s]=0,vis[s]=true;
}//全部初始化 

void init()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)//半矩阵的输入 
		{
			char s[6];
			scanf("%s",s);//统一当成字符串处理 
			if(s[0]=='x')continue;//是x就跳过 
			int w=atoi(s);//用atoi进行转换 
			e[i].push_back(make_pair(j,w));
			e[j].push_back(make_pair(i,w));
		}
}

void spfa(int s)
{
	clear(s);
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=0;i<e[u].size();i++)
		{
			int v=e[u][i].first,w=e[u][i].second;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				if(!vis[v])
				{
					vis[v]=true;
					q.push(v);
				}
			}
		}
	}
	return;
}//spfa板子
int main()
{
	init();
	spfa(1);
	for(int i=2;i<=n;i++)
		ans=max(ans,dis[i]);//找出最长时间 
	printf("%d",ans);
    return 0;
}
```


------------
谢谢观看！

---

## 作者：fanfansann (赞：1)

最短路模板...

题目大意其实就是求一个所有点的最短路的最大值

注意输入的时候是半个矩阵，以及字符串输入用atoi将char转换成int


由于是一个矩阵，而且数据比较小，我们可以直接用Floyd求一下就好了。
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>

using namespace std;

const int N = 2007;
const int M = 10007;
const int INF = 0x3f3f3f3f;
typedef pair<int,int> PII;
int n,m;
char s[100];
int dis[N][N];


int main(){
    cin>>n;
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j)
            if(i == j)dis[i][j] = 0;
            else dis[i][j]  = dis[j][i] =  INF;
    for(int i = 2;i <= n;++i)
        for(int j = 1;j <= i - 1;++j){
            scanf("%s",s);
            if(s[0] == 'x')continue;
            int val = atoi(s);
            dis[i][j] = dis[j][i] = val;
        }
    for(int k = 1;k <= n;++k)
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
    int ans = 0;
    for(int i = 1;i <= n ;++i)
        ans = max(ans,dis[1][i]);
    cout<<ans<<endl;
    return 0;
}

```



---

## 作者：yxinh (赞：1)

裸dijstra。。。。。。



题目给的下三角矩阵可以直接用邻接矩阵存。。。



用map[i][j]表示i--->j的初始距离，dis[i]表示1--->i的最小距离。


如果矩阵中是**x**,就将邻接矩阵赋值为 _INF_,表示不联通，反之附上题目所给的值。


其它关于具体的一些写法就看代码吧
```
#include <cstdio>  
#include <queue>  
#include <cstring>  
#include <iostream>  
#include <cstdlib>  
#include <algorithm>  
#define inf 0x3f3f3f3f
using namespace std;
int e[101][101],dis[101];
bool mark[101];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		dis[i]=inf;
		mark[i]=false;
		for(int j=1;j<=n;j++)
		{
			if(i==j)
			e[i][j]=0;
			else
			e[i][j]=inf;//初始化
		}
	}
	dis[1]=0;
	mark[1]=true;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			char a[5];  
            scanf("%s",&a);  
            if(a[0]!='x')  
            e[i][j]=e[j][i]=atoi(a);//将字符串转为整形  
		}
	}
	for(int i=2;i<=n;i++)
	dis[i]=e[1][i];//dis数组赋初值
	for(int i=1;i<=n;i++)
	{
		int tmp,min=inf;
		for(int j=1;j<=n;j++)
		{
			if(!mark[j] && dis[j]<min)
			{
				min=dis[j];
				tmp=j;
			}
		}
		mark[tmp]=true;
		for(int j=1;j<=n;j++)
		{
			if(!mark[j] && dis[j]>dis[tmp]+e[tmp][j])//经典两行
			dis[j]=dis[tmp]+e[tmp][j];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(dis[i]>ans)
		ans=dis[i];//取1到各节点之间的最大值
	}
	cout<<ans<<endl;
    return 0;
}
```

---

## 作者：YuanZhizheng (赞：0)

先说一下大概题意，给你一个图，求出从1到其他点的路径中，最大的那条。

这道题的点数最多100个。

**特别说一下**，像这种题目，点的数量是几百或者更小的时候，可以用Floyd算法，复杂度是O(n^3)

先上一下这个代码，很显然，思路就是枚举中转点k。来进行松弛操作。

```
for(k=1;k<=n;k++)
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
    if(s[i][k]+s[k][j]<=s[i][j])
       s[i][j]=s[i][k]+s[k][j];
```

下面直接上AC代码，上面还有一些注释，可以帮助你看懂代码

```
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
using namespace std;
void floyd();//声明函数
char ch[105];
int n,s[105][105];
const int inf=0x3f3f3f3f;//设一个相对无穷大的值，没有直接相连的两个点它们最初的距离就是这个。
void floyd()
{
    int maxx=-1;
    int i,j,k;
    //下面的三重循环就是Floyd算法
    for(k=1;k<=n;k++)
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
        if(s[i][k]+s[k][j]<=s[i][j])
        s[i][j]=s[i][k]+s[k][j];
    for(i=1;i<=n;i++)
    {
        maxx=max(maxx,s[1][i]);//找1到每个点的最大距离
    }
    printf("%d\n",maxx);//切记一定要加换行！！！不然这题会WA
}
int main()
{
    scanf("%d",&n);//接收点的数量
    int i,j,k;
    for(i=2; i<=n; i++)
    {
        for(j=1; j<i; j++)
        {
            scanf("%s",ch);//进行字符串处理，因为有可能输入x
            if(ch[0]=='x')//另一篇题解有个atoi函数，也可以学习一下
            {
                s[i][j]=inf;
                s[j][i]=inf;
            }
            else
            {
                int len=strlen(ch);
                int sum=0;
                int ans=1;
                for(k=len-1; k>=0; k--)
                {
                    sum=sum+(ch[k]-'0')*ans;
                    ans*=10;
                }
                s[i][j]=sum;
                s[j][i]=sum;
            }
        }
    }
    for(i=1; i<=n; i++)//自己与自己的距离设为0
        s[i][i]=0;
    floyd();//拉上去看看Floyd吧
    return 0;
}
```

---

