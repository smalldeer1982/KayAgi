# 题目信息

# Taisia and Dice

## 题目描述

Taisia has $ n $ six-sided dice. Each face of the die is marked with a number from $ 1 $ to $ 6 $ , each number from $ 1 $ to $ 6 $ is used once.

Taisia rolls all $ n $ dice at the same time and gets a sequence of values $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 6 $ ), where $ a_i $ is the value on the upper face of the $ i $ -th dice. The sum of this sequence is equal to $ s $ .

Suddenly, Taisia's pet cat steals exactly one dice with maximum value $ a_i $ and calculates the sum of the values on the remaining $ n-1 $ dice, which is equal to $ r $ .

You only know the number of dice $ n $ and the values of $ s $ , $ r $ . Restore a possible sequence $ a $ that fulfills the constraints.

## 样例 #1

### 输入

```
7
2 2 1
2 4 2
4 9 5
5 17 11
3 15 10
4 4 3
5 20 15```

### 输出

```
1 1
2 2 
1 2 2 4
6 4 2 3 2
5 5 5
1 1 1 1
1 4 5 5 5```

# AI分析结果

### 题目内容
# 塔西娅和骰子

## 题目描述
塔西娅有\(n\)个六面骰子。每个骰子的面都标有从\(1\)到\(6\)的数字，且从\(1\)到\(6\)每个数字仅使用一次。

塔西娅同时掷出所有\(n\)个骰子，得到一个值序列\(a_1, a_2, \ldots, a_n\)（\(1 \leq a_i \leq 6\)），其中\(a_i\)是第\(i\)个骰子朝上一面的值。这个序列的和等于\(s\)。

突然，塔西娅的宠物猫偷走了恰好一个值最大的骰子，并计算出剩下\(n - 1\)个骰子的值之和，其等于\(r\)。

你只知道骰子的数量\(n\)以及\(s\)、\(r\)的值。恢复一个满足这些约束的可能序列\(a\)。

## 样例 #1
### 输入
```
7
2 2 1
2 4 2
4 9 5
5 17 11
3 15 10
4 4 3
5 20 15
```
### 输出
```
1 1
2 2 
1 2 2 4
6 4 2 3 2
5 5 5
1 1 1 1
1 4 5 5 5
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先确定被偷走的最大骰子的值为\(s - r\)，然后再分配剩下\(n - 1\)个骰子的值，使其和为\(r\)。不同之处主要在于如何分配这\(n - 1\)个骰子的值。有的题解采用平均分配并处理余数的方式，有的题解则是在平均分配的基础上，通过一些条件判断和循环来确保分配合理，避免出现值超过最大骰子值的情况。

### 所选的题解
- **作者：__Allen_123__（5星）**
    - **关键亮点**：思路清晰，代码简洁明了。通过计算平均值和余数，直接且有效地分配剩余骰子的值，代码逻辑清晰，易于理解。
    - **重点代码**：
```cpp
cout << s - r << " "; // 输出被拿走的那个骰子的点数
n--; 
int av = r / n, num = r % n; // 计算平均值，和需要输出多少个比平均值多1的数
for(int i = 1;i <= num;i++){ // 先输出r % n个平均值 + 1
    cout << av + 1 << " ";
}
for(int i = num + 1;i <= n;i++){ // 剩下的直接输出平均值即可
    cout << av << " ";
}
```
    - **核心实现思想**：先输出最大骰子的值\(s - r\)，然后计算剩余\(n - 1\)个骰子值的平均值\(av\)和余数\(num\)。通过两个循环，先输出\(num\)个\(av + 1\)，再输出\(n - num\)个\(av\)，从而构造出满足条件的序列。
- **作者：2011qiqi（4星）**
    - **关键亮点**：详细地定义了各种输入输出函数，虽然代码整体较长，但对思路的实现较为清晰，通过判断余数情况来分别处理输出，逻辑完整。
    - **重点代码**：
```cpp
re int n=read(),s=read(),r=read(),maxx=s-r,i;
print(maxx);
re int pj=(s-maxx)/(n-1);
if(pj*(n-1)==(s-maxx)){// 如果没有余数就全输出平均数
    while(--n) print(pj);
    endl;
}else{
    re int cha=(s-maxx)-pj*(n-1);// 余数
    vector<int> v;
    for(i=0;i<n-1;++i) v.EB(pj);
    i=0;
    while(cha>0){
        ++v[i++];
        --cha;
    }
    for(i=0;i<n-1;++i) print(v[i]);
    endl;
}
```
    - **核心实现思想**：先确定最大骰子值\(maxx = s - r\)并输出。然后计算剩余值的平均数\(pj\)，若没有余数则直接输出\(n - 1\)个\(pj\)；若有余数，则将余数依次加到数组\(v\)的前几个元素上，最后输出数组\(v\)。
- **作者：minVan（4星）**
    - **关键亮点**：解题思路表述简洁，代码结构清晰，通过两个循环分别对剩余骰子赋值平均数和处理余数，实现过程简单直接。
    - **重点代码**：
```cpp
cout << s - r << ' ';
for(int i = 1; i <= n - 1; i++) {
    a[i] = r / (n - 1);
}
for(int i = 1; i <= r % (n - 1); i++) {
    ++a[i];
}
for(int i = 1; i <= n - 1; i++) {
    cout << a[i] << ' ';
}
```
    - **核心实现思想**：先输出最大骰子值\(s - r\)，接着第一个循环给\(n - 1\)个数组元素赋平均值\(r / (n - 1)\)，第二个循环将余数依次加到前\(r % (n - 1)\)个元素上，最后输出数组。

### 最优关键思路或技巧
先确定最大骰子值\(s - r\)，对于剩余\(n - 1\)个骰子的值，利用数学中的除法和取余运算，将总和\(r\)平均分配到这些骰子上，并通过处理余数来确保总和准确。这种平均分配并处理余数的方式是解决此类问题的关键技巧。

### 可拓展思路
同类型题通常围绕已知总和、部分和以及一些限制条件来构造序列。类似算法套路是先确定关键值，再根据剩余条件通过数学运算来分配其他值。例如给定总和、去掉最小值后的和以及序列长度，构造满足条件的序列等。

### 洛谷相似题目推荐
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析时间分配来满足一定条件，涉及简单的数学计算和逻辑判断。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔的价格和数量，计算满足需求的最小花费，需要运用数学计算和比较。
- [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)：通过对给定数字集合进行数学运算（两两相加），判断结果是否在集合内，考察数学思维和数组操作。 

---
处理用时：63.91秒