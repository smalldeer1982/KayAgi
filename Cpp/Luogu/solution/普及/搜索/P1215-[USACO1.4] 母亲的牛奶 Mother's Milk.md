# [USACO1.4] 母亲的牛奶 Mother's Milk

## 题目描述

农民约翰有三个容量分别是 $a,b,c$ 升的桶。  

最初，$a,b$ 桶都是空的，而 $c$ 桶是装满牛奶的。有时，农民把牛奶从一个桶倒到另一个桶中，直到被灌桶装满或原桶空了。  

当然每一次灌注都是完全的。由于节约，牛奶不会有丢失。

写一个程序去帮助农民找出当 $a$ 桶是空的时候，$c$ 桶中牛奶所剩量的所有可能性。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le a,b,c \le 20$。

题目翻译来自NOCOW。

USACO Training Section 1.4


## 样例 #1

### 输入

```
8 9 10
```

### 输出

```
1 2 8 9 10
```

## 样例 #2

### 输入

```
2 5 10```

### 输出

```
5 6 7 8 9 10```

# 题解

## 作者：远航之曲 (赞：86)

发现没有c++的题解，果断来一发。


想出了好几种解法，我就一点一点地写吧。


方法 1:DFS 因为牛奶的总量是不变的，所以可以用a,b中的牛奶量做状态，初始状态是(0,0)，每次只能有6种选择，a倒b，a倒c，b倒a，b倒c，c倒a，c倒b。用一个数组vis[i][j]判重，s[i]记录c中所有可能值（s[i]=true表示c中可能出现i），如果当前状态是(0,x)，那么s[mc -x]=true，最后输出s中所有true的就可以了。 用vis[i][j][k]也行，也就是说三维的也行。


方法 2 这个题目也可以递归…不过我不知道临界点是多少,就乱试了,结果用i=14能过…不过我不知道为什么i要等于14,没证明过当i等于14时能包括大多数的过程… (假如用BFS。只有在扩充的状态没有出现过的情况下，才把它加入队列，这样可以保证不重不漏）


方法3 人脑解法 这题简直是赤裸裸的奥数啊，直接手动算出所有的解再让计算机输出了就行了！估计只用0微秒 由于题目不对称（a要为0），导致了源代码的丑陋。分a小于b和a大于等于b两种情况，每种情况各有两种不同的方法，不断用b灌a，或者反之，如果灌完了就用c充满继续，如果充不满就说明做完了，如果灌满了还有就把被灌的倒回c，然后继续灌。最多做20次循环，因为c<=20 最后输出很简单，先遍历数组到c-1，之后再输出（c）就行（c永远是一个解）


方法4 使用枚举的方法，按照顺序A，B，C寻找每一个牛奶非空的桶，假设我们找到了B， 则接下来只能是从B-》A或B-》C或则什么都不做这三种情况；使用递归来完成。 我们需要一个数组state[500][3]来储存遍历过的三个桶中牛奶的状态， 当 当前状态已经在之前出现过，就退出。同样也是使用一个数组bool leave\_c[]来储存C中可能的牛奶量。.这样或许更容易理解。


方法5 使用二进制保存状态，因为A,B,C都在1-20之间，所以可以分别用8位表示他们的容量

int a = (status&0xFF0000)>>16;

int b = (status&0x00FF00)>>8;

int c = (status&0x0000FF);

然后分别对a->b, a->c, b->c, b->a, c->a, c->b六种情况进行DFS， 用一个数组保存已经判断过的状态。


方法6 思维模式还是BFS， 把每种状态压成了一个点，如果能从状态k1转换到k2，[k1,k2]:=true; 即相当于连一条有向边。 然后不断更新，直到不能产生新的状态，最后扫描一次A桶为0的状态的点是否能到达即可。


方法7 模拟n次

设一个标记用的数组 f[0..20,0..20,0..20]记录f[a,b,c]的情况是否出现过...

6种倒法用递归循环一下..边界出口就是当前a，b，c内的牛奶量曾出现过

也就是 f[a,b,c]=true 时。。。程序巨短》。时间和其他差不多。。性价比 较高


方法8 将i从0到c带入一个bool函数f（i定义：c桶为i，a桶空），f的功能是bfs遍历到状态为（x,x,i）,判断能否遍历到或者此时的状态a是否为0；这样做效率貌似是很低的，不过可以加一个数组p[]，设定为全局变量，在遍历时遇到（0,x,i）的状态就记录，另外在将i带入f前判断p[i]是否记录过，这样一来效率大大提高了。


上代码

（减少代码复制，创造美好洛谷）

 
 
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAX = 22;
bool milk[MAX] = {0};
bool vis[MAX][MAX][MAX] = {0};
static int bkt[3];
void dfs(int a[]) {
    if (vis[a[0]][a[1]][a[2]]) return;
    vis[a[0]][a[1]][a[2]] = true;
    if (a[0] == 0) milk[a[2]] = true;
    //six ways to check, from bkt i to bkt j
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (j == i) continue;
            if (a[j] < bkt[j] && a[i] > 0) {
                int rec = std::min(bkt[j] - a[j], a[i]);
                int b[3];
                memcpy(b, a, sizeof(int)*3);
                b[i] -= rec, b[j] += rec;
                dfs(b);
            }
        }
    }
int main() {
    //freopen("milk3.in", "r", stdin);
    //freopen("milk3.out", "w", stdout);
    int &A = bkt[0], &B = bkt[1], &C = bkt[2];
    scanf(" %d %d %d", &A, &B, &C);
    int a[3] = {0,0,C};
    dfs(a);
    for (int i = 0; i < C; ++i) {
        if (milk[i]) printf("%d ", i);
    }
    printf("%d\n", C);
    return 0;
}
```

---

## 作者：zhanghanbin (赞：74)

本大菜鸡最喜欢使用 $ \LaTeX $

## 目录：

- 这题到底是什么意思——**理解题目** 

- 深搜怎么搜——**构造递归函数**

- 这题的坑好像比较弱——**填坑**

- 哇，竟然要输出所有的可能——**答案存储与回溯**

- ~~代码亮相^o^~~ cg:什么意思

   $XD$ 附加内容 [$\color{black}{:}$](https://binbin.blog.luogu.org/) 安利博客，<-咦，链接呢?
   
   提醒，找到链接的就在评论里留个言吧 ; - )

------

### 1. 题目大意

有三个桶，容量分别为 $A, B, C$ 。这三个桶中 $A, B$ 是空的，可以倒来倒去，最后问 $A$ 桶为空的时候，$C$ 桶中牛奶剩余量的种数。

$\text{得出结论，本题需\color{red}暴力}$

### 2. 暴力方法

不难发现，这一道题的搜索方向就是倒牛奶的方法：

$\color{DarkOrchid}{1.A \Rightarrow B}$

$\color{DarkOrchid}{1.A \Rightarrow C}$

$\color{DarkOrchid}{1.B \Rightarrow A}$ $\color{red}{\textbf{\small{注意，这里的牛奶是可以重复倒的，}}} $ $\color{green}{\text{\tiny(是个梗(KEN),会处理)}}$

$\color{DarkOrchid}{1.B \Rightarrow C}$

$\color{DarkOrchid}{1.C \Rightarrow A}$

$\color{DarkOrchid}{1.C \Rightarrow B}$

```cpp
void dfs (int a, int b, int c) {
    if (c >= (A - a)) dfs(A, b, c - (A - a));
    else dfs(c + a, b, 0);
    
    //后面的事，先不管
}

```
在这里，需要分为两种情况判断，第一种是被倒的桶满了，装不下了，也就是`c >= (A - a)`。另一种是不够倒了，那就是`c < (A - a)`，其中`A - a`是 $A$ 桶还能装的数量。

### 3. 填坑

这道题坑点在，你的 `vis` 数组，也就是记录情况的数组是三维的，但是这个三维数组的意义是记录 $A, B, C$ 三个桶的状态，所以 `dfs` 函数的模型大概是这样：
```cpp
void dfs (int a, int b, int c) {
    if (vis[a][b][c] == 1) return;
    else vis[a][b][c] = 1;
	
    if (c >= (A - a)) dfs(A, b, c - (A - a));
    else dfs(c + a, b, 0);
    
    //此处有省略大量重复内容，会在最后给出。
    //后面的事，先不管
}

```

### 4. 回溯与记录

答案是被暴力出来了，但是如何存储记录呢？

所以，这你就可以来一点 **桶排序** 然而其实排序是附赠的，我们需要的就只是一个统计功能。

我们新开一个数组 `rec[i]`。

于是就有了一段显而易见的代码：
```
if (a == 0 && rec[c] == 0) rec[c] = 1;
```

### 5. 最后

接下来就是最激动人心的时刻了，但是不是代码。

> cg：cao，我看了这么久的题解，最后竟然不是代码！
> zhb：别急，这可真的不是“最后”。  
> cg：emmmmmm。

那就是输出，输出自然就很简单，读入3个数 $A, B, C$ 先按题目要求调用 `dfs` 函数：
`dfs(0, 0, C);`

然后查找一下`rec`数组，

```
for (int i = 0; i <= 21; i++) {
    if (rec[i]) cout << i << ' ';
}
```


就大功告成了！

### 6. 代码

就是这样子啦：

> cg：代码呢！？   
> zhb：为净化洛谷社区环境，决定不上代码   
> cg：你竟然骗我看到完，我现在就给你踩，亏我还给你评论！   
> zhb：别冲动呀！

$\color{gray}{~~~~~~~~~~~~~~~~~~~~~~~~~~~}$

$\color{gray}{~~~~~~~~~~~~~~~~~~~~~~~~~~~}$

$\color{gray}{~~~~~~~~~~~~~~~~~~~~~~~~~~~}$

$\color{gray}{~~~~~~~~~~~~~~~~~~~~~~~~~~~}$

$\color{gray}{~~~~~~~~~~~~~~~~~~~~~~~~~~~}$

$\color{gray}{~~~~~~~~~~~~~~~~~~~~~~~~~~~}$

-----

### 咕咕，还没完呢！

-----

### 6. 代码

> zhb：像我这么好心的人，是不会不给代码的，所以还是   
> cg：远离代码抄袭犯罪，共建美好luogu！顶！


``` cpp
#include <iostream>

using namespace std;

int A, B, C;
int vis[22][22][22];
int rec[22];

void dfs(int a, int b, int c) {
	if (vis[a][b][c] == 1) return;
	else vis[a][b][c] = 1;
	
	if (a == 0 && rec[c] == 0) rec[c] = 1;
	
	if (c >= (A - a)) dfs(A, b, c - (A - a));
	else dfs(c + a, b, 0);
	
	if (c >= (B - b)) dfs(a, B, c - (B - b));
	else dfs(a, c + b, 0);
	
	if (b >= (A - a)) dfs(A, b - (A - a), c);
	else dfs(b + a, 0, c);
	
	if (b >= (C - c)) dfs(a, b - (C - c), C);
	else dfs(a, 0, b + c);
	
	if (a >= (C - c)) dfs(a - (C - c), b, C);
	else dfs(0, b, a + c);
	
	if (a >= (B - b)) dfs(a - (B - b), B, c);
	else dfs(0, a + b, c);
}

int main(int argc, char *argv[]) {
	cin >> A >> B >> C;
	dfs(0, 0, C);
	
	for (int i = 0; i <= 21; i++) {
		if (rec[i]) cout << i << ' ';
	}
	
	return 0;
}

注：由于在文章中已经详细阐述，所以不再提共注释！
```


---

## 作者：xun薰 (赞：31)

题解：DFS暴力枚举所有情况。

A可以倒给B和C

B可以倒给A和C

C可以倒给A和B

分别DFS，倒的时候判断当前的杯子是否能倒。

注意要判断当前状态是否存在过，我一开始就A倒给C,C倒给A，A又倒给C，死循环了。

最后sort一下输出。nowa为当前a杯子的奶的多少，ta为a杯子的容量。




```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int ta,tb,tc,k,ans[1020],vis[22][22][22];
void dfs(int nowa,int nowb,int nowc){
    if(vis[nowa][nowb][nowc])return;
    if(nowa==0)ans[++k]=nowc;
    vis[nowa][nowb][nowc]=1;
    if(nowc){
        if(nowa<ta)
        dfs(min(ta,nowa+nowc),nowb,nowc-(min(ta,nowa+nowc)-nowa));
        if(nowb<tb)
        dfs(nowa,min(nowb+nowc,tb),nowc-(min(tb,nowb+nowc)-nowb));
    }
    if(nowb){
        if(nowa<ta)
        dfs(min(ta,nowa+nowb),nowb-(min(ta,nowa+nowb)-nowa),nowc);
        if(nowc<tc)
        dfs(nowa,nowb-(min(tc,nowc+nowb)-nowc),min(tc,nowc+nowb));
    }
    if(nowa){
        if(nowb<tb)
        dfs(nowa-(min(tb,nowa+nowb)-nowb),min(tb,nowa+nowb),nowc);
        if(nowc<tc)
        dfs(nowa-(min(tc,nowa+nowc)-nowc),nowb,min(tc,nowc+nowa));
    }
    return;
}
int main(){
    scanf("%d%d%d",&ta,&tb,&tc);
    dfs(0,0,tc);
    sort(ans+1,ans+k+1);
    for(int i=1;i<=k;i++)printf("%d ",ans[i]);
    return 0;
}
LCA写炸两天了，这道题1A好高兴~
```

---

## 作者：Cambridge (赞：26)


这道题本蒟蒻用了宽度搜索的方法来做，望懂宽度搜索的大佬们多多赐教（毕竟在上小学的本蒟蒻掌握还不够）我们废话不多说，直接上代码，具体在程序中解释：

    #include<iostream>
	#include<cstdio>
	#include<cmath>
    #include<string>
    #include<cstdlib>
    using namespace std;//文件头不解释
    int n,m,ax,ay,bx,by,head,tail,f[100][100][100],tt,xx,yy,c[4],b[4],g[10000];//定义变量
    struct data
    {
        int a[4];
    }que[20*20*20+5];//结构体
    void bfs(int x,int y,int z)
    {
        head=0,tail=1;
        que[0].a[1]=x,que[0].a[2]=y,que[0].a[3]=z,f[x][y][z]=1;//初始化
        while(head!=tail)
        {
            for(int i=1; i<=3; i++)
                for(int j=1; j<=3; j++)
                {
                    if(i!=j)
                    {
                        for(int k=1; k<=3; k++)b[k]=que[head].a[k];//我们现在还不能更改que，先用b数组代替
                        if(b[i]>0&&b[j]<c[j])//如果可以倒牛奶
                        {
                            if(b[i]+b[j]<c[j])b[j]+=b[i],b[i]=0;//如果倒完之后被倒桶空了，b[j]+=被倒桶内的牛奶
                            else b[i]-=c[j]-b[j],b[j]=c[j];//如果倒完之后被倒桶内还有牛奶，被倒桶-=容量-被灌桶，被灌桶=此桶容量
                        }
                        if(f[b[1]][b[2]][b[3]]==1)continue;//如果此次操作已经出现过，不执行下面操作
                        f[b[1]][b[2]][b[3]]=1;//否则此次操作为1
                        que[tail].a[1]=b[1];//更改第一个桶
                        que[tail].a[2]=b[2];//更改第二个桶
                        que[tail].a[3]=b[3];//更改第三个桶
                        tail++;
                    }
                }
            head++;
        }
    }
    int main()
    {
      cin>>c[1]>>c[2]>>c[3];//读入三个桶的容量
      bfs(0,0,c[3]);
      for(int i=0; i<=c[2]; i++)
        for(int j=0; j<=c[3]; j++)
        if(f[0][i][j]==1)g[j]=1;
      for(int i=0; i<=c[3]; i++)
      {
        if(g[i]==1)cout<<i<<' ';//这个不用说了，输出所有可能性
      }
      return 0;
    }
    
看过的大佬们留下一个赞吧


---

## 作者：yangyiming (赞：26)

这是一个很牛逼的代码。

哪怕不是大佬也一定看得懂。

~~比下面的题解牛逼~~

看题目，总得来说就是三个桶互相倒，在c桶空的时候a桶的牛奶有几种可能。

**那么直接暴力枚举不就好了吗？**

只要枚举的次数够多并不超时，就可以AC了。

用随机数枚举六种可能，然后就是互相倒。

好了，一言不合上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[10000];
int main()
{
    long long s,i,x,n,a=0,b=0,c,as,bs,cs;
    srand(time(0)); 
    cin>>as>>bs>>cs;
    c=cs;
    f[c]=1;
    for(i=1;i<=22100000;i++) 
    { 
        if(a==0)
        {
            f[c]=1;
        }
        x=rand()%6;
        if(x==0)
        {
            if(bs-b>=a)
            {
                b+=a;
                a=0;
            }
            else
            {
                a-=bs-b;
                b=bs;
            }
        }
        else if(x==1)
        {
            if(cs-c>=a)
            {
                c+=a;
                a=0;
            }
            else
            {
                a-=cs-c;
                c=cs;
            }
        }
        else if(x==2)
        {
            if(cs-c>=b)
            {
                c+=b;
                b=0;
            }
            else
            {
                b-=cs-c;
                c=cs;
            }
        }
        else if(x==3)
        {
            if(as-a>=b)
            {
                a+=b;
                b=0;
            }
            else
            {
                b-=as-a;
                a=as;
            }
        }
        else if(x==4)
        {
            if(as-a>=c)
            {
                a+=c;
                c=0;
            }
            else
            {
                c-=as-a;
                a=as;
            }
        }
        else if(x==5)
        {
            if(bs-b>=c)
            {
                b+=c;
                c=0;
            }
            else
            {
                c-=bs-b;
                b=bs;
            }
        }
    }
    for(i=0;i<=30;i++)
    {
        if(f[i]==1)
        {
            cout<<i<<" ";
        }
    }
}
```

~~就是喜欢加括号，你咬我啊~~

---

## 作者：Kewth (赞：13)

本蒟蒻认为，这道题暴力深（生）搜就可以了，三个数据都不大，也不用担心超时。。。实现的话，以复制粘贴一堆判断各种情况的三位运算符（或者if else也可以，不过本蒟蒻偷懒觉得三位运算符比较方便）为主，具体的话看代码：










```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a,b,c;//3个桶的最大容量
int t2[21][21][21],t[21];//t2数组表示三种桶的状态是否出现过 ， t数组记录x桶空时z桶的值
void milk(int x,int y,int z)//x,y,z表示三种桶的牛奶数量
{
    if(t2[x][y][z]) return;//该状态出现过就剪枝
    if(!x) t[z]=1;//如果x桶空了，满足题目要求，记录当前z桶牛奶的数量
    t2[x][y][z]=1;//记录该状态
y+z>b?milk(x,b,y+z-b):milk(x,y+z,0);//将z倒进y,三位运算符对倒满和倒不满两种情况进行处理
x+z>a?milk(a,y,x+z-a):milk(x+z,y,0);//将z倒进x,三位运算符对倒满和倒不满两种情况进行处理
z+y>c?milk(x,z+y-c,c):milk(x,0,z+y);//将y倒进z,三位运算符对倒满和倒不满两种情况进行处理
x+y>a?milk(a,x+y-a,z):milk(x+y,0,z);//将y倒进x,三位运算符对倒满和倒不满两种情况进行处理
y+x>b?milk(y+x-b,b,z):milk(0,y+x,z);//将x倒进y,三位运算符对倒满和倒不满两种情况进行处理
z+x>c?milk(z+x-c,y,c):milk(0,y,z+x);//将x倒进z,三位运算符对倒满和倒不满两种情况进行处理
    return;
}
int main()
{
    scanf("%d %d %d",&a,&b,&c);
    milk(0,0,c);//进入深搜
    int q=1;//因为不能多空格，所以q表示是否是第一个答案（第一个前面不打空格）
    for(int i=0;i<=20;i++)
    {
        if(t[i]&&q==0) printf(" %d",i);
        if(t[i]&&q==1)//是第一个答案
        {
            printf("%d",i);//不打空格
            q=0;
        }
    }
    printf("\n");
    return 0;
}
```

---

## 作者：EarthGiao (赞：7)

其实这题除了用dfs之外，还要注意一下倒牛奶的时候接收桶和倒桶的容量问题，先在纸上写出来，再写代码，出错率会小很多，还是有点绕的~~

```cpp
#include<cstdio>
#include<cstring>
    int a[4],f[21];
    int m[400][5];
    bool bz[21][21][21];
    int head=0,tail=1;
int main()
{
    scanf("%d %d %d",&a[1],&a[2],&a[3]);
    m[1][1]=a[3];//第三杯水为满 
    memset(bz,true,sizeof(bz));
    memset(f,0,sizeof(f));
    bz[0][0][a[3]]=false;//第三杯水为满的情况已有，赋值为false 
    while(head<tail)
    {
        head++;//头加1,也就是说父亲的改变 
        for(int x=1;x<=3;x++)//x杯 
        {
            for(int y=1;y<=3;y++)//y杯 
            {
                if(x!=y&&m[head][x]>0&&m[head][y]<a[y])//x杯倒入y杯，x必须有水，y必须没装满 
                {
                    tail++;//入队列 
                    for(int i=0;i<=4;i++)
                        m[tail][i]=m[head][i];//对于当前的方案来说，一定来源于他的父亲 
                    if(m[tail][x]<=a[y]-m[tail][y])//y杯中空气部分比x杯中水多，即倒空x杯
                    {
                        m[tail][y]=m[tail][y]+m[tail][x];//y杯的水等于原水+x杯的水 
                        m[tail][x]=0;//倒空x杯 
                    }
                    else//倒满y杯
                    {
                        m[tail][y]=a[y];//y杯满了 
                        m[tail][x]=m[tail][x]-(a[y]-m[head][y]);//x杯的水等于原水-倒走的水（y杯的空气部分） 
                    }
                    if(bz[m[tail][1]] [m[tail][2]] [m[tail][3]])//判断是否重复过 
                    {
                        bz[m[tail][1]] [m[tail][2]] [m[tail][3]]=false;//标记为已有当前方案
                        m[tail][4]++;//倒的次数加1 
                        if(m[tail][1]==0) f[m[tail][3]]++;//第一杯是否为空     
                    }
                    else tail--;//重复过则出队列
                }
            }
        }
    }
    for(int i=0;i<=20;i++)
        if(f[i]>0) printf("%d ",i);
    printf("%d",a[3]);
}
```


---

## 作者：Mr_HaoZzZz (赞：6)

## 本人第一次写题解，写的不好请大佬们提出。
简单搜索，也就是把所有操作都试一遍，再开一个三维数组，用来记录这种操作有没有操作过。
### 附上代码：
```cpp
#include <iostream>

using namespace std ;

int a , b , c ;//三个桶的容量 
int ans[10005] , cc ;
bool n[25][25][25] ;

int debug ;

void find( int x , int y , int z )//三个桶原有多少牛奶 
{
	int p , q , r ;//操作完后，三个桶所含的牛奶 
	
	if ( n[x][y][z] )
	{
		return ;
	}
	n[x][y][z] = true ;
	
	if ( x == 0 )
	{
		ans[cc ++] = z ;
	}
	
/*	cout << x << ' ' << y << ' ' << z << endl ;
	system("pause") ;*/
	
	if ( x >= b-y )//第一个桶倒给第二个桶 
	{
		q = b ;//第二个桶满了 
		p = x - (b-y) ;
		r = z ;
	}
	else//x < b-y
	{
		p = 0 ;
		q = y + x ;
		r = z ;
	}
//	cout << "1 -> 2" << endl ;
//	cout << x << ' ' << y << ' ' << z << " x,y,z" << endl ;
//	cout << p << ' ' << q << ' ' << r << " p,q,r" << endl ;
	find( p , q , r ) ;
	
	if ( x >= c-z )//第一个桶倒给第三个桶 
	{
		r = c ;//第三个桶满了
		p = x - (c-z) ;
		q = y ; 
	}
	else// ... < ...
	{
		p = 0 ;
		r = z + x ;
		q = y ;
	}
//	cout << "1 -> 3" << endl ;
//	cout << x << ' ' << y << ' ' << z << " x,y,z" << endl ;
//	cout << p << ' ' << q << ' ' << r << " p,q,r" << endl ;
	find( p , q , r ) ;
	
	if ( y >= a-x )//第二个桶倒给第一个桶 
	{
		p = a ;//第一个桶满了
		q = y - (a-x) ;
		r = z ; 
	}
	else
	{
		q = 0 ;
		p = x + y ;
		r = z ;
	}
//	cout << "2 -> 1" << endl ;
//	cout << x << ' ' << y << ' ' << z << " x,y,z" << endl ;
//	cout << p << ' ' << q << ' ' << r << " p,q,r" << endl ;
	find( p , q , r ) ;
	
	if ( y >= c-z )
	{
		r = c ;
		q = y - (c-z) ;
		p = x ;
	}
	else
	{
		q = 0 ;
		r = z + y ;
		p = x ;
	}
//	cout << "2 -> 3" << endl ;
//	cout << x << ' ' << y << ' ' << z << " x,y,z" << endl ;
//	cout << p << ' ' << q << ' ' << r << " p,q,r" << endl ;
	find( p , q , r ) ;
	
	if ( z >= a-x )
	{
		p = a ;
		r = z - (a-x) ;
		q = y ;
	}
	else
	{
		r = 0 ;
		p = x + z ;
		q = y ;
	}
//	cout << "3 -> 1" << endl ;
//	cout << x << ' ' << y << ' ' << z << " x,y,z" << endl ;
//	cout << p << ' ' << q << ' ' << r << " p,q,r" << endl ;
	find( p , q , r ) ;
	
	if ( z >= b-y )
	{
		q = b ;
		r = z - (b-y) ;
		p = x ;
	}
	else
	{
		r = 0 ;
		q = y + z ;
		p = x ;
	}
//	cout << "3 -> 2" << endl ;
//	cout << x << ' ' << y << ' ' << z << " x,y,z" << endl ;
//	cout << p << ' ' << q << ' ' << r << " p,q,r" << endl ;
	find( p , q , r ) ;
	
	return ;
}

int main()
{
	cin >> a >> b >> c ;
	
	find( 0 , 0 , c ) ;//直接搜索
	for ( int i = 0 ; i < cc ; i ++ )//一个选择排序，不必多言
	{
		for ( int j = i ; j < cc ; j ++ )
		{
			if ( ans[j] < ans[i] )
			{
				int temp = ans[i] ;
				ans[i] = ans[j] ;
				ans[j] = temp ;
			}
		}
	}
	for ( int i = 0 ; i < cc ; i ++ )
	{
		cout << ans[i] << ' ' ;
	}
	cout << endl ;
	return 0 ;
}
```
管理员大大求过

---

## 作者：1saunoya (赞：5)

> #[$problem$](https://www.luogu.org/problemnew/show/P1215)

>搜索 找出当A桶是空的时候，C桶中牛奶所剩量的所有可能性。
>显然 我们需要一个数组来判重 表示这种状态出现过没有。
>然而 储存答案。 需要一个桶？或者sort咯 不过多个cnt ~~我咧懒得打。~~
>所以我们用一个$vis[N][N][N] ;$ 来判重 表示这种状态出现过没有 出现过就直接返回。
>然后用一个ans数组来储存答案$ans[N] ;$ 都是布尔型的就行。
>然后进入程序片段。
>一共三个字母 则倒法有 $6$种。
>那就手工模拟好了。不用循环了。

~~~
//中心程序 dfs 写的还算比较详细了。
inline void dfs(int x,int y,int z) {
	if(vis[x][y][z]) return ;//判重。
	if(x == 0) ans[z] = true ;//题目要求。
	vis[x][y][z] = true ;
	if(x > 0) {
		if(y+x >= b) dfs(x-(b-y),b,z) ;
		if(y+x  < b) dfs(0,y+x,z) ;
//x->y
		if(z+x >= c) dfs(x-(c-z),y,c) ;
		if(z+x  < c) dfs(0,y,z+x) ;
//x->z
	}
	if(y > 0) {
		if(x+y >= a) dfs(a,y-(a-x),z) ;
		if(x+y  < a) dfs(x+y,0,z) ;
//y->x
		if(z+y >= c) dfs(a,y-(c-z),c) ;
		if(z+y  < c) dfs(x,0,z+y) ;
//y->z
	}
	if(z > 0) {
		if(x+z >= a) dfs(a,y,z-(a-x)) ;
		if(x+z  < a) dfs(x+z,y,0) ;
//z->x
		if(y+z >= b) dfs(x,b,z-(b-y)) ;
		if(y+z  < b) dfs(x,y+z,0) ;
//z->y
	}
}
~~~
> ### 这个程序没有在意时间复杂度。仅仅是观看过程。
那么主程序呢


~~~
#include <bits/stdc++.h>
using namespace std;
typedef long long LL ;
inline LL In() { LL res(0),f(1); register char c = getchar() ; //快读 可省略
	while(!isdigit(c)) { if(c == '-') f = -1 ; c = getchar() ; }
	while(isdigit(c)) res = (res << 1) + (res << 3) + (c & 15) , c = getchar() ; return res * f ;
}
int a , b , c ;
const int N = 20 + 5 ;
bool vis[N][N][N] ;
bool ans[N] ;
inline void dfs(int x,int y,int z) {//dfs
	if(vis[x][y][z]) return ;
	if(x == 0) ans[z] = true ;
	vis[x][y][z] = true ;
	if(x > 0) {
		if(y+x >= b) dfs(x-(b-y),b,z) ;
		if(y+x  < b) dfs(0,y+x,z) ;
		if(z+x >= c) dfs(x-(c-z),y,c) ;
		if(z+x  < c) dfs(0,y,z+x) ;
	}
	if(y > 0) {
		if(x+y >= a) dfs(a,y-(a-x),z) ;
		if(x+y  < a) dfs(x+y,0,z) ;
		if(z+y >= c) dfs(a,y-(c-z),c) ;
		if(z+y  < c) dfs(x,0,z+y) ;
	}
	if(z > 0) {
		if(x+z >= a) dfs(a,y,z-(a-x)) ;
		if(x+z  < a) dfs(x+z,y,0) ;
		if(y+z >= b) dfs(x,b,z-(b-y)) ;
		if(y+z  < b) dfs(x,y+z,0) ;
	}
}
signed main() {
	memset(vis,false,sizeof(vis)) , memset(ans,false,sizeof(ans)) ;//初始化
	a = In() , b = In() , c = In() ;
	dfs(0,0,c) ;//dfs 
	for(register int i=0;i<=c;i++) ans[i] ? printf("%d ",i) : 0 ;
//上面同 if(ans[i]) printf("%d ",i);
	return 0 ;
}
~~~

---

## 作者：info___tion (赞：4)

这道题是一道很经典的宽搜题目。虽然解法的思想并不难，但很考验各位OIer的程序实现能力。



------------
进入正题。

这道题目就是说，有A,B,C三桶牛奶，其中C桶牛奶一开始是满的，让我们我们在各个桶中不断倒牛奶。题目要求我们求出当A桶为空时，C桶中的牛奶量有哪些可能性。

这道题目的正解很容易想到，直接用宽搜搜完所有能扩展到的状态，然后把A桶为空时C桶的所有可能的状态记录下即可。但是，这道题目扩展状态的方式和普通的宽搜题目不一样。三个桶两两配对，总共有六种扩展方法。怎么办呢？~~废话当然是暴力啦！~~ 咳咳，我们要想一些聪明的方法（当然了，暴力也可以做）。我自己用的方法是编码法。

怎么编码呢？很简单。我们可以枚举一个变量i（0<=i<9），然后用i/3来表示“倒出牛奶”的桶的编号，用i%3来表示“倒进牛奶”的桶的编号（比如说，用0表示A桶，1表示B桶，2表示C桶）。然后，当i/3==i%3时continue掉即可（因为这时“倒出”的桶和“倒进”的桶是一样的，没有意义）。这样就可以方便的枚举所有可以扩展的状态了。

最后还有一些细节，比如说我们要用一个三维数组vis\[a]\[b]\[c]记录下“A桶牛奶量为a，B桶牛奶量为b，C桶牛奶量为c”的这个状态是否被搜索过（因为每个状态只需被搜一次即可），如果不这样加记忆化的话，肯定会TLE。

具体的细节参考代码（注释过长可能看不到，大家可以适当缩小页面缩放比例）：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxv=22;

int A,B,C;	//表示A,B,C桶的容量 

bool ans[maxv];	//ans[i]表示当A桶牛奶量为0时C桶中的牛奶量是否可能等于i 

bool vis[maxv][maxv][maxv];	//vis[a][b][c]表示“A桶牛奶量为a，B桶牛奶量为b，C桶牛奶量为c”的状态
							//是否被搜索过（因为重复搜索会死循环）

struct node
{
	int a,b,c;
	
	node(int a=0,int b=0,int c=0):a(a),b(b),c(c){}
}que[100002];

void bfs()
{
	//初始化
	
	int h=0,t=1;
	que[h]=node(0,0,C);
	
	ans[C]=true;
	
	vis[0][0][C]=true;
	
	while(h!=t)
	{
		node& head=que[h];	//利用别名简化代码 
		
		for(int i=0;i<9;i++)	//用i的值编码
		{
			int ta,tb,tc;
			ta=head.a,tb=head.b,tc=head.c;
			
			int S;	//S表示当前要“倒出来”的桶的牛奶量 
			int sn=i/3,tn=i%3;	//sn表示倒出的桶编号，tn表示倒进的桶编号 
			
			if(sn==tn) continue;
			
			if(sn==0)
			{
				S=head.a;
				
				if(tn==1)
				{
					tb=min(S+head.b,B);	//判断倒了牛奶进去的桶是否会溢出，下同
					ta=max(ta-(B-head.b),0);	//判断倒出了牛奶的桶是否会下溢（里面的牛奶量小于0），下同
				}
				if(tn==2)
				{
					tc=min(S+head.c,C);
					ta=max(ta-(C-head.c),0);
				}
			}
			if(sn==1)
			{
				S=head.b;
				
				if(tn==0)
				{
					ta=min(S+head.a,A);
					tb=max(tb-(A-head.a),0);
				}
				if(tn==2)
				{
					tc=min(S+head.c,C);
					tb=max(tb-(C-head.c),0);
				}
			}
			if(sn==2)
			{
				S=head.c;
				
				if(tn==0)
				{
					ta=min(S+head.a,A);
					tc=max(tc-(A-head.a),0);
				}
				if(tn==1)
				{
					tb=min(S+head.b,B);
					tc=max(tc-(B-head.b),0);
				}
			}
			
			if(!S||vis[ta][tb][tc]) continue;	//如果要把牛奶倒出去的桶是空的，
												//或者现在3个桶的状态已被搜索过，则不用入队 
			
			if(!ta) ans[tc]=true;		//如果A桶牛奶量为0，则在ans数组中记录下C桶此时的状态 
			
			vis[ta][tb][tc]=true;	//记下3个桶此时的状态 
			
			//入队
			
			que[t]=node(ta,tb,tc); 
			t++;
			t%=100001;
		}
		
		h++;
		h%=100001;
	}
}

int main()
{
	scanf("%d%d%d",&A,&B,&C);
	
	bfs();
	
	for(int i=0;i<=C;i++)
		if(ans[i]) printf("%d ",i);
	
	return 0;
}
```

---

## 作者：Flokirie (赞：3)

看到楼下还缺少一种算法，果断来补。    
今天我们要讲的是：（敲黑板！划重点！）**随机化**。

------------

首先，随机化可以用在什么样的题里面呢？
1. 没有明显的算法的题目。例如，班主任找到你，让你给这个级部写一个分班程序，你也没有什么好的算法，于是随机生成班级，不断更新最优解，一个小时之后验收就行了。（反正又不是OI，没有什么时限）
2. 计算某某事件的概率，然后你发现这个事件很好模拟，于是模拟它10000000次，利用蒙特卡洛方法及概率的大数原理，以频率代替概率。   
（注1：概率大数原理为：做$N$次试验，事件$A$发生了$M$次，当$N\rightarrow+ \infty$时，$\frac {M} {N} \rightarrow P(A)$）   
（注2：据经验，当做10000000次试验时，所求概率“不确定性”一般会在$(10^{-4},10^{-3})$以内。）
3.  求所有可能情况，然后这个事件很好模拟，于是你模拟了10000000次，并且有理由相信所有的情况都发生过了（运气再不好也有90~95分吧）。例如：本题。
4.  ~~骗分~~

------------

回到本题。
我们将倒奶的操作重复25000000遍（这是不放心的举措，实际上，以运行时间600~700ms为宜）。剩下的，就是pj-的情况判断。
我们对照代码分析一下：
```cpp
#include <bits/stdc++.h>

using namespace std;

//桶被编号为0,1,2
int f[6]={0,0,1,1,2,2};//意为from，从哪个桶倒出奶
int t[6]={1,2,0,2,0,1};//意为to，向哪个桶倒奶
int p[21];//C桶剩余奶量的判断

int main(){
	int a[3];
	scanf("%d %d %d",a,a+1,a+2);//输入ABC桶的容积
	int x[3]={0,0,a[2]};//x数组表示现有牛奶的体积
	srand(123456789+2*a[0]*a[1]*a[2]);//写一个很乱的种子
	for (int i=0;i<25000000;i++){
		int caozuo=rand()%6;//一共有6种倒牛奶的操作
		int dv=a[t[caozuo]]-x[t[caozuo]];//意为△V，转移牛奶的体积
		if (dv>x[f[caozuo]]){//如果一下子倒不满就全倒进去
			x[t[caozuo]]+=x[f[caozuo]];
			x[f[caozuo]]=0;
		}
		else{//否则就倒满
			x[t[caozuo]]+=dv;
			x[f[caozuo]]-=dv;
		}
		if (!x[0]){//如果A是空的
			p[x[2]]=1;//统计C桶现有牛奶体积
		}
	}
	for (int i=0;i<=a[2];i++){
		if (p[i]) printf("%d ",i);
	}
	return 0;
}
```
当采用随机化以后，算法难度瞬间降到普及-，代码量也小（33行），各位OIer不妨一试。以上就是我对随机化的一家之言。

---

## 作者：早右昕 (赞：3)

看到没有人写BFS的，果断来一发

思路：A[0~2]为容量，然后枚举状态即可！见丑陋代码：

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool vis[21][21][21];
struct in{int a[3];} now,nxt;
queue<in>que;
int ans[100000],cnt;
bool vis_ans[21];
int main() {
    int A[3];
    scanf("%d%d%d",&A[0],&A[1],&A[2]);
    now.a[0]=now.a[1]=0,now.a[2]=A[2];
    que.push(now);
    vis[A[0]][A[1]][A[2]]=1;
    while(!que.empty()) {//BFS 核心内容 
        now=que.front();
        que.pop();
        if(!now.a[0]) if(!vis_ans[now.a[2]]) //存答案 
            ans[cnt++]=now.a[2],vis_ans[now.a[2]]=1;
        nxt=now;
        for(int i=0;i<3;i++) {//枚举 i->j 
            if(now.a[i]) for(int j=0;j<3;j++) {
                if(i==j) continue;
                if(now.a[j]>=A[j]) continue;
                int need=A[j]-now.a[j];
                if(need>=now.a[i]) {
                    nxt.a[j]+=now.a[i];
                    nxt.a[i]-=now.a[i];
                } else {
                    nxt.a[j]+=need;
                    nxt.a[i]-=need;
                }
                if(!vis[nxt.a[0]][nxt.a[1]][nxt.a[2]]) {
                    vis[nxt.a[0]][nxt.a[1]][nxt.a[2]]=1;
                    que.push(nxt);
                }
                nxt=now;
            }
        }
    }
    sort(ans,ans+cnt);//排序 
    for(int i=0;i<cnt;i++) printf("%d ",ans[i]);
    return 0;
} 
```

---

## 作者：Tofu (赞：3)

其他大佬都是六个方向的dfs，而且并没有回溯，在我看来应该像递归

我的方法是回溯 只要找到可以倒的两桶奶就进行深搜

以下是代码及注释：

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

var a,b:array[1..3]of integer;//a数组用来存当前三个桶中牛奶的数量，b数组存放三个桶的容积

i,j,m,n:longint;h:array[0..20,0..20,0..20]of boolean;//h数组判断三个桶当前状态是否搜过

```cpp
    s:array[0..20]of longint;//存答案
procedure search(l,r:longint);
  var i,j,w,e,k,o:longint;p:boolean;
    begin
      p:=true;
      w:=l;
      e:=r;
      if a[1]=0 then begin inc(s[a[3]]);end;
      for i:=1 to 3 do
        for j:=1 to 3 do//默认顺序为i桶倒向j桶
          if (i<>j)and((i<>l)or(j<>r)) then //l和r是上一次倒牛奶的两个桶，如果再倒回去会死循环，相当于剪枝
            if ((a[i]>0)and(a[j]<b[j])) then
              begin
                k:=a[i];
                o:=a[j];
                if a[i]>=b[j]-a[j] then begin a[i]:=a[i]-(b[j]-a[j]);a[j]:=b[j];end
                else begin a[j]:=a[j]+a[i];a[i]:=0;end;//倒牛奶
                if h[a[1],a[2],a[3]]=true then
                      begin p:=false;h[a[1],a[2],a[3]]:=false;end;//判断是否搜过
                if p=true then begin a[i]:=k;
                    a[j]:=o; end;
                if p=false then
                  begin
                    l:=j;
                    r:=i;//把当前倒的两桶牛奶存入l和r，注意把倒和被倒互换
                    search(l,r);              
                    l:=w;
                    r:=e;
                    a[i]:=k;
                    a[j]:=o;//回溯
                  end;
              end;
      if p=true then exit;//设置出口
    end;
begin
  for i:=1 to 3 do
    read(b[i]);
  fillchar(h,sizeof(h),true);//初始化数组
  a[1]:=0;a[2]:=0;a[3]:=b[3];
  h[a[1],a[2],a[3]]:=false;
 search(0,0);
  for i:=0 to 20 do
    if s[i]>0 then write(i,' ');//输出答案
end.
```
- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
很弱的做法，也比较好理解

注意c桶可能为0，这个细节卡了我十分钟qwq

也不知道能不能过审核，还有4天noip了，祝大家rp++


---

## 作者：LuxLover (赞：2)

不说了，就是个搜索大暴力

首先，为了避免重复搜索，我们需要一个三维哈希表

还有一个关键问题，那就是中间倒牛奶的过程，为了节省代码，可以把两个桶里的牛奶加起来再做判断，这样就可以啦

贴代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int g[25][25][25];
int xx,yy,zz;
set<int> s;//set用于排序，不懂的话可以搜一下这个容器
int a[30];
void dfs(int x,int y,int z)
{
	g[x][y][z]=1;
	if(x==0) s.insert(z);
   //
	if(x+y>yy&&!g[x+y-yy][yy][z]) dfs(x+y-yy,yy,z); 
	if(x+y<=yy&&!g[0][x+y][z]) dfs(0,x+y,z);
   //
	if(x+z>zz&&!g[z+x-zz][y][zz]) dfs(x+z-zz,y,zz);
	if(x+z<=zz&&!g[0][y][x+z]) dfs(0,y,x+z);
	//
	if(x+y>xx&&!g[xx][x+y-xx][z]) dfs(xx,x+y-xx,z);
	if(x+y<=xx&&!g[x+y][0][z])dfs(x+y,0,z);
   //
	if(z+y>zz&&!g[x][z+y-zz][zz]) dfs(x,z+y-zz,z);
	if(x+y<=zz&&!g[x][0][z+y])dfs(x,0,z+y);
	//
	if(z+x>xx&&!g[xx][y][z+x-xx]) dfs(xx,y,x+z-xx);
	if(z+x<=xx&&!g[x+z][y][0]) dfs(x+z,y,0);
   //
	if(z+y>yy&&!g[x][yy][z+y-yy]) dfs(x,yy,z+y-yy);
	if(z+y<=yy&&!g[x][z+y][0]) dfs(x,z+y,0); 
}
int main()
{
	cin>>xx>>yy>>zz;
	dfs(0,0,zz);
	set<int>::iterator it;
	int i=0;
	for(it=s.begin();it!=s.end();it++)
	{
		a[++i]=*it;//装进数组输出
	}
	for(int p=1;p<=i;p++) 
	{
		if(p>1) cout<<' ';
		cout<<a[p];
	}
	return 0;
}

```
###### 完美收官

---

## 作者：「QQ红包」 (赞：2)

题解by：redbag

题解原址：http://redbag.duapp.com/?p=1088

倒牛奶一共有6种可能性，一种一种搜，然后可以做一些简单的优化，见代码

/\*
ID: ylx14271

PROG: milk3

LANG: C++

\*/
```cpp
#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<time.h>
#include<math.h>
#include<memory>
#include<vector>
#include<bitset>
#include<fstream>
#include<stdio.h>
#include<utility>
#include<sstream>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#define LL unsigned long long
using namespace std;
int a[4];//存现有牛奶 
int b[4];//存容积 
int i,j,s,ff;
int c[21][21]={0};//判重，由a和c的牛奶量就可以推出b的牛奶量\
```
所以只需判断a和c
```cpp
int t[30];//c牛奶剩余可能，1：可能出现 
void dfs(int aa,int cc)
{
    int bb=b[3]-aa-cc;
    //cout<<"——"<<aa<<"  "<<bb<<" "<<cc<<"——"<<endl;
    if (c[aa][cc]==1) return;//判重
    c[aa][cc]=1;//标记
    //下面一点小小的优化：如过a/b/c桶是空的，则不需向别的桶子倒牛奶\
```
如果接收牛奶的一方没有容积了，也不需要给它倒牛奶\
因为倒了跟没到是一个效果

    
    
```cpp
    if ((bb<=b[2])&&(aa!=0))
    {   
        dfs(aa-min(aa/*a的牛奶量*/,b[2]-bb/*b的剩余容积*/),cc);//a→b
    }
    if ((cc<=b[3])&&(aa!=0))
    {
        dfs(aa-min(aa/*a的牛奶量*/,b[3]-cc/*c的剩余容积*/),cc+min(aa,b[3]-cc));//a→c
    }
    if ((aa<=b[1])&&(bb!=0))
    {
        dfs(aa+min(bb/*b的牛奶量*/,b[1]-aa/*a的剩余容积*/),cc);//b→a
    }
    if ((cc<=b[3])&&(bb!=0))
    {
        dfs(aa,cc+min(bb,b[3]-cc));//b→c
    }
    if ((aa<=b[1])&&(cc!=0))
    {
        dfs(aa+min(cc,b[1]-aa),cc-min(cc,b[1]-aa));//c→a
    }
    if ((bb<=b[2])&&(cc!=0))
        dfs(aa,cc-min(cc,b[2]-bb));//c→b
}
int main() 
{
    freopen("milk3.in","r",stdin);
    freopen("milk3.out","w",stdout); 
    scanf("%d%d%d",&b[1],&b[2],&b[3]);//读入容积 
    a[3]=b[3];//c桶此时牛奶是满的，牛奶量即容积 
    dfs(0,a[3]);//深搜 
    for (i=0;i<=b[3];i++)//c的牛奶量不可能大于它的容积 
        if ((c[0][i]==1)&&(ff==1)) printf(" %d",i);
        else if (c[0][i]==1)
        {
            printf("%d",i);
            ff=1;
        }
    printf("\n");
    return 0;
}

```

---

## 作者：Xxzxx (赞：1)

这题虽然是$yellow$题，而且看起来很复杂。其实~~膜你~~模拟就好了。。。

```
#include <iostream>
using namespace std;
int a,b,c,flag[100],ans[25][25][25];
void dfs(int A,int B,int C)
{
    if(ans[A][B][C]==1)return;//我第一次提交就因为没加这东西爆零了，M了所有点啊。。。
    else ans[A][B][C]=1;
    if(A==0&&flag[C]==0){
        flag[C]=1;
    }
    if(A<a&&C>0)dfs(min(a,A+C),B,max(0,C-a+A));//C倒给A
    if(B<b&&C>0)dfs(A,min(b,B+C),max(0,C-b+B));//C倒给B
    if(A<a&&B>0)dfs(min(a,A+B),max(0,B-a+A),C);//B倒给A
    if(C<c&&B>0)dfs(A,max(0,B-c+C),min(c,C+B));//B倒给C
    if(B<b&&A>0)dfs(max(0,A+B-b),min(b,B+A),C);//A倒给B
    if(C<c&&A>0)dfs(max(0,A+C-c),B,min(c,C+A));//A倒给C
}
int main()
{
    cin>>a>>b>>c;
    dfs(0,0,c);//因为题目说了，只有C桶开始时是满的，所以递归是这个东西开始的。。。
    for(int i=0;i<=c;i++)
        if(flag[i]==1)cout<<i<<" ";
    return 0;
}

```

---

## 作者：Salamander (赞：1)

```cpp
//直接暴力搜索6种可能的倒法
#include<cstdio>
#include<algorithm>
using namespace std;
bool b[101][101][101];//b[A][B][C]记录这种情况是否出现过
bool f[101];//记录c桶中的某个牛奶的量是否出现过
int ans[501],t=0;//记录结果和结果数量
int aa,bb,cc;
void search(int,int,int);
int main()
{
        scanf("%d%d%d",&aa,&bb,&cc);
        search(0,0,cc);
        sort(ans+1,ans+t+1);//别忘了排序输出
        for(int i=1;i<=t;i++)
            printf("%d ",ans[i]);
        printf("\n");
        return 0;
}
void search(int A,int B,int C)//dfs，ABC分别是三桶中牛奶的量
{
        if(b[A][B][C])return;//情况重复
        b[A][B][C]=1;
        if(A==0&&!f[C])//如果满足解的条件就记录
        {
                f[C]=1;
                t++;
                        ans[t]=C;
        }
        if(A>0&&B<bb)//如果A不为空并且B还没有满，则A可以往B倒
        {
                        int p=A>(bb-B)?bb-B:A;//求出可以倒多少
                        search(A-p,B+p,C);
        }
        if(A>0&&C<cc)//如果A不为空并且C还没有满，则A可以往C倒
        {
                        int p=A>(cc-C)?cc-C:A;//求出可以倒多少
                        search(A-p,B,C+p);
        }
        if(B>0&&A<aa)//如果B不为空并且A还没有满，则B可以往A倒
        {
                        int p=B>(aa-A)?aa-A:B;//求出可以倒多少
                        search(A+p,B-p,C);
        }
        if(B>0&&C<cc)//如果B不为空并且C还没有满，则B可以往C倒
        {
                        int p=B>(cc-C)?cc-C:B;//求出可以倒多少
                        search(A,B-p,C+p);
        }
        if(C>0&&A<aa)//如果C不为空并且A还没有满，则C可以往A倒
        {
                int p=C>(aa-A)?aa-A:C;//求出可以倒多少
                        search(A+p,B,C-p);
        }
        if(C>0&&B<bb)//如果C不为空并且B还没有满，则C可以往B倒
        {
                        int p=C>(bb-B)?bb-B:C;//求出可以倒多少
                        search(A,B+p,C-p);
        }
}
```

---

## 作者：Thaumaturge (赞：0)

有技巧的枚举是啥？？？不是很懂～代码如下：（第一次数组开小了，还坑了我一个测试点）

```cpp
#include <bits/stdc++.h>

using namespace std;

int w[22][22][22],a,b,c,i,k[22];

int powe(int x,int y,int z){
	w[x][y][z]=1;
	if(x==0)
	k[z]=1;
	if(x!=0)
	{
		if(x>=b-y)
		if(w[x-b+y][b][z]!=1)
		powe(x-b+y,b,z);

		if(x<b-y)
		if(w[0][x+y][z]!=1)
		powe(0,x+y,z);

		if(x>=c-z)
		if(w[x-c+z][y][c]!=1)
		powe(x-c+z,y,c);

		if(x<c-z)
		if(w[0][y][x+z]!=1)
		powe(0,y,x+z);
	}

	if(y!=0)
	{
		if(y>=a-x)
		if(w[a][y-a+x][z]!=1)
		powe(a,y-a+x,z);

		if(y<a-x)
		if(w[x+y][0][z]!=1)
		powe(x+y,0,z);

		if(y>=c-z)
		if(w[x][y-c+z][c]!=1)
		powe(x,y-c+z,c);

		if(y<c-z)
		if(w[x][0][y+z]!=1)
		powe(x,0,y+z);
	}
	
	if(z!=0)
	{
		if(z>=a-x)
		if(w[a][y][z-a+x]!=1)
		powe(a,y,z-a+x);

		if(z<a-x)
		if(w[x+z][y][0]!=1)
		powe(x+z,y,0);

		if(z>=b-y)
		if(w[x][b][z-b+y]!=1)
		powe(x,b,z-b+y);

		if(z<b-y)
		if(w[x][y+z][0]!=1)
		powe(x,y+z,0);
	}
}

int main(){
	cin>>a>>b>>c;
	powe(0,0,c);
	for(i=0;i<=20;i++)
	if(k[i]==1) cout<<i<<" ";
	return 0;
}
```

如果这还不暴力，还有谁更暴力？？qwq，作死倒牛奶，不断模拟就行了

---

## 作者：TangLongbin (赞：0)

DFS枚举+记忆化减枝？？？	
直接枚举所有情况，然后一个rec数组记忆化；	
枚举的时候判断一下倒空或者倒满就行（即solve中的min所示）；	
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int A, B, C;
bool rec[25][25][25];
int ans[1005];

void solve(int a,int b,int c) {
	if (rec[a][b][c])return;
	rec[a][b][c] = 1;
	if (a == 0) {
		ans[++ans[0]] = c;
	}
	int k = 0;
	if (a) {
		k = min(B - b, a);
		solve(a - k, b + k, c);
		k = min(C - c, a);
		solve(a - k, b, c + k);
	}
	if (b) {
		k = min(A - a, b);
		solve(a + k, b - k, c);
		k = min(C - c, b);
		solve(a, b - k, c + k);
	}
	if (c) {
		k = min(A - a, c);
		solve(a + k, b, c - k);
		k = min(B - b, c);
		solve(a, b + k, c - k);
	}
	return;
}

void print() {
	sort(ans + 1, ans + 1 + ans[0]);
	for (register int i = 1; i <= ans[0]; i++)cout << ans[i] << " ";
	return;
}

int main() {
	cin >> A >> B >> C;
	solve(0,0,C);
	print();
	return 0;
}
```

---

## 作者：Celebrate (赞：0)

这一题采用宽搜来做，其实不是很难

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int k[4];//每个容器的容量 
int len=0,a[21];//当A桶是空的时候，C桶中牛奶所剩量
int head,tail;//宽搜时的头和尾 
bool f[21][21][21],bk[21];//f[x][y][z]表示这三个数是否出现过，bk表示 当A桶是空的时候，C桶中牛奶所剩量是否出现过 
struct node//宽搜的队列 
{
	int b[4];
}list[21000];
inline int cmp(const void *xx,const void *yy)//快排 
{
	int x=*(int*)xx;
	int y=*(int*)yy;
	if(x>y) return 1;
	if(x<y) return -1;
	return 0;
}
inline void pour(int x,int y)//将x到入y 
{
	if(list[head].b[y]==k[y]) return;//如果y是满的，就不需要了 
	int t=k[y]-list[head].b[y];//y的剩余空间 
	if(t>list[head].b[x]) t=list[head].b[x];//如果x中的奶不足，就变成x的奶量 
	int g[4];//四个桶 
	for(int i=1;i<=3;i++) g[i]=list[head].b[i];//赋值 
	g[x]-=t;g[y]+=t;//倒奶 
	if(f[g[1]][g[2]][g[3]]==true)//如果没有找过的话 
	{
		f[g[1]][g[2]][g[3]]=false;//变为找过 
		if(g[1]==0 && bk[g[3]]==true){bk[g[3]]=false;a[++len]=g[3];}//记录 
		tail++;for(int i=1;i<=3;i++) list[tail].b[i]=g[i];//往下宽搜 
	}
}
int main()
{
	int i,j;
	for(i=1;i<=3;i++) scanf("%d",&k[i]);//输入 
	memset(f,true,sizeof(f));
	memset(bk,true,sizeof(bk));bk[k[3]]=false;//有点儿麻烦的初始化 
	len=1;a[1]=k[3];f[0][0][k[3]]=false;
	head=tail=1;list[head].b[3]=k[3];
	list[head].b[1]=list[head].b[2]=0;
	while(head<=tail)
	{
		for(i=1;i<=3;i++) //枚举x 
			for(j=1;j<=3;j++) //枚举y 
				if(i!=j)
					pour(i,j);//倒奶 
		head++;
	}
	qsort(a+1,len,sizeof(int),cmp);//排序 
	for(i=1;i<len;i++) printf("%d ",a[i]);//输出 
	printf("%d\n",a[len]);
}
```

---

## 作者：ztz11 (赞：0)

# 典型爆搜
### 只需要判断此时能往哪个桶里倒即可
### ps.记得写判断，让一种状态只能出现一次，否则会死循环
## **详见代码**
```
#include<iostream>
#include<cstdio>
using namespace std;
int jg[25],cnt,a,b,c,xa,xb,xc,bnt,bj[25][25][25][4][4];//bj是用于判断去重的，5维分别表示1桶奶量，2桶奶量，3桶奶量，from，to
void dfs(int ya,int yb,int yc,int from,int to)
{
	if(bj[ya][yb][yc][from][to]==1)//判断，重复则跳出
	{
		return;
	}
	else
	{
		bj[ya][yb][yc][from][to]=1;//否则打标记
	}
	if(ya==0)
	{
		jg[yc]=1;//出现正解打标记
	}
	if(ya!=0)//开始六向搜，这桶能不能倒，倒给谁，（不可能倒回来时的桶）
	{
		if(from!=2||from==2&&to!=1)
		{
			if(ya<=xb-yb)
			{
				dfs(0,yb+ya,yc,1,2);
			}
			else
			{
				dfs(ya-xb+yb,xb,yc,1,2);
			}
		}
		if(from!=3||from==3&&to!=1)
		{
			if(ya<=xc-yc)
			{
				dfs(0,yb,yc+ya,1,3);
			}
			else
			{
				dfs(ya-xc+yc,yb,xc,1,3);
			}
		}
	}
	if(yb!=0)
	{
		if(from!=1||from==1&&to!=2)
		{
			if(yb<=xa-ya)
			{
				dfs(ya+yb,0,yc,2,1);
			}
			else
			{
				dfs(xa,yb-xa+ya,yc,2,1);
			}
		}
		if(from!=3||from==3&&to!=2)
		{
			if(yb<=xc-yc)
			{
				dfs(ya,0,yc+yb,2,3);
			}
			else
			{
				dfs(ya,yb-xc+yc,xc,2,3);
			}
		}
	}
	if(yc!=0)
	{
		if(from!=1||from==1&&to!=3)
		{
			if(yc<=xa-ya)
			{
				dfs(ya+yc,yb,0,3,1);
			}
			else
			{
				dfs(xa,yb,yc-xa+ya,3,1);
			}
		}
		if(from!=2||from==2&&to!=3)
		{
			if(yc<=xb-yb)
			{
				dfs(ya,yb+yc,0,3,2);
			}
			else
			{
				dfs(ya,xb,yc-xb+yb,3,2);
			}
		}
	}
}
int main()
{
	cin>>xa>>xb>>xc;
//	bj[0][0][xc][1][]=1;
//	bj[0][0][xc][2]=1;
//	bj[0][0][xc][3]=1;
	dfs(0,0,xc,0,0);
	for(a=0;a<=20;a++)//愉快的输出
	{
		if(jg[a]==1)
		{
			cout<<a<<" ";
		}
	}
}
```

---

## 作者：封禁用户 (赞：0)

DFS 因为牛奶的总量是不变的，所以可以用a,b中的牛奶量做状态，初始状态是(0,0)，

每次只能有6种选择，a倒b，a倒c，b倒a，b倒c，c倒a，c倒b。

用一个数组vis[i][j]判重，

s[i]记录c中所有可能值（s[i]=true表示c中可能出现i），

如果当前状态是(0,x)，那么s[mc -x]=true，

最后输出s中所有true的就可以了。

用vis[i][j][k]也行 也就是说三维的也行

```cpp
//文件输入输出，防止抄袭！ 
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<fstream>
//#define fin cin
//#define fout cout
using namespace std;
int a[4]= {0};    //三个桶的容量
int fg[22][22]= {0};    //记录该方案是否用过，fg[i][j]指a桶中i个牛奶，b桶中j个牛奶的方案用过了
int note[22]= {0};    //记录c的可能性,若note[i]==1,则c桶中可能有i个牛奶
void search(int x,int y,int z) {    //搜索，x，y，z为三个桶中的牛奶量
//    getchar();
    if(fg[x][y]==1) {
        return ;
    }
    fg[x][y]=1;
    cout<<x<<' '<<y<<' '<<z<<endl;
    if(x==0) {
        note[z]=1;
    }
    int i,j;
    int ji[4]= {0};    //暂时存储x,y,z,方便调用
    ji[1]=x;
    ji[2]=y;
    ji[3]=z;
    for(i=1; i<=3; i++) {    //从i向j倒牛奶
        for(j=1; j<=3; j++) {
            if(i!=j) {
                if(ji[i]!=0&&ji[j]!=a[j]) {    //i桶中有牛奶，j桶没有满
                    if(ji[i]>a[j]-ji[j]) {
                        int t1=ji[i],t2=ji[j];
                        ji[i]-=a[j]-ji[j];
                        ji[j]=a[j];
                        search(ji[1],ji[2],ji[3]);
                        ji[i]=t1;
                        ji[j]=t2;
                    }
                    if(ji[i]<=a[j]-ji[j]) {
                        int t1=ji[i],t2=ji[j];
                        ji[j]+=ji[i];
                        ji[i]=0;
                        search(ji[1],ji[2],ji[3]);
                        ji[i]=t1;
                        ji[j]=t2;
                    }
                }
            }
        }
    }
    return ;
}
int main() {
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");
    int i,j;
    fin>>a[1]>>a[2]>>a[3];
    search(0,0,a[3]);
    for(i=0; i<=a[3]-1; i++) {
        if(note[i]==1) {
            fout<<i<<' ';
        }
    }
    fout<<a[3]<<endl;
    return 0;
}
```

---

## 作者：Sino_E (赞：0)

暴力DFS枚举，就是打了一种情况，然后复制改改改。主要是写代码时看得眼花.-.

三个大分支，决定哪个桶出。

两个小分支，决定哪个桶入。

再来两个小判断，看看是装满还是倒空。

共十二个判断。

大概没有比这更暴力的判断了....

当然判重还是要判的。这里直接来了20进制数来判重了（其实似乎没必要）

复制改代码的时候手一抖就会错，而且很难找到错误，请谨慎操作。

代码如下：

```cpp
/*
ID: a1162731
LANG: C++
TASK: milk3
*/

#include<bits/stdc++.h>
using namespace std;

bool Hash[(int)1e4];
bool ins(int a,int b,int c){
    int v=a+b*20+c*20*20;
    if(Hash[v])return 0;
    else return Hash[v]=1;
}//判重 

int ma,mb,mc;
bool ans[40];
void dfs(int A,int B,int C){
    if(!A)ans[C]=1;//答案的标记 
    int na=A,nb=B,nc=C;//新的桶容量情况 
    if(C){
        if(C>=ma-A){
            na=ma,nc=C-ma+A,nb=B;//A装满，C减少不倒空，B不变 
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若C能把A装满 
        else{
            na=A+C,nc=0,nb=B;//A增加不装满，C倒空，B不变 
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若不能 
        /*下面以此类推*/ 
        if(C>=mb-B){
            nb=mb,nc=C-mb+B,na=A;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若C能把B装满 
        else{
            nb=B+C,nc=0,na=A;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若不能 
    }
    if(B){
        if(B>=ma-A){
            na=ma,nb=B-ma+A,nc=C;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若B能把A装满 
        else{
            na=A+B,nc=C,nb=0;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若不能 
        if(B>=mc-C){
            nc=mc,nb=B-mc+C,na=A;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若B能把C装满 
        else{
            nc=C+B,na=A,nb=0;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若不能 
    }
    if(A){
        if(A>=mb-B){
            nb=mb,na=A-mb+B,nc=C;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若A能把B装满 
        else{
            nb=B+A,nc=C,na=0;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若不能 
        if(A>=mc-C){
            nc=mc,na=A-mc+C,nb=B;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若A能把C装满 
        else{
            nc=C+A,nb=B,na=0;
            if(ins(na,nc,nb))dfs(na,nb,nc);
        }//若不能 
    }
}

int main(){
    #ifndef LOCAL
    freopen("milk3.in","r",stdin);
    freopen("milk3.out","w",stdout);
    #endif
    cin>>ma>>mb>>mc;
    dfs(0,0,mc);
    bool first=0;
    for(int i=0;i<=mc;i++){
        if(ans[i]){
            if(first)putchar(' ');
            else first=1;
            printf("%d",i);
        }
    }
    putchar('\n');
    return 0;
}
```

---

## 作者：Zcus (赞：0)

```cpp
  #include<cstdio>
#include<algorithm>
using namespace std;
int s[50][50][50];//记录A,b,c,桶的情况是否出现过。
int p[100];//存储c桶的情况
int sb[100];//判断c桶的情况有没有出现过
int i,j,k,l,aa,bb,cc,a,b,c,t;
void dfs(int a,int b,int c)//搜索
{
    if(s[a][b][c]==1) return;//判重
      s[a][b][c]=1;
    if(a==0&&sb[c]==0)//存储c桶的情况
    {
        sb[c]==1;
        t++;//t表示共有多少种
        p[t]=c;
    }
    if(a>0&&b<bb)//如果b桶未满并且a桶未空，可以倒一次。
    {
        int gg;//gg表示可以倒多少
        if(bb-b>=a) gg=a;
          else gg=bb-b;
        dfs(a-gg,b+gg,c);
    }
    if(a>0&&c<cc)
    {
        int gg;
        if(cc-c>=a) gg=a;
          else gg=cc-c;
          dfs(a-gg,b,c+gg);
    }
    if(b>0&&a<aa)//如果a桶未满并且b桶未空，可以倒一次。
    {
        int gg;
        if(aa-a>=b) gg=b;
          else gg=aa-a;
          dfs(a+gg,b-gg,c);
    }
    if(b>0&&c<cc)
    {
        int gg;
        if(cc-c>=b) gg=b;
          else gg=cc-c;
          dfs(a,b-gg,c+gg);
    }
    if(c>0&&a<aa)//如果a桶未满并且c桶未空，可以倒一次。
    {
        int gg;
        if(aa-a>=c) gg=c;
          else gg=aa-a;
          dfs(a+gg,b,c-gg);
    }
    if(c>0&&b<bb)
    {
        int gg;
        if(bb-b>=c) gg=c;
          else gg=bb-b;
          dfs(a,b+gg,c-gg);
    }
}
int main()
{
    scanf("%d %d %d",&aa,&bb,&cc);//输入
    dfs(0,0,cc);//开始搜索
    sort(p+1,p+1+t);//排序
    for(i=1;i<=t;i++)
      printf("%d ",p[i]);//输出
      return 0;
}
```

---

## 作者：hutao (赞：0)

/\*
其实方法很简单,就是枚举每一种情况,然后不断搜索

\*/
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a,b,c;//三个牛奶桶
bool vis[25][25],s[25];
void dfs(int aa,int cc)
{
    if(vis[aa][cc]==1)//因为判断完了,所以可以直接返回
        return ;
    vis[aa][cc]=1;//设置为1,表示已经走过
    if(aa==0)//如果a已经为空
        s[cc]=1;//找到一种方法
    int bb=c-aa-cc;//因为牛奶数是不变的,所以已知两个桶,就可以求另外一个桶
    if(aa!=0&&bb!=b)
        dfs(aa-min(aa,b-bb),cc);//将a桶牛奶倒入b桶牛奶
    if(aa!=0&&cc!=c)
        dfs(aa-min(aa,c-cc),cc+min(aa,c-cc));//将a桶牛奶倒入c桶牛奶
    if(bb!=0&&aa!=a)
        dfs(aa+min(bb,a-aa),cc);//将b桶牛奶倒入a桶牛奶
    if(bb!=0&&cc!=c)
        dfs(aa,cc+min(bb,c-cc));//将b桶牛奶倒入c桶牛奶
    if(cc!=0&&aa!=a)
        dfs(aa+min(cc,a-aa),cc-min(cc,a-aa));//将c桶牛奶倒入a桶牛奶
    if(cc!=0&&bb!=b)
        dfs(aa,cc-min(cc,b-bb));//将c桶牛奶倒入b桶牛奶
    return ;//返回
}
inline int read()//读入优化模版
```
/\*
读入优化模板简介:

第一步:利用getchar()字符读入

第二步:判断符号问题

第三步:将字符连串,举个例子,也就是从字符,'1','2','3','4',变成1234

\*/
```cpp
{
    int p,data=0;
    char ch=0;
    while ((ch!='-') && ch<'0' || ch>'9') 
            ch=getchar();
    if (ch=='-')
    {
        p=-1;
        ch=getchar();
    } else p=1;
    while (ch>='0' && ch<='9') 
            data=data*10+ch-'0',ch=getchar();
    return data*p;
}
inline void write(int x)//输出优化模版
```
/\*
输出优化模板简介

第一步:判断符号问题,如果为负数,打印符号,然后将其取反

第二步:不断的递归除以10操作

\*/
```cpp
{
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
int main()
{
    scanf("%d%d%d",&a,&b,&c);//读入
    dfs(0,c);//从a为0,c满桶开始搜索
    for(int i=0; i<=c; i++)
        if(s[i]==1)//如果存在着一种方法
            printf("%d ",i);
    return 0;
}
```

---

## 作者：ergeda (赞：0)

```cpp
//估计再没有比这更暴力的写法了~~~
//就是搜！！！！！！！！！！！
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int a[19];
bool p[111][111][111];
bool vis[100010];//用来判断C中剩余的量有没有出现过
int t[100010];
int cnt;
void dfs(int u,int v,int w){//u代表A中剩余,v代表B中剩余,w代表C中剩余
    if(w){//当C中有剩余
        for(int i=1;i<=2;i++){//考虑给另外两个桶分奶
            if(i==1){
                if(u==a[1])continue;
                if(a[1]-u>w){//奶不够倒满的情况
                    if(!p[u+w][v][0]){//这个三维数组记录状态，代表当A剩余u+w,B剩余v,C剩余0时有没有出现过
                        if(!vis[0]&&u+w==0){
                            t[++cnt]=0;
                            vis[0]=1;
                        }
                        p[u+w][v][0]=1;
                        dfs(u+w,v,0);
                    }
                }
                else{//奶够到满
                    if(!p[a[1]][v][w-a[1]+u]){
                        if(!vis[w-a[1]+u]&&a[1]==0){
                            vis[w-a[1]+u]=1;
                            t[++cnt]=w-a[1]+u;
                        }
                        p[a[1]][v][w-a[1]+u]=1;
                        dfs(a[1],v,w-a[1]+u);
                    }
                }
            }
            else{
                if(v==a[2])continue;
                if(a[2]-v>w){
                    if(!p[u][v+w][0]){
                        if(!vis[0]&&u==0){
                            t[++cnt]=0;
                            vis[0]=1;
                        }
                        p[u][v+w][0]=1;
                        dfs(u,v+w,0);
                    }
                }
                else{
                    if(!p[u][a[2]][w-a[2]+v]){
                        if(!vis[w-a[2]+v]&&u==0){
                            t[++cnt]=w-a[2]+v;
                            vis[w-a[2]+v]=1;
                        }
                        p[u][a[2]][w-a[2]+v]=1;
                        dfs(u,a[2],w-a[2]+v);
                    }
                }
            }
        }
    }
    if(v){//同上
        for(int i=1;i<=3;i++){
            if(i==2)continue;
            if(i==1){
                if(u==a[1])continue;
                if(a[1]-u>v){
                    if(!p[u+v][0][w]){
                        if(!vis[w]&&u+v==0){
                            t[++cnt]=w;
                            vis[w]=1;
                        }
                        p[u+v][0][w]=1;
                        dfs(u+v,0,w);
                    }
                }
                else{
                    if(!p[a[1]][v-a[1]+u][w]){
                        if(!vis[w]&&a[1]==0){
                            vis[w]=1;
                            t[++cnt]=w;
                        }
                        p[a[1]][v-a[1]+u][w]=1;
                        dfs(a[1],v-a[1]+u,w);
                    }
                }
            }
            else{
                if(a[3]==w)continue;
                if(a[3]-w>v){
                    if(!p[u][0][w+v]){
                        if(!vis[w+v]&&u==0){
                            t[++cnt]=a[3];
                            vis[w+v]=1;
                        }
                        p[u][0][w+v]=1;
                        dfs(u,0,w+v);
                    }
                }
                else{
                    if(!p[u][v-a[3]+w][a[3]]){
                        if(!vis[a[3]]&&u==0){
                            t[++cnt]=a[3];
                            vis[a[3]]=1;
                        }
                        p[u][v-a[3]+w][a[3]]=1;
                        dfs(u,v-a[3]+w,a[3]);
                    }
                }
            }
        }
    }
    if(u){
        for(int i=2;i<=3;i++){
            if(i==2){
                if(v==a[2])continue;
                if(a[2]-v>u){
                    if(!p[0][v+u][w]){
                        if(!vis[w]){
                            t[++cnt]=w;
                            vis[w]=1;
                        }
                        p[0][v+u][w]=1;
                        dfs(0,v+u,w);
                    }
                }
                else{
                    if(!p[u-a[2]+v][a[2]][w]){
                        if(!vis[w]&&u-a[2]+v==0){
                            vis[w]=1;
                            t[++cnt]=w;
                        }
                        p[u-a[2]+v][a[2]][w]=1;
                        dfs(u-a[2]+v,a[2],w);
                    }
                }
            }
            else{
                if(a[3]==w)continue;
                if(a[3]-w>u){
                    if(!p[0][v][w+u]){
                        if(!vis[w+u]){
                            t[++cnt]=w+u;
                            vis[w+u]=1;
                        }
                        p[0][v][w+u]=1;
                        dfs(0,v,w+u);
                    }
                }
                else{
                    if(!p[u-a[3]+w][v][a[3]]){
                        if(!vis[a[3]]&&u-a[3]+w==0){
                            t[++cnt]=a[3];
                            vis[a[3]]=1;
                        }
                        p[u-a[3]+w][v][a[3]]=1;
                        dfs(u-a[3]+w,v,a[3]);
                    }
                }
            }
        }
    }
}
int main(){
    int i,j,k,m,n;
    scanf("%d%d%d",&a[1],&a[2],&a[3]);
    p[0][0][a[3]]=1;
    t[++cnt]=a[3];
    dfs(0,0,a[3]);
    sort(t+1,t+cnt+1);
    for(i=1;i<cnt;i++){
        printf("%d ",t[i]);
    }
    printf("%d\n",t[cnt]);
    return 0;
}
```

---

## 作者：一碗粥 (赞：0)

发题解啦！

首先，一道中等的搜索的题目（弱渣)，题目大意就是让你枚举所有当A=0是c的情况。

我用的是很脑残的搜索，luogu神机竟然0秒飘过？？！！

总的来说就是6种可能性：

A-B
A-C
B-A
B-C
C-A
C-B
这么一想是不是就简单多了

放一个boolean数组F看一下F[a,b,c]是否出现过就ok啦

枚举每个情况，只要加一个很小的细节：A-B的时候判断一下A还有多少，B变成多少就好了，然后不断dgdgdgdg。。。

标程来也：

```cpp
01.var a,b,c,i,j,k,l,m,n:longint;   
02.    f:array[0..20,0..20]of boolean;   
03.    flag:boolean;   
04.function min(x,y:longint):longint;   
05.begin if x>y then exit(y) else exit(x); end;   //这里就是我上面说的小细节啦，不用的话有点麻烦就是6种情况都要写一遍。
06.procedure dg(ma,mc:longint);   
07.var mb:longint;   
08.begin  
09.    if f[ma,mc] then exit;   //重复就exit
10.    f[ma,mc]:=true;   
11.    mb:=c-mc-ma;   //mb就这么简单地解决啦
12.    dg(ma-min(ma,b-mb),mc);   
13.    dg(ma-min(ma,c-mc),mc+min(ma,c-mc));   
14.    dg(ma,mc+min(mb,c-mc));   
15.    dg(ma+min(mb,a-ma),mc);   
16.    dg(ma+min(mc,a-ma),mc-min(mc,a-ma));   
17.    dg(ma,mc-min(mc,b-mb));   //各种搜索
18.end;   
19.begin  
20.  read(a,b,c);   
21.  fillchar(f,sizeof(f),false);   
22.  dg(0,c);   //就两个变量哦，三个也是可以的，不过题目只看A和C，两个足矣！
23.  for i:=0 to c do  //这里再说明一下，最多情况就是c个全部都有哦，所以循环到c就够了（为什么）
24.  if f[0,i] then write(i,' ');   
25.end.  
感谢观摩！
```

---

