# 题目信息

# Tiles Comeback

## 题目描述

Vlad remembered that he had a series of $ n $ tiles and a number $ k $ . The tiles were numbered from left to right, and the $ i $ -th tile had colour $ c_i $ .

If you stand on the first tile and start jumping any number of tiles right, you can get a path of length $ p $ . The length of the path is the number of tiles you stood on.

Vlad wants to see if it is possible to get a path of length $ p $ such that:

- it ends at tile with index $ n $ ;
- $ p $ is divisible by $ k $
- the path is divided into blocks of length exactly $ k $ each;
- tiles in each block have the same colour, the colors in adjacent blocks are not necessarily different.

For example, let $ n = 14 $ , $ k = 3 $ .

The colours of the tiles are contained in the array $ c $ = \[ $ \color{red}{1}, \color{violet}{2}, \color{red}{1}, \color{red}{1}, \color{gray}{7}, \color{orange}{5}, \color{green}{3}, \color{green}{3}, \color{red}{1}, \color{green}{3}, \color{blue}{4}, \color{blue}{4}, \color{violet}{2}, \color{blue}{4} $ \]. Then we can construct a path of length $ 6 $ consisting of $ 2 $ blocks:

 $ \color{red}{c_1} \rightarrow \color{red}{c_3} \rightarrow \color{red}{c_4} \rightarrow \color{blue}{c_{11}} \rightarrow \color{blue}{c_{12}} \rightarrow \color{blue}{c_{14}} $

All tiles from the $ 1 $ -st block will have colour $ \color{red}{\textbf{1}} $ , from the $ 2 $ -nd block will have colour $ \color{blue}{\textbf{4}} $ .

It is also possible to construct a path of length $ 9 $ in this example, in which all tiles from the $ 1 $ -st block will have colour $ \color{red}{\textbf{1}} $ , from the $ 2 $ -nd block will have colour $ \color{green}{\textbf{3}} $ , and from the $ 3 $ -rd block will have colour $ \color{blue}{\textbf{4}} $ .

## 说明/提示

In the first test case, you can jump from the first tile to the last tile;

The second test case is explained in the problem statement.

## 样例 #1

### 输入

```
10
4 2
1 1 1 1
14 3
1 2 1 1 7 5 3 3 1 3 4 4 2 4
3 3
3 1 3
10 4
1 2 1 2 1 2 1 2 1 2
6 2
1 3 4 1 6 6
2 2
1 1
4 2
2 1 1 1
2 1
1 2
3 2
2 2 2
4 1
1 1 2 2```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
YES
YES```

# AI分析结果

### 题目翻译
Vlad 记得他有一系列 $n$ 个瓷砖和一个数字 $k$。瓷砖从左到右依次编号，第 $i$ 个瓷砖的颜色为 $c_i$。

如果你站在第一块瓷砖上，开始向右跳任意数量的瓷砖，你可以得到一条长度为 $p$ 的路径。路径的长度就是你所站过的瓷砖的数量。

Vlad 想知道是否有可能得到一条长度为 $p$ 的路径，使得：
- 路径结束于编号为 $n$ 的瓷砖；
- $p$ 能被 $k$ 整除；
- 路径被分成若干个长度恰好为 $k$ 的块；
- 每个块中的瓷砖颜色相同，相邻块的颜色不一定不同。

例如，设 $n = 14$，$k = 3$。

瓷砖的颜色包含在数组 $c$ = [ $ \color{red}{1}, \color{violet}{2}, \color{red}{1}, \color{red}{1}, \color{gray}{7}, \color{orange}{5}, \color{green}{3}, \color{green}{3}, \color{red}{1}, \color{green}{3}, \color{blue}{4}, \color{blue}{4}, \color{violet}{2}, \color{blue}{4} $ ] 中。那么我们可以构造一条长度为 $6$ 的路径，由 $2$ 个块组成：

$ \color{red}{c_1} \rightarrow \color{red}{c_3} \rightarrow \color{red}{c_4} \rightarrow \color{blue}{c_{11}} \rightarrow \color{blue}{c_{12}} \rightarrow \color{blue}{c_{14}} $

第一个块中的所有瓷砖颜色为 $ \color{red}{\textbf{1}} $，第二个块中的所有瓷砖颜色为 $ \color{blue}{\textbf{4}} $。

在这个例子中，也可以构造一条长度为 $9$ 的路径，其中第一个块中的所有瓷砖颜色为 $ \color{red}{\textbf{1}} $，第二个块中的所有瓷砖颜色为 $ \color{green}{\textbf{3}} $，第三个块中的所有瓷砖颜色为 $ \color{blue}{\textbf{4}} $。

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是围绕贪心算法展开，因为路径必须包含起点和终点，所以重点考虑起点和终点瓷砖的颜色情况。主要分为两种情况讨论：
1. **起点和终点颜色相同**：统计该颜色瓷砖的数量，若数量大于等于 $k$，则存在可行路径。
2. **起点和终点颜色不同**：先从起点开始找 $k$ 个与起点颜色相同的瓷砖，记录最后一个的位置，再从该位置往后找 $k$ 个与终点颜色相同的瓷砖，若能找到则存在可行路径。

各题解的算法要点基本一致，主要区别在于代码实现的细节和方式。解决的难点在于如何正确处理两种情况的判断逻辑，以及避免路径中不同颜色块的交叉。

### 所选题解
- **作者：xiazha (赞：9)，4星**
    - **关键亮点**：思路清晰，将问题分为两种情况详细讨论，代码实现简洁明了，注释较少但逻辑清晰。
- **作者：WsW_ (赞：3)，4星**
    - **关键亮点**：对题意理解准确，先手玩例子帮助理解，思路阐述清晰，代码有提交记录证明其正确性。
- **作者：信息向阳花木 (赞：2)，4星**
    - **关键亮点**：明确指出判断条件，考虑到路径区间不能有交集的情况，代码中使用了输入输出优化。

### 重点代码
#### 作者：xiazha
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200002],cnt,id,f;
signed main()
{
    cin>>t;
    while(t--)
    {
        cnt=0,id=-1,f=0;
        cin>>n>>k;
        for(int i=1;i<=n;i++) 
        {
            if(cnt==k&&f==0) id=i,f=1;
            scanf("%d",&a[i]);
            if(a[i]==a[1]) cnt++;
        }
        if(a[1]==a[n]&&cnt>=k)
        {
            puts("YES");
            continue;
        }
        if(id==-1) puts("NO");
        else
        {
            cnt=0;
            for(int i=id;i<=n;i++)
                if(a[i]==a[n]) cnt++;
            if(cnt>=k) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}
```
**核心实现思想**：先统计与起点颜色相同的瓷砖数量，当数量达到 $k$ 时记录位置。若起点和终点颜色相同且数量足够则输出 `YES`，否则从记录位置往后统计与终点颜色相同的瓷砖数量，若数量足够则输出 `YES`，否则输出 `NO`。

#### 作者：WsW_
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,k;
int a[200003];
int cntf,cntl;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        cntf=cntl=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        int j;
        for(j=1;j<=n&&cntf<k;j++){
            if(a[j]==a[1])cntf++;
        }
        for(;j<=n&&cntl<k;j++){
            if(a[j]==a[n])cntl++;
        }
        if((cntf==k&&cntl==k)||(cntf==k&&a[1]==a[n]))puts("Yes");
        else puts("No");
    }
    return 0;
}
```
**核心实现思想**：先从前往后统计与起点颜色相同的瓷砖数量，达到 $k$ 后继续往后统计与终点颜色相同的瓷砖数量，最后根据两种情况的判断条件输出结果。

#### 作者：信息向阳花木
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 200010;

inline void in(int &x)
{
    x = 0; bool f = 0; char c = getchar();
    while(c < '0' || c > '9')
    {
        if(c == '-') f = 1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c & 15);
        c = getchar();
    }
    x = f ? -x : x;
}

inline void out(int x)
{
    if(x < 0) putchar('-'), x = -x;
    if(x / 10) out(x / 10);
    putchar((x % 10) | 48);
}

int t, n, k;
int a[N], b[N];

int main()
{
    in(t);
    while (t -- )
    {
        memset(b, 0, sizeof b);
         
        int j = 0;
        in(n); in(k);
        for (int i = 1; i <= n; i ++ )
        {
            in(a[i]);
            b[a[i]] ++;
            if(b[a[1]] == k &&j == 0) j = i + 1;
        }
        
        if(a[n] != a[1])
        {
            b[a[n]] = 0;
            for (int i = j; i <= n; i ++ ) b[a[i]] ++;
        }
        
        if(j == 0) puts("NO");
        else if(b[a[n]] >= k && b[a[1]] >= k) puts("YES");
        else puts("NO");
    }
    return 0;
}
```
**核心实现思想**：使用数组 $b$ 统计每种颜色的瓷砖数量，当与起点颜色相同的瓷砖数量达到 $k$ 时记录位置。若起点和终点颜色不同，重新统计终点颜色的瓷砖数量，最后根据数量判断是否输出 `YES`。

### 最优关键思路或技巧
- **贪心策略**：只关注起点和终点的颜色，忽略中间的颜色，简化问题。
- **分类讨论**：将问题分为起点和终点颜色相同和不同两种情况，分别处理。

### 可拓展之处
同类型题或类似算法套路：
- 这类贪心问题通常需要抓住问题的关键条件，忽略无关信息，进行分类讨论。
- 可以拓展到其他路径选择问题，如在二维平面上的路径选择，同样需要满足一定的条件。

### 推荐题目
- [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录与总结
- **作者：_Only_this**：“一眼觉得这题好复杂，没有头绪，但是手搓一下样例就会发现，无非就两种情况。” 总结：对于复杂问题，可以通过手搓样例来寻找规律，简化问题。
- **作者：Wf_yjqd**：“又掉大分哩。好吧，这个题也很水啊。” 总结：即使觉得题目简单，也不能掉以轻心，在比赛中要保持良好的状态。

---
处理用时：53.77秒