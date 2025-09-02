# 题目信息

# XOR-gun

## 题目描述

Arkady owns a non-decreasing array $ a_1, a_2, \ldots, a_n $ . You are jealous of its beauty and want to destroy this property. You have a so-called XOR-gun that you can use one or more times.

In one step you can select two consecutive elements of the array, let's say $ x $ and $ y $ , remove them from the array and insert the integer $ x \oplus y $ on their place, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Note that the length of the array decreases by one after the operation. You can't perform this operation when the length of the array reaches one.

For example, if the array is $ [2, 5, 6, 8] $ , you can select $ 5 $ and $ 6 $ and replace them with $ 5 \oplus 6 = 3 $ . The array becomes $ [2, 3, 8] $ .

You want the array no longer be non-decreasing. What is the minimum number of steps needed? If the array stays non-decreasing no matter what you do, print $ -1 $ .

## 说明/提示

In the first example you can select $ 2 $ and $ 5 $ and the array becomes $ [7, 6, 8] $ .

In the second example you can only obtain arrays $ [1, 1] $ , $ [3, 3] $ and $ [0] $ which are all non-decreasing.

In the third example you can select $ 1 $ and $ 2 $ and the array becomes $ [3, 4, 6, 20] $ . Then you can, for example, select $ 3 $ and $ 4 $ and the array becomes $ [7, 6, 20] $ , which is no longer non-decreasing.

## 样例 #1

### 输入

```
4
2 5 6 8```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
5
1 2 4 6 20```

### 输出

```
2```

# AI分析结果

### 题目翻译
## XOR 枪

### 题目描述
Arkady 拥有一个非递减数组 $ a_1, a_2, \ldots, a_n $。你嫉妒它的完美，想要破坏这个性质。你有一把所谓的 XOR 枪，你可以使用一次或多次。

在一步操作中，你可以选择数组中两个相邻的元素，假设为 $ x $ 和 $ y $，将它们从数组中移除，并在它们的位置插入整数 $ x \oplus y $，其中 $ \oplus $ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。注意，操作后数组的长度会减少 1。当数组长度达到 1 时，你就不能再执行此操作了。

例如，如果数组是 $ [2, 5, 6, 8] $，你可以选择 5 和 6，并用 $ 5 \oplus 6 = 3 $ 替换它们。数组变为 $ [2, 3, 8] $。

你希望数组不再是非递减的。最少需要多少步操作？如果无论你怎么做数组都保持非递减，请输出 $ -1 $。

### 说明/提示
在第一个示例中，你可以选择 2 和 5，数组变为 $ [7, 6, 8] $。

在第二个示例中，你只能得到数组 $ [1, 1] $、$ [3, 3] $ 和 $ [0] $，它们都是非递减的。

在第三个示例中，你可以选择 1 和 2，数组变为 $ [3, 4, 6, 20] $。然后，例如，你可以选择 3 和 4，数组变为 $ [7, 6, 20] $，这就不再是非递减的了。

### 样例 #1
#### 输入
```
4
2 5 6 8
```
#### 输出
```
1
```

### 样例 #2
#### 输入
```
3
1 2 3
```
#### 输出
```
-1
```

### 样例 #3
#### 输入
```
5
1 2 4 6 20
```
#### 输出
```
2
```

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是先利用位运算的性质判断是否能通过一次操作使数组不再非递减，若不能则采用暴力枚举的方法。具体来说，利用抽屉原理，当 $n > 60$ 时，必然存在三个相邻的数二进制最高位相同，对后两个数进行异或操作可使数组非递减；当 $n \leq 60$ 时，通过枚举相邻区间的异或和来找到最小操作次数。

### 所选题解
- **作者：chen_03（4星）**
    - **关键亮点**：思路清晰，先判断一次操作的情况，再利用前缀异或和进行暴力枚举，代码实现简洁明了。
- **作者：Schwarzkopf_Henkal（4星）**
    - **关键亮点**：结合之前类似题的经验，先分析特殊情况，再进行暴力枚举，逻辑连贯。
- **作者：yuzhuo（4星）**
    - **关键亮点**：详细推导了暴力枚举的过程，利用异或前缀和优化时间复杂度，解释清晰。

### 重点代码
```cpp
// chen_03的代码
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,a[100005],x,y,ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",a+i);
    for(int i=1;i<=n-2;++i){
        x=a[i]^a[i+1];
        if(x<a[i-1] || x>a[i+2]){
            printf("1\n");
            return 0;
        }
    }
    for(int i=1;i<=n;++i)a[i]^=a[i-1];
    ans=n;
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            for(int k=i;k<j;++k){
                x=a[k]^a[i-1];
                y=a[j]^a[k];
                if(x>y)ans=min(ans,j-i-1);
            }
        }
    }
    printf("%d\n",ans<n?ans:-1);
    return 0;
}
```
**核心实现思想**：先遍历数组，判断是否能通过一次操作使数组非递减。若不能，则计算前缀异或和，然后通过三重循环枚举相邻区间的异或和，更新最小操作次数。

### 关键思路或技巧
- **抽屉原理**：利用抽屉原理判断是否存在三个相邻的数二进制最高位相同，从而确定是否能通过一次操作使数组非递减。
- **前缀异或和**：通过计算前缀异或和，快速计算区间的异或和，优化暴力枚举的时间复杂度。

### 拓展思路
同类型题或类似算法套路通常涉及位运算和暴力枚举的结合。例如，一些题目会要求在数组中进行特定的位运算操作，然后判断数组是否满足某种条件，或者求满足条件的最小操作次数。

### 推荐题目
- [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)

### 个人心得
部分题解提到之前做过类似的最小操作次数题，可以考虑最大可行操作次数，这是一种很有用的解题思路，在遇到类似问题时可以借鉴。

---
处理用时：38.05秒