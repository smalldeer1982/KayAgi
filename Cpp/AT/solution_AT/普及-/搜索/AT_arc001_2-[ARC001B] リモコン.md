# [ARC001B] リモコン

## 题目描述

高桥君要调整空调的设定温度。现在的设定温度是A度，而他想调到B度。
空调遥控器按一次可以:
- 上调或下调1度
- 上调或下调5度
- 上调或下调10度
高桥君想求出从A调到B度的最小操作数。

## 说明/提示

样例1: 
输入：
```
7 34
```
输出：
```
5
```
依次上调10、10、5、1、1度即可

样例2: 
输入：
```
19 28
```
输出：
```
2
```
上调10度、下调1度即可。


样例3: 
输入：
```
10 10
```
输出：
```
0
```
温度一样时无需调整。


感谢 @玉签初报明  提供的翻译。

# 题解

## 作者：sxtm12138 (赞：20)

本题有两种做法，正解显然是搜索，不过贪心也可以做，而且更简单，所以我两种方法都讲一下。

首先是搜索，由于数据范围较小（小得不能再小了），通过剪枝后是可以AC的，由于有六种调法，所以我先比较当前温度与目标温度的大小再进行搜索，若大于目标温度就往下搜，否则就往上搜。

 _以下是代码：_ 

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t=123456;//t记录最小次数
void dd(int x,int s)//x表示当前温度，s表示调节次数
{if(s>=t) return;//剪枝，大于最小次数就退出
if(x==n) {t=min(t,s);//选择最小次数
          return;}//调整完成就返回
if(x>n) {dd(x-1,s+1);
         dd(x-10,s+1);
         dd(x-5,s+1);}//大于目标温度就往下搜
else {dd(x+1,s+1);
      dd(x+10,s+1);
      dd(x+5,s+1);}//反之就往上搜
}
int main()
{cin>>k>>n;//读入当前温度k与目标温度n
 dd(k,0);//开始搜索
 cout<<t<<endl;//输出最小次数，别忘了换行！！！
 return 0;
}
```

------------


当然这题如果用贪心会更简单，为了使调节次数尽可能小，就应该在当前温度与目标温度差距较大时一次调十度快速缩小差距，当差距足够小时再调一度或五度。接下来开始找规律：

    温差k：  1   2   3    4    5    6    7    8    9    10

    最低次数：1   2   3    2    1    2    3    3    2    1
    
可以发现所需步数与温差与0、5、10间的差距有关，且温差大于等于8时调十度会更快；反之，如果一度一度调，所需次数等于k，如果调五度，再一度一度调，所需次数为abs(5-k)+1。（调五度也算一次所以要加一）最后，取两者中的较小值加上调十度的次数即为所求。

 _以下是代码：_ 

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t=0;//t记录次数
int main()
{cin>>k>>n;//读入
 k=abs(n-k);//算温差
 while(k>=8)//温差大于等于8时
   {k=abs(k-10);//计算当前温差
    t++;//累加次数
   }
 cout<<t+min(k,abs(5-k)+1)<<endl;//加上两者中的较小值即为总次数
 return 0;
}
```

---

## 作者：珅肐 (赞：11)

开始想用枚举取最小值，半天没有做出来（鄙人蒟蒻一枚）

当然就想到if啦

经我认真的一番推算~~（其实是手动枚举（huaji））~~后，
终于找到了规律

### :以十为区间，每个区间的值等于上一个区间的值+1

其实非常好理解，就是初值加上这个数%10

初值手算一下，也不麻烦
```cpp
#include<iostream>
using namespace std;
int main()
{
	int a,b;
	cin>>a>>b;//输入
	b-=a;
	if(b<0) b=-b;//处理一下b<a的情况
	if(b%10==1) cout<<b/10+1<<endl;
	if(b%10==6) cout<<b/10+1+1<<endl;
    if(b%10==2) cout<<b/10+2<<endl;
    if(b%10==7) cout<<b/10+2+1<<endl;
	if(b%10==3 || b%10==8) cout<<b/10+3<<endl;//3、8相同，懒得再写一个if，下同
	if(b%10==4 || b%10==9) cout<<b/10+2<<endl;
	if(b%10==5) cout<<b/10+b%10/5<<endl;
    if(b%10==0) cout<<b/10<<endl;
    //记住所有的输出一定要换行！换行！换行！~~我不会告诉你ATCoder就这样坑了我不下十次~~
	return 0;//好习惯
}
```

---

## 作者：wdcxz (赞：11)

## 一道比较水的深搜
#### 看到别的大佬都在用广搜，打表，我突发奇想，这题可以用深搜啊！
下面是代码：
```cpp
#include <bits/stdc++.h>//万能头
using namespace std;
int a,b,tot=100,v[100];//v数组用来判重，tot记录最终答案，tot必须赋大值，否则永远为0
inline void dfs(int n,int t){
	if(n>40||n<0||v[n]==1)return ;//判断边界，并去重
	if(t>tot)return ;//若当前次数已经大于tot了，则去掉
	if(n==b){tot=min(tot,t);return ;}//如果调到b了，则取tot与当前次数的较小值
	v[n]=1;//把v数组设为已经有数了
	dfs(n+1,t+1);
	dfs(n-1,t+1);
	dfs(n+5,t+1);
	dfs(n-5,t+1);
	dfs(n+10,t+1);
	dfs(n-10,t+1);//有八种方式
	v[n]=0;//回溯
}
int main(){
	scanf("%d%d",&a,&b);//输入
	dfs(a,0);//调用函数
	printf("%d",tot);//输出
	return 0;
}
//wdcxz
```

---

## 作者：Diamiko (赞：10)

## 核心思想：最短路

### 1.建模

把温度作为点，把按一次遥控器能切换的温度中间连边，边权为1，表示按了一次。

以温度A为起点，温度B为终点跑最短路。A到B的最短距离即为最少次数。

### 2.算法

本题数据量小，A与B的范围都是40，可以使用Floyd和Johnson，也可以Dijkstra和SPFA等等。

我个人秉承一贯的理念：只要是单源最短路，没有负边权，那么就用Dijkstra+堆优化。

### 3.细节

#### 怎么建图？

由于数据量小，我们可以在输入前把图预处理出来。

枚举40个温度点，把与当前温度相邻的6个温度连边，即

`x+1 , x-1 , x+5 , x-5 , x+10 , x-10`

在建边的时候注意不要越界。

### 4.代码

~~其实就是模板，感觉也不用上代码了~~

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#define INF 0x7fffffff
#define pii pair<int,int>
using namespace std;
struct Node
{
    int head;
    int dis;
}node[100005];
struct Edge
{
    int next,to,len;
}edge[1000005];
int cnt;
void addEdge(int u,int v,int w)
{
    edge[++cnt]={node[u].head,v,w};
    node[u].head=cnt;
}
//链式前向星存图
int A,B;
void Dijkstra()
{
    for(int i=0;i<=40;i++)
    {
        node[i].dis=INF;
    }
    //切记初始化
    
    priority_queue<pii,vector<pii>,greater<pii> >q;
    //STL小根堆
    q.push({0,A});
    node[A].dis=0;
    while(q.size())
    {
        pii tmp=q.top();
        q.pop();
        int d=tmp.first,u=tmp.second;
        if(d!=node[u].dis)continue;
        for(int e=node[u].head;e;e=edge[e].next)
        {
            int v=edge[e].to;
            if(node[v].dis>d+edge[e].len)
            {
                node[v].dis=d+edge[e].len;
                q.push({node[v].dis,v});
            }
        }
    }
}
//以上为模板，不过多介绍

int main()
{
    for(int i=0;i<=40;i++)
    {
        if(i+1<=40)   addEdge(i,i+1,1);
        if(i-1>=0)    addEdge(i,i-1,1);
        if(i+5<=40)   addEdge(i,i+5,1);
        if(i-5>=0)    addEdge(i,i-5,1);
        if(i+10<=40)  addEdge(i,i+10,1);
        if(i-10>=0)   addEdge(i,i-10,1);
        //注意判断越界
    }
    //预处理图
    
    scanf("%d%d",&A,&B);
    Dijkstra();
    printf("%d\n",node[B].dis);
    return 0;
}
```

OK!

### 不过你以为到这就结束了？

考虑到本题数据范围颇小，为了有更优的解，我们可以打表。

（其实以上代码已经够用了）

枚举每个A与B的情况，输出到数组里。

注意细节的处理。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#define INF 0x7fffffff
#define pii pair<int,int>
using namespace std;
struct Node
{
    int head;
    int dis;
}node[100005];
struct Edge
{
    int next,to,len;
}edge[1000005];
int cnt;
void addEdge(int u,int v,int w)
{
    edge[++cnt]={node[u].head,v,w};
    node[u].head=cnt;
}
void Dijkstra(int A)
{
    for(int i=0;i<=40;i++)
    {
        node[i].dis=INF;
    }
    priority_queue<pii,vector<pii>,greater<pii> >q;
    q.push({0,A});
    node[A].dis=0;
    while(q.size())
    {
        pii tmp=q.top();
        q.pop();
        int d=tmp.first,u=tmp.second;
        if(d!=node[u].dis)continue;
        for(int e=node[u].head;e;e=edge[e].next)
        {
            int v=edge[e].to;
            if(node[v].dis>d+edge[e].len)
            {
                node[v].dis=d+edge[e].len;
                q.push({node[v].dis,v});
            }
        }
    }
}
int main()
{
	freopen("AT46打表.txt","w",stdout);
	//输出到文件里，方便复制 
    for(int i=0;i<=40;i++)
    {
        if(i+1<=40)   addEdge(i,i+1,1);
        if(i-1>=0)    addEdge(i,i-1,1);
        if(i+5<=40)   addEdge(i,i+5,1);
        if(i-5>=0)    addEdge(i,i-5,1);
        if(i+10<=40)  addEdge(i,i+10,1);
        if(i-10>=0)   addEdge(i,i-10,1);
    }
    puts("int ans[45][45]={");
    for(int A=0;A<=40;A++)
    {
    	printf("{");
		Dijkstra(A);
    	for(int B=0;B<=39;B++)
    	{
    		printf("%d,",node[B].dis);
		}
    	printf("%d",node[40].dis);
		if(A!=40)puts("},");
		else puts("}");
	}
	puts("};");
    return 0;
}
```
这就是生成程序。

然后把打出的表放到代码里，输入A和B后直接输出即可。

```cpp
#include<cstdio>
using namespace std;
int ans[45][45]={
{0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5,6,5,4,5,6,6,5,4},
{1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5,6,5,4,5,6,6,5},
{2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5,6,5,4,5,6,6},
{3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5,6,5,4,5,6},
{2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5,6,5,4,5},
{1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5,6,5,4},
{2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5,6,5},
{3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5,6},
{3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4,5},
{2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3,4},
{1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4,3},
{2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5,4},
{3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5,5},
{4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4,5},
{3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3,4},
{2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4,3},
{3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5,4},
{4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4,5},
{4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3,4},
{3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2,3},
{2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3,2},
{3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4,3},
{4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4,4},
{5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3,4},
{4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2,3},
{3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3,2},
{4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4,3},
{5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3,4},
{5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2,3},
{4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1,2},
{3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2,1},
{4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3,2},
{5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3,3},
{6,5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2,3},
{5,6,5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1,2},
{4,5,6,5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2,1},
{5,4,5,6,5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3,2},
{6,5,4,5,6,5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2,3},
{6,6,5,4,5,6,5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1,2},
{5,6,6,5,4,5,6,5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0,1},
{4,5,6,6,5,4,5,6,5,4,3,4,5,5,4,3,4,5,4,3,2,3,4,4,3,2,3,4,3,2,1,2,3,3,2,1,2,3,2,1,0}
};
int A,B;
int main()
{
    scanf("%d%d",&A,&B);
    printf("%d\n",ans[A][B]);
    return 0;
}
```
结束！

---

## 作者：哈哈哈哈。 (赞：5)

# BFS大法好啊
好明显的广搜啊。几乎模板题，值得拿来练练手。说话实话其实 **岛国** 题还是~~比较水的吧？~~

------------
刚看到就知道是广搜了，毕竟人家让你求最少操作次数，很明显嘛，一波BFS直接带走

------------

代码  QAQ：

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int dir[8]={1,-1,5,-5,10,-10};//模拟6种调温度的可能;
struct ss{
    int x,y;//结构体方便处理当前温度，以及当前操作次数;
};
int n,m;
queue<ss> q;//队列，存储扩展状态;
int bfs(int x,int y)
{
    ss s;//初始点;
    s.x=x;
    s.y=y;
    q.push(s);//存入队列;
    while(!q.empty())//队列不为空（反正就是没有可以扩展的状态就会停下，那么此时队列为空）;
    {
        ss now=q.front();//取出当前队首;
        q.pop();//弹出队首;
        if(now.x==m)//满足温度条件;
        {
            return now.y;
        }
        for(int i=0;i<6;i++)//扩展温度;
        {
            int tx=now.x+dir[i];//存储;
            ss s;
            s.x=tx;
            s.y=now.y+1;
            q.push(s);//放入队列;
        }
    }
}
int main()
{
    cin>>n>>m;
    cout<<bfs(n,0)<<endl;
    return 0;
}
```
------------
真的 ~~简单~~ 

------------
## 值得学习啊

---

## 作者：光阴且含笑 (赞：5)

一个蒟蒻的歪门邪道的BFS

代码里u和s的用法就写在这里：以样例一为例，压入7后压入6 8 2 12 -3 17再弹出7，此时队内有6个元素，s=6,以这六个元素向6个方向搜索后u=6，则第一批搜索的6个元素都被使用了，则均弹出后队内剩下的是第二批搜索后的元素，u清零，s=第二批搜索后元素个数，一直操作到找到答案

温馨提示：输出答案后一定要换行！！（当我没换行时听到WA声一片是震惊的）



------------
 
 
AC代码如下：

```cpp
#include<bits/stdc++.h>//万能头好！（其实是我懒得记那么多头文件）
using namespace std;
int main()
{
  queue<int> q;     //使用队列
  int a,b;     //a为初始温度，b为目标温度
  int t[7]={0,-1,1,-5,5,10,-10};     //六个调温方式
  int u=0,s;     //u和s搭配使用，上面有解释
  int bj[100];     //bj就是标记（接地气）
  int ans=1;     //最短步数
  memset(bj,0,sizeof(bj));     //数组初始化为0，个人习惯
  cin>>a>>b;
  if(a==b){     //特判，万一碰到a=b（真的有一个测试点）
    cout<<"0"<<endl;
    return 0;
   } 
  bj[a+50]=1;    //a+50是因为数组下标不能为负，那就以50为0度
  q.push(a);    //压入a
  for(int i=1;i<=6;i++){    //六个调温方式
    q.push(a+t[i]);    //压入新温度
    bj[a+t[i]+50]=1;    //做标记
   }
  q.pop();    //弹出a
  s=q.size();    //得到队列元素个数
  while(q.front()!=b){
    u++;
    for(int i=1;i<=6;i++){   //以队头元素向六个方向（就那意思）搜索
      if(bj[q.front()+t[i]+50]==0)    //如果标记为1则不用再搜索了
      q.push(q.front()+t[i]);
    }
    q.pop();     //弹出队头元素
    if(u==s){
      ans++;     //还没找到答案，步数＋1
      u=0;
      s=q.size();
     }
   }
  cout<<ans<<endl;     //输出答案并换行
  return 0;
}
```


------------

啊哈，这是本蒟蒻的第一篇题解，有些小激动（排版在下已经尽力了...）


---

## 作者：云浅知处 (赞：4)

首先，很显然，我们应该将空调的温度每次调高\低 $10^{\circ}\text{C}$，直到还需要调的温度小于 $10^{\circ}\text{C}$。

那么，如何处理剩下的这几摄氏度呢？

实际上，因为只有 $\{0,1,2,3,4,5,6,7,8,9,10\}$ 这十种可能......

### 我们完全可以暴力枚举啊！

下面的表格中，符号 $+$ 表示“调高”，符号 $-$ 表示“调低”

$\begin{matrix}\small\text{还需要调的度数}&\small\text{还需要调的次数}&\small\text{方法}\\0&0&\small\textrm{不用动}\\1&1&+1\\2&2&+1+1\\3&3&+1+1+1\\4&2&+5-1\\5&1&+5\\6&2&+5+1\\7&3&+5+1+1\\8&3&+10-1-1\\9&2&+10-1\\10&1&+10\end{matrix}$

我们可以定义一个数组来存储这$11$种情况分别需要的步数

`int a[11]={0,1,2,3,2,1,2,3,3,2,1};`
***
一些需要注意的事情：

* At的题目最后必须换行！
* 有负数！（我才不会告诉你我因为这个东西WA了一次）

***
接下来，开写代码！

**代码已经过防伪处理，勿抄**

```cpp
#include<bits/stdc++.h>//万能头棒棒哒
using namespace std;
int main(){
	int a[11]={0,1,2,3,2,1,2,3,3,2,1},A,B,C,x,y;//数组a的含义上面解释过了，A,B同题意，C是A与B的差，x,y后面会解释。
	cin>>A>>B;//输入目前的温度与需要调的温度。
	C=abs(B-A);//将需要调整的温度赋值给C，记得开绝对值！
	y=C/10;//y是需要加／减十的次数。
	x=C%10;//x是在加／减y个十之后还需要调的温度。
	cout<<a[x]+y<<endl;//将调x度所需的步数与y相加并输出，记得换行。
	return 0;//完结撒花
}
```
~~貌似是最短代码哦~~

---

## 作者：LW_h_FP (赞：4)

这题可以用广度优先搜索

当然一位数组用这个可能比较多此一举吧，这个主要二维三维之类的

主要的意思是从第一个(也就是初始温度开始)用一个队列记录他能够走到的数，再去看他能够访问的那个数能够走到的数，因为第一次访问就是最短路，所以vis记录他前面走过的数不再访问，
当然看不到可以先去学学广度优先搜索，或者看看前面的题解

我有一个地方写错了，就是tail和head写反了，不爽的话可以自己改

虽然长还是写一下注释吧

```
#include<iostream>
using namespace std;

int a[100010],vis[100010],b[100010];//a记录最短路，vis记录是否访问过，b记录下一个搜索的点
int n,k,d[10]={1,-1,5,-5,10,-10},tail,head;//d是他可以前后左右走的点

int main(){
	cin>>n>>k;
	a[n]=0,vis[n]=1,b[0]=n;
	tail=head=0;
	while(tail<=head){
		int no=b[tail];
		if(b[tail]==k) break;
		tail++;
		for(int i=0;i<6;i++){
			int x=no+d[i];
			if(x<100010&&x>-1&&vis[x]!=1){
				head++;
				vis[x]=1;
				b[head]=x;
				a[x]=a[no]+1;
			}
		}
	}
	cout<<a[k]<<"拒绝抄袭，共建和谐洛谷";
	return 0;
}
```

---

## 作者：ALGOBAKE__YE (赞：4)

看到题面，一下就想到用贪心。

初贪心：
	尽可能用大的幅度调整温度。即代码中只有对10,5,1的操作。
    

------------

 但wa了一个点，后来想到9=10-1，只用两次，而不是9=5+1+1+1+1用五次。
 
 所以对十以内的数字进行判断
 
 末贪心：
 
 9=10-1 最少两次
 
 8=10-1-1 最少三次
 
 7=5+1+1 最少三次
 
 6=5+1 最少两次
 
 4=5-1 最少两次
 
 3=5-1-1=1+1+1 最少三次
 
 2=1+1 最少两次
 
 于是就有了如下代码
 ```cpp
#include<bits/stdc++.h>
using namespace std;

int a,b,box,cnt;

int main()
{
	cin>>a>>b;
	box=abs(a-b);
	
	if(box>=10)
	{
		cnt+=box/10;
		box%=10;
	}
	if(box>=9)
	{
		cnt+=2*(box/9);
		box%=9;
	}
	if(box>=8)
	{
		cnt+=3*(box/8);
		box%=8;
	}
	if(box>=5)
	{
		cnt+=box/5;
		box%=5;
	}
	if(box>=4)
	{
		cnt+=2*(box/4);
		box%=4;
	}
	cnt+=box;
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：2)

没有最短路呀~

~~赶紧过来骗一点咕值~~

由于$a,b≤40$，所以可以放心的预处理一遍，然后跑$Dijkstra$

### 要小心越界，所以预处理要特判

```cpp
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct edge
{
    int node,weight;
    edge(int node_,int weight_):
        node(node_),weight(weight_){}//构造函数
};
struct element
{
    int node,value;
    element(int node_,int value_):
        node(node_),value(value_){}//构造函数
    bool operator <(const element &other) const//重载，为优先队列提供比较方式
    {
        return value>other.value;
    }
};
vector<edge> v[41];//邻接表
int dis[41],a,b;
bool vis[41];
inline void dijkstra()//板子，不解释
{
    priority_queue<element> q;
    q.push(element(a,0));
    while(!q.empty())
    {
        element k=q.top();
        q.pop();
        if(vis[k.node])
            continue;
        vis[k.node]=1;
        dis[k.node]=k.value;
        if(k.node==b)//如果搜到了直接跳出去
            return;
        for(vector<edge>::iterator it=v[k.node].begin();it!=v[k.node].end();++it)
            q.push(element(it->node,it->weight+k.value));
    }
}
int main()
{
    cin>>a>>b;
    for(int i=1;i<=40;++i)//预处理
    {
        if(i>=1)//特判
        {
            v[i-1].push_back(edge(i,1));//建双向边
            v[i].push_back(edge(i-1,1));
        }
        if(i>=5)//特判
        {
            v[i-5].push_back(edge(i,1));
            v[i].push_back(edge(i-5,1));
        }
        if(i>=10)//特判
        {
            v[i-10].push_back(edge(i,1));
            v[i].push_back(edge(i-10,1));
        }
    }
    dijkstra();
    cout<<dis[b]<<endl;//输出
    return 0;
}
```


---

## 作者：CrTsIr400 (赞：1)

# 0.题外话qwq

看大家都没有使用双向BFS的解法，本蒟蒻就发一发吧qwq。

# 1.主要思路

因为我们知道题目给出了 $s$ 和 $t$ ，给出了起始条件和终止条件，也就是说，我们可以在**给定起点和终点**的情况下，进行双向BFS。

而且，还有一系列的变换条件，这都可以写成**每次扩展新结点**的形式，从而BFS。

# 2.双向BFS是什么？

双向BFS，顾名思义，就是这是以**两个方向BFS的**。一般从起点和终点开始遍历，使用**两个**队列扩展，如果有一棵搜索树里出现了另一棵搜索树的结点，就代表**有一种方案**使得可以找到答案，且是**最优解**，即这个**交点**所在的**从起点到终点的这么一条路径**就是**最优解**。

放张图证明双向BFS是怎么个双向搜索的：

![image.png](https://i.loli.net/2020/04/19/Mb3GsaFo9v2ewQJ.png)

这样可以把时间压缩到原来的 $\frac{1}{2}$ ，甚至更优！

代码可以这么实现：

```cpp
建立并初始化两个BFS队列q1,q2;
建立两个标记数组b1,b2;
while(!q1.empty()&&!q2.empty())
 扩展q1
  如果q1的合法扩展有q2的节点
   输出起点到这个点的距离和终点到这个点的距离；
 扩展q2
  如果q2的合法扩展有q1的节点
   输出起点到这个点的距离和终点到这个点的距离；
```

这样会大大减少程序的时间。

# 3.有一些问题

Q1：我的BFS如何扩展？

A1：可以循环 $6$ 次，每次对应一个值——如 $i=1$ 时新扩展的节点就增加 $1$，$i=2$ 时新扩展的节点就增加 $2$ 等。

Q2：如何判重？

A2：可以给每一个起始值/终止值加上一个固定的数，比如 $50$ ，这样就不会出现负数判重等问题。

# 4.部分代码

```cpp
Fu(i,1,6)
{
	Fu(j,0,1)
	{
		int nxy=q[j].front();
		if(i==1)++nxy;
		else if(i==2)nxy+=5;
		else if(i==3)nxy+=10;
		else if(i==4)--nxy;
		else if(i==5)nxy-=5;
		else if(i==6)nxy-=10;
		if(nxy>100||nxy<0)continue;
		if(b[j][nxy])continue;
		q[j].push(nxy);
//		printf("%d %d %d\n",i,j,nxy);
		b[j][nxy]=1;
		st[j][nxy]=st[j][q[j].front()]+1;
		if(b[!j][nxy])return st[j][nxy]+st[!j][nxy];
	}
}
```

然后就是注意细节方面的问题，就A了。

---

## 作者：血色黄昏 (赞：0)

本题第一篇python题解，激动~

这道题我是搜BFS看到的，结果一看发现贪心不是更简单么...

只要每次判断调几度最优就行了，这种数学应该小学就会了吧，贪心易证

上代码

```python
s = input().split()#读一行
a, b = int(s[0]), int(s[1])#赋给a和b
ans = 0#初始变动次数为0
while a != b:#一直循环到调到b度
    if abs(b - a) <= 3:#如果在3度以内（这样一度一度调最优
        if b > a:#如果是b大
            a += 1#a往上调一度
        else:
            a -= 1#不然往下调一度
    elif abs(b - a) <= 7:#<=3<=7度，这里用elif忽略掉<=3的情况，这样的话调5度最优
        if b > a:#b大
            a += 5#向上调5度
        else:
            a -= 5#不然往下5度
    else:#除此之外，肯定是调10度最优的了
        if b > a:#如果b大
            a += 10#调高10度
        else:
            a -= 10#不然调低10度
    ans += 1#次数+1
print(ans)#输出变动次数
```
总用时540ms，跑得飞快

---

## 作者：Graphcity (赞：0)

这道题其实是一道最短路的 ~~（水）~~ 裸题。

我们把每一个温度看成一个结点。假设一个结点为 $a$ , 我们只要考虑连 $a+1 , a-1 , a+5 , a-5 , a+10 , a-10$ 这六个结点就行了。

连完边之后，我们可以跑一遍 SPFA 解决问题。

```cpp
#include<bits/stdc++.h>
using namespace std;

int d[1001];
int s,t;
queue<int> q;

inline void Question(int x,int y)
{
	if(x<0 || x>1000) return;
	if(d[y]+1<d[x])
	{
		d[x]=d[y]+1;
		q.push(x);
	}
}

void SPFA(int x)
{
	Question(x+1,x);
	Question(x-1,x);
	Question(x+5,x);
	Question(x-5,x);
	Question(x+10,x);
	Question(x-10,x);
	if(!q.empty())
	{
		int num=q.front();
		q.pop();
		SPFA(num);
	}
}

int main()
{
	scanf("%d%d",&s,&t);
	memset(d,127,sizeof(d));
	d[s]=0;
	SPFA(s);
	printf("%d",d[t]);
    return 0;
}

```


---

## 作者：小小小朋友 (赞：0)

#### 题目描述：

搜索的裸题，只不过操作有点多，略烦。

#### 思路：

看到其他大佬都在用dfs，迭代加深，打表，贪心等神奇算法，蒟蒻只得给出一个标准模板（怎么还有用结构体的……完全不用啊）

使用bfs求最短路径，因为数据小可以通过，只不过在push的时候要写6个if，烦。

最后注意下输出要换行。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
queue<ll> q;
bool vis[41];
ll a,b,dis[41];
int main(){
	scanf("%lld%lld",&a,&b);
	q.push(a);
	vis[a]=1;
	dis[a]=0;
	while(!q.empty()){
		int now=q.front();
		if(now==b) {
			printf("%lld\n",dis[now]);
			return 0;
		}
		if(!vis[now-1]&&now-1>=0) vis[now-1]=1,q.push(now-1),dis[now-1]=dis[now]+1;
		if(!vis[now+1]&&now+1<=40) vis[now+1]=1,q.push(now+1),dis[now+1]=dis[now]+1;
		if(!vis[now-5]&&now-5>=0) vis[now-5]=1,q.push(now-5),dis[now-5]=dis[now]+1;
		if(!vis[now+5]&&now+5<=40) vis[now+5]=1,q.push(now+5),dis[now+5]=dis[now]+1;
		if(!vis[now-10]&&now-10>=0) vis[now-10]=1,q.push(now-10),dis[now-10]=dis[now]+1;
		if(!vis[now+10]&&now+10<=40) vis[now+10]=1,q.push(now+10),dis[now+10]=dis[now]+1;
		q.pop();
	}
	return 0;
}
```

---

## 作者：Raw_Aya9285 (赞：0)

几乎是bfs模板题，拿来练练手，顺便发个题解。

和一般的bfs题一样，只要找清楚搜索边界和调整的幅度就好啦。

首先搜索的边界，我们设定调整温度不低于0度，不高于40度。然后是调整的幅度，在题目中也有所描述，我就不赘述了。

下面贴代码吧，讲解都放在注释里面啦~

```cpp
#include<iostream>
using namespace std;

struct node{
    int dep;  //记录当前温度
    int step;  //记录调整已经经过的步数
}que[41];

int a,b,vis[41],dir[6]={1,5,10,-1,-5,-10},head=1,tail=1,flag=0;
//vis用来标注当前的温度有没有被调过
//dir是调整的六种方法，上下调1,5,10度

void bfs(){

    int nd;  //这个也是当前温度
    que[tail].dep=a;  //将开始的温度设置为a
    que[tail].step=0;  //将经过的步数设定为0
    vis[a]=1;  //当前温度已经被"用"过了
    tail++;  //尾++
    
    while(head<tail){  //当头在尾前面时才能循环
        for(int i=0;i<6;i++){  //六种调整方式
            nd=que[head].dep+dir[i];  //设定目前温度
            if(nd>0&&nd<41&&!vis[nd]){  //如果没有出界且当前温度没有被"用"过
                vis[nd]=1;  //标注一下
                que[tail].dep=nd;
                que[tail].step=que[head].step+1;
                //对应的温度和步数更改一下
                tail++;  //尾++
            }
            
            if(nd==b){
                flag=1;
                break;  //如果已经ok了，那就标记一下，退出本次循环
            }
        }
        
        if(flag){
            break;  //如果完成了，那就无需再循环了
        }
        head++;  //不然就头++
    }
    return;
}

int main(){
    cin>>a>>b;  //输入
    
    if(a==b){
        cout<<0<<endl;  //特判-如果a等于b就无需改动
        return 0;  //不用再运行了
    }
    
    bfs();  //调用函数，函数部分也可以放到这里来
    cout<<que[tail-1].step<<endl;  //输出最终步数
    return 0;  //好习惯
}
```
感谢阅读，祝你AC！

---

## 作者：ShuYuMo (赞：0)

推荐一个做法：迭代加深搜索

感觉比广搜要好写一些，其实就是加了一点别的东西的`DFS`
![迭代加深](https://cdn.luogu.com.cn/upload/pic/51128.png)

这里是luogu网校提高组讲义里的一段话，供参考。

具体来看下代码。

希望通过此题，大家能了解到这个比较冷门的算法，自我感觉挺好用。。。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int A,B;
bool haveAns=false;//用途如名，判断是否已经找到解
void DFS(int x,int deep,const int maxDeep)
//x是当前已经调到的值；deep是迭代深度；maxDeep是规定的最大迭代深度，目的就是我们不会让dfs沿着解答树的一边一头扎下去。
{
    if(haveAns)return;
    if(x==B){//找到解
        haveAns=true;//更新状态
        return;
    }
    if(deep>maxDeep)return;//限制最大迭代深度
    DFS(x+5,deep+1,maxDeep);
    DFS(x+1,deep+1,maxDeep);
    DFS(x+10,deep+1,maxDeep);
    DFS(x-1,deep+1,maxDeep);
    DFS(x-5,deep+1,maxDeep);
    DFS(x-10,deep+1,maxDeep);
}
int main()
{
    scanf("%d%d",&A,&B);
    if(A==B){cout<<0<<endl;return 0;}//之前的温度和调完的温度一样那还调啥，直接输出0步。
    int deep=abs(A-B)+5;//我们规定一个最大的深度（即每次调高或者调低一度，最大需要调节abs（A-B）次）
    //至于+5.。。这个是玄学，反正大一点总是好的。。+1就可以其实，但是时间充足，不差钱（时间）。。
    int i;
    for(i=1;i<=deep&&!haveAns;i++)//循环条件，就是没有超过最大深度，而且没找到解。
        DFS(A,1,i);
    //这样答案就是i-1。我们来考虑一下这东西的流程。
    //我先用dfs判断，如果调1步行不行；
    //如果不行，那就调两步行不行；
    //如果还不行，那就调三步行不行
    //如果还不行，那就调四步行不行
    //……………………
    //最后总有一种步数是可以的，这时候跳出循环，然后输出结果。
    cout<<--i<<endl;
    return 0;
}
//其实代码炒鸡短。。去掉注释大概30行左右。（当然还能更短）
```

---

## 作者：米奇奇米 (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
int t=123456789;//尽量把t开的大一点
int n,m;
void dd(int x,int s)
{ 
  if(s>=t) return;//考虑什么时候停止搜索（边界条件）
  if(x==n) 
  { 
     t=min(t,s);
     return;
  }
  if(x>n)
  {
	 dd(x-1,s+1);
     dd(x-10,s+1);
     dd(x-5,s+1);//按照题意（进行搜索）上调1度,上调5度,上调10度
  }
    else
    {
	  dd(x+1,s+1);
	  dd(x+10,s+1);
	  dd(x+5,s+1);//同上，下调1度，下调5度，下调10度
    }
}
int main()
{ 
  cin>>m>>n;//m为初始温度
	dd(m,0);
	cout<<t<<endl;//输出
	return 0;
}
 

```

---

