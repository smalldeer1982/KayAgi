# 题目信息

# Numbers

## 题目描述

Little Petya likes numbers a lot. He found that number 123 in base 16 consists of two digits: the first is 7 and the second is 11. So the sum of digits of 123 in base 16 is equal to 18.

Now he wonders what is an average value of sum of digits of the number $ A $ written in all bases from $ 2 $ to $ A-1 $ .

Note that all computations should be done in base 10. You should find the result as an irreducible fraction, written in base 10.

## 说明/提示

In the first sample number 5 written in all bases from 2 to 4 looks so: 101, 12, 11. Sums of digits are 2, 3 and 2, respectively.

## 样例 #1

### 输入

```
5
```

### 输出

```
7/3
```

## 样例 #2

### 输入

```
3
```

### 输出

```
2/1
```

# AI分析结果

### 题目翻译
# 数字

## 题目描述
小佩蒂亚非常喜欢数字。他发现，十进制数 123 转换为十六进制后由两位数字组成：第一位是 7，第二位是 11。因此，123 在十六进制下各位数字之和等于 18。

现在他想知道，将数字 $A$ 转换为从 2 到 $A - 1$ 的所有进制后，各位数字之和的平均值是多少。

请注意，所有计算都应在十进制下进行。你应该将结果表示为最简分数，用十进制表示。

## 说明/提示
在第一个样例中，数字 5 转换为从 2 到 4 的所有进制后分别为：101、12、11。各位数字之和分别为 2、3 和 2。

## 样例 #1
### 输入
```
5
```
### 输出
```
7/3
```

## 样例 #2
### 输入
```
3
```
### 输出
```
2/1
```

### 综合分析与结论
这些题解的核心思路都是先将数字 $A$ 转换为从 2 到 $A - 1$ 的所有进制，计算各位数字之和，再求平均值并化为最简分数。算法要点包括进制转换和求最大公约数（gcd）。
- **思路对比**：所有题解思路基本一致，只是在代码实现和细节处理上有所不同。
- **算法要点**：
    - **进制转换**：通过不断取余和整除操作，将十进制数转换为指定进制，并累加各位数字。
    - **求最大公约数**：用于将结果化为最简分数，多数使用辗转相除法。
- **解决难点**：主要难点在于进制转换和结果的约分，各题解都通过取余和 gcd 函数解决。

### 所选题解
- **作者：BYWYR (赞：7) - 5星**
    - **关键亮点**：思路清晰，代码结构简单，注释详细，便于理解。
    - **核心代码**：
```cpp
int gcd(int big,int small){
    if(small==0) return big;
    return gcd(small,big%small);
}
int deal(int k,int x){
    int sum=0;
    while(x>0){
        sum+=x%k;
        x/=k;
    }
    return sum;
}
```
- **作者：PC_DOS (赞：2) - 4星**
    - **关键亮点**：使用 `ios::sync_with_stdio(false)` 加速输入输出，代码规范，变量命名清晰。
    - **核心代码**：
```cpp
long long GetGreatestCommonDivision(long long iNum1, long long iNum2){
    if (iNum2 == 0)
        return iNum1;
    else
        return GetGreatestCommonDivision(iNum2, iNum1%iNum2);
}
```
- **作者：LYR_ (赞：1) - 4星**
    - **关键亮点**：使用 C++ 自带的 `__gcd` 函数，代码简洁。
    - **核心代码**：
```cpp
int jz(int x,int p) {
    int s=0,a;
    while(x>0) {
        a=x%p;
        s+=a;
        x/=p;
    }
    return s;
}
```

### 最优关键思路或技巧
- **进制转换**：通过取余和整除操作，不断提取各位数字并累加，实现十进制到指定进制的转换。
- **求最大公约数**：使用辗转相除法，递归或迭代实现，将结果化为最简分数。

### 可拓展之处
同类型题可能涉及不同进制之间的转换、多进制下的运算等。类似算法套路包括处理不同数制的问题，都可以通过取余和整除操作进行转换。

### 洛谷推荐题目
1. P1143 进制转换：https://www.luogu.com.cn/problem/P1143
2. P1017 进制转换2：https://www.luogu.com.cn/problem/P1017
3. P2084 进制转换：https://www.luogu.com.cn/problem/P2084

### 个人心得
题解中未包含个人心得。

---
处理用时：21.60秒