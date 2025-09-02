# 「Diligent-OI R1 D」DlgtTemplate

## 题目背景

棋盘是用板子做成的。这题是棋盘的题，所以……

## 题目描述

有一个 $1$ 行 $n$ 个格子的棋盘编号 $1\sim n$，上面每个格子写着一个得分 $a_i$。

现在你需要**从左到右**依次地选择一些格子，可以不选。有些格子选了之后，会将当前选的最靠前的 $b_i$ 个格子清除为未选格子，但你**不能**回去把这些格子重新选上。特殊地，如果该格子之前的已选格子不到 $b_i$ 个，那么该格子以及该格子以后的格子**不会**被清除为未选格子。

请你找出一种从左到右选择的方案，使得已选格子的得分之和最大。

## 说明/提示

#### 【样例 #1 解释】

先选择第一个数 $1$，这时虽然 $b_1=1$，但是因为前面没有数，所以不会清除。

再选择第二个数 $1$，这时因为 $b_2=0$，所以不会清除。

再选择第三个数 $4$，这时因为 $b_3=0$，所以不会清除。

再选择第四个数 $5$，这时因为 $b_4=2$，所以选择的第一个数和第二个数会被清除为未选的数。

此时答案 $4+5=9$。方法不唯一。

#### 【数据范围与约定】

对于 $100\%$ 的数据，满足 $1\le n\le3000$，$|a_i|\le10^8$，$0\le b_i\le n$。

| Subtask 编号 | $n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $20$ | 无 | $25$ |
| $1$ | $500$ | 无 | $20$ |
| $2$ | $3000$ | $b_i>0$ | $5$ |
| $3$ | $3000$ | $b_i=0$ | $5$ |
| $4$ | $3000$ | $a_i=1$ | $15$ |
| $5$ | $3000$ | 无 | $30$ |

## 样例 #1

### 输入

```
6
1 1 4 5 1 4
1 0 0 2 1 1```

### 输出

```
4
1 2 3 4
9```

## 样例 #2

### 输入

```
13
-1 1 4 -5 -1 -4 1 9 -1 9 -8 -1 0
1 0 2 1 3 0 0 2 0 0 2 0 1```

### 输出

```
5
1 2 7 8 10 
19```

## 样例 #3

### 输入

```
3
-1 -1 0
0 1 2```

### 输出

```
0

0```

## 样例 #4

### 输入

```
6
1 1 4 5 1 4
1 1 1 3 0 1```

### 输出

```
2
4 5
6```

# 题解

## 作者：Night_sea_64 (赞：17)

出题人题解。

一看就是某些 dp 题的样子。

但是发现好像不能直接 dp。你有可能会删掉之前已经选过的格子，这样的话得记录前面所有格子，行不通。

不如换个角度，dp 的内容是确定被选（即不会被删掉）的格子，然后对于每个状态，找出所有已选格子前面的格子能不能凑齐删掉的数量。这样的话倒着做更方便。影响我们最后检查的因素有最左边的已选格子编号和一共删掉的格子数量。删掉的格子数量显然不能 $>n$，所以这个只需 $O(n^2)$ 的时间和空间复杂度。

设最左边已选格子编号为 $i$，一共删掉 $j$ 个格子。检查的时候找 $1\sim(i-1)$ 这些格子中能不能有 $j$ 个格子够删。这就只需要让我们选择尽量多的格子不需要考虑权值了，相当于 Sub4。

这里我们给个定义，将 $b_i>0$ 的格子称为「坏格」，$b_i=0$ 的格子称为「好格」。特殊地，第一个格子也是「好格」。

显然选择一个坏格不会让总共选择的格子个数更多，所以在选择一些格子来凑齐后面的删除时，干脆不选坏格。于是检查时只需看 $1\sim(i-1)$ 中有多少个好格。

为什么第一个格子也是好格？因为选择第一个格子，即使这个格子的 $b_i$ 特别大，也不会真的删掉。所以第一个格子选了肯定不亏。后面的 $b_i>0$ 的格子因为选了第一个格子就不会再逃过删除，所以是坏格。

看起来这题就很简单了，但是你很容易能发现上面这种方法有个问题，有时候他也并不会删掉所有理论上应该删掉的格子，当且仅当前面没有那么多已选格子够你删。最后一个样例就是这样。其实稍加思考，这种情况下只可能是最左边的已选格子 $i$ 逃过了一些删除，后面再选的格子如果是坏格，就把 $i$ 给删了，不符合我们的预期。所以 $i$ 后面的已选格子都必须是好格，那只需枚举 $i$ 并选择 $i$ 后面权值 $>0$ 的好格就好了。

综上所述这题是两个情况。一种是所有坏格带来的删除都做到了。另一种是最左边的已选格子的删除没有做到，后面都是好格。分别 dp 和贪心。

下面注释中惩罚就是坏格带来的删除。代码是在写题解之前一段时间写的，所以有些说法不一样。

```cpp
//f[i][j] 表示第 n~i 个格子，一共删除掉 j 个格子的答案。j>n 时不考虑
//定义惩罚为清除之前选的格子。之前选的格子不选有惩罚的，这样不会使答案更优。下标为 1 视为无惩罚
//情况 1：正常情况，所有选定格子的惩罚都做到了
//情况 2：前面选不出那么多能删掉的格子，但是可以选定的第一个有惩罚，后面的都没有，这样就不用执行惩罚
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,a[3010],b[3010],f[3010][3010],last[3010][3010];
int s[3010],pos[3010],cur;
int ans1,ansi1,ansj1,k1,list1[3010];
int ans2,sum,ansi2,k2,list2[3010];
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
        if(i==1)b[i]=0;
        s[i]=s[i-1]+(b[i]==0);
        if(!b[i])pos[++cur]=i;
    }
    //情况 1 dp 求解
    for(int i=n;i>=1;i--)
    {
        //不选该格
        for(int j=0;j<=n;j++)
            f[i][j]=f[i+1][j],last[i][j]=0;
        //选该格
        for(int j=b[i];j<=n;j++)
            if(f[i+1][j-b[i]]+a[i]>f[i][j])
                f[i][j]=f[i+1][j-b[i]]+a[i],last[i][j]=1;
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<=n;j++)
            if(s[i-1]>=j&&f[i][j]>ans1)
                ans1=f[i][j],ansi1=i,ansj1=j;
    //情况 2 贪心求解
    for(int i=n;i>=1;i--)
        if(!b[i])
        {
            if(a[i]>0)sum+=a[i];
        }
        else
        {
            if(sum+a[i]>ans2)ans2=sum+a[i],ansi2=i;
        }
    if(ans1>ans2)
    {
        for(int i=1;i<=cur;i++)
            if(pos[i]<ansi1)list1[++k1]=pos[i];
            else break;
        int nowj=ansj1;
        for(int i=ansi1;i<=n;i++)
            if(last[i][nowj])list1[++k1]=i,nowj-=b[i];
        cout<<k1<<endl;
        for(int i=1;i<=k1;i++)cout<<list1[i]<<" ";cout<<endl;
        cout<<ans1<<endl;
    }
    else
    {
        for(int i=1;i<=n;i++)
            if(i==ansi2||(i>ansi2&&!b[i]&&a[i]>0))list2[++k2]=i;
        cout<<k2<<endl;
        for(int i=1;i<=k2;i++)cout<<list2[i]<<" ";cout<<endl;
        cout<<ans2<<endl;
    }
    return 0;
}
```

---

## 作者：zzzz1234567 (赞：14)

# P11274 「Diligent-OI R1 D」DlgtTemplate

一道比较有意思的背包题目，赛时花了点时间才想明白。

---

## Subtask 0

枚举每个格子选或不选，时间复杂度 $O(2^n)$。

## Subtask 2

稍微模拟一下会发现，$b_i$ 总是大于零会导致我们每次添加一个格子的时候都至少会删除前一个格子，相当于我们已选定的格子永远只有一个，枚举即可。

## Subtask 3

由于 $b_i$ 总是等于零，每个格子加进去都不会对之前选定的数有任何影响，所以所有 $b_i$ 非零的格子的 $a_i$ 加起来就是答案。

## Subtask 4

所谓的 $a_i = 1$ 实际意义是所有格子的贡献都一样，我们只需要找一个不被清除格子最多的方案，除了第一个格子之外，所有 $b_i$ 非零的格子一定会没有贡献（仅当 $b_i=1$）或者造成负贡献（仅当 $b_i>1$）。因此我们选第一个格子和所有 $b_i$ 为零的格子即可。

---

以上做法都是我根据赛时正解的思路口胡的，因此没有代码，也没有 Subtask 1 的 $O(n^3)$ 做法，不便处请谅解，接下来我们讲正解：

## Subtask 5 (正解)

通过对上面部分分的思考和我们对样例的进一步观摩，我们会发现以下性质：

1. 最终选定的格子中，可以分成前后两部分，前半部分不对答案作出贡献，仅用于被后半部分格子的 $b_i$ 清除，后半部分清除前半部分后对答案造成贡献。
2. 这前半部分和后半部分是有序的，也就是说我们可以在答案中找一个分界点 $i$，在 $i$ 之前的格子选择部分加入前半，之后的格子选择部分加入后半。

有了这个性质，我们就可以把本问题分成两个子问题，一个是找出对于每个分界点，前面最多可以找到多少个用来被清除的格子。另一个是找出对于每个分界点后面，清除一定的数可以得到的最大贡献。

前半问题由于选中的格子最终都会用来被删除，相当于这些格子不对答案造成贡献，只需要选最多格子就行，是不是很像 Subtask 4？实际上也确实是这个做法，选择第一个格子和分界点之前所有 $b_i$ 为零的格子，记 $c_i$ 为分界点为 $i$ 时前半部分的最多选中格子的数量。代码如下：

```cpp
for(int i=2;i<=n;++i){
	c[i]=c[i-1]+(b[i]==0);
}
```

后半问题就变成了一个经典的背包问题，每个格子价值为 $a_i$，代价为 $b_i$，设 $dp_{i,j}$ 为选择 $i \sim n$ 的格子，总共消耗 $j$ 的代价时能得到的最大价值，十分原汁原味的 01 背包，代码如下：

```cpp
for(int i=n;i;i--){
  for(int j=0;j<=n;++j){
    dp[i][j]=dp[i+1][j];
  }
  for(int j=b[i];j<=n;++j){
    dp[i][j]=max(dp[i+1][j],dp[i+1][j-b[i]]+a[i]);
  }
}
```

注意这个背包不需要优化空间复杂度，因为计算答案和找方案时要用到，因此也不需要倒序枚举 $j$。

这时候你会发现还不能完全地解决本题的各种问题，因为题面里有这样一句话：

> 特殊地，如果该格子之前的已选格子不到 $b_i$ 个，那么该格子以及该格子以后的格子不会被清除为未选格子。

仔细咀嚼这句话，发现这个情况发生意味着当后半部分的一个格子需要的代价大于前半部分此时有的格子时，我们仍然可以强行选入该格子，这需要以下条件：

1. 这个格子一定是后半部分的第一个格子，否则后半部分在他前面选中的格子应当被他清除。这也意味着发生这个情况的格子有且只有一个。
2. 这个格子之后选中的格子一定是 $b_i = 0$ 的格子，因为前半部分已经没有格子能够再被消除。
3. 这个情况发生代表我们前半部分选几个数都无所谓，所以直接不用考虑前半部分选数的数量了。

综合上述条件，设 $g_i$ 为第 $i$ 个数触发该条件能得到的最大收益，代码如下：

```cpp
g[i]=dp[i+1][0]+a[i];
```

到这里这道题就差不多了，在所有满足 $j\le c_{i-1}$ 的 $dp_{i,j}$ 和所有 $g_i$ 中找最大值就是答案，答案有 40 分。至于方案，前半部分直接输出就好，后半部分写一个 dfs 找回背包的转移过程。这部分不是重点，看代码就行了，整道题的时间复杂度瓶颈在背包，有 $O(n^2)$ 的复杂度，其他部分都是 $O(n)$ 的。

整体代码如下，在赛时代码的基础上重构了一下增加可读性，写有部分注释，应该够清楚了：

```cpp
#include<bits/stdc++.h>//zzzz1234567 
using namespace std;
#define int long long//不开long long见祖宗，这导致我赛时白给了两发 
const int N=3e3+5;
int read(){//快读 
	int num=0,typ=1,c=getchar();
	while('0'>c||c>'9'){
		if(c=='-') typ=-1;
		c=getchar(); 
	}while('0'<=c&&c<='9'){
		num=num*10+c-48;
		c=getchar();
	}return num*typ;
}
int n,ans,a[N],b[N],c[N],dp[N][N],g[N],out[N],cnt;
void dfs(int i,int j,int res){//dfs用于找方案 
	if(i==n+1&&j==0) return;//搜索边界 
	if(res==dp[i+1][j]) dfs(i+1,j,res);//这个格子没有造成贡献 
	else{
		out[++cnt]=i;//计入方案 
		if(j==0) dfs(i+1,0,dp[i+1][0]);//g[i]或dp[i][0]造成贡献 
		else dfs(i+1,j-b[i],dp[i+1][j-b[i]]);//dp[i][j]造成贡献 
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
	}
	for(int i=1;i<=n;++i){
		b[i]=read();
	}
	c[1]=1;
	for(int i=2;i<=n;++i){//计算c
		c[i]=c[i-1]+(b[i]==0);
	}
	memset(dp,-0x3f,sizeof dp);//计算dp
	dp[n+1][0]=0;
	for(int i=n;i;i--){ 
		for(int j=0;j<=n;++j){
			dp[i][j]=dp[i+1][j];
		}
		for(int j=b[i];j<=n;++j){
			dp[i][j]=max(dp[i+1][j],dp[i+1][j-b[i]]+a[i]);
		}
		g[i]=dp[i+1][0]+a[i];//顺便处理g 
	}
	int res1=n+1,res2=0;//确定方案起点 
	for(int i=1;i<=n;++i){//找答案 
		for(int j=0;j<=c[i-1];++j){
			if(dp[i][j]>ans){
				ans=dp[i][j];
				res1=i;res2=j;
			}
		}
		if(g[i]>ans){
			ans=g[i];
			res1=i,res2=0;
		}
	}
	dfs(res1,res2,ans);//找方案 
	printf("%lld\n",res2+cnt);//res2为前半部分格子数量，cnt为后半部分格子数量 
	if(res2){//输出前半部分方案 
		printf("1 ");res2--;
	}
	for(int i=2;i<=n&&res2;++i){
		if(b[i]==0){
			printf("%lld ",i);
			res2--;
		}
	}
	for(int i=1;i<=cnt;++i){//输出后半部分方案 
		printf("%lld ",out[i]);
	}putchar('\n');
	printf("%lld\n",ans);//输出答案 
	return 0;
}
```

---

## 作者：consequence (赞：7)

# P11274题解 
## 思路 

### 第一问

考虑动态规划。

直接从头开始做比较麻烦，当我们新选一个格子的时候会对之前的答案有影响。这时候我们不妨从后往前递推，显然后面的格子对前面的影响就在于需要清除的格子的个数，想到以 $dp_{i,j}$ 表示考虑 $i \sim n$ 个格子，需要前面清除 $j$ 个格子时的答案。

设 $pre_{i,0}$ 表示考虑前 $i$ 个格子（不取第 $i$ 个格子）最多能取多少个格子，$pre_{i,1}$ 表示取第 $i$ 个格子最多能取多少个格子。显然有转移:

$\begin{cases} pre_{i,0} = \max(pre_{i-1,0},pre_{i-1,1}) \\
pre_{i,1} = \max(pre_{i,0} - b_i + 1,1) \end{cases}$

那么对于 $dp_{i,j}$ 有转移：
$$ dp_{i,j} \gets \begin{cases}  \max(dp_{i,j}, dp_{i + 1,j}) & j - b_i \ge pre_{i,1} \bigcup j < b_i \\ \max(dp_{i+1,j}, dp_{i+1,j-b_i} + a_i) &  j - b_i < pre_{i,1} \bigcap j \ge b_i \end{cases} $$ 
同时注意到，本题有一种极为特殊的情况，即在前面取的格子不够清除的时候可以不清除，也就是对于从后往前最后一个取的格子，如果之前取的格子都满足 $b_i = 0$，可以不合法（即前面的格子不够删的）。实际上，从后往前最后一个取就意味着无法通过这个状态转移到其他状态，对于这种状态的更新就可以放在这个格子的所有状态都往前转移了之后。这也就避免了[官方题解](https://www.luogu.com/article/dclkkj7q)中对于这种情况用贪心单独考虑。

同样基于上述的特殊情况，$b_1$ 的值是什么都不会影响答案，不妨令 $b_1 = 0$。

最后答案就是 $\max\limits_{j = 0} ^ n dp_{1,j}$。

时间复杂度 $O(n^2)$。

### 第二问

对于没有被清除的格子，显然很好考虑，只需要从结果倒推回去即可。同时我们记录最后答案的状态 $f$。

当 $f = 0$ 时或答案是由特殊情况得到的时，显然无需有方格被清除。

而当有方格需要被清除时，被清除的格子的价值我们显然无需考虑（都是 $0$，因为都会被清除），我们只需要考虑怎么凑出来 $f$ 个没被删除格子。那么显然只有都取 $b_i = 0$ 的格子可以把这堆格子保留（已经令 $b_1 = 0$ 所以不用考虑特殊情况），也就是只需要把前 $f$ 个 $b_i = 0$ 的格子取走。

## AC代码


```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e3 + 10;
long long dp[MAXN][MAXN];
long long a[MAXN];
long long ans;
bool flag[MAXN];
int b[MAXN], pre[MAXN][2 + 2];
int n, f, ff, nf;
vector<int> v;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    b[1] = 0;
    for (int i = 1; i <= n; ++i) {
        pre[i][0] = max(pre[i - 1][0], pre[i - 1][1]);
        pre[i][1] = max(pre[i][0] - b[i] + 1, 1);
    }
    for (int i = n; i >= 1; i--) {
        for (int j = n; j >= 0; j--) {
            if (j - b[i] >= pre[i][1] || j < b[i]) dp[i][j] = max(dp[i][j], dp[i + 1][j]);
            else dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - b[i]] + a[i]);
        }
        dp[i + 1][b[i + 1]] = max(dp[i + 1][b[i + 1]], dp[i + 2][0] + a[i + 1]);//特殊情况
    }
    for (int i = n; i >= 1; i--) {
        for (int j = n; j >= 0; j--) {
            if (i == 1 && dp[i][j] < dp[i + 1][j]) flag[j] = true;//判断是否由特殊情况转移得到
            dp[i][j] = max(dp[i][j], dp[i + 1][j]);
        }
    }
    for (int i = 0; i <= n; ++i) {
        if (dp[1][i] > ans) {
            ans = dp[1][i];
            f = i;
        }
    }
    ff = f;
    nf = f;
    if (!ans) {
        cout << "0\n\n0\n";
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        if (f < b[i]) continue;
        if (!flag[ff] && f == ff && nf && !b[i]) {
            v.push_back(i);
            nf--;
        }
        if (dp[i + 1][f - b[i]] + a[i] == dp[i][f]) {
            f -= b[i];
            v.push_back(i);
        }
    }
    cout << v.size() << "\n";
    for (auto i : v) cout << i << ' ';
    cout << "\n" << ans << "\n";
    return 0;
}
```

---

## 作者：封禁用户 (赞：6)

## 思路

>棋盘是用板子做成的。这题是棋盘的题，所以……

所以提供一种背包的思路。

先简单 dp 一下求出前 $i$ 个数里最多选几个数，存在 $dp[i]$ 中。

然后就可以开始第二次 dp 找答案了。

状态：$f[i][j]$ 表示前 $i$ 个数中选 $j$ 个数（当然是合法的选择方法下）的最大可能得分。

把每个格子的得分看作价值；把选后删除前面的点数看作体积；把前 $i$ 个数里最多可以选的数看作当前点可以使用的最大容量（统计答案时使用）。

然后就转化成了 01 背包板子力，当然转移到 $f[i][dp[j]]$ 的时候就得把当前所选的点一起从上一个状态转移过来。

## code

谁说题解一定要有代码的?

---

## 作者：Reserved_ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/P11274)

# 思路

因为看着很 dp，所以往 dp 想。

然后就发现从前向后 dp 的后效性很大。

设 $f_{i,j}$ 表示 $[i,n]$ 中选出的需要把前面所选的 $j$ 个元素的最大值。

$f_{i,j} \leftarrow \max(f_{i+1,j-b_i}+a_i,f_{i,j})$。就很没有后效性。

于是我就开始犯错了。

首先，设 $psz_i$ 表示 $[1,i]$ 中 $b_i=0$ 的个数。

显然对于 $f_{i,j}$ ，仅当 $psz_{i-1} \ge j$ 时能取到。否则要删去的数会大于 $j$。而我首先想的是 $j<i$ 即可。

其次，我过不了样例 $4$ 在神秘力量的帮助下，我发现，我题目看少了。题目的有很特殊的地方。

最左边某些点会在逃过删除，而很显然逃过删除的只能是最左边的点。枚举该点，设下标为 $i$ 则 $i$ 后面选择的点的 $b_i$ 只能等于 $0$ 否则 $i$ 会被删。

于是就可以得出答案了。

因为算法是 $\mathcal{O}(n^2)$ 的，所以求方案很好求。

---

## 作者：伊地知虹夏 (赞：4)

好题，但是输出方案有点令人反感。

这个删除操作有些讨厌，我们不妨考虑最后留下的数，设这些数的位置按顺序为 $p_1, p_2, \cdots, p_s$，被删除的数的位置按顺序为 $q_1, q_2, \cdots, q_t$。容易发现 $q_t < p_1$，并且我们只关心 $t$ 而并不关心具体的位置在哪。一个保留方案合法当且仅当 $\sum_{i=1}^{s} b_{p_i} \le t$，价值为 $\sum_{i=1}^{s} a_{p_i}$，这是一个 0/1 背包的形式。

我们称好点为满足 $b_i = 0$ 的点，特别的， $1$ 也是好点。我们考虑枚举分界点 $i$，此时的 $t_{\max}$ 就是 $[1, i]$ 中好点个数。那我们从后往前做背包即可求出答案，细节还是有的，详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3005;
typedef long long LL;
int n, a[N], b[N], c[N];
bool p[N][N];
LL f[N], ans, k, m, pos = -1, flg;
signed main() {
  cin >> n;
  for (int i = 1; i <= n; cin >> a[i ++]);
  for (int i = 1; i <= n; cin >> b[i ++]);
  c[1] = 1;
  for (int i = 2; i <= n; i ++) c[i] = c[i - 1] + (b[i] == 0);
  for (int i = 0; i <= n; i ++) p[n + 1][i] = n + 1;
  for (int i = 1; i <= n; i ++) f[i] = -1e18;
  for (int i = n; i; i --) {
    LL val = f[0] + a[i];
    if (val > ans) ans = val, pos = i, flg = 0;
    for (int j = 0; j <= c[i]; j ++)
      if (f[j] > ans) ans = f[j], pos = i, m = j, flg = 1;
    for (int j = n; j >= b[i]; j --)
      if (f[j - b[i]] + a[i] <= f[j]) p[i][j] = 0;
      else f[j] = f[j - b[i]] + a[i], p[i][j] = 1;
  }
  vector<int> item;
  if (pos == -1) return cout << "0\n\n0", 0;
  if (flg == 0) {
    item.push_back(pos);
    for (int i = pos + 1; i <= n; i ++)
      if (b[i] == 0 && a[i] > 0) item.push_back(i);
  } else {
    int cnt = m;
    for (int i = 1; i <= pos; i ++)
      if (b[i] == 0 || i == 1) 
        if (cnt > 0) item.push_back(i), -- cnt;
    // cerr << m << ' ' << pos << ' ';
    for (int i = pos + 1; i <= n; i ++) 
      if (p[i][m]) m -= b[i], item.push_back(i);
  }
  cout << item.size() << '\n';
  for (auto x : item) cout << x << ' ';
  cout << '\n' << ans;
}
```

---

## 作者：Melo_qwq (赞：3)

极好的一道题，感觉不管是想法还是输出都非常聪明。盛赞 DlgtOI。

没场切，写了大分讨拿了一半。

先讲部分分，但是好像（至少我的做法是这样）对正解没有什么导向效果。

为了使叙述更加方便，我们定义 $b_i=0$ 的位置为好的，反之则是坏的，特别的，第一个位置无论如何都是好的，因为它无论如何都不会删掉任何数。

### Sub $0$

留给会爆搜和模拟的人。

### Sub $2$

结论：如果除了第一个位置都是坏的的话，那么我们最后至多只能留下一个数。

证明：当我们选了第二个数的时候，它一定会把第一个删了，同理，在选第三个的时候，第二个也一定被它删了，那么，当我们选了第 $i$ 个数的时候，第 $[1,i-1]$ 个数肯定都被删去了，得证。

那么找到最大值输出即可，**注意和 $0$ 比较。**

### Sub $3$

选一个数不会对之前的有任何影响，所以直接把所有正数全选上即可，千万要注意和 $0$ 比较啊。

### Sub $4$

这个时候如果选择一个 $b_i>0$ 的数显然是不优的，所以选所有 $b_i=0$ 的位置即可，但是注意第一个位置是一定可以选的。

## 正解

考虑一个合法答案的形式，一定是形如删除的数全在前面，留下的全在后面的形式，我们不妨设被删除的数的集合是 $Q$，留下的集合是 $P$。

合法的要求那么是：$|Q|\ge\displaystyle\sum_{i\in P}b_i$，即一定有数够删。

考虑如果 $Q$ 中有一个坏的位置的话，它不会对答案产生任何有益贡献，同 Sub $4$。那么我们可以让 $Q$ 中全是好的，一定不劣。


注意到 $P$ 是以一种类似于后缀的形式存在，可以考虑看最左边的选取的数的位置 $j$，合法的条件转化为：$sum\ge\displaystyle\sum_{i\in P}b_i$，其中 $sum$ 是 $[1,j-1]$ 中好的个数，可以利用前缀和。

由于是类似于后缀的，考虑倒序做一个背包即可，$dp_{i,j}$ 表示位置 $[i,n]$ 这个区间里留下了一些数，需要删 $j$ 个数的最大收益。

但是我们上述的方案一定是合法的必要条件吗？

不一定，那么考虑 $|Q|<\displaystyle\sum_{i\in P}b_i$ 时何时依然合法，那么一定是位置 $j$ 是坏的，它后面选取的数是好的。可以用反证法证明之，如果之后出现了一个坏位置，那么位置 $j$ 一定被删除，与我们的条件不符。

啊？你说要是 $j$ 也是好的怎么办？那它一定在第一种情况中被算到了。

上面这个可以用贪心来解决。

其他的实现细节看代码。


```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ; i <= (n) ; i += (x))
#define antif(i ,m ,n ,x) for (int i = (m) ; i >= (n) ; i -= (x))
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ; char ch = getchar () ;
	while (! isdigit (ch)) 
	{ flag = ch == '-' ; ch = getchar () ;}
	while (isdigit (ch)) 
	{ x = (x << 1) + (x << 3) + (ch ^ 48) ; ch = getchar () ;}
	flag ? x = - x : 0 ;
}
using ll = long long ; const int N = 3007 ;
int n ,num[N] ,pos[N] ,tot ,ans1i ,ans1j ,ans2i ,b[N] ; 
ll a[N] ,dp[N][N] ,sum ,ans1 ,ans2 ; bool used[N][N] ;
std :: vector < int > chs ;
int main () { 
	read (n) ;
	f (i ,1 ,n ,1) read (a[i]) ; f (i ,1 ,n ,1) read (b[i]) ;
	f (i ,1 ,n ,1) {
		if (i == 1) b[i] = 0 ;
		num[i] = num[i - 1] + (b[i] == 0) ;
		if (b[i] == 0) pos[++ tot] = i ;
	} // 记录好的位置
	antif (i ,n ,1 ,1) {
		f (j ,0 ,n ,1) dp[i][j] = dp[i + 1][j] ; // 不选 i，直接继承
		f (j ,b[i] ,n ,1) 
			if (dp[i + 1][j - b[i]] + a[i] > dp[i][j])
				dp[i][j] = dp[i + 1][j - b[i]] + a[i] , used[i][j] = 1 ;
// 注意，此时如果更新了，那么根据背包的原理我们一定是建立在选 i 的基础之上，那么 used[i][j] = 1 就表示在 dp[i][j] 这个状态下 i 这个位置被选了
	}
	f (i ,1 ,n ,1) 
		f (j ,0 ,n ,1) 
			if (ans1 < dp[i][j] && j <= num[i - 1]) 
				ans1 = dp[i][j] , ans1i = i , ans1j = j ; 
// 找到第一种情况的最大答案
// 第二种
	antif (i ,n ,1 ,1) {
		if (b[i] == 0) sum += a[i] * (a[i] >= 0ll) ; // 好的且非负的位置一定选
		else if (a[i] >= 0ll)  
			if (ans2 < sum + a[i]) // i 就是选的最左边的位置
				ans2 = sum + a[i] , ans2i = i ;
	}
	if (std :: max (ans1 ,ans2) <= 0ll) return printf ("0\n\n0\n") ,0 ;
	if (ans1 >= ans2) {
		int pt = 0 ,nowj = ans1j ;
		while (++ pt <= ans1j) chs.emplace_back (pos[pt]) ; 
// 随便选够 j 个好位置（选谁无所谓，反正被删掉了）
		f (i ,ans1i ,n ,1) 
			if (used[i][nowj])  
				chs.emplace_back (i) , nowj -= b[i] ;
// 看当前状态都留下了哪几个位置
		std :: cout << chs.size () << '\n' ;
		for (auto i : chs) std :: cout << i << ' ' ; puts ("") ;
		std :: cout << ans1 << '\n' ;
	} else {
		f (i ,ans2i ,n ,1) 
			if (i == ans2i || (b[i] == 0 && a[i] >= 0ll)) chs.emplace_back (i) ;
		std :: cout << chs.size () << '\n' ;
		for (auto i : chs) std :: cout << i << ' ' ; puts ("") ;
		std :: cout << ans2 << '\n' ;
	}
	return 0 ;
} 
```
然后是我丑陋的暴力代码：


```cpp
#include <bits/stdc++.h>
#define int long long 
#define f(i ,m ,n ,x) for (int i = (m) ; i <= (n) ; i += (x))
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = - x : 0 ;
}
template < typename T ,typename ...Args >
inline void read ( T &x ,Args &...tmp ) {
	read (x) ,read (tmp...) ;
}
const int N = 3e3 + 7 ;
int n ,a[N] ,b[N] ,sum ,tot ,allz ,c[N] ,alloz ,sta[2000005] ,tott ;
int v[N] ,siz ;
inline void dfs (int cur ,int now) {
	if (cur == n + 1) return (void) (sta[++ tott] = now) ;
	dfs (cur + 1 ,now | (1 << cur)) ;
	dfs (cur + 1 ,now) ;
}
signed main () {
	read (n) ;
	if (n <= 20) {
		f (i ,1 ,n ,1) read (a[i]) ;
		f (i ,1 ,n ,1) read (b[i]) ;
		dfs (1 ,0) ;
		int maxx = 0 ,num = 0 ;
		f (i ,1 ,tott ,1) {
			if (sta[i] == 0) continue ;
			siz = 0 ;
			f (j ,1 ,n ,1) 
				if (sta[i] & (1 << j)) v[++ siz] = j ;
			/*if (sta[i] == 30) {
				f (j ,1 ,siz ,1) std :: cout << v[j] << ' ' ;
				puts ("") ; 
			}*/
			int ans = 0 ,las = 1 ;
			f (j ,1 ,siz ,1) {
				ans += a[v[j]] ;
				int k = las ;
				for (int m = 1 ; k < j && m <= b[v[j]] ; k ++ ,m ++) ans -= a[v[k]] ;
				las = k ;
			}
			if (maxx < ans) {
				maxx = ans ;
				num = i ;
			}
		}
		if (maxx == 0) std :: cout << 0 << '\n' << '\n' << 0 << '\n' ;
		else {
			std :: cout << __builtin_popcount (sta[num]) << '\n' ;
			f (i ,1 ,n ,1) {
				if ((1 << i) & sta[num]) std :: cout << i << ' ' ;
			}
			puts ("") ;
			std :: cout << maxx << '\n' ;
		}
		return 0 ;
	}
	f (i ,1 ,n ,1) {
		read (a[i]) ;
		if (a[i] >= 0) tot ++ ,sum += a[i] ;
		c[i] = a[i] ;
	}
	f (i ,1 ,n ,1) {
		read (b[i]) ;
		if (b[i] != 0) allz = true ;
		if (b[i] == 0) alloz = true ;
	}
	if (allz && alloz) {
		int tot = 0 ;
		f (i ,1 ,n ,1) {
			if (b[i] == 0) tot ++ ;
		}
		int num = 0 ;
		f (i ,1 ,n ,1) {
			if (b[i] == 0) break ;
			num = i ;
		}
		if (num) tot ++ ;
		std :: cout << tot << '\n' ;
		if (num) std :: cout << num << ' ' ;
		f (I ,1 ,n ,1) {
			if (b[I] == 0) std :: cout << I << ' ' ; 
		}
		puts ("") ;
		std :: cout << tot << '\n' ;
		return 0 ;
	}
	if (allz) {
		std :: sort (a + 1 ,a + n + 1 ,std :: greater < int > ()) ;
		if (a[1] < 0) std :: cout << 0 << '\n' << '\n' << 0 << '\n' ;
		else {
			std :: cout << 1 << '\n' ;
			f (i ,1 ,n ,1) {
				if (c[i] == a[1]) {
					std :: cout << i << '\n' ;
					break ;
				}
			}
			std :: cout << a[1] << '\n' ;
		}
		return 0 ;
	}
	std :: cout << tot << '\n' ;
	f (i ,1 ,n ,1) if (a[i] >= 0) std :: cout << i << ' ' ;
	std :: cout << '\n' ;
	std :: cout << sum << '\n' ;
	return 0 ;
}
```

---

## 作者：CaiZi (赞：2)

## DlgtTemplate 题解
**[题目链接](https://www.luogu.com.cn/problem/P11274)**
### 题目分析
一眼 DP，设 $c_{i,j}$ 表示前 $i$ 个格子，可以消除 $j$ 个格子的最大得分。初始状态为 $c_{i,0}=a_i,c_{i,1}=0$。

选第 $i$ 个格子时，有 $c_{i,j}=\max\{c_{i-1,j+b_i}\}+a_i$，其中 $j\in[0,i-b_i-1]$；而不选第 $i$ 个格子时，有 $c_{i,j}=c_{i-1,j}$。两种方案取最大值即可。

然而这样是不对的，当 $b_i=0$ 时，显然还可以令 $c_{i,s+1}=0$，其中 $s$ 为满足 $c_{i-1,j}$ 这个状态合法的最大的 $j$，因为我们可以将这个格子选上，然后全部拿去消除。否则你会发现仅有 $j=0$ 和 $j=1$ 的状态是合法的。

然后是输出方案，考虑记录一个状态是由哪个状态转移过来的，以及这个状态是否选了 $i$，注意令 $c_{i,s+1}=0$ 时也是选了 $i$。然后 DFS 从最大值的位置往回找，回溯过程顺带输出即可。
### 代码展示
时间复杂度 $O(n^2)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[3001],b[3001],c[3001][3001],x[3001][3001],s;
bool y[3001][3001];
inline void dfs(int i,int j,int k){
	if(y[i][j]){
		k++;
	}
	if(i!=0&&x[i][j]!=-1){
		dfs(i-1,x[i][j],k);
	}
	else{
		cout<<k<<'\n';
	}
	if(y[i][j]){
		cout<<i<<' ';
	}
}
signed main(){
    cin.tie(nullptr)->sync_with_stdio(0);
    memset(x,-1,sizeof(x));
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			c[i][j]=LONG_LONG_MIN;
		}
	}
	for(int i=1;i<=n;i++){
		c[i][0]=a[i];
		c[i][1]=0;
		y[i][0]=y[i][1]=1;
	}
	for(int i=1;i<=n;i++){
		if(b[i]==0){
			c[i][s+1]=0;
			x[i][s+1]=s;
			y[i][s+1]=1;
		}
		s=0;
		for(int j=0;j<=i-b[i]-1;j++){
			if(c[i-1][j+b[i]]!=LONG_LONG_MIN){
				if(c[i][j]<c[i-1][j+b[i]]+a[i]){
					c[i][j]=c[i-1][j+b[i]]+a[i];
					x[i][j]=j+b[i];
					y[i][j]=1;
				}
			}
		}
		for(int j=0;j<=n;j++){
			if(c[i][j]<c[i-1][j]){
				c[i][j]=c[i-1][j];
				x[i][j]=j;
				y[i][j]=0;
			}
			if(c[i][j]!=LONG_LONG_MIN){
				s=j;
			}
		}
	}
	s=0;
	for(int i=0;i<=n;i++){
		if(c[n][i]>c[n][s]){
			s=i;
		}
	}
	if(c[n][s]==0){
		cout<<"0\n";
	}
	else{
		dfs(n,s,0);
	}
	cout<<'\n'<<c[n][s];
    return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/188043337)**

---

## 作者：luxiaomao (赞：1)

## [P11274](https://www.luogu.com.cn/problem/P11274) 有一定思维难度的 DP 题

赛后好久才想起来补题，顺便写篇题解。

### Problem

给出长度为 $n$ 的序列 $a$ 和 $b$。

可以从左到右选择一些格子，选择一个格子 $i$ 会为答案加上 $a_i$，同时撤销掉选择序列开头的 $b_i$ 个格子。（如果不够撤销就撤到不能撤为止）

要求最大贡献，并输出最大贡献时的选择方案。

### Solution

我们称 $b_i=0$ 的格子为“好格”，否则为“坏格”。

有两种策略：

- 第一种，全程没有出现撤销操作。也就是说，先选一个格，然后把它后面所有 $a_i > 0$ 的好格都选上。这个可以用贪心的思想来做。

- 第二种，有出现撤销操作。我们发现，必然在序列的前端选中一些好格用来被撤销，在序列的后端选中一些格子，在删掉前端的好格同时为答案做出贡献。

难在第二种策略，不难看出用 DP。但是如果从前往后 DP 比较难考虑删掉的是哪个格，我们从后往前。

记 $f_{i,j}$ 表示从 $i$ 到 $n$ 这些格子中选出一些（不一定要选 $i$），总共造成了 $j$ 个撤销，最大的答案是多少。

于是有 $f_{i,j} = \min\{f_{i+1,j},f_{i+1,j-b_i}+a_i\}$。与此同时，我们还需要记录输出方案，实现起来有点小麻烦，具体看代码。

最后，比较两种策略哪种更优，输出即可。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 3005
using namespace std;

int n,a[N],b[N];
int f[N][N],las[N][N],pre[N];
vector<int> num;

signed main()
{
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++)scanf("%lld",&a[i]);
	for(int i = 1;i <= n;i++)scanf("%lld",&b[i]);b[1] = 0;
	
	int ans1 = 0,id1 = 0,cnt1 = 0;
	for(int i = n;i;i--)
	{
		if(a[i] + cnt1 > ans1)
		{
			ans1 = a[i] + cnt1;
			id1 = i;
		}
		if(b[i] == 0 && a[i] > 0)cnt1 += a[i];
	}
	
	int ans2 = 0;pair<int,int> id2;
	for(int i = 1;i <= n;i++)
		pre[i] = pre[i-1] + (b[i] == 0);
	for(int i = n;i;i--)
	{
		for(int j = 0;j <= n;j++)
			f[i][j] = f[i+1][j],las[i][j] = 0;
		for(int j = b[i];j <= n;j++)
			if(f[i+1][j-b[i]] + a[i] > f[i][j])
			{
				f[i][j] = f[i+1][j-b[i]] + a[i];
				las[i][j] = 1;
			}
	}
	for(int i = 1;i <= n;i++)
		for(int j = 0;j <= n;j++)
			if(pre[i-1] >= j && f[i][j] > ans2)
				ans2 = f[i][j],id2 = make_pair(i,j);
	
	if(max(ans1,ans2) == 0)
	{
		printf("0\n\n0");
		return 0;
	}
	if(ans1 >= ans2)
	{
		num.push_back(id1);
		for(int i = id1 + 1;i <= n;i++)
			if(b[i] == 0 && a[i] > 0)
				num.push_back(i);
		printf("%lld\n",num.size());
		for(int i = 0;i < num.size();i++)
			printf("%lld ",num[i]);
		printf("\n%lld\n",ans1);
		return 0;
	} 
	else
	{
		int cnt2 = 0;
		for(int i = 1;i < id2.first;i++)
		{
			if(b[i] == 0)num.push_back(i),cnt2++;
			if(cnt2 == id2.second)break;
		}
		int nowj = id2.second;
		for(int i = id2.first;i <= n;i++)
			if(las[i][nowj])
			{
				num.push_back(i);
				nowj -= b[i];
			}
		printf("%lld\n",num.size());
		for(int i = 0;i < num.size();i++)
			printf("%lld " ,num[i]);
		printf("\n%lld\n",ans2);
		return 0;
	}
}
```

---

