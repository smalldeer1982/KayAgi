# 题目信息

# Hamming Distance Sum

## 题目描述

吉诺斯需要你的帮助。他被要求完成塞塔玛出的如下编程问题：  
  
  字符串 s 的长度被表示为 $\left|s\right|$。两个等长字符串 s 和 t 之间的“Hamming”距离被定义为 $\sum\limits_{i=1}^{\left|s\right|}\left|s_i-t_i\right|$，其中，$s_i$ 是字符串 s 的第 i 个字符，$t_i$ 是字符串 t 的第 i 个字符。  
  
  比如说，字符串“0011”和字符串“0110”之间的“Hamming”距离为 $\left|0-0\right|+\left|0-1\right|+\left|1-1\right|+\left|1-0\right|=0+1+0+1=2$。
  
  给定两个字符串 a 和 b，找到字符串 a 和所有字符串 b 的长度为 $\left|a\right|$ 的子串之间的“Hamming”距离总和。

## 样例 #1

### 输入

```
01
00111
```

### 输出

```
3
```

## 样例 #2

### 输入

```
0011
0110
```

### 输出

```
2
```

# AI分析结果



# 汉明距离总和

## 题目描述

吉诺斯需要你的帮助。他被要求完成塞塔玛出的如下编程问题：  

字符串 s 的长度被表示为 $\left|s\right|$。两个等长字符串 s 和 t 之间的“Hamming”距离被定义为 $\sum\limits_{i=1}^{\left|s\right|}\left|s_i-t_i\right|$，其中，$s_i$ 是字符串 s 的第 i 个字符，$t_i$ 是字符串 t 的第 i 个字符。  

例如，字符串“0011”和“0110”的 Hamming 距离为 $0+1+0+1=2$。  

给定两个字符串 a 和 b，计算 a 与 b 中所有长度为 $|a|$ 的子串之间的 Hamming 距离总和。

## 样例 #1

### 输入

```
01
00111
```

### 输出

```
3
```

## 样例 #2

### 输入

```
0011
0110
```

### 输出

```
2
```

---

**算法分类**：前缀和

---

## 题解分析与结论

### 核心思路
1. **前缀和预处理**：统计字符串 b 的每个位置前包含的 '1' 的个数，通过前缀和数组快速查询区间和。
2. **独立贡献计算**：将每个 a 的字符独立分析，确定其在 b 中对应的移动区间，利用前缀和计算该区间内不同字符的数量。
3. **区间范围推导**：a 的第 i 个字符在 b 中的比较范围为 $[i, |b| - |a| + i]$，总共有 $|b| - |a| + 1$ 次比较，通过前缀和差快速求和。

### 最优题解推荐

#### 题解作者：DiDi123  
**评分**：★★★★☆  
**关键亮点**：  
- 使用单一前缀和数组，代码简洁高效。
- 利用区间长度直接计算 0 的个数（总长度减 1 的个数），避免维护多个数组。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200001
string a,b;
long long ans,sum[MAXN];
long long get_sum(int l,int r) {
    return sum[r]-sum[l-1];
}
int main() {
    cin>>a>>b;
    for(int i=0;i<b.length();i++)
        sum[i+1]=sum[i]+b[i]-'0';
    for(int i=0;i<a.length();i++) {
        int l = i + 1;
        int r = b.length() - a.length() + i + 1;
        if(a[i]=='0') ans += get_sum(l, r);
        else ans += (r - l + 1) - get_sum(l, r);
    }
    cout<<ans;
}
```

---

### 关键技巧总结
1. **前缀和的灵活应用**：将二维区间比较问题降为一维前缀差计算。
2. **字符独立分析**：拆分每个字符的贡献，避免整体比较的重复计算。
3. **下标转换技巧**：注意字符串的 0-based 索引与前缀和数组 1-based 索引的对应关系。

### 同类题目推荐
1. [CF466C Number of Ways](https://www.luogu.com.cn/problem/CF466C)（前缀和分割统计）
2. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)（差分与前缀和结合）
3. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（前缀和变形应用）

---
处理用时：250.39秒