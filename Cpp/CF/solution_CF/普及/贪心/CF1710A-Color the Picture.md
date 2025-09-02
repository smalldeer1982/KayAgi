# Color the Picture

## 题目描述

A picture can be represented as an $ n\times m $ grid ( $ n $ rows and $ m $ columns) so that each of the $ n \cdot m $ cells is colored with one color. You have $ k $ pigments of different colors. You have a limited amount of each pigment, more precisely you can color at most $ a_i $ cells with the $ i $ -th pigment.

A picture is considered beautiful if each cell has at least $ 3 $ toroidal neighbors with the same color as itself.

Two cells are considered toroidal neighbors if they toroidally share an edge. In other words, for some integers $ 1 \leq x_1,x_2 \leq n $ and $ 1 \leq y_1,y_2 \leq m $ , the cell in the $ x_1 $ -th row and $ y_1 $ -th column is a toroidal neighbor of the cell in the $ x_2 $ -th row and $ y_2 $ -th column if one of following two conditions holds:

- $ x_1-x_2 \equiv \pm1 \pmod{n} $ and $ y_1=y_2 $ , or
- $ y_1-y_2 \equiv \pm1 \pmod{m} $ and $ x_1=x_2 $ .

Notice that each cell has exactly $ 4 $ toroidal neighbors. For example, if $ n=3 $ and $ m=4 $ , the toroidal neighbors of the cell $ (1, 2) $ (the cell on the first row and second column) are: $ (3, 2) $ , $ (2, 2) $ , $ (1, 3) $ , $ (1, 1) $ . They are shown in gray on the image below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710A/e3c8d205b2238ddbd1672ed2006ec3bad526c6bc.png)The gray cells show toroidal neighbors of $ (1, 2) $ .Is it possible to color all cells with the pigments provided and create a beautiful picture?

## 说明/提示

In the first test case, one possible solution is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710A/3537b81501ae3eaf0154251b0f27e35d8e63b1ec.png)In the third test case, we can color all cells with pigment $ 1 $ .

## 样例 #1

### 输入

```
6
4 6 3
12 9 8
3 3 2
8 8
3 3 2
9 5
4 5 2
10 11
5 4 2
9 11
10 10 3
11 45 14```

### 输出

```
Yes
No
Yes
Yes
No
No```

# 题解

## 作者：linyuhuai (赞：9)

[长文前往 blog 获得更好的阅读体验](https://by505244.github.io/oi_blogs/2022/07/25/CF1710A题解/) & [原题链接](https://codeforces.com/contest/1710/problem/A)

2023/6/14：修改部分内容。

先给下结论：

- 每种颜色必须涂满**连续的**两行或两列
- 根据上面的结论进一步推导出所有颜色只能竖着或横着。

##### 证明：


* 约定：

  1. 文章中 $(x,y)$ $x$ 指行号，$y$ 指列号。

  2. 文章中，设 $(i,j)$  的颜色为 $color_{i,j}$：

  - XX 颜色块的左上指所有符合条件的 $(i,j)$ 其中  $color_{i-1,j}\not=color_{i,j},color_{i,j-1}\not=color_{i,j}$。

  - XX 颜色块的右上指所有符合条件的 $(i,j)$ 其中  $color_{i-1,j}\not=color_{i,j},color_{i,j+1}\not=color_{i,j}$。
  - XX 颜色块的左下指所有符合条件的 $(i,j)$ 其中  $color_{i+1,j}\not=color_{i,j},color_{i,j-1}\not=color_{i,j}$。
  - XX 颜色块的右上指所有符合条件的 $(i,j)$ 其中  $color_{i+1,j}\not=color_{i,j},color_{i,j+1}\not=color_{i,j}$。
  - XX 颜色块的（左上/左下/右上/右下）还要求 $color_{i,j}=该颜色$。
  - - 注意：一个颜色块的（左上/左下/右上/右下）可能不止一个。

我们假定有两种及以上的颜色。

- 如果只涂一列：

那么显而易见每种方块只有上下两个方块与之相邻。不满足题目要求。
- 如果**所涂的列都涂满了**且涂了两列及以上（其中 $n=8,m=5$）：
- （注意其中黄色部分只是代表除蓝色以外其他颜色，不代表单一颜色）：

![](https://by505244.github.io/oi_blogs/2022/07/25/CF1710A题解/4.png)

对于不处于边缘地区的方块，一定有上下左右四个同颜色的方块，也就是，不在边缘地区的方块不会影响答案。

对于在边缘地区不在 蓝色颜色块的左上左下右上右下 的方块，一定有除了面对黄色的方向外其他三个方向有同颜色的方格。

对于在蓝色颜色块的左上左下右上右下的块，根据题目的定义，$(1,2)$ 和 $(8,2)$ 也算相邻，$(1,4)$ 和 $(8,4)$ 也算相邻，再加上前一条的结论，那么其均有 $3$ 种同颜色的方块与之相邻。符合题目要求。


- 如果**没涂满**任何一列或一行且涂两列及以上：

  

![](https://by505244.github.io/oi_blogs/2022/07/25/CF1710A题解/2.png)

显而易见在蓝色颜色块的左上左下右上右下都只有 $2$ 种同颜色的方块与它相邻。

蓝色颜色块的左下最多只有上和右两个相同颜色方块相邻。因为如果左有了相同颜色的方块，那么就不符合左下的定义。左下如果下有了同颜色的方块也不符合定义。其他 左下右上右下 区域同理。

但特别考虑 $x_{左下}=n$ 时，此时题目定义的”下“是位于 $(1,y_{左下})$。但特别注意不涂满一列指的是**这一列中有两种或以上颜色，不要求这一列的颜色是一个块**，更简单的说就是 $(1,y_{左下})$ **可能**与 $(n,y_{左下})$ 颜色相同。

但是对于这种情况我们发现 $x_{左上}\not=1$ （不涂满一列，如果一块中 $x_{左上}=1,x_{右下}=n$，那么就涂满了这一列）也就是左上的上面一块一定是 $(x_{左上}-1,y_{左上})$，那么根据前面的结论左上一定没有三个同颜色的相邻方块。

对于行的证明，只需要把图翻转过来即可。

$\texttt{END?}$

但特别的，对于这种奇奇怪怪的形状：

![](https://by505244.github.io/oi_blogs/2022/07/25/CF1710A题解/6.png)

还有

![](https://by505244.github.io/oi_blogs/2022/07/25/CF1710A题解/7.png)

注意到结合开头的约定，第一张图有不止一个的左上左下右上右下。如左下可能在 $(9,1),(4,5),(7,7),(9,8)$。

在蓝色与黄色的交界处，一定存在一格颜色，且这格只有两格相同颜色相邻。上文已经对此种情况所出现的左上左下右上右下格进行证明。但如下图所示，对于蓝色可能左上左下右上右下均符合要求，但观察黄色区域，考虑黄色区域最优情况，即全部都是同一种颜色，结合前面证明，发现黄色区域并不符合要求。

**证毕。**


### 实现

前排提示：本份题解的复杂度是 $\mathcal{O}(k\log k)$，劣于官方题解的 $\mathcal O(k)$。但数据范围允许此做法通过。 

结合上面的结论。

第 $i$ 种颜色至少取 $2$ 行或 $2$ 列，至多取 $\lfloor \frac{a_i}{m}\rfloor$ 行或 $\lfloor \frac{a_i}{n}\rfloor$ 列。  

我们分别把 $\lfloor \frac{a_i}{m}\rfloor$ 和 $\lfloor\frac{a_i}{n}\rfloor$ 分别压入两个大根堆。

我们先选取一个大根堆，不停的取里面的元素。

取到第 $k$ 个元素时，判断该元素与前面元素加和是否大于等于**对应**的 $n$ 或 $m$。

如是，判断 $k\times2\le\ 对应的\ n\ 或\ m$。（因为前面 $k$ 个元素每个至少要 $k\times2$ 对应的行或列）

如果 $k\times2\le 对应的\ n\ 或\ m$，输出 `yes`。

然后再选取另外一个大根堆也同样进行以上操作。

判断下来一个 `yes` 都没输出，那么就是 `no` 了（~~这不是废话吗~~）


为什么要大根堆？

因为这样我们可以在 $k\times2$ 尽可能小的情况下选到最大的 $\sum^k_{j=1}\lfloor \frac{a_i}{m}\rfloor$ 或 $\sum^k_{j=1}\lfloor \frac{a_i}{n}\rfloor$（注意 $i$ 不是定值，$i$ 的值变换方式取决于遍历顺序）。

[代码](https://by505244.github.io/oi_blogs/2022/07/25/CF1710A%E9%A2%98%E8%A7%A3/#%E4%BB%A3%E7%A0%81%EF%BC%9A)




---

## 作者：taozhiming (赞：8)

## CF1710A Color the Picture
## [原题面](https://www.luogu.com.cn/problem/CF1710A)
## 今晚算是 降智 降得够够得。
## 题目分析：
通过读题我们发现两个性质：

**1.想要让三个相邻的方格颜色和本身的颜色相同，那就至少填满两行或者两列**。

**2.如果我们把能填的全填上，有可能会多出来一块，如果多出来的一块是奇数，那可能是美丽的图片，或者不是一个美丽的图片**。

对第二个性质进行分类讨论:

什么时候是美丽的？

如果我们的颜色中有一个能够填满多于两行，就说明可以把奇数的部分给填好对吧。

比如说填完两列，最后剩下了 $1$ 列，我们可以用一个可以填满大于 $2$ 列的颜色填三列，把上一个填两列的给去掉

否则就会剩下奇数列，我们不管怎么填，都会剩下一列的任意一个方格没法让他与他相邻的三个同一个颜色。（这个时候我们就怎么填都填不成美丽的图片）

-----
到这里这个题就分析完了（一道~~闪避~~题，硬是让我做了 $2$ 个小时还没打出来,我应该是没救了）

## 代码：
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define m_p make_pair
#define PII pair<int,int>
#define int long long
using namespace std;
const int N=1e6+7;
const int INF=1e18+7;
inline int read(){
    int x=0,w=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;
    for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
    return x*w;
}
int n,m,k,a[N],ans=0;
bool cmp(int a,int b)
{
	return a>b;
}
signed main()
{
	int T=read();
	while(T--)
	{
		cin>>n>>m>>k;
		for (int i=1;i<=k;i++) cin>>a[i];
		sort(a+1,a+k+1,cmp);
		bool ans1=1,ans2=1,flag=0;
		ans=0;
		for (int i=1;i<=k;i++)
		{
			if (a[i]/m<2) break;
			ans+=a[i]/m;
			if (a[i]/m>2) flag=1;
		}
		if (ans<n) ans1=0;
		else if (((ans-n)&1)&&!flag) ans1=0;
		flag=0,ans=0;
		for (int i=1;i<=k;i++)
		{
			if (a[i]/n<2) break;
			ans+=a[i]/n;
			if (a[i]/n>2) flag=1; 
		}
		if (ans<m) ans2=0;
		else if (((ans-m)&1)&&!flag) ans2=0;
		if (ans1||ans2) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

存在一个大小为 $n\times m$ 的矩阵，现对其进行染色，共有 $k$ 种颜色，第 $i$ 种颜色最多可填 $a_i$ 个格子，问是否存在一种染色方案，使得对于每个格子 $(x,y)$ 的非严格四邻域中至少有三个格子与 $(x,y)$ 颜色相同（非严格四领域指满足 $x-x'\equiv\pm 1\pmod{n}$ 且 $y=y'$ 或 $y-y'\equiv\pm 1\pmod{m}$ 且 $x=x'$ 的所有格子 $(x',y')$，实际上就是普通四邻域中超出边界的格子补到对面去）。

## 解题思路

考虑一个格子 $(x,y)$ 的非严格四邻域中至少有三个格子与其颜色相同有什么性质，显然 $(x,y)$ 最多只有一个方向上与其相邻的格子与其颜色不同，容易发现这样排列后对于每种颜色，其染色的区域一定形如连续的多行或多列。若染色区域均为连续多列，则对于一种颜色 $i$，其能染的列数即为 $\left\lfloor\frac{a_i}{n}\right\rfloor$。因为最后的染色区域一定要覆盖整个矩阵，故需满足

$$
\left(\sum_{i\in[1,k]\wedge\left\lfloor\frac{a_i}{n}\right\rfloor\ge 2} \left\lfloor\frac{a_i}{n}\right\rfloor\right)\ge m
$$

但是当上面的结果 $>m$ 时，最后的染色区域会多出来一部分，而删掉这一部分后某些染色区域有可能只有一列，不满足条件。于是便记 $cnt$ 表示满足 $\left\lfloor\frac{a_i}{n}\right\rfloor\ge 2$ 的 $i$ 的个数，此时染色列数最少即为 $cnt\times 2$，若 $cnt\times 2>m$ 则说明染到最少都会超出 $m$ 列，删掉多出来的部分必定会有某些颜色区域只有一列，故除了需满足上面的求和不等式，还需满足 $2cnt\le m$。对于染色区域均为连续多行的情况也同理，$n,m$ 换一下即可，这两种情况只需满足任意一种即存在方案。

这样考虑贪心，为了存在一种方案，要使上面的求和尽量大，同时 $cnt$ 尽量小，于是可将 $a_i$ 从大到小排序，这样只需在遇到上面的求和不等式成立的情况时，判断 $cnt$ 是否满足条件即可，时间复杂度 $O(tk\log k)$。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll t,n,m,k,a[100001],ans,cnt,bz;
bool cmp(ll x, ll y) {return x>y;}

int main()
{
	t=read();
	
	while(t--)
	{
		n=read(); m=read(); k=read();
		for(R int i=1; i<=k; ++i) a[i]=read();
		sort(a+1,a+k+1,cmp); bz=0; ans=0; cnt=0;
		
		for(R int i=1; i<=k; ++i)
		{
			if(a[i]/n>1) ans+=a[i]/n, ++cnt;
			if(ans>=m) {bz+=(cnt<<1<=m); break;}
		}
			
		ans=0; cnt=0;
			
		for(R int i=1; i<=k; ++i)
		{
			if(a[i]/m>1) ans+=a[i]/m, ++cnt;
			if(ans>=n) {bz+=(cnt<<1<=n); break;}
		}
		
		printf(bz?"Yes":"No"); endl;
	}
	
    return 0;
}
```

---

