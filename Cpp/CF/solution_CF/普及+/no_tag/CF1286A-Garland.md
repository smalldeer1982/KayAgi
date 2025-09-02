# Garland

## 题目描述

Vadim loves decorating the Christmas tree, so he got a beautiful garland as a present. It consists of $ n $ light bulbs in a single row. Each bulb has a number from $ 1 $ to $ n $ (in arbitrary order), such that all the numbers are distinct. While Vadim was solving problems, his home Carp removed some light bulbs from the garland. Now Vadim wants to put them back on.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1286A/44ebad0b7dea7f3147d7078591406d3a6ec6de35.png)Vadim wants to put all bulb back on the garland. Vadim defines complexity of a garland to be the number of pairs of adjacent bulbs with numbers with different parity (remainder of the division by $ 2 $ ). For example, the complexity of 1 4 2 3 5 is $ 2 $ and the complexity of 1 3 5 7 6 4 2 is $ 1 $ .

No one likes complexity, so Vadim wants to minimize the number of such pairs. Find the way to put all bulbs back on the garland, such that the complexity is as small as possible.

## 说明/提示

In the first example, one should place light bulbs as 1 5 4 2 3. In that case, the complexity would be equal to 2, because only $ (5, 4) $ and $ (2, 3) $ are the pairs of adjacent bulbs that have different parity.

In the second case, one of the correct answers is 1 7 3 5 6 4 2.

## 样例 #1

### 输入

```
5
0 5 0 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
1 0 0 5 0 0 2```

### 输出

```
1```

# 题解

## 作者：Kewth (赞：15)

提供一个效率优秀的贪心做法。

首先排列只需要考虑奇偶性，设未确定的数中有 a 个奇数 b 个偶数。  
对于两个中间全是 0 的已经确定的数，考虑怎样安排中间的 0 能使答案尽量小。  
设这两个数模 2 为 x, y ，中间有 k 个数未确定。
分类讨论。

如果 x != y ，无论中间放什么数，都可以调整位置（只要和 x 奇偶性相同的在 x 一侧，其他在另一侧）使得对答案贡献恰好为 1 。

如果 x = y ，那么中间如果能全部放与 x, y 奇偶性相同的数就不会增加答案，  
但这样会付出一定代价，代价就是必须用 k 个 a （或 b ）。  
而如果中间不全部放与 x, y 奇偶性相同的数的话，无论放什么数，  
都可以调整位置（只要奇数在一块偶数在一块即可）使得对答案恰好贡献 2 。

那么不难发现需要决策的部分只有 x = y 中间全放一样的数这种情况，  
而且有代价和收益，收益都是 2 ，代价不等，对于两种奇偶性能承受的代价分别为 a, b 。  
将这些决策按代价排序，尽量选择代价小的去填，即可得到最大收益，即最小答案。

边界问题在于一些前缀 0 和一些后缀 0 难以判断，  
直接暴力枚举钦定 p[0] 和 p[n + 1] 的奇偶性即可。

复杂度 $O(n)$ ，排序部分用基数排序。

然而这题 n 只有 100 。。。表示不满。

```cpp
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 105;
int p[maxn], tot[2];
int q[2][maxn];

int solve(int n) {
	int las = 0;
	int res = 0;
	for(int i = 1; i <= n + 1; i ++)
		if(p[i]) {
			if(p[i] == p[las])
				++ q[p[i] - 2][i - las - 1];
			else
				++ res;
			las = i;
		}

	for(int i = 0; i < 2; i ++) {
		int max = tot[i];
		for(int x = 0; x <= max; x ++) {
			while(q[i][x] and x <= max) {
				max -= x;
				-- q[i][x];
			}
		}
	}

	for(int i = 0; i <= n; i ++) {
		res += 2 * (q[0][i] + q[1][i]);
		q[0][i] = q[1][i] = 0;
	}

	return res;
}

int main() {
	int n = read;
	if(n == 1) return puts("0"), 0;

	tot[0] = n >> 1;
	tot[1] = (n + 1) >> 1;

	for(int i = 1; i <= n; i ++) {
		int x = read;
		if(x) {
			p[i] = 2 + (x & 1);
			-- tot[p[i] - 2];
		}
	}

	int ans = 1000000000;
	for(int i = 2; i <= 3; i ++)
		for(int j = 2; j <= 3; j ++) {
			p[0] = i;
			p[n + 1] = j;
			ans = std::min(ans, solve(n));
		}

	printf("%d\n", ans);
}
```

---

## 作者：灵茶山艾府 (赞：13)

目前已有的题解写的有点麻烦，提供一个简洁点的写法。

定义 $f[i][j][0/1]$ 表示前 $i$ 个数中有 $j$ 个偶数时的奇偶性不同对的最小个数，其中 $f[i][j][0]$ 表示第 $i$ 个数是偶数，$f[i][j][1]$ 表示第 $i$ 个数是奇数。

讨论当前数字和上一个数字的奇偶性，得到转移方程（如果能填奇数/偶数才能转移）：

- $f[i+1][j][0] = \min(f[i][j-1][0], f[i][j-1][1]+1)$
- $f[i+1][j][1] = \min(f[i][j][0]+1, f[i][j][1])$

初始项 $f[0][0][0]=0,f[0][0][1]=0$，其余为无穷大。

答案为 $\min(f[n][n/2][0],f[n][n/2][1])$。

AC 代码（Golang）：

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, v int
	Fscan(in, &n)
	f := make([][][2]int, n+1)
	for i := range f {
		f[i] = make([][2]int, n/2+1)
		for j := range f[i] {
			f[i][j] = [2]int{1e9, 1e9}
		}
	}
	f[0][0] = [2]int{}
	for i := 0; i < n; i++ {
		Fscan(in, &v)
		for j := 0; j <= n/2; j++ {
			if j > 0 && v%2 == 0 {
				f[i+1][j][0] = min(f[i][j-1][0], f[i][j-1][1]+1)
			}
			if v == 0 || v%2 > 0 {
				f[i+1][j][1] = min(f[i][j][0]+1, f[i][j][1])
			}
		}
	}
	Print(min(f[n][n/2][0], f[n][n/2][1]))
}

func min(a, b int) int { if a > b { return b }; return a }
```

优化一下，第一个维度可以压缩掉：

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, v int
	Fscan(in, &n)
	f := make([][2]int, n/2+1)
	for i := 1; i <= n/2; i++ {
		f[i] = [2]int{1e9, 1e9}
	}
	for i := 0; i < n; i++ {
		Fscan(in, &v)
		for j := n / 2; j >= 0; j-- {
			if v == 0 || v%2 > 0 {
				f[j][1] = min(f[j][1], f[j][0]+1)
			} else {
				f[j][1] = 1e9
			}
			if j > 0 && v%2 == 0 {
				f[j][0] = min(f[j-1][0], f[j-1][1]+1)
			} else {
				f[j][0] = 1e9
			}
		}
	}
	Print(min(f[n/2][0], f[n/2][1]))
}

func min(a, b int) int { if a > b { return b }; return a }
```



---

## 作者：suxxsfe (赞：4)

# CF1286A题解  
整理博客的时候改了一下分类标签，重新审核一下  
**dp**  
觉得这题作为一个C比div2的B要简单点吧，~~算是找回点dp的信心。。。~~  
首先可以想到，只需关心每个数的奇偶，具体是几不用记录  
所以$0$表示偶数，$1$表示奇数，$-1$表示不确定，存在$a[]$中  
$num[0/1]$表示一共有几个偶/奇数需要填  
### 状态：  
$f[i][o][j][0/1]$: 考虑前$i$位，还剩$o$个偶数能用，剩$j$个奇数能用，第$i$位填的是偶数/奇数  
### 初始：  
先都设为极大值  
- 第一位填好了：$f[1][num[0]][num[1]][a[1]]=0$  
- 第一位需要自己填： $f[1][num[0]-1][num[1]][0]=f[1][num[0]][num[1]-1][1]=0$，要判断$num[0]$和$num[1]$是否大于0  

### 转移：  

- $i$位填好了：  
直接判断与前一位是否相等，不相等就加一  
$f[i][o][j][a[i]]=\min(f[i][o][j][a[i]],f[i-1][o][j][1]+(a[i] \neq 1))$  
$f[i][o][j][a[i]]=\min(f[i][o][j][a[i]],f[i-1][o][j][0]+(a[i] \neq 0))$  
- $i$位需要自己填：  
分别处理$i$位是偶数/奇数，在对应$i-1$位是偶数/奇数，共四种。  
容易想出$i$位是偶数/奇数时，被转移的状态分别应该$o+1$/$j+1$(因为记录的是可以可以填进去的偶数/奇数**还剩**几个，用了一个，当然要从剩余数多一个的状态转移而来）  
$f[i][o][j][1]=\min(f[i][o][j][1],f[i-1][o][j+1][1])$  
$f[i][o][j][1]=\min(f[i][o][j][1],f[i-1][o][j+1][0]+1)$  
$f[i][o][j][0]=\min(f[i][o][j][0],f[i-1][o+1][j][0])$  
$f[i][o][j][0]=\min(f[i][o][j][0],f[i-1][o+1][j][1]+1)$  

### 答案：  
当然是$\min(f[n][0][0][1],f[n][0][0][0])$  

&nbsp;  
其实代码中好多取$\min$是不需要的，但是为了方便就都写上了~~懒得想~~  
另外状态可能还能再优化？欢迎评论区指出  
&nbsp;  
$code.$,复杂度$O(n^3)$  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define R register
#define EN printf("\n")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-1;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return x*y;
}
int n;
int f[106][106][106][2];
int a[106],num[2];
inline void min(int &x,int y){(x>y)&&(x=y);}
int main(){
	n=read();
	for(R int i=1;i<=n;i++){
		a[i]=read();
		if(!a[i]){a[i]=-1;continue;}
		a[i]&=1;
		num[a[i]]++;
	}
	num[1]=(n&1?n/2+1:n/2)-num[1];num[0]=n/2-num[0];
	std::memset(f,0x3f,sizeof f);
	if(a[1]==-1){
		if(num[0]>0) f[1][num[0]-1][num[1]][0]=0;
		if(num[1]>0) f[1][num[0]][num[1]-1][1]=0;
	}
	else if(a[1]) f[1][num[0]][num[1]][1]=0;
	else f[1][num[0]][num[1]][0]=0;
	for(R int i=2;i<=n;i++){
		if(a[i]!=-1){
			for(R int o=num[0];o>=0;o--){
				for(R int j=num[1];j>=0;j--)
					min(f[i][o][j][a[i]],f[i-1][o][j][1]+(a[i]!=1)),
					min(f[i][o][j][a[i]],f[i-1][o][j][0]+(a[i]!=0));
			}
			continue;
		}
		for(R int o=num[0];o>=0;o--){
			for(R int j=num[1];j>=0;j--){
				min(f[i][o][j][1],f[i-1][o][j+1][1]);
				min(f[i][o][j][1],f[i-1][o][j+1][0]+1);
				min(f[i][o][j][0],f[i-1][o+1][j][0]);
				min(f[i][o][j][0],f[i-1][o+1][j][1]+1);
			}
		}
	}
	std::printf("%d",std::min(f[n][0][0][1],f[n][0][0][0]));
	return 0;
}
```  


---

## 作者：liuyz11 (赞：3)

# 题解 CF1286A 【Garland】

题目大意：有一个由[ 1…n ]组成的排列，其中有一些数被取走了（取走的数用0表示），现在将这些数放回这些空余的位置中。序列中每有相邻一对数的奇偶性不同就会增加序列的复杂度，求复杂度最小为多少。

这题我是在大佬的提示下才做出来的。

首先看到这个奇偶性，那么就不客气了，把数字直接给丢了留个膜2的余数就好。

现在问题变成了再剩余的位置放0/1使得相邻的复杂度最小。

虽然codeforces上这题的算法标签标了个greedy，但是我没搞懂这题怎么贪。

但是我们发现放的数为多少只会对后一个数字产生影响，所以可以用动态规划。

状态为放了i个数，用了j个1，这个数放的是0/1。

转移分两种第i个空余位置和第i - 1个空余位置相邻或者不相邻。

相邻的话只要比较第i个数和第i - 1个数，不相邻的话要比较第i个数和它的前一个以及第i - 1个数和它后一个。

有以下几个注意点：

    j要比第i个数+第i - 1个数大，当然比i要小。
    （方便起见我给i = 1的时候赋了初值）赋初值得时候也需要分类，判断第一个空余位置是否在原排列的第一位，不然还要判断第一个数和它之前的数字对答案的贡献。
    最后结束别忘了如果最后一个空余位置在原序列不是最后，也要计算贡献。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 105
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int id[MAXN], a[MAXN], dp[MAXN][MAXN][2];

int main(){
    int n, m = 0;
    scanf("%d", &n);
    int tot1 = 0;
    rep(i, 1, n){
        int x;
        scanf("%d", &x);
        if(!x){
            m++;
            id[m] = i;
            a[i] = -1;
        }
        else{
            a[i] = x % 2;
            if(x % 2) tot1++;
        }
    }
    int l = (n + 1) / 2 - tot1;
    rep(i, 1, m)
        rep(j, 0, l)
            rep(k, 0, 1) dp[i][j][k] = INF;
    if(id[1] == 1){
        dp[1][0][0] = 0;
        dp[1][1][1] = 0;
    }
    else{
        dp[1][0][0] = 0 ^ a[id[1] - 1];
        dp[1][1][1] = 1 ^ a[id[1] - 1];
    }
    rep(i, 2, m)
        rep(j, 0, min(i, l))
            rep(k, 0, 1){
                dp[i][j][k] = INF;
                if(j < k) continue;
                if(id[i - 1] < id[i] - 1){
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - k][0] + (0 ^ a[id[i - 1] + 1]) + (k ^ a[id[i] - 1]));
                    if(j >= k + 1) dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - k][1] + (1 ^ a[id[i - 1] + 1]) + (k ^ a[id[i] - 1]));
                }
                else{
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - k][0] + (0 ^ k));
                    if(j >= k + 1) dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - k][1] + (1 ^ k));
                }
            }
    int s1 = dp[m][l][0], s2 = dp[m][l][1];
    if(id[m] != n){
        s1 += 0 ^ a[id[m] + 1];
        s2 += 1 ^ a[id[m] + 1];
    }
    int ans = min(s1, s2);
    rep(i, 1, n - 1){
        if(a[i] == -1 || a[i + 1] == -1) continue;
        ans += a[i] ^ a[i + 1];
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Mr_Skirt (赞：3)

这种又像贪心又像dp的题当然是要使用随机化算法了（其实是dp太难想了）。

首先先明确这道题要求的是什么，其实是这个式子：

$
f(a)=\sum\limits_{i=2}^{n} parity(a_{i-1}) \oplus parity(a_i)
$

由于缺失的数字要么是奇数，要么是偶数，所以问题转化为如何将这些奇数和偶数填进数组使得相邻两数之间的奇偶性不同的对数最少。

由于没有什么明显的性质，dp式子也不好推，看一下数据范围$n\leq100$，那么我们显然可以用爬山/模拟退火等随机化算法搞一搞。

我们先从估价函数开始分析，对于这道题估价函数只需要$O(n)$的复杂度，完全可以接受。

接下来我们考虑枚举后继状态的转移，运用爬山的思想，我们只需要选择后继状态里面$f(a')$比当前状态小且最小的那个$a'$就行了。如果发现没有任何后继状态比这个状态更好我们就可以退出爬山了。具体的枚举方式可以是交换两个奇偶性不同的填充数字，形成一个新的排列。

我第一次尝试的就是**随机化爬山**算法。一般来说，使用随机爬山算法足以应付大部分随机化题目，但是发现爬山在本题有一个致命的缺陷。设状态$x$为当前最优状态，当$f(a')=f(x)$的时候爬山算法是不会转移到$a'$的。但是这题的函数是可以长这个样子的

![](https://cdn.luogu.com.cn/upload/image_hosting/317wgxgo.png)

于是随机爬山算法的很多起始点都会被这块平原阻挡，无法到达全局最优解。此时我们就需要对$f(a')=f(x)$状态的转移进行优化，引入模拟退火的温度概念。每次遇到与当前最优解相同的状态都用一个概率$e^{-\frac{1}{T}}$去接受它，接受的概率会随着文读的下降而下降，而与模拟退火不同的是我们不接受任何不优的$a'$。因为这题的特殊性质，$f(a')<f(x)$基本上是不会产生更优解，反而会浪费计算资源的。

加入了这个优化以后就能以相当高的几率得到最优解，同时我并没有对运行时间进行什么优化，这个算法实际上还可以更快。具体实现可以参考我的代码：

```cpp
mt19937 mt(15784371);
int a[MAXN], b[MAXN], p[MAXN];
int bin[MAXN];

// 估价函数
int eval() {
    int cnt = 0;
    for (int i = 0; i < m; i++) a[b[i]] = p[i];
    for (int i = 1; i < n; i++) cnt += (a[i - 1] & 1) ^ (a[i] & 1);
    return cnt;
}
int hill_climbing() {
    bool swp;
    int ans = eval();
    double T = 100;
    int cnt = 0;
    do {
        swp = false;
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                if (p[i] == p[j]) continue;
                swap(p[i], p[j]);
                int e = eval();
                if (e < ans) {
                    // 遇到更优解一定转移
                    swp = true, ans = e;
                } else if (e == ans) {
                    // 如果解状态并不优，则机率接受它
                    double p = exp(-1 / T);
                    if (mt.max() * p > mt()) swp = true, ans = e;
                } else {
                    // 否则回退状态
                    swap(p[i], p[j]);
                }
            }
        }
        T *= 0.85;
        cnt++;
        // 结合了爬山算法和模拟退火，要么局部最优解跳出，要么温度过低跳出
    } while (swp && T > 1e-6);
    return ans;
}

void shuffle(int* a, int sz) {
    for (int i = sz - 1; i >= 0; i--) {
        int j = mt() % (i + 1);
        swap(a[i], a[j]);
    }
}
int search() {
    int ans = INF2;
    for (int t = 0; t < 20; t++) {
        shuffle(p, m);
        ans = min(ans, hill_climbing());
    }
    return ans;
}
int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        // b数组代表第i个空是a数组的第几个元素
        if (!a[i]) b[m++] = i;
        bin[a[i]] = true;
    }
    int odd = 0;
    for (int i = 1; i <= n; i++)
        if (!bin[i])
            if (i & 1) odd++;
    // p数组代表第i个空是奇数还是偶数
    for (int i = 0; i < odd; i++) p[i] = 1;
    for (int i = odd + 1; i < m; i++) p[i] = 0;
    printf("%d\n", search());
    return 0;
}
```

---

## 作者：gyh20 (赞：2)

DP

令$f[i][j][0/1]$表示使用$i$个奇数，$j$个偶数，上一位为奇/偶的最小值。

如果当前位置为$0$则可以随便放，否则当前位置的奇偶性固定

若当前位置为奇数：


$f[i][j][0]=min(f[i-1][j][0],f[i-1][j][1]+1)

偶数同理。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0,f=1;
	re char v=getchar();
	while(v<'0'||v>'9'){
		if(v=='-')f=-1;
	v=getchar();}
	while(v>='0'&&v<='9'){
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t*f;
}
int n,a[1002],ans,f[102][102][102][2],nod,nev;
int main(){
n=read();
nod=(n+1)/2;
nev=n/2;
for(re int i=1;i<=n;++i){a[i]=read();
}
memset(f,127,sizeof(f));
f[0][0][0][0]=f[0][0][0][1]=0;
int k;
for(re int i=1;i<=n;++i){
	if(a[i]){
		if(a[i]&1){
			for(re int j=1;j<=i;++j){
				k=i-j;
					f[i][j][k][1]=min(f[i-1][j-1][k][1],f[i-1][j-1][k][0]+1);
			}
		}
		else{
			for(re int j=0;j<i;++j){
				k=i-j;
					f[i][j][k][0]=min(f[i-1][j][k-1][0],f[i-1][j][k-1][1]+1);
				
			}
		}
	}
	else{
		for(re int j=1;j<=i;++j){
				k=i-j;
					f[i][j][k][1]=min(f[i-1][j-1][k][1],f[i-1][j-1][k][0]+1);
			}
		for(re int j=0;j<i;++j){
				k=i-j;
					f[i][j][k][0]=min(f[i-1][j][k-1][0],f[i-1][j][k-1][1]+1);
				
			}
		
	}
 
}
printf("%d",min(f[n][nod][nev][0],f[n][nod][nev][1]));
}

```


---

## 作者：Li_Yichen (赞：1)

## 过程
先来表示状态，$dp[i][j][0]$ 表示前 $i$ 个数中填了 $j$ 个数组最后一个填的是偶数的答案。同理 $dp[i][j][1]$ 表示前 $i$ 个数中填了 $j$ 个数组最后一个填的是奇数的答案。

偶数的状态转移方程为 $dp[i][j][0] = \min(dp[i-1][j-1][0], dp[i-1][j-1][1]+1)$ 。同理，奇数的为 $dp[i][j][1] = \min(dp[i-1][j][0]+1,dp[i-1][j][1])$ 。至此，我们已经退完了这道题的大部分代码，最后的答案为两种情况的最小值，即为 $\min(dp[n][n/2][0],dp[n][n/2][1])$ 。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[105];
int dp[105][105][2];
int main(){
	memset(dp,0x3f,sizeof(dp));
	dp[0][0][0] = dp[0][0][1] = 0;
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		for(int j=0;j<=n/2;j++){
			if(j>0 && a[i]%2==0){
				dp[i][j][0] = min(dp[i-1][j-1][0], dp[i-1][j-1][1]+1);
			}
			if(!a[i] || a[i]%2==1){
				dp[i][j][1] = min(dp[i-1][j][0]+1,dp[i-1][j][1]);
			}
		}
	}
	cout << min(dp[n][n/2][0],dp[n][n/2][1]);
	return 0;
}

```

---

## 作者：CountState (赞：0)

dp，设 $dp[i][j][0/1]$ 表示对于前 $i$ 个数，有 $j$ 个偶数，且最后一位是 $0/1$ 时的最小答案。

可以得到转移：

- $dp[i][j][1]=\min(dp[i-1][j][0]+1,dp[i-1][j][1])$
- $dp[i][j][0]=\min(dp[i-1][j-1][1]+1,dp[i-1][j-1][0])$

如果原数组内第 $i$ 位为 $0$ 那么两个转移都可以进行，否则如果第 $i$ 位为奇数就转移 $dp[i][j][1]$，第 $i$ 位为偶数就转移 $dp[i][j][0]$。

最后答案为 $\min(dp[n][n/2][1],dp[n][n/2][0])$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=110;
int n,a[N],ans,dp[N][N][2];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	memset(dp,0x3f,sizeof(dp));
	
	dp[0][0][0]=dp[0][0][1]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n/2;j++){
			if(a[i]==0){
			    dp[i][j][1]=min(dp[i-1][j][0]+1,dp[i-1][j][1]);
			    if(j!=0) dp[i][j][0]=min(dp[i-1][j-1][1]+1,dp[i-1][j-1][0]);
	        }
	        else if(a[i]%2==0&&j){
				dp[i][j][0]=min(dp[i-1][j-1][1]+1,dp[i-1][j-1][0]);
			}
			else if(a[i]%2){
				dp[i][j][1]=min(dp[i-1][j][0]+1,dp[i-1][j][1]);
		    }
		}
    }
    cout<<min(dp[n][n/2][1],dp[n][n/2][0]);
}
```

---

## 作者：zhouzihang1 (赞：0)

# CF1286A Garland 题解

[题目链接](https://www.luogu.com.cn/problem/CF1286A)

高端的题目往往只需要简单的 dp。

## 题意

给出长度为 $n$ 的排列 $p$，其中有一些数被删去了，用 $0$ 表示。

用被删去的数填充所有 $0$ 的位置，使得**相邻**两个数奇偶性不同的对数最少。

输出最少的对数，不需要给出方案。

$1 \le n \le 10^2, 1 \le p_i \le n$。

## 思路

注意到  $1 \le n \le 10^2$ 可以 dp。

其次，此题不关心用了哪些数是否重复，只关心奇偶性。

所以我们可以设 $f_{i,j,0/1}$ 表示当前考虑到第 $i$ 位，已经填充了 $j$ 个奇数（当然偶数也可以），最后一位是偶数还是奇数。

然后是分类讨论：

记操作一表示 $f_{i,j,0} \leftarrow \min \limits _{j=0} ^{min(i,\frac{n+1}{2})}{(f_{i-1,j,0},f_{i-1,j,1}+1)}$。

操作二表示 $f_{i,j,1} \leftarrow \min \limits _{j=1} ^{min(i,\frac{n+1}{2})}{(f_{i-1,j-1,1},f_{i-1,j-1,1}+1)}$。

- 若 $p_i=0$，执行操作一和操作二。

- 若 $p_i \neq 0$ 且 $p_i \equiv 1 \pmod 2$，执行操作二。

- 若 $p_i \neq 0$ 且 $p_i \equiv 0 \pmod 2$，执行操作一。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e2+5;
int n,a[N],f[N][N][2];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	f[0][0][0]=f[0][0][1]=0;//初始化
	for(int i=1;i<=n;i++)
	{
		if(a[i]==0)
		{
			for(int j=0;j<=min(i,(n+1)/2);j++)
				f[i][j][0]=min(f[i-1][j][0],f[i-1][j][1]+1);//操作一
			for(int j=1;j<=min(i,(n+1)/2);j++)
				f[i][j][1]=min(f[i-1][j-1][1],f[i-1][j-1][0]+1);//操作二
		}
		else if(a[i]&1)
			for(int j=1;j<=min(i,(n+1)/2);j++)
				f[i][j][1]=min(f[i-1][j-1][1],f[i-1][j-1][0]+1);//操作二
		else
			for(int j=0;j<=min(i,(n+1)/2);j++)
				f[i][j][0]=min(f[i-1][j][0],f[i-1][j][1]+1);//操作一
	}
	printf("%d\n",min(f[n][(n+1)/2][0],f[n][(n+1)/2][1]));//一定有 (n+1)/2 个奇数
	return 0;
}
```

---

## 作者：FJ_OIer (赞：0)

贪心题。

将序列分成几个全 $0$ 段，则有以下关系：

- 不难发现若段两端（这里是指将全 $0$ 段包围的两个数）的数奇偶性不同，则此空位无论怎么填都必然对答案产生 $1$ 的贡献。
- 若奇偶性相同，则如果全 $0$ 段全填与其奇偶性相同的数，就不会对答案产生贡献。否则必然产生 $2$ 的贡献。

于是引出我们的贪心策略：首先求出待填的奇数、偶数数量，将两端奇偶性相同的全 $0$ 段按长度排序，优先满足长度较短的段。

但是首尾的全 $0$ 段较为特殊，与中间的全 $0$ 段一样只不过贡献变成了 $1$。在结束上述贪心策略后特判即可。

时间复杂度 $O(n)$，非常优秀。

~~屎山代码一百多行，搞不懂此题为何范围这么小？？？~~
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ls,cnt,tot,ji,ou,ans,s,e;
int a[101],p[101],Ji[101],Ou[101];
int main(){
	cin>>n;
	if (n==1){//特判n=1 
		cout<<0;
		return 0;
	}
	ji=(n+1)/2;
	ou=n/2;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		if (a[i]){
			if (!ls){
				s=i;
			}
			e=i;
			if (ls){
				if (i-ls>1){
					if ((a[ls]&1)&&(a[i]&1)){
						Ji[++cnt]=i-ls-1;//两端奇数全0段 
					}
					if (!(a[ls]&1)&&!(a[i]&1)){
						Ou[++tot]=i-ls-1;//两端偶数全0段 
					}
				}
				if ((a[ls]&1)!=(a[i]&1)){//一奇一偶全0段 
					ans++;
				}
			}
			//奇偶数数量 
			ls=i;
			ji-=(a[i]&1);
			ou-=!(a[i]&1); 
		}
	}
	if (!ls){//特判序列全0 
		cout<<1;
		return 0;
	}
	sort(Ji+1,Ji+cnt+1);
	sort(Ou+1,Ou+tot+1);
	for (int i=1;i<=cnt;i++){
		if (ji>=Ji[i]){
			ji-=Ji[i];
		}else{
			ans+=(cnt-i+1)*2;//计算贡献 
			break;
		}
	}
	for (int i=1;i<=tot;i++){
		if (ou>=Ou[i]){
			ou-=Ou[i];
		}else{
			ans+=(tot-i+1)*2;
			break;
		}
	}
	//特判首尾 
	int p=INT_MAX,q=INT_MAX,mi,ma;
	if (s>1&&(a[s]&1)){
		p=s-1;
	}
	if (e<n&&(a[e]&1)){
		q=n-e;
	}
	mi=min(p,q);
	ma=max(p,q);
	if (mi<INT_MAX){
		if (ji>=mi){
			ji-=mi;
		}else{
			ans++;
		}
		if (ma<INT_MAX){
			if (ji>=ma){
				ji-=ma;
			}else{
				ans++;
			}
		}
	}
	p=q=INT_MAX;
	if (s>1&&!(a[s]&1)){
		p=s-1;
	}
	if (e<n&&!(a[e]&1)){
		q=n-e;
	}
	mi=min(p,q);
	ma=max(p,q);
	if (mi<INT_MAX){
		if (ou>=mi){
			ou-=mi;
		}else{
			ans++;
		}
		if (ma<INT_MAX){
			if (ou>=ma){
				ou-=ma;
			}else{
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

### 贪心

我们考虑区间 $[l,r]$，其中都是 $0$，但是 $p_{l-1},p_{r+1}$ 都没有被删去。

如果 $p_{l-1},p_{r+1}$ 奇偶性不同。

- 只有一种情况，无论怎么填代价都可以是 $1$。

如果 $p_{l-1},p_{r+1}$ 奇偶性相同。

- 如果我们填入 $r-l+1$ 个和 $p_{l-1},p_{r+1}$ 奇偶性相同的数，代价为 $0$。

- 否则为 $2$。

$p_{l-1},p_{r+1}$ 奇偶性不同的情况我们可以忽略，我们只考虑奇偶性相同的情况。

我们把那些满足 $p_{l-1},p_{r+1}$ 奇偶性相同的区间拿出来，以长度从小到大排序，优先满足长度小的即可。

对于边界（即左右两端的 $0$ 串），我们发现其代价要么是 $0$ 要么是 $1$，那么我们其实也可以暴力枚举其情况，就 $4$ 种情况。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=1e2+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e9;

int n,m;

int p[N], tot[2];
int q[2][N];
int ans=INF,res;

void pre(){
    int lst=0;
	for(int i=1;i<=n+1;i++){
		if(p[i]){
			if(p[i]==p[lst])q[p[i]-2][i-lst-1]++;//如果0串开头和结尾奇偶性相同，则标记 
			else ++res;
			lst=i;
		}
    }
}

int solve(int n) {
	res=0;
	pre();
	for(int i=0;i<2;i++){
		int mx=tot[i];
		for(int x=0;x<=mx;x++){
			while(q[i][x]&&x<=mx){
				mx-=x;--q[i][x];
			}
		}
	}

	for(int i=0;i<=n;i++){
		res+=2*(q[0][i]+q[1][i]);
		q[0][i]=q[1][i]=0;
	}

	return res;
}
signed main(){
	cin>>n;
	tot[0]=n/2;//偶数个数 
	tot[1]=(n+1)/2;//奇数个数 

	for(int i=1;i<=n;i++){
		cin>>p[i];
		if(p[i]){
			p[i]%=2;--tot[p[i]];
			p[i]+=2;//偏移，方便区分偶数和删除的数 
		}
	}
//	cout<<tot[1]<<' '<<tot[0]<<endl;
	for(int i=0;i<=1;i++)//通过枚举左右端点的奇偶性来枚举左右两端的0串的处理方法
		for(int j=0;j<=1;j++){
			p[0]=i+2;
			p[n+1]=j+2;
			ans=min(ans,solve(n));
		}

	cout<<ans;
}

```







---

