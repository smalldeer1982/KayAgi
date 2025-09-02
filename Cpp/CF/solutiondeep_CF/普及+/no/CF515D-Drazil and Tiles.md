# 题目信息

# Drazil and Tiles

## 题目描述

Drazil created a following problem about putting $ 1×2 $ tiles into an $ n×m $ grid:

"There is a grid with some cells that are empty and some cells that are occupied. You should use $ 1×2 $ tiles to cover all empty cells and no two tiles should cover each other. And you should print a solution about how to do it."

But Drazil doesn't like to write special checking program for this task. His friend, Varda advised him: "how about asking contestant only to print the solution when it exists and it is unique? Otherwise contestant may print 'Not unique' ".

Drazil found that the constraints for this task may be much larger than for the original task!

Can you solve this new problem?

Note that you should print 'Not unique' either when there exists no solution or when there exists several different solutions for the original task.

## 说明/提示

In the first case, there are indeed two solutions:

```plain
<>^
^*v
v<>
```

and

```plain
^<>
v*^
<>v
```

so the answer is "Not unique".

## 样例 #1

### 输入

```
3 3
...
.*.
...
```

### 输出

```
Not unique
```

## 样例 #2

### 输入

```
4 4
..**
*...
*.**
....
```

### 输出

```
<>**
*^<>
*v**
<><>```

## 样例 #3

### 输入

```
2 4
*..*
....
```

### 输出

```
*<>*
<><>```

## 样例 #4

### 输入

```
1 1
.
```

### 输出

```
Not unique
```

## 样例 #5

### 输入

```
1 1
*
```

### 输出

```
*
```

# AI分析结果

### 题目内容
# Drazil和瓷砖

## 题目描述
Drazil设计了一个关于将1×2的瓷砖放入n×m网格的问题：
“有一个网格，其中一些单元格为空，一些单元格被占用。你应该用1×2的瓷砖覆盖所有空单元格，且任意两块瓷砖不能相互覆盖。你需要输出如何完成覆盖的方案。”
但Drazil不想为此任务编写专门的检查程序。他的朋友Varda建议他：“不如要求参赛者仅在方案存在且唯一时输出方案。否则，参赛者可以输出‘Not unique’。”
Drazil发现这个任务的限制条件可能比原始任务大得多！
你能解决这个新问题吗？
请注意，当不存在解决方案或原始任务存在多种不同解决方案时，你都应该输出“Not unique”。

## 说明/提示
在第一种情况下，确实有两种解决方案：
```plain
<>^
^*v
v<>
```
和
```plain
^<>
v*^
<>v
```
所以答案是“Not unique”。

## 样例 #1
### 输入
```
3 3
...
.*.
...
```
### 输出
```
Not unique
```

## 样例 #2
### 输入
```
4 4
..**
*...
*.**
....
```
### 输出
```
<>**
*^<>
*v**
<><>```

## 样例 #3
### 输入
```
2 4
*..*
....
```
### 输出
```
*<>*
<><>```

## 样例 #4
### 输入
```
1 1
.
```
### 输出
```
Not unique
```

## 样例 #5
### 输入
```
1 1
*
```
### 输出
```
*
```

### 算法分类
贪心

### 综合分析与结论
这几道题解思路大致相同，均利用了贪心思想。核心思路是通过寻找度数为1的点（即周围只有一个空单元格的空单元格），将其与相连的空单元格组成1×2的瓷砖进行覆盖，不断重复此过程，直到没有度数为1的点。若此时所有空单元格都被覆盖，则存在唯一解，否则输出“Not unique”。证明思路在于若存在环，可通过交换环上黑边与白边（将多米诺覆盖的两点用黑边相连，其余用白边相连）得到不同解。

### 所选的题解
- **作者：ZJMZJM (赞：4)  星级：4星  关键亮点**：代码结构清晰，注释较为详细，使用队列存储度数为1的点，通过循环不断更新节点度数并处理新出现的度数为1的点。利用宏定义简化代码书写，还使用了快读优化输入。
```cpp
// 关键代码
while(1)
{
    int i,j;
    if(!q.empty())
    {
        hp pt=q.front(); 
        q.pop();
        i=pt.x; 
        j=pt.y;
        if(color[i][j]=='*'||d[i][j]!=1) 
            continue;
        for (int k=0;k<4;++k)
        {
            int nowx=i+sx[k],nowy=j+sy[k];
            if(nowx<=0||nowx>n||nowy<=0||nowy>m) 
                continue;
            if(color[nowx][nowy]=='.')
            {
                For(l,0,3)
                {
                    int nxtx=nowx+sx[l],nxty=nowy+sy[l];
                    if (nxtx<=0||nxtx>n||nxty<=0||nxty>m||color[nxtx][nxty]=='*') 
                        continue;
                    d[nxtx][nxty]--;
                    if(d[nxtx][nxty]==1) 
                        q.push((hp){nxtx,nxty});
                }
                color[nowx][nowy]=color[i][j]='*';
                d[nowx][nowy]=d[i][j]=0;
                cnt+=2; 
                flag=false;
                switch(k)
                {
                    case 0:
                    {
                        ans[i][j]='^';
                        ans[nowx][nowy]='v';
                        break;
                    }
                    case 1:
                    {
                        ans[i][j]='v';
                        ans[nowx][nowy]='^';
                        break;
                    }
                    case 2:
                    {
                        ans[i][j]='<';
                        ans[nowx][nowy]='>';
                        break;
                    }
                    case 3:
                    {
                        ans[i][j]='>';
                        ans[nowx][nowy]='<';
                        break;
                    }
                }
                break;
            }
        }
    }
    else break;
}
if(cnt==n*m)
{
    For(i,1,n)
    {
        For(j,1,m) 
            printf("%c",ans[i][j]);
        printf("\n");
    }
}
else
    printf("Not unique\n");
```
- **作者：_edge_ (赞：1)  星级：4星  关键亮点**：代码简洁明了，直接使用数组模拟图的度数，通过两次循环遍历处理度数为1的点及其相连点，同时更新度数并判断最终是否填满所有空单元格。
```cpp
// 关键代码
for (int i=1; i<=tot; i++) {
    int xx=aa[i][0],yy=aa[i][1];
    in[xx][yy]=0;
    for (int k=0; k<4; k++) {
        int gx=fx[k]+xx,gy=fy[k]+yy;
        if (gx<1 || gy<1 || gx>n || gy>m) continue;
        if (ch[gx][gy]!='.') continue;
        in[gx][gy]--;
        if (k==0 || k==1) ch[xx][yy]=fz[k],ch[gx][gy]=fz[1-k];
        if (k==2 || k==3) ch[xx][yy]=fz[k],ch[gx][gy]=fz[(k==2? 3 : 2)];
        xx=gx,yy=gy;
        break;
    }
    for (int k=0; k<4; k++) {
        int gx=fx[k]+xx,gy=fy[k]+yy;
        if (gx<1 || gy<1 || gx>n || gy>m) continue;
        if (ch[gx][gy]!='.') continue;
        in[gx][gy]--;
        if (in[gx][gy]==1)
            aa[++tot][0]=gx,aa[tot][1]=gy;
    }
}
int fl=1;
for (int i=1; i<=n; i++)
    for (int j=1; j<=m; j++)
        if (ch[i][j]!='.');
        else fl=0;
if (!fl) cout<<"Not unique\n";
else {
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++)
            cout<<ch[i][j];
        cout<<"\n";
    }
}
```
- **作者：Error_Eric (赞：0)  星级：4星  关键亮点**：使用栈来存储度数为1的点，利用宏定义简化代码书写，如计算点周围空地数量的宏定义。代码逻辑紧凑，通过简洁的操作完成对问题的求解。
```cpp
// 关键代码
while(!s.empty()){
    pii now=s.top();s.pop();
    for(rei k=1;k<=4;k++){
        pii nex=now+dir[k];
        if(c[nx][ny]=='.'){
            switch(k){
            case 1:c[now.first][now.second]='^',c[nx][ny]='v';break;
            case 2:c[now.first][now.second]='v',c[nx][ny]='^';break;
            case 3:c[now.first][now.second]='<',c[nx][ny]='>';break;
            case 4:c[now.first][now.second]='>',c[nx][ny]='<';break;
            }
            for(rei kk=1;kk<=4;kk++){
                pii p1=nex+dir[kk],p2=now+dir[kk];
                if(c[p1.first][p1.second]=='.' and --ds[p1.first][p1.second]==1)s.push(p1);
                if(c[p2.first][p2.second]=='.' and --ds[p2.first][p2.second]==1)s.push(p2);
            }
            break;
        }
    }
}
Each()if(c[i][j]=='.')return puts("Not unique"),0;
for(rei i=1;i<=n;i++)c[i][m+1]=10;
Each()putchar(c[i][j]);
```

### 最优关键思路或技巧
利用贪心策略，优先处理度数为1的点，因为这些点的瓷砖放置方式是唯一确定的。通过不断更新点的度数来寻找新的度数为1的点，从而逐步确定整个瓷砖覆盖方案。这种思路将复杂的覆盖问题简化为一系列简单的、确定性的决策过程。同时，利用数据结构（如队列、栈）存储度数为1的点，方便进行后续处理。

### 可拓展之处
此类题目属于棋盘覆盖类问题，类似算法套路可应用于其他形状瓷砖在网格中的覆盖问题，同样可以通过寻找具有确定性放置方式的点（如边界点、孤立点等），利用贪心思想逐步解决。

### 洛谷相似题目
- P1140 相似三角形
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水 

---
处理用时：84.95秒