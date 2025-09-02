# Invertible Bracket Sequences

## 题目描述

### 题意翻译
### 题面描述
我们定义一个合法的括号序列，是仅由 `(` 和 `)` 构成的字符串且：
1. 空串 $\epsilon$ 是合法的括号序列。
2. 若 $s$ 为合法的括号序列，则 $(s)$ 也为合法的括号序列。
3. 若 $s,t$ 均为合法的括号序列，则 $st$ 也为合法的括号序列。（其中 $st$ 表示将字符串 $s$ 和 $t$ 拼接。）

定义对一个括号序列的**翻转**操作为：将这个括号序列的所有 `(` 变为 `)`，所有 `)` 变为 `(`。

如 `()(((` 翻转后成为 `)()))`。

给定一个**保证合法**的字符串 $s$。

你可以选择字符串 $s$ 的一个**子串**进行翻转操作。（注意是**子串**，与**子序列区分**，子串要求**连续**。）

问**翻转**了一个**子串**后得到的字符串 $s'$ 仍然是**合法括号序列**的方案数。

## 说明/提示

在本题中，不可以翻转长度为 $0$ 的子串。

translate by Hoks。

## 样例 #1

### 输入

```
4
(())
()
()()()
(()())(())```

### 输出

```
1
0
3
13```

# 题解

## 作者：mystic_qwq (赞：23)

计数题，赛后才会。

一些规定：  
记「栈的匹配」为分别将串里的字符放进一个栈里，然后能匹配的都弹出。这样形成的一个栈。  
记 $x_i$ 为考虑前 $i$ 个括号，「栈的匹配」的大小。  
同时记 $x$ 为特定时刻「栈的匹配」的大小。

题意：给定一个合法括号序列，问存在多少组 $[l,r]$ 使得翻转其中括号后原串仍然合法。

首先，我们能隐约的感觉到，这题要借助栈，来把所有内部的括号消去了，然后对于剩下的加上一个特定的值作为贡献。我们可以确认这样一件事情：首项只能是 $\texttt ($，末项只能 $\texttt )$。所以要加入一些限制。

进一步，这个特定的值是什么？

比如对于串 $\texttt{()()()}$，进行到字符 $3$ 时，可以翻转 $[2,3]$。进行到 $5$ 时我们可以翻转 $[2,5]$ 或 $[4,5]$。在 $2$ 的时候，栈大小和在 $4$ 时相同。

我们可以计数，将栈视为匹配的容器。当 $x$ 达到一个数的时候，我们将 $v_x$ 加 $1$。由于第一个和最后一个不能翻转，所以只有 $x\ne 0$ 时，当前位置对答案的贡献为 $v_x$。同时让 ta 自增。也就是记录下**多少位置有 $x$ 个前括号没有被匹配**。比如对于上面的串，  
1. $x_1=1$，$v_1=1$，$t$ 不变，
2. $x_2=0$，$v$，$t$ 不变，
3. $x_3=1$，$t\gets t+1=1$，$v_1=2$，
4. $x_4=0$，$v$，$t$ 不变，  
5. $x_5=1$，$t=t+2=3$，$v_1=3$。

经过上面的操作，我们成功的得出了有 $x$ 个括号的位置个数，从而推出他们对答案的贡献。

那么，这样思路是完善的吗？

其实并不是。上面这个串不够复杂。其实当 $x$ 为奇数时，我们令 $v_{\frac{x-1}2}$ 归零。这是因为，后面 $x$ 达到 $\frac{x-1}2$ 时，将无法用到之前的那些位置。

$\texttt{((((()())))())}$ 。这个串只有 $7$ 种翻转方法。以倒数第二个字符为例，ta 和第 $2$ 个字符之间出现过超越 $2x_2$ 的 $x$。所以 ta 没法与 $2$ 匹配。**这是因为在翻转时，中间有一段后括号的数量会无法匹配，造成栈里第一个括号是后括号。**

其实可以发现，$x=0$ 时候加上上述限制也可以不进行特判。所以直觉上来看，字符串题目针对 $x=0$ 的特判不是本质性质。需要探究其他方面。

时间复杂度 $O(n)$。
```cpp
#include<stdio.h>
#include<string.h>
#define N 200005
#define ll long long
char s[N];
int n,v[N];
inline ll work(){
  n=strlen(s);
  memset(v,0,n<<2);
  ll cnt=0;
  for(int i=0,x=0;i<n;++i){
    if(s[i]=='(') ++x; //left
    else --x;
    if(x&1) v[x>>1]=0; //non-match
    if(x) cnt+=v[x]++; // if(x) 可以忽略 v[0]永远0
  }
  return cnt;
}
main(int T){
  for(scanf("%d",&T);T--;)
    scanf("%s",s),printf("%lld\n",work());
}
```

---

## 作者：yshpdyt (赞：14)

## 题意
给定合法括号匹配序列，求区间取反后仍然为合法序列的连续区间个数。

## Sol
如果画出折线图，本题就很好思考。

转化成 $+1,-1$ 的序列，求前缀和，应当满足任意时刻 $sum_i>0$，考虑画出折线图，如图所示.
![](https://cdn.luogu.com.cn/upload/image_hosting/zxai0vvn.png)

每次取反首先要满足左括号数量等于右括号数量，所以选择的两个端点 $l,r$ 必须满足 $sum_l=sum_r$ ，对应图上就是 $y$ 坐标相等。

由于任意时刻 $sum_i>0$，所以对于区间 $[l,r]$，最大值设为 $sum_{x}$，应当满足 $sum_x-sum_l \le sum_l-0$，对应图上，就是最高点翻转后仍然在 $x$ 轴上方。

考虑对于确定的 $y=sum_i$，求出多少个区间可以翻着，由于区间最大值可合并性，若 $sum_l=sum_{mid}=sum_r=y$，满足 $[l,mid]$ 可翻折，$[mid,r]$ 可翻折，则 $[l,r]$ 可翻折。(可以考虑图上的 $H,L,M$ 三点)。

也就是说，钦定右端点 $r$，找到最小的左端点 $l$，满足 $\max\limits_{i=l}^r sum[i]\le2sum[l]$，区间最大值可以用线段树或 st 表轻松维护，再记录一下上一个不满足条件位置即可。

对于确定的 $y$ 已经知道如何求了，可以考虑扫描线从低到高扫描一遍累加答案。

时间复杂度 $O(n\log n)$。


## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,a[N];
string s;
ll sum[N];
struct sgt{
    #define mid ((l+r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    ll mx[N*4],lzy[N*4];
    void lt(ll p,ll x){
        mx[p]+=x;
        lzy[p]+=x;
    }
    void build(ll p,ll l,ll r){
        mx[p]=lzy[p]=0;
        if(l==r){
            mx[p]=sum[l];
            return ;
        }
        build(ls,l,mid);
        build(rs,mid+1,r);
        mx[p]=max(mx[ls],mx[rs]);
    }
    void pushdown(ll p){
        lt(ls,lzy[p]);
        lt(rs,lzy[p]);
        lzy[p]=0;
    }
    void upd(ll p,ll l,ll r,ll le,ll ri,ll t){
        if(le<=l&&ri>=r){
            lt(p,t);
            return ;
        }
        pushdown(p);
        if(le<=mid)upd(ls,l,mid,le,ri,t);
        if(ri>mid)upd(rs,mid+1,r,le,ri,t);
        mx[p]=max(mx[ls],mx[rs]);
    }
    ll qr(ll p,ll l,ll r,ll le,ll ri){
        if(le<=l&&ri>=r)return mx[p];
        pushdown(p);
        ll ans=-inf;
        if(le<=mid)ans=max(ans,qr(ls,l,mid,le,ri));
        if(ri>mid)ans=max(ans,qr(rs,mid+1,r,le,ri));
        return ans;
    }
}T;
vector<ll>v[N];
void sol(){
    cin>>s;
    n=s.size();
    s=" "+s;
    for(int i=0;i*2<=n;i++)v[i].clear();
    for(int i=1;i<=n;i++){
        if(s[i]=='(')a[i]=1;
        else a[i]=-1;
        sum[i]=sum[i-1]+a[i];
        v[sum[i]].push_back(i);
    }
    ll res=0;
    T.build(1,1,n);
    for(int i=0;i*2<=n;i++){
        ll last=-1;
        for(int j=0;j+1<v[i].size();j++){
            auto t=T.qr(1,1,n,v[i][j],v[i][j+1]);
            if(t>i*2)last=j;
            res+=j-last;
        }
    }
    cout<<res<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：Hoks (赞：9)

## 前言
比较简单/板子的题，如果碰到过类似 trick 应该能很快切吧。

这场 A 题被 CF 判成 BOT 硬控 $15$ 分钟，perf 只有 $1900$ 出头，有点亏。
## 思路分析
括号匹配问题，首先想到经典 trick，把 `(` 看做 $+1$，`)` 看做 $-1$。

得到前缀和 $s$，则如果 $s_n=0$ 并且 $\forall s_{1\sim n}\ge0$。

接着考虑怎么处理翻转。

考虑对于 $i,j$，如果翻转了 $i\sim j$ 这段括号仍然是合法的，那么他们满足的条件即为：
1. 首先这段括号要是合法的，也就是 $s_r=s_l-1$。

翻转也就是 $+1$ 变 $-1$，那怎么处理呢。

想到把这个前缀和的图像画出来。

那么前面的那个条件就相当于是这两点同高度。

那么图像上，翻转也就是把图像直接沿着 $y=s_r$ 这条线对着一下，作用区间 $[l,r]$。

因为仍然要合法，所以折下去不能到第四象限。

考虑朴素实现，用 `vector` 存下等高度的点，全部扫一遍 $check$ 计数。

接着来优化，不难发现影响是否可行的就是峰顶，如果峰顶折下去仍然符合，那么其他部分也肯定符合。

因为右端点固定了，所以 $\max$ 随着左端点往左走单调不减。

考虑用 ST 表搭配二分的方式找到最左的符合题意的左端点，加入贡献即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,mod=1e9+7,V=1e9,INF=0x3f3f3f3f3f3f3f3f;
int T,n,a[N];vector<int>e[N];char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='('||c==')'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
struct ST
{
    int st[20][N];
    void get_ST(int a[])
    {
        for(int i=1;i<=n;i++) st[0][i]=a[i];
        for(int j=1;j<=19;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    int get(int l,int r){int k=log2(r-l);l++;return max(st[k][l],st[k][r-(1<<k)+1]);}
}st;
signed main()
{
    T=read();
    while(T--)
    {
        n=0;rd(s,n);for(int i=0;i<=n;i++) e[i].clear();
        for(int i=1;i<=n;i++)
            if(s[i]=='(') a[i]=a[i-1]+1;
            else a[i]=a[i-1]-1;
        st.get_ST(a);int ans=0;
        for(int i=1;i<=n;i++)
        {
            int l=0,r=e[a[i]].size()-1,res=e[a[i]].size();
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(st.get(e[a[i]][mid],i)>2*a[i]) l=mid+1;
                else res=mid,r=mid-1;
            }ans+=e[a[i]].size()-res;e[a[i]].emplace_back(i);
        }print(ans);put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：2huk (赞：7)

小清新计数题。

> 给定一个合法括号序列 $S$。求有多少个子区间满足将其翻转（左括号变右括号，右括号变左括号）后，整个串仍合法。

定义 $a_i = \left\{ \begin{matrix} 1 &, S_i = \texttt ( \\ -1 &, S_i = \texttt )\end{matrix} \right.$，$s_i = \sum_{j=1}^i a_j$。

那么 $S$ 合法等价于：

- $s_n = 0$；
- $\min s_i \ge 0$。

考虑翻转区间 $[l, r]$。因为原串 $S$ 合法，即 $s_n = 0$，如果翻转 $[l, r]$ 后仍保持 $s_n = 0$，那么 $s_r - s_{l-1}=0$ 是必要的。也就是说区间内左右括号数量相等。

若 $s_r = s_{l-1}$，那么我们还需要保证 $\min s_i \ge 0$。我们考虑翻转后，前缀和 $s'_l, s'_{l+1}, \dots, s'_r$ 的变化：
$$
\begin{aligned}
s'_i &= s_{l-1} + s'_i - s'_{l-1}\\
&= s_{l-1}- (s_i - s_{l-1})\\
&= 2s_{l-1} - s_i
\end{aligned}
$$
我们希望 $\min s'_i \ge 0$。又因为 $i \not \in [l, r]$ 时 $s'_i = s_i$，而原串是合法的，所以条件可以强化成 $\min_{i=l}^r 2s_{l-1} - s_i \ge 0$，即 $\max_{i=l}^r s_i \le 2s_{l-1}$。

考虑计数。枚举 $l$，计算 $r$ 的合法取值数。

显然 $l$ 固定时 $\max_{i=l}^r s_i$ 是单调不降的。二分即可。

```cpp
char str[N];
int n;
int sum[N];
int st[N][20];

int query(int l, int r) {
	int k = log2(r - l + 1);
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}

map<int, vector<int>> pos;

int query(int l, int r, int x) {
	return l <= r ? upper_bound(pos[x].begin(), pos[x].end(), r) - lower_bound(pos[x].begin(), pos[x].end(), l) : 0;
}

ll solve() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	
	pos.clear();
	for (int i = 1; i <= n; ++ i ) {
		sum[i] = sum[i - 1] + (str[i] == '(' ? 1 : -1);
		st[i][0] = sum[i];
		pos[sum[i]].push_back(i);
	}
	
	for (int j = 1; j < 20; ++ j )
		for (int i = 1; i + (1 << j - 1) <= n; ++ i )
			st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	
	ll res = 0;
	
	for (int l = 1; l <= n; ++ l ) {
		int lo = l, hi = n, r = l - 1;
		while (lo <= hi) {
			int mid = lo + hi >> 1;
			if (query(l, mid) <= 2 * sum[l - 1]) lo = mid + 1, r = mid;
			else hi = mid - 1;
		}
		res += query(l, r, sum[l - 1]);
	}
	
	return res;
}
```

---

## 作者：tai_chi (赞：5)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18445424) 中阅读。

### 题意

给一个合法括号序列，问有多少区间 $[l,r]$，使得将区间内的每个括号翻转后，括号序列仍合法。

### 分析

十分套路地，我们将 `(` 看成 $+1$，将 `)` 看成 $-1$，则一个括号序列合法的充要条件是转换后的序列满足：

1. 前缀和任意位置非负；
2. 最后一项为 $0$。

考虑翻转括号序列意味着什么。翻转后 $+1,-1$ 对调，为保证条件二，需要满足区间内的 $+1,-1$ 数量相等，条件一则可以通过前缀和折线图来思考。

反转后，折线图的向上变为向下，向下变为向上，实际上就是上下对称地翻转过来，对称轴就是区间的左右端点较小值。不合法当且仅当折下去低于 x 轴。

这样条件就明朗了，我们可以将前缀和丢进 map 里面，在右端点处统计对答案的贡献。最后再把折下去不合法的从 map 里扔出去。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

void solve()
{
	string s; cin>>s;
	map<int,int> cnt;
	cnt[0]=1;
	int st=0,ans=0;
	for(char c:s)
	{
		if(c=='(') st++;
		else st--;
		ans+=cnt[st];
		cnt[st]++;
		while((*cnt.begin()).first*2<st) cnt.erase(cnt.begin());
	}
	cout<<ans<<endl;
}

signed main()
{
	IOS;
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：3)

套路的把左括号看成 $1$，右括号看成 $-1$。那么一个括号序列合法当且仅当前缀和数组 $s_i\ge0$ 且 $s_n=0$。

考虑一个区间 $[l,r]$ 可以修改当且仅当其中左右括号数量相等，同时修改完之后前缀和数组不会变成负数。前者直接前缀和数组判断，后者可以转化为 $\max_{i=l}^r s_i\le 2\times s_l$，可以 ST 表维护。

但是这样的复杂度是 $O(n^2)$ 的。但是考虑到如果区间 $[l,r]$ 和区间 $[r+1,r']$ 都可以进行修改，那么区间 $[l,r']$ 显然也可以进行修改。所以我们可以直接开桶记录前缀和相同的位置，然后每次只判断相邻两个位置构成的区间是否可以修改即可。

总时间复杂度 $O(n\log n)$。

[提交记录](https://codeforces.com/contest/1976/submission/263397329)

---

## 作者：鲤鱼江 (赞：2)

我们把左括号的权值看做 $1$，右括号的权值看做 $-1$，那么一个括号序列合法的充要条件是权值总和恰为 $0$ 且每一个前缀的权值和不小于 $0$。

由此，我们有了形式化判定一个括号序列的能力。

我们约定 $a_i$ 是赋权后的括号序列，$sum_i=\sum\limits_{j=1}^i a_j$。

从赋权角度来看，我们反转一个子串就相当于区间取反，且我们期望在反转后仍然满足以上条件，不难发现我们反转的一个区间必是和为 $0$ 的，否则一定不满足条件。

那么现在我们要处理的只有每一个前缀都不小于 $0$ 的限制了，我们先考虑如何判定是否合法。

假定我们反转了区间 $[l,r]$ 则每个前缀都不小于 $0$ 等价于区间 $[l,r]$ 的最大前缀和小于等于 $sum_{l-1}$。

有了这个结论，我们可以二分出每一个节点最远到达那里，用 vector 存下来，及时删除贡献，最后用 map 扫一遍统计答案即可。

时间：$O(n\log^2n)$。

~~感觉没 C 难啊~~。

code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define rs now<<1|1
#define ls now<<1

using namespace std;

inline int read(){
	int x=0,f=0;
	char c=getchar();
	while(c<'0'||c>'9'){f|=(c=='-');c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return f?-x:x;
}

const int N=5e5+10;
int T,n,a[N],t[N],sum[N];
vector < int > v[N];
map < int , int > mp;
char s[N];

struct MaxPre{
	struct node{
		int pre,sum,flag;
		node(){pre=sum=flag=0;}
		#define flag(k) tr[k].flag
		#define pre(k) tr[k].pre
		#define sum(k) tr[k].sum
	}tr[N<<2];
	inline node merge(node &x,node &y){
		if(!x.flag) return y;
		if(!y.flag) return x;
		node z=node();z.flag=1;
		z.pre=max(x.pre,x.sum+y.pre);
		z.sum=x.sum+y.sum;
		return z;
	}
	inline void pushup(int now){tr[now]=merge(tr[ls],tr[rs]);}
	void build(int now,int l,int r){
		flag(now)=1;
		if(l==r){
			pre(now)=max(a[l],0ll);
			sum(now)=a[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(now);
	}
	inline node ask(int now,int l,int r,int x,int y){
		if(x<=l&&r<=y) return tr[now];
		int mid=(l+r)>>1;node res1=node(),res2=node();
		if(mid>=x) res1=ask(ls,l,mid,x,y);
		if(mid<y) res2=ask(rs,mid+1,r,x,y);
		return merge(res1,res2);
	}
}p;

signed main(){
	T=read();
	while(T--){
		scanf("%s",s);n=strlen(s);mp.clear();
		for(int i=1;i<=n;++i) a[i]=((s[i-1]=='(')?1:-1);
		for(int i=1;i<=n;++i) v[i].clear();
		p.build(1,1,n);
		for(int i=1;i<=n;++i){
			sum[i]=sum[i-1]+a[i];
			int l=i,r=n,res=i;
			while(l<=r){
				int mid=(l+r)>>1;
				if(p.ask(1,1,n,i,mid).pre<=sum[i-1]){
					l=mid+1;res=mid;
				}else r=mid-1;
			}
			v[res].emplace_back(i);
		}
		int ans=0;
		for(int i=1;i<=n;++i){
			ans+=mp[sum[i]];
			++mp[sum[i-1]];
			for(int j:v[i]) --mp[sum[j-1]];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：LiaoYF (赞：2)

场切。+4。

## 做法

首先我们想一下一个括号序列合法要满足哪些条件。

- 左括号个数等于右括号个数。


- 对于每个前缀，左括号的出现次数都不小于右括号的出现次数。因为如果有一次不满足，那么多出来的那个右括号就永远无法匹配了。

对于这种题，经常需要枚举左端点，然后判断有多少个合法的右端点。

我们枚举左端点，发现满足第二个条件的位置是具有单调性的，于是在所有满足第一个条件的位置中二分右端点的位置。

如何快速判断是否满足第二个条件？先计算出来当前左括号个数减右括号个数的前缀和，然后用 ST 表维护区间最小值，再判断反转后到区间最小值满不满足即可。


## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
const int inf=1e18;
string s;
int a[200005],stmax[200005][25];
map<int,vector<int> > b;
int querymax(int l,int r){
    int x=log2(r-l+1);
    return max(stmax[l][x],stmax[r-(1<<x)+1][x]);
}
void solve(){
    cin>>s;
    int n=s.size();
    s=" "+s;
    b.clear();
    for(int i=1;i<=n;i++){
        a[i]=a[i-1]+(s[i]=='('?1:-1);
        b[a[i]].push_back(i);
    }
    for(int j=0;j<=20;j++){
        for(int i=0;i<=n;i++){
            stmax[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        stmax[i][0]=a[i];
    }
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            stmax[i][j]=max(stmax[i][j-1],stmax[i+(1<<(j-1))][j-1]);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int l=lower_bound(b[a[i-1]].begin(),b[a[i-1]].end(),i)-b[a[i-1]].begin()
        ,r=b[a[i-1]].size()-1;
        if(l>r)continue;
        int res=-1;
        int ll=l;
        while(l<=r){
            int mid=(l+r)/2;
            if(a[i-1]-(querymax(i,b[a[i-1]][mid])-a[i-1])>=0){
                l=mid+1;
                res=mid;
            }else{
                r=mid-1;
            }
        }
        if(res!=-1){
            ans+=res-ll+1;
        }
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t,multitest=1;
    if(multitest)cin>>t;
    else t=1;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：shao0320 (赞：1)

考虑前缀和，左括号为+1，右括号为-1，那么合法的括号序列匹配一定是前缀和为0，而反转一段区间不会改变右端点之后的前缀和的时候，才合法，同时要保证前缀和不能出现负数（否则在某个位置右括号的数量会大于左括号导致非法）。因此对于一个点 i，要在 $i$ 前找到所有位置 $j$ 保证 $\max pre_k (j\leq k \leq i)\leq 2\times pre_i$，同时$pre_j=pre_i$

那么用主席树或动态开点的树状数组维护即可，用 ST 表找出最靠左的合法位置 $j$ 即可。

code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<unordered_map>
#define int long long
#define lowbit(x) x&-x
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f;
}
int t,n,pre[N],st[N][19],c[N*5],cnt;
char S[N];
unordered_map<int,int>mp[N];
int query(int l,int r)
{
    int bas=log2(r-l+1);
    return max(st[l][bas],st[r-(1<<bas)+1][bas]);
}
struct Fenwick_Tree
{
    void newnode(int v,int x)
    {
        mp[v][x]=++cnt;
        c[cnt]=0;
    }
    void modify(int v,int x,int val)
    {
        for(;x<=n;x+=lowbit(x))
        {
            if(!mp[v][x])newnode(v,x);
            c[mp[v][x]]+=val;
        }
    }
    int query(int v,int x)
    {
        int res=0;
        for(;x;x-=lowbit(x))
        {
            res+=c[mp[v][x]];
        }
        return res;
    }
}T;
signed main()
{
    #ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    t=read();
    while(t--)
    {
        cin>>(S+1);
        n=strlen(S+1);cnt=0;
        for(int i=0;i<=n;i++)mp[i].clear();
        for(int i=1;i<=n;i++)pre[i]=pre[i-1]+(S[i]=='('?1:-1);
        for(int i=1;i<=n;i++)st[i][0]=pre[i];
        for(int i=1;i<=18;i++)
        {
            for(int j=1;j+(1<<i)-1<=n;j++)
            {
                st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
            }
        }
        long long ans=0;
        for(int i=1;i<=n;i++)
        {
            int L=1,R=i;
            while(L<R)
            {
                int mid=(L+R)>>1;
                if(query(mid,i)<=2*pre[i])R=mid;
                else L=mid+1;
            }
            while(L>1&&query(L-1,i)<=2*pre[i])L--;
            while(query(L,i)>2*pre[i])L++;
            ans+=T.query(pre[i],i)-T.query(pre[i],L-1);
            T.modify(pre[i],i,1);
        }
        printf("%lld\n",ans);
    }
}
```

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1976D)

比赛代码写成史了。

## $\mathtt{Solution}$

首先考虑反转 $[l,r]$ 可行的一些条件。

为方便思考，定义 `(` 为 $1$，`)` 为 $-1$。

记录原序列的前缀和 $s_i$，一段区间 $[l,r]$ 可行就有了以下条件：

- 不存在 $l\le i\le r$ 使得 $s_i+2s_{l-1}< 0$。也就是说不存在位置 $i$，使得位置 $1\sim i$ 有多余的 `)`。

- $[l,r]$ 中，左右括号的数量相等（显然）。

对于第一个条件，可以维护一颗线段树或者写 ST 表。

对于第二个条件，用一个 `vector` 把 $s_i$ 相同的放在一起处理即可。

参考代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define left rt * 2
#define right rt * 2 + 1
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 5e5 + 5, MR = 2e6 + 5;
int t, n, ans, s[MAXN], s2[MAXN], p[MAXN], cnt[MAXN];
struct Segment_tree{
	int lf[MR], rf[MR], num[MR];
	void push_up(int rt){num[rt] = min(num[left], num[right]);}
	void build(int rt, int l, int r){
		lf[rt] = l, rf[rt] = r;
		if(l == r){
			num[rt] = s2[l];
			return ;
		}
		int mid = l + r >> 1;
		build(left, l, mid);
		build(right, mid + 1, r);
		push_up(rt);
	}
	int query(int rt, int l, int r){
		if(l > rf[rt] || r < lf[rt])return 1e9;
		if(l <= lf[rt] && rf[rt] <= r)return num[rt];
		return min(query(left, l, r), query(right, l, r));
	}
}tr; 
char ch[MAXN];
vector<int>g[MAXN];
signed main(){
	t = read();
	while(t --){
		scanf("%s", ch + 1);
		n = strlen(ch + 1), ans = 0;
		for(int i = 1;i <= 2 * n + 1;i ++)g[i].clear(), cnt[i] = 0;
		s[0] = s2[0] = 0;
		for(int i = 1;i <= n;i ++){
			s[i] = s[i - 1], s2[i] = s2[i - 1];
			if(ch[i] == '(')s[i] ++, s2[i] --;
			else s[i] --, s2[i] ++;
		}
		s[0] = s2[0] = n + 1;
		for(int i = 1;i < n;i ++)s[i] += n + 1, s2[i] += n + 1, g[s[i]].push_back(i), p[i] = ++ cnt[s[i]];
		s[n] += n + 1, s2[n] += n + 1;
		tr.build(1, 1, n);
//		for(int i = 1;i <= n;i ++)printf("%lld %lld\n", s[i], s2[i]);
		for(int i = 1;i <= n;i ++){
			int lpos = i, rpos = n, res = 0, h = s[i - 1] - s2[i - 1];
			while(lpos <= rpos){
				int mid = lpos + rpos >> 1;
				if(tr.query(1, i, mid) + h >= n + 1)res = mid, lpos = mid + 1;
				else rpos = mid - 1;
			}
			if(!res)continue;
			int op = upper_bound(g[s[i - 1]].begin(), g[s[i - 1]].end(), res) - g[s[i - 1]].begin() - 1;
//			printf("%lld %lld %lld %lld\n", i, res, op, ans);
			if(op < 0)continue;
			ans += (p[g[s[i - 1]][op]] - p[i - 1]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 分析

如果一个括号序列是合法的，那么必然满足以下 $2$ 个条件：

在任意一个前缀中 $($ 的数量不小于 $)$ 的数量。

整个序列的 $($ 和 $)$ 数量相等。

现在把 $($ 和 $)$ 分别看作 $1$ 和 $-1$，对序列求一个前缀和，记为 $s_i$。考虑枚举反转区间的左端点 $l$，那么哪些右端点 $r$ 使得将区间 $[l,r]$ 内的括号反转后，整个括号序列仍是合法的？

先满足第 $1$ 个条件。如果反转区间 $[l,r]$，那么前缀会受到影响的位置就是 $k \in \mathbb [l,r]$，下标为 $k$ 的前缀会变成 $s_{l-1}-(s_k-s_{l-1})=2 \cdot s_{l-1}-s_k$。如果第条件 $1$ 要满足，那么对于每个 $k$ 都必须有 $2 \cdot s_{l-1}-s_k \ge 0$，得出 $s_k \le 2 \cdot s_{l-1}$。为此当固定 $l$ 后，可以在区间 $[l,n]$ 内二分出最远且合法的右端点 $r$，写函数的时候需要快速知道某个区间内 $s_i$ 的最大值，这个可以用 RMQ 或线段树来维护。

最后是满足第 $2$ 个条件。现在我们确定了最远的位置 $r$，但并不是所有位于 $[l,r]$ 区间内的下标都适合作为反转区间的右端点。显然反转区间内的 $($ 和 $)$ 的数量必须相同，因此合法的右端点 $k \in \mathbb [l,r]$ 还需要满足 $s_k-s{l-1}=0$。所以我们现在需要统计在 $l \le k \le r$内有多少个位置满足 $s_k=s_{l-1}$，该结果就是以 $l$ 为左端点的合法反转区间数量。只需在预处理 $s_i$ 时开个哈希表存储每个前缀值对应的下标。然后在前缀为 $s_{l-1}$ 的下标中二分出大于等于 $l$ 的最小位置 $x$，以及小于等于 $r$ 的最大位置 $y$，合法的右端点数量就是 $y-x+1$。

## 代码启动

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 2e5 + 5;
char str[N];
int s[N];
int f[18][N];

int query(int l, int r) {
    int t = __lg(r - l + 1);
    return max(f[t][l], f[t][r - (1 << t) + 1]);
}

void find() {
    scanf("%s", str + 1);
    int n = strlen(str + 1);
    map<int, vector<int>> mp;
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + (str[i] == '(' ? 1 : -1);
        mp[s[i]].push_back(i);
    }
    for (int i = 0; 1 << i <= n; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            if (!i) f[i][j] = s[j];
            else f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
        }
    }
    LL ret = 0;
    for (int i = 1; i <= n; i++) {
        int l = i, r = n;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (query(i, mid) <= s[i - 1] << 1) l = mid;
            else r = mid - 1;
        }
        if (query(i, l) <= s[i - 1] << 1) {
            int x = lower_bound(mp[s[i - 1]].begin(), mp[s[i - 1]].end(), i) - mp[s[i - 1]].begin();
            int y = upper_bound(mp[s[i - 1]].begin(), mp[s[i - 1]].end(), l) - mp[s[i - 1]].begin() - 1;
            if (x <= y) ret += y - x + 1;
        }
    }
    printf("%lld\n", ret);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        find();
    }
    
    return 0;
}
```

---

## 作者：gcx114514 (赞：0)

### Sol

首先考虑我们是如何判断一个括号序是否合法的，一般情况下我们可以零左括号为 $1$，右括号为 $-1$，然后求前缀和 $v$ ，如果序列最小值为 $0$ 并且最后一个值也为 $0$，那么这就是一个合法的括号序。

现在我们将字符串全部翻转后的前缀和数组记作 $val$。

对于一个合法括号序，其左括号个数等于其右括号个数，所以如果要翻转一个区间，那么这个区间中的左右括号个数也应该相同。

那么我们考虑枚举翻转区间的起点 $i$ ，假设该区间终点为 $j$ （终点可能很多，这是其中之一），那么一定满足 $v_j-v_{i-1}=0$。由于 $i$ 之前的位置没有被翻转，所以如果翻转 $i$ 它的前缀和还是只会受 $sum_{i-1}$ 的影响，然后再 $j$ 之后的前缀和数组不会受影响，因为我们翻转后这个区间值依然是 $0$。这样我们只用考虑区间 $[l,r]$ 中的前缀和是否满足都大于 $0$。我们可以发现对于翻转区间内的点 $k$ ，得到的 $sum_k=val_k-val_{l-1}+v_{l-1}$ 由于满足 $sum_k\geq0$ 所以有：
$$
val_k-val_{l-1}+v_{l-1}\geq 0\\
\therefore val_k\geq val_{l-1}-v_{l-1}
$$
这样我们可以去找到第一个不满足该条件的位置，由于 $val$ 不满足单调性，我们可以维护一棵线段树支持查询区间最小值，然后二分那个位置，如果 $l$ 到 $mid$ 的区间最小值不满足条件，那么移动 $r$ ，否则移动 $l$。这样我们找到了满足以上条件的区间。

我们可以发现对于所有满足条件的右端点一定在 $i$ 到二分的答案构成的区间内，因为 $j$ 满足 $v_j-v_{i-1}=0$，那么也满足 $val_j-val_{i-1}=0$，所以我们只需要查询区间对于 $val_{i-1}$ 的值的个数，这个可以有主席树解决，然后就没有然后了，因为你已经将它切了。那么时间复杂度是 $O(n\log^2n)$ 的。

还有些细节可以看代码。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e9+10;



inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

int val[Max];
struct Tree{
	int minn;
}tr[Max<<2];

Tree merge(Tree a,Tree b){
	Tree ans;
	if(a.minn<=b.minn) {
		ans=a;
	}else ans=b;
	return ans;
}

void pushup(int now){
	tr[now]=merge(tr[now<<1],tr[now<<1|1]);
}

void build(int now,int l,int r){
	if(l==r){
		tr[now].minn=val[l];
		return;
	}
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
	pushup(now);
}

Tree Query(int now,int l,int r,int L,int R){
	if(L<=l&&R>=r)return tr[now];
	Tree ans;
	ans.minn=INT_MAX;
	int mid=(l+r)>>1;
	if(L<=mid)ans=merge(ans,Query(now<<1,l,mid,L,R));
	if(R>mid)ans=merge(ans,Query(now<<1|1,mid+1,r,L,R));
	return ans;
}


//-----------------------线段树，由于二分缩小区间 

struct tree{
	int ch[2],val;
	#define ch(x,i) t[x].ch[i]
}t[Max<<5];
int tot=0;
int root[Max];


void Modify(int &now,int last,int l,int r,int to){
	now=++tot;
	if(l==r){
		t[now].val=t[last].val+1;
		return;
	}
	t[now]=t[last];
	int mid=(l+r)>>1;
	if(to<=mid)Modify(ch(now,0),ch(last,0),l,mid,to);
	else Modify(ch(now,1),ch(last,1),mid+1,r,to);
}

int Query(int now,int l,int r,int to){
	if(to<0)return 0;
	if(!now)return 0;
	if(l==r)return t[now].val;
	int mid=(l+r)>>1;
	if(to<=mid)return Query(ch(now,0),l,mid,to);
	else return Query(ch(now,1),mid+1,r,to);
}

//-----------------------------主席树，由于查询区间答案 

char c[Max];
int v[Max];
int n;
bool check(int x,int l,int mid){
	Tree ans=Query(1,1,n,l,mid);
	return ans.minn<=x;
}

void work(){
	scanf("%s",c+1);
	n=strlen(c+1);
	int z=INT_MAX;
	for(int i=1;i<=n;++i){
		if(c[i]=='('){
			v[i]=v[i-1]+1;
			val[i]=val[i-1]-1;
		}else{
			v[i]=v[i-1]-1;
			val[i]=val[i-1]+1;
		}
		z=min(z,val[i]);
	}
	if(z<0)z=2-z;
	//整体加，防止主席树跑到负值 
	tot=0;
	for(int i=1;i<=n;++i){
		root[i]=0;
		Modify(root[i],root[i-1],1,z+n,val[i]+z);
	}
	build(1,1,n);
	int Ans=0;
	for(int i=2;i<n;++i){
		int u=val[i-1]-v[i-1];
		int l=i,r=n;
		int ans=n;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(u-1,l,mid)) {                
			//其实对于一次二分，你只需要check(l,mid)区间就行 
				r=mid-1;
				ans=mid;
			}else l=mid+1;
		}
		u=val[i-1];
		Ans+=Query(root[ans],1,z+n,u+z)-Query(root[i-1],1,z+n,u+z);
		//区间求 
	}
	cout << Ans << "\n";
}

signed main(){
	int T=read();
	while(T--)work();

	return 0;
}


```

---

## 作者：Linge_Zzzz (赞：0)

~~纪念一下场切的 *1900（虽然是 vp）。~~

题意不说了。

# Sol

首先对于这种括号题，有一个众所周知的东西是：

设 $cnt_i$ 为括号字符串 $s$ 从 $1$ 到 $i$ 的右括号数量减左括号数量的差，那么 “$s$ 合法” $\Leftrightarrow \forall 1\leq i\leq n,cnt_i\geq 0$。

首先如果一个区间 $[l,r]$ 反转后合法，那么这个区间的左右括号数量一定相等。也就是 $cnt_l=cnt_r$。

其次，若一个区间 $[l,r]$ 反转后合法，那么手玩样例可发现 $cnt_{l-1}\geq\max_{k=l}^r\{cnt_k\}-cnt_{l-1}$。意思就是如果 $cnt_i$ 最大的那个地方都合法，那么其他地方一定合法。变形得 $\max_{k=l}^r\{cnt_k\}\leq 2cnt_{l-1}$。

我们不妨对于每个 $l=1,2,3,\cdots,n$ 考虑有多少个满足要求的 $r$。先对 $cnt_i$ 建一个 RMQ 的东西（我用的线段树），根据 $\max_{k=l}^r\{cnt_k\}\leq 2cnt_{l-1}$ 这个东西二分把 $r$ 的上界算出来。

现在问题就转化为了：在区间 $[l,r]$ 内有多少个 $k$ 满足 $cnt_k=cnt_{l-1}$。

这是个经典问题，但是我脑子抽风没想起来就写了个莫队（反正 $n\leq 2\times 10^5$）。后来才想起来可以 vector 上记录每个数出现的位置然后二分。

# Code

数据结构学傻了是这样的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
char s[N];
int sl[N],sr[N],val[N],cnt[N];
int t[N*4];
void build(int p,int l,int r){
	if(l==r){
		t[p]=cnt[l];
		return;
	}
	int m=(l+r)>>1;
	build(p*2,l,m);
	build(p*2+1,m+1,r);
	t[p]=max(t[p*2],t[p*2+1]);
}
int query(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[p];
	int m=(l+r)>>1,ans=0;
	if(L<=m)ans=max(ans,query(p*2,l,m,L,R));
	if(R>m)ans=max(ans,query(p*2+1,m+1,r,L,R));
	return ans;
}
int b[N],T=sqrt(N);
struct Q{
	int l,r,x;
	bool operator<(Q y){
		if(l/T!=y.l/T)return l<y.l;
		if((l/T)&1)return r<y.r;
		else return r>y.r;
	}
}q[N];
void add(int p){b[cnt[p]]++;}
void del(int p){b[cnt[p]]--;}
void solve(){
	cin>>(s+1);
	int n=strlen(s+1),ans=0;
	for(int i=1;i<=n;i++){
		sl[i]=sr[i]=0;
		if(s[i]=='(')sl[i]=1,cnt[i]=cnt[i-1]+1;
		else sr[i]=1,cnt[i]=cnt[i-1]-1;
		sl[i]+=sl[i-1],sr[i]+=sr[i-1];
	}
	build(1,1,n);
	int c=0;
	for(int i=1;i<=n;i++){
		int l=i,r=n;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(query(1,1,n,i,mid)>2*cnt[i-1])r=mid-1;
			else l=mid;
		}
		c++,q[c].l=i,q[c].r=l,q[c].x=cnt[i-1];
	}
	sort(q+1,q+1+c);
	int l=1,r=0;
	for(int i=1;i<=c;i++){
		while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);
		while(l<q[i].l)del(l++);
		while(r>q[i].r)del(r--);
		ans+=b[q[i].x];
	}
	for(int i=1;i<=n;i++)b[cnt[i]]=0;
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

鉴定为典，~~然后写了巨慢两 $\log$ 做法~~，有点菜了。
### 题意
给定一个合法括号串，定义对一个括号序列的翻转操作为将这个括号序列的所有括号左变右，右变左，求有多少个子段翻转后整体括号串仍匹配。
### 分析
首先括号匹配题，把左括号看成 $+1$，右括号看成 $-1$。

一个合法的翻转区间，必然满足区间和为零。然后要使整体串匹配，即翻转后整体串的所有前缀和 $\geq0$ 即可。因为原串是匹配串，所以只需要考虑在翻转区间内的右端点前缀和 $\geq0$。

我们可以枚举翻转区间的左端点，然后对于一个合法的翻转区间，我们只要求出它的最大前缀和，翻转以后就成为了最小，判断是否合法即可。最大前缀和在枚举了左端点以后显然单调，所以可以二分找出一个最远的合法位置，最大前缀和简单 sgt 即可。

假设枚举到 $i$，最远合法位置为 $pos$，则我们现在要求 $i$ 到 $pos$ 之间，从 $i$ 开始的前缀和为 $0$ 的数量，对原序列前缀和后转化为区间询问 $s_{i-1}$ 的出现次数，由于是静态，简单主席树维护即可。

最后时间复杂度 $O(n\log^2n)$，瓶颈在二分加 sgt。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
int T;
int n;
ll ans;
string a;
int s[maxn];
struct node{int sm,mx;};
struct Segment_Tree{
	node tr[maxn*4];
	node pushup(node x,node y){
		node z;
		z.sm=x.sm+y.sm;
		z.mx=max(x.mx,x.sm+y.mx);
		return z;
	}
	void build(int o,int l,int r){
		if(l==r){
			tr[o].sm=(a[l]=='('?1:-1);
			tr[o].mx=max(tr[o].sm,0);
			return;
		}
		int m=(l+r)/2;
		build(o*2,l,m);
		build(o*2+1,m+1,r);
		tr[o]=pushup(tr[o*2],tr[o*2+1]);
	}
	node query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return tr[o];
		int m=(l+r)/2;
		if(x<=m&&y>m) return pushup(query(o*2,l,m,x,y),query(o*2+1,m+1,r,x,y));
		if(x<=m) return query(o*2,l,m,x,y);
		return query(o*2+1,m+1,r,x,y);
	}
}seg;
struct HJT_Segment_Tree{
	struct{int ls,rs;int cnt;}tr[maxn<<5];
	int rt[maxn],tot;
	void clear(){
		for(int i=1;i<=n;i++) rt[i]=0;
		for(int i=1;i<=tot;i++) tr[i]={0,0,0};
		tot=0;
	}
	void update(int &o,int p,int l,int r,int x){
		o=++tot;tr[o]=tr[p];
		if(l==r){
			tr[o].cnt++;
			return;
		}
		int m=(l+r)/2;
		if(x<=m) update(tr[o].ls,tr[p].ls,l,m,x);
		else update(tr[o].rs,tr[p].rs,m+1,r,x);
	}
	int query(int o,int l,int r,int x){
		if(!o) return 0;
		if(l==r) return tr[o].cnt;
		int m=(l+r)/2;
		if(x<=m) return query(tr[o].ls,l,m,x);
		else return query(tr[o].rs,m+1,r,x);
	}
	int getsum(int l,int r,int k){
		return query(rt[r],0,n,k)-query(rt[l-1],0,n,k);
	}
}hjt;
signed main(){
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		cin>>a;n=a.size();a=' '+a;
		for(int i=1;i<=n;i++) s[i]=s[i-1]+(a[i]=='('?1:-1);
		hjt.clear();
		for(int i=1;i<=n;i++) hjt.update(hjt.rt[i],hjt.rt[i-1],0,n,s[i]);
		seg.build(1,1,n);ans=0;
		for(int i=1,pre=0;i<=n;i++){
			int l=i,r=n,pos=i-1;
			while(l<=r){
				int m=(l+r)/2;
				if(seg.query(1,1,n,i,m).mx<=pre){
					pos=m;
					l=m+1;
				}else{
					r=m-1;
				}
			}
			ans+=hjt.getsum(i,pos,s[i-1]);
			pre+=(a[i]=='('?1:-1);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

