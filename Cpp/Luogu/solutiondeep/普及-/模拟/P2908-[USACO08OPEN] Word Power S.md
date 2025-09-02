# 题目信息

# [USACO08OPEN] Word Power S

## 题目描述

Farmer John wants to evaluate the quality of the names of his N (1 <= N <= 1000) cows. Each name is a string with no more than 1000 characters, all of which are non-blank.

He has created a set of M (1 <= M <= 100) 'good' strings (no

longer than 30 characters and fully non-blank). If the sequence letters of a cow's name contains the letters of a 'good' string in the correct order as a subsequence (i.e., not necessarily all next to each other), the cow's name gets 1 quality point.

All strings is case-insensitive, i.e., capital letters and lower case letters are considered equivalent.  For example, the name 'Bessie' contains the letters of 'Be', 'sI', 'EE', and 'Es' in the correct order, but not 'is' or 'eB'. Help Farmer John determine the number of quality points in each of his cow's names.

约翰想要计算他那N(l < =N <= 1000)只奶牛的名字的能量.每只奶牛的名字由不超过1000个字 符构成，没有一个名字是空字体串.

约翰有一张“能量字符串表”，上面有M(1 < =M < =100)个代表能量的字符串.每个字符串 由不超过30个字体构成，同样不存在空字符串.一个奶牛的名字蕴含多少个能量字符串，这个名 字就有多少能量.所谓“蕴含”，是指某个能量字符串的所有字符都在名字串中按顺序出现（不 一定一个紧接着一个）.

所有的大写字母和小写字母都是等价的.比如，在贝茜的名字“Bessie”里，蕴含有“Be” “si” “EE”以及“Es”等等字符串，但不蕴含“Ls”或“eB” .请帮约翰计算他的奶牛的名字 的能量.


## 说明/提示

There are 5 cows, and their names are "Bessie", "Jonathan", "Montgomery", "Alicia", and "Angola". The 3 good strings are "se", "nGo", and "Ont".


"Bessie" contains "se", "Jonathan" contains "Ont", "Montgomery" contains both "nGo" and "Ont", Alicia contains none of the good strings, and "Angola" contains "nGo".


## 样例 #1

### 输入

```
5 3 
Bessie 
Jonathan 
Montgomery 
Alicia 
Angola 
se 
nGo 
Ont 
```

### 输出

```
1 
1 
2 
0 
1 
```

# AI分析结果

• 综合分析与结论：这几道题解思路相近，均采用模拟方法解决问题。算法要点在于读入奶牛名字和“好”字符串后，统一字符串大小写，再遍历判断每个“好”字符串是否为奶牛名字的子序列。解决难点主要是字符串大小写处理以及子序列判断。在代码实现上，不同题解采用了不同方式，如有的使用string自带函数，有的自定义函数判断子序列，还有的使用STL中的transform函数处理大小写转换。综合质量来看，整体题解质量未达4星。
• 通用建议与扩展思路：
    - 思路方面，对于此类字符串匹配问题，可尝试不同匹配算法，如KMP算法，在字符串较长时能优化时间复杂度。
    - 代码实现上，可注重函数封装，提高代码可读性；合理使用STL容器和算法，简化代码。同时，注意边界条件处理，如字符串为空的情况。同类型题或类似算法套路通常涉及字符串匹配、子序列查找等，可拓展到判断一个字符串是否为另一个字符串的子串、查找最长公共子序列等问题。
• 相似知识点洛谷题目：
    - P1308 统计单词数，涉及字符串查找与统计。
    - P3375 【模板】KMP字符串匹配，考察KMP匹配算法。
    - P1439 【模板】最长公共子序列，与本题判断子序列思路相关。 

---
处理用时：18.09秒