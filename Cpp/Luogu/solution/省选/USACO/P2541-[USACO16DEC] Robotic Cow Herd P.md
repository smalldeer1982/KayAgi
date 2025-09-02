# [USACO16DEC] Robotic Cow Herd P

## 题目描述

Bessie 希望通过建造 $K$ 头逼真的机器人奶牛（$1 \leq K \leq 100,000$）来愚弄 Farmer John。

事实证明，建造一头机器人奶牛有些复杂。机器人上有 $N$ 个（$1 \leq N \leq 100,000$）独立的位置需要连接微控制器（因此每个位置必须连接一个微控制器）。对于每个位置，Bessie 可以从多个不同的微控制器模型中选择，每个模型的成本各不相同。

为了让机器人牛群对 Farmer John 看起来逼真，任何两头机器人的行为都不应完全相同。因此，任何两头机器人都不应使用完全相同的微控制器集合。对于任意一对机器人，至少应有一个位置上的微控制器模型不同。保证始终有足够的不同微控制器模型来满足此约束。

Bessie 希望以尽可能低的成本建造她的机器人牛群。请帮助她确定实现这一目标的最小可能成本！

## 样例 #1

### 输入

```
3 10
4 1 5 3 10
3 2 3 3
5 1 3 4 6 6```

### 输出

```
61```

# 题解

## 作者：xs_siqi (赞：10)

个人感觉这题更像一个构造题。听说这个构造很典？反正我赛时没想出来。

我们大家肯定都做过一道题叫做[序列合并](https://www.luogu.com.cn/problem/P1631)。这道题就是把那题拓展到数列个数很大的加强版。

如果没做的话，建议做了这题之后再来写这题。如果做了，建议回去看一下那题的做法，因为我是直接基于那题解法继续写的。

首先不难想到一个暴力思路是，直接把原来削弱版的结论暴力推广，这样复杂度就是 $O(n^n\sum_{i=1}^na_i)$，$a_i$ 是数列 $i$ 的元素个数。

然后说一个与正解无关的优化方法（不看不影响理解正解做法）。就是我们可以把每次比较进行优化。一次操作相当于将 $n$ 个元素中的某一个 $+1$ 然后放入原优先队列中，那么我们可以把这个 $n$ 元组写个双哈希存起来，然后预处理哈希值，修改过程是 $O(\log n)$ 的（因为找到这个元素的前驱后继是经典的哈希上二分的套路）。这样复杂度就是 $O(n\log n\sum_{i=1}^na_i)$ 的了。

不过我赛时因为数组开太大了爆空间然后寄了。

然后我们考虑进一步优化。我们发现这个原先暴力（我指的是 $O(n^n\sum_{i=1}^na_i)$ 的暴力方法）的主要瓶颈在于，你会枚举出很多重复的元素。

举个例子，就比如说我现在有两个方案：

```
1 1 2  -->  1 2 2

1 2 1  -->  1 2 2

```

我们发现两个不同的数列 $\{1,1,2\}$ 和 $\{1,2,1\}$ 拓展后出现了一个完全相同的数列 $\{1,2,2\}$。你可能觉得这个东西几百次才重复一次啊，但是这个重复的频率实际上是很高的，如果每次都判重肯定会带来极高的复杂度。

因此，我们的优化目的是：能否找到一种方案，使得每个不同的数列拓展不会产生相同的一个数列。

那么，接下来请**欣赏**这个解法（说“欣赏”的原因是因为如果你没做过这个套路是真的很难想到的）：

首先，我们按次小值减最小值从小到大排序（使得每次的损失最少，这个感性理解一下不难吧）。

比如说，我现在在这个 $n$ 元组中，知道了一个元素 $a_p$。那么我接下来有以下几个拓展方案：

以下是这个算法的流程。你在看的过程中可能会产生很多问号，因为直接把这个结论告诉你了，你肯定百分百看不懂。直接告诉你只是为了让你先了解这个算法的流程，看不懂没关系。

操作 $1$：将 $a_p$ 深入一层。即将 $a_1,\cdots,a_p,a_{p+1}\cdots,a_n$ 变为 $a_1,\cdots,a_p+1,a_{p+1}\cdots,a_n$。

操作 $2$：将下一个元素深入一层。即将 $a_1,\cdots,a_p,\cdots,a_n$ 变为 $a_1,\cdots,a_p,a_{p+1}+1,\cdots,a_n$。

操作 $3$：假如 $a_p=1$ 时，那么直接舍弃这个元素，选下一个元素，即将 $a_1,\cdots,1,a_{p+1},\cdots,a_n$ 变为 $a_1,\cdots,0,a_{p+1}+1,\cdots,a_n$。

接下来，我们只要证明这个方法是对的就好了。

首先，证明这个方法必然找到了前 $m$ 小的解。

- 我们发现如果想将某个元素深入一层，那就是第一个操作（感觉是废话）。

- 如果要将两个相邻的元素深入一层也是有方案的。你可能没动啥叫“将两个相邻的元素深入一层”，如下：

```
1 1 1 1 1 -> 1 2 1 1 1 -> 1 2 2 1 1
```

第 $2$ 个元素和第 $3$ 个元素均深入了一层，所以叫做“相邻的元素均深入一层”。

这个算法处理的流程是：

首先，当 $p=2$ 时，我们先将这个元素深入一层（$1$ 操作），此时 $p$ 变为 $2$。

然后 $p=2$ 会被再次找到，然后这次我们进行“将下一个元素深入一层”（$2$ 操作），此时 $p$ 变为 $3$。

然后就处理完了。

- 如果要将两个不相邻的元素深入一层也是有方案的。你可能没动啥叫“将两个不相邻的元素深入一层”，如下：

```
1 1 1 1 1 -> 1 2 1 1 1 -> 1 2 2 1 1 -> 1 2 1 2 1
```

第 $2$ 个元素和第 $4$ 个元素均深入了一层，所以叫做“不相邻的元素均深入一层”。

这个算法处理的流程是：

首先，当 $p=2$ 时，我们先将这个元素深入一层（$1$ 操作），此时 $p$ 变为 $2$。

然后 $p=2$ 会被再次找到，然后这次我们进行“将下一个元素深入一层”（$2$ 操作），此时 $p$ 变为 $3$。

当 $p=3$ 时，然后这次我们进行“删除这个元素，将下一个元素深入一层”（$3$ 操作），此时 $p=4$。

然后就处理完了。

你发现没有其他情况了。也就是说这个方法真的全处理完了，而且没有重复的！

然后到这里我再解释一下为什么第三个操作一定是在 $a_p=1$ 时执行的。

因为如果在 $a_p>1$ 时执行，那么这个操作必然可以被替换为，先以 $a_p=1$ 删除这个操作跳到下一个，然后下一个再通过 $1$ 操作深入一层。这样就重复同一个方案了。

这样每次做 $3$ 个操作，将每个元素放入优先队列里，优先队列里每次枚举到一个元素就会增加 $3$ 个元素，总共要求前 $m$ 小，所以这样复杂度就是 $O(m\log n)$，常数为 $3$。

你可能想说，这个算法太高明了！但是我是如何从题目一步一步想到这个算法的呢？

我在题解开头就曾说了这是一个构造题。所以这个东西是真的很难说是怎么想到的。所以说这个东西算是一个“求前 $k$ 小”的套路吧。

然后放个代码吧。

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int maxn=3e5+5;
void read(int &x){
	x=0;char ch=getchar();int f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')x=x*10+ch-'0',ch=getchar();
	x*=f;
}
struct node{
	int x,y,v,id;
	friend bool operator < (node x,node y){return x.v>y.v;}
}p[maxn];
bool cmp(node x,node y){return x.v<y.v;}
int n,m,tot,ans,sum0,sum1,pow1[maxn];
vector<int>a[maxn],g[maxn];
priority_queue<node> q;
signed main(){
//	freopen("contain.in","r",stdin);
//	freopen("contain.out","w",stdout);
	read(n),read(m);
	for(int k,x,i=1;i<=n;i++){
		read(k);
		for(int j=1;j<=k;j++)
			read(x),a[i].pb(x);
		sort(a[i].begin(),a[i].end());
		if(k>1)p[++tot].v=a[i][1]-a[i][0],p[tot].id=i;//按次小减去最小排序选取 
		else (sum0+=a[i][0]);
	}
	sort(p+1,p+tot+1,cmp);
	for(int i=1;i<=tot;i++)
		for(int j=0;j<a[p[i].id].size();j++)
			g[i].pb(a[p[i].id][j]);//找到非只有单一元素的数列，单一放到一个 vector 里面 
	for(int i=1;i<=tot;i++)(sum1+=g[i][0]);
	ans+=(sum0+sum1);m--;
	q.push((node){1,1,(sum1-g[1][0]+g[1][1]),0});
	while(!q.empty()&&m--){
		node t=q.top();
		int x=t.x,y=t.y,v=t.v;
		q.pop();ans+=(v+sum0);
		if(y<g[x].size()-1)q.push((node){x,y+1,v-g[x][y]+g[x][y+1],0});//一号操作：将这个元素深入一层 
		if(x<tot)q.push((node){x+1,1,v-g[x+1][0]+g[x+1][1],0});//二号操作：跳到下一个元素 
		if(x<tot&&y==1)q.push((node){x+1,1,v-g[x][1]+g[x][0]-g[x+1][0]+g[x+1][1],0});//三号操作：舍弃这个元素，跳到下一个元素 
	}
	printf("%d\n",ans);
	return 0;
}

```

更新：@huangrenheluogu 大神指出了题解的不足之处。注意一开始我加入的第一个序列下标为 $1$。这是为什么呢。如果直接加入下标为 $0$ 的就会出现下面这个情况：

```
1 1 1 ----> 2 1 1 (1 号操作)---> 1 2 1 （三号操作）
1 1 1 ----> 1 2 1 (2 号操作)
```
注意这个时候方案算重了。所以我们加入下标为 $1$ 的。

那为什么别的位不会出现这个问题呢？因为别的位进入时状态就已经被更新为 $1$ 了，即选择序列第二个元素。这样就跟一开始加入下标为 $1$ 的效果相同，也就不需要特判了。

---

## 作者：Nuyoah_awa (赞：6)

### 题目大意

题目抽象成一个 $n$ 行 $k$ 列的表格，对于每行只有固定几个值可选，在满足每列互不相同的情况下，求表格中所有值和的最小值。

### 题目分析

我们不妨将答案表格排个序，很容易发现最小一列一定是所有行最小值组成的，然后我们来考虑第二小的列，简单思考可得，这一列一定是第一列其中一个值替换成另一个值所得。

我们将这一结论推广，我们设一列为一个状态，通过这一列我们将其中任意一个值改为比这个值大的那个值就可以直接得到另一个比这个状态稍大的状态，由此我们可以得到所有状态。

然后我们可以以最小状态为基础，衍生其他状态，找到最小的 $k$ 个状态，我们只需用一个优先队列维护即可。

然后时间复杂度就是 $\mathcal O(k \times n \log n)$。

很明显过不了，我们发现时间复杂度较大的原因是对于每个状态，我们都会派生出 $n$ 个状态，并且不同状态可能会派生出相同的状态，这样就会重复计算。

为优化算法，我们可以考虑更改派生方法使之不会重复，从而优化这一部分的时间。

我们发现对于所有状态，我们都可以找到一个点 $p_{x,y}$，使得 $x$ 之下都是当前行的最小值。

我们考虑对于 $p$ 做点文章，我们只需派生 $3$ 种状态：

1. 将 $p$ 向右一列，即 $p_{x, y} \to p'_{x, y+1}$

2. 将 $p$ 向下一行，即 $p_{x, y} \to p'_{x+1, y}$

3. 当 $y = 2$，$p$ 向左一行，同时下一行的点向右一列。

非常巧妙的方法，同样也可以派生所有的状态，不过说实话非常难想。

时间复杂度是 $\mathcal O(k \log n)$ 加上一个小常数的。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#define int long long

using namespace std;

const int N = 1e5 + 5, INF = 2e18;
struct cow{
	int len, d[20], val;
}p[N];
struct node{
	int val, x, y;
};
int n, k, ans;
priority_queue <node> q;

bool cmp(int x, int y){return x < y;}
bool cmp_val(cow x, cow y){return x.val < y.val;}
bool operator < (node u, node v){return u.val > v.val;}

signed main()
{
	scanf("%lld %lld", &n, &k);
	for(int i = 1;i <= n;i++)
	{
		scanf("%lld", &p[i].len);
		for(int j = 1;j <= p[i].len;j++)
			scanf("%lld", &p[i].d[j]);
		p[i].d[p[i].len+1] = INF;
		sort(p[i].d + 1, p[i].d + p[i].len + 1, cmp);
		p[i].val = p[i].d[2] - p[i].d[1];
		ans += p[i].d[1];
	}
	sort(p + 1, p + n + 1, cmp_val);
	q.push({ans - p[1].d[1] + p[1].d[2], 1, 2});
	for(int i = 1;i < k;i++)
	{
		node u = q.top();
		q.pop();
		ans += u.val;
		q.push({u.val - p[u.x].d[u.y] + p[u.x].d[u.y+1], u.x, u.y+1});
		if(u.x != n)
			q.push({u.val - p[u.x+1].d[1] + p[u.x+1].d[2], u.x+1, 2});
		if(u.x != n && u.y == 2)
			q.push({u.val - p[u.x+1].d[1] + p[u.x+1].d[2] - p[u.x].d[2] + p[u.x].d[1], u.x+1, 2});
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：guosoun (赞：3)

[更好的阅读体验](https://gzy-blog.pages.dev/posts/p2541-usaco16decrobotic-cow-herd-p-%E9%A2%98%E8%A7%A3/)  ~~如果你打的开的话~~

## 0x00 题意

给你 $N$ 序列，第 $i$ 个的长度为 $M_i$，要求在每个序列中选择一个数，每种选法的代价为选择的 $N$ 个数之和，请求出代价前 $K$ 小的方案。

$N,K\leq10^5,M_i\leq10$

## 0x01 暴力

容易得出两个结论：

- 每个序列要从小到大选；

- 最小解为每个序列最小值之和。

于是就有了一个及其暴力的写法：

首先将所有序列从小到大排序，然后维护小根堆。

一开始将最小解（也就是所有序列选第一个数）入堆，

之后 $K$ 次出当前堆中最小的数，考虑将这个状态扩展，

对于这个状态将他的后继状态入堆，也就是从 $1$ 到 $N$ 枚举哪一行往后多选一个，将这 $N$ 后继种状态入堆。

这个算法的正确性很容易保证，问题是效率太低，每次扩展都要枚举 $N$ 种情况。

时间复杂度 $O(nk)$；

空间复杂度 $O(nk)$，因为堆中需要有至少 $N$ 个状态，每个状态需要记录 $N$ 行的情况。

## 0x02 优化 1

考虑优化上述暴力。

为了方便，接下来我要用图片来表示每一种状态：

![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul3niyrqj30ii0beglp.jpg)

这个图片为 $N=3,M_i=5$ 的情况 ，

左侧一列灰色格子，表示每个序列的最小值，

每行加重的颜色，代表着这个序列选的数，上图代表着第一行选了第 $4$ 小的数，第二行选了第 $3$ 小的数，第三行第 $5$ 小。

 回到我们的暴力，我们发现，每个状态会被不止一个前驱状态入堆。

下面这三个货均会让上面的入堆。

![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul3rly72j30ig0bc3yl.jpg)
![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul3vcad1j30ii0bgjrh.jpg)
![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul3y33v3j30i60bmwel.jpg)

但是，**只要任意一个前驱状态入堆，就可以保证这个情况被考虑。**

**减少每个状态的前驱状态，是我们优化的核心。**

现在，我们规定，每个状态的前驱状态，就是这个状态的最后一行选择前一个数的状态（这个数一定比当前的小）。

特殊的，如果最后一行已经选了最小的无法再小，那就从下往上选择第一个可以更小的行（这行选的数一定是第二个或者更往后）。

举例（上面是下面的前驱状态）：

![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul40hr9rj30i60bmwel.jpg)
![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul42vvk6j30ii0beglp.jpg)

----------

![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul4483vgj30ia0baaa2.jpg)![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul4cns4lj30i20b6jrf.jpg)

注意到，每个状态的前驱状态的代价都比自己小，这就代表着每个状态都打好提前量，在合适的时候入堆，不会出现错误。

到目前，我们已经保证每个状态都用唯一的前驱状态，那么，是不是每个状态都有一个后继状态呢？

我们考虑下面这个状态的后继状态，相当于考虑哪些状态会将下面这个状态称为前驱状态。

![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul4jo4atj30ia0eqglq.jpg)

首先，是将最后一行（蓝色行）往后选一个的情况，这种情况的前驱一定当前状态。

![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul4l3urpj30i60eoq33.jpg)

但是假设蓝色行后面有一行选了第二个数，那么变为最小值之后，其前驱也是当前状态，下面这两种也是其后继。

![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul4mjin1j30i40eg0sv.jpg)![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul4p8qk8j30i80eajrk.jpg)

那到这就有点难办了，一个状态最多有 $N$ 个后继，这不和没优化一样嘛！

## 0x03 优化 2

我们的困难是，一个状态可能有若干个后继状态，但我们发现，这若干个状态有一个共同点。

除了那个将最后一行再选一个的一般情况，剩下的后继状态，都是要将下面一个选最小的行选第 $2$ 个。

我们考虑，这些状态一定需要同时入堆吗，这些状态有没有所谓的前驱、后继关系呢？

我们要知道，前驱后继的关键所在，就是某个值一定比另一个值小，只有这样，后继才能在前驱后入堆。

那么，我们要增加的第二列，有一个大小关系吗？

我们将后两行的前两个标上数试试。

![](https://tva1.sinaimg.cn/large/006y8mN6gy1h6ul4s5pmpj30fk0dcmxc.jpg)

那么我们两个后继中，将第 $3$ 行选第 $2$ 个增加的代价为 $4-2$，将第 $4$ 行选第 $2$ 个增加的代价为 $5-4$，显然后者更小。

那么，我们：

- 将「第 $3$ 行选第 $2$ 个，第 $4$ 行选第 $1$ 个」设为「第 $3$ 行选第 $1$ 个，第 $4$ 行选第 $2$ 个」的后继；

- 将「第 $4$ 行选第 $2$ 个」设为「当前状态」的后继。

但我们发现这样的顺序很难维护，所以我们先将所有行的 $f_{i,2}-f_{i,1}$ 从小到大排序。

这样，我们每个状态的后继都可以很清楚的表达出来了：

- 当前行，选择下一个；
- 下一行，选择第二个；
- 如果当前行正在选第二个，则还可以变为「当前行选择第一个，下一行选择第二个」。

这样，每个状态只有 $3$ 个后继了，时间复杂度为 $O(k\times\log{n})$，可以接受。

但是如果每个状态都把每一行选到第几列记录的话，空间复杂度 $O(n^2)$ 就难以接受了。

但考虑到，如果现在最后一行为 $i$ 的话，后继状态是不会改变 $1$ 至 $i-1$ 行的，所以我们只要记录当前行以及这行选了第几个即可。

## 0x04 code

一些小提示：

- 状态不能用 set 去重~~（画蛇添足~~，因为理论上已经不可能重复加入，由于状态只记录了最后一行选的数，不保证前面行所取的完全一样，去重会少情况；
- 用查分更好实现，但在这里方便理解我没用，读者可以自行尝试；
- 需要 long long；

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
int n,k,m[N];ll ans;
array<int,20>p[N];//stl封装的定长数组，在这题中用它实现是为了将行的(p[2]-p[1])排序；
bool cmp(array<int,20> a,array<int,20> b){return a[2]-a[1]<b[2]-b[1];}//比较函数

struct node{ll val;int x,y;};//当前选法代价是val，最后一行是x，选了y列的数
bool operator<(node x,node y){return x.val>y.val;}//堆默认是大根对，所以要反着重载。
priority_queue<node>q;

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        p[i].fill(1e9+1);/*赋最大值*/cin>>m[i];
        for(int j=1;j<=m[i];j++) 
            cin>>p[i][j];
        sort(p[i].data()+1,p[i].data()+m[i]+1);//先对每行排序
        ans+=p[i][1];//这里ans为最小情况的和
    }
    sort(p+1,p+n+1,cmp);//(p[2]-p[1])的排序
    q.push({ans-p[1][1]+p[1][2],1,2});//将x=2,y=1入堆，以后的状态均可通过这个推出来。
    for(int i=2;i<=k;i++){//最小情况已经在ans里了
        int x=q.top().x,y=q.top().y;
        ll val=q.top().val;q.pop();//取堆顶+弹堆
        ans+=val;//统计答案
        q.push({val-p[x][y]+p[x][y+1],x,y+1});//后继1
        if(x==n) continue;//这是为了防止越界
        q.push({val-p[x+1][1]+p[x+1][2],x+1,2});//后继2
        if(y==2) q.push({val-p[x+1][1]+p[x+1][2]-p[x][2]+p[x][1],x+1,2});//后继3
    }
    cout<<ans;
    
}
```



---

## 作者：JoaoFelix (赞：3)

题外话：

~~感觉楼下的做法不太靠谱，所以会卡常~~

~~为什么要搜索剪枝？感觉数据范围变大了就随便卡吗？局限性感觉有点大~~

所以来写一篇题解！

其实这题一点都不卡常，首先有一种关于线段树回溯的做法，那个做法会比剪枝的做法好的多，但是要二分，所以多一个log，不过也不错！

这里介绍一种一个log的做法，我们回忆一下求k优解的几个常见的套路

一种是用堆实现的，我们同样按照类似的思路往下想

我们发现每个组里面都要选一个，那么我们可以发现第一个一定都要选，然后我们考虑依次类推到第k个解，我们还是按照依次往下取的方案类推，分三种情况！

```cpp
for(int i=1;i<=k;i++){
	node u=q.top();q.pop();ans+=u.sum;
	if(u.y<vec[id[u.x]].size()-1)q.push((node){u.sum-vec[id[u.x]][u.y]+vec[id[u.x]][u.y+1],u.x,u.y+1});
	if(u.x<n)q.push((node){u.sum+val[id[u.x+1]],u.x+1,1});
	if(u.x<n&&u.y==1)q.push((node){u.sum-val[id[u.x]]+val[id[u.x+1]],u.x+1,1});
}
```
1.如果我们当前这行还没有取到最后一个，那么我们就接着往下取

2.如果我们这样取到这个，但是下面我们继续要往下取，所以我们就直接跳入下一行就可以了。

3.由于我们钦定每一个第一个已经取过了，因此我们直接特判一下，这一行只取一个然后往下取（其实这类情况等同于第2类）

然后我们意会一下，发现所有的可能都会我们算进去，需要注意的是，我们初始化的时候需要按照下一次选的代价排序，这样才是正确的。

因为如果没有排序很有可能后面的可能性我们在前k个考虑不到，排在前面的总之是要被考虑到的

然后代码就很短，只有1k:（要用一下stl的优先队列）

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pb push_back
using namespace std;
const int N=1e5+5;
struct node{
	LL sum;int x,y;
	bool friend operator<(node a,node b){return a.sum>b.sum;} 
};
int n,k,c,id[N],val[N];LL res,ans;
priority_queue<node>q;
vector<int>vec[N];
bool cmp(int x,int y){return val[x]<val[y];}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1,x,y;i<=n;i++){
		scanf("%d",&x);
		if(x==1){scanf("%d",&y);res+=y;continue;}
		c++;id[c]=c;
		for(int j=1;j<=x;j++)scanf("%d",&y),vec[c].pb(y);
		sort(vec[c].begin(),vec[c].end());
		res+=(LL)vec[c][0];val[c]=vec[c][1]-vec[c][0];
	}
	ans=res;k--;n=c;
	sort(id+1,id+n+1,cmp);
	q.push((node){res+val[id[1]],1,1});
	for(int i=1;i<=k;i++){
		node u=q.top();q.pop();ans+=u.sum;
		if(u.y<vec[id[u.x]].size()-1)q.push((node){u.sum-vec[id[u.x]][u.y]+vec[id[u.x]][u.y+1],u.x,u.y+1});
		if(u.x<n)q.push((node){u.sum+val[id[u.x+1]],u.x+1,1});
		if(u.x<n&&u.y==1)q.push((node){u.sum-val[id[u.x]]+val[id[u.x+1]],u.x+1,1});
	}
	printf("%lld\n",ans);
	return 0;
}

```




---

## 作者：Nine_Suns (赞：1)

一个 $\mathcal O((\sum M)\log M+(k\log k+\sum M)\log V)$ 的做法，虽然复杂度有点劣但更容易想到。

显然的，答案是关于 $k$ 的下凸函数，于是我们考虑二分它在 $k$ 处的斜率，也就是所选的所有机械牛型号造价的 $\max$，考虑如何 check 一个斜率是否合法。

假设此时我们要 check 的斜率为 $x$，首先我们对 $p_i$ 进行排序，并令 $p_{i,j}\gets p_{i,j}-p_{i,0}$，接着实时维护一个小根堆表示当前机械牛造价小于等于 $x$ 的所有方案的造价。因为我们对 $p$ 进行了类似差分的操作，于是有 $c_{i,0}=0$，也就是说，一旦当前小根堆的大小大于等于 $k$，就可以让后面的 $c$ 全取到 $0$ 制造出 $k$ 种合法的方案。否则，对于一个 $c_{i,j}(j>0)$，我们从小根堆从小到大枚举元素，若当前值 $v+c_{i,j}\le x$ 则在枚举结束后将其加入小根堆，否则停止。在过程中，若小根堆元素 $\ge k$，则可以直接返回合法。由这一判断可以保证单次 check 的复杂度为 $\mathcal O(k\log k+\sum M)$。

  于是我们可以得到答案函数在 $k$ 处的斜率 $l$，接着我们令 $x=l-1$ 再进行一次 check，显然 check 时小根堆的元素数量小于 $k$，而此时堆里所有元素都是必选的。我们记此时所有堆中元素的和为 $S$，数量为 $c$，答案即为 $S+(k-c)l+k(\sum c_{i,0})$。最后的 $k(\sum c_{i,0})$ 是补回我们 check 时差分减掉的代价。

  
```cpp
#include <bits/stdc++.h>
#define pb push_back

using namespace std;
typedef long long ll; 
const int N = 1e5+5; 
int n, k, kl; 
vector <ll> c[N]; 
ll s; 
priority_queue <ll, vector <ll>, greater <ll> > pq; 
vector <ll> tp, tq;  

bool chk (ll v, int k) {
	while (pq.size()) pq.pop(); 
	pq.push(0); s = 0; 
	for (int i = 1;i <= n;i++) { 
		tp.clear(); 
		for (int j = 1;j < c[i].size();j++) {
			tq.clear(); 
			while (pq.size() && pq.top()+c[i][j] <= v) {
				tp.pb(pq.top()+c[i][j]); s += pq.top()+c[i][j]; tq.pb(pq.top()); pq.pop(); 
				if (tp.size()+tq.size()+pq.size() >= k) return 1; 
			}
			while (tq.size()) pq.push(tq.back()), tq.pop_back(); 
		}
		while (tp.size()) pq.push(tp.back()), tp.pop_back(); 
	}
	return 0; 
}

void solve (ll v) {
	while (pq.size()) pq.pop(); 
	pq.push(0); s = 0; kl = 1;  
	for (int i = 1;i <= n;i++) { 
		tp.clear(); 
		for (int j = 1;j < c[i].size();j++) {
			tq.clear(); 
			while (pq.size() && pq.top()+c[i][j] <= v) {
				tp.pb(pq.top()+c[i][j]); s += pq.top()+c[i][j]; tq.pb(pq.top()); pq.pop(); 
				++kl; 
			}
			while (tq.size()) pq.push(tq.back()), tq.pop_back(); 
		}
		while (tp.size()) pq.push(tp.back()), tp.pop_back(); 
	}
}

int main () {
	ios::sync_with_stdio(false); 
	cin.tie(0); cout.tie(0); 
	cin >> n >> k; ll D = 0; 
	for (int i = 1;i <= n;i++) {
		int L; cin >> L; 
		while (L--) {
			int x; cin >> x; 
			c[i].pb(x); 
		}
		sort(c[i].begin(), c[i].end()); 
		D += c[i][0];
		for (int j = 1;j < c[i].size();j++) c[i][j] -= c[i][0]; c[i][0] = 0; 
	}
	ll l = 0, r = 1e13; 
	while (l < r) {
		ll mid = l+r>>1; 
		if (chk(mid, k)) r = mid;
		else l = mid+1; 
	}
	solve(l-1); 
	cout << s+(k-kl)*l+D*k; 
	return 0; 
}
```

---

## 作者：666sb666 (赞：1)

这道题做法很多，但是如果常数写大了可能会被卡到80到95分。

这里提供一个较简单的算法。

考虑DP，设f[i][j][k]表示从第i行第j列的格子往左延伸k个格子后往上延伸的最远距离。

先预处理出每个格子往上、往左延伸的最远距离，然后显然是可以O(1)更新f的。

答案就是∑f[i][j][k]，但是发现会MLE，因此需要滚动数组。

复杂度:O(n^3)


---

## 作者：black_trees (赞：0)

弱化版 shopping plans，本篇截取了那题的[题解](https://www.luogu.com.cn/blog/Junko-Youmu/cco2020-d2t3)的一部分。

（虽然 shopping plans 原题下面 benq 认为 shopping plans 是这个的 extend version 就是了）

一些类似前置思考的东西在里面，这里为了简洁不放了。

---

> 你有 $n$ 个数组，你每个数组里需要选恰好一个。
>
> 你需要求出前 $k$ 大的方案，$n, k, \sum len \le 10^5$。

考虑将所有数组排序，初始状态显然应当为全部取第一个。

考虑用状态描述，一个比较暴力的想法是考虑设一个 $n$ 元组，第 $i$ 个位置表示第 $i$ 个数组选了哪个数。

显然这样状态就存不下，而且你发现我们转移会算重，比如 $n = 4$，初始状态是 $(1,1,1,1)$，我们至少可以经由 $(1,2,1,1)$ 和 $(1,1,2,1)$ 走到 $(1,2,2,1)$，这就不满足我们所说的 $\text{trans}$ 的条件。

所以我们考虑按顺序确定，先确定好第 $i$ 个人的再确定第 $i + 1$ 个人的，具体来说我们假定前面已经算好就行。

于是状态设计为 $(sum, i, j)$ 表示考虑当前和为 $sum$，在第 $i$ 个数组选了第 $j$ 个，并且我们默认 $i + 1 \sim n$ 全部选第一个，不然你状态不是代表的某个完整的局面的。

转移分两种，一种是 $(sum, i, j) \to (sum + a(i, j + 1) - a(i, j), i, j + 1)$，一种是 $(sum, i, j) \to (sum, i + 1, 1)$。

前者就是调整一下，后者就是选定第 $i$ 行的状态。

但是你发现这样子 $(2, 1, 1, 1)$ 在 $(?, 2, 1), (?, 3, 1), (?, 4, 1)$ 都会被算到。

这怎么办，注意到问题关键在于 $j = 1$，形如 $(?, x, 1) \to (?, x + 1, 1)$ 的状态并不会有任何改变，于是我们强制考虑中的 $j > 1$ 且向下转移也保持。

然后真正要选第一个则从 $j = 2$ 撤回去就行，但是仍然需要保证单调性。

具体来说我们令 $(?, i, 2) \to (?, i + 1, 2)$ 存在两种转移，一种是本来就都选。

一种是代价为 $[a(i + 1, 2) - a(i + 1, 1)] - [a(i, 2) - a(i, 1)]$，前者为选择 $a(i + 1, 2)$ 的代价（因为默认之前选过 $a(i + 1, 1)$），后者为通过从选 $a(i, 2)$ 撤回到选 $a(i, 1)$ 的代价。

注意到这样可能会有负代价的转移，所以我们按照 $a(x, 2) - a(x, 1)$ 升序排序即可。


---

## 作者：Yasuraoka_Hanabi (赞：0)

这是很有启发性的一题。听朋友说今年 US 队选也出了一道类似的题目。

------------

碰到这类求前 $k$ 小状态的和的题目，有一种类似图论的做法：

首先我们可以轻松找到最小状态（在本题，就是每个位置都选最小花费的那一个）。然后从最小状态开始，重复地把常数个后继状态压入堆中，然后取出堆顶作为新的最小状态，直到 $k$ 个状态被取出。

这个做法要想正确，需要保证两点：

- 从当前状态拓展到后继状态的时候，必须保证加上的权值非负。

- 每个状态，都可以通过这种拓展方式，从初始状态拓展到。

事实上这两条约束加上来，就极其类似 dijkstra 算法的过程，所以说它是一个类图论的做法。

这个过程的关键在于如何确定“常数个后继”怎么选。

我们不妨从初始状态开始，从前往后地确定。假设当前确定到第 $x$ 个位置，这个位置用的是（排序后）第 $y$ 个值。那么有这样几种拓展方式：

- 第 $x$ 个位置变成选第 $y+1$ 个值。

- 第 $x$ 个位置选第 $y$ 个值不再变化，此时开始调整第 $x+1$ 个位置的值（本来第 $x+1$ 个位置应该选第 $1$ 个值，我们此时让它去选 $2$ 个值）。

- 第 $x$ 个位置从选第 $y$ 个值变为选第 $1$ 个值，然后第 $x+1$ 个位置选择第 $2$ 个值。

按照这三种后继，显然一定能拓展到所有状态。但是对于第三种拓展，我们并不能保证加上的值是非负的，因为有“第 $x$ 个位置从选第 $y$ 个值变为选第 $1$ 个值”，这里要减去 $(p_{x,y}-p_{x,1})$，无法比较其与 $p_{x+1,2}-p_{x+1,1}$ 的大小。

注意到第三种情况的本质是钦定了第 $x$ 个位置选的就是最小值 $p_{x,1}$ 不再变动，因此实质上可以只在 $y=2$ 的时候执行这一步拓展，那么约束变成了 $p_{x,2}-p{x,1}\le p_{x+1,2}-p_{x+1,1}$，此时直接按照这个差升序排序做即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const ll MAXN=1e5+10,INF=1e18;
struct Node{
    ll sum,x,y;
    bool operator<(const Node& n2)const{
        return sum>n2.sum;
    }
};
priority_queue<Node>pq;
int n,k;
ll sum,ans;
vector<int>w[MAXN];
ll diff[MAXN],arr[MAXN];
bool cmp(int x,int y){return diff[x]<diff[y];}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    ll s=0;
    rep(i,1,n){
        int m;cin>>m;
        while(m--){
            int tmp;cin>>tmp;
            w[i].push_back(tmp);
        }
        sort(w[i].begin(),w[i].end());
        if(w[i].size()>1)diff[i]=w[i][1]-w[i][0];
        else diff[i]=INF;
        arr[i]=i;
        s+=w[i][0];
    }
    sort(arr+1,arr+1+n,cmp);
    ans=s;k--;
    if(!k){cout<<ans;exit(0);}
    pq.push((Node){s+diff[arr[1]],1,1});
    while(k--){
        Node tmp=pq.top();pq.pop();
        ll s=tmp.sum,x=tmp.x,y=tmp.y;   
        ans+=s;
        if(y+1<w[arr[x]].size())pq.push((Node){s+w[arr[x]][y+1]-w[arr[x]][y],x,y+1});
        if(x<n && diff[arr[x+1]]!=INF){
            pq.push((Node){s+diff[arr[x+1]],x+1,1});
            if(y==1)pq.push((Node){s-diff[arr[x]]+diff[arr[x+1]],x+1,1});
        }
    }
    cout<<ans;
    return 0;
} 

```

到这里大家不妨思考一个简单的同类问题：

给定 $n$ 个非负整数 $a_1,a_2,...,a_n$，对于 $\{1,2,...,n\}$ 的一个子集 $\{i_1,i_2,...,i_k\}$ 定义其权值为 $\sum_{1\le j\le k} a_{i_j}$。求这 $2^n$ 个子集里权值最小的前 $k$ 个子集的权值和。这里 $a_i,n,k\le 10^5$。

如果我们进一步加强，去掉 $a_i$ 非负的限制，也可以通过简单的转换得到做法。请读者自行思考，这个问题严格简单于本题。

---

