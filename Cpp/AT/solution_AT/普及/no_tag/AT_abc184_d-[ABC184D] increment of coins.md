# [ABC184D] increment of coins

## 题目描述

袋子里原本有金币 $ A $ 枚、银币 $ B $ 枚、铜币 $ C $ 枚。

直到袋子中有一种硬币达到 $100$ 枚之前，都会进行以下操作。

操作：每秒钟都有 $1$ 枚硬币被等概率地取出，然后向袋子中放入两枚相同的硬币。

求出操作次数的数学期望。

## 说明/提示

- $ 0\ \leq\ A,B,C\ \leq\ 99 $
- $ A+B+C\ \geq\ 1 $

### 【样例解释1】 

不论第一次操作取出哪种硬币，袋中都会出现 $ 100 $ 枚该种硬币。

### 【样例解释2】 

我们只会在第一次取出金币的情况下进行第二次操作，操作次数的数学期望为 $ 2\times\ \frac{98}{98+99+99}+1\times\ \frac{99}{98+99+99}+1\times\ \frac{99}{98+99+99}=1.331081081\ldots $。

### 【样例解释3】 

每次操作只会取出铜币

## 样例 #1

### 输入

```
99 99 99```

### 输出

```
1.000000000```

## 样例 #2

### 输入

```
98 99 99```

### 输出

```
1.331081081```

## 样例 #3

### 输入

```
0 0 1```

### 输出

```
99.000000000```

## 样例 #4

### 输入

```
31 41 59```

### 输出

```
91.835008202```

# 题解

## 作者：GreenMelon (赞：4)

利用动态规划可以切掉这道题。

最初 $f$ 的所有值都是 $0$。一眼看出，取出金币的概率为 $\cfrac{A}{A+B+C}$，银币，铜币同理，最后给取出金币的概率乘上 $f_{i+1,j,k}+1$，银币，铜币同理。最后得出动态转移方程。$f_{i+1,j,k}\times\cfrac{i}{i+j+k}+f_{i,j+1,k}\times\cfrac{j}{i+j+k}+f_{i,j,k+1}\times\cfrac{k}{i+j+k}$。

记得**倒推**，且 $f$ 是 **`double` 类型**。

---

## 作者：xuchuhan (赞：2)

## Preface

蒟蒻第一次自己弄出来期望 DP，写篇题解纪念。

## Solution

其实和我之前练习到的[这道题目](https://www.luogu.com.cn/problem/AT_dp_j)很像。

这道题目我们可以记忆化搜索求解。其实递推也可以但是边界可能比记搜难写一些，故这里选择记搜。

看到 $A,B,C\leq 99$，考虑设 $dp_{x,y,z}$ 表示当前金币、银币、铜币数量分别为 $x,y,z$ 时，操作轮数的期望。下面考虑怎么 DP。

- 终止状态：若当前状态中 $x,y,z$ 中的任意一个 $\geq 100$，则结束当前记搜。
- 转移方程：
  - 若当前状态 $x>0$，则 $dp_{x,y,z}\leftarrow dp_{x,y,z}+(dp_{x+1,y,z}+1)\times\dfrac{x}{x+y+z}$。表示当前选择 $x$，步数是状态 $dp_{x+1,y,z}$ 再加一步，选择概率是 $\dfrac{x}{x+y+z}$。
  - 若当前状态 $y>0$，则 $dp_{x,y,z}\leftarrow dp_{x,y,z}+(dp_{x,y+1,z}+1)\times\dfrac{y}{x+y+z}$。原理同理。
  - 若当前状态 $z>0$，则 $dp_{x,y,z}\leftarrow dp_{x,y,z}+(dp_{x,y,z+1}+1)\times\dfrac{z}{x+y+z}$。原理同理。
- 答案：$dp_{A,B,C}$。

这道题目就做完了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
int a,b,c;
double dp[N][N][N];
double DFS(int x,int y,int z){
	if(x>=100||y>=100||z>=100)return 0;//终止状态 
	if(dp[x][y][z]!=-1)return dp[x][y][z];//记搜的记录 
	double tmp=0;
	//以下是转移 
	if(x)tmp+=(DFS(x+1,y,z)+1.0)*1.0*double(x)/double(x+y+z);
	if(y)tmp+=(DFS(x,y+1,z)+1.0)*1.0*double(y)/double(x+y+z);
	if(z)tmp+=(DFS(x,y,z+1)+1.0)*1.0*double(z)/double(x+y+z);
	return dp[x][y][z]=tmp;
}
signed main(){
	cin>>a>>b>>c;
	for(int i=0;i<=100;i++)
		for(int j=0;j<=100;j++)
			for(int k=0;k<=100;k++)
				dp[i][j][k]=-1;//初始状态 
	printf("%.10lf",DFS(a,b,c));//答案 
	return 0;
}
```

祝大家 NOIp2024 rp++。

---

## 作者：Meickol (赞：1)

提供两种做法：概率 DP 和期望 DP。

看题解区大家都是期望 DP 的做法，故来补充一个概率 DP 的题解。





#### 法一：概率DP

设 $\large f_{i,j,k}$ 表示袋中金银铜币分别为 $i,j,k$ 时的概率。

显然，初始化有 $\large f_{a,b,c}=1$。

转移也比较显然，刷表即可。

最终答案即为下面三个式子的结果相加。
$$
\begin{cases}
\sum \limits _{i=a}^{99} \sum \limits _{j=b}^{99} f_{i,j,100} \times (i-a+j-b+100-c)
 \\
\sum \limits _{j=b}^{99} \sum \limits _{k=c}^{99} f_{100,j,k} \times (100-a+j-b+k-c)
 \\
\sum \limits _{i=a}^{99} \sum \limits _{k=c}^{99} f_{i,100,k} \times (i-a+100-b+k-c
\end{cases}
$$


```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
const int N=1e2+5;
int n;
double f[N][N][N];
void solve(){
	int a,b,c;
	cin>>a>>b>>c;
	f[a][b][c]=1;
	double ans=0;
	rep(i,a,99){
		rep(j,b,99){
			rep(k,c,99){
				f[i+1][j][k]+=f[i][j][k]*i/(i+j+k);
				f[i][j+1][k]+=f[i][j][k]*j/(i+j+k);
				f[i][j][k+1]+=f[i][j][k]*k/(i+j+k);
			}
		}
	}
	rep(i,0,100){
		rep(j,0,100){
			ans+=f[i][j][100]*(i-a+j-b+100-c);
			ans+=f[i][100][j]*(i-a+100-b+j-c);
			ans+=f[100][i][j]*(100-a+i-b+j-c);
		}
	}
	printf("%.9lf",ans);
}
```






#### 法二：期望DP
设 $\large f_{i,j,k}$ 表示袋中金银铜币分别为 $i,j,k$ 时操作次数的期望值。

显然，对于 $\large f_{100,j,k},f_{i,100,k},f_{i,j,100}$ 初始化均为 $0$。

然后转移时是倒推，且状态转移方程为：
$$
\large f_{i,j,k}=(f_{i+1,j,k}+1)\cdot \dfrac{i}{i+j+k}+(f_{i,j+1,k}+1)\cdot \dfrac{j}{i+j+k}+(f_{i,j,k+1}+1)\cdot \dfrac{i}{i+j+k}
$$
最终答案即为 $\large f_{a,b,c}$。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
const int N=1e2+5;
int n;
double f[N][N][N];
void solve(){
	int a,b,c;
	cin>>a>>b>>c;
	per(i,99,a){
		per(j,99,b){
			per(k,99,c){
				f[i][j][k]=(f[i+1][j][k]+1)*(double)i/(i+j+k)+(f[i][j+1][k]+1)*(double)j/(i+j+k)+(f[i][j][k+1]+1)*(double)k/(i+j+k);
			}
		}
	}
	printf("%.9lf",f[a][b][c]);
}
```



另外因为这题是求操作数的期望，而每次取出不管是取出哪种币都需要花费一次操作，因而 加 $1$ 也可以直接提到外面，即使用下方的写法也是可以的。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
const int N=1e2+5;
int n;
double f[N][N][N];
void solve(){
	int a,b,c;
	cin>>a>>b>>c;
	per(i,99,a){
		per(j,99,b){
			per(k,99,c){
				f[i][j][k]=f[i+1][j][k]*i/(i+j+k)+f[i][j+1][k]*j/(i+j+k)+f[i][j][k+1]*k/(i+j+k)+1;
			}
		}
	}
	printf("%.9lf",f[a][b][c]);
}
```

---

## 作者：_hxh (赞：1)

### 题意

袋子里有 $A$ 枚金币，$B$ 枚银币，$C$ 枚铜币，每次操作随机增加一枚硬币，直到袋子中有一种硬币达到 $100$ 枚。求操作次数的数学期望。

### 分析

动态规划题。如果刚开始时就有一种硬币的数量达到 $100$ 枚了，那我们就不需要继续操作了，即操作次数为 $0$ 次。所以初始状态为 $dp_{i,j,100} = dp_{i,100,k} = dp_{100,j,k} = 0$。若金币有 $i$ 枚，银币有 $j$ 枚，铜币有 $k$ 枚，则增加一枚金币的概率就是 $\dfrac{i}{i + j + k}$，而这个概率就是 $dp_{i,j,k}$ 到 $dp_{i + 1,j,k}$ 的概率。由于要做到无后效性，所以我们要倒着遍历。对于银币和铜币来讲同理。

所以我们可以得到转移方程：

$$
dp_{i,j,k} \gets \dfrac{i}{i + j + k} \cdot (dp_{i + 1,j,k} \textcolor{red}{+ 1}) + \dfrac{j}{i + j + k} \cdot (dp_{i,j + 1,k} \textcolor{red}{+ 1}) + \dfrac{k}{i + j + k} \cdot (dp_{i,j,k + 1} \textcolor{red}{+ 1})
$$

注：$\textcolor{red}{+ 1}$ 是因为从 $dp_{i + 1,j,k}$ 到 $dp_{i,j,k}$ 要进行一次操作。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5;
double dp[N][N][N];
int a,b,c;
int main()
{
	cin >> a >> b >> c;
	for (int i = 99;i >= a;i--)
		for (int j = 99;j >= b;j--)
			for (int k = 99;k >= c;k--)
				dp[i][j][k] += (i * 1.0 / (i + j + k) * (dp[i + 1][j][k] + 1)) + (j * 1.0 / (i + j + k) * (dp[i][j + 1][k] + 1)) + (k * 1.0 / (i + j + k) * (dp[i][j][k + 1] + 1));
	printf("%.9f\n",dp[a][b][c]);
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：1)

## 考点

记忆化搜索。

## 题面
[[ABC184D] increment of coins](https://www.luogu.com.cn/problem/AT_abc184_d)
## 分析
发现 $A$，$B$，$C$ 都不大，所以可以直接记忆化搜索，存储当前的 $A$，$B$，$C$ 的时候所得到的答案。

然后每次向下计算分别增加一个 $\texttt{coin}$ 的期望就好了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int A,B,C;
double hys[110][110][110];
double dfs(int a,int b,int c)
{
	if(a>99||b>99||c>99)return 0;
	if(hys[a][b][c])return hys[a][b][c];
	double a1=(double){(dfs(a+1,b,c)*a)}/(double){a+b+c};
	double b1=(double){(dfs(a,b+1,c)*b)}/(double){a+b+c};
	double c1=(double){(dfs(a,b,c+1)*c)}/(double){a+b+c};
	return hys[a][b][c]=1+a1+b1+c1;
}
int main()
{
	scanf("%d%d%d",&A,&B,&C);
	printf("%.6lf",dfs(A,B,C));
	return 0;
}

```


---

## 作者：_QyGyQ_ (赞：0)

我们可以发现，数据范围比较小。所以可以用枚举来解决这道题。但直接枚举肯定超时，所以我们使用记忆化搜索。推式子可以发现，三种硬币每一种硬币往下推一个的期望，再乘以该种硬币个数除以硬币总数，再把所得值相加，再加一，就是我们要求的答案。
```cpp
#include<bits/stdc++.h>
#define int long long
#define lc(p) (p<<1)
#define rc(p) (p<<1|1)
#define debug puts("-----------")
#define endl puts("")
#define re register
#define in inline
#define cnt (suma+sumb+sumc)
using namespace std;
const int N=1e6+7;

char *p1,*p2,buf[N];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
in int read(){
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57){
        if(ch=='-') f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57) x=x*10+ch-48,ch=nc();
   	return x*f;
}

double vis[208][208][208];
in double dfs(int suma,int sumb,int sumc){
	if(suma>=100||sumb>=100||sumc>=100){
		return 0.0;
	}
	if(vis[suma][sumb][sumc]){
		return vis[suma][sumb][sumc];
	}
	vis[suma][sumb][sumc]=1+dfs(suma+1,sumb,sumc)*suma/cnt+dfs(suma,sumb+1,sumc)*sumb/cnt+dfs(suma,sumb,sumc+1)*sumc/cnt;
	return vis[suma][sumb][sumc];
}
signed main(){
	int a=read(),b=read(),c=read();
	printf("%.9lf",dfs(a,b,c));
	return 0;
}

```

---

## 作者：_Gabriel_ (赞：0)

### 思路

此题可以用 `dp` 或者 `dfs` 加记忆化搜索解决。

求得是期望值，可以用几种情况的值乘以其概率，再加起来就好了。

根据题目，可得状态转移方程为 $dp_{i,j,k}=\dfrac{i}{i+j+k}(dp_{i+1,j,k}+1)+\dfrac{j}{i+j+k}(dp_{i,j+1,k}+1)\dfrac{k}{i+j+k}(dp_{i,j,k+1}+1)$。

答案即为 $dp_{a,b,c}$。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
const int N = 1e2 + 10;
double dp[N][N][N];

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    for (int i = 99; i >= a; i--) {
        for (int j = 99; j >= b; j--) {
            for (int k = 99; k >= c; k--) {
                dp[i][j][k] += (double)i / (i + j + k) * (dp[i + 1][j][k] + 1);
                dp[i][j][k] += (double)j / (i + j + k) * (dp[i][j + 1][k] + 1);
                dp[i][j][k] += (double)k / (i + j + k) * (dp[i][j][k + 1] + 1);
            }
        }
    }
    printf("%.10f\n", dp[a][b][c]);
    return 0;
}
```

---

## 作者：迟暮天复明 (赞：0)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/15388528.html)

题意：有一堆硬币，其中金币，银币，铜币的个数分别为 $A,B,C$，每次在这堆硬币中随机挑选一枚，放两个同样的硬币进去。求存在一种硬币使得这种硬币个数超过 $100$ 的期望操作次数。

概率 DP。

这道题目应当用倒推的方法，因为初始状态是 $f_{100,j,k}=f_{i,100,k}=f_{i,j,100}=0$。
然后对于每种状态，我不妨设他的金银铜三种的个数为 $x,y,z$，那么我选择金币的概率就是 $\frac{x}{x+y+z}$，同理，选择银币，铜币的概率分别是 $\frac{y}{x+y+z}$ 和 $\frac{z}{x+y+z}$。

注意到，我选择金币的概率就是我从 $f_{x+1,y,z}$ 推到 $f_{x,y,z}$ 的概率（这个过程要进行一次操作），银币，铜币同理。那么我们就可以由此来写出方程了。

$$
f_{x,y,z}=(f_{x+1,y,z}+1)\times \frac{x}{x+y+z}+(f_{x,y+1,z}+1)\times \frac{y}{x+y+z}+(f_{x,y,z+1}+1)\times \frac{z}{x+y+z}
$$

因为我是求 $f_{A,B,C}$，所以我使用了DFS（不用也能做出来），导致需要使用记忆化搜索。

[代码](https://paste.ubuntu.com/p/wqkcmmFm66/)

---

## 作者：lowbit (赞：0)

### 题目大意
有 $A$ 个金币，$B$ 个银币，$C$ 个铜币，每次等概率地选一种硬币使其数量 $+1$，当有一种硬币数量 $\ge100$ 时停止。求操作次数的期望。

### 解题思路
期望 DP

期望值即随机变量的值乘以其概率的总和。

根据期望的定义，可得转移式：
$f(a,b,c)=1+f(a+1,b,c)\times p_a+f(a,b+1,c)\times p_b+f(a,b,c+1)\times p_c$
其中，$p_a$，$p_b$，$p_c$ 是选每种硬币的概率。

注意：求期望一般**从后往前推**，这样不会有后效性。

### 具体实现
由于采用倒推的方式，我们可以用**记忆化搜索**来写。

Code：
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define DEBUG puts("114514")
#define enter puts("")
#define db double

typedef long long ll;
const int N = 103;
const int mo = 1e9+7;
const ll INF = 2e9;
using namespace std;
inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') { x=x*10+ch-48; ch=getchar(); }
	return x*f;
}

int n, m, i, j, k, a, b, c;
db f[N][N][N]; // double类型

db dfs(int a, int b, int c) {
	if(a > 99 || b > 99 || c > 99) return 0; // 到达终点
	if(f[a][b][c]) return f[a][b][c]; // 记忆化
	double k = a+b+c; // 等概率选取
	return f[a][b][c] = 1 + dfs(a+1, b, c)*a / k + dfs(a, b+1, c)*b / k + dfs(a, b, c+1)*c / k;
}
int main() {
	cin >> a >> b >> c;
	f[99][99][99] = 1; // 任意操作一次都能到达终点，所以期望为1
	printf("%.9lf", dfs(a, b, c)); // 题目要求精确到1e-6，我们保留9位小数
	return 0;
}

```

---

