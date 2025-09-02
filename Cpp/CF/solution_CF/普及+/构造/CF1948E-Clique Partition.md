# Clique Partition

## 题目描述

You are given two integers, $ n $ and $ k $ . There is a graph on $ n $ vertices, numbered from $ 1 $ to $ n $ , which initially has no edges.

You have to assign each vertex an integer; let $ a_i $ be the integer on the vertex $ i $ . All $ a_i $ should be distinct integers from $ 1 $ to $ n $ .

After assigning integers, for every pair of vertices $ (i, j) $ , you add an edge between them if $ |i - j| + |a_i - a_j| \le k $ .

Your goal is to create a graph which can be partitioned into the minimum possible (for the given values of $ n $ and $ k $ ) number of cliques. Each vertex of the graph should belong to exactly one clique. Recall that a clique is a set of vertices such that every pair of vertices in it are connected with an edge.

Since BledDest hasn't really brushed his programming skills up, he can't solve the problem "given a graph, partition it into the minimum number of cliques". So we also ask you to print the partition itself.

## 样例 #1

### 输入

```
3
2 3
5 4
8 16```

### 输出

```
2 1
1
1 1
3 1 5 2 4
2
1 1 2 1 2
1 2 3 4 5 6 7 8
1
1 1 1 1 1 1 1 1```

# 题解

## 作者：_Z_F_R_ (赞：11)

Update on 2024.10.29：修改了一处笔误，感谢 @Bugbread 指出，顺便修改了一些表述。

---

玄学，赛时乱搞过了。

### 题意

给你 $N$ 个点与正整数 $k$，让你给每个点赋一个权值 $a_i$，使得 $\{a_i\}$ 是一个 $1 \sim N$ 的排列。然后对所有满足 $|i - j| + |a_i - a_j| \le k$ 的数对 $(i, j)$，在结点 $i$ 与结点 $j$ 之间有连一条边。求一个满足条件的 $\{a_i\}$，使图可以分成 $M$ 个[团](https://oi-wiki.org/graph/concept/#%E5%9B%A2)，并最小化 $M$。

### 思路

以下 $i, j$ 两数若同时出现，若无特殊说明，均为正整数，并满足 $1 \le i, j \le N$，且 $i \not = j$。

首先两个显然的贪心：

- 结论一：所有选择的团内，结点的编号一定连续，即，团内结点的编号的集合类似于 $\{l, l + 1, l + 2, \dots, r - 1, r\}$。

  - 证明：设有两个团，且一个团内结点编号的最大值大于另一个团内结点编号的最小值，即类似的理解为这两个团节点编号在在值域上“相交”，那么可以合理“交换”两个点（即，在交换结点所在的团的同时，交换 $a_i$），使得两个团在值域上“不相交”。
    
    例如：两个团的结点编号集合分别为 $S_1 = \{1, 3\}$ 和 $S_2 = \{2\}$，$\{a_i\} = \{1, 2, 3\}$，那么可以交换为 $S_1' = \{1, 2\}$ 和 $S_2 = \{3\}$，$\{a_i'\} = \{1, 3, 2\}$。
    
    交换后，在不等式 $|i - j| + |a_i - a_j| \le k$ 中，$|a_i - a_j|$ 不变，$|i - j|$ 总是减小。则只会连更多的边，不会影响结果。
    
- 结论二：所有选择的团内，所有结点的权值 $a_i$ 排序后一定连续，即，团内结点的权值 $a_i$ 的集合类似于 $\{l, l + 1, l + 2, \dots, r - 1, r\}$。

  - 证明：将 $a_i$ 看做新的结点编号，结点编号看做新的 $a_i$，构造新图。则在新图中，对于每个有连边的数对 $(i, j)$，在新图中 $(a_i, a_j)$ 依然是连边的，无连边的数对亦然，余下同结论一证明。
  
还有两个结论：

- 结论三：每个团大小不超过 $k$。
  - 证明：若团大小超过 $k$，则必有一个两个数均为团内结点编号的数对 $(i, j)$，使得 $|i - j| \ge k$。又因为对于任意 $i,j$，$|a_i - a_j| \ge 1$，所以 $|i - j| + |a_i - a_j| > k$，不满足团的性质。
- 结论四：对于任意整数 $t$，将每个团中各结点权值加上 $t$ 不影响结果。
  - 证明：令 $a_i' = a_i + t$，显然对于任意数对 $(i, j)$，$|i - j|$ 不变，$|a_i' - a_j'| = |(a_i + t) - (a_j + t)| = |a_i + t - a_j - t| = |a_i - a_j|$，所以 $|i - j| + |a_i' - a_j'| = |i - j| + |a_i - a_j|$，不影响结果。
  
综上，可以得出最佳的划分方案：

- 将 $1 \sim N$ 个结点划分成 $t$ 个部分，使得每个部分内编号连续，每个部分内 $a_i$ 的编号连续且其值域与结点编号的值域相等。形式化的，将 $N$ 个结点划分为 $[l_1, l_2), [l_2, l_3), [l_3, l_4), \dots, [l_{t - 1}, l_t), [l_t, l_{t + 1})$ 这样 $t$ 个部分，使得 $1 = l_1 < l_2 < l_3 < \dots < l_t < l_{t + 1} = N + 1$，且 $\forall i \in [1, t]$，$l_i \le a_i < l_{i + 1}$。

------------

根据结论四，显然我们可以把图划分为若干部分，使得每个部分可以转化为：结点编号为 $1 \sim M$，$\{a_i\}$ 是 $1 \sim M$ 的排列，构造一个 $\{a_i\}$ 使得这个图按给定方式连边后是一个团。

显然每个部分是否可以通过合适的 $\{a_i\}$ 转化为团，只与其所含结点的数量有关。

根据结论三，不可能有 $M > k$，考虑构造 $M = k$ 的情况。

可以构造：
$$a_i = \begin{cases}
\lfloor \frac{M}{2} \rfloor + 1 - i & \text{if } i \le \lfloor \frac{M}{2} \rfloor  \\ 
M + \lfloor \frac{M}{2} \rfloor + 1 - i & \text{otherwise.}
\end{cases}$$

来满足要求（即对于 $\{a_i\} = \{1, 2, \dots, M\}$，反转其区间 $[1, \lfloor \frac{M}{2} \rfloor]$ 与区间 $[\lfloor \frac{M}{2} \rfloor + 1, M]$）。

证明（设 $1 \le i < j \le M$，且 $i, j$ 是正整数）：

1. $i < j \le \lfloor \frac{M}{2} \rfloor$，则 $|i - j| + |a_i - a_j| = j - i + |\lfloor \frac{M}{2} \rfloor + 1 - i - \lfloor \frac{M}{2} \rfloor - 1 + j| = j - i + |i - j| = 2j - 2i = 2(j - i) \le 2 \times (\lfloor \frac{M}{2} \rfloor - 1) \le M$；
2. $j > i > \lfloor \frac{M}{2} \rfloor$，则 $|i - j| + |a_i - a_j| = j - i + |M + \lfloor \frac{M}{2} \rfloor + 1 - i - M - \lfloor \frac{M}{2} \rfloor - 1 + j| = j - i + |i - j| = 2j - 2i = 2(j - i) \le 2 \times (\lceil \frac{M}{2} \rceil - 1) \le M$；
3. $i \le \lfloor \frac{M}{2} \rfloor < j$，则 $|i - j| + |a_i - a_j| = j - i + |\lfloor \frac{M}{2} \rfloor + 1 - i - M - \lfloor \frac{M}{2} \rfloor - 1 + j| = j - i + |j - i - M| = j - i + i - j + M = M$；

证毕。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll Read() {
	int sig = 1;
	ll num = 0;
	char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') {
			sig = -1;
		}
		c = getchar();
	}
	while(isdigit(c)) {
		num = (num << 3) + (num << 1) + (c ^ 48);
		c = getchar();
	}
	return num * sig;
}
void Write(ll x) {
	if(x < 0) {
		putchar('-');
		x = -x;
	}
	if(x >= 10) {
		Write(x / 10);
	}
	putchar((x % 10) ^ 48);
}

vector<int> Gen_vec(int siz) {
	int i;
	vector<int> vec;
	for(i = siz / 2; i >= 1; i--) {
		vec.push_back(i);
	}
	for(i = siz; i > siz / 2; i--) {
		vec.push_back(i);
	}
	return vec;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while(testcase--) {
		int n, k, i, j;
		n = Read(), k = Read();
		for(i = 1; i <= n; i += k) {
			int l = i, r = min(i + k - 1, n);
			auto vec = Gen_vec(r - l + 1);
			for(auto v : vec) {
				Write(v + i - 1), putchar(' ');
			}
		}
		putchar('\n'), Write((n + k - 1) / k), putchar('\n'); // (n + k - 1) / k 下取整 = n / k 上取整
		for(i = 1; i <= n; i += k) {
			int l = i, r = min(i + k - 1, n);
			for(j = l; j <= r; j++) {
				Write((l - 1) / k + 1), putchar(' ');
			}
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：5)

被结论题创飞了，被数据范围骗光了。

由于和曼哈顿距离相关，尝试将 $(i,a_i)$ 扔到平面直角坐标系上。

考虑一些局部的性质：一个团有何特点。

首先是其中点对间最大曼哈顿距离不超过 $k$。

其次，其在 $x$ 轴和 $y$ 轴上的投影一定是连续的一段区间。

再而，其大小必然不超过 $k$。

容易感性理解，证明亦不难（详见[这篇题解](https://www.luogu.com.cn/article/hhh495gw)）。

自然尝试让每个团大小为 $k$（最后一个团可能达不到 $k$）。

这容易做到。

我们考虑一个正方形，其对角顶点的曼哈顿距离为定值。

只需让其他点被这个正方形包含即可。

把正方形的一条对角线垂直水平方向，定值取 $m$，让剩下的点在正方形的一组对边上即可。

具体地，对于编号在 $[l,l+k)$ 中的点，取 $mid = l + \frac k2$，按 $mid, mid-1, \dots, l, l+k-1, l+k-2, \dots, mid+1$ 的顺序降序放置 $[l,l+k)$ 即可。

```cpp
il void Solve()
{
  int n,k;rd(n),rd(k);
  ve<int>a(n),c(n);
  int ans=0;
  for(int l=0;l<n;l+=k) {
    int r=min(n,l+k),mid=l+r>>1,t=r;
    // [l,mid] (mid,r)
    for(int i=mid;i>=l;--i) a[i]=--t;
    for(int i=r-1;i>mid;--i) a[i]=--t;
    ans++;
  }
  for(int x:a) wrt(x+1,' ');
  wrt('\n',ans,'\n');
  for(int i=0;i<n;++i) wrt(i/k+1," \n"[i==n-1]);
  return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1948/submission/255045415)

---

## 作者：Drind (赞：4)

> This affected only 18 people. Unfortunately, you are one of them.
>
> 由于 checker 出锅导致我晚了半个小时才发现我的程序写挂了一个很弱智的问题。

### 题目解析

给定 $n$ 个点，需要给每个点一个互不相等的权值 $a$，对于数对 $(i,j)$，如果 $|i-j|+|a_i-a_j|\le k$ 就在 $i,j$ 点之间连边，求构造一种方案使得将图划分成若干个子图后，每个子图均为完全图且子图数量最少。

首先我们发现 $m$ 点的完全图，赋值之后这个 $|i-j|+|a_i-a_j|$ 最大只会是 $m$，构造方法是对于前 $\left\lfloor\frac{m}{2}\right\rfloor$ 的点，他们的权值是编号加 $\left\lceil\frac{m}{2}\right\rceil$，后一半的点权值就是他们的编号减去 $\left\lfloor\frac{m}{2}\right\rfloor$。

然后总的子图数量就是 $\left\lceil\frac{n}{k}\right\rceil$。

理论复杂度是 $O(tn)$，不知道为啥 $n$ 这么小。

upd on 2024-10-29 补充证明：

要求限制条件 $\le k$ 才能连边，所以一个团最大大小不会超过 $k$（否则 $|i-j|$ 将会大于等于 $k$，又因为 $a$ 是排列，所以两两不相等，故 $|a_i-a_j|\gt0$，所以不可能全部连边），而存在一种方案使得能构造出大小为 $k$ 的团（见上文），所以这种方案最优。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

int ans[N],bel[N];

inline void fake_main(){
	int n,k; cin>>n>>k; int tot=1;
	for(int i=1;i<=n;i+=k){
		int ed=min(n,i+k-1);
		int len=ed-i+1;
		for(int j=i;j<=i+len/2-1;j++){
			ans[j]=j+(len+1)/2;
			bel[j]=tot;
		}
		for(int j=i+len/2;j<=ed;j++){
			ans[j]=j-len/2;
			bel[j]=tot;
		}
		tot++;
	}
	
	for(int i=1;i<=n;i++) cout<<ans[i]<<" "; cout<<"\n";
	cout<<tot-1<<"\n";
	for(int i=1;i<=n;i++) cout<<bel[i]<<" "; cout<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：唐一文 (赞：2)

这么容易想到的构造赛时竟然不会，唐完了。

首先有一个想法就是，把编号连续的一些点划分到一个团里，会比不连续的划分更优。

对于每一段划分都可以看作一个独立的问题。现在要考虑的就是，对于一个长度为 $m$ 的段，是否存在一种分配权值的方案，使得代价不超过 $k$。

那么可以考虑求，对于一个长度为 $m$ 的段，它的代价最小可以到多少。

首先这个代价的下界为 $m$。考虑 $1$ 和 $m$ 这两个点，$m-1+|p_1-p_m|\ge m$。接下来，我们通过构造，来证明这个下界一定可以取到。

首先 $p_1=v,p_m=v-1$，然后 $p_2=v+1,p_{m-1}=v-2$；接着 $p_3=v+2,p_{m-2}=v-3$，一直这样推下去。取 $v=\lfloor\frac{m}{2}\rfloor+1$，这样构造就可以保证任意两点 $i,j$ 满足 $|i-j|+|p_i-p_j|\leq m$。

也就是说，代价不超过 $k$ 可以构造出一个大小为 $k$ 的团。将 $n$ 按 $k$ 分成 $\lceil\frac{n}{k}\rceil$ 段，每段这样构造就行了。

按写法的不同，对于奇数最中间那个点的取值可能需要特判一下。[code](https://codeforces.com/contest/1948/submission/251932077)

---

## 作者：Jerrycyx (赞：1)

首先，观察到题目中两点连边的条件为 $\lvert i-j \rvert + \lvert a_i-a_j \rvert \le k$，与曼哈顿距离的定义式 $d = \lvert x_a-x_b \rvert + \lvert y_a-y_b \rvert$ 很像，所以可以考虑将题目条件转换成坐标系中的曼哈顿距离（其实双绝对值转曼哈顿距离是数学里的常用技巧吧）。

那么，建立平面直角坐标系，对于每一个点，以下标 $i$ 作为横坐标，以 $a_i$ 作为纵坐标，就可以将这 $n$ 个点转化成坐标系中的 $n$ 个坐标。

接着，根据曼哈顿距离的性质，与坐标 $(x,y)$ 距离小于等于 $k$ 的点构成一个菱形（斜 $45\degree$ 的正方形），如下（与坐标 $(7,6)$ 距离小于等于 $5$ 的点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/k2hzntwi.png)

其次，要使一块区域每一个点都可以这样覆盖其它所有点，这些点就必须保证都在以下黑色区域内：

![](https://cdn.luogu.com.cn/upload/image_hosting/uqlndaik.png)

黑色区域就是能互相形成团的坐标范围，在这个区域内所有的点都可以构成同一个团，所以我们只需在这个区域内填入尽量多的点使所有点的横纵坐标均不同。

这个区域的对角线长度是 $k$ 且对角线是水平或竖直的，且在满足上述条件时最多放 $k$ 个点，这是其中一种放置方式（图形位置略有移动，紫色“×”代表放置点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/2rt13rjt.png)

（放置方式多种多样，只要保证区域内点的横纵坐标均不相同即可。）

这样，将点每连续 $k$ 个分为一组，像这样依次填入就可以了。

时间复杂度 $O(N)$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=45;
int ans[N],bel[N];

int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		int n,k; scanf("%d%d",&n,&k);
		int idx=0,part=0;
		for(int l=1;l<=n;l+=k)
		{
			part++;
			int r=min(n,l+k-1);
			int mid=l+r>>1;
			for(int i=mid+1;i<=r;i++)
				ans[i]=++idx,bel[i]=part;
			for(int i=l;i<=mid;i++)
				ans[i]=++idx,bel[i]=part;
		}
		for(int i=1;i<=n;i++)
			printf("%d ",ans[i]);
		putchar('\n');
		printf("%d\n",part);
		for(int i=1;i<=n;i++)
			printf("%d ",bel[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：yangshengyu0719 (赞：1)

## 思路
首先在理论上，在 $i \ne j$ 且 $i$ 固定的前提下，对于数对 $(i,j)$ 有 $|i-j| \ge 1$，因为 $|i-j|+|a_i-a_j| \le k$，所以 $|a_i-a_j|$ 有 $k-1$ 种值。换句话说，加上 $i$ 本身，我们是可以每 $k$ 个连续点构成一个完全图的。

有了这个性质，我们开始尝试构造一个由 $1$ 至 $k$ 构成的符合要求的完全图，例如：  
* 当 $k=1$ 时，$a$ 数组可以为 $1$；  
* 当 $k=2$ 时，$a$ 数组可以为 $1,2$；  
* 当 $k=3$ 时，$a$ 数组可以为 $1,3,2$；  
* 当 $k=4$ 时，$a$ 数组可以为 $2,1,4,3$；  
* 当 $k=5$ 时，$a$ 数组可以为 $2,1,5,4,3$。 

由此我们发现：  
* 当 $i<⌊\frac{k}{2}⌋$ 时，$a_i=⌊\frac{k}{2}⌋-i$；  
* 而当 $k$ 为奇数，$i>⌈\frac{k}{2}⌉$ 时，$a_i=k-a_{k-i+1}$；  
	特殊地，当 $i=⌊\frac{k}{2}⌋$ 时，$a_i=k$；  
* 当 $k$ 为偶数，$i>⌈\frac{k}{2}⌉$ 时，$a_i=k+1-a_{k-i+1}$；

但在分完 $⌊\frac{n}{k}⌋ \times k$ 个完全图后，可能剩下一些点。不过这很简单就能解决，我们直接再构造一种由剩下点组成的符合题意的新完全图即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100;
int T,n,k,b[N],bl[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) bl[i]=(i-1)/k+1;//分组
		
		int lst=n/k*k,kk=n-lst;//k个一组的完全图
		for(int i=0;i<k/2;i++) b[i]=k/2-i,b[k-i-1]=(k&1?k:k+1)-b[i];
		if(k&1) b[k/2]=k;
		for(int i=1;i<=lst;i++) cout<<b[(i-1)%k]+(bl[i]-1)*k<<' ';
			
		for(int i=0;i<kk/2;i++) b[i]=kk/2-i,b[kk-i-1]=(kk&1?kk:kk+1)-b[i];//剩下的再构成另一种
		if(kk&1) b[kk/2]=kk;
		for(int i=0;i<kk;i++) cout<<b[i]+bl[lst]*k<<' ';

		cout<<'\n'<<ceil(n*1.0/k)<<'\n';
		
		for(int i=1;i<=n;i++) cout<<bl[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Wei_Han (赞：1)

直接贪心，考虑到 $|i-j|+|a_i-a_j| \leq k$，使得序列上一段（一个子图）的差值都基本为 $k$，就能做到最优，分段考虑。

显然，按照上述构造，一段序列的长度为 $k$，那么划分出的子图数量最小为 $\left \lceil \frac{n}{k} \right \rceil$。在一段序列中（以 $1$ 到 $k$ 举例），一种构造方法为，前 $\frac{k}{2}$ 个数，从 $\frac{k}{2}$ 到 $1$ 降序排列，第 $\frac{k}{2}+1$ 到第 $k$ 个数从 $k$ 到 $\frac{k}{2}+1$ 降序排列，举个例子，当 $k=5$ 时，构造序列为 $3,2,1,5,4$。对于第一位和最后一位，差值为 $|\frac{k}{2}-\frac{k}{2}-1|+|k-1| = k$，对于第 $\frac{k}{2}$ 和第 $\frac{k}{2}+1$ 位，差值为 $|1-k|+|\frac{k}{2}+1-\frac{k}{2}|=k$ 结果均不超过 $k$，对于其他位置也相同。

时间复杂度 $O(tn)$。
### Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
#define min(a,b) (a>b?b:a)
#define bug(x,y) (x<1||y<1||x>15||y>15)
using namespace std;
typedef long long ll;
typedef double db;
const int N=5e6+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,a[N],b[N],k;
inline void solve(){
	ll now=1,op=0,limit=ceil(1.0*n/k);
	fo(1,i,limit){
		op+=k;
		ll lim=op-k/2;
		Fo(min(n,lim),i,op-k+1) wr(i),pp;
		Fo(min(n,op),i,lim+1) wr(i),pp;
	}pr;wr(limit),pr;
	fo(1,i,n/k) fo(1,j,k) wr(i),pp;
	fo(n/k*k+1,i,n) wr(n/k+1),pp;pr;	
}
signed main(){
	read(t);
	while(t--){read(n),read(k);solve();}
	return 0;
}
``````

---

