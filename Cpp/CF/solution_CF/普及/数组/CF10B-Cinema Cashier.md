# Cinema Cashier

## 题目描述

Berland 的所有电影院都是 $K$ 行 $K$ 列的矩形，每行有 $K$ 个座位，且 $K$ 是奇数。行号和座位号均从 $1$ 到 $K$ 编号。出于安全原因，购票者不能自行选择座位。过去由售票员分配座位，现在则由专门的选座程序负责。研究发现，大多数 Berland 居民去电影院是为了看电影，因此他们希望尽可能靠近影厅中心就座。此外，一起观影的 $M$ 个人必须在同一行连续占据 $M$ 个座位。

我们来描述该程序的选座和售票算法。当收到 $M$ 个座位的请求时，程序需要确定行号 $x$ 以及该行中座位区间 $[y_l, y_r]$，其中 $y_r - y_l + 1 = M$。在所有可行方案中，程序应选择使所有座位到影厅中心的“距离和”最小的方案。设影厅中心的行号和座位号均为 $\left(\frac{K+1}{2}, \frac{K+1}{2}\right)$，则距离和的计算公式为：
$$
\sum_{i=1}^{M} \left( |x - \frac{K+1}{2}| + |y_i - \frac{K+1}{2}| \right)
$$
其中 $y_i$ 表示所选区间内的每个座位号。

如果有多个方案距离和相同，优先选择行号 $x$ 较小的方案；若仍有多个方案，选择 $y_l$ 最小的方案。

你的任务是模拟该程序的工作过程。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
1 1
```

### 输出

```
1 1 1
-1
```

## 样例 #2

### 输入

```
4 3
1 2 3 1
```

### 输出

```
2 2 2
1 1 2
3 1 3
2 1 1
```

# 题解

## 作者：404Not_Found (赞：17)

upd 9/17：修正了排版（第一篇题解真的太丑了 qwq）。

# 前言

表示是从树状数组的标签找过来的，竟然还打了一个最优解，又发现没题解，本蒟蒻就来水一发。


------------

# 题意
说实话这道题的翻译真的不清楚，~~靠度娘才把题看懂~~。大意差不多就是有一个大小为 $k^2$ 的电影院，会来 $n$ 波人，同一波来的人必须坐在同一排，$(zx,zy)$ 为中心点，并且有一个花费为 $|x-zx|+|y-zy|$，要尽量使花费最小。如果坐不下，输出 $-1$。


------------
# 分析
看到 $1 \le K \le 99$ 的数据，自然就能想到暴力枚举每一个位置。我们可以用树状数组来维护每一行的区间和（不会树状数组的戳[这里](https://www.cnblogs.com/xenny/p/9739600.html)，个人认为是讲得最好的一篇）。但因为要维护每一行，所以要开n个树状数组。

我们可以直接枚举行和列算出所有合法方案，再以贪心思想，每一次坐得尽量接近中间，即寻找花费最少的方案。现在要解决的只有计算花费了。

计算花费可以循环累加，但这样还是太慢了（但貌似也可以过？）。我们考虑数学方法。下面是小学生都能看懂的推导过程：

单个位置的花费为 $|x-zx|+|y-zy|$ 。又由于是一个 $k^2$ 的电影院，所以 $zx=zy$ 。

令 $mid=zx=zy$ ,则每个位置的花费为 $|x-mid|+|y-mid|$ ，一波人自然就是每个位置的花费之和。设每一波来的人数为 $m$ ，坐的左端点为 $l$，则右端点为 $l+m-1$ ，花费之和可以表示为

$|x-mid|+|l-mid|+|x-mid|+|(l+1)-mid|+...+|x-mid|+|(l+m-1)-mid|=m \times |x-mid|+|l-mid|+|(l+1)-mid|+...+|(l+m-1)-mid|$ 

观察可以发现似乎存在一个等差数列，只是套在了绝对值里面。**所以我们要分类讨论**：

- 当 $ l\ge mid$ 时

则总花费为 $m \times |x-mid|+l-mid+(l+1)-mid+..+(l+m-1)-mid=m \times |x-mid|+(l+l+1+l+2+...+l+m-1)-m \times mid$ 

不妨定义函数
```cpp
int cost(int l,int r);
```
求 $\sum\limits_{i=l}^ri$

则原式变为

$m \times |x-mid|+cost(l,l+m-1)-m \times mid$

其他的就好办了。

- 当 $ l+m-1 \le mid $ 时

总花费为
$m \times |x-mid|+m \times mid-cost(l,l+m-1) $

- 当 $l<mid<l+m-1$ 时

不妨拆成两段来看：
在 $mid$ 右边:

$m \times |x-mid|+cost(mid,y+m-1)$

$mid$ 左边：

$mid \times (mid-y)-mid \times (y+m-mid)-cost(y,mid-1)$

两式相加即可。


------------
~~感觉真的像是写给小学生看的~~

现在应该很清晰了，上代码！



```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
int n,k;
int tree[105][105];
//树状数组 
inline int sum(int line,int x)
{
    int res=0;
    for(int i=x;i>=1;i-=lowbit(i))
        res+=tree[line][i];
    return res;
}
inline int query(int line,int l,int r)
{
    return sum(line,r)-sum(line,l-1);
}
inline void add(int line,int x)
{
    for(int i=x;i<=k;i+=lowbit(i))
        tree[line][i]++;
}
//同上，等差数列求和 
inline int cost(int l,int r)
{
    return (l+r)*(r-l+1)>>1;
}
int main()
{
    scanf("%d%d",&n,&k);
    int mid=(k>>1)+1;
    for(int i=1;i<=n;i++)
    {
        int m;
        scanf("%d",&m);
        int ansx=-1,ansy=-1;
        int minn=0x3f3f3f3f;
        for(int x=1;x<=k;x++)//枚举行 
            for(int y=1;y+m-1<=k;y++)//枚举列 
                if(query(x,y,y+m-1)==0)//如果这一片区域没有人坐 
                {
                    int tmp;
                    if(y>=mid) tmp=cost(y,y+m-1)-mid*m+abs(x-mid)*m;
                    else if(y+m-1<=mid) tmp=mid*m-cost(y,y+m-1)+abs(x-mid)*m;
                    else tmp=abs(x-mid)*m+cost(mid,y+m-1)-(y+m-mid)*mid+mid*(mid-y)-cost(y,mid-1);//同前 
                    if(tmp<minn)
                    {
                        minn=tmp;
                        ansx=x;
                        ansy=y;
                    }
                }
        if(minn!=0x3f3f3f3f)
        {
            printf("%d %d %d\n",ansx,ansy,ansy+m-1);
            for(int j=ansy;j<=ansy+m-1;j++)
                add(ansx,j); 
        }
        else puts("-1");
    }
    return 0;
}
```



------------
时间复杂度为 $O(nk^2logk)$，能通过此题。

感谢观看。

---

## 作者：ncwzdlsd (赞：4)

暴力。

先考虑一个贪心策略：坐在一行的一波人一定是挨着的，因为同一行的一波人坐得越分散每个人到中心点的曼哈顿距离就越大。

对于每一波人，枚举坐在哪一行、坐在该行的起始位置，然后判断能否坐下即可。

时间复杂度 $O(NK^3)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool vis[1005][1005];

int main()
{
    int N,K;cin>>N>>K;
    int cc=(K+1)/2;
    while(N--)
    {
        int ans=INT_MAX,M;cin>>M;
        int x=1,yl=1;
        for(int i=1;i<=K;i++)
            for(int j=1;j<=K-M+1;j++)
            {
                bool flag=1;
                int tmp=0;
                for(int l=j;l<=j+M-1;l++)
                {
                    if(vis[i][l]){flag=0;break;}
                    else tmp+=abs(i-cc)+abs(l-cc);
                }
                if(flag&&tmp<ans) ans=tmp,x=i,yl=j;
            }
        if(ans==INT_MAX) cout<<"-1\n";
        else 
        {
            cout<<x<<' '<<yl<<' '<<(yl+M-1)<<'\n';
            for(int i=yl;i<=yl+M-1;i++) vis[x][i]=1;
        }
    }
    return 0;
}
```

---

## 作者：一铭君一 (赞：1)

看了其他的两篇题解，都使用了数据结构，但是这题数据其实很小，直接暴力就能过。我想说的是，不管是赛场上还是平常练习，大家预估好可以接受的复杂度之后要写出最简单的代码来，既不容易出错还节省时间。

当然了，使用数据结构锻炼思维也未尝不可。

回归正题，$k \leq 99, n \leq 1000$ 。

假设每次来的一群人有 $t$ 个，考虑直接枚举这一排人左侧排头的位置 $(x,y)$，这样枚举的复杂度是 $O(k^2)$ 的。

对于每个合法的排头位置，暴力检查它和它之后的 $t$ 个位置是不是空的，如果是空的，就计算一下总花费尝试更新答案，当枚举完所有的可能之后，花费最小的即为最佳安排。这样枚举一个位置的复杂度是 $O(t)$ 的。

总体复杂度为 $O(nk^2+\sum t)$，刚刚破亿，不考虑优化的话，加个快读快写大概也过了。

但是这样预估复杂度实际上有点问题，每次询问的 $t$ 越大，能安排的位置就越少，实际上只用枚举 $k(k-t+1)$ 个位置（第一个人后面至少留下 $t-1$ 个座位）。

让我们忽略常数，重新计算一下总复杂度： 

$$O(nk(k-t)+ \sum t)=O(nk^2 - \sum t+ \sum t)= O(nk^2)$$

对于本题的数据显然是可以通过的。

然后就是暴力大法好啊：

```cpp
const int maxn = 105;
const int Inf = 0x7f7f7f7f;

int n, k;
int mid;
bool sits[maxn][maxn];

pair<bool, int> CalcCost(const int &x, const int &y, const int &len)
{
  int sum = 0;
  if(y + len - 1 > k)
    return make_pair(false, len);
  for(int j = 0 ; j < len; j ++)
  {
    if(sits[x][y + j])
      return make_pair(false, j);
    sum += abs(x - mid) + abs(y + j - mid);
  }
  return make_pair(true, sum);
}

signed main()
{
  ReadInt(n), ReadInt(k);
  mid = (k + 1) / 2;
  while(n --)
  {
    int len;
    ReadInt(len);//每次来了 len 个人
    int ansx, ansy, ans = Inf;
    for(int i = 1 ; i <= k ; i ++)
      for(int j = 1 ; j <= k ; j ++)
      {
        if(!sits[i][j])
        {
          pair<bool, int> result = CalcCost(i, j, len);
          if(result.first && result.second < ans)
          {
            ans = result.second;
            ansx = i, ansy = j;
          }
          else if(!result.first)
            j += result.second;
            //小优化，一个位置被证明不行，它后面至少 len 个也不行
        }
      }
    //尝试安排并计费
    if(ans != Inf)
    {
      for(int j = 0 ; j < len ; j ++)
        sits[ansx][ansy + j] = 1;
      printf("%d %d %d\n",ansx, ansy, ansy + len - 1);
    }//坐下了
    else
      printf("-1\n");
    //没坐下
  }
  return 0;
}
```

---

## 作者：YNH_QAQ (赞：0)

参考了一些题解，并且数据范围较小，所以这题用贪心。

大小为 $k·k$ 的电影院，来 $n$ 个人。同一行的人做的越紧凑，距离就越小。枚举能坐下时坐在哪一行的起始位置，电影院状态弄个数组存储即可。

复杂度 $O(k^3n)$。

核心代码：
```cpp
for(int i=1;i<=k;i++)
	for(int j=1;j<=k-a[i]+1;j++){
		bool flag=1;
		int tmp=0;
		for(int l=j;l<=j+a_i-1;l++){
			if(vis[i][l]){
            flag=0;
            break;
        }
			else tmp+=abs(i-(k+1)/2)+abs(l-(k+1)/2);
		}
		if(flag&&tmp<ans) ans=tmp,x=i,y=j;
	}
```

---

