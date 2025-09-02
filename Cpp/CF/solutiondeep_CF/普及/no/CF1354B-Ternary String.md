# 题目信息

# Ternary String

## 题目描述

You are given a string $ s $ such that each its character is either 1, 2, or 3. You have to choose the shortest contiguous substring of $ s $ such that it contains each of these three characters at least once.

A contiguous substring of string $ s $ is a string that can be obtained from $ s $ by removing some (possibly zero) characters from the beginning of $ s $ and some (possibly zero) characters from the end of $ s $ .

## 说明/提示

Consider the example test:

In the first test case, the substring 123 can be used.

In the second test case, the substring 213 can be used.

In the third test case, the substring 1223 can be used.

In the fourth test case, the substring 3221 can be used.

In the fifth test case, there is no character 3 in $ s $ .

In the sixth test case, there is no character 1 in $ s $ .

In the seventh test case, the substring 3112 can be used.

## 样例 #1

### 输入

```
7
123
12222133333332
112233
332211
12121212
333333
31121```

### 输出

```
3
3
4
4
0
0
4```

# AI分析结果

### 题目内容重写
# 三元字符串

## 题目描述

给定一个字符串 $s$，其中每个字符都是 1、2 或 3。你需要选择 $s$ 的最短连续子串，使得该子串包含这三个字符至少各一次。

字符串 $s$ 的连续子串是指通过从 $s$ 的开头移除一些（可能为零）字符，并从 $s$ 的末尾移除一些（可能为零）字符得到的字符串。

## 说明/提示

考虑以下示例测试：

在第一个测试用例中，可以使用子串 123。

在第二个测试用例中，可以使用子串 213。

在第三个测试用例中，可以使用子串 1223。

在第四个测试用例中，可以使用子串 3221。

在第五个测试用例中，$s$ 中没有字符 3。

在第六个测试用例中，$s$ 中没有字符 1。

在第七个测试用例中，可以使用子串 3112。

## 样例 #1

### 输入

```
7
123
12222133333332
112233
332211
12121212
333333
31121
```

### 输出

```
3
3
4
4
0
0
4
```

### 算法分类
字符串

### 题解分析与结论
题目要求找到包含1、2、3的最短连续子串。各题解主要采用了滑动窗口、记录字符最后出现位置、前缀和等方法来解决问题。其中，滑动窗口和记录字符最后出现位置的方法较为高效，时间复杂度为O(n)。

### 所选高星题解
1. **作者：vectorwyx (赞：7)**  
   - **星级：5星**  
   - **关键亮点**：将连续相同字符打包成“块”，通过遍历块来寻找最短子串，思路清晰，代码简洁。  
   - **核心代码**：
     ```cpp
     fo(i,R[1]+1,L[t]-1){
         if(a[L[i]-1]!=a[R[i]+1]) ans=min(ans,siz[i]+2);
         i=R[i];
     }
     ```
   - **个人心得**：通过打包连续相同字符，简化了问题，减少了不必要的遍历。

2. **作者：andyli (赞：4)**  
   - **星级：4星**  
   - **关键亮点**：记录字符最后出现的位置，通过计算当前位置与最小最后出现位置的差来更新答案。  
   - **核心代码**：
     ```cpp
     if (s[i] == '1') 
         if (pos1 = i; ~pos2 && ~pos3) 
             chkmin(ans, i - min(pos2, pos3) + 1);
     ```
   - **个人心得**：通过记录字符最后出现的位置，避免了复杂的遍历，提高了效率。

3. **作者：hereiszd (赞：3)**  
   - **星级：4星**  
   - **关键亮点**：使用双指针维护滑动窗口，通过移动指针来寻找最短子串，思路直观。  
   - **核心代码**：
     ```cpp
     while(r<=n){
         if(a&&b&&c){
             if(s[l]=='1')a--;
             if(s[l]=='2')b--;
             if(s[l]=='3')c--;
             l++;
         }
         else{
             r++;
             if(s[r]=='1')a++;
             if(s[r]=='2')b++;
             if(s[r]=='3')c++;
         }
         if(a&&b&&c)cmin(ans,r-l+1);
     }
     ```
   - **个人心得**：通过双指针的滑动窗口，有效地缩小了搜索范围，提高了效率。

### 最优关键思路
将连续相同字符打包成“块”或记录字符最后出现的位置，通过遍历或滑动窗口来寻找最短子串。这两种方法都有效地减少了不必要的遍历，提高了算法的效率。

### 可拓展之处
类似的问题可以扩展到包含更多字符或更复杂条件的最短子串搜索，如包含所有元音字母的最短子串等。

### 推荐题目
1. P1638 字符串的匹配
2. P3375 KMP字符串匹配
3. P3805 Manacher算法

### 个人心得总结
通过打包连续相同字符或记录字符最后出现的位置，可以简化问题，减少遍历次数，提高算法效率。双指针滑动窗口的方法在处理类似问题时也非常有效。

---
处理用时：30.50秒