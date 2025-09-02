# Yet Another Real Number Problem

## 题目描述

# 又一个实数问题


Three r there are's in strawberry.

（“strawberry”中有三个“r”）


给定一个长度为 $m$ 的数组 $b$ 。你可以进行以下操作任意次（可能为零次）：

- 选择两个不同的下标 $i$ 和 $j$ ，其中 $\bf{1\le i<j\le m}$ 且 $b_i$ 是偶数，将 $b_i$ 除以 $2$ ，并将 $b_j$ 乘以 $2$ 。

你的任务是通过任意次数的操作来最大化数组的和。因为结果可能会非常大，你需要输出该和对 $10^9+7$ 取模的结果。

由于这个问题太简单了，所以现在你被给定了一个长度为 $n$ 的数组 $a$，需要针对数组 $a$ 的每个前缀来求解该问题。

换句话说，记经过任意次数操作后 $ b $ 的最大和为 $f(b)$ ，你需要分别输出 $f([a_1])$ , $f([a_1,a_2])$ , $\ldots$ , $f([a_1,a_2,\ldots,a_n])$ 对 $10^9+7$ 取模的结果。

## 说明/提示

对于第一个测试用例中的每个前缀数组，操作后可能是：

- $[1]$ 和为 $1$ 
- $[1,2]$ 和为 $3$ 
- $[1,1,6]$ 和为 $8$ 
- $[1,1,3,8]$ 和为 $13$ 
- $[1,1,3,1,40]$ 和为 $46$ 
- $[1,1,3,1,5,48]$ 和为 $59$ 
- $[1,1,3,1,5,3,112]$ 和为 $126$ 
- $[1,1,3,1,5,3,7,128]$ 和为 $149$ 
- $[1,1,3,1,5,3,7,1,1152]$ 和为 $1174$
- $[1,1,3,1,5,3,7,1,9,1280]$ 和为 $ 1311 $​

## 样例 #1

### 输入

```
3
10
1 2 3 4 5 6 7 8 9 10
11
1 6 9 4 7 4 4 10 3 2 3
4
527792568 502211460 850237282 374773208```

### 输出

```
1 3 8 13 46 59 126 149 1174 1311 
1 7 22 26 70 74 150 1303 1306 1308 1568 
527792568 83665723 399119771 773892979```

# 题解

## 作者：Lucky_Cloud (赞：6)

[更好的阅读体验](https://lucky-cloud09.github.io/2024/10/28/CF2035D/)。

[传](https://www.luogu.com.cn/problem/CF2035D)。

我们考虑不限定 $i < j$ 的情况怎么做。很容易想到，$a_i = b_i \times 2^{c_i}$，$b_i$ 是奇数。我们找到 $b_i$ 最大的一个，并将所有的 $2$ 乘上它然后求和。可以证明，这样是最优的。

我们回到原题意。可以发现逆序去做是较为简单的。假设 $> i$ 的 $a$ 都已经操作过了，我们就可以将 $a_j$ 看做类似于 $b_j$ 的东西。虽然 $a_j$ 可以为偶数。然后与 $i$ 的 $b_i$ 对比。

具体的，找到操作后最大 $j > i$ 的 $a_j$。与 $b_i$ 比较，若 $a_j$ 大，则将 $2^{c_i}$ 给 $a_j$，否则不变。想一下可以发现他是对的。

题目要求求 $a$ 每个前缀的答案。

我们考虑使用单调栈，从前往后维护。

具体，每个元素存两个值，$b$ 与 $c$。考虑栈顶元素的值为 $b_1,c_1$，当前的值为 $b_2,c_2$。

按照上面的性质，$b_1 \le b_2 \times 2^{c_2}$ 就将栈顶弹出，并且 $c_2$ 赋值为 $c_2 + c_1$，$c_1$ 赋为 $0$，然后维护答案。

实现看代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, a[N], top, pw[N << 5];
struct node {
    int tw, d; // tw 是上文的 c，d 是上文的 b
} st[N];

bool cmp(node a, node b) {
    if (b.tw <= 31) return a.d <= b.d * pw[b.tw];// 因为 a.d <= 2^31
    return 1;
}
int val(node x) { return pw[x.tw] * x.d % mod; }

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int ans = 0;
    top = 0;
    for (int i = 1; i <= n; ++i) {
        int d = a[i], tw = 0;
        while (d % 2 == 0) tw++, d >>= 1;
        node nw = {tw, d};
        while (top && cmp(st[top], nw)) {
            ans = ((ans - val(st[top]) + mod) % mod + st[top].d) % mod;
            nw.tw += st[top].tw;
            --top;
        }
        st[++top] = nw;
        ans = (ans + val(nw)) % mod;
        cout << ans << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    pw[0] = 1;
    for (int i = 1; i <= N * 31 + 5; ++i) pw[i] = pw[i - 1] * 2 % mod;
    cin >> T;
    while (T--) solve();
    return 0;
}
```

---

## 作者：MightZero (赞：3)

### Solution

题目给出的操作本质是将因数 $2$ 向后转移，观察样例可知最优的方案必然是把因数 $2$ 尽量叠加到较大的数上。下文称这样的位置为**决策点**，称一个位置的取值为将**所有可行**的因数 $2$ 全部叠加到该位置后的值；但是由于转移是单向的，若某个新加入的数的取值比先前决策点的对应的取值小，其因数 $2$ 无法转移到先前的决策点上。因此最终的方案必然包含若干个决策点，注意到这些决策点的取值必然是单调下降的，否则可以合并部分决策点，因此可以用单调队列维护决策点。

考虑如何判断两个决策点的取值的大小：设 $p_i$ 表示从 $a_1$ 到 $a_i$ 中所有因数 $2$ 的数量；若如果决策点 $j$ 的取值大于 $i$，则满足 $a_i\times 2^{p_{i-1}}<a_j\times 2^{p_{j-1}}$；由于涉及到的数可能很大，可以转化为判断 $\log_2{a_i}+p_{i-1}<\log_2{a_j}+p_{j-1}$；具体实现请看代码。

### Code

```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x%10==x){putchar(x+'0');return;}
    write(x/10);putchar(x%10+'0');
}
const ll N=2e5+5,mod=1e9+7;
ll n,a[N],b[N],p[N],ans;
deque<pll> q;
ll mpw(ll a,ll x)
{
    ll res=1,tmp=a;
    while(x)
    {
        if(x&1)res=res*tmp%mod;
        tmp=tmp*tmp%mod,x>>=1;
    }
    return res;
}
void solve()
{
    n=read(),ans=0;
    q.clear();
    loop(i,1,n)p[i]=b[i]=a[i]=0;
    loop(i,1,n)
    {
        a[i]=b[i]=read();
        ll pt=0;
        while(!(b[i]&1))b[i]>>=1,pt++;
        p[i]=p[i-1]+pt;
        while(q.size()&&log2(a[i])+p[i-1]>=log2(a[q.back().first])+p[q.back().first-1])
        {
            auto [x,y]=q.back();q.pop_back();
            ans=(ans+mod-(mpw(2,y)-1)*b[x]%mod)%mod;
            pt+=y;
        }
        q.push_back({i,pt});
        ans=(ans+(mpw(2,pt))*b[i]%mod)%mod;
        printf("%lld ",ans);
    }
    puts("");
}
signed main()
{
    ll T=read();
    while(T--)solve();
    return 0;
}
```

---

## 作者：六楼溜刘 (赞：1)

# CF2035D Yet Another Real Number Problem

[传送门](https://www.luogu.com.cn/problem/CF2035D)

## 题意

- 对于一个长度为 $m$ 的数组 $b$，你可以执行以下操作任意多次：
    - 选择 $1\le i < j\le m$，满足 $b_i$ 是偶数，将 $b_i\gets \frac{b_i}{2},b_j\gets 2\times b_j$。
- 设 $f(b)$ 表示进行任意次这个操作后数组总和的最大值。
- 现在给定数组 $a$，对于 $a$ 的所有非空前缀 $b$，求出 $f(b)$。
- $1\le n\le 2\times 10^5,1\le a_i\le 10^9$。输出答案对 $10^9+7$ 取模的值。

## 题解

贪心。

考虑静态问题，有一个简单的贪心：从右到左扫，每次把所有 $2$ 因子乘到右侧最大的数里面。正确性显然。

那么动态问题怎么做呢？容易发现经过上面的贪心后，剩下的所有带 $2$ 因子的数必定是单调递减的，于是我们对**带有 $2$ 因子的数**维护一个单调栈从底到顶单调递减，每次遇到新数就考虑将栈顶的所有 $2$ 因子乘到这个数内总和是否会变大。

考虑合并的过程是否正确，容易发现我们将 $x2^p$ 合并到 $y2^{q}$ 上当且仅当 $y2^q\ge x$。那么若两数都在栈内，必定满足 $y2^p < x$，此时假如我们加入了一个数 $z2^{w} < y$，那么它就算乘上 $2^p$ 也还是小于 $x$，不能往前合并，所以我们每次只需要考虑当前的栈顶然后即可，具体见代码。

复杂度 $O(n\log V)$，瓶颈在预处理 $2^p$ 要预处理到 $O(n\log V)$ 级别。

## code

```cpp
#include<bits/stdc++.h>
#define forup(i,s,e) for(int i=(s),E123123123=(e);i<=E123123123;++i)
#define fordown(i,s,e) for(int i=(s),E123123123=(e);i>=E123123123;--i)
#define mem(a,b) memset(a,b,sizeof(a))
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void();
#endif
using namespace std;
using i64=long long;
using pii=pair<int,int>;
#define fi first
#define se second
#define mkp make_pair
#define gc getchar()
int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=2e5+5,inf=0x3f3f3f3f,mod=1e9+7;
int t,n,a[N],c[N],p2[N*30];
bool cmp(int x,int y){
    if(c[x]>=30) return true;
    return ((1ll*a[x])<<c[x])>=a[y];
}
void solve(){
    n=read();
    forup(i,1,n){
        a[i]=read();
        c[i]=__builtin_ctz(a[i]);
        a[i]>>=c[i];
    }
    a[0]=c[0]=0;
    int ans=0;
    stack<int> stk;
    forup(i,1,n){
        while(stk.size()&&cmp(i,stk.top())){
            int p=stk.top();stk.pop();
            ans=(ans+mod-1ll*a[p]*p2[c[p]]%mod)%mod;
            ans=(ans+a[p])%mod;
            c[i]+=c[p];c[p]=0;
        }
        ans=(ans+1ll*a[i]*p2[c[i]]%mod)%mod;
        if(c[i]){
            stk.push(i);
        }
        printf("%d ",ans);
    }
    puts("");
}
signed main(){
    int t=read();
    p2[0]=1;
    forup(i,1,6e6){
        p2[i]=2ll*p2[i-1]%mod;
    }
    while(t--){
        solve();
    }
}
```

---

## 作者：lhz2022 (赞：0)

作业题。

首先观察题目：

给定一个长度为 $m$ 的数组 $b$。你可以进行以下操作任意次（可能为零次）：

- 选择两个不同的下标 $i$ 和 $j$，其中 $\bf{1\le i<j\le m}$ 且 $b_i$ 是偶数，将 $b_i$ 除以 $2$，并将 $b_j$ 乘以 $2$。

- 你的任务是通过任意次数的操作来最大化数组的和。因为结果可能会非常大，你需要输出该和对 $10^9+7$ 取模的结果。

- 由于这个问题太简单了，所以现在你被给定了一个长度为 $n$ 的数组 $a$，需要针对数组 $a$ 的每个前缀来求解该问题。

简单来说，我们可以进行的操作是把前面的数的 $2$ 的乘方转移到后面的数，求数组和的最大值。

首先，我们需要求得每一个前缀的答案，所以我们猜测我们可以通过某种方式从前 $i$ 个数中的答案推导出前 $i+1$ 个数中的答案。

其次，我们发现，最优的方案是尽量对一个较后面的，除去 $2$ 的因数之后最大的数进行操作。

那么我们的目标就很明确了，维护一个单调栈，栈内如果能往后操作更优就往后操作。

最后就是比较大小的问题了。因为我们只会比较新加入的元素和栈内的元素，我们记新元素为 $u$，当前栈顶为 $v\times2^k$，则如果 $v<u$ 那么就直接把所有 $2$ 的乘方转移到后者。

[代码](https://www.luogu.com.cn/paste/49k82e8z)

---

## 作者：limingyuan333 (赞：0)

# Yet Another Real Number Problem 

题意：在一个数列中，可以将前面的某个数除以二，将后面的某个数乘以二。求一个数列的最大值。

分析：最优的方式一定是将最大的数乘以二，所以维护一个最大值，可以用单调栈的形式来记录。具体的，我们可以先把每个数最多可以拆出多少个二给别人预处理一下，然后先把答案算上不操作的值，然后当当前位置比现在使用的收益大，就把其踢出，把自己权值加上。


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
const int mod=1e9+7;
int T,n,a[MAXN],b[MAXN];
int ksm(int a,int b){
	int num=1;
	while(b){
		if(b&1)	(num*=a)%=mod;
		(a*=a)%=mod,b>>=1;
	}
	return num%mod;
}
int get(int a,int b){
	while(b){
		a<<=1;
		if(a>1e9)	return 1e9;//大于就不用算了 
		b--;
	}
	return a;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>a[i],b[i]=0;
		for(int i=1;i<=n;i++){
			while(1){
				if(a[i]&1)	break;
				a[i]>>=1;b[i]++;
			}//计算每个数有几个二 
		}
		int sum=0;
		stack<int>q;
		for(int i=1;i<=n;i++){
			sum=(sum+a[i]*ksm(2,b[i]))%mod;//算上之前的 
			while(q.size()&&a[q.top()]<get(a[i],b[i])){	//可以等价与用之前位置的权值和现在比 
				int tp=q.top();	
				sum=(sum-a[tp]*ksm(2,b[tp])%mod)%mod+mod+a[tp];sum%=mod;
				sum=(sum-a[i]*ksm(2,b[i])%mod)%mod+mod+a[i]*ksm(2,b[i]+b[tp])%mod;sum%=mod;//计算 
				b[i]+=b[tp];q.pop();
			}
			q.push(i);
			cout<<sum<<" ";
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：zhouruoheng (赞：0)

结论比较好猜，就是尽可能将 $2$ 都乘到最大的数上，但是有一个问题，前面的数不能乘后面的 $2$，就是说原本后面的数更小，但是可以乘上更多的 $2$。

因此将 $a_i$ 的 $2$ 拆出来统计个数，用一个单调栈维护，栈内单调递减，每次加入一个数，如果栈顶的元素小于这个数，就把栈顶的 $2$ 全部给新加入的数。注意这里的新数大小是要目前有的 $2$ 的。注意乘上以后会爆 `long long`。细节看代码吧。

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
const int N=2e5+5,mod=1e9+7;
int n;
ll a[N],v[N],b[N];
int st[N];
int qpow(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1) ret=1ll*ret*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return ret;
}
ll count(ll &x)
{
    if(!x) return 0;
    int ret=0;
    while(x%2==0) x/=2,ret++;
    return ret;
}
ll restore(ll x,ll y)
{
    while(y)
    {
        x<<=1;
        if(x>mod) return mod;
        y--;
    }
    return x;
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],v[i]=count(a[i]);
    int tot=0;
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=(ans+a[i]*qpow(2,v[i])%mod)%mod;
        while(tot&&a[b[tot]]<restore(a[i],v[i]))
        {
            ans=(ans-a[b[tot]]*qpow(2,v[b[tot]])%mod+mod)%mod;
            ans=(ans+a[b[tot]])%mod;
            ans=(ans-a[i]*qpow(2,v[i])%mod+a[i]*qpow(2,v[i]+v[b[tot]])%mod+mod)%mod;
            v[i]+=v[b[tot]];
            tot--;
        }
        b[++tot]=i;
        cout<<ans<<' ';
    }
    cout<<'\n';
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

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给定一个序列从左往右对于每个索引 $i$，求出其前缀的数组可以进行任意次以下操作的条件下选择 $j \le k$ 且 $k \le i$ 且 $a_j \mod 2=0$，令 $a_k=a_k \times 2$，$a_j=a_j \div 2$。
## 分析
每一个数只能从它的前面获得乘以 $2$ 的次数，考虑下面的一个序列。

原来的序列：$4,2,5,2,7$。

除 $2$ 后：$1,1,3,1,7$。

数组下标从 $1$ 开始，假如目前遍历到 $i=3$，要把前面所有的乘 $2$ 次数都贪心的乘给 $3$，因为 $3$ 最大，这样可以使每个乘 $2$ 有更大的收益。那怎么变成 $5$ 呢？

对于 $i$ 变成 $5$ 之间的乘 $2$ 次数，给不了 $3$ 乘，那就给 $7$ 去乘，乘了之后，我们发现 $7$ 变成了 $14$，对于 $i=3$ 前面的 $2$ 应该乘给这个 $14$，这样乘 $2$ 的收益更大。之后再假设 $i=5$ 时 $a_5=1$，这个时候我们用掉 $3$ 到 $5$ 之间的 $2$ 之后，$a_5=2$，$a_3>a_5$，这个时候 $i=3$ 前面的 $2$ 肯定乘给 $1_3$ 更优。

这时候我们发现，这个过程类似维护一个单调的东西，只有后面的区间的乘 $2$ 用完之后能够得到一个大于之前的那个获得前面部分乘 $2$ 的那个数，我们才会把前面部分的乘 $2$ 给这个新的数，这个时候这个新的数又守住前面的乘 $2$。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    const ll mod=1e9+7;
    int n;
    cin>>n;
    vector<ll> a(n+1),b(n+1),p_rem(n+1),c(n+1);
    for (int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
        while(b[i]%2==0){
            b[i]/=2;
            c[i]++;
        }
        c[i]+=c[i - 1];
        p_rem[i]=(p_rem[i-1]+b[i])%mod;
    }
    auto ksm=[&](ll a, ll b) -> ll{
        ll ans=1;
        while(b){
            if(b&1)ans=ans*a%mod;
            a=a*a%mod;
            b>>=1;
        }
        return ans%mod;
    };
    auto cmp=[&](ll a,ll b,ll c) -> bool{
        if(c>=30)return true;
        return a<=b*(1LL<<c);
    };
    stack<ll> st;
    ll sum=0;
    for (int i = 1; i <= n; i++){
        while(!st.empty()&&cmp(b[st.top()],b[i],c[i]-c[st.top()])){   
            int lst=0,now=st.top();
            st.pop();
            if (st.size())lst = st.top();
            sum-=(b[now]*ksm(2,c[now]-c[lst])-b[now]);
        }
        if(st.size()) sum+=b[i]*ksm(2,c[i]-c[st.top()])-b[i];
        else sum+=b[i]*ksm(2,c[i])-b[i];
        st.push(i);
        cout<<(sum%mod+p_rem[i]+mod)%mod<< " ";
    }
    cout<<'\n';
}
signed main(void){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int t=1;
    cin>>t;
    while(t--)solve();
    cout<<endl;
    return 0;
}

```

---

