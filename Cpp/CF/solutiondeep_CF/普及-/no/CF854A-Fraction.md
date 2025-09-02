# 题目信息

# Fraction

## 题目描述

Petya is a big fan of mathematics, especially its part related to fractions. Recently he learned that a fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF854A/9f8335062cbc9ed9ecb9607f5d06d53170cb1e1a.png) is called proper iff its numerator is smaller than its denominator ( $ a<b $ ) and that the fraction is called irreducible if its numerator and its denominator are coprime (they do not have positive common divisors except $ 1 $ ).

During his free time, Petya thinks about proper irreducible fractions and converts them to decimals using the calculator. One day he mistakenly pressed addition button ( $ + $ ) instead of division button ( $ ÷ $ ) and got sum of numerator and denominator that was equal to $ n $ instead of the expected decimal notation.

Petya wanted to restore the original fraction, but soon he realized that it might not be done uniquely. That's why he decided to determine maximum possible proper irreducible fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF854A/9f8335062cbc9ed9ecb9607f5d06d53170cb1e1a.png) such that sum of its numerator and denominator equals $ n $ . Help Petya deal with this problem.

## 样例 #1

### 输入

```
3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
4
```

### 输出

```
1 3
```

## 样例 #3

### 输入

```
12
```

### 输出

```
5 7
```

# AI分析结果

### 题目翻译
### 分数

#### 题目描述
Petya 是数学的忠实粉丝，尤其喜欢与分数相关的部分。最近他了解到，当一个分数 $\frac{a}{b}$ 的分子小于分母（$a < b$）时，这个分数被称为真分数；当分子和分母互质（除了 1 以外没有正的公因数）时，这个分数被称为最简分数。

在空闲时间里，Petya 会思考最简真分数，并使用计算器将它们转换为小数。有一天，他误按了加号（$+$）而不是除号（$÷$），得到分子和分母的和等于 $n$，而不是预期的小数结果。

Petya 想还原原来的分数，但很快他意识到这可能无法唯一确定。因此，他决定找出最大的最简真分数 $\frac{a}{b}$，使得其分子和分母的和等于 $n$。请帮助 Petya 解决这个问题。

#### 样例 #1
##### 输入
```
3
```
##### 输出
```
1 2
```

#### 样例 #2
##### 输入
```
4
```
##### 输出
```
1 3
```

#### 样例 #3
##### 输入
```
12
```
##### 输出
```
5 7
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕寻找最大的最简真分数 $\frac{a}{b}$，使得 $a + b = n$ 展开。题解思路大致分为两类：
1. **数学推导分类讨论**：通过对 $n$ 分奇数、偶数，偶数再细分是否为 4 的倍数等情况，利用数论知识推导得出结果。这种方法时间复杂度低，为 $O(1)$，但需要较强的数学分析能力。
2. **枚举法**：从 $\frac{n}{2}$ 开始向下枚举分子 $i$，分母为 $n - i$，判断 $i$ 和 $n - i$ 是否互质，若互质则输出。这种方法思路简单，但时间复杂度为 $O(n \log n)$，因为每次判断互质需要 $O(\log n)$ 的时间。

### 所选题解
- **作者：brealid（5星）**
    - **关键亮点**：详细地对 $n$ 分情况进行数学推导，给出每种情况的可行性和最优性证明，逻辑严谨，思路清晰。
- **作者：hensier（4星）**
    - **关键亮点**：同样对 $n$ 进行分类讨论，利用位运算提高代码效率，给出了详细的推理过程和结论。
- **作者：Ousmane_Dembele（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用递归的方式实现 gcd 算法，易于理解。

### 重点代码
#### 数学推导分类讨论（作者：brealid）
```cpp
// n 为奇数时
if (n % 2 == 1) {
    cout << (n - 1) / 2 << " " << (n + 1) / 2 << endl;
} 
// n 为偶数但不为 4 的倍数
else if (n % 4 != 0) {
    cout << n / 2 - 2 << " " << n / 2 + 2 << endl;
} 
// n 为偶数且为 4 的倍数
else {
    cout << n / 2 - 1 << " " << n / 2 + 1 << endl;
}
```
**核心实现思想**：根据 $n$ 的不同情况，直接计算出分子和分母的值，时间复杂度为 $O(1)$。

#### 枚举法（作者：Ousmane_Dembele）
```cpp
int gcd(int p, int q) {return q==0?p:gcd(q,p%q);}//gcd算法
long long ans,n;//int也行
int main(){
    cin>>n;
    for(int i=n/2;i>=1;i--){//遍历
        if(gcd(i,n-i)==1){//互质
            cout<<i<<" "<<n-i;//输出
            return 0;
        }
    }
    return 0;
}
```
**核心实现思想**：从 $\frac{n}{2}$ 开始向下枚举分子 $i$，计算分母 $n - i$，使用 gcd 函数判断 $i$ 和 $n - i$ 是否互质，若互质则输出结果。

### 关键思路或技巧
- **数学推导**：通过对 $n$ 进行分类讨论，利用数论知识推导得出结果，可将时间复杂度优化到 $O(1)$。
- **枚举优化**：从 $\frac{n}{2}$ 开始向下枚举，能更快找到最大的最简真分数。
- **位运算**：使用位运算（如 `n & 1` 判断奇数，`n >> 1` 代替 `n / 2`）可提高代码效率。

### 拓展思路
同类型题目可能会改变条件，如要求最小的最简真分数，或者分子分母之和在某个范围内等。解题思路仍可围绕数学推导和枚举展开，根据具体条件进行调整。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)
3. [P2651 添加括号III](https://www.luogu.com.cn/problem/P2651)

### 个人心得
部分题解提到了 `__gcd` 函数在竞赛中可能会被判 CE，提醒我们在竞赛中要慎用，最好自己实现 gcd 算法。 

---
处理用时：34.45秒