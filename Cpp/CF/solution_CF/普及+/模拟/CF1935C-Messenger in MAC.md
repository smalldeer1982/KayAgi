# Messenger in MAC

## 题目描述

In the new messenger for the students of the Master's Assistance Center, Keftemerum, an update is planned, in which developers want to optimize the set of messages shown to the user. There are a total of $ n $ messages. Each message is characterized by two integers $ a_i $ and $ b_i $ . The time spent reading the set of messages with numbers $ p_1, p_2, \ldots, p_k $ ( $ 1 \le p_i \le n $ , all $ p_i $ are distinct) is calculated by the formula:

 $ $$$\Large \sum_{i=1}^{k} a_{p_i} + \sum_{i=1}^{k - 1} |b_{p_i} - b_{p_{i+1}}| $ $ </p><p>Note that the time to read a set of messages consisting of <span class="tex-font-style-bf">one</span> message with number  $ p\_1 $  is equal to  $ a\_{p\_1} $ . Also, the time to read an empty set of messages is considered to be  $ 0 $ .</p><p>The user can determine the time  $ l $  that he is willing to spend in the messenger. The messenger must inform the user of the maximum possible size of the set of messages, the reading time of which does not exceed  $ l $ . Note that the maximum size of the set of messages can be equal to  $ 0$$$.

The developers of the popular messenger failed to implement this function, so they asked you to solve this problem.

## 说明/提示

In the first test case, you can take a set of three messages with numbers $ p_1 = 3 $ , $ p_2 = 2 $ , and $ p_3 = 5 $ . The time spent reading this set is equal to $ a_3 + a_2 + a_5 + |b_3 - b_2| + |b_2 - b_5| = 2 + 1 + 2 + |4 - 5| + |5 - 3| = 8 $ .

In the second test case, you can take a set of one message with number $ p_1 = 1 $ . The time spent reading this set is equal to $ a_1 = 4 $ .

In the fifth test case, it can be shown that there is no such non-empty set of messages, the reading time of which does not exceed $ l $ .

## 样例 #1

### 输入

```
5
5 8
4 3
1 5
2 4
4 3
2 3
1 6
4 10
3 12
4 8
2 1
2 12
5 26
24 7
8 28
30 22
3 8
17 17
5 14
15 3
1000000000 998244353
179 239
228 1337
993 1007```

### 输出

```
3
1
2
1
0```

# 题解

## 作者：lbdontknow (赞：7)

赛时一直以为是背包，把时间都浪费掉了。  
## 题意
给出 $n$ 条信息和限制 $l$，每个信息有 $a_i$ 和 $b_i$ 两个属性。你需要从这些信息当中选出几条信息，并按某种顺序进行阅读。  
你花费的时间为你选择信息的 $a_i$ 之和 $+$ 相邻两条你阅读的信息 $b_i$ 的差的绝对值之和。  
你需要找到你能选择的最大信息数使得你花费的时间不超过 $l$。  
## 题解
首先，我们可以得出以下性质。在我们选出的信息中，阅读顺序一定是按照 $b_i$ 的值从小到大排列花费时间最少， 此时时间为 $\max(b_i) - \min(b_j)$。  
我们先将数组按照 $b_i$ 大小进行排序。  
然后我们可以枚举 $1 \leq l \leq r \leq n$，确定阅读的信息中最小的 $b_l$ 与最大的 $b_r$，然后贪心地从 $a_l$ 到 $a_r$ 中从小到大选择 $a_i$ 加入集合，但是这样复杂度为 $O(n^3 \log n)$，需要优化。  
我们可以维护一个大根堆，在移动 $r$ 指针的时候，将 $a_r$ 入堆。然后维护一个 $sum$ 代表堆中 $a_i$ 的总和。不断将堆中的最大值弹出直到 $sum \leq l - (b_r - b_l)$ 然后堆中元素的个数就是当前 $l,r$ 的答案。在所有的答案中取最大值。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int t;
const int N = 2e6 + 10;
struct node{
	int a, b;
	bool operator<(const node &b)const{
		return this->b < b.b;
	}
}a[N];
int n, L;
void solve(){
	cin >> n >> L;
	for(int i = 1 ; i <= n ; i++)
		cin >> a[i].a >> a[i].b;
	sort(a + 1, a + 1 + n);
	int ans = 0;
	for(int l = 1 ; l <= n ; l++){
		priority_queue<int>pq;
		int sum = 0;
		for(int r = l ; r <= n ; r++){
			pq.push(a[r].a);
			sum += a[r].a;
			while(pq.size() && sum > L - a[r].b + a[l].b){
				sum -= pq.top();
				pq.pop();
			}
			ans = max(ans, (int)pq.size());
		}
	}
	cout << ans << endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin >> t;
	while(t--)
		solve();
	return 0;
}
```

---

## 作者：Alex_Wei (赞：7)

### [CF1935C Messenger in MAC](https://www.luogu.com.cn/problem/CF1935C)

对于一组选定的集合 $S$，$a$ 的最小代价为 $\sum_{i\in S} a_i$，$b$ 的最小代价为 $\max_{i\in S} b_i - \min_{i \in S} b_i$。

考虑 DP。因为要求最大个数且代价维度太大，所以一定有维度和数量有关。

将元素按 $b$ 从小到大排序，设 $f_{i, j}$ 表示考虑到第 $i$ 个元素，已经选了 $j$ 个，选中元素的 $a_i$ 之和减去 $\min b_i$ 的最小值，则 $f_{i, 1} = a_i - b_i$，$f_{i, j} = \min_{k < i} (f_{k, j - 1} + a_i)\ (j > 1)$，使用前缀 $\min$ 优化即可做到 $\mathcal{O}(n ^ 2)$。

答案即最大的 $j$ 使得存在 $i$ 满足 $f_{i, j} + b_i \leq l$。

时间复杂度 $\mathcal{O}(n ^ 2)$。[代码](https://codeforces.com/contest/1935/submission/250200026)。

---

## 作者：fast_photon (赞：4)

## CF1935C  

### 1. 题意  
给定两个长度为 $n$ 的序列 $\{a_n\},\{b_n\}$ 和一个正整数 $T$，求最大的 $k$，使得存在一个长度为 $k$ 的序列 $\{p_k\}$，满足 $\forall i\neq j,p_i \neq p_j$，且 $\sum\limits_{i=1}^k a_i+\sum\limits_{i=1}^{k-1} |b_i-b_{i+1}|\le T$。  
$1\le n\le 2000$。

### 2. 分析  
注意到选好 $p$ 的内容之后调整顺序并不会对第一项产生影响。而按 $b$ 大小排序可以让第二项最小。  
所以我们先把两个序列对应位置不变地按 $b$ 不降排序。  
然后，由于已经排好序，第二项只会受选定的位置右端点与左端点 $b$ 的差有关。  
所以可以枚举左端点扫描右端点。若左右端点分别为 $l,r$，则此时选定的 $a$ 的和不能超过 $T-(b_r-b_l)$。可以直接用线段树上二分做，但是不想写线段树。  
考虑能否贪心。当左右端点确定时，选的一定是区间中 $a$ 最小的一段前缀。左右端点事实上可以不选，因为计算的左右端点比选中的左右端点更大只会导致条件更严格（不会算出错误答案），且枚举到正确左端点并扫到正确右端点时一定会计算这一组，除非有更优解（正确答案一定被计算）。  
如果每次加入一个新的 $a$，调整 $T-(b_r-b_l)$ 的限制，当选中的数超限时就删除最大的，这样对吗？  
在某一个位置选定区间中最小若干个值的时候，由于扫描右端点只会让限制更严格，所以曾经的宽松限制一定能容下这些数存在。又因为是每次删最大的，所以比它们更大的一定先被删掉。  
所以贪心是正确的。  

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<algorithm>
#define maxn 200005
#define int long long

using namespace std;


int n, l;

struct node {
	int a, b;
	bool operator<(node y)const {
		if(b == y.b) return a > y.a;
		return b < y.b;
	}
} a[maxn];
priority_queue<int> q; //可用 multiset 代之，千万不要 set

void work() {
	cin >> n >> l; // 这里的 l 是叙述中的 T
	for(int i = 1; i <= n; i++) {
		cin >> a[i].a >> a[i].b;
	}
	int ans = 0;
	sort(a + 1, a + n + 1); //按 b 排序
	for(int i = 1; i <= n; i++) {
		while(!q.empty()) q.pop();
		int sum = 0;
		int cnt = 0;
		for(int j = i; j <= n; j++) {
			q.push(a[j].a); //扫一个新的点，把 a 暂时选上
			cnt++; //统计个数
			sum += a[j].a; //记录已经选择的数的和
			while(sum + a[j].b - a[i].b > l && !q.empty()) { //超出限制
				sum -= q.top();
				q.pop();
				cnt--;
			}
			ans = max(ans, cnt); // 一定要记得更新一次端点就更新一次答案
		}
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int _; cin >> _; while(_--) work();
} 
```

---

## 作者：破壁人罗辑 (赞：4)

## 题意简述

给出一个整数 $l$ 和两个数组 $a_i,b_i$，求出最长的使得 $\sum_{i=1}^{k} a_{p_i} + \sum_{i=1}^{k - 1} |b_{p_i} - b_{p_{i+1}}|\leq l$ 的数列 $p_i$ 的长度，其中 $p_i$ 互不相同。

## 解题思路

由绝对值的性质可知，若已经选择了 $n$ 个数 $p_1,p_2,\cdots,p_n$，则将 $p_i$ 按照 $b_{p_i}$ 严格递减或严格递增的顺序重新排列后使用的总时长一定更少，所以可以先把 $a_i$ 和 $b_i$ 按照 $b_i$ 递增或递减的顺序排序一遍。

若已经按照 $b_i$ 严格递增的顺序重新排序，则 $p_i$ 严格递增，所用的总时长为 $b_{p_n}-b_{p_1}+\sum_{i=1}^{n}a_{p_{i}}$。

设 $f[i][j]$ 表示在前 $i$ 个物品中选取 $j$ 个物品时最小的 $-b_{p_1}+\sum_{i=1}^{n}a_{p_{i}}$，则 $f[i][j]$ 的状态转移方程为 $f[i][1]=\min(f[i-1][1],a[i]-b[i]),f[i][j]=min(f[i-1][j],f[i-1][j-1]+a[i]),j>1$.

我们可以用 $O(n\log n)$ 的时间复杂度进行一次排序，再用 $O(n^2)$ 的时间复杂度求出 $f[i][j]$，找出最大的满足 $f[i][j]+b_i\leq l$ 的整数 $j$ 即为答案。

## 解题代码

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct message{
	int a,b;
}m[2002];
bool operator<(message x,message y){
	return x.b<y.b;
}
long long ans[2002][2002];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,l;scanf("%d%d",&n,&l);
		for(int i=1;i<=n;i++)scanf("%d%d",&m[i].a,&m[i].b);
		sort(m+1,m+n+1);
        int ret=0;
		ans[0][1]=l+1145141919810ll;
		for(int i=1;i<=n;i++){
			ans[i][1]=min(m[i].a-(long long)m[i].b,ans[i-1][1]);
			if(m[i].a<=l&&ret==0)ret=1;
			for(int j=2;j<=i;j++){
				ans[i][j]=min(ans[i-1][j],ans[i-1][j-1]+m[i].a);
				if(ans[i][j]+m[i].b<=l&&ret<j)ret=j;
			}
			ans[i][i+1]=l+1145141919810ll;
		}
		printf("%d\n",ret);
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：3)

诶嘿嘿没想到动态规划，写了神秘的大常数 $\operatorname{O}(n^2\log^2 n)$ 做法，并跑过了。

------------

显然答案具有单调性，考虑二分答案。

我们将二元组按 $b$ 排序，那么对于一个区间 $[l,r]$，若两端必选，$\sum\limits_{i=1}^{k-1}|b_{p_i}-b_{p_{i+1}}|=b_r-b_l$。

所以我们只需要最小化 $\sum\limits_{i=1}^ka_{p_i}$，其实就是区间内前 $k$ 小的和。

显然可以权值线段树做，不过这放 2C 想想也不可能。

考虑固定左端点向右枚举右端点，可重集维护一个反悔贪心（每次比较最大数和当前右端点，更优就换）即可。

实际过程中不需要考虑左右端点必选的问题，因为一定能枚举到都选的区间。

复杂度 $\operatorname{O}(n^2\log^2n)$。

------------

也是怀疑了半天能不能跑过，拜谢评测机。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e3+26;
struct Msg{
    int a,b;
    friend bool operator<(Msg xy,Msg zb){
        return xy.b<zb.b;
    }
}m[maxn];
int T,n,L,l,r,mid,ans,sz;
ll sum;
multiset<int> st;
inline bool check(int x){
    for(int i=1;i<=n;i++){
        st.clear();
        sz=sum=0;
        for(int j=i;j<=n;j++){
            if(sz<x){
                sz++;
                st.insert(m[j].a);
                sum+=m[j].a;
                if(sz==x&&sum+m[j].b-m[i].b<=L)
                    return 1;
            }
            else if(m[j].a<*prev(st.end())){
                sum+=m[j].a-*prev(st.end());
                st.erase(prev(st.end()));
                st.insert(m[j].a);
                if(sum+m[j].b-m[i].b<=L)
                    return 1;
            }
        }
    }
    return 0;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&L);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&m[i].a,&m[i].b);
        sort(m+1,m+n+1);
        ans=0;
        l=1;
        r=n;
        while(l<=r){
            mid=l+r>>1;
            if(check(mid)){
                ans=mid;
                l=mid+1;
            }
            else
                r=mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Genius_Star (赞：2)

### 思路：

~~刚开始想二分，结果假了……~~

先研究一下这个求贡献的式子：

$$\sum_{i=1}^k a_{p_i}+\sum_{i=1}^{k-1} |b_{p_i}-b_{p_i+1}|=\sum_{i=1}^k a_{p_i}+\sum_{i=2}^k |b_{p_i}-b_{p_i-1}|$$

考虑将式子中的绝对值化掉，即将序列按照 $b$ 的值从小到大排序即可：

$$\sum_{i=1}^k a_{p_i}+\sum_{i=2}^k b_{p_i}-b_{p_i-1}$$

首先发现后面这个式子的值和 $p$ 的顺序是有关系，那么如果要使得后面这个式子最小。

那么肯定要使得 $p_i$ 和 $p_i-1$ 两个位置的值的差的和最小，那么当 $b_{p_i}$ 是单调上升的时，后面式子最小。

那么考虑使用动态规划算法，定义 $dp_{i,j}$ 表示前 $i$ 个数选了 $j$ 个数的最小贡献，则状态转移方程为：

$$dp_{i,j}=\min\limits_{k=1}^{i-1} dp_{k,j-1}+a_i+b_i-b_k$$

时间复杂度是 $O(N^3)$ 的，明显过不去，考虑优化。

发现上述式子是求选的数量为 $j-1$ 时，当前 $dp_{k,j-1}-b_k$ 的最小值。

那么定义 $s_{i}$ 表示当选的数量为 $i$ 时 $dp_{k,i}-b_k$ 的最小值，每次拿 $dp_{i,j}$ 去更新 $s_j$ 的最小值即可。

此时状态转移方程为：

$$dp_{i,j}=s_{j-1}+a_i+b_i$$

这样时间复杂度就被优化到了 $O(N^2)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2020,INF=1e17;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll x,y;
	bool operator<(const Node&rhs)const{
		if(y!=rhs.y)
		  return y<rhs.y;
		return x<rhs.x;
	}
}a[N];
ll T,n,ans,l;
ll dp[N][N],s[N]; // 选 i 的最小贡献 
void solve(){
	n=read(),l=read();
	for(int i=1;i<=n;i++)
	  a[i]={read(),read()};
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    dp[i][j]=INF;
	for(int i=1;i<=n;i++)
	  s[i]=INF;
	dp[1][1]=a[1].x;
	s[1]=dp[1][1]-a[1].y;
	if(a[1].x<=l)
	  ans=1;
	else
	  ans=0;
	for(int i=2;i<=n;i++){
		dp[i][1]=a[i].x;
		for(int j=2;j<=i;j++)
		  dp[i][j]=s[j-1]+a[i].x+a[i].y;
//			(dp[i][j],dp[k][j-1]+a[i].x+a[i].y-a[k].y);
		for(int j=1;j<=i;j++)
		  if(dp[i][j]<=l)
		    ans=max(ans,(ll)j);
		for(int j=1;j<=i;j++)
		  s[j]=min(s[j],dp[i][j]-a[i].y);
	}
	write(ans);
	putchar('\n');
}
int main(){
//	freopen("A.in","r",stdin);
	T=read();
	while(T--)
	  solve();
	return 0;
}
```

---

## 作者：2huk (赞：2)

给定 $n$ 个二元组 $(a_i, b_i)$，你需要找出 $k$ 其中个二元组并重新排为 $(a_1,b_1),(a_2,b_2),…,(a_k,b_k)$，最大化 $k$ 使得：

$$
\sum_{i=1}^ka_i+\sum_{i=1}^{k-1}|b_i-b_{i+1}| \le l
$$

---

二分 $k$。

首先观察到，为了使条件尽量满足，我们一定希望在 $k$ 确定的情况下不等式左边 $\sum_{i=1}^ka_i+\sum_{i=1}^{k-1}|b_i-b_{i+1}|$ 的值尽量小。

更进一步，如果我们确定了选择的二元组为 $(a_1,b_1),(a_2,b_2),…,(a_k,b_k)$，但是没有确定顺序。那么此时 $\sum_{i=1}^ka_i$ 的值一定，我们为了使 $\sum_{i=1}^{k-1}|b_i-b_{i+1}|$ 最小，根据初一数学，我们应该让 $b_i$ 从小到大（或从大到小）排序。那么这个式子的值即为 $\max_{i=1}^k b_i - \min_{i=1}^k b_i$。

数据范围提示了平方复杂度，那么我们可以枚举上式中 $b$ 的最小值 $b_l$ 和最大值 $b_r$。为了方便，我们将读入的二元组 $(a_i, b_i)$ 按第二关键字升序排序。

此时，我们希望在二元组 $(a_l, b_l) \dots (a_r, b_r)$ 中选择 $k$ 个二元组，满足 $\sum a + b_r - b_l \le l$。如果存在一个 $(l, r)$ 满足这个条件，二分的 $k$ 就是合法的。

显然我们需要贪心地找 $a$ 前 $k$ 小的。具体的，我们需要维护一种数据结构，求区间内前 $k$ 小数之和。

check 函数是这样的：

```cpp
bool chk(int mid) {
	int res = 1e18;
	for (int l = 1; l <= n; ++ l ) {
        for (int r = l; r <= n; ++ r ) {
            // calc(l, r, mid) 表示区间 [l, r] 内前 mid 小的数的和
            res = min(res, calc(l, r, mid) + b[r] - b[l]);
        }
	}
	return res <= k;
}
```

~~所以我们只需要维护一颗平衡树或主席树，就能愉快切掉 div.3 C 了。~~

我们可以维护大根堆。当前堆内的元素为当前区间内的前 $k$ 小数，堆顶为当前区间的第 $k$ 小数。再维护一个值 $s$ 表示当前堆内的元素和，也就是我们希望求的。

每次新增一个元素 $a_r$，如果它比当前堆顶大，那么我们不需要处理它。否则，弹出当前堆顶并将 $a_r$ 入堆。重新计算 $s$ 的值。
注意如果此时堆的大小小于 $k$，无论如何都需要入堆。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;
typedef unsigned long long LL;
typedef pair<int, int> PII;

struct FASTREAD {
	template <typename T>
	FASTREAD& operator >>(T& x) {
		x = 0; bool flg = false; char c = getchar();
		while (c < '0' || c > '9') flg |= (c == '-'), c = getchar();
		while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
		if (flg) x = -x; return *this;
	}
	template <typename T>
	FASTREAD& operator >>(vector<T>& x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) >> *it;
		return *this;
	}
}fin;

struct FASTWRITE {
	template <typename T>
	FASTWRITE& operator <<(T x) {
		if (x < 0) x = -x, putchar('-');
		static int buf[35]; int top = 0;
		do buf[top ++ ] = x % 10, x /= 10; while (x);
		while (top) putchar(buf[ -- top] + '0');
		return *this;
	}
	FASTWRITE& operator <<(char x) {
		putchar(x); return *this;
	}
	template <typename T>
	FASTWRITE& operator <<(vector<T> x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) << *it, putchar(' ');
		putchar('\n');
		return *this;
	}
}fout;

const int N = 2010;
const int P = 998244353;

int n, k, len, nums[N], root[N], idx;
PII a[N];

bool chk(int mid) {
	int res = 1e18;
	for (int l = 1; l <= n; ++ l ) {
		int s = 0;
		priority_queue<int> q;
		for (int r = l; r <= n; ++ r ) {
			if (q.size() < mid) s += a[r].first, q.push(a[r].first);
			else {
				if (a[r].first < q.top()) {
					s += a[r].first - q.top();
					q.pop();
					q.push(a[r].first);
				}
			}
			if (q.size() >= mid) res = min(res, a[r].second - a[l].second + s);
		}
	}
	return res <= k;
}

void Luogu_UID_748509() {
	fin >> n >> k;
	for (int i = 1; i <= n; ++ i ) {
		fin >> a[i].first >> a[i].second;
		nums[i] = a[i].first;
	}
	sort(a + 1, a + n + 1, [&](PII x, PII y) {
		return x.second < y.second;
	});
	
	int l = 1, r = n, res = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (chk(mid)) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	fout << res << '\n';
	return;
}

signed main() {
	int Testcases = 1;
	fin >> Testcases;
	while (Testcases -- ) Luogu_UID_748509();
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 题目大意

给你 $n$ 个二元组 $(a_i, b_i)$，要求从中选出 $k$ 个二元组并任意打乱，设其下标集合 $S = \{p_1, p_2, ..., p_k\}$，要求在 $\sum\limits_{i = 1}^k a_i + \sum\limits_{i = 2}^k |b_{p_i} - b_{p_{i - 1}}| \le l$ 的情况下将 $k$ 最大化。

$1 \le n \le 2000$。

## 题目思路

我们考虑一个事情，如果选出了 $k$ 个且下标集合 $S = \{p_1, p_2, ..., p_k\}$，那么当 $p_i \le p_{i + 1}$ 的时候是这个集合所有顺序排列中值最小的，此时的代价是 $\sum\limits_{i = 1}^k a_i + b_{p_k} - b_{p_1}$。

因此我们考虑枚举这个集合中的下标最小值和下标最大值，在这中间，很明显元素是按照 $a$ 的大小从小往大放，直到放到不能放为止，这可以用堆来做，发现是三方的，然后我们在枚举最大值的时候顺便加进去计算，时间复杂度就是 $O(n^2 \log_2 n)$。

## 题目代码

Code：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )
 
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;
 
char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}
 
template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }
 
const int N = 2005;
 
int t, n, l, ans;
 
struct Node {
	int a, b;
} a[N];
 
bool cmp ( Node x, Node y ) {
	return x.b == y.b ? x.a < y.a : x.b < y.b;
}
 
void Solve () {
	cin >> t;
	while ( t -- ) {
		ans = 0;
		cin >> n >> l;
		for ( int i = 1; i <= n; i ++ ) {
			cin >> a[i].a >> a[i].b;
		}
		sort ( a + 1, a + 1 + n, cmp );
		for ( int i = 1; i <= n; i ++ ) {
			priority_queue < int > q;
			int res = 0;
			for ( int j = i; j <= n; j ++ ) {
				q.push ( a[j].a );
				res += a[j].a;
				while ( res + a[j].b - a[i].b > l && !q.empty () ) {
					res -= q.top ();
					q.pop ();
				}
				ans = max ( ans, ( long long ) q.size () );
			}
		}
		cout << ans << '\n';
	}
}
 
signed main () {
#ifdef judge
	freopen ( "test.in", "r", stdin );
	freopen ( "test.out", "w", stdout );
	freopen ( "test.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

## 作者：Xiphi (赞：0)

赛时智障了，没想到直接 dp，写的是二分加动规判断。

首先分析一下柿子，发现前面的 $\sum_{i=1}^k a_{p_i}$ 与后面的柿子关系不大。所以先考虑后面比较麻烦的柿子。

贪心的，发现 $b$ 数组从小到大排序后跑 dp 是最优的。感性理解一下，交换 $b_i,b_j$ 必然会多算一段内容。

接着二分 $k$，跑 dp 判断能不能选出 $mid$ 个数且值 $\le l$ 即可。

```cpp
#include<bits/stdc++.h>
#define _for(i,x,y) for(int i=x;i<=y;++i)
using namespace std;
#define int long long
int T,n,l;
pair<int,int>a[2005];
bool check(int mid){
	int dp[n+5][mid+5],Min=0x3f3f3f3f,suf[mid+5];
	memset(dp,0x3f,sizeof dp);
	memset(suf,0x3f,sizeof suf);
	dp[1][1]=a[1].first;
	suf[1]=min((long long)(1+1e9),a[1].first-a[1].second);
	if(1==mid) Min=dp[1][1];
	_for(i,2,n){
		dp[i][1]=a[i].first;
		_for(j,2,min(mid,i)){
			dp[i][j]=min(suf[j-1]+a[i].first+abs(a[i].second),dp[i][j]);
		}
		_for(j,1,min(mid,i))
			suf[j]=min(suf[j],dp[i][j]-a[i].second);
		Min=min(Min,dp[i][mid]);
	}
	return Min<=l;
}
bool cmp(pair<int,int> x,pair<int,int> y){
	if(x.second!=y.second) return x.second<y.second;
	else return x.first<y.first;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>l;
		_for(i,1,n) cin>>a[i].first>>a[i].second;
		sort(a+1,a+n+1,cmp);
		int l=1,r=n,ans=0;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

题意：给定 $n$ 个数对 $(a_i, b_i)$ 和数 $l$，请构造一个 $p_1, p_2, \dots, p_k$，使得 $\sum_{i=1}^{k} a_{p_i} + \sum_{i=1}^{k - 1} |b_{p_i} - b_{p_{i+1}}| \le l$，最大化 $k$。

转化题意：选择 $k$ 个数，使得它们的极差加上它们的和小于 $l$。

给数对排序，按 $b_i$ 升序排列，然后枚举最小值 $b_i$ 和最大值 $b_j$。

只需查询在和小于 $l$ 的前提下，最多在 $[i, j]$ 中选择几个数，这用动态开点权值线段树很容易维护，时间复杂度 $O(n^2 \log n)$。

多测要清空左右孩子！

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
#include <vector>

#define int long long

using namespace std;

int T, n, l;
int ls[2005];
int rs[2005];
struct node {
    int a, b;
    inline bool operator<(const node &nd) const {
        return b < nd.b;
    }
} a[2005];

struct ds {
    int ls, rs, val, sum;
} d[1000005];
int cnt, rt;
static inline int insert(int x, int s, int t, int p) {
    if (!p) {
        p = ++cnt;
        d[p] = {0, 0, 0, 0};
    }
    if (s == t) {
        ++d[p].val;
        d[p].sum += s;
        return p;
    }
    int mid = (s + t) >> 1;
    if (x <= mid) {
        d[p].ls = insert(x, s, mid, d[p].ls);
    } else {
        d[p].rs = insert(x, mid + 1, t, d[p].rs);
    }
    d[p].val = d[d[p].ls].val + d[d[p].rs].val;
    d[p].sum = d[d[p].ls].sum + d[d[p].rs].sum;
    return p;
}
static inline int query(int x, int s, int t, int p) {
    if (!p) {
        return 0;
    }
    if (s == t) {
        return min(x / s, d[p].val);
    }
    int mid = (s + t) >> 1;
    if (d[d[p].ls].sum <= x) {
        return d[d[p].ls].val + query(x - d[d[p].ls].sum, mid + 1, t, d[p].rs);
    } else {
        return query(x, s, mid, d[p].ls);
    }
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("CF1935C.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> l;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].a >> a[i].b;
        }
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; ++i) {
            if (a[i].b == a[i - 1].b) {
                ls[i] = ls[i - 1];
            } else {
                ls[i] = i;
            }
        }
        a[n + 1].b = 0;
        for (int i = n; i; --i) {
            if (a[i].b == a[i + 1].b) {
                rs[i] = rs[i + 1];
            } else {
                rs[i] = i;
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (ls[i] != i) {
                continue;
            }
            cnt = rt = 0;
            d[rt] = {0, 0, 0, 0};
            for (int j = i; j <= n; ++j) {
                rt = insert(a[j].a, 1, 1e9, rt);
                if (rs[j] != j) {
                    continue;
                }
                int las = l - a[j].b + a[i].b;
                ans = max(ans, query(las, 1, 1e9, rt));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

## 题意

给定 $n$ 个二元组 $\{a_i,b_i\}$，对于一个 $p_1\cdots p_k$，定义其权值为 $\sum\limits_{i=1}^ka_{p_i}+\sum\limits_{i=2}^k|b_{p_i}-b_{p_{i-1}}|(\forall i,j\in[1,k],p_i\ne p_j,p_i\le n)$。

求出最大的 $k$ 使得存在这样的一个长为 $k$ 的 $p$，且其权值小于 $l$。

## 题解
显然选出了若干物品后，最后排列它们的方式一定满足 $b$ 上单调。这启发我们把二元组按 $b$ 降序排序。

不妨设一个 dp，$f_{i,j}$ 表示排序后前 $i$ 个物品中，选出 $j$ 的最小代价。那么：

$$f_{i,1}=a_i$$
$$f_{i,j}=\min(f_{k,j-1}+b_i-b_k+a_i)(k<i)$$

这是一个 $O(n^3)$ 的 dp。

发现下面那条的转移，本质上是 $f_{k,j-1}-b_k$ 中最小的，对每个 $j$ 动态维护即可。优化到 $O(n^2)$。

但是我赛时脑子抽了，多写了个 set 为了求最小值，多了只 $\log$，反正能过。

```cpp
#include<iostream>
#include<algorithm>
#include<set>
#define F first
#define S second
#define int long long
#define pii std::pair<int, int>
int T, n, l; pii o[2005];
std::set<pii> s[2005]; int f[2005][2005];
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin >> T; while(T--){
        std::cin >> n >> l; for(int i = 1; i <= n; i++) s[i].clear();
        for(int i = 1; i <= n; i++) std::cin >> o[i].F >> o[i].S;
        std::sort(o+1, o+n+1, [&](pii a, pii b){return a.S<b.S;});
        for(int i = 1; i <= n; i++){
            auto [a, b] = o[i]; f[i][1] = a; 
            for(int j = 1; j < i; j++){
                auto it = s[j].begin(); int x = it->S;
                f[i][j+1] = f[x][j] + a + b - o[x].S;
            } for(int j = 1; j <= i; j++) s[j].emplace(f[i][j]-b, i);
        }
        int rs = 0; for(int i = 1; i <= n; i++)
            for(int j = 1; j <= i; j++) if(f[i][j] <= l) rs = std::max(rs, j);
        std::cout << rs << '\n';
    }
}
```

---

