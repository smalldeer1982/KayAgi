# 题目信息

# Nephren gives a riddle

## 题目描述

奈芙莲有一个字符串数组 $f_{0\dots\infty}$。

$f_0$ 为 `What are you doing at the end of the world? Are you busy? Will you save us?`。

她想让更多人了解这个数组，所以她定义：

$$
\forall i\ge 1,f_i=\texttt{What are you doing while sending "}+f_{i-1}\\
+\texttt{"? Are you busy? Will you send "}+f_{i-1}+\texttt{"?}
$$

**注意其中的引号。**

奈芙莲会询问 $q$ 次，第 $i$ 次给定 $n,k$，你需要求出 $f_{n,k}$ 的值。**注意字符串从 $1$ 开始。**

## 说明/提示

对于所有数据，$1\le q\le 10,1\le n\le 10^5,1\le k\le 10^{18}$。

## 样例 #1

### 输入

```
3
1 1
1 2
1 111111111111
```

### 输出

```
Wh.```

## 样例 #2

### 输入

```
5
0 69
1 194
1 139
0 47
1 66
```

### 输出

```
abdef```

## 样例 #3

### 输入

```
10
4 1825
3 75
3 530
4 1829
4 1651
3 187
4 584
4 255
4 774
2 474
```

### 输出

```
Areyoubusy```

# AI分析结果

### 题目翻译
# 奈芙莲出了一个谜题

## 题目描述
奈芙莲有一个字符串数组 $f_{0\dots\infty}$。

$f_0$ 为 `What are you doing at the end of the world? Are you busy? Will you save us?`。

为了让更多人了解这个数组，她定义：

$$
\forall i\ge 1,f_i=\texttt{What are you doing while sending "}+f_{i-1}\\
+\texttt{"? Are you busy? Will you send "}+f_{i-1}+\texttt{"?}
$$

**注意其中的引号。**

奈芙莲会进行 $q$ 次询问，第 $i$ 次给定 $n,k$，你需要求出 $f_{n,k}$ 的值。**注意字符串从 $1$ 开始。**

## 说明/提示
对于所有数据，$1\le q\le 10,1\le n\le 10^5,1\le k\le 10^{18}$。

## 样例 #1
### 输入
```
3
1 1
1 2
1 111111111111
```
### 输出
```
Wh.
```

## 样例 #2
### 输入
```
5
0 69
1 194
1 139
0 47
1 66
```
### 输出
```
abdef
```

## 样例 #3
### 输入
```
10
4 1825
3 75
3 530
4 1829
4 1651
3 187
4 584
4 255
4 774
2 474
```
### 输出
```
Areyoubusy
```

### 综合分析与结论
这些题解的核心思路都是通过递归和分类讨论来解决问题。由于字符串长度增长极快，直接模拟存储所有字符串不可行，所以大家都采用将 $f_n$ 拆分为固定部分和 $f_{n - 1}$ 的方式，根据 $k$ 的位置判断字符所在部分，若在固定部分则直接输出，若在 $f_{n - 1}$ 部分则递归求解。

### 关键思路或技巧
- **长度预处理**：先计算出每个字符串 $f_i$ 的长度，由于长度增长快，对于超过 $10^{18}$ 的长度进行特殊处理（如赋值为最大值或 -1），避免溢出问题。
- **递归求解**：将 $f_n$ 拆分为多个部分，根据 $k$ 的位置判断字符所在部分，若在固定部分则直接输出，若在 $f_{n - 1}$ 部分则递归求解。

### 可拓展之处
同类型题目可能会有不同的字符串构造规则，但解题思路类似，都是通过递归和分类讨论，根据位置判断字符所在部分。类似算法套路可用于处理具有递归结构的序列或字符串问题，如分形结构、递归生成的图形等。

### 推荐题目
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)
- [P1928 外星密码](https://www.luogu.com.cn/problem/P1928)

### 个人心得摘录
- Fuko_Ibuki：比赛时花了两个小时才推出标算，然后用 6 分钟打完。说明本题有一定难度，需要时间推导思路。

### 重点代码
以下是 Fuko_Ibuki 的核心代码，展示了递归求解的过程：
```cpp
char work(int n,ll k)
{
    if (k>changdu[n]) return '.';
    if (n==0) return f0[k];//n=0,直接输出
    if (k<r1) return a1[k];//增加的字符串的第一段
    k-=r1;
    if (k<changdu[n-1]) return work(n-1,k);//说明在f[i-1]中
    k-=changdu[n-1];
    if (k<r2) return a2[k];//第二段
    k-=r2;
    if (k<changdu[n-1]) return work(n-1,k);//也说明在f[i-1]中
    k-=changdu[n-1];
    if (k<r3) return a3[k];//第三段
    return '.';
}
```
核心实现思想：根据 $k$ 的位置判断字符所在部分，若在固定部分（如 $a1$、$a2$、$a3$）则直接输出对应字符，若在 $f_{n - 1}$ 部分则递归调用 `work` 函数求解。

---
处理用时：29.99秒