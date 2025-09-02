# Einstein学画画（数据有误）

## 题目背景

**本题数据有误，请不要提交。**

## 题目描述

Einstein 学起了画画。

此人比较懒\~\~，他希望用最少的笔画画出一张画……

给定一个无向图，包含 $n$ 个顶点（编号 $1 \sim n$），$m$ 条边，求最少用多少笔可以画出图中所有的边。

## 说明/提示

对于 $50 \%$ 的数据，$n \le 50$，$m \le 100$。

对于 $100\%$ 的数据，$1 \le n \le 1000$，$1 \le m \le {10}^5$。

## 样例 #1

### 输入

```
5 5
2 3
2 4
2 5
3 4
4 5
```

### 输出

```
1```

# 题解

## 作者：TheAutumnGlory (赞：71)

### ~~CSP马上到了,赶紧复习图论，顺便写下题解~~
**题目要使画的次数最小，那么我们就可以知道最小的次数为1**

## 于是这道题就是一笔画（欧拉路）板题，甚至还不需要求路径。

先来说一下什么是欧拉路吧：
## 七桥问题
![](https://cdn.luogu.com.cn/upload/image_hosting/vi5bjbo9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 欧拉说：是否可从某个地方出发，经过每座桥一次,回到原来出发的地方？

然后七桥问题就能转化成如下的一个**无向图**：

![](https://cdn.luogu.com.cn/upload/image_hosting/azdp2wgb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

**顶点的度**，就是指和该顶点相关联的边数。

**出度**：有向图中从某顶点出发的边数。

**入度**：有向图中在某顶点结束的边数。

## 欧拉回路：
```
若恰通过图中每条边一次回到起点,则称该回路为欧拉(Euler)回路。
具有欧拉回路的图称为欧拉图。
定理1：
一个无向图是欧拉图，当且仅当该图所有顶点度数都是偶数。
一个有向图是欧拉图，当且仅当该图所有顶点度数都是0(入度与出度之和)。
定理2：
存在欧拉回路的条件：图是连通的，且不存在奇点（顶点度数为奇数）

```

## 欧拉路（此题解法 ！）
```
若从起点到终点的路径恰通过图中每条边一次（起点与终点是不同的点），
则该路径称为欧拉路。
定理1：
存在欧拉路的条件：图是连通的，且存在2个奇点。
如果存在2个奇点，则欧拉路一定是从一个奇点出发，以另一个奇点结束。

```
### 注意：一个连通图只可能有偶数个奇点

那么我们可以从**欧拉路**的介绍，发现只有2个奇点才能1笔画完。

$code:$
```
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt[1005],ans;
cnt[x]:x的度数
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		cnt[x]++;x点度数+1
		cnt[y]++;y点度数+1
	}
	for(int i=1;i<=n;i++)
		if(cnt[i]%2)判断是否为奇点
			ans++;奇点个数+1
	if(ans==2)若只有2个奇点
		puts("1");则可以一笔画完
	return 0;
}
```

## 现在我们已经知道如何判断欧拉路了

**然后我们可以发现若每多出两个奇点，那么画的次数就会+1**

**又因为连通图只可能有偶数个奇点**

**所以，答案为$ans/2$**

$code:$
```
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt[1005],ans;
cnt[x]:x的度数
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		cnt[x]++;x点度数+1
		cnt[y]++;y点度数+1
	}
	for(int i=1;i<=n;i++)
		if(cnt[i]%2)判断是否为奇点
			ans++;奇点个数+1
	printf("%d\n",ans/2);
	return 0;
}

```
### 于是我们愉快的交了上去，WA90。。。。。

这是为什么呢？？

根据我们上面的做法，发现下列~~手购~~数据过不了：
```
3 3
1 2
2 3
3 1
```
利用[构图](https://csacademy.com/app/graph_editor/)我们可以得到这幅图：

![](https://cdn.luogu.com.cn/upload/image_hosting/owz8b0x1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 咦，发现这3个点都不是奇数点，但也可以一笔画完，所以我们只需要特判一下即可AC

$code:$
```
#include<bits/stdc++.h>上面代码已经有注释了，就不打了qwq
using namespace std;
int n,m,cnt[1005],ans;
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		cnt[x]++;
		cnt[y]++;
	}
	for(int i=1;i<=n;i++){
		if(cnt[i]&1==1)
			ans++;
	}
	if(ans==0)
		puts("1");
	else
		printf("%d\n",ans/2);
	return 0;
}
```



---

## 作者：NHZX0108 (赞：29)

本来想建图写的，但刚好前几天复习了图论，这里其实就是单纯考察对半欧拉图概念的理解与深化，不懂的同学点链接自己看：http://baike.sogou.com/v10809694.htm?fromTitle=%E5%8D%8A%E6%AC%A7%E6%8B%89%E5%9B%BE

另外再附一下代码：

```cpp
#include<bits/stdc++.h>//万能头文件大法好 
using namespace std;
int a[10001];    
int n,m,ans;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        a[x]++;
        a[y]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]%2==1)
              ans++;
    }
    if(ans)
       cout<<ans/2;
    else
       cout<<ans+1;
    return 0;
}//发了才觉得跟楼上写的好像
```

---

## 作者：Chemist (赞：16)

# 洛谷P1636 Einstein学画画(欧拉图)
~~个人认为这道题的数据有些问题~~
## 分析
这道题就是一个简单的欧拉回路的模板，统计每个点的度数，如果每个点的度数都为偶数，那么就可以一笔画(因为每个点都有进有出)，否则统计度数为奇数的点的个数(记为num)答案就是num/2(每次都把度数为奇数的点分别作为起点和终点)。
## AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,dg[1010],a,b,num=0;
//dg记录每个点的度数
bool map[1010][1010];
//用邻接矩阵储存图
long long read()//快读
{
    long long ans=0;
    char ch=getchar(),last=' ';
    while(ch<'0'||ch>'9')
    {last=ch;ch=getchar();}
    while(ch>='0'&&ch<='9')
    {ans=ans*10+ch-'0';ch=getchar();}
    if(last=='-')ans=-ans;
    return ans;
}
void add(int x,int y)//加入
{
    dg[x]++;dg[y]++;
    map[x][y]=map[y][x]=true;
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        a=read();b=read();
        add(a,b);
    }
    for(int i=1;i<=n;i++)
        if(dg[i]&1==1)num++;
    if(num==0||num==2)cout<<"1";
    else cout<<num/2;
    return 0;
}
```
## However
根据数据来看，这道题并未考虑该图是否为连通图，如果不连通，需要找到每一版块画的次数再累加。

这里还有一个小技巧，就是统计奇数偶数可以用bool数组存，每次取反，省空间

## 正确代码(54分qwq)：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,fa[1010],cnt[1010]={0},ans=0;
bool dg[1010],visit[1010];
long long read()//快读 
{
	long long ans=0;
	char ch=getchar(),last=' ';
	while(ch<'0'||ch>'9')
	{last=ch;ch=getchar();}
	while(ch>='0'&&ch<='9')
	{ans=ans*10+ch-'0';ch=getchar();}
	if(last=='-')ans=-ans;
	return ans;
}
int get(int k)//寻找根节点 
{
	if(fa[k]==k)return k;
	else return fa[k]=get(fa[k]);
}
void Union(int x,int y)//合并 
{
	fa[get(x)]=get(y);
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
	 fa[i]=i;
	for(int i=1;i<=m;i++){
	 a=read();b=read();
	 dg[a]=!dg[a];dg[b]=!dg[b];
     //真为奇数，假为偶数 
	 visit[a]=true;
	 visit[b]=true;
	 //访问过标记为true
     if(get(a)!=get(b))Union(a,b);
     //如果不在一个集合就合并 
	}
	for(int i=1;i<=n;i++){
	 if(dg[i])cnt[get(i)]++;
     //统计每个点所在的图共有几个度数为奇数的 
	}
	for(int i=1;i<=n;i++){
		if(get(i)==i&&visit[i]){
        //如果是根节点同时已经被访问过 
		 if(cnt[i]>0)ans+=cnt[i]>>1;
         //加上该图的答案 
		 else ans++;
         //否则该图可以一笔画，答案加1 
		}
	}
	cout<<ans;
	return 0;
}
```
### 祝早日学会图论！

---

## 作者：hyzxxqc (赞：9)

### 如果大家有 ~~被一笔画折磨过的经历~~ 学过一笔画，那么这道题就不难了

#### 如果没学过一笔画，请仔细地看我所写的话~~（反正也看不懂）~~

先统计每个点引出的线段有几个是奇数（储存在sum）

如果sum为0 就输出1

反之输出ceil(sum/2.0)

献上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int m,n,line[1001],x,y,sum;
int main()
{
	cin>>n>>m;//输入，不用说
	for (int i=1;i<=m;i++)//统计每个点引出几条线
	{
		cin>>x>>y;
		line[x]++;
		line[y]++;
	}
	for (int i=1;i<=n;i++)
		if (line[i]%2==1)//如果是奇数就统计入sum
			sum++;
	switch (sum)
	{
		case 0:cout<<1;break;//如果sum为0 就输出1
		default:cout<<ceil(sum/2.0);break;//反之输出ceil(sum/2.0) ###注意### 要除以2.0不是2
	}
	return 0;//是不是觉得很简单？？？
}
```

---

## 作者：封禁用户 (赞：7)

kcm 布置的题。。蒟蒻前来水篇题解/ts

我们都知道，一张图只要有$0/2$ 个奇点，就能一笔画。

不难想到，该图若不能一笔画，则需要**奇点数$/2$ 笔**才能画出。

那就可以用邻接表来实现了，读入各无向边，统计奇点个数，然后判断。

看到大佬们都直接用数组存，没存边，用vector 的蒟蒻瑟瑟发抖。


~~kcm 为啥不教vector呀，vector 大法好啊~~

Code


```cpp
#include<cstdio>
#include<vector>
using namespace std;
vector<int> g[1000];
int n,m,x,y,num;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);//建边
    }
    for(int i=1;i<=n;++i)
        if(g[i].size()%2==1)
            ++num;//num为奇点数
    if(num==2||num==0)
        printf("1");//能一笔画
    else
        printf("%d",num/2);//不能一笔画
    return 0;
}
```

[End.](https://www.luogu.com.cn/blog/CM0/)

---

## 作者：xvhuanlin (赞：7)

本题其实就是考察简单半欧拉图及其扩展定理，设顶点的度数为连接的边数，然后统计所有顶点中度数为奇数的顶点的个数n，则答案一定为n/2。

首先，根据握手定理，所有顶点的度数之和一定为偶数。则奇数顶点的个数一定为偶数。然后每画一笔，最多可以使奇数顶点个数减少两个（或者不减少），所以一定至少要n/2笔，才能把画画完。

有一个特殊情况，即为所有点构成一个环的情况。此时n=0，但实际上需要一笔画完（即欧拉图），所以需要特判一下。


---

## 作者：我丑得精致 (赞：6)

一笔画判断：奇点数为2或0或大于2且不被2整除的图

X笔画判断： 奇点数为1及2以上的图，奇点数为N，则X=N整除2

代码；

```cpp
var n,m,i,x,y,t:longint;
    a,b:array[1..100001]of longint;
begin
  readln(n,m);
  for i:=1 to m do
  begin
    readln(x,y);
    inc(a[x]);        //统计点连边的边数
    inc(a[y]);
  end;
  t:=0;
  for i:=1 to n do
    if a[i] mod 2=1 then inc(t);     //是奇点，t统计奇点数
  if t shr 1 =0 then writeln(1)      //是个环，一笔画
  else writeln(t shr 1);               //X=t 整除 2
end.
```

---

## 作者：浪遏 (赞：3)

此题其实运用一些方法就可以过了。我们可以知道，一幅图的奇数顶点必为偶数个，画一笔最多可以取消2个奇数顶点，那么除了0个外其余的图只要统计奇数点个数再除以二即可，0个的另外判断。

```cpp
var n,m,i,j,x,y,max:longint;
f:array[1..1000000] of longint;
begin
readln(n,m);
for i:=1 to m do
begin
readln(x,y);
if x>max then max:=x;
if y>max then max:=y;
f[x]:=f[x]+1;                               //判断这个点的奇偶
f[y]:=f[y]+1;
end;
j:=0;
for i:=1 to max do
if f[i] mod 2=1 then j:=j+1;         //如果是奇点个数加1
if j=0 then writeln(1)                  //奇点为0时需要特殊判断
else writeln(j div 2);                    //一笔能去除2奇点，所以除2即可
end.

```

---

## 作者：Victory_Defeat (赞：2)

虽然跟楼上各位写得差不多，但是！

#我使用了~~无敌~~的位运算！

其实很简单（没什么用……）

在此，先解释一下按位与（&）：,a&b是指将a，b分别转为二进制，然后逐位比较，如两者的同位皆为1，则结果的该位为1，否则为0。

那么，可以看出%2为1的数二进制末尾必为1，否则必为0，1&1为1,0&1为0，那么该数&1的结果即可判断奇偶性。

#综上所述：a&1=1，a为奇数，否则，a为偶数

~~位运算大法好！！！~~

闲话不多说，下面奉上代码：

```cpp
#include<cstdio>//位运算大法好 
inline void read(int &a)//快速读入 
{
    int k=1;//系数 
    char c=getchar();a=0;//定义字符，并进行第一次读入 
    while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}//如果不为数字，继续读入，特判：如为-号，系数变为-1 
    while(c>='0'&&c<='9'){a=a*10+c-'0';c=getchar();}//如果是数字，需将变量*10+当前数字 
    a*=k;//乘上系数 
}
int s,n,m,a,b,f[1010];//定义变量，s为度为奇数点总数，n，m变量见题意，a，b是读入的边的两端点，f数组统计点度数 
int main()
{
    read(n);read(m);//懒得解释 
    for(int i=1;i<=m;i++)
    {
        read(a);read(b);//读入 
        f[a]++;
        f[b]++;//两点的度+1 
    }
    for(int i=1;i<=n;i++)if(f[i]&1)s++;//如果当前点度为奇数，s++ 
    printf("%d",s?s/2:1);//输出s/2（s=0时输出1）（其中s为0或2时，能一笔画，故输出结果为1，这样快一些，又短） 
    //注意：这里使用了位运算！具体方法见上面说明！ 
}
```

---

## 作者：l1360300734 (赞：1)

/\*
这里用到一个定理，楼下说的已经很明白了，这里就复制以下OvO;

考察简单半欧拉图及其扩展定理，设顶点的度数为连接的边数,然后统计所有顶点中度数为奇数的顶点的个数n，则答案一定为n/2

用这个方法能过掉%90的点

第二个点是一个环，度为奇数的点为0个，但是好要一笔花完，这里就加一个特判，我第一次没加，就WA了好几次。。。

\*/
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int b[10001];
int main()
{
    int n,m,i,j,k,geshu=0,x,y;
    scanf("%d%d",&n,&m);
    for (i=1;i<=m;i++)//运用定理
```
{//运用定理
        scanf("%d%d",&x,&y);//运用定理

        b[x]++;//运用定理

        b[y]++;//运用定理

}//运用定理

```cpp
    for (i=1;i<=n;i++)
        if (b[i]%2==1)//判断度数
            geshu++;
    if (geshu)
        printf("%d",geshu/2);
    else//特判
        printf("%d",geshu+1);
}
```

---

## 作者：四宫辉夜 (赞：0)

不说了，这次差点自闭

一开始循环里写的i=0，结果有一个点WA了，改成i=1开始那个点就AC了

然后有三个点RE，怎么也过不去。去群里问大佬，得出的结论是数组开小了或者没用cin（我寻思着cin不是比scanf慢吗）改了之后还是不行

又读了几遍代码，发现是第二个for里面i的停止条件写错了，应该是<=n，写成了<=m

核心思路：小学奥数的一笔画问题，有0个或者2个奇数边点的图形可以一笔画，然后后面是如果N（N为偶数）个奇数边点的话，需要N/2笔画

此题题解其实已经非常多了，我就把我的放上来做个参考吧
~~~cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<cstring>
#include<string>
//气势磅礴的头文件
using namespace std;


int mp[11000],ans,n,m,a,b;//注意这里数组别开太小
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);//每次读入两个数
        mp[a]++;//这一行和下一行是给对应的点加一个数（也就是这个节点的度数）
        mp[b]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(mp[i]%2)
            ans++;
    }
    if(!ans)
        puts("1");
    else
        printf("%d\n",ans/2);
    return 0;
}


---

## 作者：LGG_ (赞：0)

先看了解一笔画的性质

~~转载~~

一笔画的判定条件：奇点数为0或2，奇点数就是从该点引出的线的数目为奇数（以下要注意，突出来的线）

奇点数为2的倍数：从该点引出的线为奇数的线的点数目有Ｎ个,则说明该图形为Ｎ/2笔画成。如下图，红色圈圈都为奇点数为8，4笔画。

.....

[~~链接~~](https://jingyan.baidu.com/article/60ccbceb59e10564cbb1976d.html)

然后就是这个极其简单的代码

```c
#include<iostream>
using namespace std;
int dx[1001],g[1001][1001];
int n,m,c;
int a,b;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		g[a][b]=g[b][a]=1;
		dx[a]++;
		dx[b]++;//入度和出度
	}
	for(int i=1;i<=n;i++)
	if(dx[i]%2==1)c++;
	if(c!=0)cout<<c/2;
	else cout<<"1";
	return 0;//好习惯
}
```
（复习qwq


---

## 作者：XQLG (赞：0)

小学的数学题——一笔画

小学数学老师教的，奇点等于0或2的时候，该图可以一笔画

奇点是个什么东西呢？？

奇点：从该点引出的线段有奇数个，则此点被称为奇点

因为这道题目并不是让我们判定一笔画，而是，看要有多少笔

所以，我们就可以寻找奇点，记录数字。

答案就是n/2或者n/0

因为，0不能当做被除数，所以，答案就是，n/2

还有就是，没有奇点的情况，n/2是等于0

但是，实际上，没有奇点的情况下，应该输出1

所以，需要特判

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10010],n,m,c,d,ans;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>c>>d;
		a[c]++;
		a[d]++;//引出的线有多少条
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]%2==1)
		{
			ans++;//计数器，有多少个奇点
		 } 
	}
	if(ans==0)
	{
		cout<<1;
	}
	else
	{
		cout<<ans/2;
	}
	return 0;
}
```


---

## 作者：Bronya18C (赞：0)

# 这不是图论，明明是数论！
---
## 我们先来了解一下一笔画的原理（欧拉一笔画原理）：
一个图形要能一笔画完成必须符合两个条件，

即图形是封闭联通的和图形中的奇点（与奇数条边相连的点）个数为0或2。

[哥德堡七桥问题](https://baike.baidu.com/item/%E4%B8%83%E6%A1%A5%E9%97%AE%E9%A2%98/2580504?fr=aladdin)

---

本题依靠的是数学，如上面欧拉一笔画原理，一笔画要符合两个条件：

### 1、封闭联通：
本题并不需要理，因为没有连的点直接不管。

### 2、奇点个数为2或0：
本题的关键。如果奇点个数为0或2，就输出1.

不然，就输出奇点个数/2(因为我们可以把一个图分为多个图，直到奇点个数为0或2)。

---
## 附上代码：
```
#include<bits/stdc++.h>

using namespace std;
long long N,M,a,b,n[100005],ans;
int main()
{
	cin>>N>>M;
	for(int i=1;i<=M;i++)
	{
		cin>>a>>b;
		n[a]++;
		n[b]++; 
	}
	for(int i=1;i<=N;i++)
	{
		if(n[i]%2==1)ans++;
	}
	if(ans==0||ans==2)cout<<1<<endl;
	else
	{
		cout<<ans/2<<endl;
	}
	return 0;
} 
```

---

## 作者：九指客 (赞：0)

特殊的一笔画问题

```cpp
#include<bits/stdc++.h>//万能头文件；
using namespace std;
int a[2010];
int ans=0;
int main()
{
    int i,j,k,m,n,x,y;
    scanf("%d%d",&m,&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        a[x]++;
        a[y]++;
    }
    for(i=1;i<=m;i++)
    {
        if(a[i]%2==1)//有奇数条路经过这个点；
        {
            ans++;
        }
    }
    if(ans)//必须没有或只有2个奇数点才能够一笔画，否则多一笔；
    printf("%d\n",ans/2);
    else //如果没有奇数点，可以一笔画；
    printf("1\n");
    return 0;
}
```

---

## 作者：ww3113306 (赞：0)

因为画一次最多画完2个边为奇数的点，所以只要统计边为奇数的点为多少就行了，这里我用了链表来存图，可能略复杂

```cpp
#include<bits/stdc++.h>
using namespace std;
struct abc{
    int t,next;    
};
struct ab{
    int num,j;//j表示这个点有多少条边
};
int n,m,tot=0,j;abc h[205000];ab head[1500];
void add(int x,int x2)//加边
{
    tot++;
    h[tot].t=x2;
    h[tot].next=head[x].num;
    head[x].num=tot;
    head[x].j++;
}
int main()
{
    int i,k,number=0,times=0,k2;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++)
    {
        scanf("%d",&k);
        scanf("%d",&k2);
        add(k,k2);//因为无向图，所以要加两次边
        add(k2,k);
    }
    for(i=1;i<=n;i++)//从1到n搜索边为奇数的点
        if(head[i].j%2==1)
            number++;//搜索到一个，number++
    times+=number/2;//笔画数先加number/2
    if(number%2==1) times++;//如果number是个奇数，那么这个点就需要额外画一笔，才能画到
    if(times==0) {printf("1");return 0;}//这个是第二个点的特判，第二个点全部都是边为偶数的点，但显然要画完还是要画一笔的
    printf("%d",times);//输出笔画数
    return 0;    
}

```

---

