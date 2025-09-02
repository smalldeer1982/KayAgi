# [USACO3.1] 总分 Score Inflation

## 题目背景

选手在我们 USACO 的竞赛中的得分越多我们越高兴。

我们试着设计我们的竞赛以便人们能尽可能的多得分,这需要你的帮助。


## 题目描述

我们可以从几个种类中选取竞赛的题目，这里的一个“种类”是指一个竞赛题目的集合，解决集合中的题目需要相同多的时间并且能得到相同的分数。

你的任务是写一个程序来告诉 USACO 的职员,应该从每一个种类中选取多少题目，使得解决题目的总耗时在竞赛规定的时间里并且总分最大。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 10^4$，$1 \leq p_i, t_i \leq 10^4$。

## 样例 #1

### 输入

```
300 4
100 60
250 120
120 100
35 20```

### 输出

```
605```

# 题解

## 作者：llzzxx712 (赞：87)

想弄懂完全背包题，当然是要先看01背包喽！作为一个刚刚学会背包一个星期的蒟蒻，我决定把我弄懂01背包和完全背包的过程分享给更多蒟蒻。

01背包
=
题目描述
-
   一个旅行者有一个最多能装 M
公斤的背包，现在有 n 件物品，它们的重量分别是W1，W2，...,Wn,它们的价值分别为C1,C2,...,Cn，求旅行者能获得最大总价值。

【输入】

第一行：两个整数，M
(背包容量，M≤200)和N(物品数量，N≤30） 

  第2..N+1
行：每行二个整数Wi，Ci，表示每个物品的重量和价值。

【输出】

仅一行，一个数，表示最大总价值。

---
下面是01背包模板代码，__最下面有样例数据__

```
    #include<iostream>
    using namespace std;
    const int maxm=201,maxn=31;
    int m,n;
    int w[maxn],c[maxn];
    int f[maxn][maxm];//表示前i个物品在容量为v下可以获得的
    最大总价值 
    int main()
    {
      cin>>m>>n;//背包容量m和物品数量n 
      for(int i=1;i<=n;i++){
          cin>>w[i]>>c[i];//输入每个物品的质量和价值 
      }
      for(int i=1;i<=n;i++){
          for(int v=m;v>0;v--){
              if(w[i]<=v){
                 f[i][v]=max(f[i-1][v],f[i-1][v-w[i]]+c[i]);
              }
    //f[i][v]表示前i件物品，总体积（质量）不超过v的最优价值 
              else{
                  f[i][v]=f[i-1][v];
              }
          }//个人习惯，每个循环都带括号，方便添加代码
       }
       cout<<f[n][m];//f[n][m]为最优解 
       return 0;
    }
```

    
  f[i-1][v-w[i]]这东西代表的就是在v的空间下，放入w[i](也就 是第i件物品）后再放之前的物品获得的价值。[v-w[i]]就是现在 的体积减掉该物品体积后剩下的，就是可以前i件物品留下的， 在之前的计算中已经求得了前i件物品可以得到的价值.
  
  它具有自动检索一般的功能，比如样例中我们在i=4时，它根据 [v-w[i]]找到了此时除了它剩下的空间放前面物品最多可以获得3 的价值，再加上它的9的价值得到12。同时它还和只放3个物品进行比较，如果第四个物品价值过小，程序将会选择不拿4。
  
  当我把 输入数据第四个物品和第三个物品的价值改为7时，发现f[3][10] 就已经达到了最大值11，程序在i=4时没有更改结果
  
以下是通过文件操作打出来的数据 
-
输入:

10 4 

2 1

3 3 

4 5

7 9

输出：
12

测试输出：
-
__（每段数据有10个，第i段数据代表i等于几时的f[i][1..10],每次的第一个数据代表本次操作时的 v）__

10 1

9 1

8 1

7 1

6 1

5 1

4 1

3 1

2 1

1 0

---
10 4


9 4

8 4


7 4

6 4

5 4

4 3

3 3

2 1

1 0

---
10 9

9 9

8 8

7 8

6 6

5 5

4 5

3 3

2 1

1 0

---
10 12

9 10

8 9

7 9

6 6

5 5

4 5

3 3

2 1

1 0

下面是用一维数组实现01背包
-
（用的本题数据和字母）但本题不是01背包题（因为每个种类中你可以选择若干道题，而不是只能做一道或不做），所以下面代码无法通过

```cpp
    #include<iostream>
    using namespace std;
    int x,y;
    int t[10002],p[10002];
    int f[10002];
    int main()
    {
        int m,n;
        cin>>m>>n;
        for(int i=1;i<=n;i++){
            cin>>p[i]>>t[i];
        }
        for(int i=1;i<=n;i++){
            for(int t1=m;t1>=t[i];t1--){
                f[t1]=max(f[t1],f[t1-t[i]]+p[i]);
             }
        }
        cout<<f[m];
        return 0;
    }
```

这里我们可以看到，它省去了数组中用来表示前i个物品（题目）的一维，因为这不重要。我们不需要管它是在前几个物品（题目）中在容量v（时间t）下得到的最大价值（最高分数），我们只需要知道在容量v下可以得到的最大价值。所以现在的f[100002]就是代表在多少容量（时间）下可以得到的最高价值（分数）。其余都和上面的背包模板一样。

---
好，现在就是完全背包了

下面是AC代码

```cpp
#include<iostream>
    using namespace std;
    int x,y;
    int t[10002],p[10002];
    int f[10002];
    int main()
    {
        int m,n;
        cin>>m>>n;
           for(int i=1;i<=n;i++){
              cin>>p[i]>>t[i];
           }
        for(int i=1;i<=n;i++){
            for(int t1=t[i];t1<=m;t1++){//注意这一行
                f[t1]=max(f[t1],f[t1-t[i]]+p[i]);
            }
        }
        cout<<f[m];
        return 0;
    }

```

也许没有我的“注意这一行”，你可能找不出来它和上面的01背包代码有什么区别。这也正说明了完全背包和01背包的相似。他们的差别只有第二重for循环的差别。

在01背包中，t1从m一直减到t【i】，保证了每个物品在一个t1中只会被放一次。 而完全背包中，从t1一直加到m，使在可以放下的情况下尽量多地放。


---

## 作者：SLYZ_0120 (赞：28)

蒟蒻的第七篇题解-关于完全背包模板题（逃）


首先这道题题面很明确的说明了每一种类的题目是没有限定数量的，也就是无限次取，所以说就是一道裸的完全背包(楼下的dalao早已看破)，所以读入时间V和种类n后，利用a数组存放分数，也就是价值，b数组存放时间，也就是代价，这里是一个坑，就是因为两个看反了，本蒟蒻硬是卡了10分钟。用一维数组f来存放当时间为耗时为k的时候所得到的最多的分数，状态转移方程为f(k) = max(f(k),f(k-b(j)+a(j)) ，最后输出f(V)就可以了

**这道题目的坑点**

- 先输入的不是常规意义上的代价而是价值，不要看反了

- 种类没有规定的数量不是01背包（虽然可以转换但是本蒟蒻还是建议直接用完全背包）


下面附上代码

```cpp
//防伪标识
#include<bits/stdc++.h>
using namespace std;
int V, n;
int a[10001],b[10001],f[10001]; //根据题目数据范围开数组，大一点的数组建议开全局
int main(){
    cin >> V >> n; //输入时间，种类
    for(int i = 1;i<=n;i++)
        scanf("%d %d",&a[i],&b[i]); //这里要注意a数组为价值b数组为代价！！！
    for(int j = 1;j<=n;j++)
        for(int k = b[j];k<=V;k++) //从0开始也可以记得加上判断防止k-b(j) < 0
            f[k] = max(f[k],f[k-b[j]]+a[j]); //状态转移方程一定不要把代价和价值弄反！！！一定！
    printf("%d",f[V]);
    return 0;
}
```

---

## 作者：傅思维666 (赞：16)

# 这里想向大家介绍，完全背包的二进制优化。

完全背包的接替模型其实是直接转换成01背包，因为总体积是V，对于每种种类，最多只能放V/v[i]个物品，就可以直接转换成01背包。

但是这个转换很麻烦，如果再放到一维数组，很容易爆炸，所以我们使用二进制思想进行优化。

本蒟蒻现在才发现，二进制思想是一个很有用的东西，就拿这道题来说，我们可以把刚才的n个满足V/V[I]种类的物品给压缩，怎么做呢？

举个例子：
V=22，v[i]=3,w[i]=2;

用刚才说的V/v[i]就拆成了7个相同的物品。

用二进制优化呢？

我们就可以拆成空间为v[i]*2^k，价值为w[i]*2^k的若干件物品，其中k满足小于V的要求。

所以用这种方法，我们就一共拆出来了3件物品，仅仅三件！！！

体积为3，6，12，价值为2，4，8.

可能你会问，那假如我想取九，上面的方法就能办到，这个就不行啊？

3+6=9，不用谢我，因为01背包我可以选很多物品。

所以我们就用这种方法做到了优化版本的完全背包，但是这道题完全没必要，我就是欠了吧唧的过来说一嘴，**求管理给过。**

祝大家生活愉快。。
——FSW

---

## 作者：ღ﹏ﻬ北❦栀 (赞：9)

此题呢，我不想多说，当我看到这是USACO的题目时我以为很难，不过当我仔细看题时，却发现这完完全全就是一道完全背包的模板题。

好了，话不多说，下面附代码：
```cpp
#include<bits/stdc++.h> 
using namespace std;
const int maxm=100000,maxn=100000;//利用宏定义来解题，就不用担心在运行时会出错。
int m,n,v,i;
int c[maxn],w[maxn];
int f[maxm];
int main()
{ //freopen("inflate.in","r",stdin);
//freopen("inflate.out","w",stdout);
scanf("%d%d",&m,&n);
for(i=1;i<=n;i++)
scanf("%d%d",&c[i],&w[i]);
for(i=1;i<=n;i++)
for(v=w[i];v<=m;v++)
if(f[v-w[i]]+c[i]>f[v])f[v]=f[v-w[i]]+c[i];
cout<<f[m];
return 0;
}
```


---

## 作者：乒乓高手 (赞：6)

第一眼看这个题，被题目给骗了；

居然以为是01背包，而且很傻的认为样例是错的（可笑）；

调试了好长时间，发现是一个完全背包（尴尬）；

由于是不限数量的，所以我们的第二个循环要从T[I]开始；

看底下有人说是01背包，我呵呵一笑，和我一样啊；

状态转移方程：  f[j]=max(f[j],f[j-t[i]]+v[i]);

解释：把取和不取找一个最大值

以下是我的C++代码；



```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>//头文件不要在意
#define maxn 10100
using namespace std;
int t[maxn],v[maxn],f[maxn];//F数组开成一维的就好
int main()
{
    int m,n;
    cin>>m>>n;
    for(int i=1;i<=n;i++)
       cin>>v[i]>>t[i];//输入
    for(int i=1;i<=n;i++)
      for(int j=t[i];j<=m;j++)
        f[j]=max(f[j],f[j-t[i]]+v[i]);//这是代码的核心，状态转移方程
    cout<<f[m];//输出
    return 0;//完美结束
}

```

---

## 作者：vibrant72 (赞：5)

# 竞赛总分

#### 题目描述

学生在我们USACO的竞赛中的得分越多我们越高兴。
我们试着设计我们的竞赛以便人们能尽可能的多得分,这需要你的帮助。
我们可以从几个种类中选取竞赛的题目,这里的一个"种类"是指一个竞赛题目的集合,解决集合中的题目需要相同多的时间并且能得到相同的分数。你的任务是写一个程序来告诉USACO的职员,应该从每一个种类中选取多少题目,使得解决题目的总耗时在竞赛规定的时间里并且总分最大。输入包括竞赛的时间,M(1 <= M <= 10,000)(不要担心,你要到了训练营中才会有长时间的比赛)和N,"种类"的数目1 <= N <= 10,000。后面的每一行将包括两个整数来描述一个"种类":
第一个整数说明解决这种题目能得的分数(1 <= points <= 10000),第二整数说明解决这种题目所需的时间(1 <= minutes <= 10000)。
你的程序应该确定我们应该从每个"种类"中选多少道题目使得能在竞赛的时间中得到最大的分数。
来自任意的"种类"的题目数目可能是任何非负数(0或更多)。
计算可能得到的最大分数。 

##### ·（看到这里感觉是个背包，qwq）

#### 输入

第 1 行: M, N--竞赛的时间和题目"种类"的数目。
第 2-N+1 行: 两个整数:每个"种类"题目的分数和耗时。

#### 输出

单独的一行包括那个在给定的限制里可能得到的最大的分数。

#### 样例输入

```
300 4
100 60
250 120
120 100
35 20
```

#### 样例输出

```
605
```

------

## 思路

这道题目么，是让我们求的是最大的分数，看到这个数据范围也只有二维DP。
$$
O(N^2)过万吧，没问题的。
$$

- [x] `其实我还见过`


$$
O(N^2)过百万的呢。
$$
**让我们来分析这个二维DP：**

题目说的竞赛时间其实转换成背包问题就是背包的容量，N表示有N件物品

每件物品有质量和体积。他说要最多，不可能只选一组的，所以这也能选一些。其实这些物品的总价值就是所给数据的答案。

所以正解是完全背包啊。（完全背包是什么请参考百度百科）

[完全背包]: https://baike.baidu.com/item/%E5%AE%8C%E5%85%A8%E8%83%8C%E5%8C%85/7066689?fr=aladdin

**具体一点的呢？**

***等一下别急。***

来讲一下完全背包。

#### 首先先将二维的打法：

设fij还是表示前i件物品放入一个为j容量的背包获得的最大价值,为第i件物品的是否选择的方案.

然后可以得出状态转移方程式：

当这件物品选的时候

```cpp
f[i][j] = f[i][j-a[i]]+w[i];
```

选的时候就把a[i]这个耗时给减掉再加上得分。

当这件物品不选的时候

```cpp
f[i][j] = f[i-1][j];
```

不选的时候就保留上一个的最优解.

于是这个代码架构就出来了。

```cpp
for(int i = 1; i <= n ; i++){
        for(int j = 1; j <= m ;j++){
            if(j < a[i]) f[i][j] = f[i-1][j];
            else if(f[i-1][j] > f[i][j-a[i]]+w[i]) f[i][j] = f[i-1][j];
            else f[i][j] = f[i][j-a[i]]+w[i];
        }
    }
```

循环 i -> n:

​		 循环 j -> m

当j < a[i] 的时候，已经确保了最优解于是不选。

当上一个的最优解已经大于当前解的话，那么也是可以不选的。

其他情况都要选。

答案放在 fnm ,输出就可以了。

放一个简介的状态转移方程：

```cpp
f[i][j]=max{f[i-1][j-k*c[i]]+k*w[i]|0<=k*c[i]<=j}
```

#### 然后再讲一维的打法：

有些时候出题人很讨厌，故意让你炸内存，让二维背包不过。

这个时候要用一维的打法的（前题是二维数组大于5000 * 5000 的时候， 二维 **RE**）。

其实不用i这一维度，只用j，空间复杂度大大下降了。

循环要改一下。

1 -> n   不变

​		w[i] -> m 避免重复

一维的思路：

这件物品选：

```cpp
if(f[j-w[i]]+a[i] > f[j]){
   	f[j] = f[j-w[i]]+a[i];
 }
```

当前的大于之前的则更新。

否则不干。

不选的情况：没有处理。

一维的代码架构就出来了：

```cpp
for(int i = 1; i <= n ; i++){
        for(int j = w[i]; j <= m ;j++){
            if(f[j-w[i]]+a[i] > f[j]){
                f[j] = f[j-w[i]]+a[i];
            }
        }
    }
```

综合一下上面的状态转移方程

```cpp
f[j] = max(f[j],f[j-w[i]]+a[i]);
```

答案存在f[m]输出就可以了。

- （确实一维要好打的多，其实一样啊）

## 总结

针对不同的题目使用不同的代码。

这道题为了内存，我还是写了一维过了。

二维jj 91 分 ，见祖宗啊。

归根到底这只是一道完全背包的模板题，最后以排名第一的成绩A了。

- （我太弱了，还要。。。qwq）

学习完全背包要懂得：

- [x] 什么是动态规划。

- [x] 什么是递推算法。
- [x] 什么是记忆化搜索。
- [x] 什么是递归算法。

才能更好的理解。

## End.

---

## 作者：Wahacer (赞：5)

仔细看题啊各位dalao

想板刷洛谷的dalao，这道题不是前面的01背包，是给了一个类型的题和对应花费的时间，所以我们要考虑一下在这个类型中要选多少道题，所以就是完全背包模型，无限个药，价值和体积已经给定了

转移方程就是f[i]=max(f[i],f[i-w[i]]+val[i])

正向一维递推就好了

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<iostream>
using namespace std ;
template<class T>void read(T &x){
    x=0;int f=0;char ch=getchar();
    while(ch<'0'||ch>'9'){f|=(ch=='-');ch=getchar();}
    while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
#define maxn 100010
int M,N,val[maxn],w[maxn],f[maxn];
int main()
{
    read(M),read(N);
    for(int i=1;i<=N;i++) read(val[i]),read(w[i]);
    for(int i=1;i<=N;i++)
        for(int j=w[i];j<=M;j++)
            f[j]=max(f[j],f[j-w[i]]+val[i]);
    printf("%d",f[M]);
    return 0 ;
}
```

---

## 作者：Ryang (赞：3)

# 没有用完全背包！！！
自创背包，优化了一下，好说歹说可以过，简单讲一下思路。
#### 既然也是取东西那就会出现很多种情况，在01中是取0件到取1件，那么~~完全背包~~就是取0件到取n件，那我们就把状态转移方程简单改一下，如下面magic key部分再加上循环从0到最大可取件数都用背包模拟一遍就好。（第一次讲，可能讲的不太好，谅解）
下面黏上代码
```cpp
#include<iostream>
#include<stdio.h>
using namespace std;
int w[10001],c[10001],f[10001];
int main(void){
	int  n,v;
	cin >> v >> n;
	for(int i = 1; i <= n; i++){
		scanf("%d %d",&w[i],&c[i]);
	}
	int i = 1;
	int j = 1;
	int k = 1;
	while(i <= v){
		j = 1;
		while(j <= n){
			k = 1;
			while(k * c[j] <= i){
         		   	//magic key
				f[i]=max(f[i],k*w[j]+f[i-k*c[j]]);
				k++;
			}
			j++;
		}
		i++;
	}
	cout << f[v];
	return 0;
}
```


---

## 作者：MaverickT (赞：2)

一只准备考usaco的蒟蒻过来报道

---------------

这道题说白了就是[疯狂的采药](https://www.luogu.org/problem/P1616)

当 第i种草药采了n次时，草药种类增加1，时间增加n×t[i]，价值增加n×p[i] 

当 第i种试考了n次时，考试种类增加1，时间增加n×t[i]，分数增加n×p[i] （对称狂魔

所以
```cpp
f[i][j]=f[i-1][j-n×t[i]]+n×p[i]
```
整理得：
```cpp
f[i][j]=max(f[i−1][j],f[i−1][j−n×t[i]]+n×p[i])
```
但是很明显空间要炸

改成一维

f[j]=max(f[j],f[j−t[i]]+p[i])
----------
代码如下

```cpp
//疯狂采药+总分
#include <iostream>
#include<cstdio>
using namespace std;
const int mx=10010;
long long typedef ll;
int tim,n;
ll w[mx],t[mx],f[mx];
int Max(int a,int b){//学长说自己打快一些
	return a>b?a:b;
}
int main() {
	std::ios::sync_with_stdio(false);//加速
	cin>>tim>>n;
	for(int i=1;i<=n;i++){
		//cin>>w[i]>>t[i];//采药就用这个
		cin>>t[i]>>w[i];
	}
	for(int i=1;i<=n;i++)
		for(int j=t[i];j<=tim;j++)
		f[j]=Max(f[j],f[j-t[i]]+w[i]);//转移方程
		cout<<f[tim];
	return 0;
}
```




---

## 作者：康娜卡姆依 (赞：1)

楼下就一个Pascal,我想我写的可能更清晰明了点。

---------------------------

完全背包基本思路:（来自百度）

```cpp
　　    这个问题非常类似于01背包问题，所不同的是每种物品有无限件。也就是从每种物品的角度考虑，与它相关的策略已并非取或不取两种，而是有取0件、取1件、取2件……等很多种。如果仍然按照解01背包时的思路，令f[i][v]表示前i种物品恰放入一个容量为v的背包的最大权值。仍然可以按照每种物品不同的策略写出状态转移方程，像这样：f[i][v]=max{f[i-1][v-k*w[i]]+k*c[i]|0<=k*w[i]<= v}。
　　将01背包问题的基本思路加以改进，得到了这样一个清晰的方法。这说明01背包问题的方程的确是很重要，可以推及其它类型的背包问题。
```
```pascal
uses math; //为后面的max函数调用math库
var
 i,v,k,n,m:longint;
 f:array[0..10000000]of longint; //根据题意开数组
 w,c:array[0..100000]of longint;
begin
  fillchar(f,sizeof(f),0); //习惯把数组初始化是一件好事，尤其是c++选手
  readln(m,n); // //背包容量m和物品数量n
  for i:=1 to n do
    readln(c[i],w[i]); //完全背包中每个物品的重量和价值
  for i:=1 to n do   // f(v)表示重量不超过v公斤的最大价值
    for v:=w[i] to m do
     f[v]:=max(f[v],f[v-w[i]]+c[i]);//不需用if语句，函数搞定，C++调用algorithm库
  writeln(f[m]); //输出答案
end.
```

---

## 作者：郑翔弈 (赞：1)

```cpp
#include<stdio.h>
int max(int a,int b)//max函数，用于比较
{
    if(a>b) b=a;
    return b;
}
int main()
{
    int i,j;//循环控制变量
    int t,m;
    scanf("%d %d",&t,&m);//读入
    int w[30000];
    int v[30000];
    int f[30000];
    for(i=0;i<m;++i){
        scanf("%d %d",&v[i],&w[i]);//读入
        for(j=w[i];j<=t;++j){
            f[j]=max(f[j],f[j-w[i]]+v[i]);//状态转移方程
        }
    }
    printf("%d",f[t]);//输出f[t]的值
    return 0;//结束
}
```

---

## 作者：cheeseYang (赞：1)

总思路：与之前做的dp题目不同的是，本题的每种题目的数量限制没有要求，也就是说每种题目可以无限次的做，这样一来，我们的最优方案就要稍稍改变一下，可以参考另外两题“采药”与“疯狂的采药”来加深理解

代码如下：

    
    
    
    
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,t[10050],p[10050],f[10050];
int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++)
        cin>>p[i]>>t[i];
    for(int i=1;i<=n;i++)
        for(int j=t[i];j<=m;j++)       (从最小开始往最大循环，因为j必须要大于要写的题目的时间才能拿到对应分数，所以从t[i]开始循环）
            f[j]=max(f[j],f[j-t[i]]+p[i]);    
    cout<<f[m];
    return 0;
}
```

---

## 作者：wzh1120 (赞：1)

废话不多说，这个题目是一个典型的完全背包问题，题解代码如下：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int a[10009],b[10009],f[10009];
int i,n,j,m;
int main()
  {
      cin>>n>>m;  //输入竞赛的时间和题目"种类"的数目。
      for(i=1;i<=m;i++)cin>>a[i]>>b[i];  //输入每个"种类"题目的分数和耗时
      for(i=1;i<=m;i++)
        for(j=b[i];j<=n;j++)f[j]=max(f[j],f[j-b[i]]+a[i]);   //完全背包状态转移方程
    cout<<f[n];  //输出在给定的限制里可能得到的最大的分数
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：1)

题解by：redbag


原题解地址：http://redbag.duapp.com/?p=1389


裸的01背包，不不不，这道题其实是裸的完全背包，n是题目种类又不是题目数量，一种题可以有很多道的。

/\*
ID: ylx14271

PROG: inflate

LANG: C++

\*/

```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int m,n,i,j;
int s,t,f[100000];
int main() 
{
    freopen("inflate.in","r",stdin);
    freopen("inflate.out","w",stdout);
    scanf("%d%d",&m,&n);
    f[0]=0; 
    for (i=1;i<=n;i++)//s分数t耗时 
    {
        scanf("%d %d",&s,&t);//读入 
        for (j=t;j<=m;j++)
        if (f[j-t]+s>f[j]) f[j]=f[j-t]+s;//比较
    }
    printf("%d\n",f[m]);//输出
    return 0;
}

```

---

## 作者：ninininininini (赞：1)

# 解题报告 P2722 总分 Score Inflation

 解题报告

---

先上题面:

```
我们可以从几个种类中选取竞赛的题目,这里的一个"种类"是指一个竞赛题目的集合,解决集合中的题目需要相同多的时间并且能得到相同的分数。你的任务是写一个程序来告诉USACO的职员,应该从每一个种类中选取多少题目,使得解决题目的总耗时在竞赛规定的时间里并且总分最大。输入包括竞赛的时间,M(1 <= M <= 10,000)(不要担心,你要到了训练营中才会有长时间的比赛)和N,"种类"的数目1 <= N <= 10,000。后面的每一行将包括两个整数来描述一个"种类":
第一个整数说明解决这种题目能得的分数(1 <= points <= 10000),第二整数说明解决这种题目所需的时间(1 <= minutes <= 10000)。
你的程序应该确定我们应该从每个"种类"中选多少道题目使得能在竞赛的时间中得到最大的分数。
来自任意的"种类"的题目数目可能是任何非负数(0或更多)。
计算可能得到的最大分数。
```

审题:

1.``使得解决题目的总耗时在竞赛规定的时间里并且总分最大``这句话告诉我们这是一道背包

2.判断:``完全背包``

  理由：

```
设有n种物品，每种物品有一个重量及一个价值。但每种物品的数量是无限的，同时有一个背包，最大载重量为M，今从n种物品中选取若干件(同一种物品可以多次选取)，使其重量的和小于等于M，而价值的和为最大。
```

这是完全背包;

题面中:``从每一个种类中选取多少题目``所以说数量是无限的

ok,then start!

```
#include<bits/stdc++.h>
#define _for(i,a,b) for(int i=a;i<=b;i++)
#define _jfor(i,a,b) for(int i=a;i>=b;i--)
int w[101100],v[101100];
int dp[1010][1010];
using namespace std;
int main()
{
    int m,n;
    cin>>n>>m;
    _for(i,1,m)
    {
        cin>>w[i]>>v[i];
    }
    _for(i,1,m)
      _jfor(j,n,0)
        for(int k=0;k*w[i]<=j;k++)
        {
            dp[i][j]=max(dp[i-1][j],dp[i-1][j-k*w[i]]+k*v[i]);
        }
    cout<<dp[m][n];
    return 0;
}
```

其实就是把完全背包写一遍
~~好像没过~~

##### 对于完全背包

$$
\because m=w_{total},n=v_{total}
$$



$$
\because 0\leqslant  k\leqslant n\div v_i
$$

$$
\therefore dp_{i,j}=\max(dp_{i,j},dp_{i-1,j-k\cdot v_i}+k\cdot w_i)
$$

```cpp
\\代码实现
for (int i = 1; i < n; i++)
{
   for (int j = 1; j <= v; j++)
   {
     for (int k = 0; k*c[i] <= j; k++)
     {
　　  if(c[i]<=j)/*如果能*/ f[i][j]=max{f[i][j],f[i-1][j-k*c[i]]+k*w[i]};
　 　 else/*放不下的话*/ f[i][j]=f[i-1][j]；
     }
   }
}
```

$$
\therefore dp_{i,j}=max(dp_{i-1,j},dp_{i,j-v_i}+w_i)
$$

```cpp
\\代码实现
for (int i=1;i<=n;++i){
    for(int j=1;j<=v;++j){
        if(c[i]<=j)
            f[i][j]=max(f[i-1][j],f[i][j-c[i]]+v[i]);
        else
            f[i][j]=f[i-1][j];
    }
}
```

$$
\therefore dp_j=\max(dp_j,dp_{j-v_i}+w_i) (1W)
$$

```cpp
\\代码实现
for (int i=1;i<=n;++i){
    for(int j=w[i];j<=v;++j){
        f[j]=max(f[j],f[j-c[i]]+v[i]);
    }
}
```

---

the End



~~求过~~





---

## 作者：renyifan010410 (赞：1)

就是一个裸的**完全背包**，考虑到Pascal程序较少，发一个比较简练的（话说NOIP2017初赛第一题就是Pascal什么时候废2333~）

贴代码：

```pascal
program p2722;
var f,a,b:array[0..10000] of longint;
    n,m,i,j:longint;
function max(x,y:longint):longint;
begin
  if x>y then exit(x);
  exit(y);
end;
begin
  readln(m,n);
  for i:=1 to n do read(a[i],b[i]);
  for i:=1 to n do
    for j:=b[i] to m do
        f[j]:=max(f[j],f[j-b[i]]+a[i]);
  write(f[m]);
end.  
```

---

## 作者：Dr_殇 (赞：1)

#这是一道DP题，刚开始的时候，还把这道题看成了贪心，做了很久都没过。后来，我发现，这道题是一道简单的完全背包题。


##注意了，很多新人都会把这题看成01背包，这样做就错了。因为题目说每一个种类，而不是只能用一次。


##状态转移方程：ans[j]=max(ans[j],ans[j-mark[i].t]+mark[i].m)，不要直接抄，好好想想状态转移方程怎么来的。


##代码如下:






```cpp
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>//头文件准备
using namespace std;
int n,s,ans[10005];//ans存储答案
struct Mark{//刚开始当成贪心了，后来懒得改，就定义了一个结构体
    int t;
    int m;
}mark[10005];
int main(){
    freopen ("2722.in","r",stdin);
    freopen ("2722.out","w",stdout);//输入输出，不解释
    scanf ("%d %d",&s,&n);//读入题目的种类和给你的时间
    for (int i=1;i<=n;i++){
        scanf ("%d %d",&mark[i].m,&mark[i].t);//读入每种题目所需的时间和它的分数
    }
    for (int i=1;i<=n;i++){
                  for (int j=mark[i].t;j<=s;j++){
            ans[j]=max(ans[j],ans[j-mark[i].t]+mark[i].m);//状态转移方程
        }
    }
    printf ("%d\n",ans[s]);//最后输出
        while (1);//反抄袭
    return 0;
}
#珍爱生命，拒绝抄袭！
```

---

## 作者：Atmizz (赞：0)

## 裸的完全背包问题！！
看题面，与01背包不同的是，题可以做许多次，不仅仅只能做一次，所以是完全背包问题。但是，我们可以转化为简单的01背包问题.

完全背包状态转移方程依然为：
```cpp
	f[j]=max{f[j],f[j-k*c]+k*w}(0<=k*c<=v)
```
我们可以进行优化，优化后的伪代码为：
```cpp
	for i=1..N

	for j=c..V

	f[j]=max{f[j],f[j-c]+w}
```
### 所以，code：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m,mi,po,f[999999];//数组其实可以开小一点
int main()//n是指个数，m是时间
{//mi是各个题目需要的是时间，po是各个题目的得分
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++) {//完全线上操作
		scanf("%d%d",&po,&mi);
		for(int j=mi;j<=m;j++)//进行枚举
			f[j]=max(f[j],f[j-mi]+po);//方程
	}
	printf("%d",f[m]);//输出
	return 0;\\防抄袭puls
}
```

---

## 作者：freesaber (赞：0)

经典完全背包。
为什么呢？因为题目并没有说同样分值和 耗时的题只有一道，所以这里认为右无数个分值耗时一样的题目。
代码如下
```
#include<cstdio>
#include<algorithm>
using namespace std;
int m,n,v[10005],f[10005],c[10005];
int main()
	{
		scanf("%d%d",&m,&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&v[i],&c[i]);
		for(int i=1;i<=n;i++)
			{
				for(int j=c[i];j<=m;j++)
					f[j]=max(f[j],f[j-c[i]]+v[i]);
			}
		printf("%d",f[m]);
		return 0;
	}
```
第一次题解多多关照

---

## 作者：xy_xw_for_2024 (赞：0)

### 咕值下降了QAQ
为了提升名次，此蒟蒻又来发一篇题解：总分  
这道题，我开始想多了，于是把他当做混合背包问题来想，然后就在自己的OJ上愉快超时。。。。。。  
然后我以为是数组开小了，内存又爆了一遍。。。。。。  
其实就是一个完全背包问题，下面给出状态转移方程：  
dp[j]=max(dp[j],dp[j-a[i].t]+a[i].w);  
其中t代表用时，w代表得分。  
还是先上代码：
```
#include<cstdio>
#include<iostream>
using namespace std;
inline void read(int &x) {
    x=0;int f=1;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9')x=x*10+s-48,s=getchar();
    x=x*f;
}
inline void pr(int x) {
    if(x<0)putchar('-'),x=-x;
    if(x>9)pr(x/10);
    putchar(x%10+48);
}//快读快输不解释
struct node{
    int t,m;
}a[10005];
int dp[10005],i,n,j,k,m;
int main() {
    read(m),read(n);
    for(i=1;i<=n;i++)
        read(a[i].m),read(a[i].t);
    for(i=1;i<=n;i++)
        for(j=a[i].t;j<=m;j++)
            dp[j]=max(dp[j],dp[j-a[i].t]+a[i].m);//就是一个典型的完全背包
    pr(dp[m]);
}
```
补充一点，用#include<iostram>里面的max和min会快一些但为了保险，建议大家这样写：
```
inline int max(int x,int y) {
    return x>y?x:y;
}
```
大概就是这个样子，不懂的可以一起讨论一下  
  ~~(求过)~~

---

## 作者：cenbinbin (赞：0)

赤裸裸的完全背包，简单。。。

======================================================================

```cpp
var
  f:array[0..100001] of longint;
  n,m,i,j,x,y:longint;
begin
  readln(m,n);//读入
  for i:=1 to n do
   begin
     readln(y,x);
     for j:=x to m do//完全背包
      if f[j-x]+y>f[j] then f[j]:=f[j-x]+y;
   end;
  writeln(f[m]);//输出
end.
```

---

## 作者：24680esz (赞：0)

就是普通的完全背包，没有什么可讲的

```cpp
#include <iostream>
using namespace std;
int t,m,w[100001]={0},v[100001]={0},f[100001]={0};//一维动归，压缩空间
int main()
{
    cin>>t>>m;
    for (int i=1;i<=m;i++) cin>>v[i]>>w[i];
    for (int i=1;i<=m;i++)
      for (int j=w[i];j<=t;j++)
        if (f[j]<=f[j-w[i]]+v[i]) f[j]=f[j-w[i]]+v[i];//转换方程式
    cout<<f[t]<<endl;
    return 0;
}
```

---

## 作者：Celebrate (赞：0)

这一道题就是一道很简单的背包

我本来想先排一次序然后for一遍求，虽然只花费了8ms，但这样会错两个点，原因

是划得来的不一定取尽可能多，假如数据太大，也就只能这样做了

不罗嗦了，言归正传，这一道题先枚举每一个重量单位，再枚举一次时间，假如可

以这样做就取最优值

初始化：

memset(f,-1,sizeof(f));f[0]=0;

DP公式：

if(f[j-a[i]]>0) f[j]=max(f[j],f[j-a[i]]+b[i]]);

f[i]表示用i的时间能取得的最大分值

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std; 
int main() 
{ 
    int t[11000],m[11000],n,v,i,j; 
    int f[11000];memset(f,-1,sizeof(f));f[0]=0; //初始化 
    scanf("%d%d",&v,&n); 
    for(i=1;i<=n;i++) scanf("%d%d",&m[i],&t[i]); //输入 
    for(i=1;i<=n;i++) 
    { 
        for(j=t[i];j<=v;j++) //因为可以自己叠加自己，所以正着求值 
        { 
            if(f[j-t[i]]!=-1) //刚才说的DP公式 
            { 
                f[j]=max(f[j],f[j-t[i]]+m[i]); 
            } 
        } 
    } 
    int x=f[1]; //因为f[v]不一定是最大的 
    for(i=2;i<=v;i++) x=max(x,f[i]); 
    printf("%d",x); 
    return 0; 
} 
```

---

## 作者：✌yww (赞：0)

简单dp01问题，状态dp[j]表示用i个物体来装容积j所得最大价值dp[j]=max(dp[j],dp[j-t[i]]+p[i]);

状态转移方程

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;
int M,N;
int dp[12000];
int p[10005],t[10005];
int main()
{
    scanf("%d %d ",&M,&N);
    for(int i=1; i<=N; i++)
        scanf("%d %d",&p[i],&t[i]);
    for(int i=1; i<=N; i++)
    {
        for(int j=t[i]; j<=M; j++)
        {
            dp[j]=max(dp[j],dp[j-t[i]]+p[i]);
        }
    }
    printf("%d",dp[M]);
    return 0;
}

```

---

