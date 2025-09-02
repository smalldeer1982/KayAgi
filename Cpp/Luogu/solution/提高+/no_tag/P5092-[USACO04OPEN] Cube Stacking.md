# [USACO04OPEN] Cube Stacking

## 题目描述

约翰和贝茜在玩一个方块游戏。编号为 $ 1\ldots n $ 的 $ n $（$ 1 \leq n \leq 30000 $）个方块正放在地上，每个构成一个立方柱。

游戏开始后，约翰会给贝茜发出 $ P $（$ 1 \leq P \leq 100000 $）个指令。指令有两种：

1. 移动（```M```）：将包含 ```X``` 的立方柱移动到包含 ```Y``` 的立方柱上。
2. 统计（```C```）：统计含 ```X``` 的立方柱中，在 ```X``` 下方的方块数目。

写个程序帮贝茜完成游戏。

## 说明/提示

部分数据范围见输入格式。

$1 \le X, Y \le n$。

## 样例 #1

### 输入

```
6
M 1 6
C 1
M 2 4
M 2 6
C 3
C 4```

### 输出

```
1
0
2```

# 题解

## 作者：Han_Innocence (赞：30)

就像NOIP2018模仿POI一样

USACO2004居然copyNOIP2002的题

而且还简化了......



------------

这算是模板题吧，相信大家都是来学习并查集的相关知识的，那我就从头开始讲，以基础知识为主


------------

解题思路：带权并查集+路径压缩

用dis数组储存某一节点到他所在队列队首的距离


------------

Part I 带权并查集

我们用fa[i]数组表示i节点的父亲，初始化为i
若某一个节点的fa等于他自己（fa[i]=i），说明这个节点还没有被移动过，他就是第i队列的队首
于是得到find函数
```cpp
int find(int x)
{
	if (fa[x]==x) return x;
	return find(fa[x]);
}
```

同时，用dis[i]表示i节点到他所在队列队首的距离，初始化为0。length[i]表示第i队列的长度（显然这一队列的队首为i），初始化为1。当移动X队列到Y后时，则有：

fa[x]=fa[y],dis[x]=length[y],length[y]+=length[x]

注意：我们已无法将其他队列移动到原x队列，故没有必要将length[x]改为0

于是得到move函数
```cpp
void move(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	fa[fx]=fy;
	dis[fx]+=length[fy];	
	length[fy]+=length[fx];
}
```


那么check函数就简单啦

```cpp
void check(int x)
{
	int ffx=find(x); 
	printf("%d\n",dis[x]);
}
```


以上程序整合后，期望得分60分。60%AC+40%TLE

那么，我们该如何优化呢？


------------

Part II 路径压缩

我们发现，当某一节点x在另一节点y上方，那么他、它永远在y上方，而且两点间距恒定。（因为我们不能把其他队列插入到它们中间）

利用这个性质，我们进行路径压缩

举个例子

fa[2]=1,fa[3]=2,fa[4]=3; 任意两点间距为1

压缩为：

fa[2]=1,dis[2]=1,fa[3]=1,dis[3]=2,fa[4]=1,dis[4]=3

这个过程我们用回溯实现，在一步步找到队列队首后，一步步原路返回，把每一节点的fa都改为队首，并相应的改变dis即可。于是得到优化后的find函数

```cpp
int find(int xx)
{
	if (fa[xx]==xx) return xx;
	int father=find(fa[xx]);
	dis[xx]+=dis[fa[xx]];
	fa[xx]=father;
	return father;
}
```



------------

完整代码，检验后AC
```
#include<cstdio>
#include<iostream>
#include<cmath> 
#define num 30001
using namespace std;
int n,fa[30005],dis[30005],length[30005];
int read()
{
    int x=0,f=1; char c=getchar();
    while (c<'0' || c>'9') {if (c=='-') f=-1; c=getchar();}
    while (c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48); c=getchar();}
    return x*f;
}
int find(int xx)
{
    if (fa[xx]==xx) return xx;
    int father=find(fa[xx]);
    dis[xx]+=dis[fa[xx]];
    fa[xx]=father;
    return father;
}
void move(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    fa[fx]=fy;
    dis[fx]+=length[fy];	
    length[fy]+=length[fx];
}
void check(int x)
{
    int ffx=find(x); 
    printf("%d\n",dis[x]);
}
int main()
{
    n=read();
    for (int i=1;i<=num;i++) fa[i]=i;
    for (int i=1;i<=num;i++) length[i]=1;
    for (int w=1;w<=n;w++)
    {
        char c; cin>>c;
        int x=read();
        if (c=='M')
        {
            int y=read(); 
            move(x,y);
        }
        if (c=='C') check(x);
    }
    return 0;
}
```





------------

最后说明几点：

1、没有必要关注fa[i]到底是i节点的上几位，因为dis数组随之变化，加上上述性质，他已经覆盖了中间区域。

2、蒟蒻写题解，有bug疏漏请大家不要喷，有问题可以在评论区提问，我会常常关注。最后希望题解对大家有用，祝大家AC此题，AK IOI。

3、如有需Pascal代码请在评论区回复。


---

## 作者：NewSjf (赞：10)

众所周知这是一个并查集的题        
但是我选择了最爱的非旋Treap        
~~跑得还挺快的~~      
把这些点看成序列      
M操作就是合并两个序列(y序列放在x序列后面)   
C操作就是某个元素val在序列中的位置-1(从左往右)   
这种合并的操作对非旋Treap来说算是常规操作了
思路非常好想     
刚开始我们新建30000个孤立的平衡树(就是只有一个点)     
我们在正常非旋Treap的基础上,维护每个点的父节点    
从某个点开始一直往父节点跳就能找到这个点所在的树的根节点  
接下来我们合并两个根节点,那么就完成了两颗平衡树的合并,或者说就是题目中的M操作,注意y树在x树前面  
当然这里都是对于点的操作,而题目中是合并值为val的两个点所在的树   
注意到每个点的值都不一样(从1到n),那么我们就用一个maps数组来记录每个值val对应平衡树中结点编号.   
这样就能从某个值找到他在平衡树中的结点,然后找到该节点所在树的根节点合并   
对于C,要麻烦点    
对平衡树中序遍历,得到的就是我们维护的序列   
现在问题就变成了某个点在中序遍历中的顺序   
做法就是从这个点一直往根节点跳
对于某个节点,如果他是其父节点的右儿子,那么对应的顺序就应该是其兄弟节点的size+父节点大小(就是以父节点为根的子树,中序遍历先遍历左子树,父节点,然后才轮到右子树,)  
如果是右儿子就直接往父节点跳
然后往父节点跳,再统计size.直到找到根节点
然后答案减一就是答案了   
接下来就是我又臭又长的代码了
```cpp
#include<iostream>
#include<cstdlib>
#define MAXN 1000001
struct node{int val,key,size,l,r,f;}t[MAXN];
int root,tot,n=40000,p,maps[MAXN];
using namespace std;
int New(int val)
{
	t[++tot]=(node){val,rand(),1,0,0,0};
	return maps[val]=tot;
}
void update(int now)
{
	t[now].size=t[t[now].r].size+t[t[now].l].size+1;  //根为now的子树大小为左子树+右子树+父节点 
	t[t[now].l].f=now;    //更新父亲 
	t[t[now].r].f=now;
}
void split(int now,int&x,int&y,int rank)
{
	if(!now){x=y=0;return;}
	if(t[t[now].l].size>=rank)y=now,split(t[now].l,x,t[y].l,rank);
	else x=now,split(t[now].r,t[x].r,y,rank-t[t[now].l].size-1);
	update(now); 
}
void merge(int&now,int x,int y)    //这个merge是非旋Treap中的merge 
{
	if(!x||!y){now=x+y;return;}
	if(t[x].key<t[y].key)now=x,merge(t[now].r,t[x].r,y);
	else now=y,merge(t[now].l,x,t[y].l);
	update(now);
}
int find_root(int val) //值为val的点所在平衡树的根节点 
{
	int now=maps[val];
	while(t[now].f)now=t[now].f;
	return now;
}
int order_of_key(int val) //在序列中的位置 
{
	int now=maps[val],ans=0;
	ans+=t[t[now].l].size+1;
	while(now)
	{
		if(t[t[now].f].r==now)
			ans+=t[t[t[now].f].l].size+1;
		now=t[now].f;
	}
	return ans;
}
void merge(int x,int y)  //这个merge对应题目中的M操作 
{
	x=find_root(maps[x]),y=find_root(maps[y]);
	merge(x,x,y);
}
int main()
{
	ios::sync_with_stdio(false);
	for(int i=1;i<=n;i++)New(i);
	cin>>p;
	for(int i=1;i<=p;i++)
	{
		char opt;
		int x,y;
		cin>>opt;
		if(opt=='M')cin>>x>>y,merge(y,x); 
		else cin>>x,cout<<order_of_key(x)-1<<endl;
	}
}
```


---

## 作者：Dawn_Sdy (赞：8)

前置知识点：并查集，不会的请先做[模板](https://www.luogu.org/problem/P3367)

首先很容易看出这是一道与并查集有关的题目，但由于他需要维护在x下面的方块个数，所以和并查集又不完全一样。

你会发现他只是比普通的并查集需要多维护一个权值而已，而这种并查集就是——**带权并查集**

按照并查集的思路，我们需要研究以下几个问题：

1.维护哪些权值

2.如何合并

3.如何查询

4.如何路径压缩

------------

### $1^o$ 需要维护哪些权值

这里有一个小技巧，由于我们需要维护的权值只有在$x$下面的数量，所以我们可以让一堆中的最下面的一个为当前集合的根，方便以后操作。

我们需要维护一下三个值：
```cpp
struct node{
	int fa,up,down;//分别是当前集合的根，在他上面的方块数(包括自己），在他下面的方块数
}father[100005];
```

### $2^o$ 如何合并

当我们要把$x$，$y$（$x$,$y$均为集合的根）两个集合合并时会产生三种变化。

1.$x$集合的每个数的$down$都会加上$y$集合中的所有元素。

而$y$集合中的所有元素会存在$father[y].up$中

所以每次:	$father[x].down=father[y].up$即可

2.$y$集合中的每个数的$up$都会加上$x$集合中的所有元素。

而$x$集合中的所有元素都会存在$father[x].up$中

所以每次：$father[y].up+=father[x].up$即可

3.并查集常规祖先变换
每次：$father[x].fa=father[y].fa$即可

给出片段代码（f1相当于x，f2相当于y)
```cpp
inline void unnion(int f1,int f2)
{
	father[f1].fa=f2;//更新fa
	father[f1].down=father[f2].up;//更新down
	father[f2].up+=father[f1].up;//更新up
}
```

### $3^o$ 如何查询


查询比较简单，只要对于$x$输出$father[x].down$即可。

### $4^o$ 如何路径压缩

我们知道在寻找一个集合的根时，路径压缩是一个很重要的优化。

而到了带权并查集中，路径压缩显得更为重要。

例如本题我们每次更新权值，都只更新了每个集合的根，而显然同一个集合中的每一个点权值是不一样的，所以此时我们就要在路径压缩时把权值传下去。（有点类似于线段树的push_down下传）

我们可以稍微画个图分析一下，首先对于每个点我们显然只有$down$这个权值还没有维护好，所以只需维护$down$

而且不难发现，对于每个点，所缺少的都是上次合并时更新到根节点中的$father[y].up$。

又由于我们的更新方式是这样的$father[x].down=father[y].up$。

所以我们只需要在路径压缩的过程中将每个点的$down$都加上根节点的$down$就行了。

放部分代码：

```cpp
inline int Find(int x)
{
	if (father[x].fa!=x)
	   {
	   int gr=Find(father[x].fa);//找根，顺便更新到他的父亲中
	   father[x].down+=father[father[x].fa].down;//路径压缩，下传权值
	   return father[x].fa=gr;
	   }
	return father[x].fa;
}
```


------------

这样维护下来就可以解决了~~~

放AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0;
	char c=getchar();
	bool f=0;
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
int p;
struct node{
	int fa,up,down;
}father[100005];
int ans[100005];
inline int Find(int x)//找根，顺便下传权值
{
	if (father[x].fa!=x)
	   {
	   int gr=Find(father[x].fa);
	   father[x].down+=father[father[x].fa].down;
	   return father[x].fa=gr;
	   }
	return father[x].fa;
}
inline void unnion(int f1,int f2)//合并
{
	father[f1].fa=f2;
	father[f1].down=father[f2].up;
	father[f2].up+=father[f1].up;
}
int main(){
	for (register int i=1;i<=100005;++i)
	    father[i].fa=i,father[i].up=1,father[i].down=0;
	p=read();
	for (register int i=1;i<=p;++i)
		{
		char c=getchar();
		while (!isalpha(c))
		      c=getchar();
		if (c=='M')
		   {
		   int x=read(),y=read();
		   int f1=Find(x),f2=Find(y);
		   if (f1!=f2)
		      unnion(f1,f2);
		   }
		else
		   {
		   int x=read();
		   Find(x);//在查询前要把权值下传
		   printf("%d\n",father[x].down);
		   }
		}
	return 0;
}

```
最后送个福利给看到最后的$Oier$们

[双倍经验](https://www.luogu.org/problem/P2342)

---

## 作者：_Felix (赞：4)

对于每个方块 $x$ ,

$cnt_x$ 代表以 $x$ 为根结点的方块的个数，（即x是一幢方块的顶，问这幢方块一共有几个。）

$dis_x$ 表示 $x$ 到根节点的距离。(即x头上顶着多少个方块)

![](https://cdn.luogu.com.cn/upload/image_hosting/j0btcev1.png)

```
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define rd(x) scanf("%d",&x);
typedef long long LL;
const int N=30010;
int n=30000;
int dis[N],fa[N],cnt[N];
int find(int x){
	if(x==fa[x]) return x;
	int f=find(fa[x]);
	dis[x]+=dis[fa[x]];
	fa[x]=f;
	return fa[x];
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy) return;
	fa[fy]=fx;
	dis[fy]=cnt[fx];
	cnt[fx]+=cnt[fy];
} 
int main(){
	for(int i=1;i<=n;i++) fa[i]=i,dis[i]=0,cnt[i]=1;
	int p;scanf("%d",&p);
	while(p--){
		char s[5];int x,y;
		scanf("%s",s);
		if(s[0]=='M'){
			scanf("%d%d",&x,&y);
			merge(x,y);
		} else {
			scanf("%d",&x);
			int fx=find(x);
			printf("%d\n",cnt[fx]-dis[x]-1);
		} 
	}
	return 0;
}

```

---

## 作者：让风忽悠你 (赞：3)

[原题](https://www.luogu.com.cn/problem/P5092)

## 题意
用一些方块组成一些立方柱，并执行以下操作
1. 移动（$M$）：将包含 $X$ 的立方柱移动到包含 $Y$ 的立方柱上。
1. 统计（$C$）：统计含 $X$ 的立方柱中，在 $X$ 下方的方块数目。

## 输入格式
- 第一行输入指令数 $q$。
- 接下来 $q$ 行每行一个指令，形如 M X Y 或 C X。

## 做法

- 对于每个方块，记录下这个方块所在的立方柱的底部节点，这个方块和底部节点之间相隔多少方块，以及所在立方柱大小。
- 每次合并含 $X$ 的立方柱和含 $Y$ 的立方柱的时候，将含 $X$ 的立方柱放在含 $Y$ 的立方柱上面，即将含 $X$ 的立方柱的底部节点变为含 $Y$ 的立方柱的底部节点，并维护各项数值，具体见代码。

## 代码
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#define N 30005

using namespace std;

int t;
int f[N],pre[N],num[N];
// f[i]表示方块i所在立方柱的底部节点。
// pre[i]表示方块i和所在立方柱底部节点的距离。
// num[i]表示方块i所在立方柱的大小。 

int find(int x){
	if(x==f[x])
		return x;
	int fx=find(f[x]);
	pre[x]+=pre[f[x]];
	return f[x]=fx;
}

int main(){
	scanf("%d",&t);
	for(int i=1;i<=N;i++){
		f[i]=i;
		num[i]=1;
	}
	char opt;
	int x,y;
	for(int i=1;i<=t;i++){
		scanf(" %c%d",&opt,&x);
		int fx=find(x);
		if(opt=='M'){
			scanf("%d",&y);
			int fy=find(y);
			f[fx]=fy;
			pre[fx]+=num[fy];
			num[fy]+=num[fx];
			num[fx]=0;
			// 合并操作。 
		}
		else printf("%d\n",pre[x]); //查询 
	}
	return 0;
}
```


---

## 作者：__wfx (赞：3)

这道题自然是加权并查集

我们在查找时维护一个dis是这个点到根之间一共有多少个方块



得到了核心代码之一

```cpp
inline int find(int x){
    if(x == fa[x]) return x;
    int t = find(fa[x]);
    dis[x] += dis[fa[x]];// 查找时处理一下x到根之间有多少个方块 
    fa[x] = t;
    return t;
}
```

在合并时维护一个根的siz

得到了核心代码之二

```cpp
inline void M(int x,int y){
    int fa_a = find(x),fa_b = find(y);
    fa[fa_b] = fa_a;
    dis[fa_b] = siz[fa_a];  
    siz[fa_a] += siz[fa_b];// 合并时维护这根柱子有多少个方块 
    return;
}
```

完整代码

码风非常丑QAQ
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<queue>
#include<ctime>
#include<list>
#include<bitset>
#define ll long long
#define N 30100
#define IL inline
using namespace std;
inline ll read()
{
 	ll res=0,bo=1;
 	char ch=getchar();
 	while(ch<'0'||ch>'9'){if(ch=='-')bo=-1;ch=getchar();}
 	while(ch>='0'&&ch<='9'){res=(res<<1)+(res<<3)+ch-'0';ch=getchar();}
 	return bo*res;
}
ll fa[N],dis[N],siz[N],n,p;
char ch;
inline int find(int x){
    if(x == fa[x]) return x;
    int t = find(fa[x]);
    dis[x] += dis[fa[x]];// 查找时处理一下x到根之间有多少个方块 
    fa[x] = t;
    return t;
}
inline void M(int x,int y){
    int fa_a = find(x),fa_b = find(y);
    fa[fa_b] = fa_a;
    dis[fa_b] = siz[fa_a];  
    siz[fa_a] += siz[fa_b];// 合并时维护这根柱子有多少个方块 
    return;
}
inline void C(int x){
    int fa_a = find(x);
    printf("%lld\n",(siz[fa_a] - dis[x] - 1));
    return;
}
int main()
{
    p = read();
    for(int i = 0;i <= 30010;i++)//初始化 
        fa[i]=i,siz[i]=1;
    for(int i = 1;i <= p;i ++){
        int x,y;
        cin>>ch>>x;
        if(ch == 'C') {
            C(x);//查询 x下面有多少方块 
            goto LZWFX;
        }
        cin>>y;
        if(ch == 'M') 
            M(x,y);
        LZWFX:;
    }	
    return 0;
}
```
这是蒟蒻发的第一篇题解希望给过


---

## 作者：Usada_Pekora (赞：2)

看上去好像没有什么思路

首先我们可以思考一下我们需要什么信息

某个方块前面有多少个

某一堆方块有多少个

那么对于集合中的每个元素，我们都记录它前面有多少个

对于每个集合的根，我们记录该集合有多少个元素


```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=30005;
int A[Maxn],B[Maxn],fa[Maxn];//A数组：该方块前面有多少个方块，B数组：该堆方块共有多少方块
int getfa(int x){
	if (fa[x]==x) return x;
	int tmp=getfa(fa[x]);
	A[x]+=A[fa[x]];
	return fa[x]=tmp;
}
void Union(int x,int y){
	int fx=getfa(x),fy=getfa(y);
	if (fx!=fy) {
		fa[fx]=fy;
		A[fx]+=B[fy];
		B[fy]+=B[fx];
	}
}
int main(){
//	freopen("cubes.in","r",stdin);
//	freopen("cubes.out","w",stdout);
	ios::sync_with_stdio(false);
	int P;
	cin>>P;
	for (int i=1;i<=Maxn;i++) fa[i]=i,A[i]=0,B[i]=1;
	for(int i=1;i<=P;i++){
		char c;
		int x,y;
		cin>>c;
		if (c=='M'){
			cin>>x>>y;
			Union(x,y);
		}
		else {
			cin>>x;
			getfa(x);
			printf("%d\n",A[x]);
		}
	}
	return 0;
}
```

---

## 作者：Sham_Sleep (赞：2)

(*需前置并查集知识）

（u1s1，其实就是[NOI2002](https://www.luogu.com.cn/problem/P1196)原题（确信））

并查集延伸题

由题目描述可以很明显可以看出，就是不断将一条链（也可以说是树）合并。

我们知道并查集可以合并两棵树的根节点。但如何处理上下方块个数呢？

其实只需要储存每个链的长度，合并的时候把父亲的长度加给儿子。

但是该问题要求的是到儿子的距离怎么办？

很简单，倒过来，把放在下面的方块看做父亲，就可以求出底下方块个数

上代码：

![](https://cdn.luogu.com.cn/upload/image_hosting/a02j0act.png)


---

## 作者：StudyingFather (赞：2)

[银河英雄传说](https://www.luogu.org/problemnew/show/P1196) 是一道与这题非常相似的题目。

在进行合并操作时，我们只需要找到两堆方块中最上面的方块进行合并，并更新该方块在该堆方块中的位置，新形成堆的方块总数，这样就实现了合并操作。

而在查询时，我们在进行路径压缩操作的同时，需要同时更新所查询的方块在该堆方块的位置。
```
#include <cstdio>
#include <algorithm>
using namespace std;
int fa[30005],order[30005],num[30005];//fa代表它的
int find(int x)
{
 if(x==fa[x])return x;
 int a=find(fa[x]);
 order[x]+=order[fa[x]];
 return fa[x]=a;
}
void unionn(int x,int y)
{
 order[x]+=num[y];
 fa[x]=y;
 num[y]+=num[x];
 num[x]=0;
}
void init()
{
 for(int i=1;i<=30000;i++)
  fa[i]=i,num[i]=1;
}
int main()
{
 int t;
 scanf("%d",&t);
 init();
 for(int i=1;i<=t;i++)
 {
  int x,y;
  char op[5];
  scanf("%s",op);
  if(op[0]=='M')
  {
   scanf("%d%d",&x,&y);
   unionn(find(x),find(y));
  }
  else
  {
   scanf("%d",&x);
   find(x);
   printf("%d\n",order[x]);
  }
 }
 return 0;
}
```

---

## 作者：QMQMQM4 (赞：1)

# 题解 p5092

~~此题和 p2342叠积木 以及 NOI2002 银河英雄列传思路相同~~

### 考点 ： 并查集（还用说

最开始我只想到维护每个积木下面的积木的个数，然后样例怎么调都是输出0。
于是就想用另一个数组维护该积木上（包含他自己）有多少个积木，命名为$l[i]$来辅助最后的答案数组$d[i]$的更新。

#####  $d[i]$:他下面有几个积木
#####  $l[i]$:他上面有几个积木（包括他自己

#### 方便起见
我们直接把最下面一个积木作为根，这样可以直接更新$l[i],d[i]$。

### CODE

```
#include<cstdio>
#include<iostream>
using namespace std;

const int maxn = 5e5+5;
int fa[maxn],d[maxn],l[maxn],n,p;

inline int read()
{
	char c = getchar();int x = 0,f = 1;
	while(c<'0'||c>'9') {if(c=='-')f = -1;c = getchar();}
	while(c>='0'&&c<='9') {x = x*10+c-'0';c = getchar();}
	return x*f;
}

//路径压缩+带权并查集标准写法，由于d[i]维护答案，直传它的值
int find(int x)
{
	if(x==fa[x])
		return x;
	int last = find(fa[x]);
	d[x] += d[fa[x]];
	return fa[x] = last;
}

//因为选用了最下面一个积木作为根，所以要用祖先来更新。
void update(int x,int y)
{
	x = find(x);y = find(y);
	if(x!=y)
	{
		fa[x] = y;
		d[x] = l[y];
		l[y] += l[x];
	}
}

int main()
{
	for(int i = 1;i<=maxn;++i)
		fa[i] = i,l[i] = 1;
	int p = read();
	for(int i = 1;i<=p;++i)
	{
		char c; cin >> c;
		if(c=='M')
		{
			int x = read();int y = read();
			update(x,y);
		}
		else
		{
			int x = read();
			find(x);
			printf("%d\n",d[x]);
		}
	}
	return 0;
}
```
~~强烈推荐手推一下合并过程，瞬间清晰~~




---

## 作者：羚羊WANG (赞：0)

相信大家看到这里的时候，对题目意思已经深刻的理解

题目当中有两个操作

$1.$把一个柱子上的立方体移动到另一个柱子上

$2.$求给定柱子上的立方体个数

**合并区间?求区间个数?**

这不是~~并查集~~吗

当要进行移动操作的时候：

我们就可以将要操作的两个柱子进行区间合并

当要进行查找立方体个数时

简单的并查集已经无法完成

这时，我们可以新开一个$len$数组，来存储区间大小

因为加了$len$数组，所以操作都进行了一些细微的变化

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
int fa[30110];
int dis[30110];
int lenn[30110];
inline int change(int x){
	if(fa[x]==x)
		return x;
	int findx;
	findx=change(fa[x]);
	dis[x]+=dis[fa[x]];
	fa[x]=findx;
	return findx;
}
inline void update(int x,int y){
	int fax;
	int fay;
	fax=change(x);
	fay=change(y);
	fa[fax]=fay;
	dis[fax]+=lenn[fay];
	lenn[fay]+=lenn[fax];
}
inline void query(int x){
	int tot;
	tot=change(x);
	write(dis[x]);
	puts("");
}
signed main(){
	n=read();
	for(register int i=1;i<=30010;++i)
		fa[i]=i;
	for(register int i=1;i<=30010;++i)
		lenn[i]=1;
	for(register int i=1;i<=n;++i)
		{
			char c;
			cin>>c;
			if(c=='M')
				{
					int x;
					int y;
					x=read();
					y=read();
					update(x,y);	
				}
			else
				{
					int x;
					x=read();
					query(x);
				}
		}
	return 0;
}

```


---

## 作者：novax (赞：0)

本题是一道**带权并查集**的题目，不了解并查集的可以先做一下[并查集模板](https://www.luogu.com.cn/problem/P3367)。

#### 题意
有 $n$ 个方块，进行 $P$ 次操作：将包含 $X$ 的立方柱移动到包含 $Y$ 的立方柱上或统计含 $X$ 的立方柱中，在 $X$ 下方的方块数目。

#### 思路
我的写法与多数题解不同，以顶端的方块为根。在标准并查集只有 $father$ 的基础上，增加两个数组，分别为 $size$ 和 $value$。$size_i$表示以 $i$ 为祖宗的集合的大小，即 $i$ 号方块及下方的方块数；$value_i$ 则表示 $i$ 元素的权值，在本题中即为 $i$ 号方块上方的方块数。

带权并查集的 $find$ 函数除普通并查集的路径压缩外，还要给每个节点的权值加上其父亲的权值，因为是自下而上找。

对于移动操作，先找到 $X$ 和 $Y$ 的祖先 $fx,fy$。$fx,fy$ 为$X,Y$所在方块柱顶端的方块编号，$size_{fx},size_{fy}$ 即为 $X,Y$ 所在方块柱的方块数量。将 $X$ 移动到 $Y$ 上，$X$ 所在方块柱子的顶端即 $fx$ 下方的方块数要增加 $Y$ 所在的柱子的方块数；$Y$ 所在方块柱顶端的上方多了 $X$ 所在方块柱的方块数。用语言描述很麻烦，这个过程写成算式就是： $size_{fx}=size_{fx}+size_{fy}$ 和 $value_{fy}=size_{fx}$。然后合并 $fx,fy$ 两个集合。

对于查询操作，因为对 $size$ 的修改都在祖先上，因此不能直接输出 $size_X$ 而是 $size_{fx}-value_{x}-1$，即 $X$ 所在方块柱的方块总数- $X$ 上方的方块数-自己的值。这里的 $value_X$ 可以直接用是因为在 $find$ 的过程中已经被赋值了。

#### 代码

代码中 $F,S,U$ 分别对应前文 $father,size,value$。

本文代码并查集的 $find$ 函数写了使用递归和非递归的两种不同写法，因而略长。

```cpp
#include <cstdio>
int F[30001];//编号为i的节点的父亲编号 
int S[30001];//编号为i的节点下面的方块个数 
int U[30001];//编号为i的节点的权值 
int find1(int p)//寻找p的祖宗节点+路径压缩-递归写法 
{
	int fp=F[p];
	if(fp!=p)
	{
		F[p]=find1(F[p]);
	} 
	U[p]+=U[fp];
	return F[p];
} 
int st[30001];//栈-左闭右闭区间 
int find2(int p)//寻找p的祖宗节点+路径压缩-循环写法 
{
	int L;
	L=0;
	while(F[p]!=p)
	{
		st[++L]=p;//向上跳一步
		p=F[p]; 
	}
	int i;
	int x;
	int sum;
	sum=0;
	for(i=L;i>=1;i--)//路径压缩 
	{
		U[st[i]]+=U[F[st[i]]];
		F[st[i]]=p;//将栈中的所有元素的父节点指向p的祖宗 
	}
	return p; 
} 
int main()
{
	int P;
	int i;
	for(i=1;i<=30000;i++)
	{
		F[i]=i;
		S[i]=1;//只有本身一块
		U[i]=0;//上方没有节点 
	}
	scanf("%d",&P);
	char str[5]; 
	int x,y;
	int fx,fy; 
	while(P--)
	{
		scanf("%s",str);//字符串读入 
		if(str[0]=='M')//合并 
		{
			scanf("%d%d",&x,&y);
			fx=find2(x);//寻找x和y的祖宗 
			fy=find2(y);
			if(fx==fy)
			{
				continue;
			} 
			U[fy]=S[fx];//合并后y上方有S[fx]个方块 
			S[fx]+=S[fy];//这个祖宗下面多了y方块所在柱子的方块数 
			F[fy]=fx;//y方块的父亲节点设置为x的祖宗 
		} 
		else
		{
			scanf("%d",&x);
			printf("%d\n",S[find2(x)]-U[x]-1);//x所在柱子的方块数-x上方的方块数-x本身=x方块下方的方块数 
		}
	} 
} 
```


---

## 作者：SymphonyOfEuler (赞：0)

（又）一道带权并查集好题。

众人所知，普通并查集不可以处理边权问题，于是聪明的人类发明了有权的并查集。就是在father数组的基础上，加了siz数组和dis数组。

在银河英雄传说那题里：

father[i]表示i点的直接所在的队头

dis[i]表示i点到父亲的距离

size[i]表示i点父亲所在的队的舰船数量

这个跟这题的思路差不多。

给我们两个操作，第一个就是普普通通的合并操作，第二个让我们求的其实是x点到父亲的距离。输出dis[x]即可？？

答案是不能，18分。

玄学的坑点来了：千万不要忘了查询前要把权往下传。

然后就是AC代码了。

```
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 30005;

int T;

int fa[MAXN], dis[MAXN], siz[MAXN];

int find(int x) {
    if (fa[x] == x) return x;
    int father = fa[x];
    fa[x] = find(father);
    dis[x] += dis[father];
    return fa[x];
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    fa[fx] = fy;
    dis[fx] += siz[fy];
    siz[fx] += siz[fy];
    siz[fy] = siz[fx];
}

void init() {
    for (int i = 1; i <= MAXN; ++i) {
        fa[i] = i;
        siz[i] = 1;
    }
}

int main() {
    init();
    cin >> T;
    while (T--) {
        char c;
        int x, y;
        cin >> c;
        if (c == 'M') {
            cin >> x >> y;
            merge(x, y);
        }
        if (c == 'C') {
            cin >> x;
            find(x);
            cout << dis[x] << '\n';
        }
    }
    return 0;
}
```


---

## 作者：gSE2xWE (赞：0)

[更好的阅读体验](https://www.cnblogs.com/loney-s/p/12940029.html)

# 题目

[传送门](https://www.luogu.com.cn/problem/P5092)

# 思路

我们单独考虑如果将包含$x$的立方柱移动包含$y$的立方柱上会有什么影响

首先对于原来的包含$y$的立方柱，所有的答案都不会发生任何变化

对于包含$x$的立方柱，他们所有的答案都会加上包含$y$的立方柱的大小

简单的去考虑，这道题可以用平衡树去做

毕竟操作只有求值，平衡树的合并，区间加法

时间复杂度为$O(nlog_n)$

本篇博客主要介绍带权冰茶姬的做法

其实也差不多，

因为每一次的操作都是针对整个冰茶姬进行操作

所以我们所有的操作都可以直接打到根上，

在$findset$操作的时候用父亲节点的信息进行维护

至于$size$的维护更简单

只有在合并两个冰茶姬的时候维护一下就可以了

# 代码

```cpp
#include<iostream>
using namespace std;
int n;
int fa[30005];
int siz[30005];
int ans[30005];
char opt;
inline void makeset(int n)
{
	for(int i=1;i<=30000;i++)
	{
		fa[i]=i;
		siz[i]=1;
		ans[i]=0;
	}
}
inline int findset(int u)
{
	if(fa[u]==u)
		return u;
	int t=fa[u];
	fa[u]=findset(fa[u]);
	ans[u]+=ans[t];
	return fa[u];
}
inline void unionset(int a,int b)
{
	int u=findset(a);
	int v=findset(b);
	if(u==v)
		return;
	fa[v]=u;
	ans[v]+=siz[u];
	siz[u]+=siz[v];
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	makeset(n);
	for(int i=1,u,v;i<=n;i++)
	{
		cin>>opt;
		if(opt=='M')
		{
			cin>>u>>v;
			unionset(v,u);
		}
		else
		{
			cin>>u;
			findset(u);
			cout<<ans[u]<<endl;
		}
	}
	return 0;
}
```



---

## 作者：Snow_Dreams (赞：0)

这道题是明显的并查集，但和普通的并查集不太一样

题意：
```latex
移动（M）：将包含 X 的立方柱移动到包含 Y 的立方柱上。
统计（C）：统计含 X 的立方柱中，在 X 下方的方块数目。
```
然后就不难发现，M操作是将两个积木堆合并，也就是并查集的合并操作，C操作是一个查询工作

这个地方要用带权并查集的思路去做，因为C操作不是去求集合里面的元素个数而是部分，所以就需要用一个另外的方式来维护这些信息

下面先放一下代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 500010;
int t;
int fa[N], d[N], size[N];
int find(int x)
{
	if(fa[x] == x) return x;
	int root = fa[x];
	fa[x] = find(fa[x]);
	size[x] = size[fa[x]];
	d[x] += d[root];
	return fa[x];
}
int main()
{
	for(int i = 1;i <= N;i++) fa[i] = i, size[i] = 1;
	scanf("%d",&t);
	for(int i = 1;i <= t;i++){
		char s;cin >> s;
		int x, y;
		if(s == 'M'){
			scanf("%d%d",&x, &y);
			x = find(x), y = find(y);
			fa[x] = y;
			d[x] = size[y];
			size[y] += size[x];
			size[x] = size[y];
		}else{
			scanf("%d",&x);
			find(x);
			printf("%d\n",d[x]);
		}
	}
	return 0;
}
```
在这里，fa数组表示节点父亲，d数组表示边权，d[i]保存了位于编号i的积木下方的积木个数

size数组则表示每个集合的大小

还有一个我要建议的是增强代码可读性，不要把一些操作写在一起，不容易调试

---

