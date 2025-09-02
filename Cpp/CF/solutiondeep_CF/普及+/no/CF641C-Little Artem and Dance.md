# 题目信息

# Little Artem and Dance

## 题目描述

Little Artem is fond of dancing. Most of all dances Artem likes rueda — Cuban dance that is danced by pairs of boys and girls forming a circle and dancing together.

More detailed, there are $ n $ pairs of boys and girls standing in a circle. Initially, boy number $ 1 $ dances with a girl number $ 1 $ , boy number $ 2 $ dances with a girl number $ 2 $ and so on. Girls are numbered in the clockwise order. During the dance different moves are announced and all pairs perform this moves. While performing moves boys move along the circle, while girls always stay at their initial position. For the purpose of this problem we consider two different types of moves:

1. Value $ x $ and some direction are announced, and all boys move $ x $ positions in the corresponding direction.
2. Boys dancing with even-indexed girls swap positions with boys who are dancing with odd-indexed girls. That is the one who was dancing with the girl $ 1 $ swaps with the one who was dancing with the girl number $ 2 $ , while the one who was dancing with girl number $ 3 $ swaps with the one who was dancing with the girl number $ 4 $ and so one. It's guaranteed that $ n $ is even.

Your task is to determine the final position of each boy.

## 样例 #1

### 输入

```
6 3
1 2
2
1 2
```

### 输出

```
4 3 6 5 2 1
```

## 样例 #2

### 输入

```
2 3
1 1
2
1 -2
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
4 2
2
1 3
```

### 输出

```
1 4 3 2
```

# AI分析结果

### 题目内容
#### Little Artem and Dance
1. **题目描述**：小阿特姆喜欢跳舞。阿特姆最喜欢的舞蹈是鲁埃达舞（rueda），这是一种由成对的男孩和女孩围成一圈一起跳的古巴舞蹈。
更具体地说，有 \(n\) 对男孩和女孩站成一圈。最初，1号男孩与1号女孩跳舞，2号男孩与2号女孩跳舞，依此类推。女孩们按顺时针方向编号。在舞蹈过程中，会宣布不同的动作，所有舞伴都要执行这些动作。在执行动作时，男孩们沿着圆圈移动，而女孩们始终保持在初始位置。对于本题，我们考虑两种不同类型的动作：
    - 宣布一个值 \(x\) 和某个方向，所有男孩沿相应方向移动 \(x\) 个位置。
    - 与偶数编号女孩跳舞的男孩与与奇数编号女孩跳舞的男孩交换位置。也就是说，与1号女孩跳舞的男孩与与2号女孩跳舞的男孩交换位置，与3号女孩跳舞的男孩与与4号女孩跳舞的男孩交换位置，依此类推。保证 \(n\) 是偶数。
你的任务是确定每个男孩的最终位置。
2. **样例 #1**
    - **输入**：
```
6 3
1 2
2
1 2
```
    - **输出**：
```
4 3 6 5 2 1
```
3. **样例 #2**
    - **输入**：
```
2 3
1 1
2
1 -2
```
    - **输出**：
```
1 2
```
4. **样例 #3**
    - **输入**：
```
4 2
2
1 3
```
    - **输出**：
```
1 4 3 2
```

### 算法分类
数学

### 题解综合分析与结论
这几道题解的核心思路都是利用操作过程中奇数编号男孩和偶数编号男孩相对位置不变这一特性来解题。
1. **思路**：
    - **AirQwQ和wang_freedom**：思路一致，都用 `odd_plus` 记录奇数编号男孩移动步数，`even_plus` 记录偶数编号男孩移动步数，`odd_flag` 和 `even_flag` 记录奇偶编号男孩是否有特定改变，根据不同操作更新这些变量，最后确定每个男孩位置。
    - **qian_shang**：同样基于奇偶编号男孩相对位置不变，预处理奇偶编号男孩的变换规律，`x` 和 `y` 分别记录奇数和偶数编号男孩的某种偏移量，`jx` 和 `jy` 记录奇偶性是否改变，通过操作更新这些值，最后得出答案。
    - **czh___**：通过观察发现知道1号男孩位置可找到所有奇数编号男孩位置，知道2号男孩位置可找到所有偶数编号男孩位置，用 `a1` 和 `a2` 记录1号和2号男孩位置，根据操作更新，最后确定所有男孩位置。
2. **算法要点**：
    - 利用奇偶编号男孩相对位置不变，分别记录奇数和偶数编号男孩相关信息（移动步数、奇偶性改变标志等）。
    - 根据不同操作类型，对记录的信息进行相应更新。
    - 最后根据更新后的信息确定每个男孩最终位置。
3. **解决难点**：理解并利用操作过程中奇偶编号男孩相对位置不变这一隐藏规律，将复杂的移动和交换操作转化为对奇偶编号男孩各自信息的处理。

### 所选的题解
1. **AirQwQ（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对操作的化简和变量的使用解释到位，如对操作2中奇偶互换理解为奇数加1偶数减1，利用位运算简化代码。
    - **个人心得**：无
    - **重点代码核心实现思想**：通过 `Move` 函数处理圆环位置，在循环处理操作时，根据操作类型更新 `odd_plus`、`even_plus`、`odd_flag` 和 `even_flag`，最后根据这些值确定每个男孩位置。
    - **核心代码片段**：
```cpp
int Move(int step){
    if(step%n) return (step+n)%n;
    return n;
}
signed main(){
    std::ios::sync_with_stdio(0);
    cin>>n>>q;
    while(q--){
        int flag;
        cin>>flag;
        if(flag==1){
            int move;
            cin>>move;
            even_plus=Move(even_plus+move); 
            odd_plus=Move(odd_plus+move);
            if(move&1) 
                odd_flag^=1,even_flag^=1;
        }
        else{
            if(even_flag) 
                even_plus=Move(even_plus+1);
            else 
                even_plus=Move(even_plus-1);
            if(odd_flag) 
                odd_plus=Move(odd_plus+1);
            else 
                odd_plus=Move(odd_plus-1);
            odd_flag^=1,even_flag^=1;
        }
    }
    for(int i=1;i<=n;++i)
        if(i&1) 
            ans[Move(odd_plus+i)]=i;
        else 
            ans[Move(even_plus+i)]=i;
    for(int i=1;i<=n;++i) 
        cout<<ans[i]<<' ';
    return 0;
}
```
2. **qian_shang（4星）**
    - **关键亮点**：代码简洁，通过 `moo` 函数处理位置合法性，利用位运算处理奇偶性改变，逻辑清晰。
    - **个人心得**：考试时因未加交换操作中奇偶性改变的代码而全WA，强调了细节的重要性。
    - **重点代码核心实现思想**：通过 `moo` 函数使位置合法，在循环处理操作时，根据操作类型更新 `x`、`y`、`jx` 和 `jy`，最后根据这些值确定每个男孩位置。
    - **核心代码片段**：
```cpp
inline int moo(int A){return (A+n)%n==0?n:(A+n)%n;}
int main(){
    n=read();q=read();
    while (q--){
        kind=read();
        if (kind==1){
            v=read(); v%=n;
            x=moo(x+v); y=moo(y+v);
            if (v&1) jx^=1,jy^=1;
        }else {
            if (jx) x=moo(x+1);
                else x=moo(x-1);
            if (jy) y=moo(y+1);
                else y=moo(y-1);
            jx^=1,jy^=1;
        }
    }
    for (R int i=1;i<=n;i++){
        if (i&1) ans[moo(i+y)]=i;
            else ans[moo(i+x)]=i;
    }
    for (R int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
```
3. **wang_freedom（4星）**
    - **关键亮点**：思路表述简洁明了，代码结构清晰，利用 `Move` 函数处理圆环位置，与AirQwQ思路类似但代码风格略有不同。
    - **个人心得**：无
    - **重点代码核心实现思想**：同AirQwQ，通过 `Move` 函数处理圆环位置，在循环处理操作时，根据操作类型更新 `odd_plus`、`even_plus`、`odd_flag` 和 `even_flag`，最后确定每个男孩位置。
    - **核心代码片段**：
```cpp
int Move(int step){
    if(step%n)
        return(step+n)%n;
    return n;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>q;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int move;
            cin>>move;
            even_plus=Move(even_plus+move); 
            odd_plus=Move(odd_plus+move);
            if(move&1){
                odd_flag=!odd_flag;
                even_flag=!even_flag;
            }
        }
        else{
            if(even_flag) 
                even_plus=Move(even_plus+1);
            else 
                even_plus=Move(even_plus-1);
            if(odd_flag) 
                odd_plus=Move(odd_plus+1);
            else 
                odd_plus=Move(odd_plus-1);
            odd_flag^=1,even_flag^=1;
        }
    }
    rep(i,1,n)
        if(i&1)
            ans[Move(odd_plus+i)]=i;
        else
            ans[Move(even_plus+i)]=i;
    rep(i,1,n)
        cout<<ans[i]<<' ';
    return 0;
}
```

### 最优关键思路或技巧
1. **思维方式**：发现并利用操作过程中奇数编号男孩和偶数编号男孩相对位置不变这一关键规律，将复杂的移动和交换操作简化为对奇偶两类男孩各自信息的记录和更新。
2. **代码实现技巧**：利用位运算（如 `^`）来简洁地处理奇偶性改变的标志更新，提高代码效率和简洁性；通过自定义函数（如 `Move` 或 `moo`）来处理圆环位置的合法性，使代码逻辑更清晰。

### 可拓展之处
同类型题通常会给出一些对序列元素的特定操作，要求通过分析操作特性，挖掘元素间不变的相对关系，从而简化问题求解。类似算法套路是先观察操作对数据的影响，找出其中隐藏的规律（如奇偶性、相对位置等不变量），然后利用这些规律设计数据结构或变量来记录关键信息，根据操作更新这些信息，最终得出结果。

### 洛谷相似题目
1. P1080 [NOIP2012 提高组] 国王游戏：涉及数学推理和贪心策略，通过分析操作对数据的影响找出最优解。
2. P2671 [NOIP2015 提高组] 求和：需要利用数学知识和前缀和思想来解决问题，与本题通过分析规律简化计算有相似之处。
3. P1147 连续自然数和：利用数学方法，通过对问题的分析找到满足条件的自然数序列，考查对数学规律的挖掘和应用。 

---
处理用时：103.89秒