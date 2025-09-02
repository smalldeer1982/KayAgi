# MEX and Array

## 题目描述

Let there be an array $ b_1, b_2, \ldots, b_k $ . Let there be a partition of this array into segments $ [l_1; r_1], [l_2; r_2], \ldots, [l_c; r_c] $ , where $ l_1 = 1 $ , $ r_c = k $ , and for any $ 2 \leq i \leq c $ holds that $ r_{i-1} + 1 = l_i $ . In other words, each element of the array belongs to exactly one segment.

Let's define the cost of a partition as $c + \sum_{i = 1}^{c} \operatorname{mex}(\{b_{l_i}, b_{l_i + 1}, \ldots, b_{r_i}\}), $  where  $ \\operatorname{mex} $  of a set of numbers  $ S $  is the smallest non-negative integer that does not occur in the set  $ S $ . In other words, the cost of a partition is the number of segments plus the sum of MEX over all segments. Let's define the value of an array  $ b_1, b_2, \ldots, b_k $  as the maximum possible cost over all partitions of this array. You are given an array  $ a $  of size  $ n $ . Find the sum of values of all its subsegments.An array  $ x $  is a subsegment of an array  $ y $  if  $ x $  can be obtained from  $ y$ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the second test case:

- The best partition for the subsegment $ [2, 0, 1] $ : $ [2], [0, 1] $ . The cost of this partition equals to $ 2 + \operatorname{mex}(\{2\}) + \operatorname{mex}(\{0, 1\}) = 2 + 0 + 2 = 4 $ .
- The best partition for the subsegment $ [2, 0] $ : $ [2], [0] $ . The cost of this partition equals to $ 2 + \operatorname{mex}(\{2\}) + \operatorname{mex}(\{0\}) = 2 + 0 + 1 = 3 $
- The best partition for the subsegment $ [2] $ : $ [2] $ . The cost of this partition equals to $ 1 + \operatorname{mex}(\{2\}) = 1 + 0 = 1 $ .
- The best partition for the subsegment $ [0, 1] $ : $ [0, 1] $ . The cost of this partition equals to $ 1 + \operatorname{mex}(\{0, 1\}) = 1 + 2 = 3 $ .
- The best partition for the subsegment $ [0] $ : $ [0] $ . The cost of this partition equals to $ 1 + \operatorname{mex}(\{0\}) = 1 + 1 = 2 $ .
- The best partition for the subsegment $ [1] $ : $ [1] $ . The cost of this partition equals to $ 1 + \operatorname{mex}(\{1\}) = 1 + 0 = 1 $ .

The sum of values over all subsegments equals to $ 4 + 3 + 1 + 3 + 2 + 1 = 14 $ .

## 样例 #1

### 输入

```
4
2
1 2
3
2 0 1
4
2 0 5 1
5
0 1 1 0 1```

### 输出

```
4
14
26
48```

# 题解

## 作者：miao5 (赞：2)

这道题的子段枚举直接大力 $n$ 方即可，这篇题解主要讲述对于一个子段，如何求出它的最大值。

设我们将一个长度 $s$ 的数组 $a$ 划分成了 $c$ 个段：$[l_1,r_1],[l_2,r_2],\dots,[l_c,r_c]$ 那么这样划分的代价为 $c+\sum_{i=1}^{i<=c}\operatorname{mex} \{a_{l_i},a_{l_{i+1}},\dots,a_{r_i}\}$，其中的 $mex$ 表示最小的在数组中没有出现过的非负数。

题目给定一个数组，要求所有子段的最大代价和。

我们先考虑一个字段的最大代价。

对于一个字段，我们考虑贪心，让每个数发挥最大的代价。我们考虑，如果想让 $mex$ 的值变大的话，那么我们需要一个 $0,1,2,\dots,x$ 的数组，如果我们将这些数划分到一起，会得到 $x+1$ 的 $\operatorname{mex}$ 代价和 $1$ 的段数代价，加起来是 $x+2$。我们再考虑把每一个数独立划分，会得到 $x+1$ 的段数代价，同时还会得到 $1$ 的 $\operatorname{mex}$ 代价，加起来也是 $x+2$。这是最适合多个数划分在同一个段的情况下，在其他的情况下，可以轻易看出每个数独立划分最优。

之后因为给定数组大小只有 $100$，所以可以放心 $O(n^2)$ 枚举子段，$O(n)$ 统计答案。

```
#include<iostream>
#define int long long
using namespace std;
int a[105];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				for(int k=i;k<=j;k++){
					ans++;
					if(a[k]==0) ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：windflower (赞：1)

为防歧义，以下将按题意划分的连续的段称为**小段**，需要求代价的段称为**子段**。  
先稍微翻译一下题意： 
- 某个子段的代价就是它的小段数+每个小段的 MEX。  
- 求所有子段的代价的最大值之和。  

再找找特殊的地方：  
- 不含 0 的小段的 MEX 为 0 。  
- 一个子段的代价也是它的小段的代价和。

来分析下划分的策略 (假设元素数量为 cnt ) ：
- 若某个子段不含 0 ，那么它的代价就是它的小段数（因为所有小段 MEX 均为 0 ），所以代价的最大值就是 cnt 。
- 若某个子段含 0 ，假设它其中一个含 0 小段的 MEX 为 k ，那么这个小段的代价就是 $k+1$ ，又显然 $k\le cnt$ ，所以这个小段的代价的最大值就是 $cnt+1$ ，而其它小段不含 0 ，最大代价便是 cnt 。由此可知，含 0 子段的最大代价是 $cnt+1$ 。  

再通俗一点：
- 非 0 元素对每个子段的贡献为 1 ， 0 对每个子段的贡献为 2 。

因此只需要把所有元素的贡献加起来就行了。  
**注意**：每个元素在几个子段中，它就贡献了几次。  
附 AC 代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++)cin>>a,ans+=i*(n+1-i)*(!a+1);
		cout<<ans<<endl;
	}
	return 0;
}
```




---

## 作者：Novice233 (赞：0)

一道纯数学题，乍一看觉得要模拟来算分割方式。

但稍微算一下就会发现，对于每一个子序列，将子序列中每个元素切开来单独成段代价是最大的。

理由如下：设子序列长度为 $k$ ，那么 MEX ( $A_1$，$A_2$，...，$A_k$）的最大值为 $k$，代价为 $k+1$。而如果将每一元素单独成段，分为 $k$ 段，代价为 $k$，若有0，则再加1。因此不难看出，每一个元素单独成段才是代价最大的。

代码
```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
int t,n;
long long a[N];
int main(){
	cin>>t;
	while(t--){
		int ans=0;
		cin>>n;
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=n;i>=1;i--){
			ans+=i*(n-i+1);
			for(int j=1;j<=n;j++){
				if(a[j]==0) ans+=min(min(j,n-j+1),min(i,n-i+1));
			}
		}
		cout<<ans<<endl;
		ans=0;
	}
	return 0;
}
```


---

## 作者：Hywel (赞：0)

#### 思路
因为是要将序列划分为 $c$ 段，代价是 $c + c * mex(a_l,....,a_r)$ 所以如果将序列划分为少于 $n$ 段的话，那么代价一定是比划分为 $n$ 段小的，所以我们把序列划分为 $n$ 段，分别处理 $mex$，最后累加即可

#### Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define forever return
using namespace std;

namespace IO
{
    template < typename T > inline void write( T x )
    {
        if(x < 0)
            putchar('-') , x = - x;
        if(x == 0)
        {
            putchar('0') ;
            return ;
        }
        if(x > 9)
            write(x / 10) ;
        putchar(x % 10 + '0') ;
        return ;
    }
    template < typename T > inline void read( T &x )
    {
        x = 0 ; int w = 1 ; char ch = getchar() ;
        while( !isdigit( ch ) ) { if(ch == '-') w = -1 ; ch = getchar() ; }
        while( isdigit( ch ) ) x = (x << 1) + (x << 3) + (ch ^ 48) , ch = getchar() ;
        x *= w;
    }
}

#define writeln(x) write(x) , putchar('\n')
#define writesp(x) write(x) , putchar(' ')
using namespace IO ;

#define int long long
/* ------------------------------------------------------------------------------------------------------------------------ */
int a[100000],b[100000];
signed main()
{
    int T ;
    read( T ) ;
    while( T -- )
    {
        int n ;
        read( n ) ;
        ll res = 0;
        for( int i = 1 ; i <= n; ++ i)
        {
            read(a[i]);
            if(a[i]==0)
                b[i]=b[i-1]+1;
            else b[i]=b[i-1];
        }
        for(int i = 1 ; i<=n;++i)
        {
            for(int j=i;j<=n;++j)
            {
                for(int k=i;k<=j;++k)
                {
                    if(a[k]==0)res++;
                    res++;
                }
            }
        }
        writeln(res);
    }   
    // system("pause");
    forever 0 ;
}
```

---

## 作者：清烛 (赞：0)

先考虑对于一个固定的序列，怎么求他的“划分”的最大代价。

经过多组观察（在做这种 D2B 级别的题的时候观察非常有效），我们可以发现，每个元素单独作为划分的一段一定是最优的，然后大胆写上去就过了这题。下面给出简要证明。

假设当前划分的一段包含了 $\{0, 1, 2,\cdots, m\}$ 中的所有数，共有 $k$ 个元素，则其代价为 $1 + \operatorname{mex}\{0,1,\cdots, m\} = m + 2$，然后我们将其划分为一个元素一段后，代价为 $k + \operatorname{cnt}(0)$，而 $m + 1\le k$，$\operatorname{cnt}(0)\ge 1$，所以将每个元素作为一段不会更劣。

再假设当前划分的一段包含了 $\{0, 1, 2,\cdots, m\}$ 中的数和其他若干 $> m$ 的数，共有 $k$ 个元素，则其代价为 $m + 2$，然后划分为一个元素一段后的代价为 $k + \operatorname{cnt}(0)$，用类似上文的分析方法可知每个元素作为一段是不会更劣的。

再假设当前划分的一段不包含 $0$，有 $k$ 个元素，则其代价为 $0$，划分为一个元素一段后代价为 $k$，所以这种情况下划分为一个元素一段是严格更优的。

综上我们完成了证明。现在考虑如何计算每个连续子段的贡献。

注意到一个元素作为一段会产生 $1$ 的贡献，所以这部分的贡献是 $\sum_{i=1}^ni(n - i + 1)$，然后是 $0$ 元素产生的 $\operatorname{mex}$ 为 $1$ 的贡献，对于 $a_i = 0$ 来说，其贡献就为 $i\times(n - i + 1)$。

所以这题其实是可以加强到 $O(n)$ 的，，，不知道为什么出题人的数据范围是 $100$。

```cpp
const int maxn = 105;
int n, a[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        int ans = 0;
        FOR(i, 1, n) {
            ans += (n - i + 1) * i;
            if (!a[i]) ans += (i) * (n - i + 1);
        }
        print(ans);
    }
    return output(), 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
设我们有一个长度为 $k$ 的数组 $b$，并且划分为了 $c$ 段，每段为 $[l_1,r_1],[l_2,r_2],\dots,[l_c,r_c]$，满足 $l_c=1$，$r_c=k$，且 $\forall i\in[2,c]$，$r_{i-1}+1=l_i$。换句话说，数组 $b$ 中的每一个元素都在恰好一段里面。

让我们定义数组 $b$ 的如上划分的代价为

$$c+\sum\limits_{i=1}^c\operatorname{MEX}(b_{l_i},b_{l_i+1},\cdots,b_r)$$

其中 $\operatorname{MEX}(S)$ 为最小的没有出现在集合 $S$ 中的**非负整数**。换句话说，如上划分的代价为划分的段数加上每一段的 $\operatorname{MEX}$ 值。

现在，给定一个长度为 $n$ 的数组 $a$，你需要求出其所有子段的**最大**代价的总和。我们称数组 $y$ 是数组 $x$ 的一个子段，当且仅当我们可以通过在数组 $x$ 的开头和结尾删去连续的若干个元素得到数组 $y$。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 30$，$1\leqslant n,\sum n\leqslant 100$，$0\leqslant a_i\leqslant 10^9$。**
## Solution
由于 $n$ 很小，我们考虑一种不用脑子的枚举子段的做法。首先肯定是得枚举子段，然后我们考虑如何计算每个子段的代价。

经过手玩样例不难发现，将一个数组全部划分为长度为 $1$ 的子段的代价一定是最大的。因为每当一个子段的长度加 $1$，其能够分成的子段个数减少 $1$，而其 $\operatorname{MEX}$ 值**最多**增加 $1$（很有可能不变），因此全部分成长度为 $1$ 的子段的代价一定不会比其余方案的代价更小。然后我们发现，除了整个大的子段的长度对代价有贡献，所有长度 $1$ 的子段中，只有单独一个 $0$ 的 $\operatorname{MEX}$ 值为 $1$，其余的都是 $0$。所以，对于一个大的子段 $[l,r]$，其最大代价为 $r-l+1+cnt_0$，其中 $cnt_0$ 为大的子段 $[l,r]$ 中 $0$ 的个数。

然后就这么统计所有子段的最大代价就做完了。
## Code
```cpp
namespace Solution {
	const int N = 107;
	int n, Test, ans, a[N];
	
	void Main() {
		read(Test);
		while(Test--) {
			read(n);
			ans = 0;
			for(int i = 1; i <= n; ++i)
				read(a[i]);
			for(int i = 1; i <= n; ++i)
				for(int j = i; j <= n; ++j) {
					int cnt = 0;
					for(int k = i; k <= j; ++k)
						if(!a[k])
							cnt++;
					ans += (j - i + 1 + cnt);
				}
			write(ans);
			puts("");
		}
		return;
	}
}
```

---

## 作者：_ajthreac_ (赞：0)

首先考虑如何计算整个序列的价值。容易发现只有包含 $0$ 的子段才会产生贡献，手玩一下会发现全部切成长度为一的最优：若有长度大于一的子段，将它切开不会使答案变劣。

那么整个序列的价值就是 $n+cnt$，其中 $cnt$ 为 $0$ 的个数。

再看原题，我们需要计算所有子段的价值和，第一项可以简单地计算出来，第二项可以分开算每个 $0$ 带来的贡献。

参考代码（其实以这题的数据范围怎么写都能过）：
```cpp
const int N=110;
int T,n,a[N];
signed main(){
  Read(T);
  while(T--){
    Read(n);int ans=0;
    for(int i=1;i<=n;i++)ans+=i*(n-i+1);
    for(int i=1,x;i<=n;i++){
      Read(x);if(!x)ans+=i*(n-i+1);
    }
    printf("%lld\n",ans);
  }
  KafuuChino HotoKokoa
}
```

---

## 作者：include_BM (赞：0)

设 $x=c + \sum_{i = 1}^{c} \operatorname{mex}\left({b_{l_i}, b_{l_i + 1}, \ldots, b_{r_i}}\right)$。

将一个序列中的每个数各自分为一个序列得到的 $x$ 一定是最大的，假设有一段长度为 $n$ 的序列 $a$，那么：

+ 若其中没有 $0$，则无论怎样分 $\operatorname{mex}$ 均为 $0$，那么 $x$ 就等于 $c$ 即分的段数，每个数各自分为一个序列时段数最多即 $x$ 最大。

+ 若其中已经包含了 $0,1,\dots i$，那么将 $i+1$ 加入到这个序列中会使 $\operatorname{mex}$ 增大 $1$，使 $c$ 减少 $1$，总体上不会更好；若加入的数不是 $i+1$，只会使 $c$ 减少 $1$，总体上会变得更差。故将一个数加入到另一个序列中不会使答案更好，即每个数各自分为一个序列时答案最优。

那么只需要枚举所有子序列并计算答案即可。

代码：

```cpp
const int N=1e4+10;
ll n,a[N],ans;
signed main(){
    for(int T=read();T;--T){
        n=read(),ans=0;
        for(int i=1;i<=n;++i) a[i]=read();
        for(int l=1;l<=n;++l)
            for(int r=l;r<=n;++r){
                ans+=r-l+1;
                for(int i=l;i<=r;++i) ans+=(a[i]?0:1);
            }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Toorean (赞：0)

提示: 本题解并非优解，只是一种用**普通的暴力**的思想来解这道题。

## 题意
设一个长度为 $k$ 的数组 $b$ 被分成了几个部分：$[l_1;r_1],[l_2;r_2],\cdots,[l_c;r_c](l_1=1,r_c=k,r_{i-1}+1=l_i)$。现定义每个部分的花费为 $c+\underset{i=1}{\overset{c}{∑}}\operatorname{mex}\{{b_{l_i},b_{l_{i+1}},…,b_{r_i}}\}$（$\operatorname{mex}\{x_1,x_2,\cdots,x_n\}$，表示与 $x_1,x_2,\cdots,x_n$ 互不相等的最小的非负整数。）。问数组 $b$ 中**所有**部分花费最大值为多少？

## 思路
首先，我们应该要把对应区间 $[l,r]$ 的 $\operatorname{mex}$ 给求出来。之后，我们可定义递归函数 $\operatorname{solve}(l,r)$ 表示在 $[l,r]$ 中的最大花费，具体定义则如下所示：
$$
\operatorname{solve}(l,r) = \begin{cases}
\operatorname{mex}(l,r)+1 ,& l = r\\
\max\{\operatorname{solve}(l+1,r)+ \operatorname{mex}(l,l + 1) + 1,\operatorname{solve}(l+2,r)+ \operatorname{mex}(l,l+2) + 1,\cdots,\operatorname{solve}(l+i,r)+ \operatorname{mex}(l,l+i) + 1\} ,& l<r
\end{cases}
$$
有了这个递归函数，我们还不要忘记进行记忆化，可定义 $f_{l,r}=\operatorname{solve}(l,r)$，便大大降低时间复杂度。

## AC Code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 110
#define LL long long 
#define max(x,y) (x > y ? x : y)

using namespace std;

int t, n;
int arr[MAXN];
LL f[MAXN][MAXN], mex[MAXN][MAXN];

LL solve (int l, int r) {       
    if (f[l][r] != -1) { return f[l][r]; }
    if (l == r) { return f[l][r] = mex[l][r] + 1; }

    LL ans = mex[l][r] + 1;     
    for (int i = l + 1; i <= r; i++) {
        ans = max (ans, solve (i, r) + mex[l][i - 1] + 1);
    }
    return f[l][r] = ans;
}

int main (void) {

    scanf ("%d", &t);
    while (t--) {
        memset (mex, 0, sizeof (mex));
        memset (f, -1, sizeof (f));

        scanf ("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf ("%d", arr + i);
        }

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                if (i == j) {
                    mex[i][j] = arr[i] ? 0 : 1;
                } else {
                    int temp[MAXN];
                    for (int k = i; k <= j; k++) {
                        temp[k] = arr[k];
                    }
                    sort (temp + i, temp + j + 1);
                    if (temp[i] != 0) {
                        mex[i][j] = 0;
                    } else {
                        int st = 1;
                        for (int k = i + 1; k <= j; k++) {
                            if (st != temp[k]) {
                                mex[i][j] = st;
                                break ;
                            } else {
                                ++ st;
                            }
                        } 
                        if (!mex[i][j]) {
                            mex[i][j] = st;
                        }
                    }
                }
            } 
        }
        
        LL ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                ans += solve (i, j);
            } 
        }

        printf ("%lld\n", ans);
    }

    return 0;
}
```

---

## 作者：Cocoly1990 (赞：0)

先不考虑子段。

假设我们划分一段区间 $\left[l,r\right]$，$0\sim m$ 都在这里面出现过至少一次，则这一段的贡献应该是 $1+m$.

很显然的是，$r-l+1\geq m$.

那么如果我把他拆成每个数单独一段，那么他的贡献 $\texttt{value}$ 应该有 $\texttt{value}\geq r-l+1+1$.

为什么还要再加 $1$ 捏？因为 $0$ 在 $\left[l,r\right]$ 之间至少出现了一次，而 $0$ 单独一段显然其 $\operatorname{Mex}=1$，所以有上式成立。

通过上述方法，我们证明了每个数单独分段必然最优，那么原数列的一个子段 $\left[l,r\right]$ 的贡献是 $r-l+1+\texttt{count-0}$，其中 $\texttt{count-0}$ 表示该段中 $0$ 的个数。

考虑到 $n$ 范围很小，直接枚举区间计算就好了，综合时间复杂度 $\mathcal{O}\left(n^3\right)$，可以通过。


---

## 作者：sinsop90 (赞：0)

题目大意:

给定一个序列, 将这个序列分为若干段, 求段数加上每一段的 MEX 值的最大值。

Solution:

不妨假设我们已经将序列分为了若干段, 其中一段是 $[l, r]$。

当我们将 $r$ 单独分为一段, 也就是说变成 $[l, r - 1]$ 和 $[r, r]$

我们发现 $[l, r - 1]$ 的 MEX 值只有两种情况 : 减一或不变, 但是段数却加一了。

因此, 对于一个区间 $[l, r]$, 分为 $[l, r - 1]$ 和 $[r, r]$ 比 $[l, r]$ 更优。

因而, 把整个序列分为 $[1,1], [2,2], [3,3] ... [n,n]$ 是最优的。

代码如下:

```
    #include <bits/stdc++.h>
    #define maxn 1005
    using namespace std;
    int T, t[maxn], a[maxn], n;
    int getsum(int l, int r) {
    	int res = 0;
    	for(int i = l;i <= r;i++) if(a[i] == 0) res ++;
    	return res;
    }
    int main() {
    	scanf("%d", &T);
    	while(T --) {
    		int ans = 0;
    		scanf("%d", &n);
    		for(int i = 1;i <= n;i++) scanf("%d", &a[i]);
    		for(int i = 1;i <= n;i++) {
    			for(int j = i;j <= n;j++) {
    				ans += getsum(i, j) + (j - i + 1);
    			}
    		}
    		printf("%d\n", ans);
    	}
    }
```


---

