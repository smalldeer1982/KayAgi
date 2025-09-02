# [USACO03FALL] Cow Exhibition G

## 题目背景




## 题目描述

奶牛想证明它们是聪明而风趣的。为此，贝西筹备了一个奶牛博览会，她已经对 $N$ 头奶牛进行了面试，确定了每头奶牛的智商和情商。

贝西有权选择让哪些奶牛参加展览。由于负的智商或情商会造成负面效果，所以贝西不希望出展奶牛的智商之和小于零，或情商之和小于零。满足这两个条件下，她希望出展奶牛的智商与情商之和越大越好，请帮助贝西求出这个最大值。


## 说明/提示

选择第一头，第三头，第四头奶牛，智商和为−5+6+2 = 3，情商和为7−3+1 = 5。再加

入第二号奶牛可使总和提升到10，不过由于情商和变成负的了，所以是不允许的


## 样例 #1

### 输入

```
5
-5 7
8 -6
6 -3
2 1
-8 -5```

### 输出

```
8```

# 题解

## 作者：学而思李老师 (赞：180)

此题是练习01背包变形一道非常好的题

- Q1 为啥要用01背包而不是其它算法？
- 答：我们发现，每只奶牛只有选和不选两种状态，而且是需要**决策**的，所以01背包绝对是最好的选择

下面将会对 OI 中01背包问题的基本解题步骤进行详细的讲解

### 一、01背包基本思考步骤

在考场上，思考关于动态规划的问题一般分三步：

1. 确定如何表示状态
2. 推导状态转移方程
3. 思考动规初始状态

下面，我将以此题为例，具体讲解一下这些步骤。

### 二、如何表示状态

01背包中，一定要想好什么是**体积**，什么是**价值**，什么是**背包容量**。此题中，我们可以把体积看成奶牛的智商，背包容量看成奶牛的个数，价值看成奶牛的情商。所以这题的状态表示就是：

$dp[i][j]$ 表示前 $i$ 只奶牛中，总智商为 $j$ 时情商的最大值

最终的答案是智商与情商之和的最大值，所以可以把 $dp$ 数组扫一遍，取 $dp[n][j]+j$ 的最大值，其中$1\leq j\leq n, dp[n][j] \geq 0$。

一开始想的状态表示可能有错（比如此题），需要在完成后面的步骤后进行修改。

### 三、状态转移方程

这其实是 dp 里面最难的一步，但此题的状态转移方程还是比较好想的。

每只牛有两种选择：参加会展和不参加会展。我们要求在智商一定的情况下情商的最大值，这其实就是01背包的模板。状态转移方程的推导如下：

- 第 $i$ 只奶牛不参加会展：$dp[i][j]=dp[i-1][j]$
- 第 $i$ 只奶牛参加会展：$dp[i][j]=dp[i-1][j-a[i].iq]+a[i].eq$
- 加上决策，选取上面两种情况的最大值：$dp[i][j]=\max(dp[i-1][j], dp[i-1][j-a[i].iq]+a[i].eq)$

这就是我们此题的状态转移方程了。

当然，此题开二维数组会MLE（拿计算器算一下，学过初赛的应该都会算吧），我们发现每次的 $dp[i][j]$ 只和上一行有关，所以我们可以把 $dp$ 数组优化成一维（这也是01背包模板的一部分）
$$dp[j]=\max(dp[j], dp[j-a[i].iq]+a[i].eq)$$

- Q2：有一些傻傻的奶牛智商居然是负的，这样导致 $j-a[i].iq$ 比 $j$ 大，在 $dp[j]$ 的右上角，而那些聪明的正智商的奶牛会在 $dp[j]$ 的左上角，那压成一维后动规的顺序是什么呢？
- 答：可以在动规的时候判断一下，如果这只奶牛很傻，那么正着dp，否则反着dp。

### 四、初始状态

最后，我们要考虑dp的初始状态，也就是边界条件。这个过程有点类似于写 dfs 时寻找出口，也就是把一眼能看出答案的地方直接赋值。比如我们这个 $dp[0]$，在没有奶牛时最大情商是多少呢？肯定是 $0$。所以我们的一个边界条件是 $dp[0]=0$

可是，我们的情商能是负数。如果把数组定义成全局变量，默认所有元素为 $0$ 的话，dp的过程中取最大值有可能一直为 $0$。所以，我们还要把数组的其它元素赋值成一个非常小的值。头文件 $\mathtt{cstring}$ 里的 $\mathtt{memset}$ 函数可以解决这个问题，把数组中每一个元素都赋值为 $-\infty$。具体用法： $\mathtt{memset(dp, -0x3f, sizeof\;dp);}$

但是，此时一个棘手的问题出来了：因为 $a[i].iq$ 和 $a[i].eq$ 都有可能是负数，所以会导致数组越界。这时，我们可以把 $dp$ 数组向右移动 $400000$ 位。数组的改变意味着我们状态的定义也会发生改变：

$dp[j]$ 表示在奶牛智商之和为 $j-400000$ 时，情商的最大值。

是不是又学会一招？在数组下标可能为负数时，将其右移可以有效避免数组越界。但是在最后求答案时，不要忘记我们求得其实是 $dp[j]+j-400000$ 的最大值。还有一个易错点：别忘记特判无法保证智商和情商无法保证大于 $0$ 的情况！

最后附核心 dp 代码：

```cpp
	memset(dp, -0x3f, sizeof dp);
	dp[400000] = 0;
	for(int i = 1; i <= n; i ++)
	{
		if(a[i].iq >= 0)
			for(int j = 800000; j >= a[i].iq; j --)
				dp[j] = max(dp[j], dp[j-a[i].iq] + a[i].eq);
		else
			for(int j = 0; j <= 800000 + a[i].iq; j ++)
				dp[j] = max(dp[j], dp[j-a[i].iq] + a[i].eq);
	}
	for(int i = 400000; i <= 800000; i ++)
		if(dp[i] > 0)
			ans = max(ans, i + dp[i] - 400000);
```


---

## 作者：a13518354766 (赞：102)

## # **此题搜索可以过！！！**
看到此题,第一想法,是01背包,然而,作为一个蒟蒻,~~我怎么会打正解呢？~~,于是就开始打dfs！

想要完成此题,普通的搜索肯定是过不了的(~~不然要dp干嘛~~),所以,我们要考虑

#### 剪枝
比较容易的,我们可以轻松想出来剪枝:

(不吐槽名字我们还是好朋友。。。)

1.用数组guji[i]表示搜索到i时,不考虑智商,情商必须大于零的限制,之后能获得的最大智,情商之和。如果当前搜索到的智,情商之和加上guji[i]任然小于等于已经搜出来的ans,那么,当前的状态一定不是最优的(这属于最优性优化)

2.用数组jiuz[i](救智商。。。2333)表示搜索到i时,不考虑其他限制,之后能获得的最大的智商。如果当前搜索到的智商加上jiuz[i]任然小于0,那么,当前状态一定不满足智商必须大于零的限制。

3.用数组jiuq[i]表示搜索到i时,不考虑其他限制,之后能获得的最大的情商。同2

然后。。。你就A了。。。测试速度25ms。。。(orz)

代码：

    //#pragma GCC optimize()//手动Ox优化
    #include<bits/stdc++.h>
    using namespace std;
    const int N=402;//记得多开1位,因为要访问n+1
    int z[N],q[N];
    int ans=0;
    int n;
    int guji[N],jiuz[N],jiuq[N];
    inline void dfs(int now,int zh,int qh){
        if(zh+qh+guji[now]<=ans){
            return;
        }
        if(zh+jiuz[now]<0){
            return;
        }
        if(qh+jiuq[now]<0){
            return;
        }
        if(now==n+1){//如果搜索到底
            ans=zh+qh;//由于当前答案一定最优,直接赋值
            return;
        }
        dfs(now+1,zh+z[now],qh+q[now]);
        dfs(now+1,zh,qh);
    }
    int main(){
        scanf("%d",&n);
        for(int i=1;i<=n;++i){
            scanf("%d%d",&z[i],&q[i]);
        }
        for(int i=n;i>=1;--i){
            guji[i]=guji[i+1];
            jiuz[i]=jiuz[i+1],jiuq[i]=jiuq[i+1];
            if(z[i]>0){//如果智商大于0
                jiuz[i]+=z[i];//智商可取最大值加上z[i]
            }
            if(q[i]>0){
                jiuq[i]+=q[i];//情商可取最大值加上q[i]
            }
            if(z[i]+q[i]>0){//如果和大于零
                guji[i]+=z[i]+q[i];//最大值加上z[i]+q[i]
            }
        }
        dfs(1,0,0);
        cout<<ans;
        return 0;
    }
    /**
    *　　┏┓　　　┏┓+ +
    *　┏┛┻━━━┛┻┓ + +
    *　┃　　　　　　　┃
    *　┃　　　━　　　┃ ++ + + +
    *  ████━████+
    *  ◥██◤　◥██◤ +
    *　┃　　　┻　　　┃
    *　┃　　　　　　　┃ + +
    *　┗━┓　　　┏━┛
    *　　　┃　　　┃ + + + +Code is far away from 　
    *　　　┃　　　┃ + bug with the animal protecting
    *　　　┃　 　 ┗━━━┓ 神兽保佑,代码无bug　
    *　　　┃ 　　　　　　 ┣┓
    *　　  ┃ 　　　　　 　┏┛
    *　    ┗┓┓┏━┳┓┏┛ + + + +
    *　　　　┃┫┫　┃┫┫
    *　　　　┗┻┛　┗┻┛+ + + +
    */



---

## 作者：YJunJ (赞：62)

我们发现这道题对于每头奶牛无非也是选或不选两种状态。那么01背包同样是选或不选两种状态，不妨试着将本题转成01背包？那么何为代价？发现有两个元素：情商，智商。而这两个元素对于题来说都是等价的，那么是不是任选一个作为背包代价也可以呢？我们来试试：假设智商为代价，即 f[j] 为当智商为 j 时情商的最大值。（为什么 f[j] 不能表示为智商与情商的和 后面再说）再思考状态转移，模仿01背包，得出方程 
```cpp
	f[j]=max(f[j],f[j-cow[i].s]+cow[i].f);
```
（cow.s 为智商，cow.f 为情商）但是又由题可得转移时 j 有可能在某个时刻为负数，当然最终答案里的 j 和 f[j] 都大于等于 0，为了防止数组越界，我们可以把 j 整体向右移动一些单位，移动多少呢？因为1 ≤ N ≤ 400 且 −1000 ≤ 奶牛的情商和智商 ≤ 1000，所以任意一个时刻 j 最小为 400 ×（-1000）= -400000，最大为 400 ×（1000）= 400000 那么我们将 j 整体向右移 400000 就好了。移动完后的 f[j] 就是移动前的 f[j-400000] 。例如移动后的 400000 就对应着移动前的 0 也就是原来的最小值。而移动后的 800000 就对应着移动前的 400000 也就是原来的最大值。至此我们便已经解决了 j 为负时的问题。现在已经很像01背包了（智商为代价，情商为价值，背包容量为 0～800000），但是还有一点不同，就是物品代价有可能为负，这就导致了我们不能跟01背包一样全部都倒序枚举背包容量然后进行状态转移，若当我们从800000开始倒序枚举，假设我们已经枚举过 j = 666666 这个状态并且当前我们在 j = 666660，同时当前的 cow.s = -6，那么此时我们就会回退到 666666 这个状态，万一在状态 666666 已经把 cow 选了一遍，现在就会又再选一遍，显然这样是不行的。既然有些为负，那么我们就只把 cow.s 为负的几个奶牛单独用正序枚举，这样若要减去一个 cow.s 也不会出现重选的情况了。至此，一个完整DP就设计出来了：

```
	for(int i=1;i<=n;i++) {
        if(cow[i].s>=0) {
            for(int j=800000;j>=cow[i].s;j--)       //非负数就倒叙枚举
                f[j]=max(f[j],f[j-cow[i].s]+cow[i].f);
        }else {
            for(int j=0;j<=800000+cow[i].s;j++)     //负数就正序枚举
                f[j]=max(f[j],f[j-cow[i].s]+cow[i].f);
        }
    }
```

在最终找答案的时候从 j = 400000 -> 800000 范围内找就行了，因为 400000 对应着移动前的 j = 0（智商和要为非负数）。 
为什么 f[j] 不能表示为智商与情商的和？  
因为在找答案时就无法判断当前状态的情商和是否为负数。  

代码：  
跑得比较慢～
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int n,m,maxx=-2147483647,f[800005];
struct {
    int s,f;
}cow[405];
int max(int a,int b) {
    return a>b?a:b;
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&cow[i].s,&cow[i].f);
    memset(f,-0x3f,sizeof(f));
    f[400000]=0;
    for(int i=1;i<=n;i++) {
        if(cow[i].s>=0) {
            for(int j=800000;j>=cow[i].s;j--)
                f[j]=max(f[j],f[j-cow[i].s]+cow[i].f);
        }else {
            for(int j=0;j<=800000+cow[i].s;j++)
                f[j]=max(f[j],f[j-cow[i].s]+cow[i].f);
        }
    }
    for(int i=400000;i<=800000;i++)
        if(f[i]>=0)
            maxx=max(maxx,f[i]+i-400000);
    printf("%d\n",maxx);
    return 0;
}
```

---

## 作者：monstersqwq (赞：48)

~~个人认为这题难度不到蓝，不过是绿还是黄就不确定了。~~

我们发现这道题中虽然看起来很复杂，但是其实也就是选哪几个奶牛可以满足要求，于是我想到了一句歌词：

> 01背包主要关注选与不选的问题

（出处：[我们仍未知道那天所看见的算法的名字](https://www.bilibili.com/video/av20220384?spm_id_from=333.338.__bofqi.13)）

所以，这道题就是一个01背包。

### 1.1：

知道了01背包，那么就要确定三个问题：

- 初值

- 状态转移方程

- 答案

先说一下定义：$dp_{i,j}$ 表示前 $i$ 个物品，智商为 $j$ 时，情商的最大值。（情商和智商可以相互转换，也没有什么关系）

初值：$dp_{0,0}=0$，其他都不可能。（不能用 $-1$ 代表不可能，因为题目中有负数，这里建议用 ~0x3f3f3f3f）

状态转移方程：标准01背包写法：$dp_{ij}=\max(dp_{i-1,j},dp_{i-1,j-iq_{i}}+eq_i)$（智商和情商的不同于题面，请自行理解）

答案：当 $dp_{n,k} \ge 0$ 时，所有 $k+dp_{n,k}$ 的最大值（$0 \le k \le MR$）（$MR=400000$，即智商或情商的最大值）。

现在，我们得到了最朴素的01背包写法：

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#define MR 400000
using namespace std;
int n,iq[405],eq[405],dp[405][MR+20],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>iq[i]>>eq[i];
	}
	memset(dp,~0x3f3f3f3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
	{
        for(int j=0;j<=MR;j++)
        {
            if(j-iq[i]>=-MR&&j-iq[i]<=MR)//判断是否在范围内
            dp[i][j]=max(dp[i-1][j],dp[i-1][j-iq[i]]+eq[i]);
        }
	}
	for(int i=0;i<=MR;i++)
	{
		if(dp[i+MR]>=0)
		{
			ans=max(i+dp[n][i+MR],ans);
		}
	}
	cout<<ans<<endl;
    return 0;
}
```
但是，如果你就把它交上去的话，就会得到满屏的 MLE。

这时我们发现数组开大了，改小一点准备搞部分分时，又发现只能搞到一个点，于是便反应过来正确性也有问题。

所以我们要解决两个问题：

- 正确性
- 空间

### 2.1：正确性

为什么会错误呢？实际上是因为数组越界，可能出现负数。（因为可以中途是负数，但是最后又攒了很多正的数回来大于0）

于是，我们发现要处理的 $j$ 并不是 $0 \le j \le MR$，而是 $-MR \le j \le MR$，为了避免负数，我们把本来的 $dp_{i,j}$ 在 $dp_{i,j+MR}$ 上赋值，就可以有效避免负数下标的出现。

代码就不放了，除了每次使用 $dp$ 数组是时第二维要 $+MR$ 和数组的定义以外没啥区别。

### 2.2：空间

当然不满足于只骗部分分，于是我们要想办法把二维的 $dp$ 压成一维的。

首先我们想到喜闻乐见的滚动数组操作（即一直用同一个数组，用 $n$ 次），但是此题中 $iq$ 有正有负，无法判断是正着循环还是倒着循环，于是可以先判断正负再选择正着循环还是倒着循环，可以减少掉 $dp$ 的第一维。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#define MR 400000
using namespace std;
int n,iq[405],eq[405],dp[MR*2+20],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>iq[i]>>eq[i];
	}
	memset(dp,~0x3f3f3f3f,sizeof(dp));
	dp[0+MR]=0;
	for(int i=1;i<=n;i++)
	{
		if(iq[i]>0)
		{
			for(int j=MR;j>=-MR;j--)
			{
				if(-MR<=j-iq[i]&&j-iq[i]<=MR)
				dp[j+MR]=max(dp[j+MR],dp[j-iq[i]+MR]+eq[i]);
			}
		}
		else
		{
			for(int j=-MR;j<=MR;j++)
			{
				if(-MR<=j-iq[i]&&j-iq[i]<=MR)
				dp[j+MR]=max(dp[j+MR],dp[j-iq[i]+MR]+eq[i]);
			}
		}
	}
	for(int i=0;i<=MR;i++)
	{
		if(dp[i+MR]>=0)
		{
			ans=max(i+dp[i+MR],ans);
		}
	}
	cout<<ans<<endl;
    return 0;
}
```
实际上这份代码已经可以通过本题（最慢962ms），但是作者又面临了一个问题——校内 OJ 被卡了，过不去。

### 3.1：几个小小的优化

#### 首先要卡过校内 OJ 

当我考虑优化时间时，我首先看到了对于每个奶牛的循环，对于每个奶牛，都要循环 $2 \times MR=800000$ 次，看起来可以再优化。

于是我想到，可以在 dp 之前先处理出 $maxx,minx$ 两个数组，$maxx_i$ 记录前 $i$ 个奶牛的最大智商是多少，$minx_i$ 记录前 $i$ 个奶牛的最小智商是多少。（用 $O(n)$ 就可解决，具体实现方法是：贪心+前缀和，可以看代码）

然后，每次循环时，可以只从 $minx_i$ 循环到 $maxx_i$，可以大大减少时间。（成功卡过了校内 OJ）

#### 继续优化循环范围

我们可以发现，循环的最小值不仅有 $minx_i$，还有 $-\dfrac{MR}{2}$，因为一旦比这个数字更小，无论后面的 $iq$ 有多高也无法把整体的 $iq$ 拉到 $\ge 0$ 所以就不需要再判断了（实际上通过这个还可以将数组降到 $600000$，不过没什么意义（毕竟不卡空间），就算了）

#### 进行一次类似贪心的选取

如果一个奶牛的 $iq \le 0$ 且 $eq \le 0$，就可以直接跳过，因为这种奶牛纯属“拖油瓶”，无法对结果造成良好的影响，可以直接舍去。

而且因为我们使用滚动数组压空间，所以不必担心中间跳过了一个奶牛导致玄学错误。

至于其它的优化。。。可能只有三目运算符和快读快输之类的吧。

再给出一种其它的压一维做法：因为在第 $i$ 次循环时，只有 $dp_{i},dp_{i-1}$ 对整体有用，可以只保存这两个，每次使用 memcpy 函数来转换即可。代码就不贴了，不然太长。

update：增加了几个小优化和一种新的压一维做法。2020.5.6

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#define MR 400000
using namespace std;
int n,iq[405],eq[405],dp[MR*2+20],ans,maxx[405],minx[405];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>iq[i]>>eq[i];
	}
	memset(dp,~0x3f3f3f3f,sizeof(dp));
	dp[0+MR]=0;
	for(int i=1;i<=n;i++)
	{
		if(iq[i]>0)
		{
			maxx[i]=maxx[i-1]+iq[i];
			minx[i]=minx[i-1];
		}
		else
		{
			maxx[i]=maxx[i-1];
			minx[i]=minx[i-1]+iq[i];
		}
	}
	for(int i=1;i<=n;i++)
	{
        if(iq[i]<=0&&eq[i]<=0) continue;
		if(iq[i]>0)
		{
			for(int j=maxx[i];j>=max(minx[i],MR/(-2));j--)
			{
				if(-MR<=j-iq[i]&&j-iq[i]<=MR)
				dp[j+MR]=max(dp[j+MR],dp[j-iq[i]+MR]+eq[i]);
			}
		}
		else
		{
			for(int j=max(minx[i],MR/(-2));j<=maxx[i];j++)
			{
				if(-MR<=j-iq[i]&&j-iq[i]<=MR)
				dp[j+MR]=max(dp[j+MR],dp[j-iq[i]+MR]+eq[i]);
			}
		}
	}
	for(int i=0;i<=MR;i++)
	{
		if(dp[i+MR]>=0)
		{
			ans=max(i+dp[i+MR],ans);
		}
	}
	cout<<ans<<endl;
    return 0;
}
```

看在我写的这么认真详细的份上，给过呗 qaq。

---

## 作者：狸狸养的敏敏 (赞：26)

本题可用DP求解

考虑01背包，把智商看成体积，情商看成价值

注意是**恰**放入体积为$j$的背包里

转移方程$dp[j]=max(dp[j],dp[j-s[i]]+f[i])$

但是你以为这样就行了吗？？

题目中是会出现负数的！

怎么办？数组偏移啊

从400000开始进行转移，(即开2倍的数组使负数转为正数)

400000是怎么来的呢?最大奶牛数$400$和最大智商$1000$的乘积

另外，还有一个比较重要的点，因为负数的特殊性，转移的时候我们要从0正着向后面找，因为负数是从左往右进行转移的

具体代码如下
```
#include<bits/stdc++.h>
using namespace std;
int s[444],f[444],dp[888888];//s,f如题意，dp数组Emm不需要解释
int n,ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",s+i,f+i);//输入
    memset(dp,-0x7f,sizeof(dp));//恰放入的初始化
    dp[400000]=0;//从400000开始转移
    for(int i=1;i<=n;i++){
        if(s[i]>0)
            for(int j=800000;j>=s[i];j--)
                dp[j]=max(dp[j],dp[j-s[i]]+f[i]);//同01背包
        else
            for(int j=0;j<=800000+s[i];j++)
                dp[j]=max(dp[j],dp[j-s[i]]+f[i]);	//负数要正着做DP，因为他是从左往右进行转移的
    }
    for(int i=400000;i<=800000;i++)//因为不一定智商越大越好,所以要枚举一遍
    if(dp[i]>=0)//注意，只有能够恰放入（被更新过），以及情商非负时，才可以更新答案
    ans=max(ans,i+dp[i]-400000);
    printf("%d\n",ans);//输出答案，换行是个好习惯
    return 0;
}

```

我口胡了，希望这篇题解给过吧QWQ

---

## 作者：Frozen_Heart (赞：9)

~~被绿题支配的恐惧？？？~~ 最开始看到题目是懵逼的，之后看了题解才明白。将**智商和情商分别看作容量和价值**来做01背包。
$F[i]$表示当智商总和为$i$时，情商的最大值。
$$F[i]=max(F[i-a[k]]+b[k])$$
但是有一点我们需要注意，在状态转移的过程中，智商和情商是允许为负数的，所以我们为了考虑到这种情况，将智商往右移$sa$个单位。
欢迎踩[Frozen_Heart](https://www.cnblogs.com/lsgjcya/p/9183448.html)

---

## 作者：ysner (赞：7)

此题为特殊的0-1背包问题。我们可以以情商为物品容量,智商为价值，将其转为正规的01背包问题。（楼下题解认为此方法未看到本质，但这种方法也能AC，但也可能是我造化太浅）

一点小优化（状压 DP）：数组的下标和值都可以存储信息，所以我们可以把智商存在下标上，情商存在值上。

最后要注意：C++ 中没有负数下标，所以我们需要把 dp 数组平移 m（背包容量、为正数情商之和） 位。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int w[105]={},f[105]={},ff[200010]={};
int main()
{
    int n,m=0;
    //freopen("smrtfun.in","r",stdin);
    //freopen("smrtfun.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
      scanf("%d%d",&w[i],&f[i]);//w数组存智商，f数组存情商（w变下标，f变值） 
      if(w[i]>0) m+=w[i];//计算背包容量（情商） 
    }
    m*=2;//m是平移的位数 
    memset(ff,-127/3,sizeof(ff)); 
    ff[m/2]=0;
    for(int i=1;i<=n;i++)
    {
        if(w[i]>0)//根据w[i]的符号确定循环方向，消除后效性,并从这里开始数组平移，防止出现负下标 
        for(int j=m;j>=w[i];j--)//接下来是01背包问题模板，保证每件物品只选一次 
          ff[j]=max(ff[j],ff[j-w[i]]+f[i]);
        else
        for(int j=0;j<=m-w[i];j++)//这个循环是数组平移弄出来的，由上个循环经数学运算得来。上个循环是m->w[i]，两边乘-1，变成-w[i]**<-**-m，再加m，即得到m-w[i]**<-**0 
          ff[j]=max(ff[j],ff[j-w[i]]+f[i]);
    }
    int ans=0,k=m/2;//k是平移的位数
    for(int i=0;i<=k;i++)
      if(ff[i+k]>=0 && i+ff[i+k]>ans)//ff[i+k]存的是情商，必须判断非负数，而从0开始的下标保证智商没负数 
        ans=i+ff[i+k];////i是智商，ff[i+k]是情商 
    printf("%d",ans);
    //fclose(stdin);
   // fclose(stdout);
    return 0;
}
可能小蒟蒻对这道题的解法不够好，也希望神牛指教。
```

---

## 作者：ShineEternal (赞：5)

[如有不能正常显示的LaTeX请来这里](https://blog.csdn.net/kkkksc03/article/details/102093788)

## description:
贝西有权选择让哪些奶牛参加展览。由于负的智商或情商会造成负面效果，所以贝西不希望出展奶牛的智商之和小于零，或情商之和小于零。满足这两个条件下，她希望出展奶牛的智商与情商之和越大越好，请帮助贝西求出这个最大值。

## solution:
这道题可以想到用背包来做。

因为两个商是相对等价的，所以我们设一个为“价格”，一个为“价值”就行了。

这样就可以分别判断数组的下标和这个下标内值的正负来确认它是否可以更新答案。

但是下标有一个弊端就是不能为负

但这样也简单，只要把它们统一加上一个大值就行了。

注意这里也不能乱加，因为这个是要算入背包时间复杂度的，加上400*1000=400000就行了。

然后洛咕的数据好玄学，读入的数组开小了4倍还能A...
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int s[105],f[105];
int dp[900005];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&s[i],&f[i]);
	}
	memset(dp,-0x3f,sizeof(dp));
	dp[400000]=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]>=0)
		for(int j=800000;j>=s[i];j--)
		{
			dp[j]=max(dp[j],dp[j-s[i]]+f[i]);
		}
		else
		{
			for(int j=0;j<=800000+s[i];j++)
			{
				dp[j]=max(dp[j],dp[j-s[i]]+f[i]);
			}
		}
	}
	int ans=0;
	for(int i=400000;i<=800000;i++)
	{
		if(dp[i]>=0)
		{
			ans=max(ans,dp[i]+i-400000);
		}
	}
	printf("%d\n",ans);
	return 0;
} 
```


---

## 作者：chenzida (赞：3)

解析：由于这是每个奶牛装或不装，很明显这是一个 01 背包

状态：$dp[i][j]=x$ 表示考虑到1到 i 头奶牛，智商和为 j 的最大情商和为 x。

答案：$max(dp[n][j])$ $(0\leq$ $j\leq400000)$。

转移：$dp[i][j]$ $=max$ $(dp[i-1][j-IQ[i]]+EQ[i],dp[i-1][j])$。

初值：$memset(dp,-999999,sizeof(dp));
dp[i][0]=1$ $(0\leq$ $i\leq$ $n$ $)$。

但是由于 j 有可能为负数，所以要将 dp 数组整体平移。

由 -400000 到 400000 变成 0 到 800000。

所以这个思路对吗？

你只要稍微测试一下就知道，这个思路会 MLE。

下面来介绍一下我的解决方法：滚动数组！！！

这是指在第 i 项只与第 i-1 项有关系的一种 dp 优化方法，这可以将第 i-2 项之前省略，能节省空间。

数组滚动后的代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int IQ[401],EQ[401];
int dp[3][800001];
int ans;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&IQ[i],&EQ[i]);
    }
    memset(dp,-999999,sizeof(dp));
    dp[1][400000]=0;
    dp[2][400000]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=800000;j++)
        {
            if(j>IQ[i])
            {
                dp[2][j]=max(dp[1][j],dp[1][j-IQ[i]]+EQ[i]);
            }
            else
            {
                dp[2][j]=dp[1][j];
            }
        }
        for(int j=1;j<=800000;j++)
        {
            dp[1][j]=dp[2][j];
        }
    }
    for(int i=400000;i<=800000;i++)
    {
        if(dp[1][i]>=0) ans=max(ans,dp[1][i]+i-400000);
    }
    cout<<ans;
    return 0;
}
```




---

## 作者：MilkyCoffee (赞：3)

如何表示状态？
```
dp[j]  前i只奶牛用for完成。
```
状态转移方程？
```
dp[j] = max(dp[j], dp[j−s[i]] + f[i])
```
初始状态？
```
memset(dp, −0x3f, sizeof(dp)); 负无穷

dp[400000] = 0;
```
### 代码

```
#include<bits/stdc++.h>
using namespace std;

int n;
int s[405], f[405];
int dp[400005];
const int MR = 100000;

int main() {
    memset(dp, -0x3f, sizeof(dp));
	cin >> n;
	for (int i = 1; i <= n; i++) {
	    cin >> s[i] >> f[i];
	}
	dp[MR] = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] >= 0) {
		    for (int j = 2 * MR; j >= s[i]; j--) {
		        dp[j] = max(dp[j], dp[j - s[i]] + f[i]);
		    }
		} else {
		    for (int j = 0; j <= 2 * MR + s[i]; j++) {
		        dp[j] = max(dp[j], dp[j - s[i]] + f[i]);
		    }
		}
	}
	int ans = 0;
	for (int i = MR; i <= 2 * MR; i++)
		if (dp[i] >= 0)
			ans = max(ans, i + dp[i] - MR);
	cout << ans << endl;
    return 0;
}
```


---

## 作者：WAMonster (赞：3)

### 沿用各位dalao的思路，这里只是介绍一下一种数组平移的~~偷懒~~方法。

看见各位dalao们都是拿着400000加啊减的，这题码量不大还好点，如果遇到码量大的题目就很烦了，其实我们可以用指针代替数组。

具体做法：比如对于此题，开个400000\*2以上大小的数组`_f`，下标是从0开始的。我们现在定义一个指针`f`，然后调用这句话：

```cpp
f = _f + 400003 //（为了防止误操作越界，原数组大小开的8e5+7）
```

由于`_f`相当于开辟了连续内存地址的指针（总共开了8e5+7个int类型数据大小），现在把`f`赋值为`_f`后连续内存的中间位置，那么指针`f`前、后各有`4e5`以上的内存。

那么这个`f`怎么用呢？用`*(f - 400000)`？

不需要！我们把它当成数组即可。也就是说，`f[xxx]`和`*(f + xxx)`在某些情况下是等价的。我们大多数时候可以把指针当做数组使用。

然后通过把题意建模成01背包类型的dp，直接做就可以啦！

#### code：
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define maxn 405
#define maxm 800007
int n, iq[maxn], eq[maxn], _f[maxm], ans;
int *f;
#define isdigit(x) ((x) >= '0' && (x) <= '9')
inline int read() {
	int res = 0, flag = 0;
	char c = getchar();
	while (!isdigit(c)) flag = c == '-', c = getchar();
	while (isdigit(c)) res = (res << 1) + (res << 3) + (c ^ 48), c = getchar();
	return flag ? -res : res;
}
int main() {
	f = _f + 400003;
	n = read();
	for (int i = 1; i <= n; ++i) iq[i] = read(), eq[i] = read();
	memset(_f, 0xcf, sizeof(_f));
	f[0] = 0;
	for (int i = 1; i <= n; ++i)
		if (iq[i] > 0) {
			for (int j = 400000; j - iq[i] > -400000; --j) f[j] = max(f[j], f[j - iq[i]] + eq[i]);
		} else {
			for (int j = -400000; j <= 400000 + iq[i]; ++j) f[j] = max(f[j], f[j - iq[i]] + eq[i]);
		}
	for (int i = 0; i <= 400000; ++i) if (f[i] >= 0) ans = max(ans, i + f[i]);
	printf("%d", ans);
	return 0;
}

```

我说的一大堆都很基础，不过有时候也很有用，有兴趣可以做一下这题=>[【P5026】Lycanthropy](https://www.luogu.org/problemnew/show/P5026)。

---

## 作者：Y_B_Y (赞：2)

# 一题背包题

### 定义
- s[i]表示情商,f[i]表示智商

- 由于智商情商可以为负所以我们设一个mid=450000用dp[k]表示情商为k时智商的最大值(情商总和最低为-400000所以mid用450000)然后每个数组的下标都加上mid这样就可以存负数了(例如dp[-1]表示为dp[449999])

~~本来是打算用map的,然后被速度慢和麻烦劝退了~~

- 由于情商可以为负也可以为正,所以背包正着循环不行反着也不行 ~~(当然你可以全都要)~~ 数组加上表示第几头牛会爆炸,所以这里用dp[1][k]表示上一次的结果,dp[2][k]表示本次循环的结果,然后用dp[2][k]刷新dp[1][k]

- k的取值为low<=k<=high(low为到现在情商出现的最小值所以当情商小于零时low+=情商,high为到现在情商出现的最大值所以当情商不小于零时high+=情商)

### 初始化

- for(int p=-400000;p<=400000;p++) dp[2][mid+p]=-5641239;//因为智商情商可能为负所以初始化为一个很小的数

- dp[2][mid]=0;//相当于一开始智商情商都为0
    


### 状态转移方程
```
dp[2][k+s[i]+mid]=max(dp[2][k+s[i]+mid],dp[1][k+mid]+f[i]);(1<=i<=n,low<=k<=high)
```

### 找最大值 
ans=max(ans,dp[2][p+mid]+p);(0<=p<=400000)注意dp[2][p+mid]一定要大于零
## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define low lll//防止已经被定义出现错误
#define high gggg//同上
int n,s[10001],f[10001];//前面都提到过
int ans=0,dp[3][900000],mid=450000,low,high;//同上
int main()
{
	cin>>n;//输入
	for(int p=1;p<=n;p++) cin>>s[p]>>f[p];//输入
	for(int p=-400000;p<=400000;p++) dp[2][mid+p]=-5641239;//初始化
	dp[2][mid]=0;//同上
	for(int i=1;i<=n;i++)//开始dp
	{
		for(int k=high;k>=low;k--) dp[1][k+mid]=dp[2][k+mid];//用dp[2][k]刷新dp[1][k]
		for(int k=high;k>=low;k--)
		{
			if(dp[1][k+mid]>-5000000)//判断dp[k+mid]是否成立,如果不满足表示搭配不出这个数,不需要计算(不过好像没必要)
			{
			dp[2][k+s[i]+mid]=max(dp[2][k+s[i]+mid],dp[1][k+mid]+f[i]);
		        }
		}
		if(s[i]<=0) low+=s[i];
		else high+=s[i];//刷新low与high的值
	}
	for(int p=0;p<=400000;p++) if(dp[2][p+mid]>=0) ans=max(ans,dp[2][p+mid]+p);//找最大值,注意if(dp[2][p+mid]>=0)是必须的
	cout<<ans;//输出
}
```




---

## 作者：RainFestival (赞：2)

dp

如果爆搜会大大的时间超限

而我们还要考虑负数的情况（样例）

空间不够，滚动数组省空间

设f[i][j]为用到第i只奶牛，智商为j时情商最大值(注意负数）

选第i只奶牛f[i-1][j-a[i]]+b[i]

不选第i只奶牛f[i-1][j]

取一个max就可以了

最后统计f[n][j]+j(注意他们都不是负数）

记得附加滚动数组，不然约63分

下面是代码63分：


```pascal
var
  n,i,j:longint;
  s,ans:longint;
  a,b:array[-5..1005] of longint;
  f:array[-5..405,-8005..8005] of longint;
function max(x,y:int64):int64;
begin
  if x>y then exit(x)
         else exit(y);
end;
begin
  readln(n);
  for i:=1 to n do
    begin
      readln(a[i],b[i]);
      s:=s+abs(a[i]);
      //writeln(s);
    end;
  for i:=0 to n do
    for j:=-2*s to s*2 do
      f[i][j]:=-100000000;
  f[0][0]:=0;
  //writeln(s);
  for i:=1 to n do
    for j:=-1*s to s do
      f[i][j]:=max(f[i-1][j-a[i]]+b[i],f[i-1][j]);
  //for i:=1 to n do
    //begin
      //for j:=-s to s do
        //write(f[n][j],' ');
      //writeln;
    //end;
  //writeln(0);
  for i:=0 to s do
    if (f[n][i]+i>ans) and (f[n][i]>0) then ans:=f[n][i]+i;
  writeln(ans);
end.
```

AC：

```pascal
var
  n,i,j:longint;
  s,ans:longint;
  a,b:array[-5..1005] of longint;
  f:array[-5..5,-800005..800005] of longint;
function max(x,y:int64):int64;
begin
  if x>y then exit(x)
         else exit(y);
end;
begin
  //writeln(sizeof(f)/1024/1024:0:2);
  readln(n);
  for i:=1 to n do
    begin
      readln(a[i],b[i]);
      s:=s+abs(a[i]);
      //writeln(s);
    end;
  for i:=0 to 1 do
    for j:=-2*s to s*2 do
      f[i][j]:=-100000000;
  f[0][0]:=0;
  //writeln(s);
  for i:=1 to n do
    for j:=-1*s to s do
      f[i and 1][j]:=max(f[(i-1) and 1][j-a[i]]+b[i],f[(i-1) and 1][j]);
  //for i:=1 to n do
    //begin
      //for j:=-s to s do
        //write(f[n][j],' ');
      //writeln;
    //end;
  //writeln(0);
  for i:=0 to s do
    if (f[n and 1][i]+i>ans) and (f[n and 1][i]>0) then ans:=f[n and 1][i]+i;
  writeln(ans);
end.
```
谢谢巨佬们的观赏！！！

---

## 作者：ModestCoder_ (赞：1)

话说我是第一次做c++处理数组负下标的题目

可以很快的想到用智商作为下标，$dp_i$表示智商和为$i$的最大情商和
直接上01背包

对于智商$s$为正，大到小枚举，为负，小到大枚举，主要是要满足01背包

由样例得知，中途智商/情商和<0是可以接受的，存在逆袭情况

所以dp数组需要记录负下标

c++无法负下标，所以全部下标加上$400000$

因为和的上界是400000

你最终判断一下两个和都得>0

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 800010
using namespace std;
int n, dp[maxn], ans;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read();
	memset(dp, -0x3f, sizeof(dp));
	dp[400000] = 0;
	while (n--){
		int s = read(), f = read();
		if (s > 0) for (int i = 800000; i >= s; --i) dp[i] = max(dp[i - s] + f, dp[i]); else
		for (int i = 0; i <= 800000 + s; ++i) dp[i] = max(dp[i - s] + f, dp[i]);
	}
	for (int i = 400000; i <= 800000; ++i)
		if (dp[i] >= 0) ans = max(ans, dp[i] + i - 400000);
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：紫薯布丁 (赞：1)

# 我们可以用不同的方法来AC（~~tle~~）这道题




### 看到这道题首先想到的方法是记忆化搜索 ~~因为好打嘛~~


### 从第一只奶牛开始深搜，等到情商和智商都不小于0的时候更新答案

同时我们就智商和情商都不小于零时更新到每个奶牛的答案判重剪枝 


代码既好写又好想
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
#include<cstring>
#include<algorithm>
#define ss 808087
using namespace std;
inline int read(){
	int x(0),f(1);char c(getchar());
	for(;!isdigit(c);c=getchar()) c=='-'?f=-1:1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return  x*f;
}

inline bool cmp(int a,int b){return a>b;}
map<int ,int >p;
int n,w[505],v[505],cnt(0),ans=0;
inline void dfs(int v1,int v2,int step){
	if(step==cnt){
		if(v1<0||v2<0) return;
		if(v1+v2<ans) return;
		ans=v1+v2;return ;
	}
	if(p[step]>v1+v2&&v1>=0&&v2>=0) return ;
	if(v1>=0&&v2>=0) p[step]=v1+v2;
	if(step>cnt) return;
	dfs(v1,v2,step+1);
	dfs(v1+w[step+1],v2+v[step+1],step+1);
	
}

int main(){
	n=read();
	for(register int i=1;i<=n;i++){
		int x(read()),y(read());
		if(x<0&&y<0) continue;
		w[++cnt]=x;v[cnt]=y;
		//f[x+400000]=y;
	}
	dfs(0,0,1);
	dfs(w[1],v[1],1);
	printf("%d\n",ans);
}
```
~~实际上跟不剪枝相比变化不大~~

------------




### 所以我们现在考虑dp做法

### 我们让F[i][j]表示到第i号奶牛的情商总和为j时的最优智商
（但情商有可能是负数啊，这咋办嘞）可以同时加上一个较大的数字让他变成非负数。数据范围已经给了我们这个数，400*1000=400000。




对于每一只奶牛，我们可以选择或者不选。

我们就可以写出状态转移方程
## f[i][j]=max(f[i-1][j],f[i-1][j-v1[i]]+v2[i])

## 咦，这就是个裸的背包啊！


### 于是我们压缩状态，就有了



## f[j]=max(f[j],f[j-v[i]]+w[i]);



#### 需要注意的是，负数比较特殊，跟正数不同，我们需要正着循环j
#### 还有一个小优化就是，当一只奶牛的智商和情商都是负数的时候，我们还要他干啥？扔掉！

附代码

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
#include<cstring>
#include<algorithm>
#define ss 808087
using namespace std;
inline int read(){
	int x(0),f(1);char c(getchar());
	for(;!isdigit(c);c=getchar()) c=='-'?f=-1:1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return  x*f;
}

inline bool cmp(int a,int b){return a>b;}

int n,w[505],v[505],cnt(0),ans=0,f[ss];
int main(){
	n=read();
	for(register int i=1;i<=n;i++){
		int x(read()),y(read());
		if(x<0&&y<0) continue;
		w[++cnt]=x;v[cnt]=y;
		f[x+400000]=y;
	}
	memset(f,0xcf,sizeof(f));f[400000]=0;
	for(register int i=1;i<=cnt;i++){
		if(v[i]>0){
			for(int j=800000;j>=v[i];j--)
			f[j]=max(f[j],f[j-v[i]]+w[i]);
		}
		else {
			for(int j=0;j<=800000+v[i];j++)
			f[j]=max(f[j],f[j-v[i]]+w[i]);
		}
	}
	for(register int i=400000;i<=800000;i++) 
	  if(f[i]>=0) 
	     ans=max(ans,f[i]+i);
	printf("%d\n",ans-400000);
}
```
求过







---

## 作者：hyr1357 (赞：1)

动规渣看过来了，搜索+剪枝A掉这题

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
int a[100010][2],ans,n,q[100010];
void dfs(int k,int s1,int s2)
{
    if(s1+s2+q[k]<=ans)
     return;
    if(s1>=0&&s2>=0&&ans<s1+s2)
     ans=s1+s2;
    if(k==n+1)
     return;
    if(a[k][0]<=0&&a[k][1]<=0)
     dfs(k+1,s1,s2);
    else
    {
        dfs(k+1,s1+a[k][0],s2+a[k][1]);
        dfs(k+1,s1,s2);
    }
} 
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {scanf("%d%d",&a[i][0],&a[i][1]);
     if(a[i][0]+a[i][1]>0)
      q[i]=a[i][0]+a[i][1];}
    for(int i=n-1;i>=1;i--)
     q[i]+=q[i+1];
    dfs(1,0,0);
    cout<<ans;
    return 0;    
}
```

---

## 作者：草原飞飞羊 (赞：1)

好题啊!好题!

好一个DP!

这道题我也没啥好说的,直接上代码!为防止抄袭,代码中有些地方没有,请大家自己敲!代码

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#define for1(i,a,b) for(int i=a;i<=b;++i)
#define for2(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
const int MR=400000;
int f[2*400000+10],q[401],z[401],ans;
//因为如果开2维数组会炸,故用情商和作为数组下标,让f[i]表示情商和为i时智商之和的最大值. 
//注意:这道题要平移!因为奶牛情商和为负时可能后面再加上一些奶牛的情商值会变成正数,所以平移200000.
/*
状态:f[i]表示情商和为i时智商之和的最大值
转移:f[i]=max(f[i],f[i-q[j]]+z[j])
答案:ans=max(i+f[i])
初值:-999999,f[400000]=0
*/
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
   	std::ios::sync_with_stdio(false);
   	int n;
   	cin>>n;
   	memset(f,-999999,sizeof(f));
   	f[400000]=0; 
   	for1(i,1,n) cin>>z[i]>>q[i];//读入,z[]代表智商,q[]代表情商. 
   	for1(i,1,n){
   	   	if(q[i]>0) for2(j,400000<<2,0) if(j-q[i]>=0&&j-q[i]<=2*400000) f[j]=max(f[j],f[j-q[i]]+z[i]);
   	   	else for1(j,0,400000<<2) if(j-q[i]>=0&&j-q[i]<=2*400000) f[j]=max(f[j],f[j-q[i]]+z[i]);
   	}
   	//ans请大家自己写吧 
   	cout<<ans;
   	return 0;
}

```

第一次写题解,求管理放过

---

