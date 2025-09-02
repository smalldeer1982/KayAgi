# [USACO1.3] 虫洞 wormhole

## 题目描述

Farmer John 周末进行高能物理实验的结果却适得其反，导致 $n$ 个虫洞出现在农场上，农场是一个二维平面，没有两个虫洞处于同一位置。

根据他的计算，FJ 知道他的虫洞两两配对，形成 $\dfrac{n}{2}$ 对配对。例如，如果 $A$ 和 $B$ 的虫洞连接成一对，进入虫洞 $A$ 的任何物体将从虫洞 $B$ 出去，方向不变；反之亦然。  

然而这可能发生相当令人不快的后果。例如，假设有两个成对的虫洞 $A(1,1)$ 和 $B(3,1)$，Bessie 从 $(2,1)$ 开始朝着 $x$ 正方向移动。Bessie 将进入虫洞 $B(3,1)$，从 $A(1,1)$ 出去，然后再次进入 $B$，困在一个无限循环中！

FJ 知道他的农场里每个虫洞的确切位置。他知道 Bessie 总是向 $x$ 正方向走进来，虽然他不记得贝茜的当前位置。  

请帮助 FJ 计算有多少种虫洞配对方案，使得存在一个位置，使得 Bessie 从该位置出发，会被困在一个无限循环中。

## 说明/提示

### 数据范围
对于 $100\%$ 的数据，$2\le n \le 12$，$0 \le x,y \le 10^9$。  
保证 $n$ 为偶数。

### 样例解释

将虫洞编号为 $1 \sim 4$，然后通过将 $1,2$ 和 $3,4$ 匹配，如果 Bessie 从 $(0,0)$ 到 $(1,0)$ 之间的任意位置出发，她会陷入无限循环中。

相似的，在相同的起始点，如果配对是 $1,3$ 和 $2,4$，贝茜也会陷入循环。（如果贝西从 $3$ 进去，$1$ 出来，她会走向 $2$ ，然后被传送到 $4$，最后又回到 $3$）

仅有 $1,4$ 和 $2,3$ 的配对允许贝茜从任何二维平面上的点向 $x$ 正方向走，而不出现无限循环。

题面翻译摘自 NOCOW

## 样例 #1

### 输入

```
4
0 0
1 0
1 1
0 1```

### 输出

```
2```

# 题解

## 作者：「QQ红包」 (赞：50)

先枚举所有的匹配方式，然后匹配完之后dfs搜找环，具体见代码

```cpp
/*
ID: ylx14271
PROG: wormhole 
LANG: C++
 */
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
struct node
{
    int x;int y;
} a[30];
int b[30];
int ans;
bool cmp(node aa,node bb)//排序 
{
    if (aa.y==bb.y) return aa.x<bb.x;
    return aa.y<bb.y;
}
int f(int num,int d,int begin,int p1)//检查，num只是用来标记的 
{ //begin,记录开始位置，用来判断是否回到原点了，
//p1=1：走的方式到达点d 的，p1=0：从某虫洞到达d 的 
    if (num!=1&&d==begin&&p1==1) return 1; // 回到原点了，而且是用走的方式 
    if (p1==0)//从虫洞d出来，就往前走，如果前面有虫洞，就走过去，没有就返回0 
    {
        if (a[d].y==a[d+1].y) return f(num+1,d+1,begin,1);
        else return 0;//没有形成环就返回0 
    }
    if (p1==1) return f(num+1,b[d],begin,0);//走到虫洞口了就跳进去 
}
bool check()
{
    for (int j=1;j<=n;j++)//尝试从每个点出发，看会不会形成环 
        if (f(1,j,j,1)==1) return 1;//有一个会形成环就返回1 
    return 0;
}
void dfs(int x)//配对
{
    if (x==n+1)    {if (check()==1) ans++;return;}//n个点都匹配完了，就检查 
    if (b[x]==0)//如果x没有匹配 
    {
        for (int i=x+1;i<=n;i++)//一个点一个点的匹配 
            if (b[i]==0)
            {
                b[i]=x;b[x]=i;//标记，i匹配x，x匹配i 
                dfs(x+1);//往后搜 
                b[i]=0;b[x]=0;//还原 
            }

    }
    if (b[x]!=0) dfs(x+1);//x匹配过了就继续往后搜 
    return;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);//这里的x是横坐标，y是纵坐标 
    }
    sort(a+1,a+n+1,cmp);//排序按照纵坐标排，纵坐标相同按横坐标 
    dfs(1);//一个点一个点的去匹配 
    printf("%d\n",ans);
    return 0;
}
```
还是比较简洁的


---

## 作者：Sino_E (赞：30)

第一思路，这玩意可以换成一个图。

因为只能往右走，所以我们可以把虫洞按坐标排个序，对同一行的虫洞进行处理，相邻的y坐标相同的虫洞连一条**有向边**。

第二思路，枚举。保证枚举的所有点对(a,b)中**a<b**，我采用了这个不知道什么原理的不重复枚举方法.-.请各位自行体会。

每枚举一个点对，就把虫洞的信息更改，将其互联。**（注意虫洞的信息与图的信息是分开存储的）**。

第三思路，测环。说明一下标记——这里标记的并不是点（虫洞），因为一个点可以入，也可以出。这里标记的是，**该点到下一个点之间经过的线段。**同时，进入搜索的下一层时，直接进入该点所连接的点。这样做的含义是**传送到该点所连接的点的前面一条线段**。

其实并不难.-.写搜环的时候思考一下标记的方式，稍微改改差不多就OK，以上的解释只是对代码含义的一个合理解释。

更多思路细节和实现细节请参考代码。

**UPD:优化后代码**

```cpp
// Code by ajcxsu
// Problem: wormhole

#include<bits/stdc++.h>
using namespace std;

const int N=20;
struct Pos {
    int x,y;
} p[N];
bool cmp(const Pos &a, const Pos &b) {
    return a.y<b.y || (a.y==b.y && a.x<b.x);
}
int n;
int to[N];
bool tag[N];
int con[N];

bool cycle(int x) {
    while(to[x]) {
        if(tag[x]) return 1;
        tag[x]=1;
        x=con[to[x]];
    }
    return 0;
}

int ans=0;
void dfs1(int k) {
    if(k>n) {
        bool ok=0;
        for(int i=1;i<=n && !ok;i++)
            memset(tag,0,sizeof(tag)), ok|=cycle(i);
        ans+=ok;
        return;
    }
    if(con[k]) dfs1(k+1);
    else {
        for(int i=k+1;i<=n;i++)
            if(!con[i]) {
                con[i]=k, con[k]=i;
                dfs1(k+1);
                con[i]=con[k]=0;
            }
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y);
    sort(p+1,p+1+n,cmp);
    for(int i=1;i<=n-1;i++)
        if(p[i].y==p[i+1].y) to[i]=i+1;
    dfs1(1);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：东门之杨 (赞：10)

发现了奶牛题总是乱加标签。

观察到数据范围只到12，所以考虑暴力枚举所有可能的排列然后一一判断。可以接受的最高复杂度为O(n^7)，不优化也不会被续。

然而还是借鉴了别人的思路╮(╯▽╰)╭


## 预处理

对数据使用结构体存储方便排序。让数据按照y递增，当y相同时按照x递增，这样可以查表找出下一个坐标位置，或者判断出行走方向上有没有下一个点。

实现：

```cpp
struct node{
    int x,y;
}map[13];

bool law(node a,node b){
    if(a.y!=b.y)
        return a.y<b.y;
    return a.x<b.x;
}

sort(map+1,map+n+1,law);
```

## 枚举配对

通过dfs获取可能的每个排列，用一个数组储存。

有点全排列的意思，或许可以用next\_permutation？

实现：

```cpp
bool book[13];
int set[13];
int k;

void dfs(void){
    if(k==n){                    //当set中有了一整个排列 
        check();
        return;
    }
    int pos;
    for(int i=1;i<=n;i++)        //扩展一个点 
        if(!book[i]){
            set[++k]=i;
            book[i]=1;
            pos=i;
            break;
        }
    for(int i=pos+1;i<=n;i++)    //搜索下一个点 
        if(!book[i]){
            set[++k]=i;
            book[i]=1;
            dfs();
            k--;//回溯 
            book[i]=0;
        }
    book[pos]=0;//恢复 
    k--;
    return;
}
```

## 检查

观察这个排列是否可以满足死循环，看注释吧。

```cpp
int ans;

void check(void){
    bool flag=0;
    for(int i=1;i<=n;i++){//枚举每一个点 
        int x=i;//备份当前点坐标 
        for(int j=1;j<=n;j++){
            int t=(x%2)?set[x+1]:set[x-1];
            //这句不好理解，意思是获取一个
            //坐标，x为偶数表示x是一个排列
            //中的前一个元素，反之为后一个 
            if(t==n||map[t+1].y!=map[t].y)
            //找到最后一个元素，或者
            //本排列不能走到下一个点 
                break;
            for(int m=1;m<=n;m++)
                if(set[m]==t+1){
                //找到了下一个点 
                    x=m;
                    break;
                }
            if(j==n){
                //本循环到结束都没被
                //break,说明符合条件 
                ans++;
                flag=1;
                break;
            }
        }
        if(flag) 
            break;
    }
    return;
}
```
### \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

完全的代码不贴了，核心算法已经在这了。

奶牛题都挺有意思的，看起来跟做起来完全两回事。


---

## 作者：2002chenhan (赞：4)

这题一看就是硬搜索,难点有两个：

1、如何枚举两两的搭配，使得结果完整？

2、如何简洁地检验是否存在环？

.

先来解决问题1。这个搜索要求平时真的很少见，它要求不漏不重地枚举两两间匹配的情况。我们这样做：在轮到k选择时，它顺手带上一个搭档，同时把搭档的选择权给除掉。这样做，就可以把k和他的搭档打包，看成一个整体，不至于使k找了他的搭档，哪回他的搭档放过来找他。

.

问题2的方法就很多了。最容易想到的就是在原图上连接新的边后直接跑原图。但这样做有几个问题，一是图很大，不可能一个个坐标的跑，二是如果直接修改原图，在用完后还要还原，不方便。

要克服这两个问题不难。如果图大，我们就直接给他们连边，让他们按边走。连边的方法有很多，可以用邻接表。考虑到她的方向是一直向x轴的正方向，她从每个点出发能到达的点是固定的，变就变在虫洞的传送。变的不要理他，把固定的先解决好。于是我们直接给每个点上标记，记录他能到达的点。

对于会改变的边，我们另开个数组来处理。在搜索的过程中，把传送的两个点连起来，在要传送时按这个走。
通过分成两块来处理，分开了变与不变，使得原先的还原操作得以删去。真是绝妙的一招！

【代码】（借鉴https://www.luogu.org/paste/t2yn4e63）
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=20;
struct Pos
{
	int x,y;
} p[N];
bool cmp(const Pos &a, const Pos &b)
{
	return a.y<b.y || (a.y==b.y && a.x<b.x);
}
int n;
int to[N];
bool tag[N];
int con[N];

bool cycle(int x)
{
	while(to[x])
	{
		if(tag[x]) return 1;
		tag[x]=1;
		x=con[to[x]];
	}
	return 0;
}

int ans=0;
void dfs1(int k)
{
	if(k>n)
	{
		bool ok=0;
		for(int i=1; i<=n && !ok; i++)
			memset(tag,0,sizeof(tag)), ok|=cycle(i);
		ans+=ok;
		return;
	}
	if(con[k]) dfs1(k+1);
	else
	{
		for(int i=k+1; i<=n; i++)
			if(!con[i])
			{
				con[i]=k, con[k]=i;
				dfs1(k+1);
				con[i]=con[k]=0;
			}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+1+n,cmp);
	for(int i=1; i<=n-1; i++)
		if(p[i].y==p[i+1].y) to[i]=i+1;
	dfs1(1);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：王轩逸 (赞：4)

```cpp
#include<iostream>
#include<cstring>
using namespace std;
/*
算法步骤:
①搜索所有可能的配对，需要确保不会重复：
-> n 个不同的物品放到 n/2 个相同的盒子里，不能出现重复。
-> 每对中的第 2 个元素 > 第 1 个元素，第 i 对的第 1 个元素 > 第 i-1
对的第 1 个元素
②判断是否会出现循环：
-> 对于每一种配对方案，依次模拟 Bessie 从第 1 个到第 n 个虫洞出发。
-> 模拟走 n 步，根据抽屉原理，如果 n 步以后 Bessie 还在某个虫洞中则，
出现了循环。
③初始化:
-> 记录每个虫洞右边的虫洞，模拟判断循环时使用。
*/ 
const int N=15;
struct Node{
	int x,y;//虫洞的 x 和 y 坐标
}w[N];
//part[i]存储第 i 个虫洞的配对虫洞，to[i]记录 i 右边的虫洞。
int n,ans,part[N],to[N];
bool is_cycle(){
	//模拟从第 1 个到第 n 个虫洞出发
	for(int start=1;start<=n;start++){
		int pos=start;
		for(int cnt=1;cnt<=n;cnt++)
			pos=to[part[pos]];
		if(pos)
			return true;
	}
	return false;
}
//n 个不同的物品放到 n/2 个相同的盒子里，不能出现重复。
//为防止重复，搜索过程中没对中的元素 2>元素 1，每一对的元素 1>上一对的元素 1 。
void dfs(int cur,int pre){
	if(cur>n/2){
		if(is_cycle())//所有配对完成，到达目的地
			ans++;
		return;
	}
	for(int i=pre+1;i<=n;i++) 
	if(!part[i])//i 还未配对
		for(int j=i+1;j<=n;j++)
			if(!part[j]){//j 还未配对
				part[i]=j,part[j]=i;//i 和 j 配对
				dfs(cur+1,i);
				part[i]=part[j]=0;
				//i 和 j 始终在变动，需要恢复状态
			} 
}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>w[i].x>>w[i].y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(w[j].y==w[i].y&&w[j].x>w[i].x)
				if(to[i]==0||w[j].x<w[to[i]].x)
					to[i]=j;//j 在 i 右边
	dfs(1,0);
	cout<<ans;
	return 0;
}
```


---

## 作者：Celebrate (赞：3)

这一题先dfs连接所有的虫洞，再判断，记录并输出

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
struct node//虫洞的坐标 
{
    int x,y;
}a[21];
int n,ans=0;
int f[21];
inline int cmp(const void *xx,const void *yy)//排序一次，就可以方便的连接虫洞了，pd函数中显示出来 
{
    node x=*(node*)xx;
    node y=*(node*)yy;
    if(x.y<y.y) return 1;
    if(x.y==y.y && x.x<y.x) return 1;
    return 0;
}
bool pd(int k,int t,int bk,int c)//k表示步数，t表示当前虫洞的编号，bk表示初始虫洞，c表示是否能利用这个虫洞来传送 
{
    if(k!=1 && t==bk && c==0)//如果陷入循环，就返还可以 
    {
        return true;
    }
    if(c==0)//如果不可以用虫洞传送，就要步行到下一个 
    {
        if(a[t].y==a[t+1].y)//如果能走到的话 
        {
            return pd(k+1,t+1,bk,1);//往下深搜，下一个可以传送 
        }
        else return false;//不然就不能陷入循环 
    }
    if(c==1)//如果可以床送的话 
    {
        return pd(k+1,f[t],bk,0);//下一个不能传送 
    }
}

void dfs(int k)//dfs来找出所有的环 
{
    if(k==n+1)//如果找完了所有的环 
    {
        for(int i=1;i<=n;i++)//判断一下 
        {
        	if(pd(1,i,i,0)==true)//如果可以 
        	{
        		ans++;break;//记录，并退出 
        	}
        }
        return;//不管下面的函数了 
    }
    if(f[k]==0)//如果还没有被找过 
    {
        for(int i=k+1;i<=n;i++)//往下搜索 
        {
            if(f[i]==0)
            {
                f[k]=i;f[i]=k;
                dfs(k+1);
                f[k]=0;f[i]=0;//回溯 
            }
        }
    }
    else 
    {
    	dfs(k+1);//被找过就不管了 
    }
}
int main()
{
    int i;
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);//输入坐标 
    qsort(a+1,n,sizeof(node),cmp);dfs(1);//排序，并dfs 
    printf("%d\n",ans);//最后输出就好了 
    return 0;
}
```

---

## 作者：xsap (赞：2)

- 黄题居然对拍了1天QwQ。
- 坑点：
  - 如果遇到虫洞，必须传送过去。
  - 可能两点之间既可以用虫洞，又可以用走路。
- 思路分析：
  - 显然，两点之间能否走路是可以预处理出的。
  - **但是** ， 当有三点满足 $ A( x_{1} , y )\  B(x_{2} , y)\  C(x_{3} , y) $ 且 满足$ x_{1} < x_{2} < x_{3} $ ，则$A$可走$B$，$B$可走$C$，但$A$不可走（走到$B$时，会被强制传送）$C$。
  - 所以，预处理时应先双关键字{y , x}排序，处理$\color{Blue}{f_{i}}$表示$\color{blue}{i}$能否到$\color{blue}{i + 1}$。
  - 之后可以DFS出黑洞配对方案。
  - 之后思考如何check。可以枚举贝西最开始的虫洞。之后每当贝西还可以走的时候，就让贝西走一步后跳虫洞。就愉快地AC了
- 代码：
```
# include <iostream>
# include <cstdio>
# include <cstring>
# include <algorithm>
using namespace std ;
int n ;
int posx[15] , posy[15] ;
int f[15] ;
int pairs[15] ;
int ans = 0 ;
bool already[15] ;
bool check( int begin )
{
	while ( f[begin] )
	{
		if ( already[begin] ) return true ;
		already[begin] = true ;
		begin = pairs[f[begin]] ;
	}
	return false ;
}
void dfs( int x )
{
    if ( x > n )
    {
        for ( int i = 1 ; i <= n ; i++ )
        {
            memset( already , false , sizeof( already ) ) ;
            if ( check( i ) )
            {
                ans ++ ;
                break ;
            }
        }
        return ;
    }
    if ( pairs[x] ) 
    {
        dfs( x + 1 ) ;
        return ;
    }
    for ( int i = x + 1 ; i <= n ; i++ )
    {
        if ( i == x ) continue ;
        if ( pairs[i] ) continue ;
        pairs[x] = i ;
        pairs[i] = x ;
        dfs( x + 1 ) ;
        pairs[x] = 0 ;
        pairs[i] = 0 ;
    }
}
struct node
{
	int x , y ;
	void read()
	{
		scanf("%d%d" , &x , &y) ; 
	}
} point[105] ;
bool cmp( node a , node b )
{
	if ( a.y != b.y ) return a.y < b.y ;
	return a.x < b.x ;
}
int main()
{
    scanf("%d" , &n) ;
    for ( int i = 1 ; i <= n ; i++ )
    	point[i].read() ;
    sort( point + 1 , point + n + 1 , cmp ) ;
    for ( int i = 1 ; i < n ; i++ )
    {
    	if ( point[i].y == point[i + 1].y )
    	{
    		f[i] = i + 1 ;
		}
	}
	dfs( 1 ) ;
    printf("%d\n" , ans) ;
    return 0 ;
}

```

---

## 作者：Thaumaturge (赞：2)

蒟蒻的我只会用搜索，然而我的脑子并不太好使。。。所以有几个地方，卡了半天。。。

1.去重。枚举时，首先要让对应关系不重复，其次顺序重复的话，通过大小顺序判断就行了。

2.经过一个点并不意味着下一次来到它时就陷入了死循环。。有可能左进右出。因此，经过时要有两个方向，一个判左，一个判右。然后。。dfs就行了。

在此献上C式C++代码：


```
#include <bits/stdc++.h>

using namespace std;

int a[20],b[20],bj[20],dy[20],i,c,sum;//a为横坐标，b为纵坐标,bj记录入栈,dy记录对应关系;
int tj=2;//统计存入了多少个洞,初始值赋值为2是为了防止越界(bb越界)
int bh[20];//记录这个洞右边的下一个洞，方便运算。如果没有，则赋值为-1
int bn[20][2];//记录这个洞有没有被进过，用来判断无限循环;
int min1;
int on;//辅助bh记录对应关系
int now;//记录目前在哪个洞
int bb[20];//记录入队情况，防止重复。
int f;//没卵用

int pd(){
	for(int i=1;i<=c;i++)
	{
		bn[i][0]=1;
		now=i;
		while(1)
		{
			now=dy[now];
			
			if(bn[now][1]==1) return 1;

			bn[now][1]=1;
			if(bh[now]==-1) {for(int ww=1;ww<=c;ww++) {bn[ww][1]=0; bn[ww][0]=0;}break;}

			now=bh[now];
			
			if(bn[now][0]==1) return 1;

			bn[now][0]=1;
		}
	}
	return 0;
}

int search(int n){
	
	for(int o=1;o<=c;o++)
	{
		if(bj[o]!=1 && o>n && (bb[tj/2-1]<n))
		{
			bj[o]=1;
			dy[o]=n;
			dy[n]=o;
			bb[tj/2]=n;
			tj+=2;
			
			if(tj==c+2)
			{
				sum+=pd();
				for(int om=1;om<=c;om++)
				{
					bn[om][0]=0;
					bn[om][1]=0;
				}
			}

			for(int p=1;p<=c;p++)//枚举即将到来的下一组洞
			if(bj[p]!=1)
			{
				bj[p]=1;
				search(p);
				bj[p]=0;
			}
			bj[o]=0;
			dy[o]=0;
			dy[n]=0;
			tj-=2;//回溯
		}
	}
}

int main(){
	cin>>c;
	for(i=1;i<=c;i++)
	cin>>a[i]>>b[i];

	for(int h=1;h<=c;h++)
	{
		on=0;
		min1=2100000000;
		for(int h1=1;h1<=c;h1++)
		{
			if(b[h]==b[h1] && a[h]<a[h1] && a[h1]-a[h]<min1)
			{
				min1=a[h1]-a[h];
				on=h1;
			}
		}
		bh[h]=on;
	}//找出每个虫洞最靠近它右边的洞方便运算
	
	for(int h=1;h<=c;h++)
	{
		if(bh[h]==0) bh[h]=-1;
	}

	bj[1]=1;//从1开始找
	search(1);
	cout<<sum;
	return 0;
}
```


---

## 作者：L_M_ (赞：2)

一开始我想直接建图找环，后来发现这是不行的，这是一个既有有向边又有无向边的图，直接找环很麻烦

稍加分析后发现，从一个点，如果上一次我是从虫洞走来的，这次我只能步行；如果我是步行来的，这次我必然走虫洞

因此，要把虫洞和步行分开存，对于每两个点i,j如果其y坐标相等则连一条有向边，然后枚举虫洞的匹配情况，最后在枚举完成后进行判环，如下：

令to[i]为步行到的点，con[i]为i的虫洞，则位于i，要先走到to[i]，再走向to[i]的虫洞，即i = con[to[i]],记录instack判环即可

但是还有一个问题：如果有多个点的y都相同，这时是不能盲目连边的

因此，将点按y坐标排序，y相同时按x排序，对于一个点i，如果i和i +１的ｙ相同，则在i和i + 1间连，这样能保证不会出现例如最小和第三小的点间连边的情况（而这本来是不可能的）

以上，就做出了这道题
```

#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
inline ll read()
{
  ll ans = 0,op = 1;
  char ch = getchar();
  while(ch < '0' || ch > '9')
    {
      if(ch == '-') op = -1;
      ch = getchar();
    }
  while(ch >= '0' && ch <= '9')
    {
      (ans *= 10) += ch - '0';
      ch = getchar();
    }
  return ans * op;
}
int n;
struct node
{
  ll x,y;
}a[20];
bool cmp(const node &a,const node &b)
{
  return a.y < b.y || (a.y == b.y && a.x < b.x);
}
int con[101],to[101];
int ans = 0;
bool vis[1001];
bool instack[1001];
bool flag = 0;
bool dfs_cy(int u)
{
  while(to[u])
    {
      if(instack[u]) return 1;
      instack[u] = 1;
      u = con[to[u]];
    }
  return 0;
}
void dfs(int k)
{
  if(k > n)
    {
      flag = 0;
      for(int i = 1;i <= n && !flag;i++) memset(instack,0,sizeof(instack)),flag |= dfs_cy(i);
      ans += flag;
    }
  if(con[k]) dfs(k + 1);
  else
    {
  for(int i = k + 1;i <= n;i++)
    {
    if(!con[i])
      {
    con[i] = k,con[k] = i;
    dfs(k + 1);
    con[i] = con[k] = 0;
      }
    }
    }
}
bool ok[101][101];
int main()
{
  n = read();
  for(int i = 1;i <= n;i++) a[i].x = read(),a[i].y = read();
  sort(a + 1,a + 1 + n,cmp);
  for(int i = 1;i <= n;i++) if(a[i].y == a[i + 1].y) to[i] = i + 1;
  //for(int i = 1;i <= n;i++) printf("%d ",to[i]);
  //cout << endl;
  dfs(1);
  printf("%d",ans);
}
```

---

## 作者：RBI_GL (赞：1)

### 题意：

给定一些点，在横向穿过这些点时将会被传送回纵坐标相同的 $y$ 轴上，问有多少种情况会使得永远向右爬的虫子陷入死循环。

### 思路：

首先因为只会向右爬，所以我们只需将同一行上的点间连边，然后 $dfs$ 暴力找匹配，之后判环即可。

### Code：

```cpp
#include <bits/stdc++.h>
#define x second
#define y first
using namespace std;
int n,to[20],pre[20],ans;
bool vis[20];
pair<int,int>p[20];
bool check(int k) { //判环
	while(to[k]) {
		if(vis[k]) return true;
		vis[k]=true;
		k=pre[to[k]];
	}
	return false;
}
void dfs(int dep) { //暴力找匹配
	if(dep>n) {
		for(int i=1; i<=n; i++) {
			fill(vis+1,vis+1+n,0);
			if(check(i)) {
				ans++;
				return;
			}
		}
		return;
	}
	if(pre[dep]) dfs(dep+1);
	else {
		for(int i=dep+1; i<=n; i++)
			if(!pre[i]) {
				pre[i]=dep;
				pre[dep]=i;
				dfs(dep+1);
				pre[i]=0;
				pre[dep]=0;
			}
	}
}
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) cin>>p[i].x>>p[i].y;
	sort(p+1,p+1+n);
	for(int i=1; i<n; i++) if(p[i].y==p[i+1].y) to[i]=i+1;
	dfs(1);
	cout<<ans;
	return 0;
}
```

---

## 作者：Kewth (赞：1)

因为每两个虫洞都可以配对，所以这道题可以在有限的虫洞两两配对方案中进行搜索，然后每种方案判断是否陷入死循环，具体的看代码


```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n;    //n个虫洞
int ans=0;    //结果
int b[13]= {0};    //记录配对情况
struct A {    //记录点的坐标
    int x;
    int y;
} a[13];
int my(const A &i,const A &j) {    //排序的函数
    if(i.y<j.y)
        return 1;
    if(i.y==j.y) {
        if(i.x<j.x)
            return 1;
    }
    return 0;
}
int doit(int num,int x,int begin,int into) {//模拟牛走动的情况,into表示到达该点的方式，0表示在该点走出虫洞，1表示走到该点
    if(num!=1&&x==begin&&into==0) {    //如果从起始点走出来，说明循环了
        return 1;
    }
    if(into==0) {    //若在该点走出虫洞，就向前走
        if(a[x].y==a[x+1].y) {    //如果前面有虫洞，就走进去
            return doit(num+1,x+1,begin,1);
        } else {    //如果前面没有虫洞，就说明循环结束
            return 0;
        }
    }
    if(into==1) {    //若是走到该点，就走进去
        return doit(num+1,b[x],begin,0);
    }
}
int judge() {    //判断
    int i,j;
    for(i=1; i<=n; i++) {    //从第i个点开始走
        if(doit(1,i,i,0)==1) {
            return 1;
        }
    }
    return 0;
}
void mpair(int x) {    //配对
    int i,j;
    if(x==n+1) {    //若已经配对完成
        if(judge()==1) {    //判断是否陷入死循环
            ans++;
        }
        return ;
    }
    if(b[x]==0) {    //如果当前虫洞暂为配对，就为其配对
        for(i=x+1; i<=n; i++) {
            if(b[i]==0) {
                b[x]=i;
                b[i]=x;
                mpair(x+1);
                b[x]=0;
                b[i]=0;
            }
        }
    } else {    //如果当前虫洞已被配对，就继续找下一个虫洞
        mpair(x+1);
    }
    return ;
}
int main() {
    int i,j,k;
    cin>>n;
    for(i=1; i<=n; i++) {
        cin>>a[i].x>>a[i].y;
    }
    for(;;);//防抄题解
    sort(a+1,a+n+1,my);    //排序，方便查找同一行的虫洞
    mpair(1);    //从第一个虫洞开始配对
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：01190220csl (赞：0)

穷举所有可能的组合，判断有没有环。

穷举方法：用DFS作n全排列，其中1与2连接，3与4连接，...（n-1）与n连接。规定：对任意的2k+1项，不存在任意一个正整数，使得该数小于2k+1项的数且位置在2k+1后面。可证：按照该要求进行全排列的结果是不重复不遗漏。

代码：

```cpp
bool go( int a , int b )//判断是否有环
{
    bool went[13] = { 0 };
    while( 1 )
    {
        int minnum = 0 , minx = 2147483647;
        for( int i = 1 ; i <= n ; i++ )
            if( y[i] == b && x[i] > a && x[i] < minx )
            {
                minx = x[i];
                minnum = i;
            }
//计算从（a,b）开始走会进入哪个虫洞，若不会进入则为0
        if( minnum == 0 )
            return 0;
        if( went[minnum] )
            return 1;
        went[minnum] = 1;
//注意：不能标记终点，可以举出反例
        int i;
        for( i = 1 ; i <= n ; i++ )
            if( com[i] == minnum )
                break;
        if( i % 2 == 0 )
        {
            a = x[com[i - 1]];
            b = y[com[i - 1]];
        }
        else
        {
            a = x[com[i + 1]];
            b = y[com[i + 1]];
        }
    }
}

int ans = 0;
bool used[13] = { 0 };
void dfs( int now )
{
    if( now > n )
    {
/*只需讨论从某一个虫洞出发的情况：若从(m,n)出发无法进入虫洞，则无需考虑；若从(m,n)出发进入a号虫洞，且a号虫洞与b号虫洞相连，则从(m,n)出发等价于从b号虫洞出发。*/
        for( int i = 1 ; i <= n ; i++ )
            if( go( x[i] , y[i] ) )
            {
                ans++;
                break;
            }
        return;
    }
    if( now % 2 == 1 )
        for( int i = 1 ; i <= n ; i++ )
            if( !used[i] )
            {
                com[now] = i;
                used[i] = 1;
                dfs( now + 1 );
                used[i] = 0;
                return;
//筛去重复情况（如：1 2 3 4；1 2 4 3）
            }
    for( int i = 1 ; i <= n ; i++ )
        if( !used[i] )
        {
            com[now] = i;
            used[i] = 1;
            dfs( now + 1 );
            used[i] = 0;
        }
}
//主函数略
```

---

## 作者：Bzy_temp (赞：0)

/\*
看了这么多图论做法，那我就离散化+dfs走一波吧.代码↓

\*/
-------------------






```cpp
#include<bits/stdc++.h>‘万能头文件 
using namespace std;//流操作命名空间 
// **line是离散的行的传送门（虫洞）个数**
// **they对应离散后的传送门坐标**
// **to是对应离散后的指向指针（dfs时确认）** 
// **height标识离散前的y轴高度**
// a是总量，geted是判重标识,all是总循环数，point是临时指针 
int line[12],they[12][2],to[12];
int height[12];int a;bool geted[12];int all,point;
//检测连接方式是否有循环 
void check(){
    for(int i=0;i<=a-1;i++){//遍历每个点为起始 
        int now=i;for(int j=0;j<=11;j++)geted[j]=false;//记录起始位置//清空标识 
        while(1){//不断循环 
            if(geted[now]){all++;return;}//如果路重复则有循环，加1，跳出寻找下一匹配 
            geted[now]=true;//记录来过的点 
            if(line[they[now][0]]==they[now][1])break;//如果X轴上无下一点则判下一出发点 
            else now=to[now+1];//如果有下一点则到跳下一点的对应点//下一点不标记 
        }
    }
}
//dfs匹配 
void dfs(int index){
    if(index==a/2){//若index达到总传送点的1/2，则有唯一匹配 
        int i=0;while(to[i]!=-1)i++;//循环找到唯一匹配 
        int j=i+1;while(to[j]!=-1)j++;
        to[i]=j;to[j]=i;//赋值到连接数组 
        check();//检测匹配 
        to[i]=-1;to[j]=-1;//清除匹配 
    }else{
        int i=0;while(to[i]!=-1)i++;//寻找所有匹配 
        for(int j=i+1;j<=a-1;j++){
            if(to[j]==-1){
                to[i]=j;to[j]=i;
                dfs(index+1);//dfs寻找下一匹配 
                to[i]=-1;to[j]=-1;
            }
        }
    }
    return;
}
int main(){
    cin>>a;int tmp=-1;//输入//定义临时变量 
    for(int i=0;i<=a-1;i++){
        int m,n;cin>>m>>n;//输入//m其实没有用，离散化后无视顺序的// 
        for(int j=0;j<=point-1;j++){
            if(height[j]==n){line[j]++;goto l;}//如果此高度已存在，则此高度的队列加1 
        }
        height[point]=n;line[point]++;point++;//否则加1个离散的队列 
        l:continue;
    }
    for(int i=0;i<=a-1;i++)to[i]=-1;//清除连接标识 
    for(int i=0;i<=point-1;i++){
        for(int j=1;j<=line[i];j++){
            tmp++;they[tmp][0]=i;they[tmp][1]=j;//顺序存入点的离散坐标 
        }
    }
    dfs(1);//dfs 
    cout<<all;//输出 
    return 0;
}
```

---

## 作者：zk1431043937 (赞：0)

没有Pascal题解哦，来一波福利。

首先匹配虫洞，枚举状态，然后再检查虫洞是否连通即可。

一个dfs和判断就能完成啦（毕竟数据才12）。

具体的见代码：

```cpp
program p1444;
  var i,j,n,total:longint;
      x,y,partner,next_on_right:array[0..13]of longint;
function cycle_exists:boolean;
  var start,pos,count:longint;
begin
  for start:=1 to n do
  begin
    pos:=start;
    for count:=0 to n-1 do
    begin
      pos:=next_on_right[pos];//先向右走。
      pos:=partner[pos];//再进虫洞另一端。
    end;
    if pos<>0 then exit(true);如果一直走下去都有虫洞那么就进入循环，加一种可能。
  end;
  exit(false);
end;
procedure solve;
  var i,j:longint;
begin
  for i:=1 to n+1 do
  if partner[i]=0 then break;
  if (i>n) then
  if cycle_exists=true then inc(total);//匹配完检验这种匹配是否可行。
  for j:=i+1 to n do
  if partner[j]=0 then
  begin//先任意匹配两个虫洞。
    partner[i]:=j;
    partner[j]:=i;
    solve;
    partner[i]:=0;
    partner[j]:=0;
  end;
end;
begin
  readln(n);
  for i:=1 to n do
  readln(x[i],y[i]);
  for i:=1 to n do
  for j:=1 to n do
  if (x[j]>x[i]) and (y[i]=y[j]) then
  if (next_on_right[i]=0) or (x[j]-x[i]<x[next_on_right[i]]-x[i]) then
  next_on_right[i]:=j;//记录i右边的第一个虫洞j，若i右边无虫洞就是0。
  total:=0;
  solve;
  writeln(total);
end.
```

---

