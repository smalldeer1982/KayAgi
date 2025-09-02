# 【MX-X9-T1】『GROI-R3』Another Me

## 题目背景

一股巨大的斥力袭来。全身上下仿佛分裂成了透明的碎片。

镜中有一个模糊的人影。是「你」吗？还是仅仅来源于幻觉？无从知道。你想要向前走，可对方却保持着极端的默契向后退去。当你让步时，对方却又赶了上来。

已经没有任何能量支撑你接着思考下去了。但朝着棱镜中央那丝微弱的光源，*你无论如何都想要再靠近一点*。此外，还有对面的另一个「你」......

## 题目描述

给定一个长为 $n$ 的整数序列 $a_1,\ldots,a_n$。你可以进行任意多次操作（也可以不操作），每次操作你需要在如下两种形式中进行选择：

- 全局自增 $1$：对每个 $1 \leq i \leq n$，将 $a_i$ 自增 $1$；
- 全局自减 $1$：对每个 $1 \leq i \leq n$，将 $a_i$ 自减 $1$。

你希望让操作后的 $\max\limits_{i=1}^n \lvert a_i \rvert$ 最小，即最小化所有 $\lvert a_i\rvert$ 的最大值，其中，$\lvert a_i\rvert$ 表示 $a_i$ 的绝对值。你只需要计算这个最小化后的结果即可。

## 说明/提示

**【样例解释 #1】**

只需要使用一次全局自增 $1$，即可得到 $a = [-4, -1, 1, 3, 4]$。此时，$\lvert a_1 \rvert, \lvert a_2 \rvert, \lvert a_3 \rvert, \lvert a_4 \rvert, \lvert a_5 \rvert$ 分别为 $4, 1, 1, 3, 4$，最大值为 $4$。可以证明 $4$ 是你能够取到的最小值。

**【数据范围】**

| 测试点编号 | $n\le$ | $\lvert a_i \rvert \le$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $1\sim 2$ | $2$ | $100$ |  |
| $3\sim 4$ | $3$ | $500$ |  |
| $5\sim 6$ | $10$ | $10^4$ |  |
| $7\sim 8$ | $30$ | $10^6$ |  |
| $9\sim 10$ | $50$ | $10^8$ |  |
| $11\sim 12$ | $100$ | $5$ |  |
| $13\sim 16$ | $100$ | $10^9$ | A |
| $17\sim 18$ | $100$ | $10^9$ | B |
| $19\sim 20$ | $100$ | $10^9$ |  |

- 特殊性质 A：保证 $n$ 为偶数，且对每个满足 $1 \leq k \leq \frac n2$ 的整数 $k$，$a_{2k-1} = -a_{2k}$。
- 特殊性质 B：保证 $a_i \geq 0$。

对于 $100\%$ 的数据，保证 $1 \leq n \leq 100$，$-10^9 \leq a_i \leq 10^9$。

## 样例 #1

### 输入

```
5
-5 -2 0 2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6
1 -1 4 5 -1 4
```

### 输出

```
3
```

## 样例 #3

### 输入

```
18
9 9 8 2 4 4 3 5 3 0 9 0 2 2 8 1 1 5
```

### 输出

```
5
```

# 题解

## 作者：2011hym (赞：6)

## 解题思路

### 前言

这道题在我比赛的时候我原本想了几分钟没想到，结果一看**同时增加**直接笑了。

### 问题分析：

每次操作都是全局的，即对序列中的所有元素同时进行自增或自减。

我们需要找到一个操作次数 $k$，使得序列中的元素经过 $k$ 次操作后，所有元素的绝对值的最大值最小。

### 观察：

设操作次数为 $k$，则操作后的序列为 $a_i + k$ 或 $a_i - k$。

我们需要找到一个 k，使得 $max(|a_i + k|)$ 或 $max(|a_i - k|)$ 最小。

### 数学推导：

设 $min_a$ 为序列中的最小值，$max_a$ 为序列中的最大值。

如果我们进行 $k$ 次全局**自增**操作，则序列变为 $a_i + k$。

如果我们进行 $k$ 次全局**自减**操作，则序列变为 $a_i - k$。

我们需要找到一个 $k$，使得 $max(|a_i + k|)$ 或 $max(|a_i - k|)$ 最小。

### 最优解：

最优的 $k$ 应该是使得序列中的最小值和最大值对称分布在 $0$ 的两侧。

具体来说，我们可以通过调整 $k$，使得序列中的最小值和最大值关于 $0$ **对称**。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, minn = LLONG_MAX, maxn = LLONG_MIN, a[114], dif;
signed main() {
    // 输入
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        minn = min(minn, a[i]);
        maxn = max(maxn, a[i]);
    }
    // 计算最小值到 0 的距离
    dif = minn;
    maxn -= dif;
    minn = 0;
    // 计算最终结果
    if (maxn & 1) { // 判断是否为奇数
        cout << maxn / 2 + 1;
    } else {
        cout << maxn / 2;
    }
    return 0;
}
```
## 代码解释

### 输入：

读取 $n$ 和序列 $a_1$, $a_2$, $\dots$, $a_n$。

同时计算序列中的最小值 $minn$ 和最大值 $maxn$。

计算最小值到 $0$ 的距离：

计算 `dif = minn`，即最小值到 $0$ 的距离。

将序列中的所有元素减去 `dif`，使得最小值变为 $0$。

更新最大值 `maxn = maxn - dif`。

### 计算最终结果：

如果 $maxn$ 是奇数，则输出 `maxn / 2 + 1`。

如果 $maxn$ 是偶数，则输出 `maxn / 2`。

---

## 作者：Lovely_yhb (赞：6)

### 题意

给定一个序列，每次可以将整个序列加一或减一，问若干次操作后序列中绝对值最大的数最小是多少。

### 思路

这个题有坑点。

首先考虑序列中既有正数又有负数的情况，记一个最大值和最小值。

如果最小值绝对值大就加，直到加到最小值与最大值绝对值相等。否则最大值绝对值大就减，减到与最小值绝对值相等。设最大值为 $ma$，最小值为 $mi$，容易推出答案是 $\lceil\frac{|ma|+|mi|}{2}\rceil$。

但如果这样写的话会是 80pts。

考虑全是正数的情况，需要先把整个序列减上最小值，再按上面方式计算。全是负数同理，先把区间减去最大值再计算。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[105],ma=-0x3f3f3f3f,mi=0x3f3f3f3f;
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		ma=max(ma,a[i]);
		mi=min(mi,a[i]);
	}
	if(mi>0) ma-=mi,mi-=mi;
	if(ma<0) ma-=ma,mi-=ma;
	cout<<(abs(ma)+abs(mi)+1)/2;
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：3)

题目传送门：[P11797 【MX-X9-T1】『GROI-R3』Another Me](https://www.luogu.com.cn/problem/P11797)

### 过程

注意到真正有用的其实只有最大的 $a_i$ 和最小的 $a_i$（因为增减都是统一的），所以我们将它俩求出来，然后取差绝对值的平均数向上取整即可（这个值代表经过若干次增减后 $|a_{mxd}|$ 和 $|a_{mnd}|$ 最接近的时候较大值）。此时不论增加还是减少都会有一个数的绝对值增大。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[101],mxd=-1e9-1,mnd=1e9+1;
int main(){
	cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mxd=max(mxd,a[i]);
        mnd=min(mnd,a[i]);
    }
    cout<<abs(mxd-mnd+1)/2;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/204419510)。

---

## 作者：Sheep_YCH (赞：2)

## 洛谷 P11797

[题目传送门](https://www.luogu.com.cn/problem/P11797)

## 题目大意

我们有一个整数序列 $a_1, a_2, \dots, a_n$ ，通过进行任意次数的全局自增或全局自减操作，我们希望将所有元素的绝对值的最大值最小化。即，我们的目标是通过选择操作，使得操作后的序列中，绝对值最大的数尽可能小。

## 解题思路

1. 为了达到最小化绝对值最大值的目标，可以考虑将所有数集中到 $0$ 附近，就能得到最小的最大绝对值。

2. 然后我们可以发现，上述操作的关心点只与 $a$ 序列中的最大值和最小值有关，所以需要求出最大值和最小值。
3. 接下来如何实现第一步呢？我们发现，最大值和最小值的差值就是整个数列的最大差值，所以直接将最大值和最小值的差值除以 $2$ 就可以得到答案了。注意当差值为奇数的时候要上取整。

### 代码实现

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define ll long long
using namespace std;
const int MAXN = 1e6 + 5;
const int INF = 1e9 + 100;
int n, a[MAXN];
int Min = INF, Max = -INF;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	for(int i = 1; i <= n; i ++) Min = min(Min, a[i]), Max = max(Max, a[i]); 
	if(Max >= 0 && Min <= 0) cout << (abs(Min) + Max) / 2 + (abs(Min) + Max) % 2;
	else cout << (Max - Min) / 2 + (Max - Min) % 2;
	
	return 0;

}
```



### 复杂度分析

- **时间复杂度**：  
  - 找最小值和最大值的时间复杂度是 $O(n)$，因此整体时间复杂度是 $O(n)$，其中 $n$ 是序列的长度。

- **空间复杂度**：  
  - 由于我们只需要存储一个长度为 $n$ 的数组，空间复杂度是 $O(n)$。

---

## 作者：mcturtle (赞：2)

## 思路
找规律。

由于所有数只能同时操作，所以整个数组的最大差是无法变化的，求出整个数列极差的平均数并向上取整即可。

~~注意不开 `long long` 是要见祖宗的。~~
```cpp
#include <bits/stdc++.h>
using namespace std;
long long mx = -1e10, mi = 1e10;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        long long x;
        cin >> x;
        mx = max(mx, x), mi = min(mi, x);//求最值
    }
    cout << (mx - mi + 1) / 2;
    return 0;
}
```

---

## 作者：ziyaojia (赞：1)

## 题解：P11797 【MX-X9-T1】『GROI-R3』Another Me
这道题目不看标签就是一道找规律题，我们看到数据范围的 $a_i$ 有可能是负数，我们就可以分类思考：

考虑正数，全体加 1 会使最大值变大，全体减 1 就可以使最大值变小。

负数则相反，全体加 1 会使最大值变小，全体减 1 就可以使最大值变大。

所以我们要使最后的最大值尽可能的最小的话，就要使数列里的最大值和最小值尽可能的接近，再次分类讨论：

如果是分别两个正数的话，公式就是：$(max-min+1)/2$。

如果是一正一负的话，就要让负数的绝对值和正数尽可能的接近，所以公式也是 $(max-min+1)/2$。

如果是两个负数的话，就要让两个负数的绝对值尽可能的接近，所以公式还是 $(max-min+1)/2$。

所以说最后的公式就是 $(max-min+1)/2$ 了，接着把它套到代码中就好了。

### My Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,tmp,maxx=INT_MIN,minn=INT_MAX;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>tmp;
        minn=min(tmp,minn);
        maxx=max(tmp,maxx);
    }
    cout<<(maxx-minn+1)/2;
    return 0;
}

```

---

## 作者：cjx_AK (赞：1)

我们可以发现，每一次操作都会使答案加一或减一，如果一个答案减小，那么与他对应的最小或最大的数则会加一。

所以就要取一个中间值才是答案。答案要向上取整，因为题目要求最大值。

code：

```
#include<bits/stdc++.h>
using namespace std;
int n,max_,ans,min_=1e9;
int a[10001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],max_=max(max_,a[i]),min_=min(min_,a[i]);
	cout<<(max_-min_)/2+(max_-min_)%2;
}
```

---

## 作者：__CJY__ (赞：1)

## 思路
没啥好讲的。

就是要注意：数组中的所有元素只能同时操作。

所以结果就是最大值和最小值的平均值向上取整即可。

**十年 OI 一场空，不开 `long long` 见祖宗！**
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ma=INT_MIN,mi=INT_MAX;
int main(){
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll x;cin>>x;
		ma=max(ma,x),mi=min(mi,x);
	}
	cout<<(ma-mi+1)/2;
}
```

---

## 作者：M1__ (赞：1)

# 题解：P11797 【MX-X9-T1】『GROI-R3』Another Me
[题目传送门](https://www.luogu.com.cn/problem/P11797)
## 形式化题意
- 所谓让 $\max\limits_{i=1}^n \lvert a_i \rvert$ 最小，实际上就是令数列中的最小值和最大值的绝对值最接近。
- 换句话说，最优操作就是令他们的绝对值相等。
- 也就是说，这个数就是数轴上他们组成线段的中点，或是说这两个数的平均值。
- 因此令数列中最大值为 $a_{max}$，最小值为 $a_{min}$，则答案为 $\lceil \frac{|a_{max}-a_{min}|}{2} \rceil $。
## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e6+10;
ll T,a[MAXN],n;
int main() {
    cin>>n;
    for(int i=1;i<=n;i++){
		cin>>a[i];
	}
    sort(a+1,a+1+n);
    cout<<(abs(a[n]-a[1])+1)/2;
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

# 题解：P11797 【MX-X9-T1】『GROI-R3』Another Me
## 分析
要使绝对值最小，并且操作是所有数一起变化。则只有最小值或最大值会对结果产生影响。

如果最小值的绝对值大于最大值的绝对值，就全局加一，反之全局减一。最终最小值和最大值会变得平均，此时数组中最大的绝对值最小。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[1000005];
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        
    }
    sort(a+1,a+1+n);
    while(abs(a[1])>abs(a[n]))
    {
        a[1]++,a[n]++;
    }
    while(abs(a[n])>abs(a[1]))
        {
            a[1]--,a[n]--;
        }
    cout<<max(abs(a[1]),abs(a[n]));
}

---

## 作者：Pufflet233 (赞：1)

### 分析题意
第一行输入一个整数 $n$ ，第二行输入 $n$ 个整数 $a_1,\ldots,a_n$ ，现在可以对每一个 $1 \leq i \leq n$ 都增加 $1$ 或减少 $1$ ，求对于全部 $1 \leq i \leq n$ ，找 $\lvert a_i\rvert$ 的最大值最小可能是什么， $\lvert a_i\rvert$ 代表 $a_1$ 的绝对值。
### 解题思路
我们分多类情况思考：  

1. 当 $n = 1$ 时：

   这时候只有一个数字 $a_1$ 。如果 $a_1$ 是正整数，我们只需要进行 $a_1$ 次全局自减 $1$ 就能让 $a_1$ 变成 $0$ 。

   如果 $a_1$ 是负整数，我们只需要进行 $a_1$ 次全局自增 $1$ 就能让 $a_1$ 变成 $0$ 。

   如果 $a_1$ 是 $0$ ，我们不需要进行任何操作就能让 $a_1$ 变成 $0$ 。

   可以注意到无论 $a_1$ 是什么数字，我们都能把 $a_1$ 变成 $0$ ，因此 $\lvert a_1\rvert$ 的最小可能一定为 $0$ ，因此如果 $n = 1$ 时，直接输出 $0$ 即可。

1. 当 $n > 1$ 时：

   首先我们可以注意到，对于所有 $1 \leq i \leq n$ ，如果 $a_i$ 既不是最大值也不是最小值，那么 $a_i$ 一定不会是 $\max\limits_{i=1}^n \lvert a_i \rvert$ ，因为 $\lvert a_i \lvert$ 一定会比这 $n$ 个数中最大值的绝对值或者最小值的绝对值中其中一个或两个要小，全局自增和全局自减是对全部数都改变， $\lvert a_i \lvert$ 无论如何都不会成为 $\max\limits_{i=1}^n \lvert a_i \rvert$ 。

   因此如果要找 $\max\limits_{i=1}^n \lvert a_i \rvert$ 最小的可能，我们只需要观察 $\max\limits_{i=1}^n a_i$ 和 $\min\limits_{i=1}^n a_i$ 即可。接下来让我们观察一下该如何全局自增或全局自减可以让 $\max\limits_{i=1}^n \lvert a_i \rvert$ 最小。

   例如 $\max\limits_{i=1}^n a_i = 5$ , $\min\limits_{i=1}^n a_i = -8$ 时，此时 $\max\limits_{i=1}^n \lvert a_i \rvert = 8$ ，如果我们进行全局自减， $\min\limits_{i=1}^n a_i$ 会越来越小，导致 $\max\limits_{i=1}^n \lvert a_i \rvert > 8$ ， $\max\limits_{i=1}^n a_i$ 和 $\min\limits_{i=1}^n a_i$ 的差也会越来越大，这个时候我们进行全局自增，令 $\max\limits_{i=1}^n a_i$ 和 $\min\limits_{i=1}^n a_i$ 的差越来越小，可以看到当 $\max\limits_{i=1}^n a_i = 6$ , $\min\limits_{i=1}^n a_i = -7$ 和  $\max\limits_{i=1}^n a_i = 7$ , $\min\limits_{i=1}^n a_i = -6$ 时， $\max\limits_{i=1}^n a_i$ 和 $\min\limits_{i=1}^n a_i$ 的差是最小的情况，此时 $\max\limits_{i=1}^n \lvert a_i \rvert = 7$ ，如果我们再继续全局自增， $\max\limits_{i=1}^n \lvert a_i \rvert > 8$ ， $\max\limits_{i=1}^n a_i$ 和 $\min\limits_{i=1}^n a_i$ 的差会越来越大，导致 $\max\limits_{i=1}^n \lvert a_i \rvert$ 越来越大。

   可以注意到当 $\lvert\max\limits_{i=1}^n a_i \lvert$ 和 $\lvert\min\limits_{i=1}^n a_i \lvert$ 的差尽可能小时， $\lvert\max\limits_{i=1}^n a_i \lvert$ 和 $\lvert\min\limits_{i=1}^n a_i \lvert$ 的较大值就是 $\max\limits_{i=1}^n \lvert a_i \rvert$ 最小的值。

   通过观察，可以进一步注意到当 $\max\limits_{i=1}^n a_i$ 为正整数， $\min\limits_{i=1}^n a_i$ 为 $0$ 或非正整数，或$\max\limits_{i=1}^n a_i$ 为负整数， $\min\limits_{i=1}^n a_i$ 为 $0$ 或非负整数，或 $\max\limits_{i=1}^n a_i$ 及 $\min\limits_{i=1}^n a_i$ 其中一个为 $0$ 时，这两个数的绝对值的平均值四舍五入取整就是 $\max\limits_{i=1}^n \lvert a_i \rvert$ 尽可能小的值。如果 $\max\limits_{i=1}^n a_i$ 和 $\min\limits_{i=1}^n a_i$ 都为正整数或负整数的情况下，就要先把其中一个数通过全局自增或全局自减变成 $0$ 才能通过这两个数的绝对值的平均值找出答案。

### 代码实现
根据以上思路找出当 $\lvert\max\limits_{i=1}^n a_i \lvert$ 和 $\lvert\min\limits_{i=1}^n a_i \lvert$ 的差尽可能小时， $\lvert\max\limits_{i=1}^n a_i \lvert$ 和 $\lvert\min\limits_{i=1}^n a_i \lvert$ 的较大值即可。

以下是实现本功能的 CPP 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    if (n == 1) {//当n为1，输出0
        cout << 0 << endl;
        return 0;
    }
    vector<int> a(n);
    for (int i = 0;i < n;++i) {
        cin >> a[i];
    }
    int x = max_element(a.begin(), a.end()) - a.begin();
    int y = min_element(a.begin(), a.end()) - a.begin();//利用max_element()和min_element()获取最大值和最小值的位置
    int sum;
    if (a[x] > 0 && a[y] > 0) {
        sum = a[x] - a[y];//若都为正整数，平均值为最大值减去最小值除以2
    }
    else if (a[x] < 0 && a[y] < 0) {
        sum = abs(a[y]) - abs(a[x]);//若都为负整数，平均值为最小值的绝对值减去最大值的绝对值除以2
    }
    else {
        sum = abs(a[x]) + abs(a[y]);//否则平均值为这两个数的绝对值的和除以2
    }
    cout << sum / 2 + (sum % 2 == 1) << endl;
    return 0;
}
```

---

## 作者：getchar_unlocked (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11797)

### 思路

无论增加，都是整体增减，所以若集体增加 $x$，最终结果即为 $f(x)=\max\limits_{i=1}^n\lvert a_i+x\rvert$。

而 $f(x)$ 其实是个单峰函数，可以进行二分。具体地，判断 $f(x)$ 与 $f(x+1)$ 的值，判断其状态上升或下降，并最终找到最小值即可。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=105;
int n,a[N];
int check(int x){
	int res=0;
	for(int i=1;i<=n;++i)
		res=max(res,llabs(a[i]+x));
	return res;
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	int l=-1e18,r=1e18,ans=LLONG_MAX;
	while(l<=r){
		int mid=(l+r)>>1,ck=check(mid);
		ans=min(ans,ck);
		if(ck>check(mid+1))
			l=mid+1;
		else r=mid-1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：zsjaaaxy (赞：1)

根据题意，可以发现 $answer=max-min$ ，其中 $min$ 表示最小数， $max$ 表示最大数，求出 $max$ 、$min$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[10000],minx=INT_MAX,maxx=-INT_MAX;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        maxx=max(maxx,a[i]);
        minx=min(minx,a[i]);
    }
    long long ans=maxx-minx;
    if(ans%2==0)
    {
        cout<<ans/2;
    }
    else
    {
        cout<<ans/2+1;
    }
    return 0;
}
```

---

## 作者：Circle_Table (赞：1)

我们知道:

$|x|=|x-0|$ 

即一个数的绝对值是它在数轴上表示的点与原点的距离

---

稍作思考，画一个图(以样例一为例):

![](https://cdn.luogu.com.cn/upload/image_hosting/6c0lx1lz.png)
显然，所有数据绝对值的最小值就是最大值与最小值分别到原点距离的最小值。容易想到令这两点的中点为原点重新建立数轴，从而求出最小绝对值。

---

以现在建立的数轴:

$|x'|=|x'-0|$

显然最短距离是左右端点距离的一半。

简而言之，求出最大值与最小值之差的一半(显然是向上取整)再输出即可。

---

AC代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,ans;
int amin=2147483647,amax=-2147483648;//方便后文取最小值与最大值操作
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		amin=min(amin,a);
		amax=max(amax,a);
	}
	ans=amax-amin;//显然,amax>=amin,因此amax-amin>=0,故不需要绝对值
	cout<<(ans+1)/2;//向上取整
	return 0;
}
```
蒟蒻第一篇题解（求大佬指点）

---

## 作者：aaalys (赞：0)

# P11797 Another Me 题解

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/P11797)

给你一个长度为 $n$ 的序列，让你找到一个偏移量 $det$（$det$ 为正表示 $det$ 次全局自增 1，为负表示 $-det$ 次全局自减 1），使得 $\max\limits_{i=1}^n \lvert a_i + det\rvert$ 最小，并输出这个数。

## 思路

### 选择二分

题目中要求最大值最小，首先想到二分，即二分最终的答案 $ans=\max\limits_{i=1}^n \lvert a_i + det\rvert$。

二分有两个关键点：边界和判断函数。

### 二分的判断函数

首先先看判断函数，假设最终的答案是 $m$，就需要保证对于 $\forall i\in[1,n]$，都必须满足 $\lvert a_i + det\rvert\le m$，即 $-m - a_i \le det \le m-a_i$。

所以对于 $\forall i\in[1,n]$，$det$ 必须在 $[-m-a_i,m-a_i]$ 这个区间范围内。

最终只需要判断 $n$ 个 $[-m-a_i,m-a_i]$ 是否有交集。如果有，表示答案可以为 $m$，$det$ 在交际范围内；如果没有，则表示不可以。

### 边界

因为一个数的绝对值 $\lvert x\rvert \ge 0$，所以答案 $ans = \max\limits_{i=1}^n \lvert a_i + det\rvert \ge 0$，因此左边界取 $0$。

如果取 $det=0$，那么此时 $\max\limits_{i=1}^n \lvert a_i + det\rvert = \max\limits_{i=1}^n \lvert a_i\rvert$，可以看出最终的答案 $ans\le\max\limits_{i=1}^n \lvert a_i\rvert$，因此右边界取 $\max\limits_{i=1}^n \lvert a_i\rvert$，本题最大为 $10^9$，因此右边界取 $10^9$。

## Code（只展示关键代码）

```cpp
bool check(int m){//判断函数
    int l = -2e9, r = 2e9;//初始设置一个大区间
    for (int i = 1; i <= n; i++){
        int nl = -m - a[i], nr = m - a[i];//nl<=det<=nr
        l = max(l, nl);//更新左端点
        r = min(r, nr);//更新右端点
        if (l > r)return 0;//没有交集，返回0
    }
    return 1;
}

int l = 0, r = 1e9;//左右边界
while (l < r){//二分
    int mid = l + r >> 1;
    if (check(mid))r = mid;
    else l = mid + 1;
}
```

## 后记

求管理员通过。

Update in 2025/3/16 修改了一些语言错误。

Update in 2025/5/5 修改了一些表达错误

---

## 作者：wwppd (赞：0)

## 思路
不难发现有规律，先找最大值和最小值，再根据规律输出。

规律：最大值减最小值加一除以二就为结果。
## 代码
```
#include<bits/stdc++.h>//万能头文件
using namespace std;

int main()
{
    int n;//定义
    cin>>n;//输入
    int a=-1e9,b=1e9;//定义
    for(int i=1;i<=n;i++)
    {
        int y;
        cin>>y;//输入
        a=max(a,y);//求最大
        b=min(b,y);//求最小
    }
    cout<<(a-b+1)/2;//输出
    return 0;
}
```

---

## 作者：lznxes_xh (赞：0)

来一发三分的题解。

首先，研究这个函数，如果整体加的值为 $x(-10^9\le x\le 10^9)$，最小值表示为 $mi$，最大值表示为 $ma$，则花费为 $\max(|ma|,|mi|)$。

不难发现函数具有**单谷性**。因此考虑三分，求谷值即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[105];
int ma = INT_MIN,mi = INT_MAX;
int check(int mid)
{
	int c = ma + mid,b = mi + mid;
	return max(abs(c),abs(b));
}
int sanfen(int l,int r)
{
	int ans;
	while (l < r)
	{
		int mid1 = l + (r - l) / 3;
		int mid2 = r - (r - l) / 3;
		if (check(mid1) > check(mid2)) l = mid1 + 1;
		else r = mid2 - 1;
	}
	return check(l);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;

	for (int i = 1,x;i <= n;i++)
	{
		cin >> x;
		ma = max(ma,x);
		mi = min(mi,x);
	}
	cout << sanfen(-1000000000,1000000000);
	return 0;
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
为了让数组中最大的绝对值最小，要让数组卡在零相对平衡，就是离零的距离相等或差一。

不难发现，最后的最大值只与数组中的极值有关。

简要证明：

设最大为 $mx$ 最小为 $mn$ 另一个为 $x$。

当将 $mx$ 和 $mn$ 在零相对平衡时，$x$ 的绝对值一定小于等于 $mx$ 或 $mn$ 的。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100100],k,mx=-1e9,mn=1e9;//初始化
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)mx=max(mx,a[i]),mn=min(mn,a[i]);//找最大最小
	cout<<(mx-mn+1)/2;//平衡
}
```

---

## 作者：Stars_Traveller (赞：0)

# 题解：P11797 【MX-X9-T1】『GROI-R3』Another Me
## 分析
简单题。

观察到操作是全局的，也就是所有元素都会跟着变。那么看绝对值的最大值也就是看最大值和最小值。仅对最大值和最小值考虑。让他们尽量接近即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a, mx, mi=1e9;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        mx=max(a,mx);
        mi=min(a,mi);
    }
    while(abs(mi)>abs(mx))
    {
        mx++,mi++;//全局自增1
    }
    while(abs(mx)>abs(mi))
    {
        mi--,mx--;//全局自减1
    }
    cout<<max(abs(mi),abs(mx));
}

---

## 作者：easy42 (赞：0)

首先一点：若一个数的绝对值比另一个数的绝对值小，则同加同减之后一个数的绝对值仍然比另一个数的绝对值小。

所以我们只要看最大的和最小的就好了。

设最大的为 $maxx$，最小的为 $minn$，最小化后的结果为 $\lceil{(maxx-minn)\div2}\rceil$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n , a[100005] , maxx = -INT_MAX , minn = INT_MAX;
signed main(){
	cin >> n;
	for(int i = 1;i <= n;i ++){
		cin >> a[i];
		maxx = max(maxx , a[i]);
		minn = min(minn , a[i]);
	}
	if((maxx - minn) % 2 == 0) cout << (maxx - minn) / 2;
	else cout << (maxx - minn) / 2 + 1;
	return 0;
}
```

---

## 作者：huanglihuan (赞：0)

### Solution
给 $a$ 排序，然后 $\lfloor\frac{a_n-a_1+1}2\rfloor$？  
我想复杂了……  
给 $a$ 排个序，然后二分，每个 $mid$ 的答案为 $\max\{\sum_{i=1}^n|a_i+mid|\}$，最终答案在所以 $mid$ 中取 $\min$，时间 $n\log 2\times10^9$。
### Code
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 988444333
#define MOD 1000000007
#define in(x,y,z) x>=y&&x<=z
using namespace std;
const int N = 2e6 + 5;
int a [N];
inline int read ()
{
	int x = 0;
	char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return x;
}
inline void write (int x)
{
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
int sum (int x)
{
	int p = 1;
	while (p <= x) p <<= 1;
	return p >> 1;
}
signed main ()
{
	int n;
	cin >> n;
	for (int i = 1;i <= n;i ++) cin >> a [i];
	if (n == 1) return cout << 0,0;
	if (n == 2) return cout << abs (a [1] - a [2] + 1) / 2,0;
	sort (a + 1,a + n + 1);
	int ma = a [n],mi = a [1];
	int l = mi - ma;
	int r = ma - mi;
	int ans = 0x7fffffff;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		int cnt = 0;
		for (int i = 1;i <= n;i ++) cnt = max (cnt,abs (a [i] + mid));
		ans = min (ans,cnt);
		if (cnt > abs (a [1] + mid)) r = mid - 1;
		else l = mid + 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：lcfollower (赞：0)

分讨题，但是红（可能是我太菜了）？

容易发现负数减小绝对值需要加法而会带动正数绝对值增大，正数绝对值减小需要减法而负数的绝对值会增大。

因此考虑如下四种情况（记 $a$ 序列最小值为 $mn$，最大值为 $mx$）：

- $\forall a_i = 0$，结果为 $0$。
- $\forall a_i > 0$，则一定会找到一个 $p$ 使得 $-(mn - p) = mx - p$（$mn\le p\le mx$），得 $p = \frac{mx + mn}{2}$，答案为 $\max\{p-mn,mx-p\}$（$p$ 可能是浮点数，此时两者需要比最大值）。
- $\forall a_i < 0$，则一定会找到一个 $p$ 使得 $-(mn + p) = mx + p$（$-mx\le p\le -mn$），得 $p = \frac{-mx-mn}{2}$，答案为 $\max\{-mn - p ,mx + p\}$。
- $mx>0$ 且 $mn < 0$，此时就是上面两种情况的总和（可加可减），取最优的即可。

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 100000000000000

using namespace std;

inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}

const int N = 1e6 + 10;
int n ,a[N];
bool fu ,zero ,zheng ;
int mx = -inf ,mn = inf;

signed main (){
  n = read ();

  up (i ,1 ,n) a[i] = read ();

  sort (a + 1 ,a + 1 + n);

  up (i ,1 ,n){
    fu |= (a[i] < 0) ;
    zero |= (a[i] == 0);
    zheng |= (a[i] > 0);
    mx = max (mx ,a[i]) ,mn = min (mn ,a[i]);
  }

  if (fu && zheng){
    int p = (-mn - mx) / 2 ,p1 = (mx + mn) / 2;
    int res1 = max(abs(mn + p) ,abs(mx + p)) ;
    int res2 = max(abs(mn - p1) ,abs(mx - p1)) ;
      
    writeln (min (res1 ,res2));

  } else if (fu){
    int p = (-mn - mx) / 2;
    int res = max(abs(mn + p) ,abs(mx + p));
    writeln (res);
  } else if (zheng){
    int p = (mx + mn) / 2;
    int res = max(abs(mn - p) ,abs(mx - p));
    writeln (res);
  } else puts("0");
  
  return 0 ;
}
```

---

## 作者：zhangrui2023 (赞：0)

### 题意

进行操作使序列中 $a_i$ 的绝对值的最大值最小。

### 思路

注意到当序列中绝对值最大的数越接近于 $0$ 则答案越优，且答案只于序列最大和最小值有关。

所以，找出序列中的最大值和最小值，将其相减。

如果结果是奇数，将其除以 $2$ 再 $+1$。

如果结果是偶数，将其除以 $2$。

### AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[1010],maxx=-1111111111,minx=1111111111;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        maxx=max(maxx,a[i]);
        minx=min(minx,a[i]);
    }
    if((maxx-minx)%2==0)cout<<(maxx-minx)/2;
    else cout<<(maxx-minx)/2+1;
    return 0;
}
```

---

