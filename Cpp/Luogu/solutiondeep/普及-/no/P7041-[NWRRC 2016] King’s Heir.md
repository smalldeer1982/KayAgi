# 题目信息

# [NWRRC 2016] King’s Heir

## 题目描述



The king is dead, long live the king! After the sudden death of the king Fert XIII the people of the Flatland Kingdom are going to welcome the new king. Unfortunately, there is a problem, Fert has too many sons.

Actually, he has $n$ sons and he loved each new son more than all of his previous sons. Well, probably he just stopped loving his sons because of their bad behavior. Anyway, after the new son was born Fert made the new testament that declared that the newly born son would be the heir.

However, there is a problem. Only the king's son who is at least $18$ years old at the moment of the $king's death$ can become a new king. Now the ministers of the government are trying to find the correct $new king,$ but they seem to fail. Help them!



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
22 10 2016
7
28 2 1999
22 7 1995
21 10 1998
23 10 1998
3 9 2000
1 4 2013
17 12 2004
```

### 输出

```
3
```

## 样例 #2

### 输入

```
22 10 2016
1
28 2 1999
```

### 输出

```
-1
```

# AI分析结果

### 算法分类
排序、模拟

### 综合分析与结论
题目要求从国王的儿子中找出年龄最小且满18岁的继承人。核心思路是通过排序和日期计算来确定符合条件的儿子。大多数题解都采用了排序和日期比较的方法，但实现细节和优化程度有所不同。

### 所选题解
1. **作者：rui_er**  
   - **星级：4星**  
   - **关键亮点**：详细解释了日期计算的逻辑，代码结构清晰，使用了结构体和自定义排序函数，便于理解和维护。  
   - **个人心得**：作者提到数据规模小，因此没有过多优化，但代码的可读性和逻辑性很强。  
   - **核心代码**：
     ```cpp
     int calc(const Node &a, const Node &b) {
         int res = 0;
         if(a.y == b.y) {
             if(a.m == b.m) return b.d - a.d + 1;
             for(int i=a.m+1;i<b.m;i++) res += month[i];
             res += month[a.m] - a.d + 1 + b.d;
             return res;
         }
         for(int i=a.y+1;i<b.y;i++) res += 365;
         for(int i=a.m+1;i<=12;i++) res += month[i];
         for(int i=1;i<b.m;i++) res += month[i];
         res += month[a.m] - a.d + 1 + b.d;
         return res;
     }
     ```

2. **作者：血色黄昏**  
   - **星级：4星**  
   - **关键亮点**：代码简洁，使用了结构体和自定义比较函数，逻辑清晰，易于理解。  
   - **核心代码**：
     ```cpp
     bool cmp(life a, life b) {
         if(a.y > b.y) return true;
         if(a.y == b.y) {
             if(a.m > b.m) return true;
             if(a.m == b.m) {
                 if(a.d > b.d) return true;
             }
         }
         return false;
     }
     ```

3. **作者：StupidSeven**  
   - **星级：4星**  
   - **关键亮点**：代码简洁，使用了结构体和自定义排序函数，逻辑清晰，易于理解。  
   - **核心代码**：
     ```cpp
     bool operator<(const Node &x)const{
         if(year==x.year){
             if(month==x.month)
                 return day>x.day;
             return month>x.month;
         }
         return year>x.year;
     }
     ```

### 最优关键思路或技巧
1. **日期计算**：通过计算两个日期之间的天数差来判断是否满18岁。
2. **排序**：将儿子按出生日期从晚到早排序，便于找到符合条件的继承人。
3. **结构体与自定义排序函数**：使用结构体存储日期信息，并通过自定义排序函数实现排序逻辑。

### 可拓展之处
1. **日期处理**：可以进一步优化日期计算，考虑闰年等特殊情况。
2. **时间复杂度**：虽然数据规模小，但可以优化排序和比较的逻辑，减少不必要的计算。

### 推荐题目
1. P1047 校门外的树
2. P1059 明明的随机数
3. P1068 分数线划定

这些题目都涉及到排序和简单的模拟，适合巩固相关知识点。

---
处理用时：25.34秒