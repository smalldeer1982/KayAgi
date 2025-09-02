# [IOI 1994] 数字三角形 Number Triangles

## 题目描述

观察下面的数字金字塔。


写一个程序来查找从最高点到底部任意处结束的路径，使路径经过数字的和最大。每一步可以走到左下方的点也可以到达右下方的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/95pzs0ne.png)

在上面的样例中，从 $7 \to 3 \to 8 \to 7 \to 5$ 的路径产生了最大权值。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le r \le 1000$，所有输入在 $[0,100]$ 范围内。

题目翻译来自NOCOW。

USACO Training Section 1.5

IOI1994 Day1T1

## 样例 #1

### 输入

```
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5 
```

### 输出

```
30
```

# 题解

## 作者：linlin1024 (赞：528)

  分析题干，发现从上面往下一步步走很麻烦，直接搜索肯定超时。所以，**逆向求解**。

  看样例分析：
  
            7 
          3   8 
    	8   1   0 
      2   7   4   4 
    4   5   2   6   5


   若从倒数第二排的‘2’开始走，只有2个选择，往左下方和右下方。
   
   往左下方是‘4’，得到的最终值为6，往右下方是‘5’，得到的最终值是7.这时当然选择右下方。
   
   我们就将‘2’改写成2+5=7。 再次考虑倒数第二排的7，

   同理，应选择左下，得到最终值是12。还是将‘7’改写成5+7=12。 
   
   依次类推则倒数第二排变为： 
  
    7 12 10 10 
  
   原数字三角形变为： 
    
            7 
          3   8 
    	8   1   0 
      7   12  10  10 
    4   5    2    6   5

  
   这时再考虑第三行第一个。有两种选择：左下和右下。
   
   假设走左下方，由于这时左下的值已经是从**左下开始走到底的最优值**，我们不需要在选择下一步怎么走，直接加上左下的值即可。 
    
   同理，走右下时，直接加上右下的值即可。因为此时**右下的值已经是从右下走到底的最优值**，不需要选择了。 
    
   再比较走两条路的值，右边的值更大，选择右边的值。则第三行的第一个值更新为8+12=20。 
   
   以此类推，得到下面的数字三角形： 
   
            7 
          3   8 
    	20  13  10 
      7   12  10  10 
    4   5    2    6   5
    
   同理，更新第二排，有： 
        
               7 
            23   21 
         20   13   10 
       7   12   10  10 
    4    5    2    6    5 
    
   最后一个了，有： 
    
               30 
            23   21 
         20   13   10 
       7   12   10  10 
    4    5    2    6    5 
    
   起点的值保存了从起点到终点的最优值，也就是答案。详见代码：

    include<iostream> 
	include<cstdio> 
	include<cmath> 
	using namespace std;  
	int n;  
	int a[1000][1000];  
	int main()  
	{       
 		scanf("%d",&n);  
 		for(int i=0;i<n;i++)  
 		for(int j=0;j<=i;j++)  
 		scanf("%d",&a[i][j]);//以上输入  
 		for(int i=n-2;i>=0;i--)   
 		{  
     		for(int j=0;j<=i;j++)//for循环按顺序扫描除最后一排前的所有数  
  			a[i][j]+=max(a[i+1][j],a[i+1][j+1]); 
            //从左下，右下中选取大的加到现在的位置上 
        } 
        cout<<a[0][0]<<endl; 
        return 0; 
     }

---

## 作者：Mine_King (赞：206)

AC的第一道DP题，记录一下（虽然离AC那天已经过去很久了……）  
# 首先申明：当时我是不会DP的。
当时我记搜写得还是不错的，可以说最擅长的就是记搜了。这道题最开始也是用记搜做。不难看出来，递归边界是$x==n$，递归式就是$f_{i,j}=a_{i,j}+max{sjx(i-1,j),sjx(i-1,j-1)}$//sjx是递归函数名，于是乎就有了下面这份代码：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,a[1005][1005],f[1005][1005];
inline int dfs(int x,int y)
{
	if(x==n) return a[x][y];
	if(f[x][y]) return f[x][y];
	return f[x][y]=max(dfs(x+1,y),dfs(x+1,y+1))+a[x][y];
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	 for(register int j=1;j<=i;j++) scanf("%d",&a[i][j]);
	printf("%d",dfs(1,1));
	return 0;
}
```
[然鹅……](https://www.luogu.org/record/21776814)  
于是又进行各种卡常，但任然逃不出TLE的手掌。  
后来我想，学记搜的时候大家都知道：`记搜/DP=递归/递推`而递归和递推的方向是相反的。于是，我就想到：$i$从$n$开始，然后往上一步步递推，递推式还是一样。再对其加以实践，得到了这份代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1005][1005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=i;j++) cin>>a[i][j];
	for(int i=n-1;i>=1;i--)
	 for(int j=1;j<=i;j++) a[i][j]+=max(a[i+1][j],a[i+1][j+1]);
	cout<<a[1][1];
	return 0;
}
```
[结果](https://www.luogu.org/record/22004257)也不出我所料。

如果这篇题解对您有帮助，或者您觉得这篇题解写得不错，请您帮我点个赞，我的[博客](https://www.luogu.org/blog/yhdhg1395754790/)里也有一些不错的东西哦！

---

## 作者：zengqinyi (赞：117)

楼下几位大佬貌似都用的是从下往上推的，

这里讲一下从上往下推的做法。

步骤：

（1）读入；

（2）a[i][j]代表从上往下到达i行j列这个点所能达到的和的最大值，

从上往下到达（i，j）这个点所能达到的和的最大值，即为其上方和左上方两个数中大的那个加上它本身的值。

```cpp
a[i][j]+=max(a[i-1][j-1],a[i-1][j]);//本题最重要的步骤 
```
 ![](https://cdn.luogu.com.cn/upload/pic/7464.png) 

（3）最后在最底下一层中找出最大的值输出就可以了。


以下为代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;
#define rint register int
inline void read(int &x)//读入优化 
{
    x=0;int w=1;char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')w=-1,ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
    x=x*w;
}
const int maxn=1000+10;
int n,a[maxn][maxn],ans; 
int main()
{
    read(n);
    for(rint i=1;i<=n;i++)
    {
        for(rint j=1;j<=i;j++)
        {
            read(a[i][j]);
            a[i][j]+=max(a[i-1][j-1],a[i-1][j]);//本题最重要的步骤 
            //a[i][j]代表从上往下到达i行j列这个点所能达到的和的最大值 
            ans=max(ans,a[i][j]);//在所有答案中找最大的（与在最底下一层找最大值是一样的）
        }
    }//边读入边计算，随手优化一下常数（其实只是懒得打for循环） 
    cout<<ans<<endl;
    return 0; 
} 
```

---

## 作者：iwprc (赞：110)

看到楼下的各位都用了二维的数组，那么我就来说说怎么用一维数组做吧。算法的思路我就不再讲了，下面说一下如何实现。

首先肯定是边读边做，第一层循环i从n到1，第二层循环j从i到n（为了每次都能取到上次的值）,每次读入一个变量p，

状态转移方程：a[j]=max{a[j],a[j+1]}+p（a[j]表示走到第i层第j个时的最大值）。最后输出a数组的最大值即可。

下面我来用测试数据模拟一下](注意：要开1002的数组，不然会越界)：

a[1] a[2] a[3] a[4] a[5] a[6]

初始化：  0    0     0     0     0    0

第一次：  0    0     0     0     7    0

第二次：  0    0     0   10    15   0

第三次：  0    0   18   16    15   0

第四次：  0   20  25   20    19   0

第五次： 24  30  27   26    24   0

代码（c/c++）：

```cpp
#include<cstdio>
int n,a[1002],i,j,ans,p;
int max(int &x,int &y){return x>y?x:y;}
int main(){
    scanf("%d",&n);
        for(i=n;i;i--)
                for(j=i;j<=n;j++)
                        scanf("%d",&p),a[j]=max(a[j],a[j+1])+p;
        for(i=1;i<=n;i++)
        ans=max(ans,a[i]);
        printf("%d",ans);
        return 0;
}
```

---

## 作者：CeLaMbDa (赞：63)

这道题完完全全被写复杂了
我使用递推来做, 从上向下推
状态转移方程: $$dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + map[i][j];$$
其中, $dp$是用来存储状态的, $map$是用来存放对应数字的  
在递推过程中, 我没有对$i == 1, j == 1$这种特殊情况进行考虑, 因为$i - 1 == 0, j - 1 == 0$, 而$dp[0][0]$默认初始化为$0$, 所以取$max$的结果绝对为$0$, 也就使$dp[1][1] = map[1][1]$  
AC记录: https://www.luogu.org/record/show?rid=14955982 
```cpp
#include<stdio.h>
#include<iostream>
using namespace std;

int main(int argc, char** args) {
	int r = 0, map[1005][1005]; //r是层数, map用来存放对应的数字
	scanf("%d", &r);
	for(int i = 1;i <= r;i++) {
		for(int j = 1;j <= i;j++) {
			scanf("%d", &map[i][j]);
		}
	}
	int dp[1005][1005] = {0}, ans = 0; //dp用来存放状态, ans用来存放答案
	for(int i = 1;i <= r;i++) {
		for(int j = 1;j <= i;j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + map[i][j];
			if(dp[i][j] > ans) { //假如取到的数字和大于原先取到的
				ans = dp[i][j];
			}
		}
	}
	printf("%d", ans);
}
```

---

## 作者：_Arahc_ (赞：42)

### 听说这是经典dp

#### 于是乎我用了~~贪心~~ 记忆搜索

在贴代码之前还是讲一讲吧。

#### - dp、分治、递归、递推、搜索 的关系
  
  很简单，~~没有关系~~ dp 是递推，是搜索的改版，是递归的进化体，是（在死亡的边缘大鹏展翅）分治的体现。
  
#### - ~~详解~~  水题解 数字三角形

首先排除贪心。

为什么？

看一眼样例吧，的确木有贪心策略。

但是，我们可以使用搜索愉快地玩耍。

那么具体怎么搜索呢？~~（好问题，我也不知道）~~

 ```cpp
#include<bits/stdc++.h>
using namespace std;
int r,a[1010][1010],i,j,ans;
void dfs(int h,int l,int s){
	if(h==r){
		ans=max(ans,s);
        return;
    }
    dfs(h+1,l,s+a[h][l]);
    dfs(h+1,l+1,s+a[h][l]);
}
int main(){
	memset(dp,-1,sizeof(dp));
	cin>>r;
	for(i=0;i<r;i++) for(j=0;j<=i;j++) cin>>a[i][j];
	dfs(0,0,0);
	return 0;
}
```
这就是最水的深搜（爆搜），不给注释了

不用试了，我交过，TLE*4。

------------

## 神奇的记忆化

这也很简单。首先记忆化一定满足：

- 函数返回值仅与其参数有关
- 相同参数下的返回值相同
- 以返回值传递结果
- ~~有一个记忆数组（滑稽）~~

辣么，我们的答案就会要以返回值传递。

具体的思路也很简单，只要 ~~洗洗睡吧其实要改很多~~ 调整一下思路，你就会发现：

#### 答案居然是 max(左边路的最大分数,右边路的最大分数)+自己的数

如果你还要问为什么，我也会 ~~严肃~~ 地回答你：

这里的左边路、右边路不是指一直向左走向右走，是本次左走之后所有的可以走的路（右边也一样）。

 _所以这也是显而易见的_ 

所以就会很简单的开始你的记忆化。

实际上三个参数的记忆化很烦的（动不动爆空间），但是，因为最终答案是以返回值传递的，所以最初爆搜代码的参数 s 就可以丢掉了。

 ```cpp
#include<bits/stdc++.h>
using namespace std;
int r,a[1010][1010],i,j,dp[1010][1010];
/*
 * dp是记忆数组。
 *
 * h和l表示行、列
 */
int dfs(int h,int l){
	if(dp[h][l]>-1) return dp[h][l];
    // 如果记忆过就直接返回
	if(h==r) dp[h][l]=a[h][l];
    // 如果搜到底层就返回数字
	else dp[h][l]=max(dfs(h+1,l),dfs(h+1,l+1))+a[h][l];
    // 伪状态转移方程
	return dp[h][l];
    //快乐结束
}
int main(){
	memset(dp,-1,sizeof(dp));//初始化，便于判断
	cin>>r;
	for(i=0;i<r;i++) for(j=0;j<=i;j++) cin>>a[i][j];
    //输入完成
	cout<<dfs(0,0);
	return 0;
    //标准结局（此结局非彼结局）
}
/*
 * 题目数据不是很大，于是乎木有输入输出优化
 *
 * 码风不好我也没办法 QAQ
 */
```
辣么这道题就可以AC了，所以我也不写 dp 代码惹 ~~其实是我不会dp~~

最后贴一张图，手动去除背景水印，所以比较亮（请佩戴墨镜）

![](https://s2.ax1x.com/2019/08/20/mJNbgH.png)

#### 这是一个算法区分图，里面的高级名词可以手动百度~

-------------

管理求过，第二次发题解（第一次发的题解误删了QAQ）

---

## 作者：hilsinleri (赞：41)

这一道题是很多教材上的dp入门提，思想是就是裸的dp。

设f[i][j]表示从(1,1)到(i,j)的最大和，则f[i][j]=max(f[i-1][j],f[i-1][j-1])+a[i][j]  因为(i,j)这个点只能从(i-1,j)和(i-1,j-1)两个点走来，所以取他们两个的最大值+这一个点上的数。

其实这一道题的dp数组f可以优化成O(n)，不过意义不大：第一反正不会超内存，第二a数组已经必须是二维了。其实a数组也可以优化为一维，但反正不会超内存，就不管了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[1001][1001],n,f[1001],ans;

int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=i;++j)
            scanf("%d",&a[i][j]);
    f[1]=a[1][1];
    for(register int i=2;i<=n;++i)
        for(register int j=i;j>=1;--j)//因为把f做成了一维，所以第二重要逆序来推。
            f[j]=max(f[j],f[j-1])+a[i][j];//f[j]其实是f[i][j]和f[i-1][j]的双重化身，但由于第一维只对i的下一次循环有影响，所以可以一维，优化思想类似于背包问题
    for(register int i=1;i<=n;++i)
        if(f[i]>ans)ans=f[i];
    printf("%d",ans);
    return 0;
}
```

---

## 作者：MuelsyseU (赞：31)

## 1. 前言

状态压缩典型题。（其实课上学过DP就会发现这道题多么典型）

由于众位dalao已花式给出了许多解法，因此本文主要讲空间复杂度的压缩。

这道题本身不太需要压缩空间，但是为了精益求精，并且自己也锻炼一下这种思维，就尝试了一下。其实是十分轻松的。

（关于2019-10-31更新： 后来发现第4部分漏讲了重要的循环方向修改）

_~~绝对又是一篇水题解……诸位dalao请轻喷~~_

## 2. 关于基本思想

_简单讲讲动规的具体实现，dalao可跳过_ 
 
可以看到，贪心是不可取的。例如根据数据，用贪心法求得 7-8-1-7-5 总和为28，但实际上存在 7-3-8-7-5 总和为30。
 
其实容易理解，即使某次决策选择的方向小于另一方向的数字，但其后可能连着一条总和更大的路径，这并不能说明该方向“不如”另一方向。
 
当然，搜索是一个好的算法，但是每个值在数据略大时会经过大量重复计算，因此增加简单的记忆化，100分AC是可以做到的。

------------

——然而本文是讲动态规划的……

首先考虑动态规划的先决条件——无后效性与最优化原理。

无后效性容易看到——任何一次选择都不会影响之前的路径。

最优化原理的话，考虑题中“每一步可以走到左下方的点也可以到达右下方的点”，换一个角度来说就是“每一个点可以由左上方的点也可以由右上方的点走到”。

那么，只要得知“由起点走到左上方点的最大和”与“由起点走到右上方点的最大和”中的最大值，就能得知“由起点走到左上方点的最大和”。

实际上，已经能看出这道题“裸”动规的影子了。

------------

根据上述内容，不难想到状态转移方程了——左上角与右上角中路径最大值加上该点本身的值。

设 v\[i,j\] 为点 (i,j) 上的值，f\[i,j\] 表示由 (1,1) 到 (i,j) 的路径最大总和，则 f\[i,j\]=Max{f\[i-1,j-1\],f\[i-1,j\]}+v\[i,j\]。此处注意“左上角点”对应的是点 (i-1,j-1)，右上角对应的是点 (i-1,j)。

边界条件更加容易想到，是 f\[i\]\[0\]=f\[0\]\[j\]=0 (0<=i,j<=n)。

最后还需注意一点。如果浅学过DP可能下意识输出 f\[n\]\[n\]**（众：除了你自己没人会这么做）**，但根据题目中“到底部任意处结束”可以看出，总和最大的路径可能终结于 (n,1) 到 (n,n) 的任意一点，最后还需要再从中寻找最大的 f\[n,j\]。

------------

整理思路，首先二重循环输入三角形存储于 a\[\]\[\] 中，再设一 f\[\]\[\] 用二重循环求解后，从 f\[n\]\[1\] 至 f\[n\]\[n\] 中找到最大值输出。

参考代码如下：

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

int a[1010][1010],f[1010][1010];
int main(){
	int n,s=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			f[i][j]=max(f[i-1][j-1],f[i-1][j])+a[i][j];
	for(int j=1;j<=n;j++) s=max(s,f[n][j]);
	cout<<s;
	return 0;
} 
```

## 3. 基本压缩

十分容易理解的部分压缩。

1. 由于对于每个阶段，唯一使用的数据是 a\[i\]\[j\] 而不使用其后输入的数据，则可以将两个二重循环并为一个，即一边输入 a\[i\]\[j\] 一边计算 f\[i\]\[j\]。

2. 当两个循环并为一个时，可以看到每次都是输入 a\[i\]\[j\] 后使用 a\[i\]\[j\]，其后不再使用，因此可将整个 a\[\]\[\] 变为一个临时变量 x，每次输入 x 再使用 x 即可。

参考代码如下：

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

int x,f[1010][1010];
int main(){
	int n,s=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++){
			cin>>x;
			f[i][j]=max(f[i-1][j-1],f[i-1][j])+x;
		}
	for(int j=1;j<=n;j++) s=max(s,f[n][j]);
	cout<<s;
	return 0;
} 
```

## 4. f数组压缩

动规的经典压缩方式（f压缩到一维），且本题状态转移极其简单，因此十分容易实现。

为什么说简单呢？因为 f\[i\]\[\] 仅由 f\[i-1\]\[\] 转移得到，其中没有出现 f\[i\]\[\] 和 f\[i-1\]\[\] 交替使用的现象，比如以下循环的情况：

```cpp
for(int i=1;i<=n;i++){
	g[i]=g[i-1];
	if(f[i-1]/v[i]>g[i])
   		g[i]=f[i-1]/v[i];
    
	f[i]=f[i-1];
	if(g[i-1]*v[i]>f[i])
   		f[i]=g[i-1]*v[i];
}
```

可以发现以上循环中 f 和 g 两数组存在上述的交替现象，不能直接压缩（其实进行一些转化也可压缩）。

言归正传。由上述内容可以看出，在计算点(i,j)时，仅需使用 f\[i-1\]\[\] 的数据，其前的值可以舍弃——最终可直接舍弃 f\[n\]\[\] 之前的所有值。

这样看来，不妨直接使用方程 f\[j\]=max(f\[j-1\],f\[j\])+x！

仔细观察方程，可发现每次 i 循环都更新了 f\[\] 中的值，这样，在执行完第 i-1 层循环后，f 数组就保存了第 i-1 层的所有数据，其后第 i 层循环，实际上等同于使用 max(f\[i-1\]\[j-1\],f\[i-1\]\[j\]) 来更新 f\[i\]\[j\]。

这种办法的妙处在于，每次更新完 f 数组，f 数组所表示的层数就不同了，但仍能保证状态转移的正确（其实容易想到一维的滚动数组）。最终，就能求出第 n 行的最大路径值，将最优化原理发挥得淋漓尽致 ~~（众：又开始自恋了）~~。可能稍有些难理解，但认真思考就能明白其中的道理了。

最后要注意一点，观察 f\[j\]=max(f\[j-1\],f\[j\])+x，可发现每个 f\[j\] 被 f\[j+1\] 所依赖，因此如果仍设 j in 1..i 将引发其后的数据不能正确调用到 f\[i-1\]\[j-1\] 的问题（调用到的将是新计算的 f\[i\]\[j-1\] ）。因此内层循环应当反向，即改为 j in i ..1，这样就不会引发覆盖的问题了。

整理思路，即是：将 f 数组变为一维，所有类似 f\[i\]\[j\] 形式的部分改为 f\[j\] 形式。但由于是二维数组需考虑同组间的冲突，将内层循环的 j in 1..i 改为 j in i ..1。

参考代码如下：

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

int x,f[1010];
int main(){
	int n,s=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=i;j>=1;j--){
			cin>>x;
			f[j]=max(f[j-1],f[j])+x;
		}
	for(int j=1;j<=n;j++) s=max(s,f[j]);
	cout<<s;
	return 0;
} 
```

## 5. 总结

整体而言，这篇文章简单地剖析了空间优化的过程，与其说是题解，更像是解题报告，或者说一种心路历程。

主要重点的部分也就是第4部分，其实并不太清晰，难以过于明晰地表述，但是我相信多思考基本上是可以理解的。就好像DP本身，初学01背包也容易一头雾水的……

最后，还是那句话，希望众dalao轻喷，也希望文章至少能帮到一些人。

谢谢。

---

## 作者：EternalAlexander (赞：21)

纪念一下第一次刷到最优解。（虽然加了O2优化）

AC的思路其他题解已经说了很多，不必再重复了。翻一下评测记录，发现很多写出了标算但是却跑到1000+ms的，这确实很有优化的必要。在这里，浅谈一下这题如何优化。


这里解释一下。我刷到12ms/1.71MB，第二名后，看了下第一名8

ms的程序。然后发现如下代码：

```cpp
    if(n==1000){
            printf("75265");
            return 0;
        } 
```
这是明显的面向数据编程啊！
为了刷到最优解，为了不使面向数据编程的程序成为最优解，我毅然决然地把上述代码复制了过来。

然后就0ms过了。

总之还是不要干这种事啦，下面的题解以及优化方案中也不会提到这种东西。


首先，这是一道dp入门题。如果你不会dp，直接搜索就是55分，时间超限+爆栈。

等到老师跟你讲完dp后，一般教的解法都是两个二维数组然后dp，大概都是这样的

```cpp
    for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                scanf("%d", &map[i-1][j]);
            }
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                dp[i+1][j]=max(dp[i+1][j], map[i+1][j]+dp[i][j]);
                dp[i+1][j+1]=max(dp[i+1][j+1], map[i+1][j+1]+dp[i][j]);
                if (i==n-1) MAX=max(MAX,dp[i][j]);
            }
        }
```
然后写的好点就是40ms/9MB
1，空间上可以优化。

一般老师都会讲，dp这个数组可以开到一维，然后滚动覆盖。

这样的话空间减少到5MB

2，时间优化。

仔细观察发现，其实可以把两个for j的循环并到同一个for i的循环中。首先扫过去一遍读入，然后反向扫一遍计算。

这样的话相当于边读边做。

3，空间再优化

一般人的空间优化到5MB基本就适可而止了。但其实，经过了上面的时间优化后发现，其实读入三角形的那个数组也可以开成一维的。

经过1，2，3三重优化后核心代码大概就成了这样

```cpp
    for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                map[j]=read();
            }
            for (int j = i; j >=0; --j)
            {
                dp[j]=max(dp[j],dp[j-1])+map[j];
                if (i==n-1) MAX=max(MAX,dp[j]);
            }
        }
```
4，速读
观察可以发现，本题的数据输入量很大，大到与时间复杂度同级。很多非常慢的程序都是因为用的cin和cout。

而这时，如果用上快读，就可以加速很多。


```cpp
    int read() {//读入优化
      int x = 0, f = 1;
      char ch = getchar();
      while (ch < '0' || ch > '9') {
        if (ch == '-')
          f = -1;
        ch = getchar();
      }
      while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
      }
      return x * f;
    }
```
最后，总结一下这道题的优化策略。
1.观察数组是否可以滚动覆盖，如果可以，用滚动数组可以减少很多空间开销。

2.能在一个循环中解决的事就在同一个循环中解决。

3.输入量大时果断用快读，千万别用cin和cout。

4.能够边读边做就边读边做

对于某些卡常的题，这些方法也许会起到一些作用。希望能帮到大家。

代码
    
        
```cpp
    #include <cstdio>
    #include <algorithm>
    using namespace std;
    int dp[1001]={-1};
    int map[1001];
    int read() {//读入优化
      int x = 0, f = 1;
      char ch = getchar();
      while (ch < '0' || ch > '9') {
        if (ch == '-')
          f = -1;
        ch = getchar();
      }
      while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
      }
      return x * f;
    }
    int main()
    {
        int MAX = 0;
        int n; 
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                map[j]=read();
                //dp[0]=map[0][0];
            }
            for (int j = i; j >=0; --j)
            {
                dp[j]=max(dp[j],dp[j-1])+map[j];
                if (i==n-1) MAX=max(MAX,dp[j]);
            }
        }
        printf("%d", MAX);
}
```

---

## 作者：劉子颺 (赞：11)

不是开玩笑

这是我连费用流的时候想出来

这可以用最大费用最大流做啊

把三角形中每个位置看做一个点i，建立附加源S汇T。

1、从S向梯形顶层每个i连一条容量为1，费用为0的有向边。

2、从梯形底层每个i向T连一条容量为无穷大，费用为i的权值的有向边。

3、对于每个点i和下面的两个点j，分别连一条从i到j容量为无穷大，费用为点i权值的有向边。

求最大费用最大流，费用流值就是结果。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const int INF=0x3f3f3f3f; 
struct Front_star{
    int u,v,w,c,nxt;
}e[10000];
int cnt=1;
int first[10000]={0};
struct Node{
    int c,num;
}f[51][51];
int n,m;
int S=0;
int T=2501;
void addedge(int u,int v,int c,int w){
    cnt++;
    e[cnt].u=u;
    e[cnt].v=v;
    e[cnt].w=w;
    e[cnt].c=c;
    e[cnt].nxt=first[u];
    first[u]=cnt;
}
void add(int u,int v,int c,int w){
    addedge(u,v,c,w);
    addedge(v,u,-c,0);
}
int dis[10001]={0};
int pre[10001]={0};
int SPFA(){
    int inqueue[10001]={0};
    for(int i=S;i<=T;i++){
        dis[i]=-INF;
    }
    dis[S]=0;
    queue<int> q;
    q.push(S);
    while(!q.empty()){
        int x=q.front();
//        cout<<x<<" "<<endl;
        q.pop();
        inqueue[x]=0;
        for(int i=first[x];i;i=e[i].nxt){
            int v=e[i].v;
//            cout<<e[i].c;
            if(dis[v]<dis[x]+e[i].c&&e[i].w){
                dis[v]=dis[x]+e[i].c;
                pre[v]=i;
                if(!inqueue[v]){
                    q.push(v);
                    inqueue[v]=1;
                }
            }
        }
    }
//    for(int i=S;i<=20;i++)
//        cout<<dis[i]<<" ";
    return dis[T]!=-INF;
}
void MCMF(){
    int ans=0;
    while(SPFA()){
//        cout<<"hello world"<<endl;
        int s=INF;
        for(int i=pre[T];i;i=pre[e[i^1].v]){
            s=min(s,e[i].w);
        }
        for(int i=pre[T];i;i=pre[e[i^1].v]){
            e[i].w-=s;
            e[i^1].w+=s;
        }
        ans+=s*dis[T];
//        cout<<s*dis[T]<<" "<<endl;
    }
    cout<<"max="<<ans<<endl;
}
void solvec(){
//    init();
    int dm=m;
    for(int i=1;i<=m;i++){
        add(S,f[1][i].num,0,1);
    }
    for(int i=1;i<=n-1;i++){
        for(int j=1;j<=dm;j++){
            add(f[i][j].num,f[i+1][j+1].num,f[i][j].c,INF);
            add(f[i][j].num,f[i+1][j].num,f[i][j].c,INF);
        }
        dm++;
    }
//    cout<<dm<<endl;
    for(int i=1;i<=dm;i++){
        add(f[n][i].num,T,f[n][i].c,INF);
    }
    MCMF();
}
int main(){
    int tot=1;
    m=1;
    scanf("%d",&n);
    int dm=m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=dm;j++){
            int w;
            scanf("%d",&w);
            f[i][j].c=w;
            f[i][j].num=tot;
            tot++;
        }
        dm++;
    }
//    cout<<dm<<endl;
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=n+1;j++){
//            cout<<f[i][j].num<<" ";
//        }
//        cout<<endl;
//    }
//    solvea();
//    solveb();
    solvec();
}
```

---

## 作者：智子·起源 (赞：7)

## 这道题有史以来最短的c++代码！！
算了，还是发挥一下题解的作用吧……

讲一下思路：
### 主要思路当然是DP
这道题从下到上DP会比较好想。

从下到上，对于每一个地方，只能走它的下面和右下面。

### 所以，对于每个地方我们只要看一下走下面哪条路和会多一些，然后从最底下推回起点即可。

### 重点来了！超短的代码！！
```cpp
#include<iostream>
using namespace std;
int n,a[1001][1001],f[1002][1002];
main(){cin>>n;
  for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)cin>>a[i][j];
  for(int i=n;i>0;i--)
    for(int j=1;j<=i;j++)
      if(f[i+1][j]>f[i+1][j+1])f[i][j]=f[i+1][j]+a[i][j];
        else f[i][j]=f[i+1][j+1]+a[i][j];
  cout<<f[1][1];}
```
开心！ \\(^o^)/   ●▽●

---

## 作者：天命之路 (赞：5)

这个数字三角形，算是一道老题了，应该有很多奆佬都看见过。鄙人不才，在这里给大家介绍两种方法：

### **DP and 深搜！**

先说深搜，这一部分是给蒟蒻看的，奆佬直接看下面的DP，为何？因为这道题目，行列数最高达到了1000，按照深搜的做法，大概率超时。不信？本人以身试险，最后凄凄惨惨的，拿个55分……


虽然下场惨了点，但只要数据范围少个零，还是可以解决的，思想可以学习。话不多说，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001][1001],n;
int solve(int x,int y)
{
	if(x==n) return a[x][y];             //1
	int u=solve(x+1,y),v=solve(x+1,y+1);
	return max(u,v)+a[x][y];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++) cin>>a[i][j];   //2
	
	cout<<solve(1,1);
	return 0;
}
```

1:这里是深搜函数，递归的终止条件是：如果坐标在最后一行，则直接返回这个坐标的数（下面已经没有数了）。递归方法：在左下方的和右下方的两个和中取最大的，再加上该坐标的数。

2:注意第二层循环，条件是j<=i,因为输入是三角形的，第i行输入i个。



DP部分：
众所周知，虽然DP的空间，时间不像深搜那样庞大，但是二维数组的空间，两层循环的时间，也有可能超，不过这题还好，空间大约是1001^2 *2 *4B（两个int二维数组），时间也不会超。
于是我放心的叫了代码，果不其然，AK……
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001][1001],n,f[1001][1001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++) cin>>a[i][j];
	
	for(int j=1;j<=n;j++) f[n][j]=a[n][j];    //1
	for(int i=n-1;i>=1;i--)
	for(int j=i;j>=1;j--)    //2
	{                                                            
		f[i][j]=max(f[i+1][j],f[i+1][j+1])+a[i][j];
	}
	
	cout<<f[1][1];
	return 0;
}
```
1:初始化。在最底下一列，最大和就是这个数字自己，因为它下面已经没有数了。

2：动态规划核心部分。从右下至左上，不然得到的答案全是零，因为下面还没初始化。max函数里的是左下的最大和以及右下的最大和，之后再加上这个位置的数。

综上，推荐大家还是用动态规划，毕竟深搜数据一超，什么RE,TLE,MLE……错误一大堆，dp就两个二维数组，不占太大地方。最后祝大家满屏AC，刷通动归！！




---

## 作者：WOWHandsome (赞：5)

**虽然此题已经有50篇题解，但是我还是非(xian)常(de)耐(dan)心(teng)的来写一篇一题多解，并且利用滚动数组，优化到了时间复杂度$O(n^2)$，空间复杂度$O(n)$。**

--------------

## 获得更好的阅读体验？前往 [My Blog](http://baoyihan.cnblogs.com/p/luogu-p1216.html)

--------------

## $Part$ $1$ 分治

我们要求这个数字三角形的路径最值，而题目规定，每一步可以走到左下方的点也可以到达右下方的点，也就是说有两条路径可以选择。显然，可以将原问题分解成两个形式相同，规模更小的子问题，分治的feel就出现了。

很明显，这里的原问题是求从最高点**，也就是 $(1,1)$ 的位置**到底部任意处结束的路径，使路径经过数字的和最大。

那么根据“每一步走左下方的点或右下方的点”，分解出两个子问题

子问题1：求从 $(i+1, j)$到底部任意处结束的路径，使路径经过数字的和最大。

子问题2：求从 $(i+1, j+1)$到底部任意处结束的路径，使路径经过数字的和最大。

**怎么合并？很简单，根据题目描述需要求路径和最大，那么我们就将两个子问题的解求一个最值，再加上他的本身 $(i, j)$ ，就得到了问题的解。**

**进一步，发现当 $i=n$ 的时候，没有两条路径可供选择，直接返回 $a(i,j)$ 的值即可。**

根据以上，写出分治的代码

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int a[101][101];
int n; 
int MaxSum(int i, int j) {
    if (i == n) return a[i][j]; //i == n，直接返回 a(i,j)的值
    int x = MaxSum(i+1, j); //递归调用两个子问题
    int y = MaxSum(i+1, j+1);
    return max(x, y) + a[i][j]; //最后合并
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            scanf("%d", &a[i][j]);
    cout << MaxSum(1,1);
    return 0;
}
```

结果如何？**$TLE$(时间超限)**。

分析原因，发现有**大量的重复计算**。

### $Why?$

（自己先思考一下，思维过程很重要哦）

**注意到，这里 $MAXN = 1000$，当此递归函数执行时，重复调用了 $MaxSum(i, j)$。假设调用了$ MaxSum(3, 2)$，则分解出2个子问题，调用了 $MaxSum(4, 2)$ 和 $MaxSum(4, 3)$。画出递归树，模拟递归过程后发现，在此之前，$MaxSum(3, 1)$ 已经调用过 $MaxSum(4, 2)$，也就是说，$MaxSum(4, 2)$被多次调用，导致递归树不断扩大，而 $MaxSum(4, 2)$的解已经被求出。**

**如果你有兴趣，可以加上一个计数数组$tot[][]$，当$MaxSum(i, j)$被调用后，将$tot[i][j]++$，然后输出$tot$数组，你会发现，$tot$数组是一个杨辉三角形！进一步，计算出此三角形的和为 $2^n$，也就是说，这个分治代码的整体时间复杂度为$O(n)$，导致了超时。怎么优化？**

----------

## $Part$ $2$ 优化$→$记忆化搜索

上面提到了优化的思路，很简单，优化的思想有两点：

* 重复

* 不必要

那么借助**“以时间换空间”**的思路，想到了**记忆化**，将$MaxSum(i, j)$的解记录。

开一个数组 $mxsum[i][j]$，记录$MaxSum(i, j)$的解，如没有被求出，就去求解，**注意：不要忘记在求出解后，将解记录下来！！！**

很快通过更改分治的代码，得到记忆化搜索的代码。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int a[1001][1001];
int n;
int mxsum[1001][1001];
int MaxSum(int i, int j) {
    if (mxsum[i][j] != -1) return mxsum[i][j]; //直接求解
    if (i == n) return a[i][j]; //基本情况
    int x = MaxSum(i+1, j);
    int y = MaxSum(i+1, j+1);
    mxsum[i][j] = max(x, y) + a[i][j]; //记录解
    return mxsum[i][j];
}
int main() { 
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            scanf("%d", &a[i][j]), mxsum[i][j] = -1;
            /*不要忘记设置mxsum的初值，-1代表没有被计算*/
    cout << MaxSum(1,1);
    return 0;
}
```

**结果：$AC$。分析该算法时间复杂度，由于每一个结点都只算了一次，所以时间复杂度为$O(n^2)$**

------

## $Part$ $3$ 自底向顶 $DP$

那么问题来了，这$dp$标签被你吃了？

不慌不慌，接下来就上$dp$。

在此之前，先分析一下$dp$的正确性。$dp$需要有两个条件

* 最优子结构性质

* 无后效性

当然作为一道$dp$入门，这两个东东还是比较拗口，你只要记住就行了qwq，以后我们会再细讲。

推出状态转移方程就不说了吧，$f[x][y]=max(f[x+1][y],f[x+1][y+1])+a[x][y]$，因为要$get$最值，之前的几篇题解推状态转移方程都有细讲，这里不再阐述。

那么边界是什么呢？这里是由下至上递推，结合上面的分治代码，边界只能为$a[x]$，也就是最底下一层。

写出超级简短的dp：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
 
int a[1001][1001];
 
int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            scanf("%d", &a[i][j]);
    for (int i = n - 1; i >= 1; i--)
        for (int j = 1; j <= i; j++)
            a[i][j] += max(a[i + 1][j], a[i + 1][j + 1]); //dp
    printf("%d\n", a[1][1]);
    return 0;
}
```

等等，f数组呢？自己想一想吧，这里不需要f数组。直接在$a[i][j]$的值上加上去就可以。自己填表，是不是这样？

分析一下时间复杂度：两个$for$，显然$O(n^2)$，当然，用 `状态一维 + 转移一维 = 二维`也可以推出。

**思考：能不能改变递推方式，从上到下递推呢？自己想一想~**

------------

## $Part$ $4$ 改变递推方式

显然，是可以的。状态转移方程作一些改变即可。具体见注释。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
 
int a[1001][1001];
 
int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            scanf("%d", &a[i][j]);
    for (int i = 2; i <= n; i++) // i从2开始，a[1][1]是边界
        for (int j = 1; j <= i; j++)
            a[i][j] += max(a[i - 1][j], a[i - 1][j - 1]); //从上到下递推
    printf("max=%d\n", *max_element(a[n] + 1, a[n] + n + 1)); //max_element函数，输出最后一行的最大值，返回的是指针
    return 0;
}
```

-----------

## $Part$ $5$ 终极优化

进一步，发现由上到下的递推只需要 a数组的两行数据，第$i$行和第$i-1$行，其他数据用过一次就没有用了。

借助滚动数组的思想，定义两个变量 $pre$ 和 $now$，分别表示 **之前一列 和 当前列，每一轮dp，都交换pre 和 now。即可将空间压缩到 $O(2n)$**。

具体代码实现：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
  
int a[2][1001];
  
int main() {
    int n; scanf("%d", &n);
    int now = 0, pre = 1; // 分别定初值，pre 和 now 的值可交换
    scanf("%d", &a[now][1]); // 一开始先读入第一行，也就是递推的边界，否则无法递推
    for (int i = 2; i <= n; i++) {
        swap(now, pre); int t; //交换pre 和 now 的值，t作输入变量
        for (int j = 1; j <= i; j++) {
            scanf("%d", &t);
            a[now][j] = max(a[pre][j], a[pre][j - 1]) + t;
        }
    }
    printf("%d\n", *max_element(a[now] + 1, a[now] + n + 1)); //最后输出最大值
    return 0;
}
```

至此，极限优化完毕。空间变为一维，评测为$800$kb，时间复杂度依旧是 $O(N^2)$

最后的思考：递推方式从底到顶可以实现空间一维优化吗？

欢迎评论鸭~

## 获得更好的阅读体验？前往 [My Blog](http://baoyihan.cnblogs.com/p/luogu-p1216.html)

---

## 作者：谭之荔 (赞：5)

动态规划
这道题阔以用搜索，递推
递推可以用顺推和逆推
但是！！！一般的搜索会超时，因为一个点的数可能算过很多很多遍，但是根本没有这个必要，所以可以用记忆化搜索！
#### 我下面把三种方法都说一下
首先说一下记忆化搜索，其实个人不是很喜欢用记忆化搜索，因为一不小心就超时，比赛的话，风险不小
#### 记忆化搜索
```
#include<iostream>
#include<cstdio>
using namespace std;
int r,f[1001][1001],a[1001][1001];
void dfs(int x,int y)
{
	if(x==r)//如果到底部，最大即为本身 
	{
		f[x][y]=a[x][y];
		return;
	}
	if(f[x][y]>=0) return;//判断之前是否赋过值 
	dfs(x+1,y);//搜自己左下方（数组中自己正下方） 
	dfs(x+1,y+1);//搜自己右下方（数组中自己右下方）
	f[x][y]=max(f[x+1][y],f[x+1][y+1])+a[x][y];
	//找下方两数的最大并加上自己本身 
}
int main()
{
	
	cin>>r;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=i;j++)
		{
			f[i][j]=-1;//赋初值 
			cin>>a[i][j];
			if(i==r)//底部的初值为本身 
			{
				f[i][j]=a[i][j];
			}
		}
	}
	dfs(1,1);//从最上面的开始 
	cout<<f[1][1];
}
```
接下来是递推，逆推比顺推好理解一些，而且在以后的题里，逆推也是比较多的
#### 逆推
```
#include<iostream>
#include<cstdio>
using namespace std;
int a[1001][1001],f[1001][1001]; 
int main()
{
	int r;
	cin>>r;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin>>a[i][j];
			if(i==r)
			{
				f[i][j]=a[i][j];//如果底部，最大即为本身 
			}
		}
	}
	for(int i=n-1;i>=1;i--)//从下向上 
	{
		for(int j=1;j<=i;j++)
		{
			f[i][j]=max(f[i+1][j],f[i+1][j+1])+a[i][j];
			//找出下方两个的最大并加上自身 
		}
	}
	cout<<f[1][1];
	
}
```
最后是顺推，顺推如果理解不了的话，可以在脑海里把数字三角形反过来然后逆推，理解了更好
#### 顺推
```
#include<iostream>
#include<cstdio>
using namespace std;
int f[1001][1001],a[1001][1001];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin>>a[i][j];
		}
	}
	f[1][1]=a[1][1];//最上面的即为本身 
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			f[i][j]=max(f[i-1][j],f[i-1][j-1])+a[i][j];
			//找出自己上方两个的最大并加上自身 
		}
	}
	int ans=f[n][1];//先假设最大为最后一行第一个数所累积起来的和 
	for(int i=2;i<=n;i++)
	{
		if(f[n][i]>ans)//找出最下方的最大值 
		{
			ans=f[n][i];
		}
	}
	cout<<ans;
	
} 
```
p有不会的一定要问的，攒着对后面的题真的没帮助，其实我还是建议三个都会，这样还是比较保险的吧

---

## 作者：ljh736731592 (赞：3)

题目描述


考虑在下面被显示的数字金字塔。
写一个程序来计算从最高点开始在底部任意处结束的路径经过数字的和的最大。
每一步可以走到左下方的点也可以到达右下方的点。

7

3 8

8 1 0

2 7 4 4

4 5 2 6 5

在上面的样例中,从7 到 3 到 8 到 7 到 5 的路径产生了最大和:30

输入

第一个行包含 R(1<= R<=1000) ,表示行的数目。

后面每行为这个数字金字塔特定行包含的整数。

所有的被供应的整数是非负的且不大于100。

输出

单独的一行包含那个可能得到的最大的和。

样例输入

5

7

3 8

8 1 0

2 7 4 4

4 5 2 6 5

样例输出

30

---

显然dp啊

这一道题是很多教材上的dp入门提，思想是就是裸的dp。

设f[i][j]表示从(1,1)到(i,j)的最大和，则f[i][j]=max(f[i-1][j],f[i-1][j-1])+a[i][j] 因为(i,j)这个点只能从(i-1,j)和(i-1,j-1)两个点走来，所以取他们两个的最大值+这一个点上的数。

其实这一道题的dp数组f可以优化成O(n)，不过意义不大：第一反正不会超内存，第二a数组已经必须是二维了。其实a数组也可以优化为一维，但反正不会超内存，就不管了。


---


```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define l long long
#define N 1000001
using namespace std;
l r,n,i,j,a[1005][1005],k,t,s;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	for(j=1;j<=i;j++)
	cin>>a[i][j];
	for(i=n-1;i>=1;i--)
	for(j=1;j<=i;j++)
	a[i][j]+=max(a[i+1][j],a[i+1][j+1]);
	cout<<a[1][1]<<endl;
	return 0;
}
```








---

## 作者：iYuer (赞：3)

竞赛中很重要的一种思维就是逆向思考。（当然这道题正向思考也能AC，但是多锻炼逆向思维是很不错的。）

d[i][j]表示第i层第j个位置的最大和。

我们就从金字塔的底部加上来的话，答案就是 d[1][1];


▲优化：可把二维数组转化为一维数组， 答案就是d[1]. 详细的看代码。


```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int maxn=1000+10;
int n,d[maxn],data[maxn][maxn];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)    scanf("%d",&data[i][j]);
    for(int i=1;i<=n;i++)    d[i]=data[n][i]; //初始化
    for(int i=n-1;i>=1;i--)
        for(int j=1;j<=i;j++)
            d[j]=max(d[j],max(d[j],d[j+1])+data[i][j]);
    printf("%d\n",d[1]);
    return 0;
}
```

---

## 作者：Ufowoqqqo (赞：3)

以我个人[delete]不太专业的水准来[/delete]判断，此题应该是**贪心**题（至少我是用类似贪心的解法写的）

下面开始分析题目。

既然要求最大和，那么就要每条路都试。也就是——**枚举**？

不对，如果**枚举**的话，1000行数据早就**TLE**了。

是**DP**吗？好像也可以？那么，有没有更简单的做法？

仔细想一想，当走到(i,j)的时候，所能产生的最大和是不是走到左上角和右上角时所产生的最大和中较大的一个数加上a[i,j]？

这样一想，好像就通了。

用b[i,j]储存走到(i,j)时所能产生的最大和，算到最后一行时再求b[n]中的最大值。

另外还要注意一个地方：虽然题目解释中是金字塔形，但是第i行只有i个值而不是i\*2-1个，所以b[i,j]的右上角对应b[i-1,j]而不是b[i-1,j+1]，这个要注意。

参考代码如下：

```delphi

var
 r,i,j:longint;
 ans:longint;
 a,b:array [0..1001,0..1001] of longint;

function max(m,n:lognint):longint;
begin
 if m>n then max:=m else max:=n
end;

begin
 readln(r);
 for i:=1 to r do
 begin
  for j:=1 to i do read(a[i,j]);
  readln
 end;
 for i:=1 to r do
  for j:=1 to i do b[i,j]:=max(b[i-1,j-1],b[i-1,j])+a[i,j];//核心，只要理解好就没问题
 for i:=1 to r do if b[r,i]>ans then ans:=b[r,i];
 write(ans)
end.

```
[color=snow]以上所有内容纯属本人胡言乱语，请勿当真。如需查看题解请看楼下。[/color]


---

## 作者：柠青哟 (赞：2)

记忆化递归做法
```c
#include<iostream>
#include<algorithm>
using namespace std;
int maxlen[1001][1001],n,a[1001][1001];;
int maxsum(int x,int y){
	if(maxlen[x][y]!=-1) return maxlen[x][y];
	if(x==n) maxlen[x][y]=a[x][y];
	else{
		int j=maxsum(x+1,y);
		int k=maxsum(x+1,y+1);
		maxlen[x][y]=max(j,k)+a[x][y];
	}
	return maxlen[x][y];
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			cin>>a[i][j];
			maxlen[i][j]=-1;
		}
	}
	cout<<maxsum(1,1);
}
```
递推做法
```c
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	int n,a[1001][1001],maxsum[1001][1001];
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)
			cin>>a[i][j];
	}
	for(int i=1;i<=n;i++){
		maxsum[n][i]=a[n][i];
	}
	for(int i=n-1;i>=1;i--){
		for(int i=1;j<=i;j++){
			maxsum[i][j]=max(maxsum[i+1][j+1],maxsum[i+1][j])+a[i][j];
		}
	}
	cout<<maxsum[1][1];
} 
```
进一步空间优化，用一维数组maxsum代替二维数组maxsum
```c
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	int n,a[1001][1001],i,j;
	int *maxsum
	cin>>n;
	for(i=1;i<=n;i++){
		for(j=1;j<=i;j++)
			cin>>a[i][j];
	}
	maxsum=a[n];//指针指向第n行 
	for(int i=1;i<=n;i++){
		maxsum[n][i]=a[n][i];
	}
	for(int i=n-1;i>=1;i--){
		for(int i=1;j<=i;j++){
			maxsum[j]=max(maxsum[j+1],maxsum[j])+a[i][j];
		}
	}
	cout<<maxsum[1];
} 
```

```


---

## 作者：简宇卿 (赞：2)

本蒟蒻第一一次发题解各位神犇勿喷……（其实我刚学两个月……
其实吧我觉得这道题事实上就从上往下遍历好了……
废话不多说，上代码QAQ
```c
# include <cstdio>
# include <algorithm>
using namespace std;
int f[1005][1005];
int n,fans;
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= i;j++)
			scanf("%d",&f[i][j]);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= i;j++)
		    f[i][j] += max(f[i - 1][j - 1],f[i - 1][j]);
	for(int i = 1;i <= n;i++)
		fans = max(f[n][i],fans);
	printf("%d",fans); 
	return 0;
} 
```

---

## 作者：cenbinbin (赞：2)

此题若用枚举，爆爆爆。。。

所以应用dp思想，从最底层向上做，对于每一个都是最优解，即为到达自己的两个点中的大值取。

======================================================================

```cpp
var
  f,a:array[0..1001,0..1001] of longint;
  n,i,j:longint;
function max(x,y:longint):longint;    //比较大小
begin
  if x>y then exit(x) else exit(y);
end;
begin
  readln(n);
  for i:=1 to n do     //读入数据
   begin      
    for j:=1 to i do
    read(a[i,j]);readln;
   end;
  for i:=n downto 1 do        //从后向前做，对于每个点都是最优解。。。
   for j:=1 to i do
    f[i,j]:=a[i,j]+max(f[i+1,j],f[i+1,j+1]);        //取大值选入
  writeln(f[1,1]);     //输出结果
end.

```

---

## 作者：Kirito_Sans_桐衫 (赞：2)

/\*
此题为动态规划

动态规划是一向让我很头疼的题目，头疼头疼再头疼

不过此题属于比较简单的类型，所以呵呵

思路：此题有两种解法，一种是从上往下递推，不难发现状态转移方程为

##​dp[i][j]=a[i][j]+max(a[i-1][j],a[i-1][j-1])

然后得到这个三角形每格第i步的最大值（在最底层哦）

但是此解需要处理后多一个循环来表查找最大值，然后输出，时间复杂度为O（n2）

另一种则是从下往上推，在数学上叫做“逆推法”

然后呵呵你懂得，从下往上找，状态转移方程为

##dp[i][j]=a[i][j]+max（a[i+1][j],a[i+1][j+1]）

然后神奇了，最后只要输出dp[1][1]即可，因为三角形最上方的数字正是第n步后取得的最大值

反正逆推法能够省一个循环，那就省吧

废话不多说了，上代码

\*/
```cpp
#include<cstdio>
#include<cstring>
int a[1100][1100];
int f[1100][1100];
int n;
int main()
{
    memset(a,0,sizeof(a));
    memset(f,0,sizeof(f));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        f[n][i]=a[n][i];
    }
    for(int i=n-1;i>=1;i--)
    {
        for(int j=i;j>=1;j--)
        {
            if(f[i+1][j]+a[i][j]>f[i+1][j+1]+a[i][j])
            {
                f[i][j]=a[i][j]+f[i+1][j];
            }
            else
            {
                f[i][j]=a[i][j]+f[i+1][j+1];
            }
        }
    }
    printf("%d",f[1][1]);
    return 0;
}
```

---

## 作者：lby2006 (赞：1)

首先这是一道dp题无疑。

但是……我打了dfs哒 ~~当然TLE了~~

首先是~~55分~~dfs代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1010][1010],ans=-1;
const int SIZE=1<<20;
inline char getch()
{
    static char buf[SIZE],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++;
}//手动getchar
inline int rd()
{
    int s=0,f=1;
    char c=getch();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getch();}
    while(c>='0'&&c<='9') {s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*f;
}//快读不解释
void dfs(int x,int y,int sum)
{
    if(y<0||y>x)return ;
    if(x==n)
    {
        ans=max(sum+a[x][y],ans);
        return ;
    }
    for(int i=0;i<2;i++)dfs(x+1,y+i,sum+a[x][y]);
    return ;
}//标准dfs
int main()
{
    n=rd();
    for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)a[i][j]=rd();
    dfs(1,1,0);
    printf("%d\n",ans);
    return 0;
}
```
但是
我dpAC了哒！
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1010][1010],ans=-1;
int dp[1010][1010];
const int SIZE=1<<20;
inline char getch()
{
    static char buf[SIZE],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++;
}
inline int rd()
{
    int s=0,f=1;
    char c=getch();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getch();}
    while(c>='0'&&c<='9') {s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*f;
}
int main()
{
    n=rd();
    for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)a[i][j]=rd();
    dp[1][1]=a[1][1];
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            if(j==1)dp[i][j]=dp[i-1][j]+a[i][j];//若他在行首，就直接等于它上面的加上这个点的值
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])+a[i][j];//否则等于它左上的点和右上的点的较大值加上它的值
        }
    }
    for(int i=1;i<=n;i++)ans=max(ans,dp[n][i]);//找到最大的
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Violette (赞：1)

这里给大家提供两个我做这道题时的代码。

No.1  学记忆化搜索之前...

我的思路：这道题直接用搜索做不就好了吗？

代码如下：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int r;
int a[1005][1005];
int ans1,ans2;
void dfs(int x,int y){
	ans1+=a[x][y];
	if(x==r) ans2=max(ans1,ans2);//达到边界
	else{
		dfs(x+1,y+1);
		dfs(x+1,y);//左下方和右下方
	}
	ans1-=a[x][y];//还原一下
}
int main(){
	cin>>r;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=i;j++)
			cin>>a[i][j];
	dfs(1,1);//调用dfs
	cout<<ans2;
	return 0;
}
```
在课上兴奋的码出代码，提交结果：[55分](https://www.luogu.org/record/23742189)

发现这种做法必然会出现TLE的情况╮(╯▽╰)╭。

No.2 学完记忆化搜索

其实不必重新码代码，直接在一开始的代码上略加修改就可以了。

因个人水平不高，刚接触c++一年，于是一开始编出了这样的[代码](https://www.luogu.org/paste/328z8s40)

然而只得了89分。。。

这又是为什么捏？————仅仅是个人犯的低级错误，在主函数中输入完毕后，应把数组对应下标赋值为一个负数（例如-1），而不是赋为1（或其他正数），否则就会。。。

最后，终于调试AC

代码：

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int r;
int a[1005][1005];
int t[1005][1005];
int ans1=0,ans2=0;
int dfs(int x,int y){	
	int sum;
	ans1+=a[x][y];
	if(x==r) return a[x][y];
	if(t[x+1][y]==-1) t[x+1][y]=dfs(x+1,y);
	if(t[x+1][y+1]==-1) t[x+1][y+1]=dfs(x+1,y+1);
	sum=a[x][y]+max(t[x+1][y],t[x+1][y+1]);
	return sum;
}
int main(){
	cin>>r;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=i;j++){
			cin>>a[i][j];
			t[i][j]=-1;
		}
	}
	cout<<dfs(1,1);
	return 0;
}
```
这个就不加注释了，思路和前边是一样的_(:з」∠)_

[提交记录](https://www.luogu.org/record/23744301)

---

## 作者：MikeC (赞：1)

这道题其实就是经典的动规。  
很多同学第一眼看到题目想到的就是贪心，  
~~但实际上，贪心连一半的分都拿不到~~  
比如说：  
```cpp
1
3 2
3 3 5
1 1 1 1
```
***~按最顶层为第一层来算***  
按照贪心的思路，从第一层的1走到第二层的3，最终得到的值是1+3+3+1=8;  
而事实上的最大值是从第一层1走到第二层的2再走到第三层的5，最终的值为1+2+5+1=9;  
  
    
 所以基本的思路就是从最n-1层开始，自身的值等于下层两个值中最大的一个加上自身，最终只需要输出第一层的值即可;
   
   上代码：
   ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tu[1001][1001],a[1001][1001];//三角形说白了就是一个二维图
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=i; j++)cin>>tu[i][j];
	}
	for(int i=n; i>=1; i--) { //从n行开始
		for(int j=1; j<=i; j++) { //遍历这一层每一个点
			a[i][j]=tu[i][j]+max(a[i+1][j],a[i+1][j+1]);//记录比较和累加后的值
		}
	}
	printf("%d",a[1][1]);
	return 0;
}
```


---

## 作者：顾月 (赞：1)

### [题目：数字三角形](https://www.luogu.org/problemnew/show/P1216)

~~蒟蒻题解：~~

~~我先来展示一下44分的贪心~~

```cpp
# include <iostream>
using namespace std;
int main()
{
	int i, j, n, ans = 0, flag = 1;
	cin >> n;
	int a[n + 1][n + 1];
	for(i = 1;i <= n;i++)
		for(j = 1;j <= i;j++)
			cin >> a[i][j];
	ans = a[1][1];
	for (i = 2;i <= n;i++)
	{
		if (a[i][flag] > a[i][flag + 1])
			ans = ans + a[i][flag];
		else{
			ans = ans + a[i][flag + 1];
			flag = flag + 1;
		}
	}
	cout << ans;
	return 0;
}
```


贪心的计算是从(1,1)开始(2,2)->(3,2)->(4,2)->(5,2) 

ans = 28， 而正解为30

显然连样例都过不了

#### 直接舍弃掉这种想法

# 我想到有四种想法

## 第一种：暴力枚举
~~（暴力出奇迹）~~

直接分析可得：

当 n = 5，的时候已经有很多种情况了（其实是懒得算）

而行数的范围为 1<= R<=**1000**

#### 直接舍弃+1

## 第二种：自下而上分析

一种非常容易理解的思想
```cpp
# include <cstdio>
# include <cstring>
# include <algorithm>
using namespace std;
int main()
{
    int i, j, r;
    scanf("%d", &r);
    int a[r+1][r+1];
    memset(a, 0, sizeof(a));
    for (i = 1;i <= r;i++)
        for (j = 1;j <= i;j++)
            scanf("%d", &a[i][j]); 
    for (i = r - 1;i >= 1;i--)//从倒数第二排开始循环 
        for (j = 1;j <= i;j++)
            a[i][j] = a[i][j] + max(a[i+1][j],a[i+1][j+1]);//寻找最大值 
    printf("%d", a[1][1]);//输出结果 
    return 0;
}
```

使用了**二维数组**存储数据

使用样例输入~~盲目~~分析

![样例输入](https://s2.ax1x.com/2019/07/14/Z5nTs0.png)
 
 自下而上分析
 
 第一次循环从第四行开始：
 
 **寻找最大值路径，然后记录下这些点加下面两个点中的最大值**

也就是说

第一次循环完毕后， 数组会变成

![第一次循环完毕](https://s2.ax1x.com/2019/07/14/Z5ug61.png)

这个亚子

同理 第二次循环完毕后，数组会变成

![第二次循环完毕](https://s2.ax1x.com/2019/07/14/Z5KZAU.png)

这样

同样的，再两次循环以后

a[1][1]就是正确答案 30了

## 第三种：自上而下分析
再循环之中

**a[i][j] 是表示从a[1][1]开始**

**一直到到达（i，j）时，经过的路径的最大值，**

最后输出最后一行里面最大值就可以了。

根据这样的思路

不难得出这样的代码

```cpp
# include <cstdio>
# include <cstring>
# include <algorithm>
using namespace std;
int main()
{
    int i, j, r;
    scanf("%d", &r);
    int a[r+1][r+1];
    memset(a, 0, sizeof(a));
    for (i = 1;i <= r;i++)
        for (j = 1;j <= i;j++)
            scanf("%d", &a[i][j]); 
    for (i = 2;i <= r;i++)
        for (j = 1;j <= i;j++)
        	a[i][j] = a[i][j] + max(a[i - 1][j], a[i - 1][j - 1]);//寻找经过的路径的最大值
    int maxn = a[r][1];
    for (i = 2; i<= r;i++)
    	maxn = max(maxn, a[r][i]);//在最后一行寻找最大值 
    printf("%d", maxn);
    return 0;
}
```
## 第四种：边读边算 + 使用一维数组

```cpp
# include <cstdio>
# include <algorithm>
# include <cstring> 
using namespace std;
int main()
{
	int n;
    scanf("%d",&n);
	int a[n + 10], i, j,temp;
	memset(a, 0, sizeof(a));
    for(i = n;i >= 1;i--)
    {
	    for(j = i;j <= n;j++)
	    {
            scanf("%d",&temp);
			a[j] = max(a[j],a[j+1])+temp;	    	
    	}    	
	} 
    int ans = a[1];
    for(i = 2;i <= n;i++)
    	ans = max(ans,a[i]);
    printf("%d", ans);
    return 0;
}
```
最终代码：（~~方便抄？~~）

```cpp
# include <cstdio>
# include <cstring> 
using namespace std;
int max(int a,int b)
{
    return a>b?a:b;
}//最大值 
int read() 
{
    int x=0;
    bool f = false;
    char ch;
    do ch=getchar(),f|=(ch=='-');
    while(ch<48||ch>57);
    while(ch>47&&ch<58)
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return f?-x:x;
}//快读 
int main()
{ 
    int i, j;
	int r = read();
    int a[r + 10];
    memset (a, 0, sizeof(a));
    for(i = r - 1;~i;i--)
        for(j = i;j^r;j++)
            a[j] = max(a[j],a[j+1]) + read();//边读边算，参考思路四。 
    int m = a[0];
    for(i = 1;i^r;i++)
        m = max(a[i],m); //比较出最大值。 
    printf("%d",m);
    return 0;
}
```
## 总结：
 思路一      暴力枚举（舍弃） 

**思路二** | **自下而上 寻找最大的路径** 

**思路三** | **自上而下 求从（1,1）到此点的最大距离**  

**思路四** |   **边读边写寻找最大值** 



---

## 作者：S1gMa (赞：1)

这是动态规划·DP的一道经典题
------------

具体做法：1.分析问题的最优解，找出最优解的性质，并刻画其结构特征：问题的最优解：所有走法中最大的权值是多少？最优解的性质和结构特征：只能向正下或者右下走，每走一行的最大权值等于前面一行的最大权值加上这一行的走的两个方向中的最大值2.递归的定义最优值：要找到从0行出发的最优值，就要找到从第1行出发的最优值要找到从1行出发的最优值，就要找到从第2行出发的最优值……………要找到第3行出发的最优值，就要找到从最后一行出发的最优值为什么是这样呢？我们分析一下题目要你求从0行出发的最优值，那么我们就是要找到从第一行出发的最优值，加上第0行到第1行的最优值但是，很重要的一点，我们需要递归求解，要先求解从倒数第一行出发的最优值，然后根据从倒数第一行出发的最优值求出从倒数第二行出发的最优值3.采用自底向上的方式计算问题的最优值：这个就是我上面说的，要先求解从倒数第一行出发的最优值，然后根据从倒数第一行出发的最优值求出从倒数第二行出发的最优值，自底向上的计算，迭代的方式求解子问题4.根据计算最优值时间得到的信息，构造最优解这个就是问你具体是怎么走的，我们需要在求解子问题的时候保存一些信息，采用构造出最优解（最优值和最优解是不同的，最优值在本问题中是一个走法中权值之和最大的那一个，而最优解是具体的走法），这里题目没有要求就是不用去构造最优解，构造起来也挺麻烦的。。。。解法：dp[i][j]：代表从第i行第j列出发得到的最优值dp[i][j]=max（dp[i+1][j]，dp[i+1][j+1]）+a[i][j]表示从第i行第j列出发的最优值等于到i+1行的两种走法中最大的那一个加上出发点的权值！

--------------------- 
~~咳咳以上其实是百度的QwQ除了那个状态转移方程~~

接下来！！！
上代码
------------


```
#include<bits/stdc++.h>//万能头~~懒得打其他的头文件了~~
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);//n行
    int a[n][n];
    memset(a,0,sizeof(a));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            scanf("%d",&a[i][j]);//输入不用多说
        }
    }
    int dp[n][n];
    memset(dp,0,sizeof(dp));
    for(int j=0;j<n;j++)
    {
        dp[n-1][j]=a[n-1][j];//因为dp是自下而上的一种解题思想，所以QwQ
    }
    for(int i=n-2;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            dp[i][j]=max(dp[i+1][j],dp[i+1][j+1])+a[i][j];//推出的
        }
    }
    printf("%d\n",dp[0][0]);//输出
    return 0;
}
```

---

## 作者：御·Dragon (赞：1)

## 很多人想用贪心，但是我发现，贪心比如这样

![](https://cdn.luogu.com.cn/upload/pic/37859.png )

### 从7开始，8>1，往8走，但是如果往1走走到10000明显就甩别人一条街了好么！ 如果你用手算一下，就会发现，只能从下往上算。然而只能从倒数第二行开始弄，所以我们可以在根据这个图为例：
![](https://cdn.luogu.com.cn/upload/pic/37860.png )
### 从10000开始，往1走再往7就行了。所以我们可以得出一个结论：

# f[i][j] = max(f[i + 1][j],f[i + 1][j + 1]) + a[i][j]!

~~备注：f记录到每个点的目前累加答案,a为这个点的数值~~

### 所以，我们只需要枚举每个点，然后每次像上面的算就行了！

#### 话不多说，附上AC代码：

```
#include<bits/stdc++.h>//万能头 
using namespace std;
const int MAXR = 1001;//定义常量 
int n;//共有n层 
int f[MAXR][MAXR];//用来存储从下到上的某个点的答案 
int a[MAXR][MAXR];//记录这个三角形 
void calc(){//主要的DP程序 
	for(int i = n - 1;i >= 1; i--){//从倒数第2行枚举 
		for(int j = 1;j <= i; j++){//枚举每行的每个点 
			f[i][j] = max(f[i + 1][j],f[i + 1][j + 1]) + a[i][j];
			/*
			这里很重要！
			就是找到这个点下面最大的这个点
			进行累加 
			*/ 
		}
	}
}
int main(){//开始 
	cin>>n;//输入 
	for(int i = 1;i <= n; i++){//枚举第i行 
		for(int j = 1;j <= i; j++){//输入j个数 
			cin>>a[i][j];//输入a[i][j]的数 
			if(i == n){//最后一层的特别判断 
				f[i][j] = a[i][j];//这层的数就等于输入的数 
			}
		}
	}
	calc();
	cout<<f[1][1];//综上所诉,从下到上,自然f的第1个点就会是答案了,所以直接输出 
	return 0;//收尾 
} 
```

__还有一种dfs的算法，但是会TLE。可以看看__

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
int a[MAXN][MAXN];
int n;
int ans;
void dfs(int x,int y,int sum){
    if(x == n){//已到达最优值
        if(sum > ans)ans = sum;//更新，返回
        return;
    }
    dfs(x + 1,y,sum + a[x + 1][y]);//左搜
    dfs(x + 1,y + 1,sum + a[x + 1][y + 1]);//右搜
}

int main(){
    cin>>n;
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= i; j++){
            cin>>a[i][j];
        }
    dfs(1,1,a[1][1]);//搜索
    cout<<ans<<endl;
    return 0;
}
```

__是吧，会TLE 55分。所以可以用记忆化搜索。其实这也和DP有相似之处__

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
int a[MAXN][MAXN];
int f[MAXN][MAXN];
int n;
int ans;

int dfs(int x,int y){//有返回值，int
    if(f[x][y] == -1){
    	if(x == n)f[x][y] = a[x][y];
    	else {
    		f[x][y] = a[x][y] + max(dfs(x + 1,y),dfs(x + 1,y + 1));
        }
    }
    return f[x][y];
}

int main(){
    memset(f,-1,sizeof(f));
    cin>>n;
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= i; j++){
            cin>>a[i][j];
        }
    dfs(1,1);
    cout<<f[1][1]<<endl;
    return 0;
}
```

__那么我们再提一下DP顺推，肯能有助于大家__

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
int a[MAXN][MAXN];
int f[MAXN][MAXN];
int n,ans;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n; i++)
		for(int j = 1;j <= i; j++){
			scanf("%d",&a[i][j]);
		}
	f[1][1] = a[1][1];
	for(int i = 2;i <= n; i++)
		for(int j = 1;j <= i; j++){
			f[i][j] = max(f[i - 1][j - 1],f[i - 1][j]) + a[i][j];
		}
	for(int i = 1;i <= n; i++){
		ans = max(ans,f[n][i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

## 好了，下期再见！

---

## 作者：Nick丶12138 (赞：1)

/\*
看到一片题解都是dp，然而本人看不太懂也不太会打dp

所以就用搜索做啦

给那些和我一样看不懂dp的人看吧

思路：

从上往下，每次可以走下或者右下

搜最大值，哪边值大走哪边

到了最后一层一个一个比，找出最大值

输出
\*/
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
struct node{int x,y;}a[1000010];
int q[1010][1010];//q数组为输入 
int w[1010][1010];//w数组为q数组的copy 
int ans=-1; 
int n;
int st=1,ed=2;
int fy[2]={0,1};//只有两种走法，且每次走x必定+1，所以可以不用写 
int pp=-1;
void bfs()
{
    a[st].x=1;a[st].y=1;w[1][1]=q[1][1];//第一步坐标(1,1)第一格的值相等 
    while(st!=ed)
    {
        for(int i=0;i<=1;i++)//只能下或者右下，所以只有两种走法 
        {
            int tx=a[st].x+1;//往下走一层 
            int ty=a[st].y+fy[i];//走下或者右下 
            if(tx<=n&&w[tx][ty]<w[a[st].x][a[st].y]+q[tx][ty])
            //如果往下走没有出，走下一步的值比下一步原本的值大，就走 
            {
                a[ed].x=tx;//走 
                a[ed].y=ty;//走 
                w[tx][ty]=w[a[st].x][a[st].y]+q[tx][ty];//这一步的值等于上一步加这一步 
                ed++;
            }
            else
            //如果走出了或者走下一步的值没有下一步原本的值大(因为可能存在负数) 
            {
                ans=ans>w[a[st].x][a[st].y]?ans:w[a[st].x][a[st].y];//看看当前答案和本格值哪个大 
                if(ans==0&&pp==1)//坑点在此，如果到了最后我的答案是0，但是我的最后一行有值 
                //pp=1证明并不是全0三角阵 
```
{//且这种情况值必定是1
```cpp
                    ans=1;//答案等于一 
                }
            }
        }
        st++;
    }
}
int main()
{
    memset(w,0,sizeof(w));//一开始全部数组都是0
    memset(p,0,sizeof(p));//个人习惯 
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            scanf("%d",&q[i][j]);//输入不说 
            if(i==n)//如果是最后一行，而且最后一行有值不为0，pp(一个标记)等于1(是为了防止坑点) 
            {
                if(q[i][j]>0) pp=1;
            }
        }
    }
    bfs();
    printf("%d",ans);//输出 
    return 0;
}

```

---

## 作者：Hydra_ (赞：1)

## 分析 ##

有的同学看到这道题目起了点思想：暴力枚举呀……或者有人说，我们只要每次走最大的点就可以了呀……都不对！！！

正解：采用自底到顶的顺序来分析。我们想，如果我们现在已经到了倒数第二排，然后我们需要向左走或者向右走，

![例子](http://img.blog.csdn.net/20170927111652487?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzk2NzA0MzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

当我们走到5这个点（假设2和4是最后一层，5是倒数第二层）的时候，我们有两种选择，一种是走2（当前路径和是5+2=7），一种是走4，（当前路径和是5+4=9），明显，机智的同学们总会走4，这样我们在5这里就可以不用判断了，走到5就一定走4（是不是呀），所以我们可以更改5这里的权值了：5就直接改成9。

就是用这种思路，我们一层一层，从底下开始往上更改，最后会更改到只剩下一个点，那就是我们的答案了。


代码
--

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1100][1100];//用来存数据
int r;//层数
int main()
{
    scanf("%d",&r);
    for(int i=1;i<=r;i++)
    for(int j=1;j<=i;j++)
    scanf("%d",&a[i][j]);
    //这里的读入要好好思考下，对新手是个挑战
    for(int i=r-1;i>=1;i--)//从倒数第二层开始更改
    for(int j=1;j<=i;j++)//该层每一个元素都要跟新
    {
        int p1=a[i][j]+a[i+1][j];//向左走的路径和
        int p2=a[i][j]+a[i+1][j+1];//向右走的路径和
        a[i][j]=max(p1,p2);//比较一下，更改
    }
    cout<<a[1][1];//输出答案。
    
    return 0;
}
```

---

## 作者：youken (赞：1)

#一步一步优化动归

ps：该题解为我这个弱鸡看看了一位大神的动归视频后总结整理而成

在此%%%orz

以这题为例，可以对动归的一种解题思路有个深入理解（貌似楼上有大神已经简略说了啊。。）

##简单分析

该题其实是ioi 1994 的原题，只不过将R从100改到了1000（usaco够毒啊。。）

先用二维数组储存数据。

我们从第一个数num（0,0）开始往下走，往左或往右走一个数即num（0+1，0），num（0+1,0+1）

从当中任意一个数num（i，j）开始就是**num（i+1，j）和num（i+1，j+1）**


##先是递归

作为标准蒟蒻的我，首先想到是递归。。

上代码。。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
int n,num[maxn][maxn];
void input(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<=i;j++){
            scanf("%d",&num[i][j]);
        }
    return;
}
inline int maxnumber(int i,int j){//递归核心
    if(i==n)return num[i][j];//如果该处是最后一行就直接出来
    return max(maxnumber(i+1,j),maxnumber(i+1,j+1)) + num[i][j];//这个地方基本和模拟差不多，单纯的按题意找max加上
}
int main(){
    input();
    cout<<maxnumber(0,0);
    return 0;
}
```
这个做法可以拿到55分，从第六个点开始t飞到无穷。。。
###我们来看看递归的复杂程度

由于使用单纯的递归，我们在一些同样的数上算了很多次。

以案例为例，我们从第一左斜行7,3,8,2,4都只算了一次，以此类推，第二斜行分别算了1,2,3,4,次，后面以此类推。。。

可以证明时间复杂度为**O（2^n）。n=1000时，我们早就被T飞。。。

于是我们开始考虑优化。

###记忆型递归

弱鸡任然不开窍，不愿放弃递归这块肉（代码好写）。。

那好吧，既然是重复计算，我们存下来不重复不就行了？！

我们另开一个数组maxans进行记忆

上代码。。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
int n,num[maxn][maxn];
int maxans[maxn][maxn];//记忆数组
void input(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<=i;j++){
            scanf("%d",&num[i][j]);
            maxans[i][j]=-1;//-1表示我们还没有对该点进行计算
        }
    return;
}
inline int maxnumber(int i,int j){//递归核心
    if(maxans[i][j]!=-1)return maxans[i][j];//计算过的不再计算
    if(i==n)return num[i][j];//如果该处是最后一行就直接出来
    return max(maxnumber(i+1,j),maxnumber(i+1,j+1)) + num[i][j];//这个地方其实就是动归方程
}
int main(){
    input();
    cout<<maxnumber(0,0);
    return 0;
}
```
相比单纯递归，我们只加了两句，这就完成了记忆化
然而此时弱鸡发现自己任然被卡在了第六个点，于是终于开窍开始考虑动归。。。（其实是优化了，洛谷的测试数据体现不出来）

##动归来了

其实在递归中，我们就已经用到了动归方程

maxans[i][j]=max(maxans[i+1][j],maxans[i+1][j+1])+num[i][j]

这里我们从最底下一行往上找，用递推的方法。。

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
int n,num[maxn][maxn];
int maxans[maxn][maxn];
void input(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<=i;j++){
            scanf("%d",&num[i][j]);
            }
    return;
}
void solve(){//递推核心
    for(int i=0;i<n;i++)maxans[n][i]=num[n][i];//将最底下一行赋给maxans
    for(int i=n;i>=0;i--)
        for(int j=0;j<=i;j++){
            maxans[i][j]=
                max(maxans[i+1][j],maxans[i+1][j+1]) + num[i][j];//又是这个熟悉的相加
        }
    cout<<maxans[0][0];
}
int main(){
    input();
    solve();
    return 0;
}
```
这里其实已经可以愉快的AC了~~
###我们对复杂度进行分析

我们将原来的递归函数，通过从下往上的递推方式，化为了两个循环、

我们的时间复杂度从**O（2^n）变成了O（n^2）**。这是质的飞跃啊，同志们！

###插一句空间优化

开窍之后的蒟蒻有些欲求不满，他认为再开一个二维太费空间，如果空间约束非常毒就死定了。（可能性不大~~）

的确，这里的递归完全用不上二维数组，我们可以只开一个一维maxans[n]即可，然后重复覆盖赋值即可

进一步考虑，因为每行仅有一个最优解，我们可以把数组maxans砍掉，直接借助num[n][n]的第n行，再通过指针实现。

这里只给出指针的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
int n,num[maxn][maxn];
int * maxans;//指针
void input(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<=i;j++){
            scanf("%d",&num[i][j]);
            }
    return;
}
void solve(){//递推核心
maxans=num[n];//maxans指向最底一行
    for(int i=n;i>=0;i--)
        for(int j=0;j<=i;j++){
maxans[j]=max(maxans[j],maxans[j+1]) + num[i][j];//又是这个熟悉的相加
```
}//利用原来的num数组的行数，每行一个最优解往上叠加
```cpp
    cout<<maxans[0];
}
int main(){
    input();
    solve();
return 0;
 }
```
运用二维数组的递推在洛谷最大数据下，空间为9667kb，用指针空间优化后为5871kb。（意义貌似不大~~。。）
但我们经历一个**二维--》一维--》指针**的一个空间优化过程，这个过程值得学习。

##总结

经过上面蒟蒻一步一步的优化，我们的程序越来越高效，由此可以总结出动归的一般思路

递归--》动归

（该处部分借鉴神牛。。%%orz）

**递归函数有n个参数，就定义一个n维的数组，数组的下标是递归函数参数的取值范围，数组元素的值是递归函数的返回值，这样就可以从边界值开始，逐步填充数组，相当于计算递归函数值的逆过程。**

最后祝大家多多AC，再次%大神和楼上各路神牛牪犇


---

## 作者：逍遥__天赐 (赞：1)

这道题要用记忆化搜索，不然会超时

思路：从最上面找起，先得到下面所有的最优解

然后做比较，得到最终的最优解

dp数组记忆到本格的最优解

若此格为-1，则还没被计算过

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1001][1001],dp[1001][1001];
int r;
int solve(int i,int j)
{
    if(dp[i][j]==-1)
    {
    if(i==r) dp[i][j]=a[i][j];
    else dp[i][j]=max(solve(i+1,j),solve(i+1,j+1))+a[i][j];
    }
    return dp[i][j];
}
int main()
{
    cin>>r;
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=i;j++)
        {
            cin>>a[i][j];
        }
    }
    solve(1,1);
    cout<<dp[1][1];
    return 0;
}
```

---

## 作者：Aehnuwx (赞：1)

###由于此题并不是特别难，所以就不发代码了，但是思路是~~肯定会讲清楚的。

不敢相信，这道题出自IOI1999。但如果我在那个时代，我肯定也做不出来。

蒟蒻一来看到这题，大叫：“哇，这题真简单！贪心~~就行啦~~！”

但是贪心法的缺点在此题中一览无余的展现了出来：目光短浅。

如果按照贪心法思路，则：7-8-1-7-5，其和为28；

但是存在着另外一条路：7-3-8-7-5，其和为30。

所以贪心法就OUT了。。。

然后蒟蒻又想：贪心法不行，那搜索总行了吧！

结果这次蒟蒻又想错了……

在本题中，R<=1000，要是用搜索，无论是DFS还是BFS，无论怎样剪枝，只有一种结果：TLE。

所以！！！

本题最简算法就是：递推！

递推共有两种方法可以选择：顺推法和逆推法，两种方法皆可。

顺推法和逆推法实际上很好区别，顺推法是从已知条件出发，向结果推导，而逆推法则是从结果出发，一步一步地往前推导。在本题中，顺推法就是从数塔的上方出发，一直推到最底层。而逆推法就是从最底层出发，往顶层前进。

我是用顺推法的。直接就写了个两重循环。

```cpp
for(int i=2; i<=n; i++)
        for(int j=1; j<=i; j++)
            if(b[i-1][j-1]>b[i-1][j]) //因为我们要求最大值，所以要将数塔上一层最大的数加上去。
                b[i][j]=b[i][j]+b[i-1][j-1];
            else b[i][j]=b[i][j]+b[i-1][j];
上面是主要部分，剩下就是什么输入输出之类的了。
```

---

## 作者：ajil (赞：1)

一个特别特别经典的题目，可以说是几乎是每个OIER接触的第一道动规题。

**(由于两个代码是分两次写的，所以可能风格不太一样……)**

先来看看讲的最多的一个方法：

##从底层向上推出最优解

用dp[i][j]表示从(i,j)开始的最优解，那么答案即是dp[1][1]

状态转移方程: **dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + map[i][j]**

```cpp
#include <iostream>
using namespace std;
const int MR(1001);    //n(即题目中的r)的最大值
int map[MR][MR];    //保存输入数据
int dp[MR][MR];    //最优解
int n;
inline int dmax(const int& a,const int& b)    //返回最大值
{ return (a>b ? a : b); }
int main()
{
    cin >> n;    //输入n
    for(int i(1);i<=n;++i)
        for(int j(1);j<=i;++j)
            cin >> map[i][j];    //输入数据
    for(int i(1);i<=n;++i)    dp[n][i] = map[n][i];   //初始化，最后一行数据的最优值即为其本身
    for(int i(n-1);i>0;--i)
        for(int j(1);j<=n;++j)
        {
            dp[i][j] = map[i][j] + dmax(dp[i+1][j], dp[i+1][j+1]);    //向上递推求出最优解
        }
    cout << dp[1][1];    //输出最优解
    return 0;
}
```
优点是最优解的表示比较容易，但由于是逆向思考可能不太好写


然后是第二个方法：

##从顶层往下推出最优解

用dp[i][j]表示以(i,j)结束的最优解，则最优解为最后一行中dp的最大值

状态转移方程: **dp[i][j] = max(dp[i-1][j-1],dp[i-1][j]) + map[i][j]**

```cpp
using namespace std;
const int Mn(1002);    //n的最大值(定义成1002是为了便于处理边界)
int dp[Mn][Mn];    //最优解
/*边读边求所以省去了map数组*/
int main()
{
    int n;
    cin >> n;    //输入n
    for(int i(1);i<=n;++i)
        for(int j(1);j<=i;++j)
        {
            int tn; cin >> tn;    //输入数据
            dp[i][j] = max(dp[i-1][j-1],dp[i-1][j]) + tn;    //求解最优解
        }
    int max(0);
    for(int i(1);i<=n;++i)
    if(dp[n][i] > max) max = dp[n][i];    //寻找最优解
    cout << max;    //输出最优解
    return 0;
}
```
优点是可以边读边求解，但最优解的表示比较麻烦

所以写动规题时要注意状态的表示和递推顺序，因为对于一道题状态定义的不同会导致代码上的较大差别


---

## 作者：_J_C_ (赞：1)

呐。
动规入门第一道，总让我分不清递推与动规（反正记住是动规了）

用一个二维数组存数字，如

1
12
123

那么点[x][y]的父节点就是[x-1][y]与[x-1][y-1]//注意，数组中x是从上往下而y从左往右

为了方便，我们从1开始，让map的左侧与上方各空一行为0

对了，map[x][[y]表示走到这个点的最大数字。






```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int map[1001][1001] = { 0 };
inline int my_max(const int &a,const int &b)//不是很懂max在哪里，就自己写个吧
{
    if (a > b)return a;
    else return b;
}
int main()
{
    int n, iMax(0);
    scanf("%d", &n);
    for (int i(1); i <= n; ++i)
    {
        for (int a(1); a <= i; ++a)
        {
            int b;
            scanf("%d", &b);
            map[i][a] = b + my_max(map[i-1][a-1],map[i-1][a]);//走到这个点无非两种选择，也就是对应两个父节点、取更大的当然是走到这个点的最优解了
            if (map[i][a] > iMax)iMax = map[i][a];//记录最大值
        }
    }
    cout << iMax;
    return 0;
}
希望能帮到你
```

---

## 作者：mingx1 (赞：1)

其实不一定要用到逆向推，我感觉这道题正向和逆向动态规划的本质上是一致的，复杂度都是一样的。（毕竟都是理论上用到“自底向上”的思想，尽管形式上一个i++一个i--....)

用b[i][j]代表在这一个点上可以获得的最大值，如下



```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[1005][1005];int b[1005][1005];int res;
int main()
{
int n;cin>>n;
for(int i=1;i<=n;i++)
for(int j=1;j<=i;j++)
cin>>a[i][j];
b[1][1]=a[1][1];
for(int i=2;i<=n;i++)
for(int j=1;j<=n;j++)
{
    b[i][j]=max(b[i-1][j],b[i-1][j-1])+a[i][j];
}    
res=b[n][1];
for(int i=1;i<=n;i++)
{
    if(b[n][i]>res)
    res=b[n][i];
}
cout<<res;
return 0;
}
```

---

## 作者：oreimo_eromanga (赞：1)

```cpp

//注意：读进来是一个直角三角形！！！！！！ 
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<string>
#include<cstdio>
#include<cmath>
using namespace std;
int a[1001][1001];
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
       for(int j=1;j<=i;j++)
          cin>>a[i][j];            //读入。
    for(int i=n-1;i>=1;i--)
       for(int j=1;j<=i;j++)
       {
          if(a[i+1][j]>=a[i+1][j+1]) //选择最大的路径。 
            a[i][j]+=a[i+1][j];
          else
            a[i][j]+=a[i+1][j+1];
       }
    cout<<a[1][1]<<endl;            //打印。 
    system("pause");
    return 0;
}

```

---

## 作者：CoolTeam (赞：1)

有最优子结构，用动态规划来算就不会重复计算。

动态规划，设D(i,j)表示从第i行第j个的点出发，能获得的最大值，答案为D(1,1)。

初始化最底层的点，D值就是a值(自己的点的值)，然后自底向上递推。

D(i,j)=max(D(i+1,j),D(i+1,j+1))+a(i,j)

C代码：

```cpp
#include<stdio.h>
int a[1001][1001],d[1001][1001];
int main(void)
{
    int n,i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    for(i=1;i<=n;i++) d[n][i]=a[n][i];//最底层的点
    for(i=n-1;i>=1;i--)
        for(j=1;j<=i;j++)
            d[i][j]=d[i+1][j]>d[i+1][j+1]? d[i+1][j]+a[i][j] :d[i+1][j+1]+a[i][j];
    printf("%d",d[1][1]);
    return 0;
}
```

---

## 作者：zzozz (赞：1)

我们看一个简单的情况比如我们在（i，j）这个位置，这个位置是有（i-1，j），我们已经求出了所有的（i，j）以下的点我们向上返回到（i-1，j）这个位置，我们就向下达到（i，j+1）我们发现（i，j）可以到达（i+1，j+1）并且（i，j+1）也可以到达（i+1，j+1）；那么这个点我们就计算了两次，导致效率低下，如果我们用一个数组表示到达（i，j）能得到的最大数值，就可以不用重复计算，这样就相当于把每个点都遍历一遍，复杂度就是（（1+n）\*n/2） 就不会超时了，我们把这个方法，叫做记忆化，而整个方法叫做记忆化搜索。





```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
const int maxn = 1010;
using namespace std;
int n;
int val[maxn][maxn], f[maxn][maxn];
int dfs(int i,int j){
    if (f[i][j] != -1) return f[i][j];
    if (i == n+1) return f[i][j] = val[i][j];
    return f[i][j] = max(dfs(i+1, j+1), dfs(i+1, j)) + val[i][j];
}
int main(){
    memset(f, -1, sizeof(f));
    scanf("%d", &n);    
    for(int i = 1;i <= n;i ++)
        for (int j = 1;j <= i;j ++) scanf("%d", &val[i][j]); 
    printf("%d", dfs(1,1));
}
博客有详细的讲解[http://www.cnblogs.com/zzozz/p/7623664.html](http://www.cnblogs.com/zzozz/p/7623664.html)
```

---

## 作者：我是小样儿 (赞：0)

这道题比较简单，本人写了博客就不详细介绍了：


```cpp
<http://blog.csdn.net/c20190413/article/details/77592412>
<http://blog.csdn.net/c20190413/article/details/77450868>
#include<cstdio>
#include<algorithm>
using namespace std;
int r,a[1002][1002],F[1002][1002];
main()
{
    scanf("%d",&r);
    for(int i=1;i<=r;i++)
        for(int j=1;j<=i;j++)
        {
            scanf("%d",&a[i][j]);
            F[i][j]=a[i][j];
        }
    for(int i=r-1;i>0;i--)
        for(int j=1;j<=i;j++)
            F[i][j]+=max(F[i+1][j],F[i+1][j+1]);
    printf("%d",F[1][1]);
}
```

---

## 作者：SofanHe (赞：0)

本蒟蒻今天A了此题.....

做完之后看各位大佬真是自愧不如啊!

不过这里有一个自创的优化,让大家见笑了....

就是关于滚动数组的优化,显然此题只对前后两行的状态有关,因此,我们仅仅储存两行的状态.


利用自然数奇偶间隔的方法,    利用  i%2   作为下标,不会重复.


下面附上我的代码


```cpp
#include<iostream>
using namespace std;
int n,s[2][1001];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)for(int j=1;j<=i;j++){cin>>s[i%2][j];    s[i%2][j]=max(s[(i-1)%2][j-1],s[(i-1)%2][j])+s[i%2][j];}
    for(int i=1;i<=n;i++)    s[n%2][0]=max(s[n%2][i],s[n%2][0]);    
    cout<<s[n%2][0];
    return 0;
}
```

---

## 作者：mr辄 (赞：0)

不妨把问题变为求“从底部任意点走到最高点的路径”的最大数字和。

我们令a[i][j]表示第i行第j列上的数。

设f[i][j]表示从底端走到第i行第j列时的最大路径和，那么它的值就是f[i+1,j]和f[i+1,j+1]两者的较大值加上a[i][j] 。

状态转移方程为f[i][j]=max(f[i+1][j],f[i+1][j+1])+a[i][j]

边界f[R][i]=a[R][i]

最后的答案即为f[1][1]。

代码：



```cpp
var a,f:array[0..1002,0..1002]of longint;
n,i,j:longint;
function max(a,b:longint):longint;
begin
 max:=a;
 if max<b then exit(b);
end;
begin
 fillchar(a,sizeof(a),0);
 fillchar(f,sizeof(f),0);
 readln(n);
 for i:=1 to n do
 for j:=1 to i do begin read(a[i,j]);end;
 for i:=1 to n do f[n,i]:=a[n,i];
 for i:=n-1 downto 1 do
 begin
  for j:=1 to i do
  f[i,j]:=max(f[i+1,j],f[i+1,j+1])+a[i,j];
 end;
 writeln(f[1,1]);
end.

```

---

## 作者：Lyrics (赞：0)

这题如果没记错的话和1999年的IOI的数塔问题是非常相似的，当初DP还是很多人不会啊，在当初可是IOI的题。

思路清晰，从下往上我们根据题目可得知每一个数只会和下面的2个数和上面的1个数相连接

所以我们可以发现我们如果要择优的话肯定从下面开始排除，就是那种人数越多越需要筛选的意思。

那么我们就可以说上面的那个值是从原本下面两个择优的值里找出一个较优的加上你自己的数

就是f[i][j]=max(f[i+1][j],f[i+1][j+1])+a[i][j];

这样其实我们的DP方程就完成了！

那么代码如下请见笑啦！！！

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1002][1002],f[1002][1002],n,maxn=-1;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++){
            scanf("%d",&a[i][j]);
            f[i][j]=a[i][j];
        } 
    for(int i=n;i>=1;i--){
        for(int j=1;j<=i;j++){
            f[i-1][j]=max(f[i][j],f[i][j+1])+a[i-1][j];
        }
    }
    printf("%d\n",f[0][1]);
    return 0;
}
```

---

## 作者：Kisarag (赞：0)

这个题目有多种解法，这里是用dp，算是很基础的dp了。

解法过程：

（1）从底层开始，本身数值即最大值；

（2）倒数第二层的计算取决于底层；

（3）即样例的路径为13-8-26-15-24。

以下贴代码233333

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1001;
int n;
int a[M][M];
int func()
{
  int i,j;
  for(i=n-1;i>=1;i--)
    for(j=1;j<=i;j++){
      if(a[i+1][j]>a[i+1][j+1]) 
        a[i][j]+=a[i+1][j];
      else a[i][j]+=a[i+1][j+1]; 
    }
  return a[1][1];
}
int main()
{ 
  int i,j;
  cin>>n;
  for(i=1;i<=n;i++)
    for(j=1;j<=i;j++)
      cin>>a[i][j];
  cout<<func()<<endl;
  return 0;
}
```

---

## 作者：Ivanhunt (赞：0)

这是一道经典的DP题目 主要想法就是从三角形底部向上推 同时进行最大值更新

##状态转移方程为：a[i][j]+=max(a[i+1][j],a[i+1][j+1]);

##核心代码为：

```cpp
for(int i=n-1;i>=1;i--)
        for(int j=1;j<=i;j++){
            a[i][j]+=max(a[i+1][j],a[i+1][j+1]);
        } 
```
以下是程序：
```cpp
#include<iostream>
#include<cstdio>
const int MaxN=1002;
int a[MaxN][MaxN]={0};   //初始化数组值为0
using namespace std;
int main(){
    int n;
    scanf("%d",&n);   //读入行的数目
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);  //读入金字塔的整数
    for(int i=n-1;i>=1;i--)
        for(int j=1;j<=i;j++){
            a[i][j]+=max(a[i+1][j],a[i+1][j+1]);  //状态转移方程 从三角形的底部向上推 更新最大值 max在iostream中就有，无需调用algorithm函数
        } 
        cout<<a[1][1];
        return 0;
}
```

---

## 作者：龘龘龘龘龘龘 (赞：0)

这一题用记忆化搜索一下就可以得出结果；很简单的一道可以用dfs解动规题，题解绝对简单易懂；严禁复制党直接抄袭！！！！

代码如下，各位可以看看；

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[1001][1001],f[1001][1001],n;
int dfs(int x,int y)
{
    if(f[x][y]==-1)//特判一下有没有被计算了，如果计算了就直接返回f[x][y];
    {
        if(x==n) f[x][y]=a[x][y];
        else f[x][y]=a[x][y]+max(dfs(x+1,y),dfs(x+1,y+1));//考虑向右和向左两方向那个数值大；
    }
    return f[x][y];
}
int main()
{
    cin>>n;//输入
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            f[i][j]=-1;//赋初值为-1；表示未被计算过；
    dfs(1,1);
    cout<<f[1][1]<<endl;
    return 0;
}

```

---

## 作者：lxyhhhhhh (赞：0)

最短代码，，，

最简理解，，，

**作为羸弱oo**

羸弱为新手发表。。。


新手可以来了解一下。。。


这可以看成逆向思维经典题。。。


将其想成从最低一层向最高层进发，经过一个数字就加上它，因此每个数上有一个数的和，以此类推最后输出最顶层的数的和。。。


为了实现，，，我们需要两个数组，一个读三角上的数，一个用来存三角形上数的和。。。


输入后一个循环嵌套即可求出最顶层的数的和。。。


实现如下：

```cpp
#include<bits/stdc++.h>//万能头文件。 
using namespace std;  
const int maxn=1000+10;
int a[maxn][maxn],b[maxn][maxn];/*a为每个节点，b为经过每个节点时积累的点数。*/ 
int main()
{    int n;
    cin>>n;//输入塔的高度。 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            cin>>a[i][j];//输入具体"TOWER"。 
    for(int i=n;i>=1;i--)
        for(int j=1;j<=i;j++)
            b[i][j]=a[i][j]+max(b[i+1][j],b[i+1][j+1]);//上一层的积累数=下一层的最大积累数加上最大的三角上的点数。 
    cout<<b[1][1];//输出撒花！！！ 
    return 0;
}
```

---

## 作者：liaopifan (赞：0)

注意三角形中不能灌0，可以灌-1，原因是若三角形中数字为0就会无谓递归导致超时（第8个测试点）



```cpp
#include<cstdio>
#include<cstring>//memset函数
const int maxn = 1000+50;//此处要开大50（其余题目也这样）
int n, a[maxn][maxn], f[maxn][maxn];
int max(int a,int b){
    return (a>b) ? a : b;
}
int ff(int x,int y){
    if(x==n) return a[x][y];
    if(f[x][y]!=-1) return f[x][y];
    return f[x][y] = a[x][y] + max(ff(x+1,y),ff(x+1,y+1));//动态转移方程
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    memset(f,-1,sizeof(f));//此处不能灌0，原因是若三角形中数字为0就会无谓递归导致超时
    printf("%d",ff(1,1));
    return 0;
}
```

---

## 作者：攀岩高手 (赞：0)

这道题用动归要从下往上推，d(i, j)表示从格子(i, j)（就是第i行的第j个格子）出发的最大总和，不难推出状态转移方程d(i, j)=a(i, j)+max{d(i+1, j), d(i+1, j+1)}. 可以使用递推的方法解这道题，但是题解似乎没有记忆化搜索，我来补上代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N=1001;
int d[N][N]; // 记忆化搜索要用的数组，d[i][j]表示从格子(i, j)出发的最大总和
int n, a[N][N];
int solve(int i, int j)
{
    if (d[i][j]>=0) return d[i][j]; // 如果这个格子不为-1，则已计算过，无需重复计算
    return d[i][j]=a[i][j]+(i==n?0:max(solve(i+1, j), solve(i+1, j+1))); // 代入状态转移方程，递归求解
}
int main()
{
    // 读入
    cin>>n;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=i; j++)
            cin>>a[i][j]; // a[i][j]表示格子(i, j)
    memset(d, -1, sizeof d); // 初始化d数组，-1表示还没有求到这个点
    cout<<solve(1, 1); // 递归求解
    return 0;
}
```

---

## 作者：strike (赞：0)

一道典型的动态规划题，dalao们的华丽丽方法都在楼下，破车就不挡道了。

**一定注意三角形数组的大小，本人就曾经因为把1000看成100导致后4个点RE。**

代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[1001][1001]={0};//首先定义数组，记得清零;
int main()
{    int n,i,j,max;
    cin>>n;
    for(i=1;i<=n;i++)
      for(j=1;j<=i;j++)
      cin>>a[i][j];               //读入就不多说了；
    for(i=1;i<=n;i++)
      for(j=1;j<=i;j++)
      if(a[i-1][j]>a[i-1][j-1])a[i][j]+=a[i-1][j];       //找一下上面那行在路线上的数中哪一个最大，加上；
      else a[i][j]+=a[i-1][j-1];                             
    max=a[n][1];                                             //最大值max；
    for(i=2;i<=n;i++)
    if(a[n][i]>max)max=a[n][i];                         //我们开心的去找最大的那一个数；
//    printf("the max number of line:");//这是胡乱加的；
    cout<<max<<endl;//输出最大值；
return 0;}               //一切，都结束了~~
```
**注意：以上题解提供给dp初学者，dalao勿喷，进阶者请参阅楼下；**


---

## 作者：一尾江河 (赞：0)

观察下面的数字金字塔。


写一个程序来查找从最高点到底部任意处结束的路径，使路径经过数字的和最大。每一步可以走到左下方的点也可以到达右下方的点。


7
3   8
8   1   0

2   7   4   4

4   5   2   6   5

在上面的样例中,从7 到 3 到 8 到 7 到 5 的路径产生了最大


输入输出格式


输入格式：

第一个行包含 R(1<= R<=1000) ,表示行的数目。


后面每行为这个数字金字塔特定行包含的整数。


所有的被供应的整数是非负的且不大于100。


输出格式：

单独的一行,包含那个可能得到的最大的和。


输入输出样例


输入样例#1：

5
7
3 8
8 1 0
2 7 4 4

4 5 2 6 5

输出样例#1：

30

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int d[1001][1001];
int n;
int maxsum[1001][1001];
int Maxsum(int i,int j){
    if(maxsum[i][j]!=1) return maxsum[i][j];
    if(i==n) maxsum[i][j]=d[i][j];
    else{
        int x=Maxsum(i+1,j);
        int y=Maxsum(i+1,j+1);
        maxsum[i][j]=max(x,y)+d[i][j];
    }
    return maxsum[i][j];
}
int main(){
     int i,j;
     cin>>n;
     for(i=1;i<=n;i++){
         for(j=1;j<=i;j++){
             cin>>d[i][j];
             maxsum[i][j]=1;
         }
     }
     cout<<Maxsum(1,1)<<endl;
     return 0;
 }

```

---

## 作者：没想好叫啥 (赞：0)

看很多大佬都用dp做

来一发记忆化搜索的题解

时间复杂度大约是O(N^2)


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a[1005][1005],b[1005][1005];
    int n,ans;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            cin>>a[i][j];//输入
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            if(j==1)  a[i][j]+=a[i-1][j];
            else  a[i][j]=a[i][j]+max(a[i-1][j-1],a[i-1][j]);//当可以获得两个值时，比较哪个更大
            if(ans<a[i][j])   ans=a[i][j];//储存最大的
        }
    }
    cout<<ans;//输出
    return 0;
}
```

---

## 作者：codesonic (赞：0)

这是道递推题，刚开始想的是贪心，可是如以下

1
1 2
1 2 3
1000000 1 1 1

贪心就不适用了

那递推怎么推呢。。。。

从下面向上推，算出各个结果，然后就知道最大结果了，我们设a[i][j]为在第i行最大的结果

就得到以下代码（为了防抄袭，仅有重要部分）

```cpp
  for (i=n-1;i>=1;i--)
   for (j=1;j<=i;j++)
     {
       if (a[i+1][j]>=a[i+1][j+1])  a[i][j]+=a[i+1][j];     //选择最大路径
       else  a[i][j]+=a[i+1][j+1];
     }
```
以上。（代码好像还比·我的文字好理解）
（我的思路居然和辅导书里面一样）


---

## 作者：LMB_001 (赞：0)

这道题最好用DP，用DP有两种方法，第一种从上往下，最后在最后一行打擂台

第二种从下往上计算，最后输出F【1，1】，以下提供第二种的程序

```cpp
uses math;
var
 a,f:array[1..1000,1..1000]of longint;
 n,i,j:longint;
begin
 readln(n);
 for i:=1 to n do
  for j:=1 to i do read(a[i,j]);//读入
 for i:=1 to n do f[n,i]:=a[n,i];//最后一行初始化
 for i:=n-1 downto 1 do
  for j:=1 to i do
   f[i,j]:=max(f[i+1,j],f[i+1,j+1])+a[i,j];//核心部分
 writeln(f[1,1]);//输出
end.
```

---

## 作者：封禁用户 (赞：0)

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int r;
int a[1005][1005];
int f[1005][1005];
int main(){
int i,j;
scanf("%d",&r);
for(i=1;i<=r;i++){//读入data
    for(j=1;j<=i;j++){
        scanf("%d",&a[i][j]);
    }
}
for(i=1;i<=r;i++){//自顶向下搜索
    for(j=1;j<=i;j++){//由题意很容易得知f[i][j]=max{f[i-1][j],f[i-1][j]}+data
        f[i][j]=max(f[i-1][j],f[i-1][j-1])+a[i][j];
    }
}
int mx=0;
for(i=1;i<=r;i++)//输出
mx=max(mx,f[r][i]);
cout<<mx;
return 0;
}

```

---

