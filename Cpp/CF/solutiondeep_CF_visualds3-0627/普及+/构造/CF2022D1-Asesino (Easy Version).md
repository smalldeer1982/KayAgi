# 题目信息

# Asesino (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, you can ask at most $ n+69 $ questions. You can make hacks only if both versions of the problem are solved.

This is an interactive problem.

It is a tradition in Mexico's national IOI trainings to play the game "Asesino", which is similar to "Among Us" or "Mafia".

Today, $ n $ players, numbered from $ 1 $ to $ n $ , will play "Asesino" with the following three roles:

- Knight: a Knight is someone who always tells the truth.
- Knave: a Knave is someone who always lies.
- Impostor: an Impostor is someone everybody thinks is a Knight, but is secretly a Knave.

Each player will be assigned a role in the game. There will be exactly one Impostor but there can be any (possible zero) number of Knights and Knaves.

As the game moderator, you have accidentally forgotten the roles of everyone, but you need to determine the player who is the Impostor.

To determine the Impostor, you will ask some questions. In each question, you will pick two players $ i $ and $ j $ ( $ 1 \leq i, j \leq n $ ; $ i \neq j $ ) and ask if player $ i $ thinks that player $ j $ is a Knight. The results of the question is shown in the table below.

 KnightKnaveImpostorKnightYesNoYesKnaveNoYesNoImpostorNoYes— The response of the cell in row $ a $ and column $ b $ is the result of asking a question when $ i $ has role $ a $ and $ j $ has row $ b $ . For example, the "Yes" in the top right cell belongs to row "Knight" and column "Impostor", so it is the response when $ i $ is a Knight and $ j $ is an Impostor.Find the Impostor in at most $ n + 69 $ questions.

Note: the grader is adaptive: the roles of the players are not fixed in the beginning and may change depending on your questions. However, it is guaranteed that there exists an assignment of roles that is consistent with all previously asked questions under the constraints of this problem.

## 说明/提示

Note that the example test cases do not represent an optimal strategy for asking questions and are only shown for the sake of demonstrating the interaction format. Specifically, we cannot determine which player is the Impostor from the questions asked in the examples.

In the first test case of the example, players at indices $ 2 $ and $ 6 $ are Knights, players at indices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are Knaves, and the Impostor is at index $ 4 $ . The following is an explanation of the questions asked:

- In the first query, player $ i $ is a Knave and player $ j $ is a Knave. The answer is "yes" since Knaves always lie.
- In the second query, player $ i $ is a Knave and player $ j $ is a Knight. The answer is "no" since Knaves always lie.
- In the third query, player $ i $ is a Knight and player $ j $ is a Knave. The answer is "no" since Knights always tell the truth.
- In the fourth query, player $ i $ is a Knight and player $ j $ is a Knight. The answer is "yes" since Knights always tell the truth.
- In the fifth query, player $ i $ is a Impostor and player $ j $ is a Knave. The answer is "yes" since the Impostor always lies.
- In the sixth query, player $ i $ is a Impostor and player $ j $ is a Knight. The answer is "no" since the Impostor always lies.
- In the seventh query, player $ i $ is a Knave and player $ j $ is a Impostor. The answer is "no" since Knaves always lie and Knaves thinks that the Impostor is a Knight.
- In the eighth query, player $ i $ is a Knight and player $ j $ is a Impostor. The answer is "yes" since Knights always tell the truth and Knights think that the Impostor is a Knight.

## 样例 #1

### 输入

```
2
7

1

0

0

1

1

0

0

1

4

0

1

1

1```

### 输出

```
? 1 3

? 7 6

? 2 5

? 6 2

? 4 5

? 4 6

? 1 4

? 2 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3```

# AI分析结果



## 算法分类
无算法分类

---

## 题解思路与解决难点

### 核心思路
通过**对称性询问**发现矛盾，确定嫌疑对，再用第三方验证。  
- 若 `ask(i,j) != ask(j,i)`，则 i 或 j 必为冒名顶替者。
- 选择第三方 k 进行交叉验证，通过 `ask(i,k)` 与 `ask(k,i)` 是否一致确定最终答案。

### 关键难点
1. **动态角色分配**：题目中角色分配是动态的，需保证所有问题存在一致解。
2. **对称性破缺**：如何高效找到矛盾对（冒名顶替者参与的询问对）。
3. **边界处理**：当 n 为奇数时，需正确处理未配对玩家的逻辑。

### 解决方案
1. **成对遍历**：将所有玩家两两配对，进行双向询问。
2. **第三方验证**：发现矛盾对后，选择非矛盾对成员作为第三方验证点。
3. **奇偶处理**：对奇数情况最后一个未配对玩家直接判为冒名顶替者。

---

## 题解评分 (≥4星)
### [WuMin4] ⭐⭐⭐⭐
- **亮点**：简洁的循环遍历策略，优雅处理奇偶边界。
- **代码分析**：  
  通过相邻配对 `(i, i+1)` 快速扫描，未找到矛盾时直接取最后一个未配对玩家。
  验证阶段选择前序或后序玩家作为第三方，逻辑清晰。
  
### [yifu_chen] ⭐⭐⭐⭐
- **亮点**：镜像配对策略 `(i, n-i+1)`，减少冗余询问。
- **代码分析**：  
  对称遍历覆盖所有可能对，中间未配对点直接作为答案候选，适合冒名顶替者在中心的情况。

### [ykzzldz] ⭐⭐⭐⭐
- **亮点**：理论推导清晰，给出严格数学证明。
- **代码简评**：  
  未提供完整代码，但思路与 WuMin4 相似，逻辑自洽。

---

## 最优思路提炼
1. **矛盾对检测**：`ask(i,j) != ask(j,i)` 时必存在冒名顶替者。
2. **第三方交叉验证**：  
   ```python
   if ask(i,k) != ask(k,i): 
       return i  
   else: 
       return j
   ```
3. **奇偶边界处理**：奇数玩家时最后一个未配对者直接作为候选。

---

## 同类型题与类似套路
1. **对称性破缺**：如 [CF1144F](https://codeforces.com/problemset/problem/1144/F)（图的边定向问题）。
2. **交互题验证**：如 [洛谷 P1854](https://www.luogu.com.cn/problem/P1854)（猜数游戏）。
3. **角色推理逻辑**：类似狼人杀身份推理问题，如 [Codeforces 834C](https://codeforces.com/problemset/problem/834/C)。

---

## 推荐相似题目
1. **洛谷 P2664**（树上博弈，对称性分析）
2. **Codeforces 1037E**（动态图判定，矛盾边处理）
3. **LeetCode 753**（交互式密码破解，最优步数设计）

---

## 算法可视化设计
### 动画方案
1. **网格布局**：玩家编号排列成环，用不同颜色区分角色（骑士绿/骗子红/冒名顶替者紫）。
2. **询问高亮**：每次询问时，连接 i→j 的箭头闪烁，显示回答结果（Yes/No）。
3. **矛盾检测**：当双向箭头颜色不同时（红蓝对比），触发警报并锁定嫌疑对。
4. **第三方验证**：用黄色高亮第三方 k，动态显示交叉验证过程。

### 复古像素风格
- **Canvas 绘制**：8-bit 像素风角色头像，询问时播放经典 FC 音效。
- **自动演示模式**：  
  模拟“贪吃蛇AI”路径，自动遍历配对并验证，背景音乐循环播放《超级玛丽》地下城BGM。
- **积分系统**：每次正确识别冒名顶替者+100分，剩余提问次数转换为连击奖励。

---

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;

bool ask(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    string res; cin >> res;
    return res == "YES";
}

void solve() {
    cin >> n;
    // 镜像配对检测 (i, n-i+1)
    for(int i=1; i < n-i+1; ++i) {
        bool res1 = ask(i, n-i+1);
        bool res2 = ask(n-i+1, i);
        if(res1 != res2) {
            // 选择第三方验证
            int k = (i != 1) ? 1 : 2;
            bool r1 = ask(i, k);
            bool r2 = ask(k, i);
            cout << "! " << (r1 != r2 ? i : n-i+1) << endl;
            return;
        }
    }
    // 奇数情况处理
    cout << "! " << (n+1)/2 << endl;
}

int main() {
    cin >> T;
    while(T--) solve();
}
```

---

## 关键逻辑说明
1. **镜像配对**：确保每个玩家最多被询问两次，覆盖所有可能的矛盾对。
2. **第三方选择**：优先选择非端点玩家（如1号或2号），保证非冒名顶替者身份。
3. **奇偶处理**：当所有配对均无矛盾时，中间玩家必为冒名顶替者。

---
处理用时：275.56秒