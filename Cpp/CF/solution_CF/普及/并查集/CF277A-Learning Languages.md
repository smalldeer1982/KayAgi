# Learning Languages

## 题目描述

The "BerCorp" company has got $ n $ employees. These employees can use $ m $ approved official languages for the formal correspondence. The languages are numbered with integers from $ 1 $ to $ m $ . For each employee we have the list of languages, which he knows. This list could be empty, i. e. an employee may know no official languages. But the employees are willing to learn any number of official languages, as long as the company pays their lessons. A study course in one language for one employee costs $ 1 $ berdollar.

Find the minimum sum of money the company needs to spend so as any employee could correspond to any other one (their correspondence can be indirect, i. e. other employees can help out translating).

## 说明/提示

In the second sample the employee $ 1 $ can learn language $ 2 $ , and employee $ 8 $ can learn language $ 4 $ .

In the third sample employee $ 2 $ must learn language $ 2 $ .

## 样例 #1

### 输入

```
5 5
1 2
2 2 3
2 3 4
2 4 5
1 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
8 7
0
3 1 2 3
1 1
2 5 4
2 6 7
1 3
2 7 4
1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 2
1 2
0
```

### 输出

```
1
```

# 题解

## 作者：⚡LZSY01_XZY⚡ (赞：20)

这道题目和[BZOJ3296](https://www.lydsy.com/JudgeOnline/problem.php?id=3296)类似，但又不尽相同。  

首先，BZOJ题数据要大特别多。其次，BZOJ不用考虑没有人会语言的情况。  
这题特别坑的地方在于你根本想不到**竟然会有人不会语言**，这时，就要特判。  

题解中的方法都比较麻烦，且不易理解，**特此填坑**。

# 进入正题
对于每一个人，我们把他当做一个点，将他与语言连边，语言所连接的边所连接的人就能够互相交流，人所连接的边所连接的语言就能相互转化。如图：  
![](https://cdn.luogu.com.cn/upload/pic/61412.png)  
上图可以清晰的看出人与语言的关系。  

实际实现中可以用并查集来模拟连边。将并查集分为两部分$1...n$记录人，$n+1...n+m$记录语言，将人与对应的语言并入同一个集合中，最后统计集合个数，只有语言就不用统计了。  
在统计集合的过程中有一个小小的优化，我们以人为根，最后统计时只要看还有多少人是做的根就可以了。

具体看代码：  
```cpp
#include <cstdio>
#include <cstring>
using namespace std;

int read()
{
	int x=0,f=1;char c=getchar();
	while (c<'0' || c>'9'){if (c=='-')f=-1;c=getchar();}
	while (c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	return x*f;
}

const int MAXM=205;
int n,m,ans;
bool flag;
int f[MAXM];

inline int find(int x)
{
	return f[x]==0?x:f[x]=find(f[x]);
}

inline void together(int x,int y)
{
	int r1,r2;
	r1=find(x);r2=find(y);
	if (r1==r2) return ;
	f[r1]=r2;flag=true;
}

int main()
{
	n=read();m=read();
	memset(f,0,sizeof(f));
//也可以替换成for (int i=1;i<=n+m;i++) f[i]=i; 但这样之后，find()就要改为 return f[x]==x?f[x]=find(f[x]);了。
	for (int i=1;i<=n;i++)
		for (int j=read();j>0;j--) together(read()+n,i);       //以i为根
	for (int i=1;i<=n;i++) if (find(i)==i) ans++;
	if (!flag) ans++;						//全是文盲的特判
	printf("%d\n",ans-1);
	return 0;
}
```
$Please~give~a~like.$  
$OI\text{之路任重道远，诸君还需继续努力！！！}$

---

## 作者：pzc2004 (赞：9)

[题目传送门](https://www.luogu.org/problem/CF277A)

来一发dfs的题解。

和其他题解中讲得一样，将每个语言、每个人都看作一个节点，一个人掌握一门语言就可以表示为将这个人代表的节点与这门语言代表的节点连一条边，只需将所有人都联通即可。

然后分一下类：
1. 如果全是不会语言的人，那么显然需要连总人数条边（每个人都学同一门语言）。
1. 如果有会语言的人，那么只需要连表示人的节点的总连通块数减一条边（将人分成不会语言的和会语言的，不会语言的同上，会语言的只需将它们连成一棵树即可，所以加起来是表示人的节点的总连通块数减一条）。

然后只需要用dfs求出表示人的节点的总连通块数，再根据上述分类操作即可

代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,x,y,s;
vector<int>k[201];//邻接表存图，1-100号节点表示人，101-200号节点表示语言
bool b[201],bb;//b数组代表该节点是否被遍历过，bb代表是否有会语言的人
void dfs(int x)
{
    b[x]=1;//将当前节点标为已遍历
    int i;
    for(i=0;i<k[x].size();i++)if(!b[k[x][i]])dfs(k[x][i]);//遍历与当前节点相连的其他未遍历的节点
}
int main()
{
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&x);
        while(x--)
        {
            scanf("%d",&y);
            k[i].push_back(100+y);//连边
            k[100+y].push_back(i);//连边
        }
    }
    for(i=1;i<=n;i++)
    {
        if(!b[i]){if(k[i].size()>=1)bb=1;s++;dfs(i);}//如果当前节点还没被遍历过，就将连通块数加一，在遍历该节点
    }
    if(bb)s--;//如果有会语言的人，就将答案减一
    printf("%d",s);
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：_HCl_ (赞：7)

# CF277A题解

[CF277A Learning Languages](https://www.luogu.com.cn/problem/CF277A)

**题意简述**

有 $n$ 个人，每个人会说几种语言（也可以一种也不会），为了使这 $n$ 个人之间都可以互相交流（可以通过过中间翻译交流），试求还需要让这些人一共要学多少种语言。

**思路**

我们先把样例2拿来研究一下。

我们可以把每个人和每种语言都看成节点，如果一个人会一种语言，就可以把它看成在这个人的节点和这种语言之间有一条无向边。

于是，我们就可以把样例2的数据绘制成一张图：

![样例2的图](https://cdn.luogu.com.cn/upload/image_hosting/nqtoyv6h.png)

其中 $P$ 是人的节点，$L$ 是语言的节点。

我们发现，图中**同一个连通块内的人节点都是可以互相交流的**（很好理解，也不需要发现）。

那么，如果要使所有人都可以互相交流，就让**所有的人节点都在一个连通块**里就好了。

注意，只需要所有的**人节点**在连通块里就行，假如有没人会的语言，也是不用考虑的！（即允许有独立的语言节点不在联通块内）。

题目让我们所求的是这些人一共要学的语言数，也就是将这些联通块都连起来的最小连边数。如果把每一个连通块都当成一个节点的话，把这些节点都连起来的最小连边数就是**连通块数** $-1$ 了。（还是要提醒：独立的语言节点不算连通块！）

另外，有个地方需要特判：假如没有一个人会一种语言，那么最后的结果就是人数（每个人都学同一种语言）。

**实现**

大概这么几个步骤：

1. 读入
1. 建图
1. 连通块计数
1. 输出

其中建图这一步，我们把人的节点编号是 $1$ 到 $n$，语言的编号是从 $n+1$ 到 $n+m$。

这里我是用邻接表来实现的，当然也可以用前向星或者邻接矩阵实现。（注意建的是无向图）

连通块计数的板子放这了：
```cpp
//dfs部分
void dfs(int x) {
	//v数组标记节点是否被遍历过
	v[x]=1;//访问了x节点，标记打上
	for(int i=0; i<e[x].size(); ++i) {//遍历与x节点相连的所有节点
		if(v[e[x][i]])continue;//如果这个节点已经被遍历过了，就不访问了
		dfs(e[x][i]);//访问这个节点
	}
}
```
```cpp
//主程序部分
for(int i=1; i<=n; ++i)//遍历每个节点
		if(!v[i])//这个节点未被访问
		{
			dfs(i);//访问
			//如果当前节点所在的连通块里的所有节点都被访问完了
			//由于访问过的节点都不在访问
			//dfs就会退出
			cnt++;//连通块的数量+1
		}
```
最后输出的时候记得输出时要记得 $-1$ 和特判。


**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int v[1000001];
vector<int> e[100001];
int n,m,cnt,flag,a,lan;
void dfs(int x) {//连通块板子
	v[x]=1;
	for(int i=0; i<e[x].size(); ++i) {
		if(v[e[x][i]])continue;
		dfs(e[x][i]);
	}
}
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; ++i) {
		cin>>a;
		for(int j=1; j<=a; ++j) {
			//flag是特判标记
			flag=1;//排除特判的情况
			cin>>lan;
			e[i].push_back(n+lan);//人的编号是i，语言的编号是n+lan
			e[n+lan].push_back(i);//建的是无向图
		}
	}
	for(int i=1; i<=n; ++i)//独立语言节点不算连通块，所以只遍历到n
		if(!v[i]) dfs(i),cnt++;//连通块板子
	if(flag)cout<<cnt-1;//记得-1
	else cout<<n;//特判
}
```


---

## 作者：Night_fall (赞：4)

[题目传送门](/problem/CF277A)

------------
### 1. 前置知识

[并查集](/blog/688674/search-tree)

------------

看了看题解区，有 dfs 的，有连语言和人的，还有只连人的，那我就来一发只连语言的吧。

------------

### 2.思路

考虑将所有能交流的语言合并。

具体合并方法就是把每个人的每一种语言和这个人的第一种语言合并。

像这样：

```cpp
for(int i=2;i<=n;i++) f[find(a[i])]=find(a[1]);
```

这样就能保证每个人会的所有语言在同一个集中。

然后是查找：

首先定义一个 vis 数组，标记这棵树有没有被检查过。

检查的时候分两种情况：

1. 这个人是文盲，直接让他学，ans++。

2. 这个人不是文盲，并且所在的树还没有被检查过，ans++。

接着是输出：

因为题目问的是要学多少种语言，就是问要连的边数，所以显而易见，要输出连通块个数 -1。

最后是特判，因为所有人都是文盲的话所有人都要学。

------------
### 3.Code

```cpp
#include<iostream>
using namespace std;

int a[110][110];
int f[110];
bool vis[110];

int find(int x){
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) f[i]=i;
    for(int i=1;i<=n;i++){
        cin>>a[i][0]; //存数据
        for(int j=1;j<=a[i][0];j++) cin>>a[i][j];
        for(int j=2;j<=a[i][0];j++) f[find(a[i][j])]=find(a[i][1]); //合并这个人会的语言
    }
    bool flag=1; //判断是否所有人都文盲
    int ans=0;
    for(int i=1;i<=n;i++){ 
        if(a[i][0]==0) ans++; //情况1
        else if(!vis[find(f[a[i][1]])]) flag=0,ans++,vis[find(f[a[i][1]])]=1; //情况2
    }
    cout<<ans-1+flag; //输出，flag就是特判
    return 0;
}
```

---

## 作者：Zvelig1205 (赞：3)

# 并查集判连通块

[题目传送门](https://www.luogu.com.cn/problem/CF277A)

通过题目，可以想到，如果 $A,B$ 有共同语言，那么 $A,B$ 就能直接交流；在此基础上，若 $B,C$ 有共同语言，则 $A,C$ 可以通过 $B$ 作为翻译间接交流。

就是这样：

![](https://pic.imgdb.cn/item/632964ff16f2c2beb1a6f320.png)

而若 $D$ 和 $A,B,C$ 都没有共同语言，那么他们就不可以直接或间接交流：

![](https://pic.imgdb.cn/item/6329657d16f2c2beb1a7f35e.png)

如果想让他们能够交流，就必须有一个人学习另一种语言，如让 $D$ 学习语言 1,2 其中之一，或者让 $A,B,C$ 其中一个人学语言 3。

至于到底学什么，并不是我们所关心的。我们只关心他们能不能交流。

所以也就是同一个连通块里的人可以相互交流。最终要将形成的所有连通块连起来。

不过，孤立的人要算上，但孤立的语言不用算上。

既然是判连通块，很自然想到并查集。这里我们采用最常用的路径压缩并查集，单次 `find` 的时间复杂度 $O(\log n)$。

最后，特判一下全是文盲的情况，这时的最小花费是 $n$ 个人全部去学同一种语言。

AC Code:

```cpp
const int inf=2e2+7;
int n,m,ans,fa[inf];
bool vis[inf],pd=1;
int find(int x){return (fa[x]^x)?(fa[x]=find(fa[x])):(x);}
int main()
{
	n=re();m=re();
	for(int i=1;i<=n+m;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		int k=re();if(k)pd=0;
		for(int j=1;j<=k;j++)
		{
			int ls=re()+n;
			fa[find(ls)]=find(i);
		}
	}
	if(pd){wr(n);return 0;}
	for(int i=1;i<=n;i++)
	{
		int ls=find(i);
		if(vis[ls])continue;
		vis[ls]=1;ans++;
	}
	wr(ans-1);
	return 0;
}
```

但做题永远不是我们的目的，我们的目的是知识。

很多人（包括之前的我）会有这样一个误区，路径压缩之后，并查集的深度会一直为 2。

事实上，并不是。举个浅显的例子，每次合并我都恰好找到两个集合的根，然后将根合并。

所以单纯的路径压缩并查集也可以卡（虽然我不会），想了解的可以自行查找：

<https://www.luogu.com.cn/blog/Atalod/shi-jian-fu-za-du-shi-neng-fen-xi-qian-tan>

<https://oi-wiki.org/ds/dsu-complexity/>

所以有时候我们会选择路径压缩和按秩合并一起执行，这样的每次 `find` 的时间复杂度可以进一步下降到 $O(\alpha(n))$（反阿克曼函数）。

不过，目前为止，我还没有见到过卡路径压缩的题目。

除了路径压缩和按秩合并，还有一种合并方法叫做 **随机合并**，就是随机选两者之中的一个作为新集合的根。

不过好像也可以卡。

一个不是很严谨的证明：

假设要合并的两个树的树高分别是 $x,y(x>y)$，那么合并之后的期望高度是 $x\times0.5+(x+1)\times0.5=x+0.5$，所以每次树高期望增加 0.5，极限树高仍是 $O(n)$。

随机合并：

```cpp
const int inf=2e2+7;
int n,m,ans,fa[inf];
bool vis[inf],pd=1;
int find(int x){return (fa[x]^x)?(find(fa[x])):(x);}
#include<random>
mt19937 rnd(114514);
int main()
{
	n=re();m=re();
	for(int i=1;i<=n+m;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		int k=re();if(k)pd=0;
		for(int j=1;j<=k;j++)
		{
			int ls=re()+n,r1=find(i),r2=find(ls);
			if(rnd()&1)fa[r1]=r2;
			else fa[r2]=r1;
		}
	}
	if(pd){wr(n);return 0;}
	for(int i=1;i<=n;i++)
	{
		int ls=find(i);
		if(vis[ls])continue;
		vis[ls]=1;ans++;
	}
	wr(ans-1);
	return 0;
}
```

双优化：

```cpp
const int inf=2e2+7;
int n,m,ans,fa[inf],siz[inf];
bool vis[inf],pd=1;
int find(int x){return (fa[x]^x)?(fa[x]=find(fa[x])):(x);}
int main()
{
	n=re();m=re();
	for(int i=1;i<=n+m;i++)
		fa[i]=i,siz[i]=1;
	for(int i=1;i<=n;i++)
	{
		int k=re();if(k)pd=0;
		for(int j=1;j<=k;j++)
		{
			int ls=re()+n,r1=find(i),r2=find(ls);
			if(siz[r1]>siz[r2])swap(r1,r2);
			fa[r1]=r2,siz[r2]+=r1;
		}
	}
	if(pd){wr(n);return 0;}
	for(int i=1;i<=n;i++)
	{
		int ls=find(i);
		if(vis[ls])continue;
		vis[ls]=1;ans++;
	}
	wr(ans-1);
	return 0;
}
```

不过本题数据范围过小，并不能看出明显的优化效果。


---

## 作者：Rbu_nas (赞：3)

考虑用并查集维护

为什么是这样呢，题意说的很清楚，相当于是给很多块连边，求最少的数量。那我们就把会同一种语言的放进一个大块中，最后得到 $tot$ 个块就需要 $tot-1$ 条边了

我们具体来分析一下合并的问题。首先没有必要存 $n$ 个人的信息，我们最多只需要 $m$ 个代表，说明有多少不同的语言是**必须**学的。假设 $n$ 个人每个人会的都不同，那就必须有 $n-1$ 个语言得学。每进来一个人，只要会之前存在过的语言就并到那个语言集中，每**成功合并一次**就 $ans--$

另外还有一个大坑就是如果 $n$ 个人没一个会说话就得学 $n$ 个语言

代码:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 103
int n, res;
int vis[N];
//vis[i]记录着会第i种语言的人的编号(1<=i<=n)
//也是指上文中的“代表”

bool NA;
//记录特殊情况(是否需要学n种语言)

struct unionFindSet
{
    int fa[N];
    inline void clear()
    {
        for(int i=1; i<=n; ++i) fa[i]=i;
        return ;
    }

    int find(int x)
    {
        if(fa[x] == x) return x;
        return fa[x]=find(fa[x]);
    }

    inline void unite(int x, int y)
    {
        int fx=find(x), fy=find(y);
        if(fx != fy) fa[fx]=fy, --res;
        //注意必须是成功合并一次才ans--
        return ;
    }
} T;

int main(void)
{
    scanf("%d%*d", &n);
    T.clear(); res=n-1;
    //把ans赋初值，就是最多需要的语言数
    for(int i=1; i<=n; ++i)
    {
        int cnt, x; scanf("%d", &cnt);
        if(cnt && !NA) NA=true;
        //如果有一个人会说话，就不需要n种语言
        while(cnt--)
        {
            scanf("%d", &x);
            if(vis[x]) T.unite(vis[x], i);
            else vis[x]=i;
        }
    }
    printf("%d", NA ? res : n);
    //最后判断一下就好了
    return 0;
}

```

---

## 作者：liuyifan (赞：3)

## 一道[并查集](https://www.luogu.org/problemnew/show/P3367)的模版题

思路:将会说同一种语言的人都分到同一个集合内,然后直接统计即可

不会并查集的新人(~~应该没有~~)看[这个](https://www.cnblogs.com/douzujun/p/6402312.html),顺便可以A掉[【模板】并查集](https://www.luogu.org/problemnew/show/P3367)

code:(注释在下面)
```
// luogu-judger-enable-o2
#include<bits/stdc++.h>//万能头文件 
#define reg register//将变量存入CPU缓存,有~~玄学~~的加速作用 
#define next liuyifan_next//防止炸变量名(本人因此CE多次) 
using namespace std;
int prt[10000000],a[10000000],k,f,next,n,m,cnt,ans;//开大点防爆 
//prt:每个点的father节点
//a:输入数据
inline int GF(reg int x)
{
    if(prt[x]==x)return x;
    return prt[x]=GF(prt[x]);
}//getfather的缩写,路径压缩 
inline void add(reg int u,reg int v)
{
    int x=GF(u),y=GF(v);//判断是否已经在同一集合
    if(x!=y)prt[x]=y;
}//连边 
inline bool panduan(reg int x,reg int y)
{
    if(GF(x)==GF(y))return 1;//father是否相同
    else return 0;
}//判断在不在一份集合(好像这道题不需要)
int mian()//仔细看,有没有问题?
{
    scanf("%d%d",n,m);
    for(reg int i=1;i<=max(n,m);i++)prt[i]=i;//max(n,m)更保险
    for(reg int i=1;i<=n;i++)
    {
        scanf("%d",k);//输入他会的语言的种数
        if(k==0)//如果一门也不会就必须学一门 
        {
            ans++;//要学的语言的个数 
            continue;//直接跳过,后面没有输入和运算了 
        }
        scanf("%d",f);
        a[f]++;//输入掌握的语言 
        for(reg int i=1;i<k;i++)
        {
            scanf("%d",&next);
            a[next]++;
            add(f,next);
        }//并查集连边 
    }
    for(reg int i=1;i<=m;i++)
    {
        if(a[i]==0)cnt++;
        if(prt[i]==i)//集合个数
		//father为自己的点的个数就是集合的个数 
        ans++;
    }
    printf("%d\n",cnt==m?n:ans-cnt-1);//输出结果
	//ans-cnt-1：交流的最小花费 
	//cnt: 集合的个数 
    return 0;//不写return 1就行 
```
Ps:[AC提交记录](https://www.luogu.org/record/show?rid=14119333)
[CE提交记录](https://www.luogu.org/record/show?rid=14119283)
### 再次警告:变量名不要开next和y1等！不然爆0！
## 拒绝抄袭,共建和谐洛谷

---

## 作者：Larry76 (赞：2)

## 题目大意：
有 $n$ 名员工，一共有 $m$ 种语言，每名员工都会其中 $k_i$ 种语言（$m \ge \boldsymbol{k_i \ge 0}$），现规定两名员工可以交流的条件如下：
1. 两名员工会一种及以上共同的语言。
2. 有一名员工可以当这两名员工的翻译（即有一名员工会这两名员工会的语言中的各一种）。

问**每位员工**所需要学习的语言数的和为多少。

## 题目分析：
我们可以对能够交流的员工建图，然后不难发现以下性质：
1. 若 $A$ 可以和 $B$ 交流，则 $B$ 也可以和 $A$ 交流（即无向性）。
2. 若 $A$ 可以和 $B$ 交流，$B$ 可以和 $C$ 交流，则 $A$ 也可以和 $C$ 交流（即传递性）。

所以，此时的问题就变成了给定一张无向图，问加几条边能够使其成为一张连通图。

可能有更好的做法，但我的做法如下：
1. 若该点表的员工一种语言也不会，则 $cnt$ 加一。
2. 若该点没有被访问过，且该点表示的员工至少会一种语言，则 $cnt$ 加一，然后以该点为起点进行 $\operatorname{dfs}$。
3. 若该点被访问过，则跳过。

此时答案是 $cnt - 1$。

注意：若没有员工会语言，则此时的答案是 $cnt$ 而不是 $cnt-1$，因为每一名员工都要学一种语言才能交流。

综上，时间复杂度 $O(n \times m)$，主要取决于建图部分的时间复杂度。

## 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define TIME_LIMIT (time_t)1e3
#define dbg(x) cerr<<#x<<": "<<x<<endl;
#define MAX_SIZE (int)2.1e4
vector <int> hashtable[MAX_SIZE];
unordered_map <int, bool> edges;
int head[MAX_SIZE];
int ver[MAX_SIZE];
int Next[MAX_SIZE];
int tot = 0;
void add(int u,int v){
    ver[++tot] = v;
    Next[tot] = head[u];
    head[u] = tot;
}
bitset<MAX_SIZE>vis;
bitset<MAX_SIZE>pass;
void dfs(int step, int u, int fa){
    assert(step<=114);
    vis[u] = 1;
    for(int i=head[u];i;i=Next[i]){
        int v = ver[i];
        if(v==fa)
            continue;
        if(v==u)
            continue;
        if(!vis[v])
            dfs(step+1,v,u);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    #undef cout
    #undef cin
    ifstream cin("in.in");
    ofstream cout("out.out");
    assert(cin.is_open());
    assert(cout.is_open());
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdin);
    time_t cs = clock();
#endif
//========================================
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int lang;
            cin>>lang;
            hashtable[lang].push_back(i);
        }
    }
    for(int i=1;i<=m;i++){
        auto &vec = hashtable[i];
        if(vec.empty())
            continue;
        int u = vec[vec.size()-1];
        pass[u] = 1;
        vec.pop_back();
        for(auto v:vec){
            if(!edges[min(u,v)*100+max(v,u)]){
                add(u,v);
                add(v,u);
                pass[v] = 1;
                edges[min(u,v)*100+max(v,u)] = 1;
            }
        }
    }
    int cnt = 0;
    for(int i=1;i<=n;i++) {
        if(!vis[i]&&pass[i]){
            dfs(1,i,i);
            ++cnt;
        }
    }
    int nothing = 0;
    for(int i=1;i<=n;i++)
        if(!pass[i])
            ++nothing;
    if(nothing==n)
        cout<<nothing;
    else
        cout<<nothing+cnt-1;
//========================================
#ifdef LOCAL
    cin.close();
    cout.close();
    time_t ce = clock();
    cerr<< "Used Time: " << ce-cs << " ms."<<endl;
    if(TIME_LIMIT<ce-cs)
        cerr<< "Warning!! Time exceeded limit!!"<<endl;
#endif
    return 0;
}
```

---

## 作者：Nozebry (赞：2)

## $Problems$
$BerCorp$ 公司有 $n$ 个人,他们总共会 $m$ 种语言。

现在给出每个人会的语言(也可能一种都不会)，问你最少让几个人学语言,就可以使得大家可以互相沟通。
## $Answer$
显而易见，这是一道并查集的经典例题，是可以直接套模板的。

我们可以拿 $m$ 种语言来当任意一个集合的首，然后发现会这个语言的人，就把这个人归入该集合。

当所有人都已经被归入相应的集合后，我们就可以直接查找哪些人需要学习语言，人后输出就可以了。
### $Episode$
并查集的 $2$ 种操作：

$No.1:$
$find$ 操作，用来确定任意元素属于哪一个子集。

#### 模板：
```pascal
function find(x:longint):longint;
begin
    if (x=a[x]) then exit(x);
    f[x]:=find(x);
    exit(f[x]);
end;

 ```
 $No.2:$$union$ 操作，先判断需要判断的两个元素所属的集合，若不为同一个集合，进行合并。
 
 #### 模板：
 ```pascal
 procedure union(x,y:longint);
begin
    x:=find(x);y:=find(y);
    if (x<>y) then a[x]:=y;
end;
 ```

---

## 作者：vandijk (赞：1)

题意:

BerCorp公司有n名雇员。这些雇员共掌握m种官方语言（以从1到m的整数编号）用于正式交流。对于每个雇员，我们有一个他掌握的语言列表，列表可以为空，这意味着一个雇员可能不掌握任何官方语言。但是雇员们愿意学习语言，只要公司为课程付费。每名雇员学习一种语言需要花费 1 Ber元。

请找出能让所有雇员直接或间接（可由其他雇员提供中间翻译）交流的最小花费。

思路很简单，我们可以dfs把每个连通块（可以互相交流的人群）求出来，然后答案就是连通块的数量-1，但是有一种特判的情况，要特判有不会语言的人。如果有不会任何一项语言的人，那答案就是连通块的数量。

上代码。

```
#include <bits/stdc++.h>
using namespace std;
int n,m;
int k[110];
vector<int> G[110];
vector<int> v[110];
bool vis[110];
void dfs(int x)//dfs
{
	vis[x]=1;
	for(int i=0;i<v[x].size();i++)
	{
		if(!vis[v[x][i]])
		{
			dfs(v[x][i]);
		}
	}
}
int main()
{
	cin>>n>>m;
	bool ok=0;
	for(int i=1;i<=n;i++)
	{
		cin>>k[i];
		if(k[i]!=0)ok=1;
		for(int j=0;j<k[i];j++)
		{
			int tmp;
			cin>>tmp;
			G[tmp].push_back(i);//语言连通块
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<G[i].size();j++)
		{
			for(int k=0;k<G[i].size();k++)
			{
				if(j==k)continue;
				v[G[i][j]].push_back(G[i][k]);//人群连通块
			}
		}
	}
	bool flag=0;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			dfs(i);
			cnt++;
		}
	}
	if(ok)cout<<cnt-1<<endl;
	else cout<<cnt<<endl;
	return 0;
}
```


---

