# [USACO15DEC] Fruit Feast G

## 题目描述

Bessie 再次闯入了 Farmer John 的房屋！她在厨房发现了一堆柠檬和一堆橙子（每种水果的数量都可以视为无限），并决定尽可能多吃。

Bessie 的最大饱腹度为 $T$（$1 \leq T \leq 5,000,000$）。每吃一个橙子会使饱腹度增加 $A$，每吃一个柠檬会使饱腹度增加 $B$（$1 \leq A,B \leq T$）。此外，Bessie 最多可以喝一次水，这将使饱腹度立即减半（向下取整）。

请帮助 Bessie 计算她能达到的最大饱腹度！

## 说明/提示

题目提供者：Nathan Pinsker

## 样例 #1

### 输入

```
8 5 6```

### 输出

```
8```

# 题解

## 作者：qscweadzx (赞：17)

**这可能是最像NOIP初赛题的题解……**

基本思路：多重背包+特别处理喝水的情况+多重背包

具体实现参见代码

```cpp
#include <bits/stdc++.h>
using namespace std;
bool f[5000100]={1};//由于题目只需要判断可否达到饱食度，故不需要开int类型
int a,b,t;
int main(){
    cin>>t>>a>>b;
    for(int i=a;i<=t;++i)f[i]|=f[i-a];//多重背包，若i-a饱食度可达到，则i饱食度可达到（位运算其实只是显得秀）
    for(int i=b;i<=t;++i)f[i]|=f[i-b];//同上，多重背包
    for(int i=1;i<=t;++i)f[i>>1]|=f[i];//喝水，如果i饱食度可达到，则i/2饱食度可达到
    for(int i=a;i<=t;++i)f[i]|=f[i-a];//喝完水后再次多重背包
    for(int i=b;i<=t;++i)f[i]|=f[i-b];
    while(!f[t])--t;//从饱食度最高值向低枚举
    cout<<t<<endl;
    return 0;
}

```

求过审……

---

## 作者：liyilin2004 (赞：7)


## 思路：枚举
#### 枚举各种可能状态，用ans更新答案
~~水题，直接上代码~~
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
bool b[5000001][2];||记录状态 
int T,A,B,ans;
void dfs(int x,int flag)||flag记录是否喝过水
{
    if(b[x][flag])
		return; ||已经枚举过该状态，返回（不判断状态会超时三个点，如我）
	b[x][flag]=1; 
	if(x+A<=T)
		dfs(x+A,flag); ||吃橙子不会撑爆，吃一个
	if(x+B<=T)
		dfs(x+B,flag);||吃柠檬不会撑爆，吃一个
    if(!flag)||没喝过水，喝一口
		dfs(x/2,1); 
	ans=max(ans,x);||更新答案
}
int main()
{
    scanf("%d %d %d",&T,&A,&B); 
	dfs(0,0); 
	printf("%d",ans); 
	return 0;
}
```
~~蒟蒻第一次发题解，欢迎大佬帮忙指正~~

---

## 作者：Lagibol (赞：7)

一道挺好的dp or DFS的题，~~就应该用暴力~~

说一下本蒟蒻的思路：
假设这只牛吃了m个橙子，n个柠檬，那么饱食度为（Am+Bn）; 这时它喝水，饱食度减为

**（Am+Bn）/2=（(m%2)A+(n%2)B)+(m/2)A+(n/2)B**


举个栗子：吃三个橙子与一个柠檬再喝水等效于吃一个橘子喝口水再吃一个橘子和一个柠檬。

所以我们可以把喝水提到前面考虑，
那么就分成了四种情况：

1.不喝水直接吃；
（没说一定要喝水）

2.吃个橘子喝口水再吃；

3.吃个柠檬喝口水再吃；

4.吃个橘子+一个柠檬喝口水再吃；

然后~~~~用一种类似鸡兔同笼的暴力解决；

代码如下（请忽略蒟蒻闷骚的码风）
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
//int ko(int x,int y)
//{
//  if (x%y==0)
//    return y;
//  return ko(y,x%y);
//}
int main( )
{
  int T,a,b,i,j,w,l1=-1,l2,l3,l4,f=0,p,l=-1;
  cin>>T>>a>>b;
  //w=ko(a,b);
  if (T%a==0||T%b==0)//特判 
    {
      cout<<T;
      return 0;
    }
  l2=a/2;
  l3=b/2; 
  l4=(a+b)/2;
  if (a+b>T)
    l4=0;
  if (T>(a-1)*(b-1)&&T>50000)//详见P3951 
    {
      cout<<T;
      return 0;
    }
  for (i=0;i<=T/a;++i)//第一种不喝水 
    {
      for (j=0;j<=T/b;++j)
        {
          if (i*a+b*j<=T&&i*a+b*j>l1)
            {
              l1=i*a+b*j;
            }
        }
    }
  p=l1;
  T-=l2;
  for (i=0;i<=T/a;++i)//第二种 
    {
      for (j=0;j<=T/b;++j)
        {
          if (i*a+b*j<=T&&i*a+b*j>l)
            {
              l=i*a+b*j;
            }
        }
    }
  p=max(p,l+l2);
  T+=l2;
  T-=l3; 
  l=-1;
  for (i=0;i<=T/a;++i)//第三种 
    {
      for (j=0;j<=T/b;++j)
        {
          if (i*a+b*j<=T&&i*a+b*j>l)
            {
              l=i*a+b*j;
            }
        }
    }
  p=max(p,l+l3);
  T+=l3;
  T-=l4;
  l=-1;
  if (a+b<=T+l4)
    {
      for (i=0;i<=T/a;++i)//第四种 
        {
          for (j=0;j<=T/b;++j)
            {
              if (i*a+b*j<=T&&i*a+b*j>l)
                {
                  l=i*a+b*j;
                }
            }
        }
    }
  p=max(p,l+l4);
  T+=l4;
  cout<<p;
  return 0;//over 
}
```
PS：排列已改，望通过

---

## 作者：StaroForgin (赞：5)

本题一看就是暴搜，看数据范围也很小，那就把所有情况都枚举一遍吧
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<set>
#include<map>
using namespace std;
int t,a,b,maxx;
int dfs(int sum,bool flag)
{
	if(sum>t)
		return 0;//超出限制，退出
	if(sum>maxx)
	{
		maxx=sum;
		if(maxx==t)
		{
			printf("%d",t);
			exit(0);
		}//达到t后不会有更大的了，直接输出
	}
	int temp=sum;
	int da=dfs(sum+a,flag);//吃橘子
	int db=dfs(sum+b,flag);//吃柠檬
	if(!flag)//如果可以喝水
	{
		int dw=dfs(sum/2,true);
		if(dw>temp)
			temp=dw;
	}
	if(da>temp)
		temp=da;
	if(db>temp)
		temp=db;
	return temp;//返回最大值
}
int main()
{
	scanf("%d %d %d",&t,&a,&b);
	printf("%d",dfs(0,false));
	return 0;
}
```
~~OK~~

---

## 作者：williamllk (赞：4)

这是一道我们模拟赛的题目，当时我写了一个36分的代码，有点难看，就不拿出来了。

先是[传送门](https://www.luogu.org/problemnew/solution/P4817)

接下来我来给各位讲解一个做法：

①因为饱腹值可以减半，所以不妨给它开一个二位数组
  ```cpp
    int seen[2][5000100];
```
②为了寻找可以达到的最大的饱腹值，不妨把所有能达到的饱腹值记录为 true ，不能达到的记录为 false。

核心思想差不多就介绍到这了，接下来上AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int seen[2][5000100];
int main(){
	//freopen("feast.in","r",stdin);
	//freopen("feast.out","w",stdout);
	int t,x,y;
	cin>>t>>x>>y;
	memset(seen,false,sizeof(seen));
	seen[0][0]=true;
	for(int a=0;a<=1;a++){
		for(int i=0;i<=t;i++){
			if(!seen[a][i]) continue;
			if(i+x<=t) seen[a][i+x]=true;
			if(i+y<=t) seen[a][i+y]=true;
			if(a<1) seen[a+1][i/2]=true;
		}
	}
	int ret=t;
	while(!seen[1][ret]) ret--;
	cout<<ret;
	return 0;
}
```
望各位看官点个赞，评个论再走！

---

## 作者：Kalium (赞：3)

# P4817题解

## 题意：

有头牛 $Bessie$ 吃橙子和柠檬，吃个橙子能加 $A$ 点能量，吃个橙子加 $B$ 点能量，$Bessie$ 还有一次喝水机会，喝一次水它就可以把现有能量除以 $2$，现在 $Bessie$ 最多能包容 $T$ 的容量，问他最多获得多少能量？

#### 本题有 $2$ 种方法

## 1.完全背包（本人只有92分，WA#3）

其实有兴趣的同学可以选择打一下

### 思路:

$Bessie$ 在吃东西的时候只有 $2$ 种选择，一种是中间和一次水，一种是中间都不喝水，那么我们可以分别用 $ans1$ 和 $ans2$ 来分别存储没喝水和喝水的时候，最大能吃多少能量

#### 没喝水

我们用 $w$ 数组来分别存储橘子和柠檬所含有的能量，那么在没喝水的情况下，背包容量为 $T$ ，价值和价格都为 $w_i$ （~~尽管 $i$ 只到 $2$~~），跑一边完全背包即可

#### 喝水

还是用 $w$ 数组来分别存储橘子和柠檬所含有的能量，喝水后它所含的能量只剩一半，相当于它的胃在原来基础上扩大了 $1$ 倍，即 $T << 1$ 了，那么这个时候背包容量就为 $T << 1$，价值和价格同上不变，存入 $ans2$ 即可，但是你的 $T << 1$ 了，那么你返回的 $ans2$ 也应该除以 $2$ 才对

#### 代码，有兴趣的自己研究为何挂了

```cpp
#include <iostream>

using namespace std;

const int T = 5e6 + 7;

int t, a, b;
int w[3];

inline int maxa(int a, int b) {
	if (a > b)
		return a;
	return b;
}

int dp1[T]; 

inline int DP1() {
	for (int i = 1; i <= 2; i ++) {
		for (int j = w[i]; j <= t; j ++)
			dp1[j] = maxa(dp1[j - w[i]] + w[i], dp1[j]);
	}
	return dp1[t];
} //没喝过水 

int dp2[T << 1];

inline int DP2() {
	int tmp = 0;
	for (int i = 1; i <= 2; i ++) {
		for (int j = w[i]; j <= (t << 1); j ++)
			dp2[j] = maxa(dp2[j - w[i]] + w[i], dp2[j]); 
	}
	return dp2[t << 1] >> 1;
} //喝过水 

int main() {
	cin >> t >> a >> b;
	w[1] = a;
	w[2] = b;
	if (a > t)
		w[1] = 0;
	if (b > t)
		w[2] = 0;
	if (a > t && b > t) {
		cout << 0 << endl;
		return 0;
	}
	int ans1 = DP1();
	int ans2 = DP2();
//	cout << ans1 << " " << ans2 << endl;
	cout << maxa(ans1, ans2) << endl;
//	cout << (T << 1) << endl;
	return 0;
}
```

## 2.搜索

在本人发现完全背包挂了的时候，毅然决然的抛弃了完全背包，又看了看数据范围

什么？就这？

爆搜石锤

其实爆搜很简单，记录一下目前吃的能量和胃的容量即可

于是我兴冲冲的写了份代码交了上去，给你们 $look$ 一下

```cpp
#include <iostream>

using namespace std;

int t, a, b;
int ans;

inline int maxa(int a, int b) {
	if (a > b)
		return a;
	return b;
}

void dfs(int food, bool flag) {
	ans = maxa(ans, food);
	if (t >= food + a)
		dfs(food + a, flag);
	if (t >= food + b)
		dfs(food + b, flag);
	if (! flag)
		dfs(food >> 1, flag ^ 1);
	return ;
}

int main() {
	cin >> t >> a >> b;
	dfs(0, 0);
	cout << ans << endl;
	return 0;
} 
```

但是T了！！！

你们可以试试，不管吸氧还是 $register$，都是TLE！！

于是开始剪枝

我们发现可以记搜，将搜索到的能量做标记，下次再搜到这个直接返回

用 $mem_i$ 来表示当前的能量搜过没，搜过直接 $return$ 即可

~~其实，你与AC只有一步之遥~~

# 代码（CODE）

```cpp
#include <iostream>

using namespace std;

const int T = 5e6 + 7;

int t, a, b;
int ans;
int mem[T];

inline int maxa(int a, int b) {
	if (a > b)
		return a;
	return b;
}

void dfs(int food, bool flag) {
	if (mem[food])
		return ;
	mem[food] = 1;//就是这步！！
	if (food > t)
		return ;
	ans = maxa(ans, food);
	dfs(food + a, flag);
	dfs(food + b, flag);
	if (! flag)
		dfs(food >> 1, flag ^ 1);
	return ;
}

int main() {
	cin >> t >> a >> b;
	dfs(0, 0);
	cout << ans << endl;
	return 0;
} 
```

---

## 作者：fyx_Catherine (赞：3)

## 暴力大法好
不少巨佬都用完全背包来做的，我一个不会完全背包的蒟蒻就用**暴力**来做
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
int read(){
	int a=0,k=1;char c=getchar();
	while (!isdigit(c)){if (c=='-')k=-1;c=getchar();}
	while (isdigit(c)){a=a*10+c-'0';c=getchar();}
	return a*k;
}
int n,m,vis[5000005],maxn=0;
struct node{
  int num,vis;
};
int main(){
	int x,y;
    memset(vis,0,sizeof(vis));
    n=read();x=read();y=read();
    queue<node>q;//定义一个q队列
    node a;a.num=x;a.vis=0;
    node b;b.num=y;b.vis=0;
    q.push(a);q.push(b);
    vis[x]=1;vis[y]=1;
    while(!q.empty()){
        node t=q.front();
        q.pop();
        if(t.num+x>n)maxn=max(maxn,t.num);
        if(t.num+x<=n&&vis[t.num+x]==0){vis[t.num+x]=1;node k;k.num=t.num+x;k.vis=t.vis;q.push(k);}
        if(t.num+y>n)maxn=max(maxn,t.num);
        if(t.num+y<=n&&vis[t.num+y]==0){vis[t.num+y]=1;node k;k.num=t.num+y;k.vis=t.vis;q.push(k);}
        if(t.vis==0&&vis[t.num/2]==0){vis[t.num/2]=1;node k;k.num=t.num/2;k.vis=1;q.push(k);}
    }
    printf("%d\n",maxn);//输出最大值
    return 0;
}

```


---

## 作者：WanderingTrader (赞：2)

这道题其实本该是一道$dp$，然而条件中多了“可以使用**1次**喝水操作”，所以$dp$就比较难写了。 
#### 题意简述
（为方便叙述我将所有字母改成小写）  
其实就是两个物品，一个重量为$a$，一个重量为$b$，每种物品都有无限个，最多只能装载$t$这么多重量，但是装载时有一次机会可以将当前重量减半，问最多能装多重。  
#### 题目分析
既然$dp$没法做，我们就要考虑比$dp$更灵活的一种算法。  
算法标签写的是“枚举，暴力”，所以我想到了搜索，而且是$bfs$(广度优先搜索)。 
#### 代码&思路
我们先定义一个结构体以及装有这种结构体的队列：
```cpp
typedef long long ll;
struct node { ll x;bool used; } k;
queue <node> q;
```
此处$x$表示当前的重量，$used$表示是否有使用减半操作。  
然后做一个$vis$数组进行“剪枝”，不过这个数组要加一维，也就是$used$这一维：
```cpp
bool vis[N][2];
```
初始化操作（当然队列也要初始化）：
```cpp
int main(){
	ll t,a,b,ans = 0;
	scanf("%lld%lld%lld",&t,&a,&b);
	q.push({0,0});
	while(!q.empty())
	{
	}
	printf("%lld\n",ans);
	return 0;
}
```
接下来我们就要重点写 $bfs$ 部分了。  
首先不满足条件的数据要舍去：
```cpp
k = q.front();
q.pop();
if(k.x > t || vis[k.x][k.used]) continue;
```
修改答案：
```cpp
vis[k.x][k.used] = 1;
ans = max(ans,k.x);
```
加入物品：
```cpp
q.push({k.x + a,k.used});
q.push({k.x+b,k.used});
```
如果还没减半就减一下：
```cpp
if(!k.used) q.push({k.x / 2 , 1});
```
结束了。是不是很简单？  
$bfs$代码：
```cpp
while(!q.empty())
	{
		k = q.front();
		q.pop();
		if(k.x > t || vis[k.x][k.used]) continue;
		vis[k.x][k.used] = 1;
		ans = max(ans,k.x);
		q.push({k.x + a,k.used});
		q.push({k.x+b,k.used});
		if(!k.used) q.push({k.x / 2,1});
	}
```
全部代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 5000005
typedef long long ll;
struct node { ll x;bool used; } k;
queue <node> q;
bool vis[N][2];
int main(){
	ll t,a,b,ans = 0;
	scanf("%lld%lld%lld",&t,&a,&b);
	q.push({0,0});
	while(!q.empty())
	{
		k = q.front();
		q.pop();
		if(k.x > t || vis[k.x][k.used]) continue;
		vis[k.x][k.used] = 1;
		ans = max(ans,k.x);
		q.push({k.x + a,k.used});
		q.push({k.x+b,k.used});
		if(!k.used) q.push({k.x / 2,1});
	}
	printf("%lld\n",ans);
	return 0;
}
```
我们可以看到，虽然题目中的$t$很大$(t\le5\times 10^6)$，但是每个数最多只访问$2$遍$(used=1\ or\ used = 0)$，加上一部分超过$t$的数据，肯定能在$1s$之内做完(实测结果：所有数据点用时加起来为$64ms$)。  
$The\ end.$

---

## 作者：TESJackeyLove (赞：1)

**题目读完，意思就是用一些A和B尽可能去拼成T，貌似要枚举，但是写循环的话好像又不是很好写，既然如此，那就用万能的DFS吧，先不用管需不需要剪枝，写了再说。**
- DFS的思路就是定义一个全局变量ans，每次进入DFS的时候用我们得到的一个饱食度x和ans进行比较，ans存二者的较大值，这里一个很容易想到的剪枝（写多了就很容易写出来）就是当 ans==T 的时候，不可能会有更好的解了，因为大于T就boom爆炸了，所以此时就可以return结束函数了。
```cpp
  ans=max(ans,x);
  if(ans==t) return;
```

- 那怎么去搜呢？先吃橙子（吃柠檬是一样的写法）看看，判断一下吃完会不会爆炸（大于T），如果不会，判断一下x+a这个饱食度状态有没有搜过，没有搜过就去搜这个状态，搜过就不搜。
- 那如果吃完会爆炸呢？不急，题目说了，有一次喝水的机会，我们用一个全局变量f记录一下是否喝过，如果没有喝过水，那我们先喝水再吃，判断喝完水再吃会不会爆炸（x/2+a<=T就不会），如果不会爆炸，一样的，看看这个状态有没有搜过，没有搜就去搜，并且把f置为1，表示水已经喝过，同时注意在DFS后面把f复位成0回溯。否则不搜。吃柠檬同理，把a改成b就可以了。以下是代码：
```cpp
  #include<iostream>
  #include<cstdio>
  #include<cmath>
  #include<algorithm>
  #include<cstring>
  #include<cstdlib>
  #include<queue>
  #include<stack>
  #define fore(i,a,b) for(int i=a;i<=b;i++)
  #define foru(i,a,b) for(int i=a;i<b;i++)
  #define ford(i,a,b) for(int i=a;i>=b;i--)
  #define IGNB std::ios::sync_with_stdio(false);
  #define ll long long
  #define INF 0x3fffffff
  using namespace std;
  int ans,t,a,b;
  bool f;
  bool vis[5000005];
  void dfs(int x){
      ans=max(ans,x);
      if(ans==t) return;
      //吃橙子 
      if(x+a<=t){
          if(!vis[x+a]){
              vis[x+a]=1;
              dfs(x+a);
          }
      }
      else{
          if(!f){
              if(x/2+a<=t&&!vis[x/2+a]){
                  f=1;
                  vis[x/2+a]=1;
                  dfs(x/2+a);
                  f=0;
              }
          }
      }
      //吃柠檬，一样的写法 
      if(x+b<=t){
          if(!vis[x+b]){
              vis[x+b]=1;
              dfs(x+b);
          }
      }
      else{
          if(!f){
              if(x/2+b<=t&&!vis[x/2+b]){
                  f=1;
                  vis[x/2+b]=1;
                  dfs(x/2+b);
                  f=0;
              }
          }
      }
  }
  int main(){
      IGNB;
      cin>>t>>a>>b;
      dfs(0);
      cout<<ans;
      return 0;
  }

```


---

## 作者：_Ayanami_ (赞：1)

看完题本来以为要用背包

然后听说数据很水就直接上DFS了

状态什么的也不用记

直接特判一下饱腹值达到t用exit(0)停止程序就完事了

非常简洁的代码
```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int t,a,b,maxx;
void dfs(int v,bool d)
{
	if(v>t) return;  //越界
	if(v==t) printf("%d",t),exit(0);  //特判
	if(v>maxx) maxx=v;  //更新最大值
	if(d) dfs(v/2,0);  //喝水
	dfs(v+a,d),dfs(v+b,d);  //继续搜
	return;
}
int main()
{
	scanf("%d%d%d",&t,&a,&b);
	dfs(0,1);
	printf("%d",maxx);
}
```


---

## 作者：9290ei (赞：1)

## 这题是黄题？！只有本蒟蒻觉得应该是红题吗
#### **看了楼下dalao的题解。~~明明是DFS，却要说是暴力枚举~~**
贴上代码：
```
#include<iostream>
#include<algorithm>
using namespace std;
long long t,a,j,b,ans,c[5000000];
void DFS(int x,int w)//w用来记录有没有喝水
{

	if(c[x]==1)
	   return ;//测到重复就baka。
	c[x]=1;  //一个小小的优化，不加就TLE。QAQ
	if(x>=ans)
	  ans=x;
	if(t>=x+a)  DFS(x+a,w);
	if(t>=x+b)  DFS(x+b,w);
	if(w==1)  DFS(x/2,0);
}
int main()
{
	cin>>t>>a>>b;
	DFS(0,1);
	cout<<ans;
}
```

---

## 作者：梧桐灯 (赞：1)

~~吐槽：Bessie喝水能变饿？！~~


**我的思路：BFS+用桶去重优化**

队列里保存两个量：当前饱食度，是否喝过水。

向下扩展时，满足以下两个条件入队：

### ①该节点没有被访问过
### ②饱食度没超过t

然后每次更新最大值即可

代码：

```

#include <cstdio>
#include <iostream>
#include <queue>
#define MP make_pair
using namespace std;

int t, a, b, ans;
bool f[5000005][2];
queue <pair <int, bool> >q;

int main () {
	scanf ("%d %d %d", &t, &a, &b);
	q.push (MP (0, 1));
	int x;
	bool y;
	while (!q.empty ()) {
		x = q.front ().first;
		y = q.front ().second;
		if (x > ans)//更新最大值
			ans = x;
		q.pop ();
		if (y && !f[x >> 1][0]) {//y=1表示还没喝水，喝水后入队列
			q.push (MP (x >> 1, 0));
			f[x >> 1][0] = 1;
		}
		if (x + a <= t && !f[x + a][y]) {//吃橙子加a饱食度，但不能超过t
			q.push (MP (x + a, y));
			f[x + a][y] = 1;
		}
		if (x + b <= t && !f[x + b][y]) {//同上
			q.push (MP (x + b, y));
			f[x + b][y] = 1;
		}
	}
	printf ("%d\n", ans);
    return 0;
}

```


---

## 作者：MuYC (赞：0)

#### 前言

$dp$ 好题。

#### 思路


不妨先跑一遍 $01$ $dp$ 跑这一遍的时候**不喝水**

然后跑 $01$ $dp$ 的同时生成一个另外的数组 $mp[i]$ 在$dp[i]$ 为 $1$ 的情况下就把 $mp[i / 2$ （向下取整）$]$ 赋值为$1$。

把第一个数组所有能够到达的饱腹值入队列1，第二个数组的可到点入队列二

接下来，枚举 $0$ ~ $T$ 的每一个数，枚举在哪一个数的时候喝水可以得到最优答案(前提是可以通过不喝水就到达这个点)。

+ 倘若当前点喝水后产生的效果，也就是到达 $i/2$ 的那一个点本来就是可以不用喝水就可以到达的，那么我们就移动队列2的指针，不断左移，直到到达第一个  $vis2[Now2] + i / 2 <= T$ ，这时候我们可以得到在当前点喝水得到的最大饱腹值。

+ 倘若 $i / 2$ 的那一个点无法通过不喝水就到达，那么就移动队列1的指针，不断左移，直到枚举到 $vis1[Now1] + i / 2 <= T$ ,就停止移动，这时候我们可以得到当前点喝水的最大饱腹值。

结合我对于队列1以及队列2的定义，不难理解这个做法。

时间复杂度O($n$)

### Code

(上面可能讲得不清楚，不懂的话可以看看代码)


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5000005;
bool dp[MAXN];
bool mp[MAXN];
int vis[MAXN], vis2[MAXN],tail = 0,tail1 = 0;
int main()
{
    dp[0] = 1;
    int T,A,B;
    cin >> T >> A >> B;
    for(int i = 0 ; i <= T ; i ++)
    {
        if(i >= A) dp[i] |= dp[i - A];
        if(i >= B) dp[i] |= dp[i - B];
        //上面是普通的01dp
        //下面是生成第二个数组
        mp[i] = dp[i];
        mp[i / 2] |= dp[i];
    }
    for(int i = 0 ; i <= T ; i ++) 
    {
        if(dp[i]) tail ++ , vis[tail] = i;//进入队列1
        if(mp[i]) tail1 ++ , vis2[tail1] = i;//进入队列2
    }
    int Now1 = tail , Now2 = tail1,Ans = -1;
    for(int i = 0 ; i <= T ; i ++)
    {
        if(dp[i] == 0) continue;//如果这个点不能通过不喝水到达，那么显然不能在这个点进行喝水
        if(dp[i / 2] == 1)//倘若可以通过不喝水就到达i/2
        {
            while(Now2 >= 1 && vis2[Now2] + i / 2 > T) Now2 --;//移动指针2
            Ans = max(Ans,vis2[Now2] + i / 2);//计算答案取max
            continue;
        }
        //省了一个else，因为上面有continue
        while(Now1 >= 1 && vis[Now1] + i / 2 > T) Now1 --;//移动队列1
        Ans = max(Ans,vis[Now1] + i / 2);//计算答案取max
    }
    cout << Ans;
    return 0;
}
```

---

