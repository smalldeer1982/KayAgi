# Phoenix and Memory

## 题目描述

拍照啦！拍照啦！菲尼克斯有 $n$ 个朋友，朋友们的编号是$1$ ~ $n$。他的朋友们本来按某种特殊顺序排成一排，但菲尼克斯还没来得及按下快门，就有一只鸭子乱入，把原本排好的顺序搞得乱七八糟。

现在，菲尼克斯不得不重新排好顺序，但他记不清了QAQ！他只记得从左数起的第$i$个朋友的编号大小在 $a_i$ 和 $b_i$ 之间。该怎么办？他只好向你请教。请问根据他的记忆有没有唯一一种方法给他的朋友们排序？

**一句话题意**：问是否存在**唯一**一个 $1$ ~ $n$ 的排列 $c$ ，满足 $a_i \leq c_i \leq b_i$ 。

## 样例 #1

### 输入

```
4
4 4
1 3
2 4
3 4```

### 输出

```
YES
4 1 2 3```

## 样例 #2

### 输入

```
4
1 3
2 4
3 4
2 3```

### 输出

```
NO
1 3 4 2 
1 2 4 3```

# 题解

## 作者：wsyhb (赞：10)

## 题意简述

问是否存在**唯一**的长度为 $n$ 的排列 $p$，满足 $a_i \le p_i \le b_i \; (1 \le i \le n)$。

**数据保证至少存在一个符合题意的排列。**

如果唯一，输出这个排列；否则输出**任意两种**不同的满足题意的排列。

**数据范围**：$1 \le n \le 2 \times 10^5$

## 分析 + 题解

首先考虑如何求出一个可行的排列。

事实上，这可以**转化为一个简单的贪心问题**—— 

$n$ 个点与 $n$ 条线段匹配，从左往右第 $i$ 个点与第 $j$ 条线段匹配的条件为这个点位于该线段上（即 $a_j \le i \le b_j$）。

具体实现可以**把线段按左端点排序**，然后从小到大枚举 $i$，对于每个 $i$，先将左端点为 $i$ 的线段丢进堆（优先队列）里，然后从中**取出右端点最小的线段**，与 $i$ 号点匹配即可。

由于我们在讨论 $i$ 号点之前，所有包含 $i$ 号点且未匹配的线段均在堆中，因此我们贪心选取其中右端点最小的策略是正确的。

（右端点越靠右，这条线段就有越多的选择的机会）

那么如何求出另外一个满足题意的排列呢？（或者发现无解）


------------


引理：**若存在另外一个满足题意的排列，我们一定可以通过交换已知排列中的其中两个数来转化成它。**

证明：

在上述条件下，必然存在一个长度 $\ge 2$ 的循环。（这是修改排列以保证仍然满足题意的充要条件）接下来让我们证明必然存在一个长度 $=2$ 的循环。

假设不存在长度 $=2$ 的循环，则必然存在一个**最短的**长度 $\ge 3$ 的循环。

设 $y$ 为这个循环中最左边的一个点，$x$ 是 $y$ 的前驱，$z$ 是 $y$ 的后继（即 $y$ 可以改为匹配 $x$ 当前对应的线段，$z$ 可以改为匹配 $y$ 当前对应的线段），如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/3teeb84e.png)

请注意 $y$ 当前对应线段的右端点一定在 $x$ 左侧，否则 $x$ 和 $y$ 就会形成一个长度为 $2$ 的循环。

而我们可以发现，此时移除 $y$ 没有任何影响，因为 $z$ 可以改为匹配 $x$ 当前对应的线段。于是我们可以获得一个更小的环，这与假设矛盾，故引理成立。


------------


于是我们只需要求出需要交换的 $p_i$ 和 $p_j$，以满足 $a_i \le p_j \le b_i$，且 $a_j \le p_i \le b_j$。

不妨设 $p_i < p_j$，则条件转化为 $a_j \le p_i < p_j \le b_i$。枚举 $i$，发现只需查询是否存在 $j$ 满足 $a_j \le p_i$（$p_i$ 为定值）且 $p_i < p_j \le b_i$（$p_i,b_i$ 为定值）。

我们设 $id$ 为 $p$ 的逆映射，即 $id_{p_i}=i$，将 $i$ 的枚举顺序改为 $id_1$，$id_2$，$\cdots$，$id_n$，每次先把 $a_j=p_i$ 的 $j$ 对应的 $p_j$ 扔进 set，然后查询 set 中是否存在值 $\in (p_i,b_i]$，二分查找即可。

## 代码

查询方法见注释。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=2e5+5;
struct node
{
	int a,b,id;
}c[max_n];
vector<node> v[max_n];
inline bool operator > (const node &x,const node &y)//重载运算符以在小根堆中比较 
{
	return x.b>y.b;
}
priority_queue<node,vector<node>,greater<node> > q;
int p[max_n],id[max_n];
set<int> s;
set<int>::iterator it;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&c[i].a,&c[i].b);
		c[i].id=i;
		v[c[i].a].push_back(c[i]);//把 c[i] 丢进左端点编号对应的 vector 中 
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<int(v[i].size());++j)
			q.push(v[i][j]);//先加入 
		id[i]=q.top().id;//再取出 
		p[id[i]]=i;
		q.pop();
	}
	for(int x=1;x<=n;++x)
	{
		for(int j=0;j<int(v[x].size());++j)
			s.insert(p[v[x][j].id]);//先加入 
		int i=id[x];//枚举 x 获得对应 i 
		it=s.upper_bound(x);//再查询
		if(it!=s.end()&&*it<=c[i].b)
		{
			int j=id[*it];
			puts("NO");
			for(int k=1;k<=n;++k)
				printf("%d%c",p[k],k<n?' ':'\n');
			swap(p[i],p[j]);
			for(int k=1;k<=n;++k)
				printf("%d%c",p[k],k<n?' ':'\n');
			return 0;
		}//查询方法：二分找到大于 p[i] 的第一个数，判断其是否小于等于 b[i] 
	}
	puts("YES");
	for(int k=1;k<=n;++k)
		printf("%d%c",p[k],k<n?' ':'\n');
	return 0;
}
```

---

## 作者：ix35 (赞：4)

首先考虑如何构造一组可行解。

考虑 $i$ 的位置，设为 $p$，那么我们从小到大枚举 $i$，然后只考虑所有 $l_p\leq i$ 且未被其他值占用的位置 $p$，从中选出右端点最小的一个 $p$ 作为 $i$ 的位置即可（一定满足条件，否则就说明不存在合法排列，与题目矛盾）。

再考虑能否构造出另一组解，容易发现只需考虑对排列进行一次对换后得到的排列能否满足要求即可。

枚举对换中较大的数 $j$，用一个 set 维护所有满足 $r_{pos_i}\ge j$ 的 $i$，考虑 set 中所有元素的最大值 $x$，如果 $x\ge l_j$，那么交换 $x,j$ 后就可以满足条件。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=200010;
struct P {
	int l,r,id;
}p[MAXN];
struct cmp {
	bool operator () (P a,P b) {return a.r>b.r;}
};
int n,a[MAXN],b[MAXN],xl[MAXN],xr[MAXN],rev[MAXN];
bool cmp1 (P a,P b) {return a.l<b.l;}
bool cmp2 (P a,P b) {return a.r>b.r;}
priority_queue <P,vector<P>,cmp> q,q2;
multiset <int> ms;
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&p[i].l,&p[i].r);
		p[i].id=i;
	}
	multiset<int>::iterator it;
	sort(p+1,p+n+1,cmp1);
	int cur=1,flg=0;
	for (int i=1;i<=n;i++) {
		while (cur<=n&&p[cur].l<=i) {
			q.push(p[cur]);
			cur++;
		}
		P tmp=q.top();
		q.pop();
		a[tmp.id]=b[tmp.id]=i,xl[tmp.id]=tmp.l,xr[tmp.id]=tmp.r,rev[i]=tmp.id;
		q2.push(tmp);
		while (!q2.empty()&&q2.top().r<i) {
			P tmp2=q2.top();
			q2.pop();
			it=ms.find(a[tmp2.id]);
			ms.erase(it);
		}
		if (!ms.empty()&&!flg) {
			it=ms.end();
			it--;
			if (*it>=tmp.l) {
				flg=1;
				swap(b[tmp.id],b[rev[*it]]);
			}
		}
		ms.insert(i);
	}
	if (flg) {
		printf("NO\n");
		for (int i=1;i<=n;i++) {printf("%d ",a[i]);}
		printf("\n");
		for (int i=1;i<=n;i++) {printf("%d ",b[i]);}
		printf("\n");
	} else {
		printf("YES\n");
		for (int i=1;i<=n;i++) {printf("%d ",a[i]);}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Caro23333 (赞：1)

再多 $10$ 分钟就 ak 了 QAQ

首先我们来考虑如何构造一组可行解。

对每一个 $r$，开一个 ``` set<pair<int,int> > pos[r] ``` 来存储所有右端点为 $r$ 的区间，其中第一关键字为左端点的值。从大到小枚举 $r$ 的值，每次从 ``` pos[r] ``` 中取出左端点最大的区间，将其对应位置的答案设为 $r$ 。对于 ``` pos[r] ``` 中的其他区间，由于 $r$ 已经被占用，所以它们等价于一系列右端点为 $r-1$ 的区间，于是只要和 ``` pos[r-1] ``` 做启发式合并即可。可以证明这样一定能构造出一组解（感性理解就是，因为每次都选最大的左端点，所以剩下的区间都是尽量“宽松的”，就可以尽量构造出解）。我们称这一组解为特解。

然后考虑如何判断解的唯一性。不难发现，如果解不唯一，则一定有一组其他的解可以由交换特解中的两个元素得到。

在构造特解的过程中，假设当前 $r$ 被分配给了 $i$ 这个位置，那么考察所有 $[i+1,b_i]$ 上的 $r'$ 所对应的位置 $i'$，只要这些 $i'$ 中存在至少一个满足 $a_{i'}<r$ ，那么就说明交换特解中 $i,i'$ 位置上的元素可以得到一组新解。

不难发现我们只要求使得 $r'$ 最小的 $i'$ 即可，可以使用线段树维护。具体见代码。

总复杂度 $O(n\log^2 n)$。值得注意的是，这份代码仅有在 ``` -std=c++11 ``` 或更高时复杂度正确，因为它涉及到 ``` swap ``` 两个 ``` set ```，而在早于 C++11 的标准中这将花费 $O(size)$ 的时间。

代码:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set> 
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
const int MAXN = 200005;
inline int readint()
{
	int res = 0, f = 1;
	char c = 0;
	while(!isdigit(c))
	{
		c = getchar();
		if(c=='-')
			f = -1;
	}
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res*f;
}
int n,a[MAXN],b[MAXN],ans[MAXN];
set<pii> pos[MAXN];
set<pii>::iterator it,it1;
int x,y;
struct Node
{
	int minn;
}t[MAXN<<2];
inline void buildTree(int id, int l, int r)
{
	t[id].minn = 0;
	if(l==r)
		return;
	int mid = (l+r)>>1;
	buildTree(id<<1,l,mid);
	buildTree(id<<1|1,mid+1,r);
}
inline void modify(int id, int ql, int qr, int pos, int d)
{
	if(ql==pos&&qr==pos)
	{
		t[id].minn = d;
		return;
	}
	int mid = (ql+qr)>>1;
	if(pos<=mid)
		modify(id<<1,ql,mid,pos,d);
	else
	 	modify(id<<1|1,mid+1,qr,pos,d);
	t[id].minn = a[t[id<<1].minn]<a[t[id<<1|1].minn]?t[id<<1].minn:t[id<<1|1].minn;
}
inline int query(int id, int ql, int qr, int l, int r)
{
	if(ql==l&&qr==r)
		return t[id].minn;
	int mid = (ql+qr)>>1;
	if(r<=mid)
		return query(id<<1,ql,mid,l,r);
	else if(l>mid)
		return query(id<<1|1,mid+1,qr,l,r);
	else
	{
		int x = query(id<<1,ql,mid,l,mid), y = query(id<<1|1,mid+1,qr,mid+1,r);
		return a[x]<a[y]?x:y; 
	}
}

int main()
{
	n = readint();
	a[0] = 1<<30;
	bool flag = true;
	for(int i = 1; i<=n; i++)
		a[i] = readint(), b[i] = readint();
	for(int i = n; i>=1; i--)
	{
		pii now = mp(a[i],i);
		pos[b[i]].insert(now);
	}
	buildTree(1,1,n);
	for(int i = n; i>=1; i--)
	{
		it = pos[i].end();
		it--;
		ans[it->se] = i;
		if(i+1<=b[it->se])
		{
			int t = query(1,1,n,i+1,b[it->se]);
			if(t&&a[t]<=i)
				flag = false, x = it->se, y = t;
		}
		modify(1,1,n,i,it->se);
		pos[i].erase(it);
		if(i>1)
		{
			if(pos[i].size()>pos[i-1].size())
				swap(pos[i],pos[i-1]);
			for(it = pos[i].begin(); it!=pos[i].end(); it++)
				pos[i-1].insert(*it);
		}
		pos[i].clear();
	}
	if(flag)
	{
		cout << "YES" << endl;
		for(int i = 1; i<=n; i++)
			cout << ans[i] << " ";
		cout << endl;
	}
	else
	{
		cout << "NO" << endl;
		for(int i = 1; i<=n; i++)
			cout << ans[i] << " ";
		cout << endl;
		swap(ans[x],ans[y]);
		for(int i = 1; i<=n; i++)
			cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}

```


---

## 作者：Sai0511 (赞：1)

发个比较容易理解的题解。    
首先给出一组答案是个 common problem, 难的是判断唯一性。    
我们对所有区间按照右端点升序排序，然后依次填每个区间未被选过的最小数即可构造一组答案。   
易证正确。   
对与唯一性，我们思索一下它的条件。    
当 $l_j \leq p(i) < p(j) \leq r_i$ 时，$i$ 和 $j$ 是可以互相交换的。   
也就是这个样子：![](https://cdn.luogu.com.cn/upload/image_hosting/khfbtlbk.png)      
显然交换完之后 $j$ 满足条件，$i$ 换完之后大于当前的坐标，而因为保证了 $p(j) \leq r_i$ 所以也是符合条件的。   
于是可以转化一下问题：    
对与一个 $i$ 寻找一个可能可以交换的 $j$，也就是找到$[i+1,r_{p_i}]$ 中 $l$ 最小的值，并判断是否可以交换即可。    
显然可以用线段树解决。  
复杂度 $\mathcal{O}(n \log n)$     
```cpp
#include <bits/stdc++.h>

const int N = 2e5 + 10;
const int inf = 0x3f3f3f3f;  

int n, m, i, j, k;
int l[N], r[N];
int a[N], rev[N], pos[N], senq[N];  

struct Segment_Tree1 {
  int mn[N << 2]; 
  inline void push_up(int u) {
    mn[u] = std::min(mn[u << 1], mn[u << 1 | 1]);
  }
  void build(int l, int r, int u) {
    if (l == r) {
      mn[u] = l;
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, u << 1);
    build(mid + 1, r, u << 1 | 1);
    push_up(u);
  }
  int range_min(int ql, int qr, int l, int r, int u) {
    //printf("%d %d %d %d %d\n", ql, qr, l, r, u);   
    if (ql <= l && r <= qr) {
      return mn[u];
    }
    int mid = (l + r) >> 1, res = inf;
    if (ql <= mid) {
      res = std::min(res, range_min(ql, qr, l, mid, u << 1));
    }
    if (mid < qr) {
      res = std::min(res, range_min(ql, qr, mid + 1, r, u << 1 | 1));
    }
    return res;
  }   
  void modify(int pos, int l, int r, int u, int val) {
    if (l == r) {
      mn[u] = val;  
      return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
      modify(pos, l, mid, u << 1, val);
    } else {
      modify(pos, mid + 1, r, u << 1 | 1, val);   
    }
    push_up(u);  
  }
} st1;

struct Segment_Tree2 {
  int mn[N << 2];  
  inline int cmpl(int a, int b) {
    return l[rev[a]] < l[rev[b]] ? a : b;
  }
  inline void push_up(int u) {
    mn[u] = cmpl(mn[u << 1], mn[u << 1 | 1]);
  }
  void build(int l, int r, int u) {
    if (l == r) {
      mn[u] = l;
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, u << 1);
    build(mid + 1, r, u << 1 | 1);
    push_up(u);
  }
  int range_min(int ql, int qr, int l, int r, int u) {
    if (ql <= l && r <= qr) {
      return mn[u];
    }
    int mid = (l + r) >> 1, res = 0;  
    if (ql <= mid) {
      res = cmpl(res, range_min(ql, qr, l, mid, u << 1));  
    }
    if (mid < qr) {
      res = cmpl(res, range_min(ql, qr, mid + 1, r, u << 1 | 1));
    }
    return res;  
  }
} st2;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", l + i, r + i);
    senq[i] = i;
  }
  std::sort(senq + 1, senq + n + 1, [](int a, int b) {
    return r[a] < r[b];
  });
  l[0] = inf;   
  st1.build(1, n, 1);
  for (int i = 1; i <= n; i++) {
    pos[senq[i]] = st1.range_min(l[senq[i]], r[senq[i]], 1, n, 1);  
    //printf("___%d %d %d %d\n", senq[i], l[senq[i]], r[senq[i]], pos[senq[i]]);  
    rev[pos[senq[i]]] = senq[i];
    st1.modify(pos[senq[i]], 1, n, 1, n);
  } 
  st2.build(1, n, 1);    
  int x = -1, y = -1;
  bool flag = 0;
  for (int i = 1, cur; i <= n; i++) {
    //printf("__%d %d %d\n", i + 1, r[rev[i]], rev[st2.range_min(i + 1, r[rev[i]], 1, n, 1)]);    
    if (l[cur = rev[st2.range_min(i + 1, r[rev[i]], 1, n, 1)]] <= i) {
      x = rev[i];
      y = cur;
      flag = 1;
      break;  
    }
  }
  if (!flag) {
    puts("YES");
    for (int i = 1; i <= n; i++) {
      printf("%d%c", pos[i], " \n"[i == n]);
    }
  } else {
    puts("NO");
    for (int i = 1; i <= n; i++) {
      printf("%d%c", pos[i], " \n"[i == n]);
    }
    std::swap(pos[x], pos[y]);
    for (int i = 1; i <= n; i++) {
      printf("%d%c", pos[i], " \n"[i == n]);
    }
  }
  return 0; 
}
```



---

## 作者：MiniLong (赞：0)

考虑构造一组解，贪心地，按右端点、左端点排序，每个区间取最左边能取的值，用个 set 维护。

考虑怎么搞两组解，感受一下就可以发现遇到一个区间，它本来还能取到更往左的值，但是已经被取了，那么就可能与那个先取的那个区间交换。

具体地，考虑设 $L_i$ 为排列中的值 $i$ 其被取的区间左端点，$R_i$ 为右端点。那么考虑从小到大枚举每个值，就是要找到一个 $L_i \le j<i\le R_j$，那么扫到一个值的时候往 $R_i$ 处插入 $i$ 以便到时候删除，然后用个 set 维护插入删除，每次二分找到一个 $\ge L_i$ 的可以了。复杂度 $\Theta(n\log n)$。

---

