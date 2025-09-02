# Liebig's Barrels

## 题目描述

你有一共m=n*k个木板。第i个木板的长度为ai。你必须用其中的每k条木板组成n个木桶。每条木板只能且必须属于一个木桶。我们把第j个木桶的最短的木板长度作为这个木桶的容积vj

你想要让这组合起来的n个木桶总容积最大。但是你需要让他们的容积尽量差不多，使得无论那两个木桶的容积差不超过l，即|vx-vy|<=l(1<=vx,vy<=n)。

输出这n个尽量相等的木桶的最大容积。如果无法组成满足要求的n个木桶，输出“0”

## 样例 #1

### 输入

```
4 2 1
2 2 1 2 3 2 2 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
2 1 0
10 10
```

### 输出

```
20
```

## 样例 #3

### 输入

```
1 2 1
5 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
3 2 1
1 2 3 4 5 6
```

### 输出

```
0
```

# 题解

## 作者：hicc0305 (赞：18)

这是一道还比较容易想到的贪心

我们先将这m个木板按照长度从小到大排个序，这很多人都能想到。

然后，在这n个木桶里，可以知道肯定有一个的容量是a[1]也就是最小的木板的长度。所以，如果a[n]-a[1]>l就不可能成立了，因为a[n]…a[m]都必定大于a[1]+l，不满足要求，而剩下只有n-1根木板，不可能满足被当做n个木桶的容量，所以直接输出零即可。

接下来的贪心策略就可想而知了。要想总容量最大，因为一个木桶的容量确定是a[1]，就要让剩下选出的n-1根木板尽可能大，且满足要求。先找到p,使得a[p]-a[1]<=l，a[p+1]-a[1]>l，p就是最大的木桶容积了。

我们把p和后k-1根木板（即m-k+2到m）组成木桶，把p-1和m-2k+3到m-k+1组成木桶……如果p后面的木板不够用了，只能用前面的木板来补了。

具体来举一个栗子：

4 3 17

1 2 3 5 9 13 18 21 22 23 25 26

这里，p=7，也就是大小为18的木板。按照上述贪心理论，我们把18,25,26组成一队（其实不从最后反着取也可以，从p+1开始正着取也可以道理是一样的）。接着把13,22,23组成一队。轮到9的时候，发现只剩下了21可以取，不够了，就只能让5作为木桶容量，把5,9,21分为一组。那么剩下的1,2,3应该也很好懂了。

ok，代码：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
long long n,m,k;
long long a[1000100];
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n*m;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n*m+1);
	if(a[n]-a[1]>k)
	{
		cout<<"0";
		return 0;
	}
	int p=n*m;
	while(a[p]-a[1]>k) p--;//求出p
	long long ans=0,num=0,j=p;
    for(int i=n*m;i-(m-1)>p;i=i-(m-1))//取p后面的组队
    {
        ans+=a[j--];
        num++;//记录从p往前多少个已经被取了
    }
    for(int i=1;i<=p-num;i=i+m)//后面不够了，前面剩下的自动隔m（即题目中的k）个作为桶的容积
    	ans+=a[i];
    printf("%lld",ans);
	return 0;
}

```

---

## 作者：EternalHeart1314 (赞：5)

### [题目传送门](https://www.luogu.com.cn/problem/CF985C)

# 思路

首先，肯定要排序的对吧。然后可以找到一个下标 $pos$，使得 $a_{pos}-a_1\le l$ 且 $a_{pos+1}-a_1>l$，所以桶的容量只能为 $a_1\sim a_{pos}$ 中的某些数。

而想要答案尽可能地大，肯定要优先选 $a_{pos}$，其次是 $a_{pos-1}$，再其次是 $a_{pos-2}\cdots$。边往前推边从最后配对组成桶，直到无法组成桶为止。

接着把剩下的木板顺序地组成桶，即 $a_1\sim a_k$ 为一组，$a_{k+1}\sim a_{2k}$ 为一组，$a_{2k+1}\sim a_{3k}\cdots$。

## 举个例子：
```
4 3 6
1 2 3 4 5 6 7 8 9 10 11 12
```
首先找到 $pos$，为 $7$。接着，把序列分成以 $pos$ 为分界点的两部分：
```
1 2 3 4 5 6 7
8 9 10 11 12
```
每次取出第一部分的最后一个和第二部分的最后 $k-1$ 个分为一组。即 $\{7,11,12\}$ 分为一组，$\{6,9,10\}$ 分为一组，此时两部分分别为：
```
1 2 3 4 5
8
```
合并：
```
1 2 3 4 5 8
```
最后，顺序地分组，即 $\{1,2,3\}$ 为一组，$\{4,5,8\}$ 为一组。

答案为 $7+6+1+4=18$。

# Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N(1e5 + 7);
int n, m, k, s, ans, cnt, pos, tmp, a[N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> k;
	s = n * m;
	for(int i(1); i <= s; ++ i) {
		cin >> a[i];
	}
	sort(a + 1, a + s + 1);
	while(a[pos + 1] - a[1] <= k) {
		++ pos;
	}
	if(pos < n) {
		return cout << 0, 0;
	}
	for(int i(s); i - m + 1 > pos; i -= m - 1) {
		ans += a[pos - cnt ++];
	}
	pos = s + 1 - m * (cnt + 1);
	while(pos > 0) {
		ans += a[pos], pos -= m;
	}
	return cout << ans, 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：灵茶山艾府 (赞：3)

以下讨论，下标从 $0$ 开始。

把 $a$ 排序，找到大于 $a_0+L$ 的最小的数，设其下标为 $i$。

木桶的体积只能在 $a_0,a_1,\cdots,a_{i-1}$ 这前 $i$ 条木板中。如果 $i < n$ 则输出 $0$。

贪心地想，**最小木板的长度越大越好**，但木桶必须恰好由 $k$ 条木板组成，所以前面的 $x$ 个木桶只能选 $a_0,a_k,a_{2k},\cdots,a_{(x-1)k}$ 这些木板。

剩下 $n-x$ 个木桶可以取前 $i$ 条木板中最大的 $n-x$ 个，这要求

$$
i-(n-x) \le xk
$$

解得

$$
x\ge \left\lceil\dfrac{i-n}{k-1}\right\rceil
$$

所以 $x$ 最小是

$$
\left\lceil\dfrac{i-n}{k-1}\right\rceil = \left\lfloor\dfrac{i-n+k-2}{k-1}\right\rfloor
$$

如果 $k=1$ 则 $x$ 最小是 $0$。

```go
package main
import("bufio";."fmt";"os";"slices";"sort")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, k, l, x, ans int
	Fscan(in, &n, &k, &l)
	a := make([]int, n*k)
	for i := range a {
		Fscan(in, &a[i])
	}

	slices.Sort(a)
	i := sort.SearchInts(a, a[0]+l+1)
	if i < n {
		Print(0)
		return
	}

	if k > 1 {
		x = (i - n + k - 2) / (k - 1)
	}
	for j := 0; j <= (x-1)*k; j += k {
		ans += a[j]
	}
	for _, v := range a[i-n+x : i] {
		ans += v
	}
	Print(ans)
}
```

时间复杂度：$\mathcal{O}(nk\log(nk))$。瓶颈在排序上。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：_ZML_ (赞：2)

# CF985C题解

## 思路

由题意得知，现在有 $n\times k$ 块木板需要组装成 $n$ 个木桶，每个木桶由 $k$ 块板组成，容量服从短板原理，要求容量差不得超过 $I$，求最大容量和。

不管采用什么方法，无疑我们首先需要将板长（数组 $a$）从小到大排列。

利用贪心算法。先找出与 $a_0$ 的长度差不超过 $l$ 的木板 $i$，$0 \le i \le index$ 如果 $index$ 不超过 $n$（桶的数目），说明无法组装成满足题目条件的桶，输出 $0$。每次从这些木板中取出尽可能多的木板（上限为 $k$）组装在同一个桶，假使剩下的木板数量仍不少于尚待组装的木桶的数目。

## 代码

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

unsigned long long maxVol()
{
    int n, k, l;    // n个桶，每个桶k块板，桶容量差不超过l
    cin >> n >> k >> l;

    unsigned long long int a[n * k];  // 板长
    for(int i = 0; i < n * k; i++)
        cin >> a[i];
    sort(a, a + n * k);

    int index = 0;
    while(a[index] - a[0] <= l && index < n * k)
        index++;

    if(index < n)
        return 0;

    unsigned long long int sum = 0;
    int i = 0;
    while(n != 0)
    {
        sum += a[i];
        if(index - i - n >= k)
            i += k;
        else
            i = index - n + 1;
        n--;
    }
    return sum;
}

int main()
{
    cout << maxVol() << endl;
    return 0;
}
```


---

## 作者：kimidonatsu (赞：2)

# CF985C Liebig's Barrels 题解

## 题意简述

* 给定总计 $n \times k$ 块木板。
* 需要选中 $k$ 条木板来组成 $n$ 个木桶。
* 每个木板只能使用一次。
* 每个木桶的容积定义为这个木桶最短的木板的长度。
* 要求这 $n$ 个容积尽可能相近的木桶的最大容积。

## 思路分析

### 贪心策略

要求最短的木板，只需要 `sort` 一遍找到 $a_1$ 即可。这根最短的木板就是当前木桶的容积。即剩下的 $n - 1$ 根木板必须要满足当作全部 $n$ 个木桶的条件。

可以发现，当 $a_n - a_1 \gt l$ 时，是不可能做出木桶的（否则 $a_n \dots a_m$ 必定大于 $a_1 + l$，这明显违背题意）。

想要让总容量最大，自然是尽可能找大的木板，有一个木桶的容量已经确定为 $a_1$，就要让剩下的几个木桶在 $a_2 \dots a_n$ 这 $n - 1$ 根木板中选择大的当作容量。

我们将最大容量定义为变量 $v$，只需要遍历数组，找到同时满足 $a_v - a_1 \leq l$ 和 $a_{v + 1} - a_1 \gt l$ 的 $v$ 即为最大容积。（由题意得，最短木板就是木桶容积，所以可以直接使用容量 $v$ 在木板长度数组 $a$ 中遍历）。

最后就是组装木桶了。由于我们要找容积尽可能大的木桶，所以往大的木板找，即找 $a_v$ 到 $a_{v + k}$ 这些木板来组成木桶。（即 $a_{m - k + 2} \dots a_m$）。以此类推，到大木板取完时，我们再回过头拿小木板。

### 样例说明

使用样例 \#1：

```
4 2 1
2 2 1 2 3 2 2 3
```

排序后遍历数组找到 $v = 6$：

```
1 2 2 2 2 2 3 3
```

所以 $a[v] = 2$，此时按照我们的贪心策略，木桶应该这么分：

![表格](https://s2.loli.net/2023/01/12/ef8qLx2BjFkrcRz.png)

~~由于洛谷博客的 Markdown 版本过老，所以大家将就着看一下图。~~

容量为 $v = 2 + 2 + 1 + 2 = 7$。

### 贪心证明

我们这里使用上文的 \#样例 1 交换一下组 2 和组 3 中的 $1$ 和 $2$，更新 $v = 2 + 2 + 1 + 2 = 7$。(若交换其他变量如 $1$ 和 $3$ 则无法满足题意)

交换处理的元素位置后却无法取得更优解，由此可以推定目前的解已经是最优解了。

---

总的来说，这是一道有水平的贪心题。在想出贪心策略后，代码的实现也是一个问题。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll N = 2e6 + 50;

ll n, k, l, ans;
ll a[N];

void work() {
    sort(a + 1, a + (n * k) + 1);   // 找出最短木板
    if (a[n] - a[1] > l) {
        printf("0\n");
        exit(0);
    }

    ll v = n * k;
    while (a[v] - a[1] > l) v--;    // 找到最大容量
    ll cnt = 0, it = v;
    for (ll i = n * k; i - (k - 1) > v; i -= (k - 1)) {
        ans += a[it--];
        cnt++;
    }
    for (ll i = 1; i <= v - cnt; i += k)
        ans += a[i];
}

int main() {
    scanf("%lld %lld %lld", &n, &k, &l);
    for (ll i = 1; i <= n * k; i++)
        scanf("%lld", &a[i]);
    work();
    printf("%lld\n", ans);
    return 0;
}

```

注意 **数据范围**，需要开 `long long`，否则在第七个数据点就会开始炸。


---

## 作者：lovely_codingcow (赞：0)

# 建议升绿

这道题是一道贪心。很容易想到，我们你需要先进行一次排序，然后再进行一些操作。

首先我们可以排除无解的情况，当**第 $n$ 短的木板的长度**与**最短的木板的长度之差** $> l$ 时，不可能有任何一种符合题意的方案。这个很好证，有兴趣的朋友可以自己证一下。

然后我们考虑如何制定一个合理的贪心计划。首先我们可以尝试确定一个最大的桶大小，这对后面的操作有很大的帮助。很显然，最大的桶大小就是与最短木板长度的差 $\leq l$ 的最大的一块木板。然后我们可以优先构造大小为最大大小的木桶，设此时找到的代表着最大溶剂的木板的下表为 $p$，我们应该尝试让长度 $\geq a_p$（$a$ 数组为木板长度的数组）的木板 $p$ 进行配对，同时更新最大长度的下标（即 `p -= 1`）。 

然后我们可以简单的统计一下剩下的桶的大小，求和即可。

### AC Code ：

```cpp
#include <iostream>
#include <algorithm>

#define int long long

using namespace std;

int n, k, t, ans, a[100009];

signed main() {
	cin >> n >> k >> t;
	for (int i = 1; i <= n * k; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n * k + 1);
	if (a[n] - a[1] > t) {
		cout << 0;
		return 0;
	}
	int p = n * k, cnt = 0;
	while (a[p] - a[1] > t) {
		p -= 1;
	}
	for (int i = n * k, j = p; i >= p + k; i -= (k - 1), j -= 1, cnt += 1) {
		ans += a[j];
	}
	for (int i = 1; i <= p - cnt; i += k) {
		ans += a[i];
	}
	cout << ans;
}
```

---

## 作者：xujingyu (赞：0)

## 思路：

一道贪心。

先将 $a$ 数组从小到大排序一次，因为每个木桶的容积为最短的木板的长度，易得必有一个木桶容积为 $a_1$。为了让剩下 $n-1$ 个木桶容积最大，就要让剩下 $n-1$ 个桶中最小木板最大。

所以需要找到一个下标 $p$ 即最大的木桶容积。所以 $p$ 满足 $a_p-a_1\leq l$ 且 $a_{p+1}-a_1>l$。为了满足要求，将下标为 $p$ 的木板与后面的 $k-1$ 根组成木桶，依此类推。

另：

* 若 $a_n-a_1>l$，输出 `0` 即可，因为有容积为 $a_1$ 的木桶后，别的木桶容积都不得大于 $a_1+l$。
* 开 `long long`。

## 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,k,t,a[100001],tot,sum,cnt,l;

signed main()
{
	scanf("%lld%lld%lld",&n,&k,&t);
	l = n * k;//木板数量
	for(int i = 1;i <= l;i++) scanf("%lld",&a[i]);
	sort(a + 1,a + l + 1);//排序
	if(a[n] - a[1] > t)//无法满足题意
	{
		printf("0");
		return 0;
	}
	int p = l;
	while(a[p] - a[1] > t) p--;//找到p
	tot = p;
    for(int i = l;i - k + 1 > p;i -= (k - 1))//组成木板
    {
        sum += a[tot--];
        cnt++;
    }
    p -= cnt;
    for(int i = 1;i <= p;i += k) sum += a[i];
    printf("%lld",sum);
	return 0;
}
```


---

## 作者：Tachibana27 (赞：0)

本题是个有点思维难度的贪心。

## 思路

最短的木板，直接 `sort` 一遍求出。

不难发现，排序后，如果 $a_n-a_1>l$ 那么必然无法组装成满足要求的桶，输出 $0$。接下来我们找一个 $pos$，使得 $a_{pos}-a_1 < l$ 并且 $a_{pos+1}-a_1>l$，那么 $pos$ 就是最大的容积了。

我们优先使用 $a_{pos}$，与后面的 $k-1$ 个组成木桶，即 $a_{pos}$ 到 $a_{pos+k}$，其次是 $a_{pos-1}$，以此类推。

更多细节可参考代码。

## 警钟

请开 `long long`。

## code

```cpp
int a[100086];
int n,k,l;
int pos;
int sum;
signed main(){
	n=read();
	k=read();
	l=read();
	for(int i=1;i<=n*k;i++)
		a[i]=read();
	std::sort(a+1,a+1+n*k);//将a数组排序 
	for(;pos<=n*k&&a[pos]-a[1]<=l;pos++);//找到pos 
	if(pos<=n){
		write(0);
		exit(0);
	}//如果无法组成满足要求的桶，输出0并退出 
	for(int i=1;n;n--){
		sum+=a[i];
		if(pos-i-n>=k)
            i+=k;//优先使用pos 
        else
            i=pos-n+1;
	}//组装木桶 
	write(sum);//输出答案 
	return 0;//完结撒花 
}
```

---

