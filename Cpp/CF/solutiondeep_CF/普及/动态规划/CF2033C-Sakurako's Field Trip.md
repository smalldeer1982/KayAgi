# 题目信息

# Sakurako's Field Trip

## 题目描述

Even in university, students need to relax. That is why Sakurakos teacher decided to go on a field trip. It is known that all of the students will be walking in one line. The student with index $ i $ has some topic of interest which is described as $ a_i $ . As a teacher, you want to minimise the disturbance of the line of students.

The disturbance of the line is defined as the number of neighbouring people with the same topic of interest. In other words, disturbance is the number of indices $ j $ ( $ 1 \le j < n $ ) such that $ a_j = a_{j + 1} $ .

In order to do this, you can choose index $ i $ ( $ 1\le i\le n $ ) and swap students at positions $ i $ and $ n-i+1 $ . You can perform any number of swaps.

Your task is to determine the minimal amount of disturbance that you can achieve by doing the operation described above any number of times.

## 说明/提示

In the first example, it is necessary to apply the operation to $ i=2 $ , thus the array will become $ [1, \textbf{2}, 1, \textbf{1}, 3] $ , with the bold elements indicating those that have swapped places. The disturbance of this array is equal to $ 1 $ .

In the fourth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [2, 1, \textbf{2}, \textbf{1}, 2, 4] $ . The disturbance of this array is equal to $ 0 $ .

In the eighth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [1, 4, \textbf{1}, 5, \textbf{3}, 1, 3] $ . The disturbance of this array is equal to $ 0 $ .

## 样例 #1

### 输入

```
9
5
1 1 1 2 3
6
2 1 2 2 1 1
4
1 2 1 1
6
2 1 1 2 2 4
4
2 1 2 3
6
1 2 2 1 2 1
5
4 5 5 1 5
7
1 4 3 5 1 1 3
7
3 1 3 2 2 3 3```

### 输出

```
1
2
1
0
0
1
1
0
2```

# AI分析结果

### 题目内容重写

#### Sakurako's Field Trip

##### 题目描述

即使在大学，学生们也需要放松。这就是为什么Sakurako的老师决定组织一次郊游。已知所有学生将排成一列行走。索引为 $i$ 的学生有一个感兴趣的主题，描述为 $a_i$。作为老师，你希望最小化学生队伍的干扰。

队伍的干扰定义为相邻学生兴趣相同的对数。换句话说，干扰是满足 $a_j = a_{j + 1}$ 的索引 $j$（$1 \le j < n$）的数量。

为了达到这个目的，你可以选择索引 $i$（$1 \le i \le n$）并交换位置 $i$ 和 $n-i+1$ 的学生。你可以进行任意次数的交换。

你的任务是通过上述操作，确定可以达到的最小干扰量。

##### 说明/提示

在第一个例子中，需要对 $i=2$ 进行操作，数组将变为 $[1, \textbf{2}, 1, \textbf{1}, 3]$，粗体表示交换的元素。该数组的干扰为 $1$。

在第四个例子中，只需对 $i=3$ 进行操作，数组将变为 $[2, 1, \textbf{2}, \textbf{1}, 2, 4]$。该数组的干扰为 $0$。

在第八个例子中，只需对 $i=3$ 进行操作，数组将变为 $[1, 4, \textbf{1}, 5, \textbf{3}, 1, 3]$。该数组的干扰为 $0$。

##### 样例 #1

###### 输入

```
9
5
1 1 1 2 3
6
2 1 2 2 1 1
4
1 2 1 1
6
2 1 1 2 2 4
4
2 1 2 3
6
1 2 2 1 2 1
5
4 5 5 1 5
7
1 4 3 5 1 1 3
7
3 1 3 2 2 3 3
```

###### 输出

```
1
2
1
0
0
1
1
0
2
```

### 题解分析与结论

#### 综合分析与结论

本题的核心在于通过交换操作最小化相邻学生兴趣相同的对数。多个题解采用了动态规划（DP）或贪心策略来解决此问题。以下是对各题解的要点提炼与难点对比：

1. **DP思路**：多个题解（如篮网总冠军、_Lazy_whr_、K_J_M）采用了DP的方法，通过枚举每个位置是否交换，并记录最小干扰数。难点在于状态转移方程的构建，特别是如何处理偶数情况下的中间对。

2. **贪心策略**：部分题解（如jess1ca1o0g3、splendore）采用了贪心策略，通过双指针从两端向中间遍历，每次判断是否交换以减少干扰。难点在于如何确保每一步的局部最优能导致全局最优。

3. **分类讨论**：部分题解（如Sakura_Emilia、sintle）通过分类讨论各种情况，直接计算干扰数。难点在于如何全面覆盖所有可能的情况，并确保计算的准确性。

#### 最优关键思路或技巧

- **DP状态转移**：通过记录每个位置是否交换的最小干扰数，逐步递推得到全局最优解。特别要注意偶数情况下的中间对处理。
- **贪心策略**：从两端向中间遍历，每次判断是否交换以减少干扰，确保每一步的局部最优能导致全局最优。
- **分类讨论**：通过全面覆盖所有可能的情况，直接计算干扰数，确保计算的准确性。

#### 可拓展之处

- **类似题目**：可以扩展到其他需要通过交换操作优化某种指标的题目，如最小化逆序对、最大化某种匹配等。
- **算法套路**：DP和贪心策略在处理类似问题时具有通用性，可以举一反三。

#### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略的应用。
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 动态规划的应用。
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060) - 动态规划的应用。

### 精选题解

#### 题解1：篮网总冠军（4星）

**关键亮点**：采用DP思路，通过枚举每个位置是否交换，并记录最小干扰数。代码清晰，状态转移方程合理。

**核心代码**：
```cpp
for(int i=2;i<=(n+1)/2;i++){
    dp[i][0]=min(dp[i-1][0]+(a[i]==a[i-1])+(a[n-i+1]==a[n-i+2]),dp[i-1][1]+(a[i]==a[n-i+2])+(a[i-1]==a[n-i+1]));
    dp[i][1]=min(dp[i-1][0]+(a[i-1]==a[n-i+1])+(a[i]==a[n-i+2]),dp[i-1][1]+(a[i]==a[i-1])+(a[n-i+1]==a[n-i+2]));
}
if (n%2==1)cout<<min(dp[(n+1)/2][0],dp[(n+1)/2][1])<<endl;
else cout<<min(dp[(n+1)/2][0],dp[(n+1)/2][1])+(a[n/2]==a[n/2+1])<<endl;
```

#### 题解2：jess1ca1o0g3（4星）

**关键亮点**：采用贪心策略，通过双指针从两端向中间遍历，每次判断是否交换以减少干扰。代码简洁，思路清晰。

**核心代码**：
```cpp
int l=2,r=n-1,ans=0;
while(l<r){
    if(a[l]==a[l-1]||a[r]==a[r+1]) swap(a[l],a[r]);
    l++,r--;
}
L(i,1,n-1,1){
    if(a[i]==a[i+1]) ans++;
}
printf("%d\n",ans);
```

#### 题解3：Sakura_Emilia（4星）

**关键亮点**：通过分类讨论各种情况，直接计算干扰数。代码逻辑清晰，全面覆盖所有可能的情况。

**核心代码**：
```cpp
for(int i=2;i<=n/2;i++){
    int j=n-i+1;
    lastA=i-1,lastB=n-(i-1)+1;
    if(a[lastA]==a[lastB]){
        if(a[i]==a[j]){
            if(a[i]==a[lastA]) ans+=2;
        }else{
            if(a[i]==a[lastA]) ans++;
            if(a[j]==a[lastB]) ans++;
        }
    }else{
        if(a[i]==a[j]){
            if(a[i]==a[lastA]||a[i]==a[lastB]) ans++;
        }
    }
}
if(n%2==1){
    if(a[(n+1)/2]==a[(n+1)/2-1]) ans++;
    if(a[(n+1)/2]==a[(n+1)/2+1]) ans++;
}else{
    if(a[n/2]==a[n/2+1]) ans++;
}
cout<<ans<<endl;
```

---
处理用时：55.73秒