# [USACO07OPEN] Catch That Cow S

## 题目描述

FJ 丢失了他的一头牛，他决定追回他的牛。已知 FJ 和牛在一条直线上，初始位置分别为 $x$ 和 $y$，假定牛在原地不动。FJ 的行走方式很特别：他每一次可以前进一步、后退一步或者直接走到 $2\times x$ 的位置。计算他至少需要几步追上他的牛。

## 样例 #1

### 输入

```
1 
5 17```

### 输出

```
4```

# 题解

## 作者：YF1999 (赞：44)

看到题解一溜溜全是搜索，这里发个带贪心的解题方法，而且是所有题解中最快的（0ms）

原题是FJ追牛，我们可以反过来想，变成牛追FJ，这样子，牛的移动方式有y+1，y-1，和直接y/2，因此我们在移动牛的时候可以**优先**考虑能否y/2，然后再考虑y+1,y-1的移动方式

之所以要反过来想是因为 在FJ追牛的时候是不能优先考虑x\*2再考虑x+1，x-1的，也不能优先考虑x+1,x-1再考虑x\*2！！


举个例子，FJ在25，牛在102，先\*2再+1再\*2共三步，FJ追牛的时候没办法优先考虑怎么走。但是如果是牛追FJ，牛可以直接y/2，这个时候牛的位置变成51，可以发现是奇数，没办法优先y/2，所以y-1变成50（y+1也要考虑），然后优先考虑y/2变成25，共三步。


代码~~

```cpp
#include<iostream>
#include<queue>
using namespace std;

typedef pair<int,int> P;// p.first 表示牛的位置，p.second表示牛走了多少步 
queue<P> que;
P p;

int main(){
    int t, FJ, Min;
    cin >> t;
    while( t -- ){
        cin >> FJ >> p.first;
        Min = 1000000;
        que.push( P(p.first,0) );
        while( que.size() ){
            p = que.front();
            que.pop();
            if( p.first < FJ ){//如果牛在FJ的后面
                p.second += FJ - p.first;
                if( Min > p.second ) Min = p.second;
            }else if( p.first % 2 == 0 ){//牛可以直接除以2，优先考虑除以2 
                if( p.first / 2 > FJ )
                    que.push( P(p.first/2,p.second+1) );
                else if( p.first - FJ > FJ - p.first/2 )//除以2 之后距离FJ近一些 
                    que.push( P(p.first/2,p.second+1) );
                else{//除以2 之后距离FJ的距离反而变远了，因此不考虑除以2，直接走到FJ那里去 
                    p.second += p.first - FJ;
                    if( Min > p.second ) Min = p.second;
                }
            }else{//如果不能直接y/2，选择y+1，y-1的方式 
                que.push( P(p.first+1,p.second+1) );
                que.push( P(p.first-1,p.second+1) );
            }
        }
        cout << Min << endl;
    }
    return 0;
}
```

个人喜欢用队列来记录数据，也可以采用其他方法


---

## 作者：于丰林 (赞：42)

这一篇题解写给刚刚学习宽搜的同学，记得当时刚学时看题解基本都是一句话：这题裸的宽搜啊，当时一脸绝望。。。

本篇题解延续个人风格，细致的讲解：各位大佬可以跳过，直接看代码找本题坑点也行。

首先先来明确一下什么是宽搜？

通俗来说，宽搜就是从一个点开始扩展，将所能延伸到的点记录下来，当不能延伸时就对下一个点重复这个操作，直到找到最先满足条件的解为止（反正我是这么理解的。。。）

那么对于这一道题来说，一个点所能延伸出来的点只有+1，-1，*2，那么我们就可以开一个队列（手写也是可以的，但是为了省事就用STL吧。。。），从起点开始延伸，遇到没有走过的点就加入队列，并记录走了多少步，那么为什么走过的点不加呢？（因为如果之前走过，那么之前走肯定比现在走得到的解更优），当遇到第一个走到的位置达到终点是跳出并输出当时走了多少步即可。

差不多就这些了吧。。。

最后，附上本题代码（有详解）：

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
queue<int>q;
const int maxn= 1e5+5;
int dis[maxn];//dis表示走到目前位置最少走了多少步 
void bfs(int s,int y)
{
    int x;
    while(!q.empty())//多组询问常规清空操作 
    {
        q.pop();
    }
    memset(dis,0x5a5b5c4f,sizeof(dis));//初值设为inf，省去一个vis数组的空间 
    dis[s]=0;
    q.push(s);
    while(!q.empty())//bfs模板 
    {
        x=q.front();
        q.pop();
        if(x==y)//满足条件跳出 
        {
            printf("%d\n",dis[y]);
            return;
        }
        if(x+1<=maxn&&dis[x+1]==dis[0])//以dis[0]作为判断依据，也就是inf。判断该点是否走过，注意不要走出maxn 
        {
            dis[x+1]=dis[x]+1,q.push(x+1);
        }
        if(x-1>0&&dis[x-1]==dis[0])//x-1>0 比较显然吧，如果小于0你会RE，如果等于0你的dis[0]就会被更新，你整个程序就会崩掉 
        {
            dis[x-1]=dis[x]+1,q.push(x-1);
        }
        if(x*2<=maxn&&dis[x*2]==dis[0])//不复读了。。。 
        {
            dis[x*2]=dis[x]+1,q.push(x*2);
        }
    }
}
int main()
{
    int t;
    int x,y;
    scanf("%d",&t);
    for(int i=1; i<=t; i++)
    {
        scanf("%d%d",&x,&y);
        bfs(x,y);
    }
    return 0;
}
```


---

## 作者：AlphaPig (赞：24)

##### BFS（breadth first search）宽（广）度优先搜索，需要队列的数据结构
#### 这是一道经典bfs题，此处用数组模拟队列，dfs的特点是不撞南墙不回头，而bfs说形象点就是辐射性的向外扩展处理
```
#include<bits/stdc++.h>
using namespace std;
int n,k,x,q[100100],v[100010],dis[100010];
//q是队列，v记录访问，dis表示到点的步数
int main()
{
    int c;
    cin>>c;
    
    while(c--) 
    {
        cin>>n>>k;
        memset(q,0,sizeof(q));
        memset(v,0,sizeof(v));
        memset(dis,0,sizeof(dis));
        
        //其实重置没有必要的，数据大了重置会炸时间，但方便大家理解
        //一般来说有多组数据亦可以直接入队，因为处理完一个点head肯定等于tail
        int head=0,tail=1;//头和尾巴（尾巴进头出）
        q[tail]=n;
        v[n]=1;	
        while(head<=tail)
        {
            head++;//表示开始处理点了
            for(int i=0;i<3;i++)//枚举三种行走方式
            {
                x=q[head];
                if(i==0) x++;
                if(i==1) x--;
                if(i==2) x*=2;
                if(x>=0 && x<=100000)
                    if(!v[x])//标准bfs
                    {
                        tail++;
                        q[tail]=x;//入队
                        v[x]=1;//记录
                        dis[x]=dis[q[head]]+1;//更新步数
                    }
            }
        }
        cout<<dis[k]<<endl;//输出结果
    } 
    return 0;
}
```

---

## 作者：Push_Y (赞：18)

# 一个深搜的代码
### 这题开始我做了很多遍，有的MLE有的WA
### 应该说现在知道了容易犯错的点，给大家分享一下
首先，如果我们把牛固定，去移动FJ，那我们就会需要判断，坐标变为x*2的FJ有没有越界，这样速度就会减慢。

所以我们改变思路，固定FJ，移动牛，因为/2是不可能小于0的（无限趋向于0也不会小于0）。

把FJ和牛看成在一条数轴上

### 看代码↓
```cpp
#pragma GCC ("Ofast")//在洛谷没用的优化，请省略
#include <bits/stdc++.h>
using namespace std;

int n,p,co,s,k;

/* n代表输入的组数
   p代表FJ的坐标
   co代表牛的初始坐标（因为牛会动）
   s代表dfs中的步数
   k代表所有s中的最小值，即最小步数
*/

void dfs(int c){//写函数dfs，c代表每次移动后牛的坐标
    if(c<p) {//如果移动后的牛已经到了FJ的左边，那直接做以下计算
        s+=p-c;
        if(s<k)k=s;   
        
        s-=p-c/2+1;//这个特别重要，记得减回去，我就是这个错没找出来做了很久
        
        return;
    }
    if(c%2==0){//考虑能够整除2的情况
    	if(c/2>p){//牛x/2以后在FJ的右边那么移动是值得的
    		s++;dfs(c/2);s--;
            return;	
        }
//接下来都是牛x/2在FJ的左边了
    	if(p-c/2<c-p-1){//如果到左边以后值得
    		s+=p-c/2+1;
    		if(s<k)k=s;
    		
         s-=p-c/2+1;//务必减回来
            
         return;
        }
        else {
            s+=c-p;
            if(s<k){
                k=s;
                return;
            }
        }
    }
    else {
        s++;dfs(c-1);s--;
        s++;dfs(c+1);s--;			
    }	
    return;	
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p>>co;
        s=0;k=abs(co-p);//把k初始赋值为牛与FJ直接的距离
        dfs(co);
        cout<<k<<endl;
    }
}
```
## 便于大家调试，给出一组输入输出
输入：
```
2
2880 39798
4560 24257
```
输出：
```
398
1507
```




---

## 作者：Strong_Jelly (赞：13)

# 本题解将详细讲解广搜，请已经会的人直接看代码

这道题可以用广搜来做，只不过是一个**数轴**的广搜，不像其他广搜是矩阵

首先：我们先看一下简单搜索的**四要素**（~~自己起的~~）

**1.起点**：有，农夫的位置

**2.终点**：有，牛的位置

**3.边界**：没有，~~自己定义一个~~，就0 ~ 1000001吧（终点牛和起点农夫的位置是正整数，还≤10^5，所以0 ~ 1000001完全够了）

**4.起点的移动方案**：有，向后一格，向前一格，到2 * 当前位置的位置（~~农夫是人吗？~~）

好了既然~~四要素~~都清楚了，先了解一下广搜的思想吧

**思想**：先把起点放到队列里，在一直循环直到队列元素为空（所有点都遍历完才会这样），取出当前队列中的元素（就是当前位置），从当前位置遍历所有从当前位置可以到的位置，把这个位置放到队列中…………如果有一次取出队列元素（及当前位置）等于终点，就直接输出从起点到这个点的步数（建一个dis数组存从起点到这个点的步数），然后就直接退出。

我们看一下深搜和广搜的**区别**吧

**区别**：广搜主要适合求从起点到终点的最佳方案，而深搜则适合求起点到终点的方案总数。（~~自己理解的~~）

既然概念都理解了（~~不理解也得理解~~），看**队列**吧，不会队列**概念**的看[这里](https://blog.csdn.net/zhongguozhichuang/article/details/53196415)，

**操作**举一个简单的例子：

```cpp
#include <bits/stdc++.h>
#include <queue>//队列头文件 
using namespace std;
queue < int > pru;//定义一个队列 
int main()
{
	pru.push(1111);//吧1111这个数放进队列中
	printf("%d\n", pru.front());//输出队列头的元素
	pru.pop();//把队列头的元素弹出
	printf("%d\n", pru.size());//输出队列里元素的个数
	if(pru.empty())//队列空就输出YES 
	{
		printf("YES\n");
	}
	return 0;
}
```

**注意事项**：如果你的评测记录[RE，像这样](https://www.luogu.org/recordnew/show/19502021)或[TLE，像这样](https://www.luogu.org/recordnew/show/19501745)，就代表你没有**规定界限**

好了，看代码吧

```cpp
//可以忽略register和inline，是用于优化的 
#include <bits/stdc++.h>
#define n 1000001//界限 
using namespace std;
int m, x, y, dis[1000001];
inline int bfs(int s, int e)//起点，终点 
{
	memset(dis, -1, sizeof(dis));//清成-1 
	queue < int > pru;//队列 
    pru.push(s);
    dis[s] = 0;//起点到起点的距离为零 
    while(!pru.empty())//非空 
    {
    	int x = pru.front();//队头元素 
    	pru.pop();
        if(x == e)//抓到牛了 
        {
            return dis[x];//输出步数 
        }
        if(x - 1 >= 0 && dis[x - 1] == -1)//界限 + 没有访问过 + 农夫向后走 
    	{
    		pru.push(x - 1);//x - 1走过了 
    		dis[x - 1] = dis[x] + 1;//到起点的距离 
		}
		if(x + 1 <= n && dis[x + 1] == -1)//农夫向前走
		{
			pru.push(x + 1);
			dis[x + 1] = dis[x] + 1;
		}
    	if(x * 2 <= n && dis[x * 2] == -1)//农夫瞬移到2 * x 
    	{
    		pru.push(x * 2);
    		dis[x * 2] = dis[x] + 1;
		}
    }
    return 0;//个人习惯，也不可以写 
}
int main()
{
    scanf("%d", &m);
    while(m--)
    {
        scanf("%d %d", &x, &y);
		printf("%d\n", bfs(x, y));//换行~ 
    }
    return 0;
}
```


---

## 作者：Ksilver (赞：10)

```
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#define N 200005
using namespace std;
int d[3]={2,1,-1};
bool vis[N];
int a,b;
struct node//结构体定义队列
{
	int x;
	int step;
}q[N];
void bfs(int s,int e)
{
	int head=1,tail=1;
	memset(vis,0,sizeof(vis));//vis数组清零
	vis[s]=1;
	q[tail].x=s;
	q[tail].step=0;
	tail++;//标记，入队
	while(head<tail)
	{
		int x=q[head].x;
		int step=q[head].step;
		if(x==e)//到达牛处，输出步数
		{
			printf("%d\n",step);
			break;
		}
		for(int i=0;i<3;i++)
		{
			int nx=0;
			if(i!=0) nx=x+d[i];
			else nx=x*d[i];
			if(nx>=0 && nx<=N && vis[nx]==0)
			{
				vis[nx]=1;
				q[tail].x=nx;
				q[tail].step=step+1;
				tail++;//若满足条件，标记，入队
			}
		}
		head++;
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d%d",&a,&b);
		if(a>b) 
			printf("%d\n",a-b);//若人在牛前面，直接输出距离差	
		else bfs(a,b);
	}
	return 0;
}
```

---

## 作者：Fraction (赞：7)

看了好几篇题解，发现有深搜广搜，有$dp$贪心。但是居然没有最短路！

~~不行，我绝对不能允许这种情况出现~~

因为我以前做这种类似的题目的时候，无论写什么搜索都过不了，所以就再也没写过搜索。

首先这题用最短路做的话，连边很简单，$(i,i+1),(i,i-1),(i,i\times2)$全部连上边，跑一遍最短路，最后特判一下$n\geq k$的情况就$ok$了。

由于我太弱了，所以写了个会被卡（但是还没卡）的$spfa$

代码如下：

```cpp
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int t, n, k;
int cnt;
int dis[2000010], vis[2000010];
int head[10000005];
queue<int> que;

struct Edge {
	int to;
	int nxt;
} edge[10000005];

void addedge(int from, int to) {
	edge[++cnt].to = to;
	edge[cnt].nxt = head[from];
	head[from] = cnt;
	return ;
}

void spfa() {
	for(register int i = 1; i <= 2*max(n, k); i++) dis[i] = 2147483647, vis[i] = 0;
	que.push(n), vis[n] = 1, dis[n] = 0;
	while(!que.empty()) {
		int u = que.front();
		que.pop(), vis[u] = 0;
		for(register int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				if(vis[v] == 0) {
					vis[v] = 1;
					que.push(v);
				}
			}
		}
	}
	return ;
}

void init() {
    scanf("%d", &t);
    while(t--) {
	    scanf("%d%d", &n, &k);
    	for(register int i = 0; i <= 2*k; i++) addedge(i, i+1);
	    for(register int i = 1; i <= 2*k; i++) addedge(i, i-1);
    	for(register int i = 1; i <= 2*k; i++) addedge(i, i*2);
    	if(n >= k) {
	    	printf("%d\n", n-k);
		    continue;
    	}
        spfa();
        printf("%d\n", dis[k]);
    }
	return ;
}

void solve() {
	return ;
}

int main() {
	init();
	solve();
	return 0;
}
```

---

## 作者：乒乓高手 (赞：7)

**禁止抄袭 题解只是帮助你的工具 请自觉**


一道BFS（广搜）的好题，就是这道题，让我明白了广搜。


看到底下的大佬都用的是STL，很少用手写队列的，那我就来一发手写队列吧（我不会告诉你我不会用STL的）。


首先，这个题需要用结构体，来存每一个点的位置和步数，然后我突发奇想的用了一个SWATCH。这样代码长度就很短了。


不断的入队列，维护这个队列，当发现时目标位置的时候就输出然后处理下一组数据。


----------------------------------------------------------------------分割线------------------------------------------------------------------------


```cpp
#include<bits/stdc++.h>   //省事，万能头文件
#define maxn 100010      //只是为了好debug
using namespace std;
int t,y,x,r,s;                       //全局变量，注意X,Y一定是全局变量，因为函数要用
bool v[maxn];                   //标志数组
struct node                      //定义结构体
{
    int pos,step;            //POS是当前的位置，STEP是到这个位置所用的步数
}q[maxn];                         //队列
void bfs()
{
    int head=0,tail=1;         //定义队首和队尾
    q[1].pos=x;                   //起点入队列
    q[1].step=0;                 //步数是0
    v[x]=1;                          //标志数组，起点已经到达
    while(head<tail)          //操作队列
      {
          head++;
        s=q[head].pos;
          r=q[head].step;          //出队列
          for(int i=1;i<=3;i++)
            {
                switch(i)             //考虑三种情况
                    {
                        case 1:
                            if((s*2<=100000)&&(s*2)>0&&(v[s*2]==0))          //两倍的情况，注意一定要判断是否越界，不然会RE
                            {
                         q[++tail].pos=s*2;          //入队操作
                             q[tail].step=r+1;             //步数加1
                             v[s*2]=1;                       //标志数组附1
                             if(q[tail].pos==y)          //如果是目标位置，就输出
                               {
                                   cout<<q[tail].step<<endl;
                                     return;
                               }
                            }
                            break;          //千万不要忘记BREAK
                        case 2:
                            if((s+1<=100000)&&(s+1>0)&&(v[s+1]==0))          //向前找一步的情况
                            {
                             q[++tail].pos=s+1;
                             q[tail].step=r+1;
                             v[s+1]=1;
                             if(q[tail].pos==y)
                               {
                                    cout<<q[tail].step<<endl;
                                    return;
                               }
                            }
                            break;
                        case 3:
                            if((s-1<=100000)&&(s-1>0)&&(v[s-1]==0))          //向后走一步的那种情况
                            {
                             q[++tail].pos=s-1;
                             q[tail].step=r+1;
                             v[s-1]=1;
                             if(q[tail].pos==y)
                               {
                                   cout<<q[tail].step<<endl;
                                   return;
                               }
                            }
                            break;
                    }
            }
      }
}
int main()
{
    cin>>t;                              //输入数据组数
    for(int i=1;i<=t;i++)           //输入数据
      {
          memset(q,0,sizeof(q));
          memset(v,0,sizeof(v));          //因为是多组数据，一定每次要清零
          s=0;r=0;
        cin>>x>>y;
          bfs();                                    //开始搜索
      }
    return 0;
}
```

---

## 作者：Stay_Hungry (赞：6)

看到许多$dalao$都用bfs，那本蒟蒻来篇dfs的题解。

首先，题中说FJ可以向前或向后一步或者FJ坐标*2，因为牛与FJ的坐标变化是相对我们可以反着搜来减小程序运算负担。   
5 -> 4 -> 8 -> 16 -> 17 可以转换为 17 -> 16 -> 8 -> 4 -> 5
```cpp
void dfs( int x , int y , int step ){
	if( ans <= step ) return ;//可行性剪枝（如果比之前所搜的结果大了就不用继续搜了）
	ans = std :: min( ans , step + abs( y - x ) );//二段维护剪枝（对于x , y当前坐标的位置，答案最大为当前步数加上距离）
	if( x == y ){//如果搜到答案就记录一次答案
		ans = std :: min( ans , step );
		return ;
	}
	if( x > y ) dfs( x , y + 1 , step + 1 );//如果FJ在牛前面了，就只能往后退了（即牛往前移动一步）
	else {
		if( y & 1 ) {//y&1相当与 y % 2 != 0
			dfs( x , y + 1 , step + 1);//向前后移动一步搜索
			dfs( x , y - 1 , step + 1 );
		}
		else dfs( x , y >> 1 , step + 1 );//如果能被2整除，就直接搜索能移动步数多的2倍坐标移动
	}
	return ;//return;好习惯
}
```
对于主函数，就不多讲了，直接上代码：
```cpp
int main( void ){
	int x , y ;
	//freopen( "Text.out" , "w" , stdout );
	std :: cin >> n ;
	while( n -- ){
		std :: cin >> x >> y ;
		if( y < x ){
			std :: cout << x - y << std :: endl;
			continue;
		}//如果牛在FJ后面，步数就是距离
		ans = y - x ;//初始化（最大步数即为距离）
		dfs( x , y , 0 ) ;
		std :: cout << ans << std :: endl ;
	}
	return 0 ; //return 0 ;好习惯
}
```
至于效率，是很有保障的，试了一下24ms（原本最快代码25ms）    
~~感觉还行~~

---

## 作者：Diaоsi (赞：5)

## 题目链接：[传送门](https://www.luogu.com.cn/problem/P1588)
## 思路：
这题可以用BFS来做，我们首先得构造隐式图

根据题意，JF每次可以前进一步、后退一步或者直接走到2*x的位置，每次花费的时间都一样

在广搜的时候我们只要把当前节点的前一个位置、后一个位置和第2*x的位置入队就好了

然后统计距离，不难理解，到达这些节点的步数是当前节点的步数+1

如果队首元素为终点位置，则结束搜索，输出到当前位置的步数
## 关于手写队列：
~~众所周知stl的常数都很大~~

我们可以用一个数组来实现队列，用两个变量l和r分别表示队首和队尾，队首变量++就相当于pop，队尾边量++就相当于push，这样可以有效防止爆队列，而且重设一下队首和队尾变量就相当于清空了整个队列。
### 优点：
常数小
### 缺点：
空间消耗较大，但是可以改成循环队列

$Code:$
```cpp
int q[N],l,r;//手写队列
```
## 代 码 放 送：

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000000;
int n,k,T,ans;
int vis[N],d[N],dx[3];
int q[N],l,r;//手写队列
void bfs(){
	while(l<=r){
		int x=q[l];
		if(x==k){printf("%d\n",d[l]);return;}
		dx[0]=x+1,dx[1]=x-1,dx[2]=x<<1;
		for(int i=0;i<3;i++)
		    if(dx[i]>=0&&dx[i]<N&&!vis[dx[i]])
			    q[++r]=dx[i],d[r]=d[l]+1,vis[dx[i]]=1;
		l++;
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		memset(d,0,sizeof(d));
		memset(vis,0,sizeof(vis));
		l=r=1;
		scanf("%d%d",&n,&k);
		q[l]=n;
		vis[n]=1;
		bfs();
	}
    return 0;
}
```


---

## 作者：Mickey_jj (赞：3)

一道BFS......（~~我不会告诉你，我一开始看到这题就想到[这题](http://ybt.ssoier.cn:8088/problem_show.php?pid=1253),抄下来然后WA了~~）

不会的bfs同学点[这里](https://www.jianshu.com/p/e58665864d54)

这题和其他题不一样，FJ的移动方式有三种：+1 ， -1  和  +自身（也就是x2），为方便大家理解，我写了一个函数px；

还有一点提醒大家，这题是**多组数据**，一定要：

## 清零！清零！清零！

否则就是[这个样子](https://cdn.luogu.com.cn/upload/pic/63078.png)QAQ

话不多说，上代码：


------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int vis[100003]; 	
int n,m,t;
int px(int i,int x){
	if(i==0)return x;//函数的返回值是用来加的，所以return x而不是2x
	if(i==1)return 1;
	else return -1;
}
struct poly{
	int x,step;//x是坐标，step是FJ到该点的最小步数
};
void bfs(int n,int m){
	memset(vis,0,sizeof(vis));
        //也可以将数组定义在函数里
        //当数据较多时，推荐定义在函数里
        //memset可能炸时间
	queue<poly> p;//stl
	poly cur={n,0};
	vis[n]=true;
	p.push(cur);
	while(!p.empty()){
		cur=p.front();
		p.pop();//弹出队首
		if(cur.x==m){//如果到达终点
			cout<<cur.step<<endl;
			return;
		}
		for(int i=0;i<=3;i++){//将原队首可去的3个地方入队
			int nx=cur.x+px(i,cur.x);
			if(nx>=1&&nx<=100000)
			if(vis[nx]==false){
				vis[nx]=true;
				poly ne={nx,cur.step+1};
				p.push(ne);
			}
		}
	}
}
int main(){
	cin>>t;
	while(t--){//多组数据
		cin>>n>>m;
		bfs(n,m);
	}
	return 0;//好习惯
}
```

---------

 本蒟蒻一向

### 心地善良
### 这篇题解复制提交可以直接**AC**.

但是......

# 非紧急情况请勿使用此特殊功能！

---

## 作者：DLSINNOCENCE (赞：2)

**真是惭愧，本蒟蒻这题RE了好多次**
# 好多次脑子抽了题目没看清楚，还出现过很多奇怪的错误。
## vis数组也忘了初始化
下面是题解;
```
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000000
int vis[maxn];
struct node{
	int x,t;
};
int bfs(int x,int y){
	queue<node> q;
	q.push((node){x,0});
	while(!q.empty()){
		node n;
		n=q.front();
		q.pop();
		for(int i=1;i<=3;i++){
			node v;
			v.t=n.t+1;
			if(i==1) v.x=n.x-1;
			if(i==2) v.x=n.x+1;
			if(i==3) v.x=n.x*2;
			if(v.x<1||v.x>maxn) continue;
			if(vis[v.x]) continue;
			if(v.x==y) return v.t;
			vis[v.x]=1;
			q.push(v);
		}
	}
}
int main(){
	int n;
	int a,b;
	cin>>n;
	while(n--){
	memset(vis,0,sizeof(vis));
	cin>>a>>b;
	if(a==0) cout<<0;
	cout<<bfs(a,b)<<endl;}
}
```


---

## 作者：维迭生 (赞：2)

嗯，这是一道很 ~~简单~~ 标准的搜索题（就比如什么迷宫之类的），所以适合用来练广搜或深搜的熟练度。我更倾向于用广搜来写（因为深搜更好写嘛，而且比如单词接龙这些题目只能用深搜写，到时候再练）。  
广搜的思想，就是只处理“在手边上的事”；而深搜是“一条道走到黑”；具体来说，对一个状态（比如在迷宫中的位置），我们需要做四件事：（1）检验是否处理完了整个事件（比如走到了出口），以及（2and3）扩展（就是接下来能往那些方向走），并（4）标记本状态为“已访问”，防止掉头回到这个状态。广搜是扩展完再进入下一层，深搜是对一个状态扩展出的状态再扩展，尽可能"深"地搜索一张图。  
那么，广搜如何实现呢？  
我建议使用**STL**里的队列$(queue)$容器。  
想象你每一个扩展到的结点去排队，等待处理；排到的结点做那三件事，扩展出的新结点再去排队，直到找到目标为止。
在你的头文件里加上#include<queue>并在“using namespace std;”后加上“queue<int>q;”来使用queue；  
queue的常用操作：    
  
1.  q.push()  :让结点去排队
2.  q.front() :排最前面的结点。
3.  q.pop()   :处理完毕，最前面的结点离开。
4.  q.empty() :队列里是否还有结点（有则为true）。  
 经常你能看到诸如pair<int,int>以及q.push(make_pair(x,y))之类的东西，那是因为系统自带的queue只能处理一个东西，如果你想把两个东西放进去就只有让它们成为“一对”，这就用到了pair。  
 对于本题，标记为已访问可以用步数steps数组来代替，因为先走到的点距离源节点的步数一定更少。   
 详见代码：
 ```
#include<iostream>
#include<cstring>
#include<queue>		//***
#define pii pair<int,int>
using namespace std;
const int MAXN=100005;
queue<int> q;		//***
//bool vis[MAXN]；防止重复访问，本题是一个变形，以steps替代省空间
int steps[MAXN];
int ans[11];
int bfs(int s,int f);
int main(){
	int c;
	cin>>c;
	for(int j=1;j<=c;j++){
		for(int i=1;i<=MAXN;i++){
			steps[i]=MAXN; 
			//vis[i]=false;
		}				//先假设所有点都没有访问过，且到达不了
		int s,f;
		cin>>s>>f;
		ans[j]=bfs(s,f);		//存答案
		while(!q.empty())q.pop();	//其实也可以用q.erase();
	}
	for(int i=1;i<=c;i++)
		cout<<ans[i]<<endl;
	return 0;
}
int bfs(int s,int f){
	steps[s]=0;		//初始点，步数为0
	q.push(s);		//源结点入队
	while(!q.empty()){
		int x=q.front();
		q.pop();
		if(x==f)return steps[x];	//操作一，如果到了，就返回
//		if(x+1==f)return steps[x]+1;	三行废话不要。
//		if(x-1==f)return steps[x]+1;
//		if(2*x==f)return steps[x]+1;
		for(int i=1;i<=3;i++){
			int y;
			switch(i){
				case(1):y=x+1;break;
				case(2):y=x*2;break;
				case(3):y=x-1;break;
			}						//操作二，按要求扩展
			if(y>MAXN)continue;		
			if(steps[y]>steps[x]+1&&y<=2*f&&y>=0){
				steps[y]=steps[x]+1;	//变形的操作四，标记。
				q.push(y);			//传说中的操作三，入队。
			}
		}
	}
	return steps[f];		//其实因为一定存在一个解，使得fj能抓住牛（大不了一步一步走就是了），所以这一行可以不要，但防止编译器给出警告，并且便于察代码（如果返回是MAXN就说明你bfs写错了），最好加上。
}
```

---

## 作者：lqx_bnu (赞：2)

## ~~跟着楼下来一波……~~##
  
  
典型的一道裸的bfs水题，然鹅要注意的细节还是很多的（后面会说）……  
  
就是从n走到k的最短路径 
  
上代码
```cpp
#include<iostream>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
int n,k,book[10000005],t;
int main()
{
	scanf("%d",&t);
	for(int l=1;l<=t;l++)
	{
		scanf("%d%d",&n,&k);
		queue<int>q;
		memset(book,-1,sizeof(book));
		q.push(n);
		book[n]=0;
		if(n==k)//第一个剪枝 出发就在目标点
		{
			putchar('0'),putchar('\n');
			continue;
		}
		if(n>k)//第二个剪枝 出发点在目标前面 倒着走
		{
			printf("%d\n",n-k);
			continue;
		}
		while(!q.empty())//开始bfs
		{
			int x=q.front();
			q.pop();
			if(book[x+1]==-1)//前
			{
				q.push(x+1);
				book[x+1]=book[x]+1;
				if(x+1==k)
				{
					printf("%d\n",book[k]);
					break;
				}
			}
			if(x-1>0&&book[x-1]==-1)//后
			{
				q.push(x-1);
				book[x-1]=book[x]+1;
				if(x-1==k)
				{
					printf("%d\n",book[k]);
					break;
				}
			}
			if(2*x<100005&&book[2*x]==-1)//传送
			{
				q.push(2*x);
				book[2*x]=book[x]+1;
				if(2*x==k)
				{
					printf("%d\n",book[k]);
					break;
				}
			}
		}
		if(!q.empty())continue;
	}
	return 0;
}
```
  
注意的要点：  
（1）向后的时候要注意越界！！！   
（2）要经常检查结果不然传送会爆  
## ~~来自一个RE十多次的蒟蒻的忠告~~##
求过……

---

## 作者：Obito (赞：2)

cpp
思路：因为题目是找最优解，所以可以用广搜，一道纯BFS，深搜可能会超（反正我没试，有兴趣的朋友可以试一下）。
代码如下

```
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=200000+5;
int a[maxn],dx[maxn],dy[maxn],s[maxn],biao[maxn];
//定义数组，数据范围是10的5次方，但还是把数组定大一点
int main()
{
	int i,j,k,m,n,jjf,x;
	cin>>jjf;//输入
	for(i=1;i<=jjf;i++){//因为是多组数据，所以要用循环 
	memset(biao,0,sizeof(biao));
	memset(dx,0,sizeof(dx));
	memset(s,0,sizeof(s));//清0，不然过不了
	cin>>n>>m; 
	biao[n]=1;//起始点标记置一
		int hd=0,tl=1;//头指针，尾指针
		dx[1]=n;s[1]=0;//初始化
		if(n>=m){//如果起始点比终点大，就只能往后走。
			printf("%d\n",n-m);//直接输出答案n-m
			continue;
		}
		while(hd<tl){//开始BFS
			hd++;//头指针++；
			x=dx[hd]-1;//第一种向后走的情况-1；
				if(!biao[x]&&x>=0){//判断会不会走到0的左边
					tl++;//尾指针++
					dx[tl]=x;//dx数组等于现在的值，dx为存储现在所在的点
					s[tl]=s[hd]+1;//S为存储步数的数组
					biao[x]=1;//标记走过
					if(x==m){//如果走到了答案点，输出答案
					cout<<s[tl]<<endl;
					continue;
					}
				}
			x=dx[hd]+1;//向前走的情况；
			if(!biao[x]&&x<maxn){//判断会不会超界
					tl++;
					dx[tl]=x; 
					s[tl]=s[hd]+1;
					biao[x]=1;
					if(x==m){
					cout<<s[tl]<<endl;
					continue;	
					}
				}
			if((dx[hd]*2<=100000)&&(dx[hd]*2)>0&&(biao[dx[hd]*2]==0))//这一句很重要，几次运行错误都是少了这句话，判断越界
			x=dx[hd]*2;
			if(!biao[x]&&x<maxn){
					tl++;
					dx[tl]=x; 
					s[tl]=s[hd]+1;
					biao[x]=1;
					if(x==m){
					cout<<s[tl]<<endl;
					continue;
					}
				}
				
		}
		}
		return 0;//结束程序
}
```
蒟蒻第一次打题解，打字不累，希望采纳。祝洛谷越来越好。祝各位大神和蒟蒻事事顺心。


---

## 作者：zhoujiale (赞：1)

我的同学竟然在一篇题解里函数名用了我的名字，所以我在这篇题解里也要把他的名字作为函数名【手动滑稽】

这个人就是他，[我同学](https://www.luogu.com.cn/user/219935)

# 不说了，进入正题

这种题适合使用bfs,什么是bfs呢？

bfs,就是我们说的广度优先搜索，它与dfs是搜索中经常用到的。

# dfs:
dfs就是深度优先搜索，它会把每一种可能都尝试一遍，通常我们使用它来求解连通块以及最短路之类的问题。
# bfs:
bfs就是广度优先搜索，dfs相当于一条道走到黑，不撞南墙不回头。bfs则是把n步可以走到多少个点来求出来。求最短路问题时会经常用到它，因为它第一次走到这个点就是到这个点的最短路。

# 好了，开始进入这道题吧
```cpp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 + 5;//这是一个好习惯
struct node
{
	int x,ans;
}st;//st代表起点。
int t,n,m,a[N],tmpx;
queue<node> q;//建立一个队列来维护bfs
void wyz(int cow)
{
	while(!q.empty())//因为有多组数据，所以要记得清空队列
		q.pop();
	q.push(st);//st压入队列
	while(!q.empty())
	{
		if(a[cow] != -1)
		{
			printf("%d\n",a[cow]);//访问到时直接输出
			break;
		}
		node t = q.front();
		q.pop();
		for(int i = 1;i <= 3;i++)//这里我的方法比较傻，大家还可以再想想。
		{
			
			if(i == 1)
			{
				tmpx = t.x + 1;//向前走一步
				if(tmpx > N)//这里要注意，不加这个会re,而在本地是能通过的，因为本地给你自动分配了内存
					continue;
				if(a[tmpx] != -1)
					continue;
				a[tmpx] = t.ans + 1;
				q.push((node)
				{
					tmpx,t.ans + 1
				});
			}
			else if(i == 2)
			{
				tmpx = t.x - 1;//向后退一步
				if(tmpx <= 0)
					continue;
				if(a[tmpx] != -1)
					continue;
				a[tmpx] = t.ans + 1;
				q.push((node)
				{
					tmpx,t.ans + 1
				});
			}
			else
			{
				tmpx = t.x*2;//走到当前位置*2的地方
				if(tmpx > N)
					continue;
				if(a[tmpx] != -1)
					continue;
				a[tmpx] = t.ans + 1;
				q.push((node)
				{
					tmpx,t.ans + 1
				});
			}
		}
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		st.x = n;
		st.ans = 0;
		memset(a,-1,sizeof(a));//注意数组初始化
		a[n] = 0;
		wyz(m);
	}
	return 0;
}
```
温馨提示：使用bfs时要记得判断问题边界哦

最后，不要抄袭。

---

## 作者：Untitled (赞：1)

蠢新第一次给P打题解QAQ

[原题](https://www.luogu.org/problemnew/show/P1588)

首先，我们想到，这个是求最少要多少步的，第一反应广搜

然后就有了第一版

```
#include<bits/stdc++.h>
using namespace std;
queue <int> qx,qg;
int ans=0,stx,edx;
bool flag[900086],d=true;
void bp(int x)
{
    qx.push(x);
    qg.push(0);
    while(!qx.empty())
    {
        int px=qx.front();
        int pg=qg.front();
        qx.pop();
        qg.pop();
        ans=pg;
        if(px==edx)
        {
            d=false;
            return;
        }
        if(flag[px+1])
        {
        	flag[px+1]=false;
        	qx.push(px+1);
        	qg.push(pg+1);
        }
        if(flag[px-1])
        {
        	flag[px-1]=false;
        	qx.push(px-1);
        	qg.push(pg+1);
        }
        if(flag[px*2])
        {
        	flag[px*2]=false;
        	qx.push(px*2);
        	qg.push(pg+1);
        }
    }
}
int main()
{
    
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
		memset(flag,true,sizeof flag);
    	d=true;
    	ans=0;
    	cin>>stx>>edx;
	    bp(stx);
    	if(!d)
    	    printf("%d\n",ans);
    	else
    	    printf("KKKSCO3: LUOGU HAS NO BUG!!!\n");
    	while(!qx.empty()) qx.pop();
    	while(!qg.empty()) qg.pop();
    }
    
}
```

然后，，全紫了，，，

这时，我们想一想，是不是队列炸了（wu

X的倍增。。。可怕

所以我们要控制一个上界

但是！FJ是可以走回头路的

所以不能生硬地设为Y

（思考30min）

所以，当你坐标比奶牛大，在各种鬼畜步往前$*2*2*2$有什么用呢？绕地球回来吗？（好像真行（wu

所以，一旦它坐标$>y$，就只能走回去的路！不在判断$+1\ and\ *2$！！！

代码奉上

```
#include<bits/stdc++.h>
using namespace std;
queue <int> qx,qg;
int ans=0,stx,edx;
bool flag[900086],d=true;
void bp(int x)
{
    qx.push(x);
    qg.push(0);
    while(!qx.empty())
    {
        int px=qx.front();
        int pg=qg.front();
        qx.pop();
        qg.pop();
        ans=pg;
        if(px==edx)
        {
            d=false;
            return;
        }
        if(flag[px+1]&&px<edx)//只有小于才行
        {
        	flag[px+1]=false;
        	qx.push(px+1);
        	qg.push(pg+1);
        }
        if(flag[px-1])
        {
        	flag[px-1]=false;
        	qx.push(px-1);
        	qg.push(pg+1);
        }
        if(flag[px*2]&&px<edx)//只有小于才行
        {
        	flag[px*2]=false;
        	qx.push(px*2);
        	qg.push(pg+1);
        }
    }
}
int main()
{
    
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
		memset(flag,true,sizeof flag);
    	d=true;
    	ans=0;
    	cin>>stx>>edx;
	    bp(stx);
    	if(!d)
    	    printf("%d\n",ans);
    	else
    	    printf("KKKSCO3: LUOGU HAS NO BUG!!!\n");//吃饱的时候
    	while(!qx.empty()) qx.pop();//清空！！！不能忘
    	while(!qg.empty()) qg.pop();
    }
    
}
```


---

## 作者：2x6_81 (赞：1)

这道题用一个BFS就搞定：
![](https://i.loli.net/2018/12/12/5c10dfbc2bc12.png)

（红色表示当前位置，橙色表示可到达的位置），样例：
```
1 
5 17
```
步骤是：
```
1:  4( 5-1)
2:  8( 4*2)
3: 16( 8*2)
4: 17(16+1)
```

接下来，就是确定上限：

我们想到，如果离目标位置相差的太远，则步数会变多。

如果是目标位置，不一定可以，比如：
```
1
50000 99999
```
如果像上限是目标位置，则步数是$49999$

实际上$2$步就行

如果是目标位置*2，就会很更远，可以

当然啦，实际上目标位置乘上×1.5就行，不过×2可以用位运算。

最后注意，如果目标的x在起点前面，那么答案必须是y-x，因为$x\times2>x\text{ ,}+1>x$，唯独$x-1<x$（想一想，是不是）

如果两点重合，直接输出$0$，即`puts("0");`

贴代码：
```
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
struct per
{
	int x,step;
    per(int xx,int st)
    {x=xx;step=st;}
};
queue<per> q;//队列
bool vis[2000005];
int from,to;
bool in(int x)
{
    return x<0 || x>(to<<1) || vis[x];
}//判断是否越界
int bfs()
{
    memset(vis,0,sizeof(vis));
    while(!q.empty())q.pop();
    //记得清空数组与队列
    if(from>=to)return from-to;
    //特判,因为from==to时是0,也是from-to,就把两个放一起了
    q.push(per(from,0));vis[from]=1;
    while(!q.empty())
    {
        int xx=q.front().x,st=q.front().step;//获取头元素
        if(xx==to)return st;
        if(in(xx+1)==false) q.push(per(xx+1,st+1)),vis[xx+1]=1;
        if(in(xx-1)==false) q.push(per(xx-1,st+1)),vis[xx-1]=1;
        if(in(xx*2)==false) q.push(per(xx*2,st+1)),vis[xx*2]=1;//枚举每个点
        q.pop();
    }
    return -999;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)//多组答案
    scanf("%d%d",&from,&to),printf("%d\n",bfs());
}
```

---

## 作者：bjrjk (赞：1)

这题的题意说的太不清楚，那个$$2*x$$里的$$x$$指的是当前节点……其实是$$2*i$$……

```cpp
#include<iostream>
#include<cstring>
#include<queue>//stl队列
using namespace std;
bool visited[100005];
int bfs(int cur, int dest){//bfs
    if (dest < cur)return cur - dest;//目的地比当前位置还小直接后退就好
    memset(visited, false, sizeof(visited));
    queue<pair<int,int>> q;//用到了stl里的pair，不懂的自己查一下
    q.push(pair<int,int>(cur,0));
    while (!q.empty()){
        pair<int,int> c = q.front(); q.pop();
        if (c.first<0 || c.first>100000)continue;//防止RE
        if (visited[c.first])continue;
        else visited[c.first] = true;
        if (c.first == dest)return c.second;
        q.push(pair<int, int>(c.first + 1, c.second + 1));//分别是左右，2*i
        q.push(pair<int, int>(c.first - 1, c.second + 1));
        q.push(pair<int, int>(2*c.first, c.second + 1));
    }
    return -1;
}
int main(){
    ios::sync_with_stdio(false);//cin,cout优化
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++){//数据读入
        int cur, dest;
        cin >> cur >> dest;
        cout << bfs(cur, dest) << endl;
    }
}
```

---

## 作者：tututu (赞：1)

裸的广搜

b是广搜的队列不解释

f[i]表示走到i的最小步数

向三个方向拓展

前提是不能<0,不能已经到过，不能超过y\*3（明显吧）；

```cpp
label 10;
var
  t,x,y,h,m:longint;
  b,f:array[-1..1000002] of longint;
begin
  readln(m);
  while m>0 do
    begin
      read(x,y);
      fillchar(f,sizeof(f),255);
      fillchar(b,sizeof(b),0);
      h:=0;
      f[x]:=0;
      b[1]:=x;
      t:=1;
      while h<t do
        begin
          inc(h);
          if b[h]>1 then if f[b[h]-1]=-1 then begin inc(t); f[b[h]-1]:=f[b[h]]+1; b[t]:=b[h]-1; end;
          if b[t]=y then begin writeln(f[b[t]]); goto 10; end;
          if b[h]<3*y then if f[b[h]+1]=-1 then begin inc(t); f[b[h]+1]:=f[b[h]]+1; b[t]:=b[h]+1; end;
          if b[t]=y then begin writeln(f[b[t]]); goto 10; end;
          if b[h]<y then
            if f[b[h]*2]=-1 then begin inc(t); f[b[h]*2]:=f[b[h]]+1; b[t]:=b[h]*2; end;
          if b[t]=y then begin writeln(f[b[t]]); goto 10; end;
        end;
```
10:
      dec(m);

  end;
end.

---

## 作者：without_wings (赞：1)

******典型的广搜，相比起二维的迷宫来说差不了多少，只要直接BFS就好了。（原来学JAVA的我一向不喜欢STL）******

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
struct sss{
    int x;
    int s;
}e[100001];
int m,n;
int h=0,t=1,k[100001];//k是用来标记这个点有没有走过的，h为头指针，t为尾指针。
int bfs(int sx,int ss){
    e[0].x=sx;
    e[0].s=0;
    k[sx]=1;//起点。
    while(h<t){
        sss p=e[h++];
        int x=p.x,s=p.s;//出队。
        if(p.x==ss)return s;//检测是否到了牛。
        if(x-1>=0&&k[x-1]==0){
            e[t++]=(sss){x-1,s+1};
            k[x-1]=1;//标记这个点已经被走过。
        }//向前走。
        if(x+1<=100000&&k[x+1]==0){
            e[t++]=(sss){x+1,s+1};
            k[x+1]=1;
        }//向后走。
        if(x*2<=100000&&k[x*2]==0){
            e[t++]=(sss){x*2,s+1};
            k[x*2]=1;
        }//乘二。
    }   
}
int main(){
    int ggg;
    cin>>ggg;
    for(int i=1;i<=ggg;i++){
        cin>>m>>n;
        cout<<bfs(m,n)<<endl;//输出。
        h=0;
        t=1;//指针归零。
        for(int i=1;i<=100000;i++){
            e[i].s=0;
            e[i].x=0;
            k[i]=0;
        }//数组初始化。
    }
    return 0;
}
```



---

## 作者：unbeatable_noob (赞：1)

有人说卡STL反正我没被卡。。

有人说要剪枝反正我没剪也过了。。

比较坑的一个地方是要判断范围不然RE

上代码

color数组用来染色（记录标记），cnt（count）数组用来记录每个节点最短数

```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int bfs(int x,int y)
{
    queue<int> arr;
    int color[10000000],cnt[1000000];
    memset(color,0,sizeof(color));
    memset(cnt,0,sizeof(cnt));
    arr.push(x);
    color[x] = 1;
    while(!arr.empty()) //while判断非空即可
    {
        int tep = arr.front();
        arr.pop();
        if(tep == y)
            return cnt[tep];//输出写在这里少写很多行呢233
        else
        {
            if(tep>=0 && tep<=100000 && color[tep-1] != 1)//这里我说特别坑我翻了题解才解决蜜汁RE
            {
                arr.push(tep-1);
                color[tep-1] = 1;
                cnt[tep-1] = cnt[tep]+1;
            }
            if(tep>=0 && tep<=100000 && color[tep+1] != 1)//同上
            {
                arr.push(tep+1);
                color[tep+1] = 1;
                cnt[tep+1] = cnt[tep]+1;
            }
            if(tep>=0 && tep<=100000 && color[tep*2] != 1)//同上++
            {
                arr.push(tep*2);
                color[tep*2] = 1;
                cnt[tep*2] = cnt[tep]+1;
            }
        }
    }
       return -1;//无解返回-1
}
int main()
{
    int a,x,y;
    cin >> a;
    for (int i = 1;i <= a;i++)
    {
        cin >> x >> y;
        cout << bfs(x,y) << endl;;
    }
 } 
```
秉承能简化就简化能少打几个字就少打几个字的原则的代码，希望有更加简化的写法欢迎交流


---

## 作者：critnos (赞：0)

我又来优化了（滑稽

先讲BFS的基本原理（会的可以跳过）：

现有一个队列，一开始只有一个元素：初始状态。

然后每次对队首的元素进行判断。

1. 如果符合条件：

搜索结束。

2. 如果不符合条件：

将这个状态可能延伸的多种状态添加到队尾，并让队首出队。

是不是还是感觉很玄乎？来道真题试试：

现在有一个变量的初始值为0，你每次可以选择把它加1或加2。那么最少几次才能把它变成5

如果用BFS做是这样的：

```cpp
0

1 2

2 2 3

2 3 3 4

3 3 4 3 4

3 4 3 4 4 5//虽然搜索已经完毕，但是还要等到5出队时才知道

4 3 4 4 5 4 5

3 4 4 5 4 5 5 6

4 4 5 4 5 5 6 4 5

4 5 4 5 5 6 4 5 5 6

5 4 5 5 6 4 5 5 6 5 6

搜索完毕。
```


那么怎么才能记录次数呢？定义一个结构体，其中有步数和状态。当然，每次添加元素时也要把步数加1；

进入正题（优化）：

1. 不一定要等到出队时才判断。事实上，在入队时判断即可。

2. 这题要判重（要不然会T）。具体是：开一个标记数组，每次入队时同时把标记入队的状态（即位置）。在以后如果有相同的位置则不入队。

3. 这题最烦的地方是有多组数据，我看有很多大佬每次都清空标记数组。其实没必要，每次更换标记即可。最简单的标记是第1组数据用1标记，第2组数据用2标记……第i组数据用i标记。

4. 确定范围。首先，我们要知道：加1，减1和乘2的范围是不同的。设初始位置为想x，终止位置为y，那么：加1的范上限是y-1，减1的下限是1，乘2的上限是y+1。

还有，为了~~偷懒~~减少码量，我定义了一个生成结构体的函数。

```cpp
#include<bits/stdc++.h>
using namespace std;
int pc[100005];
struct z
{
	int w,c;
};
queue<z>a;
z f(int e,int u)
{
	z s;
	s.w=e,s.c=u;
	return s;
}
int main() 
{
	int t,i,x,y,sw,sc;
	cin>>t;
	for(i=1;i<=t;i++)
	{
		cin>>x>>y;
		while(a.size()) a.pop();
		a.push(f(x,1));
		for(;;)
		{
			sw=a.front().w,sc=a.front().c;
			if(sw+1==y||sw-1==y||sw*2==y)
			{
				cout<<sc<<endl;
				break;
			}
			if(sw+1<y&&pc[sw+1]!=i)
				a.push(f(sw+1,sc+1)),pc[sw+1]=i;
			if(sw-1>0&&pc[sw-1]!=i)
				a.push(f(sw-1,sc+1)),pc[sw-1]=i;
			if(sw*2<=y+1&&pc[sw*2]!=i)
				a.push(f(sw*2,sc+1)),pc[sw*2]=i;
			a.pop();
		}
	}
}
```


---

## 作者：swl3992 (赞：0)

# BFS广搜

# ~~虽然刚开始我好几遍爆零~~

# ~~暴力模拟FarmJohn~~

不多说，上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k;	//貌似不需要开long long
bool vis[100010];	//vis数组，不开会T和M得很惨
struct node
{
	long long x,sum;	//坐标和走到这里用了多少步
	node(long long x=0,long long sum=0):x(x),sum(sum){}	//构造函数，后面BFS要用
};
bool check(long long x)	//check函数
{
	return (x>=0&&x<=100000);	//不能小于0，不能跃出边界100000
}
void bfs(node x)
{
	queue<node> q;
	q.push(x);	//进队
	while(!q.empty())
	{
		node f=q.front();
		q.pop();	//取出
		if(f.x==k)	//到达
		{
			cout<<f.sum<<endl;
			return;
		}
		long long xx;
		xx=f.x+1;	//向前
		if(check(xx)&&!vis[xx])	//调用
		{
			q.push(node(xx,f.sum+1));
			vis[xx]=true;
		}
		xx=f.x-1;	//同理
		if(check(xx)&&!vis[xx])
		{
			q.push(node(xx,f.sum+1));
			vis[xx]=true;
		}
		xx=2*f.x;
		if(check(xx)&&!vis[xx])
		{
			q.push(node(xx,f.sum+1));
			vis[xx]=true;
		}
	}
}
int main ()
{
	ios::sync_with_stdio(0);
	long long T;
	cin>>T;
	while(T--)	
	{
    	cin>>n>>k;
    	memset(vis,false,sizeof(vis));	//我刚开始忘记清零，结果爆零
    	node x;
    	x.sum=0;
    	x.x=n;
    	bfs(x);	//调用
	}
	return 0;
}
```


---

## 作者：MikukuOvO (赞：0)

### 题目大意

FJ丢失了他的一头牛，他决定追回他的牛。已知FJ和牛在一条直线上，初始位置分别为x和y，假定牛在原地不动。FJ的行走方式很特别：他每一次可以前进一步、后退一步或者直接走到2x的位置。计算他至少需要几步追上他的牛

### 题目分析

宽搜经典题，开一个队列，队列每一个元素维护坐标和步数，在开一个vis数组记录该点是否被找过，因为如果被找过那么到达该点的不是步数一定小于等于目前步数

### 性能分析

每一个点只会被访问一次，最差O(n)

### 代码实现

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#define maxn 100000
using namespace std;

int n,k,T;
bool vis[maxn+5];

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(vis,0,sizeof(vis));
        queue<pair<int,int> >q;
        scanf("%d%d",&n,&k);
        q.push(make_pair(n,0));
        vis[n]=1;
        while(!q.empty())
        {
            int s=q.front().first,t=q.front().second;
            q.pop();
            if(s==k)
            {
                printf("%d\n",t);
                break;
            }
            if(s*2<=maxn&&vis[s*2]==0) q.push(make_pair(s*2,t+1)),vis[s*2]=1;
            if(s+1<=maxn&&vis[s+1]==0) q.push(make_pair(s+1,t+1)),vis[s+1]=1;
            if(s-1>=0&&vis[s-1]==0) q.push(make_pair(s-1,t+1)),vis[s-1]=1;
        }
    }
    return 0;
}

---

## 作者：VLMOESR (赞：0)

第二次发题解

我们先来分析一下题目

可以移动到

x+1

x-1

x*2

于是

新的广搜开始了吗？
```pascal
	var
	i,j,k,m,n,head,tail,s,x,y,x1,y1:longint;
	b:array[1..5,1..100000]of longint;
	f:array[1..1000000]of boolean;
	begin
   	read(m);
    for i:=1 to m do
    begin
        fillchar(f,sizeof(f),false);
        readln(x,x1);
        head:=0;
        tail:=1;
        b[1,1]:=x;
        f[x]:=true;
        if x=x1 then
        begin
            writeln(x-x1);
            continue;
        end;//作调整
        while tail>=head do
        begin
            inc(head);
            y:=b[1,head]+1;
            if y<=100000 then
            begin
               inc(tail);
               b[1,tail]:=y;
               b[2,tail]:=b[2,head]+1;
               if f[y] then dec(tail)
               else f[y]:=true;
               if y=x1 then begin
                   writeln(b[2,tail]);
                   break;
               end;
            end;//向上前进1步
            y:=b[1,head]-1;
            if (y>=1) then
            begin
               inc(tail);
               b[1,tail]:=y;
               b[2,tail]:=b[2,head]+1;
               if f[y] then dec(tail)
               else f[y]:=true;
               if y=x1 then begin
                   writeln(b[2,tail]);
                   break;
               end;
            end;//向下前进1步
            y:=b[1,head]*2;
            if y<=100000 then
            begin
               inc(tail);
               b[1,tail]:=y;
               b[2,tail]:=b[2,head]+1;
               if f[y] then dec(tail)
               else f[y]:=true;
               if y=x1 then begin
                   writeln(b[2,tail]);
                   break;
               end;
            end;//向上前进x步
        end;
        y:=0;x:=0;x1:=0;fillchar(b,sizeof(b),0);
    end;
	end.
```
求通过

---

## 作者：wonSSnow (赞：0)

## 这道题我认为就是一道bfs类似模板的题目。
#### 我们可以从题目中知道FJ有3种走法：

#### 1、way+1。   2、way-1。 3、2*way

### 在bfs中每次先判断是否需要把这三种方案qush到队列中去。

### visit数组应该保存每次到达这个位置最小的步数，可以算是一个大优化。

### 并且向左走时，如果FJ到达的点是0，或者FJ到达的点是100000，就没有意义了！！！
### 所以应该再加上边界处理：0<way<100000

# code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,y,v[100005];
struct node{
    int way,step,judge;//judge是用来判断FJ是否能往左走
};
void bfs(){
    queue<node> q; 
    node start;
    if(x==1) start.judge=0;
    else start.judge=1;
    start.way=x,start.step=0;  
    v[x]=0;  
    q.push(start);
    while(!q.empty())
    {
        node now=q.front(); q.pop();
        if(now.way==y){ 
            if(now.step<v[y]) 
            	v[y]=now.step; 
            continue;
        }
        node p1,p2,p3; int flag=0;//p1,p2,p3代表三种情况，flag表示他是否往左走了
        p1.step=now.step+1,p1.judge=1,p1.way=now.way+1;
        if(now.judge==1){	
        	flag=1;
            if(now.way-1==0) p2.judge=0;
            else p2.judge=1;
            p2.step=now.step+1,p2.way=now.way-1;
        }
        p3.way=now.way*2,p3.judge=1,p3.step=now.step+1;
        if(p1.way<100000&&p1.step<v[p1.way]){ 
        	v[p1.way]=p1.step; 
            q.push(p1);
        }
        if(p2.step<v[p2.way]&&flag){ 
        	v[p2.way]=p2.step; 
            q.push(p2);
        }
        if(p3.way<100000&&p3.step<v[p3.way]){ 
        	v[p3.way]=p3.step; 
            q.push(p3);
        }
    }
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {	
        memset(v,0x3f3f3f,sizeof(v));
        scanf("%d%d",&x,&y); bfs();
        printf("%d\n",v[y]);
    }
}
```
码风奇丑，请多指教

---

## 作者：Drinkkk (赞：0)

/\*
P1588 题解

宽度优先搜索

\*/
        
        
        
        
        
        
```cpp
#include <cstdio>//头文件
#include <cstring>//头文件
struct node{ int x,t; } f[1000001];//开一个队列来存储搜索到的每一步的坐标以及当前走到这里时所要用到的**最少的**步数
int ans=0,sx=0,ex=0;//定义变量ans是用来表示当前这组数据的答案的，sx表示的是起点的坐标，ex表示的是结束的坐标
bool road[1000001];//开一个bool数组road来表示当前坐标为nx的这一层楼到底有没有到过（即road[i]表示坐标为i的楼层有没有被踩到过，如果为false表示没有被踩到过，反之如果为true就表示已经被踩到过了）
void bfs()//这是宽度优先搜索的函数
{
    int tou=1,wei=2;//初始化tou和wei（即head和tail）
    f[1].x=sx;//首先先将第一格的坐标设为起点的坐标（当然，你也可以写成f[tou].x=sx）
    f[1].t=0;//因为一开始FJ就在起点，所以将f[1].t的值设为0
    while(tou<wei)//当头的值**小于**尾的值的时候进行循环
    {
        int nx=f[tou].x+1;//向后走一格
        if(nx==ex && ans>f[tou].t+1)//如果现在走到了终点且当前的答案优于现在的答案
        {
            ans=f[tou].t+1;//那么就更新ans的值
        }
        if(nx>=1 && nx<=ex*2 && road[nx]==false)//如果当前的nx大于等于1，且**nx小于等于ex*2**时，且当前这里还没有被人走过是就可以开始存储相关信息啦
        {
            road[nx]=true;//标记一下这里已经被人走过啦
            f[wei].t=f[tou].t+1;//因为这一步是在原来的基础上又走了一步，所以得到f[wei].t=f[tou].t+1
            f[wei].x=nx;//储存新的坐标
            wei++;//把wei的值加1（即tail++）
        }
        nx=f[tou].x-1;//向前走一格
        if(nx==ex && ans>f[tou].t+1)//如果现在走到了终点且当前的答案优于现在的答案
        {
            ans=f[tou].t+1;//那么就更新ans的值
        }
        if(nx>=1 && nx<=ex*2 && road[nx]==false)//如果当前的nx大于等于1，且**nx小于等于ex*2**时，且当前这里还没有被人走过是就可以开始存储相关信息啦
        {
            road[nx]=true;//标记一下这里已经被人走过啦
            f[wei].t=f[tou].t+1;//因为这一步是在原来的基础上又走了一步，所以得到f[wei].t=f[tou].t+1
            f[wei].x=nx;//储存新的坐标
            wei++;//把wei的值加1（即tail++）
        }
        nx=f[tou].x*2;//走到当前的坐标*2的地方 
        if(nx==ex && ans>f[tou].t+1)//如果现在走到了终点且当前的答案优于现在的答案
        {
            ans=f[tou].t+1;//那么就更新ans的值
        }
        if(nx>=1 && nx<=ex*2 && road[nx]==false)//如果当前的nx大于等于1，且**nx小于等于ex*2**时，且当前这里还没有被人走过是就可以开始存储相关信息啦
        {
            road[nx]=true;//标记一下这里已经被人走过啦
            f[wei].t=f[tou].t+1;//因为这一步是在原来的基础上又走了一步，所以得到f[wei].t=f[tou].t+1
            f[wei].x=nx;//储存新的坐标
            wei++;//把wei的值加1（即tail++）
        }
        tou++;//把tou的值加1（即head++）
    }
    return ;//返回到主函数 
}
int main()
{
    int t=0;//定义变量 
    scanf("%d",&t);//读入数据组数 
    while(t--)//循环读入这t组数据 
    {
        ans=999999999;//数据初始化 
        sx=0;//数据初始化
        ex=0;//数据初始化
        memset(f,0,sizeof(f));//数据初始化
        memset(road,false,sizeof(road));//数据初始化
        scanf("%d %d",&sx,&ex);//读入数据 
        if(sx>=ex)//判断特殊情况 
        {
            printf("%d\n",sx-ex);
        }
        else
        {
            bfs();//宽搜 
            printf("%d\n",ans);//打印答案并换行 
        }
    }
    return 0;//结束程序 
}
```

---

## 作者：doby (赞：0)

P2685……

双倍经验……

广搜解决……

记得初始化……

特殊情况直接处理……

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int ts,wz[500009],u,tim[2000009],qs[2000009],head,tail,n,k,t,w,z;
int hash(int h)//因为位置有限制，直接用桶排除
{
    if(wz[h]){return 0;}
    else{wz[h]++;return 1;}
}
void bfs(int n,int k)
{
    memset(wz,0,sizeof(wz));//初始化
    memset(tim,0,sizeof(tim));
    memset(qs,0,sizeof(qs));
    head=0,tail=1;
    if(n>=k)//强力剪枝……
    {
        printf("%d\n",n-k);//直接往回跑
        return;
    }
    qs[1]=n,tim[1]=0;//入队
    while(head<tail)
    {
        head++,w=qs[head],t=tim[head];//取出状态
        z=w+1;//往前一步
        if(z<=k)//剪枝(然而根本不需要)……
        {
            if(z==k)
            {
                printf("%d\n",t+1);//抓到了……
                return;
            }
            if(hash(z))
            {
                tail++,//没有重复，入队
                qs[tail]=z,
                tim[tail]=t+1;
            }
        }
        z=w-1;//往回一步
        if(z>=0)//更没用的剪枝……
        {
            if(z==k)//全部同上
            {
                printf("%d\n",t+1);
                return;
            }
            if(hash(z))
            {
```
tail++,
```cpp
                qs[tail]=z,
                tim[tail]=t+1;
            }
        }
        z=w*2;
        if(z<=k*3)//不能超过太多……
        {
            if(z==k)//又是同上……
            {
                printf("%d\n",t+1);
                return;
            }
            if(hash(z))
            {
```
tail++,
```cpp
                qs[tail]=z,
                tim[tail]=t+1;
            }
        }
    }
}
```
/\*
核心部分已经结束了……

剩下的爱看不看……

毕竟谁都会……

就是模拟了……

\*/
```cpp
int main()
{
    scanf("%d",&ts);
    for(int i=1;i<=ts;i++)
    {
        scanf("%d%d",&n,&k);
        bfs(n,k);
    }
    return 0;
}
```

---

## 作者：ZZFreya (赞：0)

**蒟蒻的OI之路之宽搜（BFS）**

\_题目描述\_ 就是给出起点x和终点y,每次可以走到x+1，x-1,或x\*2，求走几步可以从x到y

\_方法标签\_搜索 宽搜 暴力


好啦，上重点——————

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<set>//头文件。。。
using namespace std;
int q[100005],d[100005];
bool flag[100005];
int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        int y,x,l=0,r=0;
        memset(flag,0,sizeof(flag));//清空用来打标记的数组
        cin>>x>>y;
        if(x>=y){//在目标以后？！拔腿往回跑！
            cout<<x-y<<endl;
            continue;
        }
        q[++r]=x;d[r]=0;flag[x]=1;
        while(l!=r){
            l++;
            int tt=q[l];
            int xx=tt-1;//接下来枚举三种情况
            if(xx>=0 && xx<=100000 && !flag[xx]){
                r++;q[r]=xx;d[r]=d[l]+1;flag[xx]=1;
            }
            if(xx==y){//如果找到正解
                cout<<d[r]<<endl;
                break;
            }
            if(xx>y)continue;
            xx=tt*2;//以下同上+1
            if(xx>=0 && xx<=100000 && !flag[xx]){
                r++;q[r]=xx;d[r]=d[l]+1;flag[xx]=1;
            }
            if(xx==y){
                cout<<d[r]<<endl;
                break;
            }
            xx=tt+1;//以下同上+2
            if(xx>=0 && xx<=100000 && !flag[xx]){
                r++;q[r]=xx;d[r]=d[l]+1;flag[xx]=1;
            }
            if(xx==y){
                cout<<d[r]<<endl;
                break;
            }    
        }
    }
    return 0;// Lovely ending！！！！
}
```

---

