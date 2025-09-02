# 题目信息

# Colour the Flag

## 题目描述

Today we will be playing a red and white colouring game (no, this is not the Russian Civil War; these are just the colours of the Canadian flag).

You are given an $ n \times m $ grid of "R", "W", and "." characters. "R" is red, "W" is white and "." is blank. The neighbours of a cell are those that share an edge with it (those that only share a corner do not count).

Your job is to colour the blank cells red or white so that every red cell only has white neighbours (and no red ones) and every white cell only has red neighbours (and no white ones). You are not allowed to recolour already coloured cells.

## 说明/提示

The answer for the first example case is given in the example output, and it can be proven that no grid exists that satisfies the requirements of the second example case. In the third example all cells are initially coloured, and the colouring is valid.

## 样例 #1

### 输入

```
3
4 6
.R....
......
......
.W....
4 4
.R.W
....
....
....
5 1
R
W
R
W
R```

### 输出

```
YES
WRWRWR
RWRWRW
WRWRWR
RWRWRW
NO
YES
R
W
R
W
R```

# AI分析结果

### 题目内容
# 旗帜涂色

## 题目描述
今天我们将进行一个红白涂色游戏（不，这不是俄罗斯内战；这只是加拿大国旗的颜色）。
你会得到一个 $n \times m$ 的由“R”、“W”和“.”字符组成的网格。“R”代表红色，“W”代表白色，“.”代表空白。一个单元格的邻居是指与其共享一条边的单元格（仅共享一个角的不算）。
你的任务是将空白单元格涂成红色或白色，使得每个红色单元格仅与白色邻居相邻（没有红色邻居），并且每个白色单元格仅与红色邻居相邻（没有白色邻居）。你不允许重新给已经涂色的单元格上色。

## 说明/提示
第一个示例案例的答案在示例输出中给出，可以证明不存在满足第二个示例案例要求的网格。在第三个示例中，所有单元格最初都已涂色，并且这种涂色是有效的。

## 样例 #1
### 输入
```
3
4 6
.R....
......
......
.W....
4 4
.R.W
....
....
....
5 1
R
W
R
W
R
```
### 输出
```
YES
WRWRWR
RWRWRW
WRWRWR
RWRWRW
NO
YES
R
W
R
W
R
```

### 算法分类
模拟

### 综合分析与结论
所有题解思路基本一致，均基于满足条件的矩阵只有两种形式（左上角为“R”或“W” ）这一特性。通过分析横纵坐标之和的奇偶性来确定每个位置应有的颜色，进而与输入矩阵对比判断是否能满足涂色要求。各题解的主要差异在于代码实现细节，如数组定义、输入输出方式、判断逻辑的具体写法等。

### 所选的题解
- **作者：zct_sky（5星）**
  - **关键亮点**：思路清晰，代码结构简洁明了。通过定义两个数组分别存储两种可能的矩阵形式，然后与输入矩阵对比判断，逻辑清晰，易于理解。
  - **重点代码**：
```cpp
void work(){
    char b[51][51],c[51][51];//b数组为第一个是白色的矩阵，c数组为第一个是红色的矩阵
    bool fb=1,fc=1;
    for(int i=0;i<n;i++)//存入矩阵 
        for(int j=0;j<m;j++)
            if((i+j)%2) b[i][j]='W',c[i][j]='R';
            else b[i][j]='R',c[i][j]='W';
    for(int i=0;i<n;i++)//判断 
        for(int j=0;j<m;j++)
            if(a[i][j]!='.'){ 
                if(a[i][j]!=b[i][j])fb=0;
                if(a[i][j]!=c[i][j])fc=0;
            }
    if(fb){
        cout<<"YES\n";
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++) cout<<b[i][j];
            puts("");
        }
    }else if(fc){
        cout<<"YES\n";
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++) cout<<c[i][j];
            puts("");
        }
    }else cout<<"NO\n";
}
```
  - **核心实现思想**：先初始化两种可能的矩阵 `b` 和 `c`，再遍历输入矩阵 `a`，对比已涂色部分与 `b`、`c` 相应位置，若都不匹配则输出“NO”，否则输出匹配的矩阵。

- **作者：BorisDimitri（5星）**
  - **关键亮点**：代码简洁高效，利用三维数组 `ans` 存储两种可能的矩阵形式，通过 `check` 函数判断输入矩阵与预存矩阵是否匹配，逻辑清晰，代码可读性高。
  - **重点代码**：
```cpp
bool check(int x)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(ans[i][j][x]!= g[i][j] && g[i][j]!= '.')
                return false;
    return true;
}

void print(int x)
{
    cout<<"YES"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout<<ans[i][j][x];
        cout<<endl;
    }
}

int main()
{
    cin>>t;

    for(int i=0;i<=50;i++)
        for(int j=0;j<=50;j++)
            if((i+j) % 2 == 0) ans[i][j][0] = 'W',ans[i][j][1] = 'R';
            else ans[i][j][0] = 'R',ans[i][j][1] = 'W';
 
    while(t--)
    {
        cin>>n>>m;
        for(int i=0;i<n;i++) cin>>g[i];

        if(check(0)) print(0);
        else if(check(1)) print(1);
        else cout<<"NO"<<endl;
    }

    return 0;
}
```
  - **核心实现思想**：先预处理出两种矩阵形式存入 `ans`，每次输入矩阵后，通过 `check` 函数判断是否匹配，匹配则通过 `print` 函数输出。

- **作者：HerikoDeltana（4星）**
  - **关键亮点**：对思路的阐述详细，代码中使用了较多自定义的宏定义和函数，如 `fr` 用于快速读入，`fw` 用于快速输出，虽然代码稍显复杂，但对于理解思路和优化输入输出有一定参考价值。
  - **重点代码**：
```cpp
I void cw()
{
    mst(b,0);mst(c,0);
    for(R LL i=1;i<=100;++i)
        for(R LL j=1;j<=100;++j)
            if((i+j)&1) b[i][j]=1,c[i][j]=2;
            else b[i][j]=2,c[i][j]=1;
}

S main()
{
    fr(t);
    cw();
    while(t--)
    {
        fr(n),fr(m);
        mst(a,0);
        for(R LL i=1;i<=n;++i)
            for(R LL j=1;j<=m;++j)
                cin>>ch[i][j];
        for(R LL i=1;i<=n;++i)
            for(R LL j=1;j<=m;++j)
                if(ch[i][j]=='W') a[i][j]=1;
                else if(ch[i][j]=='R') a[i][j]=2;
        bool c1,c2;
        c1=c2=true;
        for(R LL i=1;i<=n;++i)
            for(R LL j=1;j<=m;++j)
                if(b[i][j]!=a[i][j] and a[i][j])
                {
                    c1=false;
                    break;
                }
        if(c1)
        {
            puts("YES");
            for(R LL i=1;i<=n;putchar('\n'),++i)
                for(R LL j=1;j<=m;++j)
                    if(b[i][j]==2) putchar('R');
                    else putchar('W');
            continue;
        }
        for(R LL i=1;i<=n;++i)
            for(R LL j=1;j<=m;++j)
                if(c[i][j]!=a[i][j] and a[i][j])
                {
                    c2=false;
                    break;
                }
        if(c2)
        {
            puts("YES");
            for(R LL i=1;i<=n;putchar('\n'),++i)
                for(R LL j=1;j<=m;++j)
                    if(c[i][j]==2) putchar('R');
                    else putchar('W');
            continue;
        }
        else
        {
            puts("NO");
            continue;
        }   
    }
    Heriko Deltana;
}
```
  - **核心实现思想**：通过 `cw` 函数初始化两种可能的矩阵状态，将输入矩阵转换为数字形式后与预存矩阵对比判断，根据结果输出相应内容。

### 最优关键思路或技巧
利用横纵坐标之和的奇偶性来确定单元格颜色，预先生成两种可能的矩阵形式，然后与输入矩阵进行对比判断，这种方法简洁高效，避免了复杂的搜索或其他操作。

### 拓展
同类型题通常围绕矩阵元素的特定排列规则或相邻元素关系展开，类似算法套路为通过分析元素间规律，利用数学性质（如奇偶性）简化问题，预存可能的结果形式并与输入对比。

### 洛谷推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)
- [P1244 青蛙过河](https://www.luogu.com.cn/problem/P1244) 

---
处理用时：60.25秒