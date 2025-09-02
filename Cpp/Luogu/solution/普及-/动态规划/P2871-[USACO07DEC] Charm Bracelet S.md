# [USACO07DEC] Charm Bracelet S

## 题目描述

Bessie has gone to the mall's jewelry store and spies a charm bracelet. Of course, she'd like to fill it with the best charms possible from the N (1 ≤ N ≤ 3,402) available charms. Each charm i in the supplied list has a weight Wi (1 ≤ Wi ≤ 400), a 'desirability' factor Di (1 ≤ Di ≤ 100), and can be used at most once. Bessie can only support a charm bracelet whose weight is no more than M (1 ≤ M ≤ 12,880).

Given that weight limit as a constraint and a list of the charms with their weights and desirability rating, deduce the maximum possible sum of ratings.

有 $N$ 件物品和一个容量为 $M$ 的背包。第 $i$ 件物品的重量是 $W_i$，价值是 $D_i$。求解将哪些物品装入背包可使这些物品的重量总和不超过背包容量，且价值总和最大。

## 样例 #1

### 输入

```
4 6
1 4
2 6
3 12
2 7```

### 输出

```
23```

# 题解

## 作者：wxwyx (赞：120)

本蒟蒻终于理解了零一背包。( •̀ ω •́ )
~~耶~~

第一次题解。

先配一下我的翻译。


------------

  贝茜在逛珠宝店时，买了一个她喜欢的手镯。因此她想从她收集的N（1≤N≤3402）块宝石中选最好的一些镶在手镯上。对于第i块宝石，它的重量为Wi（1≤Wi≤400），并且可以给贝茜增加魅力值Di（1≤Di≤100）。由于贝茜只能忍受重量不超过M（1≤M≤12880）的手镯，她可能无法把所有她喜欢的宝石都镶上。
  
  于是贝茜找到了你，希望你能帮她计算，按照最合理的方案镶宝石，她的魅力值最多能增加多少。
  
由于每块宝石各不相同，所以典型的**零一背包**啦。

如果f数组是二维的，肯定是要爆空间的。
~~（只是本蒟蒻认为其实一维的比较好理解）~~

话不多说，代码见下。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int w[3410],v[3410];  //w数组存重量，v数组存价值（魅力值）
int f[13000];
int main()
{
	int n,m;   //m是最大重量
	cin>>n>>m;     //与采药输入顺序相反
	for(int i=1;i<=n;i++)
		cin>>w[i]>>v[i];  //输入好像没什么好说的。
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=w[i];j--)   //从后向前找不会有其它影响
		{
			f[j]=max(f[j-w[i]]+v[i],f[j]);   //最基本的状态转移方程
		}
	}
	cout<<f[m]<<endl;
	return 0;
}
```

------------
蒟蒻的第一次题解。~~管理大大求过~~

---

## 作者：ww3113306 (赞：46)

```cpp
//这道题用二维会爆
#include<bits/stdc++.h>
using namespace std;
int n,v,f[15000],i,j,w,m;
int main()
{
    scanf("%d%d",&n,&v);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&w,&m);//每读一个物品就处理一个 
        for(j=v;j>0;j--)//模拟背包剩余容量 
            if(w<=j) f[j]=max(f[j],f[j-w]+m);  //选择那与不拿（取最大值） 
    }
    printf("%d",f[v]);//最后一个即为最大值 
    return 0;    
}
```

---

## 作者：theHermit (赞：24)

看到了很多用一维数组题解

我发现用二维数组其实也是可以解决的~ 而且感觉比较容易理解一些

首先本题会爆的原因是因为如果开二维数组，由于背包大小M和物品个数N过大，会MLE。

只要用**滚动数组**就可以了 因此我在这里补充一下二维数组的做法~

**已经清楚题意的朋友可以跳过题意理解部分~**

--------------题意理解以及递推式部分---------------

根据题意，我们设当前为第i个物品，背包容量为j，我们设的二维表实际上第i行第j个的意思就是：

在背包容量为j的时候，

前i个物品所能获取的最大价值为:V[i][j]

因此我们可以想到，在第i个物品，背包容量j时，这个最大价值V的可能性可以被划分为两种：
  
条件Ⅰ：在背包足够装第i个物品的的情况下：

①拿第i个物品，放入背包，有价值W[i]

此时我们就知道，此时容量为：

j减去这个物品的重量，
为j-C[i]

那么剩下容量能装的最大价值为：

没拿这个物品时(i-1时)，

剩下背包容量(j-C[i])能装的最大价值:
V[i-1][j-C[i]]

故在条件Ⅰ下：第i个物品，背包容量j时的最大价值V为：

V[i][j]=max(V[i-1][j],V[i-1][j-C[i]]+W[i])


条件Ⅱ：不够装第i个物品，那么这个最大价值为：

V[i][j]=V[i-1][j]

--------------滚动数组部分---------------

但是如果只是上述写法，由于物品数N最大会有3,402个，背包容量最大为12,880，那么数组大小为N*M=43,817,76个元素...

并不能满足要求(MLE)

因此我们需要对内存进行优化：

我们发现递推式V[i][j]=max(V[i-1][j],V[i-1][j-C[i]]+W[i])
只用到了上一行的数据，因此我们并不需要开N个物品的空间~，只需要开2行就可以了~

然后在算到第3行(N=3)的时候，把第一行覆盖掉，这样循环使用~就可以达到我们想要的效果

递推式就变为：

V[i%2][j]=max(V[(i-1)%2][j],V[(i-1)%2][j-C[i]]+W[i]);


```cpp
    for(int i=1;i<=N;i++){
        for(int j=M;j>=1;j--){
            if(j>=C[i])
                V[i%2][j]=max(V[(i-1)%2][j],V[(i-1)%2][j-C[i]]+W[i]);
            //j-C[i]为：拿2之后剩余的重量，然后除此之外的最大值
            else
                V[i%2][j]=V[(i-1)%2][j]
        }
    }

    cout<<V[N%2][M];
```





---

## 作者：CodinPnda (赞：6)

# 01背包的优化 —— f的压缩
这道题很明显是一道01背包，于是立即可以得出：
$$ f[i][j] = max\{f[i][j-1], f[i-w[d]][j-1]+c[d]\} $$
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int t, k, w[3403], v[3403];
int f[12881][3403], b;
int flag;

int main(){
    cin >> k >> t;
    for(int i = 1; i <= k; i++) cin >> w[i] >> v[i];
    for(int i = 1; i <= k; i++) f[0][k] = 0;
    for(int i = 0; i <= t; i++){
        for(int j = 1; j <= k; j++){
            if(w[j] <= i) {
                f[i][j] = max(f[i][j-1], f[i-w[j]][j-1]+v[j]);
            }
            else f[i][j] = f[i][j-1];
        }
    }
    for(int i = 1; i <= k; i++){
        if(f[t][i] > b) b = f[t][i];
    }
    cout << b << endl;
    return 0;
}
```
但是，如果是按这种思路来的话，那么内存消耗将会非常大！
即$ f[12881][3403] $，不是MLE就是WA。

所以，唯一的出路就是压缩f。通过观察可以发现，j其实是一个多余的变量，或者说，j可以只是作为一个临时变量。此时的状态转移方程为：
$$ f[i] = max(f[i], f[i-w[d]]+c[d]) $$
代码如下：
```cpp
#include <iostream>
using namespace std;
int n, m, f[12881], w[3403], c[3403], b;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for(int j = 0; j <= n; j++){
        for(int i = m; i >= w[j]; i--){
            f[i] = max(f[i], f[i-w[j]]+c[j]);
        }
    }
    cout << f[m] << endl;
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：5)

无聊写个题解玩玩，

那些说数组一定要开很大的多半是没看数据范围

```cpp
N (1 ≤ N ≤ 3,402)
V(1 ≤ V ≤ 12,880).
Ci (1 ≤ Ci ≤ 400)
Wi (1 ≤ Wi ≤ 100), 
```
然后显而易见，二维的会爆。
```cpp
#include<iostream>
#include<cstdio> 
#include<cmath>
#include<algorithm>
#include<set>
#include<queue>
#include<vector>
#include<map>
using namespace std;
int n,v;
int c[3500],w[3500];//c:质量 w：价值
int i,j; 
int f[13880];
int main()
{
    scanf("%d %d",&n,&v);
    for (i=1;i<=n;i++)//正常的读入 
    {
        scanf("%d %d",&c[i],&w[i]);
    }
    for (i=1;i<=n;i++)
        for (j=v;j>=c[i];j--)//一维的01背包，一定要装得下才能去装  
        f[j]=max(f[j],f[j-c[i]]+w[i]);//选大的 
    printf("%d",f[v]);
    return 0;
}
```

---

## 作者：不存在之人 (赞：4)

0-1背包~~~

我是基本原理理解差不多了，就是没自己写过。。。今晚自己写了。写完蛮不自信的，还找代码对了对，居然对着类，哦也~~

具体分析详见背包九讲~~~

背包啊背包。。。大家天天都背包。。。你的背包~~~

这个题二维的大啊，大致算下，得超内存吧。

一维的
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int bag[12900];
int w[3410],v[3410];
int main(void)
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>w[i]>>v[i];
	memset(bag,0,sizeof(bag));
	for(int i=1;i<=n;i++)	
		for(int k=m;k>=w[i];k--)
			if(bag[k-w[i]]+v[i]>bag[k])
				bag[k]=bag[k-w[i]]+v[i];
	cout<<bag[m]<<endl;
	return 0;
}
```

---

## 作者：lijiahao2017 (赞：3)

# P2871 【[USACO07DEC]手链Charm Bracelet】



### 题目描述

Bessie has gone to the mall's jewelry store and spies a charm bracelet.Of course, she'd like to fill it with the best charms possible from the N (1 ≤ N ≤ 3,402) available charms.Each charm i in the supplied list has a weight Wi (1 ≤ Wi ≤ 400), a 'desirability' factor Di (1 ≤ Di ≤ 100), and can be used at most once.Bessie can only support a charm bracelet whose weight is no more than M (1 ≤ M ≤ 12,880).

Given that weight limit as a constraint and a list of the charms with their weights and desirability rating, deduce the maximum possible sum of ratings.

有$N$件物品和一个容量为$V$的背包。第$i$件物品的重量是$c[i]$，价值是$w[i]$。求解将哪些物品装入背包可使这些物品的重量总和不超过背包容量，且价值总和最大。

### 输入输出格式

##### 输入格式：
* Line 1: Two space-separated integers: N and M

* Lines 2..N+1: Line i+1 describes charm i with two space-separated integers: Wi and Di

第一行：物品个数N和背包大小$M$

第二行至第$N+1$行：第i个物品的重量$C[i]$和价值$W[i]$

##### 输出格式：
* Line 1: A single integer that is the greatest sum of charm desirabilities that can be achieved given the weight constraints

输出一行最大价值。

### 输入输出样例

##### 输入样例#1： 复制
$4$ $6$

$1$ $4$

$2$ $6$

$3$ $12$

$2$ $7$
##### 输出样例#1： 复制
$23$



小菜鸡最近比较多做      动态规划,动规,dp      的题。

今天，小菜鸡就发一道~~水题(做了三次才$AC$)~~。

这道题是一道红题，难度为    入门难度      。

讲了这么多废话，来说说重点。

这道题属于典型的     背包     的      动态规划,动规,dp。 

那我们看看是什么类型的      背包。

显然是一道基础的01背包。

但要注意数据范围（小菜鸡被坑了一次，好不开心）。

这道01背包是带有价值的。

### 开讲思路：

#### 1.注意一下数组大小

#### 2.虽带有价值但不是完全背包，千万不要打错是01背包。

#### 3.输出是f[v]最大价值。

### 上代码：

```
//最近小菜鸡改了下代码风格，为了省一行代码变成了丑丑风格
#include<cstdio>//调用      scanf和printf      的库
#include<cstring>//调用      memset      的库
#define ll long long//定义long long类型习惯了
const ll mx=50010;//注意数据范围
ll n,v;
ll c[mx],w[mx],f[mx];
//定义变量和数组
ll max(ll x,ll y) { return x>y?x:y; }//比较大小函数
//一切准备就绪
int main(){
	memset(f,0,sizeof(f));//将f[]初始值为0
	scanf("%lld %lld",&n,&v);
	for(ll i=1;i<=n;i++)scanf("%lld %lld",&c[i],&w[i]);
	//完美的输入
    for(ll i=1;i<=n;i++){//做01背包
		for(ll j=v;j>=c[i];j--)f[j]=max(f[j],f[j-c[i]]+w[i]);//更新
	}
	printf("%lld",f[v]);//输出f[v]最大价值
	return 0;//bye bye下次再见
}
```

---

## 作者：williamllk (赞：2)

这道题和[P1048 采药](https://www.luogu.org/problem/P1048)几乎一模一样。

两道题唯一的区别就是：

采药要先输入背包大小，而这题要先输入物品数量

接下来有我这位蒟蒻为大家展现一下两道题代码的不同：

采药AC代码：

```cpp
#include <iostream>
using namespace std;
int n,W,w[13010],v[13010],f[13010];
int main() {
  	cin >> W >> n;
  	for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
  	for (int i = 1; i <= n; i++)
    for (int l = W; l >= w[i]; l--)
   		if (f[l - w[i]] + v[i] > f[l]) f[l] = f[l-w[i]] + v[i];
  	cout << f[W];
  	return 0;
} 
```
本题AC代码：
```cpp
#include <iostream>
using namespace std;
int n,W,w[13010],v[13010],f[13010];
int main() {
  	cin >> n >> W;
  	for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
  	for (int i = 1; i <= n; i++)
    for (int l = W; l >= w[i]; l--)
   		if (f[l - w[i]] + v[i] > f[l]) f[l] = f[l-w[i]] + v[i];
  	cout << f[W];
  	return 0;
} 
```
如需解析，可以看我的第二个博客——[P1048 采药](https://williamllk.blog.luogu.org/solution-p1048)


---

## 作者：龘龘龘龘龘龘 (赞：2)

这是一道十分经典的例题 很多书上都有差不多一模一样的背包问题；

主要思想就是f[j]=max{f[j],f[j-a[i]]+c[i]};

学这种简单的背包就是套用这个公式就行，很适合新手用（我也是新手呢）

不过我比较不喜欢抄袭党，所以在我的代码里我会留一个很明显的错误，嘿嘿，认真看的同学就会发现呢，直接复制粘贴的我就嘿嘿一笑；

```cpp
#include<iostream>
using namespace std;
int a[3500],b[3500];
int f[13000];
int main()
{
    int i,j,m,n;
    cin>>n>>m;//输入背包的容量n和数量m
    for(i=1;i<=n;i++)
      cin>>a[i]>>b[i];//每个物品的重量和价值
    for(i=1;i<=n;i++)//设f（j）表示重量不超过j公斤的最大价值
      for(j=m;j>=a[i];j--)
        if(f[j]<f[j-a[i]]+b[i])
          f[j]=f[j-a[i]]+b[i];
      cout<<f[m];//f(m)就是最优解
      return 0;
}
这个背包问题是最基本的问题，以后要学的东西基本上都可以转换到这个背包问题上，基本上学好这个后，能干很多很多事的，和我一样是新手的同胞们加油！！！！
```

---

## 作者：Right (赞：2)

其实这道经典01背包题，

看到楼下虽然已经把二维降到了一维

但是，其实还可以再优化

例如把c和w的数组变成一个变量，每次更新

既节省了内存，又节省了时间

何乐而不为？

代码1：

>>精简
```cpp
#include <stdio.h>
#define max(a,b) (a>b?a:b) 比大小
int n,m,i,j,c,w,f[12880];
int main()
{
    for (scanf("%d%d",&n,&m),i=1; i<=n; ++i) 在读入中循环
        for (scanf("%d%d",&c,&w),j=m; j>=c; --j) f[j]=max(f[j],f[j-c]+w); 01经典公式
    printf("%d",f[m]); 输出
}
```
三行搞定，如果看不懂
代码2：

>>易懂
```cpp
#include <stdio.h>
#define max(a,b) (a>b?a:b)
int n,m;
int f[12880];
int main()
{
    int i,j,c,w;
    scanf("%d%d",&n,&m); 
    for (i=1; i<=n; ++i)
    {
        scanf("%d%d",&c,&w);
        for (j=m; j>=c; --j)
        {
            f[j]=max(f[j],f[j-c]+w);
        }
    }
    printf("%d",f[m]);
}
```
思路同代码1，供新手看，不多作解释。
over。


---

## 作者：fashoint (赞：1)

看大家都写的是~~二向箔~~降维打击。~~（低熵体开心极了）~~

所以**蒟蒻**写个滚动数组的，

写滚动数组的原因有以下两个：
		
        1. 我们发现每一阶段的i的状态只于上一阶段的i-1的状态有关。
        2. 我太菜了，没有二向箔（呜呜呜......）
## 下面看代码，**有注释哦**：

```
//学信竞第一道DP--01背包
//学信竞第一篇题解  开心
#include<bits/stdc++.h>//万能头
using namespace std;
int n,m;
int v[3404],w[3404];//许多人说没有数据范围，其实可以看看英文，另外管理员请把数据范围加到中文里吧，谢谢，谢谢
int f[2][12885];//看“2”！！！，是不是很小，只需要存俩
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&v[i],&w[i]);
	memset(f,0xcf,sizeof(f));//0xcf==-INF
	f[0][0]=0;
	for(int i=1;i<=n;i++){
    		for(int j=0;j<=m;j++)	f[i&1][j]=f[(i-1)&1][j];//“&”的意思是取反（0变1，1变0）
                                                                //让上一个更新出的值来更新下一个
		for(int j=v[i];j<=m;j++)	f[i&1][j]=max(f[i&1][j],f[(i-1)&1][j-v[i]]+w[i]);//取反，更新
	}
	int ans=0;
	for(int j=0;j<=m;j++)	ans=max(ans,f[n&1][j]);
	cout<<ans;
} 
```


---

## 作者：Atmizz (赞：1)

# 01背包的裸题（裸的不能再裸了，除非有std）
#### 先来普及一下01背包~~~
01背包是在M件物品取出若干件放在空间为W的背包里，每件物品的体积为W1，W2至Wn，与之相对应的价值为P1,P2至Pn。01背包是背包问题中最简单的问题。01背包的约束条件是给定几种物品，每种物品有且只有一个，并且有权值和体积两个属性。在01背包问题中，因为每种物品只有一个，对于每个物品只需要考虑选与不选两种情况。如果不选择将其放入背包中，则不需要处理。如果选择将其放入背包中，由于不清楚之前放入的物品占据了多大的空间，需要枚举将这个物品放入背包后可能占据背包空间的所有情况。

### 其状态转移方程为：
```cpp
f[i][v]=max{f[i-1][v],f[i-1][v-c[i]]+w[i]}
```
但是可以优化空间，因为二维的会爆空间。
### 优化后的状态转移方程为：
```cpp
f[v]=max{f[v-w[i]]+c[i]};
```
所以代码就出来了。
## code：
```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
int n,m,c[3500],w[3500],f[12884];//c存储价值，w存重量 
int main()
{
	scanf("%d%d",&n,&m);//表示数量，大小
	for(int i=1;i<=n;i++)
	scanf("%d%d",&w[i],&c[i]);//输入重量与价值 
	for(int i=1;i<=n;i++)
		for(int v=m;v>=w[i];v--)//枚举
			if(f[v]<f[v-w[i]]+c[i])//找最大值 
				f[v]=f[v-w[i]]+c[i];
	printf("%d",f[m]);//输出最大值 
	return 0;
}
```

---

## 作者：coldcool (赞：1)

第一次发题解，如不好请各位见谅。

标准01背包，用了在线读入，可以少开两个数组。

下面放代码。

```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;//头文件不用说了
int n,v,c,w,f[13003];
int main(){
    scanf("%d%d",&n,&v);//读入个数和重量
    for(int i=1;i<=n;i++){//01背包公式
        scanf("%d%d",&c,&w);//在线读入
        for(int j=v;j>=c;j--)
            f[j]=max(f[j],f[j-c]+w);//选取较优（较大）值
    }
    printf("%d\n",f[v]);//输出
    return 0;
}
```

---

## 作者：kgory (赞：1)

我来发题解了！！！

这题是01背包，但是不同于 “开心的金明” 那题如果用贪心的话可以得部分分的。但很遗憾，这题不行。

在这里，我主要介绍一下 01背包！！！

这题如果开一个二维数组的话，可能会爆掉，因为要开到 200005 ，否则会 RE或Wa ,所以要优化一下......

其实很简单，设 f[v] 表示重量不超过 v 公斤的最大值，则 f[v]=max {f[v],f[v-w[i]]+c[i]}, 当v>=w[i] , 1<=i<=n 时。

附上代码：




```cpp
#include <cstdio>
int n,m;
int w[200005],c[200005];  //数组一定要开大！！！
int f[200005];   //否则就会 WA
int main () {
    int i,j;
    scanf ("%d%d",&n,&m);  //读入不想讲
    for (i=1;i<=n;i++) {
        scanf ("%d%d",&w[i],&c[i]);  //读入不想讲
    }
    for (i=1;i<=n;i++) {  //设 f[v] 表示重量不超过 v 公斤的最大值
        for (v=m;v>=w[i];v--) {
            if (f[v-w[i]]+c[i]>f[v])   //判断
               f[v]=f[v-w[i]]+c[i];
        }
    }
    printf ("%d\n",f[m]);  //f[m]为最优解
    return 0;
}
附：我的代码可能还有缺点，如果有不完美的地方，可以私信找我，谢谢！
```

---

## 作者：zhangzhaoke (赞：1)

其实是01背包，但我用dp做的，也不复杂
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int m;
int w[3501];
int v[3501];
int f[12881];
int main(){
	memset (w,0,sizeof (w));
	memset (v,0,sizeof (v));
	memset (f,0,sizeof (f));
	cin>>n>>m;
	for (int i=1;i<=n;i++)cin>>w[i]>>v[i];
	for (int i=1;i<=n;i++)
		for (int j=m;j>=w[i];j--)
			f[j]=max (f[j],f[j-w[i]]+v[i]);//动态转移方程
	cin>>f[m];
	return 0;
}
```


---

## 作者：远山淡影 (赞：1)

直接看代码吧，讲解很详细。
```cpp
//这题其实就是一个含价值的填满型01背包。。。 
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<string>//头文件纯属无聊。 
using namespace std;
int a[21000],b[21000],n,v,f[21000];//a数组是重量，b数组是价值， f数组是答案，n是物品数量，v是背包容量。 
int mymax(int x,int y){return x>y?x:y;}//一个很有用的比较函数，意思是：如果x大于y就输出x，否则输出y。 
int main()
{
    scanf("%d%d",&n,&v);
    memset(f,0,sizeof(f));//把f数组全部初始化为0。 
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i],&b[i]);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=v;j>=a[i];j--)//为什么要从总重量往第i个物品的重量循环呢？这是为了下面的比较。 
        {
            f[j]=mymax(f[j],f[j-a[i]]+b[i]);//看一下，我是不拿你还是用掉a[i]的容量来拿你从而得到b[i]个价值好呢？ 
        }
    }
    printf("%d\n",f[v]);//输出：花掉v的容量能得到的最大价值。 
    return 0;
}
//膜拜神犇scy 
```
蒟蒻题解，大佬别喷。。。

---

## 作者：liangyanlun (赞：0)

## 01背包/背包问题模板

蒟蒻第一次发题解，不足之处还请大佬指正~~~

话不多说，上代码---

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,n1,n2,n3,n4,n5,n6,n7,n8,n9,m[100005],m1[100005],m2[100005];
//码风清奇，习惯了这样打变量，见谅。 
int main()
{
	cin>>n1>>n2;//输入物品数及背包空间数，cin读入 。 
	for(int i=1;i<=n1;i++)
	scanf("%d%d",&m1[i],&m2[i]);//读入物品性质，scanf读入快 。 
	for(int i=1;i<=n1;i++)//每个物品过一遍 。 
	for(int j=n2;j>=m1[i];j--)//01背包从后往前找，下限为m1[i]防止超界 。 
	{
		m[j]=max(m[j],m[j-m1[i]]+m2[i]);
		//这一步为找出每个背包空间所能存放物品价值的最大值 。 
	}
	cout<<m[n2];
	//输出背包空间能产生的最大价值m[n2]。 
	return 0;
}
```

~~恳请管理员高抬贵手，放过蒟蒻。~~



---

## 作者：Drinkkk (赞：0)

/\*
P2871 题解

含价值型的填满型01背包

\*/
```cpp
#include <cstdio>//头文件
int t[1000001],m[1000001],f[1000001];//t数组是用来存储这个物品的大小的，m数组是用来存储这个物品的价值的，f数组是用来存储能得到的最大价值的
int maxx(int x,int y)//用来判断到底两个数哪一个数更大
{
    return x>y?x:y;//如果x>y，那么就返回x的值，否则返回y的值
}
int main()//主函数
{
    int n=0,v=0;//定义变量（n表示有n个物品，v表示这个背包的容量是v）
    scanf("%d %d",&n,&v);//输入n和v（即有多少个物品以及背包的容量）
    for(int i=1;i<=n;i++)//读入这n个物品的大小以及这个背包的容量
    {
        scanf("%d %d",&t[i],&m[i]);//读入第i件物品所占的空间（即这个物品的大小），以及第i件物品的价值
    }
    for(int i=1;i<=n;i++)//从第1件物品到第n件物品
    {
        for(int j=v;j>=t[i];j--)//到每个楼层一次
        {
            f[j]=maxx(f[j],f[j-t[i]]+m[i]);//不管当前的f[j]（即不管f数组里面的第j层有没有放入数字，都更新一边）
        }
    }
    int ans=0;//找最大值（即“答案”的缩写：answer）
    for(int i=v;i>=0;i--)//找最大值
    {
        if(f[i]>=ans)//如果比当前所找到的最大值要大的话
        {
            ans=f[i];//更新最大值
        }
    }
            printf("%d",ans);//输出最大值
            //提示：可以去掉这个循环（以及定义ans和输出ans的那段），直接输出f[v]（也可以通过）
        return 0;//结束程序
}
```

---

## 作者：LevenKoko (赞：0)


     
    
        
    
```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
int w[10001],v[10001],a[3410][3410]={0},n,p,j,s;
//p表示背包总量，n表示物品总数，数组v表示每件物品价值，数组w表示每件物品重量，数组a表示背包容量为x时，最大的价值； 
int main()
{
    cin>>n>>p;
    for(int i=1;i<=n;i++)
    cin>>w[i]>>v[i];//输入数据；
    for(int i=w[n];i<=p;i++)
    a[n][i]=v[n];//将第n层的数据保存下来； 
    for(int i=n-1;i>=1;i--)
    for(int j=1;j<=p;j++)
    {
        s=j;
        if(s-w[i]>=0)
        a[i][j]=max(v[i]+a[i+1][s-w[i]],a[i+1][j]);
        else 
        if(s-w[i]<0)
        a[i][j]=a[i+1][j];
    }
    /*for(int i=1;i<=n;i++)
    {
    for(int j=0;j<=p;j++)
    cout<<setw(5)<<a[i][j];
    cout<<endl;
    }*/
    //可以输出每一步走法帮助理解 ； 
         cout<<a[1][p];
    return 0;
}
```

---

## 作者：cenbinbin (赞：0)

最简单的dp 没有之一

简单的01背包就可以了。

=================================================================================

```cpp
var
  f:array[0..100001] of longint;
  n,m,i,j,x,y:longint;
begin
  readln(n,m);
  for i:=1 to n do
   begin
     readln(x,y);//读入每组数据
     for j:=m downto x do//注意：用downto  若用了to 那么就是完全背包了
      if f[j-x]+y>f[j] then f[j]:=f[j-x]+y;//选取最优解
   end;
  writeln(f[m]);
end.
```

---

## 作者：Xsy123456 (赞：0)

###最基本的背包问题

二维数组可用f[i][v]=max{f[i-1][v],f[i-1][v-w[i]]+c[i]}

不过数据大时二维数组无法定义

```cpp
#include <cstdio>
using namespace std;
#define Size 200000

int m,n;
int w[Size+5],c[Size+5],f[Size+5];

int main(){
    
    scanf ("%d%d",&n,&m);  //背包容量m和物品数量n
    
    for (int i=1;i<=n;i++)
      scanf ("%d%d",&w[i],&c[i]);
    for (int i=1;i<=n;i++)     //设f(j)表示重量不超过j公斤的最大价值
      for (int j=m;j>=w[i];j--)
        if (f[j-w[i]]+c[i]>f[j])
          f[j]=f[j-w[i]]+c[i];
    
    printf ("%d",f[m]);
    
    return 0;        
    
}
```

---

## 作者：zhm411821 (赞：0)

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int dp[50000],x,y,n,v;//1 ≤ V ≤ 12,880 
int main(){
    cin>>n>>v; 
    for(int i=1;i<=n;i++){
        cin>>x>>y;//不需要用数组记录输入，可以节省空间
        for(int j=v;j>=x;j--)//要从后向前更新，这样可以保证每个物品都不被重复计算
            dp[j]=max(dp[j],dp[j-x]+y);//dp[j]记录当背包容量为j时，当前已输入的物品的最大价值
        }
    cout<<dp[v];
    return 0;
}
```

---

## 作者：xiajieke (赞：0)

```cpp
#include<iostream>
using namespace std;
int n,m,v[5000],w[5000],f[100000];
int main()
{
int i,j,k;//整型3个数
cin>>n>>m;
for(i=1;i<=n;i++)//总物品
cin>>w[i]>>v[i];
for(i=1;i<=n;i++)
for(j=m;j>=w[i];j--)
f[j]=max(f[j],f[j-w[i]]+v[i]);//计算方案数
cout<<f[m];//f[m]为最优解
return 0;//纯正的01背包，拿来试手
}
```

---

## 作者：little_gift (赞：0)

##纯正的01背包，刚学的也可以练练手##

```cpp
var
  n,m,i,j,t,w:longint;
  f:array[0..12880] of longint;  //f[x]表示当背包内物品重量（背包容量）为x时，最大的物品价值
begin
  readln(n,m);
  for i:=1 to n do
    begin
      readln(t,w); //这里不一定要定义两个数组，直接定义两个变量就可以了
      for j:=m downto t do
        if f[j]<f[j-t]+w then //如果取当前这个物品的价值比不取要好，就取它。
          f[j]:=f[j-t]+w;
    end;
  writeln(f[m]); //输出当背包容量为m时的最大价值
end.
```

---

## 作者：飞翔 (赞：0)

水水的01背包，但是要压缩状态。

```cpp
var
    i,j,n,m:longint;
    f:array[0..100000]of longint;
    c,w:array[0..5000]of longint;
begin
    fillchar(f,sizeof(f),0);
    readln(n,m);
    for i:=1 to n do readln(w[i],c[i]);
    for i:=1 to n do
        for j:=m downto w[i] do
            if f[j-w[i]]+c[i]>f[j] then f[j]:=f[j-w[i]]+c[i];
    write(f[m]);
end.
```

---

