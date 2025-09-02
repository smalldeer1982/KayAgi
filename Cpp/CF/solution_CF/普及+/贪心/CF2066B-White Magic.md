# White Magic

## 题目描述

我们称一个序列 $a_1, a_2, \ldots, a_n$ 是魔法的，如果对于所有 $1 \leq i \leq n-1$ 满足：$\operatorname{min}(a_1, \ldots, a_i) \geq \operatorname{mex}(a_{i+1}, \ldots, a_n)$。特别地，任意长度为 $1$ 的序列都被视为魔法序列。

一个整数集合 $a_1, a_2, \ldots, a_k$ 的最小未出现值（MEX）被定义为未出现在该集合中的最小非负整数 $t$。

给定一个由 $n$ 个非负整数构成的序列 $a$。请找到该序列的魔法子序列$^{\text{∗}}$ 的最大可能长度。

$^{\text{∗}}$ 若序列 $a$ 可以通过从序列 $b$ 中删除任意多个（可以是零个或全部）元素得到，则称 $a$ 是 $b$ 的子序列。


## 说明/提示

在第一个测试用例中，序列 $[4, 3, 2, 1, 0]$ 是魔法的，因为：
- $\operatorname{min}(4) = 4$，$\operatorname{mex}(3, 2, 1, 0) = 4$。满足 $4 \geq 4$。
- $\operatorname{min}(4, 3) = 3$，$\operatorname{mex}(2, 1, 0) = 3$。满足 $3 \geq 3$。
- $\operatorname{min}(4, 3, 2) = 2$，$\operatorname{mex}(1, 0) = 2$。满足 $2 \geq 2$。
- $\operatorname{min}(4, 3, 2, 1) = 1$，$\operatorname{mex}(0) = 1$。满足 $1 \geq 1$。

在第二个测试用例中，序列 $[4, 3, 3, 2, 1, 0]$ 不是魔法的，因为 $\operatorname{min}(4, 3) = 3$，$\operatorname{mex}(3, 2, 1, 0) = 4$，此时 $3 < 4$。然而该序列的子序列 $[4, 3, 2, 1, 0]$ 是魔法的，因此答案为 $5$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
5
4 3 2 1 0
6
4 3 3 2 1 0
4
2 0 1 2
1
777
4
1000000000 1 7 9
2
0 1
2
1 2
4
0 1 0 1```

### 输出

```
5
5
3
1
4
2
2
3```

# 题解

## 作者：gesong (赞：10)

题目传送门：[CF2066B White Magic](https://www.luogu.com.cn/problem/CF2066B)。
# 思路

首先观察样例，有两个很显然的性质：
1. 一个没有 $0$ 的数列是神奇的。
2. 有超过两个 $0$ 的数列不是是神奇的。

我们考虑证明性质 $1$，假设这个数列为 $a$，设 $n$ 为其项数，由于这个数列 $a$ 没有 $0$，所以对于任意的 $i$ 都有 $\min(a_1,a_2,\cdots,a_i)>0$ 且 $\operatorname{mex}(a_{i+1},a_{i+2},\cdots,a_n)=0$ 因此 $\min(a_1,a_2,\cdots,a_i)\ge \operatorname{mex}(a_{i+1},a_{i+2},\cdots,a_n)$，证毕。

我们考虑证明性质 $2$，假设这个数列为 $a$，设 $n$ 为其项数，由于这个数列 $a$ 至少有两个 $0$，我们设其中两个 $0$ 的位置为 $i,j$ 满足 $i<j$，则 $\min(a_1,a_2,\cdots ,a_{i-1},a_i=0)=0$ 且 $\operatorname{mex}(a_{i+1},a_{i+2},\cdots,a_j=0,a_{j+1},a_{j+2},\cdots,a_n)>0$ 因此 $\min(a_1,a_2,\cdots,a_i)<\operatorname{mex}(a_{i+1},a_{i+2},\cdots,a_n)$ 不符合神奇的数组的定义，因此不是神奇的，证毕。

我们假设题目给出的数组的个数为 $sum$，由性质 $1$，我们可以将所有的非零的数都挑出来组成子序列，因此答案的下界为 $n-sum$，若这个答案比 $n-sum+1$ 大，那么肯定选择了两个 $0$，由性质 $2$ 可得这种情况非法，因此答案的上界即为 $n-sum+1$。

我们现在只需要考虑 $n-sum+1$ 能否取到，暴力的做法就是将每个 $0$ 和所有非零的数挑出来然后暴力判断这个数列是否是神奇的，但是这样做是 $O(n^2)$ 的复杂度，其实我们可以根据贪心思想，我们只需要将最左边的 $0$ 判断即可，这样做就是 $O(n)$ 的了。

记得特判数组本来就没有 $0$ 的情况。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],b[N],n,mx[N],vis[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
inline bool check(int n){//暴力判断是否合法。
	for (int i=0;i<=::n;i++) vis[i]=0;
	int j=0;
	for (int i=n;i>0;i--){
		if (b[i]>::n){
			mx[i]=j;
			continue;
		} 
		vis[b[i]]=1;
		while(j<=n&&vis[j]) j++;
		mx[i]=j;
	}
	int ans=1e18;
	for (int i=1;i<n;i++){
		ans=min(ans,b[i]);
		if (ans<mx[i+1]) return 0;
	}
	return 1;
}
inline void solve(){
	n=read();
	int sum=0;
	for (int i=1;i<=n;i++) a[i]=read(),sum+=a[i]==0;
	int cnt=0;bool flag=1;
	for (int i=1;i<=n;i++)
		if (a[i]==0&&flag) b[++cnt]=a[i],flag=0;
		else if (a[i]) b[++cnt]=a[i];
	if (sum&&check(cnt)) printf("%lld\n",n-sum+1);//注意原数组要有 0 才进行判断。
	else printf("%lld\n",n-sum);
}
main(){
	int T=read();
	while(T--) solve();
    return 0;
}
//Codeforces Round 1004 RP++
//Codeforces Round 1004 RP++
//Codeforces Round 1004 RP++
//Codeforces Round 1004 RP++
//Codeforces Round 1004 RP++
```

---

## 作者：luanyanjia (赞：3)

比赛结束时我发现自己只过了两题，我意识到我的脑子已经被可爱的线段树吃掉大半了。

我并没有注意到如果直接不选 $0$ 答案只会减少 $1$ 的性质。但是这题还是可以直接暴力做。

首先 $>$ 全局 $\mathrm{mex}$ 的可以直接全选。剩下的数要满足条件，根据定义有这么几种情况：

- 直接不选。
- 这一种数选一个，选完之后 $\mathrm{mex} \le$ 他自己。符合条件。
- 选多个，且选第一个的时候要满足 $\le$ 他的所有数中至少有一个已经被选空了。此时我们发现既然这种数中选上第一个时满足该条件，那么后面的也肯定满足条件，所以选的是一个后缀。

这时直接设 $f_{i,j}$ 为考虑了 $0 \sim i$，此时选单点的数位置最靠右的在 $j$ 时，最多选了几个数。

根据上面的定义就可以直接线段树解决了。

具体地，考虑 $i$ 时：

- 直接不选 $i$，用 $\max\limits_{j=1}^{n}{f_{i-1,j}} + \sum\limits_{j \ge i+1} cnt_j$  更新答案。
- 选了 $a_j = i$，$f_{i,j} = \max\limits_{k \ge j}{f_{i-1,k}} + 1$。
- 选了一个后缀，设满足 $a_j = i$ 的 $j$ 的集合的第 $k$ 大的下标为 $b_{i,k}$，则对于 $j$ 满足 $b_{i,k+1} < j \le b_{i,k}$ 有 $f_{i,j} = f_{i-1,j} + k$。

详见代码。复杂度高且不好写。

```cpp
#include<bits/stdc++.h>
#define pii std::pair<int,int>
#define mkp std::make_pair
#define fir first
#define sec second
typedef long long ll;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
    int ch=getchar();
    T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x*=f;rd(args...);
}
const int N=2e5+5,INF=1e9;
int T,n,a[N],vis[N],tmp[N];
std::vector<int> vec[N];
int mx[N<<2],tag[N<<2];
inline void PushUp(int i){mx[i]=std::max(mx[i*2],mx[i*2+1]);}
inline void Addtag(int i,int x){mx[i]+=x,tag[i]+=x;}
inline void PushDown(int i){
    if(!tag[i])return ;
    Addtag(i*2,tag[i]);Addtag(i*2+1,tag[i]);
    tag[i]=0;
}
void Build(int i,int l,int r){
    tag[i]=0;
    if(l==r)return mx[i]=-INF,void();
    int mid=(l+r)>>1;
    Build(i*2,l,mid);Build(i*2+1,mid+1,r);
    PushUp(i);
}
void Update(int i,int l,int r,int L,int R,int x){
    if(L<=l&&r<=R)return Addtag(i,x),void();
    int mid=(l+r)>>1;PushDown(i);
    if(L<=mid)Update(i*2,l,mid,L,R,x);
    if(R>mid)Update(i*2+1,mid+1,r,L,R,x);
    PushUp(i);
}
void Modify(int i,int l,int r,int x,int v){
    if(l==r)return mx[i]=std::max(mx[i],v),void();
    int mid=(l+r)>>1;PushDown(i);
    if(x<=mid)Modify(i*2,l,mid,x,v);
    else Modify(i*2+1,mid+1,r,x,v);
    PushUp(i);
}
int Query(int i,int l,int r,int L,int R){
    if(L>R)return -INF;
    if(L<=l&&r<=R)return mx[i];
    int mid=(l+r)>>1,ans=-INF;PushDown(i);
    if(L<=mid)ans=std::max(ans,Query(i*2,l,mid,L,R));
    if(R>mid)ans=std::max(ans,Query(i*2+1,mid+1,r,L,R));
    return ans;
}
inline void Solve(){
    for(int i=1;i<=n;i++)if(a[i]<=n)vis[a[i]]=0,vec[a[i]].clear();
    rd(n);
    for(int i=1;i<=n;i++){
        rd(a[i]);
        if(a[i]<=n)vis[a[i]]=1,vec[a[i]].push_back(i);
    }
    int bas=0,lim=0,sum=0,ans=0;
    for(int i=0;i<=n;i++){
        if(!vis[i]){
            lim=i;
            for(int j=1;j<=n;j++)if(a[j]>lim)++bas;
            break;
        }
    }
    for(int i=0;i<lim;i++)sum+=vec[i].size();
    Build(1,1,n);
    int now=vec[0].size();
    for(int x:vec[0])Modify(1,1,n,x,1);
    ans=std::max(ans,sum-now);
    for(int i=1;i<lim;i++){
        now+=vec[i].size();
        ans=std::max(ans,mx[1]+sum-now);
        for(int x:vec[i])tmp[x]=Query(1,1,n,x,n)+1;
        for(int j=(int)vec[i].size()-1;j>=0;j--){
            int x=vec[i][j];
            int y=j==0?1:(vec[i][j-1]+1);
            Update(1,1,n,y,x,(int)vec[i].size()-j);
        }
        for(int x:vec[i])Modify(1,1,n,x,tmp[x]);
    }
    printf("%d\n",std::max(ans+bas,mx[1]+bas));
}
signed main(){
    rd(T);
    while(T--)Solve();
    return 0;
}
```

---

## 作者：E_M_T (赞：2)

在 dp 上想了一会，然后发现 dp 没前途，然后发现是简单题。

考虑转化题目条件，即对于 $i\in [1,n),a_i\ge \operatorname{mex}(a_{i+1},\cdots,a_n)$。

其实不转化也能做，只是转化了好观察一点。

然后观察一些性质：

* 没有 $0$ 一定合法，$\operatorname{mex}=0$。
* 不能存在两个以上的 $0$，否则前一个 $0$ 不满足上文条件。

于是必须将序列删除至一个 $0$，留下最前面的 $0$ 一定不劣。

如果留下一个 $0$ 仍不合法，则序列至少要删一个数，为了最优删去 $0$（否则可能需要删去更多数），如果合法就都不删。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define ff(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define X first
#define Y second
#define Fr(a) for(auto it:a)
int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
void put(int x){print(x);putchar('\n');}
void printk(int x){print(x);putchar(' ');}
const int N=3e5+10;
int n,a[N],vis[N],pp[N];
void solve()
{
	n=read();
	F(i,1,n+1) vis[i]=pp[i]=0;
	int sum=n,fi=0;
	F(i,1,n)
	{
		a[i]=read();
		if(!a[i])
		{
			if(!fi) fi=i;
			else
			{
				pp[i]=1;
				sum--;
			}
		}
	}
	int fl=0,mex=1;//是否有0以及不考虑0的mex
	ff(i,n,1)
	{
		if(fl&&mex>a[i])
		{
			put(sum-1);
			return;
		}
		if(a[i]<=n) vis[a[i]]=1;
		while(vis[mex]) mex++;
		if(a[i]==0&&!pp[i]) fl=1;
	}
	put(sum);
}
int main()
{
	int T=1;
	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：zyb_txdy (赞：2)

[题目链接](https://codeforces.net/contest/2067/problem/E)

### 题意

对于一个长度为 $n$ 的正整数序列 $a$，定义它为「有魔力的」，当且仅当：$\forall 1 \le i < n$，$\min(a_1, ... , a_i) \ge \text{mex}(a_{i + 1}, ... , a_n)$。

现在有多组询问，每次给定一个正整数 $n$ 和一个长度为 $n$ 的序列 $a$，问 $a$ 的最长「有魔力的」子序列有多长。

数据保证 $1 \le \sum n \le 2 \times 10^5$，$0 \le a_i \le 10^9$。

### 分析

被这题打爆了呜呜，可能写不出一些逻辑性的思考了。

首先我们有一个观察是：对于序列 $a$，如果这个序列中不存在 $0$，那么它必定是「有魔力的」。这个的证明比较显然：此时 $\forall 1 \le i < n$，$\text{mex}(a_{i + 1}, ... , a_n) = 0$，而 $\min(a_1, ... , a_i)$ 必定是自然数，故该观察成立。

进一步地，若序列中有两个及以上的 $0$ 存在，那么它必定不是「有魔力的」。证明只需要取两个 $0$ 中间的一个位置作为 $i$ 即可。

我们发现这两个观察，可以对原序列的最长「有魔力的」子序列进行一个很大的限制。具体地，设原序列中 $0$ 的个数为 $\text{cnt}$，则：

1. 若 $\text{cnt} = 0$，则答案为 $n$。

2. 否则，答案为 $n - \text{cnt}$ 或 $n - \text{cnt} + 1$。

接下来只需要讨论第二种情况即可。一个显然的想法是枚举 $a$ 的所有不为 $0$ 的元素与一个 $0$ 组成的子序列并依次判断，复杂度为 $O(n^2)$，显然过不了。并且每次判断都需要处理前缀 $\min$ 和后缀 $\text{mex}$，并不是很好快速转移。

但是还有一个性质是：对于一个不含 $0$ 的序列，若在下标为 $i$ 的位置插入一个 $0$ 后，序列仍然是「有魔力的」，则在下标为 $j$（$j < i$）的地方插入一个 $0$，序列必定也是「有魔力的」。证明只需考虑在 $j$ 插入 $0$ 后所有可能不合法的位置必定在 $i$ 的方案中出现过即可。

于是在原序列 $a$ 中存在 $0$ 时，我们只需要检查 $a$ 的所有不为 $0$ 的值加上 $a$ 中最左边的 $0$ 组成的序列是否是「有魔力的」即可。

- 若它是有魔力的，则答案为 $n - \text{cnt} + 1$。

- 否则，答案为 $n - \text{cnt}$。

这个检查需要统计前缀 $\min$ 和后缀 $\text{mex}$，而这两个东西的 $O(n)$ 求法都是简单的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 2e5 + 5;

int T, n;
int a[N], buc[N], pre[N], suf[N];

void Solve() {
	cin >> n; int cnt = 0;
	for (int i = 1; i <= n; ++i) { cin >> a[i]; cnt += (a[i] == 0); }
	if (cnt == 0) { cout << n << endl; }
	else {
		int m = 0, res = 0; bool flag = true;
		for (int i = 1; i <= n; ++i) {
			if (a[i] != 0) { a[++m] = a[i]; }
			else if (flag) { a[++m] = a[i]; flag = false; }
		}
		for (int i = 1; i <= m; ++i) pre[i] = (i == 1 ? a[i] : min(pre[i - 1], a[i]));
		for (int i = m; i > 0; --i) {
			if (a[i] <= m) ++buc[a[i]];
			while (buc[res]) ++res;
			suf[i] = res;
		}
		for (int i = 1; i <= m; ++i) if (a[i] <= m) --buc[a[i]]; // clear
		for (int i = 1; i < m; ++i) if (pre[i] < suf[i + 1]) { cout << n - cnt << endl; return ; }
		cout << n - cnt + 1 << endl;
	}
}

signed main() {
	cin >> T;
	while (T--) Solve();
	return 0;
}
```

---

## 作者：wmrqwq (赞：2)

# 题目链接

[CF2066B Devyatkino (*1600)](https://www.luogu.com.cn/problem/CF2066B)

# 解题思路

首先根据题目中的定义，你发现你选取一个没有 $0$ 的序列是一定合法的，因为此时任意一个前缀 min 都是至少为 $1$ 的，而任意一个后缀 mex 都为 $0$，原式一定合法。

其次你发现你选取的子序列中最多只能有一个 $0$，首先有一个 $0$ 可以合法，我来讲讲为什么选取 $2$ 个及以上的 $0$ 是不合法的。你发现，当 $i$ 为第一个 $0$ 的位置时，此时前缀 min 为 $0$，而后缀 mex 至少为 $1$ 的，此时原式不合法。

那么我们考虑从序列中取哪个 $0$ 最优，你发现，当你取到 $0$ 时，那么此时你之后的 mex 都为 $0$，符合题目条件，因此你发现越早取 $0$ 的约束条件是最弱的，那么直接取第一个 $0$ 是显然最优的，check 只需要按照题意模拟即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}ll Ss=chrono::steady_clock::now().time_since_epoch().count();mt19937_64 Apple(Ss);ll rand_lr(ll l,ll r){return Apple()%(r-l+1)+l;}
ll _t_;
ll lg[1000010];
ll n;
ll S;
ll a[1000010];
ll b[1000010],k;
ll mex[1000010],minn[1000010];
ll vis[1000010];
void solve()
{
    S=0;
    k=0;
	cin>>n;
	forl(i,0,n+5)
		vis[i]=0;
	forl(i,1,n)
		cin>>a[i],
		S+=(bool)a[i];
	ll id=-1;
	forr(i,n,1)
		if(!a[i])
			id=i;
	if(id==-1)
	{
		cout<<n<<endl;
		return ;
	}
	forl(i,1,n)
		if(a[i] || i==id)
			b[++k]=a[i];
	minn[0]=1e18;
	forl(i,1,k)
		minn[i]=min(minn[i-1],b[i]);
	mex[k+1]=0;
	forr(i,k,1)
	{
		mex[i]=mex[i+1];
		if(b[i]<=n+5)
			vis[b[i]]=1;
		while(vis[mex[i]])
			mex[i]++;
	}
	forl(i,1,k-1)
		if(minn[i]<mex[i+1])
		{
			cout<<S<<endl;
			return ;
		}
	cout<<max(S,k)<<endl;
}
int main()
{
    IOS;
    _t_=1;
    cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：_O_v_O_ (赞：2)

**结论一**：若一个序列中不存在 $0$，那么这个序列一定满足要求。

**证明**：很显然 $\operatorname{mex}\{a_{i+1},a_{i+2},\cdots,a_m\}=0$，而 $\min\{a_1,a_2,\cdots,a_i\}$ 至少为 $0$。

**结论二**：一个满足条件的序列中最多存在 $1$ 个 $0$。

**证明**：若这个序列含有 $\ge 2$ 个 $0$，设第一个 $0$ 所在的下标为 $i$，那么 $\operatorname{mex}\{a_{i+1},a_{i+2},\cdots,a_m\}=0\ge 1$，而 $\min\{a_1,a_2,\cdots,a_i\}=0$。

由结论二，我们选出的子序列最多有 $1$ 个 $0$，我们先贪心的只选 $1$ 个 $0$ 来检查一下这个子序列是否合法，若不合法，根据结论一，我们把选中的 $0$ 去掉即可。

---

## 作者：xzhif (赞：1)

[题面](https://codeforces.com/contest/2067/problem/E "题面")


 首先发现，对于一个没有 0 的序列，神奇序列最大长度为 $n$，因为对于任意一个后缀，其 mex 恒为 0，而对应前缀 min 始终大于零。
 对于一个选择的子序列，如果序列中存在两个 0，其一定不满足条件，因为存在一个只包含一个 0 的后缀，其 mex 不为 0，而对应前缀 min 一定为 0。

 所以，对于对于一个最长合法子序列，其一定包含所有非 0 的数，可能还会再包含一个 0。

 那么我们该选择哪个 0 加到最长合法子序列呢？通过贪心，我们只需选择序列最左边的 0 进行检验，证明：如果 0 在子序列的位置越靠右，那么当后缀包括 0 后，其 mex 一定不比在左边时小，其前缀 min 一定不会更大。

 所以我们只需对序列最左边的 0 检验即可，用 $O(n)$ 的时间判断每个前缀 min 和后缀 mex 的大小关系即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e5+5,inf=1e16;
ll n,a[N],b[N],s[N];
bool c[N];
ll sol(){
	cin>>n;
	bool fla=1;
	ll m=0,cnt;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==0){
			if(fla)b[++m]=a[i];
			fla=0;
		}else b[++m]=a[i];
	}
	if(fla)return n;
	s[0]=inf;
	for(int i=1;i<=m;i++){
		s[i]=min(s[i-1],b[i]);
	}
	ll p=0;
	for(int i=m;i>=1;i--){
		if(b[i]<N)c[b[i]]=1;
		while(c[p])p++;
		if(s[i-1]<p)fla=1;
	}
	for(int i=1;i<=m;i++){
		if(b[i]<N)c[b[i]]=0;
	}
	if(fla)return m-1;
	else return m;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--)cout<<sol()<<'\n';
}
```

---

## 作者：incra (赞：1)

[cnblog](https://www.cnblogs.com/incra/p/18714421)。
### Sol
注意到选取包含 $2$ 个 $0$ 的序列一定不符合条件，因为如果把 $2$ 个 $0$ 一个分到前缀一个分到后缀，那么前缀 $\min$ 为 $0$，后缀 $\operatorname{mex}$ 大于 $0$，不满足条件。

同时，可以发现如果没有选 $0$，那么一定满足条件，因为前缀 $\min$ 一定大于 $0$，而后缀 $\operatorname{mex}$ 一定为 $0$。

记序列中的 $0$ 的数量为 $cnt$，那么答案一定为 $n-cnt$ 或 $n-cnt+1$。

那么接下来就是判断答案是否选了 $0$，不难发现，如果选 $0$，那么选第一个 $0$ 一定不劣，因为包含 $0$ 的前缀一定满足条件，选第一个 $0$ 可以保证包含 $0$ 的前缀最多，此时检查选第一个 $0$ 和其他所有非 $0$ 的元素是否合法，如果合法答案为 $n-cnt+1$，否则为 $n-cnt$。
### Code
[Link](https://codeforces.com/contest/2066/submission/305944009)。

---

## 作者：QWVnbGVzZWVrZXI3D (赞：0)

看到题目我们就能想到 $0$ 是一个特殊的数字。

对于一个没有 $0$ 的数列，它的任何后缀的 $\operatorname{mex}$ 都为 $0$，则这个数列必然为神奇数列。

对于一个拥有超过两个 $0$ 的数列，一定存在一个分割方式使第一个子数组的 $\min$ 值为 $0$，第二个子数组的 $\operatorname{mex}$ 值超过 $0$，则这个数列不是神奇数列。

因此我们需要找到一个没有或仅有一个 $0$ 的子序列。

我们又注意到如果我们选择了数列中的第一个 $0$，假设它并非神奇数列，那么我们选择后面的 $0$ 都将不合法，这是因为 $\operatorname{mex}$ 值不会变，但是 $\min$ 值有可能变小。


方法便显而易见：先将所有非 $0$ 数字加入进来，再把原数列中的第一个 $0$ 插入到相应位置，判断这一个子序列是否为神奇数列，如果是，输出 $len$；如果不是，输出 $len-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, cnt = 0;
    cin >> n;
    vector<int> a(n + 1), tmp(n + 1), vis(n + 5);
    vector<int> zero;
    zero.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        vis[i] = 0;
        cin >> a[i];
    }
    vis[n + 1] = 0;
    bool flag = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 0 && flag == 0)
        {
            flag = 1;
            tmp[++cnt] = a[i];
        }
        else if (a[i] != 0)
        {
            tmp[++cnt] = a[i];
        }
    }
    set<int> mex;
    int Min = 0x7fffffff;
    for (int i = 1; i <= cnt; i++)
        vis[min(tmp[i], n + 1)]++;
    for (int i = 0; i <= cnt + 1; i++)
    {
        if (!vis[i])
        {
            mex.insert(i);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        Min = min(Min, tmp[i]);
        vis[min(tmp[i], n + 1)]--;
        if (vis[min(tmp[i], n + 1)] == 0)
        {
            mex.insert(min(tmp[i], n + 1));
        }
        if (Min < (*mex.begin()))
        {
            cout << (cnt - 1) << "\n";
            return;
        }
    }
    cout << cnt << "\n";
}

int main()
{
    int _;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## [CF2066B White Magic](https://codeforces.com/problemset/problem/2066/B)

## 思路

超级诈骗题。

显然当不选 $0$ 时子序列一定合法，因为此时 $\text{mex}=0$，且子序列中的最小值至少为 $1$。

其次选择 $0$ 的个数不能超过 $1$，因为当 $0$ 的个数超过 $1$ 时，可以将子序列分成两段包含 $0$ 的序列，则其中一段的 $\min=0$，另一段的 $\text{mex}$ 至少为 $1$，显然不满足条件。且选 $0$ 时总是选择最左边的 $0$ 最好，这样可以使得 $\text{mex}\neq 0$ 时的 $i$ 最小。

由此我们可以知道最大答案只可能是不选 $0$ 构成的子序列或只选 $1$ 个 $0$ 构成的子序列的长度，按照题意模拟选择 $0$ 后序列的合法性即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[200005],mn[200005],c[200005],ans,tot;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n;
		tot=n+1;
		mn[0]=INT_MAX;
		for(int i=0;i<=n;i++)
			c[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==0){
				if(tot!=n+1) a[i]=INT_MAX;
				tot--;
			}
			mn[i]=min(mn[i-1],a[i]);
		}
		for(int nw=0,i=n;i>=1;i--){
			if(a[i]<n) c[a[i]]++;
			while(c[nw]) nw++;
			if(mn[i-1]<nw){
				tot--;
				break;
			}
		}
		cout<<min(n,tot)<<endl;
	}
	return 0; 
}
```

---

## 作者：rubbishZZZ (赞：0)

## CF2066B White Magic



#### 题意：

- 我们称一个序列 $a_1, a_2, \dots, a_n$ 为神奇的，如果对于所有 $1 \leq i \leq n-1$，满足以下条件： 
  $$ \min(a_1, a_2, \dots, a_i) \geq \text{mex}(a_{i+1}, a_{i+2}, \dots, a_n) $$ 
  特别地，长度为 $1$ 的序列被认为是神奇的。

  集合 $a_1, a_2, \dots, a_k$ 的最小排除数（MEX）定义为集合中不出现的最小非负整数 $t$。

  给定一个序列 $a$，包含 $n$ 个非负整数，求最大可能的神奇子序列的长度。



#### 解法：

- 第一点：如果数组里的元素都是非 $0$ 的，那么 $\operatorname{mex}$ 一定为 $0$。因此选出所有非 $0$ 的数做子序列一定是合法的。

  第二点：如果选出了两个 $0$，那么第一个 $0$ 位置 $\leq i$，第二个 $0$ 位置 $\gt i$ 时：$\min(a_1,\dots,a_i)=0,\operatorname{mex}(a_{i+1},\dots,a_n)\geq 1$，式子不成立，因此至多选出一个 $0$。

  有了上两点的观察，我们想要判断是否能选出所有非 $0$ 数以及一个 $0$ 来更新答案。

  选哪个 $0$ 呢？考察两个 $0$ 的位置 $p\lt q$，分别选 $p,q$ 两个位置的 $0$，在 $i\leq p,i\geq q$ 的位置，$ \min(a_1, a_2, \dots, a_i) \geq \text{mex}(a_{i+1}, a_{i+2}, \dots, a_n) $ 式子里的值是一样的。在 $p\lt i\lt q$ 的位置，前者右式为 $0$，后者 $\gt 0$，因此选 $p$ 不劣于 $q$。

  因此找到第一个 $0$ 并判断一下是否合法即可。



#### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
//#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}
//int fplus(int x,int y){return x+y>=mod?x+y-mod:x+y;}
//void Fplus(int&x,int y){x=fplus(x,y);}
//int fminus(int x,int y){return x-y<0?x+mod-y:x-y;}
//void Fminus(int&x,int y){x=fminus(x,y);}

const int N=200005;
int n,a[N],mn[N],vis[N],mex,ans,pos;

bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	for(int T=read();T--;){
		n=read();
		rep(i,0,n)vis[i]=0;
		rep(i,1,n)a[i]=read();
		ans=0,pos=0;
		per(i,n,1)if(a[i])ans++;
		else pos=i;
		if(pos){
			mn[0]=1e9,mex=0;
			rep(i,1,n)mn[i]=a[i]?min(a[i],mn[i-1]):mn[i-1];
			bool flag=1;
			per(i,n,pos){
				if(a[i]<=n)vis[a[i]]=1;
				while(vis[mex])mex++;
			}
			per(i,pos-1,1){
				if(mn[i]<mex)flag=0;
				if(a[i]<=n)vis[a[i]]=1;
				while(vis[mex])mex++;
			}
			ans+=flag;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

