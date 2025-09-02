# Insert and Equalize

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ , all its elements are distinct.

First, you are asked to insert one more integer $ a_{n+1} $ into this array. $ a_{n+1} $ should not be equal to any of $ a_1, a_2, \dots, a_n $ .

Then, you will have to make all elements of the array equal. At the start, you choose a positive integer $ x $ ( $ x > 0 $ ). In one operation, you add $ x $ to exactly one element of the array. Note that $ x $ is the same for all operations.

What's the smallest number of operations it can take you to make all elements equal, after you choose $ a_{n+1} $ and $ x $ ?

## 说明/提示

In the first testcase, you can choose $ a_{n+1} = 4 $ , the array becomes $ [1, 2, 3, 4] $ . Then choose $ x = 1 $ and apply the operation $ 3 $ times to the first element, $ 2 $ times to the second element, $ 1 $ time to the third element and $ 0 $ times to the fourth element.

In the second testcase, you can choose $ a_{n+1} = 13, x = 4 $ .

In the third testcase, you can choose $ a_{n+1} = 9, x = 1 $ . Then apply the operation once to $ a_{n+1} $ .

## 样例 #1

### 输入

```
3
3
1 2 3
5
1 -19 17 -3 -15
1
10```

### 输出

```
6
27
1```

# 题解

## 作者：huangrenheluogu (赞：4)

为了操作次数最小，显然 $x$ 尽可能大才能缓解数字之间的差距。

因为 $x$ 可以化掉差值，所以 $x|(a_i-a_j),1\le i,j\le n$。

发现 $x=\gcd\{a_{i+1}-a_i\},1\le i<n$。

为什么这样就可以呢？

因为相邻两个数保证了 $x|\gcd$，那么显然可以让 $a_1=a_2$，同时，可以 $a_2=a_3,\dots ,a_{n-1}=a_n$，那么就相等了。

下面考虑 $a_{n+1}$ 放到哪里。

排序，令 $a_n$ 为最后的集合点，贪心让 $a_{n+1}$ 越大越好。

可能会问，为什么不让 $a_{n+1}=a_n+x$，像样例 $1$ 一样。

这样答案就相比于没有 $a_{n+1}$ 的时候增加 $n$，但是上面的做法增加的答案是小于等于 $n$ 的。

[code](https://codeforces.com/contest/1902/submission/237300846)

---

## 作者：luobo215 (赞：2)

### CF1902C Insert and Equalize

简要题意：给你一个整数数组 $a_{1},a_{2},a_{3},\dots,a_n$，它的所有元素都是不同的。

首先，要求你在这个数组中再插入一个整数 $a_{n+1}$；$a_{n+1}$ 不应等于 $a_{1},a_{2},a_{3},\dots,a_n$ 中的任何一个。

然后，您必须使数组中的所有元素相等。开始时，您选择一个**正**整数 $x$。在一次操作中，你将 $x$ 恰好添加到数组的一个元素中。**注意 $\mathbb{x}$ 在所有操作中都是一样的**。

在你选择了 $a_{n+1}$ 和 $x$ 之后，要使所有元素相等所需的最小运算次数是多少？

显然这个数列的可能最优最后值一定是你加入的数或此数列最大的数，然后我们可以发现强制选取数列的最大值作为最优值也一定是最优的。

如样例 $1$ 中我们强制让最大值取 $3$，$a_{n+1}$ 取 $0$ 结果仍然最优。

知道了最大值显然 $x$ 的取值就是所有值与最大值的差的最大公约数，然后我选择用 map 去重暴力跳 $a_{n+1}$ 就行。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ldb = long double;
using pii = pair<int, int>;
#define CI const int
#define mp make_pair
CI maxn=2e5+5;
ll a[maxn];
ll n,T,g,ma;
CI inf=1e9+10;
map<ll,bool> m;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>T;
    while(T--)
    {
        m.clear();
        ma=-inf;
        cin>>n;
        ll ans=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            ma=max(ma,a[i]);
        }
        g=0;
        for(int i=1;i<=n;i++)
        {
            a[i]=ma-a[i];
            m[a[i]]=1;
            g=__gcd(a[i],g);
        }
        if(g==0)g=1;
        for(int i=1;i<=n;i++)
        {
            ans+=a[i]/g;
        }
        ll k=g;
        while(m[k]==1)k+=g;
        ans+=k/g;
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：FiraCode (赞：1)

## 思路:
假如没有插入，那么我们发现最后所有的数字都是这个数组的最大值，考虑反证：

设这个数组的最大值为 $maxn$，假设最后为 $maxn+k(k>0)$ 为最优，那么 $maxn$ 要变成 $maxn+k$，那么 $x \mid k$，于是其他的数要先到 $maxn$ 然后再到 $maxn+k$，所以实际上它相比于变成 $maxn$ 增加了一些操作，所以变成 $maxn$ 比 $maxn+k$ 更优，与假设矛盾。

证毕。

那么一个数组最优的 $x$ 为 $\gcd(a_n-a_{n-1},a_{n-1}-a_{n-2},\dots,a_{2}-a_1)$。

然后考虑增加一个数字，那么这个数为 $maxn+xk$，若 $k>0$ 时每次都要 $n$ 的代价，而 $k<0$ 时，只需要找到最大的 $k$ 使得它没有在数组中出现过即可，而代价最多为 $n$，所以 $k<0$ 一定比 $k > 0$ 更优。

然后就计算每个数到最大值的操作次数再加上插入数字的操作次数即可。

复杂度 $O(Tn \log n)$。

## Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int T;
int n;
int a[200010];

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

signed main() {
	scanf("%lld", &T);
	while (T--) {
		map<int, int> ma;
		scanf("%lld", &n);
		int Gcd = 0;
		for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]), ma[a[i]] = 1;
		if (n == 1) {
			puts("1");
			continue;
		}
		sort(a + 1, a + 1 + n);
		for (int i = 2; i <= n; ++i) Gcd = gcd(Gcd, a[i] - a[i - 1]);
		int k = -1;
		while (true) {
			if (!ma[a[n] + k * Gcd]) break;
			--k;
		}

		int ans = 0;
		for (int i = 1; i <= n; ++i) ans += (a[n] - a[i]) / Gcd;

		ans -= k;

		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Robin_kool (赞：1)

一道结论题。

首先考虑 $x$ 的最优解，显然是 $\gcd(a_i-a_{i-1})(2 \leq i \leq n)$ ， 特别地这里的 $a$ 序列已经从小到大排序。

然后考虑 $a_{n+1}$ ，因为 $x$ 是正整数所以最优解一定是把 $a_n$ 当成最后相等的标准，然后从 $n$ 开始找第一个能插入的位置，例如：

$n=4,a_1=1,a_2=3,a_3=7,a_4=9$ 。显然， $x=2$ ,以 $9$ 为标准，发现 $a_{n+1}=5$  时刚好满足条件。

但也有需要单判的情况，例如：

$n=4,a_1=1,a_2=3,a_3=5,a_4=7$ 。$x=2$ ，但我们发现在 $1-7$ 范围内找不到可以插入的数字，那么就需要在 $1$ 之后，显然对于任意的这种情况而言， $a_{n+1}=a_n$ 一定需要 $n$ 次操作，那么这道题就做完了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll T, n, a[N], ans;
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline ll gcd(ll x, ll y){
	return !y ? x : gcd(y, x % y);
}
signed main(){
	//freopen("CF1902C.in", "r", stdin);
	//freopen("CF1902C.out", "w", stdout);
    T = read();
    while(T --){
    	n = read();
    	for(int i = 1; i <= n; ++ i) a[i] = read();
    	if(n == 1){//单判n=1的情况，其实可以理解为找不到插入位置
    		puts("1");
    		continue;
		}
		sort(a + 1, a + 1 + n);//排序
	    ll x = 0;
		for(int i = 2; i <= n; ++ i){
			x = gcd(x, a[i] - a[i - 1]);
		} 
		ll d = 0x3f3f3f3f;//防止找不到 a[n+1]
		for(int i = n; i >= 2; -- i){//因为要变成 a[n] 最小所以 a[n+1] 要尽量接近 a[n]
			if((a[i] - a[i - 1]) / x > 1){//可理解为 a[i-1] 和 a[i] 之间存在至少 1 个空位
				d = a[i] - x;
				break;
			}
		}
		ans = 0;
		for(int i = 1; i <= n; ++ i){
			ans += abs(a[n] - a[i]) / x; //计算 a[1-n] 的答案
		}
		ans += (d == 0x3f3f3f3f ? n : abs(a[n] - d) / x);//如上
		write(ans), putchar('\n');
	}
	return 0;
}

```


---

## 作者：czh___ (赞：0)

题意：

给定一个数组，你需要在数组后面再添加一个元素 $k$，然后选定一个 $x$，每次操作选中一个元素加上 $x$，问最少需要多少次操作，可使数组每个元素都相等。

题解：

对数组排序，所有相邻元素之间差值的最大公约数就是 $x$，然后计算出最后操作后数组的总和，减去初始数组的和，两个差值除以 $x$ 就是答案。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N];
void solve(){
	int n;
	int sum=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],
		sum+=a[i];
	if(n==1){
		cout<<"1"<<endl;
		return;
	}
	stable_sort(a+1,a+1+n);
	int x=a[2]-a[1];
	for(int i=3;i<=n;i++) 
		x=__gcd(x,a[i]-a[i-1]);
	for(int i=n;i>=1;i--)
		if(a[i]-a[i-1]!=x){
			sum+=a[i]-x;
			break;
		}
	cout<<(a[n]*(n+1)-sum)/x<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--) 
		solve();
	return 0;
}
```

[改编于](https://blog.csdn.net/m0_74461146/article/details/135831849?ops_request_misc=&request_id=&biz_id=102&utm_term=Insert%20and%20Equalize&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-135831849.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

