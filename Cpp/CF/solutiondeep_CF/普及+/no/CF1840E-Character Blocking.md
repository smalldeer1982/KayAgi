# 题目信息

# Character Blocking

## 题目描述

You are given two strings of equal length $ s_1 $ and $ s_2 $ , consisting of lowercase Latin letters, and an integer $ t $ .

You need to answer $ q $ queries, numbered from $ 1 $ to $ q $ . The $ i $ -th query comes in the $ i $ -th second of time. Each query is one of three types:

- block the characters at position $ pos $ (indexed from $ 1 $ ) in both strings for $ t $ seconds;
- swap two unblocked characters;
- determine if the two strings are equal at the time of the query, ignoring blocked characters.

Note that in queries of the second type, the characters being swapped can be from the same string or from $ s_1 $ and $ s_2 $ .

## 说明/提示

Let's look at the strings $ s_1 $ and $ s_2 $ after each of the $ q $ queries. Blocked characters will be denoted in red.

First example input:

( $ codeforces $ , $ codeblocks $ ) $ \rightarrow $ ( $ codeforces $ , $ codeblocks $ ) $ \rightarrow $ ( $ code\color{red}{f}orces $ , $ code\color{red}{b}locks $ ) $ \rightarrow $ ( $ code\color{red}{fo}rces $ , $ code\color{red}{bl}ocks $ ) $ \rightarrow $ ( $ code\color{red}{for}ces $ , $ code\color{red}{blo}cks $ ) $ \rightarrow $ ( $ code\color{red}{for}c\color{red}{e}s $ , $ code\color{red}{blo}c\color{red}{k}s $ ) $ \rightarrow $ ( $ code\color{red}{for}c\color{red}{e}s $ , $ code\color{red}{blo}c\color{red}{k}s $ ) $ \rightarrow $ ( $ codef\color{red}{or}c\color{red}{e}s $ , $ codeb\color{red}{lo}c\color{red}{k}s $ )

Second example input:

( $ cool $ , $ club $ ) $ \rightarrow $ ( $ cuol $ , $ clob $ ) $ \rightarrow $ ( $ cuol $ , $ cbol $ ) $ \rightarrow $ ( $ c\color{red}{u}ol $ , $ c\color{red}{b}ol $ ) $ \rightarrow $ ( $ c\color{red}{u}ol $ , $ c\color{red}{b}ol $ ) $ \rightarrow $ ( $ cuol $ , $ cbol $ )

## 样例 #1

### 输入

```
2
codeforces
codeblocks
5 7
3
1 5
1 6
1 7
1 9
3
3
cool
club
2 5
2 1 2 2 3
2 2 2 2 4
1 2
3
3```

### 输出

```
NO
YES
NO
YES
NO```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

给定两个长度相等的字符串 $s_1$ 和 $s_2$，由小写拉丁字母组成，以及一个整数 $t$。

你需要回答 $q$ 个查询，编号从 $1$ 到 $q$。第 $i$ 个查询在第 $i$ 秒时到来。每个查询是以下三种类型之一：

1. 封锁两个字符串中位置为 $pos$（从 $1$ 开始索引）的字符，持续 $t$ 秒；
2. 交换两个未被封锁的字符（可以来自同一个字符串或不同的字符串）；
3. 在查询时判断两个字符串是否相等，忽略被封锁的字符。

#### 说明/提示

让我们看看在每个查询后字符串 $s_1$ 和 $s_2$ 的状态。被封锁的字符将用红色表示。

第一个示例输入：

( $codeforces$ , $codeblocks$ ) $ \rightarrow $ ( $codeforces$ , $codeblocks$ ) $ \rightarrow $ ( $code\color{red}{f}orces $ , $ code\color{red}{b}locks $ ) $ \rightarrow $ ( $ code\color{red}{fo}rces $ , $ code\color{red}{bl}ocks $ ) $ \rightarrow $ ( $ code\color{red}{for}ces $ , $ code\color{red}{blo}cks $ ) $ \rightarrow $ ( $ code\color{red}{for}c\color{red}{e}s $ , $ code\color{red}{blo}c\color{red}{k}s $ ) $ \rightarrow $ ( $ code\color{red}{for}c\color{red}{e}s $ , $ code\color{red}{blo}c\color{red}{k}s $ ) $ \rightarrow $ ( $ codef\color{red}{or}c\color{red}{e}s $ , $ codeb\color{red}{lo}c\color{red}{k}s $ )

第二个示例输入：

( $cool$ , $club$ ) $ \rightarrow $ ( $cuol$ , $clob$ ) $ \rightarrow $ ( $cuol$ , $cbol$ ) $ \rightarrow $ ( $c\color{red}{u}ol$ , $c\color{red}{b}ol$ ) $ \rightarrow $ ( $c\color{red}{u}ol$ , $c\color{red}{b}ol$ ) $ \rightarrow $ ( $cuol$ , $cbol$ )

### 算法分类
模拟

### 题解分析与结论

题目要求处理三种操作：封锁字符、交换字符、查询字符串是否相等。核心难点在于如何高效地维护字符的封锁状态以及如何快速判断字符串是否相等。

### 所选题解

#### 题解1：AlicX (赞：11)
- **星级**：★★★★★
- **关键亮点**：使用 `cnt` 变量维护两个字符串中不同字符的数量，通过判断 `cnt` 是否为0来快速判断字符串是否相等。封锁操作通过记录时间并在后续查询中恢复封锁状态。
- **个人心得**：作者提到在考场中曾混淆等于和不等于的情况，提醒读者在处理逻辑时要特别注意细节。

```cpp
int cnt = 0;
for(int i=0;i<s1.size();i++) if(s1[i]!=s2[i]) cnt++;
for(int i=1;i<=n;i++){
    if(i>t&&st[i-t]){
        if(s1[p[i-t]-1]!=s2[p[i-t]-1]) cnt++;  
    }
    if(opt==1){ 
        cin>>a; st[i]=true; p[i]=a; 
        if(s1[a-1]!=s2[a-1]) cnt--;  		 
    } else if(opt==2){
        // 交换操作，更新 cnt
    }
    else{
        if(!cnt) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
```

#### 题解2：luqyou (赞：4)
- **星级**：★★★★
- **关键亮点**：使用 `set` 维护两个字符串中不同字符的位置，通过判断 `set` 是否为空来快速判断字符串是否相等。封锁操作通过队列记录并在后续查询中恢复封锁状态。
- **个人心得**：作者通过 `set` 和 `queue` 的结合，简化了封锁操作的恢复逻辑。

```cpp
set<int> s;
queue<bl> blocks;
for(int i=1;i<=n;i++){
    if(s1[i]!=s2[i]) s.insert(i);
}
for(int i=1;i<=q;i++){
    if(blocks.size()){
        int t1=blocks.front().tm,t2=blocks.front().pos;
        if(i-t1>=t){
            if(s1[t2]!=s2[t2]) s.insert(t2);
            blocks.pop();
        }
    }
    // 处理操作
}
```

#### 题解3：Imken (赞：0)
- **星级**：★★★★
- **关键亮点**：使用字符串哈希来快速判断字符串是否相等。封锁操作通过记录时间并在后续查询中恢复封锁状态。
- **个人心得**：作者通过字符串哈希优化了字符串比较的效率，适合处理大规模数据。

```cpp
u128 hsh[2] = { 0, 0 };
for (int j = 0; j < 2; j++)
    for (int i = 0; i < len; i++)
        hsh[j] = hsh[j] + s[j][i] * w[i];
for (int tt = 1; tt <= q; tt++) {
    for (int i = 0; i <= 1; i++)
        hsh[i] = hsh[i] + add[i][tt];
    // 处理操作
}
```

### 最优关键思路或技巧
1. **维护不同字符数量**：通过 `cnt` 变量或 `set` 来维护两个字符串中不同字符的数量，可以快速判断字符串是否相等。
2. **时间队列**：使用队列记录封锁操作的时间，并在后续查询中恢复封锁状态，简化了封锁操作的恢复逻辑。
3. **字符串哈希**：通过字符串哈希优化字符串比较的效率，适合处理大规模数据。

### 可拓展之处
1. **多字符串处理**：可以扩展到处理多个字符串的封锁和比较操作。
2. **动态封锁时间**：封锁时间可以动态变化，进一步增加题目的复杂性。

### 推荐题目
1. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
2. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
3. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)

### 个人心得总结
在处理字符串操作时，细节非常重要，特别是在处理等于和不等于的逻辑时。通过使用 `cnt` 变量或 `set` 来维护不同字符的数量，可以大大简化判断逻辑。同时，使用队列记录封锁操作的时间，可以有效管理封锁状态的恢复。

---
处理用时：55.51秒