# 题目信息

# Negatives and Positives

## 题目描述

Given an array $ a $ consisting of $ n $ elements, find the maximum possible sum the array can have after performing the following operation any number of times:

- Choose $ 2 $ adjacent elements and flip both of their signs. In other words choose an index $ i $ such that $ 1 \leq i \leq n - 1 $ and assign $ a_i = -a_i $ and $ a_{i+1} = -a_{i+1} $ .

## 说明/提示

For the first test case, by performing the operation on the first two elements, we can change the array from $ [-1, -1, -1] $ to $ [1, 1, -1] $ , and it can be proven this array obtains the maximum possible sum which is $ 1 + 1 + (-1) = 1 $ .

For the second test case, by performing the operation on $ -5 $ and $ 0 $ , we change the array from $ [1, 5, -5, 0, 2] $ to $ [1, 5, -(-5), -0, 2] = [1, 5, 5, 0, 2] $ , which has the maximum sum since all elements are non-negative. So, the answer is $ 1 + 5 + 5 + 0 + 2 = 13 $ .

For the third test case, the array already contains only positive numbers, so performing operations is unnecessary. The answer is just the sum of the whole array, which is $ 1 + 2 + 3 = 6 $ .

## 样例 #1

### 输入

```
5
3
-1 -1 -1
5
1 5 -5 0 2
3
1 2 3
6
-1 10 9 8 7 6
2
-1 -1```

### 输出

```
1
13
6
39
2```

# AI分析结果

### 题目内容
# 负数与正数

## 题目描述
给定一个由 $n$ 个元素组成的数组 $a$，在执行以下操作任意次数后，找出该数组可能具有的最大和：
- 选择两个相邻元素并翻转它们的符号。换句话说，选择一个索引 $i$，使得 $1 \leq i \leq n - 1$，并将 $a_i$ 赋值为 $-a_i$，$a_{i + 1}$ 赋值为 $-a_{i + 1}$。

## 说明/提示
对于第一个测试用例，通过对前两个元素执行操作，我们可以将数组从 $[-1, -1, -1]$ 变为 $[1, 1, -1]$，可以证明这个数组获得了最大可能的和，即 $1 + 1 + (-1) = 1$。

对于第二个测试用例，通过对 $-5$ 和 $0$ 执行操作，我们将数组从 $[1, 5, -5, 0, 2]$ 变为 $[1, 5, -(-5), -0, 2] = [1, 5, 5, 0, 2]$，由于所有元素都是非负的，所以这个数组具有最大和。因此，答案是 $1 + 5 + 5 + 0 + 2 = 13$。

对于第三个测试用例，数组已经只包含正数，所以执行操作是不必要的。答案就是整个数组的和，即 $1 + 2 + 3 = 6$。

## 样例 #1
### 输入
```
5
3
-1 -1 -1
5
1 5 -5 0 2
3
1 2 3
6
-1 10 9 8 7 6
2
-1 -1
```
### 输出
```
1
13
6
39
2
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是围绕如何通过给定操作，最大化数组的和。关键在于发现可以通过相邻元素符号翻转操作，实现对数组中负数的处理，使负数尽可能少或绝对值尽可能小。
1. **思路方面**：多数题解都意识到操作不影响负数个数的奇偶性，从而分负数个数为偶数和奇数两种情况讨论。偶数时可全部消除负数，奇数时保留绝对值最小的负数。
2. **算法要点**：计算数组所有元素绝对值之和，根据负数个数的奇偶性进行调整。若为奇数，减去两倍绝对值最小的数。
3. **解决难点**：证明可以通过相邻操作实现对任意两个数符号的翻转，以及理解为何这样操作能使数组和最大。

### 所选的题解
- **作者：AbsMatt (5星)**
    - **关键亮点**：思路清晰，先证明可对任意两个数取相反数，再通过排序贪心处理，每次取最小的两个数判断是否需操作，代码简洁高效。
    - **重点代码**：
```cpp
void solve(){
    ans=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        ans+=a[i];  // 当前数组总和
    }
    sort(a+1,a+n+1);   // 排序
    for(int i=1;i<n;i+=2){
        if(a[i]+a[i+1]<0){  // 将这两个数进行操作
            ans-=(a[i]*2);
            ans-=(a[i+1]*2);
        }
    }
    printf("%lld\n",ans);  // 输出。
}
```
    - **核心实现思想**：先计算数组初始和，排序后依次检查相邻两个数和是否为负，若是则通过调整和来模拟取反操作。
- **作者：LincW (4星)**
    - **关键亮点**：详细分析负数移动的方法，清晰地分负数个数为偶数和奇数两种情况，直接给出数学表达式，逻辑连贯。
    - **重点代码**：
```cpp
for(int i=1;i<=n;++i)
{
    cin>>arr[i];
    if(arr[i]<0) nega++;
    mi=min(abs(arr[i]),mi);
    sum+=abs(arr[i]);
}
if(nega%2==1)
{
    sum-=(2*mi);
}
cout<<sum<<endl;
```
    - **核心实现思想**：遍历数组统计负数个数、最小绝对值以及所有数绝对值之和，根据负数个数奇偶性调整和。
- **作者：loser_seele (4星)**
    - **关键亮点**：简洁明了地指出操作不影响负数个数奇偶性，直接得出根据奇偶性计算答案的方法，时间复杂度最优。
    - **重点代码**：
```cpp
for(int i=1;i<=n;i++)
cin>>a[i],cnt+=(a[i]<0),a[i]=abs(a[i]),minn=min(minn,a[i]),sum+=a[i];
if(cnt%2)
cout<<sum-2*minn<<'\n';
else
cout<<sum<<'\n';
```
    - **核心实现思想**：在输入时统计负数个数、计算绝对值和与最小绝对值，根据负数个数奇偶性输出结果。

### 最优关键思路或技巧
1. **思维方式**：利用操作不改变负数个数奇偶性这一特性，分情况讨论并贪心处理。
2. **代码实现技巧**：在遍历数组时同时完成多个关键数据（如负数个数、绝对值和、最小绝对值）的统计，减少重复遍历。

### 可拓展之处
同类型题通常围绕数组元素操作与最值求解，类似算法套路是分析操作对数组某些特性（如正负性、奇偶性）的影响，进而通过贪心策略解决问题。

### 洛谷相似题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)

### 个人心得摘录
作者JWRuixi提到有一发罚时，但未详细说明原因，推测可能是代码实现细节（如数据类型、边界条件等）处理不当导致。这提醒在解题时要注重细节，全面考虑各种情况。 

---
处理用时：47.64秒