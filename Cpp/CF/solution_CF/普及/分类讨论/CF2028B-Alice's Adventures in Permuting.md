# Alice's Adventures in Permuting

## 题目描述

Alice 把 transmutation（转化）和 permutation（排列）这两个词搞混了！她有一个由三个整数 $n$、$b$、$c$ 指定的数组 $a$：数组 $a$ 的长度为 $n$，其中 $a_i = b \cdot (i - 1) + c$，$1 \leq i \leq n$。例如，如果 $n=3$，$b=2$，$c=1$，那么 $a=[2 \cdot 0 + 1, 2 \cdot 1 + 1, 2 \cdot 2 + 1] = [1, 3, 5]$。

现在，Alice 非常喜欢 $[0, \ldots, n-1]$ 的排列 $^{\text{∗}}$，她想把 $a$ 变成一个排列。每次操作中，Alice 会将 $a$ 中的最大元素替换为 $a$ 的 $\operatorname{MEX}$ $^{\text{†}}$。如果 $a$ 中有多个最大元素，Alice 会选择最左边的一个进行替换。

你能帮 Alice 计算她最少需要多少次操作才能第一次将 $a$ 变成一个排列吗？如果永远无法变成排列，请输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是由 $n$ 个互不相同的整数 $0$ 到 $n-1$ 组成的数组，顺序任意。请注意，这与通常的排列定义略有不同。例如，$[1,2,0,4,3]$ 是一个排列，但 $[0,1,1]$ 不是排列（$1$ 在数组中出现了两次），$[0,2,3]$ 也不是排列（$n=3$ 但数组中有 $3$）。

$^{\text{†}}$ 一个数组的 $\operatorname{MEX}$ 是不在该数组中的最小非负整数。例如，$[0, 3, 1, 3]$ 的 $\operatorname{MEX}$ 是 $2$，$[5]$ 的 $\operatorname{MEX}$ 是 $0$。

## 说明/提示

在第一个测试用例中，数组已经是 $[0, 1, \ldots, 9]$，所以不需要任何操作。

在第三个测试用例中，初始数组为 $[1, 3, 5, \ldots, 199]$。第一次操作后，$199$ 被替换成 $0$。第二次操作，$197$ 被替换成 $2$。如此继续下去，恰好需要 $50$ 次操作才能得到 $[0, 1, 2, 3, \ldots, 99]$。

在第四个测试用例中，需要两次操作：$[1,1,1] \to [0,1,1] \to [0,2,1]$。

在第五个测试用例中，过程为 $[0,0,0] \to [1,0,0] \to [2,0,0] \to [1,0,0] \to [2,0,0]$。这个过程会无限循环，因此数组永远无法变成排列，答案为 $-1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
10 1 0
1 2 3
100 2 1
3 0 1
3 0 0
1000000000000000000 0 0
1000000000000000000 1000000000000000000 1000000000000000000```

### 输出

```
0
1
50
2
-1
-1
1000000000000000000```

# 题解

## 作者：chenxi2009 (赞：2)

# 思路
简单数学题，不用二分。需要分类讨论，先说一般情况：
- $b>0$，答案为 $n-\max(0,\left\lceil\frac{n-c}{b}\right\rceil)$。\
显然这时答案是 $n-\sum_{i=1}^n[a_i<n]$，$a$ 中小于 $n$ 的数字个数就是 $a$ 中小于 $n$ 的最后一个数字的下标（1 下标），这是因为 $a$ 单调递增。\
所以解不等式 $b(x-1)+c<n$，得 $x<\frac{n+b-c}{b}$，向上取整后减一就可以得到最大的整数根 $x$。取大值是为了处理 $c>n$ 的情况。化简得上式。
- $b=0,c<n-2$，参考样例解释第五组，这种情况必然出现死循环，因为 $a$ 的最大值最终会在 $c+1$ 和 $c+2$ 之间反复跳动。
- $b=0,n-2\le c\le n-1$，在进入死循环之前可以完成目标，$a$ 中保留一个 $c$ 其他的数和保留的数构成排列，操作 $n-1$ 次；
- $b=0,c\ge n$，操作 $n$ 次。

综合上述讨论就可以得出结果了。复杂度 $O(t)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long n,b,c;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%lld%lld%lld",&n,&b,&c);
		if(b){
			printf("%lld\n",n - max(0ll,(n - c + b - 1) / b)); //向上取整 
		}
		else{
			printf("%lld\n",c >= n - 2 ? n - bool(c <= n - 1) : -1);//归纳了一下 b=0 的情况 
		}
	}
	return 0;
}
```

---

## 作者：Lee_OIer (赞：1)

CodeForces Round Div.2 $\color{#03A89E} 1400$ 数学题，不用二分，直接分类讨论——

- 对于 $c \ge n$，则有 $a_i \ge n$，每个数都需要取 $\operatorname{MEX}$，共计 $ n $ 次。
- 对于 $c < n$：
  - 若 $b \ne 0$，需要处理大于等于 $n$ 的，等价于找最大的数 $k$，使得 $b \times (k - 1) + c \le n$，移项可得 $\max k = \frac{n - c - 1}{b}$，则需操作 $n - \frac{n - c - 1}{b} - 1$ 次（由于精度问题需 $-1$)。
  - 否则需要操作 $n - 1$ 次（注意：$n - c \ge 3$ 时无解，这种情况 $\max a_i$ 会在 $c + 1$ 和 $c + 2$ 之间反复跳动陷入死循环）。

（警钟敲烂——**十年 OI 一场空，不开 `long long` 见祖宗**）

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, n, b, c;
signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> b >> c;
		if (c >= n) cout << n << '\n';
		else {
			if (b) cout << n - (n - c - 1) / b - 1 << '\n';
			else {
				if (n - c >= 3) cout << -1 << '\n';
				else cout << n - 1 << '\n';
			}
		}
	}
}
```

---

## 作者：wuyouawa (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF2028B)

### 思路

典型分类讨论题。

我们按以下几点分类讨论：

- $c \ge n$，那么 $a_i \ge n$，需要每个取 $\operatorname{MEX}$，$n$ 次。

- 否则：

  - 如果 $b=0$，那么有 $n$ 个 $c$，打个表发现当 $n-3 \ge c$ 时无解，否则解为 $n-1$。
 
  - 如果 $b > 0$，那么小于 $n$ 的不用管，大于等于 $n$ 的要用 $\operatorname{MEX}$ 干掉，所以等价于让我们找一个最大的 $x$，使得 $c+b \times (x-1) \le n$。我们用乘法分配律把 $b$ 和 $c$ 移过去，得 $x=\frac{n-c-1}{b} \le n$，由于精度问题我们要 $-1$。
 
### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,b,c,l,r,mid;//不开long long见祖宗
int main(){
    cin>>t;
    while(t--)
    {
        cin>>n>>b>>c;
        if(c>=n)  cout<<n;//因为所有ai都大于n所以做n次操作
        else
        {
            if(b==0)  
            {
                if(n-3>=c)  cout<<-1;//无解
                else  cout<<n-1;//规律是n-1
            }
            else
            {
                cout<<n-(n-c-1)/b-1;//注意精度
            }
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：sjh0626 (赞：0)

## 思路分析
比较好的一道分类讨论和等差数列题，首先我们要对 $c$ 分类讨论：
- $c \ge n$，则 $a_i$ 同时也 $\ge n$，所以需要 $n$ 次。
- 反之：
  + $b = 0$ 时，那么 $a_i = c$，继续分类讨论。
     * 在 $n - c < 3$ 时，因为 $a_i$ 一定会有一个符合条件。所以需要 $n-1$ 次。
       
     * 反之，我们会一直改变最大的 $a_i$，无解。
  + 反之，我们可以知道 $a$ 是一个等差数列。
    
    则我们要找到一个最大的 $x$ 使得 $a_x < n$，则我们可以列出下面这个不等式：
    
    $$
    \begin{aligned}
      c+b\times(x-1) &< n \\
      \frac{c}{b}+x-1 &< \frac{n}{b}
    \end{aligned}
    $$

    则最大的 $x$ 为 $\displaystyle\frac{n-c-1}{b}-1$。

分类讨论结束，可以开始打代码了。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t;
ll n,b,c;
int main(){
	t=read();
	while(t--){
		n=read(),b=read(),c=read();
		if(c>=n)cout<<n<<"\n";
		else{
			if(b==0){
				if(n-c>=3)cout<<"-1\n";
				else cout<<n-1<<"\n";
			}
			else cout<<n-(n-c-1)/b-1<<"\n";
		} 
	}
	sjh0626s code;
}
```

---

## 作者：Drifty (赞：0)

### Solution

一道数学题。我们做下分讨：

- 若 $c \ge n$，那么 $a_i\ge n$，因此至少要做 $n$ 次操作。
- 如果 $b\neq 0$，我们只需要操作使得 $a_i\ge n$ 的 $a_i$，我们发现这样等价于找一个最大的 $k$，使得 $b\times (k - 1) + c\le n$，答案即为 $n - k$。移项得 $k = \frac{(n - c - 1)}{b} + 1$，代入即得。
- 如果 $b = 0$，那么：
  - $n-3\ge c$ 时，无解，因为最后会剩很多 $a_i=c$ 然而将其中的一个操作一次后变成 $a_i=c + 1 < n-1$，就不可能了；
  - 否则答案为 $n - 1$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int T; cin >> T;
    for (i64 n, b, c; T --; ) {
        cin >> n >> b >> c;
        i64 ans = -1;
        if (c >= n) ans = n;
        else if (b) ans = n - (n - c - 1) / b - 1;
        else if (n >= c + 3) ans = -1;
        else ans = n - 1;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：MrPython (赞：0)

怎么搞的，为什么好多大佬都在这里爆炸了？

对于 $b>0$，其最终效果一定是将所有不小于 $n$ 的数变成在 $0$ 到 $n-1$ 中没有出现的数。应用~~乌姆·尼克算法~~二分找到有多少个数小于 $n$，剩下的数都要操作各一遍。

$b=0$ 需要稍微处理一下：
- $c\ge n$ 时，初始数组内的所有数都大于等于 $n$，需要各操作一遍，共 $n$ 次。
- $c= n-1$ 时，第 $0$ 到 $n-2$ 个数分别修改为 $0$ 到 $n-2$，第 $n-1$ 项本身为 $n-1$ 无需修改，共 $n-1$ 次；
- $c= n-2$ 时，第 $0$ 到 $n-3$ 个数分别修改为 $0$ 到 $n-3$，第 $n-2$ 项被修改为 $n-1$，第 $n-1$ 项已经为 $n-2$ 不变，共 $n-1$ 次；
- $c< n-2$ 时，我们会一直重复操作那个最大的元素，永远无法到达答案，无解。

```cpp
#include <algorithm>
#include <iostream>
#include <ranges>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
using ulli = __uint128_t;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    uli n, b, c;
    fin >> n >> b >> c;
    if (b == 0) {
      if (c + 2 < n)
        fout << "-1\n";
      else
        fout << (c == n - 2 ? n - 1 : c == n - 1 ? n - 1 : n) << '\n';
      continue;
    }
    auto view =
        ranges::views::iota(0ull, n) |
        ranges::views::transform([b, c](uli x) { return (ulli)b * x + c; });
    fout << (n - uli(ranges::lower_bound(view, n) - view.begin())) << '\n';
  }
  return 0;
}
```

---

