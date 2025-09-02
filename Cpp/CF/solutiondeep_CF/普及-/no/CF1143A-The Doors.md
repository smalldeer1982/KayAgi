# 题目信息

# The Doors

## 题目描述

Three years have passes and nothing changed. It is still raining in London, and Mr. Black has to close all the doors in his home in order to not be flooded. Once, however, Mr. Black became so nervous that he opened one door, then another, then one more and so on until he opened all the doors in his house.

There are exactly two exits from Mr. Black's house, let's name them left and right exits. There are several doors in each of the exits, so each door in Mr. Black's house is located either in the left or in the right exit. You know where each door is located. Initially all the doors are closed. Mr. Black can exit the house if and only if all doors in at least one of the exits is open. You are given a sequence in which Mr. Black opened the doors, please find the smallest index $ k $ such that Mr. Black can exit the house after opening the first $ k $ doors.

We have to note that Mr. Black opened each door at most once, and in the end all doors became open.

## 说明/提示

In the first example the first two doors are from the left exit, so when Mr. Black opened both of them only, there were two more closed door in the left exit and one closed door in the right exit. So Mr. Black wasn't able to exit at that moment.

When he opened the third door, all doors from the right exit became open, so Mr. Black was able to exit the house.

In the second example when the first two doors were opened, there was open closed door in each of the exit.

With three doors opened Mr. Black was able to use the left exit.

## 样例 #1

### 输入

```
5
0 0 1 0 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 0 0 1
```

### 输出

```
3
```

# AI分析结果



# 中文题目翻译

# The Doors

## 题目描述

三年过去了，一切如故。伦敦依然在下雨，布莱克先生必须关掉家里所有的门以防被淹。然而有一次，布莱克先生非常紧张，他逐一打开所有房门直到所有门都处于开启状态。

房屋有两个出口（左出口和右出口），每个门属于其中一个出口。给定开门的顺序（0表示左出口的门，1表示右出口的门），求最早满足任意一个出口所有门都打开的开门次数k。

初始所有门关闭，开门顺序保证每个门恰好打开一次，最终所有门都开启。

## 说明/提示

第一个样例中，前两扇门属于左出口，但此时左出口仍有未开启的门。当开启第三扇右门后，右出口所有门已开启。

第二个样例中，前两扇门开启后左右出口均有未开启的门，第三扇左门开启后左出口全开。

## 样例 #1

### 输入

```
5
0 0 1 0 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 0 0 1
```

### 输出

```
3
```

---

**算法分类**  
模拟

---

**题解分析与结论**  
所有题解核心思路为：找到最后出现的0和1的位置，取最小值。但部分解法因未处理全0/全1场景存在漏洞。最优解法应通过统计总数或正确初始化来覆盖所有情况。

**精选题解**  
1. **作者：codemap（4星）**  
   **关键亮点**：通过统计总数实现精确判断，正确处理所有边界情况。  
   **核心思路**：首次遍历统计左右门总数，二次遍历时实时统计已开启数量，当某一方全开时立即输出。  
   ```cpp
   int main() {
       int n, l=0, r=0, l1=0, r1=0;
       bool a[200001];
       cin >> n;
       for(int i=1; i<=n; i++) {
           cin >> a[i];
           if(!a[i]) l++;
           else r++;
       }
       for(int i=1; i<=n; i++) {
           if(!a[i]) l1++;
           else r1++;
           if(l1==l || r1==r) {
               cout << i;
               break;
           }
       }
       return 0;
   }
   ```

2. **作者：Creator_157（3星）**  
   **核心思路**：记录最后出现的0和1的位置，取最小值。  
   **不足**：未处理全0/全1的极端情况（需修正初始化逻辑）。  
   **优化建议**：初始化最后位置为-1，并增加存在性判断。  
   ```cpp
   int main() {
       int n, a, l1=-1, l2=-1;
       cin >> n;
       for(int i=1; i<=n; i++) {
           cin >> a;
           if(a==0) l1 = i;
           else l2 = i;
       }
       if(l1 == -1) cout << l2;
       else if(l2 == -1) cout << l1;
       else cout << min(l1, l2);
       return 0;
   }
   ```

**关键技巧**  
- **极值记录法**：通过单次遍历记录关键极值（如最后出现位置），时间复杂度O(n)。  
- **双计数验证**：先统计总数再验证当前进度，确保逻辑完备性。

**拓展建议**  
类似问题可转化为极值追踪或状态验证，如[CF978B File Name](https://www.luogu.com.cn/problem/CF978B)需要记录连续字符出现次数。

**推荐题目**  
1. P1143 进制转换（极值应用）  
2. CF978B File Name（状态验证）  
3. P1598 垂直柱状图（字符统计）

---
处理用时：167.68秒