# 题目信息

# [POI 2012] PRE-Prefixuffix

## 题目描述

We consider strings consisting of lowercase letters of the English alphabet in this problem.

An initial fragment of a given string is called its prefix.

A final (terminal) fragment of a given string is called its suffix.

In particular, the empty string is both a prefix and a suffix of any string.

Two strings are cyclically equivalent if one of them can be obtained from another by    moving its certain suffix from the end of the string to its beginning.

For example, the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.1.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.2.png) are cyclically equivalent, whereas the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.3.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.4.png) are not.

In particular, every string is cyclically equivalent to itself.

A string ![](http://main.edu.pl/images/OI19/pre-en-tex.5.png) consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.6.png) letters is given.

We are looking for its prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.7.png) and suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.8.png) of equal length such that:

![](http://main.edu.pl/images/OI19/pre-en-tex.9.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.10.png) are cyclically equivalent,                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.11.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.12.png) does not exceed ![](http://main.edu.pl/images/OI19/pre-en-tex.13.png)        (i.e., the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.14.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.15.png) do not overlap in ![](http://main.edu.pl/images/OI19/pre-en-tex.16.png)), and                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.17.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.18.png) is maximized.

对于两个串 $S_1, S_2$，如果能够将 $S_1$ 的一个后缀移动到开头后变成 $S_2$，就称 $S_1$ 和 $S_2$ 循环相同。例如串 ababba 和串 abbaab 是循环相同的。

给出一个长度为 $n$ 的串 $S$，求满足下面条件的最大的 $L(L\leq \frac n 2)$：$S$ 的 $L$ 前缀和 $S$ 的 $L$ 后缀是循环相同的。

## 说明/提示

数据范围：

- 对于 $30\%$ 的数据，保证 $n\le 500$；
- 对于 $50\%$ 的数据，保证 $n\le 5000$；
- 对于 $100\%$ 数据，保证 $1\le n\le 10^6$。

## 样例 #1

### 输入

```
15
ababbabababbaab```

### 输出

```
6```

# AI分析结果


# 💡 Kay的C++算法解析：PRE-Prefixuffix 深入学习指南 💡

> "想象字符串是一根彩带，我们要在两端剪掉相同长度的A段，剩下的中间部分还要剪出相同长度的B段。通过巧妙的滑动窗口技巧和快速比较工具，我们就能高效找到最长匹配方案！"

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：**字符串哈希** 与 **编程技巧应用**

🗣️ **初步分析**：
> 解决"PRE-Prefixuffix"关键在于理解**循环同构的本质**——就像把彩带剪成AB和BA两段后重新拼接。我们需要找到最长的前缀A和后缀A'，使得中间部分的前缀B等于后缀B'。
> - **核心技巧**：利用`f[i] ≤ f[i+1]+2`的单调性关系，从字符串中心向两边扩展，像滑动窗口般高效寻找B段长度
> - **算法流程**：
>   1. 初始化双哈希数组
>   - 从n/2向1倒序枚举A的长度i
>   - 根据f[i+1]推算f[i]初始值（f[i+1]+2）
>   - 逐步减小f[i]直到中间B段匹配
> - **可视化设计**：在像素动画中，我们将用**蓝色标记A段**，**金色标记匹配的B段**，红色标记当前尝试的B段范围。当i减小时，窗口位置会**像素滑动**，匹配成功时播放8-bit胜利音效

---

## 2. 精选优质题解参考

**题解一（Alex_Wei）**
* **点评**：思路清晰阐释了循环同构转化为AB/BA模型的推导过程，创新性地利用`f[i]≤f[i+1]+2`的单调性减少比较次数。代码采用**双模数哈希**避免冲突，变量命名规范（如`f[i]`表示中间段border长度），边界处理严谨（检查f[i]是否超出中间段长度限制）。实践价值高，可直接用于竞赛场景。

**题解二（Leasier）**
* **点评**：代码简洁有力，仅60行实现核心逻辑。亮点在于用最精简的结构展示算法骨架：初始化哈希→倒序计算f[i]→验证匹配。虽然省略KMP求border步骤，但哈希比较部分采用双模数确保正确性，适合初学者理解核心思路。

**题解三（small_john）**
* **点评**：解题策略阐述直观，将算法比喻为"剪彩带"帮助理解。代码规范完整，包含详细注释，特别强调`(hash+mod)%mod`的双重取模技巧避免负值。虽赞数较少，但实现完整且边界处理清晰，作为学习模板非常合适。

---

## 3. 核心难点辨析与解题策略

1.  **难点：循环同构的等价转化**
    * **分析**：关键要理解AB=BA的数学本质。当S[1..L]与S[n-L+1..n]循环同构时，必存在划分点k使得S[1..k]=A, S[k+1..L]=B, 且S[n-L+1..n-L+k]=B, S[n-L+k+1..n]=A
    * 💡 **学习笔记**：循环问题拆解为AB/BA模型是通用解题思路

2.  **难点：f[i]的高效计算**
    * **分析**：基于观察——当A长度i减少1时，中间段B的最大长度最多增加2（f[i]≤f[i+1]+2）。因此从大i向小i枚举时，只需从f[i+1]+2开始递减检测，避免重算
    * 💡 **学习笔记**：利用状态间的单调性关系减少枚举量

3.  **难点：哈希冲突处理**
    * **分析**：自然溢出哈希易被特殊数据卡掉。优质题解均采用**双模数哈希**(如mod1=1e9+7, mod2=1e9+9)，当两个哈希值同时匹配才判定子串相等
    * 💡 **学习笔记**：竞赛中必须使用双哈希避免冲突

### ✨ 解题技巧总结
- **问题分解法**：将循环同构拆解为A段匹配+B段匹配两个子问题
- **单调性优化**：发现f[i]与f[i+1]的约束关系，减少无效计算
- **哈希技巧**：双模数哈希+幂次预处理实现O(1)子串比较
- **边界艺术**：及时检查f[i]≤(n/2-i)，防止数组越界

---

## 4. C++核心代码实现赏析

**本题通用核心C++实现**
* **说明**：综合优质题解思路，采用双模数哈希和单调性优化，完整展示算法框架
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
const int mod1 = 1e9+7, mod2 = 1e9+9;
const int base = 131;

int n, f[N];
char s[N];
long long h1[N], h2[N], pw1[N], pw2[N];

long long get_hash(int l, int r, int type) {
    if(type == 1) 
        return (h1[r] - h1[l-1]*pw1[r-l+1] % mod1 + mod1) % mod1;
    return (h2[r] - h2[l-1]*pw2[r-l+1] % mod2 + mod2) % mod2;
}

bool match(int l1, int r1, int l2, int r2) {
    return get_hash(l1,r1,1)==get_hash(l2,r2,1) && 
           get_hash(l1,r1,2)==get_hash(l2,r2,2);
}

int main() {
    scanf("%d%s", &n, s+1);
    pw1[0] = pw2[0] = 1;
    for(int i=1; i<=n; i++) {
        pw1[i] = pw1[i-1]*base % mod1;
        pw2[i] = pw2[i-1]*base % mod2;
        h1[i] = (h1[i-1]*base + s[i]) % mod1;
        h2[i] = (h2[i-1]*base + s[i]) % mod2;
    }

    for(int i=n/2; i>=1; i--) {
        f[i] = f[i+1] + 2;
        while(f[i]) {
            if(i + f[i] > n/2) f[i]--;
            else if(!match(i+1,i+f[i], n-i-f[i]+1, n-i)) f[i]--;
            else break;
        }
    }

    int ans = 0;
    for(int i=1; i<=n/2; i++)
        if(match(1,i, n-i+1,n))
            ans = max(ans, i + f[i]);
    printf("%d\n", ans);
}
```
* **代码解读概要**：
  1. **哈希预处理**：计算双模数哈希数组h1/h2和对应幂次pw1/pw2
  2. **倒序枚举**：从i=n/2开始递减计算f[i]，初始值设为f[i+1]+2
  3. **调整f[i]**：确保f[i]不越界且中间B段匹配
  4. **验证答案**：当A段匹配时，用i+f[i]更新最大长度

**题解一（Alex_Wei）片段**
* **亮点**：严谨处理f[i]的三种递减情况
* **核心代码**：
```cpp
for(int i=n/2; i; i--) {
    f[i] = f[i+1] + 2;
    while(f[i]) {
        if((i+f[i])*2 > n) f[i]--;       // 情况1：长度越界
        else if(!match(i+1,i+f[i], n-i-f[i]+1, n-i)) f[i]--; // 情况2：不匹配
        else break;                      // 情况3：匹配成功
    }
}
```
* **代码解读**：
  > 这个while循环是算法核心！就像尝试不同长度的剪刀——先按最大可能长度(f[i+1]+2)裁剪彩带，如果太长(if分支)或两端不匹配(else if分支)就缩短剪刀长度。直到找到刚好匹配的长度或剪刀缩到0为止。
* 💡 **学习笔记**：边界检查与匹配验证分离，保证代码健壮性

**题解二（Leasier）片段**
* **亮点**：精简的哈希比较函数
* **核心代码**：
```cpp
bool same(int l1,int r1,int l2,int r2) {
    return get1(l1,r1)==get1(l2,r2) 
        && get2(l1,r1)==get2(l2,r2);
}
```
* **代码解读**：
  > 通过封装same函数，将复杂的双哈希比较简化为单一调用。就像用特制的尺子同时测量两条彩带的颜色和纹理，只有完全吻合才返回true。
* 💡 **学习笔记**：功能封装提升代码可读性

**题解三（small_john）片段**
* **亮点**：清晰的变量命名和注释
* **核心代码**：
```cpp
// f[i]: 去掉首尾i字符后中间串的border长度
// 枚举i从n/2递减，利用f[i] <= f[i+1]+2
for(int i=n/2; i>=1; i--) {
    f[i] = f[i+1] + 2;  // 初始最大可能值
    while(f[i] && !match(...)) // 逐步调整
        f[i]--;
}
```
* **代码解读**：
  > 注释精准解释f[i]定义和迭代原理。就像登山时根据前人的足迹(f[i+1])确定下一步跨度(+2)，再微调找到稳固落脚点。
* 💡 **学习笔记**：好注释是代码的导航图

---

## 5. 算法可视化：像素动画演示

**主题**：8-bit字符串探险——寻找循环同构宝藏

**核心演示**：动态展示f[i]计算过程，将字符串转化为彩色像素带，通过复古游戏界面演示滑动窗口如何高效寻找匹配段

**设计思路**：
> 采用FC游戏风格，将字符串显示为16色像素带。A段用蓝色，尝试中的B段用闪烁红色，匹配成功的B段变金色。背景播放8-bit循环音乐，关键操作配电子音效。

**动画步骤**：
1. **场景初始化**：
   - 顶部控制面板：开始/暂停/单步/速度滑块
   - 主画面：字符串转为像素带（如"ababb..."→🟦🟩🟨...）
   - 侧边栏：显示当前i、f[i]值和代码执行行

2. **枚举过程演示**：
   ```mermaid
   graph LR
   A[i从n/2开始] --> B[显示蓝色A段]
   B --> C[f[i]=f[i+1]+2 红框扩展]
   C --> D{红框内匹配？}
   D -- 是 --> E[变金框 播放胜利音]
   D -- 否 --> F[红框缩小 播放错误音]
   ```

3. **交互特效**：
   - 单步执行：按方向键触发，i值变化时像素带滑动
   - 自动模式：AI角色从左向右跑动，跑到位置i时触发计算
   - 音效设计：
     * 尝试匹配："哔-哔"电子音
     * 匹配成功：上升旋律
     * 更新答案：金币收集音

4. **关键步骤可视化**：
   - 当f[i]递减时，红框像弹簧般收缩
   - 匹配成功瞬间，红框转为金框并扩散光波
   - 每次i变化，屏幕下方显示`f[%d]=f[%d]+2 → %d`的推导公式

---

## 6. 拓展练习与相似问题思考

**技巧迁移场景**：
1. **循环位移判断**：判断两字符串是否循环同构（LeetCode 796）
2. **重复子串构造**：用最小循环节构造目标串（CodeForces 1096C）
3. **双border问题**：在前后缀约束下寻找特殊子串（洛谷P4555）

**洛谷推荐**：
1. **P3375 KMP模板** 
   - 🗣️ 巩固border概念，理解f[i]单调性的理论基础
2. **P4391 无线传输** 
   - 🗣️ 练习循环节应用，强化问题分解能力
3. **P5829 失配树** 
   - 🗣️ 深入border树结构，提升字符串进阶技巧

---

## 7. 学习心得与经验分享

> **来自Alex_Wei的调试经验**："自然溢出哈希被卡了3次提交后才改用双模数哈希"

**Kay的总结**：
- 自然溢出哈希在竞赛中风险极高，必须用双模数哈希
- 哈希模数优先选1e9+7和1e9+9这对孪生质数
- 取模运算务必写`(x%mod+mod)%mod`双重保险

> **来自喵の耳的血泪教训**："取模没写规范，负数哈希导致WA"

**Kay的总结**：
- 负数取模：C++的`%`可能返回负值，必须调整
- 测试技巧：构造全a字符串验证边界情况
- 防御性编程：在哈希函数内直接完成负数矫正

---

本次"PRE-Prefixuffix"的解析就到这里。记住：字符串问题就像解谜游戏，找到正确的拆解方式和优化技巧就能事半功倍。下次挑战再见！💪

---
处理用时：226.89秒