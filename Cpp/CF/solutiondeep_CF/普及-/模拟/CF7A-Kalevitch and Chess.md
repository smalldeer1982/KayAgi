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

### 题目内容翻译
# Kalevitch与国际象棋

## 题目描述
著名的伯兰画家Kalevitch喜欢震撼公众。他最近的痴迷之一是国际象棋。一千多年来，人们一直在无趣、单调的棋盘上玩这个古老的游戏。Kalevitch决定终结这一传统，为国际象棋棋盘引入一种新的理念。

和以前一样，国际象棋棋盘是一个由方格组成的正方形棋盘，方格排列成8×8的网格，每个方格被涂成黑色或白色。Kalevitch建议按照以下方式绘制棋盘：应选择一行或一列共8个方格，将其涂成黑色。最初，整个棋盘都是白色的，可以按照上述方式进行一次或多次涂色。允许对方格进行多次涂色，但第一次涂色后，方格的颜色不会再改变，始终保持黑色。Kalevitch绘制棋盘很整齐，仅通过单个方格无法判断它是被垂直还是水平涂色的。

Kalevitch希望这样的棋盘能受到欢迎，这样他就会接到绘制棋盘的委托，从而确保自己有一个舒适的晚年。客户会告诉他他们想要什么样的棋盘，而画家会绘制一个满足客户需求的白色棋盘。

不言而喻，在这样的生意中，一切都要精打细算——对于每一个委托，他都想知道为了满足客户的需求，他最少需要涂多少次。你被要求帮助Kalevitch完成这项任务。

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
- **思路对比**：各位大神的题解思路基本一致，都是采用贪心策略，即如果某行或某列全为'B'，则对其进行涂色操作，最后统计操作次数。其中Tune_、呵呵侠和_Legacy三位作者都是分别对行和列进行遍历判断；而char32_t作者主要先对行进行判断，同时记录每行中'B'的最小数量。
- **算法要点**：核心在于遍历棋盘的每一行和每一列，判断是否全为'B'，若是则增加操作次数。最后需要对全为'B'的情况进行特判，因为此时若分别统计行和列的操作次数会得到16次，但实际只需8次。
- **解决难点**：主要难点在于对全为'B'的情况进行特判，避免操作次数统计错误。

### 所选题解
- **作者：Tune_ (5星)**
    - **关键亮点**：思路清晰，代码简洁易懂，直接对行和列进行遍历判断，最后进行特判。
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
    for(int i=0;i<8;i++)//行
    {
        bool f=1;
        for(int j=0;j<8;j++)
        {
            if(a[i][j]!='B')
                f=0;
        }
        if(f)
            ans++;
    }
    for(int i=0;i<8;i++)//列
    {
        bool f=1;
        for(int j=0;j<8;j++)
        {
            if(a[j][i]!='B')
                f=0;
        }
        if(f)
            ans++;
    }
    if(ans==16)//特判
        ans=8;
    cout<<ans;
    return 0;
}
```
- **作者：呵呵侠 (4星)**
    - **关键亮点**：代码注释详细，便于理解，同样是分别对行和列进行判断，最后特判。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
char a[8][8];
int main()
{
    for(int i = 0; i <= 7; i++)
        for(int j = 0; j <= 7; j++)
            cin >> a[i][j];//输入
    int ans = 0;
    for(int i = 0; i <= 7; i++)//判断行
    {
        bool flag = true;//判断一行是不是都是B的判断器，赋值为true
        for(int j = 0; j <= 7; j++)
        {
            if(a[i][j]!= 'B')//如果不是B
                flag = false;//判断器值为false
        }
        if(flag == true)//如果这一行都是B
            ans++;//染色次数增加1
    }
    for(int i = 0; i <= 7; i++)//判断列
    {
        bool flag = true;//判断一列是不是都是B的判断器，赋值为true
        for(int j = 0; j <= 7; j++)
        {
            if(a[j][i]!= 'B')//如果不是B
                flag = false;//判断器值为false
        }
        if(flag == true)//如果这一列都是B
            ans++;//染色次数增加1
    }
    if(ans == 16) //特判，如果8行8列都是B，那么其实只要8次操作就够了
        ans = 8;
    cout << ans;
    return 0;
}
```
- **作者：_Legacy (4星)**
    - **关键亮点**：对输入部分进行了详细处理，思路清晰，同样有行和列的判断以及特判。
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
- **贪心策略**：优先选择全为'B'的行或列进行涂色，因为这样能在最少的操作次数内达到目标。
- **特判处理**：对全为'B'的情况进行特判，避免操作次数统计错误。

### 可拓展之处
同类型题目可能会改变棋盘的大小、涂色规则或增加其他限制条件，但核心思路仍然是通过遍历和判断来确定最少操作次数。可以采用类似的贪心策略，优先选择收益最大的操作。

### 洛谷相似题目推荐
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)
- [P1094 [NOIP2007 普及组] 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录与总结
无。

---
处理用时：37.88秒