# 题目信息

# [BalticOI 2005] Ancient Manuscript

## 题目描述

给定 Baltic 字符串的定义为：

- 全部为小写字母
- 最多只能有 $V_C$ 个连续的元音
- 最多只能有 $C_C$ 个连续的辅音
- 最多只能有 $V_E$ 个连续的元音相等
- 最多只能有 $C_E$ 个连续的辅音相等

`aeiou` 为元音，除了这五个字母之外的 21 个字母为辅音。

现在给定一个字符串，一些字符为小写字母一些字符为 `*`，您可以把 `*` 替换成任意一个小写字母。

求通过替换能使得这个字符串得到的不同的 Baltic 字符串的种类数。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le V_E \le V_C \le 4$，$1 \le C_E \le C_C \le 4$，$1 \le\ $字符串的长度$\ \le 15$。

#### 说明

翻译自 [BalticOI 2005 Day2 A Ancient Manuscript](https://boi.cses.fi/files/boi2005_day2.pdf)。

## 样例 #1

### 输入

```
1 1 1 1
a** ```

### 输出

```
105```

## 样例 #2

### 输入

```
1 1 1 1
b*i ```

### 输出

```
0```

## 样例 #3

### 输入

```
1 2 1 2
ancient ```

### 输出

```
1```

## 样例 #4

### 输入

```
4 4 4 4
man****ipt ```

### 输出

```
261870```

## 样例 #5

### 输入

```
2 2 2 2
*boi* ```

### 输出

```
546```

# AI分析结果

### 综合分析与结论
这两道题解均采用动态规划（DP）来解决问题。思路上，都定义了四维状态 $dp_{i,j,k,l}$ 表示前 $i$ 位，连续相同字母 $j$ 个，连续相同种类字母 $k$ 个，当前字母为 $l$ 的方案数。算法要点在于根据当前字符和前一字符的关系（相同、同种类、不同种类）进行状态转移。解决难点主要是状态转移方程的推导和实现。

### 所选的题解
- **作者：Echoternity**：4星。关键亮点在于思路清晰，详细阐述了状态定义、转移过程和答案统计方法，代码结构完整。个人心得：作者提到还有20天中考，希望题解一遍过，打算暂时AFO，七月再战OI。
- **作者：Aurora_Borealis_**：3星。关键亮点是明确指出爆搜复杂度不可取，引出DP解法，但思路阐述相对简略。

### 重点代码及核心实现思想
#### Echoternity的核心代码
```cpp
for(int i=2;i<=len;++i)
    for(int s_now=0;s_now<=25;++s_now)
        if(val[i]==26||val[i]==s_now)
            for(int k=0;k<=25;++k)
                if(val[i-1]==26||val[i-1]==k)
                {
                    bool flag_s=expr(s_now),flag_k=expr(k);
                    if(flag_s==flag_k)
                        if(s_now==k)
                            for(int l=2;l<=C[flag_s];++l)
                                for(int I=2;I<=E[flag_s];++I)
                                    dp[i][l][I][s_now]+=dp[i-1][l-1][I-1][k];
                        else
                            for(int l=2;l<=C[flag_s];++l)
                                for(int I=1;I<=E[flag_s];++I)
                                    dp[i][l][1][s_now]+=dp[i-1][l-1][I][k];
                    else
                        for(int l=1;l<=C[flag_k];++l)
                            for(int I=1;I<=E[flag_k];++I)
                                dp[i][1][1][s_now]+=dp[i-1][l][I][k];
                }
```
核心实现思想：根据当前字符和前一字符是否相同、是否同种类，分三种情况进行状态转移，更新 $dp$ 数组。

#### Aurora_Borealis_的核心代码
```cpp
for(int i=2;i<=n;i++){
    for(int j=0;j<26;j++){
        if(a[i]==26||a[i]==j){
            for(int k=0;k<26;k++){
                if(a[i-1]==26||a[i-1]==k){
                    int p=flag[j],q=flag[k];
                    if(p==q){
                        if(j==k){
                            for(int l=2;l<=c[p];l++){
                                for(int iee=2;iee<=e[p];iee++){
                                    dp[i][l][iee][j]+=dp[i-1][l-1][iee-1][k];
                                }
                            }
                        }else{
                            for(int l=2;l<=c[p];l++){
                                for(int iee=1;iee<=e[p];iee++){
                                    dp[i][l][1][j]+=dp[i-1][l-1][iee][k];
                                }
                            }
                        } 
                    }else{
                        for(int l=1;l<=c[q];l++){
                            for(int iee=1;iee<=e[q];iee++){
                                dp[i][1][1][j]+=dp[i-1][l][iee][k];
                            }
                        }
                    }
                }
            }
        }
    }
}
```
核心实现思想：同样根据当前字符和前一字符的关系进行状态转移，更新 $dp$ 数组。

### 最优关键思路或技巧
- **状态压缩**：通过合理定义状态，将题目中的四个限制压缩到三维，减少空间复杂度。
- **动态规划**：利用 $dp$ 数组记录中间状态，避免重复计算，提高效率。

### 可拓展之处
同类型题或类似算法套路：其他字符串计数问题，如带有特定字符限制的字符串生成方案数问题，可采用类似的动态规划思路，根据字符之间的关系进行状态转移。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：基础的动态规划问题，可帮助理解动态规划的基本思想。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划入门题，与本题的状态转移思想有一定相似性。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，进一步加深对动态规划的理解和应用。

---
处理用时：32.19秒