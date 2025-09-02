# 题目信息

# Reducing Fractions

## 题目描述

To confuse the opponents, the Galactic Empire represents fractions in an unusual format. The fractions are represented as two sets of integers. The product of numbers from the first set gives the fraction numerator, the product of numbers from the second set gives the fraction denominator. However, it turned out that the programs that work with fractions in this representations aren't complete, they lack supporting the operation of reducing fractions. Implement this operation and the Empire won't forget you.

## 说明/提示

In the first test sample the numerator equals 1000, the denominator equals 500. If we reduce fraction 1000/500 by the greatest common divisor of the numerator and the denominator (by 500), we obtain fraction 2/1.

In the second test sample the numerator equals 2000, the denominator equals 300. If we reduce fraction 2000/300 by the greatest common divisor of the numerator and the denominator (by 100), we obtain fraction 20/3.

## 样例 #1

### 输入

```
3 2
100 5 2
50 10
```

### 输出

```
2 3
2 1
1 1 1
```

## 样例 #2

### 输入

```
4 3
2 5 10 20
100 1 3
```

### 输出

```
1 1
20
3
```

# AI分析结果

### 题目重写
# 化简分数

## 题目描述
为了迷惑对手，银河帝国以一种不同寻常的格式表示分数。分数由两组整数表示。第一组数字的乘积给出分数的分子，第二组数字的乘积给出分数的分母。然而，事实证明，处理这种表示形式分数的程序并不完整，它们缺少化简分数的操作。实现这个操作，帝国不会忘记你的。

## 说明/提示
在第一个测试样例中，分子等于1000，分母等于500。如果我们用分子和分母的最大公约数（500）化简分数1000/500，我们得到分数2/1。
在第二个测试样例中，分子等于2000，分母等于300。如果我们用分子和分母的最大公约数（100）化简分数2000/300，我们得到分数20/3。

## 样例 #1
### 输入
```
3 2
100 5 2
50 10
```
### 输出
```
2 3
2 1
1 1 1
```
## 样例 #2
### 输入
```
4 3
2 5 10 20
100 1 3
```
### 输出
```
1 1
20
3
```
### 算法分类
数学（质数相关）

### 题解综合分析与结论
所有题解的核心思路都是对分子和分母进行质因数分解，通过统计质因数的出现次数，找出分子分母共有的质因数部分进行约分。难点在于数据范围较大，朴素的质因数分解 $O(n\sqrt{a_i})$ 时间复杂度难以通过，因此需要优化质因数分解的方法。不同题解的优化方式有所不同，有的通过筛出质数后再分解，有的通过记录最小质因子，有的使用Pollard - rho算法等。

### 所选的题解
 - **作者：StayAlone (5星)**
    - **关键亮点**：先筛出质数再分解质因数，有效降低时间复杂度。利用桶记录质因数出现次数，清晰地实现约分过程，代码结构清晰，逻辑严谨。
    - **重点代码**：
```cpp
int n, m, a[MAXN], b[MAXN], cnt1[Q], cnt2[Q], del[Q], del2[Q];
int tot, pri[MAXN << 2]; bitset <Q> vis;
vector <int> num1[MAXN], num2[MAXN];

il void init() {
    rep1(i, 2, 1e7) {
        if (!vis[i]) pri[++tot] = i;
        for (int j = 1; j <= tot && 1ll * pri[j] * i <= 1e7; ++j) {
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
}

int main() {
    read(n, m); init(); rer(i, 1, n, a); rer(i, 1, m, b);
    rep1(i, 1, n) {
        int x = a[i];
        rep1(j, 1, tot) {
            int p = pri[j];
            if (p > sqrt(x)) break;
            while (x % p == 0) ++cnt1[p], x /= p, num1[i].eb(p);
        }
        if (x > 1) ++cnt1[x], num1[i].eb(x);
    }
    rep1(i, 1, m) {
        int x = b[i];
        rep1(j, 1, tot) {
            int p = pri[j];
            if (p > sqrt(x)) break;
            while (x % p == 0) ++cnt2[p], x /= p, num2[i].eb(p);
        }
        if (x > 1) ++cnt2[x], num2[i].eb(x);
    }
    rep1(i, 1, 1e7) del[i] = del2[i] = min(cnt1[i], cnt2[i]);
    printf("%d %d\n", n, m);
    rep1(i, 1, n) {
        for (auto v : num1[i]) if (del[v]) --del[v], a[i] /= v;
        printf("%d ", a[i]);
    } puts("");
    rep1(i, 1, m) {
        for (auto v : num2[i]) if (del2[v]) --del2[v], b[i] /= v;
        printf("%d ", b[i]);
    } puts("");
    rout;
}
```
核心实现思想：先通过init函数筛出1到1e7内的质数。然后对分子分母数组中的每个数进行质因数分解，统计每个质因数在分子分母中的出现次数。接着找出分子分母中每个质因数出现次数的最小值，作为约分需要除掉的部分。最后重新遍历每个数的质因数，按要求进行约分并输出。

 - **作者：蒟酱 (4星)**
    - **关键亮点**：在线性筛里筛出每个数的最小质因子，利用这个最小质因子进行质因数分解，优化了分解过程，代码简洁高效。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#define siz(x) int((x).size())
#define cauto const auto
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using std::cin;using std::cout;
using loli=long long;
using uloli=unsigned long long;
using lodb=long double;
using venti=__int128_t;
using pii=std::pair<int,int>;
using inlsi=const std::initializer_list<int>&;
constexpr venti operator""_vt(uloli x){return venti(x);}
constexpr int N=1e7+1;
int n,m,mif[N];
std::basic_string<int>pt,ans1,ans2;
bool pr[N];
pii cnt[N];
signed main(){
    for(int i=2;i<N;i++){if(!pr[i])pt+=i,mif[i]=i;for(int j:pt){if(i*j>=N)break;pr[i*j]=true;mif[i*j]=j;if(i%j==0)break;}}
    cin>>n>>m;
    for(int i=1,x;i<=n;i++)for(int p=mif[cin>>x,ans1+=x,x];x!=1;p=mif[x/=p])cnt[p].fi++;
    for(int i=1,x;i<=m;i++)for(int p=mif[cin>>x,ans2+=x,x];x!=1;p=mif[x/=p])cnt[p].se++;
    for(int i=1,x;i<N;i++)if(cnt[i].fi<cnt[i].se)cnt[i].se=cnt[i].fi;else cnt[i].fi=cnt[i].se;
    cout<<n<<' '<<m<<'\n';
    for(int y;int x:ans1){for(int p=mif[y=1,x];x!=1;p=mif[x/=p])if(cnt[p].fi>0)cnt[p].fi--;else y*=p;cout<<y<<' ';}
    cout<<'\n';
    for(int y;int x:ans2){for(int p=mif[y=1,x];x!=1;p=mif[x/=p])if(cnt[p].se>0)cnt[p].se--;else y*=p;cout<<y<<' ';}
    return 0;
}
```
核心实现思想：先通过线性筛得到每个数的最小质因子mif数组。输入分子分母数组时，利用最小质因子对每个数进行质因数分解并统计质因数出现次数。然后对分子分母质因数出现次数取最小值，最后再次利用最小质因子对每个数进行处理，按要求输出约分后的结果。

 - **作者：Enthon_Yuan (4星)**
    - **关键亮点**：采用线筛弱化版筛出质数，并记录每个数能分解它的一个质数。在分解质因数时记录数的来源位置，乘法时乘到相应位置，有效控制输出量。
    - **重点代码**：
```cpp
const int N = 1e7+5;
const int M = 1e5+5;
const int K = 664580;
int n,m,is[N],pri[N],cnt;
int a[M],b[M];
vector<int> s1[K],s2[K];
int fd(int x)
{
    int l = 1,r = cnt,mid,ans=0;
    while(l <= r)
    {
        mid = l+r>>1;
        if(pri[mid] < x) l=mid+1;
        else if(pri[mid] > x) r=mid-1;
        else return mid;
    }
    assert(0);
    return 0;
}
void q1(int x,int y)
{
    while(is[x])
    {
        s1[is[x]].emplace_back(y);
        x /= pri[is[x]];
    }
    if(x > 1) s1[fd(x)].emplace_back(y);
    return ;
}
void q2(int x,int y)
{
    while(is[x])
    {
        s2[is[x]].emplace_back(y);
        x /= pri[is[x]];
    }
    if(x > 1) s2[fd(x)].emplace_back(y);
}
int ans1[M],ans2[M];
int main()
{
    fo(i,2,1e7)
    {
        if(!is[i]) pri[++cnt]=i;
        fo(j,1,cnt)
        {
            ll g = pri[j]*i;
            if(g > 1e7) break;
            is[g] = j;
        }
    }
    read(n,m);
    fo(i,1,n) read(a[i]),q1(a[i],i),ans1[i]=1;
    fo(i,1,m) read(b[i]),q2(b[i],i),ans2[i]=1;
    fo(i,1,cnt)
    {
        int mm = min(s1[i].size(),s2[i].size());
        fo(j,mm,(int)s1[i].size()-1) ans1[s1[i][j]]*=pri[i];
        fo(j,mm,(int)s2[i].size()-1) ans2[s2[i][j]]*=pri[i];
    }
    printf("%d %d\n",n,m);
    fo(i,1,n) printf("%lld ",ans1[i]);printf("\n");
    fo(i,1,m) printf("%lld ",ans2[i]);printf("\n");
    return 0;
}
```
核心实现思想：先通过弱化版线筛筛出质数并记录每个数能分解它的质数。对分子分母数组中的数进行质因数分解时，记录每个质因数来自原数组的位置。然后根据分子分母质因数个数的最小值，将多余的质因数乘回到原位置对应的数上，最后输出约分后的结果。

### 最优关键思路或技巧
在处理较大数据范围的质因数分解问题时，通过筛法（如线性筛）预处理出质数或每个数的最小质因子，能有效优化质因数分解的时间复杂度。同时，利用数据结构（如桶、vector等）记录质因数及其出现次数，便于约分操作的实现。

### 可拓展之处
此类题目属于数论中分数化简结合质数相关知识的题型。类似算法套路可应用于其他需要对大数进行质因数分解、约分、求最大公约数等场景。例如，在计算多个数的最小公倍数时，也可通过质因数分解来实现。

### 洛谷推荐题目
 - [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：通过对最大公约数和最小公倍数的性质分析，结合质因数分解求解满足条件的数的个数。
 - [P2155 [SDOI2008]沙拉公主的困惑](https://www.luogu.com.cn/problem/P2155)：利用数论知识，通过对阶乘中质因数的分析，结合逆元求解满足条件的数的个数。
 - [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)：单纯考察线性筛质数的模板题，掌握线性筛质数是解决本题及相关数论问题的基础。

### 个人心得摘录与总结
 - **作者：Enthon_Yuan**：尝试过直接输出所有质数以及简单乘法存储变量的方式输出，均因输出量过大导致WA，最终通过记录数的来源位置解决输出量问题。总结出在处理输出时，需要综合考虑题目对输出量的限制，不能简单粗暴处理。 

---
处理用时：111.85秒