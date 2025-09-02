# 题目信息

# [NWRRC 2015] Black and White

## 题目描述



The jury has a great artistic idea -- to create a rectangular panel out of a huge pile of black and white squares of the same size. The panel should have exactly $b 4-connected$ areas made of black tiles, and $w 4-connected$ areas made of white tiles.

Remember, a $4-connected$ area of some color is a maximal set of the panel tiles such that:

any two tiles of the area share the same color;

for any two tiles of the area there is a tile sequence connecting them, such that any two consecutive tiles of the sequence share a common side.

In addition to the artistic idea, the jury has already developed a program that produces design of the panel. But since this problem is about art, any new solution is extremely important for the jury.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
2 3
```

### 输出

```
6 7
@@@@@@@
@.@@@@@
@@...@@
@@@@@@@
.......
@@@@@@@
```

# AI分析结果

### 算法分类
构造

### 综合分析与结论
本题要求构造一个黑白矩阵，使得矩阵内恰有 $b$ 个黑色连通块和 $w$ 个白色连通块。各题解主要通过构造特定的矩阵模式来满足题目要求，核心思路是通过交替排列黑白块，并根据 $b$ 和 $w$ 的大小关系进行调整。题解中的难点在于如何通过简单的构造规则来确保连通块的数量准确无误。

### 所选题解
1. **作者：pythoner713 (4星)**
   - **关键亮点**：通过分块构造，上端为交替黑白条纹，下端为黑块包围的白块，确保连通块数量准确。代码简洁，逻辑清晰。
   - **代码核心思想**：
     ```cpp
     for(int i = 1; i < b; i++){
         cout << (t ? "...\n@@@\n" : "@@@\n...\n");
     }
     for(int i = 1; i <= (w - b) * 2 + 3; i++){
         if(i & 1) cout << (t ? "...\n" : "@@@\n");
         else cout << (t ? ".@.\n" : "@.@\n");
     }
     ```
   - **个人心得**：通过交换 $b$ 和 $w$ 并反色输出，简化了代码实现。

2. **作者：gaoyangyang (4星)**
   - **关键亮点**：将问题分解为构建矩阵和输出规格两部分，通过简单的循环和条件判断实现构造。代码结构清晰，易于理解。
   - **代码核心思想**：
     ```cpp
     while (w!=0 or b!=0){
         if (b>w){
             while (w>1 and b>1){
                 cout<<"@@"<<endl;
                 b--;
                 cout<<".."<<endl;
                 w--;
             }
             if (w==1){
                 w--;
                 cout<<"@@"<<endl;
                 while (b!=0){
                     cout<<".@"<<endl;
                     cout<<"@@"<<endl;
                     b--;
                 }
             }        
         }
     }
     ```
   - **个人心得**：通过将问题分解为简单部分，逐步构建矩阵，确保连通块数量准确。

3. **作者：ycy1124 (4星)**
   - **关键亮点**：通过分组构造矩阵，利用多组矩阵上下相连来补差，确保连通块数量准确。代码逻辑清晰，构造方法巧妙。
   - **代码核心思想**：
     ```cpp
     while(w){
         if(w>=2){
             cout<<ch[1]<<ch[0]<<ch[1]<<'\n';
             cout<<ch[0]<<ch[0]<<ch[0]<<'\n';
             w-=2;
         }
         else{
             cout<<ch[1]<<ch[0]<<ch[0]<<'\n';
             cout<<ch[0]<<ch[0]<<ch[0]<<'\n';
             w--;
         }
     }
     ```
   - **个人心得**：通过分组构造矩阵，利用多组矩阵上下相连来补差，确保连通块数量准确。

### 最优关键思路或技巧
通过交替排列黑白块，并根据 $b$ 和 $w$ 的大小关系进行调整，确保连通块数量准确。分块构造和分组构造是两种有效的构造方法，能够简化代码实现并确保准确性。

### 可拓展之处
类似构造题可以通过分块或分组构造来简化问题，确保构造的准确性和代码的简洁性。例如，构造特定模式的矩阵或图形时，可以通过分块或分组来实现。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：19.60秒