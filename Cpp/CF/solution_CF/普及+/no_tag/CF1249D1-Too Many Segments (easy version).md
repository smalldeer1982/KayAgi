# Too Many Segments (easy version)

## 题目描述

简单难度与困难难度的唯一差别是$n,k$的范围

给予$n$条线段，这些线段可以有重叠部分甚至完全重叠在一起。第$i$条线段$[l_i,r_i](l_i≤r_i)$覆盖了所有整数点$j$满足$l_i≤j≤r_i$

如果一个整数点被**超过**$k$条线段覆盖，那么就称之为bad point（下文以坏点代替）

你的任务是去掉最少的线段使得没有坏点的存在

## 样例 #1

### 输入

```
7 2
11 11
9 11
7 8
8 9
7 8
9 11
7 9
```

### 输出

```
3
1 4 7 
```

## 样例 #2

### 输入

```
5 1
29 30
30 30
29 29
28 30
30 30
```

### 输出

```
3
1 2 4 
```

## 样例 #3

### 输入

```
6 1
2 3
3 3
2 3
2 2
2 3
2 3
```

### 输出

```
4
1 3 5 6 
```

# 题解

## 作者：一铭君一 (赞：7)

# CF1249D1

## 题目描述

用 $n$ 条线段覆盖一个数轴。要求删除最少的线段，使得数轴上每个点都被覆盖不超过 $k$ 次。

## Solution

多一句嘴：贪心题不给证明的题解都是流氓题解。

拿到题先看数据范围，因为这可以告诉你你的算法大概的时间复杂度。这题的数据范围只有 200 ，那就说明 $O(n^3)$ 以下是稳过的。

先找出哪些点是“坏点”，然后考虑对覆盖这些点的线段进行删除。

从极端情况开始考虑。最坏情况下，每次删除一个线段，只能让一个“坏点”的被覆盖次数减少一次，设这个最坏删除次数为 $a$ 。

那么什么情况能导致 $a$ 变小呢？如果一个线段覆盖了 $b$ 个“坏点”，删除这个线段就让 $b$ 个“坏点”的覆盖次数减少一次，那么答案上界就变成了 $a-b$ 。所以我们在选择时，应该尽可能选择那些 $b$ 更大的线段。

从最原始状态开始考虑。假设我们还没有进行过删除操作，扫描数轴，找到**第一个**“坏点”，记为 $P$ 点（ $P$ 点之前的点一定不是“坏点”）。

如果 $P$ 点被覆盖了 $m$ 次，那么我们至少要删除 $m-k$ 条线段，才能让 $P$ 点合法。

假设覆盖 $P$ 的线段为 $S_1[l_1,r_1]...S_m[l_m,r_m]$ ，一共 $m$ 条。那么这些线段都可以分为两段：$[l_i,P_x-1]$ 和 $[P_x,r_i]$ 。

因为 $P$ 之前的点都不是“坏点”，那么线段 $[l_i,P_x-1]$ 覆盖了 0 个“坏点”（$b=0$），也就是删除这些线段对 $a$ 没有影响。

$P$ 右侧的点中，有可能有“坏点”，那么 $[P_x,r_i]$ 的 $b\geq 0$ 。如果我们把这些线段按照 $b$ 从大到小排序，一定删除 $b$ 最大的 $m-k$ 条线段更优。

假设一个“坏点”的坐标为 $y$ ，那么它对线段 $S_i$ 的 $b$ 有贡献，当且仅当 $y\in S_i$ 。设两条线段 $S_1([P_x,r_1]),S_2([P_x,r_2])$ ，其中 $r_1<r_2$ 。那么有 $S_1\subseteq S_2$ ，此时一定存在至少一个坐标 $y$ ,使得 $y\in S_2$ 且 $y\notin S_1$ 。如果坐标 $y$ 对应的点 $Q$ 恰好是“坏点”，那么 $S_1$ 的 $b$ 一定小于 $S_2$ 的 $b$ 。

综上，当一些线段左对齐时，有 $r_i<r_j\rightarrow b_i\leq b_j$ 。

那么显然，如果要使 $P$ 不是“坏点”，最优的方案是删除在 $P$ 右侧长度最长的 $m-k$ 条线段。

继续推广，假设我们完成了第一次删除，把 $P$ 变得合法了。此时继续向后扫描，如果又找到一个“坏点”，是不是相当于“之前没有进行过删除操作”（这个“坏点”前面的点都合法）？那么归纳法，可以把这个新找到的“坏点”看成 $P$ ，上面的结论依然成立。

综上所述，我们的做法应该是：

* 从头扫描数轴上所有点

* 找到一个“坏点”之后，扫描覆盖了这个“坏点”的所有线段。

* 不断删除在这个“坏点”右侧长度最长的线段，直到这个“坏点”合法。

当扫描到数轴结尾时，得到答案。

## $\text{Talk is easy,show me the code.}$

```cpp
//因为我整了个缺省源，头文件比较长，这里省略了，只给出核心代码。
struct Node{
  int l,r,org;
};

struct Node segments[maxn];
inline bool operator < (const Node a,const Node b){
  return a.r<b.r;
}//为了方便，按右端点递增排个序

inline bool inrange(const int i,const int x){
  return (segments[i].l<=x)&&(x<=segments[i].r);
}//判断一个点是不是被第i条线段覆盖

signed main(){
  read(n),read(k);
  for(int i=1,l,r;i<=n;++i){
    read(segments[i].l),read(segments[i].r),segments[i].org=i;
    for(int j=segments[i].l;j<=segments[i].r;++j)
      ++A[j];
  }
  std::sort(segments+1,segments+1+n);
  for(int i=1;i<=200;++i){//枚举每一个点
    while(A[i]>k){//如果是坏点
      for(int j=n;j>0;--j)//从结尾开始枚举线段j(排序之后右端点递减，找到的第一个就是在坏点右侧最长的线段)
        if(inrange(j,i) && !vis[j]){//线段j覆盖了这个坏点，并且还没有被删除
          for(int q=segments[j].l;q<=segments[j].r;++q)//删掉这个线段
            A[q]--;
          vis[j]=1;//标记已删除
          ++ans;
          break;
        }
    }
  }
  write(ans);
  putchar('\n');
  for(int i=1;i<=n;++i)
    if(vis[i]) write(segments[i].org),putchar(' ');
  return 0;
}

```

---

## 作者：Lucifer_Bartholomew (赞：2)

# 暴力+贪心
直接暴力维护扫描1~2e5的坐标段,为了有序处理每一段区间,用一个set按照区间右端点为排序关键字维护。

对于每一段区间,在扫到${l_i}$坐标时将其加入set,在扫到${r_i}+1$的坐标时将其弹出。

因为为了保证不超过k段的约束,需要再弹出一些区间。而取长的区间一定不会比取短的区间更优(长区间的后效性更久),所以可以一直弹出最末一段区间直到set中所存区间数量小于等于k。

```cpp
#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int l[200001],r[200001];
vector<pair<int,int> > pos[200001];
int main()
{
    int n=read(),k=read();
    for(int i=1;i<=n;++i)
    {
    	l[i]=read();
        r[i]=read();
    	pos[l[i]].push_back(make_pair(r[i],i));
    }
    vector<int> ans;
    set<pair<int,int> > s;
    for(int i=1;i<200001;++i)
    {
    	for(int j=0;j<pos[i].size();++j)
    		s.insert(pos[i][j]);
    	while(!s.empty()&&s.begin()->first<i)s.erase(s.begin());
    	while(s.size()>k)
        {
    		set<pair<int,int> >::iterator it=s.end();
            it--;
    		ans.push_back(it->second);
    		s.erase(it);
    	}
    }
    printf("%d\n",ans.size());
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();++i)
    	printf("%d ",ans[i]);
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：Handezheng (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1249D1)
## 前言:
[前置芝士](https://oi-wiki.org/basic/greedy/)

做完的可以去做 [CF1249D1 Too Many Segments (hard version)](https://www.luogu.com.cn/problem/CF1249D2)，它是本题的加强版，我在本题中思路的实现和代码均是参考它的数据范围的。

## 思路
题目要求我们删除一部分线段使得没有“坏点”的存在，那我们肯定要遍历一遍区间，找到哪个点是“坏点”后，才能进行操作。  

当我们枚举到一个点时，如果这个点是“坏点”，**那它肯定被多条线段所覆盖**，枚举到这个点时，它前面的点一定都不是“坏点”（本来就不是“坏点”或**在前面已经删掉一些线段使它不是“坏点”**）。  
那么当前覆盖这个点的线段的**左端点对其毫无用处**，无论删除多少条线段都不会改变这个点左面所有点是不是“坏点”，那我们可以关注**右端点**：

**贪心地想**，一条线段的右端点越“远”，那它就对更多的点有影响（贡献越大）。  
所以，我们应该尽量删除**右端点更靠右的线段**。

## 细节及实现
### 实现
- 数据范围：$n \le  200$ 并且 $l,r\le 200$，我们遍历区间所有点只需要花费 $O(r_{max})$ 的时间复杂度，所以就可以再花费 $O(n)$ 的复杂度来枚举所有线段了。  
但对于[加强版](https://www.luogu.com.cn/problem/CF1249D2)，有 $n \le 2\cdot10^5$ 且 $l,r\le 2\cdot10^5$，明显上述做法的时间会爆掉。

- 考虑优化。我们可以用一个数据结构来存储覆盖到当前点的线段，考虑到要需要用**排序**维护右端点更靠右，最好用 `priority_queue` 或 `set`（我个人推荐用 `set`,因为 `priority_queue` 仅支持 `priority_queue.top()` 的删除）。

- 遍历到一个点时，可能会有多条线段以它为左端点，所以我们可以用**二维的** `vector` 来存储线段的有关信息。

### 细节
- 题目要求输出线段的编号，所以我们的 `set` 和 `vector`  都是**结构体**，包括线段右端点和线段编号。
- 在遍历到一个新的点时，我们要把右端点小于当前点的线段删掉（容易想到这样的点已经“过期”了，对后续操作无用）。
- 我们在删除线段时仅保证右端点尽量大，不保证它的编号是升序的，所以要对 $ans$ 数组进行**排序**（以编号为关键字）。
- ~~感谢 STL 库~~ `set` 中有一个不常用的功能：`set.rbegin()` 指 `set.end()` 的前一个位置，在本题中就是右端点最大点所在的位置。
- `set.begin()`，`set.rbegin()` 等返回的都是元素所在的位置，使用时应加上符号“*”。
## AC code
~~应该有部分读者最喜欢看这个，所以把它安排在最后~~


这份代码在 [加强版](https://www.luogu.com.cn/problem/CF1249D2) 中也是可以 [通过](https://www.luogu.com.cn/record/161986221) 的。~~双倍经验~~
```cpp
#include<bits/stdc++.h>
#include<vector>
#include<set>
using namespace std;
#define int long long
#define re register
#define F(j,i,n)  for(re int i = j;i <= n;i++)
const int N = 2e5 + 50,M = 1e3 + 50;
inline void read(int &x){
	re int f = 1;x = 0;
	re char s = getchar();
	while(s < '0' || s > '9'){
		if(s == '-') f = -1;
		s = getchar();
	}while(s >= '0' && s <= '9')
		x = x * 10 + s - '0',s = getchar();
	x *= f;
}

int n,k;
int tot;//被删除线段的数量 
struct node{
	int r,id;
	//r记录区间的右端点
	//id记录当前区间的编号
}ans[N];//被删除线段的编号 
inline bool operator < (node a,node b){
	if(a.r == b.r) return a.id < b.id;
	return a.r < b.r;
	//以右端点为关键字
}
inline bool cmp(node a,node b){
	return a.id < b.id;
	//以编号为关键字升序排序
}
vector <node> a[N];
//a[l]记录以l为左端点的线段的相关信息 
set <node> st;
//set记录覆盖到当前点的线段 

signed main(){
	
	read(n),read(k);
	int l,r;
	node tmp;
	F(1,i,n){
		read(l),read(r);
		tmp.r = r,tmp.id = i;
		a[l].push_back(tmp);
	}
	
	F(1,i,200000){
		while(st.size() && (*st.begin()).r < i){//区间的右端点小于当前点，说明这个区间已"过期"
			st.erase(*st.begin());
		}//删除"过期"的区间
		
		for(int j = 0;j < a[i].size();j ++){
			st.insert(a[i][j]);
		}//把以当前遍历到的点为左端点的区间插入至set
		
		while(st.size() > k){//如果这个点是坏点
			ans[++ tot] = *st.rbegin();//记录要被删除的区间
			st.erase(*st.rbegin());//删除区间
		}
	}
	printf("%lld\n",tot);
	sort(ans + 1,ans + tot + 1,cmp);
	F(1,i,tot) printf("%lld ",ans[i].id);
	
	return 0;
}
``````
## 最后
如果有代码、思路问题，错别字问题及其他问题欢迎私聊

---

## 作者：Daniel_yao (赞：1)


## 题目大意

数轴上有 $n$ 条线段，现在要求数轴上的点不能存在超过 $k$ 条线段覆盖它，如果存在超过的情况，求删除最少的线段数量以及所删除线段的编号。$(n\le200000)$

## 思路

1.思路一： 暴力

暴力枚举每一个线段，再暴力扫一遍数轴上的点，记录一下有多少条线段覆盖了该点，如果该点被超过 $k$ 个线段所覆盖，那么，将右端点最靠右的线段删除，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lnob6xkn.png)

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 205;
struct Node{
  int l, r, i;
}a[N];
int n, k, sum[N], s[N], tot;

bool cmp(Node x, Node y){
  if(x.r == y.r) return x.l < y.l;
  return x.r < y.r;
}

int main(){
  cin >> n >> k;     
  for(int i = 1;i <= n;i++){
    cin >> a[i].l >> a[i].r;//左右端点
    a[i].i = i;
  }
  sort(a + 1, a + n + 1, cmp);//按右端点从小到大排序
  for(int i = 1;i <= n;i++){
    for(int j = a[i].l;j <= a[i].r;j++){//枚举线段所覆盖的端点
      sum[j]++;
      if(sum[j] > k){//该点被超过 k 个线段所覆盖
        s[++tot] = a[i].i;//将右端点最靠右的线段删除
        break;
      }
    }
  }
  cout << tot << '\n';
  for(int i = 1;i <= tot;i++){
    cout << s[i] << ' ';//输出
  }
  return 0;
}
```
2.思路二： **优化**暴力

看一眼 $n$ 的范围，直接懵比，看来要上 $O(n\log n)$ 级别的数据结构优化了。

不难发现，所有的操作都是建立在右端点有序的情况下才进行的。所以，我们可以维护一个有序集合，将右端点放进有序集合中，在从左到右枚举左端点，枚举左端点的同时判断当前左端点所对应的点是否被超过 $k$ 个线段所覆盖。操作同
思路一。

我们还可以在此基础上加一个优化：每个线段都是有“时效性”的。当所枚举的左端点大于有序集合内某一个线段的右端点，说明该线段“过期了”，不会再影响到之后的结果。这是，我们可以直接删除此线段。

## AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
struct Node{
  int r, id;
}a[N];
int n, k, h[N], tot;
set<Node> s;
vector<Node> v[N];

bool operator < (Node x, Node y){
  if(x.r == y.r) return x.id < y.id;
  return x.r < y.r;
}

int main(){
  cin >> n >> k;
  for(int i = 1;i <= n;i++){
    int a1, b1;
    Node c;
    cin >> a1 >> b1;
    c.id = i;
    c.r = b1;
    v[a1].push_back(c);
  }
  for(int i = 1;i < N;i++){
    while(s.size() && (*s.begin()).r < i){//“过期了”直接删除
      s.erase(*s.begin());
    }
    for(int j = 0;j < v[i].size();j++){
      s.insert(v[i][j]);
    }
    while(s.size() > k){//该点被超过 k 个线段所覆盖
      a[++tot] = *s.rbegin();
      s.erase(*s.rbegin());//将右端点最靠右的线段删除
    }
  }
  cout << tot << '\n';
  for(int i = 1;i <= tot;i++){
    cout << a[i].id << ' ';
  }
  return 0;//完结撒花
}
```
~~安利下自己的[博客](https://yzy001633.blog.luogu.org/)，逃！~~

## end

---

## 作者：JWRuixi (赞：0)

~~我不会用 set~~

- 题意

不多赘述，咱直接上正题。

- 分析

不难发现这是道贪心，我怎么知道的？直接看 CF 上的 tag 即可。

怎么贪心？考虑一下，对于一个坏点，显然要删除的线段的数量是不可能变的，那么的话是不是删除越长的越好？显然跟长的线段自然能覆盖到更多的点。

所以对于每一个点，先用 vector 维护要插入的点，再将 set 中右端点在当前点之前的给干掉，这些要删的点显然在 set 的最前面，最后在 set 的元素数量大于 $k$ 时，不断去掉末尾元素即可。

分析一下复杂度，维护一个以右端点为关键值的 set 是 $O(\log n)$ 的，枚举每一个点是 $O(m)$，$m$ 为线段覆盖到的区间长度，同阶与 $n$。所以总复杂度差不多是 $O(n\log n)$，那不直接冲过去！

- 小清新 code

```cpp
#include <bits/stdc++.h>
#define mp make_pair
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 2e5 + 500;

struct node {
	int l, r;
} a[maxn];

int n, k, m, ans[maxn];
set < pair<int, int> > st;
vector <int> ev[maxn];

int main () {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) a[i] = {read(), read()};
	for (int i = 1; i <= n; i++) ev[a[i].l].push_back(i);
	for (int i = 1; i < maxn; i++) {
		for (auto u : ev[i]) st.insert(mp(a[u].r, u));
		while (!st.empty() && (*st.begin()).first < i) st.erase(st.begin());
		while (st.size() > k) {
			ans[++m] = (*prev(st.end())).second;
			st.erase(prev(st.end()));
		}
	}
	write(m), putchar('\n');
	for (int i = 1; i <= m; i++) write(ans[i]), putchar(' ');
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定 $n$ 个区间，要求删除最少数量的区间，使得每个点被覆盖的次数不超过 $k$，求方案。

**解题思路**

前缀和、差分、优先队列、贪心。

我们首先要做的事情就是能够计算出当前点 $x$ 处被几条线段覆盖的问题。我们需要先将所有线段按左端点排序，用差分维护线段结束，然后枚举每条线段，每枚举一个线段我们就让 $cnt+1$， 表示当前点 `a[i].l` 有 $cnt$ 个线段覆盖，同时 `sum[a[i].r]--`，表示线段在 `a[i].r` 在这里结束。还没完，我们在判断当前点 `a[i].l` 被几条线段覆盖时，还需要去掉右端点已经小于 `a[i].l` 的线段，这样就得到了当前点 `a[i].l` 有 $cnt$ 个线段覆盖。然后判断 $cnt>k$，如果 $cnt>k$ 说明需要去掉线段，我们优先去掉右端点最大的线段。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int n, k;
int sum[200005], cnt, pos;
vector<int> ans;
priority_queue<pair<int, int> > p;
struct node {
    int l, r, id;
} a[200005];
bool cmp(node x, node y) {
    if(x.l == y.l) {
        return x.r > y.r;
    }
    return x.l < y.l;
}
int main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    for(int i = 1; i <= n; i++) {
        p.push(make_pair(a[i].r, a[i].id));
        cnt++;
        sum[a[i].r]--;
        while(pos < a[i].l) {
            cnt = cnt + sum[pos];
            pos++;
        }
        if(a[i].l != a[i + 1].l) {
            while(cnt > k) {
                while(!p.empty() && p.top().first < a[i].l) {
                    p.pop();
                }
                ans.push_back(p.top().second);
                sum[p.top().first]++;
                p.pop();
                cnt--;
            }
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;
}
```

---

