# Help is needed for Dexter

## 题目描述

Dexter 对 Dee Dee 感到厌烦了，所以他决定让 Dee Dee 玩一个游戏来让她忙起来。这个游戏很容易玩，但至少对 Dee Dee 来说不容易赢。但是，Dexter 没有时间浪费在这种无聊的任务上，所以他需要你的帮助。

游戏中有一个按钮，当按下按钮时，电脑将随机选择一个数字 $N$。然后屏幕上会显示从 $1$ 到 $N$ 的数字。Dee Dee 可以从屏幕上的数字中选择任意数量的数字，然后她将命令计算机从所选数字中减去她选择的一个正整数（不一定是屏幕上的数字）。她的目标是让所有数字都变成 $0$。

例如，如果 $N = 3$，屏幕上将显示 $3$ 个数字：$1$、$2$、$3$。假设她现在选择 $1$ 和 $2$，命令计算机减去 $1$，那么屏幕上的数字将变为：$0$、$1$、$3$。然后她选择 $1$ 和 $3$，并命令减去 $1$，现在屏幕上的数字是 $0$、$0$、$2$。最后她选择 $2$ 并减去 $2$，所有数字变为 $0$。

Dexter 并不愚蠢，明白这可以很容易地完成，所以为了增加难度，他将为每个 $N$ 给出一个限制 $L$，并且确保 $L$ 是仍然能在 $L$ 步内完成的最小值。但 Dexter 没有时间去思考如何为每个 $N$ 确定 $L$，因此他请求你编写一个程序，输入 $N$，输出 $L$。

## 样例 #1

### 输入

```
1
2
3```

### 输出

```
1
2
2```

# 题解

## 作者：Hisaishi_Kanade (赞：4)

略带思维的题目。

### 一、题意

给出正整数 $n$，每次可以将区间 $\left[1,n\right]$ 中一些数减去一个相同的数。求最少的步数使其全为零。

### 二、思路

设 $g\left(x\right)$ 表示使区间 $\left[1,x\right]$ 全为零的最小次数。

首先考虑最原始的情况：

>每次所有非零数减一。

以上方法，共 $n$ 次，即 $g\left(n\right)=n$。

但这显然不是最优的。

再考虑略优的情况：

>每次所有比一大的数减二。

以上方法，共 $\frac n 2+1$ 次，即 $g\left(n\right)=\frac n 2+1$。

可惜是可以举出反例的。

如 $n=10$ 时，这种方法是 $6$ 步，实际最优是 $4$ 步（待会讲）。

再考虑更优的情况：

>每次所有比二大的数减三。

……

以此类推。

最后，我们总结一个规律，当每次减去的值最大就可以最优。

此时显然得到求 $g\left(n\right)$ 时第一次减去 $\frac n 2+1$ 就能得到最优解。

进一步得到递推公式：

$$
g\left(x\right)=g(\frac x2)+1
$$

再得到通项公式：

$$
g\left(x\right)=\lfloor\log_2x+1\rfloor
$$

### 三、代码

显然，套通项公式即可。
```cpp
#include <iostream>//cin cout
#include <algorithm>//__lg
using namespace std;
int n;
int main(){
	while(cin>>n)cout<<(int)(__lg(n)+1)<<endl;
	return 0;
}

```

---

## 作者：luguangxing (赞：2)

题意:
给出正整数 $n$，每次可以将区间 $[1，n]$ 中一些数减去一个相同的数。求最少的步数使其全为零。

思路:
这一题有一点 $2$ 分答案的思路，我们举个例子总共有 $10$ 个数 $1$ 到 $10$，我们把他分成两部分 $1$ 到 $5$ 和 $6$ 到 $10$。每一次把他的后半段减去 $5$ （就是二分之十） 最后减去一就是答案了。

公式展示。

由上面的思路可以得出公式：$(\log_2(n)+1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	while(cin>>n) 
   	cout<<int(log2(n)+1)<<endl;
	return 0;
}
```

---

## 作者：MrSWdAxiv (赞：1)

## 思路

拿到题目以后，最好自己试一试，就会发现一种方法：

比如说数据是 $1,2,3,4,5,6$，就把 $4,5,6$ 同时减去他们中的最小值 $4$，就能得到序列 $1,2,3,0,1,2$，因为 $1,2$ 出现了两次，所以这个数列就等价于序列 $1,2,3$。即 $f_6 = f_3 + 1$。

综上可得，一般情况下，我们会保留 $1$ ~ $n / 2$，把剩下的数同时减去 $n / 2 + 1$，得到序列 $1,2…,n / 2,0,1,…,(n - 1) / 2$，它等价于 $1,2,…,n / 2$，因此 $f_n = f_{n / 2} + 1$，边界就是 $f_1 = 1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f(int n){
	return (n==1)?1:f(n/2)+1;
}
int n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin>>n){
		cout<<f(n)<<'\n';
	}
	return 0;
}

```
感谢蓝皮书提供的思路。

---

## 作者：felixshu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA11384)

## 题目大意

给出正整数 $n$，每次可以将区间 $[1,n]$ 中一些数减去一个相同的数。求最少的步数使其全为零。

## 分析

把这个数组 $n$ 分成 $2$ 组。分别为 $[1,\frac{n}{2}-1]$ 与 $[\frac{n}{2},n]$。
然后让 $[\frac{n}{2},n]$ 减去 $\frac{n}{2}$。数组就变为了 $[1,\frac{n}{2}-1]$ 与 $[0,\frac{n}{2}]$。这就等价与 $[1,\frac{n}{2}]$。然后一直这样，最后减去 $1$ 即可。

然后就可以推出公式 $\log_2n+1$。

## 下面是 AC 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
int n;
	while(cin>>n)
	{
		cout<<__lg(n)+1<<endl;
	} 
}

```


---

## 作者：TemplateClass (赞：0)

每一次将后半段减去 $\left\lfloor\dfrac{n}{2}\right\rfloor$，得到数列 $1,2,3,\cdot\cdot\cdot,\dfrac{n}{2}-1,0,1,2,\cdot\cdot\cdot,\dfrac{n}{2}$，因为相同的数字一起减即可，所以它等价于 $1,2,3\cdot\cdot\cdot\dfrac{n}{2}$，一直下去，最后再减掉 $1$ 即可，可以推出式子 $\left\lfloor\log_{2}n+1\right\rfloor$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int main(){
	while(cin>>n) cout<<int(log2(n)+1)<<"\n";
}
```

---

## 作者：lwx20211103 (赞：0)

## 题目大意

给你一个数组 $N$ 的长度 $n$，数组中的每个数字 $N_i$ 等于 $1, 2, 3 …i$，例如 $n = 3$，那么数组就为 $[1, 2, 3]$。现在，你可以在一个区间任选几个数字，在这几个数字中同时加上或减去一个数字，求经过几次这样的操作后数组的每个数字都为 $0$。

## 解题思路和代码

我们可以考虑把数组分成两段，分别为 $[1, \lfloor \frac{n}{2} \rfloor]$，$[\lfloor \frac{n}{2} \rfloor + 1, n]$，在右半部分同时减去 $\lfloor \frac{n}{2} \rfloor + 1$，这样，数组就变成了 $[1,2… \lfloor \frac{n}{2}\rfloor, 0, 1,…\lceil\frac{n}{2} \rceil - 1]$。

因为每次能选择好几个数字，而后面的数字又如前面的数字，所以此时要操作的数列的长度只剩下 $\lfloor \frac{n}{2} \rfloor$，于是我们可以得到：
$$f(x) = \begin{cases} 1 & x = 1 \cr \ f(\frac {x}{2})+1 & \text{Otherwise.}\end{cases}$$ 

毕竟当数组长度减半的时候要多一次操作。

于是我们就能写出简单的递归代码了。

```
int func(n)
{
    if (n == 1) return 1;
    return func(n >> 1) + 1;
}
```

我们还可以加上记忆化，可以优化性能，虽然此题数据用不着。

```
int memory[1 << 21];
int func(int n)
{
	if (n == 1)
    {
        return 1;
    }
    if (memory[n])
    {
        return memory[n];
    }
    memory[n] = func(n >> 1) + 1;
    return memory[n];
}

```

但我们最终可以得出一个 $\mathcal O(1)$ 的做法，从递归代码来看，每一次整个数组减半，操作次数要一直除以二直到变成一，但结果要加一，所以，我们可以大胆地推出，$f(x) = log_2 x +1$。

于是，我们的最终代码就这样得出来了。

```
int n;
while (cin >> n) cout << log2(n) + 1 << "\n";
```


---

## 作者：ncwzdlsd (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/clximejf.png)

当 $n=6$ 的时候留下 $1,2,3$，而把 $4,5,6$ 同时减去 $min\left\{4,5,6\right\}=4$ 得到序列$1,2,3,0,1,2$，它等价于 $1,2,3$。换句话说，$f(6)=f(3)+1$。

我们保留$1$ 到 $n-2$，把剩下的数同时减去 $\dfrac{n}{2}+1$，得到序列 $1,2,...,\dfrac{n}{2},0,1,...,\dfrac{n-1}{2}$，它等价于 $1,2,...,\dfrac{n}{2}$，因此，$f(n)=f(\dfrac{n}{2})+1$。边界是 $f(1)=1$。

代码如下：
```cpp
#include<cstdio> 
int f(int n) 
{ 
    return n == 1 ? 1 : f(n/2) + 1; 
} 
int main() 
{ 
    int n; 
    while(scanf("%d", &n) == 1) 
        printf("%d\n", f(n)); 
    return 0; 
}
```

---

## 作者：Lyccrius (赞：0)

我们保留 $1 \sim n / 2$，把剩下的数同时减去 $n / 2 + 1$，得到序列 $1, 2, \cdots, n / 2, 0, 1, \cdots, (n - 1) / 2$，它等价于 $1, 2, \cdots, n / 2$，因此 $f(n) = f(n / 2) + 1$，边界是 $f(1) = 1$。

```
#include <cstdio>

const int maxn = 1e9 + 10;

int N;

int f(int n) {
    if (n == 1) return 1;
    return f(n / 2) + 1;
}

int main() {
    while (scanf("%d", &N) != EOF) {
        printf("%d\n", f(N));
    }
    return 0;
}
```

---

## 作者：Micnation_AFO (赞：0)

**题目大意**：给定一个 $n$，让你对从 $1$ 到 $n$ 的每个数进行操作，每次操作可以选择任意多个不同的数，同时减去一个任意相同的数，使得这 $n$ 个数都变为 $0$，求最少的操作次数。

**主要思路**：若需要求 $1$ 到 $x$ 的最少次数，则可以把 $x / 2 + 1$ 到 $x$ 的每个数都减去 $x / 2 + 1$，此时序列变成了：$1$，$2$，$\cdots$，$x / 2$，$0$，$1$，$\cdots$，$(x - 1) / 2$。而这个序列的最少次数就等于前一半的序列的最少次数，递归求解即可。

**Code**：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
int n;

int num(int x) {
    if (x == 1) return 1;
    return num(x / 2) + 1;
}

signed main() {
    while(1) {
        if (scanf("%lld", &n) == EOF) return 0;
        else cout << num(n) << endl;
    }
    return 0;
}

```

---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/UVA11384)

## 思路

每一次将后半段减去 $\lfloor \frac{n}{2} \rfloor$ ，得出 $1,2,3…… \frac{n}{2}$，一直减下去，最后 $-1$ 即可。

得出公式：$\lfloor \log_2 n+1 \rfloor$。

代码套用公式即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	while(cin>>n) cout<<floor(log2(n)+1)<<endl;
	return 0;
}
```
注：部分思路来自[TemplateClass](https://www.luogu.com.cn/user/735713)的题解。

---

