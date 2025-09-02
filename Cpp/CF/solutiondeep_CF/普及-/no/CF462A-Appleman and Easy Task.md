# 题目信息

# Appleman and Easy Task

## 题目描述

Toastman came up with a very easy task. He gives it to Appleman, but Appleman doesn't know how to solve it. Can you help him?

Given a $ n×n $ checkerboard. Each cell of the board has either character 'x', or character 'o'. Is it true that each cell of the board has even number of adjacent cells with 'o'? Two cells of the board are adjacent if they share a side.

## 样例 #1

### 输入

```
3
xxo
xox
oxx
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
xxxo
xoxo
oxox
xxxx
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
Toastman 想出了一个非常简单的任务。他把这个任务交给了 Appleman，但 Appleman 不知道如何解决。你能帮他吗？

给定一个 $n×n$ 的棋盘。棋盘的每个格子要么有字符 'x'，要么有字符 'o'。是否每个格子都有偶数个相邻的格子中有 'o' 呢？如果两个格子共用一条边，则称它们相邻。

### 算法分类
枚举

### 综合分析与结论
- **思路对比**：
    - xiaozeyu 题解尝试找规律，认为对称的棋盘满足条件，通过将棋盘字符串倒置后与原图比较来判断。
    - Bla_Bla、西宋太祖、SKTelecomT1_Faker、Protons 题解均采用枚举的方法，遍历棋盘的每个格子，判断其上下左右相邻格子中 'o' 的数量是否为偶数。
- **算法要点**：
    - xiaozeyu 题解利用字符串倒置和比较来判断是否对称。
    - 其他题解通过双重循环遍历棋盘，再对每个格子的四个方向进行判断。
- **解决难点**：
    - xiaozeyu 题解的难点在于规律的总结，实际上其规律并不正确。
    - 其他题解的难点在于边界的处理，要避免数组越界。

### 题解评分
- xiaozeyu：2星。思路错误，虽然尝试找规律但规律总结有误，代码简单但不可行。
- Bla_Bla：3星。思路清晰，代码实现简单直接，但边界处理方式不够严谨。
- 西宋太祖：3星。将判断部分封装成函数，结构更清晰，但边界判断条件较繁琐。
- SKTelecomT1_Faker：3星。思路和代码都比较常规，边界处理存在小问题。
- Protons：3星。提醒了输入时处理换行符的问题，用数组存储方向，代码有一定特色，但也存在边界判断问题。

### 通用建议与扩展思路
- 对于此类棋盘问题，枚举是一种常见的解决方法，关键在于处理好边界情况，避免数组越界。
- 可以使用方向数组（如 `x[4]={0,1,-1,0}, y[4]={1,0,0,-1}`）来简化对相邻格子的判断。
- 同类型题或类似算法套路：可以拓展到判断其他形状的相邻格子（如斜向相邻），或者判断相邻格子满足其他条件的问题。

### 重点代码
```cpp
// Bla_Bla 题解核心代码
for(i=1;i<=n;i++)
{
    for(j=1;j<=n;j++)
    {
        if(a[i-1][j]=='o')m++;
        if(a[i][j-1]=='o')m++;
        if(a[i][j+1]=='o')m++;
        if(a[i+1][j]=='o')m++;
        if(m%2!=0)
        {
            cout<<"NO";
            return 0;
        }
        m=0;
    }
}
```
核心实现思想：通过双重循环遍历棋盘的每个格子，对每个格子的上下左右四个方向进行判断，统计相邻格子中 'o' 的数量，若数量为奇数则输出 `NO` 并结束程序。

### 推荐洛谷题目
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
- P1012 [拼数](https://www.luogu.com.cn/problem/P1012)
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)

### 个人心得摘录与总结
- Bla_Bla：提到要注意 0 也是偶数，自己开始忘了导致对样例一感到困惑。总结：在判断偶数时，要考虑到 0 这个特殊情况。
- Protons：提醒如果用 `scanf("%c",&o);` 进行输入，要在输入二维数组前加一个 `o=getchar()` 以输入换行符，否则读入时会先读入换行符；另外，为了避免读入换行符，二维数组的列还要加一列。总结：在使用 `scanf` 输入字符时，要注意换行符的处理。 

---
处理用时：26.48秒