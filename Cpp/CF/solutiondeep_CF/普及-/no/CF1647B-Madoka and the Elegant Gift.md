# 题目信息

# Madoka and the Elegant Gift

## 题目描述

Madoka's father just reached $ 1 $ million subscribers on Mathub! So the website decided to send him a personalized award — The Mathhub's Bit Button!

The Bit Button is a rectangular table with $ n $ rows and $ m $ columns with $ 0 $ or $ 1 $ in each cell. After exploring the table Madoka found out that:

- A subrectangle $ A $ is contained in a subrectangle $ B $ if there's no cell contained in $ A $ but not contained in $ B $ .
- Two subrectangles intersect if there is a cell contained in both of them.
- A subrectangle is called black if there's no cell with value $ 0 $ inside it.
- A subrectangle is called nice if it's black and it's not contained in another black subrectangle.
- The table is called elegant if there are no two nice intersecting subrectangles.

For example, in the first illustration the red subrectangle is nice, but in the second one it's not, because it's contained in the purple subrectangle.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/527c997c3730172d58419587c380220df58d0b35.png)Help Madoka to determine whether the table is elegant.

## 说明/提示

In the second test case the table is not elegant, because the red and the purple subrectangles are nice and intersect.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/274bbf1f30d832fb82dd64034e57adcb4cd9b242.png)In the fourth test case the table is not elegant, because the red and the purple subrectangles are nice and intersect.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/6dc815ec1b802f77b63db126c6131ed14481d644.png)

## 样例 #1

### 输入

```
5
3 3
100
011
011
3 3
110
111
110
1 5
01111
4 5
11111
01010
01000
01000
3 2
11
00
11```

### 输出

```
YES
NO
YES
NO
YES```

# AI分析结果

### 题目内容
# Madoka和优雅的礼物

## 题目描述
Madoka的父亲在Mathub上刚刚达到100万订阅者！因此，该网站决定送给他一个个性化的奖励——Mathub的比特按钮！

比特按钮是一个有n行m列的矩形表格，每个单元格中包含0或1。在探索这个表格后，Madoka发现：
- 若不存在任何一个单元格包含于子矩形A但不包含于子矩形B，则子矩形A包含于子矩形B。
- 若存在一个单元格同时包含于两个子矩形，则这两个子矩形相交。
- 若一个子矩形内部不存在值为0的单元格，则该子矩形称为黑色子矩形。
- 若一个子矩形是黑色的且不包含于另一个黑色子矩形，则该子矩形称为漂亮子矩形。
- 若不存在两个漂亮的相交子矩形，则该表格称为优雅表格。

例如，在第一个图示中，红色子矩形是漂亮的，但在第二个图示中，它不是，因为它包含于紫色子矩形。
![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/527c997c3730172d58419587c380220df58d0b35.png)
请帮助Madoka确定该表格是否优雅。

## 说明/提示
在第二个测试用例中，该表格不优雅，因为红色和紫色子矩形是漂亮的且相交。
![第二个测试用例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/274bbf1f30d832fb82dd64034e57adcb4cd9b242.png)
在第四个测试用例中，该表格不优雅，因为红色和紫色子矩形是漂亮的且相交。
![第四个测试用例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/6dc815ec1b802f77b63db126c6131ed14481d644.png)

## 样例 #1
### 输入
```
5
3 3
100
011
011
3 3
110
111
110
1 5
01111
4 5
11111
01010
01000
01000
3 2
11
00
11
```
### 输出
```
YES
NO
YES
NO
YES
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解的核心思路都是通过判断矩阵中是否存在特定的子矩阵结构，来确定原矩阵是否为优雅矩阵。大部分题解发现若存在两个相交的漂亮子矩形，必然会出现一个$2\times2$的子矩阵中有3个1和1个0的情况，通过遍历矩阵检查这种子矩阵的存在与否来解题。部分题解还从连通块的角度出发，判断连通块是否为矩形来间接判断矩阵是否优雅。

### 所选的题解
- **作者：BMTXLRC（5星）**
  - **关键亮点**：思路清晰，将题目要求巧妙转换为判断矩阵中所有黑色连通块是否都为矩形，进而通过检查矩阵中所有$2\times2$子矩阵内0的个数是否为1来判断，代码简洁明了，可读性高。
  - **重点代码**：
```cpp
int check(int x,int y){
    int ans=0;
    if(a[x][y]=='0') ans++;
    if(a[x+1][y]=='0') ans++;
    if(a[x][y+1]=='0') ans++;
    if(a[x+1][y+1]=='0') ans++;
    return ans;
}
//...
for(register int i=1;i<n;i++){
    if(!ok) break;
    for(register int j=1;j<m;j++){
        int ans=check(i,j);
        if(ans==1){
            ok=false;
            break;
        }
    }
}
```
  - **核心实现思想**：`check`函数用于统计以$(x,y)$为左上角的$2\times2$子矩阵中0的个数，主循环遍历矩阵中所有可能的$2\times2$子矩阵，一旦发现0的个数为1则判定矩阵不优雅。
- **作者：windflower（5星）**
  - **关键亮点**：同样快速抓住问题本质，通过判断是否存在一个$2\cdot 2$的矩形含有三个1和一个0来解题，代码简洁高效，利用字符的ASCII码值简化判断条件。
  - **重点代码**：
```cpp
for(int i=0;i<n-1;i++)
    for(int j=0;j<m-1;j++)
        if(a[i][j]+a[i][j+1]+a[i+1][j]+a[i+1][j+1]-'0'*4==3){
            cout<<"NO"<<endl;
            goto end;
        }
```
  - **核心实现思想**：直接遍历矩阵中所有$2\times2$子矩阵，通过计算四个字符的ASCII码值之和与$4\times'0'$的差值是否为3，来判断该子矩阵是否为含三个1和一个0的特定结构，若是则输出“NO”。
- **作者：Elgo87（4星）**
  - **关键亮点**：从连通块角度出发，通过DFS找到每个连通块的边界，利用二维前缀和快速判断连通块是否为矩形，思路较为新颖，但代码相对复杂。
  - **重点代码**：
```cpp
void dfs(int x, int y, int& sx, int& sy, int& ex, int& ey) {
    sx = min(x, sx);
    sy = min(y, sy);
    ex = max(x, ex);
    ey = max(y, ey);
    for (int i = 0; i < 4; i ++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx > 0 && yy > 0 && xx <= n && yy <= m && vis[xx][yy]) {
            vis[xx][yy] = 0;
            sx = min(xx, sx);
            sy = min(yy, sy);
            ex = max(xx, ex);
            ey = max(yy, ey);
            dfs(xx, yy, sx, sy, ex, ey);
        }
    }
}
//...
for (int i = 1; i <= n; i ++) {
    for (int j = 1; j <= m; j ++) {
        int sx=1e9, ex=-1e9, sy=1e9, ey=-1e9;
        if (vis[i][j]) {
            dfs(i, j, sx, sy, ex, ey);
            if ((ey-sy+1)*(ex-sx+1)!= s[ex][ey] - s[ex][sy-1] - s[sx-1][ey] + s[sx-1][sy-1]) { 
                puts("NO");
                return ;
            }
        }
    }
}
```
  - **核心实现思想**：`dfs`函数用于标记并确定连通块的边界$(sx,sy,ex,ey)$，主循环遍历矩阵找到所有连通块，通过比较连通块面积与对应二维前缀和区域的值，判断连通块是否为矩形，若不是则输出“NO”。

### 最优关键思路或技巧
通过观察发现判断是否存在两个相交的漂亮子矩形，等价于判断矩阵中是否存在一个$2\times2$的子矩阵含有三个1和一个0，这种将复杂问题简单化的思维方式是解题关键。利用字符ASCII码值简化判断条件，以及使用二维前缀和优化连通块判断等代码实现技巧也值得学习。

### 可拓展思路
此类题目属于矩阵性质判断类型，类似套路是通过观察目标性质在矩阵局部的特征表现，将对整体复杂结构的判断转化为对局部小结构的判断。还可以拓展到更高维度的数组或者带权矩阵等情况，解题思路依然是寻找特征子结构。

### 推荐题目
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：通过模拟操作过程，判断最终灯的状态，考察对简单逻辑的模拟实现。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔的价格和数量，选择最优购买方案，属于简单的模拟与贪心结合的题目。
- [P5733 闰年判断](https://www.luogu.com.cn/problem/P5733)：按照闰年的判断规则，对输入年份进行判断，是基础的模拟题目，考察对条件判断的运用。 

---
处理用时：75.15秒