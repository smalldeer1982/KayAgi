# 题目信息

# Omkar and Password

## 题目描述

Lord Omkar has permitted you to enter the Holy Church of Omkar! To test your worthiness, Omkar gives you a password which you must interpret!

A password is an array $ a $ of $ n $ positive integers. You apply the following operation to the array: pick any two adjacent numbers that are not equal to each other and replace them with their sum. Formally, choose an index $ i $ such that $ 1 \leq i       < n $ and $ a_{i} \neq a_{i+1} $ , delete both $ a_i $ and $ a_{i+1} $ from the array and put $ a_{i}+a_{i+1} $ in their place.

For example, for array $ [7, 4, 3, 7] $ you can choose $ i =       2 $ and the array will become $ [7, 4+3, 7] = [7, 7, 7] $ . Note that in this array you can't apply this operation anymore.

Notice that one operation will decrease the size of the password by $ 1 $ . What is the shortest possible length of the password after some number (possibly $ 0 $ ) of operations?

## 说明/提示

In the first test case, you can do the following to achieve a length of $ 1 $ :

Pick $ i=2 $ to get $ [2, 4, 1] $

Pick $ i=1 $ to get $ [6, 1] $

Pick $ i=1 $ to get $ [7] $

In the second test case, you can't perform any operations because there is no valid $ i $ that satisfies the requirements mentioned above.

## 样例 #1

### 输入

```
2
4
2 1 3 1
2
420 420```

### 输出

```
1
2```

# AI分析结果

### 题目内容
# Omkar和密码

## 题目描述
奥姆卡尔大人允许你进入奥姆卡尔神圣教堂！为了考验你的价值，奥姆卡尔给你一个密码，你必须解读它！

一个密码是一个由\(n\)个正整数组成的数组\(a\)。你对这个数组执行以下操作：选择任意两个不相等的相邻数字，并用它们的和替换它们。正式地说，选择一个索引\(i\)，使得\(1 \leq i < n\)且\(a_{i} \neq a_{i+1}\) ，从数组中删除\(a_i\)和\(a_{i+1}\)，并在它们的位置放入\(a_{i}+a_{i+1}\)。

例如，对于数组\([7, 4, 3, 7]\)，你可以选择\(i = 2\)，数组将变为\([7, 4+3, 7] = [7, 7, 7]\) 。注意，在这个数组中你不能再应用这个操作了。

注意，一次操作会使密码的长度减少\(1\)。经过若干次（可能为\(0\)次）操作后，密码的最短可能长度是多少？

## 说明/提示
在第一个测试用例中，你可以按以下步骤得到长度为\(1\)：
选择\(i=2\)得到\([2, 4, 1]\)
选择\(i=1\)得到\([6, 1]\)
选择\(i=1\)得到\([7]\)

在第二个测试用例中，你不能执行任何操作，因为不存在满足上述要求的有效\(i\)。

## 样例 #1
### 输入
```
2
4
2 1 3 1
2
420 420
```

### 输出
```
1
2
```

### 算法分类
数学

### 综合分析与结论
所有题解的核心思路均为判断数组中所有元素是否都相同，若相同则输出数组长度\(n\)，否则输出\(1\)。不同题解在具体实现方式上略有差异，例如判断元素是否相同的方式、代码风格等，但整体思路一致。各题解都成功解决了问题，不过在思路清晰度、代码可读性和优化程度上存在差异。

### 所选的题解
- **作者：_QrSn_ (5星)**
    - **关键亮点**：思路清晰，先明确题意和结论，再给出代码。代码简洁明了，通过遍历数组判断相邻元素是否相等，从而确定最终输出结果。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n;

int main() {
    cin>>q;
    for(int j=0;j<q;j++)
    {
        bool AC=true;
        cin>>n;
        int a,b;
        cin>>a;
        for(int i=1;i<n;i++)
        {
            cin>>b;
            if(b!=a)AC=false;
            a=b; 
        }
        if(AC==false)cout<<1<<endl;
        else cout<<n<<endl;
    }
    
    return 0;
}
```
    - **核心实现思想**：先读入数据组数\(q\)，对于每组数据，初始化一个布尔变量\(AC\)为\(true\)，假设数组元素全部相同。读入第一个元素\(a\)，然后遍历数组剩余元素，每次读入\(b\)，若\(b\)与\(a\)不相等，则将\(AC\)设为\(false\)，同时更新\(a\)为\(b\)。遍历结束后，根据\(AC\)的值输出结果。
- **作者：红黑树 (4星)**
    - **关键亮点**：先给出结论并进行简证，逻辑较为严谨。代码简洁，利用布尔变量记录是否存在不同元素，直接根据结果输出。
    - **重点代码**：
```cpp
#include <iostream>

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        bool diff = 0;
        cin >> n >> x;
        for (int i = 1; i < n; ++i) {
            int y;
            cin >> y;
            if (x!= y) {
                diff = 1;
            }
        }
        cout << (diff? 1 : n) << '\n';
    }
    return 0;
}
```
    - **核心实现思想**：读入数据组数\(t\)，对于每组数据，读入数组长度\(n\)和第一个元素\(x\)，初始化布尔变量\(diff\)为\(0\)。遍历数组剩余元素\(y\)，若\(y\)与\(x\)不相等，将\(diff\)设为\(1\)。最后根据\(diff\)的值输出结果。
- **作者：_Hero_ (4星)**
    - **关键亮点**：先阐述题意和分析思路，通过举例辅助理解。代码逻辑清晰，利用布尔变量标记数组元素是否完全相同。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int n,a,b;
        bool x=0;
        cin>>n;
        cin>>a;
        for(int i=1;i<n;i++)
        {
            cin>>b;
            if(a!=b)
            {
                x=1;
            }
            a=b;
        }
        if(x==1)cout<<1<<endl;
        else cout<<n<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：读入数据组数\(t\)，对于每组数据，读入数组长度\(n\)和第一个元素\(a\)，初始化布尔变量\(x\)为\(0\)。遍历数组剩余元素\(b\)，若\(a\)与\(b\)不相等，将\(x\)设为\(1\)，同时更新\(a\)为\(b\)。最后根据\(x\)的值输出结果。

### 最优关键思路或技巧
通过遍历数组判断所有元素是否相等来确定最终结果，利用布尔变量简洁地记录判断结果，这种方式在处理此类判断问题时简单有效，代码实现清晰易懂。

### 拓展思路
此类题目属于通过分析操作规则得出最终结果的数学类问题。类似套路为深入分析给定操作对数据的影响，总结出一般性规律，再通过简单判断得出结论。例如在一些数组或序列操作问题中，通过观察操作前后数据的特征变化，总结规律求解最终状态。

### 相似知识点洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合判断是否为质数，考察数学中的质数判断和组合知识。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：利用数学推导和枚举解决连续自然数和的问题，与本题通过分析规律求解结果类似。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：运用数学性质和递推关系解决斐波那契数列相关的公约数问题，同样需要挖掘数学规律。 

---
处理用时：50.73秒