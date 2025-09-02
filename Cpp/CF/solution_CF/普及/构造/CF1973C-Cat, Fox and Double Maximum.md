# Cat, Fox and Double Maximum

## 题目描述

Fox loves permutations! She came up with the following problem and asked Cat to solve it:

You are given an even positive integer $ n $ and a permutation $ ^\dagger $ $ p $ of length $ n $ .

The score of another permutation $ q $ of length $ n $ is the number of local maximums in the array $ a $ of length $ n $ , where $ a_i = p_i + q_i $ for all $ i $ ( $ 1 \le i \le n $ ). In other words, the score of $ q $ is the number of $ i $ such that $ 1 < i < n $ (note the strict inequalities), $ a_{i-1} < a_i $ , and $ a_i > a_{i+1} $ (once again, note the strict inequalities).

Find the permutation $ q $ that achieves the maximum score for given $ n $ and $ p $ . If there exist multiple such permutations, you can pick any of them.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first example, $ a = [3, 6, 4, 7] $ . The array has just one local maximum (on the second position), so the score of the chosen permutation $ q $ is $ 1 $ . It can be proven that this score is optimal under the constraints.

In the last example, the resulting array $ a = [6, 6, 12, 7, 14, 7, 14, 6] $ has $ 3 $ local maximums — on the third, fifth and seventh positions.

## 样例 #1

### 输入

```
4
4
1 2 3 4
4
4 3 1 2
6
6 5 1 4 2 3
8
1 2 4 5 7 6 8 3```

### 输出

```
2 4 1 3
3 1 4 2
2 5 1 4 3 6
5 4 8 2 7 1 6 3```

# 题解

## 作者：gan1234 (赞：15)

巧妙构造题。

显然我们可以构造排列 $q$ 使得所有 $p_i+q_i=n+1$。

这样可以先让所有数相等，方便我们构造。

我们可以令 $q$ 所有偶数位置加一，奇数位置不变，显然这是我们最多只能有这么多局部最大值。

但是这不符合 $q$ 所有元素不重复的要求，考虑去重。

由于重复元素是由于偶数位置的数增大导致的，那么一定有原本较小的数没有使用。

因此我们可以用这些较小数来替换奇数位置重复的数，显然这并不会影响局部最大值的数量。

直接将这些没有使用的数排序，把奇数位置的数也排序，按排名依次替换即可。

这里有一个问题，如果偶数位置上存在 $n$ 导致其无法加一，怎么办？

依旧按上面的构造方式，奇偶互换即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
int n;
int a[MAXN],b[MAXN];
int pos[MAXN],book[MAXN];
vector<int>v;
void work(){
	v.clear();
	memset(book,0,sizeof(book));
	cin>>n;
	for(int i=1;n>=i;i++)cin>>a[i];
	int pp=0;
	for(int i=1;n>=i;i++){
		b[i]=n+1-a[i];
		if(!(i&1)&&b[i]==n)pp=1;
	}
	for(int i=2-pp;n>=i;i+=2)
		if(b[i]<n)b[i]++,book[b[i]]=1;
	for(int i=1+pp;n>=i;i+=2)v.push_back(b[i]),pos[b[i]]=i;
	sort(v.begin(),v.end());
	
	int t=1;
	for(auto i:v){
		if(book[i]){
			while(book[t])t++;
			b[pos[i]]=t;
			book[t]=1;
		}else book[i]=1;
	}
	for(int i=1;n>=i;i++)cout<<b[i]<<" ";
	cout<<endl;
}
int main(){
	int _T;
	cin>>_T;
	while(_T--)work();
	return 0;
}
```

---

## 作者：Robin_kool (赞：3)

思路是赛时瞎想的，可能会存在有漏洞的情况，但是大致方向应该是正确的。

我们肯定要让奇数位或偶数位上的数字尽量大。

如果一个位置我们让他变成了 $n+2$，不难看出，肯定存在至少 $1$ 种的构造方案使得当前位置产生贡献。这是本题的突破口之一。

那么什么数在不考虑之前方案的情况下一定不能等于 $n+2$ 呢？$1$。

现在 $1$ 的位置的奇偶性和我们想要产生贡献的位置的奇偶性应该恰好相反。于是乎，记录下 $1$ 的位置，然后大力把能够赋值的都赋值（其实都可以，因为没有 $1$ 和重复数字）。

再考虑最小化其余位置的值，且让他们标准差最小（就是最接近）。

可以倒序枚举没有修改过的值 $i$，注意不是位置。找出当前未使用且最小的 $j$，给它加上，这样做一定是最优秀的，证明显然。

没有问最小值，输出之前保存的答案即可。

复杂度单次 $O(n)$。

---

## 作者：Cute__yhb (赞：2)

## 思路

一个很显然的性质，如果 $i$ 满足条件，那么 $i-1$ 和 $i+1$ 一定不满足条件。

基于这一点，只需要看所有奇数位和所有偶数位即可。

再考虑一点，$1+n=n+1$，所以，如果 $1$ 与 $n$ 相邻，那么 $1$ 那一位肯定不满足条件。

由此可知，带 $1$ 的那一位肯定可以不选。

这样，就能确定是奇数位还是偶数位。

然后，把确定的满足条件的数存下来，利用贪心的思想，把 $n$ 个数中的较大的那些数分给它们。

具体做法是，把这些数由小到大排序，设置一个变量 $tot$，初始值为 $n$，遍历这些数，令 $q_i=tot$，然后 $tot$ 自减。

剩下的数做法同上，但选的数是小于当前 $tot$ 的数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define re register
#define ri register int
#define rll register long long
#define ld long double
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define nep(i,a,b) for(int i=(a);i>=(b);i--)
#define popcount __builtin_popcount
#define pb push_back
#define mem(a,x) memset((a),x,sizeof(a))
#define eps 1e-8
#define oper operator
#define mk make_pair
int n,a[100005],cnt=0,ans[100005];
struct node{
	int val,id;
}b[100005];//存数
bool cmp(node x,node y){//从小到大
	return x.val<y.val;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	bool f=0;
	for(int i=1;i<=n;i+=2){
		if(a[i]==1){//有1
			f=1;
			break;
		}
	}
	if(f){//偶数位
		cnt=0;
		for(int i=2;i<=n;i+=2){//满足条件
			cnt++;
			b[cnt].val=a[i];
			b[cnt].id=i;
		}
		sort(b+1,b+1+cnt,cmp);//排序
		int tot=n;
		for(int i=1;i<=cnt;i++){//填数
			ans[b[i].id]=tot;
			tot--;//自减
		}
		cnt=0;
		for(int i=1;i<=n;i+=2){//剩下的数
			cnt++;
			b[cnt].val=a[i];
			b[cnt].id=i;
		}
		sort(b+1,b+1+cnt,cmp);//排序
		for(int i=1;i<=cnt;i++){//填数
			ans[b[i].id]=tot;
			tot--;//自减
		}
	}else{//奇数位，过程同上
		cnt=0;
		for(int i=1;i<=n;i+=2){
			cnt++;
			b[cnt].val=a[i];
			b[cnt].id=i;
		}
		sort(b+1,b+1+cnt,cmp);
		int tot=n;
		for(int i=1;i<=cnt;i++){
			ans[b[i].id]=tot;
			tot--;
		}
		cnt=0;
		for(int i=2;i<=n;i+=2){
			cnt++;
			b[cnt].val=a[i];
			b[cnt].id=i;
		}
		sort(b+1,b+1+cnt,cmp);
		for(int i=1;i<=cnt;i++){
			ans[b[i].id]=tot;
			tot--;
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';//输出
	puts("");
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：hsy8116 (赞：1)

## 题意简述

[link: 题面](https://codeforces.com/problemset/problem/1973/C)

给定长度为 $n$ 的排列 $p$，构造另一长度为 $n$ 的排列 $q$，使得新序列 $a$ $(a_i = p_i + q_i)$ 有最多的局部最大值，求任意 $q$。

局部最大值是指对于一个位置 $i (1 \lt i \lt n)$，$a_i \gt a_{i-1}$ 且 $a_i \gt a_{i+1}$。

## 题目分析

### 思路过程

由于局部最大值严格大于两边，所以 $a$ 序列中相邻两个数不可能都是局部最大值，那么，长为 $n$ 的 $a$ 序列中最多有 $\frac{n}{2}$ 个局部最大值。

由于 $p$ 和 $q$ 都是长度为 $n$ 的排列，所以将 $p$ 设为 $p = \{1,2,\dots,n\}$，将 $q$ 设为 $q = \{n,n-1,\dots,1\}$ 后，$a$ 序列的每个数都为 $n + 1$。

考虑在这个基础之上构造，使 $a$ 序列的偶数位都增加 $1$，这样成功构造了有 $\frac{n}{2}$ 个局部最大值的序列。那么对应的 $q$ 的偶数位都要加 $1$，(若 $q$ 的偶数位上有 $n$ 这个数，我们考虑在奇数位上构造，避免越界)，这时，我们不再能保证 $q$ 是个排列，$q$ 的某些位可能会重复。原因就是被加 $1$ 的偶数位占了位置，而它们本来的位置空了出来。我们考虑将被占奇数位调整到空位上，即可完成对 $q$ 的构造。

_对奇数位的构造也类似，这里只解释偶数位了。_

### 实现与证明

具体实现上，先算出 $q$ 的初始状态，然后考虑先让 $q$ 中偶数位改变后的值占位，用 `vis` 打标记。之后将 $q$ 的奇数位放入 `vector` 中排序，从小到大地枚举 `vector` 中的数，若本来的位置没被占，就可以直接打标记占领这个位置；若被占，则寻找目前没被占领的最小数去占领，并改动对应的 $q$ 中的值。

为什么从小到大排序配位置正确？

考虑对被占位的奇数位的数字 $x$，$x - 1$ 可能空了出来，若还是被占位，$x - 2$ 可能空了……所以每个被占位的数，总会有一个比它小的数留给它，从小到大枚举奇数位的数，找到的替代位必然小于这个数，所以 $a$ 序列奇数位这些不该变大的位不会变大，只会变小，满足题意。

## $Code$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const int NR = 1e5 + 10;
int p[NR], q[NR];
int vis[NR], pos[NR];
vector<int> v;

int main()
{
	int T;
	scanf("%d", &T);
	while (T --)
	{
		memset(vis, 0, sizeof(vis));
		v.clear();
		int n;
		scanf("%d", &n);
		int flag = 0; // 判断偶数位是否有 n 而导致 q 数组越界
		for (int i = 1; i <= n; i ++)
		{
			scanf("%d", &p[i]);
			q[i] = n + 1 - p[i];
			if (i % 2 == 0 && q[i] == n) flag = 1;
		}
		// 需要 +1 做贡献的位
		for (int i = 2 - flag; i <= n; i += 2)
		{
			q[i] ++;
			vis[q[i]] ++;
		}
		// 其余（可能）需要调整的位
		for (int i = 1 + flag; i <= n; i += 2)
		{
			v.push_back(q[i]);
			pos[q[i]] = i;
		}
		sort(v.begin(), v.end());
		int avb = 1; // 不断用来查找从 1 开始可用的位，相当于指针
		for (int i = 0; i < (int)v.size(); i ++)
		{
			if (vis[v[i]])
			{
				// 这个位置已经被占，需要调整
				while (vis[avb]) avb ++;
				q[pos[v[i]]] = avb;
				vis[avb] = 1;
			}
			else
			{
				// 这个位置没有被占，占领这里
				vis[v[i]] = 1;
			}
		}
		for (int i = 1; i <= n; i ++)
		{
			printf("%d ", q[i]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：linyuhuai (赞：1)

[更好的阅读体验。](https://by505244.github.io/oi_blogs/2024/05/22/cf1973c/)

### 题意：

给定长度为 $n$ 且 $n$ 为偶数的**排列** $a$，构造出一个排列 $b$，使得对于序列 $c$，有 $c_i=a_i+b_i$ 且满足 $c_{i-1}<c_i<c_{i+1},i\in(1,n)$ 的 $i$ 的数量最多。



### 解法：

因为没有连续的两个 $c_i$ 可以满足题目的条件，所以最多存在 $\frac n 2 - 1$ 个 $i$。

因为 $n$ 属于偶数，所以在 $c$ 中，按照小的数和大的数交错构造时（如 $3,5,2,4,2$），会发现构造出来的数的个数为奇数，那么中间可以而外插入一个小的数（如 $3,5,2,[1],4,2$）。

这就意味着我们有一次“反悔”的机会。

一种明显的构造方法，先将偶数位作为“大数”分配尽可能大的值，奇数位反之。

容易发现当偶数位存在 $1$ 且奇数位存在 $n$ 时，是无法构造合法方案的。（最大给 $1$ 分配给 $n$，而 $n$ 最小只能分配到 $1$，二者相等）

考虑到有一次反悔机会，所以把 $1$ 跳过即可。

然后将选出来将要成为“大数”中越小的数分配越大的值，“小数”中越大的数分配越小的值。

至于为什么这样就是对的，下面是简单的证明。

考虑最坏情况，即“大数”中的数为 $2,3,\dots,\frac n 2$，“小数”中的数为 $1,\frac n 2 + 1,\frac n 2 + 2,\dots,n$。

此时把“大数”中的 $2$ 加上 $n$，$3$ 加上 $n-1,\dots ,\frac n 2$ 加上 $\frac n 2 + 2$。那么“大数”中的数均为 $n + 2$。

“小数”中的 $1$ 加上 $\frac n 2+1$，$\frac n 2 + 1$ 加上 $\frac n 2$，$\frac n 2 + 2$ 加上 $\frac n 2 - 1$，$\dots$。那么“小数”中的数除了第一个数以外均为 $n + 1 < n + 2$​。

证毕。

[code.](https://by505244.github.io/oi_blogs/2024/05/22/cf1973c/#%E4%BB%A3%E7%A0%81)

---

## 作者：wfc284 (赞：0)

我们发现极值最多可能会有 $\frac{n}{2}- 1$ 个，即偶数位全部为极值，且去除第 $n$ 个。  
 
我们将偶数位的数存一起（$\{va_{\frac{n}{2}}\}$），奇数位的数存一起（$\{vb_{\frac{n}{2}}\}$），分别排序。  
若 $vb$ 中有数 $n$，那么交换 $va,vb$。  
$va$ 中的数，从小到大枚举，依次将对应位的 $q$ 赋为 $n,n-1,\dots,\frac{n}{2}+1$。  
$va$ 中的数，从大到小枚举，依次将对应位的 $q$ 赋为 $1,2,\dots,\frac{n}{2}$。 

考虑证明。  
加上了 $\{q\}$ 之后，$vb$ 中的数是一定小于等于 $n$ 的。因为不含数 $n$，就无法取到 $n+1$。即使 $n-1$ 也在里面，它加上的数最多是 $1$，无法到达 $n+1$，以后同理。  
加上 $\{q\}$ 之后，平均值是 $n+1$，故 $va$ 中的数全是大于等于 $n+2$ 的，于是就有所有偶数位大于奇数位，显然正确。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
#define multi_cases 1

namespace Traveller {
	const int N = 1e5+2;
	
	int n, a[N];
	int p[N];
	vector<pii> va, vb;
	
	void main() {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		va.clear(), vb.clear();
		for(int i = 2; i <= n; i += 2) va.emplace_back(a[i], i);
		int flag = 0;
		for(int i = 1; i <= n; i += 2) vb.emplace_back(a[i], i), flag |= a[i] == n;
		if(flag) swap(va, vb);
		sort(all(va)), sort(all(vb), greater<pii>());
		int c1 = n, c2 = 1;
		for(auto [x, i] : va) p[i] = c1--;
		for(auto [x, i] : vb) p[i] = c2++;
		for(int i = 1; i <= n; ++i) printf("%d ", p[i]);
		puts("");
	}
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller::main();
	return 0;
}
```

---

## 作者：KevinHu0402 (赞：0)

这是一道**构造**题。

[传送门](https://www.luogu.com.cn/problem/CF1973C)

## 题目分析

这道题需要通过一个排列 $p$ 来构造另一个排列 $q$。
首先我们可以先不考虑局部最大值如何构造，先考虑将数组 $a$ 和构造数组合并构成一个每个元素大小为 $n+1$ 的新数组，如图所示：


![](https://cdn.luogu.com.cn/upload/image_hosting/fmxfk7dl.png)

然后我们就可以通过交换构造数组的位置来使之满足题目要求了。具体如何实现，看下面我的代码和以下说明：


```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000005;
int a[maxn], pac[maxn];
int ans[maxn];

void solve(int n) {
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pac[n + 1 - a[i]] = i;
    }

    int sum = pac[n] % 2;
    ans[pac[n]] = n;

    for (int i = 1; i < n;) {
        if (pac[i] % 2 == sum) {
            ans[pac[i]] = i;
            i++;
            continue;
        }

        int j = i + 1;
        while (j <= n && pac[j] % 2 != sum) j++;

        for (int k = i; k < j; k++) {
            ans[pac[k]] = k + 1;
        }
        ans[pac[j]] = i;

        i = j + 1;
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        solve(n);
        for (int i = 1; i <= n; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}

```


- `a`: 存储输入的整数数组。
- `pac`: 用于存储位置映射，`pac[n + 1 - a[i]]` 表示某个值在数组中的位置。
- 计算 `sum` 为 `pac[n]` 的奇偶性。
- 遍历从 `1` 到 `n` 的所有值，检查每个 `pac[i]` 的奇偶性与 `sum` 是否相同。
- 如果相同，则直接将 `ans[pac[i]]` 设置为当前 `i`。
- 如果不同，则找出后续直到遇到下一个相同奇偶性的索引 `j`，并更新相应的 `ans` 值。

这样题目就结束了，还是比较简单的（虽然我赛时没过……）

---

## 作者：Engulf (赞：0)

若 $a_i$ 是局部最大值，那么 $a_{i - 1}$ 和 $a_{i + 1}$ 不可能是局部最大值。这启发我们只需考虑两种情况，比如下面这个数组的红色部分：

$$[1, \color{red}2\color{black}, 4, \color{red}5\color{black}, 7, \color{red}6\color{black}, 8, 3]$$

$$[1, 2, \color{red}4\color{black}, 5, \color{red}7\color{black}, 6, \color{red}8\color{black}, 3]$$

每次贪心地赋值，为了让红色部分的数尽可能大过两边的数，我们不难想到如下策略：

- 不成为局部最大值的数（黑色的数）中，越大，我们赋越小的权值。
- 可能成为局部最大值的数（红色的数）中，越小，我们赋越大的权值（跟上面那个其实是一样的）。从小到大，先黑再红。

为什么这样是对的？

考虑最坏的情况（对于 $1$ 来说这样构造不行，但因为我的实现中是做了两遍，这不影响最终的结果），我们希望 $2, 3, 4 \cdots \frac{n}{2}$ 成为局部最大值，$1, \frac{n}{2},\frac{n}{2} + 1 \cdots n$ 不是，按照构造方法，希望变成局部最大值的数是 $2+n,3+n - 1,4+n-2 \cdots \frac{n}{2} + \frac{n}{2} + 2$，都是 $n+2$，不成的数变为 $1+\frac{n}{2} + 1,\frac{n}{2} + 1 + \frac{n}{2} \cdots n + 1$，除了 $1$ 变成 $\frac{n+4}{2}$ 以外都是 $n + 1$，当然都是 $<n+2$，即局部最大值的数，咋放答案都是 $\frac{n-2}{2}$。

用 \dfrac 的话显示出来挤成一坨了，换成了 \frac。


```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        auto query = [&](bool swapped) {
            vector<int> p(n);

            vector<pii> v[2];

            for (int i = 0; i < n; i++)
                v[(i & 1) && (i < n - 2)].emplace_back(a[i], i);

            for (int i = 0; i <= 1; i++)
                sort(v[i].begin(), v[i].end(), [](const pii &x, const pii &y) {return x.first > y.first;});

            int num = 0;
            for (int i = 0; i <= 1; i++)
                for (int j = 0; j < v[i].size(); j++)
                    p[v[i][j].second] = ++num;

            int res = 0;
            for (int i = 1; i < n - 1; i++)
                if (a[i] + p[i] > a[i - 1] + p[i - 1] && a[i] + p[i] > a[i + 1] + p[i + 1])
                    res++;

            if (swapped) reverse(p.begin(), p.end());
            return make_tuple(res, p);
        };

        auto x = query(0);
        reverse(a.begin(), a.end());
        auto y = query(1);

        if (get<0>(x) < get<0>(y)) swap(x, y);
        for (int i = 0; i < n; i++) cout << get<1>(x)[i] << " \n"[i == n - 1];
    }
    return 0;
}
```

---

## 作者：AKPC (赞：0)

为了做出相邻数字的反差，显然考虑全部让奇或者偶位在两边都有数的情况下满足条件。

然而，当选择的 $a_i\geq2$，无论相邻的数多大，都有方案可以满足条件，因为数列是排列，所以不会出现同样的数字，这也导致了一定存在 $\frac{n}{2}-1$ 个满足条件的位置。

因为我懒，所以给奇、偶数位分别搞一次决定答案最大的那个。

[code](https://www.luogu.com.cn/paste/149k1508)。

---

