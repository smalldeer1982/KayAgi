# 题目信息

# Sofa Thief

## 题目描述

Yet another round on DecoForces is coming! Grandpa Maks wanted to participate in it but someone has stolen his precious sofa! And how can one perform well with such a major loss?

Fortunately, the thief had left a note for Grandpa Maks. This note got Maks to the sofa storehouse. Still he had no idea which sofa belongs to him as they all looked the same!

The storehouse is represented as matrix $ n×m $ . Every sofa takes two neighbouring by some side cells. No cell is covered by more than one sofa. There can be empty cells.

Sofa $ A $ is standing to the left of sofa $ B $ if there exist two such cells $ a $ and $ b $ that  $ x_{a}&lt;x_{b} $ , $ a $ is covered by $ A $ and $ b $ is covered by $ B $ . Sofa $ A $ is standing to the top of sofa $ B $ if there exist two such cells $ a $ and $ b $ that  $ y_{a}&lt;y_{b} $ , $ a $ is covered by $ A $ and $ b $ is covered by $ B $ . Right and bottom conditions are declared the same way.

Note that in all conditions $ A≠B $ . Also some sofa $ A $ can be both to the top of another sofa $ B $ and to the bottom of it. The same is for left and right conditions.

The note also stated that there are $ cnt_{l} $ sofas to the left of Grandpa Maks's sofa, $ cnt_{r} $ — to the right, $ cnt_{t} $ — to the top and $ cnt_{b} $ — to the bottom.

Grandpa Maks asks you to help him to identify his sofa. It is guaranteed that there is no more than one sofa of given conditions.

Output the number of Grandpa Maks's sofa. If there is no such sofa that all the conditions are met for it then output -1.

## 说明/提示

Let's consider the second example.

- The first sofa has $ 0 $ to its left, $ 2 $ sofas to its right ( $ (1,1) $ is to the left of both $ (5,5) $ and $ (5,4) $ ), $ 0 $ to its top and $ 2 $ to its bottom (both $ 2 $ nd and $ 3 $ rd sofas are below).
- The second sofa has $ cnt_{l}=2 $ , $ cnt_{r}=1 $ , $ cnt_{t}=2 $ and $ cnt_{b}=0 $ .
- The third sofa has $ cnt_{l}=2 $ , $ cnt_{r}=1 $ , $ cnt_{t}=1 $ and $ cnt_{b}=1 $ .

So the second one corresponds to the given conditions.

In the third example

- The first sofa has $ cnt_{l}=1 $ , $ cnt_{r}=1 $ , $ cnt_{t}=0 $ and $ cnt_{b}=1 $ .
- The second sofa has $ cnt_{l}=1 $ , $ cnt_{r}=1 $ , $ cnt_{t}=1 $ and $ cnt_{b}=0 $ .

And there is no sofa with the set $ (1,0,0,0) $ so the answer is -1.

## 样例 #1

### 输入

```
2
3 2
3 1 3 2
1 2 2 2
1 0 0 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
10 10
1 2 1 1
5 5 6 5
6 4 5 4
2 1 2 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2
2 2
2 1 1 1
1 2 2 2
1 0 0 0
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 沙发大盗

## 题目描述
又一轮DecoForces竞赛即将来临！马克斯爷爷本想参加，但有人偷走了他珍贵的沙发！遭受如此重大损失，他怎么能正常发挥呢？

幸运的是，小偷给马克斯爷爷留了张纸条。这张纸条指引马克斯来到了沙发仓库。然而，所有沙发看起来都一模一样，他根本不知道哪个是自己的！

仓库用一个 \( n×m \) 的矩阵表示。每个沙发占据两个相邻的单元格（边相邻）。没有单元格被多个沙发覆盖。可能存在空单元格。

如果存在两个单元格 \( a \) 和 \( b \)，使得 \( x_{a}<x_{b} \)，且 \( a \) 被沙发 \( A \) 覆盖，\( b \) 被沙发 \( B \) 覆盖，那么沙发 \( A \) 位于沙发 \( B \) 的左边。如果存在两个单元格 \( a \) 和 \( b \)，使得 \( y_{a}<y_{b} \)，且 \( a \) 被沙发 \( A \) 覆盖，\( b \) 被沙发 \( B \) 覆盖，那么沙发 \( A \) 位于沙发 \( B \) 的上边。右边和下边的条件定义类似。

注意，在所有条件中 \( A≠B \)。而且，某个沙发 \( A \) 可能既在另一个沙发 \( B \) 的上边又在它的下边。左右条件同理。

纸条上还表明，在马克斯爷爷沙发左边的沙发有 \( cnt_{l} \) 个，右边有 \( cnt_{r} \) 个，上边有 \( cnt_{t} \) 个，下边有 \( cnt_{b} \) 个。

马克斯爷爷请你帮他找出自己的沙发。保证满足给定条件的沙发不超过一个。

输出马克斯爷爷沙发的编号。如果不存在满足所有条件的沙发，则输出 -1。

## 说明/提示
以第二个样例为例。
 - 第一个沙发左边有 \( 0 \) 个沙发，右边有 \( 2 \) 个沙发（\((1,1)\) 在 \((5,5)\) 和 \((5,4)\) 的左边），上边有 \( 0 \) 个沙发，下边有 \( 2 \) 个沙发（第2个和第3个沙发都在它下边）。
 - 第二个沙发 \( cnt_{l}=2 \)，\( cnt_{r}=1 \)，\( cnt_{t}=2 \)，\( cnt_{b}=0 \)。
 - 第三个沙发 \( cnt_{l}=2 \)，\( cnt_{r}=1 \)，\( cnt_{t}=1 \)，\( cnt_{b}=1 \)。

所以第二个沙发符合给定条件。

在第三个样例中：
 - 第一个沙发 \( cnt_{l}=1 \)，\( cnt_{r}=1 \)，\( cnt_{t}=0 \)，\( cnt_{b}=1 \)。
 - 第二个沙发 \( cnt_{l}=1 \)，\( cnt_{r}=1 \)，\( cnt_{t}=1 \)，\( cnt_{b}=0 \)。

不存在满足 \((1,0,0,0)\) 条件的沙发，所以答案是 -1。

## 样例 #1
### 输入
```
2
3 2
3 1 3 2
1 2 2 2
1 0 0 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3
10 10
1 2 1 1
5 5 6 5
6 4 5 4
2 1 2 0
```
### 输出
```
2
```

## 样例 #3
### 输入
```
2
2 2
2 1 1 1
1 2 2 2
1 0 0 0
```
### 输出
```
-1
```

### 算法分类
枚举

### 综合分析与结论
该题主要是在给定的沙发布局和相对位置条件下，找出符合特定左右上下沙发数量的目标沙发。题解采用枚举每个沙发，并通过预处理前缀和与后缀和来快速统计每个沙发左右上下的沙发数量，从而判断是否为目标沙发。这种方法的关键在于合理利用前缀和与后缀和数组，优化了统计每个沙发周围沙发数量的时间复杂度，从暴力比较的 \( O(d^2) \) 降低到 \( O(d) \)。

### 所选的题解
 - **作者：yuheng_wang080904（5星）**
    - **关键亮点**：思路清晰，详细阐述了如何通过预处理前缀和与后缀和数组来快速统计每个沙发左右上下的沙发数量，代码实现简洁明了，对边界条件处理得当。
    - **个人心得**：无

### 重点代码及核心实现思想
```cpp
#include<bits/stdc++.h>
using namespace std;
int d,n,m,cntl,cntr,cntt,cntb;
int s[5][100005],l[100005],r[100005],t[100005],b[100005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>d>>n>>m;
    for(int i=1;i<=d;i++)cin>>s[1][i]>>s[2][i]>>s[3][i]>>s[4][i];
    cin>>cntl>>cntr>>cntt>>cntb;
    for(int i=1;i<=d;i++){
        l[min(s[1][i],s[3][i])]++;
        r[max(s[1][i],s[3][i])]++;
        t[min(s[2][i],s[4][i])]++;
        b[max(s[2][i],s[4][i])]++;
    }
    for(int i=1;i<=n;i++)l[i]+=l[i-1];
    for(int i=n;i>=1;i--)r[i]+=r[i+1];
    for(int i=1;i<=m;i++)t[i]+=t[i-1];
    for(int i=m;i>=1;i--)b[i]+=b[i+1];
    for(int i=1;i<=d;i++){
        int ansl=0,ansr=0,anst=0,ansb=0;
        ansl=l[max(s[1][i],s[3][i])-1];
        if(min(s[1][i],s[3][i])==max(s[1][i],s[3][i])-1)ansl--;
        ansr=r[min(s[1][i],s[3][i])+1];
        if(max(s[1][i],s[3][i])==min(s[1][i],s[3][i])+1)ansr--;
        anst=t[max(s[2][i],s[4][i])-1];
        if(min(s[2][i],s[4][i])==max(s[2][i],s[4][i])-1)anst--;
        ansb=b[min(s[2][i],s[4][i])+1];
        if(max(s[2][i],s[4][i])==min(s[2][i],s[4][i])+1)ansb--;
        if(ansl==cntl&&ansr==cntr&&anst==cntt&&ansb==cntb){
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}
```
核心实现思想：首先读入沙发数量 \( d \)、仓库大小 \( n,m \) 以及每个沙发的位置信息和目标沙发的相对位置数量。通过循环对每个沙发，分别在表示左右上下的数组 \( l,r,t,b \) 中对应位置计数。然后对这些数组分别进行前缀和与后缀和处理。最后再次循环每个沙发，根据前缀和与后缀和数组计算出该沙发实际左右上下的沙发数量，并与目标数量比较，若相等则输出该沙发编号，循环结束未找到则输出 -1。

### 最优关键思路或技巧
利用前缀和与后缀和数组优化统计每个沙发周围沙发数量的过程，避免了每次都遍历所有沙发进行比较，降低时间复杂度。同时，在计算过程中对边界条件进行细致处理，确保结果的准确性。

### 拓展思路
此类题目属于位置关系判断与统计类问题，类似套路可以应用在其他涉及物体相对位置关系统计的题目中，例如在地图中判断某个区域周围满足特定条件的区域数量等。关键在于合理利用数据结构和预处理手段优化统计过程。

### 洛谷相似题目推荐
 - [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过枚举和状态转移解决组合计数问题，与本题枚举判断的思路类似。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过枚举不同购买方案并比较得出最优解，与本题枚举沙发并判断条件相符的思路类似。
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合并进行判断，与本题枚举沙发并判断其是否满足条件的思路类似。 

---
处理用时：66.25秒