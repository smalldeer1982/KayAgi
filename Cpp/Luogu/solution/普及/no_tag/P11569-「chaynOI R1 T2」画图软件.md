# 「chaynOI R1 T2」画图软件

## 题目背景

### 14:27 添加了 T2 样例解释。

![](https://cdn.luogu.com.cn/upload/image_hosting/g3femwbe.png)


## 题目描述

给你一个序列 $a$，你可以进行不超过 $k$ 次「落笔」操作，每次选择一个 $p(1\le p\le n)$ 使得 $a_p \gets a_p +1$（即让 $a$ 中的第 $p$ 项加上 $1$），求出让 $a$ 为非负公差的等差数列的最终序列可能的情况数。

## 说明/提示

### 样例解释

共 $(1,2,3,4,5),(2,3,4,5,6)$，$2$ 种。

### 数据范围

对于 $100\%$ 的数据，$1 \le n,a_i \le 10^6$，$k\le 10^7$。

**本题采用捆绑测试。**

+ Subtask 1(20pts)：$n,k \le 100$。
+ Subtask 2(15pts)：$n \le 100$。
+ Subtask 3(15pts)：$k \le 10^5$。
+ Subtask 4(50pts)：无特殊限制。

## 样例 #1

### 输入

```
5 6
1 2 3 4 5```

### 输出

```
2```

# 题解

## 作者：CaiZi (赞：5)

假设有一个等差数列 $\{b_n\}$ 可以通过若干次操作得到。

根据等差数列的定义，我们可以知道 $\{b_n\}$ 只和首项 $b_1$ 以及公差 $d$ 有关，这个等差数列的和 $s$ 为：
$$s=\frac{n(b_1+b_n)}{2}=\frac{nb_1+nb_1+(n-1)d}{2}=\frac{2nb_1+(n-1)d}{2}$$

考虑枚举 $d$。假设我们正在计算某个固定的 $d$ 的答案。我们首先需要求出操作次数的最小值，然后可以通过不断给整个数列全部 $+1$ 来制造更多不同的等差数列。因为 $\sum a_i$ 固定，而操作次数等于 $s-\sum a_i$，所以我们需要求出 $s$ 的最小值。因为 $n,d$ 确定，所以我们需要求出 $b_1$ 的最小值，即对 $a_1$ 进行操作的次数的最小值。

我们可以先假设 $c_1=a_1$，得到等差数列 $\{c_n\}$。由于每次操作只能 $+1$ 不能 $-1$，因此如果有 $a_i>c_i$，则只能通过对 $a_1$ 进行 $a_i-c_i$ 次操作解决。因此 $\max\{a_i-[a_1+(i-1)d]\}$ 即为对 $a_1$ 进行操作的次数的最小值，注意这个值为负数的情况。然后此时套用 $s$ 的计算方法得到 $\{b_n\}$ 的和。

然后考虑 $d$ 的范围，最小值肯定是 $0$。而最大值需要满足 $a_1+(n-1)d\le a_n+k$，即最大值为 $\frac{a_n-a_1+k}{n-1}$，因此枚举 $d$ 的复杂度是 $O(\frac{V+k}{n})$，其中 $V$ 代表 $\{a_n\}$ 的值域。然后每次计算的复杂度是 $O(n)$ 的，总复杂度为 $O(n+V+k)$。

代码展示：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[1000001],b,c,x,y,z;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b+=a[i];
	}
	for(int i=0;a[1]+(n-1)*i<=a[n]+m;i++){
		x=0;
		for(int j=1;j<=n;j++){
			x=max(x,a[j]-a[1]-(j-1)*i);
		}
		y=(2*a[1]+2*x+(n-1)*i)*n/2;
		z=m-y+b;
		if(z>=0){
			c+=z/n+1;
		}
	}
	cout<<c;
	return 0;
}
```

---

## 作者：2022dyx (赞：2)

### 题目大意
给出一个数列，询问在不超过 $k$ 次单点加的操作之后，能产生多少公差非负的等差数列。
### 解法
我们把这个数列放到一个二维平面上，其中 $x$ 轴为下标，而 $y$  轴为对应的值。不难发现，一个公差非负的等差数列在这时相当于一条斜率非负的线段。

考虑这条线段有什么限制。我们设对于一个等差数列 $f$，$f_i$ 表示下标为 $i$ 时的值。首先，由于我们只能加不能减，也就是只能把点上移，不能把点下移，所以要求所有点都在线段的下方，即 $a_i\leq f_i$。另外，加的次数不能超过 $k$，也就是 $\sum (f_i-a_i)\leq k$。

先考虑第一条限制，我们枚举等差数列的公差。设公差为 $d$，那么限制最强的点一定是斜率为 $d$ 的直线切 $a_i$ 组成的凸包的切点。显然地，我们可以通过二分斜率来求得这个点，然后带入直线，获得 $f_1$ 的下界，也就是等差数列首项的下界。

第二条限制则更加简单。同样枚举公差，原式可化为 $\sum f_i\leq k+\sum a_i$。由于 $f$ 是一个等差数列，经过推导就有 $f_1\leq\frac{1}{n}(k+\sum a_i-\frac{n(n-1)}{2}d)$，这是等差数列首项的上界。

上下界做差就是方案数。不难证明，等差数列的公差一定不会超过 $\frac{\sum a_i+2k}{n(n-1)} \approx \frac{\sum a_i + k}{n^2}$。所以我们获得了一个 $O(\frac{\log n}{n^2}(\sum a_i + k)) < O(\sum a_i + k)$ 的算法，可以通过本题。

但是还有没有什么优化呢？我们发现在同一凸包上，当斜率变大时，切得的点只会不变或左移。于是我们可以直接双指针消掉那个 $\log$，虽然复杂度上没有什么变化，但是实测下来跑得快了不少。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int n, k, a[N], sum, ans;
deque <int> q;
double slope(int x, int y) { return (double) (a[y] - a[x]) / (y - x); }
bool check(int x) {
	int y = q.back(); q.pop_back();
	int z = q.back(); q.push_back(y);
	return slope(z, y) < slope(z, x);
} 
int calc(int x, int y) { return a[x] - y * x; }
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i], sum += a[i];
	q.push_back(1), q.push_back(2);
	for (int i = 3; i <= n; ++i) {
		while(q.size() > 1 && check(i)) q.pop_back();
		q.push_back(i); 
	}
	int now = q.back(); q.pop_back();
	for (int d = 0; d <= 1e7; ++d) {
		while(q.size() && calc(now, d) <= calc(q.back(), d)) now = q.back(), q.pop_back();
		int l = calc(now, d) + d, r = (k + sum - n * (n - 1) / 2 * d) / n;
		ans += max(0LL, r - l + 1);
	}
	cout << ans;
}
```

---

## 作者：liuzhuoran141516 (赞：1)

## 题目回顾

给定一个序列 $a$，你可以进行不超过 $k$ 次「落笔」操作，每次选择一个位置 $p$ 并将 $a_p$ 增加 $1$。要求通过操作使得序列 $a$ 成为一个非负公差的等差数列，并计算所有可能的最终序列的情况数。

---

## 解题思路

1. **等差数列的性质**：

2. - 等差数列的形式为 $b_1, b_1 + d, b_1 + 2d, \ldots, b_1 + (n-1)d$，其中 $d$ 是公差，且 $d \geq 0$。
   - 等差数列的和为：
   
$$
s = \frac{n \cdot (2b_1 + (n-1)d)}{2}
$$

3. **问题转化**：
   - 我们需要找到一个公差 $d$ 和一个首项 $b_1$，使得通过不超过 $k$ 次操作，可以将原序列 $a$ 转化为等差数列。
   - 操作次数的计算公式为：
   
$$
\text{required\_ops} = s - \sum_{i=1}^n a_i
$$
   - 如果 $\text{required\_ops} \leq k$，则该等差数列是可行的。

4. **枚举公差 $d$**：
   - 公差 $d$ 的范围为 $0 \leq d \leq \frac{a_n - a_1 + k}{n-1}$。
   - 对于每个 $d$，计算需要的最小操作次数，并统计满足条件的等差数列的数量。

5. **统计结果**：
   - 对于每个满足条件的 $d$，等差数列的数量为 $\frac{k - \text{required\_ops}}{n} + 1$。

---

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k, a[1000005], ans;
signed main() {
    cin >> n >> k;
    int sum = 0;
    for (int i = 1; i <= n; i++) {//求和 
        cin >> a[i];
        sum += a[i];
    }
    int maxn = (a[n] - a[1] + k) / (n - 1);
    //枚举公差d
    for (int i = 0; i <= maxn; i++) {
        //计算对a[1]的操作次数x
        int x = 0;
        for (int j = 1; j <= n; j++) {
            x = max(x, a[j] - (a[1] + (j - 1) * i));
        }
        int s = (2 * (a[1] + x) + (n - 1) * i) * n / 2;
        //如果操作次数不超过 k，则统计满足条件的等差数列的数量
        if (s - sum <= k) {
            ans += (k - s + sum) / n + 1;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：mystic_qwq (赞：1)

将最终的 $a$ 数组类比成一次函数的形式。

$f(i)=f(0)+i\times q$。由于 $k$ 较小，考虑暴力枚举。

从 $0$ 开始枚举 $q$。有公式 $f(0)=\max(a_i-i\times q)$。根据此算出 $f(0)$，和 $f(0)$ 取得最大值所在位置 $pos$。显然该位置单调不增。初始时候 $pos=n$，注意在下一次枚举 $q$，算 $f(0)$ 的时候直接从上一次的 $pos$ 往前枚举即可。

于是每次增加量就是 $-sum+n\times f(0)+\sum i\times q$，其中 $sum$ 是 $\sum a$。而 $\sum i=(i+1)\times i\div 2$。判断这个增加量 $\Delta$，如果 $\Delta>k$ 且 $pos=1$，则显然之后 $\Delta$ 将会一直增长。此时可以退出循环。否则如果 $\Delta\le k$，则有 $1+\left\lfloor(k-\Delta)\div n\right\rfloor$ 条单调函数可采取（后面的是 $f(0)$ 每增加 $1$，$\Delta$ 就增加 $n$）。于是问题得到解决。

---

## 作者：XuZile (赞：0)

# P11569 题解
## 题目大意
给定一个数组，可以进行不超过 $k$ 次操作，每次选择一个位置 $p$ 并将 $a_p \gets a_p+1$。要求数组变为一个非负公差的等差数列，并计算数组所有的情况数。
## 题目解法
我们经过多次操作后由原数组变为了等差数组。而对于等差数组中的第 $i$ 个就是 $a_i=a_1+(i-1)x$。其中 $x$ 是该等差数组的公差。接下去就可以计算出整个等差数组的和为：
$$sum = \frac{2n \times a_1+(n^2-n) \times x}{2}$$

接下去我们需要去枚举公差 $x$。使进行不超过 $k$ 次操作，让原数组变为公差为 $x$ 的等差数组。而对于公差为 $x$ 时变为等差数组的最少操作次数为：
$$cnt=sum-\sum_{i=1}^n a_i$$

得到了最少的次数后需要与 $k$ 进行比较。如果 $cnt \le k$ 那么说明原数组就可以变为公差为 $x$ 的等差数组。  
然后我们需要进一步计算公差为 $x$ 时可多少中可能的情况。等差数组的数量为：
$$ans=\frac{k-cnt}{n}+1$$

这时候就有聪明的人问了，那么公差 $x$ 的枚举范围是多少呢？答案很明显是 $\dfrac{a_n-a_1+k}{n-1}$。  
最后的最后在把所有的 $ans$ 统计起来，得到最终的结果。
## 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,x,s;
int a[1000010];
int sum,ans;
signed main() {
    cin >> n >> k;
    for (int i=1;i<=n;i++){
        cin >> a[i];
        sum+=a[i];
    }
    int mm=(a[n]-a[1]+k)/(n-1);
    for (int i=0;i<=mm;i++) {
        x=0;
        for(int j=1;j<=n;j++){
            x=max(x,a[j]-(a[1]+(j-1)*i));
        }
        s=(2*(a[1]+x)+(n-1)*i)*n/2;
        if(s-sum<=k) ans+=(k-s+sum)/n+1;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：lzx111218 (赞：0)

# P11569 「chaynOI R1 T2」画图软件
[题目传送门](https://www.luogu.com.cn/problem/P11569)
## 思路

### 等差数列

等差数列的特点是任意两项的差都是相同的，记为 $d$。对于题目中的序列 $a$ = [$a_1$, $a_2$, ..., $a_n$]，我们希望在进行不超过 $k$ 次操作后，使得该序列变成一个等差数列，其中每个项都可以是非负的。

为了满足等差数列的条件，序列中的每一项 $a_i$ 都满足：

$a_2 - a_1 = a_3 - a_2 = ... = a_n - a_{n-1} = d$

**转化一下**：

$a_2 = a_1 + d$
$a_3 = a_1 + 2d$

$\vdots$

$a_n = a_1 + (n-1)d$

因此，我们的任务就是通过最多 $k$ 次加 $1$ 操作，使得序列变成一个等差数列。

**然后就 so easy 了**

遍历可能的 $d$，计算对于每个 $d$，将序列变为等差数列所需的最少操作次数。如果操作次数不超过 $k$，则该公差 $d$ 是有效的。
最后，统计所有有效的 $d$ 的个数，就完事了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, a[1000001], b, c, x, y, z;
signed main(){
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        b += a[i];
    }
    for (int i = 0; a[1] + (n - 1) * i <= a[n] + m; i++) {
        x = 0;
        int l = 1, r = n;
        
        while (l <= r) {
            int ld = a[l] - a[1] - (l - 1) * i;
            int rd = a[r] - a[1] - (r - 1) * i;
            x = max(x, ld);
            x = max(x, rd);
            
            if (ld < rd) {
                l++;
            } else {
                r--;
            }
        }

        y = (2 * a[1] + 2 * x + (n - 1) * i) * n / 2;
        z = m - y + b;
        
        if (z >= 0) {
            c += z / n + 1;
        }
    }
    printf("%lld\n", c);
    return 0;
}
```

---

