# 题目信息

# Make Good

## 题目描述

Let's call an array $ a_1, a_2, \dots, a_m $ of nonnegative integer numbers good if $ a_1 + a_2 + \dots + a_m = 2\cdot(a_1 \oplus a_2 \oplus \dots \oplus a_m) $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

For example, array $ [1, 2, 3, 6] $ is good, as $ 1 + 2 + 3 + 6 = 12 = 2\cdot 6 = 2\cdot (1\oplus 2 \oplus 3 \oplus 6) $ . At the same time, array $ [1, 2, 1, 3] $ isn't good, as $ 1 + 2 + 1 + 3 = 7 \neq 2\cdot 1 = 2\cdot(1\oplus 2 \oplus 1 \oplus 3) $ .

You are given an array of length $ n $ : $ a_1, a_2, \dots, a_n $ . Append at most $ 3 $ elements to it to make it good. Appended elements don't have to be different. It can be shown that the solution always exists under the given constraints. If there are different solutions, you are allowed to output any of them. Note that you don't have to minimize the number of added elements!. So, if an array is good already you are allowed to not append elements.

## 说明/提示

In the first test case of the example, the sum of all numbers is $ 12 $ , and their $ \oplus $ is $ 6 $ , so the condition is already satisfied.

In the second test case of the example, after adding $ 4, 4 $ , the array becomes $ [8, 4, 4] $ . The sum of numbers in it is $ 16 $ , $ \oplus $ of numbers in it is $ 8 $ .

## 样例 #1

### 输入

```
3
4
1 2 3 6
1
8
2
1 1
```

### 输出

```
0

2
4 4
3
2 6 2
```

# AI分析结果

### 题目内容（中文重写）
# 构造良好数组

## 题目描述
我们称一个由非负整数组成的数组 $ a_1, a_2, \dots, a_m $ 是良好的，如果 $ a_1 + a_2 + \dots + a_m = 2\cdot(a_1 \oplus a_2 \oplus \dots \oplus a_m) $ ，其中 $ \oplus $ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

例如，数组 $ [1, 2, 3, 6] $ 是良好的，因为 $ 1 + 2 + 3 + 6 = 12 = 2\cdot 6 = 2\cdot (1\oplus 2 \oplus 3 \oplus 6) $ 。而数组 $ [1, 2, 1, 3] $ 不是良好的，因为 $ 1 + 2 + 1 + 3 = 7 \neq 2\cdot 1 = 2\cdot(1\oplus 2 \oplus 1 \oplus 3) $ 。

给定一个长度为 $ n $ 的数组 $ a_1, a_2, \dots, a_n $ ，你需要向其中最多追加 3 个元素（追加的元素可以相同），使其变为良好数组。可以证明，在给定的约束条件下，解总是存在的。如果有不同的解，你可以输出任意一个。注意，你不需要最小化添加元素的数量！所以，如果一个数组本身已经是良好的，你可以不追加元素。

## 说明/提示
在样例的第一个测试用例中，所有数字的和是 12，它们的异或和是 6，所以条件已经满足。

在样例的第二个测试用例中，添加 4, 4 后，数组变为 $ [8, 4, 4] $ 。数组中数字的和是 16，异或和是 8。

## 样例 #1
### 输入
```
3
4
1 2 3 6
1
8
2
1 1
```
### 输出
```
0

2
4 4
3
2 6 2
```

### 算法分类
构造

### 综合分析与结论
这些题解大多围绕构造满足条件的数组展开。核心思路是利用异或运算的性质：$x \oplus x = 0$ 和 $0 \oplus x = x$ 。先计算原数组的异或和 $sumx$ 与和 $sums$ ，然后通过添加 $sumx$ 和 $sumx + sums$ 这两个数，使得新数组满足总和等于异或和的 2 倍。不同题解在代码实现和思路阐述的详细程度上有所差异，但整体思路一致。

### 所选题解
- **作者：Fearliciz (赞：5)，4星**
    - **关键亮点**：思路清晰，先介绍异或运算的基本性质，再逐步推导如何构造满足条件的数组，代码简洁易懂。
    - **个人心得**：无
- **作者：EXODUS (赞：3)，4星**
    - **关键亮点**：详细分析了异或和为 0 以及如何将异或和变为 0 这两种情况，逻辑严谨，代码规范。
    - **个人心得**：学弟一眼秒了，自己想了很久，感慨被打击到。
- **作者：天南月 (赞：3)，4星**
    - **关键亮点**：分享了自己的思考过程，从错误方向到找到正解，最后简洁地给出构造方法。
    - **个人心得**：一开始朝线性基方向思考无果，又找和与异或和的关系也无果，知道正解后很无奈。

### 重点代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int T,n,ans,x,cnt;
    cin>>T;
    while(T--){
        ans=0;
        cnt=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>x;
            ans^=x;
            cnt+=x;
        }   
        cout<<2<<endl<<ans<<" "<<(cnt+ans)<<endl;
    }
    return 0;
}
```
**核心实现思想**：先读取测试用例的数量 $T$ ，对于每个测试用例，读取数组的长度 $n$ ，同时计算数组的异或和 $ans$ 与和 $cnt$ ，最后输出需要添加的两个数 $ans$ 和 $ans + cnt$ 。

### 可拓展之处
同类型题可能会改变构造的条件，例如要求总和等于异或和的 $k$ 倍，或者限制添加元素的数量等。类似算法套路是利用位运算的性质进行构造，通过分析位运算的特点来找到满足条件的构造方法。

### 推荐洛谷题目
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)：考察异或运算的基本性质。
2. [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)：涉及高精度和位运算。
3. [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)：与数学和构造相关。

---
处理用时：40.17秒