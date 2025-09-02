# World is Mine

## 题目描述

Alice and Bob are playing a game. Initially, there are $ n $ cakes, with the $ i $ -th cake having a tastiness value of $ a_i $ .

Alice and Bob take turns eating them, with Alice starting first:

- In her turn, Alice chooses and eats any remaining cake whose tastiness is strictly greater than the maximum tastiness of any of the cakes she's eaten before that. Note that on the first turn, she can choose any cake.
- In his turn, Bob chooses any remaining cake and eats it.

The game ends when the current player can't eat a suitable cake. Let $ x $ be the number of cakes that Alice ate. Then, Alice wants to maximize $ x $ , while Bob wants to minimize $ x $ .

Find out how many cakes Alice will eat if both players play optimally.

## 说明/提示

In the first test case, one possible sequence of turns is:

1. Alice eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [4, 2, 3] $ .
2. Bob eats a cake with a tastiness value of $ 2 $ . The remaining cakes are $ [4, 3] $ .
3. Alice eats a cake with a tastiness of $ 3 $ . The remaining cakes are $ [4] $ .
4. Bob eats a cake with a tastiness value of $ 4 $ . The remaining cakes are $ [] $ .
5. Since there are no more cakes left, the game ends.

In the second test case, one possible sequence of turns is:

1. Alice eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [1, 1] $ .
2. Bob eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [1] $ .
3. Since Alice has already eaten a cake with a tastiness value of $ 1 $ , she cannot make a turn, so the game ends.

## 样例 #1

### 输入

```
9
4
1 4 2 3
3
1 1 1
5
1 4 2 3 4
4
3 4 1 4
1
1
8
4 3 2 5 6 8 3 4
7
6 1 1 3 5 3 1
11
6 11 6 8 7 5 3 11 2 3 5
17
2 6 5 3 9 1 6 2 5 6 3 2 3 9 6 1 6```

### 输出

```
2
1
3
2
1
3
2
4
4```

# 题解

## 作者：Rnfmabj (赞：21)

## CF1987D 题解

### 题意

A 和 B 比赛吃蛋糕，蛋糕共有 $n$ 个，每一个蛋糕有一个美味值 $a_i$。

A 与 B 交替着吃，A 先吃，且 A 需要保证 A 本次吃的蛋糕美味值要**严格大于**先前 A 所吃的所有蛋糕；接着，B可以吃掉任意一个蛋糕（当然，已经被吃掉的肯定不行），直到有一方无蛋糕可吃为止，游戏结束。

设 $x$ 为游戏结束时，A 吃下的蛋糕总数。已知 A 和 B 都足够聪明，A 想要最大化 $x$ 而 B 想要最小化 $x$，求双方都按自己的最优策略吃蛋糕时，$x$ 将会是多少。

$n \le 5000$

-----

你这 D 怎么比 C 好想这么多.jpg

如果所有蛋糕的美味值两两不同，那么显然 B 做什么复杂的决策是没有意义的，只要 A 不傻就会从最小的蛋糕开始往上递增着吃，B 最多只能吃掉一半的蛋糕，这里就和博弈没什么关系了。所以题目的重点就在于处理那些美味值相同的蛋糕。

对于一批美味值相同的蛋糕，A 想要“拿下”这批蛋糕只需要吃掉其中的一个就可以了，因为吃蛋糕的顺序是严格的单调递增，多出来的那些蛋糕没有意义；而 B ~~要考虑的就多了~~需要在 A 吃掉其中任意一个之前把它们全部吃掉。也就是说，假设这批相同美味值的蛋糕有 $p$ 个，A 让这批蛋糕对 $x$ 产生一个贡献只需要消耗 $1$ 回合就行，而 B 要拦截下这个贡献需要 $p$ 回合。

再结合 A 从小往大吃一定不劣的性质，我们因此可以对 $a$ 排序、将 $a$ 相同的蛋糕合并后依次从小往大考虑，对每批美味值相同的蛋糕 $i$ ，B 可以选择把这个 $i$ 让给 A 吃来为自己争取到一个空闲回合，用来拦截后面的蛋糕；也可以选择用已经积累好的空闲回合直接出手拦截这个 $i$，代价就是这批 $i$ 蛋糕的总个数 $c_i$。

基于这个思路做记忆化搜索就好了。设计状态 $f_{i,j}$ 表示当前考虑到了第 $i$ 批蛋糕，当前 B 已经攒下了 $j$ 个空闲回合时已经产生的最小贡献，那么不拦截和拦截产生的转移方程即为 $f_{i,j}=\min (f_{i+1,j+1}+1,f_{i+1,j-c_i})$，后者需要保证 $c_i \le j$。

时空复杂度为 $O(n^2)$。

-----

```cpp
const ll maxn=5005;
ll f[maxn][maxn];
ll a[maxn],tot,b[maxn];
ll n;
ll dfs(ll x,ll t){//记忆化搜索
	if(x>tot)return 0;
	if(~f[x][t])return f[x][t];
	ll res=dfs(x+1,t+1)+1;
	if(t>=b[x])res=min(res,dfs(x+1,t-b[x]));
	return f[x][t]=res;
}
void solve(){
	n=R;
	tot=0;
	for(ll i=1;i<=n;i++){
		a[i]=R;
		for(ll j=0;j<=n;j++)f[i][j]=-1;//多测清空
	}
	sort(a+1,a+1+n);
	for(ll i=1;i<=n;i++){
		if(a[i]>a[i-1])b[++tot]=1;
		else b[tot]++;
	}//合并
	we(dfs(1,0));
	return ;
}
```

---

## 作者：wmrqwq (赞：9)

# 题目链接

[CF1987D World is Mine](https://codeforces.com/contest/1987/problem/D)

# 提示

1. Alice 的策略是固定的。

2. 考虑用动态规划解决问题。

# 解题思路

我们发现，Alice 的最优策略一定是每次取当前能取的美味值最小的蛋糕，而 Bob 的策略难以使用贪心维护。

于是我们考虑用动态规划来考虑 Bob 的策略。

我们发现，Bob 想让让 Alice 吃不到某种蛋糕，当且仅当 Bob 把这个种类的所有蛋糕都拿走了。因此我们需要开个桶来记录每个种类的蛋糕所出现的数量。

于是我们就可以将 Bob 蛋糕的个数加 $1$ 化为 Bob 拿蛋糕的代价（加上一是因为 Alice 是先手），而 $1$ 就是 Bob 获得的收益，于是我们就可以直接 dp，$dp_{i,j}$ 表示 Bob 考虑到前 $i$ 个蛋糕，花的代价为 $j$ 时可以拿掉的最大蛋糕种类数是多少。

最终答案即为直接用原本的蛋糕种类数减去 Bob 最大拿掉的蛋糕种类数。

时间复杂度 $O(n^2)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n;
ll a[5010];
ll b[5010];
ll c[5010],d[5010];
ll pd,ans;
ll lst,k;
ll dp[5010][5010];
void solve()
{
	pd=1,k=0;
	cin>>n;
	forl(i,1,n)
		cin>>a[i],b[a[i]]++;
	forl(i,1,5000)
		if(b[i])
			k++,c[k]=k,d[k]=b[i]+1;
	forl(i,1,k)
	{
		forr(j,i,0)
		{
			dp[i][j]=max(dp[i][j],dp[i-1][j]);
			if(j+d[i]<=i)
				dp[i][j+d[i]]=max(dp[i][j+d[i]],dp[i][j]+1);
		}
		
	}
	ll ma=0;
	forl(i,1,k)
	{
		forl(j,0,i)
	/*		cout<<"["<<i<<','<<j<<']'<<dp[i][j]<<' ',*/ma=max(ma,dp[i][j]),dp[i][j]=0;
	//	cout<<endl;
	}
	cout<<k-ma<<endl;	
	forl(i,1,5000)
		a[i]=b[i]=c[i]=d[i]=0;
/*	while(1)
	{
		if(pd)
		{
			forl(i,1,5000)
			{
				if(b[i])
				{
					b[i]--;
					ans++;
					lst=i;
					break;			
				}
				if(i==5000)
				{
					cout<<ans<<endl;
					return ;
				}
			}
			pd^=1;
		}
		else
		{
			ll mi=1e18,id=0,sum=0;
			forl(i,lst+1,5000)
			{
				if(b[i])
					c[]
			}
			pd^=1;
		}
	}*/
}
int main()
{
	IOS;
	t=1;
 	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：ben090302 (赞：5)

妙妙动规题。

先把输入的数组排序，然后将相同的视作一个物品，而拿走这个物品的代价是相同元素个数。

大概这个意思:

```
for(int i=1;i<=n;i++) cin>>a[i];
sort(a+1,a+n+1);
for(int i=1;i<=n;i++){
  if(a[i]!=a[i-1]){
    V[++tot]={tot,1};
  }
  else V[tot].num++;
}
```

考虑 $A$ 的策略：显然 $A$ 必须从小往大去拿，否则漏掉一个必定更劣。

$B$ 的策略就更加复杂一丢丢，我们有两个选择:攒着回合让 $A$ 去吃一个蛋糕，或者攒够了一口气 “取走” 一个物品让 $A$ 吃不到。

设 $dp_{i,j}$ 表示到第 $i$ 类为止， $B$ 还剩 $j$ 个回合没用情况下， $A$ 吃的蛋糕数量的最小值，根据分析我们容易得出转移式子:

```
for(int i=1;i<=tot;i++){
        for(int j=0;j<=i;j++){
            dp[i][j] = min(dp[i][j],dp[i-1][j] + 1);
            if(j+V[i].num<=i-1) dp[i][j]=min(dp[i][j],dp[i-1][j+V[i].num]);
        }
    }
```

但是非常抱歉这个代码不太对味，我们发现它在 $j=0$ 的时候越界了。

怎么办？这个时候 $B$ 不妨当一下傻子，哪怕代价不够也去吃一个这个蛋糕即可。

答案为 $dp_{n,0}$ ，但是 $n$ 是种类不是输入的 $n$。

完整代码:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n,a[5005];
int dp[5005][5005];//dp i j=到第i种,B攒了j个回合去堵
struct node{
    int v,num;
};
node V[5005];
int tot;
void work(){
    cin>>n;tot=0;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        if(a[i]!=a[i-1]){
            V[++tot]={tot,1};
        }
        else V[tot].num++;
    }
    for(int i=0;i<=tot;i++){
        for(int j=0;j<=tot;j++){
            dp[i][j]=INT_MAX;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=tot;i++){
        for(int j=0;j<=i;j++){
            if(j!=0) dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=dp[i-1][j]+1;
            if(j+V[i].num<=i-1) dp[i][j]=min(dp[i][j],dp[i-1][j+V[i].num]);
        }
    }
    cout<<dp[tot][0]<<"\n";
}
signed main(){
    cin>>T;
    while(T--){
        work();
    }
}
```

时间复杂度 $O(Tn^2)$

---

## 作者：CCPSDCGK (赞：4)

考场降大智题。

首先 Alice 一定选**当前可选的最小的**最优，Bob 如果选择了一个蛋糕一定会把**与它相同价值的蛋糕都吃掉**。

设 $f_{i,j}$ 为所有价值 $\le i$ 的蛋糕中 Bob 可选的蛋糕还剩 $j$ 个，$b_j$ 为满足 $a_i=j$ 的 $i$ 的个数。

所以就有两种转移：
1. Alice 选了当前价值的蛋糕，那么转移就是 $f_{i,j+1}=\min(f_{i,j+1},f_{i-1,j}+1)$。
2. Bob 选了当前价值的蛋糕，那么转移就是 $f_{i,j-b_i}=\min(f_{i,j-b_i},f_{i-1,j})$。

时间复杂度：$O(n^2)$。
```cpp
int dp[5005][5005],a[5005];
void solve(){
	int n;cin>>n;
	for(int i=1;i<=n;i++) a[i]=0;
	for(int i=1;i<=n;i++){
		int x;cin>>x,a[x]++;
	}
	for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) dp[i][j]=inf;
	**dp=0;
	for(int i=1;i<=n;i++){
		for(int j=a[i];j<=n;j++) dp[i][j-a[i]]=min(dp[i][j-a[i]],dp[i-1][j]);
		if(a[i]) for(int j=0;j<n;j++) dp[i][j+1]=min(dp[i][j+1],dp[i-1][j]+1);
	}
	cout<<*mie(dp[n],dp[n]+n+1)<<endl;
}
```

---

## 作者：littlebug (赞：3)

## Solution

先做一个离散化。

记 $c_i$ 为第 $i$ 种蛋糕的个数。

令 $f_{i,j}$ 表示只考虑前 $i$ 个，B 攒了 $j$ 次操作（意思是在本来该轮到 B 的回合中，B 选择跳过并攒一次操作；因为 A 的操作固定，所以这是可行的），A 所能吃到蛋糕的最小值。从小到大遍历每个 $i$，再从 $0$ 到 $i$ 遍历每个 $j$，则：

- 若 B 选择蛋糕 $i$，则 B 攒的总次数 $-c_i$，A 吃到的蛋糕个数不变，$f_{i,j} = f_{i-1,j+c_i}$。
- 若 B 不选蛋糕 $i$，则 B 攒的总次数 $+1$，A 吃掉这个蛋糕，$f_{i,j} = f_{i-1,j-1}+1$。

注意 $j=0$ 可能越界，需要特判，此时第二种情况中 $f_{i,j} = f_{i-1,j}+1$，因为显然没有更优的选择。

因为攒了 $j$ 次操作相当于**剩余** $j$ 次操作，所以答案为 $f_{num,0}$（$num$ 为蛋糕的种类数）。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
//#define int long long
#define il inline
using namespace std;

const int MAXN=5000+5;
int n,a[MAXN],b[MAXN],c[MAXN];
int f[MAXN][MAXN];

il void solve()
{
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i],c[i]=0;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i) b[i]=a[i];

    int num=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+num+1,a[i])-b;

    for(int i=1;i<=n;++i) ++c[a[i]];

    for(int i=1;i<=num;++i) for(int j=0;j<=i;++j)
    {
        if(j) f[i][j]=f[i-1][j-1]+1;
        else f[i][j]=f[i-1][j]+1;
        if(j+c[i]<i) f[i][j]=min(f[i][j],f[i-1][j+c[i]]);
    }

    cout<<f[num][0]<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    int T; cin>>T; while(T--) solve();
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

（下文中 Alice 简写为 A，Bob 为 B）

首先，我们令 $b_i$ 为 $i$ 在 $a$ 中的出现次数，对于每个 $a_i$，我们令 $b_{a_i}\leftarrow b_{a_i}+1$。

我们首先考虑 A 的最优决策。

很显然，她最优就是拿当前所有蛋糕中最小的一个，即把最小的满足 $c_{i}\not = 0$ 的 $c_i$ 清零。

然后是 B。

我们注意到，B 一旦想要拿某个蛋糕，那么一定要拿完所有美味都与之相同的蛋糕，因为 A 每种蛋糕只能拿一个。

上述操作从整体上来看也相当于选择一个长度为 $m$ 的数组 $b$，对于所有的 $b_i$，令 $c_{b_i}=0$。  
而很明显，$b$ 最优是递增的，然后每回合，B 都会把最小的满足 $c_{b_i}\not=0$ 的 $c_{b_i}\leftarrow c_{b_i}-1$。

可是，$b$ 还有一些别的限制：

- 首先为了避免 B 在还没取完 $c_i$ 时 A 就取到 $c_i$ 了，一个 $c_i$ 必须满足 $\sum_{j=1}^{i-1} b_{c_j}> c_i$；
- 其次，再取到 $c_i$ 之前，前面已经有 $i-1$ 个蛋糕被 B 自己取了，那么 $c_i>i-1$。

合起来看，$\sum_{j=1}^{i-1} b_{c_j}+i-1> c_i$，即 $\sum_{j=1}^{i-1} b_{c_j}\ge c_i-i$。

那么 $c$ 已经有条件了，我们就考虑 dp。

我们设 $dp_{i,j}$ 为前 $i$ 个中，$c$ 大小为 $j$ 的最小回合数。

那么初始很显然 $dp_{0,0}=0$。

接下来是转移：

首先，我们可以不把 $i$ 加入 $c$，即 $dp_{i,j}=dp_{i-1,j}$。

接下来，如果要加，那么就要耗费 $b_i$ 个回合，也就是已经有了 $dp_{i-1,j-1}+b_i$ 个回合，那么如果有 $dp_{i-1,j-1}+b_i< i-j$，就不能满足上述条件，不能加，否则 $dp_{i,j}=\min\{dp_{i,j},dp_{i-1,j-1}+b_i\}$。

而最终答案为最大的满足 $dp_{n,i}$ 被转移过的 $n-i$。

PS：$dp_{i,j}$ 的 $i$ 这维能用滚动数组滚掉。

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1987D)

# 思路：

第一想法是贪心的决策，考虑到是博弈论，每一轮决策肯定都是最优的。显然贪心做法假掉。

发现问题具有最优子结构与后效性，考虑 dp。

将 $a_i$ 数组排序，将相同元素打包成块，块长为 $b_{a_i}$。设 $f_{i,j}$ 表示以第 $i$ 个块结尾，剩余决策数为 $j$ 的最优选择答案。

- 若当前回合的剩余决策数立马用掉，不消除答案贡献，即为 $f_{i,j}=f_{i-1,j}+1$，
- 若当前回合的剩余决策数留下，不消除答案贡献，即为 $f_{i,j}=f_{i-1,j-1}+1$，

- 若当前回合的剩余决策数用掉 
 来消除答案贡献，即为 $f_{i,j}=f_{i-1,j}+b_{a_i}$。

三种决策取最小即可。

由于博弈论的特殊性：双方在相同回合数时的总操作数相同，所以最后肯定不会剩余下决策数。所以答案为 $f_{n,0}$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+10;
const int INF=0x3f3f3f3f;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
    return;
}
int T,n,a[N],b[N],f[N][N];
signed main(){
    cin>>T;
    while(T--){
        int ans=0,num=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            b[i]=0;
        }
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                f[i][j]=INF;
            }
        }
        for(int i=1;i<=n;i++){
            cin>>a[i];
            b[a[i]]++;
        }
        sort(a+1,a+n+1);
        int tot=unique(a+1,a+n+1)-a-1;
        n=tot;
        f[0][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=i;j++){
                if(j!=0){
                    f[i][j]=min(f[i-1][j],f[i-1][j-1])+1;
                }else{
                    f[i][0]=f[i-1][0]+1;
                }
                if(b[a[i]]+j<=i-1){
                    f[i][j]=min(f[i][j],f[i-1][j+b[a[i]]]);
                }
            }
        }
        cout<<f[n][0]<<'\n';
    }
    return 0;
}
```
完结撒花~

---

## 作者：liugh_ (赞：0)

## [World is Mine](https://codeforces.com/contest/1987/problem/D)

A 每次一定会选择一个最小的可选的数，因为往大的选只会减少能选的次数，于是构造新序列 $c$ 满足 $c_i$ 为原序列 $a$ 中第 $i$ 小的数的出现次数，那么 B 消掉第 $i$ 小的数的代价即为 $c_i$。贪心地，对于一个数，B 要么不动它，要么全部消去，而且要在 A 到达之前消去才会有贡献。注意到 A 一定是顺次选择的，是有阶段性的，于是考虑 dp，并通过**对转移的限制**来满足 A。影响答案的变量有时间和 B 完全消去的数的个数，于是考虑设 $f(i,j)$ 为考虑完 $c$ 中前 $i$ 个数，且 B 完全消掉了 $j$ 个数所需的最小时间。先不考虑 A，那么转移显然有
$$
f(i,j)=\min\{f(i-1,j),f(i-1,j-1)+c_i\}
$$
那么如何对转移进行限制以满足 A 呢？注意到 A 的实际位置是时间加上 B 转移前已经完全消去的数的个数，而合法当且仅当 A 的实际位置小于 $i$，否则根据贪心策略一定不优，那么只需将不合法的状态设为无穷大即可。形式化地，若 $f(i,j)+j-1\ge i$，则令 $f(i,j)\gets \infty$。

考虑初始化，显然初始时 $j$ 只能为 $0$，于是令 $f(0,j)=[j\ne 0]\cdot \infty$。考虑统计答案，找到最大的 $j$ 满足 $f(n,j)\ne \infty$，那么 $ans=|c|-j$。时间复杂度 $O(n^2)$。[Code](https://codeforces.com/contest/1987/submission/286537631)

---

## 作者：Daniel_yao (赞：0)

# Problem

爱丽丝和鲍勃在玩游戏。最初，有 $n$ 个蛋糕，$i$ 个蛋糕的美味值为 $a_i$。

爱丽丝和鲍勃轮流吃，爱丽丝先吃:

- 轮到爱丽丝，她选择并吃任何剩下的蛋糕，这些蛋糕的味道**严格**大于她之前吃过的任何蛋糕。注意，在第一个回合，她可以选择任何蛋糕。
- 轮到鲍勃选剩下的蛋糕吃了。

当玩家吃不到合适的蛋糕时，游戏就会结束。设 $x$ 为爱丽丝吃的蛋糕的数量。然后，Alice想最大化 $x$，而Bob想最小化 $x$。

找出如果两个玩家都玩最优游戏，爱丽丝会吃多少蛋糕。

# Solve

第一想法是贪心的决策，考虑到是博弈论，每一轮决策肯定都是最优的。显然贪心做法假掉。

发现问题具有最优子结构与后效性，考虑 dp。

将 $a_i$ 数组排序，将相同元素打包成块，块长为 $b_{a_i}$。设 $f_{i,j}$ 表示以第 $i$ 个块结尾，剩余决策数为 $j$ 的最优选择答案。

- 若当前回合的剩余决策数立马用掉，不消除答案贡献，即为 $f_{i,j}=f_{i-1,j}+1$；

- 若当前回合的剩余决策数留下，不消除答案贡献，即为 $f_{i,j}=f_{i-1,j-1}+1$；

- 若当前回合的剩余决策数用掉 $b_{a_i}$ 来消除答案贡献，即为 $f_{i,j} = f_{i-1,j + b_{a_i}}$；

三种决策取最小即可。

由于博弈论的特殊性：双方在相同回合数时的总操作数相同，所以最后肯定不会剩余下决策数。所以答案为 $f_{n,0}$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define inf 1e17

using namespace std;

const int N = 5e3 + 10;

int T, n, a[N], b[N], f[N][N];

void solve() {
  int ans = 0, num = 0;
  cin >> n;
  For(i,1,n) b[i] = 0;
  For(i,0,n) For(j,0,n) f[i][j] = inf;
  For(i,1,n) cin >> a[i], b[a[i]]++;
  sort(a + 1, a + n + 1);
  int tot = unique(a + 1, a + n + 1) - a - 1;
  n = tot;
  f[0][0] = 0;
  For(i,1,n) {
    For(j,0,i) {
      if(j != 0) f[i][j] = min(f[i-1][j], f[i-1][j-1]) + 1;
      else f[i][0] = f[i-1][0] + 1;
      if(b[a[i]] + j <= i-1) f[i][j] = min(f[i][j], f[i-1][j + b[a[i]]]);
    }
  }
  cout << f[n][0] << '\n';
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

时间复杂度 $O(Tn^2)$，记得多测清空。

---

## 作者：ANDER_ (赞：0)

#### 考察：策略、动态规划。

## 题意
给定大小为 $n$ 的序列 $A$，Alice 和 Bob 轮流按照下列规定取走其中的元素，Alice 先取。若有一方无法再取，游戏结束。

1. Alice 所取的元素必须**严格大于**她上一次所取的元素。特别的，在游戏开始时，Alice 可以取任意一个元素。

2. 每一轮，Bob 可以从剩下的元素中取任意一个元素。

3. Alice 希望她所取的元素个数越多越好，而 Bob 希望 Alice 取的个数越少越好。

4. 双方都按照最优策略行动。

输出 Alice 在游戏结束时所取的元素个数。有 $t$ 组数据。

## 思路
注意到 Alice 的策略不变，考虑动态规划。

记 $B_i$ 为第 $i$ 大的数出现的次数，Alice 的最优策略显然是从小往大取。因为当 $A$ 中的元素互异时，博弈就失去了意义，两人都只会取到 $\frac{n}{2}$ 个，故主要考虑 $A$ 内相同的元素。对于 $B_i > 1$ 的情况，Alice 只需要取一个 $i$。所以 Bob 的最优策略就是赶在 Alice 取到 $i$ 之前将 $i$ 全部取完。

令 $f_{i,j}$ 表示 Bob 在前 $i$ 大的元素中取走 $j$ 个使得 $B_k = 0$ 的个数，其中 $k\isin[1, i]$。初始状态为 $-∞$，$f_{0, 0} = 0$。状态转移如下：

1. 在 Bob 不取 $B_i$ 时，$f_{i,j} = \max(f_{i,j},f_{i-1,j})$。

2. Bob 取 $B_i$ 的情况，当 $i - 1 - f_{i - 1, j - B_i} \geq j$ 时，$f_{i,j} = \max(f_{i,j},f_{i - 1, j - B_i} + 1)$。注意需要满足 Alice 取的个数大于等于 Bob 取的个数。

最后答案为 $|B| - 1 - \max^n_{i = 1}(f_{|B|, i})$。时间复杂度为 $O(\sum n^2)$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e3 + 5, INF = 1e9;
int t, n, sum, cnt[N], f[N][N];
vector<int> b;
inline void clean() {
	sum = 0;
	b.clear();
	for(int i = 0 ; i <= n ; i ++) {
		cnt[i] = 0;
		for(int j = 0 ; j <= n ; j ++) {
			f[i][j] = -INF;
		}
	}
	return;
}
inline void solve() {
	cin>>n;
	clean();
	for(int i = 1, x ; i <= n ; i ++) {
		cin>>x;
		cnt[x] ++;
	}
	b.push_back(0);
	for(int i = 1 ; i <= n ; i ++) {
		if(cnt[i] != 0) {
			b.push_back(cnt[i]);
		}
	}
	f[0][0] = 0;
	for(int i = 1, len = b.size() - 1 ; i <= len ; i ++) {
		for(int j = 0 ; j <= i ; j ++) {
			f[i][j] = f[i - 1][j];
			if(b[i] <= j && i - j >= f[i - 1][j - b[i]] + 1) {
				f[i][j] = max(f[i][j], f[i - 1][j - b[i]] + 1);
			}
		}
	}
	for(int i = 1, len = b.size() - 1 ; i <= len ; i ++) {
		sum = max(sum, f[len][i]); 
	}
	cout<<b.size() - 1 - sum<<endl;
    return;
} 
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	cin>>t;
	while(t --) {
		solve();
	}
	return 0;
}

```

---

