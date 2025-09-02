# [AGC021C] Tiling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc021/tasks/agc021_c

高橋君は、縦 $ N $ マス横 $ M $ マスのマス目を持っています。 次の条件をすべて満たすように、縦 $ 1 $ マス横 $ 2 $ マスのタイル $ A $ 枚と、縦 $ 2 $ マス横 $ 1 $ マスのタイル $ B $ 枚を マス目に置くことができるかどうかを判定し、可能なら置き方をひとつ構成してください。

- マス目の上に、全てのタイルを置かなければならない。
- タイルはマス目からはみ出してはならず、また異なるタイル同士が重なってはならない。
- マス目やタイルを回転させてはならない。
- 全てのタイルは、マス目のちょうど $ 2 $ マスを完全に覆う。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 1000 $
- $ 0\ \leq\ A,B\ \leq\ 500000 $
- $ N,M,A,B $ は整数である

### Sample Explanation 1

縦 $ 3 $ マス横 $ 4 $ マスのマス目に、縦 $ 1 $ マス横 $ 2 $ マスのタイル $ 4 $ 枚と、縦 $ 2 $ マス横 $ 1 $ マスのタイル $ 2 $ 枚を置く方法の一例として、 出力例のようなものがあります。

## 样例 #1

### 输入

```
3 4 4 2```

### 输出

```
YES
<><>
^<>^
v<>v```

## 样例 #2

### 输入

```
4 5 5 3```

### 输出

```
YES
<>..^
^.<>v
v<>.^
<><>v```

## 样例 #3

### 输入

```
7 9 20 20```

### 输出

```
NO```

# 题解

## 作者：w4p3r (赞：19)

一道比较巧妙的构造题。

为了方便，下文用$a$表示$1*2$的方块,$b$表示$2*1$的方块。

首先可以考虑，若我们先放$a$再放$b$，放$a$时我们肯定尽量将两个$a$堆在一起，这样才不会浪费。对于$b$也同理。

如下图这样：

![1](https://cdn.luogu.com.cn/upload/image_hosting/004ewuvl.png)

换句话说，我们会把棋盘分割成尽量多的$2*2$的矩形，每个矩形放两个$a$或两个$b$。

当然，当$n$或$m$为奇数时，我们会多出一行/列，多出的行只能放$a$，多出的列只能放$b$，我们直接放就好了。

如下图就是一种$n=5,m=5,A=4,B=8$的合法情况：

![2](https://cdn.luogu.com.cn/upload/image_hosting/z01h3b6a.png)

但是我们发现这种放法还是会WA 6个点，有什么问题呢？

当然是有问题的，例如$n=3,m=3,A=2,B=2$时，我们的程序会给出NO，但是实际上存在这一种情况：

![3](https://cdn.luogu.com.cn/upload/image_hosting/51c1sisq.png)

我们发现这种情况并没有把$a,b$放在$2*2$的矩形内，这是否代表我们的思路有很大问题呢？~~（我打vp的时候就是以为有很大问题然后就跳了）~~

但我们可以发现，通过这种方法，我们能放的方块总数并没有变（即$A+B$的最大值并不会改变），我们能进行的最多只有$A++,B--$，或者$A--,B++$。

进一步探究可以发现，这种情况发生，当前仅当$n,m$都是奇数时，我们选择牺牲掉一个$2*2$的方格，并同时放上一个$a,b$，如下图：

![4](https://cdn.luogu.com.cn/upload/image_hosting/xrwfeu0a.png)

(绿色表示我们划分出的，还未确定放什么的$2*2$空间)

这个图可以通过我们上述的操作变为：

![5](https://cdn.luogu.com.cn/upload/image_hosting/bns7bmlu.png)

在$n$为偶数或$m$为偶数时其实也可以进行上述变化，但是这样会使能放的方块总数减少，显然不能使原本不合法的情况合法。

判断这种情况，然后按照之前所述的方法放就可以了。

```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register int
#define fr first
#define sd second
#define pa pair<int,int>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define N 3010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline int lowbit(int x){return x&(-x);}
int n,m,A,B;
int vis[N][N],flag;
inline void END()
{
	if(A||B)cout<<"NO\n";
	else 
	{
		cout<<"YES\n";
		FOR(i,1,n)
		{
			FOR(j,1,m)
			{
				if(vis[i][j]==0)cout<<'.';
				if(vis[i][j]==1)cout<<'<';
				if(vis[i][j]==2)cout<<'>';
				if(vis[i][j]==3)cout<<'^';
				if(vis[i][j]==4)cout<<'v';
			}
			cout<<'\n';
		}	
	}
}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read(),A=read(),B=read();
	
	if(n&1)for(re j=1;j<m&&A;j+=2){vis[n][j]=1;vis[n][j+1]=2;A--;}
	if(m&1)for(re j=(n&1)?2:1/*方便进行变换*/;j<n&&B;j+=2){vis[j][m]=3;vis[j+1][m]=4;B--;}
	if(n==1||m==1){END();return 0;}
	if((A&1)&&(B&1)&&(n&1)&&(m&1))//显然只有这种情况才需要变换，如果不需要但我们变换了也不会影响原来的结果
	{
		vis[1][m-2]=3;vis[2][m-2]=4;
		vis[1][m]=2;vis[1][m-1]=1;
		A--,B--;
	}
	FOR(i,1,n-1)FOR(j,1,m-1)if(A&&!vis[i][j]&&!vis[i][j+1]&&!vis[i+1][j]&&!vis[i+1][j+1])
	{
		if(A>=2){vis[i][j]=1;vis[i][j+1]=2;vis[i+1][j]=1;vis[i+1][j+1]=2;A-=2;}
		else {vis[i][j]=1;vis[i][j+1]=2;A=0;break;}
	}
	FOR(i,1,n-1)FOR(j,1,m-1)if(B&&!vis[i][j]&&!vis[i][j+1]&&!vis[i+1][j]&&!vis[i+1][j+1])
	{
		if(B>=2){vis[i][j]=3;vis[i+1][j]=4;vis[i][j+1]=3;vis[i+1][j+1]=4;B-=2;}
		else {vis[i][j]=3;vis[i+1][j]=4;B=0;break;}
	}
	END();

	return 0;
}
//gl

```
**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**




---

## 作者：_l_l_ (赞：1)

提供另外一个思路：

我们考虑首先填充横向的方块，其次为纵向。我们需要使得在填充了若干横向方块过后能填充的纵向方块最大化。

当 $n,m$ 是偶数，我们第一个填充的横块无论放在哪里，都一定会使得纵向方块 $-2$，不妨放在 $\{(1,1),(1,2)\}$，然后我们发现一二列均空出来了两个空位，于是将下一个方块放在刚刚的下面就行。一直放下去一定是最优的。

当 $n$ 偶数 $m$ 奇数，发现策略是跟上面完全一样的。

当 $n$ 奇数 $m$ 偶数，我们先填第一行，这不会使得纵块的数量减少，然后刚好填完就变成上面的情况了。

当 $n,m$ 奇数，我们先填满第一行的前 $m-1$ 个格子，然后此时填充除了最后一列的所有列都会导致纵块数 $-1$，因此最优决策一定是填放最后两列，为了区别放在最后一行。之后我们按照顺序填放 $\{(2,m-2),(2,m-1)\}$（第一列被放了）、$\{(n,m-3),(n,m-2)\}$……填到第一列时候类似的再往右边填就行，手模一下发现非常优秀。

放完横块直接放纵块就行。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
char mat[MAXN][MAXN];
int main() {
	int n, m; scanf("%d %d", &n, &m);
	vector<pair<int, int>> vc;
	if (n % 2 == 0 && m % 2 == 0) {
		for (int i = 1; i < n; i += 2) for (int j = 1; j < m; j += 2) vc.push_back({i, j}), vc.push_back({i + 1, j});
	}
	else if (m % 2 == 0) {
		for (int j = 1; j < m; j += 2) vc.push_back({1, j});
		for (int i = 2; i < n; i += 2) for (int j = 1; j < m; j += 2) vc.push_back({i, j}), vc.push_back({i + 1, j});
	}
	else if (n % 2 == 0) {
		for (int i = 1; i < n; i += 2) for (int j = 1; j < m; j += 2) vc.push_back({i, j}), vc.push_back({i + 1, j});
	}
	else {
		for (int j = 1; j < m; j += 2) vc.push_back({1, j});
		for (int l = 2, r = n; l < r; l++, r--) {
			if (l & 1) for (int i = 1; i < m; i++) vc.push_back({i & 1 ? l : r, i});
			else for (int i = m - 1; i; i--) vc.push_back({i & 1 ? l : r, i});
		}
	}
	int p, q; scanf("%d %d", &p, &q);
	if (p > (int)vc.size()) return puts("NO"), 0;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) mat[i][j] = '.';
	for (int i = 0; i < p; i++) mat[vc[i].first][vc[i].second] = '<', mat[vc[i].first][vc[i].second + 1] = '>';
	for (int i = 1; i <= m; i++) for (int j = 1; j < n; j++) {
		if (mat[j][i] == '.' && mat[j + 1][i] == '.') {
			if (q) q--, mat[j][i] = '^', mat[j + 1][i] = 'v';
		}
	}
	if (q) return puts("NO"), 0;
	puts("YES"); for (int i = 1; i <= n; i++) puts(mat[i] + 1);
}
```

---

## 作者：xxgirlxx (赞：1)

###### ~~构造滚出OI！~~

一道~~十分简单~~的构造题。

## 题目

题目描述的十分清楚，就是问你在一个 $n \times m$ 的长方形中能否放下 $A$ 个 $1 \times 2$ 的长方形和 $B$ 个 $2 \times 1$ 的长方形。

# 思路

## 关于有解

~~思路其实挺好想~~，我们可以先想：怎么才能放下尽可能多的长方形？

那当然是将空间利用最大化啊！

那么，怎么才能将空间利用最大化呢？

看两种长方形的长和宽可以发现：两种长方形不能互相组合成一个**实心**的长方形，但是两种长方形却可以自己跟自己组合成 $2 \times 2$ 的**正方形**，也就是说，两种长方形可以通过组合成正方形来相互组合。所以，我们可以尽可能多的组合成正方形，然后填入大的长方形。

但是如果 $n$ 和 $m$ 中有奇数，用正方形填完后就会多出一行或列来，这时如果剩下的长方形又与剩下的行或列不匹配，就会导致错误的判断。所以，如果 $n$ 和 $m$ 中有奇数，我们就要先用对应的长方形去填补多出来的那一行或列，然后再用上面的方法填入。

**你以为完了吗**？这样依旧有弊端，比如说 `3 3 2 2` 这组数据，用上面的方法就会输出 `NO` 但实际上这组数据是有解的，解为：

```cpp
<>^
^.v
v<>
```

看到了吗？这种情况就会卡掉我们上面的做法，但我们怎么处理这种情况呢？

首先，我们只有在 $n$ 和 $m$ **都是奇数**的前提下，才会遇上这种情况，我们将其放在大长方形的右下角，会发现如果两边多出来的那一行和列也被填满了（最后三格不填），那么剩下的位置只不过就是 $n$ 和 $m$ 都是偶数的情况下在右下角填了一个 $2 \times 2$ 的正方形而已，还是可以按照最上面的方法照样填的。而且，这种情况哪怕在 $n$ 和 $m$ **都是奇数**的前提下，还要在填完多出来的一行和列后（最后三格不填）$A$ 和 $B$ **都是偶数**的情况下，我们才会需要用上这种情况，因为如果 $A$ 和 $B$ **都是奇数**的话，我们就可以把多的那一个填到多的那一行和列上（填在倒数第二格和倒数第一个），这样是比按照偶数的方法填要节省空间的，因为同为三个，奇数的方法填只需要 $3 \times 3 + 2 \times 2$ 的空间，但是偶数的方法却需要 $3 \times 3 + 2 \times 2 + 2 \times 2$，所以把多的那一个填到多的那一行和列上（填在倒数第二格和倒数第一个）是更优的。

## 关于无解

我们可以在把多出来的行和列填完之后，以 $2 \times 2$ 的正方形为单位，计算总共需要多少个 $2 \times 2$ 的正方形，如果大于总共拥有的正方形数量，那么就放不下，输出 `NO`。

### 最后献上蒟蒻丑陋的代码：

我写的比较像分讨，很多地方有重复的，蒟蒻太懒懒得简化，还请各位神犇见谅：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,a,b,an,bn,num,nowx=1,nowy=0,flag;
char ans[1010][1010];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>a>>b;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans[i][j]='.';
	if(n%2+m%2==0){
		an=a/2,bn=b/2,num=(n/2)*(m/2)-an-bn-a%2-b%2;
		if(num<0){cout<<"NO"<<endl;return 0;}
		for(int i=1;an>0;i++)for(int j=1;j*2<=m&&an>0;j++,an--)nowx=i,nowy=j,ans[i*2-1][j*2-1]=ans[i*2][j*2-1]='<',ans[i*2-1][j*2]=ans[i*2][j*2]='>';
		for(int i=nowx;bn>0;i++)for(int j=(i==nowx?nowy+1:1);j*2<=m&&bn>0;j++,bn--)ans[i*2-1][j*2-1]=ans[i*2-1][j*2]='^',ans[i*2][j*2-1]=ans[i*2][j*2]='v';
		if(a%2+b%2==1){
			if(a%2==1)ans[n-1][m-1]='<',ans[n-1][m]='>';
			else ans[n-1][m-1]='^',ans[n][m-1]='v';
		}
		if(a%2+b%2==2)ans[n-1][m-3]='^',ans[n][m-3]='v',ans[n-1][m-2]='<',ans[n-1][m-1]='>';
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cout<<ans[i][j];
			cout<<endl;
		}
	}
	if(n%2+m%2==1){
		if(n%2==1){
			for(int i=1;i*2<=m&&a>0;i++,a--)ans[n][i*2-1]='<',ans[n][i*2]='>';
			flag=0,n--;
		}
		else{
			for(int i=1;i*2<=n&&b>0;i++,b--)ans[i*2-1][m]='^',ans[i*2][m]='v';
			flag=1,m--;
		}
		an=a/2,bn=b/2,num=(n/2)*(m/2)-an-bn-a%2-b%2;
		if(num<0){cout<<"NO"<<endl;return 0;}
		for(int i=1;an>0;i++)for(int j=1;j*2<=m&&an>0;j++,an--)nowx=i,nowy=j,ans[i*2-1][j*2-1]=ans[i*2][j*2-1]='<',ans[i*2-1][j*2]=ans[i*2][j*2]='>';
		for(int i=nowx;bn>0;i++)for(int j=(i==nowx?nowy+1:1);j*2<=m&&bn>0;j++,bn--)ans[i*2-1][j*2-1]=ans[i*2-1][j*2]='^',ans[i*2][j*2-1]=ans[i*2][j*2]='v';
		if(a%2+b%2==1){
			if(a%2==1)ans[n-1][m-1]='<',ans[n-1][m]='>';
			else ans[n-1][m-1]='^',ans[n][m-1]='v';
		}
		if(a%2+b%2==2)ans[n-1][m-3]='^',ans[n][m-3]='v',ans[n-1][m-2]='<',ans[n-1][m-1]='>';
		if(flag==0)n++;
		else m++;
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cout<<ans[i][j];
			cout<<endl;
		}
	}
	if(n%2+m%2==2){
		for(int i=1;i*2<=m-3&&a>0;i++,a--)ans[n][i*2-1]='<',ans[n][i*2]='>';
		for(int i=1;i*2<=n-3&&b>0;i++,b--)ans[i*2-1][m]='^',ans[i*2][m]='v';
		if(a%2+b%2==0&&a>=2&&b>=2)flag=1,a-=2,b-=2,ans[n-2][m-2]=ans[n][m-1]='<',ans[n-2][m-1]=ans[n][m]='>',ans[n-2][m]=ans[n-1][m-2]='^',ans[n][m-2]=ans[n-1][m]='v';
		else{
			if(a%2==1)a--,ans[n][m-2]='<',ans[n][m-1]='>';
			if(b%2==1)b--,ans[n-2][m]='^',ans[n-1][m]='v';
		}
		n--,m--,an=a/2,bn=b/2,num=(n/2)*(m/2)-an-bn-a%2-b%2-flag;
		if(num<0){cout<<"NO"<<endl;return 0;}
		for(int i=1;an>0;i++)for(int j=1;j*2<=m&&an>0;j++,an--)nowx=i,nowy=j,ans[i*2-1][j*2-1]=ans[i*2][j*2-1]='<',ans[i*2-1][j*2]=ans[i*2][j*2]='>';
		for(int i=nowx;bn>0;i++)for(int j=(i==nowx?nowy+1:1);j*2<=m&&bn>0;j++,bn--)ans[i*2-1][j*2-1]=ans[i*2-1][j*2]='^',ans[i*2][j*2-1]=ans[i*2][j*2]='v';
		n++,m++;
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cout<<ans[i][j];
			cout<<endl;
		}
	}
	return 0;
}
```

~~求管理员大大给过~~。

---

## 作者：zhylj (赞：1)

若 $n,m$ 之一是偶数，可以发现分成若干 $2\times 2$ 后填满是最优的。然后如果 $n,m$ 中有奇数则会多出一行 / 列，那再塞剩下的就好了。

否则继续讨论 $A,B$ 的奇偶性，用如下方式构造最后一行和最后一列附近的格子（若某一类的数量甚至填不满最后一行 / 列，则全部塞边上就不会影响另一类了），使得 $A,B$ 剩下都为偶数，那就可以两两匹配出一个 $2\times 2$ 的格子把剩下的位置填满，这样能做到最后只剩下 $1$ 个空位，显然不可能再多了：


```
....^    ....^    ....^
....v    ....v    ....v
....^    ..<>^    ...^^
....v    ..^.v    ..^vv
<><>.    <>v<>    <>v<>
```

---

## 作者：Mortidesperatslav (赞：0)

萌新的第 $100$ 篇题解。

因为 $n,m$ 不分挂惨了，所以决定写题解并立 flag（flag 是什么请私信我）。

注意到砖是 $1 \times 2$ 和 $2 \times 1$ 的。显然是让我们对 $n$ 和 $m$ 的奇偶性进行讨论啊。

然后我们直接讨论。

### 一、$n$ 为偶，$m$ 为偶

把两种砖块尽可能拼成 $2 \times 2$ 填充，剩余两种砖块至多各一块，用这些砖填剩下的空位，这样一定最优。

证明：如果一行填满了，这一行 B 类砖一定填了偶数块，A 类砖一定构成 $2 \times 2$ 的结构，考虑进行平移，就会发现都是 $2 \times 2$ 的结构。一列同理。可以证明，剩下的砖一定没有更优的填法。

### 二、$n$ 为偶，$m$ 为奇

把第 $m$ 列用 B 类砖填满，然后就转化成了第一种情况。

### 三、$n$ 为奇，$m$ 为偶

把第 $n$ 行用 A 类砖填满，然后就转化成了第一种情况。

### 四、$n$ 为奇，$m$ 为奇

考虑一个问题；把第 $n$ 行前 $m-1$ 个格子用 A 类砖填满，并把第 $m$ 列前 $n-1$ 个格子用 B 类砖填满，转化为第一种情况，一定最优吗？

可以给出一组 Hack：

```plain
3 3 2 2
```

可以发现，这样填会判成无解，而实际上存在如下解：

```plain
^<>
v.^
<>v
```

难道我们假完了吗？并没有，仔细分析会发现，这种情况只能够在 $n$ 为奇 $m$ 为奇的时候把棋盘上的一块砖换成另外一类，并且会把棋盘割裂成三块：

1. $3 \times 3$ 的一小块。

2. $n \times (m - 3)$ 的一小块，满足第三种情况。

3. $3 \times (n - 3)$ 的一小块，满足第三种情况。

仔细观察可以发现，这种操作不能用于前三种情况，否则填完后棋盘上空位只会变多，一定不优。

于是就可以得出结论：这种转化操作最多执行一次。实现的时候重新填一遍就好。

因为奶猫非常不聪明，所以就按照上面的思路老老实实写了一个非常非常冗长的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, x, y;
int ans[1005][1005];
string s = ".^v<>";
void fill_hor(int pos_x, int pos_y){
	ans[pos_x][pos_y] = 3;
	ans[pos_x][pos_y + 1] = 4;
}
void fill_ver(int pos_x, int pos_y){
	ans[pos_x][pos_y] = 1;
	ans[pos_x + 1][pos_y] = 2;
}
void check(){
	if (x || y){
		cout << "NO";
		exit(0);
	}
}
void print(){
	check();
	cout << "YES\n";
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++)
			cout << s[ans[i][j]];
		cout << "\n"; 
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m >> x >> y;
	if ((x + y << 1) > n * m){
		cout << "NO";
		return 0;
	}
	if (!(n & 1) && !(m & 1)){
		for (int i = 1; i < n; i += 2)
			for (int j = 1; j < m; j += 2){
				if (x >= 2){
					fill_hor(i, j);
					fill_hor(i + 1, j);
					x -= 2;
				}else if (y >= 2){
					fill_ver(i, j);
					fill_ver(i, j + 1);
					y -= 2;
				}else if (x == 1){
					fill_hor(i, j);
					--x;
				}else if (y == 1){
					fill_ver(i, j);
					--y;
				}
			}
		print();
	}else if ((n & 1) && !(m & 1)){
		for (int i = 1; i < m; i += 2){
			if (x){
				fill_hor(n, i);
				--x;
			}
		}
		for (int i = 1; i < n - 1; i += 2)
			for (int j = 1; j < m; j += 2){
				if (x >= 2){
					fill_hor(i, j);
					fill_hor(i + 1, j);
					x -= 2;
				}else if (y >= 2){
					fill_ver(i, j);
					fill_ver(i, j + 1);
					y -= 2;
				}else if (x == 1){
					fill_hor(i, j);
					--x;
				}else if (y == 1){
					fill_ver(i, j);
					--y;
				}
			}
		print();
	}else if (!(n & 1) && (m & 1)){
		for (int i = 1; i < n; i += 2){
			if (y){
				fill_ver(i, m);
				--y;
			}
		}
		for (int i = 1; i < n; i += 2)
			for (int j = 1; j < m - 1; j += 2){
				if (x >= 2){
					fill_hor(i, j);
					fill_hor(i + 1, j);
					x -= 2;
				}else if (y >= 2){
					fill_ver(i, j);
					fill_ver(i, j + 1);
					y -= 2;
				}else if (x == 1){
					fill_hor(i, j);
					--x;
				}else if (y == 1){
					fill_ver(i, j);
					--y;
				}
			}
		print();
	}else if ((n & 1) && (m & 1)){
		int tx = x, ty = y;
		for (int i = 1; i < n - 1; i += 2){
			if (y){
				fill_ver(i, m);
				--y;
			}
		}
		for (int i = 1; i < m - 1; i += 2){
			if (x){
				fill_hor(n, i);
				--x;
			}
		}
		for (int i = 1; i < n - 1; i += 2)
			for (int j = 1; j < m - 1; j += 2){
				if (x >= 2){
					fill_hor(i, j);
					fill_hor(i + 1, j);
					x -= 2;
				}else if (y >= 2){
					fill_ver(i, j);
					fill_ver(i, j + 1);
					y -= 2;
				}else if (x == 1){
					fill_hor(i, j);
					--x;
				}else if (y == 1){
					fill_ver(i, j);
					--y;
				}
			}
	//	cout << x << " " << y << "\n";
		if (x || y){
			x = tx, y = ty;
			memset(ans, 0, sizeof ans);
			for (int i = 1; i < n - 3; i += 2){
				if (y){
					fill_ver(i, m);
					--y;
				}
			}
			for (int i = 1; i < m - 3; i += 2){
				if (x){
					fill_hor(n, i);
					--x;
				}
			}
			fill_hor(n - 2, m - 2);
			fill_ver(n - 2, m);
			fill_ver(n - 1, m - 2);
			fill_hor(n, m - 1);
			x -= 2;
			y -= 2;
			for (int i = 1; i < n - 1; i += 2)
				for (int j = 1; j < m - 1; j += 2){
					if (i >= n - 2 && j >= m - 2)
						break;
					if (x >= 2){
						fill_hor(i, j);
						fill_hor(i + 1, j);
						x -= 2;
					}else if (y >= 2){
						fill_ver(i, j);
						fill_ver(i, j + 1);
						y -= 2;
					}else if (x == 1){
						fill_hor(i, j);
						--x;
					}else if (y == 1){
						fill_ver(i, j);
						--y;
					}
				}
		}
	//	cout << x << " " << y << "\n"; 
		print();
	}
	return 0;
}
```

上面的代码分类应该相当明确了，希望大家不要学习杂鱼奶猫，否则在考场上如果键盘寄了就会因为代码过长挂 $100+$ 分。

---

