# 题目信息

# Arpa’s obvious problem and Mehrdad’s terrible solution

## 题目描述

There are some beautiful girls in Arpa’s land as mentioned before.

Once Arpa came up with an obvious problem:

Given an array and a number $ x $ , count the number of pairs of indices $ i,j $ ( $ 1<=i&lt;j<=n $ ) such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/80e8812f6abd24888e930488b3c56b15fb2a49a1.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/4298d47c0191af3c0a3103f431751061bc7e2362.png) is bitwise xor operation (see notes for explanation).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/7cd1b5aedffc45f296d333e099a050047eae38ee.png)Immediately, Mehrdad discovered a terrible solution that nobody trusted. Now Arpa needs your help to implement the solution to that problem.

## 说明/提示

In the first sample there is only one pair of $ i=1 $ and $ j=2 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/c63bc815847bae57aeba51b11f6ec2211cbd1efa.png) so the answer is $ 1 $ .

In the second sample the only two pairs are $ i=3 $ , $ j=4 $ (since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/360a9ab048a3005f1d532cfb7c78e96ffd10455b.png)) and $ i=1 $ , $ j=5 $ (since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/e00da54f194d914d5a9270c780a44af611f46740.png)).

A bitwise xor takes two bit integers of equal length and performs the logical xor operation on each pair of corresponding bits. The result in each position is $ 1 $ if only the first bit is $ 1 $ or only the second bit is $ 1 $ , but will be $ 0 $ if both are $ 0 $ or both are $ 1 $ . You can read more about bitwise xor operation here: [https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 样例 #1

### 输入

```
2 3
1 2
```

### 输出

```
1```

## 样例 #2

### 输入

```
6 1
5 1 2 3 4 1
```

### 输出

```
2```

# AI分析结果



# Arpa’s obvious problem and Mehrdad’s terrible solution

## 题目描述

给定一个数组和一个数字 $x$，统计有多少对下标 $i,j$（$1 \le i < j \le n$）满足 $a_i \oplus a_j = x$，其中 $\oplus$ 表示按位异或运算。

## 算法分类
位运算、哈希表

---

## 题解分析与结论

### 核心思路
利用异或的逆运算性质：若 $a \oplus b = x$，则 $b = a \oplus x$。维护一个计数数组/哈希表，遍历时统计当前元素之前出现过的互补值（$a_i \oplus x$）的次数，自然保证 $i<j$ 的顺序。

### 最优解法
使用数组桶计数，时间复杂度 $O(n)$，空间复杂度 $O(2^{17})$。关键点：遍历时先查询互补值出现次数，再更新当前值的计数。

---

## 精选题解

### 题解1：过往梦魇之殇（★★★★★）
**关键亮点**  
- 数组桶实现高效查询
- 代码简洁，处理顺序自然保证 $i<j$
- 数值范围处理合理

**核心代码**  
```cpp
int a[140000],n,x,t;
long long ans=0;
int main() {
    n=read();x=read();
    while(n--) {
        t=read();
        ans+=a[x^t];
        ++a[t];
    }
    printf("%lld\n",ans);
}
```

### 题解2：lizulong（★★★★☆）
**关键亮点**  
- 暴力与优化解法对比清晰
- 正确使用数组桶处理大范围数据
- 代码包含快读快写优化

**核心代码**  
```cpp
int a[200001],b[200001];
signed main(){
    n=read(),x=read();
    for(int i=1;i<=n;i++)
        a[i]=read(),sum+=b[a[i]^x],b[a[i]]++;
    cout<<sum;
}
```

### 题解3：Submerge_TA（★★★★☆）
**关键亮点**  
- 使用 `unordered_map` 处理通用情况
- 代码结构清晰，适合动态范围
- 注释明确，逻辑易读

**核心代码**  
```cpp
unordered_map<int, int> freq;
for (int num : nums) {
    int complement = num ^ x;
    count += freq[complement];
    freq[num]++;
}
```

---

## 相似题目推荐
1. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)  
2. [CF617E XOR and Favorite Number](https://codeforces.com/problemset/problem/617/E)  
3. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)  

---

## 扩展思路
- **桶数组大小**：根据 $a_i$ 和 $x$ 的最大值（约 $2^{17}$）确定数组大小
- **哈希表选择**：数值大时用 `unordered_map`，数值小时用数组更优
- **异或性质拓展**：类似问题可转化为互补值统计（如两数之和）

---
处理用时：140.57秒