# 题目信息

# IQ Test

## 题目描述

In the city of Ultima Thule job applicants are often offered an IQ test.

The test is as follows: the person gets a piece of squared paper with a $ 4×4 $ square painted on it. Some of the square's cells are painted black and others are painted white. Your task is to repaint at most one cell the other color so that the picture has a $ 2×2 $ square, completely consisting of cells of the same color. If the initial picture already has such a square, the person should just say so and the test will be completed.

Your task is to write a program that determines whether it is possible to pass the test. You cannot pass the test if either repainting any cell or no action doesn't result in a $ 2×2 $ square, consisting of cells of the same color.

## 说明/提示

In the first test sample it is enough to repaint the first cell in the second row. After such repainting the required $ 2×2 $ square is on the intersection of the $ 1 $ -st and $ 2 $ -nd row with the $ 1 $ -st and $ 2 $ -nd column.

## 样例 #1

### 输入

```
####
.#..
####
....
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
####
....
####
....
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# IQ测试

## 题目描述
在图勒市，求职者经常会被要求进行一项IQ测试。
该测试内容如下：给参与者一张方格纸，上面画有一个4×4的正方形。正方形的一些单元格被涂成黑色，其他单元格被涂成白色。你的任务是最多将一个单元格重新涂成另一种颜色，使得图形中出现一个完全由相同颜色单元格组成的2×2正方形。如果初始图形中已经存在这样的正方形，参与者只需指出，测试即完成。
你的任务是编写一个程序，判断是否有可能通过该测试。如果重新涂任何一个单元格或不采取任何行动都无法得到一个由相同颜色单元格组成的2×2正方形，则无法通过测试。

## 说明/提示
在第一个测试样例中，只需重新涂第二行的第一个单元格。重新涂色后，所需的2×2正方形位于第1行和第2行与第1列和第2列的交叉处。

## 样例 #1
### 输入
```
####
.#..
####
....
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
####
....
####
....
```
### 输出
```
NO
```

### 算法分类
枚举

### 综合分析与结论
这几道题解思路核心都是对4×4矩阵中的2×2子矩阵进行检查判断。不同点在于判断方式和代码实现细节。
 - **MornEveGlow**：通过分析2×2子矩阵黑白格数量差来判断，当差为0时不符合条件，只要有一个2×2子矩阵差不为零，大矩阵就符合条件。代码通过函数将字符转化为数值，对每个2×2子矩阵进行累加判断，思路较为巧妙，代码简洁。
 - **hensier**：将4×4矩阵进行2×2拆分，存入数组，对每个2×2子矩阵判断“.”（或“#”）数量是否为2，不为2则满足条件，最后再判断4个公共块情况。代码实现直观，但略显繁琐。
 - **zhanghengrui**：先判断原矩阵是否有满足条件的2×2矩形，若没有则枚举每一个点，改变该点颜色后再判断是否满足条件。代码逻辑清晰，实现常规。
 - **Suuon_Kanderu**：直接暴力枚举每个2×2的格子，判断是否有三个一样的格子，虽然代码繁琐，但容易理解。
 - **周子衡**：对每个2×2正方形，统计黑格数量，只要黑格数量不为2，就必定可以通过改一个格子满足条件，模拟过程简单直接。
 - **Kuriyama_Mirai**：先写函数判断以某点为左上角的2×2方格是否符合条件，先判断原矩阵是否满足，再改变每个格子颜色后判断，记得改回颜色，逻辑严谨。

### 所选的题解
 - **MornEveGlow（5星）**
    - **关键亮点**：通过分析2×2子矩阵黑白格数量差的特性来判断，思路独特，代码简洁高效。
    - **核心代码**：
```cpp
int Z(char ch){return ch=='.'?-1:1;}
...
int main(){
	...
	for(int i=0;i<3;++i)
	for(int j=0,tmp;j<3;++j)
		flag|=Z(A[i][j])+Z(A[i][j+1])+Z(A[i+1][j])+Z(A[i+1][j+1]);
```
    - **核心思想**：定义函数Z将字符转化为数值，遍历每个2×2子矩阵，将四个对应位置字符转化后累加，只要有一个累加结果不为0（即差不为0），则flag为真，表示满足条件。
 - **zhanghengrui（4星）**
    - **关键亮点**：逻辑清晰，先检查原矩阵，再枚举改变每个点判断，常规思路实现完整。
    - **核心代码**：
```cpp
inline bool ck(int row,int col)//判断以(row,col)为左上角的2*2的矩形是否颜色相同
{
	return pic[row][col]==pic[row][col+1]&&pic[row][col]==pic[row+1][col]&&pic[row][col]==pic[row+1][col+1];
}
inline bool ck()//判断4*4大矩形中是否有满足条件的小矩形
{
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
		{
			if(ck(i,j)) return true;
		}
	}
	return false;
}
int main()
{
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j) scanf(" %c",pic[i]+j);//读入
	}
	if(ck()) printf("YES");//如果不用改就有
	else
	{
		for(int i=0;i<4;++i)
		{
			for(int j=0;j<4;++j)//枚举每一个点
			{
				switch(pic[i][j])
				{
					case '.'://是白
						pic[i][j]='#';//变黑
						if(ck())//判断
						{
							printf("YES");
							goto END;
						}
						pic[i][j]='.';//变回白
						break;
					case '#'://是黑
						pic[i][j]='.';//变白
						if(ck())//判断
						{
							printf("YES");
							goto END;
						}
						pic[i][j]='#';//变回黑
						break;
				}
			}
		}
		printf("NO");
	}
	END:return 0;
}
```
    - **核心思想**：ck函数判断以某点为左上角的2×2矩形是否颜色相同，ck()函数遍历4×4矩阵检查是否有满足条件的小矩形。主函数先读入矩阵，若原矩阵有满足条件的则输出YES，否则枚举每个点改变颜色后判断。
 - **Kuriyama_Mirai（4星）**
    - **关键亮点**：逻辑严谨，先判断原矩阵，再改变每个格子颜色判断且注意还原颜色。
    - **核心代码**：
```cpp
bool judge(int x, int y) {
    if (x < 0 or y < 0 or x > 3 or y > 3)
        return false;
    return map[x][y] and map[x][y + 1] and map[x + 1][y] and map[x + 1][y + 1] or
        not map[x][y] and not map[x][y + 1] and not map[x + 1][y] and not map[x + 1][y + 1];
}

int main() {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++)
            map[i][j] = getchar() == '#';
        getchar();
    }
    
    for (int i = 0; i < 3; i ++)
        for (int j = 0; j < 3; j ++)
            if (judge(i, j)) {
                printf("YES");
                return 0;
            }
    
    for (int i = 0; i < 3; i ++)
        for (int j = 0; j < 3; j ++) {
            map[i][j] = not map[i][j];
            
            if (judge(i, j) or judge(i - 1, j) or judge(i, j - 1) or judge(i - 1, j - 1)) {
                printf("YES");
                return 0;
            }
            
            map[i][j] = not map[i][j];
        }
    
    printf("NO");
    return 0;
} 
```
    - **核心思想**：judge函数判断以某点为左上角的2×2方格是否符合条件。主函数先读入矩阵，遍历判断原矩阵是否有符合条件的，若没有则改变每个格子颜色，判断改变后及其周围2×2方格是否符合条件，记得还原颜色。

### 最优关键思路或技巧
MornEveGlow通过分析2×2子矩阵黑白格数量差的方式，简化了判断逻辑，减少了代码量，这种对问题特性的深入挖掘从而优化算法的思维方式值得学习。

### 拓展思路
此类题目属于矩阵相关的条件判断问题，类似套路有对矩阵进行分块处理、分析子矩阵特性等。同类型题可考虑改变矩阵规模、改变目标子矩阵形状或颜色条件等。

### 洛谷题目推荐
 - P1164 小A点菜：通过枚举菜品组合判断是否满足价格条件，与本题枚举判断思路类似。
 - P1308 统计单词数：在字符串中枚举匹配单词，和本题在矩阵中枚举判断子矩阵有相似之处。
 - P1909 买铅笔：枚举不同包装铅笔购买方案，与本题通过枚举来寻找满足条件的情况类似。 

---
处理用时：80.65秒