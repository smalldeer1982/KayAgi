# Pyramid of Glasses

## 题目描述

Mary has just graduated from one well-known University and is now attending celebration party. Students like to dream of a beautiful life, so they used champagne glasses to construct a small pyramid. The height of the pyramid is $ n $ . The top level consists of only $ 1 $ glass, that stands on $ 2 $ glasses on the second level (counting from the top), then $ 3 $ glasses on the third level and so on.The bottom level consists of $ n $ glasses.

Vlad has seen in the movies many times how the champagne beautifully flows from top levels to bottom ones, filling all the glasses simultaneously. So he took a bottle and started to pour it in the glass located at the top of the pyramid.

Each second, Vlad pours to the top glass the amount of champagne equal to the size of exactly one glass. If the glass is already full, but there is some champagne flowing in it, then it pours over the edge of the glass and is equally distributed over two glasses standing under. If the overflowed glass is at the bottom level, then the champagne pours on the table. For the purpose of this problem we consider that champagne is distributed among pyramid glasses immediately. Vlad is interested in the number of completely full glasses if he stops pouring champagne in $ t $ seconds.

Pictures below illustrate the pyramid consisting of three levels.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF676B/ed339075e4609507dba05c150b7d4a59f8205147.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF676B/26451ba18b38a1279a26b3d7ab7f9bf63116bb12.png)

## 说明/提示

In the first sample, the glasses full after $ 5 $ seconds are: the top glass, both glasses on the second level and the middle glass at the bottom level. Left and right glasses of the bottom level will be half-empty.

## 样例 #1

### 输入

```
3 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 8
```

### 输出

```
6
```

# 题解

## 作者：封禁用户 (赞：2)

## CF676B Pyramid of Glasses 题解
### 解题思路（最暴力的方法）
我们观察到数据范围非常的小，所以我们完全可以用 $O(n^2k)$ 的时间复杂度，**模拟**每次倒入 $1$ 的水，最后统计答案。
### 优化：
我们其实可以一次把 $k$ 的水全部倒入第一个杯子里，再将“浮空”的水**分发**下去，接着分发第二行“浮空”的水，以此类推，最后统计答案，时间复杂度 $O(n^2)$。
### 参考代码 $1$
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n , k , ans;
long double a[15][15];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> k;
	a[1][1] = k;
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= i ; j++)
		{
			if(a[i][j] > 1.0)
			{
				a[i + 1][j] += a[i][j] / 2.0 - 0.5;
				a[i + 1][j + 1] += a[i][j] / 2.0 - 0.5;
			}
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= i ; j++)
		{
			if(a[i][j] >= 0.999999999999)
			{
				ans++;
			}
		}
	}
	cout << ans;
	return 0;
}
```
### 进一步的优化
其实我们在写出 $O(n^2k)$ 的代码后，还有另一条通往 $O(n^2)$ 的路，就是我们可以用这段代码算出每一个杯子填满的时间，再查找所有 $\text{需要时间}\ \le\ k$ 的杯子就可以了。~~（简称：打表）~~
### 参考代码 $2$
```cpp
#include<bits/stdc++.h> 
using namespace std;
int biao[15][15] = {{0} , {0 , 1} , {0 , 3 , 3} , {0 , 7 , 5 , 7} , {0 , 15 , 9 , 9 , 15} , {0 , 31 , 14 , 11 , 14 , 31} , {0 , 63 , 22 , 16 , 16 , 22 , 63} , {0 , 127 , 37 , 22 , 19 , 22 , 37 , 127} , {0 , 255 , 63 , 31 , 24 , 24 , 31 , 63 , 255} , {0 , 511 , 105 , 46 , 32 , 28 , 32 , 46 , 105 , 511} , {0 , 1023 , 182 , 69 , 41 , 34 , 34 , 41 , 69 , 182 , 1023}} , n , k , ans;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= i ; j++)
			if(biao[i][j] <= k)
				ans++;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：fcy20180201 (赞：1)

## 思路
发现 $n,t$ 很小，可以直接模拟。

使用递归求解，如果递归到某个杯子时还未装满就直接返回，否则就将多的分两份给下面的杯子。但我们并不需要算完一层的所有杯子后再往下递归，因为到达下一层杯子的酒的总量是不变的，不管按什么顺序。计算每个杯子的酒量时完全可以用小数，~~但我脑抽用了分数~~。

### 用分数的细节
- 如果发现这是最后一层，就不要再算向下漏的酒了，因为会发生除 $0$ 错误。

- 一定要约分，不然数字会溢出。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[15][15],b[15][15],ans;

int gcd(int x,int y){//求最大公倍数，方便约分。
	while(x && y)(x>=y?x%=y:y%=x);
	return x+y;
}

void dfs(int i,int j){
	if(a[i][j]<=b[i][j])return ;//如果这杯还没满，就不可能往下溢，直接返回。
	int x=a[i][j]-b[i][j],y=b[i][j]*2;//算溢出的，除以 2。
	a[i][j]=b[i][j]=1;//这杯回到恰好满的状态。
	if(i==n)return ;
	int g=gcd(x,y);x/=g,y/=g;//约分。
	a[i+1][j]=a[i+1][j]*y+x*b[i+1][j],b[i+1][j]*=y;//给下面左边的一杯加上溢出的酒。
	g=gcd(a[i+1][j],b[i+1][j]),a[i+1][j]/=g,b[i+1][j]/=g;//约分
	dfs(i+1,j);//向下递归
	//处理右下的杯子同理。
	a[i+1][j+1]=a[i+1][j+1]*y+x*b[i+1][j+1],b[i+1][j+1]*=y;
	g=gcd(a[i+1][j+1],b[i+1][j+1]),a[i+1][j+1]/=g,b[i+1][j+1]/=g;
	dfs(i+1,j+1);
	return ;
}

int main(){
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)b[i][j]=1;
	//初始化别忘。
	while(t--){
		a[1][1]++;//给第一杯倒。
		dfs(1,1);
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)if(a[i][j]==b[i][j])ans++;//计算答案。
	printf("%d",ans);
	return 0;
}

```

---

## 作者：lovely_hyzhuo (赞：0)

提供一种最暴力的解法。

把这些杯子抽象成一个类似杨辉三角的矩阵。

然后枚举时间，每一秒给 $a_{1,1}$ 加一，然后暴力地往下流。

```cpp
#include<bits/stdc++.h>
using namespace std;
double a[1010][1010];
int main()
{
	int n,t;
	cin>>n>>t;
	int m=(n*n+n)/2;
	for(int i=1;i<=t;i++)
	{
		a[1][1]+=1;
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=j;k++)
			{
				if(a[j][k]>1)
				{
					double t=(a[j][k]-1)/2;
					a[j+1][k]+=t,a[j+1][k+1]+=t;
					a[j][k]=1;
				}
			}
		}
	}
	int ans=0;
	for(int j=1;j<=n;j++)
	{
		for(int k=1;k<=j;k++)
		{
			if(a[j][k]==1)
				ans++;
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：wangzelin (赞：0)

# 题目
[题目链接](https://www.luogu.com.cn/problem/CF676B)

# 题目分析
首先我们发现这一题数据范围比较小，为 $ n\le10 $，$ t\le10^4 $。

所以我们可以考虑直接模拟。

令 $ a_{i,j} $ 表示第 $i$ 行第 $j$ 列的酒量。

先使得 $ a_{1,1} \gets t $，

由此可以得到递推式为：

$ a_{i+1,j} \gets a_{i+1,j} + (a_{i,j}-1)/2 $

$ a_{i+1,j+1} \gets a_{i+1,j+1} + (a_{i,j}-1)/2 $

最后统计 $ a_{i,j} \ge 1 $ 的数量，即为答案。

# 代码

接下来上代码，注意数组开成浮点数。


```cpp
#include <bits/stdc++.h>
using namespace std;

int n,t,tot=0;
double a[11][11];

int main()
{
	cin>>n>>t;
	a[1][1] = t;
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=i;j++)
		{ 
			if(a[i][j]>=1)
			{
				a[i+1][j]+=(a[i][j]-1)/2;
				a[i+1][j+1]+=(a[i][j]-1)/2;
				a[i][j]=1;
			}
		}
	} //递推公式
	for(int i=1;i<=n;i++) for(int j=1;j<=i;j++) if(a[i][j]>=1) tot++;
	//统计答案数量
	cout<<tot;
	return 0;
}
```


---

## 作者：Nuclear_Fish_cyq (赞：0)

题目只需要我们求出最后的状态，那么为了方便进行递推，我们可以“让酒浮空”，具体就是我们可以把刚流到杯子里的酒先存起来，等到遍历到这个杯子的时候再让酒流到下面的杯子。这样，我们就可以不用一杯一杯的倒酒，而是一次性倒 $t$ 杯酒到第一个杯子。接下来就是递推方程了。

我们设 $f_{i,j}$ 是第 $i$ 行的第 $j$ 个杯子里面的水量，那么我们就可以得出递推式：

$$f_{i+1,j}=f_{i+1,j}+\frac{f_{i, j}-1}{2}$$

$$f_{i+1,j + 1}=f_{i+1,j + 1}+\frac{f_{i, j}-1}{2}$$

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
//#define mod
//#define range
using namespace std;
int n, t, ans;
double f[10][10];

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> t;
	f[0][0] = t;//在第一个杯子倒入t杯酒
	for(int i = 0; i < n - 1; i++){//由于最后一层的杯子再倒酒也没有用了所以不遍历
		for(int j = 0; j <= i; j++){ 
			if(f[i][j] >= 1.0){//有处于浮空状态的酒 
				f[i + 1][j] += (f[i][j] - 1.0) / 2.0;//给左边的杯子的酒 
				f[i + 1][j + 1] += (f[i][j] - 1.0) / 2.0;//给右边的杯子的酒 
				f[i][j] = 1.0;//清空浮空的酒 
			}
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++){ 
			if(f[i][j] >= 1.0){//酒满了，注意由于最后一层可能还有浮空的酒所以是大于等于 
				ans++;//记录答案 
			}
		}
	} 
	cout << ans << endl;
	return 0;
}

```


---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF676B)
## 题意：
有一个 $n$ 层高的酒杯金字塔（就像一个三角形，第 $n-1$ 层比第 $n$ 层少一个），一个人从最上面的酒杯开始匀速倒酒，每秒倒正好一杯的酒，如果这个杯子满了同时又有酒从上面倒下来的话，这个杯子会往它两侧了杯子按原来 $\frac{1}{2}$ 的速度向下倒酒，如果下面没有杯子了酒就会倒在桌上。

输入仅一行：$n$（酒杯金字塔的高度）和 $t$（秒数）。

输出也是一行：$ans$（已满的酒杯数量，漏桌上的不算）。
## 思路：
我们假设速度为 $1$ 个杯子每秒，可以先把 $t$ 个的酒量都倒入第一个杯子中（假设第一个杯子是无限大的）。

所一我们按顺序看看每一个酒杯里有没有需要倒入下一个酒杯的即可，有则答案加 $1$。

当 $ dp[i][j] \ge 1$ 时递推公式是:

$dp[i+1][j]=dp[i+1][j]+(dp[i][j]-1)/2.0$，

$dp[i+1][j+1]=dp[i+1][j]+(dp[i][j]-1)/2.0$。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n=0,t=0,ans=0;
double dp[21][21];
int main(){
	scanf("%lld%lld",&n,&t);
	dp[1][1]=t;//第1层第1个为t个杯子的总量
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(dp[i][j]>=1){//如果有需要倒入下一个酒杯的杯子
				ans++;
				dp[i+1][j]+=(dp[i][j]-1)/2.0;//左边的杯子
				dp[i+1][j+1]+=(dp[i][j]-1)/2.0;//右边的杯子
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

提供一种目前发现的复杂度最劣的做法。

考虑直接暴力模拟酒下落的过程，每次直接对下一个酒杯向下递归并下传当前下落的酒量的一半即可，这里用手写分数实现，注意溢出问题即可，并且记得每一步都需要约分。

时间复杂度 $ \mathcal{O}(2^n \times t) $，因为数据较小可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
int a[2000020],b[2000020];
int n,t;
int cnt=0;
void dfs(int step,int now,int plus1,int plus2)
{
	if(step==n+1)
		return;
	if(plus1==0)
		return;
	int gcder=__gcd(plus1,plus2);
	plus1/=gcder;
	plus2/=gcder;
	cnt++;
	int tmp1=a[now];
	int tmp2=b[now];
	a[now]=tmp1*plus2+tmp2*plus1;
	b[now]=tmp2*plus2;
   gcder=__gcd(a[now],b[now]);
	a[now]/=gcder;
	b[now]/=gcder;
	if(a[now]>b[now])
	{
		plus1=a[now]-b[now],plus2=b[now];
		a[now]=b[now]=1;
	}
	else
	plus1=0,plus2=0;
	dfs(step+1,step*(step+1)/2+(now-step*(step-1)/2),plus1,plus2*2);
	dfs(step+1,step*(step+1)/2+(now-step*(step-1)/2)+1,plus1,plus2*2);
}
signed main()
{
    cin>>n>>t;
    for(int i=1;i<=n*(n+1)/2;i++)
    	a[i]=0,b[i]=1;
    for(int i=1;i<=t;i++)
    {
    	for(int i=1;i<=n*(n+1)/2;i++)
    	{
    		int gcder=__gcd(a[i],b[i]);
    		a[i]/=gcder,b[i]/=gcder;
    	}
    	dfs(1,1,1,1);
    	for(int i=1;i<=n*(n+1)/2;i++)
    	{
    		int gcder=__gcd(a[i],b[i]);
    		a[i]/=gcder,b[i]/=gcder;
    	}
    }
    int ans=0;
    for(int i=1;i<=n*(n+1)/2;i++)
    {
    	int gcder=__gcd(a[i],b[i]);
    	a[i]/=gcder,b[i]/=gcder;
    	if(a[i]>=b[i])
    	ans++;
    	//cout<<a[i]<<' '<<b[i]<<'\n';
    }
    cout<<ans;
}
```


---

## 作者：极寒神冰 (赞：0)

事实上这题的复杂度与$t$无关，甚至$n$可以开到$10^4$。

直接将$t$杯水倒入第一个杯子，然后递推，若杯中水量$\geq1$，就推到下一层的两个杯子。

$$dp[i+1][j]=(dp[i][j]-1.0)/2.0 $$
$$dp[i+1][j+1]=(dp[i][j]-1.0)/2.0 $$

复杂度$O(n^2)$

发现可以滚动数组优化，然后就可以跑$10^4$了

```
signed main()
{
	n=read();
	cin>>qwq[1][1];
	R(i,1,n)
	{
		R(j,1,i)
		{
			if(qwq[i&1][j]>=1.0)
			{
				ld tmp=(qwq[i&1][j]-1.0)/2.0;
				qwq[i&1^1][j]+=tmp;
				qwq[i&1^1][j+1]+=tmp;
				tot++;
			}
			qwq[i&1][j]=0.0;
		}
	}
	printf("%lld\n",tot);
}
```


---

## 作者：Graphcity (赞：0)

## 思路

其实这道题直接暴力枚举的时间复杂度 $O(n^2t)$ 是完全没有问题的。用递归的方式枚举即可。每次递归到一个位置时，看看酒杯是不是满了，如果满了就直接往下传，没有满就往里面倒。

注意有些地方要判精度和使用 double 类型。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=10;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,t,ans;
double f[Maxn+5][Maxn+5];

const double eps=1e-7;
inline int Check(double x,double y) // 判断大小
{
    if(fabs(x-y)<=eps) return 0;
    else if(x>y) return 1;
    else return 2;
}
inline void dfs(int x,int y,double d) // 位置(x,y),倒量为d的酒
{
    if(Check(f[x][y]+d,2)==1 && x!=n) // 倒满了,往下传
        f[x][y]=2,dfs(x+1,y,d/2.0),dfs(x+1,y+1,d/2.0);
    else if(Check(f[x][y]+d,2)!=1) // 倒不满,往里加
        f[x][y]+=d;
}

int main()
{
    n=read(),t=read();
    while(t--)
        dfs(1,1,2.0); // 这里设倒满为2
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=i;++j)
            if(Check(f[i][j],2)==0) ans++;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：ShineEternal (赞：0)

更完整看这：https://blog.csdn.net/kkkksc03/article/details/101116393


## solution：

$idea1$:

暴力，每一秒枚举情况

时间复杂度$O(n^2t)$，但是本题不会超时

$idea2:$

~~考虑非正常思考方式~~

我们先把t秒的酒量都倒入第一个杯子中

因为我们只需要找到最后的状态

这样时间复杂度里面的t就可以省掉了。

$O(n^2)$按顺序看看每一个酒杯里有没有需要倒入下一个酒杯的即可

**注意最后是装满的酒杯的个数**

```cpp
#include<cstdio>
using namespace std;
double a[15][15];
int main()
{
	int n,t;
	scanf("%d%d",&n,&t);
	a[1][1]=t;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			if(a[i][j]>=1)
			{
				ans++;
				a[i+1][j]+=(a[i][j]-1)/2.0;
				a[i+1][j+1]+=(a[i][j]-1)/2.0;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
} 
```


---

## 作者：　　　吾皇 (赞：0)

### 思路分析
```
其实这题并没有想象中的那么困难，题中给的速度什么的都没用（只是当一个杯子满了后多出来的部分会平均分配给下两个杯子），而t也可以看做第一个杯子里面有t杯酒。所以核心思路就是模拟，从第一层扫到最后一层，如果a[i][j]>1，那么ans++，再分给下面的杯子
```
### 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
double a[11][11];
//n超级良心，可以开的很小。注意这里是double，因为整形在除的时候可能为0
int n,t,ans;
int main(){
	cin>>n>>t;
    //读入n和t
	a[1][1]=t;
    //因为一共有t秒，所以第一层第一个会装有t杯酒
	for (int i=1;i<=n;i++)
		for (int j=1;j<=i;j++)
        //从第一层一直扫，因为第i层有i个酒杯所以j要扫到i
			if (a[i][j]>=1){
            //如果某个酒杯中的酒大于一杯也就是会溢出
				ans++;
                //答案总数加一
				a[i+1][j]+=(a[i][j]-1)/ 2.0;
				a[i+1][j+1]+=(a[i][j]-1)/ 2.0;
                //下面一层的两个对应酒杯分别分到一半（就算下面没有也不会影响最终结果，因为不会被扫到）
			}
	cout<<ans;
    //最后输出就好
	return 0;
}
```


---

## 作者：Storm_Lightning (赞：0)

## 思路

这一题完全可以把酒杯组想成一个三角形，通过 $a[i][j]$ 来转移 $a[i+1][j]$ 和 $a[i+1][j+1]$ 。那我们就想，如果 $a[i][j]$ 没满或者都过了，这两种标记为 $0$ 和 $1$ 。那就判断，如果 $a[i][j] > 1$ 的话，则就应该向两边 $a[i+1][j]$ 的酒杯和 $a[i+1][j+1]$ 的酒杯去倒。

则易得转移式为：

- $a[i+1][j]=(a[i+1][j]+(a[i][j]-1) \div 2)$

- $a[i+1][j+1]=(a[i+1][j+1]+(a[i][j]-1) \div 2)$

### 注意（小细节）

- $a[i][j]$ 转移完之后要变为 $1$ 。

- 一开始的 $a[1][1]$ 要 $+1$ 。

- 最后统计答案时的条件为 $a[i][j] \ge 1$ 。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,t;
double a[20][20];
void fun()
{
    a[1][1]++;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            if(a[i][j]>1)
            {
                a[i+1][j]+=(a[i][j]-1)/2;
                a[i+1][j+1]+=(a[i][j]-1)/2;
                a[i][j]=1;
            }
        }
    }
}
signed main()
{
    scanf("%lld%lld",&n,&t);
    for(int i=1;i<=t;i++)fun();
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)if(a[i][j]>=1)ans++;
    }
    printf("%lld\n",ans);
    return 0;
}
```

码风一般，勿喷！

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**模拟，暴力破解**的思路：

- 将 $a_{1,1}$ 设为 $t$。然后从上往下枚举当前酒杯是否 $\geq 1$。如果是，则向下面两个酒杯溢出。并将当前酒杯赋值成 $1$。

- 最后，再统计有多少个酒杯的值是 $1$ 即可，时间复杂度为 $O(n^2)$。

## CODE

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20;
int n,ans;
long double a[N][N];//要开double
int main()
{
	cin>>n>>a[1][1];//直接这样输入
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			if(a[i][j]>=1)//如果>=1
			{
				a[i+1][j]+=(a[i][j]-1)/2;
				a[i+1][j+1]+=(a[i][j]-1)/2;//模拟向下溢出
				a[i][j]=1;//赋值成1
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			if(a[i][j]==1)//如果为1
			{
				ans++;//统计
			}
		}
	}
	cout<<ans;//输出
	return 0;
}
~~~

---

## 作者：Cure_Wing (赞：0)

[CF676B Pyramid of Glasses](https://www.luogu.com.cn/problem/CF676B)

想一想，有没有优化的余地。

### 思路

我们用最原始的暴力，每次在顶点的杯子放一滴水，模拟下落的过程。这样时间复杂度 $O(n^2t)$，空间复杂度 $O(n^2)$。

我们发现水滴依次下落和同时溢出对下一层分配方式和结果完全没有影响，所以我们一开始直接在顶点的杯子放 $t$ 滴水，时间复杂度和空间复杂度 $O(n^2)$。

发现我们这么操作后，当前行水滴的数量只依赖于前一行的状态，于是我们滚动数组优化，每一行一边处理一边统计答案，时间复杂度 $O(n^2)$，空间复杂度 $O(n)$。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<iomanip>
using std::cin;using std::cout;
constexpr int N=10005;
int n,ans;
long double a[2][N];
signed main(){
	freopen("pyramid.in","r",stdin);
	freopen("pyramid.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>a[1][1];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=i;++j){
            if(a[i&1][j]>1){
                a[!(i&1)][j]+=(a[i&1][j]-1)/2;
                a[!(i&1)][j+1]+=(a[i&1][j]-1)/2;
                a[i&1][j]=1;
            }//这里使用顺推，这一行溢出到下一行
            ans+=(a[i&1][j]>=1);
            a[i&1][j]=0;//滚动数组清空
        }
    cout<<ans;
    return 0;
}
```

---

