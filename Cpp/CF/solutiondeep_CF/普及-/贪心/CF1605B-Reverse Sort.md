# 题目信息

# Reverse Sort

## 题目描述

题目共给出 $t(1 \le t \le 1000)$ 组数据，每组数据包含一个正整数 $n(1 \le n \le 1000)$ 和一个长度为 $n$ 的 $01$ 串 $s$， 现在你需要在 $s$ 中选出一个子序列，将这个子序列中的字符翻转（如字符串 $10100$， 选出子序列 $1100$， 翻转得到 $0011$， 放回原串中得到 $00011$），使得翻转后的字符串字典序最小。

## 样例 #1

### 输入

```
3
7
0011111
5
10100
6
001000```

### 输出

```
0
1
4 1 3 4 5 
1
3 3 5 6```

# AI分析结果



# 题目重述

## 反转排序

### 题目描述

给定 $t(1 \le t \le 1000)$ 组数据，每组数据包含一个正整数 $n(1 \le n \le 1000)$ 和一个长度为 $n$ 的 $01$ 串 $s$。要求通过一次子序列翻转操作，使得翻转后的字符串字典序最小（即所有 $0$ 在前，$1$ 在后），并输出操作方案。

### 样例输入

```
3
7
0011111
5
10100
6
001000
```

### 样例输出

```
0
1
4 1 3 4 5 
1
3 3 5 6
```

---

# 综合题解分析

## 关键思路总结

1. **一次操作即可完成**：所有题解均指出，通过一次翻转即可完成排序。核心思路是找到前段（应为 $0$ 的区域）中的 $1$ 和后段（应为 $1$ 的区域）中的 $0$，将这些位置组成子序列进行翻转。
2. **位置统计**：计算 $0$ 的总数 `cnt0`，则前 `cnt0` 位应为 $0$，其余为 $1$。统计前段中的 $1$ 和后段中的 $0$，它们的数量相等，形成一一对应。
3. **输出格式**：输出这些位置的索引（注意题目要求从 $1$ 开始编号）。

---

## 精选题解

### 题解1：Jerrlee✅（5星）
**关键亮点**：思路清晰，代码简洁，直接统计关键位置。
```cpp
int main() {
    int t; cin >> t;
    while(t--) {
        int n, c = 0; string s;
        cin >> n >> s;
        // 统计1的个数c，并判断是否已有序
        bool sorted = true;
        for(int i = 0; i < n; i++) {
            if(s[i] == '1') c++;
            if(i > 0 && s[i] < s[i-1]) sorted = false;
        }
        if(sorted) { cout << "0\n"; continue; }
        // 统计需要翻转的位置
        vector<int> ans;
        for(int i = 0; i < n - c; i++) 
            if(s[i] == '1') ans.push_back(i+1);
        for(int i = n - c; i < n; i++)
            if(s[i] == '0') ans.push_back(i+1);
        // 输出结果
        cout << "1\n" << ans.size() << " ";
        for(int x : ans) cout << x << " ";
        cout << "\n";
    }
}
```

### 题解2：YangXiaopei（4星）
**关键亮点**：逻辑明确，变量命名清晰，适合初学者理解。
```cpp
int main() {
    int t; cin >> t;
    while(t--) {
        int n, cnt0 = 0; string s;
        cin >> n >> s;
        // 统计0的个数
        for(char c : s) if(c == '0') cnt0++;
        // 判断是否已有序
        bool need_op = false;
        for(int i = 0; i < cnt0; i++) 
            if(s[i] == '1') { need_op = true; break; }
        if(!need_op) { cout << "0\n"; continue; }
        // 收集翻转位置
        vector<int> pos;
        for(int i = 0; i < cnt0; i++) 
            if(s[i] == '1') pos.push_back(i+1);
        for(int i = cnt0; i < n; i++) 
            if(s[i] == '0') pos.push_back(i+1);
        // 输出
        cout << "1\n" << pos.size() << " ";
        for(int x : pos) cout << x << " ";
        cout << "\n";
    }
}
```

### 题解3：shredded_beef_qwq（4星）
**关键亮点**：双指针法动态匹配位置，避免冗余统计。
```cpp
int main() {
    int t; cin >> t;
    while(t--) {
        int n; string s;
        cin >> n >> s;
        int i = 0, j = n-1;
        vector<int> ans;
        // 双指针寻找不匹配的位置
        while(i < j) {
            while(i < j && s[i] != '1') i++;
            while(i < j && s[j] != '0') j--;
            if(i >= j) break;
            ans.push_back(i+1);
            ans.push_back(j+1);
            i++; j--;
        }
        if(ans.empty()) cout << "0\n";
        else {
            sort(ans.begin(), ans.end());
            cout << "1\n" << ans.size() << " ";
            for(int x : ans) cout << x << " ";
            cout << "\n";
        }
    }
}
```

---

## 关键技巧与拓展

1. **逆向思维**：最终目标状态唯一，直接构造目标字符串对比差异位置。
2. **双指针优化**：动态匹配前后端不合法字符，减少遍历次数。
3. **举一反三**：类似问题可参考[CF 1581B](https://codeforces.com/problemset/problem/1581/B)（区间操作优化）、[洛谷 P1106](https://www.luogu.com.cn/problem/P1106)（删数问题）、[洛谷 P1090](https://www.luogu.com.cn/problem/P1090)（贪心合并）。

---

## 个人心得摘录

- **索引偏移**：多位题解作者提到因字符串索引从 $0$ 开始，输出时需 `+1`，否则会导致错误。
- **边界检查**：需先判断是否已有序，避免无效操作。例如，Jerrlee的代码中通过一次遍历同时统计 $1$ 的数量和有序性。
- **代码简洁性**：直接使用 `vector` 收集位置比维护多个数组更简洁，如YangXiaopei的代码所示。

---
处理用时：100.35秒