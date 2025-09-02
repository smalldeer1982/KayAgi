# Salary Changing

## 题目描述

You are the head of a large enterprise. $ n $ people work at you, and $ n $ is odd (i. e. $ n $ is not divisible by $ 2 $ ).

You have to distribute salaries to your employees. Initially, you have $ s $ dollars for it, and the $ i $ -th employee should get a salary from $ l_i $ to $ r_i $ dollars. You have to distribute salaries in such a way that the median salary is maximum possible.

To find the median of a sequence of odd length, you have to sort it and take the element in the middle position after sorting. For example:

- the median of the sequence $ [5, 1, 10, 17, 6] $ is $ 6 $ ,
- the median of the sequence $ [1, 2, 1] $ is $ 1 $ .

It is guaranteed that you have enough money to pay the minimum salary, i.e $ l_1 + l_2 + \dots + l_n \le s $ .

Note that you don't have to spend all your $ s $ dollars on salaries.

You have to answer $ t $ test cases.

## 说明/提示

In the first test case, you can distribute salaries as follows: $ sal_1 = 12, sal_2 = 2, sal_3 = 11 $ ( $ sal_i $ is the salary of the $ i $ -th employee). Then the median salary is $ 11 $ .

In the second test case, you have to pay $ 1337 $ dollars to the only employee.

In the third test case, you can distribute salaries as follows: $ sal_1 = 4, sal_2 = 3, sal_3 = 6, sal_4 = 6, sal_5 = 7 $ . Then the median salary is $ 6 $ .

## 样例 #1

### 输入

```
3
3 26
10 12
1 4
10 11
1 1337
1 1000000000
5 26
4 4
2 4
6 8
5 6
2 7
```

### 输出

```
11
1337
6
```

# 题解

## 作者：Weakest_Konjac (赞：7)

时间复杂度：$O\left(Tn \ log  \ n+Tn  \ log \ s\right)$

前置知识：二分答案+贪心

读完题目，不难想到二分答案。大概思路：二分中位数，贪心判断。问题主要是如何贪心判断是否满足。

我们把第$i$个员工的薪水范围表示为$num\left[i\right].l,num\left[i\right].r$，把当前中位数表示为$mid$。我们可以把员工的薪水分为三类：

第一类：薪水上界小于中位数，即$num\left[i\right].r<mid$

第二类：薪水下界大于中位数，即$num\left[i\right].l>mid$

第三类：薪水下界小于等于中位数，上界大于等于中位数，即$num\left[i\right].l<=mid$且$num\left[i\right].r>=mid$

对于第一类，薪水一定小于中位数，为了节省钱，我们支付$num\left[i\right].l$的薪水

对于第一类，薪水一定大于中位数，为了节省钱，我们支付$num\left[i\right].l$的薪水

然后我们通过第三类来调节大于等于中位数的薪水数和小于中位数的薪水数，让大于等于中位数的薪水数$>$小于中位数的薪水数

于是，对于第三类，我们还需支付薪水小于中位数的数量和支付薪水大于中位数的数量是确定的，所以为了节省钱，我们对于下界小的一部分，支付下界$num\left[i\right].l$，对于其他部分，支付中位数$mid$。

具体解释可看代码

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
const int N=2e5+5;
struct node{
	int l,r;
}num[N];
struct cmp{
	inline bool operator () (const node&a,const node&b){
		return a.l<b.l;
	}
};
int T,n,tot[N];
long long s;
inline int check(long long mid){
	int cnt=0,cnt1=0,cnt2=0;//cnt为第三类薪水数，cnt1为第一类薪水数，cnt2位第二类薪水数
	long long sum=0;
	for (register int i=1;i<=n;++i)
		if (num[i].r<mid) sum+=num[i].l,++cnt1;//第一类
		else if (num[i].l>mid) sum+=num[i].l,++cnt2;//第二类
		else tot[++cnt]=i;//第三类薪水编号记录
	if (cnt1>(n>>1)||cnt2>(n>>1)) return 0;//如果第一类或第二类薪水数大于所有薪水数的一半，即大于或小于中位数的数大于一半，肯定不满足
	for (register int i=1;i<=(n>>1)-cnt1;++i) sum+=num[tot[i]].l;//对于num[i].l小的部分
	sum+=1ll*mid*((n>>1)+1-cnt2);//其他部分
	return sum<=s;
}
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d%lld",&n,&s);
		for (register int i=1;i<=n;++i) scanf("%d%d",&num[i].l,&num[i].r);
		sort(num+1,num+n+1,cmp());//将num[i].l从小到大排序
		long long l=num[(n>>1)+1].l,r=1ll*s/((n>>1)+1);//二分上下界自己极端估计一下
		while (l<=r){
			long long mid=l+r>>1;
			check(mid)?l=mid+1:r=mid-1;
		}
		printf("%lld\n",l-1);
	}
	return 0;
}
```


---

## 作者：灵茶山艾府 (赞：7)

提供一个比官方题解还简洁的二分思路。

观察发现中位数越大，发出的工资越多，这满足二分条件。

先预处理，将数据按照 $l$ **从大到小**排序。

然后二分中位数 $x$，贪心地计算所发工资是否不超过 $s$：

从左到右扫描排序后的数据，把 $r\geq x$ 的找出来计算额外发出的工资 $max(0,x-l)$，直到找到 $\frac{n}{2}$ 个。这样保证找到的数加上额外发出的工资都是不小于 $x$ 的，同时额外发出的工资尽可能地小。

对于 $r<x$ 的数据，有 $l\leq r<x$，所以这些数据全部位于中位数的一侧，额外发工资不会影响中位数，故不处理。

AC 代码如下：（Golang）

```go
package main

import (
    "bufio"
    . "fmt"
    "io"
    "os"
    "sort"
)

func search(n int64, f func(int64) bool) int64 {
    i, j := int64(0), n
    for i < j {
        h := (i + j) >> 1
        if f(h) {
            j = h
        } else {
            i = h + 1
        }
    }
    return i
}

func solve(reader io.Reader, writer io.Writer) {
    type pair struct{ l, r int64 }
    in := bufio.NewReader(reader)
    out := bufio.NewWriter(writer)
    defer out.Flush()

    var q, n int
    for Fscan(in, &q); q > 0; q-- {
        var money, baseCost int64
        Fscan(in, &n, &money)
        ps := make([]pair, n)
        for i := range ps {
            Fscan(in, &ps[i].l, &ps[i].r)
            // 预处理：基础工资之和
            baseCost += ps[i].l
        }
        
        // 预处理：从大到小排序
        sort.Slice(ps, func(i, j int) bool { return ps[i].l > ps[j].l })
        
        ans := search(money+1e9+1, func(x int64) bool {
            cnt := 0
            cost := baseCost
            for _, p := range ps {
            	// 把 r >= x 的找出来（n/2 个）
                if p.r >= x {
                    cnt++
                    if p.l < x {
                    	// 计算额外发出的工资
                        cost += x - p.l
                    }
                    if 2*cnt-1 == n {
                        // 能否发出工资
                        return !(cost <= money)
                    }
                }
            }
            // x 取大了
            return !false
        })
        Fprintln(out, ans-1)
    }
}

func main() {
    solve(os.Stdin, os.Stdout)
}
```


---

## 作者：HYXLE (赞：3)

## Salary Changing

首先发现答案具有单调性，即若 $x$ 可以作为中位数，则 $x-1$ 也可以作为中位数。

因为当中位数是 $x$ 的时候，所花费的工资总价值大于等于中位数是 $x-1$ 的时候。

如何判断 $x$ 是否可以当作中位数？

发现可以将所有人的工资分为 $3$ 类：

第一类:工资的上界小于 $x$，记他们的人数是 $cnt1$。

第二类:工资的下界大于 $x$，记他们的人数是 $cnt2$。

第三类:工资的下界小于等于 $x$，且工资的上界大于等于 $x$ ，记他们的人数是 $cnt3$。

显然第一类和第二类的人是无法对中位数产生影响的，不妨全部取这些人的工资的下界。

显然若 $cnt1 > \frac{n}{2}$ ，则这个数不可能作为中位数 $x$ 。

后面就可以贪心的去做了。

具体而言，对于第三类人中分别取他们的下界或者 $x$，不难发现可以贪心的选出第三类人中下界前 $\frac{n}{2} - cnt1$ 小的人取他们的下界，剩下的 $\frac{n+1}{2} - cnt2$ 人全部取 $x$。

最后判断一下总花费是否小于等于 $x$ 即可。

注意求出二分的上下界。

### 代码:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=2e5+5;
struct node{ll l,r;}a[N];
inline bool cmp(node x,node y){return x.l<y.l;}
ll n,s,id[N];
inline bool check(ll x){
	ll sum=0,cnt1=0,cnt2=0,cnt3=0;
	for(R int i=1;i<=n;++i){
		if(a[i].r<x)++cnt1,sum+=a[i].l;
		else if(a[i].l>x)++cnt2,sum+=a[i].l;
		else id[++cnt3]=i;
	}
	if(cnt1>(n>>1))return 0;
	for(R int i=1;i<=(n>>1)-cnt1;++i)sum+=a[id[i]].l;
	sum+=((n+1>>1)-cnt2)*x;
	return sum<=s;
}
inline void solve(){
	cin>>n>>s;
	for(R int i=1;i<=n;++i)cin>>a[i].l>>a[i].r;
	sort(a+1,a+n+1,cmp);
	ll l=a[(n+1)>>1].l,r=s/((n+1)>>1);ll res=l;
	while(l<=r){
		ll mid=l+r+1>>1;
		if(check(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	cout<<res<<'\n';
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int _;cin>>_;while(_--)solve();
	return 0;
}
```

---

## 作者：yangmuguang (赞：1)

### 题意

你有 $s$ 元钱、$n$ 个人，第 $i$ 个人需要给他 $l_i$ 至 $r_i$ 元钱，目标是使所有人拿到的钱中位数最大。

### 思路

答案明显具有单调性，考虑二分。

假设目标中位数是 $x$。对于第 $i$ 个人，有 $3$ 种情况：

- $r_i < x$：假设 $a$ 个。无论如何都无法比 $x$ 大，取 $l_i$。
- $x\le l_i$：假设 $b$ 个。一定大于等于 $x$，取 $l_i$。
- $l_i<x\le r_i$：假设 $c$ 个。要么取 $x$，让大于等于$x$ 的数量 +1，要么取 $l_i$。由于至少 $\frac{n+1}{2}$ 个数大于等于 $x$，把 $l_i$ 最大的 $\frac{n+1}{2}-b$ 个人取 $x$，剩下的取 $l_i$。若 $b+c<\frac{n+1}{2}$，则无解。

将最后答案与 $s$ 比较，得出结果。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
ll t,n,s;
struct _
{
	ll l,r;
	bool operator<(_ ot)
	{
		return l==ot.l?r<ot.r:l<ot.l;
	}
}a[200005];
bool chk(ll x)
{
	vector<ll>v;
	ll cnt=0,sum=0;
	for (ll i=1;i<=n;i++)
	{
		if (a[i].r<x)
		{
			sum+=a[i].l;
		}
		else if (a[i].l>=x)
		{
			sum+=a[i].l;
			cnt++;
		}
		else v.pb(i);
	}
	ll need=max(0ll,(n+1)/2-cnt);
	if (need>v.size())return 0;
	for (ll i=0;i<v.size();i++)
	{
		if (i<v.size()-need)
		{
			sum+=a[v[i]].l;
		}
		else 
		{
			sum+=x;
		}
	}
	return sum<=s;
}
int main()
{
	faster;
	cin>>t;
	while (t--)
	{
		cin>>n>>s;
		for (ll i=1;i<=n;i++)
		{
			cin>>a[i].l>>a[i].r;
		}
		sort(a+1,a+1+n);
		ll l=0,r=s,ans;
		while (l<=r)
		{
			ll mid=(l+r)/2;
			if (chk(mid))
			{
				l=mid+1;
				ans=mid;
			}
			else
			{
				r=mid-1;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：thjkhdf12 (赞：1)

### **本题做法为二分+贪心**

题意为寻找一个最大的中位数（翻译已有就不细说了）

做法为对于每个员工的工资区间，按照其区间的左端点进行排序（方便二分查找答案）

显然按左端点排序后$a[n/2+1].left$是一个可行的答案，因为一定可以有$n/2$个人发的工资可以比这个人多，也一定可以有$n/2$个人发的工资比这个人少（一律取$left$）就可以了

然后对于可能的答案区间$[a[n/2+1].left,s]$进行二分查找，验证当前查找到的值是否满足条件，（即使它为中位数，也就是可以找到$n/2$个比它大或者与它相等的值），至于如何验证这个值是否符合条件见代码

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define mfor(i,a,b) for(register int i=(a);i<=(b);i++)
#define mrep(i,a,b) for(register int i=(a);i>=(b);i--)
#define Re register
typedef pair<int, int> intpair;
typedef pair<long long int, long long int> llpair;
typedef long long int LL;

const int maxn = 1000010;

LL n;
LL s;
LL ans;
int T;
llpair a[maxn];

bool operator >(llpair a, llpair b)
{
    return a.first > b.first;
}

bool check(LL x)	//检查是否符合条件的
{
    LL t = (n >> 1) + 1;    //需要满足有t个工资大于等于x
    LL sum = 0;
    mfor(i, 1, n)
    {
        if (t && a[i].first <= x && x <= a[i].second)
        {
            //这个工人可以被发x的工资
            //贪心策略，一律取等于
            sum += x;
            t--;
        }//如果t已经归零，那么就不需要更多的比x大的值
        else
        {
            //贪心策略，不能被发x的工资，那就给他发能给的最少工资
            sum += a[i].first;
            if (a[i].first >= x && t) t--;//如果这个最少工资比x大
            //因为二分区间左端一定是一个可行解保证了不会有少于n/2个人工资可以比x小的情况
            }
    }
    if (t) return 0;    //不满足条件，x不能是中位数
    return sum <= s;    //判断钱是否足够
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--)
    {
        ans = 0;
        cin >> n >> s;
        mfor(i, 1, n) cin >> a[i].first >> a[i].second;
        sort(a + 1, a + n + 1, greater<llpair>());
        LL l = a[(n >> 1) + 1].first, r = s;
        ans = a[(n >> 1) + 1].first;
        while (l <= r)
        {
            LL mid = (l + r) >> 1;
            if (check(mid))
            {
                ans = mid;
                l = mid + 1;
                //满足条件，继续查询能不能有更大的ans
            }
            else r = mid - 1;	//注意不能写while(l<r) 这里写r=mid，会WA，原因请自行思考
            //不满足条件，小一些看能否符合条件
        }
        cout << ans << endl;
    }
    return 0;
}

---

## 作者：梧桐灯 (赞：1)

当时比较晚，所以睡了。。。

然而关掉电脑，突然想到：这题不是一个很显然的二分嘛……

我的二分思路：

首先按右端点从大到小排序取出中间线段的右端点$y$，再按左端点从小到大排序取出中间线段的左端点$x$。那么，在区间$[x,y]$内的中位数一定可行（不考虑钱数）。

此时对于一个中位数我们只需判断最小钱数$<=s$即可。那么对于右端点小于中位数的无论怎么取都只会比中位数小，肯定只取左端点（腾出更多的钱给其他）；左端点比中位数打的同理，只取左端点。

对于跨越中位数的，我们一部分去左端点，一部分取中位数，只要保证取得最小即可。

代码：
```
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
template <typename T> inline void read (T& s) {
	s = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar ();
	return ;
}

const int N = 200003;
int Q, n; ll m;
struct stu {
	int x, y;
}s[N];
int a[N];

inline int cmp1 (const stu& p, const stu& q) {
	return p.x < q.x;
}

inline int cmp2 (const stu& p, const stu& q) {
	return p.y > q.y;
}

inline int pd (const int mid) {
	int i, gr = 0, lo = 0, xd = 0;
	ll tot = 0;
	for (i = 1; i <= n; ++i) {
		if (s[i].y < mid) tot += s[i].x, ++lo;
		else if (s[i].x > mid) tot += s[i].x, ++gr;
		else a[++xd] = i;
	} //跨越中位数的存在a数组里
	int j = xd;
	i = 1;
	while (i < j) {
		if (lo < gr) tot += s[a[i++]].x, ++lo; //如果当前比中位数小的数的个数更小，就去左端点较小的跨越中位数的
		else tot += mid, --j, ++gr;
	}
	return tot + mid <= m;
}

int main () {
	read (Q); while (Q--) {
		read (n), read (m);
		int i; for (i = 1; i <= n; ++i) read (s[i].x), read (s[i].y);
		int L, R, mid;
		sort (s + 1, s + n + 1, cmp2); R = s[n + 1 >> 1].y;
		sort (s + 1, s + n + 1, cmp1); L = s[n + 1 >> 1].x;
		while (L <= R) { //二分
			mid = L + R >> 1;
			if (pd (mid)) L = mid + 1;
			else R = mid - 1;
		}
		printf ("%d\n", L - 1);
	}
	return 0;
}
```

---

## 作者：endswitch (赞：0)

二分答案后贪心，对于原序列分三种情况讨论即可。

假设已经二分出一个中位数：

- $r$ 低于中位数或者 $l$ 高于中位数，直接填 $l$ 即可。
- 否则，就先填满不足中位数的部分，对于大于等于中位数大力填中位数即可。

最后特判一下是否方案是否合法。

给出二分代码：

```cpp
inline bool check(int x) {
    int res = 0, cnt1 = 0, cnt2 = 0;

    for(int i = 1 ; i <= n ; ++ i) {
        if(r[i] < x) ++ cnt1, res += l[i];
        else if(l[i] > x) ++ cnt2, res += l[i];
    }

    cnt1 = (n >> 1) - cnt1;
    cnt2 = (n >> 1) - cnt2;

    if(cnt1 < 0) return /*cerr << "cnt:" << cnt1 << ' ' << cnt2 << '\n', */false;

    for(int i = 1 ; i <= n ; ++ i) {
        if(l[id[i]] <= x && r[id[i]] >= x) {
            if(cnt1) {
                -- cnt1;
                
                res += l[id[i]];
            }
            else res += x;
        }
    }
    
    // cerr << "sub:" << n << ' ' << res << '\n';
    
    // if(cnt1 > 1 || cnt2 > 1 || (cnt1 == 1 && cnt2 == 1) || res > s) return false;

    if(res > s) return false;
    
    return true;
}
```

---

## 作者：makerlife (赞：0)

[Blog](https://blog.makerlife.top/post/2024-practice-record/#CF1251D)

二分枚举中位数，考虑贪心地 check。将要求转化为一段段区间，对于一个区间 $i$，有三种情况：中位数大于/小于区间或在区间内。

- 对于前两种情况，一定不会产生中位数，为了省钱选下界；
- 对于第三种情况，因为此时剩余数量已经确定，为了满足总钱数最小，对于 $l$ 小的区间，仍然选左端点；而为了满足中位数，剩下的部分区间需要选择中位数。

```cpp
#define int ll
bool check(int x) {
    int sum = 0;
    int tot = 0;
    vector<int> p;
    for (int i = 1; i <= n; i++) {
        if (a[i].r < x) {
            sum += a[i].l;
        } else if (a[i].l >= x) {
            tot++;
            sum += a[i].l;
        } else {
            p.emplace_back(a[i].l);
        }
    }
    sort(p.begin(), p.end());
    int remain = max(0ll, ((n + 1) >> 1ll) - tot);
    if (remain > (int)p.size()) return 0;
    for (int i = 0; i < (int)p.size(); i++) {
        if (i < (int)p.size() - remain) sum += p[i];
        else sum += x;
    } 
    if (sum > s) return 0;
    return 1;
}
signed main() {
    T = read();
    while (T--) {
        n = read(), s = read();
        for (int i = 1; i <= n; i++) {
            a[i].l = read(), a[i].r = read();
        }
        int l = 1, r = MAXN;
        while (l < r) {
            int mid = (l + r + 1) >> 1ll;
            if (check(mid)) l = mid;
            else r = mid - 1;
        }
        cout << l << '\n';
    }
    return 0;
}
```

---

## 作者：LeBao2023 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1251D)

“中位数最大”，可以使用二分。

二分中位数，设为 $x$，如何判断是否可行，check 怎么做？

工资的区间可以分为三类：

* 发的工资怎么样也不超过 $x$，即 $r_i<x$，像这样的区间个数记为 $cnt1$。

* 发的工资怎么样也会超过 $x$，即 $l_i>x$，像这样的区间个数记为 $cnt2$。

* 发的工资包含 $x$，即 $l_i\le x\le r_i$。

下面有几种情况：

* $cnt1>\frac{n}{2}$，即有大于一半的的人发不到 $x$ 那么多的工资，直接返回 false。

* $cnt2>\frac{n}{2}$，即有大于一半的的人怎么发工资都比 $x$ 多，直接返回 true。

* 其他情况。

对于其他情况，很容易发现1，2两种情况中工资取多少对中位数没有影响，贪心的给他们发最少的工资。我们可以把第三种人进行讨论。

第三种人要不就用自己的最低价 $l_i$ 来发工资，要么用 $x$ 来发工资，可以证明这是最优的。

其中应该会有 $\frac{n}{2}-cnt1$ 个人发 $l_i$ 的工资，还有其他人发 $x$ 的工资，当然是给第三种人中 $l_i$ 前 $\frac{n}{2}-cnt1$ 小的人发 $l_i$ 的工资。

最后，$x$ 一定是这一串数的中位数。

判断要发的工资和手头上的钱 $s$ 作比较，判断是否可行。

注意二分的区间。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int n,s;
struct node
{
	int a,b;
}p[maxn];
bool cmp(node a,node b)
{
	return a.a<b.a;
}
bool check(int mid)
{
	int l=0,r=0,sum=0;
	for(int i=1;i<=n;i++)
	{
		if(p[i].b<mid)
		{
			l++;
			sum+=p[i].a;
		}
		if(p[i].a>mid)
		{
			r++;
			sum+=p[i].a;
		}
	}
	if(r>n/2)
	{
		return true;
	}
	if(l>n/2)
	{
		return false;
	}
	for(int i=1;i<=n;i++)
	{
		if(p[i].b<mid||p[i].a>mid)
		{
			continue;
		}
		if(l<n/2)
		{
			l++;
			sum+=p[i].a;
		}
		else
		{
			r++;
			sum+=mid;
		}
	}
	return sum<=s;
}
void solve()
{
	int l=0,r=0;
	cin>>n>>s;
	for(int i=1,a,b;i<=n;i++)
	{
		cin>>p[i].a>>p[i].b;
		r=max(r,p[i].b);
	}
	sort(p+1,p+n+1,cmp);
	l=p[n/2+1].a;
	while(l<r)
	{
		int mid=l+r+1>>1;
		if(check(mid))
		{
			l=mid;
		}
		else
		{
			r=mid-1;
		}
	}
	cout<<l<<'\n';
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		solve();
	}
}
```

时间发杂度：$O(T(nlogn+nlogV))$，其中 $V$ 是 $l_i,r_i$ 的值域。

---

## 作者：zhangyaiwei (赞：0)

## 题解

很明显，工资中位数满足单调性，考虑二分答案出工资中位数，然后选出一半人提到中位数以上，然后判断可行性。

发现二分出来 $mid$ 之后，这些员工被分成了4种：
1. 工资最大值小于 $mid$，这时候就没法提（①）
2. 工资最小值大于 $mid$，这时候必须选择（④）
3. 除开以上两种的情况，而且被选上（②）
4. 除开开始两种的情况，但因为人数限制没被选上（③）
![](https://cdn.luogu.com.cn/upload/image_hosting/6hxozy61.png)
实际上，这里的①和②是会有交错的，但是~~懒得画了~~

①和④判断起来很容易，而②和③的区分也不麻烦，想一下就能发现，选择最大的一部分答案一定不会劣，所以可以给②和③部分的 $l_i$ 排个序，从大往小选 $\lfloor \frac{n}{2}\rfloor-④+1$ 个，统计一下花费即可。

还要注意一下，如果①的部分超过了一半，则可以直接判无解。

时间复杂度：二分+排序=$O(n\log n\log s)$

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,s,l[211111],r[211111];
bool C(int x){
	int ndb=n/2+1;
	vector<int> v;
	for(int i=1;i<=n;i++){
		if(l[i]>x){
			ndb--;//需要的③减少
		}
		if(l[i]<=x&&x<=r[i]){
			v.push_back(l[i]);
		}
	}
	ndb=max(ndb,0ll);
	if(ndb>v.size()) return 0;//判无解
  	sort(v.begin(),v.end());//对 l 排序
	int cnt=0;
	for(int i=1;i<=ndb;i++){
		int t=v[v.size()-i];
		cnt+=x-t;
	}
	return cnt<=s;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>s;
		for(int i=1;i<=n;i++){
			cin>>l[i]>>r[i];
			s-=l[i];
		}
		int l=0,r=2e9,ans=0;
		while(l<r){
			int mid=(l+r)/2;
			if(C(mid)){
				l=mid+1;
				ans=mid;
			}
			else{
				r=mid;
			}
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

老中位数题了。

你有 $N$（$N$ 为奇数）个员工和 $S$ 元钱用来给员工支付工资。对于员工 $i$，其工资可以在一个区间 $[L_i,R_i]$ 内自由浮动。你需要最大化员工工资的中位数。求这个中位数。

发现中位数是否合法是有单调性的，考虑二分并判断当前中位数是否可行。

发现工资在中位数以上时增加工资并不会增加中位数，所以为了省钱来增加中位数，我们要么支付底薪，要么支付中位数工资。

设当前中位数为 $x$。那么对于每一个员工，其工资区间可能有三种情况：

- $x \le L_i$
- $L_i \le x \le R_i$
- $R_i \le x$

如果 $x$ 是中位数，那么会有至少 $\frac{n+1}{2}$ 个员工工资为 $x$ 以上。设这个个数为 $cnt$。

对于第一种情况，虽然不影响中位数的可行性，但为了省钱，我们支付底薪并增加 $cnt$。  
对于第二种情况，由于工资可以浮动，我们先把底薪存在一个数组 $V$ 内再决定支付底薪还是 $x$。  
对于第三种情况，由于不可能支付 $x$ 元工资，我们只支付底薪，不增加数量。

把 $V$ 里面的底薪排个序，发现里面只有一些员工要支付 $x$ 元。由于此时 $V_i \le x$，支付更多底薪显然更省钱，可行概率也更大。

具体来说，此时已经支付了 $cnt$ 个 $x$ 元，那就还剩下 $\frac{n+1}{2}-cnt$ 个。当然如果已经支付完 $\frac{n+1}{2}$ 个了，甚至还有多就一个也不会剩。我们令 $C$ 为剩下的个数。

如果第二种情况的数量还没有 $C$ 多，就不可行。

注意到无论你底薪多少，只要你支付 $x$ 元工资你就只会计算 $1$ 个个数贡献。贪心性质就很明显了，只需要把底薪最高的 $C$ 个员工支付 $x$ 元，剩下支付底薪，就是最省钱的。

最后判断最省钱的方案需要的金额是否小于等于 $s$ 即可。

---

## 作者：T_TLucas_Yin (赞：0)

这题的做法是二分。乍一看这题似乎不符合二分规律，因为如果你给出的中位数小于所有员工的 $l_i$，那么程序也会返回这个数过大。但其实我们只需要合理设置左右端点就可以避免这个问题。

注意到对于一个序列（长度为奇数）的中位数，一定有 $\frac{n+1}{2}$ 个数不大于它，有 $\frac{n+1}{2}$ 个数不小于它。因此我们要把 $l$ 和 $r$ 分别排序后，左端点设为 $l_{\frac{n+1}{2}}$，右端点设为 $r_{\frac{n+1}{2}}$，这样就可以避免中位数一侧根本不可能有足够多的数，进而发生越界的情况。

接下来考虑如何判断一个数是否能成为该序列的中位数。同样的，若一个数是中位数，则一定有 $\frac{n+1}2$ 个数不大于它。我们先给每个员工发 $l_i$ 的工资，然后找到此时发到的薪水不大于 $k$ 的员工。根据规律，我们需要让满足此条件的员工不超过 $\frac{n+1}2$ 个。若一开始有更多的员工，则给其中一些 $r_i>k$ 的员工发更多的薪水，他们移动到 $k$ 的右边，$k$ 更靠近中间。若在所有钱花完之前薪水不大于 $k$ 的员工数量可以不超过 $\frac{n+1}2$，则 $k$ 符合条件。否则不符合条件。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,a[1000005],b[1000005];
struct node{
	int l,r;
}c[1000005];
bool cmp(node a,node b){
	if(a.l!=b.l) return a.l<b.l;
	return a.r<b.r;
}
bool check(int k){
	int x=m;
	if(k*(n+1)/2>x) return 0;
	for(int i=1;i<=n;i++) x-=a[i];
	int i=n,top=n;
	while(c[i].l>k) i--,top--;
	for(;i>=1;i--){
		if(top<(n+1)/2) return 1;
		if(c[i].r<k) continue;
		if(x<k-c[i].l) return 0;
		x-=k-c[i].l,top--;
	}
	if(top<(n+1)/2) return 1;
	else return 0;
}
int read(){
	int x=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
	return x;
}
signed main(){
	t=read();
	while(t--){
		n=read(),m=read();
		for(int i=1;i<=n;i++) a[i]=read(),b[i]=read();
		for(int i=1;i<=n;i++) c[i].l=a[i],c[i].r=b[i];
		sort(c+1,c+1+n,cmp);
		sort(a+1,a+1+n);
		sort(b+1,b+1+n);
		int l=a[(n+1)/2],r=b[(n+1)/2],mid,k=l;
		while(l<=r){
			mid=(l+r)>>1;
			//cout<<l<<" "<<r<<" "<<mid<<"\n";
			if(check(mid)) l=mid+1,k=mid;
			else r=mid-1;
		}
		printf("%lld\n",k);
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

简单题。

考虑二分中位数 $mid$ 后答案变成将 $\frac{n+1}{2}$ 个数调整到大于等于 $mid$。

考虑选取出可以调整到大于等于 $mid$ 的数以及从 $l_i$ 调整到这里的代价，排序后取前 $\frac{n+1}{2}$ 小即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
int l[maxn],r[maxn],n;
int s;
bool cmp(int x,int y){return x<y;}
bool check(int x){
    vector<int> vec;
    for(int i=1;i<=n;i++){
        if(x<=r[i]) vec.push_back(max(0*1ll,x-l[i]));
    }
    sort(vec.begin(),vec.end(),cmp);
    if(vec.size()<(n+1)/2) return false;
    int sum=0;
    for(int i=0;i<(n+1)/2;i++) sum+=vec[i];
    return sum<=s;
}
void work(){
    cin>>n>>s;
    for(int i=1;i<=n;i++){
        cin>>l[i]>>r[i],s-=l[i];
    }
    int l=0,r=1e18;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(check(mid)==true) l=mid;
        else r=mid;
    }
    cout<<l<<'\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

## 作者：Hot_tear (赞：0)

题意不再赘述。

考虑二分，即二分中位数为 $x$ 判断是否可以满足大于等于 $x$，问题满足单调性

考虑贪心，可以先使得每个员工拥有其最小的工资，那么这个时候一个中位数可以被表示出来当且仅当可以让 $\lfloor\dfrac{n}{2}\rfloor+1$ 个人的工资大于等于这个中位数即可

考虑更为具体的贪心策略，二分中位数 $x$，先算出每个人的工资变成 $x$ 的最小花费，如果这个人的工资最低也要大于等于 $x$ ，那么累计进一个变量 $cnt$ 中，最后使得   个原来工资小于 $x$ 的人的工资等于 $x$ 即可，并且一定是这几个人的最高工资大于等于 $x$

考虑时间复杂度： $\mathrm{O}(n\log^2n)$，二分 $\mathrm{O}(\log n)$，计算每个人需要多少花费变成 $x$ 并排序取出前 $\dfrac{n}{2}+1-cnt$ 的时间复杂度，也即排序复杂度，即 $\mathrm{O}(n\log n)$，复杂度相乘即可

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for(ll i=a;i<=b;i++)
#define R(i,a,b) for(ll i=a;i>=b;i--)
#define sc(a) scanf("%lld",&a)
#define ps(a) printf("%lld ",a)
#define pn(a) printf("%lld\n",a)
using namespace std;
const ll N=3e6+7;
ll T,n,m,p,c[N],sum=0;
struct Segment{
	ll l,r;
}t[N];
inline bool cmp(const Segment &a,const Segment &b){
	if(a.l==b.l){
		return a.r<b.r;
	}
	return a.l<b.l;
}
inline bool check(ll x){
	ll tot=0;
	for(ll i=1;i<=n;i++){
		c[i]=x-t[i].l;
		if(t[i].r<x){
			c[i]=1e18;
		}
		if(c[i]<=0){
			c[i]=1e18;
			tot++;
		}
	}
	ll val=0;
	sort(c+1,c+n+1);
	const ll inf=1e18;
	for(ll i=1;i<=n/2+1-tot;i++){
		if(c[i]==inf) return false;
		val+=c[i];
	}
	if(sum+val>m) return false;
	return true;
}
int main(){
	sc(T);
	p=T;
	while(T--){
		sc(n),sc(m);
		sum=0;
		for(ll i=1;i<=n;i++) sc(t[i].l),sc(t[i].r),sum+=t[i].l;
		ll l=1,r=m,ans=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		pn(ans);
	}
	return 0;
}

```

---

