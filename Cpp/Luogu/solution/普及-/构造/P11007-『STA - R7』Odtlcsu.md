# 『STA - R7』Odtlcsu

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/m38cxgmq.png)

## 题目描述

给定整数 $x,y$，构造一个长度不超过 $10^6$ 的整数序列使得其和为 $x$、平方和为 $y$。保证有解。

## 说明/提示

**本题采用捆绑测试。**

数据范围：
- Subtask 1 (10pts)：$y\le 10$。
- Subtask 2 (40pts)：$x=0$。
- Subtask 3 (50pts)：无特殊限制。

对于全部数据，$0\le |x|,y\le10^6$，保证有解。

## 样例 #1

### 输入

```
100 5000```

### 输出

```
2
50 50```

## 样例 #2

### 输入

```
0 5000```

### 输出

```
2
50 -50```

# 题解

## 作者：Acheron_RBM (赞：20)

有个很显然的结论，题目中的 $x$ 与 $y$ 奇偶性相同。

有个更简单的证明，奇数的平方为奇数，偶数的平方为偶数，所以 $x$ 与 $y$ 奇偶性相同。

思路就显而易见了，考虑构造一个长度为 $y$ 的序列，其中的每个数为 $\pm1$。答案就比较显然了，我们先假设有 $y$ 个 $1$ 考虑每将一个 $1$ 修改成 $-1$ 对 $x$ 
的贡献为 $2$。所以我们只需改 $(y-x)\div2$ 个 $-1$ 即可。

代码：

```cpp
int main()
{
	int n,k;
	cin>>n>>k;
	cout<<k<<"\n";
	int cnt=abs(k-n)/2;
	for(int i=1;i<=cnt;i++)
	{
		cout<<"-1 ";
	}
	for(int i=1;i<=k-cnt;i++)
	{
		cout<<1<<" ";
	}
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：9)

首先，我们发现：$y\le 10^6$，序列长度也 $\le 10^6$。容易想到方案：取 $y$ 个数，每个数都取 $1$ 或 $-1$，平方和为 $y$，再构造和为 $x$ 即可。

但是，我们遇到一个问题：如果 $x,y$ 奇偶性不同，那么就无法使用上述方法构造了！

再仔细想一想，我们会发现一个性质：$x,y$ 必然奇偶性相同。以下给出证明（有些绕）：

- 若 $x$ 为偶数，则序列中必然有偶数个奇数。奇数的平方是奇数，所以平方和中也必然有偶数个奇数，$y$ 也为偶数。

- 若 $x$ 为奇数，则序列中必然有奇数数个奇数。奇数的平方是奇数，所以平方和中也必然有奇数个奇数，$y$ 也为奇数。

所以我们成功解决了奇偶性的问题，原问题也就迎刃而解：输出 $\frac{y+x}{2}$ 个 $1$，$\frac{y-x}{2}$ 个 $-1$，即可满足条件。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
signed main(){
	cin>>x>>y;
	int a=(y+x)/2,b=(y-x)/2;
	cout<<y<<'\n';
	for(int i=1;i<=a;i++)cout<<"1 ";
	for(int i=1;i<=b;i++)cout<<"-1 ";
	return 0;
}
```

---

## 作者：_Supernova (赞：7)

### 一、题意简述。

要求构造序列 $a$，使得各项和为 $x$，平方和为 $y$。

### 二、思路分析。

为了方便，想到用 $1$ 和 $-1$ 来构造序列，个数即为 $y$ 个。

如何使和为 $x$ 呢？

设我们要 $a$ 个 $1$，$b$ 个 $-1$。

则有：

$a+b=y$

并且：

$a-b=x$。

解得 $a=\frac{x+y}{2}$ 和 $b=\frac{y-x}{2}$。

输出即可。

### 三、代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef unsigned long long ull;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <pii, int> piii;
typedef long double ld;
int x, y, a, b;
int main(void) {
	cin.tie(0), cout.tie(0);
	cin >> x >> y;
	a = (x + y) >> 1, b = (y - x) >> 1;
	cout << y << '\n';
	for (int i = 1; i <= a; ++i) cout << 1 << ' ';
	for (int i = 1; i <= b; ++i) cout << -1 << ' ';
	return 0;
}
```

谢谢大家！

---

## 作者：mediocre_ (赞：6)

题目保证有解就说明 $x,y$ 要么同为奇数，要么同为偶数。

证明如下。

如果 $y$ 为奇数，那么 $y$ 就是由奇数个奇数相加而成的。

而 $y$ 又是很多数的平方相加而成的，而我们都知道一个数的平方如果是奇数那这个数就是奇数。

所以 $y$ 就是由奇数个奇数的平方相加而成的。

而 $x$ 就是由这些数相加而成的，所以当 $y$ 为奇数时 $x$ 就为奇数。

看到题目时可以很容易想到输出 $y$ 个 $1$ 与 $-1$ ，使它们相加为 $x$ ，不用考虑 $y$ 因为 $1$ 与 $-1$ 的平方都是 $1$ 。

那么 $1$ 与 $-1$ 各要输出多少个呢？

很简单，我们只需要稍加分类讨论就可以。

当 $y$ 为奇数且 $x>0$ 时， $1$ 要输出 $\frac{y+1}{2} + \frac{x}{2}$ 个， $-1$ 要输出 $y-(\frac{y+1}{2} + \frac{x}{2})$ 个。

当 $y$ 为奇数且 $x<0$ 时， $1$ 要输出 $\frac{y-1}{2} + \frac{x}{2}$ 个， $-1$ 要输出 $y-(\frac{y-1}{2} + \frac{x}{2})$ 个。

其余情况 $1$ 与 $-1$ 都是各输出 $\frac{y}{2} + \frac{x}{2}$ 个。

既然思路理清楚了，就开始写代码吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
int x, y, yy;
int main() {
    scanf("%d%d", &x, &y);
    printf("%d\n", y);
    yy = y;
    if (y & 1 && x > 0) ++y;
    else if (y & 1 && x < 0) --y;
    for (int i = 1; i <= y / 2 + x / 2; ++i) printf("1 ");
    for (int i = y / 2 + x / 2 + 1; i <= yy; ++i) printf("-1 ");
    return 0;
}
```

---

## 作者：TemplateClass (赞：4)

注意到 $1 ^ 2 = 1$，$(-1) ^ 2 = 1$。由于它们的符号相反，平方相同，所以我们考虑使用它们。

设我们使用 $p$ 个 $1$ 和 $q$ 个 $-1$，则有

$$\begin{cases}1 \times p + (-1) \times q = x \\ 1 ^ 2 \times p + (-1) ^ 2 \times q = y\end{cases}$$

解得 $p = \dfrac{x + y}{2}$，$q = \dfrac{y - x}{2}$。

直接输出这么多的 $1$ 和 $-1$ 即可。

---

接下来将证明做法的正确性：

1. $y - x$ 一定 $\ge 0$。
2. $p$ 和 $q$ 一定是整数。
3. $p + q \le 10 ^ 6$。

---

1. 首先对于 $a \in \Z$，有 $a \le a ^ 2$；  
   分类讨论，当 $a = 0$ 时，成立；当 $a < 0$ 时，移项得 $1 \ge a$，成立；当 $a > 0$ 时，移项得 $1 \le a$，成立。  
   由于 $x = \sum \limits _ {i = 1} ^ {n} a _ i$，$y = \sum \limits _ {i = 1} ^ {n} a _ i ^ 2$，所以 $x \le y$，即 $x - y \le 0$。

2. $p$ 和 $q$ 是整数的前提是 $x + y$ 与 $y - x$ 均为 $2$ 的倍数，这需要 $x$ 与 $y$ 的奇偶性相同。  
   由于一个数平方后不改变其奇偶性，所以 $x$ 与 $y$ 奇偶性相同，$p$ 和 $q$ 是整数。

3. $p + q = \dfrac{(x + y) + (y - x)}{2} = y \le 10 ^ 6$

---

```cpp
void solve(){
	int x, y;
	std::cin >> x >> y;
	int a = (x + y) / 2, b = (y - x) / 2;
	
	std::cout << a + b << "\n";
	for(int i = 1; i <= a; ++i) {
		std::cout << "1 ";
	}
	for(int i = 1; i <= b; ++i) {
		std::cout << "-1 ";
	}
}
```

---

## 作者：canwen (赞：4)

## 分析
首先我们先证明**只有 $x,y$ 奇偶性相同时才有解**。

奇数与奇数的乘积仍然为奇数，偶数与偶数的乘积仍然为偶数，所以数列中的**所有数的和**和**所有数的平方和**奇偶性相同。

证毕。

因为 $x,y$ 奇偶性相同，我们设 $n=|(y-|x|)|$， 那么 $n$ 必然可以被 $2$ 整除。

数列中的所有和为 $x$，当 $x<0$ 时，我们可以先输出 $|x|$ 个 $-1$，否则输出 $x$ 个 $1$。

接着输出 $n \div 2$ 对 $-1,1$，这样就能保证所有数列中的树的平方和为 $y$。

坑点在于 $x$ 可以为负数。

~~这是这场比赛唯一会做的题了，还交了十几发。~~
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,n;
int main(){
	scanf("%d%d",&x,&y);
	cout<<y<<'\n';
	for(int i=1;i<=abs(x);i++){
		if(x<0) cout<<-1<<" ";
		else cout<<1<<" ";
	}
	n=abs(y-abs(x));
	for(int i=1;i<=n/2;i++){
		cout<<1<<' '<<-1<<' ';
	}
	return 0;
}
```

---

## 作者：Decepticon (赞：4)

今天比赛的第 $1$ 题，感慨万分。

### 题目链接

[P11007 『STA - R7』Odtlcsu](https://www.luogu.com.cn/problem/P11007)

### 题目大意

构造若干个整数，使得它们的和为 $x$，平方和为 $y$。

### 题目分析

注意到，一个整数 $x$ 和它的平方 $x^2$ 奇偶性相同。

我们设自然数 $p$ 为奇数，那么 $p$ 就可以表示成奇数个奇数和若干个偶数的和，那么这些数的平方的和 $q$ 也一定是奇数。

偶数也如此。

所以我们可以得到 $x$ 和 $y$ 的奇偶性相同。

因为 $x^2 \ge 0$，所以我们可以不断构造 $-1$ 和 $1$ 来靠近答案。

我们设要构造 $a$ 个 $1$ 和 $b$ 个 $-1$。

所以可以得到 $
\begin{cases}
  a + b = y \\
  a - b = x \\
\end{cases}
$

解这个二元一次方程组可以得到 
$
\begin{cases}
a = \frac{x + y}{2} \\
b = y - \frac{x + y}{2} \\
\end{cases}
$

最后只要输出 $\frac{x + y}{2}$ 个 $1$ 和 $y - \frac{x + y}{2}$ 个 $-1$ 即可。

### $\text{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
int x,y;

int main(){
    cin >> x >> y;
    int p = (x+y)/2,q = y-(x+y)/2;
    cout << p+q << "\n";
    for(int i = 1; i <= p; i++) cout << "1 ";
    for(int i = 1; i <= q; i++) cout << "-1 ";
    return 0;
}
```

---

## 作者：jiangyunuo (赞：3)

### 题目大意：
本题意思十分好理解，构建一个序列，长度任意，保证序列所有数字之和等于 $x$，所有数字的平方之和等于 $y$，输出时要输出序列长度。
### 主要思路：
看到样例二我发现可以用负数，一对相反数的平方是相等的，因此 $x$ 和 $y$ 就很容易达成了：我可以用 $1$ 和 $-1$ 来凑，只要 $y$ 个 $1$ 或 $-1$ 就可以完成平方和为 $y$ 的条件了，因为 $1$ 和 $-1$ 的平方都是 $1$，一个个堆起来就可以了；至于 $x$，使用 $1$ 和 $-1$ 来回控制就好。注意：这样的情况下整个序列的长度为 $y$。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int x,y;
    cin>>x>>y;
    int n=y,ans=0;   //n 用来存储 y ，但好像没啥用，ans 表示当前序列所有元素之和。
    cout<<n<<endl;    //输出序列长度。
    for(int i=1;i<=n;i++){
    	if(ans<=x){ans++;cout<<1<<" ";}   //如果当前序列所有元素之和少于 x，那么下个元素用 1。
        else{ans--;cout<<-1<<" ";}      //如果当前序列所有元素之和多于 x，那么下个元素用 -1。
	}
	return 0;
}
```
### 证明：
考虑到这个想法有些难懂，我再加个证明。  
首先，按我这个说法，要让 $1$ 和 $-1$ 创建一个满足序列所有数字之和等于 $x$，所有数字的平方之和等于 $y$ 的序列，我们要保证 $x$ 和 $y$ 奇偶性相同，因为奇数 $-$ 奇数 $=$ 偶数，偶数 $-$ 偶数 $=$ 偶数，当然 $y \ge x$，因为一个数的平方一定大于等于这个数，前面说的 $x$ 和 $y$ 的奇偶性相同是因为当组成 $y$ 的几个元素减去组成 $x$ 的那 $x$ 个 $1$ 后，剩下了偶数个 $1$ 或 $-1$，当它们的数量相同时，就可以相互抵消，变成 $0$，如果认为我解答的不够好，可以参考一下[此帖](https://lglg.top/910190/2)中大佬们的解答，其中 @tanjunhan666 这位大佬讲的十分详细。  
只要我们证明 $x$ 和 $y$ 奇偶性相同，那么我的做法就是对的，实际上，如果 $x$ 和 $y$ 的奇偶性不相同，那么就是无解的，不信你自己搞几个数据试试，如果还不信，那就接着往后看。  
其实，我们依旧可以参考[此帖](https://lglg.top/910190)，其中 @Nuclear_Fish_cyq 的做法其实适用于包含其他元素，并依旧成立的序列，大家可以参考一下。  
感谢[此帖](https://www.luogu.com.cn/discuss/910190)中回复的大佬，给我提供了思路。

---

## 作者：I_Love_DS (赞：3)

## 前言

很有思维的一道构造题。

## 思路

首先我们可以确定，$x$ 和 $x^2$ 的**奇偶性一定相同**（详见证明）。

所以 $|x|$ 和 $y$ 的**奇偶性必然相同**，因为题目保证有解。

因为 $(-1)^2 = 1, 1^2 = 1$，所以令 $a_i \in \{1,-1\}$，且 $\sum a_i = x,\sum a_i^2 = y$。

接下来就可以很容易地解决了，详见代码。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int x, y;

int main() {
	scanf("%d%d", &x, &y);
	printf("%d\n", y);
	for (int i = 1; i <= abs(x); i++) printf("%d ", x / abs(x));
	y -= abs(x);
	for (int i = 1; i <= y / 2; i++) printf("1 ");
	for (int i = 1; i <= y / 2; i++) printf("-1 ");
	return 0;
}
```

## 证明环节
需要证明 $x$ 和 $x^2$ 奇偶性相同。

也就是：

1. 当 $x$ 是偶数时，$x^2$ 也是偶数。
2. 当 $x$ 是奇数时，$x^2$ 也是奇数。

### 1. 偶数情况下

假设 $x$ 是偶数。根据偶数的定义，我们可以表示 $x$ 为 $x = 2k$，其中 $k$ 是一个整数。

现在我们计算 $x^2$：
$ x^2 = (2k)^2 = 4k^2 $

注意到 $4k^2$ 可以被写成 $2(2k^2)$。这是一个偶数的形式，因为它是 $2$ 乘以一个整数。因此，$x^2$ 也是偶数。

这证明了当 $x$ 是偶数时，$x^2$ 也是偶数。

### 2. 奇数情况下

假设 $x$ 是奇数。根据奇数的定义，我们可以表示 $x$ 为 $x = 2k + 1$，其中 $k$ 是一个整数。

现在我们计算 $x^2$：
$$x^2 = (2k + 1)^2 = 4k^2 + 4k + 1 = 2(2k^2 + 2k) + 1$$

注意到 $2(2k^2 + 2k)$ 是一个偶数，因为它是 $2$ 乘以一个整数。将这个偶数加上 $1$ 得到的 $x^2$ 是奇数的形式（奇数是偶数加一）。

这证明了当 $x$ 是奇数时，$x^2$ 也是奇数。

### 总结

我们已经证明了：
- 当 $x$ 是偶数时，$x^2$ 也是偶数。
- 当 $x$ 是奇数时，$x^2$ 也是奇数。

因此，$x$ 和 $x^2$ 的奇偶性总是相同的。

Q.E.D

---

## 作者：qw1234321 (赞：2)

观察到 $x,y$ 与 $n$ 是同阶的，考虑先放 $y$ 个 $1$ 使得其满足平方和条件。

由于要使得数组和为 $x$，且保持平方和不变，自然想到将 $1$ 变成 $-1$，可以使得和减少 $2$ 而平方和不变。

并且，易知 $x,y$ 同奇偶，所以数组的和从 $y$ 一定可以通过不断 $-2$ 变成 $x$。

计算将多少个 $1$ 变成 $-1$ 即可。

---

## 作者：_xxxxx_ (赞：2)

纪念一下一眼有思路的一道题。

题意题目很清楚了。

### 分析

注意数据范围，这是一个很关键的点，$y\le 10^{6}$。

这代表了什么呢？欸，$n\le 10^{6}$。

我们可以用 $y$ 个 $1$ 来构造，因为 $1^2=1,(-1)^2=1$，所以 $y$ 这个约束就解决了，我们只需要关心她们的正负就行了。

注意到一个性质，$x$ 的奇偶性与 $y$ 的奇偶性相同。由小学数学知识可得知，奇数乘奇数等于奇数，偶数乘偶数等于偶数。平方就等于乘自己，所以 $x$ 的奇偶性与 $y$ 的奇偶性就相同了。

最后注意一下 $x$ 的正负。先构出 $x$ 再用 $1,-1$ 的组合变成 $0$ 就行了。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e6 + 10;
int x, y;
signed main()
{
    cin >> x >> y;
    int fl = 0;
    cout << y << endl;//y个1
    for(int i = 1; i <= y; i++)
    {
        //先构造出 x
        if(i <= abs(x)) cout << (x < 0 ? -1 : 1) << " ";//注意正负
        else
        {
            if(fl == 0) cout << -1 << " ";
            else cout << 1 << " ";
            fl ^= 1;
            //1,-1交替输出，使得和为0
        }
    }
    return 0;
}
```

---

## 作者：Xssion37_XY (赞：2)

简单构造题目，~~建议评橙~~。

直接分类讨论。

- 当 $x = 0$ 时：

要使得整个序列个元素之和为 $0$ 且还要平方和为 $y$，容易想到 $1$ 和 $-1$ 这样的一对，它们俩和为 $0$ 但平方和为 $2$，所以这种情况很简单，直接输出 $\frac{y}{2}$ 个 $1$ 和 $-1$ 即可，序列长度为 $y$，满足条件。

- 当 $x > 0$ 时：

各元素之和为正数，那么就不能只依靠 $1$ 和 $-1$ 交替来构造，必须留一些位置来使各元素之和为正数。

留多少呢？显然是留 $x$ 个位置。前面的 $y - x$ 个位置用于填充 $1$ 和 $-1$，而后 $x$ 个位置只填充 $1$ 即可，序列长度为 $y - x + x = y$，满足条件。

- 当 $x < 0$ 时：

此情况与 $x > 0$ 时思路一样，只需要注意 $x$ 是负数，所以最后 $|x|$ 个位置填充的是 $-1$（因为 $x < 0$ 所以要向将元素之和构造为负数）。


```cpp
#include <iostream>
using namespace std;
int main(){
	int x,y;
	cin >> x >> y;
	if (x == 0){
		cout << y << endl;
		for (int i = 1;i <= y / 2;i ++){
			cout << 1 << " " << -1 << " ";
		}
	}
	else if (x > 0){
		cout << y << endl;
		for (int i = 1;i <= (y - x) / 2;i ++){
			cout << 1 << " " << -1 << " ";
		}
		for (int i = 1;i <= x;i ++){
			cout << 1 << " ";
		}
	}
	else {
		cout << y << endl;
		for (int i = 1;i <= (y + x) / 2;i ++){
			cout << 1 << " " << -1 << " ";
		}
		x *= -1;
		for (int i = 1;i <= x;i ++){
			cout << -1 << " ";
		}
	}
} 
```

~~当然这么做是赛时乱搞。~~

可以考虑简化代码，~~因为它真的太长了。~~

观察一下 $x$ 和 $y$ 的关系，不难发现 $x$ 和 $y$ 的奇偶性一致。

考虑证明，假设 $x$ 为奇数，那么一定是奇数个奇数相加为奇数，又因为奇数的平方还是奇数，那么奇数个奇数的平方相加还是奇数，所以 $y$ 也为奇数。

同理可得：$x$ 为偶数时 $y$ 也为偶数。

既然 $x$ 与 $y$ 的奇偶性相同，那么显然就可以构造出一个长为 $y$ 且包含 $\frac{y - x}{2}$ 个 $-1$ 和 $\frac{y + x}{2}$ 个 $1$ 的序列，满足条件。


```cpp
#include <iostream>
using namespace std;
int main() {
	int x,y;
	cin >> x >> y;
	int bo = (y - x) >> 1;
	int boo = (y + x) >> 1;
	cout << y << endl;
	for (int i = 1; i <= bo; i ++) {
		cout << -1 << " ";
	}
	for (int i = 1; i <= boo; i ++) {
		cout << 1 << " ";
	}
}
```

---

## 作者：Wuzetong (赞：2)

## 关联内容
[题目链接](https://www.luogu.com.cn/problem/P11007)  
[AC记录](https://www.luogu.com.cn/record/174889615)

## 题目分析
> 奇数的平方一定为奇数，偶数的平方一定为偶数。

显然，我们只需要假设有 $y$ 个 $1$，并考虑将每个 $1$ 修改为 $-1$ 的贡献为 $2$。所以，我们只需要改 $(y-x)\div2 $ 个 $-1$ 即可。

## 代码实现
根据题目分析写出代码即可。
### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	cout<<k<<"\n"; //种类数
	int a=abs(k-n)/2;
	for(int i=1;i<=a;i++){ //a个-1
		cout<<"-1 ";
	}
	for(int i=1;i<=k-a;i++){ //其余全部为1
		cout<<"1 ";
	}
	return 0;
}
```

---

## 作者：lichenxi111 (赞：1)

题意不写了，题面比较简洁。

## 思路

观察到 $y \le 10 ^ 6$，同时构造的序列长度 $n \le 10 ^ 6$。那开心了，发现我构造的序列中只需要用到 $1$ 和 $-1$，就可以凑出 $x$ 和 $y$。

与此同时，我们根据余数的可乘方性，发现对于序列里每一项，它的奇偶性与它平方的奇偶性相同，所以，$x$ 与 $y$ 的奇偶性相同。

那么，设序列中有 $a$ 个 $1$ 和 $b$ 个 $-1$，可列出方程组：

$\begin{cases}
    a - b = x\\
    a + b = y\\
  \end{cases}$

解得：

$\begin{cases}
    a = \frac{x+y}{2}\\
    b = y - \frac{x+y}{2}\\
  \end{cases}$

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int x,y;
	cin >> x >> y;
	int cnt1 = 0,cnt2 = 0;
	cnt1=(x+y)/2;
	cnt2=y-cnt1;
	cout << y << endl;
	for(int i = 1;i <= cnt1;i++)
	{
		cout << 1 << " ";
	}
	for(int i = 1;i <= cnt2;i++)
	{
		cout << -1 << " ";
	}
	return 0;
}
```

---

## 作者：Swirl (赞：1)

本文需要保证读者掌握小学知识的奇偶数及运算。

下文将奇数简化为 $o$，偶数简化为 $e$（$o$ 和 $e$ 不代指任何数，所以会出现类似 $e + e = e$ 的情况）。

$x$ 和 $y$ 的奇偶性一定相同，证明如下：

设存在一组 $(x,y)$ 满足其奇偶性不同。

- 若 $x$ 为奇数。

则：

$$
x = k \times e + o \times o = o
$$

$k$ 为任意自然数。

那么：

$$
\begin{split}
y &= k \times e^2 + o \times o^2 \\
&= k \times e + o \times o \\
&= e + o \\
&= o
\end{split}
$$

矛盾。


- 若 $x$ 为偶数。

则：

$$
x = k \times e + e \times o = e
$$

那么：

$$
\begin{split}
y &= k \times e^2 + e \times o^2 \\
&= k \times e + e \times o \\
&= e + e \\
&= e
\end{split}
$$

又矛盾。

证毕。

此时就很好构造了。

因为 $1^2 = (-1)^2 = 1$，我们可以用 $y$ 个 $1$ 或 $-1$ 来满足平方和为 $y$ 的条件。

因为 $x$ 和 $y$ 同奇偶，那么只需要构造 $\frac {b - a} {2}$ 个 $-1$ 和 $y - \frac{b - a}{2}$ 个 $1$ 即可。

不贴代码。

---

## 作者：JYX0924 (赞：1)

看完题后，首先想到用 $y$ 个 $1$ 或 $-1$ 构成这个数列，因为 $x$ 和 $y$ 的奇偶性一致。

证明：若 $x$ 为奇数，那么数列中必然有奇数个奇数，因为奇数的平方也是奇数，所以 $y$ 也是奇数。同理可得当 $x$ 为偶数时 $y$ 也是偶数。

下面是我的 AC 代码。


```c
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll x,y,sum;
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>x>>y; cout<<y<<"\n";
    while(y--)
    {
        if(sum+1<=x) sum++,cout<<"1 ";
        else sum--,cout<<"-1 ";
    }
    return 0;
}
```
谢谢大家！！！

---

## 作者：__Allen_123__ (赞：1)

场外选手来凑热闹。

> 题目大意：构造一个序列使其和为 $x$，平方和为 $y$。

本题我们可以发现一个结论：**题目中给定的 $x,y$ 的奇偶性必定相同**。

证明：分两种情况讨论。

1. 当 $x$ 为奇数时：
   
   此时序列中显然有奇数个奇数，其余数都是偶数。由于平方不会改变一个数的奇偶性，那么它们的平方和也必然是奇数。
2. 当 $x$ 为偶数时：
   
   同理，序列中有偶数个奇数，它们的平方和也必然是偶数。

再由于题目保证有解，故得证。

观察到 $0\le y\le 10^6$，同时我们构造的序列长度可以达到 $10^6$，故我们可以考虑构造一个仅包含 $1$ 和 $-1$ 的序列，这两个数的平方都等于 $1$，此时序列的长度就为 $y$。

因为序列中数的和为 $x$，且 $x,y$ 奇偶性相同（即总是可以构造出一个只包含 $1$ 和 $-1$ 的合法序列），所以构造 $\frac{x+y}{2}$ 个 $1$，$y-\frac{x+y}{2}$ 个 $-1$ 即可。

```cpp
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y);x <= (int)(z);x++)
using namespace std;
int x, y;
signed main(){
    scanf("%d%d", &x, &y);
    printf("%d\n", y);
    rep(i, 1, (x + y) / 2){
        printf("1 ");
    }
    rep(i, 1, y - (x + y) / 2){
        printf("-1 ");
    }
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

这种构造题，一般可以先观察不变量。如果现在有一个数组 $p$ 是目标数组，现在加了一个数字，如果是奇数，那么 $x$ 就会改变奇偶性，同样 $y$ 也会。如果是偶数，那么 $x$ 奇偶性不变，$y$ 也不变。所以 $x$ 和 $y$ 的奇偶性是一样的。

这样子，我们考虑用平方的非负性来构造。如果只有 $1$ 和 $-1$ 两种数字，那么长度就是 $y$。设有 $a$ 个 $1$ 和 $b$ 个 $-1$，那么就是 $a-b = x,a+b=y$。因为 $x$ 和 $y$ 奇偶性相同，所以必有整数解。解方程得 $a= \frac{x+y}{2},b=\frac{y-x}{2}$。所以直接输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 100005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll x = rd(), y = rd(); 
int main(){
	x = x;cout << y << "\n";
	for (int i = 1; i <= (x + y) / 2; i++) printf ("1 ");
	for (int i = 1; i <= (y - x) / 2; i++) printf ("-1 ");
	return 0;
}
```

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11007)

不难通过 $1$ 和 $-1$ 维护序列和与平方和。  
具体地，由于 $x\le y$，$1+(-1)=0$ 且 $1^2=(-1)^2$，所以我们可以用 $1,-1,1,-1,\cdots,1,-1$ 的方法凑直到 $x=y$，剩余部分直接全 $1$ 即可。最终序列长度为 $y$。

证明：

- 为什么 $x\le y$？  
因为有：
  - 对于任意整数 $a_i$，满足 $a_i\le a_i^2$。
  - 由于 $x=\displaystyle\sum_{i=1}^n a_i$ 且 $y=\displaystyle\sum_{i=1}^n a_i^2$，所以 $x\le y$。
- 为什么 $(y-x)$ 一定为偶数？  
因为有：
  - 对于任意整数 $a_i$，若 $a_i$ 为奇数，则 $a_i^2$ 也为奇数；若 $a_i$ 为偶数，则 $a_i^2$ 也为偶数。
  - 奇数与奇数相减，结果为偶数；偶数与偶数相减，结果为偶数。
  - 由于 $x=\displaystyle\sum_{i=1}^n a_i$ 且 $y=\displaystyle\sum_{i=1}^n a_i^2$，所以：  
$\begin{aligned}
y-x&=\displaystyle\sum_{i=1}^n a_i^2-\displaystyle\sum_{i=1}^n a_i\\
&=\displaystyle\sum_{i=1}^n a_i^2-a_i
\end{aligned}$  
所以 $(y-x)$ 一定为偶数。

总结下来，前面用 $1,-1,1,-1,\cdots,1,-1$ 的方法凑，长度为 $(y-x)$，则 $1$ 和 $-1$ 的长度均为 $\frac{y-x}{2}$ 个。剩余部分全 $1$，长度为 $x$。  
所以我们输出 $(\frac{y-x}{2}+x)$ 个 $1$ 和 $\frac{y-x}{2}$ 个 $-1$ 即可完成本题。  
代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
#define lb(x) x&-x
#define itn int
#define fpr for
#define rD rd
inline string its(int x){stringstream ss;string s;ss<<x;ss>>s;return s;}
inline int sti(string s){stringstream ss;int x;ss<<s;ss>>x;return x;}
inline string jia(string a1,string b1){int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=max(lena,lenb),t=0;for(int i=0;i<lenc;i++){c[i]=a[i]+b[i]+t;if(c[i]>=10){t=1,c[i]%=10;}else{t=0;}}if(t==1){lenc++;c[lenc-1]=1;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline string jian(string a1,string b1){if(a1.size()<b1.size()||a1.size()==b1.size()&&a1<b1){pc('-'),swap(a1,b1);}int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=lena;for(int i=0;i<lenc;i++){if(a[i]<b[i]){a[i+1]--,a[i]+=10;}c[i]=a[i]-b[i];}while(lenc>=1&&c[lenc-1]==0){lenc--;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline int qpow(int a,int b,int p){int ans=1;while(b){if(b&1){ans=(ans*a)%p;}b>>=1;a=(a*a)%p;}return ans;}
inline int qp(int a,int b){int ans=1;while(b){if(b&1){ans*=a;}b>>=1;a*=a;}return ans;}
signed main()
{
	int x,y;
	rd(x,y);
	wtl(y);
	for(int i=1;i<=(y-x)/2;i++)
	{
		wt(-1),kg;
	}
	for(int i=(y-x)/2+1;i<=y;i++)
	{
		wt(1),kg;
	}
	hh;
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：0)

首先，有解当且仅当 $x$ 与 $y$ 奇偶性相同。

如何证明呢？若存在一个数 $z$ 满足 $z \equiv t \pmod{2}$，其中 $0 \le t \le 1$，那么肯定有 $z^2 \equiv t \pmod{2}$。所以 $x$ 和 $y$ 奇偶性要相同。

接下来考虑怎么构造。我们可以构造 $y$ 个 $1$ 或 $-1$，那么怎么让它们的和为 $x$ 呢？我们不妨设 $a, b$ 为 $1$ 和 $-1$ 的个数，此时可以列出方程组：

$$
\begin{cases}
a+b=y \\
a-b=x
\end{cases}
$$

解得 $a = \frac{x + y}{2},b=\frac{y - x}{2}$。

直接构造即可。

---

## 作者：xingshuyan000 (赞：0)

# 题目分析

一道比较简单的数学题 + 构造题。

给定数列的和为 $x$，数列的平方和为 $y$，而 $|x|,y \in [0,10^6]$，数列的长度 $n \le 10^6$，所以我们考虑数列中只填 $1$ 和 $-1$。

$x,y$ 的奇偶性显然相同。设数列中一共有 $p$ 个 $1$，一共有 $q$ 个 $-1$，因为 $1^2=(-1)^2=1$，所以 $p+q=y$，而 $p-q=x$，所以 $p=\frac{y+x}{2},q=\frac{y-x}{2}$。

最后构造出来的数列长度是 $y$，别忘记输出了。~~（我当时就是忘记输出数列长度所以爆零了）~~

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+50;
int a[N];
int main()
{
	int x,y;
	cin>>x>>y;
	for(int i=1;i<=y;i++)a[i]=1;
	int q=(y-x)/2;
	for(int i=1;i<=q;i++)a[i]=-1;
	cout<<y<<endl;
	for(int i=1;i<=y;i++)cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

**评价：简单构造。**

## 思路

注意题目中的“如果有多解输出任意一种即可”。

由于 $a$ 与 $a^{2}$ 的奇偶性必定是一致的，所以我们可以将情况分为两种。

1. 当 $x$ 与 $y$ 奇偶性不一致时，但由于 $a$ 与 $a^{2}$ 的奇偶性必定是一致的，所以始终无法构造出正确的序列。但注意题目中的这句话“保证有解”。所以就不用管它了。

2. 当 $x$ 与 $y$ 奇偶性一致时，我们可以先加上 $y$ 个 $1$，这样平方和的条件就满足了，易证明 $y$ 一定大于 $x$，然后将一部分 $1$ 改为 $-1$，这样的话平方和不变，但和会减 $2$。经计算，将前 $\frac{(y-x)}{2}$ 个数改为 $-1$，其和就被修改为了 $x$，且序列长度是 $y$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int x, y;
int main() {
	cin >> x >> y;
	cout << y << '\n';
	for (int i = 1; i <= (y - x) / 2; i++) cout << "-1 ";
	for (int i = 1; i <= y - (y - x) / 2; i++) cout << "1 ";
	return 0;
}
```

---

## 作者：vectorxyz (赞：0)

十分水，显然，如果 $x$ 和 $y$ 奇偶性不同，无法构成序列。

我们先想着让和的条件满足，我想的是用 $x$ 个 $1$，然后考虑平方和，构成平方和还需要 $y-x$ 个 $1$，又考虑到不能让和改变，所以 $y-x$ 个一半是 $1$，一半是 $-1$。

又看到题目中说 $n \le 10^6$，我们这么多 $1$，会不会爆呢？又注意到 $0\le |x|,y\le10^6$，所以是正确的。

---

## 作者：Cyx20110930 (赞：0)

# 简要题意

给定 $x,y$，构造一个长度为 $n$ 的序列使得 $\sum a_i=x,\sum a_i^2=y$。

# Sol

由 $y\le 10^6$ 可知，长度一定不会超限。

易得使用 $1$ 和 $-1$ 构造数组的方法：长度为 $y$，和为 $x$，显然 $1$ 的个数为 $\frac {y+x}2$，$-1$ 的个数为 $\frac {y-x}2$。

综上，我们就做出了这题。

# Code

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int x,y;cin>>x>>y;
    cout<<y<<endl;
    //-1a+b=x,a+b=y
    int fs=(y-x)/2;
    for(int i=1;i<=fs;i++){
        cout<<"-1 ";
    }
    for(int i=fs+1;i<=y;i++){
        cout<<"1 ";
    }
}
```

---

