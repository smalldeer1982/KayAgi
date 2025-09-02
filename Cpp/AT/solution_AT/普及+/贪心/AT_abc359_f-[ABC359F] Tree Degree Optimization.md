# [ABC359F] Tree Degree Optimization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc359/tasks/abc359_f

整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。 $ N $ 頂点の木 $ T $ に対して、 $ f(T) $ を以下で定めます。

- $ T $ の頂点 $ i $ の次数を $ d_i $ とする。このとき、$ f(T)=\sum_{i=1}^N\ {d_i}^2\ A_i $ とする。
 
$ f(T) $ として考えられる最小値を求めてください。

なお、制約下において答えが $ 2^{63} $ 未満となることは保証されています。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力される数値は全て整数
 
### Sample Explanation 1

頂点 $ 1 $ と頂点 $ 2 $ を結ぶ辺、頂点 $ 2 $ と頂点 $ 4 $ を結ぶ辺、頂点 $ 4 $ と頂点 $ 3 $ を結ぶ辺からなるような木 $ T $ を考えます。 このとき $ f(T)\ =\ 1^2\times\ 3\ +\ 2^2\times\ 2+1^2\times\ 5\ +2^2\times\ 2\ =\ 24 $ です。これが $ f(T) $ の最小値であることが証明できます。

## 样例 #1

### 输入

```
4
3 2 5 2```

### 输出

```
24```

## 样例 #2

### 输入

```
3
4 3 2```

### 输出

```
15```

## 样例 #3

### 输入

```
7
10 5 10 2 10 13 15```

### 输出

```
128```

# 题解

## 作者：Heldivis (赞：5)

# ABC359F

**大致思路：贪心。**

由于这是一颗树，所以点的度数 $d_i$ 需要满足 $1\le d_i \le n-1$ 且 $\sum d_i = 2(n-1)$。

先把每个点都给一个度数，还有 $n-2$ 个度数。

每次贪心，给一个增加一度后，增加最少的点。

对于一个度数已经为 $d$，点权为 $a$ 的点，增加量为 $a(d+1)^2 - ad^2=a(2d+1)$，所以可以开一个结构体，按照 $a(2d+1)$ 升序放在一个优先队列里，每次给堆顶的点增加一度，循环 $n-2$ 次。

最后累加堆里的每一个点的贡献即可。

代码：

```cpp
struct Node { int d, a; };
bool operator<(Node x, Node y) {return (x.d * 2 + 1) * x.a > (y.d * 2 + 1) * y.a;}
priority_queue<Node> q;
int main() {
  int n = read(); long long res = 0;
  for (int i = 1; i <= n; i++) q.push({1, read()});
  for (int t = 1; t <= n - 2; t++) {
    Node x = q.top();
    q.pop();
    x.d++;
    q.push(x);
  }
  while (q.size()) {
    res += q.top().d * q.top().d * q.top().a;
    q.pop();
  }
  printf("%lld\n", res);
  return 0;
}
```

---

## 作者：kkxacj (赞：2)

#### 思路

显然，重构只会有 $n-1$ 条边，所以入度总和只有 $2\times n-2$ 个。

首先化简一下式子，假设当前第 $i$ 个数入度为 $j$ 了，又多了一个入度，那么新增的贡献为 $a_i\times\left(2\times j+1\right) $。

由于每个点入度至少为 $1$，那么考虑先计算一次入度，这样每个点都一定会连，然后剩下的入度可以给任意的点，用优先队列实时维护最小值就行了。

**为什么一定可以呢**，发现由于对于每个点都有一个度数，还需要加 $n-2$ 个度数，对于第 $i$ 个点加一个度数可以理解为何其它点连边，假设 $n-2$ 个度数全加一个点上，一共只加 $n-2$ 个度数，但有 $n-1$ 个点可以与之连边，不全加在一个点上也一样，所以一定可行。

**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,a[300010],f[300010],l,l1,r1,r,v[300010],ans;
priority_queue<pair<int,int> >p,p1; 
int find(int x)
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
signed main()
{
	read(n);
	for(int i = 1;i <= n;i++) v[i] = 1,read(a[i]),ans+=a[i],p.push(make_pair(-a[i]*(2*v[i]+1),i)),v[i]++;
	for(int i = 1;i <= (n-1)*2-n;i++)
	{
		l = -p.top().first,r = p.top().second;
		p.pop();
		ans += l;
		p.push(make_pair(-a[r]*(2*v[r]+1),r));
		v[r]++; 
	}
	print(ans);
	flush();
	return 0;
}

```

---

## 作者：Guizy (赞：1)

感觉比 D 简单。

只要用一个小根堆，存每个点如果入度增加 $1$，对答案的贡献会增加的量。然后如果每次要加点，就把堆顶取出，答案加上贡献，再把改过的点和新加的点对答案的新贡献加入堆中，循环 $n$ 次即可。注意 $A_i$ 要先排序。

令 $d_i$ 为 $i$ 目前的度数，$i$ 的度数加 $1$，就会令答案增加：

$$a_i\times (d_i+1)^2-a_i\times d_i^2=a_i\times(2d_i+1)$$

```cpp
#include<bits/stdc++.h>
#define int long long 
#define pii pair<int,int>
using namespace std;

const int Max=200001;
int n,a[Max],b[Max],ans;//bi 表示 i 当前的度数
priority_queue<pii,vector<pii>,greater<pii> >q;
//STL 小根堆，first 存会增加的量，second 存编号。

signed main(){
	
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) 
		cin>>a[i],b[i]=1;
	
	sort(a+1,a+n+1);
	q.push(make_pair(a[1],1));
	
	for(int i=2;i<=n;i++){
		pair t=q.top(); q.pop();
		ans+=t.first+a[i];//ans 加上贡献
		q.push(make_pair(a[t.second]*(b[t.second]*2+1),t.second));
		q.push(make_pair(a[i]*(b[i]*2+1),i)); b[i]++,b[t.second]++;//更新
	}
	cout<<ans;
	
}
```

---

## 作者：_Weslie_ (赞：1)

双倍经验：P7840。

### Idea

定义一个长度为 $n-2$ 的序列叫 prufer 序列。

这个序列的求法是：

- 选择一个树上面的编号最小的叶子节点删除。
- 将这个节点所连的边的另一端的点加入到序列中。

显而易见的有一个结论：一个点的度数是它的编号在序列中的出现次数加 $1$。

为什么？因为这个点在序列中出现一次，就说明它和一个叶子节点有连边。

如果它最后被删除了，它当时一定只连一条边。这一条边不会让它加入序列，需要额外计算。

显而易见删完之后只会存在 $2$ 个点和 $1$ 条边。如果它最后被留下了，它一定是这条边两个端点之一。

上述结论现在已证毕。

通过这个性质，每个点至少连一条边，所以答案初始值必须是 $\sum a_i$。

接下来我们枚举给每个点的度数加 $1$。因为每加 $1$ 就需要消耗序列的一个位置，所以最多加 $n-2$ 次。

$d_i$ 为点 $i$ 的度数，如果度数加 $1$，则答案会加 $(d_i+1)^2-d_i^2$。

化简一下可以得到 $2\times d_i+1$。设这个值为 $w$。

可以看到当 $d_i$ 取正整数时，它是一个公差为 $2$ 的等差数列。初始当 $d_i=1$ 时，它的值为 $3$。

用一个优先队列维护 $w\times a_i$ 的值，每次取出这个值，都要把 $(w+2)\times a_i$ 加进去。即把度数再加 $1$ 产生的答案重新加入。

这是一个贪心。下面给出正确性证明：

如果我们选择了一个比较劣的答案，它所能到达的状态只会更劣。

即如果 $w\times a_j$ 劣，则 $(w+2)\times a_j$ 只会更劣。

所以这道题就解完了。

### Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<pair<int,int> >q;
int n;
int a[300005];
int ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)ans+=a[i];
	for(int i=1;i<=n;i++)q.push({-3*a[i],i});
	for(int i=1;i<=n-2;i++){
		pair<int,int >t=q.top();q.pop();
		ans-=t.first;
		q.push({(t.first-2*a[t.second]),t.second});
	}
	cout<<ans;
	return 0;
}
```

### Tips

- 本题答案可能爆 `int`。
- 优先队列默认是大根堆，但我们要求最小的。可以写小根堆，当然也可以把新增的答案当成负数算进去。
- 要维护 $i$ 的值，否则我们新算贡献可能不很好算。所以优先队列要用 pair 存储。
- pair 是自带排序的，先比较第一个再比较第二个，所以不用重载运算符。

---

## 作者：aeiouaoeiu (赞：1)

结论：对于一个满足 $\sum_{i=1}^{n}d_i=2n-2$ 且 $\forall 1\le i\le n,d_i>0$ 的长度为 $n$ 的序列 $d$，我们总能构造出一棵树 $T$ 使得 $T$ 中第 $i$ 个节点的度数为 $d_i$。

> 证明：构造一个序列 $t$，对于 $d_i$ 我们将 $d_i-1$ 个 $i$ 放到序列 $t$ 末端，则 $|t|=n-2$。构造一棵 Prufer 序列为 $t$ 的树 $T$，得证。

对于本题，考虑将 $d_i$ 自增 $1$ 转化为购买一个代价为 $((d_i+1)^2-d_i^2)a_i$ 的物品。那么我们最终要购买 $2n-2$ 个物品，由上面的结论，若能保证 $d_i>0$，我们进行最优购买后的 $d$ 序列一定能构造出一棵树。

我们首先给每个物品都买一次。然后，令当前物品的价格序列为 $v$，我们显然要贪心地取 $v$ 中最小的，取完后更新 $v$，循环往复直到取了 $2n-2$ 个物品。

上述过程可使用堆优化，时间复杂度：$\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
#define mkt make_tuple
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=400007,ee=1000000000000000007ll;
ll n,a[maxn],d[maxn],ans;
set<pair<ll,ll> > st;
signed main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	//ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]; ans+=a[i],d[i]=1;
		st.insert(mp(a[i]*3,i));
	}
	for(int i=n+1;i<=2*n-2;i++){
		//for(auto x:st) cout<<x.first<<" "<<x.second<<"\n"; cout<<"\n";
		auto it=st.begin(); ll id=it->second;
		ans+=it->first,d[id]++;
		st.erase(it),st.insert(mp(a[id]*(d[id]*2+1),id));
	}
	//for(int i=1;i<=n;i++) cout<<d[i]<<" "; cout<<"\n";
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：1)

### [AT_abc359_f [ABC359F] Tree Degree Optimization](https://www.luogu.com.cn/problem/AT_abc359_f)
对于任何一个度数合法的方案，它所对应的树一定是存在的，所以只需要考虑度数的分配即可。\
为了保证连通，每个点至少有一个度，答案先记上这一点。然后剩下 $n-2$ 个度要分配，考虑动态维护给每个点再加上一个度的贡献，贪心每次分配给贡献最小的即可。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10;
int n,a[N];
struct QQ
{
	int val,cnt,id;
	friend bool operator <(QQ a,QQ b){return a.val>b.val;} 
};
std::priority_queue<QQ> q;
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	n=read();int ans=0;
	for(int i=1;i<=n;++i){
		int x=read();
		ans+=x;
		q.push({x*3,1,x});
	}
	for(int i=1;i<=n-2;++i){
		auto it=q.top();q.pop();
		ans+=it.val;
		int x=it.cnt+1;
		q.push({it.id*(x*2+1),x,it.id});
	}
	std::cout<<ans<<'\n';
}
```

---

## 作者：qhr2023 (赞：0)

## 题意

给定 $A$ 序列。对于一棵有 $n$ 个顶点的树 $T$，定义 $f(T)$ 如下：设 $d_i$ 是 $i$ 的度数，则 $f(T)=\sum_{i=1}^n {d_i}^2 A_i$，求 $f(T)$ 的最小可能值。

## 思路

显然，每个点度数至少为 $1$。

所以先假设每个点都已经连好了，且每个点的度数都为 $1$。因为每个点的度数都得为 $1$，所以肯定是两两相连。

分类讨论一下。

当 $n$ 为偶数时，可以分成 $\frac{n}{2}$ 组，把他们连城一个树，需 $\frac{n}{2}-1$ 条边，每条边会使连接的两个点度数加 $1$，一条边会产生 $2$ 个贡献，所以会产生 $n-2$ 个贡献。

当 $n$ 是奇数时，分成 $\frac{n-1}{2}$ 组，同偶数时理，会产生 $n-3$ 个贡献，剩下的一个点随便连一个，这样会增加一个贡献，所以会产生 $n-2$ 个贡献。

综上：此题的答案为所有点的初始贡献之和加前 $n-2$ 小的度数的贡献。

## 实现

贪心和优先队列，前者输入时处理即可，后者用优先队列。

初始化 $d_i=1$，然后重复 $(N-2)$ 次，每次取出最小贡献的点后，产生的贡献为 $(d_i + 1)^2-{d_i}^2$，将 $d_i + 1$ 放回队中。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	long long d, v;
	bool operator<(const node &a) const {
		return (2*d+1)*v>(2*a.d+1)*a.v;
	}
};
long long n, ans, x;
priority_queue<node> q;
int main(){
	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> x,
		ans+=x,
		q.push({1, x});
	for(int i=1; i<n-1; i++){
		node u=q.top();
		q.pop();
		ans+=(2*u.d+1)*u.v;
		if(u.d<n-1)
			q.push({u.d+1, u.v});
	}
	cout << ans;
	return 0;
}
```

---

## 作者：roger_yrj (赞：0)

## 题意

有 $n$ 个点，每个点有点权 $a_i$，你需要把这些点连成一棵树，设 $d_i$ 表示点 $i$ 的度数，求 $\sum\limits^N_{i=1}d_i^2a_i$ 的最小值。

## 题解

首先我们要处理“树”这个条件。

我们不难发现，当 $d$ 满足以下性质是是合法的：

- $\sum\limits^N_{i=1}d_i=2(N-1)$
- $d_i>0$

所以说，每个点至少有 $1$ 的度数是固定的，剩下 $N-2$ 的度数给我们自由分配。

我们考虑贪心算法，每次给每个点试着增加一个度数，哪个点对答案的贡献最少就分配给哪个点。这一步可以用优先队列优化。

时间复杂度 $O(n\log n)$。

## 代码
```cpp
int n,m;
priority_queue<pair<ll,pii> >q;
ll ans,a[N];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];ans+=a[i];
		q.push(mp(-a[i]*3ll,mp(a[i],2ll)));
	}
	int p=n-2;
	while(p--){
		ll u=q.top().A;pii v=q.top().B;q.pop();
		ans-=u;
		if(v.A*((v.B+1ll)*(v.B+1ll)-v.B*v.B)>=((v.B+1ll)*(v.B+1ll)-v.B*v.B))q.push(mp(-v.A*((v.B+1ll)*(v.B+1ll)-v.B*v.B),mp(v.A,v.B+1)));
	}
	cout<< ans;
}
```

---

## 作者：incra (赞：0)

### Solution
观察题目，不难得到如下限制：

1. $\displaystyle\sum_{i=1}^nd_i=2\times (n-1)$，这是因为树有 $n-1$ 条边。
2. $d_i\ge 1$，这是因为图联通。

不难想到对于任意满足上述条件的 $d_i$ 一定能构造出一棵树。

考虑初始 $d_i=1$，然后再在里面选择 $n-2$ 个点（可以相同）的 $d_i$ 加 $1$。

考虑 $d_i$ 加 $1$ 对答案的贡献，显然是 $((d_i+1)^2-{d_i}^2)\times a_i=(2\times d_i + 1)\times a_i$，那么这里就可以用优先队列贪心的选择了。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << s << endl
const int N = 200010;
int n;
LL a[N];
using PLL = pair <LL,LL>;
priority_queue <PLL,vector <PLL>,greater <PLL> > heap;
int main () {
	cin >> n;
	LL ans = 0;
	for (int i = 1;i <= n;i++) cin >> a[i],ans += a[i],heap.push ({3 * a[i],3});
	for (int i = 1;i <= n - 2;i++) {
		PLL p = heap.top ();
		heap.pop ();
		ans += p.x;
		heap.push ({p.x / p.y * (p.y + 2),p.y + 2});
	}
	cout << ans << endl;
	return 0;
}
```

---

