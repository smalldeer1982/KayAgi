# 题目信息

# Diverse Substring

## 题目描述

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters.

A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, "defor" is a substring of "codeforces" and "fors" is not.

The length of the substring is the number of letters in it.

Let's call some string of length $ n $ diverse if and only if there is no letter to appear strictly more than $ \frac n 2 $ times. For example, strings "abc" and "iltlml" are diverse and strings "aab" and "zz" are not.

Your task is to find any diverse substring of string $ s $ or report that there is none. Note that it is not required to maximize or minimize the length of the resulting substring.

## 说明/提示

The first example has lots of correct answers.

Please, restrain yourself from asking if some specific answer is correct for some specific test or not, these questions always lead to "No comments" answer.

## 样例 #1

### 输入

```
10
codeforces
```

### 输出

```
YES
code
```

## 样例 #2

### 输入

```
5
aaaaa
```

### 输出

```
NO
```

# AI分析结果



---

**算法分类**: 字符串处理

---

### **题解思路与核心难点**
**核心思路**: 寻找任意相邻两个不同字符，组成长度为2的子串。此时每个字符出现次数为1，满足条件（1 ≤ 2/2）。若无相邻不同字符，则整个字符串全相同，输出NO。  
**难点对比**:  
- **O(n)解法**：遍历一次字符串，检查相邻字符是否不同。时间复杂度低，适用于所有情况。  
- **O(n²)暴力解法**：遍历所有子串，统计字符频率。虽然正确，但效率低，不必要。  

**结论**: 最优解法是O(n)的相邻字符检查法。

---

### **题解评分 (≥4星)**
1. **Annihilation_y (5星)**: 代码简洁高效，直接解决问题，无需额外数据结构。  
2. **liuyz11 (4星)**: 思路清晰，代码规范，但变量命名稍显冗余。  
3. **OoXiao_QioO (4星)**: 详细注释和思路解释，适合初学者理解。  

---

### **最优思路与技巧**
- **关键技巧**: 利用子串长度为2的特性，将问题简化为相邻字符检查。  
- **思维突破**: 观察到短子串更容易满足条件，避免复杂统计。  
- **代码实现**: 只需一次遍历，无需复杂数据结构。  

---

### **同类型题目推荐**
- **CF1073A (原题)**: 直接考察相同思路。  
- **CF1325B**: 统计不同元素，类似字符频率问题。  
- **LeetCode 3**: 最长无重复子串，滑动窗口思想。  

---

### **代码实现 (核心逻辑)**
```cpp
// 关键代码片段 (Annihilation_y)
for (int i = 2; i <= len; i++) {
    if (s[i] != s[i - 1]) {
        printf("YES\n%c%c", s[i - 1], s[i]);
        return 0;
    }
}
printf("NO");
```

---

### **可视化设计 (像素风格演示)**
**动画流程**:  
1. **像素网格**: 字符串以8位像素字符显示，每个字符占据一个方块。  
2. **遍历指针**: 用红色方块标记当前字符，绿色箭头指示比较方向（前一个字符）。  
3. **发现解**: 当相邻字符不同时，两字符闪烁黄色，播放“成功”音效（8-bit短音）。  
4. **无解情况**: 遍历结束后，全字符串变灰色，播放低沉音效。  

**交互功能**:  
- **速度调节**: 滑动条控制遍历速度（50ms~2s）。  
- **自动演示**: 点击“Auto”按钮，自动执行并高亮关键步骤。  

**音效设计**:  
- **成功音**: 高频“哔”声（类似《超级马里奥》金币音效）。  
- **失败音**: 低频“嘟”声（类似《俄罗斯方块》Game Over）。  

---

### **个人心得摘录**
- **顿悟点**: 题目要求子串“任意”，不必追求最长或最短，最短的可行解往往更易处理。  
- **调试教训**: 初始代码未处理全相同字符情况，通过测试样例2发现逻辑漏洞。  

---

**可视化演示示例**:  
![Pixel Animation Demo](https://via.placeholder.com/600x200/000000/FFFFFF?text=codeforces→遍历到'o'与'd'时闪烁)  
（实际实现中为动态像素动画，需配合音效与交互控件）

---
处理用时：95.52秒