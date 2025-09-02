# Burenka and Traditions (hard version)

## 题目描述

This is the hard version of this problem. The difference between easy and hard versions is only the constraints on $ a_i $ and on $ n $ . You can make hacks only if both versions of the problem are solved.

Burenka is the crown princess of Buryatia, and soon she will become the $ n $ -th queen of the country. There is an ancient tradition in Buryatia — before the coronation, the ruler must show their strength to the inhabitants. To determine the strength of the $ n $ -th ruler, the inhabitants of the country give them an array of $ a $ of exactly $ n $ numbers, after which the ruler must turn all the elements of the array into zeros in the shortest time. The ruler can do the following two-step operation any number of times:

- select two indices $ l $ and $ r $ , so that $ 1 \le l \le r \le n $ and a non-negative integer $ x $ , then
- for all $ l \leq i \leq r $ assign $ a_i := a_i \oplus x $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). It takes $ \left\lceil \frac{r-l+1}{2} \right\rceil $ seconds to do this operation, where $ \lceil y \rceil $ denotes $ y $ rounded up to the nearest integer.

Help Burenka calculate how much time she will need.

## 说明/提示

In the first test case, Burenka can choose segment $ l = 1 $ , $ r = 4 $ , and $ x=5 $ . so it will fill the array with zeros in $ 2 $ seconds.

In the second test case, Burenka first selects segment $ l = 1 $ , $ r = 2 $ , and $ x = 1 $ , after which $ a = [0, 2, 2] $ , and then the segment $ l = 2 $ , $ r = 3 $ , and $ x=2 $ , which fills the array with zeros. In total, Burenka will spend $ 2 $ seconds.

## 样例 #1

### 输入

```
7
4
5 5 5 5
3
1 3 2
2
0 0
3
2 5 7
6
1 2 3 3 2 1
10
27 27 34 32 2 31 23 56 52 4
5
1822 1799 57 23 55```

### 输出

```
2
2
0
2
4
7
4```

# 题解

## 作者：Alex_Wei (赞：10)

> [CF1718A2 Burenka and Traditions (hard version)](https://www.luogu.com.cn/problem/CF1718A2)

考察长度除以 $2$ 上取整的性质，我们发现一次长度为 $L$ 的操作可以拆成 $\lfloor L / 2\rfloor$ 个长度为 $2$ 的操作和 $L\bmod 2$ 个长度为 $1$ 的操作。

如果长度为 $2$ 的操作包含长度为 $1$ 的操作，则可以拆成两个长度为 $1$ 的操作。因此得到如下性质：

- 操作长度 $1$ 或 $2$。
- 长度为 $1$ 的操作和长度为 $2$ 的操作不重叠。
- 长度为 $1$ 的操作之间不重叠，长度为 $2$ 的操作之间不完全重合，但可以相交。

考虑一段相邻相交的极长的连续的长度为 $2$ 的操作，设操作共有 $L - 1$ 次，则它覆盖了长度为 $L$ 的 $a_i$。易知操作合法当且仅当这段 $a_i$ 异或和为 $0$。

因此，从原序列中选出若干段异或和为 $0$ 的不相交的子段，则总代价即 $n$ 减去子段数量。只需最大化子段数量，简单贪心即可。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 5;
int n, a[N];
void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  int ans = n, S = 0;
  map<int, int> mp;
  mp[0] = 1;
  for(int i = 1; i <= n; i++) {
    S ^= a[i];
    if(mp.find(S) != mp.end()) {
      ans--;
      mp.clear();
      mp[S = 0] = 1;
    }
    else mp[S] = 1;
  }
  cout << ans << "\n";
}
int main() {
  ios::sync_with_stdio(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：SFlyer (赞：5)

[原题传送门](https://codeforces.com/contest/1718/problem/A2)

## 题目大意
> 你有长度为 $N$ 的一个序列 $A_1,A_2,A_3,\cdots A_N$。你可以进行这样的操作：
> 
> - 选择两个坐标 $l$ 和 $r$ （$1\le l,r \le N$）和一个非负整数 $x$ 将 $A_l,A_{l+1},A_{l+2}\cdots A_r$ 变为 $A_l⊕x,A_{l+1}⊕x,\cdots A_r⊕x$。需耗费 $\lceil \frac{r-l+1}{2} \rceil$ 秒。
>
> 问把序列中每个值都变为 $0$ 的最短时间。

## 0x01

因为 $l,r$ 的取法很多，我们就可以考虑那些 $l,r$ 的取值是肯定用不上的。

性质1：所有 $r-l+1>2$ 的取值是不需要的。

原因：

设 $r-l+1>2$。

如果 $2\mid r-l+1$，则需要 $\frac{r-l+1}{2}$ 秒，如果拆成 $\frac{r-l+1}{2}$ 个长度为 $2$ 的小段，时间一样，故不需要考虑 $r-l+1>2$ 且 $2\mid r-l+1$ 的取值。

如果 $2\nmid r-l+1$，则需要 $\frac{r-l+2}{2}$ 秒，如果拆成 $\frac{r-l}{2}$ 个长度为 $2$ 的小段和 $1$ 个长度为 $1$ 的小段，时间一样，故不需要考虑 $r-l+1>2$ 且 $2\nmid r-l+1$ 的取值。

## 0x02

如果有多个区间重合，会让答案算起来更复杂。因此，我们想要区间尽量不重合。

性质2：有一种方案，使得长度为 $1$ 的区间和长度为 $2$ 的区间不重合。

原因：

假设有一个长度为 $2$ 的区间和长度为 $1$ 的区间重合了。

发现可以直接把这一部分分成两个长度为 $1$ 的区间处理，效果相同。

## 0x03

性质3：假设有区间 $[l,r]$ 使 $A_l⊕A_{l+1}⊕\cdots ⊕A_r=0$，则可以 $r-l$ 秒把它们都变为 $0$。

原因：

考虑这样操作：

第一次选择区间 $[l,l+1]$，和 $x=A_l$；

第二次选择区间 $[l+1,l+2]$，和 $x=A_{l+1}$；

第三次选择区间 $[l+2,l+1+3]$，和 $x=A_{l+2}$；

$\cdots$

这样可以把 $A_l,A_{l+1},\cdots,A_r$ 都变为 $0$。

## 0x04

考虑用 DP 实现。

设 $dp_i$ 为把前 $i$ 个数都变为 $0$ 的最短时间。

### 1

对于每一个 $i$，都可以有
$dp_i=dp_{i-1}+1$，因为可以单独把 $A_i$ 变成 $0$，再加上前面消耗的代价。

### 2

根据性质3，还可以这样转移：

设 $lst$ 使 $A_{lst}⊕A_{lst+1}⊕\cdots ⊕A_i=0$，$dp_i=dp_{lst}+i-lst$。

[代码实现](https://www.luogu.com.cn/paste/761urcz3)

---

## 作者：Licykoc (赞：3)

首先给出结论：如果 $a_l \oplus a_{l+1} \oplus a_{l+2} \oplus ... a_r = 0$，那么我们可以花费 $r - l$ 的时间将 $a_l,...,a_r$ 置零。

考虑构造证明：设 $b_l = a_l, b_{l+1} = a_l \oplus a_{l+1},...,b_r = a_l \oplus a_{l+1} \oplus ... a_r$。同时记一次操作的形式为 $[l,r,x]$，表示对区间 $[l,r]$ 中的每个数异或上 $x$。如果 $b_r = 0$ ，那么操作序列为 $[l,l+1,b_l], [l+1,l+2,b_{l+1}], ... ,b[r-1,r,b_{r-1}]$ 。总次数为 $r-l$，每次花费为 $1$，总花费为 $r-l$。由此得证。

于是我们可以从左往右做，设 $f_i$ 表示将区间 $[1,i]$ 置零的最小花费。转移很简单：

$$f_i = \min(f_{i-1}, f_{mp_i} + i - (mp_i + 1))$$

其中 $mp_i$ 表示 $a_{mp_i} \oplus a_{mp_i+1} \oplus ... a_i = 0$ 。这个可以预处理。

具体实现：

```cpp
map<int,int> mp;
UP(i,1,n) read(a[i]),b[i]=a[i]^b[i-1];
mp.clear(); mp[0]=0;
UP(i,1,n) {
  f[i]=f[i-1]+(a[i]>0);
  if (mp.count(b[i])) 
    f[i]=min(f[i],f[mp[b[i]]]+i-(mp[b[i]]+1));
  mp[b[i]]=i;
}
printf("%d\n",f[n]);
```

---

## 作者：Masna_Kimoyo (赞：2)

## 前置知识 

一个在 CF 十分常用且显然的性质：

![](https://cdn.luogu.com.cn/upload/image_hosting/g5hlel0m.png)

下面是上面的子串。

当 $xorsum1 = xorsum2$ 时，字母串差的那一截的异或和为 $0$。

## 中置知识

主题还是得靠贪心来想。

首先一定不要想的复杂了，题目说的是每次操作代价是区间长度的一半向上取整，而不是 $1$。化简一下，每一步的决策就变成了，当前是只取这一个位置，还是多向后取一个。不需要考虑其他的，因为你会发现用 $1$ 和 $2$ 拼凑起来和其他取法是 **等价的** 。

按照题意，取的时候长度为 $1$ 和 $2$ 代价是相同的，那为了减少使用，肯定首选 $2$ ，但真正的“省“，还得是在这个区间异或和为 $0$ 的时候才能体现出来，除了最后一个数，每一个数都被异或了两遍，也就是并没有省。只是在最后一个数上省了 $1$ 个代价，因为这个数没有操作却跟着前面的数一起异或成了 $0$。

这时候就有了新问题，用哪个节点作为这个异或区间的开始我们并不知道，那岂不是要一个个往前找？

于是那个性质就有了作用：只要记录一个异或前缀和，当前前缀和如果发现在这之前有与其相等的，那就说明我们找到了一个和为 $0$ 的区间，也就相当于找到了起点，累加答案即可。

记录是否有相等的很容易，来个 `set` 就完事了。

## 后置知识

代码如下：

```cpp
#include<bits/stdc++.h>
#define printlf(x) print(x),putchar('\n')
#define printsp(x) print(x),putchar(' ')
using namespace std;
inline int read(){
    int x=0;
    bool w=0;
    char c=getchar();
    while(!isdigit(c))  w|=c=='-',c=getchar();
    while(isdigit(c))   x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void print(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) print(x/10);
    putchar('0'+x%10);
}
const int N=1e5+5;
int a[N];
inline int Solve(){
    int n=read();
    for(register int i=1;i<=n;++i)  a[i]=read();
    int now=0,ans=0;
    set<int> s;
    s.insert(0);
    for(register int i=1;i<=n;++i){
        now^=a[i];
        if(s.count(now))    s.clear(),ans++;
        s.insert(now);
    }
    return n-ans;
}
signed main(){
    int T=read();
    while(T--){
        printlf(Solve());
    }
    return 0;
}

```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1HB4y1L7qy)

### 2 思路

设 $dp_i$ 为解决从 $1$ 到 $i$ 所需要的时间。$dp_0=0$。

可以发现，若 $a_i=0$，$dp_i=dp_{i-1}$。

否则可以单独操作 $a_i$。$dp_i=dp_{i-1}+1$。

但是我们可以考虑另外一种情况。

设 $sum_i$ 为 $i$ 的前缀异或和。可以发现，如果 $sum_i=sum_l$ 且 $0\le l<i$，那么从 $a_{l+1}$ 到 $a_i$ 可以通过操作 $i-l-1$ 次来全部变成 $0$。具体来讲，是 $[l+1,l+2],[l+2,l+3],...,[i-1,i]$ 的操作。

那么 $dp_i$ 可以被更新为 $dp_l+i-l-1$。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
#define max_n 100000
#define inf 0x3f3f3f3f
int t;
int n;
int a[max_n+2];
int dp[max_n+2];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1718A2_1.in","r",stdin);
	freopen("CF1718A2_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		for(int i=1;i<=n;++i)dp[i]=inf;
		dp[0]=0;
		map<int,int>r;
		for(int i=1,sum=0,l;i<=n;++i){
			if(!a[i]){
				dp[i]=dp[i-1];
				r[sum]=i;
				continue;
			}
			dp[i]=min(dp[i],dp[i-1]+1);
			sum^=a[i];
			if(r.count(sum)){
				l=r[sum];
				dp[i]=min(dp[i],dp[l]+(i-l-1));
			}
			else{
				if(!sum)dp[i]=min(dp[i],i-1);
			}
			r[sum]=i;
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/84143844)

By **dengziyue**

---

## 作者：jucason_xu (赞：1)

### 重要性质

**任何一个选定区间长度为 $n$ 的操作，都可以划分成若干个长度为 $2$ 的操作** ，若 $n$ 是奇数，还要带一个长度为 $1$ 的区间。

我们发现，原来的操作花费的总时间为 $\lceil\frac{n}{2}\rceil$，现在每一次操作时间都是 $1$，区间个数为 $\lceil\frac{n}{2}\rceil$，花费的总时间相同！

这样，我们知道，任何操作均存在一个 $1$ 或 $2$ 操作序列和它等价，那么 **任何操作序列也都存在一个 $1$ 或 $2$ 操作序列和它等价** 。我们就可以只研究长度为 $1$ 或 $2$ 的操作序列。

### 算法讨论

接着，由于 $\oplus$ 运算满足交换律和结合律， **所以操作最终的结果和操作的顺序没有关系** 。那么我们就可以钦定所有的操作都是从左到右的。

然后，如果每次都只让每一个位置上的数异或上自己的话，就可以在恰好 $n$ 的代价下完成清零。所以最终答案一定小于 $n$。

接下来，由于我们的操作是从左到右的，那么我们就可以贪心的取， **每次把当前第一个不是 $0$ 的数异或上自己** ，把它变成 $0$ 即可。

为什么这样是最优的呢？我们之后再讲。

接下来，我们有两个选择：

+ 只让自己异或自己

+ 让自己和后一位一起异或上自己

这样就有两种结果：后一位是 $a_{i+1}$ 或 $a_{i}\oplus a_{i+1}$。

我们发现，如果用 $a_{i+1}$ 继续往下做就和原来一样，用 $a_{i}\oplus a_{i+1}$ 往下做，再有一位就会有 $a_{i}\oplus a_{i+1}\oplus a_{i+2}$。

通过每次清零上一位的时候把当前位异或上上一位，就可以 **把某一位修改为 $a_{[l,r]}$ 的异或和** 。当然还需要满足一个条件：在 $a_{l-1}$上的操作长度是 $1$，也就是区间前一位的操作没有改变 $a_l$。

当什么时候我们会减少操作呢？因为我们每次都需要把一位清零，所以当做到某一位的时候它本来就是 $0$，就能减少一次操作！

而这时候，目的就变成了： **找到若干个不相交的区间 $[l,r]$，使得每一个区间内的异或和等于 $0$，最大化区间个数** 。

这个就需要开一个 `map` 记录每一个前缀异或和的最后一次出现，然后记 $[1,i]$ 的前缀异或和为 $s_i$，若有 $s_i=s_j(j<i)$，那么区间 $[j+1,i]$的异或和就一定是 $0$。

通过 `map` ，为每一个 $i$ 贪心找到最大的 $j$，得到一个区间。因为 **长度更大但是右端点相同的区间一定不能和更多的区间共存** 。

同理，对于每一个区间左端点 $i$，只保留它最左边的右端点 $nxt_i$，然后就可以开始 DP 了。

设 $dp_i$ 为前 $i-1$ 个位置全部清零的最多节省操作次数。

转移：

$dp_i \Rightarrow dp_{i+1}$

$dp_i+1\Rightarrow dp_{nxt_{i}+1}$

最后访问 $dp_{n+1}$ 即可。

### 证明填坑

但是？

**我们还有一个把当前直接变成 $0$ 的最优性没有证明！**

证明这个的关键点在于：把 $x$ 改成 $y$ 至多只能为后面增加 $1$ 的贡献。

假如我们不是把当前值清成 $0$，而是清成别的什么，考虑其后面第一个操作在自身（也就是操作不影响后一个值的地方），在这里可能会有 $1$ 的贡献（原来这里不是 $0$，因为更改变成了 $0$），但是在这之后， **前面的一切操作都不能对其产生影响** 。

所以，在某一位不改成 $0$ 而是改成其他数的，最多只能增加 $1$ 的贡献，但是却一定存在 $1$ 的额外操作，所以一定不会更优。至于如果和后一个一起改了，其实和先把当前变成零再把后一个变成 $z$ 是等价的，不需要专门讨论。

```cpp

#include<bits/stdc++.h>
using namespace std;
#define rp(i,n) for(int i=1;i<=n;i++)
typedef long long ll;
int n,a[100005],xs[100005],dp[100005],ope[100005];
inline void solve(){
	map<int,int>lst;
	cin>>n;
	rp(i,n)cin>>a[i];
	rp(i,n)ope[i]=-1;
	lst[0]=0;
	rp(i,n){
		xs[i]=xs[i-1]^a[i];
		if(lst.count(xs[i])){
			int& val=lst[xs[i]];
			if(ope[val+1]==-1)ope[val+1]=i;
		}
		lst[xs[i]]=i;
	}
	rp(i,n+1)dp[i]=0;
	rp(i,n){
		if(ope[i]!=-1){
			dp[ope[i]+1]=max(dp[ope[i]+1],dp[i]+1);
		}dp[i+1]=max(dp[i+1],dp[i]);
	}
	cout<<n-dp[n+1]<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	rp(_,t)solve();
	return 0;
}
//Accepted!


---

## 作者：Zeardoe (赞：1)

题意：现有 $a$ 数组。每次你可以选择一个区间 $[l,r]$ 和一个整数 $x$ ，花费 $\lceil \frac{(r-l+1)}2\rceil$ 的代价，将其中所有数与 $x$ 取异或。问：至少需要多少代价，才能使 $a$ 数组所有元素均为 $0$ ？

观察：本题关键在于，其实只有两种基本操作（拆操作，找操作的本质）：

选择一个元素，将它异或上 $x$。
选择连续的两个元素，将它们异或上 $x$。
**每次操作的代价为 $1$**（好性质）

其余所有操作均可由以上基本操作组成，且代价不会升高。

分析：对于一个数组，一个上界是 $n$，也就是对每个元素都执行第一个操作。
另外，对于一串 $a_l \oplus ... \oplus a_r = 0$ 的 $[l,r]$，连续执行第二种操作可以省去一次操作过程。

因此，我们可以通过把序列划分成若干个孤点和若干个**极短的**异或为 $0$ 的连续子串，如：
```plain
11
27 27 34 32 2 1822 31 23 56 52 4
```
划分为
```
[27,27] [34,32,2] 1822 [31,23,56,52,4]
```

每划分一个子串，都可以减少 $1$ 的答案。

怎么找子串呢？上一个子串的结尾及其之前的数均不可再次包含在另一个子串中，对于上一个子串的结尾之后的数（在寻找范围内），（假设第一个数的下标为 $1$），我们用 map 记录其前缀异或和，若区间 $[l,r]$ 的异或和为 $0$，那么区间 $[1,l]$ 的异或和等于 $[1,r]$ 的异或和，也就是在计算出 $r$ 的前缀异或和的时候发现 map 中有此数据，那么就代表找到了一个这样的子串。

注意 $0$ 的代价为 $0$，应该立刻划分成孤点。

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i, a, b) for(int i = (a); i <= (b); i++)
#define cl(i, n) i.clear(),i.resize(n);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 1e9;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    //think twice,code once.
    //think once,debug forever.
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int ans = n;
        map<int, int> mp;
        mp[0] = 1;
        int tmp = 0;
        f(i, 1, n) {
            int a; cin >> a; tmp ^= a;
            if(mp.count(tmp)){
                ans--; mp.clear(); mp[0] = 1; tmp = 0;
            }
            else {
                mp[tmp] = 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Purslane (赞：1)

## Solution

有没有一种可能 , 我不配打 div 1 .

首先 , 操作的顺序没有影响 . 其次 , 我们看一看到底最优解是什么情况 .

比如一个端点 $r$ , 它现在有两个左端点与之对应 : $l_1$ 和 $l_2$ , 也就是说 $[l_1,r]$ 和 $[l_2,r]$ 被操作了 . 如果 $l_1=l_2$ , 那么显然合并到一起去 , 不然 , 我们会这样做 :

把这两个操作变成 $[l_1,l_2-1]$ 和 $[l_2,r]$ ( $l_1<l_2$ ) . 很容易发现 , 这样肯定更优 . 

对于左端点也可以做同样的操作 . 这样我们就知道 , 每个点最多作为左端点一次 , 最多作为右端点一次 .

我成功卡在这里了 . 进一步思考发现 , 如果两个区间的交长度大于等于 $2$ , 那么给分裂成三个区间肯定更优 . 所以 , 现在又多了一个条件 : 任何区间的交不会超过 $1$ .

然后我们发现 , 长度为 $k$ 的区间 , 拆成 $2,2,2,\dots,2(,1)$ 并不影响答案 , 所以 , 现在所有区间的长度又不超过 $2$ 了 .

是不是还是有点晕乎 ? 那么继续 : 如果一个长度为 $1$ 的区间包含在长度为 $2$ 的区间内 , 是不是拆成两个长度为 $1$ 的区间更优 ?

所以有多了个条件 : 任何长度为 $1$ 的区间都不和其它区间相交 .

现在画一画这个图 , 如果像图一样看待问题 , 你是不是就可以把区间的两个端点连起来 . 现在发现 , 一个合适的操作 , 化成图都是 点 + 链 的形式 !

考虑到一个链上 , 每次操作相邻两个数 . 仔细推敲一下可以发现 , 最后一个数肯定等于前面那些数的异或和 , 也就是说 , 这一段异或和等于 $0$ .

而我们知道 , 最劣答案肯定是 $n$ , 每个数操作一次 . 而一个链 , 可以减少一个贡献 .

所以 , 现在也就变成了 : 在一个序列上找最多的区间 , 使它们两两不交 , 且长度都大于等于 $2$ . 这是不是一个显然的 DP .

所以就写完了 !

code :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int T,n,pre[MAXN],a[MAXN],dp[MAXN];
void work(void) {
	cin>>n; ffor(i,1,n) cin>>a[i];	
	ffor(i,1,n) pre[i]=a[i]^pre[i-1];
	dp[0]=0; map<int,int> mp;
	mp[0]=0;
	ffor(i,1,n) {
		dp[i]=dp[i-1];
		if(mp.find(pre[i])!=mp.end()) dp[i]=max(dp[i],dp[mp[pre[i]]]+1);
		mp[pre[i]]=i;	
	}
	cout<<n-dp[n]<<'\n';
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T; while(T--) work();
	return 0;
}
```

本题难点在于贪心过程 . 下次多练贪心 .

---

## 作者：_Lazy_whr_ (赞：0)

显然贪心。

每次的代价是是区间长度除以 $2$ 再向上取整，也就是说每一步只会是取当前这个位置或是向后一个。

那么最坏情况下，操作次数会是 $n$，考虑如何将多余步骤减去。

容易发现，当一个区间 $[L, R]$ 满足 $a_L \oplus a_{L + 1} \oplus a_{L + 2} \oplus ... \oplus a_{R - 1} \oplus a_R = 0$ 时，就可以由每两个数进行一次操作 $2$，由此减少一次操作。

然而异或可以用前缀来维护，所以每一次发现当前的前缀和与之前有相等就相当于找到了起点，记录答案即可。

[AC Link](https://codeforces.com/problemset/submission/1718/309058550)

---

## 作者：OIer_Hhy (赞：0)

这道题，我们只需要看一个数的操作和两个连续数的操作就行了（代价均为  1）。

用一个 map 记录每个异或和是否出现过，当异或和出现过时，map 清零，把连续两个数同时异或为 0，亦将异或和清零。否则把这个异或和标记在 map 中。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int t,n,ans;
signed main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>t;
    while(t--) {
		cin>>n;
		ans=n;
        map<int,int> mp;
        mp[0]=1;
        int XOR=0;
        for(int i=1;i<=n;i++){
            int a;
			cin>>a;
			XOR^=a;
            if(mp.count(XOR)){
                ans--;
				mp.clear();
				mp[0]=1;
				XOR=0;
            }
            else mp[XOR]=1;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF1718A2%20Burenka%20and%20Traditions%20(hard%20version))

# 思路

首先可以将题目的操作转化为：

1. 将一个数 $a_i$ 异或一个常数 $k$。

2. 将连续两个数 $a_i,a_{i + 1}$ 同时异或一个常数 $k$。

那么，你发现最坏情况下，操作次数是 $n$。那么考虑如何将多余步骤给减去。

发现，如果一个区间 $[l,r]$，$\oplus_{i = l}^{r}a_i = 0$，就可以由每两个数进行一次操作 2，进而减少一次操作。

然后使这种区间的数量尽可能多即可。用 `map` 记录，简单贪心一下就好。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,ans,arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    int cnt = 0;
    map<int,bool> vis;
    n = ans = read(); vis[0] = true;
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1;i <= n;i++){
        cnt ^= arr[i];
        if (vis[cnt]){
            vis.clear(); vis[0] = true;
            ans--; cnt = 0;
        }
        else vis[cnt] = true;
    }
    printf("%d\n",ans);
}

int main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

一看到怎么有特色的花费，我们就要考虑一下了。很显然可以知道 $2n,2n-1$ 长的区间的花费是一样的。进一步地，$a(2n)+b(2n)$ 和 $(a+b)(2n)$（此次省略乘号）的花费也是一样的。于是我们就可以把各种操作变成两个基本操作的组合。

- 操作 $1$：选择一个长度为 $2$ 的区间操作，费用为 $1$。

- 操作 $2$：选择一个长度为 $1$ 的区间操作，费用为 $1$。

这固然是一个很好的开端。可是我们接下来该怎么样呢？难道我们要贪心地选择长度为 $2$ 的区间操作吗？可是我们的操作是把区间内的数都异或一个 $x$，贪心的选择长度为 $2$ 的区间操作，不代表和选择长度为 $1$ 的区间的操作数和一样。

换一个说法，就是对于一个区间 $[l,r]$，如果我们只执行操作 $2$，那么一定可以保证执行 $r-l+1$ 次后全 $0$，但是如果是执行了操作 $1$ 呢？要想执行的操作数小于 $r-l+1$ 貌似是一种很**特殊的情况**。

继续想下去，我们也许会想得很复杂……实际上，我们只有一种贪心的方法，那就是抓住上面的**特殊情况**来考虑。那就是对于区间 $[l,r]$，如果请假内的异或和为 $1$，那么我们就可以执行 $r-l$ 次操作 $1$ 而不是执行 $r-l+1$ 次操作 $2$。并且这样一定保证两种情况的结果都是区间 $[l,r]$ 的数字全变成了 $0$（我们分别对 $(l,l+1),(l+1,l+2),\dots,(r-1,r)$ 执行操作 $1$）。

提一下，如果区间 $[l,r]$ 的异或和为 $0$，且这个区间可以划分为若干个异或和为 $0$ 的子区间，那么我们选择继续划分。想想就知道了，因为每一个异或和为 $0$ 的区间都实际上可以减少一次我们的操作。

注意有一些数无论在哪个区间内都不可以使得异或和为 $0$，我们把这些数字单独提出来执行操作 $2$。对于 $0$，我们也单独提出来，不操作（但是不可以删去）。

---

那么怎么样找到异或和为 $0$ 的区间呢？我们知道异或和加法在前缀累计方面很像。记前缀异或和数组为 $qz$，若 $qz_r=qz_l$，那么说明 $[l+1,r]$ 的异或和就是 $0$。用 map 匹配实现即可，若学过 BSGS，就马上会明白（没错非常喜欢 BSGS 虽然有时比喻不当）。

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=1e6+15;
const int INF=1e18+5;
const int MOD=998244353;

int n,ans;

signed main() {
    int t=rd;
    while(t--) {
        map<int, int> mp;
        
    	n=ans=rd;
        mp[0] = 1;
        int qz = 0;//前缀异或和
        for(int i=1;i<=n;i++) {
            int a=rd;
			qz^=a;
            if(mp[qz]){
                ans--; 
				mp.clear(); 
				mp[0] = 1; qz = 0;
            }
            else mp[qz] = 1;
        }
        cout<<ans<<endl;
    }
    return 0;
}

```




---

## 作者：Cxny (赞：0)

## Solution

容易发现，将长度 $>2$ 的区间操作拆分成若干长度为 $1$ 或$2$ 的操作，一定能够得到不劣的答案。

对于单个点，我们只需要让它异或自己便可使其值变为 $0$，因此答案一定**不存在长度为 $1$ 的区间被长度为 $2$的区间完全包含。**

而最优解显然不会将同一段区间操作两次。

因此，最优解只有三种类型：

1. 长度为 $1$ 的操作。一定不与其他操作相交。
2. 长度为 $2$ 且不与其他操作相交。
3. 长度为 $2$ 的若干**相接**操作。（如 $[1,2],[2,3]$ 等。）

对于类型 $2$，我们可以将其看成仅有一个区间的类型 $3$。

而**极长**类型 $3$ 操作合法，**当且仅当区间内元素异或和为 $0$。**

设区间内元素为 $a_l,a_{l+1},\dots,a_r$，则：

由于该操作序列已经尽可能长，不存在与其左侧相接的操作。

因此，$a_l$ 想要变成 $0$，只能使其与 $a_{l+1}$ 共同异或 $a_l$。

以此类推。最终 $a_r$ 变为 $a_l\ \text{xor}\ a_{l+1}\ \text{xor}\dots\text{xor}\ a_r$，其取值为 $0$ 当且仅当区间内异或和为 $0$。

所以对于这样的区间，我们花费 $r-l$ 次操作就可以使其全部变为 $0$。

---

朴素 dp。

设 $f(i)$ 表示到第 $i$ 个数为止全变为 $0$ 所需最小代价，则有：
$$f(i)=\min\{f(i-1)+[a_i\neq0],f(j)+i-j\}$$
其中 $j<i$ 并且 $a_j\ \text{xor}\ a_{j+1}\ \text{xor}\dots\text{xor}\ a_i=0$。

对于每个 $i$，向前枚举 $j$ 即可。

时间复杂度 $O(n^2)$，可以通过 [Easy Version](https://www.luogu.com.cn/problem/CF1718A1)。

---
考虑优化。

我们发现向前枚举时浪费了很多时间。

由于异或满足结合律，若处理出异或的前缀和 $sum_i$，则对于满足条件的 $j$，有 $sum_i=sum_{j-1}$。

而更新答案时只有 $f(j)$ 与 $j$ 两项与 $j$ 有关。

因此，可以使用 map 将异或和映射到 $f(j)-j$，这样时间复杂度优化为 $O(n\log n)$，可以通过本题。注意细节。

```cpp
int T, n, a[maxn], dp[maxn];
int sum[maxn] = {0};
map<int, int> mp;
int main(){
	scanf("%d", &T);
	while(T--){
		mp.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i - 1] ^ a[i];
		fill(dp + 1, dp + n + 1, inf);
		dp[0] = 0, mp[0] = -1;
		for(int i = 1; i <= n; i++){
			if(a[i]) dp[i] = dp[i - 1] + 1;
			else dp[i] = dp[i - 1];
			if(mp.count(sum[i]))
				dp[i] = min(dp[i], mp[sum[i]] + i), mp[sum[i]] = min(mp[sum[i]], dp[i] - i - 1);
			else mp[sum[i]] = dp[i] - i - 1;
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}
```


---

