# 题目信息

# Poisoned Dagger

## 题目描述

Monocarp is playing yet another computer game. In this game, his character has to kill a dragon. The battle with the dragon lasts $ 100^{500} $ seconds, during which Monocarp attacks the dragon with a poisoned dagger. The $ i $ -th attack is performed at the beginning of the $ a_i $ -th second from the battle start. The dagger itself does not deal damage, but it applies a poison effect on the dragon, which deals $ 1 $ damage during each of the next $ k $ seconds (starting with the same second when the dragon was stabbed by the dagger). However, if the dragon has already been poisoned, then the dagger updates the poison effect (i.e. cancels the current poison effect and applies a new one).

For example, suppose $ k = 4 $ , and Monocarp stabs the dragon during the seconds $ 2 $ , $ 4 $ and $ 10 $ . Then the poison effect is applied at the start of the $ 2 $ -nd second and deals $ 1 $ damage during the $ 2 $ -nd and $ 3 $ -rd seconds; then, at the beginning of the $ 4 $ -th second, the poison effect is reapplied, so it deals exactly $ 1 $ damage during the seconds $ 4 $ , $ 5 $ , $ 6 $ and $ 7 $ ; then, during the $ 10 $ -th second, the poison effect is applied again, and it deals $ 1 $ damage during the seconds $ 10 $ , $ 11 $ , $ 12 $ and $ 13 $ . In total, the dragon receives $ 10 $ damage.

Monocarp knows that the dragon has $ h $ hit points, and if he deals at least $ h $ damage to the dragon during the battle — he slays the dragon. Monocarp has not decided on the strength of the poison he will use during the battle, so he wants to find the minimum possible value of $ k $ (the number of seconds the poison effect lasts) that is enough to deal at least $ h $ damage to the dragon.

## 说明/提示

In the first example, for $ k=3 $ , damage is dealt in seconds $ [1, 2, 3, 5, 6, 7] $ .

In the second example, for $ k=4 $ , damage is dealt in seconds $ [2, 3, 4, 5, 6, 7, 10, 11, 12, 13] $ .

In the third example, for $ k=1 $ , damage is dealt in seconds $ [1, 2, 4, 5, 7] $ .

## 样例 #1

### 输入

```
4
2 5
1 5
3 10
2 4 10
5 3
1 2 4 5 7
4 1000
3 25 64 1337```

### 输出

```
3
4
1
470```

# AI分析结果

### 题目内容重写
# 中毒匕首

## 题目描述

Monocarp正在玩一款电脑游戏。在游戏中，他的角色需要杀死一条龙。与龙的战斗持续$100^{500}$秒，期间Monocarp用一把中毒匕首攻击龙。第$i$次攻击在战斗开始后的第$a_i$秒开始时进行。匕首本身不会造成伤害，但它会对龙施加中毒效果，在接下来的$k$秒内每秒造成$1$点伤害（从匕首刺中龙的同一秒开始）。然而，如果龙已经中毒，那么匕首会更新中毒效果（即取消当前的中毒效果并施加新的效果）。

例如，假设$k=4$，Monocarp在第$2$、$4$和$10$秒刺中龙。那么中毒效果在第$2$秒开始时施加，并在第$2$和第$3$秒造成$1$点伤害；然后在第$4$秒开始时，中毒效果被重新施加，因此在第$4$、$5$、$6$和$7$秒造成$1$点伤害；最后，在第$10$秒开始时，中毒效果再次被施加，并在第$10$、$11$、$12$和$13$秒造成$1$点伤害。总共，龙受到了$10$点伤害。

Monocarp知道龙有$h$点生命值，如果他在战斗中至少对龙造成$h$点伤害，他就能杀死龙。Monocarp还没有决定在战斗中使用的中毒强度，因此他想找到最小的$k$值（中毒效果持续的秒数），足以对龙造成至少$h$点伤害。

## 说明/提示

在第一个例子中，对于$k=3$，伤害在第$[1, 2, 3, 5, 6, 7]$秒造成。

在第二个例子中，对于$k=4$，伤害在第$[2, 3, 4, 5, 6, 7, 10, 11, 12, 13]$秒造成。

在第三个例子中，对于$k=1$，伤害在第$[1, 2, 4, 5, 7]$秒造成。

## 样例 #1

### 输入

```
4
2 5
1 5
3 10
2 4 10
5 3
1 2 4 5 7
4 1000
3 25 64 1337```

### 输出

```
3
4
1
470```

### 算法分类
二分

### 题解分析与结论
该题的核心思路是通过二分查找来确定最小的$k$值，使得中毒效果对龙造成的总伤害至少为$h$。由于$k$越大，总伤害越大，因此可以使用二分法来快速找到满足条件的最小$k$。

### 所选题解
1. **作者：Tritons (赞：2)**
   - **星级：4**
   - **关键亮点：**
     - 使用二分查找法，思路清晰。
     - 代码简洁，直接计算每次攻击的伤害并累加。
     - 通过二分法快速找到满足条件的最小$k$值。
   - **核心代码：**
     ```cpp
     ll l = 1, r = 1e18;
     while (l <= r) {
         ll mid = l + r >> 1, ans = mid;
         for (int i = 1; i < n; i++) 
             ans += std::min(mid, a[i + 1] - a[i]);
         if (ans < h) l = mid + 1;
         else r = mid - 1;
     }
     printf("%lld\n", r + 1);
     ```

2. **作者：miao5 (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 同样使用二分查找法，思路清晰。
     - 通过`check`函数判断当前$k$值是否满足条件，代码结构清晰。
     - 二分查找的边界处理得当。
   - **核心代码：**
     ```cpp
     bool check(int s){
         int tot=0;
         for(int i=1;i<n;i++){
             if(a[i]+s>a[i+1]) tot+=a[i+1]-a[i];
             else tot+=s;
         }
         tot+=s;
         if(tot>=h) return true;
         else return false;
     }
     ```

3. **作者：DaiRuiChen007 (赞：0)**
   - **星级：4**
   - **关键亮点：**
     - 详细解释了$f(x)$的单调性，证明二分法的正确性。
     - 代码结构清晰，二分查找的实现简洁明了。
     - 通过`judge`函数计算总伤害，逻辑清晰。
   - **核心代码：**
     ```cpp
     inline int judge(int k) {
         int tot=k;
         for(register int i=1;i<n;++i) {
             tot+=min(k,a[i+1]-a[i]);
         }
         return tot;
     }
     ```

### 最优关键思路或技巧
- **二分查找法**：通过二分法快速找到满足条件的最小$k$值，时间复杂度为$O(n \log h)$，效率较高。
- **伤害计算**：每次攻击的伤害为$\min(k, a_{i+1}-a_i)$，最后累加所有攻击的伤害，判断是否大于等于$h$。

### 可拓展之处
- 类似的问题可以通过二分法来解决，尤其是当问题具有单调性时，二分法是一个非常有效的工具。
- 可以扩展到其他类型的伤害计算问题，如不同攻击方式造成的伤害不同，或者伤害随时间变化等。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

### 个人心得
- **调试经历**：在实现二分查找时，注意边界条件的处理，避免死循环或遗漏某些情况。
- **顿悟感想**：二分查找法在处理具有单调性的问题时非常高效，理解其原理并熟练掌握可以解决很多类似的问题。

---
处理用时：43.41秒