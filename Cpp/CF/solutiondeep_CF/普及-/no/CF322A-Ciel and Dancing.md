# 题目信息

# Ciel and Dancing

## 题目描述

Fox Ciel and her friends are in a dancing room. There are $ n $ boys and $ m $ girls here, and they never danced before. There will be some songs, during each song, there must be exactly one boy and one girl are dancing. Besides, there is a special rule:

- either the boy in the dancing pair must dance for the first time (so, he didn't dance with anyone before);
- or the girl in the dancing pair must dance for the first time.

Help Fox Ciel to make a schedule that they can dance as many songs as possible.

## 说明/提示

In test case 1, there are 2 boys and 1 girl. We can have 2 dances: the 1st boy and 1st girl (during the first song), the 2nd boy and 1st girl (during the second song).

And in test case 2, we have 2 boys with 2 girls, the answer is 3.

## 样例 #1

### 输入

```
2 1
```

### 输出

```
2
1 1
2 1
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
3
1 1
1 2
2 2
```

# AI分析结果

### 题目内容
# Ciel和跳舞

## 题目描述
Fox Ciel和她的朋友们在一个舞蹈室里。这里有n个男孩和m个女孩，他们之前从未跳过舞。将会有一些歌曲，在每首歌曲期间，必须恰好有一个男孩和一个女孩在跳舞。此外，还有一个特殊规则：
 - 要么跳舞的这对中男孩必须是第一次跳舞（即他之前没有和任何人跳过舞）；
 - 要么跳舞的这对中女孩必须是第一次跳舞。
帮助Fox Ciel制定一个计划，使他们能跳尽可能多的歌曲。

## 说明/提示
在测试用例1中，有2个男孩和1个女孩。我们可以跳2支舞：第一个男孩和第一个女孩（在第一首歌时），第二个男孩和第一个女孩（在第二首歌时）。

在测试用例2中，我们有2个男孩和2个女孩，答案是3。

## 样例 #1
### 输入
```
2 1
```
### 输出
```
2
1 1
2 1
```
## 样例 #2
### 输入
```
2 2
```
### 输出
```
3
1 1
1 2
2 2
```
• **算法分类**：构造
• **综合分析与结论**：这几道题解思路较为一致，均认为最多能跳舞的歌曲数为n + m - 1 。通过特定的构造方式来满足题目条件，即先让一对都没跳过舞的男女跳舞，之后让其中一人与剩下的异性依次跳舞。不同题解在构造细节和代码风格上略有差异。整体来看，思路清晰易懂，代码实现也较为简单直接。
• **所选的题解**：
  - **作者：newbie_QwQ (5星)**
    - **关键亮点**：思路阐述详细，先分析出最多歌曲数为n + m - 1，再逐步说明构造过程，逻辑连贯，代码简洁明了，可读性高。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int i,n,m;
    cin>>n>>m;
    cout<<n+m-1<<endl;
    cout<<"1 1"<<endl;
    for(i=2;i<=n;i++) cout<<i<<" "<<1<<endl;
    for(i=2;i<=m;i++) cout<<1<<" "<<i<<endl;
    return 0;
}
```
    - **核心实现思想**：先输出最多歌曲数n + m - 1，然后先让第一个男孩与第一个女孩跳舞，接着让第一个女孩与2到n号男孩跳舞，最后让第一个男孩与2到m号女孩跳舞，完成构造。
  - **作者：FreedomKing (5星)**
    - **关键亮点**：简洁明了地阐述思路，代码使用scanf和printf进行输入输出，对习惯C风格输入输出的读者友好，同样清晰地实现了构造过程。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    printf("%d\n1 1",n+m-1);
    for(int i=2;i<=n;i++) printf("%d 1\n",i);
    for(int i=2;i<=m;i++) printf("1 %d\n",i);
    return 0;
}
```
    - **核心实现思想**：与newbie_QwQ思路一致，先输出最大歌曲数，然后按顺序构造每一次跳舞的组合。
  - **作者：hanyuchen2019 (4星)**
    - **关键亮点**：通过先让一个女孩与所有男孩跳舞，再让一个男孩与剩下女孩跳舞的方式构造，思路清晰，代码也能较好地实现功能。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    cout<<n+m-1<<'\n';
    for(int i=1;i<=n;i++)
        cout<<i<<" "<<1<<'\n';
    for(int i=2;i<=m;i++)
        cout<<1<<" "<<i<<'\n';
    return 0;
}
```
    - **核心实现思想**：先输出最大歌曲数，接着让第一个女孩依次和1到n号男孩跳舞，再让第一个男孩依次和2到m号女孩跳舞。
• **最优关键思路或技巧**：利用题目规则，通过固定一个已经跳过舞的人，让其与未跳过舞的异性依次跳舞，从而构造出最多舞蹈次数的方案。这种构造方式简单直接，能够高效地满足题目要求。
• **可拓展之处**：同类型题可关注一些具有特定限制条件的配对问题，类似算法套路为根据题目给定的限制，寻找一种合理的构造顺序，以达到最优解。
• **洛谷推荐题目**：
  - P1149 火柴棒等式：通过对数字的构造来满足火柴棒数量的限制，与本题构造配对的思路类似。
  - P1036 选数：在给定数字中通过一定规则构造出满足条件的组合，考察构造能力。
  - P1423 小玉在游泳：通过对游泳距离和休息时间的构造来解决问题，与本题构造方案思路相近。
• **个人心得**：无。 

---
处理用时：44.05秒