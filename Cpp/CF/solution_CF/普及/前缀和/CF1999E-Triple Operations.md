# Triple Operations

## 题目描述

**题面描述**

Ivy 在黑板上写下了在 $l$ 到 $r$ 之间的所有整数。

在一次运算中，她做了以下操作：

- 在黑板上选出任意两个数字 $x$ 和 $y$ ，将它们擦掉，然后在它们的位置上写下数字 $3x$ 和 $\lfloor \frac{y}{3} \rfloor$ 。(这里的 $\lfloor x\rfloor$ 表示取整，即四舍五入到最接近的整数）。

要使黑板上的所有数字都等于 $0$ ，Ivy 最少需要进行多少次运算？可以证明一定有解。

## 样例 #1

### 输入

```
4
1 3
2 4
199999 200000
19 84```

### 输出

```
5
6
36
263```

# 题解

## 作者：fishing_cat (赞：7)

[原题](https://codeforces.com/problemset/problem/1999/E)
### 分析
一共有两种操作，将一个数 $x$ 变为 $3x$ 和将一个数 $y$ 变为 $\lfloor \frac{y}{3} \rfloor $。而对于将所有数都变为 $0$ 的要求，将一个数 $x$ 变为 $3x$ 操作是不优的。

所以为了消除后面操作的副作用，考虑先将 $l$ 操作成 $0$，在之后的操作中，就将 $3x$ 操作一直对于 $0$ 生效，使不优的操作尽可能少，就保证了操作数最小。

记 $f(a)$ 是将数 $a$ 操作成 $0$ 的操作次数，根据上面的分析，最小方案数就是 $2f(l) + f(l+1) + \dots + f(r)$，直接暴力一定是会 TLE 的，考虑先预处理所有的 $f(a)$，并用前缀和优化。

记 $qzh(a)$ 为 $f(1)$ 到 $f(a)$ 都操作成 $0$ 的总操作次数，那最后的答案为 $f(l) + qzh(r) - qzh(l-1)$。

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void read(ll &x){ // 快读
	x = 0;
	char c = getchar();
	ll f = 0;
	for(;!isdigit(c);c = getchar())
		f |= c == '-';
	for(;isdigit(c);c = getchar())
		x = x*10 + (c ^ '0');
	if(f) x = -x; 
}
ll t,l,r,a[200014],qzh[200014];
ll work(ll x){
  // 求将数 x 操作成 0 的操作次数
	ll cnt = 0;
	while(x){
		x /= 3;
		cnt++;
	}
	return cnt;
}
int main(){
	read(t);
	for(int i=1;i<=200000;i++){
      // 预处理
		a[i] = work(i);
		qzh[i] = qzh[i-1] + a[i];
	}
	while(t--){
		read(l); read(r);
		ll ans = 0;
		ans += a[l];
		ans += qzh[r] - qzh[l-1];
		cout << ans << "\n";
	}
	return 0;
}
```
完结撒花！！！

---

## 作者：Pink_Cut_Tree (赞：6)

# CF1999E Triple Operations 题解

[Luogu Link](https://www.luogu.com.cn/problem/CF1999E)|[CF Link](https://codeforces.com/contest/1999/problem/E)|[My AC submission](https://codeforces.com/contest/1999/submission/274874768)。

需要一定的码力，即代码实现能力。

### 解析

很好想思路，将 $l$ 经过一通操作变为 $0$，然后之后每次操作将 $0$ 乘 $3$，另一个数除以 $3$ 下取整即可。

在线算法不太好想，其实可以考虑离线。预处理 $1\sim 2\times 10^5$ 每个数需要操作的次数然后做前缀和。记数 $i$ 需要操作的次数是 $f(i)$。最后答案就是 $\sum_{i=l}^{r} f(i) +f(l)$。为什么 $f(l)$ 要加两遍呢？因为你在将 $l$ 变成 $0$ 的过程中，另外一个数乘了 $F(l)$ 次，你需要将其除回去。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int T;
int l,r;
int ans[N];
int find(int x){
	int cnt=0;
	while(x){
		x/=3; cnt++;
	}
return cnt;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	for(int i=1;i<=2e5;i++){
		ans[i]=ans[i-1]+find(i); //做前缀和
	}
	cin>>T;
	while(T--){
		cin>>l>>r;
		int cnt=find(l);
		cnt<<=1;
		cout<<cnt+ans[r]-ans[l]<<"\n";
	}
return 0;
}
```

---

## 作者：PineappleSummer (赞：5)

[CF1999E Triple Operations](https://www.luogu.com.cn/problem/CF1999E)

简单题。当你没有看到 $\sum$ 的限制时应该想到需要预处理。

考虑这样一个策略：假如需要让区间 $[l,r]$ 全部变为 $0$，可以先让 $l$ 变为 $0$，然后依次消去后面的数。对于 $l+1\sim r$ 的每一个数 $i$，可以让 $l$ 乘 $3$，$i$ 除以 $3$。由于 $l$ 已经变为 $0$，消去 $l+1\sim r$ 这些数的总次数便为 $\sum\limits_{i=l+1}^r \left\lceil\log_3 i\right\rceil $。由于消去 $l$ 需要 $\log_3l$ 次，但是某一个数又乘上了 $l$，所以总次数为 $\log_3l\times 2+\sum\limits_{i=l+1}^r \left\lceil\log_3 i\right\rceil=\log_3l+\sum\limits_{i=l}^r \left\lceil\log_3 i\right\rceil$。

可以证明先消去 $l$ 一定是最优的。

预处理 $\log_3$ 的前缀和即可。

预处理时间复杂度 $\mathcal O(n)$，单次回答时间复杂度 $\mathcal O(1)$。

```cpp
void solve () {
	cin >> l >> r;
	cout << (sum[r] - sum[l - 1]) + a[l] << '\n';
}
void Pre () {
	int maxn = 2e5 + 10;
	for (int i = 1; i <= maxn; i++) {
		a[i] = a[i / 3] + 1;
		sum[i] = sum[i - 1] + a[i];
	}
}
```

---

## 作者：stils (赞：3)

## 题目大意

给出 $l$ 到 $r$ 之间的整数，每次操作可以选择两个数 $x$ 与 $y$，使 $x$ 改为 $3x$，$y$ 改为 $\lfloor \frac{y}{3} \rfloor$，问多少次操作可以让所有数都为 $0$ 且操作数最少。

## 解题思路

我们将乘法称为操作 $1$，除法称为操作 $2$，一次操作包括操作 $1$ 和操作 $2$。初看时像动态规划，但数据范围不行，于是模拟一下给的提示，可以发现在有一个数为 $0$ 的情况下剩下的操作只需要注意操作 $2$ 就可以了，因为操作 $1$ 可以在 $0$ 上使用。所以我们写一个函数，用来计算该数字要多少次操作 $2$ 后为 $0$。

```cpp
int to0(int x){//返回次数 
	int arr=x,res=0;
	while(arr){
		double drr=arr*1.0;
		drr/=3.0;
		//arr=round(drr);//这里是因为比赛时翻译软件翻译的四舍五入...坑我半天。
		arr=floor(drr);
		res++;
	}
	return res;
}
```

那么多少次操作后有一个数会到达 $0$ 呢？为了最少，我们显然需要将 $l$ 进行操作 $2$，$l+1$ 进行操作 $1$，这样显然是最优的。剩下的数只需要将答案加上操作 $2$ 到 $0$ 的次数即可。

由于 $l+2$ 已经进行了若干次操作 $1$，我们在计算操作 $2$ 到 $0$ 的次数时可以直接加上操作 $1$ 的次数，然后加上原本需要的次数。

所以答案可以归纳成全部数字需要的次数与 $l$ 需要的次数之和。

有多组询问，所以可以预处理。对每个数进行操作 $2$ 到 $0$ 的次数都较小可以忽略，时间复杂度 $O(Tn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int T,ans;
int to0(int x){
	int arr=x,res=0;
	while(arr){
		double drr=arr*1.0;
		drr/=3.0;
		arr=floor(drr);
		res++;
	}
	return res;
}
int to[N];
int main(){
	cin>>T;
	for(int i=1;i<=200000;i++)to[i]=to0(i);//这里可以递推，然而麻烦
	while(T--){
		ans=0;
		int l,r;
		cin>>l>>r;
		for(int i=l;i<=r;i++)ans+=to[i];
		ans+=to[l];
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：ICU152_lowa_IS8 (赞：1)

简单题。

首先我们搞出一个 $0$，然后给所有的乘 $3$ 操作全部丢给这个 $0$，证明如下：

首先这个数字是一定要归 $0$ 的且在无其它乘 $3$ 操作的情况下次数不变，故归 $0$ 这个操作本身不劣。

然后，对于乘 $3$ 操作：

如果对 $0$ 进行操作，最终答案不变（显然）。

如果对非 $0$ 进行操作，最终答案加 $1$。

显然对 $0$ 操作更优。

其它的数全部弄完了，再来看这个被归 $0$ 的数：

显然对这个数操作的次数为 $\lceil\log_{3}x\rceil$，另外一个数（任意）的操作次数也会增加 $\lceil\log_{3}x\rceil$。

要使这个增加的值最小，显然最开始被归 $0$ 的数也要最小。

那么该题便转化为了求这个式子：

$$(\sum_{i=l}^{r} \lceil\log_{3}i\rceil)+\lceil\log_{3}l\rceil$$

前面那个求和符号内的式子可以用前缀和预处理将询问查询复杂度降低至常数级别。

代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool check(int c,int t){
	for(int i=1;i<=t;i++){
		c/=3;
		if(c==0)break;
	}
	return c==0;
}
int cal(int x){
	if(x==0)return 0;
	int l=1,r=20,mid,ans=1;
	while(l<=r){
		mid=l+r>>1;
		if(check(x,mid)){
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	return ans;
}
int s[1000005];
signed main(){
	int t;
	cin>>t;
	for(int i=1;i<=200005;i++){
		s[i]=cal(i);
		s[i]+=s[i-1];
	}
	while(t--){
		int l,r;
		cin>>l>>r;
		cout<<s[r]-s[l-1]+cal(l)<<endl;
	}
	return 0;
}

```

---

## 作者：_O_v_O_ (赞：1)

[点此查看这个蒟蒻写的该场比赛所有题目的题解](https://www.luogu.com.cn/article/opat7vrj)

我们注意到，我们一定就要先把一个数变为 $0$ 再进行后续操作，那么我们就先选定 $l$ 把他变成 $0$，可是这样对别的数额外会产生 $\lfloor \log_3(l) \rfloor$ 此操作，再加上本身就要做  $\sum_{i=l}^r \lfloor \log_3(i) \rfloor$ 次操作，所以答案为 $\sum_{i=l}^r \lfloor \log_3(i) \rfloor+\lfloor \log_3(l) \rfloor$，用前缀和预处理一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int T;
int l,r;
int ans[N];

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=1;i<=200000;i++){
		for(int j=i;j;j/=3){
			ans[i]++;
		}
		ans[i]+=ans[i-1];
	}
	cin>>T;
	while(T--){
		cin>>l>>r;
		cout<<ans[r]-ans[l]+2*(ans[l]-ans[l-1])<<endl;
	}
	return 0;
}
```

---

## 作者：Archy_ (赞：1)

## 题目翻译
有一 $l \sim r$ 的序列，包括 $l$，$r$。其中选 $x$，$y$ 两个数，将 $x \gets 3x$，$y \gets  \lfloor \frac{y}{3} \rfloor $，记为一次操作。

问，多少操作后可以将序列所有数改为 $0$。
## 题目思路

记 $f(x)$ 为将 $x$ 变为 $0$ 所需的操作数。我们首先考虑将序列中一个数改为 $0$，然后再用这个 $0$ 与序列其他数进行操作。

为什么要这样，因为 $0$ 乘任何数还是 $0$，我们就可以只考虑除了。

首先将序列中任意一个数 $y$ 改为 $0$，由于序列还没有 $0$，它将会对答案产生 $2f(y)$ 的贡献，因为将其他数复原所需的操作数是一样的。假如我们将 $l$ 进行第一次操作，之后，所有数的贡献为 $\sum_{x=l+1}^{r} f(x)$。

很明显，这样的时间复杂度是 $O(q n\log n)$，会超时。所以我们考虑用前缀和数组进行预处理，然后 $O(1)$ 查询即可，时间复杂度是 $O(\sum_{x = 1}^{200000} \log x + q)$。
## Code
```cpp
#include <iostream>
using namespace std;
long long q, l, r, sum[200005];
inline int f(int x) {
	int cnt = 0;
	while(x > 0){
		x /= 3;
		cnt ++;
	}
	return cnt;
} 
int main() {
	cin.tie(0) -> ios::sync_with_stdio(0);
	cin >> q;
	for(int i = 1; i <= 200000; i++) {
		sum[i] = sum[i - 1] + f(i);
	}
	while(q--) {
		cin >> l >> r;
		cout << sum[r] - sum[l - 1] + f(l) << "\n";
	}
	return 0;
} 
```

---

## 作者：So_noSlack (赞：1)

## 题目简述

有 $T$ 组数据，每组数据给出 $l, r$。

你需要对 $[l, r]$ 区间内的数进行以下操作：

- 选择两个数 $x, y$，将这两个数替换为 $3x, \left \lfloor \frac{y}{3} \right \rfloor$。

求操作到 $[l, r]$ 中的数都变为 $0$ 的最小操作次数。

注意：多组数据之间不影响，每组数据是独立的。

## 思路

考虑到每次选择的数都不为 $0$ 的话，不妨设这两个数为 $x, y$，那么要将 $x, y$ 都变为 $0$ 需要 $\left \lceil \log_3 x \right \rceil \times 2  + \left \lceil \log_3 y \right \rceil$ 次（假设先让 $x$ 变为 $0$），因为每次对 $x$ 做除以三的操作时，都会使 $y$ 乘三即多消耗一次操作。

那么考虑贪心思想，当一个数变为 $0$ 之后，对于另一个非零数 $x$，只需要 $\left \lceil \log_3 x \right \rceil$ 次就可以变为 $0$。

可以看到，只有第一次操作需要多耗费操作，所以我们先将最小的数 $l$ 变为 $0$，需要 $\left \lceil \log_3 l \right \rceil \times 2$ 次操作。

对于 $(l + 1) \sim r$ 中的数 $i$，只需要耗费 $\left \lceil \log_3 i \right \rceil$ 次操作即可。

不过到这里还没完，注意到这道题的数据较大，所以需要预处理 $log$ 数组和 $log$ 数组的前缀和。

对于一次操作 $l, r$，只需输出 $log_l + p_r - p_{l - 1}$ 其中 $p$ 为前缀和数组。

代码如下：


```cpp
#include<iostream>
using namespace std;
#define MAXN 200005

long long read() {
	long long x = 0, f = 1; char ch = getchar();
	while(ch < 48 || ch > 57) { if(ch == 45) f = -1; ch = getchar(); }
	while(ch >= 48 && ch <= 57) { x = (x << 3) + (x << 1) + (ch - 48); ch = getchar(); }
	return x * f;
}

long long T, l, r, log[MAXN], p[MAXN];

int main() {
	T = read();
	for(int i = 1; i <= 200000; i ++) log[i] = log[i / 3] + 1, p[i] = p[i - 1] + log[i];
	while(T --) {
		l = read(); r = read();
		cout << log[l] + p[r] - p[l - 1] << "\n";
	}
	return 0;
}
```

[$\text{Submission}$](https://codeforces.com/contest/1999/submission/274885092)

---

## 作者：Heldivis (赞：1)

## CF1999E Triple Operations

记 $f(y)$ 为通过 $y\gets\lfloor\dfrac y3\rfloor$ 操作变为整数的次数

考虑一次操作，分 $x$ 是否为零两类讨论：

- $x\not=0$，那么为了通过 $y\gets\lfloor\dfrac y3\rfloor$ 变为整数的代价为 $2f(y)$。因为还需要同样次数的操作将 $x$ 还原。
- $x=0$ 那么 $x\gets3x$ 这一步骤不耗费任何代价。通过 $y\gets\lfloor\dfrac y3\rfloor$ 变为整数的代价为 $f(y)$。

所以，最小办法是尽快制造一个 $0$，然后让其他数作为  $y$ 和 $x=0$ 操作。

显然，先令 $l$ 变为 $0$ 一定不劣，之后再让 $l+1\sim r$ 的数和这个 $0$ 操作，答案即为 $2f(l) + \sum\limits_{i=l+1}^{r}$，预处理 $f(i)$，前缀和优化即可。

代码：

```cpp
int Calc(int x) {
  int cnt = 0;
  while (x) ++cnt, x /= 3;
  return cnt;
}

void Main() {
  int l = read(), r = read();
  printf("%lld\n", s[r] - s[l - 1] + f[l]);
}

signed main() {
#ifdef HELDIVIS
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif
  for (int i = 1; i <= n; ++i) f[i] = Calc(i), s[i] = s[i - 1] + f[i];
  for (int T = read(); T--; Main());
  return 0;
}
```

---

## 作者：wmrqwq (赞：1)

需要我教你怎么 AK div.4 吗？

# 题目链接

[CF1999E](https://www.luogu.com.cn/problem/CF1999E)

# 解题思路

我们发现，我们是一定要先把一个数字变为 $0$ 才能完成将所有数字变为 $0$ 的操作的。

因此不难看出，我们肯定是需要把最小的那个数字变成 $0$ 的。

序列中有一个 $0$ 之后，我们之后肯定是把乘三操作都丢给这个 $0$，除以三操作肯定是给不为零的数字，这部分我们可以直接预处理 $sum_i$ 表示 $\displaystyle\sum_{i=1}^{n} \left\lceil \dfrac{i}{3} \right\rceil$，预处理后可以实现 $O(1)$ 时间复杂度查询。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
ll l,r;
ll sum[200010];
ll f(ll x)
{
	ll sum=0;
	while(x)
		sum++,x/=3;
	return sum;
}
void init(){
	forl(i,1,2e5+5)
		sum[i]=f(i)+sum[i-1];
}
void solve()
{
	_clear();
	cin>>l>>r;
	cout<<sum[r]-sum[l-1]+sum[l]-sum[l-1]<<endl;	
}
int main()
{
	init();
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：donnieguo (赞：0)

## 思路

记 $f(y)$ 为使用 $y = \lfloor\frac{y}{3}\rfloor$ 操作使 $y$ 变成 $0$ 的次数，即 $f(y) = \lceil \log_3y \rceil$。

要使 $l \sim r$ 全部变成 $0$，可以考虑如下策略：

先把一个数变成 $0$，然后每次都把乘 $3$ 的操作给这个数，除以 $3$ 的操作给其他的数，这样是最优的。

显然，那一个最开始变成 $0$ 的数就是 $l$。

将 $l$ 变成 $0$ 之后，将 $l + 1 \sim r$ 变成 $0$ 的次数为 $\sum\limits^r_{i = l + 1}f(i)$。

这里注意一个细节：答案并不是 $f(l) + \sum\limits^r_{i = l + 1}f(i)$。因为虽然把 $l$ 变成 $0$ 要 $f(l)$ 次，但是同时你也把另一个数乘上了 $3^{f(l)}$，这也就意味着你在把这个数变成 $0$ 的时候需要多用 $f(l)$ 次。

也就是说，答案应该是 

$$2 \times f(l) + \sum\limits^r_{i = l + 1}f(i)$$

但是直接求会 TLE。转化一下这个式子，变成

$$f(l) + \sum\limits^r_{i = l}f(i)$$

看到 $\sum\limits^r_{i = l}f(i)$，自然想到前缀和优化。

于是 code 就出来了。

## AC code

```cpp
#include <iostream>
#define N 200010
using namespace std;

int T, l, r;
int f[N], s[N];

int pre(int x)
{
	int cnt = 0;
	while (x)
	{
		cnt++;
		x /= 3;
	}
	return cnt;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	for (int i = 1; i <= N - 10; i++) f[i] = pre(i), s[i] = s[i - 1] + f[i];
	cin >> T;
	while (T--)
	{
		cin >> l >> r;
		cout << s[r] - s[l - 1] + f[l] << '\n';
	}
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
首先，我们先将 $l$ 变为 $0$，因为 $l$ 是最小的，这样耗费的操作次数就是 $\lceil \log_3 l \rceil$ 次。接下来，我们将 $l+1 \sim r$ 的所有数都变为 $0$，将所有的乘 $3$ 操作都给 $l$，所以将这些数变为 $0$ 所需要的操作次数为 $\sum_{i=l+1}^{r} \lceil \log_3 i \rceil$。但是，由于第一次将 $l$ 变为 $0$ 的时候，当前没有一个数是 $0$，所以有一个数被乘了 $\lceil \log_3 l \rceil$ 个 $3$，所以还要加上 $\lceil \log_3 l\rceil$。

最终的答案就是 $\lceil \log_3 l \rceil \times 2 + \sum_{i=l+1}^{r} \lceil \log_3 i \rceil$。转变一下，就是 $\lceil \log_3 l \rceil + \sum_{i=l}^{r} \lceil \log_3 i \rceil$。可以预处理 $1 \sim 2 \times 10^5$ 中每个数以 $3$ 为底的对数。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200005;
int pre[N];
int log_3(int x){
    int ans(0);
    while(x)ans++,x/=3;
    return ans;
}
void calc(){
    for(int i=1;i<N;i++)
    pre[i]=log_3(i)+pre[i-1];
}
void solve(int T){
    if(!T)return;
    int l,r;
    cin>>l>>r;
    cout<<pre[r]-pre[l-1]+log_3(l)<<"\n";
    solve(T-1);
}   
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int T;
    cin>>T;
    calc();
    solve(T);
}
```

---

## 作者：block_in_mc (赞：0)

## 题目大意

有 $l\sim r$ 共 $r-l+1$ 个数，你每次可以选择两个数 $x,y$，将 $x$ 改为 $3x$，将 $y$ 改为 $\lfloor\dfrac{y}{3}\rfloor$，求你最少需要几次操作才能将所有数变为 $0$。

## 解题思路

首先观察样例解释，发现：样例首先把一个数变为 $0$，再每次将 $0$ 乘以 $3$，其他数除以 $3$ 直到所有数都为 $0$。

先把一个数变为 $0$ 的想法是显然的，如果 $x\not=0$，乘以 $3$ 的数最后还要再除回来，事实上对将所有数变为 $0$ 没有贡献。

考虑将哪一个数首先变为 $0$，对于这个数 $a$，不妨将对其的一次操作视为两次操作，且其他数不改变，因为对其他数的乘 $3$ 操作最后还要除回来。因此，$a$ 应该是最小的那个数，即 $l$。

因此，答案即为 $2\lfloor\log_3l\rfloor+\sum\limits_{i=l+1}^r\lfloor\log_3i\rfloor$，我们可以通过递推式 $\log_3i=1+\log_3\lfloor\dfrac{i}{3}\rfloor$ 预处理出 $\log_3i$ 的值，再求其前缀和 $sum$，答案即为 $sum_r+sum_l-2sum_{l-1}$。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, l, r, lg[200010];
int main() {
    for(int i = 1; i <= 200000; i++) lg[i] = lg[i / 3] + 1;
    for(int i = 1; i <= 200000; i++) lg[i] += lg[i - 1];
    cin >> t;
    while (t--) {
        cin >> l >> r;
        cout << lg[r] + lg[l] - 2 * lg[l - 1] << endl;
    }
    return 0;
}
```

---

## 作者：wwwidk1234 (赞：0)

考虑贪心。先对 $l$ 和 $l+1$ 进行操作，把 $l$ 反复除以 $3$ 变成 $0$，让 $l+1$ 反复乘以 $3$。之后就可以让 $l$ 反复乘以 $3$，让其他数除以 $3$，就可以把数列全部变成 $0$ 了。

比如第二组数据：$l=2,r=4$：

- $\lfloor \frac{2}{3} \rfloor =0,3 \times 3 = 9$，原数列变成 $0,9,4$，进行了 $1$ 次操作。
- $\lfloor \frac{9}{3} \rfloor =3,0\times 3=0$，原数列变成 $0,3,4$，进行了 $2$ 次操作。
- $\lfloor \frac{3}{3} \rfloor =1,0\times 3=0$，原数列变成 $0,1,4$，进行了 $3$ 次操作。
- $\lfloor \frac{1}{3} \rfloor =0,0\times 3=0$，原数列变成 $0,0,4$，进行了 $4$ 次操作。
- $\lfloor \frac{4}{3} \rfloor =1,0\times 3=0$，原数列变成 $0,0,1$，进行了 $5$ 次操作。
- $\lfloor \frac{1}{3} \rfloor =0,0\times 3=0$，原数列变成 $0,0,0$，进行了 $6$ 次操作。

## 做法一

朴素版，定义 $d_x$ 为 $x$ 除以三向下取整多少次才能变成 $0$，进行 $d_l$ 次操作后，原数列变成 $0,(l+1) \times 3^{d_l},l+2,\cdots,r$，所以答案就是 $2d_l+ \sum_{i=l+1}^{r} d_i$。

代码：

```cpp
inline ll solve()
{
	int l,r,w;
	read(l,r);
	ll ans=0;
	w=l;
	do ans+=2; while(w/=3);
	for(int i=l+1;i<=r;i++)
	{
		int x=i;
		do ans++; while(x/=3);
	}
	return ans;
}
```

交上去发现超时了。

## 做法二

发现这个计算 $d_x$ 的 `do-while` 循环进行了很多次重复运算，所以考虑预处理。`do-while` 循环也可以用数学知识优化：由定义知：$\lfloor \dfrac{x}{3d_x} \rfloor=0$，所以有 $d_x=\log_3(x+1)$，因为 C++ 里没有 $\log_3$，所以要用换底公式。

发现 $\sum_{i=l+1}^{r} d_i$ 还可以用前缀和优化，设 $s=\sum_{i=1}^{n} d_i$，所以答案为 $2d_l+s_r-s_l$。单次询问 $O(1)$，预处理 $O(r)$，足以通过此题。

AC 代码：

```cpp
// Problem: Triple Operations
// Contest: Codeforces
// URL: https://m1.codeforces.com/contest/1999/problem/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=2e5+3;
int d[N],s[N];
inline ll div3(int x)
{
	int lg=ceil(log(x+1)/log(3));
	return lg;
}
inline ll solve()
{
	int l,r;
	cin>>l>>r;
	return d[l]*2ll+s[r]-s[l];
}
int main()
{
	for(int i=1;i<=N-3;i++) d[i]=div3(i);
	for(int i=1;i<=N-3;i++) s[i]=s[i-1]+d[i];
	int T;
	cin>>T;
	while(T--) cout<<solve()<<endl;
	return 0;
}
```

---

## 作者：yanlikun (赞：0)

# 思路
根据贪心，先对 $l$ 和 $l+1$ 进行操作，将 $l$ 变为 $0$，之后若干数都可与这一个零进行操作。易证得此思路易优。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int num[40],ans[200005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	num[0]=1;
	num[1]=3;
	for(int i=2;i<=32;i++)
		num[i]=num[i-1]*3;
	for(int i=1;i<=2e5;i++)
	{
		ans[i]=upper_bound(num,num+33,i)-num;//预处理出以3为底L到R的每一个数的对数
		ans[i]+=ans[i-1];//前缀和优化
	}
	while(t--)
	{
		int l,r;
		int sum=0;
		cin>>l>>r;
		sum+=2*(ans[l]-ans[l-1]);//先将L变为0，再将L+1乘上的若干个3消除
		sum+=(ans[l+1]-ans[l]);
		sum+=(ans[r]-ans[l+1]);
		cout<<sum<<"\n";
	}
	return 0;
}
```

---

## 作者：ka_da_Duck (赞：0)

[Triple Operations](https://www.luogu.com.cn/problem/CF1999E)
-

题意：

给定区间 $[l,r]$，每次操作在其中选两个数字 $x$ 和 $y$，将其分别变为 $x \times 3$ 和 $\lfloor \dfrac{y}{3} \rfloor$。求最少的操作数量使所有数字变成 $0$。

思路：

考虑贪心，先把最小的 $l$ 与 $l+1$ 操作 $\lfloor(\log_3l)\rfloor$ 次后变成 $0$，在重复执行一轮使得 $l+1$ 变回原来的数值。然后，我们将 $l(0)$ 与每个数字进行操作使其变为 $0$，总共做的操作数就是 $2\times \lfloor(\log_3l)\rfloor+ \sum_{i=l+1}^r \lfloor(\log_3i)\rfloor$，我们预处理出值域中每一个数字的 $\log_3$ 值，便可以 $O(1)$ 进行操作了。

```cpp
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
const int maxn = 2e5 + 10;
 
int l, r;
int lg[maxn], s[maxn];
 
int ccc(int x) {
	int res = 0;
	while (x) {
		x /= 3;
		res++;
	}
	return res;
}
 
int calc(int l, int r) {
	int res = 0;
	res += (lg[r] - lg[l - 1]);
	return res;
}
 
void solve() {
	cin >> l >> r;
	cout << (lg[l] - lg[l - 1]) * 2 + calc(l + 1, r) << '\n';
}
 
void init() {
	for (int i = 0; i < maxn; ++i) lg[i] = lg[i - 1] + ccc(i);
}
 
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	init();
	int t;
	cin >> t;
	//t = 1;
	while (t--) solve();
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

首先给出结论，令 $a(x)=\lfloor\log_3(x)\rfloor+1$，显然有 $x$ 经过 $a(x)$ 次 $x=\lfloor\frac{x}{3}\rfloor$ 操作后变为 $0$。那么一定有答案为 $\Sigma_{i=l}^ra(i)+a(l)$。

为什么呢？

首先，我们知道，当你将一个非零值乘三之后，你的操作次数必然至少会加一，因为你还得通过除以三的操作将他变小。

因此，我们肯定会先将一个数变为零，然后其他的数用这个数一直除以三。

这个数显然取最小的那个数。因为你会多做 $a(x)$ 次操作，$x=l$ 的时候这个值一定是 $[l,r]$ 中的最小值。

但是我们还有一个问题：快速求解 $\Sigma_{i=l}^ra(i)$。两种方法：可以全部计算，然后求前缀和。这种方法当然极其快，而且常数小。

可是我脑抽了，竟一时间没有想到，转而采用了另一种方式。类似于除法分块。我们把 $a(x)$ 值相同的 $x$ 放在一起。显然可也证明这是连续且单增的。分界点就是 $3^k$。

这种方法对应的代码如下，当然并不建议大家使用：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r,tri[15],pl,pr,ans;
int main(){
	ios::sync_with_stdio(0);
	cin>>t; tri[1]=1;
	for(int i=2;i<=14;++i) tri[i]=tri[i-1]*3;
	while(t--){
		cin>>l>>r;
		pl=upper_bound(tri+1,tri+15,l)-tri-1;
		pr=upper_bound(tri+1,tri+15,r)-tri-1;
		cerr<<pl<<" "<<pr<<endl;
		if(pl==pr){
			ans=(r-l+1)*pl;
			cout<<ans+pl<<endl;
			continue;
		}
		ans=(tri[pl+1]-l)*pl;
		ans+=(r-tri[pr]+1)*pr;
		for(int i=pl+1;i<pr;++i)
			ans+=(tri[i+1]-tri[i])*i;
		cout<<ans+pl<<endl;
	}
	return 0;
}
//私は猫です
```

---

