# The Way to Home

## 题目描述

一只青蛙现在在一个数轴上，它现在要从点 $1$ 跳到点 $n$ ，它每次可以向右跳不超过 $d$ 个单位。比如，它可以从点 $x$ 跳到点 $x+a$  $( 1<=a<=d )$ 。特别的，青蛙只能在有百合花的点上停留。保证点 $1$ 和点 $n$ 之间有一些点有百合花。请输出青蛙到达点 $n$ 的最小跳跃次数。

## 说明/提示

在样例1中，青蛙可以从点 $1$ 跳3个单位到点 $4$ ，再从点 $4$ 跳4个单位到点 $8$ .
在样例2中，青蛙不能到达点 $n$ ，因为它至少需要跳3个单位，但它最多只能跳2个单位。

由 @星烁晶熠辉 提供翻译

## 样例 #1

### 输入

```
8 4
10010101
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 2
1001
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
8 4
11100101
```

### 输出

```
3
```

## 样例 #4

### 输入

```
12 3
101111100101
```

### 输出

```
4
```

# 题解

## 作者：学而思李老师 (赞：12)

# 从递归到深度优先搜索
最近正在学搜索，在 CF 区偶然看到了这一道题。虽然算法标签上都是什么“图论”“最短路”，但是，这一道题只用普通的搜索就可以完成。这篇题解中，我会对递归和搜索进行详细地介绍。由于篇幅可能较长，特附目录一份。
### 目录
 1. 函数中的递归（与题目关联不大，可跳过）
 2. 什么是深度优先搜索
 3. 剪枝

## 一、函数中的递归
什么是递归？递归就是**函数在内部调用其本身**。这时，大家可能会想，为什么一个函数还能调用本身呢？下面有一个递归函数：

```cpp
void f(int x)
{
	printf("%d %p\n", x, &x);
	if(x == 0)
		return;
	f(x - 1);
}
```

我们会发现，每一次输出的 $x$ 的地址都是不一样的，也就是说，**程序在运行一个函数时，会给一个函数分配一个空间，每一次递归都会分配一次**，正因如此，在程序进入无限递归时，错误类型是 MLE 而不是 TLE。所以，递归是可能的。

在递归函数中，我们把一个问题转化为一个或多个规模更小的子问题，解决的这些子问题可以用来解决或解释我们原先的问题。比如阶乘可以做如下的定义：

 $$n!=\begin{cases}1&n=1\\n\times(n-1)!&n>1\end{cases}$$

当我们编写一个求阶乘的函数的时候，我们可以把它写成递归的形式。当 $n=1$ 时，问题足够简单，我们可以直接写出答案：1；当 $n > 1$ 时，我们可以先计算 $n-1$ 的阶乘，最后再乘以 $n$ 。这样，我们只需要解决了 $(n-1)!$ 这个更简单的问题。这就形成了这个问题的递归函数，代码如下：

```cpp
long long f(long long x)
{
	if(x == 1) return 1;
	return x * f(x - 1);
}
```

当我们编写满足下面三个特点的问题时，我们可以用递归求解：
1. 该问题拥有一个或多个可以直接给出答案的**简单情况**；
2. 对于其它情况，该问题可以被分解为更简单的同类问题，也就是说问题必须**可以转化**；
3. 从任何一种情况出发，都能转化成简单情况，这可以避免**无限递归**。

## 二、什么是深度优先搜索

深度优先搜索是将当前状态按照一定的规则, 先考虑拓展一步得到一个子状态, 再对这个子状态递归拓展下去。 直到无法拓展或已经找遍了所有的子状态,则退回一步到上一个状态。直到找 到目标状态或遍历完所有状态。这个过程通常可以用递归的方式描述,用递归函数实现。

如下图，这就是一棵搜索树，枚举了集合 $\{1, 2, 3\}$ 的所有子集。每一个数都有选和不选两种选择，于是我们可以递归搜索每一个数选不选。

![](https://cdn.luogu.com.cn/upload/image_hosting/xt8koetu.png)

就像这一道题，我们每一次可以跳 $1\sim b$ 步，只要这一个位置可以被跳到，我们就可以从现在的位置进行递归搜索下一次所有可以跳到的地方。当我们下一步能跳到终点时，更新答案。如果答案没有被更新，那么我们就无法跳到终点，输出 $-1$。代码旁有注释，可以借助注释理解。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int NR = 1005;
char s[NR];
int n, d, ans = 1e9;
//pos现在位置，step到目前为止跳了多少步 
void dfs(int pos, int step)
{
	if(pos + d >= n) 				//现在能跳到终点 
	{
		ans = min(ans, step + 1);	//更新答案 
		return;						//结束这一次的搜索，返回上一步 
	}
	for(int i = 1; i <= d; i ++)	//枚举所有可能跳到的步数 
		if(s[pos + i] == '1')		//可以跳i步 
			dfs(pos + i, step + 1);	//跳到那里，下一步搜索 
}

int main()
{
	scanf("%d%d\n%s", &n, &d, s + 1);//注意一定加一个\n，因为字符串读入时不会把\n吃掉 
	dfs(1, 0);						 //注意读入的位置，也就是起点的位置 
	if(ans < 1e9)					 //如果答案被更新 
		printf("%d", ans);			 //输出答案 
	else							 //答案未被更新 
		printf("-1");				 //输出-1 
	return 0;
}

```

第一版代码完成了，但是，我们还有优化方案。

## 三、剪枝

剪枝是搜索中优化的一大法宝。想一下，我们刚写的 dfs 把所有的情况全都列了出来，非常容易超时。剪枝，就是把对最终答案没有贡献的子树删去，不去进一步搜索，这样，我们枚举的次数变少好多，时间也就节省下来。

这道题中，我们要求答案的最小值，根据贪心原则，我们每一次跳的步子要尽可能的大，这样才能用最少的步数到达终点。所以我们修改一下我们的 dfs 函数，把从 $1$ 到 $d$ 改为从 $d$ 到 $1$，找到可以跳的步数向下搜索，这就是目前的最少步数。每一次都跳最少的步数，那么最终就用了最少的步数。向下搜索完后，直接 break 跳出循环，返回上一步，因为剩下的步子大小不能保证最终用了最少的步数，对答案没有任何贡献，所以直接剪枝。这一版代码如下：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int NR = 1005;
char s[NR];
int n, d, ans = 1e9;
//pos现在位置，step到目前为止跳了多少步 
void dfs(int pos, int step)
{
	if(pos + d >= n) 				//现在能跳到终点 
	{
		ans = min(ans, step + 1);	//更新答案 
		return;						//结束这一次的搜索，返回上一步 
	}
	for(int i = d; i >= 1; i --)	//枚举所有可能跳到的步数 
		if(s[pos + i] == '1')	
		{
			dfs(pos + i, step + 1); //跳到那里，下一步搜索
			break;
		}							//可以跳i步 
				 
}

int main()
{
	scanf("%d%d\n%s", &n, &d, s + 1);//注意一定加一个\n，因为字符串读入时不会把\n吃掉 
	dfs(1, 0);						 //注意读入的位置，也就是起点的位置 
	if(ans < 1e9)					 //如果答案被更新 
		printf("%d", ans);			 //输出答案 
	else							 //答案未被更新 
		printf("-1");				 //输出-1 
	return 0;
}

```

好了，这篇题解就告一段落了，希望大家通过我的题解，对递归和搜索能有更深的理解，感谢阅读！

---

## 作者：wky32768 (赞：11)

不是我说，那个最短路的题解真是让人难以置信。。
这题采用贪心的策略，从当前位置+最大距离开始向后枚举，枚举出第一个1的位置跳，然后继续算。不然就输出-1。
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
char a[1200];
int main() {
	cin>>n>>m;
	scanf("%s",a+1);
	int l=1;
	while(!=n) {
		bool flag={true};
		for(int i=l+m;i>l;i--){
			if(a[i]=='1'){
				l=i;
				flag=false;
				break;
                ans++;	
			}
		}
		if(flag==true){cout<<"-1";return 0;}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：空气树 (赞：7)

又是一种新思路，本着万物皆可DP的原则，本蒟蒻运用了DP水过。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int n,k,f[105];
//f[i]表示距离起点为i的地方需要跳多少步。
char a[105];
int main(){
	n=read();k=read();
	scanf("%s",a+1);
	f[1]=0;
	for(int i=2;i<=n;i++){
		if(a[i]=='0')continue;
        //倘若这里无百合花，那么肯定到不了
		f[i]=1<<30;
        //先赋一个最大值。
		for(int j=i-1;j>=max(i-k,1);j--){
        //枚举前面可以一步跳来的地方。
			if(a[j]=='0')continue;
            //此地无百合花，肯定跳不到
			f[i]=min(f[i],f[j]+1);
            //求最小值。
		}
	}
	if(f[n]==1<<30){
		printf("-1\n");return 0;
        //判断能否跳到。
	}
	printf("%d\n",f[n]);
	return 0;
}
```


---

## 作者：Lips (赞：4)

# 这题不用 $DP$ 或 $dfs$！

前言：其实我是奔着`最短路`~~和某已死算法~~这个标签来的。

胡口写了个贪心竟然 $A$ 了，之后康了一眼题解：

- 奇怪的~~已死~~的最短路

- 无脑的 $DP$

- 暴搜 $dfs$

### 但贪心可比这些玩意简单多了！

**贪心思路：** 考虑小青蛙目前所在的点 $x$，它、珂以跳到 $x+a(a\le d)$ 的点（由题意可得）。既然是贪心，我们就让小青蛙尽可能的**往前跳**，假设点 $x+1$ 到点 $x+d$ 之间没有荷花，那么它肯定回不了家；否则就将答案 $+1$。

于是，便可得到**代码思路**：对于目前的点 $now$（初始为 $0$），从 $now+d$ 倒着遍历到 $now+1$，如果目前的节点 $s_i$ 为`1`（荷花），那么更新 $now$ 为 $i$；否则如果 $now+d$ 到 $now+1$ 都木有荷花的话，直接输出`-1`并 $\operatorname{return}$。

----

贪心 $Code:$

```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
string s;
int now,len,d,ans;
int main()
{
	cin>>len>>d>>s;//原题中的 n，d和字符串 
	len--;//字符串从0开始 
	if(s[0]=='0'||s[len]=='0') printf("-1\n");//特判0号点和n-1号点 
	while(now!=len)//只要还没到家就一直跳（执着 
	{
		bool flag=0;//来判断是否踩到荷花 
		for(register int i=now+d;i>=now+1;i--)
		//贪心，从最远的点往前遍历 
			if(s[i]=='1') //如果为荷花 
			{
				now=i,flag=1;//更新now并break 
				break;
			}
		if(flag==0) //如果木有踩到荷花 
		{
			printf("-1\n");//肯定回不了家 
			return 0;//结束 
		}
		else ans++;//否则将最后答案+1 
	}
	printf("%d\n",ans);//别忘了输出 
	return 0;//完结撒花~~ 
}
```
~~请将代码理解后再抄~~

---

## 作者：jiangXxin (赞：3)

最近在CF上练DP，这道题，~~应该属于DP里面的入门水平吧~~

这道题和[P1052 过河](https://www.luogu.org/problem/P1052)很像，但是那道题需要离散化，这道题相当于是一个弱化版,有兴趣的同学可以写一下

主要思想：根据题意，蛤蟆只能够跳到石头上，所以我们的状态转移就只能够从石头上来转移，我们可以定义*DP*数组，那么根据我刚刚讲的思路，进行枚举每一个**石头**的位置,同时在里面套循环，枚举前d个单位，由于蛤蟆只能跳石头，所以不是石头的直接跳过。

最后无解的情况：**记录一下石头的总个数，如果最后的答案大于了这个总数，就是无解**

因此可得状态转移方程：**dp[i]=min(dp[i-j]+1)(1<=j<=d)**

**code**

# 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,m;
const int N=23150;
int a[N],dp[N];
int main(){
    cin>>n>>d;
    string s;
    cin>>s;
    for(int i=0;i<s.length();i++){
        int x=s[i];
        a[i+1]=x-'0';
        if(a[i+1])m++;
    }
    memset(dp,-1,sizeof(dp));
    dp[1]=a[1];
    for(int i=2;i<=n;i++){
        if(a[i]==0)continue;
        int ans=999999;
        for(int j=i-d;j<i;j++){
            if(j<=0){
                continue;
            }
            if(a[j]==0){
                continue;
            }
            ans=min(ans,dp[j]);
        }
        dp[i]=ans+a[i];
    }
    if(dp[n]>m){
        cout<<"-1"<<endl;
        return 0;
    }
    cout<<dp[n]-a[n]<<endl;
    return 0;
}

```


---

## 作者：hhrq (赞：2)

首先审题，给你总长,最远步数，可以跳的地方，输出最小步数

于是发现可以用递归做

本题的思路是：
起点为$l$,到$l$为止已经用$cnt$步,返回从$l$到终点需要$n$步。
如果$l$加$d$大于$n$, 可以直接返回现有的步数加一。
 如果不是， 就 从大到小枚举 （注意，这里为了考虑最优解， 所以要从大到小枚举$d$到$1$。）

如果， 起点加枚举的数的点为$1$， 则继续搜索$l + i, cnt + 1$。

循环完成， 如果没有返回，则返回$-1$， 意味不可能到达。

这是这一段代码：
```
int srh(int l, int cnt)//起点为l,到l为止已经用cnt步,返回从l到终点需要n步 
{
	if(l + d >= n) return cnt + 1;//已经到达终点则返回步数加一
	for(int i = d;i >= 1;i--)//从大到小枚举
		if(flower[l + i] == 1) return srh(l + i, cnt + 1);//可以走则继续搜索
	return -1;//不可能到达
		
}
```

有了子函数，于是，完整代码就是这个样子的：
```
#include<cstdio>//狂怼头文件
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<queue>
using namespace std;

int n, d;//定义，注意要定义在main函数外，因为子函数要用
bool flower[105];//定义， 因为只有1和0，定义bool即可

int srh(int l, int cnt)//注释看前面的那一小段代码
{
	if(l + d >= n) return cnt + 1;
	for(int i = d;i >= 1;i--)
		if(flower[l + i] == 1) return srh(l + i, cnt + 1);
	return -1;
		
}

int main()
{
	cin >> n >> d;//输入
	for(int i = 1;i <= n;i++)//循环
	{
		scanf("%1d", &flower[i]);//只输入一个数字
	}
	cout << srh(1, 0) << endl;//搜索，因为从起点开始，则l = 1, cnt = 0
	return 0;//结束，不要忘记return0
}

```

---

## 作者：Siyuan (赞：1)

## 本题思路：
很显然，这就是图论的思想。对于每个点，向所有它可以到达的点连有向边，接下来直接上 **最短路** 的板子就行了！（Floyd、Dijkstra、SPFA……）

### 代码如下：

```
#include<cstdio>
#include<queue>
#define N 105
#define inf 0x3f3f3f3f
using namespace std;

int n,d,cnt;
char a[N];
int dis[N],head[N];
bool vis[N];
struct Edge{
	int v,nxt;
}edge[N*N];

inline void add(int u,int v)
{
	cnt++;
	edge[cnt].v=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void spfa()
{
	for(int i=1;i<=n;i++)  dis[i]=inf;
	queue<int> q;
	dis[1]=0;  vis[1]=1;  q.push(1);
	while(!q.empty())
	{
		int u=q.front();  q.pop();  vis[u]=0;
		for(int v,w,i=head[u];i;i=edge[i].nxt)
		{
			v=edge[i].v;  w=dis[u]+1;
			if(dis[v]>w)
			{
				dis[v]=w;
				if(!vis[v])  vis[v]=1,q.push(v);
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&d);
	while(getchar()!='\n');
	for(int i=1;i<=n;i++)  a[i]=getchar();
	for(int i=1;i<=n;i++)
		if(a[i]=='1')  for(int j=1;j<=d&&i+j<=n;j++)  add(i,i+j);
	spfa();
	if(dis[n]==inf)  puts("-1");
	else  printf("%d",dis[n]);
	return 0;
}
```

---

## 作者：ynn_2009 (赞：0)

首先分析一下题目：n为从“1”到“n”中每个点的状态
               
  			s为小青蛙一次最多跳几步(在本代码中）

下面是代码，有注释
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n , s , cnt = 666;
bool flag[105] = {false};
int a[10000] = {};

void search(int p){
    if(a[p - 1] >= n){
        cnt = min (cnt , p - 1);//更新答案
        return ;
    }
    for(a[p] = a[p - 1] + 1; a[p] <= a[p - 1] + s; a[p]++){//每一次可以跳到的位置都是从上一次跳到的位置+1到上一次跳到的位置+s,
        if(flag[a[p]] == false){//剪枝
            continue;
        }
        search(p + 1);
    }
}

int main(){
	cin >> n >> s;
	int m = 1;
	for(int i = 1; i <= n; i++){
	    char x;
	    cin >> x;
	    if(x != '0'){
	        flag[i] = true;//构造地图
	    }else{
	        m = 0;
	    }
	}
	a[0] = 1;
	search(1);
	if(cnt == 666){//判断是否可以跳回家
	    cout << -1 << endl;
	    return 0;
	}
	cout << cnt << endl;//输出
	return 0;
}
```


---

## 作者：pnpn111 (赞：0)

最近老师教了我们最短路问题，于是我就在洛谷上搜SPFA这个标签刷题。于是就看到了这一题。

这道题用其他算法会更好，但因为我要练SPFA，所以还是用最短路。（以后会把贪心算法的源码加进去）

SPFA详细过程讲解：[最短路径问题---SPFA算法详解](https://blog.csdn.net/qq_35644234/article/details/61614581)

主要思路：

建图，然后用SPFA计算答案。

建图代码：
```cpp
for(int i=0;i<n;i++)
        canGo(i);
```
这一个是将所有点依次建边的for循环，没什么好说的。

```cpp
void canGo(int w)
{
    for(int i=w+1;i<n&&i-w<=d;i++)
        if(str[i]=='1')a[w].push_back(i);
}
```

这是建边函数，和一个点建边要满足2个条件。首先，青蛙能跳到这个点上。同时，这个点是可以让青蛙停留的。

SPFA函数代码没有什么特别的地方。

代码：

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int maxn=110;
const int inf=0x3f3f3f3f;

int n,d,dis[maxn];  //dis存的是最后的结果（这题只要输出最后一个）
bool inQue[maxn];
string str;
queue <int> que;
vector <int> a[maxn];

void canGo(int w) //把下标为w的这个点所能涉及到的所有能停留的点都加进去
{
    for(int i=w+1;i<n&&i-w<=d;i++)
        if(str[i]=='1')a[w].push_back(i);
}

int main()
{
    cin>>n>>d;
    for(int i=0;i<n;i++)  //输入，初始化
        dis[i]=inf;
    cin>>str;
    for(int i=0;i<n;i++)
        canGo(i);
    inQue[0]=true;
    que.push(0);
    dis[0]=0;
    while(!que.empty())  //SPFA算法
    {
        int w=que.front();
        inQue[w]=false;
        int len=a[w].size();
        que.pop();
        for(int i=0;i<len;i++)
        {
            int ls=dis[a[w][i]];
            dis[a[w][i]]=min(dis[a[w][i]],dis[w]+1);  //选择原来的和新的走法中小的值
            if(ls!=dis[a[w][i]]&&!inQue[a[w][i]])  //如果值变动了，又没有在队列中，就把它加进去
            {
                que.push(a[w][i]);
                inQue[a[w][i]]=true;
            }
        }
    }
    if(dis[n-1]==inf)  //如果最后一个没有被改动过，说明青蛙无法到达终点，输出-1
        cout<<-1<<endl;
    else
        cout<<dis[n-1]<<endl;
    return 0;
}

```


---

## 作者：hater (赞：0)

不是我说，那个最短路的题解真是让人难以置信。。 -------by 千题大佬 wky32768

蒟蒻默默膜一波大佬

但是真的可以用最短路做

友好的数据n<=100让我选择了Floyd

建图：

```cpp
for(int i=0;i<n;i++)
      for(int j=1;j+i<n&&j<=d;j++)
       if(l1[i+j]=='1') dis[i][i+j]=1;
```
第一层循环枚举出发的节点

第二层循环枚举可以去的节点

1.i+j<n不能出界 

2.j<=d 限制跳的距离（题目里有说明）

温馨提示：不习惯数组从零开始的OIER要细心

Floyd ： 

没什么好讲的 （模板）

不要忘了dis数组赋值最大值

达不到要输出-1

主要是k（中间点）要放在最外层循环

最后贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string l1;
int n,d,dis[105][105];
int main()
{
    cin>>n>>d>>l1;
    memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<n;i++)
      for(int j=1;j+i<n&&j<=d;j++)
       if(l1[i+j]=='1') dis[i][i+j]=1;
    for(int k=0;k<n;k++)
      for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
         dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    if(dis[0][n-1]!=0x3f3f3f3f) cout<<dis[0][n-1]<<endl;
      else cout<<-1<<endl;
    return 0;
}
```



---

## 作者：Vector_ (赞：0)

非常简单的贪心

~~这标签是个什么魔鬼~~

基本思想：

从最后一个点开始考虑

能跳多远跳多远

用递归累加步数，输出答案即可

```cpp
if(ans>1000) return -1;
```
这行放在递归里面可以输出无解

附AC代码

```cpp
#include<iostream>
using namespace std;
char m[101];
int d;
int tanxin(int x,int ans)//中文看得懂吧
{
    if(ans>1000) return -1;
    if(x==1) return ans;//到达目标则返回答案
    for(int i=max(1,x-d);i<=x;i++)
    {
        if(m[i]=='1')
        {
            return tanxin(i,ans+1);//递归
        }
    }
    return -1;
}
int main()
{
    int n;
    cin>>n>>d;
    for(int i=1;i<=n;i++) cin>>m[i];
    cout<<tanxin(n,0);
    return 0;//结束
}
```


---

## 作者：风云幻 (赞：0)

dfs来一发

	#include<bits/stdc++.h>
	using namespace std;
	int n,m;
	string s;
	bool jii=0;//jii标记有没有输出
	void dfs(int k,int zhi)
	{
		if(jii==1)//输出过就不要再找了
		return;
		if(k==n-1)
		{
			cout<<zhi;jii=1;//输出然后标记输出过
			return ;
		}
		int jij=0;//看看有没有往后查，后面解释有什么用
		for(int i=k+m;i>=k+1;i--)
		{
			if(i>=0&&i<n&&s[i]=='1'&&jij==0)
            1区间注意，我是从0到n-1查。
          2我是从大往小查，如果大的可以继续查，那就不用查小的了
			{ 
				dfs(i,zhi+1);jij=1; break;查找
			} 
		}
		if(k+m>=n-1&&jij==0)
		{
			jii=1;cout<<-1;return;
           如果已经超过目标点并且没法查，那肯定没有解，直接输出。
		}
	}
	int main()
	{
		cin>>n>>m;//输入
		cin>>s;//输入
		dfs(0,0)//本人习惯从0开始到n-1
   		if(jii==0)
		cout<<-1;//注意前面都没有输出的情况
	}

---

