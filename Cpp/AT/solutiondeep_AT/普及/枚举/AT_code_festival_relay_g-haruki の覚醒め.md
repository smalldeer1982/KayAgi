# 题目信息

# haruki の覚醒め

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-relay/tasks/code_festival_relay_g

haruki さんは朝に弱いことで有名です。haruki さんの家には目覚まし時計が $ n $ 個あり、$ i $ 番目の目覚まし時計の音量は $ a_i $ です。

   
haruki さんは鳴っている目覚まし時計の音量の合計が $ m $ 以上にならない限り、目を覚ますことはありません。しかしながら、必要以上に目覚まし時計をセットすると、うるさくて近所迷惑になってしまいます。

   
そこで、合計の音量が $ m $ 以上でかつ最小となるように目覚まし時計を選んだとき、その合計の音量を求めてください。

## 样例 #1

### 输入

```
3 30

25

10

23```

### 输出

```
33```

## 样例 #2

### 输入

```
4 101

10

20

30

40```

### 输出

```
-1```

# AI分析结果

### 题目中文重写
# haruki的觉醒

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-relay/tasks/code_festival_relay_g

haruki 以早上起不来而闻名。haruki 家有 $n$ 个闹钟，第 $i$ 个闹钟的音量是 $a_i$。

haruki 只有在响着的闹钟的音量总和达到 $m$ 以上时才会醒来。然而，如果设置过多的闹钟，会很吵，给邻居带来困扰。

因此，请找出在音量总和达到 $m$ 以上且最小的情况下，这些闹钟的音量总和。

## 样例 #1

### 输入
```
3 30
25
10
23
```

### 输出
```
33
```

## 样例 #2

### 输入
```
4 101
10
20
30
40
```

### 输出
```
-1
```

### 综合分析与结论
这些题解主要围绕01背包算法解决问题，核心都是从 $n$ 个数中选若干数，使其和大于等于 $m$ 且最小。各题解思路大致可分为两类：
1. **转化为常规01背包**：先求所有数的和 $sum$，若 $sum < m$ 则输出 -1；否则将问题转化为在容量为 $sum - m$ 的背包中求最大价值，最后用 $sum$ 减去该最大价值得到结果。
2. **记录和的可达性**：同样先判断 $sum$ 与 $m$ 的大小，若 $sum \geq m$，用布尔数组记录每个和是否可达，最后从 $m$ 开始枚举，找到第一个可达的和即为答案。

### 所选题解
- **MattL（5星）**
    - **关键亮点**：思路清晰，详细推导了动态规划的过程，包括状态转移方程的得出和空间优化，代码注释丰富，易于理解。
    - **个人心得**：作者提到在动态规划求最大值时卡了一段时间，提醒读者要注意求最大值的细节。
- **simonG（4星）**
    - **关键亮点**：简洁明了地阐述了思路，将问题转化为01背包问题的过程清晰，代码实现简洁。
    - **个人心得**：提出“正难则反推”的思维方式，为解决问题提供了新的思路。
- **cjZYZtcl（4星）**
    - **关键亮点**：对背包的含义进行了独特解释，将背包容量数组存为和的可达性，思路新颖，代码中使用了快速读写优化。
    - **个人心得**：无。

### 重点代码
#### MattL
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[55],sum,f[1111111];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];//求和
    }
    sum-=m;
    if(sum<0)
    {
        cout<<-1<<endl;//怎样都不能凑够m
        return 0;
    }
    for(int i=1;i<=n;i++)
        for(int o=sum;o>=a[i];o--)//逆序枚举背包容量最小为a[i]，否则会溢出
            f[o]=max(f[o],f[o-a[i]]+a[i]);//别错了，是求最大值，我在这卡了一段时间……
    cout<<sum+m-f[sum]<<endl;//别忘了加m
    
    return 0;
}
```
**核心思想**：先计算所有数的和 $sum$，若 $sum < m$ 则输出 -1；否则将问题转化为在容量为 $sum - m$ 的背包中求最大价值，最后用 $sum$ 减去该最大价值得到结果。

#### simonG
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101],f[10001],n,m,s;
//s,表示数字的和
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]),s+=a[i];
    if(s>=m)   //否则就不可能和超过m
    {
        //01背包
        for(int i=1; i<=n; i++)
            for(int j=s-m; j>=a[i]; j--)
                //s-m表示剩下数字空间
                f[j]=max(f[j],f[j-a[i]]+a[i]);
        printf("%d\n",s-f[s-m]);
    }
    else
        puts("-1");
    return 0;
}
```
**核心思想**：先计算所有数的和 $s$，若 $s < m$ 则输出 -1；否则将问题转化为在容量为 $s - m$ 的背包中求最大价值，最后用 $s$ 减去该最大价值得到结果。

#### cjZYZtcl
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool f[500005];
int a[55];
inline int read(){
    int x = 0, m = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') m = -1;
        ch = getchar();
    }
    while(isdigit(ch)){
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * m;
}
inline void write(int x){
    if(x < 0){
        putchar('-');
        write(-x);
        return;
    }
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}
signed main(){
    int n = read(), m = read(), sum = 0;
    for(int i = 1; i <= n; i++){
        a[i] = read();
        sum += a[i];
    }
    if(sum < m){
        write(-1);
        putchar('\n');
        return 0;
    }
    memset(f, false, sizeof(f));
    f[0] = true;
    for(int i = 1; i <= n; i++){
        for(int j = sum; j >= a[i]; j--){
            f[j] = f[j] || f[j - a[i]];
        }
    }
    for(int i = m; i <= sum; i++){
        if(f[i]){
            write(i);
            putchar('\n');
            return 0;
        }
    }
}
```
**核心思想**：先计算所有数的和 $sum$，若 $sum < m$ 则输出 -1；否则用布尔数组 $f$ 记录每个和是否可达，最后从 $m$ 开始枚举，找到第一个可达的和即为答案。

### 最优关键思路或技巧
- **正难则反**：将求大于等于 $m$ 的最小和问题转化为在一定容量背包中求最大和问题，简化了问题的求解过程。
- **状态压缩**：在动态规划中，通过观察状态转移方程，将二维数组优化为一维数组，减少了空间复杂度。

### 可拓展之处
同类型题可考察不同约束条件下的组合选择问题，如限定选择的物品数量、选择物品有额外代价等。类似算法套路可应用于其他背包问题变种，如完全背包、多重背包等。

### 推荐题目
- P1048 [NOIP2005 普及组] 采药
- P1049 [NOIP2001 普及组] 装箱问题
- P1616 疯狂的采药

### 个人心得总结
- MattL 提醒在动态规划求最大值时要注意细节，避免出错。
- simonG 提出“正难则反推”的思维方式，为解决问题提供了新的思路。
- Happy_Dream 分享了自己最开始用模拟方法WA很惨的经历，强调了找到正确算法的重要性，同时提醒注意里层循环方向、输出换行和数组清零等细节。 

---
处理用时：48.37秒