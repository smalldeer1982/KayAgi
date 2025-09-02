# 题目信息

# Subsequence Addition (Easy Version)

## 题目描述

The only difference between the two versions is that in this version, the constraints are lower.

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

### 题目内容
# 子序列求和（简单版本）

## 题目描述
两个版本之间唯一的区别在于，在这个版本中，约束条件更低。
最初，数组 $a$ 仅包含数字 $1$。你可以按顺序执行若干操作来改变数组。在一次操作中，你可以选择 $a$ 的某个子序列 $^{\dagger}$，并向 $a$ 中添加一个等于该子序列所有元素之和的元素。
给定一个最终数组 $c$。检查是否可以通过对初始数组 $a$ 执行若干次（可能为 $0$ 次）操作来得到 $c$。
$^{\dagger}$ 序列 $b$ 是序列 $a$ 的子序列，如果 $b$ 可以通过删除 $a$ 中的若干个（可能为零个，但不是全部）元素得到。换句话说，选择 $k$（$1 \leq k \leq |a|$）个不同的索引 $i_1, i_2, \dots, i_k$，并在 $a$ 的任意位置插入一个值等于 $a_{i_1} + a_{i_2} + \dots + a_{i_k}$ 的新元素。

## 说明/提示
对于第一个测试用例，初始数组 $a$ 已经等于 $[1]$，所以答案是 “YES”。
对于第二个测试用例，执行任意次数的操作都会使 $a$ 变为大小至少为 $2$ 且不只有元素 $2$ 的数组，因此不可能得到数组 $[2]$，答案是 “NO”。
对于第三个测试用例，我们可以按以下顺序执行操作以获得最终给定的数组 $c$：
- 最初，$a = [1]$。
- 通过选择子序列 $[1]$，并在数组中插入 $1$，$a$ 变为 $[1, 1]$。
- 通过选择子序列 $[1, 1]$，并在数组中间插入 $1 + 1 = 2$，$a$ 变为 $[1, 2, 1]$。
- 通过选择子序列 $[1, 2]$，并在数组的第一个 $1$ 之后插入 $1 + 2 = 3$，$a$ 变为 $[1, 3, 2, 1]$。
- 通过选择子序列 $[1, 3, 1]$ 并在数组开头插入 $1 + 3 + 1 = 5$，$a$ 变为 $[5, 1, 3, 2, 1]$（这就是我们需要得到的数组）。

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
1 1 4 2 1
```
### 输出
```
YES
NO
YES
NO
YES
YES
```

### 算法分类
贪心

### 综合分析与结论
这三道题解都围绕判断给定数组能否由初始数组 $[1]$ 通过特定子序列求和操作得到这一核心问题。作者 Larryyu 和ダ月 都采用了排序后判断当前数与前面所有数总和关系的思路，作者 Flanksy 则利用 bitset 来模拟子序列求和的可能性。整体而言，这三道题解都有效解决了问题，但在思路清晰度、代码复杂度和时间复杂度上存在差异。

### 所选的题解
- **作者：Larryyu (5星)**
    - **关键亮点**：思路简洁清晰，直接抓住操作后新加入数的范围特性，通过排序和前缀和比较快速判断，代码实现简单明了。
    - **重点代码核心实现思想**：先对输入数组排序，检查最小数是否为 $1$，然后遍历数组，检查每个数是否小于等于其前面所有数的总和，若不满足则输出 “NO”，遍历结束无异常则输出 “YES”。
    - **核心代码片段**：
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
- **作者：Flanksy (4星)**
    - **关键亮点**：利用 bitset 数据结构巧妙模拟子序列求和过程，在判断可行性方面有独特视角。
    - **重点代码核心实现思想**：先对输入数组排序并检查首位是否为 $1$，初始化 bitset 表示可得到的数，遍历数组，若当前数在 bitset 中对应位为 $1$，则更新 bitset 表示加入当前数后可得到的所有数，若当前数对应位为 $0$ 则输出 “NO”，遍历结束无异常则输出 “YES”。
    - **核心代码片段**：
```cpp
void deal(){
    cin>>n,s.reset();
    for(int i=1;i<=n;i++) cin>>c[i];
    s[1]=1,sort(c+1,c+n+1);
    if(c[1]!=1) return cout<<"NO\n",void();
    for(int i=2;i<=n;i++)
        if(s[c[i]]) s|=s<<c[i];
        else return cout<<"NO\n",void();
    cout<<"YES\n";
}
```
- **作者：ダ月 (4星)**
    - **关键亮点**：从暴力搜索到 01 背包问题，再到总结出简洁的判断条件，解题思路的推导过程完整，对问题本质的挖掘较深。
    - **重点代码核心实现思想**：先对输入数组排序，检查最小数是否为 $1$，然后计算前缀和，检查每个数是否小于等于其前面所有数的总和，若不满足则输出 “NO”，遍历结束无异常则输出 “YES”。
    - **核心代码片段**：
```cpp
int main(){
    cin>>T;
    while(T--){
        cin>>n;int tem=0;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
        if(a[1]!=1){puts("NO");continue;}
        bool flag=true;
        for(int i=2;i<=n;i++)
            if(s[i-1]<a[i]){
                flag=false;
                break;
            }
        puts(flag?"YES":"NO");
    }return 0;
}
```

### 最优关键思路或技巧
最优思路是通过排序数组，利用新加入元素值介于当前最小元素（$k = 1$ 时）与所有元素总和（$k = n$ 时）之间这一特性，用前缀和判断每个元素是否符合要求，简洁高效地解决问题。

### 可拓展之处
此类题目属于序列构造可行性判断问题，类似套路是分析操作对序列元素的影响，总结出可判断的数学性质或规律。例如，其他涉及序列元素生成、变换规则，然后判断能否达到特定状态的题目都可参考此思路。

### 洛谷推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，通过分析操作对结果的影响找到最优排序。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：同样是贪心算法应用，需根据任务处理时间特点进行排序优化。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过推导元素之间的比较关系，利用贪心策略解决双属性元素的排序问题。 

---
处理用时：59.55秒