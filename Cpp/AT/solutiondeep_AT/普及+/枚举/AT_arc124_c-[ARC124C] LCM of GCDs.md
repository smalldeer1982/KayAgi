# 题目信息

# [ARC124C] LCM of GCDs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc124/tasks/arc124_c

赤い袋と青い袋と $ N $ 個のカードパックがあります。はじめどちらの袋も空です。 それぞれのカードパックには整数が書かれた $ 2 $ 枚のカードが封入されており、$ i $ 番目のカードパックに入っているカードにはそれぞれ $ a_i,b_i $ が書かれていることがわかっています。

それぞれのカードパックについて、一方のカードを赤い袋に、他方のカードを青い袋に入れます。

カードを袋に入れ終えたのち、赤い袋に入ったカードに書かれた整数全体の最大公約数を $ X $ とします。 同様に、青い袋に入ったカードに書かれた整数全体の最大公約数を $ Y $ とします。 $ X $ と $ Y $ の最小公倍数の値が得点となります。

得点としてありうる値の最大値を求めてください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ 10^9 $

### Sample Explanation 1

\- $ 2 $ が書かれたカードを赤い袋に入れ、$ 15 $ が書かれたカードを青い袋に入れ、$ 6 $ が書かれたカードを赤い袋に入れ、$ 10 $ が書かれたカードを青い袋に入れるのが最適な入れ方の $ 1 $ つです。 - このとき、赤い袋に入ったカードに書かれた整数全体の最大公約数は $ 2 $、青い袋に入ったカードに書かれた整数全体の最大公約数は $ 5 $ です。 - このときの得点は $ 10 $ です。

## 样例 #1

### 输入

```
2

2 15

10 6```

### 输出

```
10```

## 样例 #2

### 输入

```
5

148834018 644854700

947642099 255192490

35137537 134714230

944287156 528403260

68656286 200621680```

### 输出

```
238630```

## 样例 #3

### 输入

```
20

557057460 31783488

843507940 794587200

640711140 620259584

1901220 499867584

190122000 41414848

349507610 620259584

890404700 609665088

392918800 211889920

507308870 722352000

156850650 498904448

806117280 862969856

193607570 992030080

660673950 422816704

622015810 563434560

207866720 316871744

63057130 117502592

482593010 366954816

605221700 705015552

702500790 900532160

171743540 353470912```

### 输出

```
152594452160```

# AI分析结果

### 题目翻译
有一个红色袋子、一个蓝色袋子和 $N$ 个卡片包。起初，两个袋子都是空的。每个卡片包中装有两张写有整数的卡片，已知第 $i$ 个卡片包中的两张卡片上分别写有 $a_i$ 和 $b_i$。

对于每个卡片包，将其中一张卡片放入红色袋子，另一张卡片放入蓝色袋子。

放完卡片后，设红色袋子中所有卡片上整数的最大公约数为 $X$，同样，设蓝色袋子中所有卡片上整数的最大公约数为 $Y$，$X$ 和 $Y$ 的最小公倍数的值即为得分。

请求出可能的最大得分。

### 综合分析与结论
这些题解主要围绕如何高效求出最大得分展开，思路可分为动态规划、模拟退火和枚举因数三类。
- **动态规划**：利用 $\gcd$ 值域至少减半的性质，用 $\texttt{std::set}$ 存储有用状态，通过 DP 转移判断是否能到达特定的 $\gcd$ 组合。
- **模拟退火**：先尝试贪心策略但发现有问题，由于 $n$ 较小，采用模拟退火算法，通过交换插入顺序逐步接近答案。
- **枚举因数**：基于 $\gcd$ 是数的因数这一性质，枚举第一组卡片数字的因数作为可能的 $X$ 和 $Y$，再检查其是否可行，可行则更新答案。

### 所选题解
- **User_Authorized（4星）**：
    - **关键亮点**：思路清晰，代码结构良好，通过枚举约数并 $\mathcal{O}(N)$ 判断是否可行来求解，复杂度可接受。
    - **核心代码**：
```cpp
valueType lcm(valueType a, valueType b) {
    return a / std::__gcd(a, b) * b;
}

ValueVector divisor(valueType n) {
    ValueVector result;
    for (valueType i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            result.push_back(i);
            if (i * i != n)
                result.push_back(n / i);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

bool check(valueType a, valueType b, PairVector const &data) {
    return std::all_of(data.begin(), data.end(), [a, b](ValuePair const &iter) {
        return (iter.first % a == 0 && iter.second % b == 0) || (iter.second % a == 0 && iter.first % b == 0);
    });
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    valueType N;
    std::cin >> N;
    PairVector data(N);
    for (auto &iter: data)
        std::cin >> iter.first >> iter.second;
    ValueVector const A = divisor(data[0].first), B = divisor(data[0].second);
    valueType ans = 0;
    for (auto const &a: A)
        for (auto const &b: B)
            if (check(a, b, data))
                ans = std::max(ans, lcm(a, b));
    std::cout << ans << std::endl;
    return 0;
}
```
- **Pt_crN（4星）**：
    - **关键亮点**：思路简洁直接，通过枚举因数并检查可行性来求解，代码实现较为清晰。
    - **核心代码**：
```cpp
ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
inline ll Lcm(ll a,ll b){
    return a*b/gcd(a,b);
}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&e[i],&d[i]);
    }
    int a=e[1],b=d[1];
    for(int i=1;i*i<=a;i++){
        if(a%i==0){
            v1.push_back(i);
            v1.push_back(a/i);
        }
    }
    for(int i=1;i*i<=b;i++){
        if(b%i==0){
            v2.push_back(i);
            v2.push_back(b/i);
        }
    }
    ll ans=1;
    for(int i:v1){
        for(int j:v2){
            bool flag=true;
            for(int k=2;k<=n;k++){
                if((e[k]%i!=0||d[k]%j!=0)&&(e[k]%j!=0||d[k]%i!=0)){
                    flag=false;
                    break;
                }
            }
            if(flag){
                ans=max(ans,Lcm(i,j));
            }
        }
    }
    printf("%lld\n",ans);
}
```
- **Tastoya（4星）**：
    - **关键亮点**：利用约数个数增长慢的特点，枚举约数求解，代码简洁易懂。
    - **核心代码**：
```cpp
bool Check(int x,int y) {
    for(int i = 1;i <= n; i++)
        if((a[i] % x != 0 || b[i] % y != 0) && (a[i] % y != 0 || b[i] % x != 0))
            return false;
    return true;
}

int lcm(int a,int b) {
    return a / __gcd(a,b) * b;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 1;i <= n; i++)
        cin >> a[i] >> b[i];
    for(int i = 1;i * i <= a[1]; i++) {
        if(a[1] % i != 0)
            continue;
        Fac1.push_back(i);
        Fac1.push_back(a[1] / i);
    }
    for(int i = 1;i * i <= b[1]; i++) {
        if(b[1] % i != 0)
            continue;
        Fac2.push_back(i);
        Fac2.push_back(b[1] / i);
    }
    int ans = 0;
    for(auto const &i : Fac1) {
        for(auto const &j : Fac2) {
            if(Check(i,j)) {
                ans = max(ans,lcm(i,j));
            }
        }
    }
    cout << flush;
    cout << ans << endl;
    return 0;
}
```

### 最优关键思路或技巧
枚举因数是本题的关键思路，利用一个数的约数个数相对较少的特点，将枚举复杂度从 $10^9$ 级别降到约 $10^6$ 级别，再通过 $O(n)$ 的检查判断是否可行，从而在可接受的复杂度内求解。

### 拓展思路
同类型题目可能会有更多的约束条件或更复杂的规则，但枚举因数、利用 $\gcd$ 和 $\text{lcm}$ 性质的思路仍可作为重要的解题方向。例如，卡片包中卡片数量增加、袋子数量增加等情况，都可以尝试从因数和公约数的角度去思考。

### 洛谷相似题目
- P1072 [NOIP2009 提高组] Hankson 的趣味题
- P2152 [SDOI2009] SuperGCD
- P1372 又是毕业季I

### 个人心得摘录与总结
- **Cure_Wing**：尝试贪心策略发现有问题，由于 $n$ 较小，想到用模拟退火算法，通过改变加入顺序来避免特定情况加入时可能产生的问题，且参数好调，未出现卡常情况。总结：在贪心策略失效时，可考虑模拟退火等随机化算法，并且在数据规模较小时，随机化算法可能有较好的效果。 

---
处理用时：44.22秒