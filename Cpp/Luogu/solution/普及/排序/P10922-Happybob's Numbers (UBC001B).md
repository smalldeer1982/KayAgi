# Happybob's Numbers (UBC001B)

## 题目描述

happybob 在地上有 $n$ 个数，第 $i$ 个记为 $a_i$。happybob 正在研究如何将这些数全部删除。在他开始进行所有操作以前，他有一次按任意顺序摆放这些数的机会。他接下来要按照如下方式进行删数：

- happybob 有一个删数下标 $h$（初始时 $h=1$），他会设立一个新变量 $H$，其值为 $a_h$ ，然后对于每一个满足 $h\le i<k$ 的正整数 $i$ 都执行 $a_i\gets a_{i+1}$（这里 $k$ 是当前地上剩余的数的个数）并删除数 $a_k$，在这之后他会把 $h$ 赋值为 $H$。

- **如果在任何一次操作过后，$h$ 严格大于当前地上剩余的数的个数，那么他将不能再删除任何数。**

当然以他的这种删数方式不一定可以删完所有数，所以他现在想问你：他最多能删除多少个数？

## 说明/提示

#### 样例解释

对于第一个数据点，happybob 可以把 $a$ 数组排序为 $[2, 3, 1]$。以下是删数过程：

| 操作次数 | $h$（操作完成后） | 地上的数（操作完成后） |
| -- | -- | -- |
| 初始 | $1$ | $[2, 3, 1]$ |
| $1$ | $2$ | $[3, 1]$ |
| $2$ | $1$ | $[3]$ |
| $3$ | $3$ | $[]$ |

地上没有数了，也就是一共删除了 $3$ 个数。

对于第二个数据点，可以证明，无论怎么排序 $a$，都只能删除一个数。

#### 数据范围

**本题有多组测试数据。**

对于 $100\%$ 的数据，保证 $1 \le t,n,\sum n\le 5 \times 10^5$，$1\le a_i\le 10^9$。其中 $\sum n$ 表示所有测试数据中 $n$ 的和。

## 样例 #1

### 输入

```
2
3
1 2 3
4
114 514 1919 810```

### 输出

```
3
1```

# 题解

## 作者：_Weslie_ (赞：4)

一个小清新贪心题。

## 思路

发现删数的操作等同于把 $a_h$ 去掉，其他不变。

因为第 $i$ 轮一定删掉了 $i$ 个数，所以实际上我们下一次访问的下标是 $a_h+i$。

接下来我们对 $a$ 排序（升序）。

一共有 $n$ 个数，所以如果这一轮 $i$ 游戏不结束，我们最多可以选最后一个小于等于 $n-i$ 的数。

接着就是一个贪心策略：我们选最后一个小于等于 $n-i$ 的数。

证明：因为现在选的这个数在下一轮不一定可以使用，但是比这个数更小的数或许可以。所以先把这一个拉上去，留着更小的以后使。

不难发现我们肯定可以构造一个初始序列使得操作按上面的贪心策略进行。

实现起来，可以二分，也可以使用线性做法。

线性做法是基于一个定理：如果 $a$ 是升序排序的，且 $a_i+x\le n$ 是对于第 $x$ 轮的最大的 $a_i$，则使 $a_j+x+1\le n$ 的最大的 $a_j$ 一定满足 $j<i$。显然如果 $j>i$，$a_j>a_i$，就会有 $a_j+x+1>a_i+x>n$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int T,n,a[500005],ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		sort(a+1,a+n+1);
		int t=n;
		ans=1;
//		a[0]=-2147483647;
		for(int i=n;i>=1;i--){
			if(a[i]+ans<=n)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：lin_A_chu_K_fan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10922)

题意略
# 思路
题目中删数过程写的很繁琐，但其实就是把 $a_i$ 删掉，别的不变。

那么可以先将 $a$ 数列从大到小排序，然后遍历，遇到小于当前长度 $k$ 的数就删掉，然后 $k$ 减去 $1$，答案加 $1$ 即可。

**警告：只要不是全部删除，那么答案要加 $1$，因为最后还可以删一个。**

思路就是这样，蒟蒻码风过丑，就不放了，求关，溜~

---

## 作者：hjm777 (赞：1)

### Happybob's Numbers

一道贪心题，设 $k$ 为当前长度。

从大到小排序，发现一个数小于 $k$，就将这个数删掉，长度 $-1$，再将下一个小于当前 $k$ 的数，放到下一个删的位置。

但若不是全部删除，需要 $+1$，毕竟最后还可以删 $1$ 个数。

```cpp
// Author : hejinming2012
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define dbg(x) cout << #x " = " << (x) << endl
#define quickio ios::sync_with_stdio(false);
#define quickin cin.tie(0);
#define quickout cout.tie(0);
#define maxn 500005
using namespace std;
inline int read() {
	int now = 0, nev = 1; char c = getchar();
	while(c < '0' || c > '9') { if(c == '-') nev = -1; c = getchar(); }
	while(c >= '0' && c <= '9') { now = (now << 1) + (now << 3) + (c & 15); c = getchar(); }
	return now * nev;
}
void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int a[maxn];
signed main() {
	quickio
	quickin
	quickout
    int T = read();
    while(T--) {
        int n = read(), k = n, ans = 0;
        for(int i = 1; i <= n; i++)
            a[i] = read();
        sort(a + 1, a + n + 1, greater <int> ());
        for(int i = 1; i <= n; i++)
            if(a[i] < k) ans++, k--;
        if(ans == n) ans--;
        write(ans + 1), putchar(10);
    }
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

**主要思路：贪心，构造。**

## 思路

构造题，首先明确要删的就是小于 $n$ 的数，因为若删了大于等于 $n$ 的数就无法进行之后的操作了。

那这道题就简单了，先从大到小排序，遇到小于当前长度 $k$ 的数，就将这个数删掉，这时长度需减 $1$，毕竟顺序可以自己调，将下一个小于当前 $k$ 的数，放到下一个需要删的位置。

但若不是全部删除，需要加 $1$，毕竟最后还可以删 $1$ 个数。

## AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[500004];
bool cmp(int x, int y) {
	return x > y;
}
int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		int ans = 0, k = n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		sort(a + 1, a + 1 + n, cmp);
		for (int i = 1; i <= n; i++) {
			if(a[i]<k)ans++,k--;
		}
		if (ans == n)--ans;
		cout << ans + 1 << "\n";
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

出题人解。

### Sol.

我们不妨把题目理解为：我们可以一边操作，一边不断地交换 $a$ 中的数。

以下的删除一个数 $x$ 都指把 $x$ 这个数放到 $a_h$ 的位置上然后执行一次操作。

首先，设当前地上数的数量为 $cnt$。明显，大于等于 $cnt$ 的数是不能在除了最后一次操作被删除的，否则这就是最后一次操作，因为 $cnt$ 在元素删除后会减一，之后什么数都删不掉了。

接着，在所有小于 $cnt$ 的数中，应尽量优先删除大的数，否则这些数可能在未来几轮后就不能删除了，原因见上。

综上，每次删除应出严格小于当前元素数量的最大的数。

实现上先把数组从小到大排序然后倒着枚举每个数，判断是否可以删除。最后加一代表最后一次操作。

### Std.

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010];
int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		int ans=1,used;
		cin>>n;
		int flag=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=n;i;i--)
		{
			if(a[i]<n)
			{
				used=i;
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			cout<<1<<'\n';
			continue;
		}
		int now=n-1;
		for(int i=n;i;i--)
		{
			if(a[i]>=now||used==i) continue;
			now--;
			ans++;
		}
		cout<<min(ans+1,n)<<'\n';
	} 
	return 0;
}
```

---

## 作者：sbno333 (赞：1)

有个很好的想法是贪心，发现每次操作完跳到的位置只要合法，我们就可以提前安排好，这意味着我们只需要维护每次都合法即可，在不考虑删除得数本身的情况下，我们跳到哪里并不重要。

那么我们只需要每次删除一个数，保证删除后仍然可以进行下一步即可，由于删除越来越难，我们把之后删不了得数先删，就是尽量删大的。

于是我们只需要排序，然后一个指针维护数，记录当前堆里头数的数量即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000009];
bool cmp(int a,int b){
	return a>b;
}
void _main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n,cmp);
	int inn;
	inn=n;//假设此时删除前有 n 个数
	for(int i=1;i<=n;i++){
		if(a[i]>inn-1){//如果删除后跑到了外面，就不合法
			continue;
		}
		inn--;//维护的是最后一次删除前的数数量
	}
	cout<<n-inn+1<<endl;//因为删除前，所以答案要加一
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：cosf (赞：1)

给一个稍微严谨一点的证明。

假定最优策略是删除 $b_1, b_2, \dots, b_k$，那么，对于任意 $1 \le i \lt k - 1$，$b_i$ 和 $b_{i + 1}$ 会作为相邻两个消除，需要满足以下条件（英文句号防止误认为 $0$）：

1. $b_i \le n - i$.
2. $b_{i + 1} \le n - i - 1$.
3. $b_{i + 1}$ 为删除 $b_i$ 后第 $b_i$ 个数。

第三个容易达到，只要放到恰当的位置即可。

对于前两个，如果 $b_i \lt b_{i + 1}$，则有 $n - i \gt n - i - 1 \ge b_{i + 1} \gt b_i$，$b_{i + 1} \le n - i$ 与 $b_i \le n - i - 1$ 同样成立，因此，我们可以调换 $b_i$ 与 $b_{i + 1}$ 的位置（当然，也要把 $b_{i + 2}$ 移到相应位置），答案不会变劣。

因此，我们可以令最优策略中有 $b_1 \ge b_2 \ge b_3 \ge \dots b_{k - 1}$。也就是说，我们要找到一个最长的不降序列 $b_i$，满足 $b_i \le n - i$。

这样就可以贪心了，每次从 $\le \min\{n - i - 1, b_i\}$ 的数中选出最大的没有选的数，最后再从剩下的里面随便选一个作为 $b_k$，即得答案。

本来想出成输出方案的，但考虑到这是 B 题，所以放宽了一点。~~（其实是不想写 SPJ）~~

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 500005

int n;

int a[MAXN];

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1, greater<int>());
    int h = 1, c = 1, r = 1;
    for (int i = n - 1; ~i; i--)
    {
        while (a[c] > i && c < n)
        {
            c++;
        }
        if (a[c] > i || c > n)
        {
            break;
        }
        r++;
        h = a[c];
        c++;
    }
    cout << r << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：modfish_ (赞：1)

## 思路
不妨先考虑 $a$ 为一个排列的情况，以得到启发。容易发现，按照 $n-1,n,1,2,\dots,n-2$ 的方式放置，就可以全部删掉。

另一个显然的结论：在任何时候，只要删掉了一个大于等于 $n$ 的数，就不能再删下去了。

于是，我们不妨猜测：将所有小于 $n$ 的数拎出来，从大到小地消除，每一次都尽可能地多消除一点，最后剩下的位置放那些大于等于 $n$ 的数。

具体地，记当前枚举到的数为 $x$，其出现的次数为 $cnt$，上一个数为 $pre$，则（保证当前还剩下至少 $pre$ 位）：

- 先将一个 $x$ 放在第 $pre$ 位上，并消除它以及它的位置（注意，以下所有的“消除”都是指连同位置一起消除）。这是因为上一个放置的数是 $pre$，所以这一次要消除的是第 $pre$ 位。

- 记当前第 $x$ 位（包括第 $x$ 位）后面剩余了 $rst$ 位，则将 $\min(cnt,rst-1)$ 个 $x$ 一个一个放到第 $x$ 位上，并一个一个消除。这是因为对于每一个 $x$，上一个放置的数都是 $x$，所以都要被消除掉。

- 至于为什么至多消除 $rst-1$ 位，是为了保证枚举下一个数时，我们的先决条件（即当前还剩下至少 $pre$ 位）依然成立。若消掉 $rst$ 个，就只剩 $x-1$ 位了。

这个做法的正确性较为显然。感性理解一下，剩余位数越少，较大的数就较难消除，所以从大开始消；每一次消除时，我们都在保证接下来还能继续消的前提下，尽可能多地消掉了当前的数。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5 + 5;

int tag[maxn];

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++){
			int a;
			scanf("%d", &a);
			if(a < n) tag[a] ++;
		}
		int pre = 0, ans = 0, rst = 0;
		for(int i = n - 1; i >= 1; i --){
			if(tag[i]){
				tag[i] --, ans ++;
				if(!pre) rst = n - i;
				else rst += pre - i - 1;
				ans += min(tag[i], rst - 1);
				rst -= min(tag[i], rst - 1);
				pre = i;
			}
		}
		printf("%d\n", ans + 1);
		for(int i = 1; i <= n; i ++) tag[i] = 0;
	}
	return 0;
}
```

---

## 作者：StarsIntoSea_SY (赞：1)

感觉题目描述的有些难懂，说通俗一点就是：

> 先删除第 $1$ 个数，再删除第 $a_{1}$ 个数，再删除第  $a_{a_{1}}$ 个数，一直到不能删除（超出范围）为止。
>
> 你需要找到一组排列方式使得能删除最多的数。

# Solution

比赛时看到这题是一脸蒙圈的。

不过仔细分析还是有不少发现的。

- 最终答案 $\ge 1$。
- 一些很大的数尽可能不先删。
- 如果需要删除一个数 $a_{i}$，**需要满足 $a_{i} \le n-1$ 才不会超出范围**。（需要注意的是这里的 $n$ 是已删除若干个数的序列长度）
- 显然，**一个序列最大的值不影响结果**。证明：如果除最大值以外的数都能被删除，那么轮到其删除时必定结束；若不能，则前面必有较小的数超出范围，换成删其也同样会超出范围。比如样例中的`1 2 3`，换成`1 2 999999`的输出仍然是 $3$。

到了这里就足够解决了。

我们可以先对整个序列排序，从次大值开始（最大值不影响结果），如果当前的值 $\le n-1$，那么这个值必然可以被删除，那么更新答案和 $n$ 值。

为什么这样跑出来就是正确答案，显然对于加入的值，**总是可以把下一个值放在其删除后的下一个数的位置**，这样就能满足所有选择的值可以被删除。至于没有被选择的值，可以放在其他不影响删除操作的位置，这样前面删完之后到其直接跳出即可，不影响答案。

时间复杂度 $O(n \log_2 n)$，瓶颈在于排序。

# Code


```cpp
#include <stdio.h>
#include <algorithm>
using std::sort;
int a[500005];
int n=0;
void sol(){
	for(int i=1;i<=n;++i) a[i]=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int r=1;
	for(int i=n-1;i>0;i--){ //从次大值开始
		if(a[i]<=n-r) ++r; //核心操作，把能删除的点全部取出
	}
	printf("%d\n",r);
}
int main(){
	int _;scanf("%d",&_);
	while(_--) sol();
}
```

---

## 作者：Pollococido (赞：0)

### 思路

首先肯定不能删 $\ge n$ 的 $a_i$，不然就删不了了。知道这一点后，我们令 $k = n$ 从降序排序 $a$ 后，对于每个 $i(1 \le i \le n)$，若 $a_i < k$，则 $k \gets k-1$，统计次数的加 $1$。

如果没有全删完那么结果还要 $+1$ 因为可以在删一个。

### 代码

不放了。

时间复杂度 $O(n \log n)$ 因为排序。

---

## 作者：篮网总冠军 (赞：0)

偶然间刷到这题，一开始没排序竟然过了大部分数据，于是乎发篇题解纪念一下。

本题是一道很简单的贪心。

设 $k$ 是当前长度，很容易证明，我们要尽量删满足 $a_i \le k$ 且 $a_i$ 较大的，先排个序即可。

接着直接枚举即可，如果枚举到符合要求的，让长度 $-1$，再让答案 $+1$ 即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[500005]; 
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int k=n;
		int cnt=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);
		for(int i=n;i>=1;i--){
			if (a[i]<k){
				k--;
				cnt++;
			}
		}
		if (cnt==n) cout<<cnt<<endl;
		else cout<<cnt+1<<endl;
	}
	return 0;
}
```

---

## 作者：皓月星辉 (赞：0)

## 题意
~~一开始题面没改我竟然没看懂。~~

简单来说就是对于每组数据有一个一开始为 $1$ 的变量 $h$ 和一个你可以自己规定顺序的数组 $a$。

每次操作删除数组中的第 $h$ 个数，并将 $h$ 的值设为这个数，直到数组的长度小于 $h$ 时结束。

问最多能删除几个数。
## 分析
因为如果数组中的某些数大于数组的长度，那么这些数的值如果赋给了 $h$，那么操作就会无法继续下去。

所以考虑贪心思路，在数组中小于数组原长的数中越大的就优先删除，所以我们只需要计算哪些数会被删除就行了。
## 代码（有注释，请勿抄袭）

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[500005],cnt,te,x;
int main()
{
	cin>>t;
	while(t--)//多测
	{
		cin>>n;
		for(int i=0;i<n;i++)cin>>a[i];
		sort(a,a+n);
		reverse(a,a+n);//从大到小排序
		te=n;//实时记录数组长度
		cnt=0;//记录答案
		for(int i=0;i<n;i++)从//大到小遍历
		{
			if(a[i]>=te)continue;//大于数组的长度，不能删除
			else
			{
				te--;//删除后数组长度减一
				cnt++;//答案加一
			}
		}
		cout<<++cnt<<endl;//最后还要加一，因为第一次删除没有记录
	}
	return 0;
}
```

## END

---

## 作者：fish_love_cat (赞：0)

这题如果不需要构造的话感觉明显比 A 简单啊，难点不会是阅读理解吧。

而且出题人不把这题出成构造不会是因为不会写 SPJ 吧，还有这场真的一个 SPJ 都没有呢……

那也就难怪 A 要搞个字典序出来了……

---

题意：

有个序列 $h$，初始时 $h_1=1$。我们第 $i$ 次删除会令 $h_{i+1}=a_{h_i}$，然后删除掉 $a_{h_i}$，再把 $a_{h_i}$ 后面的全部向前移动一位。然后如此循环往复，直至当前删除的位置是空的。

形式化的说，设当前序列长度为 $k_i$，当 $h_i>k_i$ 时，就不能进行删除了。

给定所有元素，我们需要通过给这些元素排序使得删除的元素尽可能多。

问最多能删除多少。

---

如果当前 $a_{h_i}<k_i$，那么 $h_{i+1}<k_i$，因为 $k_{i+1}=k_i-1$，所以下一次依旧可以保证 $h\le k_{i+1}$。

所以对于每一位，我们删除满足 $a_{h_i}<k_i$ 的元素。因为位置由我们决定，所以如果有合法元素，一定可以构造出合法的方案。

注意到 $k$ 单调递减，所以大元素前面合法但随着 $k$ 单调递减可能会变得不合法。

所以我们应优先使用合法的大元素。

而如果没有合法元素了，那最多可以再删除一个不合法的，然后就结束了。

我们将元素从大到小排序模拟贪心即可。

注意全部合法的特判。

---

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,ans=0,flc;
        cin>>n,flc=n;
        vector<int>ve;
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            ve.push_back(x);
        }
        sort(ve.begin(),ve.end());
        for(int i=n-1;i>=0;i--){
            if(ve[i]<flc)flc--,ans++;
        }
        if(ans<n)ans++;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

为什么不改成构造啊。

---

