# 题目信息

# LCM Challenge

## 题目描述

Some days ago, I learned the concept of LCM (least common multiple). I've played with it for several times and I want to make a big number with it.

But I also don't want to use many numbers, so I'll choose three positive integers (they don't have to be distinct) which are not greater than $ n $ . Can you help me to find the maximum possible least common multiple of these three integers?

## 说明/提示

The least common multiple of some positive integers is the least positive integer which is multiple for each of them.

The result may become very large, 32-bit integer won't be enough. So using 64-bit integers is recommended.

For the last example, we can chose numbers $ 7 $ , $ 6 $ , $ 5 $ and the LCM of them is $ 7·6·5=210 $ . It is the maximum value we can get.

## 样例 #1

### 输入

```
9
```

### 输出

```
504
```

## 样例 #2

### 输入

```
7
```

### 输出

```
210
```

# AI分析结果

### 题目内容
# LCM挑战

## 题目描述
几天前，我学习了最小公倍数（LCM）的概念。我已经对它把玩了好几次，并且想用它来得到一个大数字。

但我也不想使用太多数字，所以我会选择三个不大于 $n$ 的正整数（它们不必不同）。你能帮我找到这三个整数的最大可能最小公倍数吗？

## 说明/提示
一些正整数的最小公倍数是能被它们中每一个整除的最小正整数。

结果可能会变得非常大，32位整数是不够的。所以建议使用64位整数。

对于最后一个例子，我们可以选择数字 $7$、$6$、$5$，它们的最小公倍数是 $7×6×5 = 210$。这是我们能得到的最大值。

## 样例 #1
### 输入
```
9
```
### 输出
```
504
```

## 样例 #2
### 输入
```
7
```
### 输出
```
210
```

### 综合分析与结论
这几道题解主要围绕如何通过数论知识优化算法，避免暴力枚举的 $O(n^3)$ 时间复杂度。思路核心在于根据 $n$ 的奇偶性分类讨论，利用数论中互质等性质找出乘积最大且两两互质的三个数，以得到最大的最小公倍数。
1. **思路**：大部分题解先明确暴力枚举不可行，然后依据数论知识，通过分析 $n$ 的奇偶性来寻找最大最小公倍数。奇数时，$n$，$n - 1$，$n - 2$ 两两互质，其乘积即为最大最小公倍数；偶数时稍复杂，需考虑 $n$ 与 $n - 3$ 是否互质等情况。
2. **算法要点**：利用数论中相邻数互质、奇数与间隔为2的奇数互质等性质，结合最小公倍数公式 $lcm(n,m)=n*m/gcd(n,m)$ 来计算。
3. **解决难点**：关键在于全面且准确地分情况讨论，特别是偶数情况下，要考虑多种子情况，如 $n$ 与 $n - 3$ 是否互质、$n$ 是否为6的倍数等，避免遗漏导致结果错误。

### 所选的题解
1. **作者：chinaxjh (5星)**
    - **关键亮点**：对推导过程解析详细，从最大公约数定理引入，逐步分析不同情况下如何得出最大最小公倍数，逻辑清晰。代码虽用Pascal，但注释详细，易理解。
    - **个人心得**：无
    - **核心代码**：
```pascal
function gcd(x,y:int64):int64;
begin
  if y=0 then exit(x);
  exit(gcd(y,x mod y));
end;
begin
  readln(n);
  if n<3 then
  begin
  writeln(n);
  halt;
  end;
  if n mod 2=1 then
  begin
   writeln(n*(n-1)*(n-2));
halt;
end;
  max:=(n-1)*(n-2)*(n-3);
  i:=n;
  j:=n-1;
  k:=n-3;
  lcm:=i*j div gcd(i,j);
  lcm:=lcm*k div gcd(lcm,k);
  if lcm>max then max:=lcm;
  writeln(max);
end.
```
    - **核心思想**：先特判 $n < 3$ 的情况，再根据 $n$ 的奇偶性分别计算。奇数时直接输出 $n*(n - 1)*(n - 2)$；偶数时，先计算 $(n - 1)*(n - 2)*(n - 3)$ 作为一种情况，再计算 $n$，$n - 1$，$n - 3$ 的最小公倍数并与前一种情况比较取大值。
2. **作者：FCB_Yiyang2006✈ (4星)**
    - **关键亮点**：先阐述做本题需掌握的知识及小引理，得出三个数的 $lcm$ 与三数乘积和两两之间的 $gcd$ 有关的结论，再分奇偶情况详细讨论，代码注释详细且考虑多种细节。
    - **个人心得**：无
    - **核心代码**：
```cpp
long long Max(long long a,long long b)
{
	if(a>b)
	{
		return a;
	}
	return b;
}
int main()
{
	scanf("%lld",&n);
	if(n==1)
	{
		printf("1");
		return 0;
	}
	if(n==2)
	{
		printf("2");
		return 0;
	}
	if(n%2==1)
	{
		printf("%lld",n*(n-1)*(n-2));
	}
	else
	{
		if(n%3!=0)
		{
			printf("%lld",Max(n*(n-1)*(n-2)/2,n*(n-1)*(n-3)));
		}
		else
		{
			printf("%lld",Max(n*(n-1)*(n-2)/2,Max((n-1)*(n-2)*(n-3),n*(n-2)*(n-3)/3)));
		}
	}
	return 0;
}
```
    - **核心思想**：先特判 $n$ 为1和2的情况，奇数时直接输出 $n*(n - 1)*(n - 2)$；偶数时，再根据 $n$ 是否能被3整除，分别比较不同组合计算出的最小公倍数并输出最大值。
3. **作者：alan1118 (4星)**
    - **关键亮点**：思路简洁清晰，直接说明不能选相同数，根据 $n$ 的奇偶性及 $n$ 是否为6的倍数，快速得出结果，代码简短高效。
    - **个人心得**：无
    - **核心代码**：
```cpp
int main()
{
    long long n;
    cin >> n;
    if(n < 3) return cout << n << endl, 0;
    if(!(n % 2))
    {
        if(n % 6) return cout << n*(n-1)*(n-3) << endl, 0;
        else return cout << (n-1)*(n-2)*(n-3) << endl, 0;
    }
    else return cout << n*(n-1)*(n-2) << endl, 0;
    return 0;
}
```
    - **核心思想**：特判 $n < 3$ 的情况，偶数时判断 $n$ 是否为6的倍数，分别输出不同的结果；奇数时直接输出 $n*(n - 1)*(n - 2)$。

### 最优关键思路或技巧
1. **数论性质运用**：利用数论中关于互质的性质，如相邻数互质、奇数与间隔为2的奇数互质等，快速确定可能得到最大最小公倍数的数字组合，避免暴力枚举。
2. **分类讨论**：根据 $n$ 的奇偶性细致分类，对于偶数情况进一步根据是否能被3整除等条件细分，全面考虑各种情况，准确得出结果。

### 可拓展之处
此类题目属于数论与优化算法结合的类型，类似套路是先分析数据范围排除暴力解法，然后利用数论知识如最大公约数、最小公倍数性质及互质关系，通过分类讨论优化算法。同类型题可围绕不同数论性质及条件变化展开，如改变数字个数、限定数字取值范围的条件等。

### 洛谷相似题目推荐
1. **P1029 最大公约数和最小公倍数问题**：通过给定的最大公约数和最小公倍数，反推满足条件的数对数量，考察对最大公约数和最小公倍数概念及关系的理解。
2. **P1572 计算分数的最大公约数和最小公倍数**：涉及分数形式下最大公约数和最小公倍数的计算，拓展对相关概念在不同数据形式下的应用。
3. **P2602 数字计数**：在一定数字范围内，统计包含特定数字的数的个数，其中可能会用到数论相关知识辅助优化计数过程，锻炼数论与计数问题结合的能力。 

---
处理用时：36.19秒