# [ABC376E] Max × Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc376/tasks/abc376_e

長さ $ N $ の数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N),\ B\ =\ (B_1,\ B_2,\ \dots,\ B_N) $ が与えられます。  
$ \lbrace\ 1,\ 2,\ \dots,\ N\ \rbrace $ の部分集合であって大きさが $ K $ のものを $ 1 $ つ選び $ S $ とします。この時、以下の式の値としてあり得る最小値を求めてください。

$ \displaystyle\ \left(\max_{i\ \in\ S}\ A_i\right)\ \times\ \left(\sum_{i\ \in\ S}\ B_i\right) $ 

$ T $ 個のテストケースが与えられるので、それぞれに対して答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 10^6 $
- 全てのテストケースに対する $ N $ の総和は $ 2\ \times\ 10^5 $ 以下
- 入力される値は全て整数

### Sample Explanation 1

$ 1 $ 番目のテストケースでは、$ S\ =\ \lbrace\ 2,\ 3\ \rbrace $ を選ぶと式の値が $ 7\ \times\ (2\ +\ 4)\ =\ 42 $ になり、これが最小です。

## 样例 #1

### 输入

```
3
3 2
3 7 6
9 2 4
5 3
6 4 1 5 9
8 6 5 1 7
10 6
61 95 61 57 69 49 46 47 14 43
39 79 48 92 90 76 30 16 30 94```

### 输出

```
42
60
14579```

# 题解

## 作者：yszkddzyh (赞：8)

前言：解释较为详细，请耐心看完。

如果有看不懂的，可以评论或者私信。

先将数组按照 $a$ 从小到大排序（注意 $b$ 的顺序要跟随 $a$ 变化）。

考虑选择 $1$ 个数 $a_i$，令其为 $\max$，为了使这种情况下乘积最小，我们需要使选择的**另外 $k - 1$ 个数的 $b$ 的和**最小。于是我们需要选择前 $k - 1$ 小的 $b_j$，前提是选择的数的 $a$ 值都小于 $a_i$，不然 $a_i$ 就不是 $\max$ 了。而我们刚刚已经按照 $a$ 排序了，所以只需要在下标小于 $i$ 的数中选择前 $k - 1$ 小的 $b$ 就可以满足前提。

整理一下思路：排序，从前往后枚举 $i$，设**数组 $b$ 中下标小于 $i$ 的前 $k - 1$ 小的数的和**为 $sum$，统计答案，即 $ans = \min(ans, a_i \times (sum + b_i))$，最后输出 $ans$ 即可。

现在的问题是如何快速求出 $sum$。

首先，我们不需要每枚举到一个 $i$，就将 $b_1$ 到 $b_{i - 1}$ 重新排序。而是每枚举到一个 $i$，在 $i - 1$ 的结果上做微操，得到 $i$ 的结果（这个思路在 abc 中经常用到）。

我们思考 $sum$ 的含义，是：数组 $b$ 中下标小于 $i$ 的前 $k - 1$ 小的数的和（下面记 $sum_i$ 为枚举到 $i$ 时的 $sum$ 值）。

假设我们现在已经知道了 $sum_{i - 1}$，那么我们应该判断 $b_i$ 与**下标小于 $i - 1$ 的 $b$ 中第 $k - 1$ 小的数**（记为 $t_{i - 1}$）的大小关系，如果 $b_i \geq t_{i - 1}$，那么 $b_i$ 就不会使前 $k - 1$ 小的数发生变化，于是 $sum_i = sum_{i - 1}$；如果 $b_i < t_{i - 1}$，那么 $b_i$ 就会成为前 $k - 1$ 小的数之一，而 $t_{i - 1}$ 就不在前 $k - 1$ 小的数当中了，于是 $sum_i = sum_{i - 1} - t_{i - 1} + b_i$。

所以我们现在就是要维护 $t_i$，这固然可以用对顶堆，但是本蒟蒻赛时没想到，用了平衡树（雾）。

最后一个问题：如何求出初始的 $sum$？实际上很简单，显然 $i$ 是要从 $k$ 开始的，而这时 $i$ 前面有且仅有 $k - 1$ 个元素，因此这 $k - 1$ 个元素一定是前 $k - 1$ 小的。

代码较长，请在[云剪贴板](https://www.luogu.com.cn/paste/ytbmfrzj)中查看。

---

## 作者：mysterys (赞：4)

赛时太唐了，导致 TLE 了，特意来写篇题解纪念一下。

# 思路

1. 观察到右边的式子，不难发现：如果想使 $\displaystyle\ \left(\sum_{i\ \in\ S}\ B_i\right)$ 最小，一定是从小到大排序后取到的。因此，我们只需要考虑左边怎么算即可。
2. 因为右边很好维护，所以可以换一下思路，将 $A_i$ 按从小到大排序，此时最大的 $A_i$ 就是当前的 $A_i$，而 $\displaystyle\ \left(\sum_{i\ \in\ S}\ B_i\right)$ 直接使用优先队列维护即可，具体见代码。
3. 这里有一个细节：按思路应该开一个优先队列维护从小到大，但是实现的时候应该**正好相反**，理由是：队列是 FIFO 结构，所以维护的时候只能从前面取出。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
#define endl '\n'
#define int long long
const int N=2e5+5;
int n,k,ans,tot;
struct node{
	int x,y;
}a[N];
priority_queue<int,vector<int>,less<int> >q;
inline void solve(){
	cin>>n>>k;
	tot=0;
    while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++) cin>>a[i].x;
	for(int i=1;i<=n;i++) cin>>a[i].y;
	stable_sort(a+1,a+n+1,[&](node p1,node p2){
		return p1.x==p2.x?p1.y<p2.y:p1.x<p2.x;
	});
	for(int i=1;i<=k;i++) {
		q.push(a[i].y);
		tot+=a[i].y;
	}
	ans=tot*a[k].x;
	for(int i=k+1;i<=n;i++){
		while((int)q.size()>=k){
			tot-=q.top();q.pop();
		}
		ans=min(ans,(tot+a[i].y)*a[i].x);
		q.push(a[i].y);tot+=a[i].y;
	}
	cout<<ans<<endl;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Ad_lqz_ht (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc376_e)

## 题意
给你两个长度为 $N$ 的序列 $A$ 和 $B$，求出 $A$ 中任意 $K$ 个元素的最大值乘在 $B$ 中对应的值的和的最小值。

比如样例：
```
3 2
3 7 6
9 2 4
```
$N=3$，$K=2$，我们一共有三种可以选择的方案。

1. 选第一个和第二个，此时 $A_1$ 和 $A_2$ 的最大值是 $7$，$B_1$ 和 $B_2$ 的和是 $11$，得到的乘积是 $77$。
2. 选第一个和第三个，此时 $A_1$ 和 $A_3$ 的最大值是 $6$，$B_1$ 和 $B_3$ 的和是 $13$，得到的乘积是 $78$。
3. 选第二个和第三个，此时 $A_2$ 和 $A_3$ 的最大值是 $7$，$B_2$ 和 $B_3$ 的和是 $6$，得到的乘积是 $42$。

所以，样例应该输出 $42$。

## 思路
首先不难发现，$A$ 中前 $K-1$ 小的元素都是没有用的，因为无论怎么选择永远不可能成为最大值。

所以我们可以先将两个序列以 $A$ 的大小为关键字进行排序，从 $K$ 开始枚举每个 $A_i$，找到最优的若干个 $B_i$。

显然从 $K\sim N$ 枚举每一个 $A_i$ 已经无法再优化，所以可以考虑优化寻找 $B_i$ 的和的过程。

因为在选择了 $A_i$ 之后，$B_i$ 是一定要被选择的，而在排序后前面的小于 $i$ 的部分无论怎么选择都不影响 $A$ 的最大值了，只影响 $B$ 的和，因此，可以使用一个优先队列，将前 $K$ 小的 $B_i$ 放进去，每次再统计贡献，具体实现看代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005;
const int inf = 0x3f3f3f3f3f3f3f3f;
int t, n, k, ans = inf, sum;
struct num
{
	int a, b;
	bool operator < (const num x) const { return a < x.a; }
} p[N]; //两个序列
priority_queue<int> q;
signed main()
{
    cin.tie(0) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--)
    {
    	cin >> n >> k;
    	for (int i = 1; i <= n; ++i) cin >> p[i].a;
    	for (int i = 1; i <= n; ++i) cin >> p[i].b;
    	sort(p + 1, p + n + 1); //让A有序
    	for (int i = 1; i <= k; ++i) q.push(p[i].b), sum += p[i].b;//前K个
    	for (int i = k; i <= n; ++i)
    	{
    		ans = min(ans, p[i].a * sum);//每一个i从k到n的贡献
    		sum -= q.top(); q.pop();//删掉不优的
    		q.push(p[i + 1].b);//新加入的
    		sum += p[i + 1].b;
    	}
    	while (!q.empty()) q.pop();//清空
    	cout << ans << '\n'; ans = inf, sum = 0;
    }
    return 0;
}
```

---

## 作者：light_searcher (赞：2)

挺典的，但是我只会做这题呜呜呜。

由于 $\max \limits _{i \in S} A_i$ 最多只有 $n$ 种取值，所以我们可以考虑从小到大枚举最大值。我们可以按 $A$ 从小到大排序，接着枚举 $i$，使最大值就为 $A_i$，由于已经排过序了，所以 $A_i$ 后面的数一定不会被取到，那么只需要在前 $B_1 \sim B_i$ 里面找最小的 $k$ 个的和，这个随便用一种数据结构来维护即可，用大根堆是最方便的。之后就可以更新答案了。

Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T,k,n;
pair<int,int>a[N];
priority_queue<int>q;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i].first);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i].second);
		sort(a+1,a+n+1);
		int ans=LONG_LONG_MAX,sum=0;
		q=priority_queue<int>();
		for(int i=1;i<k;i++){
			q.push(a[i].second);
			sum+=a[i].second;
		}
		for(int i=k;i<=n;i++){
			q.push(a[i].second);
			sum+=a[i].second;
			if(q.size()>k){
				sum-=q.top();
				q.pop();
			}
			ans=min(ans,a[i].first*sum);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

---

## 作者：Lydia1010__ (赞：1)

## 本题思路：
这道题其实算比较简单的贪心了，我们知道只要固定住 $A$ 数组的最大值是多少，那么就可以在比当前的 $A$ 值小的下标里面选最小的 $k$ 个 $B$ 数组加起来就可以了。

知道了这一点，我们就可以直接按照 $A$ 数组排序，确定最大值，然后按上文讲的贪心直接贪过去即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct f{
	int a,b;
}a[200005];
bool cmp(f x,f y){return x.a<y.a;}
priority_queue<int>q;
signed main(){
	int t;cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		while(q.size()) q.pop();
		for(int i=1;i<=n;i++) cin>>a[i].a;
		for(int i=1;i<=n;i++) cin>>a[i].b;
		sort(a+1,a+1+n,cmp);
		int sum=0;
		for(int i=1;i<=k;i++){q.push(a[i].b);sum+=a[i].b;}
		int ans=a[k].a*sum;
		for(int i=k+1;i<=n;i++){
			int p=q.top();
			if(a[i].b<p){
				q.pop(),q.push(a[i].b);sum-=p,sum+=a[i].b;
			}
//			cout<<i<<" "<<sum<<endl;
			ans=min(ans,sum*a[i].a);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：1)

## 解题思路：
首先对于一组按 $a$ 升序排序，于是就可以发现当前最大值就是 $a_i$，接着对 $b$ 进行不断求和，并把它们压入优先队列，若压入数大于 $k$，则弹出队首（最大值），并减去它。最后判断若队里的数等于 $k$ 时，则记录当前最小值即可。（讲很抽象是吧，所以详见代码）
## CODE：

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
ll t, n, k, cur, tot, ans;
struct node{ll t, b;}a[300001];
bool operator< (const node x, const node y){return x.b < y.b;}
priority_queue <ll> qp;
int main()
{
    cin >> t;
    while (t--)
    {
        ans = 1e18;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i].b;
        for (int i = 1; i <= n; i++) cin >> a[i].t;
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i++)
        {
            qp.push(a[i].t);
            tot += a[i].t;
            ++cur;
            while (cur > k)
            {
                tot -= qp.top();
                --cur;
                qp.pop();
            }
            if (cur == k) ans = min(ans, tot * a[i].b);
        }
        cout << ans << '\n';
        while (!qp.empty()) qp.pop();
        tot = cur = 0;
    }
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

典。

将 $a_i$ 排序之后，枚举 $a_p=\max_{i\in S} a_i$，那么 $b$ 可以选的就是 $a_j\le a_p$ 的 $j$（即要求 $j\le p$），贪心选择前 $k-1$ 小的，用优先队列维护。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5, inf = 0x3f3f3f3f3f3f3f3f;
int T, n, ans, sum, k;
struct node{
	int a, b;
}a[N];
priority_queue<int> pq;
signed main(){
	scanf("%lld", &T);
	while(T--){
		ans = inf;
		while(!pq.empty()) pq.pop();
		sum = 0ll;
		scanf("%lld%lld", &n, &k);
		for(int i = 1; i <= n; i++){
			scanf("%lld", &a[i].a);
		}
		for(int i = 1; i <= n; i++){
			scanf("%lld", &a[i].b);
		}
		sort(a + 1, a + n + 1, [&](node x, node y){
			return x.a < y.a;
		});
		for(int i = 1; i < k; i++){
			pq.push(a[i].b);
			sum += a[i].b;
		}
		for(int i = k; i <= n; i++){
			ans = min(ans, (sum + a[i].b) * a[i].a);
			pq.push(a[i].b);
			sum += a[i].b;
			sum -= pq.top();
			pq.pop();
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路

如果我们知道选取之后 $\max_{i\in S}A_i$ 的值，那么在比这个值小的 $A_i$ 中选取对应的尽可能小的 $k$ 个 $B_i$ 即可。

我们将 $A$ 与 $B$ 捆绑起来以 $A$ 为关键字从小到大排序，这样指定一个 $A_i$，可以选取的 $B_j$ 一定满足 $j\in[1,i]$。需要注意的是由于当前 $A_i$ 为最大值，所以它对应的 $B_i$ 是必选的。

用优先队列保存当前 $K-1$ 个最小的 $B_i$ 和其总和即可，从第 $K$ 个开始遍历数组，记录 $A_i$ 与和的乘积的最小值。

时间复杂度 $O(\sum N\log N)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int a,b;
};
int T,k,n;
long long ans,sum;
node lis[200001];
priority_queue<int>q;
bool cmp(node a,node b){
	return a.a < b.a;
}
int main(){
	scanf("%d",&T);
	while(T --){
		while(q.size()){//初始化
			q.pop();
		}
		sum = 0;
		scanf("%d%d",&n,&k);
		for(int i = 1;i <= n;i ++){
			scanf("%d",&lis[i].a);
		}
		for(int i = 1;i <= n;i ++){
			scanf("%d",&lis[i].b);
		}
		sort(lis + 1,lis + n + 1,cmp);//排序
		for(int i = 1;i < k;i ++){
			sum += lis[i].b,q.push(lis[i].b);//sum 统计最小的 K-1 个 B_i 的总和
		}
		ans = 8e18;
		for(int i = k;i <= n;i ++){
			ans = min(ans,lis[i].a * (sum + lis[i].b));//前面的 K-1 个最小的 B_j 加上当前的 B_i 乘上当前的 A_i
			if(!q.empty() && q.top() > lis[i].b){//如果当前更小，替换掉 K-1 个里最大的一个；K 可以等于一，需要判空
				sum = sum - q.top() + lis[i].b;
				q.pop();
				q.push(lis[i].b);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Xuan_qwq (赞：1)

### 题目大意
给你两个长度为 $N$ 的数组 $A$ 和 $B$，且 $S$ 是一个大小为 $K$ 的 $\{1,2,\dots,n\}$ 的子集，求：
$$(\max_{i\in S}A_i)\times(\sum_{i\in S}B_i)$$
的最小值。

### 思路
我们发现 $\max_{i\in S}A_i$ 是很好限制的，所以我们考虑从小到大枚举这个东西的值，再计算每种情况的表达式最小值。我们先把数组以 $A_i$ 为关键字排序。

考虑当前的最大值是 $A_i$，那么当最大值由 $A_i$ 变成 $A_{i+1}$ 时，要去掉一个当前所选集合中 $B_j$ 最大的元素，再加上 $B_{i+1}$，得到下一个我们选的集合。

很显然我们所选的 $B_i$ 是可以用优先队列动态维护的，再开一个变量动态记录此时队列里所有的元素和即可。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
priority_queue<int>q;
struct node{
	int a,b;
	bool operator < (const node & B) const{
		if(a==B.a)return b<B.b;//这句可以不要
		return a<B.a;
	}
}A[200005];
int n,k,T,ans,sum;
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>A[i].a;
		for(int i=1;i<=n;i++)cin>>A[i].b;
		ans=1e18,sum=0;
		sort(A+1,A+n+1);//以A[i]为关键字排序
		while(q.size())q.pop();//多测要清空，这个人因为没清空白吃了一发罚时
		for(int i=1;i<=k;i++){
			q.push(A[i].b);//先记录A[i]最大值最小时多选的的B[i]，很显然这是唯一确定的
			sum+=A[i].b;
		}
		ans=min(ans,A[k].a*sum);//记录此时答案
		for(int i=k+1;i<=n;i++){
			int tp=q.top();q.pop();//取当前所选的最大B[i]删掉
			sum-=tp;
			sum+=A[i].b;
			q.push(A[i].b);//加入新的B[i+1]
			ans=min(ans,A[i].a*sum);//更新答案
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：zhangzheng2026 (赞：1)

我们可以看出 $\displaystyle\ \left(\max_{i\ \in\ S}\ A_i\right)$ 的值只会有 $n-k+1$ 个，所以我们可以枚举最大值，算出最大值为 $A_i$ 时答案的最小值，且比 $A_i$ 小的数的个数要 $\ge k-1$。为了方便枚举最大值，我们先将 $A$ 和 $B$ 以 $A_i$ 的值从小到大排序。因为最大值确定时肯定优先选 $B_i$ 更小的，所以我们可以用一个堆存储当前前 $k$ 小的 $B_i$ 的值，每次加入新值前把最大值删去，再用一个变量储存当前在堆中的数的和即可，时间复杂度 $O(N \log N)$。

注意：
- 当最大值为 $A_i$ 时， $B_i$ 是必选的。
- 要开 long long。

code：
```cpp
#include <bits/stdc++.h>
#define int long long//开long long
using namespace std;
int t,n,k,ans;
struct node{int a,b;}e[200005];
bool cmp(node x,node y){return x.a<y.a;}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//关同步流 
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>e[i].a;
		for(int i=1;i<=n;i++) cin>>e[i].b;
		sort(e+1,e+n+1,cmp);//排序 
		priority_queue<int>pq;
		int now=0;//存储堆中的数之和 
		for(int i=1;i<=k;i++) pq.push(e[i].b),now+=e[i].b;
		ans=now*e[k].a;
		for(int i=k+1;i<=n;i++)//枚举最大值 
		{
			now-=pq.top();
			pq.pop();
			pq.push(e[i].b);
			now+=e[i].b;
			ans=min(ans,now*e[i].a);//取最小值 
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：zjj2024 (赞：0)

### 思路
考虑贪心。

发现 $ 1\ \leq\ A_i,\ B_i\ \leq\ 10^6 $，于是想到开桶。

考虑将 $A$ 从小到大排序，每次往桶中的 $A_i$ 位置加入 $B_i$。

由于 $A$ 单调递增，所以每次只取第 $i$ 项以前的值，则 $\max_{j\ \in\ S}\ A_j$ 为值为 $A_i$，此时选 $B$ 在桶中的值中的前 $K$ 小一定最优。

可以用树状数组。在桶中单点增加，后面二分前 $K$ 小。

每次加入值，如果值够了，便把之前统计的最大的值删掉，然后加入这一项，这样一定最优。

设阈值为 $V$，单次复杂度为 $O(N\log_2^2V)$
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000005;
struct T
{
	ll a,b;
}a[N];
int c[N];
bool cmp(T a,T b)
{
	return a.a<b.a;
}
void add(int x)//树状数组
{
	for(;x<N;x+=x&(-x))
		c[x]++;
}
void add_(int x)//清空时用
{
	for(;x<N;x+=x&(-x))
		c[x]--;
}
int get(int x)//统计1到i的总和
{
	int ans=0;
	for(;x>0;x-=x&(-x))
		ans+=c[x];
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T,n,k;
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		vector<int>v;
		for(int i=1;i<=n;i++)cin>>a[i].a;
		for(int i=1;i<=n;i++)cin>>a[i].b;
		sort(a+1,a+n+1,cmp);//按a[i].a排序
		ll ans=1e18,cnt=0,sum=0;
		for(int i=1;i<=n;i++)
		{
			add(a[i].b);
			cnt++;
			sum+=a[i].b;//由于最大值为当前项，当前项必选
			if(cnt==k)ans=min(ans,a[i].a*sum);//计算当前权值
			if(cnt<=k)continue;
			int l=1,r=1000000,mid;
			while(l<r)//二分出一个最大的原来统计过的值
			{
				mid=(l+r)>>1;
				if(get(mid)>k)r=mid;
				else l=mid+1;
			}
			add_(l);
			v.push_back(l);//清空时用
			cnt--;
			sum-=l;//减去最大值
			ans=min(ans,a[i].a*sum);
		}
		cout<<ans<<'\n';
		for(int i=0;i<v.size();i++)
			add(v[i]);
		for(int i=1;i<=n;i++)
			add_(a[i].b);
	}
	return 0;
}
```

---

## 作者：HotWood (赞：0)

# 题意
给你 $2$ 个序列 $A$ 和 $B$，找到任意大小为 $K$ 的集合 $S$，满足 $S\subseteq \left[1,n \right]\cap \N$，求 $\displaystyle\ \left(\max_{i\ \in\ S}\ A_i\right)\ \times\ \left(\sum_{i\ \in\ S}\ B_i\right)$ 的最小值

# 思路
一开始想到动态规划，考虑 $f_{i,j,k}$ 表示考虑到第 $i$ 个数，选了 $j$ 个，最大值为 $k$ 时的最小值，但很明显复杂度炸掉且难以用数据结构优化。

后来想到如果选了 $A_i$ 那么 $B_i$ 是一定要选的，可以把 $A_i$ 和 $B_i$ 打个包按 $A_i$ 单调递增排序，再从小往大选。

排完序后，当我们选到 $A_i$ 时，有 $\displaystyle\ \left(\max_{j\ \in\ S_{now}}\ A_j\right)=A_i$，这意味着我们只用关心 $\displaystyle\sum_{j\ \in\ S_{now}}B_j$，为了让结果尽量小，选前 $i$ 个中前 $K$ 小的 $B_j$ 就可以了。

# 实现
我们将 $i$ 从 $1$ 扫到 $n$，把 $B_i$ 扔进数据结构里，当 $i\geq K$ 时更新答案。

满足有序、查排名、求和的数据结构有很多，本题我们使用权值线段树实现。

注：本题 $B_i$ 范围较小，普通权值线段树可以胜任，但当 $B_i$ 范围过大时，只能选择平衡树或常数较大的动态开点权值线段树，以下代码用动态开点权值线段树实现。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=2e5+10,mx=1e6+10;
class xds{
    struct node{
        node *ls,*rs;
        long long l,r;
        long long dt,vl;
    }root;
    void newl(node *p){
        (*p).ls=new node;
        (*p).ls->dt=(*p).ls->vl=0;
        (*p).ls->ls=(*p).ls->rs=NULL;
        (*p).ls->l=(*p).l;
        (*p).ls->r=((*p).l+(*p).r)/2;
        return ;
    }
    void newr(node *p){
        (*p).rs=new node;
        (*p).rs->dt=(*p).rs->vl=0;
        (*p).rs->ls=(*p).rs->rs=NULL;
        (*p).rs->l=((*p).l+(*p).r)/2+1;
        (*p).rs->r=(*p).r;
        return ;
    }
    void opcg(node *p,long long sp,bool b){
        if((*p).l==(*p).r){
            if(!b){
                (*p).dt=0;
                (*p).vl=0;
            }else{
                (*p).dt+=(*p).l;
                (*p).vl+=1;
            }
            return ;
        }
        long long m=((*p).l+(*p).r)/2;
        if(sp<=m){
            if((*p).ls==NULL){
                newl(p);
            }
            opcg((*p).ls,sp,b);
        }else{
            if((*p).rs==NULL){
                newr(p);
            }
            opcg((*p).rs,sp,b);
        }
        (*p).dt=(*p).vl=0;
        if((*p).ls!=NULL){
            (*p).dt+=(*p).ls->dt;
            (*p).vl+=(*p).ls->vl;
        }
        if((*p).rs!=NULL){
            (*p).dt+=(*p).rs->dt;
            (*p).vl+=(*p).rs->vl;
        }
        return ;
    }
    long long summ(node *p,long long l,long long r){
        if((*p).l>=l&&(*p).r<=r){
            return (*p).dt;
        }
        long long m=((*p).l+(*p).r)/2;
        long long ret=0;
        if(l<=m&&((*p).ls!=NULL)){
            ret+=summ((*p).ls,l,r);
        }
        if(r>m&&((*p).rs!=NULL)){
            ret+=summ((*p).rs,l,r);
        }
        return ret;
    }
    long long sumv(node *p,long long l,long long r){
        if((*p).l>=l&&(*p).r<=r){
            return (*p).vl;
        }
        long long m=((*p).l+(*p).r)/2;
        long long ret=0;
        if(l<=m&&((*p).ls!=NULL)){
            ret+=sumv((*p).ls,l,r);
        }
        if(r>m&&((*p).rs!=NULL)){
            ret+=sumv((*p).rs,l,r);
        }
        return ret;
    }
    long long rkfdd(node *p,int rk){
        if((*p).l==(*p).r){
            return (*p).l;
        }
        if((*p).ls!=NULL){
            if((*p).ls->vl>=rk){
                return rkfdd((*p).ls,rk);
            }else{
                rk-=(*p).ls->vl;
            }
        }
        return rkfdd((*p).rs,rk);
    }
    public:
    void build(long long l,long long r){
        root.l=l;root.r=r;root.dt=0;
        root.ls=root.rs=NULL;
        return ;
    }
    void cg(long long sp,bool b){
        opcg(&root,sp,b);
        return ;
    }
    long long sum(long long l,long long r){
        return summ(&root,l,r);
    }
    long long sv(long long l,long long r){
        return sumv(&root,l,r);
    }
    long long rkfd(int rk){
        return rkfdd(&root,rk);
    }
}f;
int n,k,t;
struct sj{
    int a,b;
    bool operator<(sj b){
        return a<b.a;
    }
}a[N];
int main(){
    ios::sync_with_stdio(0);
    f.build(0,mx);
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i].a;
        }
        for(int i=1;i<=n;i++){
            cin>>a[i].b;
        }
        sort(a+1,a+n+1);
        long long ans=1e18,tp;
        for(int i=1;i<k;i++){
            f.cg(a[i].b,1);
        }
        for(int i=k;i<=n;i++){
            f.cg(a[i].b,1);
            long long aaa=f.rkfd(k);
            tp=f.sum(0,aaa-1);
            aaa=aaa*(k-f.sv(0,aaa-1));
            ans=min(ans,(aaa+tp)*a[i].a);
        }
        for(int i=1;i<=n;i++){
            f.cg(a[i].b,0);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：Sih_qwq (赞：0)

果然还是太弱了。

## 题意

给你两串数 $a$ 和 $b$，其中 $a_i$ 和 $b_i(1 \le i \le n)$ 一一对应成一个二元组。要求选出 $k$ 个二元组，使得这些二元组的 $a$ 的最大值与 $b$ 的和的乘积最小。

数据多测。（AT 也搞上多测了？）

## 思路

分别考虑两个限制能否拆分。

对 $a$ 取最大值可以想到能否求区间的最大值，但是对 $b$ 求和难搞，且 $b$ 不一定在有规律可循的区间内。所以换个方向考虑。

考虑单独 $b$ 的取法。贪心地想从一个序列里求出一个子序列，使得 $b$ 的和最小。在这种情况下考虑 $a$，那么我们也要让 $a$ 的最大值尽可能小，且不能影响 $b$。可以想到将二元组按照 $a$ 的大小排序，那么问题就转换为：在前 $i(k \le i \le n)$ 个数中，选出 $k$ 个数使得和最小。

这个东西用 dp 的话，复杂度是立方的。想一想有什么数据结构或是 STL。由于这个人比较菜，不会用数据结构，所以想可以用堆或 set。

每插入一个数，看他会不会比第 $k$ 个数小，是的话就修改和，然后再插入。

问题是我们怎么知道第 $k$ 个数多大。

堆和 set 无法直接访问元素。但是我们可以维护一个只存了 $k$ 个数的堆或是 set。

于是 set 可以直接用了。复杂度 $O(\log n)$。

如果是堆该怎么处理？我们没办法实时将前 $k$ 个数取出来加和。

![](https://s3.bmp.ovh/imgs/2024/10/20/f8f842c30b4ea66c.png)

我们要学会和小鲨鱼一样思考。

正难则反。

我们不要看他会不会比第 $k$ 个数小，而是看他会不会比第 $k$ 个数大。把当前的数扔到堆里，再弹一个堆里最大的数出来，加上当前的数，减掉最大的数，就可以得到最优的答案。如果当前的数比第 $k$ 个数大，那么弹出后直接减掉；如果比第 $k$ 个数小，那么我们得到了一个更优的子序列和。

把这个和进行修改，然后乘上当前的 $a_i$，与答案取最小值即可。

## AC Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll sum, ans;
int n, k;
struct node {
	int a, b;
	bool operator < (const node &T) const {
		return a < T.a;
	}
} d[200010];
priority_queue < int > q;
void run(void) {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", &d[i].a);
	for (int i = 1; i <= n; ++i) scanf("%d", &d[i].b);
	sort(d + 1, d + n + 1);
	sum = 0;
	while (!q.empty()) q.pop();
	for (int i = 1; i <= k; ++i) q.push(d[i].b), sum += d[i].b;
	ans = d[k].a * sum;
	for (int i = k + 1; i <= n; ++i) {
		q.push(d[i].b);
		int x = q.top();
		q.pop();
		sum = sum - x + d[i].b;
		ans = min(ans, d[i].a * 1ll * sum);
	}
	printf("%lld\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) run();
	return 0;
} 
```

---

## 作者：stripe_python (赞：0)

先按 $A_i$ 排序。

枚举 $i \in [k,n]$，此时我们把 $\max A_i$ 确定为 $A_i$。贪心地，从 $[1,k-1]$ 中选 $k -1$ 个较小的 $B_i$ 即可。这可以用大根堆维护。复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
long long n, k;
struct node {
	long long a, b;
} a[N];

void _main() {
	memset(a, 0, sizeof(node) * (n + 1));
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i].a;
	for (int i = 1; i <= n; i++) cin >> a[i].b;
	sort(a + 1, a + n + 1, [](const node& a, const node& b) -> bool {
		return a.a < b.a;
	});
	
	priority_queue<long long> q;
	long long sum = 0;
	for (int i = 1; i <= k - 1; i++) sum += a[i].b, q.emplace(a[i].b);
	
	long long res = LLONG_MAX;
	for (int i = k; i <= n; i++) {
		sum += a[i].b;
		q.emplace(a[i].b);
		res = min(res, a[i].a * sum);
		
		sum -= q.top(); q.pop();
	}
	cout << res << '\n';
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr), cerr.tie(nullptr);
	
	int t = 1; for (cin >> t; t--; ) _main();
	return 0;
}
```

---

## 作者：Cute__yhb (赞：0)

## 思路

计算每个点作为最大值时，最小的积是多少。

先对 $a$ 升序排序，容易发现，当 $a_i$ 为 $k$ 个数中最大值时，其余 $k-1$ 个数都在 $a_i$ 前面。

所以，当 $a_i$ 为最大值时，找一下前面 $i-1$ 个数中选 $k-1$ 个数和的最小值。

用大根堆维护即可，当堆中元素比 $k-1$ 多时，直接删除堆顶，直到堆中有 $k-1$ 个数

## 代码


```cpp
// Problem: E - Max × Sum
// Contest: AtCoder - AtCoder Beginner Contest 376
// URL: https://atcoder.jp/contests/abc376/tasks/abc376_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define F(i,l,r) for(int i=l;i<=r;i++)
#define UF(i,r,l) for(int i=r;i>=l;i--)
#define p_q priority_queue
#define pb push_back
#define mk make_pair
#define pii pair<int,int> 
#define ve vector
#define endl '\n'
#define fi first
#define se second
#define INF 0x3f3f3f3f
int n,k;
struct node{
	ll a,b;
}a[200005];
bool cmp(node a,node b){
	if(a.a==b.a) return a.b<b.b;
	return a.a<b.a;
}
p_q<ll,ve<ll>,less<ll> >q;//大根堆
void solve(){
	cin>>n>>k;
	while(!q.empty()) q.pop();//多测，清空堆
	for(int i=1;i<=n;i++) cin>>a[i].a;
	for(int i=1;i<=n;i++) cin>>a[i].b;
	sort(a+1,a+1+n,cmp);//对 a 进行排序
	ll ans=1e18,s=0;//ans为答案
	for(int i=1;i<=n;i++){
		if(i<k){//堆中不足 k-1 个数，直接入堆
			q.push(a[i].b);
			s+=a[i].b;//计算堆中元素总和
		}
		else{
			ll sum=a[i].b+s;
			ans=min(ans,sum*a[i].a);//计算 a[i] 为最大值的最小答案
			s+=a[i].b;
			q.push(a[i].b);
			s-=q.top();//弹出堆顶，更新堆中元素综合
			q.pop();
		}
	}
	cout<<ans<<endl;//输出
}
int main(){
	int _;
	cin>>_;
	while(_--) solve();
    return 0;
}
```

---

## 作者：Double_Light (赞：0)

可以把 $a_i$ 和 $b_i$ 看成一对二元组 $(x,y)$。

首先按 $x$ 排序。从小到大枚举最大值，问题转化成快速判断前 $i$ 个二元组中最小的 $k$ 个 $y$ 之和。

可以考虑用大根堆实现。每次枚举到一个 $i\geq k$，将 $y_i$ 加入堆中，求出当前堆中的和更新答案，然后再将堆顶弹出。堆中的和只需要入堆和出堆时记录一下就可以了。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
int T;
int n,k;
struct node{
	int x,y;
}a[200005];
bool cmp(node x,node y){
	return x.x<y.x;
}
int b[200005],tot;
int sum;
int ans;
priority_queue<int,vector<int>,less<int> >q;
signed main(){
	cin>>T;
	while(T--){
		while(!q.empty())q.pop();
		ans=9e18;
		cin>>n>>k;
		tot=0;sum=0;
		for(int i=1;i<=n;i++)cin>>a[i].x;
		for(int i=1;i<=n;i++)cin>>a[i].y;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<k;i++){
			q.push(a[i].y);
			sum+=a[i].y;
		}
		for(int i=k;i<=n;i++){
			q.push(a[i].y);
			sum+=a[i].y;
			ans=min(ans,sum*a[i].x);
			int x=q.top();
			sum-=x;
			q.pop();
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## [[ABC376E] Max × Sum](https://atcoder.jp/contests/abc376/tasks/abc376_e)

## 题意

给出 $A_1,A_2,\cdots,A_N$，$B_1,B_2,\cdots,B_N$。

令 $S$ 为 $\lbrace1, 2, \dots, N\rbrace$ 的一个大小为 $K$ 的子集，问该表达式的最小值：

$$
\displaystyle \left(\max_{i \in S} A_i\right) \times \left(\sum_{i \in S} B_i\right)
$$

## 思路

可以发现 $\max_{i\in S} A_i$ 最多只有 $N$ 种取值，于是可以将 $A,B$ 按照 $A_i$ 升序排序，设 $x$ 为 $S$ 中的最大数字，则问题可以转换成求以下表达式的最小值：

$$
A_x\times \left(\sum_{i \in S} B_i\right)
$$

这时再枚举 $x$，则只需要最小化 $\sum_{i \in S} B_i$。因为选了 $A_x$，所以 $B_x$ 一定被选，剩下的 $B_i$ 则取前 $(x-1)$ 项的前 $(K-1)$ 小值，该过程可以使用 `multiset` 维护。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,k,ans;
struct node{
	int x,y;
}a[2000005];
bool cmp(node x,node y){
	return x.x<y.x;
}
multiset<int> bg;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	cin>>T;
	while(T--){
		bg.clear(),ans=LONG_LONG_MAX;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i].x;
		for(int i=1;i<=n;i++)
			cin>>a[i].y;
		sort(a+1,a+1+n,cmp);
		int nw=0;
		for(int i=1;i<k;i++)
			bg.insert(a[i].y),nw+=a[i].y;
		for(int i=k;i<=n;i++){
			ans=min(ans,(nw+a[i].y)*a[i].x);
			if(k!=1){//k=1时multiset为空，于是喜提RE
				if(a[i].y<*--bg.end()){//比前k-1小的最大值还小
					nw-=*--bg.end();
					bg.erase(--bg.end());
					nw+=a[i].y;
					bg.insert(a[i].y);
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

# 题意
求长度为 $k$ 的子集，对于所有的在 $k$ 中的元素 $i$，使得 $\max(a_i) \times \sum{b_i}$ 最小。
# 题解
枚举哪个 $a_i$ 是 $\max(a_i)$。用优先队列维护出 $\le a_i$ 的 $a_j$，$b_j$ 的最小值。取最小的 $k-1$ 个 $b_j$ 加上 $b_i$ 就是 $\max(a_i)=a_i$ 时的 $b_i$ 最小值，枚举哪种情况最小。

时间复杂度 $O(n \log n)$。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
struct p{
	int a,b;
	bool operator<(const p&y){return a<y.a||a==y.a&&b<y.b;}
}s[200010];
long long ans,sum;
priority_queue<int>h;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k),ans=1e18,sum=0;
		while(h.size())h.pop();
		for(int w=1;w<=n;w++)scanf("%d",&s[w].a);
		for(int w=1;w<=n;w++)scanf("%d",&s[w].b);
		sort(s+1,s+n+1);
		for(int w=1;w<=n;w++){
			h.push(s[w].b),sum+=s[w].b;
			while(h.size()>k)sum-=h.top(),h.pop();
			if(h.size()==k)ans=min(ans,sum*s[w].a);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

题很好，但是造数据的开多测的都没道德。

题意简述：

有 $n$ 个有序二元组 $(a_i,b_i)$，选出一个大小为 $K$ 的集合 $S$，使得 $(\max_{i\in S}a_i)\times(\sum_{i\in S}b_i)$。

注意到 $\max$ 不好处理，那么枚举 $\max$，注意到假如我们选 $i$，且 $a_i$ 最大。

那么我们是不是要在剩下比 $a_i$ 小的取前 $k-1$ 小的和？

权值线段树做完了。

另外，不要 TM 测完一组重构线段树，直接 T 飞！

还有，建议直接 `#define int long long`，这个数据好像是开满了，别问我为啥有 $10$ 发罚时。

[我的提交记录](https://atcoder.jp/contests/abc376/submissions/58985641)

---

## 作者：hjyowl (赞：0)

### 题目大意

给定 $n$ 和 $k$，求出在序列 $a$ 和 $b$ 中选择出来 $k$ 个数，使得：

$$(\max{a_{p_1},a_{p_2}\dots a_{p_k}}) \times (\sum_{i = 1}^k b_{p_k})$$

最小。

### 思路

首先按照 $a$ 排序。

我们令 $A=(\max{a_{p_1},a_{p_2}\dots a_{p_k}})$，$B=(\sum_{i = 1}^k b_{p_k})$。

这里很明显，由于 $a$ 是有序的，所以说我们对于 $a_i$，$A = a_i$。

接下来的问题，就是最小化后面的 $B$，考虑使用平衡树动态维护，定义一个变量 $s$ 来维护选择 $k$ 时的最小，每次不断插入 $b_i$，如果 $b_i$ 的排名在前 $k$ 名，那我们就把我们的 $s$ 加上 $b_i$ 并且减掉 $k+1$ 名的值，然后每次对于 $s \times a_i$ 求最小值。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 1000010;
struct owl{
	long long a,b;
}x[N];
bool cmp(owl x,owl y){
	return x.a < y.a;
}
const long long inf = 0x3f3f3f3f;
long long n;
struct sj{
	long long l,r;
	long long key,val,cnt,size;
}tr[N];
long long root,idx;
void pushup(long long p){
	tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}
long long get_node(long long key){
	tr[ ++ idx].key = key;
	tr[idx].val = rand();
	tr[idx].cnt = tr[idx].size = 1;
	return idx;
}
void zig(long long &p){
	long long q = tr[p].l;
	tr[p].l = tr[q].r,tr[q].r = p,p = q;
	pushup(tr[p].r),pushup(p);
}
void zag(long long &p){
	long long q = tr[p].r;
	tr[p].r = tr[q].l,tr[q].l = p,p = q;
	pushup(tr[p].l),pushup(p);
}
void build(){
	get_node(-inf), get_node(inf);
	root = 1, tr[1].r = 2;
	pushup(root);
	if (tr[1].val < tr[2].val){
		zag(root);
	}
}
void insert(long long &u, long long key) {
	if (u == 0){
		u = get_node(key); 
	}
	else {
		if (tr[u].key == key) {
			tr[u].cnt ++ ;
		} else {
			if (tr[u].key > key) {
				insert(tr[u].l, key);
				if (tr[tr[u].l].val > tr[u].val){
					zig(u);
				}
			} 
			else {
				insert(tr[u].r, key);
				if (tr[tr[u].r].val > tr[u].val){
					zag(u);
				}
			}
		}
	}
	pushup(u);
}
void del(long long &u, long long key) {
	if (u == 0){
		return ;
	}
	if (tr[u].key == key) {
		if (tr[u].cnt > 1){
			tr[u].cnt -- ;
		}
		else {
			if (tr[u].l || tr[u].r) { 
				if (!tr[u].r || tr[tr[u].l].val) {
					zig(u);
					del(tr[u].r, key);
				} 
				else {
					zag(u);
					del(tr[u].l, key);
				}
			} 
			else{
				u = 0;
			}
		}
	} 
	else if (tr[u].key > key){
		del(tr[u].l, key);
	}
	else{
		del(tr[u].r, key);
	}
	pushup(u);
}
long long get_rank(long long u, long long key) {
	if (u == 0){
		return 0;
	}
	if (tr[u].key == key){
		return tr[tr[u].l].size + 1;
	}
	if (tr[u].key > key){
		return get_rank(tr[u].l, key);
	}
	return tr[tr[u].l].size + tr[u].cnt + get_rank(tr[u].r, key);
}
long long get_key(long long u, long long rank) {
	if (u == 0){
		return inf;
	}
	if (tr[tr[u].l].size >= rank){
		return get_key(tr[u].l, rank);
	}
	if (tr[tr[u].l].size + tr[u].cnt >= rank){
		return tr[u].key;
	}
	return get_key(tr[u].r, rank - tr[tr[u].l].size - tr[u].cnt);
}
long long get_pr(long long u, long long key) {
	if (u == 0) {
		return -inf;
	}
	if (tr[u].key >= key) {
		return get_pr(tr[u].l, key);
	}
	return max(get_pr(tr[u].r, key), tr[u].key);
}
long long get_ne(long long u, long long key) {
	if (u == 0) {
		return inf;
	}
	if (tr[u].key <= key) {
		return get_ne(tr[u].r, key);
	}
	return min(get_ne(tr[u].l, key), tr[u].key);
}
int main(){
	//3 6 7
	//9 4 2
	//i
	//a[i]
	//3
	long long T;
	cin >> T;
	while (T -- ){
		for (int i = 1; i <= 1000; i ++ ){
			int t = get_key(root,i);
			del(root,t);
		}
		build();
		long long n,m;
		cin >> n >> m;
		for (long long i = 1; i <= n; i ++ ){
			cin >> x[i].a;
		}
		for (long long i =1 ;i <= n; i ++ ){
			cin >> x[i].b;
		}
		sort(x + 1,x + 1 + n,cmp);
		long long now = 0;
		for (long long i = 1; i <= m; i ++ ){
			insert(root,x[i].b);
			now += x[i].b;
		}
		long long res = now * x[m].a;
		for (long long i = m + 1; i <= n; i ++ ){
			insert(root,x[i].b);
			if (get_rank(root,x[i].b) - 1 <= (m + 1)){
				now += x[i].b;
				now -= get_key(root,(m + 2));
			}
			res = min(res,now * x[i].a);
		}
		cout <<res << endl;
	}
	return 0;
}
```

---

