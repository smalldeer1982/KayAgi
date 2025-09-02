# FAST2 - Fast Sum of two to an exponent

## 题目描述

There is people that really like to do silly thinks, one of them is sum the numbers from 2^0 to 2^n, task is actually really simple, just do a ultra fast sum of term 2^0 to 2^n

## 样例 #1

### 输入

```
3\n0\n1\n2\n\n```

### 输出

```
1\n3\n7 \n\nExtra: TLE is equal to 0.15s\n```

# 题解

## 作者：zjyqwq (赞：1)

### SP11383 题解


------------
#### 题目解析

结论： $2^0 + 2^1 +...+2^{n-1} = 2^n $ 。
证明：

$2^0=1=2^1-1 $ 。

则 ：

$2^0+2^1 = 2^1-1+2^1=2 \times 2^1 -1 =2^2 -1$

$2^0+...+2^2=(2^0+2^1)+2^2=2^2-1+2^2=2 \times 2^2-1=2^3-1 $

接下去同理。

数据范围：

$n < 500$，$2^{500}$ 怎么存？

用 python。


------------
#### 代码参考
```python
n=int(input())
m=1298074214633706835075030044377087
for i in range(n):
    x=int(input())
    print((2**(x+1)-1)%m)

```


------------
PS：记得取模。



---

## 作者：hero_brine (赞：1)

题意:先输入一个正整数$t$,表示有$t$组数据等待计算。然后会输入$t$个正整数$n(0≤n≤500)$,试求出
## $\Sigma_{i=0}^{n}2^i$.
首先证明:
## $\Sigma_{i=0}^k2^i=2^{k+1}-1$
不妨设$S=\Sigma_{i=0}^k2^i$,那么$2S=\Sigma_{i=0}^k2^{i+1}=\Sigma_{i=1}^{k+1}2^i,$,故$S=2S-S=2^{k+1}-2^0=2^{k+1}-1$.

因为$0≤n≤500$ ,所以我们需要使用高精度，Ruby代码如下(代码由于过于简单不做解释):
```ruby
t = gets.to_i
for i in 1..t
	n = gets.to_i
	print (2**(n+1)-1)%1298074214633706835075030044377087
    puts("\n")
    #记得要mod
end
```
Last Update:2020.3.28  
### 此次更新是因为发现了原来题解的错误，~~不知道怎么还过了~~，没有$mod1298074214633706835075030044377087$。SPOJ还限制了提交代码的长度，所以不能打表，只能高精计算。

# 最后祝大家都能愉快地 [AC](https://www.luogu.com.cn/record/32202702) !

---

## 作者：COsm0s (赞：0)

一道数学题。

### 结论：

$2^0+2^1+...+2^{n-1}=2^n-1$。

### 证明：

设 $2^0+2^1+...+2^{n-1}=S$，

则 $2S=2^1+2^2+...+2^n$。

$S=2S-S$

$=(2^1+2^2+...+2^n)-(2^0+2^1+...+2^{n-1})$

$=2^n-2^0$

$=2^n-1$


------------
由于数据范围大到 $2^{500}$，c++ 或 pascal 代码量太大，所以我们使用 python 或 ruby 存。

下面给出 python 代码。

### Code：

```python
k=int(input())
mod=1298074214633706835075030044377087
for i in range(k):
    x=int(input())
    print((2**(x+1)-1)%mod)
```


---

## 作者：cmk666 (赞：0)

[题目链接](/problem/SP11383)

~~最短解寄念~~ ~~再整个最短题解~~

题目大意：求 $\displaystyle\sum_{i=0}^n2^i\bmod1298074214633706835075030044377087$。

使用等比数列求和公式得原式 $=(2^{i+1}-1)\bmod1298074214633706835075030044377087$。

观察到数大的一批，用 python 计算即可。

```python
for _ in range(int(input())):print((2**(int(input())+1)-1)%0x3ffffffffffffeffffffffffffff)
```

---

## 作者：Eason_AC (赞：0)

## Content
$T$ 组数据，每组数据给定一个整数 $n$，请求出下列式子的值。

$$\left(\sum\limits_{i=0}^n 2^i\right)\bmod M$$

其中 $M=1298074214633706835075030044377087$。

**数据范围：$0\leqslant n\leqslant 500$。时间限制为 $\bf 100ms$。**
## Solution
我们首先摆出一个结论：

$$\sum\limits_{i=0}^n 2^i=2^{n+1}-1$$

证明可以使用错位相减法，这里就不多讲了。

然后，由于 $n\leqslant 500$，因此这题要用到高精。这里我为了偷懒用了 Python 来实现。

这里建议直接将模数复制下来，手打容易打错。
## Code
```python
T = int(input());
while T > 0:
    n = int(input());
    print((pow(2, n + 1) - 1) % 1298074214633706835075030044377087);
    T = T - 1;
```

---

## 作者：Siteyava_145 (赞：0)

原式 $=(\sum_{i=0}^n2^i)\bmod 1298074214633706835075030044377087$

$=(2^{i+1}-1)\bmod 1298074214633706835075030044377087$

代入，得代码：
```
for i in range(int(input())):print((pow(2,int(input())+1)-1)%1298074214633706835075030044377087)
```


---

