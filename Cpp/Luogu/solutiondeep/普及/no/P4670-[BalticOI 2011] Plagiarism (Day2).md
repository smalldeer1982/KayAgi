# 题目信息

# [BalticOI 2011] Plagiarism (Day2)

## 题目描述

The participants of the World Programming Competition submitted $N$ solution files $f_1 ,...,f_N$ to the grading system. Before accepting the results as final, the jury would like to rule out any possibility of plagiarism. They have a program that takes two files and compares them to decide if they are too similar to each other.

However, the number of files is rather big and it would take too much time to compare all pairs. On the other hand, many pairs could be quickly eliminated based on the fact that the file sizes are too different.

More precisely, the jury decided to fully skip comparing every pair where the size of the smaller file is less than 90% of the size of the larger one. So, the comparison program has to examine only those distinct pairs of files $(f_i, f_j)$ where $i≠j, size(f_i) \le size(f_j)$ and $size(f_i) \ge 0.9 \times size(f_j)$.

Write a program that computes the number of pairs of files that will have to be examined.

## 说明/提示

对于 $50\%$ 的数据，$1 \le N \le 2000$。

对于所有数据，$1 \le N \le 10^5,1 \le f_i \le 10^8$。

## 样例 #1

### 输入

```
2
2 1```

### 输出

```
0```

## 样例 #2

### 输入

```
5
1 1 1 1 1```

### 输出

```
10```

# AI分析结果



**算法分类**: 排序、双指针/二分

**综合分析**  
题目核心在于高效统计满足条件的数对。由于直接枚举会超时，必须利用排序后的单调性优化。各题解主要采用两种方法：双指针（O(n)）或二分查找（O(n log n)），均通过排序预处理简化问题。

---

**精选题解**  

1. **TinyKiecoo（⭐⭐⭐⭐⭐）**  
- **关键亮点**: 双指针法巧妙利用排序后的单调性，维护左边界避免重复计算，时间复杂度O(n)。  
- **核心代码**:  
  ```cpp
  sort(f+1,f+1+n,cmp);  // 从大到小排序
  for(int i=1; i<=n; i++) {
      for(int j=l+1; j<=n; j++) {
          if(f[i]*9 <= f[j]*10) l = j;
          else break;
      }
      s += l - i;  // 统计合法区间长度
  }
  ```

2. **Kevin_Wa（⭐⭐⭐⭐⭐）**  
- **关键亮点**: 从小到大排序，维护右边界指针，代码简洁高效。  
- **核心代码**:  
  ```cpp
  sort(a+1,a+n+1);  // 从小到大排序
  int w=2;
  for(int i=1; i<=n; i++) {
      while(a[w]*9 <=10*a[i] && w<=n) w++;
      ans += w - i -1;  // 当前i的合法右端点
  }
  ```

3. **oimaster（⭐⭐⭐⭐）**  
- **关键亮点**: 使用STL的`lower_bound`实现二分，代码简洁易懂。  
- **核心代码**:  
  ```cpp
  sort(a+1,a+n+1);  // 从小到大排序
  for(int i=1; i<=n; i++) {
      int now=ceil(a[i]*0.9);
      int j=lower_bound(a+1,a+i,now) -a;  // 找到第一个>=now的位置
      sum += i - j;
  }
  ```

---

**最优技巧总结**  
- **排序预处理**: 将数组排序后利用单调性，避免暴力枚举。  
- **双指针法**: 维护一个随i递增的指针，确保每个元素仅遍历一次，达到O(n)复杂度。  
- **边界处理**: 注意浮点数比较精度问题（如转换为整数运算：`a[j]*9 >= a[i]*10`）。

---

**拓展与举一反三**  
- **同类问题**: 统计满足特定比例或差值条件的数对（如LC两数之和、三数之和）。  
- **推荐题目**:  
  1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)  
  2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)  
  3. [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)（双指针思想）  

---

**题解心得摘录**  
- **TinyKiecoo**: "若f[i]×0.9>f[j]，则后面的数也无需比较" —— 利用单调性提前终止内层循环。  
- **Kevin_Wa**: "w表示前一个数无法匹配的位置，初值赋为2" —— 从小到大的双指针初始化技巧。  
- **do_while_true**: "sort本身就是O(nlogn)时间复杂度" —— 提醒算法复杂度分析的完整性。

---
处理用时：46.63秒