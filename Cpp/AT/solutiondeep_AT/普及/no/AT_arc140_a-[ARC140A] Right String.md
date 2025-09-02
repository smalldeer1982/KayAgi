# 题目信息

# [ARC140A] Right String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc140/tasks/arc140_a

英小文字からなる文字列 $ T $ に対して次の問題を考え、その答えを $ f(T) $ とします。

> $ T $ の先頭の文字を削除し末尾に追加する操作を任意の回数行うことによって作ることのできる文字列の種類数を求めてください。

英小文字からなる長さ $ N $ の文字列 $ S $ が与えられます。あなたは以下の操作を $ K $ 回以下行うことが出来ます。($ 1 $ 回も行わなくてもよいです。)

- $ S $ の文字を $ 1 $ 個選び、任意の英小文字に変更する。

操作終了後の $ f(S) $ の値としてあり得る最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2000 $
- $ 0\ \le\ K\ \le\ N $
- $ S $ は英小文字からなる長さ $ N $ の文字列である。
- $ N,K $ は整数である。

### Sample Explanation 1

$ 1 $ 回目の操作で $ 4 $ 文字目を `c` から `b` に変更すると $ S= $ `abab` となり、$ f(S)=2 $ となります。 $ f(S) $ を $ 1 $ 回以下の操作で $ 1 $ 以下にすることはできないため、答えは $ 2 $ です。

## 样例 #1

### 输入

```
4 1

abac```

### 输出

```
2```

## 样例 #2

### 输入

```
10 0

aaaaaaaaaa```

### 输出

```
1```

## 样例 #3

### 输入

```
6 1

abcaba```

### 输出

```
3```

# AI分析结果



# [ARC140A] Right String

## 题目描述

对于由小写字母组成的字符串 $ T $，定义 $ f(T) $ 为：通过任意次将 $ T $ 的第一个字符删除并追加到末尾的操作，能得到的不同的字符串种类数。

给定长度为 $ N $ 的字符串 $ S $，允许进行最多 $ K $ 次修改操作（每次可将任意字符改为其他小写字母）。求操作后 $ f(S) $ 的最小可能值。

## 输入格式

输入包括：
- 第一行两个整数 $ N $ 和 $ K $
- 第二行字符串 $ S $

## 输出格式

输出最小的 $ f(S) $ 值

## 说明/提示

### 数据范围
- $ 1 \leq N \leq 2000 $
- $ 0 \leq K \leq N $

### 样例解释
样例1：修改第4个字符为'b'得到"abab"，其循环节长度为2，$ f(S)=2 $

---

**算法标签：字符串、枚举、数学因数**

---

## 题解分析与结论

### 核心思路
$ f(S) $ 的实质是字符串的最小循环节长度。要最小化该值，需枚举所有可能的循环节长度 $ len $（必须是 $ N $ 的因数），计算将字符串修改为 $ len $ 长度的循环节所需的最小修改次数，选择满足 $ \text{修改次数} \leq K $ 的最小 $ len $。

### 关键步骤
1. **枚举因数**：循环节长度必须是 $ N $ 的因数
2. **统计修改次数**：对于每个候选长度 $ len $，统计每个循环节位置的最优修改次数（使用出现频率最高的字符）
3. **判断可行性**：总修改次数 ≤ K 时更新答案

### 解决难点
- 快速枚举因数并验证可行性
- 利用字符频率统计实现高效计算
- 时间复杂度优化到 $ O(N^2) $，适用于题设数据范围

---

## 精选题解

### 1. 作者：chinazhanghaoxun（5星）
**亮点**：代码简洁高效，变量命名清晰，因数处理直接  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k,ans=1e6;
    string s;
    cin>>n>>k>>s;
    for(int len=1;len<=n;len++){ 
        if(n%len!=0) continue;
        int change=0; 
        for(int i=0;i<len;i++){ 
            int have[27]={0}, max_cnt=0;
            for(int j=i;j<n;j+=len) 
                max_cnt = max(max_cnt, ++have[s[j]-'a']);
            change += n/len - max_cnt;
        }
        if(change<=k) ans=min(ans,len);
    }
    cout<<ans;
}
```
**核心实现**：嵌套循环结构清晰，使用数组统计字符频率，计算修改次数高效。

---

### 2. 作者：HNOIRPplusplus（4星）
**亮点**：详细解释循环节性质，代码逻辑与数学分析结合紧密  
```cpp
#include <iostream>
using namespace std;
int main() {
    int n, k; string s;
    cin >> n >> k >> s;
    int ans = n;
    for(int l=1; l<=n; l++) {
        if(n%l !=0) continue;
        int now=0;
        for(int i=0;i<l;i++) {
            int cnt[26]={}, mx=0;
            for(int j=i;j<n;j+=l)
                mx = max(mx, ++cnt[s[j]-'a']);
            now += n/l - mx;
        }
        if(now <=k) ans=min(ans, l);
    }
    cout << ans;
}
```
**核心优化**：直接使用原生数组统计，避免STL开销，代码可读性优秀。

---

### 3. 作者：liuhongyang123（4星）
**亮点**：代码精简，包含显式变量初始化，适合快速理解  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,vis[30];
string s;
int main(){
    cin>>n>>k>>s;
    int ans=n;
    for(int len=1;len<=n;len++){
        if(n%len!=0) continue;
        int tmp=0;
        for(int i=0;i<len;i++){
            memset(vis,0,sizeof vis);
            int mx=0;
            for(int j=i;j<n;j+=len)
                mx=max(mx,++vis[s[j]-'a']);
            tmp+=n/len -mx;
        }
        if(tmp<=k) ans=min(ans,len);
    }
    cout<<ans;
}
```
**特色**：显式重置统计数组，适合理解循环节处理的细节。

---

## 关键技巧总结
1. **因数枚举**：仅需检查 $ N $ 的因数，时间复杂度从 $ O(N^2) $ 优化到 $ O(N\sqrt{N}) $
2. **频率统计优化**：对每个循环节位置独立统计，使用数组而非哈希表提升效率
3. **贪心策略**：每个字符位置选择出现次数最多的字符，最小化修改次数

---

## 同类题目推荐
1. [P10810](https://www.luogu.com.cn/problem/P10810) - 双倍经验题
2. [P1368 最小表示法](https://www.luogu.com.cn/problem/P1368) - 循环移位相关
3. [P4391 [BOI2009] Radio Transmission](https://www.luogu.com.cn/problem/P4391) - 循环节应用

---
处理用时：68.52秒