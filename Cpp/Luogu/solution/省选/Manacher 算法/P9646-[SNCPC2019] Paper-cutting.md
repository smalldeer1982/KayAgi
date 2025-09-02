# [SNCPC2019] Paper-cutting

## 题目描述

剪纸是中国最古老、最受欢迎的民间艺术之一。它在地理上可以分为南方风格和北方风格。以江苏扬州、浙江乐清作品为代表的南方风格，设计巧妙美观，雕刻精美，造型有趣。北方风格以河北蔚县、丰宁为主体，以陕北作品为代表，造型夸张、气势恢宏、刻画生动、图案多样。

基本的裁剪由单个图像组成，还有对称的设计，通常是通过在成比例的折痕上折叠，然后裁成一个形状，当展开时，就形成了对称的设计。中国剪纸通常是对称的。剪纸通常是 $2$、 $4$ 、 $24$ 等偶数系列。

你会得到一张大小为 $n \times m$ 的纸， 它被划分为 $n \times m$ 个大小为 $1 \times 1$ 的块在。这张纸可以按以下方式折叠：

- 可以在两列之间选择一条垂直线，也可以在两行之间选择一条水平线。这条线把纸分成两面。

- 你用这条线作为对称轴，把小的一面折到大的一面上。如果纸的两面大小相等，从两边对折。

你想用这张纸做一幅剪纸杰作。首先，使用上述方法将纸张折叠几次（包括零次）。然后你用剪刀剪纸。每次剪切时，都可以从折叠的纸上剪切出一个连接的部分（即使从外面无法接触到该部分并将其扔掉。请注意，如果两个 $ 1\times 1$ 的块共享一条边，则它们是连接的。

纸张的最终外观是一个包含 $0$ 和 $1$ 的大小为 $n \times m$ 的矩阵，你想知道需要使用剪刀时的最小裁剪次数。

## 说明/提示

对于样例一,你可以通过这种方式将唯一的 $0$ 剪出:
$$\begin{array}{ccc|cc} 1&1&0&0&1\\1&1&0&0&1\end{array} \to \begin{array}{ccc} 1&1&0\\ \hline 1&1&0\end{array} \to \begin{array}{ccc} 1&1&0\end{array}$$

对于样例二，你可以按照以下方式折叠并裁剪出 $0$ 的 $4$ 个连通块：
$$\begin{array}{cccc|ccc} 1&0&0&1&1&0&0\\0&1&1&0&0&1&1\\0&1&0&1&1&0&1\\0&0&1&0&0&1&0\\1&0&0&0&0&0&0\end{array} \to \begin{array}{cccc} 1&0&0&1\\0&1&1&0\\0&1&0&1\\0&0&1&0\\1&0&0&0\end{array}$$

## 样例 #1

### 输入

```
3
2 5
11001
11001
5 7
1001100
0110011
0101101
0010010
1000000
3 2
11
11
11```

### 输出

```
1
4
0```

# 题解

## 作者：jjsnam (赞：6)

蛮有意思的一道题，但是也不是很难想（因为我自己一次切掉了），很久没有写过题解了，于是这次想写一下。

## 分析

根据题目描述和样例解释，我们不难发现，答案的求解方式应该是把输入给出的 $01$ 矩阵经过若干次折叠（需要折叠部分相对折叠轴完全对称），然后统计出值为 $0$ 的连通块的个数。所有这样操作后的结果的最小值即为答案。

下图应该能帮助理解解题步骤：

![解题操作的图片解释](https://cdn.luogu.com.cn/upload/image_hosting/6e8kyx1s.png)

那么按照上面的分析，这道题目的解法大致可以以下几个部分：

1. 找对称矩阵块和对称轴
2. 确定进行几次怎样的折叠
3. 统计折叠最后所剩图形中 $0$ 连通块的总数

## 解答

我们来看看上述三个部分应该怎样解决。

**第三个部分**是最容易的，连通块用一个 ```BFS``` 即可解决。

**第一个部分**呢？对称轴的横竖是类似的，我们现在来看竖对称轴的情况：

参照上文图片容易发现，对称矩阵块的每一行单独构成了一个回文串，因而我们可以知道，每个竖对称轴所管的对称矩阵块宽度就是每一行以该轴为中心的回文串的半径的最小值。对每一行（横对称轴则为列）跑 ```Manacher``` 算法即可解决。

**第二个部分**是本题比较难的一点。我们不知道应该怎么折叠，也不知道应该折叠多少，如果枚举的话方案数太多肯定不是我们想要的复杂度。因而我们需要深入思考折叠操作，也就是解决下面两个个问题：

- **能折叠的情况下，折叠一定比不折叠更优吗？**

  **对**。最后答案的统计来自于剩余图形的 $0$ 连通块总数，因而我们只需要考虑折叠前后 $0$ 联通块的变化：

  - 对于被折叠轴穿过的连通块：折叠后连通块面积减半，但是不影响连通块总数。
  - 对于不被折叠轴穿过的连通块：如果它在折叠后被保留，那么连通块总数不变；如果他在折叠后被折到背面（也就是被舍弃）那么连通块总数会减少。

  综上，折叠一定不会让连通块总数增多。故而**能折叠就折叠**的策略，既**方便我们代码实现**，也**不会影响我们找到最优解**。

- **横折叠和竖折叠会相互影响吗？**

  **不会**。还是只考虑竖折叠轴的情况，结合下图：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/nus9det4.png)

  从竖折叠轴考虑，蓝色的横折叠的折叠轴两侧的 $01$ 矩阵是相同的，也就是他们提供给竖折叠的回文串半径信息是相同的，蓝色折叠不折叠都会保留一份完整的回文串半径信息，不会影响竖折叠对于对称矩阵块的决策。

  因而我们在实现的时候就可以采用**先把一个方向全部折叠，再折另一个方向**的策略，这也是易于我们代码实现的。

这样三个部分就比较明了了，再来考虑一些代码实现的细节。

## 实现细节

- 在实现时，我们应该保留一个完整的矩形块，因而我们可以选择在折叠时都删除偏向外侧的那层矩阵块。如下图：
  ![](https://cdn.luogu.com.cn/upload/image_hosting/mfjpsir3.png)

  因而我们可以设置四个指针代表被保留的矩阵块的横纵边界，折叠时只需要把相应指针移到对称轴的位置即可不断进行『折叠』操作。

- 根据题目描述，可以发现折叠的对称轴，也就是回文串的对称中心，都是数字之间而不是数字，也就是说我们实现 ```Manacher``` 算法时只需要求解**偶回文串**即可。

- 有了每个折叠轴对应的最大对称矩阵块，根据上面的实现准备，什么条件需要被满足来保证折叠的合法性和有效性？（以竖左边界为例）

  - 其中**一个最大对称块需要包含从竖左边界到折叠轴的所有部分**。
  - **折叠轴需要在竖左右边界的中间左侧**（否则移动竖左边界的操作是不合法的，因为此时左侧的矩阵包含了除被折叠的对称块以外更多的矩阵部分）。

- 还是以竖左边界为例，我们在枚举对称轴的时候应该从左往右枚举还是从右往左枚举？

  从左往右，广泛来说就是**由边界向中心移动的方向**。这是因为大的折叠后保留的矩阵部分不会被之前进行的小折叠所影响，同时小折叠的进行也有可能导致新的大折叠出现。

  e.g. ```011000010``` 现在从左看最大的折叠应该是 ```01|1000010```->```1000010```（**另一个更大的由于超出了折叠轴在左半部分的限制，是不能被考虑的**），但是如果将小折叠折上，就会有 ```01|1000010```->```1000010```->```100|0010```->```0010```。


- 由于没有明确的 $n, m$ 范围，因而本题用动态数组是一个合理的选择。

## 代码实现

上述就是我做这道题时的一些思考，供大家参考。其他就没什么大问题了的，最后的总复杂度就是 $O(\sum{n\times m})$，下面是代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int n, m, T;

void manacher(string s, vector<int> &p){// 第一部分
    int len = s.size();
    int mid = 0, R = 0;
    for (int i = 0; i < len; i ++){
        int j = mid * 2 - i;
        if (i < R){
            p[i] = min(p[j], R - i);
        }
        else p[i] = 0;
        while (i - p[i] >= 0 && i + p[i] + 1 < len && s[i - p[i]] == s[i + p[i] + 1]) p[i] ++;
        if (i + p[i] > R){
            mid = i, R = i + p[i];
        }
    }
}

void BFS(int ux, int uy, int xl, int xr, int yl, int yr, vector< vector<bool> > &vis, string *s){// 第三部分
    queue<PII> q;
    q.push(make_pair(ux, uy));
    while (!q.empty()){
        auto [ux, uy] = q.front();
        q.pop();
        vis[ux][uy] = true;
        for (int i = 0; i < 4; i ++){
            int vx = ux + dx[i], vy = uy + dy[i];
            if (vx < xl || vx > xr || vy < yl || vy > yr || vis[vx][vy] || s[vx][vy] == '1') continue;
            q.push(make_pair(vx, vy));
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --){
        cin >> n >> m;
        string s[n], t[m];
        for (int i = 0; i < n; i ++){
            cin >> s[i];
        }
        for (int i = 0; i < m; i ++){
            for (int j = 0; j < n; j ++){
                t[i].push_back(s[j][i]);
            }
        }
        vector< vector<int> > rowp(n, vector<int>(m)), colp(m, vector<int>(n)); // 行、列manacher的p数组
        for (int i = 0; i < n; i ++){
            manacher(s[i], rowp[i]);
        }
        for (int i = 0; i < m; i ++){
            manacher(t[i], colp[i]);
        }

        int xl = 0, xr = n - 1, yl = 0, yr = m - 1;// 横左、横右、竖左、竖右边界
        // 求横左
        for (int i = xl; i * 2 < xl + xr; i ++){
            int p = INF;
            for (int j = 0; j < m; j ++){
                p = min(p, colp[j][i]);
            }
            if (i - p + 1 > xl) continue;
            xl = i + 1;
        }
        // 求横右
        for (int i = xr; i * 2 >= xl + xr - 1; i --){
            int p = INF;
            for (int j = 0; j < m; j ++){
                p = min(p, colp[j][i]);
            }
            if (i + p < xr) continue;
            xr = i;
        }
        // 求竖左
        for (int i = yl; i * 2 < yl + yr; i ++){
            int p = INF;
            for (int j = 0; j < n; j ++){
                p = min(p, rowp[j][i]);
            }
            if (i - p + 1 > yl) continue;
            yl = i + 1;
        }
        // 求竖右
        for (int i = yr; i * 2 >= yl + yr - 1; i --){
            int p = INF;
            for (int j = 0; j < n; j ++){
                p = min(p, rowp[j][i]);
            }
            if (i + p < yr) continue;
            yr = i;
        }

        // 统计答案
        vector< vector<bool> > vis(n, vector<bool>(m));
        int ans = 0;
        for (int i = xl; i <= xr; i ++){
            for (int j = yl; j <= yr; j ++){
                if (s[i][j] == '1' || vis[i][j]) continue;
                ans ++, BFS(i, j, xl, xr, yl, yr, vis, s);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
```

谢谢观看，有任何疑问也欢迎与我讨论！

---

## 作者：ysl_wf (赞：6)

# 【SNCPC2019】Paper-cutting【保姆级】

## 前置题目
[【模版】manacher](https://www.luogu.com.cn/problem/P3805)

## 分析问题

### 时间复杂度
$O(T n m)$ 

### 简化题目

> 给定一个 01 矩阵，上下左右尽量对折，最终剩下的区块计算有多少个 0 的连通块（只允许“上下左右”连通）。


### Think-1 折
本题的所提到的“对折”的本质其实就是 **回文字符串** 的一半部分被对折。

因此，诸位想到的“第一步”一定是将矩阵从“上下左右”疯狂对折，没错，你是正确的！

### Solve-1
如果你完成了[【模版】manacher](https://www.luogu.com.cn/problem/P3805)，那你应该知道有一个概念叫做 **回文半径**。

这里我们用 $p_i$ 来表示：位置的最大回文半径，就是以 $i$ 位置为中心，向左右对称扩展，最多能扩展几格。

模版题中的样例只有一行，而我们这里是一个 **矩形**，是有多行的字符串！

这时，我们引入一个新的概念数组：$min_p[i]$。

$min_p[i]$ 表示：第 $i$ 列的最大公共回文半径。

求解这个数组时，请不要开二维数组，一是空间，二是时间，因此，我们可以在每次进入 Manacher 函数时，将定义为 **全局变量** 每次都取 min 就可以啦。

#### Partial Code
```cpp
const int N = 1e6 + 10;
int min_p[N*2], min_pt[N*2];//因为 上下 左右 均翻折，故设置两个！！！

void manacher(string s, int min_p[]){
    //...  Part Of Mnancher

    for(int i = 0; i <= 2*len; i++) 
        min_p[i] = min(min_p[i], p[i]);
    
    /* 
    memset(mncs, '\0', sizeof(char) * (len*2+1)); 
    memset(p, 0, sizeof(int) * (len*2+1)); 
    --清空操作
    这里我放到了主函数，请注意！
    */
}
```

有了它，你便可以，你便可以愉快地进行翻折的操作！

#### 先上代码！
```cpp
//从右往左翻
lr = csl-1;// csl 表示右边界
for(int i = csl-1; i >= 0; i--){
    if(i+min_p[i] >= lr && i % 2 == 0 /* 保证折的位置是'#',因为折不可以折数字！ */) lr = i;
} lr--;//让它变成数字位置
```

关键：
$$
i \pm min_p[i] \ge l \text{（} l \text{ 指折的位置）}
$$

只要 $i$ 所在位置的回文半径 **超过** 了上一次折的边界，那么，这个位置也就是“折”的位置，记得进行“上下左右”四次！

又因为 $min_p$ 数组是建立在 Manacher 算法中创建的加了 **#** 的字符串数组下进行，所以 $i \equiv 0 \pmod 2$ 一定是 **#** 号的位置（折纸位置）！

又所以，最后我们求得了：

> $lr$（右边折后位置），$lf$（左边折后位置），$lo$（上边折后位置），$lu$（下边折后位置）。

- 注：记得将他们转化成原数组的位置！！！

### Think-2 找
那么，诸位接下来的“第一反应”一定是 bfs！

> 从“折后区间”的开始位置找 0，找到就看它“连着”几个 0，然后打标记。

### Solve
那我们不如优化一下，就像“种萝卜”一样，在 bfs 的过程中，遇到 $0$ 我们就把它变成 $1$！

#### Partial Code
```cpp
const int dx[4] = {1, 0, -1, 0}; // 移列
const int dy[4] = {0, -1, 0, 1}; // 移行

void dfs(int i, int j){// 第 i 行, 第 j 列
    s[i][j] = '1';  num--;  if(!num) return ;
    for(int c = 0; c < 4; c++){
        if(i + dy[c] >= lo && i + dy[c] <= lu && j + dx[c] >= lf && j + dx[c] <= lr && s[i + dy[c]][j + dx[c]] == '0') 
            { dfs(i + dy[c], j + dx[c]); }
    }
    return ;
}
```

如果看到这里，我相信，你一定懂得一二了！！！

## 猜你心，解你疑
> 是否考虑对折部分的长度大小，优先折大的 $min_p[i]$？

- 答：多虑了。如果倒着想，最后折出来的区间一定是 **唯一** 的！所以顺序是无所谓的！

- 总结：无论你心中的折的顺序的之类的问题，请明白：

> 最后折出来的区间一定是“唯一”的！

## 特别注意！！！
- 如果你是正常的 memset，一定会出现 TLE，因为 $2 \cdot N$ 太大了，会有许多的 **浪费清空**！！！

可以像这样：
```cpp
memset(min_p, 0x3f, sizeof(int) * (2*m+1));
```

不为难你，我告诉你清空的变量：$ans$，$min_p$，$p$，$mncs$（其中 $p$ 和 $mncs$ 是每次 Manacher 时都要清空！！！）

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 1e6 + 10;
const int dx[4] = {1, 0, -1, 0}; // 移列
const int dy[4] = {0, -1, 0, 1}; // 移行
int T, n, m, min_p[N*2], min_pt[N*2], lf, lr, lo, lu, num;// n 行 m 列
string s[N], st[N]/*反转后的串*/;
int ans = 0;
char mncs[N*2]; int p[N*2];

void manacher(string s, int min_p[]){
    // memset(mncs, '\0', sizeof(mncs)); memset(p, 0, sizeof(p));
    int len = s.size();
    mncs[0] = '#';
    for(int i = 0; i < len; i++){
        mncs[i*2+1] = s[i];
        mncs[i*2+2] = '#';
    }

    int mid, r = -1;
    for(int i = 0; i <= 2*len; i++){
        p[i] = (i <= r) ? min(p[2*mid-i], r-i) : 0;
        while(p[i] < i && mncs[i-p[i]-1] == mncs[i+p[i]+1]) p[i]++;
        if(i + p[i] > r) r = i + p[i], mid = i;
    }
    for(int i = 0; i <= 2*len; i++){
        min_p[i] = min(min_p[i], p[i]);
    }
}

void dfs(int i, int j){// 第 i 行, 第 j 列
    s[i][j] = '1';  num--;  if(!num) return ;
    for(int c = 0; c < 4; c++){
        if(i + dy[c] >= lo && i + dy[c] <= lu && j + dx[c] >= lf && j + dx[c] <= lr && s[i + dy[c]][j + dx[c]] == '0') 
            { dfs(i + dy[c], j + dx[c]); }
    }
    return ;
}

int main(){
    scanf("%d", &T);
    while(T--){
        ans = 0;
        
        scanf("%d%d", &n, &m);

        memset(min_p, 0x3f, sizeof(int) * (2*m+1));
        memset(min_pt, 0x3f, sizeof(int) * (2*n+1));

        //处理min_p 以及 输入 和 翻转串 pt
        int nu = n - 1; // 翻转串 pt 的 列 = n
        for(int x = 0; x < m; x++)
            st[x].resize(n);
        for(int i = 0; i < n; i++){
            cin >> s[i];//长为 m
            for(int k = 0; k <= m*2; k++){
            	p[k] = 0;
			}
            manacher(s[i], min_p);
            for(int x = 0; x < m; x++){//这里表示 m 行 n 列
               st[x][nu] = s[i][x];
            }
            nu--;
        }
        memset(mncs, 0, sizeof(char) * (2*m+1));

        //处理min_pt
        for(int i = 0; i < m; i++){
        	for(int k = 0; k <= n*2; k++){
        		p[k] = 0;
			}
        	manacher(st[i], min_pt);
		}
        memset(mncs, 0, sizeof(char) * (2*n+1));
            

        //处理左右
        int csl = m*2+1;
        //从右往左翻
        lr = csl-1;
        for(int i = csl-1; i >= 0; i--){
            if(i+min_p[i] >= lr && i % 2 == 0 /* 保证折的位置是'#' */) lr = i;
        } lr--;//让它变成数字位置
        //从左往右折
        lf = 0;
        for(int i = 0; i < lr; i++){
            if(i-min_p[i] <= lf && i % 2 == 0) lf = i;
        } lf++;

        //处理上下
        int cslt = n*2+1;
        //从右往左折(从上往下)
        lo = cslt-1;
        for(int i = cslt-1; i >= 0; i--){
            if(i+min_pt[i] >= lo && i % 2 == 0) lo = i;
        } lo--;
        //从左往右折(从下往上)
        lu = 0;
        for(int i = 0; i < lo; i++){
            if(i-min_pt[i] <= lu && i % 2 == 0) lu = i;
        } lu++;
        lo = cslt - lo - 1; lu = cslt - lu - 1;

        //现在，我们要将 lf, lr, lo, lu 转化成"串"的 lf, lr, lo, lu
        lf = (lf+1)/2 - 1, lr = (lr+1)/2 - 1, lo = (lo+1)/2 - 1, lu = (lu+1)/2 - 1;

        num = 0;
        //dfs
        for(int i = lo; i <= lu; i++)
            for(int j = lf; j <= lr; j++)
                if(s[i][j] == '0') num++;
        if(!num) printf("0\n");
        else{
            for(int i = lo; i <= lu; i++){
                for(int j = lf; j <= lr; j++){
                    if(s[i][j] == '0'){
                        ans++;
                        dfs(i, j); // 第 i 行, 第 j 列
                    }
                    if(!num) break;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
```

## 后记
- 点赞加上关注，黄蓝勾命中注！

---

## 作者：TDoG_W (赞：3)

# [SNCPC2019]Paper-cutting
此篇题解为笔者第一篇题解

NOIp 前写题解意图于 RP++

难得一见的好题，赞。
##  前置知识
[Manacher](https://www.luogu.com.cn/problem/P3805)

[BFS 找连通块](https://www.luogu.com.cn/problem/P1596)

[二维单调队列](https://www.luogu.com.cn/problem/P2216)（仅思想）
## 分析
> 简要题意
>> 给定一 01 矩阵，以缝隙为对称轴的区块可以对折，对折后保留大的一部分，求最少的 0 连通块为多少？

首先观察样例，发现能对折的，两边区块轴对称 ~~（废话）~~ 。也就是说，如果有一块区域能横着对折，那么它的每一横行都将是偶回文串（不妨将这种区块称作“偶回文区块”），且对称轴到短的一边的长度，刚好是以对称轴为回文中心的所有最长偶回文串中，最短的那一个的长度的一半。（此处建议结合样例理解）

回忆寻找回文的算法，想到 Manacher ，但 Manacher 是序列上的算法，这里又该如何解决呢？

此题涉及 Manacher 算法的扩展应用:

$$\color{purple}{「二维Manacher」}$$

借鉴并运用二维单调队列的思想，我们只要分别对横行和竖列分别做 Manacher ，最后整合信息即可得出答案。

具体地说，横竖开一个 Manacher 数组，横 Manacher 对每一横行分别拉一遍，竖列同理。

由此，我们得到了本题的做法。

每次对横行和竖列做 Manacher ，同时更新另外开的两个偶回文最小值数组数组答案，最终即可得到整个横竖区块的“偶回文区块”

注意到数据范围 $1 \leq n \times m \leq 10^6$ 矩阵最大面积固定，但 $n, m$ 长度不固定。故须使用 vector 来动态调整大小，储存 01 矩阵。

得到“偶回文区块”后，就可以开始对折了，稍加思索，发现一张纸可能可以从上下左右四个方向对折，所以我们要根据四方的“偶回文区块”不断对折，最终会得到一个子矩阵，它的 0 连通块数将最少（证明见后）

找出子矩阵后，用 BFS 进行 0 连通块的计数，得出答案。

综上，此题做法，大致可分三个部分：

1. SEE（寻找“回文区块”,得出“偶回文区块”）
2. FOLD（折叠，即缩小矩阵,找出最终的子矩阵）
3. CUT（剪纸，即数子矩阵内 0 连通块个数）

## 疑难与解答
***以下结论皆从简论证***

$Q_1$ : 对折是否可能会增加 0 的连通块？

$A_1$ : 不可能，对折后 0 的连通块只会减少或不变（单调不增）。

- 考虑如下数据

$$
\begin{matrix}
\begin{matrix}
0 & 1 & 1 & 0\\
1 & 0 & 0 & 1\\
\end{matrix}
& \rightarrow &
\begin{matrix}
0 & 1\\
1 & 0\\
\end{matrix}\\
\color{green}{3} & \ & \color{red}{2}
\end{matrix}
$$

- 分类讨论

$\because$ 当 0 连通块越过对称轴时，对折后仍保留了半边，数量不变。

$\because$ 当 0 连通块分布在对称轴两边，对折后只保留了半边，数量减半。

$\therefore$ 综上所述，对折一定不会比不对折劣。

$Q_2$ : 若有一大对称的区块，在其边缘有一小的对称区块，先折小还是先折大有区别吗？

$A_2$ : 没有区别，最终结果是唯一的。

- 考虑如下数据

$$
\begin{matrix}
\begin{matrix}
1 & 0 & 1 & 1 & 0 & 0 & 1 & 1 & 0\\
0 & 1 & 0 & 0 & 1 & 1 & 0 & 0 & 1\\
0 & 1 & 1 & 1 & 1 & 1 & 1 & 1 & 1\\
1 & 0 & 1 & 1 & 0 & 0 & 1 & 1 & 0 
\end{matrix}
& {\rightarrow}{折大} &
\begin{matrix}
1 & 0 & 1 & 1 & 0\\
0 & 1 & 0 & 0 & 1\\
0 & 1 & 1 & 1 & 1\\
1 & 0 & 1 & 1 & 0
\end{matrix}\\
折小 \downarrow & &折小\downarrow\\
\begin{matrix}
1 & 0 & 1 & 1 & 0 & 0 & 1\\
0 & 1 & 0 & 0 & 1 & 1 & 0\\
0 & 1 & 1 & 1 & 1 & 1 & 1\\
1 & 0 & 1 & 1 & 0 & 0 & 1 
\end{matrix}
& {\rightarrow}{折大} &
\begin{matrix}
1 & 0 & 1\\
0 & 1 & 0\\
0 & 1 & 1\\
1 & 0 & 1
\end{matrix}
\end{matrix}
$$

可以发现，先折大还是先折小其实是不影响最终结果的。

- 为什么？

从简论证，因为小的对称区块实际上包括在大的对称区块里，若这边折了实际上就相当于另外一边不用折了，同时大对称轴缩短。换句话说，当我们折叠了小对称轴时，实际上就相当于已经将小的一部分先“折”过去了。

$Q_3$ : 如横竖都可对折，先折横还是先折竖有影响吗？

$A_3$ : 没有影响，最终结果是唯一的。

- 考虑如下数据

$$
\begin{matrix}
\begin{matrix}
0 & 1 & 1 & 0\\
1 & 0 & 0 & 1\\
1 & 0 & 0 & 1\\
0 & 1 & 1 & 0 
\end{matrix}
& {\rightarrow}{折横} &
\begin{matrix}
0 & 1\\
1 & 0\\
1 & 0\\
0 & 1
\end{matrix}\\
折竖 \downarrow & &折竖\downarrow\\
\begin{matrix}
0 & 1 & 1 & 0\\
1 & 0 & 0 & 1\\ 
\end{matrix}
& {\rightarrow}{折横} &
\begin{matrix}
0 & 1\\
1 & 0
\end{matrix}
\end{matrix}
$$

可以发现，先折横还是先折竖不影响最终结果的。

- 为什么？

这是。可以与向量的线性无关类比，无论其中一维怎么操作，也无法“替代”另一维的操作。

$Q_{3引}$ : 似乎还可以得到 $\begin{matrix}1 & 0\\0 & 1 \end{matrix}$ ，是否违背 $A_3$ ？

$A_{3引}$ : 注意此处所言“最终结果是唯一的”指不同操作得到的最终连通块是全等的（通过一定的翻转和旋转后重合），请有所区别。

## 代码实现细节

1. 注意 vector 的使用（ FAQ : 越界？大小？）
2. **Manacher 的答案数组每次要置零** （因为这个被[卡](https://www.luogu.com.cn/record/135405790)了一天）
3. Manacher 的答案与字符数组都要开两倍
4. 多测清空
5. 注意对折时指针与下标是否计算正确
6. vis 数组要按大小清空，否则 [#2 TLE](https://www.luogu.com.cn/record/135627797)

## LET'S FOLD&CUT!

时间复杂度 $O(TNM)$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int M=1e6+10;

int t,n,m,ans,up,down,lef,rig;
int dx[4]={1,0,-1,0},
	dy[4]={0,-1,0,1};
bool vis[M];
char c,cs[M<<1],rs[M<<1];
int col[M<<1],row[M<<1],cmin[M],rmin[M];
vector< vector<char> > paper;
string s;

struct pos{
	int x,y;
	pos(int a=0,int b=0){x=a,y=b;}
	bool law(){return x>=up and x<=down and y>=lef and y<=rig;}
	int has(){return (x-1)*m+y;}
};
queue<pos> q;

void bfs(int x,int y){
	q.push(pos(x,y));
	pos u,v;
	while(!q.empty()){
		u=q.front();
		q.pop();
		if(vis[u.has()])continue;
		vis[u.has()]=1;
		for(int i=0;i<4;i++){
			v=pos(u.x+dx[i],u.y+dy[i]);
			if(v.law() and paper[v.x][v.y]=='0' and !vis[v.has()]){
				q.push(v);
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(bool)*(n*m+1));
		cin>>n>>m;
		paper.resize(n+1);
		up=1,down=n,lef=1,rig=m;
		for(int i=1;i<m;i++)cmin[i]=INF;
		for(int i=1;i<n;i++)rmin[i]=INF;
		cs[0]='#',cs[1]='|',cs[2*m+2]='@';
		int r=0,mid=0;
		for(int i=1;i<=n;i++){
			cin>>s;
			paper[i].resize(m+1);
			for(int j=1;j<=m;j++)
				cs[2*j]=paper[i][j]=s[j-1],cs[2*j+1]='|';
			r=0,mid=0;
			for(int j=1;j<=2*m+1;j++){
				col[j]=0;
				if(j<=r)col[j]=min(col[(mid<<1)-j],r-j+1);
				while(cs[j-col[j]]==cs[j+col[j]])col[j]++;
				if(col[j]+j>r)r=col[j]+j-1,mid=j;
				if(j>=3 and j<2*m and cs[j]=='|')cmin[j/2]=min(cmin[j/2],col[j]);
			}
		}
		rs[0]='#',rs[1]='|',rs[2*n+2]='@';
		for(int i=1;i<=m;i++){
			r=0,mid=0;
			for(int j=1;j<=n;j++)
				rs[2*j]=paper[j][i],rs[2*j+1]='|';
			for(int j=1;j<=2*n+1;j++){
				row[j]=0;
				if(j<=r)row[j]=min(row[(mid<<1)-j],r-j+1);
				while(rs[j-row[j]]==rs[j+row[j]])row[j]++;
				if(row[j]+j>r)r=row[j]+j-1,mid=j;
				if(j>=3 and j<2*n and rs[j]=='|')rmin[j/2]=min(rmin[j/2],row[j]);
			}
		}
		for(int i=1;i<m;i++)cmin[i]>>=1;
		for(int i=1;i<n;i++)rmin[i]>>=1;
		for(int i=1;i<m;i++)
			if(i-cmin[i]+1<=lef)
				lef=i+1;
		for(int i=m-1;i>=lef;i--)
			if(min(i+cmin[i],(i-lef)+i)>=rig)
				rig=i;
		for(int i=1;i<n;i++)
			if(i-rmin[i]+1<=up)
				up=i+1;
		for(int i=n-1;i>=up;i--)
			if(min(i+rmin[i],(i-up)+i)>=down)
				down=i;
		ans=0;
		for(int i=up;i<=down;i++){
			for(int j=lef;j<=rig;j++){
				if(paper[i][j]=='0' and !vis[(i-1)*m+j]){
					bfs(i,j);
					ans++;
				}
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

祝诸君 $\color{yellow}{NOIp\ RP++}$ ! ^^

---

## 作者：ZHR100102 (赞：3)

蒟蒻 2025 年切的第一道题，是个紫，并且基本独立想出的，特此纪念。

# 判断能否折叠

我们先考虑一部分能折叠需要满足什么条件。显然，这一部分需要是一个长度为偶数的回文串。

那么横向和纵向会不会影响呢？答案是不会，因为横向折了之后，折过去的部分一定是对称的，那么只要原来某两列相等，这之后这两列还是相等的。我们可以画图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/a46ntf6y.png)

相同颜色的部分代表这两部分相等。

于是，我们只需要对每行每列哈希一遍，然后利用偶数回文串折叠即可。同时我们也得出**横行和纵列互不影响**的结论。

这一部分可以用 manacher 快速求出最大折叠半径。

# 折叠策略

我们先考虑这个问题的弱化版。

## 只能折一边时

在只能折一边时，我们**一定会尽可能地折叠**。这样一定更优。

证明也是容易的，折叠前折叠部分单独的连通块会被砍掉，与剩余部分相连接的连通块因为是对称过去，所以折叠过去后一定存在一个格子使它们依然连通。

因此，**折叠后连通块的个数一定不会增加，答案也一定不劣**。同时，折叠的顺序也是无影响的，因为每次能折叠当且仅当偶数回文串内存在一个能折叠到的点。

## 两边都能折时

同样是能折就折，因为左折、右折互不影响，我们可以用分类讨论来证明。

### 右折后左折能正常进行时

显然左右都能操作。

### 右折后左折被挡住一部分时

这种情况一定不存在。

左折要被挡住，必然要满足下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/skt8yv32.png)

而橙色的左折显然不合法，这种情况等效于浅橙色部分右折。

因此**能折就折的策略一定不劣**。


# 翻折实现

对每行每列跑 manacher 记录最长回文长度后，我们考虑设计 dp。


以向左翻折为例，定义 $dp_i$ 表示以 $i$ 为最后一列是否可行，$d_i$ 为回文半径长度，则：

$$dp_i=[(\sum_{j=i+1}^{i+d_i}dp_j) >0]$$

这个式子可以用前缀和优化、单调队列优化来做，或者跟我一样维护一个最近的 $1$ 的指针也可以。~~我本来用前缀和优化做的，但是挂了几十发并且还调不出就用其他题解一样的方式维护指针了。~~

注意初始化 $dp_n=1$。

向左翻折后，从左边开始再往右翻折一遍就可以了。注意不能翻过新的右边界。

最后求出左右边界、上下边界后，进行 BFS 求出需要减掉的连通块个数即可。

时间复杂度 $O(nm)$，注意动态开数组。

# 代码

非常构式，调了 2h。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
#define eb(x) emplace_back(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
using pi=pair<int,int>;
const ull nosol1=1145141919810,nosol2=1919810114514,nosol3=1911451419810;
int n,m,x,ansxl,ansxr,ansyl,ansyr,d[2000005];
int gox[]={0,0,1,-1};
int goy[]={-1,1,0,0};
vector<int>c[1000005];
ull xhs[1000005],yhs[1000005],f[2000005];
void init(int len,ull *arr)
{
    x=0;
    f[0]=nosol1;
    f[++x]=nosol2;
    for(int i=1;i<=len;i++)f[++x]=arr[i],f[++x]=nosol2;
    f[x+1]=nosol3;
}
void manacher()
{
    for(int i=1;i<=x;i++)d[i]=0;
    d[1]=1;
    for(int i=2,l=0,r=0;i<=x;i++)
    {
        if(i<=r)d[i]=min(r-i+1,d[l+r-i]);
        while(f[i-d[i]]==f[i+d[i]])d[i]++;
        if(i+d[i]-1>r)l=i-d[i]+1,r=i+d[i]-1;
    }
}
void do_dp(int len,int &ansl,int &ansr)
{
    ansr=len;
    for(int i=len-1;i>=1;i--)
    {
        int p=i*2+1;
        int dx=d[p]/2;
        if(i+dx>=ansr)ansr=i;
    }
    ansl=1;
    for(int i=1;i<ansr;i++)
    {
        int p=i*2+1;
        int dx=d[p]/2;
        if(i-dx+1<=ansl)ansl=i+1;
    }
}
bool legal(int x,int y){return (x>=ansxl&&x<=ansxr&&y>=ansyl&&y<=ansyr);}
void bfs(int x,int y)
{
    queue<pi>q;
    q.push({x,y});
    c[x][y]=1;
    while(!q.empty())
    {
        pi u=q.front();
        q.pop();
        int nx=u.fi,ny=u.se;
        for(int i=0;i<4;i++)
        {
            int tx=nx+gox[i],ty=ny+goy[i];
            if(legal(tx,ty)&&c[tx][ty]==0)
            {
                q.push({tx,ty});
                c[tx][ty]=1;
            }
        }
    }
}
void solve()
{
    int ans=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)c[i].clear();
    for(int i=1;i<=n;i++)xhs[i]=0;
    for(int i=1;i<=m;i++)yhs[i]=0;
    for(int i=1;i<=n;i++)
    {
        c[i].eb(0);
        for(int j=1;j<=m;j++)
        {
            char tmp;
            cin>>tmp;
            int k=tmp-'0';
            xhs[i]=xhs[i]*2+k;
            yhs[j]=yhs[j]*2+k;
            c[i].eb(k);
        }
    }
    init(n,xhs);
    manacher();
    do_dp(n,ansxl,ansxr);
    init(m,yhs);
    manacher();
    do_dp(m,ansyl,ansyr);
    for(int i=ansxl;i<=ansxr;i++)
    {
        for(int j=ansyl;j<=ansyr;j++)
        {
            if(c[i][j]==0)
            {
                ans++;
                bfs(i,j);
            }
        }
    }
    cout<<ans<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Lsrh666 (赞：1)

## ${\color{Violet} \mathfrak{description} }$

**折叠**考虑**回文串**  
考虑手动处理样例：  
给定你一张 $n\times m$ 的 $01$ 矩阵，要求你尽可能地折叠，以便能够剪掉更多联通的 $0$。  
其中的剪掉操作类似于生活中的剪纸，只能从四周进行剪切，不能直接从纸的中间剪开。  

## ${\color{Violet} \mathfrak{solution} }$

根据生活经验或手动尝试，我们可以发现，当待折叠部分对称时，进行折叠是最优的。  
其正确性显而易见，或者我们可以这样感性理解：当不对称时，必定会有一些 $0$ 被不对称的 $1$ 所占据，导致无法形成更大的连通 $0$ 区域。  
于是，折叠的策略就明确了：  
尽可能地折叠回文串，并确保回文串的一边到达矩阵的边界。  
否则，我们不能称之为完整的回文串（因为一次折叠需要将左右两部分都折起来，如果不达边界，就会左右不对称）。  

此时，可能会有人问：折叠的顺序是否会影响结果？  
显然不会。  
生活经验告诉我们（应该都玩过折纸吧），无论先水平折还是先竖直折，最终剪掉的形状都是一样的。  
或者说，折叠顺序影响的只是纸和剪刀接触的是哪一面，但无论怎么剪，剪掉的都是那一块区域。  

那么，如何统计联通的 $0$ 呢？  
只需要通过暴力搜索来求解连通块即可。  
具体实现时，可以采用马拉车算法来找到所有的回文串，并进行折叠操作。  
折叠时，直接折叠插入的特殊字符所对应的部分即可。

---

## 作者：ADNAP (赞：1)

### 首先先来看看折叠的条件

假设小的那一部分折过去后，有 $0$ 和 $1$ 的部分重叠，是无法裁剪的。因此，只能是 $1$ 和 $1$ 重叠，$0$ 和 $0$ 重叠，又因为折叠的对称轴是单元格间的线，换句话说，小的一面跟大的一面的对应的部分是完全对称的，也就是回文串，并且可以发现这个回文串一定是能够的到小的一面的边界的。因为是回文串，还要对是否能够得着边界，只有够得到边界我们才能折叠，所以我们使用 Manacher 算法。

### 接下来是折叠之后的等价情况

因为小的部分折过去之后大的部分 $0$ 的部分还是 $0$，$1$ 还是 $1$ 并不影响大的部分的裁剪，而是小的部分可以在大的部分裁剪过程中顺带裁剪了，于是相当于只用裁剪大的部分。

### 那么能折叠就折叠是不是最优的？

如果我们固定折叠的对称轴，那么折叠前在对称轴两侧连接的部分减半，前后都是只用剪 $1$ 次；而对于与对称轴不连接的部分，折叠前被对称轴分成两半，需要裁剪 $2$ 次，折叠后重叠，只用剪 $1$ 次。

综上，不管是不是跟折叠的对称轴连接的裁剪部分，折叠后都不会比原来更劣，换句话说，能折叠就折叠一定是最优的策略或者最优的策略之一。

### 折叠的顺序是否影响答案？

先考虑横着折之间的顺序，竖着着同理。

假设现在有两个折叠的对称轴，将整张纸分为了 $3$ 个部分。因为折叠后等价于取最大的一面，这与顺序无关，所以横着折之间的顺序是不影响结果的。

再考虑横着折和竖着折之间的顺序。

同样的，最后保留的一面一定是长和宽最长的两边，也和折叠顺序无关。

综上，折叠的顺序是不影响答案的。

### 总而言之

我们可以先对横着折考虑，能折就折；然后对竖着折考虑，能折就折。

在折叠过程中记录最大的一面的左上角坐标和右下角下标。

最后就是求最大的一面中有多少块独立的 $0$ ，只需要用dfs染块判断即可，这样的复杂度最高是 $2nm$，也就是 $nm$ 级别，常数也不大。

### 代码实现分析

所以我们可以对于横着和竖着，先跑一遍第一个字符串的 Manacher 中的 $p_i$ ，然后后面的字符串记录在 $pp_i$ 中，只用当对于一个固定的位置 $i$，每个字符串都能够到小的一面的边界才能折叠。所以如果 $p_i$ 和 $pp_i$ 是不一样的话，说明一定有一个是小的，一定有一个够不到边界，这时我们把 $p_i$ 记为 $0$，表示这个位置不可能作为折叠的对称轴。最后从左到右跑一遍 $p$ 数组，如果有能够够到边界的位置，则折叠，并且更新最大的一面的左上角和右下角的坐标。

当然，这得注意的是 Manacher 算法是从左到右更新答案数组的，没有后效性，不需要清空答案数组，清空了也会 [TLE](https://www.luogu.com.cn/record/147417246)。

最后dfs一遍我们就可以得到答案了

然后，我们就发现 [TLE](https://www.luogu.com.cn/record/147414866) 了。

原因是，我们在折叠的过程中是从左到右折叠的，如果每次只折一点点， Manacher 就会跑很多次，造成了时间复杂度为 $O(Tn^2m^2)$，确实可以造成超时，于是我们添加以下优化：

每次从中间开始找折叠的位置，这样理想情况是每次能够对半折，不仅折叠的次数减少了，跑 Manacher 也更快了，都是 $logn$ 级别，总时间复杂度是 $O(Tnm)$。

### Code
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
#define x first
#define y second
const ll N=1e5+1e4,M=1e3+1e2;
ll T;
ll n,m;
string s[N*20];
//不要用char，n和m的大小可能不均衡
char b[N*20];
ll p[N*20];
ll pp[N*20];
PLL p1,p2;
//分别记录最大的一面的左上角和右下角的坐标
ll k;
void init(ll res)
{
    b[k++]='$',b[k++]='#';
    for(ll i=p1.y-1;i<p2.y;i++)b[k++]=s[res][i],b[k++]='#';
    b[k++]='^';
}
void init2(ll res)
{
    b[k++]='$',b[k++]='#';
    for(ll i=p1.x;i<=p2.x;i++)b[k++]=s[i][res],b[k++]='#';
    b[k++]='^';
}
void manacher(ll res)
{
    ll mr=0,mid;
    if(res==p1.x)
    {
        for(ll i=1;i<k;i++)
        {
            if(i<mr)p[i]=min(p[mid*2-i],mr-i);
            else p[i]=1;
            while(b[i-p[i]]==b[i+p[i]])p[i]++;
            if(i+p[i]>mr)
            {
                mr=i+p[i];
                mid=i;
            }
        }
    }
    else
    {
        for(ll i=1;i<k;i++)
        {
            if(i<mr)pp[i]=min(pp[mid*2-i],mr-i);
            else pp[i]=1;
            while(b[i-pp[i]]==b[i+pp[i]])pp[i]++;
            if(i+pp[i]>mr)
            {
                mr=i+pp[i];
                mid=i;
            }
        }
        for(ll i=1;i<k;i++)
            if(p[i]!=pp[i])p[i]=1;
    }
}//manacher模版
void manacher2(ll res)
{
    ll mr=0,mid;
    if(res==p1.y-1)
    {
        for(ll i=1;i<k;i++)
        {
            if(i<mr)p[i]=min(p[mid*2-i],mr-i);
            else p[i]=1;
            while(b[i-p[i]]==b[i+p[i]])p[i]++;
            if(i+p[i]>mr)
            {
                mr=i+p[i];
                mid=i;
            }
        }
    }
    else
    {
        for(ll i=1;i<k;i++)
        {
            if(i<mr)pp[i]=min(pp[mid*2-i],mr-i);
            else pp[i]=1;
            while(b[i-pp[i]]==b[i+pp[i]])pp[i]++;
            if(i+pp[i]>mr)
            {
                mr=i+pp[i];
                mid=i;
            }
        }
        for(ll i=1;i<k;i++)
            if(p[i]!=pp[i])p[i]=1;
    }
}
void dfs(ll xx,ll yy)
{
	if(xx<p1.x||xx>p2.x)return ;
	if(yy<p1.y-1||yy>p2.y-1)return ;
	if(s[xx][yy]=='1')return ;
	s[xx][yy]='1';
	dfs(xx+1,yy);
	dfs(xx-1,yy);
	dfs(xx,yy+1);
	dfs(xx,yy-1);
}//找连通块
PLL p3,p4;
ll ans;
signed main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        p1.x=1,p1.y=1;
        p2.x=n,p2.y=m;
        for(ll i=1;i<=n;i++)cin>>s[i];
        while(p1.y!=p2.y)
        {
        	k=0;
            init(p1.x);
            manacher(p1.x);
            for(ll i=p1.x+1;i<=p2.x;i++)
            {
                k=0;
                init(i);
                manacher(i);
            }
            bool flag=false;
            p3.x=p1.x,p3.y=p1.y,p4.x=p2.x,p4.y=p2.y;
            for(ll i=(k/2+1-((k/2)&1));i>=3;i-=2)
            {
                if(p[i]>=2)
                {
                    if(i-p[i]==0)
                    {
                        p1.y+=(i-1)/2;
                        flag=true;
                        goto here;
                    }
                    else if(i+p[i]==k-1)
                    {
                        p2.y=p2.y-(k-i)/2+1;
                        flag=true;
                        goto here;
                    }
                }
            }
            for(ll i=(k/2+1-((k/2)&1))+2;i<k;i+=2)
            {
                if(p[i]>=2)
                {
                    if(i-p[i]==0)
                    {
                        p1.y+=(i-1)/2;
                        flag=true;
                        goto here;
                    }
                    else if(i+p[i]==k-1)
                    {
                        p2.y=p2.y-(k-i)/2+1;
                        flag=true;
                        goto here;
                    }
                }
            }
            if(p1.x==p3.x&&p1.y==p3.y&&p2.x==p4.x&&p2.y==p4.y)break;
			if(!flag)break;
            here:;
            if(p1.x==p3.x&&p1.y==p3.y&&p2.x==p4.x&&p2.y==p4.y)break;
            //折叠不了就退出，下同
        }
        
        while(p1.x!=p2.x)
        {
            k=0;
            init2(p1.y-1);
            manacher2(p1.y-1);
            for(ll i=p1.y;i<p2.y;i++)
            {
                k=0;
                init2(i);
                manacher2(i);
            }
            bool flag=false;
            p3.x=p1.x,p3.y=p1.y,p4.x=p2.x,p4.y=p2.y;
            for(ll i=(k/2+1-((k/2)&1));i>=3;i-=2)//从中间开始找
            {
                if(p[i]>=2)
                {
                    if(i-p[i]==0)
                    {
                        p1.x+=(i-1)/2;
                        flag=true;
                        goto here2;
                    }
                    else if(i+p[i]==k-1)
                    {
                        p2.x=p2.x-(k-i)/2+1;
                        flag=true;
                        goto here2;
                    }
                }
            }
            for(ll i=(k/2+1-((k/2)&1))+2;i<k;i+=2)
            {
                if(p[i]>=2)
                {
                    if(i-p[i]==0)
                    {
                        p1.x+=(i-1)/2;
                        flag=true;
                        goto here2;
                    }
                    else if(i+p[i]==k-1)
                    {
                        p2.x=p2.x-(k-i)/2+1;
                        flag=true;
                        goto here2;
                    }
                }
            }
            if(p1.x==p3.x&&p1.y==p3.y&&p2.x==p4.x&&p2.y==p4.y)break;
		    if(!flag)break;
            here2:;
            if(p1.x==p3.x&&p1.y==p3.y&&p2.x==p4.x&&p2.y==p4.y)break;
        }
        ans=0;
        for(ll i=p1.x;i<=p2.x;i++)
        {
        	for(ll j=p1.y-1;j<p2.y;j++)
        	{
        		if(s[i][j]=='0')
        		{
        			ans++;
         			dfs(i,j);
				}
			}
		}
		cout<<ans<<"\n";
    }
}
```

---

## 作者：王江睿 (赞：1)

有一张纸，大小为 $ m \times n $。每次你会剪下一个连通区域，允许将短边翻到长边上（或者对折）。给出最终剪裁的形状（保留或不保留），求需要的最少剪裁次数（折完再剪）。

多测。保证 $ \Sigma(m \times n) \leq 1e6 $。

---

_ref: [G - Paper-cutting - SUA Wiki](https://sua.ac/wiki/2019-provincial-shaanxi/g/)_

对于 $n=1$ 的情况，设该串为 $s_i$，记号 $s[l:r]$ 表示 $[s_l,\ldots,s_r]$；$s_l$ 表示 $s_0$，$s_r$ 表示 $s_{|s|-1}$。可以发现，如果我们想要 $s[1:j]$ 向右折，需要 $s[1:j]=s[2j:j+1]$；每折一次，相当于从 $s$ 中删去了 $s[1:j]$。

一个朴素贪心策略是：凡以 $i$ 为中心的极大回文串 $T$ 满足 $T_l=s_l$ 就折起来；也即“能折就折”的方法。

下面证明对折任意回文前缀 $s[1:2q]$ 能到达的中间状态，折最短回文前缀 $s[1:2p]$ 也能到达。

1° $2p\leq q$，在第一次折完以后，因为 $s[p:q]=[s_{2q-p},\ldots,s_{q+1}]$；再折一次（绿线），达到的效果是一样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/vf8j3ltz.png)

2° $2p\geq q$，这种情况下，
$$
s[1:2p-q]\xlongequal{mid=p}[s_{2p},\ldots,s_{q+1}]\xlongequal{mid=q}s[2q-2p+1:q]\xlongequal{mid=p}[s_{4p-2q},\ldots,s_{2p-q+1}]
$$
即 $s[1:4p-2q]$ 是一个更短的回文串。

![](https://cdn.luogu.com.cn/upload/image_hosting/9hunfafk.png)


因此，“能折就折”的贪心策略是正确的。

那么，什么时候停止折纸是最优的呢？如果只折一边，一直折下去会是最优的。因为每一次折叠都会让不跨过对称中心的 2 个连通块变为 1 个。但是，如果两边一起折，会不会产生冲突呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/n6v3u9cj.png)

如图，红线从左边折，蓝线从右边折；蓝线的对称中心在红线上，产生了冲突。（读者可以想像折纸的过程以理解）    

这时候，我们发现，红线的前缀中，必然存在一个更短的回文串（黑线），它与蓝线不交。（注：我们已证明，折红线到达的中间状态黑线也能到达；但是，那是靠两次折叠完成的，用于二次折叠的回文串〔绿线〕与蓝线不交［准确地说是恰好贴合］）    

因为左右对折和上下对折互不影响（不会冲突），又因为对不同方向的折叠而言，顺序无关：我们只要分别考虑四个方向，每个方向遵循上述贪心策略，就能最小化 $0$ 的连通块数量——即题目所求。

实现时，每个方向，旋转一次矩阵。时间复杂度 $O(nm)$，时间瓶颈是暴力判断两行相等。

---

## 作者：是青白呀 (赞：1)

观察到如下两个性质：

1. 对于同一个折叠方向的所有可行折叠棱，我们能折叠就一定折叠，因为折叠不会导致可行的折棱变得不可行，但可能使某些更后方的不可行的棱变得可行。
2. 不同方向的折叠操作互不影响，即一次折叠不会导致不同方向上的某个可行折叠棱变得不可行；也不会使得某个不可行折叠棱变得可行。因此四个方向可以独立求解。

我们考虑实现 cut 和 rotate 两个函数，分别表示将目前的矩形的右侧尽可能向左内折、以及将当前矩形顺时针旋转 $90^{\circ}$。重复执行这两个操作 $4$ 次，我们就可以完成四个方向的折叠。

rotate 的实现是容易的。考虑如何实现 cut 函数。我们先对每一行跑 manacher，求出每一个间隙对应的最长回文半径，$d_i$ 表示 $i$ 这一列**右侧**的空隙对应的最长回文半径。再对同列的 $d_i$ 取 $\min$，得到一条完整间隔的最长回文半径 $mind_i$。考虑从右往左扫描每一列，动态维护当前矩形的右边界对应列数 $r$，每当我们扫到一个 $i+mind_i\geq r$，就说明可以以 $i$ 这一列右侧的空隙作为折叠中心进行折叠，直接令 $r\gets i$ 即可。最终这个矩形的行数不变，但只剩余左侧的 $r$ 列。

得到最终的折纸形态后，BFS 求出 $0$ 的连通块个数即可。单组数据复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=1e6+5,M=55,mo=998244353,inf=1e9+7;
const double PI=acos(-1);
void read(int &a){
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    a=x*w;
}
int T,n,m;
vector<int>a[N],b[N];
int cm[N*2],d[N*2],mind[N];
void manacher(int len){
    repp(i,2*len-1,1){
        d[i]=0;
        if(i&1)cm[i]=cm[(i+1)>>1];
        else cm[i]=2;
    }
    int mid=0,mr=0;
    rep(i,1,2*len-1){
        if(mr>i){
            int mir=mid-(i-mid);
            if(i+d[mir]-1<mr){
                d[i]=d[mir];
                continue;
            }
            d[i]=mr-i+1;
        }
        while(i-d[i]>=1&&i+d[i]<=2*len-1&&cm[i-d[i]]==cm[i+d[i]])
            d[i]++;
        if(i+d[i]-1>mr)mr=i+d[i]-1,mid=i;
    }
    rep(i,1,len-1)
        d[i]=d[i<<1]>>1;
}
int cut(int x,int y){
    rep(i,1,y-1)
        mind[i]=inf;
    rep(i,1,x){
        rep(j,1,y)
            cm[j]=a[i][j];
        manacher(y);
        rep(j,1,y-1)
            mind[j]=min(mind[j],d[j]);
    }
    int nr=y;
    repp(i,y-1,1)
        if(mind[i]+i>=nr)nr=i;
    return nr;
}
void rotate(int x,int y){
    rep(i,1,x){
        b[i].clear();
        rep(j,0,y)
            b[i].push_back(a[i][j]);
    }
    rep(i,1,y){
        a[i].clear();
        a[i].push_back(0);
        rep(j,1,x)
            a[i].push_back(b[x-j+1][i]);
    }
}
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
void bfs(int x,int y){
    queue<pii>q;
    q.push(mp(x,y)),a[x][y]=1;
    while(!q.empty()){
        tie(x,y)=q.front(),q.pop();
        rep(l,0,3){
            int tx=x+dx[l],ty=y+dy[l];
            if(tx<1||ty<1||tx>n||ty>m||a[tx][ty])continue;
            a[tx][ty]=1,q.push(mp(tx,ty));
        }
    }
}
void solve(){
    cin>>n>>m;
    rep(i,1,n){
        a[i].clear();
        a[i].push_back(0);
        string s;
        cin>>s;
        rep(j,1,m)
            a[i].push_back(s[j-1]-'0');
    }
    rep(i,0,3){
        m=cut(n,m);
        rotate(n,m),swap(n,m);
    }
    int ans=0;
    rep(i,1,n){
        rep(j,1,m)
            if(!a[i][j])bfs(i,j),ans++;
    }
    printf("%d\n",ans);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：ADNAP (赞：0)

### 分析

前面的分析和[另一篇题解](https://www.luogu.com.cn/article/c3xflx3z)是一样的。

但是，经过缜密的分析，我们发现暴力的复杂度是正确的（而且跑出来比 Manacher 要快）。

对 Manacher 分析时间复杂度，预处理的时间复杂度是 $O(nm(\log n + \log m))$，检验的复杂度是 $O(n \log m + m \log n)$，还有一个玄学的常数。

对于暴力，我们每次是暴力检验，分析时间复杂度。不需要预处理，如果尽量从中间开始折的话，时间复杂度可以视为玄学的 $\log$ 级别，所以总体的时间复杂度是 $O(nm(\log n+\log m))$，同时也有一个玄学的常数。

看的出来，首先暴力的检验环节和 Manacher 的预处理复杂度同级，少去了 Manacher 检验环节的复杂度。这样看来是比 Manacher 要快的，但是要注意的是，Manacher 的预处理是没有玄学常数的，但是暴力的检验是有玄学常数的。然而，在折纸的过程中，纸的大小是在不断缩小的，也就是暴力的检验复杂度实际上比 $O(nm(\log n+\log m))$ 要小，如果理想地把每次纸的大小想成缩小一半，那么暴力的时间复杂度可以优化到 $O(nm)$ 为上限，还有一个大常数。

因此，暴力在很大概率上是比正解 Manacher 更优。

### Code
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
#define x first
#define y second
const ll N=1e5+1e4,M=1e3+1e2;
ll t;
ll n,m;
string s[N*10];
PLL p1,p2,p3,p4;
ll check1(ll x)
{
    if(x-p1.y+1<p2.y-x)
    {
        for(ll i=p1.x;i<=p2.x;i++)
        {
            for(ll j=p1.y;j<=x;j++)
            {
                if(s[i][j]!=s[i][x-j+x+1])return 0;
            }
        }
        return 1;
    }
    else
    {
        for(ll i=p1.x;i<=p2.x;i++)
        {
            for(ll j=x+1;j<=p2.y;j++)
            {
                if(s[i][j]!=s[i][x-j+x+1])return 0;
            }
        }
        return 2;
    }
}
ll check2(ll x)
{
    if(x-p1.x+1<p2.x-x)
    {
        for(ll i=p1.x;i<=x;i++)
        {
            for(ll j=p1.y;j<=p2.y;j++)
            {
                if(s[i][j]!=s[x-i+x+1][j])return 0;
            }
        }
        return 1;
    }
    else
    {
        for(ll i=x+1;i<=p2.x;i++)
        {
            for(ll j=p1.y;j<=p2.y;j++)
            {
                if(s[i][j]!=s[x-i+x+1][j])return 0;
            }
        }
        return 2;
    }
}
void dfs(ll xx,ll yy)
{
	if(xx<p1.x||xx>p2.x)return ;
	if(yy<p1.y||yy>p2.y)return ;
	if(s[xx][yy]=='1')return ;
	s[xx][yy]='1';
	dfs(xx+1,yy);
	dfs(xx-1,yy);
	dfs(xx,yy+1);
	dfs(xx,yy-1);
	return ;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        for(ll i=1;i<=n;i++)cin>>s[i];
        p1=make_pair(1,0);
        p2=make_pair(n,m-1);
        while(p1.y!=p2.y)
        {
            p3=p1,p4=p2;
            for(ll i=(p1.y+p2.y)/2;i>=p1.y;i--)
            {
                ll k=check1(i);
                if(k==1)
                {
                    p1.y=i+1;
                    goto here1;
                }
                else if(k==2)
                {
                    p2.y=i;
                    goto here1;
                }
                ll ii=p1.y+p2.y-i;
                k=check1(ii);
                if(k==1)
                {
                    p1.y=ii+1;
                    goto here1;
                }
                else if(k==2)
                {
                    p2.y=ii;
                    goto here1;
                }
            }
            here1:;
            if(p1==p3&&p2==p4)break;
        }
        while(p1.x!=p2.x)
        {
            p3=p1,p4=p2;
            for(ll i=(p1.x+p2.x)/2;i>=p1.x;i--)
            {
                ll k=check2(i);
                if(k==1)
                {
                    p1.x=i+1;
                    goto here2;
                }
                else if(k==2)
                {
                    p2.x=i;
                    goto here2;
                }
                ll ii=p1.x+p2.x-i;
                k=check2(ii);
                if(k==1)
                {
                    p1.x=ii+1;
                    goto here2;
                }
                else if(k==2)
                {
                    p2.x=ii;
                    goto here2;
                }
            }
            here2:;
            if(p1==p3&&p2==p4)break;
        }
        ll ans=0;
        for(ll i=p1.x;i<=p2.x;i++)
        {
            for(ll j=p1.y;j<=p2.y;j++)
            {
                if(s[i][j]=='0')
                {
                    ans++;
                    dfs(i,j);
                }
            }
        }
        cout<<ans<<"\n";
    }
}
```

---

