# [USACO09FEB] The Leprechaun S

## 题目描述

Imagine Bessie's surprise as she spied a leprechaun prancing through the north pasture. Being no one's fool, she charged at the leprechaun at captured him with her prehensile hooves.

'One wish, bovine one. That's all I have for cows,' he said.

'Riches,' Bessie said dreamily. 'The opportunity for riches.'

Leprechauns never grant precisely the easiest form of their captor's wishes. As the smoke cleared from the location of a loud explosion, a shimmering donut spun slowly over the verdant green fields.

'I have made you a torus,' the leprechaun cooed. 'And on that torus is an N x N matrix (1 <= N <= 200) of integers in the range

-1,000,000..1,000,000 that will determine the magnitude of your riches. You must find the sequence of contiguous integers all in one row, one column, or on one diagonal that yields the largest sum from among all the possible sequences on the torus.'

Bessie pondered for a moment and realized that the torus was a device for 'wrapping' the columns, rows, and diagonals of a matrix so that one could choose contiguous elements that 'wrapped around' the side or top edge.

Bessie will share the matrix with you.  Determine the value of the largest possible sum (which requires choosing at least one matrix element).

By way of example, consider the 4 x 4 matrix on the left below that has all the elements from one exemplary 'wrapped' diagonal marked:

![](https://cdn.luogu.com.cn/upload/image_hosting/03z54guy.png)

The marked diagonal of the right-hand matrix includes two nines (the highest available number) and a six for a total of 24. This is the best possible sum for this matrix and includes only three of the four possible elements on its diagonal.

你难以想象贝茜看到一只妖精在牧场出现时是多么的惊讶．她不是傻瓜，立即猛扑过去，用她那灵活的牛蹄抓住了那只妖精．

“你可以许一个愿望，傻大个儿！”妖精说．

“财富，”贝茜用梦游般的声音回答道，  “我要获得财富的机会．”

妖精从来没有碰到过这么简单的愿望．他在地方划出一大块N×N(1≤N≤200)的方格，每个格子上写上\_1,000,000到1,000,000之间的数字．他说：  “在方格上朝一个方向行走，可以是行的方向，列的方向，斜对角的方向，一步只能走一格，所有你踩过的数字的和就是你的财富．”

贝茜请你来帮忙，找到一行、一列或一条对角线上找一段连续的数字，它们的和最大．由于妖精方格的神奇特性，沿着一个方向走，走到了边际，再一步跨过去可以“绕”到方格的对边出现．一行两端的格子是相邻的，一列两端的格子也是相邻的，甚至相邻两行的分别两端的格子也是相邻的（斜对角方向）．

对于下图左边的方格，所有标记过的数字都在一条对角线上．

  
 
对于这个方格，能踩出来的最大的和是24，踩过的数字在右图中标记出来了


## 样例 #1

### 输入

```
4 
8 6 6 1 
-3 4 0 5 
4 2 1 9 
1 -9 9 -2 
```

### 输出

```
24 
```

# 题解

## 作者：0凌0 (赞：3)

~~话说这一题这么水，怎么只有二十几人通过呢~~  
题干字很多，~~够我凑一篇英语作文了~~，内容也十分有（zhi）趣（zhang），其实大意就是**在一个矩阵中，找一个和最大的子串**，不过这个子串可以从一边到达另一边，且可以走对角线。  
思路很简单，就是枚举所有点，然后往右，下，右下，右上暴搜（题目说的很清楚1<=N<=200，不会超时），输出最大值。  
### 接下来就是各位期待的东西了：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[201][201],maxx=-10000000,i,j,k,w,x,y,z;  //maxx要足够小 
int main()
{
	cin>>n;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	cin>>a[i][j];                      //输入，不解释 
	for(i=0;i<n;i++)
	for(j=0;j<n;j++,w=0,x=0,y=0,z=0)   //枚举所有点，注意w,x,y,z要清零 
	for(k=0;k<n;k++)
	{
		w+=a[i][(j+k)%n];              //下 
		x+=a[(i+k)%n][j];              //右 
		y+=a[(i+k)%n][(j+k)%n];        //右下 
		z+=a[(i-k+n)%n][(j+k)%n];      //右上 
		maxx=max(max(max(w,x),max(y,z)),maxx);  //比较大小 
	}
	cout<<maxx;                        //输出 
}
```  
本人蒟蒻，不过代码也算易懂。如果代码有不善之处，或存在废话，~~拒绝~~欢迎各位大犇指正

---

## 作者：苏22 (赞：1)

## 前言
###### 看到了一道很水的题 ，还以为很难呢，结果。。。。。
## 正解
题的意思就是向一个方向走，一直走，然后把走过的路的数加起来，看看哪条路为最大。还有它可能从这个墙穿过去到另外一个墙出来。

直接**暴力**搜索，枚举每一个点右上，右下，下，右走后能得多少分，像我这种蒟蒻，还能用啥方法呢！而且 `n` 的值那么小，不会炸的。

这样就可以了（**记得每次初始化哦**）。	
### AC代码

```cpp
#include<bits/stdc++.h>//i,j,k要从0开始，不要从1开始，不然报错 
using namespace std;
int n,m[200][200],ds,dw,s,d,mx=-1*0x3f3f;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&m[i][j]);
		}
	}
	for(int i=0;i<n;i++)//枚举位置 
	{
		for(int j=0;j<n;j++)//同上 
		{
			for(int k=0;k<n;k++)// 走k步 
			{
				s+=m[i][(j+k)%n];              //向下走，把对应的值累加
				d+=m[(i+k)%n][j];              //向右走，把对应的值累加
				ds+=m[(i+k)%n][(j+k)%n];        //向右下走，把对应的值累加
				dw+=m[(i-k+n)%n][(j+k)%n];      //向右上走，把对应的值累加
				mx=max(max(max(s,d),max(ds,dw)),mx);  //比较大小 不能放外面 
			}
			
			s=0,d=0,ds=0,dw=0; //初始化 
		}
	}
	printf("%d",mx); 
}
```


---

## 作者：两年打铁 (赞：1)

蒟蒻一开始看题看了半天竟然没看懂...
所以先讲讲题意


------------

题意大致是任选一个点，再任选一个方向，然后会一直沿着这个方向走，如果碰到了边界，就可以非常神奇地从另一个边界

# 飞出来

每到一个点就获得这个点上的宝藏，问怎样走获得最多宝藏。


------------

分析完题意，我们就可以得出一个方法，就是    万能的

# $\color{red}\colorbox{black}{爆搜}$

我们枚举每一个点，通过对这个点8个方向的方向搜索，每次计算路径上的宝藏之和，取最大值就可以了。

------------
上代码


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dx[8]={1,1,1,-1,-1,-1,0,0},dy[8]={1,0,-1,1,0,-1,1,-1};
int a[200][200];
int gg;
int ans=-0x3f3f3f3f;
int n;
bool visit[200][200];
void read(int &x)
{
    x=0;
    char ch=getchar();
    int pd=1;
    while(ch<'0'||ch>'9')
    {
    	if(ch=='-')
    	pd=-pd;
        ch=getchar();
    }
    while(ch<='9'&&ch>='0')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    x*=pd;
}
void write(const int &x)
{
    char f[100001];
    int s=0;
    int tmp=x;
    if(tmp<0)
    {
    	tmp=-tmp;
    	putchar('-');
	}
    while(tmp>0)
    {
        f[s++]=tmp%10+'0';
        tmp/=10;
    }
    while(s>0)
    {
        putchar(f[--s]);
    }
}
void dfs(int x,int y,int k)
{
    gg+=a[x][y];
    ans=max(ans,gg);
    int ddx=x+dx[k],ddy=y+dy[k];
    /*
    通过这一段就可以实现从边界飞出来的操作
    */
    if(ddx<=0)ddx=(ddx-1+n)%n+1;
    if(ddx>n)ddx=ddx%n;
    if(ddy<=0)ddy=(ddy-1+n)%n+1;
    if(ddy>n)ddy=ddy%n;
    if(!visit[ddx][ddy])
    {
        visit[ddx][ddy]=1;
        dfs(ddx,ddy,k);
        visit[ddx][ddy]=0;
    }
}
signed main()
{
    read(n);
    for(register int i=1;i<=n;++i)
    {
        for(register int j=1;j<=n;++j)
        {
            read(a[i][j]);
        }
    }
    for(register int i=1;i<=n;++i)
    {
        for(register int j=1;j<=n;++j)
        {
            for(register int k=0;k<8;++k)
            {
                visit[i][j]=1;//每次把起始点标记
                dfs(i,j,k);
                visit[i][j]=0;
                gg=0;
            }
        }
    }
    cout<<ans;
}

```

---

## 作者：luaddict (赞：1)

不要把题目想太复杂，就是把每一串数字取出来，求最大子串和。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,s[201][201],t[201],ans=-8888,v[201];
int dfs()
{
    int i,j,k;
    for(i=1;i<=n;i++)
    {
        k=i%n+1;
        j=t[i];
        ans=max(ans,j);
        while(t[k]+j>0&&k!=i)//从i往后面加，如果总和小于0就退出。
        {
            j+=t[k];
            ans=max(ans,j);
            k=k%n+1;
        }
    }
}
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    scanf("%d",&s[i][j]);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        t[j]=s[i][j];
        dfs();
        for(j=1;j<=n;j++)
        t[j]=s[j][i];
        dfs();
        int a=i-1;
        for(j=1;j<=n;j++)
        {
            a++;
            if(a>n)
            a=1;
            t[j]=s[j][a];
        }
        dfs();
        a=i+1;
        for(j=1;j<=n;j++)
        {
            a--;
            if(a<1)
            a=n;
            t[j]=s[j][a];
        }
        dfs();//这几步是取出数串。
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：lidagua1004 (赞：0)

这道题在蓝题中算是比较水的了。

题意看了半天才看懂，大概是任选一个点，再任选一个方向，然后会一直沿着这个方向走，如果碰到了边界，就可以到另一个边界。

不用多想，直接暴力即可，$O(n^3)$ 都可以过。

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1050][1050],maxn=INT_MIN,b,c,y,z;//maxn记录答案
int main(){
	cin>>n;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>a[i][j];
	for(int i=0;i<n;i++)
	    for(int j=0;j<n;j++){//枚举每一个点
	       b=c=d=e=0;//注意方向要清零
	       for(int k=0;k<n;k++){//暴力枚举四个方向
        		b+=a[i][(j+k)%n];
	          	c+=a[(i+k)%n][j];
	    	    d+=a[(i+k)%n][(j+k)%n];
        		e+=a[(i-k+n)%n][(j+k)%n];
         		maxn=max(max(max(b,c),max(d,e)),maxn);//maxn更新
         	}
	    }
	cout<<maxn;//输出答案
    return 0;
}
```

---

## 作者：面向大海 (赞：0)

$O(n^2)$算法

把矩阵分成好多个环，用O(n)时间求环上最大连续子段和(对最大连续子段和以及sum减去最小连续子段和取最大值)

注意要特判全部是负数的情况(最大连续子段和可能会一个都不取)
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200;
int ma[N << 1][N << 1];

int main()
{
    int n, m, ans = -1E9;
    scanf("%d", &n);
    m = n << 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &ma[i][j]);
            ans = max(ans, ma[i][j]);
            ma[i + n][j] = ma[i][j + n] = ma[i + n][j + n] = ma[i][j];
        }
    if (ans <= 0)
    {
        printf("%d", ans);
        return 0;
    }
    for (int i = 0; i < n; ++i)
    {
        int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, tmp1 = 0,
            tmp2 = 0, tmp3 = 0, tmp4 = 0, sum1 = 0, sum2 = 0, sum3 = 0,
            sum4 = 0;
        for (int j = 0; j < n; ++j)
        {
            sum1 += ma[i][j];
            a += ma[i][j];
            if (a < 0) a = 0;
            sum2 += ma[j][i];
            b += ma[j][i];
            if (b < 0) b = 0;
            c += ma[i][j];
            if (c > 0) c = 0;
            tmp1 = min(tmp1, c);
            d += ma[j][i];
            if (d > 0) d = 0;
            tmp2 = min(tmp2, d);
            sum3 += ma[i + j][j];
            e += ma[i + j][j];
            if (e < 0) e = 0;
            sum4 += ma[j][i + j];
            f += ma[j][i + j];
            if (f < 0) f = 0;
            g += ma[i + j][j];
            if (g > 0) g = 0;
            tmp3 = min(tmp3, g);
            h += ma[j][i + j];
            if (h > 0) h = 0;
            tmp4 = min(tmp4, h);
            ans = max(ans, max(max(a, b), max(e, f)));
        }
        ans = max(ans, max(max(sum1 - tmp1, sum2 - tmp2),
                           max(sum3 - tmp3, sum4 - tmp4)));
    }
    for (int i = n - 1; i < m - 1; ++i)
    {
        int a = 0, b = 0, tmp = 0, sum = 0;
        for (int j = 0; j < n; ++j)
        {
            sum += ma[i - j][j];
            a += ma[i - j][j];
            if (a < 0) a = 0;
            b += ma[i - j][j];
            if (b > 0) b = 0;
            tmp = min(tmp, b);
            ans = max(ans, a);
        }
        ans = max(ans, sum - tmp);
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：NaVi_Awson (赞：0)

不用楼下这么麻烦，直接暴力从四个方向找

数据比较蒻。。。

附上代码：

```cpp
#include<iostream>
#include<cstdio>
 using namespace std;
int a[205][205],n,m,ans=-1e9;
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    for (int i=1;i<=n;i++)//横向
    {
        for (int j=1;j<=n;j++)
```
{//枚举所有的点
             
```cpp
            int cnt=0;
            for (int k=0;k<n;k++)//第K个点
            {
                int x=(j+k)%n;
                if (x==0) x=n;
                if (cnt+a[i][x]>a[i][x]) cnt+=a[i][x];
                else cnt=a[i][x];
                ans=max(ans,cnt);
            }
        }
    }
    for (int i=1;i<=n;i++)//纵向
    {
        for (int j=1;j<=n;j++)
        {
            int cnt=0;
            for (int k=0;k<n;k++)
            {
                int x=(j+k)%n;
                if (x==0) x=n;
                if (cnt+a[x][i]>a[x][i]) cnt+=a[x][i];
                else cnt=a[x][i];
                ans=max(ans,cnt);
            }
        }
    }
    for (int i=1;i<=n;i++)//右下对角
    {
        for (int j=1;j<=n;j++)
        {
            int cnt=0;
            for (int k=0;k<n;k++)
            {
                int x=(i+k)%n;
                int y=(j+k)%n;
                if (x==0) x=n;
                if (y==0) y=n;
                if (cnt+a[x][y]>a[x][y]) cnt+=a[x][y];
                else cnt=a[x][y];
                ans=max(ans,cnt);
            }
        }
    }
    for (int i=1;i<=n;i++)//右上对角
    {
        for (int j=1;j<=n;j++)
        {
            int cnt=0;
            for (int k=0;k<n;k++)
            {
                int x=(i-k+n)%n;
                int y=(j+k)%n;
                if (x==0) x=n;
                if (y==0) y=n;
                if (cnt+a[x][y]>a[x][y]) cnt+=a[x][y];
                else cnt=a[x][y];
                ans=max(ans,cnt);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：什么叫中二呀 (赞：0)

## 这题直接模拟！

你看看那~~破~~数据,N<=200,就暴搜了……

## 思路：搜索每条线，求和最大。

注：斜线上比较难懂……

样例却过不了，自己测试一遍，没错！

就高兴地交上去了。

### 贴代码：

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int m[200][200],N,s[4],max1=-1000000000;
int main()
{
    cin>>N;
    for(int i=0;i<N*N;i++)scanf("%d",&m[i%N][i/N]);
    //神奇输入
    for(int i=0;i<N;i++)
    { s[0]=s[1]=s[2]=s[3]=0;//全部赋0
  	  for(int j=0;j<N;j++)
      { s[0]+=m[i][j];//横线相加
        s[1]+=m[j][i];//竖线相加
        s[2]+=m[(i-j+N)%N][(i+j)%N];
        s[3]+=m[(i+j)%N][j%N];}//两条斜线相加
    max1=max(max(max(s[0],s[1]),max(s[2],s[3])),max1);}//取最大值
    cout<<max1;
    return 0;
}
```
------------

## 发现，8个点全是WA……

重新读题，发现原来可以不走完……

重做代码：（下面正解）

可能有看不懂的地方，下面有注释（但是我也没看懂）

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int m[200][200],N,s[4],max1=-1000000000;
int main()
{
    cin>>N;
    for(int i=0;i<N*N;i++)scanf("%d",&m[i/N][i%N]);
    //告诉你了，神奇输入
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)//枚举点
      { s[0]=0,s[1]=0,s[2]=0,s[3]=0;//也告诉过你了
        for(int k=0;k<N;k++)
        { s[0]+=m[i][(j+k)%N];//横线相加
          s[1]+=m[(i+k)%N][j];//竖线相加
          s[2]+=m[(i-k+N)%N][(j+k)%N];//左斜线相加（即和相等）
          s[3]+=m[(i+k)%N][(j+k)%N];//右斜线相加（即差相等）
      	  max1=max(max(max(s[0],s[1]),max(s[2],s[3])),max1);}
      }               //告诉过你多少遍了，求最大值
    cout<<max1;
    return 0;
}
```
------------

终于AC了。二十几个人过的题目很有成就感！

---

