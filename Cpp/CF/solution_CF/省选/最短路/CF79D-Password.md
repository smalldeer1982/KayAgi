# Password

## 题目描述

Finally Fox Ciel arrived in front of her castle!

She have to type a password to enter her castle. An input device attached to her castle is a bit unusual.

The input device is a $ 1×n $ rectangle divided into $ n $ square panels. They are numbered $ 1 $ to $ n $ from left to right. Each panel has a state either ON or OFF. Initially all panels are in the OFF state. She can enter her castle if and only if $ x_{1} $ -th, $ x_{2} $ -th, $ ... $ , $ x_{k} $ -th panels are in the ON state and other panels are in the OFF state.

She is given an array $ a_{1} $ , $ ... $ , $ a_{l} $ . In each move, she can perform the following operation: choose an index $ i $ ( $ 1<=i<=l $ ), choose consecutive $ a_{i} $ panels, and flip the states of those panels (i.e. ON $ → $ OFF, OFF $ → $ ON).

Unfortunately she forgets how to type the password with only above operations. Determine the minimal number of operations required to enter her castle.

## 说明/提示

One possible way to type the password in the first example is following: In the first move, choose 1st, 2nd, 3rd panels and flip those panels. In the second move, choose 5th, 6th, 7th, 8th, 9th panels and flip those panels.

## 样例 #1

### 输入

```
10 8 2
1 2 3 5 6 7 8 9
3 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 2 1
1 2
3
```

### 输出

```
-1
```

# 题解

## 作者：Licykoc (赞：22)

# 题意

给定一个01序列，有 $m$ 种长度，每次可以让一段长度为 $a_i$ 的字串翻转，求让序列归零的最少次数。

# $\mathcal{Sol:}$

第一眼看见这题时会感觉无从下手对吧，其实从数据范围可以给予一定启发。

发现到 $k \le 10$ ,这么小的范围，很明显就是状压dp。

然鹅状压dp跟此题有个半毛钱的关系啊（目前），但我们可以试着将问题转化。

## 转化:

题目中的修改操作为区间修改，这很容易联想到线段树，但是他的常数大，且代码实现困难~~菜是原罪~~，我们可以使用**差分**。

如果你对差分并不了解，可以自行bfs，其中有详细的解释，这里不再阐述。

本题使用的是**异或差分**，其代码为 $a_i=a_i\ xor\ a_{i+1}\ \ (i\ge 0)$ 。 

以样例1为例：

原始序列： 01110111110 （为了方便在开头处加了个0）

差分序列： 10011000010  

手玩一下可以发现在原序列中翻转 $(l,r)$ 区间就等于在差分序列中取反 $b_{l-1}, b_r$ 。

这样就可以将修改操作变为 $\mathcal{O(1)}$ 的了，且题目变为：

---

给定一个01串,每次操作为：

**从给定的 $m$ 种长度中选择一种，选择序列上相距这个长度的两个位同时取反。**

求让序列归零的最少次数。

---

到这里一步时我们终于可以使用关于 $k$ 的状压dp辣！

- Q:  Why?

- A:  因为在差分后的序列中我们只关心的是其中的1，而其中最多也只有 $2\times k$ 个1，所以大力状压即可。


我们设 $dp_i$ 为当前状态为 $i$ 下所需的最小次数，$x$ 和 $y$ 为当前状态下未被选过的位，那么显而易见：
$$dp_{i | (1<<x) | (1<<y)} = min(dp_{i | (1<<x) | (1<<y)},dp_i + Cost(x,y)) $$

其中 $Cost(x,y)$ 即将 $x$ 和 $y$ 位同时变为0所需的最小次数。

每一次循环都计算一次的话肯定会T,所以我们可以**预处理**出这个数组。

我们可以对差分序列中1的位置进行一次spfa，这样的话这题就愉快的解决辣！

# $Code:$

```cpp
//Code by Licykoc  2020.11.19 
#include <bits/stdc++.h>
#define int long long
#define Get getchar()
inline void read (int &x){
	char c=Get; int w=1; x=0;
	while (!isdigit(c)) {if (c=='-') w=-1; c=Get;}
	while (isdigit(c)) {x=(x*10)+(c^48),c=Get;};
	x*=w;
}
using namespace std;
typedef long long ll;
int n,m,k,x,y,tot=0;
int a[100001],b[100001];
int q[200001][2];
//q[x][0]表示第x个1在此序列中的位置，q[x][1]表示第x个1在原序列中的下标
int f[201][100001];
int Q[100001];
int dp[10000001];
signed main(){
	read(n); read(m); read(k);
	for (int i=1;i<=m;++i) read(x),a[x]=1;
	for (int i=1;i<=k;++i) read(b[i]);
	for (int i=0;i<=n;++i) a[i]^=a[i+1]; //差分序列
	for (int i=0;i<=n;++i) if (a[i]) q[tot][0]=tot,q[tot][1]=i,tot++; //将所有1的位置保存在q数组中
	
   //---------------------SPFA & START-----------------------
	
	for (int i=0;i<tot;++i){ 
	    //这里的spfa每次转移时的权值为1，所以不需要记录该点是否已在队列内 
		for (int j=0;j<=n;++j) f[q[i][0]][j]=0x7FFFFFFF;
		f[q[i][0]][q[i][1]]=0;
		int l=1,r=1;
		Q[1]=q[i][1];
		while (l<=r) {
			int x=Q[l];
			for (int j=1;j<=k;++j) {
				if (x-b[j]>=0&&f[q[i][0]][x]+1<f[q[i][0]][x-b[j]]) {
					f[q[i][0]][x-b[j]]=f[q[i][0]][x]+1;
					r++; Q[r]=x-b[j];
				}
				if (x+b[j]<=n&&f[q[i][0]][x]+1<f[q[i][0]][x+b[j]]) {
					f[q[i][0]][x+b[j]]=f[q[i][0]][x]+1;
					r++; Q[r]=x+b[j];
				}
			}
			l++;
		}
	}
	
	//---------------------SPFA & END-----------------------
    
	memset(dp,127,sizeof(dp));
	dp[0]=0;
	int Mx=(1ll<<tot)-1;
	for (int i=0;i<=Mx;++i) {
		x=0; 
		while ((i>>x)&1ll) x++;
		for (y=x+1;y<tot;++y) if (!((i>>y)&1ll))  
			dp[i|(1ll<<x)|(1ll<<y)]=min(dp[i|(1ll<<x)|(1ll<<y)],dp[i]+f[x][q[y][1]]);
	}
	
	printf("%lld\n",dp[Mx]>1e9?-1:dp[Mx]); //-1千万不要忘辣！ 
}
```

---

## 作者：shadowice1984 (赞：21)

51nod上某题的弱化版中的弱化版

原题需要跑一般图最小权匹配这种十分不可写的东西……

不过这题因为就20个点，大力状压dp即可通过本题
_________________________

好了题目意思简单明了……给定一个初始状态全0的串然后可以对长度为一些特定值的区间进行01翻转操作，求将这个串变成给定的串至少需要几次操作

特殊限制是目标串当中最多有10个1

# 本题题解

那么我们来看，如果我们可以通过一通操作将原串翻转成目标串，那么我们将这些操作全部倒过来做就会把目标串翻转成一个全0串

所以问题变成了如何使用最少的操作次数将目标串变成全0的

那么我们发现我们唯一可以做到的操作就是区间取反这个操作

区间取反是等于区间异或上1的而区间异或上1相当于在模2剩余系下进行区间+

那么我们的目标是通过一系列区间+将这个目标串清0

区间加太麻烦了，我们考虑把区间加变成单点修改，发现好像的确可办到……，众所周知，区间加是等于在差分数组上进行两次单点修改的，所以我们把目标串在模2剩余系下差分一下，那么问题就变成了我们可以给间距为一些特定值的两个点进行翻转，求最小的翻转次数使得所有点都变成0，(因为差分全0的数组一定是全0数组，并且全0数组的差分数组都是全为0的)

那么这个问题该怎么求解呢？

这就是一个经典套路了，通过一系列骚操作把这个问题转化成一般图的最小权匹配问题

我们进行这样一个转化，如果我们可以通过一次操作将$(i,j)$翻转的话，我们就在$(i,j)$之间连上一条边，那么**同时翻转u,v而不影响其他点的状态**这个操作的代价就是$(u,v)$之间的最短路

证明非常简单，首先由于最短路径一定是一个简单路径，所以除了u，v之外这条路径上的点恰好有两条最短路上的边和它相连，换句话说这个点被翻转了两次，状态自然是不变的，而u和v恰好有一条边和他们相连，所以恰好被翻转了

那么现在我们就可以处理出所有1两两间的最短路，这题由于最多20个1并且边权全部是单位边权所以我们可以大力从每个起点开始bfs一发求出所有1之间的最短路

设第i个1和第j个1之间的最短路为$dis_{i,j}$那么我们可以发现最优的方案一定是把这些1一对一对的翻转然后消掉(因为借助别的1作为一个跳板进行翻转这种情况已经在最短路中被考虑过了)

也就是说，如果我们在$i,j$之间连一条长度为$dis_{i,j}$的边，来建一张新图的话，我们的最小代价就是这张图的**最小权完美匹配**，之所以强调是完美匹配是因为如果这张图不存在完美匹配的话，我们就无法通过翻转一堆点对的方式来完成将所有1消掉了(比如说奇数个点的话就一定没有完美匹配了)

当然这道题是没必要去写鬼畜的一般图最小权完美匹配了，因为我们发现最多有20个1

这就十分nice了，设$dp_{S}$表示将S这个集合消成0的最小消去步数，大力状压dp进行转移即可

最后一个问题，我们维护前向差分也好后向差分也罢，都会出现在处理前缀/后缀翻转的时候只是改变了一个差分点的辣手情况，解决这个问题也很简单，我们在序列的最前端/末尾补一个0点带着一起差分，这样的话差分数组的长度变成n+1，此时我们进行任意的翻转都是同时翻转两个点了，也就可以进行状压dp了

上代码~

```C
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;const int N=1e4+10;const int P=1048576+10;const int Y=30;typedef long long ll;
int tr[N];int cnt;int cf[N];int a[N];int n;int m;int k;int cst[Y][Y];int d[N];int dp[P];queue <int> q;
inline void bfs(int s)//大力bfs求出最短路 
{
    for(int i=1;i<=n+1;i++)d[i]=0x3f3f3f3f;d[s]=0;int nw;int i=1;
    for(q.push(s);!q.empty();)
        for(nw=q.front(),q.pop(),i=1;i<=m;i++)
        {
            int v1=nw+a[i];if(v1<=n+1&&d[v1]==0x3f3f3f3f)d[v1]=d[nw]+1,q.push(v1);
            int v2=nw-a[i];if(v2>=1&&d[v2]==0x3f3f3f3f)d[v2]=d[nw]+1,q.push(v2);
        }
    for(int i=1;i<=n+1;i++)if(tr[i]!=-1)cst[tr[s]][tr[i]]=d[i];
}
int main()
{
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1,t;i<=k;i++){scanf("%d",&t);cf[t]=1;}
    for(int i=1;i<=m;i++)scanf("%d",&a[i]);
    for(int i=n+1;i>=1;i--)cf[i]^=cf[i-1];cnt=-1;//求差分数组 
    for(int i=1;i<=n+1;i++)tr[i]=-1;
    for(int i=1;i<=n+1;i++)if(cf[i])tr[i]=++cnt;
    for(int i=1;i<=n+1;i++)if(cf[i])bfs(i);
    for(int i=1;i<(1<<(cnt+1));i++)dp[i]=0x3f3f3f3f;
    for(int i=0;i<(1<<(cnt+1));i++)//大力状压dp 
    {
        if(dp[i]==0x3f3f3f3f)continue;
        for(int j=0;j<=cnt;j++)
        {
            if((i>>j)&1)continue;
            for(int k=j+1;k<=cnt;k++)
                if(((i>>k)&1)==0)dp[i+(1<<j)+(1<<k)]=min(dp[i+(1<<j)+(1<<k)],dp[i]+cst[j][k]);
        }
    }int ans=dp[(1<<(cnt+1))-1];
    printf("%d",(ans==0x3f3f3f3f)?-1:ans);return 0;//拜拜程序~ 
}
```









---

## 作者：Resurgammm (赞：12)

原问题就是：

> 给定长度为 $n$ 的 $01$ 序列 $a_{1\dots n}$ 有 $k$ 个位置为 $1$，其余为 $0$，共有 $m$ 种操作，每个操作可以反转长度 $l_i$ 的区间，求将 $a$ 清零的最小操作数。


感觉每次扫一下 $\otimes 1$ 很麻烦，可以考虑一下差分，即：

$$b_i=a_i\otimes a_{i+1}$$

那么对 $a$ 数组 $[l,r]$ 区间反转就等价于让差分数组的 $b_{l-1}\gets b_{l-1}\otimes 1,b_r\gets b_r\otimes 1$。

由于每次抑或最多会生成两个 $1$，所以最多也就有 $2k$ 个 $1$，那么问题就转化为了：

> 给定一个长度为 $2k$ 的 $01$ 序列 $b_{0\dots 2k-1}$，其中最多有 $2k$ 个 $1$，共有 $m$ 个操作，每个操作可以选择距离为 $l_i$ 的两点，将其反转，求将 $b$ 清零的最小操作数。

设选择的一对位置为 $(x,y)$，进行分类讨论：

* 若 $b_x=0,b_y=0$，则操作后 $b_x=1,b_y=1$。

* 若 $b_x=1,b_y=1$，则操作后 $b_x=0,b_y=0$。

* 若 $b_x=1,b_y=0$，则操作后 $b_x=0,b_y=1$。

* 若 $b_x=0,b_y=1$，则操作后 $b_x=1,b_y=0$。

发现情况一会使答案更劣，情况二会使答案更优，情况三和情况四不会对答案有影响。

所以只需要考虑情况二即可。

可以对任意 $i$ 和 $i+l_j$ 连一条边权为 $1$ 的无向边，那么问题转化为了：

> 给定一个有 $n+1$ 个节点的图（编号为 $0\sim n$）当 $\texttt{dis}(x,y)=l_i$ 时，存在边 $\texttt{edge}(x,y)$，初始时最多有 $2k$ 个节点上有标记，每次可以沿边移动标记，两个标记相遇就会消失，求使所有标记消失的最少移动次数。

那么差分数组中 $b_{l-1}\gets b_{l-1}\otimes 1,b_r\gets b_r\otimes 1$ 的最小操作次数就是图中 $l-1$ 和 $r$ 之间的最短路，记做 $\texttt{cost}(l-1,r)$。

则对原序列 $[l,r]$ 进行区间反转的最小操作次数就是 $\texttt{cost}(l-1,r)$。

因为边权全是 $1$，所以跑 $n$ 遍 $bfs$ 就可以求出 $\texttt{cost}$，时间复杂度 $O(nmk)$。

然后因为 $2k\leq 16$ ，可以考虑状压 $DP$，只有差分数组中的 $1$ 会对答案有贡献。

设 $f_{sta}$ 为标记点状态为 $sta$ 时的最小操作次数，两个需要消除的标记位置分别为 $i,j$，有：

$$f_{sta}=\min\{f_{sta-2^i-2^j}+\texttt{cost}(i,j)\}$$

设 $tot$ 为初始时标记点的个数，答案为 $f_{2^{tot}-1}$。

时间复杂度为 $O(nmk+k2^{2k})$。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=4e4+5,maxk=20,inf=0x3f3f3f3f;
	
	int n,k,m,tot,ans;
	int a[maxn],op[105],dis[maxn],cost[maxk][maxk],id[maxn],f[1<<maxk];
	bool vis[maxn];
	queue<int> q;
	void spfa(int s){
		for(int i=0;i<=n;i++) dis[i]=inf,vis[i]=0;
		dis[s]=0; vis[s]=1;
		q.push(s);
		while(!q.empty()){
			int u=q.front(); q.pop();
			for(int i=1;i<=m;i++){
				int v1=u+op[i],v2=u-op[i];
				if(v1<=n && !vis[v1]){
					dis[v1]=dis[u]+1;
					vis[v1]=1; q.push(v1);
				}
				if(v2>=0 && !vis[v2]){
					dis[v2]=dis[u]+1;
					vis[v2]=1; q.push(v2);
				}
			}
		}
		for(int i=0;i<=n;i++)
			if(a[i]) cost[id[s]][id[i]]=dis[i];
	}
	
	inline int main(){
		n=read(); k=read(); m=read();
		for(int i=1;i<=k;i++) a[read()]=1;
		for(int i=1;i<=m;i++) op[i]=read();
		for(int i=0;i<=n;i++) a[i]^=a[i+1],id[i]=a[i]?tot++:0;
		for(int i=0;i<=n;i++) if(a[i]) spfa(i);
		for(int sta=1;sta<(1<<tot);sta++){
			f[sta]=inf;
			for(int i=0;i<tot;i++){
				if(!((sta>>i)&1)) continue;
				for(int j=i+1;j<tot;j++){
					if(!((sta>>j)&1)) continue;
					f[sta]=min(f[sta],f[sta-(1<<i)-(1<<j)]+cost[i][j]);
				}	
			}		
		}
		printf("%d\n",f[(1<<tot)-1]==inf?-1:f[(1<<tot)-1]);
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：Itst (赞：8)

### [双倍经验](https://www.luogu.org/problemnew/show/P3943)
### 看到区间取反操作，除了线段树之外，还能够想到一种加速的方式：差分。我们将无需点亮的看做$0$，需要点亮的看做$1$，那么原序列就变成了一个$01$序列。我们在最后补上一个$0$，然后对其进行差分，这样原序列的一段$1$就对应了差分数组上的两个$1$（如果最后不补$0$那么原串结尾的$1$在差分数组上就只会有一个$1$，对于之后的操作就比较麻烦）
### 考虑每一次区间取反操作的实质，长度为$K$的区间取反操作在差分数组上体现为两个间隔为$K$的数取反。显然将两个$0$变成$1$不会是最优情况，那么我们可以认为：在差分数组上对于一个$0$和一个$1$的一次区间取反操作就是$1$向旁边走了$K$格，而两个$1$的取反操作就是两个$1$走到了一起然后被消除。
### 发现需要点亮的点最多只有$10$个，那么差分数组中的$1$最多只有$20$个，那么我们可以通过最短路计算差分数组上第$i$个$1$和第$j$个$1$走到一起的最小操作次数$f_{i,j}$；然后通过状压$DP$计算消除$i$集合中的$1$的操作次数$g_i$，大力转移即可。
```
#include<bits/stdc++.h>
using namespace std;
bool vis[40010];
int N , M , K , num[110] , cnt[20] , minDis[40010] , minN[31][31] , dp[1 << 21 + 1] , cnt1[1 << 21 + 1];
queue < int > q;

inline void Dijk(int dir){
    memset(minDis , 0x3f , sizeof(minDis));
    minDis[cnt[dir]] = 0;
    q.push(cnt[dir]);
    while(!q.empty()){
        int t = q.front();
        q.pop();
        for(int i = 1 ; i <= K ; i++){
            if(t + num[i] <= N + 1 && minDis[t + num[i]] > minDis[t] + 1){
                minDis[t + num[i]] = minDis[t] + 1;
                q.push(t + num[i]);
            }
            if(t - num[i] > 0 && minDis[t - num[i]] > minDis[t] + 1){
                minDis[t - num[i]] = minDis[t] + 1;
                q.push(t - num[i]);
            }
        }
    }
    for(int i = 1 ; i <= cnt[0] ; i++)
        minN[dir][i] = minDis[cnt[i]];
}

int main(){
    cin >> N >> M >> K;
    for(int i = 1 ; i <= M ; i++){
        int a;
        cin >> a;
        vis[a] = 1;
    }
    for(int i = 1 ; i <= N + 1 ; i++)
        if(vis[i] ^ vis[i - 1])
            cnt[++cnt[0]] = i;
    if(cnt[0] == 0){
        cout << 0;
        return 0;
    }
    for(int i = 1 ; i <= K ; i++)
        cin >> num[i];
    for(int i = 1 ; i <= cnt[0] ; i++)
        Dijk(i);
    for(int i = 1 ; i < 1 << cnt[0] ; i++)
        cnt1[i] = cnt1[i - (i & -i)] + 1;
    memset(dp , 0x3f , sizeof(dp));
    dp[0] = 0;
    for(int i = 0 ; i < (1 << cnt[0]) ; i++)
        if(!(cnt1[i] & 1)){
            int t = ((1 << cnt[0]) - 1) ^ i;
            if(t == 0){
                cout << (dp[i] == 0x3f3f3f3f ? -1 : dp[i]);
                return 0;
            }
            t = log2(t & -t) + 1;
            for(int j = t + 1 ; j <= cnt[0] ; j++)
                if(!(i & (1 << j - 1)))
                    dp[i | (1 << t - 1) | (1 << j - 1)] = min(dp[i | (1 << t - 1) | (1 << j - 1)] , dp[i] + minN[t][j]);
        }
    return 0;
}
```


---

## 作者：2huk (赞：7)

> - 你有 $n$ 个灯泡，一开始都未点亮。
>
>   同时你有 $l$ 个长度，分别为 $a_1 \sim a_l$。
>
>   每次你可以选择一段连续的子序列，且长度为某个 $a_i$，并将这些灯泡的明灭状态取反。
>
>   求最少的操作次数，使得最后有且仅有 $k$ 个位置是亮的，这些位置已经给定，为 $x_1 \sim x_k$。
>
> - $n \le 10^4$，$k \le 10$，$l \le 100$。

设 $n$ 个灯泡的开关状态为 $b_1 \sim b_n$。若 $b_i = 1$ 表示第 $i$ 盏灯开启，$b_i = 0$ 表示第 $i$ 盏灯关闭。

第一个观察是，我们从 $b_1 = b_2 = \dots = b_n = 0$ 变化成所有 $b_{x_i} = 1$ 的局面，等价于从所有 $b_{x_i} = 1$ 变化成 $b_1 = b_2 = \dots = b_n = 0$ 的局面。

所以最开始我们让所有 $b_{x_i} \gets 1$。现在的问题是：

> 给定 $a, b$。每次可以选择一个 $b$ 的区间 $[x, x + a_i - 1]$ 取反。求将 $b$ 全部变为 $0$ 的最少操作数。

区间反转用差分维护。令 $b$ 的差分数组为 $c_1 \sim c_{n+1}$，即 $c_i = b_i \operatorname{xor} b_{i-1}$。那么将区间 $[l, l + a_k - 1]$ 取反等价于将 $c_l, c_{l+a_k}$ 取反。

显然当 $c_1 = c_2 = \dots = c_{n+1} = 0$ 时，我们的任务就完成了。现在的问题是：

> 给定 $a, c$。每次可以选择一个 $c$ 的区间 $[x, x + a_i]$，并将 $c_x, c_{x+a_i}$ 取反。求将 $c$ 全部变为 $0$ 的最少操作数。

显然我们只需要考虑那些为 $1$ 的位置，即 $\{i \mid c_i = 0\}$。因为操作 $\{i \mid c_i = 1\}$ 显然是不优的。

若令 $g(x, y)$ 表示将 $x, y$ 同时反转的最小的所需次数。

考虑状压 DP。令 $S$ 表示当前 $c$ 中仍为 $1$ 的下标集合，设 $f(S)$ 表示在状态 $S$ 的情况下，将 $c$ 全部变为 $0$ 的最少操作次数。

转移显然：
$$
f(S) = \min_{u, v \in S}\{f(S/u/v) + g(u, v)\}
$$
答案为 $f(\{x \mid c_x = 1\})$。

考虑 $g(x, y)$ 的求解。举个例子，如果我们可以同时将 $c_x, c_{x+a}$ 取反，也可以同时将 $c_{x+a}, c_{x+a+b}$ 取反，那么我们就可以通过两次操作，同时将 $c_x, c_{x+a+b}$ 取反。

具体的，考虑建图。对于一条边 $u \longleftrightarrow v$ 表示可以通过一次操作将 $u, v$ 同时取反，那么这张图上 $x \to y$ 的最短路即 $g(x,y)$。

```cpp
#include <bits/stdc++.h>

constexpr int N = 10009, K = 22, L = 209;

int n, k, l, x[K], a[L];
bool b[N], c[N];
int mp[L][L];
int Id[N], Di[N], cnt;
int f[1 << K];

struct Gragh {
	int h[N], e[N * L], ne[N * L], idx = 1;
	
	void add(int a, int b) {
		e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
		e[idx] = a, ne[idx] = h[b], h[b] = idx ++ ;
	}
	
	int dis[N];
	bool st[N];
	
	void bfs(int s) {
		std::queue<int> q;
		q.push(s);
		
		memset(dis, 0x3f, sizeof dis);
		memset(st, 0, sizeof st);
		
		dis[s] = 0;
		st[s] = true;
		
		while (q.size()) {
			int u = q.front();
			q.pop();
			
			for (int i = h[u]; i; i = ne[i]) {
				int v = e[i];
				if (!st[v]) {
					st[v] = true;
					dis[v] = dis[u] + 1;
					q.push(v);
				}
			}
		}
		
		for (int i = 1; i <= n + 1; ++ i )
			if (c[i]) mp[Di[s]][Di[i]] = dis[i];
	}
}G;

int dp(int S) {
	if (!S) return 0;
	if (f[S]) return f[S];
	
	int &res = f[S];
	res = 1e9;
	
	for (int i = 0; i < cnt; ++ i )
		if (S >> i & 1)
			for (int j = 0; j < cnt; ++ j )
				if (S >> j & 1)
					res = std::min(res, dp(S ^ (1 << i) ^ (1 << j)) + mp[i][j]);
	
	return res;
}

int main() {
	std::cin >> n >> k >> l;
	
	for (int i = 1; i <= k; ++ i ) {
		std::cin >> x[i];
		b[x[i]] = true;
	}
	
	for (int i = 1; i <= n + 1; ++ i ) {
		c[i] = b[i] ^ b[i - 1];
	}
	
	for (int i = 1; i <= l; ++ i ) {
		std::cin >> a[i];
	}
	
	for (int i = 1; i <= n + 1; ++ i )
		if (c[i]) Id[cnt ++ ] = i, Di[i] = cnt - 1;
	
	for (int i = 1; i <= n + 1; ++ i )
		for (int j = 1; j <= l; ++ j )
			if (i + a[j] <= n + 1) G.add(i, i + a[j]);
	
	for (int i = 1; i <= n + 1; ++ i )
		if (c[i]) G.bfs(i);

	std::cout << (dp((1 << cnt) - 1) == 1e9 ? -1 : f[(1 << cnt) - 1]) << '\n';
	
	return 0;
}
```

---

## 作者：kcn999 (赞：5)

题目可以看作有一个长度为 $n$ 的 $01$ 串，有 $k$ 位为 $1$，其余为 $0$。每次操作相当于区间 $\oplus 1$，求变成全 $0$ 串的最小操作次数。

操作为区间修改，那么考虑对原 $01$ 串进行差分。
例如给定一个原串为 $\color{red}{0}\color{black}{10001}\color{red}{0}$，这里设第 $0$ 位和第 $n+1$ 位都为 $0$，用红色数字表示。      
则差分之后是 $\color{red}{0}\color{black}{11001}\color{red}{1}$，即设原串第 $i$ 位为 $a_i$，差分后新串第 $i$ 位为 $d_i$，则 $a_i=d_0\oplus d_1\oplus d_2\oplus \cdots \oplus d_i$。   
这个时候我们考虑，对原串 $[l,r]$  进行区间 $\oplus1$，其实就相当于令新串的 $d_l\gets d_l\oplus1,d_{r+1}\gets d_{r+1}\oplus 1$。

变化有 $4$ 种情况：
1. 若 $d_l=d_{r+1}=0$，则相当于把这两位变成 $1$，增加 $2$ 个 $1$。
2. 若 $d_l=d_{r+1}=1$，则相当于把这两位变成 $0$，减少 $2$ 个 $0$。
3. 若 $d_l=1,d_{r+1}=0$，则相当于把 $l$ 上的 $1$ 移到 $r+1$，$1$ 数量不变。
4. 若 $d_l=0,d_{r+1}=1$，则相当于把 $r+1$ 上的 $1$ 移到 $l$，$1$ 数量不变。

那我们可以对任意 $i$ 和 $i+b_j$ 连一条边权为 $1$ 的无向边，则新串中 $d_l\gets d_l\oplus 1,d_{r+1}\gets d_{r+1}\gets 1$ 的最小操作次数为 $l$ 到 $r+1$ 的最短路，记作 $\textit{dis}(l,r+1)$。则对原串 $[l,r]$ 进行区间 $\oplus1$ 的最小操作次数为 $\textit{dis}(l,r+1)$。因为边权为 $1$，所以求最短路跑 $n$ 次 BFS 即可。    
容易得到，新串变为全 $0$ 串是原串变为全 $0$ 串的充要条件。

考虑 $k$ 很小，实际上新串中初始最多只有 $2k$ 个 $1$，而其他的 $0$ 我们根本就不用管，也就是说只用计这 $2k$ 个 $1$。则新串只有 $2^{2k}$ 种状态，直接上状压 dp。    
设 $f(S)$ 为新串状态为 $S$ 时的最小操作次数，预处理出新串的初始状态 $\textit{st}$，则 $f(\textit{st})=0$。    
显然每次转移，进行上面的第 $1,3,4$ 种变化是没有意义的，所以只需要做第 $2$ 种变化（即转移中，只转移第 $2$ 种变化，实际上已经包括了其他 $3$ 种）。    
设 $T=S-2^{i-1}-2^{j-1}$，则 $f(T)=\min \{f(S)+\textit{dis}(i,j)\}$。答案即为 $f(0)$。   
同样的，我们在 BFS 的时候，只用从初始值为 $1$ 的位开始搜，那么最多跑 $2k$ 遍 BFS。   
时间复杂度为 $O(2knm+2^{2k}(2k)^2)$。   

实际上每次转移的时候，$i$ 可以只取 $S$ 中 $1$ 的最低位（无论如何都要转移这个最低位，那么可以先转移）。   
时间复杂度为 $O(2knm+2^{2k} (2k))$。


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N (10000 + 5)
#define MAX_M (100 + 5)
#define MAX_K (10 + 5)
#define MAX_S ((1 << 20) + 5)
using std::min;

int n, m, k;
int a[MAX_K * 2], len;
int b[MAX_M];
int dis[MAX_N];
int g[MAX_K * 2][MAX_K * 2];
int q[MAX_N], l, r;
bool vis[MAX_N];
int f[MAX_S];

void BFS() {
	int u, v;
	for (int I = 1; I <= len; ++I) {
		memset(dis, 0x3f, sizeof dis);
		memset(vis, 0, sizeof vis);
		l = r = 1;
		dis[a[I]] = 0;
		vis[a[I]] = 1;
		q[1] = a[I];
		while (l <= r) {
			u = q[l++];
			for (int i = 1; i <= m; ++i) {
				v = u - b[i];
				if (v >= 1 && !vis[v]) {
					dis[v] = dis[u] + 1;
					vis[v] = 1;
					q[++r] = v;
				}
				v = u + b[i];
				if (v <= n + 1 && !vis[v]) {
					dis[v] = dis[u] + 1;
					vis[v] = 1;
					q[++r] = v;
				}
			}	
		}
		for (int i = 1; i <= len; ++i)
			g[I][i] = dis[a[i]];
	}
}

int main() {
	scanf("%d%d%d", &n, &k, &m);
	int pos;
	for (int i = 1; i <= k; ++i) {
		scanf("%d", &pos);
		vis[pos] ^= 1;
		vis[pos + 1] ^= 1;
	}
	for (int i = 1; i <= n + 1; ++i)
		if (vis[i]) a[++len] = i;
	for (int i = 1; i <= m; ++i)
		scanf("%d", &b[i]);
	BFS();
	const int lim = (1 << len) - 1;
	memset(f, 0x3f, sizeof f);
	f[lim] = 0;
	int tmp, T;
	for (int S = lim; S; --S) {
		tmp = S;
		pos = 1;
		while ((tmp & 1) == 0) {
			++pos;
			tmp >>= 1;
		}
		for (int i = pos + 1; i <= len; ++i) {
			if ((S & 1 << i - 1) == 0) continue;
			T = S ^ 1 << pos - 1 ^ 1 << i - 1;
			f[T] = min(f[T], f[S] + g[pos][i]);
		}
	}
	if (f[0] == 0x3f3f3f3f) printf("-1\n");
	else printf("%d", f[0]);
	return 0;
}
```


---

## 作者：Tang_poetry_syndrome (赞：3)

## [CF79D] Password 
思维好题。
### 题意
给定一个长度为 $n$ 的零一序列，并给定 $m$ 个操作，第 $i$ 个操作可以将序列中长度为 $len_i$ 的子序列元素反转，求将原串改为前 $k$ 项为 $1$，后面都为 $0$，所需的最小操作次数。
### 思路
首先像开关灯这样 $1$ 和 $0$ 的变化适宜用异或差分解决，即 $op_i = op_i \oplus 1$。  
这里我们对异或的进行简单的介绍：异或是一种位运算，异或的基本规则为 $a \oplus b = \begin{cases}0(a=b)\\1(a \ne b)\end{cases}$。  
然后题目要求区间修改，容易想到两种方式：线段树、差分，差分显然会更简单，并且效率更高。  
我们将原问题放在差分数组上进行，则对区间 $[l,l+len-1]$ 进行操作与对差分区间 $[l,l+len]$ 操作等效。  
现在，题意转化为将差分序列中相隔距离为 $x(x\in len)$ 的值取反，求将序列归零的最小次数。分析数据范围 $k\le10$，无疑是很适合状态压缩这种暴力的算法的，但是有一些小区间可以通过给出长度的拼凑取得，但是直接跑 DP 会超出范围限制，举个栗子：$n=5,len=\{4,5\},op=\{1,0,1,0,0\}$ 。   
为了熄灭所有灯，我们在理想状态下应该将 $(1,5),(2,5),(2,6),(3,6)$ 四组点对取反，但是实际上并没有第六个灯泡，所以需要预处理出每个点能达到的点，再跑 DP。  
最后推柿子，我们设 $dp_i$ 为所有灯泡状态在十进制下为 $i$ 所要转换的最小次数，那么当 $x,y$ 两位都没有熄灭，且这两个点的可以通过长度拼凑出来，那么就从 $i|2^x|2^y$ 处转移到 $i$，那么如果将 $x$ 到 $y$ 的代价记作 $cst_{x,y}$，据上所述，容易得出 $dp_i=\min(dp_{i|2^{x-1}|2^{y-1}}+cst_{x,y})$。  
因为我们是从初始状态推到全为零，所以**通过倒推才能计算出中间状态的代价**，进而计算出正确答案。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y) 
const int N=4e4+10,INF=0x3f3f3f3f;
int n,m,k,x,len[N],dis[N],dp[(1<<20)+5],cst[20][20];
vector<int>pos;
bool op[N];
void gtmin(int a,int &b){if(a<b)b=a;}
void bfs(int x)
{
	queue<int>q;
	while(!q.empty())q.pop();
	memset(dis,INF,sizeof dis);
	q.push(pos[x]);
	dis[pos[x]]=0;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		f(i,1,k){
			int l=now-len[i],r=now+len[i];
			if(l>0&&dis[l]==INF){
				dis[l]=dis[now]+1;
				q.push(l);
			}
			if(r<=n+1&&dis[r]==INF){
				dis[r]=dis[now]+1;
				q.push(r);
			}
		}
	}
	if(pos.empty())return;
	f(i,0,pos.size()-1)if(dis[pos[i]]!=INF)cst[x][i]=dis[pos[i]];
	return ;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	f(i,1,m)cin>>x,op[x]^=1,op[x+1]^=1;
	f(i,1,k)cin>>len[i];
	f(i,1,n+1)if(op[i])pos.pb(i);
	memset(cst,INF,sizeof cst);
	memset(dp,INF,sizeof dp);
	//-------------------Init--------------------
	if(!pos.empty())f(i,0,pos.size()-1)bfs(i);
	//-------------------BFS---------------------
	dp[(1<<pos.size())-1]=0;
	g(i,(1<<pos.size())-1,0){
		f(j,0,pos.size()-1){
			if(!((1<<j)&i))continue;
			f(k,j+1,pos.size()-1){
				if(!((1<<k)&i))continue;
				gtmin(dp[i]+cst[j][k],dp[~((~i)|(1<<j)|(1<<k))]);
			}
		}
	}
	if(dp[0]!=INF)cout<<dp[0];
	else cout<<-1;
	return 0;
}
```
（手动求赞 awa)

---

## 作者：SunsetSamsara (赞：3)

## 前置知识

状压 dp，最短路 / bfs

## 分析

首先看到数据范围和大概题意就能联想到状压 dp

但是，直接状压 dp 的话会发现无从下手。

所以，我们要转换这个连续子序列的修改。发现连续子序列取反可以通过**异或差分**转换为两个单点修改的形式，于是就可以套路出最短路的做法：

+ 通过异或差分找到翻转任意两个点的代价

+ 跑一遍 bfs 最短路，此时第 $i$ 个 $1$ 和第 $j$ 个 $1$ 的距离为 $dis_{ij}$，则同时消掉两个 $1$ 的最少代价方式就是在 $i$ 到 $j$ 的最短路上沿路径一个一个消。

+ 最后就很简单了，直接状压 dp，利用最短路跑出的最少代价，对于每一个状态 $i$，尝试利用 $i$ 上没有的两位进行更新，最后算出来的全为 $1$ 的状态就是答案。

+ 因为权值都是 $1$ 所以可以 bfs

## 代码

```cpp
#include <stdio.h>
#include <queue>
using namespace std;
const int N = 10010, M = 30, F = 1048586;
const int inf = 0x3f3f3f3f;
int tr[N], cnt;
int df[N], a[N];
int n, m, k;
int cst[M][M];
int d[N], f[F];
queue<int> q;
void bfs(int s) {
	for (int i = 1; i <= n + 1; ++ i) d[i] = inf;
	d[s] = 0;
	int u;
	q.push(s);
	for (; !q.empty(); ) {
		u = q.front(), q.pop();
		for (int i = 1, v1, v2; i <= m; ++ i) {
			v1 = u + a[i]; if (v1 <= n + 1 && d[v1] == inf) d[v1] = d[u] + 1, q.push(v1);
			v2 = u - a[i]; if (v1 >= 1 && d[v2] == inf) d[v2] = d[u] + 1, q.push(v2);
		}
	}
	for (int i = 1; i <= n + 1; ++ i) if (~tr[i]) cst[tr[s]][tr[i]] = d[i];
}
int main() {
	scanf("%d%d%d", &n, &k, &m);
	for (int i = 1, t; i <= k; ++ i) scanf("%d", &t), df[t] = 1;
	for (int i = 1; i <= m; ++ i) scanf("%d", a + i);
    for (int i = n + 1; i >= 1; -- i) df[i] ^= df[i - 1];
    cnt = -1;
	for (int i = 1; i <= n + 1; ++ i) tr[i] = -1;
	for (int i = 1; i <= n + 1; ++ i) if (df[i]) tr[i] = ++ cnt;
	for (int i = 1; i <= n + 1; ++ i) if (df[i]) bfs(i);
	for (int i = 1; i < (1 << (cnt + 1)); ++ i) f[i] = inf;
	for (int i = 0; i < (1 << (cnt + 1)); ++ i) {
		if (f[i] != inf) {
			for (int j = 0; j <= cnt; ++ j) {
				if ((i >> j) & 1) continue;
				for (int k = j + 1; k <= cnt; ++ k)
					if (!((i >> k) & 1)) f[i + (1 << j) + (1 << k)] = min(f[i + (1 << j) + (1 << k)], f[i] + cst[j][k]);
			}
		}
	}
	int ans = f[(1 << cnt + 1) - 1];
	printf("%d\n", (ans == inf) ? -1 : ans);
}
```

---

## 作者：灵乌路空 (赞：3)

# 知识点: DP，差分，Bfs

## [原题面](https://www.luogu.com.cn/problem/CF79D)

双倍经验 [P3943 星空](https://www.luogu.com.cn/problem/P3943)。  
将此题代码交过去可直接 AC，但 P3943 数据较弱，没有卡掉错误的背包解法。  
完全背包解法错误原因 详见 [题解 P3943 【星空】 - Epworth 的博客](https://www.luogu.com.cn/blog/EpworthX/solution-p3943)。

---

## 题意简述

>给定一长度为 $n$ 的 $0$ 串，给定 $k$ 个 位置。  
>给出 $m$ 个长度 $b_i$，每次可选择一段长度为 $b_i$ 的子序列取反。  
>求使 $k$ 个位置变为 $1$ ，其他位置仍为 $0$ 的最小步数。  
>$1\le n\le 10^4,\ 1\le m\le 100,\ 1\le b_i\le n,\ k\le 10$。  

---

## 分析题意

发现题目等价于 一开始只有 $k$ 个位置开着灯，使所有灯都关上的最小步数。  
**设关灯为 $0$，开灯为 $1$，以下均按照上述等价情况展开。**

---

看到区间修改，考虑差分。  
但此题为区间取反，一般的作差差分无法使用，考虑异或差分。  
令 $b_i = a_i\ \text{xor}\ a_{i+1}$，对于样例 1，有：  

|差分前|$\ \ 1 1 1 0 1 1 1 1 1 0$|  
|-|-|  
|差分后|$10011000010$|  

在差分后数组前添加一个 $0$ 位置。  
手玩后发现，差分后必然有偶数个 $1$ 出现。

此时若进行区间取反，只会使区间两端位置改变，中间不变。  
若将原序列中 $1\sim 3$ 取反，则有：  

|差分前|$\ \ 0 0 0 0 1 1 1 1 1 0$|  
|-|-|  
|差分后|$00001000010$|  

发现只有 $0,3$ 两个位置的 $1$ 被改变。

---

则问题转化为：  
>给定一有 $2k$ 个位置为 $1$ 的 01 串。  
>每次可选择一对距离为 $b_i$ 的位置，将其取反。  
>求将其变为 $0$ 串的最小步数。

分类讨论，进行下一步转化：  
1. 将一对 $0$ 取反，显然会使答案更劣，不可能发生。  
2. 将一个 $0$ 一个 $1$ 取反，可看做原有的 $1$ 移动至 $0$ 的位置。  
3. 将一对 $1$ 取反，可看做一个 $1$ 移动到另一个的位置，两个 $1$ 碰撞变成 $0$。

一定会发生偶数次 两个 $1$ 碰撞的情况。  
考虑每次使两个 $1$ 碰撞的最小代价。  

若已知两个 $1$ 的位置为 $u,v$，使其碰撞的代价即 使用 $b_i$ 和 $-b_i$ 凑出 $v - u$ 的步数。  
显然可以 bfs 预处理出碰撞每对 $1$ 的花费。

---

问题转化为：
>给定 $2k$ 个物品，每次可取出一对物品。  
>取出每对物品的花费已知，求全取出的最小花费。

由于 $k\le 10$，显然可以压缩 $k$ 个物品选/不选的状态。  
接下来就是个很简单的状压了。  
每次枚举两个不在集合中的物品 加入集合转移即可。

---

## 代码实现


```cpp
//知识点:DP，差分，Bfs
/*
By:Luckyblock
异或差分 + Bfs + 状压DP
*/
#include <queue>
#include <cstdio>
#include <ctype.h>
#include <cstring>
#include <algorithm>
#define ll long long
const int kMaxm = 110;
const int kMaxn = 1e4 + 10;
const int kInf = 1e9 + 2077;
//=============================================================
int n, k, m, cnt;
int pos[kMaxm], a[kMaxn], b[kMaxm];
int dis[kMaxn], map[kMaxn], cost[30][30];
int f[(1 << 21) + 10];
//=============================================================
inline int read() {
  int f = 1, w = 0; char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void GetMin(int &fir, int sec) {
  if (sec < fir) fir = sec;
}
void Bfs(int s) { //预处理出碰撞每对 1 的花费。
  std :: queue <int> q;
  memset(dis, 63, sizeof (dis));
  dis[s] = 0; 
  q.push(s);
  
  while (! q.empty()) {
    int u = q.front(); q.pop();
    for (int i = 1; i <= m; ++ i) {
      int v1 = u + b[i], v2 = u - b[i]; //v1 向右扩张，v2 向左。
      if (v1 <= n && dis[v1] > kInf) dis[v1] = dis[u] + 1, q.push(v1);
      if (v2 >= 1 && dis[v2] > kInf) dis[v2] = dis[u] + 1, q.push(v2);
    }
  }
  for (int i = 1; i <= n; ++ i) {
    if (map[i]) cost[map[s]][map[i]] = dis[i];
  }
}
void Prepare() {
  n = read(), k = read(), m = read();
  for (int i = 1; i <= k; ++ i) a[read()] = 1;
  for (int i = 0; i <= n; ++ i) a[i] ^= a[i + 1];
  for (int i = 1; i <= m; ++ i) b[i] = read();
  for (int i = 0; i <= n; ++ i) {
    if (a[i]) map[i] = ++ cnt; //建立映射关系
  }
  for (int i = 0; i <= n; ++ i ) if (a[i]) Bfs(i);
}
//=============================================================
int main() {
  Prepare();
  memset(f, 63, sizeof (f)); f[0] = 0;
  int all = (1 << cnt) - 1;
  for (int i = 0; i < all; ++ i) {
    if (f[i] > kInf) continue ;
    for (int x = 1; x <= cnt; ++ x) {
      if ((1 << (x - 1)) & i) continue ;
      for (int y = x + 1; y <= cnt; ++ y) { //每次枚举两个 1 转移
        if ((1 << (y - 1)) & i) continue ;
        GetMin(f[i | (1 << (x - 1)) | (1 << (y - 1))], 
               f[i] + cost[x][y]);
      }
    }
  }
  printf("%d", f[all] < kInf ? f[all] : - 1);
  return 0;
}
``` 

---

## 作者：crh1272336175 (赞：3)

标签：状压+bfs+dp

虽然题目中说的的是区间修改，但是我们可以通过考虑它的**差分**序列，使得要修改的位置个数变成2个。

我们应该很容易发现，这题可以使用逆向思维，只要求出最少的修改，使得原序列变成全0就可以了。

so，对原序列进行差分，那么每次修改就是要你对i号位置和i+size[]模2意义下的加1。容易看出：差分后的序列中，数值为1的个数是不会超过2k个，即不会超过20个。

考虑每次对i和i+x改动的过程，如果原序列中，i号位置和i+x号位置**都是0**的话，**没有必要进行改动**。所以任意时刻，数值为**1**的位置**个数**是**不会增加**的。so，我们可以把每一个的1看成一个的石子，那么每次我们可以把石子往某个方向移动size[]步，如果移动之后的位置存在石子的话，就相互抵消掉了。

至此，不难看出，石子之间的关系肯定是一个匹配的关系，否则就没有抵消这种说法。我们先bfs一遍所有是1的点，求出Dist[i][j]表示，石子i要走到石子j的位置，至少需要移动多少步，这一部分的复杂度是O(2kmn)。

现在问题转化为有一个大小不超过20的完全图，我们想要求它的最小权最大匹配。

可以用状压DP，设f[S]表示集合S的最小划分代价，每次选出最小的元素作为匹配元素之一，枚举另一个元素即可。

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e4+5,INF=1<<29;
int n,k,m,cnt;
int number[M];
int a[M],size[M],f[1<<25];
int dis[M],dist[25][25],visited[M];
queue<int> q;
void bfs(int x,int id)
{
	memset(visited,0,sizeof visited);
	memset(dis,0x3f3f3f3f,sizeof dis);
	q.push(x); visited[x]=1;
	dis[x]=0;
	while(!q.empty())
	{
		x=q.front(); q.pop();
		for(int i=1; i<=m; i++)
		{
			int tmp=size[i];
			if((x+tmp)<=n && !visited[x+tmp]) 
			{
                visited[x+tmp]=1;
				dis[x+tmp]=dis[x]+1;
				q.push(x+tmp);
            }
            if((x-tmp)>=1 && !visited[x-tmp]) 
			{
                visited[x-tmp]=1;
				dis[x-tmp]=dis[x]+1;
				q.push(x-tmp);
            }
		}
	}
	for(int i=1; i<=cnt; i++)
	{
		if(visited[number[i]]) dist[id][i]=dis[number[i]];
		else dist[id][i]=INF;
	}
}
void dp()
{
	for(int i=1; i<(1<<cnt); i++) f[i]=INF;
    for(int i=0,j; i<(1<<cnt); i++)
	{
        for(int k=1; k<=cnt; k++)
		    if((1<<k-1)&i) 
			{
			    j=k;
				break;
			}
        for(int k=1; k<=cnt; k++) 
		    if((1<<k-1)&i) 
                f[i]=min(f[i],f[i^(1<<j-1)^(1<<k-1)]+dist[j][k]);
    }
}
int main()
{
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1; i<=k; i++) 
	{
		int x; scanf("%d",&x);
		a[x]=1;
	}
	for(int i=1; i<=m; i++) scanf("%d",&size[i]);
	n++;//要注意边界，所以n要++
	for(int i=n; i>=1; i--) a[i]^=a[i-1];//差分
	for(int i=1; i<=n; i++)
	    if(a[i])
	    {
	    	a[i]=++cnt;
	    	number[cnt]=i;//number数组记录所有石子的下标
		}
	for(int i=1; i<=n; i++)
	    if(a[i]) bfs(i,a[i]);
	dp();
	if(f[(1<<cnt)-1]==INF) puts("-1");
    else printf("%d\n",f[(1<<cnt)-1]);
    return 0;
}
```


---

## 作者：Waldin (赞：1)

## 题解
首先，把这个问题进行逆向推理，发现这个问题等价于：

> 有 $n$ 盏灯。一开始，第 $x_{i\isin[1\dots k]}$ 盏灯是亮的，其余是灭的。每次操作可以将任意连续 $a_{i\isin[1\dots l]}$ 个灯的明灭状态取反。求让所有灯灭的最少操作次数。

形式化地：
> 有一个长度为 $n$ 的 $01$ 串，其中第 $x_{i\isin[1\dots k]}$ 位为 $1$，其余位为 $0$。每次操作可以将任意一段长度为 $a_{i\isin[1\dots l]}$ 的连续子序列中的所有元素取反。求让序列中所有元素归 $0$ 的最少操作次数。

由于操作涉及区间修改，容易想到**异或差分**：
$$
dif_i=org_i\oplus org_{i+1}
$$
其中 $org_{i\isin[1\dots n]}$ 是长度为 $n$ 的原序列，$dif_{i\isin[0\dots n]}$ 是差分原序列得到的序列。计算时，$org_0$ 和 $org_{n+1}$ 的值当作 $0$ 处理。这里需要注意 $dif$ 的长度是要比 $org$ 的长度大 $1$ 的，且**序号从 $0$ 开始**，如下：
$$
\begin{aligned}
\textsf{012345678}&\\
\color{blue}11101110&\\
\color{red}1\color{red}00110010
\end{aligned}
$$
其中黑色的代表这一纵列的元素在各自序列中的序号，蓝色的为原序列，红色的为差分序列。

显然，在原序列中取反长度为 $x$ 的区间 $[y,y+x-1]$ 就等价于在差分序列中取反相距 $x$ 的 $dif_{y-1}$ 和 $dif_{y+x-1}$。并且注意到，对于原序列中的每一个 $1$，异或最多只能把它差分成两个 $1$，所以**差分序列中最多只有 $2k$ 个 $1$**。这样，问题就又变成了：

> 给定一个长度为 $n+1$ 的 $01$ 串，其中最多有 $2k$ 个 $1$。每次操作可以把相距 $a_{i\isin[1\dots l]}$ 的两个元素取反。求让序列中所有元素归 $0$ 的最少操作次数。

容易发现，由于将序列中任意两个元素取反需要的最少操作次数是固定的，所以如果要最小化操作次数，只需要考虑每一次取反哪两个元素即可。易得，对于要取反的两个元素有且只有以下三种情况：

- 取反的两个元素都是 $0$；
  
- 取反的两个元素一个是 $1$，一个是 $0$；
  
- 取反的两个元素都是 $1$。
  

显然，针对每一次取反，**只有在最后那种情况下才能实现最优化**，所以只考虑处理最后那种情况即可。

随后注意到，如果设 $\text{popcnt}_s$ 表示序列 $s$ 中 $1$ 的个数；将题目给出的序列差分后得到的序列为 $bulbs_{i\isin[0\dots n]}$；$DP_{i\isin[1\dots2^{\text{popcnt}_{bulbs}})}$ 表示差分序列中状态为 $1$ 的元素们是否归 $0$ 的状态为 $i$（从低位向高位数，二进制下 $i$ 的第 $x\pod{x\isin[0\dots\text{popcnt}_{bulbs})}$ 位为 $0$ 表示差分序列中第 $x$ 个状态为 $1$ 的元素还没有归 $0$，为 $1$ 则表示已经归 $0$ 了）时需要的最少操作次数；$times_{i\isin[0\dots\text{popcnt}_{bulbs}),j\isin[0\dots\text{popcnt}_{bulbs})}$ 表示让第 $i$ 和 $j$ 个状态为 $1$ 的元素归零，同时其余所有元素都不变的最少操作数，则
$$
DP_{i\isin[1\dots2^{\text{popcnt}_{bulbs}})}=
\min_{j\isin[0\dots\text{popcnt}_{bulbs}),k\isin[0\dots\text{popcnt}_{bulbs})}DP_{i-2^j-2^k}+times_{j,k}
\pod{2^{-j}i\bmod2=2^{-k}i\bmod2=1}
$$

即通过枚举归零的两个差分序列中状态为 $1$ 的元素的序号 $j$ 和 $k$ 来实现状态转移。初始状态为 $DP_0=0$，表示让差分序列中状态为 $1$ 的元素们仍为 $1$，即没动的最少操作数为 $0$；目标状态，也就是最终答案，为 $DP_{2^n-1}$，表示让差分序列中状态为 $1$ 的元素们都归 $0$，即差分序列中所有元素都归 $0$ 的最少操作次数。

现在再考虑如何求 $times_{i,j}$：显然可以建一个**无向图**，在编号为 $x\pod{x\isin[0\dots n]}$ 的点与编号为 $x\pm a_y\pod{x\pm a_y\ge0}$ 的点之间连一条边权为 $1$ 的边，则 $times_{i,j}$ 就是图中点 $i$ 到点 $j$ 的**最短路**。

时间复杂度分析：异或差分算法的时间复杂度为 $\Theta(n)$；状态压缩动态规划的时间复杂度为 $\text o[2^{2k}(2k)^2]$；$01$ 最短路可以通过 $2k$ 遍广度优先搜索 $\texttt{BFS}$ 求得，时间复杂度为 $\text O(2kn\times2l)$。综上所述，**总时间复杂度为 $\text O(n+2^{2k+2}k^2+4knl)$**。

示例代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define typeof(...) __decltype(__VA_ARGS__)
constexpr size_t MAXn = 1e4, MAXk = 1e1, MAXl = 1e2;

#ifndef _getchar_nolock
#define _getchar_nolock getchar_unlocked
#endif
class FastIn_Base {
public:
    template<typename _Ty>
    FastIn_Base& operator>>(_Ty& __restrict__ int_var) noexcept {
        int c; bool f;
        if (is_signed<_Ty>::value)
            f = false;
        while (!isdigit(c = _getchar_nolock()))
            if (is_signed<_Ty>::value && c == 45)
                f = true;

        int_var = c - 48;
        while (isdigit(c = _getchar_nolock()))
            int_var = int_var * 10 + (c - 48);

        if (is_signed<_Ty>::value && f)
            int_var = -int_var;
        return *this;
    }
};
#define intIn ((FastIn_Base) {})
#define cin intIn

template<typename _Ty>
bool to_min(_Ty& x, const _Ty y) noexcept {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

int main(void) noexcept {
    ios::sync_with_stdio(false);

    unsigned short n; unsigned char k, l;
    cin >> n >> k >> l;
    unsigned char bulbs[MAXn + 2];  // bulbs[i] 表示灯泡 i 的明灭状态：0 为灭；1 为明
    for (typeof(k)i = 1; i <= k; ++i) {
        unsigned short x; cin >> x;
        bulbs[x] = 1;
    }
    unsigned short a[MAXl];
    for (typeof(l)i = 0; i < l; ++i)
        cin >> a[i];

    // 差分并离散化
    unsigned char order[MAXn + 1],  // order[i] 是 i 号明灯(差分后)离散后的编号
        cnt = 0;  // 统计时编号状态的记录。这里由于异或差分对于一盏明灯最多能差分出两盏明灯，所以差分后的明灯数最多为 2 * k，也就是说，离散后编号的最大值为 2 * MAXk，所以开 char 足够
    bulbs[0] = 0; bulbs[n + 1] = 0;  // 为异或差分做必要的清零
    for (typeof(n)i = 0; i <= n; ++i) {
        bulbs[i] ^= bulbs[i + 1];  // 异或差分
        if (bulbs[i])  // 只离散明灯(差分后)，这受解法要求
            order[i] = cnt++;  // 离散化
    }

    // 最短路。此后注释里的「明灯」都是指差分处理后还亮的灯，将不再单独说明
    unsigned short times[2 * MAXk][2 * MAXk];  // time[i][j] 是只使 i 号(离散后)明灯和 j 号(离散后)明灯熄灭至少需要的操作次数。关于数组大小，上文说明过，离散后明灯编号的最大值为 2 * MAXk
    for (typeof(n)i = 0; i <= n; ++i)
        if (bulbs[i]) {  // 枚举明灯
            unsigned short dis[MAXn + 1];  // dis[j] 表示从 i 号明灯到 j 号明灯的「距离」
            memset(dis + 1, 0x7F, n * sizeof(*dis));  // 由于第 123 行可能出现两个正无穷相加，也就是说临时右值最大可能为两倍「正无穷」，所以初始为 0x7F7F 比较合适，初始为 0xFFFF 在相加时可能会导致右值溢出
            dis[i] = 0;
            bitset<MAXn + 1> vis;
            vis[i] = true;
            queue<unsigned short> q;
            q.push(i);

            // BFS 求 01 最短路
            while (!q.empty()) {
                #define u (q.front())
                for (typeof(l)j = 0; j < l; ++j) {  // 枚举「长度」
                    unsigned short v;
                    if ((v = u + a[j]) <= n && !vis[v]) {  // 向右
                        dis[v] = dis[u] + 1;
                        vis[v] = true;
                        q.push(v);
                    }
                    if ((v = u - a[j]) <= n && !vis[v]) {  // 向左。如果 u - a[j] < 0 的话会因为是无符号型而溢出，因此还是像向左的时候那样判断是否 <= n 即可
                        dis[v] = dis[u] + 1;
                        vis[v] = true;
                        q.push(v);
                    }
                }
                #undef u
                q.pop();
            }

            // 因为求出的数据都是未离散状况下的，而后面状压 DP 只认离散数据，所以这里要把刚求出的数据映射到离散后的状态保存下来
            for (typeof(n)j = 0; j <= n; ++j)
                if (bulbs[j])  // 上文提过离散和明灯的关系，故有此判断
                    times[order[i]][order[j]] = dis[j];
        }

    // 状压 DP
    unsigned long DP[1UL << (2 * MAXk)];  // DP[s] 表示状态为 s(1 位表示灭；0 位表示明)时的最小操作次数
    DP[0] = 0;
    memset(DP + 1, 0x7F, sizeof(DP) - sizeof(*DP));
    for (unsigned long i = 1; i < (1UL << cnt); ++i)
        for (unsigned char j = 0; j < cnt; ++j)
            if ((i >> j) & 1UL)  // 保证状态合法：枚举出来的上一盏灭掉的灯在状态里肯定得是灭掉的状态
                for (unsigned char k = j + 1; k < cnt; ++k)
                    if ((i >> k) & 1UL)  // 同上
                        to_min(DP[i], DP[i - (1UL << j) - (1UL << k)] + times[j][k]);

    if (DP[(1 << cnt) - 1] >= 0x7F7F)
        cout << "-1";
    else
        cout << DP[(1 << cnt) - 1];
    return 0;
}
```
## 习题
[P3943$\,$星空](https://www.luogu.com.cn/problem/P3943)

只需要按题目要求把上一题代码中的数据范围改一下即可 [$\color{green}\mathcal{AC}$](https://www.luogu.com.cn/record/151139114)：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define typeof(...) __decltype(__VA_ARGS__)
constexpr size_t MAXn = 4e4, MAXk = 8, MAXl = 64;

#ifndef _getchar_nolock
#define _getchar_nolock getchar_unlocked
#endif
class FastIn_Base {
public:
    template<typename _Ty>
    FastIn_Base& operator>>(_Ty& __restrict__ int_var) noexcept {
        int c; bool f;
        if (is_signed<_Ty>::value)
            f = false;
        while (!isdigit(c = _getchar_nolock()))
            if (is_signed<_Ty>::value && c == 45)
                f = true;

        int_var = c - 48;
        while (isdigit(c = _getchar_nolock()))
            int_var = int_var * 10 + (c - 48);

        if (is_signed<_Ty>::value && f)
            int_var = -int_var;
        return *this;
    }
};
#define intIn ((FastIn_Base) {})
#define cin intIn

template<typename _Ty>
bool to_min(_Ty& x, const _Ty y) noexcept {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

int main(void) noexcept {
    ios::sync_with_stdio(false);

    unsigned short n; unsigned char k, l;
    cin >> n >> k >> l;
    unsigned char bulbs[MAXn + 2];  // bulbs[i] 表示灯泡 i 的明灭状态：0 为灭；1 为明
    for (typeof(k)i = 1; i <= k; ++i) {
        unsigned short x; cin >> x;
        bulbs[x] = 1;
    }
    unsigned short a[MAXl];
    for (typeof(l)i = 0; i < l; ++i)
        cin >> a[i];

    // 差分并离散化
    unsigned char order[MAXn + 1],  // order[i] 是 i 号明灯(差分后)离散后的编号
        cnt = 0;  // 统计时编号状态的记录。这里由于异或差分对于一盏明灯最多能差分出两盏明灯，所以差分后的明灯数最多为 2 * k，也就是说，离散后编号的最大值为 2 * MAXk，所以开 char 足够
    bulbs[0] = 0; bulbs[n + 1] = 0;  // 为异或差分做必要的清零
    for (typeof(n)i = 0; i <= n; ++i) {
        bulbs[i] ^= bulbs[i + 1];  // 异或差分
        if (bulbs[i])  // 只离散明灯(差分后)，这受解法要求
            order[i] = cnt++;  // 离散化
    }

    // 最短路。此后注释里的「明灯」都是指差分处理后还亮的灯，将不再单独说明
    unsigned short times[2 * MAXk][2 * MAXk];  // time[i][j] 是只使 i 号(离散后)明灯和 j 号(离散后)明灯熄灭至少需要的操作次数。关于数组大小，上文说明过，离散后明灯编号的最大值为 2 * MAXk
    for (typeof(n)i = 0; i <= n; ++i)
        if (bulbs[i]) {  // 枚举明灯
            unsigned short dis[MAXn + 1];  // dis[j] 表示从 i 号明灯到 j 号明灯的「距离」
            memset(dis + 1, 0x7F, n * sizeof(*dis));  // 由于第 123 行可能出现两个正无穷相加，也就是说临时右值最大可能为两倍「正无穷」，所以初始为 0x7F7F 比较合适，初始为 0xFFFF 在相加时可能会导致右值溢出
            dis[i] = 0;
            bitset<MAXn + 1> vis;
            vis[i] = true;
            queue<unsigned short> q;
            q.push(i);

            // BFS 求 01 最短路
            while (!q.empty()) {
                #define u (q.front())
                for (typeof(l)j = 0; j < l; ++j) {  // 枚举「长度」
                    unsigned short v;
                    if ((v = u + a[j]) <= n && !vis[v]) {  // 向右
                        dis[v] = dis[u] + 1;
                        vis[v] = true;
                        q.push(v);
                    }
                    if ((v = u - a[j]) <= n && !vis[v]) {  // 向左。如果 u - a[j] < 0 的话会因为是无符号型而溢出，因此还是像向左的时候那样判断是否 <= n 即可
                        dis[v] = dis[u] + 1;
                        vis[v] = true;
                        q.push(v);
                    }
                }
                #undef u
                q.pop();
            }

            // 因为求出的数据都是未离散状况下的，而后面状压 DP 只认离散数据，所以这里要把刚求出的数据映射到离散后的状态保存下来
            for (typeof(n)j = 0; j <= n; ++j)
                if (bulbs[j])  // 上文提过离散和明灯的关系，故有此判断
                    times[order[i]][order[j]] = dis[j];
        }

    // 状压 DP
    unsigned long DP[1UL << (2 * MAXk)];  // DP[s] 表示状态为 s(1 位表示灭；0 位表示明)时的最小操作次数
    DP[0] = 0;
    memset(DP + 1, 0x7F, sizeof(DP) - sizeof(*DP));
    for (unsigned long i = 1; i < (1UL << cnt); ++i)
        for (unsigned char j = 0; j < cnt; ++j)
            if ((i >> j) & 1UL)  // 保证状态合法：枚举出来的上一盏灭掉的灯在状态里肯定得是灭掉的状态
                for (unsigned char k = j + 1; k < cnt; ++k)
                    if ((i >> k) & 1UL)  // 同上
                        to_min(DP[i], DP[i - (1UL << j) - (1UL << k)] + times[j][k]);

    if (DP[(1 << cnt) - 1] >= 0x7F7F)
        cout << "-1";
    else
        cout << DP[(1 << cnt) - 1];
    return 0;
}
```

---

## 作者：TernaryTree (赞：1)

区间异或，套路式地差分。一次操作会使得 $i$ 与 $i+a_j$ 取反，所以将 $i$ 与 $i+a_j$ 连边。

对于两个位置，要使两者都点亮，并且不影响其他位置，其操作次数为两点的最短路。

边权都为 $1$ 的图可以 bfs $\Theta(n)$ 求出单源最短路。

对每个要点亮的点跑两两的最短路。$\Theta(kn)$。

然后转换为了完全图上最小权完美匹配问题。

枚举两个点，状压即可。

复杂度 $\Theta(k^24^k+kn+nm)$。

底数是 $4$ 是因为异或差分后 $1$ 的个数最多是 $2k$ 个的。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

typedef pair<int, int> pii;
const int maxn = 1e4 + 10;
const int maxk = 22;
const int maxm = 1e2 + 10;

struct edge { int to, next; };

int n, k, m;
int a[maxn];
int b[maxn];
int d[maxn];
int head[maxn];
edge e[maxn * maxm * 2];
int cnt;

void add_edge(int u, int v) {
	e[++cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}

int p[maxk], c;
int dis[maxk][maxk];
int vis[maxn];
int f[1 << maxk];

void bfs(int s) {
	for (int i = 1; i <= n; i++) vis[i] = 0;
	for (int i = 1; i <= c; i++) dis[s][i] = 1e18;
	queue<pii> q;
	q.push({p[s], 0});
	dis[s][s] = 0;
	vis[p[s]] = 1;
	while (!q.empty()) {
		pii u = q.front();
		q.pop();
		for (int i = head[u.first]; i; i = e[i].next) {
			int v = e[i].to;
			if (!vis[v]) {
				if (a[v]) dis[s][a[v]] = u.second + 1;
				vis[v] = true;
				q.push({v, u.second + 1});
			}
		}
	}
}

inline int popcount(int x) {
	int z = 0;
	while (x) ++z, x &= x - 1;
	return z;
}

signed main() {
	cin >> n >> k >> m, ++n;
	for (int i = 1; i <= k; i++) cin >> b[i], a[b[i]] = 1;
	for (int i = 1; i <= m; i++) cin >> d[i];
	for (int i = n; i >= 1; i--) a[i] = a[i] ^ a[i - 1];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i + d[j] <= n) add_edge(i, i + d[j]);
			if (i - d[j] >= 1) add_edge(i, i - d[j]);
		}
	}
	for (int i = 1; i <= n; i++) if (a[i]) p[++c] = i, a[i] = c;
	for (int i = 1; i <= c; i++) bfs(i);
	f[0] = 0;
	for (int i = 3; i < (1 << c); i++) {
		if (popcount(i) & 1) continue;
		f[i] = 1e18;
		for (int j = 0; j < c; j++) {
			if (!(i >> j & 1)) continue;
			for (int k = j + 1; k < c; k++) {
				if (!(i >> k & 1)) continue;
				f[i] = min(f[i], f[(i ^ (1 << j)) ^ (1 << k)] + dis[j + 1][k + 1]);
			}
		}
	}
	if (f[(1 << c) - 1] >= 1e18) puts("-1");
	else cout << f[(1 << c) - 1];
	return 0;
}

```

---

## 作者：C_Pos_Princess (赞：0)

### 题解

这个题我们看到了区间的操作，首先按照经验必然想到线段树，但是好像不太好维护呢。

我们又注意到，这个序列好像只有 0 和 1 啊！我们自然想到异或，又由于是序列操作，想到差分。

我们不妨把原数列两两异或成一个新的序列，试观察有什么性质。

手动模拟发现，原序列区间取反就相当于新序列取反两个数！

问题就变成了，每次改变序列中的两个数，最少几次能把序列归零。

又注意到 $k$ 很小，那我们可不可以利用这个性质状压呢？当然可以。

求最少几次的时候，我们可以利用最短路，这个时候就不要用所有的点了，只需要用不是 0 的点，这样就减少了状态数。

最后用 dp 转移即可。

#### 总结：
1. 输入数组，处理异或数组；
2. 将 1 的位置统计出来，利用最短路求每个 1 到其他的 1 的距离；
3. 动态规划转移即可；


#### 代码

```cpp
const int N = 4e4+10;
const int INF = 0x3f3f3f3f;
using namespace std;
int n,k,l;
int x[N];
int b[N];
int c[N];
int a[N];
int f[30][30];
int dis[N];
bool st[N];
int tot;
int d[N];
void spfa(int s){
	queue<int>q;
	q.push(s);
	memset(dis,0x3f,sizeof dis);
	memset(st,0,sizeof st);
	st[s]= 1;
	dis[s] = 0;
	while(q.size()){
		
		int u = q.front();
		q.pop();
		for(int i = 1;i<=l;i++){
			int v1 = u+a[i],v2 = u-a[i];
			if(v1<=n && !st[v1]){
				dis[v1] = dis[u]+1;
				st[v1] = 1;
				q.push(v1);
			}
			if(v2>=0 && !st[v2]){
				dis[v2] = dis[u]+1;
				st[v2] = 1;
				q.push(v2);
			}	
		}
	}
	for(int i = 0;i<=n;i++){
		if(c[i]) f[d[s]][d[i]] = dis[i];
	}
} 

int dp[1<<21];
void solve(){
	
	for(int s = 1;s<(1<<tot);s++){
		dp[s] = INF;
		for(int i = 0;i<tot;i++){
			if(!((s>>i)&1)) continue;
			for(int j = i+1;j<tot;j++){
				if(!((s>>j)&1)) continue;
				dp[s] = min(dp[s],dp[s-(1<<i)-(1<<j)]+f[i][j]); 
			}
		}	
	}
	write((dp[(1<<tot)-1] == INF)?-1:dp[(1<<tot)-1]);	
	LF;
}


int main(){
	read(n,k,l);
	for(int i = 1;i<=k;i++){
		read(x[i]);
		b[x[i]] = 1;
	}	
	for(int i = 0;i<=n;i++){
		c[i] = b[i]^b[i+1]; 
	}
	
	for(int i = 1;i<=l;i++){
		read(a[i]);
	}

	for(int i = 0;i<=n;i++){
		if(c[i]) d[i] = tot++;
	}
	
	
	for(int i = 0;i<=n;i++){
		if(c[i]) spfa(i);
	}
	solve();
	
	return 0;
}
```

---

## 作者：pomelo_nene (赞：0)

题意：有一个长度为 $n$ 的 $01$ 序列，初始全为 $0$。给定 $l$ 个操作，由一个数 $a$ 表示，表示可以将一段连续的长度为 $a$ 的所有数全部取反。要求仅使得 $k$ 个位置为 $1$，求最小操作数。$n \leq 10^5,l \leq 100,k \leq 10$。

首先修改一段显然不优雅，于是差分。取反 $[l,r]$ 相当于在差分数组上取反 $a'_l,a'_{r+1}$。

考虑构造初始的差分数组。注意到整个操作是可逆的，我们可以看成初始有 $k$ 个位置是 $1$，目标是全部变成 $0$。那么有 $k$ 个位置为 $1$，相当于对 $k$ 个长度为 $1$ 的区间取反，套用上面的方法。

注意到 $1$ 的个数一定是偶数个，又显然最优情况下我们一定会每次消掉两个 $1$。注意到 $k$ 很小，于是可以直接保存下所有的 $1$，直接状压 dp。每次枚举消掉两个 $1$（有一个小优化是，只枚举一个 $1$，然后和最低位上的 $1$ 消去，反正没有影响）。

考虑 dp 过程，有一个地方是，我们要将第 $i$ 个 $1$ 原来的位置和第 $j$ 个 $1$ 原来的位置取反。考虑如何计算这个东西。

显然背包不行（因为背包上限显然不定，而你不能一边加一遍减去消去上限影响）。只能考虑暴力的做法。

注意到，我们对一个 $s$ 操作，将 $s$ 作为起点或者终点选择一段 $a_i$ 取反（相当于取反 $s$ 和 $s ± a_i$），那么相当于有边权为 $1$ 的边 $s \to s ± a_i$（如果合法），于是对于每个可能的起点（也就是差分数组中 $1$ 的位置）都做一遍 $01$ 最短路就行。

代码细节不多，直接写就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
// s[105], a[25];
bool vis[40005];
int n,k,l,a[40005],s[105],p[25],dis[40005],len,f[25][25],dp[(1<<23)];
void bfs()
{
	for(int i=1;i<=len;++i)
	{
		memset(dis,63,sizeof dis);
		memset(vis,false,sizeof vis);
		int S=p[i];
		dis[S]=0,vis[S]=true;
		queue<int> Q;
		Q.push(S);
		while(!Q.empty())
		{
			int now=Q.front();
			Q.pop();
			for(int j=1;j<=l;++j)
			{
				int to;
				to=now+s[j];
				if(to<=n+1 && !vis[to])
				{
					dis[to]=dis[now]+1;
					vis[to]=true;
					Q.push(to);
				}
				to=now-s[j];
				if(to>=1 && !vis[to])
				{
					dis[to]=dis[now]+1;
					vis[to]=true;
					Q.push(to);
				}
			}
		}
		for(int j=1;j<=len;++j)	f[i][j]=dis[p[j]];
	}
}
int lowbit(int x){return x&(-x);}
int main(){
	scanf("%d %d %d",&n,&k,&l);
	for(int i=1;i<=k;++i)
	{
		int x;
		scanf("%d",&x);
		a[x]^=1,a[x+1]^=1;
	}
	for(int i=1;i<=l;++i)	scanf("%d",&s[i]);
	for(int i=1;i<=n+1;++i)	if(a[i])	p[++len]=i;
	bfs();
	memset(dp,63,sizeof dp);
	int U=(1<<len)-1;
	dp[U]=0;
	int inf=dp[0];
	for(int S=U;S;--S)
	{
		int st=lowbit(S),pos=0;
		while(st)	st>>=1,++pos;
		for(int i=pos+1;i<=len;++i)
		{
			if(!((S>>(i-1))&1))	continue;
			int T=S^(1<<(pos-1))^(1<<(i-1));
			dp[T]=min(dp[T],dp[S]+f[pos][i]);
		}
	}
	printf("%d",dp[0]==inf?-1:dp[0]);
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

记录一下这道感觉非常神的 daily problem。讲思路。

下文 $1$ 表示亮，$0$ 表示不亮。

首先，操作到一个固定状态显然是比操作回全 $0$ 难做的。于是把操作逆过来。

如果我们直接按题目说的，区间反转入手，容易发现 $1$ 的个数大概率是越来越多的。怎么办呢？因为是区间操作，又是异或，于是想到将区间修改**差分**。

设 $b_i=a_i\oplus a_{i-1}$，问题就转换成：每次可以将 $b_i,b_{i+x_j}(i+x_j\le n+1)$ 两个位置异或上 $1$，问最少多少次操作后 $\forall i\in[1,n],b_i=0$。

考虑怎么解决一个问题。先思考：我们会凭空对两个为 $0$ 的位置操作吗？显然是**不会**的。但是又有一个问题：为什么不能用这次操作完产生的 $1$ 和其他位置再操作呢？这是因为差分操作可以无视顺序，所以交换顺序后，**一定满足每次操作至少有一个位置的 $b_i=1$。**

好的，现在这个问题已经被简单化很多了，但是两个位置同时异或 $1$ 这个操作仍然不好表示，于是考虑再把这个操作做一个转化。

考虑如果操作 $i,j$ 两个位置，$b_i=1,b_j=0$，可以怎么刻画呢？发现其实可以视作 $i$ 上的 $1$ **移动到**了 $j$！如果两者都是 $1$ 呢？就可以视作 $i$ 上的 $1$ 移动到 $j$，并且和 $j$ 上的 $1$ 抵消了。

于是，我们可以**将一次操作视为一个 $1$ 在一张图上走了一步**，问最后每个点都能匹配上另一个点，使它们最后在同一个位置，或者这个点在 $n+1$ 号点。

由于 $\sum[b_i=1]\le2\times k\le20$，于是直接考虑状压 dp。预处理出 $i,j$ 位置上的 $1$ 最少需要几步相遇，然后每次枚举两个为 $1$ 的位置转移，最后加上移动到 $n+1$ 的贡献即可。

总结一下做法，每个 $i$ 向 $i+x_j,i-x_j$ 连边，用 $b_i=1$ 的位置做多源 bfs，最后状压 dp 求出两两匹配的最小操作次数。时间复杂度 $O(nl+2^{2k}k^2)$。

code：

```cpp
int n,m,k,s,a[N],b[N],c[N],d[N],dis[27][N],f[27][27],dp[M];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<7];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void bfs(int s,int j){
	queue<int> q;
	dis[j][s]=0,q.push(s);
	while(q.size()){
		int u=q.front();
		q.pop();
		go(i,u){
			int v=e[i].to;
			if(dis[j][v]<=dis[j][u]+1){
				continue;
			}
			dis[j][v]=dis[j][u]+1;
			q.push(v);
		}
	}
}
void Yorushika(){
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,m){
		int x;scanf("%d",&x);
		a[x]=1;
	}
	rep(i,1,k){
		scanf("%d",&c[i]);
	}
	rep(i,1,n){
		b[i]=a[i-1]^a[i];
		if(b[i]){
			d[++s]=i;
		}
		rep(j,1,k){
			if(i-c[j]>0){
				add(i,i-c[j]);
			}
			if(i+c[j]<=n+1){
				add(i,i+c[j]);
			}
		}
	}
	mems(dis,0x3f);
	rep(i,1,s){
		bfs(d[i],i);
	}
	rep(i,1,s){
		rep(j,i+1,s){
			if(i==j){
				continue;
			}
			f[i][j]=inf;
			rep(k,1,n){
				f[i][j]=min(f[i][j],dis[i][k]+dis[j][k]);
			}
		}
	}
	const int mx=1<<s;
	mems(dp,0x3f),dp[0]=0;
	int ans=inf;
	rep(S,0,mx-1){
		rep(i,1,s){
			rep(j,i+1,s){
				if(!(S>>(i-1)&1)||!(S>>(j-1)&1)){
					continue;
				}
				dp[S]=min(1ll*dp[S],1ll*dp[S^(1<<(i-1))^(1<<(j-1))]+f[i][j]);
			}
		}
		if(dp[S]>1e9){
			continue;
		}
		int sum=dp[S];
		bool fl=1;
		rep(i,1,s){
			if(!(S>>(i-1)&1)){
				if(dis[i][n+1]>1e9){
					fl=0;break;
				}
				sum+=dis[i][n+1];
			}
		}
		if(fl){
			ans=min(ans,sum);
		}
	}
	printf("%d\n",ans>1e9?-1:ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题目传送门](https://codeforces.com/contest/79/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF79D)

一个远古场的 *2800，在现在看来大概 *2600 左右罢（

不过我写这篇题解的原因大概是因为这题教会了我一个套路罢（

首先注意到每次翻转的是一个**区间**，那么我们可以考虑它的**差分序列**（这就是这题教会我的套路，碰到区间操作有关的问题不妨考虑它的差分序列，这样可将影响多个元素的区间操作转化为 $2$ 个单点操作，其实第一次碰见这个套路是在[这个题](https://www.luogu.com.cn/problem/AT4831)，可是由于当时比较 naive 没能及时补题并整理这些方法），那么每次操作显然是将差分序列上两个单点进行翻转，而翻转的两个单点的距离恰好等于操作区间的长度，于是现在问题转化为：你有一个初始为 $0$ 的长度为 $n+1$ 的序列 $a$，你可以选择两个单点并将它们的状态翻转，满足这两个单点的距离属于某个集合 $S$，要求最少多少次操作将序列变为给定序列 $a'$。

考虑怎样解决转化后的问题，首先取两个单点并翻转显然是不影响 $1$ 的个数的奇偶性的，因此如果 $1$ 的个数是奇数那直接 $-1$ 即可，否则显然我们会将这些 $1$ 两两配对，对于同一对中的两个位置 $x,y$，我们会以如下方式让 $x,y$ 上的数都变为 $0$：

> 重复以下步骤若干次：
>
> - 选择一个长度 $l\in S$ 并将 $x$ 与 $x+l$ 或 $x-l$ 同时翻转，这样即可将 $x$ 上的 $1$ 转移到 $x+l$ 或 $x-l$ 上。
>
> 直到 $x+l=y\lor x-l=y$

我们记 $d_{x,y}$ 为将 $x,y$ 上的数变为 $0$ 的最小步骤，那么显然我们可以以每个 $1$ 为起点进行一遍 BFS 求出所有 $d_{x,y}$。注意到此题 $k\le 10$，因此差分序列上 $1$ 的个数 $\le 20$，故考虑状压 $dp$，$dp_S$ 表示将 $S$ 中的 $1$ 变为 $0$ 的最小代价，转移就枚举两个 $x,y\notin S$ 然后 $dp_{S\cup\{x\}\cup\{y\}}\leftarrow dp_S+d_{x,y}$ 即可。

~~据说有更优秀的二分图最小权完美匹配的做法？i 了 i 了，可惜我懒癌爆发懒得写了~~

复杂度 $2^kk^2+nmk$，其中 $k=20$。

```cpp
const int MAXN=1e4;
const int MAXM=100;
const int MAXK=20;
const int MAXP=1<<20;
const int INF=0x3f3f3f3f;
int n,k,m,a[MAXN+5],b[MAXN+5],l[MAXM+5],id[MAXN+5],pos[MAXK+5];
int dis[MAXN+5],d[MAXK+5][MAXK+5],cnt;
void bfs(int s){
	queue<int> q;memset(dis,-1,sizeof(dis));
	dis[s]=d[id[s]][id[s]]=0;q.push(s);
	while(!q.empty()){
		int x=q.front();q.pop();
		if(id[x]) d[id[s]][id[x]]=dis[x];
		for(int i=1;i<=m;i++){
			if(x+l[i]<=n+1){
				if(!~dis[x+l[i]]) dis[x+l[i]]=dis[x]+1,q.push(x+l[i]);
			} if(x-l[i]>=1){
				if(!~dis[x-l[i]]) dis[x-l[i]]=dis[x]+1,q.push(x-l[i]);
			}
		}
	}
}
int dp[MAXP+5];
int main(){
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1,x;i<=k;i++) scanf("%d",&x),a[x]=1;
	for(int i=1;i<=m;i++) scanf("%d",&l[i]);
	for(int i=1;i<=n+1;i++) b[i]=a[i]^a[i-1];
	for(int i=1;i<=n+1;i++) if(b[i]) id[i]=++cnt,pos[cnt]=i;
	memset(d,63,sizeof(d));
	for(int i=1;i<=n+1;i++) if(id[i]) bfs(i);
	memset(dp,63,sizeof(dp));dp[0]=0;
//	printf("%d\n",cnt);
//	for(int i=1;i<=cnt;i++) for(int j=1;j<=cnt;j++)
//		printf("%d%c",d[i][j]," \n"[j==cnt]);
	for(int i=0;i<(1<<cnt);i++){
		if(dp[i]>=INF) continue;
		for(int j=1;j<=cnt;j++) for(int l=1;l<j;l++)
			if((~i>>j-1&1)&&(~i>>l-1&1))
				chkmin(dp[i|(1<<j-1)|(1<<l-1)],dp[i]+d[j][l]);
	} printf("%d\n",(dp[(1<<cnt)-1]>=INF)?-1:dp[(1<<cnt)-1]);
	return 0;
}
```



---

