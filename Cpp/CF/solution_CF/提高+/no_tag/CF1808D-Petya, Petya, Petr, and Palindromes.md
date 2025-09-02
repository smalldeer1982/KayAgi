# Petya, Petya, Petr, and Palindromes

## 题目描述

Petya and his friend, the robot Petya++, have a common friend — the cyborg Petr#. Sometimes Petr# comes to the friends for a cup of tea and tells them interesting problems.

Today, Petr# told them the following problem.

A palindrome is a sequence that reads the same from left to right as from right to left. For example, $ [38, 12, 8, 12, 38] $ , $ [1] $ , and $ [3, 8, 8, 3] $ are palindromes.

Let's call the palindromicity of a sequence $ a_1, a_2, \dots, a_n $ the minimum count of elements that need to be replaced to make this sequence a palindrome. For example, the palindromicity of the sequence $ [38, 12, 8, 38, 38] $ is $ 1 $ since it is sufficient to replace the number $ 38 $ at the fourth position with the number $ 12 $ . And the palindromicity of the sequence $ [3, 3, 5, 5, 5] $ is two since you can replace the first two threes with fives, and the resulting sequence $ [5, 5, 5, 5, 5] $ is a palindrome.

Given a sequence $ a $ of length $ n $ , and an odd integer $ k $ , you need to find the sum of palindromicity of all subarrays of length $ k $ , i. e., the sum of the palindromicity values for the sequences $ a_i, a_{i+1}, \dots, a_{i+k-1} $ for all $ i $ from $ 1 $ to $ n-k+1 $ .

The students quickly solved the problem. Can you do it too?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1808D/86f24a4a8ddcd54e3f5304c40e3875fe7ba6699c.png)

## 说明/提示

In the first example, the palindromicity of the subarray $ [1, 2, 8, 2, 5] $ is $ 1 $ , the palindromicity of the string $ [2, 8, 2, 5, 2] $ is also $ 1 $ , the palindromicity of the string $ [8, 2, 5, 2, 8] $ is $ 0 $ , and the palindromicity of the string $ [2, 5, 2, 8, 6] $ is $ 2 $ . The total palindromicity is $ 1+1+0+2 = 4 $ .

In the second example, the only substring of length $ 9 $ coincides with the entire string, and its palindromicity is $ 0 $ , so the answer is also $ 0 $ .

## 样例 #1

### 输入

```
8 5
1 2 8 2 5 2 8 6```

### 输出

```
4```

## 样例 #2

### 输入

```
9 9
1 2 3 4 5 4 3 2 1```

### 输出

```
0```

# 题解

## 作者：Anguei (赞：7)

## 分析

此题最重要的性质是在于 $k$ 的范围：**保证是奇数**。$k$ 是奇数，那么所有长度为 $k$ 的区间当中的所
有元素，轴对称的位置与其本身的位置 **奇偶性保持一致**。因为假设对称轴坐标是整数 $m$，那么对称轴左侧位置为 $m-i$ 的元素，对称之后就到了 $m+i$ 的位置，而 $(m+i) - (m-i) = 2i$ 是偶数。

对于此类计数问题，可以从左到右，依次扫描每个元素，计算有多少元素可以与之配对。为了避免重复，对于第 $p$ 个元素，我们只从 $[1, p-1]$ 范围内（即 **它的左侧**）进行计数。

长度为 $n$ 的序列最多有 $n-k+1$ 个长度为 $k$ 的子区间，每个子区间最多贡献 $\frac{k+1}{2}$ 的答案（要记得 $k$ 是奇数），因此答案的最大值是 $(n-k+1) \times \frac{k+1}{2}$。

假设对于第 $p$ 个元素，它左侧可能存在与之配对（对称并相等）的元素的范围是 $[l, r]$，那么只要提前分奇偶把所有数字出现的位置存下来，使用 `std::upper_bound` 和 `std::lower_bound` 就可以快速计算出这个范围内有多少个。答案的最大值减去所有的配对个数，就是最终答案。

那么接下来的主要问题，就是计算 $[l, r]$。

### 对于 $l$

- 首先要保证 $l$ 到 $p$ 的距离在 $k$ 以内，即 $p-l+1 \leq k$，化简得到 $l \geq p-k+1$。
- $l$ 与 $p$ 之间对称轴的位置是 $m=\frac{l+p}{2}$，要保证对称轴左边还有足够的位置来容纳这个长度为 $k$ 的区间，得到 $\frac{l+p}{2} - \frac{k+1}{2} \geq 1$，化简得到 $l \geq k+2-p-1$。

### 对于 $r$

- 为了避免重复计算，我们只考虑在 $p$ 左边的可能的位置。$r$ 的最大值在对称轴位于 $m=p-1$ 的时候取到，此时 $r=p-2$。因此：$r \leq p - 2$。
- $r$ 与 $p$ 之间对称轴的位置是 $m = \frac{r+p}{2}$，与刚才类似，现在要保证对称轴右边（到数组尽头）还有足够的位置来容纳这个长度为 $k$ 的区间，即 $\frac{r+p}{2} + \frac{k+1}{2} <= n$，化简得到 $r \leq 2n - p - k + 1$。

### 整理式子

根据上述计算，有 $$\begin{aligned} l &= \max(p-k+1, k-p+1) \\ r &= \min(p-2, 2n-p-k+1) \end{aligned}$$
要注意有可能计算得到 $l > r$，这种情况应当予以忽略。

## 代码

```cpp
void solution() {
  int n, k;
  std::cin >> n >> k;
  assert(k & 1);
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  std::vector<std::vector<int>> odd(200001), even(200001);
  for (int i = 1; i <= n; ++i)
    i & 1 ? odd[a[i]].push_back(i) : even[a[i]].push_back(i);
  ll ans = 1ll * (k / 2) * (n - k + 1);
  auto solve = [&](auto& pos) {
    for (int x = 1; x <= 200000; ++x) {
      for (auto p : pos[x]) {
        int l = std::max(p - k + 1, k - p + 1);
        int r = std::min(p - 2, 2 * n - p - k + 1);
        auto it1 = std::lower_bound(pos[x].begin(), pos[x].end(), l);
        auto it2 = std::upper_bound(pos[x].begin(), pos[x].end(), r);
        auto sub = std::distance(it1, it2);
        ans -= sub <= 0 ? 0 : sub;
      }
    }
  };
  solve(odd);
  solve(even);
  std::cout << ans << "\n";
}
```

---

## 作者：mod998244353 (赞：7)

我们考虑计算有几个二元组 $(i,j)$ 对答案有贡献 $(1\leq i< j\leq n)$。

由于 $k$ 为奇数，所以 $i,j$ 的奇偶性相同。

由于区间长度为 $k$ 且 $i\not=j$，得到： $i+2\leq j\leq i+k-1$

由于 $(i,j)$ 对应的回文区间不能超出边界，式子用回文区间中心点的范围来写：

$\dfrac{k+1}{2}\leq \dfrac{i+j}{2}\leq n-\dfrac{k-1}{2}$

化简得： $k-i+1\leq j\leq2n+1-k-i$

所以我们对于每个 $i$，要计算的 $j$ 的区间为：

$[\max\{i+2,k-i+1\},\min\{n,i+k-1,2n+1-k-i\}]$

还有 $i,j$ 的奇偶性相同， $a_i\not=a_j$ 的限制。

采用类似莫队的计算方式，可以发现，$l$ 指针先减小一段之后增大，$r$ 指针先增大一段之后减小。

所以总移动次数是 $O(n)$ 级别的，故时空复杂度为 $O(n)$，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=200005;
inline int read() {
	static int x=0,c=getchar(),f=1;
	for(f=1; c<=47||c>=58; c=getchar())f=f&&c^45;
	for(x=0; c>=48&&c<=57; c=getchar())x=(x<<3)+(x<<1)+(c&15);
	return f?x:-x;
} 
int n,k,a[MAXN],cnt[MAXN],l,r;
inline int calc(int L,int R,int x) {
	if((L&1)!=(x&1)) ++L;
	if((R&1)!=(x&1)) --R;
	if(L>R)return 0;
	while(l>L) --l,cnt[a[l]]+=(l&1)==(x&1);
	while(r<R) ++r,cnt[a[r]]+=(r&1)==(x&1);
	while(l<L) cnt[a[l]]-=(l&1)==(x&1),++l;
	while(r>R) cnt[a[r]]-=(r&1)==(x&1),--r;
	return (R-L+2)/2-cnt[a[x]];
}
int main() {
	n=read(),k=read(),l=1,r=0;
	for(int i=1; i<=n; ++i) a[i]=read();
	ll ans=0;
	for(int i=1; i<=n; i+=2)
		ans+=calc(max(i+2,k-i+1),min(n,min(i+k-1,n+n-k+1-i)),i);
	memset(cnt,0,sizeof(cnt));
	l=1,r=0;
	for(int i=2; i<=n; i+=2)
		ans+=calc(max(i+2,k-i+1),min(n,min(i+k-1,n+n-k+1-i)),i);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Xy_top (赞：2)

这里是无脑的 ds 解法。

首先正难则反，先假设所有长度为 $k$ 的都需要进行 $\lfloor \frac{k}{2}\rfloor$ 次操作，那么总答案为 $\lfloor \frac{k}{2}\rfloor\times (n-k+1)$，然后因为有些数会相同所以就不用换了，倒着扫一遍，找它后面与它相同的数中有几个符合条件。

设它后面与它相同的数为 $x$，当前的数位置为 $i$，满足条件当且仅当 $\min(n-x,i-1)\times2+n-x+1\geq k$，发现这个不等式并不好解，可以把两种情况都解一下，因为有一种要求更严格。

然后对每个数，还要分奇偶性建一个动态开点线段树维护每个数字出现的位置，直接 query 即可。

注意我代码中 query 的上下界，还有两个特殊的取值。

~~代码虽然长但如果直接贺线段树板子 $5$ mins 大概能敲完吧。~~

```cpp
#include<iostream>
using namespace std;
int n,k,cnt;
int a[200005],rt1[200005],rt2[200005];
int sum1[4000005],ls1[4000005],rs1[4000005];
int sum2[4000005],ls2[4000005],rs2[4000005];
long long ans;
void add1(int l,int r,int &k,int x){
	if(!k)k=++cnt;
	sum1[k]++;
	if(l==r)return;
	int mid=l+r>>1;
	if(x<=mid)add1(l,mid,ls1[k],x);
	else add1(mid+1,r,rs1[k],x);
}
void add2(int l,int r,int &k,int x){
	if(!k)k=++cnt;
	sum2[k]++;
	if(l==r)return;
	int mid=l+r>>1;
	if(x<=mid)add2(l,mid,ls2[k],x);
	else add2(mid+1,r,rs2[k],x);
}
int query1(int l,int r,int k,int x,int y){
	if(y>n)return query1(l,r,k,x,n);
	if(x>y)return 0;
	if(x<=l&&y>=r)return sum1[k];
	int mid=l+r>>1,res=0;
	if(x<=mid)res=query1(l,mid,ls1[k],x,y);
	if(y>mid)res+=query1(mid+1,r,rs1[k],x,y);
	return res;
}
int query2(int l,int r,int k,int x,int y){
	if(y>n)return query2(l,r,k,x,n);
	if(x>y)return 0;
	if(x<=l&&y>=r)return sum2[k];
	int mid=l+r>>1,res=0;
	if(x<=mid)res=query2(l,mid,ls2[k],x,y);
	if(y>mid)res+=query2(mid+1,r,rs2[k],x,y);
	return res;
}
int main(){
	cin>>n>>k;
	cnt=400000;
	for(int i=1;i<=200000;i++)rt1[i]=i;
	for(int i=1;i<=200000;i++)rt2[i]=i+200000;
	ans=(long long)(k/2)*(n-k+1);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i>=1;i--){
		if(i&1){
			ans-=query1(1,n,rt1[a[i]],max(k-i+1,i+2),min(2*n-k-i+1,k+i-1));
			add1(1,n,rt1[a[i]],i);
		}else{
			ans-=query2(1,n,rt2[a[i]],max(k-i+1,i+2),min(2*n-k-i+1,k+i-1));
			add2(1,n,rt2[a[i]],i);
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：hh弟中弟 (赞：1)

### [CF1808D Petya, Petya, Petr, and Palindromes](https://www.luogu.com.cn/problem/CF1808D)
比较水的题。首先直接不太好想，正难则反，考虑将所有不需要改变的点对处理出来，拿总数一减就是答案。\
发现合法数就是两个位置的数相同，所以就变成了，对于每一个数，查询指定区间内与它相等的数的个数。\
因为需要满足回文的对称性，所以偶数位置只会和偶数位置匹配，奇数位置只会和奇数位置匹配，此时其实可以直接无脑上数据结构了，时间复杂度 $\mathcal{O}(n\log n)$。\
不考虑数据结构，这里有两种处理方法。
- 开个桶记录一下每个数的出现次数，类似莫队的思想，两个指针记录一下桶的范围，每次查到 $a_i$ 时，求出与 $a_i$ 的对应位置范围，然后移动指针，如果位置 $j$ 与 $i$ 奇偶性相同，就产生 $1$ 的贡献，奇数偶数各查一次。
- 开桶记录每个数出现的奇数位置和偶数位置，对于每个数，双指针不断向右扩展，直到不合法时记录一下两个指针之间的数的个数，也是奇数偶数都查一次。

这两种做法的时间复杂度都是 $\mathcal{O}(n)$，做法一因为区间单调，所以保证了复杂度，做法二显然是线性，这里给出做法一的代码。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10;
int a[N],n,k,q[N],mid,l1,r1,ans;
inline void work(int pd){
	l1=1,r1=0;
	memset(q,0,sizeof(q));
	for(int i=mid+2+pd;i<=n;i+=2){
		int L=std::max(1ll,i-k+1),R=std::min(n,i+mid-1);
		int l=(L+L+k-1)-i,r=(R+(R-k+1))-i;
		while(r1<r){if((r1&1)!=(i&1))q[a[++r1]]++;else ++r1;}
		while(r1>r){if((r1&1)==(i&1))q[a[r1--]]--;else --r1;}
		while(l1<l){if((l1&1)==(i&1))q[a[l1++]]--;else ++l1;}
		while(l1>l){if((l1&1)!=(i&1))q[a[--l1]]++;else --l1;}
		ans+=q[a[i]];
	}
}
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	n=read();k=read();
	for(int i=1;i<=n;++i)a[i]=read();
	mid=k/2;int pd=mid&1;
	work(pd),work(pd^1);
	std::cout<<(n-k+1)*(k/2)-ans<<'\n';
}
```

---

## 作者：banned_gutongxing (赞：1)

## 思路

这道题很简单。

我们枚举去求回文度固然很难，那么我们可以**正难则反**，去看看单独每个的回文度。对于每个数的位置，按照奇数位偶数位分类。然而对于每个数，只需要求出有几个不匹配的位置，但是这个固然也很难，于是我们可以**再次正难则反**，算合法的个数，就很简单了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5+10;
int n,k,a[MAXN],ans,vis1[MAXN],vis2[MAXN];
bool use[MAXN];
vector<int> pos1[MAXN],pos2[MAXN];
void check(vector<int> v,int num){
	auto now = v.begin();
	auto farest = v.begin();
	while(now!=v.end()){
		while(farest!=v.end()&&*farest-*now<k) farest++;farest--;
		ans += farest-now+1;
		now++; 
	}
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i = 1;i<=n;i++){
		scanf("%lld",a+i);
		if(i&1){
			pos1[a[i]].push_back(i);
		}else{
			pos2[a[i]].push_back(i);
		}
	}
	for(int i = 1;i<=n;i++){
		if(i&1){
			if(!vis1[a[i]]){
				vis1[a[i]] = true;
				check(pos1[a[i]],a[i]);
			}
		}else{
			if(!vis2[a[i]]){
				vis2[a[i]] = true;
				check(pos2[a[i]],a[i]);
			}
		}
	}
	for(int i = 1;i<=k/2;i++){
		ans--;
		if(i&1){
			if(pos1[a[i]].size()==1) continue;
			auto tmp = lower_bound(pos1[a[i]].begin(),pos1[a[i]].end(),k-i+1);tmp--;
			auto now = lower_bound(pos1[a[i]].begin(),pos1[a[i]].end(),i);
			ans -= tmp-now;
		}else{
			if(pos2[a[i]].size()==1) continue;
			auto tmp = lower_bound(pos2[a[i]].begin(),pos2[a[i]].end(),k-i+1);tmp--;
			auto now = lower_bound(pos2[a[i]].begin(),pos2[a[i]].end(),i);
			ans -= tmp-now;
		}
	}
	for(int i = n;i>=n-k/2+1;i--){
		ans--;
		if(i&1){
			if(pos1[a[i]].size()==1) continue;
			auto tmp = upper_bound(pos1[a[i]].begin(),pos1[a[i]].end(),n-k+k-(i-(n-k))+1);	
			auto now = lower_bound(pos1[a[i]].begin(),pos1[a[i]].end(),i);
			ans -= now-tmp;
		}else{
			if(pos2[a[i]].size()==1) continue;
			auto tmp = upper_bound(pos2[a[i]].begin(),pos2[a[i]].end(),n-k+k-(i-(n-k))+1);
			auto now = lower_bound(pos2[a[i]].begin(),pos2[a[i]].end(),i);
			ans -= now-tmp;
		}
	}
	printf("%lld",1ll*(n-k+1)*(k+1)/2-ans);
	return 0;
}
```

---

## 作者：masonpop (赞：1)

思维题。感觉不难。

记 $\alpha(x,y)=1-[x=y]$。（即相等为 $0$，不等为 $1$）。不难发现，对于一个长度为 $2r+1$ 的串 $s$，要将它变为回文串的最小操作次数就是 $\sum\limits_{i=1}^r\alpha(s_i,s_{2r+2-i})$。

设 $k=2t+1$。以 $n=8$ 为例。此时容易发现，答案为 $\alpha(a_1,a_5)+\alpha(a_2,a_4)+\alpha(a_2,a_6)+\alpha(a_3,a_5)+\alpha(a_3,a_7)+\alpha(a_4,a_6)+\alpha(a_4,a_8)+\alpha(a_5,a_7)$。

其中显然有规律。对于每个 $i$，能和它在一起产生贡献的 $j$ 需要满足 $2|(j-i)\le 2t$，且 $\frac{i+j}{2}\in[t+1,n-t]$。设 $j=i+2s$，则 $s$ 需要满足 $s\in[t+1-i,\min\{t,n-t-i\}]$。这说明 $n-t-i>0$，即  $i\le n-t-1$。

整理可得对于每个 $i$，与其产生贡献的 $j$ 的范围是 $[\max\{i+2,2t+2-i\},\min\{2t+i,2n-2t-i\}]$。且 $i,j$ 奇偶性相同，$\alpha(a_i,a_j)=1$。

分 $i$ 的奇偶性考虑。此时左端点和右端点都是分成两段单调的，复杂度能保证在 $O(n)$。用类似莫队的方式维护即可。[代码](https://codeforces.com/contest/1808/submission/219982035)。

---

## 作者：Helenty (赞：0)

### 题目大意

给出一个长为 $n$ 的数组，对于每个长度为 $k$ 的连续数组，它的代价是变为回文数组的最小修改次数。求所有长度为 $k$ 的数组代价之和。

### 思路

正向思考并不容易算，我们可以考虑反着来。可以对于每一对数字的贡献计算，在全部的对数中减去不做出贡献的数对。因为k一定是奇数，所以对称的位置的奇偶性都是相同的，我们可以对于每个数计算与它可以配对的数量，具体做法可以在区间内二分找到配对的个数。

### Code


```cpp
#include <bits/stdc++.h>
 
typedef long long ll;
#define int long long
const int N = 2e5 + 5;
int n, k;
std::vector<int> vec[N][2];
 
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cin >> n >> k;
	if(k == 1) {
		std::cout << 0 << '\n';
		return 0;
	}
	ll ans = (n - k + 1) * (k / 2);
	for(int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		vec[x][i & 1].push_back(i);
	}
	auto get = [&](const std::vector<int> &v, int l, int r) {
		return upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l);
	};
	for(int i = 0; i < 2; i ++) {
		for(int j = 1; j <= 200000; j ++) {
			for(auto u : vec[j][i]) {
				int l = std::max((k - 1) + 2 - u, u - k + 1);
				int r = std::min(u - 2, 2 * n - (k - 1) - u);
				if(l <= r) ans -= get(vec[j][i], l, r);
			}
		}
	}
	std::cout << ans << '\n';
	return 0;
}
```

---

