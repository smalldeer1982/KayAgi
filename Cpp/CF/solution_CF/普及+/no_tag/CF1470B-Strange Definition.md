# Strange Definition

## 题目描述

Let us call two integers $ x $ and $ y $ adjacent if $ \frac{lcm(x, y)}{gcd(x, y)} $ is a perfect square. For example, $ 3 $ and $ 12 $ are adjacent, but $ 6 $ and $ 9 $ are not.

Here $ gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ , and $ lcm(x, y) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ x $ and $ y $ .

You are given an array $ a $ of length $ n $ . Each second the following happens: each element $ a_i $ of the array is replaced by the product of all elements of the array (including itself), that are adjacent to the current value.

Let $ d_i $ be the number of adjacent elements to $ a_i $ (including $ a_i $ itself). The beauty of the array is defined as $ \max_{1 \le i \le n} d_i $ .

You are given $ q $ queries: each query is described by an integer $ w $ , and you have to output the beauty of the array after $ w $ seconds.

## 说明/提示

In the first test case, the initial array contains elements $ [6, 8, 4, 2] $ . Element $ a_4=2 $ in this array is adjacent to $ a_4=2 $ (since $ \frac{lcm(2, 2)}{gcd(2, 2)}=\frac{2}{2}=1=1^2 $ ) and $ a_2=8 $ (since $ \frac{lcm(8,2)}{gcd(8, 2)}=\frac{8}{2}=4=2^2 $ ). Hence, $ d_4=2 $ , and this is the maximal possible value $ d_i $ in this array.

In the second test case, the initial array contains elements $ [12, 3, 20, 5, 80, 1] $ . The elements adjacent to $ 12 $ are $ \{12, 3\} $ , the elements adjacent to $ 3 $ are $ \{12, 3\} $ , the elements adjacent to $ 20 $ are $ \{20, 5, 80\} $ , the elements adjacent to $ 5 $ are $ \{20, 5, 80\} $ , the elements adjacent to $ 80 $ are $ \{20, 5, 80\} $ , the elements adjacent to $ 1 $ are $ \{1\} $ . After one second, the array is transformed into $ [36, 36, 8000, 8000, 8000, 1] $ .

## 样例 #1

### 输入

```
2
4
6 8 4 2
1
0
6
12 3 20 5 80 1
1
1```

### 输出

```
2
3```

# 题解

## 作者：fanfansann (赞：14)

## [***点我获得更好的阅读体验***](https://fanfansann.blog.csdn.net/article/details/113522707)




**Problem D Strange Definition**

两个整数 $x$ 和 $y$ 是 **相邻的** 当 $\frac{lcm(x,y)}{gcd(x,y)}$是完全平方数。

你有一个长度为 $n$ 的序列 $a$。每一秒，所有的 $a_i$都会变成序列中所有和它 **相邻的** 的数的乘积。令 $d_i$为数列中与 $a_i$    **相邻的** 的数的个数

有 $q$ 次询问，每次询问给出一个 $w$，求在 $w$ 秒时的 
$\max\{d_i\}$

**Solution**

首先，我们来学习一个单词：$\tt perfect\ square$：完全平方数...我还以为是完美的正方形，我说哪来的正方形...给我人看傻了...

以及 $\tt adjacent$： adj. 相邻的，毗邻的

然后开始照例分析题目中的性质。

首先是完全平方数，就是指整数 $x$ 存在一个正整数 $y$ ，使得 $x=y^2$，整数 $x$ 就是一个完全平方数。

我们定义两个数是相邻的，是指两个整数 $x$ 和 $y$ ，满足：   $\frac{lcm(x,y)}{gcd(x,y)}$ 是完全平方数。

我们知道 $\gcd(x,y) \times lcm(x,y)=x\times y$。

$$\frac{lcm(x,y)}{gcd(x,y)}=\frac{x\times y}{\gcd(x,y)^2}$$

这个东西是完全平方数，也就意味着它可以被开根。

即

$$\sqrt{\frac{x\times y}{\gcd(x,y)^2}}=\frac{\sqrt{x\times y}}{\gcd(x,y)}$$

也就是说对于任意两个整数 $x$ 和 $y$ 而言，若 $x\times y$ 是完全平方数，则这两个数是相邻的。

由 **数论必备** 唯一分解定理得：

$x=p_1^{\alpha_1}\times p_2^{\alpha_2} \times \cdots\times p_{k}^{\alpha_{k}}$

$y=p_1^{\beta_1}\times p_2^{\beta_2} \times \cdots\times p_{k}^{\beta_{k}}$

$x\times y=p_1^{\alpha_1+\beta_1}\times p_2^{\alpha_2+\beta_2} \times \cdots\times p_{k}^{\alpha_k+\beta_{k}}$

显然，若两个数的乘积是完全平方数，则所有质因子的次幂 $\alpha +\beta$ 均为偶数。

也就意味着所有质因子对应的 $\alpha$ 和 $\beta$ 是同奇偶性的，即 $\alpha$ 是奇数， $\beta$ 也是奇数，或者 $\alpha$ 是偶数， $\beta$ 也是偶数，或者一个是偶数，一个是 $0$ ，这样二者相加才是偶数。

因为我们发现还有 $0$ 的存在，所以我们需要考虑如何把偶次幂与偶次幂，和 $0$ 次幂与偶次幂表示成一个形式。很容易就想到了我们判断奇偶性的时候使用的 `% 2`，这样偶次幂或者本来就是 $0$ 的最后都会变成 $0$ ，而奇次幂最后会变成 $1$ 所以我们将每个数都质因数分解的同时，对于每一个质因子的次幂都 `% 2` ，也就是质因数分解的时候指数一直 `/= 2` 也就是 $/= i^2$ 。最后将 $x=p_1^{\alpha_1}\times p_2^{\alpha_2} \times \cdots\times p_{k}^{\alpha_{k}}$ 变为 $x=p_1^{1}\times p_2^{0} \times \cdots\times p_{k}^{0}$ 的形式。

这样，最后只要是 $0$ 就都是一组。

但是对于奇数而言，不一定。因为虽然都是是 $1$ ，但是奇次幂的话，必须能够配对，才是一组，配对的意思就是 变成 $x=p_1^{1}\times p_2^{0} \times \cdots\times p_{k}^{0}$ 的形式以后，两个数剩余的质因子必须完全相同，也就是拥有相同的 $1$ 次幂的质因子，也就是转换为上面的那个形式以后， 两个数的值完全相同。

我们可以使用 `map` 来储存同一组（相互都相邻）的元素个数。

分析完相邻的性质以后，我们知道如何判断是否相邻，我们可以直接对于每个输入的数，判断一下，存入 `map` 中。

然后再来考虑第二个问题，题目中的操作，合并。

我们从第 $0$ 秒开始，每一秒，每一个数都会变成所有与自己相邻（包括自己）的数的乘积，然后有 $q$ 次询问，每次会问第 $\omega$ 秒，数列中，所有相邻组（全部两两相邻）中元素个数最多的个数。$\omega \le10^{18}$。所以我们瞬间就可以看出点什么东西，就是这个操作修改以后，答案肯定存在一个循环节或者之后的某一时刻就不会再发生变化了。因为询问的数据太大， 啥数据结构都不可能存得下，也不可能快速地求解。

然后我们来分析这个操作，同一组的所有的数都会同时合并，我们根据上面的分析，知道一共有四种组别

1. 个数为偶数的 $0$ 组（偶次幂）
2. 个数为奇数的 $0$ 组（偶次幂）
3. 个数为偶数的 $1$ 组（奇次幂）
4. 个数为奇数的 $1$ 组（奇次幂）

我们来分析这四种组别合并后会发生什么。

- **第一种，第二种**

我们的合并操作是全部数的乘积，对于质因数分解后的 $x$ ，全部数的乘积实际上就是所有数的指数的和，而第一种，第二种，不管组内个数是奇数个还是偶数个，因为都是偶数，所以和仍然是偶数，也意味着还是第一种或者第二种，而第一种和第二种实际上是同一种，因为都是相邻的，这里分开只是两种不同的情况。所以第一第二种任意秒以后，仍然还是第一第二种。

- **第三种**

偶数个全部对应的奇次幂，和为偶数，因为每个次幂都是奇数，也就是 $1$ ，奇数加奇数为偶数，在第一秒第一次合并以后归为第一种或者第二种。

- **第四种**

奇次幂，还是奇数个，那么相乘，也就是指数相加，永远都还是第四种。

分析完我们发现，询问一共分 $\omega=0$ 和 $\omega>0$ 两种情况， $\omega=0$ 的时候，数列中的数一共分为三种

- 第一种就是我们上面说的第一第二种，我们累计所有指数是偶次幂的元素的个数。
- 第二种为我们上面说的第三种，即虽然是 $1$ 组，但是个数是偶数，也就是我们 `map` 存的第二维是偶数。
- 第三种就是我们上面说的第四种，奇数个的奇数次幂，我们用 `map` 来hash一下，对于这一种的每一个值，都分为每一组，取最值。

 $\omega=0$ 时答案就是上述三种的元素个数的最大值。

 $\omega>0$ 时， 第二种全部归为第一种，所以我们只需要用第三种里最大的那一组的个数，与第一种元素个数加上第二种的元素个数，取最大值即可。


**detail**

虽然上面说了那么大一堆，这些实际上只是我当时做题的时候的心理活动，在演草纸上画思维导图来分类讨论，总共花了不到 $10$ 分钟，因为写题解我习惯讲的比较详细，我希望可以把如何思考问题带给大家，所以内容有点多了，请大家见谅 ...

**Code**

实现就非常简单了，照着上面的思路模拟一遍就行了
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;
const int N = 3e5 + 7, mod = 1e9 + 7;
typedef long long ll;
unordered_map<int, int> Hash;
void get_factor(int x)
{
    for(int i = 2; ; ++ i) {
        int even = i * i;
        while(x % even == 0 && x >= even) x /= even;
        if(x < even) break;
    }
    Hash[x] ++ ;////我们实际上只需要知道它是奇还是偶
    //x就是把所有的质因子的次方全部压成0或者1，0就是偶次幂，x=1(被除尽了)，1次就是奇次幂。x=若干一次质因子的乘积

    //偶次幂无所谓，奇次幂必须所含奇次幂的质因子全部完全相同才是一组（能凑成偶数，也就是完全平方数）
}
int n, m, t, q;
int main()
{
    scanf("%d", &t);
    while(t -- ) {
        Hash.clear();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i) {
            int a;
            scanf("%d", &a);
            get_factor(a);
        }
        int ans1 = 0, ans2 = 0;
        for(auto it = Hash.begin(); it != Hash.end(); ++ it) {
            //0秒的情况不变
            ans1 = max(ans1, it -> second);//second是个数，0秒没有变化的时候，最大数量的那组就是最大的那组
            //1秒的情况合并
            if(it -> second % 2 == 0 || it -> first == 1)//(组内有偶数个 || 这个组是偶数次幂组)
                ans2 += it->second;//1秒钟后就会全部归为偶组
        }
        ans2 = max(ans2, ans1);//取奇数组和偶数组中的最大值
        scanf("%d", &q);
        for(int i = 1; i <= q; ++ i) {
            ll w;
            scanf("%lld", &w);
            if(w == 0)
                printf("%d\n", ans1);
            else printf("%d\n", ans2);
        }
    }
    return 0;
}
```

---

## 作者：灵茶山艾府 (赞：7)

由于 $z=\dfrac{\textrm{lcm}(x,y)}{\gcd(x,y)} = \dfrac{xy}{\gcd(x,y)^2}$，所以要使 $z$ 为完全平方数，$xy$ 需要是完全平方数。

定义 $x$ 的**核** $\textrm{core}(x)$ 为 $x$ 去掉其完全平方数后剩余的部分，例如 $\textrm{core}(12)=\dfrac{12}{4}=3,\ \textrm{core}(16)=\dfrac{16}{16}=1$.

由定义可知，$xy$ 为完全平方数，当且仅当 $\textrm{core}(x)=\textrm{core}(y)$.

这样就可以通过统计 $\textrm{core}(x)$ 的个数来求出第 $0$ 秒时的答案，即按照 $\textrm{core}$ 值分组，元素最多的组的元素个数。

对于**替换**操作，由于是将所有等于 $\textrm{core}(x)$ 的数乘起来，若这样的数有偶数个，显然我们可以得到一个完全平方数，乘积的 $\textrm{core}$ 值为 $1$；若这样的数有奇数个，则乘积的 $\textrm{core}$ 值仍为 $\textrm{core}(x)$。

所以经过一秒后，$\textrm{core}(x)$ 要么变为 $1$，要么不变。而 $\textrm{core}(x)$ 一旦变为 $1$ 后，后续的替换操作也不会改变其值，所以对于任意正数秒之后的答案和第 $1$ 秒的答案是一样的。将 $\textrm{core}$ 值更新一遍后重新统计即可。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	const mx int = 1e6
	lpf := [mx + 1]int{1: 1}
	for i := 2; i <= mx; i++ {
		if lpf[i] == 0 {
			for j := i; j <= mx; j += i {
				if lpf[j] == 0 {
					lpf[j] = i
				}
			}
		}
	}
	core := func(x int) int {
		c := 1
		for x > 1 {
			p := lpf[x]
			e := 1
			for x /= p; lpf[x] == p; x /= p {
				e ^= 1
			}
			if e > 0 {
				c *= p
			}
		}
		return c
	}

	var T, n, v, q int
	var w int64
	for Fscan(in, &T); T > 0; T-- {
		cnt := map[int]int{}
		for Fscan(in, &n); n > 0; n-- {
			Fscan(in, &v)
			cnt[core(v)]++
		}
		maxC, c1 := 0, cnt[1]
		for v, c := range cnt {
			maxC = max(maxC, c)
			if v > 1 && c&1 == 0 {
				c1 += c
			}
		}
		for Fscan(in, &q); q > 0; q-- {
			if Fscan(in, &w); w == 0 {
				Fprintln(out, maxC)
			} else {
				Fprintln(out, max(maxC, c1))
			}
		}
	}
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
```




---

## 作者：Fairicle (赞：3)

考虑两个数什么时候能满足题述条件。设 $x=p_1^{a_1}p_2^{a_2}...p_k^{a_k},y=p_1^{b_1}p_2^{b_2}...p_{k'}^{b_{k'}}$

设它们质因子的并集为 $P$，那么 LCM 就是 $\prod_{p_i\in P}p_i^{\max(a_i,b_i)}$，GCD 就是 $\prod_{p_i\in P}p_i^{\min(a_i,b_i)}$。

故 $\frac{LCM}{GCD}=\prod_{p_i\in P}p_i^{{\max(a_i,b_i)}-{\min(a_i,b_i)}}$

要想是完全平方数，只要每对 $(a_i,b_i)$ 的差是偶数就行了。

可以发现，若两个数满足条件，则它们分解出来的每个指数**对 2 取余**之后的结果是一样的。

于是我们**把每个数都分解，然后把指数对 2 取余，得到新的数**。那么这个时候，相等的数就说明它们的原数之间是满足条件的，所以 $w=0$ 的情况只需要找出**哪个相等数集合最大**。

$w\leq 10^{18}$，怎么解决？看到这个就想到必定有个结论使得 $w$ 过大时一定是某个答案。我们发现，当相等集合合并的时候（也就是都变成这个集合的乘积），只有两种情况，合并成 1，或者不变（在取余之后）。

证明：

显然**原集合数之积**进行指数对 2 取余之后的结果和**已经取余过的数（这些数已经相等）的乘积**进行指数对 2 取余是等价的。设这些相等的数都为 $p_1p_2p_3...p_k$（指数为0无影响，忽略），总共有 $q$ 个这种数。那么显然 $q$ 是奇数时不变，$q$ 是偶数时变成完全平方数，取余之后所有指数为 0，乘积为 1。

那么 $w=1$ 时就是部分集合不变，部分集合全部变成 1。而之后就不会变化。（显然，为 1 的不变，先前的不变集合肯定不变）。

所以本题就转化成了 $w=0$ 和 $w>0$ 的情况。

~~其实比赛的时候随便猜猜这个结论就行了~~

code：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define N 300010
#define ri register int
#define ll long long
inline ll rd(){
    ll x=0,flg=1;
    char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') flg=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+(ch^48);ch=getchar();}
    return x*flg;
}
int t,n,a[N],q,tmp,cnt,fir,sec,pre;
ll w;
int main(){
    t=rd();
    while(t--){
        n=rd();
        for(ri i=1;i<=n;++i){
            a[i]=rd();tmp=a[i];
            for(ri j=2;j*j<=tmp;++j){
                if(tmp%j==0){
                    cnt=0;
                    while(tmp%j==0) tmp/=j,a[i]/=j,cnt++;
                    if(cnt&1) a[i]*=j;
                }
            }
        }
        
        fir=0,sec=0,pre=0;
        sort(a+1,a+1+n);a[n+1]=0;
        for(ri i=1;i<=n;++i){
            if(a[i]!=a[i+1]) {fir=max(fir,i-pre);if(a[i]==1) sec+=i-pre;else if(((i-pre)&1)^1) sec+=i-pre;pre=i;} //判断一下，长度为奇数就记入 w>0 的答案
        }
        q=rd();sec=max(sec,fir);
        while(q--) {w=rd();if(w) printf("%d\n",sec);else printf("%d\n",fir);} 
    }
    return 0;
}
```


---

## 作者：do_while_true (赞：2)

[$\text{不一样的阅读体验}$](https://www.cnblogs.com/do-while-true/p/14242801.html)

# $\mathcal{Translate}$

注: "$x,y$ adjacent" 译作 "$x,y$ 相邻"

定义 $x,y$ 相邻需要满足 $\frac{lcm(x,y)}{gcd(x,y)}$ 是完全平方数。

共有 $t$ 组数据。

对于每一种数据，给定长度为 $n$ 的序列 $a_i$，从第 $1$ 秒 $a$ 开始变换，每一次 $a_i$ 变成所有与它相邻的数的乘积（包括它自己）。

定义 $d_i$ 为 $a$ 中与 $a_i$ 相邻的数的个数。

共有 $q$ 次询问，每次询问给出一个 $w$，回答第 $w$ 秒时（也就是经过 $w$ 次变换后）的 $\max d_i$。

# $\mathcal{Solution}$

$\frac{lcm(x,y)}{gcd(x,y)}=\frac{x\times y}{gcd(x,y)^2}$

$\because gcd(x,y)^2$ 是完全平方数。

$\therefore \frac{x\times y}{gcd(x,y)^2}$ 是完全平方数等价于 $x\times y$ 是完全平方数。

若 $x\times y$ 是完全平方数。

$\therefore x\times y$ 质因数分解后每个底数的指数都是偶数。

$\therefore x,y$ 分别质因数分解之后各个底数的指数奇偶性相同。

到这里显然可以得出相邻是具有传递性的。

考虑把每个串质因数分解后出的指数模 $2$ 看成一个 $01$ 串，若 $01$ 串相等则这两个数是相邻的。

若多个数相乘，最后的乘积的 $01$ 串为所有因数的 $01$ 串的异或后结果（看成每个质因子分别相乘即可说明此点）。

那么考虑对相同的 $01$ 串看成一个集合，考虑一次变换，若 $01$ 串为全 $0$ 或集合大小为奇数则这些 $01$ 串不变，否则这些 $01$ 串都变成 $0$。

那么显然只有第一次变换是有用的，这会使所有集合大小为偶数的 $01$ 串变成全 $0$。

分别统计第 $0$ 秒和第 $1$ 秒时的答案即可，后面的答案和第 $1$ 秒相同。

把 $01$ 串为 $1$ 的位置拿下来哈希放在一个 $map$ 里面就能做了。

一组数据的时间复杂度为 $\mathcal{O}(n\log n+n\sqrt{\max a_i})$

# $\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
#include<map>
#define pb push_back
#define pp std::pair<unsigned long long, unsigned long long> 
#define mp std::make_pair
#define fir first
#define sec second
#define ll long long
#define re register
#define ull unsigned long long
//#define int long long
inline int Max(int x, int y) { return x > y ? x : y; }
inline int Min(int x, int y) { return x < y ? x : y; }
inline int Abs(int x) { return x < 0 ? ~x + 1 : x; }
inline int read() {
	int r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') w = 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		r = (r << 3) + (r << 1) + (ch ^ 48);
		ch = getchar();
	}
	return w ? ~r + 1 : r;
}
//#undef int
const int N = 300010;
const ull base = 21841;
const ull mod = 29050993; 
const ull base2 = 1429;
const ull mod2 = 68861641;
int n, a[N], ans1, ans2;
pp hs[N];
std::map<pp, int>vis;

pp hasher(int x) {
	std::vector<int>vec; int xx = x;
	for(int i = 2; i * i <= xx; ++i)
		if(x % i == 0) {
			int ct = 0;
			while(x % i == 0) x /= i, ++ct;
			if(ct&1) vec.pb(i); 
		}
	if(x > 1) vec.pb(x);
	ull sum1 = 0, sum2 = 0;
	std::sort(vec.begin(), vec.end());
	int len = vec.size(); 
	for(int i = 0; i < len; ++i) sum1 = (sum1 * base % mod + (ull)vec[i]) % mod;
	for(int i = 0; i < len; ++i) sum2 = (sum2 * base2 % mod2 + (ull)vec[i]) % mod2;
	return mp(sum1, sum2);
}

void solve() {
	n = read(); vis.clear(); ans1 = ans2 = 0;
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) hs[i] = hasher(a[i]), vis[hs[i]]++, ans1 = Max(ans1, vis[hs[i]]);
	for(int i = 1; i <= n; ++i) if(vis[hs[i]] % 2 == 0 || hs[i].fir + hs[i].sec == 0) ans2 += vis[hs[i]], vis[hs[i]] = 0;
	ans2 = Max(ans1, ans2);
	int q = read();
	ll x;
	while(q--) {
		scanf("%lld", &x);
		if(x == 0) printf("%d\n", ans1);
		else printf("%d\n", ans2);
	}
}

signed main() {
	int T = read();
	while(T--) solve(); 
	return 0;
}
```

---

## 作者：AK_400 (赞：0)

注意到 $\operatorname{lcm}(x,y)\cdot\gcd(x,y)=x\cdot y$。

于是 $\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}=\dfrac{x\cdot y}{\gcd(x,y)^2}$。

令完全平方数 $x=k^2$，若 $\exists p,p^2|x$，则 $\dfrac{x}{p^2}=( \dfrac{k}{p})^2$，即其除以一个完全平方数后仍为完全平方数。

即题目要求的相邻的数 $x,y$ 的乘积为完全平方数。

所以我们可以对每个数除以它最大的完全平方因子，这样相同的数相乘才是完全平方数，开个桶，取最大值即为不做修改时的答案。

对于一次操作，如果一个数的相邻的数有偶数个，那么它本身会变成一个完全平方数，除以它最大的完全平方因子后变成一，否则不变。因为一无法更改，于是只有一次修改有效，按上面的做法做即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[300005];
bool not_prime[1000005];
vector<int>prime;
map<int,int>cnt;
void read(int &x){
    char c=getchar();
    x=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
}
void slv(){
    cnt.clear();
    read(n);
    for(int i=1;i<=n;i++)read(a[i]);
    int ans0=0;
    for(int i=1;i<=n;i++){
        for(int x:prime){//除以它最大的完全平方因子等价于任意除以一个非一完全平方因子直到没有。
            if(x*x>a[i])break;
            while(a[i]%(x*x)==0)a[i]/=(x*x);
        }
        // cout<<a[i]<<" ";
        cnt[a[i]]++;
        ans0=max(ans0,cnt[a[i]]);//不修改的答案。
    }
    int ans1=ans0;
    for(auto it=cnt.begin();it!=cnt.end();it++){
        if(it->first!=1&&it->second%2==0){//偶数个会变成1。
            cnt[1]+=it->second;
            ans1=max(ans1,cnt[1]);
        }
    }
    int q;
    read(q);
    while(q--){
        int w;
        read(w);
        if(w==0)printf("%lld\n",ans0);
        else printf("%lld\n",ans1);
    }
}
signed main(){
    for(int i=2;i<=1000;i++){//预处理1000以内质数。
        if(!not_prime[i]){
            for(int j=i+i;j<=1000;j+=i)not_prime[j]=1;prime.push_back(i);
        }
        
    }
    int T;cin>>T;while(T--)
    slv();
    return 0;
}
```

---

## 作者：氧少Kevin (赞：0)

# CF1471D - Strange Definition
- 数论、质因数、哈希
- https://www.luogu.com.cn/problem/CF1470B

## 题意
两个整数 $x$ 和 $y$ 是*有关的*当且仅当 $\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$ 是完全平方数。

你有一个长度为 $n(n\leq 3\cdot 10^5)$ 的序列 $a(1\leq a_i\leq 10^6)$。每一秒，所有的 $a_i$ 都会变成序列中所有和它*有关的*数的乘积。令 $d_i$ 为数列中与 $a_i$ *有关的*数的个数

有 $q$ 次询问，每次询问给出一个 $w(0\leq w\leq 10^{18})$，求在 $w$ 秒时的 $\max\{d_i\}$。

## 思路
$$
    \frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}=\frac{x\cdot y}{\gcd^2(x,y)}=k^2
$$

$$
    xy=\big( k\cdot \gcd(x,y)\big )^2
$$

因此，$\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$ 是完全平方数 $\Leftrightarrow x\cdot y$ 是完全平方数。

$x\cdot y$ 是完全平方数，说明对 $x\cdot y$ 分解成若干个质因数相乘的形式后，每一种质因数的指数都是偶数。

假设：
$$x=p_1^{k_1}\cdot p_2^{k_2} \cdot p_3^{k_3}\dots p_n^{k_n}$$
$$y=p_1^{k_1'}\cdot p_2^{k_2'} \cdot p_3^{k_3'}\dots p_n^{k_n'}$$

那么，$k_i$ 与 $k_i'$ 的奇偶性相同。

### 计算第 $0$ 秒时的答案
对每个 $a_i$ 分解质因数，挑出分解的质因数中指数为奇数的计算哈希，在所有 $a_i$ 中哈希相同的就是有关的。

不难发现，如果 $a_i$ 和 $a_j$ 有关，并且 $a_j$ 和 $a_k$ 有关，那么 $a_i$ 和 $a_k$ 有关。

实际上，形成的是连通块，同一个连通块里的元素两两有关。

### 第 $1$ 秒以及第 $1$ 秒过后
从第 $1$ 秒开始，每一秒，$a_i$ 都会变成序列中所有和它*有关的*数的乘积。

如果第 $0$ 秒时：
- 某个 $a_i$ 的某个 $k_j$ 是奇数，并且它所处于的连通块大小为偶数，那么第 $1$ 秒时，它所处的连通块中所有的 $k_j$ 会变成偶数，在这以后，此 $k_j$ 的奇偶性永远不变。
- 其它情况，$k_j$ 的奇偶性不会再变。

因此，在第 $1$ 秒过后，答案不会再改变。

计算第 $0$ 秒和 第 $1$ 秒的答案后，回答询问即可。

**统计第 $1$ 秒的答案**

$ans_1 = \max(ans_0,$ $\sum$所有长度为奇数的连通块的长度 $+\sum$ 所有$k_i$为偶数的连通块长度  $)$

---

## 作者：vectorwyx (赞：0)

思维题。

看到 gcd 和 lcm 首先想到分解质因数。令 $a=\prod_{i=1}^{\infty}p_{i}^{e_{i}},b=\prod_{i=1}^{\infin}p_{i}^{e'_{i}}$（$p_{i}$ 为第 $i$ 个质数）。则 $lcm(a,b)=\prod_{i=1}^{\infin}p_{i}^{\max(e_{i},e'_{i})},\gcd(a,b)=\prod_{i=1}^{\infin}p_{i}^{\min(e_{i},e'_{i})}$。令 $t=\frac{lcm(a,b)}{gcd(a,b)}$，则$t=\prod_{i=1}^{\infin}p_{i}^{\max(e_{i},e'_{i})-\min(e_{i},e'_{i})}$。因此 $t$ 为完全平方数当且仅当 $\forall i\in \mathbb{N^{+}},2|(\max(e_{i},e'_{i})-\min(e_{i},e'_{i}))$。也就是 $e_{i}$ 与 $e'_{i}$ 奇偶性相同。因此 $a$ 和 $b$ 是否相邻就只与 $e_{i}$ 和 $e'_{i}$ 的奇偶性有关了，我们把奇数看做 $1$，偶数看做 $0$，每个数就可以用一个 $01$ 串来表示，而两个数相邻当且仅当它们的 $01$ 串相同。

这也就是说，每次变化都会将数组中所有 $01$ 串相同的元素合并在一起（其实就是把这些 $01$ 串加起来）。如果参与合并的元素个数为偶，那么合并过后每个 $e_{i}$ 都会变为 $0$，即一个全 $0$ 串。如果参与合并的元素个数为奇，那么合并之后每个元素的 $01$ 串并不会发生改变。这意味着数组在变化过一次后，出现的全 $0$ 串从此始终是全 $0$ 串，非全 $0$ 串从此也不会再发生改变，所以答案最多只有两种： $w=0$ 时，和 $w=1$ 时，直接套哈希模拟就行，由于  $01$ 串的哈希值只与 $1$ 的位置有关，因此我们可以把所有 $1$ 的位置拎出来做哈希。时间复杂度为 $O(n\log n+n\sqrt {\max a_{i})}$。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define mod1 998244353
#define mod2 19260817
#define base1 19260813
#define base2 300007
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e6+5;
int np[N],p[N],top,rk[N];

void xxs(){
	fo(i,2,N-1){
		if(!np[i]) p[++top]=i,rk[i]=top;
		fo(j,1,top){
			int t=i*p[j];
			if(t>=N) break;
			np[t]=1;
			if(i%p[j]==0) break;
		}
	}
}

int a[N];

struct Ha{
	int v1,v2;
	bool operator<(const Ha &x){
		if(v1!=x.v1) return v1<x.v1;
		return v2<x.v2;
	}
	bool operator==(const Ha &x){return v1==x.v1&&v2==x.v2;} 
}hx[N];

void work(){
	int n=read();
	fo(i,1,n) a[i]=read();
	fo(i,1,n){
		hx[i].v1=hx[i].v2=0;
		int t=a[i];
		//printf("%d:\n",t);
		fo(j,1,top){
			if(p[j]*p[j]>t) break;
			bool cnt=0;
			while(t%p[j]==0){
				t/=p[j];
				cnt^=1;
			}
			//printf("%d %d\n",p[j],cnt);
			if(cnt) hx[i].v1=(1ll*hx[i].v1*base1+j)%mod1,hx[i].v2=(1ll*hx[i].v2*base2+j)%mod2;
		}
		if(t>1) hx[i].v1=(1ll*hx[i].v1*base1+rk[t])%mod1,hx[i].v2=(1ll*hx[i].v2*base2+rk[t])%mod2;
		//printf("v1=%d v2=%d\n",hx[i].v1,hx[i].v2);
	}
	sort(hx+1,hx+1+n);
	int ans0=0,ans1=0,cnt=0;
	fo(i,1,n){
		int pos=i;
		while(pos<=n&&hx[pos]==hx[i]) ++pos;
		int len=pos-i;
		//printf("%d:%d %d %d %d\n",i,hx[i].v1,hx[i].v2,pos,len);
		ans0=max(ans0,len);
		ans1=max(ans1,len);
		if(len%2==0||hx[i].v1+hx[i].v2==0) cnt+=len;
		i=pos-1;
	}
	ans1=max(ans1,cnt);
	int q=read();
	while(q--){
		ll w;
		scanf("%lld",&w);
		if(w==0) printf("%d\n",ans0);
		else printf("%d\n",ans1);
	}
	//puts("");
}

int main(){
	xxs();
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```

---

