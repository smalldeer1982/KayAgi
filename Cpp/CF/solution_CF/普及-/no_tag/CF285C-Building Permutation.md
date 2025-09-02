# Building Permutation

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

You have a sequence of integers $ a_{1},a_{2},...,a_{n} $ . In one move, you are allowed to decrease or increase any number by one. Count the minimum number of moves, needed to build a permutation from this sequence.

## 说明/提示

In the first sample you should decrease the first number by one and then increase the second number by one. The resulting permutation is $ (2,1) $ .

In the second sample you need 6 moves to build permutation $ (1,3,2) $ .

## 样例 #1

### 输入

```
2
3 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
-1 -1 2
```

### 输出

```
6
```

# 题解

## 作者：Jerrycyx (赞：0)

## 思路

典型的**贪心算法**。

如果要用最少的步骤把原数列改成从 $1$ 到 $n$ 的有序数列，即：使数列里每个数与目标数列的差之和最小。所以可得：

1. **将原数列排序**

2. **计算每个数与目标数列的差值**

3. **累加，输出答案**

最终得到的答案是：

$$\sum\limits_{i=1}^n{\lvert a_i-i\rvert}$$

这样得到的答案必定最小，且时间复杂度为 $O(n)$。

还有，累加到答案的过程中可能会超出 `int` 范围，所以答案变量应该使用 `long long`。

其它细节见代码注释。

## $\textcolor{#52C41A}{\texttt{AC}}$ 代码

```cpp
#include<cstdio>
#include<algorithm>	//包含快速排序函数 sort 
#include<cmath>		//包含绝对值函数 abs 
#define N 300005
using namespace std;

int n,a[N];
long long ans=0;	//答案变量开 long long 

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);		//sort 快速排序函数 
	for(int i=1;i<=n;i++)
		ans+=abs(a[i]-i);	//注意“差值”不能单纯两数相减，要用绝对值函数 abs 
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：tanghg (赞：0)

这是一道贪心题。

注意，还是那句古话：十年 OI 一场空，不开 longlong 见祖宗。开 longlong!

### 思路：

我们可以看到出来，如果想用最短的次数将原数组变成 $1∼n$ 的形式，自然要将每一个数都在 $1∼n$ 中找到一个与其最接近的即可，这就是这道题的贪心策略。

我们可以对原数组进行从小到大的排序，这样就可以把数跟数组下标连接起来（数组下标从 $1$ 开始正好是要求的序列）然后就是输出 $\sum\limits_{i=1}^n{\lvert i-a_i\rvert}$ 即可。

时间复杂符为 $O(n)$。

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a[100005],n;
int main(){
    cin>>n;
    for (int i = 1; i <=n ; ++i) {
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    ll ans=0;
    for (int i = 1; i <=n ; ++i) {
        ans+= abs(i-a[i]);
    }
    cout<<ans;
    return 0;
}

```


---

## 作者：Code_AC (赞：0)

### 题目大意：
就是给你一个长度为 $n$ 的序列 $a_i$ ，现在只能进行 $+1$ 和 $-1$ 的操作，问你最少需要多少步操作才能将原序列变为下标从 $1$ 到 $n$ ，且数值同样从 $1$ 到 $n$ 的序列。

### 题目分析：

这题我们可以使用贪心的策略，我们这样想：

- 将序列按从小到大的顺序排序后，每个数和其对应下标的差值必定最小，所以，将这些差值的绝对值加和就是我们要求的答案。

看这道题的数据范围， $-10^9 \leqslant a_i \leqslant 10^9$ ，需要开 $long \ long$ 。

**Code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=3e5+5;

int n;       
int a[MAXN];
int ans;

signed main()
{
	scanf("%lld",&n);
	for(register int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(register int i=1;i<=n;i++)
		ans+=abs(a[i]-i);
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Sternenlicht (赞：0)

思路：模拟。依题意可知，要将第 $i$ 个元素 $a_i$ 变为 $i$。我们可将 $a$ 数组排序，排序后 $a_i$ 与 $i$ 的差值肯定是最小的，只要把差值的绝对值求和就是答案。

注意：记录答案时，要开 long long。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 3e5+10;
int a[N],n;
LL ans;
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++)ans+=abs(a[i]-i);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：lmndiscyhyzdxss (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF285C)
## 大意
给出 $ n $ 个整数，通过最少次数的加 $ 1 $ 减 $ 1 $ 操作把原数列改造成只含 $ 1-n $ (每个数字只含一次)的数列---把 $ a[i] $ 的值通过最少次数的加 $ 1 $ 减 $ 1 $ 改成 $ i $ ,求最少的操作次数。
## 思路
- 打眼一看，直接模拟。
- 依次枚举，个数依次加上 $ a[i]-i $ 或 $ i-a[i] $ ,为了方便，直接写 $ abs(a[i]-i) $ 即可。
- 注意： $ gs $ 不开 $ long long $ 见祖宗。 
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300010];
long long gs;
int main() {
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)gs+=abs(a[i]-i);
    cout<<gs;
    return 0;
}
```

---

## 作者：TulipeNoire (赞：0)

### 思路

看到这道题，考虑贪心。

假设有两个数 $x$ 和 $y(x\le y)$，它们要变成 $p$ 和 $q(p+1=q)$。

这时候我们分三种情况讨论。

+ 当 $x\le p$ 且 $y\le q$ 时，将 $x$ 变为 $p$ 或 $q$ 是等价的 $(p-x+q-y=p-y+q-x)$ 。

+ 当 $x\le p$ 且 $y>q$ 时，将 $x$ 变为 $p$ 是较优的 $(p-x+y-q<q-x+y-p)$ 。

+ 当 $x>p$ 且 $y>q$ 时，将 $x$ 变为 $p$ 或 $q$ 是等价的 $(x-p+y-q=x-q+y-p)$ 。

所以将原数列排序并将新数列第 $i$ 元素变为 $i$ 可满足上述所有的最优情况。

### code

```cpp
#include<bits/stdc++.h>
#define N 300005
using namespace std;
int n,a[N];
long long ans;//注意long long
int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++) {
        ans+=abs(a[i]-i);
    }
    printf("%lld",ans);
    return 0;
}
```

---

