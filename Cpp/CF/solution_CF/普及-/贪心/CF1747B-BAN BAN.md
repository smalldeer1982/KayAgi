# BAN BAN

## 题目描述

You are given an integer $ n $ .

Let's define $ s(n) $ as the string "BAN" concatenated $ n $ times. For example, $ s(1) $ = "BAN", $ s(3) $ = "BANBANBAN". Note that the length of the string $ s(n) $ is equal to $ 3n $ .

Consider $ s(n) $ . You can perform the following operation on $ s(n) $ any number of times (possibly zero):

- Select any two distinct indices $ i $ and $ j $ $ (1 \leq i, j \leq 3n, i \ne j) $ .
- Then, swap $ s(n)_i $ and $ s(n)_j $ .

You want the string "BAN" to not appear in $ s(n) $ as a subsequence. What's the smallest number of operations you have to do to achieve this? Also, find one such shortest sequence of operations.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In the first testcase, $ s(1) =  $ "BAN", we can swap $ s(1)_1 $ and $ s(1)_2 $ , converting $ s(1) $ to "ABN", which does not contain "BAN" as a subsequence.

In the second testcase, $ s(2) =  $ "BANBAN", we can swap $ s(2)_2 $ and $ s(2)_6 $ , converting $ s(2) $ to "BNNBAA", which does not contain "BAN" as a subsequence.

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
1
1 2
1
2 6```

# 题解

## 作者：CR7_houyetong (赞：11)

# 题意
- 给定一个 $n$，表示字符串有 $n$ 个```BAN```。
- 你可以任意交换两个字母的位置，例如可以把```BAN```交换成```ABN```。
- 求交换最小次数满足```BAN```不是新字符串的字串，并求出交换方案。
- 最后，$n≤100$。

# 分析
此题看上去挺像模拟的，事实上只是一道简单的数学，看“普及-”的标签就知道了，什么```BAN```来```BAN```去的，那都是迷惑你的。

我们要满足```BAN```不是新字符串的字串，就要尽可能地用较少的交换次数去消除尽可能多的```BAN```。

我们发现，把两个```BAN```，即```BANBAN```的第一个```A```和第二个```N```交换，就可以消除两个```BAN```，于是这就引出了了我们固定下来的所有数据都适合的交换方案：

1. 第 $1$ 个```BAN```的```A```和第 $n$ 个```BAN```的```N```交换。
1. 第 $2$ 个```BAN```的```A```和第 $n-1$ 个```BAN```的```N```交换。

......

最后我们发现，第 $i$ 个```BAN```与第 $n-i$ 个```BAN```交换，所以交换次数就是 $\lceil \frac n 2 \rceil$。


Q：为什么要交换```A```和```N```呢？

A：因为如果是奇数个```BAN```的话，最中间一个消除的时候不能交换同一个位置，不然就等于没交换，所以选择```A```和```N```。
# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n,i;
signed main(){
    cin>>T;
    while (T--){
        cin>>n;
        cout<<(n+1)/2<<endl;
        for (i=1;i<=(n+1)/2;i++)
          cout<<3*i-1<<" "<<(n-i+1)*3;
    }
    return 0;
}
```


---

## 作者：ImNot6Dora (赞：1)

这个题是一道经典的数学题，本来读题以为是模拟，结果没想到他是有规律的。

由于这个题要求是不让出现 BAN 这个**子序列**，所以我们必须把所有的字母 B 放在最后，把所有的 $N$ 放在前面，也就是说，将对应($i\times 3-2$ 位置上的 B 和 $(n-i+1)\times 3$ 位置上的 N )的两个 BAN 的首尾两字母 B 和 N 交换位置，推算可知交换次数为 $\lceil \dfrac{n}{2} \rceil$，这个向上取整的空间是留给 $n$ 为**奇数**的情况，在这种情况下，最中间的 BAN 还要操作一次，变成 NAB。

时间复杂度仅为 $\mathcal O(t\times n)$。

### C++ CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		cout<<ceil(n/2.0)<<endl;
		for(int i=1;i<=ceil(n/2.0);i++){
			cout<<i*3-2<<' '<<(n-i+1)*3<<endl;
		}
	}
   return 0;
}
```

By ImNot6Dora

---

## 作者：HNOIRPplusplus (赞：1)

## 题意
+ 你有一个由 $n$ 个 `BAN` 连起来组成的字符串，形如 `BANBAN...BAN`。
+ 你每次可以交换两个字母的位置。
+ 求最少多少次交换以后 `BAN` 不是字符串的子串。

## 做法
### 方案
本题中所要求的不以 `BAN` 为子串，实际上可以转化为没有一个 `A`，它左边有一个 `B` 的同时右边有一个 `N`。  
那么我们可以把所有的 `A` 都给它放到 `B` 的左边，即从右到左把每个 `A` 和从左到右的 `B` 交换。  
可以注意到每个 `A` 之间和每个 `B` 之间的距离都是相等的。
### 步数
因为每次交换可以将右边的一个 `A` 移到左边来（于是这个 `A` 左边没有 `B` 了），同时可以把左边的一个 `B` 移到右边去（于是这个 `B` 本来右边的那个 `A` 左边也没有 `B` 了），一共有 $n$ 个 `A`，一步可以处理 $2$ 个，所以最终步数为 $\lceil\frac n2\rceil$。[](https://www.luogu.com.cn/paste/z0ysj530)
## 代码
```cpp
#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    cout << (n + 1) / 2 << '\n';
    for(int i = 1, j = 3 * n - 1; i < j; i += 3, j -= 3) {
      cout << i << ' ' << j << '\n';
    }
  }
  return 0;
}
```
[AC 0ms 4.00KB](https://www.luogu.com.cn/record/94512733)

---

## 作者：luogu_gza (赞：1)

题意：

给定一个字符串 $s(n)$ ， $s(n)$ 定义为 $n$ 个 `BAN` 字符串拼接在一起。

如 $s(3)$ 为 `BANBANBAN` 。

一次操作定义为将任意两个字符交换。

请问最少几次操作就可以令字符串中不含为 `BAN` 的连续子串。

要求输出交换方案。

多测。

----

我用代码框给大家解释一下这个做法

首先，我们来看 `BANBAN` 这个字符串
                  
第一个N和第二个N交换即可。

可以发现，一次交换可以“摧毁”两个 `BAN` 

所以，交换次数就是 $\lceil \frac{n}{2} \rceil$ (奇数的情况需要再来一次)
具体方案就是

1. 交换第 $1$ 个 `BAN` 的 `A` 和第 $n$ 个 `BAN` 的 `N`

2. 交换第 $2$ 个 `BAN` 的 `A` 和第 $n-1$ 个 `BAN` 的 `N`

$\cdots$

第 $i$ 次：交换第 $i$ 个 `BAN` 的 `A` 和第 $n-i+1$ 个 `BAN` 的 `N`

$\cdots$

再来思考一个问题：

$\texttt{Q:}$ 为什么要是 `A` 和 `N` 呢？不能是 `A` 和 `A` 呢？

$\texttt{A:}$因为如果是奇数个 `BAN` 的话，最中间一个“摧毁”的时候你不能交换同一个位置，那样就达不到“摧毁”的效果了，所以选择 `A` 和 `N` 。


---

$\texttt{Talk is cheap,I'll show you the code!}$

```
#include<bits/stdc++.h>
using namespace std;
#define R read()
#define int long long
#define inf 0x3f3f3f3f
#define mod1 1000000007
#define mod2 998244353
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define rep(i,a,b) for(int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
#define m2(a,b) memcpy(a,b,sizeof b)
namespace IO{
    inline int read()
    {
        int X=0; bool flag=1; char ch=getchar();
        while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
        while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
        if(flag) return X;
        return ~(X-1);
    }
    inline void write(int X)
    {
        if(X<0) {X=~(X-1); putchar('-');}
        if(X>9) write(X/10);
        putchar(X%10+'0');
    }
}
using namespace IO;
int t,n;
signed main(){
    t=R;
    while(t--)
    {
        n=R;
        write(n+1>>1),puts("");
        for(int i=1;i<=n+1>>1;i++) write((3*i-1),putchar(' '),write((n-i+1)*3),puts("");
    }
}
```

---

## 作者：BEST_CAT (赞：0)

# CF1747B BAN BAN 题解
## 题目简述
- 给定 $n$，表示字符串有 $n$ 个 `BAN`。
- 你可以任意交换两个字母的位置。
- 求交换最小次数满足 `BAN` 不是新字符串的字串，并求出交换方案。

数据范围：$n\le 100$。

## 思路
我们要尽可能地少用交换次数去消除尽可能多的 `BAN`。

### 具体交换方案

将前一个 `BAN` 的 `A` 与后一个 `BAN` 的 `N` 交换，就可以交换一次，消除两个 `BAN`。

1. 第 $1$ 个 `BAN` 的 `A` 和第 $n$ 个 `BAN` 的 `N` 交换，位置分别为 $3\times 1-1$ 和 $n\times 3$。
2. 第 $2$ 个 `BAN` 的 `A` 和第 $n-1$ 个 `BAN` 的 `N` 交换，位置分别为 $3\times 2-1$ 和 $3\times (n-2+1)$。
3. 第 $3$ 个 `BAN` 的 `A` 和第 $n-2$ 个 `BAN` 的 `N` 交换，位置分别为 $3\times 3-1$ 和 $3\times (n-3+1)$。

$\;$以此类推……

#### 求操作次数
最少操作总数就为 $\lceil \frac{n}{2} \rceil$，要用到 `cmath` 库中的 `ceil()` 函数。

#### 求交换位置
不难发现第 $i$ 此操作交换的是第 $3\times i-1$ 个和第 $3\times (n-i+1)$ 个。

## 代码
```cpp
#include <iostream>
#include <cmath>//cmath 库
using namespace std;
typedef long long ull;
double t,n;//ceil 必须是double
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        int l=ceil(n/2);//记录一下操作次数
        cout<<l<<endl;
        for(int i=1;i<=l;i++){//用for跑一遍
            cout<<3*i-1<<" "<<3*(n-i+1)<<endl;//输出交换位置
        }
    }
    return 0;
}

```


---

## 作者：lwx20211103 (赞：0)

## 题目意思

给出数字 $n$，形成字符串 $n$ 个由“BAN"组成的字符串头尾相连接的字符串，每次操作交换两个字符，求几次操作可以使这个字符串没有含“BAN”的连续子串。输出次数和两个字符的位置。

## 思路

[题目链接](https://www.luogu.com.cn/problem/CF1747B)。

可以看作简单的贪心。因为 BAN 三个字符互不相同，所以换掉一个“A”和 “N”就可以使这个字符串没有含“BAN”的连续子串。

所以，只要 $\frac{n + 1}{2}$ 种方案即可，向下取整。

对于每个被替换字符“A”和“N”的位置分别是 $3i - 1$ 和 $3(n - i + 1)$，$1 \leq i \leq \frac{n + 1}{2}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xhjgw40q.png)

这样，我们的程序就出来了。

```cpp
void solve(int n)
{
    cout << (n + 1 >> 1) << "\n";//位运算，相当于 (n + 1) / 2
    for (int i = 1; i <= (n + 1 >> 1); i++)
    {
        cout << 3 * i - 1 << " " << (n - i + 1) * 3 << "\n";
    }
}
```


---

## 作者：Lyccrius (赞：0)

没有字符串 `BAN` 的子序列也意味着原始字符串中没有 `BAN` 的子串。令没有 `BAN` 的子串的最小操作数为 $x$，这也是没有串 `BAN` 的子串的下界。

声明：$x = \lceil \frac{n}{2} \rceil$。

证明：将 $i$-th `B` 从开始与 $i$-th `N` 交换为 $1 \le i \le \lceil \frac{n}{2} \rceil$。我们可以看到，在执行 $\lceil \frac{n}{2} \rceil$ 操作后，不存在 `BAN` 的子串。 由于我们在一次操作中最多只能销毁 2 个子字符串，因此 $\lceil \frac{n}{2} \rceil$ 是最小的可能。

现在如果你看清楚了，在执行了上述操作之后，原始字符串中不存在字符串 `BAN` 的任何子序列。 因此 $\lceil \frac{n}{2} \rceil$ 也是原始问题的答案。

```
#include <cstdio>
#include <cmath>

int m;
int n;

int main() {
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &n);
        int ans = std::ceil((double)n / 2);
        printf("%d\n", ans);
        for (int l = 1, r = n * 3; l < r; l += 3, r -= 3) printf("%d %d\n", l, r);
    }
    return 0;
}
```

---

## 作者：sunzz3183 (赞：0)

# CF1747B-BAN BAN 题解

## 题意

给定一个 $N$，生成一个长度为 $N\times3$ 的字符串，形式为“$\texttt {BANBAN...BAN}$”，现在，找到一种替换方式，使得字符串中不会出现子序列“$\texttt {BAN}$”，输出替换次数和方案。

## 思路

因为不能出现子序列“$\texttt {BAN}$”，所以我们可以把前面所有的 “A” 移动到 “N” 后面，这样就不会出现“$\texttt {BAN}$”了。

移动方案：将所有**前后**对应的 “A” 和 “N” 替换位置。

则替换次数为 $\lceil n/2 \rceil$。

证明：显然每次交换最优方案就是每次操作，把两个子串破坏掉，并且不会出现新的子串。

而将第 $i$ 个“A”与第 $n-i$ 个“N”替换后，由于前面没有“A”自然不会出现“$\texttt {BAN}$”，而后面没有“N”，也不会出现“$\texttt {BAN}$”了。就实现了最优操作。

而上取整就是为了特判中间的“$\texttt {BAN}$”，使它变为“$\texttt {BNA}$”。



## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
string du(){
	string s;char c=getchar();
	while(c!=' '&&c!='\n'){s+=c;c=getchar();}
	return s;
}
int T,n;
signed main(){
	T=read();
	while(T--){
		n=read();
		int y=(n+1)/2;
		printf("%lld\n",y);
		for(int i=2,j=n*3,k=1;k<=y;i+=3,j-=3,k++)//寻找每个“A”和“N”的下表
			printf("%lld %lld\n",i,j);
	}
	return 0;
}
```


---

