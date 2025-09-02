# 题目信息

# [NWRRC 2015] Lucky Chances

## 题目描述



Lucky Chances is a lottery game. Each lottery ticket has a play field and a scratch area. The play field is a rectangular $r \times c$ field filled with numbers. The scratch area hides row and column numbers that specify the bet cell.

There are four possible winning directions: up, down, left and right. You win a direction if all numbers in this direction from the bet cell are strictly less than a number in the bet cell. And if the bet cell is on the edge of the grid, you win the corresponding direction automatically!

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11477/1.png)

Unscratched ticket

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11477/2.png)

Scratched ticket $1$

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11477/3.png)

Scratched ticket $2$

Larry wants to choose the ticket that has maximum total number of winning directions for all possible bet cells. Write a program that determines this number for the given grid.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
3 4
5 3 9 10
1 8 8 2
4 3 4 3
```

### 输出

```
25
```

# AI分析结果

### 算法分类
**模拟**

### 题解分析与结论
所有题解的核心思路都是通过枚举每个单元格，并检查其四个方向（上、下、左、右）的所有元素是否严格小于当前单元格的值。如果满足条件，则累加获胜方向的数量。这种思路属于典型的模拟算法，直接按照题目要求进行遍历和判断。

### 题解评分与亮点
1. **作者：柠檬布丁吖**  
   - **星级：4**  
   - **亮点**：代码结构清晰，注释详细，变量命名合理，适合初学者理解。  
   - **核心代码**：
     ```cpp
     for(int i=1; i<=n; i++) {
         for(int j=1; j<=m; j++) {
             bool k=false;
             for(int l=i-1; l>=1; l--) {
                 if(Map[l][j]>=Map[i][j]) {
                     k=true;
                     break;
                 }
             }
             if(k==false) ans++;
         }
     }
     ```

2. **作者：Eason_AC**  
   - **星级：4**  
   - **亮点**：代码简洁，逻辑清晰，使用了宏定义简化代码，适合有一定基础的读者。  
   - **核心代码**：
     ```cpp
     F(i, 1, r) F(j, 1, c) {
         int flag = 1;
         R(k, i - 1, 1) if(a[k][j] >= a[i][j]) {flag = 0; break;}
         ans += flag;
     }
     ```

3. **作者：Gaogao2011**  
   - **星级：4**  
   - **亮点**：代码结构清晰，注释详细，适合初学者理解。  
   - **核心代码**：
     ```cpp
     for(int i=1; i<=r; i++) {
         for(int j=1; j<=c; j++) {
             bool flag = true;
             for(int k=i+1; k<=r; k++) {
                 if(a[k][j] >= a[i][j]) {
                     flag = false;
                     break;
                 }
             }
             if(flag) sum++;
         }
     }
     ```

### 最优关键思路
- **枚举与模拟**：通过枚举每个单元格，并模拟四个方向的检查过程，确保所有元素严格小于当前单元格的值。
- **边界处理**：无需特殊处理边界，因为遍历时会自动停止在边界处。

### 拓展与举一反三
- **类似题目**：
  1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 模拟题，考察二维数组的遍历与条件判断。
  2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042) - 模拟题，考察字符串处理与条件判断。
  3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056) - 模拟题，考察二维数组的遍历与条件判断。

### 个人心得摘录
- **柠檬布丁吖**：建议避免使用与STL库冲突的变量名，如`Map`，以防止混淆。
- **Eason_AC**：使用宏定义简化代码，提高了代码的可读性和编写效率。
- **Gaogao2011**：强调了边界处理的简化，使得代码更加简洁。

---
处理用时：25.08秒