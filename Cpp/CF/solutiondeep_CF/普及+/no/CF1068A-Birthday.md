# 题目信息

# Birthday

## 题目描述

Ivan is collecting coins. There are only $ N $ different collectible coins, Ivan has $ K $ of them. He will be celebrating his birthday soon, so all his $ M $ freinds decided to gift him coins. They all agreed to three terms:

- Everyone must gift as many coins as others.
- All coins given to Ivan must be different.
- Not less than $ L $ coins from gifts altogether, must be new in Ivan's collection.

But his friends don't know which coins have Ivan already got in his collection. They don't want to spend money so they want to buy minimum quantity of coins, that satisfy all terms, irrespective of the Ivan's collection. Help them to find this minimum number of coins or define it's not possible to meet all the terms.

## 说明/提示

In the first test, one coin from each friend is enough, as he will be presented with 15 different coins and 13 of them will definitely be new.

In the second test, Ivan has 11 friends, but there are only 10 different coins. So all friends can't present him different coins.

## 样例 #1

### 输入

```
20 15 2 3
```

### 输出

```
1```

## 样例 #2

### 输入

```
10 11 2 4
```

### 输出

```
-1```

# AI分析结果

### 题目内容
# Birthday

## 题目描述
Ivan正在收集硬币。世界上仅有$N$种不同的收藏硬币，Ivan已经拥有了其中的$K$种。他的生日即将来临，他的$M$个朋友决定送他硬币作为礼物。他们一致同意遵循以下三个条件：
- 每个人送的硬币数量必须相同。
- 送给Ivan的所有硬币必须各不相同。
- 所有人送的硬币中，至少有$L$个是Ivan收藏中没有的新硬币。

然而，他的朋友们并不知道Ivan已经拥有了哪些硬币。他们不想花太多钱，所以希望购买满足所有条件的最少数量的硬币，无论Ivan现有的收藏情况如何。请帮助他们找出这个最小数量的硬币，或者确定无法满足所有条件。

## 说明/提示
在第一个测试用例中，每个朋友送1枚硬币就足够了，因为他将收到15枚不同的硬币，其中13枚肯定是新的。
在第二个测试用例中，Ivan有11个朋友，但只有10种不同的硬币。所以所有朋友无法送给他各不相同的硬币。

## 样例 #1
### 输入
```
20 15 2 3
```
### 输出
```
1
```

## 样例 #2
### 输入
```
10 11 2 4
```
### 输出
```
-1
```

### 算法分类
数学

### 综合分析与结论
所有题解思路基本一致，先判断无解情况，再计算每个朋友至少要送的硬币数。无解情况主要有两种：一是朋友数量$m$大于硬币总种类数$n$，导致无法保证每人送不同硬币；二是Ivan没有的硬币种类数$n - k$小于至少要送的新硬币数$l$。计算每个朋友至少送的硬币数时，考虑到需保证至少$l$个新硬币，所以总数至少为$k + l$，再除以朋友数$m$，由于整型除法可能损失精度，需判断若$res\times m < k + l$，则$res$要加1 。最后再判断$res\times m$是否小于等于$n$ ，若满足则$res$为答案，否则无解输出$-1$。各题解主要差异在于代码实现细节和表述方式。

### 所选的题解
- **作者：xiaozeyu (5星)**
    - **关键亮点**：不仅给出正确解法，还详细指出题目翻译误导导致的错误理解及相应错误代码，同时列举了自己做题时遇到的数据类型和函数使用的错误及正确写法，内容全面详细。
    - **个人心得**：强调题目翻译可能误导解题思路，以及做题过程中数据类型和函数使用不当会导致错误，如`int`类型在大数据范围下会溢出，`ceil`函数在本题数据范围下使用会因精度问题爆炸。
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register long long i=a;i<=b;i++)
#define Rep(i,a,b) for(register long long i=a;i>=b;i--)
using namespace std;
inline long long read()
{
    char c=getchar();long long x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
long long n,m,k,l,ans;
int main()
{
    //freopen("coin.in","r",stdin);
    //freopen("coin.out","w",stdout);
    n=read();m=read();k=read();l=read();
    if(n<m||n-k<l)
    {
        printf("-1\n");
        return 0;
    }
    ans=(k+l)/m;
    if(ans*m<k+l) ans++;
    if(ans*m<=n) printf("%lld\n",ans);
    else printf("-1\n");
}
```
- **作者：damage (4星)**
    - **关键亮点**：思路清晰简洁，先明确指出两种无解情况，再说明计算每个朋友送币数的方法及考虑整型除法精度损失的处理，最后再次判断结果是否满足条件，逻辑连贯。
```cpp
#include<cstdio>
long long n,m,k,l,res; //long long
int main()
{
    scanf("%lld%lld%lld%lld",&n,&m,&k,&l);
    if(n<m||n-k<l) //特判无解
    {
        printf("-1\n");
        return 0;
    }
    res=(k+l)/m; //计算res
    if(res*m<k+l) ++res; //如果不够就res+1
    if(res*m<=n) printf("%lld\n",res); //有解则直接输出
    else printf("-1\n"); //否则无解输出-1
    return 0;
}
```
- **作者：云雷心柠檬听 (4星)**
    - **关键亮点**：按题目条件逐步分析，清晰阐述每个条件对结果的限制，得出需找在$[K + L, N]$区间内$M$的倍数这一结论，实现细节处也明确提醒注意数据范围。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull n,m,k,l;

void input(){
    cin>>n>>m>>k>>l;
}

void solve(){
    if((k+l)<=n&&(k+l)%m==0) cout<<(k+l)/m;
    else if(((k+l)/m+1)*m<=n) cout<<(k+l)/m+1;
    else cout<<"-1";
}

int main(){
    input();
    solve();
    return 0;
}
```

### 最优关键思路或技巧
- **数学分析与逻辑判断**：通过对题目条件的数学分析，准确找出无解的条件，并合理计算满足条件时每个朋友至少要送的硬币数，尤其注意整型除法精度损失问题。
- **数据类型选择**：根据题目给定的大数据范围$10^{18}$，选择合适的数据类型`long long`或`unsigned long long` ，避免数据溢出。

### 可拓展之处
此类题目属于基于条件限制的数学计算类型，类似套路是先根据题目条件进行数学建模，分析出各种边界情况和无解条件，再通过合理的数学运算得出结果。同类型题可能会在条件设置上更加复杂，如增加更多限制条件或改变条件间的逻辑关系。

### 推荐题目
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析条件计算满足要求的结果，锻炼对条件的分析和数学运算能力。
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：根据给定条件找出满足等式的数量，涉及到条件分析和循环枚举，与本题分析条件得出结果的思路类似。
- [P1228 地毯填补问题](https://www.luogu.com.cn/problem/P1228)：需要根据特殊条件进行数学构造和逻辑推导，培养处理复杂条件的能力。 

---
处理用时：74.57秒