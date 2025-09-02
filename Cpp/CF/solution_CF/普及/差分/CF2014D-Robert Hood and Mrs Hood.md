# Robert Hood and Mrs Hood

## 题目描述

Impress thy brother, yet fret not thy mother.



Robin's brother and mother are visiting, and Robin gets to choose the start day for each visitor.

All days are numbered from $ 1 $ to $ n $ . Visitors stay for $ d $ continuous days, all of those $ d $ days must be between day $ 1 $ and $ n $ inclusive.

Robin has a total of $ k $ risky 'jobs' planned. The $ i $ -th job takes place between days $ l_i $ and $ r_i $ inclusive, for $ 1 \le i \le k $ . If a job takes place on any of the $ d $ days, the visit overlaps with this job (the length of overlap is unimportant).

Robin wants his brother's visit to overlap with the maximum number of distinct jobs, and his mother's the minimum.

Find suitable start days for the visits of Robin's brother and mother. If there are multiple suitable days, choose the earliest one.

## 说明/提示

In the first test case, the only job fills all $ 2 $ days, both should visit on day $ 1 $ .

In the second test case, day $ 2 $ overlaps with $ 2 $ jobs and day $ 1 $ overlaps with only $ 1 $ .

In the third test case, Robert visits for days $ [1,2] $ , Mrs. Hood visits for days $ [4,5] $ .

## 样例 #1

### 输入

```
6
2 1 1
1 2
4 1 2
1 2
2 4
7 2 3
1 2
1 3
6 7
5 1 2
1 2
3 5
9 2 1
2 8
9 2 4
7 9
4 8
1 3
2 3```

### 输出

```
1 1
2 1
1 4
1 1
1 1
3 4```

# 题解

## 作者：cly312 (赞：4)

差分，每次差分将 $\max(1,l-d+1)$ 加 $1$，将 $r+1$ 位置减 $1$。

然后前缀和求原数组，再遍历一下求最小值和最大值即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, d, k;
		cin >> n >> d >> k;
		vector<int> cover(n + 2, 0);
		for (int i = 0; i < k; ++i) {
			int l, r;
			cin >> l >> r;
			cover[max(1,l-d+1)]++;
			cover[r + 1]--;
		}
		for (int i = 1; i <= n; ++i) {
			cover[i] += cover[i - 1];
		}
		int bday = 1, mday = 1;
		int maxn = -1, minn = INT_MAX;
		for (int day = 1; day <= n - d + 1; ++day) {
			if (cover[day] > maxn) {
				maxn = cover[day];
				bday = day;
			}
			if (cover[day] < minn) {
				minn = cover[day];
				mday = day;
			}
		}
		cout << bday << ' ' << mday << '\n';
	}
	return 0;
}
```

---

## 作者：Temp113 (赞：3)

## Solution

考虑差分。对于第 $i$ 个工作，连续逗留 $d$ 天，所得到的区间为 $[l_i - d + 1, r_i]$。将 $l_i - d + 1$ 加 $1$，并将 $r_i + 1$ 减 $1$ 即可。

再求前缀和得到重叠的工作数，最后依此求两个答案。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int t, n, d, k, l, r, a[N], maxa, mina, ans1, ans2;
inline int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
void solve(){
	maxa = -1e9;
	mina = 1e9;
	cin >> n >> d >> k;
	for(int i = 1; i <= n; i++) a[i] = 0;
	for(int i = 1; i <= k; i++){
		cin >> l >> r;
		a[max_(1, l - d + 1)]++;
		a[r + 1]--;
	}
	for(int i = 1; i <= n; i++) a[i] += a[i - 1];
	for(int i = 1; i <= n - d + 1; i++){
		if(a[i] > maxa){
			maxa = a[i];
			ans1 = i;
		}
		if(a[i] < mina){
			mina = a[i];
			ans2 = i;
		}
	}
	cout << ans1 << ' ' << ans2 << '\n';
	return ;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie();
	cin >> t;
	for(int kk = 1; kk <= t; kk++) solve();
	return 0;
}
```

---

## 作者：WRT_Partisan (赞：2)

# 题解：CF2014D Robert Hood and Mrs Hood

[题目链接](https://www.luogu.com.cn/problem/CF2014D)

## 题目大意

已知在 $[1,n]$ 之间有 $k$ 个区间，要在 $[1,n]$ 之间找到两个长度为 $d$ 的区间，分别使目标区间与尽量少和尽量多的已知区间相交，分别输出两个目标区间的左端点。

## 解题思路

$l_i$ 代表在 $[i,n]$ 之间的已知区间的个数，$r_i$ 代表在 $[1,i]$ 之间的已知区间的个数，则和以 $i$ 为左端点的目标区间相交的一直区间的个数为 $k-l_{i+d}-r_{i-1}$，分别求它们的最大值和最小值。

## 代码

```cpp
/*
 * @FilePath: \c++\CF2014D.cpp
 * @Author: WRT_Partisan
 * @Date: 2024-11-17 18:00:35
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef unsigned long long ull;
int t, n, d, k, l[100005], r[100005], ans[100005], a, b, maxx, minn;
signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(ans, 0, sizeof(ans));
        maxx = minn = 1;
        scanf("%lld%lld%lld", &n, &d, &k);
        for (int i = 1; i <= k; i++)
            scanf("%lld%lld", &a, &b), l[a]++, r[b]++;
        for (int i = 1; i <= n; i++)
            r[i] += r[i - 1];
        for (int i = n; i >= 1; i--)
            l[i] += l[i + 1];
        for (int i = 1; i <= n - d + 1; i++)
            ans[i] = k - l[i + d] - r[i - 1];
        for (int i = 2; i <= n - d + 1; i++)
        {
            if (ans[maxx] < ans[i])
                maxx = i;
            if (ans[minn] > ans[i])
                minn = i;
        }
        printf("%lld %lld\n", maxx, minn);
    }
    return 0;
}
```

---

## 作者：lyxxys (赞：1)

### 题目大意
在 $[1,n]$ 有 $k$ 个区间，用一个长度为 $d$ 的线段去覆盖这些区间，分别求线段和最多、最少个区间相交的个数是多少。
### 解题思路
这里提供一个 $O(n\log{n})$ 的做法：枚举 $i$，表示当前的区间 $[i-d+1,i]$，用 **set** 去维护 $i$ 左边区间的右端点，此时右端点个数就是区间的个数，只要及时把勾不住的右端点删去，就是当前 $[i-d+1,i]$ 这个线段有多少区间，取最大和最小区间个数即可。
```cpp
#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n, d, k;
    cin >> n >> d >> k;
    vector <vector<int>> L(n+1);
    vector <int> Ls;
    for (int i = 0, l, r; i < k; ++ i){
        cin >> l >> r;
        Ls.push_back(r);
        L[l].push_back(i);
    }
    set <pair<int,int>> st;
    array <int,2> ans = {-1, 1};
    for (int i = 1; i <= n; ++ i){
        while (!st.empty() && i - st.begin()->first >= d){
            st.erase(st.begin());
        }
        for (auto &x : L[i]){
            st.insert({Ls[x], x});
        }
        if (i >= d && (int)st.size() > ans[0]){
            ans[0] = st.size();
            ans[1] = i-d+1;
        }
    }
    array <int,2> res = {(int)1e9, 1};
    st.clear();
    for (int i = 1; i <= n; ++ i){
        while (!st.empty() && i - st.begin()->first >= d){
            st.erase(st.begin());
        }
        for (auto &x : L[i]){
            st.insert({Ls[x], x});
        }
        if (i >= d && (int)st.size() < res[0]){
            res[0] = st.size();
            res[1] = i-d+1;
        }
    }

    cout << ans[1] << " " << res[1] << "\n";
}
 
int main(){
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#else
    freopen("in.txt", "rt", stdin), freopen("out.txt", "wt", stdout);
#endif
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

对于连续访问的一段时间 $[i,i+d-1]$，会做出贡献的区间 $[l_i,r_i]$ 满足 $l_i< i+d,r_i\ge i$。这是个很典型的二位偏序，把 $l_i$ 当作下标，$r_i$ 当作权值放入主席树里统计就好了。

# Code

```cpp
#include<bits/stdc++.h>
struct segment{
	int val;
	int lc,rc;
}t[2000005];
int root[100005],idx;
void add(int&p,int q,int L,int R,int x){
	t[p=++idx]=t[q];
	++t[p].val;
	if(L==R)return;
	int mid=L+R>>1;
	if(x<=mid)add(t[p].lc,t[q].lc,L,mid,x);
	else add(t[p].rc,t[q].rc,mid+1,R,x);
}
int ask(int p,int L,int R,int x){
	if(L==R)return t[p].val;
	int mid=L+R>>1;
	if(x>mid)return ask(t[p].rc,mid+1,R,x);
	return ask(t[p].lc,L,mid,x)+t[t[p].rc].val;
}
std::vector<int>v[100005];
int T,n,m,q,ans1,id1,ans2,id2;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<=n;++i)v[i].clear();
		for(int i=1,l,r;i<=q;++i)
			scanf("%d%d",&l,&r),v[l].push_back(r);
		idx=0;
		for(int i=1;i<=n;++i){
			root[i]=root[i-1];
			for(const int&j:v[i])
				add(root[i],root[i],1,n,j);
		}
		ans1=0;ans2=0x3f3f3f3f;
		for(int i=1,j=m,res;j<=n;++i,++j){
			res=ask(root[j],1,n,i);
			if(ans1<res)ans1=res,id1=i;
			if(ans2>res)ans2=res,id2=i;
		}
		printf("%d %d\n",id1,id2);
	}
	return 0;
}
```

---

## 作者：Hide_In_The_Shadow (赞：1)

其实就是一个前缀和？容易发现只需要暴力扫一遍即可求出答案。

记录 $L[i]$ 表示第 $i$ 天有几个任务开始，对 $L[i]$ 求前缀和得 $suml[i]$。$sumr[i]$ 同理。

计算得区间 $[l,r]$ 内可以被重叠的任务数为 $suml[r]-sumr[l-1]$。加之 $n$ 很小，对每一天进行遍历即可。
时间复杂度 $O(n)$。

```c++
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fio std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
template<typename T>inline void read(T &x){
	x=0;
	char c=getchar();
	T ret=0;
	while(!isdigit(c))ret|=!(c^'-'),c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(ret)x=(~x)+1;
	return;
}
template<typename T>inline void print(T x){
	if(x<0)putchar('-'),x=(~x)+1;
	if(x>9)print(x/10);
	putchar((x-x/10*10)^48);
	return;
}
template<typename T>inline void wr1(T x){
	print(x);
	putchar(' ');
	return;
}
template<typename T>inline void wr2(T x){
	print(x);
	putchar('\n');
	return;
}
int t,n,d,k,l[114514],r[114514],suml[114514],sumr[114514],bro,mum,mx,mi;
int main(){
	read(t);
    while(t--){
        mx=0;
        read(n);
        read(d);
        read(k);
        mi=k+1;
        for(int i=1;i<=n;++i){
            l[i]=r[i]=0;
        }
        for(int i=1;i<=k;++i){
            int L,R;
            read(L);
            l[L]++;
            read(R);
            r[R]++;
        }
        for(int i=1;i<=n;++i){
            suml[i]=suml[i-1]+l[i];
            sumr[i]=sumr[i-1]+r[i];
        }
        for(int i=1;i<=n;++i){
            int L=i;
            int R=L+d-1;
            if(R>n)break;//注意必须 k 天在 n 以内
            int te=suml[R]-sumr[L-1];
            if(mx<te){
                mx=te;
                bro=L;
            }
            if(mi>te){
                mi=te;
                mum=L;
            }
        }
        wr1(bro),wr2(mum);
    }
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

考虑暴力，问题转化为求所有区间内工作的数量。

于是规约为下面的数据结构问题：

插入一个区间 $ [l,r] $，或查询一个区间与之前多少个区间有交集。

然后这个问题就是 [这题](https://www.luogu.com.cn/problem/P2184) 的弱化版，我们统计出一个区间前面有多少个左端点，后面有多少个右端点，显然中间的部分就是答案，开两个树状数组维护即可。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

[提交记录](https://codeforces.com/contest/2014/submission/294790526)

---

## 作者：sad_lin (赞：0)

考虑用**差分**将**区间贡献转化为点贡献**，对于一个工作区间  $[l,r]$，因为访问也是一个区间，所以将位置 $l-d+1$ 加 $1$，$r+1$ 减 $1$。

我们再求前缀和就可以得到每个位置 $i$ 的访问区间 $[i,i+d-1]$ 内不同工作数，求最大值最小值的下标即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register
const int N=1e5+10;
using namespace std;

int n,d,m;
int a[N];

void solve(){
	cin>>n>>d>>m;
	
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		a[max(1ll,l-d+1)]++;
		a[r+1]--;
	}
	
	for(int i=1;i<=n;i++){
		a[i]+=a[i-1];
	}
	int mx=0,mxid=0,mi=1e9,miid=0;
	for(int i=1;i<=n-d+1;i++){
		if(a[i]>mx){
			mx=a[i];
			mxid=i;
		} 
		if(a[i]<mi){
			mi=a[i];
			miid=i;
		} 
	} 
	cout<<mxid<<" "<<miid<<"\n";
	for(int i=1;i<=n+1;i++){//要多清一个位置
		a[i]=0;
	}
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：doumingze (赞：0)

一个很直接的做法是枚举每个区间看里面有多少 jobs 与这个区间有交集。这个实际上就是正解了，但是枚举的时候如果使用暴力统计一定超时，需要一定的技巧。

我们使用两个指针 $L, R$ 维护现在枚举到的区间，记该区间答案为 $ans$。因为要保持区间长度为 $d$，于是我们考虑当两个指针 $L, R$ 都右移一位，移动到 $L + 1, R + 1$ 时 $ans$ 的变化。当一件工作的结束时间为 $L$ 时，$[L + 1, R + 1]$ 这段区间内将不再包含 $L$，于是将 $ans$ 减去右端点与 $L$ 相等的工作区间的数量；当一件工作的开始时间为 $R + 1$ 时，$[L + 1, R + 1]$ 这段区间内将包含 $R + 1$，于是将 $ans$ 加上左端点与 $R + 1$ 相等的工作区间的数量。记左端点为 $R + 1$ 的区间数量为 $x$，记右端点为 $L$ 的区间数量为 $y$，那么 $[L + 1, R + 1]$ 的答案就是 $ans + x - y$。

那么我们只需要给每个 $i \in [1, n]$ 统计左/右端点等于 $i$ 的区间数量，就可以直接按照上述方法递推了，这个时好统计的。这样我们 $O(n)$ 扫一遍就可以得到所有区间的答案，根据题意统计即可。

一些细节可以看看代码，后面忘了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int l[N], r[N];
int be[N], ed[N];
int n, d, k;

int main()
{
	int t;
	cin >> t;
	while(t --)
	{
		scanf("%d%d%d", &n, &d, &k);
		for(int i = 1; i <= k; i ++) scanf("%d%d", &l[i], &r[i]), be[l[i]] ++, ed[r[i]] ++;
		int ans1 = 1, ans2 = 1, val1 = 0, val2 = 0, res = 0;
		int L = 1, R = 0;
		while(R < d) res += be[++ R];
		val1 = val2 = res;
		while(R < n)
		{
			res -= ed[L ++];
			res += be[++ R];
			if(val1 < res)
			{
				ans1 = L;
				val1 = res;
			}
			if(val2 > res)
			{
				ans2 = L;
				val2 = res;
			}
		}
		printf("%d %d\n", ans1, ans2);
		for(int i = 1; i <= k; i ++) be[l[i]] --, ed[r[i]] --;
	}
	return 0;
}
```

---

## 作者：Meickol (赞：0)

算是经典问题了，有两种处理方式。在此给出一个相对容易理解的区分起点与终点数组的写法。

记录 $b\_start[i]$ 表示第 $i$ 天有几个任务开始，对其求前缀和得 $pre\_start[i]$。

记录 $b\_end[i]$ 表示第 $i$ 天有几个任务结束，对 $b\_end[i]$ 求前缀和得 $pre\_end[i]$。

则区间 $[l,r]$ 内可以被重叠的任务数为 $pre\_start[r]−pre\_end[l−1]$。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
const int N=2e5+5;
int n,d,k;
int b_start[N],b_end[N];
int pre_start[N],pre_end[N];
void solve(){
	cin>>n>>d>>k;
	rep(i,1,k){
		int l,r;
		cin>>l>>r;
		b_start[l]++,b_end[r]++;
	}
	rep(i,1,n){
		pre_start[i]=pre_start[i-1]+b_start[i];
		pre_end[i]=pre_end[i-1]+b_end[i];
	}
	int mx,mn;
	memset(&mn,0x3f,sizeof mn);
	memset(&mx,0x80,sizeof mx);
	int mxpos=-1,mnpos=-1;
	rep(i,1,n-d+1){
		int cnt=pre_start[i+d-1]-pre_end[i-1];
		if(cnt>mx) mx=cnt,mxpos=i;
		if(cnt<mn) mn=cnt,mnpos=i;
	}
	cout<<mxpos<<" "<<mnpos;
	rep(i,1,n) b_start[i]=0,b_end[i]=0;
}
```

---

