# SCUBADIV - Scuba diver

## 题目描述

A scuba diver uses a special equipment for diving. He has a cylinder with two containers: one with oxygen and the other with nitrogen. Depending on the time he wants to stay under water and the depth of diving the scuba diver needs various amount of oxygen and nitrogen. The scuba diver has at his disposal a certain number of cylinders. Each cylinder can be described by its weight and the volume of gas it contains. In order to complete his task the scuba diver needs specific amount of oxygen and nitrogen. What is the minimal total weight of cylinders he has to take to complete the task?

## 样例 #1

### 输入

```
1
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119
```

### 输出

```
249
```

# 题解

## 作者：STA_Morlin (赞：13)

[SP181 SCUBADIV - Scuba diver（水肺潜水 - 潜水员） の 题目传送门。](https://www.luogu.com.cn/problem/SP181)

# 题目简化
> 给定两个数 $o, p$，再给定 $n$ 组数，每组数有 $3$ 个数，分别为其价值 $co_i, cp_i$ 和其代价 $w_i$。  
> 你可以选择几组数，使其 $co, cp$ 之和分别大于等于 $o, p$。

> 求满足条件的最小代价之和。

# 思路讲解
黄，不很经典背包例题。

平常的背包问题是 **指定代价求价值最大**。  
而这个问题是 **指定价值求最小代价**。

莫得关系，照样做。

- 首先考虑前提：$f_{i, j}$ 代表什么。  

平常的背包只需要一维数组，但这种背包是要二维的，因为他有两个决定条件：$co_i$ 和 $cp_i$。

再次由平常背包推理：平常背包 $f_i$ 是在重量为 $i$ 时最大价值，那么推及到本道题上来，$f_{i, j}$ 就是氧气，氮气在数量（我也不知道这个量词对不对）为 $i, j$ 时最少的代价。

---
- 然后推转移方程。  

这种背包的方程~~与众不同~~也和普通背包不一样。  
不过基本思路是一样的。

复习一下普通背包：
$$f_j = \max\{f_j, f_{j+w_i}+c_i\}$$
再看这里，容易得出，
$$f_{no, np} = \min\{f_{no, np}, f_{j, k}+w_i\}$$
（好吧其实不容易。（建议搭配下方循环讲解食用效果更佳。）  
就是在现有氧、氮量为 $j, k$ 时，装上了第 $i$ 个氧气瓶。  
$no, np$ 的意思是装上了这个氧气瓶后氧氮数量。  
这里需要注意：千万不可直接使用 $j+co_i$ 和 $k+cp_i$，因为那样会造成 RE。就算你把数组开大，在取结果时也是不方便的，因为你需要扫描他后面的空间。

---
# 代码实现
因为这里求的是最小值，所以是需要初始化的。  
将 $f_{i, j}$ 全域设置为 $inf$，但需要保留 $f_{0, 0}$ 的值为 $0$，因为潜水员一点气都不要自然就没有重量。

后面的循环是三层的，一层代表氧气瓶编号，一层代表氧气数量，一层代表氮气数量。

这里 $no, np$ 还需要处理一下，都知道不能直接使用 $j+co_i$ 和 $k+cp_i$ 了，就要考虑一下 $no, np$ 是什么值。  
其实很简单，就是 $\min\{j+co_i, o\}$，$\min\{k+cp_i, p\}$。这样答案就直接出现在 $f_{o, p}$ 了。
#  _CODE_：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int man = 1e3+10, inf = 0x3f3f3f3f;

int T, o, p, n;
int w[man], co[man], cp[man], f[25][85];
int main () {
	#ifndef ONLINE_JUDGE
		freopen("test.in", "r", stdin);
		freopen("test.out", "w", stdout);
	#endif
	scanf("%d", &T);
	while (T --) {
		for (int i = 0; i <= 23; ++ i) memset(f[i], inf, sizeof(f[i]));
		f[0][0] = 0;
		scanf("%d%d%d", &o, &p, &n);
		for (int i = 1; i <= n; ++ i) scanf("%d%d%d", co+i, cp+i, w+i);
		for (int i = 1; i <= n; ++ i) 
			for (int j = o; j >= 0; -- j) for (int k = p; k >= 0; -- k) {
				int no = min(j+co[i], o), np = min(k+cp[i], p);//
				f[no][np] = min(f[no][np], f[j][k]+w[i]);
			}
		printf("%d\n", f[o][p]);
	}
	return 0;
}
```
## E.N.D.

---

## 作者：ZolaWatle (赞：10)

## SP181 题解

这是一道比较优秀的**动态规划**题目，十分值得像我这样的 $dp$ 菜鸡一刷。

本题解主要面向动态规划的萌新和菜鸡们。

以鄙人拙见，我们大可以拿这道题目跟经典的$01$背包问题做类比。

------------

请允许我先重复一遍题意：

潜水员有一个带 $2$ 种气体的气缸：一个为氧气，一个为氮气。潜水员有一定数量的气缸。每个气缸都有重量和气体容量。

潜水员为了完成他的工作需要特定数量的氧和氮。要求他完成工作所需气缸的总重的**最低限度**是多少。

~~好吧其实就是乱改了一下我的翻译~~

------------

看到这种样子的题目，第一个想到的多半是$01$背包这个算法。

但这道题与典型的$01$背包的最明显的区别就在于：$01$背包只会涉及到两件事情，重量和价值；然而本题却涉及到了三个。

第二点，$01$背包问题给到我们最大载重，让我们**将能够承载的价值最大化**；然而这一道题恰恰相反，是在给到至少要满足的价值的情况下，让我们**把能提供这些价值的重量最小化**。

------------

在这两点的基础上，我们建立一个 $ dp_{i,j} $数组，**表示获得 $i$ 容量氧气和 $j$ 容量氮气时气缸的最小重量。**

（当然，可以类比$01$背包的 $dp_i$ 数组，它表示的是取 $i$ 重量时价值的最大值）

所以有一点可以先明确：$01$背包的 $dp$ 数组初始是 $0$，因为和本题恰好相反，所以本题的 $dp$ 数组的初值应该是**无限大**的（我比较习惯用$ 1e9 $来表示无限大）。

但还有一个问题，我们并不能把 $dp$ 数组整个儿给设成无限大。

因为当需要 $ 0 $ 容量氧气和 $0$ 容量氮气时，很显然，潜水员不需要携带任何一个气缸，所以此时的最小重量应该是 $0$ 。可以用代码表示为：

```cpp
dp[0][0]=0;
```

我们设潜水员需要 $Y$ 容量氧气，$D$ 容量氮气，容易得出如下所示的初始化代码：

```cpp
for(re i=0;i<=Y;i++)
	for(re j=0;j<=D;j++)
		dp[i][j]=1e9;  //把dp数组的初值赋成无限大 
dp[0][0]=0;  //就像我上面所说的那样 
```

------------

第一阶段结束，现在我们来思考如何进行**状态转移**的问题。

我们设潜水员有 $n$ 个气缸可供选择，每个气缸能够提供 $y_i$ 容量氧气，能够提供 $d_i$ 容量氮气，自身重量为 $w_i$ 。

我先把循环代码给大家放上来：

```cpp
for(re i=1;i<=n;i++)
	for(re j=Y;j>=0;j--)
		for(re k=D;k>=0;k--)
```

是这么一个意思：

现有的氧气、氮气量分别为 $j$，$k$，再在原有的基础上加上第 $i$ 个气缸的储备。

那么很容易知道，加上这个气缸之后，现在有的氧气和氮气量分别为：

```cpp
y[i]+j
d[i]+k
```

那就分别把它们设为 $ now \_ y $ 和 $ now \_ d$ 吧。

从刚刚给的那个循环代码中可以看出：$j$ 和 $k$ 的最大值分别为 $Y$ 和 $D$，因此做出判断如下：

**$ now \_ y $ 和 $ now \_ d$ 是很有可能超过潜水员的需求量 $Y$ 和 $D$ 的。**

我为什么要专门讲这个？其实不管这些也行，只不过最后找最小值的时候，你不仅需要扫描 $dp_{Y,D}$ 的值，还得把它们后边的空间都扫个遍。另外，对于如此不确定的 $ now \_ y $ 和 $ now \_ d$，也存在着极大的 $RE$ 隐患。

**那就干脆把超出需求量的部分浪费掉，就把它当成是刚刚好满足 $Y$，$D$ 的需求吧！**

注意！这很重要！

所以易得以下代码段：

```
now_y=std::min(now_y,Y);
now_d=std::min(now_d,D);
//合理地进行浪费 
```

------------

呼~接下来的活终于要变得轻松了~

正如上文所提及的，这里的 $ dp_{now\_y,now\_d} $ 表示的便是得到 $ now \_ y $ 和 $ now \_ d$ 的氧气和氮气时，气缸总重的最小值。

于是我们就可以来考虑 $ dp_{now\_y,now\_d} $ 是从哪些状态转换而来的了。

- 第一种，那就是不变的情况，也就是 $ dp_{now\_y,now\_d} $ 本身。

- 第二种，也很简单。还记得我刚才提到的：现有的氧气、氮气量分别为 $j$，$k$，再在原有的基础上加上第 $i$ 个气缸的储备这句话吗？好好理解一下，便可以知道第二种状态便是：原本有的 $j$ 单位氧气和 $k$ 单位氮气的最小重量 $dp_{j,k}$ 加上新增的那个气缸的重量 $w_i$，即 $ dp_{j,k}+w_i $

------------

历尽千辛万苦，我们终于推得了伟大的状态转移方程：

$$ dp_{now\_y,now\_d} \ =\ \{dp_{now\_y,now\_d},\ dp_{j,k}+w_i\}_{min} $$

最后我们要求的答案，就是 $ dp_{Y,\ D} $ 廖~

------------

什么？您告诉我还有组数？加上就完了呗~

```cpp
while(t--)
{
	//完整代码还等各位自己补充~
}
```

------------

这篇题解到这里就结束了。

另外，这是本蒟蒻第一次这么大篇幅的题解，有什么不足之处，或者出了什么锅，欢迎各位大佬指出，也恳请大家多多包涵。我将第一时间予以致谢以及对我的文章进行改正。

よろしく！（鞠躬）

---

## 作者：turing_hcy (赞：6)


这是一道比较好的背包题

首先我们要找状态就是用一个二维数组表示氧气容量，氮气容量为多少时的最小重量

找到状态之后就要状态转移方程，如果他需要该气缸的话，就让氧气,氮气，分别加上新的容量，再判断是否大于需求量，如果大于的话就会浪费掉，由于题目要求的是最小值，干脆就把浪费了的当作需求量，因为如果氧气和氮气多于需求值的话也是可以的，氧气和氢气的含量影响不大，主要求的是最小的重量，我认为这里是本题的难点，下面就是~~轻松简单的~~代码了，有具体讲解


多提供一组样例

 	输入
	5 60 5
	3 36 120
 	10 25 129
 	5 50 250
 	1 45 130
 	4 20 119
 	输出
	249
    
    
```c
#include<bits/stdc++.h>
using namespace std;
int m,n,k1;
int y,d,mm;
int f[1005][1005];
int main()
{
     cin>>m>>n;
     cin>>k1;
     memset(f,9999999,sizeof(f));//结果要最小值，所以初始化要很大，最大值还可以用127或127/3或0x3f3f3f3f
     f[0][0]=0;//初始化0氧气0氮气质量为0
     for(int i=1;i<=k1;i++)
     {
          cin>>y>>d>>mm;//写数组的话要单独用一个循环，不然有问题，血的教训
          for(int j=m;j>=0;j--)
          {
              for(int k=n;k>=0;k--)
              {
                  int t1=j+y,t2=k+d;
                  if(t1>m)	t1=m;//超过需求量可以直接用需求量
                  if(t2>n)	t2=n;//同上
                  f[t1][t2]=min(f[t1][t2],f[j][k]+mm);//氧气t1氮气t2时的最小质量


              }
          }
      }
      cout<<f[m][n];
      return 0;
  }
  ```

 ~~这篇题解改了好几遍真不容易，求过求过~~


---

## 作者：Energy_Making (赞：3)

思路已经很清楚了，就是用dp[i][j]表示氧气容量为i，氮气容量为j时的最小重量。我着重讲讲代码细节。

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
int y,d,n;
int a[1005],b[1005],w[1005],dp[1005][1005];
int main()
{
	cin>>y>>d;
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d %d %d",&a[i],&b[i],&w[i]);
	memset(dp,0x3f3f3f3f,sizeof(dp));//因为要求最小重量，所以初始化为无限大。
	dp[0][0]=0;//初始化，不带氧气与氮气时最小重量为0.
	for(int k=1;k<=n;k++)
		for(int i=y;i>=0;i--)
			for(int j=d;j>=0;j--)
			{
				int t1=i-a[k],t2=j-b[k];
				if(t1<0)t1=0;
				if(t2<0)t2=0;//若小于零则会运行错误，故小于零时让其等于零。
				if(dp[t1][t2]+w[k]<dp[i][j])dp[i][j]=dp[t1][t2]+w[k];
			}
	printf("%d",dp[y][d]);
	return 0;
}
```


---

## 作者：wbs200 (赞：2)

[更好的阅读体验](https://www.cnblogs.com/wbs200/p/solution-sp181.html)。

[原题](https://www.luogu.com.cn/problem/SP181)[链接](https://www.acwing.com/problem/content/1022/)。

二维费用经典背包问题。

状态数组 `f[i][j][k]` 描述为在前 $i$ 个物品中选取，且氧气含量至少为 $j$，氮气含量至少为 $k$ 的所有选法。数组含义为所有符号条件的选法的重量最小值。

每一个状态可以分为两种情况，一种是不包含第 $i$ 个物品，那么 `f[i][j][k]` 的状态与 $i - 1$ 的状态 `f[i - 1][j][k]` 相同，表示没有选取第 $i$ 个物品。

另外一种状态就是包含第 $i$ 个物品，它的状态转移方程就是 `f[i][j][k] = f[i - 1][j - v1][k - v2] + w`。

可以注意到，这时候 $j$ 表示的是氧气至少是 $j$ 的情况，$j$ 的值和 $v1$ 的值并没有什么直接的联系，只要原来的值加上 $v1$ 这个值之后大于等于 $j$ 即可，也就是说状态转移方程中的 $j−v1$ 也就没有确切的值，它只是一个小于 $j$ 的数，可以大于 $0$，可以等于 $0$，也可以小于 $0$。

1. $j - v1 > 0$，表示要满足 $j$ 的需求，不能只靠 $v1$，还要选取其他的氧气瓶才能达到要求。
2. $j - v1 = 0$，表示要满足 $j$ 的需求，只选取 $v1$ 就足够了，恰好可以满足 $j$ 的需求。
3. $j - v1 < 0$，表示要满足 $j$ 的需求，只选取 $v1$ 就足够了，甚至还有剩余，可以大于 $j$ 的需求，不过过剩并没有什么用，我们只需要 $j$ 的需求就可以了。

这就导致在设置初始值的时候要考虑到 $j−v1$ 小于 $0$ 的时候，也是符合要求的一种情况，表示只选取 $v1$ 这个氧气瓶，这时候除去 $v1$ 之后，`f[j]` 就表示没有 $j$ 的这一维状态下没有选择氧气瓶了，也就是 `f[0]` 的状态。

由此可得状态转移方程为 `f[i][j][k] = f[i - 1][max(j - v1, 0)][max(k - v2, 0)] + w)`。表示 $j−v1$ 至多到 $0$ 状态。由于 $j - v1$ 可能小于 $0$，所以要和 $0$ 取一个 $\max$ 值。
```
#include <iostream>
#include <cstring>
using namespace std;

const int N = 22, M = 80;
int f[N][M];

int main()
{
	int q;
	cin >> q;
	while (q--)
	{
	    int n, m, K;
	    cin >> n >> m >> K;
	    memset(f, 0x3f, sizeof f);
	    f[0][0] = 0;
	    while (K--)
	    {
	        int v1, v2, w;
	        cin >> v1 >> v2 >> w;
	        for (int i = n; i >= 0; i--)
	            for (int j = m; j >= 0; j--)
	                f[i][j] = min(f[i][j], f[max(0, i - v1)][max(0, j - v2)] + w);
	    }
	    cout << f[n][m] << endl;
	}
    return 0;
}
```

---

## 作者：Jeremiahy (赞：0)

## 分析

很经典的二维背包问题。

设 $dp_{i,j}$ 表示氧气容量为 $i$，氮气容量为 $j$ 时的最小背包重量。因为要求最小重量，所以我们可以将初值都设为正无穷，只有 $dp_{0,0}$ 初值为 $0$（因为不需要携带任何气缸）。

状态转移应该最外层循环从 $1$ 到 $n$ 表示选择哪个气缸。第二三层循环则是氧气量与氮气量从 $O$,$N$ 倒序循环。

很容易得到如下的状态转移方程：

$$dp_{o_i+j,n_i+k}=\min(dp_{o_i+j,n_i+k},dp_{j,k}+w_i)$$

由于 $o_i+j$ 和 $n_i+k$ 可能超出 $O$ 和 $N$ 的范围，所以我们可以将它们与 $O,N$ 取最小值。

最后答案就是 $dp_{O,N}$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int q, O, N, m, o[1005], n[1005], w[1005], now_y, now_d, dp[1005][1005];
signed main () {
	cin >> q;
	while (q--) {
		cin >> O >> N >> m;
		for (register int i = 1; i <= m; i++)
			cin >> o[i] >> n[i] >> w[i];
		for (register int i = 0; i <= O; i++)
			for (register int j = 0; j <= N; j++)
				dp[i][j] = 1e9;  
		dp[0][0] = 0;//初值为 0
		for (register int i = 1; i <= m; i++)
			for (register int j = O; j >= 0; j--)
				for (register int k = N; k >= 0; k--)
					dp[min(o[i] + j, O)][min(n[i] + k, N)] = min(dp[min(o[i] + j, O)][min(n[i] + k, N)], dp[j][k] + w[i]);
		cout << dp[O][N] << '\n';
	}
	return 0;
}
```



---

