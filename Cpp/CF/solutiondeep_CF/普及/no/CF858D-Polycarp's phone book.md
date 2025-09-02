# 题目信息

# Polycarp's phone book

## 题目描述

There are $ n $ phone numbers in Polycarp's contacts on his phone. Each number is a 9-digit integer, starting with a digit different from $ 0 $ . All the numbers are distinct.

There is the latest version of Berdroid OS installed on Polycarp's phone. If some number is entered, is shows up all the numbers in the contacts for which there is a substring equal to the entered sequence of digits. For example, is there are three phone numbers in Polycarp's contacts: $ 123456789 $ , $ 100000000 $ and $ 100123456 $ , then:

- if he enters $ 00 $ two numbers will show up: $ 100000000 $ and $ 100123456 $ ,
- if he enters $ 123 $ two numbers will show up $ 123456789 $ and $ 100123456 $ ,
- if he enters $ 01 $ there will be only one number $ 100123456 $ .

For each of the phone numbers in Polycarp's contacts, find the minimum in length sequence of digits such that if Polycarp enters this sequence, Berdroid shows this only phone number.

## 样例 #1

### 输入

```
3
123456789
100000000
100123456
```

### 输出

```
9
000
01
```

## 样例 #2

### 输入

```
4
123456789
193456789
134567819
934567891
```

### 输出

```
2
193
81
91
```

# AI分析结果



# 题目内容重写

### 题目名称：Polycarp的电话簿

## 题目描述

Polycarp的手机通讯录中有 $n$ 个电话号码。每个号码都是9位数字，不以0开头，且所有号码互不相同。

当输入一串数字时，Berdroid系统会显示所有包含该数字串作为子串的号码。例如通讯录中有三个号码：$123456789$、$100000000$、$100123456$ 时：
- 输入"00"会显示后两个号码
- 输入"123"会显示第一个和第三个号码
- 输入"01"只显示第三个号码

任务是为每个号码找到最短的识别码（即子串），使得输入该子串时只会显示对应的号码。

---

# 算法分类
**字符串**

---

# 题解分析与结论

## 核心思路对比

| 方法        | 思路                                                                 | 时间复杂度          | 空间复杂度        |
|-----------|--------------------------------------------------------------------|-------------------|-----------------|
| 字典树       | 对所有号码的所有子串建字典树，动态删除当前号码子串后查询最短唯一子串                    | O(Σk^2) k=9       | O(Σk^2)         |
| map暴力统计  | 预处理所有子串出现次数，每个子串用set去重后存入map，最后为每个号码寻找出现次数为1的最短子串 | O(nk^2 + nk^3)    | O(nk^2)         |

## 最优题解推荐

1. **404Not_Found的字典树解法（⭐⭐⭐⭐⭐）**
   - **亮点**：利用动态删除当前号码子串的特性，通过字典树快速查询最短唯一子串
   - **关键代码**：
     ```cpp
     void query(char *s) {
         for(int i=0; i<len; i++) {
             tmp[i] = s[i];
             int to = trie[now].next[id];
             if(trie[to].val == 0) { // 找到唯一子串
                 strcpy(ans, tmp);
                 break;
             }
         }
     }
     ```
   - **心得**：强调字典树的空间消耗问题，需注意节点数估算（总子串数约7e4*45=3.15e6）

2. **kimi0705的map解法（⭐⭐⭐⭐）**
   - **亮点**：利用set去重确保每个子串在同号码中只计数一次，按长度从小到大搜索
   - **关键优化**：
     ```cpp
     set<string> SET; // 去重容器
     if(!SET.count(S)) {
         C[S]++;
         SET.insert(S);
     }
     ```

---

# 关键技巧总结

1. **字典树动态维护**：通过插入-删除-再插入的流程，实现实时查询当前号码的独占子串
2. **子串去重统计**：使用set容器确保同一号码的重复子串不重复计数
3. **剪枝优化**：按子串长度从小到大遍历，找到首个合法解即可提前终止

---

# 拓展延伸

**同类问题特征**：需要快速查询字符串集的唯一标识子串。类似问题包括：
1. 最短唯一前缀（P2580）
2. 子串频率统计（P2922）
3. 最小特征码生成（P1737）

---

# 推荐习题
1. [P2580 错误的点名](https://www.luogu.com.cn/problem/P2580) - 字典树基础应用
2. [P2922 Secret Message](https://www.luogu.com.cn/problem/P2922) - 前缀匹配计数
3. [P1737 寻找最短唯一子串](https://www.luogu.com.cn/problem/P1737) - 同类问题变式

---
处理用时：49.51秒