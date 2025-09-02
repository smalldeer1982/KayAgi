# Super-Permutation

## 题目描述

A permutation is a sequence $ n $ integers, where each integer from $ 1 $ to $ n $ appears exactly once. For example, $ [1] $ , $ [3,5,2,1,4] $ , $ [1,3,2] $ are permutations, while $ [2,3,2] $ , $ [4,3,1] $ , $ [0] $ are not.

Given a permutation $ a $ , we construct an array $ b $ , where $ b_i = (a_1 + a_2 +~\dots~+ a_i) \bmod n $ .

A permutation of numbers $ [a_1, a_2, \dots, a_n] $ is called a super-permutation if $ [b_1 + 1, b_2 + 1, \dots, b_n + 1] $ is also a permutation of length $ n $ .

Grisha became interested whether a super-permutation of length $ n $ exists. Help him solve this non-trivial problem. Output any super-permutation of length $ n $ , if it exists. Otherwise, output $ -1 $ .

## 样例 #1

### 输入

```
4
1
2
3
6```

### 输出

```
1
2 1
-1
6 5 2 3 4 1```

# 题解

## 作者：Little_Cart (赞：14)

## 题意简述

判断能否构造并构造一个长度为 $n$ 的 $1…n$ 的排列，满足其 $n$ 个前缀和模 $n$ 的值加 $1$ 后也是一个 $1…n$ 的排列。

## 做法简述

首先，我们可以看出，$n$ 是必须放在开头的。

如果说 $n$ 不放在开头，那么设 $n$ 的位置为 $x$，我们可以发现 $1…x-1$ 的和与 $1…x$ 的和在模 $n$ 的意义下是相等的，与题意不符，所以不成立。

由于 $n$ 必须放在开头，那么 $n$ 为奇数时一定不成立，因为此时 $1+2+…+n=\frac{n \times (n+1)}{2}$ 模 $n$ 会等于 $0$，也就意味着 $1$ 的值与 $1…n$ 的和在模 $n$ 的意义下是相等的，此时不成立。

当然，此处有一个特例，就是当 $n=1$ 的时候，此时 $1$ 是满足条件的一个构造，需要特判一下。

那么此时可以暴力一下发现这样一组构造。

$n,n-1,2,n-3,4,n-5,…,n-2,1$。

我们可以分段来看。

先把开头的 $n$ 和末尾的 $1$ 忽略掉，然后把每两个相邻的数看作一组。

我们发现 $n-1$ 和 $2$ 可以构成一个 $n+1$，模 $n$ 为 $1$。

$n-3$ 和 $4$ 可以构成一个 $n+1$，模 $n$ 为 $1$。

所以此时每一组模 $n$ 都为 $1$，也就意味着我们可以使余数变为 $1,2,…,\frac{n}{2}-1$。

接下来，重新分段，把每两个相邻的数看作一组（比如 $n$ 和 $n-1$）。

我们发现此时每组模 $n$ 都是 $n-1$，也就意味着我们可以使余数变为 $n-1,n-2,…,\frac{n}{2}$。

最后再把开头的 $n$ 算上，$n$ 模 $n$ 为 $0$，此时我们就有了 $0,1,2,…,n-1$，加 $1$ 后是一个 $1…n$ 的排列。

## 全代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200024;
int t,n;
int a[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		if(n==1){
			cout<<"1\n";
			continue;
		}
		if(n%2){
			cout<<"-1\n";
			continue;
		} 
		cout<<n<<" ";
		for(int i=n-1,j=2;j<=n-2;i-=2,j+=2){
			cout<<i<<" "<<j<<" ";
		}
		cout<<"1\n";
	}
	return 0;
}

```


---

## 作者：TimSwn090306 (赞：4)

# [CF1822D Super-Permutation 题目传送门](https://www.luogu.com.cn/problem/CF1822D)

## 0.写在前面：

很妙的一道构造题，推了好久。

## 1.简化题意：

给定 $n$，求一个 $1\thicksim n$ 的排列，使得这个排列的所有前缀和模 $n$ 的值重新组成了 $0\thicksim (n-1)$ 的一个排列，如果无解输出 $-1$。

## 2.解题思路：

唠叨两个~~显然易见的~~性质。

**性质1：**$n$ 是要放在第一个位置的。

* 证明：反证法，由于 $n$ 在模 $n$ 意义下等同于 $0$，所以如果 $n$ 放置的位置 $i$ 不是第一个的话，一定存在一个前缀和 $sum_i = sum_{i-1}+n\equiv sum_{i-1} \bmod n \space(i>1)$，因此前缀和一定不是一个排列，故 $n$ 一定在第一个位置。

**性质2：** 当 $n$ 为大于 $1$ 的奇数的时候，无解。

* 证明：不管这个排列怎么放置，它们的和一定是个固定的值即 $\frac{n(n+1)}{2}$。由性质 1 可得，第一位一定是 $n$，所以这个和模 $n$ 不等于 $0$。又因为当 $n$ 为奇数时，原式是 $n$ 的倍数，所以 $n$ 为奇数时无解。特殊的，$n=1$ 时有解。

下面就来考虑有解的情况下怎么得到这个解（后文的前缀和均是模 $n$ 意义下的前缀和）。

由于不同的数字对于模 $n$ 的值不同，不好找出通解，所以我们可以把它们**两两分对**，组成若干和相同的数对，共同考虑。

这里举例分成和均为 $n+1$ 的数对的分组方法：

首先，剩下未放置的数是 $1\thicksim(n-1)$，所以我们可以把它们合成和等于 $n+1$ 的数对，余下 $1$ 没有组对，举个 $n=10$ 的例子：

$$1,2,3,4,5,6,7,8,9$$

$$\Longrightarrow (2,9),(3,8),(4,7),(5,6)$$

然后我们将组成的数对**相邻**着一对一对塞入序列，这样可以保证奇数位上的前缀和是从 $0$ 开始，公差为 $1$，的等差数列，也就是说奇数位上的前缀和恰好组成了 $0 \thicksim (\frac{n}{2}-1)$ 而不重复。

进而，不管一个固定位置的数对内怎么交换两数顺序，第二个数的前缀和是固定的，所以只需要看第一个数怎么处理就可以了。

假设第 $i$ 个数对的第一个数是 $x_i$，那么这个位置的前缀和是

$$(i-1)\times 1+n+x_i \equiv x_i+i-1 \bmod n$$

可以发现 $x_i$ 为一个公差为 $-2$ 的等差数列时，前缀和可以覆盖一段**连续**的数，由此可以构造出来恰好覆盖 $ (\frac{n}{2}+1)\thicksim (n-1)$ 的排列：

$$(2,9),(3,8),(4,7),(5,6)$$

$$\Longrightarrow (9,2),(7,4),(5,6),(3,8)$$

最后前面放个 $n$，后面落个 $1$ 就 ok 了。

$$(9,2),(7,4),(5,6),(3,8)$$

$$\Longrightarrow 10,(9,2),(7,4),(5,6),(3,8),1$$

$$\Longrightarrow 10,9,2,7,4,5,6,3,8,1$$

## 3.代码实现：

很简单，注意要特判 $1$ 可行。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n;
inline void solve(){
    scanf("%d",&n);
    if (n==1){
        printf("1\n");
        return ;
    }
    if (n&1){
        printf("-1\n");
        return ;
    }
    printf("%d ",n);
    for (int i=n-1;i>1;i-=2) printf("%d %d ",i,n+1-i);
    printf("1\n");
}
int main(){
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
```

$$----TheEnd----$$

---

## 作者：wawatime1 (赞：2)

### 题目分析
一道好题，构造题。

1. $n = 1$ 的情况：超级排列就是 $1$。
2. $n > 1$ 的情况：
- 对于奇数 $n > 3$，$\sum_{i = 1}^{n}i =  \frac{n(n + 1)}{2}$，因为 $n$ 为奇数，$\frac{n(n + 1)}{2} \mod n$ 会导致 $b_n$ 使得 $b_n + 1$ 在 $[b_1 + 1,b_2+1……b_n+1]$ 中产生重复元素，不存在超级排列。

- 对于偶数 $n$，可以构造超级排列。方法是，去掉首尾项，然后将将 $n$ 个数分成两部分，前半部分从 $n - 2$ 开始递减，后半部分从 $2$ 开始递增。例如 $n = 6$ 时，排列为 $[6,5,2,3,4,1]$。

### 代码
```cpp
#include <iostream>
using namespace std;
int t;
int main() {
	cin >> t;
	while (t--) {
		int n;
		scanf ("%d", &n);
		if (n == 1){
			printf ("1\n");
		}
		else if (n % 2 == 1){
			printf ("-1\n");
		}
		else{
			printf ("%d ", n);
			for (int i = n - 1, j = 2; i > 1 && j < n; i -= 2, j += 2)
				printf ("%d %d ", i, j);
			printf ("1\n");
		}
	}
	return 0;
}
```

---

## 作者：ykzzldz (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1822D)

首先，考虑几个性质：

1. $n$ 只能放在第一个位置

2. 除 $1$ 外，其他 $n$ 为奇数的情况无解

证明：

1. 如果 $n$ 不放在第一个位置，设 $n$ 放置的下标为 $i$，则 $sum_{i-1}$ 与 $sum_i=sum_{i-1}+n$ 在模 $n$ 意义下是相同的，不符合题意

2. 由性质一，可以知道一定存在一个数模 $n$ 等于 $0$（也就是 $n$），那么最后一个前缀和 $sum_n=\frac{n\times (n+1)}{2}$ 模 $n$ 等于 $0$，也不符合题意

那么，考虑构造有解情况：

通过~~暴力打表~~严谨分析可以发现，解的情况为 $n,n-1,2,n-3,\dots,n-2,1$，考虑证明这样构造一定合法：

我们先去掉首尾项，分析相邻两项的情况。可以看出，相邻两项的和为 $1$，这里可以看作是一个差分数组全为 $1$，那么，整个序列的值就为 $1$ 到 $n-1$ 的排列。

现在，我们将首尾项加上，可以发现整个序列的值就为一个 $0$ 到 $n-1$ 的排列，加一后正好就是一个 $1$ 到 $n$ 的排列。下面给出代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n==1){
			cout<<"1\n";
			continue;
		}
		if(n%2==1){
			cout<<"-1\n";
			continue;
		}
		cout<<n<<" ";
		for(int i=1;i<n;i++){
			if(i%2==1)cout<<n-i<<' ';
			else cout<<i<<' ';
		}
		cout<<"\n";
	}
    return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

硬想是有难度的，于是我们使用全排列的方式爆搜 $10$ 以内的几个数。发现在 $2$ 到 $10$ 中有这样的规律：

+ 奇数无解。 

+ 偶数为 $n$，$n-1$，$2$，$n-3$，$4$，一直到 $1$。

此时我们不知道这个规律正不正确。于是验算一下。

发现从第二个开始，$2k$ 个与 $2k+1$ 个的和都是 $n+1$。那么 $b$ 数组就是从 $1$ 到 $\frac{n}{2} -1$。

从第一个开始，$2k+1$ 个与 $2(k+1)$ 个的和都是 $2n-1$。那么 $b$ 数组就是从 $\frac{n}{2}$ 到 $n$。

于是这个规律就是正确的。特判 $1$ 就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
void solve(){
	scanf("%lld",&n);
	if(n==1) printf("1\n");
	else if(n%2==1) printf("-1\n");
	else{
		printf("%lld ",n);
		for(int i=n-1,j=2;j<=n-2;i-=2,j+=2){
			printf("%lld %lld ",i,j);
		}
		printf("1\n");
	}
}
signed main(){
	scanf("%lld",&t);
	while(t--) solve();
    return 0;
}

```

---

## 作者：The_foolishest_OIer (赞：0)

CF 的构造题一般可以用打表解决。

那么就先用 $O(n!)$ 的做法打表吧。

打表代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int a[15],b[15],vis[15];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
bool check (int x){
	for (int i = 1 ; i <= x ; i++)
		if (!vis[i])
			return 0;
	return 1;
}
signed main(){
    for (int i = 1 ; i <= 10 ; i++){
    	cout << "test:" << i << endl;
    	for (int j = 1 ; j <= i ; j++)
			a[j] = j;
		bool flag = 0;
		do{
			memset(vis,0,sizeof(vis));
			int sum = 0;
			for (int j = 1 ; j <= i ; j++){
				sum += a[j];
				b[j] = sum % i + 1;
				vis[b[j]] = 1;
			}
			if (check(i)){
				flag = 1;
				for (int j = 1 ; j <= i ; j++)
					cout << a[j] << ' ';
				cout << endl;
			}
		}while (next_permutation(a + 1,a + i + 1));
		if (!flag) cout << -1 << endl;
	}
	return 0;
}
```

然后就可发现，$n = 1$ 时直接输出 `1`。

$n$ 为奇数时肯定无解（除了 $1$）。

$n$ 为偶数时就有构造 $n,1,n-2,2,…,n - 1,2$。

我们可以把上述构造两个数一组分开（比如 $n$ 和 $1$），发现每组的数之和模 $n$ 余 $1$。

再重新分割（比如 $n$ 和 $n-1$），发现每组的数之和模 $n$ 余 $n - 1$。

合并之后刚好得到了一个 $0 \sim n - 1$ 的排列，然后就做完了。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int t,n;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> n;
	if (n == 1){
		cout << 1 << endl;
		return;
	}
	if (n & 1){
		cout << -1 << endl;
		return;
	}
	for (int i = n,j = 1 ; j <= n ; i -= 2,j += 2)
		cout << i << ' ' << j << ' ';
	cout << endl;
}
signed main(){
	close();
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：Kindershiuo (赞：0)

# 解题思路
这题的话其实我是模拟了很多组样例找到的规律，就拿题目的样例来看：

|题目样例|6|5|2|3|4|1|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|前缀和|6|11|13|16|20|21|
|取模后加 $1$ |1|6|2|5|3|4|

我相信聪明的你们很快就能发现这是有规律的，规律就是我们取模后的数组是最小的配上一个最大的然后后面紧接一个次小配次大，就这样以此类推，而奇数的时候是配不出来的，因为会漏一个数字，所以 $n$ 为奇数的时候是无解，但是有一个特例，就是 $n$ 为 $1$ 的时候，这个我们是有解的，解就是 $1$ 本身；还有一个性质就是，不管我们这个排列如何，最后的数组总和是一定的。
那么我的解题思路就是根据规律预处理一个取模后的数组，然后我们从总和开始慢慢处理出来前缀和数组，然后答案数组就自然而然的出来了，就是前缀和后一项减去前一项就行。

所以我的思路就是咱们倒着来，从取模后的数组入手。
# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
#define endl '\n'
int T;
int a[N];
int b[N];

void solve() {
	int n;
	cin>>n;
	if(n==1){cout<<1<<endl;return;}
	if(n%2!=0){cout<<-1<<endl;return;}
	else{
		int t1=1;
		int t2=n;
		for(int i=1;i<=n;i++){
			if(i%2!=0){
				a[i]=t1;
				t1++;
			}else{
				a[i]=t2;
				t2--;
			}
		}
		int s=0;
		for(int i=1;i<=n;i++)s+=i;
		b[n]=s;
		for(int i=n-1;i>=1;i--){
			if(a[i]<a[i+1]){
				b[i]=b[i+1]-(a[i+1]-a[i]);
			}else{
				int t=n;
				b[i]=b[i+1]-a[i+1];
				b[i]-=(t-a[i]);
			}
		}
		cout<<b[1]<<" ";
		for(int i=2;i<=n;i++){
			cout<<b[i]-b[i-1]<<" ";
		}
		cout<<endl;
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
//	T=1;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：CznTree (赞：0)

做题最重要的方法：找规律。

我们不妨来暴力算一下：

```
n    	        ans
1		1
2		2 1
3		-1
4		4 3 2 1
5		-1
6		6 5 2 3 4 1
7		-1
8		8 7 2 5 4 3 6 1
9		-1
10		10 9 2 7 4 5 6 3 8 1
11		-1
```

不难发现，当 $n = 1$ 时，序列就为 $1$，当 $n$ 为非 $1$ 奇数时，答案为 $-1$，其他肯定都有答案。

那么我们再来看其他的规律。

显然，每个序列的第一个数都是 $n$，第二个数为 $n - 1$，第三个数却变成了 $2$，接着又变成了 $n - 3$，然后是 $4$，然后是 $n-5 \dots$ 以此类推，可以得出答案序列为：

${n, n - 1, 2 \times 1, n - 3,2 \times 2, n - 5, 2\times3\dots2\times k, 1}$

好了，直接照这个序列输出就可以了，这个序列的长度不难发现也是 $n$。

```cpp
#include <bits/stdc++.h> 
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr) 
#define rep(i, a, b) for (int i = a; i <= b; i++) 
#define per(i, a, b) for (int i = a; i >= b; i--)
#define lcb(x) ((x) * size - size + 1) 
#define rcb(x) ((x) * size) 
#define lc(x) x << 1ll
#define rc(x) x << 1ll | 1ll				
#define lowbit(x) ((x) & (-x))
#define LEN_LC (tree[lc(i)].r - tree[lc(i)].l + 1) 
#define LEN_RC (tree[rc(i)].r - tree[rc(i)].l + 1) 
#define LEN (tree[i].r - tree[i].l + 1)  
#define int long long
#define endl "\n"
const int N = 1e6 + 7;
template<typename T>inline void read(T &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}

void solve() {
	int n; read(n); 
	if(n == 1) {
		std::cout << "1" << endl; 
		return ; 
	}
	if(n % 2 == 1) {
		std::cout << "-1" << endl; 
		return ; 
	}
	std::cout << n << " ";
	int x1 = 2, x2 = n - 1; 
	rep(i, 1, n - 1) {
		if(i % 2 == 0) { std::cout << x1 << " "; x1 += 2;}
		else { std::cout << x2 << " "; x2 -= 2;} 
	} 
	std::cout << endl; 
}

signed main() {
	int t; read(t); 
	while(t--) 
	solve(); 
	return 0; 
}
```

---

## 作者：weihaozhen2010 (赞：0)


# 题意：

[CF1822D](https://www.luogu.com.cn/problem/CF1822D)

#  思路：

- 一道有难度的构造题，有多种情况。

- 很明显的是 $n$ 必须在第一个数，一旦 $n$ 放在了第 $i$ 个位置，那么 $b_i$ 就会与 $b_{i-1}$ 在模 $n$ 的意义下同余。因此 $n$ 是在第一个位置的。

- 由于 $n$ 是在第一个位置的，且 $b_n=a_1+a_2+\dots+a_n=\frac{n×(n+1)}{2}$。因此，很明显可以得出 $n$ 为奇数时无解。

- 怎么一回事呢？其实因为当 $n$ 为奇数时 $b_n=\frac{n×(n+1)}{2}$ 模 $n$ 会为 $0$，而 $a_1$ 又正好为 $n$，它模 $n$ 也会为 $0$，所以他们两个是同余的，因此无解。

- 但是，当 $n=1$ 时是有解的，直接输出 $1$ 即可。 

- 到目前为止我们得出了两个结论了。一个是 $n$ 必须在第一个位置，另一个是非 $1$ 的奇数是无解的。

- 那么剩下的情况又如何解决呢？看一下样例找找规律。

  ```cpp
  n=2：2 1
  n=4：4 3 2 1
  n=6：6 5 2 3 4 1
  n=8：8 7 2 5 4 3 6 1
  n=10：10 9 2 7 4 5 6 3 8 1
  ```

  很容易发现规律。抛开第一位，当序列到达偶数位时，序列是一个公差为二的上升偶数等差数列。当序列到达奇数位时，序列是一个公差为二的下降奇数等差数列。

  更直观的就是 $n , n-1 , 2 , n-3 , 4 , n-5 , 6 , n-7 , \dots , 1$。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void re()
{
    int n;
	cin>>n;
	if(n==1) 
	{
		cout<<"1\n";
		return;
	}
	if(n%2==1&&n!=1) 
	{
		cout<<"-1\n";
		return;
	}
    cout<<n<<" ";
    int sum1=n-1,sum2=2;
    for(int i=1;i<=n-1;i++)
    {
        if(i%2==0)
        {
            cout<<sum2<<" ";
            sum2+=2;
		}
        else
        {
            cout<<sum1<<" ";
            sum1-=2;
        }
    }
    cout<<"\n";
    return;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		re();
	}
	return 0;
}
```

---

## 作者：wuzijie (赞：0)

## 题面解释：
找出长度为 $n$ 的满足以下条件的序列：

1. 它是一个排列。

	- 对于每一个 $1\le i\le n$，有 $1\le a_i\le n$。

	- 序列中的数不重复出现。

3. 这个数的前缀和数组，对每个数对 $n$ 取模 $+1$ 后也是一个排列。

## 思路分析：
我们如何去构造这个数组呢？

首先，对 $n$ 取模，那 $n$ 一定是特殊的一项，加 $n$ 与否不会有任何差别，所以假设 $a_x=n$，那么操作后的数组一定有 $b_{x-1}=b_x$，所以 $x-1$ 与 $x$ 不能同时存在，对于 $1\le x\le n$，可得 $n$ 一定在第一项。

此外，末项也一样重要，根据高斯求和公式可得 $b_n=\frac{n(n+1)}{2}$ 对 $n$ 取余再 $+1$ 的结果，那么可以发现，当 $n$ 是一个奇数时，其结果一定为 $1$，与首项相同，肯定不行。

特别的，当 $n=1$ 时，首项与末项是同一项，不存在冲突，结果为 $1$ 。

然后我们就可以通过打表开始找规律了：

$n=2$：$\left [ 2,1 \right ] $；

$n=4$：$\left [ 4,3,2,1 \right ] $；

$n=6$：$\left [ 6,5,2,3,4,1 \right ] $；

$n=8$：$\left [ 8,7,2,5,4,3,6,1 \right ] $；

……

我们可以发现，把首项与末项去掉，正好是两两一组，和为 $n+1$。同时前一个是奇数且递减，后一个是偶数且递增。

那么这道题目就愉快地解决了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
signed main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n==1){//特判1
			printf("1\n");
			continue;
		}
		if(n%2==1){//奇数情况
			printf("-1\n");
			continue;
		}
        //偶数情况
		printf("%d ",n);
		for(int i=n-1,j=2;j<n;i-=2,j+=2)
			printf("%d %d ",i,j);
		printf("1\n");
	}
	return 0;
}
```

谢谢！

---

## 作者：FireRain (赞：0)

# 思路

首先发现 $n$ 只能放在第一位，因为如果 $n$ 放置的位置为 $k$，那么 $b_k = (b_{k - 1} + n) \bmod n = b_{k - 1} \bmod n$。

其次，除了 $1$ 以外的所有奇数都无解，因为 $b_n = \frac{(n + 1) \cdot n}{2} \bmod n = b_1$。

然后发现 $a = [n,1,n - 2,3,n - 4,5,\dots,n - 1,2]$ 是一种可行的解。


# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

int n;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    n = read();
    if (n == 1) puts("1");
    else if (n & 1) puts("-1");
    else{
        bool r = false;
        for (re int i = 1,j = n,k = 1;k <= n;k++){
            if (r){
                printf("%d ",i);
                i += 2;
            }
            else{
                printf("%d ",j);
                j -= 2;
            }
            r ^= 1;
        }
        puts("");
    }
}

int main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：zxh923 (赞：0)

# CF1822D Super-Permutation 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1822D)

### 思路

首先，我们可以证明，$n$ 必须放在第一个位置。

否则，$n$ 不论被放在其他的任何一个位置，可以确定这个位置的前缀和数组和这个位置的前一个位置的前缀和数组在模 $n$ 意义下是相同的，显然这与题意矛盾。

然后我们观察 $6 5 2 3 4 1$ 这个样例，可以发现从第二个数开始，编号为偶数的数和它后面的数的和为 $n-1$。

显然序列中的第一个数为 $n$，最后一个数为 $1$。

对于其它位置的数，偶数位置的数为 $n-i+1$，奇数位置的数为 $i-1$。

然后证明若 $n$ 为奇数且不为 $1$ 一定不行。此时整个序列的和为 $\frac {n\times(n+1)}2$，显然 $n+1$ 是 $2$ 的倍数，所以序列和对 $n$ 取余为 $0$。但是 $n$ 对 $n$ 取余也是 $0$，出现了重复，显然这与题意矛盾。

但是，如果 $n$ 是 $1$，是不会出现重复的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int t,n,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n==1){
			cout<<"1\n";
			continue;
		}else if(n&1){//如果是奇数但不是1
			cout<<"-1"<<"\n";
			continue;
		} cout<<n<<" ";
		for(int i=1;i<=n-2;i++){//和思路中的描述略有差别，不过不影响
			if(i&1)cout<<n-i<<' ';
			else cout<<i<<' ';
		}
		cout<<"1"<<"\n";
	}
	return 0;
}
```


---

## 作者：Michael1234 (赞：0)

- 本题属于**构造**题

- 首先推出，$n$ 必须放 $a_1$，如果放在了其他位置，$b_i\equiv b_{i-1} (\bmod \ n)$，无解。

- 接下来，可以推出，奇数无解，因为 $b_n=\frac{n\times(n+1)}{2}$，而 $\frac{n\times(n+1)}{2} \equiv b_1 (\bmod \ n)$，而 $b_1=n$。

- 接下来，我么来玩一下样例。

~~~
4：4 3 2 1
6：6 5 2 3 4 1
8：8 7 2 5 4 3 6 1
~~~

- 可以得知，$a$ 序列的构造如下。

- $n,n-1,2,n-3,4,n-5,6\dots n-4,3,n-1,1$

- 按照构造公式构造，输出即可。

## CODE

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n==1)//特判一下1,是可以构造的
		{
			cout<<"1\n";
			continue;
		}
		if(n%2==1)//不为1的奇数，无解
		{
			cout<<"-1\n";
			continue;
		}
		cout<<n<<" ";//先输出n
		for(int i=n-1,j=2;j<n;i-=2,j+=2)//按公式循环
		{
			cout<<i<<" "<<j<<" ";//输出每一步
		}
		cout<<"1\n";//最后输出1
	}
	return 0;
}

---

