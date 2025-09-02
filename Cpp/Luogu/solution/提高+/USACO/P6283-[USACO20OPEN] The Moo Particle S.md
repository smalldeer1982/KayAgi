# [USACO20OPEN] The Moo Particle S

## 题目描述

FJ 的奶牛们最近很无聊，她们想到了一种全新的方式缓解无聊：研究高等物理！事实上，她们甚至成功发现了一种新的亚原子粒子，她们将其命名为“哞粒子”。

奶牛们正在进行一项有关 $N$ 个哞粒子的实验（$1\le N\le 10^5$）。粒子 $i$ 的“自旋”可以用范围在 $−10^9\ldots 10^9$ 之间的两个整数 $x_i$ 和 $y_i$ 来描述。有时两个哞粒子会发生相互作用。自旋为 ($x_i,y_i$) 和 ($x_j,y_j$) 的两个粒子之间仅当 $x_i\le x_j$ 并且 $y_i\le y_j$ 时会发生相互作用。在这些条件下，有可能这两个粒子中的一个会消失（另一个粒子不会发生任何变化）。在任意给定的时刻，至多只有一次相互作用会发生。

奶牛们想要知道在经过一些任意的相互作用之后剩余的哞粒子的最小数量。

## 说明/提示

### 样例输入输出 1 解释

一个可能的相互作用顺序：

- 粒子 $1$ 和 $4$ 相互作用，粒子 $1$ 消失。
- 粒子 $2$ 和 $4$ 相互作用，粒子 $4$ 消失。
- 粒子 $2$ 和 $3$ 相互作用，粒子 $3$ 消失。
仅留下粒子 $2$。

### 样例输入输出 2 解释

粒子 $3$ 不能与任何其他两个粒子相互作用，所以它必然会留下。粒子 $1$ 和 $2$ 中必然留下至少一个。

### 子任务
- 测试点 $3$-$6$ 满足 $N\le 10^3$。
- 测试点 $7$-$12$ 没有额外限制。

## 样例 #1

### 输入

```
4
1 0
0 1
-1 0
0 -1```

### 输出

```
1```

## 样例 #2

### 输入

```
3
0 0
1 1
-1 3```

### 输出

```
2```

# 题解

## 作者：wylt (赞：17)

USACO 2020 US Open 白银组T3 The Moo Particle

原题面（英文）：[http://www.usaco.org/index.php?page=viewproblem2&cpid=1040](http://www.usaco.org/index.php?page=viewproblem2&cpid=1040)

官方题解（英文）：[http://www.usaco.org/current/data/sol_moop_silver_open20.html](http://www.usaco.org/current/data/sol_moop_silver_open20.html)



------------
### 题意简述

有 $N$ 个粒子，每个粒子都有描述其自身的参数 $x,y$ 。

规定两个粒子可以相互作用当且仅当其中任意一个粒子的 $x,y$ 都分别比另一个粒子的 $x,y$ 大。

相互作用的规则是删掉其中任意一个，保留另一个。

其中 $1\le N\le 10^5$ 。

### 题目分析

我们可以这样想，把所有可以相互作用的点之间连边，将输入数据表示成一张图，这张图中可能含有许多互不联通的子图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ibdq9ycj.png)

上图是一种 $N=9$ 时的情况，拿 $8,5,1,4$ 这一组说，我们每次可以删去其中任意一个点，而只要删掉的不是割点，我们下一次就还可以继续删。由于没有一个图可以满足所有点都是割点，所有我们每次都一定可以找到一个非割点并删去，知道只剩一个点。

所以我们只需要找到其中有多少个互不联通的子图就可以了。

现在我们已经可以得到一半的分了，但想要 $AC$ 就必需在小于 $O(n^2)$ 的时间内找出集合数，当然这就需要再次从题目中找特殊性质了。

那么第二个技巧就是把 $x,y$ 在数轴上表示出来（看到 $x,y$ 就放到数轴上是个不错的习惯）。

则可以自己随便出一组样例：（来源于USACO官方题解）

![](https://cdn.luogu.com.cn/upload/image_hosting/czw23yt3.png)

那么放在坐标上就是：（来源于USACO官方题解）

![](https://cdn.luogu.com.cn/upload/image_hosting/e24xiie4.png)

再用前面的画图法表示为：

![](https://cdn.luogu.com.cn/upload/image_hosting/8fxj4yum.png)

所以，规律就呼之欲出了。

总结一下就是先对数据按 $x$ 排序，如果当前的 $i$ 的 $y_{i}\le \min(y_{1},y_{2}…y_{i-1})$ 因为排序后它是满足 $x_{i}\ge \max(x_{1},x_{2}…x_{i-1})$ 的，

所以此时这个 $i$ 不会和前面任意一个数分到一组，则它会是新的一组，那就把统计的 $cnt+1$ 就好了。

所以只要 $O(n\ \log(n))$ 排个序再加上 $O(n)$ 边遍历边统计就完事了！



------------

### 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100000
 
int N;
int x[MAXN], y[MAXN];
int cid[MAXN];
int minl[MAXN];
int maxr[MAXN];
 
bool cmp(int a,int b)
{
	if(x[a]==x[b]) return y[a]<y[b];
	return x[a]<x[b];
}
 
 
int main()
{
	cin >> N;
	for(int i=0;i<N;i++)
	{
		cin >> x[i] >> y[i];
		cid[i] = i;
	}
	sort(cid,cid+N,cmp);
	minl[0] = y[cid[0]];
	for(int i=1;i<N;i++)
		minl[i] = min(minl[i-1], y[cid[i]]);
	maxr[N-1] = y[cid[N-1]];
	for(int i=N-2;i>=0;i--)
		maxr[i] = max(maxr[i+1], y[cid[i]]);
	int ans = 1;
	for(int i=0;i<N-1;i++)
		if(minl[i] > maxr[i+1])
			ans++;
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：xixiup (赞：13)

### 写在前面的话

苏格拉底曾指出，求得知识的最好办法是有系统的问与答，故本题解采用了该种方式。

### 思路分享

问：这道题你怎么看？

答：首先看到这道题时，我们可能会想到二位偏序，但是很遗憾地告诉大家，这道题用二位偏序并不能解决。

问：为什么不能解决呢？

答：考虑对于 $1$ 个点，若此时将这个点加入了树状数组中，那么如何计算它的贡献呢？我们并不能在给定的时间中将这个贡献计算出来。

问：那么我们该怎么做呢？

答：考虑转化为一道图论题，若粒子 $x$ 与粒子 $y$ 之间可以发生作用，就在粒子 $x$ 与粒子 $y$ 之间连一条无向边。

问：为什么要这么做呢？

答：因为我们可以发现，若一些粒子处于一个连通块中，那么这些粒子就可以经过一番相互作用之后变为 $1$ 个粒子，而若两个粒子不在一个连通块中，那么这两个连通块再怎么相互作用也只可能变成 $2$ 个粒子。

问：但是这样仍是 $\Theta(n^2)$ 的，怎么优化呢？

答：考虑使用二位偏序的思想，将这些点以 $y$ 为关键字排序，我们就可以仅考虑 $x$ 一维了。

问：那么如何计算答案呢？

答：考虑使用并查集的思想，若排序后，一个粒子可以与它前面的粒子相互作用，那么就将这两个点连接起来，否则就计算一次贡献。

问：乍一看感觉很对呢，这就是正解了吧？

答：先别着急，我们先来看看这个思路的代码实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100100;
int n,Min;
struct node{
	int x,y;
	bool operator<(node u)const{
		return y==u.y?x>u.x:y<u.y;
	}//x坐标需要从大到小排序
	//因为如果两个粒子y坐标相同，那么x较大的更有可能与其他粒子互相作用，从而获得更小答案。
}moo[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&moo[i].x,&moo[i].y);
	}
	stable_sort(moo+1,moo+1+n);
	Min=1000000001;
	moo[0].y=-1000000001;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(moo[i].x<Min&&moo[i].y!=moo[i-1].y){
			ans++;//若与前面的粒子无法发生互相作用，那么将答案加1
		}
		Min=min(Min,moo[i].x);
	}
	printf("%d",ans);
	return 0;
}
```

答：看完之后，可以发现其实这个方法是错误的，只能通过前两个测试点（也就是两个样例）

问：为什么它是错的呢？乍一看感觉很对呢。

答：我们可以考虑如下图中的三个粒子。

![](https://cdn.luogu.com.cn/upload/image_hosting/h5ondvm8.png)

答：按照这种方式排好序之后，我们就可以得到三个粒子 $1$、$2$、$3$。通过这份代码所计算出来的答案是 $2$ ，两次贡献分别在点 $1$ 与 $2$ 处产生，但是其实正确的答案为 $1$，即 $3$ 粒子与另外两个粒子互相作用并使这两个粒子消失。

问：那好吧。那么我们还可以怎样做呢？

答：我们不妨设 $l_i$ 为粒子 $1 \sim i$ 的 $x$ 坐标的最小值，$r_i$为粒子 $i \sim n$ 的 $x$ 坐标的最大值，那么我们可以发现，若对于某个粒子 $i$，若 $l_i > r_i+1$，即粒子 $i$ 前面的所有粒子的 $x$ 坐标最小值还要大于后面所有粒子的 $x$ 坐标最大值，那么又因为我们已经将所有粒子按照 $y$ 坐标从小到大排序了，那么对于所有 $i \in \left[ 1,i \right],j \in \left( i,n \right]$，都有 $x_i > x_j$ 且 $y_i \leqslant y_j$，即 $\left[ 1,i \right]$ 与 $\left( i,n \right]$ 不可能在一个连通块中，就可以将答案加 $1$。

问：那么这就是正解了吗？

答：是的。

### 正解代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100100;
int n;
int l[maxn],r[maxn];
struct node{
	int x,y;
	bool operator<(node u)const{
		return y==u.y?x<u.x:y<u.y;
	}//与前面差不多的排序，但是y坐标相同时x坐标需改成从小到大
}moo[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&moo[i].x,&moo[i].y);
	}
	stable_sort(moo+1,moo+1+n);
	l[1]=moo[1].x;
	for(int i=2;i<=n;i++){
		l[i]=min(l[i-1],moo[i].x);
	}//处理l
	r[n]=moo[n].x;
	for(int i=n-1;i>=1;i--){
		r[i]=max(r[i+1],moo[i].x);
	}//处理r
	int ans=1;//这里ans的初始值需要赋为1
	for(int i=1;i<n;i++){
		if(l[i]>r[i+1]){
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：hhhyyyfff (赞：5)

注：原来一篇公式挂了

- 题意简述：有 $N\ (1 \le N \le 10^5)$ 个粒子，每个粒子的坐标 $(x_i,y_i)\ (-10^9 \le x_i,y_i \le 10^9)$。两个满足 $x_i \le x_j$ 且 $y_i \le y_j$ 的为消失的粒子 $i,j$，可以使其中一个粒子消失。进行任意次操作，求剩下的粒子的最小数量。

- 前置知识：排序，单调队列

- 算法分析 $O(N \log N)$：  
  根据题意，对于`红色`的粒子，`蓝色`的粒子可以与其操作，而`黄色`的粒子不能。  
  ![2-3-1](https://cdn.luogu.com.cn/upload/image_hosting/3ik1nx14.png)  
  将可以操作的粒子**连边**，同一连通块的最少留下一个粒子，理由如下：取任一生成树，取任一根节点，按深度操作，使深度较大的粒子消失，最后留下根节点。下图中`红色`的粒子为一个连通块。  
  ![2-3-2](https://cdn.luogu.com.cn/upload/image_hosting/mty759rj.png)  
  可以发现，若对于两个粒子 $a,b$，存在 $i$ 满足$x_i \le x_a,x_b$ 且 $y_i \le y_a,y_b$，则 $a,b$在同一连通块。  
  ![2-3-3](https://cdn.luogu.com.cn/upload/image_hosting/7dzft82n.png)  
  按 $x_i,y_i$ 为一、二关键字从大到小排序，对每个连通块保留 $y_i$ 最大的点，遍历所有粒子。设当前保留的 $y_i$ 有 $a_1,a_2,\dots,a_{cnt}$，当前 $y_i=m$，若 $m>a_{cnt}$，则出现新的连通块 $cnt \gets cnt + 1,a_{cnt}=m$；否则未出现新的连通块，若 $m \le a_{cnt-1}$，则合并两个连通块 $a_{cnt-1}=a_{cnt},cnt \gets cnt-1$，并重复操作，直到不能再合并。这个操作其实是单调队列的操作。答案为 $cnt$。

- 代码：

``` cpp
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

pair<int, int> a[100010];
int N, cnt, s[100010];

int main() {
    freopen("moop.in", "r", stdin);
    freopen("moop.out", "w", stdout);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d%d", &a[i].first, &a[i].second);
    sort(a + 1, a + N + 1);
    s[cnt = 0] = -2e9;
    for (int i = N; i > 0; --i)
        if (a[i].second > s[cnt])
            s[++cnt] = a[i].second; else
            while (a[i].second <= s[cnt - 1]) {
                s[cnt - 1] = s[cnt];
                --cnt;
            }

    printf("%d\n", cnt);
    return 0;
}
```

---

## 作者：feecle6418 (赞：4)

在能发生作用的粒子间连边，问题转化为求联通块个数。证明：取一联通块内任意生成树，从叶子开始删除叶子，一定能删到根。

按照 $x$ 排序，设当前点为 $i$，相当于要向所有 $y_j\le y_i$ 的 $j$ 连边。主席树优化建图即可，建一棵入树一棵出树分别连边（千万不能在一棵树上像我一样 sb 地连双向边。。。）。

时空复杂度均为 $O(n\log n)$。为了卡空间，不能用 vector 存图而要用邻接表。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b[100005],tot,cnt=0,v[4000005],h[4000005],ww;
struct P {
	int x,y;
} a[100005];
struct E{
	int to,next;
}e[12000005];
void A(int x,int y){
	e[++ww]={y,h[x]},h[x]=ww;
}
void dfs(int x) {
	if(!x||v[x])return ;
	v[x]=1;
	for(int i=h[x];i;i=e[i].next)dfs(e[i].to);
}
struct SEGMENT {
	int c[4000005][2],rt;
	bool is;
	void Ins(int &p,int l,int r,int x,int y) {
		int q=++tot;
		c[q][0]=c[p][0],c[q][1]=c[p][1];
		if(!is)A(q,p);
		else A(p,q);
		p=q;
		if(l==r) {
			if(!is)A(p,y);
			else A(y,p);
			return ;
		}
		int mid=(l+r)/2;
		if(!is) {
			if(x<=mid)A(p,c[p][1]),Ins(c[p][0],l,mid,x,y),A(p,c[p][0]);
			else A(p,c[p][0]),Ins(c[p][1],mid+1,r,x,y),A(p,c[p][1]);
		}
		else {
			if(x<=mid)A(c[p][1],p),Ins(c[p][0],l,mid,x,y),A(c[p][0],p);
			else A(c[p][0],p),Ins(c[p][1],mid+1,r,x,y),A(c[p][1],p);
		}
	}
	void Link(int p,int l,int r,int x,int y) {
		if(!p)return ;
		if(r<=x) {
			if(!is)return A(y,p),void();
			else return A(p,y),void();
		}
		int mid=(l+r)/2;
		Link(c[p][0],l,mid,x,y);
		if(x>mid)Link(c[p][1],mid+1,r,x,y);
	}
}q1,q2;
int main() {
	cin>>n,tot=n;
	for(int i=1; i<=n; i++)cin>>a[i].x>>a[i].y,b[i]=a[i].y;
	sort(b+1,b+n+1);
	for(int i=1; i<=n; i++)a[i].y=lower_bound(b+1,b+n+1,a[i].y)-b;
	sort(a+1,a+n+1,[](P i,P j) {
		return i.x^j.x?i.x<j.x:i.y<j.y;
	});
	q2.is=1;
	for(int i=1; i<=n; i++) {
		q1.Link(q1.rt,1,n,a[i].y,i);
		q1.Ins(q1.rt,1,n,a[i].y,i);
		q2.Link(q2.rt,1,n,a[i].y,i);
		q2.Ins(q2.rt,1,n,a[i].y,i);
	}
	for(int i=1; i<=n; i++) {
		if(!v[i])dfs(i),cnt++;
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：信守天下 (赞：3)

## [洛谷传送门](https://www.luogu.com.cn/problem/P6283)
## 思路
首先有个很简单的想法，依次判定每两个粒子是否可以互相消掉。

但这显然不行，因为你无法确定要消除两个粒子中的哪一个。

我们可以将每个哞粒子看成一个点。

所以就可以把每两个可以互相消除的点建立一条无向边。

那么题目就转化成了有多少个连通图。

但实际上我们并不需要真正去建图。

我们可以先将所有点按 $x$ 坐标优先，$y$ 坐标其次的顺序进行排序。

这样我们就可以直接记录当前图中 $y$ 坐标最小的点。

利用单调性，后枚举的点的 $x$ 坐标一定比当前记录点的 $x$ 坐标大。

所以只要其他点的 $y$ 坐标比它大，就表示可以建边。

在遇到 $y$ 坐标更小的点时，可以直接更换当前点。

如果不比它小，直接将可以合并的点合并，留下 $y$ 坐标的最低点。
## $code$
~~~cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
struct E {
  int x, y;
  bool operator<(const E &e) const {  // 先x后y排序
    return x < e.x || (x == e.x && y < e.y);
  }
} e[kMaxN];
int s[kMaxN] = {1 << 30};            // 初始化边界
int n, t;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].x >> e[i].y;
  }
  sort(e + 1, e + 1 + n);
  for (int i = 1; i <= n; i++) {
    if (e[i].y < s[t]) {             // 遇到更低点则记录
      s[++t] = e[i].y;
    } else {
      for (; t > 1 && e[i].y >= s[t - 1]; t--) {  // 将可以合并的点合并，留下最低点
        s[t - 1] = s[t];
      }
    }
  }
  cout << t;
  return 0;
}
~~~

---

## 作者：OfstAutomataMachine (赞：3)

关于这道题……悲惨的故事

首先，考试时看到这道题：明明就是并查集模板鸭！只要看有多少个集就行了！

然而，需要 $O(n^2)$ 的复杂度合并，就算离散化后set优化，还是TLE了6个点，对了6个点，但还是能进AU的。

在结束的前2分钟，这个智障又随便优化了一下，交了，结果只对了4个点。

但是，令他万万没想到的是，USACO并不是IOI赛制，而是以最后一次提交为主，于是与金组擦肩而过。

教训：每次不要着急提交，确定后十拿九稳后再交，改错不要着急改，先看好确定解决方案后再改。



------------
官方题解：

可以考虑利用单调性，先以x优先，y其次的顺序排序，用两个数组 $minl,maxr$ 分别记录前 $i$ 个数y的最小值和后 $j$ 个数y的最大值。

对于第 $i$ 个数，如果 $minl_i>maxr_{i+1}$，由于x是从小到大的，所以前面的x都是小于后面的x的，故不可能发生反应 ，ans++；

其实和并查集有异曲同工的作用。

证明同一个集里面必然只剩一个：由于在一个集里面，每一个点都可以到达另一个点，故定一个点x，其他点必然都可以到达x。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,ans=1,x[100001],y[100001],minl[100001],maxr[100002],id[100001];
bool cmp(int a,int b)
{
	return x[a]==x[b]?y[a]<=y[b]:x[a]<=x[b];
}
int main()
{
	freopen("moop.in","r",stdin);
	freopen("moop.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		id[i]=i;
	}
	sort(id+1,id+1+n,cmp);
	minl[0]=1e9+1;
	for(int i=1;i<=n;i++)
		minl[i]=min(minl[i-1],y[id[i]]);
    maxr[n+1]=-1*(1e9+1);
	for(int i=n;i>=1;i--)
		maxr[i]=max(maxr[i+1],y[id[i]]);
	for(int i=1;i<n;i++)
		ans+=(minl[i]>maxr[i+1]);
	cout<<ans;
	return 0;
 } 
```


---

## 作者：Godzilla (赞：1)

### 题目大意 ：

有 $N$个点 $(x_i,y_i)$  ，如果存在 $i$ ，$j$ ，使得 $x_i\le x_j$ ，$y_i \le y_j$ ，称它们相互作用。

相互作用可以删除其中一个点，保留一个点。

求经过任意次相互操作后剩余点的最小数量。

$1\le N \le 10^5$ ，$-10^9 \le x_i,y_i \le 10^9$ 。

---------------------------------

### 前置知识 :

1. [单调栈](https://zhuanlan.zhihu.com/p/346354943)

--------------------------------------

### 思路 ：

首先，按照 $x_i$ 为第1关键字， $y_i$  为第2关键字排序，保证其有序，方便处理。

不能从 $max\{x_i\}$ 或 $max\{y_i\}$ 的点向前作用，因为会出现这种情况 :

$x_1<x_2<x_3$ ，$y_1<y_3<y_2$ 。

那么如果从2或3点作用的话，最后剩下了2个点。

但是从2作用1，留下1，再用3作用1，只会剩下1个点。

这本质上是一种贪心，对于一对点 $(i,j)$ ，假设按照 $x_i$ 为第1关键字排徐，

那么留下来的是 $\min\{y_i,y_j\}$  。因为后面的点 $x_k$ 都比它们大，就不用考虑，

只需考虑 $y$ 对答案的影响了。

恰好，这种作用方式可以用单调队列来做。

如果能作用，就作用，并且留下最小的那个。

-----------------------------------

### 代码 :

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define LL long long

using namespace std;

const int kMax=1e5+5;
const int kInf=1e9+5;

struct Dot{
	int x,y;
}d[kMax];

int n;
int s[kMax],h,w[kMax];

bool cmp(Dot x,Dot y){
	if(x.x!=y.x){return x.x<y.x;}
	return x.y<y.y;
}

int Read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-'){y=-1;c=getchar();}
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();
	}
	return x*y;
}

int main(){
	n=Read();
	for(int i=1;i<=n;++i){d[i].x=Read();d[i].y=Read();}
	sort(d+1,d+1+n,cmp);//按x为关键字排序
	for(int i=1;i<=n;++i){
		int sum=0,h2=h,last=kInf,pos;
		while(h>0&&d[s[h]].y<=d[i].y){
			if(d[s[h]].y<last){last=d[s[h]].y;pos=s[h];}//找到能作用的点其中y最小的1个
			sum+=w[h];//累加宽度
			w[h]=0;
			h--;
		}
		if(h==h2){s[h+1]=i;}
		else{s[h+1]=pos;}
		w[++h]=sum+1;//加入单调队列
	}
	printf("%d\n",h);
	return 0;
}
```





---

## 作者：j_GF_y (赞：1)

### 题目：

[The Moo Particle S](https://www.luogu.com.cn/problem/P6283)

------------

### 题目大意：

有 $N$ 个粒子，每个粒子都有描述其自身的参数 $x$,$y$ .规定两个粒子可以相互作用当且仅当其中任意一个粒子的 $x$,$y$ 都分别比另一个粒子的 $x$,$y$ 大.相互作用的规则是删掉其中任意一个，保留另一个.其中 $1$ $\leq$ $N$
 $\leq$ $10^5$.

------------

### 思路：

第一想法建图,能消除的粒子互相建无向边,然后求图里连通块的个数.但时间复杂度是 $O($ $N^2$ $)$,明显过不了.

发现将粒子按 $x$ 为第一关键词, $y$ 为第二关键词升序排序,排序后分别求出 $y$ 坐标的前缀最小值和后缀最大值,如果存在两个连通块中左侧最小的 $y$ 坐标小于等于右侧最大的 $y$ 坐标,就可以合并;如下面一组样例(来自官方题解):

    7

    1 0

    0 1

    -1 0

    0 -1

    3 -5

    4 -4

    2 -2
    
排序后,第 $i$ 个粒子和第 $i+1$ 个粒子不在一个可消除的连通块中,即满足
$min$ $($ $y_1$ $,$ $y_2$ $,$ $...$ $,$ $y_i$ $)$ $>$ $max$ $($ $y_{i+1}$ $,$ $y_{i+2}$ $,$ $...$ $,$ $y_N$ $)$ (因为 $x$ 已经有序),所以我们就可以把时间复杂度降至 $O($ $N$ $)$.

------------

### code:

    #include<iostream>
    #include<cstdio>
    #include<cstring>
    #include<algorithm>
    #define aa q[i].a
    #define bb q[i].b
    using namespace std;
    int a[100001],b[1000001],ans,n,m;
    bool pool[100001];

    struct qq{
        int a,b;
        bool operator <(const qq &tmp)const{

            if(a!=tmp.a)return a<tmp.a;
            else return b<tmp.b; 

        }
    }q[10000001];

    int main(){
        cin>>n;

        for(int i=1;i<=n;i++){
            scanf("%d%d",&aa,&bb);
        }

        sort(1+q,1+q+n);

        for(int i=n;i>=1;i--){

            if(!pool[i]){
            //	cout<<endl<<i<<endl;

                for(int j=i-1;j>=1;j--){

                    if(!pool[j]&&bb>=q[j].b){
                        pool[j]=1;
                        ans++;
                    }
                    else if(!pool[i]&&pool[j]){
                        pool[i]=1;
                        ans++;
                    }

                }

                pool[i]=1;
            }

        }

        cout<<n-ans;
    } 
    
求过鸭~

---

## 作者：Parat_rooper (赞：0)

**解题思路：**

首先，我们发现本题直接考虑消除点是不可做的，所以我们换一个思路考虑。

我们把所有满足条件的点之间连一条边，可以发现，同一个连通块中的点都能消成一个点，于是问题就变成了求解连通块有多少个。

然后，看到题目中给的不等式 $\begin{cases}x_i \le x_j\\y_i \le y_j\\\end{cases}$
就自然想到了排序 	。

不妨对$x$进行排序，然后按照$x$不减的顺序考虑每个点，对于连续两个点$i$和$j$，如果$y_j < y_i$,说明$i$和$j$是不连通的，要记录到答案中。否则说明$i$和$j$不仅是联通的，而且$i$还可以通过$j$连接之前一些点，然后将边全连完后，保留最小的$y$的$i$即可。

以上操作可以通过栈来实现，排序时应注意以$y$作为第二关键字。

**复杂度分析：**

时间：

$$\Theta(N \log N)$$

空间：

$$\Theta(N)$$

代码如下：

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

struct E {
  int x, y;
  bool operator<(const E &e) const {  // 先x后y排序
    return x < e.x || (x == e.x && y < e.y);
  }
} e[kMaxN];

int s[kMaxN] = {1 << 30};  // 初始化边界
int n, t;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].x >> e[i].y;
  }
  sort(e + 1, e + 1 + n);
  for (int i = 1; i <= n; i++) {
    if (e[i].y < s[t]) {  // 遇到更低点则记录
      s[++t] = e[i].y;
    } else {
      for (; t > 1 && e[i].y >= s[t - 1]; t--) {  // 将可以合并的点合并，留下最低点
        s[t - 1] = s[t];
      }
    }
  }
  cout << t;
  return 0;
}
```


---

## 作者：qhy_ (赞：0)

### 思路
- 消失的过程比较麻烦，不知道应该让哪一个消失来达到最优，所以我们可以换一个角度想。
- 这道题可以看成在每两个满足 $x_i\leq x_j,y_i\leq y_j$ 的点之间建一条无向边(就是消失)，问可以形成多少个连通块。（这样就不用考虑消失哪一个了。）
- 注意过程中保留 $y$ 值最小的点，因为它最可能与其他点联系。

## code

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

struct E {
  int x, y;
  bool operator<(const E &e) const {
    return x < e.x || (x == e.x && y < e.y);
  }
} e[kMaxN];
int s[kMaxN] = {1 << 30};
int n, t;

int main() {
  //freopen("moop.in", "r", stdin);
  //freopen("moop.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].x >> e[i].y;
  }
  sort(e + 1, e + 1 + n);
  for (int i = 1; i <= n; i++) {
    if (e[i].y < s[t]) {
      s[++t] = e[i].y;  //连边
    } else {
      for (; t > 1 && e[i].y >= s[t - 1]; t--) {
        s[t - 1] = s[t];
      }
    }
  }
  cout << t;
  return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：0)

首先题目很明显可以转化成按照所有可以互相作用的点连边，求连通块的个数

因为每个连通块都是可以具体消除到只剩一个点的，可以随意去掉一些边当作树来看即可

一种正常的思路就是 按照$x$从大到小排序 然后就可以只管$y$了

具体的条件是 对于$i<j$ 如果$y_i<y_j$ 那么$i$和$j$就可以互相作用

但是如果两两考虑连边的话复杂度是$O(n^2)$的，考虑优化

可以发现排完序后的每一段连通块在排序序列上也是连续的区间

具体证明：对于$i<j$ $i$和$j$能够互相作用

对于任意的$i<k<j$ 如果$y_k>y_j$，那么$k$可以和$j$作用，如果$y_k<y_j$，因为$y_j<y_i$，所以$y_k<y_i$，那么$k$可以和$i$作用

一直往右搜二分搞最右端点（即最长区间）即可 
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
struct Node{
    int x,y;
}p[N];
int n,ans,Minn[N],r[N];
inline int Read(){
    char ch;
    int f=1;
    while((ch=getchar())<'0'||ch>'9')
        if(ch=='-') f=-1;
    int x=ch^48;
    while((ch=getchar())>='0'&&ch<='9')
        x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
inline bool Cmp(const Node u,const Node v){
    return u.x>v.x||(u.x==v.x&&u.y>v.y);
}
inline int Min(const int x,const int y){
    return x<y?x:y;
}
inline void Init(){
    n=Read();
    for(register int i=1;i<=n;i++){
        p[i].x=Read();
        p[i].y=Read();
        r[i]=i;
    }
    sort(p+1,p+n+1,Cmp);
    Minn[n]=p[n].y;
    for(register int i=n-1;i;i--)
        Minn[i]=Min(Minn[i+1],p[i].y);
    return ;
}
inline void Query(){
    for(register int i=1;i<=n;i++){
//      printf("%d %d\n",i,r[i-1]);
        if(i>r[i-1]) ans++;
        else r[i]=r[i-1];
        int le=i,ri=n;
        while(le<ri){
            int mid=le+ri+1>>1;
            if(Minn[mid]<=p[i].y) le=mid;
            else ri=mid-1;
        }
//      r[i]=le;
        if(le>r[i]) r[i]=le;
    }
    printf("%d\n",ans);
    return ;
}
int main(){
    Init();
    Query();
    return 0;
}
```

---

