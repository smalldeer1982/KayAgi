# Coloring

## 题目描述

$\text{Snakes}$正在玩游戏，他在一张画有$n*m$个格子的白纸上给方格染色。然而，杂乱无章的染色并不有趣，所以他想出了一个奇怪的问题：


在$n*m$的方格中用$c$种不同的颜色尝试将所有方格染色，不同的颜色用$1..c$间的整数表示。染色需要满足以下条件：


+ 每个方格只能且必须染一种颜色。

+ 第$i$种颜色最多可以且必须染$p_i$个格子，保证满足$\sum_{i=1}^cp_i=n*m$。

+ 将每个格子上下左右与其颜色相同的格子视为位于同一个联通块内，并定义不同联通块之间的方格边的条数为$q$。可参考样例说明。


现在，$\text{Snakes}$想知道，如果给出$n,m,c$以及$p_1..p_c$，你能够构造出的符合条件且$q$尽量小的染色方案。


## 说明/提示

```plain
   |   |   
 2 | 3 | 1 
   +   +---
 2 | 3   3 
   |       
```

对于样例，有$q=4$，其中三条竖边，一条横边。


#### 约定


本题为 Special Judge。


对于每个测试点，将会设置阈值$w$，并保证存在构造使得$q\leq w$。


对于程序输出的答案，我们将会以以下方式计算得分：


$$\begin{matrix}q&score&q&score\\\\ q \leq w&10&1.75w < q \leq 2w&5\\\\ w < q \leq 1.1w&9&2w < q \leq 2.3w&4\\\\ 1.1w < q \leq 1.25w&8&2.3w < q \leq 2.6w&3\\\\ 1.25w < q \leq 1.5w&7&2.6w < q \leq 3w&2\\\\ 1.5w < q \leq 1.75w&6&3w < q \leq 3.5w&1\end{matrix}$$


若$q > 3.5w$，将以 `Wrong Answer` 处理。


比赛时显示的得分即为最后得分。


#### 数据规模


对于$10\%$的数据，有$1\leq n,m\leq 3$，$c\leq 3$。


对于$30\%$的数据，有$1\leq n,m\leq 8$，$c\leq 6$。


对于$50\%$的数据，有$1\leq n,m\leq 15$，$c\leq 25$。


对于$100\%$的数据，有$1\leq n,m\leq 20$，$c\leq 50$，$p_i\leq 20$。


## 样例 #1

### 输入

```
2 3 3
1 2 3```

### 输出

```
2 3 1
2 3 3```

# 题解

## 作者：3493441984zz (赞：26)

# 纯粹模拟退火！！
****
感谢：[我的好盆友：超級·考場WA怪](https://www.luogu.org/space/show?uid=73574)帮我纠正了某些错误
****
题外话:

这道题其实比较好做的，~~但是我用小号交了90遍才过~~

不信可以去看，小号：[模拟退火](https://www.luogu.org/space/show?uid=147609)
****
[P3936题面](https://www.luogu.org/problemnew/show/P3936)

开始~~乱搞~~讲思路：

1.按照题目要求先建一个有顺序的图，求出q

那样例打比方：

输入：

2 3 3

1 2 2

我们可以按照顺序建图~~当然你也可以随机建图~~

按顺序建图后为：

| 1 | 2 | 2 |
| :----------: | :----------: | :----------: |
| 3 | 3 | 3 |

代码：

~~~cpp
void getmap()
{
    int x=1,y=1;
    for(int i=1;i<=c;i++)
    {
        while(color[i]--)
        {
            g[x][y]=i;
            nowg[x][y]=i;	
            if(y==m)
            {
                x++;
                y=1;
            }
            else
                y++;
        }
    }
}
~~~

2.就可以开始~~随意乱搞~~玄学模拟退火了

如果对模拟退火不理解的话~~不理解你也不会来这里吧~~，我推荐去看看[2018年洛谷日报索引](https://www.luogu.org/discuss/show/48491)
里面的模拟退火算法

如果没$AC$的话，就试试换换参数吧，我就是这样试过来的$qwq$

下面贴没有剪枝但是开$O3$才$AC$了的代码

~~~cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#pragma GCC optimize(3)
using namespace std;
int g[25][25],color[55],nowg[25][25];
int n,m,c,ansq,older;
int getq()
{
    int sum=0;
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
        {
            if(nowg[i][j]!=nowg[i][j+1])
                sum++;
            if(nowg[i][j]!=nowg[i+1][j])
                sum++;
        }
    for(int i=1;i<m;i++)
        if(nowg[n][i]!=nowg[n][i+1])
            sum++;
    for(int i=1;i<n;i++)
        if(nowg[i][m]!=nowg[i+1][m])
            sum++;
    return sum;
}
void getmap()
{
    int x=1,y=1;
    for(int i=1;i<=c;i++)
    {
        while(color[i]--)
        {
            g[x][y]=i;
            nowg[x][y]=i;	
            if(y==m)
            {
                x++;
                y=1;
            }
            else
                y++;
        }
    }
}
void cpy()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
        //	printf("%d ",nowg[i][j]);
            g[i][j]=nowg[i][j];
        }
        //printf("\n");
    }
}
void cpy1()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
        //	printf("%d ",nowg[i][j]);
            nowg[i][j]=g[i][j];
        }
        //printf("\n");
    }
}
void monituihuo()
{
    double T=1,deita=0.99999,T_min=1e-5;
    older=ansq;
    while(T>T_min)
    {
        int x1=(rand()%(n))+1;
        int y1=(rand()%(m))+1;
        int x2=(rand()%(n))+1;
        int y2=(rand()%(m))+1;
        int huan=nowg[x1][y1];
        nowg[x1][y1]=nowg[x2][y2];
        nowg[x2][y2]=huan;
        int ans_now=getq();
        double de=ans_now-older;
        if((de<0)||(exp(-de/T)*RAND_MAX>((rand()%1000000)/1000000.0)))
            older=ans_now;
        else
            cpy1();
        if(older<=ansq)
        {
        	ansq=older;
        	cpy();
        }
        T*=deita;
    }	
}
int main()
{
    srand(107.77777777);
    srand(rand());
    scanf("%d%d%d",&n,&m,&c);
    for(int i=1;i<=c;i++)
        scanf("%d",&color[i]);
    getmap();
    ansq=getq();
    older=ansq;
/*	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            printf("%d ",nowg[i][j]);
        printf("\n");
    }*/
    for(int i=1;i<=3;i++)
        monituihuo();
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            printf("%d ",g[i][j]);
        cout<<endl;
    }
    //cout<<ansq<<endl;
    return 0;
}
~~~

如果觉得有用的话，让我看到你们的赞$qwq$

---

## 作者：ddwqwq (赞：20)

今天研究模拟退火算法，搜到了这题。不得不说，模拟退火的确是一个十分精妙的算法。下面言归正传，讨论一下本题的解法。各种骗分策略楼上已经讲得很清楚了，不再多说，主要讲解模拟退火算法。


一.关于模拟退火算法


模拟退火算法（Simulate Anneal，SA）是一种通用概率演算法，用来在一个大的搜寻空间内找寻命题的最优解。模拟退火是由S.Kirkpatrick, C.D.Gelatt和M.P.Vecchi在1983年所发明的。V.Čern&yacute;在1985年也独立发明此演算法。模拟退火算法是解决TSP问题的有效方法之一。（来自百度百科）


[这里](https://mp.weixin.qq.com/s?\_\_biz=MjM5MDE3OTk2Ng==&mid=2657432747&idx=1&sn=55d2b2594a3ec0ed92538f47847746c0&chksm=bdd923ba8aaeaaac6022bef8216b60256d0c236d402434732b78b70e47ba93900582883f4a0b&mpshare=1&scene=24&srcid=0123348572YE57z0s058aGgc&pass\_ticket=LHNTbEViOtTrgaa6knsa6HqqoYVzurL1A2ZuQRgI7Olxb6BBlmVIuheVtruXLyb6#rd)有一篇不错的讲解此算法的文章，其中还有本人看不懂的证明。


二.本题的具体实现


首先按顺序填充颜色，得到初始解，之后按一定规则随机交换两个色块,并在每次执行交换流程后降低温度，直到温度低于设定的温度下界。以上过程总共进行m次，以确保总能得到足够优秀的解（理论上来说，如果初始温度T极高，退火速度a极慢，温度下界T\_end足够接近0，则必定能一次得到最优解，但计算量无法承受）。


交换规则：


随机获得两个下标并交换其颜色，原解q值记作q,所得新解q值记作q'。令t=q'-q，若t<0,则接受新解，否则以exp(-t/T)的概率随机接受新解，其中T代表当前温度。可见，exp(-t/T)随着T值降低而降低，所得解也将趋于稳定。其中exp（i）代表e的i次方。


注意事项：


1.下标一定要随机获取，不要自作聪明，否则会陷入次优解无法自拔。


2.具体参数通过实验确定。我将T设为1，a设为0.99999，T\_end设为1e-15，m设为3，执行一遍耗时约2.8秒，一般来说可以对付本题的输入规模。


3.计算q值只需遍历矩阵一遍，记录每个方格的临边，最后除二即可得到答案。注意，每次交换无需再次遍历，计算交换的两下标的临边即可。否则会浪费时间，导致精确度下降，那样的话就只能碰运气了。


4.为了方便做实验、节约时间和挽救AC率，可以使用time.h中的clock()函数来记录时间，很方便。


另外，生成新解的其它方法也可尝试，比如翻转区间之类，也可多种方法组合，或许能提速不少，就是不知效果如何，有赖于读者自行验证了。


大概就是这些了，最后提供代码，不保证一次AC。重要处做了注释。

```cpp
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <cstring>
#include <time.h>

#define INF 2000000000//2 * 10^9
inline int max(int a, int b)
{
    return a>b ? a : b;
}
inline int min(int a, int b)
{
    return a<b ? a : b;
}

int n, m;
int c, p[55];

struct map {
private:
    int a[25][25];
    int q;    
public:
    map()
    {
        q = -1;
    }
    int c(int i, int j)
    {
        return a[i][j];
    }
    void swap(int i, int j, int x, int y)
    {
        if (i > n || x > n || j > m || y > m)
            return;
        if (i < 1 || j < 1 || x < 1 || y < 1)
            return;
       //↓之所以起这个名字，是因为original是“原始”的意思
        int o_q = 0, q2 = 0;
        if (a[i][j] != a[i + 1][j])
            o_q++;
        if (a[i][j] != a[i - 1][j])
            o_q++;
        if (a[i][j] != a[i][j + 1])
            o_q++;
        if (a[i][j] != a[i][j - 1])
            o_q++;
        if (a[x][y] != a[x + 1][y])
            o_q++;
        if (a[x][y] != a[x - 1][y])
            o_q++;
        if (a[x][y] != a[x][y + 1])
            o_q++;
        if (a[x][y] != a[x][y - 1])
            o_q++;

        int t = a[i][j];
        a[i][j] = a[x][y];
        a[x][y] = t;

        if (a[i][j] != a[i + 1][j])
            q2++;
        if (a[i][j] != a[i - 1][j])
            q2++;
        if (a[i][j] != a[i][j + 1])
            q2++;
        if (a[i][j] != a[i][j - 1])
            q2++;
        if (a[x][y] != a[x + 1][y])
            q2++;
        if (a[x][y] != a[x - 1][y])
            q2++;
        if (a[x][y] != a[x][y + 1])
            q2++;
        if (a[x][y] != a[x][y - 1])
            q2++;

        q = q + q2 - o_q;
    }
    int getq()
    {
        if (q > -1)
            return q;

        int cnt = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                if (i > 1 && a[i - 1][j] != a[i][j])
                    cnt++;
                if (i < n && a[i + 1][j] != a[i][j])
                    cnt++;
                if (j > 1 && a[i][j - 1] != a[i][j])
                    cnt++;
                if (j < m && a[i][j + 1] != a[i][j])
                    cnt++;
            }
        return cnt / 2;
    }
    void put()
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
    }
    void setmap()
    {
        int cnt = 0;
        int col = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                if (cnt < p[col])
                    a[i][j] = col;
                else
                {
                    cnt = 0;
                    col++;
                    a[i][j] = col;
                }
                cnt++;
            }
        q = getq();
    }
};

map ans;
int ans_q;
double T;
const double a = 0.99999;
const double end = 1e-15;

void renew(map &M,int &M_q)//更新解
{
    map t = M;
    int q;
    int x = abs(rand()) % n + 1, y = abs(rand()) % m + 1;
    int x1 = abs(rand()) % n + 1, y1 = abs(rand()) % m + 1;

    t.swap(x, y, x1, y1);
    q = t.getq();
    if (q <= M_q)
    {
        M = t;
        M_q = q;
    }
    else if (exp((M_q - q) / T) > fabs((double)(rand() % 1000) / 1000))
    {
        M = t;
        M_q = q;
    }
    if (M_q < ans_q)
    {
        ans = M;//记录，防止最优解遗失
        ans_q = M_q;
    }
}

void search()//模拟退火
{
    map tans = ans;
    int q = ans_q;
    T = 1;//初始温度

    while (T > end)
    {
        renew(tans, q);//更新解
        T *= a;//退火
    }
}

int main()
{
    srand(time(NULL));

    scanf("%d %d %d", &n, &m, &c);
    for (int i = 1; i <= c; i++)
        scanf("%d", &p[i]);
    long long start = clock();

    ans.setmap();
    ans_q = ans.getq();

    for (int i = 0; i < 3; i++)
        search();//模拟退火三次
    ans.put();//输出

    printf("%d\n", ans_q);//这几行都是要去掉的
    printf("%lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    system("pause");
    return 0;
}
```

---

## 作者：年华天地 (赞：11)

## 我：看客老爷们点个赞再走吧。
## 老爷：下次一定

## 什么是模拟退火
我看不懂的简绍(⚆_⚆)
  
模拟退火算法（Simulate Anneal，SA）是一种通用概率演算法，用来在一个大的搜寻空间内找寻命题的最优解。模拟退火是由S.Kirkpatrick, C.D.Gelatt和M.P.Vecchi在1983年所发明的。V.Černý在1985年也独立发明此演算法。模拟退火算法是解决TSP问题的有效方法之一。
模拟退火的出发点是基于物理中固体物质的退火过程与一般组合优化问题之间的相似性。模拟退火算法是一种通用的优化算法，其物理退火过程由加温过程、等温过程、冷却过程这三部分组成。

——百度百科

其实就是蒟蒻骗分必备算法

## 模拟退火主要思想
个人做的退火题不多，但就做的几道题而言，退火一般是先随机生成一个序列，用这个序列算出一个答案，在交换序列里的两个数，得到一个新解，若新解更优，直接更新ans，否者以一定概率接受，多试几次后输出答案。
## 	模拟退火前置
 模拟退火需要用到几个常量，T_begin,T_end,V,分别对应退火初温，末温和退火速度（其实就是决定SA函数**运行次数**的，能不能过题大部分就靠这个了）。
   C++自带的**CLOCKS_PER_SEC，clock()经常被用来卡常**，CLOCKS_PER_SEC指一秒,clock（）指当前时间。
    常在代码最上方写double be=clock();
    运行SA时while(clock()-be<0.9*CLOCKS_PER_SEC)SA();
## 模拟退火大致模板
	```
```
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
...
const double be=clock()//卡时,记录当前时间
const double T_begin=..;//退火初温
const double T_end=..;//末温
const double V=..;//速率
void fz()
{
	... //若题目有关序列操作模拟退火常需要随机生成一个序列(random_shuffle)
}
void js()//模拟退火最耗时的函数，写的好题就A了
{
	...//有一个解，需算出答案，后与已知最优解比较
}
void SA()//模拟退火主要函数
{
 	fz()
  	...//改变当前解，得到一个新答案,常用rand()；
  	int de=tmp-ans;//tmp：当前接，ans：已知最优解
  	if (de>0)//当前解更优
	else if (exp(de/T)>(double)rand()/RAND_MAX)以一定概率接受劣解
	else // 讨论情况
}
int mian()
{
  	srand((int)time(0))；//玄学随机种子
	...
  	while(clock()-be<0.9*CLOCKS_PER_SEC)SA();
   ...//输出答案
	return 0;
}                                             
```
这里解释一下srand((int)time(0))
因为C++函数中的rand()函数是伪随机的，是关于随机种子的一个函数，srand（）就是输入随机种子，time(0)是当前时间（我习惯用为随机种子），~~当然你可以恶臭的用八位质数~~
## 如何生成新解（即得到一个新的答案）
####  --引用M_sea大佬的话
坐标系内：随机生成一个点，或者生成一个向量。

序列问题： random\_shufflerandom_shuffle 或者随机交换两个数。

网格问题：可以看做二维序列，每次交换两个格子即可。

## 例题
### P3936 Coloring
纪念自己写的第一道[黑题](https://www.luogu.com.cn/problem/P3936)

## 关于本题
知道了模拟退火这道题就好做了
首先可以随机染色，记录答案，随后在不断的更新答案就行了，计算答案暴力就行了。
话不多说，看码
```
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
const double T0=1e5;
const double T_end=1e-3;
const double V=0.998;
int n,m,k,a[100],map[25][25],an[25][25],ans=1e9;
int dx[2]={1,0},dy[2]={0,1};
int dx1[4]={1,-1,0,0},dy1[4]={0,0,1,-1};
double be=clock();
void fz()
{
	int xx=1,yy=0;
	for (int i=1;i<=k;++i)
	{
		for (int j=1;j<=a[i];++j)
		{
			yy++;
			if (yy>m)
			{
				yy=1;
				xx++;
			}
			map[xx][yy]=i;
		}
	}
	
}
int js()
{
	int cnt=0;
	for (int i=1;i<=n;++i)
	{
		for (int j=1;j<=m;++j)
		{
			for (int k=0;k<=1;++k)
			{
				int ddx=i+dx[k];
				int ddy=j+dy[k];
				if (ddx>n||ddy>m)continue;
				if (map[ddx][ddy]!=map[i][j])cnt++;
			}
		}
	}
	return cnt;
}
void swap(int a,int b,int c,int d)
{
	int tmp=map[a][b];
	map[a][b]=map[c][d];
	map[c][d]=tmp;
}
int calc(int x,int y){
    int S=0;
    S+=(map[x][y]!=map[x-1][y])+(map[x][y]!=map[x+1][y])+(map[x][y]!=map[x][y-1])+(map[x][y]!=map[x][y+1]);
    return S;
}
void SA()
{
	fz();
	double T=T0;
	int res=js();
	while (T>T_end)
	{
		for (int i=1;i<=100;i++)
		{
			int x1=(rand()%n)+1;
			int y1=(rand()%m)+1;
			int x2=(rand()%n)+1;
			int y2=(rand()%m)+1;
			if (map[x1][y1]==map[x2][y2])continue;
			int tmp=res-calc(x1,y1)-calc(x2,y2);
			swap(x1,y1,x2,y2);
			tmp+=calc(x1,y1)+calc(x2,y2);
			int de=res-tmp;
			if (de>0)
			{
				res=tmp;
				if (res<ans)
				{
					for (int i=1;i<=n;++i)
					{
						for (int j=1;j<=m;++j)
							an[i][j]=map[i][j];
					}
					ans=res;
				}
			}
			else if (exp(de/T)>(double)rand()/RAND_MAX)
				res=tmp;
			else
				swap(x1,y1,x2,y2);
		}
		T*=V;
	}
		
}
int main()
{
	srand(9);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=k;i++)
		scanf("%d",&a[i]);
	fz();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
				an[i][j]=map[i][j];
	ans=js();
	while(clock()-be<0.9*CLOCKS_PER_SEC)SA();
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			printf("%d ",an[i][j]);
		printf("\n");
	}
	return 0;
}
```
我也就交了几页（= =）
## 最后
最后祝大家~~骗分愉快~~Oier的事怎么能叫骗分呢？
祝大家Coding愉快




	


 

---

## 作者：lukelin (赞：11)

考虑搜索，发现复杂度爆炸  
-------贪心，正确性过低(~~实测爆炸~~)

于是，~~发现~~这题是模拟退火

这里不讲解退火的定义了，初学退火可以去平衡点

退火本身维护一个答案图像，答案的q，当前图像，当前的q  
暴力根据计算图像计算q即可

关于这题我们发现如果任由其随机，可能会导致偏差太大  
但如果过多修正偏差，可能导致其跃出局部最优解的能力降低  
于是我加了这么一句话

```cpp
if (curq - ansq >= (temp * 90)){
	for (ri i = 1; i <= n; ++i)
		for (ri j = 1; j <= m; ++j)
			cur_map[i][j] = ans_map[i][j];
	curq = ansq;
}
```
即根据当前温度及时修正偏差，温度越高，偏差容忍度越高


最后放个代码(不保证一直AC)

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define ll long long
#define ri register int

const double DEL = 0.00001;
const double DELTA = 0.99999;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int n, m, c;
int ansq;
int ans_map[25][25];
int curq;
int cur_map[25][25];
int p[25];

inline void swp(int x1, int y1, int x2, int y2){
    int t = cur_map[x1][y1];
    cur_map[x1][y1] = cur_map[x2][y2];
    cur_map[x2][y2] = t;
}

inline int getQ(int x1, int y1, int x2, int y2){
    int res = 0;
    swp(x1, y1, x2, y2);
    for (ri i = 1; i <= n; ++i)
        for (ri j = 1; j <= m; ++j){
            if (i < n)
                if (cur_map[i][j] != cur_map[i+1][j])
                    ++res;
            if (j < m)
                if (cur_map[i][j] != cur_map[i][j+1])
                    ++res;
        }
    swp(x1, y1, x2, y2);
    return res;
}

void SA(){
    register double temp = 10000.0;
    int x1, y1, x2, y2;
    int excq;
    while (temp >= DEL){
        x1 = (rand() % n) + 1, y1 = (rand() % m) + 1, x2 = (rand() % n) + 1, y2 = (rand() % m) + 1;
        srand(rand());
        excq = getQ(x1, y1, x2, y2);
        if (excq < ansq){
            curq = ansq = excq;
            swp(x1, y1, x2, y2);
            for (ri i = 1; i <= n; ++i)
                for (ri j = 1; j <= m; ++j)
                    ans_map[i][j] = cur_map[i][j];
        }
        else if (exp(-(excq - ansq) / temp) * RAND_MAX > ((rand() % 1000000) / 1000000.0)){
            curq = excq;
            swp(x1, y1, x2, y2);
        }
        else{
        	if (curq - ansq >= (temp * 90)){
            	for (ri i = 1; i <= n; ++i)
                    for (ri j = 1; j <= m; ++j)
                        cur_map[i][j] = ans_map[i][j];
                curq = ansq;
            }
        }
        temp *= DELTA;
    }
}

int main(){
    srand(19260817);
    srand(rand()); srand(rand()); srand(rand());
    n = read(), m = read(), c = read();
    for (ri i = 1; i <= c; ++i)
        p[i] = read();
    int k1 = 1, k2 = 1;
    for (ri i = 1; i <= n; ++i)
        for (ri j = 1; j <= m; ++j){
            ans_map[i][j] = cur_map[i][j] = k1;
            ++k2;
            if (k2 > p[k1]){
                ++k1;
                k2 = 1;
            }
        }
    ansq = 0;
    for (ri i = 1; i <= n; ++i)	
        for (ri j = 1; j <= m; ++j){
            if (i < n)
                if (cur_map[i][j] != cur_map[i+1][j])
                    ++ansq;
            if (j < m)
                if (cur_map[i][j] != cur_map[i][j+1])
                    ++ansq;
        }
    //for (int k = 1; k <= 3; ++k)
    SA();//, curq = ansq;
    for (ri i = 1; i <= n; ++i)
        for (ri j = 1; j <= m; ++j){
            printf("%d", ans_map[i][j]);
            if (j < m)
                printf(" ");
            else
                printf("\n");
        }
        
    //调试 
    //printf("%d", ansq);
    return 0;
}

```

---

## 作者：Snakes (赞：11)


#### 算法一


我会随机！


没试过，期望得分$40$以下。


#### 算法二


我会骗分！


按从左往右，从上往下的顺序依次填颜色，期望得分$60$。


#### 算法三


我会贪心！


手玩几个例子不难发现把相同颜色的放在一起更优。每次填颜色，贪心找一块在边界且尽可能大的位置，放下该颜色的所有格子。期望得分$70$至$90$。


#### 算法四


我会搜索！


搜索时间复杂度$O(c^{nm})$，超时无疑。


嘿嘿嘿。


#### 算法五


我会物理！


哦豁？搜索其实很靠近正解，但是时间太慢。我们考虑模拟退火。


每次操作交换两个在联通块边界的格子，计算答案是否更优，按概率更新。



#### 算法六


等等……为啥会是$90$？


因为你可能会陷入局部最优解。


多随机几次就好了。


时间复杂度$O($跑得过$)$，期望得分$100$。


---

## 作者：xzyxzy (赞：4)

### 模拟退火

#### 这里有一个搜索专讲的[课件](http://www.cnblogs.com/xzyxzy/p/8546384.html)?(预计2018暑假之前完成吧，大家可以看一看，也许不是以课件的形式呈现)

思路就是rand一个答案，然后退火地交换，直到最优

计算贡献用另外一种方便点的方式：每个点往四周算，那么方格内的贡献被算两次，边界上被算一次，但是不影响

## Code
```cpp
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
using namespace std;
int N,M,C,p[51];
int A[25][25],E[51],out[25][25];
int sum,ans=1000000;
int Get(int x,int y)
{
    int Ans=0;
    if(A[x][y]!=A[x-1][y]) Ans++;
    if(A[x][y]!=A[x+1][y]) Ans++;
    if(A[x][y]!=A[x][y-1]) Ans++;
    if(A[x][y]!=A[x][y+1]) Ans++;
    return Ans;
}
void Update(int k)
{
    if(ans<=k) return;
    ans=k;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            out[i][j]=A[i][j];
}
double Rand(){return 1.0*(rand()%100000000)/100000000;}
int Rand(int x){return rand()%x+1;}
void SA(double T)
{
    while(T>1e-15)
    {
        T*=0.99999;
        int x1=Rand(N),x2=Rand(N);
        int y1=Rand(M),y2=Rand(M);
        int p=sum;
        p-=Get(x1,y1)+Get(x2,y2);
        swap(A[x1][y1],A[x2][y2]);
        p+=Get(x1,y1)+Get(x2,y2);
        if(p<sum||exp((sum-p)/T)>Rand()) {Update(sum=p);continue;}
        swap(A[x1][y1],A[x2][y2]);
    }
}
int main()
{
    srand(19260817233);
    cin>>N>>M>>C;
    for(int i=1;i<=C;i++) cin>>p[i];
    int T=5;
    while(T--)
    {
        for(int i=1;i<=C;i++) E[i]=p[i];
        for(int i=1;i<=N;i++)
            for(int j=1,x=1;j<=M;j++)
            {
                x=rand()%C+1;
                while(!E[x]) x=rand()%C+1;
                A[i][j]=x; E[x]--;
            }
        sum=0;
        for(int i=1;i<=N;i++) 
            for(int j=1;j<=M;j++)
                sum+=Get(i,j);
        Update(sum);SA(100000000);
    }
    for(int i=1;i<=N;i++,puts(""))
        for(int j=1;j<=M;j++)
            printf("%d ",out[i][j]);
    return 0;
}
//之前这里一个错误找了一周：定义了一个B存该点贡献，但是交换的话应该改动10个B
//而我只改了2个，把贡献算成负数，但是somehowAC了

```
## 不保证程序能一遍AC(你也看到了是完全随机的随机种子)


~~另外我很迷的地方是这个now（贡献）算到最后是负数。。~~

~~有没有大佬能教教我QAQ~~

好的找到原因了Upd:7.18

---

## 作者：破忆 (赞：3)

[P3936 Coloring](https://www.luogu.com.cn/problem/P3936)

异于模拟退火的一般随机问题解法。

## 【题意】

将网格图染色，规定每种颜色的格子的数量，求一个方案，让相邻格子不同颜色的边的数量尽量小。

## 【分析】

把相同颜色的摆一起，能得到一个初始的较优解。

然后枚举格子对，若交换颜色能让当前更优就交换。

接着进行微调，随机选择 $20$ 对格子交换颜色，以避免陷入僵局。

卡个时多做几遍就行，不能过的换几个种子就行~~我用npy的生日就过了~~。

我将网格图映射成序列，感觉会好写点。

这个做法比模拟退火暴力多了，省去了调参的时间，且正确性也有一定保证。

## 【算法】

随机化贪心

## 【代码】

```cpp
#include<bits/stdc++.h>
#define DB double
using namespace std;
const int maxn=25,maxt=maxn*maxn,maxc=55;
int n,m,c,t;
int p[maxc];
int mp[maxn][maxn],a[maxt],id[maxt],ma[maxt];
#define id(x,y) ((x-1)*m+y)
#define x(id) ((id+m-1)/m)
#define y(id) ((id+m-1)%m+1)
int ans,now;
int calc(){
	int ret=0;
	for(int i=1;i<t;i++){
		ret+=(x(i)<n&&a[i]!=a[i+m])+(y(i)<m&&a[i]!=a[i+1]);
	}
	return ret;
}
int del(int id){
	return (x(id)<n&&a[id]!=a[id+m])+(y(id)<m&&a[id]!=a[id+1])+(x(id)>1&&a[id]!=a[id-m])+(y(id)>1&&a[id]!=a[id-1]);
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P3936.in","r",stdin);
	freopen("P3936.out","w",stdout);
	#endif
	srand(20050205);
	scanf("%d%d%d",&n,&m,&c);
	t=n*m;
	for(int i=1;i<=c;i++) scanf("%d",&p[i]);
	for(int i=1,j=1,x=p[j];i<=t;i++){
		if(!x) x=p[++j];
		ma[i]=a[i]=j;
		id[i]=i;
		x--;
	}
	ans=calc();
	while((DB)clock()/CLOCKS_PER_SEC<0.95){
		for(int i=1;i<=t;i++) a[i]=ma[i];
		for(int i=1;i<=20;i++) swap(a[rand()%t+1],a[rand()%t+1]);
		now=calc();
		random_shuffle(id+1,id+1+t);
		bool flg=1;
		while(flg){
			flg=0;
			for(int i=1;i<t;i++)
			for(int j=i+1;j<=t;j++){
				int x=id[i],y=id[j];
				int nxt=now-del(x)-del(y);
				swap(a[x],a[y]);
				nxt+=del(x)+del(y);
				if(nxt<ans){
					ans=now=nxt;
					flg=1;
					for(int k=1;k<=t;k++) ma[k]=a[k];
				}else
				if(nxt<now){
					now=nxt;
					flg=1;
				}else swap(a[x],a[y]);
			}
		}
	}
//	printf("%d\n",ans);
	for(int i=1;i<=t;i++){
		printf("%d",ma[i]);
		if(i%m==0){
			if(i^t) putchar(10);
		}
		else putchar(' ');
	}
	return 0;
}
```


---

## 作者：tommymio (赞：3)

这题其实很水，就是普通的求最优解最小，可以直接套用**Metropolis**接受准则。但我们需要注意对当前最优解微调的方式，我们可以通过每次随机交换两个点来进行微调。

另外，我们需要考虑如何快速计数不同联通块之间的方格边的条数，可以很轻易的发现,一个点$(x,y)$对答案的贡献，就是看它的上下左右与它的颜色是否不同，不同即为1。但如果每次对一个点都上下左右算贡献的话，可以发现会被算两遍，所以我们只需要对每个点的左,上统计贡献即可得到**不同联通块之间的方格边的条数**$q$。我们还可以发现，修改点$(x,y)$的颜色，只会对$(x+1,y)$,$(x,y+1)$,$(x,y)$三个点的贡献产生影响，因此我们能够在$O(1)$的时间下得到交换任意两个点的颜色对答案造成的影响。

最重要的，在转移的过程中，接受一个次优解时不能直接替换最优解继续转移，必须每次都记录下最优解，避免代码输出时不是当前最优解的情况。

代码实现细节有点多，详见代码
```cpp
#include<ctime>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define f(i,j) (((a[i][j]!=a[i-1][j])&&(i!=0))+((a[i][j]!=a[i][j-1])&&(j!=0)))
#define fx(i,j) ((a[i][j]!=a[i-1][j])&&(i!=0))
#define fy(i,j) ((a[i][j]!=a[i][j-1])&&(j!=0))
#define double long double
const double d=0.999995;
int n,m,c,res,minn=40000;
int p[55],cnt[55];
int a[25][25],tmp[25][25];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(f=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int calc(int x1,int y1,int x2,int y2) {
	int res=0;
	res-=fx(x1+1,y1)+fy(x1,y1+1)+fx(x2+1,y2)+fy(x2,y2+1)+f(x1,y1)+f(x2,y2);
	std::swap(a[x1][y1],a[x2][y2]);
	res+=fx(x1+1,y1)+fy(x1,y1+1)+fx(x2+1,y2)+fy(x2,y2+1)+f(x1,y1)+f(x2,y2);
	return res; 
}
inline void SA() {
	double t=500;
	while(t>1e-15) {
		int x1=rand()%n,y1=rand()%m,x2=rand()%n,y2=rand()%m,tot=0;
 		int del=calc(x1,y1,x2,y2);
 		//if(del<0||exp(-del*1.00/t)*RAND_MAX>rand()) ans+=del;
 		//else std::swap(a[x1][y1],a[x2][y2]);
 		if(res+del<minn) {
 			for(register int i=0;i<n;++i) {
 				for(register int j=0;j<m;++j) {
 					tmp[i][j]=a[i][j];
 				}
 			}
 			res+=del;minn=res;
 		}
 		else if(exp(-del*1.00/t)*RAND_MAX>rand()) res+=del;
 		else std::swap(a[x1][y1],a[x2][y2]);
 		t*=d;
	} 
}
int main() {
	int x=1;
	srand(20050103);
	n=read(),m=read(),c=read();
	for(register int i=1;i<=c;++i) p[i]=read();
	for(register int i=0;i<n;++i) {
		for(register int j=0;j<m;++j) {
			if(p[x]<=cnt[x]) ++x;
			a[i][j]=x;res+=f(i,j);++cnt[x];
			//printf("%d ",a[i][j]);
		}
		//printf("\n");
	}
	while((double)clock()/CLOCKS_PER_SEC<0.98) SA();
	for(register int i=0;i<n;++i) {
		for(register int j=0;j<m;++j) {
			printf("%d ",tmp[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：little_sun (赞：2)

思路其实很容易想到，只是调参有那么"一点点"恶心

首先按顺序把$1-c$这$c$种数全部填进表格里

然后每次随机选两个颜色不同的块交换，然后计算原方案与现方案的差距，并按几率更新（其实就是模拟退火的套路啦）

代码五分钟，调参两百年:C
 
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
const int MaxN = 30;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int n, m, c;
int p[51];
int a[MaxN][MaxN], tmp[MaxN][MaxN];
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}
inline int calc(int A[30][30])
{
    int ret = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k <= 3; k++)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if (A[nx][ny] && (A[nx][ny] != A[i][j]))
                    ++ret;
            }
        }
    }
    return ret / 2;
}
inline void init()
{
    int now = 1, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            a[i][j] = now;
            ++cnt;
            if (cnt == p[now])
                cnt = 0, now++;
        }
    }
}
inline void sa()
{
    double t = 1.0, delta;
    if (n * m <= 400)
        delta = 0.9999900001;
    memcpy(tmp, a, sizeof(a));
    while (t > 1e-5)
    {
        std::pair<int, int> pos1, pos2;
        pos1.first = rand() % n + 1;
        pos2.first = rand() % n + 1;
        pos1.second = rand() % m + 1;
        pos2.second = rand() % m + 1;
        while (tmp[pos1.first][pos1.second] == tmp[pos2.first][pos2.second])
        {
            pos1.first = rand() % n + 1;
            pos2.first = rand() % n + 1;
            pos1.second = rand() % m + 1;
            pos2.second = rand() % m + 1;
        }
        std::swap(tmp[pos1.first][pos1.second], tmp[pos2.first][pos2.second]);
        int num = calc(tmp) - calc(a);
        if (num < 0)
            std::swap(a[pos1.first][pos1.second], a[pos2.first][pos2.second]);
        else if (exp(-num / t) * RAND_MAX > rand())
            std::swap(a[pos1.first][pos1.second], a[pos2.first][pos2.second]);
        else
            std::swap(tmp[pos1.first][pos1.second], tmp[pos2.first][pos2.second]);
        t *= delta;
    }
}
int main()
{
    srand(107);
    n = read(), m = read(), c = read();
    for (int i = 1; i <= c; i++)
        p[i] = read();
    init();
    for (int i = 1; i <= 2; i++)
        sa();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            printf("%d ", a[i][j]);
        puts("");
    }
    return 0;
}

```



---

## 作者：丛雨 (赞：1)

# 关于退火
#### 模拟退火算法（Simulate Anneal，SA）是一种通用概率演算法，用来在一个大的搜寻空间内找寻命题的最优解。模拟退火是由S.Kirkpatrick, C.D.Gelatt和M.P.Vecchi在1983年所发明的。V.Čern&yacute;在1985年也独立发明此演算法。模拟退火算法是解决TSP问题的有效方法之一。
#### 模拟退火的出发点是基于物理中固体物质的退火过程与一般组合优化问题之间的相似性。模拟退火算法是一种通用的优化算法，其物理退火过程由加温过程、等温过程、冷却过程这三部分组成。

# 进入正题
#### 1.how to get 初始解
### 	C1.随机
    可变性较强，但容易使得结果不以得到最优解。
###    C2.贪心
    把同颜色居于一处，但易陷入局优。
## 此处选择C2

------------
#### 2.how to change
### 	随机交换，没有多了（或许是我tcl）
------------
------------
#### 3.how to choose
### 分类讨论
Ps(to:下个状态 n:当前状态 T(x):此状态的结果 Fi:当前温度)
1. T(to)<T(n)----直接转移
1. T(to)>T(n)----以exp((T(n)-T(to))/Fi)概率接受

------------
#### End.上代码
```cpp
#include<ctime>
#include<cmath>
#include<cstdio> 
#include<cstdlib>
#include<cstring>
#include<algorithm>
using std::swap;
# define read read1<int>()
# define Type template<typename T>
# define Rand ((double)rand()/RAND_MAX)
Type inline const T read1()
{
    T m=0;
    char k=getchar();
    while(('0'>k||k>'9')&&(k!='-'))k=getchar();
    const bool f=(k=='-'?1:0);
    if(f)k=getchar();
    while('0'<=k&&k<='9')m=(m<<3)+(m<<1)+(k^48),k=getchar();
    return f?-m:m;
}
int a[22][22],n,m,c,*w[51][2],p[51],x[4]={1,-1,0,0},y[4]={0,0,1,-1},ta[22][22];
int Get()
{
	int t=0;
	for(int i=0;i++^n;)
		for(int j=0;j++^m;)
			for(int k=0;k^4;++k)
				t+=a[i+x[k]][j+y[k]]&&a[i][j]!=a[i+x[k]][j+y[k]];
	return t;
}
int main()
{
	srand(time(NULL));
	n=read,m=read,c=read;
	if(c==1)
	{
		for(int i=0;i++^n;putchar('\n'))
			for(int j=0;j++^m;printf("1 "));
		return 0;
	}
	int nx=1,ny=1;
	for(int i=0;i++^c;)
	{
		p[i]=read;
		w[i][0]=new int[p[i]],w[i][1]=new int[p[i]];
		for(int j=0;j^p[i];++j)
		{
			if(ny==m+1)++nx,ny=1;
			a[w[i][0][j]=nx][w[i][1][j]=ny]=i;
			ta[nx][ny]=i;
			++ny;
		}
	}
	int ans=Get(),dans,tans=ans;
	for(int T=10;T--;)
	{
		double fi=100000,ne=0.9999;
		while(fi>1e-10)
		{
			int o[2],p1[2];
			o[0]=rand()%c+1;
			o[1]=rand()%p[o[0]];
			do p1[0]=rand()%c+1;while(o[0]==p1[0]);
			p1[1]=rand()%p[p1[0]];
			swap(w[o[0]][0][o[1]],w[p1[0]][0][p1[1]]);
			swap(w[o[0]][1][o[1]],w[p1[0]][1][p1[1]]);
			swap(a[w[o[0]][0][o[1]]][w[o[0]][1][o[1]]],a[w[p1[0]][0][p1[1]]][w[p1[0]][1][p1[1]]]);
			int dans=Get();
			if(dans<ans)
			{
				ans=dans;
				if(tans>dans)
					for(int i=0;i++^n;)
						for(int j=0;j++^m;)
							ta[i][j]=a[i][j];
			}
			else if(Rand<exp((ans-dans)/fi))ans=dans;
				else swap(w[o[0]][0][o[1]],w[p1[0]][0][p1[1]]),
					swap(w[o[0]][1][o[1]],w[p1[0]][1][p1[1]]),
					swap(a[w[o[0]][0][o[1]]][w[o[0]][1][o[1]]],a[w[p1[0]][0][p1[1]]][w[p1[0]][1][p1[1]]]);
			fi*=ne;
		}
	}
		
	for(int i=0;i++^n;putchar('\n'))
		for(int j=0;j++^m;printf("%d ",ta[i][j]));
	return 0;
}

```
#### 当然，我们会发现只能得90~95,因为这样的单次转移用时太长，所以需要优化。
```cpp
int Get()
{
	int t=0;
	for(int i=0;i++^n;)
		for(int j=0;j++^m;)
			t+=Di(i,j);
	return t;
}
```
### 这个函数,有木有发现可以改进，因为只变化了两个位置。

## 改进后：
```cpp
#include<ctime>
#include<cmath>
#include<cstdio> 
#include<cstdlib>
#include<cstring>
#include<algorithm>
using std::swap;
# define read read1<int>()
# define Type template<typename T>
# define Rand ((double)rand()/RAND_MAX)
Type inline const T read1()
{
    T m=0;
    char k=getchar();
    while(('0'>k||k>'9')&&(k!='-'))k=getchar();
    const bool f=(k=='-'?1:0);
    if(f)k=getchar();
    while('0'<=k&&k<='9')m=(m<<3)+(m<<1)+(k^48),k=getchar();
    return f?-m:m;
}
int a[22][22],n,m,c,*w[51][2],p[51],x[4]={1,-1,0,0},y[4]={0,0,1,-1},ta[22][22];
int Di(int i,int j)
{
	int t=0;
	for(int k=0;k^4;++k)
		t+=a[i+x[k]][j+y[k]]&&a[i][j]!=a[i+x[k]][j+y[k]];
	return t;
}
int Get()
{
	int t=0;
	for(int i=0;i++^n;)
		for(int j=0;j++^m;)
			t+=Di(i,j);
	return t;
}
int main()
{
	long long start=clock();
	srand(time(NULL));
	n=read,m=read,c=read;
	if(c==1)
	{
		for(int i=0;i++^n;putchar('\n'))
			for(int j=0;j++^m;printf("1 "));
		return 0;
	}
	int nx=1,ny=1;
	if(n<m)
		for(int i=0;i++^c;)
		{
			p[i]=read;
			w[i][0]=new int[p[i]],w[i][1]=new int[p[i]];
			for(int j=0;j^p[i];++j)
			{
				if(nx==n+1)++ny,nx=1;
				a[w[i][0][j]=nx][w[i][1][j]=ny]=i;
				ta[nx][ny]=i;
				++nx; 
			}
		}
	else
		for(int i=0;i++^c;)
		{
			p[i]=read;
			w[i][0]=new int[p[i]],w[i][1]=new int[p[i]];
			for(int j=0;j^p[i];++j)
			{
				if(ny==m+1)++nx,ny=1;
				a[w[i][0][j]=nx][w[i][1][j]=ny]=i;
				ta[nx][ny]=i;
				++ny;
			}
		}
	int ans=Get(),dans,tans=ans;
	while((double)(clock()-start)/CLOCKS_PER_SEC<4.6)
	{
		double fi=90000,ne=0.99999;
		while(fi>1e-10)
		{
			int o[2],p1[2];
			o[0]=rand()%c+1;
			o[1]=rand()%p[o[0]];
			do p1[0]=rand()%c+1;while(o[0]==p1[0]);
			p1[1]=rand()%p[p1[0]];
			int oi=a[w[o[0]][0][o[1]]][w[o[0]][1][o[1]]],pi=a[w[p1[0]][0][p1[1]]][w[p1[0]][1][p1[1]]];
			dans=ans;
			dans-=Di(w[o[0]][0][o[1]],w[o[0]][1][o[1]])<<1;
			a[w[o[0]][0][o[1]]][w[o[0]][1][o[1]]]=pi;
			dans+=Di(w[o[0]][0][o[1]],w[o[0]][1][o[1]])<<1;
			dans-=Di(w[p1[0]][0][p1[1]],w[p1[0]][1][p1[1]])<<1;
			a[w[p1[0]][0][p1[1]]][w[p1[0]][1][p1[1]]]=oi;
			dans+=Di(w[p1[0]][0][p1[1]],w[p1[0]][1][p1[1]])<<1;
			if(dans<ans)
			{
				ans=dans;
				if(tans>dans)
					for(int i=0;i++^n;)
						for(int j=0;j++^m;)
							ta[i][j]=a[i][j];
			}
			else if(Rand<exp((ans-dans)/fi))ans=dans;
				else swap(w[o[0]][0][o[1]],w[p1[0]][0][p1[1]]),
					swap(w[o[0]][1][o[1]],w[p1[0]][1][p1[1]]),
					swap(a[w[o[0]][0][o[1]]][w[o[0]][1][o[1]]],a[w[p1[0]][0][p1[1]]][w[p1[0]][1][p1[1]]]);
			fi*=ne;
		}
	}
		
	for(int i=0;i++^n;putchar('\n'))
		for(int j=0;j++^m;printf("%d ",ta[i][j]));
	return 0;
}

```


------------
这样，就可以在98分以上了！！


---

## 作者：infinities (赞：0)

大致题意：有 $c$ 种颜色，每种颜色必须染 $p_i$ 个格子，要你找出一种方案，使得不同颜色格子之间的边的数目 $q$ 尽量小。

因为数据范围很小，再加上奇特的计分方式，我们理所当然想到模拟退火。

类似于序列上做模拟退火，每次随机两个点，进行交换，然后根据交换完的答案和交换前的答案进行更新即可。

初始化序列要用到贪心，即从左往右，从上往下将一种颜色染完再进行下一个。这是因为我们知道，要使得 $q$ 尽量小，就要使得每一种颜色尽可能分布在一起，这样我们一开始得到的答案就不会很大。

注：交换颜色更新答案不能将整个白纸的每一块都枚举一遍，复杂度太大，需要 $O(1)$（可以带点大常数）更新答案。这是由于这题很毒，$O(1)$ 更新答案的模拟退火都需要每个点跑到 $3-4s$ 才能保证AC。

因为题目毒瘤，温度变动量 $\Delta$ 要比正常模拟退火题更接近1，建议不大于0.99999，因为如果再接近就容易出精度问题，导致TLE。

第一遍统计答案时不能算上格子和边界的不同，而且因为每个不同边都被算了两遍，所以算完需要除以2。

卡时神器：
```cpp
while(clock() / CLOCKS_PER_SEC < 3)SA();
```

最后如果还是脸黑过不了，可以使用~~某恶臭数字~~一些别的数字做随机数~~获得恶臭加持~~。

code:
```cpp
#include<bits/stdc++.h>
#define rint register int
const int maxn = 5e3;
const int INF = 2e9;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
using namespace std;
int n, m, c, p[maxn], ansnx[maxn][maxn], cnt = 1, cntt;
int ans = 0;
double delta = 0.99999, te = 1e-30; 
void init(){
	cin >> n >> m >> c;
	for(int i = 1; i <= c; i ++){
		p[i] = read();
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(cntt >= p[cnt]){
				cnt++, cntt = 0;
			}
			++cntt;
			ansnx[i][j] = cnt;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(i > 1 && ansnx[i][j] != ansnx[i - 1][j])++ans;
			if(i < n && ansnx[i][j] != ansnx[i + 1][j])++ans;
			if(j > 1 && ansnx[i][j] != ansnx[i][j - 1])++ans;
			if(j < m && ansnx[i][j] != ansnx[i][j + 1])++ans;//不算边界情况 
		}
	}
	ans /= 2;//去掉重复的 
}
void SA(){
	double ts = 114514 * 19;//ts调大点 
	int ans1 = ans;
	while(ts > te){
		int x1 = rand() % n + 1, y1 = rand() % m + 1, x2 = rand() % n + 1, y2 = rand() % m + 1;
		int a = 0, b = 0;
		if(ansnx[x2][y2] != ansnx[x2 - 1][y2])b++;
		if(ansnx[x2][y2] != ansnx[x2 + 1][y2])b++;
		if(ansnx[x2][y2] != ansnx[x2][y2 - 1])b++;
		if(ansnx[x2][y2] != ansnx[x2][y2 + 1])b++;
		if(ansnx[x1][y1] != ansnx[x1 - 1][y1])b++;
		if(ansnx[x1][y1] != ansnx[x1 + 1][y1])b++;
		if(ansnx[x1][y1] != ansnx[x1][y1 - 1])b++;
		if(ansnx[x1][y1] != ansnx[x1][y1 + 1])b++;
		swap(ansnx[x1][y1], ansnx[x2][y2]);
		int ansnow = ans1;
		
		if(ansnx[x2][y2] != ansnx[x2 - 1][y2])a++;
		if(ansnx[x2][y2] != ansnx[x2 + 1][y2])a++;
		if(ansnx[x2][y2] != ansnx[x2][y2 - 1])a++;
		if(ansnx[x2][y2] != ansnx[x2][y2 + 1])a++;
		if(ansnx[x1][y1] != ansnx[x1 - 1][y1])a++;
		if(ansnx[x1][y1] != ansnx[x1 + 1][y1])a++;
		if(ansnx[x1][y1] != ansnx[x1][y1 - 1])a++;
		if(ansnx[x1][y1] != ansnx[x1][y1 + 1])a++;//O(1)更新答案 
		ansnow = ansnow + a - b;
		int del = ansnow - ans1;
		if(del < 0){
	    	ans1 = ansnow;
			if(ans > ansnow){
				ans = ansnow;
			}
	    }
		else if(exp(-del / ts) * RAND_MAX > rand())ans1 = ansnow;
		else swap(ansnx[x1][y1], ansnx[x2][y2]);
	    ts = ts * delta;
    }
}
void solve(){
    srand(19198101);
	init();
	while(clock() / CLOCKS_PER_SEC < 3)SA();//卡时，到3就行，换成4极易TLE 
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cout << ansnx[i][j] << " ";
		}
		cout << "\n";
	}
	return;
}
signed main(){
	solve();
}
```

---

