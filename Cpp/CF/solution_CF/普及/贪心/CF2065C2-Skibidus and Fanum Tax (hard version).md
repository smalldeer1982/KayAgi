# Skibidus and Fanum Tax (hard version)

## 题目描述

这是这道题的困难版本。在该版本中，$m \leq 2\cdot 10^5$。

Skibidus 有两个数组 $a$ 和 $b$，分别包含 $n$ 个和 $m$ 个元素。对于 $1$ 到 $n$ 的每个整数 $i$，他**最多**可以执行一次以下操作：

- 选择一个整数 $j$（$1 \leq j \leq m$），将 $a_i$ 赋值为 $b_j - a_i$。注意，经过此操作后，$a_i$ 可能变为非正数。

Skibidus 需要你的帮助，判断是否可以通过若干次上述操作，使得数组 $a$ 为非递减序列。

$^{\text{∗}}$ 若 $a_1 \leq a_2 \leq \dots \leq a_n$，则数组 $a$ 为非递减序列。

## 说明/提示

- 在第一个测试用例中， $[5]$ 已经是非递减序列。
- 在第二个测试用例中，可以证明无法使其非递减。
- 在第三个测试用例中，我们可以将 $a_2$ 更新为 $b_1 - a_2 = 6 - 4 = 2$，将 $a_3$ 更新为 $b_3 - a_3 = 8 - 6 = 2$。此时数组变为 $[2,2,2,5]$，为非递减序列。
- 在最后一个测试用例中，我们可以对每个位置均执行操作，数组变为 $[-1,0,1]$，是非递减序列。

## 样例 #1

### 输入

```
5
1 3
5
9 1 1000000000
3 2
1 4 3
3 4
4 3
2 4 6 5
6 1 8
5 2
6 4 5 4 5
4 1000
3 1
9 8 7
8```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：Pyrf_uqcat (赞：4)

考虑一个贪心策略。为了成为非递减序列，需要让前面的数尽量小。

所以对于每个数，我们要在**保证非递减的前提**下进行对数的操作，让当前数尽量小。考虑到 $m$ 大于一，每次通过二分选择可以让当前数最小且非递减的 $b$。

赛时已过代码。


```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N=2e5+5;

int n,m,a[N],b[N];

signed main()
{
	int t;cin>>t;
	while(t--)
	{
		memset(b,0,sizeof(b));
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) cin>>b[i];
		bool flag=1;
		a[0]=LONG_LONG_MIN;
		sort(b+1,b+m+1);
		for(int i=1;i<=n;i++)
		{
			int p=upper_bound(b+1,b+m+1,a[i-1]+a[i])-b;
			if(p!=0&&b[p-1]==a[i-1]+a[i]) p--;
			if(b[p]-a[i]>=a[i-1]) a[i]=min(a[i],b[p]-a[i]);
			if(a[i]<a[i-1]) a[i]=max(a[i],b[p]-a[i]);
			if(a[i]<a[i-1]) flag=0;
		}
		cout<<(flag?"YES":"NO")<<endl;
	}
    return 0;
}
```

---

## 作者：thedyingkai (赞：2)

### 思路
先初始化 $now$ 为无穷小，把 $a_i$ 从头开始扫描，如果 $a_n$ 小于 $a_{n-1}$，尝试用 $b_i$ 去减 $a_n$，让 $a_n$ 在不小于 $a_{n-1}$ 的情况下尽可能接近 $a_{n-1}$。

**本质上是为了让 $a_n$ 在允许的范围内最小化，给后面的数据留下尽可能多的操作空间**。

相当于在 $b_i$ 中找一个使得 $a_{n-1}≤b_n-a_n$ 成立的最小的数，这样想到要用二分去求。

先把 $b_i$ 排序，然后用 $\operatorname{lower\_bound()}$ 二分查找，如果能找到符合要求的 $b_n$ 就令 $a_n=b_n-a_n$。

思路就这些，下面是代码。
### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, m;
    cin>>n>>m;
    vector<int> a(n+1), b(m+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];
    sort(b.begin(),b.end());
    long long now=-0x3f3f3f3f3f3f3f3fLL;
    for(int i=1;i<=n;i++){
        long long num=a[i],nxt=0x3f3f3f3f3f3f3f3fLL;
        if(num>=now) nxt=min(nxt,num);
        auto it=lower_bound(b.begin()+1,b.end(),now+num);
        if(it!=b.end()) nxt=min(nxt,*it-num);
        if(nxt==0x3f3f3f3f3f3f3f3fLL){
            cout<<"NO\n";
            return;
        }
        now=nxt;
    }
    cout<<"YES\n";
}
int main() {
    int t;
    cin>>t;
    while(t--) solve();
}
```

---

## 作者：fish_love_cat (赞：1)

赛时 C 写挂调了一个世纪没调出来，导致时间严重不够。

然后赛后 13min 调出来了（

---

题面要求我们通过若干次操作使得序列单调递增，我们只需要在合法的前提下使靠前的元素尽可能小就行了。

如果最后无法合法就是无解。

注意到对于相同的 $a_i$，$b_j$ 越大结果越大。

那么我们就可以将 $b$ 排序后二分修改最优解了。

时间复杂度 $O(n \log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005];
void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    for(int i=1;i<=m;i++)
    cin>>b[i];
    sort(b+1,b+1+m);
    a[1]=min(a[1],b[1]-a[1]);
    //cout<<a[1]<<' ';
    for(int i=2;i<=n;i++)//,cout<<a[i-1]<<' ')
    {
        int l=1,r=m+1;
        while(l<r){
            int mid=(l+r)/2;
            if(b[mid]-a[i]<a[i-1])l=mid+1;
            else r=mid;
        }
        //cout<<r<<'!';
        if(r!=m+1&&(b[r]-a[i]<=a[i]||a[i]<a[i-1]))
        a[i]=b[r]-a[i];
    }
    for(int i=1;i<n;i++)
    if(a[i]>a[i+1]){
        puts("NO");
        return;
    }
//    for(int i=1;i<=n;i++)
//    cout<<a[i]<<' '; 
    puts("YES");
    return;
}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

糖题写挂，人比题糖。

---

## 作者：Cells (赞：1)

考场上太唐，C1 都没切出来，结果第二天就知道错哪里了，然后 C2 就秒了。

首先一眼贪心，对于每个 $1 \le i \le n$，我们都希望：在 $a_{i - 1} \le a_i$ 的时候，$a_i$ 尽可能的小，以便给后续的数字腾出空间。但是我写的时候偏偏漏掉了 $a_{i - 1} \le a_i$ 这个重要条件，~~在此进食后人~~。

- 当 $a_{i - 1} \le a_i$，我们寻找最小的 $b_j$ 使得 $a_{i - 1} \le b_j - a_i$，移项 $a_{i - 1} + a_i \le b_j$，取 $\min(a_i, b_j)$，此处可以用二分。
- 当 $a_{i - 1} > a_i$，同理，寻找最小的 $b_j$ 使得 $a_{i - 1} + a_i \le b_j$，这里不需要取 $\min$，因为必须这样做，当然如果找不到，就说明不可能。

时间复杂度 $O(n \log(n))$。

```c++
//# pragma GCC optimize("Ofast")
# include <bits/stdc++.h>
# define int long long
# define fr front
# define il inline
# define fir first
# define sec second
# define vec vector
# define it iterator
# define pb push_back
# define lb lower_bound
# define ub upper_bound
# define all(x) x.begin(), x.end()
# define mem(a, b) memset(a, b, sizeof(a))

# define lc (t[p].l)
# define rc (t[p].r)
# define ls(x) (x << 1)
# define rs(x) (x << 1 | 1)
# define lson ls(p), l, mid
# define rson rs(p), mid + 1, r

# define sqr(x) ((x) * (x))
# define bpc __builtin_popcount
# define lowbit(x) ((x) & (-(x)))
# define geti(x, i) (((x) >> (i)) & 1)
# define set1(x, i) ((x) | (1 << (i)))
# define set0(x, i) ((x) & (~(1 << (i))))

# define debug1(x) cerr << #x << " = " << x << " "
# define debug2(x) cerr << #x << " = " << x << "\n"
# define bug cerr << "--------------------------\n"

# define each1(i, x) for(auto (i) : (x))
# define each2(i, x) for(auto (&i) : (x))
# define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
# define pre(i, a, b) for(int i = (a); i >= (b); -- i)
# define G(i, h, u, ne) for(int i = h[(u)]; i; i = ne[i])
# define reps(i, a, b, c) for(int i = (a); i <= (b); i += (c))
# define pres(i, a, b, c) for(int i = (a); i >= (b); i -= (c))
using namespace std;

using DB = double;
using LL = long long;
using LDB = long double;
using PII = pair<int, int>;
using ULL = unsigned long long;

const int N = 2e5 + 10;
const int INF1 = 0x3f3f3f3f, INF2 = INT_MAX;
const LL INF3 = (LL)1e18, INF4 = 0x3f3f3f3f3f3f3f3f, INF5 = LLONG_MAX;

int T, n, m;
int a[N], b[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> T;
	while(T --){
		cin >> n >> m;
		
		rep(i, 1, n) cin >> a[i];
		rep(i, 1, m) cin >> b[i];
		
		sort(b + 1, b + 1 + m);
		
		a[1] = min(a[1], b[1] - a[1]);
		
		m ++;
		b[m] = INF4;
		
		rep(i, 2, n){
			if(a[i - 1] <= a[i]){
				int j = lb(b + 1, b + 1 + m, a[i - 1] + a[i]) - b;
				if(b[j] - a[i] - a[i - 1] < a[i] - a[i - 1]) a[i] = b[j] - a[i];//这里在比较大小，实际上是比较差值 
			}
			
			else{
				int j = lb(b + 1, b + 1 + m - 1, a[i - 1] + a[i]) - b;
				if(j == m) continue;//找不到 
				a[i] = b[j] - a[i];
			}
		}
		
		bool ok = true;
		rep(i, 2, n){
			if(a[i - 1] > a[i]){
				ok = false;
				break;
			}
		}
		
		if(ok) cout << "YES\n";
		else cout << "NO\n";
	}
	
	return 0;
}
```

最后：不愿放下哦Baby，是我太傻——陶喆《流沙》

---

## 作者：Lfz312g (赞：0)

# 题解：CF2065C2 Skibidus and Fanum Tax (hard version)
## 题目分析
切掉 C1 后，这题一眼秒了。  
显然有贪心策略，对于一个数进行的操作，进行分类讨论，如果 $a_i < a_{i-1}$，则必须进行操作，此时为了给后面的数更大的操作空间，$a_i$ 要尽量取小值，将 $b$ 数组排序后，找到第一个 $j$ 使得 $b_j \ge a_i + a_{i-1}$，此时 $b_j - a_i$ 最小。这个可以用二分优化。  
如果 $a_i \ge a_{i-1}$ 则需要与原 $a_i$ 取最小值。  
时间复杂度：$O(n \log n)$。
## 代码实现

```cpp
#include <bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
const int Maxn=2e5+27;
int a[Maxn],b[Maxn];
void solve()
{
	int n,m;
	cin>>n>>m;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,m) cin>>b[i];
	sort(b+1,b+1+m);
	a[0]=INT_MIN;
	ffor(i,1,n) {
		int j,l=1,r=m,mid;
		while (l<=r) {
			if (b[mid=l+r>>1]>=a[i-1]+a[i]) j=mid,r=mid-1;
			else l=mid+1;
		}
		if (a[i]>=a[i-1]) {
			if (b[j]-a[i]<=a[i]&&b[j]-a[i]>=a[i-1]) a[i]=b[j]-a[i];
		}
		else a[i]=b[j]-a[i];
	}
	ffor(i,1,n) {
		if (a[i]<a[i-1]) {
			cout<<"NO\n";
			return;
		}
	}
	cout<<"YES\n";
}
int main()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	int T;
	cin>>T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV1eiNhe7EZ9?t=130)

---

## 作者：CaoSheng_zzz (赞：0)

### 题面

给定两个数组 $a, b$ 每次你可以选择一个你没有选择过的 $i$ 和一个任意的 $j$ 将 $a_i$ 赋值为 $b_j - a_i$，现在题目询问在若干次操作之后能否将 $a$ 数组变为不下降序列。

### 思路

不难发现 $$a_i = \min\left\{ \begin{aligned} a_i (a_i \geq a_{i - 1}) \\ b_j - a_i(b_j-a_i \geq a_{i - 1}) \end{aligned} \right.$$ 通过下面那个公式的条件不难推出 $b_j \geq a_i + a_{i - 1}$，所以我们通过第二个公式找到最小的 $b_j - a_i$ 只需要排序 $b$ 数组并使用 `lower_bound` 函数找到第一个 $\geq a_i + a_{i - 1}$ 的 $b_j$ 即可。

当上述公式没有一个满足条件时就无法将 $a$ 变成不下降序列。

时间复杂度为 $\Omicron(T n \log n)$ 可以完美通过此题。

---

## 作者：Wind_love (赞：0)

## 思路
对于该题，我们很容易想到一个贪心思路。  
即对于每一个 $a_i$，在保证其大于等于 $a_{i-1}$ 的同时尽量最小化其值。   
则对于每一个 $a_i$，我们有两种可能的情况。第一种，保持其值不变；第二种，通过题中所说操作改变其值。    
我们重点看到第二种情况，我们可以通过二分查找的方式，让 $b_j-a_i$ 在大于等于 $a_{i-1}$ 的情况下最小。   
最后，对于两种情况，若都能满足大于等于 $a_{i-1}$，则取最小值；否则取能满足的值。   
得到结果后遍历数组判定是否非严格递增即可。  
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n,m,a[200005],b[200005];
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=m;i++)cin>>b[i];
		sort(b+1,b+m+1);
		int f=1;
		a[0]=-1e18;
		for(int i=1;i<=n;i++){
			int temp=lower_bound(b+1,b+m+1,a[i]+a[i-1])-b;
			if(temp<=m){
				if(a[i]>=a[i-1])a[i]=min(a[i],b[temp]-a[i]);
				else a[i]=b[temp]-a[i];
			}
		}
		for(int i=1;i<n;i++){
			if(a[i]>a[i+1]||a[i-1]>a[i]){
				f=0;
				break;
			}
		}
		if(f)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

---

## 作者：The_foolishest_OIer (赞：0)

这道题的 E.v 是来搞笑的？

显然，我们让一个数组单调不降，就尽可能地让前面的数小。

设当前的数是 $a_i$。

如果 $a_{i - 1} > a_i$，二分查找 $b_i$，若不存在 $b_i$ 使得条件成立，输出 `NO`，否则使 $a_i$ 尽可能小。

否则使 $a_i = \min(a_i,\min_{j = 1}^m (b_j - a_i))$。

时间复杂度：$O(n \log m)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 10;
const int inf = 1e16;
const int mod = 1e9 + 7;
int T,n,m;
int a[N],b[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> n >> m;
	for (int i = 1 ; i <= n ; i++) cin >> a[i];
	for (int i = 1 ; i <= m ; i++) cin >> b[i];
	sort (b + 1,b + m + 1);
	a[0] = -inf;
	for (int i = 1 ; i <= n ; i++){
		int L = 1,R = m,id = -1;
		while (L <= R){
			int mid = (L + R) >> 1;
			if (b[mid] - a[i] >= a[i - 1]){
				R = mid - 1;
				id = mid;
			}else{
				L = mid + 1;
			}
		}
		if (a[i - 1] > a[i] && id == -1){
			cout << "NO\n";
			return;
		}
		if (id != -1){
			if (a[i - 1] > a[i]) a[i] = b[id] - a[i];
			else a[i] = min(a[i],b[id] - a[i]);
		}
	}
	cout << "YES\n";
}
signed main(){
	close();
	T = 1;
	cin >> T;
	while (T--) solve();
	return 0;
}












```

---

## 作者：EternalLabyrinth (赞：0)

### 题意：
$T$ 组数据，给定序列 $a$，给定序列 $b$。对于 $a$ 序列的每个 $a_i$，都可以至多选择一个 $j$，让 $a_i$ 变为 $b_j-a_i$。

请问经过操作后是否能让序列单调不降。

### 解法：

先把 $b$ 序列从小到大排序。

首先对于第一个位置的处理：肯定是让 $a_i$ 变为 $\min\{a_i,b_1-a_i\}$。其次我们注意到往前的位置应该在满足条件的情况下尽可能小。这一点可以类比最长不下降子序列。

于是对于每个位置 $i(i\geq 2)$。应二分找到最小的 $j$ 使得 $b_j-a_i\geq a_{i-1}$，当然如果 $a_i$ 本身大于等于 $a_{i-1}$ 的话，它是最优的也是有可能的，需要特判。

无解情况就是找不到这个 $j$ 且 $a_i$ 本身又小于 $a_{i-1}$ 了。注意如果找到了别忘了每次把 $a_i$ 赋为 $\min\{a_i,b_j-a_i\}$。然后我们就做完了。

---

## 作者：Lele_Programmer (赞：0)

# CF2065C2 题解

## 思路

困难版，$b$ 数组有多个值。

对于一个 $a_i$，设 $k$ 为 $b$ 中的元素，则取值分别为 $k-a_i$ 或 $a_i$。

为了使序列单调不降，那么让所填的数在合法的情况下尽可能小，这里 $k-a_i$ 的值不是固定的，所以无法判断 $k-a_i$ 和 $a_i$ 的大小。

设 $res$ 为 $a_i$ 将要填的数，初始为 $+ \inf$，如果 $a_i \ge a_{i-1}$ 那么 $res \leftarrow a_i$。

接下来还要考虑 $k-a_i$ 的情况。将 $b$ 数组递增排序，显然，如果存在一个 $k \in b$ 可以使得 $k-a_i \ge a_{i-1}$，那么在 $k$ 后面的数都可以取，这一步可以用二分来求，找到最小的 $k$，那么 $k-a_i$ 自然就是最小的了，于是 $res \leftarrow \min(res,k-a_i)$，最后 $a_i \leftarrow res$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define _dinic(i,u) for (int i=cur[u];~i && k<limit;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string& x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string& x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string& x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

const int N=200005;
const int inf=2e9;

int T,n,m;
int a[N],b[N];

int main() {
    read(T);
    while (T--) {
        read(n),read(m);
        _rep(i,1,n) read(a[i]);
        _rep(i,1,m) read(b[i]);
        sort(b+1,b+1+m);
        bool ok=true;
        int las=-inf;
        _rep(i,1,n) {
            int pos=lower_bound(b+1,b+1+m,las+a[i])-(b+1)+1;
            int res=inf;
            if (a[i]>=las) res=min(res,a[i]);
            if (pos<=m) res=min(res,b[pos]-a[i]);
            if (res==inf) {
                ok=false;
                break;
            }
            las=res;
        }
        if (!ok) puts("NO");
        else puts("YES");
    }
    return 0;
}
```

---

## 作者：jzjr (赞：0)

## 前置知识

* 贪心
* 二分

## 题意

现在给你长度为 $n$ 的数组 $A$ 和长度为 $m$ 的数组 $B$。

你对于每一个 $1\leq i\leq n$，最多一次可以选择将 $A_i$ 变为 $B_j-A_i$。

问是否存在一种操作方法满足 $A$ 是一个单调不下降序列。

## 思路

考虑贪心。

把 $A_1$ 先变为最小。

然后对于 $2\leq i\leq n$，利用二分求出大于等于 $A_{i-1}$ 的最小 $A_i$。

如果存在 $A_{i-1}>A_i$ 输出 ```No```。

否则为 ```Yes```。

## 实现

按思路模拟即可，二分采用 ```lower_bound```。

### AC code:

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,a[N],b[N];
inline void solve(){
	int dmax=-1000000000;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i],dmax=max(dmax,b[i]);
	sort(b+1,b+m+1);
//	cout<<dmax<<'\n';
	int x=a[1];
	for(int i=1;i<=m;i++)a[1]=min(a[1],b[i]-x);
//	cout<<a[1]<<'\n';
	for(int i=2;i<=n;i++){
		x=a[i]+a[i-1];
	//	cout<<x<<'\n';
		int cnt=lower_bound(b+1,b+m+1,x)-b;
		int y=b[cnt];
	//	cout<<y<<'\n';
		if(a[i-1]>a[i]&&cnt<=m)a[i]=y-a[i];
		else if(cnt<=m)a[i]=min(a[i],y-a[i]);
	//	cout<<a[i]<<'\n';
		if(a[i]<a[i-1]){
			cout<<"No\n";
			return ;
		}
	}
	cout<<"Yes\n";
}
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
/*
1
4 1
1 4 2 5
6

*/
```

---

## 作者：nightwatch.ryan (赞：0)

### Analysis
将 $b$ 数组排序。二分找出 $b$ 数组中第一个大于等于 $a_i + a_{i - 1}$ 的位置 $j$。如果 $a_{i - 1} < a_i$，且 $a_{i - 1} \leq b_j - a_i < a_i$，那么 $a_i \gets b_j - a_i$。否则，$a_i \gets b_j - a_i$。

最后遍历一遍 $a$ 数组，如果其不是升序的，那么输出 `NO`，否则输出 `YES`。
### Code
```cpp
#include <bits/stdc++.h>
const int N = 2e5 + 5;
int a[N], b[N], n, m;
int main() {
    int T; std::cin >> T;
    while (T --) {
        std::cin >> n >> m;
        for (int i = 1; i <= n; i ++) std::cin >> a[i];
        for (int i = 1; i <= m; i ++) std::cin >> b[i];
        std::sort(b + 1, b + m + 1); bool f = 0;
        a[1] = std::min(a[1], b[1] - a[1]);
        for (int i = 2; i <= n; i ++) {
            int l = 1, r = m, j = 0;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(b[mid] - a[i] >= a[i - 1]){
                    j = mid;
                    r = mid - 1;
                }else{
                    l = mid + 1;
                }
            }
            if(a[i - 1] <= a[i]){
                if(a[i - 1] <= b[j] - a[i] && b[j] - a[i] < a[i]){
                    a[i] = b[j] - a[i];
                }
            }else{
                a[i] = b[j] - a[i];
            }
        }
        for(int i = 1; i < n; i ++){
            if(a[i] > a[i + 1]){
                std::cout << "NO" << std::endl; f = 1;
                break;
            }
        }
        if(!f) std::cout << "YES" << std::endl;
    }
}
```

---

## 作者：StormWhip (赞：0)

### 思路
考虑贪心：对于数组中每一个元素 $a_i$，要在保证其不小于 $a_{i-1}$ 的前提下最小化其的值。即在 $b$ 数组中找到一个最小的数 $p$，使得 $p-a_i\ge a_{i-1}$，得 $p\ge a_i+a_{i-1}$，将 $b$ 数组排序后二分查找即可。如果找不到且 $a_i<a_{i-1}$ 则说明无法使其按非递减顺序排序。注意需要特判 $a_1$。  

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,Inf=-1e12;
int T,n,m,a[N],b[N];
signed main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		bool f=1;
		cin>>n>>m;
		a[0]=Inf;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) cin>>b[i];
		sort(b+1,b+m+1);
		for(int i=1;i<=n;i++)
		{
			if(i==1) {a[i]=min(a[i],b[1]-a[i]);continue;}
			int t=a[i]+a[i-1],d=lower_bound(b+1,b+m+1,t)-b;
			if(d>=m+1)
			{
				if(a[i]>=a[i-1]) continue;
				else {cout<<"NO\n";f=0;break;}
			}				
			int p=b[d]-a[i];
			if(p>=a[i-1]&&a[i]>=a[i-1]) a[i]=min(a[i],p);
			if(p>=a[i-1]&&a[i]<a[i-1]) a[i]=p;
			if(p<a[i-1]&&a[i]>=a[i-1]) continue;
			if(p<a[i-1]&&a[i]<a[i-1]) {cout<<"NO\n";f=0;break;}
		}
		if(f) cout<<"YES\n";
	}
	return 0;
}
```

---

