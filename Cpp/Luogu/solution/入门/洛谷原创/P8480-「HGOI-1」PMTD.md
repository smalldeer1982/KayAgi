# 「HGOI-1」PMTD

## 题目背景

 $\text{uuku}$ 在学习[四则运算](https://baike.baidu.com/item/%E5%9B%9B%E5%88%99%E8%BF%90%E7%AE%97/5337481?fr=aladdin)！

## 题目描述

为了验证 $\text{uuku}$ 学习成果，$\text{bh1234666}$ 给出一个长为 $n$ 整数序列 $a_i$。并让 $\text{uuku}$ 给这个序列进行 $m$ 次操作。

每次操作可以任意选择序列中一个数 $a_i$，令 $a_i$ 变成 $a_i+2$，$a_i-2$，$a_i\times 2$，$\lfloor\frac{a_i}{2}\rfloor$ 这四个结果中的一个。

$\text{bh1234666}$ 希望 $m$ 次操作后，整个序列的极差（最大值减最小值）最大。

显然 $\text{uuku}$ 没有认真学习，所以他希望你来帮他回答这个问题。

## 说明/提示

#### 样例解释

第一步操作：将 $1$ 加上 $2$ 得到 $3$。

第二步操作：将 $3$ 乘以 $2$ 得到 $6$。

极差为 $6-0=6$。

#### 数据范围

本题采用**捆绑测试**，共有 $2$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \textbf{特殊限制} \cr\hline
1 & 40 & n \le 5,m \le 5 \cr\hline
2 & 60 &  \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$2 \le n \le 10^6$，$1 \le m \le 10$，$0 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
3 2
0 1 0 ```

### 输出

```
6```

# 题解

## 作者：uuku (赞：33)

设当前的最大值为 $mx$，最小值为 $mn$。为了让极差变大，我们显然是只操作这两个数。并且一定是让 $mx$ 变大，$mn$ 变小。

所以我们只可能进行这四个操作：

1. $mx:=mx+2$。
2. $mx:=mx\times 2$。
3. $mn:=mn-2$。
4. $mn:=\lfloor \dfrac {mn}{2}\rfloor$。

下面我们就来考虑那种操作对答案的贡献更大：

设一次操作对答案的贡献为 $dlt$。

那么这四种操作的贡献分别为：

1. $dlt_1=2$。
2. $dlt_2=mx$。
3. $dlt_3=2$。
4. $dlt_4=mn-\lfloor \dfrac{mn}{2}\rfloor$。

显然有 $dlt_4\le mn \le mx=dlt_2$。所以操作 $4$ 不可能进行。也就意味着如果我们改变最小值，每次操作最多将答案 $+2$。而如果改变最大值，每次操作至少可以让答案 $+2$。所以我们只要操作最大值就可以了。

下面我们考虑如何选取 $1$ 和 $2$ 操作。

不难发现，当 $mx>2$ 时，进行 $2$ 操作更优。当 $mx=2$ 时，两种操作效果一样。当 $mx<2$ 时，进行 $1$ 操作更优。

并且当进行一次 $1$ 操作后必然有 $mx\ge2$。

所以我们只需要记录初始序列的最大值和最小值，如果最大值小于 $2$，就先将其 $+2$，然后不断的对最大值进行 $\times 2$ 操作即可。

下面是 $\text{std}$：

```cpp
#include<cstdio>
int n,val,mx,mn=1e9,m;
int main()
{
	scanf("%d%d",&n,&m);
	while(n--)
	{
		scanf("%d",&val);
		if(val>mx)mx=val;
		if(val<mn)mn=val;
	}
	if(mx<2)mx+=2,m--;
	printf("%lld",((1ll*mx)<<m)-mn);
	return 0;
}
```

---

