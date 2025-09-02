# 「EZEC-7」Erinnerung

## 题目描述

小 Y 和小 Z 都是生活在 Arcaea Offline 的精灵。小 Y 有无数片落叶，其中第 $i$ 片落叶的价值为 $C_i$。小 Z 有无数片雪花，其中第 $i$ 片雪花的价值为 $E_i$。经过小 X 的仔细观察，他发现 $C$ 和 $E$ 满足特殊的条件：

$$
C_i=
\begin{cases}
x\times i& (x\times i\le K)\\
-K& \text{otherwise}
\end{cases}
$$
$$
E_i=
\begin{cases}
y\times i& (y\times i\le K)\\
-K& \text{otherwise}
\end{cases}
$$

小 Y 和小 Z 可以对这些落叶和雪花进行一些操作。每次，他们会选择满足价值之和 $\ge K$ 的一片落叶和一片雪花，然后让把它们一同组成一段彩色的回忆（Erinnerung）。之后，这片雪花和这片落叶就消失不见了，之后的操作也不能再用到这片雪花和落叶了。

小 X 想知道，他们最多能进行多少次操作。

## 说明/提示

**【样例解释】**

对于样例 1 的第一组数据，落叶的价值为 $2,4,6,8,10,-10,-10\dots$ ，雪花的价值为 $3,6,9,-10,-10\dots$ 。第一次操作选取第 $4$ 片落叶和第 $1$ 片雪花，价值和为 $11$。第二次操作选取第 $2$ 片落叶和第 $2$ 片雪花，价值和为 $10$。第三次操作选取第 $5$ 片落叶和第 $3$ 片雪花，价值和为 $19$。如是，可以进行 $3$ 次操作。容易证明不存在更优的解。

对于第二组数据，进行的两次操作可以为：选取第 $4$ 片落叶和第 $1$ 片雪花，以及选取第 $2$ 片落叶和第 $2$ 片雪花。

对于样例 2，所有的雪花和落叶的价值都为 $0$，不可能找到落叶和雪花使其和 $\ge 1$。

---

**【数据范围】**

-  Subtask 1（30 points）：$x,y,K,T\le 10$。
-  Subtask 2（70 points）：无特殊限制。

对于 $100\%$ 的数据，满足 $0\le x,y\le 10^{10}$，$1\le K\le 10^{10}$，$1\le T\le 10^5$。

## 样例 #1

### 输入

```
2
2 3 10
2 4 11```

### 输出

```
3
2```

## 样例 #2

### 输入

```
1
0 0 1```

### 输出

```
0```

# 题解

## 作者：Unordered_OIer (赞：46)

# P7441 题解
这道题的思维难度还是有的。

## Description
给定两个整数 $x,y$ 和一个正整数 $K$，生成了一个长度为 $\infty$ 的序列 $C,E$，满足：  
$$C_i=\begin{cases} x \times i & x \times i \leq K\\-K & \text{otherwise}\end{cases}$$

  
$$E_i=\begin{cases} y \times i & y \times i \leq K\\-K & \text{otherwise}\end{cases}$$

需要选择 $m$ 对 $C_i,E_j$ 满足 $C_i + E_j \geq K$，选择一次后所选择的 $C_i,E_j$ 都不可再用，问 $m$ 的最大值。

一共有 $T$ 组这样的数据

## Solution
观察一下数据范围，$1 \leq K \leq 10^{10},0 \leq x,y \leq 10^{10}$，所以单次询问算法复杂度肯定是 $\mathcal O(1)$ 级别的，于是考虑数学。

首先这个 $\infty$ 长度是假的，因为负数 $+$ 负数一定不会 $\geq K$，所以有效的 $C_i,E_j$ 分别有 $\left\lfloor \dfrac{K}{x} \right\rfloor,\left\lfloor \dfrac{K}{y} \right\rfloor$ 个。

观察样例，基本猜出答案为 $\min(\left\lfloor \dfrac{K}{x} \right\rfloor,\left\lfloor \dfrac{K}{y} \right\rfloor)$，也就是说，对于有效长度更小的序列，**每一个值都一定都能够找到另一个序列上的值使和 $\geq K$，且这些值可以不重复**。


下面给出一个略证，我们把序列 $E$ 的长度设为 $L_E$ ，序列 $C$ 的长度设为 $L_C$：

1. 当 $x<y$：

因为 $x<y$，所以 $L_E \leq L_C$。

则对于 $E_1$ 来说，它要匹配到的 $C_i$ 使得 $C_i+E_1 \geq k$，则必须满足 $i \geq \left\lceil \dfrac{K-E_1}{x} \right\rceil$，为了使答案最优，需要尽量取 $i=\left\lceil \dfrac{K-E_1}{x} \right\rceil$，为了方便表达，我们令 $p=\left\lceil \dfrac{K-E_1}{x} \right\rceil$，此时 $E_1+C_p \geq K$。

继续考虑 $E_2$，我们知道 $E_2-E_1=y$，$C_p-C_{p-1}=x$，则 $E_2+C_{p-1}-(E_1+C_p)=E_2-E_1+C_{p-1}-C_p=y-x>0$，所以 $E_2+C_{p-1}$ 也一定 $\geq K$。

所以对于所有的 $E_j+C_{p-j}(j < p)$，都一定 $\geq K$。那么前 $p$ 个 $E_j$ 就全部可以匹配到相应的 $C_i$。

此时会剩下一些 $E_j$，这些 $E_j$ 都一定比之前的 $E_j$ 大；此时还会剩下一些 $C_i$，这些 $C_i$ 也都比之前的 $C_i$ 大。所以在剩下的所有序列元素中，任意选择 $i,j$ 匹配都会满足要求。

而又因为 $L_E<L_C$，所以剩下的 $E_j$ 都一定可以匹配到 $C_i$，且匹配完还有剩余。

两部分相结合，则得到结论：$\forall\ 1 \leq j \leq L_E$ 都能成功匹配。

2. 当 $x>y$，与上述情况相同。

3. 当 $x=y$：

此时 $L_E=L_C$，则 $E_{L_E}+C_1>E_{L_E}+(K-E_{L_E})=K$，即 $E_{L_E}+C_1>K$，其他情况类似，所以这时也是能全部成功匹配的。

综上，答案就是 $\min(\left\lfloor \dfrac{K}{x} \right\rfloor,\left\lfloor \dfrac{K}{y} \right\rfloor)$。

还有一个要注意的点是 $x=0$ 时，一个序列全部为 $0$，此时如果 $y \nmid K$ 是无解，而 $y \mid K$ 时序列的最后一项匹配另一个序列的任意一项即为唯一满足条件的解。$y=0$ 类似。

所以就可以写程序了，总复杂度 $\mathcal O(T)$。

## Code

```cpp
ll T,x,y,k;
int main(){
	T=read();
	while(T--){
		x=read(),y=read(),k=read();
		if(x==0&&y==0){
			writeln(0);
			continue;
		}
		if(x==0)writeln(k%y==0?1:0);
		else if(y==0)writeln(k%x==0?1:0);
		else writeln(min(k/x,k/y));
	}
	return 0;
}
```

## 后记
这道题好像劝退了不少人，但是我觉得没那么难（

最后还是祝洛谷月赛**越来越好**。



---

## 作者：_zy_ (赞：23)

## [题目传送门](https://www.luogu.com.cn/problem/P7441)

**题目大意:**

求 $ai+bj≥k$ 的正整数解的个数。

~~并且，通过数据发现肯定是$O_{1}$输出。~~

- 当$ai>=k时$，$c[i]$为$-k$，再加上小于$k$的$d[i]$,一定不满足题意。

- 我们贪心的选择$min(a,b)$,试图找到更多的解。
	
    关于证明：
    
    不妨看$sample$吧$!$
    
    $2i+3j≥10$ 
    
    $1.j≥\frac{10-2i}{3}$,当i=1时有最大值$2$ .
 
    $2.i≥\frac{10-3i}{2}$,当i=1时有最大值$3$ .
    
    显然。

- 关于$0$的情况

	如果$x=y=0$，显然是$0$ .
    
   如果有一个不为零（显然是更大的那个），就判断是否$max(x,y)|K$,$true$为$1$，$false$为$0$。
   
 代码如下：
 
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define int unsigned long long 
using namespace std;
int re() {
	int p=0; char i=getchar();
	while(i<'0'||i>'9')	i=getchar();
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return p;
}
int T;
signed main()
{
	cin>>T;
	while(T--)
	{
		int x,y,k;
		x=re(); y=re(); k=re();
		if(x>y)	swap(x,y);
		if(x==0&&y!=0)	{if(k%y==0)	printf("1\n");else printf("0\n");continue;}
		if(x==0&&y==0)
		{printf("0\n");continue;}
		int tmp=(k-(k/x)*x)/y;
		cout<<(k/y)-tmp<<endl;
	}
}
```
   
   
  **如有不妥，请不要吝啬您的评价.**
    




---

## 作者：lgswdn_SA (赞：18)

出题人题解（

upd on 03.27: 修了一个锅

答案：$\min(\lfloor \frac{K}{x}\rfloor,\lfloor \frac{K}{y}\rfloor)$

---

构造方案：设 $n=K/x, m=K/y$，不妨设 $n\ge m$。则第 $i$ 片雪花和第 $n-i+1$ 片落叶配对形成一次操作。

---

证明：

显然不存在比他更大的方案（所有权值非负的雪花都能进行操作）

证明合法性。由于 $x\le y$，所以 $C_{n}+E_{1}$ 为所有操作的 $E+C$ 的最小值。由于 $C_{n}+x\ge K$，又因为 $y\ge x$，所以有 $C_{n}+y\ge K$。所以一定合法。

要注意 $x,y=0$ 的时候的特判。$x,y$ 都为 $0$ 的时候答案为 $0$，否则设大的那个为 $p$，答案为 $[K\equiv 0\pmod p]$。

```cpp
#define int long long
int T,x,y,k;
signed main() {
	T=read();
	while(T--) {
		x=read(), y=read(), k=read();
		if(!(x||y)) printf("%lld\n",0);
		else if(!(x&&y)) printf("%lld\n",x==0?k%y==0:k%x==0);
		else printf("%lld\n",x>y?k/x:k/y);
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：6)

## Content
给定 $x,y,K$。定义两个数列 $c,e$，其中 $c_i=\begin{cases}x\cdot i&x\cdot i\leqslant K\\-K&\text{otherwise}\end{cases}$，$e_i=\begin{cases}y\cdot i&y\cdot i\leqslant K\\-K&\text{otherwise}\end{cases}$。每次操作从两个数列中各选取一个数，满足两个数之和 $\geqslant K$。一个数选取了之后不能再重复取。问你一共能进行多少次操作。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 10^5$，$0\leqslant x,y\leqslant 10^{10}$，$1\leqslant K\leqslant 10^{10}$。**
## Solution
不难发现，如果 $x,y\neq0$，那么答案必定是 $\min\{\left\lfloor\dfrac Kx\right\rfloor,\left\lfloor\dfrac Ky\right\rfloor\}$。

证明：

（1） $y\geqslant x$，则对于 $(c_n,e_1)$ 这一对数（$n$ 表示能够使 $c_i\geqslant 0$ 成立的最大的 $i$），因为 $c_n+x\geqslant K$，而 $y\geqslant x$，所以必然有 $c_n+e_1=c_n+y\geqslant K$。后面的 $(c_{n-1},e_2),\dots$ 也显然成立。

（2）$y\leqslant x$，则对于 $(c_1,e_m)$ 这两对 （$m$ 含义类比于上面的 $n$），因为 $e_m+y\geqslant K$，而 $x\geqslant y$，所以必然有 $c_1+e_m=e_m+x\geqslant K$。后面的 $(c_2,e_{m-1}),\dots$ 也显然成立。

证明完之后我们再来看看 $x,y$ 中至少有一个等于 $0$ 时的情况：

（1）$x,y$ 中有且仅有一个等于 $0$。则我们需要看是否有 $\max\{x,y\}\mid K$，如果有的话，那我们可以拿一个 $K$ 和 $0$ 组成一对，这对数的和恰好等于 $K$，此时答案为 $1$；否则，答案为 $0$。

（2）$x,y$ 都等于 $0$，显然，由于 $K\geqslant 1$，且无法选出一对数使得它们的和为正整数，所以答案为 $0$。

分类讨论完这些情况后，代码就不难打了。
## Code
```cpp
int main() {
	MT {
		ll x = Rll, y = Rll, k = Rll;
		if(!x && y && !(k % y)) puts("1");
		else if(!y && x && !(k % x)) puts("1");
		else write(min((!x ? 0 : k / x), (!y ? 0 : k / y))), puts("");
	}
	return 0;
}
```

---

## 作者：Macesuted (赞：5)

[题面](https://www.luogu.com.cn/problem/P7441)

# 分析

显然价值为 $-K$ 的落叶或雪花对我们来说是没有意义的。

下面我们假设 $x > y$。

对于一个价值为 $x \times i$ 的物品，我们令其与 $y \times ( \lfloor \frac K y \rfloor -i+1)$ 匹配。两物品和为

$x \times i + y \times (\lfloor \frac K y \rfloor -i+1)=(x-y)\times i + y \times (\lfloor \frac K y\rfloor +1)$

由于 $y \times (\lfloor \frac K y \rfloor +1) > K$ 且 $(x-y) \times i>0$，所以两物品之和满足题目所给的条件。

显然 $\forall 1 \le i \le \lfloor \frac K x\rfloor,\lfloor \frac K y\rfloor -i +1 \ge 1$，所以答案即为 $\lfloor \frac K x\rfloor$。

# 代码

需要注意特判，并注意特判的时候不要出现对 $0$ 取模的情况。

```cpp
/**
 * @author Macesuted
 * @date 2021-03-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

using io::getch;
using io::putch;
using io::read;
using io::write;

int main() {
    int T = read<int>();
    while (T--) {
        long long x = read<long long>(), y = read<long long>(), K = read<long long>();
        if (x == 0 && y == 0)
            write(0);
        else if (x == 0)
            write(K % y == 0);
        else if (y == 0)
            write(K % x == 0);
        else
            write(K / max(x, y));
        putch('\n');
    }
    return 0;
}
```

---

## 作者：Thomas_Cat (赞：5)

观察题目：

$$C_i=\begin{cases}x \times i&(x \times i \le K)\\-K&\texttt{otherwise}\end{cases},E_i=\begin{cases}y \times i&(y \times i \le K)\\-K&\texttt{otherwise}\end{cases}$$

由题意，得题目中 $C_i$ **有效数组** 一定不是下面 $-K$ 的情况，即下文中的所有叙述都为第一种情况，通过观察发现，题目中的有效数组的数量为$\left\lfloor\dfrac{K}{x}\right\rfloor,\left\lfloor\dfrac{K}{y}\right\rfloor$。

则可以猜想题目中的答案为 $\min(\left\lfloor\dfrac{K}{x}\right\rfloor,\left\lfloor\dfrac{K}{y}\right\rfloor)$。

---

下给出证明：

令题目中能够使 $c_i \ge 0$ 的最大值 $\max(i)=\alpha$，能够使 $e_i \ge 0$ 的最大值 $\max(i)=\beta$

- 当 $y \ge x$ 时，则对于 $(C_\alpha,E_1)$ 显然成立。

$\because C_\alpha + x \ge K$ 且 $y \ge x$

$\therefore (C_\alpha,E_1) \to C_\alpha + E_1 = C_\alpha + y \ge K$

则显然后续数组 $(C_{\alpha-1},E_2) \cdots$ 显然成立。

- 当 $x \ge y$ 时，则对于 $(C_1,E_\beta)$ 显然成立。

$\because E_\beta + y \ge K$ 且 $x \ge y$

$\therefore (C_1,E_\beta) \to C_1 + E_\beta = E_\beta + x \ge K$

则显然后续数组 $(C_2,E_{\beta-1}) \cdots$ 显然成立。

---

在这里还需要特判 $x,y=0$ 的情况。

- $x,y$ 都为 $0$ ，易知答案为 $0$（证明略）

- $x,y$ 其中有一个为 $0$，如果 $\max(x,y) \equiv\ 0 \pmod{K}$可以取 $0,K$ 一对，答案为 $1$ ，否则为 $0$。

---

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	while(t--){
		long long x,y,k;
		cin>>x>>y>>k;
		if(x==0&&y!=0&&(k%y)==0) cout<<1<<endl;
		else if(y==0&&x!=0&&(k%x)==0) cout<<1<<endl;
		else cout<<(min((!x?0:k/x),(!y?0:k/y)))<<endl;
	}
	return 0;
}
```

---

## 作者：闲人 (赞：4)


~~说实话，当我看到这道题时还有点懵。~~  
但是你静下来就会发现其实是一道数学思维的题。

我们可以把题抽象一下：  
- 有T组数据据。  
- 每一组数据有两个等差数列，公差分别为x，y；   
- 两个数列最大的一个数不大于K；  

## 一些小问题 
细心地同学已经发现，我好像并没有考虑-K的情况。  
why？  
很简单    

$∵0\le C _i  ,E _i\le K$  
$∴C _i+(-K),E _i+(-K) < K$  

so我们可以不用考虑-K的情况  
## 进入正解

### Round1 
我们看看样例中的两个等差数列：  
2 4 6 8 10  
3 6 9  
因为每一片叶子和每一片雪花只能用一遍  
所以我们可以用其中一个数列中最小的数字去加另一个数列的最大数。  
为什么这样做?  
不难发现  
$3 + 10 = 13$  
$6 + 8 = 14$  
$9 + 6 = 15$  
这是一个递增的关系  
有兴趣的小朋友可以证明一下为什么。  

如果加起来不足K怎么办？  
那我们就用一个数列的第一个去加另一个数列的倒数第二个数。  

### Round 2 
新的问题又出现：应该用哪一个数列的第一个数去加另一个数列的最后一个数呢？  
再看一下样例：  
2 4 6 8 10  
3 6 9  
可以发现我们最好情况下可以配对所有数字最少数列中的所有数，所以我们应该尽量把数字少的数列中的数字用完。  
### Round 3 
那么思路就出来了：  
1. 找出数列短的那一个。  
1. 用这个数列的第一个去加另一数列的最后一个数，如果大于等于K，则证明这个数列中的数都能匹配，直接输出此数列的数字个数。  
1. 如果2没有执行我们就用这个数列的第一个数去加另一个数列的倒数第二个数。   
### Round 4 之亿点点问题  
看看第二个样例是什么  
1  
0 0 1  
有“0”？？？？？？  
没错，如果有“0”，就会比较麻烦。  
1. 如果两个公差都是“0”，那必然输出“0”，没说的  
1. 如果其中一个公差是“0”，我就还要判断另一个数列的最后一个数等不等于K，若是，就输出“1”。如不是，就只能输出“0”了
### Round 5 

最后还是附上代码（代码的思路有一点点不一样，它说用数列数字多的那一个数列的最后一个数依次加另一数列的1,2,3...个数）


```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;

int find_ans(ll x,ll y,ll k){
	ll X_ = k / x, X = x, Y_2 = k % y;
	ll Y_ = k / y, Y_last = k - Y_2;
	for(ll i = Y_ ; i >= 0; -- i){
		if((Y_last + x) >= k){
			cout << X_ << endl;
			return 0;
		}
		else {
			x += X;
			X_ --;
		}
	}
	cout << "0" << endl;
	return 0;
}
int main(){
	ll n;
	cin >> n;
	for(ll i = 1; i <= n; i ++){
		ll a,b,c;
		cin >> a >> b >> c;
		if(a == 0 || b == 0){
			if(a == 0 && b == 0){
				cout << "0" << endl;
			}
			else if(a == 0 && c % b == 0){
				cout << "1" << endl;
			}
			else if(b == 0 && c % a == 0){
				cout << "1" << endl;
			}
			else cout << "0" << endl;
		}
		else{
		 	if(a >= b){
			 	find_ans(a,b,c);
			 }
			else {find_ans(b,a,c);}
		}
	}
	return  0;
}
```
## 后记

这篇题解中有些话可能有点绕，需要好好思考一下。  
因为是我第一篇发的题解（前面（一年前）发过只有代码的题解没有过） 也许有不足之处，还请随时指出。  
感谢阅览！

---

## 作者：Merron (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P7441)

思路：

咱们先来分析特殊的情况

  1. `If x = 0 && y = 0`  显然，直接没戏，因为K恒大于等于1。

  2. `If x = 0 || y = 0 `

     之所以换行，是因为这里有一个坑点。有的人可能和我一样，直接输出无解。However, WAWAWA...

     为什么直接输出不行呢？举两个栗子。

     第一个是成立的栗子（默认第一个为0，不影响结果）：

     $x = 0 , y = 3, K = 5$

     此时的数组：

     $C = \{0, 0, 0, 0, ...\}$

     $E = \{3, -5, -5, -5, ...\}$

     此时，确实不行。

     第二个是反例：

     $x = 0, y = 3, K = 6$

     $C = \{0, 0, 0, 0, ...\}$

     $E = \{3, 6, -6, -6, ...\}$

     欸，有没有发现，此时刚好有一种。

     由于某些原因（~~其实是我懒~~），此处不再举例子，直接出结论：

     当 $x$ ， $y$ 中有一个为0时（方便起见，默认 $x$ 为零）


     如果 $y$ 互质于 $K$ , 输出0

     否则输出1

     

-------

最后来分析一般情况：

先上公式：
$$
Ans = \min(\lfloor\frac{K}{x}\rfloor, \lfloor\frac{K}{y}\rfloor)
$$
分析：

$C = \{x, 2x, 3x, 4x, ... , nx, -K...\} $ (n 为与x相乘小于K的最大数，则 n = $\lfloor\frac{K}{x}\rfloor$, 下m同 )

$E = \{y, 2y, 3y, 4y, ..., my, -K...\}$

---

情况一： $If \ x = y$

   显然，此时答案为 $n$ ，与公式符合（此处易证）

情况二： $If \ x > y$

   则 $n \leq m$，如果按公式，答案就为n，那为什么呢？

   根据除法可知：

   $K \div n = a ... z$

   $z$ 为余数，定小于 $n$ ，也小于 $m$

   此处敲黑板

---

$$
\because K = n \times a + z, \ and \ m > z
\\
\therefore n \times a + m > K
\\
\text{又因为 n} \leq m
\\
\therefore n \times a + m - n + m = n(a-1)+ 2m \ge n \times a + m > K
\\ 由此可得，每一个ix总能找到一个iy与之匹配
$$
   洛谷的Latex好像有点炸。。。


所以，答案就是x的数量（因为x较小）

同理可证 $x < y$ 的情况

证毕



懒得总结了，看代码吧...

----

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
long long x, y, k;

int main()
{
    scanf("%d", &t);
    while(t --)
    {
        scanf("%lld%lld%lld", &x, &y, &k);
        if(x == 0 && y == 0)
        {
            printf("0\n");
            continue;
        }
        else if(x == 0 || y == 0)
        {
            if(k % max(x, y) == 0)printf("1\n");
            else printf("0\n");
            continue;
        }
        printf("%lld\n", min(k / x, k / y));
    }
}
```

---

## 作者：0x3F (赞：2)

首先，这个 $-K$ 可以不用考虑它。不为什么。

其次，如果 $x, y$ 都是 $0$，那答案就是 $0$。不为什么。

再次，如果 $y$ 为 $0$，$x$ 非 $0$，则当 $x \mid K$ 时答案为 $1$，否则答案为 $0$。

因为 $E$ 数组全为 $0$，只有当存在一个 $C_i$ 恰好等于 $K$ 时才存在。

最后，如果 $x, y$ 均非 $0$，那么：

$C$ 数组的有效元素的个数为 $\lfloor \frac{K}{x} \rfloor$，数组 $E$ 的有效元素的个数为 $\lfloor \frac{K}{y} \rfloor$，

显然答案一定不会超过 $\min(\lfloor\frac{K}{x}\rfloor,\lfloor\frac{K}{y}\rfloor)$， 也就是 $\lfloor\frac{K}{\max(x, y)}\rfloor$。

我们猜测答案就是它。下面是证明：

令 $x \ge y, \lfloor \frac{K}{x} \rfloor = a, \lfloor \frac{K}{y} \rfloor = b $，则 $a \le b$。

我们取 $a$ 组，分别是 $(C_1, E_b), (C_2, E_{b-1}) , \cdots, (C_a, E_{b-a+1})$。

易知 $C_1 = x, E_b = b \times y \ge K - y$

所以 $C_1 + E_b \ge K+x-y \ge K$。

又因为 $C_i + E_{b-i+1} = C_1 + E_b + (i-1)(x-y) \ge C_1 + E_b \ge K$

所以每一组都大于等于 $K$。

证毕。

综上，答案为：

$$\begin{cases}0&x=y=0\\0&x=0,y\nmid K\\1&x=0,y\mid K\\\lfloor\frac{K}{\max(x, y)}\rfloor&x\neq0, y\neq0\end{cases}$$

关于为什么要开 $\texttt{long long}$，我就不说了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
long long x, y, k;

int main() {
    ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> x >> y >> k;
		if (x == 0) {
			if (y == 0) cout << 0 << endl;
			else cout << (k % y == 0) << endl;
		} else if (y == 0) cout << (k % x == 0) << endl;
		else cout << k / max(x, y) << endl;
	}
	return 0;
}
```


---

## 作者：_lfxxx_ (赞：2)

### 做题前要知道的：
负数的价值是肯定用不上的，并且答案最多只有 $\dfrac{K}{\max(x,y)}$ 个。
### 思路：
显然，有一些部分落叶（或雪花）是没有用的（当 $x$ 不等于 $y$ 时）。也就是说，我们只要关注那些大的落叶（或雪花）即可。

即关注 $x*(x-y+1),x*(x-y+2)\cdots$ 和 $y$ 的全部。（以下证明前提条件均为$x\leq y$）

#### 举个例子：
拿这组样例说：
```
1
3 4 10
```
我们只要关注 $6,9$ 和 $4,8$。

（$x\leq y$ 且 两个数都不为 $0$ ）按照贪心的思想，应该让大的配小的才能配对次数多一些。$x$ 组最后一个数是 $K-K \bmod x$ 这时 $y$ 组的第一个为 $y$ ，因为 
$y\geq x$ ，所以 $y\geq K \bmod x$ ，所以第一组可以，后面每一组和都会加 $y-x$ ，所以后面的组肯定可以，也就是说一共有 $\dfrac{K}{y}$ 组。

但如果你真就按这个思路交了上去，恭喜错3个点。

为什么会错3个点呢，因为忽略了 $0$。

显然，~~粗鄙之语~~当有一组为 $0$ 时， 其他一组必须最大数是 $K$ 时，才能成功一次。也就是判断能不能整除。

知道这些点以后，这题就特别简单了。
### 插一句，别忘开 $\texttt{long long}$
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long x,y,k;
		scanf("%lld%lld%lld",&x,&y,&k);
        if(x==0||y==0){//特判0
            if(x&&!(k%x))
                puts("1");
            else if(y&&!(k%y))
                puts("1");
            else
                puts("0");
        }
        else
			printf("%lld\n",k/max(x,y));
	}
	return 0;
}
```
~~这是红题就离谱~~

~~麻烦管理再审一下，我补充了一些东西，谢谢~~

---

## 作者：Booksnow (赞：2)

# Erinnerung

## 题目大意

现在我们有两个无穷大的数组， $C$ 与 $E$ ，这个数组里面的元素如下：

$$ C_i=\lbrace ^{x\times i (x\times i\leq K)}_{-K(x\times i> K)} $$

$$ E_i=\lbrace ^{y\times i (y\times i\leq K)}_{-K(y\times i> K)} $$

一次操作可以从这两个数组中各选出一个数，要求选出数的数和大于等于 $K$ ，之后这两个数从数组中删去。

给出 $x,y,K$ ，求最多能够进行多少次操作。 

## 分析

如题，我们能够发现以下显然结论：

- 选出的数不能是 $-K$ 。

- 将两个数组不为负数的部分提出，皆为**等差数列**。

很显然此题满足性质如下：

用公差小的一组数的最大值从小到大尝试另一组数的每个值与之相加是否能大于等于 $k$，若找到一个满足条件的值后，则公差大的一组数中大于此数的数分别与公差小的一组数**从大到小**一定能够结合。

其实就相当于是**从公差大的一组数中选出来的数的增量是肯定大于从公差小的一组数中选出来的数的减量**，所以剩下的数从公差小的一组数中选择最大的，从公差大的一组数中选择比上一个选择的数大的，一定满足条件（前提是第一个满足条件）。

实现也极为简单。公差大的一组数（假设为 $C$ ）中最小能够与公差小的一组数（假设为 $E$ ）中最大值匹配的数的编号为: 

$$ tag=\lceil (\frac{(K-y\times \lfloor \frac {K}{y}\rfloor  )}{x}) \rceil $$

注意 $tag$ **可能会等于零**，也就是第一个数就可以，特判一下即可。

最后代码如下：

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
    ll s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') w=-1;ch=getchar(); }
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
ll x,y,k;
ll xx,yy,T;
int main(){
	T=read();
	while(T--){
        x=read(),y=read(),k=read();
        if(!x&&!y){ puts("0"); continue; }
        if(!x) { if(k%y==0) puts("1"); else puts("0"); continue; }
        if(!y) { if(k%x==0) puts("1"); else puts("0"); continue; }
        if(x&&y){
	        xx=floor((double)k/x),yy=floor((double)k/y);
	        if(xx>yy) { swap(xx,yy);swap(x,y); }
			ll tag=ceil((double)(k-y*yy)/x);
			if(!tag) tag++;
			printf("%lld\n",xx-tag+1);
	        continue;
        }  
	}
	return 0;
}
```

---

## 作者：VinstaG173 (赞：2)

还是挺有趣的，但是搞这个 $x=0$ 或 $y=0$ 就很讨厌。

当 $x>0$ 且 $y>0$ 时，答案为 $\left\lfloor\dfrac{K}{\max(x,y)}\right\rfloor$。

证明：

设 $x>y$。显然答案不能超过 $s=\left\lfloor\dfrac{K}{x}\right\rfloor$。

设 $t=\left\lfloor\dfrac{K}{y}\right\rfloor$。

由 $ty \le K <(t+1)y$ 且 $x>y$，有 $x+ty >K$。

因此显然 $vx+(t-v)y>K$ 且 $vx \le K,(t-v)y \le K (v=1,2,\dots,s)$。

故答案可以取到 $s$，即答案为 $s$。

证毕。

然后考虑 $x$ 或 $y$ 为 $0$，不妨设 $x=0$。则显然在 $y|K$ 时答案为 $1$，其余情况答案为 $0$。若都为 $0$ 则显然答案为 $0$。

Code:
```cpp
#include<cstdio>
#define ll long long
inline char rc()
{
	static char buf[524288],*pn=buf,*pe=buf;
	return (pn==pe)&&(pe=(pn=buf)+fread(buf,1,524288,stdin),pn==pe)?EOF:*pn++;
}
inline int read()
{
	int x=0;
	char cc=rc();
	while(cc<'0'||cc>'9')cc=rc();
	while(cc>='0'&&cc<='9')x=x*10+cc-'0',cc=rc();
	return x;
}
inline ll _read()
{
	ll x=0;
	char cc=rc();
	while(cc<'0'||cc>'9')cc=rc();
	while(cc>='0'&&cc<='9')x=x*10+cc-'0',cc=rc();
	return x;
}
int t;
ll x,y,k;
int main()
{
    t=read();
    while(t--)
    {
        x=_read(),y=_read(),k=_read();
        printf("%lld\n",(x)?((y)?(k/((x>y)?x:y)):(!(k%x))):((y)?(!(k%y)):0));
    }
    return 0;
}
```

---

## 作者：HYdroKomide (赞：1)

# **正文：**
## 题意：
本题没有多少难点，主要就是特判的细节。首先，易得若 $C_i$ 与 $E_i$ 中有 $-K$ 出现，结果肯定无法 $≥K$。我们可以简单地求出 $E$ 中不是 $-K$ 的数量为 $[k/x]$，$E$ 中不是 $-K$ 的数量为 $[k/y]$。我们首先简单地猜想结果就是 $min([k/x],[k/y])$。~~在比赛中建议不花太多时间证明，直接先试一试结果是否可以成功。~~

但是在题解中我们还是需要证明我们的结论：

首先我们设 $x≥y$，这时我们的答案为 $min([k/x],[k/y])$，也就是 $[k/x]$。此时，$E_{[k/x]}+C_1=y+[k-x]\times x$ 也必定 $≥K$。之后每一种情况也都满足两数之和 $≥K$。

之后就是特判：
- 如果 $x==0$ 而且 $y==0$，那么结果显然为 $0$。
- 如果 $x$ 与 $y$ 其中一个为 $0$，如果 $K$ 能够整除那个不为 $0$ 的数，则结果为 $1$。
## 程序部分：
时间复杂度 $O(T)$，注意要开 `long long`。
```cpp
#include<cstdio>
using namespace std;
long long t,x,y,k;
int main(){
    scanf("%lld",&t);
    while(t--){
    	scanf("%lld%lld%lld",&x,&y,&k);
    	if(k>0&&(x==0&&y==0))printf("0\n");
    	else if(k>0&&x==0){//特判
    		if(k/y*y==k)printf("1\n");
    		else        printf("0\n");
		}
		else if(k>0&&y==0){//与上一个特判一样
    		if(k/x*x==k)printf("1\n");
    		else        printf("0\n");
		}
    	else printf("%lld\n",min(k/x,k/y));
	}
    return 0;
}
```
# **THE END**

---

## 作者：KSToki (赞：1)

既然是月赛第一题，看完样例我们直接大胆猜想：当 $x\not=0$ 且 $y\not=0$ 时答案为 $\min(k/y,k/x)$。

证明一下：直接不妨设有 $x<y$，则答案应为 $k/y$。此时一定有 $C_{k/x}+E_1\geq k$，因为 $C_{k/x}$ 与 $k$ 相差不到 $x$，而 $E_1=y$。每次将 $E$ 的 $i$ 加一，$E$ 增大的比 $C$ 减少的多，所以始终满足条件，直到 $E$ 中的正数被用完。

注意到我们使用了除法，自然要考虑为 $0$ 的特殊情况，当 $x=0$ 且 $y=0$ 时答案显然为 $0$；当 $x=0$ 或 $y=0$ 时，如果另一个是 $k$ 的因数，那么答案显然为 $1$，否则为 $0$。

代码，记得开 `long long`：
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T;
ll x,y,k;
int main()
{
	T=read();
	while(T--)
	{
		scanf("%lld%lld%lld",&x,&y,&k);
		if(x==0&&y==0)
			puts("0");
		else if(x==0)
			putint(k%y==0);
		else if(y==0)
			putint(k%x==0);
		else
			putll(min(k/x,k/y));
	}
	return 0;
}
```

---

## 作者：Terac (赞：0)

一道很不错的思维题。  

把 $x=0$ 或 $y=0$ 的情况给特判掉，可以证明一个结论：  

$$ans=\min(\left\lfloor{\dfrac{K}{x}}\right\rfloor,\left\lfloor{\dfrac{K}{y}}\right\rfloor)$$  

即 $ans=\lfloor{\frac{K}{\max(x,y)}}\rfloor$。 
    
稍微理解下题意后，易知当 $C_i=-K$ 和 $E_i=-K$ 时，这些落叶和雪花是构造不了的。  

对于证明，若 $ans>\min(\lfloor{\frac{K}{x}}\rfloor,\lfloor{\frac{K}{y}}\rfloor)$，容易找出反例。

令 $n=\lfloor{\frac{K}{x}}\rfloor$，$m=\lfloor{\frac{K}{y}}\rfloor$，则 $\max C_i=n\times x$，$\max E_i=m\times y$，因为 $x,y$ 的意义一样，不妨设 $x\leq y$，$n\ge m$。  


令 $K=ix+(n-i)x+t$，其中 $i\in[1,n]$，$t<x$。  

因为 $x\le y$，所以 $K<ix+(n-i)y+y$，即 $K<ix+(n-i+1)y$。  

因为 $1\le n-i+1\le m,1\le i\le n$ 且 $n\ge m$，所以 $n-i+1$ 的满足题意的 $m$ 种取值 $i$ 均可取到。  

于是至少有 $m$ 种匹配的方法。  

而 $m =\min(\lfloor{\frac{K}{x}}\rfloor,\lfloor{\frac{K}{y}}\rfloor)$，所以最多可以操作 $\min(\lfloor{\frac{K}{x}}\rfloor,\lfloor{\frac{K}{y}}\rfloor)$ 即 $\lfloor{\frac{K}{\max(x,y)}}\rfloor$ 次。  

然后代码随便敲就好了。  

记得开 `long long`。

---

