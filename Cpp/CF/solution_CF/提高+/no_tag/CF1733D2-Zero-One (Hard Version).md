# Zero-One (Hard Version)

## 题目描述

两个长度为 $n$ 的二进制字符串 $a$ 和 $b$。你可以进行如下操作若干次（可以为0次）：

- 选两个数 $l,r(l<r$)，对 $a_l,a_r$ 取反。
- 如果 $l+1=r$，代价为 $x$。否则，代价为 $y$。

## 样例 #1

### 输入

```
6
5 8 9
01001
00101
6 2 11
000001
100000
5 7 2
01000
11011
7 8 3
0111001
0100001
6 3 4
010001
101000
5 10 1
01100
01100```

### 输出

```
8
10
-1
6
7
0```

# 题解

## 作者：灵茶山艾府 (赞：19)

### 提示 1

首先统计 $a[i] \ne b[i]$ 的 $i$，记到数组 $p$ 中，由于每次操作只能改变 $2$ 个这样的 $i$，那么如果 $p$ 的长度是奇数，则输出 $-1$。

### 提示 2

分类讨论：$y \le x$ 和 $y > x$。

### 提示 3

设 $m$ 为 $p$ 的长度。对于 $y \le x$：

- 如果 $m=2$ 且 $p[0]+1=p[1]$，则答案为 $\min(2y, x)$，因为可以找个不相邻的位置充当「中转站」（注意 $n\ge 5$）；
- 否则答案为 $m/2 \cdot y$，方案是把 $p[i]$ 和 $p[i+m/2]$ 一组。


### 提示 4

对于 $y > x$，可以用动态规划求解。

### 提示 5

设 $f[i]$ 表示修改 $p$ 的前 $i$ 个位置的最小花费，那么对于 $p[i]$，有两种方案：

1. 找个不相邻的位置操作，花费 $y$，那么对于 $p[i]$ 相当于花费 $y/2$，因此
    $$
    f[i] = f[i-1] + y/2
    $$
2. 不断找相邻的位置操作，把 $p[i]$ 和 $p[i-1]$ 一组，那么需要操作 $p[i]-p[i-1]$ 次，因此
    $$
    f[i] = f[i-2] + (p[i]-p[i-1])\cdot x
    $$

两者取最小值，即
$$
f[i] = \min(f[i-1] + y/2, f[i-2] + (p[i]-p[i-1])\cdot x)
$$

初始值 $f[0]=0$，$f[1]=y$，答案为 $f[m]$。

代码实现时，为了方便处理 $y/2$，可以把所有数都乘 $2$，最后再除以 $2$。

此外，计算 $f$ 的过程可以用两个变量滚动计算。

### 答疑

**问**：为什么花费 $y$ 的时候，不用考虑相邻的情况？

**答**：因为 $y>x$，如果相邻，从 $f[i-2]$ 转移过来是更优的。

**问**：转移方程没有对选了多少个 $y$ 加以限制，如果选了奇数个 $y$ 怎么办？

**答**：注意 $m$ 是偶数，那么一定会选偶数个 $y$，你可以从记忆化搜索的角度来思考这一点。

### 代码（Golang）

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var T, x, y int64
	var a, b []byte
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &a, &x, &y, &a, &b)
		p := []int{}
		for i, c := range a {
			if c != b[i] {
				p = append(p, i)
			}
		}
		m := len(p)
		if m%2 > 0 {
			Fprintln(out, -1)
		} else if m == 0 || y <= x {
			if m == 2 && p[0]+1 == p[1] {
				Fprintln(out, min(y*2, x))
			} else {
				Fprintln(out, int64(m/2)*y)
			}
		} else {
			f, g := int64(0), y
			for i := 1; i < m; i++ {
				f, g = g, min(g+y, f+int64(p[i]-p[i-1])*x*2)
			}
			Fprintln(out, g/2)
		}
	}
}

func min(a, b int64) int64 { if a > b { return b }; return a }
```

### 复杂度分析

- 时间复杂度：$O(n)$。
- 空间复杂度：$O(n)$。


---

## 作者：Poncirus (赞：6)

题解 [CF1733D2](https://www.luogu.com.cn/problem/CF1733D2)。

以下内容还原了赛时的思考过程，可能较为冗长，但同时也较为细致。

---

没做过简单版本，模拟赛上遇到，乍一看是个贪心，但贪心思维太弱想不到怎么贪。所以思考其他方法。

下文称同时取反 $a_i$ 和 $a_j$ 的一次操作为「取反 $(a_i, a_j)$」，称 $a_i=b_i$ 的状态为「匹配」。

---

### 思维关键点

若我们想要将 $(a_i,a_j)$ 取反，我们可以怎么做？

不难发现，分 $a_i$ 与 $a_j$ 相邻和不相邻两种情况：

1. $a_i$ 与 $a_j$ 相邻：

   1. 直接取反，代价为 $x$。
   1. 寻找到一个与 $a_i$ 和 $a_j$ 都不相邻的 $a_k$，先将 $(a_i,a_k)$ 取反，再将 $(a_j,a_k)$ 取反，代价为 $2\times y$。
1. $a_i$ 与 $a_j$ 不相邻：

   1. 直接取反，代价为 $y$。
   1. 将 $(a_i,a_{i + 1}),(a_{i + 1}, a_{i + 2}),\cdots,(a_{j - 1}, a_{j})$ 取反，代价为 $(j - i)\times x$。
   
   
接下来考虑另一个问题：我们要取反哪些 $(a_i,a_j)$ 呢？

假设现在有 $a_p$ 与 $b_p$ 不匹配，$a_q$ 与 $b_q$ 不匹配，那么我们肯定选择将 $(a_p,a_q)$ 取反。

原因很简单，假设有 $a_k=b_k$，如果我们将 $(a_p,a_k)$ 取反，那么 $a_k\ne b_k$，我们需要额外的一次与 $a_k$ 有关的操作将其复原。如果我们挑选一个 $a_l=b_l$，并将 $(a_k,a_l)$ 取反，那么 $a_l$ 与 $b_l$ 又会不匹配，又需要一次操作；如果挑选一个 $a_l\ne b_l$，并将 $(a_k,a_l)$ 取反，那么为什么不能在一开始就将 $(a_p,a_l)$ 取反呢？此时的 $a_k$ 相当于一个中继，而这种情况我们已经在取反 $(a_p,a_l)$ 时考虑到了。

也就是说，我们每次取反 **只** 选择两个无法与 $b$ 匹配的 $a$。

那么，有没有一种情况，让我们无法选择两个无法匹配的值呢？

那就是不匹配的值的数量有奇数个，才会让我们两个两个选的时候有元素落单。

不妨思考一次取反操作所有可能的情况（假设不受上面的结论限制）：

1. 取反一个匹配值和一个不匹配值

   此时匹配值变为非匹配，不匹配值变为匹配，不匹配的元素总数不变。
1. 取反两个不匹配值

   两个不匹配值都变为匹配，不匹配元素的总数量增加 $-2$。
1. 取反两个匹配值

   两个匹配值都变为非匹配，不匹配元素的总数量增加 $2$。

综上，一次操作对不匹配元素总数带来的更改只可能为 $0,2,-2$，均为偶数。当不匹配元素为奇数时，必定无法将其更改至刚好为 $0$。此时输出 $-1$。

我们上面结论的可实现性也得到了保障：只取反两个不匹配的 $a$，不会有元素落单。

下文记从前往后第 $i$ 个与 $b$ 不匹配的 $a$ 的下标为 $d_i$。

---
   
### 确定实现方法
   
发现 $\sum n\le 5\times 10^3$，确定算法复杂度为 $\mathcal O(n^2)$。

首先不难想到暴力搜索，每次枚举将哪一对 $(d_i, d_j)$ 取反。

亦或是使用 `bitset` 记录哪些非匹配值已被取反（被取反为 $1$，否则为 $0$），枚举数对暴力 DP 更新最小值。

但以上两种方法铁定超时。

受到上面两种方法的启发，扩展思维，我们发现：

* 取反操作的顺序不会影响最终答案。

   因为每个数被取反的次数一定，最终结果也就一定。
* 我们可以通过 DP 的方式寻找最小值。

设计状态。

不妨考虑让问题麻烦起来的是什么，对于 $d_i$ 与 $d_j$ 不相邻时的取反，我们无法得知 $d_i$ 需要哪一个 $d_j$（而对于 $d_i$ 与 $d_j$ 相邻的情况，$d_j$ 就是 $d_{i + 1}$，位置是确定的）。

但我们同时也发现，与相邻时的代价不同，不相邻时的操作代价与 $i$，$j$ 的具体值无关。

所以不妨用 $f_{i,j}$ 表示，已枚举到 $d_i$，前面有 $j$ 个数需要后面 **与它们不相邻的数** 用以和它们配对取反。

假设已枚举到 $d_i$，当前面有 $s$ 个数需要配对时，有以下的情况：

* 当 $s = 1$，即只有一个数需要配对时：

   * 如果这个数是 $d_{i - 1}$，那么代价为 $2\times y$。
   
      注意，这里只枚举了需要不相邻的数来配对的情况，相邻的情况将会另外计算，所以代价不能为 $x$。
   * 否则，代价为 $y$。
* 当 $s>1$ 时，即有多个数需要配对时：

   不管 $d_{i-1}$ 是否需要配对，我们都不选它。因为选它的代价是 $2\times y$，而随便选另一个待配对数的代价都只有  $y$。

那么问题来了，我咋知道它们相不相邻？

再多开一维 $0/1$ 状态，记录最后一个需要与其他后面的元素配对值是否是 $a_{i-1}$ 即可。

假设现在已经枚举到 $f_{i,j,0/1}$，即已枚举完 $d_i$，有 $j$ 个元素需要配对。

则更新 $d_{i+1}$ 的状态：

* 若我们想要让 $d_{i+1}$ 与后面的元素配对，则代价至少为 $y$。至于是否会因为待配对元素相邻而额外增加 $y$ 的代价，我们在待配对元素处计算。

   $$
   f_{i+1,j+1,1}\gets\min(f_{i,j,0},f_{i,j,1}) + y
   $$
* 若我们想要让 $d_{i+1}$ 与其相邻的 $a_{i+2}$ 匹配，那么 $d_{i+2}$ 就不需要再与后面的元素配对了，故最后一维为 $0$。

   $$
   f_{i+2,j,0}\gets\min(f_{i,j,0},f_{i,j,1})+(d_{i+2}-d_{i+1})\times x
   $$
* 如果我们想让 $d_{i+1}$ 与前面的待配对元素配对：

   在此种大前提下，$d_{i+1}$ 一定不需要与后面的元素配对，故最后一维为 $0$。

   * 当 $j=1$ 且 $d_i+1=d_{i+1}$ 时，即存在其相邻元素，且只有一个配对可选项时：
  
      * 如果这个数是 $d_{i}$，则 $d_{i+1}$ 必须与相邻元素配对。
      
      $$
      f_{i+1,j-1,0}\gets f_{i,j,1}+y
      $$
      
      因为在计算 $f_{i,j,1}$ 时已计算了一个 $y$，所以此处只用加一个 $y$。
      * 否则，该元素完成配对，不产生任何代价。
      
         $$
         f_{i+1,j-1,0}\gets f_{i,j,0}
         $$
   * 否则，随意选择前面的一个数。
   
      因为此时，要么前面有除了相邻元素的其他数可选，要么根本没有相邻元素，所以该数完成配对不会产生任何代价（因为 $y$ 已经加过了）。
      
      $$
      f_{i+1,j-1,0}\gets \min(f_{i,j,0},f_{i,j,1})
      $$

至此，全部情况讨论完毕。因为不能让最后一个元素再去与后面的元素配对，最终答案为 $f_{tot,0,0}$，其中 $tot$ 为 $d$ 数组长度。

时间复杂度 $\mathcal O(n^2)$，空间复杂度 $\mathcal O(n^2)$。

因为 $x,y\le 10^9$，最坏情况下需要加 $\dfrac n2$ 次，故需要为 DP 数组开 `long long`。尽管热心人士 @[cqbztzl](/user/428358) 帮助我计算得出使用空间约为 300 兆，但仍然会 MLE。

不难发现，第一维枚举到 $i$ 时，只需要更新第一维为 $i+1$ 和 $i+2$ 状态的值，而不需要其他任何 DP 值，故将第一维模 $3$，滚动为 $0\sim 2$。

---

```cpp
// 代码里可能有一些赛时的神秘注释 hhh
namespace XSC062 {
using namespace fastIO;
const ll inf = 1e18;
const int maxn = 5e3 + 5;
ll x, y;
int T, n, tot;
ll f[3][maxn][2];
int diff[maxn], a[maxn], b[maxn];
inline ll min(ll x, ll y) {
	return x < y ? x : y;
}
inline void upd(int i, int j, int k, ll y) {
	f[i % 3][j][k] = min(f[i % 3][j][k], y);
	return;
}
int main() {
	read(T);
	while (T--) {
		read(n), read(x), read(y);
		tot = 0;
		for (int i = 1; i <= n; ++i)
			getnum(a[i]);
		for (int i = 1; i <= n; ++i) {
			getnum(b[i]);
			if (a[i] != b[i])
				diff[++tot] = i;
		}
		if (tot & 1) {
			puts("-1");
			continue;
		}
		memset(f, 0x3f, sizeof (f));
		f[0][0][0] = 0;
		for (int i = 0; i <= tot; ++i) {
			for (int j = 0; j <= i; ++j) {
				// 新增起点
				if (i + 1 <= tot) {
					upd(i + 1, j + 1, 1,
						min(f[i % 3][j][0],
							f[i % 3][j][1]) + y);
				}
				// 碾过去 
				if (i + 2 <= tot) {
					upd(i + 2, j, 0,
						min(f[i % 3][j][0],
							f[i % 3][j][1]) +
							(diff[i + 2] -
							diff[i + 1]) * x);
				}
				// 使用起点
				if (j > 0 && i + 1 <= tot) {
					if (j == 1 && diff[i] + 1 ==
										diff[i + 1]) {
						upd(i + 1, j - 1, 0,
								f[i % 3][j][1] + y);
						upd(i + 1, j - 1, 0,
								f[i % 3][j][0]);
					}
					else {
						upd(i + 1, j - 1, 0,
							min(f[i % 3][j][0],
								f[i % 3][j][1]));
					}
				}
				if (i != tot) {
					f[i % 3][j][0] =
						f[i % 3][j][1] = inf;
				}
			}
		}
		print(f[tot % 3][0][0], '\n');
	}
	return 0;
}
} // namespace XSC062
```

---

## 作者：mayike (赞：5)

对于我这种 $\mathcal{O}(n^2)$ 的~~垃圾~~来说这题就比较没实力了。

### [题目传送门](https://www.luogu.com.cn/problem/CF1733D2)

## 思路

首先，我们记 $cnt$ 为 $a,b$ 不配对的个数，$s$ 数组记录它们的位置。

无解情况当 $cnt$ 为奇数时成立，显然。

对于题目有 $5 \le n$ 且 $y \le x$ 的情况：按简单版，当 $cnt=2$ 且 $s_1+1=s_2$，$ans=\min(x,2\times y)$，反之 $ans=cnt\div2\times y$。

之后就是 $x< y$ 的情况了。

### 证伪的思路

------------

我开始是和 easy 版一样想，想了个 $\mathcal{O}(n)$ 的 dp 加贪心的结合。这里我把 $s$ 中相邻的数分在了一组，即 $s_i+1=s_{i+1}$ 的情况，那么对于相邻两组，因为至多给对方 $1$ 个数来消耗，那么 $i$ 给 $i+1$ 和 $i+1$ 给 $i$ 没区别，所以我统一定为 $i+1$ 给 $i$。另定义 $r_i$ 表示一组的结尾，$len_i$ 表示个数，$ct$ 表示组数，那么对于这个状态转移只用处理相邻两个间的问题。

定义状态 $f_{i,1}$ 和 $f_{i,0}$ 表示给了 $i-1$ 一个或没给，转移方程就很简单了。

$$f_{i,0}=\begin{cases} f_{i-1,1}+(len_{i-1}-1)\div2\times x & len_{i-1} \operatorname{is} \operatorname{odd} \\ f_{i-1,0}+len_{i-1}\div 2\times x & len_{i-1} \operatorname{is} \operatorname{even}\end{cases}$$

$$f_{i,1}=\begin{cases} f_{i-1,0}+\min((r_i-len_i+1-r_{i-1})\times x,y)+(len_{i-1}-1)\div 2\times x & len_{i-1} \operatorname{is} \operatorname{odd} \\ f_{i-1,1}+\min((r_i-len_i+1-r_{i-1})\times x,y)+(len_{i-1}-2)\div 2\times x & len_{i-1} \operatorname{is} \operatorname{even}\end{cases}$$

$$ans=\begin{cases} f_{ct,1}+(len_{ct}-1)\div 2\times x & len_{ct} \operatorname{is} \operatorname{odd} \\ f_{ct,0}+len_{ct}\div 2\times x & len_{ct} \operatorname{is} \operatorname{even}\end{cases}$$

然后就[这样](https://www.luogu.com.cn/record/158884725)了，[代码](https://codeforces.com/contest/1733/submission/260754029)。

这里给出一个想了一会的 hack：

```cpp
1
15 3 4
110010011010011
000000000000000
out:14
ans:13
```

然后我就发现我代码废掉了，发现其实在某些跨越大区间的地方用 $y$ 可能比两点直接慢慢跑要小的多，故我结合 $5 \le n \le 5000$ 想到了 $\mathcal{O}(n^2)$ 的简单区间 dp。

### 可过的思路

------------

对于 $s,cnt$ 的再次声明：对于 $1\le i\le n$，若 $a_i \ne b_i$，$cnt$ 次数增加 $1$，并且 $s_{cnt}=i$。

我们对于 $s$ 的区分还是要的，定义 $f_{i,j}$ 为区间 $i$ 到 $j$ 的最小花费次数，这里的区间是 $s$ 中的区间，而非实际区间。

显然有 $f_{i,i}=+\infty$，因为单个数消不了。

$$f_{i,i+1}=\begin{cases}\min(2\times y,x) & s_i+1=s_{i+1} \\ \min(x\times (s_{i+1}-s_i),y) & s_i+1 \ne s_{i+1} \end{cases}$$

这个很正常，要么借助其他数多个 $y$，要么直接交换或慢慢用 $x$ 移过去。

纯 $f_{i,j}$ 就更简单了，自己看吧。

$$f_{i,j}=\min({f_{i+1,j-1}+y,f_{i+2,j}+\begin{cases}\min(2\times y,x) & s_i+1=s_{i+1} \\ \min(x\times (s_{i+1}-s_i),y) & s_i+1 \ne s_{i+1} \end{cases},f_{i,j-2}+\begin{cases}\min(2\times y,x) & s_{j-1}+1=s_j \\ \min(x\times (s_j-s_{j-1}),y) & s_{j-1}+1 \ne s_j \end{cases}})$$

**正确性证明**：假若对于 $f_{i,j}$ 时的操作必消耗 $i$，则只能是与 $i+1,j$ 相消耗，为何？考虑反证，不妨设有点 $k$ 且 $i+1<k<j$，$k$ 是 $i$ 这次相消的点，那么对于 $k-1$ 和 $k+1$ 就变成了相邻点。后续对于 $k-1$ 和 $k+1$ 的处理要么是互不影响，要么是花费 $y$ 的代价或用 $x$ 慢慢挪动，可对于挪动的距离绝没有 $k-1$ 到 $k$ 或 $k$ 到 $k+1$ 的少，显然代价一定更大。对于 $j$ 同理，证毕。

然后就没了，写题解好累，谢谢支持！

```cpp
#include<bits/stdc++.h>//
using namespace std;
#define int long long
const int N=5005;
int T,n,x,y,cnt,s[N],f[N][N];
string a,b;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cnt=0,cin>>n>>x>>y>>a>>b,a=' '+a,b=' '+b;
		for(int i=1;i<=n;i++)
		    if(a[i]!=b[i])s[++cnt]=i;
		if(cnt&1){cout<<"-1\n";continue;}
		if(y<=x)
			if(cnt==2)
				if(s[1]+1==s[2])cout<<min(x,2*y)<<"\n";
				else cout<<y<<"\n";
			else cout<<cnt/2*y<<"\n";
		else{
			for(int i=1;i<=cnt;i++)
				for(int j=i;j<=cnt;j++)f[i][j]=5e12;
			for(int i=1;i<cnt;i++)
				if(s[i]+1==s[i+1])f[i][i+1]=min(2*y,x);
				else f[i][i+1]=min(x*(s[i+1]-s[i]),y);
			for(int l=3;l<=cnt;l++)
				for(int i=1;i+l-1<=cnt;i++){
				    int j=i+l-1;
				    f[i][j]=min({f[i+1][j-1]+y,f[i+2][j]+(s[i]+1==s[i+1]?min(2*y,x):min(x*(s[i+1]-s[i]),y)),f[i][j-2]+(s[j-1]+1==s[j]?min(2*y,x):min(x*(s[j]-s[j-1]),y))});
				}cout<<f[1][cnt]<<""\n;
		}
	}
	return 0;
}
```

---

## 作者：Lgx_Q (赞：5)

$O(n)$ 解法。

首先需要 AC [CF1733D1](https://www.luogu.com.cn/problem/CF1733D1)

其次是本题。如果 $x>y$，那么还是原来的贪心做法。

接下来我们讨论当 $x<y$ 的做法。对于字符串 $a$ 中与 $b$ 不相同的字符位置，假设为 $p_1,p_2,...,p_m$。

首先，当 $m$ 为奇数时无解。

然后，如果利用连续一段的相邻交换，只会对相邻两个位置 $p_k,p_{k+1}(1≤k<m)$ 做贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/vziwojk9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如上图，在 $p_3,p_4$ 之间执行连续一段的相邻交换操作，会使得 $a_{p_3}=b_{p_3},a_{p_4}=b_{p_4}$，但是不能对 $p_2,p_4$ 之间执行交换操作，因为这样做 $a_{p_3}$ 的值不会改变，总有一种方案会比这种方案更优。

因此我们得出结论：连续一段相邻交换操作只会对相邻的 $p_k,p_{k+1}$ 做贡献。

但是如果不使用相邻操作呢？我们可以记录非相邻操作的操作次数的奇偶性（每两次操作花费 $y$）。

设状态 $f[i][0/1]$ 为完成了 $a_1,...,a_i$ 的修改，使用u的非相邻操作的奇偶性。

若 $i≠p_k$（$a_i=b_i$），那么直接转移 $f[i][0]=f[i-1][0],f[i][1]=f[i-1][1]$。

若 $i=p_k$ （$a_i≠b_i$），有两种情况：

1. 花费 $y$ 远程操作，此时 $f[i][0]=f[i-1][1]+y,f[i][1]=f[i-1][0]$（两次只会花费一个 $y$）。

2. 在 $p_{k-1},p_k$ 之间执行连续一段操作。此时 $f[i][0]=f[p_{k-1}-1][0]+(i-p_{k-1})x,f[i][1]=f[p_{k-1}-1][1]=(i-p_{k-1})x$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5010;
int t,n,x,y,cnt,p1,p2,f[maxn][2],ans;
char a[maxn],b[maxn];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld%s%s",&n,&x,&y,a+1,b+1);
		p1=p2=cnt=0;
		if(x>=y)
		{
			for(int i=1;i<=n;i++)
			{
				if(a[i]!=b[i])
				{
					++cnt;
					if(p1) p2=i;
					else p1=i;
				}
			}
			if(cnt&1)
			{
				printf("-1\n");
				continue;
			}
			if(cnt==0) ans=0;
			else if(cnt==2)
			{
				if(p1+1==p2) ans=min(x,y*2);
				else ans=y;
			}
			else ans=y*cnt/2;
			printf("%lld\n",ans);
			continue;
		}
		f[0][1]=0x3f3f3f3f3f3f3f3f;
		for(int i=1,j=0;i<=n;i++)
		{
			if(a[i]==b[i])
			{
				f[i][0]=f[i-1][0];
				f[i][1]=f[i-1][1];
			}
			else
			{
				f[i][0]=f[i-1][1]+y;
				f[i][1]=f[i-1][0];
				if(j)
				{
				    f[i][0]=min(f[i][0],f[j-1][0]+(i-j)*x);
				    f[i][1]=min(f[i][1],f[j-1][1]+(i-j)*x);
				}
				j=i;
			}
		}
		if(f[n][0]<0x3f3f3f3f3f3f3f3f) printf("%lld\n",f[n][0]);
		else printf("-1\n");
	}
	return 0;
}
```

---

## 作者：心灵震荡 (赞：2)

一道超级妙妙题。

注意到 D1 与 D2 的差别仅在于不再有 $x \ge y$ 的限制，那么正解一定包含了 D1 的部分。

先想想无解情况。

记 $m = \displaystyle \sum_{i = 1}^n [a_i \ne b_i]$，并记所有 $a_i \ne b_i$ 的位置为 $p_1, p_2, \cdots, p_m$，满足 $p_1 < p_2 < \cdots < p_m$。 一次操作会改变两个位置的状态，会使 $m$ 的值 $+2$,$-2$ 或不变。

那么当且仅当 $m$ 为偶数时有解，否则一定无解。

对于有解的情况，先考虑 $x \ge y$ 怎么做。此时取不相邻的比相邻的优，所以考虑每次尽可能取不相邻的位置。

- 若 $m>2$，一定可以按照某种方式将所有 $a_i, b_i$ 不同的点进行两两配对，使得不存在一对点中有相邻点。

  构造也很容易。考虑一组较劣的配对 $(p_1, p_2), (p_3, p_4), \cdots, (p_{m-1}, p_m)$，调整每对中右端点的位置，使其变为 $(p_1, p_4), (p_3, p_5), \cdots, (p_{m-2}, p_m), (p_{m-1}, p_1)$。这样的一组配对就满足了无相邻，答案为 $\frac{m}{2} \times y$，可以证明不存在更优的答案。

- 若 $m = 2$，就不能进行有效的调整，只能通过把 $p_1$, $p_2$ 和同一个数放在一起进行匹配，使重复的操作抵消掉，这样做的代价为 $2y$。若 $p_1=p_2 - 1$，答案为 $\min(2y, x)$；否则答案为 $y$。

上面的部分其实就是 D1。

下面来思考 $x < y$ 的做法。注意，**以下的所有说明均建立在 $x < y$ 的基础条件上，不保证在其他情况下成立。**

首先考虑单独的一对匹配 $(p_u, p_v)$（$p_u < p_v$）对答案的贡献，应当有通过 $y$ 完成与通过 $x$ 完成两种情况：

1. 直接花费 $y$ 的代价完成匹配；
2. 依次对 $(p_u, p_u + 1), (p_u + 1, p_u + 2), \cdots, (p_{v - 1}, p_v)$ 执行操作。容易发现，这样操作后仍然只改变了 $p_u, p_v$ 两个位置的值，代价为 $(p_v - p_u) \times x$。

两者取最小值，即为真正的贡献。

再证一个引理：对于任意四个位置 $p_i < p_j < p_k < p_l$，匹配 $(p_i, p_k), (p_j, p_l)$ 一定不优于 $(p_i, p_j), (p_k, p_l)$（也就是说，匹配形如下图的情况不存在）。

![](https://img.zshfoj.com/2591105de09d817bba473c406845cf4f1af8699f80b248197f27a0a8a13fbd1e.png)

考虑 $(p_i, p_k),(p_j, p_l)$ 对答案的贡献之和为 $\min(y, (p_k - p_i)\times x)+ \min(y, (p_l - p_j) \times x)$，$(p_i, p_j), (p_k, p_l)$ 时为 $\min(y, (p_j - p_i)\times x)+ \min(y, (p_l - p_k) \times x)$。

由 $p_k - p_i > p_j - p_i$ 与 $p_l - p_j > p_l - p_k$ 不难说明上述结论。

我们定义满足 $y \le (p_v - p_u) \times x$ 的一组匹配 $(p_u, p_v)$ 是 $y$-匹配，否则是 $x$-匹配。

可以发现，$x$-匹配不可能有重叠部分，而上面已经证明，每组 $y$-匹配形成的区间不可能相交。

考虑两组 $y$-匹配 $(p_i, p_l)$ 与 $(p_j, p_k)$，满足 $p_i < p_j < p_k < p_l$。注意到当前的贡献已经达到了理论上的最大值 $2y$，所以将匹配改为 $(p_i, p_j)$ 与 $(p_k, p_l)$ 一定不会更劣，而且在某组新匹配变为 $x$-匹配时会更优。

于是最优的匹配形式就变得很简单，一定是由若干段连续的 $x$-匹配组成，某些连续的 $x$-匹配外套有至多一个。

设计状态 $f_i$ 表示以 $i$ 结尾的最优答案，转移时需要考虑当前是 $x$-匹配的末尾，还是套在某些 $x$-匹配外的 $y$-匹配的末尾，然后枚举上一段连续 $x$-匹配末尾的位置。实际上是简单的，可以参照代码理解。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 5005;

int n, x, y, f[N];
char a[N], b[N];

void solve()
{
	cin >> n >> x >> y;
	cin >> (a + 1) >> (b + 1);
	int ans = 0, cnt = 0;
	vector<int> gg; gg.clear();
	gg.push_back(0);
	for(int i = 1; i <= n; i++)
		if(a[i] != b[i]) cnt++, gg.push_back(i);
	if(cnt & 1) {cout << "-1\n"; return;}
	if(cnt == 0) {cout << "0\n"; return;}
	if(x >= y)
	{
		if(cnt == 2) cout << (gg[1] == gg[2] - 1 ? min(x, 2 * y) : y) << '\n';
		else cout << cnt / 2 * y << '\n';
	}
	else
	{
		for(int i = 2; i <= cnt; i++) f[i] = 1e14;
		for(int i = 1; i <= cnt; i++)
		{
			int sl = 0;
			if(i > 1) f[i] = min(f[i], f[i - 2] + min(y, (gg[i] - gg[i - 1]) * x));
			for(int j = i - 2; j >= 1; j -= 2)
			{
				sl += (gg[j + 1] - gg[j]) * x;
				f[i] = min(f[i], f[j - 2] + y + sl);
			}
		}
		cout << f[cnt] << '\n';
	}
	return;
}

signed main()
{
	ios :: sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Iamzzr (赞：2)

思路：分类讨论 + 区间 DP。

前置知识：[1733D1 - Zero-One (Easy Version)](https://codeforces.live/problemset/problem/1733/D1)，不会的可以[看看](https://www.luogu.com.cn/blog/HIZZR/d1-zero-one-easy-version)。

--------------------------

先判无解状态，如果字符串中不同的个数为偶数，则显然无法完成要求。

然后预处理出**第 $i$ 个不同的位置在原字符串中的下标**，放进一个数组 $k$。

考虑区间 DP。令 $f_{l, r}$ 表示将数组 $k$ 中的区间 $[l, r]$ 全部反转的最少次数。我们可以写出以下有缺陷的动态转移方程：

$$
f_{l, r} = \min(f_{l, r - 2} + \min((k_r - k_{r - 1}) \cdot x, y), f_{l - 2, r} + \min((k_{l + 1} - k_{l}) \cdot x, y), f_{l + 1, r - 1} + y)
$$

提前预处理出长度为 $2$ 的块，即可转移，并且转移的时候块长可以增加 $2$，因为我们无法处理区间长度为奇数的答案（块长为奇数不合法）。

上面的方程非常好理解，但是为什么有错误呢？

可以看看这个数据：
```
1
4 2 1
1001
0110
```

这个时候，显然 $f_{2, 3}$ 的值是 $2$，$f_{1, 4}$ 的值按照方程是 $4$。但是我们发现，如果 $1$ 和 $3$ 反转，$2$ 和 $4$ 反转，可以做到代价为 $2$。原因是 $y$ 太小，而 $x$ 太大，所以一次 $x$ 可能还不如连续的 $y$ 操作。

所以要进行分类讨论。如果 $x \le y$，可以用区间 DP 解决。如果不是，则需要用文章开头提到的 CF1733D1 的方法解决，直接复制原来的代码就可以。

不要忘记开 `long long`。

AC 代码：

```cpp
#include <iostream>

using namespace std;

#define int long long
const int N = 5010;

int T;
int n, x, y; 
int f[N][N];
int k[N];

int cost(int l, int r) {
    return min((k[r] - k[l]) * x, y);
}

signed main() {
    cin >> T;
    while (T--) {
        cin >> n >> x >> y;
        string a, b; getline(cin, a);
        getline(cin, a), getline(cin, b);
        if (x >= y) {
            int cnt = 0;
            for (int i = 0; i < n; i++)
                if (a[i] != b[i]) cnt++;
            //cout << cnt << endl;
            if (cnt % 2) {
                cout << -1 << endl;
                continue;
            }
            if (cnt == 2) {
                bool flag = false;
                for (int i = 0; i < n - 1; i++)
                    if (a[i] != b[i] && a[i + 1] != b[i + 1]) {
                        flag = true;
                        break;
                    }
                if (flag) {
                    if (n == 2) cout << x << endl;
                    else cout << min(x, 2 * y) << endl;
                    continue;
                }
                cout << y << endl;
                continue;
            }
            cout << (cnt / 2) * y << endl;
            continue;
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) 
            if (a[i] != b[i]) k[++cnt] = i;
        if (cnt % 2) {
            cout << -1 << endl;
            continue;
        }
        if (cnt == 2) {
            bool flag = false;
            for (int i = 0; i < n - 1; i++)
                if (a[i] != b[i] && a[i + 1] != b[i + 1]) {
                    flag = true;
                    break;
                }
            if (flag) {
                if (n == 2) cout << x << endl;
                else cout << min(x, 2 * y) << endl;
                continue;
            }
            cout << min(y, (k[2] - k[1]) * x) << endl;
            continue;
        }
        for (int i = 1; i < cnt; i++)
            for (int j = i + 1; j <= cnt; j += 2) 
                if (k[i] + 1 != k[j]) f[i][j] = min((k[j] - k[i]) * x, y);
                else f[i][j] = min(x, y * 2);
        for (int len = 4; len <= cnt; len++) {
            for (int l = 1; l < cnt; l++) {
                int r = l + len - 1;
                if (r > cnt) break;
                f[l][r] = min(min(f[l + 2][r] + cost(l, l + 1), f[l][r - 2] + cost(r - 1, r)), f[l + 1][r - 1] + y/*cost(l, r)*/);
            }
        }
        cout << f[1][cnt] << endl;
    }
    return 0;
}

```

---

## 作者：ask_silently (赞：1)

## 思路分析

为了方便，我们可以先将二进制位不同的位置存起来。下文中的 $cnt$ 代指不同的位置个数，$a_i$ 代表第 $i$ 个不同位置的下标。

我们发现，每次取反的时候 $cnt$ 奇偶性是不变的，所以当 $cnt$ 为奇数时，一定是无解的。

接着我们可以先求解 $y \le x$ 的情况。

我们发现，若 $cnt$ 大于等于 $4$ 的话，我们一定可以将位置个数分为两份，前面的每个位置作为 $l$，后面的位置作为 $r$，这样就可以用最少的次数 $\frac{cnt}{2}$ 与最小的代价 $y$ 来达到最小的答案 $\frac{cnt}{2} \times y$。当 $cnt=2$ 的时候，此时的答案是固定的，若两个位置相邻即为 $x$，否则答案为 $y$。

而对于 $y > x$ 的情况，我们考虑 dp。

设 $dp_i$ 为前 $i$ 位匹配成功的最小代价，注意，当 $i$ 为奇数时，$dp_i$ 为空了一位的最小代价。

考虑如何进行转移。因为 $x < y$，所以我们需要尽可能多的使用 $x$。

- 若当前位使用了第一种操作，因为 $a_i$ 与 $a_{i-1}$ 之间的下标差一定最小，所以我们考虑从上一位进行转移。我们考虑将 $a_{i-1}$ 与 $a_{i-1}+1$ 位置取反，将 $a_{i-1}+1$ 与 $a_{i-1}+2$ 位置取反等等，所以一共会取反 $a_i-a_{i-1}$ 次，代价就是 $(a_i-a_{i-1}) \times x$，所以我们可以从 $dp_{i-2}$ 进行转移，这样不会影响到当前位与 $i-1$ 位的操作，转移就是：

$$dp_i=dp_{i-2}+(a_i-a_{i-1}) \times x$$

- 若当前位使用了第二种操作，则我们需要判断一下当前位的奇偶性。若当前位为奇数，因为当前一定有一位没有被选，所以和上一位操作次数相等，直接转移即可。若当前位为偶数，则一定增加了一次操作次数，所以加上 $y$ 就行了。转移为：

$$dp_i=\begin{cases}dp_{i-1}&i \mod 2 = 1\\dp_{i-1}+y&i \mod 2 = 0\end{cases}$$

所以转移就是：

$$dp_i=\begin{cases}\min(dp_{i-1},dp_{i-2}+(a_i-a_{i-1})\times x)&i \mod 2 = 1\\\min(dp_{i-1}+y,dp_{i-2}+(a_i-a_{i-1})\times x)&i \mod 2 = 0\end{cases}$$

## AcCode


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N=5010;

int n,x,y,cnt;
int a[N],dp[N];

string s1,s2;

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f),c=getchar();
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

void solution(){
	/*

	*/
}

void solve1(){
	if(cnt==2&&a[1]+1==a[2]){
		cout<<min(x,2*y)<<'\n';
		return;
	}
	if(x>=y){
		cout<<cnt/2*y<<"\n";
		return;
	}
}

signed main(){
	int T=read();
	while(T--){
		n=read(),x=read(),y=read();
		cin>>s1>>s2;
		cnt=0;
		for(int i=0;i<n;i++)
			if(s1[i]!=s2[i]) a[++cnt]=i;	
		if(cnt&1){
			cout<<-1<<"\n";
			continue;
		}
		if(x>=y) solve1();
		else{
			for(int i=2;i<=cnt;i++){
				if(i&1) dp[i]=min(dp[i-1],dp[i-2]+(a[i]-a[i-1])*x);
				else dp[i]=min(dp[i-1]+y,dp[i-2]+(a[i]-a[i-1])*x);
			}
			cout<<dp[cnt]<<'\n';
		}
	}
	return 0;
}

```

---

## 作者：Hisaishi_Kanade (赞：1)

首先考虑直接找到所有 $a_i\not = b_i$ 的 $i$ 的点集，按照升序排序得到 $p_1,\cdots,p_k$。

容易证明无论如何操作 $k$ 的奇偶性不变，则可以使得 $k\to0$ 的充要条件是 $k\equiv 0\ (\bmod\ 2)$。

然后考虑如何处理。因为 $y\le x$，所以能一次 $y$ 绝不使用 $x$。

那么如果 $k>2$ 则可以两两配对使得价值为 $\dfrac {ky} 2$。

当 $k=2$ 且这两个点相邻时，这时候挑一个已经匹配的操作两次 $y$，或者使用 $x$。

以上是 ez version 的解法，解法前提是 $y\le x$。当不满足时我们要考虑别的解法。设 $f(i)$ 表示全部解决了 $p_1\sim p_i$  这些不匹配的点的最小代价。

考虑直接转移，显然两种是 $x$ 或 $y$，直接写出方程：

+ $f(i)=\min\left(f(i-2)+x(p_i-p_{i-1}),f(i-1)+\dfrac y 2\right)$

解释一下就是，一种是将相邻两个一直用 $x$ 操作过去；或者用 $y$ 操作，因为 $y$ 交换两个不匹配的点，每个点的花费相当于 $\dfrac y 2$。

或许会怀疑这个 $\dfrac y 2$ 会不会出现取了奇数次的情况？

答案是不会。我们浅证明一下。我们模拟一下求得最优解的路径。

从 $i$ 如果是用 $x$ 转移，则认为从 $i-2$ 跳过来，用 $y$ 我们直接认为他从 $i-1$ 跳过来。显然 $\dfrac y 2$ 的个数等于从 $i-1$ 跳过来的点数（只考虑在最优解转移的这条路径上的点）。

第一种情况无论出现多少次，总共去掉的点数都是偶数，$k$ 也是偶数，则用 $y$ 转移的点就是偶数个。所以不会出现那种情况。

对于实现，全局乘二，输出时除回来即可。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
const int N=5005;
char u[N], v[N]; int t, i, n, x, y, tot;
int p[N]; long long f[N];
inline void solveez()//y<=x
{
	tot=0;
	rep(i, 1, n) if(u[i]!=v[i]) p[++tot]=i;
	if(tot&1) puts("-1");
	else if(tot==2 && p[1]==p[2]-1) printf("%d\n", min(x, y<<1));
	else printf("%lld\n", 1ll*(tot>>1)*y);
	return ;
}
inline void solvehd()
{
	tot=0;
	rep(i, 1, n) if(u[i]!=v[i]) p[++tot]=i;
	if(tot&1) puts("-1");
	else if(tot==2 && p[1]==p[2]-1) printf("%d\n", min(x, y<<1));
	else
	{
		f[1]=y;
		rep(i, 2, tot) f[i]=min(f[i-2]+1ll*x*(p[i]-p[i-1])*2, f[i-1]+y);
//		rep(i, 1, tot) printf("%d %d\n", i, f[i]);
		printf("%lld\n", f[tot]>>1);
	}
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d %d %s %s", &n, &x, &y, u+1, v+1);
		if(y<=x) solveez();
		else solvehd();
	}
	return 0;
}
```

---

## 作者：zxh_qwq (赞：0)

### CF1733D2 题解

#### 思路

首先注意到 $\sum n \le 5 \times 10^3$，时间复杂度应为 $O(n^2)$ 以下。

首先，将所有 $a_i \neq b_i$ 的数拿出来存到另一个数组 $c$ 中。

因为每次操作只进行两个数的操作，所以当 $c$ 中的元素个数（令元素个数为 $s$）为奇数时，必然不能完成，直接输出 `-1`。

先考虑 $y \le x$ 的情况。

我们分三类讨论：

1. $s=0$。直接输出 `0`。

2. $s=2$。答案为 $\begin{cases}\min(x,2y) & c_0+1=c_1\\ \min[x \cdot (c_1-c_0),y] & c_0+1 \neq c_1 \end{cases}$。只需要考虑直接交换还是中转。

3. $s>2$。答案为 $\dfrac{sy}{2}$。因为显然可以有一种匹配使得交换的元素两两不相邻。

接下来，对于 $y > x$ 的情况，考虑区间 DP。

令 $f_{i,j}$ 为将 $c$ 数组中区间 $i$ 到 $j$ 消除的最小花费代价。

显然初始条件为 $f_{i,i}= + \infty$。

所以 $f_{i,i+1}=\begin{cases}\min(x,2y) & c_i+1=c_{i+1}\\ \min[x \cdot (c_{i+1}-c_i),y] & c_i+1 \neq c_{i+1} \end{cases}$。

上面的式子不难证明，就是直接交换和用一个点当中转交换两种情况。

那么我们就可以推导出 $f_{i,j}$ 的式子。

当取反 $c_i,c_j$ 时，$f_{i,j}=f_{i+1,j-1}+y$。

当取反 $c_i,c_{i+1}$ 时：

$$f_{i,j}=f_{i+2,j}+\begin{cases}\min(x,2y) & c_i+1=c_{i+1}\\ \min[x \cdot (c_{i+1}-c_i),y] & c_i+1 \neq c_{i+1} \end{cases}$$

当取反 $c_{j-1},c_j$ 时：

$$f_{i,j}=f_{i,j-2} + \begin{cases}\min(x,2y) & c_{j-1}+1=c_j\\ \min[x \cdot (c_j-c_{j-1}),y] & c_{j-1}+1 \neq c_j \end{cases}$$

所以我们将三种情况取 $\min$ 即可。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int c[5020],f[5020][5020];
main(){
	int t;
	cin>>t;
	while(t--){
		string a,b;
		int n,x,y,cnt=0;
		cin>>n>>x>>y>>a>>b;
		a=" "+a;
		b=" "+b;
		for(int i=1;i<=n;i++){
		    if(a[i]!=b[i]){
		    	c[++cnt]=i;
			}
		}
		if(cnt%2==1){
			cout<<-1<<endl; 
			continue;
		}
		if(y<=x){
			if(cnt==0)cout<<0;
			else if(cnt==2){
				if(c[1]+1==c[2]){
					cout<<min(x,2*y);
				}
				else cout<<y;
			}
			else cout<<cnt/2*y;
		}//y<=x 分类讨论 
		else{
			for(int i=1;i<=cnt;i++){
				for(int j=i;j<=cnt;j++){
					f[i][j]=1e17;
				}
			}//记得多测清空 
			for(int i=1;i<cnt;i++){
				if(c[i]+1==c[i+1]){
					f[i][i+1]=min(x,2*y);
				}
				else{
					f[i][i+1]=min(x*(c[i+1]-c[i]),y);
				}
			}//初始条件 
			for(int len=3;len<=cnt;len++){
				for(int i=1;i+len-1<=cnt;i++){
				    int j=i+len-1;
				    int k=1e18;
				    k=min(k,f[i+1][j-1]+y);
					//从 f[i+1][j-1] 转移
					 
				    if(c[i]+1==c[i+1])k=min(k,f[i+2][j]+min(x,2*y));
				    else k=min(k,f[i+2][j]+min(x*(c[i+1]-c[i]),y));
				    //从 f[i+2][j] 转移
				    
				    if(c[j-1]+1==c[j])k=min(k,f[i][j-2]+min(x,2*y));
				    else k=min(k,f[i][j-2]+min(x*(c[j]-c[j-1]),y));
				    //从 f[i][j-2] 转移
				    f[i][j]=k; 
				}
			}//转移
			cout<<f[1][cnt];
		}//y>x DP 
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1733D2)

# 思路：
分多种情况考虑，预处理出不相同的位置数量，记为 ```cnt```。

1. ```cnt``` 为 $0$，输出 $0$。

2. ```cnt``` 为奇数，必然不可能，输出 $-1$。

3. ```cnt``` 为偶数，当 $y$ 比 $x$ 小时，除了仅有的两个位置相邻的情况，可以贪心的知道最小的代价一定是 $cnt\div 2 \times y$。

4. ```cnt``` 为偶数，当 $y$ 比 $x$ 大时，首先对于两个位置需要交换的情况进行考虑：如果两个位置相邻，可以通过一次 $x$ 操作或者两次 $y$ 操作取得；如果两个位置不相邻，可以通过一次 $y$ 操作或者 $k$ 次 $y$ 操作取得（$k$ 为两者距离差）。

对于 $cnt \gt 2$ 的偶数情况，从两边往里贪心的记忆化搜索，一边拿两个，或者一边拿一个，因为 $x$ 小于 $y$，所以最优的解法一定从中取得。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+100;
const int INF=0x3f3f3f3f3f3f3f3f;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
    return;
}
int t,n,x,y;
string a,b;
vector<int>res;
int dp[N][N];
int check(int a,int b){
	int k=b-a;
	if(k==1){
        return min(x,2*y);
    }else{
        return min(k*x,y);
    }
}
int dfs(int l,int r){
	if(l>r){
        return 0;
    }
	if(dp[l][r]!=INF){
        return dp[l][r];
    }
	dp[l][r]=INF;
	dp[l][r]=min(dp[l][r],dfs(l+2,r)+check(res[l],res[l+1]));
	dp[l][r]=min(dp[l][r],dfs(l,r-2)+check(res[r-1],res[r]));
	dp[l][r]=min(dp[l][r],dfs(l+1,r-1)+check(res[l],res[r]));
	return dp[l][r];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
        cin>>n>>x>>y>>a>>b;
        a="#"+a;
        b="#"+b;
        res.clear();
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                dp[i][j]=INF;
            }
        }
        for(int i=1;i<=n;i++){
            if(a[i]==b[i]){
                continue;
            }
            res.push_back(i);
        }
        if(res.size()==0){
            cout<<0<<'\n';
        }else if(res.size()&1){
            cout<<-1<<'\n';
        }else if(res.size()==2){
            cout<<check(res[0],res[1])<<'\n';
        }else if(y>x){
            cout<<dfs(0,res.size()-1)<<'\n';
        }else{
            cout<<res.size()/2*y<<'\n';
        }
    }
    return 0;
}
```
完结撒花~

---

## 作者：xiazha (赞：0)

好题！

让我们思考以下 ```easy ver``` 的作用，然后想到了分讨。

首先将所有 $s_i\ne t_i$ 的下标 $i$ 组成长为 $c$ 的序列 $a$。

特别的，若 $c$ 为奇数，输出 ```-1```。

- $y\le x$

贪心的，当 $c\le 2$ 且 $a_1+1=a_2$ 时，我们想不用相邻交换就必须用另一个点作为中转点，将中转点翻两次，注意到 $n\ge 5$，所以我们一定能找到一个不相邻的中转点，答案为 $\min(x,2y)$。否则一定可以将所有下标两两配对且不相邻，答案为 $c/2\times y$。

- $y > x$

考虑 dp。

设 $dp_i$ 为将前 $i$ 个下标都修改为与 $t$ 相等最小花费。

那么若选相邻的，则将 $a_i$ 与 $a_{i-1}$ 一组，需要交换 $a_i-a_{i-1}$ 次，方程为 $dp_i=dp_{i-2}+(a_i-a_{i-1})\times x$。

若不选相邻的，则我们将 $y$ 的贡献均匀拆成两个 $y/2$，$dp_i=dp_{i-1}+y/2$。

将上述两个取最小值即可。

还有两个提示：

第一，将 dp 过程中的值全部乘 $2$，最终再除 $2$ 防止小数出现。

第二，你可能会不理解 $y/2$ 会不会没有与他匹配的另一半，根据转移方程，你会发现选择 $y/2$ 一定是偶数次，因为另一种操作每次都会加上两个数，而 $c$ 也是偶数，故方程是正确的。

时间复杂度 $O(n)。$

---

## 作者：linjinkun (赞：0)

提供一个 $O(n)$ 的 ```线性dp```。~~（虽然已经有一堆人提供了）~~

只有 [https://www.luogu.com.cn/article/sprmkv26](https://www.luogu.com.cn/article/sprmkv26) 这篇题解和我思路相同，但他的讲的并不是很清楚，我来清楚地讲一遍。

首先这题一眼动态规划，还是采用简单版的套路，设 $s_i$ 表示第 $i$ 个 $a_i \not = b_i$ 的位置 $i$，那么状态转移就是 $f_i = \min(f_{i-2}+x \times (s_i-s_{i-1}),f_{i-1}+(i \bmod 2 \not = 0) \times y)$，来解释一下为什么是这样的，因为对于第 $i$ 个 $a_i \not = b_i$ 的值，他要不就和 $i-1$ 一起取反，要不就继承上一个，具体的说，当 $i$ 为偶数时，从 $i-1$ 一直操作到 $i$ 的代价是 $x \times (s_i-s_{i-1})$，还可以直接将 $i$ 和 $i-1$ 取反，代价为 $f_{i-1}$，这个时候你可能就要问了，为什么不是 $f_{i-1}+y$ 呢？因为这个时候 $i-1$ 是奇数，奇数的情况是无解的，但为了方便转移，我们将他继承了它的上一个。当 $i$ 为奇数的情况，本身是无解的，所以跟它的上一个差不多，就是多了一个 $+y$，$f_i = \min(f_{i-2}+x \times (s_i-s_{i-1}),f_{i-1}+y)$，其实就是把 $f_{i-1}$ 直接传到了 $f_{i+1}$，多了两个数，所以多了一个操作，只是为了方便转移，通过 $f_i$ 这个无解的情况传了过去。

**要开 ```long long```。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int f[5005];
int s[5005];
signed main()
{
	int t;
	scanf("%lld",&t);
	while(t--)
	{
		string a,b;
		int n,x,y;
		scanf("%lld %lld %lld",&n,&x,&y);
		cin >> a >> b;
		if(a == b)
		{
			printf("0\n");
			continue;
		}
		int k = 0;
		for(int i = 0;i<n;i++)
		{
			if(a[i]!=b[i])
			{
				s[++k] = i;
			}
		}
		if(k%2 == 1)
		{
			printf("-1\n");
			continue;
		}
		if(k == 2&&s[1]+1 == s[2])
		{
			printf("%lld\n",min(2*y,x));
			continue;
		}
		f[1] = y;
		for(int i = 2;i<=k;i++)
		{
			f[i] = min(f[i-2]+x*(s[i]-s[i-1]),f[i-1]+(i&1)*y);
		}
		printf("%lld\n",f[k]);
	}
	return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

题意我就不讲了哈

# 思路

先将不同的 $a_i,b_i$ 取出来，得到一个新数组 $p$ 大小记为 $cnt$，因为每次操作改变两个数，显然只有 $cnt$ 为偶数时有解，然后分类讨论：如果 $x>y$，考虑贪心做法，否则用一个简单的区间 DP，$O(n^2)$（线性的我不会，本人蒟蒻）。

- $x>y$，显然我们要尽可能将不相邻的两个数取反，所以将 $p$ 分成两半，$a_i$ 和 $a_{i+m \div 2}$ 一组，所以答案就是 $m \div 2 \cdot y$。我们还要考虑如果 $p$ 中只有两个数，并且它们是相邻的，那样要么直接相邻取反，要么借助第三者跳转，答案就变成 $\min(2y,x)$。补充：跳转相当于本来要变 $a,b$ 的，改为找一个与它们不相邻的 $c$，先变 $a,c$，再变 $a,b$，这样 $c$ 没变，相当于一个跳板。

- $x \le y$，我们设 $dp_{l,r}$ 表示区间 $[l,r]$ 变完后的最低代价，注意我们是在 $p$ 数组上跑的，不是 $a$。我们先预处理出长度为 $2$ 的区间代价。对于区间 $[l,r]$ 代价的计算，如果两个数相邻，代价就是 $\min(x,y*2)$，否则就是 $\min(x(p_r-p_l),y)$。接下来我们要思考 $dp_{l,r}$ 从哪个状态转移而来，因为奇数区间无解，所以每次从少两个数的状态过来，于是我们就有 $dp_{l,r}=\min(dp_{l+2,r}+ 代价 (l,l+1),dp_{l,r-2}+ 代价 (r-1,r),dp_{l+1,r-1}+ 代价 (l,r))$。

在 DP 时有一个优化，我们不枚举奇数区间，因为它无法对答案有贡献。

---


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5001,INF=0x7fffffffffff;
string a,b;
int t,n,x,y,p[N],cnt,dp[N][N];
int calc(int l,int r)//代价计算
{
    return p[l]+1==p[r]?min(x,y*2):min((p[r]-p[l])*x,y);
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
    while(t--)
    {
        cnt=0;
        cin>>n>>x>>y>>a>>b;
        for(int i=0;i<n;i++)
        {
            if(a[i]!=b[i])
            {
                p[++cnt]=i+1;
                dp[cnt][cnt]=INF;
            }
        }
        if(cnt&1)
        {
            cout<<"-1\n";
            continue;
        }
        if(x>y)
        {
            if(cnt==2&&p[1]+1==p[2])
            {
                cout<<min(2*y,x);
            }else
            {
                cout<<cnt/2*y;
            }
            cout<<"\n";
            continue;
        }
        for(int i=1;i<cnt;i++)
        {
            dp[i][i+1]=calc(i,i+1);
        }
        for(int len=4;len<=cnt;len+=2)
        {
            for(int l=1,r=len;r<=cnt;l++,r++)
            {
                dp[l][r]=min({dp[l+2][r]+calc(l,l+1),dp[l][r-2]+calc(r-1,r),dp[l+1][r-1]+y});
            }
        }
        cout<<dp[1][cnt]<<"\n";
    }
	return 0;
}
```

如果我的题解有用，请给我关注。

---

## 作者：AC_love (赞：0)

首先我们发现：每次我们都会修改两个位置。

修改两个位置使无法改变 $a, b$ 不同的数的个数的奇偶性的，因此如果 $a, b$ 不同的数个数为奇数，那一定就寄了，输出 $-1$。

然后考虑如何修改。

不难发现：修改的代价为 $x$ 的条件一定是比修改代价为 $y$ 的条件更苛刻一些的。

因此，当 $y \le x$ 时，显然我们尽量多选 $y$ 会更好一些。

假设有 $k$ 个不同的位置，当 $k \ge 4$ 或 $k = 2$ 且两个位置不相邻时，答案为 $\dfrac{ky}{2}$。

当 $k = 2$ 且两个位置相邻时，答案为 $\min(x, 2y)$。

如果 $y > x$ 应该怎么办呢？

我们考虑 DP 来解决这个问题。

我们考虑记录一下所有 $a, b$ 不同的数出现的位置，存到一个数组 $p$ 里。

对于某个位置，我们有两种方案。

1. 直接修改这个位置。
2. 从上一个位置一路修改过来。

如果直接修改这个位置，显然代价为 $\dfrac{y}{2}$。

如果从上一个位置一路修改过来，代价为 $x(p_i - p_{i - 1})$。

取一个最小值即可。

设 $f(i)$ 表示将前 $i$ 个不同的数修改的最小代价。

显然有转移：

$$f(i) = \min(f(i - 1) + \dfrac{y}{2}, f(i - 2) + x(p_i - p_{i - 1}))$$

答案为 $f(k)$。

---

## 作者：Xiphi (赞：0)

考虑线性 dp。设 $f_{i}$ 表示修复前 $i$ 个不同点所需要的最小代价。显然，最终答案为 $f_{\text{不同点的个数}}$。

首先，有一个贪心策略便是每次修复相邻两个不同点的策略一定不劣。感性理解一下，修复两个跨越其他点的点，中间用“相邻交换”策略时，就必然不优。

其实，转移方程可以是 $f_i=\min(f_{i-2}+x\times (now-last),f_{i-1}+\frac{y}{2})$。其中 $last$ 表示上一个需要修复的点的下标，$now$ 表示现在所要处理的需要修复的点的下标。

接下来，我来解释一下这一坨东西：

首先，为什么是 $f_{i-2}$ 而不是 $f_{i-1}$？因为在修复 $i$ 点时，已经把第 $i-1$ 个该修复的点修复掉了，所以不需要考虑第 $i-1$ 个该修复的点。

然后就是 $\frac{y}{2}$ 的问题了。因为我们只需要算第 $i$ 个点应有的贡献所以就是 $\frac{y}{2}$。

细节方面见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n,x,y;
int f[5005];
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    cin>>T;
    while(T--){
        cin>>n>>x>>y;
        string a,b;
        cin>>a>>b;
        a=" "+a,
        b=" "+b;
        vector<int> pos(1);
        int last=0,flag=0,ans=0;
        for(int i=1;i<=n;++i){
            if(a[i]!=b[i]) pos.push_back(i);
        }
        if(pos.size()==3&&pos[1]+1==pos[2]){
		cout<<(min(y << 1, x))<<'\n';
        continue;
        }
        f[1]=y;
        for(int i=2;i<pos.size();++i){
            f[i]=min(f[i-2]+2*x*(pos[i]-pos[i-1]),f[i-1]+y);
        }
        cout<<(pos.size()%2==0?-1:f[pos.size()-1]+1>>1)<<'\n';
    }
	return 0;
}
```

---

