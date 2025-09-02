# 题目信息

# Kalevitch and Chess

## 题目描述

A famous Berland's painter Kalevitch likes to shock the public. One of his last obsessions is chess. For more than a thousand years people have been playing this old game on uninteresting, monotonous boards. Kalevitch decided to put an end to this tradition and to introduce a new attitude to chessboards.

As before, the chessboard is a square-checkered board with the squares arranged in a $ 8×8 $ grid, each square is painted black or white. Kalevitch suggests that chessboards should be painted in the following manner: there should be chosen a horizontal or a vertical line of 8 squares (i.e. a row or a column), and painted black. Initially the whole chessboard is white, and it can be painted in the above described way one or more times. It is allowed to paint a square many times, but after the first time it does not change its colour any more and remains black. Kalevitch paints chessboards neatly, and it is impossible to judge by an individual square if it was painted with a vertical or a horizontal stroke.

Kalevitch hopes that such chessboards will gain popularity, and he will be commissioned to paint chessboards, which will help him ensure a comfortable old age. The clients will inform him what chessboard they want to have, and the painter will paint a white chessboard meeting the client's requirements.

It goes without saying that in such business one should economize on everything — for each commission he wants to know the minimum amount of strokes that he has to paint to fulfill the client's needs. You are asked to help Kalevitch with this task.

## 样例 #1

### 输入

```
WWWBWWBW
BBBBBBBB
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
```

### 输出

```
3
```

## 样例 #2

### 输入

```
WWWWWWWW
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
```

### 输出

```
1
```

# AI分析结果

### 题目翻译
# Kalevitch与国际象棋

## 题目描述
著名的伯兰画家Kalevitch喜欢震撼公众。他最近的痴迷之一是国际象棋。一千多年来，人们一直在无趣、单调的棋盘上玩这个古老的游戏。Kalevitch决定结束这一传统，为国际象棋棋盘引入一种新的观念。

和以前一样，国际象棋棋盘是一个由方格组成的正方形棋盘，方格排列成8×8的网格，每个方格被涂成黑色或白色。Kalevitch建议按照以下方式绘制国际象棋棋盘：应选择一行或一列的8个方格（即一行或一列），并将其涂成黑色。最初，整个棋盘都是白色的，可以按照上述方式进行一次或多次涂色。允许对方格进行多次涂色，但第一次涂色后，其颜色不会再改变，仍然是黑色。Kalevitch绘制棋盘很整齐，仅通过单个方格无法判断它是用垂直还是水平笔画涂的。

Kalevitch希望这样的棋盘能受到欢迎，这样他就会接到绘制棋盘的委托，这将有助于他安享晚年。客户会告诉他他们想要什么样的棋盘，画家会绘制一个满足客户要求的白色棋盘。

不言而喻，在这样的生意中，一切都要精打细算——对于每一个委托，他都想知道为了满足客户的需求，他至少需要涂多少次。你被要求帮助Kalevitch完成这项任务。

## 样例 #1
### 输入
```
WWWBWWBW
BBBBBBBB
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
```
### 输出
```
3
```

## 样例 #2
### 输入
```
WWWWWWWW
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
```
### 输出
```
1
```

### 综合分析与结论
- **思路对比**：四位作者的核心思路一致，均是判断棋盘的行和列是否全为'B'，若是则计数，最后对全为'B'的情况进行特判。
- **算法要点**：遍历棋盘的行和列，检查是否全为'B'，并对全黑棋盘的计数结果进行修正。
- **解决难点**：关键在于判断行和列是否全为'B'，以及处理全黑棋盘时避免重复计数。

### 所选题解
- **作者：Tune_ (赞：19)，5星**
    - **关键亮点**：思路清晰，代码简洁易读，注释详细。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[8][8];
int main()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            cin>>a[i][j];
    int ans=0;
    for(int i=0;i<8;i++){
        bool f=1;
        for(int j=0;j<8;j++){
            if(a[i][j]!='B')
                f=0;
        }
        if(f)
            ans++;
    }
    for(int i=0;i<8;i++){
        bool f=1;
        for(int j=0;j<8;j++){
            if(a[j][i]!='B')
                f=0;
        }
        if(f)
            ans++;
    }
    if(ans==16)
        ans=8;
    cout<<ans;
    return 0;
}
```
- **作者：呵呵侠 (赞：2)，4星**
    - **关键亮点**：思路清晰，使用布尔变量作为判断器，代码可读性高。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
char a[8][8];
int main()
{
    for(int i = 0; i <= 7; i++)
        for(int j = 0; j <= 7; j++)
            cin >> a[i][j];
    int ans = 0;
    for(int i = 0; i <= 7; i++){
        bool flag = true;
        for(int j = 0; j <= 7; j++){
            if(a[i][j]!= 'B')
                flag = false;
        }
        if(flag == true)
            ans++;
    }
    for(int i = 0; i <= 7; i++){
        bool flag = true;
        for(int j = 0; j <= 7; j++){
            if(a[j][i]!= 'B')
                flag = false;
        }
        if(flag == true)
            ans++;
    }
    if(ans == 16) 
        ans = 8;
    cout << ans;
    return 0;
}
```
- **作者：_Legacy (赞：1)，4星**
    - **关键亮点**：对输入和判断过程有详细注释，逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    char a[9][9],b[9];
    int t,ans=0;
    for(int i=0;i<8;i++){
        cin >> b;
        for(int j=0;j<8;j++){
            a[i][j]=b[j];
        }
    }
    for(int i=0;i<8;i++){
        t=1;
        for(int j=0;j<8;j++){
            if(a[i][j]!='B'){
                t=0;
                break;
            }
        }
        if(t){
            ans++;
        } 
    }
    for(int i=0;i<8;i++){
        t=1;
        for(int j=0;j<8;j++){
            if(a[j][i]!='B'){
                t=0;
                break;
            }
        }
        if(t){
            ans++;
        } 
    }
    if(ans==16) ans=8;
    cout << ans;
} 
```

### 最优关键思路或技巧
- 采用贪心策略，优先选择全为'B'的行或列进行涂色。
- 对全黑棋盘的情况进行特判，避免重复计数。

### 可拓展之处
同类型题目可能会改变棋盘大小、涂色规则或增加其他限制条件，但核心思路仍然是判断特定区域是否满足某种条件，并进行相应计数。

### 洛谷相似题目推荐
- P1007 独木桥
- P1223 排队接水
- P1090 合并果子

### 个人心得
题解中未包含个人心得内容。

---
处理用时：30.96秒