# 题目信息

# Bear and Different Names

## 题目描述

In the army, it isn't easy to form a group of soldiers that will be effective on the battlefield. The communication is crucial and thus no two soldiers should share a name (what would happen if they got an order that Bob is a scouter, if there are two Bobs?).

A group of soldiers is effective if and only if their names are different. For example, a group (John, Bob, Limak) would be effective, while groups (Gary, Bob, Gary) and (Alice, Alice) wouldn't.

You are a spy in the enemy's camp. You noticed $ n $ soldiers standing in a row, numbered $ 1 $ through $ n $ . The general wants to choose a group of $ k $ consecutive soldiers. For every $ k $ consecutive soldiers, the general wrote down whether they would be an effective group or not.

You managed to steal the general's notes, with $ n-k+1 $ strings $ s_{1},s_{2},...,s_{n-k+1} $ , each either "YES" or "NO".

- The string $ s_{1} $ describes a group of soldiers $ 1 $ through $ k $ ("YES" if the group is effective, and "NO" otherwise).
- The string $ s_{2} $ describes a group of soldiers $ 2 $ through $ k+1 $ .
- And so on, till the string $ s_{n-k+1} $ that describes a group of soldiers $ n-k+1 $ through $ n $ .

Your task is to find possible names of $ n $ soldiers. Names should match the stolen notes. Each name should be a string that consists of between $ 1 $ and $ 10 $ English letters, inclusive. The first letter should be uppercase, and all other letters should be lowercase. Names don't have to be existing names — it's allowed to print "Xyzzzdj" or "T" for example.

Find and print any solution. It can be proved that there always exists at least one solution.

## 说明/提示

In the first sample, there are $ 8 $ soldiers. For every $ 3 $ consecutive ones we know whether they would be an effective group. Let's analyze the provided sample output:

- First three soldiers (i.e. Adam, Bob, Bob) wouldn't be an effective group because there are two Bobs. Indeed, the string $ s_{1} $ is "NO".
- Soldiers $ 2 $ through $ 4 $ (Bob, Bob, Cpqepqwer) wouldn't be effective either, and the string $ s_{2} $ is "NO".
- Soldiers $ 3 $ through $ 5 $ (Bob, Cpqepqwer, Limak) would be effective, and the string $ s_{3} $ is "YES".
- ...,
- Soldiers $ 6 $ through $ 8 $ (Adam, Bob, Adam) wouldn't be effective, and the string $ s_{6} $ is "NO".

## 样例 #1

### 输入

```
8 3
NO NO YES YES YES NO
```

### 输出

```
Adam Bob Bob Cpqepqwer Limak Adam Bob Adam```

## 样例 #2

### 输入

```
9 8
YES NO
```

### 输出

```
R Q Ccccccccc Ccocc Ccc So Strong Samples Ccc```

## 样例 #3

### 输入

```
3 2
NO NO
```

### 输出

```
Na Na Na```

# AI分析结果



# Bear and Different Names（熊与不同的名字）

## 题目描述

在军队中，要组建一支在战场上有效的士兵小组并不容易。沟通至关重要，因此任何两名士兵都不应共享相同的名字（如果有两个Bob，当收到命令让Bob担任侦察兵时会发生什么？）。

当且仅当士兵的姓名不同时，一组士兵才是有效的。例如，小组（John、Bob、Limak）是有效的，而小组（Gary、Bob、Gary）和（Alice、Alice）则无效。

你是一名潜入敌方营地的间谍。你注意到有 $n$ 名士兵排成一列，编号为 $1$ 到 $n$。将军想要选择一个由 $k$ 个连续士兵组成的有效小组。对于每个由 $k$ 个连续士兵组成的小组，将军都记录了它们是否有效。

你窃取了将军的笔记，其中包含 $n-k+1$ 个字符串 $s_{1},s_{2},...,s_{n-k+1}$，每个字符串为 "YES" 或 "NO"。

- 字符串 $s_{1}$ 描述的是士兵 $1$ 到 $k$ 组成的小组（"YES" 表示有效）。
- 字符串 $s_{2}$ 描述的是士兵 $2$ 到 $k+1$ 组成的小组。
- 以此类推，直到字符串 $s_{n-k+1}$ 描述士兵 $n-k+1$ 到 $n$ 组成的小组。

你的任务是找出可能的士兵姓名方案。每个姓名应为由 $1$ 到 $10$ 个英文字母组成的字符串，首字母大写，其余字母小写。允许任意生成姓名。

---

## 算法分类
构造

---

## 题解综合分析

### 关键思路总结
1. **构造核心**：对于每个 `NO` 要求，将当前区间的首尾元素设为相同（`s[i+k-1] = s[i]`），确保该区间内有重复，同时不影响后续区间。
2. **唯一性保证**：初始为每个位置生成唯一编号（如整数转26进制），默认所有区间满足 `YES`。
3. **名字生成技巧**：将唯一编号转换为首字母大写+小写字母的字符串（例如整数转26进制，首字符特殊处理）。

### 最优题解推荐

#### 题解作者：E1_de5truct0r（★★★★☆）
**亮点**  
- 使用整数转26进制生成唯一名字，保证初始差异  
- 代码简洁高效，核心逻辑仅需一次遍历  
```cpp
int a[200005];
string turn(int x) {
    string s="";
    while(x) s+=(char)(x%26+'a'),x/=26; 
    s[0] = s[0]-'a'+'A'; // 首字母大写
    return s;
}
// 处理逻辑：
for(int i=1;i<=n-k+1;i++) {
    string x; cin>>x;
    if(x=="NO") a[i+k-1] = a[i]; 
}
```

#### 题解作者：tallnut（★★★★☆）
**亮点**  
- 独立输出函数处理字符串转换，代码模块化  
- 显式注释说明关键步骤  
```cpp
void output_int_as_str(int x) {
    putchar('A'); // 强制首字母大写
    while(x) putchar('a' + x%26), x/=26;
}
// 处理逻辑与上述类似
```

#### 题解作者：qusia_MC（★★★☆☆）
**个人心得**  
- 强调不能简单处理最后两个名字，需考虑k≥3时的连锁影响  
- 使用队列维护当前窗口的名字集合，动态调整重复项  

---

## 类似题目推荐
1. [CF1153B - Serval and Toy Bricks](https://www.luogu.com.cn/problem/CF1153B)（构造三维图形）  
2. [P8109 [CCO2021] Swap Swap Sort](https://www.luogu.com.cn/problem/P8109)（逆向构造交换序列）  
3. [P7984 [USACO21DEC] Air Cownditioning B](https://www.luogu.com.cn/problem/P7984)（差分数组的构造应用）

---
处理用时：45.47秒