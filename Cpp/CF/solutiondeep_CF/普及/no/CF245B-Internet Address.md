# 题目信息

# Internet Address

## 题目描述

Vasya is an active Internet user. One day he came across an Internet resource he liked, so he wrote its address in the notebook. We know that the address of the written resource has format:

 <protocol>://<domain>.ru\[/<context>\]where:

- <protocol> can equal either "http" (without the quotes) or "ftp" (without the quotes),
- <domain> is a non-empty string, consisting of lowercase English letters,
- the /<context> part may not be present. If it is present, then <context> is a non-empty string, consisting of lowercase English letters.

If string <context> isn't present in the address, then the additional character "/" isn't written. Thus, the address has either two characters "/" (the ones that go before the domain), or three (an extra one in front of the context).

When the boy came home, he found out that the address he wrote in his notebook had no punctuation marks. Vasya must have been in a lot of hurry and didn't write characters ":", "/", ".".

Help Vasya to restore the possible address of the recorded Internet resource.

## 说明/提示

In the second sample there are two more possible answers: "ftp://httpruru.ru" and "ftp://httpru.ru/ru".

## 样例 #1

### 输入

```
httpsunrux
```

### 输出

```
http://sun.ru/x
```

## 样例 #2

### 输入

```
ftphttprururu
```

### 输出

```
ftp://http.ru/ruru
```

# AI分析结果



【题目翻译】  
# 互联网地址  

## 题目描述  

Vasya 是个活跃的互联网用户。某天他发现了一个有趣的网络资源，于是将地址记在笔记本上。已知正确的地址格式为：  

 `<协议>://<域名>.ru[/<上下文>]`，其中：  
- <协议> 只能是 "http" 或 "ftp"（不带引号）  
- <域名> 是非空的小写字母字符串  
- /<上下文> 为可选部分。若存在，则 <上下文> 必须是非空的小写字母字符串  

当没有上下文时，最后的斜杠不显示。地址中要么有两个"/"（在协议后和域名前），要么有三个（多一个在上下文前）。  

Vasya 回家后发现记录的地址丢失了所有标点符号（冒号、斜杠、点号）。现在需要根据输入的字符串还原可能的合法地址。  

## 输入输出样例  
样例1：  
输入：`httpsunrux`  
输出：`http://sun.ru/x`  

样例2：  
输入：`ftphttprururu`  
输出：`ftp://http.ru/ruru`  

【算法分类】  
字符串、模拟  

【题解分析】  

▍关键思路对比  
1. 协议识别：所有题解均通过首字母判断协议类型（'h'→http，'f'→ftp）  
2. ru定位：主要分歧点在于如何选择ru的位置：  
   - 正向首个ru（qinshi0308）：可能产生空域名（如"ftpru..."）  
   - 反向首个ru（A524）：保证域名非空  
3. 输出处理：多数题解在找到ru后分三段处理（协议头、域名、上下文）  

▍优质题解推荐  
1. 作者：A524（⭐⭐⭐⭐⭐）  
   亮点：  
   - 逆向寻找第一个ru，确保域名非空  
   - 处理末尾ru时自动省略斜杠  
   核心代码：  
   ```cpp  
   if (s[0]=='f') { /* 处理ftp协议 */ }  
   for (int i = sta+1; i < sz-1; i++) {  
       if (s[i]=='r' && s[i+1]=='u') {  
           // 输出域名并设置上下文起点  
       }  
   }  
   // 处理上下文  
   ```  

2. 作者：TheCliffSwallow（⭐⭐⭐⭐）  
   亮点：  
   - 使用状态变量记录处理位置  
   - 明确分割域名和上下文的边界  
   核心代码：  
   ```cpp  
   for(int i=sta+1; i<s.size()-1; i++){  
       if (找到ru) {  
           // 输出域名部分  
           break;  
       }  
   }  
   // 输出上下文  
   ```  

3. 作者：708151_qwq（⭐⭐⭐）  
   亮点：  
   - 使用flag标记首次出现的ru  
   - 处理末尾ru的特殊情况  
   核心代码：  
   ```cpp  
   bool flag = true;  
   for(;i<len;i++){  
       if (发现ru且flag) {  
           // 输出.ru或.ru/  
           flag = false;  
       }  
   }  
   ```  

▍关键技巧总结  
1. 逆向寻找ru：优先从后往前找第一个ru，确保域名部分有字符（如样例2的"http.ru"）  
2. 协议处理：通过首字母快速判断协议类型，直接输出对应前缀  
3. 边界处理：当ru出现在字符串末尾时，不添加多余的斜杠  

【举一反三】  
1. 类似题型：CF978B（文件名处理）、CF734B（字符串构造）  
2. 核心训练点：  
   - 字符串分割与重构  
   - 边界条件处理（空字段、末尾字符）  

【推荐习题】  
1. P1109 [NOIP2001 普及组] 域名生成（字符串构造）  
2. CF978B File Name（字符删除处理）  
3. CF734B Anton and Digits（字符串格式验证）  

▍调试心得摘录  
- A524提到：最初采用正向查找时，遇到"ftpru..."会导致空域名，改为逆向查找后解决  
- qinshi0308的代码在样例2中可能输出其他合法答案（需注意题目允许多解）

---
处理用时：52.39秒