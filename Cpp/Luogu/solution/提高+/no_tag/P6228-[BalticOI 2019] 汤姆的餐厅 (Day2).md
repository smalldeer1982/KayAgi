# [BalticOI 2019] 汤姆的餐厅 (Day2)

## 题目背景

**译自 [BalticOI 2019](http://boi2019.eio.ee/tasks/) Day2 T1.** ***[Tom's Kitchen](http://boi2019.eio.ee/wp-content/uploads/2019/05/kitchen.en_.pdf)***

## 题目描述

*Tom's Kitchen* 是一家非常受欢迎的餐厅，其受欢迎的原因之一是每份菜都由至少 $ K $ 名厨师进行准备。今天有 $ N $ 份菜需要准备，第 $ i $ 份菜的准备时间是 $ A_i $ 小时。

Tom 可以雇佣 $ M $ 名厨师，厨师 $ j $ 最多可以工作 $ B_j $ 小时。此外，即使厨师 $ j $ 的工作时间不到 $ B_j $ 小时，他也会得到工作 $ B_j $ 小时的报酬。一名厨师可以花不同的时间准备不同的菜，但是每一道菜都需要由至少 $ K $ 名厨师准备，并且他们花的时间总和恰好为 $ A_i $。当一名厨师准备菜品时，他总会花正整数小时。

Tom 需要一套最优的雇佣厨师方案，以使得厨师不工作就获得报酬的小时数（即所有雇佣厨师的总工作时间上限与准备所有菜的总时间之差）尽可能小。

## 说明/提示

### 样例解释 1

Tom 需要雇佣这两位厨师来完成所有菜的准备工作。准备所有菜的时间为 $ 5 $ 小时，但 Tom 需要支付 $ 3+4=7 $ 小时的费用，即厨师不工作就能得到 $ 2 $ 小时的工资。

### 样例解释 2

准备一份菜需要至少两位厨师，但只能雇佣一位厨师，因此不能完成准备工作。

### 样例解释 3

第三份菜无法由三位厨师来准备，因为准备第三份菜的时间只有 $ 2 $ 小时（这意味着如果由三名厨师准备第三份菜的话，至少有一位厨师的准备时间是 $ 0 $ 小时，而这是不符合题目要求的）。

### 子任务

各子任务的分值与数据规模如下：

- 子任务 1（9 分）：$ 1 \leq N,K \leq 300, 1 \leq M \leq 2, 1 \leq A_i,B_j \leq 300 $；
- 子任务 2（22 分）：$ 1 \leq N,K \leq 300, 1 \leq M \leq 15, 1 \leq A_i,B_j \leq 300 $；
- 子任务 3（20 分）：$ 1 \leq N,M,A_i,B_j \leq 300, K=1 $；
- 子任务 4（21 分）：$ 1 \leq N,M,K,A_i,B_j \leq 40 $；
- 子任务 5（28 分）：$ 1 \leq N,M,K,A_i,B_j \leq 300 $。

## 样例 #1

### 输入

```
1 2 2
5
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
1 1 2
5
5```

### 输出

```
Impossible```

## 样例 #3

### 输入

```
3 3 3
3 3 2
3 3 3```

### 输出

```
Impossible```

# 题解

## 作者：StudyingFather (赞：12)

显然当 $\exists i \in [1,N]$，满足 $A_i \lt K$ 的时候无解。

在排除这种情况后，我们考虑 DP。

我们将每个菜的时间分拆为两部分：基本时间和额外时间。基本时间为 $K$ 小时，每个参与这道菜制作的厨师最多可以向它贡献 $1$ 小时时间（这样就满足了至少 $K$ 个厨师参与制作的要求），同时一个厨师的工作时间中，最多有 $\min \{N,B_i\}$ 的时间可以贡献为基本时间。剩下的时间则是额外时间。

一个方案是合法的，当且仅当：

1. 总雇佣时间 $\geq \sum a_i$；
2. 所有厨师向基本时间的贡献 $\geq N \times K$（超过的部分可以自动并入额外时间中，注意对额外时间的分配没有任何限制）。

这是一个背包的模型。

设 $f_{i,j}$ 表示考虑前 $i$ 位厨师，总雇佣时间为 $j$ 时，最大的基本时间数。

对于每个状态，有两种决策：

1. 不选第 $i$ 名厨师，此时 $f_{i,j}=f_{i-1,j}$；
2. 选第 $i$ 名厨师，此时 $f_{i,j}=f_{i-1,j-B_i}+\min \{N,B_i\}$。

在两种决策中选最优的一种即可。

最终最小合法雇佣时间数就是满足 $f_{M,j} \geq N \times K$ 且 $j \geq \sum a_i$ 的最小的 $j$。

时间复杂度 $O(M\sum b_i)$，空间复杂度在滚动数组优化后可以做到 $O(\sum b_i)$，可以通过本题。

```cpp
// Problem : P6228 [BalticOI 2019 Day2]汤姆的餐厅
// Contest : Luogu Online Judge
// URL : https://www.luogu.com.cn/problem/P6228
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 250 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int b[305],f[2][90005];
int main()
{
 int n,m,k,suma=0,sumb=0;
 cin>>n>>m>>k;
 for(int i=1;i<=n;i++)
 {
  int x;
  cin>>x;
  if(x<k)
  {
   cout<<"Impossible"<<endl;
   return 0;
  }
  suma+=x;
 }
 for(int i=1;i<=m;i++)
  cin>>b[i];
 memset(f,191,sizeof(f));
 f[0][0]=0;
 for(int i=1;i<=m;i++)
 {
  int p=i&1,q=p^1;
  for(int j=0;j<b[i];j++)
   f[p][j]=f[q][j];//这种情况下只能选决策一
  sumb+=b[i];
  for(int j=b[i];j<=sumb;j++)
   f[p][j]=max(f[q][j],f[q][j-b[i]]+min(b[i],n));
 }
 for(int i=suma;i<=sumb;i++)
  if(f[m&1][i]>=n*k)
  {
   cout<<i-suma<<endl;
   return 0;
  }
 cout<<"Impossible"<<endl;
 return 0;
}
```

---

## 作者：Sampson_YW (赞：3)

一个傻呗 $O\left(\frac{n^4}{\omega}\right)$ 做法。

先判掉 $A_{i}<K$ 的无解情况。考虑判断一种选厨师的方案是否合法。

假如选的厨师集合为 $S$，那么要满足两个条件：

1. 这些厨师工作总时长 $\ge$ 所有种类的菜需要的总时长。也就是 $\sum_{j\in S}B_j\ge\sum A_i$。
2. 这些厨师各自最多能做的菜的种类数之和 $\ge$ 每种的菜需要的厨师数量之和。也就是 $\sum_{j\in S}\min(B_j,N)\ge NK$。

容易想到一个 $O(n^6)$ 的 dp 做法：

设 $dp_{i,j,k}$ 表示考虑前 $i$ 个人是否在 $S$ 中，是否存在一种选人方式使得在 $S$ 中的人 $\sum B=j,\sum \min(B,N)=k$。

考虑优化。上述状态中 $j$ 和 $k$ 不同的地方在于 $k$ 中有个 $\min(B,N)$，考虑从这个 $\min$ 入手，将它去掉。

当 $B\leq N$ 时，$\min(B,N)=B$，当 $B>N$ 时，$\min(B,N)=N$。又因为选人的顺序是没有影响的，所以可以将人按 $B$ 分成两类：$B\leq N$ 的人和 $B>N$ 的人。

如果对第一类人做上述 dp，他们的 $j$ 和 $k$ 是完全一样的。那么只要设 $f_{i,j}$ 代表前 $i$ 个人，$\sum B=j$ 时是否可行即可。复杂度 $O(n^3)$。

如果对第二类人做上述 dp，容易发现 $k=|S|\times N$，也就是只和选了多少个人有关。那么设 $g_{i,k,j}$ 表示前 $i$ 个人，选了 $k$ 个人，$\sum B=j$ 是否可行。用 bitset 优化即可做到 $O\left(\frac{n^4}{\omega}\right)$。

记 $s=\sum A$。接下来将两类人合并：

由于两个 dp 的第一维在合并时是没有用的，那么可以用滚动数组优化掉。

设 $f_j$ 表示第一类人中选出一些人使得 $\sum B=j$ 是否可行，$g_{k,j}$ 表示第二类人中选出 $k$ 个人使得 $\sum B = j$ 是否可行。

合并的时候先考虑满足 $\sum \min(B,N)\ge NK$ 这个要求。枚举第一类人的和 $i$，枚举第二类人选了 $k$ 个人。那么当 $f_{i}=1$ 且 $k\times N + i\ge NK$ 时可行。这一部分复杂度 $O(n^3)$。

然后要找到一个最小的 $j$ 使得 $j+i\ge s$ 且 $g_{k,j}=1$。设 $\text{nxt}_{k,j}$ 表示一个最小的 $t$ 使得 $t\ge j$ 且 $g_{k,t}=1$。通过 $O(n^3)$ 预处理求出。那么 $j=\text{nxt}_{k,\max(0,s-i)}$，用 $i+j$ 更新答案即可。

总时间复杂度 $O\left(\frac{n^4}{\omega}\right)$，瓶颈在第二类人的背包。[code](https://www.luogu.com.cn/paste/7fnkaiwz)

---

## 作者：DengDuck (赞：2)

非常巧妙的动态规划，我没想出来，还不是因为自己不够努力。

发现对于每道菜的限制条件很多，素质很差，所以我们考虑拆一下厨师的贡献：

- 用来满足有 $k$ 个厨师的限制，每个厨师可以给的贡献是 $\min(n,B_i)$。
- 用来满足要花费 $A_i$ 时间的限制，每个厨师可以给的贡献是 $B_i$。


然后我们发现结合一下抽屉原理，好像这俩东西都只用看整体的和来判定，素质比较高，所以我们接下来考虑类似背包的东西就行了。

注意答案要求最小化的是我们选择的 $\sum B$ 和所有的 $\sum A$ 的差，这个有点毒瘤，所以我们的状态设计应该是 $F_{i,j}$ 表示当前选到第 $i$ 项，$\sum B$ 是 $j$ 情况下最大的选中的 $\min(n,B_i)$ 之和，直接转移就做完了。

拆贡献真好玩，我也要出拆贡献题，我素质低下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
int n,m,k,A,B[N],SB,F[2][90005];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(x<k)return puts("Impossible"),0;
		A+=x;
	}
	for(int i=1;i<=m;i++)scanf("%d",&B[i]);
	memset(F,-27,sizeof(F));
	F[0][0]=0;
	for(int i=1;i<=m;i++)
	{
		int Id=i&1;
		for(int j=0;j<B[i];j++)F[Id][j]=F[Id^1][j];
		SB+=B[i];
		for(int j=B[i];j<=SB;j++)F[Id][j]=max(F[Id^1][j],F[Id^1][j-B[i]]+min(B[i],n));
	}
	for(int i=A;i<=SB;i++)
	{
		if(F[m&1][i]>=n*k)return printf("%d\n",i-A),0;
	}
	puts("Impossible");
	
}
```

---

## 作者：StayAlone (赞：1)

先判掉一个显然的无解情况：存在 $a_i<k$。

将每个菜的时间分为两份。第一份大小为 $k$，被称为基本时间。要求这 $k$ 时间恰好由不同的厨师完成。

当选择一名厨师，先让他公平地给每个菜品的基本时间贡献 $1$。若有空余时间，随便分配都不影响。我们只在意“空余时间”的和。

只要总基本时间达到 $nk$，且总时间达到 $\sum a_i$，就是一个合法的选择。


选择一个厨师，其**有能力**向基本时间贡献 $\min\{n, b_i\}$（除非超出 $nk$）。超出的部分计入空余的时间即可。

于是思路明朗了。设 $f_{i, j}$ 表示考虑前 $i$ 个厨师，总时间为 $j$，最大的基本时间和。分讨第 $i$ 个厨师选不选即可，总时间复杂度 $\mathcal O(m\sum b_i)$。答案就是 $f_{m, j}\geq nk$，且 $j\geq \sum a_i$ 的最小 $j$。

交题解时是最优解。

```cpp
int n, m, k, sa, sb, a[310], b[310], f[MAXN];

int main() {
	read(n, m, k); rer(i, 1, n, a), sa += a[i]; rer(i, 1, m, b), sb += b[i];
	rep1(i, 1, n) if (a[i] < k) return puts("Impossible"), 0;
	rep1(i, 1, sb) f[i] = -inf;
	sb = 0;
	rep1(i, 1, m) {
		sb += b[i];
		rep2(j, sb, b[i]) gmax(f[j], f[j - b[i]] + min(n, b[i]));
	}
	rep1(j, sa, sb) if (f[j] >= n * k) return printf("%d", j - sa), 0;
	puts("Impossible");
	return 0;
}
```

---

## 作者：wjyppm1403 (赞：1)

欢乐赛题所以没有更好的阅读体验，发现出来只有我一个对了炸杠了。

先判掉 $a_i<k$ 的无解情况。

然后考虑发掘性质，注意到本题目存在一个至少 $k$ 个人的去做。故我们考虑将一份菜拆成两份时间，第一份为 $k$，要求由不同厨师完成。第二个随意安排。那么方案合法只要总时间大于等于 $\sum_{i} a_i$，并且第一份总和时间满足分配后能达到 $nk$ 那么方案就是合法。

考虑 DP 这个方案，设 $f(i,j)$ 表示前 $i$ 个厨师，总时间为 $j$ 的最大第一份时间分配。若第 $i$ 个厨师选择雇佣，那么会贡献 $\min\{ n,b_i \}$，即 $f(i,j)\leftarrow f(i,j-b_i)+\min\{ n,b_i \}$。若不雇佣则为 $f(i,j)\leftarrow f(i-1,j)$。

输出答案从 $\sum a_i \to \sum b_i$ 枚举 $j$ 的时候判断一下 $nk$ 的条件即可，时间复杂度 $O(m\sum b_i)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520,MM=1e5+15;
int f[MN][MM],n,m,K,a[MN],b[MN],suma,sumb;


int main(){
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]<K){
            cout<<"Impossible\n";
            return 0;
        }
        suma+=a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    memset(f,128,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=m;i++){
        sumb+=b[i];
        for(int j=0;j<=sumb;j++){
            f[i][j]=max(f[i][j],f[i-1][j]);
            if(j-b[i]>=0) f[i][j]=max(f[i][j],f[i-1][j-b[i]]+min(n,b[i])); 
        }
    }
    for(int j=suma;j<=sumb;j++){
        if(f[m][j]>=n*K){
            cout<<j-suma;
            return 0;
        }
    }
            cout<<"Impossible\n";
    return 0;
}
```

---

