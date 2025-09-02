# Skyscrapers

## 题目描述

Dora loves adventures quite a lot. During some journey she encountered an amazing city, which is formed by $ n $ streets along the Eastern direction and $ m $ streets across the Southern direction. Naturally, this city has $ nm $ intersections. At any intersection of $ i $ -th Eastern street and $ j $ -th Southern street there is a monumental skyscraper. Dora instantly became curious and decided to explore the heights of the city buildings.

When Dora passes through the intersection of the $ i $ -th Eastern and $ j $ -th Southern street she examines those two streets. After Dora learns the heights of all the skyscrapers on those two streets she wonders: how one should reassign heights to the skyscrapers on those two streets, so that the maximum height would be as small as possible and the result of comparing the heights of any two skyscrapers on one street wouldn't change.

Formally, on every of $ nm $ intersections Dora solves an independent problem. She sees $ n + m - 1 $ skyscrapers and for each of them she knows its real height. Moreover, any two heights can be compared to get a result "greater", "smaller" or "equal". Now Dora wants to select some integer $ x $ and assign every skyscraper a height from $ 1 $ to $ x $ . When assigning heights, Dora wants to preserve the relative order of the skyscrapers in both streets. That is, the result of any comparison of heights of two skyscrapers in the current Eastern street shouldn't change and the result of any comparison of heights of two skyscrapers in current Southern street shouldn't change as well. Note that skyscrapers located on the Southern street are not compared with skyscrapers located on the Eastern street only. However, the skyscraper located at the streets intersection can be compared with both Southern and Eastern skyscrapers. For every intersection Dora wants to independently calculate the minimum possible $ x $ .

For example, if the intersection and the two streets corresponding to it look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/b8843ce623a50ba6456e010cf2c98b56b8233e32.png)Then it is optimal to replace the heights of the skyscrapers as follows (note that all comparisons "less", "equal", "greater" inside the Eastern street and inside the Southern street are preserved)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/39639df2ab400935251b9673b829739a400357e3.png)The largest used number is $ 5 $ , hence the answer for this intersection would be $ 5 $ .

Help Dora to compute the answers for each intersection.

## 说明/提示

In the first example, it's not possible to decrease the maximum used height for the problem at any intersection, hence we don't have to change any heights.

In the second example, the answers are as follows:

- For the intersection of the first line and the first column ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/bc671d6177e8cc9f707791f4138061e48affa407.png)
- For the intersection of the first line and the second column ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/d2849b7fe606944f0348e44d9e4591b7a87d7ec6.png)
- For the intersection of the second line and the first column ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/75a5e58bc106cd0d570dac89dc650cfe52c62ac2.png)
- For the intersection of the second line and the second column ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/d38748916182cc695792c65c0945a1b43c6a19ac.png)

## 样例 #1

### 输入

```
2 3
1 2 1
2 1 2
```

### 输出

```
2 2 2 
2 2 2 
```

## 样例 #2

### 输入

```
2 2
1 2
3 4
```

### 输出

```
2 3 
3 2 
```

# 题解

## 作者：CE_Prince (赞：5)

# 离散化
我们把每一行和每一列拿出来拿出来离散化处理好之后直接二分一下这个元素在行和列中有多少个元素比它大，有多少个元素比它小。 在这一行一列中最多有 $\max\left(xa,ya\right)$ 个比它小的数。最多有    $\max\left(xb,yb\right)$ 个比它大的数。所以最后输出    $\max\left(xa,ya\right)+\max\left(xb,yb\right)$ 就好啦QVQ （变量代表什么都在代码中）。

## Code:
```cpp

#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e3+10;
int a[MAXN][MAXN],b[MAXN][MAXN],n,m,x[MAXN][MAXN],va[MAXN],vb[MAXN],xa,ya;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&x[i][j]);//输入原矩阵 注意 一定要用scanf 用cin会超时
            a[i][j]=x[i][j];//行离散化数组
            b[j][i]=x[i][j];//列离散化数组
        }
    }
    for(int i=1;i<=n;i++){//离散化第 1......n 行
        sort(a[i]+1,a[i]+m+1);//将第i行从小到大排序
        va[i]=unique(a[i]+1,a[i]+m+1)-a[i]-1;//将去重完的长度存进va[i]
    }
    for(int i=1;i<=m;i++){//离散化第 1......m 列
        sort(b[i]+1,b[i]+n+1);//将第i列从小到大排序
        vb[i]=unique(b[i]+1,b[i]+n+1)-b[i]-1;//将去重完的长度存进vb[i]
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            xa=lower_bound(a[i],a[i]+va[i],x[i][j])-a[i];//二分查找x[i][j]在这一行从小到大排第几
            ya=lower_bound(b[j],b[j]+vb[j],x[i][j])-b[j];//二分查找x[i][j]在这一列从小到大排第几
            int xb=va[i]-xa;//xb表示在这一行有多少个比x[i][j]大的数
            int yb=vb[j]-ya;//yb表示在这一列有多少个比x[i][j]大的数
            printf("%d ",max(xa,ya)+max(xb,yb));//输出最终结果 
        }
        cout<<endl;
    }
    return 0;
}
```



---

## 作者：OIerJiang_1017 (赞：1)

## [CF1137A 题目传送门](https://www.luogu.com.cn/problem/CF1137A)

## 题目大意
给出一个 $n \times m$ 的网格矩阵，网格中每个单元格都有一个权值 $A_{i,j}$。对于每一个单元格，提取这个单元格的行和列，允许对这一行和这一列上的每个单元格重新赋权值，但需要在保证矩阵中的这一行上元素之间和这一列上元素之间的相对大小均不改变的前提下，使得每个单元格权值的最大值最小，并记录下这个最小值，输出时，作为矩阵相应单元格的权值。每次操作每次按照输入格式，对应输出每一个单元格新的权值。

## 解决思路
### 概念理解
首先了解新概念**离散化**。
> 离散化，把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。

分别**离散化**每一行和每一列，然后使用**二分**得出每行和每列中分别有几个数比它大和比它小。在这一行一列中最多有 $\max (xa, ya)$ 个比它小的数。最多有 $\max (xb, yb)$ 个比它大的数。所以最后输出 $\max (xa, ya) + \max (xb, yb)$，并按题目输出格式换行即可。

## 代码展示
```cpp
#include <iostream>
using namespace std;

const int N = 1010;
int n, m, x[N][N], a[N][N];
int b[N][N], va[N], vb[N], xa, ya;

int main()
{
    scanf("%d%d", &n, &m);//建议scanf,更快
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
		{
            scanf("%d", &x[i][j]);
            a[i][j] = x[i][j];//行离散化
            b[j][i] = x[i][j];//列离散化
        }
    for(int i = 1; i <= n; i++)
	{//离散化第 1 ~ n 行
        sort(a[i] + 1, a[i] + m + 1);//排序第i行
        va[i] = unique(a[i] + 1, a[i] + m + 1) - a[i] - 1;//va存储去重后的数组长度
        //unique函数可以对数组去重
    }
    for(int i = 1; i <= m; i++)
	{//离散化第 1 ~ m 列
        sort(b[i] + 1, b[i] + n + 1);//排序第i列
        vb[i] = unique(b[i] + 1, b[i] + n + 1) - b[i] - 1;//va存储去重后的数组长度
    }
    for(int i = 1; i <= n; i++)
	{
        for(int j = 1; j <= m; j++)
		{
            xa = lower_bound(a[i], a[i] + va[i], x[i][j]) - a[i];//二分查找x[i][j]在第i行从小到大排第几
            ya = lower_bound(b[j], b[j] + vb[j], x[i][j]) - b[j];//二分查找x[i][j]在第i列从小到大排第几 
            int xb = va[i] - xa, yb = vb[j] - ya;
            printf("%d ", max(xa, ya) + max(xb, yb));//建议printf,更快
        }
        printf("\n");//换行是个好习惯
    }
    return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

根据题意先对每行每列**分别**进行离散化，同时记录一下离散化后有几个不同的数字。

发现对于每一个交叉口而言，最多有 $\max(f1,f2)$ 个比他小的数（$f1$，$f2$ 表示离散化后的值），相应的有$\max(alen-f1,blen-f2)$ 个比他大的数。
($alen$，$blen$ 分别表示离散化后这行和这列有多少个不同的个数)。
## 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1010][1010],f1[1010][1010],f2[1010][1010],arr[1010],al,alen[1010],blen[1010];
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++){
		al=0;
		for(int j=1;j<=m;j++) arr[++al]=a[i][j];
		sort(arr+1,arr+1+al);
		alen[i]=unique(arr+1,arr+1+al)-arr-1;
		for(int j=1;j<=m;j++) f1[i][j]=lower_bound(arr+1,arr+1+alen[i],a[i][j])-arr;
	}
	for(int i=1;i<=m;i++){
		al=0;
		for(int j=1;j<=n;j++) arr[++al]=a[j][i];
		sort(arr+1,arr+1+al);
		blen[i]=unique(arr+1,arr+1+al)-arr-1;
		for(int j=1;j<=n;j++) f2[j][i]=lower_bound(arr+1,arr+1+blen[i],a[j][i])-arr;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",max(f1[i][j],f2[i][j])+max(alen[i]-f1[i][j],blen[j]-f2[i][j]));
		}
		printf("\n");
	}
    return 0;
}

```

---

## 作者：FP·荷兰猪 (赞：0)

## 排序+数据结构

将每一行（每一列）都排个序，并将原位置的在这一行（列）中的排行记录在一个数组里

注意，要将楼高度相同的元素看作一个元素

> 如 1 1 4 5 6 8 8，则排行是

>     1 1 2 3 4 5 5

处理好后，枚举每一个十字路口，

若当前的处在的行的排行大于列的排行，则当前这个元素之后的列中元素应以行的排行开始依次递增，

若当前的处在的行的排行小于列的排行，则当前这个元素之后的行中元素应以列的排行开始依次递增，

注意，若当前的处在的行的排行等于列的排行时，则要从如上两个方面同时考虑，取最大值。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[1010][1010],hh[1010][1010],ll[1010][1010];
int mh[1500],ml[1500];
struct node
{
    int wh,num;
};
vector <node> h[1010],l[1010];
bool cmp(node a,node b)
{
    return a.num<b.num;//以高度降序排序
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for (int i=1;i<=n;i++)//处理行的情况
    {
        node t;
        for (int j=1;j<=m;j++)
        {
            t.num=a[i][j];
            t.wh=j;
            h[i].push_back(t);
        }
        sort(h[i].begin(),h[i].end(),cmp);
        int how=0;
        for (int j=0;j<m;j++)
        {
            if (j!=0)
            {
                if (h[i][j-1].num==h[i][j].num)
                  how++;//重复的有多少个
            }
            hh[i][h[i][j].wh]=j+1-how;//记录排行
        }
        mh[i]=m-how;//最大值
    }
    for (int j=1;j<=m;j++)//处理列的情况
    {
        node t;
        for (int i=1;i<=n;i++)
        {
            t.num=a[i][j];
            t.wh=i;
            l[j].push_back(t);
        }
        sort(l[j].begin(),l[j].end(),cmp);
        int how=0;
        for (int i=0;i<n;i++)
        {
            if (i!=0)
            {
                if (l[j][i-1].num==l[j][i].num)
                  how++;
            }
            ll[l[j][i].wh][j]=i+1-how;
        }
        ml[j]=n-how;
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            int cha;
            if (hh[i][j]==ll[i][j])//如上
            {
                int cha1;
                cha1=mh[i]-hh[i][j];
                cha=ml[j]-ll[i][j];
                printf("%d ",max(max(hh[i][j]+cha,mh[i]),max(ll[i][j]+cha1,ml[j])));
            }
            else
            if (hh[i][j]>ll[i][j])
            {
                cha=ml[j]-ll[i][j];
                printf("%d ",max(hh[i][j]+cha,mh[i]));
            }
            else
            if (hh[i][j]<ll[i][j])
            {
                cha=mh[i]-hh[i][j];
                printf("%d ",max(ll[i][j]+cha,ml[j]));
            }
        }
        printf("\n");
    }
}
```

---

## 作者：Zechariah (赞：0)

贪心即可  
我们把每一行和每一列单独拿出来排序去重  
对于一个询问点$(i,j)$，直接二分一下他在行和列中的位置  
行中比这个数小的数有$x$个，比这个数大的数有$totx-x$个  
列中比这个数小的数有$y$个，比这个数大的数有$toty-y$个  
于是要想表示出所有比这个数小的数，我们需要至少$min(x, y)$个  
要想表示出所有比这个数小的数，我们需要至少$max(totx - x, toty-y)$个  
直接输出他们的和就好了
```cpp
#pragma GCC optimize("fast-math,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e3 + 5, mod = 998244353, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int ans[N][N], a[N << 1][N];

int main(void)
{
    rg int n = fast_IO::read(), m = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)
        for (rg int j = 1; j <= m; ++j)
            ans[i][j] = a[i][j] = a[j + n][i] = fast_IO::read();
    for (rg int i = 1; i <= n + m; ++i)
    {
        if (i <= n)
        {
            sort(a[i] + 1, a[i] + m + 1);
            *a[i] = unique(a[i] + 1, a[i] + m + 1) - a[i] - 1;
        }
        else
        {
            sort(a[i] + 1, a[i] + n + 1);
            *a[i] = unique(a[i] + 1, a[i] + n + 1) - a[i] - 1;
        }
    }
    for (rg int i = 1; i <= n; ++i)
    {
        for (rg int j = 1; j <= m; ++j)
        {
            rg int x = lower_bound(a[i] + 1, a[i] + *a[i] + 1, ans[i][j]) - a[i] - 1;
            rg int y = lower_bound(a[j + n] + 1, a[j + n] + *a[j + n] + 1, ans[i][j]) - a[j + n] - 1;
            fast_IO::write(fast_IO::max(x, y) + fast_IO::max(*a[i] - x, *a[j + n] - y)); putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}


```


---

