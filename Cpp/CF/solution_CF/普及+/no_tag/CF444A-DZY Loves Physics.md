# DZY Loves Physics

## 题目描述

DZY loves Physics, and he enjoys calculating density.

Almost everything has density, even a graph. We define the density of a non-directed graph (nodes and edges of the graph have some values) as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/a425e0bd8ecdace80b53301f0ed617a22d06cb47.png) where $ v $ is the sum of the values of the nodes, $ e $ is the sum of the values of the edges.Once DZY got a graph $ G $ , now he wants to find a connected induced subgraph $ G' $ of the graph, such that the density of $ G' $ is as large as possible.

An induced subgraph $ G'(V',E') $ of a graph $ G(V,E) $ is a graph that satisfies:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/205d30887fed54bfaabe37b0daf749cd5804bf34.png);
- edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/7ea118e128a0519e2d5be64db2d60ebfb7343781.png) if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/ea6ddeec58cbe4a1da10914bab9d3a37e180ee3e.png), and edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/a10ab0808c4b5f03a82ae1ae0a40b33ad030284e.png);
- the value of an edge in $ G' $ is the same as the value of the corresponding edge in $ G $ , so as the value of a node.

Help DZY to find the induced subgraph with maximum density. Note that the induced subgraph you choose must be connected.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/3a3e9eb2a63d273e409ca45b73267a13b68b4d42.png)

## 说明/提示

In the first sample, you can only choose an empty subgraph, or the subgraph containing only node $ 1 $ .

In the second sample, choosing the whole graph is optimal.

## 样例 #1

### 输入

```
1 0
1
```

### 输出

```
0.000000000000000
```

## 样例 #2

### 输入

```
2 1
1 2
1 2 1
```

### 输出

```
3.000000000000000
```

## 样例 #3

### 输入

```
5 6
13 56 73 98 17
1 2 56
1 3 29
1 4 42
2 3 95
2 4 88
3 4 63
```

### 输出

```
2.965517241379311
```

# 题解

## 作者：一铭君一 (赞：8)

看到题解里大部分人都说：只选一条边，但是没有证明为什么这样做是对的

这里给出我花了一晚上想出的一个比较容易理解的证明方法，希望能给做此题的小伙伴一点帮助吧


------------
## 题目大意

找到一个连通子图使得点权和除以边权和最大

## 解法

答案一定来自密度最大的两节点链，所以读边时扫点求值，维护最大即可

## 解法证明

**在以下数学证明中，我们用$t$表示这个最大值**

### 证明一：证明环中一定包含一条链比它优

其实乍一看，链就一定比环优，现在我们尝试证明它：

![](https://img2020.cnblogs.com/blog/1924188/202007/1924188-20200715152450612-1589604178.png)

那么在这个简单环中，我们设置以下四个变量来表示环和链的$t$值

用 $t_{abc}$ 来表示环的 $t$ 值，有 $t_{abc}=\frac{a+b+c}{x+y+z}$

用 $t_{ab}$ 表示两节点链 $ab$ 的 $t$ 值，有 $t_{ab}=\frac{a+b}{x}$

用 $t_{bc}$ 表示两节点链 $bc$ 的 $t$ 值，有 $t_{bc}=\frac{b+c}{y}$

用 $t_{ac}$ 表示两节点链链 $ac$ 的 $t$ 值，有 $t_{ac}=\frac{a+c}{z}$

**开始证明**

首先，不妨设 $t_{ab}\geq t_{bc}\geq t_{ac}$，（PS：如果不满足，交换顺序即可，不影响证明的正确性）

那么化简 $t_{ab}$，$t_{bc}$，$t_{ac}$ 得到了一个包含三个不等式的不等式组：

$
\begin{cases}
ay+by\geq bx+cx\\
bz+cz\geq ay+cy\\
az+bz\geq ax+cx\\
\end{cases}
$

因为 $t_{ab}\geq t_{bc}\geq t_{ac}$，只需要证明 $t_{ab}>t_{abc}$ ，即可说明每一个环本身中，至少存在一个两节点链比这个环更优

设左式为 $left$ ，右式为 $right$，设：

$$left=t_{ab}=\frac{a+b}{x},right=t_{abc}=\frac{a+b+c}{x+y+z}$$

$1、$同时乘以：$x(x+y+z)$ 

$$left=(a+b)(x+y+z),right=x(a+b+c)$$

$2、$同时减去：$x(a+b)$ 

$$ left=(y+z)(a+b),right=cx $$

$3、$化简一步：

$$left=ay+by+az+bz,right=cx $$

$4、$根据上面的不等式组：

$$ay+by+az+bz\geq bx+cx+ax+cx=2cx+ax+bx$$

$5、$又因为 $a,b,c,x,y,z$ 均为正数，所以推出：

$$2cx+ax+bx>cx$$

$6、$推出：$left>right$，即 ：

$$t_{ab}>t_{abc}$$

综上所述：每一个环本身中，至少存在一个两节点链比这个环更优

**证毕**

那么得到了这样一个结果——每一个环本身中，至少存在一个两节点链比这个环更优。现在，我们就不用考虑环的情况了

既然我们可以证明环和链之间的大小关系，进一步思考：链和链之间的大小关系可不可以证明呢？

### 证明二：证明长链中一定包含一个短链比它优以及结论推广

让我们从最短的链证起，请看图：

![](https://img2020.cnblogs.com/blog/1924188/202007/1924188-20200715160517399-1347253465.png)

**开始证明：**

在这个三个节点组成的链中，我们设置以下三个变量来表示两个短链和一个长链的$t$值

用$t_{abc}$表示长链的$t$值，有$t_{abc}=\frac{a+b+c}{x+y}$

用$t_{ab}$表示短链$ab$的$t$值，有$t_{ab}=\frac{a+b}{x}$

用$t_{bc}$表示短链$bc$的$t$值，有$t_{bc}=\frac{b+c}{y}$

首先，不妨设：$t_{ab}\geq t_{bc}$（PS：如果不满足，依旧交换即可，不影响证明的正确性）

那么化简这个式子，得到一个不等式：

$$ay+by\geq bx+cx$$

因为：$t_{ab}\geq t_{bc}$，只需证$t_{ab}>t_{abc}$，即可说明在任意一三节点个长链本身中，至少存在一个两节点短链比这个长链更优

设左式为 $left$ ，右式为 $right$，且：

$$left=t_{ab}=\frac{a+b}{x},right=t_{abc}=\frac{a+b+c}{x+y}$$

$1、$同时乘以：$x(x+y)$

$$left=(a+b)(x+y),right=x(a+b+c)$$

$2、$同时减去：$x(a+b)$ 

$$left=y(a+b),right=cx$$

$3、$化简一步：

$$left=ay+by,right=cx$$

$4、$根据上面推出的不等式：$ay+by\geq bx+cx$，且 $x,y,a,b,c$ 均为正数，有$bx>0$，所以推出

$$ay+by>cx$$

$5、$推出：$left>right$，即：

$$t_{ab}>t_{abc}$$

综上所述：在任意一三节点个长链本身中，至少存在一个两节点短链比这个长链更优

但是还没有完，我们还需要得知长度为$n$的长度为$2$的链谁更优一些

$n$节点链可以看成是$n-2$的链再连上两个点构成的（如下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/kbu57x17.png)

而前面$n-2$长度的链可以用点权和比边权和算出它的$t$来，这时把这整个链看成是点权是$t$的节点，问题就又转化成两节点和三节点谁优了。

另外，对于其他形状的子图来说，同样适用刚才说的“缩点”法。只要缩成两、三节点链，我们就可以用结论证明啦！

**证毕**

综上，最优的解一定是一条两节点链，所以贪心求解

代码很简单，就不放了

---

## 作者：loctopus (赞：2)

## 简述题意
- 定义一张无向图的密度为其点权之和除以边权之和。

- 注：边权之和为零的图密度为零。

- 给定一张无向图，求该图的联通子图密度的最大值。

- 子图：选取一个顶点集，以两端点均在该顶点集中的边的全体为边集的图。

- 输出保留小数点后 $15$ 位，若与标准答案相差不超过 $10^{-9}$ 则 Accept。 

## 思路

下文中图的密度用 $\rho$ 表示。

经过初步思考可以发现，选出的子图中必定不含环，即一棵树。

证明如下：

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设选出一棵树后的点权和为 $A$，边权和为 $B$。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;新加入一条边 $(u,v)$，边权为 $c$，且使子图中出现一个环。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;则易得 $\rho_0 = {A\over B}$ ，$\rho_1 = {A\over B+c}$

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;易得 $\rho_0 > \rho_1$

那么，当加入一条边后仍为树时会发生什么呢？

我们像刚才那样再来一遍。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设选出一棵树后的点权和为 $A$，边权和为 $B$。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;新加入一条边 $(u,v)$，满足 $u$ 已在树上而 $v$ 不在树上,

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其中 边权为 $c$ ，$u$ 的点权为 $e$，$v$ 的点权为 $d$

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;则易得 $\rho_0 = {A\over B}$ ，$\rho_1 = {A+d\over B+c}$

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 则 $\rho_0 - \rho_1 = {A\over B}-{A+d\over B+c}={A(B+c)-B(A+d)\over B(B+c)}={cA-dB\over B(B+c)}$


&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设分子为 $S=cA-dB$

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果加边后 $\rho$ 增大，则 $S<0$ 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;故有 ${A\over B}<{d\over c}<{d+e\over c}$

至此我们可以得出结论：

- 要使加边后 $\rho$ 增大，则加入的边的 $\rho_{(u,v)}$ 应该**严格大于** $\rho$ 。

进一步可以得出本题的解题策略：

- 只选择密度**最大**的**一条边**。

当然题感超好的stO 神犇们 Orz自然是直接发现结论，然后反证一下就AC了。

放一个CF原题解通道 $\rightarrow$ [Codeforces Round # 254 Editorial By xyZ111](https://codeforces.com/blog/entry/12959)

那 code 就很简单啦。

```c++
#include<cstdio>
#include<iostream>
#define N 550
using namespace std;
int n,m,a,b;
double x[N],c,ans=0;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lf",&x[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lf",&a,&b,&c);
		ans=max(ans,(x[a]+x[b])/c);
	}
	printf("%.15lf",ans);
	return 0;
}

```



---

## 作者：XL4453 (赞：0)

### 解题思路：

直觉上来讲，选的边少，点和边的数量之比就大，也就更有可能选出更大的价值。

考虑每一次选出一条边，然后就以这一条边和它的两个顶点构成一个联通导出子图，求出价值即可。

----
### 证明：

首先权值，包括边权和点权，都是正数，这就为证明提供了很大的便利

设当前已经选择了两个节点，权值分别为 $a$ 和 $b$，两者之间有一条权值为 $x$ 的边，这样原来的价值为 $\dfrac{a+b}{x}$。

对于新加入的一个点，它与两个点都有连边而想要加入后使得价值更大这个命题弱于只与一个点有连边，这是显然的，接下来值讨论只与一个点有连边的情况。

再设新加入的点的权值为 $c$，与权值为 $a$ 的那一个点有一条权值为 $y$ 的边，那么在加入这个点后价值为 $\dfrac{a+b+c}{x+y}$。

此时如果 $\dfrac{a+b+c}{x+y}>\dfrac{a+b}{x}$，则有：
$ax+bx+cx>ax+ay+bx+by$，化简得到 $cx>ay+by$，也就是 $\dfrac{a+c}{y}-\dfrac{a}{y}>\dfrac{a+b}{x}$。

---
结合上面权值为正的条件，发现上面这个不等式严格强于 $\dfrac{a+c}{y}>\dfrac{a+b}{x}$，也就是说如果单独选择一条边，则选择 $a$ 与 $c$ 的那一条边更优。

---
然后，比较全选两条边和只选一条边。为了方便观察，转化 $cx>ay+by$，记 $cx=ay+by+k$，其中 $k>0$。

写出等式的弱形式：$ax+ay+k>0$。

即：$ax+ay+by+k>by$。

也就是：$ax+cx>by$。

添项并除以 $(x+y)\times y$ 得到：$\dfrac{a+b+c}{x+y}<\dfrac{a+c}{y}$。

命题得证。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,v[505],x,y,z;
double ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		ans=max(ans,((double)v[x]+(double)v[y])/(double)z);
	}
	printf("%.15lf",ans);
	return 0;
}
```


---

## 作者：CobaltChloride (赞：0)

~~既然没有Pascal题解,那本蒟蒻就来水一发~~

```
var n,m,i,p,q,r:longint;
a:array[1..500] of longint;
ans:double;
function max(x,y:double):double;
begin
if x>y then exit(x);
else exit(y);
end;//较大值
begin
read(n,m);
for i:=1 to n do read(a[i]);
for i:=1 to m do begin
read(p,q,r);
ans:=max(ans,(a[p]+a[q])/r);//枚举每条边,求最大值
end;
write(ans:0:12);//注意精度
end.

```

---

