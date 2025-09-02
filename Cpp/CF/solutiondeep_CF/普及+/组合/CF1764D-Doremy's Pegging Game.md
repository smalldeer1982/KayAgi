# 题目信息

# Doremy's Pegging Game

## 题目描述

Doremy has $ n+1 $ pegs. There are $ n $ red pegs arranged as vertices of a regular $ n $ -sided polygon, numbered from $ 1 $ to $ n $ in anti-clockwise order. There is also a blue peg of slightly smaller diameter in the middle of the polygon. A rubber band is stretched around the red pegs.

Doremy is very bored today and has decided to play a game. Initially, she has an empty array $ a $ . While the rubber band does not touch the blue peg, she will:

1. choose $ i $ ( $ 1 \leq i \leq n $ ) such that the red peg $ i $ has not been removed;
2. remove the red peg $ i $ ;
3. append $ i $ to the back of $ a $ .

Doremy wonders how many possible different arrays $ a $ can be produced by the following process. Since the answer can be big, you are only required to output it modulo $ p $ . $ p $ is guaranteed to be a prime number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) game with $ n=9 $ and $ a=[7,5,2,8,3,9,4] $ and another game with $ n=8 $ and $ a=[3,4,7,1,8,5,2] $

## 说明/提示

In the first test case, $ n=4 $ , some possible arrays $ a $ that can be produced are $ [4,2,3] $ and $ [1,4] $ . However, it is not possible for $ a $ to be $ [1] $ or $ [1,4,3] $ .

## 样例 #1

### 输入

```
4 100000007```

### 输出

```
16```

## 样例 #2

### 输入

```
1145 141919831```

### 输出

```
105242108```

# AI分析结果

### 题目翻译
# Doremy的钉绳游戏

## 题目描述
Doremy有 $ n + 1 $ 个钉子。有 $ n $ 个红色钉子排列成一个正 $ n $ 边形的顶点，按逆时针顺序从 $ 1 $ 到 $ n $ 编号。在多边形的中心还有一个直径稍小的蓝色钉子。一根橡皮筋绕在红色钉子上。

Doremy今天非常无聊，决定玩一个游戏。最初，她有一个空数组 $ a $。当橡皮筋没有碰到蓝色钉子时，她将进行以下操作：
1. 选择 $ i $（$ 1 \leq i \leq n $），使得红色钉子 $ i $ 尚未被移除；
2. 移除红色钉子 $ i $；
3. 将 $ i $ 追加到数组 $ a $ 的末尾。

Doremy想知道通过上述过程可以产生多少种不同的数组 $ a $。由于答案可能很大，你只需要输出答案对 $ p $ 取模的结果。$ p $ 保证是一个质数。

![边长为9和8的多边形示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) 左图为 $ n = 9 $ 且 $ a = [7, 5, 2, 8, 3, 9, 4] $ 的游戏，右图为 $ n = 8 $ 且 $ a = [3, 4, 7, 1, 8, 5, 2] $ 的游戏

## 说明/提示
在第一个测试用例中，$ n = 4 $，一些可能产生的数组 $ a $ 是 $ [4, 2, 3] $ 和 $ [1, 4] $。然而，$ a $ 不可能是 $ [1] $ 或 $ [1, 4, 3] $。

## 样例 #1
### 输入
```
4 100000007
```
### 输出
```
16
```

## 样例 #2
### 输入
```
1145 141919831
```
### 输出
```
105242108
```

### 综合分析与结论
这些题解的核心思路都是先将问题转化为寻找满足特定条件的操作序列数量，利用对称性简化计算，通过枚举不同参数（如连续钉子数量、两侧点距离、保留数个数等），结合组合数和排列数计算方案数，最后乘以 $n$ 得到最终结果。

| 作者           | 思路要点                                                                                      | 算法要点                                                         | 解决难点                                                                      | 评分 |
|--------------|-------------------------------------------------------------------------------------------|--------------------------------------------------------------|---------------------------------------------------------------------------|------|
| VinstaG173   | 利用对称性，先求 $a_k = n$ 的情况，枚举 $s + t$，计算不同取值下的方案数再求和。                                 | 预处理阶乘及阶乘逆元，使用组合数公式计算。                                       | 处理圆上连续钉子与连续整数的对应关系，以及 $s$ 和 $t$ 的取值范围和组合数计算。                       | 4星   |
| honglan0301  | 假设最终状态是 $1$ 与 $1 + i$ 之间的数被删完，定义 $f(i, j)$ 表示情况数，通过分步计算得出递推公式并求和。                      | 预处理组合数和阶乘，使用递推公式计算。                                       | 确定最后一个被删点的范围，以及不同情况下的选点方式和顺序。                              | 4星   |
| Alex_Wei     | 枚举最终绑在两侧的点的距离 $i$ 和两侧点之间保留的数的个数 $j$，计算方案数并求和。                                       | 枚举参数，使用组合数和排列数计算。                                       | 确定 $r$ 的取值和 $i$ 的枚举范围，以及不同奇偶性下的处理。                            | 3星   |
| MortisM      | 枚举连续一段的长度 $l$ 和其他位置选择的个数 $x$，根据不同因素计算方案数并求和。                                       | 枚举参数，使用组合数和排列数计算。                                       | 推导最后一个放的位置的数量，以及组合数和排列数的应用。                            | 3星   |
| james1BadCreeper | 利用对称性，枚举实际被删掉的 $l$ 和其他位置选择的个数 $x$，计算方案数并求和。                                 | 预处理阶乘和组合数，枚举参数计算。                                       | 确定可能成为中间位置的个数，以及组合数和排列数的计算。                            | 3星   |

### 所选题解
- **VinstaG173（4星）**
    - 关键亮点：思路清晰，利用对称性简化问题，详细推导了不同情况下的组合数和排列数计算方式。
    - 核心代码：
```cpp
int n,ntf;ll res,tmp;
ll fac[5003];
ll fic[5003];
inline ll C(int m,int b){
    return fac[m]*fic[b]%ntf*fic[m-b]%ntf;
}
void solve(){
    rd(n);rd(ntf);res=0;
    fac[0]=1;for(rg int i=1;i<=n;++i)fac[i]=fac[i-1]*i%ntf;
    fic[n]=qpw(fac[n]);for(rg int i=n;i;--i)fic[i-1]=fic[i]*i%ntf;
    for(rg int m=n/2-1;m<n-2;++m){
        tmp=0;for(rg int i=0;i<=n-m-3;++i){
            tmp=(tmp+fac[m+i]*C(n-m-3,i))%ntf;
        }
        res=(res+(n-(n&1)-1-m)*tmp)%ntf;
    }
    res=(res+(1-(n&1))*fac[n-2]%ntf)%ntf;
    printf("%lld\n",res*n%ntf);
}
```
    - 核心实现思想：先预处理阶乘和阶乘逆元，然后枚举 $s + t$ 的值 $m$，对于每个 $m$ 再枚举在剩余区间选的钉子数 $i$，计算组合数和排列数，最后将结果累加并乘以 $n$。

- **honglan0301（4星）**
    - 关键亮点：通过定义状态 $f(i, j)$ 进行递推计算，思路直观，对偶数情况进行了特判。
    - 核心代码：
```cpp
for(int i=n/2+1;i<=n-1;i++){
    for(int j=i-1;j<=n-2;j++){
        dp[i][j]=n/2+n/2-i+1;
        dp[i][j]*=c[n-i-1][j-i+1];
        dp[i][j]%=mod;
        dp[i][j]*=jc[j-1];
        ans+=dp[i][j];
        ans%=mod;
    }
}
if(n%2==0){
    dp[n][n-1]=1;
    dp[n][n-1]*=jc[n-2];
    ans+=dp[n][n-1];
    ans%=mod;
}
ans*=n;
ans%=mod;
```
    - 核心实现思想：枚举 $i$ 和 $j$，根据递推公式计算 $f(i, j)$ 的值并累加到答案中，对偶数情况进行特判，最后将结果乘以 $n$。

### 最优关键思路或技巧
- **利用对称性**：通过分析问题的对称性，只计算最后一个钉子为某一特定值的情况，再乘以 $n$ 得到最终结果，简化了计算过程。
- **枚举与组合数结合**：通过枚举不同的参数（如连续钉子数量、保留数个数等），结合组合数和排列数计算方案数，将复杂问题分解为多个子问题。
- **预处理阶乘和逆元**：在计算组合数时，预处理阶乘和阶乘逆元可以提高计算效率。

### 拓展思路
同类型题目可能会改变问题的场景，如改变钉子的排列方式、操作规则或停止条件等，但核心思路仍然是寻找满足特定条件的组合和排列方案数。可以使用类似的枚举和组合数计算方法来解决。

### 洛谷相似题目推荐
- [P1833 樱花](https://www.luogu.com.cn/problem/P1833)：涉及组合数和排列数的计算，需要枚举不同的选择情况。
- [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)：主要考察组合数的计算和性质，需要预处理组合数。
- [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)：需要运用组合数学的思想，通过计算总方案数和不满足条件的方案数来得到满足条件的方案数。

### 个人心得摘录与总结
- **MortisM**：“简单题，赛时智障没调出来。” 总结：即使题目看似简单，在比赛中也可能因为紧张或其他原因出现问题，需要冷静思考和调试。

---
处理用时：50.74秒