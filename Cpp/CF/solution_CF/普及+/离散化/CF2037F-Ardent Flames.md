# Ardent Flames

## 题目描述

You have obtained the new limited event character Xilonen. You decide to use her in combat.

There are $ n $ enemies in a line. The $ i $ 'th enemy from the left has health $ h_i $ and is currently at position $ x_i $ . Xilonen has an attack damage of $ m $ , and you are ready to defeat the enemies with her.

Xilonen has a powerful "ground stomp" attack. Before you perform any attacks, you select an integer $ p $ and position Xilonen there ( $ p $ can be any integer position, including a position with an enemy currently). Afterwards, for each attack, she deals $ m $ damage to an enemy at position $ p $ (if there are any), $ m-1 $ damage to enemies at positions $ p-1 $ and $ p+1 $ , $ m-2 $ damage to enemies at positions $ p-2 $ and $ p+2 $ , and so on. Enemies that are at least a distance of $ m $ away from Xilonen take no damage from attacks.

Formally, if there is an enemy at position $ x $ , she will deal $ \max(0,m - |p - x|) $ damage to that enemy each hit. Note that you may not choose a different $ p $ for different attacks.

Over all possible $ p $ , output the minimum number of attacks Xilonen must perform to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead. Note that an enemy is considered to be defeated if its health reaches $ 0 $ or below.

## 说明/提示

In the first testcase, it is optimal to select $ p=2 $ . Each attack, the first enemy takes $ 5-|2-1|=4 $ damage, the second enemy takes $ 5 $ damage, the third enemy takes $ 4 $ damage, the fourth enemy takes $ 3 $ damage, and the fifth enemy takes $ 2 $ damage. After $ 2 $ attacks, the first three enemies will be defeated. It can be shown that it is impossible to defeat $ 3 $ enemies in less than $ 2 $ attacks, no matter which $ p $ is selected.

In the second testcase, we must kill all $ 9 $ enemies. By selecting $ p=5 $ , all nine enemies will be defeated in $ 2 $ attacks.

In the third testcase, we must kill both enemies. However, it can be shown that no $ p $ selected will damage both enemies at the same time, so the answer is $ -1 $ .

In the fourth testcase, selecting $ p=1 $ will enable us to defeat the first enemy in $ 6969697 $ attacks.

In the fifth testcase, selecting $ p=10 $ will make each enemy take $ 1 $ damage per attack. Both enemies will be defeated in $ 15 $ attacks.

## 样例 #1

### 输入

```
6
5 5 3
7 7 7 7 7
1 2 3 4 5
9 5 9
2 4 6 8 10 8 6 4 2
1 2 3 4 5 6 7 8 9
2 10 2
1 1
1 20
2 10 1
69696969 420420420
1 20
2 10 2
10 15
1 19
2 2 2
1000000000 1
1 3```

### 输出

```
2
2
-1
6969697
15
1000000000```

# 题解

## 作者：1234567890sjx (赞：3)

如你所见，这是一道 diff 为 $2100$ 的题目，看上去十分困难。

你十分惊慌，恐怕这道题你根本就无法做出来，马上就要面临着再次 rating $-145$，甚至 FST 后获得 $-233$ 的到来。

你冷静地思考了一会，发现这是你最擅长的二分题目，你逐渐有了一些自信。

你发现如果二分到一个长度 $p$，则可以对于每一个怪物 $i$，计算出在 $k$ 次攻击后，她可以去世的区间 $[x_i-m+\lceil\frac{h_i}{p}\rceil,x_i+m-\lceil\frac{h_i}{p}\rceil]$。

前面这一步可以直接套公式快速解决，但是该如何快速判断是否存在一个位置可以杀害至少 $k$ 个怪物，即覆盖至少 $k$ 个区间？

在耀眼的光芒中，你看见了可爱班花 yhb，她只给了你三个汉字“扫描线”，让你自己领会。

在艰难的探索中，你终于发现，对于每一个区间 $[l,r]$，都可以将其拆分为 $(l,1)$ 和 $(r+1,-1)$ 两个二元组，将其按照左端点从小到大排序之后扫描，对第二维做前缀和，若某一时刻其前缀和的值 $\ge k$，则符合条件，否则不符合条件。

你非常高兴，很快就打出了一份代码，它十分的正确，仅一遍就通过了样例，并获得了一个绿色的 Accepted。

```cpp
namespace ttq012 {
 
int h[N], x[N];
void run() {
    int T = read();
    while (T--) {
        int n = read(), m = read(), k = read();
        for (int i = 1; i <= n; ++i) {
            h[i] = read();
        }
        for (int i = 1; i <= n; ++i) {
            x[i] = read();
        }
        int l = 1, r = inf, best = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            vector<pair<int, int>> event;
            for (int i = 1; i <= n; ++i) {
                int pwk = (h[i] + mid - 1) / mid;
                if (pwk <= m) {
                    int L = x[i] - (m - pwk), R = x[i] + (m - pwk);
                    event.eb(L, 1), event.eb(R + 1, -1);
                }
            }
            sort(event.begin(), event.end(), [&](auto l, auto r) {
                return l.first < r.first || l.first == r.first && l.second < r.second;
            }) ;
            int pref = 0, ok = 0;
            for (auto &[pos, vx] : event) {
                if ((pref += vx) >= k) {
                    ok = 1;
                    break;
                }
            }
            if (ok) {
                best = mid, r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << best << '\n';
    }
} }
```

正在你看到你 AK 了本场比赛，获得 rk 前 $10$ 的时候，你醒了。原来你昨天晚上打比赛写 G 线性筛忘记更新质数列表调不出来，趴在桌子上睡着了。你不但没有切掉 G，甚至 F 题更是被榜带偏根本没看，注定只能获得负数 Delta。

[文案来源](https://www.luogu.com.cn/article/e2plnt1n)

---

## 作者：postpone (赞：0)

对于一个怪，每次攻击的伤害是（固定的）强度 $m$ 减去你和它的距离。那么如果要击败一个怪，需要站的位置肯定是它周围的一段区间。

也就是说，至少击败 $k$ 个怪，即站的位置要至少被 $k$ 个区间包含。

二分攻击次数就行了。怎么判断能不能被 $k$ 个区间包含，可以化成扫描线问题，扫一遍每个端点，过程中维护左端点和右端点的差 $s$，若 $s\geq k$ 就可行。

复杂度 $O(n\log n\log V)$，其中 $V = 10^9$。

```cpp
constexpr int inf = 1e9;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> h(n), x(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    auto check = [&](int c) {
        vector<array<int, 2>> e;
        for (int i = 0; i < n; i++) {
            if (1ll * m * c < h[i]) {
                continue;
            }
            int d = (h[i] + c - 1) / c;
            int l = x[i] - m + d;
            int r = x[i] + m - d;
            e.push_back({l, 1});
            e.push_back({r + 1, -1});
        }
        ranges::sort(e);
        int s{};
        for (auto [_, i] : e) {
            s += i;
            if (s >= k) {
                return true;
            }
        }
        return false;
    };

    int lo = 0, hi = inf + 1;
    while (lo < hi) {
        int mi = (lo + hi) / 2;
        if (check(mi)) {
            hi = mi;
        } else {
            lo = mi + 1;
        }
    }
    cout << (lo > inf ? -1 : lo) << "\n";
}
```

---

## 作者：KaruAWA (赞：0)

观察到题目要求求出“最小的攻击次数”，而对于攻击次数而言是否合法一定具有单调性，因此可以想到二分。

令现在二分求到的最小攻击次数为 $at$，对于第 $i$ 个原魔，它会被攻击至死的充要条件是 $at\times \max(0,m-|p-x_i|)\ge h_i$，假设这个原魔一定会被攻击到（没被攻击到很没意义啊），再化简一下式子得到：$|p-x_i|\le m-\lceil\frac{h_i}{at}\rceil$。再次进行观察，发现不等式右边是 $p$ 到 $x_i$ 的距离，设 $len=m-\lceil\frac{h_i}{at}\rceil$，那么这个式子可以抽象成 $p$ 一定要在 $[x-len,y+len]$ 这个区间内才合法。

于是判断 $at$ 是否可行的问题可以转化为，给出若干个线段，问是否存在至少被 $k$ 条线段覆盖的点。这个差分一下就行。

感觉难点大概在转化成区间问题？

code：

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+15;
int n,m,k,K;
int h[N],p[N];
int b[N<<1];
int ch[N<<1];
int cnt;

struct node{
    int l,r;
}a[N];

void clear(){
    for(int i=0;i<=n+5;++i) a[i].l=a[i].r=0;
    for(int i=0;i<=cnt+5;++i) b[i]=0;
    for(int i=0;i<=K+5;++i) ch[i]=0;
    cnt=K=0;
}

bool check(int at){
    for(int i=1;i<=n;++i){
        ll tmp=1ll*h[i]/at;
        if(h[i]%at) tmp++;
        int len=m-tmp;
        if(len<0) continue;
        a[i].l=max(1,p[i]-len);
        a[i].r=p[i]+len;
        b[++cnt]=a[i].l,b[++cnt]=a[i].r;
    }
    sort(b+1,b+cnt+1);
    K=unique(b+1,b+cnt+1)-b-1;

    for(int i=1;i<=n;++i){
        if(!a[i].l&&!a[i].r) continue;
        a[i].l=lower_bound(b+1,b+K+1,a[i].l)-b;
        a[i].r=lower_bound(b+1,b+K+1,a[i].r)-b;
        ch[a[i].l]++;
        ch[a[i].r+1]--;
    }

    for(int i=1;i<=K;++i){
        ch[i]+=ch[i-1];
        if(ch[i]>=k){
            clear();
            return true;
        }
    }
    clear();
    return false;
}

void solve(){
    cin>>n>>m>>k;
    int lt=1,rt=0;
    for(int i=1;i<=n;++i){
        cin>>h[i];
        rt=max(rt,h[i]);
    }
    for(int i=1;i<=n;++i) cin>>p[i];

    int maxh=rt;
    lt--,rt++;
    while(lt+1<rt){
        int mid=(lt+rt)>>1;
        if(check(mid)) rt=mid;
        else lt=mid;
    }
    if(rt==maxh+1) cout<<"-1\n";
    else cout<<rt<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
/*
题意：
定义攻击方式为选择一个位置 p，并对怪物进行单次 max(0,m-|p-x|) 的伤害，可以进行多次攻击但位置无法改变。
求最小满足击败至少 k 个敌人的攻击次数。
二分攻击次数
有式子 |p-x|<=m-(h[i]/at)
那么将每个怪物抽象成以 x 为中心，长度为 2*(m-(h[i]/at)) 的区间
*/
~~~

---

## 作者：__vector__ (赞：0)

### 题意
有 $n$ 个编号为 $1$ 到 $n$ 的奶龙在 $x$ 坐标轴上，第 $i$ 个奶龙的生命值为 $h_i$，横坐标为 $x_i$，保证奶龙们的横坐标按照其编号升序。    

你可以预先选定一个横坐标 $p$，并发动任意次数强度为 $m$ 的攻击。  

每次攻击后，第 $i$ 个奶龙受到 $\max(0,m-|p-x_i|)$ 的伤害，当奶龙的生命值降到 $0$ 及以下，这个怪物就被击败了。注意 $p$ 在攻击前选定，且选定之后不能改变。    

给定整数 $n,m,h_i,x_i,k$，求如何选择 $p$，使得能在最少的攻击次数内击杀至少 $k$ 个奶龙。  

只需要求出最少的攻击次数。

### 做法  
显然答案具有单调性，可以二分答案，设当前二分的答案为 $l$。  

考虑如何快速检查合法性。  

注意到，此时需要判断是否存在一个坐标，使得其能击败至少 $k$ 个奶龙。  

考虑求出每个奶龙可以被打败的 $p$ 区间。  

对于第 $i$ 个奶龙，打败它需要保证 $l\cdot(m-|p-x_i|) \ge h_i$。

得出 $m-|p-x_i| \ge \frac{h_i}{l}$。   

即 $-|p-x_i| \ge \lceil \frac{h_i}{l} \rceil+m$。 

$|p-x_i| \le m-\lceil \frac{h_i}{l} \rceil $。  

也就是说，第 $i$ 个奶龙会被打败当且仅当选定的坐标 $p$ 与这个奶龙距离不能超过 $m-\lceil \frac{h_i}{l} \rceil$。  

计算出每个奶龙会被打败的 $p$ 区间，看下是否存在一个点被大于等于 $k$ 个区间覆盖就可以解决。此部分可以离散化再差分。

---

## 作者：AtomAlpaca (赞：0)

## 题面
[link](https://www.luogu.com.cn/problem/CF2037F)

Too long, didn't translate

## 题解

不懂咋 *2100 的。

考虑二分答案 $t$，那么对于每个怪物 $i$ 需要每次至少造成 $\lceil \frac{h_i}{t} \rceil$，那么所在的位置必须在 $[x_i - (m - \lceil \frac{h_i}{t} \rceil), x_i + (m - \lceil \frac{h_i}{t} \rceil)]$ 这个区间里面，于是我们只需要判定是否存在一个点被至少 $k$ 个线段覆盖。

然后我们对所有区间 $[l, r]$，把 $l$ 放进一个队列 $q_+$，$r + 1$ 放进另一个队列 $q_-$，然后把这两个队列排序，每次取出较小的那个并对应加减，如果当前值大于等于 $k$ 说明存在被 $k$ 个线段覆盖的点。

$O(n \log n \log V)$，$V$ 是答案的上界。

## 代码

```c++
#include <bits/stdc++.h>
#include <cstdio>

const int MAX = 1e5 + 5;
typedef long long ll;

const ll INF = 1e9 + 7;
int T;
ll h[MAX], x[MAX];
ll n, k, m;

bool check(ll t)
{
    std::deque <int> p, q; ll cnt = 0, mx = 0;
    for (int i = 1; i <= n; ++i)
    {
        ll dmg = (ll)std::ceil(1.0 * h[i] / t);
        if (dmg > m) { continue; }
        ll len = m - dmg;
        p.push_back(x[i] - len); q.push_back(x[i] + len + 1);
    }
    std::sort(p.begin(), p.end()); std::sort(q.begin(), q.end());
    while (!p.empty() and !q.empty())
    {
        if (p.front() == q.front()) { p.pop_front(); q.pop_front(); }
        else if (p.front() < q.front()) { p.pop_front(); ++cnt; }
        else { q.pop_front(); --cnt; }
        mx = std::max(mx, cnt);
    }
    while (!p.empty()) { p.pop_front(); ++cnt; mx = std::max(mx, cnt); }
    while (!q.empty()) { q.pop_front(); --cnt; }
    return mx >= k;
}


void solve()
{
    scanf("%lld%lld%lld", &n, &m, &k);
    for (int i = 1; i <= n; ++i) { scanf("%lld", &h[i]); }
    for (int i = 1; i <= n; ++i) { scanf("%lld", &x[i]); }
    ll ans = INF; ll l = 1, r = INF;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (check(mid)) { ans = mid; r = mid - 1; }
        else { l = mid + 1; }
    }
    if (ans == INF) { printf("-1\n"); }
    else { printf("%lld\n", ans); }

}

int main()
{
    scanf("%d", &T); while (T--) { solve(); }
}
```

---

## 作者：zhouruoheng (赞：0)

二分答案，设攻击了 $k$ 次。  

因为只能是在同一个位置 $p$ 攻击，所以第 $i$ 个敌人每次攻击需要受到至少 $t_i=\lceil\frac{h_i}{k}\rceil$ 的伤害，因此 $p$ 的范围就是 $[x_i-(m-t[i]),x_i+(m-t[i])]$，若 $m < t_i$ 则一定无法击败第 $i$ 个敌人。

这样就转化成了 $n$ 个区间的覆盖问题，问是否有一个点被覆盖了至少 $k$ 次。

离散化加差分轻松搞定，复杂度为 $O(n\log(n)\log(V))$。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=2e5+5,inf=1e9;
int n,m,k;
int h[N],x[N],t[N];
int tot;
int b[N],c[N];
bool check(int k)
{
    tot=0;
    for(int i=1;i<=n;i++) 
    {
        t[i]=(h[i]+k-1)/k;
        if(t[i]<=m) 
        {
            c[++tot]=x[i]-(m-t[i]);
            c[++tot]=x[i]+(m-t[i])+1;
        }
    }
    sort(c+1,c+tot+1);
    tot=unique(c+1,c+tot+1)-c-1;
    for(int i=1;i<=tot;i++) b[i]=0;
    for(int i=1;i<=n;i++)
    {
        if(t[i]<=m)
        {
            int l=lower_bound(c+1,c+tot+1,x[i]-(m-t[i]))-c;
            int r=lower_bound(c+1,c+tot+1,x[i]+(m-t[i])+1)-c;
            b[l]++,b[r]--;
        }
    }
    for(int i=1;i<=tot;i++) b[i]+=b[i-1];
    for(int i=1;i<=tot;i++) if(b[i]>=k) return 1;
    return 0;
}
void solve()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>h[i];
    for(int i=1;i<=n;i++) cin>>x[i];
    int l=1,r=inf,mid,ans=-1;    
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans<<'\n';
}
int main ()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}

```

---

## 作者：Iniaugoty (赞：0)

### CF2037F Ardent Flames

二分求出最小的 $q$，使得存在一个位置 $p$，攻击 $q$ 次能干掉 $k$ 个怪。

设 $p$ 距离一个怪 $(h, x)$ 为 $d$，能干掉意味着 $q (m - d) \ge h$，可得 $d \le m - \lceil \frac h q \rceil$，所以 $p \in [x - d _ {\max}, x + d _ {\max}]$。我们将能干掉 $(h, x)$ 的位置限定在了一个区间内。

坐标离散化后差分，对所有 $[x - d _ {\max}, x + d _ {\max}]$ 打标记。那么 $p$ 能干掉 $k$ 个怪，当且仅当 $p$ 上的标记不少于 $k$ 个。

做完了，时间复杂度 $O(n \log ^ 2 n)$，[code](https://codeforces.com/contest/2037/submission/292001923)。

---

## 作者：Melo_DDD (赞：0)

怎么比 E 简单啊。

最小次数可以二分是显然的，考虑怎么 check。我们发现 $p$ 是固定的，那么问题应该很好解决了。

  我们设当前二分的攻击次数是 $q$，那么如果一个怪物需要被击杀，那么我们单次造成的伤害至少是 $y=\lceil\frac{h_i}{q}\rceil$ 的，如果 $y>m$ 它显然不可能被击杀，否则可以。可以发现如果在位置 $p$ 攻击 $q$ 次可以击杀怪物 $i$ 的话，那么 $p\in[x_i-(m-y),x_i+(m-y)]$。

现在我们的问题转化为：每一个怪物对应着一个区间，表示这个区间内的点可以击杀他，那么我们的目标就是找到一个点，它至少被 $k$ 个区间覆盖。

接下来就是~~一个典型的 DS 题了~~。这显然是一个古典的可以线性扫一遍完事的问题，对于每个区间，我们给它的左端点打上权值 $1$，右端点加 $1$ 的地方打上权值 $-1$。开一个变量，循环一遍，每次加上当前位置的权值，就可以正确维护这个点被几个区间覆盖了。

简单解释一下，如果权值是 $1$，说明进入了一个区间，覆盖数增加；如果是 $-1$，说明刚刚走出了一个区间，覆盖数减少；如果是 $0$，说明这个点肯定不是端点，那么覆盖数与前一个位置无二，所以没有变化。

就看这个变量有没有不小于 $k$ 的时刻即可。

Code：


```cpp
#include <bits/stdc++.h>
#define mid (l + r >> 1)
#define f(i ,m ,n ,x) for (int i = (m) ; i <= (n) ; i += (x))
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ; char ch = getchar () ;
	while (! isdigit (ch)) 
	{ flag = ch == '-' ; ch = getchar () ;}
	while (isdigit (ch))
	{ x = (x << 1) + (x << 3) + (ch ^ 48) ; ch = getchar () ;}
	flag ? x = - x : 0 ;
}
template < typename T , typename ...Args >
inline void read ( T &x , Args &...tmp ) { read (x) , read (tmp...) ;}
using ll = long long ; const int N = 1e5 + 7 ;
int t ,n ,m ,k ; ll x[N] ,h[N] ;
std :: vector < std :: pair < ll ,ll > > v ;  
inline ll ceil (ll x ,ll y) { return x % y ? x / y + 1ll : x / y ;}
inline bool check (ll cur) {
	v.clear () ;
	f (i ,1 ,n ,1) {
		ll val = ceil (h[i] ,cur) ;
		if (val <= m) {
			v.emplace_back (std :: make_pair (x[i] - (m - val) ,1)) ;
			v.emplace_back (std :: make_pair (x[i] + (m - val) + 1 ,- 1)) ; 
		}
	}
	std :: sort (v.begin () , v.end ()) ;
	std :: vector < std :: pair < ll ,ll > > :: iterator it ;
	static int tot ; tot = 0ll ;
	for (it = v.begin () ; it != v.end () ; it ++) {
		tot += it -> second ;
		if (tot >= k) return true ;
	}
	return false ;
} 
int main () {
	read (t) ;
	while (t --) {
		read (n ,m ,k) ;
		f (i ,1 ,n ,1) read (h[i]) ;
		f (i ,1 ,n ,1) read (x[i]) ;
		ll l = 1ll , r = (ll) 1e9 , ans = 0ll ;
		while (l <= r) {
			if (check (mid)) r = (ans = mid) - 1 ;
			else l = mid + 1 ;
		}
		if (ans == 0) { puts ("-1") ; continue ;}
		else std :: cout << ans << '\n' ;
	}
	return 0 ;
}
```

---

