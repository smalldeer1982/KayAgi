# Subsequence Counting

## 题目描述

Pikachu had an array with him. He wrote down all the non-empty subsequences of the array on paper. Note that an array of size $ n $ has $ 2^{n}-1 $ non-empty subsequences in it.

Pikachu being mischievous as he always is, removed all the subsequences in which Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=d $

Pikachu was finally left with $ X $ subsequences.

However, he lost the initial array he had, and now is in serious trouble. He still remembers the numbers $ X $ and $ d $ . He now wants you to construct any such array which will satisfy the above conditions. All the numbers in the final array should be positive integers less than $ 10^{18} $ .

Note the number of elements in the output array should not be more than $ 10^{4} $ . If no answer is possible, print $ -1 $ .

## 说明/提示

In the output of the first example case, the remaining subsequences after removing those with Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=5 $ are $ [5],[5,7],[5,6],[5,7,6],[50],[7],[7,6],[15],[6],[100] $ . There are $ 10 $ of them. Hence, the array $ [5,50,7,15,6,100] $ is valid.

Similarly, in the output of the second example case, the remaining sub-sequences after removing those with Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=2 $ are $ [10],[100],[1000],[10000] $ . There are $ 4 $ of them. Hence, the array $ [10,100,1000,10000] $ is valid.

## 样例 #1

### 输入

```
10 5
```

### 输出

```
6
5 50 7 15 6 100```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
4
10 100 1000 10000```

# 题解

## 作者：XCH_0803 (赞：1)

# 题意

找到一个数列（长度不超过 $10^4$），使得有且仅有 $x$ 个非空子数列中元素极差小于 $d$ ，或者输出 $-1$ 。

# 思路

考虑如何让后加的子序列中的数不会影响到前面的，只需要加一个 $d$ ，就可以形成新的一组。

于是我们需要将子序列拆成若干个互不相干的组，每组内取一个相同的值。

对于一个含有 $n$ 个元素的组，它的贡献是 $2n−1$。

假如这个贡献是 $2n$ 就可以直接二进制分解做了。

那么我们强行补一个大小为 $1$ 的组，这样就可以当做它是 $2n$ 了。

话不多，说上代码！！！


```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000005;
int n,x,d,a[N],m;
signed main(){
    cin>>x>>d;
    for(int i=31;i>=0;i--){
        if(x&(1ll<<i)){
            a[m]=i;
            a[m+1]=1;
            n+=i+1;
            m+=2;
        }
    }
    cout<<n<<endl;
    for(int i=0;i<m;i++){
        while(a[i]--){
			cout<<1+d*i<<" ";
        }
    }
    return 0;
}
```




---

## 作者：LouYiYang1 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF960C)
考虑如何让后加的子序列中的数不会影响到前面的，只需要加一个 $d$，就可以形成新的一组。于是我们需要将子序列拆成若干个互不相干的组，每组内取一个相同的值。对于一个含有 $n$ 个元素的组，它的贡献是 $2n−1$ 。假如这个贡献是 $2n$ 就可以直接二进制分解做了。我们强行补一个大小为 $1$ 的组，这样就可以当做它是 $2n$ 了。

# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,d,a[1000005],m;
signed main(){
	cin>>x>>d;
	for(int i=31;i>=0;i--){
		if(x&(1ll<<i)){
			a[m]=i;
			a[m+1]=1;

			n+=i+1;
			m+=2;
		}
	}
	cout<<n<<endl;
	for(int i=0;i<m;i++){
		while(a[i]--){
			cout<<1+d*i<<" ";
		}
	}
	return 0;
}

```

---

## 作者：Composite_Function (赞：0)

# 思路

首先，把题意中有可能令人误解的特性说一下：

- 对于序列 $\left\{ 1, 1 \right\}$，$\left\{ 1 \right\}$ $\left\{ 1 \right\}$ $\left\{ 1, 1 \right\}$ 都是该序列的子序列。$\left\{ 1 \right\}$ $\left\{ 1 \right\}$ 是不同的子序列

- 本题为 $\texttt{SP}$，对所求序列的顺序没有要求。

如果看完这一段发现于自身理解有偏差的话，不放再做一做。

------------

因为结果对输出没有特殊限制。因此，只要在构造答案时保证，后面构造的数不会影响到前面已构造的的数就行了。很显然，每次对前一个值加上 $d$，就是一个满足要求的子序列。

接下来，如果有任意一个值在所求序列中出现了 $i$，则会贡献 $2^k - 1$ 个子序列。所以对于每一位，若 $x$ 的二进制位为 $1$ 则创建出在已构造序列中尚未出现的值，其数量为二进制位数。贪心算法直接加入序列即可。

------------

# 代码

随时嵌套循环，但由于每次操作的次数不会超过 $x$ 的二进制位，因此时间复杂度 $O(x)$，且实际运行不会有那么多次。

```cpp
# include <bits/stdc++.h>
using namespace std;
# define int long long
int x, d, num = 1, cnt = 1;
vector<int> ans;
signed main()
{
    cin >> x >> d;
    while (x != 0) {
        if (x % 2 == 1) {
            for (int i = 1; i <= num - 1; ++i)
                ans.push_back(cnt);
            cnt += d, ans.push_back(cnt), cnt += d;
        }
        x /= 2, ++num;
    }
    int size = ans.size();
    cout << size << endl;
    for (int i = 0; i < size; ++i)
        cout << ans[i] << " ";
    return 0;
}
```


---

## 作者：w33z8kqrqk8zzzx33 (赞：0)

观察到题目没有限制输出的值范围，所以来强上子序列范围限制可以把所有互不相同的元素用一个巨大数隔开。

如果某一个值出现 $k$ 次，它会贡献恰好 $2^k-1$ 个子序列。题并没有要求最优，于是直接贪心，先从最大 $k$ 开始，一直到最小 $k$，毕竟当 $k=1$ 只会贡献一个子序列，肯定能造出来要求序列。

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>
//#define int ll
const int MOD = 1000000007;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int x, _; cin >> x >> _;
    vector<ll> ans;
    ll dst = 1;
    for(int i=30; i>=1; i--) {
        int cnt = (1<<i)-1;
        while(x >= cnt) {
            rep(j, i) ans.pb(dst);
            dst += MOD;
            x -= cnt;
        }
    }
    cout << ans.size() << endl;
    for(ll& j:ans) cout << j << ' ';
}
```

---

## 作者：DPair (赞：0)

## 【坑点】
这道题你构造出的序列中可以有重复元素，而且对于$[1, 1]$，有$3$个非空子序列——$[1],[1],[1,1]$

看到这里会做了的可以回去了，不会的请继续往下看。。。

## 【思路】
构造题，找构造方法。

这道题具体思想其实就是**让后面加上来的子序列中的数不会影响到前面的**。

这简单，加一个$d$就行了，就可以形成新的一组。（因为当前序列中最大值加$d$一定不能与先前的任意一个数出现在同一序列中）。

下面把你的子序列拆分成很多互不干扰的组，每一组的**子序列个数和显然就是总的子序列个数和。**(对于互不干扰上文已有解释）

然后通过每一组进行一个构造看看，要找出一个规律。

由于每一个有$n$个元素的组有$2^n-1$种非空子序列（由于是同一组的，一定是合法的），考虑尽可能使得这一组的合法子序列数变为$2^n$，就可以对于$x$进行**二进制拆分**做了。

到这里已经基本做完了，想挑战自己的同学可以停下了。下面介绍使得$2^n-1$变为$2^n$的解法。

很简单，在这一组中加入一个$a_{max}+d$，然后让下一组的开头由$a_{max}+d$变为$a_{max}+2d$。

还是互不干扰的，并且对于每一组**恰好加上了一个非空子序列个数为$1$的一组。**

然后就做完了，对于$x$进行二进制拆分，可以发现最多拆成$log_2x$个，反正在$30$左右。也就是按刚才的解法顶多加到$60d$的数据，不会爆炸。

## 【代码】
`想抄代码的，我劝你善良。`
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL x, d, base = 1, cur = 1;
vector <LL> ans;
int main()
{
	cin >> x >> d;
	while(x)
	{
		if(x & 1)
		{
			for (register int i = 1;i <= base - 1;i ++)
			{
				ans.push_back(cur);
			}
			cur += d;
			ans.push_back(cur);
			cur += d;
		}
		x >>= 1;
		base ++;
	}
	printf("%lld\n", (LL)ans.size());
	for (register int i = 0;i < ans.size();i ++)
	{
		printf("%lld ", ans[i]);
	}
}
```

---

## 作者：氧少Kevin (赞：0)

# CF960C - Subsequence Counting
- https://www.luogu.com.cn/problem/CF960C
- 分块构造

## 题意

给出 $X,d(1\leq X,d\leq 10^9)$，你需要构造一个序列，满足：
- 长度不超过 $10^4$。
- 每个元素大小不超过 $10^{18}$。
- 假设构造的序列长度为 $n$，那么恰好有 $2^n-1$ 个非空子序列。要求这些非空子序列中，恰好有 $X$ 个子序列满足：序列中元素最大值 $-$ 序列中元素最小值 $<d$。

## 思路

注意到：
- 题目中精确要求了非空子序列的数量，不能多也能不少。
- 构造的序列每个元素大小不超过 $10^{18}$，这正好是 $d$ 取值上限的 $10^9$ 倍。

综上，考虑分块构造。

即：将序列一块一块地构造，每个块之间互不影响。

具体而言：
- 对于同一个块内的元素，两两元素之差均 $<d$。
- 对于不同块的元素，两两元素之差均 $\geq d$。

这样，设某一个块的元素数量为 $cnt$，那么它对总数的贡献为 $2^{cnt}-1$，并且不受其他块的影响。

对于题目中精确要求了非空子序列的数量这一点，将 $X$ 拆二进制构造即可。

---

