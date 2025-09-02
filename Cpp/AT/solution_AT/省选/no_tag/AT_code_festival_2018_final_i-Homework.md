# Homework

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2018-final/tasks/code_festival_2018_final_i

高橋君は夏休みの宿題を片付けることにしました。

宿題は $ 1 $ から $ N $ までの番号がついた $ N $ 個の問題からなります。 問題 $ i $ は解くのに $ 2^{A_i} $ 秒かかり、$ B_i $ 点だけ得点が得られます。

高橋君は得られた得点の総和が $ K $ 以上になるように問題を解く必要があります。これを達成するために必要な時間の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{5} $
- $ 0\ \leq\ A_i\ \leq\ 30 $
- $ 1\ \leq\ B_i\ \leq\ 10^{9} $
- $ 1\ \leq\ K\ \leq\ Σ{B_i} $
- 与えられる入力は全て整数

### Sample Explanation 1

\- 問題 $ 2,3,5 $ を解くと、$ 7 $ 秒間で $ 24 $ 点が得られ、これが最適です。

### Sample Explanation 3

\- 答えが大きくなりうることに注意してください

## 样例 #1

### 输入

```
6 24
1 5
0 4
1 9
2 10
2 11
3 15```

### 输出

```
7```

## 样例 #2

### 输入

```
13 105
0 1
3 8
5 28
0 1
0 2
4 17
5 26
5 33
3 8
4 19
3 7
2 4
4 17```

### 输出

```
98```

## 样例 #3

### 输入

```
5 5000000000
30 1000000000
30 1000000000
30 1000000000
30 1000000000
30 1000000000```

### 输出

```
5368709120```

# 题解

## 作者：Conan15 (赞：7)

说句闲话：如果体积很小或者价值很小可以直接 DP。\
然后考虑按照 $a_i$ 进行“数位背包”。

记录 $dp_{u,i}$ 表示从高到低做背包，做到第 $u$ 位，有 $i$ 个 $1$（可以选 $i$ 个物品），能获得的最大价值。\
发现 $i \gt n$ 的状态是无用的，所以 $i \leftarrow \min(n, i)$。\
另外对于体积相同的物品，价值从大到小排序选一个前缀肯定不劣。

发现当体积递增的时候，价值也是单增的，所以考虑二分体积求价值。\
暴力枚举这一位选几个的复杂度是 $O(n^2 \log W)$ 的，套一个二分成了 $O(n^2 \log^2 W)$。\
赛时就只想到这里了 qwq，但这题虽然是紫题，但其实并不难想啊。

二分看上去不是很好整优化，而且复杂度主要瓶颈在于 DP，所以考虑优化这个过程。\
高位往低位貌似也不好优化了，所以从低位往高位做。\
发现 $2^k$ 的体积空间一定存不下 $2^{k+1}$ 体积的物品，所以形如这样的空间拿来装体积为 $2^k$ 的物品一定不劣。\
这种情况一定出现在体积的 $2^k$ 这一位是 $1$，那剩下的那些物品怎么办呢？\
显然，两两合并再扔到 $2^{k+1}$ 肯定是对的，因为接下来就不可能拆成一个计算答案了。\
如果合并后剩下一个呢？那就直接把它当作体积为 $2^{k+1}$ 扔到下一层。

复杂度分治套贪心 $O(n \log n)$，因为每一层 $n,\frac{n}{2},\frac{n}{4},\dots$ 加起来一定不超过 $2n$，所以复杂度**不是** $O(n \log^2 n)$。\
乘上外层二分 $O(\log W)$，总复杂度是 $O(n \log n \log W)$，已经可以通过。

可以通过归并排序变成贪心线性，总复杂度 $O(n \log W)$，太累了就不写代码了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 15, M = 65;
int n;
long long k;
vector<long long> v[M], a[M];

bool cmp(long long a, long long b) { return a > b; }

long long solve(int u, long long x) {
    if (!x) return 0;
    if (!a[u].size()) return solve(u + 1, x >> 1);
    
    sort(a[u].begin(), a[u].end(), cmp);
    long long add = 0;
    if (x & 1) add = a[u][0];
    else add = 0;

    // cout << '\t' << u << ' ' << add << endl;
    // for (int i : a[u]) cout << i << ' '; puts("");
    
    for (int i = (x & 1) ? 1 : 0; i < a[u].size(); i += 2) {
        if (i + 1 < a[u].size()) a[u + 1].push_back(a[u][i] + a[u][i + 1]);
        else a[u + 1].push_back(a[u][i]);
    }
    return solve(u + 1, x >> 1) + add;
}

int main() {
    scanf("%d%lld", &n, &k);
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int x; long long y;
        scanf("%d%lld", &x, &y);
        sum += (1 << x);
        v[x].push_back(y);
    }

    long long l = 0, r = sum;
    while (l < r) {
        long long mid = l + r >> 1;
        for (int i = 0; i <= 60; i++) a[i] = v[i];
        if (solve(0, mid) >= k) r = mid;
        else l = mid + 1;
    }
    printf("%lld\n", l);
    return 0;
}
```

---

## 作者：___Furina___ (赞：1)

~~模拟赛一直在想这道题怎么 dp，最后时间复杂度算假，怎么绘世呢？~~

### 题目简述：
无。

### 题解：
这里介绍一个贪心的思路。

我们假设答案为 $x$。

自然而然的，我们可以考虑按照 $a_i$ 从小到大考虑每个作业写还是不写。

因为用时是形如 $2^{a_i}$ 的形式，所以对于答案而言，如果这一位为 $1$，则代表这一位需要写一份作业，否则就不用。

考虑贪心，如果答案已经确定，那么这一位写的作业一定越大越好，正确性显然。

换而言之，就是如果这一位一定要写一份作业，一定会写这一位分数最大的作业。

那么考虑完这一位是否写作业后，这一位剩下的作业怎么办呢？

做法很简单，假设这一位写一份作业的耗时为 $2^x$，那么高一位写一份作业的耗时为 $2^{x+1}$，也就是高一位写一份作业的用时刚好是这一位写**两**份作业的时间。

于是考虑把这一位剩下的作业两两合并，传递到更高一位，然后转到高一位处理（代码注释 A），可以使用堆（优先队列）维护；注意若多余一个，则直接放入高一位（代码注释 B）。

最后考虑如何确定答案，注意到直接二分就可以了。

### 时间复杂度：
注意到把某一位作业数量传递到更高一位时，这一位作业数量会减半，所以传递作业总次数是 $O(n)$ 级别的，再算上堆（优先队列）和二分的复杂度，总时间复杂度为 $O(n\log^2n)$ 。

### 代码如下：
```cpp
/*Life is too long to end at a grave*/
#include<bits/stdc++.h>
#define N 100010
#define I_love_Furina return// Furina 这么可爱！
#define forever 0
#define foreverr 1
#define endl '\n'
#define FIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define db double
#define ull unsigned long long
#define chc cout<<114514<<endl
#define mid (l+r>>1)
#define int long long
using namespace std;
int n,T,m;
vector<int> g[62];
priority_queue<int> p[62];
inline bool check(int x){
	int ans=0;
	for(int i=0;i<=30;i++){
		for(int j:g[i])p[i].push(j);
	}
	for(int i=0;i<=60;i++){
		if((x>>i&1ll)&&!p[i].empty()){
			ans+=p[i].top();
			p[i].pop();
		}
		while(!p[i].empty()){
			int x=p[i].top();
			p[i].pop();
			if(p[i].empty()){p[i+1].push(x);continue;}//B
			int y=p[i].top();
			p[i].pop();
			p[i+1].push(x+y);//A
		}
	}
	I_love_Furina ans>=m;
}
signed main(){
	IOS;
	cin>>n>>m;
	for(int i=1,x,y;i<=n;i++)cin>>x>>y,g[x].push_back(y);
	int l=0,r=1e15;
	while(r-l>2){
		if(check(mid))r=mid;
		else l=mid;
	}
	if(check(l))cout<<l;
	else if(check(mid))cout<<mid;
	else cout<<r;
	I_love_Furina forever;
}

```

---

## 作者：qiucr (赞：1)

~~模拟赛被创飞了，遂来记录一下。~~\
首先这道题求的是总分数不小于 $k$ 需要的最短时间，我们发现这其实是一个背包问题，但是这道题做背包无论是空间复杂度还是时间复杂度都是不可以接受的，所以我们考虑别的做法\
既然我们要求最短时间，并且这道题的答案显然是具有单调性的，所以我们选择去二分这个时间。\
接下来是 $\operatorname{check}$ 的写法，因为所有物品的需要体积都是 $2^{a_{i}}$，所以肯定要想到对二分出的体积**拆位**，基于一个**贪心**的做法，我们发现对于体积二进制上每一位上的 $1$，我们选择若干个物品满足它们的体积之和的这一位上也是 $1$，且它们的价值是最大的，到这里我们就已经推出做法了。我们记录每一位所对于的物品集合的总体积，每次发现二分出的体积的这一位是 $1$，那么我们就加上最大贡献，然后我们再做一个**合并**，把现在这一位上的物品体积集合合并，存到下一位上，如果有单独的我们就直接把它放到下一位。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6+100,mod=1e9+7;
priority_queue<ll> d[51],s[51];
ll n,k;
bool check(ll x){
    for(int i=0;i<50;i++) s[i]=d[i];
    ll res=0;
    for(int i=0;i<50;i++){
        if(x>>i&1&&!s[i].empty()) res+=s[i].top(),s[i].pop();
        while(!s[i].empty()){
            ll a=0,b=0;
            if(!s[i].empty()) a=s[i].top(),s[i].pop();
            if(!s[i].empty()) b=s[i].top(),s[i].pop();
            s[i+1].push(a+b);
        }
    }
    return res>=k;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        d[a].push(b);
    }
    ll l=1,r=(1ll<<50)-1,res=0;
    while(l<=r){
        ll mid=l+r>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<res<<endl;
    return 0;
}

```

---

## 作者：__Floze3__ (赞：0)

## 思路

我们先来考虑一个更广为人知的问题：如果时间已经确定，那么能得到的分数的最大值是多少？这就是 [P3188](https://www.luogu.com.cn/problem/P3188)。但那道题的数据范围更小，这迫使我们研究这道题与 P3188 的不同之处：时间的值一定正好是 $2$ 的次方。这提醒我们要考虑从低位合并为高位的情况。我们不难想到一个从低位向高位贪心的方法：假设时间第 $i$ 位的二进制表示为 $1$，我们就选择要占用 $2 ^ i$ 时间的分数最大值（容易证明这样一定可以使得高分所需的时间最短）；无论这一位选不选，我们都要把剩下的需要 $2^i$ 时间的分数贪心的从大到小两两合并，组成需要 $2 ^ {i + 1}$ 时间的一组分数，如果最后还剩下一组分数，直接把它的时间视为 $2 ^ {i + 1}$ 即可，这样也显然是不劣的。那么我们只需要二分时间，即可求出所需的时间最小值。为什么这个具有单调性？因为更大的时间一定可以通过等价的调整（例如，转为从之后的位数得到同样甚至更多的分数）使得每一位实质上得到的分数都不降，正确性显然。设答案的上界为 $V$，如果预先排序，我们可以通过归并的方式做到 $O(n \log V)$，不过使用优先队列的 $O(n \log n \log V)$ 也可通过。

## 代码

[Submission #59506999 - CODE FESTIVAL 2018 Final](https://atcoder.jp/contests/code-festival-2018-final/submissions/59506999)

---

