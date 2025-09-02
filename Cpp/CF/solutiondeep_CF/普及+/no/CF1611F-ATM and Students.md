# 题目信息

# ATM and Students

## 题目描述

Polycarp started working at a bank. He was assigned to monitor the ATM. The ATM initially contains $ s $ rubles.

A queue of $ n $ students lined up to him. Each student wants to either withdraw a certain amount of money or deposit it into an account. If $ a_i $ is positive, then the student credits that amount of money via ATM. Otherwise, the student withdraws $ |a_i| $ rubles.

In the beginning, the ATM is turned off and an arbitrary number of students are not served. At some point, Polycarp turns on the ATM, which has an initial amount of $ s $ rubles. Then, the remaining students start queueing at the ATM. If at some point in time there is less money in the ATM than the student wants to withdraw, then the student is not served and Polycarp turns off the ATM and does not turn it on anymore.

More formally, the students that are served are forming a contiguous subsequence.

Polycarp wants the ATM to serve the maximum number of students. Help him in this matter. Print the numbers of the first and last student, or determine that he will not be able to serve anyone.

In other words, find such a longest continuous segment of students that, starting with the sum of $ s $ at the ATM, all these students will be served. ATM serves students consistently (i.e. one after another in the order of the queue).

## 说明/提示

In the first test case, the only correct answer is 2 4, since when serving students, the number of rubles at the ATM does not become negative, and this is the maximum number of students that can be served.

In the second test case, the answer is -1, as there is not enough money for any student at the ATM.

In the third test case, the answer can be either 1 2 or 4 5.

## 样例 #1

### 输入

```
3
4 10
-16 2 -6 8
3 1000
-100000 -100000 -100000
6 0
2 6 -164 1 -1 -6543```

### 输出

```
2 4
-1
1 2```

# AI分析结果

### 题目中文重写
# ATM与学生

## 题目描述
波利卡普开始在一家银行工作。他被分配去监控自动取款机（ATM）。这台ATM最初存有 $s$ 卢布。

有 $n$ 名学生排成一队来找他。每个学生要么想从ATM中取出一定金额的钱，要么想往账户里存入钱。如果 $a_i$ 是正数，那么该学生通过ATM存入这个金额的钱；否则，该学生取出 $|a_i|$ 卢布。

一开始，ATM处于关闭状态，任意数量的学生可能不会被服务。在某个时刻，波利卡普打开了ATM，此时ATM中有初始金额 $s$ 卢布。然后，剩下的学生开始在ATM前排队。如果在某个时刻，ATM中的钱比学生想要取出的钱少，那么该学生将不被服务，波利卡普会关闭ATM，并且不再重新开启。

更正式地说，被服务的学生形成一个连续的子序列。

波利卡普希望ATM能服务最多的学生。请帮助他解决这个问题。打印出第一个和最后一个被服务学生的编号，或者确定他无法服务任何学生。

换句话说，找到这样一个最长的连续学生段，从ATM有 $s$ 金额开始，所有这些学生都能被服务。ATM按顺序为学生服务（即按照队列的顺序一个接一个地服务）。

## 说明/提示
在第一个测试用例中，唯一正确的答案是 2 4，因为在为学生服务时，ATM中的卢布数量不会变为负数，并且这是能服务的最多学生数量。

在第二个测试用例中，答案是 -1，因为ATM中的钱不足以服务任何学生。

在第三个测试用例中，答案可以是 1 2 或 4 5。

## 样例 #1
### 输入
```
3
4 10
-16 2 -6 8
3 1000
-100000 -100000 -100000
6 0
2 6 -164 1 -1 -6543
```

### 输出
```
2 4
-1
1 2
```

### 算法分类
二分

### 综合分析与结论
这些题解主要围绕如何找到最长的连续学生段，使得从ATM有初始金额 $s$ 开始，所有这些学生都能被服务。思路主要分为两类：双指针法和二分法结合前缀和与ST表。

- **双指针法**：通过左右指针的移动，不断尝试找到满足条件的最长区间，时间复杂度为 $O(n)$。
- **二分法结合前缀和与ST表**：枚举左端点，二分查找右端点，利用前缀和计算区间和，ST表 $O(1)$ 查询区间最小值，时间复杂度为 $O(n\log n)$。

### 所选题解
- **作者：Rushroom (赞：7)，4星**
    - **关键亮点**：思路清晰，使用双指针法，复杂度为 $O(n)$，代码实现简洁明了。
- **作者：XL4453 (赞：6)，4星**
    - **关键亮点**：同样采用尺取法（双指针），有小技巧省去无解的特判，代码简洁。
- **作者：szkzyc (赞：3)，4星**
    - **关键亮点**：详细阐述了二分答案结合前缀和与ST表的思路，代码注释详细，容易理解。

### 重点代码
#### Rushroom的双指针法
```cpp
rep(i, n)
{
    if (r < i)
        r = i, sum = a[i];
    while (r < n && s + sum >= 0)
    {
        if (r - i + 1 > ans)
            ans = r - i + 1, ansl = i, ansr = r;
        r++, sum += a[r];
    }
    if (r < n)
        sum -= a[r], r--;
    else
        break;
    sum -= a[i];
}
```
**核心实现思想**：左指针 $i$ 向右移动，右指针 $r$ 尽量向右移动，用 $sum$ 记录左右指针之间所有数的和，当 $s + sum < 0$ 时停止移动右指针，更新答案。

#### XL4453的双指针法
```cpp
while(r<n){
    now+=a[++r];
    if(now<0){
        while(l<=r&&now<0){
            now-=a[l];
            l++;
        }
    }
    if(r-l>ans){
        ans=r-l;
        ansl=l;
        ansr=r;
    }
}
```
**核心实现思想**：右指针 $r$ 不断向右移动，当当前金额 $now$ 小于 0 时，移动左指针 $l$ 直到 $now$ 大于等于 0，更新答案。

#### szkzyc的二分法结合前缀和与ST表
```cpp
for(int L = 1; L <= n; L++){//二分答案 
    int num = 0;
    int left = L;//枚举左端点 
    int right = n;//先默认右端点为n 
    while(left <= right){
        int mid = (left + right) / 2;//中间值 
        if(check(L, mid, s)){//判断区间 
            num = mid;//记录 
            left = mid + 1;//缩小区间 
        }
        else right = mid - 1;//缩小区间 
    }
    if(num - L + 1 > answer){//当前答案最优 
        answer = num - L + 1;//记录答案 
        ansleft = L;//记录左端点 
        ansright = num;//记录右端点 
    }
}
```
**核心实现思想**：枚举左端点 $L$，二分查找右端点，利用 $check$ 函数判断区间是否满足条件，更新答案。

### 关键思路或技巧
- **双指针法**：通过左右指针的移动，线性地找到满足条件的最长区间，避免了不必要的计算。
- **二分法结合前缀和与ST表**：利用二分的思想缩小查找范围，前缀和快速计算区间和，ST表 $O(1)$ 查询区间最小值，将复杂度降低到 $O(n\log n)$。

### 拓展思路
同类型题或类似算法套路：
- 求满足某种条件的最长子数组或子区间问题，可考虑双指针法或二分法结合前缀和。
- 涉及区间最值查询的问题，可使用ST表或线段树进行优化。

### 推荐洛谷题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)
- [P3865 【模板】ST表](https://www.luogu.com.cn/problem/P3865)

### 个人心得摘录与总结
- **szkzyc**：周三vp CF1611时这道题有思路但没做出来，课后跟王江睿讨论，发现可以用前缀和、ST表和二分答案解决，花了一天时间在赛后写完。总结：遇到难题可与他人讨论，赛后也要及时复盘。

---
处理用时：58.72秒