# 题目信息

# Ira and Flamenco

## 题目描述

Ira loves Spanish flamenco dance very much. She decided to start her own dance studio and found $ n $ students, $ i $ th of whom has level $ a_i $ .

Ira can choose several of her students and set a dance with them. So she can set a huge number of dances, but she is only interested in magnificent dances. The dance is called magnificent if the following is true:

- exactly $ m $ students participate in the dance;
- levels of all dancers are pairwise distinct;
- levels of every two dancers have an absolute difference strictly less than $ m $ .

For example, if $ m = 3 $ and $ a = [4, 2, 2, 3, 6] $ , the following dances are magnificent (students participating in the dance are highlighted in red): $ [\color{red}{4}\color{black}, 2,\color{red}{2}\color{black},\color{red}{3}\color{black}, 6] $ , $ [\color{red}{4}\color{black}, \color{red}{2}\color{black}, 2, \color{red}{3}\color{black}, 6] $ . At the same time dances $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, 6] $ , $ [4, \color{red}{2}\color{black}, \color{red}{2}\color{black}, \color{red}{3}\color{black}, 6] $ , $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, \color{red}{6}\color{black}] $ are not magnificent.

In the dance $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, 6] $ only $ 2 $ students participate, although $ m = 3 $ .

The dance $ [4, \color{red}{2}\color{black}, \color{red}{2}\color{black}, \color{red}{3}\color{black}, 6] $ involves students with levels $ 2 $ and $ 2 $ , although levels of all dancers must be pairwise distinct.

In the dance $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, \color{red}{6}\color{black}] $ students with levels $ 3 $ and $ 6 $ participate, but $ |3 - 6| = 3 $ , although $ m = 3 $ .

Help Ira count the number of magnificent dances that she can set. Since this number can be very large, count it modulo $ 10^9 + 7 $ . Two dances are considered different if the sets of students participating in them are different.


## 说明/提示

In the first testcase, Ira can set such magnificent dances: $ [\color{red}{8}\color{black}, 10, 10, \color{red}{9}\color{black}, \color{red}{6}\color{black}, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, \color{red}{10}\color{black}, 10, \color{red}{9}\color{black}, 6, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, 10, \color{red}{10}\color{black}, \color{red}{9}\color{black}, 6, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, 10, \color{red}{10}\color{black}, \color{red}{9}\color{black}, 6, \color{red}{11}\color{black}, 7] $ , $ [\color{red}{8}\color{black}, \color{red}{10}\color{black}, 10, \color{red}{9}\color{black}, 6, \color{red}{11}\color{black}, 7] $ .

The second testcase is explained in the statements.

## 样例 #1

### 输入

```
9
7 4
8 10 10 9 6 11 7
5 3
4 2 2 3 6
8 2
1 5 2 2 3 1 3 3
3 3
3 3 3
5 1
3 4 3 10 7
12 3
5 2 1 1 4 3 5 5 5 2 7 5
1 1
1
3 2
1 2 3
2 2
1 2```

### 输出

```
5
2
10
0
5
11
1
2
1```

# AI分析结果

### 题目内容重写（中文）

Ira非常喜欢西班牙弗拉门戈舞。她决定开设自己的舞蹈工作室，并找到了$n$个学生，第$i$个学生的水平为$a_i$。

Ira可以选择她的几个学生来编排舞蹈。因此，她可以编排大量的舞蹈，但她只对“壮丽”的舞蹈感兴趣。一个舞蹈被称为“壮丽”的，当且仅当满足以下条件：

- 恰好有$m$个学生参与舞蹈；
- 所有舞者的水平互不相同；
- 任意两个舞者的水平之差的绝对值严格小于$m$。

例如，若$m = 3$且$a = [4, 2, 2, 3, 6]$，则以下舞蹈是壮丽的（参与舞蹈的学生用红色标出）：$[\color{red}{4}\color{black}, 2,\color{red}{2}\color{black},\color{red}{3}\color{black}, 6]$，$[\color{red}{4}\color{black}, \color{red}{2}\color{black}, 2, \color{red}{3}\color{black}, 6]$。而舞蹈$[\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, 6]$，$[4, \color{red}{2}\color{black}, \color{red}{2}\color{black}, \color{red}{3}\color{black}, 6]$，$[\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, \color{red}{6}\color{black}]$则不是壮丽的。

在舞蹈$[\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, 6]$中，只有$2$个学生参与，尽管$m = 3$。

在舞蹈$[4, \color{red}{2}\color{black}, \color{red}{2}\color{black}, \color{red}{3}\color{black}, 6]$中，参与的学生水平为$2$和$2$，尽管所有舞者的水平必须互不相同。

在舞蹈$[\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, \color{red}{6}\color{black}]$中，参与的学生水平为$3$和$6$，但$|3 - 6| = 3$，尽管$m = 3$。

帮助Ira计算她可以编排的壮丽舞蹈的数量。由于这个数字可能非常大，请对$10^9 + 7$取模。如果两个舞蹈的参与学生集合不同，则认为它们是不同的。

### 算法分类
组合数学

### 题解分析与结论
本题的核心在于找到满足条件的$m$个学生，且他们的水平互不相同且极差小于$m$。通过分析可以发现，这$m$个学生的水平必须形成一个公差为1的等差数列。因此，题解大多采用了排序、去重、统计每个数的出现次数，并通过乘法原理计算符合条件的方案数。

### 高星题解推荐

#### 题解1：Coffee_zzz（5星）
**关键亮点**：
- 通过排序和去重，找到可以形成等差数列的区间。
- 使用前缀积和逆元优化计算，避免了重复计算。
- 代码清晰，逻辑严谨，时间复杂度较低。

**核心代码**：
```cpp
sort(a+1,a+1+n);
for(int i=1;i<=n;i++){
    if(a[i+1]-a[i]>1||i==n){
        if(a[i]-a[p]>=m-1){
            cnt=0;
            for(int j=p;j<=i;j++) ma[a[j]]++;
            tim[a[p]-1]=1;
            for(int j=a[p];j<=a[i];j++) tim[j]=ma[j]*tim[j-1]%mod;
            for(int j=a[p],k=a[p]+m-1;k<=a[i];j++,k++){
                ans=ans+(tim[k]*ksm(tim[j-1],mod-2)%mod);
                ans=ans%mod;
            }
        }
        p=i+1;
    }
}
```

#### 题解2：Little_x_starTYJ（4星）
**关键亮点**：
- 使用线段树维护区间乘积，避免了重复计算。
- 通过离散化处理，减少了空间复杂度。
- 代码实现较为复杂，但思路清晰。

**核心代码**：
```cpp
buildTree(1, 1, k);
id = 1;
for (int i = 2; i <= k; i++) {
    if (a[i] - a[i - 1] == 1) id++;
    else id = 1;
    if (id == m) {
        int temp = query(1, 1, k, i - m + 1, i);
        ans = (ans + temp) % mod;
        id--;
    }
}
```

#### 题解3：hjqhs（4星）
**关键亮点**：
- 通过滑动窗口和逆元优化计算，减少了时间复杂度。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码**：
```cpp
for(int i=1,j=1;i<=n;++i){
    while(j<=n&&a[j]<a[i]+m)c=c*(cnt[a[j]])%MOD,++j;
    if(j-i==m)ans+=c,ans%=MOD;
    c=c*qpow(cnt[a[i]],MOD-2)%MOD;
}
```

### 最优关键思路与技巧
1. **排序与去重**：通过排序和去重，可以快速找到符合条件的等差数列区间。
2. **前缀积与逆元**：使用前缀积和逆元优化计算，避免了重复计算，提高了效率。
3. **滑动窗口**：通过滑动窗口的方式，减少了时间复杂度，适合处理大规模数据。

### 可拓展之处
本题的核心思想可以应用于其他需要处理连续区间的问题，如寻找最长连续子序列、统计满足特定条件的区间等。类似的问题可以通过排序、去重、滑动窗口等技巧来解决。

### 推荐题目
1. [P1494 [国家集训队]小Z的袜子](https://www.luogu.com.cn/problem/P1494)
2. [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)
3. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)

---
处理用时：51.13秒