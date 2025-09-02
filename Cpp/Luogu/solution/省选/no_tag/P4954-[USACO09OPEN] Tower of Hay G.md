# [USACO09OPEN] Tower of Hay G

## 题目描述

为了调整电灯亮度，贝西要用干草包堆出一座塔，然后爬到牛棚顶去把灯泡换掉。干草包会从传送带上运来，共会出现 $n$ 包干草，第 $i$ 包干草的宽度是 $W_i$，高度和长度统一为 $1$。干草塔要从底层开始铺建。贝西会选择最先送来的若干包干草，堆在地上作为第一层，然后再把紧接着送来的几包干草包放在第二层， 再铺建第三层……重复这个过程，一直到所有的干草全部用完。每层的干草包必须紧靠在一起，不出现缝隙，而且为了建筑稳定，上层干草的宽度不能超过下层的宽度。 按顺序运来的干草包一定要都用上，不能将其中几个干草包弃置不用。贝西的目标是建一座最高的塔，请你来帮助她完成这个任务吧。

## 说明/提示

### 样例解释

将 $1$ 和 $2$ 放在第一层，将 $3$ 放在第二层。

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
2```

# 题解

## 作者：emptysetvvvv (赞：43)

## 单调队列 动态规划

### 背景

小萌新 $\varnothing$ 初遇此题是在模拟赛上，私以为数据很水，果断贪心.......

### 思路

- 贪心的错误性

相信很多人看到此题会想到贪心：**让高层尽可能的小**，从后往前倒叙贪心。

方面起见，我们倒叙读入，从前向后贪心使每段尽可能的小。

那么可以枚举 第一层由 $a[1]\sim a[i]$ 构成，设从前往后到了 $a[i]$，当前层的宽度为 $w$，那么就从 $i$ 再往前后连续一段，使得这一段的长度恰好大于 $w$。

对 $a[i]$ 求前缀和 $s[i]$，也就有了以下的代码：

```cpp
for(int i = 1; i <= n and s[i]*ans <= s[n]; ++i) {
	int w = s[i], cur = i, pre, cnt = 1;
	while(s[cur] + w <= s[n]) { 
		pre = cur; 
		cur = lower_bound(s+cur+1, s+n+1, s[cur]+w) - s;
		w = s[cur] - s[pre];
		++cnt;
	} 
	ans = max(ans, cnt);
}
```

对于随机数据还是表现很不错的，但随手卡一下就会挂掉。

>举个例子：

```
6
9 8 2 1 5 5 
```

>倒叙之后是 $5\ 5\ 1\ 2\ 8\ 9$，贪心划分结果为 $5\ |\ 5\ |\ 1\ 2\ 8\ 9$ 共三层，然而正确答案是 $5\ |\ 5\ 1\ 2\ |\ 8\ |\ 9$ 共四层。

可以看出，贪心错误之处在于 前面的贪心使得 底层过大，难以扩展。

我们大胆猜测，有一个较为贪心的结论：

**构成最优解的若干种方案中，一定有一种满足底层最小**，即 **底层最小的方案 一定可以 构造出最高的层数**。

>此结论由 ZKW 大神严谨证明。

- 考虑动态规划

一样，我们先把 $a$ 数组翻转过来，前缀和为 $s[i]$。

$f[i]$ 表示 考虑到位置 $i$ 时，$a[1]\sim a[i]$ 最高能搭多少层，$g[i]$ 表示此时最后一层（即 $a[i]$ 所在层）的最小宽度。

转移方程：

$$f[i]=f[j]+1(\text{ $j$ 为满足 } j\in[0,i-1]\text{ 且 } g[j]\leqslant s[i]-s[j] \text{的最后一个 }j)$$

要求最后一个 $j$ 是由于我们想要此时最后一层的宽度尽可能的小，得到 $j$ 后有 $g[i]=s[i]-s[j]$，

边界条件 $f[0]=0$。

转移复杂度 $O(n)$，总复杂度 $O(n^2)$。


- 考虑单调队列优化

转移条件为 $g[j]\leqslant s[i]-s[j]$，即 $g[j]+s[j]\leqslant s[i]$，那么就会有一个显然的结论：

若有 $k<j$ 且 $g[k]+s[k]\geqslant g[j]+s[j]$，则 $k$ 永远不可能再转移别人了，因为如果 $k$ 满足转移条件，那么 $j$ 也会满足，而 $j$ 的位置还更加靠后。

因此，我们可以维护一个 $g+s$ 值单调递增的 单调队列。

每次转移时从 单调队列中找到 最后一个 $g[j]+s[j]\leqslant s[i]$ 的位置 $j$，单调队列中 $j$ 以左的元素从队首出队。

转以后从队尾弹出 $g[j]+s[j]\geqslant g[i]+s[i]$ 的元素，然后将位置 $i$ 加入单调队列。

每个元素进出队列各一次，复杂度 $O(n)$。

### 代码

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 100005;
int n, a[maxn], s[maxn], f[maxn], g[maxn];
int q[maxn], l, r;
int main() {
	scanf("%d", &n);
	for(int i = n; i; --i) scanf("%d", a+i);
	for(int i = 1; i <= n; ++i) s[i] = s[i-1] + a[i];
	for(int i = 1; i <= n; ++i) {
		while(l < r and s[q[l+1]]+g[q[l+1]] <= s[i]) ++l;
		f[i] = f[q[l]] + 1;
		g[i] = s[i] - s[q[l]];
		while(l < r and s[q[r]]+g[q[r]] >= s[i]+g[i]) --r;
		q[++r] = i;
	}
	printf("%d\n", f[n]);
	return 0;
}
```

---

## 作者：祝硕鹏 (赞：23)

# 我们知道啊，这道题不是水；
*Bessie必须建一座干草堆。一共有N大包的干草（1<=N<=100000）(从1到N编号)依靠传送带连续的传输进牛棚来。
第i包干草有一个 宽度W_i(1<=w_i<=10000)，高度为1。 Bessie必须利用所有N包干草来建立起干草堆，按顺序严格摆放。
说得更清楚一些：一旦她将一个草包放在第二级 ，她不能将接下来的草包放在地基上。要求每一级不能比下面的一级宽。
求最大高度。*
###  动归比较坑的一点是
##   看上去是贪心
先要了解一个结论，在多种可行的堆叠方案中，至少有一种能使层数最高的方案同时使得底边最短。即底边最短的，层数一定最高。证明：（引用张昆玮大牛，虽然我不知道是谁）
 任意取出一个能使层数最高的方案，设有CA层，把其中从下往上每一层最大的块编号记为Ai；任取一个能使底边最短的方案，设有CB层，把其中从下往上每一层最大的块编号记为Bi。
 显然A1>=B1,ACB<=BCB，这说明至少存在一个k∈(1,CB)，满足Ak-1≥Bk-1且Ak≤Bk。
 也就是说，方案 A 第K 层完全被方案 B 第K 层包含。
 构造一个新方案，第K 层往上按方案 A，往下按方案 B，
 两边都不要的块放中间当第K 层。 新方案的层数与 A 相同，而底边长度与 B 相同。证毕。
 知道这个结论后，贪心就明显不可行了。比如a + b> c+ d,b + c < d,贪心的结果是a,b,c||d,而a,b||c,d则更优。
 设F[i]为第i..N个干草包所叠成的塔底层最短边的值,同时用g[i]记下此时的层数。
 F[i]=min(sum[j-1]-sum[i-1]) (j>i 且 sum[j-1]-sum[i-1]>=F[j]) 
 像这样O(n^2)的算法明显过不了，要进行优化。
 我们发现在阶段i时，对于k>j>i，j会比k优，决策为k的情况只能是J不满足条件而k满足条件，整理方程得
      f[j] - sum[j - 1] > f[k]-sum[k - 1]
 所以我们可以用一个单调队列来维护。均摊时间为o(n)。
 #### ~~本蒟蒻第一次写题解，插入代码还不怎么会用，请见谅~~
```cpp

#include<cstring>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
int n,a[100002],sum[100002],q[100002];
int wide[100002],h[100002];
void dp()
{
	int t=0,w=0; q[t]=n+1;
	for(int i=n;i>=1;i--)
	   {while(t<w&&wide[q[t+1]]<=sum[q[t+1]-1]-sum[i-1]) t++;//如果该层塔下一层的宽度<=到i为止可得的宽度，则表明可新建一层 
	    wide[i]=sum[q[t]-1]-sum[i-1];//i所在那层的宽度 
	    h[i]=h[q[t]]+1;
	    while(t<w&&wide[i]-sum[i-1]<wide[q[w]]-sum[q[w]-1]) w--;
	    q[++w]=i;
	   }
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	   {cin>>a[i];
	    sum[i]=sum[i-1]+a[i]; //前缀和 
	   }
	dp();
	printf("%d",h[1]);
	return 0;
}
```

---

## 作者：installb (赞：15)

updated Nov.29.2019  

CSPS2019D2T2打卡(不过那道题比这道复杂多了 只是撞思路了?)  
思路很妙的一道题  

是道贪心 好像没人写证明 给个简单的证明吧  

给出贪心结论 **存在使得第一层最小的合法划分方式 使得层数最多**(即得到最优解)  
即一定能构造出一种最优解是满足这个解是第一段最小的  

画个图:  
假定方案2比方案1多分一段且两种方案均合法 并且方案2的第一段更长  
我们假设方案2就是段数最多的一种方案  
则一定能构造出一种分段数和2一样多的方案使得第一段和方案1一样大  
![](https://cdn.luogu.com.cn/upload/image_hosting/q9xj71y4.png)
根据抽屉原理 黄圈中的部分一定会存在 即一定能构造出方案3 使得方案3合法 分段数与方案2相同 且第一段长度与方案1相等  

只要存在分段数为小于最优解的分段方案 我们在确定第一段不变的情况下一定能够构造出分段数等于最优解的分段方案  

**具体实现**  

首先第一段要尽量小 这里我们先枚举第一段$[1,i]$的右端点$i$ 由于所有数都是正数 所以$i$一定是越小越好的 这样才能使得第一段更小  

此外 当$i$过小的时候 由于第二段、第三段...都是需要小于等于第一段的 可能会导致后面的段分不出来 所以我们需要**寻找符合要求的最小的$i$**  

这个很难判断 但是当我们枚举$i$的时候 可以假装第一段已经确定 然后计算出$[i+1,n]$所有划分方案中第一段(从i+1开始的段)最小的方案 的 第一段的值  
由于**存在使得第一层最小的合法划分方式 使得层数最多** 所以这在层数上也一定可以是最优解之一 并且对前面的限制更小  

这样我们把问题转化为了子问题 即求出**对于所有$i$ 将$[i,n]$分段第一段最小值**  
后面就好办了 直接用一个看起来像DP的枚举就可以了  
注意j越小越好 所以找到第一个符合要求的j就直接 确定答案+break  

这里$d_i$记录了每一段分段的大小  
```cpp
for(int i = 1;i <= n;i ++) cin >> a[i];
for(int i = n;i >= 1;i --) s[i] = s[i + 1] + a[i];
for(int i = n;i >= 1;i --){
	for(int j = i;j <= n;j ++){
		if(s[i] - s[j + 1] < d[j + 1]) continue; // 不能划分
		d[i] = s[i] - s[j + 1]; dp[i] = dp[j + 1] + 1;
		break;
	}
}
cout << dp[1] << endl;
```

这样是平方算法 我们需要快速确定j 减少无用的枚举  

由于$s_i$和$d_j$是单调的 故$s_i+d_i$是单调的 满分算法需要要用单调队列优化  
```cpp
for(int i = 1;i <= n;i ++) cin >> a[i];
for(int i = n;i >= 1;i --) s[i] = s[i + 1] + a[i];
q[++ t] = 0;
for(int i = n;i >= 1;i --){
	while(h < t && s[q[h + 1]] + d[q[h + 1]] <= s[i]) h ++;
	d[i] = s[i] - s[q[h]]; dp[i] = dp[q[h]] + 1;
	while(h <= t && s[i] + d[i] <= s[q[t]] + d[q[t]]) t --;
	q[++ t] = i;
}
```

---

## 作者：Otomachi_Una_ (赞：7)

本题使用 dp。

下面对物块的放置为倒序的，也就是说我们先搭顶塔，再往下搭。

很容易发现，在同一高度时，底座宽度越小对接下来的搭建越有利。在使用同样多的物品时，塔的高度越高，底座宽度就越小。

于是可以假设 $f_i$ 表示从物块 $i$ 到 $n$ 的最大高度，$g_i$ 表示高度为 $f_i$ 时底座最小宽度。

状态转移方程：

$$f_i=f_{k+1}+1$$

$$g_i=s_i-s_{k+1}$$

其中 $k$ 表示从物块 $i$ 到 $n$ 中最小的物块 $k$，使得 $g_{k+1}\leq s_i-s_{k+1}$，$s_i$ 表示后缀和。

于是得到以下代码：

```cpp
#include<iostream>
using namespace std;
const int MAXN=1e5+5;
int n;
int a[MAXN];
int f[MAXN];//f[i]: i~n 最大高度  
int g[MAXN];//g[i]: i~n 时最小底座
int s[MAXN]; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=n;i>=1;i--)
		s[i]=s[i+1]+a[i];
	for(int i=n;i>=1;i--){
		for(int j=i;j<=n;j++)
			if(s[i]-s[j+1]>=g[j+1]){
				f[i]=f[j+1]+1;
				g[i]=s[i]-s[j+1];
				break;
			}
	}
	cout<<f[1];
	return 0;
}
```

时间复杂度 $\mathcal{O}(n^2)$，这能 AC 说明数据过水，对于一些极端数据还是会超时的。

下面我们讲讲优化。

很明显发现我们大量的时间都浪费在枚举 $k$ 上。实际上，根据上面的式子：

$$g_{k+1}+s_{k+1}\leq s_i$$

可以把 $g_{k+1}+s_{k+1}$ 视为整体，这就变成里一个简单的单调栈问题。

时间复杂度 $\mathcal{O}(n)$ 这里就不放代码了。

---

## 作者：__gcd (赞：5)

由于堆干草堆的顺序固定，也就是说**无后效性**，考虑DP。

影响答案的因素有：当前堆到第几个干草堆，当前层的宽度。很容易定义状态 $dp(i,j)$ 为当前层的末尾为第 $i$ 个干草堆，宽度为 $j$ 的最大高度。

由于宽度的限制，我们从前往后（也就是从上到下）枚举的话，会给宽度一个上界（上界即为上一层的宽度），这个上界意味着可能有**堆不完**的情况。解决这个问题的方法是：反着堆。从上往下堆，这样宽度只会有一个下界，而下界是可以通过一直堆来解决的，所以不会出现堆不完的情况。

考虑完DP的顺序之后，我们发现定义的状态会超空间，所以要想办法化二维为一维。**显然在使用同等数量的干草堆的情况下，宽度越小越好**（使下一层使用干草堆尽可能少），所以我们把第二维去掉，保留最小的宽度即可。定义 $dp(i)$ 为当前层的末尾为第 $i$ 个干草堆，相对应地，$w(i)$ 为最小的宽度。假设 $j$ 是最优的决策点，可以得到转移方程：

$\begin{cases}w(i)=sum(i)-sum(j)\\dp(i)=dp(j)+1\end{cases}$

需要满足的条件是：

$sum(i)-sum(j)\geq w(j)$

当前时间复杂度为 $O(n^2)$，不能通过此题。所以我们要寻找相应的性质。

结论：$dp(i)$ 不下降。

证明：对于每个 $i$，可以构造出如下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/67kqgh3x.png)

此时 $dp(i)=dp(i-1)$，并且有可能出现更优的情况。证毕。

于是我们只需要找到满足 $sum(i)-sum(j)\geq w(j)$ 的最大的 $j$ 即可。

把上面这个式子变形得到：

$sum(i)\geq sum(j)+w(j)$

这个条件相当于给了 $sum(j)+w(j)$ 一个上界 $sum(i)$。并且随着 $i$ 的增加，$sum(i)$ 也增加，等同于 $sum(j)+w(j)$ 的上界增加，满足**单调性**，也就是 $j$ 可行，那么在以后就都可行。

考虑使用单调队列优化。维护一个 $sum(j)+w(j)$ 值递增，下标递增的单调队列。每次询问查找最大满足条件的 $j$，进行转移即可。

由于每个元素最多进队一次，出队一次，所以时间复杂度为 $O(n)$，可以通过本题。

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
inline int read()
{
	int x = 0; bool op = false;
	char c = getchar();
	while(!isdigit(c))op |= (c == '-'), c = getchar();
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return op ? -x : x;
}

const int N = 100010;
int n;
int a[N], w[N], sum[N], dp[N];
deque<int> q;

int calc(int x)
{
	return w[x] + sum[x];
}

int main()
{
	n = read();
	for(int i = n; i >= 1; i--)
		a[i] = read();
	for(int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i];
	int pos = 0; //这里一定要放外面，因为上一次的可行解可能被弹出了
	for(int i = 1; i <= n; i++)
	{
		while(q.empty() == false && sum[i] >= calc(q.front()))
		{
			pos = q.front();
			q.pop_front();
		}
		w[i] = sum[i] - sum[pos];
		dp[i] = dp[pos] + 1;
		while(q.empty() == false && calc(i) <= calc(q.back()))
			q.pop_back();
		q.push_back(i);
	}	
	printf("%d", dp[n]); 
	return 0;
} 
```


---

## 作者：colemak (赞：4)

## 这题数据是真的水。。。

暴力n^2可以AC，总时间只比单调队列慢22ms，[评测记录](https://www.luogu.org/recordnew/show/17464785)。

把整个序列翻转过来，题目就是求将序列变成单调不下降的，f[i]表示分到第i个位置时最多可以建多少层,g[i]保存当前层的宽度，首先f[i]一定是单调不降的，并且贪心一点的想法是当前位置向前找转移的第一个可行位置最优，因为这样当前层的宽度是尽可能小的，下一层所需要的代价就不会更劣，所以每次暴力从i-1向前跳，遇到第一个位置就转移break出循环。

代码如下
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#define FOR(i,a,b) for(register int i(a);i<=b;++i)
#define ROF(i,a,b) for(register int i(a);i>=b;--i)
using namespace std;
const int N(1000010);
int n;
int f[N],g[N],sum[N];
int main()
{
	cin>>n;ROF(i,n,1)cin>>sum[i];
	FOR(i,1,n)sum[i]+=sum[i-1];
	FOR(i,1,n)
	{
		ROF(j,i-1,0)
		if(sum[i]-sum[j]>=g[j])
		{
			f[i]=f[j]+1;
			g[i]=sum[i]-sum[j];
			break;
		}
	}
	cout<<f[n]<<'\n';
	return 0;
}
```


---

## 作者：BF_AlphaShoot (赞：2)

~~讲课时的例题，A了之后写下这篇题解。~~

首先有一个性质，**最下层最窄的方案一定也是一个最高的方案。**这是本题最重要的性质。

不妨先给出这个自造数据：

```
4
4 2 1 4
```

第 2、3 个干草堆的高度低于第 4 个，又由于必须用到全部干草堆，所以相当于第 4 个“强制拆掉”了第 2、3 个并拆成 1 层。

所以**正向转移时是没有单调性**的，因此这道题必须**倒推**，因为最上层已经确定，后面的层高也不会变，所以倒推的答案是单调的。

首先可以倒序设计一个 $\Theta(n^2)$ 的 **DP**，即同时维护到第 $i$ 包干草 最下层宽度 $g_i$ 和高度 $f_i$ ，枚举上一层最后一个干草的位置即可 $\Theta(n)$ 转移，易得状态转移方程：

$$
g_i=\min(sum_{j-1}-sum_{i-1})\ (j>i,g_j\leqslant sum_{j-1}-sum_{i-1})
$$

$$
f_i=f_j+1
$$

显然的，需要优化才能通过此题数据。~~不过由于本题数据过水，此方法可直接 AC。~~

想到**单调队列优化DP**的方式，是把所有在未来都不可能比这个决策优的最优决策的方案都删掉，那么**队列中维护的是位置越来越靠后，决策越来越劣的方案**。而我们又想到，**位置越靠后，对于未来决策的合法性越高**。

或许放一张图可以更好解释这一问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/qx95qi82.png)

其中，括号为数列上所选区间，标有”max”的为数列最大值（亦为区间起始点左边界），圆圈为所选点。现区间向右侧移动，而最左侧的选点（即图中标有箭头的点）虽然距离最大值距离最远，但在未来能被区间选中的几率更大。

我们不妨把上面所写状态转移方程进行移项，可得：

$$
sum_{i-1}\leqslant sum_{j-1}-g_j
$$

$g$ 的增大在将来可能更优；从转移来看，$sum_{i-1}$ 越小越好，即 $i$ 越小越好。
所以应该维护一个 $sum_{j-1}-g_j$ 单调递增，$j$ 单调递增的队列。

所以这其实是一个**变形的单调队列优化DP**，由于决策越靠后越优，所以队头并不一定是最优解，只要接下来的满足条件，就不停弹队头。

再将状态转移方程与队列进行结合，具体请看代码。

View Code：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ri register int
#define il inline

const int N=1e5+10;
int n,a=0,b=1;
int w[N],sum[N];
int q[N],g[N];
int f[N];

il ll read(){
    ll x=0,y=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}

signed main(){
    memset(q,0,sizeof(q));
    n=read();
    for(ri i=1;i<=n;i++)
        w[i]=read();
    for(ri i=n;i>=1;i--)
        sum[i]=sum[i+1]+w[i];
    for(ri i=n;i>=1;i--){
        while(a<b&&sum[q[a+1]]+g[q[a+1]]<=sum[i])
            a++;
        g[i]=sum[i]-sum[q[a]];
        f[i]=f[q[a]]+1;
        while(a<=b&&sum[i]+g[i]<=sum[q[b]]+g[q[b]])
            b--;
        q[++b]=i;
    }
    printf("%d",f[1]);
    return 0;
}
```

如果有任何代码和讲解的问题，欢迎在评论处留言。

---

## 作者：ListenSnow (赞：2)

## 题意

给定n个数字，将它们分成**连续**的若干个区间。满足后一个区间中的数字之和一定**不大于**前一个区间中的数字之和。求最多可以分成多少个区间。

## 思路

~~显然~~，本题可以用动态规划进行求解。

定义 $f[i]$表示最后一个区间的右端点为第 $i$ 个数的时候所能分成的最大区间数。 

但是只靠 $f[i]$数组无法满足题目中的限制条件。于是需要定义 $g[i]$ 表示在最优的状态下最后一个区间内的数字和。同时定义一个 $s[i]$ 表示前 $i$ 个数字之和。（这两个数组的具体用法下面状态转移方程会提到）  

有一个很~~显然~~的贪心性质，每一个区间的数字之和越小越好。

但是如果直接正向枚举。会发现一个很奇怪的问题。由于需要满足上面的贪心性质，所以第一个区间就会特别小，而区间数字之和又要满足非严格单调**递减**，于是就可能会出现即使一个数字单独成为一个区间还是不合法的尴尬局面。于是可以考虑**倒序**枚举，就可以避免下一个区间放不下一个数字的局面。

于是就可以列出状态转移方程：

设 $0 \leq j \leq i$ ，若满足 $g[j] \leq s[i] - s[j]$ ，那么就有

$f[i]= max(f[j]+1)$ 。

这个转移方程还是比较好理解的。但是 $O(n^2)$ 的时间复杂度显然无法直接通过本题。于是需要用到单调队列优化转移方程。


观察之前的状态转移方程的条件 $g[j] \leq s[i] - s[j]$ ，移项，得 $g[j]+s[j] \leq s[i]$。而不等式的左边为定值，于是就可以对不等式左边的值进行单调队列优化。

有一个很~~显然~~的性质，如果 $k \le j$ 且 $s[k]+g[k] \geq s[j]+g[j]$ 。那么 $k$ 就一定无法成为最优状态。因为对于 $i$ 来说。$i$ 所在的这一个区间内的数字之和一定要在满足不小于前一个区间的数字和的前提下越小越好。 如果 $k$ 比 $j$ 小，但是它所在的那一段区间长度反而比 $j$ 还要长。那么肯定将区间分成了更少的部分，显然违背了之前提到的贪心性质。所以就不可能成为最优解了。于是维护一个满足 $g[i]+s[i]$ 单调递增（也就是队头为区间最小值）的队列。（队尾出队判断）

同时，由于本题没有对区间长度进行限制，那么根据贪心性质，肯定是在满足 $g[j]+s[j] \leq s[i]$ 的前提下 $j$ 越靠近右边越好。（队头出队判断）

于是就可以做到 $O(n)$ 时间内通过本题。

## code：

```cpp
#include<iostream>
#include<cstdio>
#include<deque>
using namespace std;
const int M=1e6+10;
deque<int> q;
int n,w[M],sum[M],f[M],g[M];
int calc(int k)
{
    return sum[k]+g[k];
}
int main()
{
	scanf("%d",&n);
	for(int i=n;i>=1;i--) scanf("%d",&w[i]);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+w[i];
	int last=0;
	for(int i=1;i<=n;i++)
	{
		while(q.size()&&sum[i]>=g[q.front()]+sum[q.front()]) 
		{
			last=q.front();//由于本人比较懒，不想写模拟双向队列判断出队。所以需要一个last来记录最后一个满足s[i]+g[i]<=s[i] 的下标 
			q.pop_front();
		}
		g[i]=sum[i]-sum[last];
		f[i]=f[last]+1;
		while(q.size()&&calc(q.back())>calc(i)) q.pop_back();
		q.push_back(i);
	}
	printf("%d\n",f[n]);
	return 0;
}
```


---

## 作者：401rk8 (赞：2)

[My blog](https://www.luogu.com.cn/blog/Rings/#)

---

正着做不容易确定当前层放几个（多了层数可能少，少了以后可能摞不上去），于是倒着做，这样在层数相同时当前层放的越少越好。预处理 $w$ 的后缀和 $s$，设 $f[i]$ 为 $i$ 到 $n$ 的草堆最多能摞的层数， $g[i]$ 为 $f[i]$ 的最小宽度，转移：$f[i]=\max(f[i],f[j]+1)(s[i]-s[j]\ge g[j])$。时间复杂度 $O(n^2)$
```cpp
for(int i = n; i; --i)
	for(int j = i+1; j <= n+1; ++j)
	if( s[i]-s[j] >= g[j] ) {
		if( f[j]+1 > f[i] ) f[i] = f[j]+1, g[i] = s[i]-h[j];
		else if( g[i] > s[i]-s[j] ) g[i] = s[i]-s[j];
	}
```
但 $n\le 10^5$，考虑优化。本题有如下性质：
- $s$ 单增（从后往前看，下同）
- $f$ 不降（把 $i$ 摞在 $f[i+1]$ 层，这样合法且 $f[i]=f[i+1]$）
- 转移条件可以改写为 $w[i]\ge w[j]+g[j]$ 
于是考虑单调队列优化。具体来说，维护一个 $w[i]+g[i]$ 单增，$i$ 单减的单调队列。时间复杂度均摊 $O(n)$
```cpp
long long val(int i) { return s[i]+g[i]; }
	for(int i = n, j = n+1; i; --i) {
    // j要定义成全局的，因为上次的决策可能出队
		while( fro <= rea && s[i] >= val(que[fro]) )
		/*
			这里并非普通的单调队列
		    而是利用 f[i] 不降将用过的决策记录并出队
		*/
			j = que[fro++];
		f[i] = f[j]+1, g[i] = h[i]-h[j];
		while( fro <= rea && val(i) <= val(que[rea]) ) --rea;
        // i<que[rea] <=> f[i]>=f[que[rea]]，且 val(i) 更小，i 更容易成为决策点的，que[rea]就无用了
		que[++rea] = i;
	}
```

---

## 作者：zhengrunzhe (赞：2)

我懒得写单调队列，就写了个数据结构优化

序列倒过来，$sum[i]$表示新序列的前缀和

$g[i]$表示$i$的最优决策$j$的宽度，即$g[i]=sum[i]-sum[j]$

$f[i]=\max\left\{f[j] \right \}+1,j<i,sum[i]-sum[j]\geq g[j]$

移项，$sum[j]+g[j]\leq sum[i]$

这是个简单偏序，开个数据结构维护，$sum[]+g[]$为关键字，$f[]$为权值求最大值

可以用线段树，树状数组，当然，由于只需要$\leq$，也就是一个前缀最大值，树状数组就可以了常数最小

然而我懒得写离散化，考虑平衡树，我就写了个FhqTreap

$for$一遍$i \ 1 \rightarrow n$，对于每个$i$，现在平衡树中查$\leq sum[i]$的最大值，并且同时能够获取这个最大值所在的下标，比如这个下标记作$j$，然后我们需要把$sum[i]+g[i]$塞到平衡树里，也就是插入$sum[i]+sum[i]-sum[j]$=$2sum[i]-sum[j]$

```cpp
#include<cstdio>
#include<cstdlib>
template<class type>inline const type max(const type &a,const type &b){return a>b?a:b;}
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
const int N(1e5+5);
namespace Fhq_Treap
{
	struct data
	{
		int val,id;
		inline data():val(0),id(0){}
		inline data(const int &val,const int &id):val(val),id(id){}
		inline const bool operator>(const data &d)const
		{
			return val^d.val?val>d.val:id>d.id;
		}
	};
	struct tree
	{
		data val,mx;
		int key,priority;
		tree *lson,*rson;
		static tree *null;
		void *operator new(size_t size);
		inline tree(const int &key=0,const int &val=0,const int &id=0):key(key),priority(rand()),val(data(val,id)),mx(data(val,id)),lson(null),rson(null){}
		inline const void pushup()
		{
			mx=max(val,max(lson->mx,rson->mx));
		}
	}*tree::null,*root;
	#define null tree::null
	char memory_pool[N*sizeof(tree)],*tail(memory_pool+sizeof memory_pool);
	inline void *tree::operator new(size_t size){return tail-=size;}
	inline const void init()
	{
		root=null=new tree;
	}
	inline const void split(tree *&a,tree *&b,tree *p,const int &k)
	{
		if (p==null)return a=b=null,void();
		if (k<p->key)b=p,split(a,b->lson,p->lson,k),b->pushup();
		else a=p,split(a->rson,b,p->rson,k),a->pushup();
	}
	inline tree *merge(tree *a,tree *b)
	{
		if (a==null&&b==null)return null;
		if (a==null)return b;
		if (b==null)return a;
		if (a->priority<b->priority)return a->rson=merge(a->rson,b),a->pushup(),a;
		return b->lson=merge(a,b->lson),b->pushup(),b;
	}
	inline const void insert(const int &key,const int &val,const int &id)
	{
		tree *a,*b;
		split(a,b,root,key-1);
		root=merge(a,merge(new tree(key,val,id),b));
	}
	inline const data query(const int &k)
	{
		tree *a,*b;
		split(a,b,root,k);
		const data mx(a->mx);
		root=merge(a,b);
		return mx;
	}
}using namespace Fhq_Treap;
int sum[N],a[N],n,ans;
int main()
{
	read(n);init();
	for (int i(n);i;i--)read(a[i]);
	for (int i(1);i<=n;i++)sum[i]=sum[i-1]+a[i];
	for (int i(1);i<=n;i++)
	{
		const data t(query(sum[i]));
		ans=max(t.val+1,ans);
		insert(sum[i]+sum[i]-sum[t.id],t.val+1,i);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：ChrisK (赞：0)

单调队列优化DP

先吧数组倒序

这样就是求序列和逐渐上升。

那么设到以i结尾的时候这一段的值为 $g[i]$ ，高度为 $f[i]$

 $sum[]$ 是前缀和数组。

那么当 $sum[i]-sum[j]⩾g[j]$ 的时候 $f[i]=f[j]+1$。( $j$∈$[$0,i−1$]$  )

显然 j 越在后面越优。

这样j倒序暴力DP就可以了。

可以单调队列优化。

显然当 $k<j$ 而且 $g[k]+sum[k]⩾g[j]+sum[j]$ 时$k$是不优的

就可以弹tail了。

head就是找到最后一个符合的j就可以。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n;
int w[maxn],q[maxn],f[maxn],g[maxn],sum[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=n;i;i--)
		scanf("%d",&w[i]);
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+w[i];
	int l=1,r=0;
	for(int i=1;i<=n;i++){
		while(l<=r && g[q[l]]+sum[q[l]]<=sum[i]) l++;
		g[i]=sum[i]-sum[q[l-1]];
		f[i]=f[q[l-1]]+1;
		while(l<=r && g[q[r]]+sum[q[r]]>=g[i]+sum[i]) r--;
		q[++r]=i;
	}
	cout<<f[n]<<endl;
	return 0;
}

```


---

## 作者：⊱⋛赫宇⋚⊰ (赞：0)

[博客](https://blog.csdn.net/yhhy666/article/details/109266863)

[题目](https://www.luogu.com.cn/problem/P4954)

# 思路
## 贪心
相信很多人看到此题会想到贪心：让高层尽可能的小，从后往前倒叙贪心。
方面起见，我们倒叙读入，从前向后贪心使每段尽可能的小。
但是，对于每一层，我们可以有两种的方法，一个是向上，一个是巩固地基，所以不能用贪心来实现，但是我们还是得到了一个结论

底层最小的方案 一定可以 构造出最高的层数。

6
9 8 2 1 5 5

就会输出5/5/1288  而实际则是 5 /512 /8 /8

## 普通dp
所以我们就看可以先造一个dp来解决，因为题目说是要按照从下面到上面要递减，我们这样是没办法进行dp转移的，那我们不妨把它给倒过来，然后写用前缀和求出大小。并且用两个数组来转移。一个是dp[i]表示到第i个草堆可以叠多少层，g[i]表示叠到最后一层的宽度

然后转移就是从第i堆草到第N堆，如果两个前缀和一减<=前面那一层，那么就可以转移
复杂的O(n^2)
```cpp
for(int i = 1;i <= n;i ++) cin >> a[i];
for(int i = n;i >= 1;i --) s[i] = s[i + 1] + a[i];//把数组倒过来
for(int i = n;i >= 1;i --){
	for(int j = i;j <= n;j ++){
		if(s[i] - s[j + 1] < d[j + 1]) continue; // 不能划分
		d[i] = s[i] - s[j + 1]; dp[i] = dp[j + 1] + 1;//上面那一层加一
		break;
	}
}
cout << dp[1] << endl;
```

## DP+单调队列
由于是s[i]和d[j]是单调的 故s[i]+d[j]
是单调的 满分算法需要要用单调队列优化
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 100005;
int n, a[maxn], s[maxn], f[maxn], g[maxn];
int q[maxn], l, r;
int main() {
	scanf("%d", &n);
	for(int i = n; i; --i) scanf("%d", a+i);
	for(int i = 1; i <= n; ++i) s[i] = s[i-1] + a[i];
	for(int i = 1; i <= n; ++i) {
		while(l < r and s[q[l+1]]+g[q[l+1]] <= s[i]) ++l;
		f[i] = f[q[l]] + 1;
		g[i] = s[i] - s[q[l]];
		while(l < r and s[q[r]]+g[q[r]] >= s[i]+g[i]) --r;
		q[++r] = i;
	}
	printf("%d\n", f[n]);
	return 0;
}

```


---

