# [ABC352D] Permutation Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc352/tasks/abc352_d

$ (1,2,\dots,N) $ を並び替えて得られる数列 $ P=(P_1,P_2,\dots,P_N) $ が与えられます。

長さ $ K $ の正整数列 $ (i_1,i_2,\dots,i_K) $ であって、以下の条件を共に満たすものを**良い添字列**と呼びます。

- $ 1\leq\ i_1\ <\ i_2\ <\ \dots\ <\ i_K\ \leq\ N $
- $ (P_{i_1},P_{i_2},\dots,P_{i_K}) $ はある連続する $ K $ 個の整数を並び替えることで得られる。   
  厳密には、ある整数 $ a $ が存在して、$ \lbrace\ P_{i_1},P_{i_2},\dots,P_{i_K}\ \rbrace\ =\ \lbrace\ a,a+1,\dots,a+K-1\ \rbrace $。

全ての良い添字列における $ i_K-i_1 $ の最小値を求めてください。 なお、本問題の制約下では良い添字列が必ず $ 1 $ つ以上存在することが示せます。

## 说明/提示

### 制約

- $ 1\leq\ K\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ P_i\leq\ N $
- $ i\neq\ j $ ならば $ P_i\neq\ P_j $
- 入力は全て整数

### Sample Explanation 1

良い添字列は $ (1,2),(1,3),(2,4) $ の $ 3 $ つです。 例えば $ (i_1,i_2)=(1,3) $ は、 $ 1\leq\ i_1\ <\ i_2\ \leq\ N $ かつ $ (P_{i_1},P_{i_2})=(2,1) $ が連続する $ 2 $ つの整数 $ 1,2 $ の並び替えなので良い添字列です。 これらの良い添字列のうち $ i_K-i_1 $ の値が最小となるのは $ (1,2) $ で、そのときの値は $ 2-1=1 $ です。

### Sample Explanation 2

どの良い添字列においても $ i_K-i_1=i_1-i_1=0 $ です。

## 样例 #1

### 输入

```
4 2
2 3 1 4```

### 输出

```
1```

## 样例 #2

### 输入

```
4 1
2 3 1 4```

### 输出

```
0```

## 样例 #3

### 输入

```
10 5
10 1 6 8 7 2 5 9 3 4```

### 输出

```
5```

# 题解

## 作者：yzx3195 (赞：18)

# 题目大意
就是在原序列 $P$ 中取出 $k$ 个元素，这 $k$ 个元素的下标必须 **从小到大**，且这 $k$ 个元素为连续的自然数，求满足条件的最大下标减最小下标的最小值。
# 思路
不难发现我们可以将数组中的元素映射在另一个数组上，即 
$$ a_{p_i}=i $$

拿样例来说吧，`10 1 6 8 7 2 5 9 3 4` 映射完就是 `2 6 9 10 7 3 5 4 8 1`，由于这 $k$ 个数可以互换，所以这样做是没有错的，最后在 $i$ 至 $i+k-1$ 这个区间查询最大值和最小值，相减取最小即可。

时间复杂度为 $O(n \log k)$。

~~听说正解是滑动窗口~~。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e05 * 2 + 7;

int p[MAXN];

int n, k;

int a[MAXN];

template <typename T> int mymax(T x, T y)
{
    return x > y ? x : y;
}

template <typename T> int mymin(T x, T y)
{
    return x < y ? x : y;
}

int tree[MAXN << 2];

int tree1[MAXN << 2];

void Build(int l, int r, int p)
{
    if(l == r)
    {
        tree[p] = a[l];
        tree1[p] = a[l];
        return ;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, p << 1);
    Build(mid + 1, r, p << 1 | 1);
    tree[p] = mymax(tree[p << 1], tree[p << 1 | 1]);
    tree1[p] = mymin(tree1[p << 1], tree1[p << 1 | 1]);
    return ;
}

int Query_max(int pl, int pr, int l, int r, int p)
{
    int ans = -0x3f3f3f3f;
    if(l > pr or r < pl)   
        return -0x3f3f3f;
    if(pl <= l and r <= pr)
    {
        return tree[p];
    }
    int mid = (l + r) >> 1;
    if(pl <= mid)
        ans = mymax(Query_max(pl, pr, l, mid, p << 1), ans);
    if(pr > mid)
        ans = mymax(ans, Query_max(pl, pr, mid + 1, r, p << 1 | 1));
    return ans;
}

int Query_min(int pl, int pr, int l, int r, int p)
{
    int ans = 0x3f3f3f3f;
    if(l > pr or r < pl)
    {
        return 0x3f3f3f3f;
    }
    if(pl <= l and r <= pr)
    {
        return tree1[p];
    }
    int mid = (l + r) >> 1;
    if(pl <= mid)
        ans = mymin(ans, Query_min(pl, pr, l, mid, p << 1));
    if(pr > mid)
        ans = mymin(ans, Query_min(pl, pr, mid + 1, r, p << 1 | 1));
    return ans;
}

signed main()
{
    scanf("%d%d", &n, &k);

    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        a[p[i]] = i;
    }

     //for(int i = 1; i <= n; i++)
      //   cout << a[i] << " ";
     //cout << "\n";

    Build(1, n, 1);

    int ans = 0x3f3f3f3f;

    for(int i = 1; i <= n; i++)
    {
        if(i + k - 1 > n)
            break;
        int Kul = Query_max(i, i + k - 1, 1, n, 1);
        int Kop = Query_min(i, i + k - 1, 1, n, 1);
        // cout << Kul << " " << Kop << "\n";
        ans = mymin(ans, Kul - Kop);
    }

    printf("%d", ans);

    return 0;
}
```
# Update 
2024.5.9 谢谢 [liuhongyang123](https://www.luogu.com.cn/user/914372) 大苣发现一处笔误，已修改。

---

## 作者：zhujiangyuan (赞：14)

[problem](https://www.luogu.com.cn/problem/AT_abc352_d)

不懂为什么有这么多人用 ST 表、单调队列，甚至线段树，set 它不香吗？

记 $pos_i$ 为数字 $i$ 的位置，用一个 set 维护当前集合。

设当前数字为 $a$，则 set 中存的是 $pos_{a-k+1}\sim pos_{a}$，$ans$ 对 set 中的最大值与最小值之差取 $\min$。

set 代码很短：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL n, k, a[N], ans = 1e10, pos[N];
set <LL> s;
int main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i;
	for (int i = 1; i <= k; i++) s.insert (pos[i]);
	ans = *(--s.end()) - *s.begin();
	for (int i = k + 1; i <= n; i++) {
		s.erase (pos[i - k]);
		s.insert (pos[i]);
		ans = min (ans, *(--s.end()) - *s.begin());
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：7)

虽然比赛没打，但是想来~~水估值~~发表思路。

## 题意

给你一个 $1\sim n$ 的排列，让你从中找一段长为 $k$ 的子序列，使得这个子序列中的元素排序后数值连续。

## 分析

题意转换一下，先用结构体存储每个元素的编号和数值，按照数值排序。

于是这道题就成了：一个序列，让你求所有长 $k$ 的子段中每个段编号极差的最小值。

所以我们需要维护每个段编号最大最小值，我选择了 ST 表。

其他做法维护也有很多，这里就不讲了。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int maxn=1e6+10;
int n,k;
struct no
{
	int d,id;
}a[maxn];
bool cmp(no x,no y)
{
	return x.d<y.d;
}
int ma[maxn][22],mi[maxn][22];
void pre()
{
	for(int j=1;j<=20;j++){
     	for(int i=1;i+(1<<j)-1<=n;i++)
			mi[i][j]=min(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
	}
    for(int j=1;j<=20;j++){
     	for(int i=1;i+(1<<j)-1<=n;i++)
      		ma[i][j]=max(ma[i][j-1],ma[i+(1<<(j-1))][j-1]);
	}
	
}
int askmax(int l,int r)
{
	int le=l,ri=r;
        int len=log2(ri-le+1);
        return max(ma[le][len],ma[ri-(1<<len)+1][len]);
}
int askmin(int l,int r)
{
	int le=l,ri=r;
        int len=log2(ri-le+1);
		return min(mi[le][len],mi[ri-(1<<len)+1][len]);
}
signed main()
{
//  freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		a[i].d=read();
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);	
	for(int i=1;i<=n;i++)swap(a[i].d,a[i].id);
	for(int i=1;i<=n;i++)mi[i][0]=ma[i][0]=a[i].d;
	pre();
	int ans=1e9+7;
	for(int l=1;l<=n-k+1;l++)
	{
		int r=l+k-1;
		ans=min(ans,askmax(l,r)-askmin(l,r));
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：XXh0919 (赞：7)

第一次写 D 题题解，还请管理员大大过一下，谢谢！

### 前言

玄学……抽象……代码写得云里雾里的……

### 题意

给你一个长度为 $N$ 的序列，让你在这个序列中找到长度为 $K$ 的“好索引序列”，使得这个“好索引序列”满足以下条件：

- $1\leq i_1<i_2<i_K\leq N$
- 该数列为公差为 $1$ 的等差数列。

求这个长度为 $K$ 的序列末尾元素减去首个元素可能的最小值。

### 解法

由于题目保证 $K\leq N$，所以我们只需要考虑输入进来的每个元素是否小于等于 $K$，然后我们还要记录下这个元素的位置，以便后面的操作进行（该数组我们称为 $Q$）。

接着从 $K+1$ 循环到 $N$，每一次循环就将 $Q_i$ 加进去，再将 $Q_{i-K}$ 从 $Q$ 中删除，然后找末尾元素减去首个元素的最小值，输出就行了……

~~头脑风暴……~~

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define MDR(a,k) memset(a,k,sizeof a)
#define FAL(i,n) for(int i=1;i<=(n);++i)
#define LAF(i,n) for(int i=(n);i>=1;--i)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=3e6+15;
int n,k;
int p[N],q[N];

void solve(){
	set<int>t;
	cin>>n>>k;
	FAL(i,n){
		cin>>p[i];
		q[p[i]]=i;
		if(p[i]<=k)t.insert(i);
	}
	int ans=*t.rbegin()-*t.begin();
	rep(i,k+1,n){
		t.insert(q[i]);
		t.erase(q[i-k]);
		ans=min(ans,*t.rbegin()-*t.begin());
	}
	cout<<ans<<endl;
}

main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
} 
```

---

## 作者：Tjaweiof (赞：6)

# AT_abc352_d 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_d)

先求出每个数的位置 $c_i$，表示数字 $i$ 在排列中的位置。

题目转化成求 $\min_{i=1}^{n-k+1}(\max_{j=i}^{i+k-1}c_i-\min_{j=i}^{j+k-1}c_i)$，直接硬算时间复杂度是 $O(n^2)$ 的，显然会炸。于是考虑优化：后面的 $\max_{j=i}^{i+k-1}c_i-\min_{j=i}^{j+k-1}c_i$ 可以用两个单调队列维护以达到 $O(n)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FIRE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n, k, a[200001], c[200001], ans;
deque <int> dq, dq2;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	ans = n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		c[a[i]] = i;
	}
	for (int i = 1; i <= n; i++){
		while (!dq.empty() && dq.back() < c[i]){
			dq.pop_back();
		}
		dq.push_back(c[i]);
		while (!dq.empty() && a[dq.front()] < i - k + 1){
			dq.pop_front();
		}
		while (!dq2.empty() && dq2.back() > c[i]){
			dq2.pop_back();
		}
		dq2.push_back(c[i]);
		while (!dq2.empty() && a[dq2.front()] < i - k + 1){
			dq2.pop_front();
		}
		if (i >= k){
			ans = min(ans, dq.front() - dq2.front());
		}
	}
	cout << ans;
    return 0;
}

```

---

## 作者：Dtw_ (赞：4)

[at](https://atcoder.jp/contests/abc352/tasks/abc352_d)
# 题目大意
给你一个长度为 $N$ 的排列组合 $P$，求一个长度为 $K$ 的区间，要求 $[i,i+k-1]$ 中要包含 $i,i+1,...,i+k-1$。定义一个这样的区间的值为 $\max(t_i)-\min(t_i)$ 其中 $t_i$ 为 $i$ 出现的位置。求他的符合要求的区间的最小值。

# 思路
首先，我们考虑如何去找一个区间包含我们希望选的数，但是发现好像不太行。那么从区间上找不行那我们就从数上找。

我们考虑将 $1,2,...,N$ 每个数作为开头（注意边界）然后挨个去找他们的最大的坐标和最小的坐标，那么我们就会发现，这不就是区间查询最大值和最小值吗？

~~直接用线段树！~~

因为他是静态区间，所以考虑用 st 表来维护。

st 表不会的可以去看[这](https://www.luogu.com.cn/article/c89177og)。

他比线段树要快，而且码量少。

在多一嘴，本题要维护最大和最小，所以我们开两个数组来维护就行。

# Code

`f` 表示最大值，`g` 表示最小值
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n, k;

int a[N], b[N];

int llg[N];

int f[N][21];
int g[N][21];

void init()
{
	llg[0] = -1;
	for(int i=1; i<=N-10; i++)
	{
		llg[i] = llg[i>>1] + 1;
	}
}

int st(int l, int r)
{
	int p = llg[r - l + 1];
	return max(f[l][p], f[r-(1<<p)+1][p]);
}

int st2(int l, int r)
{
	int p = llg[r - l + 1];
	return min(g[l][p], g[r-(1<<p)+1][p]);
}

signed main()
{
	init();
	fst;
	cin >> n >> k;
	for(int j=1; j<=20; j++)
	{
		for(int i=1; i<=n-(1<<j)+1; i++)
		{
			g[i][j] = INF;
		}
	}
	for(int i=1; i<=n; i++)
	{
		cin >> a[i];
		b[a[i]] = i;
	}
	for(int i=1; i<=n; i++)
	{
		f[i][0] = b[i];
		g[i][0] = b[i];
	}
	for(int j=1; j<=20; j++)
	{
		for(int i=1; i<=n-(1<<j)+1; i++)
		{
			f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
			g[i][j] = min(g[i][j-1], g[i+(1<<(j-1))][j-1]);
		}
	}
	int ans = INF;
	for(int i=1; i<=n-k+1; i++)
	{
		int l = st2(i, i+k-1);
		int r = st(i, i+k-1);
		ans = min(r - l, ans);
//		cout << l << " " << r;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：zhangyuhaoaa (赞：4)

## 思路

这道题的暴力非常的简单，我在这里不过多介绍了，现在看一下 $AC$ 方法。

我们考虑贪心我们知道，要让跨度最短，我们枚举每一个连在一起的长度，我们用 $minn$ 维护最小值即可。

我们可以用小根堆和大根堆维护每个段的最靠前和最靠后的即可

## $AC\ code$

```cpp
#include <bits/stdc++.h>
#define re register
#define il inline
#define int long long
#define endl '\n'
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int P = 998244353;
const int INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e6 + 5;

struct node {
	int x, y;
};

int n, k;
int c[maxn];
int ans = INF;
node a[maxn]; 
priority_queue<int> pq1;
priority_queue<int, vector<int>, greater<int> > pq2;

bool cmp(node a, node b) {
	return a.x < b.x;
}

signed main() {
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    fst;
	
	cin >> n >> k;
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i].x;
		a[i].y = i;
	}
	sort(a + 1, a + n + 1, cmp);
	
	for (int i = 1; i <= n; ++ i ) {
		if (i < k) {
			c[a[i].y] ++;
			pq1.push(a[i].y);
			pq2.push(a[i].y);
		} else if (i == k) {
			c[a[i].y] ++;
			pq1.push(a[i].y);
			pq2.push(a[i].y);
			ans = min(ans, pq1.top() - pq2.top());
		} else {
			c[a[i - k].y] --;
			c[a[i].y] ++;
			pq1.push(a[i].y);
			pq2.push(a[i].y);
			while (!pq1.empty() && c[pq1.top()] == 0) {
				pq1.pop();
			}
			while (!pq2.empty() && c[pq2.top()] == 0) {
				pq2.pop();
			}
			ans = min(ans, pq1.top() - pq2.top());
		}
	}
	cout << ans;
	
    return 0;
}

```

---

## 作者：Ame_wiki (赞：4)

题面传送门： [link](https://www.luogu.com.cn/problem/AT_abc352_d)

## 题意简述

给你一个长度为 $n$ 的序列，让你选择一串长度为 $k$ 的子序列（不要求连续），使得子序列重排后构成一个公差为 $1$ 的等差序列，使得的子序列中最大下标减最小下标的值最小，求这个值。

## 思路

由于序列中数字不重复，很明显，我们可以用数组存下来每个数在序列的下标。然后枚举从 $k$ 到 $n$ 枚举重排后子序列（等差数列）的右端点，至于这一段中最大跨度，只需要用 ST 表预处理查询即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"
const int N=1145140+1919810,M=10005,inf=1e18;

int n,a[N],x[N],k,minn=inf;
int f[500005][30],dp[500005][30],lg[5000005];
void intt(){
	for(int i=1;i<=n;i++) f[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
	for(int i=1;i<=n;i++) dp[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i<=n;i++){
			dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
		}
	}
	lg[1]=0;
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
}
int getlow(int l,int r){
	int k=lg[r-l+1];
	return min(dp[l][k],dp[r-(1<<k)+1][k]);
}
int getup(int l,int r){
	int k=lg[r-l+1];
	return max(f[l][k],f[r-(1<<k)+1][k]);
} 

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>x[i],a[x[i]]=i;
	intt();
	for(int i=k;i<=n;i++){
		minn=min(minn,getup(i-k+1,i)-getlow(i-k+1,i));
	}cout<<minn;
	return 0;
}
/*  idea By cotton Joe
	*/
```

时间复杂度 $O(nlogn)$。

---

## 作者：kkxacj (赞：2)

#### 思路

假设我们选的等差数列为 $i$ 到 $i+k-1$，那么将这些数都选择后的序列跨度为**在原序列中数 $p_i$ 的值在 $i$ 到 $i+k-1$ 中最后出现的位置减去最开始出现的位置**，很容易想到维护两个 `st` 表维护最大值最小值，然后枚举选的等差数列，去最小值就完了。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	template<typename T>
	void Read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void Read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,k,x,a[300010],ans,id[300010],st[300010][50],st1[300010][60],lg[300010];
signed main()
{
	Read(n),Read(k);
	for(int i = 2;i <= n;i++) lg[i] = lg[i / 2] + 1;
	for(int i = 1;i <= n;i++) Read(a[i]),id[a[i]] = i,st[a[i]][0] = i,st1[a[i]][0] = i;
	for(int i = 1;i <= lg[n];i++)
		for(int j = 1;j + (1 << (i - 1)) - 1 <= n;j++)
			st[j][i] = min(st[j][i - 1],st[j + (1 << (i - 1))][i - 1]);
	for(int i = 1;i <= lg[n];i++)
		for(int j = 1;j + (1 << (i - 1)) - 1 <= n;j++)
			st1[j][i] = max(st1[j][i - 1],st1[j + (1 << (i - 1))][i - 1]);
	ans = n-1;
	for(int i = 1;i <= n - k + 1;i++)
	{
		x = lg[k];
		ans = min(ans,max(st1[i][x],st1[i+k - (1 << x)][x]) - min(st[i][x],st[i+k - (1 << x)][x]));
	} 
	print(ans);
	flush();
	return 0;
}

```

---

## 作者：Frank08 (赞：1)

## 思路

预处理出所有 $P_i$ 的下标，即 $S_{P_i} = i$。

然后对于每个长度为 $K$ 的区间最大最小值的差取最小值即为答案。

以上操作可以使用 set 维护答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k,p[200002],s[200002];
set <int> v; 

int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++)
		scanf("%d",&p[i]), s[p[i]] = i;
	int ans = n + 1;
	for(int i = 1;i <= k;i++)
		v.insert(s[i]);
	for(int i = 1,j = k;j <= n;i++,j++){
		auto v_end = v.end(); v_end--;
		ans = min(ans,*v_end - *v.begin());
		v.erase(s[i]); v.insert(s[j + 1]);
	}
	printf("%d",ans);
}
```

---

## 作者：c1ampy (赞：1)

### 题意简述

给定一个 $ 1 $ 到 $ N $ 的**排列** $ P $ 与一个整数 $ K $。

一个长度为 $ K $ 的序列 $ \left(i_1, i_2, \dots, i_K\right) $ 是**好序列**当且仅当：

- $ 1 \le i_1 < i_2 < \dots < i_K \le N $。

- 序列 $ \left(P_{i_1}, P_{i_2}, \dots, P_{i_K}\right) $ 可以被重排为 $ K $ 个**连续整数**。形式化地讲，存在一个整数 $ a $ 使得 $ \{P_{i_1}, P_{i_2}, \dots, P_{i_K}\} = \{a, a + 1, \dots, a + K - 1\} $。

求出 $ i_K - i_1 $ 的**最小值**。可以证明在任何情况下都至少存在一个好序列。

$ 1 \le K \le N \le 2 \times 10^5 $。

### 解法分析

稍作转换，本题可以转化为求最短的包含至少 $ K $ 个连续整数的 $ P $ 的连续子序列的长度 $ L $，最终的答案即为 $ L - 1 $。

不难发现有以下事实：

- 对于一个包含至少 $ K $ 个连续整数的 $ P $ 的连续子序列 $ S $，如果 $ T $ 也是 $ P $ 的连续子序列且 $ S $ 是 $ T $ 的连续子序列，则 $ T $ 同样包含至少 $ K $ 个连续整数。

根据以上事实，易知本题的答案满足单调性，故我们考虑二分答案，本题可转化为如下问题：

- 判断 $ P $ 中是否存在包含至少 $ K $ 个连续整数的长度为 $ L $ 的连续子序列。

可以使用滑动窗口逐一判断所有的 $ N - L + 1 $ 个长度为 $ L $ 的连续子序列是否包含至少 $ K $ 个连续整数。

我们使用一个长度为 $ N $ 的序列 $ A $ 作为桶，来记录每个整数是否在当前的滑动窗口中出现。$ A_i = 1 $ 表示整数 $ i $ 在滑动窗口中出现，$ A_i = 0 $ 反之。

滑动窗口每次移动之后，我们只需查询序列 $ A $ 中最长的连续的 $ 1 $ 的长度是否大于等于 $ K $，这个信息可以使用线段树维护。

对于每个线段树结点对应的区间，我们维护当前区间最长的连续的 $ 1 $ 的长度 $ max $，当前区间靠左的最长的连续的 $ 1 $ 的长度 $ lmax $，当前区间靠右的最长的连续的 $ 1 $ 的长度 $ rmax $。这些信息可以以如下方式自底向上传递：

```cpp
void push_up() {
	this->lmax = this->lc->lmax + (this->lc->max == this->lc->len ? this->rc->lmax : 0);
	this->rmax = this->rc->rmax + (this->rc->max == this->rc->len ? this->lc->rmax : 0);
	this->max = std::max(std::max(this->lc->max, this->rc->max), this->lc->rmax + this->rc->lmax);
}
```

对维护方法更详细的介绍参见 [P2572 [SCOI2010] 序列操作](https://www.luogu.com.cn/problem/P2572)。

每个数进入滑动窗口最多 $ 1 $ 次，弹出滑动窗口最多 $ 1 $ 次，故进入与弹出的总次数是 $ \mathcal{O} \left(n\right) $ 的，每次进入与弹出滑动窗口的时间复杂度为 $ \mathcal{O} \left(\log n\right) $，每次查询的时间复杂度为 $ \mathcal{O} \left(1\right) $，故单次判断的时间复杂度为 $ \mathcal{O} \left(n \log n\right) $，总时间复杂度为 $ \mathcal{O} \left(n \log^2 n\right) $。

### 代码实现

```cpp
#include <iostream>
#include <vector>

class SegmentTree {
	
	struct Node {
		
		Node *lc, *rc;
		int l, r, len;
		int lmax, rmax, max;
		
		Node(const int l, const int r)
		: lc(nullptr), rc(nullptr), l(l), r(r), len(r - l + 1), lmax(0), rmax(0), max(0) {}
		
		void modify(const int value) {
			this->lmax = this->rmax = this->max = value;
		}

		void push_up() {
			this->lmax = this->lc->lmax + (this->lc->max == this->lc->len ? this->rc->lmax : 0);
			this->rmax = this->rc->rmax + (this->rc->max == this->rc->len ? this->lc->rmax : 0);
			this->max = std::max(std::max(this->lc->max, this->rc->max), this->lc->rmax + this->rc->lmax);
		}
	};
	
	Node *root;
	
	void build(Node *&cur, const int l, const int r) {
		cur = new Node(l, r);
		if (l == r) return;
		
		int mid = (l + r) >> 1;
		build(cur->lc, l, mid);
		build(cur->rc, mid + 1, r);
	}
	
	void del(Node *&cur) {
		if (!cur) return;
		del(cur->lc), del(cur->rc);
		delete cur;
		cur = nullptr;
	}

	void modify(Node *cur, const int idx, const int value) {
		if (cur->l == cur->r) {
			cur->modify(value);
			return;
		}
		
		int mid = (cur->l + cur->r) >> 1;
		modify(idx <= mid ? cur->lc : cur->rc, idx, value);
		cur->push_up();
	}

public:
	
	SegmentTree(const int n) : root(nullptr) {
		build(root, 1, n);
	}
	
	~SegmentTree() {
		del(root);
	}

	void modify(const int idx, const int value) {
		modify(root, idx, value);
	}
	
	int query() const {
		return root->max;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int n, k; std::cin >> n >> k;
	std::vector<int> p(n + 1);
	for (int i = 1; i <= n; ++i)
		std::cin >> p[i];
	
	const auto check = [&](const int l) -> bool {
		SegmentTree a(n);
		for (int i = 1; i <= n; ++i) {
			a.modify(p[i], 1);
			if (a.query() >= k)
				return true;
			if (i > l)
				a.modify(p[i - l], 0);
		}
		return false;
	};
	
	int l = k - 2, r = n;
	while (r - l > 1) {
		int mid = (l + r) >> 1;
		check(mid) ? r = mid : l = mid;
	}
	
	std::cout << r << '\n';
	
	return 0;
}
```

---

## 作者：RioFutaba (赞：1)

## 题意
给定 $n$、$k$ 和一个 $1$ 到 $n$ 的排列 $p$。求排序后成为一个公差为 $1$ 的等差数列的 $p$ 的子序列中，子序列最大下标与最小下标的差的最小值。
## 思路
首先我们设任意一个 $i$（$1 \le i \le n$）在 $p$ 中的下标为 $a_i$。

求出 $a$ 的每一个长度为 $k$ 的连续子序列中的最大值减去最小值然后取最小的就是答案了。这一过程可以用单调队列优化。

因为 $n$ 是 $2 \times 10^5$ 规模的，所以也可以用 st 表和线段树等 $O(n \log n$) 的做法。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

//D
const int maxn=2e5+5;
int n,k,p[maxn],a[maxn];
deque<int> q1,q2;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
		a[p[i]]=i;
	}
	int ans=n;//答案最大为n-1 
	for(int i=1;i<=n;i++){//单调队列模板 
		while(!q1.empty() && q1.front()<=i-k) q1.pop_front();
		while(!q1.empty() && a[q1.back()]>a[i]) q1.pop_back();
		q1.push_back(i);
		while(!q2.empty() && q2.front()<=i-k) q2.pop_front();
		while(!q2.empty() && a[q2.back()]<a[i]) q2.pop_back();
		q2.push_back(i);
		if(i>=k) ans=min(ans,a[q2.front()]-a[q1.front()]);//统计答案 
	}
	printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：kevinZ99 (赞：1)

# 前言

好水，但是 $E$ 我没打暴力，啊啊啊。

# 简化题意

在长度为 $n$ 的序列 $a$ 中，找出连续 $k$ 个数的下标，将这其中的最大与最小的下标做差，到最小值。

# 具体思路

很明显，先看数据范围，性质？

每一个数字只会出现一次！

那这就很容易了，开一个桶 $b$。

```b[i]``` 表示数字 $i$ 在第 ```b[i]``` 个 。

接着对于 $b$ 数组构建 线段树/st表/单调队列/ 。

然后枚举一个 $i$ 表示若我们选择 $\left[ i , i+k-1 \right]$ 这段区间答案是多少，接着对于这段区间进行查询即可。

# 代码code

代码比较单纯，两个线段树，因为我板子里打了线段树，所以直接拷贝过来用。

```cpp
//Author:Kevin Z K Y
#include <bits/stdc++.h>
#define putendl putchar('\n')
#define putspace putchar(' ')
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
#define fst first
#define sed second
using namespace std;
using ll = long long ;
using hint = __int128 ;
using pii = pair<int,int> ;
using pll = pair<ll,ll> ;
using vi = vector<int> ;
using vl = vector<ll> ;
using vpi = vector<pair<int,int>> ;
using db = double ;
const double eps=1e-6;
namespace IO{
//	#define gc() getchar_unlocked()
	#define gc() getchar()
	ll max(ll x,ll y){return x>=y?x:y;}
    ll min(ll x,ll y){return x<=y?x:y;}
    ll abs(ll x){return x<=0?-x:x;}
	double fabs(double x){return x<=-eps?-x:x;}
	template<typename T>
	void writei(T x){if(x<0)putchar('-'),x=-x;int index_output=0;char s[40];do{s[index_output++]=x%10+48,x/=10;}while(x);while(index_output)putchar(s[--index_output]);}
	template<typename T>
	void writeis(T x,char c){writei(x);putchar(c);}
	void writess(string &s,int start){int index_output=start;while(s[index_output]!='\0')putchar(s[index_output++]);}
	void writesse(string &s,int start,int end){int index_output=start;while(s[index_output]!='\0'&&index_output<end+1)putchar(s[index_output++]);}
}
using namespace IO;
namespace my{
	const int N=(int)(2e5+5);
	string ot;
	int n;
	int a[N];
	int b[N];
	struct segment_tree_max{
		int mx[(N<<2)],t[(N<<2)];
		#define mid ((l+r)/2)
		int ls(int p){return p*2;}
		int rs(int p){return p*2+1;}
		void push_up(int p){mx[p]=max(mx[ls(p)],mx[rs(p)]);}
		void add_tag(int x,int p){mx[p]+=x;t[p]+=x;}
		void push_down(int p){
			if(t[p]==0)return ;
			add_tag(t[p],ls(p));add_tag(t[p],rs(p));
			t[p]=0;
		}
		void build(int l,int r,int p){
			if(l==r){
				mx[p]=b[l];
				t[p]=0;
				return ;
			}
			build(l,mid,ls(p));build(mid+1,r,rs(p));
			push_up(p);
		}
		void add(int l,int r,int L,int R,int x,int p){
			if(r<L||l>R)return ;
			if(l>=L&&r<=R){
				add_tag(x,p);
				return ;
			}
			push_down(p);
			add(l,mid,L,R,x,ls(p));add(mid+1,r,L,R,x,rs(p));
			push_up(p);
		}
		int ask(int l,int r,int L,int R,int p){
			if(r<L||l>R)return -INT_MAX;
			if(l>=L&&r<=R)return mx[p];
			push_down(p);
			return max(ask(l,mid,L,R,ls(p)),ask(mid+1,r,L,R,rs(p)));
		}
	};
	struct segment_tree_min{
		int mx[(N<<2)],t[(N<<2)];
		#define mid ((l+r)/2)
		int ls(int p){return p*2;}
		int rs(int p){return p*2+1;}
		void push_up(int p){mx[p]=min(mx[ls(p)],mx[rs(p)]);}
		void add_tag(int x,int p){mx[p]+=x;t[p]+=x;}
		void push_down(int p){
			if(t[p]==0)return ;
			add_tag(t[p],ls(p));add_tag(t[p],rs(p));
			t[p]=0;
		}
		void build(int l,int r,int p){
			if(l==r){
				mx[p]=b[l];
				t[p]=0;
				return ;
			}
			build(l,mid,ls(p));build(mid+1,r,rs(p));
			push_up(p);
		}
		void add(int l,int r,int L,int R,int x,int p){
			if(r<L||l>R)return ;
			if(l>=L&&r<=R){
				add_tag(x,p);
				return ;
			}
			push_down(p);
			add(l,mid,L,R,x,ls(p));add(mid+1,r,L,R,x,rs(p));
			push_up(p);
		}
		int ask(int l,int r,int L,int R,int p){
			if(r<L||l>R)return INT_MAX;
			if(l>=L&&r<=R)return mx[p];
			push_down(p);
			return min(ask(l,mid,L,R,ls(p)),ask(mid+1,r,L,R,rs(p)));
		}
	};
	int k;
	void solve(){
		cin>>n>>k;
		up(i,1,n){
			cin>>a[i];
			b[a[i]]=i;
		}if(k==1){
			cout<<'0'<<'\n';
			return ;
		}
		segment_tree_max t;t.build(1,N,1);
		segment_tree_min m;m.build(1,N,1);
		int ans=1e9+114514;
		up(i,1,n-k+1)
			ans=min(ans,abs(t.ask(1,N,i,i+k-1,1)-m.ask(1,N,i,i+k-1,1)));
		
		cout<<ans<<'\n';
	}
}
int main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int _=1;
	while(_--)my::solve();return 0;
}

```

---

## 作者：xxboyxx (赞：1)

## 提供一种平衡树做法

### 翻译

给定一个序列，再此序列中找到一个长度为 $m$ 的子序列，满足子序列为连续的 $k$ 整数，求这些子序列两端在原序列中的位置的差的最小值为多少。

### 思路

我们对原序列做一个桶，保存每个值所在的位置，这样问题就可以转换成每次挪动一个区间，求这个区间中的最大与最小值的差。构造一棵平衡树，先加入 $1\sim m-1$ 的位置，然后对于 $m\sim n$ 的区间挪动操作，设当前位置为 $x$，那么就加入 $x$ 的位置，求排名为 $1$ 和 $m$ 的数值，删除 $x-m+1$ 的位置，这样就完成了一次挪动。

### 注意

桶中存储的是位置，不要弄混淆了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int v,k,l,r,s;
};
node tree[1000005];
int a[200005];
int b[200005];
int n,m,minn=1e18;
int tot=0,root=0;
int newnode(int v)
{
	tree[++tot].v=v;
	tree[tot].k=rand();
	tree[tot].s=1;
	return tot;
}
void pushup(int p)
{
	tree[p].s=tree[tree[p].l].s+tree[tree[p].r].s+1;
}
void split(int p,int v,int &x,int &y)//裸的FHQ平衡树 
{
	if (p==0)
	{
		x=0,y=0;
		return;
	}
	if (tree[p].v<=v)
	{
		x=p;
		split(tree[p].r,v,tree[p].r,y);
	}
	else
	{
		y=p;
		split(tree[p].l,v,x,tree[p].l);
	}
	pushup(p);
}
int merge(int x,int y)
{
	if (!x || !y)
		return x+y;
	if (tree[x].k<tree[y].k)
	{
		tree[x].r=merge(tree[x].r,y);
		pushup(x);
		return x;
	}
	else
	{
		tree[y].l=merge(x,tree[y].l);
		pushup(y);
		return y;
	}
}
void ins(int v)
{
	int x,y,z;
	split(root,v,x,y);
	z=newnode(v);
	root=merge(merge(x,z),y);
}
void del(int v)
{
	int x,y,z;
	split(root,v,x,z);
	split(x,v-1,x,y);
	y=merge(tree[y].l,tree[y].r);
	root=merge(merge(x,y),z);
}
int get_k(int p,int k)
{
	if (k<=tree[tree[p].l].s)
		return get_k(tree[p].l,k);
	if (k==tree[tree[p].l].s+1)
		return p;
	return get_k(tree[p].r,k-tree[tree[p].l].s-1);
}
int get_p(int v)
{
	int x,y,ans;
	split(root,v-1,x,y);
	ans=tree[x].s+1;
	root=merge(x,y);
	return ans;
}
int get_s(int v)
{
	int k,ans;
	k=get_k(root,v);
	ans=tree[k].v;
	return ans;
}
signed main()
{
	srand(time(0));
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]=i;//加入桶 
	}
	for (int i=1;i<m;i++)
		ins(b[i]);
	for (int i=m;i<=n;i++)
	{
		ins(b[i]);//插入头部 
		int x=get_s(1);//最左边的位置 
		int y=get_s(m);//最右边的位置 
		if (y-x<minn)
			minn=y-x;
		del(b[i-m+1]);//删除尾部 
	}
	cout<<minn;
	return 0;
}
```

### 总结

本题正解是单点队列，但是用于平衡树练手还是不错的，但是码量比较大，细节比较多。

---

## 作者：FinderHT (赞：1)

### 题意简述

给你一个长度为 $n$ 的排列 $P$，定义好索引序列为任意选 $k$ 个数 $i_1,i_2,\dots,i_k$，使得 $1\le i_1<i_2<\dots<i_k$ 且 $(P_{i_1},P_{i_2},\dots,P{i_k})$ 经过排序后是一段连续的正整数。求出所有好索引序列中 $i_k-i_1$ 的最小值。

### 思路

提供一个线段树做法。

因为 $P$ 是一个排列，所以 $1\sim n$ 中的每个数都会在其中出现一次（重要条件）。

由此我们可以用一个数组 $pos$ 将 $P$ 中每个数的出现位置都记录下来，并建到线段树里。我们枚举 $1\sim n-k+1$，每次取出一段长度为 $k$ 的区间，代表 $k$ 个连续的整数，然后用线段树求 $pos$ 数组对应区间中的最大值和最小值，维护答案即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long
#define ull unsigned long long
#define lowbit(x) x&(-x)
#define fst first
#define snd second
#define L(x) x<<1
#define R(x) x<<1|1
using namespace std;
typedef pair<int,int> pii;
const double eps=1e-6;
inline bool pts(char ch){return ch>=48&&ch<=57;}
inline int read(){
	bool f=0;int x=0;char ch;
	ch=gt();
	while(!pts(ch)&&ch!=EOF){if(ch=='-')f=1;ch=gt();}
	while(pts(ch)){x*=10;x+=(ch-48);ch=gt();}
	if(f)return -x;
	else return x;
}
template<class T>
inline void print(T x){
	char s[114];
	int top=0;
	if(x<0)pt('-');
	do{
		top++;
		if(x>=0)s[top]=(x%10)+48;
		else s[top]=(-(x%10)+48);
		x/=10;
	}while(x);
	while(top){pt(s[top]);top--;}
}
int p[200005];
struct SegmentTree{
	int l,r;
	int lazy;
    int maxn,minx;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define maxn(x) tree[x].maxn
    #define minx(x) tree[x].minx
	#define lazy(x) tree[x].lazy
}tree[800005];
void pushup(int p){
	minx(p)=min(minx(L(p)),minx(R(p)));
    maxn(p)=max(maxn(L(p)),maxn(R(p)));
}
int pos[200005];
void build(int p,int l,int r){
	l(p)=l;
	r(p)=r;
	if(l==r){
		minx(p)=maxn(p)=pos[r];
		return;
	}
	int mid=(l+r)>>1;
	build(L(p),l,mid);
	build(R(p),mid+1,r);
  	pushup(p);
}
int getmax(int p,int l,int r){
	if(l(p)>=l&&r(p)<=r)
		return maxn(p);
    int ans=-1e18;
	if(r(L(p))>=l)
		ans=max(ans,getmax(L(p),l,r));
	if(l(R(p))<=r)
		ans=max(ans,getmax(R(p),l,r));
	return ans;  
}
int getmin(int p,int l,int r){
	if(l(p)>=l&&r(p)<=r)
		return minx(p);
    int ans=1e18;
	if(r(L(p))>=l)
		ans=min(ans,getmin(L(p),l,r));
	if(l(R(p))<=r)
		ans=min(ans,getmin(R(p),l,r));
	return ans;  
}
signed main(){
	int n=read(),k=read();
    for(int i=1;i<=n;i++){
    	p[i]=read();
    	pos[p[i]]=i;
	}
    build(1,1,n);
    int mans=INT_MAX;
    for(int i=1;i+k-1<=n;i++){
        int l=i,r=i+k-1;
        mans=min(mans,getmax(1,l,r)-getmin(1,l,r));
    }
    cout<<mans;
	return 0;
}
```

---

## 作者：FreedomKing (赞：1)

set 板子题。

### 思路

看到题第一眼感觉是类似于滑动窗口的东西。

设一个数组 $f$ 来记录 $i$ 在 $P$ 中出现的下标，每次截取一段长为 $k$ 的区间，这段 $l,r$ 区间的贡献就是 $\max\{f_x\}-\min\{f_x\},(l\le x\le r)$。考虑使用 set 维护这个窗口即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int xN=1e7+5,N=2e5+5,mN=1e3+5,mod=1e9+7;
namespace FreedomKing_qwq{
	//#define lc (p<<1)
	//#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abss(int x){return (x>=0?x:-x);}
	inline int lowbit(int x){return (x&-x);}
//	int fa[N];
//	inline void init(int x){
//		for(int i=1;i<=x;i++) fa[i]=i;
//		return;
//	}
//	inline int find(int x){
//		return (fa[x]==x?x:fa[x]=find(fa[x]));
//	}
//	inline void update(int x,int y){
//		x=find(x);y=find(y);
//		fa[y]=x;
//		return;
//	}
}
int a[N],f[N];
set<int>st;
signed main(){
	int n=qr,m=qr;
	for(int i=1;i<=n;i++){
		a[i]=qr;
		f[a[i]]=i;
	}
	int ans=LONG_LONG_MAX;
	for(int i=1;i<=n;i++){
		st.insert(f[i]);
		if(i<m) continue;
		st.erase(f[i-m]);
		ans=min(ans,*st.rbegin()-*st.begin());
	}
	qw(ans);
	return 0;
}
```

---

## 作者：Size_OIer (赞：1)

## 题意  
给定一个长度为 $ N $ 无序数列，定义一种特殊子序列，它是连续的 $ K  $个整数的一种排列，它的权值为在原序列中位置的极差。  
请你求最小的权值。
## 分析
记录下每个元素的大小和位置，然后根据大小排个序，再做个滑动窗口，窗口内比较的是原来所在位置的最大值与最小值，最后取答案就行了。  
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200000+5;
struct node{
	int x,id;
}a[maxn];
int n,k,ans=0x3f3f3f3f;
int q1[maxn],q2[maxn];
int l1,r1,l2,r2;
inline bool cmp(node x,node y){
	return x.x<y.x;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmp);
	l1=l2=1;
	r1=r2=0;
	for(int i=1;i<=n;i++) {
		while(l1<=r1&&i-q1[l1]>=k) l1++;
		while(l2<=r2&&i-q2[l2]>=k) l2++;
		while(l1<=r1&&a[q1[r1]].id<a[i].id) r1--;
		while(l2<=r2&&a[q2[r2]].id>a[i].id) r2--;
		q1[++r1]=i;
		q2[++r2]=i;
		if(i>=k) ans=min(ans,a[q1[l1]].id-a[q2[l2]].id);
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：CQBZ_ZJYjoe (赞：1)

[link](https://atcoder.jp/contests/abc352/tasks/abc352_d)

# 题目思路
本题题目比较难懂，总结一下就是：

- 要你在给定序列 $P$ 里选出一个长度为 $K$ 的子序列。
- 这个子序列从小到大排列后要为连续自然数。
- 这个序列在原数组最大下标减最小下标的差最小。

输出一下最大下标减最小下标最小的差即可。

因为本题保证原序列是 $N$ 的排列，所以我是用平衡树和 set 去维护答案的。

# 代码实现
```cpp
//FHQ Treap
#include<bits/stdc++.h>
using namespace std;
int root,n,cnt,k,a[200005],b[200005];
set<int> q;
struct Node
{
	int lson,rson,val,key,siz;
}tree[200005];
inline int newnode(int x)
{
	tree[++cnt].val=x;
	tree[cnt].key=rand()+1;
	tree[cnt].siz=1;
	return cnt;
}
inline void update(int x)
{
	tree[x].siz=tree[tree[x].lson].siz+tree[tree[x].rson].siz+1;
}
inline void split(int x,int v,int &a,int &b)
{
	if (x==0)
	{
		a=b=0;
		return ;
	}
	if (tree[x].val<=v)
	{
		a=x;
		split(tree[a].rson,v,tree[a].rson,b);
		update(a);
	}
	else
	{
		b=x;
		split(tree[b].lson,v,a,tree[b].lson);
		update(b);
	}
}
inline int merge(int x,int y)
{
	if (!x||!y)
		return x+y;
	if (tree[x].key<tree[y].key)
	{
		tree[x].rson=merge(tree[x].rson,y);
		update(x);
		return x;
	}
	else
	{
		tree[y].lson=merge(x,tree[y].lson);
		update(y);
		return y;
	}
}
inline void insert(int x)
{
	int a,b;
	split(root,x,a,b);
	root=merge(merge(a,newnode(x)),b);
}
inline int ask_val(int x,int k)
{
	if (tree[tree[x].lson].siz+1==k)
		return tree[x].val;
	else if (tree[tree[x].lson].siz+1>k)
		return ask_val(tree[x].lson,k);
	else 
		return ask_val(tree[x].rson,k-tree[tree[x].lson].siz-1);
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for (int i=1;i<=n;i++)
		cin>>a[i],insert(a[i]),b[a[i]]=i;
	int ans=0,ma=0,mi=2e9;
	for (int i=1;i<=k;i++)
		q.insert(b[ask_val(root,i)]);
	auto tx=q.end(),xt=q.begin();
	ans=*(--tx) - *xt;//set中begin() 最小,(--end())最大,使用*获得值
	for (int i=k+1;i<=n;i++)
	{
		q.erase(b[ask_val(root,i-k)]);
		q.insert(b[ask_val(root,i)]);//寻找满足要求的子序列
		tx=q.end(),xt=q.begin();
		ans=min(ans,*(--tx) - *xt);
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Abczzzzz (赞：1)

考虑暴力枚举所有 $n-k+1$ 个符合要求的子序列来找最优解，第 $i$ 次的结果为 $i$ 到 $i+k-1$ 中位置最大值减位置最小值。发现与滑动窗口问题相似，可以处理出每个数的位置，再用单调队列处理。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[1000000+5];
struct node
{
	int id;
	int v;
};
deque<node> q;
int maxn[1000000+5];
int minn[1000000+5];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int ssss;
		scanf("%d",&ssss);
		a[ssss]=i;
	}for(int i=1;i<=n;i++)
	{
		while((!q.empty())&&q.back().v>a[i]) q.pop_back();
		while((!q.empty())&&q.front().id<i-k+1) q.pop_front();
		q.push_back(node{i,a[i]});
		if(i>=k)maxn[i]=q.front().v;
	}
	while(!q.empty()) q.pop_back();
	for(int i=1;i<=n;i++)
	{
		while((!q.empty())&&q.back().v<a[i]) q.pop_back();
		while((!q.empty())&&q.front().id<i-k+1) q.pop_front();
		q.push_back(node{i,a[i]});
		if(i>=k)minn[i]=q.front().v;
	}
	int ans=2e9;
	for(int i=k;i<=n;i++)
	{
		ans=min(ans,minn[i]-maxn[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：2023lpx (赞：1)

# AT_abc352_d [ABC352D] Permutation Subsequence 题解

## 题目大意

给你一串 $1,2,3,\dots,N$ 的排列 $P$，让你从 $P$ 中选出数字连续的 $K$ 个，求所有能选的组合中在原数组最大下标减最小下标的差最小的值。

## 思路

其实这道题有[原题](https://www.luogu.com.cn/problem/P1886)。

用类似的思路，用单调队列维护区间下标最大最小值即可。

## code

```cpp
#include<cstdio>
using namespace std;
#define int long long
int k,n;
int p[2000010];
int s[2000010];
int t[2000010];
int q1[2000010];
int q2[2000010];
int h1,h2;
int t1,t2;
int ans;
int min(int a,int b){
	return a<b?a:b;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&p[i]);
		s[p[i]]=i;
	}
	for(int i=1;i<=n;i++){
		t[i]=s[i];
	}
	h1=1;
	t1=0;
	h2=1;
	t2=0;
	ans=n*k;
	for(int i=1;i<=n;i++){
		while(h1<=t1&&q1[h1]+k<=i)h1++;
		while(h1<=t1&&t[q1[t1]]>t[i])t1--;
		q1[++t1]=i;
		while(h2<=t2&&q2[h2]+k<=i)h2++;
		while(h2<=t2&&t[q2[t2]]<t[i])t2--;
		q2[++t2]=i;
		if(i>=k){
//			printf("%d %d %d\n",t[q2[h2]]-t[q1[h1]],q2[h2],q1[h1]);
			ans=min(ans,t[q2[h2]]-t[q1[h1]]);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Hughpig (赞：0)

发现 $\{P_i,P_{i+1},\dots,P_{i+k-1}\}$ 和 $\{P_{i+1},P_{i+2},\dots,P_{i+k}\}$ 之间只存在一处差异，因此每次找最大值中其实只有一个元素是不同的。

所以可以用单调队列维护区间最大值和最小值，每次将 $P_i$ 出队，$P_{i+k}$ 入队即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k,a[200007],p[200007],l=1,r,q[200007],q2[200007],minn[200007],ans=INT_MAX;

void in(int x){
	while(r>=l&&p[x]<=p[q[r]])r--;
	++r;
	q[r]=x;
}

void in2(int x){
	while(r>=l&&p[x]>=p[q2[r]])r--;
	++r;
	q2[r]=x;
}

int main()
{
    up(1,n,i)cin>>a[i],p[a[i]]=i;
    for(int i=1;i<k;++i)in(i);//单调队列维护最小值。
    for(int i=k;i<=n;++i){
    	in(i);
    	minn[i]=p[q[l]];
    	if(q[l]==i-k+1)++l;
	}
	l=1,r=0;
	for(int i=1;i<k;++i)in2(i);//单调队列维护最大值。
	for(int i=k;i<=n;++i){
		in2(i);
		ans=min(ans,p[q2[l]]-minn[i]);//找到最小的极差。
		if(q2[l]==i-k+1)++l;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# AT_abc352_d

## 解题思路

由题意得，我们需要求出原数列中 $a\sim a+k-1$ 这几个数下标的极差。

我们只需要保存下每个数的下标，然后枚举起点 $a$，求出该区间内的极差即可，单调队列之类的 RMQ 算法均可，~~由于单调队列我写的不是很熟，~~ 我赛时写的 st 表，复杂度在预处理方面会多一个 $\log$。

[code](https://atcoder.jp/contests/abc352/submissions/53119105)

```cpp
// Problem: D - Permutation Subsequence
// Contest: AtCoder - AtCoder Beginner Contest 352
// URL: https://atcoder.jp/contests/abc352/tasks/abc352_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-05-04 20:15:28

#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,k,a[N],p[N];
int stmax[N][50];
int stmin[N][50];
int qry_max(int l,int r){
	int k=__lg(r-l+1);
	return max(stmax[l][k],stmax[r-(1<<k)+1][k]);
}
int qry_min(int l,int r){
	int k=__lg(r-l+1);
	return min(stmin[l][k],stmin[r-(1<<k)+1][k]);
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		stmax[a[i]][0]=p[a[i]]=i;
		stmin[a[i]][0]=p[a[i]]=i;
	}
	for(int k=1;k<=30;k++)
		for(int i=1;i+(1<<k)-1<=n;i++)
			stmax[i][k]=max(stmax[i][k-1],stmax[i+(1<<(k-1))][k-1]),
			stmin[i][k]=min(stmin[i][k-1],stmin[i+(1<<(k-1))][k-1]);
	int ans=INT_MAX;
	for(int i=1;i+k-1<=n;i++)
		ans=min(ans,qry_max(i,i+k-1)-qry_min(i,i+k-1));
	cout<<ans;
	return 0;
}

```

---

## 作者：pangyou3s (赞：0)

因为本题是要找到好索引序列中 $i_k - i_1$ 的最小值，我们可以找到所有好索引序列的 $i_k - i_1$ 后再枚举最小值。
由于题目规定“子序列 $(Pi_1,Pi_2,…,Pi_K)$ 可以通过重新排列一些连续的 $K$ 整数而得到,”
我们可以记录输入的序列各个元素的下标，再将输入序列排序。这样只需枚举长度为 $k$ 的滑动窗口内的最大值和最小值之差即可，这里可以用 $\rm deque$ 来实现。
- 维护最小值的 $\rm deque$ $\rm (minDeque)$ 为单调递增：遇到比当前元素大的元素就弹出，保证队列中的元素是按照从小到大排序的。
- 维护最大值的 $\rm deque$ $\rm (maxDeque)$ 为单调递减：遇到比当前元素小的元素就弹出，保证队列中的元素是按照从大到小排序的。

遍历数组 $a$，依次将元素加入两个 $\rm deque$ 中，并维护窗口大小为 $k$。
当窗口大小达到 $k$ 时，计算当前窗口内的最大值和最小值，并更新答案。时间复杂度为 $O(n)$

![](https://s21.ax1x.com/2024/05/05/pkA5iHf.png)

```cpp
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    
    sort(a.begin(), a.end()); // 按照第一个值进行从小到大排序
    
    deque<int> minDeque, maxDeque;
    int ans = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        // 维护最小值的deque（单调递增）
        while (!minDeque.empty() && a[minDeque.back()].second > a[i].second) {
            minDeque.pop_back();
        }
        minDeque.push_back(i);
        
        // 维护最大值的deque（单调递减）
        while (!maxDeque.empty() && a[maxDeque.back()].second < a[i].second) {
            maxDeque.pop_back();
        }
        maxDeque.push_back(i);
        
        // 维护窗口大小为k
        if (i >= k - 1) {
            // 当前窗口的最小值
            while (minDeque.front() < i - k + 1) {
                minDeque.pop_front();
            }
            int min_val = a[minDeque.front()].second;
            
            // 当前窗口的最大值
            while (maxDeque.front() < i - k + 1) {
                maxDeque.pop_front();
            }
            int max_val = a[maxDeque.front()].second;
            
            // 计算当前窗口的最大值和最小值之差
            int t = max_val - min_val;
            ans = min(ans, t);
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
```

---

## 作者：Spark_King (赞：0)

# ABC_352_D题解

## 题意翻译

给你一个长度为 $N$ 的数列 $P$，要从中选取一个长度为 $K$ 的子序列，且要求该子序列内的数在排序后是**连续的整数**，求这个子序列中**元素下标的极差的最小值**。

## 题目分析

乍一看题目很难懂，我们通过第三个样例分析一下：

输入样例：
```
10 5
10 1 6 8 7 2 5 9 3 4
```
输出样例：
```
5
```

根据题目要求，我们可以从中取子序列为：$6$ $8$ $7$ $5$ $9$（排序后为：$5$ $6$ $7$ $8$ $9$），不难看出此时**最大下标**为 $8$，**最小下标**为 $3$，**差**为 $5$。

清楚了题意之后，我们开始思考做法：

首先，我们可以将每一个数字**对应的下标**存下来，像这样：
```
数字：1 2 3 4 5 6 7 8 9 10
下标：2 6 9 10 7 3 5 4 8 1
```
由于我们要找连续整数数列，所以我们可以在**下标数组中**枚举每一个长度为  $K$ 的**连续子序列**，然后从中**取最大和最小值做差**，其中最小的就是答案。

这里的区间操作我选择用 ST 表维护。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,k;
ll p[200010];
ll pos[200010];
ll maxn[200010][20],minn[200010][20];//两个ST表
ll ans=1e18;
ll queryax(ll x,ll y)
{
	ll k=log2(y-x+1);
	return max(maxn[x][k],maxn[y-(1<<k)+1][k]);
}
ll queryin(ll x,ll y)
{
	ll k=log2(y-x+1);
	return min(minn[x][k],minn[y-(1<<k)+1][k]);	
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(ll i=1;i<=n;i++)
	{
		cin>>p[i];
		pos[p[i]]=i;
		maxn[p[i]][0]=i,minn[p[i]][0]=i;//预处理
	}
	for(ll j=1;j<=18;j++)//注意这里log2(2e5)约等于17.6
	{
		for(ll i=1;i+(1<<j)-1<=n;i++)
		{
			maxn[i][j]=max(maxn[i][j-1],maxn[i+(1<<(j-1))][j-1]);
			minn[i][j]=min(minn[i][j-1],minn[i+(1<<(j-1))][j-1]);
		}
	}
	for(ll i=1;i+k-1<=n;i++) ans=min(ans,queryax(i,i+k-1)-queryin(i,i+k-1));
	cout<<ans;//处理答案输出
	return 0;
}
```

---

## 作者：xiaofu15191 (赞：0)

考虑将原数组排序，这样就可以保证子序列 $[i,i+k-1]$ 是连续的等差数列。

于是对数组中每个数进行编号，直接维护区间编号最大与最小值。用线段树等数据结构维护。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	long long num,i;
}p[200010];
bool cmp(node t1,node t2)
{
	return t1.num<t2.num;
}
long long n,k,tree[800010][2];
void build(long long now,long long l,long long r)
{
	if(l==r)
	{
		tree[now][0]=tree[now][1]=p[l].i;
		return;
	}
	long long mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
	tree[now][0]=max(tree[now<<1][0],tree[now<<1|1][0]);
	tree[now][1]=min(tree[now<<1][1],tree[now<<1|1][1]);
}
long long find_max(long long now,long long l,long long r,long long x,long long y)
{
	if(r<x||l>y) return 0;
	if(x<=l&&r<=y) return tree[now][0];
	long long mid=(l+r)>>1,result=0;
	if(x<=mid) result=max(result,find_max(now<<1,l,mid,x,y));
	if(y>mid) result=max(result,find_max(now<<1|1,mid+1,r,x,y));
	return result;
}
long long find_min(long long now,long long l,long long r,long long x,long long y)
{
	if(r<x||l>y) return 0x3f3f3f3f;
	if(x<=l&&r<=y) return tree[now][1];
	long long mid=(l+r)>>1,result=0x3f3f3f3f;
	if(x<=mid) result=min(result,find_min(now<<1,l,mid,x,y));
	if(y>mid) result=min(result,find_min(now<<1|1,mid+1,r,x,y));
	return result;
}
int main()
{
	scanf("%lld%lld",&n,&k);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&p[i].num);
		p[i].i=i;
	}
	sort(p+1,p+n+1,cmp);
	long long ans=0x3f3f3f3f;
	build(1,1,n);
	for(long long i=1;i+k-1<=n;i++)
		ans=min(ans,find_max(1,1,n,i,i+k-1)-find_min(1,1,n,i,i+k-1));
	printf("%lld\n",ans);
}
```

---

## 作者：Annihilation_y (赞：0)

### 题目翻译
给你一个整数 $n$，以及 $n$ 个数，满足这 $n$ 个数是 $1 \sim n$ 的一个排列。现在让你在这 $n$ 个数中选 $k$ 个数，满足这 $k$ 个数中最大值减去最小值刚好为 $k-1$。求所有的 $n-k+1$ 种选数方案中，下标最靠右的数减去下标最靠左的数的最小值。

### 思路
转换一下思路，用 $b$ 数组表示值为 $1 \sim n$ 的位置。那么问题就转换成了，对于 $b$ 数组的每一个 $i \sim i+k-1$ ，求区间最大值和最小值，我们用 RMQ 来维护。

### Code
~~~c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int a[MAXN],b[MAXN],RMQ[MAXN][25],RMQ_MIN[MAXN][25];
int n,k,sum=0;
int Ask(int l,int r){
	int x=int(log(r-l+1)/log(2));
	return max(RMQ[l][x],RMQ[r-(1<<x)+1][x]);
}
int Ask_Min(int l,int r){
	int x=int(log(r-l+1)/log(2));
	return min(RMQ_MIN[l][x],RMQ_MIN[r-(1<<x)+1][x]);
}
void ST(){
	for(int i=1;i<=n;i++){
		RMQ[i][0]=b[i];
		RMQ_MIN[i][0]=b[i];
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			RMQ[i][j]=max(RMQ[i][j-1],RMQ[i+(1<<(j-1))][j-1]);
			RMQ_MIN[i][j]=min(RMQ_MIN[i][j-1],RMQ_MIN[i+(1<<(j-1))][j-1]);
		}
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]=i;
	ST();
	int Min=INT_MAX/3;
	for(int i=1;i<=n-k+1;i++){
		Min=min(Min,Ask(i,i+k-1)-Ask_Min(i,i+k-1));
	}
	cout<<Min<<endl;
	return 0;
}
~~~

---

## 作者：OIer_Tan (赞：0)

为什么不能场切，自闭自闭自闭。\fn\
下次我再做不出 AT 的题，一半的原因来自于翻译。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_d)

## 题意

给你一个 $(1, 2, \dots, N)$ 的排列组合 $P = (P_1, P_2, \dots, P_N)$。

如果一个索引序列 $(i_1, i_2, \dots, i_K)$ 同时满足以下两个条件，那么它就是一个好的索引序列：

- $1 \leq i_1 < i_2 < \dots < i_K \leq N$。
- 子序列 $(P_{i_1}, P_{i_2}, \dots, P_{i _K})$ 可以通过重新排列一些连续的 $K$ 整数而得到。形式上，存在一个整数 $a$，使得 $\lbrace P_{i_1},P_{i_2},\dots,P_{i_K} \rbrace = \lbrace a,a+1,\dots,a+K-1 \rbrace$。

求所有好的索引序列中 $i_K - i_1$ 的最小值。可以证明，在此问题的约束条件下，至少存在一个好的索引序列。

## 思路

现在我们定义数组 $b={b_1,b_2,b_3,\cdots,b_n}$ 为存储 $P$ 中每个元素的位置，即 $b_{p_i}=i$。\
因此，上面的问题可以重新理解成：

- $b_a,b_{a+1},\dots,b_{a+K-1}$ 的最大值与最小值之差。

然后考虑使用 [滑动窗口](https://www.luogu.com.cn/problem/P1886) 的思路来做。如果你喜欢用 `set`，带一只 $\log$ 也可以过。

总复杂度为 $O(N)$ 或 $O(N\log K)$。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , k , p [N] , b [N] , ans ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> k ;
	set <ll> st ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> p [i] ;
		b [p [i]] = i ;
	}
	for ( ll i = 1 ; i <= k ; i ++ )
	{
		st.insert ( b [i] ) ;
	}
	ll ans = ( * st.rbegin () ) - ( * st.begin () ) ;
	for ( ll i = k + 1 ; i <= n ; i ++ )
	{
		st.erase ( st.find ( b [i - k] ) ) ;
		st.insert ( b [i] ) ;
		ans = min ( ans , ( * st.rbegin () ) - ( * st.begin () ) ) ;
	}
	cout << ans << endl ;
	return 0 ;
} 
```

---

## 作者：Vitamin_B (赞：0)

# 思路
蒟蒻不会平衡树，只能使用单调队列力。

先用 $mp_i$ 表示数字 $i$ 在原数组中的位置，然后像滑动窗口一样，$q_1$ 维护这 $k$ 个数字内位置最靠前的数，$q_2$ 维护位置最靠后的数，然后两个数减一减就是距离，取 $\min$ 即可。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
int n, k, x, mp[200005], minx = 1919810;
deque <int> q1, q2;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> k;
	for (int i = 0; i < n; ++ i)
		cin >> x, mp[x] = i;
	for (int i = 1; i <= n; ++ i) {
		while (! q1.empty () && mp[q1.front ()] <= mp[i])
			q1.pop_front ();
		while (! q2.empty () && mp[q2.front ()] >= mp[i])
			q2.pop_front ();
		q1.push_front (i);
		q2.push_front (i);
		while (! q1.empty () && q1.back () <= i - k)
			q1.pop_back ();
		while (! q2.empty () && q2.back () <= i - k)
			q2.pop_back ();
		if (i >= k)
			minx = min (minx, mp[q1.back ()] - mp[q2.back ()]);
	}
	cout << minx << '\n';
	return 0;
}
```

---

## 作者：xixisuper (赞：0)

# AT_abc352_d [ABC352D] Permutation Subsequence 题解

为什么要用平衡树呢？是我单调队列不香吗？

建议添加标签：单调队列。

建议评价难度：黄 or 绿。

## 思路

我们考虑把每一种可能的子序列情况都统计一遍。

对于每一种情况，我们需要找到这 $K$ 个数中**最先出现的位置与最后出现的位置**。我们可以把这个问题转换一下，用一个桶来存每一个数出现的位置，于是问题变成了这个桶**连续 $K$ 个数中最大的一个数与最小的一个数**，这不就是滑动窗口吗？直接单调队列走起。

不会单调队列的移步[P1886单调队列](https://www.luogu.com.cn/problem/P1886)题解区。

详细地，我们可以建立两个单调队列，一个单调递增，一个单调递减，分别用于维护区间最小值与最大值。对于第 $i$ 种情况，我们设其最大值为 $mx_i$，最小值为 $mn_i$，则最后答案为 $\max(mx_i-mn_i)$。

总共需要两步操作，先用桶存下来，再用单调队列统计，总时间复杂度为 $O(n)$。

## 代码

蒟蒻代码，不喜勿喷。

```cpp
#include <iostream>
#define ll int
using namespace std;
const ll N=2e5+10;
ll dddl_mn[N],dddl_mx[N],tong[N],nums[N];
ll rear_mn,rear_mx,front_mn,front_mx;
ll n,k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(ll i=1;i<=n;i++){
		cin>>nums[i];
		tong[nums[i]]=i;
	}
	front_mn=rear_mn=front_mx=rear_mx=0;
	for(ll i=1;i<k;i++){
		if(front_mn==rear_mn) dddl_mn[rear_mn++]=i;
		else{
			while(front_mn<rear_mn&&tong[i]<tong[dddl_mn[rear_mn-1]]){
				rear_mn--;
			}
			dddl_mn[rear_mn++]=i;
		}
		if(front_mx==rear_mx) dddl_mx[rear_mx++]=i;
		else{
			while(front_mx<rear_mx&&tong[i]>tong[dddl_mx[rear_mx-1]]){
				rear_mx--;
			}
			dddl_mx[rear_mx++]=i;
		}
	}
	ll ans=2147483647;
	for(ll i=k;i<=n;i++){
		if(front_mn==rear_mn) dddl_mn[rear_mn++]=i;
		else{
			while(front_mn<rear_mn&&tong[i]<tong[dddl_mn[rear_mn-1]]){
				rear_mn--;
			}
			dddl_mn[rear_mn++]=i;
		}
		if(front_mx==rear_mx) dddl_mx[rear_mx++]=i;
		else{
			while(front_mx<rear_mx&&tong[i]>tong[dddl_mx[rear_mx-1]]){
				rear_mx--;
			}
			dddl_mx[rear_mx++]=i;
		}
		ans=min(tong[dddl_mx[front_mx]]-tong[dddl_mn[front_mn]],ans);
		if(i<n){
			if(dddl_mx[front_mx]<=i-k+1) front_mx++;
			if(dddl_mn[front_mn]<=i-k+1) front_mn++;
		}
	}
	cout<<ans;
	return 0; 
}
```

---

## 作者：zengziqvan (赞：0)

本题乍一看很难考虑。

但我们发现：问题等价于找一个最小长度区间，使这个区间至少含有 $k$ 个连续的数。

可以用一个数组 cnt 存储每个数字出现的位置。

这样问题就转化成了一个长度为 $k$ 的区间 $[l,r]$，这样区间内所有数字对应在原序列上的位置就表示原序列中凑出 $[l,r]$ 所有数字需要选择的位置集合。

这些位置的最大值即为选择的 $i_k$，最小值即为 $i_1$。

问题转化成在 cnt 数组中找长度为 $k$ 的子段，使子段中的最大值减去最小值最小。

这个问题显然可以类比 [滑动窗口](https://www.luogu.com.cn/problem/P1886)。

单调队列 $\operatorname{O}(n)$、线段树、ST 表 $\operatorname{O}(n\log n)$ 均可解决上述问题。

这里写的是 ST 表。

```c++
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define FOR(i,l,r) for(int i=l;i<=r;++i)
#define ROF(i,r,l) for(int i=r;i>=l;--i)
#define mkp make_pair
#define fr first
#define se second
#define pb push_back
using namespace std;
int n,k,a[200010],ans=1e9,Max=-1,Min=1e9,cnt[200010];
int dp[200010][50],f[200010][50];
int AMx(int l,int r) {
	int k=log(r-l+1)/log(2);
	return max(dp[l][k],dp[r-(1<<k)+1][k]);
}
int AMn(int l,int r) {
	int k=log(r-l+1)/log(2);
	return min(f[l][k],f[r-(1<<k)+1][k]);
}
main() {
	cin>>n>>k;
	FOR(i,1,n) cin>>a[i],cnt[a[i]]=i;
	FOR(i,1,n) dp[i][0]=f[i][0]=cnt[i];
	int t=log(n)/log(2);
	FOR(j,1,t) FOR(i,1,n-(1<<j)+1) {
		dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
		f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	} 
	FOR(i,0,n-k) {
		int l=i+1,r=i+k;
		ans=min(ans,AMx(l,r)-AMn(l,r));
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc352_d)

## 题目大意

给定一个 $1$ 到 $N$ 的排列 $P$，还有一个整数 $K$。

你可以选出 $K$ 个下标 $(i_1,i_2,\dots,i_K)$，满足 $1 \le i_1 < i_2 < \dots < i_K \le N$。然后这些下标在 $P$ 中对应的元素组成一个数列 $A$（即 $A = \{ P_{i_1}, P_{i_2}, \dots, P_{i_K}\}$）。

如果将 $A$ 排序后得到的数列相邻两项都相差 $1$，那么这些下标 $(i_1,i_2,\dots,i_K)$ 就被称为 $P$ 的“好的索引”。

求 $P$ 所有“好的索引”中 $i_K - i_1$ 的最小值。

## 题解

首先将 $P$ 排序，并记录下每个数在排序前的位置，数字 $x$ 记为 $\text{pos}_x$。由于 $P$ 是排列，那么每个 $\text{pos}_x$ 都是唯一的。

此时，我们无论选择序列上任何 $[i, i + K)$ 的区间的数组成的数列相邻两项差都为 $1$，也就是说它们的下标就是 $P$ 的“好的索引”。

所以，要求这个最小值，只要求出 $\text{pos}$ 在 $[i, i + K)$ 中的最大值减去最小值（也就是序列中的数的最大位置减去最小位置）。

这个我们用 $\text{ST}$ 表维护一下就好了。时间复杂度 $O(n \log n)$，记得考虑 $\text{ST}$ 表的初始化的赋值。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

struct node{ int a, id; } a[N];
int n, k, ans = 2e5 + 5;
bool cmp( node x, node y ){ return x.a < y.a; }

int stmx[N][25], stmn[N][25], lg2[N];

void stpre(){
	for( int i = 2; i <= n; ++i ) lg2[i] = lg2[i >> 1] + 1;
	for( int i = 1; i <= lg2[n] + 1; ++i ){
		for( int j = 1; j <= n && j + ( 1 << ( i - 1 ) ) - 1 <= n; ++j ){
			stmx[j][i] = max( stmx[j][i - 1], stmx[j + ( 1 << ( i - 1 ) )][i - 1] );
			stmn[j][i] = min( stmn[j][i - 1], stmn[j + ( 1 << ( i - 1 ) )][i - 1] );
//			printf( "%d %d %d %d\n", j, j + ( 1 << i ) - 1, stmx[j][i], stmn[j][i] );
		}
	}
}

int dis( int l, int r ){
	return max( stmx[l][lg2[r - l + 1]], stmx[r - ( 1 << lg2[r - l + 1] ) + 1][lg2[r - l + 1]] ) - min ( stmn[l][lg2[r - l + 1]], stmn[r - ( 1 << lg2[r - l + 1] ) + 1][lg2[r - l + 1]] );
}

int main(){
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; ++i ){
		scanf( "%d", &a[i].a ); a[i].id = i;
	}
	sort( a + 1, a + n + 1, cmp );
	memset( stmn, 0x7f, sizeof stmn );
	for( int i = 1; i <= n; ++i ) stmx[i][0] = a[i].id, stmn[i][0] = a[i].id;
	stpre();
	for( int i = 1; i + k - 1 <= n; ++i )ans = min( ans, dis( i, i + k - 1 ) );
	printf( "%d", ans );
	return 0;
}
```

---

## 作者：codingwen (赞：0)

## 题目描述

给你一个 $ (1,2,\dots,N) $ 的排列 $ P=(P_1,P_2,\dots,P_N) $.

当一个序列 $ K=(i_1,i_2,\dots,i_K) $ 是“好的”，当且仅当：

- $ 1\leq\ i_1\ <\ i_2\ <\ \dots\ <\ i_K\ \leq\ N $
- $ (P_{i_1},P_{i_2},\dots,P_{i_K}) $ 可以通过 $ X=(a,a+1,\dots,a+K-1) $ 重排得到。   

求一个序列 $ K^\prime $，使得它是“好的”，且 $ i_K-i_1 $ 的值尽可能小，只需输出这个最小值即可。


## 前置

注意到它求的是数而不是位置，所以我们对一个指定的区间  $(l,l+1,l+2,\dots,r)$，它的答案就是（这些数在 $P$ 数组中的下标最大值 $-$ 这些数在 $P$ 数组中的下标最小值）。


## 方法一 暴力模拟
时间复杂度 $\Theta(kn^2)$

直接枚举开始的 $a$，然后根据开始的数值一次递增到 $a+k-1$，对于每个要查找的数，直接暴力查找数所在的位置，分别取最大最小值再进行减法，最后统计答案。

代码就不放了（因为过于暴力）

## 方法二 使用下标数组

时间复杂度 $\Theta(kn)$

注意到每次数的位置都是固定的，所以先开一个数组 $a$，让 $a_i$ 存储 $i$ 在原数组里的位置。这样在查找的时候就可以省去一重循环。

核心代码：
```cpp
int ans=1e6;
for(int i=1;i<=n-k+1;i++){
    int mx=0,mn=1e6;
    for(int j=i;j<=i+k-1;j++){
        mx=max(mx,a[j]);
        mn=min(mn,a[j]);
    }
    ans=min(ans,mx-mn);
}
```

## 方法三 线段树（赛时方法）

 注意到我们是求一个区间的最大最小值，所以我~~异想天开地~~想到了线段树。直接套模板即可（变量要修改）。
 
 赛时代码：
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int a[200010];
int n,k;
struct segment{
	int l,r;
	int mx,mn;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define mx(x) tree[x].mx
	#define mn(x) tree[x].mn
}tree[800010];
void build(int p,int l,int r){
	l(p)=l;
	r(p)=r;
	if(l==r){
		mx(p)=mn(p)=a[l];
		return ;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	mx(p)=max(mx(p*2),mx(p*2+1));
	mn(p)=min(mn(p*2),mn(p*2+1));
}
int ask_max(int p,int l,int r){
	if(l<=l(p) && r>=r(p))return mx(p);
	int mid=(l(p)+r(p))/2,ans=0;
	if(l<=mid)ans=max(ans,ask_max(p*2,l,r));
	if(r>mid)ans=max(ans,ask_max(p*2+1,l,r));
	return ans;
}
int ask_min(int p,int l,int r){
	if(l<=l(p) && r>=r(p))return mn(p);
	int mid=(l(p)+r(p))/2,ans=1e6;
	if(l<=mid)ans=min(ans,ask_min(p*2,l,r));
	if(r>mid)ans=min(ans,ask_min(p*2+1,l,r));
	return ans;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a[x]=i;
	}
	build(1,1,n);
	int res=1e6;
	for(int i=1;i<=n-k+1;i++)res=min(res,ask_max(1,i,i+k-1)-ask_min(1,i,i+k-1));
	cout<<res;
	return 0;
} 
 ```
 
 时间复杂度：线段树的询问是 $\Theta(logn)$ 的，外面再套一层 $\Theta(n)$ 的枚举，总时间复杂度 $\Theta(nlogn)$。
 
## 方法四 单调队列

时间复杂度 $\Theta(n)$。   

求最大最小值？那不就是[滑动窗口](https://www.luogu.com.cn/problem/P1886)吗？  
直接用单调队列模板，稍改一下就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],s[1000010],mx[1000010],mn[1000010];
int main(){
    int n,k,p,q;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
    	int x;
    	cin>>x;
    	a[x]=i;
    }
    for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
    p=q=0;
    for(int i=1;i<=n;i++){
        if(i-s[p]>=k)p++;
        while(p<=q && a[i]<=a[s[q]])q--;
        q++;
        s[q]=i;
        if(i>=k)mn[i-k+1]=a[s[p]];
    }
    p=q=0;
    for(int i=1;i<=n;i++){
        if(i-s[p]>=k)p++;
        while(p<=q && a[i]>=a[s[q]])q--;
        q++;
        s[q]=i;
        if(i>=k)mx[i-k+1]=a[s[p]];
    }
    int ans=1e6;
    for(int i=1;i<=n-k+1;i++)ans=min(ans,mx[i]-mn[i]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

比较容易想到，我们可以先统计出对于所有 $1\le i\le n$，$i$ 在排列中出现的位置，然后枚举 $1$ 到 $n$ 中每一个长度为 $K$ 的区间，计算这段区间在排列中出现位置的最大值和最小值的差，即为这段区间的跨度。在这些值中取最小值输出即可。

考虑用一个数据结构维护这个信息。每遍历下一个区间时，将上一个区间的左端点在结构中删掉，再将右端点的后一位加入结构。使用线段树或单调队列等都可以实现。这里使用了线段树。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005];
int f1[1000005],f2[1000005];
unordered_map<int,int> ma;
void build(int root,int l,int r){//给最小值赋初值为正无穷
	if(l==r){ f2[root]=0x3f3f3f3f;return; }
	int mid=(l+r)>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	f2[root]=min(f2[root<<1],f2[root<<1|1]);
}
void update(int root,int l,int r,int k,int x){//增加或删掉一个元素。注意删除时要把最小值归为正无穷
	if(l==r){ f1[root]=x,f2[root]=(x==0?0x3f3f3f3f:x);return; }
	int mid=(l+r)>>1;
	if(k<=mid) update(root<<1,l,mid,k,x);
	else update(root<<1|1,mid+1,r,k,x);
	f1[root]=max(f1[root<<1],f1[root<<1|1]);
	f2[root]=min(f2[root<<1],f2[root<<1|1]);
}
int Find1(int root,int l,int r,int fl,int fr){//找区间最大值
	if(fl<=l&&r<=fr) return f1[root];
	int mid=(l+r)>>1,maxn=0;
	if(fl<=mid) maxn=max(maxn,Find1(root<<1,l,mid,fl,fr));
	if(fr>mid) maxn=max(maxn,Find1(root<<1|1,mid+1,r,fl,fr));
	return maxn;
}
int Find2(int root,int l,int r,int fl,int fr){//找区间最小值
	if(fl<=l&&r<=fr) return f2[root];
	int mid=(l+r)>>1,maxn=0x3f3f3f3f;
	if(fl<=mid) maxn=min(maxn,Find2(root<<1,l,mid,fl,fr));
	if(fr>mid) maxn=min(maxn,Find2(root<<1|1,mid+1,r,fl,fr));
	return maxn;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=n;i++) ma[a[i]]=i;
	for(int i=1;i<=m;i++) update(1,1,n,i,ma[i]);
	int minn=0x3f3f3f3f;
	for(int i=m;i<=n;i++){
		minn=min(minn,Find1(1,1,n,1,i)-Find2(1,1,n,1,i));
		update(1,1,n,i-m+1,0);
		update(1,1,n,i+1,ma[i+1]);
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

# ABC352D

前置芝士：线段树。

## 题意

给定长度为 $N$ 的排列  $P = (P_1,P_2,\dots,P_N)$，选一个长度为 $K$ 的索引序列 $i_1,i_2,\dots,i_K$（$1\le i_1<i_2<\dots<i_K\le N$）且 $\exists a\in\N^*$，使得 $\{P_{i_1},P_{i_2},\dots,P_{i_K}\}=\{a,a+1,\dots,a+K-1\}$。求符合要求的 $i$ 的 $i_K-i_1$ 的最小值。

## 分析 & 解题

先预处理每个值在原排列里的位置 $pos_v$。

考虑枚举每一个权值区间 $[1,K]\sim[n-k+1,K]$，由于是集合相等，**不要求有序**，可以对于每一个权值区间，使用这段区间各个元素在原排列里的位置的最大值，减去这段区间各个元素在原排列里的位置的最小值。

暴力时间复杂度为 $O(n^2)$，如何优化？

发现每次最大最小值查询的区域是一段连续的区间，符合线段树的区间查询操作。

使用线段数维护区间最大值、区间最小值即可。

由于不涉及修改，也可以使用 ST 表等等。

*[Code](https://www.luogu.com.cn/paste/ejnuog60)*

---

## 作者：封禁用户 (赞：0)

感觉题目描述有点绕。


# 思路

如果知道 $a$，那么其实答案就是 $a\sim a+k-1$ 这一段**数字的位置**的极差。

令 $p_{a_i}= i$，即 $a_i$ 这个数字的位置。

发现其实题目要求的就是 $p_i\sim p_{i+k-1}$ 这个区间极差的最大值。

枚举 $i$，此时如果暴力统计最大最小求极差的话总体复杂度为 $O(nk)$ 无法接受，考虑优化。

~~你可以使用st表线段树树状数组等冲过去~~。

反正是静态的，做法很多。

因为 $i$ 每次加 $1$ 时 $p_i\sim p_{i+k-1}$ 这个区间会向右移动一个，所以我用了滑动窗口计算极差，随后取最小。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=2e5+10;
int ma[N],mi[N];
int num[N];
int q[N],a[N];
int head,tail;
int n,k,x;
il void solve()
{
	n=read(),k=read();
	F(i,1,n) x=read(),a[x]=i;
	head=1,tail=1;
	for(int i=1;i<=n;i++)//记录最小值
	{
		while(num[head]<i-k+1&&head<=tail) head++;
		while(a[i]<q[tail]&&head<=tail) tail--;
		q[++tail]=a[i];
		num[tail]=i;
		mi[i]=q[head];
	}
	head=1,tail=1;
	for(int i=1;i<=n;i++)//记录最大值
	{
		while(num[head]<i-k+1&&head<=tail) head++;
		while(a[i]>q[tail]&&head<=tail) tail--;
		q[++tail]=a[i];
		num[tail]=i;
		ma[i]=q[head];
	}
  	int res=inf;
	F(i,k,n) res=MIN(res,ma[i]-mi[i]);//计算极差
	put(res);
}
int main()
{
    int T=1;
//    T=read();
    while(T--) solve();
    return 0;
}
```

---

## 作者：__Floze3__ (赞：0)

## 思路简述

简单题。

我们考虑枚举连续的一串整数，不难发现答案即为这些数下标的最大值减去下标的最小值。所以我们只需要不断地从中删除第一个数的下标，并插入下一个数的下标。我们可以用 set 很容易的做到这一点，但赛时写了线段树。

## 完整代码

[赛时提交记录](https://atcoder.jp/contests/abc352/submissions/53104458)

---

## 作者：PikachuQAQ (赞：0)

## Description

给定一个长为 $n$ 的序列，选取其中长为 $k$ 的子序列，使得其中的值满足 $[a,a+1,a+2,...,a+k-1]$，$a$ 为非负整数。

$1 \le n \le 2\times10^5$，$1\le k\le n$。

## Solution

可以造一个下表序列 $b_i$，其中 $b_{a_i}=i$。

对于上文子序列 $[i,i+1,i+2,...,i+k-1](i+k-1\le n)$，将 $i$ 从 $1$ 到 $n$ 逐个遍历，也就是找出所有子序列。找每个子序列中的元素的 $b_i$ 最大值和最小值，将它们作差，取其中最小值。

对于找出子序列中最大下标和最小下标的差值，暴力复杂度为 $O(n)$，可以使用线段树将复杂度降到 $O(\log n)$。

总复杂度 $O(n \log n)$，此题得解。

## Code

```cpp
// 2024/5/5 PikachuQAQ

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kN = 2e5 + 1, kM = kN << 2;

int n, k, a[kN], b[kN], ans = 1e9;
int seg1[kM], seg2[kM];

void pushup1(int p) {
    seg1[p] = max(seg1[p << 1], seg1[p << 1 | 1]);
}

void pushup2(int p) {
    seg2[p] = min(seg2[p << 1], seg2[p << 1 | 1]);
}

void Build(int l, int r, int p) {
    int mid = l + r >> 1;
    if (l == r) {
        seg1[p] = seg2[p] = b[l];
    } else {
        Build(l, mid, p << 1), Build(mid + 1, r, p << 1 | 1);
        pushup1(p), pushup2(p);
    }
}

int Query1(int l, int r, int p, int s, int t) {
    int res = 0, mid = l + r >> 1;
    if (s <= l && r <= t) {
        return seg1[p];
    }
    if (s <= mid) res = max(res, Query1(l, mid, p << 1, s, t));
    if (mid + 1 <= t) res = max(res, Query1(mid + 1, r, p << 1 | 1, s, t));
    return res;
}

int Query2(int l, int r, int p, int s, int t) {
    int res = 1e9, mid = l + r >> 1;
    if (s <= l && r <= t) {
        return seg2[p];
    }
    if (s <= mid) res = min(res, Query2(l, mid, p << 1, s, t));
    if (mid + 1 <= t) res = min(res, Query2(mid + 1, r, p << 1 | 1, s, t));
    return res;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[a[i]] = i;
    }
    Build(1, n, 1);
    for (int l = 1, r = l + k - 1; r <= n; l++, r++) {
        ans = min(ans, Query1(1, n, 1, l, r) - Query2(1, n, 1, l, r));
    }
    cout << ans;

    return 0;
}
```

---

## 作者：lfxxx_ (赞：0)

## 思路
- 用一个数组 $pos_i$ 记录数字 $i$ 出现的位置，然后我们需要查询从 $i$ 到 $i+k-1$ 之间最大的位置减去最小的位置，然后去最小值即可
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n;
int a[N],st[2][N][21],LOG2[N],pos[N];
void build()
{
	LOG2[0]=-1;
	for(int i=1;i<=n;++i)
		LOG2[i]=LOG2[i/2]+1;	
	for(int i=1;i<=n;++i)
	{
	
		st[0][i][0]=st[1][i][0]=pos[i];	
	}
	for(int j=1;j<=LOG2[n];++j)
		for(int i=1;i+(1<<j)-1<=n;++i)
		{
			st[0][i][j]=max(st[0][i][j-1],st[0][i+(1<<j-1)][j-1]);
			st[1][i][j]=min(st[1][i][j-1],st[1][i+(1<<j-1)][j-1]);
		}
}
int query(int l,int r)
{
	int k=LOG2[r-l+1]; 
	return max(st[0][l][k],st[0][r-(1<<k)+1][k])-min(st[1][l][k],st[1][r-(1<<k)+1][k]);
}
signed main()
{
	int k;
	cin>>n>>k;
	for(int i=1;i<=n;++i)
		cin>>a[i],pos[a[i]]=i;
	build();
	int ans=1e18;
	for(int i=1;i+k-1<=n;++i)
	{
		ans=min(ans,query(i,i+k-1));
//		cout<<i<<'-'<<i+k-1<<':'<<query(i,i+k-1)<<'\n';
	}
	cout<<ans;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析

注意到题目并没有要求 $i_1,i_2,\dots,i_K$ 连续，并且给出的 $p$ 是 $1,2,\dots,N$ 的排列，因此我们将 $p$ 排序后每一组连续的 $K$ 个数一定是连续的 $K$ 个整数。所以，我们只需要维护每一个长度为 $K$ 的区间 $[L,R]$ 对应的原数组编号的最大值与最小值就行了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=2e5;
int n,k,p[maxn+5];

void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		p[x]=i;
	}
	
	set<int>st;
	for(int i=1;i<=k;i++) st.insert(p[i]);
	
	int ans=1e9;
	for(int i=1;i+k-1<=n;i++){
		ans=min(ans,*(--st.end())-*st.begin());
		st.erase(st.find(p[i]));st.insert(p[i+k]);
	}
	
	cout<<ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：0)

一道较为简单的题，建议评黄。

不难发现数列 $i$ 是单调递增的，且长度为 $K$
，那么意味着对于每个 $a$，$i_k-i_1$ 的值即为 $a$ 到 $a+K-1$ 之间的整数出现位置的最大值和最小值之差，而题目让我们最小化这个差。

考虑用 $p_v$ 表示 $v$ 的出现位置，最小差值即为：
$$
\min_{a=1}^{N-K+1}(\max_{j=a}^{a+K-1}p_j-\min_{j=a}^{a+K-1}p_j)
$$

如果直接暴力计算，那么时间复杂度为 $O(NK)$，无法通过此题。

但我们可以使用 ST 表维护数列 $p$，这样预处理的时间复杂度为 $O(N\log N)$，计算答案的时间复杂度为 $O(N)$，可以通过此题。

[Submission Link.](https://atcoder.jp/contests/abc352/submissions/53125060)

---

## 作者：lilong (赞：0)

看到题目后，第一反应便是暴力枚举确定 $i$。但是看到了 $N \le 2 \times 10^5$，这种想法便不合适了。观察题目第二个条件，不难发现其实真正合法的方案很少。于是可以转变方向，枚举**题目要求的排列集合**。

想到这步，接下来就不难了。确定好原排列中被选的数后，需要求出**它们的下标**的最小值和最大值。又由于这些数本身是连续的，因此可以**用这些数作为下标**，存储**它们原先的下标**。这样做就把这些下标集中在一起了，转换为区间最值查询问题，用各种数据结构维护即可。

以下采用 ST 表实现，时间复杂度 $O( n \log n )$。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

int n,k,p,ans,a[1000001],st1[1000001][20],st2[1000001][20],lg[1000001];

void rd( void )
{
	for( int j = 1 ; j <= 19 ; j ++ )
		for( int i = 1 ; i + ( 1 << ( j - 1 ) ) <= n ; i ++ )
		{
			st1[i][j] = max( st1[i][j - 1] , st1[i + ( 1 << ( j - 1 ) )][j - 1] );
			st2[i][j] = min( st2[i][j - 1] , st2[i + ( 1 << ( j - 1 ) )][j - 1] );
		}
}

int query( int l , int r )
{
	int d = lg[r - l + 1];
	int ans1 = max( st1[l][d] , st1[r - ( 1 << d ) + 1][d] );
	int ans2 = min( st2[l][d] , st2[r - ( 1 << d ) + 1][d] );
	return abs( ans1 - ans2 );
}

signed main()
{
	cin >> n >> k;
	for( int i = 2 ; i <= n ; i ++ )
		lg[i] = lg[i >> 1] + 1;
	for( int i = 1 ; i <= n ; i ++ )
	{
		cin >> p;
		a[p] = i;
		st1[p][0] = st2[p][0] = i;
	}
	rd();
	ans = n;
	for( int i = 1 ; i + k - 1 <= n ; i ++ )
		ans = min( ans , query( i , i + k - 1 ) );
	cout << ans;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_d)

## 思路

线段树做法比较好想。

我们读入数据后排序，保证整个序列都是“良好序列”。记录此时每个数是开始时的哪个数（即此时序列 $\{P_{i_1},P_{i_2},...,P_{i_K}\}$ 对应读入时的数的位置 $\{i_1,i_2,...,i_K\}$）。

将这些位置保存在线段树中，然后从 $1$ 到 $N-K+1$ 循环，循环到 $i$ 时查找序列 $\{i,i+1,...,i+K-1\}$ 中最大的数 $-$ 减最小的数（也就是序列 $P$ 最大值位置 $-$ 最小值位置）。这些结果中最小的结果即为最小的 $i_K-i_1$。

线段树优化后时间复杂度 $\mathcal{O}(N\log N)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
int n,k,ans=1e9;//先赋个极大值，之后找最小。
struct segment_tree{
	int l,r,mi,ma;
}tr[N<<2];
pii a[N];//pair 方便排序。
void pushup(int i){//pushup 两个，一个最大值一个最小值。
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);
	tr[i].mi=min(tr[i<<1].mi,tr[i<<1|1].mi);
	return ;
}
void build(int i,int l,int r){
	tr[i].l=l;
	tr[i].r=r;
	if(l==r){
		tr[i].mi=tr[i].ma=a[l].se;//记录叶子节点最大值、最小值都是这个位置。
		return ;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	pushup(i);
	return ;
}
int qmax(int i,int l,int r){//找最大值。
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].ma;
	int mid=tr[i].l+tr[i].r>>1,res=-1e9;
	if(l<=mid)res=qmax(i<<1,l,r);
	if(mid<r)res=max(res,qmax(i<<1|1,l,r));
	return res;
}
int qmin(int i,int l,int r){//找最小值。
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].mi;
	int mid=tr[i].l+tr[i].r>>1,res=1e9;
	if(l<=mid)res=qmin(i<<1,l,r);
	if(mid<r)res=min(res,qmin(i<<1|1,l,r));
	return res;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i].fi;
		a[i].se=i;
	}
	sort(a+1,a+1+n);//先排序。
	build(1,1,n);
	for(int i=1;i<=n-k+1;++i){
		int ma=qmax(1,i,i+k-1);
		int mi=qmin(1,i,i+k-1);
		ans=min(ans,ma-mi);//记录最小差值。
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/158053271)

---

## 作者：CheZiHe929 (赞：0)

### 简要题意

给你一个 $1$ 到 $n$ 的排列 $p$，并定义良好序列为含有连续 $k$ 个数的序列，求 $p$ 的子序列（不要求连续）中所有良好序列在 $p$ 中位置的极差的最小值。

### 简要思路

根据良好序列的定义，我们将 $p$ 按照权值排序，以便于良好序列的查找，并维护其在 $p$ 中原先的位置。

此时我们再分析，会发现按照权值排序之后，我们要求的每个良好序列的位置的极差就是排序后每个长度为 $k$ 的序列的位置的极差。

据此，我们不难想到滑动窗口（单调队列），将滑动的序列的值设为按权值排序后每个点在 $p$ 中原先的位置。

### 完整代码

```xpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=2e5+5;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

int n,k;
struct node{
	int val,loc;//val-权值 loc-位置 
}a[MAXN];

bool cmp(node a,node b){return a.val<b.val;}

struct queuee{//单调队列 
	int z[MAXN],head,tail;
	queuee(){//初始化 
		head=1,tail=0;
		memset(z,0,sizeof(z));
	}
	void push1(int x){//保证单调递增的插入 
		while(head<=tail&&a[x].loc<=a[z[tail]].loc)tail--;
		z[++tail]=x;
	}
	void push2(int x){//保证单调递减的插入 
		while(head<=tail&&a[x].loc>=a[z[tail]].loc)tail--;
		z[++tail]=x;
	}
	void pop(){head++;}
	int front(){return z[head];}
	int size(){return tail-head+1;}
}q1,q2;//分别求最小值和最大值 

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i].val=read();
		a[i].loc=i;
	}
	
	std::sort(a+1,a+n+1,cmp);//按照权值从小到大排序
	 
	for(int i=1;i<=k;i++)
		q1.push1(i),q2.push2(i);//先将第一个长度为 k 的窗口 push 进队列，并将其赋为 minn 的初始值
		 
	int minn=a[q2.front()].loc-a[q1.front()].loc;
	for(int i=1;i<=n-k+1;i++){
		q1.push1(i+k-1);
		q2.push2(i+k-1);//窗口向后移 
		if(q1.front()==i-1)q1.pop();
		if(q2.front()==i-1)q2.pop();//看当前最小/大值是否已经不在当前窗口中 
		minn=std::min(minn,a[q2.front()].loc-a[q1.front()].loc);//维护最小的极差 
	}
	println(minn);
	
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

毫无技术的简单题。

我们转化一下题意中的两个条件：

- 能重排使得序列递增。
- $\{p_{i_1},p_{i_2},p_{i_3},\cdots,p_{i_k}\}=\{x,x+1,x+2,\cdots,x+k-1\}$。

答案为 $\max\limits_{i=1}^k p_i-\min\limits_{i=1}^k p_i$。

很显然第一条是总是能实现的，那么只剩第二条了。

设 $b_i$ 为 $i$ 在 $p_i$ 中的位置，那很显然，$b$ 中连续子序列都是满足条件的。

那么很显然答案就为 $b$ 中所有连续子序列中的最大 $-$ 最小值。

可以用 ST 表或单调队列或线段树解决。

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_d)
## 思路
命 $p_i$ 为数为 $i$ 所在的位置，那么 $1$ 到 $n$ 中长度为 $k$ 的区间的答案就是 $p$ 的最大值减去 $p$ 的最小值，最后从这些区间中选出最小值作为答案。
## 做法
对于区间最值我们可以用 set 维护，我这里用了两个 set 维护。先将前 $1$ 到 $k - 1$ 的位置与对应值存在 pair 里然后放进 set，每当删除一个数时就将它的位置与它的值存成的 pair 删掉，加一个数时就加进去。具体看代码。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
I n,k,p[200010],r[200010];
set<pair<I,I>>x,y;//维护区间最值 
I main(){
	scanf("%d%d",&n,&k);
	for(I i = 1;i <= n;i++){
		scanf("%d",&p[i]);
		r[p[i]] = i;//每个值对应的位置 
	}
	for(I i = 1;i < k;i++){//pair 的双关键字排序 
		x.insert({r[i],i});
		y.insert({-r[i],i});//小技巧，把负数存进去，输出时再变成正数，就是从大到小排 
	}
	I ans = 1e9 + 10;
	for(I i = k;i <= n;i++){
		x.insert({r[i],i});
		y.insert({-r[i],i});//加入新的 
		//printf("%d %d ",-y.begin()->fi,x.begin()->fi);//调试代码 
		ans = min(ans,-(y.begin()->fi) - (x.begin()->fi));//更新答案 
		x.erase({r[i - k + 1],i - k + 1});
		y.erase({-r[i - k + 1],i - k + 1});//前面的可以删掉了 
		//printf("%d %d\n",r[i - k + 1],i - k + 1);//调试代码 
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

# 1.题解
给定一个 $1$ 到 $n$ 的排列。

我们不妨设 $p_i$ 为 $i$ 出现的位置。

题目就变成，$k \le i \le n$ 时，$p_{i-k+1}$ 到 $p_i$，最大值减最小值，使这个值最小并输出。

求的是连续区间，我们可以用线段树维护。

时间复杂度 $O(n \log n)$。
# 2.代码
```
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200010],p[200010],ans=1e6;
struct tree{int ma,mi;}tr[2000010];
void pushup(int i){tr[i].ma=max(tr[i*2].ma,tr[i*2+1].ma),tr[i].mi=min(tr[i*2].mi,tr[i*2+1].mi);}
void build(int i,int l,int r){
	if(l==r){tr[i]={p[l],p[l]};return;}
	int m=(l+r)/2;
	build(i*2,l,m),build(i*2+1,m+1,r),pushup(i);
}
int q1(int i,int l,int r,int ql,int qr){
	if(l>qr||r<ql)return 0;
	if(l>=ql&&qr>=r)return tr[i].ma;
	int m=(l+r)/2;
	return max(q1(i*2,l,m,ql,qr),q1(i*2+1,m+1,r,ql,qr));
}
int q2(int i,int l,int r,int ql,int qr){
	if(l>qr||r<ql)return 1e6;
	if(l>=ql&&qr>=r)return tr[i].mi;
	int m=(l+r)/2;
	return min(q2(i*2,l,m,ql,qr),q2(i*2+1,m+1,r,ql,qr));
}
int main(){
	scanf("%d%d",&n,&k);
	for(int w=1;w<=n;w++)scanf("%d",&a[w]),p[a[w]]=w;
	build(1,1,n);
	for(int w=k;w<=n;w++)ans=min(ans,q1(1,1,n,w-k+1,w)-q2(1,1,n,w-k+1,w));
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Dream_poetry (赞：0)

### 题意：
我相信我不是唯一一个因为题意被卡半小时的蒟蒻。

大意为：在序列 $P$ 中找一个长度为 $K$ 的子序列，使得这个子序列内的元素是**连续的**，输出这个子序列中**下标最大值减去下标最小值**。

注意！不是最大值的下标减去最小值的下标

### 思路：
本题难度在于理解题意，然后我们考虑用堆做。

存一个大根堆 $maxn$，一个小根堆 $minn$，其中元素是 ```pair<int,int>```，作用显然，存储子序列最左下标和最右下标。

先将 $P$ 中前 $K$ 个数和他们的下标存入放入两个堆中，此处注意，要将下标作为第一关键字，值作为第二关键字。

接下来枚举即可，每次用 ```maxn.top().first-minn.top().first``` 即可。

如何更新呢？

当我们两个堆顶的元素的值不在我们所求的子序列中时，就要删除堆顶。

每次再加入新元素即可。

### 代码：

讲解可能不是太容易理解，但看了代码大家应该都能明白。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
#define pii pair<int,int>
int p[5000005];
map<int,int> pos;
int ans=0x3f3f3f3f;

priority_queue<pii,vector<pii>,less<pii> > maxn;// 大根堆 
priority_queue<pii,vector<pii>,greater<pii> > minn;// 小根堆 


signed main(){
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>p[i];
		pos[p[i]]=i; // 存储下标 
	}
	if (k==1){ // 此处特判 
		cout<<0;
		return 0;
	} 
	for (int i=1;i<=k;i++){ // 将 1~k 加入堆中 
		maxn.push(make_pair(pos[i],i));
		minn.push(make_pair(pos[i],i));
	}
	ans=min(ans,maxn.top().first-minn.top().first);
	for (int i=2;i<=n-k+1;i++){
		while (maxn.top().second<i) maxn.pop(); // 若堆顶的值不在当前子序列中，就要删掉。 
		while (minn.top().second<i) minn.pop();// 同理 
		maxn.push(make_pair(pos[i+k-1],i+k-1));// 加入新元素 
		minn.push(make_pair(pos[i+k-1],i+k-1));// 同理 
		ans=min(ans,maxn.top().first-minn.top().first);// 更新答案 
	} 
	cout<<ans;
	
	
	return 0;
} 
```

---

## 作者：FXLIR (赞：0)

由于选出的 $i$ 不需要是连续的，可以考虑将数列排序。

排序后，连续的 $K$ 个数字在原数列中的位置肯定满足第二条要求。如果此时 $i$ 的顺序不符合第一条要求，我们只需要将它们排序就可以，当然在这个题中我们并没有排序的必要。

对原数列中位置的记录很容易，开个结构体记录数字和位置即可。

由于第一条要求中的限制，每个“良好序列”中的 $i_1$ 肯定是最小的，而 $i_K$ 肯定是最大的，因此我们可以使用 ST 表维护整个排序后数列的索引最大值和最小值。

具体做法为：边输入边记录每个数字在原数列中的位置，然后将整个数列按照数字大小从小到大排序，再枚举所有长度为 $K$ 的“良好序列”，对于每个序列求其中的索引最大值和最小值，对于每个最大值和最小值的差求最小值即可。

AC 代码：[here](https://atcoder.jp/contests/abc352/submissions/53128507)

---

## 作者：zhangjiting (赞：0)

## 思路

看到排列，首先想到把数列拍在值域上，$a_i$ 表示 $i$ 这个数所在的位置。我们要求的就是 $\min_{i=1}^{n-k+1}(\max_{j=i}^{i+k-1}-\max_{j=i}^{i+k-1})$。

建一颗线段树维护 $a$ 序列，枚举 $i$，对于每一个 $i$ 求区间最值。时间复杂度 $O(N\log_{2}^N)$

## 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define debug(x) cout<<#x<<':',write(x),puts("");
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=2e5+5;
int n,k,a[N],ans=INT_MAX;
#define ls(p) p<<1
#define rs(p) p<<1|1
struct node{
	int l,r,mx,mn,sum;
}tree[N<<2];
void push_up(int p){
	tree[p].mx=max(tree[ls(p)].mx,tree[rs(p)].mx);
	tree[p].mn=min(tree[ls(p)].mn,tree[rs(p)].mn);
	tree[p].sum=tree[ls(p)].sum+tree[rs(p)].sum;
}
void build(int p,int l,int r){
	tree[p].l=l,tree[p].r=r;
	if(l==r){
		tree[p].mx=tree[p].mn=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	push_up(p);
}
int askmx(int p,int l,int r){
	if(l<=tree[p].l&&tree[p].r<=r){
		return tree[p].mx;
	}
	int mid=(tree[p].l+tree[p].r)>>1,res=INT_MIN;
	if(l<=mid) res=max(res,askmx(ls(p),l,r));
	if(r>mid) res=max(res,askmx(rs(p),l,r));
	return res;
}
int askmn(int p,int l,int r){
	if(l<=tree[p].l&&tree[p].r<=r){
		return tree[p].mn;
	}
	int mid=(tree[p].l+tree[p].r)>>1,res=INT_MAX;
	if(l<=mid) res=min(res,askmn(ls(p),l,r));
	if(r>mid) res=min(res,askmn(rs(p),l,r));
	return res;
}
signed main(){
	cin>>n>>k;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		a[x]=i;
	}
	build(1,1,n);
	for(int i=1;i<=n-k+1;i++){
		ans=min(ans,askmx(1,i,i+k-1)-askmn(1,i,i+k-1));
	}
	cout<<ans;
	return 0;
}
```

---

