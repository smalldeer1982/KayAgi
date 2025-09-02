# 题目信息

# Playing with GCD

## 题目描述

You are given an integer array $ a $ of length $ n $ .

Does there exist an array $ b $ consisting of $ n+1 $ positive integers such that $ a_i=\gcd (b_i,b_{i+1}) $ for all $ i $ ( $ 1 \leq i \leq n $ )?

Note that $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

## 说明/提示

In the first test case, we can take $ b=[343,343] $ .

In the second test case, one possibility for $ b $ is $ b=[12,8,6] $ .

In the third test case, it can be proved that there does not exist any array $ b $ that fulfills all the conditions.

## 样例 #1

### 输入

```
4
1
343
2
4 2
3
4 2 4
4
1 1 1 1```

### 输出

```
YES
YES
NO
YES```

# AI分析结果

### 题目重写

#### 题目描述

给定一个长度为 $n$ 的整数数组 $a$。

是否存在一个长度为 $n+1$ 的正整数数组 $b$，使得对于所有的 $i$（$1 \leq i \leq n$），都有 $a_i = \gcd(b_i, b_{i+1})$？

注意，$\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的最大公约数。

#### 说明/提示

在第一个测试用例中，我们可以取 $b=[343,343]$。

在第二个测试用例中，$b$ 的一个可能取值是 $b=[12,8,6]$。

在第三个测试用例中，可以证明不存在满足所有条件的数组 $b$。

#### 样例 #1

##### 输入

```
4
1
343
2
4 2
3
4 2 4
4
1 1 1 1
```

##### 输出

```
YES
YES
NO
YES
```

### 算法分类

构造、数学

### 题解分析与结论

题解的核心思路是通过构造数组 $b$，使得 $b_i$ 是 $a_{i-1}$ 和 $a_i$ 的最小公倍数，然后验证是否满足 $a_i = \gcd(b_i, b_{i+1})$。大多数题解都采用了这一思路，但在实现细节和优化上有所不同。

### 精选题解

#### 题解1：作者：jwsdy (赞：10)

**星级：5星**

**关键亮点：**
- 详细解释了构造数组 $b$ 的思路，即 $b_i$ 应为 $a_{i-1}$ 和 $a_i$ 的最小公倍数。
- 使用了辗转相除法求最大公约数，代码简洁且高效。
- 在构造完数组 $b$ 后，进行了严格的验证，确保构造的数组满足题目要求。

**核心代码：**
```cpp
int gcd(int a, int b){
	if(a%b==0) return b;
	return gcd(b,a%b);
}

for(int i=1;i<=n+1;i++)
	b[i]=a[i]*a[i-1]/gcd(a[i],a[i-1]);

bool r=1;
for(int i=1;i<=n;i++){
	if(gcd(b[i],b[i+1])!=a[i]){
		cout<<"NO"<<endl;
		r=0;
		break;
	}
}
if(r) cout<<"YES"<<endl;
```

#### 题解2：作者：Larryyu (赞：8)

**星级：4星**

**关键亮点：**
- 同样采用了构造数组 $b$ 的思路，代码简洁明了。
- 使用了 `__gcd` 函数来求最大公约数，减少了代码量。
- 在验证部分，直接遍历数组 $b$ 并检查是否满足条件，逻辑清晰。

**核心代码：**
```cpp
for(int i=1;i<=n+1;i++)
	b[i]=a[i]*a[i-1]/__gcd(a[i],a[i-1]);

bool f=0;
for(int i=1;i<=n;i++){
	if(__gcd(b[i],b[i+1])!=a[i]){
		cout<<"NO"<<endl;
		f=1;
		break;
	}
}
if(!f) cout<<"YES"<<endl;
```

#### 题解3：作者：Lemansky (赞：3)

**星级：4星**

**关键亮点：**
- 提出了一个优化判断的思路，即在 $n \geq 3$ 时，通过检查 $a_{i+1}$ 是否为 $\gcd(a_{i-2}, a_i)$ 的倍数来判断是否有解。
- 代码实现简洁，减少了不必要的循环遍历。

**核心代码：**
```cpp
for(int i=3;i<=n;i++){
	scanf("%d",&a[i]);
	if(a[i-1]%__gcd(a[i-2],a[i])!=0) f=0;
}
puts(f?"YES":"NO");
```

### 最优关键思路

通过构造数组 $b$，使得 $b_i$ 是 $a_{i-1}$ 和 $a_i$ 的最小公倍数，然后验证是否满足 $a_i = \gcd(b_i, b_{i+1})$。这一思路简洁高效，且易于实现。

### 可拓展之处

类似的问题可以通过构造和验证的思路来解决，特别是在涉及最大公约数和最小公倍数的题目中。例如，可以拓展到更复杂的数组构造问题，或者涉及多个数组的交互问题。

### 推荐题目

1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P1447 最大公约数](https://www.luogu.com.cn/problem/P1447)

---
处理用时：29.77秒