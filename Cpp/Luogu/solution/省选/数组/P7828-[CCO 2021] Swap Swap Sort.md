# [CCO 2021] Swap Swap Sort

## 题目描述

你有一个长度为 $n$ 的序列，每项都是不超过 $k$ 的正整数。

你的朋友发明了一个排序算法，可以根据一个 $1 \sim k$ 的排列对序列进行排序，排序后序列中任意两个不相等的数的相对位置与排列中的相对位置相同。他的算法只使用了邻项交换的操作，且总是保证操作次数最少。为了方便描述，他将这个 $1 \sim k$ 的排列称为目标排列。

例如，序列为 $[1, 4, 2, 1, 2]$，目标排列为 $[4, 1, 2, 3]$，排序后为 $[4, 1, 1, 2, 2]$。

你对你朋友的排序算法在目标排列不同时执行 swap 的次数很感兴趣。为了研究其中的规律，你一开始将目标排列设置为 $1 \sim k$，并以此进行 $q$ 次操作，每次操作交换目标排列中相邻的两个数的位置。每次交换后，你想知道如果用他的排序算法对原序列进行排序会执行 swap 的次数。

## 说明/提示

#### 数据范围
**由于官方数据包过大，本题只节选了官方数据的 $\frac{20}{27}$。**

对于 $\frac{4}{27}$ 的数据，$1 \leq n, q \leq 5 \times 10^3$；

对于另外 $\frac{4}{27}$ 的数据，$1 \leq q \leq 100$；

对于另外 $\frac{7}{54}$ 的数据，$1 \leq k \leq 500$；

对于 $100\%$ 的数据，$1 \leq n, k \leq 10^5$，$1 \leq q \leq 10^6$，$1 \leq a_i \leq k$，$1 \leq b < k$。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D1T1

## 样例 #1

### 输入

```
5 4 3
1 4 2 1 2
3
2
1```

### 输出

```
4
2
2```

# 题解

## 作者：Imiya (赞：9)

先抽象一下题意，对于一种排列，要求的最小交换次数其实就是重赋值后的逆序对个数，比如初始排列就是求正常的逆序对数。

我们不可能每次修改排列都重新求一遍逆序对，那么可以尝试考虑一下单次修改后逆序对是如何变化的。

不难发现，由于修改排列是交换相邻的两个数，这意味着原序列中只有两种值的关系发生变化，逆序对个数只会受这两种值影响。

具体地说，设 $(x,y)$ 表示序列中 $x$ 值在前 $y$ 值在后的数对的个数，交换这两个数在排列中的位置后，若在交换前 $x$ 比 $y$ 靠前，逆序对 $ans=ans-(x,y)+(y,x)$。

容易发现对于任意 $x\ne y$，均有 $(x,y)+(y,x)=c_xc_y$，其中 $c_k$ 指 $k$ 在原序列中的出现次数。因为 $(x,y)+(y,x)$ 是所有由 $x,y$ 组成的数对的个数，其等于 $c_xc_y$。

将 $(y,x)=c_xc_y-(x,y)$ 代入原式，则有 $ans=ans+c_xc_y-2(x,y)$，于是问题变成了求 $(x,y)$。

尝试根号分治，设阈值为 $S$。

对于每一次要交换的 $x,y$，若 $c_x<S$ 且 $c_y<S$，发现可以预处理出每一个值在原序列中的出现位置，利用贡献的单调性使用双指针 $O(S)$ 求出 $(x,y)$，

若 $c_x\ge S$，显然所有大于等于 $S$ 的数不会超过 $\frac n S$ 种，考虑离线处理所有涉及这些数的询问。将所有 $c_x\ge S$ 的询问的信息挂在 $x$ 上。离线处理单个 $x$ 时，可以 $O(n)$ 求出所有 $(x,y),y\ne x$，然后遍历所有挂在 $x$ 上的询问，可以直接对每个询问 $O(1)$ 交付已经求得的 $(x,y)$。

若 $c_x< S$ 且 $c_y\ge S$，可以将 $ans=ans+c_xc_y-2(x,y)$ 变换成 $ans=ans-c_xc_y+2(y,x)$，可以将询问信息挂在 $y$ 上，和上面的那种情况一起处理。

复杂度为 $O(\frac n S\cdot n+S\cdot q)$，根据高中数学知识，可知 $S$ 理论取 $\frac n {\sqrt q}=100$ 最优。

这样一来我们便求出了每一个询问相比上一个询问答案的增值。

求出初始逆序对后累加增值即为最后答案。

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
//#define int long long
inline int read(){
    int i=getchar(),r=0;
    while(i<'0'||i>'9')i=getchar();
    while(i>='0'&&i<='9')r=(r<<1)+(r<<3)+(i^48),i=getchar();
    return r;
}
const int N=100100,S=100;
int n,a[N],b[N],q,k;
long long cnt[N];
vector<int>pos[N];
struct offline{
    long long id,y,sign;
};
vector<offline>t[N];
long long ans[N*10];
long long bta[N];
inline void Add(int i,int v){while(i<=k)bta[i]+=v,i+=i&-i;}
inline int Get(int i){long long r=0;while(i)r+=bta[i],i-=i&-i;return r;}
void init(){
    cin>>n>>k>>q;
    for(int i=1;i<=k;i++)b[i]=i;
    for(int i=1;i<=n;i++){
        a[i]=read();
        pos[a[i]].emplace_back(i);
        cnt[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        Add(a[i],1);
        ans[0]+=i-Get(a[i]);
    }
}
inline long long get_f(int x,int y){//前x后y的对数
    long long res=0;
    int j=0;
    for(int i=0;i<cnt[x];i++){
        while(j<cnt[y]&&pos[y][j]<=pos[x][i])j++;
        res+=cnt[y]-j;
    }
    return res;
}
long long f[N];
signed main(){
//    freopen("read.in","r",stdin);
    init();
    for(int Q=1;Q<=q;Q++){
        int x=read();
        int y=x+1;
        swap(b[x],b[y]);
        if(cnt[b[x]]<S&&cnt[b[y]]<S)ans[Q]+=cnt[b[x]]*cnt[b[y]]-2*get_f(b[x],b[y]);
        else{
            if(cnt[b[x]]>=S)ans[Q]+=cnt[b[x]]*cnt[b[y]],t[b[x]].emplace_back((offline){Q,b[y],-2});
            else ans[Q]-=cnt[b[x]]*cnt[b[y]],t[b[y]].emplace_back((offline){Q,b[x],2});
        }
    }
    for(int i=1;i<=k;i++){
        if(t[i].empty())continue;
        memset(f,0,sizeof(f));
        long long c=0;
        for(int j=1;j<=n;j++){
            c+=(a[j]==i);
            f[a[j]]+=c;
        }
        int siz=(int)t[i].size();
        for(int j=0;j<siz;j++)ans[t[i][j].id]+=t[i][j].sign*f[t[i][j].y];
    }
    for(int i=1;i<=q;i++)ans[i]+=ans[i-1],printf("%lld\n",ans[i]);
    return 0;
}
```















---

## 作者：未来姚班zyl (赞：5)

## 题目大意

给你一个数列 $a_n$，值域为 $[1,k]$。数值的权由排列 $p_k$ 表示，初始时 $p_i=i$。有 $q$ 次修改，每次交换 $p_x$ 和 $p_{x+1}$，你需要在每次修改后求出对 $a_n$ 按照数值的权进行冒泡排序的总次数。

## 题目分析

冒泡排序的总次数等于逆序对个数。则题目求的是带权重的逆序对个数。初始时答案就为原序列的逆序对个数。

设 $c_i$ 表示为值 $i$ 出现的次数。

交换两个权重相邻的值 $a,b$ 的权重，只需要考虑它们俩之间的逆序对变化量 $\Delta$。显然为 $a,b$ 的顺序对数减去逆序对数。当然，求出了其中一个另一个也就求出来了，因为顺序对数与逆序对数之和等于 $c_ac_b$。

很容易想到两种暴力，一种是直接双指针 $O(q(c_a+c_b))$ 求出。一种是把查询挂在 $a$ 或者 $b$ 上，然后离线对每个数求出与其它数的逆序对的数量，$O(n^2)$ 求出。考虑根号分治，设阈值为 $B$，对 $c_a,c_b\le B$ 的做第一种暴力，反之做第二种暴力。复杂度 $O(qB+\frac{n^2}{B})$，根据基本不懂式，$B$ 取 $\sqrt{\frac{n^2}{q}}$ 时有理论最快复杂度 $O(n\sqrt{q})$。

实测发现 $B=90$ 时跑得飞快！

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define E(x) for(auto y:p[x])
#define pc putchar
int read(){int s=0,w=1;char c=getchar();while(c<48||c>57){if(c=='-')w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
void pf(ll x){if(x<0)pc('-'),x=-x;if(x>9)pf(x/10);pc(x%10+48);}
const int N=1e5+5,M=1e6+5;
using namespace std;
vector<int>p[N];
int n=read(),k=read(),m=read(),siz=90,a[N],P[N],sz[N],t[N];
ll ans,del[M],as[N];
int get(int a,int b){
    int l=0,ans=0;
    if(!sz[a])return 0;
    E(b){
        while(l<sz[a]&&p[a][l]<y)l++;
        ans+=l;
    }
    return ans;
}
void add(int x){
    while(x<=k)t[x]++,x+=x&-x;
}
int qry(int x){
    int ans=0;
    while(x)ans+=t[x],x-=x&-x;
    return ans;
}
struct node{
    bool ty;
    int id,b;
};
vector<node>q[N];
int main(){
    repn(i)a[i]=read(),p[a[i]].pb(i);
    rep(i,1,k)P[i]=i,sz[i]=p[i].size();
    repn(i)ans+=qry(k)-qry(a[i]),add(a[i]);
    repm(i){
        int ps=read(),&x=P[ps],&y=P[ps+1];
        if(sz[x]<=siz&&sz[y]<=siz)del[i]=get(x,y)*2-sz[x]*sz[y];
        else if(sz[x]>sz[y])q[x].pb({0,i,y});
        else q[y].pb({1,i,x});
        swap(x,y);
    }
    rep(i,1,k)if(!q[i].empty()){
        int nw=0;
        rep(j,1,k)as[j]=0;
        repn(j)if(a[j]==i)nw++;
        else as[a[j]]+=nw;
        for(auto y:q[i]){
            del[y.id]=1LL*sz[y.b]*sz[i]-as[y.b]*2;
            if(!y.ty)del[y.id]*=-1;
        }
    }
    repm(i)ans+=del[i],pf(ans),pc('\n');
    return 0;
}
```


---

## 作者：Fido_Puppy (赞：5)

$$\texttt{Description}$$

[P7828 [CCO2021] Swap Swap Sort](https://www.luogu.com.cn/problem/P7828)

$$\texttt{Solution}$$

这里提供一种比较 $\text{naive}$ 的在线做法。

假设目标排列为 $p_1, p_2, \cdots, p_k$，则每次需要求的可以感性理解为 $a$ 数组**以 $\bm{p}$ 为基准**的逆序对数量。

刚开始明显答案就是 $a$ 数组的逆序对数量。

然后我们考虑每次 $p$ 排列中交换相邻的两个数会导致答案有什么变化。

由于交换的是**相邻两个**，所以明显在除这两个数之外的数与这两个数的“大小关系”是不会发生变化的，只有这两个数的“大小关系”会变化。

所以设交换的两个数为 $x, y$，我们答案的变化量就可以简单的表示为：

$$\sum_{i = 1}^n \sum_{j = i + 1}^n [a_i = x \wedge a_j = y]$$

这部分的系数为 $+$，因为本来没有算进去，现在改变“大小关系”之后要算了，

$$\sum_{i = 1}^n \sum_{j = i + 1}^n [a_i = y \wedge a_j = x]$$

这部分的系数为 $-$，原因类似。

问题就被简化为求出上面这个式子的值。

接着我们考虑设一个阈值 $B$，对于一个数的出现次数进行根号分治：

首先先用 `vector` 记录每个数出现的位置。

考虑交换的两个数 $x, y$。

+ $x$ 或者 $y$ 的出现次数 $> B$，这部分的答案可以预处理出来。

具体可以先枚举每一个数出现的位置，然后可以枚举出现次数 $> B$ 的数，这样的数不会超过 $\dfrac{n}{B}$ 个，每次直接在 `vector` 上二分求出在位置 $i$ 前面值为 $j$ 的数的个数。

这部分时间复杂度 $\Theta(\dfrac{n ^ 2}{B} \log n)$，空间复杂度 $\Theta(\dfrac{n ^ 2}{B})$。

+ $x$ 和 $y$ 的出现次数都 $\le B$，这部分的答案可以直接在 `vector` 上双指针求出。

这部分时间复杂度 $\Theta(nB)$。

总时间复杂度 $\Theta(\dfrac{n ^ 2}{B} \log n + nB)$，空间复杂度 $\Theta(nB)$，具体 $B$ 的取值就根据程序慢慢调吧。

尽量选择常数较小，空间消耗较小的写法，然后找个评测机心情好的时候，开个 $\text{O}_2$ 就可以过啦！

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

#define N 100005
#define B 1000
#define Poly vector <int>
#define pb push_back
#define ll long long
#define mt make_tuple

using namespace std;

int n, k, q, a[N], p[N], t[N];
Poly vec[N], num;
ll ans = 0;
vector < tuple <int, int, int> > f[N];

void update(int x, int v) {
	for (; x; x -= x & -x) {
		t[x] += v;
	}
}
int query(int x) {
	int ans = 0;
	for (; x <= k; x += x & -x) {
		ans += t[x];
	}
	return ans;
}

int pre(int c, int k) {
	if (vec[c].empty()) return 0;
	else if (vec[c].front() > k) return 0;
	else if (vec[c].back() <= k) return vec[c].size();
	else {
		return upper_bound(vec[c].begin(), vec[c].end(), k) - vec[c].begin();
	}
}

int suc(int c, int k) {
	if (vec[c].empty()) return 0;
	else if (vec[c].back() < k) return 0;
	else if (vec[c].front() >= k) return vec[c].size();
	else {
		return vec[c].size() - (lower_bound(vec[c].begin(), vec[c].end(), k) - vec[c].begin());
	}
}

int main() {
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> n >> k >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		vec[ a[i] ].pb(i);
		ans += query(a[i] + 1);
		update(a[i], 1);
	}
	iota(p + 1, p + n + 1, 1);
	for (int i = 1; i <= k; ++i) {
		if (vec[i].size() > B) num.pb(i);
	}
	for (int i = 1; i <= n; ++i) {
		for (auto j : num) {
			if (i != j) {
				int sum1 = 0, sum2 = 0;
				for (auto pos : vec[i]) {
					sum1 += pre(j, pos);
					sum2 += suc(j, pos);
				}
				f[i].pb(mt(j, sum1, sum2));
			}
		}
	}
	while (q--) {
		int pos; cin >> pos;
		int x = p[pos], y = p[ pos + 1 ];
		if (vec[x].size() > B) {
			for (auto i : f[y]) {
				if (get <0> (i) == x) {
					ans += get <1> (i);
					ans -= get <2> (i);
					break;
				}
			}
		}
		else if (vec[y].size() > B) {
			for (auto i : f[x]) {
				if (get <0> (i) == y) {
					ans += get <2> (i);
					ans -= get <1> (i);
				}
			}
		}
		else {
			int len1 = vec[x].size(), len2 = vec[y].size();
			int j = 0;
			for (int i = 0; i < len1; ++i) {
				while (j < len2 && vec[y][j] <= vec[x][i]) ++j;
				ans -= j;
				ans += len2 - j;
			}
		}
		swap(p[pos], p[ pos + 1 ]);
		cout << ans << "\n";
	}
	return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：UNVRS (赞：3)

## 题意

给定长度为 $n$ 的值域为 $[1,k]$ 的序列 $A$，每次交换两种数的大小关系，求逆序对。

$n\le 10^5,q\le 10^6$

## 思路

这题非常套路，操作是交换两种数的大小关系，所以我们只需要求出这两种数的顺序对就可以了（因为顺序对好写，逆序对用总对数减即可）。

然后非常经典的对值域分块，设 $B$ 表示出现次数大于 $B$ 的为大数，那么对于大数暴力求出它跟所有数的顺序对（使用前缀和，然后拿其他块查前缀和总和），时空复杂度 $O(n^2/B)$。

询问时两个都是小数的则双指针扫一遍，时间复杂度 $O(qB)$。

于是有 $B=n/\sqrt q = 100$ 时最优，可能需要看评测机心情。

## 吗？

但是我不想看评测机的心情，或者我甚至想要拿个最优解玩玩那就不能取 $B=100$ 了。

我们先考虑怎么样比较好的卡常数，首先我们发现当双指针的时候小块的大小若小于 $B/\log B$ 则可以直接二分。

然后把重复的询问丢进哈希表里。

---

我们发现 $q$ 相比于 $n$ 来说实在是大得不像话，那这样有没有进一步地（至少看起来地）分摊复杂度呢？

以下假定询问非常聪明全部查小块。

然后我们分析一下：

我们设微块（一定二分）的大小为 $A$，数量为 $C$，那么有：
$$
\min\{q,\frac{n-AC}{B}\times C\}(B+A)+Aq\log B
$$
实际上我们会把 $A$ 设得再小一些，那么 $Aq\log B$ 很小，可以忽略不记。

考虑左边，如果 $(n-AC)/B\times C$ 要较大的话，则 $B+A$ 就不可能接近 $2B$（因为接近的话则左边的 $\min$ 是两个根号相乘 $O(n)$ 的）。

于是至少常数除二了（可能认真分析能到一个类似于 $(nq)^{3/4}$ 的东西）。

## 那么实际怎么样呢？

实际上数据里塞了很多 $400\sim 500$ 的块，$B$ 调到 $500$ 以上，那么 $\min$ 里面的东西只有 $6\times 10^4$ 多，于是我们不开 O2 都可以顶着 `unordered_map` 的巨大常数轻松通过此题！

二分有一点优化作用，但不多。

~~第一名老哥跑得好快啊！打不过啊！~~用 emhash 黑科技打过了 QwQ。

## CODE

实际代码为以下代码中的 `emhash.h` 替换成自用的魔改版。

```c++
#include "emhash.h"

#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<unordered_map>
using namespace std;
using ll=long long;
constexpr int N=100010,B=700,LB=10,FSIZE=1<<16;
int n,k,q,a[N],b[N],pre[N],num[N],big;
ll ans,to[N/B][N];
vector<int> v[N];
// unordered_map<ll,ll> old;
emhash7::HashMap<ll,ll> old;
struct FT{
    int a[N];
    void modify(int x){for(;x;x-=x&-x) ++a[x];}
    void query(int x){for(;x<=n;x+=x&-x) ans+=a[x];}
}ini;
char BuF[FSIZE],*InF=BuF,WuF[FSIZE],*OnF=WuF,ST[20],*STC=ST;
inline char nxtc(){
    if(BuF+FSIZE==InF) fread(InF=BuF,1,FSIZE,stdin);
    return(*InF++);
}
inline void putc(char c){
    if(WuF+FSIZE==OnF) fwrite(OnF=WuF,1,FSIZE,stdout);
    *OnF++=c;
}
template<typename T>inline void read(T &x){
    char c=nxtc();
    while(c<33) c=nxtc();
    for(x=0;32<c;c=nxtc()) x=x*10+(c^48);
}
void write(ll x){
    if(!x) putc(48);
    for(;x;x/=10) *++STC=x%10^48;
    for(;STC!=ST;putc(*STC--));
    putc('\n');
}
void calc(int num,int is){
    for(int i:v[is]) to[num][is]+=pre[i];
}
int main(){
    fread(BuF,1,FSIZE,stdin);
    read(n);read(k);read(q);
    for(int i=1;i<=n;++i){
        read(a[i]);
        ini.query(a[i]+1);
        ini.modify(a[i]);
        v[a[i]].push_back(i);
    }
    for(int i=1;i<=k;++i){
        int s=v[i].size();
        if(s>B){
         
            num[i]=++big;
            for(int j=1,k=0;j<=n;++j){
                for(;k<s&&v[i][k]<j;++k);
                pre[j]=k;
            }
            for(int j=1;j<i;++j) calc(big,j);
            for(int j=n;j>i;--j) calc(big,j);
        }
    }
    for(int i=1;i<=n;++i) b[i]=i;
    for(int p;q--;){
        read(p);
        int x=b[p],y=b[p+1],sx=v[x].size(),sy=v[y].size();
        auto add=[&](ll s){
            if(x==b[p]) ans+=s+s-(ll)sx*sy;
            else ans+=(ll)sx*sy-s-s;
        };
        if(sx<sy){
            swap(x,y);
            swap(sx,sy);
        }
        if(sx<=B){
            ll tmp=x*n+y;
            auto p=old.insert(make_pair(tmp,0));
            ll &sum=p.first->second;
            if(p.second)
                for(int i=0,j=0;j<sy;++j){
                    for(;i<sx&&v[x][i]<v[y][j];++i);
                    sum+=i;
                }
            add(sum);
        }else add(to[num[x]][y]);
        swap(b[p],b[p+1]);
        write(ans);
    }
    fwrite(WuF,1,OnF-WuF,stdout);
    return(0);
}
```





---

## 作者：Aria_Math (赞：3)

分块做法。

首先题目其实就是让你求出有多少对 $i < j$ 满足 $a_i = x, a_j = y$。

如果 $i$ 和 $j$ 不在同一个块内，设 $cnt(i,j)$ 表示第 $i$ 个块内 $j$ 出现了几次，那么答案就是 $\sum_i cnt(i,y) \times \sum_{j < i} cnt(j, x)$，枚举 $i$ 后 $j$ 直接前缀和即可。

如果 $i$ 和 $j$ 在同一个块，这样的 $(i,j)$ 对数只有 $\dfrac{n}{B} \times B ^ 2 = nB$ 个，全部找出来即可。实现可以先枚举块，再枚举 $a_i = y$，把 $i$ 前面的数丢到桶里。

时间复杂度 $\mathcal{O}((n + k) B + \dfrac{qn}{B})$，由此可知 $B = 1000$ 左右最优，空间离线后逐块处理可以做到线性。

## Code

```cpp
// They say that life is always easier
// After you let yourself come undone
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
const int Q = 1e6 + 10;
struct Node {
	int x, id, sgn;
};
int n, k, q, a[N], b[N], c[N], pre[N], buk[N];
ll ans[Q];
vector<Node> p[N];
vector<int> pos[N];
void Add(int pos, int k) {
	while(pos) c[pos] += k, pos -= pos & -pos;
}
int Sum(int pos) {
	int ans = 0;
	while(pos <= k) ans += c[pos], pos += pos & -pos;
	return ans;
}
int main() {
	freopen("data.in", "r", stdin);
	freopen("code.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> k >> q;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= k; ++i) b[i] = i;
	for(int i = 1; i <= n; ++i)
		ans[0] += Sum(a[i] + 1), Add(a[i], 1);
	for(int i = 1; i <= q; ++i) {
		int x; cin >> x;
		p[b[x + 1]].push_back({b[x], i, 1});
		p[b[x]].push_back({b[x + 1], i, -1});
		swap(b[x], b[x + 1]);
	}
	int B = 4000;
	for(int l = 1, r; l <= n; l = r + 1) {
		r = min(l + B - 1, n);
		for(int i = l; i <= r; ++i)
			pos[a[i]].push_back(i);
		for(int x = 1; x <= k; ++x) {
			for(int i : pos[x]) 
				for(int j = l; j < i; ++j) buk[a[j]]++;
			for(Node i : p[x])
				ans[i.id] += 1ll * i.sgn * (pre[i.x] * pos[x].size() + buk[i.x]);
			for(int i : pos[x]) 
				for(int j = l; j < i; ++j) buk[a[j]]--;
		}
		for(int i = l; i <= r; ++i) pre[a[i]]++;
		for(int x = 1; x <= k; ++x) pos[x].resize(0);
	}
	for(int i = 1; i <= q; ++i)
		printf("%lld\n", ans[i] += ans[i - 1]);
	return 0;
}
```

---

## 作者：woshishabi11451444 (赞：2)

首先思考如何计算贡献，令 $p_i$ 表示 $a_i$ 在目标排列的出现位置。

若 $a_i$ 在运动时要跨过 $a_j$ 当且仅当 $j < i$ 且 $p_i < p_j$。

这不就是逆序对吗？

接下来是多种做法。

由于是交换相邻两个数，所以只有这两个数内部的贡献会对答案造成影响。

令 $ans_i$ 表示第 $i$ 次询问的答案，$cnt_i$ 表示原序列中有多少个元素 $i$，$(x, y)$ 表示在序列中有多少对 $(i, j)$ 满足 $a_i = x, a_j = y$。

假设第 $i$ 次操作 $p_x$ 和 $p_{x + 1}$ 交换。

易得：

$$ans_i = ans_{i - 1} - (p_{x + 1}, p_x) + (p_x, p_{x + 1})$$

注意到：$(p_x, p_{x + 1}) + (p_{x + 1}, p_x) = cnt_{p_x} \times cnt_{p_{x + 1}}$。

那么易得：

$$ans_i = ans_{i - 1} + cnt_{p_x} \times cnt_{p_{x + 1}} - 2 \times (p_{x + 1}, p_x)$$

此时问题变成了询问 $(p_{x}, p_{x + 1})$。

## 分块做法

设块长为 $B$，对整个序列分块。

对于一个合法数对 $(i, j)$，若 $i$ 和 $j$ 在同一个块，考虑预处理，定义 $k_{i, x, y}$ 为此时所求。

接着我们处理 $i$ 和 $j$ 不在同一个块的情况。

定义 $s_{i, j}$ 表示第 $i$ 个块元素 $j$ 的出现数量。

那么容易发现 $i$ 和 $j$ 不在同一个块情况，用 $s_{i, j}$ 可以快速求解。

此时时间复杂度：$O(\frac{N}{B} \times B^2 + q \times \frac{N}{B}) = O(NB + q \times \frac{N}{B})$。

此时有一个 trick：我们可以提前记录每个元素是否出现在某个块，若出现记录这个元素在这个块内离散化后的值，那么 $s_{i, j}$ 和 $k_{i, x, y}$ 的规模就变小了。

空间复杂度：$O(NB)$。

考虑平衡时间复杂度，推理如下：

$$NB = q \times \frac{N}{B}$$

$$NB^2 = qN$$

$$B^2 = q$$

$$B = \sqrt{q}$$

理论上 $B$ 取 $\sqrt{q}$ 即 $1000$ 最优，实际会微调。

由于空间限制考虑将查询信息存下来，离线做。

那么此时空间就存得下了。

## 根号分治做法

考虑设置阀值 $B$。

若 $\max(cnt_{p_x}, cnt_{p_{x + 1}}) < B$，我们可以预先记录每种元素在哪些位置上出现，通过双指针得到这部分的答案。

否则，不妨设 $cnt_{p_{x}} > cnt_{p_{x + 1}}$，如果不满足该条件可以用 $(p_x, p_{x + 1}) + (p_{x + 1}, p_x) = cnt_{p_x} \times cnt_{p_{x + 1}}$ 这个式子转化成 $cnt_{p_{x}} > cnt_{p_{x + 1}}$ 的情况，那么 这样的 $p_x$ 的数量不超过 $\frac{N}{B}$，考虑预处理这样的询问。

时间复杂度：$O(N \times  \frac{N}{B} + q \times B)$。

考虑平衡时间复杂度，推理如下：

$$N \times  \frac{N}{B} = q \times B$$

$$N^2 = qB^2$$

$$B^2 = \frac{N^2}{q}$$

$$B = \sqrt{\frac{N^2}{q}}$$

理论上 $B$ 取 $\sqrt{\frac{N^2}{q}}$ 即 $100$ 最优，实际会微调。

空间复杂度：$O(\frac{N^2}{B})$。

由于这里空间较大，建议将查询记下来离线实现。

---

## 作者：7KByte (赞：2)

有删减，原文见[**我的博客**](https://www.cnblogs.com/SharpnessV/p/15177914.html)。

对于初始排列，就是求原序列的逆序对数。

对于逆序对我们可以拆开来算，用 $[i,j]$ 表示满足 $a_u =i,a_v=j,i>j$ 二元组 $(u,v)$ 个数。

那么初始答案可以表示为 $\sum\limits_{i = 1}^{k}\sum\limits_{j = i + 1}^{k}[i,j]$。

推导之后可以得到，对于一次交换，令交换的两个数为 $x,y$，我们只用在上一次答案的基础上加上 $2\times[x,y] - c _x\times c_y$，其中 $c_i$ 表示 $i$ 在原序列中出现的次数。

现在我们只用求 $[x,y]$​，这个玩意本质上也是求逆序对，考虑根号分治，对于 $c_x, c_y\le \sqrt n$ 的直接爆算，其余的离线后对整个原序列扫一遍统计答案。

由于 $q$ 远大于 $n$ ，我们令 $lim$ 表示对于 $c_x, c_y\le lim$ 的 $[x,y]$ 进行爆算，解方程 $q\times lim = \frac{n^2}{lim}$，解的 $lim = 100$ 时最优。

---

## 作者：StayAlone (赞：1)

强行在线的做法。

直接维护每一次修改后的新相对大小下逆序对数量。

令 $(x, y) = \sum\limits_{i=1}^n\sum\limits_{j=i+1}^n [a_i=y\land a_j=x]$，$s_x$ 表示序列中 $x$ 的出现次数。

若此时交换值 $p, q$，显然只有 $p, q$ 两者内部的逆序对受到影响。而这次答案与上次答案的变化量 $\Delta=-(p, q)+(q, p)$。

注意到 $(p,q) + (q,p)=s_p\times s_q$，则只需要考虑计算 $(p,q)$ 或 $(q,p)$ 其中之一即可。

设定阈值 $B$。

对于 $cnt_p > B$，称这样的 $p$ 为“少量的”。这样的 $p$ 不会超过 $\frac{n}{B}$ 个，考虑预处理。对于每一个“少量的” $p$，预处理 $cnt_v=\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n [a_i=v\land a_j=p]$。只需要扫一遍 $a$ 数组，$a_i$ 会对 $cnt_{a_i}$ 作出的贡献，就是 $i$ 右边 $p$ 的数量。总时间复杂度和空间复杂度为 $\mathcal O(\frac{n^2}{B})$，查询复杂度为 $\mathcal O(1)$。

预处理好上面的数组，就可以轻易维护变化量了。

- 若 $cnt_p>B$，直接得出 $(p, q)=cnt_q$；
- 否则，若 $cnt_q>B$，直接得出 $(q, p) = cnt_p$。

注意上述两种情况中的 $cnt$ 数组是不同的，其对应的是“少量的”数的 $cnt$ 数组。

- 上述两种情况外，有 $cnt_p\leq B, cnt_q\leq B$，此时使用双指针求逆序对即可，时间复杂度 $\mathcal O(B)$。

总时间复杂度 $\mathcal O(\frac{n^2}{B} + qB)$，显然有 $B=\frac{n}{\sqrt q}=100$ 时最优，然而此时被卡空间。

实测这个题时限是比较松的，$B=1000$ 就能通过。调了一下取 $B=250$。

而离线处理“少量的”数的询问就能避免空间问题，降至 $\mathcal O(n+q)$。

[AC record](https://www.luogu.com.cn/record/172086602)

```cpp
int n, k, q, B, a[MAXN], p[MAXN], idx[MAXN], s[MAXN]; ll ans0, cnt[405][MAXN];
vector <int> pos[MAXN], mrt;

struct {
	int sum[MAXN];
	
	il void add(int x) {
		while (x) ++sum[x], x -= lowbit(x);
	}
	
	il int query(int x) {
		int ans = 0;
		while (x <= k) ans += sum[x], x += lowbit(x);
		return ans;
	}
} T;

int main() {
	read(n, k, q); B = 250;
	rep1(i, 1, n) {
		read(a[i]); pos[a[i]].eb(i); ++s[a[i]];
		ans0 += T.query(a[i] + 1); T.add(a[i]);
	}
	rep1(i, 1, k) p[i] = i;
	rep1(i, 1, k) if (pos[i].size() > B) {
		int r = pos[i].size(), lst = 0; mrt.eb(i); idx[i] = mrt.size();
		for (auto v : pos[i]) {
			rep1(j, lst + 1, v - 1) cnt[idx[i]][a[j]] += r;
			--r; lst = v;
		}
	} int t;
	while (q--) {
		read(t); int a = p[t], b = p[t + 1]; swap(p[t], p[t + 1]);
		const ll f = 1ll * s[a] * s[b]; ll pre = 0;
		if (!s[a] || !s[b]) {
			printf("%lld\n", ans0);
			continue;
		}
		if (idx[a]) pre = cnt[idx[a]][b];
		else if (idx[b]) pre = 1ll * s[a] * s[b] - cnt[idx[b]][a];
		else {
			for (int i = 0, j = -1; i < pos[a].size() && j < (int)pos[b].size(); ++i) {
				while (j + 1 < (int)pos[b].size() && pos[b][j + 1] < pos[a][i]) ++j;
				pre += j + 1;
			}
		} ans0 -= pre, ans0 += f - pre; printf("%lld\n", ans0);
	}
	return 0;
}
```

---

