# 题目信息

# Perfect Square

## 题目描述

Kristina有一个大小为$n \times n$的矩阵，里面填满了小写拉丁字母。$n$的值是偶数。

她想要改变一些字符，使得她的矩阵变成一个完美方阵。一个矩阵被称为完美方阵，如果它在顺时针旋转90度后仍然保持不变。

这是一个顺时针旋转矩阵90度的例子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1881C/4b38bf84bcab0c377c4a504ebb049a6239821153.png)

在一次操作中，Kristina可以选择任意一个单元格，并将其值替换为字母表中的下一个字符。如果字符等于"z"，则它的值不会改变。

找出使得矩阵成为完美方阵所需的最小操作次数。

例如，如果$4 \times 4$的矩阵如下所示：

$ \begin{matrix} a & b & b & a \\ b & c & \textbf{b} & b \\ b & c & c & b\\ a & b & b & a \\ \end{matrix} $

那么只需要对加粗的字母b进行1次操作即可。

## 说明/提示

第一个测试用例在问题描述中已经解释过了。

## 样例 #1

### 输入

```
5
4
abba
bcbb
bccb
abba
2
ab
ba
6
codefo
rcesco
deforc
escode
forces
codefo
4
baaa
abba
baba
baab
4
bbaa
abba
aaba
abba```

### 输出

```
1
2
181
5
9```

# AI分析结果

【题目内容】
# 完美方阵

## 题目描述

Kristina有一个大小为$n \times n$的矩阵，里面填满了小写拉丁字母。$n$的值是偶数。

她想要改变一些字符，使得她的矩阵变成一个完美方阵。一个矩阵被称为完美方阵，如果它在顺时针旋转90度后仍然保持不变。

这是一个顺时针旋转矩阵90度的例子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1881C/4b38bf84bcab0c377c4a504ebb049a6239821153.png)

在一次操作中，Kristina可以选择任意一个单元格，并将其值替换为字母表中的下一个字符。如果字符等于"z"，则它的值不会改变。

找出使得矩阵成为完美方阵所需的最小操作次数。

例如，如果$4 \times 4$的矩阵如下所示：

$ \begin{matrix} a & b & b & a \\ b & c & \textbf{b} & b \\ b & c & c & b\\ a & b & b & a \\ \end{matrix} $

那么只需要对加粗的字母b进行1次操作即可。

## 说明/提示

第一个测试用例在问题描述中已经解释过了。

## 样例 #1

### 输入

```
5
4
abba
bcbb
bccb
abba
2
ab
ba
6
codefo
rcesco
deforc
escode
forces
codefo
4
baaa
abba
baba
baab
4
bbaa
abba
aaba
abba```

### 输出

```
1
2
181
5
9```

【算法分类】
贪心

【题解分析与结论】
本题的核心思路是通过贪心策略，找到每个旋转对称的四个字符中的最大值，然后计算将其他字符变为该最大值所需的操作次数。所有题解都采用了这一思路，但在实现细节上有所不同。

【精选题解】
1. 作者：liuyi0905 (赞：7)
   - 星级：5
   - 关键亮点：思路清晰，代码简洁，直接计算每个旋转对称的四个字符的最大值，并累加操作次数。
   - 代码核心思想：通过两层循环遍历矩阵的左上角部分，计算每个旋转对称的四个字符的最大值，并累加操作次数。
   - 核心代码片段：
     ```cpp
     for(int i=1;i<=n/2;i++)
         for(int j=1;j<=n/2;j++){
             int maxi=max({a[i][j],a[n-j+1][i],a[j][n-i+1],a[n-i+1][n-j+1]});
             int cnt=a[i][j]+a[n-j+1][i]+a[j][n-i+1]+a[n-i+1][n-j+1];
             ans+=maxi*4-cnt;
         }
     ```

2. 作者：_anll_ (赞：4)
   - 星级：4
   - 关键亮点：通过标记已处理的字符，避免重复计算，代码结构清晰。
   - 代码核心思想：使用标记数组记录已处理的字符，避免重复计算，累加操作次数。
   - 核心代码片段：
     ```cpp
     for(int i=1;i<=n;i++)
         for(int j=1;j<=n;j++){
             if(vu[i][j]==1) continue;
             vu[i][j]=1,vu[n-i+1][n-j+1]=1;
             vu[n-j+1][i]=1,vu[j][n-i+1]=1;
             dy[1]=map[i][j],dy[2]=map[n-i+1][n-j+1];
             dy[3]=map[n-j+1][i],dy[4]=map[j][n-i+1];
             sort(dy+1,dy+5);
             for(int i=1;i<4;i++) ans+=dy[4]-dy[i];
         }
     ```

3. 作者：1234567890sjx (赞：2)
   - 星级：4
   - 关键亮点：代码简洁，直接计算每个旋转对称的四个字符的最大值，并累加操作次数。
   - 代码核心思想：通过两层循环遍历矩阵的左上角部分，计算每个旋转对称的四个字符的最大值，并累加操作次数。
   - 核心代码片段：
     ```cpp
     for(int i=1;i<=n/2;i++)
         for(int j=1;j<=n/2;j++){
             int to=max({a[i][j],a[j][n-i+1],a[n-j+1][i],a[n-i+1][n-j+1]});
             int s=a[i][j]+a[j][n-i+1]+a[n-j+1][i]+a[n-i+1][n-j+1];
             sum+=4*to-s;
         }
     ```

【最优关键思路】
通过贪心策略，找到每个旋转对称的四个字符中的最大值，然后计算将其他字符变为该最大值所需的操作次数。这种方法确保了最小操作次数的计算。

【可拓展之处】
类似的问题可以扩展到其他对称变换，如180度旋转、镜像对称等，思路类似，只需找到对应的对称字符并计算操作次数。

【推荐题目】
1. P1881C - Perfect Square
2. P1881D - Perfect Square
3. P1881E - Perfect Square

---
处理用时：32.63秒