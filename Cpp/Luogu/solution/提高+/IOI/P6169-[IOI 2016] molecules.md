# [IOI 2016] molecules

## 题目描述

彼得在一家公司工作，这家公司已经制造了一台检测分子的机器。每个分子的重量都是正整数。这台机器的检测范围是 $[l,u]$，这里 $l$ 和 $u$ 都是正整数。这台机器能够检测一个分子集合当且仅当这个集合包含了一个子集，这个子集的分子的重量属于机器的检测范围。

考虑 $n$ 个分子，重量记为 $w_0,\cdots,w_{n-1}$。如果存在一个下标的集合（并且该集合中的下标都不相同）$I=\{i_1,\cdots,i_m\}$ 使得 $l\le w_{i_1}+\cdots+w_{i_m}\le u$，那么检测就会成功。

由于机器的细节，$l$ 和 $u$ 之间的差距要保证会大于等于最重分子和最轻分子之间的差距，即 $u-l \ge w_{max}-w_{min}$，其中 $w_{max}=\max(w_0,\cdots,w_{n-1})$，$w_{min}=\min(w_0,\cdots,w_{n-1})$

你的任务是写一个程序，该程序能找到一个子集，使得该子集的总重量属于检测范围，或者判定没有这样的子集存在。


### 样例一 
 
 ```
  4 15 17
  6 8 8 7
 ```

这个例子当中，我们有四个分子，重量分别是 $6,8,8$ 和 $7$。这台机器可以检测子集总重量在 $15$ 到 $17$ 之间（包含 $15$ 和 $17$）的子集。注意，$17-15 \ge 8-6$。分子 $1$ 和分子 $3$ 的重量之和为 $w_1+w_3=8+7=15$, 所以应该输出
```
2
1 3
```
其他可能正确的答案有 
```
2 
1 2
```
（$w_1+w_2=8+8=16$）

和 
```
2
2 3
```
（$w_2+w_3=8+7=15$）。

### 样例二 

```
4 14 15
5 5 6 6
```

这个例子当中，我们有四个分子，重量分别为 $5,5,6$ 和 $6$，我们要寻找一个子集，其总重量介于 $14$ 和 $15$ 之间（包含 $14$ 和 $15$）。请注意，$15-14 \ge 6-5$。因为不存在总重量介于 $14$ 和 $15$ 之间的子集，所以输出 `0`。

## 说明/提示

对于 $100\%$ 的数据，$n \le 2 \times 10^5$，$w_i \le 	2^{31}-1$，$l,u \le 2^{31}-1$。

## 样例 #1

### 输入

```
1 10 12
9
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 5 10
4 2```

### 输出

```
2
0 1```

# 题解

## 作者：gznpp (赞：4)

题意：给定 $N$ 个数的集合 $A$，求出一个子集满足它的和在 $[L, R]$ 内。

特殊性质：$R - L \ge \max A - \min A$。

暴力：当然可以用 bitset 优化背包做，时间复杂度 $O(\dfrac{NW}{64})$，貌似可以过 Subtask 5。

这完全没有考虑特殊性质，而这正是正解不同之处。我们来探究一下它到底表达了什么。

正解：猜想对序列排序之后，答案可以是一个线段。

因为只要丢掉一个线段左侧的元素再增加一个右侧的元素，对答案的影响一定不超过 $\max A - \min A$，也就不超过 $R - L$，一定不会错过答案。

实现时先一路取前缀到和 $\le L$，然后模拟前面过程即可。复杂度瓶颈是排序的 $O(N \log N)$，双指针 $O(N)$。

Code:

```cpp
#include <bits/stdc++.h>
#include "molecules.h"
#define rgi register int
#define ll long long
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
using namespace std;
int n;
ll s,L,R;
vector<int> ans;
vector<pii> a;
vector<int> find_subset(int LL,int RR,vector<int> w)
{
	n=w.size();
	L=LL,R=RR;
	for(rgi i=0;i<n;++i)
		a.push_back(mkp(w[i],i));
	sort(a.begin(),a.end());
	for(rgi l=0,r=0;l<n;++l)
	{
		while(s<L&&r<n)
			s+=(ll)a[r++].fi;
		if(s>=L&&s<=R)
		{
			for(rgi i=l;i<r;++i)
				ans.push_back(a[i].se);
			return ans;
		}
		s-=a[l].fi;
	}
	return vector<int>();
}
```

官方题解还有一种做法，就是答案可以是一段前缀加一段后缀。

其实道理是一样的，先把前缀取完然后慢慢减前缀长度加后缀后缀长度即可，每次移动也不会超过 $\max A - \min A \le R - L$，不会错过答案。

Code:

```cpp
#include <bits/stdc++.h>
#include "molecules.h"
#define rgi register int
#define ll long long
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
using namespace std;
int n;
ll s,L,R;
vector<int> ans;
vector<pii> a;

vector<int> find_subset(int LL,int RR,vector<int> w) {
    n = w.size(); a.resize(n);
    L = LL, R = RR;
    for (int i = 0; i < n; ++i) {
        a[i].fi = w[i];
        a[i].se = i;
        s += (ll)w[i];
    }
    sort(a.begin(), a.end());
    for (int i = n - 1, j = n; i < j && i >= -1;) { // interval [0, i] \cup [j, n - 1]
        while (s > R && i >= 0) {
            s -= (ll)a[i].fi;
            --i;
        }
        if (L <= s && s <= R) {
            for (int k = 0; k <= i; ++k) ans.push_back(a[k].se);
            for (int k = j; k < n; ++k) ans.push_back(a[k].se);
            return ans;
        }
        --j;
        s += (ll)a[j].fi;
    }
    return vector<int>();
}
```

---

## 作者：wangliu (赞：0)

# P6169 \[IOI 2016] molecules

## 题目大意

给定有 $n$ 个元素的集合 $A$，求 $A$ 的子集，使子集所有元素之和在 $[L,R]$ 之间。

**特别的**：$R-L \ge w_{max}-w_{min}$，其中 $w_{max}=\max(w_0,\cdots,w_{n-1})$，$w_{min}=\min(w_0,\cdots,w_{n-1})$

## 思路

将集合元素排序，由特殊性质可知，答案必定在连续的区间上。因此我们可以用双指针和前缀和维护，先找到第一个大于 $r$ 的位置，然后进行如下操作：

- 如果 $\sum_{i=l}^rA_i>R$，$l$ 指针前移。
- 如果 $\sum_{i=l}^rA_i<L$，$r$ 指针前移。
- 否则输出答案，程序结束。

## 代码

```cpp
//洛谷非常重视学术诚信。抄袭、复制题解和代码，以达到刷 AC 率/AC 数量或其他目的的行为，在洛谷是严格禁止的.
//这将会导致您成为作弊者。
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+3;
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void print(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
int n,L,R;
struct number{
	int val,pos,sum;
	bool operator < (number a)const{
		return a.val > val;
	}
}arr[N];
signed main(){
	n = read();L = read();R = read();
	for(int i=1;i<=n;i++) arr[i].val = read(),arr[i].pos = i - 1;
	sort(arr + 1,arr + n + 1);
	int l = 1,r = 0;
	for(int i=1;i<=n;i++){
		arr[i].sum = arr[i-1].sum + arr[i].val;
		if(arr[i].sum >= L and r == 0) r = i; 
	}
	while(l <= r and r <= n){
		if(arr[r].sum - arr[l-1].sum >= L and arr[r].sum - arr[l-1].sum <= R){
			print(r-l+1);putchar('\n');
			for(int i=l;i<=r;i++){
				print(arr[i].pos);putchar(' ');
			}
			return 0;
		}
		if(arr[r].sum - arr[l-1].sum >= R) l++;
		else if(arr[r].sum - arr[l-1].sum <= L) r++;
	}
	print(0);
	return 0;
}
```

这样就成功拿下 IOI 力！~~其实题目挺水的~~

时间复杂度主要在排序上。

---

## 作者：shinzanmono (赞：0)

考虑限制条件 $u-l\geq w_{\max}-w_{\min}$，如果将数组排序，那么我们将最小值删去，最大值加回来，差值一定不会大于 $u-l$，所以我们不会错过任意可能的答案。于是我们可以将原数组排序，然后先找到 $< L$ 的最大前缀，然后向右拓展区间即可。时间复杂度 $O(n\log n)$，瓶颈在于排序。

```cpp
#include<iostream>
#include<algorithm>
#include<bitset>
#include<vector>
const int sz=2e5+10;
int a[sz],w[sz];
std::vector<int> solve(int n,int l,int r){
    for(int i=1;i<=n;i++)a[i]=i-1;
    std::sort(a+1,a+n+1,[&](int x,int y){return w[x]<w[y];});
    int ql=1,qr=0;
    long long sum=0;
    while(qr<=n&&sum<l)sum+=w[a[++qr]];
    if(qr==n+1)return std::vector<int>();
    if(sum>=l&&sum<=r){
        std::vector<int>ans;
        for(int i=ql;i<=qr;i++)ans.push_back(a[i]);
        return ans;
    }
    sum-=w[a[qr--]];
    while(qr<n&&sum<l){
        sum+=w[a[qr+1]]-w[a[ql]];
        ql++,qr++;
    }
    if(sum<l||sum>r)return std::vector<int>();
    else{
        std::vector<int>ans;
        for(int i=ql;i<=qr;i++)ans.push_back(a[i]);
        return ans;
    }
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,l,r;
    std::cin>>n>>l>>r;
    for(int i=0;i<n;i++)std::cin>>w[i];
    std::vector<int>res=solve(n,l,r);
    std::cout<<res.size()<<"\n";
    for(int i=0;i<res.size();i++)std::cout<<res[i]<<" ";
    std::cout<<"\n";
    return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

 [洛谷传送门](https://www.luogu.com.cn/problem/P6169)

## 分析

结论：如果存在解，则一定有一个解使得选的数是排序后的一段前缀并上一段后缀。

下文所说序列均已排序。

引理：对于一个可行解选的某个数，一定可以将其换成序列中的最小数或最大数而使得换完之后还是一个可行解。

证明：反证法。假设都不可换。

设当前选的所有数的和为 $s$，限制为 $\ge L$ 且 $\le R$，所给的所有重量最大值为 $r$，最小值为 $l$。要换掉的数为 $x$。

先考虑换成最大数，则不可换等价于 $r - x > R - s$。

同理不可换为最小数等价于 $x - l > s - L$。

由于都不可换，所以两式同时成立。于是两式相加，得 $r - l > R - L$，与题目所给限制条件矛盾。所以必有至少一个方向可换。

证毕。

根据引理弱化可得，必然可以将可行解中的某个数变大或变小（换之后要保证在给定数中），而保证换之后仍为可行解。

那么我们随便考虑一个可行解，从左往右看选的每个数。我们肯定可以把这个数换成还未选的最大数或最小数，而且换完之后还是可行解。

于是必然可以把这个可行解中所有选的数都堆到前缀或后缀上。从而必存在一个可行解是一段前缀并上一段后缀。

于是枚举右端点，符合条件的左端点必为一段区间。搞出这个区间的左右端点，即可判断是否可行。注意不要选到重复数。记得判无解。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
pair<long long, int> a[2000005];
long long pre[200005];
// first >=
int n, l, r;
vector<int> ans;
int bck[200005];
int Search1(long long x) {
    int l = 1, r = n, mid, ans = n + 1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (pre[mid] >= x)
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return ans;
}
// last <=
int Search2(long long x) {
    int l = 1, r = n, mid, ans = -1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (pre[mid] <= x)
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> l >> r;
    for (int i = 1; i <= n; i++) cin >> a[i].first;
    for (int i = 1; i <= n; i++) a[i].second = i;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i].first;
    long long suf = 0;
    for (int i = n + 1; i; --i) {
        suf += a[i].first;
        if (suf >= l && suf <= r) {
            cout << n - i + 1 << "\n";
            while (i <= n) cout << (a[i++].second) - 1 << " ";
            return 0;
        }
        int x = Search1(l - suf);
        int y = min(i - 1, Search2(r - suf));
        if (x <= y) {
            cout << n - i + 1 + x << "\n";
            while (x) cout << (a[x--].second) - 1 << " ";
            while (i <= n) cout << (a[i++].second) - 1 << " ";
            return 0;
        }
    }
    cout << 0 << "\n";
    return 0;
}
```

---

## 作者：0xyz (赞：0)

我们首先将所有数从小到大排好，预处理出 $w$ 的前缀和 $s$，然后枚举子集 $i$。子集的和 $sum$ 必然在 $[s_i,s_n-s_{n-i}]$。

我们分 3 类讨论：

- $l\le s_i\le r$ 或者 $l\le s_n-s_{n-i}\le r$。已经成立。
- $r<s_i$ 或者 $s_n-s_{n-i}<l$。子集大小为 $i$ 必然不成立。
- $s_i\le l\le r\le s_n-s_{n-i}$。我们一开始令 $sum=s_i$，选前 $i$ 个数，然后逐渐将最后的那个元素 $j$ 往后调。每次调整最多将 $sum$ 增大 $w_{k+1}-w_k\le w_{max}-w_{min}\le r-l$，必然会有一个状态使得 $sum\in[l,r]$。我们可以先将 $j$ 调到最右边的 $n-i+j$，然后如果 $sum>r$ 就把 $j$ 调回去，然后一个一个往右调。

时间复杂度 $O(n\log n)$，瓶颈在排序。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int _=2e5+5;
struct O{int x,y,z;}a[_];
long long s[_],sum;
vector<int>find_subset(int l,int r,vector<int>w){
	int n=w.size();vector<int>res;
	for(int i=1;i<=n;i++)a[i].x=w[i-1],a[i].y=i-1;
	sort(a+1,a+n+1,[&](O u,O v){return u.x<v.x;});
	for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i].x;
	for(int i=1;i<=n;i++)
		if(l<=s[i]&&s[i]<=r){
			for(int j=1;j<=i;j++)a[j].z=1;
			break;
		}else if(l<=s[n]-s[n-i]&&s[n]-s[n-i]<=r){
			for(int j=n-i+1;j<=n;j++)a[j].z=1;
			break;
		}else if(s[i]<l&&r<s[n]-s[n-i]){
			sum=s[i];
			for(int j=1;j<=i;j++)a[j].z=1;
			for(int j=i;j;j--){
				if(sum+a[n-i+j].x-a[j].x>r){
					for(int k=j+1;k<n-i+j;k++)
						if(sum+a[k].x-a[j].x>=l){
							sum+=a[k].x-a[j].x;
							a[j].z=0;a[k].z=1;
						}
				}else{
					sum+=a[n-i+j].x-a[j].x;
					a[j].z=0;a[n-i+j].z=1;
				}
				if(l<=sum&&sum<=r)break;
			}
			break;
		}
	for(int i=1;i<=n;i++)
		if(a[i].z)res.push_back(a[i].y);
	return res;
}
int main(){
	int n,l,u;
	scanf("%d%d%d",&n,&l,&u);
   	vector<int>w(n);
	for(int i=0;i<n;i++)scanf("%d",&w[i]);
	vector<int>res=find_subset(l,u,w);
	int m=res.size();
	printf("%d\n",m);
    for(int i=0;i<m;i++)printf("%d%c",res[i],i==m-1?'\n':' ');
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

为方便叙述，以下内容中以 $r$ 代替原题中的 $u$。注意到有一个条件：$r-l\geq w_{max}-w_{min}$。以此为突破口，可以发现，答案一定是排序后的数列内的连续段。因为每次我们往右端新增一个数，并从左端删去数，整段的和必定不会变化超过 $r-l$，因此在双指针扫的时候一定能扫出答案。要注意，下标从 $0$ 开始。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
pii p[200010];
int cmp(pii p1,pii p2)
{
	return p1.first<p2.first;
}
signed main()
{
	int n,l,r;
	cin>>n>>l>>r;
	for(int i=0;i<n;i++)
	{
		cin>>p[i].first;
		p[i].second=i;
	}
	sort(p,p+n,cmp);
	int h=0,t=0,now=p[0].first;
	while(h<=t&&t<n)
	{
		if(l<=now&&now<=r)
		{
			cout<<t-h+1<<endl;
			for(int i=h;i<=t;i++) cout<<p[i].second<<' ';
			return 0;
		}
		while(now>r&&h<t)
		{
			now-=p[h].first;
			h++;
		}
		if(l<=now&&now<=r)
		{
			cout<<t-h+1<<endl;
			for(int i=h;i<=t;i++) cout<<p[i].second<<' ';
			return 0;
		}
		t++;
		now+=p[t].first;
	}
	cout<<0;
	return 0;
}

---

## 作者：Aurora_Borealis_ (赞：0)

#  [IOI2016]molecules 题解

在看到题目后提取关键词：子集。

既然问的是子集，那就说明了，在对数列排序的情况下不影响题目求解，且容易想到，排序后的数列中的答案要么没有，否则都是**连续的**一段数。

随后可以对数列取前缀和，由于排过序，所以具有二分性，可以二分找到答案，随手丢到 vector 里 return 就好了。

总复杂度 $ O(n \log n) $。 

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long maxn,cnt,ans[200001];
struct node{
	int id;
	long long num;
	bool operator < (const node &t) const {
		return num<t.num;
	}
}a[200001];
long long s[200001];
vector<int> find_subset(int l,int r,vector<int>w){
	int n=w.size();
	for(int i=1;i<=n;i++){
		a[i].id=i;
		a[i].num=w[i-1];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i].num;
	}
	for(int i=1;i<=n;i++){
		int ll=i,rr=n+1;
		while(rr-ll>1){
			int mid=(ll+rr)>>1;
			if(s[mid]-s[i-1]<=r){
				ll=mid;
			}else{
				rr=mid;
			}
		}
		int R=ll;
		if(l<=s[R]-s[i-1]&&s[R]-s[i-1]<=r){
			if(R-i+1>=maxn){
				cnt=0;
				maxn=R-i+1;
				for(int k=i;k<=R;k++){
					ans[++cnt]=a[k].id;
				}
			}
		}
	}
	vector<int>answer;
	for(int i=1;i<=cnt;i++){
		answer.push_back(ans[i]-1);
	}
	return answer;
}
```


---

