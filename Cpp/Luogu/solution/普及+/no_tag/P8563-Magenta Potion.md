# Magenta Potion

## 题目描述

给定一个长为 $n$ 的整数序列 $a$，其中所有数的绝对值均大于等于 $2$。有 $q$ 次操作，格式如下：

$\texttt{1 i k}$，表示将 $a_i$ 修改为 $k$。保证 $k $ 的绝对值大于等于 $2$。

$\texttt{2 l r}$，考虑 $[l,r]$ 的子区间（包括本身）中乘积最大的的区间乘积 $M$。如果 $M>2^{30}$，输出 `Too large`，否则输出 $M$。特别地，空区间的元素乘积定义为 $1$。

## 说明/提示

对于所有的数据，$2\le |a_i|,|k| \le 10^9$，$1 \le n,q \le 2\times 10^5$，$1 \le l \le r \le n$。

$$
\def\arraystretch{1.5}
\begin{array}{c|c|c}\hline 
\textbf{测试点编号}&\bm{~~~~~~~~n,q\le~~~~~~~~}&~~~~\textbf{特殊限制}~~~~\cr\hline 
\textsf1\sim \sf2 & 10& \cr\hline 
\sf3\sim 6 & 100&  \cr\hline 
\sf7\sim 10 & 5 \times 10^3&\cr\hline 
\sf 11\sim 13 &  &\sf A\cr\hline 
\sf14\sim 16 & & \sf B\cr\hline
\sf17\sim 20 & &\cr\hline
\end{array}
$$

$\textsf A$：保证 $a_i,k \ge 2$。

$\textsf B$：保证对于每一组询问，对应的 $r-l \ge 100$。



## 样例 #1

### 输入

```
5 7
2 2 3 4 5
2 1 5
1 3 -3
2 1 5
2 3 3
1 1 100000
1 2 100000
2 1 2```

### 输出

```
240
20
1
Too large```

# 题解

## 作者：cyhtxdy (赞：14)

## 前言

我打算在这篇题解中将线段树做法和线性贪心做法都写出来，以拓宽大家的思路，让大家有所收获。

ps：线段树篇幅略长，想直接看简单的贪心可以直接跳过。

------------

## 解题思路

先抛开修改操作，思考一下如何计算区间的最大乘积。

因为 $\left | k \right |,\left | a_i \right | \ge 2$，那么在保证乘积为正数时，乘的数字越多，乘积越大。

由于负数的特殊性，所以要根据负数的个数进行分类讨论。

- 当负数的个数为偶数时：
	
   就可以取整个区间，答案就是整个区间的乘积。

- 当负数的个数为 $1$ 且区间只有一个数字时：

	答案就为 $1$。

- 当负数的个数为 $1$ 且区间有大于 $1$ 个数字时：

	答案为负数位置左侧的乘积和右侧的乘积中的较大值。

- 当负数的个数为奇数时：

	此时就需要舍弃一个负数。根据上面的说法，就需要舍弃最左边的负数，或者最右边的负数，将剩余连续的偶数个负数和其余的正数相乘，两种方案取最大值，就是最终答案。
    
### $\text{Solution1}$
    
根据以上思路，我们需要维护的区间内的值有这些：负数出现的位置，负数的个数，区间乘积。

这启发我们采用**线段树**进行操作。

在查询区间最左边的负数位置时，可以用二分找出最小的前缀负数个数为 $1$ 的位置，查询区间最右边的负数位置时，也是如此。时间复杂度为 $O(\log^2n)$。

由于是单点修改，那么就不需要使用懒标记维护区间乘积了，可以直接维护。查询和修改的时间复杂度均为 $O(\log n)$。

查询最终答案时，根据上面思路直接写，时间复杂度 $O(\log n)$。

综上，时间复杂度为 $O(n \log^2 n)$。

值得一提的是，根据数据范围发现，如果直接维护区间乘积，这个值是非常非常巨大的，并且无法存放。

那我们可以这样操作：由于负数在最终乘完后也变为正数，那么在计算的时候判断运算中的值的绝对值是否大于等于 $2^{30} + 1$，如果符合，那就将其修改为 $2^{30}+1$。这样做减小了数据规模，并且最终计算得到的结果也会大于 $2^{30}$ ，不影响正确性。这样就可以存储下来了。

给出较简洁且部分注释的代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 2e5 + 7;
const ll P = (1ll << 30) + 1;

int n, q;
ll a[N], sum[N << 2]; //sum维护区间乘积
int num[N << 2], pos[N << 2];//num维护区间负数个数，pos维护区间负数位置

#define _max(a, b) (a > b ? a : b)
#define _min(a, b) (a < b ? a : b)

ll change (ll x) {
	return abs (x) >= P ? P : x;
}//将一个绝对值大于等于 2^30+1 的数字改为 2^30+1

struct SegMentTree {
	void pushup (int p) {
		sum[p] = change (sum[p << 1] * sum[p << 1 | 1]);//维护区间乘积
		num[p] = num[p << 1] + num[p << 1 | 1];//维护区间负数个数
	}
	
	void build (int p, int l, int r) {
		if (l == r) {
			sum[p] = change (a[l]);//减小数据规模
			if (a[l] < 0) {
				num[p] = 1;
				pos[p] = l;
			}
			return ;
		}
		int mid = (l + r) >> 1;
		build (p << 1, l, mid);
		build (p << 1 | 1, mid + 1, r);
		
		pushup (p);
	}//建树
	
	void update (int p, int l, int r, int qp, int k) {
		if (l == r) {
			sum[p] = change (k);//减小数据规模
			if (k < 0) {
				num[p] = 1, pos[p] = l;
			}
			else {
				num[p] = 0, pos[p] = 0;
			}
			return ;
		}
		int mid = (l + r) >> 1;
		if (qp <= mid) {
			update (p << 1, l, mid, qp, k);
		}
		if (qp > mid) {
			update (p << 1 | 1, mid + 1, r, qp, k);
		}
		
		pushup (p);
	}//单调修改直接暴力 logn 即可
	
	int query_num (int p, int l, int r, int ql, int qr) {
		if (ql <= l && qr >= r) {
			return num[p];
		}
		int mid = (l + r) >> 1, ans = 0;
		if (ql <= mid) {
			ans += query_num (p << 1, l, mid, ql, qr);
		}
		if (qr > mid) {
			ans += query_num (p << 1 | 1, mid + 1, r, ql, qr);
		}
		return ans;
	}//查询区间负数个数
	
	int find_l (int l, int r) {
		int ans = 0;
		while (l <= r) {//二分
			int mid = (l + r) >> 1;
			if (query_num (1, 1, n, l, mid)) {
				r = mid - 1;
				ans = mid;
				//找到最小的mid满足前缀只有一个负数，那么这就是最左边的负数位置
			}
			else {
				l = mid + 1;
			}
		}
		return ans;
	}
	
	int find_r (int l, int r) {
		int ans = 0;
		while (l <= r) {//二分
			int mid = (l + r) >> 1;
			if (query_num (1, 1, n, mid, r)) {
				l = mid + 1;
				ans = mid;
				//找到最大的mid满足后缀只有一个负数，那么这就是最右边的负数位置
			}
			else {
				r = mid - 1;
			}
		}
		return ans;
	}
	
	ll query_sum (int p, int l, int r, int ql, int qr) {
		if (ql > qr) {
			return 1;
		}
		if (ql <= l && qr >= r) {
			return change (sum[p]);//减小数据规模
		}
		int mid = (l + r) >> 1;
		ll ans = 1;
		if (ql <= mid) {
			ans = ans * query_sum (p << 1, l, mid, ql, qr);
		}
		if (qr > mid) {
			ans = ans * query_sum (p << 1 | 1, mid + 1, r, ql, qr);
		}
		return change (ans);//减小数据规模
	}//查询区间乘积
	
	ll query_ans (int p, int l, int r) {
		int tot = query_num (1, 1, n, l, r);
		if (! (tot % 2)) {
			return _min (query_sum (1, 1, n, l, r), P);
			//偶数个负数时，答案就是整个区间乘积
		}
		else {
			int nl = find_l (l, r);
			int nr = find_r (l, r);
			if (nl == nr) {
				if (l == r) {//1个负数且区间长度为1
					return 1;
				}
				else {//1个负数且区间长度大于1
					ll ans1 = abs (query_sum (1, 1, n, l, nl - 1));//负数左侧的乘积（不包括负数）
					ll ans2 = abs (query_sum (1, 1, n, nl + 1, r));//负数右侧的乘积（不包括负数）
					return _min (_max (ans1, ans2), P);
				}
			}
			else {
				ll ansl = abs (query_sum (1, 1, n, l, nl));//最左边负数左侧的乘积（包括负数）
				ll ansmid = abs (query_sum (1, 1, n, nl + 1, nr - 1));//最左边负数和最右边负数之间的乘积（不包括负数）
				ll ansr = abs (query_sum (1, 1, n, nr, r));//最右边负数右侧的乘积（包括负数）
				return _min (_max (ansl, ansr) * ansmid, P);//ansl和ansr的较大值乘以ansmid就是区间最大乘积，可以理解一下
			}//与2^30+1取min也是为了减小数据规模
		}
	}//查询区间最大乘积
} DS;

int main () {
	scanf ("%d%d", &n, &q);
	for (int i = 1; i <= n; i ++) {
		scanf ("%lld", &a[i]);
	}
	DS.build (1, 1, n);
	while (q --) {
		int op, x, y;
		scanf ("%d%d%d", &op, &x, &y);
		if (op == 1) {
			DS.update (1, 1, n, x, y);
		}
		else if (op == 2) {
			if (DS.query_ans (1, x, y) >= P) {
				printf ("Too large\n");
			}
			else {
				printf ("%lld\n", DS.query_ans (1, x, y));
			}
		}
	}
	
	return 0;
}
```


------------

### $\text{Solution2}$
观察到题目要求答案大于 $2^{30}$ 时，就输出 `Too large`。

而且 $\left | k \right |,\left | a_i \right | \ge 2$，仔细想想这有什么关联？

没错，当一个区间的长度过长时，不用计算这个区间的最大乘积，我们也知道这个最大乘积大于 $2^{30}$！

因为每个值最小为 $2$，如果超过 $30$ 个值，那么这个区间最大乘积肯定超过了 $2^{30}$！

为了保险起见，当查询的区间长度大于 $70$ 时，就可以直接输出 `Too large`！

那么这样，对于区间长度小于等于 $60$ 时，就可以根据上文的方法算出最大乘积并判断，且这个数字也可以存储下来。

这样的总复杂度为 $O(n)$，代码短并且效率高。

给出代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 2e5 + 7;
const ll P = (1ll << 30);

int n, q;
ll a[N]; 

int main () {
	scanf ("%d%d", &n, &q);
	for (int i = 1; i <= n; i ++) {
		scanf ("%lld", &a[i]);
	}
	while (q --) {
		int op, l, r;
		scanf ("%d%d%d", &op, &l, &r);
		if (op == 1) {
			a[l] = r;//O1直接修改
		}
		else if (op == 2) {
			if (r - l + 1 > 70) {
				printf ("Too large\n");//长度过长 直接输出
			} 
			else {
				int tot = 0;
				for (int i = l; i <= r; i ++) {
					if (a[i] < 0) {
						tot ++;//负数个数
					}
				}
				bool output = false;
				ll ans = 1, p, t = 1ll;
				if (!(tot % 2)) {//偶数个负数
					for (int i = l; i <= r; i ++) {
						ans = ans * abs (a[i]);
						if (ans > P) {//在运算过程中 时刻防止溢出
							printf ("Too large\n");
							output = true;
							break;
						}
					}
					if (!output) {
						printf ("%lld\n", ans);
					}
				}
				else {//奇数个负数
					for (int i = l; i <= r; i ++) {
						if (a[i] < 0) {
							p = i;
							break;
						}
					}
					for (int i = r; i > p; i --) {
						t = t * a[i];
						if (t > P) {//在运算过程中 时刻防止溢出
							printf ("Too large\n");
							output = true;
							break;
						}
					}
					if (output) {
						continue;
					}
					ans = max (ans, t);
					t = 1;
					for (int i = r; i >= l; i --) {
						if (a[i] < 0) {
							p = i;
							break;
						}
					}
					for (int i = l; i < p; i ++) {
						t = t * a[i];
						if (t > P) {//在运算过程中 时刻防止溢出
							printf ("Too large\n");
							output = true;
							break;
						}
					}
					ans = max (ans, t);
					if (!output) {
						if (ans > P) {//在运算过程中 时刻防止溢出
							printf ("Too large\n");
						}
						else {
							printf ("%lld\n", ans);
						}
					}
				}
			}
		}
	}
	return 0;
}
```



------------

## 后言
本人赛时线段树写挂成 $10$ 分，没有看到这个 `Too large` 的作用，只是将其当做一个限制，这告诉我们要**好好读题**。

如果读清楚题，想到这个作用，这题就迎刃而解了，而且代码编写简单。（哭）

希望大家不要学我/bx


---

## 作者：E1_de5truct0r (赞：9)

## 思路

这道题只需要证明一个结论：长度大于 $2k+1$ 的序列，其最大子段乘积一定大于 $2^k$。

证明很显然，对于最劣的情况肯定是一段长度为 $k-1$ 的正数，一个负数，再一段长度为 $k-1$ 的正数，这个时候乘积至少是 $2^{k-1}$，如果再多一个数，无论它的位置、正负，一定可以构造出一种方案使得乘积至少是 $2^k$。

由于这道题答案 $>2^k$ 就不需要输出了，所以我们可以设置一个长度的阈值 $B=2 \times 30+2=62$，如果长度大于这个显然答案远远超出范围就没必要算了，直接输出 `Too large`。

而对于长度小于 $62$ 的，我们直接跑一个最大子段积就行了，即令 $dp_{i,0/1}$ 表示以 $i$ 结尾的，最大的正的乘积和 / 最小的负的乘积和，每次按 $a_i$ 的正负讨论即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int __int128
using namespace std;

namespace io{
	... // 省去了缺省源（太长了，200 多行）
}


const int N=(1ll<<30),INF=(1ll<<31)-1;

int dp[200005][2],a[200005],pre[200005];

signed main(){
	int n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	
	while(q--){
		int op=read(),l=read(),r=read();
		if(op==1){a[l]=r;continue;} // 直接单点修改
		
		if(r-l>=62){writes("Too large\n"); continue;} // 按阈值分治
		
		int ans=1; dp[0][0]=dp[0][1]=0;
		for(int i=l;i<=r;i++){
			int j=i-l+1;
			if(a[i]<0){
				dp[j][0]=dp[j-1][1]*a[i];
				dp[j][1]=min(dp[j-1][0]*a[i],a[i]);
			}else{
				dp[j][0]=max(dp[j-1][0]*a[i],a[i]);
				dp[j][1]=dp[j-1][1]*a[i];
			}
		}
		for(int i=l;i<=r;i++) ans=max(ans,dp[i-l+1][0]);
		if(ans>N) writes("Too large\n");
		else write(ans),writechar('\n');
	}
	return flush(),0;
}
```

---

## 作者：TensorFlow_js (赞：6)

### 0.题意简述

给定一个长为 $n$ 的整数序列 $a$，**其中所有数的绝对值均大于等于** $2$，需要支持单点修改和查询最大子区间乘积，如果答案大于 $2^{30}$ 则输出 `Too large` 即可。空区间的乘积定义为 $1$。

### 1.做法详解

不用脑子的线段树+平衡树做法。

可以发现，当 $[l,r]$ 的总乘积为正数，则最大子区间乘积就是这个总乘积；否则设这段区间的第一个负元素的位置为 $\textit{beg}$，最后一个为 $\textit{ed}$，则最大子区间乘积为 $\max\{\prod_{i=beg}^{r}a_i,\prod_{i=l}^{\textit{\textit{beg}}}a_i\}$，特别地，若这段区间只有一个元素且其为负，则最大子区间乘积为 $1$。

直接用线段树维护区间乘积，平衡树维护负数位置即可。

代码很好懂，不解释。

### 2.代码

```cpp
#include<bits/extc++.h>
using namespace std;
//快读快输部分（mmapreader,mmapwriter）已隐藏
class segtree {
protected:
    using vt = __int128;
    static constexpr vt maxsize = 800005, maxval = 1ll << 30;
    vt v[maxsize], n, cnt = 0;
    __gnu_pbds::tree<vt, __gnu_pbds::null_type> tr;//gnu 拓展库中的平衡树
    #define lc    (x << 1)
    #define rc    (x << 1 | 1)
    #define m     (l + (r - l >> 1))
    #define v(x)  (*(v + (x)))
    #define b1    l, m
    #define b2    m + 1, r
    inline bool pushup (vt x) {
        if ((v (lc) * v (rc) > maxval))v (x) = 0ll;
        else v (x) = v (lc) * v (rc);
        return true;
    }
    void build (vt l, vt r, vt x) {
        if (l == r)
            return (void)((v[x] = mmapreader::read<vt>()) < 0 ? tr.insert (++cnt), 0 : ++cnt);
        return build (b1, lc), build (b2, rc), (void)pushup (x);
    }
public:
    segtree (vt N = 0) {
    	n = N;
        build (1, n, 1);
        tr.insert (numeric_limits<vt>::min ( ));
        tr.insert (numeric_limits<vt>::max ( ));
    }
    vt getmul (vt a, vt b, vt l = 1, vt r = -1, vt x = 1) {
        if (!~r)r = n;
        if (l > b || r < a || l <= 0 || r > n)return 1ll;
        if (l >= a && r <= b)return v (x);
        vt ans = getmul (a, b, b1, lc) * getmul (a, b, b2, rc);
        return ans > maxval ? 0ll : ans;
    }
    bool change (vt a, vt y, vt l = 1, vt r = -1, vt x = 1) {
        if (!~r)r = n;
        if (l > a || r < a || l <= 0 || r > n)return false;
        if (l == r && r == a) {
            if (y > 0 && (*tr.lower_bound (a)) == a)tr.erase (a);
            if (y < 0 && (*tr.lower_bound (a)) != a)tr.insert (a);
            return v[x] = y;
        }
        return change (a, y, b1, lc), change (a, y, b2, rc), pushup (x);
    }
    vt ask (vt a, vt b) {
        vt ans = getmul (a, b);
        if (!ans)return 0;
        if (ans > 0)return ans;
        if (a == b)return 1;
        vt na = (*tr.lower_bound (a)) + 1, nb = (*(--tr.lower_bound (b + 1))) - 1;
        static vt X, Y;
        X = ask (na, b), Y = ask (a, nb);
        if (!X || !Y)return 0;
        return max(X, Y) > maxval ? 0 : max(X, Y);
    }
    #undef lc  
    #undef rc  
    #undef m   
    #undef v
    #undef b1  
    #undef b2  
};
signed main ( ) {
    mmapreader::prepare (stdin), mmapwriter::prepare (stdout);
    int n = mmapreader::read<int>(), m = mmapreader::read<int>(), op, x, y, ans;
    static segtree tr (n);
    while (m--)mmapreader::read (op, x, y), op - 1 ? ans = tr.ask (x, y),mmapwriter::writeln(ans > 0 && ans <= (1 << 30) ? to_string (ans) : "Too large"), true : tr.change (x, y);
    return 0;
}
```

### 3.优劣分析

优点：很容易扩展到没有“如果答案大于 $2^{30}$ 则输出 `Too large` 即可”这个条件时的情形。

缺点：很难写。

---

## 作者：JohnVictor (赞：4)

以下记 $M=2^{30}$。

#### Solution 1

由于定义了空区间的元素乘积为 $1$，我们只用考虑元素乘积为正整数的子区间。

考虑暴力，我们枚举询问到的区间的所有子区间，先判断乘积是否为正，如果为正则直接计算其中的元素乘积或者判断出大于 $M$。

如果任意时刻乘积的绝对值已经大于 $M$ 了，由于序列中都是非零整数，最后的乘积也是大于 $M$ 的，直接输出 `Too large` 即可；否则输出所有不是太大的乘积的最大值。

直接实现，复杂度为 $O(q(r-l)^3)$，期望通过数据点 $1\sim 6$。

#### Solution 2

继续分析一个区间的答案可能是什么样。

实际上，如果所有数的乘积非负，那么答案就是区间中所有数的乘积；否则设这个区间从左往右的第一个、最后一个负数的位置分别为 $x,y$。我们发现任意同时包含 $x,y$ 的区间乘积都是负数；而其他的区间一定是 $[l,y-1]$ 或者 $[x+1,r]$ 的子区间，并且这两个子区间的乘积是正数，我们只用分别计算即可。（或者判断大于 $M$）

暴力的实现上述做法，在绝对值大于 $M$ 时结束即可。时间复杂度 $O(q(r-l))$，期望通过数据点 $1\sim 10$。

#### Solution 3

在 $r-l \le 100$ 的时候使用 Solution 2 暴力。否则我们证明答案一定为 `Too large`。事实上，如果所有数的乘积非负，至少是 $2^{100}$；否则我们找到的两个区间 $[l,y-1]$ 和 $[x+1,r]$  一定有一个长度不小于 $50$，那么乘积的绝对值至少为 $2^{50}$，结合乘积非负知道答案为 `Too large`。

### 原版本

原版本允许 $a_i,k$ 的绝对值为 $1$。针对原版本有以下解法：

#### Solution 4

用数据结构维护 Solution 2 即可。我们使用两个 `set` 分别维护数列中负数的下标以及绝对值大于等于 $2$ 的数的下标。利用 `set` 中自带的 `lower_bound()` 函数可以在 $O(\log n)$ 的时间内找到上述 $x,y$。对于计算区间乘积，由于我们已经知道了正负性，只用计算大于等于 $2$ 的数的绝对值的乘积。在 `set` 上暴力往后跳，直到大于 $M$ 或者到 $r$ 为止，这里最多跳了 $O(\log M)$ 次，因此总复杂度为 $O((n+q)(\log n+\log M))$，期望通过所有数据点。

#### Solution 5

我们也可以用线段树。这个做法相较于上一个做法细节更少。每一个节点维护如下信息：区间乘积的符号；区间乘积的绝对值（如果不超过 $M$ 就记录真实值，否则记录 $M+1$）；区间内第一个和最后一个负数的位置。

以上信息容易将左右儿子合并。单点修改时一路 `pushup` 即可；区间查询时也很好利用维护的信息找到第一个，最后一个负数的位置，再用一般的处理方式计算区间乘积。总复杂度 $O(n+q\log n)$，期望通过所有数据点。

#### 实现细节

注意各种地方是否要 $+1,-1$；答案应该初始化为 $1$ 而不是 $0$ 或者 $-\infty$，因为这是空区间的答案。

---

## 作者：Fishmaster (赞：3)

### Solution

出题人给了一个非常良心的条件：$a$ 中所有数的绝对值都 $\ge 2$。

于是我们有一个非常重要的性质：由于所有数的绝对值都 $\ge 2$，对于询问 $2$ 询问区间 $[l,r]$ 的时候，当 $r - l + 1 > 61$ 时，显然应该输出 `Too large`。

为什么？因为当 $r - l + 1 = 61$ 时，有一组最坏情况：$30$ 个 $2$，一个 $-2$，$30$ 个 $2$。如果再添一个数，则肯定能找到乘积 $> 2^{30}$ 的区间。

于是对于剩下的情况，我们暴力模拟就可以了。

模拟时注意细节：

- 当 $l = r$（即区间长度为 $1$）且 $a_l$ 为负数时，把这个负数删掉，输出 $1$。
- 剩余情况看区间内负数个数，为偶数直接乘，为奇数则从两边找到第一个负数，然后把剩余部分相乘就可以了。
- **注意乘的时候要乘绝对值，否则可能会爆负数。**

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define inf 1<<30
using namespace std;
int n, q;
ll arr[200005];

int main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	while (q--) {
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1)
			arr[x] = y;
		else {
			if (x == y && arr[x] < 0)
				cout << 1 << endl;
			else {
				if (y - x + 1 > 61)
					cout << "Too large" << endl;
				else {
					int cnt = 0;
					for (int i = x; i <= y; i++)
						if (arr[i] < 0)
							cnt++;
					if (cnt % 2 == 0) {
						ll res = 1;
						for (int i = x; i <= y && res <= inf; i++)
							res *= abs(arr[i]);
						if (res > inf)
							cout << "Too large" << endl;
						else
							cout << res << endl;
					} else {
						int l = x, r = y;
						while (arr[l] > 0 && l <= y)
							l++;
						while (arr[r] > 0 && r >= x)
							r--;
						ll res1 = 1, res2 = 1;
						for (int i = l + 1; i <= y && res1 <= inf; i++)
							res1 *= abs(arr[i]);
						for (int i = x; i < r && res2 <= inf; i++)
							res2 *= abs(arr[i]);
						if (res1 > inf || res2 > inf)
							cout << "Too large" << endl;
						else
							cout << max(res1, res2) << endl;
					}
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：SegTree (赞：2)

$\text{Update 2022/10/04}$ 被讨论区的 $\text{Hack}$ 数据卡了，修改代码。

[题目传送门。](https://www.luogu.com.cn/problem/P8563)

作者分成了两个 `namespace`。`namespace subtask1` 是针对有负数的情况，而 `namespace subtask2` 是针对没有负数的情况。

## namespace subtask2（特殊性质 A）
因为全部为正数，所以最大的肯定是全部乘起来，如果这个过程中会超过 $2^{30}$，那么输出 `Too large` 否则输出乘积。


## namespace subtask1（不满足特殊性质 A）
枚举所有可能的区间开始点。

如果乘出超过 $2^{30}$ 的情况，输出 `Too large`；如果乘出小于 $-2^{30}$ 的情况，如果从剩下的数到区间结束没法使它变成正数则直接退出枚举循环枚举下一个左端点。每次计算都取一次 $\max$。**请注意答案可以是空区间，所以 `maxn` 初始值应设为 $1$。**

上面的做法原来能通过本题，但现在被卡了。

发现每个过程相当于设法往后找到负数，于是可以用 `vector` 维护所有负数所在位置，并在每次进行修改操作中维护。这个过程需要调用函数 `upper_bound`，故查找这个数的复杂度为 $\mathcal{O}(\log n)$。因为这个过程中只要乘到 $31$ 次就必然会不在 $[-2^{30},2^{30}]$ 这个区间内，所以不会超时。

## 完整代码
```cpp
#include<bits/stdc++.h>
int a[200005],opt[200005],l[200005],r[200005],n,q;
std::vector<int>v;
inline int read(){
    int x=0;
    short t=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            t=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+(ch-'0');
        ch=getchar();
    }
    return x*t;
}
const int MAXN=1<<30;
int choose=2;
void init(){
    n=read(),q=read();
    for(int i=1;i<=n;++i){
        a[i]=read();
        if(a[i]<0){
            choose=1;
            v.push_back(i);
        }
    }
    for(int i=1;i<=q;++i){
        opt[i]=read();
        l[i]=read();
        r[i]=read();
        if(r[i]<0)choose=1;
    }
}
namespace subtask1 {
    void solve(){
        for(int I=1;I<=q;++I){
            if(opt[I]==1){
                auto it=lower_bound(v.begin(),v.end(),l[I]);
                if(a[l[I]]<0){
                    v.erase(it);
                }
                if(r[I]<0){
                    v.insert(it,l[I]);
                }
                a[l[I]]=r[I];
            }
            else {
                bool f=1;
                long long maxn=1;
                for(int i=l[I];i<=r[I];++i){
                    long long mul=1;
                    for(int j=i;j<=r[I];++j){
                        mul=mul*a[j];
                        if(mul>MAXN){
                            f=0;
                            break;
                        }
                        if(mul<-MAXN){
                            short now=-1;
                            auto it=upper_bound(v.begin(),v.end(),j);
                            if(it==v.end())break;
                            if(*it>r[I])break;
                            f=0;
                            break;
                        }
                        maxn=std::max(maxn,mul);
                    }
                    if(!f)break;
                }
                if(!f)puts("Too large");
                else printf("%lld\n",maxn);
            }
        }
    }
};
namespace subtask2 {
    void solve(){
        for(int i=1;i<=q;++i){
            long long mul=1;
            bool f=1;
            if(opt[i]==1){
                a[l[i]]=r[i];
                continue;
            }
            for(int j=l[i];j<=r[i];++j){
                mul=mul*a[j];
                if(mul>MAXN){
                    f=0;
                    break;
                }
            }
            if(!f)puts("Too large");
            else printf("%lld\n",mul);
        }
    }
};
int main(){
    init();
    if(choose==2)subtask2::solve();
    else subtask1::solve();
}
```

---

## 作者：happybob (赞：1)

## 题意

给定序列，多次求区间最大子段积。

## 解法

考虑线段树。

每个区间维护前缀最大值和最小值，后缀最大值和最小值，`pushup` 时只有可能最大乘以最大或最小乘以最小（负数乘以负数）。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll __int128

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline ll read()
{
	ll op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << (ll)1) + (x << (ll)3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(ll x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, q;
ll a[N], nans = LLONG_MIN;
bool flag;

class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		ll lmaxn, rmaxn, mul, res;
		ll lminn, rminn, totalres;
		bool is_bigger;
	}tr[N << 2];
	Node merge(Node x, Node y)
	{
		if (x.l == -1) return y;
		if (y.l == -1) return x;
		Node z;
		z.mul = x.mul * y.mul;
		z.l = x.l, z.r = y.r;
		z.lmaxn = max({x.lmaxn, x.mul * y.lmaxn, x.mul * y.lminn, (ll)1, z.mul});
		z.rmaxn = max({(ll)1, y.rmaxn, y.mul * x.rmaxn, y.mul * x.rminn, z.mul});
		z.res = max({ x.res, y.res, x.rmaxn * y.lmaxn, z.mul, (ll)1 });
		z.lminn = min({x.lminn, x.mul * y.lminn, z.mul, (ll)1, x.mul * y.lmaxn});
		z.rminn = min({y.rminn, y.mul * x.rminn, z.mul, (ll)1, y.mul * x.rmaxn});
		z.totalres = max({x.totalres, y.totalres, (ll)1, z.res, x.rminn * y.lminn});
		if (z.totalres > (__int128)1 << 30)
		{
			z.is_bigger = 1;
		}
		else z.is_bigger = 0;
		z.is_bigger |= (x.is_bigger | y.is_bigger);
		return z;
	}
	void pushup(int u)
	{
		tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, a[l], a[l], a[l], a[l], a[l], a[l], a[l], 0 };
		tr[u].lmaxn = tr[u].rmaxn = tr[u].res = max(tr[u].res, (ll)1);
		tr[u].lminn = tr[u].rminn = min(tr[u].lminn, (ll)1);
		tr[u].totalres = max(tr[u].totalres, (ll)1);
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void update(int u, int p, ll x)
	{
		if (tr[u].l == tr[u].r)
		{
			tr[u].lmaxn = tr[u].rmaxn = tr[u].res = max(x, (ll)1);
			tr[u].lminn = tr[u].rminn = min(x, (ll)1);
			tr[u].totalres = max(x, (ll)1);
			tr[u].mul = x;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (p <= mid) update(u << 1, p, x);
		else update(u << 1 | 1, p, x);
		pushup(u);
	}
	Node query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) 
		{
			return tr[u];
		}
		int mid = tr[u].l + tr[u].r >> 1;
		Node ret;
		ret.l = -1;
		if (l <= mid) ret = query(u << 1, l, r);
		if (r > mid) ret = merge(ret, query(u << 1 | 1, l, r));
		return ret;
	}
}t;

int main()
{
	//freopen("C:\\Users\\60215\\Downloads\\T1ex1.in", "r", stdin);
	//freopen("C:\\Users\\60215\\Downloads\\tt.out", "w", stdout);
	// freopen("*.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) a[i] = read();
	t.build(1, 1, n);
	while (q--)
	{
		int opt;
		scanf("%d", &opt);
		if (opt == 1)
		{
			int x;
			scanf("%d", &x);
			ll y = read();
			t.update(1, x, y);
		}
		else
		{
			int l, r;
			scanf("%d%d", &l, &r);
			SegmentTree::Node ans = t.query(1, l, r);
			if (ans.is_bigger) printf("Too large\n");
			else
			{
				ll res = max((ll)1, ans.totalres);
				write(res);
				printf("\n");
			}
		}
	}
	return 0;
}
```


---

## 作者：Shameimaru_Aya (赞：1)

正解就是线段树嘛（确信）。

所有数的绝对值都大于 $2$，当区间内负数的数量是个**偶数**时，答案是整个区间的乘积。

如果数量是个奇数，那么需要**舍去一个负数**。又因为子区间越大越好，所以只可能舍去最左边或者最右边的负数。

于是用线段树维护区间的乘积、负数的数量、最左和最右负数的位置就好了。

还有就是处理 ```Too large``` 的细节，如果一个子区间的乘积大于 $2^{30}$ 或者小于 $-2^{30}$，大胆地把它标记上。只要答案包含这一段就是 ```Too large``` 呐。

（比赛时没判断小于 $-2^{30}$ 挂了 $60$ 分。

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
const int maxn=2e5+50,INF=pow(2,30);
#define ll long long
int n,q;
ll a[maxn*4],tr[maxn*4];
ll tw[maxn*4];
ll lw[maxn*4],rw[maxn*4];
inline void pushup(int k)
{
	tw[k]=tw[k*2]+tw[k*2+1];
	lw[k]=min(lw[k*2],lw[k*2+1]);rw[k]=max(rw[k*2],rw[k*2+1]);
	tr[k]=tr[k*2]*tr[k*2+1];
	if(tr[k]>INF||tr[k]<-INF)tr[k]=INF+114;
}
inline void build(int k,int l,int r)
{
	if(l==r)
	{
		tr[k]=(a[l]>INF||a[l]<-INF)?INF+114:a[l];
		tw[k]=(a[l]<0)?1:0;
		lw[k]=(a[l]<0)?l:0x7fffffff;
		rw[k]=(a[l]<0)?l:-1;
		return;
	}
	int mid=(l+r)>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	pushup(k);
}
inline void update(int k,int l,int r,int x,int v)
{
	if(r<x||l>x)return;
	if(l==r&&l==x)
	{
		tr[k]=(v>INF||v<-INF)?INF+114:v;
		tw[k]=(v<0)?1:0;
		lw[k]=(v<0)?x:0x7fffffff;
		rw[k]=(v<0)?x:-1;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(k*2,l,mid,x,v);
	if(x>mid)update(k*2+1,mid+1,r,x,v);
	pushup(k);
}
inline ll queryT(int k,int l,int r,int x,int y)
{
	if(r<x||l>y)return 0;
	if(x<=l&&r<=y)return tw[k];
	int mid=(l+r)>>1,ans=0;
	if(x<=mid)ans+=queryT(k*2,l,mid,x,y);
	if(y>mid)ans+=queryT(k*2+1,mid+1,r,x,y);
	return ans;
}
inline ll queryL(int k,int l,int r,int x,int y)
{
	if(r<x||l>y)return 0x7fffffff;
	if(x<=l&&r<=y)return lw[k];
	int mid=(l+r)>>1;
	ll ans=0x7fffffff;
	if(x<=mid)ans=min(ans,queryL(k*2,l,mid,x,y));
	if(y>mid)ans=min(ans,queryL(k*2+1,mid+1,r,x,y));
	return ans;
}
inline ll queryR(int k,int l,int r,int x,int y)
{
	if(r<x||l>y)return -1;
	if(x<=l&&r<=y)return rw[k];
	int mid=(l+r)>>1;
	ll ans=-1;
	if(x<=mid)ans=max(ans,queryR(k*2,l,mid,x,y));
	if(y>mid)ans=max(ans,queryR(k*2+1,mid+1,r,x,y));
	return ans;
}
inline ll queryS(int k,int l,int r,int x,int y)
{
	if(r<x||l>y)return 1ll;
	if(x<=l&&r<=y)return tr[k];
	int mid=(l+r)>>1;
	ll ans=1ll;
	ans*=queryS(k*2,l,mid,x,y);
	if(ans>INF||ans<-INF)return INF+114;
	ans*=queryS(k*2+1,mid+1,r,x,y);
	if(ans>INF||ans<-INF)return INF+114;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=q;i++)
	{
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==1)update(1,1,n,l,r);
		else
		{
			if(queryT(1,1,n,l,r)%2==0)
			{
				ll ans=queryS(1,1,n,l,r);
				if(ans<=INF&&ans>=-INF)cout<<ans<<"\n";
				else cout<<"Too large\n";
			}
			else
			{
				int L=queryL(1,1,n,l,r),R=queryR(1,1,n,l,r);
				ll ans=max(queryS(1,1,n,L+1,r),queryS(1,1,n,l,R-1));
				if(ans<=INF&&ans>=-INF)cout<<ans<<"\n";
				else cout<<"Too large\n";
			}
		}

}
```


---

## 作者：251Sec (赞：1)

~~T1 写了一个多小时 T2写了个 $O(n^3)$ 后面都不会写这直接耻辱退役得了。~~

据某绿鸟管理说这题可以暴力……我感觉我的时间被浪费了。

但是我觉得时间也不能白白浪费，所以我们来考虑一下这题如果 $\exists a_i \in \{1, -1\}$ 怎么用优雅的方式做出来。

看到存在修改操作和区间查询操作，显然我们可以使用线段树维护区间信息。

想到线段树维护区间最大子段和的思想，对于线段树的每个节点，可以考虑维护从左边开始的区间和从右边开始的区间的信息。

考虑到乘法的性质，我们可以分开维护乘积为正数和负数的绝对值最大值。

我们不难发现，令某个线段树的节点（不妨设该节点在数组中的下标为 $i$）中有 $f_i = \prod\limits_{j=l}^r a_j$，那么在这个区间 $[l, r]$ 内，**不存在一个连续区间的乘积的绝对值大于 $f_i$。**

因此，对于与 $f_i$ 同号的情况，我们无需记录左右区间的信息，因为整个区间的乘积就是最大的。

在维护与 $f_i$ 异号的情况时，我们就需要分开记录左右区间的信息，用类似于维护最大子段和的思想来完成。

不妨设线段树维护的区间 $[l, r]$ 中从左边开始的一个区间 $[l, r']$ 中，与 $f_i$ 异号的绝对值最大的乘积为 $g_i$。（这话好拗口）从右边开始的一个区间 $[l',r]$ 中，与 $f_i$ 异号的绝对值最大的乘积为 $h_i$。

可以证明，该区间内最大的连续区间的乘积为 $\max\{1, f_i, g_i, h_i\}$。

大部分操作都比较常规，唯一一个比较困难的操作在于合并两个区间的信息。（在 Pushup 和 Query 操作中都有用到）假设我们要把区间 $j$ 和 $k$ 的信息合并到 $i$。

对于 $f_i$，显然直接令其为 $f_j \times f_k$ 即可。

对于 $g_i$，由于要求它与 $f_i$ 异号，所以需要分类讨论。我们发现 $f_j \times g_k$ 必定与 $f_i$ 异号。所以若 $f_i$ 与 $f_j$ 同号，则 $f_i$ 取 $g_j$ 与 $f_j \times g_k$ 中绝对值较大的一个。若 $f_i$ 与 $f_j$ 异号，则 $f_i$ 取 $f_j$ 与 $f_j \times g_k$ 中绝对值较大的一个。（$f_j \times g_k$ 的绝对值不一定大于 $f_j$ 的绝对值，因为在线段树的叶子结点可能出现 $g_k=0$ 的情况）

对于 $h_i$，方法类似，这里不再赘述。

最后敲一下你祖传的线段树即可。因为是单点修改所以懒标记也不用打了，太棒了！（？

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1 << 30;
int n, q;
class IO {
    template <class T>
    void write(T a) {
        if (a > 9)
            write(a / 10);
        putchar(a % 10 + '0');
    }
public:
    template <class T>
    IO operator<<(T a) {
        if (a < 0) {
            putchar('-');
            a = -a;
        }
        write(a);
        return *this;
    }
    IO operator<<(char a) {
        putchar(a);
        return *this;
    }
    template <class T>
    IO operator>>(T &a) {
        int sign = 1;
        a = 0;
        char c = getchar();
        while (c < '0' || c > '9') {
            if (c == '-') {
                sign = -1;
            }
            c = getchar();
        }
        while (c >= '0' && c <= '9') {
            a = (a << 1) + (a << 3) + (c ^ 48);
            c = getchar();
        }
        a *= sign;
        return *this;
    }
} io;
struct Node {
    ll f, g, h;
    ll getval() {
        return max(1ll, max(f, max(g, h)));
    }
} tr[800005];
ll a[200005];
void Pushup(int p) {
    tr[p].f = tr[p << 1].f * tr[p << 1 | 1].f;
    if (abs(tr[p].f) > inf) tr[p].f = tr[p].f > 0 ? inf + 1 : -inf - 1;

    if (tr[p].f * tr[p << 1].f < 0) tr[p].g = tr[p << 1].f;
    else tr[p].g = tr[p << 1].g;
    if (abs(tr[p].g) < abs(tr[p << 1].f * tr[p << 1 | 1].g)) tr[p].g = tr[p << 1].f * tr[p << 1 | 1].g;

    if (tr[p].f * tr[p << 1 | 1].f < 0) tr[p].h = tr[p << 1 | 1].f;
    else tr[p].h = tr[p << 1 | 1].h;
    if (abs(tr[p].h) < abs(tr[p << 1 | 1].f * tr[p << 1].h)) tr[p].h = tr[p << 1 | 1].f * tr[p << 1].h;

    if (abs(tr[p].g) > inf) tr[p].g = tr[p].g > 0 ? inf + 1 : -inf - 1;
    if (abs(tr[p].h) > inf) tr[p].h = tr[p].h > 0 ? inf + 1 : -inf - 1;
}
void Build(int l, int r, int p) {
    if (l == r) {
        tr[p].f = a[l];
        tr[p].g = tr[p].h = 0;
        return;
    }
    else {
        int mid = l + r >> 1;
        Build(l, mid, p << 1);
        Build(mid + 1, r, p << 1 | 1);
        Pushup(p);
    }
}
void Modify(int l, int cl, int cr, int p, ll w) {
    if (cl == cr) {
        tr[p].f = w;
        tr[p].g = tr[p].h = 0;
    }
    else {
        int mid = cl + cr >> 1;
        if (l <= mid) {
            Modify(l, cl, mid, p << 1, w);
        }
        else {
            Modify(l, mid + 1, cr, p << 1 | 1, w);
        }
        Pushup(p);
    }
}
Node Query(int l, int r, int cl, int cr, int p) {
    if (cl >= l && cr <= r) {
        return tr[p];
    }
    int mid = cl + cr >> 1;
    Node ans, a, b;
    if (r <= mid) {
        ans = Query(l, r, cl, mid, p << 1);
    }
    else if (l > mid) {
        ans = Query(l, r, mid + 1, cr, p << 1 | 1);
    }
    else {
        a = Query(l, r, cl, mid, p << 1);
        b = Query(l, r, mid + 1, cr, p << 1 | 1);
        ans.f = a.f * b.f;
        if (abs(ans.f) > inf) ans.f = ans.f > 0 ? inf + 1 : -inf - 1;
        if (ans.f * a.f < 0) ans.g = a.f;
        else ans.g = a.g;
        if (abs(ans.g) < abs(a.f * b.g)) ans.g = a.f * b.g;

        if (ans.f * b.f < 0) ans.h = b.f;
        else ans.h = b.h;
        if (abs(ans.h) < abs(b.f * a.h)) ans.h = b.f * a.h;

        if (abs(ans.g) > inf) ans.g = ans.g > 0 ? inf + 1 : -inf - 1;
        if (abs(ans.h) > inf) ans.h = ans.h > 0 ? inf + 1 : -inf - 1;
    }
    return ans;
}
int main() {
    io >> n >> q;
    for (int i = 1; i <= n; i++) io >> a[i];
    Build(1, n, 1);
    while (q--) {
        int op, x, y;
        io >> op >> x >> y;
        if (op == 1) {
            Modify(x, 1, n, 1, y);
        }
        else {
            Node res = Query(x, y, 1, n, 1);
            if (res.getval() > inf) puts("Too large");
            else printf("%lld\n", res.getval());
        }
    }
    return 0;
}
```

---

