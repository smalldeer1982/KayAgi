# Tracking Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ zeros. You are also given a set of $ m $ not necessarily different segments. Each segment is defined by two numbers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) and represents a subarray $ a_{l_i}, a_{l_i+1}, \dots, a_{r_i} $ of the array $ a $ .

Let's call the segment $ l_i, r_i $ beautiful if the number of ones on this segment is strictly greater than the number of zeros. For example, if $ a = [1, 0, 1, 0, 1] $ , then the segment $ [1, 5] $ is beautiful (the number of ones is $ 3 $ , the number of zeros is $ 2 $ ), but the segment $ [3, 4] $ is not is beautiful (the number of ones is $ 1 $ , the number of zeros is $ 1 $ ).

You also have $ q $ changes. For each change you are given the number $ 1 \le x \le n $ , which means that you must assign an element $ a_x $ the value $ 1 $ .

You have to find the first change after which at least one of $ m $ given segments becomes beautiful, or report that none of them is beautiful after processing all $ q $ changes.

## 说明/提示

In the first case, after first 2 changes we won't have any beautiful segments, but after the third one on a segment $ [1; 5] $ there will be 3 ones and only 2 zeros, so the answer is 3.

In the second case, there won't be any beautiful segments.

## 样例 #1

### 输入

```
6
5 5
1 2
4 5
1 5
1 3
2 4
5
5
3
1
2
4
4 2
1 1
4 4
2
2
3
5 2
1 5
1 5
4
2
1
3
4
5 2
1 5
1 3
5
4
1
2
3
5
5 5
1 5
1 5
1 5
1 5
1 4
3
1
4
3
3 2
2 2
1 3
3
2
3
1```

### 输出

```
3
-1
3
3
3
1```

# 题解

## 作者：Xy_top (赞：12)

这题其实还行。

如果能想到二分答案就会比较简单，我们来看如何写 check 函数。

把当前所有的单点修改存起来，然后依次遍历每个区间，观察这个区间内被单点修改的点的个数是否严格大于该区间长度的一半即可。

我们需要一个支持单点修改区间查询的工具，首先想到树状数组，但前缀和有够用了。

时间复杂度：$O(\max({n,m})\times \log n)$，注意 $-1$ 的情况。

代码，跑得很快： 
```cpp
#include <iostream>
using namespace std;
int t;
int n, m, q;
int c[100005], s[100005], upd[100005];
struct Node {int l, r;}a[100005];
bool check (int x) {
	for (int i = 1; i <= n; i ++) s[i] = 0;
	for (int i = 1; i <= x; i ++) ++ s[upd[i] ];
	for (int i = 1; i <= n; i ++) s[i] += s[i - 1];
	for (int i = 1; i <= m; i ++) 
		if (2 * (s[a[i].r] - s[a[i].l - 1]) > a[i].r - a[i].l + 1) return true;
	return false;
}
int main () {
	scanf ("%d", &t);
	while (t --) {
		scanf ("%d%d", &n, &m);
		for (int i = 1; i <= m; i ++) scanf ("%d%d", &a[i].l, &a[i].r);
		scanf ("%d", &q);
		for (int i = 1; i <= q; i ++) scanf ("%d", &upd[i]);
		int l = 1, r = q, mid;
		while (l <= r) {
			mid = l + r >> 1;
			if (check (mid) ) r = mid - 1;
			else l = mid + 1;
		}
		printf ("%d\n", (l == q + 1 ? -1 : r + 1) );
	}
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：6)

与众不同的做法。

虽然赛时第一想法是二分，由于当天脑子出了点状况，敲了个分块板子。

------------

根据数据分析，通常 CF 喜欢 $\sum n\le2\times 10^5$，而此题为 $1\times 10^5$，合理猜测不卡（可能也卡不了）分块。

每次操作都将一个 $0$ 改成 $1$，所以任意区间内 $1$ 的个数单调不降，满足单调性。

于是可以二分解决，但我就不。

考虑每操作 $\sqrt q$ 次，枚举 $m$ 个区间前缀和维护一次检查，如果已经满足条件了，就倒退至多 $\sqrt q$ 次，找到第一个满足的位置。

复杂度为 $\operatorname{O}(m\times \sqrt{q})$。

以防万一我还加了个没啥用的小优化（快了 $15$ ms）。

操作前将 $m$ 个区间按长度从小到大排序，因为越长的区间要想满足的最少次数越多，所以后检查。

------------

竟然比几个大佬二分的还快。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+84;
struct Query{
    int l,r;
    friend bool operator<(Query kn,Query sr){
        return kn.r-kn.l<sr.r-sr.l;
    }
}s[maxn];
int T,n,m,q,l,r,ans,x[maxn],SizE,CnT,fnsh,a[maxn],b[maxn];
inline bool check(){
    for(int i=1;i<=n;i++)
        b[i]=b[i-1]+(a[i]==1?1:-1);
    for(int i=1;i<=m;i++)
        if(b[s[i].r]-b[s[i].l-1]>0)
            return 1;
    return 0;
}
int main(){
    scanf("%d",&T);
    while(T--){
        memset(a,0,sizeof(a));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d",&s[i].l,&s[i].r);
        sort(s+1,s+m+1);
        scanf("%d",&q);
        SizE=sqrt(q+1);
        CnT=(q-1)/SizE+1;
        fnsh=0;
        ans=-1;
        r=0;
        for(int i=1;i<=CnT;i++){
            l=r+1;
            r=r+SizE;
            if(i==CnT)
                r=q;
            for(int j=l;j<=r;j++){
                scanf("%d",&x[j]);
                if(!fnsh)
                    a[x[j]]=1;
            }
            if((!fnsh)&&check()){
                puts("Sherry");
                fnsh=1;
                for(int j=l;j<=r;j++)
                    a[x[j]]=0;
                for(int j=l;j<=r;j++){
                    a[x[j]]=1;
                    if(check()){
                        ans=j;
                        break;
                    }
                }
            }
        }
        printf("%d Sherry\n",ans);
    }
    return 0;
}
```


---

## 作者：Auto_Accepted (赞：3)

## 题意：
定义一串序列为美丽的当且仅当这个序列里 $1$ 的个数严格大于 $0$ 的个数。

现在有在长度为 $n$ 的序列里的 $m$ 个区间，所有序列元素初始为 $0$。

有 $q$ 次操作，第 $i$ 次操作会把 $x_i$ 位置的数变为 $1$。

输出最少在几次操作之后，这 $m$ 个区间内至少有一个区间是美丽的。

如果在 $q$ 次操作后，依然没有区间是美丽的，输出 $-1$。

**多组数据测试。**

## 题解：
观察可知这个答案是有单调性的，所以考虑二分答案。

在 `check` 的过程中，我们把前 $mid$ 个操作按照 $x$ 排序，通过二分查找来在 $\log$ 的时间内求出第 $i$ 个区间在执行完前 $mid$ 个操作后有几个 $1$，然后通过 $1$ 的个数来判断这个区间是否美丽。

## 代码：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int l[1000005] , r[1000005] , a[1000005] , tmp[1000005];
int n , m;
inline bool check(int mid){
	vector <int> ans;
//	for(int i = 1;i <= mid;i++){
//		ans.insert(lower_bound(ans.begin() , ans.end() , a[i]) , a[i]);
//	}
	for(int i = 1;i <= mid;i++){
		tmp[i] = a[i];
	}
	sort(tmp + 1 , tmp + mid + 1);
	for(int i = 1;i <= mid;i++){
		ans.push_back(tmp[i]);
	}
	for(int i = 1;i <= m;i++){
		int tl = lower_bound(ans.begin() , ans.end() , l[i]) - ans.begin() + 1 , tr = upper_bound(ans.begin() , ans.end() , r[i]) - ans.begin();
//		cout << tl << ' ' << ans[tl - 1] << ' ' << tr << ' ' << ans[tr - 1] << endl;
if(tr > ans.size()) tr = ans.size();
		if(tr - tl + 1 >= (r[i] - l[i] + 1) / 2 + 1) return 1;
	}
	return 0;
}
signed main() {
	int t;
	cin >> t;
	while(t--){
		cin >> n >> m;
		for(int i = 1;i <= m;i++){
			cin >> l[i] >> r[i];
		}
		int q;
		cin >> q;
		int l = 1 , r = q , ans = -1;
		for(int i = 1;i <= q;i++) cin >> a[i];
		while(l <= r){
			int mid = (l + r) >> 1;
			if(check(mid)) ans = mid , r = mid - 1;
			else l = mid + 1;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：slzx2021zjx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1843E)
## 思路
第一眼看过去，暴力 $O(nm)$ 会超时。于是想可以用二分。

二分 $1$ 到 $m$，$check$ 每个被二分的点是否满足，如果满足则 $r=mid-1$(后面的数行，可以尝试下前面的)；否则 $l=mid+1$(前面的数不行，肯定要往后面找)。

$check$ 函数可以用类似于前缀和的写法，先把每个点放进去，最后统计（否则会超时）。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 100005
int t,m,n,q,a[maxn],l[maxn],r[maxn],b[maxn];
bool check(int x){
	memset(a,0,sizeof(a));
	for(int i=1;i<=x;i++){
		a[b[i]]++;
	}
	for(int i=1;i<=n;i++){
		a[i]=a[i]+a[i-1];
	}
	for(int i=1;i<=m;i++){
		if(2*(a[r[i]]-a[l[i]-1])>r[i]-l[i]+1) return 0;
	}
	return 1;
}
int er()
{
	int l=1,r=q;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	if(l==q+1) return -1;
	else return r+1;
}
signed main()
{
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%lld%lld",&l[i],&r[i]);
		}
		scanf("%lld",&q);
		for(int i=1;i<=q;i++){
			scanf("%lld",&b[i]);
		}
		printf("%lld\n",er());
	}
}
```


---

## 作者：Coffee_zzz (赞：1)

### 分析

看到需要求满足条件中的最小值，且条件具有单调性（因为之后的操作只会增加 $1$ 的数量，不会减少 $1$ 的数量），不难想到二分。

考虑一下如何在线性的时间内判断是否合法。

我们先求出当前的数组 $a$，再求出 $a$ 的前缀和数组 $sum$。

对于第 $i$ 个区间 $[l_i,r_i]$，它的长度为 $r_i-l_i+1$，区间内 $1$ 的数量为 $sum_r-sum_{l_i-1}$。如果区间内 $1$ 的数量的两倍大于区间长度，那么显然这个区间是合法的，因为 $1$ 的数量大于 $0$ 的数量。

如果每个区间都是不合法的，那么整体也就是不合法的。

我们首先可以把 $a_{x_1},a_{x_2},\cdots,a_{x_q}$ 都设为 $1$，然后进行一次判断。如果不合法就输出 $-1$，合法就直接二分查找答案即可。

一次判断的复杂度为 $O(q+n+m)$，二分次数为 $\log q$，总复杂度为 $O(\log q \times(q+n+m))$，可以通过此题。

### 代码

```c++
const int N=1e5+5;
int m,n,q,a[N],sum[N],l[N],r[N],p[N];
bool check(){
	int d,k;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=m;i++){
		d=r[i]-l[i]+1;
		k=sum[r[i]]-sum[l[i]-1];
		if(k*2>d) return 1;
	}
	return 0;
}
void solve(){
	n=read(),m=read();
	int x,y,g;
	for(int i=1;i<=m;i++) l[i]=read(),r[i]=read();
	q=read();
	x=1,y=q;
	for(int i=1;i<=q;i++) p[i]=read();
	for(int i=1;i<=n;i++) a[i]=0;
	for(int i=1;i<=q;i++) a[p[i]]=1;
	if(!check()){
		cout<<-1<<endl;
		return;
	}
	while(x<y){
		g=(x+y)/2;
		for(int i=1;i<=n;i++) a[i]=0;
		for(int i=1;i<=g;i++) a[p[i]]=1;
		if(check()) y=g;
		else x=g+1;
	}
	cout<<y<<endl;
}
```

---

## 作者：XSean (赞：1)

# E：Tracking Segments

[Problem - E - Codeforces](https://codeforces.com/contest/1843/problem/E)

## 基本思路：

思路：求最小变化数，使用对变化进行二分的方法，然后再用最多 $O(N)$ 的方法 `check` 出整段序列是否有符合条件的区间即可。方法就是利用前缀和求得一段区间的 $1$ 的数量再与区间长度比较即可。

**时间复杂度：$O(N\log Q)$**。

## 代码实现：

代码应该很好理解，就不多解释了。

核心代码：

```cpp
const int N = 2e5 + 10;
int n, m;
int L[N], R[N];
int a[N], p[N];
int s[N];
void cover(int indx){
	rep(i, 1, n) a[i] = 0;
	rep(i, 1, indx) a[p[i]] = 1;
}
bool check(){
	int len, k;
	rep(i, 1, n) s[i] = s[i - 1] + a[i];
	rep(i, 1, m){
		len = R[i] - L[i] + 1;
		k = s[R[i]] - s[L[i] - 1];
		if(k * 2 > len) return 1; 
	}
	return 0;
}
int main(){
	int T; rd(T);
	while(T--){
		rd(n, m);
		rep(i, 1, m) rd(L[i], R[i]);
		int q; rd(q);
		rep(i, 1, q) rd(p[i]);
		cover(q);
		if(!check()){
			puts("-1");
			continue;
		}
		int l = 1, r = q;
		while(l < r){
			int mid = (l + r) >> 1;
			cover(mid);
			if(!check()) l = mid + 1;
			else r = mid;
		}
		prf("%d\n", l);
	}
	return 0;
}
```

 **[完整代码](https://codeforces.com/contest/1843/submission/210493092)**

---

## 作者：sz_jinzikai (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1843E) &[CF 传送门](https://codeforces.com/problemset/problem/1843/E)
# 思路
这题可以用二分答案来求解，让我们来看看怎么写 check 函数吧。首先，我们可以枚举每个区间和区间内的每个点，但是这样时间复杂度肯定超标，所以我们要想着优化。我们可以很容易地想到遍历每个区间内的点的时候太慢了，我们要把这部分从 $O(r_i-l_i)$ 变成 $O(1)$ 的，所以我们可以使用前缀和来优化，然后逐个枚举区间，判断当前区间中 $1$ 的个数是否大于区间中数字个数的一半即可，即 $s_{r_i}-s_{l_i-1}>\lfloor\frac{r_i-l_i+1}2\rfloor$，接着，正解就产生了。
# 代码
```cpp
# include <bits/stdc++.h> //万能头 
using namespace std;
int t, n, m, q, l[100005], r[100005], s[100005], a[100005]; //定义变量
/*
t 数据组数
n 序列长度
m 区间个数
q 修改次数
l 区间左端点
r 区间右端点
s 前缀和数组
a 修改的位置
*/
bool check (int mid) { //定义判断函数
	for (int i = 1; i <= n; ++ i)
		s[i] = 0; //多次利用要清空
	for (int i = 0; i < mid; ++ i)
		s[a[i]] = 1; //赋值
	for (int i = 2; i <= n; ++ i)
		s[i] += s[i - 1]; //计算前缀和
	for (int i = 0; i < m; ++ i) //枚举每个区间
		if (s[r[i]] - s[l[i] - 1] > (r[i] - l[i] + 1) / 2) //满足条件
			return 1; //提前返回
	return 0; //不满足条件
}
int main () { //定义主函数
	ios::sync_with_stdio (0); //关输入输出同步
	cin.tie (0); //cin 加速
	cout.tie (0); //cout 加速
	cin >> t; //输入数据组数
	while (t --) { //多组数据经典写法
		cin >> n >> m; //输入序列长度和区间个数
		for (int i = 0; i < m; ++ i)
			cin >> l[i] >> r[i]; //输入区间左右端点
		cin >> q; //输入修改次数
		for (int i = 0; i < q; ++ i)
			cin >> a[i]; //输入修改位置
		int l = 1, r = q, mid, best = -1; //定义二分要用的变量
		while (l <= r) { //二分继续条件
			mid = l + r >> 1; //计算中间数
			if (check (mid)) //如果成功了
				r = mid - 1, best = mid; //继续看左半段，更新答案
			else //如果不成功
				l = mid + 1; //继续看右半段
		}
		cout << best << '\n'; //输出最优解
	}
	return 0; //结束程序
}
```

---

## 作者：shuangmu (赞：0)

VP 的时候本来摆烂了，结果快结束的时候想到了做法（没时间敲了 qwq）。这里提供一种和上面题解不同的思路。

我们发现，对于每个修改，我们可以将该点的值修改为这次修改的时间，未修改的点则赋为 $n+1$。这样转化后，区间合法的条件就是区间内小于 $n+1$ 的值至少要有 $\lfloor \frac{r-l+1}{2} \rfloor+1 $ 个，我们令 $k = \lfloor \frac{r-l+1}{2} \rfloor+1$，，则最早达到合法条件的时间就是这些值中第 $k$ 小的。这样一来，我们就可以把问题转化为静态区间第 $k$ 小，主席树做就行。答案就是所有查询结果中最小值，如果都为 $n+1$ 则说明无解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+100;

int n, m;
int root[N], a[N];
int ls[30*N], sum[30*N], rs[30*N],tot;
int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch<'0'||ch>'9') {
		if(ch == '-')f = -1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9') {
		x = x*10+ch-48;
		ch = getchar();
	}
	return x*f;
}
void change(int &tr, int lst, int l, int r, int p) {
	tr = ++tot;
	sum[tr] = sum[lst]+1;
	if(l == r) return;
	int mid = (l+r)>>1;
	ls[tr] = ls[lst], rs[tr] = rs[lst];
	if(p <= mid) change(ls[tr], ls[lst], l, mid, p);
	else change(rs[tr], rs[lst], mid+1, r, p);
}
int query(int tr, int lst, int l, int r, int kth) {
	if(l == r) return l;
	int mid = (l+r)>>1;
	int tmp = sum[ls[tr]]-sum[ls[lst]];
	if(tmp>=kth) return query(ls[tr], ls[lst], l, mid, kth);
	else return query(rs[tr], rs[lst], mid+1, r, kth-tmp);
}

int T;
struct question{
	int l, r;
}q[N];
int main() {
	T = read() ;
	while(T--){
		
		n = read(), m = read();
		for(int i = 1; i<=m; ++i){
			q[i].l = read();
			q[i].r = read();
		}
		int Q = read();
		for(int i = 1; i<=n; ++i) a[i] = n+1;
		for(int i = 1; i<=Q; ++i){
			int tmp = read();
			a[tmp] = i;
		}
        
		for(int i = 1; i<=n; i++) change(root[i], root[i-1], 1, n+1, a[i]);
		int ans = n+1;
		for(int i = 1; i<=m; i++) {
			int kth = (q[i].r-q[i].l+1)/2+1;
			int tmp = query(root[q[i].r], root[q[i].l-1], 1, n+1, kth);
			if(tmp == n+1) continue;
			else ans = min(ans, tmp);
		}
		if(ans == n+1) puts("-1");
		else printf("%d\n", ans);
		for(int i = 1; i<=tot; ++i){//手动清空防止TLE
			ls[i] = rs[i] = sum[i] =  0;
		}
		for(int i = 1; i<=n; ++i) root[i] = 0;
		tot = 0;
	}

	return 0;
}
```



---

## 作者：_Only_this (赞：0)

### Tracking Segments

------------

打比赛时，我大佬同学用分块过了，而我只想到二分。

这题还是二分比较好想吧。

因为每次操作都是将一个 $0$ 改成 $1$，符合条件的区间肯定是越来越多的，所以显然具有单调性，然后就可以二分答案了。

每次二分出一个操作次数 $mid$，然后将 $1$ 到 $mid$ 的位置标记，用前缀和求出区间中 $1$ 的数量，判断当前二分的值符不符合条件。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
struct qwe{
	int l,r;
}a[maxn];
int T,n,m,q;
int pos[maxn],sum[maxn];
void Init(){
	memset(sum,0,sizeof sum);
	return ;
}
bool Check(int mid){
	for(int i=1;i<=mid;i++)
		sum[pos[i]]=1;
	for(int i=1;i<=n;i++)
		sum[i]+=sum[i-1];
	for(int i=1;i<=m;i++)
		if((sum[a[i].r]-sum[a[i].l-1]<<1)>a[i].r-a[i].l+1)
			return 1;
	return 0;
}
int Solve(){
	int l=1,r=q,mid,res=-1;
	while(l<=r){
		Init();
		mid=l+r>>1;
		if(Check(mid))
			r=mid-1,res=mid;
		else
			l=mid+1;
	}
	return res;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
			scanf("%d%d",&a[i].l,&a[i].r);
		scanf("%d",&q);
		for(int i=1;i<=q;i++)
			scanf("%d",&pos[i]);
		printf("%d\n",Solve());
	}
	return 0;
}
```
完结，散花(～￣▽￣)～



---

## 作者：ran_qwq (赞：0)

有一个长度为 $n$ 的序列 $a$，初始为 $0$。你有 $q$ 次操作，每次给定一个正整数 $x$，把 $a_x$ 赋为 $1$。

又有 $m$ 个区间 $[l_i,r_i]$。定义一个区间是“漂亮的”当且仅当区间 $1$ 的个数**严格大于** $0$ 的个数。求执行 $1\sim x$ 操作后，让 $m$ 个区间中至少一个是“漂亮的”的最小的 $x$。

---
不难发现，执行操作 $1$ 会越来越多。如果执行前 $x$ 次操作可以，那么前 $x+1$ 次操作也可以，具有单调性，考虑二分。

如何判断执行前 $x$ 次操作可不可以？可以把执行前 $x$ 次操作的数组求前缀和。再判断有没有一个区间 $1$ 的个数**严格大于** $0$ 的个数就行了。

```cpp
int check(int x)
{
	for(int i=0;i<=n;i++) b[i]=0;
	for(int i=1;i<=x;i++) b[a[i]]=1;
	for(int i=1;i<=n;i++) b[i]+=b[i-1];
	for(int i=1;i<=m;i++) if(b[R[i]]-b[L[i]-1]>R[i]-L[i]+1-(b[R[i]]-b[L[i]-1])) return 1;
	return 0;
}
void solve()
{
	n=read(),m=read();for(int i=1;i<=m;i++) L[i]=read(),R[i]=read();
	q=read();for(int i=1;i<=q;i++) a[i]=read();
	int l=1,r=q,ans=-1;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	write(ans,"\n");
}
```

---

