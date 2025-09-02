# [ARC135C] XOR to All

## 题目描述

给定 $n$ 个非负整数 $a_1,a_2,\dots,a_n$，你可以执行以下操作任意（可以为零）次：

- 选择一个数 $x\in \{a_1,a_2,\dots,a_n\}$。

- 对于所有 $a\leq i\leq n$，将 $a_i$ 修改为 $a_i\oplus x$，其中 $\oplus$ 表示按位异或操作。

请你最大化操作后 $\sum_{i=1}^na_i$ 的值。

## 说明/提示

- $1\leq n \leq 3\times 10^5$
- $0\leq a_i<2^{30}$

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
19```

## 样例 #2

### 输入

```
5
10 10 10 10 10```

### 输出

```
50```

## 样例 #3

### 输入

```
5
3 1 4 1 5```

### 输出

```
18```

# 题解

## 作者：ran_qwq (赞：9)

结论题。

记第 $k$ 次异或变换的 $A$ 数组为 $A_k$，初始为 $A_0$。

若第一次选取 $x=p$，则 $A_1$ 除了 $A_1^p$ 为 $0$，其它都从 $A_0^i$ 变为了 $A_0^i\oplus A_0^p$。

若第二次选取 $x=q$，则 $A_2$ 除了 $A_2^q$ 为 $0$，其它都从 $A_1^i=A_0^i\oplus A_0^p$ 变为了 $A_0^i\oplus A_0^p\oplus A_1^q=A_0^i\oplus A_0^p\oplus A_0^q\oplus A_0^p=A_0^i\oplus A_0^q$。

所以每一次变换都把前一次的给消掉了，换句话说，只用操作一次就能和最大。

统计每一二进制位为 $1$ 的个数 $c_i$，选择第 $i$ 个数，若它第 $j$ 为为 $1$，则对于第 $j$ 位，对总和进行了 $2^j\times(n-c_j\times2)$ 的贡献。求出每个数贡献和取最大值就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,ans,sum,a[N],b[N][32],c[32];
void solve()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read(),ans+=a[i],sum+=a[i];
		for(int j=0;j<30;j++)
			if(a[i]&(1<<j)) b[i][j]=1,c[j]++;
	}
	for(int i=1;i<=n;i++)
	{
		int tot=sum;
		for(int j=0;j<30;j++) tot+=b[i][j]*(n-c[j]*2)*(1<<j);
		ans=max(ans,tot);
	}
	write(ans,"");
}
signed main()
{
	int T=1;
	while(T--) solve();
}
```

---

## 作者：Pretharp (赞：2)

## 思路

先玩一遍。

假如我们从位置 $i$ 选取 $x$，那么整个数列除了 $A_i$ 变成 $0$，其它的从 $A_k$ 变为了 $A_k \oplus A_i$。如果我们再从位置 $j$ 选取 $x$，那么 $A_i$ 从 $0$ 变为了 $A_j \oplus A_i$，$A_j$ 变为了 $0$，其它的从 $A_k$ 变成了 $A_k \oplus A_i \oplus A_j \oplus A_i=A_k \oplus A_j$。

发现了什么？是的，当你第二操作时你会发现第一次操作的影响被抵消掉了，第三次及以后操作同理，所以不管你操作多少次，最后只有最后一次操作会生效。

接下来就变成了板子了，具体看代码。

## 代码

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define int long long
const int N=3e5+5,K=35;
int n,a[N],b[K][2],ans;
// n 和 a[] 见题意，b[i][j] 是记录整个区间内所有数二进制下第 i 位的 j 的个数（j ∈ {0,1}）
signed main()
{
//	freopen("input.in","r",stdin);
//	freopen("output.out","w",stdout);
	cin.tie(0),cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans+=a[i]; // 这一步是记录不操作的情况。
		for(int j=0;j<K-2;j++){
			b[j][1&(a[i]>>j)]++;
		}
	}
	for(int i=1,cnt;i<=n;i++){
		cnt=0;
		for(int j=0;j<K-2;j++){
			cnt+=(b[j][!(1&(a[i]>>j))]<<j);
		}
		ans=max(ans,cnt);
	}
	return cout<<ans<<endl,0;
}
```

---

## 作者：cppcppcpp3 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc135_c)。

## Solution

诈骗题。

第一次操作后变为 $p_x=a_x \oplus a_y$，第二次操作后变为 $q_x=p_x \oplus p_z=a_x \oplus a_y \oplus a_z \oplus a_y=a_x \oplus a_z$。看得出第二次操作后第一次操作带来的影响被消去了。

所以**最多操作一次**就能得到答案。

先令 $ans=\sum_{i=1}^n a_i$。记 $b_{i,j}$ 为 $a_i$ 二进制下的第 $j$ 位的值，$c_j=\sum_{i=1}^{n}b_{i,j}$。把 $a_i$ 按位拆开，计算以它为 $x$ 的结果：若 $b_{i,j}=1$，则在第 $j$ 位上的贡献为 $2^j (n-c_j)$；否则为 $2^j \times c_j$。所有的结果同 $ans$ 取 $\max$ 即可。
复杂度 $O(30 \times n)$。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=3e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,a[N],c[31],ans,p,q;
int b[N][31];

void solve1(){
	for(int i=1;i<=n;++i){
		int tot=0;
		for(int j=1;j<=n;++j) tot+=(a[i]^a[j]);
		ans=max(ans,tot);
	}
}

main(){
	n=wrd();
	for(int i=1;i<=n;++i) ans+=(a[i]=wrd());
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) for(int j=0;j<31;++j) if((a[i]>>j)&1) b[i][j]=1;
	
	for(int i=0;i<31;++i){
		for(int j=1;j<=n;++j) c[i]+=b[j][i];
	} 
	
	for(int i=1;i<=n;++i){
		int tot=0;
		for(int j=0;j<31;++j){
			if(b[i][j]) tot+=((n-c[j])*(1<<j));
			else tot+=(c[j]*(1<<j));
		} 
		ans=max(ans,tot);
	}
	
	return printf("%lld",ans),0;
}
```

---

## 作者：TemplateClass (赞：0)

我们定义二进制下权值为 $2 ^ w$ 的那一位为第 $w$ 位。

假设第一次 $\oplus\ x$，那么 $a' _ i = a _ i \oplus x$。然后第二轮挑选一个 $a' _ p$，于是 $a''_i = (a _ i \oplus x) \oplus (a _ p \oplus x) = a _ i \oplus a _ p$。

也就是说，上一次操作异或的数会在下一次操作的时候被消掉。换言之，也就是只用操作 $0$ 或 $1$ 次就可以使 $\sum a _ i$ 最大。

设 $c _ i$ 表示序列 $a$ 中的元素在二进制下的第 $i$ 位是 $1$ 的个数。如果要异或的数 $x$ 的第 $i$ 位是 $1$，那么它会给总和带来的贡献如下：

- 有 $c _ i$ 个数在第 $i$ 位会被消掉，所以带来 $-2 ^ i c _ i$ 的贡献；
- 有 $n - c _ i$ 个数在第 $i$ 位会获得 $1$，所以带来 $2 ^ i (n - c _ i)$ 的贡献。

于是加起来取一个 $\max$ 就完了。

```cpp
#include<iostream>
#include<algorithm>

typedef long long ll;
typedef unsigned long long ull;

constexpr int N = 3e5 + 5;
constexpr int M = 30 + 1;

int n, a[N], c[M], b[N][M]; ull sum = 0;

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		std::cin >> a[i]; sum += a[i];
		for(int j = 0; j < M; ++j) {
			if(a[i] & (1 << j)) {
				b[i][j] = 1; ++c[j];
			}
		}
	}
	
	ull ans = sum;
	for(int i = 1; i <= n; ++i) {
		ull val = 0;
		for(int j = 0; j < M; ++j) {
			if(!b[i][j]) continue;
			val += (1ull << j) * (n - 2 * c[j]);
		}
		ans = std::max(ans, sum + val);
	}
	
	std::cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

# 题面

给定一个长度为 $n$ 的序列 $a$，可以进行若干次操作，每次操作可以从 $a$ 中选择一个数 $a_i$，并且让所有 $a_j$ 变成 $a_i \oplus a_j$，求操作之后 $\sum_{i=1}^{n}a_i$ 的最大值。

# 分析

思考操作几次后最优。如果我们先选择 $a_i$，然后再选择 $a_j$，结果会怎样。

第一次操作后，$a_i \to 0,a_j \to a_i \oplus a_j,a_k \to a_i \oplus a_k$。

第二次操作后，$a_i \to 0 \to a_ i \oplus a_j,a_j \to a_i \oplus a_j \to 0,a_k \to a_i\oplus a_k \to (a_i \oplus a_k) \oplus (a_i \oplus a_j) = a_k \oplus a_j$。

可以发现，操作两次之后的效果和直接操作 $a_j$ 的效果是等价的，所以实际上我们只需要操作一次即可。

至于求 $\sum_{i=1}^{n}a_i \oplus x$ 的 $O(\log x)$ 做法就不用多讲了吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 300005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), a[N], t[35], ans;
int main(){
	for (int i = 1; i <= n; i++){
		a[i] = rd();
		ans += a[i];
		for (int j = 0; j <= 30; j++) t[j] += ((a[i] >> j) & 1);
	}
	for (int i = 1; i <= n; i++){
		ll sum = 0;
		for (int j = 0; j <= 30; j++) sum += ((((a[i] >> j) & 1) ? n - t[j] : t[j]) << j);
		ans = max(ans, sum);
	}
	printf ("%lld\n", ans);
	return 0;
}

```

---

## 作者：User_Unauthorized (赞：0)

## 题意

给定 $N$ 个非负整数 $A_1, A_2, A_N$，定义每次操作如下：

1. 选取一个数 $x \in \{A_!, A_2, \cdots, A_N\}$。

2. 对于所有的 $1 \le i \le N$，进行 $A_i \leftarrow A_i \oplus x$。

你可以进行若干次操作（可以不进行操作），最大化 $\sum\limits_{i = 1}^{N}A_i$。

（$1 \le N \le 3 \times 10^5$）

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ARC135C.html)

首先，设初始序列为 $A$，进行过任意次操作后的序列为 $B$。

对于一次操作，设我们这次选取的数为 $B_i$，我们考察本次操作对其他整数（$i \neq j$）的影响。

由于在这次操作前可能会进行其他操作，所以 $B_i$ 和 $B_j$ 实际上可以表达为 $A_i \oplus x$ 和 $A_j \oplus x$，那么我们完成操作后，有

$$B_j \leftarrow B_i \oplus B_j = (A_i \oplus x) \oplus (A_j \oplus x) = A_i \oplus A_j$$

所以我们可以得出结论：在多次操作的过程中，最后一次操作会将之前的所有操作的影响撤销。也就是说，我们最多只需要操作一次即可。

下面我们讨论如何操作使得最终的和最大，考虑按二进制位考虑当前操作对总和的影响，所以我们可以预处理出二进制下每一位原序列中为 $1$ 的数的个数，然后遍历序列，计算出选取当前数对答案的影响即可。

总复杂度 $\mathcal{O}(N \log A)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MAXB = 31;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    ValueVector A(N);

    for (auto &iter: A)
        std::cin >> iter;

    ValueVector B(MAXB, 0);

    for (auto const &iter: A) {
        for (valueType i = 0; i < MAXB; ++i) {
            if (iter & (1 << i))
                --B[i];
            else
                ++B[i];
        }
    }

    valueType const base = std::accumulate(A.begin(), A.end(), (valueType) 0);

    valueType ans = base;

    for (auto const &iter: A) {
        valueType sum = 0;

        for (valueType i = 0; i < MAXB; ++i)
            if (iter & (1 << i))
                sum += B[i] * (1 << i);

        ans = std::max(ans, base + sum);
    }

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc135_c)
# 题目描述
有数组 $a$，其中可执行操作任意次（当然可以不操作），每一次操作可以选定数组中一个数 $a_{i}$，使得 $\forall k\in a,a_{k}=a_{k}\oplus a_{i}$。求 $\max{\sum\limits_{i=1}^{n}a_{i}}$。
# 题目分析
## 首先模拟一波
让我们先试着操作一次，不妨设改的数是 $a_{i}$。显然，$a_{i}\oplus a_{i}=0$，换句话说就是“牺牲”一个数，使剩余的数都与它异或。

第一次数组更改为：$a_{t}\oplus a_{i},t\in [1,n]$。

设第二次更改的数是 $a_{j}$。

则第二次数组更改为：$(a_{t}\oplus a_{i})\oplus(a_{j}\oplus a_{i})$ 即为 $a_{t}\oplus a_{j}$。相较于更改 $a_{j}$，还有一项 $a_{i}\oplus a_{j}$ 消失了。所以 **更改一次一定比更改两次更优**。

同理，更改 $k$ 次一定比更改一次更优，其中 $(k>1)$。
### 结论
本题中修改次数 $k$ 不是 $0$ 就是 $1$。换句话说，要么不修改，要么修改一次。

## 方法
记 $b_{i,j}$ 为 $a_i$ 二进制下的第 $j$ 位的值，$c_j=\sum_{i=1}^{n}b_{i,j}$。

若 $b_{i,j}=1$，则在第 $j$ 位上的贡献为 $(n-c_{j})\times 2^{j}$；否则为 $c_{j}\times 2^{j}$。复杂度 $O(n)$。
# 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=3e5+5;
const int MAXM=30+5;
int n,ans,sum;
int a[MAXN];
int used[MAXN][MAXM];
int cnt[MAXM];
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans+=a[i];
		sum+=a[i];
		for(int j=0;j<30;j++)
			if((1<<j)&a[i])
				used[i][j]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<30;j++)
			cnt[j]+=used[i][j];
	for(int i=1;i<=n;i++){
		int tot=sum;
		for(int j=0;j<30;j++)
			tot+=used[i][j]*(n-cnt[j]*2)*(1<<j);
		ans=max(ans,tot);
	}
	cout<<ans;
}
```

---

