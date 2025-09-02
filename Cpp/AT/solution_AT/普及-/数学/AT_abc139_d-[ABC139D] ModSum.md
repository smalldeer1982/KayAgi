# [ABC139D] ModSum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc139/tasks/abc139_d

整数 $ N $ に対して、$ \{1,\ 2,\ ...,\ N\} $ を並べ替えた数列 $ \{P_1,\ P_2,\ ...,\ P_N\} $ を選びます。

そして、各 $ i=1,2,...,N $ について、$ i $ を $ P_i $ で割った余りを $ M_i $ とします。

$ M_1\ +\ M_2\ +\ \cdots\ +\ M_N $ の最大値を求めてください。

## 说明/提示

### 制約

- $ N $ は $ 1\ \leq\ N\ \leq\ 10^9 $ を満たす整数である。

### Sample Explanation 1

$ \{1,\ 2\} $ を並び替えた数列として $ \{P_1,\ P_2\}\ =\ \{2,\ 1\} $ を選ぶと、$ M_1\ +\ M_2\ =\ 1\ +\ 0\ =\ 1 $ となります。

## 样例 #1

### 输入

```
2```

### 输出

```
1```

## 样例 #2

### 输入

```
13```

### 输出

```
78```

## 样例 #3

### 输入

```
1```

### 输出

```
0```

# 题解

## 作者：Alter_Native (赞：3)

# [ABC139D] ModSum 题解

[ABC139D ModSum](https://www.luogu.com.cn/problem/AT_abc139_d)

#### 题目大意

给定 $N$ 个数，找出这 $N$ 个数的一种排列，使其中每一个数对它的下标取模的得数之和尽可能大。求这个最大值。

#### 解题思路

我们可以假设这 $N$ 个数的位置不会变化，只更改每一个数对应的下标。

一个数对比它大的任意一个数取模，得到的总是它本身。比如 $3 \bmod 4$，得到的是 $3$。

经过简单推导，可以得出对 $N$ 个数的一种下标安排方式：

$\ \ \ \ \ \ \ \ \ 1\qquad2\qquad3\qquad...\qquad N-1\qquad N$

$\ \ \ \ i:2\qquad3\qquad4\qquad...\qquad N \qquad\quad\ \ \ 1$

$M_i:1\qquad 2\qquad 3\qquad ...\qquad N-1 \qquad 0$

可以验证，这样得到的余数和总是最大的，为：

$0+1+2+...+(N-1)$。

那我们就可以结和等差数列的求和公式，求出这道题的答案：

$S_n=\frac{(0+N-1)\times N}{2}=\frac{N(N-1)}{2}$

#### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
    long long n;
    scanf("%lld",&n);
    printf("%lld",(n-1)*n/2);
    return 0;
}
```

---

## 作者：ruanwentao666 (赞：1)

# [ABC139D] ModSum题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc139_d)

------------

## 结论证明

首先给出结论:
$$ ans = \frac{n \times (n-1)}{2} $$

证明呢也很简单：

对于 $ 0 \le i \le n-1 $ 的情况，只需要让 $i$ 对 $  i+1 $ 取余即可

对于 $ i = n $ 的情况，只需将 $i$ 对 $1$ 取余即可。

所以对 $M$ 数组求和可以得到：
$$ 0 + 1 + 2 + \dots + n - 1 $$

运用高斯求和公式即可得出上面的结论。

## 完整代码

下面给出 AC 代码：
```cpp
#include<iostream>
using namespace std;
long long n;
int main(){
    cin>>n;
    cout<<(n-1)*n/2<<endl;
    return 0;
}
```
注：不开 long long 见祖宗！

---

## 作者：tZEROちゃん (赞：1)

结论：输出 $\dfrac{N(N - 1)}{2}$。

证明如下：

由题意可知，$1 \sim N$ 之间的每个数都出现了恰好一次，而我们要求的值是：

$$a_1 \bmod 1 + a_2 \bmod 2 + a_3 \bmod 3 + \cdots + a_N \bmod N$$

不难发现每一项的最大值分别是 $0, 1, 2, \cdots, N - 1$，于是可以发现让 $a_i = i - 1(i \ge 2)$，$a_1 = N$ 是可以取到每一项的最大值的，所以我们直接输出 $0 \sim N - 1$ 的和就可以了。

等差数列求和公式可知，$0 \sim N - 1$ 的和等于 $\dfrac{(0 + N - 1) \cdot N}{2}$，即 $\dfrac{N\cdot (N - 1)}{2}$，输出即可。

```python
n = int(input())
print(n * (n - 1) // 2)
```

---

## 作者：洛璟 (赞：1)

这道题……题目表述的确让人难受……要是看懂了题目表述，那么也就是橙-黄的难度。

大意就是有一个数组 $a_{i}$，且 $a_{i}= i$ 求将 $a_{i}$重新排列后 $a_{i}\space mod \space i$的最大值 

## Solution：

我们其实不难想到对一个数取模之后，得到的数必然小于模数，那么我们不难想到让一个数取模的结果尽量大，就需要找一个比它本身还大的数字作为模数，所以我们就会想到把每个数向前移动一个单位，也就是令 $a_{i}=i-1$，$a_{1}=n$ ，那我们不难得出$i-1\space mod \space i=i-1$，那么这个问题就变成了如何求等差数列之和的问题了。

至于证明……我也不会，~~易证得此结论~~

等差数列公式，想必大家都是知道的，因此不再赘述。

哦对了，由于数据范围的关系，因此中间计算时应当乘上1ll，将中间过程转化为long long 类型

### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
signed main()
{
    n = read();
    int ans = 1ll*n * (n - 1) / 2;
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：Ra_whi (赞：1)

# 题目思路:
### 先输入，再套公式 $a \times (a+1) \div 2$  即等差数列求和，最后输出即可。
$Q:$ 为什么公式是 $a \times (a+1) \div 2$？  
$A:$ 显然当 $P_i=N$ 的时候 $\sum_{i=1}^{n} M_i$ 最大，所以这道题就是一道等差数列求和的问题，而等差数列求和的公式是 $a \times (a+1) \div 2$。

#### PS：数据原因必须开 ```long long```!
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

long long a;//由于数据原因，需开 long long

int main()
{
    cin>>a;
    cout<<a*(a-1)/2<<endl;//套用公式等差数列求和输出
    return 0;
}
```

---

## 作者：qjxqjx (赞：1)

## 题目大意：
有一个数组 $a$，且 $a_i=i$，求将数组排列后 $a_i$ $\bmod$ $i$ 后的最大值。

## 题目思路：
超级水题。首先可以发现一个数取模之后，所得数必定会小于取模的数，所以让一个数取模的结果尽可能的大，就要找一个比数本身还大的数作为模数，那么我们就把每个数向前移动一个单位，也就是，易得 $i-1$ $\bmod$ $i$ $=i-1$。向后枚举，可得结果为等差数列求和,套公式即可：

$n\times (n+1)\div 2$

注意：数据原因开 $long$ $long$

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;//千万要开long long
int main(){
    cin>>n;
    cout<<n*(n-1)/2;//套公式输出
    return 0;
}
```

---

## 作者：Flyingsnow (赞：0)

## 结论

$$
ans=\frac{n(n-1)}{2}
$$

## 证明

因为我们知道 $a \bmod b$ 的值不可能大于 $b$ 那么就很显然我们就可以把 $b+1$ 当成模数，这样的答案会尽可能大。在题目中就是让 $a_i=i-1(i\ge2)$，让 $a_1 = n$。

所以我们只需要将每个数向前移一位，这道题公式就变成了 $\frac{n(n-1)}{2}$，也就是等差数列的求和公式。

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
	long long n;
	scanf("%lld", &n);
	printf("%lld", n * (n - 1) / 2);
	return 0;
}

```

---

## 作者：kdy20100729 (赞：0)

## 题目大意：
有一个数组 $a$，且 $a_i=i$，求将数组排列后 $a_i \bmod i$ 后的最大值。

## 解题思路:
套公式 $n \times (n+1) \div 2$  即等差数列求和，最后输出即可。

$Q:$ 为什么公式是 $n \times (n+1) \div 2$ ？  
$A:$ 显然当 $P_i=N$ 的时候 $\sum_{i=1}^{n} M_i$ 最大，所以这道题就是一道等差数列求和的问题，而等差数列求和的公式是 $n \times (n+1) \div 2$。  
$\mathtt{PS: \textbf{不开 long long 见祖宗}}$


## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
signed main()
{
    cin >> n;
    cout << n*(n-1)/2;//用公式输出
    return 0;
}
```

---

## 作者：xiezihanAKIOI (赞：0)

由题意得本题要求 $q_i\bmod i$。那么如何使 $q_i$ 尽量大呢，很显然当 $i$ 比 $p_i$ 大时，那么 $q_i\bmod i$ 就是他本身。。所以当 $i$ 大于 $q_i$ 时是最优解，所以对于 1 到 $n$ 的每个数，只要使 $i$ 大于 1 即可。

所以本题的最优解也就是 $1+2+3+...+n$ 根据等差序列求和公式。我们又可以把时间从 $O(n)$ 降到 $O(1)$。

虽然题目说有什么都不输的情况，但样例似乎没有。我还是打上吧。

代码如下（记得开 long long 本人被卡了近半个钟）：

```cpp
#include <bits/stdc++.h>

using namespace std;

long long n;

int main ()
{
    cin >> n;
    if (n == 1) return 0;
    else cout << (n - 1) * n / 2;
    return 0;
}
```


---

## 作者：_lgh_ (赞：0)

## 思路：
看到数据范围不难发现题目的时间复杂度应为 $O(1)$ 。

答案：

$$\sum_ {i=1}^{n} i \bmod p_i$$


易得
$$\max ({a \bmod b})=b-1$$

$$\therefore \max(\sum_ {i=1}^{n} i \bmod p_i)=\sum_ {i=1}^{n} (p_i-1)=0+1+...+(n-1)=\frac{(n-1)\times n} 2$$

输出 $\frac {n\times (n-1)} 2$ 即可。


## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    long long n;cin>>n;cout<<(n-1)*n/2<<'\n';
    return 0;
}
```


---

## 作者：diqiuyi (赞：0)

~~好久没发题解了。~~

[题目传送门](https://www.luogu.com.cn/problem/AT4873)

**思路**

$\because m_i \le p_i-1\therefore \sum_{i=1}^nm_i \le \sum_{i=1}^n(p_i-1)=\dfrac{n(n-1)}{2}$。

显然，令数组 $p_i=(i+1) \bmod (n+1)$，也就是说 $p_i=i+1,p_n=1$ 就可以得到上面的结果。

因此不难得到答案就是 $\dfrac{n(n-1)}{2}$。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//不开 long long 见祖宗
inline int read(int x=0,bool f=1){
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return f?x:-x;
}
int n; 
signed main(){
	n=read();
	printf("%lld\n",(n-1)*n>>1);
	return 0;
}
```

~~大水题。~~

---

## 作者：μηδσ (赞：0)

## Definition

对于整数我们选择$\{1,2,3,\cdots,N\}$的排列$\{P_1,P_2,P_3,\cdots P_N\}$。

然后对于每个$i=1,2,3,\cdots,N$,设$M_i$为$i$除以$P_i$时的语数求$M_1+M_2+M_3+\cdots+M_N$的最大可能值

## Solution

显然当$P_i=N$的时候$\sum_{i=1}^{n}M
_i$最大（~~可以证明，但是就不在这里赘述了~~

于是这个题就变成了等差数列求和公式，记得开$long\ long$

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

ll n, ans;		//记得开long long
 
int main(){
    cin >> n;			//输入n
    ans = n * (n - 1) / 2;	//等差数列求和
    cout << ans; 		//输出ans
    return 0;
}
~~~

---

