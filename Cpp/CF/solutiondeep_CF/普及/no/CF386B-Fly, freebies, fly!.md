# 题目信息

# Fly, freebies, fly!

## 题目描述

Everyone loves a freebie. Especially students.

It is well-known that if in the night before exam a student opens window, opens the student's record-book and shouts loudly three times "Fly, freebie, fly!" — then flown freebie helps him to pass the upcoming exam.

In the night before the exam on mathematical analysis $ n $ students living in dormitory shouted treasured words. The $ i $ -th student made a sacrament at the time $ t_{i} $ , where $ t_{i} $ is the number of seconds elapsed since the beginning of the night.

It is known that the freebie is a capricious and willful lady. That night the freebie was near dormitory only for $ T $ seconds. Therefore, if for two students their sacrament times differ for more than $ T $ , then the freebie didn't visit at least one of them.

Since all students are optimists, they really want to know what is the maximal number of students visited by the freebie can be.

## 样例 #1

### 输入

```
6
4 1 7 8 3 8
1
```

### 输出

```
3
```

# AI分析结果



# Fly, freebies, fly! 题目重写

## 题目描述  
每个人都喜欢免费的东西，尤其是学生。  

众所周知，如果学生在考试前夜打开窗户、翻开成绩册并大喊三声"Fly, freebie, fly!"，那么飞来的免费福利会帮助他通过考试。  

在数学分析考试前夜，宿舍里有 $n$ 个学生喊出了这句神圣的话语。第 $i$ 个学生在时间 $t_i$ 进行了仪式，其中 $t_i$ 表示从夜晚开始经过的秒数。  

已知免费福利是一个任性的女士，她只在宿舍附近停留了 $T$ 秒。因此，如果两个学生的仪式时间差超过 $T$，则免费福利至少无法访问其中一个学生。  

乐观的学生们想知道：最多有多少学生能被免费福利访问。  

## 输入格式  
第一行输入整数 $n$  
第二行输入 $n$ 个整数 $t_i$  
第三行输入整数 $T  

## 输出格式  
输出能被访问的最大学生数  

## 样例输入  
```
6
4 1 7 8 3 8  
1
```

## 样例输出  
```
3
```

---

**算法分类**：排序、二分法、枚举  

---

### 题解综合分析  
本题核心在于寻找一个时间窗口 $[x, x+T]$，使得覆盖的学生数最多。关键点在于：  
1. 所有合法窗口的左端点必须是某个学生的时刻  
2. 最优窗口必定覆盖排序后的某个连续区间  

题解主要分为三类思路：  
1. 暴力枚举每个时刻作为窗口起点（O(n²)）  
2. 排序后使用二分查找窗口边界（O(n log n)）  
3. 利用前缀和统计优化（O(n + M)，M为最大时刻值）  

---

### 精选题解  

#### 1. 崔化博（4星）  
**关键亮点**：  
- 使用排序+二分法，时间复杂度最优  
- 利用STL的`upper_bound`和`lower_bound`简化代码  
- 清晰展示算法优化思路  

**核心代码**：  
```cpp
sort(a+1, a+n+1);
for(int i=1; i<=n; i++) {
    maxn = max(maxn, (long long)(upper_bound(a+1,a+n+1,a[i]+t) 
                               - lower_bound(a+1,a+n+1,a[i])));
}
```

#### 2. Dfkuaid（4星）  
**关键亮点**：  
- 提出前缀和桶计数法，时间复杂度O(n + M)  
- 展示不同优化层次的解题思路  
- 包含代码效率对比的趣味分析  

**核心实现**：  
```cpp
// 桶计数
for(int i=1; i<=n; i++) b[a[i]]++; 
// 前缀和预处理  
for(int i=1; i<=mx+T+1; i++) sum[i] = sum[i-1] + b[i];
// 查询答案
ans = max(ans, sum[a[i]+T] - sum[a[i]-1]);
```

#### 3. Ninelife_Cat（4星）  
**关键亮点**：  
- 排序后使用提前终止的暴力优化  
- 代码简洁易懂，适合小数据量  
- 包含翻译修正的思考过程  

**核心代码**：  
```cpp
sort(a+1, a+n+1);
for(int i=1; i<=n; i++) {
    int cnt = 1;
    for(int j=i+1; j<=n; j++) {
        if(a[j]-a[i] <= t) cnt++;
        else break; // 提前终止优化
    }
    maxn = max(maxn, cnt);
}
```

---

### 最优思路总结  
**关键技巧**：  
1. **排序预处理**：将无序时刻排序，便于后续处理  
2. **二分边界查找**：利用有序性快速确定窗口右端点  
3. **前缀和优化**：当数值范围较小时，桶计数法可达到线性复杂度  

**调试心得**：  
- 注意排序后数组的索引范围（题解中多从1开始）  
- 统计区间时注意闭区间端点处理（`upper_bound`找严格大于的位置）  
- 暴力法中提前终止循环能显著优化实际运行时间  

---

### 拓展训练  
1. **滑动窗口最大值**：[P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
2. **连续区间统计**：[P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)  
3. **时间窗口覆盖**：[P2280 激光炸弹](https://www.luogu.com.cn/problem/P2280)

---
处理用时：58.60秒