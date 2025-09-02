# [ABC354C] AtCoder Magics

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc354/tasks/abc354_c

高橋くんは、カードゲーム「AtCoder Magics」のカードを $ N $ 枚持っています。$ i $ 番目のカードをカード $ i $ と呼ぶことにします。各カードには強さとコストのパラメーターがあり、カード $ i $ の強さは $ A_i $ で、コストは $ C_i $ です。

高橋くんは、弱いカードは要らないので捨てることにしました。具体的には、以下の操作をできなくなるまで繰り返します。

- $ 2 $ つのカード $ x,\ y $ であって、 $ A_x\ >\ A_y $ かつ $ C_x\ <\ C_y $ であるようなものを選ぶ。カード $ y $ を捨てる。

操作ができなくなったとき、捨てられなかったカードの集合は一意に定まることが証明できます。これを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ C_i\ \leq\ 10^9 $
- $ A_1,\ A_2,\ \dots\ ,A_N $ は全て異なる
- $ C_1,\ C_2,\ \dots\ ,C_N $ は全て異なる
- 入力はすべて整数

### Sample Explanation 1

カード $ 1,\ 3 $ に注目すると、 $ A_1\ <\ A_3 $ かつ $ C_1\ >\ C_3 $ なのでカード $ 1 $ を捨てることができます。 それ以上操作をすることはできません。このときカード $ 2,\ 3 $ が残っているので、これらを出力します。

### Sample Explanation 2

この場合、どのカードも捨てることができません。

## 样例 #1

### 输入

```
3
2 4
1 1
3 2```

### 输出

```
2
2 3```

## 样例 #2

### 输入

```
5
1 1
10 2
100 3
1000 4
10000 5```

### 输出

```
5
1 2 3 4 5```

## 样例 #3

### 输入

```
6
32 101
65 78
2 29
46 55
103 130
52 40```

### 输出

```
4
2 3 5 6```

# 题解

## 作者：hjyowl (赞：10)

# atcoder ABC354C题解

[原题链接 (atcoder)](https://atcoder.jp/contests/abc354/tasks/abc354_c)

### 题目概括：

给你很多卡，每个卡有一个强度和价格，每次选择两张卡片，如果一个卡片比另外一张强而且还有便宜一些，把另外一张卡片删除，求出最后剩下的卡片数量和集合，而且不存在相同的价格或者是一样强的卡牌。

### 暴力思路：

首先，可以想到 $O(n^2)$ 暴力，对于所有卡牌，直接枚举，如果发现出来一张比他强而且还比他便宜的卡，就删除，当然这样做肯定会超时。

### 前置算法：

排序。

### 正解思路：

我们可以按照他们的价格从小到大排序，然后我们扫一遍，如果遇到第 $i$ 张卡牌不是最大的，我们就删除他。

### 可行性分析：

很简单，如果他不是前 $i$ 个当中的最大的，那么他肯定会被删除（因为他前面的价格都比他小，而且如果他不是最大值，那就会有一个比他强的，而且比他便宜，所以第 $i$ 个数会被删除)。而且数据保证不会有相同价格的卡牌或者是相同强度的卡牌，所以不会出现前面某张卡牌的价格等于第 $i$ 张。

### 时间复杂度分析：

本来扫一遍只需要 $O(n)$，但是因为要排序，所以时间复杂度为 $O(n \log n)$ 。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 100010;
long long n;
struct owl{
	long long x,y,id;
}a[N];
bool cmp(owl a,owl b){
	return a.y < b.y;
}
int main(){
	cin >> n;
	set<int>st;
	for (long long i = 1; i <= n; i ++ ){
		cin >> a[i].x >> a[i].y;
		st.insert(i);
		a[i].id = i;//记录编号，不然排序后会乱
	}
	sort(a + 1,a + 1 + n,cmp);
	long long mx = -1e9;
	for (long long i = 1; i <= n; i ++ ){
		mx = max(mx,a[i].x);
		if (a[i].x != mx){
			st.erase(a[i].id);
		}
	}
	cout << st.size() << endl;
	set<int>::iterator it;
	for (it = st.begin(); it != st.end(); it ++ ){
		cout << *it << " ";
	}
	return 0;
}
```

---

## 作者：wo_hen_la (赞：2)

让你求哪些卡片成本**又便宜强度又高**，转化成求**又贵且强度低**的卡片个数，最后用卡片总数减去。

先按照卡片的**成本从小到大**排序，然后枚举卡片的**强度**，如果当前卡片的**强度**小于之前卡片的**强度最大值**，那么这张卡要被丢到。

看第二个样例，排完序后卡片强度是递增的，所以都会保留。第三个样例，排序后是

```2 52 46 65 32 103```

$46$ 比 $52$ 小，$32$ 比 $65$ 小，因此弃掉。


注意到 $A_1, A_2, \dots ,A_N$ 都是不同的，可以用 map 记录每个强度对应的下标。

```cpp
int ans[N];
struct node
{
	int q,c;//q表示题目中的A，c表示C
}a[N];
bool cmp(node x,node y){ return x.c<y.c; }
unordered_map<int,int> mp;

int main()
{
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].q>>a[i].c;
		mp[a[i].q]=i;//记录a[i].q对应的下标 
	}
	sort(a+1,a+1+n,cmp);//按照成本排序 
	int mx=a[1].q,cnt=0; 
	for(int i=2;i<=n;i++){
		if(a[i].q<mx) cnt++,ans[mp[a[i].q]]=1;//如果要弃掉，个数加 1，并把a[i].q对应的下标标记 
		mx=max(mx,a[i].q);//取最大值 
	}
	cout<<n-cnt<<"\n";//要求的是留下的 
	for(int i=1;i<=n;i++){
		if(!ans[i]) cout<<i<<' ';//留下的未被标记 
	}
	return 0;
}
```

---

## 作者：_xxxxx_ (赞：2)

### 题意

现在你有 $n$ 张卡牌，每张卡有价值 $A_i$ 和花费 $C_i$，定义第 $i$ 张牌为废牌当可以找到一个 $j$ 使得 $A_i<A_j$ 且 $C_i>C_j$。问把废牌丢掉后剩下的牌数及每张牌的编号。

### 分析

每张牌有两个属性，想从正面下手不太好做，先看看简单的。

1. 假如只有一种属性

只有一种属性，排序完取最优的一张牌即可。

2. $A_i$ 严格升序，$C_i$ 严格降序

取 $A_i$ 最大，$C_i$ 最小的一张牌就是最优。

回到问题，两种属性无序，尝试把牌排序，使得一种属性有序。这里我们使 $A_i$ 降序。

现在得到了一个 $A_i$ 降序，$C_i$ 无规律的序列。易发现：

1. 如果 $j>i$ 且 $C_i<C_j$，$A_i$ 一定比 $A_j$ 大，所以这张牌**是**废牌。

2. 如果 $j>i$ 且 $C_i=C_j$，$A_i$ 一定比 $A_j$ 大，但花费相等，这张牌**不是**废牌。

3. 如果 $j>i$ 且 $C_i<C_j$，这张牌的花费更小，这张牌**不是**废牌。

4. 后面的牌取与不取**不会**影响到前面的牌，前面的牌也**不会**影响到后面（无后效性）。

总结一下，将牌按价值降序排列，前面的牌价值大，只需要比较花费。同时存一下已经遍历完了的牌中的花费最小，后面的牌花费超出这个值，则它没有这张花费小的牌更优。

### 代码

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n;
struct node
{
	int a, c, id;
}p[N];
bool cmp(node a, node b)
{
	//按花费排 
	if(a.a == b.a) return a.c < b.c;
	return a.a > b.a;
}
int ans[N], cnt;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> p[i].a >> p[i].c;
		p[i].id = i;//记录编号，排完序会乱 
	}
	sort(p + 1, p + n + 1, cmp);
	int mt = p[1].c;
	//mt: 从1到i的花费最小值 
	ans[++cnt] = p[1].id;//价值最大的一定会拿 
	for(int i = 2; i <= n; i++)
	{
		if(p[i].c > mt) continue;//花费大了，是废牌 
		if(p[i].c == mt)
		{
			//花费相等，存下来 
			ans[++cnt] = p[i].id;
			continue;
		}
		//更新最小值 
		mt = min(mt, p[i].c);
		ans[++cnt] = p[i].id;
	}
	sort(ans + 1, ans + cnt + 1);//把编号再排一遍 
	cout << cnt << endl;
	for(int i = 1; i <= cnt; i++) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：XXh0919 (赞：2)

思路挺简单的。

### 翻译

给你两张牌 $x$ 和 $y$，每张牌有一个攻击力 $A$ 和消耗能量值 $C$（可以这么理解），要求 $A_x > A_y$ 并且 $C_x < C_y$，留 $x$，弃 $y$。重复执行上述操作。当无法进行该操作时，输出剩余牌数和剩下牌的编号。

### 解法

首先肯定是要保存编号的（毕竟要输出）。然后按照题目要求进行排序，按照攻击力从大到小进行排序，如果相等就按消耗能量值从小到大排序。排完序后就进行操作。若当前牌消耗能量的最小值比上次的最小值还小，那么就更新（不用管攻击力，因为本来就是按照它的大小排序的），如果该牌不符合题意，就直接弃牌（跳过）。在操作之后，记录下该牌的编号（该牌未弃）。

因为第一次排序是按照攻击力从大到小进行排序的，编号会被打乱，所以最后我们还要按照编号从小到大排回来输出。

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int N=3e6+15,inf=1e18;

struct node {
	int a,c;
	int id;
}t[N];
int n;
vector<int>anser;

inline bool cmp(node a,node b){
  return a.a>b.a||(a.a==b.a&&a.c<b.c);
}

void solve() {
	cin>>n;
	rep(i,1,n) {
		cin>>t[i].a>>t[i].c;
		t[i].id=i;
	}
	sort(t+1,t+n+1,cmp);
	int maxx=-inf,mcx=inf;//mcx 就是消耗能量的最小值
	int al=t[1].a,cl=t[1].c;
	rep(i,1,n) {
		if(t[i].c<mcx) {//消耗最少
			al=maxx,cl=mcx;
			maxx=t[i].a,mcx=t[i].c;
		}
		if(t[i].a<al&&t[i].c>cl||t[i].a<maxx&&t[i].c>mcx)continue;//不满足则跳过
		anser.push_back(t[i].id);
	}
	int k=anser.size();
	cout<<k<<endl;
	sort(anser.begin(),anser.end());
	for(auto i:anser) {
		cout<<i<<' ';
	}
	cout<<endl;
}

signed main() {
	ios::sync_with_stdio(0);
	int T=1;
	//cin>>T;
	while(T--)solve();
	return 0;
}
```

感谢用户 [littlebug](https://www.luogu.com.cn/user/541634) 的帮助！

---

## 作者：txl20 (赞：2)

蒟蒻第一篇题解。

## 题目大意

给定 $n$ 张卡牌，第 $i$ 张卡牌有强度 $a_i$ 和花费 $c_i$。

对于卡牌 $i, j$，如果 $a_i > a_j$ 且 $c_i < c_j$，卡牌 $j$ 将会被丢弃。

我们一直重复以上操作，问最后剩下的牌是哪些。

## 解题思路

我们可以先对数组按 $c$ 从小到大排序，依次考虑卡牌 $j$ 是否需要被。

发现因为我们是按照顺序枚举 $j$ 的，那么对于任何 $i < j$ 都有 $c_i < c_j$，这时候就只需要判断 $a_i > a_j$ 了。

我们可以维护一个前缀最大值 $\operatorname{max}_{1\le i\le j}(a_i)$，如果存在 $\operatorname{max}_a > a_j$，就说明了卡牌 $j$ 需要被丢弃，否则不用。

我们把不用丢弃的丢到一个数组里面，然后就可以输出了。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
vector<array<int, 2> > a;
vector<int> sv;
vector<int> ans;

bool cmp1(int i, int j){
	return a[i][1] < a[j][1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    a.resize(n), sv.resize(n);
    for (auto& x : a) cin >> x[0] >> x[1];
    
    iota(sv.begin(), sv.end(), 0);
    sort(sv.begin(), sv.end(), cmp1);
    
    int maxn = 0;
    for (auto x : sv) {
        if (a[x][0] < maxn) continue;
        ans.push_back(x);
        maxn = max(maxn, a[x][0]);
    }
    cout << ans.size() << '\n';
    
    sort(ans.begin(), ans.end());
    for (auto x : ans) {
        cout << x + 1 << " ";
    }
}
```

---

## 作者：Ivan422 (赞：2)

题目大意：给出 $n$ 张卡牌，每张卡牌强度为 $a_i$，成本为 $c_i$。当两张卡牌 $x$ 与 $y$ 满足 $a_x>a_y$ 且 $c_x<c_y$，扔掉牌 $y$。求最后剩余的卡牌数量以及编号。

思路：我们可以按照 $a_i$ 先排序，保证强度大的在前面。接着，我们可以对当前 $c_i$ 不断的取最小值，只要它是当前的最小值，那么后面一定有可以跟它扔掉的卡牌，这个组是固定的，于是我们考虑扔掉这个最小值。最后得出的答案就是正确的了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=998244353,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
struct card{int a,c,i;}a[N];
bool cmp(card x,card y){
    return x.a>y.a;
}
int n,cur,mn;
bool dl[N];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i].a>>a[i].c;a[i].i=i;}
    sort(a+1,a+n+1,cmp);
    mn=1e18;
    for(int i=1;i<=n;i++){
        if(mn<a[i].c){dl[a[i].i]=1;}
        mn=min(mn,a[i].c);
    }
    for(int i=1;i<=n;i++)if(!dl[i])cur++;
    cout<<cur<<endl;
    for(int i=1;i<=n;i++)if(!dl[i])cout<<i<<" ";
    return 0;
}
```

---

## 作者：stripe_python (赞：2)

建议标签：排序、模拟。建议难度：橙。

先把所有卡牌按 $a$ 排序。

接下来遍历一遍，判断 $i$ 卡牌是否会被删。如果 $i$ 前面有比 $c_i$ 小的 $c$，就会被删除。

在实现中，动态维护当前的 $\min c$ 即可。复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define N 200005
using namespace std;

int n;
struct node {
	int i, a, c;
} a[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].a >> a[i].c, a[i].i = i;
	sort(a + 1, a + n + 1, [](const node& a, const node& b) -> bool {
		return a.a > b.a;
	});
	vector<int> res;
	res.emplace_back(a[1].i);
	int minx = a[1].c;
	for (int i = 2; i <= n; i++) {
		if (a[i].c <= minx) res.emplace_back(a[i].i), minx = a[i].c;
	}
	sort(res.begin(), res.end());
	cout << res.size() << '\n';
	for (auto i : res) cout << i << ' ';
	return 0;
}
```

---

## 作者：hzxphy (赞：2)

## 题目大意
对于 $ 1\le x \le n$，若有 $y$ 满足 $A_x < A_y$ 并且 $C_x > C_y$ 那么删除这个牌。

求还剩下哪些牌。
## 思路
因为 $A_x < A_y$，而且只要其中 $A$ 数组比它大的之中有一个 $C_y<C_x$ 就行了。所以考虑排序。

从后往前扫，被遍历过的已经满足了 $A$ 数组的条件，处理 $C_x > C_y$。

我用了一个 set 容器来存储，每一次判断开头是否比 $C_x$ 小，如果没有，那么它就还存在。

随后将 $C_x$ 插入容器之中并重复以上操作。
## 样例推算
拿
```cpp
3
2 4
1 1
3 2
```

举例
| | $C_i$ | set 容器 |
| :----------: | :----------: | :----------: |
| $n=3$ | $3$ | $[]$ |
| $n=2$ | $1$ | $[3]$ |
| $n=1$ | $4$ | $[1,3]$ |

综上有 2 和 3 保留。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define A first
#define C second.first
#define id second.second
set<int>st;
set<int>ans;
int N;
pair<int,pair<int,int> > a[200010];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>N;
    for(int i=1;i<=N;i++)cin>>a[i].A>>a[i].C;
    for(int i=1;i<=N;i++)a[i].id=i;
    sort(a+1,a+1+N,less<pair<int,pair<int,int> > >());
    st.insert(1e9+1);
    for(int i=N;i>=1;i--){
//        cout<<a[i].C<<' '<<*st.begin()<<"***\n";
        if(a[i].C<*st.begin())ans.insert(a[i].id);
        st.insert(a[i].C);
    }
    cout<<ans.size()<<'\n';
    for(int i:ans)cout<<i<<' ';
    return 0;
}

```

---

## 作者：zhujiangyuan (赞：1)

[Problem](https://www.luogu.com.cn/problem/AT_abc354_c)

存一个结构体，包含强度 $x$、价值 $y$、编号 $id$。

按照强度 $x$ 从大到小排序，$x$ 相同按照价值 $y$ 从小到大排序。

按照 $1\sim n$ 循环 $i$，用 $minn$ 表示 $y_1\sim y_{i - 1}$ 中的最小价值，用 $mp_a$ 表示**第一次碰到 $a$ 时的 $minn$ 值**。

有 $2$ 种情况需要删去 $i$：
- $x_{i-1}>x_i$ 且 $y_i>minn$
- $x_{i-1}=x_i$ 且 $y_i>mp_{x_i}$

模拟即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int n, cnt, minn = 1e16;
bool flag[N];
struct T3 { int x, y, id; } a[N];
bool operator < (T3 a, T3 b) {
	return a.x > b.x || (a.x == b.x && a.y < b.y);
}
unordered_map <int, int> mp;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y, a[i].id = i;
	sort (a + 1, a + n + 1);
	cnt = n;
	for (int i = 1; i <= n; i++) {
		if (a[i - 1].x > a[i].x && a[i].y > minn) {
			flag[a[i].id] = 1, cnt--;
			continue;
		}
		if (a[i - 1].x == a[i].x && a[i].y > mp[a[i].x]) {
			flag[a[i].id] = 1, cnt--;
			continue;
		}
		if (a[i].x != a[i - 1].x) mp[a[i].x] = minn;
		minn = min (minn, a[i].y);
	}
	cout << cnt << '\n';
	for (int i = 1; i <= n; i++)
		if (!flag[i]) cout << i << ' ';
	return 0;
}
```

---

## 作者：CheZiHe929 (赞：1)

### 简要题意

高桥有 $n$ 张卡牌，其中第 $i$ 张卡牌的强度为 $a_i$，成本为 $c_i$。

高桥不喜欢弱牌，所以他会重复进行以下操作直至无法进行：

- 选择两张卡牌 $x,y$，如果 $a_x>a_y$ 且 $c_x<c_y$，高桥就会从牌堆中移除卡牌 $y$。

求最后剩余卡牌的数量并从小到大输出。

### 简要思路

将所有卡牌按照成本从小到大排序，并维护之前出现过的最大强度，如果当前卡牌的强度比最大强度小，则移除；反之则在剩余牌堆中（因为按照成本从小到大遍历）。

### 完整代码

```cpp
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

struct node{
	int a,c,num;
}m[MAXN];

int cnt,ans[MAXN];//最终牌堆情况 

bool cmp(node x,node y){
	return x.c<y.c;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	int n=read();
	for(int i=1;i<=n;i++){
		m[i].a=read();
		m[i].c=read();
		m[i].num=i;
	}
	
	std::sort(m+1,m+n+1,cmp);
	int maxn=-INT_MAX;
	for(int i=1;i<=n;i++){
		if(m[i].a>=maxn)
			ans[++cnt]=m[i].num;//加入牌堆 
		maxn=std::max(maxn,m[i].a);//更新最大强度 
	}
	
	std::sort(ans+1,ans+cnt+1);
	
	println(cnt);
	for(int i=1;i<=cnt;i++)
		put(ans[i],i,cnt);

	return 0;
}

```

---

## 作者：huangzhixia (赞：1)

第一眼，逆序对？写写写！结果挂惨了样例不过，然后觉得还是双关键字排序，但是升级板！

读入用结构体，此外还要多记一个变量 $id$ 来记录编号。

双关键字排序这题就是按照第一关键字，看 $a$，$a$ 哪个大哪个就整体大，相等的话看 $c$，$c$ 那个小那个就整体小。然后就是 ```sort``` 一遍，写个 ```cmp``` 即可。
                                                                  
遍历一遍，不仅是知道当前位置的信息，上一个位置的也要知道，这个和 $id$ 一样都是用来维护排序的稳定性的。每次将记录上一个位置的更新，然后判断一下，如果这张是弱卡，跳过不看，否则将强卡加入答案数组，最后排一遍序，输出即可。

这里可以证明，双关键字排序后只需要比较上一个即可，因为维护过了稳定性，不会出现下标混乱的情况。

上代码吧：
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 2e5 + 10;

struct Info {
	int a, c;
	int id;
}s[N];

inline bool cmp(Info &x, Info &y) {
	if (x.a == y.a)
		return x.c < y.c;
	return x.a > y.a;
}

int n, f1, pos1 = INT_MAX, f2, pos2 = INT_MAX, len;
vector<int> q;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &s[i].a, &s[i].c);
		s[i].id = i;
	}
	sort(s + 1, s + n + 1, cmp);
	f2 = s[1].a;
	pos2 = s[1].c;
	for (int i = 1; i <= n; i++) {
		if (s[i].c < pos1) {
			f2 = res1;
			pos2 = pos1;
			f1 = s[i].a;
			pos1 = s[i].c;
		}
		if (s[i].a < f2 && s[i].c > pos2 || s[i].a < f1 && s[i].c > pos1)
			continue;
		len += 1;
		q.push_back(s[i].id); 
	}
	printf("%d\n", len);
	sort(q.begin(), q.end());
	int l = q.size();
	for (int i = 0; i < l; i++)
		printf("%d ", q[i]); 
}
```

---

## 作者：Ryzen_9_7950X (赞：0)

赛时脑抽了，导致赛后1分钟才调出来。\
请大家食用正文：
# 思路
我们将排序前的第 $i$ 个元素的编号设置为 $i$，随后把每一张卡牌的力量值从小到大排序，\
然后用后缀和处理的方式找出 $i$ 到 $N$ 之间的最小代价值，其中 $1 \le i \le N$。\
然后比较排序后的第 $i$ 张卡牌的代价是否大于后面某一张卡牌的代价，如果是则丢弃，反之则留下。\
（特别地，排序后第 $N$ 张卡牌一定会被留下，因为没有卡牌比它更强大。）\
最后将留下的卡牌的编号从小到大输出。
# 示例
我们以样例 $3$ 为例：
```
6
32 101
65 78
2 29
46 55
103 130
52 40
```
将输入内容排序后，结果如下：
```cpp
2 29 //编号为3
32 101 //编号为1
46 55 //编号为4
52 40 //编号为6
65 78 //编号为2
103 130 //编号为5
```
此时的后缀和处理数组 $u$ 的结果如下：\
$[29,40,40,40,78,130]$\
第 $1$ 张卡牌的代价为 $29$，$u_2$ 的值为 $40$，$29 < 40$，所以留下第 $1$ 张牌，其编号为 $3$。\
第 $2$ 张卡牌的代价为 $101$，$u_3$ 的值为 $40$，$101 > 40$，所以丢弃第 $2$ 张牌，其编号为 $1$。\
第 $3$ 张卡牌的代价为 $55$，$u_4$ 的值为 $55$，$55 > 40$，所以丢弃第 $3$ 张牌，其编号为 $4$。\
第 $4$ 张卡牌的代价为 $40$，$u_5$ 的值为 $78$，$40 < 78$，所以留下第 $4$ 张牌，其编号为 $6$。\
第 $5$ 张卡牌的代价为 $78$，$u_6$ 的值为 $130$，$78 < 130$，所以留下第 $5$ 张牌，其编号为 $2$。\
由于没有比第 $6$ 张牌更强的牌了，所以留下第 $6$ 张牌，其编号为 $5$。\
处理完毕后，答案数组为：\
$[3,6,2,5]$\
排序之后为：\
$[2,3,5,6]$\
最后输出```2 3 5 6```。
# 代码
我们可以通过上述思路，得到下面的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node
{
    int ll,cost,bh;
};
bool cmp(node x,node y)
{
    return x.ll < y.ll;
}
node b[300005];
int hzh[300005];
signed main()
{
    int a;
    cin >> a;
    int ans = 0;
    for(int i = 0;i < a;i++)
    {
        cin >> b[i].ll >> b[i].cost;
        b[i].bh = i + 1;
    }
    sort(b,b + a,cmp);
    hzh[a] = 2147483647;
    for(int i = a - 1;i >= 0;i--) hzh[i] = min(hzh[i + 1],b[i].cost);
    vector<int> x;
    for(int i = 0;i < a - 1;i++)
    {
        if(b[i].cost >= hzh[i + 1]) continue;
        x.push_back(b[i].bh);
    }
    x.push_back(b[a - 1].bh);
    sort(x.begin(),x.end());
    cout << x.size() << endl;
    for(int i = 0;i < x.size();i++)
    {
        cout << x[i] << " ";
    }
    return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
我们可以先以 $c$ 为第一关键字从小到大排序，$a$ 为第二关键字从小到大排序，此时我们就只要删去 $a_i<a_j$ 且 $i<j$ 的元素即可，剩下的数下标从小到大排序输出就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
struct node {
	int x, y, id;
	bool operator < (const node& t) const {
		return y != t.y ? y < t.y : x < t.x;
	}
} a[200005];
int n, now;
vector <int> ans;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
		cin >> a[i].x >> a[i].y, a[i].id = i + 1;
	sort (a, a + n);
	for (int i = 0; i < n; ++ i)
		if (now <= a[i].x)
			ans.emplace_back (a[i].id), now = a[i].x;
	cout << ans.size () << '\n';
	sort (ans.begin (), ans.end ());
	for (int& i : ans)
		cout << i << ' ';
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

在一开始存储好每个元素的初始位置。然后我们先按照 $A_i$ 从大到小给输入的元素排个序。此时问题转化为对于一个元素，如果位置比它靠前的元素中有 $C_i$ 更小的，则删除该元素；否则保留该元素。

那么我们可以遍历一遍排好序的数组，每到一个位置，先判断当前元素的 $C_i$ 是否小于等于前面元素的 $C$ 最小值，是则把该元素的初始位置仍到答案数组里。然后再用该元素的 $C$ 更新最小值，并判断下一个元素。遍历完成后把答案数组从小到大排序后输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int a,c,k;
}a[1000005];
bool cmp(node a,node b){
	return a.a>b.a;
}
int f[1000005],top;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d %d",&a[i].a,&a[i].c),a[i].k=i;
	sort(a+1,a+1+n,cmp);
	int minn=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		if(a[i].c<=minn) f[++top]=a[i].k;
		minn=min(minn,a[i].c);
	}
	sort(f+1,f+1+top);
	printf("%d\n",top);
	for(int i=1;i<=top;i++) printf("%d ",f[i]);
	return 0;
}
```

---

## 作者：crz_qwq (赞：0)

## 思路
- 先对每个元素按 $A_i$ 排序。
- 再从后往前枚举，如果这个数后面没有 $C_i$ 比他小的则保留下来。
- 怎么知道是否有比这个数小呢？
- 可以先离散化，再用树状数组记录之前的每个 $C_i$ ，查询时查询 $1 \sim C_i -1$，若查询值大于 $0$，则舍弃此卡。
## 上代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n;
struct node{
	int v,c,i;
	bool operator<(const node&b)const{return v<b.v;}
}a[N];
int l[N],tr[N];
void add(int x,int d)
{
	for(int i=x;i<=200000;i+=i&-i)
		tr[i]+=d;
}
int sum(int x)
{
	int res=0;
	for(int i=x;i;i-=i&-i)
		res+=tr[i];
	return res;
} 
vector<int>ans;
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i].v>>a[i].c,a[i].i=i,l[i]=a[i].c;
	sort(l+1,l+n+1);
	for(int i=1;i<=n;++i)
		a[i].c=lower_bound(l+1,l+n+1,a[i].c)-l;
	sort(a+1,a+n+1);
	for(int i=n;i;--i)
	{
		if(sum(a[i].c-1)==0)
			ans.emplace_back(a[i].i);
		add(a[i].c,1);
	}
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(int i:ans)
		cout<<i<<' ';
}
```

---

## 作者：Redshift_Shine (赞：0)

# 3. [AtCoder Magics](https://atcoder.jp/contests/abc354/tasks/abc354_c) - 魔术

## 题意

给定 $n$ 个整数 $a_i,c_i$，在集合 $\{1,2,...,n\}$ 内删去所有存在整数 $x$ 满足 $a_x>a_y$ 且 $c_x<c_y$ 的整数 $y$，求无法再次进行删除的集合。

## 思路

将 $(a_i,c_i)$ 绑定为 `pair` 并进行升序排序，之后进行暴力删除即可。

## 代码

```c++
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
const int N = 2e5 + 10;
map<int, set<int>, greater<int>> mp;
set<int> res;
int n;
using pii = tuple<int, int, int>;
pii a[N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        auto &[x, y, z] = a[i];
        scanf("%d%d", &x, &y);
        z = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        while (mp.size() and mp.begin()->first > get<1>(a[i]))
        {
            mp.erase(mp.begin());
        }
        mp[get<1>(a[i])].insert(get<2>(a[i]));
    }
    for (auto &[k, v] : mp)
    {
        for (auto &j : v)
            res.insert(j);
    }
    printf("%d\n", res.size());
    for (auto &i : res)
        printf("%d ", i);
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
先将每张卡片按照强度排个序，然后从 $1 \sim n$ 遍历每一张卡片，我们用优先队列（小根堆）来维护当前最小的成本。

- 如果当前优先队列不为空，并且当前这张卡片的成本大于优先队列顶端的元素（也就是最小的成本），那么就可以弃掉这张卡片。
- 否则我们就把这张牌的编号（输入顺序）放进答案序列中，然后将这张卡片的成本加入进优先队列。

最后输出答案序列。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#define int long long
struct Node{
	int a,c,id;
}aa[200005];
bool cmp(Node a,Node b){
	return a.a>b.a;
}
std::priority_queue<int,std::vector<int>,std::greater<int>> q;
signed main(){
	int n;std::cin>>n;
	for(int i=1;i<=n;i++){
		std::cin>>aa[i].a>>aa[i].c;
		aa[i].id=i;
	}
	std::sort(aa+1,aa+1+n,cmp);
	std::vector<int>ans;
	for(int i=1;i<=n;i++){
		if(q.size()&&aa[i].c>q.top())continue;
		ans.push_back(aa[i].id);
		q.push(aa[i].c);
	}
	std::sort(ans.begin(),ans.end());
	std::cout<<ans.size()<<std::endl;
	for(int i=0;i<ans.size();i++){
		std::cout<<ans[i]<<" ";
	}
}
```

---

## 作者：Spark_King (赞：0)

# ABC354C 题解

## 题意理解

我们有 $N$ 张牌，每一张牌有自己的**强度** $A_i$ 和**代价** $C_i$，其中保证所有 $A_i$ 和 $C_i$ 互不相等。我们可以从中**任意选择**两张牌（下标分别为 $x$ 和 $y$），如果有 $A_x < A_y$ 且 $C_x > C_y$（即**强度低代价高**），则丢掉下标为 $x$ 的牌。**重复以上操作**，直到不能再进行为止。问最后还剩下哪些牌。

## 题目分析

根据题目要求，我们可以把每张牌的信息存储在结构体里，包含**强度**、**代价**以及**下标**。然后按照每张牌的**强度大小从小到大**进行排序。

此时，对于第 $i$ 张牌，它之后的牌的强度均**高于**它，所以只要判断是否**存在** $j > i$ 使得 $C_j < C_i$。如果存在，则可以将第 $i$ 张牌抛弃；反之，则该牌为**最后剩下**的牌之一。

这里我选用**后缀最小值**的方式判断 $C$ 的**存在性**。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct Card
{
	ll a,c,id;
}cd[200010];
bool cmp(Card x,Card y)
{
	return x.a<y.a;
}//排序方式
ll n;
ll minc[200010];//后缀最小值
ll cnt,ans[200010];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++)
	{
		cin>>cd[i].a>>cd[i].c;
		cd[i].id=i;
	}
	sort(cd+1,cd+1+n,cmp);
	minc[n]=1e18;//初始化
	for(ll i=n-1;i>=1;i--)
	{
		minc[i]=min(minc[i+1],cd[i+1].c);//处理最小值
	}
	for(ll i=1;i<=n;i++)
	{
		if(cd[i].c<minc[i])//符合条件 
		{
			cnt++;//计数并记录答案
			ans[cnt]=cd[i].id;
		}
	}
	cout<<cnt<<"\n";
	sort(ans+1,ans+1+cnt);//下标记得排序
	for(ll i=1;i<=cnt;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目简述

现有 $N$ 张牌，每张牌都有强度 $A$ 和成本 $C$。现对这 $N$ 张牌进行如下操作：

- 选择两张牌 $x,y$，使得 $A_x>A_y$ 且 $C_x<C_y$，丢掉牌 $y$。

求所有操作进行完后，剩下的牌的编号。

## 题目分析

当我们对所有的牌按照成本 $C$ 从小到大进行排序，并将成本相同的牌分在一个区后，只要我们当前分析到的牌之前的区域出现的强度最高的牌的强度比这张牌的强度高，这张牌就会被舍弃。维护一个区域之前的区域出现的最高强度也很简单，只需要从头到尾扫描每一张牌，然后用这张牌的强度去更新下一区域以前的最大强度就行了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=2e5;
int n,id[maxn+5],Max[maxn+5];
bool flag[maxn+5];
vector<int>ans;
struct node{
	int a,c,id;
}b[maxn+5];

bool cmp(node x,node y){
	return x.c<y.c;
}

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i].a>>b[i].c;
		b[i].id=i;
	}
	
	sort(b+1,b+n+1,cmp);
	int tot=1;
	for(int i=1;i<=n;i++){
		if(b[i].c!=b[i-1].c) id[i]=++tot;
		else id[i]=tot;
	}
	for(int i=1;i<=n;i++){
		Max[id[i]+1]=max(Max[id[i]+1],b[i].a);
		if(id[i+1]!=id[i]) Max[id[i+1]+1]=Max[id[i]+1];
	}
	for(int i=1;i<=n;i++) if(b[i].a<Max[id[i]]) flag[b[i].id]=true;
	
	for(int i=1;i<=n;i++) if(!flag[i]) ans.push_back(i);
	cout<<ans.size()<<endl;
	for(int i:ans) cout<<i<<' ';
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

## 作者：Albatross_LC (赞：0)

## 思路:

题目中要求我们要使剩下的卡牌中没有一张卡牌的实力比另一张卡牌小且价格又高。那么我们将原数组排序，实力值大且价格又低的放前面。

遍历时每次求出价格的最小值 $p$，若小于最小值或实力值不小于前一个数即可加入栈。

## Code:

```cpp
#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
struct PII {
	int x, y, id;
};
PII a[200001];
int n;
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i].x >> a[i].y, a[i].id = i;
	sort(a + 1, a + 1 + n, [](auto l, auto r) {
		if (l.x != r.x) return l.x > r.x;
		return l.y < r.y;
	});
	int m = 1, p = a[1].y;
	vector<int> o; o.push_back(a[1].id);
	for (int i = 2; i <= n; i ++ ) {
		if (a[i].y <= p || a[i].x == a[i - 1].x) m ++ , p = min(p, a[i].y), o.push_back(a[i].id);
	}
	cout << m << '\n';
	sort(o.begin(), o.end());
	for (auto i : o) cout << i << ' ';
}
```

---

## 作者：CEFqwq (赞：0)

我们会发现，直接暴力做是 $O(n^2)$ 的，肯定过不了。

但是如果我们能把比当前牌 $C$ 小的全找出来，比较 $A$，就可以很快了。

所以我们把 $C$ 排序，边扫边维护 $A$ 的最大值。

时间复杂度是排序的 $O(n \log n)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int id, aa, c;
}a[200005];
int n, ans[200005], cnt;
stack<int> s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		a[i].id = i;
		cin >> a[i].aa >> a[i].c;
	}
	sort (a + 1, a + 1 + n, [](node x, node y){return x.c > y.c;});
	int ma = 0;
	for (int i = n; i; i--)
		if (a[i].aa >= ma){//比前缀 A 的最大值还要大，保留
			ma = a[i].aa;
			s.push(a[i].id);//把原 id 放入栈（也可以是队列）中
		}
	cout << s.size() << "\n";//牌数
	while (!s.empty()){//这时牌的 id 是无序的，要再排序
		ans[++cnt] = s.top();
		s.pop();
	}
	sort(ans + 1, ans + cnt + 1);
	for (int i = 1; i <= cnt; i++)
		cout << ans[i] << " ";
}
```

---

## 作者：forever_nope (赞：0)

对于题目给出的性质，我们肯定是想要去证明的，

但是容易发现求解本题的过程本身就是一个构造性的证明。

注意到，牌力 $A_i$ 最大的一张牌，永远不会被 $A_x>A_i$ 选中而丢弃。

根据这个可以得出非常重要的一个性质，牌力最大的牌，一定会保留。

考虑到根据题目描述，最终得到的是怎样一个序列，

容易发现，我们将 $A_i$ 降序排列，则这个序列的 $C_i$ 应当也是递减的。

因为题目规定了 $A_i,C_i$ 两两不同，因此不需要考虑 $A_i$ 相同时的结果。

根据上述两条性质，我们可以给出确定性的构造：

从牌力 $A_i$ 最大的开始，依次 $A_i$ 递减，只有 $C_i$ 递减的才会保留。

容易发现，目前得到的这个序列是确定且唯一的。

考虑继续证明，在 $A_i$ 递减且 $C_i$ 也递减的序列中，每一张牌都会被保留。

其实只要读懂题了这个都很容易证明，这个只能算观察了，

因为在 $A_j>A_i$ 的中，所有的 $C_j>C_i$ 成立，因此 $i$ 一定不会被丢弃。

证毕，我们梳理一遍思路，

+ 将所有牌按照 $A_i$ 递减排序。
+ 考虑保留最大的 $A_i$ 的牌，然后枚举后面的每一张牌，
+ 如果加入这张牌，可以保持 $C_i$ 递减的性质，那么加入，
+ 否则，丢弃。

代码实现也不难，

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

template<typename tp>
istream& operator >>(istream &in, vector<tp> &a) {
    for (tp &t : a) in >> t;
    return in;
}

template<typename tp>
ostream& operator <<(ostream &out, vector<tp> &a) {
    for (auto i : a) out << i << " ";
    return out;
}

constexpr int N = 2e5 + 10;

int a[N], c[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n; vector<int> id(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> c[i], id[i] = i;
    sort(id.begin(), id.end(), [] (int i, int j) { return a[i] > a[j]; });
    int mx = 2e9; vector<int> ans;
    for (int i : id) if (c[i] < mx) mx = c[i], ans.push_back(i + 1);
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl << ans << endl;
    return 0;
}
```

---

