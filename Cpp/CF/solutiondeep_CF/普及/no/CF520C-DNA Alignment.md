# 题目信息

# DNA Alignment

## 题目描述

Vasya became interested in bioinformatics. He's going to write an article about similar cyclic DNA sequences, so he invented a new method for determining the similarity of cyclic sequences.

Let's assume that strings $ s $ and $ t $ have the same length $ n $ , then the function $ h(s,t) $ is defined as the number of positions in which the respective symbols of $ s $ and $ t $ are the same. Function $ h(s,t) $ can be used to define the function of Vasya distance $ ρ(s,t) $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/0b4348c88074431fd692746719c4a6f852a88ac1.png) where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/e04d6b40ed912903e989b816c65cd323f288312f.png) is obtained from string $ s $ , by applying left circular shift $ i $ times. For example,  $ ρ(&quot;AGC&quot;,&quot;CGT&quot;)= $   $ h(&quot;AGC&quot;,&quot;CGT&quot;)+h(&quot;AGC&quot;,&quot;GTC&quot;)+h(&quot;AGC&quot;,&quot;TCG&quot;)+ $   $ h(&quot;GCA&quot;,&quot;CGT&quot;)+h(&quot;GCA&quot;,&quot;GTC&quot;)+h(&quot;GCA&quot;,&quot;TCG&quot;)+ $   $ h(&quot;CAG&quot;,&quot;CGT&quot;)+h(&quot;CAG&quot;,&quot;GTC&quot;)+h(&quot;CAG&quot;,&quot;TCG&quot;)= $   $ 1+1+0+0+1+1+1+0+1=6 $ Vasya found a string $ s $ of length $ n $ on the Internet. Now he wants to count how many strings $ t $ there are such that the Vasya distance from the string $ s $ attains maximum possible value. Formally speaking, $ t $ must satisfy the equation: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/106c86f5cd7beb20b5aaf5b6e98985a65f7d4450.png).

Vasya could not try all possible strings to find an answer, so he needs your help. As the answer may be very large, count the number of such strings modulo $ 10^{9}+7 $ .

## 说明/提示

Please note that if for two distinct strings $ t_{1} $ and $ t_{2} $ values $ ρ(s,t_{1}) $ и $ ρ(s,t_{2}) $ are maximum among all possible $ t $ , then both strings must be taken into account in the answer even if one of them can be obtained by a circular shift of another one.

In the first sample, there is $ ρ(&quot;C&quot;,&quot;C&quot;)=1 $ , for the remaining strings $ t $ of length 1 the value of $ ρ(s,t) $ is 0.

In the second sample, $ ρ(&quot;AG&quot;,&quot;AG&quot;)=ρ(&quot;AG&quot;,&quot;GA&quot;)=ρ(&quot;AG&quot;,&quot;AA&quot;)=ρ(&quot;AG&quot;,&quot;GG&quot;)=4 $ .

In the third sample, $ ρ(&quot;TTT&quot;,&quot;TTT&quot;)=27 $

## 样例 #1

### 输入

```
1
C
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
AG
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
TTT
```

### 输出

```
1
```

# AI分析结果



### 题目重写
# DNA 对齐

## 题目描述

给定两个长度均为 $n$ 的字符串 $s$ 和 $t$，定义 $h(s,t)$ 为两个字符串在相同位置上字符相同的次数。Vasya 距离 $\rho(s,t)$ 定义为所有 $s$ 的循环移位与 $t$ 的循环移位之间的 $h$ 值总和。

现给定长度为 $n$ 的字符串 $s$，求有多少个字符串 $t$ 使得 $\rho(s,t)$ 取得最大值。答案对 $10^9+7$ 取模。

## 样例解释

样例1中 $\rho("C","C")=1$，其他长度为1的字符串 $t$ 的 $\rho$ 值为0，输出1。  
样例2中四个字符串的 $\rho$ 值均为4，输出4。  
样例3中只有全"T"字符串能达到最大 $\rho$ 值27，输出1。

---

### 算法分类
数学

---

### 题解对比与结论

**关键思路**  
所有最优解 $t$ 的每个字符必须选自原字符串 $s$ 中出现次数最多的字符。设出现次数最多的字符有 $k$ 种，则答案为 $k^n \mod (10^9+7)$。

**正确性证明**  
每个字符选择出现频率最高的字符能最大化所有循环移位后的匹配次数总和。当多个字符出现次数同为最大值时，每个位置有 $k$ 种选择，总方案数为 $k^n$。

---

### 精选题解

#### 题解1（lightningZ，4星）
**亮点**  
- 通过构造表格验证规律  
- 代码简洁，直接统计四个核苷酸出现次数  
- 快速幂取模实现高效计算

**核心代码**  
```cpp
int zdx(int x) { // 快速幂
    int num=1;
    while(n--) num=num*x%mod;
    return num;
}
// 统计出现次数
if(a==m) ans++; // 统计最大出现次数的字符种类数
```

#### 题解3（_Passerby_，4星）
**亮点**  
- 使用快速幂函数提高可读性  
- 清晰的字符统计逻辑  
- 变量命名直观（mx为最大出现次数，bs为种类数）

**核心代码**  
```cpp
int qpow(int a, int b) { // 标准快速幂
    int ans=1;
    while(b) {
        if(b&1) ans=ans*a%P;
        a=a*a%P; b>>=1;
    }
    return ans;
}
// 统计各字符出现次数后
cout << qpow(bs, n); // 输出结果
```

#### 题解2（The_jester_from_Lst，4星）  
**亮点**  
- 使用排序简化最大值判断  
- 代码包含输入优化模板

**核心代码**  
```cpp
sort(sum+1, sum+1+4, cmp); // 排序后统计最大出现次数种类
for(int i=2;i<=4;++i) {
    if(sum[i]<sum[1])break;
    ++s; // s为最大出现次数的字符种类数
}
ans=(ans*s)%mod; // 累乘计算答案
```

---

### 关键代码实现
```cpp
// 统计出现次数并计算答案（示例代码）
int a=0, c=0, g=0, t=0;
for(char ch : s) { // 遍历字符串
    if(ch=='A') a++;
    else if(ch=='C') c++;
    else if(ch=='G') g++;
    else if(ch=='T') t++;
}
int m = max({a, c, g, t});
int k = (a==m) + (c==m) + (g==m) + (t==m); // 统计种类数
int ans = 1;
for(int i=0; i<n; ++i) // 计算k^n
    ans = 1LL * ans * k % 1000000007;
```

---

### 拓展与总结
**同类型题目**  
- [P3802 小魔女帕琪](https://www.luogu.com.cn/problem/P3802)（概率与期望）  
- [P1404 平均数](https://www.luogu.com.cn/problem/P1404)（数学推导）  
- [P1866 路径计数](https://www.luogu.com.cn/problem/P1866)（组合数学）

**心得总结**  
- 构造极端样例（如全相同字符）可快速验证思路  
- 快速幂是处理大指数取模问题的标准工具  
- 注意字符统计时区分大小写等边界条件

---
处理用时：98.96秒