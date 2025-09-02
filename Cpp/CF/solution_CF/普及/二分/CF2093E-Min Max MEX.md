# Min Max MEX

## 题目描述

给定一个长度为 $n$ 的数组 $a$ 和一个数字 $k$。

子数组被定义为数组中一个或多个连续元素组成的序列。你需要将数组 $a$ 分割成 $k$ 个互不重叠的子数组 $b_1, b_2, \dots, b_k$，使得这些子数组的并集等于整个数组。此外，你需要最大化 $x$ 的值，其中 $x$ 等于所有子数组 $b_i$（$i \in [1..k]$）的 MEX 的最小值。

MEX $(v)$ 表示数组 $v$ 中未出现的最小非负整数。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
1 1
0
5 1
0 1 3 2 4
6 2
2 1 0 0 1 2
5 5
0 0 0 0 0
5 2
2 3 4 5 6
6 2
0 0 1 1 2 2
4 4
1 0 0 0```

### 输出

```
1
5
3
1
0
1
0```

# 题解

## 作者：Takato_ (赞：3)

# [Min Max MEX](https://vjudge.net/contest/708851#problem/E)

#### 算法：二分

#### 思路：

当我们看到要求“最小 $MEX$ 等于 $x$ 的最大可能值”时，二分便是显而易见的了。

边界 $l,r$ 初始分别为 $0,n$。然后跑二分加 $check$。

传一个参数 $x$ 给 $check$，表示当前以 $x$ 为最小 $MEX$ 进行划分。接下来遍历每一个数，如果这个数小于 $x$，那么就可以和前面的数放进一个集合。同时用 $cnt$ 累计集合个数。如果集合个数满足 $k$，那么就是可行方案。

因为 $x$ 是作为 $MEX$，所以从 $0$ 到 $x - 1$ 的所有数都要统计到，用 $set$ 记录每个数的出现。每统计一个集合就需要清空上一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int P = 10000007;
int t, n, k, a[200010];
bool check(int x) {
    set <int> vis;
	int cnt = 0, p = 0;
	for(int i = 1; i <= n; ++ i) {
		if(a[i] < x){
			vis.insert(a[i]);
		}
        if(vis.size() == x) {
			++ cnt;
            vis.clear();
		}
	}
	return cnt >= k;
}
signed main() {
	cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; ++ i) cin >> a[i];
		int l = 0, r = n;
		while(l < r){
			int mid = (l + r + 1) >> 1;
			if(check(mid)) l = mid;
			else r = mid - 1;
		}cout << l << endl;
	}
}
```

---

## 作者：Noah03 (赞：1)

### 题意

---

给你一个长度为 $n$ 的数组 $a$ 和一个数字 $k$。

子数组的定义是数组中一个或多个连续元素的序列。你需要将数组 $a$ 分割成 $k$ 个**不重叠**的子数组 $b_1,b_2,…,b_k$，使得这些子数组的合集等于整个数组。此外，你需要最大化 $x$ 的值，即等于 $i∈[1..k]$ 的最小 $\operatorname{MEX}(b_i)$ 值。

$\operatorname{MEX}(v)$ 表示数组 $v$ 中没有的最小非负整数。

~~题目怎么没有翻译。~~

### 分析

---

首先，题目中有关键词：最小值最大，由此我们可以想到使用**二分答案**的方法来解决。

贴一个二分答案的模板：

```cpp
int l=1,r=inf,ans=-1;
while(l<=r){
    int mid=(l+r)>>1;
    if (check(mid)) l=mid+1,ans=mid;
    else r=mid-1;
}
printf("%d\n",ans);
```

在二分中，最重要的部分就是 check 函数了。

这题的 check 函数怎么写呢？我们可以用一个 set 来存储题目中所说的子数组，这样就很容易写出来了。

check 函数代码：
```cpp
bool check(int x){
	set<int> s; 
	register int cnt=0;
	for(register int i=1;i<=n;++i){
		if (a[i]<x) s.insert(a[i]);
		if (s.size()>=x){
			s.clear();
			cnt++;
		}
		if (cnt>=k) return true;
	}
	return false;
}
```

代码的时间复杂度为 $O(T \times n \times \log^2n)$，不会超时。

### 代码

---

**请勿抄袭。**

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=2e5+10;
int a[MAXN];
int n,k;
bool check(int x){
	set<int> s; 
	register int cnt=0;
	for(register int i=1;i<=n;++i){
		if (a[i]<x) s.insert(a[i]);
		if (s.size()>=x){
			s.clear();
			cnt++;
		}
		if (cnt>=k) return true;
	}
	return false;
}
int main(){
	register int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&k); 
		for(register int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		register int l=0,r=n,ans=-1;
		while(l<=r){
			register int mid=(l+r)>>1;
			if (check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

#### 题外话

---

我比赛时脑抽 check 函数里用了 unordered_map，结果赛后被 Hack 了。

**The End.**

---

## 作者：cwxcplh (赞：1)

**题目大意：** 给定一个长度为 $n$ 的数组，现在要把它切成 $k$ 份，求每一份的 $\operatorname{MEX}$ 的最小值的最大值。

触发关键词：**最小的最大**。

第一眼算法：二分答案。

这个二分答案我就不多说了，我们主要看这个判断函数怎么写。

题目中还有一条信息我们没用：切成 $k$ 份。

正向思路：直接枚举，看看从那切成 $k$ 份满足题意。

这样的话还不如不写二分答案……

逆向思路：按照当前二分出来的 $\operatorname{MEX}$ 来分割，看看是否比 $k$ 份多。

非常好的方案，只需要循环一下然后看看能分割成几份就行了！

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,a[200006];
bool check(int x)
{
    int t=0,num=0;
    vector<int>v(x+6,0);//标记数组
    for(int i=1;i<=n;i++)
    {
        if(!v[a[i]]&&a[i]<=x)
        {
            v[a[i]]=1;
            if(a[i]<x)
            {
                num++;
            }
        }
        if(num>=x)
        {
            t++;
            for(int j=0;j<v.size();j++)
            {
                v[j]=0;
            }
            num=0;
        }
    }
    return t>=k;
}
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        int l=0,r=n,mid=0,ans=0;
        while(l<=r)
        {
            mid=l+r>>1;
            if(check(mid))
            {
                ans=mid;
                l=mid+1;
            }
            else
            {
                r=mid-1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：zyc418 (赞：1)

[题目](https://codeforces.com/problemset/problem/2093/E)
# 思路
对于 $u=\operatorname{MEX}(v)$，如果选择数组 $v$ 的一部分组成新数组 $s$ 那么在所有的 $w<u$ 中，能否都能找到 $w=\operatorname{MEX}(s)$？

这当然是肯定的，不难想到，我们可以考虑**二分**，下限 $l = 0$，上限 $r=n$（因为数组顶多是 $[0,1, \dots, n-1]$）。

但如何写 $\operatorname{check}$ 函数呢？

我们发现对于 $mx=mid$ 我们只需维护一个区间，然后遍历整个数组，对于每个元素，满足 $a_{i} \le u$ 就将它加入集合，当集合元素个数达到了 $mid$，就统计次数加一，并且清空当前集合。这样到最后，只要计数大于等于 $k$，就表示可以合理划分。时间复杂度为 $O(n \log n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 2e18
const ll mod=1e9+7;
namespace io {
	using namespace std;
	inline ll read() {
		char n=getchar();
		ll num=0,flag=1;
		while(n<'0'||n>'9') {
			if(n=='-') {
				flag=-1;
			}
			n=getchar();
		}
		while(n>='0'&&n<='9') {
			num=num*10+n-'0';
			n=getchar();
		}
		return num*flag;
	}
	inline void print(ll x) {
		if(x<0) {
			putchar('-');
			print(-x);
			return;
		}
		if(x==0) {
			return;
		}
		print(x/10);
		putchar((char)(x%10+'0'));
	}
}
using namespace io;
const ll N=2e5+5;
ll T,n,k,a[N];
map<ll,bool> mp;
bool ck(ll x) {
	for(ll i=0;i<=x;i++) {
		mp[i]=0;
	}
	ll cnt=0,pos=0;
	for(ll i=1;i<=n;i++) {
		if(a[i]<x&&!mp[a[i]]) {
			mp[a[i]]=1;
			pos++;
		}
		if(pos>=x) {
			cnt++;
			pos=0;
			for(ll j=0;j<=x;j++) {
				mp[j]=0;
			}
		}
	}
	if(cnt>=k) {
		return true;
	}
	return false;
}
void solve() {  
    n=read();
	k=read();
	for(ll i=1;i<=n;i++) {
		a[i]=read();
	}
	ll l=0,r=n,ans=0;
	while(l<=r) {
		ll mid=(l+r)>>1;
		if(ck(mid)) {
			l=mid+1;
			ans=mid;
		}
		else {
			r=mid-1;
		}
	}
	if(!ans) putchar('0');
	else print(ans);
	cout<<endl;
}
int main() {
	T=read();
	while(T--) {
		solve();
	}
	return 0;
}
```

~~当你把这代码交上去时会得到一个令人开心的 TLE~~

为什么呢?

我们发现，`mp.clear()` 的复杂度是 $O(n)$ 的，这样你的复杂度就来到了 $O(n^2 \log n)$。

但我们只需改成普通数组即可光速通过，以下是正确代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 2e18
const ll mod=1e9+7;
namespace io {
	using namespace std;
	inline ll read() {
		char n=getchar();
		ll num=0,flag=1;
		while(n<'0'||n>'9') {
			if(n=='-') {
				flag=-1;
			}
			n=getchar();
		}
		while(n>='0'&&n<='9') {
			num=num*10+n-'0';
			n=getchar();
		}
		return num*flag;
	}
	inline void print(ll x) {
		if(x<0) {
			putchar('-');
			print(-x);
			return;
		}
		if(x==0) {
			return;
		}
		print(x/10);
		putchar((char)(x%10+'0'));
	}
}
using namespace io;
const ll N=2e5+5;
ll T,n,k,a[N],mp[N];
bool ck(ll x) {
	for(ll i=0;i<=x;i++) {
		mp[i]=0;
	}
	ll cnt=0,pos=0;
	for(ll i=1;i<=n;i++) {
		if(a[i]<x&&!mp[a[i]]) {
			mp[a[i]]=1;
			pos++;
		}
		if(pos>=x) {
			cnt++;
			pos=0;
			for(ll j=0;j<=x;j++) {
				mp[j]=0;
			}
		}
	}
	if(cnt>=k) {
		return true;
	}
	return false;
}
void solve() {  
    n=read();
	k=read();
	for(ll i=1;i<=n;i++) {
		a[i]=read();
	}
	ll l=0,r=n,ans=0;
	while(l<r) {
		ll mid=(l+r+1)>>1;
		if(ck(mid)) {
			l=mid;
			ans=mid;
		}
		else {
			r=mid-1;
		}
	}
	if(!ans) putchar('0');
	else print(ans);
	putchar('\n');
}
int main() {
	T=read();
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Grace2022 (赞：0)

## 题目大意
将长度为 $n$ 的数组 $a$ 分割成 $k$ 个部分，使得各个部分的未出现的最小非负整数（即 $\text{MEX}$）的最小值最大。  
## 方法思路
“最小最大”触发关键词：二分答案。我们需要二分的是这个 $\text{MEX}$，那么就出现了以下框架：
```cpp
while(l <= r){
	mid = (l + r) >> 1;
	if(check(mid)){
		ans = mid;
		l = mid + 1;
	}
	else{
		r = mid - 1;
	}
}
```
重点在 $\text{check}(mid)$ 上。我们需要使分到的答案符合题意——是各个部分的 $\text{MEX}$，按照这个要求来把数组分为 $cnt$ 个部分，最后判断 $cnt$ 和 $k$ 的大小关系即可：若 $cnt \lt k$，那么分割得更多至 $k$ 次一定不符合题意，因为我们的在统计 $cnt$ 时是尽量让它大的；若 $cnt \ge k$，这个 $mid$ 就可行，继续往大里二分。  

我判断 $\text{MEX}$ 的方法是用一个 ```unordered_set``` 统计小于 $mid$ 的 $a_i$ 的个数。这里如果直接统计个数会统计重复（因为 $a_i$ 可能等于 $a_j$），关于只去重不排序且时间复杂度接近 $\mathcal{O}(1)$ 的 STL 容器就是 ```unordered_set```。    

关于时间复杂度：这里二分的 $r$ 取到 $n$ 即可，无需取到值域最大值，因为一定有 $0 \le \text{MEX}(b_i) \le n$，其中 $b_i$ 是分割后的各个子数组，即这 $n$ 个数从 $0$ 开始无重复递增，未出现的数就是 $n$。所以时间复杂度为 $\mathcal{O}(T \times n \log n)$，但是 ```unordered_set``` 的常数较大，且我在清空的时候频繁调用构造和析构函数，如果想要时间复杂度严格 $\mathcal{O}(T \times n \log n)$，可以用 ```bool vis[]``` 或 ```bitset``` 代替 ```unordered_set```。
## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
	char c = getchar();
	int s = 0, st = 1;
	while(c < '0' || c > '9'){
		(c == '-') && (st = -1);
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = getchar();
	}
	return s * st;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9){
		write(x / 10);
	}
	putchar(x % 10 + 48);
}
inline void Endl(){
	putchar('\n');
}
const int N = 2e5;
int n, m, l, r, mid, ans, T, cnt;
int a[N + 5];
inline bool check(){//mid: 最小 mex 
	unordered_set<int> s;
	cnt = 0;
	for(rint i = 1; i <= n; ++i){
		if(a[i] < mid){
			s.insert(a[i]);
		}
		if(s.size() == mid){
			++cnt;
			unordered_set<int> ().swap(s);
		}
	} 
	if(cnt < m){
		return false;
	}
	else{
		return true;
	}
}
inline void run(){
	n = read(), m = read();
	l = 0, r = n, ans = 0;
	for(rint i = 1; i <= n; ++i){
		a[i] = read();
	}
	while(l <= r){
		mid = (l + r) >> 1;
		if(check()){
			ans = mid;
			l = mid + 1;
		}
		else{
			r = mid - 1;
		}
	}
	write(ans);
	Endl();
}
signed main(){
	T = read();
	while(T--) run();
	return 0;
} 
```

---

## 作者：metrixgo_caozhendi (赞：0)

比较标准的二分模板题。题意为给定一个长度为 $n$ 的数组，要求你切成 $k$ 个子数组（顺序不变，没有重叠或空缺），对于每个数组找到 $\operatorname{mex}$，然后取所有 $\operatorname{mex}$ 的最小值，问你这个最小值最大是多少。$\operatorname{mex}$ 定义为集合内没有出现过的最小的**非负整数**。

看起来我们只需要二分这个最大值就行了。每一次二分就进行一次确认，如果二分到的值可行，就左端点右移，否则右端点左移。为了让程序更快，这里可以让初始右端点等于 $\frac{n}{k}$，因为至少要有 $x$ 个元素才能让一个集合的 $\operatorname{mex}$ 等于 $x$。

具体的检查一个值 $x$ 是否可行的方法是从左往右遍历数组，一旦出现了 $0$ 到 $x-1$ 的所有数，那么计数就加一，然后开始新的一轮计数。一旦计数达到 $k$ 就说明可行（剩下没用到的数拼在最后一个子数组就行。额外的元素不会减少该数组的 $\operatorname{mex}$）。如果所有元素都遍历完了，计数还没达到 $k$，就说明不可行。这里我用的是数组来记录一个数是否出现，并且没有使用 $\operatorname{memset}$ 是怕被卡时间。但是事实证明你用了影响也不大，毕竟调用的次数与 $k$ 挂钩，而且 $k$ 越大你要开的数组就越小。

好了，还有不懂的就去看代码吧，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200005];
bool ck(int x){
    if(x==0) return true;
    int cnt=0,gcnt=0,book[x]={0},lv=1;
    for(int i=1;i<=n;i++){
        if(a[i]<x&&book[a[i]]<lv){
            cnt++;
            book[a[i]]++;
        }
        if(cnt==x){
            gcnt++;
            cnt=0;
            lv++;
            if(gcnt==k) return true;
        }
    }
    return false;
}
int binsch(){
    int l=0,r=n/k,mid,ret=0;
    while(l<=r){
        mid=(l+r)/2;
        if(ck(mid)){
            ret=max(ret,mid);
            l=mid+1;
        }
        else r=mid-1;
    }
    return ret;
}
int main()
{
    
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        cout<<binsch()<<endl;
    }
    return 0;
}
```

---

## 作者：lw393 (赞：0)

发现求的是最大最小值。直接考虑二分。

讲一下怎么实现二分吧。我们怎么一边遍历数组，一边求序列 $\operatorname{mex}$ 呢？我们利用桶，在遍历到一个数时，将它放入桶中，然后若桶中存在当前记录到的 $\operatorname{mex}$，就让它 $+1$，知道不能再加为止。

代码实现（不完整，仅为二分中的判断函数）：

```cpp
bool check(int x){
  int cnt = 0, mex = 0;
  unordered_map<int, bool>m;
  for(int i = 1; i <= n; i++){
    if(a[i] <= x) m[a[i]] = 1;
    while(m.count(mex)) mex++;
    if(mex >= x) { cnt++; m.clear(); mex = 0; }
  }
  if(mex >= x) cnt++;
  return cnt >= k;
}
```

---

## 作者：AK_400 (赞：0)

考虑二分答案，我们检查一个答案 $x$ 是否合法时，只需要遍历数组，记录当前段的 mex 值，如果大于 $x$，那么在这个位置分一段，最后判断是否分出 $k$ 段即可。

复杂度：$O(n\log n)$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,c),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int n,k,a[200005];
vector<int>v;
bool vis[200005];
bool chk(int x){
    int cnt=0,mex=0;
    for(int i=0;i<=x;i++)vis[i]=0;
    for(int i=1;i<=n;i++){
        if(a[i]>=x)continue;
        v.push_back(a[i]);
        vis[a[i]]=1;
        while(vis[mex])mex++;
        if(mex>=x){
            cnt++;
            for(int j:v)vis[j]=0;
            v.clear();
            mex=0;
        }
    }
    return cnt>=k;
}
void slv(){
    read2(n,k);
    for(int i=1;i<=n;i++)read(a[i]);
    int l=0,r=n,mid;
    while(l<r){
        mid=l+r+1>>1;
        if(chk(mid))l=mid;
        else r=mid-1;
    }
    cout<<l<<endl;
    return;
}
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

