# Two Hundred Twenty One (hard version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that the hard version does require you to output the numbers of the rods to be removed. You can make hacks only if all versions of the problem are solved.

Stitch likes experimenting with different machines with his friend Sparky. Today they built another machine.

The main element of this machine are $ n $ rods arranged along one straight line and numbered from $ 1 $ to $ n $ inclusive. Each of these rods must carry an electric charge quantitatively equal to either $ 1 $ or $ -1 $ (otherwise the machine will not work). Another condition for this machine to work is that the sign-variable sum of the charge on all rods must be zero.

More formally, the rods can be represented as an array of $ n $ numbers characterizing the charge: either $ 1 $ or $ -1 $ . Then the condition must hold: $ a_1 - a_2 + a_3 - a_4 + \ldots = 0 $ , or $ \sum\limits_{i=1}^n (-1)^{i-1} \cdot a_i = 0 $ .

Sparky charged all $ n $ rods with an electric current, but unfortunately it happened that the rods were not charged correctly (the sign-variable sum of the charge is not zero). The friends decided to leave only some of the rods in the machine. Sparky has $ q $ questions. In the $ i $ th question Sparky asks: if the machine consisted only of rods with numbers $ l_i $ to $ r_i $ inclusive, what minimal number of rods could be removed from the machine so that the sign-variable sum of charges on the remaining ones would be zero? Also Sparky wants to know the numbers of these rods. Perhaps the friends got something wrong, and the sign-variable sum is already zero. In that case, you don't have to remove the rods at all.

If the number of rods is zero, we will assume that the sign-variable sum of charges is zero, that is, we can always remove all rods.

Help your friends and answer all of Sparky's questions!

## 说明/提示

In the first test case for the first query you can remove the rods numbered $ 5 $ and $ 8 $ , then the following set of rods will remain: +--+--++-++-. It is easy to see that here the sign-variable sum is zero.

In the second test case:

- For the first query, we can remove the rods numbered $ 1 $ and $ 11 $ , then the following set of rods will remain: --++---++---. It is easy to see that here the sign-variable sum is zero.
- For the second query we can remove the rod numbered $ 9 $ , then the following set of rods will remain: ---++-. It is easy to see that here the variable sum is zero.
- For the third query we can not remove the rods at all.

## 样例 #1

### 输入

```
3
14 1
+--++---++-++-
1 14
14 3
+--++---+++---
1 14
6 12
3 10
4 10
+-+-
1 1
1 2
1 3
1 4
2 2
2 3
2 4
3 3
3 4
4 4```

### 输出

```
2
5 8
2
1 11
1
9
0
1
1
2
1 2
1
2
2
1 3
1
2
2
2 3
1
3
1
3
2
3 4
1
4```

# 题解

## 作者：遮云壑 (赞：6)

# Description

一个 1、-1 交错的串，每次询问一段区间，使其奇数位乘上 1 ，偶数位乘上 -1 ，问最少删掉多少数字能使这一段和为 0 。输出方案。

[传送门](https://www.luogu.com.cn/problem/CF1562D2)

# Solution

给了那么多的样例，我们可以大胆猜测，删掉的数字的个数只可能是 0，1，2 。

然后想想为什么。

由于奇数位乘 1 ，偶数位乘 -1 ，反正最后要的和是 0 ，你奇偶弄反了问题也不大，所以我们在预处理前缀和的时候直接给偶数位乘上 -1.

- **删 0 个数**  这很显然，一串的和为0就行了。

- **删 1 个数**  当串的和为奇数的时候。
	
    首先，串什么时候和会是奇数。我们发现，当两位相邻，它们对总和的贡献一定是偶数（1，1或-1，-1，或1，-1），那么若和为奇数，当且仅当串长度为奇数。

	**当我们删掉一个数，后面数的符号都会改变，所以后面那一段的和相当于乘上了 -1 ，概括说，我们找到一个  前缀和的值的一半  的位置删掉就行了。**
    
	设串的和为 $tmp$ ，我们找到在串里第一个出现前缀和为 $\left \lceil \frac{tmp}{2}  \right \rceil $ 的位置删掉。
    
    - 若整串和为正，第一个出现 $\left \lceil \frac{tmp}{2}  \right \rceil $ 的位置一定是 1 ，（如果是 -1 肯定是从前面减过来，那么 $\left \lceil \frac{tmp}{2}  \right \rceil $ 一定出现过），删掉之后前后两段的和都是 $\left \lfloor \frac{tmp}{2}  \right \rfloor $ ，一正一负，加起来刚好是 0 。
    - 若整串和为负，第一个出现 $\left \lceil \frac{tmp}{2}  \right \rceil $ 的位置一定是 -1 ，一样的道理，前后两段 $\left \lfloor \frac{tmp}{2}  \right \rfloor $ 一正一负，加起来为 0 。
    
- **删 2 个数** 当串的和为偶数的时候。

	和为偶数，你把最后一个数删掉不就是奇数了，然后跟上面是一样的方法。
    
    在这种情况删一个数，整串的和一定是奇数，（为什么是奇数，看上面）不可能为 0 ，所以删 2 个数一定是最优方案。
    
# Code

关于找到第一个 $\left \lceil \frac{tmp}{2}  \right \rceil $ 的位置，我们可以在算前缀和的时候把当前位置扔进当前前缀和的值的一个 vector （这里看代码去吧，不大好讲），询问的时候二分即可。

```cpp
#include<bits/stdc++.h>
#define N 300010
using namespace std;
inline void read(int& x)
{
	x=0;int y=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x=x*y;
}
int t,n,q;
char s[N];
int sum[N];
int main(){
	read(t);
	for(int heq=1;heq<=t;heq++)
	{
		read(n),read(q);
		vector<int> pos[N<<1];
		scanf("%s",s+1);
		pos[n].push_back(0); 
		sum[0]=n;
		for(int i=1;i<=n;i++)
		{
			if(i&1)
			{
				if(s[i]=='+')sum[i]=sum[i-1]+1;
				else sum[i]=sum[i-1]-1;
				pos[sum[i]].push_back(i);
			}
			else 
			{
				if(s[i]=='+')sum[i]=sum[i-1]-1;
				else sum[i]=sum[i-1]+1;
				pos[sum[i]].push_back(i);
			}
		}
		for(int i=1,l,r;i<=q;i++)
		{
			read(l),read(r);
			int tmp=sum[r]-sum[l-1];
			if(!tmp)
			{
				printf("0\n");
				continue;
			}
			if(abs(tmp)&1)
			{
				printf("1\n");
				int val;
				if(tmp>0)val=sum[l-1]+tmp/2+1;
				if(tmp<0)val=sum[l-1]+tmp/2-1;
				printf("%d\n",*lower_bound(pos[val].begin(),pos[val].end(),l));
			}
			if(abs(tmp)%2==0)
			{
				printf("2\n");
				int val;
				tmp=sum[r-1]-sum[l-1];
				if(tmp>0)val=sum[l-1]+tmp/2+1;
				if(tmp<0)val=sum[l-1]+tmp/2-1;
				printf("%d %d\n",*lower_bound(pos[val].begin(),pos[val].end(),l),r);
			}
		}
	}
	return 0;
}
```

# Conclusion

- 这种结论题要多玩数据，多看多试，敢想敢猜。

- 对于位置乘 1，-1 交错的题目删掉数后，后面一段的和相当于乘 -1 ，要敏感。

---

## 作者：pufanyi (赞：3)

先考虑没有多组询问。

窝萌首先发现一个性质，那就是如果有两个连续的相同字符，那么这两个字符对答案无贡献，我们可以直接删掉。那我们一次删掉之后，最后得到的序列只能是正负交替的了。于是我们只要考虑此种情况即可。我们发现如果删完的序列长度为奇数的话，我们只要删除最中间那个数就可以了。我们考虑偶数，如果长度已经为 $0$，那显然就不用删除了，如果不为 $0$ 的话，考虑到们此相同字符消除一定是两个两个删的，所以至少要删两个数，有考虑到如果随便删一个数，那么序列长度就变成奇数了，所以我们只需要删两个数即可。

于是我们发现，如果是询问系列长度为奇数，那答案最多是 $1$，如果是偶数，我们可以维护前缀和 $S_i=\sum_{j=1}^i(-1)^{j-1}a_j$，如果 $S_r-S_{l-1}$ 是 $0$，那答案就是 $0$，否则是 $2$。

这样 D1 就做完了。

我们考虑 D2，我们先考虑奇数的情况，我们假设要删掉的数是第 $k$ 个，那我们有 $\sum_{i=l}^{k - 1}(-1)^{i-1}a_{i}+(-1)\cdot\sum_{i=k+1}^r(-1)^{i-1}a_i=0$ 也即 $S_{k-1}-S_{l-1}=S_{r}-S_{k}$ 也即 $S_{k-1}+S_k=S_{l-1}+S_r$，于是我们对每个 $S_{k-1}+S_k$ 相同的开个 `set`，之后对每组询问 $\left<l,r\right>$，我们只要在所有 $S_{k-1}+S_k=S_{l-1}+S_r$ 数中 `lower_bound` 出一个在 $[l,r]$ 中的答案即可。

长度为偶数就直接随便删掉最左边或是最右边的数，然后按照奇数的方法做即可。

```cpp
const int maxn = 300005;

int qzh[maxn];
char s[maxn];

void solve() {
  int n, q;
  scanf("%d%d%s", &n, &q, s + 1);
  std::map<int, std::set<int>> mp;
  for (int i = 1; i <= n; ++i) {
    qzh[i] = qzh[i - 1] + (((i & 1) == (s[i] == '+')) ? 1 : -1);
    mp[qzh[i - 1] + qzh[i]].insert(i);
  }
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (qzh[r] - qzh[l - 1]) {
      if ((r - l) & 1) {
        puts("2");
        writesp(r);
        r--;
      } else {
        puts("1");
      }
      writeln(*mp[qzh[l - 1] + qzh[r]].lower_bound(l));
    } else {
      puts("0");
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
```

---

## 作者：yy1695651 (赞：1)

## 题意

给出一个长度为 $N$ 的字符串 $S$ 和 $Q$ 次询问，每次询问一个区间 $[l_i, r_i]$。

对于数列 $a_1, a_2, \ldots, a_n$，定义“不同符号和”(sign-variable)：

$s(\{a_n\}) = a_1-a_2+a_3-a_4+\cdots + (-1)^{n-1}\cdot a_n= \sum_{i=1}^n(-1)^{i-1}\cdot a_i$

现在数列 $a_1, a_2, \ldots, a_n$ 只有 $+1$ 和 $-1$ 构成，通过只含有正负号的字符串 $S$ 给出
如果 $a_i=1\Rightarrow S_i=\texttt{+}$，$a_i=-1\Rightarrow S_i=\texttt{-}$

每次询问给出区间 $[l_i, r_i]$，设字符串 $T = S_{l_i}S_{l_i+1}\cdots S_{r_i}$，求至少要从 $T$ 中删除多少个字符才能使得 $s(T) = 0$，并给出每次删除的字符位置。（第一个问题是D1所要求的，第二个问题是D2所要求的）。

数据范围：$1\leqslant N,Q\leqslant 3\times10^5$

## 思路

方法参考了cf官方题解。

我们先不考虑 $S$ 的子串问题，先考虑整个 $S$ 串。

设 $s(l, r) = \sum_{i=l}^r(-1)^{i-1}a_i$，表示 $s(S)$ 中 $[l, r]$ 这一段的不同符号和。

设 $f(i)$ 为去掉 $S$ 串中第 $i$ 个字符后变为 $S'$，整个 $S'$ 的不同符号和，即 $f(i)=s(S')$。

> 命题1：$|f(i)-f(i+1)| = 0 \text{或} 2$

**证明：**

不难发现：
$$
\begin{aligned}
&f(i)= s(1, i-1) - s(i+1, n)\\
&f(i+1)=s(1,i)-s(i+2, n)\\
\Rightarrow & |f(i)-f(i+1)|=|s(i, i)+s(i+1, i+1)|=|a_i-a_{i+1}|
\end{aligned}
$$
则：
- 当 $a_i=a_{i+1}$ 时，$|f(i)-f(i+1)|=0$。

- 当 $a_i\neq a_{i+1}$ 时，$|f(i)-f(i+1)| = 2$。

**QED**

下面这个结论不难证明：

> 命题2：$|S|$ 与 $s(S)$ 同奇偶性，也就是字符串长度和字符串的不同符号和的奇偶性相同。

因为 $+1$ 和 $-1$ 之和会发生抵消，抵消以后字符总数 $-2$ 不影响奇偶性，所以最终的不同符号和奇偶性与开始时的字符总长奇偶性相同。

所以，如果 $s(S) = 0$ 则一定有 $|S|$ 为偶数。

> 命题3：当 $s(1,n)\neq 0$ 时，$f(1)\cdot f(n) \leqslant 0$。

**证明：**

命题等价于证明 $f(1)$ 和 $f(n)$ 异号，或者至少有一个为 $0$。

$$
\begin{aligned}
&f(1)=-s(2, n)=a_1-s(1,n)\\
&f(n)=s(1, n-1)=s(1, n)-a_n\\
\end{aligned}
$$

由于 $|s(1, n)| \geqslant 1$，所以 $f(1)$ 和 $f(n)$ 的符号只能取决于 $s(1,n)$ 的符号，$a_1, a_n$ 对它们的影响太小，而 $s(1, n)$ 在 $f(1),f(n)$ 中的符号正好是一正一负，所以 $f(1),f(n)$ 只能异号，或者至少一个为 $0$。

**QED**

下面给出**删除方法**：

设 $n=|S|$ 为奇数，则 $f(i)$ 为偶数，因为它从 $S$ 中删除了一个字符。

又通过**命题1**知，相邻的 $f(i), f(i+1)$ 之间差值为 $0$ 或 $2$，由**命题3**知，$f(1), f(n)$ 异号，则一定存在 $k$，使得 $f(k)=0$，可以通过反证法证明。（类似于连续函数的零点存在定理）

则说明，对于长度为奇数的串，我们一定可以找到 $f(k)=0$，即将 $a_k$ 从 $S$ 删除即可满足题意。

如果长度为偶数的串，可以先删除 $a_n$ 使得它的长度变为奇数且 $s(1, n-1)$ 不会发生变化，然后再按照奇数的删除方法删除。

综上，最大的删除字符个数不会超过2个。

拓展到任意 $S$ 的子串 $T$ 方法很简单，只需要求出 $s(T)$ 即可，所以可以通过维护函数 $s$ 的前缀和完成。

于是对于长度为 $n$ 的字符串 $S$：

- $s(S) = 0$ 输出 $0$。

- $n$ 为奇数，输出 $1$。

- $n$ 为偶数，输出 $2$。

时间复杂度 $O(N)$。

下面给出 D1(easy version) 的代码：

```c++
#include <bits/stdc++.h>
#define vi vector<int>
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		string s;
		cin >> n >> m >> s;
		vi sum(n+1);
		for (int i = 1; i <= n; i++) {
			sum[i] = sum[i-1] + (s[i-1] == '+' ? 1 : -1) * (i % 2 == 1 ? 1 : -1);
		}
		while (m--) {
			int l, r;
			cin >> l >> r;
			if (sum[r] - sum[l-1] == 0) cout << 0 << '\n';
			else if ((r - l + 1) % 2 == 1) cout << 1 << '\n';
			else cout << 2 << '\n';
		}
	}
	return 0;
}
```

对于 D2 (hard version) 只需要求出每次奇数长度时删除的位置 $k$ 即可。

我们知道计算函数零点，可以通过二分完成（判断当前二分中点的函数值和两个端点的函数值是否异号），所以直接二分零点即可。

时间复杂度 $O(N\log N)$。

```c++
#include <bits/stdc++.h>
#define vi vector<int>
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		string s;
		cin >> n >> m >> s;
		vi sum(n+1);
		for (int i = 1; i <= n; i++) {
			sum[i] = sum[i-1] + (s[i-1] == '+' ? 1 : -1) * (i % 2 == 1 ? 1 : -1);
		}
		while (m--) {
			int l, r;
			cin >> l >> r;
			if (sum[r] - sum[l-1] == 0) cout << 0 << '\n';
			else {
				if ((r - l + 1) % 2 == 0) {
					cout << 2 << '\n' << r << ' ';
					r--;
				}
				else cout << 1 << '\n';
				int L = l, R = r;
				while (l <= r) {
					int mid = (l + r) >> 1, x = mid;
					if ((sum[x-1] - sum[L-1] - sum[R] + sum[x]) * (-sum[R] +sum[L]) <= 0) r = mid - 1;
					else l = mid + 1;
				}
				cout << l << '\n';
			}
		}
	}
	return 0;
}
```

安利下本蒟蒻的 [blog](https://wty-yy.github.io/posts/3451/)


---

## 作者：Echidna (赞：1)

[更好的阅读体验](https://oieraln.blog.luogu.org/CF741Div2)

## 题意简述：

给你一个长度为 $n$ 的 $\text{1/-1}$ 序列 $a$ 和 $q$ 个询问，每次询问给你一条线段 $[l,r]$ ，然后让你删除线段 $[l,r]$ 中的几个数，并且要求你删除完成之后把剩下的线段的偶数位置取反之后加和为 $0$ 。

请问最少的删除次数是多少？并且请输出一组可行的方案。

-----------------

有些大佬说这题需要主席树才能做，我当场 `/kk` ……~~（虽然也会）~~

不过那个大佬想错了，因为我用 `vector` 加二分过了 ~~，还能玩一手常数和码量压制，美滋滋~~。

## 题目分析：

建议先阅读[弱化版的题解](https://oieraln.blog.luogu.org/solution-cf1562d1)。~~（实际上是懒得复制一遍定义）~~

如果您继续往下阅读，那么我默认您知道我所定义的符号的含义。

----------------

还是接着那个套路。

对于一个询问 $[l,r]$ ，我们需要找到一个 $x \in [l,r]$ 并且有 $f(l,x-1)=f(x+1,r)$ 。

于是我们差分一下：

$$
\begin{aligned}
f(l,x-1)&=f(x+1,r)\\
f(1,x-1)-f(1,l-1)&=f(x+1,n)-f(r+1,n)\\
f(1,x-1)-f(x+1,n)&=f(1,l-1)-f(r+1,n)\\
g(x)&=f(1,l-1)-f(r+1,n)
\end{aligned}
$$

那我们就预先处理一下 $g(x)$ ，并且对于 $g(x)$ 的每一个取值都记录对应的自变量（不止一个），最后查询的时候二分答案就能找到一个 $x\in [l,r]$ 并且 $g(x)=f(1,l-1)-f(r+1,n)$ 的 $x$ 了。

另外，这题**稍微**卡常，如果您在第三个点 T 掉了那开个快读大概就可以过了。（而且跑得飞快）

时间复杂度：$O(q \log n)$

$\text{Code:}$

```cpp
int a[N],b[N];
int qzh[N],hzh[N];
int n,q;
vector<int> vec[N];
void solve(){
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        char c=readchar();
        a[i]=(c=='+')?+1:-1;
        b[i]=(i%2==0)?-a[i]:a[i];
        qzh[i]=qzh[i-1]+b[i];
    }
    hzh[n+1]=0;
    for(int i=n;i>=1;i--)
        hzh[i]=hzh[i+1]+b[i];
    for(int i=1;i<=n;i++)
        vec[qzh[i-1]-hzh[i+1]+2*n].push_back(i);
    for(int l,r,i=1;i<=q;i++){
        l=read(),r=read();
        vector<int> ans;
        if((r-l+1)%2==0)
            if(qzh[l-1]==qzh[r]){
                printf("0\n");
                continue;
            }else {
                ans.push_back(r);
                r--;
            }
        vector<int>& v=vec[qzh[l-1]-hzh[r+1]+2*n];
        ans.push_back(v[lower_bound(v.begin(),v.end(),l)-v.begin()]);
        printf("%d\n",ans.size());
        for(int i=0;i<ans.size();i++)
            printf("%d ",ans[i]);
        printf("\n");
        ans.clear();
    }
    for(int i=0;i<=4*n;i++)
        vec[i].clear();
}
```

## 关于 $\color{orange}\text{Wind\_Eagle}$ 在最后提出的小问题

如果以线性时间复杂度来做出此题？

我们考虑一下我们转化出来的问题：给定 $l,r,k$ ，找到一个 $x\in[l,r]$ 并且 $g(x)=k$ ，保证有解。

我们首先把 $k$ 分开来做，把询问按照 $k$ 分成不同组的时间复杂度为 $O(q)$ 。

然后，对于每一组，其实就变成了另外一个问题：告诉你数轴上某些点是特殊点，给你 $n$ 条线段，让你对于每一条线段举出一个特殊点的例子，要求这个特殊点在这条线段上。

我们可以考虑把线段按照左端点从大到小的方向排序。因为这里是正整数值域，并且左端点的大小和 $n$ 同级，所以直接 $O(n)$ 桶拍即可。

于是我们从右往左扫，同时记录上一次经过的特殊点。这里有个非常有趣的事情，就是线段的右端点没有意义了，因为保证有解，所以上一次经过的特殊点一定在右端点之内。

于是我们就可以实现一个 $O(n+q)$ 的算法了。但是因为$\mathop{\text{细节稍微有点多}}\limits^{\text{这人懒得要死}}$ ，就不写对应的代码了。

---

## 作者：xuanxuan001 (赞：1)

这次我的解法和官方解法不一样，所以就发了篇题解。

正文
-
首先，将读入的字符串转换为由 $\pm 1$ 组成的数组并将所有偶数位的数去相反数。把这个数组记为 $a$。一个区间的 sign-variable sum 的绝对值就是 $a$ 的对应区间和的绝对值。这足够我们判定是否为 0 了。为了求区间和，再记一个前缀和 $b$。

下面处理询问。对于长度为偶数的，就先把 $l$ 删去，长度变成奇数。

下面讨论奇数情况：考虑如果删除了位置 $p$ 的数，那么 $p$ 往后的数对这个 sign-variable sum 的贡献会取相反数，所以答案为
$$sum_{l,p-1} - sum_{p+1,r}$$

转换成前缀和的形式就是：

$$b_r - b_p - b_{p-1} + b_{l-1}$$

再化简一下并且加上对应值应该为 0 这个条件：

$$b_{l-1} + b_r - b_{p-1} + b_p = 0$$

将和 $p$ 有关的数移到一边：

$$b_{p-1} - b_p = b_{l-1} + b_r$$

现在我们就可以对于每个 $p$ 计算出它对应的值，然后每次就相当于是找 $l$ 到 $r$ 中值为一个数的任意一个 $p$。由于一定存在（存在性 CF 的官方题解已经证过了，也算好证，这里就不证了），所以可以直接找小于等于 $r$ 的最大的 $p$ 作为答案。

转换后的问题可以先将问题离线，按 $r$ 从小到大排序，然后扫一遍维护一个桶就行了，不过要注意这个 $p$ 的对应值在最极端的情况下是绝对值不超过 $2n$ 的。所以桶要开 4 倍，每次加上 $2n$（代码中就直接加二倍 MAXN 了） 。而且由于一定存在，所以多组数据间甚至都不用清空桶。

然后注意要特判答案为 0 的情况，别的就没什么了。

复杂度 $O(n + q \log q)$，和官方解法差不多。

代码
-
```
#include<cstdio>
#include<algorithm>
#define MAXN 300002
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define fOR(i,a,b) for(int i=a;i<b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define rOF(i,a,b) for(int i=a;i>b;i--)
using namespace std;
typedef long long ll;
int maxn(int a,int b){return a>b?a:b;}
int minn(int a,int b){return a<b?a:b;}
int qr(){
	char ch=getchar();int x=1,s=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-')x=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';ch=getchar();
	}return x*s;
}int T,n,m,l,r,b[MAXN],lst[MAXN<<2];char s[MAXN];
struct node{int l,r,k,id,ans;}q[MAXN];
bool cmp1(node a,node b){return a.r<b.r;}
bool cmp2(node a,node b){return a.id<b.id;}
int main(){
	fOR(i,0,MAXN)q[i].id=i;
	T=qr();
	while(T--){
		n=qr();m=qr();
		scanf("%s",s+1);
		FOR(i,1,n){//读入+求出数组a,b
			b[i]=b[i-1];
			if(s[i]=='+'){
				if(i&1)b[i]++;
				else b[i]--;
			}else{
				if(i&1)b[i]--;
				else b[i]++;
			}
		}FOR(i,1,m){
			q[i].l=l=qr();q[i].r=r=qr();
			if(r-l&1)q[i].k=b[l]+b[r];
			else q[i].k=b[l-1]+b[r];
		}sort(q+1,q+m+1,cmp1);//读入询问+离线
		FOR(i,1,m){
			fOR(j,q[i-1].r,q[i].r)lst[b[j]+b[j+1]+(MAXN<<1)]=j+1;//加入p的对应值
			q[i].ans=lst[q[i].k+(MAXN<<1)];//求值
		}sort(q+1,q+m+1,cmp2);
		FOR(i,1,m){
			l=q[i].l;r=q[i].r;
			if(b[l-1]==b[r])printf("0\n");
			else if(r-l&1)printf("2\n%d %d\n",l,q[i].ans);
			else printf("1\n%d\n",q[i].ans);
		}
	}return 0;
}
```
一些闲话
-
比赛的时候我推了个比这个要复杂的多的式子：
$$b_{p-1} + \dfrac{1 - a_p}{2} = b_{l-1} + \dfrac{b_r - b_{l-1}}{2}$$

然后我最后那个分数是按 $\lfloor \dfrac{b_r - b_{l-1}}{2} \rfloor$ 算的，但是系统的除法是直接取整数部分，也就是说负数的时候是向上取整的。所以如果是负数就出了错，用位运算来做就可以。就是这个导致没 AC，也算是一个语法上的细节吧。

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1562D2)
## 思路
怎么感觉题解里都讲的好复杂，我就按照我的理解简单地讲一下。

这道题的本质其实是把 $a_i$ 按照 $i$ 的奇偶性分成两组，使两组的 $\sum$ 相同，问最小的修改次数。

我们首先看样例，好家伙，全都是 $0/1/2$。我们不妨大胆猜测答案是 $0$ 或 $1$ 或 $2$。

接下来我们需要分类。

$\bullet$ 显然当原序列已经满足条件答案是 $0$。

$\bullet$ 当答案是 $1$ 时，意味着我们可以分成 $x$ 和 $x+1$ 的两组，我们执行的操作是把 $x+1$ 减 $1$，也就是 $\sum a_i$ 是一个奇数，这时我们找到前缀和为 $\left\lfloor\dfrac{\sum a_i}{2}\right\rfloor$ 的位置，然后删除这个位置后面的那个数即可。

$\bullet$ 当答案是 $2$ 时，显然 $\sum a_i$ 是一个偶数，那么我们只要随便删一个然后转化为奇数的情况即可。
## 代码
思路很明显，就不放代码了，跟其他题解的代码都差不多。

---

## 作者：FoXreign (赞：0)

## 题意
给你一个由 + - 组成的字符串 $s$ ， $s[i]$ 为 + 代表 $a_i$ 值为 $1$ ， $s[i]$ 为 - 代表 $a_i$ 为 $-1$ ，每次询问一个区间 $[l,r]$ ，问最少移除序列中多少个字符后，可以使得 $a_l + a_{l+1} + ... + a_{r-1} + a_r$ 之和，即 $\sum_{i=l}^ra_i$ 为 $0$ ？

## 题目分析
这道题的分析用到了 $dp$ 的思想，对于任意一段序列，不难发现最终答案只与它的区间和有关，与长度无关，对于奇数和的情况，我们一定能找到一个位置 $i$ ，在保证 $a_i$ 有贡献的情况下，使得 $[l,i]$ 与 $[i+1,r]$ 的值相差为1，这时候删去位置 $i$ 的值，就能保证 $i$ 前后序列之和大小相等、符号相反，此时的 $cost$ 为 $1$ ，当情况为偶数和的时候，其删去头尾之一即退化为奇数和，所以总 $cost$ 是 $2$ 。

什么叫有贡献呢？比如 + - + - （+ +） + - + 虽然 $sum[4]$ 和 $sum[6]$ 的前缀和相等，但中间括号括起来的两个 + 就属于没有贡献的值，因为这对 + 相互抵消了，所以我们要找的位置 $i$ = $4$ 。

其实再举个通俗点的例子：比如你区间符号和是 $9$ ，然后你找一个区间符号和为 $5$ 的位置， $5$ 这一个位置就是因为存在 $a_i$ 这个元素，使得原来是 $4$ 的现在变成 $5$ 了，它很碍事，所以我们拿掉它，那么之后的 $4$ 个贡献现在被取反了，正好和前面相互抵消了 。

其实如果D1想明白了，D2就很简单了，根据之前的理论，我们只需要分析奇数和的情况就好了，开个数组记录下每个值的位置 $pos$ ，设 $res$ = $sum[r] - sum[l-1]$ ，每次询问偶数和先化奇数和，然后奇数和就找询问区间内前缀和为 $\frac{res}{2} + 1$ 出现的第一个位置就好了。

需要注意的是前缀和可能会出现负数的情况，因此我们不妨给所有的前缀和加上 $n$ 后再进行操作。

## AC代码
```
#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x); i <= (y); i++)
#define down(i, x, y) for (register int i = (x); i >= (y); i--)
using namespace std;
const int maxn = 3e5 + 5;

string s;
int t, n, q, sum[maxn];

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--)
    {
        cin >> n >> q >> s;
        vector<vector<int>> pos(2 * n + 1);
        //处理负数
        pos[n].push_back(0);
        sum[0] = n;
        rep(i, 1, n) sum[i] = sum[i - 1] + (i & 1 ? (s[i - 1] == '+' ? 1 : -1) : (s[i - 1] == '+' ? -1 : 1)), pos[sum[i]].push_back(i);
        int l, r, ans;
        rep(i, 1, q)
        {
            cin >> l >> r;
            int res = sum[r] - sum[l - 1];
            if (!res)
                cout << "0" << endl;
            else if (abs(res) & 1)
            {
                cout << "1" << endl;
                //根据区间和的正负性进行不同操作，不要漏掉之前的前缀和sum[l - 1]
                //6 / 2 + 1 = 4, -6 / 2 - 1 = -4
                int tmp = sum[l - 1] + (res > 0 ? res / 2 + 1 : res / 2 - 1);
                cout << *lower_bound(pos[tmp].begin(), pos[tmp].end(), l) << endl;
            }
            else
            {
                cout << "2" << endl;
                --r; //化为奇数和的情况
                res = sum[r] - sum[l - 1];
                int tmp = sum[l - 1] + (res > 0 ? res / 2 + 1 : res / 2 - 1);
                cout << *lower_bound(pos[tmp].begin(), pos[tmp].end(), l) << " " << r + 1 << endl;
            }
        }
    }
    return 0;
}
```

---

## 作者：cmll02 (赞：0)

首先这个题的 $a_1-a_2+a_3\cdots$ 可以把偶数位的正负号反转一下，这样就变成求和了。

反转好之后记为 $b_i=(-1)^{i-1}a_i$。

前缀和一下。

对于每个询问三种情况：

令 $d=\sum\limits_{i=l}^rb_i$。

1. $d=0$，输出 $0$。
2. $d \bmod 2=1$。

接下来证明一次操作必然可行。

假设 $d$ 是正数。

记 $c_k=\sum\limits_{i=l}^kb_i$。

那么有 $|c_i-c_{i-1}|=1~(l<i\le r )$。

假设我们删掉的位置是 $k$。

那么新的权值就是 $c_{k-1}-(c_r-c_k)$。

如果 $b_k=1$，

有 $2c_k-1=c_r=d$。

显然当 $b_i=1$ 时 $c_i$ 可以取遍 $[0,d]$ 之间的整数，并且 $d$ 是正整数，有 $\dfrac{d+1}2\le d$。

那么我们必然能找到一个 $k$ 满足 $b_k=1$， $c_k = \dfrac{d+1}2$。

$d$ 是负数也是类似做法。

所以一次操作一定可行。

具体的实现方法：每个 $c$ 的值开个桶 $s_j$ 存 $c_i=j$ 的 $i$。

然后每次查询的时候直接二分 $\ge l$ 的最小值。

3. $d\bmod 2=0$

这个也很简单，首先根据奇偶性，一次操作完之后权值是奇数，肯定不行。

那么先把最后一个符号删掉，然后就转换成了情况 $2$。

这样两次操作就做完了。

代码太丑了，挂个 CF [链接](http://codeforces.com/contest/1562/submission/127152341)吧。

---

## 作者：KSToki (赞：0)

# 题目大意
给定一个长为 $n$ 的仅含 $1$ 或 $-1$ 的数组 $a$，有 $q$ 次询问，问 $l$ 到 $r$ 至少要删多少个数才能使 $\sum_{i=l}^{r}(-1)^{i-l} \cdot a_i=0$，可以删完所有数。与 D1 不同的是，你需要输出方案，即你删了哪些数。
# 题目分析
到 D2 了想必 D1 的结论都会了吧，这里挂一个 D1 的[证明](https://www.luogu.com.cn/blog/ypcaeh/solution-cf1562d1)。

有了 D1 的结论，长度为偶数先删第一个转化为奇数，核心仍然在找出长度为奇数的解。这时只需要开一个 `vector` 顺序记录出现某一个前缀贡献的所有位置，每次计算出值在里面对 $l$ 用 `lower_bound` 判断即可。时间复杂度 $O(qlogn)$，可以通过。

贴一手赛时的代码，有点乱，不过这个思路有了写起来还是比较简单，关键是要得出 D1 的结论。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
const int N=3e5;
int T,n,q,x,y,sum[300001];
char s[300001];
vector<int>pos[2][600001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		q=read();
		scanf("%s",s+1);
		For(i,1,n)
		{
			sum[i]=sum[i-1]+((s[i]=='+')?1:-1)*((i&1)?1:-1);
			if(((i&1)&&(s[i]=='+'))||((s[i]=='-')&&!(i&1)))
				pos[0][sum[i]+N].pb(i);
			else
				pos[1][sum[i]+N].pb(i);
		}
		while(q--)
		{
			x=read();
			y=read();
			if(sum[y]-sum[x-1]==0)
				puts("0");
			else
			{
				if((y-x)&1)
				{
					puts("2");
					printf("%d ",x);
					++x;
					int s=sum[y]-sum[x-1];
					int t=(s-1)/2+sum[x-1]+1;
					auto it=lower_bound(pos[0][t+N].begin(),pos[0][t+N].end(),x);
					if(it!=pos[0][t+N].end()&&*it<=y)
					{
						putint(*it);
						goto over;
					}
					t=(s+1)/2+sum[x-1]-1;
					it=lower_bound(pos[1][t+N].begin(),pos[1][t+N].end(),x);
					if(it!=pos[1][t+N].end()&&*it<=y)
					{
						putint(*it);
						goto over;
					}
				}
				else
				{
					puts("1");
					int s=sum[y]-sum[x-1];
					int t=(s-1)/2+sum[x-1]+1;
					auto it=lower_bound(pos[0][t+N].begin(),pos[0][t+N].end(),x);
					if(it!=pos[0][t+N].end()&&*it<=y)
					{
						putint(*it);
						goto over;
					}
					t=(s+1)/2+sum[x-1]-1;
					it=lower_bound(pos[1][t+N].begin(),pos[1][t+N].end(),x);
					if(it!=pos[1][t+N].end()&&*it<=y)
					{
						putint(*it);
						goto over;
					}
				}
			}
			over:;
		}
		For(i,1,n)
		{
			if(((i&1)&&(s[i]=='+'))||((s[i]=='-')&&!(i&1)))
				pos[0][sum[i]+N].clear();
			else
				pos[1][sum[i]+N].clear();
		}
	}
	return 0;
}

```


---

