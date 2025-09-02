# [PA 2019 Final] 摆棋 / Pionki

## 题目背景

译自 PA 2019 Final。


本题数据为自造。

std：zimpha，validator：Starrykiller，generator：Wuyanru & Starrykiller。

## 题目描述

给定一个 $A\times B\times C$ 的立体棋盘。每个格子可以用三元组 $(i,j,k)$ 描述，其中 $1\le i\le A$，$1\le j\le B$，$1\le k\le C$。

起初，$(i,j,k)$ 上有 $a_{i,j,k}$ 个棋子。

每次操作，可以选择一个格子 $(i,j,k)$，满足 $(i,j,k)$ 上至少有一个棋子，然后将这枚棋子移动到 $(i+1,j,k)$ 或 $(i,j+1,k)$ 或 $(i,j,k+1)$ 中的一个。棋子不能移出棋盘边界。

目标是让 $(i,j,k)$ 上有 $b_{i,j,k}$ 个棋子。判断是否能够达成目标。




## 说明/提示

- $1\le T\le 10^4$；
- $1\le A,\sum A\le 10^4$；
- $1\le B,C\le 6$；
- $0\le a_{i,j,k},b_{i,j,k}\le 10^{12}$；
- $\sum a_{i,j,k}=\sum b_{i,j,k}$。



## 样例 #1

### 输入

```
2
2 3 4
2 0 0 1
0 0 1 0
1 0 0 0

0 1 0 0
1 0 0 0
0 0 0 0

0 0 1 0
0 1 0 0
0 0 0 0

1 0 0 0
0 0 0 0
0 0 0 4
2 2 2
2 2
2 1

2 1
1 1

1 1
1 2

1 2
2 2```

### 输出

```
NIE
TAK```

# 题解

## 作者：TruchyR (赞：3)

知识点：Hall 定理、轮廓线 dp。

赛时被队友一眼秒了但是自己不会怎么办。

**本文内棋子可以移动的方向和题目里的相反**。

我们把初始状态的每个棋子看作一个左部点，最终状态的每个棋子看作一个右部点。

在可以到达的状态之间连边，本题就是在求这个二分图是否存在完备匹配。

根据 Hall 定理，一个二分图存在完备匹配的充要条件是对于左部点的大小为 $k$ 的任意子集 $S$，这些点在右部连到的点集大小不小于 $k$。

所以我们令 $c_{i,j,k}=a_{i,j,k}-b_{i,j,k}$，我们要求的就是以下问题。

选取若干个点，如果有一个点被某个选择的点偏序了那么这个点也要选。使得选出的点的权值 $c$ 之和最大。

如果这个最大值大于 $0$，就说明存在一个点集不满足上述条件。

设 $p_{i,j}$ 表示第 $i$ 块第 $j$ 行选了前 $p_{i,j}$ 个点。根据偏序关系容易有 $p_{i,j}\geq p_{i,j+1}$ 和 $p_{i,j}\geq p_{i+1,j}$。

因为后两维的数据范围很小，考虑直接把他们压缩在一起。状态数的计算考虑组合意义，即 $C_{6+6}^{6}=924$。

有第一种状态 $f_{i,w}$ 表示考虑到第 $i$ 层且第 $i$ 层选点状态是 $w$，权值和的最大值。

直接暴力转移是 $O(n\times 924^2)$ 的，大抵是过不去。

怎么办？可以考虑轮廓线 dp。

假如轮廓线现在的状态长这样：  
| $p_{i,j}$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$j-1$|$/$|$/$|$/$|$?$|$1$|$0$|
|$j$|$6$|$3$|$3$|$2$|$/$|$/$|

那么我们枚举问号处选中了多少个点，就可以从上一个轮廓线的状态转移。

还是因为偏序关系，这里轮廓线的总状态数顶天是 $6\times 924$ 的，加上转移复杂度仍然是可以过的。

实现时建议开滚动数组，以及特判 $B=1$ 时带来的一些问题。

代码前面几行也是简要的题解。

```cpp
//学习Hall定理和轮廓线dp。 
//首先每个棋子看成一个点 a是左部点b是右部点
//能移动到的连边 这题就是在求是否有完备匹配
//Hall定理：一个图存在完备匹配的充要条件是
//          对于任意大小为k的左部点集S，它的可达右部点集T大小>=k
//那么令c[i][j][k]=a[i][j][k]-b[i][j][k]
//我们要选择一些点(如果一个点选了那么被偏序的必须选)
//使得sum(c[i][j][k])最大。
//其他两维很小，考虑直接压缩状态 
// #####. 首先对于一层的点的选择状态肯定长这样。 
// #####. 考虑直接把第三维压掉变成二维问题。 
// ####.. 从上往下转移，每层选的点数肯定也和上一层偏序。 
// ####.. 然后转移是一个高维前缀max 但是不好做 实际上和状压差不多 
// ##.... 我们考虑轮廓线dp！
//        假如轮廓线现在长这样（存储为f[4][6,3,3,2,1,0]） 
// ...?10 那么我们只需要枚举?位置的值就可以从f[3][6,3,3,?,1,0]转移过来了
// 6332   用组合意义粗略估算有效状态数约为C(12,6)*6=5544。轻微卡常。 
#include<bits/stdc++.h>
#define MX 10005
#define int long long
#define CKE if(CHECK)
#define FRE if(FIL)
using namespace std;
const int CHECK=0,FIL=0;int read();
int T,n,x,y,cnt,a[MX][7][7],b[MX][1000];
int f[117649],p[1000][8],q[7],g[7][1000]; 
void dfs(int t,int lst,int o){
	if(t>x){
		p[++cnt][0]=o;f[o]=cnt;
		for(int i=1;i<=x;i++)
			p[cnt][i]=q[i];
		p[cnt][x+1]=0;
		return;
	}
	for(int i=0;i<=lst;i++){
		q[t]=i;dfs(t+1,i,o*(y+1)+i);}
}
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	FRE freopen(".in","r",stdin);
	FRE freopen(".out","w",stdout);
	T=read();while(T--){
		n=read();x=read();y=read(); 
		for(int i=n;i>=1;i--) for(int j=x;j>=1;j--) for(int k=y;k>=1;k--)
			a[i][j][k]=read();
		for(int i=n;i>=1;i--) for(int j=x;j>=1;j--) for(int k=y;k>=1;k--)
			a[i][j][k]-=read();
		//搜索所有可能状态 & 其他预处理 
		//p[t][0] 第t个状态hash值
		//p[t][1~x] 第t个状态代表什么
		//f[h] hash值为h的是哪个状态
		//b[i][t] 第i层 第t个状态覆盖的点的权值和 
		cnt=0;dfs(1,y,0);
		memset(g[0],-0x3f,sizeof(g[0]));
		g[0][1]=0,q[x]=1;
		for(int i=x-1;i>=0;i--) q[i]=q[i+1]*(y+1);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=cnt;j++){
				b[i][j]=0;
				for(int k=1;k<=x;k++) for(int l=1;l<=p[j][k];l++)
					b[i][j]+=a[i][k][l];
			}
		}
		//轮廓线 dp
		int res=0;
		for(int t=n;t>=1;t--){
			for(int o=1;o<=x;o++){
				for(int I=1;I<=cnt;I++){
					//第t块
					//轮廓线包含第t块前o个和第t-1块的后B-o个状态 
					//这些状态叠起来是第I个状态 
					int lo=p[I][o+1];
					int hi=p[I][o];
					int zt=p[I][0]-q[o]*hi;
					if(x>1) g[o%x][I]=-1e18;
					for(int i=lo;i<=hi;i++)
						g[o%x][I]=max(g[o%x][I],g[o-1][f[zt+q[o]*i]]);
				}
			}
			//这一层枚举完了 加上对应权值 
			for(int I=1;I<=cnt;I++){
				g[0][I]+=b[t][I];
				if(t==1) res=max(res,g[0][I]);
			}
		}
		if(res>0) printf("NIE\n");
		else printf("TAK\n");
	}
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```

---

## 作者：_wsq_ (赞：2)

更新于 2025/1/25：修复了一处笔误。

注：本做法由 [RDFZchenyy](https://www.luogu.com.cn/user/567610) 提出，我实现，并在比赛最后五分钟 AC。

先说结论：若对于每一个满足 $st_{x_1,y_1,z_1}\le st_{x_2,y_2,z_2}(1\le x_1\le x_2\le a, 1\le y_1\le y_2\le b, 1\le z_1\le z_2\le c)$ 且 $st_{x,y,z}$ 的值为 $0$ 或 $1$ 的 $st$ 数组都有 $\sum_{i=1}^{x}\sum_{j=1}^{y}\sum_{k=1}^{z}st_{i,j,k}(a_{i,j,k}-b_{i,j,k})\ge0$，则能够达成目标，否则不能达成目标。

证明：我们可以把每一枚棋子看成一个点，若某一个棋子可以到达最终状态的某一个位置，就在这两个位置之间连一条边。则本题等价于判断这个二分图是否有完美匹配。然后可以发现前面的式子与霍尔定理等价，由此得证。

然后，我们注意到 $B,C\le6$。因此，我们可以暴力搜索出 $st$ 数组在 $y$ 和 $z$ 两维上所有可能的情况。根据插板法，最多只有 $C_{7+6-1}^{7-1}=924$ 种合法的情况。

对于第一维，我们考虑动态规划。直接枚举上一个状态是 $924^{924}$ 的，显然不可接受。考虑前缀和优化，规定每个 $st$ 数组的合法状态只能从他自己和把这个 $st$ 数组的某一个 $0$ 变成 $1$ 形成的合法状态转移过来，细节看代码。这样，时间复杂度就是 $O(AB\cdot C_{B+C}^{B})$ 的，可以通过本题。

代码：

```cpp
#include <iostream>
#include <map>
using namespace std;
#define int long long
int aa,bb,cc,a[10005][10][10],num[10],nxt[2005][10],tot,dp[10005][2005];//nxt 数组表示对于每个合法状态只将一个 0 变成 1 后形成的合法状态编号
bool ans;
struct node{
	int a[10];
	node(){
	}
	node(int a1,int a2,int a3,int a4,int a5,int a6){
		a[1]=a1;
		a[2]=a2;
		a[3]=a3;
		a[4]=a4;
		a[5]=a5;
		a[6]=a6;
	}
	/*bool operator<(const node rhs)const{
		if(a[1]!=rhs.a[1]){
			return a[1]<rhs.a[1];
		}
		if(a[2]!=rhs.a[2]){
			return a[2]<rhs.a[2];
		}
		if(a[3]!=rhs.a[3]){
			return a[3]<rhs.a[3];
		}
		if(a[4]!=rhs.a[4]){
			return a[4]<rhs.a[4];
		}
		if(a[5]!=rhs.a[5]){
			return a[5]<rhs.a[5];
		}
		return a[6]<rhs.a[6];
	}*/
}st[2005];

int ma[1000005];
// map<node,int> ma;
//一开始用的 map 被卡了
int to(node x){
	return ((((((((((x.a[1]<<3)|x.a[2])<<3)|x.a[3])<<3)|x.a[4])<<3)|x.a[5])<<3)|x.a[6]);
}

void dfs(int x){//暴搜出所有合法状态及 nxt
	if(x>bb){
		st[++tot]=node(num[1],num[2],num[3],num[4],num[5],num[6]);
		ma[to(st[tot])]=tot;
		for(int i=1;i<=bb;i++){
			if(num[i]!=num[i-1]){
				num[i]++;
				nxt[tot][i]=ma[to(node(num[1],num[2],num[3],num[4],num[5],num[6]))];
				num[i]--;
			}
			else{
				nxt[tot][i]=0;
			}
		}
		return;
	}
	for(int i=num[x-1];~i;i--){
		num[x]=i;
		dfs(x+1);
	}
	return;
}
void dfs2(int x){
	if(x>bb){
		ma[to(st[tot])]=0;
		return;
	}
	for(int i=num[x-1];~i;i--){
		num[x]=i;
		dfs(x+1);
	}
	return;
}
int read(void){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x*=10;
        x+=ch-'0';
        ch=getchar();
    }
    return x;
}
signed main(){
    int t;
    t=read();
    while(t--){
    	tot=0;
        ans=true;
        aa=read();
        bb=read();
        cc=read();
        num[0]=cc;
        num[1]=0;
        num[2]=0;
        num[3]=0;
        num[4]=0;
        num[5]=0;
        num[6]=0;
        dfs(1);
        for(int i=1;i<=aa;i++){
            for(int j=1;j<=bb;j++){
                for(int k=1;k<=cc;k++){
                    a[i][j][k]=read();
                }
            }
        }
        for(int i=1;i<=aa;i++){
            for(int j=1;j<=bb;j++){
                for(int k=1;k<=cc;k++){
                    a[i][j][k]-=read();
                }
            }
        }
        for(int i=1;i<=aa;i++){
        	for(int j=1;j<=tot;j++){
        		dp[i][j]=dp[i-1][j];//从自己转移
			}
			for(int j=1;j<=tot;j++){
        		for(int k=1;k<=bb;k++){
        			if(nxt[j][k]){
        				dp[i][j]=min(dp[i][j],dp[i][nxt[j][k]]);//从将一个 0 变成 1 后形成的合法状态转移
					}
				}
			}
			for(int j=1;j<=tot;j++){
				for(int k=1;k<=bb;k++){
					for(int l=1;l<=st[j].a[k];l++){
						dp[i][j]+=a[i][k][l];//加上这种状态本身的答案
					}
				}
				if(dp[i][j]<0){
					ans=false;
				}
			}
        }
        if(ans){
            putchar('T');
            putchar('A');
            putchar('K');
            putchar('\n');
        }
        else{
            putchar('N');
            putchar('I');
            putchar('E');
            putchar('\n');
        }
        dfs2(1);
    }
    return 0;
}
```

---

## 作者：Felix72 (赞：0)

我们看到这道题的第一思路多半是网络流判断能否流满，但是复杂度太大了，因此考虑模拟网络流。从最小割的角度考虑，我们对于每个平面，枚举它可能的点集作为和汇点相连的点（剩下的和源点相连），并作为 DP 状态即可。因为本题是带方向的网格图，所以每一行的点数量递减且都集中在一侧，相当于一个递减数列，情况不大于 $1000$ 种。搜索出来即可。

接下来设 $f_{i, j}$ 表示考虑到剖面 $i$，当前点集状态为 $j$ 是的最小割代价。设 $m$ 为第二维状态数，朴素转移是 $O(n m^2)$ 的，但是可以用分步转移优化，一次仅减少一个点，这样只用枚举减少哪一行，总复杂度为 $O(nmh)$。可以用 unordered_map 建立映射关系。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;

const int N = 20010;
int T, n, h, w;

long long a[N][6][6], b[N][6][6], global_a[N], global_b[N], g_a[N][1010], g_b[N][1010], f[N][1010];
unordered_map < int, int > mp;
array < int, 6 > state[N], base; int cnt;
inline int Hash(array < int, 6 > arr)
{
	int res = 0;
	for(int i = 0; i < 6; ++i) res = res * 10 + arr[i];
	return res;
}
inline void search(int p, int lim)
{
	if(p == h)
	{
//		cerr << "-> "; for(int i = 0; i < h; ++i) cerr << base[i] << " "; cerr << '\n';
		state[++cnt] = base, mp[Hash(base)] = cnt; return ;
	}
	for(int i = 0; i <= lim; ++i) base[p] = i, search(p + 1, i), base[p] = 0;
}

inline void sol()
{
	cin >> n >> h >> w; cnt = 0, mp.clear();
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < h; ++j)
			for(int k = 0; k < w; ++k)
				cin >> a[i][j][k], global_a[i] += a[i][j][k];
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < h; ++j)
			for(int k = 0; k < w; ++k)
				cin >> b[i][j][k], global_b[i] += b[i][j][k];
	search(0, w);
	for(int i = 1; i <= n; ++i)
	{
		global_a[i] = global_b[i] = 0;
		for(int j = 1; j <= cnt; ++j) g_a[i][j] = g_b[i][j] = 0;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= cnt; ++j)
			for(int x = 0; x < h; ++x)
				for(int y = 0; y < state[j][x]; ++y)
					g_a[i][j] += a[i][x][y], g_b[i][j] += b[i][x][y];
	for(int i = 1; i <= n + 1; ++i) memset(f[i], 0x3f, sizeof(f[i]));
	for(int i = 1; i <= cnt; ++i) f[1][i] = 0;
	for(int p = 1; p <= n; ++p)
	{
		for(int i = cnt; i >= 1; --i)
		{
			array < int, 6 > cur = state[i];
			for(int j = 0; j < h; ++j)
			{
				if(cur[j] - 1 >= 0 && (j == h - 1 || cur[j] > cur[j + 1]))
				{
					--cur[j]; int t_id = mp[Hash(cur)]; ++cur[j];
					if(f[p][i] < f[p][t_id]) f[p][t_id] = f[p][i];
				}
			}
//			cerr << p << " " << i << "  ";
//			for(int j = 0; j < h; ++j) cerr << cur[j] << " ";
//			cerr << " " << f[p][i] << '\n';
//			cerr << g_a[p][i] << " " << global_b[p] - g_b[p][i] << '\n';
			if(f[p][i] + g_a[p][i] + (global_b[p] - g_b[p][i]) < f[p + 1][i])
				f[p + 1][i] = f[p][i] + g_a[p][i] + (global_b[p] - g_b[p][i]);
		}
	}
	long long res = 9e18;
	for(int i = 1; i <= cnt; ++i) res = min(res, f[n + 1][i]);
	for(int i = 1; i <= n; ++i) res -= global_a[i];
	if(!res) cout << "TAK" << '\n';
	else cout << "NIE" << '\n';
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--) sol();
	return 0;
}
/*

*/
```

---

