# Hacking Numbers (Medium Version)

## 题目描述

这是该问题的中等版本。在此版本中，你最多可以发送 $\mathbf{4}$ 条指令。只有在解决所有版本的问题后才能进行 hack。

这是一个交互式问题。

欢迎，决斗者们！在这个交互式挑战中，存在一个未知整数 $x$（$1 \le x \le 10^9$）。你需要通过利用"Mathmech"怪兽的力量，将其变为输入中给定的整数 $n$。你可以发送以下指令之一：

| 指令          | 约束条件                          | 结果                  | 更新操作                 | 裁判响应 |
|---------------|-----------------------------------|-----------------------|--------------------------|----------|
| "add $y$"     | $-10^{18} \le y \le 10^{18}$      | $\mathrm{res} = x + y$ | 若 $1 \le \mathrm{res} \le 10^{18}$，则 $x \leftarrow \mathrm{res}$ | "1"      |
|               |                                   |                       | 否则 $x \leftarrow x$    | "0"      |
| "mul $y$"     | $1 \le y \le 10^{18}$             | $\mathrm{res} = x \cdot y$ | 若 $1 \le \mathrm{res} \le 10^{18}$，则 $x \leftarrow \mathrm{res}$ | "1"      |
|               |                                   |                       | 否则 $x \leftarrow x$    | "0"      |
| "div $y$"     | $1 \le y \le 10^{18}$             | $\mathrm{res} = x/y$  | 若 $y$ 整除 $x$，则 $x \leftarrow \mathrm{res}$ | "1"      |
|               |                                   |                       | 否则 $x \leftarrow x$    | "0"      |
| "digit"       | —                                 | $\mathrm{res} = S(x)$ $^{\text{∗}}$ | 总是 $x \leftarrow \mathrm{res}$ | "1"      |

你需要用最多 $\mathbf{4}$ 条指令使 $x$ 等于 $n$。

$^{\text{∗}}$ $S(n)$ 是一个函数，返回非负整数 $n$ 的各位数字之和。例如，$S(123) = 1 + 2 + 3 = 6$。

## 说明/提示

**解释**  
$\texttt{2}$：共有 2 个测试用例。  
$\texttt{100}$：第一个测试用例中，未知整数 $x = 9$，目标值 $n = 100$。  
$\texttt{add -10}$ $\texttt{0}$：指令"add -10"返回"0"，因为 $9 + (-10) \le 0$，$x$ 保持为 9。  
$\texttt{add 1}$ $\texttt{1}$：指令"add 1"成功，$x$ 变为 10。  
$\texttt{mul 10}$ $\texttt{1}$：指令"mul 10"成功，$x$ 变为 100。  
$\texttt{!}$ $\texttt{1}$：确认 $x = n$。  
$\texttt{5}$：第二个测试用例中，$x = 1234$，$n = 5$。  
$\texttt{digit}$ $\texttt{1}$：$x$ 变为各位数字之和 10。  
$\texttt{div 2}$ $\texttt{1}$：指令"div 2"成功，$x$ 变为 5。  
$\texttt{!}$ $\texttt{1}$：确认 $x = n$。  

注意示例中的空行仅为清晰展示，实际交互中不会出现。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
100

0

1

1

1

5

1

1

1```

### 输出

```
add -10

add 1

mul 10

!

digit

div 2

!```

# 题解

## 作者：zhujiajun2013 (赞：2)

第一次通过交互题。

### 题意：

我们需要通过最多 $4$ 条指令将未知整数 $x$ 转变为给定的目标整数 $n$。可用的指令包括加法、乘法、除法和数字求和操作。

### 思路：
这个题目的思路其实很巧妙，就像玩一个数字魔术，分四步就能把任意数字变成我们想要的 $n$。咱们一步步来看：

**先来个"瘦身"操作**

不管 $x$ 最开始多大，先让它变成各位数字相加的和，比如 $x$ 是 $1234 \to 1+2+3+4=10 \to 1+0=1$ 这一步保证 $x$ 变成1到9之间的单个数字。

**然后放大招**

把现在的个位数乘以 $99$，比如 $x$ 是 $5 \to 5×99=495$，重点来了：所有 $99$ 的倍数$(99,198,...,891)$的数字和都是 $18$！
如：$495 \to 4+9+5=18$。

**再来一次"瘦身"**

现在 $x$ 是 $495$ 这样的数，再求数字和，必定得到 $18$（这就是数学的妙处）。

**最后微调**

现在 $x=18$，要变成 $n$，直接加上差值就行，
比如 $n=100 \to +82(100-18=82)$。

轻松搞定！
### AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,t;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<"digit"<<endl;cin>>x;
		cout<<"mul 99"<<endl;cin>>x;
		cout<<"digit"<<endl;cin>>x;
		cout<<"add "<<n-18<<endl;cin>>x;
		cout<<"!"<<endl;cin>>x;
	}
	return 0;
}
```

---

## 作者：CaiZi (赞：2)

有大神拿这题做儿童节游园会小游戏，所以写篇题解。

首先除法是肯定不能直接用的，你首先需要尝试让 $x$ 变成一定为某个数的倍数。于是考虑小学数学经典结论：如果对于一个数 $x$，若 $x$ 为 $9$ 的倍数，则 $S(x)$ 也为 $9$ 的倍数。

于是我们可以尝试一下 $S(9x)$，这个数是 $9$ 的倍数，且不难发现其 $<100$。

然后就简单了，因为 $S(9x)$ 为 $9$ 的倍数，所以 $S(S(9x))$ 为 $9$ 的倍数，显然只能为 $9$。

除法是没有用的，但是确实对思路有帮助。

最终答案：
```cpp
cout<<"mul 9\n";
cout<<"digit\n";
cout<<"digit\n";
cout<<"add "<<n-9<<"\n";
```

---

## 作者：MattL (赞：2)

如果你不会做，先别急着看下面的题解，可以先看看官方给的这些 tips：

1. 第一个操作不是 `digit`。
2. 第一个操作是 `mul`。
3. `digit` 操作和 `mul` 操作结合起来很强大！试试找出 一个数将它们结合起来。
4. 回忆一下我们中学就学过的（官方题解是这么说的）知识：一个数能被 $9$ 整除当且仅当它的数位和能被 $9$ 整除。
---

对于这个知识的证明如下：

对于一个数 $k=\overline{a_na_{n-1}a_{n-2}\cdots a_1}$，我们把它展开：

$$k=10^0\times a_1+10^1\times a_2+\cdots 10^{n-1}\times a_n$$

由于 $10^x=9\times \overline{11\cdots1}+1$（其中 $\overline{11\cdots1}$ 有 $x$ 个 $1$，$x$ 是非负整数），即：

$$10^x\equiv1\pmod9$$

$$\therefore k \equiv a_1+a_2+a_3+\cdots+a_n= S(n)\pmod9$$

这是模 $9$ 意义上的，所以不难想到第一步是 `mul 9`，操作后未知数变为 $9\sim 9\times10^{18}$ 中 $9$ 的倍数。

进行 `digit` 操作，操作后未知数变为 $9\sim 81$ 中 $9$ 的倍数。

再进行 `digit` 操作，操作后未知数变为 $9$。

最后再进行 `add n-9` 即可。

---

code：

```cpp
int n,tmp;
void solve(){
	cin>>n;
	cout<<"mul 9"<<endl;cin>>tmp;
	cout<<"digit"<<endl;cin>>tmp;
	cout<<"digit"<<endl;cin>>tmp;
	cout<<"add "<<n-9<<endl;cin>>tmp;
	cout<<"!"<<endl;cin>>tmp;
}
````

---

## 作者：StarTwinkleTwinkle (赞：2)

还是那句话：除啥用没有。

考虑对未知整数进行一次 digit 操作，则其一定在 $1$ 到 $81$ 之间。

似乎然后就寸步难行了，那我们考虑乘法，让它乘上一个数使其位数和为一个定值。求这个数的代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int st;
inline int digit(int x)
{
	int ans=0;
	while(x)ans+=x%10,x/=10;
	return ans;
}
signed main(){
	for(int i=1;;++i){
		st=digit(1*i);
		for(int j=2;j<=81;++j)
		{
			if(st!=digit(j*i))goto S;
		}
		cout<<i;
		break;
		S:;
	}
	return 0;
}
```

最终结果：$99$。

故再让其乘上 $99$，然后进行一次 digit 操作，其结果定为 $18$，最终加上 $n-18$ 即可。如上，我们共进行了 $4$ 次操作，符合题目要求。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,T;
inline void solve()
{
	cin>>n;
	
	cout<<"digit"<<endl;
	cin>>x;
	
	cout<<"mul 99"<<endl;
	cin>>x;
	
	cout<<"digit"<<endl;
	cin>>x;
	
	cout<<"add "<<n-18<<endl;
	cin>>x;
	
	cout<<"!"<<endl;
	cin>>x;
}
signed main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：_mi_ka_ (赞：0)

[题目传送门](https://codeforces.com/contest/2109/problem/C2)

## 题目大意

交互题。$T$ 组数据，每组给定一个整数 $n(1\le n\le 10^9)$，评测机中有一个隐藏的整数 $x(1\le x\le10^9)$。你可以对这个隐藏的 $x$ 做出以下四种操作若干次（这里 C2 这道题要求**最多 $4$ 次**）将隐藏的 $x$ 变成 $n$。

1. `add y` 表示将 $x$ 增加 $y(-10^{18}\le y\le 10^{18})$；
2. `mul y` 表示将 $x$ 乘上 $y(1\le y\le 10^{18})$；
3. `div y` 表示将 $x$ **除以** $y(1\le y\le 10^{18})$；
4. `digit` 表示将 $x$ 的十进制各位数字相加，赋值给 $x$；

在以上的四种操作中，如果假设 $x$ 操作后得到的数为 $res$，那么当且仅当 $1\le res\le 10^{18}$ 且 $res$ **为整数时**此次操作有效，交互机会返回 $1$，否则这次操作无效，$x$ 不做改变，交互机返回 $0$。

在确定 $x=n$ 时给交互机一个指令 `!` 结束这组数据，这时交互机会返回一个值 $1$（正确）或者 $-1$（错误）。

## 解题思路

一种思路为可以将 $x$ 经过若干次操作后使得 $x$ 变成我们可以确定的数，然后再经过最多一次操作使得 $x$ 变为 $n$。这里我们需要保留最后一次将 $x$ 由我们已知的数字变为 $n$ 的过程，那么题意就变成了：**最多 $3$ 次操作使得 $x$ 变成一个确定的数**。

如何去选取这个确定的数呢？在 C1 中我们选取数字 $1$ 作为这个数字，但是缩小范围的过程过于繁琐，可不可以将这个数缩小成一个更大一点的确定的数呢？这里就需要用到我们小学数学中学到的一个结论：任何能被 $9$ 整除的数，其十进制各位数字之和为 $9$ 的倍数。该定理过于简单，这里不做证明。这里我们对 $x$ 先乘一个 $9$，在去观察是否能够通过两次操作使得 $x$ 变成 $9$。即：

1. `mul 9` 得到 $1\le x\le 10^9\to 9\le x\le 9\times10^9$；
2. `digit` 得到 $9\le x\le 9\times 10^9\to 9\le x\le 81$ 且由结论得 $9\mid x$。至于这里为什么还是 $81$，我们很容易想到这里能取到的最大的数字 $8999999999$，它的各位之和是 $89$，所以可以写出 $1\le x\le 89$，但是由于 $9\mid x$，自然引出结论 $9\le x\le 81$；
3. 考虑 $9$ 到 $81$ 之间的所有 $9$ 的倍数，它的各位之和为 $9$。于是再进行一次 `digit` 操作得到 $9\le x\le 81\to x=9$。

最后进行一次操作 `add n-9` 即可得到数字 $n$。这里还是有一个细节就是当 $n=9$ 时这一步操作不合法，所以需要特判一下。

单次时间复杂度 $O(1)$。

**不要忘记每次输出后清空缓存区哦**。

## AC Code
这里只放主函数
```cpp
signed main()
{
	int T=re();
	while(T--)
	{
		int n=re();
		puts("mul 9");
		cout.flush();
		int op=re();
		puts("digit");
		cout.flush();
		op=re();
		puts("digit");
		cout.flush();
		op=re();
		if(n!=9)
		{
			printf("add %d\n",n-9);
			cout.flush();
			op=re();
		}
		puts("!");
		cout.flush();
		op=re();
	}
	return 0;
}
```

---

## 作者：AstaVenti_ (赞：0)

本题与 CF2109C1 的区别仅在操作次数。

小学老师告诉我们：如果 $x\mid9$ ，那么 $S(x)\mid9$。因此 $S(S(x))\mid 9$。

进一步打表还可以发现，在题目的范围内，如果 $x\mid9$ ，那么 $S(S(x))=9$。

于是我们就可以先将这个数 $\times 9$（即 `mul 9`），然后通过两遍 `digit` 操作将其变成 $9$，再进行一次 `add n-9` 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n;
bool qry(ll t){
	cout<<"add "<<t<<endl;
	ll fh;
	cin>>fh;
	return fh;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		ll fh;
		cout<<"mul 9"<<endl;cin>>fh;
		cout<<"digit"<<endl;cin>>fh;
		cout<<"digit"<<endl;cin>>fh;
		qry(n-9);
		cout<<"!"<<endl;
		cin>>fh;
	}
}

```

---

## 作者：Scean_Tong (赞：0)

## Hacking Number 题解

### Problem
给定一个 $n$，有一个不知道的 $x$，你要通过加，乘，除，变成 $S(n)$ 的方式把这个数变成 $n$。

$S(n)$ 为 $n$ 的数位之和，如果除完变成分数，加或乘完变成 $0$ 或负数，不会改变 $x$。

### Solution2
第 $2$ 题，使用 $4$ 步操作变成 $n$。

由于我们做完 C1 了，所以只用加和变成 $S(n)$ 肯定是不够的。

所以考虑使用乘法。

引理：$S(9x)$ 一定为 $9$ 的倍数。

证明：有经典结论 $S(x)\equiv x\pmod 9$，另外还有 $10\equiv 1\pmod 9$。所以 $S(9x) \equiv 9 \times x \pmod 9$，$x$ 为正整数，证毕。

所以先乘上 $9$，再变成数位之和，现在的 $x$ 一定满足 $x \in \left\{ 9,18,27,36,45,54,63,72,81 \right\}$，再变成数位之和一定是 $9$，再加上 $n-9$ 即可。

一共 $4$ 步，符合 C2 题意。

```cpp
#include <bits/stdc++.h>
#define int long long
int T, n;
inline void solve(){
	int op;
	std::cin >> n;
	std::cout << "mul 9" << std::endl;
	std::cin >> op;
	std::cout << "digit" << std::endl;
	std::cin >> op;
	std::cout << "digit" << std::endl;
	std::cin >> op;
	std::cout << "add " << n - 9 << std::endl;
	std::cin >> op;
	std::cout << "! " << std::endl;
	std::cin >> op;
} 

int32_t main(){
	std::cin.tie(nullptr) -> std::ios::sync_with_stdio(false);
	std::cin >> T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

