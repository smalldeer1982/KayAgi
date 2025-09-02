# Voting (Easy Version)

## 题目描述

简单难度和困难难度的唯一差别是数据范围

有一群选民，你想获得他们全部的选票，而对于第$i$选民，有着一个跟风值$m_i$，如果有其它不低于$m_i$个选民已经投票给你，那么他就会跟风一起投票给你；还有着一个贿赂值$p_i$，如果你可以付出$p_i$个硬币，那么他就会把票投给你

这种投票是分阶段进行的，例如，现在有五个选民他们的跟风值分别是$m_1=1$, $m_2=2$, $m_3=2$, $m_4=4$, $m_5=5$，然后你可以贿赂第五个选民，然后所有选民就会都投票给你，投票给你的选民变化为：$5→1,5→1,2,3,5→1,2,3,4,5$

现在请你计算出最少需要多少个硬币来让所有选民投票给你

## 样例 #1

### 输入

```
3
3
1 5
2 10
2 8
7
0 1
3 1
1 1
6 1
1 1
4 1
4 1
6
2 6
2 3
2 8
2 7
4 4
5 5
```

### 输出

```
8
0
7
```

# 题解

## 作者：wxzzzz (赞：8)

### 思路

贪心。

首先，买一个 $m$ 更大的人显然是更优的，因此以 $m$ 为第一关键字排序，从大到小枚举每个人。

然后，将所有可能自愿交朋友的人存入一个集合 $S$，假设当前考虑到 $i$ 这个人，把他存进去，然后看已经交了朋友的人，也就是 $n-|S|$ 是否大于等于 $m_i$，如果是，那么这个人确实可以免费。否则，从集合里取一个代价最小的（可能也是 $i$），然后把他买通，使得 $i$ 可以免费，这个过程可以用优先队列实现。

此题有多测，优先队列最后可能不为空，要手动清空。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
long long ans;
struct node {
    int m, p;
} a[1000005];
priority_queue<int, vector<int>, greater<int>> q;
bool cmp(node a, node b) {
    if (a.m == b.m)
        return a.p < b.p;

    return a.m < b.m;
}
int main() {
    cin >> t;

    while (t--) {
        cin >> n, ans = 0;

        while (!q.empty())
            q.pop();

        for (int i = 1; i <= n; i++)
            cin >> a[i].m >> a[i].p;

        sort(a + 1, a + 1 + n, cmp);

        for (int i = n; i >= 1; i--) {
            q.push(a[i].p);

            if (a[i].m > n - q.size())
                ans += q.top(), q.pop();
        }

        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：Remilia1023 (赞：5)

# Voting (Easy Version)

## 题面翻译

一共有 $n$ 个选民，你可以付出 $p_{i}$ 的代价让第 $i$ 个选民为你投票，或者，在为你投票的人数达到 $m_{i}$ 时，他会主动为你投票而不用你付出任何代价。

问得到所有选民投票的最小代价。



## Solution

非常难的思维题，从来没遇到过这种题目（说白了就是菜QAQ），觉得 dp 状态设计非常有意思，于是决定写篇题解，这种又能 dp 又能贪心的题挺少见的。

考虑 dp，容易发现，线性 dp 是**有后效性的**，要怎么消除这种后效性呢？

**约定** ：选民编号从 0 开始，$a_i$ 表示第 $i$ 人。

### Analysis:
1. 可以发现，如果已经确定要选哪些人，那么选这些人的顺序是无关的，于是为了方便转移，可以按 $m_i$ 从小到大排序。

2. 一个想法的雏形是，假设正在处理 $a_i$ ，前 $0\sim i - 1$ 人都已投票，要确定 $a_i$ 是否能跟风，最难的地方在于，第 $i + 1 \sim n$ 人的选择会影响当前的转移，这启示我们将 $i$ 之后选择了多少人放入状态之中。

### DP:
设 $dp_{i,j}$ 表示让前 $i + 1$ 个人（即第 $0\sim i$ 人）投票的最小代价，在第 $i$  人之后有 $j$ 个人付了钱。

- 若 $j \ge m_i$，$a_i$ 可立即投票，此时对于 $a_{i - 1}$ 来说，投票人数为 $j + 1$ ，于是 $dp_{i, j} = \min(dp_{i, j}, dp_{i - 1, j + 1})$ 。

- 若 $j + i \ge m_i$（因为编号从 0 开始，所以前面有 $i$ 人），有可能白嫖，但是因为 $m_i$ 从小到大排序了，所以如果能跟风，前面的人一定比 $a_i$ 先跟风，为了不让 $a_i$ 的跟风影响前面的人的决策，$dp_{i, j} = \min(dp_{i, j}, dp_{i - 1, j})$ 。
- 若给 $a_i$ 付钱，$dp_{i, j} = \min(dp_{i, j}, p_i + dp_{i - 1, j + 1})$ 。

### Code1:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second
using LL = long long;
using pii = pair<int, LL>;
const int kN = 5010;
int n, t;
pii a[kN];
LL dp[kN][kN];

int main()
{
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d %lld", &a[i].fir, &a[i].sec);
    sort(a, a + n);                // 按m排序
    for (int j = 0; j <= n; j++)   // 第0人单独处理
      dp[0][j] = (j >= a[0].fir ? 0 : a[0].sec);
    for (int i = 1; i < n; i++)
      for (int j = 0; j <= n - i - 1; j++) {     // i之后最多 n - i - 1 人
        dp[i][j] = 1e18;
        if (j >= a[i].fir)
          dp[i][j] = dp[i - 1][j + 1];
        else if (j + i >= a[i].fir)
          dp[i][j] = dp[i - 1][j];
        dp[i][j] = min(dp[i][j], a[i].sec + dp[i - 1][j + 1]);
      }
    printf("%lld\n", dp[n - 1][0]);
  }
  return 0;
}
```

### Code2:
发现可以滚动数组优化时空常数。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second
using LL = long long;
using pii = pair<int, LL>;
const int kN = 5010;
int n, t;
pii a[kN];
LL dp[kN];

int main()
{
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d %lld", &a[i].fir, &a[i].sec);
    sort(a, a + n);
    for (int j = 0; j <= n; j++)
      dp[j] = (j >= a[0].fir ? 0 : a[0].sec);
    for (int i = 1; i < n; i++)
      for (int j = 0; j <= n - i - 1; j++) {
        if (j >= a[i].fir)
          dp[j] = dp[j + 1];
        else if (j + i >= a[i].fir)
          dp[j] = dp[j];
        else  dp[j] = 1e18;
        dp[j] = min(dp[j], a[i].sec + dp[j + 1]);
      }
    printf("%lld\n", dp[0]);
  }
  return 0;
}
```

PS: 题解写到一半发现自己不会 QAQ 。

---

## 作者：出言不逊王子 (赞：4)

有一种最极端的方法，就是买下所有人，成本记为 $t$。

我们希望成本最小，所以我们希望省下的钱最多。

省下钱，很显然只能通过跟风的形式。

$m$ 很小的乌合之众很容易被吸引过来，所以我们优先考虑 $m$ 大的人。

我们现在处理 $m$ 从大到小第 $i$ 大的人。

我们假设通过跟风被吸引过来的人的集合是 $q$。我们假设他会跟风，所以 $i$ 一开始也在 $q$ 里面。

则最多有 $n-|q|$ 个人我们可以收买。**注意，$q$ 里面的人我们还不知道他是不是真的会投票，所以不计入**。

如果我们把剩下的所有人都收买了，但是他还是不跟风，怎么办？

- 花钱收买他。
- 现在花钱收买另一个人，从而让他跟风。

第二个操作是啥意思呢？

因为此时 $|q|$ 最多是 $i$。

假设 $m_i$ 非常高，那么让他跟风，本来就完全没戏。

那么这个操作就是在 $q$ 中选代价最大的，其他人继续出局，该收买的就乖乖收买。

假如 $m_i$ 比较小，那么他自己就直接被吞噬进去了。

可以手动模拟一下 [P6346](https://www.luogu.com.cn/problem/P6346) 的样例 $3$，能有更深的理解。

也可以手动模拟如下样例：

```
7
6 10
6 9
6 8
5 7
5 6
5 5
5 4
```

对于前三个人，$q$ 集合只养得起一个，所以就是在 $q$ 集合里打擂台。

对于后四个人，$q$ 集合能多养一个了，因为只要五个人被收买，就能有至少一个 $m=5$ 的人成功跟风。可是其他三个 $m=5$ 的人为了养起这个人，必须被收买。

否则大家都互相干瞪眼，没人投出第一张票。

那这三个 $m=5$ 的人是谁呢？肯定是 $p$ 值最小的。

所以用一个优先队列维护集合 $q$。

如果 $p_i$ 非常小，挪来挪去还不如直接买，那就不管了，直接收买 $p_i$ 完事。

记省下的钱是 $r$，答案就是 $t-r$。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define mid (l+r>>1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=200001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
struct per{
	int m,p;
}a[N];
bool cmp(per x,per y){return x.m<y.m;}
priority_queue<int,vector<int>,greater<int> > q;//q里面的表示我们认为他真的会投票的
//但是可能不会呢？那这样一来我们就只能买了
int n,m[N],p[N],tot,g,res;
void mian(){
	tot=g=res=0;
	n=read();fs(i,1,n,1) a[i].m=read(),a[i].p=read(),tot+=a[i].p;
	sort(a+1,a+n+1,cmp);while(!q.empty()) q.pop();
	ft(i,n,1,-1){//先找M大的，这意味着他们的抗打击能力最强 
		//很显然我们希望这些被保的最多
		g+=a[i].p;
		q.push(a[i].p);//我进去，我肯定也能保了
		//注意，此时“保”是我们期待的，但不一定是真的
		if(a[i].m>n-q.size()){//保了的以外的我们全买了，还不够？
			int t=q.top();q.pop();//不过还好欠的不多（顶天一个）
			//因为一个位置最多给你放一个进去，所以ai不会太大，也就是说换了以后它肯定能成功 
			g-=t;
		}
		res=max(res,g);//这次投票活动作废
	} 
	cout<<tot-res<<'\n';
}
signed main(){
	int t=read();while(t--) mian();
	return 0;
}

```

---

## 作者：封禁用户 (赞：3)

[加强版](https://www.luogu.com.cn/problem/CF1251E2)

[第三倍经验](https://www.luogu.com.cn/problem/P6346)

这个减弱版的数据可以用 $O(n^2)$ 的做法实现，但是用 $O(n \log n)$ 的贪心它不香吗？虽然要想一会儿但是写起来快。

### 分析

对于每个人优先考虑是否满足他的 $m$ 值，不满足的话就买 $p$ 值最小的人，这样重复操作每次记录最多能省的钱。

当我们从小到大对 $m$ 排序时很明显贪心就出错了。所以可以考虑从大到小排序，如果不满足 $m$ 就尽量把他往后放，到后面看满不满足。当不满足一个人的 $m$ 时对于 $p$ 值可以把它放进一个优先队列里来维护，每次 $m>n-size$（$size$ 为当前优先队列里元素的数量，即已经获得支持并且不用买的人数）的时候取队首元素，也就是花费最小的人来满足。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 214514
#define M 1919810
#define ll long long
ll t,n;
struct xx{
	ll m,p;
}a[N];
bool cmp(xx x,xx y){
	return x.m>y.m;
}
ll sum,tot,ans; //sum取p的和，tot和ans取最多能节省的钱
int main(){
	cin>>t;
	while(t--){
		priority_queue<ll,vector<ll>,greater<ll> > q;//把优先队列放循环里清空
		sum=tot=ans=0;
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i].m>>a[i].p,sum+=a[i].p;
		sort(a+1,a+n+1,cmp);//从大到小排
		for(int i=1;i<=n;++i){
			tot+=a[i].p;
			q.push(a[i].p);
			if(a[i].m>n-q.size()){
				tot-=q.top();
				q.pop();
			}
			ans=max(ans,tot);
		}
		cout<<sum-ans<<'\n';
	}
	return 0;
}
```


---

## 作者：M_CI (赞：3)

[原题链接](https://www.luogu.com.cn/problem/CF1251E1)

### 思路

一眼丁真，鉴定为贪心。

一开始想了个 $O(t \times n^2)$ 的暴力贪心，但因为看错数据范围而打了个 $O(t \times n \log_2 n)$ 的小根堆维护的贪心。

首先将所有人按 $m_i$ 从小到大的顺序排序，再倒序循环枚举每个人，使得有更高金钱需求的人可以被“零元购”就获得支持。每次将排完序后的第 $i$ 个人的 $q_i$ 值存入小根堆，如果这个人的 $m_i$ 大于可“零元购”获得支持的人数 $n-size$，则将所求答案 $ans$ 加上堆顶元素，然后弹出堆顶，视作已获得其支持。最后输出答案 $ans$。

如果不懂看代码。

### 代码（有注释）


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int t,n;//数据组数与人数
struct node {
	int m,q;
	bool operator < (const node &x) const {
		return m<x.m;
	}//重载运算符
} a[5010];//人
priority_queue<int,vector<int>,greater<int> > h;//定义小根堆

signed main () {
	cin>> t;//输入数据组数
	while (t--) {
		cin>> n;
		long long ans=0;//所求答案（即最小代价）
		while (h.size ()) h.pop ();//多测记得清空
		for (int i=1;i<=n;i++)
			cin>> a[i].m>> a[i].q;//输入人
		sort (a+1,a+n+1);//按mi排序
		for (int i=n;i>=1;i--) {//逆序枚举
			h.push (a[i].q);//压入堆
			if (a[i].m>n-h.size ()) {//判断是否不符合条件
				ans+=h.top ();//增加花销
				h.pop ();//弹出
			}
		}
		cout<< ans<< "\n";//输出
	}
	return 0;//圆满结束
}
```

~~马蜂不好，勿喷~~

据说多倍经验，写一下：

[CF1251E2](https://www.luogu.com.cn/problem/CF1251E2)

[P6346](https://www.luogu.com.cn/problem/P6346)

---

## 作者：Epi4any (赞：2)

补充一个并查集做法：

1. 把 $q_i$ 由大到小排序，因为我们想要白嫖价值最高的数。
2. 把 $q_i$ 安排到一个序列 $p$ 里，这个序列表示被收买的第 $i$ 个人为 $p_i$。

然后我们分析如何搞好 $p$，让其开销最小，此时我们不难想到应该先安排价值最大的那个点。简而言之，我们把 $q_i$ 放到 $p$ 中从 $m_i+1$ 到 $n$ 中第一个没有被用过的地方，如果没有这个位置，我们就把那个人买下来，然后放到 $1$ 到 $n$ 的第一个空位上。

对于查找 $p_k$ 到 $p_n$ 第一个空位的下标，我们用并查集维护，注意路径压缩。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
#define ll long long
struct Node {
	ll a,b;
	bool operator<(const Node x) const {
		return b>x.b;
	}
} in[maxn];
ll n,fa[maxn],size[maxn],p[maxn],ans;
void init() {
	for(ll i=1;i<=n+1;i++){
		fa[i]=i,size[i]=1;
	}
}
ll getf(ll x){
	if(fa[x]==x) return x;
	else {
		fa[x]=fa[fa[x]];
		return getf(fa[x]);
	}
}
inline void merge(ll x,ll y){
	ll fx=getf(x),fy=getf(y);
	if(fx==fy) return;
	fa[fx]=fy,size[fy]+=size[fx];
}
void solve(){
	memset(p,0,sizeof(p));
	ans=0;
	cin>>n;
	for(ll i=1;i<=n;i++) {
		cin>>in[i].a>>in[i].b;
	}
	sort(in+1,in+n+1);/*
	for(int i=1;i<=n;i++) {
		cout<<in[i].a<<" "<<in[i].b<<endl;
	}*/
	init();
	for(ll i=1;i<=n;i++) {
		ll fx=getf(in[i].a+1);
		if(fx<n+1) {
			merge(fx,fx+1);
			p[fx]=in[i].b;
		} else {
			ll pos=getf(1);
			merge(pos,pos+1);
			ans+=in[i].b;
		}
	}
	cout<<ans<<endl;
}
int main() {
	ll t;
	cin>>t;
	while(t--) {
		solve();
	}
	return 0;
}
```


---

## 作者：snowstorm1939 (赞：2)

### CF1251E1 Voting

思路来源于CF某网友。

我们考虑DP。

对所有投票者按照 $m$ 进行不降序排序。

考虑设 $dp_{ind,team}$ 为让前 $ind+1$ 个选民投票所花费的最低金额，而团队中已有一定数量的选民投票。因此，$dp_{n-1,0}$ 即为答案。

我们考虑如何转移

- 若 $team+ind \geq voter_{ind}.first$  那么我们有可能白嫖，转移到 $dp_{ind-1,team}$。
- 付给他 $voter_{ind}.second$，转移到 $dp_{ind-1,team+1}$。

$dp_{ind,team}$ 的值将是这三者中的最小值。对于我们的基本条件，当我们只有一个选民 $(ind=0)$ 要考虑的时候，那么我们必须选择付钱或不支，这取决于我们目前拥有的选民数量。

第一个转换有效是因为当前 $ind$ 个选民投票时，才会转到当前状态。

只能过E1，E2过不了。

```c++
#include<bits/stdc++.h>
#define itn int
#define re register
#define il inline
#define ll long long
#define ull unsigned long long
#define vc vector
#define fi first
#define sc second
using namespace std;
il int read()
{
	int sum=0,sign=1;
	char ch;
	ch=getchar();
	while(!isdigit(ch)){if(ch=='-')sign=-1;ch=getchar();}
	while(isdigit(ch)){sum=sum*10+ch-'0';ch=getchar();}
	return sum*sign;
}
const int mod=1e9+7,maxn=5005;
int n,T;
il ll sol(int n,int team,vc<pair<int,int> >&v,vc<vc<ll> >&dp)
{
    if(!n)
	{
        if(team>=v[n].fi)return 0;//免费
        else return v[0].sc;//付钱
    }
    else if (dp[n][team]!=-1)return dp[n][team];
    ll ans=2e18;
    if (team>=v[n].fi)ans=min(ans,sol(n-1,team+1,v,dp));//有足够的，免费
    else if (team+n>=v[n].fi)ans=min(ans,sol(n-1,team,v,dp));//将来可能能免费
    ans=min(ans,(ll)v[n].sc+sol(n-1,team+1,v,dp));//付钱
    return dp[n][team]=ans;
}
int main()
{
    T=read();
    while (T--)
	{
        n=read();
		vc<pair<int,int> >v(n);
        for (int i=0;i<n;i++)v[i].fi=read(),v[i].sc=read();
        vc<vc<ll> >dp(n,vc<ll>(n+1,-1));
        sort(v.begin(),v.end());
        cout<<sol(n-1,0,v,dp)<<'\n';
    }
    return 0;
}
```



---

## 作者：Hisaishi_Kanade (赞：1)

首先显然如果我们钦定了对于每个人 $i$ 是贿赂还是让他跟风，则先贿赂谁后贿赂谁是不影响答案的。

显然跟风的过程是 $m$ 升序去跟的。我们直接排序先。

那么我们就可以考虑到一个事实，如果 $i$ 是跟风的，那么 $1\sim i-1$ 必然已经被跟掉了。

然而如果前面的不够让他跟风呢？我们在 $m$ 大于当前值的人中寻找一些花费最小的，也就是目前不知道是不是跟风的，贿赂一些，使得可以把目前的跟风掉即可。

如何实现呢？我们 $m$ 从大往小处理，这样前面跟风的改成贿赂就不会算重了。记录目前已经贿赂的人数即可。至于找花费最小的，可以使用 `std::multiset` 维护。具体可以看看代码。

```cpp
#include <bits/stdc++.h>
#define m first
#define p second
using namespace std;
#define clr() fflush(stdout);
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
const int N=5e5+5;
vector<int> e[N];
long long ret;
int i, n, pre, x, y, lft, now;
int main()
{
	int t; scanf("%d", &t);
    while(t--)
	{
        ret=0;
        rep(i, 0, n) e[i].clear();
        cin>>n;
        rep(i, 1, n)
		{
            cin>>x>>y;
            e[x].emplace_back(y);
        }
        multiset<int> q;
        pre=n; now=0;
        req(i, n, 0)
		{
            if(e[i].empty())continue;
            pre-=e[i].size();
            lft=i-pre-now;
            for(auto ins : e[i]) q.insert(ins);
            while(lft-->0)
			{
            	++now;
                ret+=*q.begin();// printf("%lld\n", ret);
                q.erase(q.begin());
            }
        }
        printf("%lld\n", ret);
    }
}
```

---

## 作者：Shadows_of_Twilight (赞：1)

考虑使用**贪心**。

对每个人按 $m$ 从大到小排序，这样可以使后面跟风的人跟多,需要花费金币越少。

维护一个小根堆，从后往前枚举，每次将人的贿赂值入小根堆。

如果当前人民的跟风值**大于**在小根堆里的人数，就将答案加上堆顶元素，并将堆顶元素出堆。

最后输出答案。

注意易错点，每次要将堆清空。~~不会只有我才犯这种错误吧~~。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct M{
	int m,q;
}a[200005];
inline bool cmp(M x,M y){
    return x.m<y.m;
}
priority_queue<int,vector<int>,greater<int> >q;
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i].m>>a[i].q;
		}
        while(q.size())q.pop();//清空堆
		sort(a+1,a+n+1,cmp);
		int cnt=0;
		long long ans=0;
		for(int i=n;i>=1;i--){
			q.push(a[i].q);
			if(a[i].m>n-q.size ())ans+=q.top(),q.pop();
		}
		cout<<ans<<endl;
	} 
	return 0;
}
```


---

## 作者：1234567890sjx (赞：0)

嗯好玩的题，这里放一下可以一并通过 E2 的思路。

[三倍经验 P6346](https://www.luogu.com.cn/problem/P6346)

首先考虑一个很简单的贪心对吧：把所有的人按照 $m$ 从大到小排序然后贿赂，因为看上去肯定是贿赂那些难以随风摇摆的人更优秀是吧？也容易证明这是错的。

因此考虑稍微修正一下贪心。考虑排序之后枚举每一个人 $p$，并把它放到一个优先队列里。一开始默认所有人都是需要被贿赂的。若对于当前枚举的人，认为其不需要被贿赂。使用当前在优先队列里决定被贿赂的人若无法贿赂当前的人，那么就在优先队列里找到代价最小的没有被贿赂的人并将其贿赂即可。时间复杂度为 $O(n\log n)$。

代码写起来真的很简单。

```cpp
const int N=1000100,mod=998244353;
struct qwq{
	int m,p;
}a[N];
signed main(){
	int T;cin>>T;
	while(T--){
		int n;cin>>n;
		int sum=0;
		priority_queue<int,vector<int>,greater<int>>q;
		F(i,1,n)cin>>a[i].m>>a[i].p;
		sort(a+1,a+n+1,[&](auto l,auto r){
			return l.m>r.m||l.m==r.m&&l.p>r.p;
		});
		int s=0;
		F(i,1,n){
			q.push(a[i].p);
			if(a[i].m>n-q.size())s+=q.top(),q.pop();
		}
		cout<<s<<'\n';
	}
	return 0;

```

---

## 作者：fish_love_cat (赞：0)

并查集太巧妙啦！

---

我想买你的票，那么正常情况下我要给你 $p_i$ 块钱。但我如果是在第 $m_i+1$ 及以后的时刻找的你，我就可以白嫖你的票，省下 $p_i$ 块钱。

为了省下尽可能多的钱，我们可以先把每个人按照 $p_i$ 降序排序。

对于当前的这个人，我们能省则省，把找他的时间放到 $m_i+1\sim n$ 中第一个空闲时间。

如果没有空闲时间了那就老老实实买票，不占用多余的时间，把找这个人的时间放到整体的第一个空闲时间。

至于求解某个时间及之后的第一个空闲时间，我们可以使用并查集维护。

注意并查集要初始化到 $n+1$。

---

[代码](https://www.luogu.com.cn/paste/h1nkcv63)。

[CF AC 记录](https://codeforces.com/contest/1251/submission/277144915)。

为什么是 CF？

我想 RMJ 大抵是[似了](https://www.luogu.com.cn/discuss/598533)，所以洛谷这里目前没有 AC 记录，先这样。

---

## 作者：CQ_Bab (赞：0)

# 前言
感谢 LPhang 巨佬教我数学归纳法。
# 思路
看到这种题一眼贪心，首先肯定无疑先按照 $m_i$ 排序，然后再按 $q_i$ 排序但是，这里我们不能直接按照顺序取因为可能你会先用金币一个 $m_i$ 很大的但是 $q_i$ 很小的，所以我们考虑用一个集合 $S$ 来维护那些是可以直接跟风的（这里需要倒序遍历），对于到了一个 $i$ 我们直接判断其前面的和后面补了的的和是否大于等于 $m_i$ 即 $i-1+pl$ 是否大于等于 $m_i$ 这里用 $pl$ 来代表从集合中拿出了几个数，就是要拿几个出来是一个原来要花钱的变成可以白嫖的。

因为这里求的最小值所以直接用一个小根堆维护即可，这个很好维护，这里我要来解释一下为什么每次只用取一个就能保证满足条件。

我们假设在 $i+1$ 的集合为 $S$ 而在 $i$ 时的集合为 $s$ 那么我们对于 $i+1$ 这个点要么会弹出一个要么不变，而在 $i$ 这个点必定会加入一个数，用式子表达就是在 $i+1$ 这个点 $pl$ 最大加一,到了 $i$ 这个点 $i$ 必定减一所以我们可以发现 $pl_i+i\geq pl_{i+1}+i$ 而对于 $i+1$，$pl_{i+1}+i\geq m_i$ 的所以我们可以发现对于 $pl_i+i-1$ 这个式子 $x$ 最小取 $1$ 便可满足 $pl_i+i-1+x\geq m_i$ 毕竟 $m_{i+1}\geq m_i$。
# 代码
代码就很好写了。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
const int N=2e5+10;
int n;
struct node{
	int x,y;
	friend bool operator<(const node&a,const node&b) {
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
}s[N];
priority_queue<int,vector<int>,greater<int>>q;
int res;
void solve() {
	in(n);
	while(q.size()) q.pop();
	rep(i,1,n) in(s[i].x),in(s[i].y);
	sort(s+1,s+1+n);
	int c=0;
	res=false;
	rep1(i,n,1) {
		q.push(s[i].y);
		if(i-1+c<s[i].x) {
            c++;
			res+=q.top();
			q.pop();
		}
	} 
	cout<<res<<endl;
	return;
}
fire main() {
	in(T);
	while(T--) {
		solve();
	}
	return false;
}
```
同时这道题还有三倍经验，讨论区有帖子就不放了。

---

## 作者：Lamb_Carp (赞：0)

# analysis

这个题目我们可以考虑用贪心来做。

我们不难看出来，这个题目是要让我们推出这么个结论：**花小钱，办大人。**

整体贪心的思路就出来了，然后就是实现部分。

因为我们认识的人随便是谁都可以。所以我们如果要买肯定是买最便宜的。这个性质可以用小根堆来维护。同时我们还可以维护我们可能结交的人数 $n - size_q$ 如果比这个人需要的人少直接白嫖不需要什么操作，如果不行就买下来这个人。

# code time
原谅蒟蒻当时写的时候因为忘记怎么写小根堆了，所以多此一举写了个结构体。>_<
```
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define rl register ll 
#define x first
#define y second

typedef pair<ll, ll> pll;

const ll N = 2e5 +10;

ll n, ans;

pll a[N];

struct node
{
    ll x;
    bool operator <(const node &o) const 
    {
        return x > o.x;
    }
};

priority_queue<node> q;

int main()
{
    // freopen("1.in", "r", stdin), freopen("1.out", "w", stdout);

    scanf("%lld", &n);

    for(rl i=0; i < n; ++ i) scanf("%lld%lld", &a[i].x, &a[i].y);

    sort(a, a + n);

    for(rl i=n - 1; i >= 0; -- i)
    {
        q.push({a[i].y});
        if(a[i].x > n - q.size())
        {
            auto t = q.top();
            ans += t.x;
            q.pop();
        }
    }

    printf("%lld", ans);
    return 0;
}
```

---

## 作者：_ldyex_ (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF1251E1)

共有 $t$ 组数据，每组数据中有 $n$ 人，已知每个人的跟风值 $m$ 和贿赂值 $q$ ，跟风值指如有 $x$ 个人是与你一伙的，那么 $m \le x$ 的人都会加入你的队伍，如果不会，你可以贿赂他。求当让所有人加入你所需的最少钱数。

## 思路：
### 贪心
我们在输入数据后要先排序，按 $m$ 从大到小排。为什么？因为要优先考虑不容易跟风的人。如果 $m$ 相同，则 $q$ 小的在前，因为他们需要的钱更少（~~当然不是因为没钱~~）。

接着遍历每个人，用小根堆将遍历时人的 $q$ 存起，当已被贿赂或将被贿赂的人的数量比这个人的跟风值小时（ $n - \left| q \right| < a_{m}$ ），那我们就从小根堆中拿出最少的钱以用于贿赂，直到这个人被贿赂为止。

### 易错点

1. 最坏情况下 $ans = 10^{9} \times 5^{3} \approx 10^{11}$，所以 $ans$ 要开 ```long long```！

2. 本题有多组数据，需要清空！

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn = 5e3 + 1;

struct node{
  int q, m;
}a[maxn];

int t, n;
long long ans;
priority_queue<int> q;

bool cmp(const node &a, const node &b){
  return (a.m != b.m ? a.m > b.m : a.q < b.q);
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while(t--){
    cin >> n;
    ans = 0;
    for(int i = 1; i <= n; i++){
      cin >> a[i].m >> a[i].q;
    }
    sort(a + 1, a + 1 + n, cmp);	  //排序
    for(int i = 1; i <= n; i++){	  //懒得写小根堆，于是将数变为负数
      q.push(-a[i].q);
      if(n - q.size() < a[i].m){
        ans -= q.top();
        q.pop();					
      }
    }
    while(q.size()){             //多测不清空，爆零两行泪
      q.pop();
    }
    cout << ans << '\n';
  }
  return 0;
}
```


---

## 作者：elbissoPtImaerD (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P6346)，下文记 $m$ 为 $a$，$p$ 为 $b$。

最优策略一定是先把所有要代价的朋友交完，然后剩下的全部不花费代价。

那么只需考虑给定不花费代价的项目判断合法。

按 $a_i$ 从大到小排序，显然有需要满足第 $i$ 个不花费代价的朋友 $x$ 要 $a_x \le n-i$。

直接贪心，维护不花费代价的朋友集合即可。

```cpp
void Solve() {
  int n; cin>>n;
  LL s=0;
  ve<pii>a(n); for(auto&[x,y]:a) cin>>x>>y,s+=y;
  sort(rll(a));
  multiset<int>S;
  for(auto[x,y]:a) {
    S.ep(y);
    if(n-Sz(S)<x) S.erase(begin(S));
  }
  cout<<(s-accumulate(all(S),0LL))<<'\n';
  return;
}
```

---

