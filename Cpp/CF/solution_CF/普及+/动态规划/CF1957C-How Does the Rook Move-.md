# How Does the Rook Move?

## 题目描述

你在一个 $n\times n$ 的棋盘上玩一个游戏。

你每次可以选择在 $(r,c)$ 的位置放置一个**白色的车**，使得放置后所有车无法通过水平或垂直的方向攻击到其它车（无论颜色）。如果 $r\not=c$ 则电脑在 $(c,r)$ 处放一个**黑色的车**，可以证明，如果你的操作合法，电脑操作必定合法。

现在你已经放置了 $k$ 个白色的车（显然电脑也已经进行了对应操作），如果你继续放车直到没有合法的位置放车，则游戏结束。

你希望知道游戏结束时形成的局面的可能性。

答案对 $10^9+7$ 取模。

两个局面不同当且仅当某个位置上的车颜色不同或其中一个局面放了车而另一个没有。

## 说明/提示

对于全部数据，满足 $ 1 \leq t \leq 10^4 $，$ 1 \leq n \leq 3 \times 10^5 $ , $ 0 \leq k \leq n $，$\sum n\le3\times10^5$。

## 样例 #1

### 输入

```
3
4 1
1 2
8 1
7 6
1000 4
4 4
952 343
222 333
90 91```

### 输出

```
3
331
671968183```

# 题解

## 作者：破壁人罗辑 (赞：12)

题面传送门：[洛谷](https://www.luogu.com.cn/problem/CF1957C)/[Codeforces](https://codeforces.com/problemset/problem/1957/C)

## 解题思路

对于任意一种排满方案，每一行和每一列都必须存在且仅存在一颗棋子。

证明：若一行或一列超过一颗棋子，则它们可以相互攻击，不为合法方案。若 $n\times n$ 的棋盘上有一行不存在棋子，那么因为每行都只能存在不多于一颗棋子，那么棋盘上的棋子总数必然小于或等于 $n-1$，那么因为每个棋子都只能占据一列，存在棋子的列也必然小于或等于 $n-1$，必然有一列不存在棋子，在不存在棋子的这一行和这一列的交点处落子的方案一定是合法的。

在棋盘的左上-右下的对角线上落子相当于删去了棋盘的一行和一列，在其它地方落子由于电脑的对称操作相当于删去了棋盘的两行和两列。

设 $f(n)$ 表示 $n\times n$ 的棋盘上的排满棋子的方案。

显然，$f(0)=1,f(1)=1,f(2)=3$。

当 $n>2$ 时，由于第一行和第一列一定会有棋子，为了防止重复，我们先考虑第一行和第一列，分两种情况考虑：

- 若在 $(1,1)$ 落子，则相当于删去了棋盘的一行和一列，此情况下的方案数为 $f(n-1)$；
- 若不在 $(1,1)$ 落子，则相当于在第一行和第一列除了 $(1,1)$ 之外的 $2n-2$ 个点中选取任意一点落子，相当于删去了棋盘的两行和两列，此情况下的方案数为 $(2n-2)f(n-2)$。

所以，我们可以得到如下表达式：

$$f(n)=\begin{cases}
	1&,n\leq 1\\
	f(n-1)+(2n-2)f(n-2)&,n\geq 2
\end{cases}$$

递推或者记忆化递归都能解决，时间复杂度 $O(n_{max})$。

## AC 代码
### C++
```cpp
#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
unordered_map<int,long long>mp;
long long f(int n){
	if(mp.find(n)==mp.end())mp[n]=(((n-1ll)<<1)*f(n-2)+f(n-1))%MOD;
	return mp[n];
}
int main(){
	mp[1]=1;mp[0]=1;mp[2]=3;
	int T;scanf("%d",&T);while(T--){
		int n,k;scanf("%d%d",&n,&k);
		for(int i=0;i<k;i++){
			int x,y;scanf("%d%d",&x,&y);
			n=n-(x==y?1:2);
		}
		printf("%lld\n",f(n));
	}
	return 0;
}
```
### Python
```python
T=int(input())
f=[1 for i in range(300001)]
for i in range(2,300001):
    f[i]=(f[i-1]+2*(i-1)*f[i-2])%1000000007
for Tt in range(T):
    [n,k]=input().split()
    n=int(n)
    k=int(k)
    for i in range(k):
        [x,y]=input().split()
        if x==y:
            n=n-1
        else:
            n=n-2
    print(f[n])
```

---

## 作者：hgckythgcfhk (赞：4)

考虑到车的性质，每次会导致同行同列不可用，题面说的很清楚，可以保证黑车不与白车冲突，所以相当于放了两个车，对于一个边长为 $n$ 的棋盘每次选完可以通过平移拼接出一个边长为 $n-2$ 的棋盘，这个性质没有后效性，发现可以 dp，由于黑车和白车有一定的关系，确定白车的位置黑车的位置就唯一确定，考虑到黑车能放的前提是白车的横纵坐标不相等，所以在 $n^2$ 的棋盘上只有 $n\times(n-1)$ 个可选的位置，这样总感觉哪里怪怪的，因为看似 dp 式写出来不会和上一项有关系，但这种一次一次操作的数数题和上一项没关系很别扭，仔细读题，发现我们还露了一种情况，那就是黑车不能放的情况，这样我们只会放一个白车，有 $n$ 种放法，然后我们就得到了一个看起来很对的式子 $dp_i=n\cdot dp_{i-1}+\dfrac{n\times(n-1)}{2}\cdot dp_{i-2}$ 。但做过点数数题的人就知道，我们通过翻译字面意思得到的式子一般会算重，这个式子是把放置顺序不同的情况看作为了不同情况，但我们只要结果，发现原因是因为我们式子中的两项每一项都同时考虑了行和列，我们看作一边只管行一边只管列，反正行和列是一样的，那限定一下，$n-1$ 不能管行，那就得固定到某一行，只有一种选择，$n-2$ 不能管列，那就得固定在某一列，有 $n-1$ 种选择，最后讨论颜色，$n-1$ 的颜色固定是白色，不用管，$n-2$ 的情况选 $(r,c)$ 和 $(c,r)$ 为白色是一样的，但会造成不一样的结局局面且无法逆转，所以要乘 $2$。

则有 $dp_i=dp_{i-1}+2\cdot(n-1)\cdot dp_{n-2}$，由于本人极其手残，家里碰不到电脑偷着用手机在在线 IDE 上不知道哪里扣挂了，一气之下把程序全都删了，~~看一眼题解后~~发现其实记忆化搜索比较不容易挂，于是就写了一个记忆化搜索，这启示我们 dp 题并不是不能递归，这次没有火车头，用手机扣的，程序略微有点不美观，但勉强能看。

展开了当时用手机扣的两行的程序。

```cpp
#include<bits/stdc++.h>
using namespace std;
unordered_map<int,long long>m;
inline long long aa(int n){
  if(m.find(n)==m.end())
  	m[n]=(((n-1ll)<<1)*aa(n-2)+aa(n-1))%1000000007;
  return m[n];
}
signed main(){
  m[1]=1;m[0]=1;m[2]=3;
  int t;cin>>t;
  while(t--){
   	int n,k,x,y;cin>>n>>k;
    	for(int i=0;i<k;i++)cin>>x>>y,n-=(x==y?1:2);
     	cout<<aa(n)<<'\n';
  }
}
```
直接在文章编辑区展开的，无任何修改，保证可以运行。

---

## 作者：___Furina___ (赞：4)

### 题意简述：
无。
### 题解：
~~根据 OEIS，我们可得：~~
尝试手推转移方程，我们可得：

$f_i=f_{i-1}+2(i-1)f_{i-2}$。

下面给出推导过程：

不妨假设从右下角下到左上角。

- 若下一步下在 $(1,1)$，行列各减少一行；
- 若下在第一行或第一列别的位置，由于电脑也要下，所以行列各减少两行。

从而得出式子。
### 注意：
- 开 longlong；
- 取模。
### 代码如下：
```cpp
#include<bits/stdc++.h>
#define N 300010
#define I_love_Furina return //发电+防抄袭
#define forever 0
#define int long long//防止溢出
#define mod 1000000007//取模！！！
using namespace std;
int n,T,m,a[N],f[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	f[0]=1,f[1]=1,f[2]=3;
	for(int i=3;i<=300000;i++)f[i]=(f[i-1]+2*(i-1)*f[i-2]%mod)%mod;//转移方程
	while(T--){
		cin>>n>>m;
		int cnt=0;
		for(int i=1,x,y;i<=m;i++){
			cin>>x>>y;
			if(x==y)cnt++;//主对角线行列各减少一行
			else cnt+=2; //否则各减少两行
		}
		cout<<f[n-cnt]<<endl;
	}
  I_love_Furina forever;//完结撒花
}
```
点个赞再走！！！

---

## 作者：MMXIandCCXXII (赞：2)

$\Large{\text{solution}}$

听了学长讲解，感觉 DP 好简单。

通过题意和样例，不难发现，每在对角线上放一个，因为无法对称，就只会少一行一列，如果放之前是 $n \times n$，放之后就是 $(n-1)\times (n-1)$。而放在其他地方，对称之后都会少两行两列，就会变成 $(n-2) \times (n-2)$。

于是我们定义 $f_i$ 为将边长为 $i$ 的空正方形填完的情况数。

我们假设现在是 $n\times n$ 的正方形，还能填一次，假设填在对角线上，就只有一种情况，因为其他对角线上的点已经都填上了（只能填一次），这样填完剩下的部分的填法就是 $f_{i-1}$，不填在对角线上，就有 $2(i-1)$ 个点可填，填完之后对称一下，剩下的部分就是 $f_{i-2}$，所以转移方程就是
$$
f_i = f_{i - 1} + 2(i-1)f_{i - 2}
$$

最后记得取模。

![](https://cdn.luogu.com.cn/upload/image_hosting/jdaopoxw.png)

$\Large{\text{code}}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 7;
int f[300010];

signed main()
{
    f[1] = f[0] = 1;
    for (int i = 2; i <= 300000; i++) f[i] = (f[i - 1] + 2 * (i - 1) * f[i - 2] % mod) % mod;
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            cin >> x >> y;
            if (x == y) n--;
            else n -= 2;
        }
        cout << f[n] << endl;
    }
    return 0;
}
```

---

## 作者：ChenYanlin_20 (赞：2)

### 思路
一道DP，设 $f_i$ 表示填满边长为 $i$ 的棋盘所有的方案数。由于计算机会镜像棋子，不难发现当我们选择对称轴计算机无法镜像时，会占去最外层的一列和一行，此时的方案相当于 $f_{i-1}$ ![](https://cdn.luogu.com.cn/upload/image_hosting/75oh176w.png)
由于每个棋子会占去 $1$ 横 $1$ 边，当我们的选择计算机可以镜像时,棋盘的横宽相当于减 $2$ ，相当于 $f_{i-2}$ 
![](https://cdn.luogu.com.cn/upload/image_hosting/ub4w1n4k.png)

除去对称轴，横纵均有 $i-1$ 个 $2$ 情况，对角线有一种 $1$ 情况，所以 $f_i = (i-1)\times2\times f_{i-2} + f_{i-1}$ ,注意取模。
### CODE
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10,Mod=1e9+7;
int f[N];
signed main(){
	int t;
	cin>>t;
	f[0]=1,f[1]=1;
	for(int i=2;i<N;i++)
		f[i]=(f[i-1]+2*(i-1)*f[i-2]%Mod)%Mod;
	while(t--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			int x,y;
			cin>>x>>y;
			if(x==y)
				n--;
			else n-=2;
		}
		cout<<f[n]<<'\n';
	}	
	return 0;
}
```

---

## 作者：analysis (赞：1)

20240423

---

### $k = 0$

容易发现操作 $(i,i)$ 删去一行一列，$(i,j)|i \neq j$ 删去两行两列。

于是设 $f_{i}$ 表示在 $i \times i$ 的空棋盘上的方案。

为了不重不漏，我们需要保证操作的出现顺序。

于是钦定第一次操作一定要消除第一行第一列，得到式子：

$$
f_i = f_{i-1} + 2(n-1)f_{i-2}
$$

递推求出即可。

### $k \neq 0$

模拟 $k$ 次操作，若 $i = j$ 令 $n \to (n-1)$，否则 $n \to (n-2)$。

得到一个新的 $n$，问题转化为 $k=0$，答案即为 $f_n$。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
using namespace std;
int t,k,n;
int f[300005];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    f[0] = f[1] = 1;
    for(int i=2;i<=3e5;i++)
    {
        f[i] = (f[i-1] + f[i-2] * (i-1) % mod * 2 % mod) % mod;
    }
    cin >> t;
    while(t--)
    {
        cin >> n >> k;
        while(k--)
        {
            int a,b;
            cin >> a >> b;
            n--;
            if(a != b)n--;
        }
        cout<<f[n]<<'\n';
    }
    return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

[Link](https://www.cnblogs.com/Luxinze/p/18162677#c-how-does-the-rook-move)

题意：$n \times n$ 的棋盘上 $A$ 与电脑轮流下车，$A$ 白子，电脑黑子，满足：

+ 一行或一列只能存在一个车，不论颜色。
+ $A$ 下在 $(i, j)$，则电脑下 $(j, i)$。
+ $A$ 下在 $(i, i)$，则电脑 skip。

$A$ 先手，给定 $A$ 的前 $k$ 步棋，求不同的最终局面个数。

注意到最终局面与前 $k$ 步棋的位置无关，只取决于于 $k$ 步之后还剩多少行和列。

不妨让 $n$ 表示新的行数。

1. 下在 $(i, i)$ 相当于在剩余列中选出一列。
2. 下在 $(i, j)$ 相当于白子选一列，黑子选一列。

如果当前下了 $i$ 步 $1$ 类棋。

此时 $n - i$ 一定要偶数，否则 $2$ 类棋下不完剩余列。

令 $j = \dfrac{n - i}{2}$，则问题转化为在 $n - i$ 个数中选出 $j$ 对二元组的方案。


钦定白子选的列，然后黑子任意排列，则方案为 $\begin{pmatrix}n - i\\ j \end{pmatrix} j!$。


所以最终局面数为 $\sum\limits_{i = 0}^n [n - i \equiv 0 \pmod 2] \begin{pmatrix}n\\ i \end{pmatrix} \begin{pmatrix} n - i\\ j\end{pmatrix} j!$。

[submission](https://codeforces.com/contest/1957/submission/258329684)

---

## 作者：liugh_ (赞：0)

[CF1957C How Does the Rook Move?](https://codeforces.com/contest/1957/problem/C)

若在 $(x,y)$ 放了一个白子，则必须同时在 $(y,x)$ 放一个黑子（当 $x=y$ 时则不放黑子），求放完棋子（使得每行每列有且仅有 $1$ 个棋子）的方案数。

考虑每放置一个白子，空余的行数（棋盘是正方形，故行和列等价）有什么变化？例如一个 $5\times 5$ 的空棋盘，若 $x=y$，因为棋子只会影响其所在的行和列，对其余行和列没有影响，考虑将分割成的各个部分拼在一起，形成了一个新的空棋盘，大小为 $4\times 4$。 如下图，$\red{+}$ 表示放白子的位置，$\red{\times}$ 表示被“封锁”的行和列，彩色的 $-$ 表示空余的行和列被分割成的各个部分。

$$
\begin{aligned}
&\orange{-}\red{\times}\blue{-}\blue{-}\blue{-} &\orange{-}\blue{-}\blue{-}\blue{-}\\
&\red{\times}\red{+}\red{\times}\red{\times}\red{\times} &\green{-}\purple{-}\purple{-}\purple{-}\\
&\green{-}\red{\times}\purple{-}\purple{-}\purple{-} \qquad\rightarrow\quad &\green{-}\purple{-}\purple{-}\purple{-}\\
&\green{-}\red{\times}\purple{-}\purple{-}\purple{-} &\green{-}\purple{-}\purple{-}\purple{-}\\
&\green{-}\red{\times}\purple{-}\purple{-}\purple{-}\\
\end{aligned}
$$

此时你想到了什么？递推！没错，继续看 $x\ne y$ 的情况，将各个部分拼在一起后形成了一个 $3\times 3$ 的新棋盘。

$$
\begin{aligned}
&\red{\times}\red{\times}\red{+}\red{\times}\red{\times} \\
&\red{\times}\orange{-}\red{\times}\blue{-}\blue{-} &\orange{-}\blue{-}\blue{-}\\
&\red{+}\red{\times}\red{\times}\red{\times}\red{\times} \qquad\rightarrow\quad &\green{-}\purple{-}\purple{-}\\
&\red{\times}\green{-}\red{\times}\purple{-}\purple{-} &\green{-}\purple{-}\purple{-}\\
&\red{\times}\green{-}\red{\times}\purple{-}\purple{-}\\
\end{aligned}
$$

我们指定将棋子放在第 $1$ 行或第 $1$ 列，为什么正确？例如 $x=y$ 的情况，将白子放在对角线上的哪一个位置，棋盘大小都只会 $-1$，故看做一种方案。

设放白子前棋盘大小为 $i$，则我们有 $1$ 种放置方法使得 $x=y$，即放在 $(1,1)$。同理，我们一共有 $2(i-1)$ 种放置方法使得 $x\ne y$，即把棋子放在除 $(1,1)$ 的位置上。如下图，$\blue{O}$ 表示可以放置的位置。

$$
\begin{aligned}
O\blue{O}\blue{O}\blue{O}\blue{O}\\
\blue{O}OOOO\\
\blue{O}OOOO\\
\blue{O}OOOO\\
\blue{O}OOOO\\
\end{aligned}
$$

此时答案已经显然，我们有递推式 $f_i=f_{i-1}+2(i-1)f_{i-2}$。最后，一开始已经放置的白子怎么办？只要预处理出一开始空闲的行数 $n'$，答案即为 $f_{n'}$。

---

## 作者：sbno333 (赞：0)

我对这道题的评价是比 D 难。

我们考虑证明电脑合法的充要条件是我们合法。

假设不成立，则有 $(r,c')$ 与 $(r,c)$ 冲突，且 $(c,r)$ 合法。

有 $(r,c')$ 必然有 $(c',r)$，与 $(c,r)$ 冲突，$(r',c)$ 同理。

此时与假设冲突，故假设不成立。

我们考虑每次操作对禁止放棋子格子的贡献。

$(c,r)$ 对第 $c$ 行和第 $r$ 列产生攻击，由于有 $r,c$，所以会对 $c,r$ 行和列攻击，此时二者本质一致，所以只考虑一维。

问题变成每一次选取二元组 $(x,y)$，使得之前两个数都没有出现过，求方案数，不考虑顺序。

当然，$x$ 可以等于 $y$，所以就是对 $1\sim n$ 的数打包，每一包都是 $1\sim2$ 个数，求方案数。

由于放置于 $c<r$ 和 $r<c$ 本质一致，但算不同方案，所以打包成 $2$ 的产生 $2$ 贡献。

我们考虑枚举打包成 $1$ 的数量和 $2$ 的数量，由于打包顺序不计算，因此可以先打包 $1$，再打包 $2$，此时 $1$ 内部顺序要去掉，$2$ 内部顺序要去掉，但每包两个的先后顺序不需要去掉，因为每一包需要 $2$ 的贡献。

处理顺序是容易的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mod=1e9+7;
int ksm(int a,int b){
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
int jc[1000009];
int cj[1000009];
void _main(){
	int n,k;
	cin>>n>>k;
	int m;
	m=n;//还剩多少未打包
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		if(x==y){
			m--;
		}else{
			m-=2;
		}
	}
	int ans;
	ans=0;
  	int l;
	l=ceil(m/2.0);
	int sum1,sum2;
	sum1=m;//sum1 个 1 的
	sum2=0;//sum2 个 2 的
	for(int i=m;i>=l;i--){
		ans+=jc[m]*cj[sum1]%mod*cj[sum2]%mod;//所有的结成去掉组内阶乘
		ans%=mod;
		sum1-=2;//变成下一个情况
		sum2++;
	}
	cout<<ans<<endl;
}
signed main(){
	jc[0]=1;
	for(int i=1;i<=1000000;i++){
		jc[i]=jc[i-1]*i%mod;//阶乘处理顺序
	}
	cj[1000000]=ksm(jc[1000000],mod-2);
	for(int i=999999;i>=0;i--){
		cj[i]=cj[i+1]*(i+1);//阶乘逆元
		cj[i]%=mod;
	}
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

定义 $f_{i}$ 表示为还剩下 $i$ 行 $i$ 列时的方案数，则 $f_1=1,f_0=1$。

而发现的是每次 $f_i$ 都增加了最后一行以及左后一列，而放置这其中的任意一个格子会出现两种情况：

- 放置在对角线上，则此时计算机不会模仿操作，只占用的 $1$ 行 $1$ 列，则此时答案为 $f_{i-1}$。
- 放置在其他地方，则此时计算机会占用另一个格子，则此时占用了 $2$ 行 $2$ 列，答案为 $2\times \left(i-1\right)\times f_{i-2}$。

则此时已经占用了一些格子，而剩下的格子依然有如上两种条件，则显然下的棋子会减去 $1$ 或 $2$ 的贡献，答案为贡献。

#### code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define lx first
#define ly second
const int maxn=3e5+10;
const int inf=1e9+7;
ll f[maxn];
int T,n,m;
signed main(){
    scanf("%d",&T);f[0]=f[1]=1;
    for(int i=2;i<=maxn-10;++i)f[i]=(f[i-1]+2*(i-1)*f[i-2])%inf;
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i){int r,c;scanf("%d%d",&r,&c);n-=2-(r==c);}
        printf("%lld\n",f[n]);
    }
    return 0;
}
```

---

