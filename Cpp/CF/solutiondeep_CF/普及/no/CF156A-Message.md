# 题目信息

# Message

## 题目描述

Dr. Moriarty is about to send a message to Sherlock Holmes. He has a string $ s $ .

String $ p $ is called a substring of string $ s $ if you can read it starting from some position in the string $ s $ . For example, string "aba" has six substrings: "a", "b", "a", "ab", "ba", "aba".

Dr. Moriarty plans to take string $ s $ and cut out some substring from it, let's call it $ t $ . Then he needs to change the substring $ t $ zero or more times. As a result, he should obtain a fixed string $ u $ (which is the string that should be sent to Sherlock Holmes). One change is defined as making one of the following actions:

- Insert one letter to any end of the string.
- Delete one letter from any end of the string.
- Change one letter into any other one.

Moriarty is very smart and after he chooses some substring $ t $ , he always makes the minimal number of changes to obtain $ u $ .

Help Moriarty choose the best substring $ t $ from all substrings of the string $ s $ . The substring $ t $ should minimize the number of changes Moriarty should make to obtain the string $ u $ from it.

## 说明/提示

In the first sample Moriarty can take any substring of length $ 3 $ , and it will be equal to the required message $ u $ , so Moriarty won't have to make any changes.

In the second sample you should take a substring consisting of characters from second to fourth ("bca") or from fifth to sixth ("bc"). Then you will only have to make one change: to change or to add the last character.

In the third sample the initial string $ s $ doesn't contain any character that the message should contain, so, whatever string you choose, you will have to make at least $ 7 $ changes to obtain the required message.

## 样例 #1

### 输入

```
aaaaa
aaa
```

### 输出

```
0
```

## 样例 #2

### 输入

```
abcabc
bcd
```

### 输出

```
1
```

## 样例 #3

### 输入

```
abcdef
klmnopq
```

### 输出

```
7
```

# AI分析结果



# Message

## 题目描述

莫里亚蒂博士要给夏洛克·福尔摩斯发送一条消息。他有一个字符串 $s$。

如果可以从字符串 $s$ 的某个位置开始连续读取得到字符串 $p$，则称 $p$ 是 $s$ 的子串。例如字符串 "aba" 有六个子串："a", "b", "a", "ab", "ba", "aba"。

莫里亚蒂计划从字符串 $s$ 中截取一个子串 $t$，然后对这个子串进行零次或多次修改，最终得到固定字符串 $u$（即要发送给福尔摩斯的消息）。每次修改可以是以下三种操作之一：
- 在任意一端插入一个字符
- 从任意一端删除一个字符
- 将任意一个字符替换为其他字符

莫里亚蒂非常聪明，在选定子串 $t$ 后，他总是以最少的修改次数将 $t$ 转换为 $u$。

请帮助莫里亚蒂从 $s$ 的所有子串中选择最优的 $t$，使得将 $t$ 转换为 $u$ 所需的修改次数最少。

## 说明/提示

第一个样例中可以选择任意长度为 3 的子串，它们都与目标字符串 $u$ 相同，无需修改。

第二个样例中选择第二到第四个字符（"bca"）或第五到第六个字符（"bc"），均只需一次修改。

第三个样例中原始字符串 $s$ 与目标字符串 $u$ 没有共同字符，至少需要 7 次修改。

## 样例 #1

### 输入
```
aaaaa
aaa
```

### 输出
```
0
```

## 样例 #2

### 输入
```
abcabc
bcd
```

### 输出
```
1
```

---

**算法分类**：字符串、枚举

**综合分析**：  
本题核心在于通过滑动窗口思想，枚举所有可能的对齐方式，寻找最大匹配字符数。由于操作限制在两端插入/删除，问题转化为寻找 $u$ 在 $s$ 中任意连续或扩展子序列的最大匹配。

---

### 高分题解精选

#### 题解作者：fuxuantong123 ⭐⭐⭐⭐⭐  
**关键亮点**：  
1. 简洁的暴力枚举实现，覆盖所有可能的对齐方式  
2. 通过负数索引处理前缀插入的情况  
3. 时间复杂度 O(nm) 完全可行  

**核心代码**：  
```cpp
string s,b;
int ans=2147483647;
cin>>s>>b;
for(int i=-b.size();i<s.size();i++){ // 枚举所有可能的起始偏移
    int cnt=0;
    for(int j=0;j<b.size();j++){      // 逐字符比对
        if(i+j>=0 && i+j<s.size() && s[i+j]==b[j]) cnt++;
    }
    ans=min(ans, (int)b.size()-cnt);
}
cout<<ans;
```

#### 题解作者：iiawaKL ⭐⭐⭐⭐  
**实现技巧**：  
- 扩展枚举范围到 -2000 确保覆盖边界情况  
- 清晰直观的匹配计数逻辑  

**调试心得**：  
> "i的负值范围需要足够大才能覆盖所有可能的前缀插入情况，这里直接取-2000保证题目约束下的正确性。"

---

**最优思路总结**：  
通过枚举 $u$ 在 $s$ 上的所有可能偏移量（包括负数偏移代表前缀插入），计算每个偏移下的最大匹配字符数。最终答案即为 $u$ 长度减去最大匹配数。该解法巧妙利用了操作限制的特性，将问题转化为滑动窗口比对。

**拓展延伸**：  
类似题目可考虑：
1. 编辑距离问题（操作限制不同）
2. 最长公共子序列问题
3. 带通配符的字符串匹配

**推荐练习**：  
1. 洛谷 P2758 编辑距离  
2. 洛谷 P1143 最长公共子序列  
3. 洛谷 P3375 KMP字符串匹配

---
处理用时：91.41秒