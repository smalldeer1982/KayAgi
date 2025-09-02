# [ABC389E] Square Price

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc389/tasks/abc389_e

有 $ N $ 种商品，每种商品各有 $ 10^{100} $ 个。

你可以购买任意数量的每种商品（包括 0 个）。购买第 $ i $ 种商品 $ k $ 个需要花费 $ k^2 P_i $ 日元。

在总花费不超过 $ M $ 日元的条件下，求最多可以购买多少个商品。

## 说明/提示

### 约束条件

- $ 1 \leq N \leq 2 \times 10^{5} $
- $ 1 \leq M \leq 10^{18} $
- $ 1 \leq P_i \leq 2 \times 10^{9} $
- 输入数值均为整数

### 样例解释 1

购买第 1 种商品 1 个、第 2 种商品 2 个时，总花费为 $ 1^2 \times 4 + 2^2 \times 1 = 8 $ 日元。由于无法在总花费不超过 9 日元的情况下购买 4 个或更多商品，因此答案为 3。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 9
4 1 9```

### 输出

```
3```

## 样例 #2

### 输入

```
10 1000
2 15 6 5 12 1 7 9 17 2```

### 输出

```
53```

# 题解

## 作者：chenxi2009 (赞：14)

**Upd 2025.1.22: 细节问题被 Hack，修改代码。**
## 思路
转化：对于一种商品 $P_i=p$，第 $x$ 件的价格为 $(2x-1)p$，且购买它之间必须先购买第 $x-1$ 件同种商品（$x>1$）。

由于购买一件商品之后“解锁”的商品只会更贵，所以贪心地每次选择当前可购买的最便宜的一件商品不劣。

如果这样模拟写一个多路归并贪心就 [T 了](https://atcoder.jp/contests/abc389/submissions/61808256)。显然当 $P_i=1$ 时，要买 $10^9$ 件花费才到 $M$ 的上界。

多路归并没有优化的空间，但是贪心思路启发我们使用二分。贪心每一次购买当前最便宜的商品，这样去购买每一次花费的钱是不减的。\
宏观上看就是购买了一个价格以下的所有商品，再尝试买这个价格的商品直至没钱。

可以二分最高的价格使得能把这个价格及以下的商品全部买完，然后尝试购买这个价格加一的商品。

**如何快速购买一个价格以下一个种类的所有商品？**

对于商品 $P_i=p$，要找到最大的 $k$ 使得 $(2k-1)p\le X$。期中 $X$ 为限定价格。\
解得 $k\le\frac{X+p}{2p}$。所以共购买$k=\left \lfloor \frac{X+p}{2p} \right \rfloor $ 件商品，花费为 $k^2p$。

综上 $O(1)$ 可以得出一个价格确定的商品种类在购买一个价格以下所有商品时的花费与收益。\
所以得知所有在一个价格下的商品全部买完的花费是 $O(N)$ 的，二分复杂度 $O(N\log M)$。

二分完之后按照价格买就行了。时间复杂度 $O(N\log M)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[300000];
long long m,l,r,mid,ans,k;
inline bool check(long long x){
	long long cnt = 0;
	for(int i = 1;i <= n;i ++){
		k = (x + p[i]) / (2ll * p[i]);//购买的商品数 
		if(k >= 1000000000 || k * k >= 2e18 || 2e18 / p[i] < k * k) return false; //防爆 long long 
		cnt += k * k * p[i];
		if(cnt > m) return false;
	}
	return true;
}
int main(){
	scanf("%d%lld",&n,&m);
	for(int i = 1;i <= n;i ++) scanf("%d",&p[i]);
	l = 0,r = m;
	while(l < r){
		mid = l + r + 1 >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	for(int i = 1;i <= n;i ++){
		k = (l + p[i]) / (2 * p[i]);
		m -= k * k * p[i],ans += k;//购买 l 价格及以下的所有商品 
	} 
	printf("%lld",ans + m / (l + 1));//根据二分，l+1 的商品不会被买完，放心直接除就行
	return 0;
}

```

---

## 作者：2huk (赞：9)

若某件物品当前已经选了 $k$ 件，想再来一个变成 $k+1$，那么相当于多花费 $(k+1)^2p_i - k^2p_i = (2k+1)p_i$ 元。

于是我们可以把一种物品拆成无数个，价格分别为 $p_i,3p_i,5p_i,7p_i \dots$。这样要贪心选的话肯定先选前面便宜的，这样转化后的问题就跟原问题没有区别了。

于是一个非常 naive 的想法是真的把每种物品都拆成无数个价格分别为 $p_i,3p_i,5p_i,7p_i \dots$ 的「小物品」。然后将所有「小物品」从便宜到贵排序，然后从前往后能选就选。肯定不现实。

然而既然是从小到大选，就肯定存在最后一个选的，也就是最贵的。换言之，一定存在某个数 $x$，使得价格 $<x$ 的「小物品」都选了，$=x$ 的尽量多的选了，$>x$ 的选不了。

显然这个 $x$ 可以二分求出，check 合法的条件是能否将价格 $<x$ 的「小物品」都选上且总价不超过 $M$。如果合法，再尝试求出最多能选多少 $=x$ 的「小物品」。

于是现在问题是求：

- 价格 $<x$ 的「小物品」价格和：
  - 对每种物品分别考虑。第 $k$ 件「小物品」的价格为 $(2k+1)p_i$，我们要求 $(2k+1)p_i < x$，那么最大的 $k$ 可以解不等式求出。这个最大的 $k$ 就代表这种物品我们要选 $k$ 个，即价格和为 $k^2p_i$。
- 有多少价格 $=x$ 的「小物品」：
  - 即有多少种物品 $i$ 满足存在 $k$ 使得 $(2k+1)p_i = x$。解方程即可。

```cpp
// Problem: E - Square Price
// Contest: AtCoder - Toyota Programming Contest  2025（AtCoder Beginner Contest 389)
// URL: https://atcoder.jp/contests/abc389/tasks/abc389_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #define tests
#include <bits/stdc++.h>

using namespace std;

#define int long long
typedef __int128 ll;

const int N = 2e5 + 10;

int n, m, p[N];

int get(int p, int m) {
	int lo = 1, hi = 1e18, res = 0;
	while (lo <= hi) {
		int mid = lo + hi >> 1;
		if ((__int128)(mid * 2 - 1) * p < m) {
			res = mid;
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	return res;
}

void solve() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; ++ i ) {
		cin >> p[i];
	}
	
	int lo = 0, hi = 1e18, res = 0;
	while (lo <= hi) {
		int mid = lo + hi >> 1;
		
		ll cnt0 = 0, cnt1 = 0, sum = m;
		for (int i = 1; i <= n; ++ i ) {
			// (2k - 1) * p[i] < mid
			ll k = get(p[i], mid);
			
			cnt0 += k;
			sum -= k * k * p[i];
			
			if ((2 * k + 1) * p[i] == mid) {
				cnt1 ++ ;
			}
			
			if (sum < 0) break;
		}
		
		if (sum >= 0) {
			res = max(res, (int)(cnt0 + min(cnt1, sum / mid)));
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	
	cout << res;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
#ifdef tests
	cin >> T;
#endif
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：george0929 (赞：5)

其实这个套路挺经典的。

买一个物品共 $k$ 件需要花 $k^2P$ 元，可以转换为:

> 已经买了 $k-1$ 件这个物品，再买一件，需要加价 $(k^2-(k-1)^2)P=(2\times k-1)P$ 元。

$(2\times k-1)P$ 随 $k$ 的增大而增大，考虑贪心，每次买一件加价最少的物品，直到钱不够为止。

物品价格以平方速度增长，所以最多购买 $O(\sqrt M)$ 个物品，因此时间复杂度 $O(N\sqrt M)$，使用优先队列优化可以做到 $O((\log N)\sqrt M)$，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,M;
__int128 m;
__int128 p[200005];
struct node{
	int id;
	__int128 up,cnt;
	bool operator< (const node &b) const{
		return up>b.up;
	}
};
priority_queue<node> Q;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>M;
	m=M;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		p[i]=x;
		Q.push({i,p[i],1});
	}
	int ans=0;
	while(1){
		auto u=Q.top();
		Q.pop();
		if(m<u.up) break;
		ans++;
		m-=u.up;
		u.up=(2*u.cnt+1)*p[u.id];
		u.cnt++;
		Q.push(u);
	}
	cout<<ans<<endl;
	return 0;
}
```

当然这个复杂度不足以通过此题，我们重新考察这个贪心的过程，每次加价的价格单调不降（即上述代码第 $32$ 行 `u.up` 单调不降），而每次加价会使答案增加 $1$，因此答案随最后一个加价价格的增加而增加。

因此我们考虑二分答案，二分最后一个加价的价格，之后算出每个物品的最大购买件数，检查总费用是否 $\le M$ 即可。

设最后加价价格为 $mx$，则对于物品 $i$，有 $(2\times k-1)P\le mx$，即 $k\le \frac{mx+P}{2P}$。

求出最后加价价格 $mx$ 后，批量处理每个物品购入 $\frac{mx+P}{2P}$ 件。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,p[200005];
bool ck(int mx){
	__int128 pri=0;
	for(int i=1;i<=n;i++){//p(2*mid-1)<=mx
		__int128 t=(mx+p[i])/(2*p[i]);
		t*=t;
		if(t>(__int128)m) return false;
		t*=p[i];
		if(t>(__int128)m) return false;
		pri+=t;
	}
	return pri<=m;
}
int getans(int mx){
	int ans=0;
	for(int i=1;i<=n;i++){//2*mid-1<=mx
		ans+=(mx+p[i])/(2*p[i]);
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	int l=1,r=m,res=0;
	while(l<=r){
		int mid=(l+r)/2;
		if(ck(mid)){
			res=mid;
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	cout<<getans(res)<<"\n";
	return 0;
}
```

然后你发现你 WA 了两个点，考虑这个例子：

```
2 25
1 1
```

最优解是第一个物品购买 $3$ 个，第二个物品购买 $4$ 个，最后加价价格为 $16-9=7$。

但是如果最后加价价格为 $7$，二分检查时程序会认为每个物品都购买了 $4$ 个，从而返回 `false`。

因此我们得到的最后加价价格上界为 $6$，于是最后批量处理时程序会认为每个物品只能买 $3$ 个，少算了 $1$ 个，然后就 WA 了。

解决方法很简单，少算当且仅当两个物品加价价格一样，因此每个物品最多少算 $1$ 个，答案最多少算 $N$ 个，在批量处理之后，计算出剩余钱数，然后用优先队列处理少算的部分即可。

时间复杂度 $O(N\log M+N\log N)$，可以通过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,p[200005];
bool ck(int mx){
	__int128 pri=0;
	for(int i=1;i<=n;i++){//检查总费用是否小于等于 M
		__int128 t=(mx+p[i])/(2*p[i]);
		t*=t;
		if(t>(__int128)m) return false;
		t*=p[i];
		if(t>(__int128)m) return false;
		pri+=t;
	}
	return pri<=(__int128)m;
}
struct node{
	int id;
	__int128 up,cnt;
	bool operator< (const node &b) const{
		return up>b.up;
	}
};
priority_queue<node> Q;
int getans(int mx){
	int ans=0;
	for(int i=1;i<=n;i++){//批量处理
		int t=(mx+p[i])/(2*p[i]);
		ans+=t;
		m-=t*t*p[i];
		Q.push({i,(__int128)p[i]*(2*t+1),t+1});
	}
	while(m){//处理少算的部分
		auto u=Q.top();
		Q.pop();
		if(m<u.up) break;
		ans++;
		m-=u.up;
		u.up=(__int128)(2*u.cnt+1)*p[u.id];
		u.cnt++;
		Q.push(u);
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	int l=1,r=m,res=0;
	while(l<=r){//二分最后加价的价格
		int mid=(l+r)/2;
		if(ck(mid)){
			res=mid;
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	cout<<getans(res)<<"\n";
	return 0;
}
```

---

## 作者：_Kenma_ (赞：4)

## 前言

E 比 F 困难，怎么会是呢？

## 思路分析

首先考虑一种经典做法：将问题转化为物品体积为 $p_i,3p_i,5p_i,7p_i \cdots$ 的 01 背包问题。因为物品价值都为 $1$，所以可以贪心地选择体积前 $k$ 小的物品。

然后问题转化到这一步就自然了，考虑二分出我们选与不选的物品体积的临界值，小于等于这个值的物品都选上。

已知临界值 $mid$，对于每一个 $p_i$，我们选择的物品数量 $k$ 应该满足：

$$(2k-1)p_i\le mid$$

放缩一下：

$$k \le \lfloor \frac{\lfloor \frac{mid}{p_i} \rfloor +1}{2} \rfloor$$

这里有一个细节：在选完小于等于临界值的物品后，如果背包容量还有剩余，会考虑选择大于临界值的物品，特判一下即可。

总体复杂度 $O(n \log m)$。

## 代码实现

不知道在 check 时会不会炸 long long，所以开了 __int128。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,p[200005],sum,m,n,maxn;
bool check(long long ans){
	__int128 sum=0;
	for(int i=1;i<=n;i++){
		__int128 num=((ans/p[i]+1))/2;
		sum+=num*num*p[i];
		if(sum>m) return false;
	}
	return true;
}
long long find(long long l,long long r){
	if(l==r) return l;
	long long mid=(l+r+1)>>1;
	if(check(mid)) return find(mid,r);
	else return find(l,mid-1);
}
int main(){
	//freopen("in.in","r",stdin);
	//freopen("out.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(long long i=1;i<=n;i++){
		cin>>p[i];
	}
	ans=find(0,m);
	for(long long i=1;i<=n;i++){
		__int128 num=(ans/p[i]+1)/2;
		sum+=num;
		m-=num*num*p[i];
		maxn=max((__int128)maxn,(2*num+1)*p[i]);
	}
	sum+=m/maxn;
	cout<<sum;
	return 0;
}
```

---

## 作者：201012280925LSY (赞：3)

## 题意
有 $n$ 个商品，第 $i$ 种商品的标价是 $p_i$，库存是 $10^{100}$。但是买 $k$ 个第 $i$ 种商品花的钱是 $k^2p_i$。你有 $m$ 块钱，问你最多能买多少个商品。
## 思路
看到这道题，可以发现同一种的商品的价格可以是不同的。第 $j$ 个第 $i$ 种商品的价格是 $p_i(2j-1)$。如果我们想买尽量多的商品，肯定不能在一种商品身上死磕。

容易想到十分暴力的做法：每次从所有商品中选择最便宜的一个商品，然后把这种商品下一个的价格算出来，加入到商品里面。

然而你就算是用优先队列来维护商品队列，也还是会超时。

既然是每次贪心去选，那么我们肯定想要是的每种商品买的最贵的商品的价格尽量接近，这样才不至于花太多的冤枉钱。我们如果把这些商品的价格求出来，就可以反过来求出买了多少个。那么这些接近的商品的价格怎么求呢？观察到这些商品的价格都是具有单调性，所以就可以二分了。

所以思路就很显然了。我们二分出来一个值之后，再把价格比这个值低的商品买完即可。

我们开心的写完之后，发现[过不了](https://atcoder.jp/contests/abc389/submissions/61852059)。然后测一下这个样例，错了。
```
2 1
1 1
```
答案是 `1`，但是程序输出了 `0`。

思考发现，如果我们买价格小于等于 `1` 的商品是买不完的。所以我们在买完了价格小于等于这个值的商品之后再尽量多买一些价格比这个值多一的商品即可。但是为什么不买多二的、多三的商品呢？因为我们是二分啊，所以我们在买完之后这个值是会往上涨的，到时候多二的、多三的商品自然就会被买下来了。

这里还有一个细节：在运算过程中注意不要不要爆 `long long`。例如在二分过程中，二分应该写成 `mid=l+(r-l)/2`。同时因为每一种商品至多只可能买 $10^9$ 个，所以如果买了多于 $10^9$ 个商品，就应该立即退出。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[200010],answer;
bool check(long long ans)
{
	long long sum=0,Ans=0;
	for(int i=1;i<=n;i++)
	{
		long long prize=ans/a[i];
		prize++;
		prize/=2;//计算这种商品买了多少个
		if(prize>1e9)return false;//多于 1e9 个商品
		Ans+=prize;
		prize=prize*prize*a[i];
		if(prize<0||prize>m-sum)return false;//钱不够用
		sum+=prize;
		if(sum>m||sum<0)return false;//钱不够用
	}           
	if(sum<m)//买比值多 1 的商品
	{
		for(int i=1;i<=n;i++)
		{
			long long prize=ans/a[i];
			prize++;
			prize/=2;
			prize++;
			prize=prize*2-1;
			prize*=a[i];
			if(ans+1==prize&&sum+prize<=m)sum+=prize,Ans++;//每一种的商品只有可能买一件
		}
	}
	answer=max(answer,Ans);
	return true;//钱足够用。
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	long long l=-1,r=m+1,mid;//有可能值为 0 的
	while(l+1<r)
	{
		mid=l+(r-l)/2;//注意细节
		if(check(mid))l=mid;
		else r=mid;
	}
	cout<<answer;
	return 0;
}
```

[记录](https://atcoder.jp/contests/abc389/submissions/61857125)

---

## 作者：wenlebo (赞：3)

众所周知，所有商品的收益都是一样的。

因为买 $j$ 件 $i$ 商品价格为 $i^2P_j$ 可以理解为第 $i$ 件 $j$ 商品价格为 $i^2P_j - (i-1)^2P_j$ 也就是 $(2i-1)P_j$ 元。

众所周知，能买便宜的为什么要买贵的。

所以说，我们贪心的想，我们要先买最便宜的，然后慢慢买贵的直到买不下。

但我们不可能把每一件商品的价格（同种商品买不同次价格不同，视为不同商品，见上文）算出来，取最小的一些值。不过可以确认的是，假如我们购买的商品价格最高为 $M$ 那么我们一定会将所有价格低于 $M$ 的商品都买了（价格等于 $M$ 的不一定全都要买）于是便想到二分答案。

我们二分 $M$ 的值，计算能否将所有价值小于 $M$ 的东西都买了（对于价值等于 $M$ 的东西，先买下来如果没钱了再卖了），再检查的同时更新最大能买的件数！

别忘了开 __int128，我因为没开这个 WA*3 致使没场切。

 _写在最后：致洛谷题解审核员，我非常反感洛谷题解审核的格式要求，尤其是对空格的，多一个少一个空格并不会影响阅读以及理解甚至是美观，而且只缺一个空格直接改一下不就行了吗，为什么要再费半天劲再交一遍等好几天？还有奇葩的英文问题，有一回我写在代码里面的注释都嫌它“不规范”，更不用说今天的 int128,我翻了 P7076 的题解，对数据类型的写法千奇百怪：有直接写的，有开 KaTeX 的，有用字符串的，所以请不要因为“那个 int128 有个数要用 Katex”之类的话拒绝了！_

---

## 作者：kkxacj (赞：2)

#### 思路

先考虑转化每个商品的贡献，对于一件商品 $i$，买第 $j$ 件的价格即为 $\left(2\times j-1\right) \times P_i$，也就是 $\left(j-1\right)^2\times P_i$ 到 $j^2 \times P_i$ 多出来的贡献，根据常识 $i > 0$。

转化完后我们最终每个商品的单价一定都会大于等于一个值 $x$，我们二分这个值即可，每次二分一个 $mid$，我们对于每个商品二分出一个最大的 $j$ 使得 $\left(2\times j-1\right) \times P_i < x$，这样下一件就一定 $\ge x$，然后我们令 $sum + j,sum1 + j^2\times P_i$，若 $sum1 > m$，则调小一点，$l=mid-1$，否则 $r = mid+1$。

不过这样并不算完，我们是满足了最终所有单价都大于等于一个数，可是这里面还可以**再选一些**，不过可以证明的是每个商品最多被选一次，若一个商品被被选了多次，说明一定**可以调大 $mid$** 达到这个状态，所以每次的最后将每个商品按单价排序贪心选即可。

**code**

```cpp
#include<bits/stdc++.h>
#define ll __int128
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 2e5+10;
int n;
ll m,a[N],b[N],ans,sum,sum1,l,r,mid,o,M;
inline bool check(ll x)
{
	sum = sum1 = 0;
	for(int i = 1;i <= n;i++)
	{
		ll l,r,mid; o = 0;
		l = 1,r = 1e18;
		while(l <= r)
		{
			mid = ((l+r)>>1);
			if((2*mid-1)*a[i] < x) l = mid+1,o = mid;
			else r = mid-1;
		}
		sum += o,sum1 += o*o*a[i];
		b[i] = (2*o+1)*a[i];
		if(sum1 > m) return 0;
	}
	sort(b+1,b+1+n); m -= sum1;
	for(int i = 1;i <= n;i++)
		if(m >= b[i]) m -= b[i],sum++;
	return 1;
}
signed main()
{
	read(n),read(m); M = m;
	for(int i = 1;i <= n;i++) read(a[i]);
	l = 0,r = 1e18;
	while(l <= r)
	{
		mid = (l+r)/2; m = M;
		if(check(mid)) ans = max(ans,sum),l = mid+1;
		else r = mid-1;
	}
	print(ans); flush();
	return 0;
}
/*
2*2*1

1*1*4

i*i
(i+k)*(i+k)
2k*i+k^2
*/
```

---

## 作者：ZHR100102 (赞：2)

把 `ll` 改 `__int128` 前 `WA*22`，改 `__int128` 直接 AC 了，难评。

抛开卡精度这题还是挺好的。

# 暴力

先考虑暴力思路，显然暴力应该这么打：把所有物品全丢进优先队列里，每次选出价值最小的物品，把多选择一个的物品的价值与当前数量的物品价值做差，丢进优先队列。一直执行直到不能选为止。

显然可以构造全 $1$ 的数据来把它卡爆，不能过。

# 正解

考虑优化暴力的过程，不难发现，我们最后取出的结果，代价一定小于等于某一个值。而每个元素选的越多，每一个的代价就越多，因此我们可以二分出最后选出的最大代价，设为 $mx$。假设当前在计算第 $i$ 个元素在此限制下最多能选 $k$ 个该元素，则可以得到下列不等式：

$$p_i\times(k^2-(k-1)^2)\le mx$$

$$p_i\times(2k-1)\times 1 \le mx$$


$$2k-1 \le \frac{mx}{p_i}$$

$$k \le \frac{mx}{2\times p_i}+\frac{1}{2}$$

因此，我们就可以求出 $k$ 了，之后在 check 时将当前答案加上 $k^2\times p_i$，最后看答案是否小于等于 $m$ 即可。

最后统计答案的时候，因为二分时默认所有选的代价都小于等于 $mx$，那么如果 $mx$ 后面的还有剩余，就还要加上这一部分的答案。

时间复杂度 $O(n \log V)$。

**注意精度问题，要开 `__int128` 和 `long double`，二分边界记得开大！**

# 总结

不论精度问题的话，这题还挺巧妙的。这题能用二分代替优先队列的关键就在于下列几点：
- 是取所有价值中的前 $x$ 小值，具有单调性。
- 单个元素的贡献能被快速计算。
- 单个元素的代价具有单调性。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
using pl=pair<ll,pair<ll,pair<ll,ll> > >;
ll n,m,p[200005],res=0;
bool check(ll mx)
{
    res=0;
    __int128 now=0;
    for(int i=1;i<=n;i++)
    {
        __int128 k=max(__int128(0),__int128(floor(ldb((ldb(1.0*mx)/ldb(p[i])+1.0))/ldb(2.0))));
        now+=k*k*p[i];
        if(now>m)return 0;
        res=res+k;
    }
    return 1;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>p[i];
    ll l=0,r=1e15,mid;
    while(l<r)
    {
        mid=(l+r+1)>>1;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    res=0;
    __int128 now=0;
    for(int i=1;i<=n;i++)
    {
        ll k=max(__int128(0),__int128(floor(ldb((ldb(1.0*l)/ldb(p[i])+1.0))/ldb(2.0))));
        now+=__int128(k)*__int128(k)*__int128(p[i]);
        res+=k;
    }
    for(int i=1;i<=n;i++)
    {
        __int128 kx=max(__int128(0),__int128(floor(ldb((ldb(1.0*l)/ldb(p[i])+1.0))/ldb(2.0))));
        __int128 ky=max(__int128(0),__int128(floor(ldb((ldb(1.0*(l+1))/ldb(p[i])+1.0))/ldb(2.0))));
        __int128 cst=__int128(ky)*__int128(ky)*__int128(p[i]),oricst=__int128(kx)*__int128(kx)*__int128(p[i]);
        if(kx!=ky&&now-oricst+cst<=m)
        {
            now=now-oricst+cst;
            res++;
        }
    }    
    cout<<res;
    return 0;
}
```

---

## 作者：sodalyghat (赞：2)

### 思路
一个贪心应该是很容易发现的，就是我们每次会选择当前价格最低的去买。然后根据题目给的条件，我们可以计算出当买第 $k$ 个物品 $i$ 时，我们花费的价格其实是 $(2k-1)P_i$ 元。然后就可以有一个暴力，就是把所有的物品扔到一个堆里，然后每次购买堆顶的物品，然后把这个物品价格改变之后的物品放回堆里。

然后我们考虑优化。我们可以二分一个 $mid$ 做为最大价格，单价不高于这个价格的物品全部购买。显然这是有单调性的。最后，我们在购买完所有单价不高于 $mid$ 的物品后，可能还剩一点钱可以购买少量价格高于 $mid$ 的物品，这部分就用上面提到的暴力即可，因为能买到的个数一定不超过 $n$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Luo_ty{
	const int MAXN = 300005;
	int a[MAXN];
	int n, m;
	bool check(int lim){
		int sum = m, cnt = 0;
		for(int i = 1;i <= n;i++){
			int tmp = lim / a[i];
			int k = (tmp + 1) / 2;
//			printf("%lld ", k);
			cnt += k;
			if(sum < (__int128)k * k * a[i]) return 0;
			sum -= k * k * a[i];
		}
		return 1;
	}
	struct node{
		int val, bel, cnt;
	};
	bool operator < (node a, node b){
		return a.val > b.val;
	}
	priority_queue<node> q;
	int main(){
		scanf("%lld%lld", &n, &m);
		for(int i = 1;i <= n;i++){
			scanf("%lld", &a[i]);
		}
		//二分最高价格 
		int l = 0, r = 1e18, ans = 0;
		while(l <= r){
			int mid = l + r >> 1;
			if(check(mid)){
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		} 
		int sum = m, cnt = 0;
		for(int i = 1;i <= n;i++){
			int tmp = ans / a[i];
			int k = (tmp + 1) / 2;
			cnt += k;
			sum -= k * k * a[i];
			q.push((node){(2 * k + 1) * a[i], i, k + 1});
		}
		while(1){
			node tmp = q.top();
			q.pop();
			if(tmp.val > sum) break;
			cnt++;
			sum -= tmp.val;
			tmp.cnt++;
			tmp.val = a[tmp.bel] * (2 * tmp.cnt - 1);
			q.push(tmp);
		}
		printf("%lld", cnt);
		return 0;
	}
} 
signed main(){
	return Luo_ty::main();
}//International Milan is the best team.
```

---

## 作者：Lucyna_Kushinada (赞：1)

不开 `__int128` 很容易寄，最后计算答案的细节也很恶心。

我们可以把第 $i$ 种商品价格拆成 $p_i,3p_i,5p_i,7p_i\dots$。以此类推下去，发现购买前 $k$ 个的价格正好是题目的 $k^2p_i$，而第 $k$ 个的价格是 $(2k-1)p_i$，且购买它必须先买前 $(k-1)$ 个。

一个较为显然的策略就是每次买当前局面价格最便宜的商品，因为每个商品对答案的贡献都是 $1$，且我们买完某一个商品之后它只会变得更贵，我们继续买它还不如买其它更便宜的，因此这个贪心策略是非常正确的。

这似乎是个多路归并贪心问题，不过由于值域太大，会超时，我们要考虑其他方法。

我们设定一个值 $v$，对于每个商品，一直购买它，直到它的价格大于 $v$ 才收手，这不仅满足了贪心策略，也使得我们能够使用一种方法，二分。

我们考虑二分 $v$，对于物品 $i$，显然它能够购买 $\lfloor \frac{v+p_i}{2p_i} \rfloor$ 件，花费就是 $\lfloor\frac{v+p_i}{2p_i}\rfloor^2 p_i$，接着我们把所有物品的花费加起来，判断是否大于 $m$ 即可。

我们二分出最优的 $v$ 之后，对于每个物品计算出它购买的件数，累加到答案里。

需要注意的细节是，此时还不能输出，因为我们剩下的钱还可能再买几件商品，不过件数不会超过 $n$，不然此时的 $v$ 就不是最优的，既然最多买 $n$ 件，我们不妨跑一个多路归并贪心，直到买不了任何物品，此时的答案才是正确的。

丑陋的代码实现。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define tp tuple<int,int,int>
#define id(x) get<2>(x)
#define num(x) get<1>(x)
#define cost(x) get<0>(x)
#define fi first
#define se second
#define pb push_back

#define int __int128
#define N 214514

int n,m,a[N];

inline int calc(int k){
    int ans=0;

    rep(i,1,n){
        int cnt=(k+a[i])/(2*a[i]);
        
        cnt*=cnt;

        if(cnt>2e18){
            return 2e18;
        }

        cnt*=a[i];

        if(cnt>2e18){
            return 2e18;
        }

        ans+=cnt;

        if(ans>2e18){
            return 2e18;
        }
    }

    return ans;
}

priority_queue<tp>q;

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    long long x;

    cin>>x;
    n=x;

    cin>>x;
    m=x;

    rep(i,1,n){
        cin>>x;
        a[i]=x;
    }

    int l=0,r=m,mid,st=0;
    
    while(l<=r){
        mid=(l+r)>>1;

        int res=calc(mid);

        if(res<=m){
            st=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }

    int ans=0;

    rep(i,1,n){
        int t=(st+a[i])/(a[i]*2);

        ans+=t;

        m-=t*t*a[i];

        q.push({-(2*t+1)*a[i],t+1,i});
    }

    while(m){
        tp u=q.top();
        q.pop();

        if(m<-cost(u)){
            // cout<<m<<' '<<-cost(u)<<"\n";
            break;
        }

        ans++;
        m+=cost(u);

        int t=num(u),i=id(u);

        q.push({-(2*t+1)*a[i],t+1,i});
    }

    cout<<(long long)ans;

    return 0;
}
```

---

## 作者：_ayaka_ (赞：1)

### 思路

将买第 $i$ 个物品 $k_i$ 次需花费 $p_i\times k_i^2$ 块钱转化为买第 $i$ 个物品第 $k_i$ 次需要花费 $p_i\times (2\times k_i-1)$ 块钱。证明一下为什么这是正确的。

考虑第 $k_i$ 个物品在什么时候会被买。显然，它是最便宜的一个的时候。而如果第 $k_i$ 个物品是最便宜的，那么它前面的 $k_i-1$ 个物品，$k_i-2$ 个物品之类，肯定已经被买下。毕竟它们肯定会比第 $k_i$ 个更便宜嘛。所以，即使被拆开，购买一种物品 $k_i$ 次也肯定是购买前 $k_i$ 个。

然后，我们就相当于获得了很多个物品，只要每一次都取最小的就好了。但是，假如每个物品价格都为 $1$，那相当于我们要取 $M$ 次，每一次还要维护最小的物品，肯定超时。考虑优化。

总价格小于 $M$，要尽可能取得多，其实有做题经验就已经知道这里会使用二分了。二分的东西是能取到的物品的最大价格 $M_w$，每一次二分后统计答案，看能否将所有价格小于等于 $M_w$ 的物品全部拿下，不行就往下走，可以就往上走，最后统计答案就可以了。注意，第 $i$ 个物品取到第几次才会大于 $M_w$ 这个问题是可以 $O(1)$ 求解的，因为有公式，做一下除法就可以了。

最后时间复杂度 $O(n\log m)$。

初生题目需要注意范围溢出，要开 `__int128` 和 `long double`，这里就不附代码了。

---

## 作者：Tairitempest (赞：1)

## [ABC389E] Square Price
#### $O(\sqrt{m}\log n)$ 做法
根据表达式得到第 $k$ 次选择第 $i$ 个物品的代价是 $(2k-1)p_i$。因此可以用优先队列存储增加某个物品的代价，贪心选择物品。

但是时间复杂度太高了，过不了。
#### $O(n\log m)$ 做法
我们再看一看上面的过程，我们发现当上面这个过程的增加物品的代价存在某个上限。当我们知道这个上限的时候，根据上面的式子，每个物品可以购买的数量就可以快速计算出来。这时我们可以快速得出物品的总数以及物品总计花的价钱了。因此我们考虑对价格上限进行**二分答案**。

但是还要打个两个补丁：

- 我们进行二分答案的时候，可能会存在一些价格相同，但价钱只能让你选择其中一部分的情况，这种时候要记录所有进一步增加物品的代价中代价最小的那些物品并进行手动的添加。
- 对于超级大的 $m$，部分时候要使用 int128 来存储，然而有些时候数字大了还是会溢出。所以对于这种情况，我们每次添加的时候特判一下，如果这一次加上去大于 $m$，就直接赋值为 $m+1$，这样就能够保护它不溢出。（这里最好将 $p_i$ 除过去防止溢出，另外防止错判，可以放宽一点限制。损失的精度不要紧，只要让它不溢出就可以了就行）
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,p[200010],maxk,resk;
__int128 res,k[200010];
void check(ll maxprice){
	ll minprice=1e18,minnum=0;
	res=resk=0;
	memset(k,0,sizeof k);
	for(int i=1;i<=n;i++){
		k[i]=(maxprice+p[i])/(2*p[i]);
		resk+=k[i];
		if(k[i]*k[i]>(m-res+p[i])/p[i])
			res=m+1;
		else res+=k[i]*k[i]*p[i];
		if((2*k[i]+1)*p[i]<minprice){
			minprice=(2*k[i]+1)*p[i];minnum=1;
		}else if((2*k[i]+1)*p[i]==minprice) minnum++;
	}
	while(res+minprice<=m&&minnum--){
		res+=minprice;
		resk++;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>p[i];
	ll l=1,r=m;
	while(l<r){
		ll mid=(l+r)/2;
		check(mid);
		if(res>m) r=mid;
		else{
			maxk=max(maxk,resk);
			l=mid+1;
		}
	}
	cout<<maxk<<endl;
	return 0;
}
```

---

## 作者：Otue (赞：1)

可以将此题第 $i$ 个物品的看成有无限个形如 $P,3P,5P,7P,\dots$ 的物品。即将 $k^2$ 拆分为 $\sum _{i=1}^k (2i-1)$。

那么有个正确性显然的贪心是：从价值最小的物品开始选择，直到选满 $M$ 的背包为止。可以注意到：选了价值为 $x+1$ 的物品，那么价值为 $x$ 的物品则为必选。数据范围不允许把所有物品列出来排序，但是可以进行二分。

我们二分选出 **完整物品** 的价值最大值 $mid$。**完整物品** 的定义为：此价值的物品全选。

那么把所有价值小于等于 $mid$ 的物品计入答案，如果最终成本小于等于 $M$，那么就满足条件。

设最终二分出的值为 $L$。考虑到，我们还可能会选择一些价值等于 $L+1$ 的不完整物品，那么将这些物品额外计入即可。如何保证 $L+1$ 的不完整物品一定存在？因为如果不存在，二分的 $L$ 至少会变为 $L+1$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int __int128
const int N = 3e5 + 5;

int n, m, a[N], cnt, res;

int read() {
	char c = ' ';
	int f = 1, x = 0;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x;
}

void wr(int x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) wr(x / 10);
	putchar(x % 10 + '0');
}

int check(int x) {
	res = 0; cnt = 0;
	_for(i, 1, n) {
		int t = x / a[i];
		if (t == 0) continue;
		if (t % 2 == 0) t--;
		cnt += t / 2 + 1; res += (t / 2 + 1) * (t / 2 + 1) * a[i];
		if (res > m) return 0;
	}
	return res <= m;
}

signed main() {
	n = read(), m = read();
	_for(i, 1, n) a[i] = read();
	int L = 0, R = 1e18;
	while (L < R) {
		int mid = (L + R + 1) >> 1;
		if (check(mid)) L = mid;
		else R = mid - 1;
	}
	check(L);
	wr(cnt + (m - res) / (L + 1));
}
```

---

## 作者：lam_dyr (赞：1)

由题可知，
- 对于每种商品 $i$，购买 $k$ 件商品的总费用为 $k^2 \times P_i$。
- 购买 $j$ 件商品的费用遵循公式：$w = \sum_{i=1}^j (2i-1) \times P_i$。
- 累加 $j$ 件商品的费用为 $\sum_{i=1}^j (2i-1) = j^2$。

因此，我们可以列出一个**价格表**，包含所有产品的单件价格并从小到大排列。此时我们只要从最便宜的物品开始购买，直到总花费超过 $M$。事实上，这个价格表是虚拟的，因为每种物品近似无限个。

我们注意到一个关键性质，存在一个价格 $x$，使得我们可以购买所有价格小于等于 $x$ 的物品，以及部分价格为 $x+1$ 的物品。这个 $x$ 是一个关键的分割点，我们可以通过二分查找来找到它。

找到这个 $x$ 后，我们也就找到了可购买物品的最大数量。注意开 `long long`。

---

## 作者：Drifty (赞：1)

### Solution

不难题。

考虑如何暴力的去做这个问题，实际上这个问题等价于于去花费 $(2k + 1)p_i$ 的代价来购买一个物品。显然，我们可以直接对这个价值排序，贪心地做。

但这样有点慢，我们考虑二分出我们所取的最贵的物品，然后容易计算出总和，然后就做完了。

---

## 作者：Dtw_ (赞：0)

# Solution
观察到 $M$ 是 $10^{18}$ 级别的，所以背包啥的肯定不行，所以自然想到贪心。

考虑新选 $1$ 个的代价：即 $(k + 1)^2p - k^2p = (2k - 1)p$。

然后就接着出现了一个思路，就是对于每个物品，我先选 $1$ 个，然后选完 $1$ 轮之后我再回来继续选。当然 $p$ 是不同的，所以肯定不能直接这样选，但这启发我们应该先把所有小的都选完了，然后才去选大的。

那么现在问题在于如何判断他是小的还是大的？既然判断不了那么我们可以枚举，枚举一个 $x$ 我们对于每件物品都选 $k_i$ 件，使得 $(k_i)^2p_i \leq x$ 那么如果还有剩余的我们再去选后面的。

注意到这个 $x$ 有单调性，所以可以二分 $x$，现在复杂度为 $O(n\log m)$ 可以通过。

我 wa 了几发，原因是爆 `long long` 了，改成 `__int128` 好像也不行，所以就直接看了[这篇](https://www.luogu.com.cn/article/f7zu5fev)。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 2e5 + 10, inf = 0x3f3f3f3f3f3f3f3f;

int n, m, p[N];

bool check(int x)
{
    int cur = 0;
    for (int i = 1; i <= n; i++)
    {
        int k = (x + p[i]) / (2 * p[i]);
        if (k >= 1e9 || k * k >= inf || inf / p[i] < k * k) return false;
        cur += k * k * p[i];
        if (cur > m) return false;
    }
    return true;
}

signed main()
{
    fst
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> p[i];
    int l = 0, r = m, t = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid + 1, t = mid;
        else r = mid - 1;
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        int k = (t + p[i]) / (2 * p[i]);
        res += k;
        m -= k * k * p[i];
    }
    res += m / (t + 1); // 剩下的再选价值为 (t + 1) 的，直接除是因为 t 一定最大，(t + 1) 一定选不完
    cout << res;
    return 0;
}
```

---

## 作者：Laisira (赞：0)

化一下式子就是 $j^2 = \sum_{i=1}^{j}(2\times i-1)$。

每选择一个额外数的代价被拆开了，显然贪心的选择代价最小的，暴力模拟是会 TLE。

不难发现大多取数代价都是小于等于一个数 $W$ 的，注意是大多。

然后就可以二分一个值 $W$，然后再贪一遍把零碎的贡献加上，时间复杂度 $O(n\log M +n\log n)$。

再说一下大多代价都是小于等于一个数 $W$ 的，由于每个数的贡献小于等于 $1$，所以选择最小数一定不劣。

---

