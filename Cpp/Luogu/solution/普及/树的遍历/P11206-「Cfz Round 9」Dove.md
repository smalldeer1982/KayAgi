# 「Cfz Round 9」Dove

## 题目描述

你的面前有一棵树。

这棵树共有 $n$ 个结点，这些结点之间由 $n-1$ 根树枝相连，每个结点上都有一只鸽子。

她希望你对所有鸽子进行编号。设第 $i$ 只鸽子的编号为 $p_i$，你需要满足：

- 序列 $p$ 为一个 $1 \sim n$ 的排列，即 $1\sim n$ 中的每个数在所有鸽子的编号中恰好出现一次；
- 对于结点 $u,v$，若结点 $u$ 与结点 $v$ 之间存在一根树枝，则结点 $u$ 上的鸽子的编号与结点 $v$ 上的鸽子的编号之和不大于 $n+1$，即 $p_u+p_v \le n+1$。

你想求出一种满足条件的对鸽子进行编号的方式。可以证明，一定存在至少一组解。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组测试数据，结点 $1$ 上的鸽子的编号为 $1$，结点 $2$ 上的鸽子的编号为 $3$，结点 $3$ 上的鸽子的编号为 $2$，由于 $1+2$ 和 $1+3$ 均不大于 $4$，所以这种对鸽子进行编号的方式满足条件。

对于第 $2$ 组测试数据，另一种满足条件的对鸽子进行编号的方式为：令结点 $1,2,3,4,5$ 上的鸽子的编号分别为 $2,1,4,5,3$。

#### 「数据范围」

对于所有测试数据，保证：

- $1 \le T \le 10$；
- $2 \le n \le 10^5$；
- $1 \le u_i,v_i \le n$；
- 输入数据形成一棵树。

**本题采用捆绑测试。**

- Subtask 0（21 points）：$n \le 8$。
- Subtask 1（25 points）：$n \le 1000$。
- Subtask 2（11 points）：对于任意小于 $n$ 的正整数 $i$，都满足 $u_i=1$ 且 $v_i=i+1$。
- Subtask 3（18 points）：对于任意小于 $n$ 的正整数 $i$，都满足 $u_i=i$ 且 $v_i=i+1$。
- Subtask 4（25 points）：无特殊限制。

## 样例 #1

### 输入

```
2
3
1 2
1 3
5
4 2
1 5
3 1
2 1```

### 输出

```
1 3 2
1 2 3 4 5```

# 题解

## 作者：normalpcer (赞：7)

## 题意简述

给定一棵树，希望给其上的所有点编号，使得所有边的两端端点编号之和均不超过 $N+1$。

## 分析

可以使用如下的贪心策略进行编号：

- 按照从深到浅的顺序排序所有点。
- 按照顺序，将一个点编上尽可能大的号码，同时，如果它的父节点没有被编号，则将其父节点编上尽可能小的号码。

接下来，我们对这个策略的正确性进行一个简要的证明。

使用数学归纳法。我们称在一个拥有 $N$ 个节点的子树上，使用 $\left[L, R\right]$ 区间中的整数进行编号为一次操作 $\operatorname{F}\left(N, L, R\right)$。这个操作的结果合法，当且仅当所有边两端端点的编号之和不超过 $L+R$。为了方便，我们称这个编号之和为这个边的“值”，并记点 $V$ 的编号为 $id_V$。接下来我们证明这个操作的结果合法。

对于 $N=1$ 和 $N=2$ 的情况，这种操作的结果必然合法。

假设 $N=k$ 和 $N=k-1$ 时，$\operatorname{F}\left(k, L, R\right)$ 的结果合法，不妨再令 $N=k+1$。在此时进行操作 $\operatorname{F}\left(k+1, L, R\right)$

![AQPCDBE](https://cdn.luogu.com.cn/upload/image_hosting/aukq73hf.png)

我们设要编号为 $R$ 的点为 $P$，它的父节点为 $Q$。不妨考虑将 $P, Q$ 两点去掉，此时原图会分裂成若干个子树（对于上图，三个子树为 $C$, $D$ 和 $ABE$）。将这三个子树以任意方式连接，则是一个包含 $k-1$ 节点的树。

![ACDBE](https://cdn.luogu.com.cn/upload/image_hosting/ar1k1zyd.png)

如图，我们把 $P, Q$ 去掉，并分别编上号码 $R$ 和 $L$，然后添上两条新的边（$AC, AD$），这样就是一棵树。对这棵树执行操作 $\operatorname{F}\left(k-1, L+1, R-1\right)$ 即可。那么，剩余的几条边和蓝边都能够保证它们的值不超过 $L+R$。

接下来，考虑这个过程中去掉的边（$QP, QC, QD$），对于 $QP$，它的值为 $L+R$，是合法的。对于 $Q$ 和它的一个子节点 $S$ 的连线，必然有 $L+1 \le id_S \le R-1$，这个边的值 $v = L + id_S \le L+R-1$，也是合法的。故此次操作的结果是合法的。

特别地，考虑 $Q$ 已经有编码的情况。事实上，这种情况更加简单，对于去掉点 $P$ 的子树，我们可以执行操作 $\operatorname{F}\left(k, L, R-1\right)$，那么所有边的值都能保证 $v \le L+R-1$，而新连的边值为 $L+R$，依旧合法。

故由数学归纳法，原命题成立。操作 $\operatorname{F}\left(N, 1, N\right)$ 的结果即为本题答案。

## 代码

这里不多加阐述，可以参考下方的代码和注释。

```cpp
/**
 * @link https://www.luogu.com.cn/problem/P11206
 */

#include <bits/stdc++.h>
#define upto(i,n) for(int i=1;i<=(n);i++)

int T;
namespace Solution {
    int N;
    const int _N = 1e5+5;

    int depth[_N];  // 到根节点（1）的距离

    std::vector<int> conn[_N];  // i 和 conn[i][j] 互相连接
    int parent[_N];  // 记录父亲节点
    int filling_queue_arr[_N];
    int filled[_N];
    std::queue<int> filling_queue;
    
    void init() {
        // 重设，防止多测数据互相污染
        std::memset(depth, 0, sizeof(depth));
        upto(i, _N)  conn[i].clear();
        std::memset(parent, 0, sizeof(parent));
        std::memset(filling_queue_arr, 0, sizeof(filling_queue_arr));
        std::memset(filled, 0, sizeof(filled));
        scanf("%d", &N);
        int x=0, y=0;
        upto(_, N-1) {
            scanf("%d%d", &x, &y);
            conn[x].push_back(y);
            conn[y].push_back(x);
        }
    }

    void dfs_depth(int p, int prev) {  // 计算深度
        parent[p] = prev;
        depth[p] = depth[prev] + 1;

        for (auto &dest: conn[p]) {
            if (dest == prev)  continue;
            dfs_depth(dest, p);
        }
    }

    bool check() {
        upto(i, N) {
            for (auto &dest: conn[i]) {
                if (filled[i] + filled[dest] > N+1) {
                    return false;
                }
            }
        }
        return true;
    }

    void solve() {
        init();
        dfs_depth(1, 0);  // 以 1 为根节点
        // 按照深度排序填充顺序
        upto(i, N)  filling_queue_arr[i] = i;
        std::sort(filling_queue_arr+1, filling_queue_arr+1+N, [](auto a, auto b) {
            return depth[a] > depth[b];
        });
        upto(i, N)  filling_queue.push(filling_queue_arr[i]);  // 压入队列

        int L=1, R=N;  // 区间最小值和最大值
        // 依次填充
        while (not filling_queue.empty()) {
            auto cur = filling_queue.front();  filling_queue.pop();
            if (filled[cur])  continue;  // 填过的就忽略
            // 尝试在该点填充一个最大的数
            filled[cur] = R; R--;
            // 在父节点填充一个最小的数
            if (parent[cur] != 0 /* 特判，根节点不做处理 */ && not filled[ parent[cur] ]) {
                filled[ parent[cur] ] = L; L++;
            }
        }

        // 全部填充完毕
        upto(i, N)  printf("%d ", filled[i]);
        assert(check());  // 结果正确
        printf("\n");
    }
}


int main() {
    scanf("%d", &T);
    while (T --> 0)
        Solution::solve();
    return 0;
}
```

这里的 `check()` 函数事实上是无用的，不过可以方便调试。

此外，还是要提醒一下，对于多测的题目，要注意完全清空所有可能用到的数组和容器。

---

## 作者：liyunhe (赞：7)

### 题目分析
跟据题意，输入的是一个图。由于输入数据形成一棵树，且只有 $n-1$ 条边，所以，肯定无向无环，可以用 dfs 来搜索。
由于限制，所以值为 $1$ 和 $n$ 的点之间应该有一条边。且值为 $n$ 的点只能与之相连。以此类推，尽量将大值放到度为 $1$ 的点上.在是将小值放到与它相邻的点上
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
vector<int> mp[N];//可变数组，用来储存图
int n,l,r,num[N];
inline void dfs(int u,int f){
	for(int v:mp[u]){//遍历u的边
		if(v==f) continue;
		dfs(v,u);//搜索下一个节点，因为无环，所以不会死循环
	}
	if(!num[u]){//没有子节点的优先赋最大值
		num[u]=r--;
		if(f&&!num[f]) num[f]=l++;//其相邻的赋一个小值
	}
}
inline void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) e[i].clear(),num[i]=0;
	for(int i=2;i<=n;i++){
		int u,v;cin>>u>>v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	l=1,r=n;
	dfs(1,0);
	for(int i=1;i<=n;i++) cout<<num[i]<<" ";
  cout<<endl;
}
signed main(){
	int T;cin>>T;
	while(T--)solve();
}
```

---

## 作者：fish_love_cat (赞：6)

笑点解析：单向建边差点似考场上。

---

有这样的贪心思路，先确定儿子节点的答案，然后对于每个点放尽可能大的值。

因为叶结点的值只影响自己的父亲，所以贪心的令叶子结点的值尽量大这样肯定不劣，然后因为叶节点确定，也就相当于确定了父节点的取值范围。此时叶节点的父节点就变成了新的叶节点，再重复上面的贪心即可成功构造。

那么我们递归求解即可。

但是因为要求最大值，暴力找单次最坏是 $O(n)$ 的，综合起来 $O(n^2)$，可能会挂。

不过有一个很典的用并查集处理的 trick，这样就能过了。

我觉得有绿吧。

---

代码：

并查集部分写的有点难评谔谔。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int>ve[100005];
int ans[100005],n;
int f[100005];
bool vis[100005];
int find(int x){return (x==f[x]?x:f[x]=find(f[x]));}
int dfs(int x){
	vis[x]=1;
    int maxx=n;
    for(int i=0;i<ve[x].size();i++){
    	if(vis[ve[x][i]])continue;
        maxx=min(n-dfs(ve[x][i])+1,maxx);
    }
    //cout<<"!"<<x<<':'<<maxx<<' '<<find(maxx);
    ans[x]=find(maxx);
    f[find(maxx)]=find(f[find(find(maxx)-1)]);
    find(f[maxx]);
    return ans[x];
}
signed main(){
    int t;
    cin>>t;
    while(t--){
        memset(ans,0,sizeof ans);
        memset(vis,0,sizeof vis);
        cin>>n;
        for(int i=1;i<=n;i++)
        ve[i].clear();
        for(int i=1;i<n;i++){
            int x,y;
            cin>>x>>y;
            ve[x].push_back(y);
            ve[y].push_back(x);
            f[i]=i;
        }
        f[n]=n;
        dfs(1);
        for(int i=1;i<=n;i++)
        cout<<ans[i]<<' ';
        cout<<endl;
        sort(ans+1,ans+1+n);
        for(int i=2;i<=n;i++)
        if(ans[i]==ans[i-1])while(1);
    }
    return 0;
}
```

---

## 作者：mysterys (赞：2)

发现目前的题解区还没有这种做法，于是特意来写篇题解。
# 思路
1. 不难发现度数大的节点应该放小的数，而度数小的节点应该放更大的数（证明可以参考别的题解和讲评）。
2. 所以我们不妨统计度数，从叶子节点开始放。具体实现是：跑一个拓扑排序，用 set 维护当前能放的最大数。

时间复杂度：$O(n \log n)$。
# Code 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#define ll long long
#define endl '\n'
const int N=1e5+5;
vector<int>g[N];
int d[N],ans[N];
int n;
set<int>s;
inline void topo(){
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(!d[i]) q.push(i);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		int maxx=0;
		for(int i:g[u]){
			if(!ans[i]) continue;
			maxx=max(ans[i],maxx);
		}
		int it=*s.lower_bound(n+1-maxx);
		ans[u]=it;s.erase(it);
		for(int v:g[u]){
			--d[v];
			if(d[v]==0) q.push(v);
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	cout<<endl;
}
inline void solve(){
	cin>>n;
	s.clear();
	for(int i=1;i<=n;i++) {
		g[i].clear();
		d[i]=-1;ans[i]=0;
		s.insert(i);
	}
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
		++d[u];++d[v];
	} 
	topo();
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

## 作者：NTT__int128 (赞：2)

# P11206 「Cfz Round 9」Dove题解
对于每个点按深度从大到小排序。贪心地把这些点中还没有填数的点填上最大的还没有填的数。如果这个点的父节点还没有填数，就把它的父节点填上最小的没填过的数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,p[N],f[N];
vector<int>v[N],cl;
struct node{
	int d,id;
	bool operator<(const node&_)const{return (d==_.d?id<_.id:d>_.d);}
}x[N];
void dfs(int cur,int fa){
	f[cur]=fa;
	x[cur].id=cur,x[cur].d=x[fa].d+1;
	for(int to:v[cur])if(to!=fa)dfs(to,cur);
}
void work(){
	cin>>n;
	for(int i=1;i<=n;i++)v[i]=cl;
	bool l=1,g=1;
	for(int i=1;i<n;i++){int x,y;cin>>x>>y,v[x].push_back(y),v[y].push_back(x),l&=(y==x-1||x==y-1),g&=(x==1||y==1);}
	if(l){
		for(int i=1,j=n,k=1;k<=n;i+=(k%2==0),j-=(k&1),k++)cout<<(k&1?j:i)<<' ';
		cout<<'\n';
		return;
	}
	if(g){
		for(int i=1;i<=n;i++)cout<<i<<' ';
		cout<<'\n';
		return;
	}
	for(int i=1;i<=n;i++)p[i]=0;
	dfs(1,0);
	sort(x+1,x+n+1);
	int cnt=0,up=n;
	for(int i=1;i<=n;i++){
		if(p[x[i].id])continue;
		p[x[i].id]=up--;
		if(p[f[x[i].id]]==0)p[f[x[i].id]]=++cnt;
	}
	for(int i=1;i<=n;i++)cout<<p[i]<<' ';
	cout<<'\n';
}
int main(){
	cin>>t;
	while(t--)work();
	return 0;
}
```

---

## 作者：ForgetOIDuck (赞：1)

### 闲话
第一次赛时过 T3，庆祝一下。

### 题目思路
先随便搞个根节点 $1$。

容易发现叶子节点度数只有 $1$，那么我们要把大的尽量往这里塞。这样能保证其他度数较多的点有较小的数可选。

然后选完这个叶子节点再往他的父亲塞一个**不超过题目限制范围的 没选过的 最大的数。** 

其实就是 dfs，每次遇到一个节点都把其子树都 dfs 选完，然后找和所有儿子节点满足和不超过 $N + 1$ 的最大没被选过的。

~~这么贪心应该是对的，感性理解一下。~~

找这个数我赛时用的是树状数组 $+$ 二分 ~~，似乎是个脑抽做法~~。时间复杂度 $O(T\cdot N\log^2N)$，高达 $10^8$ 量级。不过最慢 $985 ms$，拜谢洛谷神评测机。

### AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, T, e[200002], h[200002], ne[200002], bh[200002], tr[200002], idx, l;
bool ff[200002];
ll lowbit(ll x) {
	return x & (-x);
}
void update(ll x) {
	while (x <= n) tr[x] ++, x += lowbit(x);
}
ll query(ll x) {
	ll res = 0;
	while (x) res += tr[x], x -= lowbit(x);
	return res;
}
void add(ll x, ll y) {
	e[idx] = y, ne[idx]= h[x], h[x] = idx ++;
}
void dfs(ll x) {
	ff[x] = 1;
	bool az = 1;
	ll minn = 0x3f3f3f3f3f3f3f3f;
	for (ll i = h[x]; i; i = ne[i]) {
		ll y = e[i];
		if (ff[y]) continue;
		az = 0;
		dfs(y);
		minn = min(minn, n + 1 - bh[y]);
	}
	ll l = 1, le = (az ? n : minn), r = le, ans;
	while (l <= r) {
		ll mid = l + r >> 1;
		if (query(le) - query(mid - 1) >= le - mid + 1) r = mid - 1;
		else ans = mid, l = mid + 1;
	}
	bh[x] = ans;
	update(ans);
}
int main() {
	cin >> T;
	while (T -- ) {
		cin >> n;
		idx = 1;
		for (ll i = 1; i <= n; i ++ ) tr[i] = ff[i] = bh[i] = h[i] = tr[i] = 0;
		for (ll i = 1; i <= 2 * n; i ++ ) e[i] = ne[i] = 0;		
		for (ll x, y,  i = 1; i < n; i ++ ) cin >> x >> y, add(x, y), add(y, x);
		l = n;
		dfs(1);
		for (ll i = 1; i <= n; i ++ ) cout << bh[i] << (i == n ? '\n' : ' '); 
	}
}
```

---

## 作者：枫之都 (赞：1)

[P11206 题目链接](https://www.luogu.com.cn/problem/P11206)

由题意可知，给出一个树，随便找一个节点当根节点就行，比如节点 $1$。

## 题目含义

对树中 $ 1 \sim n $ 的节点每一个节点给一个 $ 1 \sim n $ 的编号，使得每一条边的两个端点编号之和不大于 $ n + 1 $。

## 题目分析

很容易想到，编号为 $ n $ 的节点只能有一条边，连接编号为 $ 1 $ 的节点，从而可以想到，我们应该让编号较大的节点和编号较小的节点间隔排列。
#### ~~错误想法~~

有些人~~比如我~~最初可能会考虑把节点分成奇偶层，把数分成两组**较大的数**和**较小的数**，一层大一层小，但是这样会 **WA** 掉一片，大概只能拿 $29$ 分。

### 正确想法

我们考虑这样一个问题，什么样的边是符合要求的？

很显然，两个**较小的数**组成的边符合要求，一个**较大的数**和一个**较小的数**组成的边**可能**符合要求，两个**较大的数**组成的边一定不符合要求。

那么，一个**较大的**编号和一个**较小的**编号相连，什么时候**这两个编号的和**会**小于等于** $ n + 1$？

很显然，只有**已经分配出去的较小的数的个数**(比如 $ k1 $ )**小于等于较大的数的个数**(比如 $ k2 $ )时成立,很显然，现在能分配的较小的数为 $k1+1$，较大的数为 $n-k2$。

或者说，只有 $ k1 \leq k2$ 时，才有：
$$
(k1+1)+(n-k2)=n+1+(k1-k2)\leq n+1
$$
而上面的错误想法，很容易考虑到在当前层是**较小的数**的情况下，很容易会发生 $k1 > k2$ 的情况，故不成立。

那么什么情况下能保证 $ k1 \leq k2$ 呢，很显然，我们可以考虑到，一对父子关系中，**父节点的个数($1$)一定小于等于子节点的个数**。

也就是说，我们把较大的数流放到离根节点最远的叶子结点，然后给这些被发配的节点的父节点上盖住一层较小的数。

由以上条件可知，这时候一定有 $ k1 \leq k2$，这些父节点的父节点(称作祖父节点)就算是分配剩下的数里最大的数，也会与父节点构成一条合法的边，这样已经分配出去的叶子结点及其父节点就已经~~我滴任务完成辣~~。

**对于剩下的节点我们重复以上操作，直至整个树都完成编号。**

$Q.E.D.$

当然，在实际编程中，我们只需要一个 **dfs** 就可以解决。

[**Uncommented code**](https://www.luogu.com.cn/record/183609589)

### 有注释的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=int32_t;
class P11206
{
public:
    class _MyIn///一个快读
    {
    public:
        using _I=ll;
        static constexpr bool sign=1;
        //#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,BZ,stdin),p1==p2)?EOF:*p1++)
        ///卡常时开fread
        #ifdef getchar
        static constexpr int BZ=1<<20;
        char buf[BZ],*p1=buf,*p2=buf;
        #endif
        _I operator()()///单例仿函数
        {
            _I n=0;
            bool b=0;
            char c=getchar();
            while(c<48||c>57)((sign&&c=='-')?b=1:0),c=getchar();
            while(c>=48&&c<=57)
                n=(n<<1)+(n<<3)+(c^48),c=getchar();
            return b?-n:n;
        }
        _MyIn& operator>>(_I &n){return n=operator()(),(*this);}///习惯用cin的可以这么写
        #undef getchar
    }read;//O.o
    static constexpr int N=1e5+9;
    ll n,t;
    array<vector<int>,N> T;///存储树
    array<int,N> ans;///存储答案
    array<int,2> m;///m[0]表示当前能分配的较小数，m[1]表示较大数(就是k1+1和n-k2)
    int dfs(int r,int f)///当前节点及其父节点
    {
        for(int i=0;i<T[r].size();++i)///遍历所有子节点
        {
            if(T[r][i]==f)continue;
            dfs(T[r][i],r);
        }
        if(!ans[r])///如果当前节点没有被当做父节点赋值
        {
            ans[r]=m[1]--;///分配一个较大的数
            if(!ans[f]&&f)ans[f]=m[0]++;///如果父节点没有数，且父节点存在，给父节点分配一个较小的数
        }
        return 0;
    }
    P11206()///主程序在这
    {
        t=read();
        while(t--)
        {
            T.fill(vector<int>());///初始化
            ans.fill(0);
            n=read();
            for(int i=1,u,v;i<n;++i)
            {
                read>>u>>v;
                T[u].push_back(v);
                T[v].push_back(u);
            }
            m[0]=1,m[1]=n;///把最大最小的数初始化为n和1
            dfs(1,0);///随便找一个点作为根节点，根节点没有父节点
            for(int i=1;i<=n;++i)
            {
                cout<<ans[i]<<' ';
            }
            cout<<endl;
        }
    }
    ~P11206()
    {
        ;
    }
}obj;
int main()
{
    return 0;
}
```

---

## 作者：Graph (赞：1)

明天就 CSP 了，RP++。

----

考虑贪心。

我们最优是把小的和大的匹配，这样能使数值尽量平均。

一个节点的标号为 $n$，当且仅当那个节点是度数为 $1$ 的节点，**接下来必定把与它连接的那个点标为 $1$**。

考虑把度数丢到优先队列里面，每次取出度数最小的节点，把它标为目前剩余的编号的最大值，然后把它所有未标号的邻接点标为最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 

const int N=1e5+5;
class Node
{
public:
	int val,x;
	bool operator<(const Node& tmp)const
	{
		return val>tmp.val;
	}
};
int n,ans[N];
vector<int>nbr[N];
priority_queue<Node>pq;

void Work()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		nbr[i].clear(),ans[i]=-1;
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		cin>>x>>y;
		nbr[x].push_back(y);
		nbr[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		pq.push({nbr[i].size(),i});
	int q=1,h=n;
	while(pq.empty()==false)
	{
		int cur=pq.top().x;
		pq.pop();
		if(ans[cur]!=-1)
			continue;
		ans[cur]=h--;
		for(int nxt:nbr[cur])
			if(ans[nxt]==-1)
				ans[nxt]=q++;
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	cout<<"\n";
	return ;
}

signed main()
{
	int T;
	cin>>T;
	while(T--)
		Work();
	return 0;
}
```

嗯？$82$ 分？

认真想一想，实际上会链卡掉。

为什么？

因为我们从链的两端标为最大，同时向中间标号，那么中间的标号过大不就 GG 了？

特判！居然过了。

其实只有这种情况可能不行。

因为如果有 $3$ 个度数为 $1$ 的节点向中间扩展，合在一起时中间两点的和是偏小的。

$3$ 个以上度数为 $1$ 的点也同理。

那么只有 $2$ 个度数为 $1$ 的点会被卡。

只有 $2$ 个度数为 $1$ 的点？那不是一条链吗？

于是数据分治一下就可以了。

赛时 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 

const int N=1e5+5;
class Node
{
public:
	int val,x;
	bool operator<(const Node& tmp)const
	{
		return val>tmp.val;
	}
};
int n,ans[N],top;
vector<int>nbr[N];
priority_queue<Node>pq;
int lq,rq;

void dfs(int cur,int fa,bool flag)
{
	if(flag==false)
		ans[cur]=rq--;
	else
		ans[cur]=lq++;
	for(int nxt:nbr[cur])
	{
		if(nxt==fa)
			continue;
		dfs(nxt,cur,!flag);
	}
	return ;
}

void lian()
{
	lq=1,rq=n;
	dfs(top,0,0);
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	cout<<"\n";
	return ;
}

void Work()
{
	cin>>n;
	while(pq.empty()==false)
		pq.pop();
	for(int i=1;i<=n;i++)
		nbr[i].clear(),ans[i]=-1;
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		cin>>x>>y;
		nbr[x].push_back(y);
		nbr[y].push_back(x);
	}
	bool flag=false;
	int k=0;
	top=-1;
	for(int i=1;i<=n;i++)
	{
		pq.push({nbr[i].size(),i});
		if(nbr[i].size()>2)
			flag=true;
		if(nbr[i].size()==1)
			k++,top=i;
	}
	if(flag==false&&k==2)
	{
		lian();
		return ;
	}
	int q=1,h=n;
	while(pq.empty()==false)
	{
		int cur=pq.top().x;
		pq.pop();
		if(ans[cur]!=-1)
			continue;
		ans[cur]=h--;
		for(int nxt:nbr[cur])
			if(ans[nxt]==-1)
				ans[nxt]=q++;
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	cout<<"\n";
	return ;
}

signed main()
{
	int T;
	cin>>T;
	while(T--)
		Work();
	return 0;
}
```

马蜂丑陋。

---

## 作者：篮网总冠军 (赞：1)

一道纯贪心+二分的题目。

首先，我们可以得出，树枝越多的点，鸽子的编号应该越小。

然后，鸽子的编号不能重复。

所以，我们先给点排个序，再枚举这个点最大能选的数值，最后二分得出第一个**未选的**小于最大能选数值的数，再把这个数删除即可。

P.S. 对于一条链，建议特殊处理，否则会有不可预见的后果。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int>a[100005];
int d[100005];
int s[100005];
bool vis[100005];
struct pair1{
	int x,d;
	friend bool operator<(pair1 t1,pair1 t2){
		return t1.d>t2.d; 
	}
};
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		vector<int>q1;
		memset(vis,0,sizeof(vis));
		memset(d,0,sizeof(d));
		memset(s,0,sizeof(s));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) a[i].clear();
		bool f=1;
		for(int i=1;i<=n;i++) q1.push_back(i); 
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			if (v-u!=1) f=0;
			a[u].push_back(v);
			a[v].push_back(u);
			d[u]++;
			d[v]++;
		}
		if (f){
			int u1=n,u2=1;
			if (n%2==0){
				for(int i=1;i<=n;i+=2){
					s[i]=u1,s[i+1]=u2;
					u1--;
					u2++;
				}
			}
			else{
				s[n]=n/2+1;
				for(int i=1;i<=n-1;i+=2){
					s[i]=u1,s[i+1]=u2;
					u1--;
					u2++;
				}
			}
			for(int i=1;i<=n;i++) cout<<s[i]<<" ";
			cout<<endl;
			continue;
		}
		priority_queue<pair1>q;
		for(int i=1;i<=n;i++){
			pair1 y;
			y.x=i,y.d=d[i];
			q.push(y);
		}
		while(!q.empty()){
			pair1 op=q.top();
			q.pop();
			int maxp=0;
			for(int i=0;i<a[op.x].size();i++){
				maxp=max(maxp,s[a[op.x][i]]);
			}
			int v=n+1-maxp;
			if (v==n+1) v=n;
			int y;
			if(v>=q1[q1.size()-1]) y=q1.size()-1;
			else {
				int l=0,r=q1.size()-1;
				while(l<r){
					int mid=(l+r+1)/2;
					if (q1[mid]<=v) l=mid;
					else r=mid-1; 
				}
				y=l;
			}
			s[op.x]=q1[y];
			q1.erase(q1.begin()+y);
		}
		for(int i=1;i<=n;i++) cout<<s[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# Problem
构造权值为 $n$ 的排列的一棵树，使得任意两个相邻的节点权值和 $\le n+1$。
# Solution
我们可以从下往上填节点，每个节点都在儿子的后面被填到。  
我们贪心地想，每一个节点都尽可能赋满足不与所有儿子冲突的最大的权值，可以证明这么做是不劣的。  
我们可以用 set 来维护剩下的权值，每次取出对应的权值即可。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5;
int t,n,ans[N+5];
vector<int>g[N+5];
set<int>s;
void dfs(int u,int f){
	int maxn=0;
	for(int v:g[u])if(v!=f){
		dfs(v,u);
		maxn=max(maxn,ans[v]);
	}
	auto it=prev(s.upper_bound(n+1-maxn));
	ans[u]=*it;
	s.erase(it);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			g[u].push_back(v),g[v].push_back(u);
		}
		for(int i=1;i<=n;i++)s.insert(i);
		dfs(1,0);
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		cout<<'\n';
		for(int i=1;i<=n;i++)g[i].clear();
	}
}
```

---

## 作者：ELECTRODE_kaf (赞：0)

必然会给一个点赋权值为 $n$，那与这个点相邻的点就只能有一个，且它的权值为 $1$。因此这个点只能是叶子节点。随后 $n-2$ 与 $2$ 相邻，$n-3$ 与 $3$ 相邻，以此类推。

这样我们可以推出一种贪心策略：优先把大数赋给深度大的点，把小数赋给它的父亲。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,x,y) for(ll i=x;i<=y;i++)
#define pause system("pause")

const ll N=1e5+10;
ll q,n,rk[N];
vector<ll> a[N];

struct node {
	ll dep,fa,ans,no;
	bool vis;
} mp[N];

bool cmp(node x,node y) {
	return x.dep>y.dep;
}

void dfs(ll p,ll fa) {
	mp[p].dep=mp[fa].dep+1;
	mp[p].fa=fa;
	mp[p].no=p;
	mp[p].vis=0;

	for(ll i:a[p]) {
		if(i==fa) continue;

		dfs(i,p);
	}
}

int main() {
	cin>>q;

	while(q--) {
		cin>>n;

		rep(i,1,n) a[i].clear();

		rep(i,1,n-1) {
			ll u,v;
			cin>>u>>v;
			a[u].push_back(v);
			a[v].push_back(u);
		}

		dfs(1,0);

		sort(mp+1,mp+n+1,cmp);

		rep(i,1,n) rk[mp[i].no]=i;

//		rep(i,1,n) cout<<rk[i]<<' ';

//		cout<<'\n';
		ll l=1,r=n;

		rep(i,1,n) {
			if(mp[i].vis) continue;

//			cout<<"l="<<l<<" r="<<r<<'\n';
			mp[i].ans=r--;
			
			if(mp[rk[mp[i].fa]].vis==0) mp[rk[mp[i].fa]].ans=l++;
			
			mp[i].vis=mp[rk[mp[i].fa]].vis=1;
		}

		rep(i,1,n) cout<<mp[rk[i]].ans<<' ';

		cout<<'\n';
	}
}
/*
1
5
4 2
1 5
3 1
2 1
*/
```

---

## 作者：GCSG01 (赞：0)

## P11206 Dove
贪心，从 $n$ 开始想，发现 $n$ 只能在叶子节点，且父亲节点必须为 $1$。于是我们可以大胆的猜想，每次对最深的点赋值为目前未被使用的最大数字，如果它的父亲节点没有被赋值，就赋值为当前未被使用的最小数字。具体的证明可以看[这篇帖子](https://www.luogu.com.cn/discuss/966217) 。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
vector<int>a[N];
int dep[N];
int ans[N];
int f[N];
int fa[N];
int b[N];
int n;
bool cmp(int a,int b)
{return dep[a]>dep[b];}
void dfs(int x,int ffa)
{
	dep[x]=dep[ffa]+1;
	fa[x]=ffa;
	for(int i=0;i<a[x].size();i++)
		if(a[x][i]!=ffa)dfs(a[x][i],x);
	return ;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			a[i].clear(),b[i]=i;
		memset(f,0,sizeof(f));
		memset(ans,0,sizeof(ans));
		
		for(int i=1,u,v;i<n;i++)
			cin>>u>>v,a[u].push_back(v),a[v].push_back(u);
		dfs(1,0);
		sort(b+1,b+n+1,cmp);
		int minn=1,maxx=n;
		for(int i=1;i<=n;i++)
		{
			int now=b[i];
			if(f[b[i]])continue;
			ans[b[i]]=maxx;
			maxx--;
			f[b[i]]=1;
			if(!f[fa[b[i]]])f[fa[b[i]]]=1,ans[fa[b[i]]]=minn,minn++;
		}
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

对树进行 dfs。过程中，先搜索子树，然后对于一个节点，统计儿子编号的最大值，用 $n+1$ 去减，得到当前节点必须小于等于某个数，这时候在范围内找最大的没选过的数即可，然后把选择的数标记，这可以并查集实现，复杂度 $O(n\log n)$。

证明的话考虑每次就等价于选取一个儿子为叶子的子树，给叶子最大，给自己小，其它节点取值范围发现等价于把这个子树去掉后的情况然后就证完了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct st{
	int v,ne;
}sd[1000009];
int inn;
int h[1000009];
void add(int u,int v){
	sd[++inn].v=v;
	sd[inn].ne=h[u];
	h[u]=inn;
}
int fa[1000009];
int getfa(int t){
	if(t==fa[t]){
		return t;
	}
	return fa[t]=getfa(fa[t]);
}
int p[1000009];int n;
void dfs(int t,int ff){
	for(int i=h[t];i;i=sd[i].ne){
		if(sd[i].v!=ff)
		dfs(sd[i].v,t);
	}
	int z;
	z=n;
	for(int i=h[t];i;i=sd[i].ne){
		if(sd[i].v!=ff)
			z=min(z,n+1-p[sd[i].v]);
	}
	p[t]=getfa(z);
	fa[p[t]]=fa[p[t]-1];
}
void _main(){
	
	cin>>n;
	inn=0;
	for(int i=1;i<=n;i++){
		h[i]=0;
		fa[i]=i;
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		cout<<p[i]<<" ";
	}
	cout<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

