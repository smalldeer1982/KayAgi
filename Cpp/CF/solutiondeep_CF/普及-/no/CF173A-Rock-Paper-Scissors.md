# 题目信息

# Rock-Paper-Scissors

## 题目描述

Nikephoros and Polycarpus play rock-paper-scissors. The loser gets pinched (not too severely!).

Let us remind you the rules of this game. Rock-paper-scissors is played by two players. In each round the players choose one of three items independently from each other. They show the items with their hands: a rock, scissors or paper. The winner is determined by the following rules: the rock beats the scissors, the scissors beat the paper and the paper beats the rock. If the players choose the same item, the round finishes with a draw.

Nikephoros and Polycarpus have played $ n $ rounds. In each round the winner gave the loser a friendly pinch and the loser ended up with a fresh and new red spot on his body. If the round finished in a draw, the players did nothing and just played on.

Nikephoros turned out to have worked out the following strategy: before the game began, he chose some sequence of items $ A=(a_{1},a_{2},...,a_{m}) $ , and then he cyclically showed the items from this sequence, starting from the first one. Cyclically means that Nikephoros shows signs in the following order: $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{m} $ , $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{m} $ , $ a_{1} $ , $ ... $ and so on. Polycarpus had a similar strategy, only he had his own sequence of items $ B=(b_{1},b_{2},...,b_{k}) $ .

Determine the number of red spots on both players after they've played $ n $ rounds of the game. You can consider that when the game began, the boys had no red spots on them.

## 说明/提示

In the first sample the game went like this:

- R - R. Draw.
- P - S. Nikephoros loses.
- S - P. Polycarpus loses.
- R - P. Nikephoros loses.
- P - R. Polycarpus loses.
- S - S. Draw.
- R - P. Nikephoros loses.

Thus, in total Nikephoros has $ 3 $ losses (and $ 3 $ red spots), and Polycarpus only has $ 2 $ .

## 样例 #1

### 输入

```
7
RPS
RSPP
```

### 输出

```
3 2```

## 样例 #2

### 输入

```
5
RRRRRRRR
R
```

### 输出

```
0 0```

# AI分析结果

### 题目内容
# 石头剪刀布

## 题目描述
尼基福罗斯（Nikephoros）和波利卡普斯（Polycarpus）玩石头剪刀布游戏。输的一方会被轻轻捏一下（不会太疼！）。

让我们回顾一下这个游戏的规则。石头剪刀布由两名玩家进行。在每一轮中，玩家们相互独立地从三个物品中选择一个。他们用手展示物品：石头、剪刀或布。获胜者由以下规则决定：石头胜剪刀，剪刀胜布，布胜石头。如果玩家选择相同的物品，则这一轮以平局结束。

尼基福罗斯和波利卡普斯玩了 $n$ 轮。在每一轮中，获胜者会友好地捏一下输的一方，输的一方身上就会出现一个新的红印。如果这一轮以平局结束，玩家们什么也不做，继续游戏。

尼基福罗斯想出了以下策略：在游戏开始前，他选择了一些物品序列 $A=(a_{1},a_{2},...,a_{m})$ ，然后他从第一个开始循环展示这个序列中的物品。循环的意思是尼基福罗斯按照以下顺序展示物品： $a_{1}$ ， $a_{2}$ ， $...$ ， $a_{m}$ ， $a_{1}$ ， $a_{2}$ ， $...$ ， $a_{m}$ ， $a_{1}$ ， $...$ 等等。波利卡普斯也有类似的策略，只是他有自己的物品序列 $B=(b_{1},b_{2},...,b_{k})$ 。

确定他们玩了 $n$ 轮游戏后，两人身上红印的数量。你可以认为游戏开始时，两人身上都没有红印。

## 说明/提示
在第一个样例中，游戏过程如下：
- 石头 - 石头。平局。
- 布 - 剪刀。尼基福罗斯输。
- 剪刀 - 布。波利卡普斯输。
- 石头 - 布。尼基福罗斯输。
- 布 - 石头。波利卡普斯输。
- 剪刀 - 剪刀。平局。
- 石头 - 布。尼基福罗斯输。

因此，尼基福罗斯总共输了 $3$ 次（有 $3$ 个红印），而波利卡普斯只输了 $2$ 次。

## 样例 #1
### 输入
```
7
RPS
RSPP
```
### 输出
```
3 2```

## 样例 #2
### 输入
```
5
RRRRRRRR
R
```
### 输出
```
0 0```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用两个玩家出手序列周期的最小公倍数（lcm）来优化计算，避免直接 $O(n)$ 模拟导致超时。因为数据范围 $n\leq 2\times 10^9$ 直接模拟会超时，而每个周期长度不超过 $1000$，通过求出 lcm 可以将计算量大幅减少。各题解在实现细节上略有不同，如计算 lcm 和 gcd 的方式、判断胜负的实现等，但整体思路一致。

### 所选的题解
- **作者：chlchl（5星）**
    - **关键亮点**：思路清晰，代码简洁明了，直接利用 C++ 自带的 `__gcd()` 函数计算最大公约数，进而求出最小公倍数，在计算过程中对边界条件处理得当。
    - **个人心得**：强调了在处理余数部分循环时，循环范围是从 0 到 q - 1 而不是 1 到 q，该边界条件容易出错。
    - **重点代码**：
```cpp
int lcm(int a, int b){return a / __gcd(a, b) * b;}

void iswin(int a, int b){
    if(s[a] == 'R' && t[b] == 'S')    loseb++;
    if(s[a] == 'S' && t[b] == 'R')    losea++;
    if(s[a] == 'S' && t[b] == 'P')    loseb++;
    if(s[a] == 'P' && t[b] == 'S')    losea++;
    if(s[a] == 'P' && t[b] == 'R')    loseb++;
    if(s[a] == 'R' && t[b] == 'P')    losea++;
}

signed main(){
    scanf("%d", &n);
    cin >> s >> t;
    lens = s.length(), lent = t.length();
    l = lcm(lens, lent);
    for(int i=0;i<l;i++)    iswin(i % lens, i % lent);
    cnt = n / l, q = n % l;
    losea *= cnt, loseb *= cnt;
    for(int i=0;i<q;i++)    iswin(i % lens, i % lent);
    cout << losea << ' ' << loseb << endl;
    return 0;
}
```
核心实现思想：先定义 `lcm` 函数计算最小公倍数，`iswin` 函数判断每一局的胜负并更新输的次数。在 `main` 函数中，读入数据后计算最小公倍数，在一个最小公倍数周期内统计双方输的次数，再根据总轮数 $n$ 中包含的完整周期数和余数分别计算最终双方输的次数并输出。
- **作者：Eason_AC（5星）**
    - **关键亮点**：代码简洁高效，通过定义 `gcd` 和 `lcm` 函数计算最大公约数和最小公倍数，在循环统计输赢次数时逻辑清晰，利用数组记录每个位置的输赢情况，最后再汇总计算结果。
    - **重点代码**：
```cpp
string s1, s2;
int n, loses[1000007], loset[1000007], lose1, lose2, ans1, ans2;

inline int gcd(int a, int b) {return!b? a : gcd(b, a % b);}
inline int lcm(int a, int b) {return a / gcd(a, b) * b;} 

int main() {
    n = Rint; str(s1, len1); str(s2, len2);
    int round = lcm(len1, len2);
    F(i, 0, round - 1) {
        if((s1[i % len1] == 'R' && s2[i % len2] == 'P') || (s1[i % len1] == 'P' && s2[i % len2] == 'S') || (s1[i % len1] == 'S' && s2[i % len2] == 'R'))
            loses[i + 1]++, lose1++;
        if((s2[i % len2] == 'R' && s1[i % len1] == 'P') || (s2[i % len2] == 'P' && s1[i % len1] == 'S') || (s2[i % len2] == 'S' && s1[i % len1] == 'R'))
            loset[i + 1]++, lose2++;
    }
    F(i, 1, n % round) ans1 += loses[i], ans2 += loset[i];
    return printf("%d %d", ans1 + lose1 * (n / round), ans2 + lose2 * (n / round)), 0;
}
```
核心实现思想：定义数组 `loses` 和 `loset` 分别记录在一个最小公倍数周期内两人输的情况，通过循环 `round` 次，根据石头剪刀布规则判断每一局的输赢并更新数组和总输赢次数 `lose1`、`lose2`。最后根据总轮数 $n$ 的完整周期数和余数计算最终两人输的次数并输出。
- **作者：fzj2007（4星）**
    - **关键亮点**：对知识点讲解详细，不仅给出了利用最小公倍数优化的思路，还详细讲解了辗转相除法求最大公约数以及最小公倍数的计算原理，并对代码中的每个函数都进行了详细解释。
    - **重点代码**：
```cpp
int gcd(int x,int y){
    return!y?x:gcd(y,x%y);
}
inline int lcm(int x,int y){
    return x*y/gcd(x,y);
}
inline int findint(char u){
    return (u=='S'?1:(u=='P'?2:3));
}
inline int win(char x,char y){
    int nowx=findint(x),nowy=findint(y);
    if(nowx==nowy) return 0;
    if(nowx==1&&nowy==2) return 1;
    if(nowx==1&&nowy==3) return 2;
    if(nowx==2&&nowy==3) return 1;
    if(nowx==2&&nowy==1) return 2;
    if(nowx==3&&nowy==2) return 2;
    if(nowx==3&&nowy==1) return 1;
}
int main(){
    n=read();
    cin>>a>>b;
    len=lcm(a.length(),b.length());
    for(int i=0;i<len;i++)
        if(win(a[i%(a.length())],b[i%(b.length())])==1) bl++;
        else if(win(a[i%(a.length())],b[i%(b.length())])==2) al++;    
    al*=(n/len);
    bl*=(n/len);
    for(int i=0;i<n%len;i++)
        if(win(a[i%(a.length())],b[i%(b.length())])==1) bl++;
        else if(win(a[i%(a.length())],b[i%(b.length())])==2) al++;    
    printf("%d %d\n",al,bl);
    return 0;
}
```
核心实现思想：通过 `gcd` 和 `lcm` 函数分别计算最大公约数和最小公倍数。`findint` 函数将字符转化为整数值方便判断胜负，`win` 函数根据转化后的整数值判断每一局谁获胜。在 `main` 函数中，读入数据后计算最小公倍数，在一个最小公倍数周期内统计双方输赢情况，再根据总轮数 $n$ 的完整周期数和余数计算最终双方输的次数并输出。

### 最优关键思路或技巧
利用两个玩家出手序列周期长度的最小公倍数来优化计算，避免直接模拟 $n$ 轮。通过求出最小公倍数，可知在这个周期内双方输赢情况是固定的，只需统计一个最小公倍数周期内的输赢次数，再结合总轮数 $n$ 中包含的完整周期数和余数，就能高效计算出最终结果。同时，计算最小公倍数时可利用公式 $lcm(a,b)=a / gcd(a,b) * b$，C++ 中可直接使用 `__gcd()` 函数计算最大公约数，或者自己实现辗转相除法求最大公约数。

### 可拓展思路
同类型题通常是具有周期性规律的游戏或序列问题，类似算法套路是寻找问题中的周期，利用周期特性减少计算量。例如，一些具有固定循环模式的博弈游戏，或者周期性出现的序列匹配问题等，都可以尝试通过计算周期相关的值（如最小公倍数）来优化求解。

### 相似知识点洛谷题目
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及到序列的循环移位和规律查找，与本题寻找周期规律类似。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：需要利用斐波那契数列的性质和最大公约数的计算来解决问题，与本题计算最小公倍数（依赖最大公约数计算）有相似之处。
- [P2398 GCD SUM](https://www.luogu.com.cn/problem/P2398)：主要考查最大公约数的计算以及对循环和累加的处理，与本题在计算最小公倍数过程中涉及的最大公约数计算知识点相关。 

---
处理用时：89.40秒