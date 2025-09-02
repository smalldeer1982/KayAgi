# 题目信息

# [ICPC 2020 Nanjing R] Fireworks

## 题目描述

Kotori is practicing making fireworks for the upcoming hanabi taikai$^1$. It takes her $n$ minutes to make a single firework, and as she is not really proficient in making fireworks, each firework only has a probability of $p \times 10^{-4}$ to be perfect.

After she finishes making a firework, she can just start making the next firework, or take $m$ minutes to light all the remaining fireworks finished before. If there is at least one perfect firework among the lit ones, she will be happy and go to rest. Otherwise, she will continue practicing. Can you tell her the minimum expected practicing time before she goes to rest if she takes the optimal strategy?

Notice that no matter how many fireworks remain, it always takes $m$ minutes to light them all.

$^1$ Hanabi taikai: Romaji of the Japanese word ``花火大會``, which means the firework... err... party?

## 样例 #1

### 输入

```
3
1 1 5000
1 1 1
1 2 10000```

### 输出

```
4.0000000000
10141.5852891136
3.0000000000```

# AI分析结果

### 算法分类
**概率论**

### 综合分析与结论
该题的核心是通过概率论中的几何分布模型，计算在最优策略下的期望时间。所有题解都采用了类似的思路：假设每次制作固定数量的烟花后进行测试，推导出期望时间的公式，并通过三分法或二分法找到最小值。难点在于如何正确推导期望时间公式，并证明其凸性以应用三分法。

### 所选题解

#### 1. 作者：一只绝帆 (赞：4)
**星级：★★★★★**
**关键亮点：**
- 详细推导了期望时间的公式，并通过数学证明其凸性。
- 使用三分法进行优化，代码简洁且高效。
- 提供了对几何分布的深入理解，帮助读者更好地掌握概率论的应用。

**个人心得：**
- 作者提到在推导过程中多次出错，最终通过求导软件验证了函数的凸性，强调了数学推导的严谨性。

**核心代码：**
```cpp
db check(db x) {return (x+m)/(1-pow(1-p,x));}
int main() {
    F(T,1,read()) {
        n=read();m=(db)read()/n;p=(db)read()/10000;q=1-p;
        int L=1,R=1e9,mid;
        while(L<=R) {
            mid=L+R>>1;
            if(L+10>=R) break;
            if(check(mid)<check(mid+1)) R=mid+1;
            else L=mid;
        } db ans=1e20;
        F(i,L,R) ans=min(ans,check(i));
        printf("%.10Lf\n",ans*n);
    }
    return 0;
}
```

#### 2. 作者：SDLTF_凌亭风 (赞：1)
**星级：★★★★**
**关键亮点：**
- 简洁明了地推导了期望时间公式，并直接应用三分法求解。
- 代码实现简洁，易于理解。

**核心代码：**
```cpp
inline double f(int k) { double t = 1.0 - qp(1.0 - p, k); return (!t) ? (double)0x3f3f3f3f : (k * n * 1.0 + m) / t; }
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T, mid1, mid2; cin >> T;
    for(double f1, f2; T; -- T) {
        cin >> n >> m >> p, p *= 1e-4;
        int l = 1, r = 0x3f3f3f3f; double res = (double)0x3f3f3f3f3f3f3f3f;
        while(r > l) mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3, f1 = f(mid1), f2 = f(mid2), res = min(res, min(f1, f2)), (f1 < f2) ? (r = mid2 - 1) : (l = mid1 + 1); 
        cout << fixed << setprecision(10) << res << endl;
    }
}
```

#### 3. 作者：hellolin (赞：0)
**星级：★★★★**
**关键亮点：**
- 通过二分法求解期望时间的最小值，代码实现清晰。
- 提供了对概率论应用的直观理解。

**核心代码：**
```cpp
auto calc = [&](ll x) {
    return ((ld)m + (ld)x * n) / ((ld)1.0 - fpow((ld)1.0 - p, x));
};
void solve() {
    std::cout << std::fixed << std::setprecision(10);
    for(std::cin >> T; T--; [&](){
        std::cin >> n >> m >> p;
        p *= 1e-4;
        l = 0, r = N;
        while(l < r) {
            ll mid = (l + r) >> 1;
            if (calc(mid + 1) - calc(mid) < Eps)
                l = mid + 1;
            else
                r = mid;
        }
        std::cout << calc(l) << nl;
    }());
}
```

### 最优关键思路或技巧
- **几何分布模型**：通过几何分布模型推导期望时间公式，理解其数学背景是解决问题的关键。
- **三分法/二分法**：在证明函数凸性后，使用三分法或二分法快速找到最小值，优化了计算效率。

### 可拓展之处
- 类似的问题可以通过概率论中的其他分布模型（如泊松分布、正态分布）进行求解。
- 三分法和二分法在优化问题中的应用广泛，可以用于其他需要寻找极值的问题。

### 推荐题目
1. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

### 个人心得总结
- **调试经历**：作者在推导过程中多次出错，最终通过求导软件验证了函数的凸性，强调了数学推导的严谨性。
- **顿悟感想**：通过几何分布模型和三分法的结合，作者成功解决了问题，体现了数学与算法结合的强大之处。

---
处理用时：28.72秒