# [YDOI R1] whk

## 题目背景

小 Z 要卷 whk。

## 题目描述

小 Z 一共要卷 $n$ 门科目，第 $i$ 门科目他有且只有 $a_i$ 道题。有无数天时间，每天小 Z 可以做无数道题。

如果小 Z 认为一天是有趣的，仅当他在这一天**至少**做了 $t$ 门科目的题。

小 Z 想知道最多有多少天是有趣的。

## 说明/提示

Subtask 0 为 hack 数据，不计分。

 **本题采用捆绑测试**。
| 子任务编号 | $n\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: | 
| $1$ | $1000$ | $1000$ | 无 | $20$ | 
| $2$ | $5\times10^5$ | $10^5$ | $t=1$ | $10$ |  
| $3$ | $5\times10^5$ | $1$ | 所有 $a_i$ 值都为 $1$ | $10$ |  
| $4$ | $5\times10^5$ | $10^6$ | 无 | $60$ |   



对于所有数据，$1\le t\le n\le5\times10^5$，$1\le a_i \le 10^6$。


## 样例 #1

### 输入

```
5 3 
3 2 5 1 1 ```

### 输出

```
3 ```

## 样例 #2

### 输入

```
6 4 
1 1 4 5 1 4 ```

### 输出

```
3 ```

# 题解

## 作者：T_TLucas_Yin (赞：17)

首先要明白，要使得有趣的天数更多，就要懂得“节约”。一天要刷 $t$ 个科目，那我们每天就任选 $t$ 个科目，每科只刷一道题。这样可以给每个科目节约更多的题，留用于让后面更多天变得有趣。我们遵循的原则是，任一天只要变得有趣了，我们就停止刷题。也就是说，每天刷 $t$ 个科目，每个科目一道题，坚决不多刷。

又很容易发现，如果 $n$ 天是有趣的，那么肯定有 $(n-1)$ 天是有趣的（这还用证明嘛？有趣的那 $n$ 天里前 $(n-1)$ 天一定是有趣的吧？）。这就启发我们用二分答案的思想。查找最多的有趣天数 $k$。

如何判定一个 $k$ 是否满足条件呢？我们已经知道了让有趣天数尽可能多的刷题策略。在这种策略下，由于每天每科目只刷一道题，所以一个科目 $k$ 天内至多刷 $k$ 道题。不足的自然能有几道刷几道，超过的最多就能刷 $k$ 道。又根据策略，$k$ 天刷且仅刷 $kt$ 道题。我们算一下每个科目 $k$ 天的过题数之和是否超过了下限即可。

别忘了每一天都不有趣的情况。 

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[1000005],sum;
bool check(long long k){
    long long cnt=0;
    for(int i=1;i<=n;i++){
        if(a[i]>=k) cnt+=k;
        else cnt+=a[i];
    }
    return cnt>=k*m;//判断有没有超过（够不够刷）
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){ cin>>a[i];sum+=a[i]; }
    long long l=0,r=sum,mid,k=0;//!下限天数为0!
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid)) l=mid+1,k=mid;
        else r=mid-1;
    }
    cout<<k;
    return 0;
}
```

---

## 作者：woshishabi11451444 (赞：5)

令 $f(i)$ 表示有趣天数为 $i$ 时的合法性，合法用 $1$ 表示，不合法用 $0$ 表示。

那么可以发现若 $f(i + 1) = 1$，则 $f(i) = 1$（ $f(i)$ 具有单调性 ）。

所以我们可以二分最后一次合法的 $i$，也就是答案。

那么我们现在考虑 $f(i)$ 如何实现。

假设我们现在二分的值为 $x$。

首先，一天至少会写 $t$ 种不同的科目。

所以这 $x$ 天总共会至少写 $x \times t$ 个科目的题目。

那么对于一种科目他最多写 $x$ 天。（每天都写这个科目）

所以一种科目的题目他最多写 $\min \{ a_i, x \}$。

那么这 $N$ 种科目最多可以写 $\sum \limits_{i=1} ^{i=n} \min \{a_i, x \}$。

而这 $N$ 种科目最少得写 $x \times t$ 种题目。

所以只需判断 $\sum \limits_{i=1} ^{i=n} \min \{a_i, x \}$ 是否大于等于 $x \times t$，是就是合法，不是就是非法。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;
const long long INF = 5e11;

int n, t;
long long l, r = INF, a[N];

bool Check(long long x){
	long long sum = 0;
	for(int i = 1; i <= n; i++){
		sum += min(a[i], x);
	}
	return sum >= x * t;
}

int main(){
	cin >> n >> t;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	while(l < r){
		long long mid = (l + r + 1) >> 1;
		Check(mid) ? l = mid : r = mid - 1;
	}
	cout << l;
	return 0;
}
```

---

## 作者：水星湖 (赞：4)

这里是官方题解。

### 子任务一

考虑怎样可以使有趣的天数最多。

显然，贪心策略为每天都选取当前剩余时间最多的 $t$ 门科目**分别只做一道题**，直到只有小于 $t$ 门科目未完成。

设有趣的天数最多为 $k$，$kt$ 的最大值 $10^6$。

取剩余时间最多的可以使用优先队列，复杂度是 $O(kt \log n)$ 。

### 子任务二
因为 $t=1$，所以每天只做 $1$ 门科目的一道题这天就是有趣的。

故答案为 $\sum a_i$。

记得开 `long long`。

### 子任务三
每一门科目只有 $1$ 道题，所以一门科目最多只能做 $1$ 天，且 $\sum a_i=n$。而一天要做 $t$ 门科目才是有趣的，所以答案就是 $\lfloor\frac{n}{t}\rfloor$。因为子任务二满足 $t=1$，所以可以输出 $\lfloor\frac{\sum a_i}{t}\rfloor$，能得到 $20$ 分。

### 子任务四

以下思路来自 [hdkk](https://www.luogu.com.cn/user/728778)。

很明显答案具有单调性，如果可以有 $x$ 天有趣，则小于 $x$ 天也可以，因此就可以二分答案。

重点在于 check 函数怎么写。

首先，若有 $x$ 天有趣，那就总共至少做了 $x\times t$ 道题。对于一个 $a_i$，如果 $a_i>x$，那么最多造成 $x$ 的贡献，因为这种科目最多做 $x$ 道题，后面的都不计入种类数了。反之，如果 $a_i\le x$，那很明显能都做完并产生贡献。这样 check 函数的复杂度是 $O(n)$ 的。

#### code (by [hdkk](https://www.luogu.com.cn/user/728778))
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500005];
int n,t;
bool check(int x)
{
	int sum=x*t;
	int xb=1;
	while(xb<=n&&sum>0)
	{
		sum-=min(a[xb],x);
		xb++;
	}
	if(sum>0)
		return 0;
	return 1;
}
signed main()
{
	
	cin>>n>>t;
	int l=1;
   	int r=5e11+1;
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	while(l+1<r)
	{
		int mid=(r-l)/2+l;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	
	cout<<l;
}
	
```
时间复杂度 $O(n \log k)$，$k$ 的最大值为 $5\times10^{11}$，可以通过。

我还有一种与二分不同的 $O(n \log n)$ 的做法，因为蒟蒻语文不好，并且这种做法本身也不是很好理解，就只贴代码了，可以自行研究。
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll ans = 0,sum = 0;
const int N = 500005;
ll s[N],a[N];
signed main()
{
    int n,t;
    cin>>n>>t;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1,[](int x,int y){return x>y;});
    
    for(int i=1;i<=n;i++)
    	s[i] = s[i-1] + a[i];
    
    sum = s[n] - s[t];

    for(int i=1;i<=t;i++)//这部分可以二分，不过没必要
    {
        ll x = a[i]*(t-i)-s[t]+s[i];
        if(x <= sum)
        {
            if(i == 1)
                ans = s[n]/t;
            else
                ans = a[i]+(sum-x)/(t-i+1);
            break;
        }
    }
    cout<<ans;
    return 0;
}
    
```

此外，第一种做法可以预处理，第二种做法可以桶排序，都能达到 $O(n+V)$ 的时间复杂度，其中 $V$ 为 $a_i$ 的值域。


---

## 作者：elbissoPtImaerD (赞：2)

没看懂官方题解。

记原题中的 $t$ 为 $m$，原题中的答案为 $t$。

枚举 $t$，不难发现 $\sum \min(t,a_i) \ge mt$ 和 $t$ 可行是等价的。

证明详见这个：[Sir, this way.](https://www.luogu.com.cn/problem/P3586)

但是由于 $t$ 很大，我们不能直接枚举它。

观察得知当 $t \le 10^6$ 时 $\min(t,a_i)$ 才起作用，所以对 $t>10^6$ 特判一下即可。

```cpp
il void Solve()
{
  int n,m;rd(n),rd(m);
  const int V=1e6+7;
  ve<int>a(V);
  LL s=0;
  for(int i=0,x;i<n;++i) rd(x),++a[x],s+=x;
  if(s>=1ll*m*V) return wrt(s/m);
  for(LL t=V-1,suf=0;~t;--t) {
    if(s>=1ll*m*t) return wrt(t);
    suf+=a[t],s-=suf;
  }
  return;
}
```

---

## 作者：hjqhs (赞：2)

答案单调，所以二分天数。  
考虑贪心 check，如果有 $k$ 天有趣，那么题目数量 $\ge k$ 的科目最多只能做 $k$ 道题（因为总共只有 $k$ 天），而题目数量 $< k$ 的科目则得全部做完。如果这些题目数量 $\ge k \times t$，函数返回 $1$，否则返回 $0$。  
可以通过。  
```cpp
// Problem: P10184 [YDOI R1] whk
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10184
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Created Time: 2024-02-25 08:58:05
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
typedef long long ll;
typedef unsigned long long ull;
const int N = 500005;
const int INF = 0x3f3f3f3f;
int n, t, a[N];
bool check(int k) {
	int cnt = 0;
	rep(i, 1, n) cnt += min(a[i], k);
	return cnt >= k * t;
}
void solve() {
	cin >> n >> t; rep(i, 1, n) cin >> a[i];
	int l = 1, r = 5e11 + 5;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid - 1;
	}
	cout << l - 1;
	return;
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1;
	// cin >> T;
	while(T --) solve();
	return 0;
}
```

---

## 作者：Walrus (赞：1)

## 题意

一共 $n$ 门课，每门课有 $a_i$ 道题，若一天至少做了 $t$ 门课的题，则这一天是“有趣的”。求最多有多少天是“有趣的”。其实这里的“至少“是废话，我肯定每天只做 $t$ 门最优。

## 做法

因为若有 $k$ 天是“有趣的”，所以一定有 $k-1$ 天是有趣的，故答案有单调性，考虑二分答案。

### Sub 1

我曾经（并不是赛时）考虑过优先队列的做法，是在二分 check 里套，不过我当时没实现，所以这里口胡一下。

每次肯定选优先队列里最大的 $t$ 个数，将其分别减去 $1$ 又放回去，这是显而易见的。

时间复杂度 $O(wt \log n)$。这里的 $w$ 应该挺大的，所以 $n$ 最大只能有 $1000$。

### Sub 2

每天就做一门课的题，答案显然为 $\sum \limits_{i=1} \limits^{n} a_i$。

时间复杂度 $O(n)$。

### Sub 3

所有 $a_i$ 都为 $1$，通过 Sub 1 可以发现，当我选了第 $i$ 门课后 $a_i$ 就没了，可以跳过其中的”重新放回“操作。所以答案为 $\lfloor \dfrac{n}{t} \rfloor$。

时间复杂度 $O(n)$。

### Sub 4

考虑正解了，二分方法挺多的，这里我二分**若”有趣的“天数为 $k$，则每天至多可做多少道题**。若每天可做的题数大于题目要求 $t$，则此答案可作为备选答案。

时间复杂度 $O(n \log n)$。



```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

int a[N], n, k, l, r, ans;

bool check(int x) {
	int res = 0, cnt = 0;
	for(int i = 1; i <= n; ++i) {
		if(a[i] >= x)
			++cnt;
		else
			res += a[i];
	}
	cnt += res / x;
	return cnt >= k;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n >> k;
	for(int i = 1; i <= n; ++i)
		cin >> a[i], r += a[i];

	l = 0, r = 1e12;

	while(l + 1 < r) {
		int mid = l + r >> 1;
		if(check(mid))
			l = mid;
		else
			r = mid;
	}
	cout << l;
	return 0;
}
```

2024-7-11 update：删废话。

---

## 作者：_Jocularly_ (赞：0)

## 过程
首先考虑使用的算法，可以发现如果当前这一天是有趣的，那么前一天也必是有趣的，发现答案具有单调性，可以使用二分答案求解最大值。

我们知道，如果要让天数尽可能的多，那么每一天每一科刷的题目就要尽可能的少，那么我们一科刷一道题显然是最优的。

实现检查函数，我们采用上面说的，在 $n$ 天内，每一个学科，只要题目数不小于 $n$ 那么我们就刷 $n$ 道题；否则，把能刷的都刷了就行。

形式化的说，第 $i$ 个科目有 $t_{i}$ 道题，那么刷的题的个数就为 $t_{i}$ 和 $k$ 的最小值。

**注意：** 最少的天数为零，所以要把答案初始化为零。

## 代码： 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[1000005];
int cnt;
int ans;
bool check(int k){
    int cnt = 0;
    for(int i=1;i<=n;i++){
    	cnt += min(a[i],k);
    }
    if(cnt >= k * m) return 1;
    return 0;
}
signed main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){  
		cin >> a[i];
		cnt += a[i];
	}
    int l = 0,r = cnt;
    while(l <= r){
        int mid = (l + r) / 2;
        if(check(mid)){
        	l = mid+1;
        	ans = mid;
		}
        else r = mid-1;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：him的自我修养 (赞：0)

# solution
根据数据范围，考虑二分答案。假设有 $x$ 天有趣，那么会做 $t \times x$ 道题目，对于每个 $a_i$，如果 $x\le a_i$，那么 $a_i$ 的贡献是 $x$，否则，贡献是 $a_i$。所以总共产生的贡献就是 $\sum_{i=1}^{n} \min(x,a_i)$，如果大于 $t \times x$，返回真，否则返回假。因为每个数只会产生一次贡献，所以 check 函数的时间复杂度是 $O(n)$ 的，总的时间复杂度是 $O(n \log_{2} n)$，可以通过。

# code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+10;
int n,t,a[N];
bool check(int x){
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=min(a[i],x);
	return cnt>=t*x;
}
signed main(){
	cin >>n>>t;
	for(int i=1;i<=n;i++) cin >>a[i];
	int l=1,r=1e12,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout <<ans;
	return 0;
}  
```

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10184)

## 分析

发现如果有 $x$ 天被定义为有趣，则必然有 $x-1$ 天被定义为有趣，答案具有单调性，考虑二分。

如果有 $x$ 天被定义为有趣，那么至少做了 $x\times t$ 道题，每门科目的贡献为 $\min(a[i],x)$，如果题目有剩余则 $x$ 为有效答案。

时间复杂度 $O(n\log m)$，$m$ 的最大值为 $5\times 10^5\times 10^6=5\times 10^{11}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,t,a[500005];
bool check(int x){
	int now=x*t;
	for(int i=1;i<=n;i++)now-=min(a[i],x);
	return now<=0;
}
signed main(){
	n=read(),t=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int l=1,r=1e12,ans=0;
	while(l+1<r){
		int mid=l+r>>1;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%lld\n",l);
	return 0;
}
```


---

## 作者：sbno333 (赞：0)

暴力可以每次都选取最大的 $t$ 个 $a_i$，答案加一，$a_i$ 减一，知道没有为止。

这样太慢，发现没有思路，所以考虑二分答案，发现代入二分后问题变得看的可做：每天至少做 $t$ 各科目 $k$ 天内是否可以构造出答案使得每天的科目不一样。

贪心可以把至少去掉，变成必须。

对于每天，需要安排 $t$ 各科目，总共 $kt$ 需要安排，对于每个科目，如果 $a_i\ge k$，可以每天都做一次这个科目，然后我们就安排了 $k$，需要安排的科目减少 $k$，可以证明同一个科目最多安排 $k$ 次。

由于每次考虑的科目不同，并且一个科目每天最多安排 $1$ 个，因此不会有同一天相同的情况。

接着对于 $a_i<k$，直接全部安排即可。

因此 $i$ 对安排的贡献为 $\min(a_i,k)$。

我们只需要返回最后是否安排满即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
int a[1000009];
bool ef(int k){
	int s;
	s=t*k;//s 待安排
	for(int i=1;i<=n;i++){
		s-=min(a[i],k);
		if(s<=0){//安排完
			return 1;
		}
	}
	return 0;//到最后都没安排完
}
signed main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l,r;
	l=1;
	r=1e12;
	while(l<r){
		int mid;
		mid=l+r+1;
		mid>>=1;
		if(ef(mid)){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	cout<<l<<endl;
	return 0;
} 
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

我们发现，如果满足有 $i$ 天是有趣的，那么一定满足有 $i - 1$ 天是有趣的，我们发现答案单调，于是考虑用二分。

对于第 $i$ 个科目，设我们二分到的值为 $x$，则如果 $a_i \leq x$，则全部都要刷，否则由于我们每天只需要刷一道题即可，$x$ 天只要刷 $x$ 道。

最后把所有贡献加起来，判断其是否大于等于 $kt$ 即可。

剩下的就是二分板子了。

代码过丑，不放了。

---

