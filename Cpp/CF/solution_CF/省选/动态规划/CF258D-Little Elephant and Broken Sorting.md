# Little Elephant and Broken Sorting

## 题目描述

The Little Elephant loves permutations of integers from $ 1 $ to $ n $ very much. But most of all he loves sorting them. To sort a permutation, the Little Elephant repeatedly swaps some elements. As a result, he must receive a permutation $ 1,2,3,...,n $ .

This time the Little Elephant has permutation $ p_{1},p_{2},...,p_{n} $ . Its sorting program needs to make exactly $ m $ moves, during the $ i $ -th move it swaps elements that are at that moment located at the $ a_{i} $ -th and the $ b_{i} $ -th positions. But the Little Elephant's sorting program happened to break down and now on every step it can equiprobably either do nothing or swap the required elements.

Now the Little Elephant doesn't even hope that the program will sort the permutation, but he still wonders: if he runs the program and gets some permutation, how much will the result of sorting resemble the sorted one? For that help the Little Elephant find the mathematical expectation of the number of permutation inversions after all moves of the program are completed.

We'll call a pair of integers $ i,j $ $ (1<=i<j<=n) $ an inversion in permutatuon $ p_{1},p_{2},...,p_{n} $ , if the following inequality holds: $ p_{i}>p_{j} $ .

## 样例 #1

### 输入

```
2 1
1 2
1 2
```

### 输出

```
0.500000000
```

## 样例 #2

### 输入

```
4 3
1 3 2 4
1 2
2 3
1 4
```

### 输出

```
3.000000000
```

# 题解

## 作者：谁是鸽王 (赞：16)

## 题解 CF258D 【Little Elephant and Broken Sorting】

[传送门](https://www.luogu.org/problemnew/show/CF258D)

考虑直接设满足**逆序对**的**充要条件**为$dp$对象。以后学着点。= =

### $dp(i)(j)=P(a_i>a_j)$  

每读入一个$(x,y)$考虑他们对期望逆序对的贡献，

和的期望等于期望的和！

初始条件$dp(t)(i)=[a_t>a_i]$


首先，$dp(x)(y)=0.5$十分显然。



对于$\forall t\not=x,y$



然后$ dp(t)(x)=dp(t)(y)$也很显然



然后$dp(x)(t)=dp(y)(t)=1-dp(t)(y)=1-dp(t)(x)$也很显然，因为这是个排列，不存在相等。



转移方法就不显然了，仔细思考，发现就是



$dp(t)(x)=0.5 \times (dp(t)(x)+dp(t)(y) )$

$dp(t)(y)=0.5 \times (dp(t)(y)+dp(t)(x)) $



你发现是一样滴。

最后答案是:



## $\Sigma _{i<j} {dp(i)(j)}$



上代码，╮(╯▽╰)╭为什么别人可以那么神仙，我好落伍啊QAQ



```cpp
#include<bits/stdc++.h>
#define RP(t,a,b) for(register int (t)=(a),edd_=(b);t<=edd_;++t)

using namespace std;typedef long long ll;typedef double db;
const int maxn=1005;
double dp[maxn][maxn];
int data[maxn];
int t1,t2;
int n,m;
double ans;

int main(){
    
    n=qr(1);
    m=qr(1);
    RP(t,1,n)
	cin>>data[t];
    RP(t,1,n)
	RP(i,1,n)
	dp[t][i]=data[t]>data[i];
    
    RP(t0,1,m){
	cin>>t1;
	cin>>t2;
	RP(t,1,n){
	    dp[t1][t]=dp[t2][t]=(db)0.5*(dp[t1][t]+dp[t2][t]);
	    dp[t][t1]=dp[t][t2]=(db)1-dp[t1][t];
	}
	dp[t1][t2]=dp[t2][t1]=(db)0.5;
    }
    
    RP(t,1,n)
	RP(i,t+1,n)
	ans+=dp[t][i];
    
    printf("%.8lf\n",ans);
    return 0;
}
```



---

## 作者：1saunoya (赞：11)

换一种思考方式，把逆序对的贡献展开。

让 $f_{i,j}$ 变成 $i$ 比 $j$ 大的概率。(位置)


$f_{i,x} = f_{i,y} = \frac{f_{i,x} + f_{i,y}}{2}$。

$f_{x,i} = f_{y,i} = \frac{f_{x,i} + f_{y,i}}{2}$。


然后考虑交换 $x,y$，那么 $x$ 比 $y$ 大和 $y$ 比 $x$ 大的概率相同，所以 $f_{x,y} = f_{y,x} = 0.5$

最后要求的是 $\sum_{i = 1}^{n} \sum_{j=i+1}^{n} f_{i,j}$。


---

## 作者：XL4453 (赞：4)

### $\text{Difficulty : 2600}$

---
### 解题思路：

设 $f_{i,j}$ 表示第 $i$ 位置上的值比第 $j$ 位置上的值大的概率。最终答案即为 $\sum_{i=1}^n\sum_{j=i+1}^n f_{i,j}$。

没有更改时直接两两比较即可，关键考虑更改。若当前可能发生交换的位置为 $x$ 和 $y$，其中 $x<y$。

对于 $f_{x,y}$ 和 $f_{y,x}$，由于给出的是一个排列，没有相等，明显 $f'_{x,y}=f'_{y,x}=\dfrac{1}{2}$。

对于其余的数，如果交换发生则 $f'_{i,x}=f_{i,y}$，$f'_{i,y}=f_{i,x}$，以及 $f'_{x,i}=f_{y,i}$，$f'_{y,i}=f_{x,i}$。不交换不变。两者发生的概率都是 $\dfrac{1}{2}$。

也就是：$f'_{i,x}=f'_{i,y}=\dfrac{f_{i,x}+f_{i,y}}{2}$ 以及 $f'_{x,i}=f'_{y,i}=\dfrac{f_{x,i}+f_{y,i}}{2}$。

---
似乎可以利用 $f_{i,j}+f_{j,i}=1$ 来写出一个更加简单的形式，没啥必要的说。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int n,m,a[1005],x,y;
double f[1005][1005],ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(a[i]>a[j])f[i][j]=1.0;
	while(m--){
		scanf("%d%d",&x,&y);
		for(int i=1;i<=n;i++){
			if(i==x||i==y)continue;
			f[i][x]=f[i][y]=(f[i][x]+f[i][y])/2.0;
			f[x][i]=f[y][i]=(f[x][i]+f[y][i])/2.0;
		}
		f[x][y]=f[y][x]=0.5;
	}
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	ans+=f[i][j];
	printf("%.9lf",ans);
	return 0;
}
```


---

## 作者：密期望 (赞：3)

一个同学的思路，看他一直没有来发题解，我就帮他发了吧(逃)，由于我并不知道该同学的洛谷账号，原谅我没给链接。

核心思路:用dp\[i]\[j]表示第i个数比第j个数大的概率，之后就O(N)修改就可以了。

代码:
```
#include<cstdio>
#include<cstdlib>
#define run
typedef long long ll;
typedef double ld;
const int N=1010;
void file(const char *str){
    char in[100],out[100];
    sprintf(in,"%s.in",str),sprintf(out,"%s.out",str);
    freopen(in,"r",stdin),freopen(out,"w",stdout);
}
ld dp[N][N];
ld buf[N];
ld ans;
int a[N];
int n,m;
void input(){
    scanf("%d%d",&n,&m);
    int x;
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
    }
}
void begin(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=(a[i]>a[j]);
        }
    }
}
void solve(){
    int p1,p2;
    for(int i=0;i<m;i++){
        p1=0;
        p2=0;
        scanf("%d%d",&p1,&p2);
        if(p1!=p2){
            for(int j=1;j<=n;j++){
                if(j!=p1&&j!=p2){
                    buf[j]=dp[p1][j];
                    dp[p1][j]=(dp[p1][j]+dp[p2][j])*0.5;
                    dp[j][p1]=1-dp[p1][j];
                }
            }
            for(int j=1;j<=n;j++){
                if(j!=p1&&j!=p2){
                    dp[p2][j]=(buf[j]+dp[p2][j])*0.5;
                    dp[j][p2]=1-dp[p2][j];
                }
            }
            dp[p1][p2]=dp[p2][p1]=0.5;
        }
    }
}
void output(){
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            ans+=dp[j][i];
        }
    }
    printf("%.8lf",ans);
}
void test(){
    input();
    begin();
    solve();
    output();
}
void all(){
    file("inversion");
    test();
}
int main(){
#ifndef run
    printf("compile successfully\n");
    exit(0);
#endif
    test();
    return 0;
}
```

---

## 作者：Prean (赞：2)

太厉害啦

首先做期望题最不能忘记的就是期望的线性性。

所以我们直接将全局逆序对对数拆成两个数其中一个比另一个大的期望（概率），设为 $ f[i][j] $，初值为 $ [a_i>b_j] $。

如果我们修改两个位置 $ x,y $，最直接的修改一定就是令 $ f[x][y]=0.5 $。

那么别的位置呢？

我们发现这会令 $ f[i][x]=f[i][y],f[x][i]=f[y][i] $，而且因为这是一个排列，很明显有 $ f[a][b]+f[b][a]=1 $。

那么我们怎么才能转移 $ f $？

很容易发现一件事情，转移前的 $ f[i][x]+f[i][y] $ 等于转移后的 $ f[i][x]+f[i][y] $。

为什么呢？我比两个数大的概率之和，然后交换一下，明显还是不变嘛。

所以有新的 $ f[i][x]=f[i][y] $ 等于原来的 $ \frac {f[i][x]+f[i][y]} 2 $。

于是这样大力转移就好啦。
```cpp
#include<cstdio>
const int M=1005;
int n,m,a[M];double ans,dp[M][M];
signed main(){
	int i,j,x,y;scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%d",a+i);
	for(i=1;i<=n;++i)for(j=1;j<=n;++j)dp[i][j]=a[i]>a[j];
	while(m--){
		scanf("%d%d",&x,&y);
		for(i=1;i<=n;++i)dp[x][i]=dp[y][i]=.5*(dp[x][i]+dp[y][i]),dp[i][x]=dp[i][y]=1-dp[x][i];dp[x][y]=dp[y][x]=.5;
	}
	for(i=1;i<=n;++i)for(j=i+1;j<=n;++j)ans+=dp[i][j];printf("%.9lf",ans);
}
```

---

## 作者：Meteor_ (赞：0)

# CF258D Little Elephant and Broken Sorting 题解

## 题目大意

有一个 $1 \sim n$ 的排列，会进行 $m$ 次操作，操作为交换两位置的数，每次操作都有 $50\%$ 的概率进行，求 $m$ 次操作之后的期望逆序对个数。（$n, m \le 1000$）

## 分析

感觉大体方向是比较好想的。看完数据范围，一眼期望 $dp$。那么就来考虑怎么设计 $dp$。

## 题解

第一反应想到计数，用 $dp_{i, j}$ 来代表数对 $(i, j)$ 对最终答案作出的贡献。但是在写转移时发现有一点麻烦，于是浅改一下思路，用 $dp_{i, j}$ 来代表 位置 $i$ 上的数比位置 $j$ 上的数大的概率。

我们很容易得到，最终答案就是 $\displaystyle \sum_{i = 1}^{n} \sum_{j = i + 1}^{n} dp_{i, j}$。

$dp$ 的初始值比较好想，就是 $O(n^2)$ 跑一遍，对于每一个 $i$ 位置上的数大于 $j$ 位置上的数的情况，把 $dp_{i, j}$ 赋成 $1$ 即可。接下来我们考虑操作一次会使 $dp$ 怎样变化。假设我们这一次操作所交换的两个位置是 $x$ 和 $y$，$x$ 位置上的数为 $a_x$，$y$ 位置上的数为 $a_y$。

最好想的就是 $dp_{x, y}$ 和 $dp_{y, x}$ 如何变化。首先我们想到，因为这是一个排列，所以每一个位置上的数不相同，所以在交换 $x$ 和 $y$ 以后，$dp_{x, y}$ 和 $dp_{y, x}$ 都会被直接赋值成 $0.5$。

而对于其他的位置上的数，我们再设一个位置 $t(1 \le t \le n \land t \neq x \land t \neq y)$（$\land$ 是“且”的意思，$\lor$ 是“或”的意思），其位置上的数为 $a_t$，那么一定有：

$$
\begin{aligned}

dp_{x, t} &= 1 - dp_{t, x}\\

dp_{x, t} &= 1 - dp_{t, x}\\

dp_{t, x} = dp_{t, y} &= \frac{dp_{t, x} + dp_{t, y}}{2}\\

dp_{x, t} = dp_{y, t} &= \frac{dp_{x, t} + dp_{y, t}}{2}

\end{aligned}
$$

前两个式子显然成立（但是好像这个题没用上），我们考虑怎么去证明后两个式子。其实也很好证，因为如果两者换位成功，则 $dp_{t, x} = dp_{t, y}$，否则不变。而我们又知道，成功的几率为 $0.5$，那么 $\displaystyle dp_{t, x} = \frac{dp_{t, x} + dp_{t, y}}{2}$ 显然成立。其他的同理。

既然有了这些结论，那么我们就可以对于每一次操作，枚举一遍 $t$。再算上给 $dp$ 赋初值的时间复杂度，那么总的时间复杂度就是 $O(n^2 + mn)$。

## 代码

```cpp
//https://www.luogu.com.cn/problem/CF258D Little Elephant and Broken Sorting
#include <bits/stdc++.h>
#define M 1005

using namespace std;

inline int read() {
    int x = 0, s = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')
            s = -s;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * s;
}

void write(int x) {
    if(x < 0)  {
        x = ~(x - 1);
        putchar('-');
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}

int n, m, a[M];
long double dp[M][M], ans;

signed main() {
    n = read();
    m = read();
    for(int i = 1; i <= n; ++ i)
        a[i] = read();
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n; ++ j)
            if(a[i] > a[j])
                dp[i][j] = 1;
    for(int i = 1; i <= m; ++ i) {
        int x = read(), y = read();
        if(x == y)
            continue;
        for(int j = 1; j <= n; ++ j) {
            if(j != x && j != y) {
                dp[y][j] = dp[x][j] = dp[x][j] / 2 + dp[y][j] / 2;
                dp[j][y] = dp[j][x] = dp[j][x] / 2 + dp[j][y] / 2;
            }
        }
        dp[x][y] = 0.5;
        dp[y][x] = 0.5;
    }
    for(int i = 1; i <= n; ++ i)
        for(int j = i + 1; j <= n; ++ j)
            ans += dp[i][j];
    printf("%Lf", ans);
}
```

---

## 作者：Tastoya (赞：0)

### 题目大意
有一个 $1 \sim n$ 的排列 $a$，会进行 $m$ 次操作，操作为交换 $x,y$。每次操作都有 $50\%$ 的概率进行。

求进行 $m$ 次操作以后的期望逆序对个数。

（$n,m \le 1000$）。
### 思路
这道题非常巧妙。

记 $dp_{i,j}$ 表示 $a_i>a_j$ 的概率，初始值很好设，直接根据初始给出的排列情况进行赋值。

- 若 $a_i>a_j$，则 $dp_{i,j}=1$；
- 若 $a_i < a_j$，则 $dp_{j,i}=1$。

考虑如果我们交换 $x$ 和 $y$ 的位置，会产生什么影响。对于 $\forall i,j \in \left[ 1,n \right]$，其中 $i,j$ 没有与 $x$ 或 $y$ 的情况，不会影响 $dp_{i,j}$ 的值。

记 $f_{i,j}$ 表示未更改前的 $dp$ 数组，考虑有 $x,y$ 的情况，显然有

$$dp_{i,x}=\dfrac{f_{i,x}+f_{i,y}}{2}$$
$$dp_{i,y}=\dfrac{f_{i,x}+f_{i,y}}{2}$$
$$dp_{x,i}=\dfrac{f_{x,i}+f_{y,i}}{2}$$
$$dp_{y,i}=\dfrac{f_{x,i}+f_{y,i}}{2}$$
因为交换成功的概率是 $50\%$，那么交换后的期望就是交换成功和交换失败的平均值。

所以最后答案为
$$\sum^{n}_{i=1}\sum^{n}_{j=i+1}dp_{i,j}$$
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1050;

int n,m;

int a[N];

double dp[N][N];

int main() {
    cin >> n >> m;
    for(int i = 1;i <= n; i++) 
        cin >> a[i];
    
    for(int i = 1;i <= n; i++) {
        for(int j = i + 1;j <= n; j++) {
            if(a[i] > a[j])
                dp[i][j] = 1.00000;
            else
                dp[j][i] = 1.00000;
        }
    }

    for(int i = 1,x,y;i <= m; i++) {
        cin >> x >> y;

        for(int i = 1;i <= n; i++) {
            if(i == x || i == y)
                continue;
            
            dp[i][x] = dp[i][y] = 0.5 * (dp[i][x] + dp[i][y]);
            dp[x][i] = dp[y][i] = 0.5 * (dp[x][i] + dp[y][i]);
        }

        dp[x][y] = dp[y][x] = 0.5;
    }

    double ans = 0;

    for(int i = 1;i <= n; i++) {
        for(int j = i + 1;j <= n; j++) {
            ans += dp[i][j];
        }
    }

    cout.precision(12);
    cout << fixed << ans << "\n";
    return 0;
}
```

---

## 作者：User_Authorized (赞：0)

## 题意

给定一个长度为 $n$ 的排列 $a$ 和 $m$ 个形如 $\left(x,y\right)$ 的操作，每次操作有 $50\%$ 的概率交换 $a_x, a_y$，求最终排列的期望逆序对数。

（$1 \le n,m \le 5000$）。

## 题解

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-CF258D.html)**

首先转化答案

$$\text{Ans} = \sum\limits_{i = 1}^{n} \sum\limits_{j = i + 1}^{n} \operatorname{P}\left(a_i > a_j\right)$$

考虑设 $f_{i, j} = \operatorname{P}\left(a_i > a_j\right)$。初始值很显然

$$f_{i, j} = \left[a_i > a_j\right]$$

考虑交换操作 $\left(x, y\right)$ 对该数组值的影响，设 $g$ 为更改操作前 $f$ 的拷贝，对于 $\forall t \neq x \land t \neq y$，有 

$$\begin{aligned}
f_{t, x} &= \dfrac{1}{2} g_{t, x} + \dfrac{1}{2} g_{t, y} \\
f_{t, y} &= \dfrac{1}{2} g_{t, x} + \dfrac{1}{2} g_{t, y} \\
f_{x, t} &= \dfrac{1}{2} g_{x, t} + \dfrac{1}{2} g_{y, t} \\
f_{y, t} &= \dfrac{1}{2} g_{x, t} + \dfrac{1}{2} g_{y, t} \\
\end{aligned}$$

因为原数组为排列，即元素互不相同，那么对于 $x, y$，有

$$\begin{aligned}
f_{x, y} &= 0.5 \\
f_{y, x} &= 0.5 \\
\end{aligned}$$

每次操作 $\mathcal{O}(n)$ 维护即可，总复杂度 $\mathcal{O}(n^2 + nm)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef double realType;
typedef std::vector<realType> realVector;
typedef std::vector<realVector> realMatrix;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    ValueVector source(N + 1);
    realMatrix F(N + 1, realVector(N + 1, 0));

    for (valueType i = 1; i <= N; ++i)
        std::cin >> source[i];

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = i + 1; j <= N; ++j) {
            if (source[i] > source[j]) {
                F[i][j] = 1.0;
            } else {
                F[j][i] = 1.0;
            }
        }
    }

    for (valueType t = 0; t < M; ++t) {
        valueType a, b;

        std::cin >> a >> b;

        for (valueType i = 1; i <= N; ++i) {
            if (i == a || i == b)
                continue;

            F[i][a] = F[i][b] = (F[i][a] + F[i][b]) / 2;
            F[a][i] = F[b][i] = (F[a][i] + F[b][i]) / 2;
        }

        F[a][b] = F[b][a] = 0.5;
    }

    realType ans = 0;

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = i + 1; j <= N; ++j) {
            ans += F[i][j];
        }
    }

    std::cout << std::fixed << std::setprecision(10) << ans << std::endl;

    return 0;
}
```

---

## 作者：happybob (赞：0)

考虑 $f_{i,j}$ 表示当前 $a_i < a_j$ 的概率。

从前往后处理每个操作。

对于 $x,y$ 互换，显然 $f_{x,y} = f_{y,x}$。那具体等于什么呢，应该是 $\dfrac{f_{x,y}+f_{y,x}}{2}$，也就是有一半的概率互换。

对于任意 $i \neq x$ 且 $i \neq y$，$f_{i,x} = \dfrac{f_{i,x}+f_{i,y}}{2}$。也是一样的，有一半的概率交换。同理 $f_{x,i}$，$f_{i,y}$ 和 $f_{y,i}$ 也要这样算。

最终答案为 $\sum \limits_{i=1}^n \sum \limits_{j=1}^{i-1} f_{i,j}$。

---

## 作者：Aw顿顿 (赞：0)

**核心思想：期望的线性性质。**

------

双倍经验：[AT4513 [AGC030D] Inversion Sum](https://www.luogu.com.cn/problem/AT4513)

令 $f(i,j)$ 表示 $i$ 比 $j$ 大的概率，则根据期望的线性性质得到：

$$f(i,x)=f(i,y)=\dfrac{f(i,x)+f(i,y)}{2}$$

$$f(x,i)=f(y,i)=\dfrac{f(x,i)+f(y,i)}{2}$$

由于每次等概率求取，因此对于 $f(x,y)$ 也要进行一次计算，因此答案为：

$$2^q\times\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}f(i,j)$$

代码实现如下：


```cpp
#include<bits/stdc++.h>
#define N 3005
#define mod 1000000007
#define int long long
using namespace std;
int n,q,a[N];
double f[N][N],ans;
int ksm(int b,int p){
	int s=1;b%=mod; 
	while(p){
		if(p&1)s=s*b%mod;
		b=b*b%mod;p>>=1;
	}return s%mod;
}signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		if(a[i]<a[j])f[i][j]=1;
	for(int i=1;i<=q;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		f[x][y]=f[y][x]=(f[x][y]+f[y][x])/2;
		for(int j=1;j<=n;j++){
			if(j==x||j==y)continue;
			f[x][j]=f[y][j]=(f[x][j]+f[y][j])/2;
			f[j][x]=f[j][y]=(f[j][x]+f[j][y])/2;
		}
	}for(int i=1;i<=n;i++)for(int j=1;j<i;j++)
		ans=(ans+f[i][j]);
	printf("%.10lf",ans);
	return 0;
}
```

时间复杂度 $O(qn)$ 可以通过本题。

---

## 作者：ZigZagKmp (赞：0)

## 题意简述
给定一个长度为 $n$ 序列和 $m$ 次操作，每次操作交换一对位置上的元素。

现在每一个操作可以做也可以不做，求所有操作方案得到的最终序列的逆序对个数的期望。

$n,m\le 1000$。

## 算法分析

~~本题和AGC030D几乎完全相同，不知道是谁抄谁的。~~

期望有线性性，启发我们把逆序对拆开来，拆成**每一个位置对对答案的贡献**。

我们维护所有二元组 $\left(x,y\right)$ 满足 $a_x<a_y$ 的概率。

这样对于一次交换操作的做或不做，只会影响到**与当前操作相关**的二元组，这些二元组要么包含第一个数，要么包含第二个数，总量为 $O(n)$ ，可以接受。

总时间复杂度为 $O(n^2+nm)$ 。

~~本题精度似乎很松？~~

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 3005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long
#define lb long double
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
int a[maxn];
lb dp[maxn][maxn];
signed main(){
	read(n);read(m);
	for(int i=1;i<=n;++i)read(a[i]);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			dp[i][j]=(a[i]<a[j]);
		}
	}
	for(int i=1,x,y;i<=m;++i){
		read(x);read(y);
		dp[x][y]=dp[y][x]=0.5;
        //因为有了交换，所以两者的大小于情况互补，可以直接都赋为0.5
        //注：由于本题保证a是一个排列，所以不存在两者相等的情况，可以这样简化，否则应当将两者原概率取平均
		for(int j=1;j<=n;++j){
			if(j!=x&&j!=y){//下面两种情况同理求平均
				dp[x][j]=dp[y][j]=0.5*(dp[x][j]+dp[y][j]);
				dp[j][x]=dp[j][y]=0.5*(dp[j][x]+dp[j][y]);
			}
		}
	}
	lb ans=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<i;++j){
			ans=(ans+dp[i][j]);
		}
	}
	printf("%.10lf\n",(double)ans);
	return 0;
}
```

---

## 作者：cirnovsky (赞：0)

## 题意简述

求若干次交换操作后的序列逆序对个数期望。

## 题解

要啥设啥惯性设计状态不好。

设 $f_{i,j}=P(a_{i}>a_{j}),i<j$。

我们假设当前我们的操作为交换 $a_{x},a_{y}$。

那么 $f_{i,x}=f_{i,y}$，也有 $f_{i,x}=f_{i,y}=1-f_{x,i}=1-f_{y,i}$。

转移比较神奇
$$
\begin{cases}
f_{i,x}=\frac{f_{i,x}+f_{i,y}}{2} \\
f_{i,y}=\frac{f_{i,x}+f_{i,y}}{2} \\
\end{cases}
$$
答案即
$$
\sum_{i=1}^{n}\sum_{j=i+1}^{n}f_{i,j}
$$
边界条件
$$
f_{i,j}=[a_{i}>a_{j}],i<j
$$
这题的状态设计也给我提了个醒，不要惯性做题。

```cpp
#include <cstdio>

const int MAXN = 1000 + 5;

int N, M;
int a[MAXN];
double f[MAXN][MAXN];

int main () {
	scanf ( "%d%d", &N, &M );
	for ( int i = 1; i <= N; ++ i )	scanf ( "%d", &a[i] );
	for ( int i = 1; i <= N; ++ i ) {
		for ( int j = 1; j <= N; ++ j ) {
			if ( a[i] > a[j] )	f[i][j] = 1;
			else	f[i][j] = 0;
		}
	}
	while ( M -- > 0 ) {
		int x, y;
		scanf ( "%d%d", &x, &y );
		for ( int i = 1; i <= N; ++ i ) {
			f[i][x] = f[i][y] = ( f[i][x] + f[i][y] ) / 2;
			f[x][i] = f[y][i] = 1 - f[i][x];
		}
		f[x][y] = f[y][x] = 0.5;
	}
	double Ans = 0;
	for ( int i = 1; i <= N; ++ i ) {
		for ( int j = i + 1; j <= N; ++ j )	Ans += f[i][j];
	}
	printf ( "%.6lf\n", Ans );
	return 0;
}                          
```

---

## 作者：是个妹子啦 (赞：0)

~~假~~[双倍经验](https://www.luogu.com.cn/problem/AT4513) (建议先做CF这个，AT的在$mod$意义下，而且还要转换题意)

$N$很小，考虑直接枚举点对$(i,j)(1\le i<j\le N)$，来统计逆序对

$f[i][j]$表示位置$i>j$概率，初始化$f[i][j]=a[i]>a[j]$，

$f[x][y]=f[y][x]=0.5$，因为$x,y$之间谁大的概率相同

$f[i][x]=f[i][y]$，由上式子可知

每次修改$x,y$只会对$(i,j)$至少有一个为$x$或$y$的数产生影响，所以暴力转移

$\large f_{i,x}=f_{i,y}=\frac{f_{i,x}+f_{i,y}}2$            $\large f_{x,i}=f_{y,i}=\frac{f_{x,i}+f_{y,i}}2$

答案就是
$$
\large\sum_{i=1}^n\sum_{j=i+1}^nf_{i,j}
$$

```cpp
double f[N][N],ans; int a[N],n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%d",&a[i]);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			f[i][j] = a[i] > a[j];
	int u,v;
	while(m--){
		scanf("%d%d",&u,&v);
		for(int i = 1;i <= n;++i){
			f[u][i] = f[v][i] = 0.5 * (f[u][i]+f[v][i]);
			f[i][u] = f[i][v] = 1 - f[u][i];
		}
		f[u][v] = f[v][u] = 0.5;
	}
	for(int i = 1;i <= n;++i)
		for(int j = i+1;j <= n;++j)
			ans += f[i][j];
	printf("%.9f",ans);
}
```



---

## 作者：TempestMiku (赞：0)

# [洛谷题目](https://www.luogu.com.cn/problem/CF258D) & [CodeForce题目](https://codeforces.com/problemset/problem/258/D)

看到数据范围 $n\le 5000$ 考虑动态规划，可以开两维数组 $dp_{i,j}$ 表示第 $i$ 个位置比第 $j$ 个位置大的概率。

答案即为：

$$\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}{dp_{i,j}}$$

当我们交换 $x,y$ 时，其他数也会同等的受到 $50\%$ 的影响。所以有 $dp_{x,i}=dp_{y,i}=\frac{dp_{x,i}+dp_{y,i}}{2}$ 且 $dp_{i,x}=dp_{i,y}=\frac{dp_{i,x}+dp_{i,y}}{2}$。

最后如果交换 $x$ 和 $y$ 则 $x>y$ 和 $y>x$ 的概率都是 $50\%$，因为排列中每个数都不相同，无论是之前哪个大，都有 $50\%$ 概率变成比另一个小的。所以交换后 $dp_{x,y}=dp_{y,x}=0.5$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
int n,m;
double Tempestissimo(0);
double dp[5005][5005];
int a[5005];
signed main(void){
    n=read(),m=read();
    for(register int i=1;i<=n;i++){
        a[i]=read();
    }
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=n;j++){
            if(i==j) continue;
            if(a[i]>a[j]){
                dp[i][j]=1;
            }
            else{
                dp[i][j]=0;
            }
        }
    }
    while(m--){
        register int x=read(),y=read();
        for(register int i=1;i<=n;i++){
            if(i==x||i==y) continue;
            dp[x][i]=dp[y][i]=(dp[x][i]+dp[y][i])/2;
            dp[i][x]=dp[i][y]=(dp[i][x]+dp[i][y])/2;
        }
        dp[x][y]=dp[y][x]=0.5;
    }
    for(register int i=1;i<=n-1;i++){
        for(register int j=i+1;j<=n;j++){
            Tempestissimo+=dp[i][j];
        }
    }
    printf("%.9lf",Tempestissimo);
    return 0;
}
```




---

