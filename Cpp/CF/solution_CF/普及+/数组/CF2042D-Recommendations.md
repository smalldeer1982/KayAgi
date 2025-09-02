# Recommendations

## 题目描述

有 $n$ 个区间 $S_i=[l_i,r_i]$，对于每个区间求出 $|\bigcap\limits_{j} S_j|-|S_i|$，其中 $j\neq i$，且 $S_i\subseteq S_j$。即对于每个区间求出其包区间交集的大小，并减去自己的大小。

## 样例 #1

### 输入

```
4
3
3 8
2 5
4 5
2
42 42
1 1000000000
3
42 42
1 1000000000
42 42
6
1 10
3 10
3 7
5 7
4 4
1 2```

### 输出

```
0
0
1
999999999
0
0
0
0
0
2
3
2
4
8```

# 题解

## 作者：Eddie08012025 (赞：10)

## 思路
显然的，对于所有完全包含区间 $i$ 的交集，就是所有区间中最大的 $l$ 到最小的 $r$，$(l,r)$ 即为区间交集。

下面以求最小的 $r$ 为例。

对所有区间进行排序，以左端点为第一关键字从小到大排序，右端点为第二关键字从大到小排序。

考虑使用可以保证单调性的容器 set 处理所有区间中最小的 $r$，set 中存储 $r$ 的值。

对于排序后的第 $i$ 个区间，一定保证前面的 $l$ 一定不大于 $l_i$，后面的区间不会有能完全包含 $i$ 区间的区间，所以考虑前面的区间中不小于 $r_i$ 的最小的 $r$ 即可，因为单调性所以可以用二分的方式处理。

在排序前用 map 存储每个区间的编号，用 $rmn_i$ 存储能完全包含 $i$ 区间的所有区间的最小右端点。

处理最大的 $l$ 方法类似，仅需以右端点为第一关键字从大到小排序，左端点为第二关键字从小到大排序即可，用 $lmx_i$ 存储能完全包含 $i$ 区间的所有区间的最大左端点。

最后对于每个区间，输出 $rmn_i-r_i+l_i-lmx_i$。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,l[200005],r[200005],lmx[200005],rmn[200005];
pair<int,int>z[200005],p[200005];
map<pair<int,int>,int>mp;
bool cmd(pair<int,int>aa,pair<int,int>bb){
	if(aa.first!=bb.first){
		return aa.first<bb.first;
	}else return aa.second>bb.second;
}bool cmp(pair<int,int>aa,pair<int,int>bb){
	if(aa.first!=bb.first){
		return aa.first>bb.first;
	}else return aa.second<bb.second;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			l[i]=r[i]=rmn[i]=lmx[i]=0;
			cin>>z[i].first>>z[i].second;
			l[i]=z[i].first;
			r[i]=z[i].second;
			p[i]={z[i].second,z[i].first};
			mp[z[i]]=i;
			mp[p[i]]=i;
		}sort(z+1,z+n+1,cmd);
		sort(p+1,p+n+1,cmp);
		set<int>s;
		set<int,greater<int> >s1;
		for(int i=1;i<=n;i++){
			auto a=s.lower_bound(z[i].second);
			rmn[mp[z[i]]]=*a;
			s.insert(z[i].second);
		}for(int i=1;i<=n;i++){
			auto a=s1.lower_bound(p[i].second);
			lmx[mp[p[i]]]=*a;
			s1.insert(p[i].second);
		}for(int i=1;i<=n;i++){
			if(lmx[i]>l[i]||rmn[i]<r[i])cout<<"0\n";
			else cout<<rmn[i]-r[i]+l[i]-lmx[i]<<"\n"; 
		}
	}
	return 0;
}
```

---

## 作者：Austin0116 (赞：7)

# 分析
首先，所有包含第 $i$ 个区间中最小的 $r$ 减去最小的 $l$ 就是这个答案。

首先，对序列进行排序：先由左端点从小到大排序，再由右端点从大到小进行排序。

排序后再将右端点依次插入 set 中，可用二分找到最小的大于等于右端点的 $r$，两者之差即是右端点的贡献。

然后处理左端点。我们只需要将每个区间翻转到数轴的负方向，例如 $(1,2)$ 就会变成 $(-2,-1)$，然后重复上面两个操作就可以了，因为翻转后的左端点已经成为了右端点。

两次操作之和即是最后答案。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
set<int> s;
int t,n,ans[200005];
struct ha{
	int l,r,id;
	inline bool operator < (const ha &o) const{//排序
		if(l!=o.l) return l<o.l;
		return r>o.r;
	}
};
ha a[200005];
char ch;
inline void read(int &x){
	x=0;
	while(ch<48||ch>57) ch=getchar();
	while(ch>=48&&ch<=57){
		x=x*10+(ch^48);
		ch=getchar();
	}
}
void write(int x){
	if(x>9) write(x/10);
	putchar((x%10)^48);
}
int main(){
	read(t);
	while(t--){
		read(n);
		for(int i=1;i<=n;i++){
			read(a[i].l);read(a[i].r);
			a[i].id=i;
		}
		sort(a+1,a+1+n);
		s.insert(a[1].r);
		for(int i=2;i<=n;i++){//处理右端点
			if(!(i!=n&&a[i].l==a[i+1].l&&a[i].r==a[i+1].r)&&!(a[i].l==a[i-1].l&&a[i].r==a[i-1].r)){//判重叠
				auto p=s.lower_bound(a[i].r);
				if(p!=s.end()) ans[a[i].id]+=((*p)-a[i].r);
			}
			s.insert(a[i].r);
		} 
		for(int i=1;i<=n;i++){//翻转到数轴的负方向
			a[i].l=-a[i].l;
			a[i].r=-a[i].r;
			swap(a[i].l,a[i].r);
		}
		sort(a+1,a+1+n);
		s.clear();
		s.insert(a[1].r);
		for(int i=2;i<=n;i++){//处理左端点
			if(!(i!=n&&a[i].l==a[i+1].l&&a[i].r==a[i+1].r)&&!(a[i].l==a[i-1].l&&a[i].r==a[i-1].r)){
				auto p=s.lower_bound(a[i].r);
				if(p!=s.end()) ans[a[i].id]+=((*p)-a[i].r);
			}
			s.insert(a[i].r);
		}
		for(int i=1;i<=n;i++){
			write(ans[i]);
			putchar('\n');
			ans[i]=0;
		} 
		s.clear();
	}
	return 0;
}
```

---

## 作者：Hide_In_The_Shadow (赞：5)

被 $C$ 卡太久导致没写出来的好题。。。

看到有大佬说 CDQ 和二维数点，但是蒟蒻不会。

对于一个一条线段，找到所有完全覆盖它的线段，找到其交集，交集长度减去当前线段长度即为答案。

注意到不是询问额外的区间，而是求给定了的线段之间的关系。

那么，我们可以这样操作，将序列先按 $l$ 排序，对于当前线段 $i$，找到满足 $l_j\leq l_i$ 且 $r_j\geq r_i$ 的最小的 $r_j$，记为 $R_i$。同理，按 $r$ 排序后找到满足条件的最大的 $l_j$，记为 $L_i$。则 $R_i-L_i-r_i+l_i$ 即为答案，具体的，我们可以用 `multiset` 实现。

时间复杂度 $O(n\log(n))$。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n,l[N],r[N];
struct seg{
    int l,r,id;
}a[N];
bool cmp0(seg a,seg b){
    return a.l<b.l;
}
bool cmp1(seg a,seg b){
    return a.r<b.r;
}
multiset<int>s;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i].l>>a[i].r,a[i].id=i;
        sort(a+1,a+n+1,cmp0);
        s.clear();
        int pre=0;
        for(int i=1;i<=n;++i){
            pre=i;
            s.insert(a[i].r);
            while(i+1<=n&&a[i+1].l==a[i].l)s.insert(a[++i].r);
            for(int j=pre;j<=i;++j){
                auto it=s.lower_bound(a[j].r);
                it++;
                if(it!=s.end())r[a[j].id]=*it;
                else r[a[j].id]=-1;
                //cout<<a[j].id<<' '<<a[j].r<<' '<<r[a[j].id]<<'\n';
            }
        }
        s.clear();
        sort(a+1,a+n+1,cmp1);
        for(int i=n;i>=1;--i){
            pre=i;
            s.insert(a[i].l);
            while(i-1>0&&a[i-1].r==a[i].r)s.insert(a[--i].l);
            for(int j=i;j<=pre;++j){
                auto it=s.upper_bound(a[j].l);
                it--,it--;
                if(it!=s.end())l[a[j].id]=(*it)+a[j].r-a[j].l+1;
                else l[a[j].id]=-1;
                //cout<<a[j].id<<' '<<a[j].r<<' '<<r[a[j].id]<<'\n';
            }
        }
        for(int i=1;i<=n;++i){
            //cout<<l[i]<<" "<<r[i]<<'\n';
            if(l[i]==-1||r[i]==-1)cout<<"0\n";
            else cout<<r[i]-l[i]+1<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：SilverLi (赞：2)

> [推一推](https://www.cnblogs.com/Silver-Wolf/p/18620985/Recommendations) \
> [题目传送门](https://www.luogu.com.cn/problem/CF2042D)

假设要求第 $i$ 个用户的强烈推荐的曲目数。那么对于所有曲目，因为是 $i$ 的所有预测器都喜欢这首曲目才算答案，也就是求**完全包含 $i$ 的区间的交**。

那怎么算完全包含的区间呢？

可以先把这些区间 $\left [l_i, r_i \right ]$ 排序，$r$ 不一样就按 $r$ 从小到大排，$r$ 一样就按 $l$ 从大到小排，再从后往前扫。

设扫到了第 $i$ 个区间 $\left [l_i, r_i \right ]$，一个完全包含 $i$ 的区间 $j$ 满足 $l_i \ge l_j \wedge r_i \le r_j$，那么可以开两个线段树，一个存 $l$ 的最大值，一个存 $r$ 的最小值。

每算完一个答案，在第一个线段树的 $l_i$ 位置改为 $l_i$，第二个线段树的 $l_i$ 位置改为 $r_i$。

那么完全包含 $i$ 的区间 $l$ 的最大值就是第一个线段树中 $\left [1,l_i \right ]$ 的最大值，$r$ 的最小值就是第一个线段树中 $\left [1,l_i \right ]$ 的最小值，最小 $r$ 减最大 $l$ 就是答案。

note: 离散化后要特判线段树里是正无穷和负无穷。

~~为了展开 atcoder 的库函数，码长快 300 行。~~

```cpp
#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#ifdef _MSC_VER
#include <intrin.h>
#endif

#if __cplusplus >= 202002L
#include <bit>
#endif

namespace atcoder
{

    namespace internal
    {

#if __cplusplus >= 202002L

        using std::bit_ceil;

#else

        unsigned int bit_ceil(unsigned int n)
        {
            unsigned int x = 1;
            while (x < (unsigned int)(n))
                x *= 2;
            return x;
        }

#endif

        int countr_zero(unsigned int n)
        {
#ifdef _MSC_VER
            unsigned long index;
            _BitScanForward(&index, n);
            return index;
#else
            return __builtin_ctz(n);
#endif
        }

        constexpr int countr_zero_constexpr(unsigned int n)
        {
            int x = 0;
            while (!(n & (1 << x)))
                x++;
            return x;
        }

    } // namespace internal

} // namespace atcoder

namespace atcoder
{

#if __cplusplus >= 201703L

    template <class S, auto op, auto e>
    struct segtree
    {
        static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                      "op must work as S(S, S)");
        static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                      "e must work as S()");

#else

    template <class S, S (*op)(S, S), S (*e)()>
    struct segtree
    {

#endif

    public:
        segtree() : segtree(0) {}
        explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
        explicit segtree(const std::vector<S> &v) : _n(int(v.size()))
        {
            size = (int)internal::bit_ceil((unsigned int)(_n));
            log = internal::countr_zero((unsigned int)size);
            d = std::vector<S>(2 * size, e());
            for (int i = 0; i < _n; i++)
                d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--)
            {
                update(i);
            }
        }

        void set(int p, S x)
        {
            assert(0 <= p && p < _n);
            p += size;
            d[p] = x;
            for (int i = 1; i <= log; i++)
                update(p >> i);
        }

        S get(int p) const
        {
            assert(0 <= p && p < _n);
            return d[p + size];
        }

        S prod(int l, int r) const
        {
            assert(0 <= l && l <= r && r <= _n);
            S sml = e(), smr = e();
            l += size;
            r += size;

            while (l < r)
            {
                if (l & 1)
                    sml = op(sml, d[l++]);
                if (r & 1)
                    smr = op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }
            return op(sml, smr);
        }

        S all_prod() const { return d[1]; }

        template <bool (*f)(S)>
        int max_right(int l) const
        {
            return max_right(l, [](S x)
                             { return f(x); });
        }
        template <class F>
        int max_right(int l, F f) const
        {
            assert(0 <= l && l <= _n);
            assert(f(e()));
            if (l == _n)
                return _n;
            l += size;
            S sm = e();
            do
            {
                while (l % 2 == 0)
                    l >>= 1;
                if (!f(op(sm, d[l])))
                {
                    while (l < size)
                    {
                        l = (2 * l);
                        if (f(op(sm, d[l])))
                        {
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = op(sm, d[l]);
                l++;
            } while ((l & -l) != l);
            return _n;
        }

        template <bool (*f)(S)>
        int min_left(int r) const
        {
            return min_left(r, [](S x)
                            { return f(x); });
        }
        template <class F>
        int min_left(int r, F f) const
        {
            assert(0 <= r && r <= _n);
            assert(f(e()));
            if (r == 0)
                return 0;
            r += size;
            S sm = e();
            do
            {
                r--;
                while (r > 1 && (r % 2))
                    r >>= 1;
                if (!f(op(d[r], sm)))
                {
                    while (r < size)
                    {
                        r = (2 * r + 1);
                        if (f(op(d[r], sm)))
                        {
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = op(d[r], sm);
            } while ((r & -r) != r);
            return 0;
        }

    private:
        int _n, size, log;
        std::vector<S> d;

        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    };

} // namespace atcoder

#define int long long
using namespace std;
using namespace atcoder;
inline int read()
{
    int f = 0, ans = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return f ? -ans : ans;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
const int N = 4e5 + 5, M = N * 20, inf = 1e18, mod = 1e9 + 7;
int n, cnt, b[N], ans[N];
struct que
{
    int l, r, id;
    bool operator<(const que &rhs) const { return r == rhs.r ? l > rhs.l : r < rhs.r; }
} a[N];
signed main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T = read();
    while (T--)
    {
        n = read(), cnt = 0;
        for (int i = 1; i <= n; ++i)
            a[i] = {read(), read(), i},
            b[++cnt] = a[i].l, b[++cnt] = a[i].r;
        sort(a + 1, a + n + 1);
        sort(b + 1, b + cnt + 1);
        cnt = unique(b + 1, b + cnt + 1) - b - 1;
        segtree<int, [](int a, int b)
                { return max(a, b); }, []()
                { return -inf; }>
            pre(cnt + 1);
        segtree<int, [](int a, int b)
                { return min(a, b); }, []()
                { return inf; }>
            suf(cnt + 1);
        a[n + 1] = {0, 0, 0};
        for (int i = n; i; --i)
        {
            auto &[l, r, id] = a[i];
            l = lower_bound(b + 1, b + cnt + 1, l) - b;
            r = lower_bound(b + 1, b + cnt + 1, r) - b;
            if (l != a[i + 1].l || r != a[i + 1].r)
            {
                int pr = pre.prod(1, l + 1), su = suf.prod(1, l + 1);
                if (pr != -inf && su != inf)
                    ans[id] = b[su] - b[pr] - (b[r] - b[l]);
                pre.set(l, l), suf.set(l, r);
            }
            else
                ans[a[i + 1].id] = 0;
        }
        for (int i = 1; i <= n; ++i)
            write(ans[i]), putchar('\n'), ans[i] = 0;
    }
    return 0;
}
```

---

## 作者：lovely_nst (赞：2)

# [CF2042D] Recommendations

## 题意

给定 $n$ 个区间 $[l_i,r_i]$，求每个区间除自己外其他**包区间**的交的大小，然后减去自己的大小。

包区间即为包含该区间的其他区间。

## 分析

考虑转化，可以发现交的左端点是所有包区间左端点的最大值，交的右端点是所有包区间右端点的最小值，易证。

然后考虑到区间 $[l,r]$ 的包区间 $[a,b]$ 满足 $a\le l \wedge r\le b$，所以把 $n$ 个区间建点 $(l_i,r_i)$ 在平面直角坐标系上，区间 $[l,r]$ 的包区间均在 $(l,r)$ 的左上角，从上往下扫描线，从左往右加点即可。

## 细节

1. 注意到数的范围较大，所以要离散化。
2. 当两个区间完全相同时，答案均为 $0$，需要特判。

## AC Code


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n , m , l[500005] , r[500005] , a[500005];
pair <int , int> lst;
vector <pair <int , int> > p[500005];
int mn[500005] , mx[500005] , ans[500005];
void upd1 (int pos , int c){while (pos <= m){mn[pos] = min (c , mn[pos]);pos += pos & (-pos);}}
int qry1 (int pos){int ans = 1e18;while (pos){ans = min (ans , mn[pos]);pos -= pos & (-pos);}return ans;}
void upd2 (int pos , int c){while (pos <= m){mx[pos] = max (c , mx[pos]);pos += pos & (-pos);}}
int qry2 (int pos){int ans = 0;while (pos){ans = max (ans , mx[pos]);pos -= pos & (-pos);}return ans;}
signed main ()
{
	ios::sync_with_stdio (0) , cin.tie (0) , cout.tie (0);
	int t;
	cin >> t;
	while (t --){
	m = 0;
	cin >> n;
	for (int i = 1;i <= n;i ++)
		cin >> l[i] >> r[i] , a[++ m] = l[i] , a[++ m] = r[i] , ans[i] = 0;
	sort (a + 1 , a + m + 1);
	m = unique (a + 1 , a + m + 1) - a - 1;
	for (int i = 1;i <= n;i ++)
	{
		l[i] = lower_bound (a + 1 , a + m + 1 , l[i]) - a , r[i] = lower_bound (a + 1 , a + m + 1 , r[i]) - a;
		p[r[i]].push_back ({l[i] , i});
	}
	for (int i = 1;i <= m;i ++)
		sort (p[i].begin () , p[i].end ()) , mx[i] = 0 , mn[i] = 1e18;
	for (int i = m;i >= 1;i --)
	{
		lst = {0 , 0};
		for (auto j : p[i])
		{
			if (lst.first == j.first)
				ans[lst.second] = 0;
			else
			{
				int f = qry1 (j.first) , g = qry2 (j.first);
				if (g >= 1 && f <= m)
					ans[j.second] = a[qry1 (j.first)] - a[qry2 (j.first)];
				upd1 (j.first , i) , upd2 (j.first , j.first);
			}
			lst = j;
		}
		p[i].clear ();
	}
	for (int i = 1;i <= n;i ++)
		cout << max (0ll , ans[i] - a[r[i]] + a[l[i]]) << '\n';
	}
	return 0;
}
```

---

## 作者：Kotobuki_Tsumugi (赞：1)

题意可以被描述为：给定 $n$ 个区间，求每个区间的母区间的交集的长度再减掉自身的长度。

先按照左端点为第一关键字升序排序。

这样，对于排序后第 $i$ 个区间，前面的区间中如果有右端点大于 $i$ 的右端点的区间就是第 $i$ 个区间的母区间。

贡献有两部分：第 $i$ 个区间的左边和右边。

但是请注意，不管是哪部分的贡献，都建立在一个前提上：母区间的交集。

第一部分的贡献（左边）怎么求？我们需要找到一个最大的母区间左端点。

第二部分的贡献（右边）怎么求？我们需要找到一个最小的母区间右端点。

这两部分的贡献有多种求法。

1. 可以线段树二分：先离散化，记录下前缀每个数的数值的前缀和，出现次数的前缀和，这可能需要开两颗线段树。
2. 树状数组：先离散化，这种做法单次询问要 $O(\log^2n)$，不过树状数组常数小，实测和线段树没什么区别。
3. 观察到每次查询的是一段前缀，那就可以直接开 ```set``` 维护，用 ```STL``` 自带的二分单次查询 $O(\log n)$。比较好写。

代码量很不小。

复杂度 $O(n\log n+q\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5+10;
multiset<int> s;
int n,ans[N];
struct str{
	int l,r,id;
}a[N];
struct tee{
	int num,id,minn;
}tree[N<<2];
bool cmp(str a,str b){
	if(a.l == b.l) return a.r > b.r;
	else return a.l < b.l;
}
inline int ls(int p){return p << 1;}
inline int rs(int p){return (p << 1) | 1;}
void Push_up(int p){
	tree[p].num = max(tree[ls(p)].num,tree[rs(p)].num);
	tree[p].minn = min(tree[ls(p)].minn,tree[rs(p)].minn);
}
void Build(int s,int t,int p){
	if(s == t){
		tree[p].minn = a[s].r;
		tree[p].num = a[s].r;
		tree[p].id = a[s].id;
		return;
	}
	int mid = s+((t-s)>>1);
	Build(s,mid,ls(p));
	Build(mid+1,t,rs(p));
	Push_up(p);
}
tee Getnum(int l,int r,int s,int t,int p){
	if(l <= s && t <= r) return tree[p];
	int mid = s+((t-s)>>1);
	tee maxn = {0,0};
	if(l <= mid){
		tee res = Getnum(l,r,s,mid,ls(p));
		if(res.num > maxn.num) maxn = res;
	}
	if(r > mid){
		tee res = Getnum(l,r,mid+1,t,rs(p));
		if(res.num > maxn.num) maxn = res;
	}
	return maxn;
}
int Getmin(int l,int r,int s,int t,int p){
	if(l <= s && t <= r) return tree[p].minn;
	int mid = s+((t-s)>>1),res = 1e9+10;
	if(l <= mid) res = min(res,Getmin(l,r,s,mid,ls(p)));
	if(r > mid)  res = min(res,Getmin(l,r,mid+1,t,rs(p)));
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T; cin>>T;
	while(T--){
		cin>>n; s.clear();
		for(int i = 1;i<=n+10;i++) ans[i] = 0,a[i].l = a[i].r = a[i].id = 0;
		for(int i = 1;i<=(n<<2)+10;i++)
			tree[i].num = tree[i].id = 0,tree[i].minn = 0;
		for(int i = 1;i<=n;i++){
			cin>>a[i].l>>a[i].r;
			a[i].id = i;
		}
		sort(a+1,a+n+1,cmp);
		Build(1,n,1);
		s.insert(a[1].r);
		for(int i = 2;i<=n;i++){
			if(i < n && a[i].l == a[i+1].l && a[i].r == a[i+1].r){
				s.insert(a[i].r);
				continue;
			}
			int l = 1,r = i-1,tmp = i;
			while(l <= r){
				int mid = l+((r-l)>>1);
				tee res = Getnum(mid,i-1,1,n,1);
				if(res.num >= a[i].r) tmp = mid,l = mid+1;
				else r = mid-1;
			}
			ans[a[i].id] = a[i].l - a[tmp].l;
			auto p = s.lower_bound(a[i].r);
			if(p != s.end()) ans[a[i].id] += *p - a[i].r;
			s.insert(a[i].r);
		}
		for(int i = 1;i<=n;i++)
			cout<<ans[i]<<'\n';
	}

	return 0;
}
```

---

## 作者：Arrtan_73 (赞：1)

# 题目大意
[Codeforces传送门](https://codeforces.com/problemset/problem/2042/D)  
给你 $n$ 个区间，每次查询给一个区间 $[l,r]$
求所有包含 $[l,r]$ 的区间的交。
# 题解
首先我们考虑当前所求的区间 $[l, r]$，则包含它的区间一定形如 $[l', r']$ 且满足 $l' \le l \wedge r' \ge r$。

则答案即满足以上限制的区间的 $(r'_{min} - l'_{max} + 1) + (r - l + 1)$，也等价于 $(r'_{min} - r) + (l - l'_{max})$，然后对加号两边分别维护。

假设我们现在在统计 $r'_{min} - r$ 部分的贡献，则考虑对 $l$ 递增排序，即在统计过程中左端点始终满足 $l' \le l$ 的限制，$r'_{min}$ 则用线段树维护即可。统计 $l - l'_{max}$ 时同理。

现在思考如何维护 $r'_{min}$，修改时直接在线段树上单点修改，查询的时候，把线段树上所有在查询点左侧的极大节点存下来，可以证明这样的节点只有 $O(\log n)$ 个。从左至右对每个节点遍历一遍，然后找到第一个被修改过的节点，在此节点中继续二分查找即可。

时间复杂度 $O(n \log n)$。
# Code
```cpp
/*Codeforces RemoteJudge炸了，在Luogu上没AC记录，但Codeforces上过了*/
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
#define int long long
bool tree[N << 3];
int T, n;
struct node{int l, r, id;}a[N];
bool cmpl(const node x, const node y){
    if(x.l != y.l)return x.l < y.l;
    else return x.r > y.r;
}
bool cmpr(const node x, const node y){
    if(x.r != y.r)return x.r > y.r;
    else return x.l < y.l;
}
void clear(int p, int l, int r){
    tree[p] = false;
    if(l == r)return;
    int mid = l + r >> 1;
    clear(p << 1, l, mid);
    clear(p << 1 | 1, mid + 1, r);
}
void push_up(int p){tree[p] = tree[p << 1] | tree[p << 1 | 1];}
void Update(int p, int l, int r, int pos){
    if(l == pos && r == pos){tree[p] = true; return;}
    int mid = l + r >> 1;
    if(pos <= mid)Update(p << 1, l, mid, pos);
    if(pos > mid)Update(p << 1 | 1, mid + 1, r, pos);
    push_up(p);
}
int ret, leaf[N], l_[N], r_[N];
void Query(int p, int l, int r, int pos, int opt){
    if(l == r){leaf[++ret] = p; r_[ret] = l_[ret] = pos; return;}
    int mid = l + r >> 1;
    if(pos <= mid){
        if(opt == 0)leaf[++ret] = p << 1 | 1,  l_[ret] = mid + 1, r_[ret] = r;
        Query(p << 1, l, mid, pos, opt);
    }
    if(pos > mid){
        if(opt == 1)leaf[++ret] = p << 1,  l_[ret] = l, r_[ret] = mid;
        Query(p << 1 | 1, mid + 1, r, pos, opt);
    }
}
int check(int p, int l, int r, int opt){
    if(l == r){return l;}
    int mid = l + r >> 1;
    if(opt == 0){
        if(tree[p << 1])return check(p << 1, l, mid, opt);
        else return check(p << 1 | 1, mid + 1, r, opt);
    }
    if(opt == 1){
        if(tree[p << 1 | 1])return check(p << 1 | 1, mid + 1, r, opt);
        else return check(p << 1, l, mid, opt);
    }
}
int Find(int opt){
    int res = 0;
    for(int i = ret; i >= 1; i--)if(tree[leaf[i]]){res = check(leaf[i], l_[i], r_[i], opt); break;}
    return res;
}
int Ans[N];
int t[N << 1];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i].l >> a[i].r;
            a[i].id = i;
            t[(i << 1) - 1] = a[i].l;
            t[i << 1] = a[i].r;
            Ans[i] = 0;
        }
        a[n + 1].l = a[n + 1].r = 0;
        sort(t + 1, t + 2 * n + 1);
        int top = unique(t + 1, t + 2 * n + 1) - (t + 1);

        sort(a + 1, a + n + 1, cmpl);
        clear(1, 1, top);
        for(int i = 1; i <= n; i++){
            int tr = lower_bound(t + 1, t + top + 1, a[i].r) - t;
            ret = 0; Query(1, 1, top, tr, 0);
            int closer = Find(0);
            if(closer && (a[i].l != a[i + 1].l || a[i].r != a[i + 1].r))Ans[a[i].id] += t[closer] - a[i].r;
            Update(1, 1, top, tr);
        }

        sort(a + 1, a + n + 1, cmpr);
        clear(1, 1, top);
        for(int i = 1; i <= n; i++){
            int tl = lower_bound(t + 1, t + top + 1, a[i].l) - t;
            ret = 0; Query(1, 1, top, tl, 1);
            int closer = Find(1);
            if(closer && (a[i].l != a[i + 1].l || a[i].r != a[i + 1].r))Ans[a[i].id] += a[i].l - t[closer];
            Update(1, 1, top, tl);
        }
        for(int i = 1; i <= n; i++)cout << Ans[i] << endl;
    }
    return 0;
}
```

---

## 作者：WaterM (赞：1)

定义：若区间 $A, B$ 有 $A \subseteq B$，则称 $B$ 是 $A$ 的包区间。  
区间很乱，直接做发现不可做，于是考虑排序。  
排序（规则：右端点不降为第一关键字，左端点不升为第二关键字）的好处就是可以让一个区间的包区间**都在它的后面**。  
又由于我们不关心包区间的个数，只关心包区间**左端点的最大值和右端点的最小值**。我们考虑 $A \subseteq B$ 的充要条件，是 $l_B \leq l_A \wedge  r_A \leq r_B$。右端点的条件已经满足，只要保证左端点的条件即可。  
于是问题就变成了：求一个区间后面（这里指下标靠后）的区间中，左端点小于等于当前区间左端点的区间中，左端点最小值以及右端点最大值。  
将区间的左右端点作为 value，挂在以端点为 index 的序列上。只需求：
- 前缀最小值。
- 单点修改。

这可以用树状数组维护。  
于是终。  
别忘了若存在区间相等，要输出 0。（为什么？）

---

## 作者：luqyou (赞：1)

# 思路

考虑先对所有区间按左端点排序。然后对于一个区间  $[l_i,r_i]$，我们需要统计 $j<i$ 且 $r_j \ge r_i$ 的 $r_j$ 的最小值和 $l_j$ 的最大值（因为这些区间交集的大小显然为 $\min r_i - \max l_i + 1$）。

于是使用线段树维护即可，时间复杂度 $O(n \log n)$。

细节：如果一个区间出现了多于一次，则该区间答案为 $0$。

---

## 作者：lyxxys (赞：1)

### 题目大意
对于每一个区间，求其他的所有包含我这个区间的**区间交长度**减去我**自身区间**的长度是多少。

---
### 解题思路
将所有区间排序，按左端点升序，相同时右端点降序.按顺序枚举所有区间。

假设区间交是 $[L,R]$，那么对于我当前的区间 $[l,r]$：

由于我们的排序规则：
- 对于 $R$,由于前面左端点都小于等于 $l$，前面右端点大于等于 $r$ 的一定把我覆盖，我们可以很轻易的找到 $R$，$R$ 就是前面出现过的右端点中第一个大于等于 $r$ 的，用 ```set``` 轻松维护。
- 对于 $L$，由于并不是前面所有的右端点都大于等于 $r$，所以我们只选择右端点大于等于 $r$ 的最大的左端点 $L$，用 树状数组维护右端点的左端点的后缀最大值。

- 最后统计贡献 $ans = l-L + R-r$。

注意这里会出现一些区间完全相同的情况，它们的答案一定是 $0$，我们要将它们一起考虑。

---
### 复杂度分析
时间复杂度 $O(n\log{n})$，空间复杂度 $O(n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
template <class T> void fmax(T &a, const T &b){
    if (b > a) a = b;
}
template <class T> void fmin(T &a, T b){
    if (b < a) a = b;
}
struct fenwick{
        vector <int> info;
        int n;
        fenwick(){}
        fenwick(int n): info(n+1, -1), n(n) {}
        void update(int i, int v){
            i = n-i+1;
            while (i <= n){
                fmax(info[i], v);
                i += i&-i;
            }
        }
        int query(int i){
            int res = -1;
            i = n-i+1;
            while (i){
                fmax(res, info[i]);
                i -= i&-i;
            }
            return res;
        }
};

void solve(){
    using ary3 = array<int,3>;
    using Yint = fenwick;
    const int inf = 1e9+1;

    int n;
    cin >> n;
    vector <ary3> segs;
    map <int,int> mps;
    for (int i = 0,l,r; i < n; ++ i){
        cin >> l >> r;
        segs.push_back({l,r,i});
        mps[r] = 1;
    }
    int tot = 0;
    for (auto &it : mps){
        it.second = ++ tot;
    }
    Yint Y(tot);

    sort(segs.begin(), segs.end(), [&](auto &u, auto &v){
        return u[0] == v[0] ? u[1] > v[1] : u[0] < v[0];
    });
    vector <int> ans(n);
    set <int> st;

    for (int i = 0; i < n; ++ i){
        auto &[l, r, id] = segs[i];

        int L = -1, R = inf;
        if (i < n-1 && segs[i+1][0] == l && segs[i+1][1] == r){
            st.insert(r);
            Y.update(mps[r], l);
        }
        auto it = st.lower_bound(r);
        if (it != st.end()) R = *it;
        L = Y.query(mps[r]);

        if (R != inf && L != -1){
            ans[id] += l-L + R-r;
        }

        st.insert(r);
        Y.update(mps[r], l);
    }

    for (auto &x : ans){
        cout << x << "\n";
    }
}

int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}
```

---

## 作者：gcx114514 (赞：0)

首先我们发现在一个区间的左边或者右边的合法个数是两个互不干扰的、等价的东西，那么我们只需要考虑一边即可。那么这里只讨论左边的情况。

考虑将区间按照右端点从小到大排序扫描线（假设当前扫到 $i$，要处理的是线段 $x$ 的答案），用一棵线段树或者树状数组维护右端点在 $i$ 之后的区间的左端点出现在哪些位置，那么注意到对于 $x$ 来说，那些左端点小于 $x$ 的左端点的线段一定是包含了这个 $x$ 这个区间的（当然不包括 $x$）。那么这些合法的区间中左端点最大的那一个就是对 $x$ 限制最严的一个，直接作差计算答案即可。

同理只需要按左端点从大到小处理右边的即可。

（当然注意要离散化和清空。）

### Code 

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define int long long
#define mk make_pair
#define se second
#define fi first
#define itn int
#define mid ((l+r)>>1)
#define rs now<<1|1
#define ls now<<1
using namespace std;
bool Mst;
const int Max=5e5+10;
const int mod=998244353;
const int inf=1e18+10;

inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

struct SGT{
	int maxx,val,minn;
	SGT(){
		maxx=-inf,minn=inf;
	}
}tr[Max<<2];
void pushup(int now){
	tr[now].maxx=max(tr[ls].maxx,tr[rs].maxx);
	tr[now].minn=min(tr[ls].minn,tr[rs].minn);
}

void Modify(int now,int l,int r,int to,int val){
	if(l==r){
		tr[now].val+=val;
		if(tr[now].val<=0){
			tr[now].maxx=-inf;
			tr[now].minn=inf;
		}else{
			tr[now].maxx=tr[now].minn=l;
		}
		return;
	}
	if(to<=mid)Modify(ls,l,mid,to,val);
	else Modify(rs,mid+1,r,to,val);
	pushup(now);
}

pii Query(int now,int l,int r,int L,int R){
	if(R<L)return mk(-inf,inf);
	if(L<=l&&R>=r){
		return mk(tr[now].maxx,tr[now].minn);
	}
	pii ans=mk(-inf,inf);
	if(L<=mid)ans=Query(ls,l,mid,L,R);
	if(R>mid){
		pii res=Query(rs,mid+1,r,L,R);
		ans.fi=max(ans.fi,res.fi);
		ans.se=min(ans.se,res.se);
	}
	return ans;
}

int QueryVal(int now,int l,int r,int to){
	if(l==r){
		return tr[now].val;
	}
	if(to<=mid) return QueryVal(ls,l,mid,to);
	else return QueryVal(rs,mid+1,r,to);
}

void build(int now,int l,int r){
	tr[now]=SGT();tr[now].val=0;
	if(l==r)return;
	build(ls,l,mid);build(rs,mid+1,r);
}


vector<pii> l[Max],r[Max];
struct SG{
	int l,r;
	SG(int l=0,int r=0) :
		l(l),r(r){;}
}a[Max];

vector<int>ys;
int Ans[Max];

void clear(int n){
	int N=ys.size()-1;
	for(int i=1;i<=n;++i)Ans[i]=0;
	for(int i=1;i<=N;++i){
		Ans[i]=0;l[i].clear();r[i].clear();
	}
	ys.clear();
}

void work(){
	
	int n=read();
	clear(n);
	for(int i=1;i<=n;++i){
		int l,r;
		l=read();r=read();
		a[i]=SG(l,r);
		ys.pb(l),ys.pb(r);
	}
	ys.pb(-1);
	sort(ys.begin(),ys.end());
	ys.erase(unique(ys.begin(),ys.end()),ys.end());
	for(int i=1;i<=n;++i){
		a[i].l=lower_bound(ys.begin(),ys.end(),a[i].l)-ys.begin();
		a[i].r=lower_bound(ys.begin(),ys.end(),a[i].r)-ys.begin();
		l[a[i].r].pb(mk(a[i].l,i));
		r[a[i].l].pb(mk(a[i].r,i));
	}
	int N=ys.size()-1;
	build(1,1,N);
	for(int i=1;i<=n;++i){
		Modify(1,1,N,a[i].l,1);
	}
	for(int i=1;i<=N;++i){
		for(auto j:l[i]){
			int z=Query(1,1,N,1,j.fi-1).fi;
			int res=QueryVal(1,1,N,j.fi);
			if(res!=1)continue;
			Ans[j.se]+=(z==-inf?0:ys[j.fi]-ys[z]);
		}
		for(auto j:l[i]){
			Modify(1,1,N,j.fi,-1);
		}
	}
	build(1,1,N);
	for(int i=1;i<=n;++i){
		Modify(1,1,N,a[i].r,1);
	}
	for(int i=N;i>=1;--i){
		for(auto j:r[i]){
			int z=Query(1,1,N,j.fi+1,N).se;
			int res=QueryVal(1,1,N,j.fi);
			if(res!=1)continue;
			Ans[j.se]+=(z==inf?0:ys[z]-ys[j.fi]);
		}
		for(auto j:r[i]){
			Modify(1,1,N,j.fi,-1);
		}
	}
	for(int i=1;i<=n;++i){
		cout << Ans[i] << "\n";
	}
}

bool Med;
signed main(){
	int T=read() ;
	while(T--)work();


	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

首先对所有区间按左端点排序。然后对于一个区间 $[l _ i, r _ i]$，我们统计 $j < i$ 且 $r _ j \ge r _ i$ 的 $r _ j$ 最小值和 $l _ j$ 的最大值。

注意：如果一个区间出现了多于一次，则该区间答案为 $0$。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 2e5 + 10;
ll T, n, l[MAXN], r[MAXN];
struct node {
    ll l, r, id;
}a[MAXN];
bool cmp1 (node c, node b) {
    return c.l < b.l;
}
bool cmp2 (node c, node b) {
    return c.r < b.r;
}
multiset <ll> s;
void read () {
    cin >> n;
    for (ll i = 1; i <= n; i ++) {
		cin >> a[i].l >> a[i].r;
		a[i].id = i;
	}
    sort (a + 1, a + n + 1, cmp1);
    s.clear ();
    ll pre = 0;
    for (ll i = 1; i <= n; i ++) {
        pre = i;
        s.insert (a[i].r);
        while (i + 1 <= n && a[i + 1].l == a[i].l) s.insert (a[++ i].r);
            for (ll j = pre; j <= i; j ++) {
                auto it = s.lower_bound (a[j].r);
                it ++;
                if (it != s.end ())r[a[j].id] = *it;
                else r[a[j].id] = -1;
            }
    }
    s.clear ();
    sort (a + 1, a + n + 1, cmp2);
    for (ll i = n; i >= 1; i --) {
        pre = i;
        s.insert (a[i].l);
        while (i - 1 > 0 && a[i - 1].r == a[i].r) s.insert (a[-- i].l);
        for (ll j = i; j <= pre; j ++) {
            auto it = s.upper_bound (a[j].l);
            it --; it --;
            if (it != s.end ()) l[a[j].id] = (*it) + a[j].r - a[j].l + 1;
            else l[a[j].id] = -1;
        }
    }
    for (ll i = 1; i <= n; i ++) {
        if (l[i] == -1 || r[i] == -1) cout << 0 << endl;
        else cout << r[i] - l[i] + 1 << endl;
    }	
}
int main () {
    cin >> T;
    while (T --) read ();
    return 0;
}
```

---

## 作者：__vector__ (赞：0)

### 题意  

有 $n$ 个用户和 $10^9$ 首歌曲，第 $i$ 个用户喜欢的歌曲是编号在 $[l_i,r_i]$ 的一段连续子区间。  

用户 $j$ 称为用户 $i$ 的预测者当且仅当 $[l_j,r_j]$ 包含 $[l_i,r_i]$。  

对于每个用户 $i$，计算其预测者喜欢的歌曲的并集大小（原题求出结果后需要减去 $r_i-l_i+1$）。  

### 做法

注意到完全包含的对数可以达到 $O(n^2)$ 级别，逐个计算是不可能的。  

考虑对于每个人，如何计算其答案。   

考虑简化问题，分别考虑对于一个人，其预测者喜欢的音乐的并集区间的左端点和右端点。  

假设当前处理用户 $i$ 的答案。

容易注意到，左端点是在 $i$ 的预测者的左端点里面取最大值，右端点是在 $i$ 的预测者的右端点里面取最小值。  

能否二分左右端点呢？  

由于左右端点的做法是等价的，此处仅讨论左端点的情况。  

此时，二分的目的是求出最大的 $l$ 使得 $l$ 是某个预测者的左端点。

注意到，一个左端点是某个预测者的左端点，当且仅当这个左端点能直接到达的最大右端点大于等于 $r_i$，当然，这对左端点右端点的组合不能是 $(l_i,r_i)$ 本身。  

那么，二分 check 的时候只需要看从 mid 到 $l_i$ 是否存在一个预测者的左端点就可以了，可以 ST 表维护做到 $O(1)$ 判定。

---

