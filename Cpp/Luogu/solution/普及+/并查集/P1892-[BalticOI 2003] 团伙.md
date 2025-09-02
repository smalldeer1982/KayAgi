# [BalticOI 2003] 团伙

## 题目描述

现在有 $n$ 个人，他们之间有两种关系：朋友和敌人。我们知道：

- 一个人的朋友的朋友是朋友
- 一个人的敌人的敌人是朋友

现在要对这些人进行组团。两个人在一个团体内当且仅当这两个人是朋友。请求出这些人中最多可能有的团体数。

## 说明/提示

对于 $100\%$ 的数据，$2 \le n \le 1000$，$1 \le m \le 5000$，$1 \le p,q \le n$。

## 样例 #1

### 输入

```
6
4
E 1 4
F 3 5
F 4 6
E 1 2```

### 输出

```
3```

# 题解

## 作者：x义x (赞：519)

萌新刚AC了本题，谈下心得吧~

以下代码






```cpp
#include<iostream>
#include<string>
using namespace std;
int n,m,f[1001],enm[1001];  //f存放节点的父亲，enm存放每个人的敌人 
int find(int x)            //寻找x的祖先 
{
    while(f[x]!=x) x=f[x]; //不断更新寻找祖先
    return x;
}
void hebing(int x,int y)    //中文看得懂吧 
{
    x=find(x);y=find(y);  //无判定超简单合并_(:з」∠)_照顾一下和我一样的萌新
    if(x==y) return;
    f[y]=x;
    return;
}
int main()
{
     cin>>n>>m;
     for(int i=1;i<=n;i++)
        f[i]=i;
    for(int i=1;i<=m;i++)
    {
        int p,q;
        char c;
        cin>>c>>p>>q;
        if(c=='F') hebing(p,q);  //是朋友就合并 
        else {
                if(enm[p]==0) enm[p]=find(q);
              else hebing(q,enm[p]);  //一个人有两个或更多敌人，合并他们 
              if(enm[q]==0) enm[q]=find(p);
              else hebing(p,enm[q]);
            } 
    }
    int count[1001]={0};
    for(int i=1;i<=n;i++)
        count[find(i)]++;
    int cnt=0;
    for(int i=1;i<=n;i++)
        if(count[i]) cnt++; //统计，做得不是很简洁 
    cout<<cnt;
 } 
```
首先，要充分理解题目。
“敌人的敌人就是朋友”可以这么理解：如果一个人有两个或更多敌人，这些敌人就应该被合并。

代码中的enm数组就是记录了每个人的第一个敌人，再遇到敌人时就把这两个敌人合并。

没想出这点的话还是蛮难做的。

路径优化什么的，咳咳，都说是萌新了。


另外致萌新：如果错了一定优先检查循环条件\_(:з」∠)\_本人调了一小时才发现是某循环条件的“==”打成“=”了……以前学pascal的后遗症啊


至于代码注释不够清晰等问题欢迎提出~

讲得可能比那些高估咱萌新实力的大牛们稍微易懂点吧，人生中第一个题解，希望能过⁄(⁄ ⁄•⁄ω⁄•⁄ ⁄)⁄


---

## 作者：铃宕 (赞：259)

## ** 并查集+反集**

### 1.  关于并查集
 
 如果你连并查集都不会[请移步模板](https://www.luogu.org/problemnew/show/P3367)
 
### 2.  关于反集
 
 我也是做这道题才知道的
 
 如果a和b是敌人，合并n+b和a，n+a和b
 
 如果c和a是敌人，合并n+c和a，n+a和c
 
 那么b和c就并在一起了
 
 这样就符合了题目敌人的敌人是朋友的规则
 
```
#include<bits/stdc++.h>
using namespace std;
int s,n,m,a,b,f[2500];
char ch;
int find(int x){
    if(f[x]!=x)f[x]=find(f[x]);//查找+路径压缩，如果没有祖先就回溯
    return f[x];
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=2*n;i++){
        f[i]=i;//初始化，千万不能漏
    }
    for(int i=1;i<=m;i++){
        cin>>ch>>a>>b;
        if(ch=='F'){
            f[find(a)]=find(b);//合并
        }else{
            f[find(a+n)]=find(b);
            f[find(b+n)]=find(a);//反集合并
        }
    }
    for(int i=1;i<=n;i++){
        if(f[i]==i)s++;
    }
    cout<<s;//祖先数就是团伙数
}
```

---

## 作者：Ajwallet (赞：64)

看到各位dalao们的题解，只想说666.

当我做完食物链的时候，发现这两题本质是一样的，而且这题的难度还要低过食物链，只需要简单的查找合并操作就行了。

a表示a的朋友（这个容易吧。。。）

a+n表示a的敌人（这个也不难）

如果是朋友，合并a和b。

如果是敌人，合并a+n和b，b+n和a(a的敌人是b，b的敌人是a)

代码
```cpp
#include<bits/stdc++.h>
#define r(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int f[2002],n,m,a,b,ans;char c;
bool tong[1001];
struct BCJ{/*并查集，自己弄得几个函数，dalao勿喷。。。*/
    void start(int x)//初始化
    {r(i,1,x) f[i]=i;}
    int find(int x)//查找
    {return x==f[x]?x:f[x]=find(f[x]);}
    void judge(int a,int b)//合并
    {f[find(a)]=find(b);}
    bool too(int a,int b)//判断两个元素是否在同一集合
    {return find(a)==find(b);}
}acs;
int main()
{
    cin>>n;
    acs.start(n*2);//初始化
    cin>>m;
    r(i,1,m)
    {
        cin>>c>>a>>b;
        if(c=='E')//敌对关系
         {
             acs.judge(b+n,a);//合并
             acs.judge(a+n,b);//合并
         }
        else
             acs.judge(a,b);//合并
    }
    r(i,1,n)
     {if(f[i]==i)ans++;}//求一共有几种
    cout<<ans;
}
```

---

## 作者：Wings (赞：50)

# 题面
### Description
Chicago in the 1920s: a battlefield of gangsters.

 _二十世纪二十年代的芝加哥：黑帮的战争。_ 

If two gangsters have ever met each other, then they have become either true friends or mortal enemies. The gangsters live --- and die --- by the following code of ethics:

 _如果两个黑帮成员**曾经**见过，那么他们就**已经**成为了朋友或者敌人。黑帮成员们从始至终遵从下面的准则：_ 

1. A friend of my friend is also my friend.
2. An enemy of my enemy is my friend.


1.  _我朋友的朋友也是我的朋友_ 。
2.  _我敌人的敌人也是我的朋友_ 。

Two gangsters are in the same gang if and only if they are friends.

 _两个成员属于同一个黑帮当且仅他们是朋友。_ 

Poor you are employed by the Chicago Police Department. You must calculate the maximal possible number of different gangs in Chicago based on what the Department knows about the relations between the individual gangsters.

 _可怜的你在芝加哥警局工作。你必须依据警局**已知**的两个成员之间的关系计算芝加哥最多可能有多少个黑帮。_ 

### Input data

The first line of the input file GANGS.IN gives the number$N (2 ≤ N ≤ 1 000)$of known gangsters. The gangsters are numbered from 1 to N. The second line gives the number$M (1 ≤ M ≤ 5 000)$of known facts about these gangsters.

 _第一行一个数字$N (2 ≤ N ≤ 1 000)$表示黑帮成员数量。他们从1到N编号。第二行一个数字$M (1 ≤ M ≤ 5 000)$表示这些成员之间**已知**的关系_ 

The following M lines list the facts, each fact on its own line. Each fact is of the form $F\ p\ q$ or $E\ p\ q$, where$1 ≤ p < q ≤ N$ are the two gangsters in question. (Each of the three components is separated by a space.) If the first letter is $F$, the line says that $p$ and $q$ are known friends. If it is $E$, then they are known enemies.

 _接下来M行给出这些关系，每个关系一行。关系用$F\ p\ q$或$E\ p\ q$表示$(1 ≤ p < q ≤ N)$。$F\ p\ q$表示$p$和$q$是**已知**的朋友$E\ p\ q$表示$p$和$q$是**已知**的敌人。_ 

It can be assumed that the input is consistent --- two gangsters cannot be both friends and enemies of each other.

 _数据保证两个成员不可能同时是敌人和朋友。_ 

### Output data

The first and only line of the output file GANGS.OUT must contain the maximal possible number of gangs.

 _仅一行，输出最多可能有多少个黑帮。_ 

### Sample

#### GANGS.IN
```
6
4
E 1 4
F 3 5
F 4 6
E 1 2
```
#### GANGS.OUT
```
3
```
### Remark

The 3 gangs in the example above are {1}, {2, 4, 6}, and {3, 5}.

 _样例的三个黑帮为{1}, {2, 4, 6}, 和 {3, 5}。_ 

###### 上面翻译里的黑体是洛谷翻译没有注意到的细节。

# 头脑风暴
洛谷上的[翻译](https://www.luogu.org/problemnew/show/P1892)有误，导致想了好久好久，怎么想都是带权并査集，可就是40分(我还丧心病狂地证明了，[见这里](https://www.luogu.org/discuss/show?postid=54737))。两个人之间其实是可以没有关系的：可以曾经没有遇见，或者警局不知道他们的关系。而洛谷上翻译说得像所有人都有关系。所以这里给出原题和自己的傻瓜式翻译(这样就不会理解错题意了)。

# 正确解法
并査集，不用带权。Friend合并，Enemy记录，再把下一个Enemy和记录的Enemy合并。因为敌人的敌人是朋友。比如
$E\ 1\ 2,\ E\ 2\ 3$
记录E[1] = 2, E[2] = 1，现在到了E 2 3， E[2]有了，那么把1,3合并，然后记录E[3] = 2。由于敌人的敌人已经合并，那么这时的1或者3都是2的敌人，取一个代表就行，下次再碰到2和某个人是敌人，把他和1合并或把它和3合并是一样的。连通块在合并的时候统计就可以了。

# 方法挖掘

(抽象的讲不清楚，只可意会不可言传)

1. 对于两个人之间的关系，**可以不存在关系，记录下不能合并的关系，再次找到时合并可以合并的人**。
2. 对于两个人之间的关系，**一定存在关系，用带权并査集**。

# 算法实现
```
#include <cstdio>

const int maxn = 1e3+10;

int n, m;
int fa[maxn], enemy[maxn], ssc = 0;

void Init() {
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    ssc = n;
}

int Find(int x) {
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Union(int x, int y) {
    if (Find(x) != Find(y)) {
        ssc--;
        fa[Find(x)] = Find(y);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    Init();
    while (m--) {
        char o[10];
        int x, y;
        scanf("%s%d%d", o, &x, &y);
        if (o[0] == 'F')
            Union(x, y);
        else {
            //int fx = Find(x), fy = Find(y);
            if(enemy[y])
                Union(x, enemy[y]);
            else 
                enemy[y] = x;
            if (enemy[x])
                Union(y, enemy[x]);
            else
                enemy[x] = y;
        }
    }
    printf("%d", ssc);
    return 0;
}
```

我 @ 了管理员说翻译有误，管理员不理我╥﹏╥...

---

## 作者：zzzyc (赞：39)

并查集。。。。。。。。。。。。。。。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int fa[1010]; //记录团伙头目。。。（感觉这个强盗是家族产业，毕竟是father） 
bool fight[1010][1010]; //仇敌关系的说,打架。。。 
int find(int x) //寻找根节点。 
{
    if (fa[x]!=x) fa[x]=find(fa[x]); //路径压缩
    return fa[x];
}
void unionn(int x,int y) //合并x和y所在集合
{
    int f1=find(x);
    int f2=find(y);
    if (f1!=f2) fa[f2]=f1;
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        fa[i]=i; //预处理并查集。 
    for(int asdf=1;asdf<=m;asdf++) //asdf纯属丧心病狂。。。 
    {
        char h;
        int a,b;
        cin>>h>>a>>b;
        if (h=='F') unionn(a,b); //如果是朋友直接合并
        else //否则是敌人  
        {
            fight[a][b]=fight[b][a]=true; //仇敌关系
            for (int i=1;i<=n;i++) //检查所有强盗，因为很菜不会套路，本以为要GG的。 
            {
                if (fight[a][i]) unionn(b,i); //a和k是敌人，又因为a和b是敌人，所以b和k是朋友 
                if (fight[b][i]) unionn(a,i); //同上
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(fa[i]==i)
            ans++; //统计团伙个数（也就是树根）
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：LSG_waterf (赞：11)

这题很简单，我们可以定义一个二位数组，用b[i][j]时表示i，j两人的关系：b[i][j]=1时为敌人，反之，相信大家并查集的模板都会了，直接上代码，相信大家一下就能看懂。
下面市本题代码，因为数据比较小，这种简单的思路是很好理解的：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,f[100010],b[1010][1010],ans=0;
char c;
int find(int x)
{
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
void lsy(int fa,int fb)//lsy为本人年轻的教练名字
{
	fa=find(fa); fb=find(fb);
	f[fb]=fa;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;//一开始的预处理每个人是自己的爸爸
	for(int i=1;i<=m;i++)
	{
		cin>>c>>x>>y;
		if(c=='F') lsy(x,y);//合并x和y
		if(c=='E')
		{
			b[x][y]=b[y][x]=1;
			for(int j=1;j<=n;j++)//一到n枚举
			{
				if(b[x][j]==1) lsy(y,j);
				if(b[y][j]==1) lsy(x,j);
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(f[i]==i) ans++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：安笙凉城 (赞：11)

#并查集 并查集 并查集（重要的事情说三遍QAQ）


#本蒟蒻的思路是**如果这两个人是盆友，那么直接合并，即一个人成为另一个人的爸爸（随便认爹）**

#**如果这两个人是敌人，用一个结构体把每个人的敌人存起来，然后循环找队友，继续认爹**

#**最后只要看有多少人的爹是自己，就有多少对团伙**


#上代码（虽然没爆，但跑得慢，费空间大）







```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,pre[50005],sum,ans;//pre存父亲
struct node//结构体存敌人
{
    int p,q;
}team[50005];
int find(int x)//递归找最老的父亲
{
    if(x==pre[x])
      return x;
    return find(pre[x]);
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
      pre[i]=i;//一开始每个人的爸爸是他自己
    for(int i=1;i<=m;i++)//m条信息
      {
          char o;
          int p,q;
          cin>>o>>p>>q;
          if(o=='F')//如果是朋友，随便一个人当另一个人的爸爸
            pre[find(p)]=find(q);
        if(o=='E')//如果不是就把他们存起来
          {
              team[sum].p=q;
              team[sum].q=p;
              sum++;
          }
      }
    for(int i=0;i<sum;i++)
      {
          for(int j=i+1;j<sum;j++)
            {
            if(team[i].p==team[j].p)
                  pre[find(team[i].q)]=find(team[j].q);
                if(team[i].p==team[j].q)
                  pre[find(team[i].q)]=find(team[j].p);
                if(team[i].q==team[j].p)
                  pre[find(team[i].p)]=find(team[j].q);
                if(team[i].q==team[j].q)
                  pre[find(team[i].p)]=find(team[j].p);//这一段写的有点丑，不过意思就是找敌人的敌人认爹
            }
      }
    for(int i=1;i<=n;i++)
      if(pre[i]==i)//有多少人的爸爸是自己就有多少对团伙
        ans++;
    cout<<ans<<endl;//输出答案
    return 0;
}
```

---

## 作者：谭之荔 (赞：10)

 _题目描述_ 

1920年的芝加哥，出现了一群强盗。如果两个强盗遇上了，那么他们要么是朋友，要么是敌人。而且有一点是肯定的，就是：
我朋友的朋友是我的朋友；
我敌人的敌人也是我的朋友。
两个强盗是同一团伙的条件是当且仅当他们是朋友。现在给你一些关于强盗们的信息，问你最多有多少个强盗团伙。

并查集！！！
是朋友的就放一个连通块中，其实可以不用想那个最多，直接求数目就阔以啦！

```
#include<iostream>
#include<cstdio>
using namespace std;
int father[1005],f[1005][1005];  //father即父亲结点，f数组判断是否是敌人 
int find(int x) //递归 
{
	if(father[x]!=x) father[x]=find(father[x]); //优化 
	return father[x];//如果自己不是父亲结点，那么寻找父亲结点 
}
void uni(int x,int y)//合并 
{
	int r1=find(x);
	int r2=find(y);
	if(r1!=r2)
	{
		father[r2]=r1; //使r2的父亲结点是r1; 
	}
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		father[i]=i; //初始化，即开始前，每个数都是单独存在的，即每个数的父亲结点都是自己 
	}
	for(int i=1;i<=m;i++)
	{
		char p; 
		int x,y;
		cin>>p>>x>>y;
		if(p=='F') uni(x,y);//如果是朋友就直接合并 
		else
		{
			f[x][y]=f[y][x]=1;//前面说过，f数组用来判断xy是否是敌人，为1则是
			// 注意！！无向一定要 f[x][y] f[y][x]都赋值 
			for(int i=1;i<=n;i++)//把所有人都列出来，看看是不是x或者y的敌人 
			{
				if(f[x][i]) uni(i,y);// 如果x和i是敌人，x又和y是敌人，那么i和y是朋友合并 
				if(f[y][i]) uni(i,x);//同上 
			}
		}
	}
	int ans=0;//统计数目 
	for(int i=1;i<=n;i++)
	{
		if(father[i]==i)//如果父亲结点是自己，那么就是一个团队 
		{
			ans++;
		}
	}
	cout<<ans;
}
```
ps太渣了……真的第一次发

---

## 作者：苏拉威西3号 (赞：7)

小蒟蒻第一次发题解！！！一定要给过啊

先上代码

```
#include<bits/stdc++.h>
using namespace std;
int f[1001],vis[1001];
int n,m,x,y,r1,r2,s;
char z;
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)
	{
		cin>>z>>x>>y;
		if(z=='F'){r1=find(x),r2=find(y);f[r2]=r1;}
		if(z=='E')
		{
			if(vis[x])
			{
				r1=find(y),r2=find(vis[x]),f[r2]=r1;
			}
			else vis[x]=y;
			if(vis[y])
			{
				r1=find(x),r2=find(vis[y]),f[r2]=r1;
			}
			else vis[y]=x;
		}
	}
	for(int i=1;i<=n;i++)if(f[i]==i)s++;
	cout<<s;
	return 0;
}
```
分析一下

首先读入n个数，每个数先将自己作为自己的祖先，也就是
```
for(int i=1;i<=n;i++)f[i]=i;
```
接着读入m组关系，对于每一组关系分类讨论。如果两人是朋友则将其中一人设为祖先，可以简单理解为一个团伙的头头，将以后每一个与他为朋友的人加入他的麾下。具体实现为

```
if(z=='F'){r1=find(x),r2=find(y);f[r2]=r1;}
```
如果两个人是敌人，那么判断这个人之前有过敌人吗？如果有，就将另一个人加入他敌人的阵营中，如果没有，那么另一个人就是他敌人的头头，也就是
```
if(z=='E')
		{
			if(vis[x])
			{
				r1=find(y),r2=find(vis[x]),f[r2]=r1;
			}
			else vis[x]=y;
			if(vis[y])
			{
				r1=find(x),r2=find(vis[y]),f[r2]=r1;
			}
			else vis[y]=x;
		}
```
那么如何判断祖先呢，具体见函数find，在这里给大家放一下

```
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}
```
在代码最后挨个查找每一个人，如果这个人是一个团伙的头头，团队数就加一，至于他麾下的小喽喽就不用理会了
望各位dalao指正

---

## 作者：king_xbz (赞：5)

期末考炸了，来洛谷刷题宣泄一下

一道经典的并查集，但是却和普通的并查集不太一样，这题用到反集的知识

那么我们来说说反集
```cpp
if(a=='E')
	{
	unions(b+n,c);
	unions(c+n,b);
	}
```
十分简洁，易(meng)懂(bi)，不少第一次接触的蒟蒻（像我）会发出灵魂的拷问：为啥这样合并呢？

那就让我们用模拟的方法来解决一下吧：

假设：a，b的关系是敌人：b，c的关系是敌人

那么我们将a+n和b，b+n和a合并合并，将b+n和c，c+n和b合并

那么我们find（a）就会找到b+n，find（b+n）就会找到c

这样的话通过一个中间量我们成功的将a与c建立起联系

是不是感觉有点眼熟，这种处理方法是不是和[ P2629 好消息，坏消息](https://www.luogu.com.cn/problem/P2629)有异曲同工之妙呢（当然一个是前缀和，一个是并查集，还是有本质区别的）

```cpp
for(fint i=1;i<=n*2;i++)
	f[i]=i;初始化集合，注意建立邻接表需要*2
```
```cpp
for(fint i=1;i<=m;i++)
	{
	cin>>a>>b>>c;
	if(a=='F')
	unions(b,c);
	else
	if(a=='E')
	{
	unions(b+n,c);
	unions(c+n,b);
	}
}   合并敌人或朋友关系
```
```cpp
for(fint i=1;i<=n;i++)
    if(f[i]==i)
    t++;
```  
记录团伙数

完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define fint register int
#define fread ios::sync_with_stdio
#define p 234873
#define h 2001
using namespace std;
inline void unions(int x,int y);
int findx(int x);
int f[p];
signed main()
{
	fread(false);
	int n;
	cin>>n;
	for(fint i=1;i<=n*2;i++)
	f[i]=i;
	int m;
	cin>>m;
	char a;
	int b,c;
	for(fint i=1;i<=m;i++)
	{
	cin>>a>>b>>c;
	if(a=='F')
	unions(b,c);
	else
	if(a=='E')
	{
	unions(b+n,c);
	unions(c+n,b);
	}
}
    int t=0;
    for(fint i=1;i<=n;i++)
    if(f[i]==i)
    t++;
    cout<<t;
    exit(0);
} 
inline void unions(int x,int y)
{
 	if(findx(x)!=findx(y))
 	f[findx(x)]=findx(y);
}
int findx(int x)
{
 	if(f[x]==x)
 	return x;
 	return f[x]=findx(f[x]);
}
```



---

## 作者：gaozitao1 (赞：3)

**题目大意**：有n个强盗，m个关系，分别表示两个强盗p，q是朋友还是敌人，问最多有几个强盗团伙？

这一道题基本上也是并查集的模板题。

首先是输入输出：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short N(1001);
short f[N];//记录最高的首领首领
inline short find(short v)//寻找上一个首领
{
	if(f[v]!=v)//如果上一个首领不是自己
		f[v]=find(f[v]);//就是自己的上一个首领
	return f[v];//返回自己的上一个首领
}
inline void merge(short v,short u)//合并
{
	f[find(u)]=find(v);//u的上一个首领是v
}
int main()
{
	char c;
	short a(0),i,m,n,p,q;
	scanf("%hd%hd",&n,&m);
	for(i=1; i<=n; ++i)
		f[i]=i;//初始化，一开始每个人的上一个首领都是自己
	for(i=1; i<=m; ++i)
	{
		for(c=getchar(); c!='E'&&c!='F'; c=getchar());
		//读入字符，保证c不是空格和换行，也可以改成std::cin>>c;
		scanf("%hd%hd",&p,&q);
		//处理
	}
	for(i=1; i<=n; ++i)
		f[i]=find(f[i]);//寻找自己的最大的首领
	for(i=1; i<=n; ++i)
		if(f[i]==i)
			++a;
	//如果自己的最大的首领是自己，那么就有一个团伙，一个团伙只有一个最大的首领
	printf("%hd",a);//输出
	return 0;
}
```
之后，如果两个人是朋友，容易处理：
```cpp
if(c=='F')//如果是朋友
	merge(p,q);//合并
```
但是如果是敌人，怎么办呢？

这就需要用到并查集的反集了。

可以将数组开成2倍，a和a+n是敌人，所以如果a和b是朋友，可以合并a和b，如果a和b是敌人， 就合并a和b+n，合并b和a+n，就可以处理了。
```cpp
else//如果是敌人
{
    merge(p,q+n);
    merge(q,p+n);//反集合并
}
```
完整代码：
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
const short N(2001);//N开成规定的2倍
short f[N];//记录最高的首领首领
inline short find(short v)//寻找上一个首领
{
	if(f[v]!=v)//如果上一个首领不是自己
		f[v]=find(f[v]);//就是自己的上一个首领
	return f[v];//返回自己的上一个首领
}
inline void merge(short v,short u)//合并
{
	f[find(u)]=find(v);//u的上一个首领是v
}
int main()
{
	char c;
	short a(0),i,m,n,p,q;
	scanf("%hd%hd",&n,&m);
	for(i=1; i<=2*n; ++i)
		f[i]=i;//初始化，一开始每个人的上一个首领都是自己
	for(i=1; i<=m; ++i)
	{
		for(c=getchar(); c!='E'&&c!='F'; c=getchar());
		//读入字符，保证c不是空格和换行，也可以改成std::cin>>c;
		scanf("%hd%hd",&p,&q);
		if(c=='F')//如果是朋友
			merge(p,q);//合并
        else//如果是敌人
        {
        	merge(p,q+n);
        	merge(q,p+n);//反集合并
        }
	}
	for(i=1; i<=n; ++i)
		f[i]=find(f[i]);//寻找自己的最大的首领
	for(i=1; i<=n; ++i)
		if(f[i]==i)
			++a;
	//如果自己的最大的首领是自己，那么就有一个团伙，一个团伙只有一个最大的首领
	printf("%hd",a);//输出
	return 0;
}
```

---

## 作者：Sakura_Peng (赞：3)

PS：似乎与上面大佬们的思路大致相同，但是我还是想发一下，毕竟我还是在下方的题解中手动操作了一下反集这个思想的具体体现，比较易于理解吧（蒟蒻的我光看代码看不懂=-=）

------------
这种题目当然我们应该需要用**并查集**来解决。

我们用一个集合代表一个团伙

然后如果根节点为自己就说明有一个新的集合产生，那么就说明多了一个团伙

那么我们也就只用处理以下两句话了


> 我朋友的朋友是我的朋友


这个我们只需要判断是否两个点在一个集合，在一个集合就说明几个肯定都是朋友


> 我敌人的敌人也是我的朋友


但是这里我们怎么解决呢？

我们可以使用一种新的思想叫做：反集

若某A和某B两个人

那么我们设定 

**A代表的是相对当前人是团伙 A1代表的相对当前人是敌人**

**B代表的是团伙当前人是团伙 B1代表的相对当前人是敌人**

**……**

如果

某A与某C是朋友关系

则生成集合 {A,C} 

某C与某B是敌人关系

生成集合 {B1,C} {C1,B}

某D与某B是敌人关系

生成集合{D1,B} **{C,B1,D}**

这个时候就可以找到 

C和D在一个集合里了，他们现在就是一个团伙的了

A1 B1 C1这种我们怎么表示呢？其实有很多种形式，我们可以重新定义A1 B1 C1或者直接A+N B+N C+N

~~这种反集的思想蒟蒻表示真的蛮神奇的~~ 

但是很多要注意的，这道题目的输入让我彻底知道了cin的好处，空格换行是scanf字符输入难受一批的....

另外，在合并的过程中，如果我们要合并A1 B这种情况，我们一定要把A1接到B的后面，不能把B接到A1的后面，这样会影响答案，因为如果我们最后出现以A1 B1这种的为根节点就麻烦了。

代码：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int n,m,fa[1000001],total;
int find(int x)
{
	if (fa[x]==x)
	return x;
	fa[x]=find(fa[x]);
	return fa[x];
}  //并查集路径压缩
void he(int x,int y)
{
	int x1=find(x),y1=find(y);
	if (x1!=y1)
	fa[x1]=y1;
}  //合并操作
int main()
{
	scanf("%d%d",&n,&m);
	 for (int i=1;i<=2*n;i++)
	 fa[i]=i;  //我这里使用了 A B C和A+N b+N这种形式来定义相对的朋友和敌人关系
	 for (int i=1;i<=m;i++)
	 {
	 	int x,y;
	 	char ch;
	 	cin>>ch>>x>>y;
	 	if (ch=='F')
	 		he(x,y);
		else
		{
	 he(x+n,y);
	 he(y+n,x);  //反集思想具体体现
	 }
}
	 for (int i=1;i<=n;i++)
	 if (fa[i]==i)  //有几个根节点是自己的就说明有几个子树，也就是有几个集合（团伙）
	 total++;
	 printf("%d",total);
	return 0;
 } 
```


---

## 作者：Celebrate (赞：3)

```cpp
//思路：这一题，把每个有联系的人形成一个并查集，每个并查集就只有两种可能
//第一种就是里面都是朋友（用0表示），第二种就是里面有朋友和敌人（用1表示） 
//忘记说了，洛谷的数据有点问题，比如说：
/* 
输入： 
4
3
E 2 3
F 2 1
E 1 4 
输出：
2
这题很多人都被坑到了吧，其实朋友的敌人也算敌人的 
*/
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int fa[2100],s[2100];//fa[x]表示x的父亲，s表示这个并查集里面的情况 
int find_zuxian(int xx)//找祖先 
{
    int zuxian;
    if(fa[xx]!=xx)
	{
		zuxian=find_zuxian(fa[xx]);
	}
    else zuxian=xx;
    fa[xx]=zuxian;
    return zuxian;
}
int main()
{
    int i,n,m,x,y;char ss[1];//定义，char一定要这样，不然会出现bug 
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)fa[i]=i;
    while(m--)
    {
        scanf("%s%d%d",ss,&x,&y);
        int fx=find_zuxian(x);//找x的祖先 
        int fy=find_zuxian(y);//找y的祖先 
	    if(fx!=fy)//如果他们的祖先不一样 
	    {
	       	fa[fy]=fx;//如果他们的祖先不同，那么y家族 就是x家族的了 
	        if(s[fx]==1 || s[fy]==1) s[fx]=1;//如果并查集里面分为两派，那么并查集x就改为1 
	    }
	    if(ss[0]=='E')s[fx]=1;//有敌人的默认为1 
    }
    int ans=0;
    for(int i=1;i<=n;i++)//n个并查集 
		if(fa[i]==i)//如果i就是这个家族的祖先 
			ans+=s[i]+1;//就增加s[i]+1,记得+1 
    printf("%d\n",ans);//输出
	return 0; 
}
```

---

## 作者：万物一 (赞：2)

这道题标答貌似是并查集 然而我不会写(wcsl)

~~所以蒟蒻的我决定拿图论水过去~~

首先考虑建图 很容易想到如果两人是朋友那么他们之间存在双向边

问题来了 题目说敌人的敌人就是朋友

例如有

E 2 3

E 2 4

那么显然有 4 与 3是朋友, 我们该怎样建图呢？

一个简单的想法是储存所有2的敌人 ，然后在读取完之后再讲将他们之间连接双向边

建图完毕 我们接下来只需要计算有几张连通图就行了

连通图的数量就是这题的答案

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1005;
const int maxm = 5050;

vector<int> E[maxn];
vector<int> Emy[maxn];
bool vis[maxn];

void dfs(int s) {
    vis[s] = true;
    for (auto &&next : E[s]) {
        if(!vis[next]) {
            dfs(next);
        }
    }
}

int main() {
    //加速cin cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int count = 0;
    for (int i = 1; i <= m; ++i) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        if(c == 'F') {
            //存储朋友
            E[a].push_back(b);
            E[b].push_back(a);
        } else {
            //存储敌人
            Emy[a].push_back(b);
            Emy[b].push_back(a);
        }
    }
    //将敌人连边
    for (int i = 1; i <= n; ++i) {
        int lastP = -1;
        for (auto &&p : Emy[i]) {
            if(lastP == -1) {
                lastP = p;
                continue;
            }
            E[lastP].push_back(p);
            E[p].push_back(lastP);
            lastP = p;
        }
    }
    for (int i = 1; i <= n; ++i) {
        //记得不要重复遍历 遍历过的点
        if(!vis[i]) {
            dfs(i);
            //累加答案
            ++count;
        }
    }
    cout << count << endl;
    return 0;
}

```

---

## 作者：tryrtj (赞：2)

那么多篇题解居然没有暴力算法，全是并查集。。。


并查集的大佬们大概该题总时间都在200ms以下，所以不用并查集的蒟蒻来写个暴力算法。


朋友的朋友是朋友，敌人的敌人是朋友，自然想到枚举每个人，找他的朋友，都是这个人的两个朋友标签改为朋友，敌人相同，然后就TLE了.............


即使O2挽救了高达30分，但是总共只有70分，所以就开始剪枝。


三重循环外面加一个while，很容易卡出去，所以在二重循环时加一个条件，如果前两个人是朋友或敌人，再继续，否则直接找下一个人，因为进第三重循环也没用。


然后又TLE了...........


不过拿了60分，开O2的话80分；最后再加一个条件：第三重循环的数从第二重循环开始，因为要不然k与j一定会重复一次，这样就节省了一半时间。


~~（开O2才能过哦。。。）~~


代码如下：

```
#include<iostream>
using namespace std;
int a[1005][1005];
int n,m;
bool l[1005];
void floodfill(int q){
	for(int i=1;i<=n;i++){
		if(i!=q&&a[i][q]==2){
			l[i]=1;
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){//存储状态
		char q;
		int w,e;
		cin>>q>>w>>e;
		if(q=='E'){
			a[w][e]=1;
			a[e][w]=1;
		}
		if(q=='F'){
			a[w][e]=2;
			a[e][w]=2;
		}
	}
	bool g=1;
	while(g==1){//每一次修改状态都要在来一遍
		g=0;//判断是否修改过
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(a[i][j]!=1)continue;//剪枝
				for(int k=j+1;k<=n;k++){
					if(a[i][k]==1&&a[j][k]!=2){
						a[j][k]=2;
						a[k][j]=2;
						g=1;//修改加判断
					}
				}
			}
		}
		for(int i=1;i<=n;i++){//同上
			for(int j=1;j<=n;j++){
				if(a[i][j]!=2)continue;
				for(int k=j+1;k<=n;k++){
					if(a[i][k]==2&&a[j][k]!=2){
						a[j][k]=2;
						a[k][j]=2;
						g=1;
					}
				}
			}
		}
	}
	int ge=0;//记录团伙数
	for(int i=1;i<=n;i++){
		if(l[i]==0){
			l[i]=1;
			floodfill(i);//查找所有朋友
			ge++;
		}
	}
	cout<<ge<<'\n';//输出
	return 0;
}
```


---

## 作者：康娜卡姆依 (赞：2)

其实在**并查集**中也算水题啦

楼下的几位并没有把子程序的变量名写得简单易懂，这里再稍作补充。

直接上代码——




```cpp
//pascal
var f:array[0..1000,0..1000] of boolean;  //用f[i,j]表示关系
    father:array[0..1000] of longint;
    i,k,n,m,x,y,tot:longint;
    ch:char;  // 友敌的读入变量
function find(x:longint):longint;  //查询工作，如果父亲节点并不是要查询的则把父亲当作当前位置往上搜
begin
  if father[x]<>x then father[x]:=find(father[x]);
  find:=father[x];
end;
procedure union(x,y:longint);    //将双方联盟
var r1,r2:longint;
begin
  r1:=find(x);
  r2:=find(y);
  if r1<>r2 then father[r1]:=r2;
end;
begin
  readln(n,m);
  for i:=1 to n do father[i]:=i;
  for i:=1 to m do
    begin
      readln(ch,x,y);  //读入
      if ch='F' then union(x,y)   //如果是朋友则union
      else
        begin
          f[x,y]:=true; f[y,x]:=true;
          for k:=1 to n do
             begin
               if f[x,k] then union(k,y);
               if f[k,y] then union(k,x);
             end;
        end;
    end;
  for i:=1 to n do if find(i)=i then inc(tot);
  writeln(tot); //输出
end.
```

---

## 作者：Steam (赞：2)

本题有一个难点，在于敌人的敌人也需要归入自己的朋友中去，好难的样子有木有？

但是看看数据，笑了：


用并查集来维护自己的朋友，然后就可以轻松地知道有多少个团伙了；

对于敌人，暴力维护自己的敌人是谁。

每次读入一个人的敌人，然后把敌人的敌人全部加入到自己的朋友中去


喜闻乐见的代码：

```delphi

var
  enemy:array[1..1010,0..1000]of longint;
  friend:array[1..1010]of longint;
  i,j,m,n,k,e,h,d,p,q,ans:longint;
  AC:char;

function getfather(v:longint):longint;
begin
  if friend[v]=v then exit(v);
  friend[v]:=getfather(friend[v]);
  exit(friend[v]);
end;

begin
  readln(n);
  for i:=1 to n do
    friend[i]:=i;
  readln(m);
  ans:=n;
  for i:=1 to m do
    begin
      readln(AC,p,q);
      if AC='F' then
        if getfather(p)<>getfather(q) then
          begin
            dec(ans);
            friend[getfather(p)]:=friend[getfather(q)];//把自己的朋友加入自己的团伙
          end;
      if AC='E' then
        begin
          for j:=1 to enemy[p,0] do
            if friend[getfather(q)]<>friend[getfather(enemy[p,j])] then
              begin
                friend[getfather(q)]:=friend[getfather(enemy[p,j])];
                dec(ans);
              end;//把自己的敌人的敌人加入自己的朋友中去
          for j:=1 to enemy[q,0] do
            if friend[getfather(p)]<>friend[getfather(enemy[q,j])] then
              begin
                friend[getfather(p)]:=friend[getfather(enemy[q,j])];
                dec(ans);
              end;//把自己的敌人加入到这个敌人的朋友中去
          inc(enemy[p,0]);
          enemy[p,enemy[p,0]]:=q;
          inc(enemy[q,0]);
          enemy[q,enemy[q,0]]:=p;
        end;
    end;
  writeln(ans);
  exit;
end. 

```

---

## 作者：杨铠远 (赞：2)

#### **刚学了STL  稍微用一下**# 

详情见代码
```cpp
#include<iostream>
#include<algorithm>
#include<set>//记着打 
#include<cstring>
using namespace std;
int n,m,x,y;
char p;
int f[10005];

int find(int q)
{
	if(f[q]!=q)
	return find(f[q]);
	else return q;//路径压缩 
}
int main()
{
	set<int> pp;//开一个set 
	cin>>n>>m;
	for(int i=1;i<=2*n;i++)
	{
		f[i]=i;	}//自己对应自己 
	for(int i=1;i<=m;i++)
	{
		cin>>p;
		if(p=='F')
		{
			cin>>x>>y;
			int xx=find(x);
			int yy=find(y);
			f[xx]=yy;
		}
		if(p=='E')
		{
			cin>>x>>y;
			f[find(x+n)]=find(y);
			f[find(y+n)]=find(x);//借助上上上...个大佬的补集 
		}
	}
	for(int i=1;i<=n;i++)
	{
		pp.insert(find(i));//送到set    
	}						//set中会自动去重 
	cout<<pp.size();//大小就是团伙数 
	return 0;//收场 
}
```

---

## 作者：曼恩薄荷 (赞：2)

**根据题意我们不难看出来题目中的朋友关系可以容易的用并查集处理出来，
而这道题目的难点就在于敌人关系‘E’的处理QWQ。
而“敌人的敌人是朋友”这句关键的话使我想到：可以针对每一个敌人关系，
从他的敌人所在的点出发去寻找敌人的敌人，
而把敌人的敌人直接当做朋友，进行合并处理。
在建图的过程中我又想到，可以使用STL中的vector来进行存边的处理，
简洁方便，代码如下：
    

------------
			
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 1005;

int f[maxn],n,m,ans,vis[maxn];
vector <int> g[maxn];

int Find(int x)				//寻找祖先 

    if(f[x]!=x) f[x]=Find(f[x]);
    return f[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        f[i]=i;				//并查集初始化 
    for(int i=1;i<=m;i++)
    {
        char c;
        int a,b;
        cin>>c;
        scanf("%d%d",&a,&b);
        if(c=='F')			//如果是朋友，则可以直接合并 
        {
            int fa=Find(a),fb=Find(b);
            if(fa!=fb)
                f[fa]=fb;
        }
        else				//如果是敌人： 
        {
            for(int j=0;j<g[b].size();j++)// 就从敌人的点出发，去找到敌人的敌人 
            {
                int fa=Find(a),fb=Find(g[b][j]); //即视为自己的朋友，进行合并 
                if(fa!=fb)
                    f[fb]=fa;
            }
            for(int j=0;j<g[a].size();j++)//记得从两个点都来一遍 
            {
                int fa=Find(g[a][j]),fb=Find(b);
                if(fa!=fb)
                    f[fa]=fb;
            }
            g[a].push_back(b);//将敌人关系保存下来 
            g[b].push_back(a);//记得建双向边 
        }
    }
    for(int i=1;i<=n;i++)//统计联通块个数 
    {
        int fa=Find(i);
        if(!vis[fa])
            vis[fa]=1,ans++;
    }
    cout<<ans;
}
```
	在这里我们定义了一个二维的vector数组g[maxn][],当你在使用push_back函数的时候他会把你要储存的参数自动扩展一位存在g[xx][size()]里并将size++我们调用边关系的时候就只需要从0到size调用g[a][i]里的参数就可以了，带来了许多方便。
	希望能对大家有所帮助QwQ。

---

## 作者：CSP_Sept (赞：1)

**想获得更佳的阅读体验？戳[这里](https://blog.csdn.net/fsupervisor/article/details/104116706)！**

## 题意简述

若两人是朋友则合并两人所在的并查集，若两人是敌人则合并自己与对方所有敌人所在的并查集。

## 思路

建立一个数组来存储每两个人之间的关系，`1`表示是敌人，`0`表示是朋友。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int dir[1010][1010],f[1010];
int find(int a){
    if(f[a]==a) return a;
    return f[a]=find(f[a]);
}
void jr(int a,int b){
    int t1=find(a),t2=find(b);
    if(t1!=t2) f[t1]=t2;
}
int main(){
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) f[i]=i;
	char opt;
	for(int j=0;j<m;j++){
		scanf(" %c%d%d",&opt,&x,&y);
		if(opt=='F') jr(x,y);
		else if(opt=='E'){
			dir[x][y]=1;
			dir[y][x]=1;
			for(int i=1;i<=n;i++){
				if(dir[x][i]) jr(y,i);
				if(dir[i][y]) jr(i,x);
			}
		}
	}
	int tot=0;
	for(int i=1;i<=n;i++){
		if(f[i]==i) tot++;
	}
	printf("%d",tot);
	return 0;
}
```
## 分析

$1.$ `if(opt=='F') jr(x,y);` 若两人是朋友则合并两人所在的并查集。

$2.$ 
```cpp
else if(opt=='E'){
	dir[x][y]=1;
	dir[y][x]=1;//把两人设为敌人
	for(int i=1;i<=n;i++){
        if(dir[x][i]) jr(y,i);
    	if(dir[i][y]) jr(i,x);
    }//合并自己与对方敌人的并查集
}
```
$3.$ `if(f[i]==i) tot++;` 依据:每个并查集都只有一个根

---

## 作者：一中益达 (赞：1)

是朋友就直接合并。

难点在于敌人。看很多大佬对敌人建图一个个加边表示不屑

不用管那么多。直接暴力。

每次加边遍历一次图，把朋友的朋友合并。

重点就在当发现要合并的两个人在一个集合中，直接退出搜索（想想为什么）

这样就无脑写出来了，而且还不慢，62ms
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
struct node
{
	int nxt,to;
}edge[10050];
int head[1050];
int tree[1050];
int find(int x)
{
	int origin=x;
	while(x!=tree[x]) x=tree[x];
	tree[origin]=x;
	return x;
}
int cnt;
void add(int st,int ed)
{
	edge[++cnt].to=ed;
	edge[cnt].nxt=head[st];
	head[st]=cnt;
}
char read()
{
	char ch=getchar();
	while(ch!='F'&&ch!='E') ch=getchar();
	return ch;
}
bool merge(int x,int y)
{
	if(find(x)==find(y)) return false;
	tree[find(x)]=tree[find(y)];
	return true;
}
void dfs(int t,bool E,int origin)
{
	if(!E)
	{
		if(!merge(t,origin)) return;
	}
	for(int i=head[t];i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		dfs(to,E^1,origin);
	}
}
int ans;
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		tree[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		if(read()=='F')
		{
			int x,y;
			scanf("%d %d",&x,&y);
			merge(x,y);
		}
		else
		{
			int x,y;
			scanf("%d %d",&x,&y);
			add(x,y);
			add(y,x);
			dfs(y,true,x);
			dfs(x,true,y);
		}
	}
	for(int i=1;i<=n;i++) if(tree[i]==i) ans++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：EightSixSun (赞：1)

//阅读题目一眼就能看出来这是个并查集的题
#### 这个题的结点之间的关系是：

朋友的朋友是朋友，敌人的敌人是敌人

#### 而且注意到： 
输入数据保证不会产生信息的矛盾

所以连判定矛盾都不用了，就比较简单了


那么就可以把一个团伙当做一个并查集来看，直接在读入的同时合并所有的朋友关系，存下敌人关系，读入结束之后再合并所有的敌人的敌人

最后统计有多少个集合即可，用一个t数组来标记统计过的并查集的根节点，如果没有统计过一个并查集，答案数+1并标记该并查集的根结点

我不会说一开始以为敌人的朋友是敌人，朋友的敌人是敌人，做了好久

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <map>
#define For(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
bool t[1001];//et[1001][1001],t[1001];
short int n,m,fa[1001],e[1001][5001],ecnt[1001];
int find(int x)
{
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}
void merge(int x,int y)
{
    fa[find(x)]=find(y);
}
int main()
{
    int tx,ty,ans=0;
    char temp;
    cin>>n>>m;
    For(i,1,n)
     fa[i]=i;
    For(i,1,m)
    {
        cin>>temp>>tx>>ty;
        if(temp=='E')
        {
            ecnt[tx]++;
            ecnt[ty]++;
            e[tx][ecnt[tx]]=ty;
            e[ty][ecnt[ty]]=tx;
            //et[tx][ty]=1;
            //et[ty][tx]=1;
        }
        else
        {
            merge(tx,ty);
        }
    }
    For(i,1,n)//处理敌人的敌人
    {
        For(j,1,ecnt[i])
        {
            tx=e[i][j];			//代码习惯不好，一开始写的很乱然后脑子短路这里就写错了- -
            For(h,1,ecnt[tx])
            {
                //if(!et[i][e[e[i][j]][h]])
                 merge(i,e[tx][h]);
            }
        }
    }
    For(i,1,n)//统计答案数
    {
        if(!t[find(i)])
        {
            ++ans;
            t[find(i)]=1;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：毛毛39015148 (赞：1)

这个题用并查集基本可以。

蒻狗不会写带权并查集，就直接写并查集用敌人数组维护。

再特判一下如果你的朋友也是你敌人的朋友，就不能进行合并。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxsize=1000;
using namespace std;
int uset[maxsize],rank[maxsize];
void makeset(int size)//模板并查集
{
    for(int i=1;i<=size;i++)
    {
        uset[i]=i;
        rank[i]=1;
    }
}
int find(int x)
{
    if(x!=uset[x])uset[x]=find(uset[x]);
    return uset[x];
}
void unionset(int x,int y)
{
    if((x=find(x))==(y=find(y)))return;
    if(rank[x]>rank[y])uset[y]=x;
    else
    {
        uset[x]=y;
        if(rank[x]==rank[y])rank[y]++;
    }
}
int main()
{
    int n,m,ans=0,x1,y1,e[maxsize],count[maxsize];
    char z;
    scanf("%d%d",&n,&m);
    makeset(n);
    for(int i=1;i<=maxsize;i++)
    {
        e[i]=0;
        count[i]=0;
    }
    for(int i=1;i<=m;i++)
    {    
        cin>>z>>x1>>y1;
        if(z=='F')
        {
            if(find(e[x1])!=find(y1))unionset(x1,y1);//敌人的朋友不一定是我的敌人，但不能合并；
        }
        else
        {
            if(e[x1]==0)e[x1]=y1;
            else{
                unionset(e[x1],y1);
            }
            if(e[y1]==0)e[y1]=x1;
            else{
                unionset(e[y1],x1);
            }
        }
    }
    for(int i=1;i<=n;i++)//简单的统计
    {
        count[find(i)]=1;
    }
    for(int i=1;i<=n;i++)
    {
        if(count[i]==1)ans++;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：shadowice1984 (赞：1)

这道题应该都知道用并查集维护朋友的关系

那么敌人的关系该怎么办呢？

一个朴素的想法是用一个邻接表维护他的所有敌人

然后一个一个并出边。

（是不是很蠢)

但是你的边也是一个个加进去的，这样的话根据朋友的朋友还是朋友，

我们关心的就是出边集合的代表元而不是出边集合的每一个元素

所以邻接表就退化为一个数组，然后就可以Ac了

上代码~


```cpp
#include<stdio.h>
using namespace std;
int res;int n;int m;
struct set//一只裸的并查集
{
    int fa[1010];
    void ih()
    {
        for(int i=1;i<=n;i++)
        fa[i]=i;
        return;
    }
    int f(int x)
    {
        if(fa[x]==x)return x;
        else 
        {
            fa[x]=f(fa[x]);
            return fa[x];
        }
    }
    void u(int u,int v)
    {
        int x=f(u);
        int y=f(v);
        if(x!=y)res--;
        fa[x]=y;
        return;
    }
}fr;
int em[1010];
int main()
{
    scanf("%d%d",&n,&m);
    res=n;
    fr.ih();
    for(int i=0;i<m;i++)
    {
        char c[2];int u;int v;
        scanf("%s%d%d",c,&u,&v);
        if(c[0]=='F')
        {
            fr.u(u,v);
        }
        if(c[0]=='E')
        {
            if(em[u]!=0)//精髓所在，每次并上集合的代表元即可，因为每个人的敌人们一定是团伙
            {
                fr.u(em[u],v);
            }
            if(em[v]!=0)
            {
                fr.u(em[v],u);
            }
            em[u]=v;em[v]=u;
        }
    }
    /*for(int i=1;i<=n;i++)
    {
        printf("fa[%d]=%d,em[%d]=%d\n",i,fr.fa[i],i,em[i]);
    }*/
    printf("%d",res);
    return 0;
}

```

---

## 作者：僚机 (赞：1)

写法是裸的并查集没有错  ，运用到并查集补集的思想 关系只能按照题目给的来建！！！

f[i]:朋友 f[i+n]:敌人

每次处理关系




```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int fa[2005];//f[i]:朋友 f[i+n]:敌人 
int n,m;
bool in[2005];
int find(int u){
    if(u==fa[u]){
        return u;
    }
    return fa[u]=find(fa[u]);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n*2;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        char c;
        int y1,x1;
        cin>>c>>x1>>y1;
        if(c=='E'){
            fa[find(y1+n)]=find(x1);
            fa[find(y1)]=find(x1+n);
        }
        if(c=='F'){
            fa[find(x1)]=find(y1);
        }
    }
    for(int i=1;i<=n;i++){
        in[find(i)]=true;
    }
    int sumn=0;
    for(int i=1;i<=n*2;i++){
        if(in[i]){
            sumn++;
        }
    }
    cout<<sumn<<endl;
    return 0;
}
```

---

## 作者：Mojiu (赞：1)

对于这道题，其实我一开始以为是道简单并查集模板题，对于“我朋友的朋友是我的朋友”这个要求很好理解，直接并查集模板就可以过，


但是对于“我敌人的敌人也是我的朋友”这个要求就需要动点脑筋了。我一开始想用两个并查集，一个代表朋友，一个代表敌人，然后通过遍历敌人的并查集来确定关系，但是很显然是做不到的。


于是我再次研究了一下题目，于是发现了一件重要的事，一个敌人的所有敌人都在同一个朋友并查集里。所以我们只要用一个数组来记录a的一个敌人（是的，没错就是一个），当再次遇到a的一个敌人时直接将他们两个放入同一个并查集，于是题目就完美的解决了。


ps：而且通过比较，这种比那种用二维存储敌人关系的方法要快的多，我十个点全部0ms，如果题目数据更大的话，显然是这种方法更占优势


---

## 作者：lvjiyuan (赞：1)

因为数据规模较小，所以用邻接矩阵。

对于i点，朋友关系直接并到fa中，对于敌人，查i的敌人的敌人，再把i敌人的敌人并到fa【i】中，

因为每个节点都循环一次，所以不会漏掉。

蒟蒻一枚，代码凑合看吧。

            
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Z=6000;
bool ene[1001][1001],fri[1001][1001],vis[1001];
int fa[1001];
int p,m;
int getf(int no)
{
    if(no==fa[no])return no;
    else return fa[no]=getf(fa[no]);
}
void hebing(int i,int jj)
{
    int t1=getf(i);
    int t2=getf(jj);
    if(t1!=t2)fa[t2]=t1;    
}
void search(int u,int v)
{
    for(int i=1;i<=p;i++)
    {
        if(ene[i][v]==1&&i!=u)
        {
            hebing(u,i);
        }
    }
}
int main()
{
    cin>>p>>m;
    char c;
    int x,y;
    for(int i=1;i<=p;i++)fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        cin>>c>>x>>y;
        if(c=='E'){ene[x][y]=ene[y][x]=1;}
        if(c=='F'){fri[x][y]=fri[y][x]=1;}
    }
    for(int i=1;i<=p;i++)
    {
        for(int jj=1;jj<=p;jj++)
        {
            if(i!=jj)
            {
                if(fri[i][jj])hebing(i,jj);
                if(ene[i][jj])search(i,jj);
            }
        }
    }
    int cnt=0;
    for(int i=1;i<=p;i++){
        if(fa[i]==i)cnt++;
    }
    cout<<cnt;
    return 0;
}
```

---

## 作者：infinityedge (赞：1)

一道普通的并查集题

难点在于有敌人这个系统 大多数人想到的就是把这个人的敌人和所有敌人一一合并，然而这样既浪费时间（Onm）也浪费空间（On2）;

解决方法是只开一个一位数组e[1001]来存储最近读入的敌人，（为什么不全部存储呢？）因为之前的敌人已经被合并过了；

===================分割线=====================

[codec]

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int f[1001],e[1001],c[1001],n,m,cnt=0;
void csh() {//初始化，把每个强盗都视为一个团伙
    memset(f,0,sizeof(f));
    memset(e,0,sizeof(e));
    memset(c,0,sizeof(c));
    for(int i=1; i<=n; i++) {
        f[i]=i;
    }
}
int find(int x) {//找头目 会并查集的应该都会（反正我会）
    if(f[x]==x)return x;
    f[x]=find(f[x]);
    return f[x];
}
void hebing(int x,int y) {//合并函数，把两个互为朋友的人合并为一个团伙
    int x1=find(x);
    int y1=find(y);
    if(x1!=y1) {
        f[x1]=y1;
    }
}
int main() {//前方高能
    cin>>n>>m;
    csh();
    char ch;
    int x,y;
    for(int i=1; i<=m; i++) {
        cin>>ch;
        cin>>x>>y;
        if(ch=='F') {//如果是朋友就合并，不多说
            hebing(x,y);
        }
        if(ch=='E') {//如果是敌人
            if(e[x]!=0)hebing(y,e[x]);//把自己的敌人合并为一个团伙（最近读到的敌人已经与前面所有敌人合并，只与他合并就可以）
            if(e[y]!=0)hebing(x,e[y]);//把自己和自己敌人的敌人合并为一个团伙
            e[x]=y;
        }
    }
    for(int i=1; i<=n; i++) {//遍历 如果有这个团伙对应的变量为1（之前初始化为0了）
        c[find(i)]=1;
    }
```
[/codec]
```cpp
    for(int i=1; i<=n; i++) {//统计有多少团伙
        if(c[i])cnt++;
    }
    cout<<cnt;
    return 0;
}

```

---

## 作者：Skywalker_David (赞：1)

跟普通并查集一样，是朋友就合并；出现敌人，则敌人的敌人与自己合并（至于敌人是怎么存的，我是用的邻接表……）最后加以个vis数组遍历一遍，如果出现新祖宗就加一。

==================魂淡的分割线========================

把每个人拆成两个点，如果a,b两人是敌人，就合并a的朋友点和b的敌人点，再合并a的敌人点和b的朋友点；如果a,b两人为朋友，就合并a,b两人的朋友点，注意不要合并敌人点。

```delphi

var
  f,e:array[1..1000] of longint;
  k:char;
  n,m,a,b,max,i:longint;
function find(o:longint):longint;
begin
  if f[o]=0 then exit(o)
            else exit(find(f[o]));
end;
procedure hb(a,b:longint);
begin
  a:=find(a);
  b:=find(b);
  if a<>b then f[a]:=b;
end;
procedure pd;
begin
end;
begin
  readln(n);
  readln(m);
  for i:=1 to m do
  begin
    readln(k,a,b);
    if (k='F')or(k='f') then hb(a,b)
                        else
                        begin
                          if e[a]<>0 then hb(e[a],b);
                          if e[b]<>0 then hb(e[b],a);
                          if e[a]=0 then e[a]:=b;
                          if e[b]=0 then e[b]:=a;
                        end;
  end;
  for i:=1 to n do
    if f[i]=0 then inc(max);
  writeln(max);
end.

```

---

## 作者：唔啊唔 (赞：1)

这是一道稍简单的并查集。

思路是，开始时设有n个团伙，每次合并时团伙数减一。

附上AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,cnt[1010],dr[1010][1010],father[1010];
char c;
inline int find(int x){	//压缩路径 
    if(x!=father[x])
        father[x]=find(father[x]);
    return father[x];
}
int main(){
    cin>>n>>m;
    int ans=n;
    for(register int i=1;i<=n;i++)father[i]=i;
    for(register int i=1;i<=m;i++){
        cin>>c>>x>>y;
        if(c=='F'){	//是朋友就合并 
            int q=find(x),w=find(y);
            if(q!=w){
                father[q]=w;
                ans--;
            }
        }
        else{	//记录敌人 
            cnt[x]++;
            cnt[y]++;
            dr[x][cnt[x]]=y;
            dr[y][cnt[y]]=x;
        }
    }
    for(register int i=1;i<=n;i++){	//敌人的敌人是朋友 
        for(register int j=1;j<cnt[i];j++){
            int q=find(dr[i][j]),w=find(dr[i][j+1]);
            if(q!=w){
                father[q]=w;
                ans--;
            }
        }
    }
    cout<<ans;
    return 0; 
}
```


---

## 作者：C6H2CH3_NO2_3 (赞：0)

首先，刷题是好的，它能让你发现很多奇怪的错误。然后你以后就不会再犯这些错误。--蒟蒻的刷题心得
---

首先献上30分代码
```
#include<bits/stdc++.h>
#define ll long long 
#define maxn 1005
using namespace std;
ll read(){
	ll f=1,k=0;
	char c=0;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+c-'0';
		c=getchar();
	}
	return k*f;
}
ll n,m,fa[maxn];
ll father(ll x){
	if(fa[x]==x)return x;
	return fa[x]=father(fa[x]);
}
void add(ll x,ll y){
	ll xfa=father(x),yfa=father(y);
	if(xfa==yfa)return;
	fa[xfa]=yfa;
}
vector< ll >fight[maxn];
int main(){
	n=read();m=read();
	for(ll i=1;i<=n;i++)fa[i]=i;
	for(ll i=1;i<=m;i++){
		char c=getchar();
		ll x=read(),y=read();
		if(c=='F')add(x,y);
		else{
			fight[x].push_back(y);
			fight[y].push_back(x);
		}
	}
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<fight[i].size();j++){
			for(ll k=0;k<fight[fight[i][j]].size();k++){
				add(i,fight[fight[i][j]][k]);
			}
		}
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
	if(father(i)==i)ans++;	
	}
	cout<<ans;
	return 0;
} 
```

我检查了好多遍，都没有发现错误（大佬orz可以帮忙找下错）
那么错误究竟是什么呢？请看AC代码：
```
#include<bits/stdc++.h>
#define ll long long 
#define maxn 1005
using namespace std;
ll read(){
	ll f=1,k=0;
	char c=0;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+c-'0';
		c=getchar();
	}
	return k*f;
}
ll n,m,fa[maxn];
ll father(ll x){
	if(fa[x]==x)return x;
	return fa[x]=father(fa[x]);
}
void add(ll x,ll y){
	ll xfa=father(x),yfa=father(y);
	if(xfa==yfa)return;
	fa[xfa]=yfa;
}
char get(){
	char c=' ';
	while(c==' '||c=='\r'||c=='\n'){
		c=getchar();
	}
	return c;
}
vector< ll >fight[maxn];
int main(){
	n=read();m=read();
	for(ll i=1;i<=n;i++)fa[i]=i;
	for(ll i=1;i<=m;i++){
		char c=get();
		ll x=read(),y=read();
		if(c=='F')add(x,y);
		else{
			fight[x].push_back(y);
			fight[y].push_back(x);
		}
	}
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<fight[i].size();j++){
			for(ll k=0;k<fight[fight[i][j]].size();k++){
				add(i,fight[fight[i][j]][k]);
			}
		}
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
	if(father(i)==i)ans++;	
	}
	cout<<ans;
	return 0;
} 
```
大家可以发现，在30分代码中，我使用的是getchar函数读取字符，而100分代码中，是自定义函数get读取字符。这样就可以过滤掉多余的东西！！！

```
ll n,m,fa[maxn];//fa[i]--i的父亲
ll father(ll x){
    if(fa[x]==x)return x;//如果x为自己的父亲返回x
	return fa[x]=father(fa[x]);//路径压缩   
}
void add(ll x,ll y){//合并x,y所在的两个团伙
	ll xfa=father(x),yfa=father(y);
	if(xfa==yfa)return;//若属于同一团伙则不需合并
	fa[xfa]=yfa;
}
```
以上是合并团伙的代码段

```
int main(){
	n=read();m=read();
	for(ll i=1;i<=n;i++)fa[i]=i;
	for(ll i=1;i<=m;i++){
		char c=get();
		ll x=read(),y=read();
		if(c=='F')add(x,y);
		else{
			fight[x].push_back(y);
			fight[y].push_back(x);
//fight[i]为vector数组，表示i的所有敌人的编号
		}
	}
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<fight[i].size();j++){
			for(ll k=0;k<fight[fight[i][j]].size();k++){
				add(i,fight[fight[i][j]][k]);
//将i的敌人的所有敌人与i合并
			}
		}
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
	if(father(i)==i)ans++;	
//犯罪团伙计数
	}
	cout<<ans;
	return 0;
} 
```
于是，我从这道题中学到了--自己动手，丰衣足食。（以后读入输出都要自己打！！！！！）
--
                    by 一个蒟蒻

---

## 作者：zhaowangji (赞：0)

看到前面几篇题解，都写得好简便啊~~然而看不懂~~

于是自己写了一篇，虽然代码看着有点饶头（vector的嵌套），但思路还是很清晰的

用并查集+vector

fri指朋友，ene指敌人,th指团伙

fa是并查集，保存每个人的祖先


```cpp
#include<iostream>
#include<algorithm>
#include<vector> 
using namespace std;
int n,m;
vector<int> fri[1007];
vector<int> ene[1007];
vector<int> th;
int fa[1007];
int fi(int x){
	if(fa[x]!=x)fa[x]=fi(fa[x]);
	return fa[x];//找祖先
}
void hb(int x,int y){
	fa[x]=y;
	return;//合并
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	fa[i]=i;//先把祖先保存为自己
	for(int i=1;i<=m;i++){
		char s;
		int x,y;
		cin>>s>>x>>y;//读入，注意类型
		if(s=='E'){//两个人是敌人
			ene[x].push_back(y);
			ene[y].push_back(x);//分别把对方视为敌人
		}
		else {//两个人是朋友
			fri[x].push_back(y);
			fri[y].push_back(x);//分别把对方视为朋友
			if(fi(x)!=fi(y))
				hb(fi(x),fi(y));//把朋友合并（团伙）
		}
	}
	for(int i=1;i<=n;i++)//每个人
		for(int j=0;j<fri[i].size();j++)//他的朋友
			for(int k=0;k<fri[fri[i][j]].size();k++)//朋友的朋友
				if(fi(i)!=fi(fri[fri[i][j]][k]))//不在同一个集合里
					hb(fi(i),fi(fri[fri[i][j]][k]));//合并他们
	for(int i=1;i<=n;i++)//每个人
		for(int j=0;j<ene[i].size();j++)//他的敌人
			for(int k=0;k<ene[ene[i][j]].size();k++)//敌人的敌人
				if(fi(i)!=fi(ene[ene[i][j]][k]))//不在同一个集合里
					hb(fi(i),fi(ene[ene[i][j]][k]));合并
    	//fri/ene[i][j]就是每个人的朋友/敌人，而fri/ene[ fri/ene[i][j](就是一个人) ][k]就是每个人的朋友/敌人的朋友/敌人          
        //这样合并以后，凡是同一个团伙的人，祖先都相同
	for(int i=1;i<=n;i++){//每个人
		bool flag=false;//没有找到自己的团伙
		for(int j=0;j<th.size();j++)
			if(fi(i)==th[j]){flag=true;break;}
				//自己的祖先与团伙的祖先相同，说明已经在一个团伙里了，标记
        	if(flag==false)//没找到自己的团伙
			th.push_back(fi(i));//自己开办一个团伙
	}
	cout<<th.size()<<endl;//团伙数
	return 0;
}
```


---

## 作者：路依然远 (赞：0)

照例与各位分享一首纯音：Strength Of A Thousand Men

边听边看


------------

没事写篇题解

这题不知道各位大佬们是怎么做的，但本蒟蒻是用并查集做的。

然后AC了

如果不知道并查集是神马，[点我](https://wenku.baidu.com/view/9c1a469848d7c1c709a1)

先上代码：

```pascal
var
 d:array[0..1000,0..1000] of boolean;
 f:array[0..1000] of longint;
 i,k,n,m,x,y,t:longint;
 c,h:char;
 
function find(x:longint):longint;/查，查找两个集合的根
begin
 if f[x]<>x then f[x]:=find(f[x]);
 find:=f[x];
end;
procedure merge(x,y:longint);//并，合并两个集合
var
 fx,fy:longint;
begin
 fx:=find(x);
 fy:=find(y);
 if fx<>fy then f[fx]:=fy;
end;
begin
 readln(n,m);
 for i:=1 to n do //并查集初始化
  f[i]:=i;
 for i:=1 to m do
  begin
   readln(c,h,x,y);
   if c='F' then merge(x,y)//如果是盆友，则合并
            else begin //如果不是，就麻烦了
                  d[x,y]:=true;d[y,x]:=true;
                  //敌人连起来
                  for k:=1 to n do
                  //k枚举中间的人
                   if (k<>x)and(k<>y) then
                    begin
                     if d[x,k] then merge(k,y);
                     //若x和k是敌人，那么k和y就是盆友
                     if d[k,y] then merge(k,x);
                     //若k和y是敌人，那么k和x就是盆友
                    end;
                 end;
  end;
 for i:=1 to n do
  if f[i]=i then t:=t+1;
 writeln(t);
end.


```
~~懂了再抄~~

其实也没什么，把并查集模板套进去就OK了，只不过敌人的敌人是朋友这点有点麻烦

就到这了,关机睡觉


---

## 作者：bztMinamoto (赞：0)

蒟蒻刚学了一点并查集，写的不好请神犇们勿喷

基础思路：如果两个人是朋友，将其合并

如果两个人是敌人，将A的敌人和B合并（即将A的敌人和B视为朋友），B的敌人同理

基于以上思路，我们可以用一个数组存储每个人的敌人

因为每个人的敌人已经被合并，，可以保证不会有遗漏

细节看注解吧，上代码
```
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1050;
struct ab{
    int f,h;
};
ab f[N];//存储父亲，h用于按秩合并，可以省略
int g[N];
int n,m,ans=0;
bool used[N];
int ff(int x)
{
    if(f[x].f==x) return x;
    return f[x].f=ff(f[x].f);
}
//寻找父亲
void unite_1(int x,int y)
{
    x=ff(x),y=ff(y);
    if(x==y) return;
    if(f[x].h<f[y].h)
    f[x].f=y;
    else if(f[x].h>f[y].h)
    f[y].f=x;
    else
    f[y].f=x,f[x].h++;
    return;
}
//将两个朋友合并
void unite_2(int x,int y)
{
  //如果敌人为0，将其指为另一人，否则会出错（我就是因为这个WA了好几次）
    if(g[x]==0)
    g[x]=y;
    unite_1(g[x],y);
    if(g[y]==0)
    g[y]=x;
    unite_1(g[y],x);
    return;
}
//将敌人与自己的朋友合并
bool same(int x,int y)
{
    if(ff(x)==ff(y)) return true;
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    f[i].f=i,f[i].h=1,g[i]=0;//初始化，敌人为0
    for(int i=0;i<m;i++)
    {int a,b;
    char k;
    cin>>k>>a>>b;
    if(k=='F')
    unite_1(a,b);
    else
    unite_2(a,b);
        }
    for(int i=1;i<=n;i++)
    {if(!used[ff(i)]) ans++,used[ff(i)]=1;
        }
    //遍历一遍，检查有几个团伙
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Macwyw (赞：0)

并查集求集合数

最后求一个代表元素的数量即为集合的数量

（附一个蒟蒻的AC代码）






    

    
    

    
    


    
    
    
            
            
            
    
    
    
        
    
    

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 1050;
int fa[MAXN];
int f[MAXN];
void init(int n)
{
    int i;
    for(i=0;i<=n;i++)
    {
        fa[i]=i;
    }
}
int find_set(int x)
{
    int fx,y;
    fx=x;
    while(fa[fx]!=fx)
    {
        fx=fa[fx];
    }
    while(fa[x]!=fx)
    {
        y=fa[x];
        fa[x]=fx;
        x=y;
    }
    return fx;
}
void union_set(int x,int y)
{
    int fx,fy;
    fx=find_set(x);
    fy=find_set(y);
    fa[fy]=fx;
}
int main()
{
    int n,m;
    int i,j,k;
    int x,y;
    char c;
    int ans;
    scanf("%d%d",&n,&m);
    memset(f,0,sizeof(f));
    init(n);
    for(i=0;i<m;i++)
    {
        scanf("%s%d%d",&c,&x,&y);
        if(c=='E')
        {
            if(f[x]==0)
            {
                f[x]=find_set(y);
            }
            if(f[y]==0)
            {
                f[y]=find_set(x);
            }
            union_set(f[y],x);
            union_set(f[x],y);
        }
        else if(c=='F')
        {
            union_set(x,y);
        }    
    }
    memset(f,0,sizeof(f));
    ans=0;
    for(i=1;i<=n;i++)
    {
        k=find_set(i);
        f[k]++;
    }
    for(i=1;i<=n;i++)
    {
        if(f[i]!=0)
        {
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：封禁用户 (赞：0)






```cpp
//并查集pascal代码
var
  fa,f:array[0..10000] of longint;
//fa指一个点的父亲，f是重点，指的是一个点的敌人集合的根节点
  i,j,k,l,m,n,y,z,t,n1,m1:longint;
  x:char;
  b:array[0..2000,0..2000]of boolean;
function ask(x:longint):longint;//并查集简单操作
begin
  if fa[x]=x then exit(x) else ask:=ask(fa[x]);
  fa[x]:=ask;//优化加速
end;
procedure bcj(x,y:longint);//合并x，y两个集合
var p,q:longint;
begin
  p:=ask(x); q:=ask(y);
  if p=q then exit;
  fa[q]:=p;
end;
function min(x,y:longint):longint;
begin
  if x<y then exit(x)else exit(y);
end;
begin
  readln(n); readln(m);
  for i:=1 to n do fa[i]:=i;
  for i:=1 to m do
  begin
    readln(x,y,z);
    if x='F' then bcj(y,z)//是友则直接合并
    else
    begin
      if f[z]=0 then f[z]:=y else bcj(f[z],y);//是敌人则合并敌人的敌人集合
      if f[y]=0 then f[y]:=z else bcj(f[y],z);//同上
      b[y,z]:=true;
      b[z,y]:=true;
    end;
  end;
  for i:=1 to n do
  for j:=1 to n do
  if b[i,j]then
  begin
    bcj(f[i],j);
    bcj(f[j],i);
  end;
  for i:=1 to n do if i=fa[i]then inc(k);
  write(k);
end.
```

---

