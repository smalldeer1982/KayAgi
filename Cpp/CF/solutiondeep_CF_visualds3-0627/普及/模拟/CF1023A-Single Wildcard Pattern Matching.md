# 题目信息

# Single Wildcard Pattern Matching

## 题目描述

给定两个小写英文单词 $s,t$，其中 $s$ 包含还不多于一个的 `*`。$s$ 的长度为 $n$，而 $t$ 的长度为 $m$。

$s$ 中的 `*` 可以被替换为任意小写字母串（可以是空串），但其他字母不能被更改或者调换顺序。如果将 `*` 替换为一个任意小写字母串之后，$s=t$，那么我们称 $s,t$ 是匹配的。

例如，字符串 $s=$ `lu*gu` 与 `luogu` `lugu` `luooooogu`都是匹配的，但与字符串 `lougu` `log` `lu^_^gu` `lu114514gu` 都是不匹配的。

如果给定的 $s,t$ 是匹配的，输出 `YES`，否则输出 `NO`。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le2\times10^5$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)

## 样例 #1

### 输入

```
6 10
code*s
codeforces
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6 5
vk*cup
vkcup
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1 1
v
k
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
9 6
gfgf*gfgf
gfgfgf
```

### 输出

```
NO
```

# AI分析结果



## 算法分类
字符串处理

## 综合分析与结论
题目核心是判断字符串 `s` 和 `t` 是否通过 `*` 通配符匹配。关键思路是将 `s` 按 `*` 分割为前缀和后缀，检查 `t` 是否满足：
1. `t` 的前缀匹配 `s` 的前缀；
2. `t` 的后缀匹配 `s` 的后缀；
3. `t` 的长度足够容纳前缀和后缀。

**难点**在于正确处理 `*` 的位置及边界条件（如 `*` 在开头或结尾）。各题解均采用分割前后缀的思路，但实现方式略有差异。

### 可视化设计思路
1. **动画演示**：将 `s` 拆分为 `pre` 和 `suf` 两部分，高亮显示 `t` 中与 `pre` 和 `suf` 匹配的部分，中间部分以流动动画表示通配符匹配的任意内容。
2. **像素风格**：用 8 位像素风格展示字符串，`pre` 和 `suf` 用不同颜色标记，通配符区域闪烁提示。
3. **交互功能**：支持步进控制，观察每一步匹配过程；音效提示匹配成功/失败。

## 题解评分（≥4星）
1. **小闸蟹（4.5星）**  
   - **亮点**：代码简洁高效，直接分割前后缀逐段匹配，逻辑清晰。  
   - **代码片段**：
     ```cpp
     auto Pos = Str1.find('*');
     for (int i = 0; i < p; ++i) // 前缀匹配
     for (int i = n - 1, j = m - 1; i > p; --i, --j) // 后缀匹配
     ```
2. **To_Carpe_Diem（4星）**  
   - **亮点**：使用 `substr` 直接截取前后缀，逻辑直观易懂。  
   - **代码片段**：
     ```cpp
     string s_prefix = s.substr(0, wildcard_pos);
     string s_suffix = s.substr(wildcard_pos+1);
     if (t.substr(0, s_prefix.length()) == s_prefix && ...)
     ```
3. **2012zxt（4星）**  
   - **亮点**：拼接 `t` 的前后缀与 `s` 比较，思路新颖且正确。  
   - **代码片段**：
     ```cpp
     string tmp2 = t.substr(1,pos-1) + t.substr(m-tmp1+1);
     if (s == tmp2) ...
     ```

## 最优思路提炼
1. **长度检查**：若 `n > m + 1` 直接不匹配（`*` 至少替换空串）。
2. **分割前后缀**：以 `*` 为分界，`pre` 和 `suf` 分别匹配 `t` 的头部和尾部。
3. **子串比较**：检查 `t` 的前 `pre.length()` 字符等于 `pre`，后 `suf.length()` 字符等于 `suf`。

## 相似题目推荐
1. **CF 1023A**：原题变种，可巩固思路。
2. **LeetCode 44（Wildcard Matching）**：通配符包括 `*` 和 `?`，难度提升。
3. **洛谷 P1305（字符串的展开）**：需处理通配符替换逻辑。

## 代码实现（核心逻辑）
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    if (s.find('*') == string::npos) {
        cout << (s == t ? "YES" : "NO");
        return 0;
    }

    if (n - 1 > m) {
        cout << "NO";
        return 0;
    }

    int pos = s.find('*');
    string pre = s.substr(0, pos);
    string suf = s.substr(pos + 1);

    if (t.substr(0, pos) != pre || t.substr(m - suf.size()) != suf) {
        cout << "NO";
    } else {
        cout << "YES";
    }
    return 0;
}
```

## 可视化算法演示
1. **步骤分解**：  
   - **Step 1**：高亮 `s` 中的 `*`，拆分 `pre`（绿色）和 `suf`（蓝色）。  
   - **Step 2**：在 `t` 中标记与 `pre` 和 `suf` 对应的区域，中间部分显示为黄色流动块。  
   - **Step 3**：若匹配成功，播放上扬音效并显示 "YES"；否则播放失败音效。  
2. **像素风格**：使用 16 色调色板，`pre` 和 `suf` 用不同色块渲染，通配区域动态闪烁。  
3. **交互功能**：支持暂停/继续，拖动进度条观察匹配细节。

---
处理用时：118.06秒