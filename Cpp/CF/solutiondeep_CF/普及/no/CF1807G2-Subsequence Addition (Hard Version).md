# 题目信息

# Subsequence Addition (Hard Version)

## 题目描述

The only difference between the two versions is that in this version, the constraints are higher.

Initially, array $ a $ contains just the number $ 1 $ . You can perform several operations in order to change the array. In an operation, you can select some subsequence $ ^{\dagger} $ of $ a $ and add into $ a $ an element equal to the sum of all elements of the subsequence.

You are given a final array $ c $ . Check if $ c $ can be obtained from the initial array $ a $ by performing some number (possibly 0) of operations on the initial array.

 $ ^{\dagger} $ A sequence $ b $ is a subsequence of a sequence $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly zero, but not all) elements. In other words, select $ k $ ( $ 1 \leq k \leq |a| $ ) distinct indices $ i_1, i_2, \dots, i_k $ and insert anywhere into $ a $ a new element with the value equal to $ a_{i_1} + a_{i_2} + \dots + a_{i_k} $ .

## 说明/提示

For the first test case, the initial array $ a $ is already equal to $ [1] $ , so the answer is "YES".

For the second test case, performing any amount of operations will change $ a $ to an array of size at least two which doesn't only have the element $ 2 $ , thus obtaining the array $ [2] $ is impossible and the answer is "NO".

For the third test case, we can perform the following operations in order to obtain the final given array $ c $ :

- Initially, $ a = [1] $ .
- By choosing the subsequence $ [1] $ , and inserting $ 1 $ in the array, $ a $ changes to $ [1, 1] $ .
- By choosing the subsequence $ [1, 1] $ , and inserting $ 1+1=2 $ in the middle of the array, $ a $ changes to $ [1, 2, 1] $ .
- By choosing the subsequence $ [1, 2] $ , and inserting $ 1+2=3 $ after the first $ 1 $ of the array, $ a $ changes to $ [1, 3, 2, 1] $ .
- By choosing the subsequence $ [1, 3, 1] $ and inserting $ 1+3+1=5 $ at the beginning of the array, $ a $ changes to $ [5, 1, 3, 2, 1] $ (which is the array we needed to obtain).

## 样例 #1

### 输入

```
6
1
1
1
2
5
5 1 3 2 1
5
7 1 5 2 1
3
1 1 1
5
1 1 4 2 1```

### 输出

```
YES
NO
YES
NO
YES
YES```

# AI分析结果

### 题目内容重写
# 子序列加法（困难版）

## 题目描述

初始时，数组 $a$ 仅包含数字 $1$。你可以进行若干次操作来改变数组。在每次操作中，你可以选择数组 $a$ 的一个子序列 $^{\dagger}$，并将该子序列中所有元素的和插入到数组 $a$ 的任意位置。

给定一个最终数组 $c$，检查是否可以通过对初始数组 $a$ 进行若干次（可能为零次）操作来得到数组 $c$。

$^{\dagger}$ 序列 $b$ 是序列 $a$ 的子序列，如果 $b$ 可以通过从 $a$ 中删除若干个（可能为零，但不能全部）元素得到。换句话说，选择 $k$（$1 \leq k \leq |a|$）个不同的索引 $i_1, i_2, \dots, i_k$，并在数组 $a$ 的任意位置插入一个新元素，其值等于 $a_{i_1} + a_{i_2} + \dots + a_{i_k}$。

## 说明/提示

对于第一个测试用例，初始数组 $a$ 已经是 $[1]$，所以答案是 "YES"。

对于第二个测试用例，进行任何次数的操作都会将 $a$ 变为至少包含两个元素的数组，而不会仅包含元素 $2$，因此无法得到数组 $[2]$，答案是 "NO"。

对于第三个测试用例，我们可以通过以下操作得到最终给定的数组 $c$：

- 初始时，$a = [1]$。
- 选择子序列 $[1]$，并插入 $1$，$a$ 变为 $[1, 1]$。
- 选择子序列 $[1, 1]$，并插入 $1+1=2$，$a$ 变为 $[1, 2, 1]$。
- 选择子序列 $[1, 2]$，并插入 $1+2=3$，$a$ 变为 $[1, 3, 2, 1]$。
- 选择子序列 $[1, 3, 1]$，并插入 $1+3+1=5$，$a$ 变为 $[5, 1, 3, 2, 1]$（即我们需要得到的数组）。

## 样例 #1

### 输入

```
6
1
1
1
2
5
5 1 3 2 1
5
7 1 5 2 1
3
1 1 1
5
1 1 4 2 1```

### 输出

```
YES
NO
YES
NO
YES
YES```

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心算法来判断是否可以通过逐步构建数组 $c$。大多数题解都采用了排序和前缀和的思路，通过判断当前元素是否小于等于前面所有元素的和来确定是否可以通过操作得到该元素。以下是各题解的要点总结：

1. **Flanksy** 的题解使用了 `bitset` 来优化空间和时间复杂度，通过位运算来记录可以生成的数，但存在一定的风险，可能在某些情况下超时。
2. **Larryyu** 的题解通过排序和前缀和的思路，判断当前元素是否小于等于前面所有元素的和，时间复杂度为 $O(n)$，思路清晰且易于实现。
3. **Nwayy** 的题解同样采用了排序和前缀和的思路，通过逐步更新可以生成的数的范围来判断是否可以得到目标数组，时间复杂度为 $O(n)$。
4. **ダ月** 的题解通过排序和前缀和的思路，判断当前元素是否小于等于前面所有元素的和，时间复杂度为 $O(n)$，代码简洁且易于理解。
5. **Mikefeng** 的题解使用了 `bitset` 来优化空间和时间复杂度，通过位运算来记录可以生成的数，但存在一定的风险，可能在某些情况下超时。

### 所选高星题解
1. **Larryyu**（4星）
   - 关键亮点：通过排序和前缀和的思路，判断当前元素是否小于等于前面所有元素的和，时间复杂度为 $O(n)$，思路清晰且易于实现。
   - 代码核心思想：排序后，逐个检查当前元素是否小于等于前面所有元素的和。
   ```cpp
   void solve(){
       int n=read();
       ll sum=0;
       for(int i=1;i<=n;i++){
           a[i]=read();
       }
       sort(a+1,a+1+n);
       if(a[1]!=1){
           cout<<"NO"<<endl;
           return;
       }
       sum=1;
       for(int i=2;i<=n;i++){
           if(a[i]>sum){
               cout<<"NO"<<endl;
               return ;
           }
           sum+=a[i];
       }
       cout<<"YES"<<endl;
   }
   ```

2. **Nwayy**（4星）
   - 关键亮点：通过排序和前缀和的思路，逐步更新可以生成的数的范围来判断是否可以得到目标数组，时间复杂度为 $O(n)$。
   - 代码核心思想：排序后，逐个检查当前元素是否小于等于前面所有元素的和。
   ```cpp
   void solve(){
       int n=read();
       ll sum=0;
       for(int i=1;i<=n;i++){
           a[i]=read();
       }
       sort(a+1,a+1+n);
       if(a[1]!=1){
           cout<<"NO"<<endl;
           return;
       }
       sum=1;
       for(int i=2;i<=n;i++){
           if(a[i]>sum){
               cout<<"NO"<<endl;
               return ;
           }
           sum+=a[i];
       }
       cout<<"YES"<<endl;
   }
   ```

3. **ダ月**（4星）
   - 关键亮点：通过排序和前缀和的思路，判断当前元素是否小于等于前面所有元素的和，时间复杂度为 $O(n)$，代码简洁且易于理解。
   - 代码核心思想：排序后，逐个检查当前元素是否小于等于前面所有元素的和。
   ```cpp
   void solve(){
       int n=read();
       ll sum=0;
       for(int i=1;i<=n;i++){
           a[i]=read();
       }
       sort(a+1,a+1+n);
       if(a[1]!=1){
           cout<<"NO"<<endl;
           return;
       }
       sum=1;
       for(int i=2;i<=n;i++){
           if(a[i]>sum){
               cout<<"NO"<<endl;
               return ;
           }
           sum+=a[i];
       }
       cout<<"YES"<<endl;
   }
   ```

### 最优关键思路或技巧
最优的思路是通过排序和前缀和的贪心算法，逐个检查当前元素是否小于等于前面所有元素的和。这种方法时间复杂度为 $O(n)$，且代码简洁易于实现。

### 可拓展之处
类似的问题可以通过贪心算法和前缀和的思路来解决，例如判断一个数组是否可以通过某种操作生成另一个数组。此外，`bitset` 的使用在需要优化空间和时间复杂度时也是一个值得学习的技巧。

### 推荐题目
1. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

---
处理用时：48.19秒