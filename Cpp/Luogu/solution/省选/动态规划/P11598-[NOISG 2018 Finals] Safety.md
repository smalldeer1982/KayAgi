# [NOISG 2018 Finals] Safety

## 题目背景

译自 [NOISG 2018 Finals E. Safety](https://github.com/noisg/sg_noi_archive/tree/master/2018/tasks/safety)。

## 题目描述

小老鼠 Squeaky 最近开始欣赏视觉艺术，并尝试创作自己的艺术作品，在城里最负盛名的艺术节上展出！

他的作品由若干发光柱组成，其中每个发光柱又都是由发光立方体堆砌而成的。

具体来说，他的作品是排成一条直线的 $N$ 个发光柱，从左到右编号为 $1$ 到 $N$。其中第 $i$ 个发光柱的高度为 $S_i$，意味着它由 $S_i$ 个发光立方体堆砌而成。

例如下图是 $N=20$ 时一种可能的作品：

![](https://cdn.luogu.com.cn/upload/image_hosting/qp61p4fu.png)

然而，观众撞到不安全的展品将造成灾难性的后果。所以，安全委员会要求 Squeaky 保证作品的安全性。具体来说，作品安全当且仅当任意两个相邻发光柱的高度差不超过 $H$，即 $|S_i-S_{i+1}|\le H,\forall i\in[1,N)$。

Squeaky 的作品可能是不安全的，为了确保正常展出，他希望通过修改作品使其安全。

他可以进行的修改只有两种：

- 在发光柱 $k$ 上添加一个发光立方体，即 $S_k\gets S_k+1$。
- 从还有至少一个发光立方体的发光柱 $k$ 上移除一个发光立方体，即 $S_k\gets S_k-1$。

注意，即使一个发光柱没有发光立方体，我们也认为它依然存在于原来的位置。

你的任务是帮助 Squeaky 确定至少需要多少次修改他的作品才能安全。

## 说明/提示

### 样例 #1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/o2mb9wvh.png)

如图所示，我们删去红色立方体，添加黄色立方体，通过修改 $10$ 次使 Squeaky 的作品安全：任意相邻的两个发光柱高度差都不超过 $H=1$。

可以证明，不存在少于 $10$ 步的修改方法。

这组样例满足子任务 $3$ 和子任务 $5$ 至 $9$。

### 样例 #2 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/9i4cjmny.png)

如图所示，我们删去红色立方体，添加黄色立方体，通过修改 $6$ 次使 Squeaky 的作品安全。可以证明，不存在少于 $6$ 步的修改方法。

这组样例满足子任务 $5$ 至 $9$。

### 样例 #3 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/v83yezxt.png)

如图所示，我们删去红色立方体，添加黄色立方体，通过修改 $4$ 次使 Squeaky 的作品安全。可以证明，不存在少于 $4$ 步的修改方法。

这组样例满足子任务 $1$ 至 $3$ 和子任务 $5$ 至 $9$。

### 样例 #4 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/narncyxs.png)

Squeaky 的作品本来就是安全的，所以不需要进行修改。

这组样例满足子任务 $3$ 和子任务 $5$ 至 $9$。

### 样例 #5 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/fo23a2wx.png)

如图所示，我们删去红色立方体，通过修改 $2$ 次使 Squeaky 的作品安全。可以证明，不存在少于 $2$ 步的修改方法。

这组样例满足所有子任务。

### 子任务

对于 $100\%$ 的数据，$1\le N\le 2\times 10^5$，$0\le H\le 10^9$，$0\le S_i\le 10^9$。

| 子任务 | 得分 | 数据范围及特殊性质 |
| :----------: | :----------: | :----------: |
| $1$ | $3$ | $N\le 10$，$S_i\le 4$ |
| $2$ | $4$ | $N\le 14$，$H\le 1$，$S_i\le 4$ |
| $3$ | $9$ | $N\le10$，$H\le 2$ |
| $4$ | $5$ | $H=0$ |
| $5$ | $6$ | $N\le 500$，$S_i\le 400$ |
| $6$ | $11$ | $N\le 500$，$S_i\le 5\times 10^3$ |
| $7$ | $11$ | $N\le 5\times 10^3$，$S_i\le 5\times 10^3$ |
| $8$ | $22$ | $N\le 5\times 10^3$ |
| $9$ | $29$ | 无特殊限制 |


## 样例 #1

### 输入

```
6 1
2 10 0 2 4 3```

### 输出

```
10```

## 样例 #2

### 输入

```
6 3
2 10 2 6 4 3```

### 输出

```
6```

## 样例 #3

### 输入

```
4 1
1 4 1 4```

### 输出

```
4```

## 样例 #4

### 输入

```
10 1
10 9 8 7 6 5 4 3 2 1```

### 输出

```
0```

## 样例 #5

### 输入

```
3 0
1 1 3```

### 输出

```
2```

# 题解

## 作者：happy_dengziyue (赞：7)

### 1 思路

我们不必限制柱子的高度必须是整数，也不必限制必须是非负数。因为调整法可以证明如果柱子的高度不是非负整数就一定不优。

首先考虑动态规划。设 $dp_{i,j}$ 为：只考虑前 $i$ 柱并且第 $i$ 柱高度必须是 $j$ 时的最小代价。

边界情况是 $dp_{0,j}=0$。可以容易地写出转移： 

$$dp_{i,j}=\min_{k=j-H}^{j+H}dp_{i-1,k}+|j-S_i|$$

答案则为 $dp_N$ 的最小值。

直接计算这个式子显然是无法通过的。但是我们发现 $dp_i$ 一定是个下凸函数：因为 $dp_{0,j}=0$，而之后的操作也不会破坏下凸的性质。

再分析这个式子。可以化为对 $dp_i$ 的如下两个修改操作：

$$dp_{i,j}\gets\min_{k=j-H}^{j+H}dp_{i-1,k}$$

$$dp_{i,j}\gets|j-S_i|$$

第一个操作实际上是将常函数段左侧往左平移 $H$，常函数段右侧往右平移 $H$，类似“拉扯”。第二个操作实际上是加上一个简单的 V 形函数。

可以考虑用两个优先队列分别维护常函数段左侧和常函数段右侧的折点，同时维护常函数段的值。

第一个操作只需要打个标记。第二个操作要分讨 V 形函数的顶点在常函数段横坐标范围里还是两侧，并修改常函数段横坐标范围；如果是两侧还需还需要计算常函数段的值的变化。

时间复杂度 $\Theta(N\log N)$。

### 2 代码与记录

```cpp
#include<bits/stdc++.h>
using namespace std;
#define max_n 200000
#define inf ((long long)2e9)
int n;
long long lim;
long long a[max_n+2];
priority_queue<long long>ql;
priority_queue<long long,vector<long long>,greater<long long>>qr;
long long low=0;
long long tagl=0,tagr=0;
int main(){
	#ifdef dzy
	freopen("P11598_1.in","r",stdin);
	freopen("P11598_1.out","w",stdout);
	#endif
	scanf("%d%lld",&n,&lim);
	for(int i=1;i<=n;++i)scanf("%lld",a+i);
	ql.push(-1); qr.push(inf); low=0;
	for(int i=1;i<=n;++i){
		tagl-=lim; tagr+=lim;
		long long l=ql.top()+tagl,r=qr.top()+tagr;
//		printf("l=%lld r=%lld low=%lld\n",l,r,low);
		if(l<=a[i]&&a[i]<=r){ql.push(a[i]-tagl); qr.push(a[i]-tagr);}
		else if(a[i]<l){
			low+=l-a[i];
			ql.push(a[i]-tagl); ql.push(a[i]-tagl);
			qr.push(ql.top()+tagl-tagr); ql.pop();
		}
		else{
			low+=a[i]-r;
			qr.push(a[i]-tagr); qr.push(a[i]-tagr);
			ql.push(qr.top()+tagr-tagl); qr.pop();
		}
	}
	printf("%lld\n",low);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/203697390)

By **dengziyue**

---

## 作者：Purslane (赞：4)

# Solution

本题等价于：给出整数序列 $t_{1,2,\cdots,n}$ 使得：$|t_i-t_{i+1}| \le h$，且 $\sum_{i=1}^n |t_i-s_i|$ 最小。

注意到没必要限制 $t$ 是非负整数，因为 $t_i < 0$ 显然不优。设 $dp_{i,j}$ 为，使得 $t_i=j$ 的最小答案。

转移显然为：

$$
dp_{i,j} = | s_i - j | + \min_{j-h \le k \le j+h} dp_{i-1,k}
$$

一个预感是，$dp_{i,j}$ 为凸函数（这种东西很难数据结构优化）。试试确实如此。

那考虑 $z_{i,j}=\min_{j-h \le k \le j+h} dp_{i-1,k}$ 的形态，发现如下图所示：

![](https://s21.ax1x.com/2025/01/28/pEVnDHO.png)

因此考虑维护斜率的连续段，发现只有：

1. 二分找到第一个 $>0$ 的位置。
2. 插入一段数。
3. 区间 $\pm 1$。

发现可以使用平衡树加速，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10; 
mt19937 myrand(time(NULL));
int n,h,s[MAXN],fval,rt,tot;
struct Node {int len,tag,k,sze,key,lson,rson;}t[MAXN<<1];
int get_node(int k) {return t[++tot]={0,0,k,0,myrand(),0,0},tot;}
void assign(int u,int ad) {return t[u].k+=ad,t[u].tag+=ad,void();}
void push_up(int u) {return t[u].sze=t[t[u].lson].sze+t[t[u].rson].sze+t[u].len,void();}
void push_down(int u) {return assign(t[u].lson,t[u].tag),assign(t[u].rson,t[u].tag),t[u].tag=0,void();}
void split1(int u,int &p,int &q) {
	if(!u) return p=q=0,void();
	push_down(u);
	if(t[u].k<0) return p=u,split1(t[u].rson,t[u].rson,q),push_up(u),void();
	return q=u,split1(t[u].lson,p,t[u].lson),push_up(u),void();
}
void split2(int u,int s,int &p,int &q) {
	if(!u) return p=q=0,void();
	push_down(u);
	if(t[t[u].lson].sze>=s) return q=u,split2(t[u].lson,s,p,t[u].lson),push_up(u),void();
	if(t[t[u].lson].sze+t[u].len>s) {
		int v=get_node(t[u].k);
		int len1=s-t[t[u].lson].sze;
		int len2=t[u].len-len1;
		t[u].len=len1,t[v].len=len2,t[v].rson=t[u].rson,t[u].rson=0;
		return p=u,q=v,push_up(u),push_up(v),void();	
	}
	return p=u,split2(t[u].rson,s-t[t[u].lson].sze-t[u].len,t[u].rson,q),push_up(u),void();
}
int merge(int u,int v) {
	if(!u||!v) return u|v;
	push_down(u),push_down(v);
	if(t[u].key<=t[v].key) return t[u].rson=merge(t[u].rson,v),push_up(u),u;
	return t[v].lson=merge(u,t[v].lson),push_up(v),v;
}
void dfs(int u) {
	if(!u) return ;
	push_down(u),dfs(t[u].lson),dfs(t[u].rson);
	if(t[u].k<0) fval+=t[u].k*t[u].len;
	return ;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>h;
	ffor(i,1,n) cin>>s[i];
	fval=s[1];
	int id1=get_node(-1),id2=get_node(1);
	t[id1].len=t[id1].sze=s[1],t[id2].len=t[id2].sze=1000000000;
	rt=merge(id1,id2);
	ffor(i,2,n) {
		int A,B,C;
		split1(rt,A,B),C=get_node(0),t[C].len=t[C].sze=h*2;
		rt=merge(A,merge(C,B));
		split2(rt,s[i]+(i-1)*h,A,B);
		fval+=abs(s[i]+(i-1)*h);
		assign(A,-1),assign(B,1);
		rt=merge(A,B);
	}
	dfs(rt);
	cout<<fval;
	return 0;
}
```

---

## 作者：冷却心 (赞：1)

Slope Trick 板题，不知道之前为什么不会做。

记 $f_i (x)$ 表示第 $i$ 个柱子放 $x$ 个立方体，使得前 $i$ 个柱子满足要求，最小的花费。那么显然有转移： 
$$ f_i (x) \leftarrow |S_i - x| + \min_{x - H \le y \le x + H} f_{i-1}(y). $$ 
注意到 $f_i (x)$ 下凸，证明考虑归纳法，首先 $f_1(x)$ 是一个绝对值，显然下凸，如果已知 $f_i (x)$ 下凸，那么它连续一段取 $\min$ 同样下凸，加上一个绝对值的凸函数仍保持凸性，所以 $f_{i+1}(x)$ 也是下凸的。

所以考虑 slope trick。我们维护斜率为 $0$ 的底部的左右两侧的斜率变化点的集合即可。取 $\min$ 操作相当于左侧集合整体减去 $H$，右侧集合整体加上 $H$，而加上绝对值函数相当于插入两个 $S_i$ 点，这个时候要注意分讨：

- 如果 $S_i$ 落在原来斜率为 $0$ 的部分那么左右各加入一个 $S_i$，此时 $S_i$ 恰好为函数最小值，答案不变。
- 如果 $S_i$ 落在左侧集合内，那么因为它给斜率加了 $2$，所以左侧集合的最右端点变成了上升的部分，要移动到右侧集合，并且造成函数最小值变化，也就是答案的变化。当 $S_i$ 落在右侧集合同理。

支持全局加法，查询集合 $\min/\max$ 的数据结构选择优先队列或者 `multiset` 然后做完了。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
int n, H, A[N];
multiset<LL> s1, s2; LL tag1, tag2, Ans = 0;
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> H;
	for (int i = 1; i <= n; i ++) cin >> A[i];
	s1.insert(A[1]); s2.insert(A[1]);
	for (int i = 2; i <= n; i ++) {
		tag1 -= H, tag2 += H;
		if (*s1.rbegin() + tag1 >= A[i]) {
			s2.insert(*s1.rbegin() + tag1 - tag2); s1.erase(s1.find(*s1.rbegin()));
			s1.insert(A[i] - tag1); s1.insert(A[i] - tag1);
			Ans += *s2.begin() + tag2 - A[i];
		} else if (*s2.begin() + tag2 <= A[i]) {
			s1.insert(*s2.begin() + tag2 - tag1); s2.erase(s2.find(*s2.begin()));
			s2.insert(A[i] - tag2); s2.insert(A[i] - tag2);
			Ans += A[i] - *s1.rbegin() - tag1;
		} else s1.insert(A[i] - tag1), s2.insert(A[i] - tag2);
		while (!s1.empty() && *s1.begin() + tag1 < 0) s1.erase(s1.find(*s1.begin()));
	} cout << Ans << "\n";
	return 0;
}
```

---

## 作者：liuchuliang666 (赞：0)

不久前从 [OI Wiki 那儿](https://oi-wiki.org/dp/opt/slope-trick/) 学的 Slope Trick，写发题解巩固一下。

首先，我们设 $f_{i, j}$ 为已考虑前 $i$ 个柱子，并且第 $i$ 个被调整至 $j$ 时的最小代价，那么容易得到朴素的转移：

$$f_{i, j} = \min_{k = j - H}^{j + H} f_{i - 1, k} + |j - S_i|$$

时间复杂度达到了惊人的 $O(nV^2)$，考虑优化。

我们注意到每次加进来绝对值函数 $w = |j - S_i|$，其图像是一段折线。

这提示我们使用 Slope Trick，考虑将 $f_{i, j}$ 改写成函数形式 $f_i(j)$，那么前面的 $\min$ 操作就是将曲折的地方“拍平”，通过手玩样例可以归纳发现，$y = f_i(x)$ 的图像永远是左边一段斜率递减的折线，中间一条水平线段，右边一段斜率递增的折线。

那么这个状态的转移就有了一个更为形象的表述：将图像左右两端拉开，中间加一折线段。

对应到 Slope Trick，就是：
1. 原负斜率段向左移动 $h$，正斜率段向右移动 $h$；
2. 插入两次 $a_i$。

考虑到所有操作都集中在平的那段，我们开个对顶堆来维护左右两部分的拐点，那么第一个操作打懒标记即可，第二个操作分别向两边插一个 $a_i$，然后需要维护一下对顶堆，因为未必最大堆的堆顶仍然小于等于最小堆的堆顶。

最后考虑如何统计答案，事实上，画图可以发现，每次交换堆顶时，函数会平移堆顶差的距离，累加即可。

最后献上极其丑陋的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define rep(i, l, r, ...) for (int i = (l), i##e = (r), ##__VA_ARGS__; i <= i##e; ++i)
#define per(i, r, l, ...) for (int i = (r), i##e = (l), ##__VA_ARGS__; i >= i##e; --i)
#define mst(x, val) memset(x, val, sizeof(x))
#define mcp(from, to) memcpy(to, from, sizeof(to))
#define mid (((l) + (r)) >> 1)
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int MAXN = 2e5 + 10, inf = 1e18;
int n, h, x, lt, rt, ans;
priority_queue<int> pqmx;
priority_queue<int, vi, greater<>> pqmn;
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> h;
    while (n--)
    {
        cin >> x, lt += h, rt += h;                   // 区间平移打标记
        pqmx.emplace(x + lt), pqmn.emplace(x - rt);   // 插入两次 x
        int l = pqmx.top() - lt, r = pqmn.top() + rt; // 调整对顶堆
        while (l > r)
        {
            pqmn.pop(), pqmx.pop();
            ans += l - r; // 相当于函数平移了
            pqmx.emplace(r + lt), pqmn.emplace(l - rt);
            l = pqmx.top() - lt, r = pqmn.top() + rt;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：tony0530 (赞：0)

这显然是 Slope Trick 板题呀。

先考虑朴素DP，用 $f_i(x)$ 表示第 $i$ 个柱子放 $x$ 个立方体，使得前 $i$ 个柱子满足要求的最小的花费。

显然有 $f_i(x) = |S_i - x| + \min_{|x - y| \le H} f_{i-1}(y)$，证明这个函数是一个下凸函数可以用数学归纳法来证，比较简单，就不在这里提供证明了。

就直接维护斜率为 0 的底部的左右两侧的斜率变化点的集合即可。

维护如下：

- 取 $\min$ 的时候，就是将左侧减去 $H$，再将右侧加上 $H$ 就可以了。
- 加上绝对值函数就不太一样了，虽然相当于插入两个 $S_i$，但是，请注意分讨：

  - 若 $S_i$ 在斜率为 0 的部分， 则左右各加一个 $S_i$，此时 $S_i$ 最小，函数不变。
  - 若 $S_i$ 在斜率为 0 的左右两侧，由于对称性，不妨设落在斜率为 0 的左侧的话，因为斜率加了 2 ，所以左部分的最右边上升了，要移动到右部分，此时的答案也有了变化，就是最小值的变化，这个就用 multiset 来维护就好了，当然如果是在斜率为 0 的右边也同理。

代码就不放了，码风很乱，上面说的也够清楚了，其他题解也有。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P11598)

**题目大意**

> 给定 $a_1\sim a_n$，每次操作可以选择一个 $a_i$ 增减一，求最小操作次数使得所有 $|a_{i+1}-a_i|\le h$。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

朴素 dp $f_{i,j}$ 表示 $a_i=j$ 的方案数，转移为 $f_{i,j}\gets \min f_{i-1}[j-h,j+h]+|j-a_i|$。

那么考虑凸优化，直接维护函数斜率的拐点，拓展操作相当于把斜率为 $0$ 的区间左右分别平移 $h$。

用两个堆维护斜率为正负两部分的拐点，需要支持全局加，打标记即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
int n,m,a[MAXN];
priority_queue <ll> L;
priority_queue <ll,vector<ll>,greater<ll>> R;
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	ll tg=0,ht=0; L.push(a[1]),R.push(a[1]);
	for(int i=2;i<=n;++i) {
		tg+=m;
		ll x=L.top()-tg,y=R.top()+tg;
		if(a[i]<=x) {
			ht+=abs(a[i]-x),L.pop(),L.push(a[i]+tg),L.push(a[i]+tg),R.push(x-tg);
		} else if(y<=a[i]) {
			ht+=abs(a[i]-y),R.pop(),R.push(a[i]-tg),R.push(a[i]-tg),L.push(y+tg);
		} else L.push(a[i]+tg),R.push(a[i]-tg);
	}
	printf("%lld\n",ht);
	return 0;
}
```

---

