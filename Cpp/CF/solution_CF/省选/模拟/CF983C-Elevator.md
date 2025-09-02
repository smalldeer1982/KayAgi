# Elevator

## 题目描述

## 题意

一个$9$层的楼有一个可以容纳$4$个人的电梯，你要管理这个电梯。

现在各层楼上有一些在排队的人，你知道他们在哪层要到哪层去。你也知道到电梯门口的顺序。根据公司的规定，如果一个人比其他人早到。他也必须先进电梯（无论楼层，只凭时间）。注意人们可以随时离开电梯。

电梯有两个命令：
* 上楼或者下楼， 代价为1
* 打开当前楼层的门，所有到目的地的人会从电梯里出来，当前楼层排队的人会在**不违反规定的情况下**一个一个进（在电梯还有空间的情况下）（这不是天朝的电梯，不能超员）每个人用1s时间来出入电梯。

最初电梯是空的，在1楼。你需要求出最少用多长时间来吧所有人送回到目的地。最后电梯可以停在任意位置

## 样例 #1

### 输入

```
2
3 5
5 3
```

### 输出

```
10```

## 样例 #2

### 输入

```
2
5 3
3 5
```

### 输出

```
12```

# 题解

## 作者：DPair (赞：2)

## 【前言】

这个做法十分暴力，复杂度似乎也不对，但还是过了。。。（几乎每个点都卡着时限），仅供参考，肯定有更优秀的解法。（最后跑了 $1.49min$ 你敢信？）

## 【思路】

首先我们发现这是一个最优化问题，考虑 $DP$ 。

这个做法的状态设计十分暴力，不难发现某一状态下电梯的状态只与电梯中每个人的目的地与电梯所在楼层有关，而与电梯中人的编号是无关的。

这不难证明，如果按人的编号进行 $n$ 次DP，并保证当前编号的人上了电梯（不一定要下电梯），那么每次DP时都不会出现编号大的先上了电梯的不合法情况。

由于电梯只有 $4$ 个位置，考虑设置一个五维数组。（ $n$ 那一维直接滚动数组滚掉了，这里不赘述）

设：

$$
dp[j][k1][k2][k3][k4]
$$

表示有一批人，他们分别要到达 $k1, k2, k3, k4$ 楼层且电梯在 $j$ 层，这个状态表示送走这批人时达到这个状态，所需要的最小时间。

但由于电梯不仅要送人，还要接人，因此再设一个五维数组。

设：

$$
g[j][k1][k2][k3][k4]
$$

表示有一批人，他们分别要到达 $k1, k2, k3, k4$ 楼层且电梯在 $j$ 层，这个状态表示接走这批人时达到这个状态所需要的最小时间。

以上当 $k=0$ 时，表示这个位置为空，可以接人。

下面考虑状态转移。

首先是送人环节：

$$
if(k1)dp[k1][0][k2][k3][k4]=min(dp[k1][0][k2][k3][k4], dp[j][k1][k2][k3][k4] + abs(j - k1) + 1)
$$

$$
if(k2)dp[k2][k1][0][k3][k4]=min(dp[k2][k1][0][k3][k4], dp[j][k1][k2][k3][k4] + abs(j - k2) + 1)
$$

$$
if(k3)dp[k3][k1][k2][0][k4]=min(dp[k3][k1][k2][0][k4], dp[j][k1][k2][k3][k4] + abs(j - k3) + 1)
$$

$$
if(k4)dp[k4][k1][k2][k3][0]=min(dp[k4][k1][k2][k3][0], dp[j][k1][k2][k3][k4] + abs(j - k4) + 1)
$$

这是显然的，表示你的电梯从 $j$ 层走到了 $k1,k2,k3,k4$ ，去送人，而且你送人还需要 $1$ ，单位的时间，然后这个位置就没人了。

由于要送 $4$ 个人，考虑循环 $4$ 次。

然后是接人（实际实现中先接人再送人）：

$$
g[a[i]][b[i]][k2][k3][k4]=min(g[a[i]][b[i]][k2][k3][k4], dp[j][0][k2][k3][k4] + abs(j - a[i]) + 1);
$$

$$
g[a[i]][k1][b[i]][k3][k4]=min(g[a[i]][k1][b[i]][k3][k4], dp[j][k1][0][k3][k4] + abs(j - a[i]) + 1);
$$

$$
g[a[i]][k1][k2][b[i]][k4]=min(g[a[i]][k1][k2][b[i]][k4], dp[j][k1][k2][0][k4] + abs(j - a[i]) + 1);
$$

$$
g[a[i]][k1][k2][k3][b[i]]=min(g[a[i]][k1][k2][k3][b[i]], dp[j][k1][k2][k3][0] + abs(j - a[i]) + 1);
$$

也很显然，你只有有空位才能接一个人。

然后接完人之后电梯的状态其实就是你送人的状态。

然后代码就很好实现了。

最后，由于电梯可以停在任意一个位置，答案就是：

$$
ans=min\{dp[j][0][0][0][0]\}(j\in[1,9])
$$

最终复杂度 $O(n*10^5)$ ，还有大量常数，但就是过了。

代码很好实现：

## 【代码】

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef unsigned int UI;
typedef pair <int, int> pi;

template <typename T>
inline T mn(T x, T y) {return x < y ? x : y;}
template <typename T>
inline T mx(T x, T y) {return x > y ? x : y;}
template <typename T>
inline void chmin(T &x, T y) {(x > y) && (x = y);}
template <typename T>
inline void chmax(T &x, T y) {(x < y) && (x = y);}

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
//下面是有效代码
int dp[10][10][10][10][10], g[10][10][10][10][10];
int a[2010], b[2010], n;
int main(){
    read(n);
    memset(dp, 31, sizeof(dp));dp[1][0][0][0][0] = 0;//初始化，电梯在一楼，空的
    for (register int i = 1;i <= n;i ++){
        read(a[i]);read(b[i]);
        memset(g, 31, sizeof(g));
        for (register int j = 1;j <= 9;j ++){//接人
            for (register int k1 = 0;k1 <= 9;k1 ++){
                for (register int k2 = 0;k2 <= 9;k2 ++){
                    for (register int k3 = 0;k3 <= 9;k3 ++){
                        for (register int k4 = 0;k4 <= 9;k4 ++){
                            if(!k1) chmin(g[a[i]][b[i]][k2][k3][k4], dp[j][k1][k2][k3][k4] + abs(j - a[i]) + 1);
                            if(!k2) chmin(g[a[i]][k1][b[i]][k3][k4], dp[j][k1][k2][k3][k4] + abs(j - a[i]) + 1);
                            if(!k3) chmin(g[a[i]][k1][k2][b[i]][k4], dp[j][k1][k2][k3][k4] + abs(j - a[i]) + 1);
                            if(!k4) chmin(g[a[i]][k1][k2][k3][b[i]], dp[j][k1][k2][k3][k4] + abs(j - a[i]) + 1);
                        }
                    }
                }
            }
        }
        memcpy(dp, g, sizeof(dp));
        for (register int k = 1;k <= 4;k ++){//送人×4
            for (register int j = 1;j <= 9;j ++){
                for (register int k1 = 0;k1 <= 9;k1 ++){
                    for (register int k2 = 0;k2 <= 9;k2 ++){
                        for (register int k3 = 0;k3 <= 9;k3 ++){
                            for (register int k4 = 0;k4 <= 9;k4 ++){
                                if(k1) chmin(dp[k1][0][k2][k3][k4], dp[j][k1][k2][k3][k4] + abs(j - k1) + 1);
                                if(k2) chmin(dp[k2][k1][0][k3][k4], dp[j][k1][k2][k3][k4] + abs(j - k2) + 1);
                                if(k3) chmin(dp[k3][k1][k2][0][k4], dp[j][k1][k2][k3][k4] + abs(j - k3) + 1);
                                if(k4) chmin(dp[k4][k1][k2][k3][0], dp[j][k1][k2][k3][k4] + abs(j - k4) + 1);
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for (register int i = 1;i <= 9;i ++) chmin(ans, dp[i][0][0][0][0]);
    fprint(ans, 10);
    return 0;
}
```



---

## 作者：Shunpower (赞：0)

简单题。

首先你需要先读对题，不是每层楼按照时间顺序上电梯，是所有人按照时间顺序上电梯，无论哪个楼层。读对了这个我们容易设计出来一个状态：$f_{i,j,mask}$，表示目前前 $i$ 个人上了电梯，现在电梯在第 $j$ 层，电梯里的人想到达的楼层状态是 $mask$，$mask$ 恰好可以是一个四位十进制数。

考虑这样有多少状态，如果不精细实现（不排除 $mask$ 中因为无序导致的本质相同的情况）发现是 $2\times 10^8$ 种，直接随意实现开不下这么大的空间，还需要滚动数组，比较麻烦。

考虑优化状态。我们发现，在第 $i$ 个人上了电梯之后电梯肯定在 $a_i$ 楼，然后我们去接下一个人。所以我们考虑状态 $f_{i,mask}$ 表示现在电梯接完人 $i$ 在 $a_i$ 楼，电梯里的人（包括 $i$）想到达的楼层状态是 $mask$。然后我们考虑转移。

我们发现，转移总是形如从 $a_i$ 楼到 $a_{i+1}$ 楼，中途让电梯里面人的一个子集下电梯。所以我们考虑再预处理一个 $g_{i,j,mask}$ 表示电梯从 $i$ 楼到 $j$ 楼，想到达的楼层状态是 $mask$ 的一堆人下电梯。这可以直接枚举 $i,j,mask$ 再枚举 $mask$ 有值位置的全排列直接暴力计算，做到跑不满的 $\mathcal O(10^p\cdot p^pf^2)$，其中 $p=4,f=9$。

在 $f$ 的转移中，我们直接枚举下电梯的人的子集，利用 $g$ 来计算转移产生的代价。直接朴素实现转移就能做到 $\mathcal O(2^p\cdot p)$。

最终答案因为电梯里所有人都要下电梯，直接枚举人 $n$ 上电梯之后的电梯中人的状态和最后到达哪个楼层，再利用 $g$ 计算一次就行。

初值显然是 $f_{0,0}=0$，其他 $f$ 为 $+\infty$，特别地实现时要设置 $a_0=1$。

总时间复杂度 $\mathcal O(10^p(p^pf^2+2^pp\cdot n))$，但是严重跑不满所以和常数基本平衡了。最终跑了 $1$ 秒。

拆函数写起来还是比较清晰的，写完调了一下样例直接 A 了。

```cpp
int dp[N][10000];
int w[10][10][10000];
int n;
int a[N],b[N];
vector <int> sub;
int subans;
int getc(int mask,int pos){
    if(pos==0) return mask%10;
    else if(pos==1) return mask/10%10;
    else if(pos==2) return mask/100%10;
    else return mask/1000;
}
int getsubset(int mask,int sub){
    int ans=0;
    if(sub&1){
        if(!(mask%10)) return -1;
        ans+=mask%10;
    }
    if((sub>>1)&1){
        if(!(mask/10%10)) return -1;
        ans+=mask/10%10*10;
    }
    if((sub>>2)&1){
        if(!(mask/100%10)) return -1;
        ans+=mask/100%10*100;
    }
    if((sub>>3)&1){
        if(!(mask/1000)) return -1;
        ans+=mask/1000*1000;
    }
    return ans;
}
int getminn0(int mask){
    if(!(mask%10)) return 0;
    if(!(mask/10%10)) return 1;
    if(!(mask/100%10)) return 2;
    if(!(mask/1000)) return 3;
    return -1;
}
int mergenew(int mask,int pos,int to){
    if(pos==0) return mask+to;
    else if(pos==1) return mask+to*10;
    else if(pos==2) return mask+to*100;
    else return mask+to*1000;
}
bool vis[5];
void dfs(int x,int sum,int st,int gl){
    if(x==sub.size()) return subans=min(subans,sum+abs(st-gl)),void();
    fr1(i,0,(int)sub.size()-1){
        if(vis[i]) continue;
        vis[i]=1;
        dfs(x+1,sum+abs(sub[i]-st),sub[i],gl);
        vis[i]=0;
    }
}
int main(){
#ifdef SHUN
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    memset(dp,0x3f,sizeof dp);
    cin>>n;
    fr1(i,1,n) cin>>a[i]>>b[i];
    fr1(x,1,9){
        fr1(y,1,9){
            fr1(g,0,9999){
                sub.clear();
                fr1(p,0,3){
                    if(getc(g,p)!=0) sub.pb(getc(g,p));
                }
                subans=1e9;
                dfs(0,0,x,y);
                w[x][y][g]=subans;
            }
        }
    }
    a[0]=1;
    dp[0][0]=0;
    fr1(i,1,n){
        fr1(j,0,9999){
            if(dp[i-1][j]==0x3f3f3f3f) continue;
            fr1(k,0,15){
                int Pass=getsubset(j,k);
                if(Pass==-1) continue;
                int pos=getminn0(j-Pass);
                if(pos==-1) continue;
                int status=j-Pass;
                status=mergenew(status,pos,b[i]);
                dp[i][status]=min(dp[i][status],dp[i-1][j]+w[a[i-1]][a[i]][Pass]);
            }
        }
    }
    int ans=1e9;
    fr1(j,0,9999){
        fr1(k,1,9) ans=min(ans,dp[n][j]+w[a[n]][k][j]);
    }
    cout<<ans+2*n<<'\n';
    ET;
}
```

[AC Submission](https://codeforces.com/contest/983/submission/280819762)。

---

## 作者：SFlyer (赞：0)

首先有提个很明显的 dp 状态：$dp_{i,a,b,c,d,f}$ 表示已经考虑了前 $i$ 个人，然后现在在电梯里的是想要到 $a,b,c,d$，现在楼层是 $f$。可惜这样的状态数太大了。因此考虑可以把 $a,b,c,d$ 排序。这样状态数可以少很多。（$a,b,c,d$ 只有 $495$ 种）

考虑转移，有几种情况：

- 上一层楼，这里要求 $f<9$。

- 下一层楼，这里要求 $f>1$。

- 下一个人，要么是 $a,b,c,d$。这里要求正好是他要去的楼层。

- 上一个人，这里要求是 $a\neq 0$（因为是排好序的），直接使这个人变为 $a$ 再排序。

因为花费的时间都是 $1$，所以可以直接 bfs。

注意要卡空间。可以把一些换成 `bool` 或 `char` 即可。


```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e3+3;

#define node tuple<int,int,char,char,char,char,int>

int n,fr[N],to[N];
bool hsh[N][10][10][10][10][10];
queue<node> q;

void pu(int tm,int _n,char a,char b,char c,char d,int f){	
	#define sp(x,y) if (x>y) swap(x,y);
	sp(a,b)sp(b,c)sp(c,d)sp(a,b)sp(b,c)sp(a,b);
	if (!hsh[_n][a][b][c][d][f]){
		hsh[_n][a][b][c][d][f]=1;
		q.push(make_tuple(tm,_n,a,b,c,d,f));
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=1; i<=n; i++){
		cin>>fr[i]>>to[i];
	}
	pu(0,0,0,0,0,0,1);
	while (!q.empty()){
		int tm,_n,a,b,c,d,f;
		tie(tm,_n,a,b,c,d,f)=q.front();
		if (_n==n && !a && !b && !c && !d){
			cout<<tm<<"\n";
			return 0;
		}
		q.pop();
		hsh[_n][a][b][c][d][f]=1;
		if (f<9){
			pu(tm+1,_n,a,b,c,d,f+1);
		}
		if (f>1){
			pu(tm+1,_n,a,b,c,d,f-1);
		}
		if (a==f){
			pu(tm+1,_n,0,b,c,d,f);
		}
		if (b==f){
			pu(tm+1,_n,a,0,c,d,f);
		}
		if (c==f){
			pu(tm+1,_n,a,b,0,d,f);
		}
		if (d==f){
			pu(tm+1,_n,a,b,c,0,f);
		}
		if (!a && _n<n && fr[_n+1]==f){
			pu(tm+1,_n+1,to[_n+1],b,c,d,f);
		}
	}
	return 0;
}
```

---

## 作者：zztqwq (赞：0)

$f(i,s_0,s_1,s_2)$ 表示考虑到前 $i$ 个人刚进入电梯的情况，剩下三个人想要到的层分别是 $s_0,s_1,s_2$（如果无人则为 $0$），为了方便可以钦定 $s_0\le s_1\le s_2$。那么每次考虑到下一个人进电梯之前这四个人去最终的楼层以及顺序即可。$\mathcal O(9^3n\cdot(\mathrm A_4^1+\mathrm A_4^2+\mathrm A_4^3+\mathrm A_4^4))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
void write(int n)
{
	if(n<0){putchar('-');n=-n;}
	if(n>9)write(n/10);
	putchar(n%10^48);
}
const int N=2010,inf=0x3f3f3f3f;
int f[N][10][10][10],a[N],b[N]; 
void Min(int &x,int y){x=min(x,y);}
void Sort(int &a,int &b,int &c,int &d)
{
	vector<int> v(4);
	v[0]=a,v[1]=b,v[2]=c,v[3]=d;
	sort(v.begin(),v.end());
	a=v[0],b=v[1],c=v[2],d=v[3];
}
int main()
{
	int n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	memset(f,0x3f,sizeof(f));
	f[1][0][0][0]=a[1];
	for(int i=1;i<=n;i++)
	{
		for(int s0=0;s0<=9;s0++)
		{
			for(int s1=s0;s1<=9;s1++)
			{
				for(int s2=s1;s2<=9;s2++)
				{
					if(f[i][s0][s1][s2]==inf)continue;
					int c0=s0,c1=s1,c2=s2,c3=b[i],now=a[i];
					Sort(c0,c1,c2,c3);
					if(c0)//四个人全走 
					{
						int c[4]={c0,c1,c2,c3};
						do{
							Min(f[i+1][0][0][0],
							f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-c[2])+abs(c[2]-c[3])+abs(c[3]-a[i+1])+5);
						}while(next_permutation(c,c+4));
					}
					if(c1)//走三个 
					{
						int c[3]={0,0,0};
						if(c0&&c1&&c2)
						{
							c[0]=c0,c[1]=c1,c[2]=c2;
							do{
								Min(f[i+1][0][0][c3],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-c[2])+abs(c[2]-a[i+1])+4);
							}while(next_permutation(c,c+3));
						}
						if(c0&&c1&&c3)
						{
							c[0]=c0,c[1]=c1,c[2]=c3;
							do{
								Min(f[i+1][0][0][c2],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-c[2])+abs(c[2]-a[i+1])+4);
							}while(next_permutation(c,c+3));
						}
						if(c0&&c2&&c3)
						{
							c[0]=c0,c[1]=c2,c[2]=c3;
							do{
								Min(f[i+1][0][0][c1],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-c[2])+abs(c[2]-a[i+1])+4);
							}while(next_permutation(c,c+3));
						}
						if(c1&&c2&&c3)
						{
							c[0]=c1,c[1]=c2,c[2]=c3;
							do{
								Min(f[i+1][0][0][c0],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-c[2])+abs(c[2]-a[i+1])+4);
							}while(next_permutation(c,c+3));
						}
					}
					if(c2)//走两个 
					{
						int c[2]={0,0};
						if(c0&&c1)
						{
							c[0]=c0,c[1]=c1;
							do{
								Min(f[i+1][0][c2][c3],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-a[i+1])+3);
							}while(next_permutation(c,c+2));
						}
						if(c0&&c2)
						{
							c[0]=c0,c[1]=c2;
							do{
								Min(f[i+1][0][c1][c3],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-a[i+1])+3);
							}while(next_permutation(c,c+2));
						}
						if(c0&&c3)
						{
							c[0]=c0,c[1]=c3;
							do{
								Min(f[i+1][0][c1][c2],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-a[i+1])+3);
							}while(next_permutation(c,c+2));
						}
						if(c1&&c2)
						{
							c[0]=c1,c[1]=c2;
							do{
								Min(f[i+1][0][c0][c3],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-a[i+1])+3);
							}while(next_permutation(c,c+2));
						}
						if(c1&&c3)
						{
							c[0]=c1,c[1]=c3; 
							do{
								Min(f[i+1][0][c0][c2],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-a[i+1])+3);
							}while(next_permutation(c,c+2));
						}
						if(c2&&c3)
						{
							c[0]=c2,c[1]=c3;
							do{
								Min(f[i+1][0][c0][c1],
								f[i][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-a[i+1])+3);
							}while(next_permutation(c,c+2));
						}
					}
					//走一个
					{
						if(c3)Min(f[i+1][c0][c1][c2],f[i][s0][s1][s2]+abs(now-c3)+abs(c3-a[i+1])+2);
						if(c2)Min(f[i+1][c0][c1][c3],f[i][s0][s1][s2]+abs(now-c2)+abs(c2-a[i+1])+2);
						if(c1)Min(f[i+1][c0][c2][c3],f[i][s0][s1][s2]+abs(now-c1)+abs(c1-a[i+1])+2);
						if(c0)Min(f[i+1][c1][c2][c3],f[i][s0][s1][s2]+abs(now-c0)+abs(c0-a[i+1])+2);
					}
					
					if(!c0)Min(f[i+1][c1][c2][c3],f[i][s0][s1][s2]+abs(now-a[i+1])+1);//不走 
				}
			}
		}
	}
	int Ans=inf;
	for(int s=1;s<=9;s++)
	{
		a[n+1]=s;
		for(int s0=0;s0<=9;s0++)
		{
			for(int s1=s0;s1<=9;s1++)
			{
				for(int s2=s1;s2<=9;s2++)
				{

					int c0=s0,c1=s1,c2=s2,c3=b[n],now=a[n];
					Sort(c0,c1,c2,c3);
					if(c0)
					{
						int c[4]={c0,c1,c2,c3};
						do{
							Min(Ans,
							f[n][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-c[2])+abs(c[2]-c[3])+abs(c[3]-a[n+1])+4);
						}while(next_permutation(c,c+4));
					}
					else if(c1)
					{
						int c[3]={0,0,0};
						c[0]=c1,c[1]=c2,c[2]=c3;
						do{
							Min(Ans,
							f[n][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-c[2])+abs(c[2]-a[n+1])+3);
						}while(next_permutation(c,c+3));
					}
					else if(c2)
					{
						int c[2]={c2,c3};
						c[0]=c2,c[1]=c3;
						do{
							Min(Ans,
							f[n][s0][s1][s2]+abs(now-c[0])+abs(c[0]-c[1])+abs(c[1]-a[n+1])+2);
						}while(next_permutation(c,c+2));
					}
					else Min(Ans,f[n][s0][s1][s2]+abs(now-c3)+abs(c3-a[n+1])+1);
				}
			}
		}
	}
	printf("%d",Ans);
	return 0; 
}
```

---

