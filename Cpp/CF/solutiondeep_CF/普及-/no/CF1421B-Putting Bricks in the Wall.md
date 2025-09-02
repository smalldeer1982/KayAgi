# 题目信息

# Putting Bricks in the Wall

## 题目描述

Pink Floyd are pulling a prank on Roger Waters. They know he doesn't like [walls](https://www.youtube.com/watch?v=YR5ApYxkU-U), he wants to be able to walk freely, so they are blocking him from exiting his room which can be seen as a grid.

Roger Waters has a square grid of size $ n\times n $ and he wants to traverse his grid from the upper left ( $ 1,1 $ ) corner to the lower right corner ( $ n,n $ ). Waters can move from a square to any other square adjacent by a side, as long as he is still in the grid. Also except for the cells ( $ 1,1 $ ) and ( $ n,n $ ) every cell has a value $ 0 $ or $ 1 $ in it.

Before starting his traversal he will pick either a $ 0 $ or a $ 1 $ and will be able to only go to cells values in which are equal to the digit he chose. The starting and finishing cells ( $ 1,1 $ ) and ( $ n,n $ ) are exempt from this rule, he may go through them regardless of picked digit. Because of this the cell ( $ 1,1 $ ) takes value the letter 'S' and the cell ( $ n,n $ ) takes value the letter 'F'.

For example, in the first example test case, he can go from ( $ 1, 1 $ ) to ( $ n, n $ ) by using the zeroes on this path: ( $ 1, 1 $ ), ( $ 2, 1 $ ), ( $ 2, 2 $ ), ( $ 2, 3 $ ), ( $ 3, 3 $ ), ( $ 3, 4 $ ), ( $ 4, 4 $ )

The rest of the band (Pink Floyd) wants Waters to not be able to do his traversal, so while he is not looking they will invert at most two cells in the grid (from $ 0 $ to $ 1 $ or vice versa). They are afraid they will not be quick enough and asked for your help in choosing the cells.  Note that you cannot invert cells $ (1, 1) $ and $ (n, n) $ .

We can show that there always exists a solution for the given constraints.

Also note that Waters will pick his digit of the traversal after the band has changed his grid, so he must not be able to reach ( $ n,n $ ) no matter what digit he picks.

## 说明/提示

For the first test case, after inverting the cell, we get the following grid:

```
<pre class="verbatim"><br></br>S010<br></br>0001<br></br>1001<br></br>111F<br></br>
```

## 样例 #1

### 输入

```
3
4
S010
0001
1000
111F
3
S10
101
01F
5
S0101
00000
01111
11111
0001F```

### 输出

```
1
3 4
2
1 2
2 1
0```

# AI分析结果

### 题目内容
# 在墙上砌砖

## 题目描述
平克·弗洛伊德（Pink Floyd）正在捉弄罗杰·沃特斯（Roger Waters）。他们知道他不喜欢[墙](https://www.youtube.com/watch?v=YR5ApYxkU-U)，他希望能够自由行走，所以他们把他堵在房间里，这个房间可以看作一个网格。

罗杰·沃特斯有一个 $n \times n$ 的正方形网格，他想从左上角（$1,1$）角走到右下角（$n,n$）角。沃特斯可以从一个方格移动到任何其他相邻的方格（只要边相邻且仍在网格内）。除了单元格（$1,1$）和（$n,n$），每个单元格都有一个值 $0$ 或 $1$。

在开始他的遍历之前，他会选择一个 $0$ 或 $1$，并且只能走到值等于他所选数字的单元格。起始和结束单元格（$1,1$）和（$n,n$）不受此规则限制，无论他选择什么数字，他都可以通过它们。因此，单元格（$1,1$）的值为字母 'S'，单元格（$n,n$）的值为字母 'F'。

例如，在第一个示例测试用例中，他可以通过这条路径上的 $0$ 从（$1, 1$）走到（$n, n$）：（$1, 1$），（$2, 1$），（$2, 2$），（$2, 3$），（$3, 3$），（$3, 4$），（$4, 4$）。

乐队的其他成员（平克·弗洛伊德）希望沃特斯无法完成他的遍历，所以趁他不注意，他们将在网格中最多反转两个单元格（从 $0$ 变为 $1$ 或反之亦然）。他们担心自己动作不够快，所以向你求助，让你帮忙选择要反转的单元格。注意，你不能反转单元格（$1, 1$）和（$n, n$）。

我们可以证明，对于给定的约束条件，总是存在解决方案。

还要注意，沃特斯将在乐队改变他的网格后选择他遍历的数字，所以无论他选择什么数字，他都不能到达（$n,n$）。

## 说明/提示
对于第一个测试用例，反转单元格后，我们得到以下网格：

```
<pre class="verbatim"><br></br>S010<br></br>0001<br></br>1001<br></br>111F<br></br>
```

## 样例 #1
### 输入
```
3
4
S010
0001
1000
111F
3
S10
101
01F
5
S0101
00000
01111
11111
0001F```
### 输出
```
1
3 4
2
1 2
2 1
0```

### 算法分类
构造

### 题解综合分析与结论
这些题解的核心思路都是通过对与起点 $(1,1)$ 相邻的 $(1,2)$、$(2,1)$ 和与终点 $(n,n)$ 相邻的 $(n - 1,n)$、$(n,n - 1)$ 这四个格子进行操作（至多反转两个格子的值），使得从起点出发按同一种数字（$0$ 或 $1$）的路径无法到达终点。具体做法是让 $(1,2)$ 与 $(2,1)$ 的值相同，$(n - 1,n)$ 与 $(n,n - 1)$ 的值相同，且这两组的值不同。各题解主要围绕这四个格子的值的不同情况进行分类讨论，从而确定需要反转的格子。不同题解在代码实现的细节、变量命名、空间使用等方面存在差异，但整体思路一致。

### 所选的题解
#### 作者：_ztyqwq (5星)
- **关键亮点**：思路清晰，直接围绕关键的四个格子展开讨论，代码简洁明了，通过 `if - else` 语句清晰地处理各种情况。
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[201];
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            cin >> s[i];
        if(s[0][1] == s[1][0])
        {
            printf("%d\n", (s[0][1] == s[n - 1][n - 2]) + (s[0][1] == s[n - 2][n - 1]));
            if(s[n - 1][n - 2] == s[0][1])
                printf("%d %d\n", n, n - 1);
            if(s[n - 2][n - 1] == s[0][1])
                printf("%d %d\n", n - 1, n);
        }
        else if(s[n - 1][n - 2] == s[n - 2][n - 1])
        {
            printf("%d\n", (s[n - 1][n - 2] == s[0][1]) + (s[n - 1][n - 2] == s[1][0]));
            if (s[n - 1][n - 2] == s[0][1])
                printf("%d %d\n", 1, 2);
            if (s[n - 2][n - 1] == s[1][0])
                printf("%d %d\n", 2, 1);
        }
        else
        {
            printf("2\n");
            printf("1 2\n");
            if(s[n - 1][n - 2] == s[1][0])
                printf("%d %d\n", n, n - 1);
            if(s[n - 2][n - 1] == s[1][0])
                printf("%d %d\n", n - 1, n);
        }
    }
    return 0;
}
```
核心实现思想：先判断起点相邻两格 $(s[0][1]$ 与 $s[1][0])$ 是否相等，若相等则判断终点相邻两格与它们是否相等，根据情况确定需反转的格子及数量；若起点相邻两格不相等，再判断终点相邻两格是否相等，同样根据情况确定反转方案。

#### 作者：littlebug (4星)
- **关键亮点**：代码结构清晰，使用 `pair` 来存储相关格子的值，逻辑较为紧凑，通过 `if - else` 语句完成不同情况的处理。
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
//#define int long long
#define pii pair<int,int>
#define st first
#define nd second
#define mp make_pair
#define il inline
#define pb emplace_back
using namespace std;

const int MAXN=200+5;
int n;
char p[MAXN][MAXN];
vector < pii > ans;

il void solve()
{
    ans.clear();

    cin>>n;
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) cin>>p[i][j];

    pair <char,char> s=mp(p[1][2],p[2][1]),t=mp(p[n-1][n],p[n][n-1]);
    if(s.st==s.nd)
    {
        if(t.st==s.st) ans.pb(n-1,n);
        if(t.nd==s.st) ans.pb(n,n-1);
    }
    else if(t.st==t.nd)
    {
        if(s.st==t.st) ans.pb(1,2);
        if(s.nd==t.st) ans.pb(2,1);
    }
    else
    {
        if (s.st == '1') ans.pb(1, 2);
        else ans.pb(2, 1);
        if (t.st == '0') ans.pb(n - 1, n);
        else ans.pb(n, n - 1);
    }
    cout<<ans.size()<<'\n';
    for(auto i:ans) cout<<i.st<<' '<<i.nd<<'\n';

    return;
}

signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```
核心实现思想：先将起点相邻两格和终点相邻两格的值分别存入 `pair` 中，然后判断起点相邻两格的值是否相等，若相等再判断终点相邻两格的值与起点相邻两格的值的关系，确定是否需要反转终点相邻的格子；若起点相邻两格的值不相等，再判断终点相邻两格的值是否相等，进而确定需要反转的起点相邻的格子。最后输出反转的格子数量及坐标。

#### 作者：vectorwyx (4星)
- **关键亮点**：将问题转化为对长度为 $4$ 的 $01$ 串的处理，思路独特，通过对不同的 $01$ 串情况进行分类讨论得出结果，代码逻辑清晰。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
    int x=0,fh=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') fh=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*fh;
}

const int maxn=205;
string a[maxn],s;

void work(){
    int n=read(),ans=0;
    fo(i,0,n-1) cin>>a[i];
    s.resize(4); 
    s[0]=a[0][1];
    s[1]=a[1][0];
    s[2]=a[n-1][n-2];
    s[3]=a[n-2][n-1];
    //s=a[0][1]+a[1][0]+a[n-1][n-2]+a[n-2][n-1];//(1,2) (2,1) (n-1,n-2) (n-2,n-1)
    //cout<<s<<endl;
    if(s=="0011"||s=="1100"){
        puts("0");
        return; 
    }
    if(s=="0000"||s=="1111"){
        puts("2");
        puts("1 2");
        puts("2 1");
        return;
    }
    if(s[0]!=s[1]){
        if(s[2]==s[3]){
            puts("1");
            if(s[0]==s[2]) puts("1 2");
            else puts("2 1");
        }else{
            puts("2");
            if(s[0]=='1') puts("1 2");
            else puts("2 1");
            if(s[2]=='0') printf("%d %d\n",n,n-1);
            else printf("%d %d\n",n-1,n); 
        }
    }else{
        puts("1");
        if(s[2]==s[0]) printf("%d %d\n",n,n-1);
        else printf("%d %d\n",n-1,n);
    }
    //puts("");
}
int main(){
    int T=read();
    while(T--){
        work();
    }
    return 0;
}
```
核心实现思想：将与起点和终点相邻的四个格子的值组成一个长度为 $4$ 的字符串 `s`，然后判断 `s` 是否已经是目标的 `0011` 或 `1100` 形式，若是则无需反转；若 `s` 是 `0000` 或 `1111` 形式，则反转起点相邻的两个格子；若起点相邻两格不同，再根据终点相邻两格是否相同来确定反转哪个起点相邻格以及是否需要反转终点相邻格；若起点相邻两格相同，则根据终点相邻格与起点相邻格的值的关系确定反转哪个终点相邻格。

### 最优关键思路或技巧
抓住与起点和终点相邻的四个关键格子，通过合理构造这四个格子的值（两组相同但组间不同）来实现阻止从起点到终点的同数字路径。这种思维方式将复杂的网格路径问题简化为对四个特定位置的处理，极大降低了问题的复杂度。同时，在代码实现上，清晰的分类讨论结构有助于准确处理各种可能的初始状态。

### 拓展思路
同类型题通常围绕网格路径限制与条件修改展开，类似算法套路是寻找关键位置或元素，通过对其进行操作来满足题目要求。例如给定网格中某些特殊点的限制，要求通过有限次操作改变网格状态，使得满足特定的行走规则或无法完成特定路径。

### 洛谷相似题目
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及策略构造，与本题通过构造特定状态来满足条件类似。
- [P1339 热浪](https://www.luogu.com.cn/problem/P1339)：虽然是最短路问题，但同样是在网格（地图）环境下，通过特定规则（路径限制）来求解，和本题有一定相似的思考方向。
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：在序列或网格上通过一定规则寻找满足条件的解，与本题在特定区域内构造满足条件的状态有类似的思维过程。 

---
处理用时：137.71秒