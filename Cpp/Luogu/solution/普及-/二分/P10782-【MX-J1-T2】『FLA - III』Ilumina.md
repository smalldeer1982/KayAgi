# 【MX-J1-T2】『FLA - III』Ilumina

## 题目背景

原题链接：<https://oier.team/problems/J1B>。

## 题目描述

定义 $\lfloor X \rfloor$ 为最大的小于等于 $X$ 的整数，例如 $\lfloor 1.99 \rfloor = 1,\lfloor 7 \rfloor = 7$。

有五个正整数 $n,m,a,b,c$，已知 $b=\left\lfloor \frac{a}{n} \right\rfloor , c=\left\lfloor \frac{b}{m} \right\rfloor$。

给定 $a$ 和 $c$ 的值，求出一个合法的 $b$ 的值，或者报告不存在合法的 $b$ 的值。

**本题使用自定义校验器，如果存在多个合法的 $b$ 的值，输出其中一个即可。**

## 说明/提示

**「样例解释 #1」**

对于第一组测试数据，取 $n=1,m=1$ 时可以得到 $b=1$。

对于第二组测试数据，取 $n=2,m=1$ 时可以得到 $b=3$。

对于第三、第四组测试数据，可以证明不存在合法的 $b$ 的值。

**「数据范围」**

|测试点编号|$a,c \leq$|特殊性质|
|:-:|:-:|:-:|
|$1 \sim 3$|$10$|无|
|$4 \sim 6$|$10^3$|无|
|$7 \sim 8$|$10^{18}$|有|
|$9 \sim 10$|$10^{18}$|无|

特殊性质：保证对于每组给定的 $a,c$ 一定存在合法的 $b$ 的值。

对于 $100\%$ 的数据，$1 \leq T \leq 10^5$，$1 \leq a,c \leq 10^{18}$。

2024 年 7 月 15 日：添加了 7 组 hack 数据置于 Subtask #1。

## 样例 #1

### 输入

```
4
1 1
7 3
23 8
17 23
```

### 输出

```
1
3
-1
-1
```

# 题解

## 作者：RyanLi (赞：26)

### 30 分解法

$a, c \le 10$ 的部分分。

已知 $b = \left \lfloor \dfrac{a}{n} \right \rfloor$，$c = \left \lfloor \dfrac{b}{m} \right \rfloor$，并且 $a$ 和 $c$ 的值已经给定。我们将 $b = \left \lfloor \dfrac{a}{n} \right \rfloor$ 代入 $c = \left \lfloor \dfrac{b}{m} \right \rfloor$ 中，得到下列式子。

$$
c = \left \lfloor \dfrac{\left \lfloor \dfrac{a}{n} \right \rfloor}{m} \right \rfloor
$$
因为 $n, m, a, b, c$ 均为正整数，并且 $n$ 和 $m$ 在 $b = \left \lfloor \dfrac{a}{n} \right \rfloor$ 和 $c = \left \lfloor \dfrac{b}{m} \right \rfloor$ 中均为分母，因此只有当 $n \le a$ 且 $m \le b$ 时，$b$ 和 $c$ 才为正整数。

枚举 $[1, a]$ 中的整数 $n$ 和 $\left[1, \left \lfloor \dfrac{a}{n} \right \rfloor \right]$ 中的整数 $m$，并判断是否有满足 $\left \lfloor \dfrac{\left \lfloor \dfrac{a}{n} \right \rfloor}{m} \right \rfloor = c$ 的 $n$ 和 $m$ 即可。

---

### 60 分解法

$a, c \le 10^3$ 的部分分。

使用 $\{ x \}$ 表示 $x$ 的小数部分，显然 $\{ x \} <1$，因此下列式子中 $\left \{ \dfrac{a}{n} \right \}$ 的值不可能改变式子的取值。

$$
\left \lfloor \dfrac{a}{nm} \right \rfloor = \left \lfloor \dfrac{\dfrac{a}{n}}{m} \right \rfloor = \left \lfloor \dfrac{\left \lfloor \dfrac{a}{n} \right \rfloor + \left \{ \dfrac{a}{n} \right \} }{m} \right \rfloor = \left \lfloor \dfrac{\left \lfloor \dfrac{a}{n} \right \rfloor}{m} \right \rfloor
$$
所以 $c = \left \lfloor \dfrac{a}{nm} \right \rfloor$。因为 $n$ 和 $m$ 可以为任意正整数，我们令 $n = 1$，此时 $b = a$，$c = \left \lfloor \dfrac{a}{m} \right \rfloor$。枚举 $m$ 即可。

---

### 80 分解法

$a, c \le 10^3$ 和特殊性质的部分分。

对于特殊性质，因为合法的 $b$ 始终存在，可以发现有如下等式成立。
$$
c = \left \lfloor \dfrac{\left \lfloor \dfrac{a}{n} \right \rfloor}{m} \right \rfloor = \left \lfloor \dfrac{b}{m} \right \rfloor
$$
$m$ 可以为任意正整数，因此我们令 $m = 1$，即可得到 $b = c$。直接输出 $c$ 的值即可。

---

### 正解

由 60 分解法可以发现，问题转化成了判断是否存在正整数 $m$ 使得 $c = \left \lfloor \dfrac{a}{m} \right \rfloor$。

如果存在这样的 $m$，由于构造中 $n=1$，直接输出 $a$ 即可。


$$
\left \lfloor \dfrac{a}{\left \lfloor \dfrac{a}{c} \right \rfloor} \right \rfloor \ge \left \lfloor \dfrac{a}{\dfrac{a}{c}} \right \rfloor = \left \lfloor c \right \rfloor = c = \left \lfloor \dfrac{a}{m} \right \rfloor
$$



存在合法的 $m$ 当且仅当存在区间 $[l,r]$ 满足 $l \leq r$ 且对于 $i \in [l,r] \cap \mathbb{Z}$ 有 $\left \lfloor \dfrac{a}{i} \right \rfloor =c$。

很显然，最大的满足条件的 $i$（使用 $i_0$ 表示）满足 $i_0 \times c \leq a$ 且 $(i_0+1) \times c > a$，容易得到 $i_0 = \left \lfloor \dfrac{a}{c} \right \rfloor$，计算 $i_0$ 的值并且检验 $\left \lfloor \dfrac{a}{i_0} \right \rfloor$ 是否等于 $c$ 即可判断是否存在合法的 $m$。

单组数据时间复杂度 $O(1)$。

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int t;
ll a, c;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        cin >> a >> c;
        if (a < c) cout << "-1\n";
        else cout << (a / (a / c) == c ? a : -1) << '\n';
    } return 0;
}
```

### 可能的其他解法

由 60 分解法可以得到 $m$ 具有单调性，因此可以对 $m$ 进行二分查找。单组数据时间复杂度 $O(\log n)$。

---

## 作者：cff_0102 (赞：8)

因为 $c=\lfloor\frac{b}{m}\rfloor$，$b=\lfloor\frac{a}{n}\rfloor$，所以 $c=\lfloor\frac{\lfloor\frac{a}{n}\rfloor}{m}\rfloor$。因为 $m$ 是个正整数，所以实际上 $\lfloor\frac{\lfloor\frac{a}{n}\rfloor}{m}\rfloor=\lfloor\frac{\frac{a}{n}}{m}\rfloor=\lfloor\frac{a}{nm}\rfloor$。设 $k=nm$，如果找不到 $k$ 使得 $c=\lfloor\frac{a}{k}\rfloor$，则必然无解，输出 $-1$。如果找到了这样的 $k$，则直接令 $n=k,m=1$，这样 $b=\lfloor\frac{a}{n}\rfloor=\lfloor\frac{a}{k}\rfloor=c$，$c=\lfloor\frac{b}{m}\rfloor=\lfloor\frac{c}{1}\rfloor=c$ 必然成立，直接输出 $c$ 即可。

于是问题转化为了能否找到一个正整数 $k$ 使得 $\lfloor\frac{a}{k}\rfloor=c$。易得 $ck\le a<(c+1)k$。转化一下，得到 $\frac{a}{c+1}<k\le\frac{a}{c}$。只要存在一个 $k$ 满足这个条件，那么就有解，否则就无解。

那么，只需判断 $(\frac{a}{c+1},\frac{a}{c}]$ 中是否存在整数即可。最快的方法就是判断 $\lfloor\frac{a}{c}\rfloor$ 是否大于 $\frac{a}{c+1}$，即 $(c+1)\lfloor\frac{a}{c}\rfloor$ 是否大于 $a$。若大于 $a$，则有解，输出 $c$，否则无解，输出 $-1$。

记得开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		long long a,c;cin>>a>>c;
		if(a/c*(c+1)>a)cout<<c<<endl;
		else cout<<-1<<endl;
	} 
	return 0;
}
```

---

## 作者：DFs_YYDS (赞：7)

官方题解好厉害，蒟蒻看不懂。我自己写一篇吧。
## 题目大意
给定两个整数 $a$ 和 $c$，让你找到一个整数 $b$，使其满足 $b=\left\lfloor \frac{a}{n} \right\rfloor,c=\left\lfloor \frac{b}{m} \right\rfloor$，其中 $n$ 和 $m$ 是任意正整数。输出任意一个满足条件的 $b$。
# 方法一：100分（？）
## 具体思路
我们将两个式子合并，得出：

$c=\left\lfloor \frac{\left\lfloor \frac{a}{n} \right\rfloor}{m} \right\rfloor$。

整理一下，得出：

$c=\left\lfloor \frac{a}{nm} \right\rfloor,b=\left\lfloor \frac{a}{n} \right\rfloor$。

那么现在，我们的任务就变成了找出合法的 $n$ 和 $m$，并输出 $\left\lfloor \frac{a}{n} \right\rfloor$。

而由于 `c++` 的 `/` 是整除，也就是自动下取整，所以我们可以不管式子中的下取整。

因为已经给出 $a$ 和 $c$，我们可以用 $a/c$ 求出 $nm$ 的积，然后枚举 $n$。

对于每次枚举，先用 $a/c/n$ 算出 $m$，然后判断是否合法，如果合法输出 $a/n$，否则继续枚举。

不懂的可以看注释，**注意开 `long long`**。
## 完整代码
```cpp
#include<bits/stdc++.h>//万能头。 
using namespace std;
int main(){//主函数。 
	int t;//t组数据。 
	cin>>t;//输入t。 
	while(t--){//while循环t组数据，等价于for(int i=0;i<t;i++){ 
		long long a,c,k,f=1;//a和c的含义如题目所示，k是a/c的值，f是无解判断。 
		cin>>a>>c;//输入a和c。 
		k=a/c;//k赋值为a/c。 
		for(int i=1;i*i<=k/*可以想一下为什么i*i就行了，可以参考一下质数判断*/;i++){
			if(k%i==0/*k/i表示n，因为n是正整数，所以如果k能整除i才可能存在合法的n*/ && a/i/(k/i)==c/*判断合法性，如果a/n/m=c，说明满足题目中的条件*/){
				cout<<a/i<<"\n",f=0;//输出a/i，也就是b，不是无解，f=0。 
				break;//跳出循环。 
			}
		}
		if(f)/*一直没找到合法解，也就是无解*/cout<<-1<<"\n";//输出-1。 
	}
	return 0;//好习惯。 
}//说实话，这个题目确实挺有迷惑性，一开始我还以为是枚举b呢。
```
# 方法二：100分（！）
方法一被 `hack` 了（悲）。

因为上面代码的最坏时间复杂度是 $O(t\sqrt{a})$，明显会超时。
## 具体思路
跟方法一一样，我们依旧使用：

$c=\left\lfloor \frac{a}{nm} \right\rfloor,b=\left\lfloor \frac{a}{n} \right\rfloor$。

我们设 $n$ 是 $1$，$nm$ 的积就是 $m$，就变成了：

$c=\left\lfloor \frac{a}{m} \right\rfloor,b=a$。

现在，就变成了求是否合法的 $m$ 了。

如果 $m$ 合法，那我们可以得出：

$c=\left\lfloor \frac{a}{\left\lfloor \frac{a}{c} \right\rfloor} \right\rfloor$

也就是说我们只需要判断输入的 $a$ 和 $c$ 是否满足上面的式子就行。

注意特判 $a$ 比 $c$ 小的情况，因为这种情况下 $\left\lfloor \frac{a}{c} \right\rfloor=0$，而除数不能为 $0$，所以无解，输出 $-1$。 
## 完整代码
没错就是这么简短。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long a,c;
		cin>>a>>c;
		if(a-c>=0/*a比c小肯定无解*/&& a/(a/c)==c/*是否满足条件*/)cout<<a;//有解，输出a。 
		else cout<<-1;//无解，输出-1。 
	}
	return 0;//完结撒花！ 
}
```

---

## 作者：Louis_lxy (赞：5)

找规律可知，答案要么是 $c$，要么是 $-1$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
long long a, b, c;

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lld %lld", &a, &c);
		if (c > a) { printf("-1\n"); continue; }
		b = c;
		if (a / (a / b) == b) printf("%lld\n", b);
		else puts("-1");
	}
	return 0;
}
```

然后考虑证明，显然当 $b=c$ 时， $m=1$。如果 $m\ne1$ 时显然让 $b=kc$。当 $b=kc$ 时，有 $\left\lfloor \frac{a}{n} \right\rfloor=kc$ 显然此时可以让 $n \gets n\times k$，因此此时 $c$ 也一定是答案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
long long a, b, c;

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lld %lld", &a, &c);
		if (c > a) { printf("-1\n"); continue; }
		b = c;
		if (a / (a / b) == b) printf("%lld\n", b);
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：Crsuh2er0 (赞：4)

数论入门题。

看到高斯函数，一个很自然的想法是列出带余除法式。
$$a = nb + r_1, 0 \le r_1 < n \ (1)$$ 

$$b = mc + r_2, 0 \le r_2 < m \ (2)$$

将 $(2)$ 式代入 $(1)$ 式得

$$a = nmc + nr_2  + r_1, 0 \le r_1 < n, 0 \le r_2 < m \ (3)$$

观察发现 $0 \le nr_2 + r_1 < nm$，于是 $(3)$ 式同样是一个带余除法式。

故 $nm = \lfloor \frac{a}{c} \rfloor$。

令 $p = nm, q = a - pc$，则 $p, q$ 已知。

又由 $(3)$ 式，

$$q = nr_2  + r_1, 0 \le r_1 < n, 0 \le r_2 < m$$

取 $n = 1$，有

$$m = p,r_1 = 0,r_2 = q,b = pc + q,a = b$$

此时有解的条件是 $r_2 < m$，即 $q < p$。

```
#include <bits/extc++.h>
using namespace std;
typedef long long ll;
ll a, c;

void solve() {
    cin >> a >> c;
    ll p = a / c, q = a - p * c, n = 1, m = p, b = p * c + q, a = q * b;
    cout << (q < p ? b : -1) << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}
```

---

## 作者：Indestructible (赞：2)

### 题意

给定正整数 $a,c$，求是否存在正整数 $n,m$，使正整数 $b=\lfloor\frac{a}{n}\rfloor$ 并有 $c=\lfloor\frac{b}{m}\rfloor$，存在则输出任意解，不存在输出 $-1$。

### 解法

首先，容易发现，$a<c$ 时一定无解，$a=c$ 时解为 $a$ 或 $c$。

将 $b=\lfloor\frac{a}{n}\rfloor,c=\lfloor\frac{b}{m}\rfloor$ 合并为 $c=\lfloor\frac{\lfloor\frac{a}{n}\rfloor}{m}\rfloor$，当 $m=1$ 时 $b=c$，转为计算是否存在 $c=\lfloor\frac{a}{n}\rfloor$。当 $\lfloor\frac{a}{c}\rfloor>a\bmod c$ 时，显然有 $n=\lfloor\frac{a}{c}\rfloor$，而 $\lfloor\frac{a}{c}\rfloor\le a\bmod c$ 时，仍取 $n=\lfloor\frac{a}{c}\rfloor$，则 $\lfloor\frac{a}{n}\rfloor$ 会大于给出的 $c$，此时无解。

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main()
{
	long long t, a, c;
	scanf("%lld", &t);
	while (t --)
	{
		scanf("%lld%lld", &a, &c);
		if (a < c) printf("-1\n");
		if (a == c) printf("%lld\n", a);
		if (a > c)
		{
			if (a / c > a % c) printf("%lld\n",c);
			else printf("-1\n");
		}
	}
	return 0;
}
```

---

## 作者：xixisuper (赞：2)

# P10782 【MX-J1-T2】『FLA - III』Ilumina 题解

最近在做莫比乌斯反演，解题技巧中有一个小结论正好能够用在这个题里，来写一下题解。

## 题解

形式化题目：

- 存在五个正整数 $n,m,a,b,c$，且已知 $b=\left\lfloor \frac{a}{n} \right\rfloor , c=\left\lfloor \frac{b}{m} \right\rfloor$。
- 给定一组 $a,c$，询问是否存在合法的 $b$，若存在则输出任意一个合法答案即可，否则输出 `-1`。

根据题意，我们能够得出如下等式：

$$c=\left\lfloor \frac{b}{m} \right\rfloor=\left\lfloor \frac{\left\lfloor \frac{a}{n} \right\rfloor}{m} \right\rfloor$$

其实对于这个式子，我们有一个引理：

$$\forall a,b,c \in\Z^+,\left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor=\left\lfloor\frac{a}{bc}\right\rfloor$$

证明如下：

我们记 $\{x\}=x-\left\lfloor x \right\rfloor$，于是有：

$$
\begin{aligned}
\left\lfloor\frac{a}{bc}\right\rfloor&=\left\lfloor\frac{\frac{a}{b}}{c}\right\rfloor\\
&=\left\lfloor\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}+\frac{\left\{\frac{a}{b}\right\}}{c}\right\rfloor\\
&=\left\lfloor\left\lfloor\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor+\left\{\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\}+\frac{\left\{\frac{a}{b}\right\}}{c}\right\rfloor
\end{aligned}
$$

单独看后面的 $\left\{\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\}+\frac{\left\{\frac{a}{b}\right\}}{c}$ 这一部分，不难发现：

$$\left\{\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\}\le\frac{c-1}{c}$$
$$\frac{\left\{\frac{a}{b}\right\}}{c}<\frac{1}{c}$$

$$\therefore \left\{\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\}+\frac{\left\{\frac{a}{b}\right\}}{c}<1$$

而前面的 $\left\lfloor\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor$ 又是整数，所以有：

$$\left\lfloor\frac{a}{bc}\right\rfloor=\left\lfloor\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor$$

证毕。

回到本题，则原等式可等效看为是：

$$c=\left\lfloor\frac{a}{nm}\right\rfloor$$

所以说 $a,c$ 之间仅与 $n\times m$ 有关，不妨设 $m=1$，则有：

$$c=\left\lfloor\frac{a}{n}\right\rfloor=b$$

结束了吗？莫慌，我们还需要检查一番：

$$\because c=\left\lfloor\frac{a}{n}\right\rfloor\le\frac{a}{n}$$
$$\therefore c\times n\le a$$
$$\therefore n=\left\lfloor\frac{a}{c}\right\rfloor\le\frac{a}{c}$$

我们把 $n$ 求出来，然后看看 $c$ 是否与 $\left\lfloor\frac{a}{n}\right\rfloor$ 相等，如果相等，直接输出 $c$ 就好了，否则输出 `-1`。

## 代码

感觉这个题如果直接靠注意力的话还是有点难度的，评橙是不是有一点点低（个人意见，也有可能是笔者太菜）？

```cpp
#include <iostream>
#define ll long long
using namespace std;
ll T,a,c; 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>a>>c;
		ll n=a/c;
		if(n&&c==a/n) cout<<c<<"\n";
		else cout<<"-1\n";
	}
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

这是一道简单题。

我们不妨设 $n = 1$，因为这样可以让 $b$ 尽量大，从而找出一个合法的解。

那么问题转换为：是否存在一个 $m$ 满足 $c = \lfloor \frac{a}{m} \rfloor$。

我们可以采用二分查找的方法，在 $(\lfloor \frac{a}{c + 1} \rfloor, \lfloor \frac{a}{c} \rfloor]$ 这个区间进行查找即可。

单次询问时间复杂度 $O(\log n)$。

参考代码如下：

```cpp
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#define ll long long
#define writes(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n');
static char buf[100000], * pa(buf), * pb(buf);
int st[114], top;
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
void debug(auto st, auto ed, bool endline) {
	for (auto it = st; it != ed; ++it) {
		cout << *it << " ";
	}
	if (endline) cout << '\n';
}
template <typename T> void read(T& x) {
	T t = 0, sgn = 1;
	char ch = gc;
	while (!isdigit(ch)) {
		if (ch == '-') sgn = -sgn;
		ch = gc;
	}
	while (isdigit(ch)) {
		t = (t << 3) + (t << 1) + (ch ^ 48);
		ch = gc;
	}
	x = sgn * t;
}
template <typename T, typename ...Args> void read(T& tmp, Args &...tmps) {
	read(tmp); read(tmps...);
}
template <typename T> void write(T x) {
	if (x < 0) putchar('-'), x = -x;
	top = 0;
	while (x) {
		st[++top] = x % 10;
		x /= 10;
	}
	do {
		putchar(st[top--] + '0');
	} while (top > 0);
}
template <typename T, typename ...Args> void write(T& tmp, Args &...tmps) {
	writes(tmp);
	writes(tmps...);
}
template <typename T> T rand(T l, T r) {
	return rnd() % (r - l + 1) + l;
}
int main() {
	// cin.tie(0)->sync_with_stdio(0);
	// cout.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--) {
		ll a, c;
		read(a, c);
		ll l = a / (c + 1) + 1, r = a / c;
		bool ok = 0;
		while (l <= r) {
			ll mid = l + r >> 1;
			if (a / mid == c) {
				ok = 1;
				writeln(a);
				break;
			}
			if (a / mid > c) {
				l = mid + 1;
			}
			else r = mid - 1;
		}
		if (!ok) puts("-1");
	}
}
```

---

## 作者：M4rkSELby (赞：1)

简易数学题。

我们先尝试把 $b$ 的式子代入 $c$ 的式子，可得 $c=\left\lfloor \frac{\left\lfloor \frac{a}{n} \right\rfloor}{m} \right\rfloor$，尝试化简这个式子，得 $c=\left\lfloor \frac{a}{n\times m}\right\rfloor$。（暂时不要在意向下取整，后面会判。）

题目给出了 $a$ 与 $c$，那么我们来分讨一下：因为要求这些数都是正整数，所以当 $a<c$ 时显然无解；否则我们求出 $n\times m$ 的值，为 $\left\lfloor \frac{a}{c}\right\rfloor$。因为几重有向下取整，这个值仍不能保证正确。因此我们再尝试用 $a$ 除以这个值，向下取整后若不能等于 $c$，则该值也是有问题的。此时也无解。排除无解的情况后 $b$ 的值就可以直接计算了，就是 $\frac{a}{n\times m}$。为什么我们可以直接用乘积呢？因为我们可以将 $m$ 设为 $1$，此时的 $n\times m$ 就是 $n$。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
#define mod 1000000007
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=(jya<<1)+(jya<<3)+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
il int max(int x,int y){return x>=y?x:y;}
il int min(int x,int y){return x<=y?x:y;}
const int JYAAKIOI=1145141919810;
int T,a,c,b,n;
signed main(){
	//freopen("jytwcsnm.in","r",stdin);
	//freopen("jytwcsnm.out","w",stdout);
	T=rd();
	while(T--){
		a=rd();c=rd();
		if(a<c){
			wr(-1);
			putchar('\n');
			continue;
		}
		n=a/c;
		if(a/n!=c){
			wr(-1);
			putchar('\n');
			continue;
		}
		wr(a/n);
		putchar('\n');
	}
    return 0;
}
```

---

## 作者：chenlongli (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10782)
### 思路
对于 $b=\lfloor\frac{a}{n}\rfloor,c=\lfloor\frac{b}{m}\rfloor$ 这两个式子，我们可以把它变成 $c=\lfloor\frac{a}{nm}\rfloor$，我们可以把 $nm$ 转为一个数 $x$，那么就需要找到一个 $x$，使得 $c=\lfloor\frac{a}{x}\rfloor$，我们可以再将这个式子转为 $x=\lfloor\frac{a}{c}\rfloor$，那么我们就可以判断这个 $x$ 是否存在，如果不存在，返回无解，如果 $x$ 存在，既然 $c=\lfloor\frac{a}{x}\rfloor$，那么我们就可以把 $b$ 设为 $c$，这样就是一组满足条件的解法。 
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	long long n,k;
	for (int i=0;i<t;i++)
	{
		cin>>n>>k;
		if (n>=k&&n/(n/k)==k)
		{
			cout<<k<<endl;
		}
		else
		{
			cout<<-1<<endl;
		}
	}
}
```

---

## 作者：stylus (赞：1)

# 思路：
推个柿子：
$$\because b=\left \lfloor \tfrac{a}{n} \right \rfloor \therefore b\le\tfrac{a}{n}<b+1$$
$$\because c=\left \lfloor \tfrac{b}{m} \right \rfloor \therefore c\le\tfrac{b}{m}<c+1$$
$$\therefore c\le\tfrac{b}{m}\le\tfrac{\tfrac{a}{n}}{m}=\tfrac{a}{n\times m}<b+1$$
$$\therefore \tfrac{a}{c}=n\times m$$
$$\therefore \tfrac{a}{\tfrac{a}{c}}=\tfrac{b}{m}$$
我们可以令 $m=1，\therefore \tfrac{b}{m}=b$，为什么呢？因为 $m$ 可以为任意正整数
## 代码君：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a,c;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>c;
        if(a<c)cout<<"-1\n";
		else if(a/(a/c)>=c&&a/(a/c)<c+1)cout<<a/(a/c)<<endl;//判断b合不合法
		else cout<<"-1\n";
	}
	return 0;
}
```

---

## 作者：哈哈人生 (赞：0)

# 前言
本题数学性质比较好推，确实是上位橙左右。

# 思路
有一个数学上的小小的前置知识，就是 $\left\lfloor\frac{\left\lfloor\frac{a}{n}\right\rfloor}{m}\right\rfloor=\left\lfloor\frac{a}{n\times m}\right\rfloor$，具体证明可以去 [OI Wiki 数论相关定理介绍](https://oi-wiki.org/math/number-theory/basic/)。

那么问题就转化为了给定 $a$ 和 $\left\lfloor\frac{a}{n\times m}\right\rfloor$，求 $\left\lfloor\frac{a}{n}\right\rfloor$ 或判定无解。我们思考在什么情况下对于一个正整数 $a$，无正整数 $x=n\times m$ 满足 $\left\lfloor\frac{a}{x}\right\rfloor=c$。我们把这个式子变换一下，则 $x$ 可能的取值有且仅有 $\left\lfloor\frac{a}{c}\right\rfloor$ 和 $\left\lfloor\frac{a}{c}\right\rfloor+1$（可以感性理解为向下取整与原数误差不超过一），而我们把这两个数再反过来带入 $\left\lfloor\frac{a}{x}\right\rfloor$ 看它的值是否和 $c$ 相等即可，如果有一项相等这样就求出了 $x$ 的值，否则无解。

现在我们求出了 $x$ 的一个值，那么我们要输出的就是一个正整数 $b=\left\lfloor\frac{a}{n}\right\rfloor$，其中 $n$ 是正整数且乘上另一个正整数 $m$ 等于 $x$，这其实就是 $x$ 的一个因数，我们此时 $n$ 取 $1$ 即可（因为 $1$ 肯定是任意正整数的因数），输出 $b=\left\lfloor\frac{a}{1}\right\rfloor=a$ 此题就做完了。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a,c;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>a>>c;
		if(a<c)cout<<-1<<"\n";
		else{
			int x=a/c,y=a/c+1;
			if(a/x==c||a/y==c){
				cout<<a<<"\n";
			}
			else cout<<-1<<"\n";
		}
	} 
	return 0;
}
```
点个赞吧。

---

## 作者：SnapYust (赞：0)

# 更好的阅读感受

[这里](https://www.cnblogs.com/snapyust/p/18301962)

# 题目传送门

[【MX-J1-T2】『FLA - III』Ilumina](https://www.luogu.com.cn/problem/P10782)

# 思路

硬导题。

因为 $c=\lfloor \frac{b}{m}\rfloor$，那么 $b$ 一定可以表示为 $c\times m+x$，其中 $0\le x\le m-1$。

又因为 $b=\lfloor \frac{a}{n}\rfloor$，那么 $a$ 一定可以表示为 $b\times n+y$，其中 $0\le y\le n-1$。

由上可以得出：

$$b=cm+x$$

$$a=bn+y$$

所以：

$$b=\frac{a-y}{n}$$

所以：

$$\frac{a-y}{n}=cm+x$$

$$\therefore a=cmn+nx+y$$

由于 $a,c,m,n,x,y\in N$ 且 $m$ 和 $n$ 不为 $0$，所以 $a\ge c$。

考虑分类讨论：

* $a<c$ 时：因为若有解，那么 $a$ 一定不小于 $c$，所以此时无解。

* $a=c$ 时：很容易可以得出当 $m=n=1$ 时，一定满足 $a=b=c$，所以一个合法 $b$ 的值就等于 $a$ 和 $c$。

* $a>c$ 时：重新考虑上述方程，即 $a=cmn+nx+y$：因为 $x\le m-1,y\le n-1$，所以 $nx+y\le n(m-1)+n-1$，所以 $nx+y\le mn-1$，所以再设 $z=nx+y$，所以 $0\le z\le mn-1$，代入方程，可得： $a=cmn+z$，再令 $mn=f$，所以 $a=cf+z$，其中 $0\le z\le f-1$。此时我们只需要考虑 $f$ 存不存在正整数解即可。

（判断 $f$ 有没有正整数解很简单，用贪心的思想，我们可以要求 $f$ 尽可能大，也就是让 $f=\lfloor\frac{a}{c}\rfloor$，然后判断 $a-cf$ 与 $f$ 的大小即可，具体见代码。）

# 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--){
		int a,c;cin>>a>>c;
		if(a==c)cout<<a<<endl;
		else if(a<c)cout<<-1<<endl;
		else{
			int f=a/c;int u=a-c*f;
			if(u>=f)cout<<-1<<endl;
			else cout<<c<<endl;
		}
	}
	return 0;
}
```

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10782)

有一个显然的做法。

令 $c=\lfloor\frac{b}{m}\rfloor$ 中 $m=1$，则 $b=c$；则 $c=\lfloor\frac{a}{n}\rfloor$。

显然此时 $a<c$ 则无 $n$ 的正整数解，也就没有 $b$ 的正整数解。

对于 $a\ge c$ 的情况，我们考虑用二分求出 $n$ 的正整数解。如果二分到 $c=\lfloor\frac{a}{mid}\rfloor$ 的情况，则答案就为 $c$（因为 $b=c$），否则继续二分即可。若没有二分出任何答案则报告无解即可。

```cpp
signed main()
{
	int t;
	rd(t);
	while(t--)
	{
		int a,c;
		rd(a,c);
		if(a<c)
		{
			wtl(-1);
			continue;
		}
		int l=1,r=1e18;
		int ans=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(a/mid==c)
			{
				ans=c;
				break;
			}
			else if(a/mid<c)
			{
				r=mid-1;
			}
			else
			{
				l=mid+1;
			}
		}
		wtl(ans);
	}
	return 0;
}
```

---

## 作者：Register_int (赞：0)

写这题的起因是有人在赛时 uoj 群里问，后面忘了。

首先我们有：

$$c=\left\lfloor\frac{\left\lfloor\frac am\right\rfloor}n\right\rfloor=\left\lfloor\frac a{mn}\right\rfloor$$

那么不妨 $m=1$，只要存在 $n$ 使 $\left\lfloor\frac an\right\rfloor=c$ 即可，可构造 $b=a$。

直接解可得到 $n=\left\lfloor\frac ac\right\rfloor$。代进去得到的如果不是 $c$ 则无解，否则输出即可。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 10;

int T; ll a, c;

int main() {
	for (scanf("%d", &T); T--;) {
		scanf("%lld%lld", &a, &c);
	// c = a/nm
		if (c > a || c != a / (a / c)) puts("-1");
		else printf("%lld\n", a);	
	}
}
```

---

## 作者：JYX0924 (赞：0)

首先，考虑暴力枚举 $n$ 的大小，然后枚举 $m$ 的大小，这样就会超时。

所以，我们要考虑优化。先枚举 $n$ 的大小，然后算出 $b$，接着算出 $m$ 的取值范围：$b\div c-1 \le m \le b\div c+1$，这样时间复杂度就会大大优化。

但是这样还是过不了。

我们不妨设 $n=1$，则 $m$ 的值就可以算出来。算出后判断一下答案即可。

下面是我的 AC 代码。

```c
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll T,x,y;
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>x>>y;
		if(x<y) cout<<"-1\n";
		else {ll t=x/y; if(x/t==y) cout<<x<<"\n"; else cout<<"-1\n";}
	}
	return 0;
}
```
谢谢大家！！！

---

## 作者：SunsetVoice (赞：0)

评价：秒过 $1,2$，逆天 $3$。

考虑推式子。

$$\because b=\lfloor \frac{a}{n} \rfloor $$
$$\therefore c= \lfloor \frac{b}{m} \rfloor=\lfloor \frac{\lfloor \frac{a}{n} \rfloor}{m} \rfloor$$

注意到显然的结论：$\lfloor \frac{\lfloor \frac{a}{n} \rfloor}{m} \rfloor=\lfloor \frac{a} {n\times m} \rfloor$

此时，$c$ 的值只和 $a,n\times m$ 相关。当 $m=1$ 时，可以合法的获得一个 $n$ 值。

于是判断是否有解，使用 $\frac{a}{c}$ 上下一判断，注意 $a=0$ 特判。

答案为 $-1$ 或 $c$。

---

## 作者：Lujoqera (赞：0)

### 思路：
我们先把 $b$ 的式子带入 $c$ 的式子，可得 $c=\lfloor\frac{\lfloor\frac{a}{n}\rfloor}{m}\rfloor$ 即 $c=\lfloor\frac{a}{nm}\rfloor$。我们已知 $a$，那么我们可知 $m \times n$ 的结果，需带进去检测，若不是则输出 $-1$，若可行，令 $m=1$，即可知道 $b=c$, 输出 $c$ 即可。

### 代码：
```
#include <bits/stdc++.h>
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#define int long long
#define endl "\n"
#define ull unsigned long long
#define write(n,x) cout<<setprecision(n)<<fixed<<x<<endl
typedef long long LL;
using namespace std;

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int a,c;
		cin>>a>>c;
		if(a<c)
		{
			cout<<"-1"<<endl;
			continue;
		}
		int x=a/c;
		if(a/x==c)
		{
			cout<<a/x<<endl;
		}
		else
		{
			cout<<"-1"<<endl;
		}
	}
	return 0;
}
/*
*/




                             
```

---

## 作者：sxq9 (赞：0)

## 思路

数学题。

我们观察一下式子，易知：$c=\left\lfloor \frac{\left\lfloor \frac{a}{n} \right\rfloor}{m}\right\rfloor$。

可以证明，$\left\lfloor \frac{\left\lfloor \frac{a}{n} \right\rfloor}{m}\right\rfloor=\left\lfloor \frac{a}{nm} \right\rfloor$。

所以，只要看存不存在这样的 $nm$ 即可。

如果存在 $nm$ 为整数，那么我们可知，$nm$ 一定可以拆分成 $1\times nm$，即令 $n=1$。

所以如果有解，输出 $a$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long a,c;
		scanf("%lld%lld",&a,&c);
		long long nm=a/c;
		if(nm==0){
			printf("-1\n");
		}
		else if(a/nm!=c){
			printf("-1\n");
		}
		else{
			printf("%lld\n",a);
		}
	}
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

### 思路

我们可以令答案 $b=c$。

先判断无解：

- $a<c$ 时，显然无解。
- $\lfloor\dfrac{a}{\lfloor\frac{a}{c}\rfloor}\rfloor\neq c$ 时，无解。

证明（口胡）一下下面的结论：

$\lfloor\dfrac{a}{c}\rfloor$ 是 $a$ 除以 $c$ 的整数值。如果 $a$ 整除以这个数都无法达到 $b$（也就是 $c$），那么更没有别的数让 $a$ 整除以这个数得到 $b$ 了，因为起码这个数理论可行（$\dfrac{a}{\frac{a}{c}}=c$），而其它数连理论都做不到。

那可能 $b>c$ 吗？我们还是要看题目中给的条件。如果连上面的要求都做不到，$b>c$ 时需要的要求更多，更做不到。

所以这道题就做完了。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int T;
long long a,b,ans;
int main(){
	cin>>T;
	while(T--){
		cin>>a>>b;
		ans=b;
		long long g=a/b;
		if(a<b)cout<<-1<<endl;
		else if(a/g!=b)cout<<-1<<endl;
		else cout<<b<<endl;
	}
	return 0;
}
```

---

## 作者：tin_ingot (赞：0)

根据题目中的两个式子可得 $ c\times m \le b \le \frac{a}{n}$，则 $ c\le b \le a$。

发现 $b$ 是在 $[a,c]$ 这个区间范围内的，由于 $a,c$ 最大有 $10^{18}$ ，$O(n)$ 做法暴力枚举 $b$ 显然行不通，考虑二分答案。

每次二分一个 $b$，如果 $b$ 符合题目条件就可以直接输出了。如果 $b<c$ ，说明枚举的 $b$ 小了；如果 $b>a$ ，说明枚举的 $b$ 大了。

接着考虑如何判断 $b$ 是否符合题目条件，将题目中的式子变形可得 $n\le \frac{a}{b}$，只有 $n$ 越接近 $\frac{a}{b}$ 时 $b$ 才可能满足题目的第一个条件，即使 $n\approx\frac{a}{b}$；同理，根据第二个式子可得应使 $m\approx\frac{b}{c}$ 才可能符合条件。由于题目中使用了“向下取整”，以上式子中使用了“约等于”符号，算出的 $n,m$ 可能会有一点误差，需要逐个验证。

```cpp
#include <iostream>
using ll = long long;
using namespace std;
bool check(ll b,ll a,ll c) {
	ll n=a/b,m=b/c; //n和m是一个估计值，可能有误差
	bool f1=0,f2=0; //是否满足题目要求的两个条件
	for(int k=-1;k<=1;k++) { //k为误差值
		if(k+n==0) continue; //除数不能为0
		if(a/(k+n)==b) f1=1; //满足第一个条件
	}
	for(int k=-1;k<=1;k++) {
		if(k+m==0) continue;
		if(b/(k+m)==c) f2=1; //满足第二个条件
	}
	return f1&&f2; //两个条件都满足
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		ll a,c;
		cin >> a >> c;
		ll l=min(a,c),r=max(a,c); //取较小值作为l，较大值作为r
		bool f=0;
		while (l<=r) {
			ll b=(l+r)>>1;
			if(check(b,a,c)) { //b满足要求
				f=1;
				cout << b << endl;
				break;
			} else if(c>b) { //b小了
				l=b+1;
			} else { //b大了，比如b>a
				r=b-1;
			}
		}
		if(!f) cout<<"-1\n";
	}
	return 0;
}
```

---

## 作者：wei2013 (赞：0)

## 思路：
考虑若 $b=c$，则 $m=1$，显然有解，现在问题就变成了 $b$ 是否能变成 $c$，因 $b=\frac{a}{n}$，所以 $n=\frac{a}{b}$，因为是整除所以依旧有可能造成偏差，如：$\lfloor \frac{23}{8} \rfloor=2$，$\lfloor \frac{23}{2} \rfloor=11$，$11\not =8$，所以输出 $-1$，所以 $\frac{a}{\frac{a}{c}}=c$，就一定有解。
## code:
```cpp
#include <iostream>
using namespace std;
#define int long long
signed main() {
    int t;
    cin>>t;
   	while(t--){
	   	int a,c;
        cin>>a>>c;
        if(a/c!=0/*除数不能为0*/ && a/(a/c)==c){
        	cout<<c<<endl;
		}else{
			cout<<-1<<endl;
		}
    }
    return 0;
}
```

---

