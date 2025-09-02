# [USACO10JAN] Tea Time S

## 题目描述

N (1 <= N <= 1000) cows, conveniently numbered 1..N all attend a tea time every day. M (1 <= M <= 2,000) unique pairs of those cows have already met before the first tea time. Pair i of these cows who have met is specified by two differing integers A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N). The input never indicates that cows have met each other more than once.

At tea time, any cow i and cow j who have met a mutual friend cow k will meet sometime during that tea time and thus expand their circle of known cows.

Determine whether Q (1 <= Q <= 100) pairs of cows have met after tea times are held for long enough that no new cow meetings are occurring. Query j consists of a pair of different cows X\_j and Y\_j (1 <= X\_j <= N; 1 <= Y\_j <= N).

For example, suppose that out of cows 1 through 5, we know that 2 has met 5, 2 has met 3, and 4 has met 5; see (a) below.

```cpp
   2---3           2---3            2---3
    \              |\  |            |\ /|
1    \     -->  1  | \ |    -->  1  | X |
      \            |  \|            |/ \|
   4---5           4---5            4---5
    (a)             (b)              (c)
```
In the first tea time, cow 2 meets cow 4, and cow 3 meets cow 5; see (b) above. In the second tea time, cow 3 meets cow 4; see (c) above.


N(1 <= N <= 1000)头奶牛，编号为1..N，在参加一个喝茶时间活动。在喝茶时间活动开始之前，已经有M(1 <= M <= 2,000)对奶牛彼此认识（是朋友）。第i对彼此认识的奶牛通过两个不相同的整数Ai和Bi给定(1<= Ai <= N; 1 <= Bi <= N)。输入数据保证一对奶牛不会出现多次。 在喝茶时间活动中，如果奶牛i和奶牛j有一个相同的朋友奶牛k，那么他们会在某次的喝茶活动中去认识对方（成为朋友），从而扩大他们的社交圈。 请判断，在喝茶活动举办很久以后（直到没有新的奶牛彼此认识），Q(1 <= Q <= 100)对奶牛是否已经彼此认识。询问j包含一对不同的奶牛编号Xj和Yj(1 <= Xj <= N; 1 <= Yj <= N)。 例如，假设共有1..5头奶牛，我们知道2号认识5号，2号认识3号，而且4号认识5号；如下图(a)。

```cpp
   2---3           2---3            2---3
    \              |\  |            |\ /|
1    \     -->  1  | \ |    -->  1  | X |
      \            |  \|            |/ \|
   4---5           4---5            4---5
    (a)             (b)              (c)
```
在某次的喝茶活动中，2号认识4号，3号认识5号；如上图(b)所示。接下来的喝茶活动中，3号认识4号，如上图(c)所示。


## 说明/提示

感谢@蒟蒻orz神犇 提供翻译。


## 样例 #1

### 输入

```
5 3 3 
2 5 
2 3 
4 5 
2 3 
3 5 
1 5 
```

### 输出

```
Y 
Y 
N 
```

# 题解

## 作者：jingyangzhi (赞：6)

## 标准的并查集模板，趁题目刚出水一篇c++题解，
### 类似题目：P3367 【模板】并查集；
### [并查集详解链接]（初学请务必先理解）(https://blog.csdn.net/qq_34594236/article/details/51834882)
## 好以下是AC代码：
```
#include <iostream>

using namespace std;
int f[1009];
int n,m,q;
int fin(int k){
if(f[k]==k)return k;
return f[k]=fin(f[k]);
}//标准的并查集函数，f[n]表示n的老大是谁
int main()
{    cin>>n>>m>>q;
    int b,l;
    for(register int i=1;i<=n;i++){
        f[i]=i;//初始化，让每个牛的刚开始只认识自己，即自己是自己的老大；
    }
    for(register int i=1;i<=m;i++){
        cin>>b>>l;
        f[fin(b)]=fin(l);使ai的老大是bi
    }
    for(register int i=1;i<=q;i++){
        cin>>b>>l;
        if(fin(b)==fin(l)){
            cout<<'Y'<<endl;
        }else{
        cout<<'N'<<endl;
        }\\判断俩牛是否认识，即是否为同一老大；
      然后因为是输入进文本中的，不用存储直接输出就行了；
    }

    return 0;
}

```
## 萌新求过~~！！


---

## 作者：ZJMZJM (赞：3)

蒟蒻的题解

这其实枚举可以过

只需三重for循环
```
#include<bits/stdc++.h>
using namespace std;
int a[2005],b[101];
bool f[2005][2005];//记录奶牛是否认识
int main()
{
	ios::sync_with_stdio(false);//其实也没什么用
	int n,m,q,t=1;
	cin>>n>>m>>q;//输入
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		f[x][y]=1;//初始化关系
		f[y][x]=1;//注意：是双向边
	}
	for(int i=1;i<=n;i++)//第一重循环，枚举第一只奶牛
	{
		for(int j=1;j<=n;j++)//第二重循环，枚举第二只奶牛
		{
			if(f[i][j]==1)//如果两只奶牛是朋友
			{
				for(int k=j+1;k<=n;k++)//枚举第三只奶牛
				{
					if(f[i][k]==1)//如果符合题意
						f[j][k]=1,f[k][j]=1;//建立关系
				}
			}
		}
	}
	for(int i=1;i<=q;i++)
	{
		int x,y;
		cin>>x>>y;
		if(f[x][y]==1)//判断
			cout<<"Y"<<endl;
		else
			cout<<"N"<<endl;
	}
    return 0;
}
```
请勿抄袭

---

## 作者：cryozwq (赞：2)

一道很好的并查集入门题。

题解区 dalao 们并查集都讲得不是特别详细（对于我这种蒟蒻来说），所以这篇题解
是写给没学过并查集或刚学并查集的萌新看的，dalao 们自动忽略。

为了让大家更好的理解并查集，不被抽象的概念吓倒，我们先看题目。

### 题目分析

给出 $M$ 对朋友关系，并且朋友的朋友就是朋友，要我们回答任意两头牛是不是朋友。

### 算法介绍

首先，我们把朋友论资排辈，这样每对朋友之间都有了个大哥。我们用数组 $pre[i]$ 记录第 $i$ 头牛的大哥是谁，当然一开始每头牛的大哥是自己，所以我们得到了初始化代码：
~~~cpp
for(i=1;i<=n;i++)
pre[i]=i;
~~~
现在，有两头牛相遇了，他们互相看不顺眼，想打一架。但是打架之前要先确认是不是一个集体的，怎么确认呢？他们找到了自己的大哥，问：“你认识他吗？”，他的大哥表示不认识，于是他的大哥又去找他自己的大哥：“你认识他吗？”，最后他们分别找到了终极大哥，发现这是同一头牛，两牛便握手言和，一起喝茶，成为了朋友。

细心的人已经发现一个问题：“这样每次找来找去不很麻烦吗？”，所以在寻找终极大哥的过程中，把所有问过的牛的大哥都变为终极大哥，这样每次找就很容易了。

（~~这真是我编过最 SB 的故事~~）

上面这个故事，蕴含了并查集的两个操作：找根和查询以及路径压缩

首先我们来看找根，这个过程是递归的，所以我们使用递归，代码如下：
~~~cpp
int sreach(int k){
    if(pre[k]==k)//如果这头牛的大哥就是自己，那他就是终极大哥
	return k;
    return pre[k]=sreach(pre[k]);//不然就找他的大哥，顺手把他的大哥设为终极大哥（即路径压缩）
}
~~~
然后是查询 $x$ 号牛与 $y$ 号牛是否是朋友，即他们的终极大哥是否相同。
~~~cpp
cin>>x>>y;
if(sreach(y)==sreach(x))//如果两个人的终极大哥一样
cout<<'Y'<<endl;
else
cout<<'N'<<endl;
~~~
下面只剩下如何让两头牛交朋友，即合并操作了，我们还是用一个~~无比尴尬的~~故事来看。

刚才那两头牛成为了朋友，但是他俩成了朋友，他们的朋友（大哥）也得成为朋友，怎么办呢？最简单粗暴的办法是把一边的终极大哥变为另一个终极大哥的小弟，这样就成为了一个集体，但变成小弟的那头牛不高兴啊：“凭什么我是小弟？”，那行，你俩打一架吧！秉着“自古对波左边输”的信念，左边的果然输了，成了小弟。

以下就是 $x$ 和 $y$ 号牛交朋友的代码：
~~~cpp
cin>>x>>y;
pre[sreach(x)]=sreach(y);
~~~
怎么样？并查集是不是非常简单？学会了这些，这道题便可以秒切了!
### 完整代码(无注释)
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int i,n,m,q,pre[10010];
int sreach(int k){
    if(pre[k]==k)
	return k;
    return pre[k]=sreach(pre[k]);
}
int main()
{
	int x,y;
    cin>>n>>m>>q;
    for(i=1;i<=n;i++)
    pre[i]=i;
    for(i=1;i<=m;i++){
        cin>>x>>y;
        pre[sreach(x)]=sreach(y);
    }
     for(i=1;i<=q;i++){
        cin>>x>>y;
        if(sreach(y)==sreach(x))
        cout<<'Y'<<endl;
        else
        cout<<'N'<<endl;
    }
    return 0;
}
~~~

---

## 作者：封禁用户 (赞：1)

由于我们萌新不会什么并查集(虽然用并查集更简单)假设我们只会图算法，那么这道题其实再求奶牛A到奶牛B是否连通,我们可以用DFS算法来解决问题。

算法如下:
M轮建边，使用邻接表存储
Q轮询问,使用DFS算法

下面是AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;//图结点最大个数
vector<int> G[maxn];//邻接表大法
int vis[maxn];
bool dfs(int cowa,int cowb){
    if(cowa == cowb){
        return true;
    }
    vis[cowa] = 1;
    for(int i = 0;i < G[cowa].size();i++){
        if(vis[G[cowa][i]]==0){
            if(dfs(G[cowa][i],cowb))return true;
        }
    }
    
    return false;
}
int main(){
    int n,m,q;
    cin >> n >> m >> q;
    for(int i = 1;i <=m;i++){
        int u,v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        //建无向图
    }
    for(int i = 1;i <=q;i++){//q轮调用dfs
        int a,b;//a b 两头奶牛
        cin >> a >> b;
        if(dfs(a,b)){
            cout << "Y"<<endl;
        }else{
            cout << "N"<<endl;
        }
        memset(vis,0,sizeof(vis));//标记清零
    }
}
```


---

## 作者：lshhhhhh (赞：1)

/\*
**这题其实就是并查集，如果写过1551亲戚的话，这题其实几乎完全一样，如果没写过的话，写完这题的可以去看看那题。方法：初始将各个点的父亲节点定位自己，把连在一起的点的父亲节点定为其中一个点，如果这两个点已经有父亲节点的话，每次在寻找它们的父亲节点，并将其中一个的父亲节点的父亲节点定为另一个点的父亲节点，并在搜索过程中不断压缩数的高度**

举个例子5的父亲节点为1，1的父亲节点为2,3的父亲节点为4,3和4有关系的话，将2的父亲节点变为3,5的父亲节点变为2

附上伪代码

\*/
```cpp
using namespace std; 
int n,m,p;
int p1,p2,fa[5005],t,k,a1,b;
int getfa(int x)
{
    if(x==fa[x])return x;
    k=getfa(fa[x]);
    fa[x]=k;return k;
}
int main()
{
    cin>>n>>m>>p;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int m1,m2,k1,k2;
        cin>>m1>>m2;
        k1=getfa(m1);
        k2=getfa(m2);
        fa[k2]=k1;
    }
    for(int i=1;i<=p;i++)
    {
        cin>>p1>>p2;
        a1=getfa(p1),b=getfa(p2);
        if(a1==b)cout<<"Y";
        else cout<<"N";
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：Dr_殇 (赞：0)

#楼下的叫什么并查集的算法好高深啊，然而我只会穷举。

#题目分析

我们可以先画一个表，这样能看的更清楚。

对于输入输出样例1，1表示是朋友，0表示不是

1 2 3 4 5 6                                  1 2 3 4 5 6

1 0 0 0 0 0 0                               1 0 0 0 0 0 0

2 0 0 1 0 1 0                               2 0 0 1 1 1 0

3 0 1 0 0 0 0              --->          3 0 1 0 0 1 0

4 0 0 0 0 1 0                               4 0 1 0 0 1 0

5 0 1 0 1 0 0                               5 0 1 1 1 0 0

6 0 0 0 0 0 0                               6 0 0 0 0 0 0

可见，只要模拟每一行，判断每一行中有几个朋友关系，如果是i,j和i,k都是朋友关系，那么j,k也就是朋友关系。

所以再加一个优化，其时间复杂度也不会超时。

##代码如下：




```cpp
//--新阶梯工作室防伪水印--
//--By新阶梯工作室 闪现--
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备
#define in freopen (".in","r",stdin)
#define out freopen (".out","w",stdout)
#define INF 2147483647
#define UNINF -2147483648ll
#define ch char
#define bo bool
#define ui unsigned int
#define ll long long//闪现为了少打几个字符，弄了好多好多宏定义
using namespace std;
int n,m,q;
bo fri[1005][1005];//fri数组用于存储朋友关系（话说friend为毛是个关键字啊）
inline void work();
int main(){
    //in;out;
    work();
    return 0;
}
inline void work(){
    scanf ("%d %d %d",&n,&m,&q);
    for (int i=1,x,y;i<=m;i++){
        scanf ("%d %d",&x,&y);
        fri[x][y]=fri[y][x]=1;//将这两个人的朋友关系存下来
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            if (fri[i][j]){//如果i,j是朋友关系
                for (int k=j+1;k<=n;k++){//从j+1开始搜，因为前面已经搜过，再搜一遍时间就会增多，所以为了避免超时，不要作死
                    if (fri[i][k])fri[j][k]=fri[k][j]=1;//如果i,k也是朋友关系，那么j,k就是朋友关系
                }
            }
        }
    }
    for (int i=1,x,y;i<=q;i++){
        scanf ("%d %d",&x,&y);
        if (fri[x][y])printf ("Y\n");//如果x,y是朋友关系，就输出Y（Yes）
        else printf ("N\n");//否则输出N（No）
    }
}

```

---

## 作者：syfufo (赞：0)

```cpp
//我看到很多人都用的并查集来过这道题。
//其实这道题不需要什么数据结构，只需要将图遍历一遍，当几个点连通时将这几个点打成一个标记即可。
//对于判断是否能认识，只需要看两点的标记是否相同即可
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define MAXN 1004
vector<int> map1[MAXN];
int n,m,q;
int hx[MAXN];
void dfs(int x,int y){
    hx[x]=y;
    for(int i=0;i<map1[x].size();++i){
        if(hx[map1[x][i]]==0){
            hx[map1[x][i]]=y;
            dfs(map1[x][i],y);
        }
    }
}
void input(){
    cin>>n>>m>>q;
    int xx,yy;
    for(int i=0;i<m;++i){
       cin>>xx>>yy;
       map1[xx].push_back(yy);
       map1[yy].push_back(xx);
    }
    for(int i=1;i<=n;++i){
        if(hx[i]==0){
            dfs(i,i);
        }
    }
    int xx2,yy2;
    for(int i=0;i<q;++i){
        cin>>xx2>>yy2;
        if(hx[xx2]==hx[yy2]) cout<<"Y"<<endl;
        else cout<<"N"<<endl;
    }
}
int main(){
    input();
    return 0;
}
```

---

## 作者：fighter_OI (赞：0)

裸的并查集。每次合并认识的奶牛所在的集合。

标程：

```cpp
var n,m,q,i,a,b:longint;
    die:array[1..1000] of longint;
function zd(k:longint):longint;
begin
 if die[k]=k then exit(k);
 die[k]:=zd(die[k]);
 exit(die[k]);
end;
begin
 read(n,m,q);
 for i:=1 to n do
  die[i]:=i;
 for i:=1 to m do
  begin
   read(a,b);
   die[zd(a)]:=zd(b);
  end;
 for i:=1 to q do
  begin
   read(a,b);
   if zd(a)=zd(b) then writeln('Y')
                  else writeln('N');
  end;
end.
```

---

## 作者：Caishifeng666 (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[5002],a,b,m,n,p;
void build(int hh) {for(int i=1;i<=hh;i++) fa[i]=i;return ;}
int find(const int &x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
bool cha(const int &x,const int &y){return find(x)==find(y);}
void mer(const int &x,const int &y) {if(!cha(x,y)) fa[fa[x]]=fa[y];return ;}
int main(){
    int i;
    scanf("%d%d%d",&n,&m,&p);
    build(n);
    for (i=1;i<=m;i++)scanf("%d%d",&a,&b),
	mer(a,b);
    for (i=1;i<=p;i++){scanf("%d%d",&a,&b);if (cha(a,b)) printf("Y\n");else printf("N\n");}
    return 0;
}
```

---

## 作者：_扶笙_ (赞：0)

蒟蒻来了

发现这题AC的人好少啊，其实就是并查集啊，跟亲戚几乎一模一样，如果已经对了，你懂得，没对的话，请你去看一下那一题。

并查集，将儿子指向爸爸的位置，然后对于每一个数进行判断。

代码如下（我是P）

```cpp
var n,m,k,i,x1,y1,x,y :longint;
f:array[0..100000] of longint;//并查集
function find(x:longint):longint;//find用来寻找祖先，而不是爸爸
begin
if f[x]=x then exit(x);如果等于自己，直接返回
find:=find(f[x]);继续搜索当前指向的位置
f[x]:=find;保存最新的结果（其实是一个优化，否则要浪费更多的时间）
end;
begin
readln(n,m,k);{读入}
for i:=1 to n do f[i]:=i;一开始每一个人都指向自己
for i:=1 to m do
  begin
  read(x,y);//读入
  x1:=find(x);y1:=find(y);//x1寻找x的祖先，y1寻找y的祖先
  if x1<>y1 then f[y1]:=x1;//祖先不一样就保存
  end;
for i:=1 to k do
  begin
  readln(x,y);//读入
  {if find(x)=find(y) then writeln('Y')
  else writeln('N');}如果x和y祖先一样，那么Y，否则N
  end;
end.
```
消耗了我10分钟时间，希望成功。
大神勿喷


---

## 作者：ljc20020730 (赞：0)

这和并查集的模板题一样

分析：

算法一：构造数据结构为图，用一个n\*n的二维数组描述亲戚关系，记忆各个点之间的关系。然后，只要判断给定的两个点是否连通则可知两个元素是否有“亲戚”关系。

但要实现上述算法，我们遇到两个困难：①空间问题：需要n^2的空间，而n高达1000！②时间问题：每次判断连通性需要O(n)的处理。该算法显然不理想。

算法1.用DFS求连通分量

算法2.用floyd算法

算法3.并查集的路径压缩

路径压缩实际上是在找完根结点之后，在递归回来的时候顺便把路径上元素的父亲指针都指向根结点。

这就是说，我们在“合并5和3”的时候，不是简单地将5的父亲指向3，而是直接指向根节点1，由此我们得到了一个复杂度只是O(1)的查找算法(询问)。

```cpp
var F:array[0..5000]of integer;
   i,j,k,m,n,p:integer;
function father(x:longint):longint;
  var fy:longint;
begin
    fy:=F[x];      //寻找x的父结点
    if  fy<>x  then  fy:= father(fy);
    F[x]:=fy;     //路径压缩,把x的父节点直接改成树的根
    father:=fy;
end;
begin
 readln(n,m,p);
 for i:=1 to n do F[i]:=i;//读入数据，将节点的标记记为他自己
 for i:=1 to m do begin
  readln(j,k);
  if father(j)<>father(k) then F[father(j)]:=k;//合并集合
 end;
 for i:=1 to p do begin  //判断，查询结果
   readln(j,k);
   if father(j)=father(k) then writeln('Yes')
                            else writeln('No');
 end;
end.
```

---

