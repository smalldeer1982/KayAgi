# 题目信息

# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
3 100
50 50 100
```

### 输出

```
5
2
```

## 样例 #3

### 输入

```
2 50
50 50
```

### 输出

```
-1
0
```

# AI分析结果

### 题目内容翻译
# Greg和朋友们

## 题目描述
一天，Greg和他的朋友们在森林里散步。总共有$n$个人一起走，包括Greg。很快，他发现自己来到了一条河前。大家立刻决定过河。幸运的是，在河岸边上，也就是大家站着的地方，有一条船。我们知道这条船最多能承载总重量为$k$千克的人。

Greg立刻拿出一张纸，列出了他团队中所有人（包括他自己）的体重。结果发现每个人的体重要么是50千克，要么是100千克。现在Greg想知道，要把整个团队运到河对岸，船最少需要过河多少次。船从一岸到另一岸至少需要一个人来驾驶。当船过河时，只要乘客的总重量不超过$k$，可以搭载任意非零数量的乘客。

此外，Greg还想知道，用最少的乘船次数将所有人运到对岸有多少种方法。如果在某次航行中船上的人员组合不同，则认为这两种方法是不同的。

请帮助Greg解决这个问题。

## 说明/提示
在第一个测试用例中，Greg独自走路，因此他只需要一次过河。

在第二个测试用例中，你应该遵循以下计划：
1. 运送两个50千克的人；
2. 运送一个50千克的人回来；
3. 运送一个100千克的人；
4. 运送一个50千克的人回来；
5. 运送两个50千克的人。

总共需要5次航行。根据在步骤2中选择哪个人，我们可以得到两种不同的方法。

## 样例 #1
### 输入
```
1 50
50
```
### 输出
```
1
1
```

## 样例 #2
### 输入
```
3 100
50 50 100
```
### 输出
```
5
2
```

## 样例 #3
### 输入
```
2 50
50 50
```
### 输出
```
-1
0
```

### 题解综合分析与结论
- **思路方面**：所有题解都采用动态规划的思想，通过定义不同的状态来解决问题。状态的定义主要围绕着已渡河和未渡河的50千克与100千克的人数以及船所在的位置或渡河次数。
- **算法要点**：利用状态转移方程，根据当前状态推导出下一个状态。在转移过程中，通过组合数来计算不同人员上船方案的数量。同时，都考虑到了船的载重限制，避免超重情况。
- **解决难点**：难点在于如何合理定义状态和状态转移方程，使得能够准确计算出最少渡河次数和对应的方案数。并且要处理好边界条件以及避免重复计算。

### 所选的题解
#### 作者：gesong (赞：4)
- **星级**：4星
- **关键亮点**：思路清晰，对状态$f_{i,j,k}$的定义明确，即第$i$个过程结束后，还有$j$个50千克，$k$个100千克的人没有过河的方案数。通过奇偶判断区分船是到达对岸还是从对岸回来，分别进行状态转移。代码实现简洁明了，注释详细。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=60,mod=1e9+7;
int f[4*N][N][N],C[N][N],x,y,n,m;
inline int read(){
    char c=getchar();
    int f=1,ans=0;
    while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
    while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
    return ans*f;
}
main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++){
        int xx=read();
        if (xx==50) x++;
        else y++;
    }
    C[0][0]=1;
    for (int i=1;i<=n;i++){
        C[i][0]=1;
        for (int j=1;j<=n;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    f[0][x][y]=1;
    for (int i=1;i<=4*n;i++)
        for (int j=0;j<=x;j++)
            for (int k=0;k<=min(y,n-j);k++){
                if (i&1){
                    for (int a=0;a<=x-j;a++)
                        for (int b=0;b<=y-k;b++)
                            if (!(a==0&&b==0)&&50*a+100*b<=m)
                                f[i][j][k]=(f[i][j][k]+f[i-1][j+a][k+b]*C[j+a][a]%mod*C[k+b][b]%mod)%mod;
                    if (f[i][0][0]){
                        cout <<i<<endl<<f[i][0][0];
                        return 0;
                    }
                }
                else{
                    for (int a=0;a<=j;a++)
                        for (int b=0;b<=k;b++)
                            if (!(a==0&&b==0)&&50*a+100*b<=m)
                                f[i][j][k]=(f[i][j][k]+f[i-1][j-a][k-b]*C[x-j+a][a]%mod*C[y-k+b][b]%mod)%mod;
                }
            }
    puts("-1\n0");
    return 0;
}
```
核心实现思想：通过三层循环枚举过程数$i$、剩余50千克人数$j$和剩余100千克人数$k$。根据$i$的奇偶性，分别枚举本次渡河的50千克和100千克人数，进行状态转移，并在转移过程中判断是否已将所有人运到对岸。

#### 作者：封禁用户 (赞：4)
- **星级**：4星
- **关键亮点**：状态定义$dp[i][j][k]$表示第$i$次运送后对岸有$j$个50kg，$k$个100kg的方案数，较为直观。代码逻辑清晰，通过两次循环分别处理从这岸到那岸和从那岸回来的情况，每次循环中通过四重循环进行状态转移。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
long long n, k;
long long a[55];
long long c[55][55];
long long dp[105][55][55];
/*int会炸！！！！！*/
long long num_50, num_100;
long long old, now;
bool ok;
int main() {
    for(int i = 0; i < 50; i++) {
        c[i][0] = 1;
        for(int j = 1; j <= i; j++) 
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }
    scanf("%lld%lld", &n, &k);
    k /= 50;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        if(a[i] == 50)
            num_50++;
        else
            num_100++;
    }
    old = 1;
    now = 0;
    dp[0][num_50][num_100] = 1;
    for(int l = 0; l < 2 * n; l++) {
    	/*从这岸到那岸*/
        swap(now, old);
        memset(dp[now], 0, sizeof(dp[now]));
        for(int i = 0; i <= num_50; i++) {
            for(int j = 0; j <= num_100; j++) {
                if(i + j * 2 && (i + j * 2) <= k) {
                    for(int x = i; x <= num_50; x++) {
                        for(int y = j; y <= num_100; y++) {
                            dp[now][num_50 - x + i][num_100 - y + j] += dp[old][x][y] * c[x][i] % MOD * c[y][j] % MOD;
                        }
                    }
                }
            }
        }
        if(dp[now][num_50][num_100]) {
            printf("%d\n", l * 2 + 1);
            printf("%lld\n", dp[now][num_50][num_100] % MOD);
            ok = 1;
            break;
            //输出解
        }
        /*从那岸回来*/
        swap(now, old);
        memset(dp[now], 0, sizeof(dp[now]));
        for(int i = 0; i <= num_50; i++) {
            for(int j = 0; j <= num_100; j++) {
                if(i + j * 2 && (i + j * 2) <= k) {
                    for(int x = i; x <= num_50; x++) {
                        for(int y = j; y <= num_100; y++) {
                            dp[now][num_50 - x + i][num_100 - y + j] += dp[old][x][y] * c[x][i] % MOD * c[y][j] % MOD;
                        }
                    }
                }
            }
        }
    }
    if(ok == 0)
        printf("-1\n0");
       //无解
    return 0;
}
```
核心实现思想：通过循环枚举运送次数$l$，每次运送分从这岸到那岸和从那岸回来两个阶段。在每个阶段中，通过多层循环枚举当前岸边和对岸不同体重人数的变化，利用组合数进行状态转移，判断是否完成所有人的运送。

#### 作者：zztqwq (赞：3)
- **星级**：3星
- **关键亮点**：通过$f(pos,j,k)$定义状态，明确表示船在$pos$岸，对岸有$j$个50kg和$k$个100kg的人的方案数，通过不同的公式处理船在不同岸时的状态转移。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
const int mod=1e9+7,N=310;
inline int qpow(int a,int n)
{
    int ans=1;
    while(n)
    {
        if(n&1)ans=(long long)ans*a%mod;
        a=(long long)a*a%mod;
        n>>=1;
    }
    return ans;
}
int inv[N],p[N];
int binom(int n,int m){return (long long)p[n]*inv[n-m]%mod*inv[m]%mod;}
int f[2][60][60];
int main()
{
    p[0]=inv[0]=1;
    for(int i=1;i<=50;i++)p[i]=(long long)p[i-1]*i%mod,inv[i]=qpow(p[i],mod-2);
    int n=read(),K=read(),tot5=0,tot1=0;
    for(int i=1;i<=n;i++)
    {
        int x=read();
        tot5+=(x==50);
        tot1+=(x==100);
    }
    f[0][0][0]=1;
    for(int i=1;i<=4*n;i++)
    {
        for(int j=0;j<=tot5;j++)
            for(int k=0;k<=tot1;k++)
                f[i&1][j][k]=0;
        for(int j=0;j<=tot5;j++)
        {
            for(int k=0;k<=tot1;k++)
            {
                if(i&1)
                {
                    for(int c5=0;c5<=tot5-j;c5++)
                    {
                        for(int c1=0;c1<=tot1-k;c1++)
                        {
                            if(!c5&&!c1)continue;
                            if(50*c5+100*c1>K) continue;
                            f[1][j+c5][k+c1]+=(long long)binom(tot5-j,c5)*binom(tot1-k,c1)%mod*f[0][j][k]%mod;
                            f[1][j+c5][k+c1]%=mod;
                        }
                    }
                }
                else
                {
                    for(int c5=0;c5<=j;c5++)
                    {
                        for(int c1=0;c1<=k;c1++)
                        {
                            if(!c5&&!c1)continue;
                            if(50*c5+100*c1>K) continue;
                            f[0][j-c5][k-c1]+=(long long)binom(j,c5)*binom(k,c1)%mod*f[1][j][k]%mod;
                            f[0][j-c5][k-c1]%mod;
                        }
                    }
                }
            }
        }
        if(f[i&1][tot5][tot1])
        {
            printf("%d\n%d",i,f[i&1][tot5][tot1]);
            return 0;
        }
    }
    printf("-1\n0");
    return 0;
}
```
核心实现思想：通过枚举轮数$i$，根据$i$的奇偶判断船的位置，分别对船在出发岸和对岸的情况进行状态转移，通过枚举每次渡河的50kg和100kg人数，利用组合数更新方案数，判断是否完成所有人的运送。

### 最优关键思路或技巧
- **状态定义**：合理定义状态是解决问题的关键，如定义状态表示已渡河或未渡河的不同体重人数以及船的位置，能清晰地描述问题的不同阶段。
- **状态转移**：根据船的行驶方向（到达对岸或返回），分别制定状态转移方程，结合组合数计算不同人员上船方案，准确地实现状态转移。
- **边界处理**：设置合适的初始状态和边界条件，如初始方案数设为1，以及判断无解的条件（如经过一定次数仍未完成运送）。

### 可拓展之处
同类型题可拓展到其他具有不同限制条件的过河问题，例如人员有多种不同体重，或者船的载重限制更为复杂。类似算法套路主要是动态规划，通过定义合适的状态和状态转移方程来解决问题，可应用于资源分配、路径规划等场景。

### 洛谷相似题目推荐
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：经典的棋盘路径动态规划问题，与本题类似，通过定义状态和状态转移方程求解方案数。
- [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：也是动态规划问题，通过不同的状态转移策略求最优解，与本题在动态规划思路上有相似之处。
- [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：利用动态规划解决在一定条件下的最优路径问题，可锻炼动态规划的思维方式。

### 个人心得摘录与总结
暂无个人心得相关内容。 

---
处理用时：73.46秒