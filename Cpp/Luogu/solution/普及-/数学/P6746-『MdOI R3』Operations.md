# 『MdOI R3』Operations

## 题目背景

这是这场比赛唯一一道没有题目背景的题，这就是本题的题目背景。

## 题目描述

给定非负整数 $a,b$，有两种操作：

1. 任意选择一个正整数 $x$，将两数都减去 $x$，执行一次该操作的代价为 $c$；
2. 任意选择一个正整数 $x$，将两数其中一个数乘以 $x$，另一个除以 $x$ 后向下取整，执行一次该操作的代价为 $d$。

在这里，向下取整指使一个数变为**不大于它的最大的整数**，比如 $3.5$ 向下取整为 $3$，$-0.07$ 向下取整为 $-1$。

选择的 $x$ 可以为任意正整数。在操作的过程中，可以把 $a,b$ 变为负数。

你可以任意多次对这两个数操作，求将 $a,b$ 都变成 $0$ 的代价最小值。

## 说明/提示

【样例解释】

先使用一次 $2$ 操作，选择 $x=2$，将 $a$ 乘 $2$，将 $b$ 除以 $2$，得 $a=18,b=18$。  
再使用一次 $1$ 操作，选择 $x=18$，将两个数都减去 $18$，得 $a=0,b=0$。  
可以证明没有比上述操作代价更小的方案。

更多样例请[到这里](https://www.luogu.com.cn/paste/fnvd95y2)领取。

【数据范围】  

**本题采用捆绑测试**，换言之，你只有通过一个子任务的所有测试点，才可以拿到该子任务对应分数。
| 子任务编号 | $a=0$ | $b=0$ | $a=b$ | $c=1,d\geq 10^5$ | $c \geq 10^5,d=1$ | 分值 |
| :--------: | :------: | :------: | :--------: | :----------------: | :----------------: | :--: |
|     $1$      |    $\surd$     |    $\surd$     |            |                    |                    |  10  |
|     $2$      |    $\surd$     |          |            |                    |                    |  10  |
|     $3$      |          |          |     $\surd$      |         $\surd$          |                    |  10  |
|     $4$      |          |          |          | $\surd$ |                  |  10  |
|     $5$      |          |          | $\surd$ |                  | $\surd$ |  10  |
|     $6$      |          |          |            |                    |         $\surd$   |  10  |
|     $7$      |          |          |            |                    |                    |  40  |

特殊性质如上所示，其中，$\surd$ 表示保证有该特殊性质，空格表示不保证有该性质。

对于所有数据，$0\leq a,b,c,d \leq 10^9$。

## 样例 #1

### 输入

```
9 36 1 3```

### 输出

```
4
```

# 题解

## 作者：chen_zhe (赞：29)

# 『MdOI R3』Operations

对着数据范围做题。

首先，当 $a=0$ 且 $b=0$ 时，显然是不用代价的，即代价为 $0$。

当 $a=0$ 时，显然可以用一次 $2$ 操作，使得 $a$ 乘上一个很大的数字，$b$ 除以一个很大的数字，这样 $a$ 还是 $0$，$b$ 因为有下取整操作因此也会变成 $0$。当 $b=0$ 时同理可做。代价是 $d$。

当 $a=b$ 时，显然可以用一次 $1$ 操作，使得两数都减去 $a$，这样两个数字都变成 $0$ 了，代价是 $c$。还有一个方法是让 $a$ 乘上一个很大的数字，$b$ 除以一个很大的数字，使得其变为 $a\neq 0$，$b=0$ 的形式，使用上面的方法即可处理，代价是 $2 \times d$，取最小值即可。

当 $a \neq b$ 时，其实可以用一次 $1$ 操作，使得 $a$ 变为 $0$，然后再用 $a=0$，$b \neq 0$ 的方法去做（若 $a>b$，则让 $b$ 变成 $0$），代价是 $c+d$。还有一个方法是让 $a$ 乘上一个很大的数字，$b$ 除以一个很大的数字，使得其变为 $a\neq 0$，$b=0$ 的形式，使用上面的方法即可处理，代价是 $2 \times d$，取最小值即可。

然后结合这些分析即可 AC 本题。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
	int a=read(),b=read(),c=read(),d=read();
	if (a==0 && b==0)
		puts("0");
	else if (a*b==0)
		cout << d << endl;
	else if (a==b)
		cout << min(c,2*d) << endl;
	else
		cout << min(c+d,2*d) << endl;
	return 0;
}
```


---

## 作者：仗剑_天涯 (赞：7)

这道题的数都是 $1e9$，复杂度一般是 $O(1)$ 的，也就是说，这是一道数学题。

首先，想让一个数变成 $0$，可以将其乘以 $0$。但是，在这同时，一个数也要除以 $0$。在数学课上，一个数除以 $0$ 是没有意义的，所以这道题里一个数除以 $0$ 是被禁止的。那怎么办呢？ 我们可以除法结果利用向下取整的特性，将一个数除以一个极其大的数，也可让一个数变成 $0$。  
于是，我们可以开始写思路了。

不考虑任何特殊情况，最基本的答案是：$min(c+d,d+d)$。  
$c+d$ 的操作是：先将一个数减到 $0$，再将另一个数除以一个极其大的数。  
$d+d$ 的操作是：先将一个数除以一个极其大的数，再将另一个数除以一个极其大的数。

然后是特判。  
1.$a==0$ 且 $b==0$ 时，已经满足了要求，答案是 $0$。  
2.$a==0$ 或 $b==0$ 时，已经有一个数是 $0$了，再将另一个数除以一个极其大的数即可，答案是 $d$。  
3.$a==b$ 时，直接全部减到 $0$ 即可（注意它不一定比 $d+d$ 优），答案是 $min(c,d+d)$。

最后，就AC了！

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main()
{
	cin>>a>>b>>c>>d;
	if(a==0&&b==0)//特判1
	{
		cout<<0;
		return 0;
	}
	if(a==0||b==0)//特判2
	{
		cout<<d;
		return 0;
	}
	if(a==b)//特判3
	{
		cout<<min(c,d+d);
		return 0;
	}
	cout<<min(c+d,d+d);//最基本的答案
	return 0;
}
```

---

## 作者：Rubidium_Chloride (赞：5)

2020.8月月赛B题题解。

## 0.前言

[$\color{Red}{See\ }\color{green}{in\ }\color{blue}{the\ }\color{pink}{blog}$](https://www.luogu.com.cn/blog/Rolling-blog1424/solution-p6746)

那么，让我们开始吧！

## 1.题目大意

有 $2$ 个数 $a,b$，有两种操作：

- 第一种，花费 $c$ 的价值，选定一个正整数 $x$ ，将 $a,b$ 变成 $a-x,b-x$ ；

- 第二种，花费 $d$ 的价值，选定一个正整数 $x$ ，将 $a,b$ 变成 $a\times x,\left[\dfrac{b}{x}\right]$ 或者 $\left[\dfrac{b}{x}\right],a\times x$，其中 $\left[k\right]$ 表示 $k$ 向下取整。

现在要让两个数全部变成 $0$，求最小花费价值。

## 2.基本分析

为了方便，本文以下用 $\left(a,b\right)$ 表示 $a,b$ 两个数。

首先让我们来看几种特殊情况。

$1.a=b=0$：此时不用花费任何价值，输出 $0$。

$2.a=0,b\neq 0$：此时发现不可以只用 $1$ 操作，但是可以用一次 $2$ 操作，选择 $x=b+1$，将 $\left(0,b\right)$ 转换成 $\left(0\times(b+1),\left[\dfrac{b}{b+1}\right]\right)$，也就是 $\left(0,0\right)$。总共花费 $d$。

$3.a\neq 0,b=0$：这种情况尽管数据中没有提到，但是如果不考虑这种情况，会让你从 $100pts\to 40pts$。

同理第 $2$ 种情况，用一次 $2$ 操作，选择 $x=a+1$，将 $\left(a,0\right)$ 转换成 $\left(\left[\dfrac{a}{a+1}\right],0\times(a+1)\right)$，就是$\left(0,0\right)$。总共花费 $d$。

接下来我们先停一停我的讨论的脚步，来证明一个结论：对于任意的 $\left(a,b\right)$，用 $2$ 次操作一定能够变成 $\left(0,0\right)$。

介绍两种方法。

$$(a,b)$$

进行一次 $2$ 操作，选择 $x=a+1$；

$$\to \left(\left[\dfrac{a}{a+1}\right],b\times(a+1)\right)\to(0,b\times(a+1))$$

再进行一次 $2$ 操作，选择 $x=b\times(a+1)+1$；

$\to \left(0\times \left(b\times(a+1)+1\right),\left[\dfrac{b\times(a+1)}{b\times(a+1)+1}\right]\right)\to (0,0)$，总花费 $2\times d$。

或者（不妨假设 $a<b$）：

$$(a,b)$$

进行一次 $1$ 操作，选择 $x=a$；

$$\to \left(a-a,b-a\right)\to(0,b-a)$$

进行一次 $2$ 操作，选择 $x=b-a+1$；

$\to \left(0\times \left(b-a+1\right),\left[\dfrac{b-a}{b-a+1}\right]\right)\to (0,0)$，总花费 $c+d$。

让我们再来看一种特殊情况。

$4.a=b\neq 0$：此时可以执行 $1$ 次 $1$ 操作，也可以执行如上的 $2$ 次 $2$ 操作。所以答案就是 $\min(c,2\times d)$。

如果 $\left(a,b\right)$ 不满足如上的任何一种特殊情况，可知是不能只通过 $1$ 操作来完成的，也不可能只通过 $2$ 操作。所以答案就是上面两种的最小值，也就是 $\min(c+d,2\times d)$。

## 3.Code

贴上代码：
```cpp
#include<bits/stdc++.h>
#define N 
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
inline ll read() {
    ll x=0,f=1;int c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
ll a,b,c,d;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	a=read(),b=read(),c=read(),d=read();
	if(a==0&&b==0){printf("0");return 0;} 
	if(a==0){printf("%lld",d);return 0;}
	if(b==0){printf("%lld",d);return 0;}
	if(a==b) printf("%lld",min(c,2*d));
	else printf("%lld",min(c,d)+d);
	return 0;
}
```
## 4.后记

这就到了这篇题解的结尾了。

希望以后月赛能够越办越好！

---

## 作者：Unordered_OIer (赞：4)

# P6746 题解
## 题意
对数值 $a,b$ 进行两种操作。
1. 各减去一个数值
2. 选定一个数，选一个数乘以这个数，另一个数除以这个数并下取整


## 解答
一开始我还想用搜索来解决这道题，但是写着写着写挂了，于是我开始了分类讨论。

真的要谢谢 $\text{Subtask}$ 制作者，否则我还真的讨论不全。

首先，我们一定可以证明最小花费一定不会超过 $c+d$ ，因为可以先把一个数减至 $0$ ，然后进行乘除的操作。

并且，由于**下取整**的特性，一旦出现负数就凉了。

我们来分 $\text{Subtask}$ 看看吧
1. $a=0\ \&\ b=0$  
很好看出一定输出 $0$ 。
2. $a=0\ or\ b=0$  
这时我们只能进行 $2$ 号操作，因为一个 $=0$ 的数无论如何乘除结果都是 $0$ ，利用此特性与 $2$ 操作是除法 $+$ **下取整**，因此我们只要取一个大于 $\max(a,b)$ 的数，并用这个数对 $a,b$ 进行乘除操作即可。
3. $a=b$  
一种方法就是进行 $1$ 操作，然后操作的数取 $a$ ，即可全部归 $0$ 。  
但是不要忘记，还有一种办法，就是**做两次** $2$ 操作。具体方法就是先使较小的那个数变成 $0$ ，然后再进行一次第二种分类讨论（即 $a=0\ or\ b=0$ ），代价为 $2d$ 。  
两种情况取 $\min$ 即可。
4. $\text{else}$  
其他情况也是一样，首先 $c+d$ 保底。其次就是也是先把一个数用 $2$ 操作清零，再用 $2$ 操作把另一个也清零，代价为 $2d$ 。  
两种情况取 $\min$ 即可。

然后我们就可以快乐地写代码啦~

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,c,d;
int main(){
	cin>>a>>b>>c>>d;
	if(a==0&&b==0)return puts("0"),0;
	else if(a==0||b==0)return cout<<d<<endl,0;
	else if(a==b)return cout<<min(c,2*d)<<endl,0;
	else return cout<<min(2*d,c+d)<<endl,0;
	return 0;
}
```
## 总结
这道题构思很巧妙，并且 $\text{Subtask}$ 很好地启发了思路。算是一道不错的题目。

最后，祝洛谷月赛
# 越办越好
完结撒花~顺便求赞

---

## 作者：一只书虫仔 (赞：2)

[$\sf \color{Red}Best\ \color{Orange}Watch\ \color{Gold}In\ \color{LimeGreen}The\ \color{CornflowerBlue}Blog$](https://www.luogu.com.cn/blog/Shuchong/post-8-yue-yue-sai-i-b-ti-xie)

#### Description

> 给定 $a$ 和 $b$，并给定两种操作：
> - 将两数都减去一个特定的数，代价为 $c$
> - 将两数的其中一个数乘上一个特定的数，另一个数出去这个特定的数并取下取整，代价为 $d$     

> 求将两数均变为 $0$ 的最小代价。

#### Solution For Subtask 1：$a=b=0$

当 $a$ 和 $b$ 都等于 $0$ 的时候，我们发现不需要进行操作即可都变为 $0$，输出 $0$。

Part Code：

```cpp
if (a == 0 && b == 0) printf("0");
```

#### Solution For Subtask 2：$a=0$（或者理解为 $a$ 或 $b$ 其中一个数为 $0$）

当 $a$ 或 $b$ 其中一个数为 $0$ 的时候，我们可以使用第二个操作，输出 $d$。

Part Code：

```cpp
if (a == 0 || b == 0) printf("%d", d);
```

#### Solution For Subtask 3：$a=b$

当 $a=b$ 的时候，我们可以有两种处理方式：

1. 使用操作一，均减去一个数，输出 $c$
2. 使用两次操作二（输出 $2d$）：

- 第一次让一个数除以一个比他大的数，下取整为 $0$
- 第二次让另一个不为 $0$ 的数除以一个比他大的数，两个数均为 $0$

最后输出 $\min\{c,2d\}$ 即可。

Part Code：

```
if (a == b) printf("%d", min(c, 2 * d));
```

#### Solution For All Test Points

其实上面列举的三种情况是程序要特判的，也就是说，现在我们的程序框架是

```cpp
if (a == 0 && b == 0) printf("0");
else if (a == 0 || b == 0) printf("%d", d);
else if (a == b) printf("%d", min(c, 2 * d));
else 
```

就差最后一种普通情况了。

普通情况我们其实也有两种处理方式：

1. 先使用操作一，让一个数变为 $0$，然后就用 Subtask 2 的思路，输出 $c+d$
2. 见 Subtask 3 第二个处理方式，输出 $2d$

最后输出 $\min\{c+d,2d\}$ 即可。

然后我们就可以得到完整代码力。

#### Code

```cpp
#include <bits/stdc++.h>

想抄代码？想桃子呢？using namespace std;

int main () {
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	if (a == 0 && b == 0) printf("0");
	else if (a == 0 || b == 0) printf("%d", d);
	else if (a == b) printf("%d", min(c, 2 * d));
	else printf("%d", min(c + d, 2 * d)); 想抄袭的，棕名欢迎你
	return 0;
}
```

By Shuchong       
2020.8.8

---

## 作者：infinities (赞：1)

拿到题不妨先设 $a\le b$。

根据数据范围分多种情况讨论：

1. $a=0,b=0$。

这时代价为 0。

2. $a=0$。

这时进行一次 2 操作，除以一个极大数，这样保证 $b$ 下取整之后归零。

3. $a=b$。

此时有两种方式归零，一种是进行一操作，直接同减去 $a$，另一种是进行两次二操作，分别除以极大数，两种方式取最小值即可。

4. 上述皆不满足。

此时也有两种方式，一种是一次一操作一次二操作，先同减去 $a$，然后再让剩下的数除以一个极大数，一种是两次二操作，操作方式同上。取最小值即可。

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rint regester int
const int maxn = 1e6 + 10;
const int INF = 1e9;
using std::ios;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::unique;
using std::lower_bound;
using std::swap;
using std::abs;
using std::acos;
using std::queue;
using std::map;
using std::string;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int a, b, c, d;
signed main(){
	cin >> a >> b >> c >> d;
	if(a > b)swap(a, b);
	if(a == 0 && b == 0)cout << 0;
	else
	if(a == 0)cout << d;
	else
	if(a == b)cout << min(c, 2 * d);
	else
	cout << min(2 * d, c + d);
}

```

---

## 作者：囧仙 (赞：1)

## 题目大意

有两个非负整数 $a,b$ 。现有两种操作。

- $a\gets a-x,b\gets b-x$ ，其中 $x$ 为正整数。此操作花费非负整数 $c$ 。

- $a\gets a\times x,b\gets \left\lfloor\dfrac{b}{x}\right\rfloor$ ，或者 $b\gets b\times x,a\gets \left\lfloor\dfrac{a}{x}\right\rfloor$ ， 其中 $x$ 为正整数。此操作花费非负整数 $d$ 。

询问将 $a,b$ 都变成 $0$ 所花费的最大权值。

## 题解

一道挺有意思的分类讨论题。

- 当 $a=b=0$ 时，显然答案为 $0$ 。

- 当其中一个为 $0$ 时，我们可以执行操作 $2$ ， $x$ 取一个很大的值。此时另外一个非零的元素就能通过除法变成 $0$ 。

- 当两者都不为 $0$ 时，又存在三种情况。  
  - 当 $a=b$ 时 ，我们可以仅使用一次操作 $1$ 。  
  - 使用操作 $1$ 将更小的那个数减到 $0$ 。另外一个数就可以使用一次操作 $2$ 变成 $0$ 。
  - 使用两次操作 $2$ 。先将某个数除成 $0$ ，再将另外一个数除成 $0$ 。
  
一个公式概括答案：

$$ans=\begin{cases}
0 & a=b=0 \cr
d & a\times b=0 \text{ 且 } a+b\neq 0 \cr
\min\{c,2\times d\} & a=b\neq 0 \cr
\min\{c+d,2\times d\} & \text{其他情况}
\end{cases}$$

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int a,b,c,d,ans=INF;
int main(){
    a=qread(),b=qread(),c=qread(),d=qread();
    ans=min(ans,c+d);
    if(a==b) ans=min(ans,c);
    if(a==0||b==0){
        ans=min(ans,d);
    }
    ans=min(ans,2*d);
    if(a==0&&b==0) ans=0;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：囧仙 (赞：1)

## 题目大意

有两个非负整数 $a,b$ ，使用两种操作将它们都变成 $0$ 。

1. 两个数同时减去正整数 $x$ 。

2. 一个数乘以正整数 $x$ ，另一个数除以 $x$ 并下取整。

## 题解

提供一个 $\text{Pascal} $ 版本的题解，共大家参考。

题面操作简单，但似乎并不那么容易写。先让我们从题目给出的部分分入手。

- $\textbf{Subtask 1}:a=b=0$

显然，我们只要输出 $0$ 即可。

- $\textbf{Subtask 2}:a=0$

使用操作 $2$ 。显然，$0$ 乘以任何数都为 $0$ 。于是，我们让 $a$ 乘以一个很大的正整数（比如 $10^{18}$） ，$b$ 除以 $x$ 下取整后自然变成了 $0$ 。

- $\textbf{Subtask 3\& 5}:a=b$

这种情况下，我们可以仅使用一次 $c$ 操作让 $a,b$ 变成 $0$ 。

- $\textbf{Subtask 7}:\text{无特殊限制}$

首先，我们能够通过操作 $1$ **或者** $2$ 将一个数变成 $0$ 。这时就化归成了 $\text{Subtask 2}$ 的情形，即再花费 $d$ ，来将另外一个数变成 $0$ 。

结果只要取上述符合条件下所有情况的最小值即可。

关于 $\text{Pascal}$ 的条件语句，它的一般格式为`if 条件 then 支路1;` 或者 `if 条件 then 支路1 else 支路2 ;` 。如果某个支路内有多个操作，需要用 `begin end` 进行嵌套。

由于该题中条件语句较为简单，因此代码写起来非常容易。

## 参考代码

```pascal
uses math;
var a,b,c,d,ans:longint;
begin
    ans:=2147483647;
    read(a); read(b); read(c); read(d);
    if ((a=0) and (b=0)) then ans:=min(ans,0);
    if (a=b)             then ans:=min(ans,c);
    if ((a=0) or  (b=0)) then ans:=min(ans,d);
    ans:=min(ans,c+d); ans:=min(ans,2*d);
    writeln(ans);
end.
```


---

