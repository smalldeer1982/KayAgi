# [PA 2022] Łamigłówka

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 4 [Łamigłówka](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/lam/)**

Byteasar 在玩拼图。它是一个由单元格组成的 $n\times m$ 大小的矩形。每个单元格可能是空的，也可能包含一个黑色或白色的方块。

在每次操作中，这个玩具可以向平行于矩形边的四个方向之一倾斜。然后所有的方块会朝那个方向滑动到最远可以所处的位置，而不超出矩形范围或重叠。

Byteasar 倾斜了多次，请给出倾斜最后一次后整个拼图的状态。

## 说明/提示

对于 $100\%$ 的数据，满足：

$1\le n,m\le 500, 1\le k\le 5 \times 10 ^ 5$。 

## 样例 #1

### 输入

```
4 5
.....
.B.C.
..C..
...B.
3
GLP
```

### 输出

```
..BCC
....B
.....
.....
```

# 题解

## 作者：lsj2009 (赞：9)

## Description

有一个大小 $n\times m$ 的矩阵（有些地方有东西，有些地方为空），有 $q$ 次操作，每次操作会改变整个矩阵的 **重力方向**（仅限于上下左右）。

即矩形上的所有东西都朝着重力方向移动直到遇到边界或者遇到其他物品（想一下 2048 小游戏？）

求 $q$ 操作之后的矩阵长什么样子。

$1\le n,m\le 500$，$1\le k\le 5\times 10^5$。

1.00s，512MB。

## Solution

我们首先消去连续的同一方向类型（上下为一类型，左右为一类型）的操作，再删去间隔一位的相同操作，会发现最终只剩下开头（要把所有东西搞到角落）、结尾的 $\mathcal{O}(1)$ 次操作和 $\mathcal{O}(k)$ 次「转圈」。

其中 $\mathcal{O}(1)$ 次操作可以暴力做，考虑如何快速做「转圈」。

注意到「转圈」有不同种类（如右下左上和下右上左是不同的），但总归只有 $\mathcal{O}(1)$ 种，并且「转圈」具有 **交换律**，也就是我先转那个圈还是先转这个圈是无所谓的（想想证明？这很重要。），所以我们把相同种类的转圈归到一起做就好了。

Observation：**进行一轮「转圈」之后，物品的轮廓是不变的。**

手摸一下还是比较显然的。这里其实也就解释了「转圈」具有交换律的原因。

则由于轮廓不变，**所以每次一个位置 $(x,y)$ 在转一圈后去到的位置 $P_{(x,y)}$ 是一致的**

事实上 $P$ 是一个置换，则转 $k$ 次后 $(x,y)$ 就会去到 $P^k_{(x,y)}$，**问题转换为求置换的 $k$ 次方**，可以直接把置换环拉出来然后拿出每个点往后 $k$ 个点的位置即可；或者注意到置换具有结合律，跑一个快速幂即可。

两种实现，前者复杂度为 $\mathcal{O}(nm+k)$，后者为 $\mathcal{O}(k+nm\log{k})$。

## Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(3,"Ofast","inline")
//#define int long long
#define i128 __int128
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define ld double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
#define pcnt(x) __builtin_popcount(x)
#define lg(x) (31-__builtin_clz(x))
using namespace std;
void file_IO() {
//	system("fc .out .ans");
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
bool M1;
const int N=5e2+5,M=5e5+5;
char s[N][N],t[M],ans[M];
int a[N][N],d[N][N],p[M],q[M],tot,n,m,k;
bool used[M];
int c[M],ttot;
void dfs(int u) {
	if(used[u])
		return;
	used[u]=true;
	c[++ttot]=u;
	dfs(p[u]);
}
int new_node() {
	return ++tot;
}
template<typename T>
void upd(T s[N][N],T x,char op) {
	T b[N];
	if(op=='G') {
		rep(j,1,m) {
			int len=0;
			rep(i,1,n) {
				if(s[i][j]!=x)
					b[++len]=s[i][j];
			}
			rep(i,1,len)
				s[i][j]=b[i];
			rep(i,len+1,n)
				s[i][j]=x;
		}
	} else if(op=='D') {
		rep(j,1,m) {
			int len=0;
			per(i,n,1) {
				if(s[i][j]!=x)
					b[++len]=s[i][j];
			}
			rep(i,1,len)
				s[n-i+1][j]=b[i];
			rep(i,len+1,n)
				s[n-i+1][j]=x;
		}
	} else if(op=='L') {
		rep(i,1,n) {
			int len=0;
			rep(j,1,m) {
				if(s[i][j]!=x)
					b[++len]=s[i][j];
			}
			rep(j,1,len)
				s[i][j]=b[j];
			rep(j,len+1,m)
				s[i][j]=x;
		}
	} else {
		rep(i,1,n) {
			int len=0;
			per(j,m,1) {
				if(s[i][j]!=x)
					b[++len]=s[i][j];
			}
			rep(j,1,len)
				s[i][m-j+1]=b[j];
			rep(j,len+1,m)
				s[i][m-j+1]=x;
		}
	}
}
int get1(char op) {
	return op=='G'||op=='D';
}
int get2(char op) {
	return op=='G'||op=='L';
}
map<stack<char>,int> cnt;
void solve() {
	scanf("%d%d",&n,&m);
	rep(i,1,n)
		scanf("%s",s[i]+1);
	scanf("%d",&k);
	scanf("%s",t+1);
	int S=0,pos=k,op1=-1,op2=-1;
	rep(i,1,k) {
		S|=1<<get1(t[i]);
		if(S==3) {
			pos=i;
			break;
		}
	}
	int x=0,y=0;
	per(i,pos,1) {
		if(get1(t[i])) {
			op1=get2(t[i]);
			x=i;
			break;
		}
	}
	per(i,pos,1) {
		if(!get1(t[i])) {
			op2=get2(t[i]);
			y=i;
			break;
		}
	}
	if(x>y)
		swap(x,y);
	if(x)
		upd(s,'.',t[x]);
	if(y)
		upd(s,'.',t[y]);
	if(pos==k) {
		rep(i,1,n)
			printf("%s\n",s[i]+1);
		return;
	}
	stack<char> st;
	rep(i,pos+1,k) {
		if(get1(t[i])) {
			if((t[i]=='G')==op1)
				continue;
			if(!st.empty()&&get1(st.top()))
				st.pop();
			else
				st.push(t[i]);
			op1^=1;
		} else {
			if((t[i]=='L')==op2)
				continue;
			if(!st.empty()&&!get1(st.top()))
				st.pop();
			else
				st.push(t[i]);
			op2^=1;
		}
		if((int)st.size()==4) {
			++cnt[st];
			while(!st.empty())
				st.pop();
		}
	}
	for(auto x:cnt) {
		tot=0;
		rep(i,1,n) {
			rep(j,1,m) {
				if(s[i][j]!='.') {
					int u=new_node();
					d[i][j]=a[i][j]=u;
					ans[u]=s[i][j];
				} else
					a[i][j]=d[i][j]=0;
			}
		}
		stack<char> st=x.first;
		int tt[5],len=0;
		while(!st.empty())
			tt[++len]=st.top(),st.pop();
		reverse(tt+1,tt+len+1);
		rep(i,1,len)
			upd(a,0,tt[i]);
		rep(i,1,n) {
			rep(j,1,m) {
				if(d[i][j])
					p[d[i][j]]=a[i][j];
			}
		}
		rep(i,1,tot)
			used[i]=false;
		int cc=x.second;
		rep(i,1,tot) {
			if(!used[i]) {
				ttot=0;
				dfs(i);
				rep(j,1,ttot)
					q[c[j]]=c[(j+cc-1)%ttot+1];
			}
		}
		rep(i,1,n) {
			rep(j,1,m) {
				if(d[i][j])
					s[i][j]=ans[q[d[i][j]]];
				else
					s[i][j]='.';
			}
		}		
	}
	int tt[5],len=0;
	while(!st.empty())
		tt[++len]=st.top(),st.pop();
	reverse(tt+1,tt+len+1);
	rep(i,1,len)
		upd(s,'.',tt[i]);
	rep(i,1,n)
		printf("%s\n",s[i]+1);
}
/*
3 5
C.CB.
.C..C
C.C..
8
GLDPGLDP


*/
bool M2;
signed main() {
	//file_IO();
	int testcase=1;
	//scanf("%d",&testcase);
	while(testcase--)
		solve();
	fprintf(stderr,"used time = %ldms\n",1000*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"used memory = %lldMB\n",(&M2-&M1)/1024/1024);
	return 0;
}
```

---

## 作者：critnos (赞：8)

萌萌题。经过 2 次非平凡操作之后这堆东西就会靠在角落，然后可以发现每次操作要么是无效的，要么是撤销上一次操作，那实际上每步只有唯一的有效操作，结果就是这玩意一直在绕圈。一次绕圈不会改变这堆东西的形状只会改变其中的颜色排列顺序，于是每次绕圈就是乘上一个置换。时间复杂度线性或线性对数。

---

## 作者：qiuzx (赞：3)

注意到有一些操作是没用的，例如在向下操作之后立即向上操作，或者连续两次向下操作等等。我们可以发现主要有下面两类操作时没用的：

1. 连续两次操作向相反的方向（一次向左一次向右，或一次向上一次向下），此时只需要保留后者。
2. 在两次向同一个方向的操作之间没有向相反方向的操作（例如两次向左的操作之间全是上下操作），此时只需要保留前者。

对操作序列做上述修改可以用类似单调栈的方式进行，每次向后添加一个操作之后检查后缀是否出现了上面两种情况。注意到一个没有上面这两种冗余操作的操作序列必然形如某个连续四个不同方向的操作拼在一起的序列（可以为 `GLDP`、`GPDL`、`DLGP` 或 `DPGL` ）循环多次，所以检查是否合法只有最后的两个字符是有用的，可以直接判定并暴力修改。

下面我们可以先做 $O(1)$ 步操作将方块移到某个角落，并且使得剩余操作序列的长度是 $4$ 的倍数。这样操作序列是呈周期性的，我们只需考察一个周期的操作会对局面产生什么改变即可。发现四个方向依次转一圈之后一定会回到原位（即所有有方块的位置是一样的），但块与块之间的位置关系可能发生了改变。如果将所有方块依次编号，则一个周期相当于对它们进行了一次置换，显然每个周期发生的置换是一样的。所以预处理 $4$ 次操作发生的置换是什么，将置换环求出之后即可求得最终答案。复杂度 $O(nm)$。

[代码](https://loj.ac/s/2167798)

---

## 作者：gdf_yhm (赞：0)

[P9262](https://www.luogu.com.cn/problem/P9262)



### 思路

每次所有滑块滑向上左下右四个方向。

考虑操作的规律。相对的方向做多次只用保留最后一次。同一种操作两两之间如果没有反向的操作，则后面一次无用。用栈来删，发现最后去掉开头结尾 $O(1)$ 次操作后，四种操作以一个合法的顺序重复多次，形如多次转圈。

开头处理若干步后所有的滑块都在某个角落。此时转一圈只改变每个滑块的位置，不改变整体的形状，是一个置换。

做一轮就可以知道原来在一个位置的滑块会去到的新位置。求出置换后，要把他做 $k=\frac{num}{4}$ 次，可以快速幂。也可以找出置换环后 $cyc_i\to cyc_{(i+k)\bmod siz}$。复杂度 $O(nm)$。

### code

```cpp
int n,m,q,a[maxn];
char s[maxq];
int id[maxn],to[maxn],tmp[maxn],res[maxn];
int b[maxm][maxm];
int st[maxn],tp;
bool vis[maxn];
void trans(int op){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)b[i][j]=id[(i-1)*m+j];
    }
    if(op==0){
        for(int j=1;j<=m;j++){
            vector<int> id1,id2;
            for(int i=1;i<=n;i++){
                if(a[b[i][j]])id1.pb(b[i][j]);
                else id2.pb(b[i][j]);
            }
            for(int i=0;i<id1.size();i++)b[i+1][j]=id1[i];
            for(int i=0;i<id2.size();i++)b[i+1+id1.size()][j]=id2[i];
        }
    }
    if(op==1){
    }
    if(op==2){
    }
    if(op==3){
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)id[(i-1)*m+j]=b[i][j];
    }
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)a[(i-1)*m+j]=(s[j]=='.'?0:s[j]-'A');
    }
    for(int i=1;i<=n*m;i++)id[i]=i;
    q=read();scanf("%s",s+1);
    for(int i=1;i<=q;i++){
        if(s[i]=='G')st[++tp]=0;
        if(s[i]=='D')st[++tp]=1;
        if(s[i]=='L')st[++tp]=2;
        if(s[i]=='P')st[++tp]=3;
        if(tp>1&&(st[tp-1]==st[tp]||(st[tp-1]^1)==st[tp]))st[tp-1]=st[tp],tp--;
        if(tp>2&&st[tp]==st[tp-2])tp--;
    }
    q=tp;
    if(q<8){
        for(int i=1;i<=q;i++)trans(st[i]);
    }
    else{
        for(int i=1;i<=q%4+4;i++)trans(st[i]);
        int lst=(q-(q%4+4))/4;
        for(int i=1;i<=n*m;i++)tmp[i]=id[i];
        for(int i=(q%4)+5;i<=(q%4)+8;i++)trans(st[i]);
        for(int i=1;i<=n*m;i++)to[tmp[i]]=id[i];
        for(int i=1;i<=n*m;i++)if(!vis[i]){
            vector<int> cyc;
            int x=i;
            while(!vis[x])vis[x]=1,cyc.pb(x),x=to[x];
            for(int j=0;j<cyc.size();j++)res[cyc[j]]=cyc[(j+lst)%cyc.size()];
        }
        for(int i=1;i<=n*m;i++)id[i]=res[tmp[i]];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!a[id[(i-1)*m+j]])putchar('.');
            else putchar(char(a[id[(i-1)*m+j]]+'A'));
        }
        puts("");
    }
}
```

---

## 作者：ZHONGZIJIE0608 (赞：0)

大约这的确是一道好题。

你有一个玩具，是一个 $n \times m$ 大小的网格，里面有一些黑色和白色的滑块。滑块只能水平或者竖直滑动。

每次你可以选定一条边的方向并让所有滑块朝着那条边的方向滑动最远距离。（突然想到一个小玩具，就是你可以倾斜一个盒子来用重力让一个小球走迷宫，修改重力大概就是这个样子）

求 $K$ 次操作之后你的玩具内滑块的分布情况。

我们一步步分析这个题。

**考虑有没有没用的操作。**

不难发现是有的。

我们把向上和向下归为第一类，往左和往右归为第二类。

如果相邻的两个操作是同一类，只保留后一个操作。

**在此之后**，如果相邻的三个操作中，第一个和第三个相同，并且中间的第二个和另外两个不是一类，只保留前两个。

于是我们维护一个栈来保留有用的操作作为新的操作序列。

**考虑有用的操作序列有没有什么性质。**

不难发现，此时没有相邻两个同类的操作了，也没有两个相同的操作中间只加了一个操作。所以在有用的操作当中必定在 $O(1)$ 步后上下左右在连续的四个操作中分布，并且两类操作是交替分布的。我们称其为“转圈”。（比如“上左下右”）

自然，两类操作各有两种，并且交替分布的位置的奇偶性有两种，所以分布类型一共只有八种。

注意到不同种类的“转圈”的处理顺序和结果无关，所以只要对这八种转圈分开做就好。（之前认为只有一种循环，发现好像是这样，但是因为不明原因假掉，大概是其他地方，保险起见写了八种转圈）。

有一个性质，如果此时滑块都在角落里（大概是一个联通块状物），在转一整圈四个操作后其轮廓是不变的。

轮廓不变，滑块（有效点数）不变，所以这个“转圈”实质上就是一个置换操作。

那么大方向上就可以考虑如何实现了。

首先简化操作序列使其全部是有效操作。

首先跑前面的 $O(1)$ 步，只要两类操作都出现过，并且没做过的操作数量是 $4$ 的倍数就好。

考虑中间的环。（对于八种转圈统计次数分开操作，不过转圈类型不存在的就不用考虑了）此时所有滑块都已经在角落里了，转一圈就可以直接确定置换内容。

就和跑前面一样，只要记录坐标。

确定转一圈的置换后，转几圈就是容易的。设圈数是 $R$。

我们把数据范围内的每个点的 $2$ 的整数次方步求出来，对 $R$ 倍增就行了。

时间复杂度大概是 $O(k+nm\log k)$，但是前面那个 $k$ 应该是跑不满，反正最后跑得比较快……

将近 5KB 的代码连写带调花了半天，也太不牛了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string str,opt;
const int N=505;
typedef pair<int,int> pii;
pii MP[N][N];
vector<pii>VEC[N];
char mp[N][N],mt[N][N],Ans[N][N];
int n,m,k; 
pii nxt[N][N][18];
string ROT[9]={"HAPPY_BIRTHDAY_CHIFAN","GLDP","GPDL","DPGL","DLGP","LDPG","PDLG","PGLD","LGPD"};
unordered_map<string,int>hsh;
bool Clarify(char x){
	if(x=='G'||x=='D')return 0;
	return 1;
}
vector<char>vec[N];
int CNT[9];
void UP(){
	for(int i=1;i<=m;++i)vec[i].clear(),VEC[i].clear();
	for(int j=1;j<=m;++j){
		for(int i=1;i<=n;++i){
			if(mp[i][j]=='B')vec[j].push_back('B');
			if(mp[i][j]=='C')vec[j].push_back('C');
			if(MP[i][j]!=make_pair(0ll,0ll)){
				VEC[j].push_back(MP[i][j]);
			}
			mp[i][j]='.';MP[i][j]={0,0};
		}
	}
	for(int j=1;j<=m;++j){
		for(int i=0;i<(int)vec[j].size();++i){
			mp[i+1][j]=vec[j][i];
			MP[i+1][j]=VEC[j][i];
		}
	}
}
void DOWN(){
	for(int i=1;i<=m;++i)vec[i].clear(),VEC[i].clear();
	for(int j=1;j<=m;++j){
		for(int i=1;i<=n;++i){
			if(mp[i][j]=='B')vec[j].push_back('B');
			if(mp[i][j]=='C')vec[j].push_back('C');
			if(MP[i][j]!=make_pair(0ll,0ll)){
				VEC[j].push_back(MP[i][j]);
			}
			mp[i][j]='.';MP[i][j]={0,0};
		}
	}
	for(int j=1;j<=m;++j){
		int o=vec[j].size();
		for(int i=0;i<(int)vec[j].size();++i){
			mp[n-o+i+1][j]=vec[j][i];
			MP[n-o+i+1][j]=VEC[j][i];
		}
	}
}
void LEFT(){
	for(int i=1;i<=n;++i)vec[i].clear(),VEC[i].clear();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(mp[i][j]=='B')vec[i].push_back('B');
			if(mp[i][j]=='C')vec[i].push_back('C');
			if(MP[i][j]!=make_pair(0ll,0ll)){
				VEC[i].push_back(MP[i][j]);
			}
			mp[i][j]='.';MP[i][j]={0,0};
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<(int)vec[i].size();++j){
			mp[i][j+1]=vec[i][j]; 
			MP[i][j+1]=VEC[i][j];
		}
	}
}
void RIGHT(){
	for(int i=1;i<=n;++i)vec[i].clear(),VEC[i].clear();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(mp[i][j]=='B')vec[i].push_back('B');
			if(mp[i][j]=='C')vec[i].push_back('C');
			if(MP[i][j]!=make_pair(0ll,0ll)){
				VEC[i].push_back(MP[i][j]);
			}
			mp[i][j]='.';MP[i][j]={0,0};
		}
	}
	for(int i=1;i<=n;++i){
		int o=vec[i].size(); 
		for(int j=0;j<(int)vec[i].size();++j){
			mp[i][m-o+j+1]=vec[i][j]; 
			MP[i][m-o+j+1]=VEC[i][j];
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>mp[i][j];mt[i][j]=mp[i][j];
			if(mp[i][j]!='.')MP[i][j]={i,j};
		}
	}
	cin>>k;cin>>str;k=str.size();str=" "+str;
	stack<char>stk;
	for(int i=1;i<=k;++i){
		stk.push(str[i]);
		if(stk.size()>=2){
			char p2=stk.top();stk.pop();
			char p1=stk.top();stk.pop();
			if(Clarify(p1)!=Clarify(p2))stk.push(p1);
			stk.push(p2);
		}
		if(stk.size()>=3){
			char p3=stk.top();stk.pop();
			char p2=stk.top();stk.pop();
			char p1=stk.top();stk.pop();
			stk.push(p1);stk.push(p2);
			if(p1==p3 && Clarify(p2)!=Clarify(p1))continue;
			stk.push(p3);
		}
	}
	while(!stk.empty()){
		opt.push_back(stk.top());stk.pop();
	}
	reverse(opt.begin(),opt.end());
	k=opt.size();
	opt=" "+opt;
	bool f0=0,f1=0;
	int pos=-1;
	for(int i=1;i<=k;++i){
		char S=opt[i];
		if(S=='G')UP();
		if(S=='D')DOWN();
		if(S=='L')LEFT();
		if(S=='P')RIGHT();
		if(Clarify(S))f1=1;
		else f0=1;
		if(i<k && i%4==k%4 && f0 && f1){pos=i;break;}
	}//DPGL 
	if(pos==-1){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cout<<mp[i][j];
			}cout<<'\n';
		}
		return 0;
	}
	for(int i=1;i<=8;++i)hsh[ROT[i]]=i;
	for(int i=pos;i<=k;i+=4){
		string S="";
		S+=opt[i+1],S+=opt[i+2],S+=opt[i+3],S+=opt[i+4];
		++CNT[hsh[S]];
	}
	for(int ITEM=1;ITEM<=8;++ITEM){
		if(!CNT[ITEM])continue;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				mt[i][j]=mp[i][j];
				if(mp[i][j]!='.')MP[i][j]={i,j};
				else MP[i][j]={0,0};
			}
		}
		mt[0][0]='.';
		for(int i=1;i<=4;++i){
			char S=ROT[ITEM][i-1];
			if(S=='G')UP();
			if(S=='D')DOWN();
			if(S=='L')LEFT();
			if(S=='P')RIGHT();		
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(MP[i][j].first==0 && MP[i][j].second==0)nxt[i][j][0]={i,j};
				else nxt[MP[i][j].first][MP[i][j].second][0]={i,j};
			}
		}
		int cyc=CNT[ITEM];
		for(int i=1;(1<<i)<=cyc;++i){
			for(int x=1;x<=n;++x){
				for(int y=1;y<=m;++y){
					nxt[x][y][i]=nxt[nxt[x][y][i-1].first][nxt[x][y][i-1].second][i-1];
				}
			}
		}
		for(int x=1;x<=n;++x){
			for(int y=1;y<=m;++y){
				int curx=x,cury=y,cur=cyc;
				for(int i=20;i>=0;--i){
					if((1<<i)>cur)continue;
					cur-=(1<<i);
					int X=curx,Y=cury;
					curx=nxt[X][Y][i].first,cury=nxt[X][Y][i].second;
				}
				Ans[curx][cury]=mt[x][y];
			}
		}
	}
	for(int x=1;x<=n;++x){
		for(int y=1;y<=m;++y){
			if(!Ans[x][y])Ans[x][y]='.';
			cout<<Ans[x][y];
		}
		cout<<'\n';
	}
	return 0;
}
//Written By ZHONGZIJIE0608
//HAPPY NEW YEAR
```

---

