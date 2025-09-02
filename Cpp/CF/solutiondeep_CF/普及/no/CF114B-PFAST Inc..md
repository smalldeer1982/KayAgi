# 题目信息

# PFAST Inc.

## 题目描述

When little Petya grew up and entered the university, he started to take part in АСМ contests. Later he realized that he doesn't like how the АСМ contests are organised: the team could only have three members (and he couldn't take all his friends to the competitions and distribute the tasks between the team members efficiently), so he decided to organize his own contests PFAST Inc. — Petr and Friends Are Solving Tasks Corporation. PFAST Inc. rules allow a team to have unlimited number of members.

To make this format of contests popular he organised his own tournament. To create the team he will prepare for the contest organised by the PFAST Inc. rules, he chose several volunteers (up to 16 people) and decided to compile a team from them. Petya understands perfectly that if a team has two people that don't get on well, then the team will perform poorly. Put together a team with as many players as possible given that all players should get on well with each other.

## 样例 #1

### 输入

```
3 1
Petya
Vasya
Masha
Petya Vasya
```

### 输出

```
2
Masha
Petya
```

## 样例 #2

### 输入

```
3 0
Pasha
Lesha
Vanya
```

### 输出

```
3
Lesha
Pasha
Vanya
```

# AI分析结果



# PFAST Inc.

## 题目描述

小 Petya 进入大学后开始参加 ACM 竞赛，但不满三人组队限制，遂创立 PFAST Inc. 规则允许任意人数组队。现需从最多 16 名志愿者中组建最大无矛盾团队，要求团队中任意两人无敌对关系。

## 样例 #1

### 输入
```
3 1
Petya
Vasya
Masha
Petya Vasya
```

### 输出
```
2
Masha
Petya
```

## 样例 #2

### 输入
```
3 0
Pasha
Lesha
Vanya
```

### 输出
```
3
Lesha
Pasha
Vanya
```

---

**算法分类**：枚举（二进制枚举/DFS）

---

### 题解综合分析

所有题解均基于暴力枚举思想，核心要点如下：
1. **二进制枚举**：利用位运算表示选择状态，复杂度 O(2ⁿ)
2. **敌对关系预处理**：将字符串转换为编号，建立二维标记数组
3. **字典序处理**：提前对名字排序，避免输出时二次排序
4. **最优解更新**：通过打擂台机制维护最大人数解

---

### 精选题解（评分≥4星）

#### 1. 作者：404Not_Found（评分：★★★★☆）
**核心亮点**：
- 状态压缩实现高效枚举
- 预处理名称排序解决字典序输出问题
- 二维数组存储敌对关系，O(1)时间验证矛盾
```cpp
// 核心代码片段
sort(s,s+n); // 预处理字典序
for(int i=0;i<(1<<n);i++) { // 二进制枚举
    bool valid = true;
    for(int j=0;j<m;j++) { // 检查所有敌对对
        int x=hashs(v[j].first), y=hashs(v[j].second);
        if((i&(1<<x)) && (i&(1<<y))) valid = false;
    }
    if(valid) update_answer(i);
}
```

#### 2. 作者：xiaomuyun（评分：★★★★☆）
**核心亮点**：
- 使用 pair<string,string> 直接存储敌对关系
- DFS 剪枝优化，提前终止无效分支
- 自动维护字典序的答案数组
```cpp
void dfs(int x, string a[], int len) {
    if(len <= max_len) return; // 剪枝优化
    // 检查所有可能矛盾对
    for(int i=1;i<=len;i++) 
        for(int j=i+1;j<=len;j++)
            if(存在矛盾) return;
    // 更新最优解
}
```

#### 3. 作者：_Wind_Leaves_ShaDow_（评分：★★★★☆）
**创新优化**：
- 递推预处理 popcount 优化计数
- 位运算快速验证矛盾关系
- 线性时间复杂度处理冲突检查
```cpp
for(int i=0;i<(1<<n);i++) {
    cnt[i] = cnt[i>>1] + (i&1); // 递推统计1的个数
    for(int j=0;j<=m;j++) { // 快速冲突检查
        if(j&&(i&(1<<a[j][0]))&&(i&(1<<a[j][1]))) break;
        if(j==m) ans=i;
    }
}
```

---

### 关键思路总结

1. **状态压缩技巧**：用整数的二进制位表示选择状态，16人对应16位
2. **名称离散化**：通过 map 或排序建立字符串到编号的映射
3. **矛盾验证优化**：建立 O(1) 访问的二维标记数组
4. **输出优化**：预先排序解决字典序要求，避免最终排序开销

---

### 类似题目推荐

1. [P1032 字串变换](https://www.luogu.com.cn/problem/P1032) - BFS与状态表示
2. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433) - 状态压缩DP
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443) - BFS与状态记录

---

### 调试心得摘录

"开始用字符串直接比较导致超时，后改用编号映射效率提升百倍" —— 来自题解作者调试记录  
"忘记处理字典序WA了三次，后来在输入时直接排序解决" —— 多位作者共同踩坑点  
"二进制枚举时把循环写成 1<<m 导致错误，调试两小时才发现" —— 位运算常见陷阱

---
处理用时：61.58秒