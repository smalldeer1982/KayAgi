# Simplified Nonogram

## 题目描述

In this task you have to write a program dealing with nonograms on fields no larger than $ 5×20 $ .

Simplified nonogram is a task where you have to build such field (each cell is either white or black) that satisfies the given information about rows and columns. For each row and each column the number of contiguous black segments is specified.

For example if size of the field is $ n=3,m=5 $ , аnd numbers of contiguous black segments in rows are: $ [2,3,2] $ and in columns are: $ [1,0,1,2,1] $ then the solution may look like:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF534F/6475e8c66c897f247015722a0394e139a91bb231.png)It is guaranteed that on each test in the testset there exists at least one solution.

## 样例 #1

### 输入

```
3 5
2 3 2
1 0 1 2 1
```

### 输出

```
*.**.
*.*.*
*..**```

## 样例 #2

### 输入

```
3 3
2 1 2
2 1 2
```

### 输出

```
*.*
.*.
*.*
```

## 样例 #3

### 输入

```
3 3
1 0 1
2 2 2
```

### 输出

```
***
...
***
```

# 题解

## 作者：wishapig (赞：11)

### 题目大意

给出序列 $a[1\cdots n]$，$b[1\cdots m]$，构造一个 $n\times m$ 的 $01$ 矩阵，满足：

- 对每个 $1\le i\le n$，第 $i$ 行的极长连续 $1$ 段数量为 $a[i]$。
- 对每个 $1\le j\le m$，第 $j$ 列的极长连续 $1$ 段数量为 $b[i]$。

输出时对 $0$ 输出 `.`，对 $1$ 输出 `*`。

$1\le n\le 5$，$1\le m\le 20$，保证有解。

---

注意到这个 $n$ 比较小，因此可以状压 $n$ 的这一维，扫描 $m$ 的这一维。

先给出每行每列连通块的求法，这里采取 “当且仅当第 $i-1$ 位为 $0$，第 $i$ 位为 $1$ 的时候贡献 $1$ 的统计方式”。由这个统计方式可以发现，对一个长为 $l$ 的序列，其 $1$ 连通块的个数最多为 $\lceil l/2\rceil$，由于题目保证了有解，故有 $a_i\le 10$，$b_i\le 3$。

一个朴素的 dp 想法是令 $dp[i][s][bitmask]$ 分别表示前 $i​$ 列，每一行目前的连通块个数，前一列的 $0/1$ 状态，是否可以达到，转移就枚举下一列的 $0/1$ 状态，更新一下每一行目前的连通块个数，还原方案就记一下前驱状态。但这样做 dp 的状态数是 $20\times 11^5\times 2^5$ 的，转移还要 $2^5$，效率太低（考虑到每一列的连通块个数还有限制，这里不是 $2^5$ 而是 $2^4​$，不过也还是太大了）。

然后考虑 meet in the middle，把 $m$ 列分为前 $1\cdots \lfloor m/2\rfloor$ 列和后 $\lfloor m/2\rfloor+1\cdots m$ 列，两边分别跑上面的 dp（注意此时左侧有贡献的位置为 $0\sim 1,1\sim 2,\cdots ,\lfloor m/2\rfloor-1\sim \lfloor m/2\rfloor$，右侧有贡献的位置为 $\lfloor m/2\rfloor+1\sim \lfloor m/2\rfloor+2,\cdots ,m-1\sim m$，中间 $\lfloor m/2\rfloor\sim \lfloor m/2\rfloor+1$ 在后面合并左右两侧时进行计算），注意到这时一边的状态数降低到 $10\times 6^5\times 2^5$，转移还是 $2^5$，这样就可以了。

合并的时候，枚举左侧的每行连通块个数，第 $\lfloor m/2\rfloor$ 列的 $0/1$ 状态，第 $\lfloor m/2\rfloor+1$ 列的 $0/1$ 状态，可以算出右侧每行的连通块个数，取出对应的 dp 状态就可以快速合并了。

代码略微难写

```cpp
int dpL[22][7780][32],dpR[22][7780][32],Add[32][32],ns[7780][32];
pair<int,int> pre[22][7780][32],suf[22][7780][32];
int n,m,LIM,B,a[22],b[22],ans[22][22];
vector<int> rec[22];
int P[6]={1,6,36,216,1296,7776};
int main(){
	scanf("%d%d",&n,&m); LIM=P[n],B=m/2;
	for (int i=1; i<=n; i++) scanf("%d",&a[i]);
	for (int i=1; i<=m; i++) scanf("%d",&b[i]);
	for (int i=0; i<(1<<n); i++){
		for (int j=0; j<(1<<n); j++) for (int k=0; k<n; k++)
			if (!((i>>k)&1) && ((j>>k)&1)) Add[i][j]|=1<<k;
		for (int j=0; j<LIM; j++)
			for (int k=0,t=j; k<n; k++,t/=6) ns[j][i]+=(t%6+((i>>k)&1))*P[k];
		int c=0;
		for (int j=1; j<=n; j++)
			if (((i>>(j-1))&1) && !((i>>j)&1)) c++;
		rec[c].push_back(i);
	}
	dpL[0][0][0]=1;
	for (int x:rec[b[m]]) dpR[m][0][x]=1;
	for (int i=0; i<B; i++) for (int j=0; j<LIM; j++) for (int k:rec[b[i]]){
		if (!dpL[i][j][k]) continue;
		for (int t:rec[b[i+1]]){
			dpL[i+1][ns[j][Add[k][t]]][t]=1;
			pre[i+1][ns[j][Add[k][t]]][t]={j,k};
		}
	}
	for (int i=m; i>B+1; i--) for (int j=0; j<LIM; j++) for (int k:rec[b[i]]){
		if (!dpR[i][j][k]) continue;
		for (int t:rec[b[i-1]]){
			dpR[i-1][ns[j][Add[t][k]]][t]=1;
			suf[i-1][ns[j][Add[t][k]]][t]={j,k};
		}
	}
	for (int i=0; i<LIM; i++) for (int j=0; j<(1<<n); j++){
		if (!dpL[B][i][j]) continue;
		for (int k=0; k<(1<<n); k++){
			int sta=0;
			for (int t=0,cur=i; t<n; t++,cur/=6){
				int v=a[t+1]-cur%6-((Add[j][k]>>t)&1);
				if (v<0 || v>5){ sta=-1; break; }
				else sta+=v*P[t];
			}
			if (sta==-1 || !dpR[B+1][sta][k]) continue;
			for (int t=B,cj=i,ck=j; t>=1; t--){
				for (int l=0; l<n; l++) ans[l+1][t]=(ck>>l)&1;
				auto d=pre[t][cj][ck]; cj=d.first,ck=d.second;
			}
			for (int t=B+1,cj=sta,ck=k; t<=m; t++){
				for (int l=0; l<n; l++) ans[l+1][t]=(ck>>l)&1;
				auto d=suf[t][cj][ck]; cj=d.first,ck=d.second;
			}
			for (int t=1; t<=n; t++,puts(""))
				for (int l=1; l<=m; l++) putchar(ans[t][l]?'*':'.');
			return 0;
		}
	}
}
```



---

## 作者：gcx12012 (赞：4)

### 前言
一篇好想的卡空间的记搜题解。
### Solution
首先考虑数据范围很小，于是我们可以写出一个搜索。

设 $f_{now,lst,p_i}$ 为当前考虑到了第 $now$ 列，上一列填的状态为 $lst$，第 $i$ 行当前有 $p_i$ 个连续段。

然后有一个结论：一个长度为 $n$ 的 $01$ 串关于 $0$ 和 $1$ 最多只会有 $\lceil \frac{n}{2} \rceil$ 个连续段，证明显然。

于是得出每一个 $p_i$ 的上界为 $\lceil \frac{m}{2} \rceil$。

每次枚举一个列的状态然后判断是否合法即可。

然后用 bool 数组记录一下这个状态是否达到过，如果之前已经达到过就返回，这样可以避免搜索到重复的状态，大大的提升了时间上的效率。

上述做法的时间复杂度上界为 $O(\lceil \frac{m}{2} \rceil^n \times 4^nm)$，空间复杂度为 $O(\lceil \frac{m}{2} \rceil^n \times 2^nm)$，但是我们用的 bool 数组，因此不会爆空间。

如果害怕 TLE 多写点剪枝即可。
### Code

```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 300010
#define For(i,a,b) for(ll i=a;i<=b;i++)
#define Rof(i,a,b) for(ll i=a;i>=b;i--)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
bool st;
int a[N],b[N],p[32];
bool f[21][32][11][11][11][11][11];
int n,m;
bool ed;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int ans[21];
int is=0;
void dfs(int now,int lst,int p1,int p2,int p3,int p4,int p5){
	if(p1>a[1] || p2>a[2] || p3>a[3] || p4>a[4] || p5>a[5] || m-now+1<max(max(a[1]-p1,max(a[2]-p2,a[3]-p3)),max(a[4]-p4,a[5]-p5))) return;
	if(now==m+1){
		For(i,1,n){
			For(j,1,m){
				if((ans[j]>>(i-1))&1) cout<<"*";
				else cout<<".";
			}
			cout<<endl;
		}
		exit(0);
	}
	if(f[now][lst][p1][p2][p3][p4][p5]) return;
	f[now][lst][p1][p2][p3][p4][p5]=1;
	For(i,0,(1<<n)-1){
		int pp[5]={p1,p2,p3,p4,p5};
		if(b[now]!=p[i]) continue;
		For(j,0,n-1){
			if(!((lst>>j)&1) && ((i>>j)&1)) pp[j]++;
		}
		ans[now]=i;
		dfs(now+1,i,pp[0],pp[1],pp[2],pp[3],pp[4]);
	}
}

int main()
{
	//fprintf(stderr,"%d",(&ed-&st)/1024/1024);
    n=read(),m=read();
    For(i,1,n) a[i]=read();
    For(i,1,m) b[i]=read();
    For(i,0,31){
    	int lst=0;
    	For(j,0,4){
    		int now=(i>>j)&1;
    		if(!lst && now) p[i]++;
    		lst=now;
		}
	}
	dfs(1,0,0,0,0,0,0);
	return 0;
}
/*

*/
```

---

## 作者：wrkwrkwrk (赞：1)

当看到数据范围 $1 \leq n \leq 5$，$1 \leq m \leq 20$，考虑搜索。

显然暴力搜索是会 TLE 的，于是我们需要剪枝。

考虑从上而下，每行从左到右来遍历情况。

考虑对每行可能的 $2^m$ 种情况进行状压并按照连通块的个数进行分类，这样每一行可以减少一部分计算量，因为每一行不需要判断这种情况是否符合这一行所对应的连通块数量。

显然还是不够，考虑将这 $2^m$ 种情况放到对应的 01trie，对于每一次向右遍历判断这一次放置是否超过这一列的限制。

由于部分数据在搜索中使用 $1$ 更容易找到答案，而部分数据在搜索中使用 $0$ 更容易找到，于是考虑随机化。由于题目保证有解，故省下了很多时间。

以下是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],b[30]; //如题意
bool ans[6][30];//保存答案
int nowc[6][30];//这一行现在纵向连通块个数
int w[30];//遍历每一种情况的临时数组
int n,m;//如题意 
int trie[30][1000006][2];//各个行连通块所要的 01trie
int f[30];//各个行连通块所要的 01trie 末编号
void insert(int o,int p){//01trie 插入
	//o：01trie 编号
	//p：要插入的值 
	int now=0;
	for(int i=1;i<=m;i++){
		int r=(p>>i)&1;
		if(trie[o][now][r]==0)trie[o][now][r]=++f[o];
		now=trie[o][now][r];
	}
}
void dfs(int dep,int now,int j,int at){
	//dep：当前搜索的行号
	//now：当前搜索的列号
	//j：当前这一行的值
	//at：当前在这个 01trie 的编号
	//可以用 trie[a[dep]] 来找到这一行对应的 trie
	if(dep==n+1){//搜索到结束 
		for(int j=1;j<=m;j++){//判断是否合法
			if(nowc[n][j]!=b[j])return;
		}
		for(int i=1;i<=n;i++){//输出方案
			for(int j=1;j<=m;j++){
				if(ans[i][j])cout<<'*';
				else cout<<'.';
			}
			cout<<endl;
		}
		exit(0);//结束
	}
	if(now==m+1){//这一行搜索到结束
		int y=j;
		for(int j=1;j<=m;j++)ans[dep][j]=(y>>j)&1;
		for(int j=1;j<=m;j++){//统计连通块数量 
			if(ans[dep][j]&&!ans[dep-1][j]){
				nowc[dep][j]=nowc[dep-1][j]+1;
			}else{
				nowc[dep][j]=nowc[dep-1][j];
			}
		}
		bool t=true; 
		for(int j=1;j<=m;j++){
			//(n-dep+1-ans[dep][j])/2：理论最多还能加上的连通块的个数。
			//如果不满足要求，那么没有必要搜索了。
			if(nowc[dep][j]>b[j]||nowc[dep][j]+(n-dep+1-ans[dep][j])/2<b[j]){
				t=false;
				break;
			}
		}
		if(t)dfs(dep+1,1,0,0);
		return;
	}
	bool t=rand()%2;//随机分支 
	if(t)if(trie[a[dep]][at][0])dfs(dep,now+1,j,trie[a[dep]][at][0]);
	if(ans[dep-1][now]||nowc[dep-1][now]!=b[now]){ 
		//即：如果上一行是空的，或者这一列的连通块数量没有达到极限，
		//且下一步可行，那么向下搜索。
		if(trie[a[dep]][at][1])dfs(dep,now+1,j+(1<<now),trie[a[dep]][at][1]);
	}
	if(!t)if(trie[a[dep]][at][0])dfs(dep,now+1,j,trie[a[dep]][at][0]);
}
int main(){
	srand(time(0));//随机化 
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=0;i<1<<m;i++){//遍历每一种情况 
		int y=i<<1;//将 0-(m-1) 区间转换成 1-m 区间 
		int q=0;
		for(int j=1;j<=m;j++)w[j]=(y>>j)&1; 
		for(int j=1;j<=m;j++)if(w[j]&&!b[j])continue;//如果有 0 的位置，那么就这一列什么都不能放。
		for(int j=1;j<=m;j++)if(w[j]&&!w[j-1])q++;//统计这一行的连通块数量 
		insert(q,y);//插入到对应的 trie 中
	}
	dfs(1,1,0,0); //开始搜索
	//cout<<-1; 
	return 0;
}

```
[AC 记录](https://codeforces.com/contest/534/submission/213456169)

---

## 作者：StayAlone (赞：1)

为什么要 meet-in-the-middle？

考虑朴素的 dp。$f_{i, s1, s2}$ 表示，考虑前 $i$ 列，目前的最长连续段状态为 $s1$，第 $i$ 列选或不选状态为 $s2$，此时是否可行。由于最多只有 $\frac{m}{2}=10$ 个连通块，因此 $s1$ 是一个十一进制数；同时 $s2$ 是一个二进制数。转移为 $2^n$。

信仰写一发。惊奇发现如果记录 dp 时转移的上一个状态，空间炸得很严重。那么套路的处理就是枚举上一个状态是什么，判断能否转移到当前状态。常数变大，时间复杂度不变。

信仰交一发。惊奇发现 TLE。把数据扒下来竟然跑了 4s。于是把 f 数组改成 bitset，竟然只跑了 400ms，空间也变得小了。于是过了。

[AC record](https://www.luogu.com.cn/record/157386398)

```cpp
int n, m, a[10], b[25], pw11[10]; char ch[10][25];
bitset <MAXN> f[25][40];
vector <int> T[25];

il bool check(int x, int s) {
	int lst = -1, cnt = 0;
	rep1(i, 0, n - 1) if (~s >> i & 1) {
		if (i - lst - 1 > 0) ++cnt;
		lst = i;
	} return cnt + (lst < n - 1) == b[x];
}

int main() {
	pw11[0] = 1;
	rep1(i, 1, 6) pw11[i] = pw11[i - 1] * 11;
	read(n, m); rer(i, 1, n, a); rer(i, 1, m, b);
	f[0][0][0] = 1;
	int p = 0;
	rep1(i, 1, n) p += a[i] * pw11[i - 1];
	rep1(i, 1, m) {
		rep1(t, 0, (1 << n) - 1) if (check(i, t)) T[i].eb(t);
	}
	rep1(i, 0, m) rep1(s, 0, (1 << n) - 1) rep1(s2, 0, pw11[n] - 1) if (f[i][s][s2]) {
		if (i == m && s2 == p) {
			rep2(i, m, 1) {
				rep1(j, 0, n - 1) ch[j + 1][i] = (s >> j & 1) ? '*' : '.';
				bool fg = 0;
				rep1(ss, 0, (1 << n) - 1) {
					if (fg) break;
					rep1(ss2, 0, pw11[n] - 1) if (f[i - 1][ss][ss2]) {
						int nw = ss2;
						rep1(j, 0, n - 1) nw += pw11[j] * ((s >> j & 1) && (~ss >> j & 1));
						if (nw == p) {
							s = ss; p = ss2; fg = 1;
							break;
						}
					}
				}
			}
			rep1(i, 1, n) puts(ch[i] + 1);
			return 0;
		}
		for (auto t : T[i + 1]) {
			int nw = s2;
			rep1(j, 0, n - 1) nw += pw11[j] * ((t >> j & 1) && (~s >> j & 1));
			f[i + 1][t][nw] = 1;
		}
	}
	rout;
}
```

---

## 作者：Shunpower (赞：0)

为什么要 meet-in-the-middle？为什么要 bitset？为什么要卡常？

思维水平不够，暴力水平来凑。

------------------

考虑延续 @[StayAlone](https://www.luogu.com.cn/user/409236) 大帝的思路。$f_{i,s1,s2}$ 表示完成前 $i$ 列，每一行上连续段数量的状态为 $s1$，第 $i$ 列的状态为 $s2$。显然每一行上连续段的数量不会超过 $\frac{m}{2}=10$，所以 $s1$ 可以记成一个 $5$ 位 $11$ 进制数，$s2$ 可以记成一个 $5$ 位 $2$ 进制数。

通过精细计算，$s1$ 不会超过 $161050$，空间非常充裕。

接下来考虑转移。枚举 $i,s1,s2$ 后枚举下一列的状态 $s2'$，之后可以轻易 $\mathcal O(n)$ 得到下一列的 $s1'$ 进行转移 $f_{i,s1',s2'}\gets f_{i,s1,s2}$。

最后的构造就是把 $a$ 数组压缩成 $11$ 进制得到 $sa$ 之后，从 $f_{m,sa,s}$ 且 $s$ 满足有 $b_m$ 个极长连续 $1$ 段的限制的状态往前推就行。注意每一列上的状态都要符合对应 $b$ 的限制。

计算可以发现，直接朴素转移需要 $1.6\times 10^{10}$ 的运算次数，会 TLE on #16，但是我们可以大大地剪枝。

首先我们把转移改成 push 的形式，然后不再转移 $f_{i,s1,s2}=0$ 的状态。在枚举 $s1$ 将上界收缩到 $sa$，且一边枚举一边判定 $s1$ 拆分出的每一项是否都仍然小于等于 $a$ 数组中的对应项，否则不转移。

这样做可以减少很多无用状态的枚举和转移。

其次，在增添一列时我们直接要求 $s2'$ 需要满足下一列上 $b$ 的限制，这容易进行 $\mathcal O(n)$ check。之后我们可以认为，所有 $f_{i,s1,s2}=1$ 都满足一定可以往回推出一个符合 $b$ 数组前 $i$ 项，且此时每一行上连续段数的状态为 $a$ 的构造。

这样做之后往回构造时我们就不再需要 check，并且可以减少推 $s1'$ 的次数。

最后，在推 $s1'$ 的时候也判定 $s1'$ 拆分出的每一项是否都仍然小于等于 $a$ 数组中的对应项，否则不转移。这和第一条是同理的。

上面这一套剪枝操作搞完之后，随便实现 dp 部分极限数据就可以跑进两秒且绰绰有余。构造部分容易做到不去枚举 $11$ 进制数而只枚举状态（已知 $sa$ 和最后一列的状态后，可以通过枚举上一列状态逆推回去，以此类推），复杂度本来就不高。于是可以获得通过。

精细实现和降低不必要常数后，目前可以做到只比一般实现的 meet-in-the-middle 慢 $50$ 毫秒，其实还行。

--------

核心代码：

```cpp
bool dp[21][161051][33];
int a[10],b[25];
int n,m;
int ans[25];
bool print[6][25];
int cnt[5];
int get1(int x){
    int c=0;
    fr1(k,0,n-1){
        if(((x>>k)&1)==1&&((x>>k+1)&1)==0) c++;
    }
    return c;
}
void con(int i,int s11,int si){
    if(i==0) return;
    ans[i]=si;
    int t=s11,tot=0;
    fr1(q,0,4) cnt[q]=0;
    while(t){
        cnt[tot]=t%11;
        t/=11;
        tot++;
    }
    fr1(k,0,(1<<n)-1){
        int newj=0;
        bool flg=0;
        fr2(q,n-1,0){
            int x=(cnt[q]-(((si>>q)&1)==1&&((k>>q)&1)==0));
            if(x<0){
                flg=1;
                break;
            }
            newj=newj*11+x;
        }
        if(flg) continue;
        if(dp[i-1][newj][k]){
            con(i-1,newj,k);
            break;
        }
    }
}
int main(){
#ifdef Rain
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n>>m;
    fr1(i,0,n-1) cin>>a[i];
    fr1(i,1,m) cin>>b[i];
    dp[0][0][0]=1;
    int to11=0;
    fr2(i,n-1,0) to11=to11*11+a[i];
    fr1(i,0,m-1){
        fr1(j,0,to11){
            int tot=0,t=j;
            fr1(q,0,4) cnt[q]=0;
            while(t){
                cnt[tot]=t%11;
                if(cnt[tot]>a[tot]){
                    tot=-1;
                    break;
                }
                t/=11;
                tot++;
            }
            if(!(~tot)) continue;
            fr1(k,0,(1<<n)-1){
                if(!dp[i][j][k]) continue;
                fr1(l,0,(1<<n)-1){
                    if(get1(l)!=b[i+1]) continue;
                    int newj=0;
                    bool flg=0;
                    fr2(q,n-1,0){
                        int x=(cnt[q]+(((l>>q)&1)==1&&((k>>q)&1)==0));
                        if(x>a[q]){
                            flg=1;
                            break;
                        }
                        newj=newj*11+x;
                    }
                    if(flg) continue; 
                    dp[i+1][newj][l]|=dp[i][j][k];
                    // if(dp[i+1][newj][l]) break;
                }
            }
        }
    }
    fr1(i,0,(1<<n)-1){
        if(dp[m][to11][i]){
            con(m,to11,i);
            break;
        }
    }
    fr1(i,1,m){
        fr1(j,0,n-1) print[j+1][i]=(ans[i]>>j)&1;
    }
    fr1(i,1,n){
        fr1(j,1,m) cout<<(print[i][j]?'*':'.');
        cout<<'\n';
    }
    // cerr<<clock()<<'\n';
    ET;
}
```

---

