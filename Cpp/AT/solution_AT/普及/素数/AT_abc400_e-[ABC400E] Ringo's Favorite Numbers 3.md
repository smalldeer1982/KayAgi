# [ABC400E] Ringo's Favorite Numbers 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc400/tasks/abc400_e

对于正整数 $N$，当且仅当满足以下两个条件时，$N$ 被称为 **400 number**：

- $N$ 恰好有 $2$ 种不同的素因数。
- 对于 $N$ 的每个素因数 $p$，$N$ 被 $p$ 整除的次数为偶数次。更严格地说，对于 $N$ 的每个素因数 $p$，使得 $p^k$ 是 $N$ 的约数的最大非负整数 $k$ 是偶数。

给定 $Q$ 个查询，请回答每个查询。每个查询给出一个整数 $A$，请找出不超过 $A$ 的最大 400 number 的值。在本问题的约束条件下，保证 $A$ 以下必定存在至少一个 400 number。

## 说明/提示

### 约束条件

- $1 \leq Q \leq 2 \times 10^5$
- 对于每个查询，$36 \leq A \leq 10^{12}$
- 输入中的所有值均为整数

### 样例解释 1

以第一个查询为例：  
$400$ 的素因数恰好为 $2$ 和 $5$ 两种。$400$ 被 $2$ 整除的次数为 $4$ 次（偶数次），被 $5$ 整除的次数为 $2$ 次（偶数次），因此 $400$ 是 400 number。而 $401$、$402$、$403$、$404$ 均不是 400 number，故答案为 $400$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
404
36
60
1000000000000
123456789```

### 输出

```
400
36
36
1000000000000
123454321```

# 题解

## 作者：dongzirui0817 (赞：6)

## 题目大意

给定一个数 $A$，求最大的正整数 $N$，满足：

- $N \le A$
- $N$ 可表示为 $p ^ {2i} q ^ {2j}$，其中 $p, \, q$ 为素数，且 $p \not = q$，$i, \, j \in \N ^ +$。

多测，设单测试点的测试数为 $Q$，则 $1 \le Q \le 2 \times 10 ^ 5$，$36 \le A \le 10 ^ {12}$。

## 思路

基本操作，设 $N = p ^ {2i} q ^ {2j}$，其中 $p, \, q$ 为素数，且 $p \not = q$，$i, \, j \in \N ^ +$。

$\because N = p ^ {2i} q ^ {2j} = (p ^ i q ^ j) ^ 2$

$\therefore p ^ i q ^ j = \sqrt{N}$

$\because N \le A$

$\therefore p ^ i q ^ j \le \sqrt{A}$

$\because A \le 10 ^ {12}$

$\therefore p ^ i q ^ j \le 10 ^ 6$

$\therefore$ 符合条件的 $N$ 最多只有 $10 ^ 6$。

暴力预处理符合 $N = p ^ {2i} q ^ {2j}$ 的数即可，查询时交给二分。

## 代码实现

这里提供 $2$ 种做法。（第一种代码短，第二种速度快）

### 第一种

设 $R = p ^ i q ^ j$，按照上面的结论 $R \le 10 ^ 6$，大力枚举 $R$，分解质因数，判断是否符合条件即可。

但速度太慢了，所有时间点均超 $1000$ ms。

[记录 & 代码](https://atcoder.jp/contests/abc400/submissions/64574691)

### 第二种

用素数筛筛出 $1 \sim 10 ^ 6$ 的素数，设 $prime_x$ 表示第 $x$ 个素数。之后选取两个正整数数 $u , \, v$，那么 $p = prime_u$，$q = prime_v$，之后枚举指数 $i , \, j$，算出 $p ^ i q ^ j$，只要小于等于 $10 ^ 6$，就把它的平方扔进一个栈里。（因为这个数的平方肯定符合要求）

最后对栈排序即可。（赛时做法）

虽然代码长，但速度快啊，最慢测试点 $122$ ms。当然，如果您只是为了通过此题，第一种就够用了。

当然细节较多，其他细节请看代码。

[记录 & 代码](https://atcoder.jp/contests/abc400/submissions/64542759)

---

## 作者：ctw123 (赞：5)

# 题解：E - Ringo's Favorite Numbers 3

## 题意
多个查询，每个查询给出一个整数 $A$，要找到不超过 $A$ 的最大「400 数」。「400 数」定义：
- 恰好有 2 个不同的质因子。
- 每个质因子的指数均为偶数。

### 思路
设满足条件的数为 $N = p^{2c} \times q^{2d}$，则 $N = (p^c \times q^d)^2$。因此，所有「400 数」都可表示为某个数的平方，且该平方数恰好有两个不同的质因子。

### 具体实现
1.用欧拉筛预处理每个数的最小质因子。    
2. 对每个数 $i$：
有状态转移：$cnt[i] = cnt[i/p[i]] + [p[i] \nmid (i/p[i])]$。     
3.
     若 $cnt[i] = 2$，则 $rec[i] = i^2$
     否则 $rec[i] = rec[i-1]$。     
4. 对于每个 $A$，计算 $\lfloor \sqrt{A} \rfloor$，直接查表输出 $rec[\lfloor \sqrt{A} \rfloor]$。
### 复杂度
$1\le\lfloor \sqrt{A} \rfloor\le10^6$。    
设 $N=\max(\lfloor \sqrt{A} \rfloor)$  。      
因此时间复杂度 $O(N)$。

### 代码
```cpp
#include <bits/stdc++.h>
#define N 1000006
#define int long long
using namespace std;

vector<int> prime;      // 存储素数
vector<int> p(N);       // p[i] 表示i的最小质因子
vector<int> cnt(N);     // cnt[i] 表示i的不同质因子数量
vector<int> rec(N);     // rec[i] 记录平方基数为i时的最大答案
vector<bool> is_prime(N, false); // 筛法标记数组

// 预处理最小质因子和质因子数量
void preprocess() {
    is_prime[1] = true;
    for (int i = 2; i < N; ++i) {
        if (!is_prime[i]) {
            prime.push_back(i);
            p[i] = i;
        }
        for (int j = 0; j < prime.size() && i * prime[j] < N; ++j) {
            is_prime[i * prime[j]] = true;
            p[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
    
    cnt[1] = 0;
    for (int i = 2; i < N; ++i) {
        int prev = i / p[i];
        // 若prev中不含当前质因子，则数量+1
        cnt[i] = cnt[prev] + (prev % p[i] != 0);
        // 维护前缀最大值
        rec[i] = (cnt[i] == 2) ? i * i : rec[i - 1];
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    preprocess();
    
    int Q;
    cin >> Q;
    while (Q--) {
        int A;
        cin >> A;
        int sqrt_A = (int)sqrtl(A); // 计算平方根
        cout << rec[sqrt_A] << '\n';
    }
    return 0;
}

---

## 作者：wmrqwq (赞：4)

这是一篇视频题解。

![](bilibili:BV19BRdYdEHk?t=477)

[参考代码](https://atcoder.jp/contests/abc400/submissions/64539653)

---

## 作者：Merge_all (赞：2)

# Solution
考虑到 $A \le 10^{12}$，那么筛质数就只用筛到 $\sqrt{A} = 10^6$ 即可，那么剩下的其实就是暴力枚举 $A$ 可以分解成的质因数 $a, b$，然后枚举 $a, b$ 的次数。

预处理以后就可以直接输出了。
# Code
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
static constexpr size_t N = 1e6 + 5, M = 2e3 + 5;
int n, q, prime[N], cnt, pos;
bool vis[N];
vector<int> ans;
signed main () {
	*cin.tie(nullptr) << fixed << setprecision (20);
	cout.tie(nullptr) -> ios_base :: sync_with_stdio (false);
	
	cin >> q;
	for (int i = 2; i <= N - 5; i ++) {
		if (!vis[i]) prime[++ cnt] = i;
		for (int j = 1; j <= cnt && i * prime[j] <= N - 5; j ++) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (int i = 1; i <= cnt; i ++)
		for (int j = 1; j < i && prime[i] * prime[j] <= N - 5; j ++)
			for (int k = prime[i]; k <= N - 5; k *= prime[i])
				for (int l = prime[j]; k * l <= N - 5; l *= prime[j])
					ans.push_back (k * l);// 这里没有进行平方
	sort (ans.begin (), ans.end ());
	while (q --) {
		cin >> n;
		pos = *-- upper_bound (ans.begin (), ans.end (), sqrt (n));
		cout << pos * pos << '\n';//平方回去
	}
	return 0;
}
```

---

## 作者：_Weslie_ (赞：2)

昨晚见证了 ABC400 的诞生。但是这场为什么这么抽象。

## Solution AT_abc400_e

### Idea

不难发现原题要求最大的满足 $w^2\le n$ 且 $w=p_1^{s_1}p_2^{s_2}$ 的 $w$，其中 $p$ 为质数。

我们先线性筛出 $10^6$ 以内的素数列表 $p$（因为原题中 $N\le 10^{12}$，则 $w\le 10^6$）。

然后我们再预处理出所有 $p_i^r$ 使得 $p_i^r\le 10^6$。把这个数组记为 $q$ 并对 $q$ 排序（方便后面单调性的使用）。

接着，我们只需要随便找两个质数次方相乘，就可以把 $10^6$ 以内所有的 $w$ 找出来。但是在这里有一点问题：因为 $q$ 是排过序的，你需要保证相乘的两个 $q$ 不是由同一个素数乘方得到的。于是将 $q$ 定义为结构体，同时维护一个这个 $q$ 是由哪个素数乘方得到的值，这样就可以解决这个问题了。

我们把所有的 $w$ 排序并乘方，然后对每组询问直接二分找出答案。

### Code

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct node{
    ll x;int p;
};
int prime[1000001],p,a[1000001];node q[1000001];int cnt;
ll w[1000001],l;
void Prime(){
	for(int i=2;i<=1000000;i++){
		if(a[i]==0)prime[++p]=i;
		for(int j=1;j<=p&&prime[j]*i<=1000000;j++){
			a[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
}
bool cmp(node _,node __){
    return _.x<__.x;
}
ll n;
int main(){
    Prime();
    for(int i=1;i<=p;i++){
        ll res=prime[i];
        while(res<=1000000){
            q[++cnt].x=res;
            q[cnt].p=prime[i];
            res=res*prime[i];
        }
    }
    sort(q+1,q+cnt+1,cmp);
    for(int i=1;i<=cnt;i++){
        for(int j=i+1;j<=cnt;j++){
            if(q[i].p==q[j].p)continue;
            if(q[i].x*q[j].x>1000000)break;//q 的单调性
            w[++l]=q[i].x*q[j].x;
        }
    }
    sort(w+1,w+l+1);
    for(int i=1;i<=l;i++)w[i]*=w[i];
    int T;scanf("%d",&T);
    while(T--){
        scanf("%lld",&n);
        printf("%lld\n",w[upper_bound(w+1,w+l+1,n)-w-1]);
    }
}
```

### Time

由于我们在每次循环中最多枚举到 $10^6$。素数的乘方两两不同，唯一分解定理告诉我们不可能有一个数会有两对质因数分解，于是求 $w$ 的过程也不可能重复。于是时间复杂度为 $\operatorname{O}(\omega)$，其中 $\omega$ 为 $\sqrt{n}$ 的值域。

---

## 作者：ikunTLE (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc400_e)

### 思路

首先打个埃氏筛，统计出每个数不同素因数的个数，计入数组 $C$ 中。

然后遍历一遍，用数组 $R$ 统计，$R_i$ 表示不超过 $i$ 的最大的恰好有两个不同的素因数。令 $P=0$，遍历时，若有 $C_i=2$，则说明 $i$ 恰好有两个不同的素因数，更新 $P=i$。每一次遍历无论是否更新 $P$，都要记 $R_i=P$。

查询的时候，答案即为 $R_{\lfloor\sqrt{A}\rfloor}^2$。这是因为 $R$ 中储存的是恰好有两个不同的素因数，平方后即为答案。

时间复杂度 $\mathcal{O}(N\log\log N)$，是埃氏筛的复杂度。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e6;
int cnt[N+10],res[N+10];
void _init(){
	for(int i=2;i<=N;++i)
		if(!cnt[i])
			for(int j=i;j<=N;j+=i)
				++cnt[j];
	int p=0;
	for(int i=1;i<=N;++i){
		if(cnt[i]==2)
			p=i;
		res[i]=p;
	}
	return;
}
signed main(){
	_init();
	int q=read();
	while(q--){
		int a=read();
		int sq=sqrt(a);
		while(sq*sq>a)
			--sq; // 控制精度
		printf("%lld\n",res[sq]*res[sq]);
	}
	return 0;
}
```

---

## 作者：2huk (赞：1)

幸运数字一定能被表示成 $p^{2a}q^{2b}$ 的形式，其中 $p,q$ 是质数。

注意到这东西等于 $(p^aq^b)^2$。那很好了，$p^{2a}q^{2b} \le n$ 转化成了 $p^aq^b \le \sqrt n$，也就是说幸运数字的数量是 $\sqrt n$ 级别的。

首先把质数筛出来。枚举质数 $p_i$，枚举指数 $a$，将所有这样的不超过 $10^6$ 的 $p_i^a$ 存起来。

将存起来的 $p_i^a$ 排序得到序列 $A$。注意到序列 $A$ 中没有重复数字，且每个数都不超过 $10^6$，所以 $A$ 的长度不超过 $10^6$，所以上面操作的复杂度是正确的。

枚举 $i<j$，将不超过 $10^6$ 的 $A_i \times A_j$ 存起来。

将存起来的 $A_i \times A_j$ 排序得到序列 $B$。注意到序列 $B$ 中没有重复数字，且每个数都不超过 $10^6$，所以 $B$ 的长度不超过 $10^6$，所以上面操作的复杂度是正确的。

一个小问题是 $B$ 中可能存在 $8,16$ 这种不对劲的数字。这是因为 $A_i \times A_j$ 中 $A_i,A_j$ 可能对应同一个质数底数 $p_i$。而这样错误的 $B_i$ 肯定也在 $A$ 中出现过，那很好了，判断一下删掉即可。

然后查询时在 $B$ 中二分就做完了。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e6 + 10;

int p[N], cnt;
bool st[N];
vector<int> vec;
vector<int> res;
set<int> S;

void init() {
	for (int i = 2; i < N; ++ i ) {
		if (!st[i]) p[ ++ cnt] = i;
		for (int j = 1; p[j] <= (N - 1) / i; ++ j ) {
			st[p[j] * i] = true;
			if (i % p[j] == 0) break;
		}
	}
	
	for (int i = 1; i <= cnt; ++ i ) {
		for (int x = p[i]; x < N; x *= p[i]) {
			vec.push_back(x);
			S.insert(x);
		}
	}
	
	sort(vec.begin(), vec.end());
	
	for (int i = 0; i < vec.size(); ++ i )
		for (int j = i + 1; j < vec.size(); ++ j ) {
			int x = vec[i] * vec[j];
			if (x < N) {
				if (!S.count(x)) res.push_back(x);
			} else break;
		}
	
	sort(res.begin(), res.end());
}

int solve() {
	int x;
	cin >> x;
	x = sqrtl(x);
	int ans = *(upper_bound(res.begin(), res.end(), x) - 1);
	return ans * ans;
}

signed main() {
	init();
	int T;
	cin >> T;
	while (T -- ) cout << solve() << '\n';
	return 0;
}
```

---

## 作者：qwqerty (赞：1)

# 题意简化
求不小于 $a$ 的最大正整数，使得它是完全平方数且刚好有两个质因子。
# 解题思路
若一个数是完全平方数且有两个质因子，则它的平方根也必定有两个质因子。所以只需用线性筛预处理质因子个数，再从 $\sqrt{a}$ 向后枚举即可。
# AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n;
const int N = 1e6;
bool vis[N + 5];
int c, pr[N + 5], cnt[N + 5];
void init() {
	for (int i = 2; i <= N; i++) {
		if (vis[i] == 0) cnt[i] = 1, pr[++c] = i;
		for (int j = 1; j <= c && i * pr[j] <= N; j++) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0){
				cnt[i * pr[j]] = cnt[i];
				break;
			} else cnt[i * pr[j]] = cnt[i] + 1;
		}
	}
}
signed main() {
	init();
	cin >> t; 
	while (t--) {
		cin >> n;
		int sq = sqrtl(n);
		while (1) {
			if (cnt[sq] == 2) {
				cout << sq * sq << "\n";
				break;
			}
			sq--;
		}
	}
	return 0;
}
```

---

## 作者：Dream_poetry (赞：1)

### 思路：

首先我们假设一个好的数是 $x$，满足 $x=p^{2u}q^{2v}$，其中 $p,q$ 都是质数，$u,v$ 都是正整数。

我们变换得到 $x=(p^uq^v)^2$。

也就是说一个好的数必然是一个完全平方数。

那我们只枚举 $1$ 到 $10^6$ 这些可能是平方根的数。

我们设 $ans_i$ 表示以 $i^2$ 为上限的答案。

首先预处理筛选出所有的质数。

显然由题意知，$36$ 是最小的好的数，所以我们得到 $ans_6=6$。

然后我们从 $7$ 枚举到 $10^6$，首先 $ans_i=ans_{i-1}$，考虑如果当前的数 $i$ 分解质因数后恰好有两种质因子，则将 $ans_i$ 更新为 $i$。

查询时，直接输出 $ans_{\sqrt{a}}$ 即可。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T;
int n;
int ans[1000005];

inline void solve(){
	cin>>n;
	int k=sqrt(n);
	cout<<ans[k]*ans[k]<<'\n';
}
int sum;
int spf[1000005];




signed main(){
	ios::sync_with_stdio(0);
	cin>>T;
	for (int i=1;i<=1000000;i++){
		spf[i]=i;
	}
	for (int i=2;i*i<= 1000000;i++) {
        if (spf[i]==i){
            for (int j=i*i;j<=1000000;j+=i){
                if (spf[j]==j) spf[j]=i;
            }
        }
    }
    ans[6]=6;
    for (int i=7;i<=1000000;i++){
        ans[i]=ans[i-1];
		int x=i;
        int lst=0;
		int cnt=0;
        while (x!=1) {
            int p=spf[x];
            if (p!=lst){
                ++cnt;
                if (cnt>2){
					cnt=0;
                	break;
				}
                lst=p;
            }
            x/=p;
        }
        if (cnt==2){
        	ans[i]=i;
		}
		else{
			ans[i]=ans[i-1];
		}
    }
	
	while (T--){
		solve();
	}	
	
	
	return 0;
}
```

---

## 作者：szh_AK_all (赞：1)

发现我们不好在询问时做过多的事情，那么考虑预处理，预处理什么呢？似乎必须要把所有的合法的数找出来（当然大小不能超过 $10^{12}$）。

第一步是筛质数，容易发现我们所筛的质数大小只需要在 $10^6$ 以内，因为合法的数是可以分解成 $p^{2a} \times q^{2b}$ 的形式的，若 $p,q$ 中有一个数超过了 $10^6$，则他们组成的数肯定会超过 $10^{12}$。

第二步是枚举每对质数找出所有合法的数。枚举指数即可，但是在枚举时记得加一些中断条件。

最后可以将所有合法的数按从小到大的顺序排个序，在询问时直接二分即可。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int vis[1000005], pri[1000005], tot;
int a[8252395], cnt;

int qpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b % 2)
			ans = ans * a;
		a = a * a;
		b /= 2;
	}
	return ans;
}

signed main() {
	for (int i = 2; i <= 1000000; i++) {
		if (!vis[i])
			pri[++tot] = i;
		for (int j = 1; j <= tot && i * pri[j] <= 1000000; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0)
				break;
		}
	}
	for (int i = 1; i <= tot; i++) {
		for (int j = i + 1; j <= tot; j++) {
			if (pri[i]*pri[i]*pri[j]*pri[j] > 1000000000000)
				break;
			for (int k = 2;; k += 2) {
				if (qpow(pri[i], k) > 1000000000000)
					break;
				for (int kk = 2;; kk += 2) {
					if (qpow(pri[i], k)*qpow(pri[j], kk) > 1000000000000)
						break;
					a[++cnt] = qpow(pri[i], k) * qpow(pri[j], kk);
				}
			}
		}
	}
	sort(a + 1, a + cnt + 1);
	int q;
	cin >> q;
	while (q--) {
		int aa;
		cin >> aa;
		int po = lower_bound(a + 1, a + cnt + 1, aa) - a;
		if (a[po] == aa)
			cout << aa << "\n";
		else
			cout << a[po - 1] << "\n";
	}
}
```

---

## 作者：2012_Zhang_ (赞：0)

## 思路解析
分析一下这道题，我们可以对其转换，设每次询问的答案为 $K$，我们对其开根，记为 $k'$。  
显然有 $k'=p^a\times q^b$，其中 $p,q$ 为质数，$a,b \ge 1$，说白了就是有两个质因数。  
我们不难发现，$k' \le 10^6$，我们可以对其预处理，使用埃氏筛记录每个数的质因数个数，在用一个数组处理这个数前面最大符合要求的数。  
这道题已经分析全面了，接下来是代码实现。
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5,N=1e6;
const double eps=1e-6;
int prime[maxn],a[maxn],tot,nxt[maxn],q,x;
bool vis[maxn];
void init(){
	for(int i=2;i<=N;i++){
		if(!vis[i]){
			for(int j=i;j<=N;j+=i){
				vis[j]=1;
				a[j]++;
			}
		}
	}
	for(int i=1;i<maxn;i++){
		if(a[i]==2) nxt[i]=i;
		else nxt[i]=nxt[i-1];
	}
}
int solve(int n){
	int l=1,r=1e9,ans;
	while(l<=r){
		int mid=(l+r)/2;
		if(mid*mid<=n) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>q;
	init();
	while(q--){
		cin>>x;
		int k=solve(x);
		cout<<nxt[k]*nxt[k]<<endl;
	}
	return 0;
}

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[ABC400E](https://www.luogu.com.cn/problem/AT_abc400_e)

## Statement

定义 $N$ 若为一个 $400$ 数满足以下条件：

- $N$ 恰含两个质因子。
- 对于 $N$ 的两个质因子，最大的 $k$ 使得 $p^k$ 满足 $p^k \mid N$ 为偶数。

有 $Q$ 次询问，每次给定一个数 $x$，求不超过 $x$ 最大的 $400$ 数。

## Solution

因为 $N \leq 10^{12}$，考虑筛 $O(\sqrt{n})$ 内的质数然后枚举倍数，找出恰含两个质因子的数的平方，这样就保证 $k$ 定为偶数。

每次查询二分即可。

## Code

[Submission](https://atcoder.jp/contests/abc400/submissions/64553517)

---

## 作者：I_am_kunzi (赞：0)

# AT_abc400_e 题解

### 前言

作为第 $ 400 $ 场 ABC，这场的题跟 $ 400 $ 都跑不了联系，这道题也不例外，因为 $ 400 $ 正是符合题目规定的一个数字。

### 题目翻译

一个数 $ N $ 是 $ 400 $ 数，当且仅当其满足以下两个条件：

+ $ N $ 恰好有两个质因子；

+ 在以上条件下，若这两个质因子为 $ p $ 和 $ q$，有 $ N = p ^ a \times q ^ b (a > 0 , b > 0)$，则 $ a \bmod 2 = 0$，$b \bmod 2 = 0$。（本条相较于原题面中的第二条稍作改动，但意思不变。）

现在给你 $ Q $ 组询问，每组询问给你一个 $ A$，求最大的不超过 $ A $ 的 $ 400 $ 数。由于题目限定 $ A \ge 36$，所以不超过 $ A $ 的 $ 400 $ 数一定存在。

### 题目思路

首先容易发现最小的 $ 400 $ 数是 $ 36$，因为最小的两个质数为 $ 2 $ 和 $ 3$，而满足条件的数中质数的幂次必定是偶数，故最小的 $ 400 $ 数为 $ 2 ^ 2 \times 3 ^ 2 = 36$。

其次我们发现将上文的第二条限制改写，可得到 $ \sqrt N = p ^ {\frac a 2} \times q ^ {\frac b 2}$，因为 $ a $ 和 $ b $ 均为偶数。这个时候发现 $ \frac a 2 $ 和 $ \frac b 2 $ 都是正整数，一个暴力的想法就是找出 $ \sqrt {10 ^ {12}} = 10 ^ 6 $ 内所有的这种数，并将其平方得到范围内的所有 $ 400 $ 数，每次处理询问时二分即可。

但这个做法的复杂度如何？若设 $ 10 ^ {12} $ 之内的 $ 400 $ 数的个数为 $ T$，则 $ Q $ 次二分的复杂度是 $ O(Q \log T)$ 的。现在的关键在于处理 $ 400 $ 数的复杂度。

若想要处理出 $ 400 $ 数，只需要处理出 $ 10 ^ 6 $ 之内的质因子只有两个的数再平方，而我们可以把质数筛出来，并用一个数组 $ a $ 记录每个数的质因子个数，把质数的倍数对应位置的值 $ + 1 $ 即可。

当然这里还有一个不需要筛质数的方法，但其思想类似。容易发现质数的因子只有 $ 1 $ 和它本身，而如果我们还是用 $ a $ 数组来统计每个数的因子个数，从 $ 1 $ 开始扫到 $ 10 ^ 6$，若扫到一个位置发现这个位置的值为 $ 0$，则证明这个数没有小于它本身的质因子，即它是一个质数。所以我们扫到这种位置时，按照上一段的方法处理即可。

最后把 $ a $ 数组再扫一遍，每一个 $ a_i = 2 $ 的 $ i$ 就对应着一个 $ 400 $ 数的算术平方根，把这种 $ i $ 平方后记录到另一个 $ b $ 数组中，即可处理出 $ 400 $ 数的数组，容易发现 $ i $ 从小到大枚举时，$ i ^ 2 $ 也是单调递增的，故不需要排序也可以保证正确性。

但是这里有两个注意点：

+ 扫 $ a $ 数组时的循环变量记得开 ```long long```，不然平方之后会超过 ``` int ``` 的范围；

+ 对于二分，除了手写之外也可以选用 ```upper_bound```，但需注意将找到的位置往前一个才是正确答案。因为 ``` lower_bound ``` 查找大于等于某数的第一个数，若用在此题中，查到的数大于这个数，则需要向前一个位置；但如果恰好查到这个数，则不需移动。而 ``` upper_bound ``` 查到的是大于某数的第一个数，所以无论什么情况都只需要向前一个位置即可。相比起来 ``` upper_bound ``` 的判断更方便，所以就用它了。（不是说不能写 ```lower_bound```，只是判断太麻烦了而已。）

### 代码

[附 AtCoder 提交记录。](https://atcoder.jp/contests/abc400/submissions/64567239)

```cpp
// 缺省源见 https://www.luogu.com.cn/paste/9xcy6boi
int a[1000005];
long long b[1000005];
int cnt = 0;
signed main()
{
	for(int i = 2 ; i <= 1000000 ; i++)
	{
		if(a[i] == 0) // prime
		{
			for(int j = i ; j <= 1000000 ; j += i)
			{
				a[j]++;
			}
		}
	}
	for(long long i = 1 ; i <= 1000000 ; i++) // 记得开 long long 不然会炸出奇怪东西爆调不过
	{
		if(a[i] == 2)
		{
			b[++cnt] = i * i;
		}
	}
	int t;
	read(t);
	while(t--)
	{
		long long x;
		read(x);
		//printnl(*lower_bound(b + 1 , b + cnt + 1 , x) == x ? x : *(lower_bound(b + 1 , b + cnt + 1 , x) - 1));
		printnl(*(upper_bound(b + 1 , b + cnt + 1 , x) - 1)); // 上面那行就是正确的 lower_bound 写法，但太长了
	}
	return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [ABC400E] Ringo's Favorite Numbers 3

一个符合条件的数字必须满足其是完全平方数，并且其平方根恰好有两个质因数。所以我们预处理它的满足条件的平方根。

筛出 $10^6$ 以内的所有数字，暴力枚举所有范围内的数字并判断，因为大于该数字平方根的质因数最多只会有一个，所以只需要枚举不超过该数字平方根的素数，剩下的质因子用前面的质数筛留的是否是质数表判一下就可以了。

由于剪枝会减掉很多，所以虽然理论复杂度根号但是跑得并不慢。

## [Code](https://atcoder.jp/contests/abc400/submissions/64541860)

---

## 作者：xiaoyin2011 (赞：0)

## AT_abc400_e [ABC400E] 最爱的数字 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc400_e)

### 题目大意

定义一种特殊的数，这种数具有如下性质：

- 这个数有且仅拥有两个质因子 $p_1$、$p_2$，且 $p_1 \ne p_2$。

- 对于这个数任一质因子 $p$，这个数刚好可以被 $p$ 整除偶数次。

给出 $Q$ 次查询，每次一个数 $A$，问不超过 $A$ 的最大这种特殊数大小。

### 思路及实现

试图改写这两条性质：

- 即这个数有且仅有两个不同的质因数。

- 这个数是个完全平方数。

可以这样理解第二条：如果把这个数放在根号下，那么能够整除两次的所有质因子都跑到根号外了，而原题性质二意味着它只有这样的质因子，最后根号下只有 $1$，所以是一个完全平方数。

现在问题转化为小于等于 $A$ 的最大的，恰好两个不同质因数的完全平方数。

因为是完全平方数，可以通过其算术平方根反找，完全平方数恰有两个质因数，所以平方根也恰有两个。因此，问题转化为小于等于 $\sqrt A$ 的最大的有两个不同质因数的数。

剩下的性质中，恰有两个不同质因数不好实现，考虑增序预处理所有包含这个性质的数，然后从中选出最大的不超过 $\sqrt A$ 的数，即 `upper_bound`。

现在，需要求 $1 \sim N$ 中每个数字的质因子数量，每一个去拆复杂度高达 $O(N\sqrt N)$，无法完成。因此，考虑筛法。

无论是埃氏筛还是欧拉筛，都对每个质数进行操作，将这个质数的倍数进行标记。同时，埃氏筛中某个合数恰好被它的质因子全都标记过一边，欧拉筛通过合数最多标记一次来优化。这里，我们可以选择埃氏筛，顺便记录下每个数字被标记的次数，即可。同时，$\sqrt A \le 10^6$ 对于 $O(N \log \log N)$ 还算可以。

最后，顺序遍历 $1 \sim N$，找出所有的恰有两个质因数的数字，并且放入序列 `twd` 中。这个序列是升序的，

---

这里也可以印证，如果前面选择直接把 $10^{12}$ 之内的完全平方数具有恰好两个质因子的数筛出来是不现实的，因此要先考虑完全平方数性质。

---

预处理部分：

```cpp
for (int p = 2; p <= 1000000; p++) // 10^6 埃氏筛
    if (cnt[p] == 0) // 没有标记过的质因数表示是个质数
        for (int m = p; m <= 1000000; m += p)
            cnt[m]++;
for (int k = 2; k <= 1000000; k++)
    if (cnt[k] == 2)
        twd.push_back(k);
```

查询部分：

```cpp
sr = sqrt(A) - 1;
while ((sr + 1) * (sr + 1) <= A) sr++; // 让 sr 回到小于等于 sqrt(A) 的最大整数
int it = upper_bound(twd.begin(), twd.end(), sr) - twd.begin() - 1;
if (it >= 0)
    printf("%lld\n", twd[it] * twd[it]);
else
    printf("0\n"); // 题目保证不可能到达这里
```

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll Q, A, sr;
ll cnt[1000005];
vector<ll> twd;
int main()
{
    for (int p = 2; p <= 1000000; p++)
        if (cnt[p] == 0)
            for (int m = p; m <= 1000000; m += p)
                cnt[m]++;
    for (int k = 2; k <= 1000000; k++)
        if (cnt[k] == 2)
            twd.push_back(k);
    scanf("%lld", &Q);
    while (Q--)
	{
        scanf("%lld", &A);
        sr = sqrt(A) - 1;
        while ((sr + 1) * (sr + 1) <= A) sr++;
        int it = upper_bound(twd.begin(), twd.end(), sr) - twd.begin() - 1;
        if (it >= 0)
            printf("%lld\n", twd[it] * twd[it]);
    }
    return 0;
}
```

---

## 作者：cyq32ent (赞：0)

我们发现，满足条件的 $N=p^{2n}q^{2m}$，其中 $p,q\in P$。所以， $N=(p^nq^m)^2$。我们通过素数筛法将小于等于 $\sqrt A$ 的素数全部筛出，再将小于等于 $\sqrt A$ 的素数的幂全部筛出，然后把素数的幂两两相乘得到的小于等于 $\sqrt A$ 的结果全部列出。我们得到的数都是 $\sqrt N$ 的候选。然后，对于每一个询问，我们在候选中找到小于等于 $\sqrt A$ 的最大值并平方即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int>prime,praw;
bool ip[1<<20];
int j;
void pm(){
	memset(ip,1,sizeof ip);
	for(int i=2;i<=5e5;i++)if(ip[i])
	for(prime.push_back(i),j=i<<1;j<=1e6;j+=i)ip[j]=0;
	int N=prime.size();
	for(int i=0;i<N;i++){
		int p=prime[i];
		for(int j=p*p;j<=1e6;j*=p)prime.push_back(j);
	}sort(prime.begin(),prime.end());
	for(auto k:prime){
		for(auto n:prime){
			if(k*n>1e6||n>=k)break;
			if(k%n)praw.push_back(k*n);
		}
	}sort(praw.begin(),praw.end());
}
signed main(){
	pm();
	int Q;cin>>Q;
	while(Q--){
		int N;cin>>N;
		int A=sqrtl(N);
		auto it=lower_bound(praw.begin(),praw.end(),A);
		int B=(*it==A)?A:(*--it);
		cout<<B*B<<endl;
	}
	return 0;
}
```

---

