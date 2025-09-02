# 题目信息

# Masha and Bears

## 题目描述

A family consisting of father bear, mother bear and son bear owns three cars. Father bear can climb into the largest car and he likes it. Also, mother bear can climb into the middle car and she likes it. Moreover, son bear can climb into the smallest car and he likes it. It's known that the largest car is strictly larger than the middle car, and the middle car is strictly larger than the smallest car.

Masha came to test these cars. She could climb into all cars, but she liked only the smallest car.

It's known that a character with size $ a $ can climb into some car with size $ b $ if and only if $ a<=b $ , he or she likes it if and only if he can climb into this car and $ 2a>=b $ .

You are given sizes of bears and Masha. Find out some possible integer non-negative sizes of cars.

## 说明/提示

In first test case all conditions for cars' sizes are satisfied.

In second test case there is no answer, because Masha should be able to climb into smallest car (so size of smallest car in not less than 21), but son bear should like it, so maximum possible size of it is 20.

## 样例 #1

### 输入

```
50 30 10 10
```

### 输出

```
50
30
10
```

## 样例 #2

### 输入

```
100 50 10 21
```

### 输出

```
-1
```

# AI分析结果

### 题目中文重写
# Masha和熊

## 题目描述
一个由熊爸爸、熊妈妈和熊宝宝组成的家庭拥有三辆车。熊爸爸可以钻进最大的那辆车，并且他喜欢这辆车。此外，熊妈妈可以钻进中等大小的车，并且她喜欢这辆车。而且，熊宝宝可以钻进最小的车，并且他喜欢这辆车。已知最大的车严格大于中等大小的车，中等大小的车严格大于最小的车。

玛莎（Masha）来测试这些车。她可以钻进所有的车，但她只喜欢最小的那辆车。

已知一个身高为 $a$ 的角色可以钻进大小为 $b$ 的车，当且仅当 $a \leq b$；他或她喜欢这辆车，当且仅当他能钻进这辆车且 $2a \geq b$。

给定熊和玛莎的身高，找出一些可能的非负整数的车的大小。

## 说明/提示
在第一个测试用例中，所有关于车大小的条件都满足。

在第二个测试用例中，没有答案，因为玛莎应该能够钻进最小的车（所以最小的车的大小不小于 21），但熊宝宝应该喜欢它，所以它的最大可能大小是 20。

## 样例 #1
### 输入
```
50 30 10 10
```
### 输出
```
50
30
10
```

## 样例 #2
### 输入
```
100 50 10 21
```
### 输出
```
-1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先判断无解的情况，再找出有解时车大小的取值。无解情况主要围绕玛莎、小熊和母熊的身高关系展开，有解时大车和中车一般取公熊和母熊身高的两倍，小车取小熊和玛莎身高的最大值。各题解的算法要点和解决难点基本一致，只是在代码实现和思路阐述的详细程度上有所差异。

### 所选题解
- **作者：信息向阳花木（4星）**
    - **关键亮点**：思路清晰，分无解情况和有解情况详细阐述，代码可读性高，解释了每个步骤的原因，即使是新手也容易理解。
- **作者：YUYGFGG（4星）**
    - **关键亮点**：思路简洁明了，直接列出关键条件，代码简洁，能快速解决问题。
- **作者：zplqwq（4星）**
    - **关键亮点**：对不满足的情况和满足的情况分析清晰，代码结构清晰，注释明确。

### 重点代码
```cpp
// 以信息向阳花木的代码为例
#include <iostream>
using namespace std;
int v1,v2,v3,vm;
int main() {
    cin>>v1>>v2>>v3>>vm;
    if(vm>2*v3||v3>2*vm||v2<=vm) {
        cout<<-1<<endl;
    }
    else {
        cout<<2*v1<<endl<<2*v2<<endl<<max(v3,vm)<<endl;
    }
    return 0;
}
```
**核心实现思想**：先读取公熊、母熊、小熊和玛莎的身高，然后判断是否满足无解的条件（玛莎身高大于小熊身高两倍、小熊身高大于玛莎身高两倍、母熊身高不大于玛莎身高），若满足则输出 -1，否则输出大车（公熊身高两倍）、中车（母熊身高两倍）、小车（小熊和玛莎身高的最大值）的大小。

### 最优关键思路或技巧
- **反向思考**：不直接去求车的大小，而是先找出无解的情况，再确定有解时的取值，简化了问题的解决过程。
- **合理取值**：有解时，大车和中车取对应熊身高的两倍，小车取小熊和玛莎身高的最大值，既满足条件又方便计算。

### 拓展思路
同类型题可能会改变角色和车的数量，或者修改能钻进车和喜欢车的条件，但解题思路类似，都是先分析不满足的情况，再找出满足条件的取值。

### 推荐洛谷题目
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
- [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)

### 个人心得
无

---
处理用时：31.69秒