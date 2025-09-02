# [ARC122E] Increasing LCMs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc122/tasks/arc122_e

長さ $ N $ の正整数列 $ A_1,A_2,\cdots,A_N $ があります． あなたは，これらの整数を並び替えることで，正整数列 $ x_1,x_2,\cdots,x_N $ を作ろうとしています． この時，$ x $ は以下の条件を満たす必要があります．

- $ y_i=\operatorname{LCM}(x_1,x_2,\cdots,x_i) $ と定義する．ここで，$ \operatorname{LCM} $ は与えられた整数たちの最小公倍数を返す関数である．このとき，$ y $ は狭義単調増加である．つまり，$ y_1\ <\ y_2\ <\ \cdots\ <\ y_N $ が成り立つ．

条件を満たすような $ x $ が存在するか判定し，存在するなら一つ例を示してください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 2\ \leq\ A_1\ <\ A_2\ \cdots\ <\ A_N\ \leq\ 10^{18} $
- 入力される値はすべて整数である

### Sample Explanation 1

$ x=(3,6,4) $ のとき， - $ y_1=\operatorname{LCM}(3)=3 $ - $ y_2=\operatorname{LCM}(3,6)=6 $ - $ y_3=\operatorname{LCM}(3,6,4)=12 $ となり，$ y_1\ <\ y_2\ <\ y_3 $ を満たします．

### Sample Explanation 2

どのように $ A $ を並び替えても条件を満たすことができません．

## 样例 #1

### 输入

```
3
3 4 6```

### 输出

```
Yes
3 6 4```

## 样例 #2

### 输入

```
3
2 3 6```

### 输出

```
No```

## 样例 #3

### 输入

```
10
922513 346046618969 3247317977078471 4638516664311857 18332844097865861 81706734998806133 116282391418772039 134115264093375553 156087536381939527 255595307440611247```

### 输出

```
Yes
922513 346046618969 116282391418772039 81706734998806133 255595307440611247 156087536381939527 134115264093375553 18332844097865861 3247317977078471 4638516664311857```

# 题解

## 作者：_⁢　 (赞：13)

> 神秘构造。

$a_i$ 能作为答案的末尾，当且仅当 $\gcd(a_i,\operatorname{lcm}_{j\neq i}(a_j))<a_i$，转换为 $\operatorname{lcm}_{j\neq i}(\gcd(a_i,a_j))<a_i$。

考虑倒序构造，每次在答案开头新增一个数 $x$。

设能作为 $x$ 的 $a_i$ 的集合为 $b$。随着 $a$ 内数的数量减少，$\operatorname{lcm}(a_i)$ 单调不升，因此 $b$ 内的数只会新增不会被移除。

每次任意选取 $b$ 内数放在答案开头即可。

无解当且仅当 $b$ 为空且 $a$ 不为空。由于 $b$ 内数不会被移除，该做法能保证正确性。（以答案的长度作为时刻，不存在某个 $a_i$ 在 $t$ 时刻能作为 $x$，在 $t+\Delta>t$ 时刻不行）

暴力枚举 $x$，时间复杂度 $\mathcal{O}(n^3\log a_i)$。

[提交记录](https://atcoder.jp/contests/arc122/submissions/38664919)。


---

## 作者：AKPC (赞：6)

本篇已通过，~~稍~~作修改。

本题可以采取数学归纳法的思想。

假设你已经把前 $i-1$ 个数字确定好了，如果要确定第 $i$ 个，那么 $\operatorname{lcm}\displaystyle_{j=1}^ix_j>\operatorname{lcm}\displaystyle_{j=1}^{i-1}x_j$，也即 $\operatorname{lcm}\{x_i,\operatorname{lcm}\displaystyle_{j=1}^{i-1}x_j\}>\operatorname{lcm}\displaystyle_{j=1}^{i-1}x_j$。

可以尝试倒序构造。假设剩余 $i$ 个数，并需要从这里选出一个数 $x_i$ 使得不包括 $x_i$ 的 $\operatorname{lcm}$ 小于这 $i$ 个数的总体 $\operatorname{lcm}$。暴力求这个 $x_i$ 的理论复杂度是 $\Theta(n^2\log n)$。总体复杂度为 $\Theta(n^3\log n)$。

但实际上，找到一个符合条件的 $x_i$ 就可以退出寻找了，$x_i$ 与 $x_{1\sim i-1}$ 的排布是没有相互影响的，所以这个复杂度会比理论小很多。

为什么找到一个符合条件的 $x_i$ 就可以退出？假设在 $i>2$ 个剩余数中，$o$ 存在 $i$ 个数中独有的因子，$p$ 也存在，那么当 $x_i$ 选择 $o$，$x_{i-1}$ 选 $p$ 亦然成立，反之也亦然。然而如果不存在 $p$，肯定在下一次 $i-1$ 个数的选择中是无解的。

值得注意的是，$\operatorname{lcm}\displaystyle_{j=1}^{i-1}x_j$ 的值可能过大，需要转换。钦定 $T=\operatorname{lcm}\displaystyle_{j=1}^{i-1}x_j$，则 $\operatorname{lcm}\{x_i,T\}>T$ ，即 $x_iT>T\gcd\{x_i,T\}$，即 $\gcd\{x_i,T\}<x_i$，这说明 $x_i$ 的所有因子不全被 $T$ 包含。

然而，根据唯一分解定理，假设 

$$a=p_1^{d1_1}p_2^{d2_1}\dots p_k^{dk_1},b=p_1^{d1_2}p_2^{d2_2}\dots p_k^{dk_2}$$

那么

$$\gcd\{a,b\}=p_1^{\min\{d1_1,d1_2\}}p_2^{\min\{d2_1,d2_2\}}\dots p_k^{\min\{dk_1,dk_2\}}$$

类似地，$\operatorname{lcm}$ 就是把 $\min$ 改成 $\max$。

据定理，

$$\gcd\{x_i,\operatorname{lcm}_{j=1}^{i-1}a_j\}=p_1^{\min\{d1_i,\max_{j=1}^{i-1}\{d1_j\}\}}p_2^{\min\{d2_i,\max_{j=1}^{i-1}\{d2_j\}\}}\dots p_k^{\min\{dk_i,\max_{j=1}^{i-1}\{dk_j\}\}}$$

对质因子 $p$ 的指数部分稍作转化，得到原式 

$$=p_1^{\max_{j=1}^{i-1}\{\min\{d1_j,d1_i\}\}}p_2^{\max_{j=1}^{i-1}\{\min\{d2_j,d2_i\}\}}\dots p_k^{\max_{j=1}^{i-1}\{\min\{dk_j,dk_i\}\}}=\operatorname{lcm}_{j=1}^{i-1}\{\gcd\{x_i,x_j\}\}$$

这样就可以达到本题的要求了。

[code](https://www.luogu.com.cn/paste/lv7t1ndt)。

---

## 作者：TianyiLemon (赞：6)

口胡一个不需要脑子的方法。

观察到 $A_i$ 能放在末尾当且仅当 $\operatorname{lcm}_{j\not= i}A_j$ 不能够整除 $A_i$，可以暴力找出这样的 $A_i$，然后递归求解 $n-1$ 个数的情况。

$\operatorname{lcm}_{j\not= i}A_j$ 可能很大，但是每个数不同的质因子个数不多，最多只有 $15$ 个。

用 Pollard Rho 分解质因数，求出每个质因子在序列中的出现次数，暴力判断即可。

时间复杂度 $O(n\sqrt[4]{\max{A_i}}+n^2)$。

---

## 作者：james1BadCreeper (赞：5)

考虑归纳构造。

$n=1$ 时显然成立。

对于 $n>1$，我们考虑找出这个序列的最后一个数。这最后一个数需要满足前面数的 $\operatorname{lcm}$ 不是它的倍数，也就是说 $\gcd(\operatorname{lcm}_{j\ne i}\{a_j\},a_i)<a_i$。这个式子相当于 $\operatorname{lcm}_{j\ne i}\{\gcd(a_j,a_i)\}<a_i$，这样就可以转化为规模为 $n-1$ 的问题。

由于 $\operatorname{lcm}$ 随着问题规模的减小不会上升，可以放在最后一个的 $a$ 越来越多，因此找到一个就放入答案不会使少掉可能的解。因此如果找不到这最后一个 $a$ 就无解。

时间复杂度 $O(n^3\log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64; 

int n; 
vector<i64> ans; 

i64 gcd(i64 x, i64 y) { if (y == 0) return x; return gcd(y, x % y); }
i64 lcm(i64 x, i64 y) { return x / gcd(x, y) * y; }

void solve(vector<i64> a) {
    if (a.size() == 1) return ans.emplace_back(a[0]), void(); 
    for (int i = 0; i < a.size(); ++i) {
        bool flag = 1; i64 l = 1;
        for (int j = 0; j < a.size(); ++j) if (i != j) l = lcm(l, gcd(a[j], a[i])); 
        if (l < a[i]) {
            ans.emplace_back(a[i]); 
            vector<i64> tmp; 
            for (int j = 0; j < a.size(); ++j) if (i != j) tmp.emplace_back(a[j]);
            solve(tmp); return; 
        }
    }
}

int main(void) {
    cin >> n; vector<i64> a(n); 
    for (int i = 0; i < n; ++i) cin >> a[i]; 
    solve(a); 
    if (ans.size() != n) puts("No"); 
    else {
        puts("Yes"); 
        reverse(ans.begin(), ans.end()); 
        for (i64 x : ans) cout << x << ' '; 
        cout << '\n'; 
    }
    return 0;
}
```

---

## 作者：0x3F (赞：3)

注意到如果一个序列合法，那么其子序列必然合法。

若一个元素 $A_i$ 可以放在末尾，那么必然满足 $\operatorname{lcm}(A_1,\cdots,A_{i-1},A_{i+1},\cdots,A_n)\ne\operatorname{lcm}(A_1,\cdots,A_n)$。

此时，若其他元素可以构成合法的序列，那么将 $A_i$ 放在末尾即可得到合法的原序列。反之若原序列合法，那么无论 $A_i$ 放在哪里，将其删去以后得到的子序列仍然合法。

因此将 $A_i$ 放在末尾不影响答案。删去 $A_i$ 后，剩下的 $A^{\prime}_{1\sim n-1}$ 继续计算，直到长为 $0$ 则合法，或找不到这样的 $A_i$ 则不合法。

但是上式的值太大了，无法直接计算。考虑转化为 $\operatorname{lcm}\left[\gcd(A_1,A_i),\cdots,\gcd(A_{i-1},A_i),\gcd(A_{i+1},A_i),\cdots,\gcd(A_n,A_i)\right]\ne A_i$，左式的值不会超过 $A_i$，可以直接计算。

时间复杂度为 $\mathcal{O}(n^3\log V)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long a[110];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    bool flg = true;
    for (int k = n; k >= 1; k--) {
        bool ok = false;
        for (int i = 1; i <= k; i++) {
            long long num = 1LL;
            for (int j = 1; j <= k; j++) {
                if (j != i) {
                    long long tmp = __gcd(a[i], a[j]);
                    num *= tmp / __gcd(tmp, num);
                }
            }
            if (num != a[i]) {
                swap(a[i], a[k]);
                ok = true;
                break;
            }
        }
        if (!ok) {
            flg = false;
            break;
        }
    }
    if (flg) {
        cout << "Yes" << endl;
        for (int i = 1; i <= n; i++) {
            cout << a[i];
            if (i != n) cout << ' ';
        }
        cout << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
```

---

## 作者：Leasier (赞：2)

- **正难则反。**

直接正着考虑加数是很麻烦的，因为我们很难表述出前面有哪些数。

但注意到若我们先填最后一个数，则它前面的数就是剩下的所有数，这是确定的。

首先考虑判断钦定最后一个数为 $a_i$，则 $\operatorname{lcm}_{j = 1}^n a_j > \operatorname{lcm}_{j \neq i} a_j$。

这个条件比较神秘，但注意到若我们设 $M = \operatorname{lcm}_{j \neq i} a_j$，则该条件等价于 $\operatorname{lcm}(M, a_i) > M$，或言之 $\gcd(M, a_i) < a_i$。

但是 $M$ 很大，我们还是不好处理。又注意到 $\gcd(M, a_i) = \operatorname{lcm}_{j \neq i} \gcd(a_j, a_i)$，于是我们就可以比较方便地判断了。

于是一个简单的想法就是从后到前确定每个 $x_i$ 的值，那这样对不对呢？

注意到删去一个 $x_i$ 后 $x$ 仍然合法，于是若不能确定任何一个数作为当前 $x_i$ 则一定无解。

模拟上述过程即可。时间复杂度为 $O(n^3 \log w)$，其中 $w$ 为值域 $10^{18}$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;
typedef __int128 lll;

ll a[107], b[107][107], ans[107];
bool vis[107];

ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a % b);
}

inline ll lcm(ll a, ll b){
	return (lll)a * b / gcd(a, b);
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			b[i][j] = gcd(a[i], a[j]);
		}
	}
	for (int i = n; i >= 1; i--){
		bool flag = false;
		for (int j = 1; j <= n; j++){
			if (!vis[j]){
				ll cur_val = 1;
				for (int k = 1; k <= n; k++){
					if (k != j && !vis[k]) cur_val = lcm(cur_val, b[j][k]);
				}
				if (cur_val < a[j]){
					vis[j] = flag = true;
					ans[i] = a[j];
					break;
				}
			}
		}
		if (!flag){
			printf("No");
			return 0;
		}
	}
	printf("Yes\n");
	for (int i = 1; i <= n; i++){
		printf("%lld ", ans[i]);
	}
	return 0;
}
```

---

## 作者：wangtairan114 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc122_e)

## 思路
  题意比较好理解。观察到直接写不好做，考虑倒做。如果第 $i$ 个位置放 $x_i$，需要满足 $\gcd(\operatorname{lcm}(x_i,x_j)) < x_i$，其中 $j \in [1,i)$。转变式子，推得 $\operatorname{lcm}(\gcd(x_i,x_j)) < x_i$。

同时发现，如果有 $a_x$，$a_y$ 均能够放在位置 $i$，那么放置 $a_x$，$a_y$ 的先后顺序对于答案无影响。

倒着枚举每一位即可。时间复杂度 $O(n^3\log|a_i|)$。

## 代码
```
#include <bits/stdc++.h>
using namespace std;
#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)<(b)?(b):(a))
#define INF 0x3f3f3f3f
#define ll long long
#define sc scanf
#define pr printf
#define v1 first
#define v2 second
#define f(nm1,nm2,nm3) for(int nm1=nm2; nm1<= nm3; nm1++)
#define lowbit(x) (x&(-x))
int n;
ll a[105];
ll gcd(ll x,ll y){
    if(x<y)
        swap(x,y);
    return (x%y==0)?(y):(gcd(y,x%y));
}
__int128 lca(__int128 x,__int128 y){
    return x*y/gcd(x,y);
}
bool b[105];
vector<ll> v;
int main()
{
    sc("%d",&n);
    for(int i=1; i <= n; i++)
        sc("%lld",&a[i]);
    for(int i=n-1; i >= 0; i--){
        bool ok2=0;//判断位置i是否有合法答案
        for(int j=1; j <= n; j++){
            if(b[j])
                continue;
            __int128 res=1;
            bool ok=1;//判断a_j是否合法
            for(int l=1; l <=n; l++){
                if(l==j||b[l])
                    continue;
                res=lca(gcd(a[j],a[l]),res);
                if(res>=a[j]){
                    ok=0;
                    break;
                }
            }
            if(ok){
                ok2=1;
                b[j]=1;
                v.push_back(a[j]);
                break;
            }
        }
        if(!ok2){
            pr("No\n");
            return 0;
        }
    }
    pr("Yes\n");
    reverse(v.begin(),v.end());//逆序输出
    for(auto y: v)
        cout << y << " ";
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

认准一个黄金原则：正难则反。

为什么这道题“正难”呢？因为它会影响到后面的，而且你不知道具体会影响什么。

那反着来呢？虽然你并不知道正着的排列，但是只要数一确定，其最小公倍数也是确定的，因此可以用来检验能不能选这个数。

至此，思路已经明确：倒序枚举每个位置选什么，检查合法与否，合法则选择并递归处理上一个位置。

时间复杂度：$n$ 的枚举位置，$n$ 的枚举数，$n\log V$ 的检查合法性，总复杂度 $n^3\log V$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[105]; stack<int>ans; bitset<108>vis;
inline int lcm(const int&l,const int&r){
	return l/__gcd(l,r)*r;
}
inline bool check(int v,int id){
	int lv=1;
	for(int i=1;i<=n;++i)
		if(!vis[i]&&i!=id&&(lv=lcm(lv,__gcd(v,a[i])))==v)
			return 0;
	return 1;
}
inline bool solve(int lt){
	if(!lt) return 1;
	for(int i=1;i<=n;++i)
		if(!vis[i]&&check(a[i],i)){
			vis[i]=1; ans.emplace(a[i]);
			if(solve(lt-1)) return 1; 
			vis[i]=0; ans.pop();
		}
	return 0;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n; for(int i=1;i<=n;++i) cin>>a[i];
	if(!solve(n)){ cout<<"No\n"; return 0; }
	cout<<"Yes\n";
	while(ans.size()) cout<<ans.top()<<" ",ans.pop();
}
```

---

## 作者：phil071128 (赞：1)

### [ARC122E] Increasing LCMs

> 给定序列 $a$，构造一种重新排序的方案使得其前缀 LCM 严格递增。

考虑**归纳构造（倒序构造）**。

$n=1$ 显然成立。

对于 $n>1$，我们考虑任意找出这个序列的最后一个数，满足题目要求 $\text{lcm}(a_j)<\text{lcm}(\text{lcm}(a_j),a_i),j\ne i$，就选择其作为当前序列最后一项，问题变成一个 $n-1$ 的子问题。

**引理：** 一个序列合法，那么其任意子序列都合法。

很好感性理解，理性证明的话，考虑 $\text{lcm}$ 的实质是质因数分解后，对一串底数的指数取 $\max$，也就是说合法序列中每一个 $i>1$ 的位置，其至少有一个质因数的指数是其前缀 $\max$，前缀 $\max$ 单调不降，所以删掉可以保证后面依旧合法。

回到原问题，我们要证明这样任意选择，不会使得**答案的总数减少**。考虑一个可能成为最终答案的答案，满足最后一项不是 $a_i$，那么把 $a_i$ 删掉，根据引理可得此时依旧合法，变成一个大小为 $n-1$ 的子问题，再从后面加上 $a_i$，根据构造规则这样依旧合法。

**经典套路：** 求一串数的 lcm 常常因为太大无法保存，如果值域较小可以存质因数的指数，但本题值域高达 $10^{18}$，需要转换条件：$a_i$ 存在一个严格最大指数，而 gcd 相当于取 min，因此转换为 $\text{lcm} (\text{gcd}(a_i,a_j))<a_i$。

 
```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=105;
int a[N],b[N];
int lcm(int a,int b){
	return a/__gcd(a,b)*b;
}
void work(int n) {
	if(n==1) {
		b[1]=a[1];
		return ;
	}
	for(int i=1;i<=n;i++) {
		int res=1;
		for(int j=1;j<=n;j++) {
			if(i==j) continue;
			res=lcm(res,__gcd(a[i],a[j]));
		}		
		if(res<a[i]) {
			b[n]=a[i];
			for(int j=i;j<=n-1;j++) a[j]=a[j+1];
			work(n-1);
			return ;
		}
	}
}
signed main(){
//	fil();
	int n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	work(n);
	if(b[1]) {
		puts("Yes");
		for(int i=1;i<=n;i++) cout<<b[i]<<" ";
		cout<<endl;
		return 0;
	}
	puts("No");
	return 0;
}

```

---

## 作者：Code_星云 (赞：1)

由于正序处理的话限制很多，所以考虑倒着放。

具体的，我们对于每一位枚举能放的数，其限制条件即为前面数的最小公倍数不能把该数除尽。这样做的正确性证明如下：若对于一个数能放在前面（非末尾）的话，也一定能够放在后面，而通过反证法和递归构造则可以说明。

需要注意的是，由于数据很大，判最小公倍数那里要改一下。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;
#define int long long

const int N = 205;
int n, a[N], bar[N];
bool vis[N] = {false};

int gcd(int a, int b){
	if(b == 0) return a;
	return gcd(b, a % b);
}
int lcm(int a, int b){
	return a / gcd(a, b) * b;
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	for(int i = n; i >= 1; i --){
		int flag = 0;
		for(int j = 1; j <= n; j ++) if(vis[j] == 0){
			int tmp = 1;
			for(int k = 1; k <= n; k ++) 
			  if(vis[k] == 0 && k != j)
			    tmp = lcm(tmp, gcd(a[j], a[k]));
			if(tmp < a[j]){
				vis[j] = true; flag = a[j];
				break;
			}
		}
		if(! flag){
			puts("No");
			return 0;
		}
		bar[i] = flag;
	}
	puts("Yes");
	for(int i = 1; i <= n; i ++) printf("%lld ", bar[i]);
	puts(""); return 0;
}
```


---

## 作者：ListenSnow (赞：1)

### 思路：

如果 $A_i$ 可以放在数组的末尾，那么一定满足 $\mathrm{LCM} _{j \ne i}(\mathrm{GCD} (A_i,A_j))<A_i$。

对于这样的数，只要有解，那么 $A_i$ 必然可以放到数组的最后面，证明如下：

假设存在一个 $A_i$，单独考虑它时，可以放在数组的最末尾。而有解时，只能放在数组中间的某一个位置 $j$，那么此时将 $A_i$ 移动到数组的末尾，对于 $1 \sim j-1$ 位置上的数没有影响，而对于 $j+1 \sim n$ 位置上的数，删去 $A_i$ 后前缀 $\mathrm{LCM} $ 依旧单调递增。根据假设前提，$A_i$ 可以放到最后一位，那么 $A_i$ 放在数组末尾依旧是一组合法的解。故结论成立。

那么只需要倒序填数，每次找到一个可以填上的数就填上去。根据前面的结论，如果有解，那么这样做一定可以找到一组解。

### code：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=110;
#define LL long long
LL a[N],ans[N];int n;bool vis[N];
LL gcd(LL a,LL b){return b==0ll?a:gcd(b,a%b);}
LL lcm(LL a,LL b){return a/gcd(a,b)*b;}
int main()
{
	scanf("%d",&n);for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=n;i>=1;i--)
	{
		bool ok=false;
		for(int j=1;j<=n;j++)
		{
			if(vis[j]) continue;LL l=1;
			for(int k=1;k<=n;k++) if(k!=j&&!vis[k]) l=lcm(l,gcd(a[j],a[k]));
			if(l!=a[j]){ans[i]=a[j];ok=true;vis[j]=true;break;}
		}
		if(!ok) return puts("No"),0;
	}
	puts("Yes");for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

一个简单直接的想法是从前往后 ``push_back``，探究一个数能在前面有若干个数的情况下能够成功插入的条件。很不幸，无法直接写成我们可以利用的形式。

**考虑从后往前插入**。具体地，我们考虑一个数 $a_i$ 能够成为最后一个数的条件：显然为 $\operatorname{lcm} \limits_{j \neq i} a_j < \operatorname{lcm}_{i=1}^{n} a_i$。这看起来也没有什么前途对吧，但是：

>断言：当一个数 $a_i$ 被插到最后一个位置之后，如果之前另外一个数 $a_j$ 之前能够硬塞到未确定序列的最后，之后也可以。
>
>证明：令 $f(a,p)$ 为 $a$ 在唯一分解中 $p$ 的指数位置。则条件相当于存在一个 $p$，使得 $f(a_j,p) > \max_{i \neq j}f(a_i,p)$。显然后者在删除一个数之后不增，也即之前成立的 $p$ 在之后依然成立。故结论得证。

>断言：不会有两个终局状态 $S_1,S_2$ 使得 $S_1 \cap S_2 \neq \emptyset$。
>
>证明：假设有两个终局状态 $S_1$ 与 $S_2$，考虑其路径 $P_1,P_2$。定义一次操作为：对于一个集合 $S$ 以及一个位置 $i$，如果其已经在 $S$ 了，不用管，否则将其加入 $S$。则按照 $P_1$ 的顺序操作一轮之后再按照 $P_2$ 的顺序操作一轮之后即可得到 $S_1 \cup S_2$，与 $S_1$ 是终局状态矛盾。

于是每次直接挑一个数放在未确定集合的末尾即可。

直接计算 $\operatorname{LCM}$ 可能会爆 ``long long``,可以采用 $\operatorname{lcm}_{j \neq i} \operatorname{gcd}(a_j,i) < a_i$ 来判别。时间复杂度 $O(n^3 \log n)$。

---

## 作者：Zelotz (赞：0)

使用归纳法。

对于 $n>1$，我们考虑找出这个序列的最后一个数。

最后一个数需要满足前面数的 $\operatorname{lcm}$ 不是它的倍数，也就是说 $a_i \nmid \operatorname{lcm}_{j \ne i }a_j$。

这个式子相当于 $\operatorname{gcd}(a_i,\operatorname{lcm}_{j \ne i }a_j) < a_i$。

但是 $\operatorname{lcm}$ 太大，把式子转化一下。

$$
\operatorname{lcm}_{j\ne i}\{\gcd(a_j,a_i)\}< a_i $$

满足这个式子的 $a_i$ 则可以作为序列的最后一个数，注意到 $\operatorname{lcm}$ 随着问题规模的减小不会上升，故找到一个可行的 $a_i$ 就放入答案是正确的。问题变为规模为 $n-1$ 的问题，递归即可。

```
#define int ll
const int N = 500 + 5;
int n; 
vector <int> ans;
int lcm(int x, int y) {return x / __gcd(x, y) * y;}
void solve(vector <int> v) {
    if (v.size() == 1) return ans.push_back(v[0]), void();
    R(i, 0, v.size() - 1) {
        int L = 1;
        R(j, 0, v.size() - 1) {
            if (i == j) continue;
            L = lcm(L, __gcd(v[i], v[j]));
        }   
        if (L < v[i]) {
            ans.push_back(v[i]);
            vector <int> t; 
            R(j, 0, v.size() - 1) if (i != j) t.push_back(v[j]);
            solve(t);
            return ;
        }
    }
    puts("No"); exit(0);
}
signed main() {
    cin >> n; vector <int> v(n);
    R(i, 1, n) cin >> v[i - 1];
    solve(v);
    reverse(ans.begin(), ans.end());
    puts("Yes");
    for (int x : ans) cout << x << ' ';
    return 0;
}
```

---

## 作者：win114514 (赞：0)

感觉像比较套路的构造题。

### 思路

假如我们正着进行构造，可以发现我们加入一个数以后，对后面的数产生的影响是很大的。

但是如果我们从最后一个数开始构造，那么可以发现它是不会对之后的构造产生任何影响的。

应为越前面的数的限制会越少，那么可以填的数一定是不减的。

一个数可以填在后面，那么也一定可以填在前面。

所以我们现在只需要不断找到可以填的数即可。

考虑限制是什么。

要求：

$$
a_i\not |\operatorname{lcm}_{i=1}^{j-1}a_j
$$

但是 $\operatorname{lcm}$ 太大了，我们需要简化一下，相当于：

$$
\gcd(a_i,\operatorname{lcm}_{i=1}^{j-1}a_j)<a_i
$$

$$
\operatorname{lcm}_{i=1}^{j-1}\gcd(a_i,a_j)<a_i
$$

这样就可以处理了。

时间复杂度：$O(n^3\log n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, a[110], b[110], v[110];

inline int lcm(int x, int y) {
  int g = __gcd(x, y);
  return (__int128) x * y / g;
}

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = n; i >= 1; i--) {
    for (int j = 1; j <= n; j++) {
      if (v[j]) continue;
      int x = 0;
      for (int k = 1; k <= n; k++) {
        if (v[k] || k == j) continue;
        if (x == 0) x = __gcd(a[j], a[k]);
        x = lcm(__gcd(a[j], a[k]), x);
      }
      if (x < a[j]) {
        v[j] = 1, b[i] = a[j];
        break;
      }
    }
    if (b[i] == 0) cout << "No\n", exit(0);
  }
  cout << "Yes\n";
  for (int i = 1; i <= n; i++) cout << b[i] << " \n"[i == n];
}
```

---

## 作者：ethan0328 (赞：0)

## 思路

题意其实就是每位填的数要保证 $\gcd(\text{lcm}_{j<i}(x_j),x_i) \ne x_i$。

考虑从后往前填数，每次只要把任意满足条件的填入即可。

注意到 $\gcd(\text{lcm}_{j<i}(x_j),x_i)$ 其实相当于 $\text{lcm}_{j<i}(\gcd(x_j,x_i))$，然后就可以直接枚举做了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=110;
int n,a[N],out[N],pre[N][N];
bool vis[N];
int gcd(int x,int y)
{
    if(x>y)
    {
        swap(x,y);
    }
    if(x==0)
    {
        return y;
    }
    return gcd(y%x,x);
}
int lcm(int x,int y)
{
    return x/gcd(x,y)*y;
}
signed main()
{
    int x;
    bool flg;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            pre[i][j]=gcd(a[i],a[j]);
        }
    }
    for(int i=n;i;i--)
    {
        flg=0;
        for(int j=1;j<=n;j++)
        {
            if(vis[j])
            {
                continue;
            }
            x=1;
            for(int k=1;k<=n;k++)
            {
                if(j==k||vis[k])
                {
                    continue;
                }
                x=lcm(x,pre[j][k]);
            }
            if(x!=a[j])
            {
                flg=1;
                out[i]=a[j];
                vis[j]=1;
                break;
            }
        }
        if(!flg)
        {
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++)
    {
        cout<<out[i]<<" ";
    }
}
```

---

## 作者：arundo (赞：0)

[ARC122E] Increasing LCMs 题解。

尝试为序列选择一个末位，并规约到子问题。

能作为末尾的数可以简单求出，只需要包含/不包含其的 LCM 不相同即可，也就是说能在前面的数的基础上产生新的因子。可以说明的是，任意一个合法的数作为末尾都是一样的，因为可以将一个合法序列中该数挪到末尾，形成新的合法序列。然后继续处理子问题即可。

时间复杂度 $O(n^3\log n)$。

---

一个另外的细节是，基础款判断条件是 $a_i\nmid\text{LCM}_{j\neq i}(a_j)$，后面的部分无法直接求出。

尝试改写为 $\text{LCM}_{j\neq i}(\text{GCD}(a_i,a_j))\neq a_i$ 即可。

---

## 作者：aaaaaaaawsl (赞：0)

考虑从后往前放。

如果一个数被放在了最后，那么前面数的 $\operatorname{lcm}$ 一定不是这个数的倍数，这样加入这个数后 $\operatorname{lcm}$ 才能扩大。

也就是 

$$\gcd(a_j,\operatorname{lcm}(a_i)_{i \neq j}) \neq a_j$$

换一种说法也就是前面的数和它的最大公因数不能把它完全包含，即 

$$\operatorname{lcm}(\gcd(a_i, a_j)) < a_j$$


考虑第二种说法的式子，当某些数被选走后，由于 $a_i$ 数量变少，$a_j$ 大小不变（不管选没选走），剩下的数的 $\operatorname{lcm}(\gcd(a_i, a_j))$ 一定不会增大，如果某个数在某个状态可以当做结尾，那么它之后也一定能当做结尾。所以每次在可以作为结尾的数里任意取一个即可。

枚举放倒数第几个，枚举把哪个数当做结尾，枚举没被选的数，加上 $\gcd$ 的计算，时间复杂度为 $O(n^3\log V)$。

实测时间很充裕。[Submission](https://atcoder.jp/contests/arc122/submissions/47402116)。

-----

代码

``` cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#define int long long

using namespace std;

inline int read(){
	register int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f;
}

const int N = 1e2 + 10;
int n, flag;
int a[N], use[N], ans[N];

inline int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

signed main(){
	n = read();
	for(int i = 1; i <= n; ++ i) a[i] = read();
	for(int r = n; r > 1; -- r){
		flag = 0;
		for(int now = 1; now <= n; ++ now){
			if(use[now]) continue; int gd = 0, lcm = 0;
			for(int ck = 1; ck <= n; ++ ck){
				if(use[ck] || ck == now) continue;
				gd = gcd(a[ck], a[now]);
				lcm = (lcm == 0 ? gd : gd / gcd(gd, lcm) * lcm);
			}
			if(lcm < a[now]){
				ans[r] = a[now]; flag = 1;
				use[now] = 1; break;
			}
		}
		if(flag == 0) {
			puts("No");
			return 0;
		}
	}
	for(int i = 1; i <= n; ++ i) if(!use[i]) ans[1] = a[i];
	puts("Yes");
	for(int i = 1; i <= n; ++ i) printf("%lld ", ans[i]);
	return 0; 
}
```

你大洛谷 AT 绑不上什么时候处理。

---

