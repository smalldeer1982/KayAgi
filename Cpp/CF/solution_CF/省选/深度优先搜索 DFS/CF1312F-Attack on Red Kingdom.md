# Attack on Red Kingdom

## 题目描述

The Red Kingdom is attacked by the White King and the Black King!

The Kingdom is guarded by $ n $ castles, the $ i $ -th castle is defended by $ a_i $ soldiers. To conquer the Red Kingdom, the Kings have to eliminate all the defenders.

Each day the White King launches an attack on one of the castles. Then, at night, the forces of the Black King attack a castle (possibly the same one). Then the White King attacks a castle, then the Black King, and so on. The first attack is performed by the White King.

Each attack must target a castle with at least one alive defender in it. There are three types of attacks:

- a mixed attack decreases the number of defenders in the targeted castle by $ x $ (or sets it to $ 0 $ if there are already less than $ x $ defenders);
- an infantry attack decreases the number of defenders in the targeted castle by $ y $ (or sets it to $ 0 $ if there are already less than $ y $ defenders);
- a cavalry attack decreases the number of defenders in the targeted castle by $ z $ (or sets it to $ 0 $ if there are already less than $ z $ defenders).

The mixed attack can be launched at any valid target (at any castle with at least one soldier). However, the infantry attack cannot be launched if the previous attack on the targeted castle had the same type, no matter when and by whom it was launched. The same applies to the cavalry attack. A castle that was not attacked at all can be targeted by any type of attack.

The King who launches the last attack will be glorified as the conqueror of the Red Kingdom, so both Kings want to launch the last attack (and they are wise enough to find a strategy that allows them to do it no matter what are the actions of their opponent, if such strategy exists). The White King is leading his first attack, and you are responsible for planning it. Can you calculate the number of possible options for the first attack that allow the White King to launch the last attack? Each option for the first attack is represented by the targeted castle and the type of attack, and two options are different if the targeted castles or the types of attack are different.

## 样例 #1

### 输入

```
3
2 1 3 4
7 6
1 1 2 3
1
1 1 2 2
3```

### 输出

```
2
3
0```

## 样例 #2

### 输入

```
10
6 5 4 5
2 3 2 3 1 3
1 5 2 3
10
4 4 2 3
8 10 8 5
2 2 1 4
8 5
3 5 3 5
9 2 10
4 5 5 5
2 10 4 2
2 3 1 4
1 10
3 1 5 3
9 8 7
2 5 4 5
8 8
3 5 1 4
5 5 10```

### 输出

```
0
2
1
2
5
12
5
0
0
2```

# 题解

## 作者：Froggy (赞：12)



### 博弈论好题

当时没学博弈论的我在这场 CF 后痛定思痛了 QAQ。

---

写这道题目之前,首先要知道**组合游戏**和**有向图游戏**,了解 **SG 函数** 和 **mex 运算**。~~(否则写这道题两眼一抹黑)~~

我们先考虑 $a_i$ 比较小的时候该怎么做。

先回顾几个定理:

- 有向图游戏的和的 SG 函数的值等于它包含的各个子游戏 SG 函数值的异或和。

- 有向图游戏的某个局面必败，当且仅当该局面对应 SG 函数值等于 $0$。

对于这道题目而言，我们可以把每个塔（数）看作一个有向图游戏，最后局面的 SG 函数值就是这 $n$ 个数的 SG 函数值的异或和。

甲先操作，那么甲就要在第一次操作后让局面的 SG 函数值变成 $0$。

由于每次操作还和上一次操作种类有关，那么每个有向图游戏的状态可以这样记：

$SG(k,c)$ 表示数的值为 $k$ 且上一次操作为 $c\,(0\leq c\leq 2)$ 的状态的 SG 函数值。

$c=0,1,2$ 分别表示上一次取 $x,y,z$ 个。特别地，没有操作等价于 $c=0$ 的情况 (因为它们的转移是相同的）

然后就可以得到：


$$\begin{aligned}
SG(k,0)&=\operatorname{mex}\{SG(k-x,0),SG(k-y,1),SG(k-z,2)\} \\
SG(k,1)&=\operatorname{mex}\{SG(k-x,0),SG(k-z,2)\} \\
SG(k,2)&=\operatorname{mex}\{SG(k-x,0),SG(k-y,1)\}
\end{aligned}$$

注意 $k-x,k-y,k-z$ 都要和 $0$ 取 $\max$ ，因为数字不能是负数。

然后就可以愉快地统计答案了！↓↓↓

令 $sum$ 为最初局面的 SG 函数值。

假设一个数最初的 SG 函数值为 $v_0$，甲第一次操作完后函数值的值为 $v$，那么新的 SG 函数的值为 $sum \operatorname{xor} v \operatorname{xor} v_0$

目标就是 $sum \operatorname{xor} v \operatorname{xor} v_0=0$，

设 $s_i$ 为 $v \operatorname{xor} v_0=i$ 的方案数，那么答案显然是 $s_{sum}$。

---

但是这道题目的 $a_i$ 达到了 $10^{18}$ 的级别，这样暴力求每个状态复杂度要爆炸。

发现 $x,y,z$ 的值很小，可以猜测 SG 函数的循环节应该不大。

每个状态的 SG 函数值最多有 $4$ 种可能，每次转移最多只与 $3\times 5=15$ 个状态有关，所以循环节大小最大是 $4^{15}$。

还是很大？但是根据 CF 官方题解上说（也可以通过打表），循环节最大是 $36$ ！证明可以看原题题解。

找循环节可以开个 `map`，每次往里扔最后 $5$ 个 $k$ 的 SG 函数的值，如果 `map` 中已经有了就说明找到循环节了。这时候用 `vector` 记录状态就很方便了！

找到循环节后，对于每个 $a_i$ 就可以 $\mathcal{O}(1)$ 分别求得操作之前和操作一次后的 SG 函数值。

问题就迎刃而解了。

---

***code：***

```cpp
typedef vector<vector<int> > vt;
typedef long long ll;
#define N 300030
int T,n,x,y,z,vis[5],pre,len; 
ll a[N];
vt sg;
map<vt,int> mp;
inline int mex(int a,int b,int c){ //mex运算
	memset(vis,0,sizeof(vis));
	vis[a]=vis[b]=vis[c]=1;
	for(int i=0;;++i){
		if(!vis[i])return i;
	}
} 
void Add(){ //加入状态
	vector<int> tmp(3,0);
	int tot=sg.size();
	tmp[0]=mex(sg[max(tot-x,0)][0],sg[max(tot-y,0)][1],sg[max(tot-z,0)][2]);
	tmp[1]=mex(sg[max(tot-x,0)][0],4,sg[max(tot-z,0)][2]);
	tmp[2]=mex(sg[max(tot-x,0)][0],sg[max(tot-y,0)][1],4);
	sg.push_back(tmp);
}
inline int Get(ll x){
	return x<pre?x:(x-pre)%len+pre;
}
int main(){
	T=read();
	while(T--){
		n=read(),x=read(),y=read(),z=read();
		for(int i=1;i<=n;++i){
			a[i]=read();
		}
		sg.clear(),mp.clear();
		sg.push_back({0,0,0});
		for(int i=1;i<5;++i){
			Add();
		}
		while("zz has no dick! /fn"){
			vt tmp(sg.end()-5,sg.end());
			if(mp.count(tmp)){  //找到了循环节
				pre=mp[tmp],len=sg.size()-5-pre;  //pre是进入循环之前的长度，len是循环节长度
				break;
			}
			mp[tmp]=sg.size()-5;
			Add();
		}
		int sum=0,s[4]={0,0,0,0};
		for(int i=1;i<=n;++i){
			ll v0=max(a[i]-x,0LL),v1=max(a[i]-y,0LL),v2=max(a[i]-z,0LL);
			int now=sg[Get(a[i])][0],X=sg[Get(v0)][0],Y=sg[Get(v1)][1],Z=sg[Get(v2)][2]; //分别是操作之前的SG函数值和每种操作后的SG函数值
			sum^=now;
			++s[now^X],++s[now^Y],++s[now^Z];
		}
		printf("%d\n",s[sum]);
	}
	return 0;
}

```


---

## 作者：dead_X (赞：1)

## 思路
注意到这个游戏同时在多个数上进行，因此我们要求 SG 函数。

注意到 $x,y,z$ 都很小，这必然有用。

我们考虑列出 SG 函数。设 $f_{i,j}$ 为当前数为 $i$，上一次执行操作为 $j$ 的 SG 函数，则 $f_{i}$ 显然只与 $f_{i-5}$ 及之后的数有关。

这 $15$ 个数一共只有 $4^{3\max(x,y,z)}$ 个状态，因此循环节最大只有 $4^{3\max(x,y,z)}$。在得到循环节之后，我们就可以快速算出一个很大的数的 SG 函数了。

最后的问题是如何统计能获胜的操作数量，这个我降智了好久，最后发现枚举所有操作分别算出操作后的 SG 值就可以了。

因此我们预处理所有 $x,y,z$ 对应的 SG 函数，每次不单独计算即可，时间复杂度为 $xyzL$，其中 $L$ 为循环节长度。

看起来这个复杂度过不去，事实上我们手捏几组大数据会发现，SG 函数会很快进入循环节，大概只要循环几十次。

在写题解之前，我去看了 froggy 的题解，上面说 CF 题解中证明了循环节最多为 $36$。于是我跑去 CF 上看了官方题解，最后发现 $36$ 是暴力枚举得到的？？？
## 代码
```cpp
// Problem: F. Attack on Red Kingdom
// Contest: Codeforces - Educational Codeforces Round 83 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1312/F
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//愿神 zhoukangyang 指引我。
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int sdt,len;
int f[100003][4];
void init(int x,int y,int z)
{
	unordered_map<unsigned,int> mp;
	mp[0]=0;
	bool F=0;
	for(int i=5; i<=1000; ++i)
	{
		unsigned s=0;
		bool vis[5];
		memset(vis,0,sizeof(vis)),
		f[i][0]=f[i][1]=f[i][2]=0;
		vis[f[i-x][0]]=vis[f[i-y][1]]=vis[f[i-z][2]]=1;
		while(vis[f[i][0]]) ++f[i][0];
		memset(vis,0,sizeof(vis)),
		vis[f[i-x][0]]=vis[f[i-z][2]]=1;
		while(vis[f[i][1]]) ++f[i][1];
		memset(vis,0,sizeof(vis)),
		vis[f[i-x][0]]=vis[f[i-y][1]]=1;
		while(vis[f[i][2]]) ++f[i][2];
		f[i][3]=(f[i][0]<<4)+(f[i][1]<<2)+f[i][2];
		for(int j=i-4; j<=i; ++j) 
		s=(s<<6)+f[j][3];
		if(mp.find(s)!=mp.end())
		{
			sdt=mp[s],len=i-4-mp[s];
			F=1;
			break;
		}
		mp[s]=i-4;
	}
	return ;
}
int solve(int x)
{
	if(x<sdt) return x;
	return sdt+(x-sdt)%len;
}
signed main()
{
	for(int T=read();T--;)
	{
		int n=read(),x=read(),y=read(),z=read();
		init(x,y,z);
		int c[4],s=0;
		c[0]=c[1]=c[2]=c[3]=0;
		for(int i=1,G,A,B,C; i<=n; ++i)
			G=read()+4,
			A=f[solve(G-x)][0],   
			B=f[solve(G-y)][1],
			C=f[solve(G-z)][2],
			G=f[solve(G)  ][0],
			++c[A^G],++c[B^G],++c[C^G],s^=G;
		printf("%lld\n",c[s]);
	}
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
SG 函数康复训练。

摘自 [交互、构造、博弈](https://www.luogu.com.cn/training/676672)。

类似类型题目：[CF273E](https://www.luogu.com.cn/problem/CF273E)。
## 思路分析
先对单个数考虑。

发现上一次进行的操作种类对下一次的选择会产生较大影响，所以我们直接把数值大小和上一次操作种类一起压进状态。

考虑 SG 函数，定义 $sg_{i,j}$ 表示数值为 $i$ 上一次操作为 $j$ 的 SG 函数，那么我们有倒着转移：

$$sg_{i,1}=\text{mex}(sg_{i-x,1},sg_{i-y,2},sg_{i-z,3})$$
$$sg_{i,2}=\text{mex}(sg_{i-x,1},sg_{i-z,3})$$
$$sg_{i,3}=\text{mex}(sg_{i-x,1},sg_{i-y,2})$$

发现值域比较吓人，而 $x,y,z$ 的值又较小，不妨先来打表看看。

通过打表的方式，我们发现这个 SG 函数存在循环节（其实这种要么就是循环节，要么就是连续段划分）。

考虑到 $sg_{i,k}$ 的转移最远只能从 $sg_{i-5,k}$ 转移过来。

所以我们取当前的最后 $5$ 位记忆化，跑到循环节就记录环长/进入环步数预处理即可。

看下最后跑出来的结果会发现最长的也只需要 $36$ 步就已经跑完了一个完整的循环节了，所以这一步的运算次数大概是 $5^4\times 36\times3$，显然是随便跑的。

有了 SG 函数值再来处理下一步问题。

根据 SG 函数的定义，先手只需要操作一次使得变化后的 SG 函数异或和为 $0$ 则必胜。

也就是对于先手假设操作了一个 SG 函数值为 $x$ 的，将其变为了 $x'$，且原来总的 SG 函数值异或和为 $s$。

当且仅当 $x\oplus s\oplus x'=0$ 时，先手才必胜。

移项也就是 $x\oplus x'=s$ 时，先手必胜。

左边的扔进桶里右边的扫一遍算出来输出就行了。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=3e5+10,M=1e5+10,V=2e2+10,lim=19,mod=998244353,INF=0x3f3f3f3f3f3f3f3f;
int n,x,y,z,pre[6][6][6];vector<int> f[6][6][6][3];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int getmex(int x,int y,int z)
{
	if(!(x==0||y==0||z==0)) return 0;
	if(!(x==1||y==1||z==1)) return 1;
	if(!(x==2||y==2||z==2)) return 2;
	return 3;
}
inline void prework()
{
	for(int x=1;x<=5;x++) for(int y=1;y<=5;y++) for(int z=1;z<=5;z++)
	{
		int i=1;
		for(int k=0;k<3;k++) f[x][y][z][k].emplace_back(0);
		map<vector<tuple<int,int,int>>,int>mp;
		while(1)
		{
			for(int k=0;k<3;k++) 
				f[x][y][z][k].emplace_back(getmex(
				f[x][y][z][0][max(0ll,i-x)],
				k!=1?f[x][y][z][1][max(0ll,i-y)]:-1,
				k!=2?f[x][y][z][2][max(0ll,i-z)]:-1));
			if(i>=4)
			{
				vector<tuple<int,int,int>>a;
				for(int j=i-4;j<=i;j++) a.emplace_back(f[x][y][z][0][j],f[x][y][z][1][j],f[x][y][z][2][j]);
				if(mp.count(a))
				{
					pre[x][y][z]=mp[a];
					break;
				}mp[a]=i-4;
			}i++;
		}cout<<i<<endl;
	}
}
inline int get(int w)
{
	int len=f[x][y][z][0].size()-5-pre[x][y][z];
	return w<pre[x][y][z]?w:(w-pre[x][y][z])%len+pre[x][y][z];
}
inline void solve()
{
	n=read();x=read(),y=read(),z=read();int s=0,cnt[5]={0};
	for(int i=1,cur,w,a,b,c;i<=n;i++)
	{
		w=read();
		cur=f[x][y][z][0][get(w)];
		a=f[x][y][z][0][get(max(0ll,w-x))];
		b=f[x][y][z][1][get(max(0ll,w-y))];
		c=f[x][y][z][2][get(max(0ll,w-z))];
		s^=cur;cnt[cur^a]++;cnt[cur^b]++;cnt[cur^c]++;
	}print(cnt[s]);put('\n');
}
signed main()
{
	int T=1;prework();
	T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

