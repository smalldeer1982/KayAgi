# Sums on Segments

## 题目描述

### 题目内容
给定一个长度为 $n$ 的数组 $a$，其中除了至多一个 $i \in [0,n)$ 满足 $|a_i| \neq 1$ 以外，其余全部项均满足 $|a_i|=1$。

求该数组中全部可能的子数组和，以升序输出。子数组是原数组中一段连续的数组。

## 样例 #1

### 输入

```
5
5
1 -1 10 1 1
5
-1 -1 -1 -1 -1
2
-1 2
2
7 1
3
1 4 -1```

### 输出

```
8
-1 0 1 2 9 10 11 12 
6
-5 -4 -3 -2 -1 0 
4
-1 0 1 2 
4
0 1 7 8 
6
-1 0 1 3 4 5```

# 题解

## 作者：Eous (赞：13)

## 题意

给你一个长度为 $n$ 的数组 $a$，满足 $a$ 中有且仅有一个不为 $1$ 也不为 $-1$ 的数（以下简称特殊的值），剩余的数都是 $1$ 或 $-1$。求所有可能的子区间的和的值（下文简称答案）。从小到大一次输出每一个值，每个值只输出一遍。

## 题解

首先，我们发现，如果把那个特殊的值考虑进来不那么好搞，而又“有且仅有一个不为 $1$ 也不为 $-1$ 的数”，于是我们考虑把 $a$ 数组从那个特殊的值那里分成两段，他左边的成一段，他右边的另成一段，他自己提出来。然后我们就从考虑一个大问题分成了三个子问题：左边区间的所有可能的子区间的和的值，右边区间所有可能的子区间的和的值，包含特殊的值的所有可能的子区间的和的值。

### 左边区间 & 右边区间

这里有个不怎么显然的结论：在一个值域为 $\{1,-1\}$ 的数组里，设他的最大子段和是 $a$，最小子段和是 $b$。那么，有且仅有属于 $[b,a] \cap \mathbb{Z}$ 的数是答案，且这个集合里的每一个数都是答案。有了这个结论，左边区间的答案和右边区间的答案都好求了，但是，结论固然得证，所以我们就来证这个结论。

我们找到能造成最大子段和 $a$ 的区间，然后，将它分成 $a$ 个和为 $1$ 的子区间，能够证明一定有分法。然后，如果我们想得到和为 $a - 1$ 的子区间，我们只需要从左边或者右边去掉一个和为 $1$ 的子区间就能得到。对于 $a - 2,a - 3, \cdots 1$ 都可以用这种方法得出。于是我们就证得属于 $[1,a] \cap \mathbb{Z}$ 的数一定是答案。如法炮制，我们也能证出属于 $[b,-1] \cap \mathbb{Z}$ 也一定是答案。最后并上一个 ${0}$，就得到了 $[b,a] \cap \mathbb{Z}$。这样我们就成功的求出了左边区间和右边区间的答案。

### 包含特殊值的区间

也是如法炮制，不过因为要包含特殊值，所以就不能简单的求最大（小）字段和，要求最大（小）前（后）缀和。对于左边区间就是后缀，对于右边，就是前缀。然后我们设左边的最大后缀和是 $max_{1}$，最小后缀和是 $min_{1}$。右边的最大前缀和是 $max_{2}$，最小前缀和是 $min_{2}$，那么包含特殊值的区间的答案区间就是 $[min_{1} + min_{2} + val,max_{1} + max_{2} + val] \cap \mathbb{Z}$。这里 $val$ 指特殊值。

## code

```cpp
#include<bits/extc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 5;
int n,val,pos,sum;
int max1,min1,max2,min2;
int a[maxn],dp1[maxn],dp2[maxn];
void solve()
{
    cin >> n;
    pos = val = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] != 1 && a[i] != -1)
        {
            val = a[i];
            pos = i;
        }
    }
    max1 = min1 = 0;
    fill(dp1 + 1,dp1 + n + 1,0);
    fill(dp2 + 1,dp2 + n + 1,0);
    for (int i = 1; i <= pos - 1; i++)   
    {
        dp1[i] = max(dp1[i - 1] + a[i],0ll);
        max1 = max(max1,dp1[i]);//求左边区间的最大子段和
        dp2[i] = min(dp2[i - 1] + a[i],0ll);
        min1 = min(min1,dp2[i]);//求左边区间的最小子段和
    }
    max2 = min2 = 0;
    fill(dp1 + 1,dp1 + n + 1,0);
    fill(dp2 + 1,dp2 + n + 1,0);
    for (int i = pos + 1; i <= n; i++)
    {
        dp1[i] = max(dp1[i - 1] + a[i],0ll);
        max2 = max(max2,dp1[i]);//求右边区间的最大
        dp2[i] = min(dp2[i - 1] + a[i],0ll);
        min2 = min(min2,dp2[i]);//求右边区间的最小
    }
    set<int>ans;
    for (int i = min(min1,min2); i <= max(max1,max2); i++)
        ans.insert(i);//先把不包含val的值加入
    max1 = min1 = sum = 0;
    for (int i = pos - 1; i >= 1; i--)
    {
        sum += a[i];
        max1 = max(max1,sum);//求左边区间的最大后缀和
        min1 = min(min1,sum);//求左边区间的最小后缀和
    }
    max2 = min2 = sum = 0;
    for (int i = pos + 1; i <= n; i++)
    {
        sum += a[i];
        max2 = max(max2,sum);//如法炮制
        min2 = min(min2,sum);
    }
    for (int i = (min1 + min2); i <= (max1 + max2); i++)
        ans.insert(val + i);//记录答案
    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

upd:更新几处笔误

---

## 作者：HetmesAskalana (赞：2)

## 题意
给定一个长度为 $n$ 的数 $a$，其中除了至多一个 $i \in [0,n)$ 不满足 $|a_i|=1$ 以外，其余全部项均满足该条件。

求该数列中全部可能的子数列和，以升序输出。

## 题解
首先，STL 中的集合模板具有去重和自动排序的性质，所以我们可以先声明一个答案集合，由于空数组也算子数组，我们为其插入初值 $0$。

不难看出，因为 $|a_i|=1$，设子数列是任意 $i$ 位置上长度为 $m$ 的邻域，那么扩张子数列时对子数列和的影响步长均为 $1$。所以我们只需要求出一个区间内的最大值和最小值，更新 $[min,max] \cap \Z$ 至答案。

而因为 $|a_i| \neq 1$ 的项不多于一个，我们不妨将数列分为两种情况处理。

### $k$ 不存在时
只需按照下文第一种情况求整个数组的极值并添加该区间至答案即可。
### $k$ 存在时
由于 $x \in [-10^9,10^9]$，并不能完全确定，我们不妨将子数组分为两类：包含 $x$ 的和不包含 $x$ 的。

其中，不包含 $x$ 的可以通过下文第一种分别求 $x$ 的左、右两个方向不包含 $x$ 的区间内的最大、最小值；再通过下文第二种方法求所有包含 $x$ 的区间的最大、最小值。

### 处理方式
#### 只存在 $|a_i|=1$ 的区间
由于步长均为 $1$，为了保证求出全部子序列和中和的最大、最小值，我们不妨将两个值的初值均设置为 $0$，并将最小值限制为 $min \leq 0$，最大值同理，限制为 $0 \leq max$，每次越界时将该值重置为 $0$。

#### 包含 $x$ 的区间（ $k$ 存在时）
从 $i=k$ 开始向左、右扩张子数列，求出 $x$ 在数组 $a$ 中的左、右邻域的最大、最小值，之后将两个最大值和两个最小值分别相加，再加上 $x$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

void proc(vector<int> &a, int &tmp1, int &tmp2, int &minx, int &maxx, int i, bool can = false){ // 执行部分，因为重复拎出来防止两个函数过长，can 代表是不是只有 ±1，只有的话需要限制 tmp 的范围
    tmp1 += a[i];
    tmp2 += a[i];
    if(can){
        if(tmp1 > 0) tmp1 = 0;
        if(tmp2 < 0) tmp2 = 0;
    }
    minx = min(tmp1, minx);
    maxx = max(tmp2, maxx);
}

array<int, 2> mm(vector<int> &a, int l, int r){ // 用于处理只包含 ±1 的子数组的最大最小值，并返回一个可以直接传递给 merge() 的区间
    int minx = 0, maxx = 0, tmp1 = 0, tmp2 = 0;
    for(int i = l; i <= r; ++i)  proc(a, tmp1, tmp2, minx, maxx, i, 1);
    return {minx, maxx};
}

array<int, 2> mx(vector<int> &a, int k){ // 用于分别处理 x 在 a 中的左右邻域总和的最大最小值
    int minx = 0, maxx = 0, tmp1 = 0, tmp2 = 0;
    int r1 = 0, r2 = 0;
    for(int i = k - 1; i >= 0; --i) proc(a, tmp1, tmp2, minx, maxx, i);
    r1 += minx, r2 += maxx;
    tmp1 = tmp2 = minx = maxx = 0;
    for(int i = k + 1; i < a.size(); ++i) proc(a, tmp1, tmp2, minx, maxx, i);
    r1 += minx; r2 += maxx;
    return {r1 + a[k], r2 + a[k]};
}

void merge(set<int>& R, array<int, 2> range){ // 用于将[l，r]区间内的所有整数加入答案 R 中
    auto [l, r] = range;
    for(int i = min(l, r); i <= max(l, r); ++i) R.insert(i);
}

void solve(){
    int n, k = -1;
    cin >> n;
    vector<int> a(n);
    set<int> R = {0}; // 记得初始化一个 0 进去防止翻车，因为空数组也算子数组。
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        R.insert(a[i]); // 长度为1的子数组也算子数组
        if(abs(a[i]) != 1) k = i; // 由于只有一个 k ，所以记录一个就行
    }
    if(k != -1){
        merge(R, mm(a, 0, k - 1)); // 不包含 x 的左邻域
        merge(R, mm(a, k + 1, n - 1)); // 不包含 x 的右邻域
        merge(R, mx(a, k)); // 包含 x 的左右邻域
    }else merge(R, mm(a, 0, n - 1)); // 数组 a
    cout << R.size() << endl;
    for(auto i : R) cout << i << " "; // 由于集合自动排序，所以挨个儿输出即可
    cout << endl;
    return;
}

int main(){
    int T = 1; cin >> T;
    while(T--) solve();
    return false;
}
```

---

## 作者：wfc284 (赞：1)

我们先想全是 $\pm 1$ 的。令区间内最小子段和为 $mn$，最大子段和为 $mx$，注意到 $[mn,mx]$ 内的数全都能被凑出来。  

- 证明：我们在区间 $[l,r]$ 内任意取一个子区间 $[l',r']$。
  - 定义【扩展】为将一个区间左边或右边添加一个数。
  - 定义【收缩】为将一个区间左边或右边去掉一个数。

  我们发现所有 $[l,r]$ 的子区间都能通过 $[l',r']$【扩展】或【收缩】得到。而对于【扩展】或【收缩】，操作前后的 $sum$ 一定是连续的。于是，所有子区间的 $sum$ 都是连续的。所谓【连续】，当然是从最小和连续到最大和。

将 $[mn,mx]$ 内的数加入答案即可。

对于有特殊值的，类似分治的思想，劈两半算两遍，再管包含特殊值的区间。和一定是左半的后缀加特殊值加右半的前缀。同理，只会取到最小值到最大值的所有数。

排序，去重，输出即可。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 2e5+2;
	
	int n, a[N];
	
	vector<int> ans;
	int sum[N];
	void work(int *a, int n) {
		int x = 0, y = 0;
		int mx = 0, mn = 0;	//初值的艺术
		int sum = 0;
		for(int i = 1; i <= n; ++i) {
			sum += a[i];
			mx = max(mx, sum - y);
			mn = min(mn, sum - x);
			x = max(x, sum);
			y = min(y, sum);
		}
		for(int i = mn; i <= mx; ++i) ans.push_back(i);
	}
	
	void main() {
		cin >> n;
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for(int i = 1; i <= n; ++i) sum[i] = sum[i-1] + a[i];
		
		int p = -1;
		for(int i = 1; i <= n; ++i)
			if(abs(a[i]) != 1) {
				p = i;
				break;
			}
		
		ans.clear();
		if(~p) {
			int mx = 0, mn = 0;
			int x = 0, y = 0;
			work(a, p-1);
			for(int i = p-1; i >= 0; --i)
				x = max(x, sum[p-1] - sum[i]), y = min(y, sum[p-1] - sum[i]);
			mx += x, mn += y;
			
			x = y = 0;
			work(a+p, n-p);
			for(int i = p; i <= n; ++i)
				x = max(x, sum[i] - sum[p]), y = min(y, sum[i] - sum[p]);
			mx += x, mn += y;
			
			for(int i = mn; i <= mx; ++i) ans.push_back(i + a[p]);
		}
		else work(a, n);
		
		sort(all(ans));
		ans.erase(unique(all(ans)), ans.end());
		printf("%d\n", (int)ans.size());
		for(int ele : ans) printf("%d ", ele);
		puts("");
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：TSY48 (赞：1)

**解题思路**

---

分两种情况讨论。

1. 存在一个元素不等于 $-1$ 或 $1$ 的情况。
2. 所有元素都等于 $-1$ 或 $1$。

先来讨论第二种情况，由[介值定理](https://baike.baidu.com/item/%E4%BB%8B%E5%80%BC%E5%AE%9A%E7%90%86/10818809?fr=ge_ala)可知，我们只要计算如果以 $i$ 做起点，其能取到的最大值与最小值即可，此为如果以 $i$ 做起点，其可以取到的值的范围。

答案即为所有区间的并。

现在来讨论第一种情况，由题意知，不等于 $1$ 或 $-1$ 的元素至多只有一个，令其位置为 $locx$，则答案为：$[1,\dots,locx-1]$ 的和并上 $[locx+1,\dots,n]$ 的和并上所有包含 $locx$ 的子数组的和。

- $[1,\dots,locx-1]$ 和 $[locx+1,\dots,n]$ 这两种情况可以用上述方法求解。
- 包含 $locx$ 的子数列可以考虑以 $locx-1$ 为终点可以取到的最大值和最小值以及以 $locx+1$ 为起点可以取到的最大值和最小值，然后加上 $a_{locx}$ 即可。

**代码**

---

```C++
int n;
scanf("%lld", &n);
for (int i = 1; i <= n; i++)
    scanf("%lld", &a[i]);
int locx = -1;
for (int i = 1; i <= n; i++)
{
    if (a[i] != -1 && a[i] != 1)
    {
        locx = i;
        break;
    }
}
if (!(~locx))
{
    int mx = -inf, mn = inf;
    int nwmx = 0, nwmn = 0;
    for (int i = n; i >= 1; i--)
    {
        if (a[i] == 1)
            nwmx++, nwmn++;
        else
            nwmn--, nwmx--;
        nwmx = max(nwmx, 0ll);
        nwmn = min(nwmn, 0ll);
        mx = max(nwmx, mx);
        mn = min(mn, nwmn);
    }
    set<int> ans;
    for (int i = mn; i <= mx; i++)
        ans.insert(i);
    ans.insert(0);
    printf("%lld\n", siz(ans));
    for (auto t : ans)
        printf("%lld ", t);
    printf("\n");
}
else
{
    set<int> ans;
    int mx1 = -inf, mn1 = inf, nwmn1 = 0, nwmx1 = 0;
    for (int i = 1; i <= locx - 1; i++)
    {
        if (a[i] == 1)
            nwmx1++, nwmn1++;
        else
            nwmn1--, nwmx1--;
        nwmx1 = max(nwmx1, 0ll);
        nwmn1 = min(nwmn1, 0ll);
        mx1 = max(nwmx1, mx1);
        mn1 = min(mn1, nwmn1);
    }
    int mx2 = -inf, mn2 = inf, nwmn2 = 0, nwmx2 = 0;
    for (int i = n; i >= locx + 1; i--)
    {
        if (a[i] == 1)
            nwmx2++, nwmn2++;
        else
            nwmn2--, nwmx2--;
        nwmx2 = max(nwmx2, 0ll);
        nwmn2 = min(nwmn2, 0ll);
        mx2 = max(nwmx2, mx2);
        mn2 = min(mn2, nwmn2);
    }
    for (int i = mn1; i <= mx1; i++)
        ans.insert(i);
    for (int i = mn2; i <= mx2; i++)
        ans.insert(i);
    for (int i = nwmn1 + nwmn2 + a[locx]; i <= nwmx1 + nwmx2 + a[locx]; i++)
        ans.insert(i);
    ans.insert(0);
    printf("%lld\n", siz(ans));
    for (auto t : ans)
        printf("%lld ", t);
    printf("\n");
}
```

---

## 作者：Hanggoash (赞：1)

# CF2043C 题解

## 题意

给定一个除了 $-1,1$ 之外，最多存在一个 $x,x\in[-10^9,10^9]$ 的数的序列，求其子段和的所有可能值，从小到大输出。

## 分析

很容易就去思考如何从这个特殊的 $x$ 入手。于是先排除这个特例，考虑全都是 $1,-1$ 的情形，那么顺序从左到右不断加入 $a_i$ ，可以发现可以通过维护当前值域的上下界来解决问题。最后我们对于 $x$ 之前的数统计一遍， $x$ 之后的数倒序统计一遍，然后通过 $x$ 把两边合并起来就好了。

赛时就是这么想的，思路也大体正确了。

但是存在的一个问题是，值域中的某些数，可能并不能和当前这个 $a_i$ 拼接到一起，因为它可能不是以 $a_{i-1}$ 结尾的。比赛的时候是这么写的，很麻烦，最后也没有调出来。 

### 值域统计

不妨换一个角度思考，一个 $[l,r]$ 的子段和可以表示为 $sum_r-sum_{l-1}$，由于 $x$ 比较特殊，我们还是像上文提到的那样对于 $x$ 的两边分别统计，最后单独考虑 $x$。

这样对于一个固定的 $i$ 来说，$sum_i-sum_j$ 的取值一定是**在整数意义下**连续的。因为任意的 $sum_i$ 和 $sum_{i-1}$ 相比，绝对值只会相差 $1$ ，这就是 $1,-1$ 的带来的特殊性。（这段比较抽象，建议画一个 $s_i$ 的散点图来理解）

所以只需要考虑前缀和的前缀 $max$ 和 $min$ 就可以了，对于一个 $s_i$，$[s_i-pmax,s_i-pmin]$ 之间的所有整数一定都是可以取到的，这样我们就成功计算出了以 $a_i$ 为结尾的子段值域。

注意，这仅仅是以 $a_i$ 为结尾的值域情况，我们不断维护它，是为了到最后能和 $x$ 拼接起来，但是如果直接把它当成答案，肯定会有所遗漏，因为答案子段的结尾并不仅仅只是一个固定的元素，因此，对于所有算出来的值域，我们要取并集。

至于这个取并集过程的实现，观察到分别以两个相邻元素为结尾子段的值域相差不会太大，我们只需要把每次更新值域后 被遗漏的部分提前标记为 true 就可以了。当然，在差分数组上操作，最后前缀和一遍的 trick 也是可以的。

以上是对于 $x$ 左侧的计算方法，对于 $x$ 的右侧来说，倒序枚举如法炮制即可。

### 对 $x$ 两侧的值域进行合并
记 $x$ 对应的下标为 $pos$。

假设左边以 $a_{pos-1}$ 为结尾的值域是 $[l,r]$，右边以 $a_{pos+1}$ 为结尾的值域是 $[L,R]$。

很明显的是，最后能够取到的就是 $[x,x]\cup[l+x,r+x]\cup[L+x,R+x]\cup[l+L+x,r+R+x]$，把这一部分并进答案即可。

我个人的实现方法过于抽象，不过最后还是过了就行。

记得要单独把 $0$ 也标记为 true。
## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int T,n;
const int N=2e5+10;
int a[N];
set<int> les,mor;
vector<int> output;
inline void out(set<int> &s){for(int x:s)cout<<x<<' ';}
const int INF=998244353;
inline void solve()
{
    cin>>n;
    les.clear(),mor.clear(),output.clear();
    vector<int> vis(2*n+10,0);
    auto upd=[&](int l,int r)
    {
        for(int i=l;i<=r;++i)
        {
            if(i<-n)les.insert(i);
            else if(i>n)mor.insert(i);
            else vis[i+n]=1;
        }
    };
    for(int i=1;i<=n;++i)cin>>a[i];
    int pos=n+1>>1;//随便钦定一个位置即可
    for(int i=1;i<=n;++i)if(a[i]!=1&&a[i]!=-1){pos=i;break;}
    int l=0,r=0,s=0;
    int mx=0,mn=0;
    for(int i=1,nowl,nowr;i<pos;++i)
    {
        s+=a[i];
        nowl=s-mx,nowr=s-mn;
        for(int j=l;j<nowl;++j)vis[j+n]=1;
        for(int j=r;j>nowr;--j)vis[j+n]=1;
        mx=max(mx,s),mn=min(mn,s);
        l=nowl,r=nowr;
    }
    int L=0,R=0;
    s=0,mx=0,mn=0;
    for(int i=n,nowl,nowr;i>pos;--i)
    {
        s+=a[i];
        nowl=s-mx,nowr=s-mn;
        for(int j=L;j<nowl;++j)vis[j+n]=1;
        for(int j=R;j>nowr;--j)vis[j+n]=1;
        mx=max(mx,s),mn=min(mn,s);
        L=nowl,R=nowr;
    }
    int x=a[pos];
    upd(l,r);
    upd(L,R);
    upd(x,x);
    upd(l+x,r+x);
    upd(L+x,R+x);
    upd(l+L+x,r+R+x);
    vis[n]=1;
    for(int i=-n;i<=n;++i)if(vis[i+n])output.push_back(i);
    cout<<les.size()+output.size()+mor.size()<<'\n';
    out(les);
    for(int val:output)cout<<val<<' ';
    out(mor);
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--)solve();
    return 0;
}
```

---

