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



# Doremy的钉子游戏

## 题目描述

Doremy有$n+1$个钉子。其中$n$个红色钉子按逆时针顺序排列成一个正$n$边形的顶点，编号为$1$到$n$。中间有一个直径稍小的蓝色钉子。橡皮筋被拉伸在红色钉子上。

Doremy进行如下操作：当橡皮筋未接触蓝色钉子时，不断选择未被移除的红色钉子$i$，移除它并将$i$追加到数组$a$末尾。求所有可能的不同数组$a$的数量模$p$的结果。

## 题解综合分析

### 核心思路对比
1. **VinstaG173（★★★★★）**
   - **对称性简化**：利用环形对称性，固定最后一个移除的钉子为$n$，最终结果乘$n$
   - **连续段分析**：枚举满足条件的连续段长度$m$，计算剩余钉子的组合排列
   - **数学推导**：通过$(s,t)$范围确定有效组合数，结合阶乘预处理
   - **代码亮点**：清晰的数学公式转换，预处理阶乘逆元优化组合计算

2. **honglan0301（★★★★☆）**
   - **状态定义**：定义$f(i,j)$表示删去$j$个点且特定区间被删完的情况数
   - **边界处理**：处理$n$为偶数时的特殊情况
   - **组合推导**：直接计算合法位置数、组合数及排列数的乘积

3. **Alex_Wei（★★★★☆）**
   - **两侧点枚举**：枚举连续段在环上的跨度$i$，计算相关参数$r$
   - **保留点处理**：通过$\binom{i-2}{j}$处理中间保留点的组合方式
   - **环结构处理**：利用环的对称性简化计算

### 最优关键技巧
1. **对称性简化**：固定最后一个移除点，将环结构转换为线性问题
2. **连续段枚举**：通过枚举最后一步形成的连续段长度，确保不重不漏
3. **组合数优化**：预处理阶乘和逆元，快速计算排列组合
4. **奇偶特判**：单独处理$n$为偶数时的边界情况

### 核心代码实现
以VinstaG173的代码为例：
```cpp
void solve(){
    rd(n);rd(ntf);res=0;
    // 预处理阶乘及逆元
    fac[0]=1;for(rg int i=1;i<=n;++i)fac[i]=fac[i-1]*i%ntf;
    fic[n]=qpw(fac[n]);for(rg int i=n;i;--i)fic[i-1]=fic[i]*i%ntf;
    
    for(rg int m=n/2-1;m<n-2;++m){ // 枚举连续段参数
        tmp=0;
        for(rg int i=0;i<=n-m-3;++i){
            // 计算组合数及排列数的乘积
            tmp=(tmp+fac[m+i]*C(n-m-3,i))%ntf;
        }
        res=(res+(n-(n&1)-1-m)*tmp)%ntf;
    }
    res=(res+(1-(n&1))*fac[n-2]%ntf)%ntf; // 处理偶数特例
    printf("%lld\n",res*n%ntf); // 乘对称因子n
}
```

### 举一反三
1. **环形排列问题**：类似CF1764D的环结构处理思路可用于[CF1392E](https://www.luogu.com.cn/problem/CF1392E)
2. **组合计数优化**：预处理阶乘逆元技巧适用于[P3807 卢卡斯定理](https://www.luogu.com.cn/problem/P3807)
3. **终止条件枚举**：最后一步触发的计数模式可参考[P3223 排队](https://www.luogu.com.cn/problem/P3223)

### 个人心得摘录
- **调试经验**：VinstaG173提到"注意奇偶特判"，强调边界条件的重要性
- **思维突破**：Alex_Wei指出"利用环的对称性将问题线性化"，提供结构转换的关键思路
- **优化意识**：多篇题解强调预处理阶乘的重要性，体现算法优化思维

---
处理用时：56.13秒