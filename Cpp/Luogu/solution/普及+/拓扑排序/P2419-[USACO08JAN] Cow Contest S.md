# [USACO08JAN] Cow Contest S

## 题目描述

$ N (1 ≤ N ≤ 100) $ cows, conveniently numbered $ 1 ~ N $ , are participating in a programming contest. As we all know, some cows code better than others. Each cow has a certain constant skill rating that is unique among the competitors.

The contest is conducted in several head-to-head rounds, each between two cows. If cow $ A $ has a greater skill level than cow $ B (1 ≤ A ≤ N; 1 ≤ B ≤ N; A ≠ B) $, then cow $ A $ will always beat cow $ B $ .

Farmer John is trying to rank the cows by skill level. Given a list the results of $ M (1 ≤ M ≤ 4,500) $ two-cow rounds, determine the number of cows whose ranks can be precisely determined from the results. It is guaranteed that the results of the rounds will not be contradictory.

FJ的 $N$（$1 \leq N \leq 100$）头奶牛们最近参加了场程序设计竞赛。在赛场上，奶牛们按 $1, 2, \cdots, N$ 依次编号。每头奶牛的编程能力不尽相同，并且没有哪两头奶牛的水平不相上下，也就是说，奶牛们的编程能力有明确的排名。 整个比赛被分成了若干轮，每一轮是两头指定编号的奶牛的对决。如果编号为 $A$ 的奶牛的编程能力强于编号为 $B$ 的奶牛 （$1 \leq A, B \leq N$，$A \neq B$)，那么她们的对决中，编号为 $A$ 的奶牛总是能胜出。 FJ 想知道奶牛们编程能力的具体排名，于是他找来了奶牛们所有 $M$（$1 \leq M \leq 4,500$）轮比赛的结果，希望你能根据这些信息，推断出尽可能多的奶牛的编程能力排名。比赛结果保证不会自相矛盾。

## 说明/提示

样例解释：

编号为 $2$ 的奶牛输给了编号为 $1, 3, 4$ 的奶牛，也就是说她的水平比这 $3$ 头奶牛都差。而编号为 $5$ 的奶牛又输在了她的手下，也就是说，她的水平比编号为 $5$ 的奶牛强一些。于是，编号为 $2$ 的奶牛的排名必然为第 $4$，编号为 $5$ 的奶牛的水平必然最差。其他 $3$ 头奶牛的排名仍无法确定。

## 样例 #1

### 输入

```
5 5
4 3
4 2
3 2
1 2
2 5```

### 输出

```
2
```

# 题解

## 作者：xun薰 (赞：146)

floyed算法

floyed不仅能求任意两点的最短路，还能求一个点能否到另一个点。

f[i][j]=f[i][j]|(f[i][k]&f[k][j])表示i能否走到j，即要么一开始i能到j,要么i能到k，k再能到j。

那么这里表示的是i能否赢j。用floyed求出每个点与个点的关系，只要这个点和其他

n-1个点的关系都确定了，就能确定他的排名。

代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,n,m,f[101][101],ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        f[a][b]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
              f[i][j]=f[i][j]|f[i][k]&f[k][j];
    for(int i=1;i<=n;i++){
        int gg=1;
        for(int j=1;j<=n;j++)
        if(i==j)continue;else 
         gg=gg&(f[i][j]|f[j][i]);
         ans+=gg;
    }
    printf("%d\n",ans);
}
```

---

## 作者：Believe_R_ (赞：45)

## ~~从“拓扑排序”过来的，但好像我做下来，一点拓扑的味都没呀…！~~

回归正题，一看到这题 $n$ 的数据最大只有$100$，不禁让人想到用 $Floyd$ 来存图。

**其实这道题就是 $Floyd$ 的一个变形。通常我们用 $Floyd$ 算法是求途中的最短路，但这里用 $Floyd$ 是判断图的连通性。**

话说这道题目，如果我们能明确确定一个点的排名，那么换句话说，我们已经明确确定这个点和其他点之间的连通关系。而这里的联通关系，我们可以用 $Floyd$ 算法来实现！

> 我们可以开一个 $f[i][j]$，表示节点 i 和节点 j 之间是明确联通的。
> 
> 那么我们枚举中间点 $k$ 时，如果 $f[i][k]$ 和 $f[k][j]$ 都是 $true$，那么 $f[i][j]$ 就是 $true$。
>
> 这样到最后二维扫描时，对于任意节点 $u$，如果其他所有节点到节点 $u$ 和从节点 $u$ 到其他所有节点的路径都是确定的，那么节点 $u$ 的排名就是确定的。
>


$P.s$： 对于以上算法的实现，我用到了下面两个运算符： && 和 $||$ ~~【位运算 & 和 $|$ 也是可以的】~~ **但是要特别注意它们的优先级，下面这张图片列举了常用的几个运算符的优先级！！！**

![](https://gss2.bdstatic.com/-fo3dSag_xI4khGkpoWK1HF6hhy/baike/c0%3Dbaike80%2C5%2C5%2C80%2C26/sign=59a3e1017d3e6709aa0d4dad5aaef458/63d9f2d3572c11df57c9a205612762d0f703c2f8.jpg)


#### 下面附上c++代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int f[200][200];
int n,m,ans=0;
inline int read()         //快读优化（其实也没快多少）
{
    int re=0, f=1; char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {re=re*10+(ch-'0'); ch=getchar();}
    return re*f;
}
int main()
{
    n=read(); m=read();
    for(int i=1;i<=m;++i)
    {
        int x=read(), y=read();
        f[x][y]=1;
    }
    for(int k=1;k<=n;++k)
      for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        f[i][j]=f[i][j] || f[i][k] && f[k][j];
    for(int i=1;i<=n;++i)
    {
        int a=1;
        //这里注意一下，至于为什么这么做，自己体会吧 ~~
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            else a=a && (f[i][j] || f[j][i]);
        }
        ans+=a;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：lixiao189 (赞：31)

看到许多大佬都用了拓补排序，本蒟蒻偏不用这么~~高级的~~算法,其实这道题目用dfs就可以过了。(ps:对本题解有疑惑的person可以向我留下评论)
### 思路：
我们先来考虑一下怎么样我们才可以确定一个牛的排名，我们如果假设赢了或间接赢了这个牛的牛数为sum_win,输了或间接输掉的牛数为sum_lose，如果要确认一个牛的排名，~~很显然~~当且仅当满足一下情况的时候才能确定一个牛的排名。
```cpp
sum_win+sum_lose==n-1
```
接下来这样的问题就转换为了如何求sum_win与sum_lose。
我们用两个图用来存这道题目中的输赢关系，其中第一个图我们用一个结点指向另一个结点表示一头牛**输给了别人**，另外一个图恰好相反。这样我们从1~n枚举结点i，从一个结点i开始dfs一遍第一个图，sum_win就是遍历到的结点数，这样也很~~完美地~~解决了间接赢了别人如何处理的问题，之后我们再遍历第二个图，累计遍历到的点，得到sum_lose
之后判断一下上面给出的条件即可得到第i个结点即牛是否满足条件
### 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e2+5;

int n,m;
int vis_win[N];
int vis_lose[N];
int sum_win,sum_lose;
vector <int> win_graph[N];
vector <int> lose_graph[N];

void add(int x,int y){ //x为胜者
	win_graph[y].push_back(x);
	lose_graph[x].push_back(y);
}

void dfs_win(int x){
	vector <int> :: iterator it;
	for(it=win_graph[x].begin();it!=win_graph[x].end();it++){
		if(vis_win[*it]==0){
			sum_win++;
			vis_win[*it]=1;
			dfs_win(*it);
		}
	}
}

void dfs_lose(int x){
	vector <int> :: iterator it;
	for(it=lose_graph[x].begin();it!=lose_graph[x].end();it++){
		if(vis_lose[*it]==0){
			sum_lose++;
			vis_lose[*it]=1;
			dfs_lose(*it);
		}
	}
}

int main(){
	
	scanf("%d%d",&n,&m);
	int temp_x,temp_y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&temp_x,&temp_y);
		add(temp_x,temp_y);
	}
	
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(vis_win,0,sizeof(vis_win));
		memset(vis_lose,0,sizeof(vis_lose));
		sum_win=0;sum_lose=0;
		dfs_win(i);
		dfs_lose(i);
		if(sum_win+sum_lose==n-1) ans++;
	}
	
	printf("%d\n",ans);
	
	return 0;
	
}
```

---

## 作者：BFSBFSBFSBFS (赞：15)

由于担心奇怪的缩进影响,发图片(不知luogu图床能上题解.?)..

```pas
program P2419;
 type
  dis=record
   n,t:longint;
  end;
 var
  a:array[0..4501,1..2] of dis;
  d,h,f:array[0..101,1..2] of longint;                                         //这里的[1..2]分别(1起)用来做正向和反向SPFA.
  b:array[0..101] of longint;
  i,j,m,n,o,p,p1,p2,p3,s,x,y:longint;
  u:boolean;
 procedure hahai(x,y,z:longint);                                               //链式前向星表示边.
  begin
   a[i,z].n:=h[x,z];
   a[i,z].t:=y;
   h[x,z]:=i;
   inc(f[y,z]);                                                                //f[y]表示有多少条边指向编号为y的点.
  end;
 procedure hahasw(var x,y:longint);                                            //排序交换.
  var
   t:longint;
  begin
   t:=x;
   x:=y;
   y:=t;
  end;
 procedure hahas(l,r:longint);                                                 //快排..
  var
   o,p,m:longint;
  begin
   o:=l;
   p:=r;
   m:=d[(l+r) div 2,1];
   repeat
    while d[o,1]<m do inc(o);
    while d[p,1]>m do dec(p);
    if o<=p then
     begin
      hahasw(d[o,1],d[p,1]);
      hahasw(d[o,2],d[p,2]);
      inc(o);
      dec(p);
     end;
   until o>p;
   if o<r then hahas(o,r);
   if l<p then hahas(l,p);
  end;                                                                         //根据每个点活动范围排序,以便之后的处理.
 begin
  readln(n,m);
  fillchar(h,sizeof(h),0);
  fillchar(f,sizeof(f),0);
  for i:=1 to m do
   begin
    readln(x,y);
    hahai(x,y,1);          
    hahai(y,x,2);                                                              //反向建立边.
   end;                                                                        //存边..
  for j:=1 to 2 do                                                             //正反1起做..
   begin
    o:=1;
    p:=0;
    a[0,j].n:=-1;
    if j=1 then s:=0;
    for i:=1 to n do
     if j=1 then d[i,j]:=0
            else d[i,j]:=s;                                                    //d[i]表示i号点在树形结构上的上下限,意思为这个点可以在d[i,1]~d[i,2]中的任意1层上面.
    for i:=1 to n do
     if h[i,3-j]=0 then
      begin
       inc(p);
       b[p]:=i;                                                                //b数组为SPFA的队列.
      end;                                                                     //用前向星特性找出入度为0的点.
    while o<=p do                                                              //最长路法求上下限.
     begin
      p1:=b[o];                                                                //指定当前的起点(p1).
      i:=h[p1,j];
      while a[i,j].n<>-1 do                                                    //遍历所有与p1相关联的边.
       begin
        p2:=a[i,j].t;                                                          //这条边的终点(p2).
        dec(f[p2,j]);                                                          //删除这条边.
        if j=1 then                                                            //正反分开考虑..
         begin
          p3:=1;
          u:=d[p1,j]+p3>d[p2,j];                                               //如果p2的上限>=p1的上限,不满足条件,加强p2的限制.
         end
               else
         begin
          p3:=-1;
          u:=d[p1,j]+p3<d[p2,j];                                               //如果p2的下限<=p1的下限,不满足条件,加强p2的限制.
         end;
        if u then d[p2,j]:=d[p1,j]+p3;                                         //满足上述变化.
        if (d[p2,j]>s) and (j=1) then s:=d[p2,j];                              //找出最大的层数(s),即确定反向的层数.
        if f[p2,j]=0 then                                                      //如果所有指向p2的边都删完了.p2就可以入队了.
         begin
          inc(p);
          b[p]:=p2;
         end;
        i:=a[i,j].n;                                                           //指向下1条边.
       end;
      inc(o);
     end;
   end;                                                                        //做完后我们得到了每个点在树上的上下限.最后的答案就是那些上限和下限相等(即d[i,1]=d[i,2].),且没有与其他点有公共区域的点.
  hahas(1,n);
  p:=0;
  d[0,1]:=-1;
  for i:=1 to n+1 do
   if (d[i,1]=d[i,2]) or (i=n+1) then                                          //找出可能是答案的点(d[i,1]=d[i,2]).
    begin
     if (d[b[p],1]<>d[i,1]) and (p<>0) or (i=n+1) then                         //i=n+1即最后再做1遍删除.
      begin
       p1:=1;
       while (d[b[p],1]=d[b[p-p1],1]) and (p-p1>0) do inc(p1);                 //p1确定连续重复的位置.
       if d[b[p],1]=d[b[p-1],1] then dec(p,p1);                                //如果有重复的删除.
      end;                                                                     //有些原先就重复的点(即d[i,1]=d[j,1],d[i,2]=d[j,2])要把他们全部删除.
     if i<>n+1 then
      begin
       inc(p);
       b[p]:=i;
      end;                                                                     //新点入列.b数组用来存储可能是答案的点.
    end;
  o:=1;
  s:=0;                                                                        //统计答案个数.
  for i:=1 to n do
   if d[i,1]<>d[i,2] then                                                      //上下限不相等的点已经不可能是答案(如果是答案,说明d[i,1]~d[i,2]在其他点上没有公共的部分,最后得出来的还是d[i,1]=d[i,2]的样子..),但可能与b数组的点有公共区域.这些b数组的点也要删掉.
    begin
     while (d[b[o],1]<d[i,1]) and (o<=p) do                                    //由于已经有序.脱离范围的点就是答案了.
      begin
       inc(s);
       inc(o);
      end;
     while (d[b[o],1]>=d[i,1]) and (d[b[o],1]<=d[i,2]) and (o<=p) do inc(o);   //有相同的区域,不计入答案.
    end;
  writeln(s+p-o+1);                                                            //最后还有p-o+1个点也要算上.
 end.
```
 ![](https://cdn.luogu.com.cn/upload/pic/5737.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/5738.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/5739.png) 

补充说明..

····其实所谓的SPFA就是拓扑了..形式上有点像而已...

····此题解额外的求出了每头牛的可能的位置..作为延伸吧..

(ಡωಡ).


---

## 作者：cxm1024 (赞：12)

## 一种不是拓扑排序也不是Floyd的玄学算法
### 目的
就拿样例来说吧：

[![Uh1R2D.md.png](https://s1.ax1x.com/2020/07/20/Uh1R2D.md.png)](https://imgchr.com/i/Uh1R2D)

我们其实可以从图中获得更多信息，比如1比5厉害等，所以我们希望它能把我们所有的已知信息都表现出来，像这样：

[![Uh1Wxe.png](https://s1.ax1x.com/2020/07/20/Uh1Wxe.png)](https://imgchr.com/i/Uh1Wxe)

然后就可以方便地做判断了：哪个点的入度和出度之和 $=n-1$ ，哪个点就可以确定排名。
在实际应用中，我们为了方便，再把每个点都和自己连一条边（反正不用任何图论算法，连了也没关系），就可以直接判断哪个点的入度和出度之和 $=n$ 了。
### 具体方法
先用矩阵存图，1指向2就把第一行第二列变成1，以此类推，得到：

![截屏2020-07-19 下午1.18.00.png](https://s1.ax1x.com/2020/11/05/BWPlf1.png)

然后要变成第二张图的样子（把所有已知信息表示出来），具体步骤：
**如果$(x,y)$点有标记，$(y,z)$点也有标记，那么$(x,z)$点就可以打标记。**

为什么呢？因为$(x,y)$点有标记表示$x$比$y$厉害，$(y,z)$点有标记表示$y$比$z$厉害，$x$比$y$厉害，$y$比$z$厉害，$x$就比$z$厉害，所以$(x,z)$点就可以打标记。

最后，要如何判断点i能否和每个点都连边呢？其实很简单：**只需要把第i行和第i列上的点都加起来，再减去1（点$(i,i)$被计算了两次），看是否为n就行。**

为什么呢？因为第$i$行的标记表示$i$比别“人”厉害，第$i$列的标记表示别“人”比$i$厉害，知道几个“人”比$i$厉害，几个“人”比$i$蒻，就可以知道i的排名了。
### 算法比较难理解，有耐心的话可以仔细画画想想。
------------
### 附上AC代码：
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast")
#pragma GCC optimize("inline")
using namespace std;
bool a[110][110];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		a[x][y]=1;
	}
	for(int i=1;i<=n;i++)
		a[i][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j])
			{
				for(int k=1;k<=n;k++)
					if(k!=i&&a[k][i])
						a[k][j]=1;
				for(int k=1;k<=n;k++)
					if(k!=j&&a[j][k])
						a[i][k]=1;
			}
	int num=0;
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		for(int j=1;j<=n;j++)
		{
			ans+=a[i][j];
			ans+=a[j][i];
		}
		if(ans-1==n)
			num++;
	}
	cout<<num<<endl;
	return 0;
}
```

---

## 作者：yjxyjx (赞：10)

现在在努力肝作业。。~~感觉没什么好说的（因为我是借鉴楼下思路的）~~

代码：（至于思路都在代码里说了，看的时候请自备草稿纸）

```

/* 
    主要思路：
    我们要明确：能确定排名的人 其实就相当于：入度 + 出度 = N - 1
    可以先琢磨一下这个式子，（其实也不算太难），（先想上几分钟再往下看）

    提示一下：我们的边是从胜利者指向失败者。。

    好了公布答案：入度 => 这头奶牛被打败了(注意“被”字)， 出度 => 这头奶牛打败了其它奶牛
                 N - 1 => 除了这只奶牛之外的其它奶牛；
    （其实这个思路我也是从楼下的题解中看(chao)的）

    程序流程：

    先跑Floyd，（跑Floyd可以明确所有点之间的关系（即使是间接到达的））

    然后再统计每个点的入、出度，查每个点，假设符合上面说的式子，ans++

    最后，cout << ans;

 */



#include<iostream>
#include<algorithm>


const int oo = 0x3f3f3f3f;
const int MaxN = 100 + 30;

/* dist：第一维：起点；第二维：终点
   haveGame[i]：奶牛i的入、出度的总和
    N:有N头奶牛 => （结）点
   M:有M轮比赛 => （有向）边
 */
 
int N, M, dist[MaxN][MaxN], haveGame[MaxN], ans = 0;

void Floyd() {
    for (int k = 1; k <= N; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                dist[i][j] =std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}/* 跑floyd */


void Init() {
    for (int i = 0; i <= N + 10; ++i) {
        for (int j = 0; j <= N + 10; ++j) {
            (i != j) ? dist[i][j] = oo : dist[i][j] = 0;
        }
    }
}/* 跑Floyd的初始工作 */

void debug1() {
    for (int i = 0; i <= N + 3; ++i) {
        for (int j = 0; j <= N + 3; ++j) {
            std::cerr << dist[i][j] << "   ";
        }
        std::cerr << "\n";
    }
    std::cerr << "\n\n\n\n";
}

void debug2() {
    for (int i = 0; i <= N + 3; ++i) std::cerr << haveGame[i] << "  ";
    std::cerr << "\n\n";
}

int main() {
    std::cin >> N >> M;

    Init();

    for (int i = 1; i <= M; ++i) {
        int x, y;
        std::cin >> x >> y;
        dist[x][y] = 1;
    }

    Floyd();

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            /* 判断的时候一定要注意要大于0 */
            if ((dist[i][j] != oo) && (dist[i][j] > 0)) {
                haveGame[i]++;
                haveGame[j]++;
            }
        }
    }

    for (int i = 0; i <= N; ++i) {
        if (haveGame[i] == N - 1) ans++;
    }
    std::cout << ans;

    return 0;
}

```

---

## 作者：Starria的脑残粉 (赞：9)

正向反向dfs罢了，对每个点都搜出他能到达的所有点（大概是比floyd的复杂度优的吧

懒得挂边表所以用邻接矩阵

于是n^3

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,a[200][200],ans;
bool flag[200];
int dfs1(int d){//正向
        int ans=1;flag[d]=true;
        for (int i=1;i<=n;i++)
            if (a[d][i]&&!flag[i])ans+=dfs1(i);//计数
        return ans;
    }
int dfs2(int d){//反向
        int ans=1;flag[d]=true;
        for (int i=1;i<=n;i++)
            if (a[i][d]&&!flag[i])ans+=dfs2(i);
        return ans;
    }
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;for (int i=1;i<=m;i++)cin>>x>>y,a[x][y]=1;
    for (int i=1;i<=n;i++){
        memset(flag,false,sizeof(flag));
        if (dfs1(i)+dfs2(i)-1==n)ans++;//比当前数大的和比当前数小的加起来=n时可以确定当前的排名
    }
    cout<<ans<<endl;//输出统计出的个数
}
```

---

## 作者：karma (赞：8)

看了楼下的九篇题解,发现与我的方法都不同.于是决定发个题解.


### 总结楼下算法

- 建立正反图,分别对每个点进行一遍dfs,记录经过节点的个数.如果个数==n+1 ans++;

- 使用Floyd.f[i][j]表示可以确定i与j的关系,如果某点与其他点的f[i][j]都可以知道,那么这个点满足条件.可以使用位运算优化.

- 一个写的极其长的题解(表示看不懂)

- 拓扑排序+并查集

### 我的方法

- 拓扑排序+暴力枚举


将每个点作为拓扑排序的起点,即进行n次拓扑排序.得到n种拓扑序列.比较每个点在每次拓扑排序中的位置,如果该点满足在n种拓扑序列中位置不变,则ans++;


```cpp
#include<cstdio>
#include<cstring>
#define maxn 105
int head[maxn],cnt,N,M,topo[maxn][maxn],t,vis[maxn],ans;
//topo[i]存第i次拓扑排序的结果 
struct node{
    int next,to;
}edge[4505];
void add(int u,int v){edge[cnt].next=head[u],edge[cnt].to=v,head[u]=cnt++;}
//链式前向星存图 
void dfs(int now,int ran){//参数解释:now为当前节点,ran为第几次拓扑排序 
    vis[now]=1;//标记访问 
    for(int i=head[now];~i;i=edge[i].next){
        if(vis[edge[i].to]==0)dfs(edge[i].to,ran);
    }//访问所有未访问过的子节点 
    topo[ran][t--]=now;//记录拓扑排序结果 
}
int main(){
    memset(head,-1,sizeof(head));//我的链式前向星的head[]从-1开始
    //所以for()中的终止条件为 ~i 
    scanf("%d %d",&N,&M);
    t=N;
    ans=N;//满足条件的点最多有N个 
    for(int i=1,t1,t2;i<=M;++i){
        scanf("%d %d",&t1,&t2);
        add(t1,t2);
    }//建图 
    for(int i=1;i<=N;++i){
        memset(vis,0,sizeof(vis));//每次清空vis 
        t=N; 
        for(int j=i;j<=i+N-1;++j)
        if(vis[(j-1+N)%N+1]==0)dfs((j-1+N)%N+1,i); 
    }
    for(int i=1;i<=N;++i)
    for(int j=1;j<N;++j){
        if(topo[j][i]!=topo[j+1][i]){ans--;break;}
    }//如果在某两次拓扑序列中相同位置的值不同,则该点不能确定 
    printf("%d",ans);
    return 0;
} 
```

---

## 作者：zengxr (赞：7)

# 思路：
floyed算法的变化，用floyed算法判图的连通性。
用f[i][j]判断从i到j联不联通。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[101][101],ans;
void read(int &x) {
    char ch; bool ok;
    for(ok=0,ch=getchar(); !isdigit(ch); ch=getchar()) if(ch=='-') ok=1;
    for(x=0; isdigit(ch); x=x*10+ch-'0',ch=getchar()); if(ok) x=-x;
}
int main(){
    read(n),read(m);
    int x,y;
    for(int i=1;i<=m;i++)
    {
        read(x),read(y);
        f[x][y]=1;//输入时将f[x][y]赋值为真
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
              f[i][j]=f[i][j]||f[i][k]&&f[k][j];//核心，意思要么是f[i][j]中间本来就联通，或者从i到k并且从k到j都联通，如果两种情况都不是，就不连通
    for(int i=1;i<=n;i++)
    {
        int sum=1;
        for(int j=1;j<=n;j++)
            if(i==j)
                continue;
            else 
                sum=sum&&(f[i][j]||f[j][i]);
        ans+=sum;
    }//统计答案
    printf("%d\n",ans);//输出
}
```



---

## 作者：于丰林 (赞：6)

题目大意：有若干个数（各不相同），给出若干个大小关系，问有多少个数大小关系确定？

ｎ＜＝１００　ｍ＜＝４５００

真是一道好题啊。。。

直接说思路吧，这道题利用了图的思想：

我们把ａ大于ｂ看作从ａ向ｂ连一条有向边，那么两个数如果大小关系确定的话就代表两点是联通的，那么我们就可以利用floyd的思想：

如果ｉ能到ｊ，只有两种可能：从ｉ到ｊ有一条边或从ｉ经过ｋ到达ｊ。

所以这道题就做完了，最后能确定关系的数的条件就是他与其他的ｎ－１个点都联通。

最后，附上本题代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;
//Debug Yufenglin
#define dej printf("Running\n");
#define dep1(x) cout<<#x<<"="<<x<<endl;
#define dep2(x,y) cout<<#x<<"="<<x<<' '<<#y<<"="<<y<<endl;
#define dep3(x,y,z) cout<<#x<<"="<<x<<' '<<#y<<"="<<y<<' '<<#z<<"="<<z<<endl;

//Standfor Yufenglin
#define LL long long
#define LB long double
#define reg register
#define il inline
#define maxn 100
#define maxm 1005

int n,m,cnt,ans;
int f[maxn+5][maxn+5];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        f[x][y]=1;
    }
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                f[i][j]=f[i][j]|(f[i][k]&f[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        cnt=0;
        for(int j=1;j<=n;j++)
        {
            if(f[i][j]==1||f[j][i]==1) cnt++;
        }
        if(cnt==n-1) ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：cyborg (赞：5)

这道题的思路很简单，假如说a赢b，b赢c，那么a就能赢c，如果用拓扑排序的话，从能赢的点到输的点有一条有向边，那么对于当前点now，如果说能到now的点输给了i，那么now也会输给i。
那么怎么判断now能否赢i这个点呢？用now能到达的点去于i判断，但是这时候now能到的点还不确定，所以就要再建一个栈，按拓扑排序的顺序放进去，然后从下往上判断，就能得到一个点能否赢另一个点了。
```c
#include<cstdio>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int map[101][101],n,m,in[101],zhan[101],answer,get[101][101],zh[101];
bool jud[101][101];
int main()
{
	freopen("test.cpp","r",stdin);
    int a,b;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        if(jud[a][b])continue;
        map[a][++map[a][0]]=b;//map[a][b]表示a能赢b
        in[b]++;
        get[b][++get[b][0]]=a;
        jud[a][b]=true;
    }
    for(int i=1;i<=n;i++)
    {
        if(in[i]==0)
        {
            zhan[++zhan[0]]=i;
        }
    }
    while(zhan[0]!=0)
    {
        int now=zhan[zhan[0]];zhan[0]--;zh[++zh[0]]=now;//cout<<now<<endl;
        for(int i=1;i<=map[now][0];i++)
        {
            in[map[now][i]]--;
            if(in[map[now][i]]==0)
            {
                zhan[++zhan[0]]=map[now][i];
            }
        }
        for(int i=1;i<=n;i++)
        {
        	int t=1;
        	while(!jud[i][now]&&t<=get[now][0])
        	{
        		jud[i][now]=jud[i][get[now][t]];//如果get[now][t]输给了i，那么now也会输，因为get[now][t]能够赢now
        		t++;
        	}
        }
    }
    for(int i=1;i<=zh[0];i++)
    {
    	int now=zh[i];
    	for(int i=1;i<=n;i++)
    	{
    		int t=1;
    		while(!jud[now][i]&&t<=map[now][0])
    		{
    			jud[now][i]=jud[map[now][t]][i];//道理同上
    			t++;
    		}
    	}
    }
    for(int i=1;i<=n;i++)
    {
    	int t;
    	for(t=1;t<=n;t++)
    	{
    		if(!jud[i][t]&&!jud[t][i]&&i!=t)break;
    	}
    	if(t==n+1)
    	answer++;
    }
    cout<<answer;
}
```

---

## 作者：狛枝凪斗 (赞：4)

折腾了个纯暴力做法出来

感谢@宇興 大佬帮我修正了这个思路

因为数据n比较小，所以利用集合思想纯循环过了

应该还是有可以优化的地方，不过既然过了就没有太纠结了

思路：

就像上面说的一样，利用集合。

开四个数组s,b,sm,bg，

s[i][j]记录比i小的所有j值，即若j比i小，s[i][j]=1

b[i][j]同理，不过j比i大

sm[i]是数据中比i小的个数

bg[i]则是比i大的个数

m次询问，每一次读入aa，bb后，因aa>bb，


令sm[aa]++,bg[bb]++,s[aa][bb]=1,b[bb][aa]=1.

接下来考虑维护集合

所有比aa大的，一定也比bb大，扫一遍n更新b[bb]数组

同理，维护s[aa]数组

过程中同时还要考虑，扫到的这个数j的b和s也可以更新

最后退出m循环后，担心是否有没能更新到的数【这里就体现我的懒了…不愿多想】，所以再次全扫一遍更新所有能更新的【时间上天但能过】

那么具体来看代码吧，风格比较丑，写得很麻烦…
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
int sm[101],bg[101];
int s[101][101],b[101][101];
int main()
{
    int ans=0;
    scanf("%d%d",&n,&m);
    for(int i=1,aa,bb;i<=m;i++){
        scanf("%d%d",&aa,&bb);
        if(!s[aa][bb]){
            sm[aa]++;
        	s[aa][bb]=1;
        }
        if(!b[bb][aa]){
            bg[bb]++;
    		b[bb][aa]=1;
        }
        for(int j=1;j<=n;j++){
            if(b[aa][j]&&!b[bb][j]){
                bg[bb]++;
                b[bb][j]=1;
                if(!s[j][bb]){
                    sm[j]++;
                    s[j][bb]=1;
                }
                if(!s[j][aa]){
                    sm[j]++;
                    s[j][aa]=1;
                }
            }
        }
        for(int j=1;j<=n;j++){
            if(s[bb][j]&&!s[aa][j]){
                sm[aa]++;
                s[aa][j]=1;
                if(!b[j][aa]){
                    bg[j]++;
                    b[j][aa]=1;
                }
                if(!b[j][bb]){
                    bg[j]++;
                    b[j][bb]=1;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++){
    		if(b[i][j]){
    			for(int k=1;k<=n;k++){
                    if(b[j][k]&&!b[i][k]){
                        bg[i]++;
                        b[i][k]=1;
                        if(!s[k][i]){
                            sm[k]++;
                            s[k][i]=1;
                        }
                        if(!s[k][j]){
                            sm[k]++;
                            s[k][j]=1;
                        }
                    }
                }
                for(int k=1;k<=n;k++){
                    if(s[i][k]&&!s[j][k]){
                        sm[j]++;
                        s[j][k]=1;
                        if(!b[k][j]){
                            bg[k]++;
                            b[k][j]=1;
                        }
                        if(!b[k][i]){
                            bg[k]++;
                            b[k][i]=1;
                        }
                    }
                }
			}
		}
	}
    for(int i=1;i<=n;i++){
        if(bg[i]+sm[i]==n-1){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
```

虽然的确是很麻烦，也有更好的做法，但是这样想过以后感觉还是有好处的

---

## 作者：1saunoya (赞：4)

>[更好的阅读体验](https://www.cnblogs.com/qf-breeze/p/10473684.html)

>这题是一个Floyd 刚开始以为是~~拓扑排序~~\
>然后的话 ~~点开标签~~\
>发现是一道Floyd的水题\
>海星 反正我accepted了
关于Floyd 一直是这一段
```cpp
inline void Floyd(){
	for(register int k=1;k<=n;k++)
		for(register int i=1;i<=n;i++)
			for(register int j=1;j<=n;j++) dis[i][j]=dis[i][j]|dis[i][k]&dis[k][j];
}
```
>当然这个是传递闭包的题目\
>挺不错的吧\
>代码
>
```cpp
#include <bits/stdc++.h>
#define Min(a,b) a<b?a:b
using namespace std;
typedef long long LL;
inline LL read () { LL res = 0 ;int f (1) ;char ch = getchar ();
	while (!isdigit(ch)) { if (ch == '-') f = -1 ;ch = getchar();}
	while (isdigit(ch)) res = (res << 1) + (res << 3) + (ch ^ 48) ,ch = getchar(); return res * f ;
}
int n,m;
int dis[500+5][500+5];
const LL Inf=0x3f3f3f3fLL;
inline void Floyd(){
	for(register int k=1;k<=n;k++)
		for(register int i=1;i<=n;i++)
			for(register int j=1;j<=n;j++) dis[i][j]=dis[i][j]|dis[i][k]&dis[k][j];
}
signed main () {
	n=read(),m=read();
	for(register int i=1;i<=m;i++) {
		int u=read(),v=read();
		dis[u][v]=1;
	}
	Floyd();
	LL ans=0;
	for(register int i=1;i<=n;i++){
        LL p=1;
        for(register int j=1;j<=n;j++){
        	if(i==j) continue;
			else p=p&(dis[i][j]|dis[j][i]);
		}
		ans+=p;
    }
	cout << ans << endl ;
	return 0;
}

```


---

## 作者：jamespaul (赞：4)

做俩遍dfs。题目要求能确定位置的cow数，可以建一个正图一个反图，分别对每个点在正图和反图各做一次dfs，并记录经过了多少个结点，如果结点数等于n+1，则说明这个cow的排名可以确定。


---

## 作者：HPXXZYY (赞：3)

[题目传送门](https://www.luogu.org/problemnew/show/P2419)

这道题很明显有传递性（即a赢b，b赢c，则a赢c，相反，a输b，b输c，则a输c）

我们设两个bool型二维数组w和l，其中w[i][j]==true表示i赢j，即i的实力比j强，l[i][j]==true表示i输j，即i的实力比j弱，一边输入，可以一边初始化w和l

**输入代码：**
```cpp
n=read();m=read();
for(i=1;i<=m;i++){
    a=read();b=read();
    w[a][b]=true;l[b][a]=true;
}
```
其中read()为读入优化（**听说**每500万个数据可省100毫秒）

**读入优化代码（需要调用cctype库）：**
```cpp
#define g(c) isdigit(c)
#define gc getchar()
int read(){
    char c=0;int x=0,f=0;
    while (!g(c)) f|=c=='-',c=gc;
    while (g(c)) x=x*10+c-48,c=gc;
    return f?-x:x;
}
```

然后，我们对w和l数组**分别**进行一次**floyd算法**（n不大，O(n^3)能过）

**floyd算法代码：**
```cpp
void floyd(bool f[N][N]){
    //注意不能写成floyd(bool f[][])，会CE(编译错误)
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    if (i!=k)
    for(int j=1;j<=n;j++)
    if (j!=i&&j!=k)
    f[i][j]=f[i][j]||(f[i][k]&&f[k][j]);
}
//因为floyd算法要进行两遍且两遍代码几乎一样
//所以我们可以把floyd算法定义为一个函数，而非直接打两遍几乎一样的代码
int main(){
    读入+预处理
    floyd(w);floyd(l);
}
```

最后，我们对于**每个**i（1<=i<=n），枚举j（1<=j<=n且i!=j），若w[i][j]==true**或**l[i][j]==true，我们把计算器s++,若s==n-1则答案（ans）++，输出ans程序结束

因为w[i][j]==true时，l[i][j]**肯定**等于false（即**不可能**i赢j，j倒回来又赢i），同理l[i][j]==true时，w[i][j]**肯定**等于false，所以**不会**出现少算或多算

实际测试中w[i][i]和l[i][i]肯定等于false，所以i和j不必判断是否相等

```cpp
for(i=1;i<=n;i++){
    for(j=1,s=0;j<=n;j++)
    if (w[i][j]) s++;
    for(j=1;j<=n;j++)
    if (l[i][j]) s++;
    if (s==n-1) ans++;
}
printf("%d",ans);
```
[评测记录：](https://www.luogu.org/recordnew/show/16155068)

状态/分数：Accepted，100分

耗时/内存：76ms，800KB

语言/长度：C++，0.83KB

**完整代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=105;
bool w[N][N],l[N][N];
int n,m,a,b,i,j,s,ans;
#define g(c) isdigit(c)
#define gc getchar()
int read(){
    char c=0;int x=0,f=0;
    while (!g(c)) f|=c=='-',c=gc;
    while (g(c)) x=x*10+c-48,c=gc;
    return f?-x:x;
}
void floyd(bool f[N][N]){
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    if (i!=k)
    for(int j=1;j<=n;j++)
    if (j!=i&&j!=k)
    f[i][j]=f[i][j]||(f[i][k]&&f[k][j]);
}
int main(){
//	freopen("t2.in","r",stdin);
    n=read();m=read();
    for(i=1;i<=m;i++){
        a=read();b=read();
        w[a][b]=true;l[b][a]=true;
    }
    //读入+预处理
    floyd(w);floyd(l);
    //floyd算法
    for(i=1;i<=n;i++){
        for(j=1,s=0;j<=n;j++)
        if (w[i][j]) s++;
        for(j=1;j<=n;j++)
        if (l[i][j]) s++;
        if (s==n-1) ans++;
    }
    //计算结果
    printf("%d",ans);
    return 0;
}
```

最后，说一下万能头bits/stdc++.h

noi比赛文件中说：**理论上**可以用万能头，但实际中可能不支持使用万能头，若因为使用万能头而导致CE（编译错误），比赛**概不负责**，即**选手负全责**！！！

所以，比赛时建议**不要**使用万能头，平时可以稍微使用一下

---

## 作者：善良的死神 (赞：3)

看了楼下的10篇题解,发现与我的方法都不同.于是决定发个题解.

用到了楼下的floyed思路

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,map[1000][1000];
int ans=0,num=0;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        map[x][y]=1,map[y][x]=-1;定关系
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    for(int k=1;k<=n;k++)k起传递作用
        {                
            if(map[i][j]==0)没关系，就给他关系
            {
                if(map[i][k]==1&&map[k][j]==1)i打的过k，k打的过j
                    map[i][j]=1,map[j][i]=-1;传递
                else if(map[i][k]==-1&&map[k][j]==-1)
                map[i][j]=-1,map[j][i]=1;                
            }
        }
for(int i=1;i<=n;i++)
{
    num=0;计数器，能打的过的人
for(int j=1;j<=n;j++)
{
if(map[i][j]==0&&i!=j)谁都打不过我，领唱：无敌是多么寂寞
num++;
}
if(num==0)无敌了
ans++;
}
cout<<ans<<endl;
return 0;
}
减少代码复制，共创美好洛谷，这就是我不打"//"的原因，并不是我lazy
```

---

## 作者：L_J_Y (赞：3)

用弗洛伊德算法。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[101][101],s[101],ans,x,y;
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
       for (int j=1;j<=n;j++) a[i][j]=10001;//初始化
    for (int i=1;i<=m;i++) {
        scanf("%d%d",&x,&y);
        a[x][y]=1;  //，把连着的边边权赋值为1
    }
    for (int k=1;k<=n;k++)
      for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
           a[i][j]=min(a[i][j],a[i][k]+a[k][j]);    //核心代码
    for (int i=1;i<=n;i++) 
      for (int j=1;j<=n;j++)
        if (a[i][j]<10001) {
            s[i]++;s[j]++;    //判断是否连着，连着的边加1
        }      
    for (int i=1;i<=n;i++)
       if (s[i]==n-1) ans++;  //每找到一条连着其他全部点的边，答案加1
       printf("%d",ans);    
}
```

---

## 作者：塔罗兰 (赞：3)

机房又考试了，在另一个dalaoAK的时候，本蒟蒻在洛谷A考试中的水题……这题不是拓扑排序吗？

仔细一看，这题表面上是拓扑排序，其实应该用Floyd，然后本蒟蒻果断用了~~大法师~~DFS

样例的图:

![样例](https://cdn.luogu.com.cn/upload/pic/60622.png)

于是我们可以发现这题的一个规律：

### 当且仅当一头牛外的所有牛都必弱于或必强于该牛时,该牛的排名是确定的

翻译成人话就是:

#### 一个节点向上搜到的节点数+向下搜到的节点数==n-1时符合题目要求

这就是为什么本蒟蒻果断用了~~大法师~~DFS的原因

因为题目保证了没有环，所以直接爆搜就可以了
```cpp
#include<bits/stdc++.h>//万能头
#define MAX 4505
#define MIN 105
using namespace std;
int v[MIN],n,m,a[MAX][2],sum;
inline int up(int x)
{
	int upsum(0);
	for(register int k(1);k<=m;k+=1)
	if(a[k][1]==x&&v[a[k][0]]==0)
	v[a[k][0]]=1,upsum+=1+up(a[k][0]);//记录遍历过的节点
	return upsum;
}//向上爆搜
inline int down(int x)
{
	int downsum(0);
	for(register int k(1);k<=m;k+=1)
	if(a[k][0]==x&&v[a[k][1]]==0)
	v[a[k][1]]=1,downsum+=1+down(a[k][1]);//记录遍历过的节点
	return downsum;
}//向下爆搜
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i(1);i<=m;i+=1)
	scanf("%d%d",&a[i][0],&a[i][1]);//输入
	for(register int i(1);i<=n;i+=1)
	{
		memset(v,0,sizeof(v));//v记录是否遍历到了该节点,防止重复计算(如样例的节点4)
		if(up(i)+down(i)==n-1)//套规律
		sum+=1;//记录总数
	}
	printf("%d",sum);
}
```
由于~~大法师~~DFS迷一样的时间复杂度(最坏情况为O(n!))于是本蒟蒻卡了卡常

1.定义循环变量时加register,加register可以加快变量值的改变(大约十几倍),建议用在循环变量上，但是要注意用register定义的变量不能太多，不然会变慢。

2.inline可以加快函数的调用,~~大法师~~DFS这种函数前面建议加一下，不过在主函数前加inline会CE

然鹅好像没有必要的样子……

声明:本题解只是说明了一种简单~~到我这样的蒟蒻都能写出来的~~A题方法,更优的算法请详见其他巨佬们的Floyd

---

## 作者：code_magician (赞：2)

/// 注释全在代码中
```cpp
#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 101;

int rank_[maxn];
int win[maxn][maxn]; /// win[a][b] a > b时 是继续加深
int lose[maxn][maxn]; /// lose[a][b] a < b时 继续加深
int visit[maxn]; /// 访问标记

int n, m;

void dfs(int u, int rute[][maxn], int now){
    visit[u] = 1;
    for(int i = 1; i <= n; ++i){
        if(!visit[i] && rute[u][i]){ /// 当数组是win[u][i] 时， 当 u > i时继续往下搜，就能够搜出全部败给了u的人数
            rank_[now]++;           /// 当数组是lose[u][i] 时， 当 u < i时继续往下搜，就能够搜出全部赢了 u 的所有人数
            dfs(i, rute, now);      /// 当 u失败的人数 + u赢过的人数 +  1 (本身的) = n的时候，u的排名就是可知的
        }
    }
}

void solve(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        win[a][b] = true; /// a是胜利的一方 b是失败的一方
        lose[b][a] = true; /// b是失败的一方，a是胜利的一方
    }
    for(int i = 1; i <= n; ++i){
        memset(visit, 0, sizeof(visit));
        rank_[i]++; /// 加上本身 1
        dfs(i, win, i); /// 能够得出 i 这只牛赢了的牛的数目
        dfs(i, lose, i); /// 能够得出 i 这只牛败给其他牛的数目
    }
    int res = 0;
    for(int i = 1; i <= n; ++i){
        if(rank_[i] == n) res++; /// 如果rank_[i] == n 的时候，这只牛的排名是可知的，res++;
    }
    cout << res;
}

int main(){
    solve();
    return 0;
}

```


---

## 作者：EricPaul (赞：2)

弗洛伊德算法，只要该点与其他所有点相连即可确定名次。

c++代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int start,ending,ans[120],amount,dp[120][120],n,m;
signed main(){
    cin>>n>>m;
    for(int i=0;i<120;i++){
        for(int j=0;j<120;j++){
             dp[i][j]=99999;
            }
        }
    for(register int i=1;i<=m;i++){
        cin>>start>>ending;
        dp[start][ending]=1;
        }
    for(register int k=1;k<=n;k++){
        for(register int i=1;i<=n;i++){
            for(register int j=1;j<=n;j++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
                }
            }
        }
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=n;j++){
            if(dp[i][j]<99999) {ans[i]++;
            ans[j]++;}
        }
        }
    for(register int i=1;i<=n;i++){
        if(ans[i]==n-1) amount++;
        }
    cout<<amount;
    return 0;
}
```

---

## 作者：Create_Random (赞：1)

题意：

给定$n$个点，求问有几个点与其它点都有关系(打败或被打败)

蒟蒻思路：

用$floyd$求出$i$点与$j$点是否有关系

($dis[i][j]$表示$i$能打败$j$)

最后$n^2$枚举点$i$是否与其他点全部有关系即可

贴代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int dis[110][110];
int a[110];
bool flag;
int ans;
int main()
{
	memset(dis,0x3f,sizeof(dis));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		dis[u][v]=1;//有向图！
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);//使得i与j有关系
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i!=j)
			{
				if(dis[j][i]!=0x3f3f3f3f||dis[i][j]!=0x3f3f3f3f)//如果与所有点都有关系就ans++
				{
					flag=1;
				}
				else
				{
					flag=0;
					break;
				}
			}
		}
		if(flag)
		{
			ans++;
		}
		flag=0;//别忘了清空！
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：最喜欢saber了 (赞：1)

这道题我刚开始做是用的dfs，但我不太会写，所以没写出来，然后我就换了个思路，用并查集，但是还有个问题，我无法表示是出一个点的父亲是其他所有点，所以我又失败了，最后，我看了一眼标签，我看到了他————Floyed，咦，弗洛伊德？，然后我想了一会儿，想出了一个朴素做法：先定义$f[i][j]$表示每个点之间的关系，再初始化其为一个极大值，再将有胜负关系的奶牛$f[a][b]=1$,然后跑一遍Floyed，这样我们在将$f[a][b]<inf$的点记录一下，最后再扫一遍，如果这个点积累的次数等于n-1，说明这个点与其他所有的点的关系都确定了，那么他就是合法的，ans++。最后输出，于是就结束了，但这样的做法无疑是$O(n^3)$，在本题的数据范围下还是可以跑过的，数据再大一点可能就不行了，但通过本题还是绰绰有余的，我看题解好像没有这种做法，求管理员通过。

```cpp
#include<algorithm>
#include<cstring>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<cctype>
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &x){
    x=0;T f=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
    for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
    x*=f;
}
const int maxa = 110,inf = 0x7f;
int n,m,f[maxa][maxa],sum[maxa],ans=0,a,b;
int main(){
    read(n);read(m);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            f[i][j]=inf;
        }
    }
    /*for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            read(f[i][j]);
        }
    }*/
    for(int i=1;i<=m;++i){
        read(a);read(b);
        f[a][b]=1;
    }
    for(int k=1;k<=n;++k){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(i!=j&&j!=k&&k!=i){
                    f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
                }
            }
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(f[i][j]<inf){
                sum[i]++;
                sum[j]++;
            }
        }
    }
    for(int i=1;i<=n;++i){
        if(sum[i]==n-1)ans++;
    }
    printf("%d",ans);
    return 0;
}
```

谢谢观看 请记住 我太弱了

---

## 作者：Minclxc (赞：1)

弗洛伊德算法，位运算优化

g[i][j]=1表示i胜过j（直接或间接）

具有传导性g[i][j]=g[i][k]&g[k][j]|g[i][j]如果i胜过k并且k胜过j则i胜过j，

如果一个点或其他所有点都有明确的胜负关系，就可以确定排名

即g[i][j]|g[j][i]("|"是c的or)
代码如下，现在应该是内存最小，0ms

```cpp
#include<cstdio>
using namespace std;
#define fo(a,b,c) for(int a=b;a<=c;a++)
#define go(a,b,c) for(int a=b;a>=c;a--)
int read(){
    int a=0,f=0;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')f=1;
    for(;c>='0'&&c<='9';c=getchar())a=a*10+c-'0';
    return f?-a:a;
}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int g[101][101];
int main(){
    int n=read(),m=read(),ans=0;
    fo(i,1,m)g[read()][read()]=1;
    fo(k,1,n)fo(i,1,n)fo(j,1,n)
        g[i][j]=g[i][k]&g[k][j]|g[i][j];//弗洛伊德
    fo(i,1,n){
        int f=1;
        fo(j,1,n)if(i-j)f&=g[i][j]|g[j][i];//如果都为0则不计入答案
        ans+=f;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：PaRz1VaL (赞：1)

萌新刚学Floyd ~~本来打算练一下拓扑结果惊奇的发现是Floyd题~~

借鉴了**Believe_R_大佬**的Floyd思路，从萌新的角度来补充一些萌新可能一下子理解不了的细节

思路大致是通过Floyd来更新图中每两个点的连通情况，从而判断图的连通性

然后遍历图的每一个结点，判断这个结点与其他结点能否连通，如果可以的话则这头牛的排名可以确定，如果与任何一个点不连通也就是无法确定这两头牛谁厉害，则这头牛的排名不能被确认

这里用到两个位运算符&和|

&是按位与运算，当且仅当两个数都为1时答案位1

|是按位或运算，当且仅当两个数都为0时答案为0

其他细节都在代码里了
```cpp
#include<cstdio>

int n, m, ans;
int edge[105][105];            //最多有100个点，所以可以用邻接矩阵

void inp(){

    scanf("%d %d",&n,&m);
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d %d",&x,&y);
        edge[x][y] = 1;        //标记i到j可以连通
    }
}

int main(){

    inp();

    for(int k = 1; k <= n; k++)             //Floyd
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(!edge[i][j])             //两个点不直接连通的话，判断两个点能不能通过其他点连通
                    edge[i][j] = (edge[i][k] & edge[k][j]);
    
    for(int i = 1; i <= n; i++)
    {
        int x = 1;                               //x用于标记是否出现过与结点i不连通的点
        for(int j = 1; j <= n; j++)
            if(j != i && x)
                x = x&(edge[i][j]|edge[j][i]);   //判断两个点是否连通
        ans += x;                                //更新答案
    }

    printf("%d",ans);

    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

这道题使用Floyd算法，找奶牛和奶牛之间的关系，从而推断出一个奶牛和另一个奶牛的关系。

具体代码如下：

```delphi

var
  a:array[1..100,1..100] of integer;
  x,y,n,m,i,j,k,ans,s:longint;
begin
  readln(n,m);
  for i:=1 to m do
  begin
    readln(x,y);
    a[x,y]:=1;
    a[y,x]:=-1;
  end;
  for k:=1 to n do                                        //Floyd算法
    for i:=1 to n do
      for j:=1 to n do
        if (a[i,k]=1)and(a[k,j]=1)then
        begin
          a[i,j]:=1;
          a[j,i]:=-1;
        end;

  for i:=1 to n do
  begin
    s:=0;
    for j:=1 to n do
      if a[i,j]=0 then
        inc(s);
    if s=1 then
      inc(ans);
  end;
  writeln(ans);
end.

```

---

## 作者：fanfansann (赞：0)

这个说明就讲的很清楚
**说明/提示
输出说明:
编号为2的奶牛输给了编号为1、3、4的奶牛，也就是说她的水平比这3头奶
牛都差。而编号为5的奶牛又输在了她的手下，也就是说，她的水平比编号为5的
奶牛强一些。于是，编号为2的奶牛的排名必然为第4，编号为5的奶牛的水平必
然最差。其他3头奶牛的排名仍无法确定。**

## 所以我们直接用Floyd传递闭包

根据题意既是如果i能赢k，k能赢j，那么i能赢j。说明关系可传递，使用Floyd传递闭包。`f[i][j] = 1`表示i能胜j。（如果i能赢k，j也能赢k，那么i和j的胜负不定，就没办法确定最终排名了。）因此如果一头牛能与剩下n-1头都能确定胜负关系，那么就能确定它的排名。
我们用`f[x][y]`表示`x`可以赢`y`,这样只有i能赢k，k能赢j，才能确定i能赢j，也就是`f[i][j] = 1`。

然后就是传递闭包的模板了 ~~优美的位运算~~

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
int f[N][N];
int ans;

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        f[x][y] = 1;
    }
    for(int k = 1;k <= n;++k)
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                f[i][j] |= f[i][k] & f[k][j];
    for(int i = 1;i <= n;++i){
        int now = 1;
        for(int j = 1;j <= n;++j)
            if(i != j)
                now &= f[i][j] | f[j][i];
        ans += now;
    }
    cout<<ans<<endl;
    return 0;
}

```

---

