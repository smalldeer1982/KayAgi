# 题目信息

# Two Substrings

## 题目描述

You are given string $ s $ . Your task is to determine if the given string $ s $ contains two non-overlapping substrings "AB" and "BA" (the substrings can go in any order).

## 说明/提示

In the first sample test, despite the fact that there are substrings "AB" and "BA", their occurrences overlap, so the answer is "NO".

In the second sample test there are the following occurrences of the substrings: BACFAB.

In the third sample test there is no substring "AB" nor substring "BA".

## 样例 #1

### 输入

```
ABA
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
BACFAB
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
AXBYBXA
```

### 输出

```
NO
```

# AI分析结果



# 题目重写

## 题目描述

给定一个字符串 $s$，判断其中是否存在两个互不重叠的子串 "AB" 和 "BA"（两个子串的顺序可以任意）。

## 说明/提示

第一个样例中虽然存在 "AB" 和 "BA"，但它们重叠，因此输出 "NO"。

第二个样例中存在不重叠的 "AB" 和 "BA"（如 BACFAB 中的 BA 和 AB）。

第三个样例中不存在任何一个子串。

## 样例 #1

### 输入

```
ABA
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
BACFAB
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
AXBYBXA
```

### 输出

```
NO
```

**算法分类**：字符串

---

# 题解分析与结论

### 核心思路
通过两次独立检查：第一次寻找 AB 后替换并检查 BA，第二次寻找 BA 后替换并检查 AB。确保两种顺序都得到验证，避免遗漏情况。

### 最优题解

#### 1. _Clown_（★★★★☆）
**亮点**：  
- 双向覆盖：分别处理 AB→BA 和 BA→AB 两种情况  
- 使用替换操作消除重叠可能性  
- 代码简洁清晰  

**核心代码**：
```cpp
string S,T;
int main() {
    cin>>S,T=S;
    int F=S.find("AB");
    if(F!=-1) {
        S.replace(F,2,"JXT");
        if(S.find("BA")!=-1) { cout<<"YES"; return 0; }
    }
    S=T;
    F=S.find("BA");
    if(F!=-1) {
        S.replace(F,2,"JXT");
        if(S.find("AB")!=-1) { cout<<"YES"; return 0; }
    }
    cout<<"NO";
}
```

#### 2. Steven_Meng（★★★★☆）
**亮点**：  
- 使用特殊字符替换避免干扰  
- 双重检查逻辑清晰  
- 时间复杂度 O(n)  

**核心代码**：
```cpp
string a;
cin>>a;
string tmp=a;
int cnt=0;
// 第一次检查 AB→BA
for(int i=0;i<a.length()-1;i++)
    if(a[i]=='A'&&a[i+1]=='B') {
        a[i]=a[i+1]='~';
        cnt++; break;
    }
for(int i=0;i<a.length()-1;i++)
    if(a[i]=='B'&&a[i+1]=='A' && cnt) { cout<<"YES"; return 0; }
// 第二次检查 BA→AB
a=tmp; cnt=0;
// ...类似处理 BA...
```

#### 3. yuchenren（★★★★☆）
**亮点**：  
- 使用临时副本避免修改原字符串  
- 两次独立检查结构对称  
- 可读性强  

**核心代码**：
```cpp
int AB = s.find("AB");
if(AB != -1) {
    string temp = s;
    temp.replace(AB, 2, ".");
    if(temp.find("BA") != -1) { cout<<"YES"; return 0; }
}
// 类似处理 BA→AB 情况
```

---

# 关键思路总结
1. **双向检查**：必须分别处理 AB→BA 和 BA→AB 两种顺序  
2. **字符串替换**：找到第一个目标子串后，用特殊字符替换以消除重叠可能性  
3. **独立副本**：每次操作使用字符串副本，避免修改影响后续检查  

# 拓展练习
1. [CF550A Two Substrings](https://www.luogu.com.cn/problem/CF550A)（本题原型）  
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)（字符串模式匹配）  
3. [P3370 字符串哈希](https://www.luogu.com.cn/problem/P3370)（字符串唯一性判断）  

---

# 调试经验摘录
- **yzx72424**：首次提交未处理 BA→AB 顺序导致 WA，补充双向检查后 AC  
- **Insouciant21**：通过分析重叠特例 ABA/BAB，提出分情况统计的思路  
- **Mysterious_Cat**：未考虑双向检查导致部分用例失败（样例1）

---
处理用时：118.23秒