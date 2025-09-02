# Sum AND Subarrays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_b

ある日、ドワンゴ社員のニワンゴくんは、長さ $ N $ の整数列 $ (a_1,\ ...,\ a_N) $ を見つけました。ニワンゴくんは、数列 $ a $ の性質に興味を持っています。

数列 $ a $ の空でない連続する部分列 $ a_l,\ ...,\ a_r $ $ (1\ \leq\ l\ \leq\ r\ \leq\ N) $ の **美しさ** は、 $ a_l\ +\ ...\ +\ a_r $ と定義されます。ニワンゴくんは、ありうる $ N(N+1)/2 $ 個の空でない連続する部分列のうち、 $ K $ 個を選んで取ってきて、それらの美しさのビット毎の論理積 (AND) を計算したとき、その最大値がどうなるかを知りたがっています (取ってくる部分列の間で重複する要素があっても構いません)。

彼の代わりに最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $
- $ 1\ \leq\ K\ \leq\ N(N+1)/2 $
- 入力として与えられる数値はすべて整数である

### Sample Explanation 1

異なる空でない連続する部分列は $ 10 $ 個存在します。全列挙すると、 - 1 番目から始まるもの: $ \{2\},\ \{2,\ 5\},\ \{2,\ 5,\ 2\},\ \{2,\ 5,\ 2,\ 5\} $ - 2 番目から始まるもの: $ \{5\},\ \{5,\ 2\},\ \{5,\ 2,\ 5\} $ - 3 番目から始まるもの: $ \{2\},\ \{2,\ 5\} $ - 4 番目から始まるもの: $ \{5\} $ です (数列の要素が同じでも、異なる添字から始まる列は異なるものとみなすことに注意してください)。 このうち異なる $ 2 $ 個の部分列の美しさのビット毎の論理積 (AND) として得られる値の最大値は $ 12 $ です。 これは $ \{5,\ 2,\ 5\} $ (美しさ $ 12 $) と $ \{2,\ 5,\ 2,\ 5\} $ (美しさ $ 14 $) を選んだ時に達成できます。

## 样例 #1

### 输入

```
4 2
2 5 2 5```

### 输出

```
12```

## 样例 #2

### 输入

```
8 4
9 1 8 2 7 5 6 4```

### 输出

```
32```

# 题解

## 作者：Licykoc (赞：2)

# 题意：

给定一个长度为 $n$ 的序列，求其各个非空连续子序列和中 $k$ 个的与(&)和最大为多少。

$2 \le n \le 1000$ 。

# $\mathcal{Sol:}$

首先求连续子序列和的话没得优化，只能 $\mathcal{O}(n^2)$ 暴力预处理，接下来考虑取 $k$ 个怎么取。

首先因为答案是与和，所以我们一定要选最高位尽量大的数来组合。这很好证明，因为 $2^x$ 一定大于等于 $2^{x-1}+2^{x-2}+ ... +2^0$ 。基于这点结论，我们就可以贪心的来选数，从大到小枚举答案的每一位，然后挨个判断预处理好的数，如果满足条件的数 $\ge\ k$ 那么代表这一位是可取的，计入总和即可。注意要开`long long `，~~否则会和我一样调1天~~。

综上，我们得到了约为一个 $\mathcal{O}(n^2 \times 63)$ 的算法。

# $Code:$

```cpp
#include <bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int MAXN=1e3+10;
typedef long long ll;
int N=0,n,k,ans;
int a[MAXN];
int s[MAXN];
int st[MAXN*MAXN];
signed main () {
	IOS;
	cin>>n>>k;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=1;i<=n;++i) s[i]=s[i-1]+a[i];
   //必要的前缀和预处理，降一位时间复杂度
	for (int len=1;len<=n;++len) 
		for (int i=1;i<=n-len+1;++i) st[++N]=s[i+len-1]-s[i-1];
	for (int bit=62;bit>=0;--bit) {
    //枚举位
		int cnt=0,now=ans+(1ll<<bit);
		for (int i=1;i<=N;++i) if ((now&st[i])==now) ++cnt;
        //如果 & 后还等于自身，那么就说明该数不会使答案变劣，属于满足的情况
		if (cnt>=k) ans=now;
	}
	cout<<ans<<endl;
}
```

---

## 作者：A1C3 (赞：0)

# Sum AND Subarrays

观察本题，一个显然的思路是将所有的 $\frac {N(N+1)} {2}$ 个非空连续子序列的和全部存下来（记存的数组为 $a$），然后依次从高位到低位枚举二进制位（保证答案最优）。设当前枚举到的位数为 $i$，如果对于任意的 $j (1 \le j \le \frac {N(N+1)} {2})$，有不少于 $K$ 个 $a_j$ 右移 $i$ 位后的最低位为 $1$，则说明当前位可选；反之当前位不选。如果个数恰好为 $K$，则退出循环，无需再选。枚举下一个二进制位时，从当前选出的数中进一步筛选即可。

细节实现：非空连续子序列的和可以使用前缀和计算。注意到本题 $N \le 1000, a_i \le 10^9$，最大可能的和为 $1000 \times 10^9 = 10^{12}$。因此，需要使用 long long，二进制位从 $63 \sim 0$ 依次枚举。

综上，此做法的时间复杂度为 $O(N^2)$。

## AC Code

```cpp
#include <iostream>
using namespace std;
using LL = long long;
const int N = 1e6 + 7;
LL s[N], a[N], b[N];
int main() {
	int n, m, tp = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		LL x;
		scanf("%lld", &x);
		s[i] = s[i-1]+x;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j)
			a[++tp] = s[j]-s[i-1];
	int ct = 0;
	for (int i = 63; i >= 0; --i) {
		ct = 0;
		for (int j = 1; j <= tp; ++j)
			if ((a[j]>>i) & 1LL) b[++ct] = a[j];
		if (ct < m) continue;
		for (int j = 1; j <= ct; ++j)
			a[j] = b[j];
		if (ct == m) break;
		tp = ct;
	}
	LL ans = a[1];
	for (int i = 2; i <= m; ++i)
		ans &= a[i];
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的绿题。

## 思路：

这题我们可以用贪心思想来完成。

首先将每个数都要求出来，从高位枚举，记录每个数二进制位 $1$ 的个数，若 $1$ 的个数大于等于 $k$ 的时候，则将当前位为 $0$ 的全部删除，同时给 $ans$ 加上当前位的值。

最后再输出 $ans$ 值即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=100007;
long long n,k;
long long a[N];

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> k;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
	}
	vector<long long> v;
	for(long long i=1;i<=n;i++)
	{
		long long sum=0;
		for(long long j=i;j<=n;j++)
		{
			sum+=a[j];
			v.push_back(sum);
		}
	}
	long long ans=0;
	for(long long i=41;i>=0;i--)
	{
		vector<long long> t;
		long long p=((long long)1 << i);
		for(auto e:v)
		{
			if(e&p)
			{
				t.push_back(e);
			}
		}
		if(t.size() >= k)
		{
			ans+=p;
			v.clear();
			v=t;
		}
	}
	cout << ans << endl;
	return 0; 
}
``````

---

## 作者：wht_1218 (赞：0)

本题可以简化为求 $n$ 个数最大的按位与的和。

我们可以使用贪心算法解决这个问题。

首先将每个数求出来，从**高位**枚举，记录每个数二进制位 $1$ 的个数，若 $1$ 的个数**大于等于** $k$，则将当前位为 $0$ 的全部删掉，同时 $ans$ 加上当前位的值。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1007;
ll a[N];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}vector<ll> v;
	for(int i=1;i<=n;++i){
		ll cnt=0;
		for(int j=i;j<=n;++j){
			cnt+=a[j];
			v.push_back(cnt);
		}
	}ll ans=0;
	for(int i=41;i>=0;--i){//2^0也是数，别忘了！
		vector<ll> t;
		ll p=((ll)1<<i);
		for(auto e:v){
			if(e&p){
				t.push_back(e);
			}
		}if(t.size()>=k){
			ans+=p;
			v.clear();
			v=t;
		}
	}cout<<ans<<endl;//岛国题要换行！
	return 0; 
}
```


---

## 作者：原子げんし (赞：0)

em... 这道题真的是恶心

我们可以采取一种构造答案的方法:**猜某一位是否为1**,可以看出,按位与后的值只会缩小.可以贪心:用 $2^x and   $ $sum_i$ 
 ($sum_i$为某一段子序列的和.)
当上式的值不为0时,说明$sum_i$的位数小于等于$2^x$的位数,故答案不变,为最优解.

上代码(递归):
```
#include<bits/stdc++.h>
using namespace std;
long long a[1010];vector<long long>sum;
int N,K;
long long dfs(vector <long long> sum,long long dep=40) {
	if(dep==-1) return 0;//边界
	vector <long long> v; //候选的和
	for(int i=0;i<sum.size();i++) if(sum[i]&(1ll<<dep)) v.push_back(sum[i]);//满足条件时就把候选的和压进去
	if(v.size()>=K) return (1ll<<dep)+dfs(v,dep-1);//有大于等于K个可以的和
	return dfs(sum,dep-1);//不然继续枚举位数
}
int main() {
	int ans=0; cin>>N>>K;
	for(int i=0;i<N;i++) {
		cin>>a[i];
	}
	for(int i=0;i<N;i++) {
		long long cnt=0;
		for(int j=i;j<N;j++) cnt+=a[j], sum.push_back(cnt);//求和
	}
	cout<<dfs(sum)<<endl;
}

```


---

