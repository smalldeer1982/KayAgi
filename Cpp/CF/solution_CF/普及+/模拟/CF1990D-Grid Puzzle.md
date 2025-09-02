# Grid Puzzle

## 题目描述

You are given an array $ a $ of size $ n $ .

There is an $ n \times n $ grid. In the $ i $ -th row, the first $ a_i $ cells are black and the other cells are white. In other words, note $ (i,j) $ as the cell in the $ i $ -th row and $ j $ -th column, cells $ (i,1), (i,2), \ldots, (i,a_i) $ are black, and cells $ (i,a_i+1), \ldots, (i,n) $ are white.

You can do the following operations any number of times in any order:

- Dye a $ 2 \times 2 $ subgrid white;
- Dye a whole row white. Note you can not dye a whole column white.

Find the minimum number of operations to dye all cells white.

## 说明/提示

In the first test case, you don't need to do any operation.

In the second test case, you can do:

- Dye $ (1,1), (1,2), (2,1) $ , and $ (2,2) $ white;
- Dye $ (2,3), (2,4), (3,3) $ , and $ (3,4) $ white;
- Dye $ (3,1), (3,2), (4,1) $ , and $ (4,2) $ white.

It can be proven $ 3 $ is the minimum number of operations.

In the third test case, you can do:

- Dye the first row white;
- Dye $ (2,1), (2,2), (3,1) $ , and $ (3,2) $ white.

It can be proven $ 2 $ is the minimum number of operations.

## 样例 #1

### 输入

```
10
1
0
4
2 4 4 2
4
3 2 1 0
3
0 3 0
3
0 1 3
3
3 1 0
4
3 1 0 3
4
0 2 2 2
6
1 3 4 2 0 4
8
2 2 5 2 3 4 2 4```

### 输出

```
0
3
2
1
2
2
3
2
4
6```

# 题解

## 作者：Muse_Dash (赞：7)

感谢这道题让我第一次挤进 CF 榜单第一页。

我们完全可以考虑从上到下完成每排的涂色，并讨论对本排使用哪种操作。

我们可以先尝试着记录每次遍历到一排时未涂的格子数量 $x$。当 $x=0$，不操作。当 $0<x\leq2$ 的时候，显然考虑 $2\times 2$ 方案（如果最优地做这个问题，在两个格子未涂的时候这两个必定是连续的），可以判断能否去除下一排的一些负担。如果 $>2$，直接覆盖本排，否则 $2\times 2$ 对后面的效益一定不比直接覆盖强。

具体地，判断 $2\times2$ 对后一排的覆盖情况时，如果这一排的最左边两个格子被上一排的 $2\times2$ 覆盖，需要打标记，因为最下面的两个格子没有再涂的必要，考虑转到第三、四个格子。


```cpp
while (T--){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read(),tmp[i]=0;
	int sum=0;
	for (int i=1;i<=n;i++){
		if (a[i]<=0) a[i]=0;
		else if (a[i]<=2){
			a[i]=0;
			if (!tmp[i-1]) a[i+1]-=2,tmp[i]=1;
			else if (tmp[i-1]&&a[i+1]==3) a[i+1]=2;
			else if (tmp[i-1]&&a[i+1]>3) a[i+1]-=2;
			sum++;
		}
		else a[i]=0,sum++;
	}
	cout<<sum<<'\n';
}
```

---

## 作者：aulive (赞：3)

# Solution
容易发现采取第一种操作时无非两种情况
1. $a_i\le2$，此时染 $2\times2$ 的方案能让下一行也染到前两列。
2. 如果上一行染色影响到了当前这一行并且 $a_i\le4$，此时染 $2\times2$ 明显更优，理由同上。

其余的情况直接染一整行即可，因为此时如果采取染 $2\times2$ 的方案至少要染两次，可以用进行两次染一整行的操作代替。

按照上面的结论简单模拟即可
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
int n,a[maxn+5],tag1[maxn+5],tag2[maxn+5]; 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test;
	cin>>test;
	while(test--){
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i],tag1[i]=tag2[i]=0;
		for(int i=1;i<=n;i++){
			if(!a[i])continue;
			if(tag1[i]&&a[i]<=2)continue;
			if(tag1[i]&&tag2[i]&&a[i]<=4)continue;
			//特判当前这一列被染完的情况 
			if(a[i]<=2){
				tag1[i]=tag1[i+1]=1;
			}else if(a[i]<=4){
				if(tag2[i])tag1[i]=tag1[i+1]=1;//后面的染了染前面 
				else if(tag1[i])tag2[i]=tag2[i+1]=1;//前面的染了染后面
			}
			ans++;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：SunsetLake (赞：2)

## 思路

首先有一个观察：对于 $a_i > 4$ 的行，一定只会用一次操作二，因为若要用操作一，那么将 $i,i + 1$ 都变白至少都需要 $3$ 次操作，用操作二只需要两次。于是我们只考虑 $a_i \le 4$ 的情况。

根据上面这个观察，我们可以知道对于两行 $i,i + 1$ 放 $2$ 个 $2 \times 2$ 和用两次操作二是等价的，于是对于放 $2$ 个 $2 \times 2$ 的行都将其换成用两次操作二。那么，每行就最多只会有 $1$ 个 $2 \times 2$ 的方格，考虑其放在那里（若存在）：一定不会在 $2$ 和 $3$ 列之间，因为每一行的黑格子是从 $1 \sim a_i$ 连续的，不能覆盖 $1$ 一定不优。故只会在 $1,2$ 或 $3,4$ 之间。记两个 `bool` 变量 $l,r$ 表示当前这一行的 $1,2 / 3,4$ 是否被 $2 \times 2$ 矩形覆盖，方便进行答案计算。

接下来分类讨论：

- $a_i = 0$，不管它，跳过。
- $l = 1$ 且 $a_i \le 2$，此时这一行已经被覆盖完，不用再操作。
- $3 \le a_i \le 4$ 时：
	- 若 $l = 1$ 或 $r = 1$，只需要在没被覆盖的那一边放上一个 $2 \times 2$ 的矩形即可，并将 $l,r$ 都取反。
	- 否则一定是用操作二将这行全覆盖。为什么？因为~~不这样写过不了样例~~根据上面的推论，在当前行放 $2 \times 2$ 是与用两个操作二等价的，还不如不用 $2 \times 2$ 的矩阵，而是给下一行更多选择机会，反正最劣也是再用一次操作二，更优的情况可能是 $i + 1$ 行放 $2 \times 2$ 省下一些步骤。
- $1 \le a_i \le 2$，放一个 $2 \times 2$ 在左边，并 $l \gets 1,r \gets 0$ 即可。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N = 2e5 + 5;
int a[N];	
int n;
void solve(){
	cin >> n;
	for(int i = 1;i <= n;++ i) cin >> a[i];
	int ans = 0;
	bool l = 0,r = 0;
	for(int i = 1;i <= n;++ i){
		if(a[i] == 0 || (l && a[i] <= 2)){
			l = r = 0;
			continue;
		}
		if(a[i] > 4){
			l = r = 0;
			++ ans;
			continue; 
		}
		if(l || r){
			++ ans;
			swap(l,r);
			continue;
		}
		if(a[i] > 2){
			++ ans;
			l = r = 0;
			continue;
		}
		++ ans;
		l = 1;r = 0;
	}
	cout << ans << endl;
}
int main(){
	int _;
	cin >> _;
	while(_ --) solve();
	return 0;
}
/*
1
4
3 2 1 0
*/

```

---

## 作者：Luzhuoyuan (赞：2)

Links: [[Codeforces]](http://codeforces.com/problemset/problem/1990/D) [[Luogu]](https://www.luogu.com.cn/problem/CF1990D)

### 题意

给定一个长为 $n$ 的非负整数序列 $a$。有一个 $n\times n$ 的方格图，其中第 $i$ 行中的靠左的 $a_i$ 个格子为黑色，其余格子为白色。你可以进行若干次以下操作之一：

- 选择图中一个 $2\times 2$ 的子矩形染成白色；
- 选择图中一行格子染成白色。

问让每个格子都变为白色至少需要多少次操作。每个测试点 $t$ 组测试用例。

- $1\le t\le 10^4$；
- $1\le n\le 2\cdot 10^5$；
- $0\le a_i\le n$；
- $\sum n\le 2\cdot 10^5$。

### 思路

看到这题首先有个很简单的想法：如果有连续的两行黑格数都小于等于 $2$，那么就染方块，否则就染一整行，因为在同一组相邻的行放两个方块显然不优于直接分别染两行。然后发现样例第二组爆炸了，因为它可以用三个方块叠成两层，比上面这个更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/2us238zm.png)

然后我们思考会不会有方块叠成更多层，可以发现如果我们要在某个行上覆盖三个方块，那么显然这样只能覆盖至多 $2$ 行的黑格，所以显然是劣于直接染两行的。同理，叠更多层显然就更劣了。因此我们最多只会用方块叠两层，并且是这样交替地叠。

![](https://cdn.luogu.com.cn/upload/image_hosting/myidpf1l.png)

然后考虑用 DP 求解。设 $f_{i,0/1/2}$ 表示填完了前 $i$ 行，第 $i$ 行 没有填方块 / 填了一个 $1,2$ 两列的方块 / 填了一个 $3,4$ 两列的方块 的最小操作次数（这里“在第 $i$ 行填方块”指的是在第 $i$ 和 $i+1$ 行和指定列填方块，下同）。考虑转移：

- 第 $i$ 行不填，那么要么是 $a_i=0$，要么是 $a_i\le 2$ 且前一行填了 $1,2$ 列。
- 第 $i$ 行填整行，那么要求前一行没有填方块（因为前一行填方块，本行填整行的方案总是不优于两行都填整行）。
- 第 $i$ 行 $1,2$ 列填方块，如果 $a_i\le 2$，那么可以 $i-1$ 行不填方块；如果 $a_i\le 4$ 那么可以 $i-1$ 行填 $3,4$ 列，第 $i$ 行插进去。
- 第 $i$ 行 $3,4$ 列填方块，如果 $a_i\le 4$，那么 $i-1$ 行填 $1,2$ 列，第 $i$ 行叠上去。

即转移如下：

- $f_{i,0}\gets f_{i-1,0}+[a_i>0]$；
- $f_{i,0}\gets f_{i-1,1},f_{i,1}\gets f_{i-1,0}+1,(a_i\le 2)$；
- $f_{i,1}\gets f_{i-1,2}+1,f_{i,2}\gets f_{i-1,1}+1,(a_i\le 4)$。

转移到 $f_{n-1}$，最后处理一下即可。复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=2e5+5,INF=1e9;
int _,n,a[N],f[N][3],ans;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>_;
	while(_--){
		cin>>n;for(int i=1;i<=n;i++)cin>>a[i],f[i][0]=f[i][1]=f[i][2]=INF;
		if(n==1){cout<<!!a[1]<<'\n';continue;}
		f[1][0]=!!a[1];if(a[1]<=2)f[1][1]=1;
		for(int i=2;i<n;i++){
			f[i][0]=f[i-1][0]+!!a[i];
			if(a[i]<=2)f[i][0]=min(f[i][0],f[i-1][1]),f[i][1]=f[i-1][0]+1;
			if(a[i]<=4)f[i][1]=min(f[i][1],f[i-1][2]+1),f[i][2]=f[i-1][1]+1;
		}
		ans=f[n-1][0]+!!a[n];if(a[n]<=2)ans=min(ans,f[n-1][1]);
		cout<<ans<<'\n';
	}
	return 0;
}
```

（逃

---

## 作者：w9095 (赞：2)

[CF1990D Grid Puzzle](https://www.luogu.com.cn/problem/CF1990D)

DP 好题。考虑分析两种操作的性质，不难发现操作 $1$ 至多只能涂白 $4$ 个方格，而操作 $2$ 可以涂白的方格取决于这一行的方格数，几乎无上限。 因此，从涂白的方格数考虑，对于黑色方格数量 $\ge5$ 的一行，我们直接使用操作 $2$ 涂白。注意黑色方格数量等于 $4$ 的一行不一定直接使用操作 $2$，因为无法比较两种操作哪个更优。

之后，考虑到剩余每行的黑色方格数很少，不会超过 $4$，考虑动态规划。不难发现每次使用操作 $1$ 左下角一定在第一列或者第三列，否则可以挪动证明一定不优。设状态 $f[i][j]$ 表示第 $i$ 行状态为 $j$ 且前 $i-1$ 行全部被覆盖的最小操作次数。若 $j=0$，表示没有任何方格被覆盖；若 $j=1$，表示第一、二行的方格被覆盖，即以这一行第一列为左下角进行一次操作 $1$；若 $j=2$，表示第三、四行的方格被覆盖，即以这一行第三列为左下角进行一次操作 $1$；若 $j=3$，表示所有方格被覆盖。初始时全为负无穷。

显然，对于黑色方格数量 $\ge5$ 的一行或本来就没有黑色方格的一行，$f[i][3]=0$。

对于其他情况，我们把每个状态分别进行转移。

$$f[i][0]=\min(f[i][0],f[i-1][3])$$

$$f[i][0]=\min(f[i][0],f[i-1][1])(a[i-1]\le2)$$

如果这一行没有任何方格被覆盖，为了满足定义前 $i-1$ 行全部被覆盖，必须选取全部被覆盖的状态，即 $f[i-1][3]$。特别的，若 $a[i-1]\le2$，状态 $f[i-1][1]$ 也是完全覆盖。

$$f[i][1]=\min(f[i][1],\min(f[i-1][3]+1,f[i-1][2]+1))$$
		       	
$$f[i][1]=\min(f[i][1],f[i-1][0]+1)(a[i-1]\le2)$$

以这一行第一列为左下角进行一次操作 $1$，则也会覆盖上一行的第一、二列。因此，可以从 $f[i-1][2]$ 的状态转移过来，这样上一行所有列都被覆盖。当然，也可以从 $f[i-1][3]$ 转移。特别的，若 $a[i-1]\le2$，从状态 $f[i-1][0]$ 转移也是完全覆盖。

$$f[i][2]=\min(f[i][2],\min(f[i-1][3]+1,f[i-1][1]+1))$$

同上，不过不需要考虑 $a[i-1]\le2$ 的情况，因为没有影响。

$$f[i][3]=\min(f[i][3],\min(f[i-1][3]+2,\min(f[i-1][2]+2,\min(f[i-1][1]+2,f[i-1][0]+2))))$$

$$f[i][3]=\min(f[i][3],f[i-1][3]+1)$$

$$f[i][3]=\min(f[i][3],f[i-1][1]+1)(a[i-1]\le2)$$

如果这一行所有方格被覆盖，那么上一行的状态可以任意选择。另外，也可以直接使用操作 $2$，同 $f[i][0]$ 的转移，此时应该选择 $f[i-1][3]$ 进行转移。特别的，若 $a[i-1]\le2$，状态 $f[i-1][1]$ 也是完全覆盖。

最后，对于每段被 $0$ 隔开的部分分别计算答案进行累加，并计算上最初操作 $2$ 的贡献，即可解决问题。时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,a[300000],f[300000][4];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long ans=0;
	   	scanf("%lld",&n);
	   	for(int i=1;i<=n;i++)
	   	    {
		    scanf("%lld",&a[i]);
		    if(a[i]>=5)ans++,a[i]=0;
		    }
		for(int i=0;i<=n;i++)
		    for(int j=0;j<=3;j++)
		        f[i][j]=1e16;
		f[0][3]=0,a[n+1]=0;
		for(int i=1;i<=n;i++)
		    if(!a[i])f[i][3]=0;
		for(int i=1;i<=n;i++)
		    if(a[i])
		       {
		       	f[i][0]=min(f[i][0],f[i-1][3]);
		       	if(a[i-1]<=2)f[i][0]=min(f[i][0],f[i-1][1]);
		       	f[i][1]=min(f[i][1],min(f[i-1][3]+1,f[i-1][2]+1));
		       	if(a[i-1]<=2)f[i][1]=min(f[i][1],f[i-1][0]+1);
		       	f[i][2]=min(f[i][2],min(f[i-1][3]+1,f[i-1][1]+1));
		       	f[i][3]=min(f[i][3],min(f[i-1][3]+2,min(f[i-1][2]+2,min(f[i-1][1]+2,f[i-1][0]+2))));
			    f[i][3]=min(f[i][3],f[i-1][3]+1);
			    if(a[i-1]<=2)f[i][3]=min(f[i][3],f[i-1][1]+1);
			   }
		for(int i=1;i<=n;i++)
		    if(a[i]!=0&&a[i+1]==0)
		       {
			   long long k=min(f[i][3],min(f[i][2]+1,min(f[i][1]+1,f[i][0]+2)));
			   if(a[i]<=2)k=min(k,f[i][1]);
			   ans+=k;
			   }
		printf("%lld\n",ans);
	   }
	return 0;
}
```

---

## 作者：luogu_gza (赞：2)

我爸让我“系统地做题”，所以我开了个 div2D，舒缓一下身心。

虽然因为数组大小和多组清空原因 +2，所以我觉得我是一发过的。

---

首先有一个结论是 $a_i \geq 5$ 就一定只能用二操作了，因为你明显会在这里至少花上三次一操作，一次可以白嫖上一行的，但是这样还是需要自己掏腰包两次操作，不划算。

得到这个结论后容易发现每次一操作只是继承了上一行，然后帮忙消了两个点。

还有结论：每次只可能操作一二两个位置或者三四两个位置，这个比较明显。

那么我们如何处理问题呢？

我们记录一个变量 `flag` 表示上一行的状态，零表示上一行没一操作，一表示上一行对一二位置做了一操作，二表示上一行对于三四位置做了一操作。

如果 $a_i=0$ 直接将 `flag=0`，跳到下一行。

如果 $1 \leq a_i \leq 2$，如果 `flag=1`，则直接跳下一行，否则就对一二位置做一次一操作，将 `flag=1`，跳到下一行。

如果 $3 \leq a_i \leq 4$，如果 `flag=1`，就对三四位置做一次一操作，将 `flag=2`，跳到下一行，如果 `flag=2`，就对一二位置做一次一操作，将 `flag=1`，跳到下一行，如果 `flag=0`，就做一次二操作，将 `flag=0`，跳到下一行。

如果 $a_i \geq 5$，那么直接做一次二操作，将 `flag=0`，跳到下一行。

[code](https://codeforces.com/contest/1990/submission/271720555)。

---

## 作者：I_will_AKIOI (赞：2)

首先当 $a_i>4$ 时，肯定是直接把一整行变为白色更优。所以只考虑 $a_i\le4$ 的情况。

接着由于一个 $2\times2$ 的矩阵，可以染前两列或后两列，所以我们分开考虑。使用两个变量 $x,y$，分别记录上一行有没有在这两列用矩阵。

首先若 $a_i=0$，那么不需要染色，直接跳过，同时把 $x,y$ 赋值为 $0$。

若当前 $x=y=0$，$a_i\le2$ 就直接用一个矩阵，不然直接用操作二染白一整行。

否则如果 $x=1$，$a_i\le2$ 的话就已经为我们染好了，就不需要多余的步数。否则就在三四列用一个矩阵。

若 $y=1$，那么前两列肯定是染不到的，所以在一二列用一个矩阵给他染一下。

于是这么大力分讨完之后，答案就出来了。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int n,a[200005];
vector<int>v;
void solve()
{
  int ans=0,x=0,y=0;
  v.clear();
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i];
  for(int i=1;i<=n;i++) if(a[i]>4) a[i]=0,ans++;
  for(int i=1;i<=n;i++)
  {
    if(a[i]==0)
    {
      x=y=0;
      continue;
    }
    if(x==0&&y==0)
    {
      ans++;
      if(a[i]<=2) x=1;
    }
    else if(x==1)
    {
      x=0;
      if(a[i]>2) ans++,y=1;
    }
    else
    {
      ans++;
      x=1,y=0;
    }
  }
  cout<<ans<<"\n";
  return;
}
int main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：TTpandaS (赞：1)

首先可以发现如果一行长度大于 $4$，那么一定是直接涂这一行最优，因为就算进行一操作也需要与别的行一起进行至少 $3$ 次，不如直接与别的行一起直接涂。

观察可以让答案减少的图案，一定是首先有一个长度小于等于 $2$ 的行与下一行一起用以操作涂，接着下面长度小于等于 $4$ 的行依次与下一个用一操作涂色，最后由一个长度小于等于 $2$ 的行收尾。

因此可以先处理出长度小于等于 $2$ 的行，再判断中间的行是否都长度小于等于 $4$ 且总数为偶数。答案先是非空行的数量，每判断成功一次则答案减一即可。

---

## 作者：Alex_Wei (赞：1)

### [CF1990D Grid Puzzle](https://www.luogu.com.cn/problem/CF1990D)

对于 $a_i > 4$，如果不使用操作 $2$，那么至少需要 $3$ 次操作 $1$，不优于对 $i - 1, i, i + 1$ 使用操作 $2$。

如果操作 $1$ 覆盖第 $2, 3$ 列，那么将其移动到第 $3, 4$ 列不影响构造的合法性。

设 $f_{i, 0 / 1, 0 / 1}$ 表示当前考虑到第 $i$ 行，是否覆盖第 $i, i + 1$ 行的第 $1, 2$ 列，是否覆盖第 $i, i + 1$ 行的第 $3, 4$ 列时的最小代价。$f_{i - 1, j, k}\to f_{i, j', k'}$ 的转移的贡献：$j' + k' + c$，其中若第 $i$ 行没有被操作 $1$ 完全覆盖则 $c = 1$，否则 $c = 0$。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1990/submission/271862154)。

---

## 作者：Guchenxi0971 (赞：0)

## Sol

由于是消除 $2\times 2$ 的格子，那么构建数组 $b$ 使 $b_i=\lceil\frac{a_i}{2}\rceil$。我们可以发现对于 $b=\{1,2,2,1\}$ 时只需要 $3$ 次，对于 $b=\{1,2,2,2,2,1\}$ 就只需要 $5$ 次，然而对于存在 $b_i>2$ 时你选择第二种操作是不劣于使用若干一操作的。那么大胆猜测只要在两个 $1$ 中间夹了偶数个小于 $1$ 的值时对于答案的贡献会减一。实践证明这是对的，有人会问了：对于 $b=\{3,4,4,4,4,3\}$ 能否减少贡献呢？事实上这是不行的，因为你如果要将这个序列转化为 $b=\{1,2,2,2,2,1\}$ 这种序列时要使用 $\frac{n}{2}$ 次操作，但是最后只会减少 $1$ 次操作，得不偿失。但是需要注意的是 $d$ 对于 $b=\{1,2,2,1,2,2,1\}$ 这种序列只会减少一次贡献，意思就是说一个 $1$ 最多在一个序列中。

## Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e9+10;



inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

int a[Max],b[Max];

void work(){
	int n=read();
	int pos=n;
	for(int i=1;i<=n;++i){
		a[i]=raed();
		if(!a[i])pos--; 
		//去除0的贡献 
		b[i]=ceil(a[i]*1.0/2);
		//计算b 
	}
	int l=0;
	for(int i=1;i<=n;++i){
		if(b[i]==1){
			if(l!=0){
				if((i-l-1)%2==0)pos--,l=0;
				else l=i;
			}else l=i;
		}else{
			if(b[i]!=2)l=0;
		}
	}
	cout << pos << "\n";
}


signed main(){
	int T=read() ;
	while(T--)work();

	return 0;
}

```

---

## 作者：eastcloud (赞：0)

不动脑子做法：发现当某一行需要被涂掉的方块太多时，一行涂掉比涂 $2 \times 2$ 方格肯定优，于是每一行上方能传递下来的长度比较有限，你大眼观察随便取一个阈值状压 dp 就做完了，转移是容易的因为肯定贪心放，我赛时怕挂取的 8，再小一点也是可以的。


```
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9')f=(ch=='-'?-1:1),ch=getchar();
	while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x/10)write(x/10);
	putchar(x%10+'0');
}
int f[N][(1<<8)],val[9][(1<<9)],st[9][(1<<9)];
int a[N];
void solve(){
	int n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int lasmin=0;
	for(int i=0;i<=n;i++)for(int j=0;j<(1<<8);j++)f[i][j]=0x3f3f3f3f;
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		if(a[i]>8){
			f[i][0]=lasmin+1;lasmin++;continue;
		}
		int T=(1<<a[i])-1;
		f[i][0]=min(f[i][0],lasmin+1);lasmin=f[i][0];
		
		for(int S=0;S<(1<<8);S++){
			T=(1<<a[i])-1;
			if(f[i-1][S]==0x3f3f3f3f)continue;
			T=S&T;
			if(st[a[i]][T]>=(1<<8))continue;
			f[i][st[a[i]][T]]=min(f[i][st[a[i]][T]],f[i-1][S]+val[a[i]][T]);
			lasmin=min(lasmin,f[i][st[a[i]][T]]);
		}
	}
	write(lasmin);putchar('\n');
}
int main(){
	for(int i=1;i<=8;i++)for(int S=0;S<(1<<8);S++){
		int T=0;
		for(int j=0;j<i;j++){
			if(!(S&(1<<j)) && !(T&(1<<j))){
				val[i][S]++;T|=(1<<j);T|=(1<<(j+1));
			}
		}
		st[i][S]=T;
	}
	int T=read();while(T--)solve();
}
```

---

## 作者：EricWan (赞：0)

## 结论

当 $a_i>4$ 时，就不会使用操作 1 了

## 证明

考虑反正：假设 $a_i>4$，我们不使用操作二，只使用操作一，那么我们一共需要至少 $3$ 次操作，这 $3$ 次操作最多只会影响到当前行和相邻的两行，我们使用操作二操作这 $3$ 行是严格优于使用至少 $3$ 次的操作一。

注：第一次没写这个部分，被打回了，看来交洛谷题解不能糊弄过关啊。

## 实现方法

我们考虑状压 dp。

设置 dp 状态为：$dp_{i,j}$ 代表已经把前 $i$ 行刷白还可以帮助第 $i+1$ 行把 $y$ 坐标所对应的二进制位在 $j$ 中是 $1$ 的位置刷白的最小操作数。

转移方程见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int countbit(int x) {
	int ans = 0;
	while (x) {
		ans += (x & 1);
		x >>= 1;
	}
	return ans;
}
int T, n, a[200005], dp[200005][17], minn[200005];
int getmin(int k) {
	int ans = 10000000;
	for (int i = 0; i <= 15; i++) {
		if ((i | ((1 << a[i]) - 1)) == i) {
			ans = min(ans, dp[k][i]);
		}
	}
	return ans;
}
signed main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			for (int j = 0; j < 16; j++) {
				dp[i][j] = n;
			}
		}
		for (int j = 0; j < 16; j++) {
			dp[0][j] = n;
		}
		dp[0][0] = 0;
		for (int i = 1; i <= n; i++) {
			minn[i - 1] = getmin(i - 1);
			dp[i][0] = min(dp[i][0], minn[i - 1] + 1); // 在刷这一行时使用大招
			if (a[i] <= 4) { // 判断是否可以不使用大招
				for (int j = 0; j <= 15; j++) { // 枚举使用小招的位置（左上角）
					if (j & (j << 1)) continue; // 如果重叠，说明不是最优方案
					if ((j | (j << 1)) > 15) continue; // 如果刷到了第 5 列，说明不是最优方案
					for (int k = 0; k <= 15; k++) { // 枚举上一行给这一行的帮助
						if (((k | j | (j << 1)) | ((1 << a[i]) - 1)) == (k | j | (j << 1))) { // 如果自己加上帮助可以满足自己的要求
							dp[i][j | (j << 1)] = min(dp[i][j | (j << 1)], dp[i - 1][k] + countbit(j)); // 更新答案
						}
					}
				}
			}
		}
		cout << getmin(n) << endl;
	}
	return 0;
}
```

---

