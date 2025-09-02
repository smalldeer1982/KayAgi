# 题目信息

# ccj与zrz之积木问题

## 题目背景

ccj和zrz无聊到了玩起了搭积木...(本题选自uva101，翻译来自《算法竞赛入门经典2》)


## 题目描述

从左到右有 $n$ 个木块，编号从 $0$ 到 $n-1$，要求模拟以下 $4$ 种操作（下面的 $a$ 和 $b$ 都是木块编号，归位表示比如 $1$ 号木块归到 $1$ 号位去）。

- $\texttt{move }a\texttt{ onto }b$：把 $a$ 和 $b$ 上方的木块全部归位，然后把 $a$ 摞在 $b$ 上面；
- $\texttt{move }a\texttt{ over }b$：把 $a$ 上方的全部归位，然后把 $a$ 放在 $b$ 所在木块堆的顶部；
- $\texttt{pile }a\texttt{ onto }b$：把 $b$ 上方的木块全部归位，然后把 $a$ 及上面的木块整体摞在 $b$ 上面；
- $\texttt{pile }a\texttt{ over }b$：把 $a$ 及上面的木块整体摞在 $b$ 所在木块堆的顶部；
- 遇到 $\texttt{quit}$ 停止。$a$ 和 $b$ 在同一堆的指令时非法指令，应当忽略。

最后输出每个位置的木块列表，按照从底部到顶部的顺序排列。

## 说明/提示

### 数据范围及约定

对于全部数据，$0<n<25$。

## 样例 #1

### 输入

```
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit```

### 输出

```
0: 0
1: 1 9 2 4
2:
3: 3
4:
5: 5 8 7 6
6:
7:
8:
9:```

# AI分析结果

• 综合分析与结论：这些题解均针对积木操作模拟问题，核心思路是根据不同操作指令对积木位置进行调整。大多题解使用vector来存储积木状态，部分使用数组或栈。算法要点在于准确实现四种操作指令，难点主要是处理归位操作以及保证积木移动顺序正确。部分题解通过函数封装使代码结构更清晰，部分题解在细节处理和代码可读性上有所欠缺。

所选的题解：
  - 作者：gcwixsxr (赞：12)  星级：4星
    - 关键亮点：思路清晰，对每个操作函数进行详细解释，代码结构完整，通过findd函数查找木块位置，各操作函数依据题目要求准确实现积木的移动和归位。
    - 个人心得：在pile_onto函数中提到将a上方木块移至b上面时，要注意按正序推入，否则顺序会颠倒，自己在此处出错多次。
    ```cpp
    void findd(int a,int &p,int &h){//查找原值的位置（"&"可改变原值）
        for(int i=0;i<n;i++){
            for(int j=0;j<v[i].size();j++){
                if(v[i][j]==a)p=i,h=j;//p为队列的指针，h为该数在队列中的位置
            }
        }
    }
    void move_onto(int a,int b){
        int p,h;
        findd(a,p,h);
        for(int i=v[p].size()-1;i>h;i--){
            v[v[p][i]].push_back(v[p][i]);//把v[p][i]放到队列v[v[p][i]]里
            v[p].pop_back();//弹出队列v[p]中的尾位
        }
        v[p].pop_back();//弹出a    
        findd(b,p,h);
        for(int i=v[p].size()-1;i>h;i--){
            v[v[p][i]].push_back(v[p][i]);//把v[p][i]放到队列v[v[p][i]]里
            v[p].pop_back(); //弹出队列v[p]中的尾位
        }
        v[p].push_back(a);//在b的上方推入a
    }
    ```
  - 作者：1124828077ccj (赞：5)  星级：4星
    - 关键亮点：同样采用vector模拟，将每个操作单独写成函数，逻辑清晰，代码简洁明了。
    ```cpp
    void find(){
        for (int i=0;i<n;i++)
            for (int o=0;o<s[i].size();o++)
                {if (s[i][o]==a){h1=i;q1=o;}if (s[i][o]==b){h2=i;q2=o;}};
    }
    void moveonto(){
        for (int i=q1+1;i<s[h1].size();i++)
            s[s[h1][i]].push_back(s[h1][i]);
        for (int i=q2+1;i<s[h2].size();i++)
            s[s[h2][i]].push_back(s[h2][i]);
        s[h1].resize(q1);
        s[h2].resize(q2+1);
        s[h2].push_back(a);
    }
    ```
  - 作者：KobeBeanBryantCox (赞：4)  星级：4星
    - 关键亮点：通过定义多个辅助函数，如find、add、back和move，将复杂操作模块化，使代码逻辑更清晰，易于理解和维护。
    - 个人心得：因忽略a和b在同一堆时指令非法的情况，调试很久代码。
    ```cpp
    int find(int x)
    // 寻找编号为 x 的积木所在的堆的编号
    {
        for(int i=0;i<n;i++)
            for(int j=1;j<=height[i];j++)
                if(a[i][j]==x)return i;
        return 0;
    }
    void add(int x,int y)
    // 将编号为 y 的积木摞到编号为 x 的堆的顶部
    {
        a[x][++height[x]]=y;
    }
    void back(int x)
    // 编号为 x 的积木上面的积木全部归位
    {
        int k=find(x); // 先找到 x 所在的堆
        for(;height[k]>0;height[k]--)
        {
            int u=a[k][height[k]]; // u 表示当前这个堆的最顶层的积木编号
            if(u==x)break;
            add(u,u); // 把它上面的全部归位
        }
    }
    void move(int x,int y)
    //编号为 x 的积木以及它以上的积木 全部整体摞在 编号为 y 的积木所在的那一堆的顶部
    {
        int ka=find(x),kb=find(y),xx; // 先找到 x 和 y 的堆
        for(int i=1;i<=height[ka];i++)
            if(a[ka][i]==x)
            {
                xx=i;
                break;
            }
        for(int i=xx;i<=height[ka];i++)add(kb,a[ka][i]);
        height[ka]=xx-1; // 高度变化
    }
    ```

最优关键思路或技巧：使用合适的数据结构（如vector）存储积木状态，通过函数封装将复杂操作模块化，提高代码的可读性和维护性。在处理积木移动和归位时，要注意操作顺序和边界条件。

可拓展之处：同类型题通常涉及物体位置的模拟和调整，类似算法套路是先确定合适的数据结构来表示物体状态，再将各种操作抽象成函数进行实现。

推荐题目：
  - P1032 [NOIP2002 普及组] 字串变换
  - P1162 填涂颜色
  - P1443 马的遍历 

---
处理用时：61.25秒