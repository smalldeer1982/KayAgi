# Kolya and Movie Theatre

## 题目描述

Recently, Kolya found out that a new movie theatre is going to be opened in his city soon, which will show a new movie every day for $ n $ days. So, on the day with the number $ 1 \le i \le n $ , the movie theatre will show the premiere of the $ i $ -th movie. Also, Kolya found out the schedule of the movies and assigned the entertainment value to each movie, denoted by $ a_i $ .

However, the longer Kolya stays without visiting a movie theatre, the larger the decrease in entertainment value of the next movie. That decrease is equivalent to $ d \cdot cnt $ , where $ d $ is a predetermined value and $ cnt $ is the number of days since the last visit to the movie theatre. It is also known that Kolya managed to visit another movie theatre a day before the new one opened — the day with the number $ 0 $ . So if we visit the movie theatre the first time on the day with the number $ i $ , then $ cnt $ — the number of days since the last visit to the movie theatre will be equal to $ i $ .

For example, if $ d = 2 $ and $ a = [3, 2, 5, 4, 6] $ , then by visiting movies with indices $ 1 $ and $ 3 $ , $ cnt $ value for the day $ 1 $ will be equal to $ 1 - 0 = 1 $ and $ cnt $ value for the day $ 3 $ will be $ 3 - 1 = 2 $ , so the total entertainment value of the movies will be $ a_1 - d \cdot 1 + a_3 - d \cdot 2 = 3 - 2 \cdot 1 + 5 - 2 \cdot 2 = 2 $ .

Unfortunately, Kolya only has time to visit at most $ m $ movies. Help him create a plan to visit the cinema in such a way that the total entertainment value of all the movies he visits is maximized.

## 说明/提示

The first test case is explained in the problem statement.

In the second test case, it is optimal not to visit any movies.

In the third test case, it is optimal to visit movies with numbers $ 2 $ , $ 3 $ , $ 5 $ , $ 6 $ , so the total entertainment value of the visited movies will be $ 45 - 6 \cdot 2 + 1 - 6 \cdot 1 + 39 - 6 \cdot 2 + 11 - 6 \cdot 1 = 60 $ .

## 样例 #1

### 输入

```
6
5 2 2
3 2 5 4 6
4 3 2
1 1 1 1
6 6 6
-82 45 1 -77 39 11
5 2 2
3 2 5 4 8
2 1 1
-1 2
6 3 2
-8 8 -2 -1 9 0```

### 输出

```
2
0
60
3
0
7```

# 题解

## 作者：Rain_javalearner (赞：14)

赛场上止步于此。。。

一个很重要的性质是，$d$ 项对答案的影响只跟 $m$ 场中最后一场电影有关系。那么枚举最后一场的位置，我们可以只关心之前所有电影的 `entertainment value` 的和，而不关心看它们的时间。

直接用优先队列贪心即可。遇到正数丢进去，超过 $m$ 个就把最小的丢出来。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long i64;

i64 t;
i64 n, m, d;
i64 x;
priority_queue<i64, vector<i64>, greater<i64> > q;
int main() {
	scanf("%lld", &t);
	while(t--) {
		scanf("%lld%lld%lld", &n, &m, &d);
		i64 ans = 0, sum = 0;
		while(!q.empty()) q.pop();
		for(i64 i = 1 ; i<= n ; i++) {
			scanf("%lld", &x);
			if(x > 0) q.push(x), sum += x;
			while(q.size() > m) sum -= q.top(), q.pop();
			ans = max(ans, sum - d*i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：Scorilon (赞：4)

先注意到我们娱乐值损耗的多少只与最后一场电影有关系，所以假设最后一场电影看的下标为 $k$，那么最后就要减去 $d \times k$。

得出这个性质之后开个小根堆反悔贪心即可，首先 $a_i<0$ 的没必要考虑，对于 $a_i>0$ 的，如果还没到 $m$ 场电影，我们就直接往里塞就可以，如果到了，我们就进行反悔操作，取出已选的贡献最小的那场电影，然后看看会不会更优，如果会的话就加进去。

算是反悔贪心板子题，时间复杂度 $O(n\log n)$。

然后就是一定要记得开 ```long long```，吃了两发。

```cpp
#include <cstdio>
#include <queue>
#include <algorithm>

typedef long long ll;

int t;
int n,m,d;
int a[200005];

void solve() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d%d",&n,&m,&d);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		std::priority_queue<int> q;
		int tot=0;
		ll ans=0,sum=0;
		for(int i=1;i<=n;i++) {
			if(a[i]<0) continue;
			if(tot<m) {
				tot++;
				q.push(-a[i]);//大根堆每次存相反数作用就是小根堆
				sum+=a[i];
			} else if(-q.top()<a[i]) {//反悔操作
				sum+=q.top();
				q.pop();
				sum+=a[i];
				q.push(-a[i]);
			}
			ans=std::max(ans,sum-1ll*d*i);
		}
		printf("%lld\n",ans);
	}
}

int main() {
	solve();
	return 0;
}
```


---

## 作者：YBaggio (赞：3)

# 题意
有 $n$ 场电影，第 $i$ 场电影能够带来 $a_i$ 的快乐值，但是当距离上一次观看电影 $cnt$ 天后观看一场电影，这场电影带来的欢乐值会减少 $d \cdot cnt$（可能减少至负数）。现在我们可以去选择观看 $n$ 场电影中的不大于 $m$ 场，使得最终所获得的欢乐值最大。

# 题解
假设我们观看了第 $i_1, i_2 \dots i_s$ 这 $s$ 场电影，那么我们获得的欢乐值表示为 

$a_{i_1} - i_1 \cdot d + a_{i_2} - (i_2 - i_1) \cdot d + \dots + a_{i_s} - (i_s - i_{s - 1}) \cdot d$

将 $d$ 提取出来得到：

$a_{i_1} + a_{i_2} + \dots + a_{i_s} - i_s \cdot d$

由此可见，$d$ 的系数仅与看的最后一场 $i_s$ 有关，因此我们可以枚举看的最后一场电影，得到 $- i_s \cdot d$ 的取值，随后贪心选择第 $i_1 \dots i_{s-1}$ 场电影。

## Code
```cpp
#include <iostream>
#include <queue>
typedef long long ll;
using namespace std;
const int maxn = 200010;
int t, n, m;
ll d, ans, a[maxn];
priority_queue <pair <ll, int>> q; 
int main () {
  ios::sync_with_stdio (false), cin.tie (0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> d;
    ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll sum = 0;
    while (q.size ()) q.pop ();
    for (int i = 1; i <= n; i++) { //枚举 i_s
      ans = max (ans, sum + a[i] - d * i);
      if (a[i] > 0) { //选择a[i]最大的m场（当然如果是负数就显然不会选）
        q.push ({-a[i], i});
        sum += a[i];
        if (q.size () >= m) {
          sum += q.top ().first;
          q.pop ();
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
```


---

## 作者：lfxxx (赞：3)

赛场上想复杂就一直没过。。。

考虑这样一个结论，把所有因为不去电影院产生的贡献减少累加起来，不难发现其只跟最后一次去电影院的事件有关，因此考虑一次将每天的选择加入答案，再用当前答案减去当前天数乘 $d$ 更新最后的答案。

问题是如何加入答案？

不难发现这是一个容量固定为 $1$ 的背包问题，考虑反悔贪心，每次将价值最小的拿出来反悔即可。

```cpp
/* 
1 
3 1 4
-7 5 -1
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;
multiset<int,less<int> > s;
int a[maxn]; 
bool cmp(int A,int B){
	return A>B;
}
void work(){
	s.clear();
	int n,m,d,ans=0,res=0;
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(s.size()<m&&x>0){
			s.insert(x);
			ans+=x;
		}
		else{
			int top=(*s.begin());
			if(top<x){
				s.erase(s.find(top));
				ans-=top;
				s.insert(x);
				ans+=x;
			}
		}
		res=max(res,ans-d*i);
	}
	cout<<res<<'\n';
} 
int T;
signed main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>T;
while(T--) work();

return 0;
}
/*
1
6 6 6
-82 45 1 -77 39 11
*/ 
```


---

## 作者：Special_Tony (赞：1)

[洛谷传送门](/problem/CF1862E) & [CF 传送门](https://codeforces.com/problemset/problem/1862/E)
# 思路
这题中 $a_i$ 可能是非正数，非正数我们肯定不选。我们设最后一个被选中的数的下标是 $i$，则最优策略就是选择前 $i$ 个数中前 $m$ 大的数，并以下标从小到大的顺序去走，这样总共答案就是前 $i$ 个数中前 $m$ 大的数之和减去 $i\times d$ 即可，最后，我们只要对每个 $i$ 算出来的答案取 $\max$ 即可。

前 $i$ 个数的前 $m$ 大值我们可以定义一个优先队列 $q$ 用于存储前 $m$ 大值，再定义变量 $sum$ 表示 $q$ 内的数之和即可。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll; //不开 ll 见祖宗
ll t, n, x, sum, maxx, m, d;
priority_queue <ll, vector <ll>, greater <ll>> q; //小根堆
ll f () {
	sum = maxx = 0; //多组数据要清零
	while (! q.empty ()) //多组数据要清空
		q.pop ();
	cin >> n >> m >> d;
	while (n --) {
		cin >> x;
		if (x > 0) { //是正数才要添加
			q.push (x), sum += x;
			if (q.size () > m) //超过了 m 个，舍弃一个最小值
				sum -= q.top (), q.pop ();
		}
		sum -= d; //又要减掉一个 d 了
		maxx = max (maxx, sum); //取 max
	}
	return maxx;
}
int main () {
	cin >> t;
	while (t --)
		cout << f () << '\n';
	return 0;
}
```

---

## 作者：ax_by_c (赞：1)

# 题意描述

题意有点晕，讲一下吧。

就是选择至多 $m$ 个数，然后答案是每个选择的数的权值之和,但是要减去**离上一次选择的位置的差** （当前位置也算） （假设初始选了 $0$）乘以 $d$ **的积**。

问答案最大是多少。

# 解题思路

一开始想的是直接选大的数。

然后发现最后一次选择后的那些数的贡献（都是负数）是不会算上的。

所以先枚举最后一次选的位置。

然后设这个位置为 $p$，那么不管前面怎么选，减去的和都是 $p \times d$。（因为对于每个位置，无论是选还是不选，都要减去一个 $d$）

所以就是在前面选较大的数。

所以用一个堆来动态维护前 $m-1$ 个正整数，然后再维护堆内元素之和 $sum$。

那么计算时位置 $p$ 的最大答案就是 $sum+a_p-p \times d$。

然后如果 $a_p$ 是个正整数，且最小的数比 $a_p$ 小，则进行替换。

注意，当堆还没装满时，如果 $a_p$ 是个正整数，可以直接加入。

注意，是先计算后加入。

核心代码：

```cpp
cin>>n>>m>>k;
int ans=0,sum=0;
priority_queue<int,vector<int>,greater<int> > pq;
for(int i=1;i<=n;i++)
{
	cin>>a[i];
	ans=max(ans,sum+a[i]-i*k);
	if(a[i]>=0)
	{
		if(pq.size()<m-1)
		{
			pq.push(a[i]);
			sum+=a[i];
		}
		else if(!pq.empty())
		{
			if(pq.top()<a[i])
			{
				sum-=pq.top();
				pq.pop();
				pq.push(a[i]);
				sum+=a[i];
			}
		}
	}
}
cout<<ans<<'\n';
```

---

## 作者：One_JuRuo (赞：1)

## 思路

假设我们选择了第 $p_1,p_2 \cdots p_x$ 场电影，那么减去的舒畅值是 $d\times(p_1+p_2-p_1+\cdots+p_x-p_{x-1})=d\times p_x$ 所以减去的舒畅值，只与最后一场电影的天数有关。

所以我们可以枚举最后一场电影在第几天，假设在 $i$ 天。

那么，减去的舒畅值是固定的 $i\times d$，所以我们需要在前 $i$ 场电影中，选择权值最大的 $m$ 场，特别的，如果某场电影的舒畅值是负数，我们就不选，因为这场电影对答案的贡献是负的。

现在，我们需要思考的是如何快速地求出前 $i$ 个整数中所有非负整数前 $m$ 大的数之和。

于是我们想到了用优先队列处理这个问题。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,m,d,a;
long long sum,ans;
priority_queue<long long,vector<long long>,greater<long long> >q;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		while(!q.empty()) q.pop();
		scanf("%lld%lld%lld",&n,&m,&d),ans=sum=0;
		for(long long i=1;i<=n;++i)
		{
			scanf("%lld",&a);
			if(a<0) continue;
			q.push(a),sum+=a;
			if(q.size()>m) sum-=q.top(),q.pop();
			ans=max(ans,sum-d*i);
		}
		printf("%lld\n",ans);
	}
}
```

## 优化

大概是出题人没卡优先队列吧，上面的程序可以卡成 $\operatorname{TLE}$ 的，赛时以拿分为主，平时练习以彻底解决为主。所以，我们需要思考一种正确的复杂度的做法，也就是另一种可以得到数据顺序的数据结构，但是如果涉及了排序，时间复杂度至少都是 $O(\log n)$。

但是有一种不需要排序也能得到顺序的方式，那就是桶排，单纯的桶排想要找最小还是很麻烦，于是我们想到了 $\operatorname{set}$。

$\operatorname{set}$ 有一个功能是 $\operatorname{begin()}$ 可以求出这个集合最小的数字。（蒟蒻的我在看官方程序前都不知道）

所以我们只需要一个套了 $\operatorname{pair}$ 的 $\operatorname{set}$ 就可以代替上面的优先队列的相关操作。具体可以看[官方程序](https://codeforces.com/blog/entry/119715)。

**UPD：感谢大佬 @XSean 指出错误，$\operatorname{set}$ 的时间复杂度也是 $O(\log n)$，蒟蒻切腹谢罪。**

---

## 作者：DerrickLo (赞：0)

显然的，对于最后一天看电影的是第 $i$ 天，那么所有看的电影的娱乐价值下降的值就是 $d\times i$，那我们就可以对于每个 $1\le i\le n$，动态维护出所有 $1\le j \le i,a_j>0$ 的前 $m$ 大 $a_j$ 的和，可以使用 multiset 维护。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,a[200005],d;
multiset<int> st;
signed main(){
	cin>>t;
	while(t--){
		st.clear();
		cin>>n>>m>>d;
		for(int i=1;i<=n;i++)cin>>a[i];
		int nowsum=0,ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]<0)continue;
			if(st.size()<m){
				st.insert(a[i]);
				nowsum+=a[i];
				ans=max(ans,nowsum-d*i);
			}
			else{
				int minn=*st.begin();
				if(a[i]>minn){
					nowsum+=a[i]-minn;
					st.erase(st.begin());
					st.insert(a[i]);
					ans=max(ans,nowsum-d*i);
				}
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：XSean (赞：0)

[Problem - E - Codeforces](https://codeforces.com/contest/1862/problem/E)

## 基本思路：

思路：

- 将答案的式子化简一下：

假设在 $i_1, i_2, \ldots, i_k$ 看电影，那么式子： 
$$
(a_{i_1} - d \times i_1) + (a_{i_2} - d \times (i_2 - i_1)) + \times + (a_{i_k} - d \times (i_k - i_{k-1})) = (a_{i_1} + a_{i_2} + \ldots + a_{i_k}) - d \times i_k
$$

- 显然的：
  - 维护前缀长度不超过 $m$ 最大子序列和 $sum$。
  - 枚举 $k$，维护 $sum - d\times i_k$ 的最大值。

**时间复杂度：$O(N\log N)$**。

## 代码实现：

核心代码：

```cpp
//bool stt;
const int N = 2e5 + 10;
int n, m, d;
int a[N];
//bool edd;
int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
//	cerr << (&edd - &stt) / 1024.0 / 1024.0 << endl;
	int T; rd(T);
	while(T--){
		rd(n, m, d);
		rep(i, 1, n) rd(a[i]);
		LL sum = 0, ans = 0;
		priority_queue<int, vector<int>, greater<int>> heap;
		rep(i, 1, n){
			if(a[i] > 0){
				sum = sum + a[i];
				heap.push(a[i]);
				if(heap.size() > m){
					sum = sum - heap.top();
					heap.pop();
				}
				ans = max(ans, sum - (LL)i * d);
			}
		}
		prf("%lld\n", ans);
	}
	return 0;
}
```

**[完整代码](https://codeforces.com/contest/1862/submission/220387491)**



---

## 作者：Kedit2007 (赞：0)

### 思路

考虑转化一下题意。注意到 Kolya 快乐值的衰减实际上与其最后一个访问的天数成**正比**，具体地说，若 Kolya 最后一次访问电影院是在第 $i$ 天，则其快乐值会衰减 $d\cdot i$。

同时，如果去看某一场电影不能获得超过 $0$ 的快乐值，那么这一场电影肯定不去。这样便可以计算出若第 $i$ 天是 Kolya 最后一天去看电影，其获得的快乐值大小，具体地说，记 $s$ 是前 $i$ 个数中**前 $m$ 大的**大于零的数的和，其获得的快乐值为 $s - d\cdot i$。

现在只需遍历上文中的 $i$，计算快乐值最大值即可。前 $i$ 个数中前 $m$ 大的数之和可以用小根堆维护，当堆中元素不足 $m$ 时，直接压入堆中，累计和，否则判断堆顶与新元素的大小，若新元素大，则弹出堆顶压入新元素，同时更新和，否则不作任何操作。

### 参考代码

```cpp
void work()
{
	int n, m, d;
	cin >> n >> m >> d;
	int ans = 0, sum = 0;
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = 1; i <= n; i++)
	{
		int t;
		cin >> t;
		if (t > 0)
		{
			if (q.size() >= m)
			{
				sum -= q.top();
				t = max(t, q.top());
				q.pop();
			}
			q.push(t);
			sum += t;
		}
		ans = max(ans, sum - i * d);
	}
	cout << ans << endl;
}
```

---

## 作者：qejwdi (赞：0)

你会发现题目里的 $d$ 就是在诈骗你，比如说我最后一个在第 $a$ 天，那么显然我总的掉的票价就是 $a \times d$，那么对于一个 $i$，我就算出 1 到 $i$ 的前 $m$ 大值再减掉 $i \times d$。

# 代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int N = 2e5 + 5;
int a[N];
int n, m, d;
void solve() {
    scanf("%d%d%d", &n, &m, &d);
    long long ans = 0, ans_ = 0;
    priority_queue<int, vector<int>, greater<int> > q;
    for (int i = 1; i <= n; i ++ ) {
        scanf("%d", &a[i]);
        if (a[i] < 0) continue;
        if (q.size() < m) {
            q.push(a[i]);
            ans += a[i];
        } else {
            if (a[i] > q.top()) {
                ans -= q.top();
                q.pop();
                q.push(a[i]);
                ans += a[i];
            }
        }
        ans_ = max(ans_, ans - 1ll * i * d);
    }
    printf("%lld\n", ans_);
}
int main() {
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}
```

---

## 作者：yangmingshuo114514 (赞：0)

## 题意

Kolya 要从 $n$ 天中选至多 $m$ 天看电影。每场电影都有其娱乐值 $a_i$。前一次观影距这一次观影过去了 $i$ 天，那么这一次观影的娱乐值就会少 $d\times i$。同时我们知道在这 $n$ 天的前一天 Kolya 看了一场电影。求娱乐值的最大值。

## 思路

两场电影之间的间隔是连续的，所以因前一次电影与这一次观影的距离所失去娱乐值的总和只与最后一次观影的日期有关。即最后一次观影是在第 $i$ 天，那么失去娱乐值总和就是 $d\times i$。

这时，我们只要求出原娱乐值总和减去失去娱乐值总和的最大值总和就可以了。

对于原娱乐值总和的最大值，贪心即可。我们选出前 $i$ 天中，前 $m$ 大（可以少于 $m$ 个）的正娱乐值（如果为负或者为 $0$ 就没有任何意义）。最后的答案就是 $sum-d\times i$。

分析一下数据结构，当 $n$ 达到 $2\times 10^5$ 时，就得用 $O(n\log n)$ 才过得了，每次枚举 $i$ 就得有 $O(n)$ 了，循环里面的就必须用 $O(\log n)$ 的求解方法了。

那该用什么数据结构来每次 $O(\log n)$ 解决这类“单点插入，前几大求和”的问题呢？我们好像并没有能直接解决这类问题的数据结构，不如变通一下思路，看看在各种情况下和的变化。

各种情况下和的变化如下：

1.当 $a_i\le 0$ 时，根据之前我们的判断，肯定是没有意义的，跳过。

2.当总个数不到 $m$ 个时，我们必然将其加入到总和中。

3.当总和达到 $m$ 个，且前 $m$ 大的最小值小于 $a_i$，把最小值替换成 $a_i$，修改总和。

4.当总和达到 $m$ 个，且前 $m$ 大的最小值大于等于 $a_i$，没有必要修改。

通过观察可知，以上只调用了前 $m$ 大数中的最小值，用堆解决即可。正好 C++ 中有一种东西叫 STL，其中就包含这种容器，即 priority_queue。

## 代码

代码照上面的分类讨论写即可。

```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#define int long long
using namespace std;
int t,n,m,d,a[200005];
long long sum,ans;
priority_queue<int,vector<int>,greater<int> >q;
signed main(){
	scanf("%lld",&t);
	while(t--){
		sum=ans=0;
		scanf("%lld%lld%lld",&n,&m,&d);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++){
			if(a[i]<=0) continue;
			if(q.size()<m)
				q.push(a[i]),sum+=a[i];
			else if(q.top()<a[i]){
				sum+=a[i]-q.top();
				q.pop();
				q.push(a[i]);
			}
			ans=max(ans,sum-d*i);
		}
		while(!q.empty()) q.pop();
		printf("%lld\n",ans);
	}
	return 0;
}

---

