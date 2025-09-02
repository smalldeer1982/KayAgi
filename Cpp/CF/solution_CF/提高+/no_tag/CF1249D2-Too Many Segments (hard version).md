# Too Many Segments (hard version)

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
4 6 7 
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
1 4 5 
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

## 作者：梧桐灯 (赞：8)

对于这种区间覆盖问题大部分情况是贪心，小部分情况是DP，还有极少部分是网络流—— @Binary_Search_Tree

没错，此题就是利用堆的贪心来解决区间覆盖问题。

首先将读入的线段按左端点从小到大排序并丢到一个差分数组离里去，排完序后我们按点考虑。

考虑1~i-1个点已经合法，对于第i个点首先将覆盖这个点的线段放进堆里。

然后如果这个点不合法，我们肯定尽量删除覆盖它且右端点更大的线段。

所以维护以右端点为关键字的大根堆即可。

code:

```cpp
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
 
inline void read (int& s) {
	s = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar ();
	return ;
}
 
const int N = 200003;
int k, n, ans, a[N], sum[N], mx;
struct stu {
	int x, y, id;
}s[N], p;
 
inline int cmp2 (const stu p, const stu q) {
	if (p.x == q.x) return p.y < q.y;
	return p.x < q.x;
}
 
struct cmp {
	inline int operator () (const stu& p, const stu& q) const {
		return p.y < q.y;
	}
};
 
priority_queue <stu, vector <stu>, cmp> q;
 
int main () {
	read (n), read (k);
	int i; for (i = 1; i <= n; ++i) {
		read (s[i].x), read (s[i].y), s[i].id = i;
		++sum[s[i].x];
		--sum[s[i].y + 1];
	} //先丢进差分数组
	sort (s + 1, s + 1 + n, cmp2); //按左端点排序
	int j = 1;
	for (i = 1; i < N; ++i) {
		while (j <= n && s[j].x <= i) q.push (s[j++]);//将覆盖这个点的线段丢进堆里
		sum[i] += sum[i - 1]; 
		while (sum[i] > k) {
			p = q.top ();
			q.pop ();
			a[++ans] = p.id;
			--sum[i];
			++sum[p.y + 1];
		} //尽量删靠右的线段
	}
	printf ("%d\n", ans);
	if (ans) {
		for (i = 1; i < ans; ++i) printf ("%d ", a[i]);
		printf ("%d\n", a[ans]);
	}
	return 0;
}
```


---

## 作者：Lucifer_Bartholomew (赞：7)

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

## 作者：Handezheng (赞：6)

## [题目传送门](https://www.luogu.com.cn/problem/CF1249D2)
## 前言:
这道题是 [CF1249D1 Too Many Segments (easy version)](https://www.luogu.com.cn/problem/CF1249D1) 的加强版，建议读者先去做一下此题，或是看一下它的题解，理解这两道题 **贪心** 的基本思路，~~以免看得一头雾水。~~

## 思路
~~额，本来想略过的，楼上 dalao 讲的很清楚了，但考虑到这是我洛谷上的第一篇题解，还是讲一讲吧。~~  
题目要求我们删除一部分线段使得没有“坏点”的存在，那我们肯定要遍历一遍区间，找到哪个点是“坏点”后，才能进行操作。  

当我们枚举到一个点时，如果这个点是“坏点”，**那它肯定被多条线段所覆盖**，枚举到这个点时，它前面的点一定都不是“坏点”（本来就不是“坏点”或**在前面已经删掉一些线段使它不是“坏点”**）。  
那么当前覆盖这个点的线段的**左端点对其毫无用处**，无论删除多少条线段都不会改变这个点左面所有点是不是“坏点”，那我们可以关注**右端点**：

**贪心地想**，一条线段的右端点越“远”，那它就对更多的点有影响（贡献越大）。  
所以，我们应该尽量删除**右端点更靠右的线段**。

## 细节及实现
### 实现
- 数据范围：$n \le  2\times10^5$ 并且 $l,r \le 2\times10^5$，这意味着遍历区间所有点就需要花费 $O(r_{max})$ 的时间复杂度，所以就无法再花费 $O(n)$ 的复杂度来枚举所有线段了。
- 考虑优化。我们可以用一个数据结构来存储覆盖到当前点的线段，考虑到要需要用**排序**维护右端点更靠右，最好用 `priority_quque` 或 `set`（我个人推荐用 `set`,因为 `priority_quque` 仅支持 `priority_queue.top()` 的删除）。
- 遍历到一个点时，可能会有多条线段以它为左端点，所以我们可以用**二维的** `vector` 来存储线段的有关信息。

### 细节
- 题目要求输出线段的编号，所以我们的 `set` 和 `vector`  都是**结构体**，包括线段右端点和线段编号。
- 在遍历到一个新的点时，我们要把右端点小于当前点的线段删掉（容易想到这样的点已经“过期”了，对后续操作无用）。
- 我们在删除线段时仅保证右端点尽量大，不保证它的编号是升序的，所以要对 $ans$ 数组进行**排序**（以编号为关键字）。
- ~~感谢 STL 库~~ `set` 中有一个不常用的功能：`set.rbegin()` 指 `set.end()` 的前一个位置，在本题中就是右端点最大点所在的位置。
- `set.begin()`，`set.rbegin()` 等返回的都是元素所在的位置，使用时应加上符号“*”。
## AC code
~~应该有部分读者最喜欢看这个，所以把它安排在最后~~
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
## 最后的最后
本蒟蒻第五次申请题解，希望管理大大高抬贵手，把审核通过了吧~  
第一次被打回：2024-06-13 10:08  
第二次被打回：2024-07-05 14:18  
第三次被打回：2024-07-08 15:47  
第四次被打回：2024-07-10 22:21

---

## 作者：Daniel_yao (赞：3)

本题是 [CF1249D1 Too Many Segments (easy version)](https://www.luogu.com.cn/problem/CF1249D1) 的加难版，在解决本题之前，可以先看看本题的简单版本，可能会对你解这道题起到一个过度作用。~~以防止讲了一大堆到后来自己却没有思路。~~

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
2.思路二：**优化** 暴力

看一眼 $n$ 的范围，直接懵比，看来要上 $O(n\log n)$ 级别的数据结构优化了。

不难发现，所有的操作都是建立在右端点有序的情况下才进行的。所以，我们可以维护一个有序集合将右端点放进有序集合中，在从左到右枚举左端点，枚举左端点的同时判断当前左端点所对应的点是否被超过 $k$ 个线段所覆盖。操作同思路一。

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

## 作者：Chenyanxi0829 (赞：2)

先把区间按照左端点排序，然后从前往后一个一个加进去，同时用一个支持区间加的线段树维护每个位置的最大被覆盖次数，如果加进去这第 $i$ 个区间后最大被覆盖次数 $>k$，就需要删掉一个区间，删完这个区间后肯定会变为合法，因为加入第 $i$ 个区间之前是合法的。由于左端点是递增的，所以删掉当前加进去的区间中右端点最大的区间肯定是最优的，因此还需要用一个优先队列维护加进去的区间中右端点最大的区间。

## 代码
其他实现细节见代码。
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 1;

int n, m, tr[kMaxN * 4], la[kMaxN * 4], l1, r1, X, ma;
array<int, 3> a[kMaxN];
priority_queue<array<int, 3>> q;
bool g[kMaxN];

inline void P(int i) { tr[i << 1] += la[i], tr[(i << 1) | 1] += la[i], la[i << 1] += la[i], la[(i << 1) | 1] += la[i], la[i] = 0; }

int Q(int i, int l, int r) {
  if (l1 <= l && r <= r1) {
    return tr[i];
  }
  if (r < l1 || r1 < l) {
    return 0;
  }
  P(i);
  int m = (l + r) >> 1;
  return max(Q((i << 1), l, m), Q(((i << 1) | 1), m + 1, r));
}

void G(int i, int l, int r) {
  if (l1 <= l && r <= r1) {
    tr[i] += X, la[i] += X;
    return;
  }
  if (r < l1 || r1 < l) {
    return;
  }
  P(i);
  int m = (l + r) >> 1;
  G((i << 1), l, m), G(((i << 1) | 1), m + 1, r), tr[i] = max(tr[i << 1], tr[(i << 1) | 1]);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i][0] >> a[i][1], a[i][2] = i, ma = max(ma, a[i][1]);
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    l1 = a[i][0], r1 = a[i][1], X = 1, q.push({r1, l1, a[i][2]}), G(1, 1, ma);
    if (tr[1] > m) {
      l1 = q.top()[1], r1 = q.top()[0], q.pop(), X = -1, G(1, 1, ma);
    }
  }
  cout << n - q.size() << '\n';
  for (; q.size(); g[q.top()[2]] = 1, q.pop()) {
  }
  for (int i = 1; i <= n; i++) {
    if (!g[i]) {
      cout << i << " ";
    }
  }
  return 0;
}
```

---

## 作者：minVan (赞：2)

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

## 作者：JWRuixi (赞：2)

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

