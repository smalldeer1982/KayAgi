# 【MX-X11-T4】「蓬莱人形 Round 1」视奸

## 题目背景

原题链接：<https://oier.team/problems/X11E>。

---

「お願い　きみが欲しいの」

「頼り散らしてシックラブ　なんて最高ね」

「分けてくれなきゃ　君の“痛い”感じていたい」

「ねえいいでしょう？　吸い取って　救いたいんだってば」



## 题目描述

定义一个**不可重集**二元组 $(A,B)$ 是好的当且仅当能通过以下操作在有限次操作内将 $A$ 变成 $B$。

- 每次可以选择 $A$ 中一个数 $x$，将 $x$ 从 $A$ 中删除，再把 $x-1,x+1$ 加到 $A$ 中，若有相同只保留一个。

给定 $A,B$ 集合**初始**的值域 $[1,n]$，且都为整数，**操作过程中可以超出** $[1,n]$。再给出 $B$ 集合，和一个长度为 $n$ 的数组 $p$。

求一个符合要求的 $A$，使得 $(A,B)$ 是好的，且满足 $\sum\limits_{i=1}^n [i \in A] \times p_i$ 最小。

## 说明/提示

**【样例解释 #1】**

对于第一组测试数据，$A=\{ 1,4,5,8,9\}$ 为一个合法的答案。花费为 $3+(-3)+4+(-3)+(-5)=-4$。

对于第二组测试数据，$A=\{ 2,7\}$ 为一个合法的答案，因为可以通过分别操作 $2,7$ 变为 $\{1,3,6,8\}$，即集合 $B$。花费为 $0+2=2$。

**【数据范围】**

**本题使用子任务捆绑**。

对于所有测试数据，$1 \le T \le 10$，$1 \le n \le 10^5$，$-10^9 \le p_i \le 10^9$。

|子任务编号|$n\le$|特殊性质|分值|
|:-:|:-:|:-:|:-:|
|$1$|$18$|无|$10$|
|$2$|$10^5$|A|$10$|
|$3$|$10^5$|B|$20$|
|$4$|$10^5$|C|$20$|
|$5$|$10^5$|无|$40$|

- 特殊性质 A：保证 $B$ 集合大小不超过 $10$。
- 特殊性质 B：保证字符串 $s$ 中不会出现子串 `101`。
- 特殊性质 C：保证所有 $p_i$ 相等。

## 样例 #1

### 输入

```
0 2
9
100110011
3 0 -1 -3 4 -1 -4 -3 -5
8
10100101
2 0 2 4 1 1 2 2```

### 输出

```
-4
2```

# 题解

## 作者：chenly8128 (赞：3)

~~细节题，赛时交了 5 发才过。~~

这题需要分段分类。

题目中说“过程中可以超过 $[1,n]$”，但是因为超过 $[1,n]$ 的节点没法被删掉（或者说删掉后会产生至少一个另外的、超出 $[1,n]$ 的节点），不可能与集合 $B$ 匹配，所以实际上不能超过 $[1,n]$。（当然，笔者实力有限，没有想明白为什么题目里会有这么一句话，这一段分析可能是胡扯，欢迎批评指正）。

## part 1

首先考虑特殊性质 B 怎么做。如果没有 `101` 那么，很明显操作从来没有进行过，不然一定会产生 `101` 结构。于是直接统计每个需要选择的元素的权值累加和即可。

## part 2

**对于 $B$ 中形如 `X0…0Y` 形式的结构（`0` 至少两个），中间所有 `0` 代表的集合元素，都不能在 $A$ 中出现**。否则这样的元素 $a$ 删掉后，与它相邻的、$B$ 中没有出现的元素 $b$ 就会出现；为了与 $B$ 匹配，只能再删除 $b$，然后 $a$ 就会出现。以上过程循环交替，永远不可能使得 $a$ 和 $b$ 同时被删除。

根据以上结论，可以将 $B$ 分段。凡是出现连续两个 `0` 的位置，都要把 $B$ 分为两段，两段之间一定互不干扰。特别的，为了代码方便，首尾都加上两个 `0` 作为哨兵。

现在只需要在每一段中处理这个问题了。

## part 3

如果某一段满足性质 B，那么直接用 part 1 方法求解。如果不满足性质 B，那么该段长度至少为 $3$：

- 如果该段长度为 $3$：那么该段只能为 `101`，此时**需要分类特判**。$A$ 有 `111`，`101`，`011`，`110`，`010` 这几种选法，计算最优解即可。
- 如果该段长度大于 $3$：假设 $B$ 中该段形式如 `1X1`，**只要在 $A$ 的 `X` 段中有元素被选择，那么整一段一定可以通过若干次操作与 $B$ 吻合**。因此只需要根据贪心思想，选择所有负权值的节点即可。然而根据结论，如果 $A$ 的 `X` 中一个节点都没有选择，那么必须强制选择权值最小的非负节点。

## 参考代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5+10;
int c,T,n,v[MAXN],sum[MAXN],sum2[MAXN];
char s[MAXN];
signed main (void) {
	scanf ("%lld%lld",&c,&T);
	while (T--) {
		scanf ("%lld%s",&n,s+1);
		for (int i = 1;i <= n;i++) scanf ("%lld",v+i);
		for (int i = 1;i <= n;i++) {
			sum[i] = sum[i-1] + min(0ll,v[i]);
			sum2[i] = sum2[i-1] + v[i];
		}
		int ans = 0,st = 1,p = 1e16;
		s[0] = s[n+1] = s[n+2] = '0';
		bool b = false;
		for (int i = 1;i <= n+2;i++) {
			if (s[i] == '0' && s[i-1] == '0') {
				st = i+1;
				p = 1e16;
				b = false;
				continue;
			}
			if (s[i] == '0' && s[i+1] == '0') {
				int ed = i-1;
				if (st <= ed) {
					if (b) {
						if (ed - st == 2) {
							if (v[st+1] < 0) {
								ans += sum[ed] - sum[st-1];
								continue;
							}
							if ((v[st] >= 0 && v[ed] >= 0)
								|| (v[st] < 0 && v[ed] < 0))
								ans += min(v[st+1],v[st]+v[ed]);
							else if (v[st] < 0) ans += v[st] + min(v[st+1],v[ed]);
							else ans += v[ed] + min(v[st+1],v[st]);
						}
						else {
							ans += sum[ed] - sum[st-1];
							if (sum[ed-1] - sum[st] == 0) ans += p;
						}
					}
					else ans += sum2[ed] - sum2[st-1];
				}
				continue;
			}
			if (i-1 > st) p = min(p,v[i-1]);
			if (s[i] == '1' && s[i-1] == '0' && i != st) b = true;
		}
		printf ("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：_lmh_ (赞：2)

首先题目里那个“中间结果可以超出 $[1,n]$”是骗人的，如果走出那个范围就回不来了。

不仅如此，任何一个长度 $\ge 2$ 的 `0` 连续段都不能在过程中出现 `1`。假设左边出现了一个 `1`，那么必须把它消掉；这样右边多出来一个 `1`，永远也消不完。

现在我们只需要处理 `0` 连续段长度 $\le 1$ 的段 $[l,r]$ 了。

下面证明：只要 $[l,r]$ 不全是 `1`（此时必须全部选择），那么只需在 $[l+1,r-1]$ 中选任意一个位置 $x$ 置 `1` 就可以通过合理的操作方式满足题目要求。

只有一个 `0`，其他位置都是 `1`，并且两端都是 `1` 的连续段可以通过操作 `0` 两侧的 `1` 移动它的位置。而如果此时 `0` 处在第二个位置，则可以操作第一个位置的 `1` 扩展整个序列。

因此我们先对 $x$ 进行一次操作，造出一个 `0`。现在先向左扩展到 $l$，把 `0` 移回 $x$，再向右扩展到 $r$ 。

最后，把 `0` 移到任意一个需要置 `0` 的位置，然后在其他位置挖空即可。

然后我们贪心选择负数的 $w$，如果没选到 $[l+1,r-1]$ 中间的再选一个最小的非负整数。需要特判 `101`，此时可以只选择两侧的 `1`。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=100007;
ll T,n,ans,w[N];
char s[N];
void solve(int l,int r){
	if (l+2==r&&s[l+1]=='0'){
		ans+=min(w[l]+w[l+2],w[l+1]+min(0ll,w[l])+min(0ll,w[l+2]));
		return;
	}
	bool fl=1;
	for (int i=l;i<=r;++i) fl&=(s[i]=='1');
	if (fl){
		for (int i=l;i<=r;++i) ans+=w[i];return;
	}
	fl=0;
	for (int i=l;i<=r;++i) if (w[i]<0){
		ans+=w[i];if (i!=l&&i!=r) fl=1;
	}
	if (fl) return;
	ll mn=1e18;
	for (int i=l+1;i<r;++i){
		mn=min(mn,w[i]);
	}
	ans+=mn;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T>>T;
	while(T--){
		cin>>n>>(s+1);ans=0;
		for (int i=1;i<=n;++i) cin>>w[i];s[n+1]=s[n+2]='0';
		for (int l=0,r=1;r<=n;++r){
			if (s[r]=='1'){
				if (l==0) l=r;
				if (s[r+1]=='0'&&s[r+2]=='0'){solve(l,r);l=0;}
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：2)

# P12150 题解

赛时想出正解，没想到特判长度为 $3$ 的情况，痛失 $60$ 分，感谢 [@良心WA题人](https://www.luogu.com.cn/user/132424) 赛后的帮助。

## 思路

对于满足下列条件的段，我们将其归为一个连通块：

- 左右端都为 $1$。
- 相邻的 $0$ 不超过 $1$ 个。

记区间为 $[l,r]$，在这样的连通块里面，当 $r-l+1>3$ 时，在区间 $[l+1,r-1]$ 中填入任意个 $1$（不为 $0$ 个），可以证明能够通过若干次操作转化成任意一个至少具有 $1$ 个 $0$ 的串。因此，对于这样的连通块，在 $[l+1,r-1]$ 必须选出至少一个设为 $1$，如果区间内的 $p$ 全部为正，那么选择一个最小的整数，否则将所有负数累加。最后考虑左右端点，很显然，当对应的 $p$ 值为负，则将其选上。如果连通块内不存在 $0$，则需要将所有位置全部选上。

```cpp
bool all1=true;
_rep(i,l,r) {
    if (!s[i]) {
        all1=false;
        break;
    }
}
if (all1) {
    _rep(i,l,r) ans+=p[i];
    continue;
}
bool allpst=true;
int mn=inf,sum=0;
_rep(i,l+1,r-1) {
    if (p[i]<=0) allpst=false,sum+=p[i];
    else mn=min(mn,p[i]);
}
// printf("[%lld, %lld]: %lld %lld %lld\n",l,r,allpst,mn,sum);
if (allpst) ans+=mn;
else ans+=sum;
ans+=min(p[l],0LL);
ans+=min(p[r],0LL);
```

接下来考虑长度为 $3$ 的，很明显只有三个一或者两个一夹一个零的情况，如果是三个一，那么三个位置都选上，如果是两个一夹着一个零，那么有两种选择，要么选择两端，要么选择中间然后两端根据其 $p$ 值正负性决定是否选择。

```cpp
if (s[l+1]) ans+=p[l]+p[l+1]+p[r];
else {
    int a=p[l]+p[r];
    int b=p[l+1]+min(p[l],0LL)+min(p[r],0LL);
    ans+=min(a,b);
}
```

考虑长度为 $2$ 的连通块，显然，需要两个都取。

```cpp
ans+=p[l]+p[r];
```

长度为 $1$，显然，直接取掉。

```cpp
ans+=p[l];
```

## 代码

```cpp
const int N=100005;
const int inf=5e18;

int c,T,n;
char arr[N];
int s[N];
int p[N];
vector<pii> vec;

i32 main() {
    read(c),read(T);
    while (T--) {
        memset(s,0,sizeof(s));
        memset(p,0,sizeof(p));
        read(n);
        readstr(arr+1);
        _rep(i,1,n) s[i]=arr[i]-'0';
        _rep(i,1,n) read(p[i]);
        vec.clear();
        int l=1,r;
        while (true) {
            while (l<=n && !s[l]) l++;
            if (l==n+1) break;
            r=l;
            while ((s[r+1] || s[r+2]) && r+1<=n) r++;
            vec.emplace_back(pii{l,r});
            // printf("add sequence: [%lld, %lld]\n",l,r);
            l=r+1;
        }
        int ans=0;
        _iter(it,vec) {
            int l=it->first,r=it->second;
            if (l==r) ans+=p[l];
            else if (l+1==r) ans+=p[l]+p[r];
            else if (l+2==r) {
                if (s[l+1]) ans+=p[l]+p[l+1]+p[r];
                else {
                    int a=p[l]+p[r];
                    int b=p[l+1]+min(p[l],0LL)+min(p[r],0LL);
                    ans+=min(a,b);
                }
            } else {
                bool all1=true;
                _rep(i,l,r) {
                    if (!s[i]) {
                        all1=false;
                        break;
                    }
                }
                if (all1) {
                    _rep(i,l,r) ans+=p[i];
                    continue;
                }
                bool allpst=true;
                int mn=inf,sum=0;
                _rep(i,l+1,r-1) {
                    if (p[i]<=0) allpst=false,sum+=p[i];
                    else mn=min(mn,p[i]);
                }
                // printf("[%lld, %lld]: %lld %lld %lld\n",l,r,allpst,mn,sum);
                if (allpst) ans+=mn;
                else ans+=sum;
                ans+=min(p[l],0LL);
                ans+=min(p[r],0LL);
            }
        }
        writeln(ans);
    }
    return 0;
}
```

---

## 作者：寄风 (赞：2)

首先注意到如果存在两个相邻数都是 $0$ 的话那么一定不能有一个在操作 $A$ 的过程中变成 $1$，否则就一定不能把 $A$ 操作成 $B$ 了。

那么我们可以把原 $B$ 分段，具体的就是先扫一遍，遇到 $0\ 0$ 就分段。

然后注意到每一段中能通过一系列操作使得代价比全选择这段中的 $1$ 更低的充要条件是这段中存在 $101$ 的子串。

而且我们发现如果有了 $101$ 的话，那么我们选择这个段中任意一个不在两端的数都是可以还原的。

所以我们在这个段中选出所有代价是负数的，如果没有负数就选一个最小的正数即可。

那么做完了。

实现有些细节，要注意一下。

```cpp
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;

const int N = 1e5 + 5;

int C, T, n, sb;
std::string s;
i64 a[N], dp[N];

struct node {
    int l, r;
    i64 v;
};

inline void solve() {
    std::cin >> n >> s;
    s = ' ' + s;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    std::vector<bool> vis(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '0' && s[i] == '0') vis[i - 1] = vis[i] = 1;
    }
    vis[0] = 1;
    if (s[1] == '0') vis[1] = 1;
    if (s[n] == '0') vis[n] = 1;
    // if (s[n - 1] == '0') {
    //     s.pop_back();
    //     n--;
    // }
    // if (s[0] == '0') {
    //     for (int i = 2; i <= n; i++) a[i - 1] = a[i];
    //     s.erase(s.begin());
    //     n--;
    // }

    std::vector<std::vector<std::pair<int,i64> >> tp;
    for (int i = 1; i <= n; i++) {
        if (vis[i - 1] && !vis[i]) {
            int j = i;
            for(; j <= n && !vis[j]; j++);
            j--;
            std::vector<std::pair<int,i64> > nw;
            for (int k = i; k <= j; k++) {
                nw.push_back(std::make_pair(s[k] - '0', a[k]));
                // std::cerr << s[k - 1] - '0' << ' '<<a[k] << '\n';
            }
            // std::cerr << '\n';
            tp.push_back(nw);
        }
    }
    
    i64 ans = 0;
    int nid = 0;
    for (auto v : tp) {
        i64 res = 0 , tmp = 0;
        for (auto [a, b] : v) {
            if(a) tmp += b;
        }
        bool f = 0;
        for (int j = 0; j + 2 < v.size(); j++) {
            if (v[j].first == 1 && v[j + 1].first == 0 && v[j + 2].first == 1) {
                f = 1;
                break;
            }
        }

        if (!f) {
            ans += tmp;
            // std::cerr << tmp << ' ';
            // for (auto [u, vv] : v) std::cerr << u << ' ' << vv << '\n';
            // std::cerr << '\n';
            continue;
        }
        f = 0;
        auto dw = v;
        if (dw.size() <= 2) {
            ans += tmp;
            continue;
        }
        dw.erase(dw.begin());
        dw.pop_back();
        for (auto [a, b] : dw) {
            res += std::min(0ll, b);
        }
        if (res >= 0) {
            res = 1e18;
            for (auto [a, b] : dw) {
                res = std::min(res, b);
            }
        }
        res = std::min(res + std::min(0ll, v.front().second) + std::min(0ll, v.back().second), tmp);
        ans += res;
        // std::cerr << res << ' ';
        // for (auto [u, vv] : v) std::cerr << u << ' ' << vv << '\n';
        // std::cerr << '\n';
    }
    std::cout << ans << '\n';
    // std::cerr << "\n\n\n";
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);

    std::cin >> C >> T;

    while (T--) {
        solve();
    }

    return 0;
}
```

---

## 作者：sbno333 (赞：1)

考虑一个长度至少为 $2$ 的连续 $0$ 的子串不能选取其中任何一个，因为之后怎么操作都没办法让这段重新变为全 $0$。

考虑两边都被长度至少为 $2$ 的连续 $0$ 的字串包围的连续 $1$ 的字串必须都选，否则无法操作做到全 $1$。

考虑单独的一个 $0$。

我们认为一个仅有连续 $1$ 以及单独的 $0$ 构成的串（并且都有）为一段，两边被长度至少为 $2$ 的连续 $0$ 子串包围。

对于每一段，两个端点不能操作，单独考虑。

考虑中间部分，发现只要中间任何一处有选了，就能通过操作塞入每一个单独 $0$ 的段是他们在集合中。

然后对每个单独的 $0$ 操作一次，再对随便一边操作一次单独的 $0$ 就又被选了，连续 $1$ 的子串的一个端点也被选了，这个端点显然可以随便操作，然后就强行操作就可以填满这个子串，所以中间有就行，当然除了 `101` 这一种段，显然显然两边都选，中间不选，要么中间选，两边想选就选，不想选就不选。

其它的中间都必须选一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int ans;
string s;
int p[1000009];
void jc(int l,int r){
	bool fl;
	fl=0;
	for(int i=l;i<=r;i++){
		if(s[i]=='0'){
			fl=1;
		}
	}
	if(!fl){
		for(int i=l;i<=r;i++){
			ans+=p[i];
		}
	}else{
		if(r-l+1==3){
			ans+=min(p[l]+p[r],p[l+1]+min(p[l],0ll)+min(p[r],0ll));
			return;
		}
		if(p[l]<0){
			ans+=p[l];
		}
		if(p[r]<0){
			ans+=p[r];
		}
		fl=0;
		for(int i=l+1;i<r;i++){
			if(p[i]<0){
				fl=1;
				ans+=p[i];
			}
		}
		if(!fl){
			int mi;
			mi=1e16;
			for(int i=l+1;i<r;i++){
				mi=min(p[i],mi);
			}
			ans+=mi;
		}
	}
}
void _main(){
	ans=0;
	cin>>n;
	cin>>s;
	s='.'+s;
	s+='0';
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	int l,r;
	l=r=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			r=i;
			if(l==0){
				l=i;
			}
		}
		if((i==n||(s[i]=='0'&&s[i+1]=='0'))&&l!=0){
			jc(l,r);
			l=0;
		}
	}
	cout<<ans<<endl;
}
signed main(){
	int c,t;
	cin>>c>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：_wsq_ (赞：1)

首先，我们注意到如果相邻两个数字都在 $A$ 中，那么无论如何操作，这两个数字最后一定会有至少一个仍在 $A$ 中。因此，如果 $s$ 中有相邻的两个 $0$，那么这两个位置一定不会被选入到 $A$ 中。由此，我们可以对 $s$ 进行分段，每一段的两端都是 $1$，段与段之间彼此独立。

然后，如果某一段里只有 $1$，那么答案就是这一段的 $p$ 之和，这是因为操作以后被操作的位置一定不在 $A$ 当中，所以我们不能对这一段进行操作。

对于一般的情况，我们首先考虑两端是不能操作的，所以如果两端满足 $p<0$，那么我们就直接将两端的 $p$ 加入答案中，后面就不用考虑两端了。然后，我们可以发现，无论初始的时候中间的哪个位置被选入到 $A$ 中，我们都可以不断进行操作使得最终只有一个位置没有被选，然后就可以调整这个位置到任意一个 $s=0$ 的位置。而剩下的 $s=0$ 的位置也很好处理，只需要进行一次操作就够了（因为第一步的分段保证了不会有相邻的两个 $0$）。

当然，也有一个例外：`101`。我们特判掉即可。

代码：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
#define maxn 100005
#define int long long
int n,p[maxn],ans;
string s;
signed main(){
    int c,t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>c>>t;
    while(t--){
        cin>>n>>s;
        for(int i=1;i<=n;i++){
            cin>>p[i];
        }
        int last=0;
        for(int i=1;i<=n+1;i++){
            if((i>n||s[i-1]=='0'&&(i==n||s[i]=='0'))&&last){
                if(i-last==1){
                    ans+=p[last];
                    last=0;
                    continue;
                }
                if(i-last==2){
                    ans+=p[last]+p[i-1];
                    last=0;
                    continue;
                }
                if(i-last==3&&s[last]=='0'){
                    ans+=min(p[last]+p[i-1],p[last+1]+min(p[last],0ll)+min(p[i-1],0ll));
                    last=0;
                    continue;
                }
                if(p[last]<0){
                    ans+=p[last];
                }
                if(p[i-1]<0){
                    ans+=p[i-1];
                }
                int sum1=0,sum2=0,minp=0x3f3f3f3f3f3f3f3f;
                bool all=true;
                for(int j=last+1;j<i-1;j++){
                    if(p[j]<0){
                        sum1+=p[j];
                    }
                    sum2+=p[j];
                    minp=min(minp,p[j]);
                    if(s[j-1]=='0'){
                        all=false;
                    }
                }
                if(all){
                    ans+=sum2;
                    if(p[last]>0){
                        ans+=p[last];
                    }
                    if(p[i-1]>0){
                        ans+=p[i-1];
                    }
                    last=0;
                    continue;
                }
                if(minp>0){
                    ans+=minp;
                }
                else{
                    ans+=sum1;
                }
                last=0;
            }
            if(s[i-1]=='1'&&!last){
                last=i;
            }
        }
        cout<<ans<<'\n';
        ans=0;
    }
    return 0;
}
```

---

