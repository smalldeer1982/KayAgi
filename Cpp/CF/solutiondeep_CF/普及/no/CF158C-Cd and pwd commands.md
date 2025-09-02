# 题目信息

# Cd and pwd commands

## 题目描述

Vasya is writing an operating system shell, and it should have commands for working with directories. To begin with, he decided to go with just two commands: cd (change the current directory) and pwd (display the current directory).

Directories in Vasya's operating system form a traditional hierarchical tree structure. There is a single root directory, denoted by the slash character "/". Every other directory has a name — a non-empty string consisting of lowercase Latin letters. Each directory (except for the root) has a parent directory — the one that contains the given directory. It is denoted as "..".

The command cd takes a single parameter, which is a path in the file system. The command changes the current directory to the directory specified by the path. The path consists of the names of directories separated by slashes. The name of the directory can be "..", which means a step up to the parent directory. «..» can be used in any place of the path, maybe several times. If the path begins with a slash, it is considered to be an absolute path, that is, the directory changes to the specified one, starting from the root. If the parameter begins with a directory name (or ".."), it is considered to be a relative path, that is, the directory changes to the specified directory, starting from the current one.

The command pwd should display the absolute path to the current directory. This path must not contain "..".

Initially, the current directory is the root. All directories mentioned explicitly or passed indirectly within any command cd are considered to exist. It is guaranteed that there is no attempt of transition to the parent directory of the root directory.

## 样例 #1

### 输入

```
7
pwd
cd /home/vasya
pwd
cd ..
pwd
cd vasya/../petya
pwd
```

### 输出

```
/
/home/vasya/
/home/
/home/petya/
```

## 样例 #2

### 输入

```
4
cd /a/b
pwd
cd ../a/b
pwd
```

### 输出

```
/a/b/
/a/a/b/
```

# AI分析结果



【题目翻译】  
# cd 和 pwd 命令  

## 题目描述  
Vasya 正在编写一个操作系统 shell，需要支持目录操作命令。目前实现了两个命令：cd（切换当前目录）和 pwd（显示当前目录）。  

目录结构采用传统的树状层级结构：  
- 根目录用单个斜杠 "/" 表示  
- 每个目录（除根目录）有名称（由小写字母组成）  
- ".." 表示父目录  

cd 命令接收一个路径参数：  
- 以斜杠开头的路径是绝对路径（从根目录开始）  
- 否则是相对路径（从当前目录开始）  
- 路径可能包含多个 ".." 表示回退父目录  

pwd 命令必须输出不含 ".." 的绝对路径，且路径必须以 "/" 结尾  

初始当前目录为根目录，保证所有操作合法（不会回退到根目录的上级）  

【算法分类】  
模拟  

---

### 题解综合分析  
各解法的核心思路均围绕路径解析与栈式存储：  
1. **栈/列表维护路径层级**：最优解法（如 JerryMao、nxd_oxm）利用 vector/stack 存储目录层级，通过压栈/弹栈处理路径变化，逻辑清晰  
2. **字符串拼接**：直接操作字符串（如 Withershine）需处理复杂截取逻辑，易出错  
3. **路径分割技巧**：统一在路径末尾加斜杠，便于分割处理（关键优化点）  

---

### 精选题解  

#### 1. JerryMao（⭐⭐⭐⭐⭐）  
**核心思路**：  
- 使用 `vector<string>` 存储目录层级  
- 绝对路径时清空 vector  
- 逐个处理路径片段，".." 则弹栈，否则压栈  
**代码亮点**：  
```cpp  
vector<string> v;  // 存储目录层级

// 处理 cd 命令的核心逻辑  
string s;  
cin >> s;  
if(s[0] == '/') v.clear();  // 绝对路径清空
s += '/';  // 统一加斜杠便于分割
for(int i=0; i<s.size(); ) {
    string t;
    while(s[i] != '/') t += s[i++];  // 提取路径片段
    if(t == "..") v.pop_back();
    else if(!t.empty()) v.push_back(t);
    i++;  // 跳过斜杠
}
```  
**心得**：初始未清空 vector 导致 WA，强调边界检查的重要性  

#### 2. nxd_oxm（⭐⭐⭐⭐）  
**核心思路**：  
- 手动实现栈结构存储目录  
- 分割路径时直接处理每个片段  
**代码亮点**：  
```cpp  
string s[10001];  // 栈结构
int top = 0;      // 栈顶指针

// 处理绝对路径
if(add[0] == '/') {  
    top = 0;      // 清空栈
    for(分割路径...) {
        if(片段是"..") pops(); 
        else pushs(片段);
    }
}
```  
**优势**：栈操作直观体现目录层级变化  

---

### 关键技巧总结  
1. **统一路径格式**：在路径末尾追加斜杠，避免边界判断  
2. **层级存储结构**：使用栈/列表维护目录层级，天然支持 ".." 回退操作  
3. **路径分割策略**：按斜杠分割后逐个处理片段，逻辑清晰  

---

### 拓展练习  
1. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)（栈结构应用）  
2. [P3958 NOIP2017 奶酪](https://www.luogu.com.cn/problem/P3958)（三维路径模拟）  
3. [P1024 NOIP2001 一元三次方程求解](https://www.luogu.com.cn/problem/P1024)（分治与路径搜索）

---
处理用时：62.17秒