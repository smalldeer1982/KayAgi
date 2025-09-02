# 题目信息

# Nastia and a Good Array

## 题目描述

Nastia has received an array of $ n $ positive integers as a gift.

She calls such an array $ a $ good that for all $ i $ ( $ 2 \le i \le n $ ) takes place $ gcd(a_{i - 1}, a_{i}) = 1 $ , where $ gcd(u, v) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ u $ and $ v $ .

You can perform the operation: select two different indices $ i, j $ ( $ 1 \le i, j \le n $ , $ i \neq j $ ) and two integers $ x, y $ ( $ 1 \le x, y \le 2 \cdot 10^9 $ ) so that $ \min{(a_i, a_j)} = \min{(x, y)} $ . Then change $ a_i $ to $ x $ and $ a_j $ to $ y $ .

The girl asks you to make the array good using at most $ n $ operations.

It can be proven that this is always possible.

## 说明/提示

Consider the first test case.

Initially $ a = [9, 6, 3, 11, 15] $ .

In the first operation replace $ a_1 $ with $ 11 $ and $ a_5 $ with $ 9 $ . It's valid, because $ \min{(a_1, a_5)} = \min{(11, 9)} = 9 $ .

After this $ a = [11, 6, 3, 11, 9] $ .

In the second operation replace $ a_2 $ with $ 7 $ and $ a_5 $ with $ 6 $ . It's valid, because $ \min{(a_2, a_5)} = \min{(7, 6)} = 6 $ .

After this $ a = [11, 7, 3, 11, 6] $ — a good array.

In the second test case, the initial array is already good.

## 样例 #1

### 输入

```
2
5
9 6 3 11 15
3
7 5 13```

### 输出

```
2
1 5 11 9
2 5 7 6
0```

# AI分析结果

### 题目内容
# Nastia和一个好数组

## 题目描述
Nastia收到了一个由n个正整数组成的数组作为礼物。

她称这样的一个数组a是好的，当对于所有的i（2 ≤ i ≤ n）都满足gcd(ai - 1, ai) = 1，其中gcd(u, v)表示整数u和v的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

你可以执行以下操作：选择两个不同的索引i, j（1 ≤ i, j ≤ n，i ≠ j）以及两个整数x, y（1 ≤ x, y ≤ 2·10^9），使得min(ai, aj) = min(x, y)。然后将ai改为x，将aj改为y。

这个女孩要求你使用最多n次操作使数组变好。

可以证明这总是可行的。

## 说明/提示
考虑第一个测试用例。

最初a = [9, 6, 3, 11, 15]。

在第一次操作中，将a1替换为11，将a5替换为9。这是有效的，因为min(a1, a5) = min(11, 9) = 9。

在此之后a = [11, 6, 3, 11, 9]。

在第二次操作中，将a2替换为7，将a5替换为6。这是有效的，因为min(a2, a5) = min(7, 6) = 6。

在此之后a = [11, 7, 3, 11, 6] —— 一个好数组。

在第二个测试用例中，初始数组已经是好的。

## 样例 #1
### 输入
```
2
5
9 6 3 11 15
3
7 5 13
```
### 输出
```
2
1 5 11 9
2 5 7 6
0
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕构造一个满足相邻元素互质条件的数组展开。大部分题解利用了相邻自然数或质数互质的性质。思路上，有的通过找到数组最小值，以其为基础构造相邻差值为1的序列；有的则通过寻找大于数组元素的质数来替换数组元素以满足互质条件。解决难点在于如何在满足操作条件（min(ai, aj) = min(x, y)）的前提下，有效地构造出符合要求的数组。

### 所选的题解
- **作者：_VEGETABLE_OIer_xlc (5星)**
    - **关键亮点**：思路清晰简洁，利用相邻自然数互质的性质，通过找到数组最小值及其下标，以固定格式输出操作序列，直接构造出满足条件的数组，代码实现简单明了。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,n,a[100010];
    int main(){
        cin>>t;
        while(t--)
        {
            int pos=-1,minn=1e9+7;
            cin>>n;
            for(int i=1;i<=n;i++)
            {
                cin>>a[i];
                if(a[i]<minn)
                {
                    minn=a[i];
                    pos=i;
                }
            }
            cout<<n-1<<endl;
            for(int i=1;i<=n;i++)
            {
                if(i==pos)continue;
                cout<<pos<<" "<<i<<" "<<minn<<" "<<minn+abs(i-pos)<<endl;
            }
        }
        return 0;
    } 
    ```
    - **核心实现思想**：先遍历数组找到最小值minn及其下标pos，然后对除pos位置外的每个位置i，输出操作序列，将位置pos的数与位置i的数按规则修改，构造出相邻元素互质的数组。
- **作者：qinyihao (4星)**
    - **关键亮点**：同样利用相邻自然数互质性质，逻辑清晰地阐述了通过找到最小元素，对所有元素按特定规则操作来构造数组的过程，代码简洁，对操作后的数组结构有清晰分析。
    ```cpp
    #include "bits/stdc++.h"

    using namespace std;

    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);

        int q;
        cin >> q;

        while (q--) {
            int n; cin >> n;
            int x = 1e9 + 7, pos = -1;
            for (int i = 0; i < n; ++i) {
                int a; cin >> a;
                if (a < x) x = a, pos = i;
            }
            cout << n - 1 << endl;
            for (int i = 0; i < n; ++i) {
                if (i == pos) continue;
                cout << pos + 1 << ' ' << i + 1 << ' ' << x << ' ' << x + abs(i - pos) << "\n";
            }
        }
    }
    ```
    - **核心实现思想**：与上一个题解类似，先找出最小元素x及其位置pos，然后对每个位置i（除pos外），按照给定的操作格式输出，构造出满足相邻元素互质的数组。
- **作者：Meaninglessness (4星)**
    - **关键亮点**：清晰阐述题目大意和解题思路，利用gcd(x, x + 1) = 1的性质，通过找到最小值及其位置，详细说明构造满足要求数组b的过程，逻辑连贯。
    ```cpp
    // 假设此处为完整代码框架，核心部分如下
    int mina = *min_element(a + 1, a + n + 1);
    int pos = find(a + 1, a + n + 1, mina) - a;
    // 构造数组b的逻辑，伪代码示意
    for (int i = 1; i < pos; i++) {
        b[i] = b[i + 1] + 1;
    }
    b[pos] = mina;
    for (int i = pos + 1; i <= n; i++) {
        b[i] = b[i - 1] + 1;
    }
    // 输出操作序列
    for (int i = 1; i <= n; i++) {
        if (i == pos) continue;
        cout << pos << " " << i << " " << b[i] << " " << b[pos] << endl;
    }
    ```
    - **核心实现思想**：先找到数组最小值mina及其位置pos，根据规则构造数组b，然后按照操作要求输出将原数组变为数组b的操作序列。

### 最优关键思路或技巧
利用相邻自然数互质（gcd(x, x + 1) = 1）这一数学性质，通过找到数组中的最小值，以最小值为基础向两边构造相邻差值为1的序列，从而满足相邻元素互质的要求，这种构造方式简洁高效，巧妙地利用了题目给定的操作条件。

### 可拓展之处
此类题目属于构造类型，类似套路是先观察题目要求的性质（如本题的相邻元素互质），寻找与之相关的数学规律（如相邻自然数或质数的性质），再结合给定的操作规则，设计合理的构造方法。同类型题通常围绕特定性质对给定数据进行改造，通过构造满足条件的数据结构或序列来解决问题。

### 洛谷相似题目推荐
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：同样涉及对自然数性质的运用和构造满足条件的序列。
- [P1579 哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)：考察质数相关知识，需要构造满足特定条件的质数组合。
- [P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615)：通过特定规则构造幻方，属于构造类型题目。

### 个人心得摘录
无。 

---
处理用时：53.33秒