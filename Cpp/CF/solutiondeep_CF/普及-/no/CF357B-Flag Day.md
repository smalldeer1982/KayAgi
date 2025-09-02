# 题目信息

# Flag Day

## 题目描述

In Berland, there is the national holiday coming — the Flag Day. In the honor of this event the president of the country decided to make a big dance party and asked your agency to organize it. He has several conditions:

- overall, there must be $ m $ dances;
- exactly three people must take part in each dance;
- each dance must have one dancer in white clothes, one dancer in red clothes and one dancer in blue clothes (these are the colors of the national flag of Berland).

The agency has $ n $ dancers, and their number can be less than $ 3m $ . That is, some dancers will probably have to dance in more than one dance. All of your dancers must dance on the party. However, if some dance has two or more dancers from a previous dance, then the current dance stops being spectacular. Your agency cannot allow that to happen, so each dance has at most one dancer who has danced in some previous dance.

You considered all the criteria and made the plan for the $ m $ dances: each dance had three dancers participating in it. Your task is to determine the clothes color for each of the $ n $ dancers so that the President's third condition fulfilled: each dance must have a dancer in white, a dancer in red and a dancer in blue. The dancers cannot change clothes between the dances.

## 样例 #1

### 输入

```
7 3
1 2 3
1 4 5
4 6 7
```

### 输出

```
1 2 3 3 2 2 1 
```

## 样例 #2

### 输入

```
9 3
3 6 9
2 5 8
1 4 7
```

### 输出

```
1 1 1 2 2 2 3 3 3 
```

## 样例 #3

### 输入

```
5 2
4 1 5
3 1 2
```

### 输出

```
2 3 1 1 3 
```

# AI分析结果

### 题目内容
# 国旗日

## 题目描述
在伯兰，即将迎来国庆节——国旗日。为了庆祝这个节日，该国总统决定举办一场大型舞会，并要求你的机构来组织。他有几个条件：
- 总共必须有 $m$ 场舞蹈；
- 每场舞蹈必须恰好有三个人参加；
- 每场舞蹈必须有一名穿着白色衣服的舞者、一名穿着红色衣服的舞者和一名穿着蓝色衣服的舞者（这是伯兰国旗的颜色）。

该机构有 $n$ 名舞者，且人数可能少于 $3m$。也就是说，一些舞者可能需要参加不止一场舞蹈。你所有的舞者都必须在舞会上跳舞。然而，如果某场舞蹈中有两名或更多来自之前舞蹈的舞者，那么当前这场舞蹈就不再精彩。你的机构不能允许这种情况发生，所以每场舞蹈最多只能有一名曾参加过之前舞蹈的舞者。

你考虑了所有标准，并制定了 $m$ 场舞蹈的计划：每场舞蹈都有三名舞者参加。你的任务是为 $n$ 名舞者中的每一位确定衣服颜色，以便满足总统的第三个条件：每场舞蹈必须有一名穿白色衣服的舞者、一名穿红色衣服的舞者和一名穿蓝色衣服的舞者。舞者在舞蹈之间不能换衣服。

## 样例 #1
### 输入
```
7 3
1 2 3
1 4 5
4 6 7
```
### 输出
```
1 2 3 3 2 2 1 
```

## 样例 #2
### 输入
```
9 3
3 6 9
2 5 8
1 4 7
```
### 输出
```
1 1 1 2 2 2 3 3 3 
```

## 样例 #3
### 输入
```
5 2
4 1 5
3 1 2
```
### 输出
```
2 3 1 1 3 
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略。即每次处理一个三人组时，优先利用已确定颜色的人来决定未确定颜色人的颜色。算法要点在于记录每个人的颜色以及已使用的颜色，难点在于如何在满足每个三人组颜色各不相同且尽量复用之前颜色分配结果的情况下，为所有人分配颜色。各题解在实现细节上略有差异，但整体思路相近。

### 所选的题解
- **作者：lrx___ (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，使用数组和布尔数组分别记录每个人衣服的颜色和颜色是否被访问，逻辑直观。
    - **重点代码**：
```pascal
var
    a:array[1..100005,1..5]of longint;
    c:array[1..100005]of byte;
    vs:array[1..5]of boolean;
    n,m,i,j:longint;
begin
    read(n,m);
    for i:=1 to m do begin
        for j:=1 to 3 do begin
            read(a[i,j]);
        end;
    end;
    for i:=1 to m do begin
        vs[1]:=0;vs[2]:=0;vs[3]:=0;
        for j:=1 to 3 do begin
            vs[c[a[i,j]]]:=true;
        end;
        for j:=1 to 3 do begin
            if(c[a[i,j]]=0)then begin
                if(not vs[1])then begin
                    c[a[i,j]]:=1;vs[1]:=true;
                end else if(not vs[2])then begin
                    c[a[i,j]]:=2;vs[2]:=true;
                end else begin
                    c[a[i,j]]:=3;vs[3]:=true;
                end;
            end;
        end;
    end;
    for i:=1 to n do begin
        write(c[i],' ');
    end;
end.
```
    - **核心实现思想**：外层循环遍历每场舞蹈，每次先初始化颜色使用标记数组 `vs`。内层循环先标记已确定颜色的人的颜色，再为未确定颜色的人选择未使用的颜色。最后输出每个人的颜色。
- **作者：Keroshi (4星)**
    - **关键亮点**：结合图示解释贪心过程，使思路更易理解，代码采用 `C++` 编写，结构清晰。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,a[N],f[N],d[N];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a[1],&a[2],&a[3]);
        memset(d,0,sizeof(d));
        for(int j=1;j<=3;j++)
            if(f[a[j]]) d[f[a[j]]]=1;
        for(int j=1;j<=3;j++)
            if(!f[a[j]])
                for(int k=1;k<=3;k++)
                    if(!d[k]){
                        f[a[j]]=k;
                        d[k]=1;
                        break;
                    }
    }
    for(int i=1;i<=n;i++)
        printf("%d ",f[i]); 
    return 0;
} 
```
    - **核心实现思想**：每次处理一场舞蹈时，先清空颜色使用标记数组 `d`，然后标记已确定颜色的人的颜色，接着为未确定颜色的人从可用颜色中选择一种。最后输出每个人的颜色。
- **作者：okra_l (4星)**
    - **关键亮点**：代码注释详细，对数组和变量的用途解释清晰，逻辑连贯。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[100010][5], f[100010]; 
bool v[5]; 

int main() {
    int n, m, i, j;
    scanf("%d%d", &n, &m); 

    for(i = 0; i < m; i++) {
        for(j = 0; j < 3; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for(i = 0; i < m; i++) {
        for(j = 0; j < 3; j++) {
            v[f[a[i][j]]] = 1; 
        }
        for(j = 0; j < 3; j++) {
            if(!f[a[i][j]]) {
                if(!v[1]) {
                    v[1] = 1; 
                    f[a[i][j]] = 1; 
                } else if(!v[2]) {
                    v[2] = 1; 
                    f[a[i][j]] = 2; 
                } else {
                    v[3] = 1; 
                    f[a[i][j]] = 3; 
                }
            }
        }
        v[1] = v[2] = v[3] = 0; 
    }

    for(i = 1; i <= n; i++) {
        printf("%d ", f[i]);
    }

    return 0;
}
```
    - **核心实现思想**：与其他题解类似，先读取所有三人组信息，然后在处理每场舞蹈时，标记已使用颜色，为未确定颜色的人分配未使用颜色，最后输出每个人的颜色。

### 最优关键思路或技巧
利用贪心策略，优先利用已确定颜色的人来决定未确定颜色人的颜色，通过数组记录每个人的颜色以及颜色的使用情况，从而高效地为所有人分配颜色。

### 可拓展之处
同类型题通常围绕条件限制下的资源分配或组合问题，类似算法套路是利用贪心思想，根据已有的状态去决定后续的选择，以满足整体的条件要求。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
无个人心得相关内容。 

---
处理用时：61.87秒