# [IOI 2014] friend 朋友

## 题目背景

**这是一道交互题**

## 题目描述

我们建立了一个由编号为 $0,\cdots,n - 1$ 的 $n$ 个人组成的社交网络。网络中的有些对会成为朋友。如果 $x$ 号人成为 $y$ 号人的朋友，则 $y$ 号人同时也会成为 $x$ 号人的朋友。

这些人将通过 $n$ 个阶段加入这个网络，阶段也编号为 $0$ 至 $n−1$。第 $i$ 号人在第 $i$ 个阶段加入。在阶段 $0$，$0$ 号人加入网络并成为唯一的人。此后 $n - 1$ 个阶段的各个阶段，都有一个人会被主持人加入到网络中，而这个主持人可以是已在网络中的任何一个人。在阶段 $i$ 中（$1\le i\le n−1$），该阶段的主持人可以用如下三种方式之一把第 $i$ 号人加入到网络中：

- IAmYourFriend：将第 $i$ 号人仅变成主持人的朋友。
- MyFriendsAreYourFriends：将第 $i$ 号人变成主持人当前的每一个朋友的朋友。 注意，这个方式不会将第 $i$ 号人变成主持人的朋友。
- WeAreYourFriends：将第 $i$ 号人变成主持人的朋友，同时也变成主持人当前的每一个朋友的朋友。

在建立此网络之后，我们想挑选一个调查的样本，也就是说要从网络中选择一组人。由于朋友之间通常拥有相似的兴趣，因此样本不应包含任何一对互为朋友的人。每个人都会有一个调查的可信度，表示为一个正整数，而我们想要找出一个可信度总和最大的样本。

### 任务

给定各阶段的描述以及每个人的可信度值，请找出一个可信度总和最大的样本。你只需要实现函数 `findSample`。

* `findSample(n, confidence, host, protocol)`
	* $n$: 人数.
	* `confidence`: 大小为 $n$ 的数组；`confidence[i]` 表示第 $i$ 号人的可信度。
	* `host`: 大小为 $n$ 的数组；`host[i]` 表示阶段 i 的主持人。
	* `protocol`: 大小为 $n$ 的数组；`protocol[i]` 表示在阶段 （$0<i<n$） 所采用的方式的代码: `0` 代表 IAmYourFriend，`1` 代表 MyFriendsAreYourFriends，而 `2` 代表 WeAreYourFriends。
	* 由于在阶段 `0` 中没有主持人，因此 `host[0]` 和 `protocol[0]` 是没有被定义的，而且在你的程序中也不应访问它们。

这个函数应该返回样本可信度总和的最大值。

## 说明/提示

对于 $100\%$ 的数据，$2 \le n \le 10^5$，$1 \le \mathrm{confidence}[i] \le 10^6$。

|**子任务**|**分值**|$n$|**可信度**|**采用的方式**|
|:-:|:-:|:-:|:-:|:-:|
|1|$11$|$n\leq 10$|$1\leq \mathrm{confidence}\leq 10^6$|全部三种方式|
|2|$8$|$n\leq 1000$|$1\leq \mathrm{confidence}\leq 10^6$|只有 `MyFriendsAreYourFriends`|
|3|$8$|$n\leq 1000$|$1\leq \mathrm{confidence}\leq 10^6$|只有 `WeAreYourFriends`|
|4|$19$|$n\leq 1000$|$1\leq \mathrm{confidence}\leq 10^6$|只有 `IAmYourFriend`|
|5|$23$|$n\leq 1000$|所有可信度值均为 $1$|只有 `MyFriendsAreYourFriends` 和 `IAmYourFriend` 两种方式|
|6|$31$|$n\leq 10^5$|$1\leq \mathrm{confidence}\leq 10^4$|全部三种方式|

## 样例 #1

### 输入

```
6
13 3 6 20 10 15
0 0 0 1 1 2 2 1 0 0
```

### 输出

```
35
```

# 题解

## 作者：Umbrella_Leaf (赞：8)

讲一个其他题解都没有的做法，甚至不需要开空间。

**~~我真没用空间啊，是交互库开的关我啥事啊~~**

### 题意简述

> 给定一张无向图，让你求最大权独立集。
> 
> 但是最大权独立集是 NPC 问题，所以这个图有特殊的构造方式：
> 
> 初始只有一个点 $0$，从 $1$ 到 $n-1$ 依次加入点，每次加入点 $i$ 时有三种选择：
> 
> 0. 给定 $j$，将 $i$ 与 $j$ 连边；
> 1. 给定 $j$，将 $i$ 与 $j$ 的所有邻居连边；
> 2. 给定 $j$，将 $i$ 与 $j$ 和 $j$ 的所有邻居连边。
> 
> $n\le 10^5$。

### 思路分析

我们考虑倒过来做，从大到小依次删掉点 $i$。

分类讨论：

1. $i$ 与 $j$ 连边。我们先把答案加上 $a_i$，然后 $a_j\gets a_j-a_i$。但是可能会 $a_j<a_i$，此时一定不会选 $a_j$，因此应该是 $a_j\gets \max(a_j-a_i,0)$。

2. $i$ 与 $j$ 的所有邻居连边。此时 $i$ 和 $j$ 的所有出边相同，因此他们是否被选也一定相同，所以 $a_j\gets a_j+a_i$。

3. $i$ 与 $j$ 和 $j$ 的所有邻居连边。此时 $i$ 和 $j$ 只能选一个，并且选哪个对其他点来说是一样的，所以 $a_j\gets \max(a_j,a_i)$。

然后就过了，时间复杂度 $O(n)$。

### 代码展示

$b_0$ 没用，所以可以用来存答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int findSample(int n,int* a,int* b,int* opt){
	b[0]=0;
	while(--n)
		if(!opt[n])b[0]+=a[n],a[b[n]]=max(0,a[b[n]]-a[n]);
		else if(opt[n]==1)a[b[n]]+=a[n];
		else a[b[n]]=max(a[b[n]],a[n]);
	return b[0]+a[0];
}
```

Update：有同学发现上面的代码会用到编译器的临时空间，写了个疑似不需要辅助空间的代码：

```cpp
int findSample(int n, int a[], int b[], int opt[]) {
    *b = 0;
    while (--n) {
        opt += n;
        if (*opt) {
            if (*opt &= 1) {
                a += n, *opt = *a, a -= n;
                b += n, a += *b;
                *a += *opt;
                a -= *b, b -= n;
            } else {
                a += n, *opt = *a, a -= n;
                b += n;
                a += *b, *opt -= *a, a -= *b;
                *opt *= -1;
                *opt >>= 31;
                if (*opt) {
                    a += n, *opt = *a, a -= n;
                    a += *b, *a = *opt, a -= *b;
                }
                b -= n;
            }
        } else {
            a += n, *b += *a, a -= n;
            b += n;
            a += n, *opt = *a, a -= n;
            a += *b;
            *a -= *opt;
            *opt = *a, *opt >>= 31;
            if (*opt) *a = 0;
            a -= *b;
            b -= n;
        }
        opt -= n;
    }
    return *b += *a;
}
```

---

## 作者：Acc_Robin (赞：6)

这种神仙题必须得写个题解纪念一下！！！

如果你读完题，发现是个NPC，是不是有砸电脑的冲动了？

好了，言归正传，这道题有它的独特性质——每次都是特定的三种连边方式。

套路地，我们令 $f_i,g_i$ 分别表示 选/不选 $i$ 号节点时以 $i$ 为根的子树的答案。

我们考虑怎么处理这三种连边方式：

约定 $y$ 为当前处理的节点，$x$ 为 `host[y]`，即题目给定的主持人。

#### 情况一

这一种最好处理，就相当于树上最大权独立集（上司的舞会）

那么有转移：

$$
f_x\leftarrow f_x+g_y
$$

$$
g_x\leftarrow g_x+\max(f_y,g_y)
$$

#### 情况二（最麻烦的）

- 如果选了 $x$，那么与 $x$ 连接的节点（记为 $z_1,z_2,\cdots$，泛称为 $z$）一定不会被选，而 $y$ 即将与 $z$ 连边，说明 $y$ 选不选都可以，则有

$$
f_x\leftarrow f_x+\max(f_y,g_y)
$$

- 如果没有选 $x$，同样的，$y$ 选不选都可以

	- 如果 $y$ 也不被选，那么简单地，有
    
    $$
    g_x\leftarrow g_x+g_y
    $$
    
    - 如果 $y$ 被选了，那么 $z$ 必然不能够被选，问题有些棘手，但是接下来的处理就比较神仙了
    
    	我们考虑倒着 $n-1,n-2,\cdots,1$ 进行转移
    	    
    	这样被限制的 $z$ 就到后面处理了，此时不需要考虑。
        
    	引用yhx的话：
        
    	对于后面还未转移的点来说，$v$ 的邻点已经 "没用了"，因此我们需要将它转移到 $f_v$。
        
        那么有
        
        $$
        f_x\leftarrow g_x+f_y
        $$

#### 情况三

这种情况同情况二很类似，唯一的区别是 $y$ 不能和 $x$ 同时选。相当于把情况二中的

$$
f_x\leftarrow f_x+\max(f_y,g_y)
$$

改成

$$
f_x\leftarrow f_x+g_y
$$

大功告成。

代码：

```cpp
#include "friend.h" //在洛谷上交不需要这一句
#include<bits/stdc++.h>
using namespace std;
int g[100009];
int findSample(int n,int f[],int h[],int w[]){
	for(int i=n-1,x;x=h[i],i;--i)
		switch(w[i]){
			case 0:f[x]+=g[i],g[x]+=max(f[i],g[i]);break;
			case 1:f[x]+=max(f[i],g[i]),f[x]=max(f[x],g[x]+f[i]),g[x]+=g[i];break;
			case 2:f[x]+=g[i],f[x]=max(f[x],g[x]+f[i]),g[x]+=g[i];break;
		}
	return max(*f,*g);
}
```

---

## 作者：yangwenbin (赞：4)

# 题解 P5875 【[IOI2014]friend 朋友】

蒟蒻的第一道交互题,我提交了一整页(同时一整天)

就很离谱,一半的提交来自我

[P5875 [IOI2014]friend 朋友](https://www.luogu.com.cn/problem/P5875)

思路来自 : [这位dalao](https://blog.csdn.net/tgop_knight/article/details/44727595) 和 洛谷里的发题解的大佬

这道题目非常的好,我想了很久查了资料才A出来了,

~~要是我在考场上就暴毙了~~ ( 不我连资格都没有 )

这是一道很优秀的 DP 题 , 老师推荐的 , 前后大概想了一个月 .

这道题是一道在图上的最大独立集问题$(NP-hard  ?)$

想一想也应离谱的 , 这个类型的问题没有标准算法,就很离谱.我在这里想了很久,但是如果照着最大独立集的思路去想,那就大错特错了. ( IOI 的出题老师就希望你们这样跳到大坑里呢 ~~( 嘻嘻 )~~ )

不妨换一个思路,考虑到$host[i]$与$i$的关系, 将他们之间连一条边,就有了一棵树,

在通过连边方式的不同,来设定不同的边权 , 没错这就很树形$DP$.

## 考虑做法

不妨设两个数组记录结果 

$chose \lbrack i \rbrack \implies $ 以$i$为根的子树**可以选择**点$i$时的最大点权独立集 

$unchose \lbrack i \rbrack \implies $ 以$i$为根的子树**不可以选择**点$i$时的最大点权独立集

分类讨论：


一、

$ \forall  protocol \lbrack i \rbrack = 0 $

经典的最大独立集的求法：

$ chose \lbrack host \lbrack i \rbrack \rbrack = chose \lbrack host \lbrack i \rbrack \rbrack + unchose \lbrack i \rbrack$

$ unchose \lbrack host \lbrack i \rbrack \rbrack = unchose \lbrack host \lbrack i \rbrack \rbrack + \max ( chose \lbrack  i  \rbrack , unchose \lbrack i \rbrack ) $



------------


二、

$ \forall  protocol \lbrack i \rbrack = 1 $


如果之前选了 $ host \lbrack i \rbrack $，那现在 $ i $  选或不选都行;

假如之前没选$ host \lbrack i \rbrack $，就会有一个$ j $被保留了下来，成为了  $ host \lbrack i \rbrack $ 的邻居，而没有被删除，

这时$ i $ 就需要和$ j $ 连边，

而$ j $已经选了，那$ i $就不能选，所以方程已经确定了：

$ chose \lbrack host \lbrack i \rbrack \rbrack = \max ( \max ( chose \lbrack host \lbrack i \rbrack \rbrack + chose \lbrack i \rbrack , chose \lbrack host \lbrack i \rbrack \rbrack + unchose \lbrack i \rbrack ) , unchose \lbrack host \lbrack i \rbrack \rbrack + chose \lbrack i \rbrack ) $ 

$ unchose \lbrack host \lbrack i \rbrack \rbrack = unchose \lbrack host \lbrack i \rbrack \rbrack + unchose \lbrack i \rbrack $ 



------------


三、

$ \forall  protocol \lbrack i \rbrack = 2$

如果选择过了$ host \lbrack i \rbrack  $ 那么 $ i $ 就可以选择，

假如$ host \lbrack i \rbrack  $还没有被选择过，所以我们可以选择 $ host \lbrack i \rbrack  $ ， 同时是必要的放弃选择 $ i $ 的操作

所以应当这样转移 ： 

$ chose \lbrack host \lbrack i \rbrack  \rbrack  = \max ( chose \lbrack host \lbrack i \rbrack  \rbrack  + unchose \lbrack i \rbrack , unchose \lbrack host \lbrack i \rbrack  \rbrack  + chose \lbrack i \rbrack ) $
$ unchose \lbrack host \lbrack i \rbrack  \rbrack = unchose \lbrack host \lbrack i \rbrack  \rbrack +  unchose \lbrack i \rbrack  $

## pay attention to

明白什么是交互题的就当我没说

这是一道交互题，所以这道题目只需要提交一个函数就行了

题目相当于把你的函数 , $ ctrl C + ctrl V $ 一下，放到别的题目里面，所以没有输入（这很重要，输入$ 100%  $ 会 $ TLE $ ， 题目中要函数只返回结果，所以也没有输出。

注意函数的名称传参要一毛一样，不然会很莫名其妙的错误。


ps ： 我交了一页才明白的

# CODE （这个真可以提交AC）


```cpp
#include<bits/stdc++.h>
using namespace std;


int findSample(int n, int confidence[], int host[], int protocol[])
{
	int chose[100050],unchose[100050];
	memset(chose,0,sizeof(chose));
	memset(unchose,0,sizeof(unchose));
	for (int i = 0; i < n; ++i)
	{
		chose[i] = confidence[i];
	}
	for (int i = n-1; i >= 1; --i)
	{
		if (!protocol[i])
		{
			chose[host[i]] += unchose[i];
			unchose[host[i]] += (chose[i] > unchose[i] ? chose[i] : unchose[i]);
		}
		else if (protocol[i] == 1)
		{
			chose[host[i]] = max(max(chose[host[i]] + chose[i],chose[host[i]] + unchose[i]),unchose[host[i]] + chose[i]);
			unchose[host[i]] += unchose[i];
		}
		else 
		{
			chose[host[i]] = max(chose[host[i]] + unchose[i],unchose[host[i]] + chose[i]);
			unchose[host[i]] += unchose[i];
		}
	}
	int ans = (chose[0] > unchose[0] ? chose[0] : unchose[0]);
	return ans;
}

```



---

## 作者：TTpandaS (赞：1)

虽然图论题时光倒流很常见，但是这道题真的没想到。中间想过能不能倒着做，但是自己超小的脑容量瞬间将这个想法挤掉了。

考虑倒着删掉第 $i$ 个人，意味着此时第 $i$ 个人仅剩的连边即为加入网络时的连边。

如果连向主持人 $j$，那么反悔贪心，先直接选第 $i$ 个人，返回操作只会对 $j$ 有影响，将 $a_j$ 更新为 $\max(0,a_j-a_i)$。

如果连向主持人 $j$ 的朋友们，那么如果选择了 $j$ 就一定可以选择 $i$，将 $a_j$ 更新为 $a_i+a_j$。

如果全部连边，那么此时 $i$ 与 $j$ 没有区别，将 $a_j$ 更新为 $\max(a_i,a_j)$。

---

## 作者：快斗游鹿 (赞：1)

## 思路

考虑 dp。设 $f_{i,0/1}$ 表示第 $i$ 个点不选或选能取到的最大价值。发现题目中加边形式比较特别，先分类讨论一下：

对于第一种加边方式，显然第 $i$ 个人和主持人 $h_i$ 中最多选一个。所以转移方程为 $f_{i,0}+=\max(f_{h_i,0},f_{h_i,1}),f_{i,1}+=f_{h_i,0}$。

然后发现如果这么转移，第二种加边方式很难处理。因为 $h_i$ 的朋友与 $i$ 必然不能同时选，但现在我们只能处理 $i$ 和 $h_i$ 之间的关系。所以考虑反着处理，这样一对多的关系就可以转化为没有限制的多对一了。

那么重新考虑转移。第一种加边方式没什么差别，变为 $f_{h_i,0}+=\max(f_{i,0},f_{i,1}),f_{h_i,1}+=f_{i,0}$。

然后处理第二种。可以发现 $i$ 和 $h_i$ 其实没有关系，所以转移时要多考虑一点。如果不选 $h_i$，那么 $f_{h_i,0}+=f_{i,0}$，为什么不加 $f_{i,1}$ 呢？先来看下面的转移方程。

而如果选 $h_i$，则有 $f_{h_i,1}=\max(f_{h_i,0}+f_{i,1},f_{h_i,1}+f_{i,0},f_{h_i,1}+f_{i,1})$。你会发现，假如上面加上了 $f_{i,1}$，而这一步转移的 $h_i$ 又刚好是上一次转移的 $h_i$ 的朋友，在算 $f_{h_i,1}+f_{i,0}$ 这项时，就不满足条件了。还需要注意，应该先转移 $f_{h_i,1}$，不然会重复算。

第三种处理类似，这次 $i$ 和 $h_i$ 有了直接关系。所以直接得到 $f_{h_i,1}=\max(f_{h_i,1}+f_{i,0},f_{h_i,0}+f_{i,1}),f_{h_i,0}+=f_{i,0}$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int f[N][2];
int findSample(int n,int c[],int h[],int p[]){
	//n=read();
	for(int i=0;i<n;i++)f[i][1]=c[i];
	for(int i=n-1;i>=1;i--){
		//h[i]=read();p[i]=read();
		if(p[i]==0){
			f[h[i]][1]+=f[i][0];
			f[h[i]][0]+=max(f[i][0],f[i][1]);
		}
		else if(p[i]==1){
			f[h[i]][1]=max(f[h[i]][0]+f[i][1],f[h[i]][1]+max(f[i][0],f[i][1]));
			f[h[i]][0]+=f[i][0];
		}
		else{	
			f[h[i]][1]=max(f[h[i]][1]+f[i][0],f[h[i]][0]+f[i][1]);
			f[h[i]][0]+=f[i][0];
		}
	}
	return max(f[0][0],f[0][1]);
}
```


---

## 作者：Illusory_dimes (赞：1)

[不知道更好还是更坏的阅读体验](https://www.cnblogs.com/Illusory-dimes/p/15502399.html)

复盘 pb 讲的题，来写篇题解~~造福社会~~。

## Description

给定 $n$ 个点的点权 $w_i$ 和 $n - 1$ 条关系，第 $i$ 条关系如下：

1. 给定 $p$ ，让 $i$ 向 $p$ 连边；

2. 给定 $p$ ，让 $i$ 向 $p$ 的所有儿子连边；

3. 给定 $p$ ，让 $i$ 向 $p$ 和 $p$ 的所有儿子连边；

求建出来的图中所有独立集的最大点权和。

$n\ \leq 10 ^ 5,\ w_i\ \leq 10 ^ 6$

## Analysis

这种显然连的边数量是 $O(n ^ 2)$ 级别的，肯定不能直接莽。

但是为什么我的第一思路却是 DS 优化建图啊喂， 虽然看上去确实有点像 Legacy ，但一来这不是区间，二来 3 操作着实有点迷惑。

但是题目要我们求的是最大独立集，也就是说我们可能不需要建图重新跑一遍，可以考虑在给定的条件上做文章。

## Solution

那么，能够想到，设 $ans_{i, 0/1}$ 表示前 $i$ 个点，点 $i$ 选或不选的独立集最大点权和。

现在就要想怎么让后面的条件加进来以后不会影响到当前的条件的贡献。

但是会发现假如我们直接正着处理的话，对于一个点 $u$ 有多个父亲，父亲又没有直接连边，那贡献肯定不能边走边算了。

所以正着做是肯定是不行了，那么就会想要倒着做，加点改成删点。

感觉上其实还是有问题，假如一个点 $v$ 和一个点 $u$ 有个 2/3 操作，肯定是不能去把所有 $u$ 的儿子的答案都更新一遍。但是所有儿子都要去更新点 $u$ ，所以只要 $v$ 的贡献先更新到了 $u$ 身上就行了。

做法大概是确定了，画个图手膜一下， 3 种操作大概就是：

1. 因为 $p$ 和 $i$ 直接连边，所以要么 $p$ 选 $i$ 不选，要么 $p$ 不选 $i$ 选，要么 $p$ 不选 $i$ 不选

2. 注意 $p$ 和 $i$ 之间没有边，所以两个点选或不选都可以，但是要注意 $p$ 不选，$i$ 选的情况是归类到 $p$ 选的贡献里面，因为 $p$ 的儿子是和 $i$ 连了边的，本质上 $p$ 和 $i$ 是一个道理。

3. 比操作 2 多练了一条边，所以只是和操作 1 的方案一样，但是同时和操作 2 一样要注意贡献的归类

然后这么做下来，发现好像没有什么后效性，也没有什么其他要处理的，那就是做完了呀！！！

## Code

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int ans[N][2];

int findSample(int n, int w[], int hos[], int pro[]) {
	for (int i = 0; i < n; ++i) {
		ans[i][1] = w[i];
	}
	for (int i = n - 1; i >= 1; --i) {
		int ans1 = ans[hos[i]][1] + ans[i][1];
		int ans2 = ans[hos[i]][1] + ans[i][0];
		int ans3 = ans[hos[i]][0] + ans[i][1];
		int ans4 = ans[hos[i]][0] + ans[i][0];
		if (pro[i] == 0) {
			ans[hos[i]][1] = ans2;
			ans[hos[i]][0] = max(ans3, ans4);
		}
		else if (pro[i] == 1) {
			ans[hos[i]][1] = max(max(ans1, ans2), ans3);
			ans[hos[i]][0] = ans4;
		}
		else {
			ans[hos[i]][1] = max(ans2, ans3);
			ans[hos[i]][0] = ans4;
		}
	}
	return max(ans[0][0], ans[0][1]);
}
```

---

## 作者：Tx_Lcy (赞：1)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16799506.html)

[题目传送门](https://www.luogu.com.cn/problem/P5875)

似乎是我的第一篇 $\verb!IOI!$ 题解？

## 思路
虽然说是 $\verb!IOI!$ 题，但是其实并没有那么难。

这个题目描述比较杂乱，简单的描述就是：给你一些关系，你需要选出一些点，使这些点的权值和最大，并且这些点之间两两都没有关系。

似乎像是一个 $\verb!DP!$，所以我们不妨设出状态：$f_{i,0/1}$ 表示第 $i$ 个点，选/不选的最大权值和。

设 $w_i$ 表示第 $i$ 个点的权值，$x$ 表示当前的主持人。

我们来一种一种操作分析：

+ $\verb!IAmYourFriend!$：就是一个简单的没有上司的舞会，$f_{x,0}=w_x+f_{i,1},f_{x,1}=\max(f_{i,0},f_{i,1})$。
+ $\verb!MyFriendsAreYourFriends!$：意为 $i$ 是 $x$ 所有朋友的朋友，那么既然选了 $i$，那么 $x$ 的朋友必须不选，那么 $x$ 显然可以选，所以 $f_{x,0}=\max(w_x+f_{i,0},w_x+f_{i,1},f_{x,1}+f_{i,0},f_{x,1}+f_{i,1}),f_{x,1}+=f_{i,1}$。
+ $\verb!WeAreYourFriends!$：相当于第一种情况和第二种情况拼起来，不再赘述。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e6+10;
int f[N][2],co[N],ho[N],pr[N];
int findSample(int n,int confidence[],int host[],int co[]){
    for (int i=0;i<n;++i) f[i][0]=confidence[i];
    for (int i=n-1;i;--i){
        int x=host[i];
        if (co[i]==0)
            f[x][0]+=f[i][1],f[x][1]+=max(f[i][0],f[i][1]);
        else if (co[i]==1)
            f[x][0]+=max(f[i][0],f[i][1]),f[x][0]=max(f[x][0],f[x][1]+max(f[i][1],f[i][0])),f[x][1]+=f[i][1];
        else if (co[i]==2)f[x][0]+=f[i][1],f[x][0]=max(f[x][0],f[x][1]+f[i][0]),f[x][1]+=f[i][1];
    }
    int ans=0;
    for (int i=0;i<n;++i) ans=max(ans,f[i][0]),ans=max(ans,f[i][1]);
    return ans;
}
```


---

## 作者：lyhqwq (赞：0)

# Solution
绝世好题。

正难则反，考虑倒着做把加边变为删边。

令 $f_{i,0/1}$ 表示选（不选） $i$ 的答案，删除的点的答案已经确定，所以可以转移。

我们分类讨论三种加边方式，不妨令 $x=h_i$，$y=i$

对于第一种方式，显然就是一个没有上司的舞会。

$f_{x,0} \gets f_{y,0}$

$f_{x,1}\gets \max(f_{y,0},f{y,1})$

对于第二种方式，虽然 $x$ 与 $y$ 没有关系，但当 $x$ 向他的朋友转移时还需要考虑 $y$ 的贡献，所以 $f_{x,0}$ 应该是 $x$ 和 $y$ 至少选一个的答案。

$f_{x,0} \gets \max(f_{x,0}+\max(f_{y,0},f_{y,1}),f_{x,1}+f_{y,0})$

$f_{x,1} \gets f_{y,1}$

第三种方式则是在第二种方式的基础上加了 $x$ 和 $y$ 不能同时选的限制。

$f_{x,0} \gets \max(f_{x,0}+f_{y,1},f_{x,1}+f_{y,0})$

$f_{x,1} \gets f_{y,1}$

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int f[N][2];
int findSample(int n,int w[],int h[],int a[]){
	for(int i=0;i<=n-1;i++) f[i][0]=w[i];
	for(int i=n-1;i;i--){
		int x=h[i],y=i;
		if(a[i]==0) f[x][0]+=f[y][1],f[x][1]+=max(f[y][0],f[y][1]);
		if(a[i]==1) f[x][0]=max(f[x][0]+max(f[y][0],f[y][1]),f[x][1]+f[y][0]),f[x][1]+=f[y][1];
		if(a[i]==2) f[x][0]=max(f[x][0]+f[y][1],f[x][1]+f[y][0]),f[x][1]+=f[y][1];
	}
	return max(f[0][0],f[0][1]);
}
```

---

