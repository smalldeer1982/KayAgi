# [USACO16JAN] Build Gates S

## 题目描述

FarmerJohn 打算在他农场的一部分，建设一个围栏。但是因为没有认真做事，建造完成后，围栏变成一个很奇怪的形状。

具体来说，FJ 从 $(0,0)$ 出发，走了 $N$ 步，每步移动一单位（向东、向南、向西或向北）。

他走过的每一步，都会留下一段单位长度的围栏。例如，如果他的第一步向北，他建造一单位从 $(0,0)$ 到 $(0,1)$ 的围栏。

FJ 可能重复到达点多次，他也可能重复建造一段围栏多次。如果他的路径穿过一段已经建成的围栏，他的围栏也有可能会有交叉。

不用说，FJ 看到完成的围栏时，一定很沮丧。特别的，他发现一些区域被围栏封闭起来，从而无法到达。FJ 想在围栏上，安装一些门来解决这个问题。

门可以安装在任意一段单位长度（注：必须是之前走过的某一步）的围栏上，从而可以穿越这段围栏的两侧。

请计算 FJ 最少需要安装多少个门，才能保证农场上任意区域到任意区域都可到达。

## 说明/提示

注意，如果农场初始连通，答案就是 $0$。

### 数据范围

$1\le n\le 1000$。


## 样例 #1

### 输入

```
14
NNNESWWWSSEEEE```

### 输出

```
2```

# 题解

## 作者：LPhang (赞：24)

## 题意
 
FJ 从 $(0,0)$ 开始在一个平面上走动（无限制），会在走过的路径上留下栅栏， 形成一些封闭的空间。而现在要求把尽量少的一部分栅栏换成门（也可以看做删除这段栅栏），使得整个平面连通。

## 思路

### 方法一
答案很明显，因为对于每一个环**至少需要一次**删边才能解开这个环，那么删边的最小次数即是环的数量。但是对于一条边可能**包含在多个环中**，一次就会满足多个环，每个环都算就会**出现错误**，所以我们把图中那些**不包含其他环的环**的数量求出来就可以了，而之所以求这样的环，是因为只有这种环才能保证环内**有且仅有**一个封闭空间，那么对于每一个这种环进行一次删边就符合题意了。

例如样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/d0r7akt0.png)

（紫色的是起点）因为有两个这样（黄色区域和蓝色区域）的环，所以 $ans=2$。

再举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/apvxrt9e.png)

在这个图中就存在 $3$ 个符合上文要求的环（黄、蓝、绿），虽然黄绿部分也能组成环，但这个环内存在两个封闭空间，所以不能算，故 $ans=3$。

到这里就不难发现，一个点如果**到过**，那么从另一个**没走过的方向**再次到这个点会形成一个新的符合要求的环, 因为这样就表明出现一条新的路径连接到了这个点，也必然会**多且仅多出**一个封闭空间，也就使答案加一。到这里为止，一个大体的算法就出来了，我们首先使 FJ 一边移动一边把路径存下来，我们设 FJ 现在所处的点为 $k$，到点 $k$ 之前的点为 $k-1$，如果 $k$ 不是第一次到，并且 FJ 从点 $k-1$ 到点 $k$ 之前不存在这条路径，则 $ans+1$。

完整代码如下：

```cpp
#include<bits/stdc++.h>
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, -1, 1};
const char s[] = {'N', 'S', 'W', 'E'};
const int N = 2e3 + 10, M = 2e3 + 10;
using namespace std;
int n, x = 1000, y = 1000, xt = 1000, yt =1000, num, bol[N][M], f[N][M], a[N][M], ans;
/* 
n表示FJ行走的步数
(x, y)表示上文中的 k
(xt, yt)表示上文中的 k - 1 
num表示FJ所到达的不同的点的个数 
bol[i][j]表示坐标为(i, j)的点是否到过
f[i][j]表示编号i和编号j的点是否存在路径
a[i][j]表示坐标为(i, j)的点的编号
ans表示答案 
*/ 
int main() {
	scanf("%d\n", &n); num = 1, bol[1000][1000] = 1, a[1000][1000] = 1;
	//因为有负坐标，所以起点坐标设为(1000, 1000);同时给起点编号为 1 
	for(int i = 1; i <= n; ++i) {
		char c; scanf("%c", &c);
		for(int j = 0; j < 4; ++j) {
			if(c == s[j]) {x += dx[j], y += dy[j]; break;}
		} //按读入移动并求出坐标(x, y) 
		if(!bol[x][y]) a[x][y] = ++num;
		//如果点(x, y)第一次到，给(x, y)编号为已有点个数 + 1 
		int last = a[xt][yt], now = a[x][y];
		//last表示坐标(xt, yt)的编号，now表示坐标(x, y)的编号 
		if(!f[last][now] && bol[x][y]) ++ans;
		//如果点 k 不是第一次到，并且FJ从点 k - 1 到点 k 之前不存在这条路径，则 ans + 1
		f[last][now] = f[now][last] = 1;
		//标记点 k - 1 到点 k 的路径存在 
		xt = x, yt = y; bol[x][y] = 1;
		//更新点 k - 1 为 k，并标记点 k 到过； 
	}
	printf("%d\n", ans);
	//输出答案 
	return 0;
}
```

### 方法二

先分析一下 : 因为这个图是 FJ 所走的路径，所以一定是联通的。而如果图中出现了环，也就一定代表出现了封闭空间，那么也只有当图中没有环之后才会满足题意，题目要求**删边最少**等价于**留边最多**，当一个图不存在环时，**树**的边是最多的，再多就**一定会出现环**，所以保证图是一棵树是一定是最优解，如果图中点数为 $n$ 边数为 $p$，则 $ans=p-(n-1)$，其中 $n-1$ 表示**树的边数**。

例如样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/d0r7akt0.png)

样例点数为 $13$ 边数为 $14$，故 $ans=14-(13-1)=2$。

还是上面的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/apvxrt9e.png)

点数为 $18$ 边数为 $20$，故 $ans=20-(18-1)=3$。

完整代码如下：

```cpp
#include<bits/stdc++.h>
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, -1, 1};
const char s[] = {'N', 'S', 'W', 'E'};
const int N = 2e3 + 10, M = 2e3 + 10;
using namespace std;
int n, x = 1000, y = 1000, xt = 1000, yt =1000, num, bol[N][M], f[N][M], a[N][M], num1;
/* 
n表示FJ行走的步数
(x, y)表示上文中的 k
(xt, yt)表示上文中的 k - 1 
num表示FJ所到达的不同的点的个数 
bol[i][j]表示坐标为(i, j)的点是否到过
f[i][j]表示编号i和编号j的点是否存在路径
a[i][j]表示坐标为(i, j)的点的编号
num1表示FJ移动所留下的边数 
*/ 
int main() {
	scanf("%d\n", &n); num = 1, bol[1000][1000] = 1, a[1000][1000] = 1;
	//因为有负坐标，所以起点坐标设为(1000, 1000);同时给起点编号为 1 
	for(int i = 1; i <= n; ++i) {
		char c; scanf("%c", &c);
		for(int i = 0; i < 4; ++i) {
			if(c == s[i]) {x += dx[i], y += dy[i]; break;}
		} //按读入移动并求出坐标(x, y) 
		if(!bol[x][y]) a[x][y] = ++num, bol[x][y] = 1;
		//如果点(x, y)第一次到，给(x, y)编号为已有点个数 + 1，并标记为到过 
		int last = a[xt][yt], now = a[x][y];
		//last表示坐标(xt, yt)的编号，now表示坐标(x, y)的编号 
		if(!f[last][now]) {
			f[last][now] = f[now][last] = 1;
			++num1;
		}
		//如果这条边是新建的，则边数 + 1 
		xt = x, yt = y;
		//更新点 k - 1 为 k
	}
	printf("%d\n", num1 - num + 1);
	//有没有可能减出负数呢？答案是不会，因为FJ所走的路径一定联通，所以整个图至少也会是一棵树，答案最小也就为num - 1（树的边数） 
	return 0;
}
```

---

## 作者：lxzy_ (赞：18)

$\color{red}\text{考试时做的一道题，也是唯一AC的一道题。。。}$

---

# 这题非常~~简单~~毒瘤。

$$\text{First:标记围栏}$$

我们可以开一个二维数组$map$来模拟FJ修建围栏，也就是说把他所走过的路在数组上全部标记为$1(true)$，而未走过的路则标记为$0(false)$。这样，就可以把FJ所建的围栏的形状搞出来啦。

## 且慢！！

如果光是这么FJ走一步你就标记一步，那么程序连样例也过不了。拿样例来说：(橙色为FJ所走过的路)

![](https://cdn.luogu.com.cn/upload/pic/73348.png)

上图为正常走法。我们所看到的封闭区域仅仅只有一个$\text{(1号)}$，但正确答案是两个$\text{(1号和2号)}$，也就是说
__2号封闭区域太小了，人与电脑都无法识别。__

因此，我们可以：

**把一步当两步走**


这样，我们就可以完整地统计出封闭区域的数量辣，看！

![](https://cdn.luogu.com.cn/upload/pic/74210.png)

$\text{1号}$和$\text{2号}$都完美显现，接下来我们只需需统计封闭区域的数量就行了。

---

$$\text{Second:确定搜索边界}$$

这个就简(ma)单(fan)了，要找准FJ所走过的最南处，最西处、最东处和最北处后，将搜索区域转化成为一个矩阵，以便统计封闭区域的数量。

$\color{red}\text{注意：}$
$\color{red}\text{如果搜索区域紧紧地贴着FJ所走到的最南处，最西处、最东处和最北处的话。}$
$\color{red}\text{会出现如下现象：(绿色框内为要搜索的部分)}$

![](https://cdn.luogu.com.cn/upload/pic/73357.png)

瞧，封闭区域变成$4$个了。

为了避免这种情况发生，矩阵的四条边应该与南处，最西处、最东处和最北处保持$1$格的~~安全~~距离。

就是酱紫的~~

![](https://cdn.luogu.com.cn/upload/pic/73365.png)

我们只要最后把最外围那一块减去即可。

---

$$\text{Third:统计封闭区域数量}$$

这里我们可以使用深搜或广搜统计，不过为了缩短~~代码长度~~做题时间，我就用了深搜。

# $Code:$

```cpp
#include<iostream>//srO ldq Orz
#include<queue>
using namespace std;
const int N=4002;
//定义二维数组，至于为什么要开到4002*4002，见下。
bool map[N][N];

int n;
string s;

//定义当前FJ所在的坐标，至于为什么定义在(2001,2001)，见下。
int x=2001;
int y=2001;

//定义矩阵四个角的位置，为啥定义在2001，见下。
int Maxx=2001;
int Maxy=2001;
int Minx=2001;
int Miny=2001;

//深搜模板，不用讲了吧。。。
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
inline void DFS(int x,int y)
{
    map[x][y]=true;
    for(register int i=0;i<=3;i++)
    {
        int nx=x+dx[i];
        int ny=y+dy[i];
        if(nx>=Minx-2&&nx<=Maxx+2&&ny>=Miny-2&&ny<=Maxy+2&&map[nx][ny]==false)
        {
            DFS(nx,ny);
        }
    }
}
inline int solve()
{
    int sum=0;
    for(register int i=Minx-1;i<=Maxx+1;i++)
    {
        for(register int j=Miny-1;j<=Maxy+1;j++)
        {
            if(map[i][j]==false)
            {
                sum++;
                DFS(i,j);
            }
        }
    }
    return sum;
}

int main()
{
    map[x][y]=1;//切记，一定要把FJ的起点也标记上！
    cin>>n;
    cin>>s;
    for(register int i=0;i<=n-1;i++)
    {
        if(s[i]=='N')
        {
            map[--x][y]=true;//向北走两步
            map[--x][y]=true;
            Minx=min(Minx,x);//查找最北处
        }
        if(s[i]=='E')
        {
            map[x][++y]=true;//向东走两步
            map[x][++y]=true;
            Maxy=max(Maxy,y);//查找最东处
        }
        if(s[i]=='S')
        {
            map[++x][y]=true;//向南走两步
            map[++x][y]=true;
            Maxx=max(Maxx,x);//查找最南处
        }
        if(s[i]=='W')
        {
            map[x][--y]=true;//向西走两步
            map[x][--y]=true;
            Miny=min(Miny,y);//查找最西处
        }
    }
    int ans=solve();
    if(ans==0)//如果一个也没找到就直接输出0
    {
        cout<<0;
    }
    else//否则减去外围的假封闭区域后输出
    {
        cout<<ans-1;
    }
    return 0;//完美！
}
```

## 注意点：

1. 如果你真的按出题人的"指引"~~咦好冷~~把FJ的起点定在$(0,0)$处的话，那么一旦出现FJ最开始就往下建围栏的情况，电脑就会访问到像$map[-1][-1]$这样的点，要知道，数组访问到负数是会$\text{嘿嘿嘿}$的，所以我们参考数据，把起点定在了$(2001,2001)$处。自然而然，矩阵四个角的位置初始化就为$2001$了。

2. 由于FJ可能比较无聊，如果他一直向上建围栏或一直向下建围栏，那么我们的数组必须开到$2001*2001$这么大才不会让数组爆炸，而我们又把他一步当两步走，所以自然要开到两倍那么大，也就是$4002*4002$才行。

---

PS:

由于本题注意点较多，因此这篇题解写得有点冗余，大佬勿喷。有什么问题可以私信蒟蒻——@[流星之愿](https://www.luogu.org/space/show?uid=67493)，不要在评论区里问啊。~~因为我被禁言了~~
# $\color{orange}\text{完结(撒花)}$

---

## 作者：Minclxc (赞：12)

画图看看，可以发现有多少个交点就有多少个联通块+1，就要修多少扇门

求交点的话就比求联通块更快了

记录每个点有没有访问过，并且每个点每个方向有没有访问过

只有访问过的点且该方向没有访问过才算交点

```cpp
#include<cstdio>
using namespace std;
#define fo(i,s,t) for(int i=s;i<=t;i++)
const int N=2e3+1,m=1e3,f[4][2]={{1,0},{0,1},{0,-1},{-1,0}};
int a[N][N][4],b[N][N],num[100];
int main(){
    num['N']=0,num['S']=3,num['E']=1,num['W']=2;
    int n,x=m,y=m,ans=0;b[x][y]=1;
    scanf("%d\n",&n);
    fo(i,1,n){
        int opt=num[getchar()];
        a[x][y][opt]=1;
        x+=f[opt][0],y+=f[opt][1];
        ans+=(b[x][y]&!a[x][y][3-opt]);
        a[x][y][3-opt]=b[x][y]=1;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：w_x_c_q (赞：10)

**并不感觉这道题和字符串有很大关系。。**

我的做法比较奇葩，开了一个很大的将近3000*3000的数组，去作为地图使用。

然后把起点放到一个比较中间的位置，因为Farmer John会向四个方向走。

之后O(n)扫一遍，对于每一个指令去模拟他走的过程。

这个模拟我是用map实现的。

最重要的是判断交点，以此来确定联通块的个数。

需要注意的问题：一个点可能在不同的方向意义上算作不同的交点。

简单来说，就是这个点是可以从其上下左右四个点走来的，那么如果从不同的点走到这个点，就有可能形成不同的联通快，所以这个点作为交点不能只被算作一次；

所以怎么做？

记录走到的每个点是由哪一个方向走来的就行。

开一个三维的桶：cz[x][y][z]=1表示x，y这个点已经由z方向延伸过。

那么每次找到焦点就只需要判断该方向上这个点有没有来过就可以了就可以了。

还有一个需要注意的问题，就是如何标记方向。

首先，我们如果是从A点走到B点，那么B点的A到B这个方向就要被标记。

同时，从A到B实际上是等效于从B到A的，所以我们也要标记A点的B到A的方向。

这道题就做完了（虽然我WA了很多次。。。）

代码在这里：
```cpp
/*
 by w_x_c_q
 建门
 模拟
 皮卡丘·· 
*/
#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
using namespace std;
int n;
char a[1005];
int ans[2999][2999];
int cz[2999][2999][4];
int dx[5]={0,0,-1,0,1};
int dy[5]={0,1,0,-1,0};
const int ox=1500;
int tot;
const int oy=1500;
map<char,int> q;
int main()
{
	memset(ans,0,sizeof ans);
	memset(flag,0,sizeof flag);
	q['N']=1;
	q['W']=2;
	q['S']=3;
	q['E']=4; //map存储方向 
	scanf("%d",&n);
	scanf("%s",a+1);
	int x=ox,y=oy;
	ans[x][y]++;
	for(int i=1;i<=n;i++){
		ans[x+dx[q[a[i]]]][y+dy[q[a[i]]]]++;
		x+=dx[q[a[i]]];y+=dy[q[a[i]]];
		if((!cz[x][y][q[a[i]]])&&(ans[x][y]>1))tot++;//判断是否是交点 
		cz[x][y][q[a[i]]]=1;//正向标记 
		cz[x-dx[q[a[i]]]][y-dy[q[a[i]]]][(q[a[i]]>2?q[a[i]]-2:q[a[i]]+2)]=1;//反向标记 
	}
	printf("%d\n",tot);
	return 0;
} 
```

---

## 作者：樱初音斗橡皮 (赞：4)

一道有意思的题，看到大多数人用搜索来做。然而yyc（我）的第一感认为这道题完全有一个更好的解法。

首先门的个数等于联通块的个数，等于增加的联通块的个数。

那么联通块是怎么出现的呢？

容易发现，如果后面走到一个前面走到过的点，就会出现一个联通块。

但这种做法有一个问题，如果走过一条以前走过的边，就会重复计算。

很简单，对边也判一次即可，如果走到一个走过的点而且没走到过边，就加一。

这里使用set实现。

更多解释在代码。

```
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <set>
using std::scanf;
using std::printf;
int n;
std::string s;
std::set<std::pair<int, int> > p;
std::set<std::pair<std::pair<int, int>, int> > e; //前两维为点，后一维为边的方向
int next[4][2]={1, 0, 0, 1, -1, 0, 0, -1}; //边的方向
int change(char c) //把字符变成边
{
    switch (c)
    {
        case 'N': return 0;
        case 'E': return 1;
        case 'S': return 2;
        case 'W': return 3;
    }
    printf("stupid yyc\n"); //滑稽
    return -1;
}
int ans;
int main()
{
    std::cin>>n;
    std::cin>>s;
    s=' '+s;
    std::pair<int, int> cur({0, 0}), lst; //cur当前点
    p.insert(cur);
    //printf("cur={%d, %d}\n", cur.first, cur.second);
    for (int i=1; i<=n; ++i)
    {
        int noe=change(s[i]); //number of edge
        lst=cur;
        cur.first+=next[noe][0];
        cur.second+=next[noe][1];
        //修改cur
        //printf("cur={%d, %d}, noe=%d\n", cur.first, cur.second, noe);
        if (p.find(cur)==p.end())
            p.insert(cur), e.insert(std::make_pair(cur, noe)), e.insert(std::make_pair(lst, (noe+2)%4));
        //双向建边
        else if (e.find(std::make_pair(cur, noe))==e.end())
            ++ans, e.insert(std::make_pair(cur, noe)), e.insert(std::make_pair(lst, (noe+2)%4));
    }
    printf("%d\n", ans);
    return 0;
}

```


---

## 作者：狸狸养的敏敏 (赞：2)

本题思路：

先对读入的字符串进行处理，处理出每一个栅栏的位置

然后因为栅栏都是连续的，所以，需要添加的门的数量就是封闭联通块的数量-1

如何计算联通块的数量呢？

考虑Flood-Fill？

我没试过，由于数据范围小$N\le 1000$

所以可以直接跑暴力完全没有问题

下面给出复杂度证明

由于我们在走的时候每个点只走一次，即使全图走一遍

也只有$O(R*C)$的复杂度（即面积）

按最坏复杂度看，（即创建了一个平行于X，Y轴并相交于原点的图）

那么复杂度是$O((\frac{N}{2})^{2})=O(\frac{N^2}{4})$

完全没有问题

最需要注意的点就是在处理栅栏的时候，可能会出现移动到负数的情况

一种方法是取一个较大的数为原点

另一种方法就是使用映射(map)或无序映射(unordered_map)

或者dalao不嫌烦的可以手打自然溢出

下面给出代码

```
#include<bits/stdc++.h>//万能头，不解释
#include<tr1/unordered_map>//后面用unordered_map要用
/*
因为unordered_map是用Hash实现的，所以建表复杂度是O(N)
查询复杂度基本控制在常数级别

而map使用的是红黑平衡树
复杂度一般为LogN级别的

为了时限(装逼)，我们采用unordered_map

或者可以把X,Y设置于较大的起点，就可以用普通数组了
*/
#define um unordered_map //宏定义一下
using namespace std;//标准命名库，不解释
using std::tr1::um;//宏定义过了，所以可以直接调用um

//不然正确的写法应该是 using std::tr1::unordered_map;
//因为unordered_map不属于C++0x标准库

//所以这一句非常重要！！

//想CE吗？去掉这一句就可以了

int tot,n,x,y,a,b,c,d;//tot记录联通块的数量

//n同题意

//x，y分别是FJ当前走到的位置

//a,b,c,d分别是枚举范围
um<int,um<int,bool> >q,f;//定义二维数组

//定义好之后后面的q,f就可以和普通数组一样用了

char ch;//读取FJ行进的方向
void mv(int xx,int yy)//移动
{
    if(xx<a||xx>c||yy<b||yy>d||f[xx][yy])return;//判断边界条件
    f[xx][yy]=1;//标记当前点已经走过防止下次再搜这个联通块
    if(!q[xx][yy+1])//若下一格不是栅栏，即可跳过这一格，填充当前联通块
    mv(xx,yy+2);//这里解释下为什么是+2
	
	/*
	我们在行进的时候必然要考虑到不重复性
	而FJ每走一步
	不是在当前位置留下栅栏，请看题目
	
	'例如，如果他的第一步向北，他建造一单位从(0,0)到(0,1)的围栏。'
	
	从这句话我们可以看到，FJ的栅栏建造是双位置的，即跨越性的
	
	如果你还是不理解，这里有一个栗（例）子
	
	OOOOOOO
	OOOOOOO
	O+++OOO
	O+O+++O
	O+O@O+O
	O+OOO+O
	O+++++O
	
	其中，O为草地的位置
	+为围栏的位置
	@为我们现在所到的位置
	
	如果走一格，会踏到围栏上，这不是我们想看到的
	所以防止这种事情的产生，我们只能两格两格跨
	*/
    if(!q[xx][yy-1])
    mv(xx,yy-2);
    if(!q[xx+1][yy])
    mv(xx+2,yy);
    if(!q[xx-1][yy])
    mv(xx-2,yy);
	
	//皆同上
} 
int main()
{
    scanf("%d",&n);//输出
    a=b=INT_MAX;//极限值赋值
    c=d=INT_MIN;
    for(int i=1;i<=n;i++)
    {
        scanf("%c",&ch);//读入字符
		while(ch!='N'&&ch!='E'&&ch!='S'&&ch!='W')
		scanf("%c",&ch);//防止空格，回车等奇奇怪怪的字符
		//如果不加这句话会WA第二个点（别问我怎么知道的）
        if(ch=='N')
        {
            y+=2;
            q[x][y-1]=1;
        }//建栅栏的过程
		
		//为什么两格两格跨上面已经解释过了
        if(ch=='E')
        {
            x+=2;
            q[x-1][y]=1;
        }
        if(ch=='S')
        {
            y-=2;
            q[x][y+1]=1;
        }
        if(ch=='W')
        {
            x-=2;
            q[x+1][y]=1;
        }
		//皆同上
        if(x<a)a=x;
        if(y<b)b=y;
        if(x>c)c=x;
        if(y>d)d=y;
		//更新最大与最小值
    }
    a--,b--,c++,d++;
	/*
	这里解释下为什么要边界向外扩展
	
	考虑这种情况
	
	OO+OO
	OO+OO
	OO+OO
	OO+OO
	OO+OO
	
	O，+的含义皆同上
	
	如果不把边界扩展出去，我们会扫到两个联通块，即左边和右边
	
	但是实际上
	拓展出去之后
	
	OOOOOOO
	OOO+OOO
	OOO+OOO
	OOO+OOO
	OOO+OOO
	OOO+OOO
	OOOOOOO
	
	就会扫到只有1个联通块了
	
	有效防止了栅栏落在边界的情况
	*/
    for(int i=a;i<=c;i++)
    {
        if((i-a)&1)continue;//如果是奇数位置，直接跳过
        for(int j=b;j<=d;j++)//开始枚举
        {
            if((j-b)&1)continue;
            if(f[i][j])continue;//如果当前块已经走过，跳过
            mv(i,j);//从i，j开始移动
            tot++;//联通块个数+1
        }
    }
    printf("%d\n",tot-1);//输出联通块的个数-1
    return 0;
}
```

~~我应该是讲的最详细的题解了吧QWQ~~

---

## 作者：duchengjun (赞：1)

**USACO 的质量是真的高。**

# 题目大意

让你求出一共有**不包含其它环的封闭的环**。

# 分析

这一题以 $(0,0)$ 为起点，有一个问题——出现了负数下标，样例都不对。

那么，我们第一个想法是把起点改掉。

∵$n ≤ 1000$

∴我们设起点为 $(1000,1000)$ 即可。

一个点如果到过，那么从另一个没走过的方向再次到这个点会形成一个新的不包含其它环的封闭的环。

因为题目间接的告诉了我们这个图。

所以我们只需要模拟一下即可。

# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=2*1000+10;
int n,x,y,nx,ny;
int vis[N][N],id[N][N],ans;
bool f[N][N];
int cnt;
char c;
signed main(){
	x=1000,y=1000,nx=1000,ny=1000;
	ans++;
	vis[1000][1000]=true;
	id[1000][1000]=1;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='N')x++;
		else if(c=='E')y++;
		else if(c=='S')x--;
		else y--;
		if(!vis[x][y])
			id[x][y]=++ans;
		int a=id[nx][ny],b=id[x][y];
		if(!f[a][b]&&vis[x][y])
			cnt++;
		f[a][b]=f[b][a]=true;
		nx=x,ny=y;
		vis[x][y]=true;
	}
	cout<<cnt;
	return 0;
}

```

---

## 作者：wangzikang (赞：1)

~~这题真\**毒瘤~~

蒟蒻第一次写题解，~~水点咕值~~有不对的地方敬请补充。


首先，我们想到~~大法师~~dfs法求解统计封闭区域,代码如下：
```cpp
int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0}/*dfs模板*/，Map[4010][4010]/*存储栅栏*/;
void dfs(int x,int y){//记忆搜索
    Map[x][y]=1;//标记
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i]
        if(xx>=zx-1&&xx<=cx+1&&yy>=zy-1&&yy<=cy+1&&!Map[xx][yy])dfs(xx,yy);//如果在范围内&&没有走过，就在深一层dfs
    }
}
```
这点没什么可讲的~~是个OIer都会~~。

# 毒瘤处1：

我们想存栅栏,存栅栏代码如下：
```cpp
for(int i=0;i<n;i++){
    char c=getchar();
    if(c=='N'){
        Map[sx][++sy]=1;
    }else if(c=='S'){
        Map[sx][--sy]=1;
    }else if(c=='E'){
        Map[++sx][sy]=1;
    }else{
        Map[--sx][sy]=1;
    }
    cx=min(sx,cx);
    zx=max(sx,zx);
    cy=min(sy,cy);
    zy=max(sy,zy);
    //找最小左上点，最大右下点
}
```
等一下!这个代码是错的，你连样例都过不了。

由于有可能会出现一个四宫格，那样的封闭区域~~大法师~~dfs统计不出来，所以一下要走两次。~~不想放代码了~~

# 毒瘤处2：

等一下!改过的代码是错的，你连样例都过不了。

由于有假封闭区域，所以我们应该把~~大法师~~dfs范围扩大一个格子。（rt）
应是两个封闭区域，但识别出来的是四个。

![tp](https://cdn.luogu.com.cn/upload/image_hosting/1xt6shej.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
# 毒瘤处3：

等一下!改过的代码是错的，你连第二个点都过不了。

第二个点有一个换行符，在洛谷IDE能测出来，但本地是对的。

所以要把输入换成:

```cpp
char c=getchar();
while(!isupper(c))c=getchar();
```
其他简单的放在代码注释中。
```cpp
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0}/*dfs模板*/,n,cx=-200000000,cy=-200000000,zx=0x7fffffff,zy=0x7fffffff,/*最小左上点，最大右下点*/Map[4010][4010]/*存储栅栏*/,ans=-1;//如有n个联通块，则有n-1个门所以ans设为-1
template<class T>void read(T &x){//快读
    x=0;int f=0;char ch=getchar();
    while(!isdigit(ch))  {f|=(ch=='-');ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x-11;
}
template<class T>void write(T x){//快写
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'1');
}
void dfs(int x,int y){//记忆搜索
    Map[x][y]=1;//标记
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i]
        if(xx>=zx-1&&xx<=cx+1&&yy>=zy-1&&yy<=cy+1&&!Map[xx][yy])dfs(xx,yy);//如果在范围内&&没有走过，就在深一层dfs
    }
}
int sx,sy;//起始点
int main(){
	int temp[100000001];
    read(n);
    sx=sy=2005;//如果你把FJ的起点定在(0,0)处的话，那么FJ最开始就往左||上建围栏，就会访问到像（0,-1）这样的点，数组访问到负数会RE
    Map[sx][sy]=1;//标记中点走过了
    for(int i=0;i<n;i++){//输入n个字符
        char c=getchar();
        //第二个测试点有一个Linux下的\r换行符，这个地方害的我调了一周，还是老师帮我调出来的(大雾
        while(!isupper(c))c=getchar();
        if(c=='N'){//有可能会出现一个四宫格，那样的封闭区域dfs统计不出来，所以一下走两次
            Map[sx][++sy]=1;
            Map[sx][++sy]=1;
        }else if(c=='S'){
            Map[sx][--sy]=1;
            Map[sx][--sy]=1;
        }else if(c=='E'){
            Map[++sx][sy]=1;
            Map[++sx][sy]=1;
        }else{
            Map[--sx][sy]=1;
            Map[--sx][sy]=1;
        }
        cx=max(sx,cx);
        zx=min(sx,zx);
        cy=max(sy,cy);
        zy=min(sy,zy);
        //找最小左上点，最大右下点
    }
    //把左上点，右下点都扩大一格，方便统计封闭区域数量
    cx++;
    cy++;
    zx--;
    zy--;
    //dfs统计封闭区域数量
    for(int i=zx;i<=cx;i++){
        for(int j=zy;j<=cy;j++){
            if(!Map[i][j]){
                dfs(i,j);//走过了，且没有围栏，就dfs一下
                ans++;//建的门数量加一
                j=zy;
            }
        }
    }
    write(ans==-1?0:ans);//输出,如果是-1（没有），输出0，否则输出ans
    return 0;
}
```


~~不认真干活的后果~~

---

## 作者：1124828077ccj (赞：1)

这题可用DFS，枚举有多少个封闭图形，答案就是封闭图形数量-1，主要就是处理栅栏比较麻烦。

```cpp
#include<cstdio> 
#include<cstdlib> 
int ans,n,x,y,a,b,r,c,l; 
bool f[4002][4002],q[4002][4002]; 
char t[1002]; 
void ccj(int xx,int yy){ 
     if (xx<a || xx>r || yy<b || yy>c || f[xx][yy])return; 
     f[xx][yy]=1; 
     if (!q[xx][yy+1])ccj(xx,yy+2); 
     if (!q[xx][yy-1])ccj(xx,yy-2); 
     if (!q[xx+1][yy])ccj(xx+2,yy); 
     if (!q[xx-1][yy])ccj(xx-2,yy); 
} 
int main() 
{ 
    a=1e9;b=1e9;r=-1e9;c=-1e9; 
    scanf("%d%s",&n,t);x=2000;y=2000; 
    for (int i=0;i<n;i++) 
    { 
        if (t[i]=='N'){x+=2;q[x-1][y]=1;} 
        if (t[i]=='E'){y+=2;q[x][y-1]=1;} 
        if (t[i]=='S'){x-=2;q[x+1][y]=1;} 
        if (t[i]=='W'){y-=2;q[x][y+1]=1;} 
        if (x<a)a=x;if (y<b)b=y;if (x>r)r=x;if (y>c)c=y; 
    } 
    a--;b--;r++;c++; 
    for (int i=a;i<=r;i+=2) 
    for (int j=b;j<=c;j+=2) 
    { 
        if (f[i][j])continue; 
        ccj(i,j);ans++; 
    } 
    printf("%d",ans-1); 
    return 0; 
}
```

---

## 作者：羚羊WANG (赞：0)

看完输入，好像是一个字符串的问题，再仔细一想，好像跟字
符串没有任何关系

我的做法十分的~~寻常~~，直接用$O(n)$的时间暴力模拟奶牛走的情况

每次走到一个点，我们可以用一个三维数组来记录走的情况

用$f_i$,$_j$,$_k$ = 1表示$(i,j)$这个点从$k$方向走来

每次走过一个点的时候，我们都要队这个点进行标记

**$Q:$那怎么标记呢**

其实，我们可以发现，从$north$与$south$或者从$east$与
$west$走来都是一样的

所以，我们每从一个点走过来，都要对当前结点进行方向标记
最后统计答案即可

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))
		{
			f|=(c=='-');
			c=getchar();
		}
	while(isdigit(c))
		{
			x=(x<<3)+(x<<1)+(c^48);
			c=getchar();
		}
	return f?-x:x;
}
inline void write(int x){
	if(x<0)
		{
			putchar('-');
			x=-x;
		}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int n;
char s[1500];
map<char,int> num;
int f[3010][3010][4];
int l[3010][3010];
int dx[5]={0,0,-1,0,1};
int dy[5]={0,1,0,-1,0};
int ans;
int k;
int x,y;
inline void into(){
	num['N']=1;
	num['S']=3;
	num['E']=4;
	num['W']=2;
	n=read();
	scanf("%s",s+1); 
	x=1500;
	y=1500;
	l[x][y]++;
	for(register int i=1;i<=n;++i)
		{
			char c;
			c=s[i];
			x=x+dx[num[c]];
			y=y+dy[num[c]];
			l[x][y]++;
			if(!f[x][y][num[c]] && l[x][y]>1)
				ans++;
			f[x][y][num[c]]=1;
			if(num[c]>2)
				f[x-dx[num[c]]][y-dy[num[c]]][num[c]-2]=1;
			else
				f[x-dx[num[c]]][y-dy[num[c]]][num[c]+2]=1;
		}
}
signed main(){
	into();
	write(ans);
	return 0;
}
```


---

## 作者：Zenith_Yeh (赞：0)

不难发现，每多一个交点，就会多一个封闭图形（也就是要多开一扇门）。

所以此题的难度就在于，如何求交点。

我们记一下自己的东南西北（~~为什么不叫上下左右呢，因为雀打多了~~）方向是否有栅栏即可，若一个点被走过两次或以上就是交点。

**上菜：**
```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
int n,mapp[2005][2005],now_x=1000,now_y=1000,ans;
bool bj[2005][2005][4];//0北，1东，2南，3西
int main()
{	scanf("%d",&n);
	mapp[now_x][now_y]++;
	for(register int i=1;i<=n;++i)
	{	char c;
        cin>>c;
		switch(c)
		{	case 'N'://北的情况
			{	if(bj[now_x][now_y][0]==0&&bj[now_x-1][now_y][2]==0)
                {   mapp[now_x-1][now_y]++;
                    if(mapp[now_x-1][now_y]>=2)ans++;
                }
				bj[now_x][now_y][0]=bj[now_x-1][now_y][2]=1;
                now_x--;
                break;
			}
			case 'E'://东的情况
			{	if(bj[now_x][now_y][1]==0&&bj[now_x][now_y+1][3]==0)
                {   mapp[now_x][now_y+1]++;	
                    if(mapp[now_x][now_y+1]>=2)ans++;
                }
				bj[now_x][now_y][1]=bj[now_x][now_y+1][3]=1;
                now_y++;
                break;
			}
			case 'S'://南的情况
			{	if(bj[now_x][now_y][2]==0&&bj[now_x+1][now_y][0]==0)
                {   mapp[now_x+1][now_y]++;	
                    if(mapp[now_x+1][now_y]>=2)ans++;
                }   
				bj[now_x][now_y][2]=bj[now_x+1][now_y][0]=1;
                now_x++;
                break;
			}
			case 'W'://西的情况
			{	if(bj[now_x][now_y][3]==0&&bj[now_x][now_y-1][1]==0)
                {   mapp[now_x][now_y-1]++;
                    if(mapp[now_x][now_y-1]>=2)ans++;
                }
				bj[now_x][now_y][3]=bj[now_x][now_y-1][1]=1;
                now_y--;
                break;
			}
		}
	}
	cout<<ans;
	return 0;
}
//N（北），E（东），S（南）,或W（西）
```


---

## 作者：nbqdd_2003 (赞：0)

这道题可以直接**暴力枚举**

栅栏把农场分割成一堆块

有m块就要m-1的门（两块之间要一个门）

代码如下：

```pascal
var
  total,n,x,y,a,b,c,d,i,j:longint;
  f,q:array[0..4001,0..4001]of boolean;
  ch:char;
procedure fsb(xx,yy:longint);
begin
  if (xx<a)or(xx>c)or(yy<b)or(yy>d)or(f[xx][yy]) then//如果超出划定的范围或来过就退出
    exit;
  f[xx][yy]:=true;//这个标记为已来过
  if not q[xx][yy+1] then//没有栅栏就往这个方向延伸
    fsb(xx,yy+2);
  if not q[xx][yy-1] then
    fsb(xx,yy-2);
  if not q[xx+1][yy] then
    fsb(xx+2,yy);
  if not q[xx-1][yy] then
    fsb(xx-2,yy);
end;
begin
  readln(n);
  a:=maxlongint;//从无限远端开始
  b:=maxlongint;
  c:=-maxlongint;
  d:=-maxlongint;
  x:=2000;//从中心开始
  y:=2000;
  for i:=1 to n do
    begin
      read(ch);
      if ch='N' then
        begin
          y:=y+2;
          q[x][y-1]:=true;//构建栅栏
        end;
      if ch='E' then
        begin
          x:=x+2;
          q[x-1][y]:=true;
        end;
      if ch='S' then
        begin
          y:=y-2;
          q[x][y+1]:=true;
        end;
      if ch='W' then
        begin
          x:=x-2;
          q[x+1][y]:=true;
        end;
      if x<a then//缩小枚举的范围，防止超时
        a:=x;
      if y<b then
        b:=y;
      if x>c then
        c:=x;
      if y>d then
        d:=y;
    end;
  dec(a);//往里一格
  dec(b);
  inc(c);
  inc(d);
  for i:=a to c do
    begin
      if (i-a)mod 2=1 then//跨2格
        continue;
      for j:=b to d do
        begin
          if (j-b)mod 2=1 then
            continue;
          if f[i][j] then//来过
            continue;
          fsb(i,j);
          inc(total);//加一块
        end;
    end;
  writeln(total-1);
end.
```

---

