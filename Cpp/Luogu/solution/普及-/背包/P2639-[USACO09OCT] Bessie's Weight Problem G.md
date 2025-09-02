# [USACO09OCT] Bessie's Weight Problem G

## 题目描述

Bessie 像她的诸多姊妹一样，因为从 Farmer John 的草地吃了太多美味的草而长出了太多的赘肉。所以 FJ 将她置于一个及其严格的节食计划之中。她每天不能吃多过 $H (5 \le H \le 45,000)$ 公斤的干草。 Bessie 只能吃一整捆干草；当她开始吃一捆干草的之后就再也停不下来了。她有一个完整的$N (1 \le N \le 500)$ 捆可以给她当作晚餐的干草的清单。她自然想要尽量吃到更多的干草。很自然地，每捆干草只能被吃一次（即使在列表中相同的重量可能出现2次，但是这表示的是两捆干草，其中每捆干草最多只能被吃掉一次）。 给定一个列表表示每捆干草的重量 $S_i (1 \le S_i \le H)$ , 求 Bessie 不超过节食的限制的前提下可以吃掉多少干草（注意一旦她开始吃一捆干草就会把那一捆干草全部吃完）。

## 说明/提示

#### 输入说明

有四捆草，重量分别是 $15,19,20$ 和 $21$。Bessie 在 $56$ 公斤的限制范围内想要吃多少就可以吃多少。


#### 输出说明

Bessie 可以吃 $3$ 捆干草（重量分别为 $15, 20, 21$）。恰好达到她的 $56$ 公斤的限制。


## 样例 #1

### 输入

```
56 4
15
19
20
21```

### 输出

```
56```

# 题解

## 作者：青珹 (赞：35)

其实刚开始做这道题时，我以为这和01背包不一样——毕竟**只有体积而没有价值**。

但是——我再去想它和01背包有什么相同点时，我发现：只不过01背包是在**体积满足时**找**最大价值**，而这道题是在**体积满足时**找**最大体积**。

那么问题来了：**假如我们换个思路**，将这道题的每个干草也**赋予它自己的价值**，那岂不是**变得和01背包一模一样了**？？

nice~~

那我们赋予每一个干草的价值是什么呢？？答案显而易见：**就是它自己的体积！！**

nice~~

上代码：（先看**01背包**的代码）：

```cpp
#include<iostream>
using namespace std;
int f[45001]={0},w[10001]/*价值*/,c[10001]/*重量*/,n,m;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i]>>w[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=c[i];j--)
		{
			if(f[j-c[i]]+w[i]>f[j])
			f[j]=f[j-c[i]]+w[i];
		}
	}
	cout<<f[m];
	return 0;
}
```

然后再来**本题**AC代码：

```cpp
#include<iostream>
using namespace std;
int f[45001]={0},w[10001]/*价值*/,c[10001]/*重量*/,n,m;
int main()
{
	cin>>m>>n;        //不同之处1：输入顺序变了
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		w[i]=c[i];   //不同之处2：直接赋值而非输入！
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=c[i];j--)
		{
			if(f[j-c[i]]+w[i]>f[j])
			f[j]=f[j-c[i]]+w[i];
		}
	}
	cout<<f[m];
	return 0;
}
```

有心者可以将两段代码对比一下，即可发现两题是多么相似！！

---

## 作者：ysy666 (赞：21)

看到很多人用的都是01背包的算法，其实这道题还有一种简单点的方法；

从1到n扫一遍，把所有可能出现的情况在一个bool数组中标记出来；

最后从v到0跑一遍，找到的第一个非零的值，此时i为最大值；



下面贴代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[600];
bool t[100000];//t作为一个标记，统计所有可能出现的情况 
int main()
{
    int h,n;
    cin>>h>>n;
    t[0]=1;
    for(int i=1;i<=n;i++)  cin>>a[i];
    for(int i=1;i<=n;i++)//枚举所有可能达到的情况 
        for(int j=h;j>=0;j--)  if(t[j])  t[j+a[i]]=1;//j循环一定要倒着跑！ 
    for(int i=h;i>=0;i--)  if(t[i])//从最大值开始找，一旦找到一个非0的t，这时候的i就是答案 
    {
        cout<<i;//输出答案 
        return 0;//剩下的就没必要找了，直接结束程序 
    }
}
```

---

## 作者：2016jzy (赞：9)

这题其实就是01背包，跟装箱问题类似。。

可以把每一捆干草的重量，看成吃这一捆的价值，然后把二维优化成一维，就AC啦~

```cpp
#include<iostream>      //头文件
using namespace std;
int n,m,a[10001],b[10001],f[100001]={0};     //要注意数据范围
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i];        //输入每一捆干草的数量
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=n;j>=a[i];j--)
        {
            if(f[j]<=f[j-a[i]]+a[i])f[j]=f[j-a[i]]+a[i];    //因为数据过大，所以要记得优化成一维的
        }
    }
    cout<<f[n]<<endl;            //输出结果
    return 0;
}
由于是第一次写题解，可能写得不太好，望谅解。。。
```

---

## 作者：Atmizz (赞：4)

## 不算很裸的01背包！！
先看一下题目，题目中求的是吃的最大重量，我们可以设想为“重量==价值”，也就是说value=干草的质量，weight=干草的质量，于是我们就转化为了简单的01背包问题，然后就可以套状态转移方程：
```cpp
	f[i][v]=max{f[i-1][v],f[i-1][v-c[i]]+w[i]}
```
然后就会发现内存会爆炸，于是乎~我们转化一下，就得到了另一个状态转移方程：
```cpp
	f[v]=max{f[v],f[v-val]+val};
```
好，一切准备就绪，全部代码上场。
## code：
```cpp
  #include<cstdio>
  #include<iostream>
  #include<cmath>
  using namespace std;
  int n,m,val,f[45001];//数组开大，不然会运行错误（别问我咋知道的）
  int main()
  {
      scanf("%d%d",&m,&n);//m表示容量，n表示物品个数
      for(int i=1;i<=n;i++) {//完全可以线上计算
          scanf("%d",&val);//输入价值也就是质量
          for(int v=m;v>=val;v--)//枚举
              f[v]=max(f[v],f[v-val]+val);//状态转移方程
      }
      printf("%d",f[m]);//输出
      return 0;我可以防抄题解
  }
```

---

## 作者：fighter_OI (赞：4)

裸的存在性背包不说

翻了一下题解没有bitset优化？

那就上一个，用bitset优化转移
```cpp
#include<iostream>
#include<bitset>
using namespace std;
int a[600];
bitset<100000>t;
int main()
{
    int h,n;
    cin>>h>>n;
    t[0]=1;
    for(int i=1;i<=n;i++)cin>>a[i],t|=t<<a[i];//bitset优化转移
    for(int i=h;i>=0;i--)  
    if(t[i])
    {
        cout<<i;
        return ~~(0-0);//恶意卖萌
    }
}
```

---

## 作者：moye到碗里来 (赞：3)

这道题，其实就是01背包的一种变形，刷水题的时候看到的= =，对于这种题，其实可以转换为01背包求**方案总数**，那么先设f[0]=1;然后转移的时候直接加就是方案数，如果是完全背包呢？就用完全背包的写法，同样转移直接加

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int w[1000];
int f[50000];
int main()
{
    scanf("%d %d",&m,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&w[i]);
    }
    f[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=w[i];j--)
        {
            f[j]+=f[j-w[i]];
        }
    }
    for(int i=m;i>=1;i--)
    {
        if(f[i])
        {
            printf("%d",i);
            return 0;
        }
    }
}
```

---

## 作者：VenusM1nT (赞：3)

粗略看了下 发现一些dalao的想法略复杂

这道题严格来说都不能算一道01背包

因为没有价值

只是一道简单的装箱问题稍微改了一下题面（doge

所以是一道dp的新手题目

状态转移方程： $f[j]=max(f[j-a[i]]+a[i],f[j])$

答案在 $f[v]$ 的位置


具体见代码





```cpp
#include<cstdio>
#define max(x,y) x>y ? x : y
int v,n;
int a[505],f[50000];
int main()
{
    scanf("%d %d",&v,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);//输入所有题目所含的变量 
    for(int i=1;i<=n;i++)
    {
        for(int j=v;j>=a[i];j--) f[j]=max(f[j],f[j-a[i]]+a[i]);//比较标准的01背包结构 虽然这题不像01背包 
    }
    printf("%d",f[v]);//输出答案位置 
    return 0;
}
```
pascal版：

```cpp
var i,j,n,v:integer;
a:array[1..500] of integer;
f:array[1..50000] of integer;
function max(x,y:integer):integer;
begin
if(x>y) then exit(x)
else exit(y);
end;
begin
read(v,n);
for i:=1 to n do read(a[i]);
for i:=1 to n do
begin
for j:=v downto a[i] do
f[j]:=max(f[j],f[j-a[i]]+a[i]);
end;
writeln(f[v]);
end.
```

---

## 作者：霍士弘 (赞：2)

# 一道01背包
（本蒟蒻太菜了，错误难免，请dalao见谅）  
做这一道题目之前可以先做一做[P1048采药](https://www.luogu.org/problemnew/show/P1048)  
我当时做题的时候，第一眼觉得是01背包，后来我发现题目中没有*价值*，肯定不是01背包！~~（真香警告）~~ 所以我就去设计~~瞎猜~~一个适用于这一道题目的dp方程。后来发现不太对劲~~太菜了~~然后放弃了。后来我还是用了01背包~~真香！~~
## Part1 01背包模型套用
这道题怎么用01背包呢？如果我们把这一道题的节食限制看为背包容量，干草的重量看做物品重量，价值其实就是干草的重量（因为答案求的就是最大重量，也就是通过价值来计算的）  
改成01背包的说法：有一个容量为$H(5 \leq H \leq 45,000)$的背包，和$N(1 \leq N \leq 500)$个物品，每个物品有一个重量$S_i$和价值$S_i(1 \leq S_i \leq H)$，（这俩一样），求不超过背包容量的情况下，将物品装入背包的最大价值。 
## Part2 状态转移方程
设$f[i][j]$ 为选择1到$i$的物品，背包容量为$j$时的最大价值。  
转移方程为：  

$f[i][j] = max(f[i-1][j],f[i-1][j - w[i] + w[i])$  
$w[i]$是干草的重量。  
## Part3 代码实现
因为题目没有卡空间，可以使用二维数组。
代码如下：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int w[505];
int f[505][45005];
int n,m;	
int main()
{
    cin>>m>>n;
    for(int i = 1;i <= n;i++) cin>>w[i];
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            if(j < w[i])
            {
                f[i][j] = f[i-1][j];
            }else
            {
                f[i][j] = max(f[i-1][j],f[i-1][j - w[i]] + w[i]);
            }
        }
    }
    cout<<f[n][m];
    return 0;
}
```
上面代码用时: 29ms / 内存: 37780KB    
一维数组优化后：  
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int w[505];
int f[45005];
int n,m;	
int main()
{
    cin>>m>>n;
    for(int i = 1;i <= n;i++) cin>>w[i];
    for(int i = 1;i <= n;i++)
    {
        for(int j = m;j >= w[i];j--)
        {
            f[j] = max(f[j],f[j - w[i]] + w[i]);
        }
    }
    cout<<f[m];
    return 0;
}
```
这个代码用时: 17ms / 内存: 912KB  
~~这个问题可以起名为吃草问题（大雾）~~

---

## 作者：傅思维666 (赞：1)

因为是裸题，所以来水一波01背包的压维优化。

博客食用口味更佳：

[背包九讲—上—简单背包](https://www.cnblogs.com/fusiwei/p/11544682.html)


## 0/1背包问题

#### 题目类型

 有$N$件物品和一个容量为$V$的背包。第$i$件物品的费体积是$v[i]$，价值是$val[i]$，求将哪些物品装入背包可使价值总和最大。

#### 问题解析

0/1背包问题是最基础的背包问题，可以这么说：0/1背包是所有背包的祖先。因为0/1背包是用线性动归的思路来求解的，而其他的背包是用0/1背包的思想来求解的。所以，为了解决这个问题，我们来用线性DP的基本内容来思考。

* **决策**

因为是动态规划，所以我们在思考的时候一定要牢记DP的两个性质：无后效性和最优子结构，也就是说，设置决策是解决动归的灵魂。回归0/1背包的问题，我们容易得出一个性质：每件物品只会面临一个决策：放还是不放。那么，我们接下来的部分就可以用这两个选择来继续进行。

* **状态**

状态的定义建立在子问题的基础上，针对0/1背包，我们的状态被设置成：$dp[i] [j]$表示前$i$件物品中任选若干件放入容量为$j$的背包所能得到的最大价值。

* **状态转移方程**

$$
dp[i] [j]=max(dp[i-1] [j],dp[i-1] [j-v[i]]+val[i])
$$

我们有必要好好理解这个方程。这个方程表示的是一个决策的过程，因为我们在决策一件物品放或不放的时候，牵扯到的数据只是在放它之前的那个状态。那么易知：如果不放的话，那$dp[i] [j]$就是$dp[i-1] [j]$，因为容量没有变，如果放了的话，那么就需要在原来的背包中腾出一个$v[i]$那么大的空位，否则这个新物品将无处可放。当然，如果放了这个物品，那么还需要加上$val[i]$。

* **答案**

综上所述，最终要求的答案就是$dp[n] [V]$。

#### 空间复杂度的优化

我们发现，上面的$dp$数组是一个二维数组，那么假如背包最大容量和物品件数都特别大的时候，这样的空间复杂度肯定会爆炸。所以我们需要采取手段来优化它的空间复杂度。01背包的空间复杂度优化方式有两种：一种是**滚动数组**优化，另一种是**压维**优化。

我们会发现，0/1背包的状态转移方程只用到了$dp[i-1] [j]$的数据。也就是说，我们在求取答案的时候，$1-(i-2)$的数据是啥用没有的。那么我们考虑不再存储这些数据，而将数组“滚动”起来，依次覆盖上一次用不着的数据，这样就可以把dp数组的第一维只开2位，而完成0/1背包的DP操作，大大地降低了空间复杂度。

在此我不讲解滚动数组的代码实现，因为特别麻烦。但是又不得不说这个滚动数组，因为这是理解下一个优化：压维的重要知识铺垫。

我们来看一下压维操作。

因为每种物品只有放或者不放这两种可能，所以我们在处理的时候可以把存物品的那一维省略，直接用背包容量来进行DP，更大地压缩了空间复杂度。

实现的时候非常简单：

```cpp
for(int i=1;i<=n;i++)
	for(int j=V;j>=v[i];j--)
		dp[j]=maxn(dp[j],dp[j-v[i]]+w[i]);
```

细心的读者可能已经注意到了，这里的第二维$j$是从$V$到$V[i]$开始枚举的。这是为什么呢？

我们的外层循环进行的是逐物品枚举，而内层循环只起到一个作用：持续更新当前容量的价值最大值。所以状态转移方程的意义就是：当前物品的放与不放是否会对当前的答案产生影响。这就是0/1背包的压维优化了。

---

综上所述，这道题可以把重量和体积划等号，然后直接应用模板解决。

代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,h;
int v[510];
int dp[45001];//dp[i]表示其在i范围内能吃多少干草
int main()
{
    scanf("%d%d",&h,&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    for(int i=1;i<=n;i++)
        for(int j=h;j>=v[i];j--)
            dp[j]=max(dp[j],dp[j-v[i]]+v[i]);
    printf("%d",dp[h]);
    return 0;
}
```

---

## 作者：yjmcreeper (赞：1)

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int main(){
  int Fat,n;
  cin>>Fat>>n;
  int hea[505];//每捆干草的重量 
  int i;
  int chi[90005];//可以吃多少干草，每捆最多45000重量（在Fat最大的情况下），由于本题利用可达求解，需考虑到极端情况：连续两个45000，故开90005） 
  for(i=1;i<=n;i++)
    cin>>hea[i];//输入
  chi[0]=1;//0斤干草是可以达到的， 
  int j;
  for(i=1;i<=n;i++)//枚举干草序号 
    for(j=Fat;j>=0;j--)//注意要循环到0，才能保证正常运算，因为每捆干草只能吃一次，因此从n到0循环 
    {
      if(chi[j]==1)//如果j斤干草可以达到 
      {
        chi[j+hea[i]]=1;//则j+hea[i]斤可以达到 
      }
    } 
  for(i=Fat;i>=0;i--)//输出符合题意的最大值 
    if(chi[i]==1)
    {
      cout<<i<<endl;
      break;
    }
  system("PAUSE");
  return 0;
}

```

---

## 作者：Keane_Bal (赞：1)

 这道题乍一看是一道01背包~~（实际上它的确是的）~~
 
**但是**
也有另一种方法

话不多说
附上代码


------------
```cpp
#include<iostream>
using namespace std;
int v,f[336699],dp[336699],n,len[336699],t,maxn,tmp;
//不习惯题目提供的变量就自己定了
int main()
{
	cin>>v>>n;
	for(int i=1;i<=n;i++)
		cin>>len[i];
    //输入部分
    
	maxn=0;
	f[0]=1;
	t=1;
	dp[0]=0;
	tmp=t;//tmp是为了解决叠加在自己的非法情况
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=t;j++)
		{
			
			if(f[len[i]+dp[j]]==0&&len[i]+dp[j]<=v)
            //dp数组中没有记录的且不大于最大食量
			{
				dp[++tmp]=len[i]+dp[j];
				f[len[i]+dp[j]]=1;
				maxn=max(maxn,dp[tmp]);
				if(maxn==v)//正好等于最大食量时直接输出
				{
					cout<<maxn;
					return 0;//退出
				}
			}
		}
		t=tmp;//将t赋上新值
	}
	cout<<maxn<<endl;
	return 0;
}
```
其实也是01背包，只是省去了一大堆判断而已，

直接加还是十分简单粗暴的。

---

## 作者：郑翔弈 (赞：1)

```cpp
#include<stdio.h>
int main()
{
    int m,n;
    scanf("%d %d",&m,&n);//读入
    int w[35000];
    int i,j;//循环控制变量
    int f[35000];//用于储存所有可行方案最大值的数组
    for(i=0;i<n;++i){
        scanf("%d",&w[i]);//读入
        f[i]=0;//初始化
        for(j=m;j>=w[i];--j){//将状态转移方程变换后的代码
            if(f[j]<f[j-w[i]]+w[i])
                f[j]=f[j-w[i]]+w[i];
        }
    }
    printf("%d",f[m]);//输出
    return 0;//结束
}
```

---

## 作者：cirnovsky (赞：0)

这是一道很好的背包练手题。

细读题目，可以发现题目中并没有给定每捆干草的价值，只给出了每捆干草的重量。

再读题目，我们发现题目求Bessie不超过节食的限制的前提下可以吃掉多少干草，所以，我们可以把每堆干草的重量看作它的的价值，这就成了一个01背包的模板了

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

namespace solv
{
	const long long MAXN = 50000 + 5;
	long long F[MAXN], w[MAXN];
	long long n, m, c[MAXN];
	
	template<typename T>
	inline T getMax(T x, T y)
		{ return x > y ? x : y; }
	
	inline void Solve()
	{
		scanf("%lld%lld", &m, &n);
		for (long long i = 1; i <= n; ++i)
			scanf("%lld", &w[i]);
		for (long long i = 1; i <= n; ++i)
			for (long long j = m; j >= w[i]; --j)
				F[j] = solv::getMax(F[j], F[j - w[i]] + w[i]);
		
		printf("%lld\n", F[m]);
	}
}

signed main()
{
	solv::Solve();
}
```

---

## 作者：青鸟_Blue_Bird (赞：0)

废话不多说，和最经典的装箱问题其实是一样的
```cpp
#include<bits/stdc++.h>
using namespace std;
#define qnmd ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int w[66666],ans[66666];
	
int main(){
	int tot,n;//tot重量上限，n数量 
	qnmd;
	cin >> tot >> n;
	for(int i = 1; i <= n; i++)
		cin >> w[i];
   //---------------
   //这里开始才是核心
	for(int i = 1; i <= n; i++)
		for(int j = tot;j >= w[i]; j--)
			ans[j] = max(ans[j], ans[j - w[i]] + w[i]);//第一个ans[j]是代表不装他时的重量。第二个为没有装他时的重量加上如果装上了它时的重量
	cout << ans[tot];
	return 0;
}
```
蒟蒻很少发题解，求大佬们勿喷

ps：两行神秘代码可以解除绑定加快输入输出，在数据多的时候很有用


---

## 作者：HPXXZYY (赞：0)

题意相当于给定一堆物品，重量等于价值，进行01背包

~~关于01背包，可自行百度。~~

一定要弄懂，这很基础、重要，尤其是优化！！！
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int f[45010],n,m,c,i,j;
int main(){
    scanf("%d%d",&n,&m);
    for(j=1;j<=m;j++){
        scanf("%d",&c);
        for(i=n;i>=c;i--)
        f[i]=max(f[i],f[i-c]+c);
    }
    printf("%d",f[n]);
    return 0;
}
```

---

## 作者：lijiahao2017 (赞：0)

# P2639 [USACO09OCT]Bessie的体重问题Bessie's We…



### 题目描述

$Bessie$像她的诸多姊妹一样，因为从$Farmer John$的草地吃了太多美味的草而长出了太多的赘肉。所以$FJ$将她置于一个及其严格的节食计划之中。她每天不能吃多过$H (5 <= H <= 45,000)$公斤的干草。 $Bessie$只能吃一整捆干草；当她开始吃一捆干草的之后就再也停不下来了。她有一个完整的$N (1 <= N <= 500)$捆可以给她当作晚餐的干草的清单。她自然想要尽量吃到更多的干草。很自然地，每捆干草只能被吃一次（即使在列表中相同的重量可能出$2$次，但是这表示的是两捆干草，其中每捆干草最多只能被吃掉一次）。 给定一个列表表示每捆干草的重量$S_i (1 <= S_i <= H)$, 求$Bessie$不超过节食的限制的前提下可以吃掉多少干草（注意一旦她开始吃一捆干草就会把那一捆干草全部吃完）。

### 输入输出格式

##### 输入格式：
* 第一行: 两个由空格隔开的整数: H 和 N * 第2到第N+1行: 第i+1行是一个单独的整数，表示第i捆干草的重量S_i。

##### 输出格式：
* 第一行: 一个单独的整数表示Bessie在限制范围内最多可以吃多少公斤的干草。

### 输入输出样例

##### 输入样例#1： 复制
$56$ $4$

$15$

$19$

$20$

$21$
##### 输出样例#1： 复制
$56$
### 说明

##### 输入说明:

有四捆草，重量分别是$15$, $19$, $20$和$21$。$Bessie$在$56$公斤的限制范围内想要吃多少就可以吃多少。

##### 输出说明:

$Bessie$可以吃$3$捆干草（重量分别为$15$, $20$, $21$）。恰好达到她的$56$公斤的限制。





最近都在做      动态规划,动规,dp      的题。

因为，我个人比较喜欢做这种题。

这种题，思维上比较有挑战性，代码却比较短。

好了，闲话少说，回归正题。

这次讲的是      背包      类型的题。

而且是属于比较简单的$01$背包。

那我们的思路是逆推，也就是搭积木，从上往下看是否可以放。

如果可以就放，否则继续往下看。

所以，要注意f[0]=1。

因为最低也就到地板。

每个都做一次之后，从上往下搜一次就可以找到结果了。

## 核心大放送：

### 先做一次01背包

### 注意f[0]=1

### 最后再从上到下扫一次



### 代码$dalao$：

```
//P2639 [USACO09OCT]Bessie的体重问题Bessie's We…

//题目提供者 FarmerJohn2
//评测方式 云端评测
//标签 动态规划,动规,dp 背包 USACO 2009
//难度 普及-
//时空限制 1000ms / 128MB

#include<cstdio>//调用      scanf和printf      的库 
#include<cstring>//调用      memset      的库 
#define ll long long//习惯定义long long 
const ll mx=510;
ll h,n;
ll a[mx],f[mx*90];
//定义变量和数组 
int main(){
	memset(f,0,sizeof(f)),f[0]=1;//清0，注意f[0]=1 
	scanf("%lld %lld",&h,&n); 
	for(ll i=1;i<=n;i++)scanf("%lld",&a[i]);
	//输入 
	for(ll i=1;i<=n;i++){//枚举每一个 
		for(ll j=h;j>=a[i];j--){//逆推 
			if(f[j-a[i]]==1)f[j]=1;//如果可以落脚就搭 
		}
	}
	//做01背包 
	for(ll i=h;i>0;i--){//从上到下 
		if(f[i]==1){ 
			printf("%lld",i);//如果有就输出 
			break;//退出 
		}
	}
	//扫一遍 
	return 0;//结束 
}
```

---

## 作者：felixwu (赞：0)

我还以为是DFS呢我的天2^200绝对TLE  
80分哈哈哈
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,a[100001],ans;
void dfs(int x,int sum)
{
	if (x==n+1) {
		if (sum<=m)
			ans=max(ans,sum);//保存数据
		return;
	}
	for(int i=0;i<=1;i++)//0，不取  1，取
		dfs(x+1,sum+a[x]*i);//下一个数
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	dfs(1,0);//DFS
	printf("%d",ans);
    return 0;
}
```
再来看100分的DP（一维01背包）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10001],b[10001],f[100001];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)
        for(int j=n;j>=a[i];j--)
			f[j]=max(f[j],f[j-a[i]]+a[i]);//状态转移方程
    printf("%d",f[n]);
    return 0;
}
```
哪里有DFS，哪里就有DP
哈哈哈哈

---

## 作者：Liangkry (赞：0)

題目中 Bessie 有 N 捆草，每捆草給出質量，

但是由於體重限制， Bessie 最多吃質量為 H 的草。

很明顯，這是動態規劃「背包問題」的經典模板。

    #include<iostream>
    #include<cstdio>
    #include<cmath>
    #include<algorithm>
    using namespace std;
    long long opt[45001];
    int main()
     {
      int i,j,total,n,mass;
      scanf("%d%d",&total,&n); //「total」為最多進食的總質量
      for(i=1;i<=n;i++)
      {
          scanf("%d",&mass); //「mass」為每捆草的質量，在此輸入，節約空間
          for(j=total;j>=mass;j--) //DP
            opt[j]=max(opt[j],opt[j-mass]+mass); //DP狀態轉移方程：opt[j]表示如果規定最多進食質量為 j 的草，那麼實際最多進食的草的質量（階段內的最優解）
      }
      printf("%lld",opt[total]); //opt[total]就係在限制範圍內能食的最多量
      return 0；
    }


---

## 作者：cheeseYang (赞：0)

总思路：简单的01背包问题，不过需要稍微加一点优化，不然数组一大会TLE

代码如下：

```cpp
#include<cmath>
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
int h,n,w[50500],f[50500];
int main(){
    cin>>h>>n;
    for(int i=1;i<=n;i++)
        cin>>w[i];
    for(int i=1;i<=n;i++)
        for(int j=h;j>=w[i];j--){                  (此处一定要倒着来，不然会出现重复吃前一捆草的现象，如果用二维数组的话可以忽略这个问题）
            f[j]=max(f[j],f[j-w[i]]+w[i]);（状态转移方程，选或者不选，如果选，就要付出相应的“代价”）
            if(f[j]==h){
            cout<<f[j];
            return 0;
            }
        }
    cout<<f[h];
    return 0; 
}
```

---

## 作者：The_Key (赞：0)

首先这题数据很水，贪心能得80.。。


其次这是一道很裸的01背包。。。


这是代码：


```cpp
#include<iostream>
using namespace std;
int n,m,fin[100008];//fin数组储存结果
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)//第一层循环
    {
        int w;
        cin>>w;//输入干草的重量
        for(int j=n;j>=w;j--)//第二重循环
        fin[j]=max(fin[j],fin[j-w]+w);//经典的01背包动态转移方程
    }
    cout<<fin[n];//输出最后结果
    return 0;
}//本人蒟蒻一只，代码不精，大神勿喷
```

---

## 作者：雄鹰展翅 (赞：0)

这道题有许多做法（但不是每一种做法都能得分）。//--出自神犇经典语录

首先，贪心。于是80分。。。

然后，DP。于是AC。。。

重量为价值的的01背包：

每一捆草吃或不吃，输出最大值（最后一个数）

还有数组空间注意开大。。。

c++题解:（一维）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,v,x,a[45001];//数组...
void read()
{
    int i,j;
    cin>>v>>n;
    for(i=1;i<=n;i++){
        cin>>x;//这个值只用一次,可以不用数组***好
        for(j=v;j>=x;j--)//在能吃的情况下
        a[j]=max(a[j],a[j-x]+x);//状态转移方程
    }
    cout<<a[v]<<endl;//结果
}
int main()
{
    read();
    return 0;
}
题解好像较少，是不是神犇们都懒得发题解了。。。
```

---

## 作者：ars4me (赞：0)

先说一下感受 这个题的数据和 装箱问题 一样水

试了试贪心都能得80

贪心就是排好序之后从大往小装 装不进去了就换下一个

毕竟不是正解就不发代码了 正解还是动态规划01背包

平常的简单背包问题都不仅仅有重量 还有价值

而这个题我们可以把它的重量理解成它的价值

而且每个物品只有一件供你选择 吃 还是 不吃  可以看出是01背包

下面写出状态转移方程

二维：f[i][j]=max{f[i-1][j-a[i]]+a[i],f[i-1][j]}

一维：f[j]=max{f[j],f[j−a[i]]+a[i]}

贴一个一维的代码


```cpp
#include<iostream>
using namespace std;
#define size 50001
int h,n;
int a[size],f[size]; 
int main()
{
    cin>>h>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    for(int j=h;j>=a[i];j--){
        if(f[j-a[i]]+a[i]>f[j])
        f[j]=f[j-a[i]]+a[i];
    }
    cout<<f[h];
}//COYG
装箱问题 p1049
```

---

## 作者：yang2016 (赞：0)

//01背包经典的背包问题 直接DP即可（似乎还没有c++题解）

  
```cpp
#include<cstdio>  
using namespace std;  
int h,n,a;  
int dp[50000];  
int main(){  
    scanf("%d%d",&h,&n);  //输入
    dp[0]=1;  
    for(int i=1;i<=n;i++) {  
         scanf("%d",&a);  
         for(int j=h;j>=a;j--){  
             if(dp[j-a]){           
                dp[j]=1;  
             } 
         }  
    }  
    for(int i=h;i>=0;i--){
        if(dp[i]==1){  
           printf("%d\n",i);  
           break;  
        }  
    }  
    return 0;  
}  

```

---

## 作者：fl_334 (赞：0)

```delphi

//动态规划的题
var
        f,a:array[0..46000]of longint;//注意数据范围！！一开始就因此wa掉了
        i,j,h,n:longint;
function max(x,y:longint):longint;
begin
        if x>y then exit(X)
        else exit(y);
end;
begin
        readln(h,n);
        for i:=1 to n do
                readln(a[i]);
        for i:=1 to n do
                for j:=h downto a[i] do
                        f[j]:=max(f[j],f[j-a[i]]+a[i]);//动态转移方程
        writeln(f[h]);
end.

```

---

## 作者：封禁用户 (赞：0)

本题是USACO 2009 October Gold的题目

其实就是一个01背包

用动态规划

bessie可以吃的草的重量是背包的容量，每捆草的重量就是价值。

附上AC code

```delphi

var  
  f:array[0..45000] of longint;  
  c,w:array[0..1000] of longint;  
  m,n,i,j:longint;  
begin  
  readln(m,n);  
  for i:=1 to n do  //初始化
  begin  
    readln(w[i]);  
    c[i]:=w[i];  
  end;  
  for i:=1 to n do  //动态规划
    for j:=m downto w[i] do  
      if f[j]<f[j-w[i]]+c[i] then  
        f[j]:=f[j-w[i]]+c[i];  
  writeln(f[m]);  
end.  

```

---

## 作者：first_fan (赞：0)

### 这么水的一道题，01背包的做法是最正常的，但是都烂大街了，今天，我来教教大家怎么用模拟退火解决这类的01背包问题。
### 尚未学会模拟退火的同学看这里！戳?[模拟退火学习](https://www.cnblogs.com/rvalue/p/8678318.html)
#### 首先我们知道，一堆干草有选和不选两种情况，那么如何利用模拟退火解决呢？
### 通过学习我们已经知道模拟退火需要一个能量差，那么背包问题的能量差从何而来呢？答案自然是来自~~大自然的力量~~物品的体积。
```
bool accept(int del) {
    return ((del>0)||exp(-del/T) > (double)rand()/RAND_MAX);
} //转移概率表达式
```
### 利用这个转移表达式，可以把一个数转换成0~1之间的概率值，而且温度大概率也大[为什么？](https://www.cnblogs.com/rvalue/p/8678318.html)
#### 所以对于每个物体，我们对它的体积进行概率转移，就会形成随机在当前的最佳情况之下，以某种概率跳出当前情况的形式。
### 有人就问了，为什么这样下来他不会一直换换换而无法结束呢？原因就是：随着降温的进行，跳出当前解的概率也越来越小，最后就固定在其中进行小范围跳动，也就得到了最优解。

------------

# 放代码：
```
#include<bits/stdc++.h>
#define MAXN 510
#define Tk 0.99789
#define rd (rand() % n + 1)
using namespace std;

int v[MAXN];
int V, n, ans = 0, tot = 0;
bool vis[MAXN];
double T = 1926;

bool accept(int del) {
    return ((del>0)||exp(-del/T) > (double)rand()/RAND_MAX);
} //转移概率表达式

int main() {
    srand(time(0));
    scanf("%d%d", &V ,&n);
    for(int i=1; i<=n; i++)
    {
    	scanf("%d", &v[i]);
	}
    int a;
    while(T > 1e-14) {
        ans=max(ans,tot);
        a = rd;
        int dE = v[a];
        if(vis[a])
		{
			dE *= -1;
		}
        if(accept(dE)) 
		{
            if(vis[a])
			{
                vis[a] = false;
                tot -= v[a];
            }
			else
			{
                if(tot + v[a] > V)
				{
					continue;
				}
                vis[a] = true;
                tot += v[a];
            }
        }
        T *= Tk;
    }
    cout <<ans;
    return 0;
}
```
### 警告⚠：如果你rp不好，请勿直接复制该题解，上天会用WA来惩罚你?

---

