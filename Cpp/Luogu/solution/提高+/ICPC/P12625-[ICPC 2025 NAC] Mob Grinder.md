# [ICPC 2025 NAC] Mob Grinder

## 题目描述

在某款流行的沙盒视频游戏中，玩家可以建造一种名为 *mob grinder*（怪物磨床）的结构。

一个 mob grinder 由 $N \times M$ 的矩形网格组成。怪物（或称 "mob"）会随机出现在网格各处。mob grinder 的目标是将所有怪物移动到网格右上角的格子，无论它们最初出现在哪里。为实现这一目标，每个格子（除右上角外）都装有一个指定方向（上、右、下、左）的传送带。怪物在传送带上会沿着传送带方向移动到相邻的格子。

你的任务是为每个格子（除右上角外）设置传送带方向，使得无论怪物出现在网格何处，都能在有限时间内被传送到右上角，且不会离开网格边界。但每种方向的传送带使用数量有限制：最终设计必须恰好使用 $U$ 个向上、$R$ 个向右、$D$ 个向下、$L$ 个向左的传送带。

你需要设计多个 mob grinder，每个都有特定的传送带使用数量要求。判断每个规格是否可行，若可行则输出有效设计。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
4 3 5 3 1 2
1 2 0 1 0 0```

### 输出

```
RR*
URU
UDU
ULL

R*```

## 样例 #2

### 输入

```
3
3 3 0 0 0 8
2 2 0 2 0 1
1 1 0 0 0 0```

### 输出

```
impossible

impossible

*```

# 题解

## 作者：E_firework (赞：0)

### 简要题意

一个 $n\times m$ 的棋盘，你需要在除了右上角的每个位置上填一个 `URDL` 中的字符，规定了每种字符的个数。要求从每一个格子出发，按照格子上的字母所代表的方向一直移动，最后都能到达棋盘的左上角。判断是否有解，有解则构造一组方案。

### 解法

首先，`U` 至少要有 $n-1$ 个，因为除了第一行外每一行都至少要有一个 `U`，否则无法到达上一行。同理，`R` 至少有 $m-1$ 个。我们猜想满足这两个条件就一定有解。

如果没有 `D` 的话，如下的构造是合法的：第一行全填 `R`，然后只需要保证每行至少有一个 `U`，且 `U` 的左边只有 `L`，右边只有 `R`，这是容易做到的。

在原题的限制下，下面是一种可行的构造。

只用 `U` 和 `R` 构建出一条从左下角到右上角的路径，在这条路径的左上方只用 `R` 和 `D` 来填，右上方只用 `U` 和 `L` 来填，这样从不在路径上的格子出发可以在有限步内移动到路径上。那我们只需要保证路径左上方的格子数正好等于剩下的 `R` 和 `D` 的总数就行了。这是容易做到的。一种容易实现的方案是选取的路径先沿着左边缘向上，再向右穿过盘面，中间可能要再向上一步，最后沿着右边缘向上。

![](https://cdn.luogu.com.cn/upload/image_hosting/eidyw7or.png)

（用上述方法得到的构造方案，用红色标出的是从左下角到右上角的路径）

code:

```cpp
#include <bits/stdc++.h>
#define LL long long
#define Maxn 100005
#define id(i, j) (((i) - 1) * m + j)
using namespace std;
inline LL read(){char c;c = getchar();while(!(('0' <= c && c <= '9') || c == '-')) c = getchar();bool flag = 0;if(c == '-'){flag = 1;c = getchar();}LL tot = 0;while('0' <= c && c <= '9'){tot = 10 * tot + c - '0';c = getchar();}return flag ? -tot : tot;}
char c[Maxn];
int main(){
    int T = read(), n, m, u, r, d, l, x, y;
    while(T--){
        n = read(), m = read(), u = read(), r = read(), d = read(), l = read();
        if(u < n - 1 || r < m - 1){
            puts("impossible");
            if(T) puts("");
            continue;
        }
        for(int i = 1; i <= n * m; i++) c[i] = 0;
        c[id(1, m)] = '*';
        if(n == 1){
            for(int i = 1; i < m; i++) c[i] = 'R';
        }else if(m == 1){
            for(int i = 2; i <= n; i++) c[i] = 'U';
        }else{
            x = (r + d) / (m - 1) + 1;
            y = (r + d) % (m - 1) + 1;
            for(int i = n; i > x; i--) c[id(i, 1)] = 'U';
            for(int i = 1; i < y; i++) c[id(x, i)] = 'R';
            c[id(x, y)] = 'U';
            for(int i = y; i < m; i++) c[id(x - 1, i)] = 'R';
            for(int i = x - 1; i > 1; i--) c[id(i, m)] = 'U';
            u -= n - 1, r -= m - 1;
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= m; j++){
                    x = id(i, j);
                    if(!c[x]){
                        if(r) c[x] = 'R', r--;
                        else if(d) c[x] = 'D', d--;
                        else if(u) c[x] = 'U', u--;
                        else if(l) c[x] = 'L', l--;
                    }
                }
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                printf("%c", c[id(i, j)]);
            }
            puts("");
        }
        if(T) puts("");
    }
    return 0;
}
```

---

