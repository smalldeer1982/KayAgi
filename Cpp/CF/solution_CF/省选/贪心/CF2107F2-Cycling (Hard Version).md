# Cycling (Hard Version)

## 题目描述

> 这是此问题的困难版本，和其他版本的区别是此版本中 $1\le n\le 10^6$，且需要对每个前缀都求解。

Leo 骑车去见他的女朋友。在 Leo 的前面有 $n$ 名骑手，从前往后排在第 $i$ 名的骑手的灵活度为 $a_i$。

Leo 将要加速超过前面的所有骑手，他可以执行以下两种操作：
- 当他在骑手 $i$ 后面，骑手 $i+1$ 前面（或 $i=n$）时，付出 $a_i$ 的代价超过骑手 $i$，之后他将在骑手 $i$ 前面，骑手 $i-1$ 后面（如果 $i>1$）；
- 使用他的超级力量交换 $a_i$ 和 $a_j$，代价为 $\vert i-j\vert$。

请你找出超过所有 $n$ 名骑手的最小代价。

额外地，Leo 想知道对于每个 $i(1\le i\le n)$，当只有骑手 $1,2,\cdots,i$ 存在时，他超过所有 $i$ 名骑手的最小代价。

## 说明/提示

**样例解释**

第一组数据中，当存在所有 $n$ 名骑手时，一组操作如下所示：
- 交换 $a_2$ 和 $a_3$，之后 $a=(1,4,2)$，代价为 $1$；
- 超过第 $3$ 名骑手，代价为 $2$；
- 交换 $a_1$ 和 $a_2$，$a=(4,1,2)$，代价为 $1$；
- 超过第 $2$ 名骑手，代价为 $1$；
- 交换 $a_1$ 和 $a_2$，$a=(1,4,2)$，代价为 $1$；
- 超过第 $1$ 名骑手，代价为 $1$。

总代价为 $7$。可以证明这是最小的代价。

第二组数据中，当存在所有 $n$ 名骑手时，如果一直执行“超过”操作，花费为 $4$。可以证明这是最小的代价。

By chenxi2009

## 样例 #1

### 输入

```
4
3
1 2 4
4
1 1 1 1
2
1 2
4
4 1 3 2```

### 输出

```
1 3 7
1 2 3 4
1 3
4 3 6 8```

# 题解

## 作者：masonpop (赞：4)

思维难度 *800 的做法。

以下的 $a$ 序列均是 reverse 后的，即这里认为需要从 $1$ 走到 $n$。

不难想到最优方案一定是若干段代价相同的段组成的，考虑对这些段进行 DP。由于 F2 是后缀询问，因此设 $f_i$ 表示走完了 $1\sim i$，走到 $n$ 的最小代价。转移就枚举这一段的结尾 $j$，那么最优方案一定是把 $[i+1,j]$ 区间的最小值推过来，再一路推到 $j$。设 $[i+1,j]$ 的最小值位置为 $p_j$（如有多个取离 $i+1$ 最近的），那么有转移：

$$\begin{aligned}f_i=\min\limits_{j\ge i+1}\{f_j+(p_j-i-1)+(j-i-1)+a_{p_j}\times (j-i)\}\end{aligned}$$

直接实现可以通过 F1。

注意到这个做法转移和区间最小值有关，太不牛了，考虑简化一下转移形式。我们可以把刚刚的转移方式拆成两段，即 $(i+1)\to p_j$ 和 $(p_j+1)\to j$。那么，我们其实可以认为，如果要从 $i$ 走到 $j$，则中间的代价只有 $a_i$ 和 $a_j$ 两种可能。显然这样能覆盖刚刚的所有转移且均是合法的。

因此可以把转移式拆成以下两种取 $\min$：

$$\begin{aligned}f_i\leftarrow  f_j+(a_i+1)\times (j-i)\end{aligned}$$

$$\begin{aligned}f_i\leftarrow f_j+2(j-i-1)+a_j\times (j-i)\end{aligned}$$

这个东西显然可以使用斜率优化/李超树实现。

这份[代码](https://codeforces.com/contest/2107/submission/319011411)使用后者实现，复杂度 $O(n\log n)$。

---

## 作者：Eous (赞：4)

建议先阅读[简单版题解](https://www.luogu.com.cn/article/ditmhfhm)。~~不读也行~~

我们发现其实我们是可以确定区间的分界点的。比如我们拿一个样例：`4 1 3 2`。我们首先拿 $2$ 一直超。直到我们发现这里出现了一个 $1$。我们发现拿 $1$ 一直超比拿 $2$ 一直超更优。于是我们改拿 $1$ 一直超。我们把 $dp_i$ 的意义改一下，改成：先拿最后的一直超，直到现在超的比前一个数小，我们改拿前一个数继续超，如此循环往复。用此策略超到最前面的最小代价。显然，这玩意可以 $O(n)$ 预处理。

> 不懂策略的看过来\
> 比如 `4 1 3 2 5 3`，先拿 $3$ 一直超，直到我们看到了 $2$，就改拿 $2$ 继续超，然后我们又看到了 $1$，我们又改超 $1$。

那有人要问了：你没考虑把一段区间的最小值掏过来然后拿它一直超的情况啊？确实没考虑，所以我们现在考虑。依然是这个样例：`4 1 3 2 5 3`。假设我们现在在第 $6$ 个数后面。如果我们想把 $2$ 掏过来超，那么需要花费的代价是 $dp_4 + (6 - 4) \times 2 + 2 \times (6 - 4)$。每一项分别表示：已经走到 $2$ 所在的位置还需要的代价，$2$ 往返需要的代价，不停的超过 $2$ 需要的代价。

我们再推几组样例，会发现：如果我想把 $a_i$ 拿到 $j$ 的位置然后一直超，所需要的代价是 $dp_i + (j - i) \times 2 + (j - i) \times a_i$。这玩意可以看做是一个关于 $j$ 的一次函数。总共 $n$ 个一次函数。我们把所有的一次函数都塞到一颗李超线段树里，然后每个位置的答案就是在这个位置查最小值。

```cpp
#include<bits/extc++.h>
#define int long long
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const int maxn = 1e6 + 5;
int n;
int a[maxn],dp[maxn],ans[maxn];
struct line
{
    int k,b;
    int f(int x){return k * x + b;}
}tree[maxn << 2];
int read()
{
    int x = 0,f = 1;
    char ch = getchar();
    while (!isdigit(ch)){f = ch == '-' ? -1 : 1; ch = getchar();}
    while (isdigit(ch)){x = x * 10 + (ch ^ 48); ch = getchar();}
    return x * f;
}
void build(int l,int r,int rt)
{
    tree[rt] = {0,inf};
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l,mid,ls);
    build(mid + 1,r,rs);
}
void upd(line ln,int l = 1,int r = n,int rt = 1)
{
    int lp = tree[rt].f(l),rp = tree[rt].f(r);
    int lq = ln.f(l),rq = ln.f(r);
    if (lq <= lp && rq <= rp)
        tree[rt] = ln;
    else if (lq < lp || rq < rp)
    {
        int mid = (l + r) >> 1;
        if (ln.f(mid) < tree[rt].f(mid))
            swap(ln,tree[rt]);
        if (ln.f(l) < tree[rt].f(l))
            upd(ln,l,mid,ls);
        else
            upd(ln,mid + 1,r,rs);
    }
}
int que(int pos,int l = 1,int r = n,int rt = 1)
{
    int res = tree[rt].f(pos);
    if (l == r)
        return res;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        res = min(res,que(pos,l,mid,ls));
    else
        res = min(res,que(pos,mid + 1,r,rs));
    return res;
}
void solve()
{
    n = read();
    build(1,n,1);
    stack<int> stk;
    stk.push(0);
    for (int i = 1,j; i <= n; i++)
    {
        a[i] = read();
        while (a[j = stk.top()] > a[i])
            stk.pop();// 单调栈维护 dp
        // 我们发现，a[i] 会在 i 和第一个小于 a[i] 的数之间被一直超，于是效仿简单版的转移即可
        dp[i] = dp[j] + i - j - 1 + (i - j) * a[i];
        upd({a[i] + 2,dp[i] - (a[i] + 2) * i});// 塞进李超树
        ans[i] = que(i),stk.push(i);// 单点查询更新答案（一定是边插入边查询）
    }
    for (int i = 1; i <= n; i++)
        printf("%lld ",ans[i]);
    putchar('\n');
}
signed main()
{
    int t = read();
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

[F1，这里要用](https://www.luogu.com.cn/article/b2yc5w5h)

考虑我们最终得到的式子：

$$(a_i+2)n+[sum_i-i(a_i+2)]$$

容易发现，在满足 $i$ 是后缀最小值时，$sum_i$ 是不会随着 $n$ 的变化而变化的，因此这是定的直线，用李超线段树即可。

考虑维护一个单调栈，这样我们可以直接弹出非后缀最小值的位置，这样 $sum$ 的变化是好维护的，转化为区间覆盖区间和，然后上线段树即可。

对于李超线段树，问题转化为：

- 插入线段。

- 撤销最后一次插入。

可以直接可持久化，每次撤销的时候回滚即可。

但是你会发现这样会卡空间，你发现查询只会查询最后一个版本，这样的话我们用肥节点的 trick，每个点修改值直接用 `vector` 存其来，同时维护插入每条线段时哪些点有修改，然后撤销的时候直接 `pop_back`，查询的时候直接调用 `back`。

这样的话，我们在可持久化的时候，就不用每次都复制节点了，并且我们不需要维护左右儿子，空间常数大大减小。

时间空间都是 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define ls p<<1
#define rs p<<1|1
#define endl '\n'
using namespace std;
const int N=1e6+5;
int T,n,k,now,a[N];
stack<int> s;
struct ST{
	struct node{ 
		LL sum;
		int tag; 
	}t[N<<2];
	void build(int p,int l,int r){
		t[p]=node({0,0});
		if(l==r) return;
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=l+r>>1;
			t[ls].tag=t[p].tag,t[rs].tag=t[p].tag;
			t[ls].sum=1LL*t[p].tag*(mid-l+1);
			t[rs].sum=1LL*t[p].tag*(r-mid);
			t[p].tag=0;
		}
	}
	void update(int p,int l,int r,int ql,int qr,int val){
		if(ql<=l&&r<=qr){
			t[p]=node({1LL*val*(r-l+1),val});
			return;
		}
		pushdown(p,l,r);
		int mid=l+r>>1;
		if(ql<=mid) update(ls,l,mid,ql,qr,val);
		if(mid<qr) update(rs,mid+1,r,ql,qr,val);
		t[p].sum=t[ls].sum+t[rs].sum;
	}
	LL qsum(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return t[p].sum;
		pushdown(p,l,r);
		int mid=l+r>>1;
		LL res=0;
		if(ql<=mid) res+=qsum(ls,l,mid,ql,qr);
		if(mid<qr) res+=qsum(rs,mid+1,r,ql,qr);
		return res;
	} 
}S;
vector<pair<int,LL> > t[N<<2];
vector<int> v[N]; 
void build(int p,int l,int r){
	t[p].clear(),t[p].shrink_to_fit();
	t[p].emplace_back(make_pair(0,0x3f3f3f3f3f3f3f3fLL));
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void insert(int p,int l,int r,int k,int b){
	if(1LL*k*l+b<1LL*t[p].back().first*l+t[p].back().second&&1LL*k*r+b<1LL*t[p].back().first*r+t[p].back().second){
		t[p].emplace_back(make_pair(k,b));
		return;
	}
	if(1LL*k*l+b>=1LL*t[p].back().first*l+t[p].back().second&&1LL*k*r+b>=1LL*t[p].back().first*r+t[p].back().second) return;
	int mid=l+r>>1;
	insert(ls,l,mid,k,b);
	insert(rs,mid+1,r,k,b);
}
LL query(int p,int l,int r,int x){
	if(l==r) return 1LL*t[p].back().first*x+t[p].back().second;
	int mid=l+r>>1;
	LL res=1LL*t[p].back().first*x+t[p].back().second;
	if(x<=mid) res=min(res,query(ls,l,mid,x));
	else res=min(res,query(rs,mid+1,r,x));
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		while(s.size()) s.pop();
		S.build(1,1,n);
		build(1,1,n);
		for(int i=1;i<=n;++i){
			while(s.size()&&a[s.top()]>a[i]){
				for(auto p:v[s.top()]) t[p].pop_back();
				s.pop();
			}
			if(s.empty()){
				if(i>1) S.update(1,1,n,1,i-1,a[i]+1);
			} else{
				if(s.top()!=i) S.update(1,1,n,s.top()+1,i-1,a[i]+1);
			}
			S.update(1,1,n,i,i,a[i]);
			s.emplace(i);
			now=i,insert(1,1,n,a[i]+2,S.qsum(1,1,n,1,i)-1LL*i*(a[i]+2));
			cout<<min(S.qsum(1,1,n,1,i),query(1,1,n,i))<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：baka24 (赞：0)

一种非 DP 做法。

先考虑单个序列。

在我们从后往前的过程中，当前在 $i$，如果 $a_{i-1}>a_i$，那花费 $1$ 来交换 $a_{i-1},a_i$ 肯定更优。

找出所有后缀最小值，在这之上考虑。

考虑把一个前面的数 $i$ 移到 $j$ 造成的影响，移动花费 $j-i$，每次向前花费 $j-i$，在每个位置花费 $a_i$。

摊下来就是每个位置造成 $a_i+2$ 的代价。

如果不交换，$i\sim j$ 的这段区间每个位置的代价就是 $a_j+1$。

也就是当 $a_j+1>a_i+2$ 时已经不需要考虑 $a_j$ 了，那么可以得到 $a_j=a_i+1$。

此时 $a_i$ 和 $a_j$ 在每个位置造成的平均代价是一样的，但是 $a_j$ 可能在这段区间出现多次，此时这些位置的代价要 $-1$（因为不用移动了），所以不能断言 $a_i$ 不劣于 $a_j$。

但是如果再引入一个 $j<k$，此时 $a_k=a_j+1$，而 $j\sim k$ 的这段平均代价就是 $a_k+1$，它明显大于 $a_i+2$，也就是说这一段换成 $a_i+2$ 一定是更优的。

所以此时需要比较 $i\sim j$ 选 $a_j+1$ 带来的好处多还是 $j\sim k$ 选 $a_i+1$ 带来的好处多。

就是这两种情况怎样更好：

![](https://cdn.luogu.com.cn/upload/image_hosting/3cgy8lf3.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/kfh88wkx.png)

形式化一点就是比较 $(a_i+2)(k-i)$ 和 $(a_j+1)(j-i)+(a_k+1)(k-j)-cnt_{a_j}-cnt_{a_k}$。

化简一下即 $(a_i+2)(k-i)$ 和 $(a_i+2)(k-i)+(k-j)-cnt_{a_j}-cnt_{a_k}$。

如果让 $i$ 覆盖掉 $[i,k]$ 就不需要考虑 $k$ 了，就是说保留 $k$ 的话需要满足 $cnt_{a_j}+cnt_{a_k}>k-j$。

以此类推，当更多的后缀最小值 $p_i$ 纳入考虑时，限制会变成这样形状的：

$\sum cnt_{a_{p_i}}\ge \sum i(p_{i+1}-p_i)$

就是这两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/6tc0s0gn.png)
~~某人说这个图像某国国旗嘀嘀嘀~~
![](https://cdn.luogu.com.cn/upload/image_hosting/n81uplqq.png)


当这个条件不被满足之后一些 $p_i$ 将会被删掉。

因为右式在 $p_i$ 较多的时候会特别大，所以可以断言 $p_i$ 的有效数量特别少。

所以在枚举前缀的过程中用单调栈维护后缀最小值和后缀最小值出现次数，暴力计算答案即可。

注意扔掉一些数时它们的 $cnt$ 后面还会增长，所以不能全部扔掉，要适当留一点点数。

这不比李超树好写多了（
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=1000010;
int n,m,a[MAXN],b[MAXN];
struct node{
    int x,id,cnt;
}p[MAXN];
void slv(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    m=0;
    for(int i=1;i<=n;i++){
        while(p[m].x>a[i])m--;
        if(!m)m=1,p[1]={a[i],i,1};
        else if(p[m].x+1==a[i])p[++m]={a[i],i,1};
        else if(p[m].x==a[i])p[m].cnt++,p[m].id=i;
        int ans=(p[m].x+2)*(i-p[m].id);
        for(int j=m;j>=1;j--){
            if((p[j].x+2)*(i-p[j].id)<ans)ans=(p[j].x+2)*(i-p[j].id),m=min(m,j+3);
            ans+=(p[j].id-p[j-1].id)*(p[j].x+1)-p[j].cnt;
        }
        printf("%lld ",ans);
    }
    puts("");
}
signed main(){
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    int _=read();while(_--)
    slv();
    return 0;
}
```

---

