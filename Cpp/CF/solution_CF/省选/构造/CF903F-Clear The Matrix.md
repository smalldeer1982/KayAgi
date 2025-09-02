# Clear The Matrix

## 题目描述

给定一个4×n的元素只为'*'或'.'的矩阵f

你可以不断地选择一个f的子方阵,并将方阵的元素都变为'.'

选择一个k×k的方阵需要代价$a_k$​。

问最少要多少代价,才能将所有元素都变为'.'

## 样例 #1

### 输入

```
4
1 10 8 20
***.
***.
***.
...*
```

### 输出

```
9
```

## 样例 #2

### 输入

```
7
2 1 8 2
.***...
.***..*
.***...
....*..
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
10 10 1 10
***.
*..*
*..*
.***
```

### 输出

```
2
```

# 题解

## 作者：Lauzun (赞：4)

一看到矩阵只有四行，果断想状压$DP$

不得不说这个题的状态设计确实有点神仙。

我们从第$0$列开始，一列一列向后考虑，

$dp[i][j]$表示考虑到第 $i$ 行，前 $i-1$ 列已经全部变成“$.$”，现在第 $i$ 到第 $i+3$ 列状态为 $j$ 的最小花费。

为什么 $j$ 只表示第 $i$ 到第 $i+3$ 列的状态呢？因为可以用来覆盖的正方形最大边长为 $4$，所以当前在 $i$ 时，是影响不到 $i+4$ 的。

也就是说 $dp$ 数组的第二维只需要 $1 << 4$ 即可 _~~(这么想，多了你也开不下啊)~~_ 

然后，我们用$mx[k][p]$表示边长为 $p$ 的正方形，放在第 $k$ 行，所能覆盖到的状态。

易得 _~~(怎么就易得了。。)~~_ $dp[i][j$ & $mx[k][p]]=min${$dp[i][j]+w[p]$}。$(w[p]$表示边长为 $p$ 的正方形的代价，即读入的第二行$)$

需要注意的一点是，如果第 $i$ 行本身就全部为“$.$”，那么可以直接转移，此时$S$ & $15==0$

其余的就没什么细节了。

快乐的代码时间$:$

```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
#define maxn 20
#define maxm 1005
#define inf 0x3f3f3f3f
using namespace std;
char c;//c用来读入矩阵 
int n, now, pos;//n为列数，now用来预处理mx，pos用来预处理dp数组 
int w[maxn], f[maxm];//w读入花费,f存储初始状态 
int mx[maxn][maxn], m[maxn][maxn];//mx[k][p]表示边长为p的正方形，放在第k行，所能覆盖到的状态。m用来预处理mx 
int dp[maxm][(1 << 16) + 4];//dp数组，本题的精髓，第二维只需要(1<<16)，表示第i列到第i+3列的状态

void init() {
	scanf("%d", &n);
	for(int i = 1; i <= 4; i ++) scanf("%d", &w[i]);
	//上方读入没什么说的了吧。。 
	for(int i = 0; i < 4; i ++)	
		for(int j = 0; j < n; j ++) {
			cin >> c;
			f[j] <<= 1;
			if(c == '*') f[j] ++;
		}
	//用c读入矩阵，顺便得到初始状态 
	for(int i = 0; i < 4; i ++)
		for(int j = 1; j <= 4 - i; j ++) {
			for(int k = 0; k < 4; k ++)
				for(int p = 0; p < 4; p ++)
					m[k][p] = 1;
			for(int k = 0; k < j; k ++)
				for(int p = 0; p < j; p ++)
					m[k][i + p] = 0;
			now = 0;
			for(int k = 3; k >= 0; k --)
				for(int p = 0; p < 4; p ++)
					now = (now << 1) + m[k][p];
			mx[i][j] = now;
		}
	//预处理mx数组，为什么这么预处理就留给各位思考了qwq(想一想，为什么？) 
	memset(dp, inf, sizeof(dp));//初始化dp数组 
	for(int i = 3; i >= 0; i --) {
		pos <<= 4;
		pos += f[i];
	}
	//pos是最开始四列的状态 
	dp[0][pos] = 0;//记得要将最开始的状态的花费变成0，即不需要任何代价即可得到（这个显然得不能再显然吧） 
}

void work() {
	for(int i = 0; i <= n; i ++)//枚举0~n-1列 
		for(int j = (1 << 16) - 1; j >= 0; j --) {//枚举状态 
			if(dp[i][j] >= inf - 10) continue; 
			if(!(j & 15)) {//如果当前已经满足，那么直接到下一行 
				int now = (f[i + 4] << 12) | (j >> 4);//now得到下一行的状态 
				dp[i + 1][now] = min(dp[i][j], dp[i + 1][now]);
			}
			for(int k = 0; k < 4; k ++)//这个就是上面说的了，k表示正方形放在哪一行 
				for(int p = 1; p <= 4 - k; p ++)//p表示正方形的边长 
					dp[i][j & mx[k][p]] = min(dp[i][j & mx[k][p]], dp[i][j] + w[p]);//进行上面说的dp 
		}
}

int main() {
	init();//愉快的预处理
	work();//开心的work函数，使main变得辣么短QuQ 
	printf("%d\n", dp[n][0]);
    //输出当前在第n列（因为我们最多到第n-1列，所以在第n列说明前n-1列全部考虑完了），状态为0的最小花费。 
}
```


---

## 作者：hegm (赞：3)

抽象题，不过是我的做法抽象。

首先看到题面 $4\times n$ 就考虑暴力记录状态。

$f_{i,a,b,c,d}$ 表示考虑前 $i$ 列，第 $1$ 行最远的 $*$ 距离当前距离为 $a$，$b,c,d$ 以此类推。并且我钦定，在状态 $i$ 上只能操作右边界紧贴 $i$ 这一列的矩形。

这个状态看上去就非常的美妙，并且转移非常简单。

在转移之前，我们需要处理一下四种矩阵的成本让我们更加方便的转移。

```cpp
for(int i=3;i>=1;i--)w[i]=min(w[i],w[i+1]);
w[2]=min(w[2],4*w[1]);
w[3]=min({w[3],4*w[2],w[2]+5*w[1],2*w[2]+2*w[1]});
w[4]=min({w[4],4*w[2],w[3]+3*w[2],w[3]+w[2]+4*w[1],w[3]+7*w[1],2*w[3]+2*w[1]});
```

意思很简单，只需要让一次选择 $k\times k$ 的花费尽可能的少即可。

然后考虑转移，我们枚举一个状态 $(i,a,b,c,d)$。

然后考虑把 $i+1$ 这一行加入当前状态中，显然对于 $a,b,c,d=4$ 这种状态，我们再加入 $i+1$ 这一行距离就为 $5$ 了，无法影响，因此 $a,b,c,d\in (0,3)$。

然后我们对于状态加入 $i+1$ 这一列的状态为 $pa,pb,pc,pd$。

我们分情况讨论删除的情况：具体的，我们枚举哪些位置被删除为 $0$。对于每种情况，我们分讨使用了哪些矩阵。

代码非常简单。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ull unsigned long long
#define make make_pair
#define val(i,a,b,c,d) f[i][a][b][c][d]
#define N 1005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,w[5],f[N][5][5][5][5],pa,pb,pc,pd;
char C[5][N];
void gmin(int &a,int b)
{
	a=min(a,b);
}
int g(int l,int r)
{
	int mx=0;
	if(l<=1&&1<=r)mx=max(mx,pa);
	if(l<=2&&2<=r)mx=max(mx,pb);
	if(l<=3&&3<=r)mx=max(mx,pc);
	if(l<=4&&4<=r)mx=max(mx,pd);
	mx=max(mx,r-l+1);
	return w[mx];
}
signed main()
{
	n=read();
	for(int i=1;i<=4;i++)w[i]=read();
	for(int i=3;i>=1;i--)w[i]=min(w[i],w[i+1]);
	w[2]=min(w[2],4*w[1]);
	w[3]=min({w[3],4*w[2],w[2]+5*w[1],2*w[2]+2*w[1]});
	w[4]=min({w[4],4*w[2],w[3]+3*w[2],w[3]+w[2]+4*w[1],w[3]+7*w[1],2*w[3]+2*w[1]});
//	cout<<w[1]<<" "<<w[2]<<" "<<w[3]<<" "<<w[4]<<"|\n";
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=4;i++)scanf("%s",C[i]+1);
	f[0][0][0][0][0]=0;
	for(int i=0;i<=n;i++)
	{
		for(int a=0;a<=3;a++)for(int b=0;b<=3;b++)for(int c=0;c<=3;c++)for(int d=0;d<=3;d++)
		{
			if(f[i][a][b][c][d]!=f[0][1][1][1][1]);//cout<<i<<" "<<a<<" "<<b<<" "<<c<<" "<<d<<":"<<f[i][a][b][c][d]<<"\n";
			else continue;
			pa=a+1,pb=b+1,pc=c+1,pd=d+1;int to=f[i][a][b][c][d];
			if(a==0&&C[1][i+1]=='.')pa=0;if(b==0&&C[2][i+1]=='.')pb=0;
			if(c==0&&C[3][i+1]=='.')pc=0;if(d==0&&C[4][i+1]=='.')pd=0;
			gmin(val(i+1,pa,pb,pc,pd),to);
			gmin(val(i+1,0,pb,pc,pd),to+w[pa]);
			gmin(val(i+1,pa,0,pc,pd),to+w[pb]);
			gmin(val(i+1,pa,pb,0,pd),to+w[pc]);
			gmin(val(i+1,pa,pb,pc,0),to+w[pd]);
			gmin(val(i+1,0,0,pc,pd),to+min(w[max({pa,pb,2})],w[pa]+w[pb]));
			gmin(val(i+1,0,pb,0,pd),to+w[pa]+w[pc]);
			gmin(val(i+1,0,pb,pc,0),to+w[pa]+w[pd]);
			gmin(val(i+1,pa,0,0,pd),to+min(w[max({pc,pb,2})],w[pb]+w[pc]));
			gmin(val(i+1,pa,0,pc,0),to+w[pb]+w[pd]);
			gmin(val(i+1,pa,pb,0,0),to+min(w[max({pc,pd,2})],w[pc]+w[pd]));
			gmin(val(i+1,0,0,0,pd),to+min({w[pa]+w[pb]+w[pc],g(1,2)+w[pc],w[pa]+g(2,3),g(1,3)}));
			gmin(val(i+1,0,0,pc,0),to+min({w[pa]+w[pd]+w[pb],g(1,2)+w[pd],g(1,4)}));
			gmin(val(i+1,0,pb,0,0),to+min({w[pa]+w[pd]+w[pc],g(3,4)+w[pa],g(1,4)}));
			gmin(val(i+1,pa,0,0,0),to+min({w[pd]+w[pb]+w[pc],g(2,3)+w[pd],w[pb]+g(3,4),g(2,4)}));
			gmin(val(i+1,0,0,0,0),to+min({g(1,4),w[pa]+w[pd]+w[pb]+w[pc],w[pa]+g(2,4),w[pa]+w[pb]+g(3,4),g(1,2)+g(3,4),g(1,2)+w[pc]+w[pd],g(1,3)+w[pd],w[pa]+w[pd]+g(2,3)}));
		}
	}
	cout<<f[n][0][0][0][0];
	return 0;
}

```

---

## 作者：RedLycoris (赞：0)

题目大意：

有一个 $4\times n$ 的 $01$ 矩阵。你每次可以选择一个 $k \times k (1 \le k \le 4)$ 大小的子矩阵，将其中的值都赋为 $0$，代价为 $a_k$。问你最小的代价使得整个矩阵的值都为 $0$。

题解：

萌萌题。

看到只有 $4$ 行就想到可以状压 $dp$。

令 $dp_{i,mask}$ 表示考虑到底 $i$ 列，当前第 $i-3$ 至 $i-1$ 列的状态为 $msk$。

我们考虑从前往后赋值。$dp_i$ 能够转移到 $dp_{i+1}$ 当且仅当第 $i-3$ 列已经全部赋值为 $0$了，因为到后面就再也不可能赋值它了。

但这个转移有点恶心，具体的可以参照代码里的注释。

```cpp
using namespace std;
char c[5][1005];
int n,p,q,r,s; 
bool a[5][1005];
int dp[1005][5555];
int tmp[5][5];     //tmp是当前考虑的第 i-3 列至第 i 列的矩阵的值
inline int get(){   //解压
	int rt=0,cnt=0;
	for(int i=1;i<=4;++i){
		for(int j=2;j<=4;++j){
			rt+=tmp[i][j]<<cnt;
			++cnt;
		}
	}
	return rt;
}
inline void rget(int msk){ //对这三列进行压缩
	for(int i=1;i<=4;++i){
		for(int j=1;j<=3;++j){
			tmp[i][j]=msk&1;
			msk>>=1;
		}
	}
}
inline void Min(int&x,int y){if(x>y)x=y;}
int tmpc[555][5][5],sta;//这个tmpc是在转移的时候存储tmp，应为我们要模拟赋值对tmp更改 前面还要开一维是应为它是递归，如果不开会覆盖上一层存储的东西
inline void cpy(){++sta;for(int i=1;i<=4;++i)for(int j=1;j<=4;++j)tmpc[sta][i][j]=tmp[i][j];}//存储
inline void rcpy(){for(int i=1;i<=4;++i)for(int j=1;j<=4;++j)tmp[i][j]=tmpc[sta][i][j];--sta;}//还原
inline void go(int i,int j,int msk,int cur=0){//考虑如何把最前面那一列全部赋为 0
	if(j==5){//到头了
		Min(dp[i+1][get()],dp[i][msk]+cur);
		return;
	}
	if(j==1)Min(dp[i+1][0],dp[i][msk]+s);//覆盖 4*4 的
	if(j<=2){ //3*3
		cpy();
		for(int e=0;e<3;++e)for(int f=0;f<3;++f)tmp[j+f][e+1]=0;
		go(i,j+1,msk,cur+r);
		rcpy();
	}
	if(j<=3){ //2*2
		cpy();
		for(int e=0;e<2;++e)for(int f=0;f<2;++f)tmp[j+f][e+1]=0;
		go(i,j+1,msk,cur+q);
		rcpy();
	}
	{//1*1
		cpy();
		tmp[j][1]=0;
		go(i,j+1,msk,cur+p);
		rcpy();
	}
	if(tmp[j][1]==0)go(i,j+1,msk,cur);//因为不用覆盖，可以考虑直接跳到下一行
}
inline void solve(){
	cin>>n>>p>>q>>r>>s;
	for(int i=1;i<=4;++i){
		for(int j=1;j<=n;++j)cin>>c[i][j];
		for(int j=n+1;j<=n+3;++j)c[i][j]='.';
	}
	n+=3;//我们从第4列开始考虑的，而且转移的时候是要求第 i-3 列全部清空，如果不 +3 的话第 n-2 列至第 n 列就会没有被考虑进去
	for(int i=1;i<=4;++i){
		for(int j=1;j<=n;++j){
			if(c[i][j]=='.')a[i][j]=0;
			else a[i][j]=1;
		}
	}
	memset(dp,63,sizeof(dp));
	int inf=dp[0][0];
	for(int i=1;i<=4;++i)for(int j=1;j<=3;++j)tmp[i][j+1]=a[i][j];
	dp[4][get()]=0;
	for(int i=4;i<=n;++i){
		for(int msk=0;msk<(1<<12);++msk){
			if(dp[i][msk]>=inf)continue;
			rget(msk);
			for(int j=1;j<=4;++j)tmp[j][4]=a[j][i];
			go(i,1,msk);
		}
	}
	cout<<dp[n+1][0]<<'\n';
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;
	//cin>>T;
	for(;T--;)solve();
	return 0;
}
```

---

