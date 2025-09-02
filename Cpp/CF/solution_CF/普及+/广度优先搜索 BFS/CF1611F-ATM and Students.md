# ATM and Students

## 题目描述

Polycarp started working at a bank. He was assigned to monitor the ATM. The ATM initially contains $ s $ rubles.

A queue of $ n $ students lined up to him. Each student wants to either withdraw a certain amount of money or deposit it into an account. If $ a_i $ is positive, then the student credits that amount of money via ATM. Otherwise, the student withdraws $ |a_i| $ rubles.

In the beginning, the ATM is turned off and an arbitrary number of students are not served. At some point, Polycarp turns on the ATM, which has an initial amount of $ s $ rubles. Then, the remaining students start queueing at the ATM. If at some point in time there is less money in the ATM than the student wants to withdraw, then the student is not served and Polycarp turns off the ATM and does not turn it on anymore.

More formally, the students that are served are forming a contiguous subsequence.

Polycarp wants the ATM to serve the maximum number of students. Help him in this matter. Print the numbers of the first and last student, or determine that he will not be able to serve anyone.

In other words, find such a longest continuous segment of students that, starting with the sum of $ s $ at the ATM, all these students will be served. ATM serves students consistently (i.e. one after another in the order of the queue).

## 说明/提示

In the first test case, the only correct answer is 2 4, since when serving students, the number of rubles at the ATM does not become negative, and this is the maximum number of students that can be served.

In the second test case, the answer is -1, as there is not enough money for any student at the ATM.

In the third test case, the answer can be either 1 2 or 4 5.

## 样例 #1

### 输入

```
3
4 10
-16 2 -6 8
3 1000
-100000 -100000 -100000
6 0
2 6 -164 1 -1 -6543```

### 输出

```
2 4
-1
1 2```

# 题解

## 作者：Rushroom (赞：7)

[传送门](https://www.luogu.com.cn/problem/CF1611F)

第一篇 $O(n)$ 题解？

### 思路

我们使用 two pointers 来做这道题。

每次左指针向右移动一格，右指针尽量向右移动，用 $sum$ 记录左右指针之间所有数的和，如果 $s+sum<0$ 就停止移动右指针，并且用 $r-l+1$ 来更新答案。

复杂度为 $O(n)$ 。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i, a, n) for (int i = a; i <= n; i++)
#define rep(i, n) forr(i, 0, n - 1)
#define repp(i, n) forr(i, 1, n)
#define pb push_back
#define mp make_pair
#define init(a, i) memset(a, i, sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T, case_;
int n, a[200005], r, ans, ansl, ansr;
ll s, sum;
void solve()
{
    cin >> n >> s;
    rep(i, n) cin >> a[i];
    r = -1;
    sum = 0;
    ans = -1;
    rep(i, n)
    {
        if (r < i)
            r = i, sum = a[i];
        while (r < n && s + sum >= 0)
        {
            if (r - i + 1 > ans)
                ans = r - i + 1, ansl = i, ansr = r;
            r++, sum += a[r];
        }
        if (r < n)
            sum -= a[r], r--;
        else
            break;
        sum -= a[i];
    }
    if (ans == -1)
        cout << ans << endl;
    else
        cout << ansl + 1 << ' ' << ansr + 1 << endl;
}
int main()
{
    T = 1;
    cin >> T;
    for (case_ = 1; case_ <= T; case_++)
        solve();
    return 0;
}//by JFHT
```


---

## 作者：XL4453 (赞：6)

### 解题思路:

~~1800 就这？~~

考虑尺取法，每一次向右移动一次右指针，然后不断向右移动左指针直到满足条件，这个过程中维护当前剩下的钱就行了。

一个小 trick 就是可以让左指针移动超过右指针一个单位，再更改一下计算长度的代码，使得算下来的答案无法更新 ans，直接省去无解的特判。


注意用长整型存储数据。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int l,r,a[200005],T,n,now,ans=-1,ansl,ansr;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d%I64d",&n,&now);
		for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
		r=0;
		ans=-1;
		l=1;
		while(r<n){
			now+=a[++r];
			if(now<0){
				while(l<=r&&now<0){
					now-=a[l];
					l++;
				}
			}
			if(r-l>ans){
				ans=r-l;
				ansl=l;
				ansr=r;
			}
		}
		if(ans==-1)printf("-1\n");
		else printf("%I64d %I64d\n",ansl,ansr);
	}
	return 0;
}
```


---

## 作者：szkzyc (赞：3)

周三的时候 vp CF1611，这道题有思路但没做出来，课后跟王江睿讨论了一下，发现可以用前缀和，ST表搞搞。

花了一天时间，终于在赛后把这道题写完了。

题意：求最长区间 $[l,r]$ 使得 $s+\sum\nolimits_{i=l}^ra_i$ 的每一个前缀均大于等于 $0$。

这道题首先先否定暴力：因为要在每一时刻都大于等于 $0$，所以光是一个前缀和还没啥用，复杂度 $O(N^3)$，显然超时。（根据数据范围可以发现，就算枚举左右端点后 $O(1)$ 查询，也会超时）

因为根据数据和时限，能接受的最大复杂度在 $O(n\log n)$ 左右，看见带 log，就能立刻想到一种做法：二分答案！

这个数列是可以二分的，因为在前 $n$ 个数可以，那更少的数也照样能可以。但一次二分可远远不行，需要将左端点从 1 到 n 枚举，再二分右端点就可以了。若是将二分答案的 check 降到 $O(1)$，复杂度就可以了。

那如何 $O(1)$ check？

难的不是在 $[l,r]$ 区间求和，区间求和一个基本的前缀和就能实现。而是如何判定每一个前缀都大于等于 $0$。可以发现，当这个区间和的值加上这个区间的最小值也大于等于 $0$ 时，那就肯定大于等于 $0$。否则就存在前缀使得 
$[l,x]\lt s$ $(x∈[l,r])$。

那如何 $O(1)$ 求静态区间最小值？

当然是ST表啊！复杂度 $O(n\log n)$，可以通过此题。

所以，只要需前缀和 + ST表 + 二分答案即可解决此题！

### 接下来上特别好理解的代码:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int st[200005][105];//ST表 
int a[200005];//把数组本身当前缀和数组用 
int ansleft, ansright;
int answer;
int stmin(int left, int right){//利用ST表求任意区间的最小值 
	int X = log(right - left + 1) / log(2);
	return min(st[left][X], st[right - (1 << X) + 1][X]);
}
bool check(int left, int right, int s){//二分答案的check函数 
    return stmin(left, right) + s - a[left - 1] >= 0; //[left,right]min + s - [1,left)sum>=0
	//即：left到right区间的最小值加上s再减去前left-1个数的和大于等于0 
}
signed main(){
    ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--){
		answer = ansleft = ansright = 0;
		int n, s;
		cin >> n >> s;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			a[i] += a[i - 1];//转为前i个数的和，前缀和 
		}
		for(int i = 1; i <= n; i++) st[i][0] = a[i];

		for(int j = 1; j <= (int)(log(n) / log(2)); j++){
			for(int i = 1; i <= n - (1 << j) + 1; i++){
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);//这里是min，最小值 
			}
		}//ST表求静态区间最小值 
		for(int L = 1; L <= n; L++){//二分答案 
			int num = 0;
			int left = L;//枚举左端点 
			int right = n;//先默认右端点为n 
			while(left <= right){
				int mid = (left + right) / 2;//中间值 
				if(check(L, mid, s)){//判断区间 
					num = mid;//记录 
					left = mid + 1;//缩小区间 
				}
				else right = mid - 1;//缩小区间 
			}
			if(num - L + 1 > answer){//当前答案最优 
				answer = num - L + 1;//记录答案 
				ansleft = L;//记录左端点 
				ansright = num;//记录右端点 
			}
		}
		if(answer != 0) cout << ansleft << ' ' << ansright << endl;//有解输出 
		else cout << -1 << endl;//无解-1 
	}
	return 0;
}
```


---

## 作者：Ryder00 (赞：1)

题意清晰，不再阐述。

## 思路
看到区间，条件反射想到二分和数据结构。注意到答案是单调的，可以二分。题目本质上是要我们求一个前缀和数组，在一段区间内的最小值。容易想到线段树维护。

二分复杂度 $O(\log n)$，线段树操作复杂度 $O(n\log n)$，总复杂度 $O(n\log^2 n)$。

本题线段树究极卡常！1996ms 喜提最劣解。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=2e5+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,s,a[N],sum[N],t[N*4],Lans,Rans,tag[N*4];
void build(int id,int l,int r){
    if(l==r){
        t[id]=sum[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    t[id]=min(t[id*2],t[id*2+1]);
}
int query(int id,int l,int r,int L,int R){
    if(L<=l&&R>=r) return t[id];
    int mid=(l+r)>>1,ans=inf;
    if(L<=mid) ans=min(ans,query(id*2,l,mid,L,R));
    if(R>mid) ans=min(ans,query(id*2+1,mid+1,r,L,R));
    return ans;
}
bool check(int x,int y){
    if(query(1,1,n,x,y)+s-sum[x-1]>=0) {
        Lans=x,Rans=y;
        return 1;
    }
    return 0;
}
void solve(){
    cin>>n>>s;
    bool pd=1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pd&=(a[i]<0&&abs(a[i])>s);
        sum[i]=sum[i-1]+a[i];
    }
    if(pd){
        cout<<-1<<endl;
        return ;
    }
    build(1,1,n);
    int mx=0,ansL=0,ansR=0;
    for(int i=1;i<=n;i++){
        int l=1,r=n-i+1,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(i,i+mid-1)) l=mid+1,ans=mid;
            else r=mid-1;
        }
        if(ans>mx) mx=ans,ansL=Lans,ansR=Rans;
    }
    cout<<ansL<<" "<<ansR<<endl;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>T;
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

## 作者：I_am_Accepted (赞：1)

### UPD

发现这道题尺取法能 $O(n)$ 做，是我太蒻了 qwq。

### 题意简述

给一个长度为 $n$ 序列 $\{a\}$ 和一个整数 $s$，求一个最长的子串 $\{b\}$ 使得 $\{b\}$ 的任何前缀和均 $\geqslant -s$。

### 题目分析

由于是关于前缀和的问题，我们求出 $\{a\}$ 的前缀和 $\{c\}$。

枚举子串的左端点 $x$，接下来的问题就是如何 $O(\log n)$ 找到最靠右的右端点 $y$ 使得：
$$\forall z \ | \ x\leqslant z\leqslant y,c_z\geqslant c_{x-1}-s$$

我们想到倍增往右，可用 ST 表维护区间 $\{c\}$ 的最小值。

最后的最后再取长度 $\max$ 输出即可。

### Code

**注：代码变量名与上文推导变量名不同，请仔细辨别。**

```cpp
#define For(i,j,k) for(register int i=j;i<=k;i++)
#define Rof(i,j,k) for(register int i=j;i>=k;i--)
#define fir first
#define sec second
#define mkp make_pair
#define pii pair<int,int>
#define N 200010
#define C 20
#define int long long
int n,m,a[N];
pii ans;
int b[N][C+1];//ST 表
bool flag;
int check(int x){//求长度最大值
	int pos=x,tar=b[x-1][0]-m;
	Rof(i,C,0){
		if(pos-1+(1<<i)<=n && b[pos][i]>=tar){
			pos+=(1<<i);
		}
	}
	return pos-x;
}
void work(){
	cin>>n>>m;
	ans=mkp(0,0);
	For(i,1,n) cin>>a[i];
	flag=1;
	For(i,1,n)
		if(a[i]>=-m)
			flag=0;
	if(flag){//无人生还
		cout<<-1<<endl;
		return ;
	}
	For(i,1,n) b[i][0]=b[i-1][0]+a[i];//前缀和
	For(j,1,C){
		For(i,1,n){
			if(i+(1<<j)>n+1) break;
			b[i][j]=min(b[i][j-1],b[i+(1<<(j-1))][j-1]);
		}
	}
	For(i,1,n)//枚举左端点
		ckmx(ans,mkp(check(i),i));
	cout<<ans.sec<<" "<<ans.sec+ans.fir-1<<endl;
}
```

---

## 作者：EuphoricStar (赞：0)

## 思路

双指针。

从小到大枚举 $l$，对于每个 $l$ 计算出最优的 $r$。这个很容易想到 $O(\log n)$ 的二分，但是存在线性做法。可以维护一个下标 $r$，当 $\sum\limits_{i=l}^{r+1}a_i \geq -s$ 就移动 $r$。这样我们就得到了最优的 $r$。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 200100;

ll n, m, a[maxn];

void solve() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	int l = 0, r = -1;
	ll sum = 0;
	for (int i = 1, j = 0; i <= n; ++i) {
		sum -= a[i - 1];
		if (j < i - 1) {
			j = i - 1;
			sum = 0;
		}
		while (j < n && sum + a[j + 1] >= -m) {
			sum += a[++j];
		}
		if (j - i > r - l) {
			r = j;
			l = i;
		}
	}
	if (r == -1) {
		puts("-1");
	} else {
		printf("%d %d\n", l, r);
	}
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：智子 (赞：0)

## 题意

[题面翻译](https://www.luogu.com.cn/paste/wrrwu53t)

给定一个长度为 $n$ 的序列 $a$ 和一个整数 $s$，求一段最长的区间 $[l,r]$ 使得 $\forall i \in [l,r] , s + \sum\limits_{j = l}^i a_j \geq 0$。

## 思路

对于这种“求最长的符合要求的区间的问题”，由于它满足单调性，所以我们可以用“枚举左端点，二分右端点”的常用套路求解。

我们先求出 $a$ 数组的前缀和 $sum$，那么问题就变成了求一段最长的区间 $[l,r]$ 使得 $s + \min_{j = l}^r sum_j - sum_{i - 1} \geq 0$。中间求区间最小值的部分可以用 ST 表预处理出来，然后 $O(1)$ 查询；而这个式子本身则可以用二分答案求解。

总复杂度 $O(n \ \log\ n)$。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 200000 + 5;
const int MAXB = 21;

long long st[MAXN][MAXB], lg[MAXN];
long long a[MAXN];
int n, s;

void init() {
    for(int i = 1; i <= n; i++) {
		st[i][0] = a[i];
		if(i >= 2) {
			lg[i] = lg[i / 2] + 1;
		}
	}
	for(int j = 1; j < MAXB; j++) {
		for(int i = 1; i + (1 << j) - 1 <= n; i++) {
			st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
}

long long ask(int l, int r) {
	int t = lg[r - l + 1];
	return min(st[l][t], st[r - (1 << t) + 1][t]);
}

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &s);
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            a[i] += a[i - 1];
        }
        init();
        int ansl, ansr, ans = 0;
        for(int i = 1; i <= n; i++) {
            int l = i, r = n, res = 0;
            while(l <= r) {
                int mid = (l + r) / 2;

                if(s + ask(i, mid) >= a[i - 1]) {
                    res = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if(res == 0) {
                continue;
            }
            if(res - i + 1 > ans) {
                ans = res - i + 1;
                ansl = i;
                ansr = res;
            }
        }
        if(ans == 0) {
            printf("%d\n", -1);
        } else {
            printf("%d %d\n", ansl, ansr);
        }
    }

    return 0;
}

```

---

## 作者：Gloaming (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/kevin07/p/15609743.html)

## 题目描述

给你一个长度为 $n(n\leq 2
\times 10^5)$ 的序列 $a$ 和一个整数 $s$，求一段最长的连续子序列 $[l,r]$ 使得 $\forall i\in[l,r],x+\sum\limits_{j=l}^i a_j\geq 0$。

## 分析

我们首先看到题目给定的这一个限制条件，可以用***前缀和***来进行一次转化 $\forall i\in[l,r],x+qzh_i-qzh_{l-1}\geq 0$，再次观察可以发现只要 $[l,r]$ 中最小的 $qzh_i$ 满足这一个条件，整个区间就可以满足了，求区间最小可以用ST表来做，时间复杂度为查询 $O(1)$，预处理 $O(n\log n)$

然后考虑枚举左端点，在应用二分的方法来寻找右端点，判断用ST表优化到 $O(1)$，每一组数据时间复杂度 $O(n\log n)$

代码实现就不是很复杂了（记得开`long long`）

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int T,n,s;
int qzh[N],a[N];
int f[N][32];
int lg[N];
void Pre(){
    // int xx=loog(n);
    lg[1]=0;
    for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
    for(int j=1;j<=lg[n];j++) {
        for(int i=1;i+(1<<j)-1<=n;i++)
            f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
    }
}

int Query(int l,int r){
    int delta=lg[r-l+1];
    return min(f[l][delta],f[r-(1<<delta)+1][delta]);
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--){
        cin>>n>>s;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            qzh[i]=qzh[i-1]+a[i];
            for(int j=1;j<=30;j++) f[i][j]=0x3f3f3f3f;
            f[i][0]=qzh[i];
        }
        Pre();
        int ans=-1,ansv=0,ansl=0,ansr=0;
        for(int l=1;l<=n;l++){
            int rl=l,rr=n,fl=0;
            while(rl<=rr){
                int mid=rl+rr>>1;
                if(s+Query(l,mid)-qzh[l-1]<0) rr=mid-1;
                else rl=mid+1,fl=mid;
                // cout<<rl<<' '<<rr<<endl;
            }
            // if(fl==0) continue;
            if(fl-l+1>ansv){
                ansl=l;ansr=fl;
                ansv=fl-l+1;
            }
        }
        if(ansv) cout<<ansl<<' '<<ansr<<endl;
        else cout<<-1<<endl;
    }
    return 0;
}
```

---

