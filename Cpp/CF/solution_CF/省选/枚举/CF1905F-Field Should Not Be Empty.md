# Field Should Not Be Empty

## 题目描述

You are given a permutation $ ^{\dagger} $ $ p $ of length $ n $ .

We call index $ x $ good if for all $ y < x $ it holds that $ p_y < p_x $ and for all $ y > x $ it holds that $ p_y > p_x $ . We call $ f(p) $ the number of good indices in $ p $ .

You can perform the following operation: pick $ 2 $ distinct indices $ i $ and $ j $ and swap elements $ p_i $ and $ p_j $ .

Find the maximum value of $ f(p) $ after applying the aforementioned operation exactly once.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ p = [1,2,3,4,5] $ and $ f(p)=5 $ which is already maximum possible. But must perform the operation anyway. We can get $ f(p)=3 $ by choosing $ i=1 $ and $ j=2 $ which makes $ p = [2,1,3,4,5] $ .

In the second test case, we can transform $ p $ into $ [1,2,3,4,5] $ by choosing $ i=1 $ and $ j=2 $ . Thus $ f(p)=5 $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
5
2 1 3 4 5
7
2 1 5 3 7 6 4
6
2 3 5 4 1 6
7
7 6 5 4 3 2 1```

### 输出

```
3
5
2
3
2```

# 题解

## 作者：I_am_Accepted (赞：3)

除了排序好的答案为 $n-2$，其他必定交换更优。

不妨设交换使得 $i$ 位置变得合法：

* 交换位置不含 $i$，则必然是 $i$ 位置前恰有一个值比它大，同时后面恰有一个比它小，将这两个位置交换了。
* 交换位置含 $i$，则必然是 $i,a_i$ 这两个位置交换了。

综上至多 $2n$ 种交换，求答案取最大值即可。可以用 `std::map` 维护第一类交换中间有多少位置会变为合法。

什么时候能想到枚举一个变得合法的位置来讨论。

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

给定一个排列 $p$，定义 $p_i$ 是好的，当且仅当前面的数都比它小，后面的数都比它大。你必须交换两个位置上的数，求最大的好的数的个数。

## 题目分析

先求出初始的数量，考虑交换的数对答案的影响。

计算每个数会对哪些操作 $p_l,p_r$ 产生贡献。

如果 $p_i$ 已经是好的了，则如果 $l\le i\le r$，就会产生 $-1$ 的贡献，事实上我们不可能会这样交换，因为我们不会选择非逆序对交换。

如果 $p_i$ 不是好的。有两种情况，一种是当前正好差 $1$ 对数不满足，而交换的就是这对数，产生 $1$ 的贡献。另一种是 $p_i$ 与 $p_{p_i}$ 交换，且交换后变成了好的数。

贡献为 $1$ 的数只会带来 $O(n)$ 组可能的交换，复杂度 $O(n\log n)$，瓶颈在于 map，精细实现的话其它内容可以达到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define Pi pair<int,int>
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N =2e5+5,inf=(1LL<<31)-1;
int n,p[N],mx[N],a[N],w[N],mxp[N],t[N],ans;
inline void add_(int x){
	while(x<=n)t[x]++,x+=x&-x;
}
inline int query(int x){
	int ans=0;
	while(x)ans+=t[x],x-=x&-x;
	return ans;
}
map<Pi,int>P;
inline void Main(){
	P.clear(),n=read(),ans=0;
	repn(i)p[i]=read(),t[i]=0,a[p[i]]=i,mx[i]=max(mx[i-1],p[i]);
	repn(i)mxp[i]=max(mxp[i-1],a[i]);
	repn(i){
		add_(p[i]);
		if(p[i]==i){
			if(mx[i]==i)ans++;
			if(query(i)==i-1)P[{a[mx[i]],mxp[i]}]++;
		}else if(p[i]>i){
			if(mx[p[i]]==p[i])P[{i,p[i]}]++;
		}else if(mxp[p[i]-1]==p[i]-1)P[{p[i],i}]++;
	}
	int Mx=-2;
	for(auto y:P)Mx=max(Mx,y.second);
	cout <<ans+Mx<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1905F)

[也许更好的阅读体验](https://www.cnblogs.com/tx-lcy/p/17929115.html)

一种比较暴力的做法，不需要观察任何性质。

## 思路

首先特判一下 $\forall i,p_i=i$ 的情况，输出 $n-2$，不难发现剩下的情况必定需要交换两个数。

首先考虑**设 $a_i$ 表示 $i$ 左边比 $p_i$ 大的数的个数与 $i$ 右边比 $p_i$ 小的数的个数之和**，$a$ 数组可以用树状数组简单求出。

我们发现此时的 $f(p)$ 值即为满足 $a_i=0$ 的  $i$ 的个数。

**考虑若交换 $i,j$，此时的 $a$ 数组会如何变化。**

设 $A=p_i,B=p_j$，不难发现**交换仅会在 $A>B$ 时发生**，且此时受到影响的位置必然 $\in [i,j]$。

我们先不考虑 $a_i$ 和 $a_j$ 的变化，只考虑 $(i,j)$ 内的数。

首先计算交换 $A,B$ 后对每个位置左边比它大的数的个数的影响，不难发现会令 $p_k \in (B,A)$ 的所有 $a_k$ 减一。

然后计算交换 $A,B$ 后对每个位置右边比它小的数的个数的影响，不难发现会令 $p_k \in (B,A)$ 的所有 $a_k$ 减一。

**所以我们操作 $i,j$ 对所有区间 $(i,j)$ 内的数的影响是令所有满足 $p_k \in (p_j,p_i)$ 的 $a_k$ 减二。**

接着特殊处理一下端点的贡献，不难发现 $p_i$ 想要满足条件必须得从位置 $i$ 被交换到位置 $p_i$，这些位置一共只有 $n$ 种，扫到的时候判一下就行了。

接下来我们继续尝试转化原问题。

**不难发现，我们操作的 $i,j$ 一定满足 $p_i$ 是前缀最大值，$p_j$ 是后缀最小值。**

那么考虑扫描线，由于 $p_i$ 递增，所以我们每次把上一个前缀最大值到当前前缀最大值之间的所有数扫入线段树内，同时每次把不满足条件的数踢出。此时已经消去了一维，由于每个数只会被加入一次，**当某个数被加入的时候我们二分一下它可以对哪些后缀最小值产生贡献，然后在线段树上区间加就行了。**

至此，本题成功被解决，时间复杂度 $\mathcal O(n \log n)$。

## 代码

[提交记录](https://codeforces.com/contest/1905/submission/238939989)

---

## 作者：MiniLong (赞：2)

因为 $p$ 是个排列，所以好的数 $x$ 所在的位置也必定是 $x$，前 $x - 1$ 个数是 $1$ 到 $x - 1$ 的一个排列。设 $pmax_i$ 为前 $i$ 中最大的值的下标，$smin_i$ 为 $i$ 到 $n$ 最小值的下标所以 $p_i$ 是好的，当且仅当 $\max\limits_{j=1}^{i-1} p_j =i-1,p_i=i$，即 $a_{pmax_{i-1}} = i-1,p_i=i$

然后考虑哪些操作是优的，也就是怎么尽量去增加个数。

- 交换 $i,p_i$。这样肯定能使 $a_{p_i}$ 这个数满足 $a_{p_i}=p_i$，有可能增加。

- $p_i=i,i>1$，交换 $pmax_{i-1},smin_i$，当 $a_{pmax_{i-1}} > a_{smin_i}$ 时，可以使 $[pmax_{i-1} + 1,smin_i -1]$ 中的某些数变好。

考虑树状数组维护这个操作，可以先找出所有好的位置和前面 **仅有一个** 比它大且 $p_i=i$ 的位置，开两个树状数组，把它们分别塞进去，价值都是 $1$。交换 $l,r$ 时，它减去的贡献就是 $\forall l<i<r,a_l<i,a_r>i$ 且 $a_i$ 是好的，可以在好的位置的树状数组中求出 $[\max(l+1,a_l +1),\min(r-1,a_r -1)]$ 这段区间好的个数减去即可。加的贡献类似，$\forall l<i<r,a_l>i,a_r<i$ 且 $i$ 是第二类的数，那么在第二类的数的树状数组中求出 $[\max(l+1,a_r+1,\min(r-1,a_l-1)]$ 这段区间中第二类数的个数就行。然后 $l,r$ 两点可以手动更新一下，依照定义就行，但注意 $pmax_{r-1}$ 可能会随 $l,r$ 交换改变。

---

## 作者：huangrenheluogu (赞：1)

除了 $a_i=i$ 的情况，其他情况都会在原基础上增加，所以上面的情况先特判。

枚举 $i$，用小/大根堆可以维护左边缺了什么或者右边多了什么。

如果都只有一样，就可以交换，并且贡献加一，这个贡献用 map 维护一下就可以了。

我的做法就是开一个 $b$ 数组记录左边需要和什么交换，遇到右边的时候再判断一下是否可以交换。

注意交换没有交换 $i$ 这个数的时候需要判断 $i$ 是不是和 $a_i$ 相等，不然没有贡献。

注意如果一边扫过来另一边需要换、一边扫过来发现不需要换，就是说明这个位置需要和别人换才可以产生贡献。

[code](https://codeforces.com/contest/1905/submission/237681584)

---

## 作者：daniEl_lElE (赞：0)

对于一个初始就是好的点 $i$，只有交换的两个位置 $x,y$ 满足 $x,y<i$ 或 $x,y>i$ 才可能继续成为好的。

对于其余的 $p_i=i$ 的位置，如果前缀只有一个位置满足 $p_j>i$（容易发现此时后缀只有一个位置满足 $p_k<i$），交换 $p_j,p_k$ 可以让这个位置变成好。

对于 $p_i\neq i$ 的情况，显然只有交换 $p_i,i$ 才有可能让 $i$ 位置变为好的，至于到底是不是好的可以预处理初始每个前缀和后缀是否是好的。

容易发现除了第一类以外，最多有 $O(n)$ 个交换会提供好的位置。把所有符合要求的 $x,y$ 扔到 map 里面，对于每个分别统计一下即可。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
int ff[1000005],ok[1000005],pre[1000005],tag1[1000005],tag2[1000005],p[1000005];
map<pair<int,int>,int> mp; 
void solve(){
	mp.clear();
	int n; cin>>n; for(int i=1;i<=n;i++) ff[i]=ok[i]=pre[i]=tag1[i]=tag2[i]=p[i]=0;
	int a[n+1],cnt=0; for(int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
	priority_queue<int,vector<int>,greater<int>> pq;
	for(int i=1;i<=n;i++){
		if(a[i]<=i) cnt++;
		else pq.push(a[i]);
		while(!pq.empty()&&pq.top()==i) cnt++,pq.pop();
		ok[i]=cnt;
		if(pq.size()==1) tag1[i]=pq.top();
	}
	priority_queue<int> pq2;
	for(int i=n;i>=1;i--){
		if(a[i]<i) pq2.push(a[i]);
		while(!pq2.empty()&&pq2.top()==i) pq2.pop();
		if(pq2.size()==1) tag2[i]=pq2.top();
	}
	for(int i=1;i<=n;i++) if(a[i]==i) if(ok[i]==i) pre[i]=1;
	for(int i=1;i<=n;i++) pre[i]+=pre[i-1];
	for(int i=1;i<=n;i++){
		if(a[i]==i){
			if(ok[i]!=i){
				if(ok[i]==i-1){
					mp[make_pair(p[tag1[i]],p[tag2[i]])]++;
				}
			}
		}
		else{
			if(a[i]>i){
				if(ok[a[i]]==a[i]){
					mp[make_pair(i,a[i])]++;
				}
			}
			else{
				if(ok[a[i]-1]==a[i]-1){
					mp[make_pair(a[i],i)]++;
				}
			}
		}
	}
	int maxv=max(pre[n-2],pre[n]-pre[2]);
	for(auto v:mp){
		int x=v.first.first,y=v.first.second;
		maxv=max(maxv,pre[x-1]+pre[n]-pre[y]+v.second);
	}
	cout<<maxv<<"\n";
}
signed main(){
	int t; cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

一个点 good 的条件就是 $a_i = i$，且小于其的数都在其左侧，大于其的数都在其右侧。

首先如果已经是单位排列了，那么答案是 $n-2$，我们特判掉这种情况。

首先有一个重要结论，我们不会把一个小的数交换到大的数后面去，因为显然这不会让答案变好。

同理，把一个大的数放到后面去不可能会让答案变差，所以最初 good 的点操作完肯定还是 good 的。

我们只能交换一次，其实可以发现我们的选择是有限的。

我们会进行的操作只有两种可能：
1. 操作 $a,b$，会让 $a,b$ 中间的某个位置变 good；
2. 操作 $a,b$，会让 $a,b$ 其中某个点本身变 good。

对于某个点,如果已经满足 $a_i = i$，我们看一下它的前面都多少个数大于它，如果没有，那么已经满足要求；如果有一个，我们可以找到需要交换的位置，记录下来，否则不可能在一次操作内让这个点变 good，我们忽略即可。

如此我们就可以维护每个操作的贡献，用 map 记录，因为每个点最多只会对应一个有效的操作，所以有效操作数量最多有 $n$ 次。

然后就是对于让本身变 good 的方案，我们同样枚举一下就行，数量也是 $n$ 个，可以用线段树解决。
## Code
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<numeric>
#include<functional>
#include<map>
using namespace std;
using LL = long long;

const int INF = 1e9;
struct Info {
    int mn = INF, mx = -INF;
};

Info operator+(const Info &a, const Info &b){
    return {min(a.mn, b.mn), max(a.mx, b.mx)};
}

template<class Info>
struct SegmentTree{
    int n;
    vector<Info> info;

    SegmentTree() {}

    SegmentTree(int n, Info _init = Info()){
        init(vector<Info>(n, _init));
    }

    SegmentTree(const vector<Info> &_init){
        init(_init);
    }

    void init(const vector<Info> &_init){
        n = (int)_init.size();
        info.assign((n << 2) + 1, Info());
        function<void(int, int, int)> build = [&](int p, int l, int r){
            if (l == r){
                info[p] = _init[l - 1];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }

    void pull(int p){
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void modify(int p, int l, int r, int x, const Info &v){
        if (l == r){
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x <= m){
            modify(2 * p, l, m, x, v);
        } 
        else{
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v){
        modify(1, 1, n, p, v);
    }

    Info query(int p, int l, int r, int x, int y){
        if (l > y || r < x){
            return Info();
        }
        if (l >= x && r <= y){
            return info[p];
        }
        int m = (l + r) / 2;
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m + 1, r, x, y);
    }

    Info query(int l, int r){
        return query(1, 1, n, l, r);
    }
};

template<typename T>
struct Fenwick{
    int n;
    vector<T> tr;

    Fenwick(int n) : n(n), tr(n + 1, 0){}

    int lowbit(int x){
        return x & -x;
    }

    void modify(int x, T c){
        for(int i = x; i <= n; i += lowbit(i)) tr[i] += c;
    }

    void modify(int l, int r, T c){
        modify(l, c);
        if (r + 1 <= n) modify(r + 1, -c);
    }

    T query(int x){
        T res = T();
        for(int i = x; i; i -= lowbit(i)) res += tr[i];
        return res;
    }

    T query(int l, int r){
        return query(r) - query(l - 1);
    }

    int find_first(T sum){
        int ans = 0; T val = 0;
        for(int i = __lg(n); i >= 0; i--){
            if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] < sum){
                ans |= 1 << i;
                val += tr[ans];
            }
        }
        return ans + 1;
    }

    int find_last(T sum){
        int ans = 0; T val = 0;
        for(int i = __lg(n); i >= 0; i--){
            if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] <= sum){
                ans |= 1 << i;
                val += tr[ans];
            }
        }
        return ans;
    }

};
using BIT = Fenwick<int>;

int main(){

#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n + 1), pos(n + 1);
        vector<Info> init(n);
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            pos[a[i]] = i;
            init[a[i] - 1] = {i, i};
        }
        if (is_sorted(a.begin() + 1, a.end())){
            cout << n - 2 << '\n';
            continue;
        }
        vector<int> pre(n + 2), suf(n + 2, INF);
        for(int i = 1; i <= n; i++){
            pre[i] = max(pre[i - 1], a[i]);
        }
        for(int i = n; i >= 1; i--){
            suf[i] = min(suf[i + 1], a[i]);
        }

        map<pair<int, int>, int> mp;
        vector<int> good;
        BIT bit(n);
        for(int i = 1; i <= n; i++){
            if (a[i] == i && pre[i - 1] < i && suf[i + 1] > i){
                good.push_back(i);
            }
            if (a[i] == i && bit.query(a[i]) == i - 2){
                int l = pre[i - 1], r = suf[i + 1];
                mp[minmax(pos[l], pos[r])] += 1;
            }
            bit.modify(a[i], 1);
        }

        SegmentTree<Info> seg(init);
        vector<bool> v(n + 1);

        auto check = [&](int x){
            return seg.query(1, x - 1).mx < x && seg.query(x + 1, n).mn > x;
        };

        for(int i = 1; i <= n; i++){
            if (a[i] != i && !v[i]){
                seg.modify(i, {i, i});
                seg.modify(a[i], {pos[i], pos[i]});
                if (pos[i] == a[i]){
                    v[i] = v[pos[i]] = true;
                    if (check(i)) mp[minmax(i, pos[i])] += 1;
                    if (check(pos[i])) mp[minmax(i, pos[i])] += 1;
                }
                else{
                    v[i] = true;
                    if (a[i] > i && i > pos[i]){

                    }
                    else if (a[i] < i && i < pos[i]){

                    }
                    else{
                        if (check(i)) mp[minmax(i, pos[i])] += 1;
                    }
                }
                seg.modify(i, {pos[i], pos[i]});
                seg.modify(a[i], {i, i});
            }
        }
        
        int ans = 0;
        for(auto [x, y] : mp){
            ans = max(ans, y);
        }
        cout << ans + good.size() << '\n';
    }

}
```

---

## 作者：shinkuu (赞：0)

*2600？*2100！

考虑一个位置 $i$，考虑什么时候交换 $x,y(x<y)$ 位置的数，它会对答案有 $1$ 的贡献。

- $\sum_{j<i}[p_j>p_i]>1$ 或 $\sum_{j>i}[p_j<p_i]>1$。

显然这种情况下是不可能使 $i$ 有贡献的。

- $\exist j<i,p_j>p_i$ 且 $\exist j>i,p_j<p_i$。

此时当且仅当交换这两个 $j$ 的位置时，会使 $i$ 有贡献。

- 否则。

无法通过交换两个不为 $i$ 的位置使 $i$ 产生贡献。

还有一种情况：交换了 $i$ 和另一个位置，使得 $i$ 有贡献。

记录 $pl_i$ 表示最大的 $j$ 使得 $p_j<p_i$，$pr_i$ 表示最小的 $j$ 使得 $p_j>p_i$。则当 $pl_i<pr_i$ 时：

- $i<pl_i$。

交换 $i$ 和 $pl_i$ 使其有贡献。

- $i>pr_i$。

交换 $i$ 和 $pr_i$ 使其有贡献。

以上就是所有可能新增贡献的情况。但是原本有贡献的位置会不会变没有呢？

显然不会，因为我们不会交换 $x,y(p_x<p_y)$。

除非？

除非整个序列升序。特判即可。

至于维护上面的东西，第一部分用一个 set 再扫描线一下。第二部分是一个值域上的前缀 $\max$ 后缀 $\min$。再用一个 map 记录所有有贡献的 $x,y$，如果没有一个 $x,y$ 则说明原序列升序，特判。

code：

```cpp
int n,m,a[N],b[N],f[N],g[N],pf[N],pg[N];
map<pii,int> c;
set<pii> st;
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]),b[a[i]]=i;
	st.clear();
	rep(i,1,n){
		if(st.size()>1&&prev(prev(st.end()))->fi>a[i])f[i]=-1;
		else if(st.size()&&prev(st.end())->fi>a[i])f[i]=prev(st.end())->se;
		else f[i]=0;
		st.emplace(a[i],i);
	}
	st.clear();
	drep(i,n,1){
		if(st.size()>1&&next(st.begin())->fi<a[i])g[i]=-1;
		else if(st.size()&&st.begin()->fi<a[i])g[i]=st.begin()->se;
		else g[i]=0;
		st.emplace(a[i],i);
	}
	int sum=0;c.clear();
	rep(i,1,n){
		if(f[i]>0&&g[i]>0)c[Mp(f[i],g[i])]++;
		if(!f[i]&&!g[i])sum++;
	}
	pf[1]=b[1],pf[0]=0;
	rep(i,2,n)pf[i]=max(b[i],pf[i-1]);
	pg[n]=b[n],pg[n+1]=n+1;
	drep(i,n-1,1)pg[i]=min(b[i],pg[i+1]);
	rep(i,1,n){
		if(pf[i-1]>pg[i+1]||i>pf[i-1]&&i<pg[i+1])continue;
		if(i<=pf[i-1])c[Mp(b[i],pf[i-1])]++;
		else c[Mp(pg[i+1],b[i])]++;
	}
	int ans=-2;
	for(auto i:c)ans=max(ans,i.se);
	printf("%d\n",ans+sum);
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：happybob (赞：0)

特判如果排列初始时是 $1,2,\cdots,n$，输出 $n-2$。

如果不是，那么我们交换两个后的结果一定大于等于初始值。

考虑新增的贡献是什么？假设交换 $p_i,p_j(i < j)$，那么新增的贡献必然是一个 $k \in [i,j]$，交换前 $k$ 不是好的，交换后是好的。

注意到位置 $i$ 是好的的必要条件是 $p_i=i$。

考虑枚举上文的 $k$。接着考虑交换的 $i,j$ 会怎么样。

第一种可能是，$i=k$ 或 $j=k$。那么根据必要条件，我们知道换的一定是 $i$ 和 $p_i$ 这两个位置。

第二种，$i \neq k$ 且 $j \neq k$，那么交换的必然是 $[1,i)$ 中的最大值点和 $(i,n]$ 中的最小值点，证明显然。

然后现在有 $O(n)$ 对 $(i,j)$，每一对算贡献都可以讨论贡献然后前缀和做到 $O(1)$。预处理有个 $O(n \log n)$ 的复杂度，但是可能可以优化？但是我们避开了树状数组或线段树等数据结构！

```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#pragma GCC target("avx,sse,sse2,sse3,popcnt")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <vector>
using namespace std;

const int N = 2e5 + 5;

int t, n, p[N];
int minn[N], maxn[N];
bool g[N], f[N];
int sf[N], sg[N];
int ra[N];

inline int query(int l, int r)
{
	if (l > r) swap(l, r);
	int nl = l + 1, nr = r - 1;
	nl = max(nl, p[r] + 1);
	nr = min(nr, p[l] - 1);
	int res = 0;
	if (nl <= nr)
	{
		res += sg[nr] - sg[nl - 1];
	}
	res -= (sf[r - 1] - sf[l]);
	res -= f[l];
	res -= f[r];
	res += (p[l] == r && (maxn[r - 1] == r) && (p[r] <= r - 1));
	res += (p[r] == l && maxn[l - 1] == l - 1);
	return res;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		int sum = 0;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> p[i], g[i] = f[i] = 0, ra[p[i]] = i;
		maxn[1] = p[1];
		for (int i = 2; i <= n; i++) maxn[i] = max(maxn[i - 1], p[i]);
		minn[n + 1] = (int)1e9;
		for (int i = n; i >= 1; i--) minn[i] = min(minn[i + 1], p[i]);
		if (is_sorted(p + 1, p + n + 1))
		{
			cout << n - 2 << "\n";
			continue;
		}
		set<int> s1;
		for (int i = 1; i <= n; i++)
		{
			f[i] = (p[i] == i) && (maxn[i - 1] == i - 1);
			g[i] = (p[i] == i) && (!s1.empty()) && (s1.upper_bound(p[i]) == --s1.end());
			s1.insert(p[i]);
			sum += f[i];
			sf[i] = sf[i - 1] + f[i];
			sg[i] = sg[i - 1] + g[i];
		}
		int ans = sum;
		for (int i = 1; i <= n; i++)
		{
			if (g[i])
			{
				ans = max(ans, sum + query(ra[maxn[i - 1]], ra[minn[i + 1]]));
			}
			if (p[i] != i) ans = max(ans, sum + query(i, p[i]));
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

