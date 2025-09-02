# Binary String

## 题目描述

你有一个由 $1$ 和 $0$ 构成的字符串 $s$。

你需要先从 $s$ 的开头移除若干字符，然后从 $s$ 的结尾移除若干字符。（当然，你可以不移除任何字符，也可以将整个 $s$ 移除掉）

这样做的代价是从 $s$ 中移除的 $1$ 的个数和 $s$ 中剩余的 $0$ 的个数的最大值。

求代价的最小值。

## 说明/提示

样例解释：

`101110110` -> `(10) 111011 (0)`

`1001001001001` -> `(100100) 1001 (001)`

`0000111111` -> `(0000) 111111 ()`

`00000` -> `(00000)()`

`1111` -> `()1111()`

## 样例 #1

### 输入

```
5
101110110
1001001001001
0000111111
00000
1111```

### 输出

```
1
3
0
0
0```

# 题解

## 作者：断清秋 (赞：20)

[题目传送门](https://www.luogu.com.cn/problem/CF1680C)

官方题解好像写了二分，提供一个线性做法。

题意是给定一个 $01$ 串，从开头和结尾各删去一些数（可以不删），求 删除的 $1$ 个数 与 剩下的 $0$ 个数 的最大值。

首先，最优方案下一定有 删 $1$ 数 $=$ 剩 $0$ 数（此时继续删除不会使答案更优），而删除的数的个数等于 删 $1$ 数 $+$ 删 $0$ 数，因此删除的数的个数就是 删 $0$ 数 $+$ 剩 $0$ 数，即原串中 $0$ 的个数。

然后预处理出这个串的前缀有多少个 $0$，后缀有多少个 $0$，之后暴力枚举开头删几个数即可做到 $O(1)$ 计算开头和结尾的贡献，复杂度 $O(n)$。

---

## 作者：Zwb0106 (赞：7)

####  [原题链接](https://codeforces.com/contest/1680/problem/C)

------------
给一个简单易懂的 $O(n\log n)$ 做法。

------------
## 题意
有 $T$ 组数据，对于每组数据，给定一个 $01$ 串，可以删除开头连续几个字符和末尾连续几个字符（可以不删除或全删除），删除方案的代价为删除的 $1$ 的数目和剩余的 $0$ 的数目的最大值，求最小代价。

------------
## 思路
先预处理出两个前缀和，分别维护 $01$ 串中 $0$ 和 $1$ 的数目。

删除两段相当于保留一个子区间 $[l,r]$，那么对于两个段点 $l$ 和 $r$，我们 $O(n)$ 枚举 $l$。

略作思考，发现 $l$ 固定的时候，最右侧删除的字符越多（$r$ 越小），删除的 $1$ 越多，剩余的 $0$ 越少，这两个值的差（前项减去后项）就越大，而我们希望它们的较大者更小，就等价于希望两个值的差的绝对值更小，那么这个代价是关于 $r$ 的单峰函数，于是 $r$ 的移动带来的影响满足单调性，二分即可。

时间复杂度 $O(n\log n)$。

---

## 作者：西湖水妖 (赞：6)

### 题意简述

+ 给定一个只由 01 组成的字符串，你需要从它的开头删除一些连续的字符，再从结尾删除一些连续的字符。可以不删除，也可以全部删除。

+ 定义删除的代价为下列两个值的**最大值**：

  1. 字符串里剩余的 0 的数量。
  2. 删除的 1 的数量。
  
+ 你需要使这个代价**最小**。

+ 有 $t$ 组数据，$t\in\mathbf{Z}$ 且 $1\le t\le10^4$。字符串 $s$ 的长度记为 $|s|$，$1\le |s|,\sum|s|\le2\times10^5$。

### 题目分析

看见最大值最小，我们就应该想到二分，这是二分的标志。发现每个代价是否可行是单调的，所以直接二分这个代价，答案 $\in[0,|s|]$。

设当前判断到的代价为 $m$。然后每次我们判断的时候，如果先保证删除的 1 的数量 $\le m$，要从两边枚举删除字符的数量，$\operatorname O(|s|^2)$ 还是会超时。考虑先保证剩余的 0 的数量 $\le m$，然后再计算删除的 1 的数量，如果 $\le m$ 当前这个代价就可行，如果一个都不满足当前这个代价不可行。我们可以记录前缀的 1 的数量来优化这个过程。

设当前的保留的区间的下标为 $[l,r]$，发现 $l$ 随着 $r$ 的增加而增加，所以这个过程可以尺取法优化。每次右移 $r$ 的时候，如果新的 $r$ 所在的字符是 0，增加当前的 0 的数量。如果 0 的数量 $>m$ 了，不断右移 $l$ 直到区间里 0 的数量 $\le m$ 就可以了。总时间复杂度 $\operatorname O(t|s|\log|s|)$，可以通过本题。

注意如果字符串全都是 0 需要特判，因为没有一个区间的 0 的数量为 0，所以会输出 1，但是答案应该为 0。

#### 主函数部分

```cpp
// a 为字符串，s 为前缀的 1 的数量。
if(! s.at(a.size())) //特判全都是 0 的情况，没有一个 1 就是全都是 0。
{
    cout << "0\n";
    continue;
}
l = 0u;
r = a.size(); //设置边界。
while(l != r) //二分。
{
    mid = l + r >> 1u;
    if(check(mid))
        r = mid;
    else
        l = mid + 1u;
}
cout << l << "\n";
```

#### 判断可行部分

```cpp
//mx 是代价。
bool check(const unsigned &mx)
{
    for(auto sum(0u), l(0u), r(0u); r != a.size(); ++ r) //sum 是当前区间 0 的数量。
    {
        sum += a.at(r) == '0'; //增加 0 的数量。
        while(sum > mx && l <= r)
            sum -= a.at(l ++) == '0'; //不断右移 l。
        if(l > r) //没有满足条件的区间直接跳过。
            continue;
        if(s.at(l) /*左边 1 数量*/ + s.at(a.size()) - s.at(r + 1u) /*右边 1 数量*/ <= mx)
            return true;
    }
    return false;
}
```


---

## 作者：灵茶山艾府 (赞：5)

### 方法一：二分答案+滑动窗口

代价越大，越容易做到（存在移除方案）。

二分最大代价 $\textit{mx}$，用滑动窗口来维护，只要窗口尽量大（窗口内 $0$ 的个数不超过 $\textit{mx}$），那么窗口外的 $1$ 的个数就尽量小。

如果某个时刻窗口外的 $1$ 的个数不超过 $\textit{mx}$，那么答案至多为 $\textit{mx}$。根据这个来写 $\text{check}$ 函数。

```go
package main
import("bufio";."fmt";"os";"sort";"strings")

func main() {
	in := bufio.NewReader(os.Stdin)
	var T int
	var s string
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &s)
		tot1 := strings.Count(s, "1")
		Println(sort.Search(len(s), func(mx int) bool { // 二分最大代价 mx
			in0 := 0     // 窗口内的 0 的个数
			out1 := tot1 // 窗口外的 1 的个数
			left := 0
			for _, b := range s {
				v := int(b & 1)
				in0 += v ^ 1
				out1 -= v
				for in0 > mx { // 窗口内的 0 太多了
					v = int(s[left] & 1)
					in0 -= v ^ 1
					out1 += v
					left++
				}
				if out1 <= mx { // 答案至多为 mx
					return true
				}
			}
			return false // 答案至少为 mx+1
		}))
	}
}
```

时间复杂度：$\mathcal{O}(n\log n)$，其中 $n$ 是字符串 $s$ 的长度。

### 方法二：利用性质

注意到，如果窗口内的 $0$ 的个数低于窗口外的 $1$ 的个数，那么扩大窗口更好：

- 如果把 $1$ 移入窗口，那么窗口外 $1$ 的个数变小，代价变小。
- 如果把 $0$ 移入窗口，虽然代价不变，但如果后面把 $1$ 移入窗口，也会让代价变小。相当于更有机会让代价变小。

同样，如果窗口内的 $0$ 的个数超过窗口外的 $1$ 的个数，那么缩小窗口更好：

- 如果把 $0$ 移出窗口，那么窗口内 $0$ 的个数变小，代价变小。
- 如果把 $1$ 移出窗口，虽然代价不变，但如果后面把 $0$ 移出窗口，也会让代价变小。

所以无需二分，直接滑窗即可。

```go
package main
import("bufio";. "fmt";"os";"strings")
func min(a, b int) int { if b < a { return b }; return a }

func main() {
	in := bufio.NewReader(os.Stdin)
	var T int
	var s string
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &s)
		ans := len(s)
		in0 := 0
		out1 := strings.Count(s, "1")
		left := 0
		for _, b := range s {
			v := int(b & 1)
			in0 += v ^ 1
			out1 -= v
			for in0 > out1 { // 0 多就缩小窗口
				v = int(s[left] & 1)
				in0 -= v ^ 1
				out1 += v
				left++
			}
			ans = min(ans, out1) // in0 <= out1
		}
		Println(ans)
	}
}
```

时间复杂度：$\mathcal{O}(n)$，其中 $n$ 是字符串 $s$ 的长度。


---

## 作者：BerlandsFD (赞：3)

~~不用二分~~
#### 题目
[题目传送门](https://www.luogu.com.cn/problem/CF1680C)

#### 思路
我们，知道如果删掉 $1$ 数等于剩下的 $0$ 数代价一定最优。那如何让两数相等呢？

我们定义有 $cnt0$ 个 $0$。

我们知道剩下的 $0$ 的数，最大是 $cnt0$。所以我们只要取 $cnt0$ 个数删掉 $1$ 的个数一定等于剩下的 $0$ 的数。再证明一下这个。

设删掉 $x$ 个 $1$，剩下 $y$ 个 $0$。

第一种情况

如果删掉的数都是 $1$ 那么 $x = y$。

第二种情况

如果删掉的数里面有 $0$。再设删掉的数中有 $z$ 个 $0$。则 删掉 $cnt0 - z$ 个 $1$。剩下 $cnt0 - z$ 个 $0$。删掉的 $1$ 和剩下的 $0$ 仍然相等。

所以我们枚举前面删多少，就知道后面删多少，再算一下代价就可以了。提示，要用前缀和。

#### code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 100;
int z[N], o[N];

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		string s;
		cin >> s;
		int l = s.size();
		for(int i = 0; i < l; i++)
		{
        //前缀和
			if (s[i] == '0') z[i + 1] = z[i] + 1;
			else z[i + 1] = z[i];
			if (s[i] == '1') o[i + 1] = o[i] + 1;
			else o[i + 1] = o[i];
		}
		int cnt0 = z[l];
		int ans = 2000000000; //设为极大值
		for (int i = 0; i <= cnt0; i++)
		{
			int tmp = l - (cnt0 - i);
			int maxn = o[i] + o[l] - o[tmp];
			ans = min(ans, maxn);
		}
		if (ans == 2000000000) cout << "0" << endl;
		else cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Henry_C (赞：2)

# 题意
$\qquad$给定长度不超过 $2 \times 10^5$ 的由 $ 0,1$ 构成的字符串，可以从开头和结尾删除任意长度的连续字符串，删除的代价为删除 $1$ 的数量和留下 $0$ 的数量的最大值，求删除的最小代价。
# 思路
$\qquad$思路 $1$：用双指针法维护滑动窗，当窗口内当 $n_{1 \ \rm{deleted}}=n_{0 \ \rm{remained}}$ 时，可能取得最小代价。因此可以用双指针法维护滑动窗，记录窗内 $0$ 的数量 $n_{0 \ \rm{remained}}$ 和窗外 $1$ 的数量 $n_{1 \ \rm{deleted}}$，遍历窗口的起点 $i$，当 $n_{1 \ \rm{deleted}}<n_{0 \ \rm{remained}}$，滑动窗口右端点 $j$，直到 $n_{1 \ \rm{deleted}} \ge n_{0 \ \rm{remained}}$ 停止，更新一次答案。

$\qquad$思路 $2$：在思路 $1$ 的基础上继续延伸。
$\because n_{1 \ \rm{deleted}}=n_{0 \ \rm{remained}}$

$\therefore n_{0 \ \rm{remained}}+n_{1 \ \rm{remained}}=n_{1 \ \rm{deleted}}+n_{1 \ \rm{remained}}=n_{1 \ \rm{total}}$

因此维护一个固定长度为 $n_{1 \ \rm{total}}$ 的滑块，统计滑块内留下的 $0$、滑块外删除的 $1$，即可更新答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin>>s;
    int cnt1 = 0;
    int n = s.size(); //字符总数
    for(int i = 0; i < n; i++) {//统计0,1的数量
        if (s[i] == '1') cnt1++;
    }

    //
    int out1 = cnt1, inner0 = 0;//滑动窗
    //先建立滑动尺
    for(int i=0; i<cnt1; i++){
        if (s[i] == '0') inner0++;
        else out1--;
    }
    int ans = max(out1, inner0);
    for(int i=cnt1; i<n; i++){//滑动窗前沿
        if (s[i] == '0') inner0++;
        else out1--;

        if (s[i-cnt1] == '0') inner0--;
        else out1++;

        ans = min(ans, max(out1, inner0));
    }

    cout<<ans<<endl;
}


int main() {
//    freopen("1.in","r",stdin);
    int t;
    cin>>t;
    while(t--) {
        solve();
    }
    return 0;
}
```


---

## 作者：Luciylove (赞：2)

赛时看错题选手报道, 提供一个无脑解法。

我们记录 $pre_{i, op}$ 表示 $[1, i] $ 出现的 $op$ 个数， $suf_{i, op}$ 表示 $[i, n]$ 出现的 $op$ 个数。

特定的， 我令 $s_0 = pre_{n, 0}$

我们发现，对于前缀 $a$ , 后缀 $b$ 所表示的答案是 ：

$$\max\{{s_0 - pre_{a, 0} - suf_{b,0}, pre_{a,1} + suf_{b, 1}}\}$$

- 较为暴力的 method :

考虑对于左右两边加上 $pre_{a, 0} + suf_{b,0}$ 得到 ：

$$\max\{{s_0, pre_{a,1} + suf_{b, 1} +pre_{a, 0} + suf_{b,0}}\} - pre_{a, 0} - suf_{b,0}$$

我们分类讨论.

- 1.$s_0 \leq pre_{a,1} + suf_{b, 1} +pre_{a, 0} + suf_{b,0}$ 的情况

$pre_{a,0} + pre_{a, 1}$ 是 已知的， 考虑求 $suf_{b, 0} + suf_{b, 1} \geq s_0 - pre_{a,0} - pre_{a, 1}$ 的最小 $suf_{b,1}$ 。

- 1.$s_0 > pre_{a,1} + suf_{b, 1} +pre_{a, 0} + suf_{b,0}$ 的情况

$pre_{a,0} + pre_{a, 1}$ 是 已知的， 考虑求 $suf_{b, 0} + suf_{b, 1} < s_0 - pre_{a,0} - pre_{a, 1}$ 的最大 $suf_{b,0}$ 。

比较暴力的方法是， 考虑倒序枚举去确定 $a$ 的位置， 直接开线段树去分类讨论维护这个题。

- 较为优美的 method :

但是我们发现， 其实这个题没有这么麻烦， 拎出来这个式子 :

$$\max\{{s_0 - pre_{a, 0} - suf_{b,0}, pre_{a,1} + suf_{b, 1}}\}$$

为了方便地比较大小， 左右作移项得 ：

$$\max\{{s_0, pre_{a,1} + suf_{b, 1} + pre_{a, 0} + suf_{b,0}}\}$$

发现可以继续合并 ：

$$\max\{s_0, a + b\}$$

那么就是看左右哪个大的大小取值。

考虑到 $pre_{0/1},suf_{0/1}$ 单调不降。

考虑枚举 $a$。

如果左边大那么就是取 $s_0 - pre_{a, 0} - suf_{b,0}$ ， 那么肯定 $b$ 越大越好， 因为 $a + b \leq s_0$ 考虑令 $b = s_0 - a$ .

如果左边大那么就是取 $pre_{a,1} + suf_{b, 1}$ ， 那么肯定 $b$ 越小越好， 因为 $a + b > s_0$ 考虑令 $b = s_0 - a + 1$. 

所以我们有 $O(n)$ 做完这个题。

---

## 作者：赖今羿 (赞：1)

看到题解区都写的是线性或者二分做法……我就不写了，这里介绍一种三分做法。

就是假设我们是从不删任何数字到删完所有数字，那么每次多删一个数字，删除 $1$ 的数量只会变多、留下 $0$ 的数量只会变少。

而这个代价是它们两个取 $\max$，那么它肯定会首先变小，后来变大，所以这是单峰函数。

所以就可以三分代价了，设 $x$ 轴是删除的数量，$y$ 轴是最小代价，每次直接算，还是 $\mathcal O(n\log n)$ 的。

具体就是先预处理前后缀 $1$ 的个数，每次枚举前缀删了多少个，那么就可以 $\mathcal O(1)$ 算出删去 $1$ 的数量和留下 $0$ 的数量，最终取个 $\min$ 就好了。

当然当这个串全是 $1$ 或者全是 $0$ 时，这个峰在边界，这需要注意一下。

---

## 作者：lsj2009 (赞：1)

##  题目大意
给定一个字符串 $s$，你可以从该字符串开头删除若干个字符（可能为 $0$），再从结尾删除若干个字符（可能为 $0$），两次删除的代价总和为两次删除的字符串中 $1$ 的总个数和完成两次删除后的字符串剩余的 $0$ 的个数中的较大值。

请使删除代价最小化。
## 思路
很有意思的一题，感觉思维难度已经完全超过了普通 2C 甚至达到 2D 的难度。

最简单的思路，我们枚举开头删除几个字符，再枚举结尾删除几个字符，然后计算代价，最后取代价最小值。这样进行计算，枚举时间复杂度 $\Theta(n^2)$，计算代价复杂度 $\Theta(n)$，总时间复杂度 $O(n^3)$，哪怕是 $n\le1000$ 的极小数据也难以通过。

考虑前缀和优化。

我们约定 $pre_{0,i}$ 和 $pre_{1,i}$ 分别为 $s_{1\sim i}$（字符串下标从 $1$ 开始）中 $0$ 和 $1$ 的个数。$nxt_{0,i}$ 和 $nxt_{1,i}$ 分别为 $s_{n-i+1\sim n}$ 中 $0$ 和 $1$ 的个数。

则删除字符串前 $a$ 个字符，然后再删除结尾 $b$ 个字符的代价为 $\max\{pre_{1,a}+nxt_{1,b},pre_{0,n}-pre_{0,a}-nxt_{0,b}\}$。这样，计算代价复杂度降至 $\Theta(1)$，预处理前缀和复杂度为 $\Theta(n)$，总时间复杂度为 $\Theta(n^2)$，还需要优化。

为什么复杂度会是 $n^2$ 呢？是的，主要是因为计算代价中 $\max$ 的原因。对于代价取两次删除的字符串中 $1$ 的总个数即 $pre_{1,a}+nxt_{1,b}> pre_{0,n}-pre_{0,a}-nxt_{0,b}$ 的情况，我们可以将其稍微移项：

$\quad \quad \quad \quad \quad \quad \quad \quad \;\;pre_{1,a}+nxt_{1,b}> pre_{0,n}-pre_{0,a}-nxt_{0,b}$

$\quad \; pre_{1,a}+nxt_{1,b}+pre_{0,a}+nxt_{0,b}\ge pre_{0,n}$

$(pre_{1,a}+pre_{0,a})+(nxt_{1,b}+nxt_{0,b})> pre_{0,n}$

$\quad \quad \quad \quad \quad \quad \quad \quad \quad \quad \quad \quad \quad a+b> pre_{0,n}$

也就是，当 $a+b> pre_{0,n}$ 时，代价取 $pre_{1,a}+nxt_{1,b}$ 反之取 $pre_{0,n}-pre_{0,a}-nxt_{0,b}$。

容易发现，$pre$ 和 $nxt$ 序列都是非严格单调递增的。

则，我们想要在代价取 $pre_{1,a}+nxt_{1,b}$ 的情况下使之最小化，那么已知 $a$，无疑让 $b$ 越小越好，而为了满足 $a+b> pre_{0,n}$，我们让 $b=pre_{0,n}-a+1$ 时最佳。

我们想要在代价取 $pre_{0,n}-pre_{0,a}-nxt_{0,b}$ 的情况下使之最小化，那么已知 $a$，无疑让 $b$ 越大越好，而为了满足 $a+b\le pre_{0,n}$，我们让 $b=pre_{0,n}-a$ 时最佳。

这样，我们只需要枚举 $a$，然后 $\Theta(1)$ 最优化 $b$，计算代价取最小值即可。时间复杂度 $\Theta(n)$。

## Code：
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
#define _go(i,u) for(int i=head[u];i;i=Edge[i].nxt)
using namespace std;
namespace I {
	template <typename T> void read(T& x) {
		x=0; T f=1; char ch=getchar();
		while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
		while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch&15); ch=getchar(); }
		x=x*f; return;
	}
	template <typename T,typename ...Arg> void read(T& x,Arg& ...arg) {
		read(x); read(arg...);
	}
}
namespace Math {
	template <typename T> T power(T a,T b,T MOD) {
		T ans=1; while(b) { if(b&1) ans=ans*a%MOD; a=a*a%MOD; b>>=1; } return ans%MOD;
	}
	template <typename T> T gcd(T a,T b) {
		if(b) return gcd(b,a%b); return a;
	}
	template <typename T> T lcm(T a,T b) {
		return a/gcd(a,b)*b;
	}
	template <typename T> T inv(T n,T p) {
		return power(n,p-2);
	}
	const int Test[]={0,2,3,5,7,11,13,17,19,23,29};
	template <typename T> bool is_prime(T n) {
		if(n<2) return 0;
		T t=n-1,k=0; while((t+1)&1) ++k,t>>=1;
		_for(i,1,10) {
		    if(n==Test[i]) return 1;
		    T s=power(Test[i],t,n); T tmp=s;
		    _for(j,1,k) {
		        tmp=s*s%n; if(tmp==1&&s!=1&&s!=n-1) return 0; s=tmp;
		    }
		    if(s!=1) return 0;
		}
		return 1;
	}
}
const int N=2e5+5;
char s[N];
int T,n,pre0[N],pre1[N],nxt0[N],nxt1[N];
signed main() {
	I::read(T);
	while(T--) {
		scanf("%s",s+1); n=strlen(s+1);
		_for(i,1,n) pre0[i]=pre0[i-1]+(s[i]=='0'),pre1[i]=pre1[i-1]+(s[i]=='1');
		_for(i,1,n) nxt0[i]=nxt0[i-1]+(s[n-i+1]=='0'),nxt1[i]=nxt1[i-1]+(s[n-i+1]=='1');
		int ans=0x7fffffff;
		_for(i,0,pre0[n])
			ans=min(ans,min(pre0[n]-pre0[i]-nxt0[pre0[n]-i],pre1[i]+nxt1[pre0[n]-i+1]));
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：jr_zch (赞：0)

# [Binary String](https://www.luogu.com.cn/problem/CF1680C)

## by jr_zch

### 题目大意

给你一个字符串 $s$ 要求从开头和结尾删除若干个字母 求最小的移除 $1$ 的个数或保留 $0$ 的个数。

### 题目解法

***一个优秀的思路往往来源于最暴力的解法***。

* $O(n^3)$ 算法：枚举开头和结尾删除的个数 然后遍历整个序列求代价。

* $O(n^2)$ 算法：用**前缀和**与**后缀和**预处理** $0$ 和 $1$ 的个数** 就可以 $O(1)$ 求代价了。

* $O(n)$ 算法：

  通过公式变形 **只枚举其中一个量**就可以算出答案。

  先预处理 $fsum_{0~i}$ $fsum_{1~i}$ $ssum_{0~i}$ $ssum_{1~i}$ 分别表示前 $i$ 个数字中 $0$ 和 $1$ 的个数 后$i$个数字中$0$和$1$的个数 即**前缀和**与**后缀和**。

  显然 这$4$个数组的值都是**递增**的 $($个数会越来越多 真的很显然$)$ 。

  设要删除前 $a$ 个以及后 $b$ 个数字 代价即为 $\max(fsum_{1~a}+ssum_{1~b},fsum_{0~n}-fsum_{0~a}-ssum_{0~b})$。

  其中n为**序列长度**。

  就会有**判断语句**为 $fsum_{1~a}+ssum_{1~b}>fsum_{0~n}-fsum_{0~a}-ssum_{0~b}$ 。

  接下来对它进行**变形**。

  > $fsum_{1~a}+ssum_{1~b}>fsum_{0~n}-fsum_{0~a}-ssum_{0~b}$
  >
  > $fsum_{1~a}+fsum_{0~a}+ssum_{1~b}+ssum_{0~b}>fsum_{0~n}$
  >
  > $a+b>fsum_{0~n}$

  所以如果 $a+b>fsum_{0~n}$ 那么答案取 $fsum_{1~a}+ssum_{1~b}$ 否则取$fsum_{0~n}-fsum_{0~a}-ssum_{0~b}$。

  现在假设答案取 $fsum_{1~a}+ssum_{1~b}$。

  通过**枚举**可以确定 $a$ 的值。

  因为**要求最小值且数组递增** 肯定要让 $b$ **越小越好**。

  结合条件 $a+b>fsum_{0~n}$ $b$ 取 $fsum_{0~n}-a+1$ 即可求出答案。

  反之 如果答案取 $fsum_{0~n}-fsum_{0~a}-ssum_{0~b}$ 。

  同理 肯定要让 $b$ **越大越好** 则 $b=fsum_{0~n}−a$ 。

  枚举 $a$ 的时候将所有答案**取 $\min$**。

  **code：**

  ```c++
  #include <bits/stdc++.h>
  #define int long long
  using namespace std;
  
  const int maxn=2e5+7,inf=0x3f3f3f3f;
  int t,n,ans;
  int fs[2][maxn],ss[2][maxn];
  char s[maxn];
  
  signed main(){
  	scanf("%lld",&t);
  	while(t--){
  		scanf("%s",s+1),n=strlen(s+1),ans=inf;
  		for(int i=1;i<=n;i++){
  			fs[0][i]=fs[0][i-1];
  			fs[1][i]=fs[1][i-1];
  			if(s[i]=='0') fs[0][i]++;
  			else fs[1][i]++;
  		}
  		for(int i=1;i<=n;i++){
  			ss[0][i]=ss[0][i-1];
  			ss[1][i]=ss[1][i-1];
  			if(s[n-i+1]=='0') ss[0][i]++;
  			else ss[1][i]++;
  		}
  		for(int i=0;i<=fs[0][n];i++) ans=min(ans,min(fs[0][n]-fs[0][i]-ss[0][fs[0][n]-i],fs[1][i]+ss[1][fs[0][n]-i+1]));
  		printf("%lld\n",ans);
  	}
  	return 0;
  }
  ```

---

