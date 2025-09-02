# Add, Divide and Floor

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ). In one operation, you can choose an integer $ x $ ( $ 0 \le x \le 10^{18} $ ) and replace $ a_i $ with $ \lfloor \frac{a_i + x}{2} \rfloor $ ( $ \lfloor y \rfloor $ denotes rounding $ y $ down to the nearest integer) for all $ i $ from $ 1 $ to $ n $ . Pay attention to the fact that all elements of the array are affected on each operation.

Print the smallest number of operations required to make all elements of the array equal.

If the number of operations is less than or equal to $ n $ , then print the chosen $ x $ for each operation. If there are multiple answers, print any of them.

## 说明/提示

In the first testcase, all elements are already equal, so $ 0 $ operations are required. It doesn't matter if you print an empty line afterwards or not.

In the second testcase, you can't make less than $ 2 $ operations. There are multiple answers, let's consider the answer sequence $ [2, 5] $ . After applying an operation with $ x = 2 $ , the array becomes $ [\lfloor \frac{4 + 2}{2} \rfloor, \lfloor \frac{6 + 2}{2} \rfloor] = [3, 4] $ . After applying an operation with $ x = 5 $ after that, the array becomes $ [\lfloor \frac{3 + 5}{2} \rfloor, \lfloor \frac{4 + 5}{2} \rfloor] = [4, 4] $ . Both elements are the same, so we are done.

In the last testcase, you can't make less than $ 6 $ operations. Since $ 6 $ is greater than $ n $ , you don't have to print them. One possible answer sequence is $ [0, 0, 0, 0, 0, 0] $ . We are just dividing the second element by $ 2 $ every time and not changing the first element.

## 样例 #1

### 输入

```
4
1
10
2
4 6
6
2 1 2 1 2 1
2
0 32```

### 输出

```
0
2
2 5
1
1
6```

# 题解

## 作者：2huk (赞：12)

## Description

给定一个长度为 $n$ 的序列 $\{a_n\}$。每次操作你需要选择一个整数 $x$ 并将所有 $a_i$ 替换为 $\lfloor \frac {a_i + x}2 \rfloor$。求至少多少次操作后能将所有 $a_i$ 变相同。

若最少次数小于等于 $n$，输出操作次数和每次操作所选择的 $x$。否则仅输出操作次数。

$1 \le n \le 2 \times 10^5$，$0 \le a_i \le 10^9$。

## Solution

可以观察到，每次操作后，数字的**相对**大小关系不会发生改变。

例如 $a = \{4, 2, 5\}$，$x = 3$，那么操作后的 $a' = \{3, 2, 4\}$。可以发现 $a_3$ 和 $a'_3$ 分别都是两个序列的最大值，$a_2$ 和 $a'_2$ 都是两个序列的最小值。

那么就启发我们不用同时维护原序列中的所有值，只需要维护序列中的最大值和最小值。当这两个值相等时，就代表序列中所有的数都相同了。

那么问题就被转化成了这样：

> 给定两个整数 $a, b$。每次操作你需要选择一个整数 $x$ 并将 $a \gets \lfloor \frac {a + x}2 \rfloor$，$b \gets \lfloor \frac {b + x}2 \rfloor$。求至少多少次操作后 $a = b$。

每次操作我们肯定是希望利用下取整这个优秀性质来让 $a$ 尽量接近 $b$，也就是想让操作后 $a - b$ 尽量小。那么我们可以直接分讨：

- $a$ 为偶数，$b$ 为偶数：[$x$ 任意取值](https://www.luogu.com.cn/paste/gx9nzxic)；
- $a$ 为奇数，$b$ 为奇数：[$x$ 任意取值](https://www.luogu.com.cn/paste/yvohb091)；
- $a$ 为偶数，$b$ 为奇数：[$x$ 任意一个奇数](https://www.luogu.com.cn/paste/wa8gp7br)；
- $a$ 为奇数，$b$ 为偶数：[$x$ 任意一个偶数](https://www.luogu.com.cn/paste/uaevgx1b)。

然后就解决了。用 `vector` 记录答案即可。

## Code

```cpp
void solve()
{
	cin >> n;
	a = 0, b = 2e9;
	for (int i = 1; i <= n; ++ i )
	{
		cin >> x;
		a = max(a, x);
		b = min(b, x);
	}
	
	vector<int> res;
	while (a != b)
	{
		if (a % 2 == 0 && b % 2 == 0) x = rand();
		else if (a % 2 == 1 && b % 2 == 1) x = rand();
		else if (a % 2 == 0 && b % 2 == 1) x = rand() * 2 + 1;
		else x = rand() * 2;
		a = (a + x) / 2;
		b = (b + x) / 2;
		res.push_back(x);
	}
	
	cout << res.size() << '\n';
	if (res.size() <= n)
	{
		for (auto i : res) cout << i << ' ';
		if (res.size()) puts("");
	}
	
	return;
}
```

---

## 作者：灵茶山艾府 (赞：9)

**提供一个和目前所有题解都不同的做法。**

**观察 1**：操作次数至多为 $\max(a)$ 的二进制长度，因为每次选 $x=0$，相当于所有数都右移一位，最终都会变成 $0$。这也启发我们往**二进制**上思考。

**观察 2**：只需关注 $m = \min(a)$ 和 $M = \max(a)$ 这两个数，如果它俩能变成一样的，那么中间的所有数也都能变成一样的。

**观察 3**：如果只允许选 $x=0$，具体要操作多少次？相当于只能右移，操作次数取决于 $M \operatorname{xor} m$ 的二进制长度。

例如 $M=1110_{(2)},\ m=1011_{(2)}$，$M \operatorname{xor} m = 101_{(2)}$，要右移 $3$ 次才能让两个数相同。

$M \operatorname{xor} m$ 的二进制长度越小，答案也就越小。

考虑第一次操作，选什么样的 $x$，可以最小化 $M \operatorname{xor} m$ 呢？

或者等价于，在 $M$ 二进制长度不变的前提下，让 $M$ 和 $m$ 的二进制**公共前缀**越长越好。

**观察 4**：考虑 $M=100_{(2)},\ m=011_{(2)}$ 这个例子，如果第一次操作选择 $x=3$，那么 $M+3=111_{(2)},\ m+3=110_{(2)}$，右移后两个数相同，这样只需操作一次。

在 $M$ 二进制长度不变的前提下，为了让 $M$ 和 $m$ 的二进制**公共前缀**尽量长。我们可以把 $M$ 增大至全为 $1$ 的数，即 $2^L-1$，其中 $L$ 是 $M$ 的二进制长度。

> 为什么不考虑更长的 $M$？这不会让答案变得更优，如果 $M$ 已经变成一个二进制全为 $1$ 的数，继续变大相当于把 $M$ 和 $m$ 都加上 $2^k$，这不会改变 $M \operatorname{xor} m$。此外这也说明后面的操作只需选 $x=0$。

第一次操作选 $x=2^L-1-M$，后面的操作全部选 $x=0$。

答案为 $1$ 加上 $M' \operatorname{xor} m'$ 的二进制长度，其中 $M'=2^{L-1}-1,\ m'=\left\lfloor\dfrac{m+x}{2}\right\rfloor$。

注意特判 $m=M$ 的情况，此时无需操作。

```go
package main
import("bufio";."fmt";"math/bits";"os";"strings")

func main() {
	in := bufio.NewReader(os.Stdin)
	var T, n, v int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n)
		m, M := int(1e9), 0
		for i := 0; i < n; i++ {
			Fscan(in, &v)
			m = min(m, v)
			M = max(M, v)
		}
		if m == M {
			Println(0)
			continue
		}
		u := 1<<bits.Len(uint(M)) - 1
		x := u - M
		ans := 1 + bits.Len(uint((u/2)^((m+x)/2)))
		Println(ans)
		if ans <= n {
			Println(x, strings.Repeat("0 ", ans-1))
		}
	}
}
```

**时间复杂度**：$\mathcal{O}(n)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：Jerrycyx (赞：1)

首先，题目要求使所有的 $a_i$ 相同，而这只与它们的相对大小关系有关。

容易发现其相对大小关系只与每次所选的 $x$ 奇偶性有关，而与 $x$ 的具体大小无关，比如 $x=0$ 和 $x=2$ 不会改变 $a$ 的相对大小关系（后者相对于前者，所有元素都增加了 $1$，相对大小关系不变）。

所以，令 $x$ 只有 $0$ 和 $1$ 两种选择。每一次操作，所有的 $a_i$ 都变为 $\lfloor \frac{a_i}{2} \rfloor$ 或 $\lfloor \frac{a_i+1}{2} \rfloor$，使用 $\log_2 \max a$ 级别的操作次数就可以将所有数都变为 $0$，也就是说，最大操作次数是 $\log$ 级别的。

而要将所有数变为一样，自然可以想到将所有数全部变为最小值 $\min a$，而每次取 $x = \min a$ 就可以让最小值维持不变，其它数全部变为 $\lfloor \frac{a_i + \min a}{2} \rfloor$。根据上文，操作次数是 $\log$ 级别的，所以直接暴力改变数值并判断即可，时间复杂度 $O(n \log a)$。

核心代码：

```cpp
while(true)
{
	int is_ok=true;
	for(int i=1;i<=n;i++)
		if(a[i]!=a[1]) is_ok=false;
	if(is_ok) break;
	ans++; 
	for(int i=1;i<=n;i++)
		a[i]=(a[i]+mina)>>1;
}
```

[AC 记录 + 完整代码](https://codeforces.com/contest/1901/submission/290990924)

---

## 作者：LucasXu80 (赞：1)

考虑两个数 $a,b (a \leq b)$，选择整数 $a$（即两个数中的更小值）对他们进行操作。

则两个数将分别变为 $a$、$\lfloor \dfrac {a+b} 2 \rfloor$。

考虑操作前后这两个数的差，由 $b-a$ 变为 $\lfloor \dfrac {b-a} 2 \rfloor$。

特别地，在某一次操作后相同的两个数在以后的任何操作后都仍相同。因此我们只需要关注数列的最大、最小值即可。

不难找到思路：先求出数列的极差 $d_{max}$，则最小操作数为 $\lfloor \log{}_2 d_{max} \rfloor +1$。

注意当 $ans \leq n$ 时还要输出每一步操作 $x$ 的取值。根据上面的推导，可以在第一步操作时选择数列的最小值作为 $x$，此后每一次操作取 $\lfloor \dfrac x 2 \rfloor$ 即可。


```cpp
#include <iostream>
#include <math.h>
using namespace std;
int t,a[200001],n,minn,maxn;
int main()
{
	cin>>t;
	while (t--)
	{
		cin>>n;
		minn=2e9;
		maxn=-1;
		for (int i=1; i<=n; i++)
		{
			cin>>a[i];
			minn=min(minn,a[i]);
			maxn=max(maxn,a[i]);
		}
		if (minn==maxn)
		{
			cout<<0<<'\n';
			continue;
		}
        int ans=log2(maxn-minn)+1;
		cout<<ans<<'\n';
		if (ans<=n)
		{
			int now=minn;
			for (int i=1; i<=ans; i++) cout<<now<<' ';
			now/=2;
			cout<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：KarmaticEnding (赞：0)

易于观察到，要使一个序列全部等于一个值，只要使它们的最大值和最小值变为同一个值就行了。

而在这道题目中，最大值和最小值所处的位置是不会改变的，这就是说无论经过几次操作，原序列最大值的位置还是最大值，原序列最小值的位置还是最小值。

这启发我们只需要维护序列最大值和序列最小值就好了。赛场上写复杂了，甚至排了个序，实际上没必要。

我们设序列的最大值为 $a$，最小值为 $b$，那么我们所做的每一步都是要缩小 $a$ 和 $b$ 之间的差距而不是增大它们之间的差距。

观察到，给 $a$ 和 $b$ 执行 $\left \lfloor \frac{a+x}{2} \right \rfloor$ 和 $\left \lfloor  \frac{a+x+2}{2}\right \rfloor$ 两个操作，操作完之后 $a-b$ 的值是不会变的。

所以为了使思路和代码简化，我们令 $x\in \{0,1\}$

回到我们的思路：

  - $a$ 和 $b$ 奇偶性相同的时候，$x$ 无论是选 $0$ 还是选 $1$，操作完之后 $a-b$ 的值都是一样的，所以我们为了方便，选择 $0$。
  - $a$ 为奇数 $b$ 为偶数的时候，如果 $x=1$，那么 $\left \lfloor \frac{a+1}{2} \right \rfloor=\left \lfloor \frac{a}{2} \right \rfloor+1$，而 $\left \lfloor \frac{b+1}{2} \right \rfloor=\left \lfloor \frac{b}{2} \right \rfloor$，不如选 $0$，所以这样的情况下我们选 $x=0$。
  - $a$ 为偶数 $b$ 为奇数的时候，如果 $x=1$，那么 $\left \lfloor \frac{a+1}{2} \right \rfloor=\left \lfloor \frac{a}{2} \right \rfloor$，而 $\left \lfloor \frac{b+1}{2} \right \rfloor=\left \lfloor \frac{b}{2} \right \rfloor+1$，所以只有在这个情况下我们必须选 $x=1$。

把得到的 $x$ 存在一个 `vector` 中就可以了。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=2e5+10;
int a[MAXN];
int n;
int T;
vector<int> vec;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		int op_time=0;
		vec.clear();
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		if(n==1){
			putchar('0');putchar('\n');
			continue;
		}
		sort(a+1,a+n+1);
		//难道只用关注一头一尾?
		while(a[1]!=a[n]){
			++op_time;
			if((a[1]&1)&&((a[n]&1)==0)){
				a[1]=(a[1]+1)>>1;
				a[n]=(a[n]+1)>>1;
				vec.push_back(1);
			}
			else{
				a[1]=a[1]>>1;
				a[n]=a[n]>>1;
				vec.push_back(0);
			}
		}
		printf("%d\n",op_time);
		if(op_time<=n){
//			printf("x={");
			for(int g:vec){
				printf("%d ",g);
			}
//			printf("}");
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：yegengghost (赞：0)

~~不~~根据数学基础，~~很难~~不难发现两个数字都除以同一个数字时，除数越大，两数除完后的差就越小。

那么我们就根据这个来解决这个问题。

对于输入的数据，我们发现：当最大值与最小值相等时，该序列的值也就都一样了。所以只需考虑最大值与最小值经几次能够相等即可。

但是，如何才能让最大值与最小值向着一个值靠拢捏？

我们又发现：可以从奇偶性下手。如果两数字奇偶性相同，则要处理的数字就直接设为 $0$。如果较小数是奇数，则将处理数字设为 $1$，最后处理即可。

我觉得用随机数有点 wyy 吧。

---

## 作者：hjqhs (赞：0)

*1400 还是能做到 15 分钟薄纱的！  
很明显只用关注最大值和最小值。  
记把 $a_i$ 变成 $\lfloor \frac{a_i+x}{2} \rfloor$ 为一次 $f(x)$ 变换。  
举个例子，一组数最大和最小是 $[10,5]$。  
$f(0)$ 变换（即单纯的除以 $2$）后差为 $3$，但进行一次 $f(1)$ 运算后差为 $2$。  
究其根本，是因为偶数 $f(0)$ 变换和 $f(1)$ 变换后值是不变的，而奇数则会差 $1$。  
再究其根本，就是分析奇偶性。  
所以就可以得到，要么进行 $f(0)$ 变换要么进行 $f(1)$ 变换。  
所以讨论 $mx$ 和 $mn$ 的奇偶性即可。
```cpp
// Problem: C. Add, Divide and Floor
// Contest: Codeforces - Educational Codeforces Round 158 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1901/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Created Time: 2023-12-21 18:35:44
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
typedef long long ll;
typedef unsigned long long ull;

const int N = 200005;
const int INF = 0x3f3f3f3f;

int T;

int n, a[N], mx = -INF, mn = INF, op[N], ont;
bool flag;

void init() {
	n = 0, mx = -INF, mn = INF, ont = 0, flag = 1;
	
	memset(a, 0, sizeof(a)), memset(op, 0, sizeof(op));
}
void solve() {
	cin >> n; rep(i, 1, n) {cin >> a[i]; mx = max(mx, a[i]), mn = min(mn, a[i]); }
	
	while(mx != mn) {
		int mx2 = mx % 2, mn2 = mn % 2;
		
		if(mx2 == 0 && mn2 == 0) {
			mx >>= 1, mn >>= 1;
			
			if(++ ont > n) flag = 0;
			if(flag) op[ont] = 0;
		} else if(mx2 == 0 && mn2 == 1) {
			mx >>= 1, mn = (mn + 1) >> 1;
			
			if(++ ont > n) flag = 0;
			if(flag) op[ont] =1;
		} else if(mx2 == 1 && mn2 == 0) {
			mx >>= 1, mn >>= 1;
			
			if(++ ont > n) flag = 0;
			if(flag) op[ont] = 0;
		} else if(mx2 == 1 && mn2 == 1) {
			mx >>= 1, mn >>= 1;
			
			if(++ ont > n) flag = 0;
			if(flag) op[ont] = 0;
		}
	}
	
	cout << ont << '\n';
	if(flag && ont) {rep(i, 1, ont) cout << op[i] << ' '; cout << '\n'; }
	
	return;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	cin >> T;
	while(T --) init(), solve();
	
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

首先，你每次要么 $x=0$，要么 $x=1$，那么就简单了。可以发现，这种操作，一定不会改变单调顺序，所以只要极差为 $0$ 即可。

但是每次放 $0$ 还是 $1$ 呢。我们可以打个表，发现其实每次就是根据最小值的奇偶性判断，若最小值为奇数，则 $x=1$，反之则 $x=0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll T, n, k, x, y;
vector <ll> a; 
int main(){
	scanf ("%lld", &T);
	while (T--){
		scanf ("%lld", &n);
		x = -1e18, y = 1e18;
		for (int i = 1; i <= n; i++) scanf ("%lld", &k), x = max(x, k), y = min(y, k);
		while (x != y){
			k = y & 1;
			x = (x + k) >> 1;
			y = (y + k) >> 1;
			a.push_back(k);
		}
		k = a.size();
		printf ("%lld\n", k);
		if (k <= n){
			for (int i = 0; i < k; i++) printf ("%lld ", a[i]);
			puts("");
		}
		a.clear();
	}
	return 0;
}

```

---

## 作者：I_will_AKIOI (赞：0)

我们可以发现 $x$ 其实只有两种选择，$0$ 或 $1$。一种是 $\displaystyle x\leftarrow\left \lfloor \frac{x+1}{2} \right \rfloor$，另一种是 $\displaystyle x\leftarrow\left \lfloor \frac{x}{2} \right \rfloor$。对于其他情况，可以的出结果是一样的。

其次，由于不可能出现类似 $x<y,\displaystyle \left \lfloor \frac{x+1}{2} \right \rfloor>\displaystyle \left \lfloor \frac{y}{2} \right \rfloor$ 的情况。所以在整个 $a$ 数组中，最值的两个数的位置是不变的，所以我们只需要记录最大值和最小值，对他们进行操作即可。我们需要贪心选择差值最小的操作。

接下来我们就需要选择 $0$ 还是 $1$ 了。我们设 $x=\min\{a_i\},y=\max\{a_i\}$，进行分类讨论：

若 $x$ 是奇数，$y$ 是奇数，选择 $0$ 或 $1$ 可使差值最小。

若 $x$ 是奇数，$y$ 是偶数，选择 $1$ 可使差值最小。

若 $x$ 是偶数，$y$ 是奇数，选择 $0$ 可使差值最小。

若 $x$ 是偶数，$y$ 是偶数，选择 $0$ 或 $1$ 可使差值最小。

所以选择 $0$ 还是 $1$，取决于 $x$ 的奇偶性，也就是 $x\operatorname{and} 1$。

最后将每次操作的值记录在数组中，最后输出即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
vector<int>ans;
signed main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
  	cin>>n;
  	int maxx=0,minn=INT_MAX,x;
  	for(int i=1;i<=n;i++) cin>>x,maxx=max(maxx,x),minn=min(minn,x);//记录最值
  	while(maxx!=minn)
  	{
  	  x=minn&1;
  	  minn=minn+x>>1;
  	  maxx=maxx+x>>1;
	  ans.push_back(x);
    }//选择操作的数
    cout<<ans.size()<<"\n";
    if(ans.size()<=n)
    {
      for(int i=0;i<ans.size();i++) cout<<ans[i]<<" ";//输出结果
	  cout<<"\n";
	}
	ans.clear();//多测不清空，爆零两行泪
  }
  return 0;
}
```

---

## 作者：eastcloud (赞：0)

我们先将 $a$ 数列排序，由于每次操作后不会出现原来 $x$ 比 $y$ 小现在 $y$ 比 $x$ 小的情况，因此我们可以只考虑第一个数和最后一个数的变化情况。

然后注意到不管每次 $x$ 如何选择，如果我们只关心最大值和最小值的差值，那么其实所有的选择都和选择 $0$ 或 $1$ 本质相同，那什么时候我们选 $1$ 不选 $0$ 呢？简单分讨一下可以发现当最小值为奇数的时候选 $1$ 一定不劣。

```cpp
void solve(){
	ll n=read(),tot=0;
	for(ll i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	while(1){
		if(a[1]==a[n])break;
		ll val=a[1]%2;b[++tot]=val;a[1]=(a[1]+val)/2;a[n]=(a[n]+val)/2;
	}
	write(tot);putchar('\n');
	if(tot<=n)for(ll i=1;i<=tot;i++)write(b[i]),putchar(' ');
	putchar('\n');
}
```


---

## 作者：Crazyouth (赞：0)

**分析**

观察发现，此题中的操作次数只和序列的 $\max$ 与 $\min$ 相等，主要证明如下：

若 $a=b$，则无论如何操作，都会得到 $a=b$；

$|a-b|$ 越大，则需要的操作数越大，因为要使 $a,b$ 相等，需要 $(\log_2|a-b|)+1$ 次，$a=b$ 除外，这一点是显然的。

那么，不难发现 $x>2$ 时并不会优于 $x=0$ 或 $x=1$ 时，所以讨论什么时候用 $x=0$，什么时候用 $x=1$。枚举奇偶性可得，$\min$ 值为奇数，$\max$ 值为偶数时需要 $x=1$，其他情况需要 $x=0$。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[int(2e5+10)];
int lg(int x)
{
	if(x==0) return -1;
	if(x==1) return 0;
	else return lg(x/2)+1;
}
void solve()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(n==1)
	{
		cout<<0<<endl;
		return;
	}
	int maxx=-1,minn=1e9;
	for(int i=1;i<=n;i++) maxx=max(maxx,a[i]),minn=min(minn,a[i]);
	int tp=lg(maxx-minn)+1;
	cout<<tp<<endl;
	if(tp<=n)
	for(int i=1;i<=tp;i++)
	{
		int out;
		if(minn%2&&!(maxx%2)) cout<<1<<' ',out=1;
		else cout<<0<<' ',out=0;
		minn=minn+out>>1;
		maxx=maxx+out>>1;
	}
	if(tp<=n&&tp) cout<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	solve();
	return 0;
}

---

