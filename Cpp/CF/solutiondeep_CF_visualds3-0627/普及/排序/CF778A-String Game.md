# 题目信息

# String Game

## 题目描述

Little Nastya has a hobby, she likes to remove some letters from word, to obtain another word. But it turns out to be pretty hard for her, because she is too young. Therefore, her brother Sergey always helps her.

Sergey gives Nastya the word $ t $ and wants to get the word $ p $ out of it. Nastya removes letters in a certain order (one after another, in this order strictly), which is specified by permutation of letters' indices of the word $ t $ : $ a_{1}...\ a_{|t|} $ . We denote the length of word $ x $ as $ |x| $ . Note that after removing one letter, the indices of other letters don't change. For example, if $ t= $ "nastya" and $ a=[4,1,5,3,2,6] $ then removals make the following sequence of words "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya".

Sergey knows this permutation. His goal is to stop his sister at some point and continue removing by himself to get the word $ p $ . Since Nastya likes this activity, Sergey wants to stop her as late as possible. Your task is to determine, how many letters Nastya can remove before she will be stopped by Sergey.

It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

## 说明/提示

In the first sample test sequence of removing made by Nastya looks like this:

"ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba"

Nastya can not continue, because it is impossible to get word "abb" from word "ababcba".

So, Nastya will remove only three letters.

## 样例 #1

### 输入

```
ababcba
abb
5 3 4 1 7 6 2
```

### 输出

```
3```

## 样例 #2

### 输入

```
bbbabb
bb
1 6 3 4 2 5
```

### 输出

```
4```

# AI分析结果



---

## 算法分类
**二分答案**

---

## 题解思路与难点分析

### 核心算法流程
题目要求在特定删除顺序下，找到**最大可删除次数**使得剩余字符串仍能包含目标串 $p$。核心思路为：
1. **二分答案**：枚举可删除次数，验证删除后的字符串是否包含 $p$。
2. **验证函数 (check)**：利用双指针法判断剩余字符是否有序包含目标串。

### 解决难点
1. **动态索引处理**：删除操作后原字符串索引不变，需正确标记被删除的位置。
2. **高效验证**：直接遍历原字符串并跳过已删除字符，避免生成新字符串的开销。

### 算法对比
- **排序法**：部分题解收集未被删字符的索引后排序，时间复杂度 $O(n \log n)$。
- **标记数组法**：直接标记被删除的位置，遍历原字符串时跳过，时间复杂度 $O(n)$，效率更优。

---

## 题解评分（≥4星）

### ⭐⭐⭐⭐ Adolfo_North 的题解
- **亮点**：通过映射数组记录删除顺序，避免显式生成新字符串。
- **代码可读性**：结构清晰，正确处理了输入索引的偏移问题。
- **核心代码**：
  ```cpp
  bool check(int m){
      memset(f,0,sizeof f);
      for(int i=1;i<=m;i++) f[b[i]-1]=1; // 处理索引偏移
      int cnt=0;
      for(int i=0;i<sizea;i++){
          if(!f[i]&&a[i]==t[cnt]) cnt++;
          if(cnt==sizet) return 1;
      }
      return 0;
  }
  ```

### ⭐⭐⭐⭐ Uuuuuur_ 的题解
- **亮点**：直接在原字符串中跳过删除位，双指针逻辑简洁。
- **调试提示**：注释明确说明 `pos` 的边界条件。
- **核心代码**：
  ```cpp
  bool check(int x) {
      string now = p;
      for (int i=0; i<x; i++) now[a[i]-1] = ' '; // 标记删除位
      int pos=0;
      for (char c : now) {
          if (c == t[pos]) pos++;
          if (pos == t.size()) return true;
      }
      return false;
  }
  ```

### ⭐⭐⭐⭐ DecemberFox 的题解
- **亮点**：利用删除次序映射，无需生成中间字符串。
- **时间复杂度**：直接遍历原字符串，复杂度 $O(n)$。
- **核心代码**：
  ```cpp
  bool check(int pos) {
      int i,j=0,l=p.size(),r=t.size();
      for(i=0; i<r; ++i) {
          while(j<l && (p[j]!=t[i] || del[j+1]<=pos)) ++j; // 跳过不匹配或已删除位
          if(j==l) return false;
          ++j;
      }
      return true;
  }
  ```

---

## 最优思路与技巧提炼

### 关键步骤
1. **二分框架**：设可删除次数的上下界为 $[0, |t| - |p|]$。
2. **标记删除位**：用数组记录每个位置是否被删除。
3. **双指针匹配**：遍历原字符串，跳过删除位，匹配目标串。

### 代码实现
```cpp
bool check(int mid, vector<int>& del_order, string& t, string& p) {
    vector<bool> deleted(t.size(), false);
    for (int i=0; i<mid; i++) 
        deleted[del_order[i]-1] = true; // 处理1-based输入
    int j=0;
    for (int i=0; i<t.size() && j<p.size(); i++) {
        if (!deleted[i] && t[i] == p[j]) j++;
    }
    return j == p.size();
}
```

---

## 相似题目推荐
1. **P2678 跳石头**：二分最小跳跃距离。
2. **P1182 数列分段 II**：二分最大子段和。
3. **CF1117C Magic Ship**：二分天数验证路径可行性。

---

## 可视化与算法演示

### 动画设计
1. **二分过程**：动态展示左右边界变化，高亮当前 `mid`。
2. **删除标记**：用红色方块标记被删除的字符位置。
3. **双指针匹配**：
   - 绿色指针在目标串上移动。
   - 蓝色指针在原字符串上跳跃式移动，跳过红色标记位。

### 复古像素风格
- **颜色方案**：8-bit 调色板，红色（#FF0000）标记删除位，绿色（#00FF00）匹配成功。
- **音效**：
  - 删除标记时播放短促“哔”声。
  - 匹配成功时播放上升音阶。

### 交互控制
- **步进按钮**：单步执行二分和匹配过程。
- **速度调节**：滑动条控制动画速度（1x~5x）。
- **自动演示**：AI自动完成二分流程，按空格键暂停/继续。

---

## 个人心得摘录
> “在调试时发现输入索引是1-based的，必须减1才能正确标记原字符串位置。” —— Adolfo_North  
> **总结**：处理输入时需注意题目中的索引起始约定，避免差一错误。

---
处理用时：85.78秒