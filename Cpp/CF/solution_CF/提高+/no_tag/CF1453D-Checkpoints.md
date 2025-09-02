# Checkpoints

## 题目描述

Gildong is developing a game consisting of $ n $ stages numbered from $ 1 $ to $ n $ . The player starts the game from the $ 1 $ -st stage and should beat the stages in increasing order of the stage number. The player wins the game after beating the $ n $ -th stage.

There is at most one checkpoint on each stage, and there is always a checkpoint on the $ 1 $ -st stage. At the beginning of the game, only the checkpoint on the $ 1 $ -st stage is activated, and all other checkpoints are deactivated. When the player gets to the $ i $ -th stage that has a checkpoint, that checkpoint is activated.

For each try of a stage, the player can either beat the stage or fail the stage. If they beat the $ i $ -th stage, the player is moved to the $ i+1 $ -st stage. If they fail the $ i $ -th stage, the player is moved to the most recent checkpoint they activated, and they have to beat the stages after that checkpoint again.

For example, assume that $ n = 4 $ and the checkpoints are on the $ 1 $ -st and $ 3 $ -rd stages. The player starts at the $ 1 $ -st stage. If they fail on the $ 1 $ -st stage, they need to retry the $ 1 $ -st stage because the checkpoint on the $ 1 $ -st stage is the most recent checkpoint they activated. If the player beats the $ 1 $ -st stage, they're moved to the $ 2 $ -nd stage. If they fail it, they're sent back to the $ 1 $ -st stage again. If they beat both the $ 1 $ -st stage and the $ 2 $ -nd stage, they get to the $ 3 $ -rd stage and the checkpoint on the $ 3 $ -rd stage is activated. Now whenever they fail on the $ 3 $ -rd stage, or the $ 4 $ -th stage after beating the $ 3 $ -rd stage, they're sent back to the $ 3 $ -rd stage. If they beat both the $ 3 $ -rd stage and the $ 4 $ -th stage, they win the game.

Gildong is going to build the stages to have equal difficulty. He wants you to find any series of stages and checkpoints using at most $ 2000 $ stages, where the [expected number](https://en.wikipedia.org/wiki/Expected_value) of tries over all stages is exactly $ k $ , for a player whose probability of beating each stage is exactly $ \cfrac{1}{2} $ .

## 说明/提示

In the first and the second case, we can see that the 'easiest' series of stages is to have $ 1 $ stage with a checkpoint. This already requires $ 2 $ tries in expectation, so it is impossible to make it to require only $ 1 $ try.

In the third case, it takes $ 2 $ tries in expectation to beat each stage, and the player can always retry that stage without falling back to one of the previous stages if they fail it. Therefore the total expected number of tries is $ 8 $ . Note that there exists an answer with fewer stages, but you are not required to minimize the number of stages used.

## 样例 #1

### 输入

```
4
1
2
8
12```

### 输出

```
-1
1
1
4
1 1 1 1
5
1 1 0 1 1```

# 题解

## 作者：Euler_Pursuer (赞：7)

### 题目大意

有若干个点，有的点有重生点，有的点没有。一到达某个重生点，这个点就是当前重生点。玩家从第一个点开始走走到最后一个点，每个点活与死的概率各一半。给定你期望走的点数，请你构造并输出这样的序列（$1$ 表示重生点， $0$ 表示普通点），没有则输出 $-1$。

### 解题思路

对于这种题目，我们可以考虑分而治之的思维。我们不难发现不论前面是怎样的序列，后面只要出现一个 $1$，那么就与前面的情况独立开来了。因此我们可以分两种情况讨论。

#### 单独的 $1$

对于这种情况，我们发现情况很容易想，要么就是活了离开这个点，要么就是总是死而复生。于是其期望走的点数为：

$$E_0 = \frac{1}{2}\times 1+\frac{1}{2^2}\times 2+\cdots +\frac{1}{2^n}\times n+\cdots$$

利用 $2E_1 - E_1$ 很容易得到：

$$E_0 = 1+\dfrac{\dfrac{1}{2}(1-\dfrac{1}{2^{+\infty}})}{\dfrac{1}{2}} = 2$$

这也验证了样例中的 $2$ 的情况。

#### $1$ 后跟 $0$

我们发现，如果 $1$ 后面跟着 $0$，这个事情就复杂了起来。这里我们用数列的眼光看这个序列。我们设 $E_k$ 表示 $1$ 后跟着 $k$ 个 $0$ 所得到的序列走的点数的期望。

假设我们知道了 $E_k$，对于新加入的第 $k+1$ 个 $0$，要么成功经过它，要么总是失败，回到前面的重生点，再走一遍 $k$ 个 $0$ 的情况，再经历一次第 $k+1$ 个 $0$（听起来很惨）。

因此不难想到：对于 $E_{k+1}$ 与 $E_{k}$ 有这样的关系：

$$E_{k+1} = \frac{1}{2}\times (E_k+1)+\frac{1}{2^2}\times 2(E_k+1)+\cdots +\frac{1}{2^n}\times n(E_k+1)+\cdots$$

类似上面操作一下，就得到通项：

$$E_{k+1} = E_k+1+\dfrac{\dfrac{1}{2}(1-\dfrac{1}{2^{+\infty}})}{\dfrac{1}{2}}\times(E_k+1) = 2(E_k+1)$$

因此，最终的构造可以看做是很多 $1$ 和很多 $100\cdots$ 的组合（当然，$1$ 也可以看作是 $1$ 加上 $0$ 个 $0$）。

这里注意，我们发现任意组合都是偶数，所以遇到奇数就可以直接判断不存在了。

#### 一个说明

学过数列的同学知道：我们其实能够求出 $E_k$ 通项。

上式化为：

$$E_{k}+2 = 2(E_{k-1}+2) = 2^k(E_0+2) = 2^{k+2}$$

所以：

$$E_k=2^{k+2}-2$$

但是对于程序设计，这个并做不到阶的优化，~~所以我们一切从懒~~。

不过这个可以帮我们检验，最终构造的序列一定不会超过 $2000$ 个，满足题目要求。

### 程序实现

我们要注意，我们不一定能够用单一的 $100\cdots$ 序列组成答案，所以这就需要迭代求解。也就是对于每次试着增加 $0$ 的操作，我们都判断当前期望是否超过当前值，超过了就退一个 $0$，当前值减去这个期望，结果作为下一次迭代的值继续求解。具体设计如下：

```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;
int ans[2005];
int main()
{
    int T;
    long long k, v, z;
    scanf("%d", &T);
    while(T--)
    {
        int tot = 2000, vas = 0;
        v = 0;
        scanf("%lld", &k);
        z = k;
        if(k & 1)
        {
            printf("-1\n");
            continue;
        }
        do
        {
            v = 0;
            while(z >= v)
            {
                if(v)
                    ans[tot+1] = 0;
                ans[tot] = 1;
                v = 2ll*(v+1ll);
                tot -= 1;
            }
            tot += 1;
            ans[tot]=0;
            ans[tot+1]=1;
            z -= v/2-1;
        }while(z > 0);
        printf("%d\n", 2000-tot);
        for(register int i = tot+1; i<=2000;i+=1)
            printf("%d ", ans[i]);
        puts("");
    }
    return 0;
}

```

### 一点话

经典比赛的时候推不出来，比赛一结束就知道了，哭唧唧，又掉分了。

---

## 作者：Lynkcat (赞：2)

首先我们可以发现，当关卡如 $1\ 0\ 0\ 0 ……$ 的方式构造时，对答案产生的贡献用二进制表示为 $11111……1110$ 的形式。

那我们显然可以可以考虑二进制构造。

我们发现如果 $k$ 在二进制第 $0$ 位上为 $1$ ，那么我们构造不出一种方案来满足答案中有单独的 $2^0$ ，因此直接 $-1$ 。

否则我们一定可以通过构造一个贡献 $11111……1110$ 的关卡 $1\ 0\ 0\ 0……$ ,再加上一个单独的 $1$ 关卡构造出这个答案。

显然这个需要的关卡数非常的少。完全比 $2000$ 要小。

```c++
int T,n;
vector<int>G;
signed main()
{
	T=read();
	while (T--)
	{
		n=read();G.clear();
		if (n&1) puts("-1"); else
		{
		for (int i=1;i<=63;i++)
			if ((1ll<<i)&n)
			{
				if (i!=1){
				G.push_back(1);
				for (int j=1;j<i-1;j++) G.push_back(0);}
				G.push_back(1);
			}
			writeln(G.size());
			for (int i=0;i<G.size();i++) writesp(G[i]);
			puts("");
		}
	}
	
}
```

---

## 作者：Little09 (赞：1)

先破解这个期望。一个 $1$ 通过的期望步数是 $2$，一个 $1$ 后面带上 $x$ 个 $0$ 连续通过的期望步数是 $2^{x+2}-2$。这个不会的同学可以看一下 [P6835 [Cnoi2020]线形生物](https://www.luogu.com.cn/problem/P6835)。

然后考虑构造。构造若干个形如 $10...0$ 的段，每个段的期望就是 $2^{x+2}-2$。就是二进制分解，这样分解必定是可行的。多试几组发现根本过不了 $2000$，很稳。


另外奇数显然无解，输出 `-1`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2001],cnt;
long long u[61];
void fill(int x)
{
	a[++cnt]=1;
	for (int i=1;i<=x-2;i++) a[++cnt]=0;
}
void f(long long x)
{
	long long tot=x;
	for (int i=60;i>=2;i--)
	{
		while (tot>=u[i]) 
		{
			fill(i);
			tot-=u[i];
		}
	}
	//assert(tot==0);
}
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int main()
{
	u[0]=1;
	for (int i=1;i<=60;i++) u[i]=u[i-1]*2ll;
	for (int i=2;i<=60;i++) u[i]-=2ll;
	int T=read();
	while (T--)
	{
		long long n;
		cin >> n;
		cnt=0;
		if (n%2==1) 
		{
			cout << -1 << endl;
			continue;
		}
		f(n);
		cout << cnt << endl;
		for (int i=1;i<=cnt;i++) cout << a[i] << " ";
		cout << endl;
	}
	return 0;
}
```


---

## 作者：Prean (赞：0)

VP 的时候发现的一道数学题（

在思考这个问题之前，先让我们思考一件事：走到距离上一个存档点 $ n $ 的位置的期望是多少？（假设这个值为 $ f[n] $）

先思考 $ f[1] $ 是多少，很明显是：
$$ S=\sum_{i=0}^{\infty}i \times 2^{-i} $$
手拆一下：
$$ 2^{-1}S=\sum_{i=1}^{\infty}(i-1) \times 2^{-i} $$
相减：
$$ 2^{-1}S=\sum_{i=1}^{\infty}2^{-i} $$
很容易得到 $ 2^{-1}S=1 $，也就是 $ f[1]=2 $ ~~当然你也可以通过观察样例来得到这个结论~~ 

来思考 $ f[n] $，考虑从 $ f[n-1] $ 递推过来。枚举失败的次数：
$$ f[n]=\sum_{k=0}^{\infty}((k+1) \times f[n-1]+(k+1)) \times 2^{-k-1} $$
$$ f[n]=(f[n-1]+1)\sum_{k=1}^{\infty}k \times 2^{-k} $$
于是有 $ f[n]=(f[n-1]+1) \times 2 $。手玩一下即可发现 $ f[n]=2^{n+2}-2 $。

因为期望具有线性性，（$ E(a+b)=E(a)+E(b) $）于是问题就变成了了如何用若干个 $ f $ 凑出 $ k $。

变形一下，$ f[n]=2(2^{n+1}-1) $，说明 $ n $ 为奇数时一定不行。

于是我们枚举最大的 $ f $，枚举到一个就让 $ k $ 减去 $ f $，然后当做当前的 $ k $ 接着做。
```cpp
#include<cstdio>
typedef long long ll;
ll k,f[61];int len,ans[2005];
signed main(){
	int T,i,j;ll k;f[0]=2;scanf("%d",&T);
	for(int i(1);i<=60;++i)f[i]=f[i-1]+1<<1;
	while(T--){
		scanf("%lld",&k);len=0;
		if(k&1){
			printf("-1\n");continue;
		}
		for(i=60;i>=0;--i){
			while(k>=f[i]){
				ans[++len]=1;
				for(j=1;j<=i;++j)ans[++len]=0;k-=f[i];
			}
		}
		printf("%d\n",len);
		for(i=1;i<=len;++i)printf("%d ",ans[i]);printf("\n");
	}
}
```

---

## 作者：qhztz (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1453D)
## 题目大意：
构造一个序列，1 就是当前关卡的存档点，0 就不是， 给一个 $k$，怎么构造关卡序列使得所有关卡的期望等于 $k$，每个关卡的通过率是$\large\frac{1}{2}$ 。
## 思路：
思考后发现：1 的关卡的期望一定是 2，问题就在 0001 这种上面，在 1 这个关卡上一定要 2 次，那 1 前面的 0 就要 4 次，因为 4 次机会才会有两次机会通过，这两次机会才能通过后面的 1，所以不难发现规律，那事情就简单了，就按着这样一直去减即可。

**要注意题目规定了第一个关卡必须是 1。**

每个关卡的期望贡献都是偶数，所以和一定是偶数，那奇数就是 −1。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,k;
int main(){
	scanf("%lld",&T);
	while(T--){
		vector<int> ans;//用vector储存答案
		scanf("%lld",&k);
		if(k&1){
			printf("-1\n");
			continue;
		}
		k-=2;
		while(k){
			ans.push_back(1);
			k-=2;
			for(ll i=4;i<=k;i<<=1)
				ans.push_back(0),k-=i;
		}
		ans.push_back(1);
		reverse(ans.begin(),ans.end());
		printf("%d\n",ans.size());
		for(int i=0;i<ans.size();++i)
			printf("%d ",ans[i]);
		printf("\n");
	}
}
```
拜拜qwq

---

