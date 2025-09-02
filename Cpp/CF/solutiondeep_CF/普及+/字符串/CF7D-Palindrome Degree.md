# 题目信息

# Palindrome Degree

## 题目描述

String $ s $ of length $ n $ is called $ k $ -palindrome, if it is a palindrome itself, and its prefix and suffix of length ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF7D/f337f976991ac53405b164907ebe1f51ebb0830e.png) are $ (k-1) $ -palindromes. By definition, any string (even empty) is 0-palindrome.

Let's call the palindrome degree of string $ s $ such a maximum number $ k $ , for which $ s $ is $ k $ -palindrome. For example, "abaaba" has degree equals to $ 3 $ .

You are given a string. Your task is to find the sum of the palindrome degrees of all its prefixes.

## 样例 #1

### 输入

```
a2A
```

### 输出

```
1```

## 样例 #2

### 输入

```
abacaba
```

### 输出

```
6```

# AI分析结果



# 题目中文翻译

## 题目名称：回文度

### 题目描述

长度为 $n$ 的字符串 $s$ 被称为 $k$ 阶回文串，当且仅当它本身是回文串，且其长度为 $\lfloor \frac{n}{2} \rfloor$ 的前缀和后缀都是 $(k-1)$ 阶回文串。根据定义，任何字符串（包括空串）都是 0 阶回文串。

我们定义字符串 $s$ 的回文度为最大的 $k$ 值，使得 $s$ 是 $k$ 阶回文串。例如，"abaaba" 的回文度为 3。

给定一个字符串，请计算其所有前缀回文度之和。

## 样例 #1

### 输入
```
a2A
```

### 输出
```
1
```

## 样例 #2

### 输入
```
abacaba
```

### 输出
```
6
```

---

# 题解综合分析

### 核心算法思路
所有题解均采用动态规划（DP）结合哈希校验的核心框架：
1. **状态定义**：$dp[i]$ 表示前缀 $s[1..i]$ 的回文度
2. **转移方程**：  
   $dp[i] = \begin{cases} 
   dp[\lfloor i/2 \rfloor] + 1 & \text{若 } s[1..i] \text{是回文} \\
   0 & \text{否则}
   \end{cases}$
3. **回文校验**：通过双哈希（正序+逆序）或滚动哈希实现高效判断

### 优化关键
1. **滚动哈希**：边遍历边计算哈希值（无需预处理整个哈希数组），空间复杂度优化至 $O(1)$
2. **位运算加速**：利用 `i >> 1` 快速计算 $\lfloor i/2 \rfloor$
3. **同余处理**：通过大基数（如13、131）和自然溢出降低碰撞概率

---

# 高分题解推荐

## 1. 唐一文（★★★★☆）
**关键亮点**：  
- 滚动哈希实时计算，空间复杂度最优  
- 代码极致简洁（仅15行核心逻辑）  
- 自然溢出处理避免取模运算  

```cpp
int main(){
    scanf("%s",c),n=strlen(c);
    for(register int i=0;i<n;++i){
        fro=fro*13+c[i],bac=bac+fac*c[i],fac=fac*13;
        !(fro^bac)?ans+=(dp[i]=dp[i-1>>1]+1):0;
    }
    printf("%d",ans);
}
```

## 2. Gaode_Sean（★★★★☆）
**核心优势**：  
- 变量命名清晰，可读性更佳  
- 使用131作为基数，平衡性能与碰撞概率  
- 逻辑流线性复杂度 $O(n)$  

```cpp
for(int i=1;i<=n;i++){
    a=a*131+ch[i],b+=ch[i]*t;
    t*=131;
    if(a==b) dp[i]=dp[i>>1]+1,ans+=dp[i];
}
```

## 3. smqk（★★★☆☆）
**独特价值**：  
- 提供Java实现版本  
- 展示基础哈希应用模式  
- 变量注释详细，适合教学  

```java
int forward = 0, back = 0, factor = 1;
for (int i = 0; i < n; i++) {
    forward = forward * 13 + s.charAt(i);
    back = back + s.charAt(i) * factor;
    factor *= 13;
    if (forward == back) {
        ans += (dp[i] = dp[(i - 1) / 2] + 1);
    }
}
```

---

# 关键技巧总结
1. **滚动哈希**：动态维护前缀的正逆序哈希值，避免预处理存储所有哈希
2. **状态转移优化**：利用回文的递归性质，将问题规模不断折半
3. **基数选择**：使用质数（如13、131、149）作为哈希基数，降低碰撞概率
4. **位运算加速**：用 `i >> 1` 替代 $\lfloor i/2 \rfloor$ 的计算

---

# 拓展训练建议
### 同类题目推荐
1. P1210 [USACO1.5] 回文质数 —— 回文判断与质数校验结合
2. P1435 [IOI2000] 回文字串 —— 动态规划求最小插入次数
3. P1659 [国家集训队] 拉拉队排练 —— Manacher算法与快速幂结合

### 调试经验摘录
> "注意哈希基数的选择要足够大，否则可能发生碰撞导致错误判断" —— 唐一文的代码使用13作为基数，通过自然溢出处理  
> "当i为奇数时，前半部分长度应为⌊i/2⌋，需要确保哈希区间正确" —— Fool_Fish在预处理逆序哈希时的关键点

---
处理用时：60.61秒