# Balance (Easy version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version there are no "remove" queries.

Initially you have a set containing one element — $ 0 $ . You need to handle $ q $ queries of the following types:

- + $ x $ — add the integer $ x $ to the set. It is guaranteed that this integer is not contained in the set;
- ? $ k $ — find the $ k\text{-mex} $ of the set.

In our problem, we define the $ k\text{-mex} $ of a set of integers as the smallest non-negative integer $ x $ that is divisible by $ k $ and which is not contained in the set.

## 说明/提示

In the first example:

After the first and second queries, the set will contain elements $ \{0, 1, 2\} $ . The smallest non-negative number that is divisible by $ 1 $ and is not contained in the set is $ 3 $ .

After the fourth query, the set will contain the elements $ \{0, 1, 2, 4\} $ . The smallest non-negative number that is divisible by $ 2 $ and is not contained in the set is $ 6 $ .

In the second example:

- Initially, the set contains only the element $ \{0\} $ .
- After adding an integer $ 100 $ the set contains elements $ \{0, 100\} $ .
- $ 100\text{-mex} $ of the set is $ 200 $ .
- After adding an integer $ 200 $ the set contains elements $ \{0, 100, 200\} $ .
- $ 100\text{-mex} $ of the set is $ 300 $ .
- After adding an integer $ 50 $ the set contains elements $ \{0, 50, 100, 200\} $ .
- $ 50\text{-mex} $ of the set is $ 150 $ .

## 样例 #1

### 输入

```
15
+ 1
+ 2
? 1
+ 4
? 2
+ 6
? 3
+ 7
+ 8
? 1
? 2
+ 5
? 1
+ 1000000000000000000
? 1000000000000000000```

### 输出

```
3
6
3
3
10
3
2000000000000000000```

## 样例 #2

### 输入

```
6
+ 100
? 100
+ 200
? 100
+ 50
? 50```

### 输出

```
200
300
150```

# 题解

## 作者：lailai0916 (赞：4)

## 原题链接

- [洛谷 CF1732D1 Balance (Easy version)](https://www.luogu.com.cn/problem/CF1732D1)

## 解题思路

考虑通过直接模拟来解决。维护一个 `set`，在每次插入操作 `+` 时，将元素插入集合中；在查询操作 `*` 时，从小到大暴力枚举 t 的值。

然而，这种方法在最坏情况下会导致时间复杂度为 $O(q^2)$。例如在前一半操作频繁插入 $1, 2, \dots, \frac{q}{2}$，而后一半的操作频繁查询 $1$ 时，无法满足题目时间限制。

考虑优化，注意到集合中的元素是单调递增的。因此，对于每个数 $x$ 的查询，答案只会增大而不会减小。我们可以利用 map 来记录每个数 $x$ 上一次查询的答案，若再次遇到相同的查询，则可以从上次的结果继续计算，而不必重新从头开始。

优化后的最坏情况是：前半部分的操作插入 $1, 2, \dots, \frac{q}{2}$，后半部分的操作查询 $1, 2, \dots, \frac{q}{2}$。此时，对于第 $i$ 个数，我们最多需要枚举约 $\frac{q/2}{i}$ 次，因此时间复杂度为 $O(\sum_{i=1}^{q/2}\frac{q/2}{i})=O(q \log q)$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int N=200005;
set<ll> s;
map<ll,ll> m;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int q;
	cin>>q;
	s.insert(0);
	while(q--)
	{
		char op;
		ll x;
		cin>>op>>x;
		if(op=='+')s.insert(x);
		else if(op=='?')
		{
			ll ans=m[x];
			while(s.find(ans)!=s.end())ans+=x;
			m[x]=ans;
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：zac2010 (赞：4)

本题有一种思路不言而喻：每次用哈希表或者 `map` 记录一个数是否出现过，若是插入操作则直接在上述的数据结构里插入，否则开始一步一步的求解 $t$。注意：对于相同的 $k$ 要记忆化一下（毕竟只有插入没有删除），$t_{now}$ 一定大于 $t_{last}$。

给出较为严谨的时间复杂度证明：

考虑一种情况，假设插入有 $2 \times 10^5$ 次，询问也有有 $2 \times 10^5$ 次。虽然这种情况的总操作次数不合法，但是依旧是在同个数量级的，故而忽略多出来的常数。

接下来，发现有如下性质：
* 操作的数较小不劣于操作的数较大。

	显然，操作的数更小那么他们的倍数会分布地更密集一些。
* 操作的数在总体比较小的情况下，分布地更密集一些能使时间复杂度卡得更坏。

有了如上性质，我们不难发现最坏的情况是插入的数为 $1$ 到 $2 \times 10^5$，查询的数也是这个范围。时间复杂度为 $O(\frac{q}{1}+\frac{q}{2}+...+\frac{q}{q-1}+\frac{q}{q})=O(q \log q)$。

[代码](https://codeforces.com/contest/1732/submission/204304296)。

---

## 作者：fmdd_szx (赞：2)

[原题](https://www.luogu.com.cn/problem/CF1732D1)

## 思路

看看数据范围 $1 \le x \le 10^{18}$，考虑使用 map。

- 操作为 $+ x$ 时，标记 $x$。
- 操作为 $? k$ 时，枚举答案即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,i,t,x;
char c;
map<int,int> f,a;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    while(n--){
        cin>>c>>x;
        if(c=='+') f[x]++;//标记，加入x
        else{
            //判断是否有上一次，有则从上一次开始，反之则从1开始枚举
            if(!a[x]) t=1;
            else t=a[x];
            for(i=t;;i++)//枚举
                if(!f[i*x]){
                    cout<<i*x<<"\n",a[x]=i;
                    break;
                }
        }
    }
    return 0;
}//注意long long
```

---

## 作者：loser_seele (赞：2)

我们企图证明其他题解暴力的复杂度是对的。

首先不难发现因为每个 $ k $ 最多被询问一次（否则可以记忆化），所以最差情况是前面一半的操作是插入 $ 1,2,...,\frac{q}{2} $，后面一半的操作是询问相同的数的时候，每个数需要跳的次数之和为调和级数，显然是 $ \mathcal{O}(q\log{q}) $。

于是总时间复杂度是 $ \mathcal{O}(q\log{q}) $，用 unordered_map 实现 $ \mathcal{O}(1) $ 的查询。

但是 unordered_map 会被卡，手写一个哈希就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char op[3];
struct seele_hash
{
    static uint64_t splitmix64(uint64_t x) 
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const 
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
unordered_map<long long, int,seele_hash> mp,rem;
int main()
{
    int T;
    scanf("%d", &T);                     
    while(T--)
    {
        long long x;
        scanf("%s%lld", op + 1, &x);        
        if(op[1] == '+')               
            mp[x]++;
        else
        {
            long long k = 1;
            if(rem[x]) 
            k = rem[x];
            while(mp[x * k]) 
            k++;
            rem[x] = k; 
            printf("%lld\n", x * k);
        }
    }
}
```


---

## 作者：CodingOIer (赞：1)

## CF1732D1 Balance 题解

### 题目解释

输入一个 $op$ 和 $x$，$op$ 有 $2$ 种情况。

> - $op$ 为 `+`，则将 $x$ 加入到集合中。
> - $op$ 为 `?`，则找到一个最小的 $k$，使 $k \times x$ 不在合集中。

题目非常简单明了。

### 具体实现

这时，看到这句话：$1 \le x \le 10^{18}$，所以不可能用数组实现。

这就涉及到了另一个数据结构：`map`。

语法为：`map<键的数据类型,值的数据类型>标识符;`

访问方法和数组很像：`标识符[键]`。

例子：

```cpp
map<int,int>m;
m[7]=2;
printf("%d\n",m[7]);
```

知道这个之后就十分简单了。

可以直接用 `map` 进行标记。

然后 `?` 的选项便可以直接用循环枚举。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
char op;
long long n;
long long x;
map<long long, bool> t;
map<long long, long long> last;
// 记录上一次的答案
int main()
{
    scanf("%lld", &n);
    getchar();
    // 把回车除去，不然等会输入的的op为'\n'
    for (long long i = 1; i <= n; i++)
    {
        scanf("%c %lld", &op, &x);
        getchar();
        // 把回车除去，不然下一次的op为'\n'
        if (op == '+')
        {
            t[x] = true;
            // 放入合集
        }
        else if (op == '?')
        {
            for (long long j = (last[x] == 0 ? 1 : last[x])/*如果有上一次，则从上一次开始枚举，否则从1开始*/;; j++)
            {
                // 循环枚举
                if (!t[j * x])
                {
                    printf("%lld\n", j * x);
                    last[x] = j;
                    // 更新
                    break;
                    // 输出并退出
                }
            }
        }
    }
    return 0;
}
```
**注：**`map` 的时间复杂度为 $O(\log N)$。

时间复杂度：对于最大的数据，假设为 $N = 2 \times 10^5 , Q = 2 \times 10^5$ 虽然不符合题意，但时间复杂度为 $O(\frac{N}{1}+\frac{N}{2}+\frac{N}{3}+\dots+\frac{N}{N}) \Rightarrow O(N \log N)$

---

## 作者：Priestess_SLG (赞：0)

好简单一题。考虑到弱化版只有添加和查询没有删除，因此对于每一个相同的 $k$ 随时间推移答案肯定单调不降。所以直接用 `set` 维护当前所有出现过的数，然后用 `map` 暴力维护每一个 $k$ 当前的答案即可。更新的时候无需维护，只需要在查询的时候直接暴力往上跳答案即可。没有什么手法。

```cpp
namespace ttq012 {
    const int N = 500100;
    void run() {
        set<int> se;
        map<int, int> mp;
        int q;
        cin >> q;
        while (q--) {
            char o;
            int v;
            cin >> o >> v;
            if (o == '+') {
                se.emplace(v);
            } else {
                if (!mp.count(v)) mp[v] = v;
                while (se.count(mp[v])) mp[v] += v;
                cout << mp[v] << '\n';
            }
        }
    }
}
```

---

## 作者：Stars_Traveller (赞：0)

## CF1732D1 Balance (Easy version) 题解

### 思路
看到没有删除操作，并且第二种操作的询问可以用枚举和标记实现，但是 $x$ 的范围很大，因此考虑 map。

第一种操作直接对 $x$ 进行标记，第二种操作枚举 $t$，然后如果之前 $x$ 已经进行过第二种操作，就直接从上一次枚举到的地方继续走，类似记忆化。

### 代码
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#define int long long
using namespace std;
 
int n;
char op;
int t;
map<int,int> mp, id;
signed main()
{
	for(cin>>t;t;t--)
	{
		cin>>op>>n;
		if(op=='?')
		{
			int lst=1;
			if(id[n])
			{
				lst=id[n];
			}
			while(mp[n*lst])
			{
				lst++;
			}
			id[n]=lst;
			cout<<n*id[n]<<"\n";
		}
		if(op=='+')
		{
			mp[n]++;
		}
	}
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

## 题解：CF1732D1 Balance (Easy version)
### 分析
观察到 $x$ 的范围很大，考虑用 map 当作桶标记 $x$。

对于第二种操作，枚举 $t$ 即可。

由于直接这么做会超时，所以对于相同的 $x$，如果上次枚举了就直接从上次的开始枚举。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
int n;
char op;
int t;
map<int,int> mp, id;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(cin>>t;t;t--)
	{
		cin>>op>>n;
		if(op=='?')
		{
			int lst=id[n];
			if(lst==0)
			{
				lst=1;
			}
			while(mp[n*lst])
			{
				lst++;
			}
			id[n]=lst;
			cout<<n*id[n]<<"\n";
		}
		else
		{
			mp[n]++;
		}
	}
}

---

