# [Algo Beat Contest 002 D] Distance of Trip

## 题目背景

| Problem | Score | Idea | Std | Data | Check | Solution |
| :----------------------------------: | :---: | :---------------------------------------------------: | :---------------------------------------------------: | :---------------------------------------------: | :-------------------------------------------------: | :----------------------------------------------------------: |
|    $\text{D - Distance of Trip}$     | $400$ | [zhoumurui](https://www.luogu.com.cn/user/305928) | [zhoumurui](https://www.luogu.com.cn/user/305928) | [joe_zxq](https://www.luogu.com.cn/user/623577) | [joe_zxq](https://www.luogu.com.cn/user/623577) |     [Link](https://www.luogu.com.cn/article/2ezk7trk) by [zhoumurui](https://www.luogu.com.cn/user/305928)   |


[![image.png](https://pic1.imgdb.cn/item/67a9f552d0e0a243d4fdff9c.png)](https://pic1.imgdb.cn/item/67a9f552d0e0a243d4fdff9c.png)


## 题目描述

在和小伙伴们一起玩耍了几天后，Cirno 开始觉得没日没夜地玩冻青蛙的游戏对她而言已经有些无聊了。她悄无声息地离开了雾之湖，她要出去走走。

第二天早上，Cirno 发现自己身处于草木繁茂的森林中，她不知道她是怎么走到这个地方来的，但好在她还随身携带了指南针。她决定一直往一个方向走，这样一定能够离开森林。

接下来的 $T$ 秒，每一秒 Cirno 会从以下 $3$ 个选项中**等概率随机**选择一项：

- 向东移动 $1$ 米。
- 向南移动 $1$ 米。
- 先向东移动 $1$ 米，然后向南移动 $1$ 米。

现在告诉你 $T$，请你计算 Cirno 在 $T$ 秒内的位移大小的期望值。

> Cirno 一段时间内的位移大小定义为这段时间结束前 Cirno 的位置和结束后 Cirno 的位置的直线距离。

## 说明/提示

**【样例解释 #1】**

有以下 $9$ 种可能：

- Cirno 在第一秒向东移动了 $1$ 米，在第二秒向东移动了 $1$ 米。Cirno 移动的距离是 $2$ 米。
- Cirno 在第一秒向东移动了 $1$ 米，在第二秒向南移动了 $1$ 米。Cirno 移动的距离是 $\sqrt2$ 米。
- Cirno 在第一秒向东移动了 $1$ 米，在第二秒向东移动了 $1$ 米又向南移动 $1$ 米。Cirno 移动的距离是 $\sqrt5$ 米。
- Cirno 在第一秒向南移动了 $1$ 米，在第二秒向东移动了 $1$ 米。Cirno 移动的距离是 $\sqrt2$ 米。
- Cirno 在第一秒向南移动了 $1$ 米，在第二秒向南移动了 $1$ 米。Cirno 移动的距离是 $2$ 米。
- Cirno 在第一秒向南移动了 $1$ 米，在第二秒向东移动了 $1$ 米又向南移动 $1$ 米。Cirno 移动的距离是 $\sqrt5$ 米。
- Cirno 在第一秒向东移动了 $1$ 米又向南移动 $1$ 米，在第二秒向东移动了 $1$ 米。Cirno 移动的距离是 $\sqrt5$ 米。
- Cirno 在第一秒向东移动了 $1$ 米又向南移动 $1$ 米，在第二秒向南移动了 $1$ 米。Cirno 移动的距离是 $\sqrt5$ 米。
- Cirno 在第一秒向东移动了 $1$ 米又向南移动 $1$ 米，在第二秒向东移动了 $1$ 米又向南移动 $1$ 米。Cirno 移动的距离是 $2\sqrt2$ 米。

以上 $9$ 种可能发生的概率均为 $1/9$，因此 Cirno 移动的距离的期望值为 $\displaystyle \frac{1}{9} \times (2+\sqrt2+\sqrt5+\sqrt2+2+\sqrt5+\sqrt5+\sqrt5+2\sqrt2) =  \frac{4+4\sqrt2+4\sqrt5}{9}$，约等于 $2.06679179$。

**【数据范围】**

- $1 \le T \le 200$。



## 样例 #1

### 输入

```
2```

### 输出

```
2.06679179```

# 题解

## 作者：weifengzhaomi (赞：7)

## 思路：

看完题目后，应该都能知道这是一道 DP 题。

### 设状态

设 $dp_{i,j,k}$ 表示第 $k$ 秒后，在 $(x,y)$ 的概率。

### 设转移

如果当前位置为 $(x,y)$ 的话，那么，按照题目的做法，一共有三种走法，如此，把每种走法都加到一起，再乘一个 $\frac{1}{3}$ 就是走到当前位置的概率。

则有转移状态：

$$dp_{i,j,k} = \frac{1}{3}(dp_{x−1,y,z−1}+dp_{x,y−1,z−1}+f_{x−1,y−1,z−1})$$

接下来，枚举每个位置，求出到这个位置的概率，最后求和就可以了。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
double dp[210][210][210],ans;
int n;
signed main(){
	scanf("%d",&n),dp[0][0][0] = 1;
	for (int i = 1;i <= n;i++)
		for (int j = 0;j <= n;j++)
			for (int k = 0;k <= n;k++){
				if (j > 0) dp[j][k][i] += dp[j - 1][k][i - 1];
				if (k > 0) dp[j][k][i] += dp[j][k - 1][i - 1];
				if (j > 0 && k > 0) dp[j][k][i] += dp[j - 1][k - 1][i - 1];
				dp[j][k][i] /= 3.0;
			}
	for (int i = 0;i <= n;i++)
		for (int j = 0;j <= n;j++) ans += dp[i][j][n] * sqrt(i * i + j * j);
	printf("%.9lf\n",ans);
}
```

---

## 作者：zhoumurui (赞：5)

### 题面简述

![](https://cdn.luogu.com.cn/upload/image_hosting/8bmmc9v2.png)

### 解题思路

令 $f_{x,y,z}$ 表示 Cirno 在 第 $z$ 秒恰好走到 $(x,y)$ 的概率。

考虑动态规划。如果 Cirno 在第 $z$ 秒走到了 $(x,y)$，那么它在第 $z-1$ 秒可能在 $(x,y-1)$、$(x-1,y)$ 或 $(x-1,y-1)$。

当她在这些位置的时候，各有 $\frac{1}{3}$ 的概率来到 $(x,y)$。

因此状态转移方程是 $f_{x,y,z}=\frac{1}{3}(f_{x-1,y,z-1}+f_{x,y-1,z-1}+f_{x-1,y-1,z-1})$。

> 期望是试验中每次可能结果的概率乘以其结果的总和。

我们想要计算 Cirno 到达的位置与起点直线距离的期望值。那么我们只需要枚举所有 Cirno 可能到达的位置即可。

她每秒最多往东走一格，往南走一格，那么她可能到达的位置 $(x,y)$ 一定满足 $0 \le x,y \le T$。

我们在这个范围内枚举所有的 $(x,y)$，加上 **Cirno 在 $T$ 秒后恰好来到 $(x,y)$ 的概率**即 $f_{x,y,T}$ **乘上 $(x,y)$ 到起点的直线距离**即 $\sqrt{x^2+y^2}$ 即可。

### 核心代码展示

dp 时要判越界。

```cpp
double f[205][205][205];
signed main(){
    int t;
    cin>>t;
    f[0][0][0]=1;
    for (int i=1;i<=t;i++){
        for (int j=0;j<=t;j++){
            for (int k=0;k<=t;k++){
                if (j>0)f[j][k][i]+=f[j-1][k][i-1];
                if (k>0)f[j][k][i]+=f[j][k-1][i-1];
                if (j>0&&k>0)f[j][k][i]+=f[j-1][k-1][i-1];
                f[j][k][i]/=3.0;
            }
        }
    }
    double ans1=0;
    for (int i=0;i<=t;i++){
        for (int j=0;j<=t;j++){
            //cout<<i<<" "<<j<<" "<<f[i][j][t]<<"\n";
            ans1+=f[i][j][t]*sqrt(i*i+j*j);
        }
    }
    printf("%.10lf",ans1);
    return 0;
}

---

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P12717)
## 前言
没打比赛，前来水题解。
## 思路
首先我们可以知道，一共有 $3^T$ 种方案。

很明显，$3^T$ 会超时，不妨倒过来，从 $T^3$ 的思路去想（这步有点玄学）。

这题就是走路，容易想到用**搜索**或**动态规划**。

由于没有地图，所以用**动态规划**进行转移。

看到样例解释，不难发现，用到了**勾股定理**。

> 勾股定理，是一个基本的几何定理，指直角三角形的两条直角边的平方和等于斜边的平方。中国古代称直角三角形为勾股形，并且直角边中较小者为勾，另一长直角边为股，斜边为弦，所以称这个定理为勾股定理，也有人称商高定理。

然后，既然思路是 $T^3$，则 $dp$ 是三维数组。

于是，我们可以定义 $dp_{i,j,k}$ 表示走到 $(i,j)$ 刚好用 $k$ 秒的概率。

若第 $k$ 秒在 $(i,j)$，则由题目给的走法：

- 向东移动 $1$ 米。
- 向南移动 $1$ 米。
- 先向东移动 $1$ 米，然后向南移动 $1$ 米。

可知，第 $k-1$ 秒，Cirno 应该在 $(i,j−1)$、$(i−1,j)$ 或 $(i−1,j−1)$ 处。

第 $k$ 秒走到 $(i,j)$ 的概率是 $\frac{1}{3}\times(dp_{i,j-1,k-1}+dp_{i-1,j,k-1}+dp_{i-1,j-1,k-1})$。还是很和谐的一个式子呢！说明我们推的没错。

最后概率 $dp_{i,j,k}$ 还要乘上距离，用到了上面讲到的**勾股定理**。

讲完了，开始写代码。注意类型用 double。

> 本题使用 SPJ，你的代码获得一个测试点的分数当且仅当你的代码对于该测试点的输入数据输出的答案与该测试点的输出数据的差不大于 $10^{−6}$。

（还真是 $O(T^3)$ 哎！）
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std; 
const int N=205;
int T;
double dp[N][N][N],ans;
int main(){
    scanf("%d",&T);
    dp[0][0][0]=1;//初始化 
    for(int i=1;i<=T;i++)
        for(int j=0;j<=T;j++)
            for(int k=0;k<=T;k++){
            	//转移 
                dp[j][k][i]+=dp[j-1][k][i-1];
                dp[j][k][i]+=dp[j][k-1][i-1];
                dp[j][k][i]+=dp[j-1][k-1][i-1];
                dp[j][k][i]*=(1.0/3);//乘上 1/3 
            }
    for(int i=0;i<=T;i++)
        for(int j=0;j<=T;j++)
            ans+=dp[i][j][T]*sqrt(i*i+j*j);//距离乘概率 
    printf("%.7lf",ans);//精度 
    return 0;
}
```
别急着抄，这代码会 RE。

为什么呢？因为转移时会越界。

加上判断条件。
## AC Code!
```cpp
#include<bits/stdc++.h>
using namespace std; 
const int N=205;
int T;
double dp[N][N][N],ans;
int main(){
    scanf("%d",&T);
    dp[0][0][0]=1;//初始化 
    for(int i=1;i<=T;i++)
        for(int j=0;j<=T;j++)
            for(int k=0;k<=T;k++){
            	//转移（不能越界） 
                if(j>=1) dp[j][k][i]+=dp[j-1][k][i-1];
                if(k>=1) dp[j][k][i]+=dp[j][k-1][i-1];
                if(j>=1&&k>=1) dp[j][k][i]+=dp[j-1][k-1][i-1];
                dp[j][k][i]*=(1.0/3);//乘上 1/3 
            }
    for(int i=0;i<=T;i++)
        for(int j=0;j<=T;j++)
            ans+=dp[i][j][T]*sqrt(i*i+j*j);//距离乘概率 
    printf("%.7lf",ans);//精度 
    return 0;
}
```
撒花。

---

## 作者：ArisakaMashiro (赞：3)

~~赛时糖丸了没想出 dp 做法，靠着打表和数据分析能力水过去了。~~

分析题意，我们考虑预处理出每个点被到达的方案数，利用方案数、概率和期望间的转换即可得到答案。

问题在于如何求出方案数。下文我们钦定向南方向行走为在纵坐标上 $+1$，向东方向行走为在横坐标上 $+1$。

假定我们现在已经执行了 $T$ 次操作一，我们现在即在点 $(T, 0)$ 处，显然这样的合法操作数有且仅有 $1$ 种。

若想到达点 $(T, 1)$ 又怎么办呢？我们只需要在 $T$ 次操作一中选择一个变为操作三即可，不难发现这样的方案数即为 $C_{T}^{1}$ 种。如此类推，到达点 $(T, i)$ 的方案数即为 $C_{T}^{i}$ 种。

现在考虑横坐标不为 $T$ 的点：若想到达 $(T-1, i)$，我们能且只能执行 $T-1$ 次操作一或操作三，也就是我们必定执行一次操作二。

那么我们需要的操作三次数也非常显然了：即为 $i-1$。归纳可得到达 $(T - x, i)$ 的方案数即为 $\frac{T!}{x! \times (i - x)! \times (T-i)!}$，条件为 $T-x+i \ge T$。

其中 $200! \approx 10^{375}$，远小于 `long double` 的储存上界 $10^{4932}$，储存没有问题。

综上，我们在 $O(T^2)$ 的时间复杂度内解决了这个问题，唯一的问题就是 $T$ 开的再大点的话 `long double` 塞不下还有可能的精度问题（笑）。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long double fac[3010], ans_e;
long double qpow(long double low, int a){
    long double rtv = 1;
    while(a){
        if(a & 1){
            rtv *= low;
        }
        low *= low;
        a >>= 1;
    }
    return rtv;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	cin >> T;
	fac[1] = 1; fac[0] = 1;
	for(int i = 2; i <= T; i++){
		fac[i] = fac[i - 1] * i;
	}
    for(int i = 0; i <= T; i++){
        for(int j = 0; j <= T; j++){
            if(i + j < T){
                continue;
            }
            int tmp = T - i;
            ans_e += ((fac[T] / fac[tmp]) / fac[j - tmp]) / fac[T - j] * sqrt(qpow(i, 2) + qpow(j, 2));
        }
    }
	cout.precision(8);
	cout << fixed << ans_e / qpow(3, T) << '\n';
}
``````
依照如此做法，理论 $T$ 最大可以开到 $1754$，是不是可以申请个加强版？不过 $T$ 开到这么大我不敢保证精度没有问题。

---

## 作者：lcfollower (赞：2)

我讨厌 dp！

所以这是和官解不一样的做法。

以下为了和代码保持一致，默认题目中的 $T$ 为 $n$。

发现到 $1\le n\le 200$，于是思考 $\mathcal O(n^3)$ 做法。

枚举三个选项（选项 $1$，$2$，$3$）的出现次数，**分别**记作 $i$，$j$，$k$。

当 $i + j + k = n$ 时，正好经过 $n$ 秒，可以计算答案。

通过计算，得往东走的距离 $east = i + k$，往南走的距离 $north = j + k$，于是根据勾股定理，得此时到原点的距离为 $\sqrt {east^2 + north^2}$。

但是还不能过样例。

我们发现，这些情况是可以**交换顺序**的！

比如先 $1$ 后 $2$ 和先 $2$ 后 $1$，都是 $i=j=1$，$k=0$，但是方案却不一样。

我们又要去除如 $1$，$1$ 交换之后仍然不变的方案。

于是用到我们的组合数知识，先放 $1$，答案为 $C_{n}^i$；然后放 $2$，答案为 $C_{n-i}^j$；最后 $3$ 不得不放下。

根据乘法原理，得到方案数为 $C_{n}^i \times C_{n - i}^j$。

最后每种情况的出现概率为 $\frac{1}{3^n}$，乘一下就可以得到期望值。

然后就做完了，时间复杂度为 $\mathcal O(n^3)$。

但是要开 `long double`！不然见祖宗（计算阶乘用）！

然而我们觉得这个复杂度并不优秀，于是考虑枚举 $i$，$j$，如果 $i+j<n$ 则可以计算 $k = n - i - j$，这样优化了一重，时间复杂度为 $\mathcal O(n^2)$！

但是如果真的开成 $1\le n\le 5000$ 我怕 `long double` 也存不下，还有我懒得打，就留给读者自己完成吧，~~反正也没改多少~~。

---

下面是 $\mathcal O(n^3)$ 做法代码：

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 1e14
 
using namespace std;
 
inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}
# define double long double
constexpr int N = 2e5 + 10;
int n;
double ans ,fact[N];
inline double C(int x ,int y){//计算组合数。
  if (!y || x < y) return 1;
  return (fact[x] / fact[y] / fact[x - y]);
} signed main (){
  n = read ();
  fact[0] = 1;
  up (i ,1 ,n) fact[i] = fact[i - 1] * i;
  up (i ,0 ,n) {
    up (j ,0 ,n) {
      up (k ,0 ,n) {
        if (i + j + k == n) {
          double east = i + k ,north = j + k;
          double dis = sqrt (east * east + north * north);
          ans = ans + dis * C(n ,i) * C(n - i ,j);
        }
      }
    }
  }
  up (i ,1 ,n) ans /= 3.0;
  printf ("%Lf\n" ,ans);
  return 0 ;
}
```

---

## 作者：lnquoein (赞：1)

## 分析[题面](https://www.luogu.com.cn/problem/P12717)

首先注意到题面中这样一段话
> 接下来的 T 秒，每一秒 Cirno 会从以下 3 个选项中等概率随机选择一项：  
向东移动 1 米。  
向南移动 1 米。  
先向东移动 1 米，然后向南移动 1 米。

可以看出如果按照题意正向推导会导致计算量巨大，因此不妨从终点开始反向推导。根据~~标签~~此点很容易想到使用动态规划。  

那么我们看一看动态规划的做法。

## 动态规划分析

首先我们要明确**期望值**的意思。注意分析样例可以发现：  

期望=每次可能结果的概率×其结果的总和

因为题目中的 _向东_ 或 _向南_ 可以首先想到二维 dp，即 $f_{x,y}$ 代表向南 $ x $ 步，向东 $ y $ 步到达地点的期望值。那么接下来尝试推导转移方程。

此时会发现，缺少一个记录时间的维度，无法判断循环停止，于是我们添加一个时间维度 $ z $。

现在我们可以推导出转移方程了：

$ f_{x,y,z} = \frac{1}{3}(f_{x-1,y,z-1}+f_{x,y-1,z-1}+f_{x-1,y-1,z-1})$

可以发现这是一个 $O(n^3) $ 的时间复杂度。回头看一眼数据范围，发现 $T\le200$，可以通过。  

那么就可以写代码了，注意答案精度要求。

## 参考程序


```cpp
#include<bits/stdc++.h>
using namespace std;

double f[210][210][210];

int main(){
	int t;
    scanf("%d",&t);

    //DP部分
    f[0][1][1]=1;
    for(int i=1;i<=t;i++){
    	for(int j=1;j<=t+1;j++){
    		for(int k=1;k<=t+1;k++){
    			f[i][j][k]=1.0/3*(f[i-1][j-1][k]+f[i-1][j][k-1]+f[i-1][j-1][k-1]);
			}
		}
	}

    //统计答案
	double ans=0;
	for(int i=1;i<=t+1;i++){
		for(int j=1;j<=t+1;j++){
			ans+=f[t][i][j]*sqrt((i-1)*(i-1)+(j-1)*(j-1));
		}
	}
	printf("%.7lf",ans);//注意精度
    return 0;
}
```

---

## 作者：ingo_dtw (赞：1)

# P12717 [Algo Beat Contest 002 D] Distance of Trip
[题目传送门](https://www.luogu.com.cn/problem/P12717)
### 解题思路：

- 使用 $dp_{t,i,j}$ 表示经过 $t$ 秒后位于坐标 $(i,j)$ 的概率。这里 $i$ 是向东的总位移，$j$ 是向南的总位移。

- 每一秒，有三种选择：
  - 向东移动 $1$ 米：从 $dp_{i-1,j}$ 转移而来。
  - 向南移动 $1$米：从 $dp_{i,j-1}$ 转移而来。
  - 同时向东和向南移动 $1$ 米：从 $dp_{i-1,j-1}$ 转移而来。
    每种转移的概率均为 $\frac{1}{3}$。
  - 由于 $dp_t$ 只依赖于 $dp_{t-1}$，我们使用滚动数组来节省空间，交替更新当前层和下一层。

- 遍历所有可能的 $(i,j)$ 坐标，计算 $dp_{T,i,j} \times \sqrt{(i^2 + j^2)}$ 的总和，即为期望位移。

### Ac Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _ read<int>()
template <class T>inline T read()
{
	T r=0,f=1;char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-') f=-1;c=getchar();
	}
	while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f*r;
}
inline void out(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x<10) putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=210;
double d[2][N][N];
signed main() 
{
    int t=_;
    memset(d,0,sizeof(d));
    d[0][0][0]=1;
    int c=0;
    for(int p=1;p<=t;p++) 
	{
        int n=c^1;
        for(int i=0;i<=t;i++) 
		{
            for(int j=0;j<=t;j++) 
			{
                d[n][i][j]=0;
            }
        }
        for(int i=0;i<=p;i++)
		{
            for(int j=0;j<=p;j++) 
			{
                if(i>=1) d[n][i][j]+=d[c][i-1][j]*(1.0/3.0);
                if(j>=1) d[n][i][j]+=d[c][i][j-1]*(1.0/3.0);
                if(i>=1&&j>=1) d[n][i][j]+=d[c][i-1][j-1]*(1.0/3.0);
            }
        }
        c=n;
    }
    double r=0;
    for(int i=0;i<=t;i++) 
	{
        for(int j=0;j<=t;j++) 
		{
            if(d[c][i][j]>0) 
			{
                r+=d[c][i][j]*sqrt(1.0*i*i+1.0*j*j);
            }
        }
    }
    printf("%.8lf",r);
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

upd：更新状态转移方程。

这道题 $T\le200$，说明暴力枚举的 $O(3^T)$ 算法肯定是过不去的，而且即使能过，肯定会丢精度。

考虑 $O(T^3)$ 算法。由于操作是等概率随机，下面设 $X=\frac{1}{3}$。

可以发现如果第 $t$ 秒在某一个位置（原点东边 $i$ 米，南边 $j$ 米），那么上一秒一定在西边 $1$ 米、北边 $1$ 米、正西北方向 $\sqrt{2}$ 米之一。

因此列出状态转移方程：

$$ dp_{i,j,t}=dp_{i,j-1,t-1}\cdot X+dp_{i-1,j,t-1}\cdot X+dp_{i-1,j-1,t-1}\cdot X $$

边界条件为 $dp_{0,0,0}=1,\ dp_{-1,a,b}=dp_{a,-1,b}=dp_{-1,-1,b}=0$，其中 $a,b$ 是任意非负整数。

每秒每个方向最多移动 $1$ 米，因此在第 $t$ 秒两个方向不可能超过 $t$ 米，在两个方向递推到 $t$ 即可。

这样就可以 $O(T^3)$ 做了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long double
ll dp[205][205][2],ans;
const ll X=1.0l/3;
ll c(ll x,ll y){
    return sqrtl(x*x+y*y);
}
int main(){
    int n;
    cin>>n;
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            for(int k=0;k<=i;k++){
                dp[j][k][i&1]=0;
                if(j)dp[j][k][i&1]+=dp[j-1][k][(i&1)^1]*X;
                if(k)dp[j][k][i&1]+=dp[j][k-1][(i&1)^1]*X;
                if(j&&k)dp[j][k][i&1]+=dp[j-1][k-1][(i&1)^1]*X;
            }
        }
    }
    for(int j=0;j<=n;j++){
        for(int k=0;k<=n;k++){
            ans+=c(j,k)*dp[j][k][n&1];
        }
    }
    cout<<fixed<<setprecision(15)<<ans;
}
```

---

## 作者：tuntunQwQ (赞：1)

可以发现最多有 $3^{200}$ 种可能的路径，但最多能走到的位置数只有 $200\times 200$ 个，对于每一时刻，一定是从上一时刻的三个位置的其中一个走到了当前所在位置。考虑 $f_{i,x,y}$ 表示走了 $i$ 个时刻，向东的位移为 $x$，向南的位移为 $y$ 的概率，可以得出转移方程 $f_{i,x,y}=\frac{1}{3}f_{i-1,x-1,y}+\frac{1}{3}f_{i-1,x,y-1}+\frac{1}{3}f_{i-1,x,y-1}$。最后的答案就是每一个 $f_{T,x,y}$ 乘上该位置到起点的距离之和。

为了避免数组越界，代码中的 $x,y$ 编号均从 $1$ 开始。

代码如下，可供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
int t;double f[N][N][N],ans;
int main(){
    cin>>t;
    f[0][1][1]=1;
    for(int i=1;i<=t;i++){
    	for(int x=1;x<=t+1;x++){
    		for(int y=1;y<=t+1;y++){
    			f[i][x][y]=1.0/3*(f[i-1][x-1][y]+f[i-1][x][y-1]+f[i-1][x-1][y-1]);
			}
		}
	}
	for(int x=1;x<=t+1;x++){
		for(int y=1;y<=t+1;y++){
			ans+=f[t][x][y]*sqrt((x-1)*(x-1)+(y-1)*(y-1));
		}
	}
	cout<<fixed<<setprecision(10)<<ans<<'\n';
    return 0;
}
```

---

## 作者：Wzmois (赞：1)

## Solution
哇！$T\le200$ 说明什么？说明 $O(n^3)$ 也能过！

那就来个简单的 DP 吧！
### 如何 DP
题目中有三种状态：$T,x,y$。

如果 Cirno 一直选择第三种方法，那她位移最大可去到 $(T,T)$，所以 $x,y$ 从 $0$ 到 $T$ 递推即可。

上一秒他可以在 $(x-1,y)\;,(x,y-1)\;,(x-1,y-1)$ 的随机一个位置，我们只需加上上一个位置的状态值即可。
### 状态转移方程

我们规定 $f$ 是状态转移数组，$t$ 代表当前时间，$x$ 代表当前横坐标，$y$ 为当前纵坐标。

对于第一种移动方式，有
$$
f_{t,x,y}=f_{t-1,x,y-1}+f_{t,x,y}
$$
对于第二种移动方式，有
$$
f_{t,x,y}=f_{t-1,x-1,y}+f_{t,x,y}
$$
对于第三种移动方式，有
$$
f_{t,x,y}=f_{t-1,x-1,y-1}+f_{t,x,y}
$$
总方程：
$$
f_{t,x,y}=f_{t-1,x-1,y-1}+f_{t-1,x-1,y}+f_{t-1,x,y-1}
$$
**从 $0$ 开始还要特判一下。**

最后再将所有第 $T$ 秒的状态值累加起来即为答案。

于是就有了下面代码。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fp(mois,t) for(int mois=t;mois<=n;mois++)
double ans,f[202][202][202];
int n;
int main(){
    cin>>n;
    f[0][0][0]=1;
    fp(i,1)fp(j,0)fp(k,0){
        bool a1=j>0,a2=k>0;
        if (a1&&a2) f[i][j][k]=(f[i-1][j-1][k]+f[i-1][j][k-1]+f[i-1][j-1][k-1])/3.0;
        else if(a1) f[i][j][k]=(f[i-1][j-1][k])/3.0;
        else if(a2) f[i][j][k]=(f[i-1][j][k-1])/3.0;
    }
    fp(i,0)fp(j,0) ans+=f[n][i][j]*sqrt(pow(i,2)+pow(j,2));
    cout<<fixed<<setprecision(9)<<ans;
}
``````

---

## 作者：huangzilang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12717)

**题目大意：**

给定一个时间 $T$，求出在这 $T$ 秒内位移大小的期望值。也就是移动的距离的平均值。

**思路：**

相信有懂一点数学的都知道一共有 $3^{T}$ 种吧！我一开始想的使用搜索，但是看到 $T \le 200$ 时，就发现我还是太天真了，这明显是跟决策问题差不多的题，那就可以用 dp 来做。

题目中都是东和南两种情况，那我们就可以定义一个 $f_{i,j}$，表示走到 $(i,j)$ 的可能，我们可以把所有路径的直线距离的平均值求出来后，这一题求解决了。

现在我们来看最关键的部分。

我们可以把所有能到的地方都遍历一遍，如果这个地方被遍历过，那就用到这个地方的距离除以 $3$，再把到这个地方可以到的位置都加上这个值。

**注意：**

一定要创建一个新的 dp 数组来加，不然它会一直重复加，这就超过了 $T$ 秒的限制。


**代码：**


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main() 
{
	cin>>n;
	vector<vector<double> >f(n+2,vector<double>(n+2,0.0));
	f[0][0]=1.0;
	for(int i=0;i<n;i++) 
	{
		vector<vector<double> >f1(n+2,vector<double>(n+2,0.0));
		for(int j=0;j<=n;j++)
		{
			for(int k=0;k<=n;k++) 
			{
				if(f[j][k]==0) continue;
				double p=f[j][k]/3.0;
				f1[j+1][k]+=p;
				f1[j][k+1]+=p;
				f1[j+1][k+1]+=p;
			}
		}
		f=f1;
	}
	double ans=0.0;
	for(int i=0;i<=n;i++) 
	{
		for(int j=0;j<=n;j++) 
		{
			if(f[i][j]>0) 
			{
				ans+=f[i][j]*sqrt(i*i+j*j);
			}
		}
	}
	printf("%.9lf",ans);
	return 0;
}
```

---

## 作者：枫原万叶 (赞：0)

# 题解 P12717

## 分析

这个问题大致意思是需要计算在规定时间里面里，主人公移动的位移大小的期望值。

既然是动态规划，我们就设 $dp_{x,y}$ 是表示 Cirno 在任何时间点位于 $(x,y)$ 的概率。

状态转移方程很简单，当时间为 0 时，那么 Cirno 位于 $(0,0)$ 这个位置，此时 $dp_{i,j} = 1.0$。

根据移动的方式进行转移：

向东移动：$(x+1,y)$ 的概率增加 $\frac{1}{3} \times $ 当前概率。

向南移动：$(x,y+1)$ 的概率增加 $\frac{1}{3} \times $ 当前概率。
向南移动：$(x+1,y+1)$ 的概率增加 $\frac{1}{3} \times $ 当前概率。

最后，需要计算位移大小，那么就遍历所有坐标，使用两点距离计算公式 $\sqrt{x^2+y^2}$ 并乘以对应的概率，累加得到的期望值就是我们要的答案。

## 代码

```cpp
#include <bits/stdc++.h>
#define Robin ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
const int MAXN=2e2+5;
double dp[201][201],ndp[201][201];

int main() {
	Robin;
	int T;
	cin>>T;
	dp[0][0]=1.0;
	for(int t=0;t<T;t++){
		memset(ndp,0,sizeof(ndp));
		for(int x=0;x<=200;x++)
			for(int y=0;y<=200;y++)
				if (dp[x][y]>0) {
					ndp[x+1][y]+=dp[x][y]/3.0;
					ndp[x][y+1]+=dp[x][y]/3.0;
					ndp[x+1][y+1]+=dp[x][y]/3.0;
				}
		memcpy(dp, ndp, sizeof(dp));
	}
	double ans=0.0;
	for (int x=0;x<=200;x++)
		for (int y=0;y<=200;y++)
			ans+=sqrt(x*x+y*y)*dp[x][y];
	cout<<fixed<<setprecision(8)<<ans<<endl;
	return 0;
}
```

---

## 作者：Chenxuhang_play (赞：0)

## 思路

暴力的时间复杂度为 $O(3^T)$，即使 $T\le 200$ 也过不了。所以考虑使用其他的方法。

注意到题目中给出了三种状态：$T,x,y$，所以考虑使用 DP。因为 $x$ 和 $y$ 最大只能到 $T$，即 $x\le T,y\le T$，所以只需要从 $0$ 遍历到 $T$ 即可。

令$f_{t,x,y}$ 表示概率，其中 $t$ 代表当前时间，$x$ 代表当前横坐标，$y$ 为当前纵坐标。则可以归纳状态转移方程：

$$
f_{t,x,y}=\frac{1}{3}\times(f_{t-1,x-1,y}+f_{t-1,x,y-1}+f_{i-1,x-1,,y-1})
$$

**实际操作中，为避免越界，故从 $1$ 开始遍历到 $T+1$。**

---

最后的答案就是每一个 $f_{T,x,y}$ 乘上该位置到起点的距离之和。坐标轴内的两点距离公式为：

$$
dis_{A,B}=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}
$$

这个公式是由勾股定理演变的。其中 $dis_{A,B}$ 表示点 $A$ 到点 $B$ 的距离，$A$ 的坐标为 $(x_1,y_1)$，$B$ 的坐标为 $(x_2,y_2)$。

另外要注意的一个点是，$f_{t,x,y}$ 的类型是 `double`，而不是 `int`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	double f[205][205][205],ans=0;
	f[0][1][1]=1;
    for(int i=1;i<=T;i++)
	{
    	for(int x=1;x<=T+1;x++)
		{
    		for(int y=1;y<=T+1;y++)
			{
    			f[i][x][y]=1.0/3*(f[i-1][x-1][y]+f[i-1][x][y-1]+f[i-1][x-1][y-1]);
			}
		}
	}
	for(int x=1;x<=T+1;x++)
	{
		for(int y=1;y<=T+1;y++)
		{
			ans+=f[T][x][y]*sqrt((x-1)*(x-1)+(y-1)*(y-1));//两点距离公式 
		}
	}
	cout<<fixed<<setprecision(8)<<ans; 
	return 0;
}
```

---

## 作者：signed_long_long (赞：0)

没学过概率 DP，但写出来了……

# 题目解法

令 $f_{i,j,k}$ 为在第 $k$ 秒走到格子 $(i,j)$ 的概率，因为每秒都有 $\frac{1}{3}$ 的概率向右、下、右下走，则有转移方程：

$$f_{i,j,k}=\frac{f_{i-1,j,k-1}+f_{i-1,j-1,k-1}+f_{i,j-1,k-1}}{3}$$

要求期望值，只需把距离乘以 $f_{i,j,T}$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
double f[205][205][205];
double dis(int x,int y){
	x=x-1;y=y-1;
	return sqrt(x*x+y*y);
}
int main(){
	cin>>T;
	f[1][1][0]=1;
	for(int i=1;i<=T+1;i++){
		for(int j=1;j<=T+1;j++){
			for(int k=0;k<=T;k++){
				if(i==1 and j==1 and k==0) continue;
					f[i][j][k]=f[i-1][j-1][k-1]/3.0+f[i-1][j][k-1]/3.0+f[i][j-1][k-1]/3.0;
			}
		}
	}
	double ans=0;
	for(int i=1;i<=T+1;i++){
		for(int j=1;j<=T+1;j++){
			ans+=f[i][j][T]*dis(i,j);
		}
	}
	printf("%.10f",ans);
	return 0;
}
```

---

