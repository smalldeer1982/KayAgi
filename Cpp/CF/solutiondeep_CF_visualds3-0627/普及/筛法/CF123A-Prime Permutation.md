# 题目信息

# Prime Permutation

## 题目描述

You are given a string $ s $ , consisting of small Latin letters. Let's denote the length of the string as $ |s| $ . The characters in the string are numbered starting from $ 1 $ .

Your task is to find out if it is possible to rearrange characters in string $ s $ so that for any prime number $ p<=|s| $ and for any integer $ i $ ranging from $ 1 $ to $ |s|/p $ (inclusive) the following condition was fulfilled $ s_{p}=s_{p×i} $ . If the answer is positive, find one way to rearrange the characters.

## 说明/提示

In the first sample any of the six possible strings will do: "abc", "acb", "bac", "bca", "cab" or "cba".

In the second sample no letter permutation will satisfy the condition at $ p=2 $ ( $ s_{2}=s_{4} $ ).

In the third test any string where character "y" doesn't occupy positions 2, 3, 4, 6 will be valid.

## 样例 #1

### 输入

```
abc
```

### 输出

```
YES
abc
```

## 样例 #2

### 输入

```
abcd
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
xxxyxxx
```

### 输出

```
YES
xxxxxxy
```

# AI分析结果



# 算法分类  
**数论（质数筛法） + 贪心**

---

## 综合分析与结论  
### 核心思路  
1. **关键位置确定**  
   - 所有合数位置必须与某一质数位置相同  
   - 质数位置若满足 `p <= n/2`，则其倍数位置必须与其相同  
   - 最终所有必须相同的位置构成一个**大集合**，其余位置可自由填充  

2. **贪心策略**  
   - 统计字符出现次数，选择出现次数最多的字符填充大集合  
   - 剩余字符随意填充非关键位置  

### 难点对比  
- **Oscar12345**：通过预处理每个数的最大质因子标记关键位置，逻辑复杂但通用  
- **qwertim**：直接判断位置是否为合数或小质数，简洁高效  
- **Rei_Sen**：利用筛法预处理质数，快速计算关键位置总数，代码最简  

### 可视化设计  
1. **像素动画**  
   - **红色方块**：表示必须填充相同字符的关键位置  
   - **绿色方块**：自由填充位置  
   - **动态填充**：从高频字符开始，逐步填充红色区域，再填充绿色区域  

2. **音效设计**  
   - 填充关键位置时播放"叮"声，自由位置播放"嗒"声  
   - 成功时播放8-bit胜利音乐，失败时播放低沉音效  

---

## 高星题解推荐  
### [qwertim] ⭐⭐⭐⭐⭐  
- **亮点**：直接推导关键位置范围，代码简洁高效  
- **核心代码**：  
  ```cpp  
  rep(i,2,s.size()) // 判断每个位置是否为关键位置  
    if(!prime(i)) b[i]=1,sp++;  
    else if(i<=s.size()/2) b[i]=1,sp++;  
  ```

### [Rei_Sen] ⭐⭐⭐⭐  
- **亮点**：数学推导清晰，预处理筛法快速计算关键位置数  
- **关键逻辑**：  
  ```cpp  
  int siz_need = n - (presum[n] + 1) + presum[n / 2];  
  ```

### [Lily_White] ⭐⭐⭐  
- **亮点**：尝试用并查集管理连通块，适合复杂变式题  
- **启示性代码**：  
  ```cpp  
  for (int j = i; j <= n; j += i) // 合并质数倍数到集合  
    if (!mark[j]) mark[j] = true, pos.pb(j);  
  ```

---

## 最优代码实现  
### 核心逻辑（qwertim 简化版）  
```cpp  
int main() {  
    string s; cin >> s;  
    vector<int> cnt(26,0);  
    for(char c:s) cnt[c-'a']++;  

    int n = s.size(), need = 0;  
    vector<bool> must(n+1, false);  
    for(int i=2; i<=n; ++i) {  
        if(!is_prime(i)) must[i] = true, need++;  
        else if(i <= n/2) must[i] = true, need++;  
    }  

    char max_char = 'a';  
    int max_cnt = *max_element(cnt.begin(), cnt.end());  
    if(max_cnt < need) { cout << "NO"; return 0; }  

    // 构造答案  
    string ans(n, ' ');  
    for(int i=1; i<=n; ++i)  
        if(must[i]) ans[i-1] = max_char, cnt[max_char-'a']--;  

    int ptr = 0;  
    for(int i=0; i<n; ++i) {  
        if(ans[i] != ' ') continue;  
        while(cnt[ptr] == 0) ptr++;  
        ans[i] = 'a' + ptr;  
        cnt[ptr]--;  
    }  
    cout << "YES\n" << ans;  
}  
```

---

## 相似题目推荐  
1. **CF17C Balance**（字符串平衡与字符重组）  
2. **Luogu P1217 [USACO] 回文质数**（质数性质与字符串处理）  
3. **CF451C Predict Outcome of the Game**（数学推导与排列组合）  

---

## 可视化演示要点  
1. **初始标记阶段**  
   - 用红色高亮所有合数位置  
   - 用黄色高亮 `p <= n/2` 的质数位置  

2. **填充阶段**  
   - 最大频率字符（如蓝色方块）逐步填充红色/黄色区域  
   - 剩余字符（绿色方块）填充白色区域  

3. **音效触发**  
   - 关键位置填充时播放 `beep(800, 100)`  
   - 自由填充时播放 `beep(400, 100)`  

---

通过上述分析与实现，可快速掌握质数筛法与贪心策略在该类问题中的核心应用，并通过可视化加深对关键位置标记过程的理解。

---
处理用时：80.26秒