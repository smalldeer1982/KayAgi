# [ARC185B] +1 and -1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc185/tasks/arc185_b

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ があります。  
 あなたは次の操作を $ 0 $ 回以上好きな回数行うことが出来ます。

- $ 1\ \leq\ i\ \lt\ j\ \leq\ N $ を満たす整数対 $ (i,\ j) $ を選び、$ A_i $ を $ A_i\ +\ 1 $ に、$ A_j $ を $ A_j\ -\ 1 $ に置き換える。
 
操作によって $ A $ を広義単調増加な数列にすることが可能かどうか判定してください。

$ T $ 個のテストケースが与えられるので、それぞれに対して答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- 全てのテストケースに対する $ N $ の総和は $ 2\ \times\ 10^5 $ 以下
- 入力される値は全て整数
 
### Sample Explanation 1

$ 1 $ 番目のテストケースでは、次のように操作を行うことで $ A $ を広義単調増加な数列にすることが出来ます。 - $ (i,\ j) $ として $ (1,\ 2) $ を選ぶ。操作後の $ A $ は $ (2,\ 6,\ 5) $ になる。 - $ (i,\ j) $ として $ (1,\ 2) $ を選ぶ。操作後の $ A $ は $ (3,\ 5,\ 5) $ になる。 $ 2 $ 番目のテストケースでは、どのように操作しても $ A $ を広義単調増加な数列にすることは出来ません。

## 样例 #1

### 输入

```
3
3
1 7 5
2
9 0
10
607 495 419 894 610 636 465 331 925 724```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：Super_Cube (赞：4)

# Solution

无论如何操作，$s=\sum a_i$ 不变，那么最优构造即为前面一段为 $n-s\bmod n$ 个 $\left\lfloor\dfrac{s}{n}\right\rfloor$，后面一段为 $s\bmod n$ 个 $\left\lfloor\dfrac{s}{n}\right\rfloor+1$。

现在最终序列都定下来了，你说你还不会做？

设最优构造的序列为 $b$，$a$ 合法的情况为 $\displaystyle\min_{m=1}^n\sum_{i=1}^m b_i-a_i\ge0$，即对于任意的前缀都不会出现 $+1$ 比 $-1$ 少。

---

## 作者：Locix_Elaina_Celome (赞：2)

首先会发现一个很神妙的事情：如果现在有了一个合法的结果，那么一定可以继续操作使得整个序列的每个位置要么是 $\lfloor\bar a\rfloor$，要么是 $\lceil\bar a\rceil$ 且仍然保持单调。

所以我们就可以把问题转化为尝试构造这样的一个数组。我们设目标数组为 $g$。

先扔结论：如果 $\min\limits_{i=1}^n (\sum\limits_{j=i}^n a_j-g_j) > 0$，那么这个序列就是合法的。

因为当 $a_i>g_i$ 的时候，相当于这个位置需要减小，先存着。

当 $a_i<g_i$ 的时候，这个位置需要增大，而增大需要消耗后面需要减小的位置，如果不够用就不合法了。

```cpp

int n;
int a[N];
int g[N];
int main(){
	int T;
	read(T);
	while(T--){
		read(n);
		int sm=0;
		for(int i=1;i<=n;i++){
			read(a[i]);
			sm+=a[i];
		}
		for(int i=1;i<=n;i++){
			if(i<=(n-sm%n))g[i]=sm/n;
			else g[i]=sm/n+1;
		}
		sm=0;
		for(int i=n;i;i--){
			sm+=a[i]-g[i];
			if(sm<0){
				puts("No");
				break;
			}
		}
		if(sm>=0)puts("Yes");
	}
	return 0;
}

```

---

## 作者：Never_care (赞：1)

### 思路
先说题意。一个的序列经过 $k$ 次操作，每次操作选出一个 $a$ 和一个 $b$，使数组的第 $a$ 项加 $1$，第 $b$ 项减 $1$，问能不能将数组修改为一个不下降序列。

不难想到差分，建议先做[差分基础题](https://www.luogu.com.cn/problem/P2367)，考虑让数组尽量每个数值之间的差距尽可能小，即平均，且让前面的数尽可能大。若按照操作模拟出的数组和原数组任意一个数字的差为负数就代表不可构建，则输出 No。

### code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f 
using namespace std;
const int N=2e5+5;
int n;
ll a[N],b[N],pre[N];
int t;
int main(){
	cin>>t;
	while(t--){
		cin>>n;/
		for(int i=1;i<=n;i++){//前缀和
			cin>>a[i];
			pre[i]=pre[i-1]+a[i]; 
		}
		int t=pre[n]/n;
		for(int i=1;i<=n-pre[n]%n;i++){
			b[i]=t+b[i-1];//差分前半部分 
		}
		for(int i=(n-s[n]%n+1);i<=n;i++){//差分后半部分 
			b[i]=t+b[i-1]+1;
		}
		for(int i=1;i<=n;i++){
			if(s[i]>b[i]){//判断是否符合条件 
				cout<<"No\n";
				continue;
			}
		}
		cout<<"Yes\n";
	}
	return 0;
}
```

---

## 作者：wfc284 (赞：0)

只有当 $a_i < a_{i-1}$ 时，需要进行操作。  
我们可以时刻维持 $[1,i-1]$ 的不减性。  
假如扫到 $i$，要抹平差距，有两种办法。

1. 前面某两个元素加一减一。发现在一段区间内任意操作，区间内和 $sum$ 不变。我们可以让 $a_1 \sim a_{i-1}$ 尽量平均，使得他们中的最大值最小。于是让 $a_1 \sim a_k$ 为 $\lfloor \frac{sum}{i-1} \rfloor$，$a_{k+1} \sim a_{i-1}$ 为 $\lfloor \frac{sum}{i-1} \rfloor+1$。我们不关心 $k$ 具体是多少，只关心【均值】是否小于等于 $a_i$。
2. 如果【1.】仍然不行，可把 $a_{i+1}$ 减去【差距】，$a_i$ 加上【差距】。当然，如果此时 $i = n$，没有东西匀给 $a_i$ 了，输出 `No`。

Q：为什么【2.】中只需用 $a_{i+1}$ 给 $a_i$ 匀？  
A：$a_{i+1}$ 的亏的，后面再给他补。

做完了。
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
#define int long long
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 2e5+2;
	
	int n, a[N];
	
	int avg(int n, int sum) { return n == 0 ? 0 : sum / n + (sum % n != 0); }
	
	void main() {
		scanf("%lld", &n);
		for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
		int sum = 0;
		for(int i = 1; i <= n; ++i) {
			int x = avg(i-1, sum);
			if(a[i] < x) {
				if(i == n) {
					puts("No");
					return;
				}
				a[i+1] -= x - a[i];
				a[i] = x;
			}
			sum += a[i];
		}
		puts("Yes");
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：Noah2022 (赞：0)

### 题目大意
有一个长度为 $ N $ 的序列 $ A $ 。进行 $ k (0 \le k) $ 次操作：选择一对 $ i,j (1\le i<j\le n) $ ，将 $ A_i $ 加一，并且将 $ A_j $ 减一。判断是否能够将 $ A $ 数组修改成一个**不递减序列**。

### 思路
我们可以造一个**极限的目标数组**，如： $ 3,3,4,4 $ 。这样尽量平均的数组，保证前面的数最大化，如果 $ A $ 数组前面 $ i (1 \le i \le n) $ 个数的和，比目标数组前 $ i $ 个数的和要大，那就输出 NO 。

**注：因为目标数组的前面的数是最大化的，所以比目标数组大的都是不合法的。**

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200005],b[200005],s[200005];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(register int i(1);i<=n;i=-~i)
		{
			cin>>a[i];
			s[i]=s[i-1]+a[i]; // 记录目标的前缀和 
		}
		int pingjun=s[n]/n; // 取平均数
		for(register int i(1);i<=n-s[n]%n;i=-~i) // 前面一部分 
		{
			b[i]=pingjun+b[i-1];// 记录目标的前缀和 
		}
		for(register int i(n-s[n]%n+1);i<=n;i=-~i)
		{
			b[i]=b[i-1]+pingjun+1; // 后部分的前缀和 
		}
		for(register int i(1);i<=n;i=-~i)
		{
			if(s[i]>b[i])
			{
				cout<<"No\n";
				goto ss;
			}
		}
		cout<<"Yes\n";
		ss:;
	}
} 
```
[AC记录及代码](https://atcoder.jp/contests/arc185/submissions/59030333)

---

## 作者：Nuclear_Fish_cyq (赞：0)

我们注意到我们只需要判断可不可行。

如果有一个序列，所有可行的序列都可以变成这个序列而别的序列不行，那这题就好做了。

注意到一个上升的序列通过操作变成别的上升序列，由于每次总是前面加一后面减一相当于取长补短，那么新的序列总是会比原来的更“平”一些。

那么我们知道最平的序列就是把每个元素都搞得相等，但是有可能有余数，所以我们最优的序列实际上是这样的（令 $s=\sum a$）：

- 前 $n-s\bmod n$ 个数为 $\lfloor \frac{s}{n}\rfloor$。

- 后 $s\bmod n$ 个数为 $\lceil \frac{s}{n}\rceil$。

然后就是怎么判断一个序列能不能转化成这个序列。每一个加一都会让后面有一个减一的空间，每一个减一都会消耗前面的额度。如果有一个时刻额度不足，那就无法转化。

代码：


```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
#define mod 998244353
#define lwbd lower_bound
#define upbd upper_bound
//#define range
using namespace std;
void read(int &x){
	cin >> x;
	return;
}
void readll(ll &x){
	cin >> x;
	return;
}void readdb(db &x){
	cin >> x;
	return;
}
ll t, n, a[200000], sum, now;

//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n;
		sum = 0;
		now = 0;
		for(int i = 0; i < n; i++){
			cin >> a[i];
			sum += a[i];
		}
		for(int i = 0; i < n; i++){
			ll t = sum / n + (n - i <= sum % n);//t代表终点值
			now += t - a[i];
			if(now < 0){
				cout << "No" << endl;
				break;
			} 
		}
		if(now >= 0){//防止同时输出No和Yes 
			cout << "Yes" << endl;
		} 
	}
	return 0;
}



```

---

## 作者：Binah_cyc (赞：0)

看着题解区写的都是倒序做法，我提供一个正序考虑的贪心做法。

一个比较显然的性质：当前的位置越低，后面就越有可能是单调不降的。因此，我们需要考虑如何让当前的位置尽量小。

正序考虑每一个 $a_i$，如果它大于了当前所需要的最低要求，我们就将它多出来的那一部分向前面填，直到填到前面都填平或者是这个位置不够了就不填了，同时更新当前位置的最低要求。这是第一次向前填。如果能够填平前面的数，我们就在这个位置打一个标记，表示以这个数为结尾的前缀能够成为单调不降的，最后只需要看 $n$ 处是否有标记。

但是，在第一次向前填之后，可能还会剩下一些数字。为了让后面更有可能成功，我们需要**让当前位置最小**。因此，为了保证当前位置最小，我们将多出来的部分平均分配到前面。这是第二次向前填。

但是，这样还是有一些缺陷。

样例：
```
4
3 3 4 5
```
如果按照前面的做法去做的话，第 $4$ 个位置是不够的，因为它会认为前面还有两个 $3$ 需要填。但是实际上前面的两个 $3$ 已经不需要额外的数字来填它了，它本身就在以第 $3$ 个位置为结尾的前缀里面。

因此，我又维护了一个 $lst$ 表示上一个已经填完的位置是哪里，我们第一次向前填的时候，只需要从 $lst$ 向后填即可。但是，我们第二次向前填的时候，仍然需要从 $1$ 开始填。因为第一次填我们要**保证它是单调不降的序列**，第二次填我们要让它尽量少，**让后面的数字更有可能成为单调不降的**。

大体思路就是这样，语言表述可能不准确，建议看代码辅助理解。

```
// Problem: B - +1 and -1
// Contest: AtCoder - AtCoder Regular Contest 185
// URL: https://atcoder.jp/contests/arc185/tasks/arc185_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
constexpr int N=2e5+5;
#define int long long
int _,n,a[N],sum[N],f[N],vis[N],lst;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>_;
	while(_--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i];//使用前缀和进行优化
		f[1]=a[1];
		for(int i=2;i<=n;i++)//第一个位置没有考虑的必要
		{
			if(a[i]>=f[i-1])//大于了当前位置的要求
			{
				int desum=f[i-1]*(i-1-lst)-(sum[i-1]-sum[lst]);//desum表示前面还剩余多少没有填
				//从lst位置向前填
				int oversum=a[i]-f[i-1];//oversum表示这个位置最多能提供多少
				//这个if是第一次向前填
				if(desum>oversum) f[i]=f[i-1];//不够填的,直接全都填到前面,但是要求仍然不变
				else//还有剩的
				{
					//第二次向前填
					oversum=(a[i]-f[i-1])-(f[i-1]*(i-1)-sum[i-1]);//从1开始填,因为我们想要让这个位置最低
					int ave;//ave表示每一个位置平均能分到多少
					if(oversum<=0) ave=0;
					else ave=(oversum+i-1)/i;//上取整
					f[i]=f[i-1]+ave;
					vis[i]=1,lst=i;//打标记
				}
			}
			else f[i]=f[i-1];//本来就无法满足当前位置的需求,只能等着别人填它
		}
		if(vis[n]) cout<<"Yes\n";
		else cout<<"No\n";
		for(int i=1;i<=n;i++) vis[i]=0;
		lst=0;//多测清空
	}
	return 0;
}
```

---

## 作者：zengziqvan (赞：0)

### 题目大意

给定一个长为 $n$ 的序列 $A$，可以对此序列进行以下操作，操作次数无限制：

- 选择两个位置 $i,j$ 满足 $1\le i< j\le n$，将 $A_i$ 加 $1$ 并将 $A_j$ 减 $1$。

问序列 $A$ 能否通过以上操作形成一个单调不降的序列。

$T$ 组数据。

### 题目分析

发现最后一个数字显然不会被修改，所以可以从后往前考虑。

设已经将 $i+1\sim n$ 位置考虑完毕。

考虑第 $i$ 个位置。

根据贪心，第 $i$ 个位置的数字要尽量大。

有两种情况：

- $A_i>A_{i+1}$

此时显然需要通过操作使得 $A_i\le A_{i+1}$。

显然操作 $A_{i}-A_{i+1}$ 次 $A_i$ 取最大值。

不妨让 $A_{i-1}$ 成为被增加的数。

- $A_i<A_{i+1}$

此时如果直接确定 $A_i$，那么前面的数字限制将更加严格，更难以找到可行解。

所以考虑做若干次形如 $(i,j),i<j$ 的操作，让 $A_i$ 尽量大。

肯定是越接近后面的值越好。

所以 $A_i$ 的最优值显然是 $\lfloor \frac{\sum _{k=i}^{n} A_k}{n-i+1}\rfloor$。

时间复杂度 $\operatorname{O}(n)$。

```c++
const int N=2e5+10;
int t,n,a[N],b[N];
void solve() {
	cin>>n;
	FOR(i,1,n) a[i]=b[i]=read();
	if(n==1) {
		puts("Yes");
		return ;
	}
	LL um=a[n];
	ROF(i,n-1,2) {
		um+=b[i];
		if(a[i+1]<a[i]) {
			int dt=a[i]-a[i+1];
			a[i]-=dt;
			a[i-1]+=dt;
		} else {
			a[i]=um/(n-i+1);
		}
	}
	if(a[1]<=a[2]) {
		puts("Yes");
	}
	else puts("No");
}
main() {
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Dr_April (赞：0)

题意相当清晰，不做赘述。

拿到题目的第一眼相信看上去很像一个找规律或者推公式的题目。但是搓几个样例就会发现貌似没有公式或者规律。

既然正着推不好做，索性反过来想。

操作结束后的序列既然是单调不降的，再根据体面的操作，可以考虑让操作结束后的序列尽可能地平均，如果你构造出的序列与原序列任意一项的差小于 $0$ 就说明在最优构造的情况下仍然没法构造成功那就只能无解了。

那就直接按照这个思路构造就可以了。

---

