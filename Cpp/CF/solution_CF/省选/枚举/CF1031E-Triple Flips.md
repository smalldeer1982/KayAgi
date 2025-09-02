# Triple Flips

## 题目描述

You are given an array $ a $ of length $ n $ that consists of zeros and ones.

You can perform the following operation multiple times. The operation consists of two steps:

1. Choose three integers $ 1 \le x < y < z \le n $ , that form an arithmetic progression ( $ y - x = z - y $ ).
2. Flip the values $ a_x, a_y, a_z $ (i.e. change $ 1 $ to $ 0 $ , change $ 0 $ to $ 1 $ ).

Determine if it is possible to make all elements of the array equal to zero. If yes, print the operations that lead the the all-zero state. Your solution should not contain more than $ (\lfloor \frac{n}{3} \rfloor + 12) $ operations. Here $ \lfloor q \rfloor $ denotes the number $ q $ rounded down. We can show that it is possible to make all elements equal to zero in no more than this number of operations whenever it is possible to do so at all.

## 说明/提示

In the first sample the shown output corresponds to the following solution:

- 1 1 0 1 1 (initial state);
- 0 1 1 1 0 (the flipped positions are the first, the third and the fifth elements);
- 0 0 0 0 0 (the flipped positions are the second, the third and the fourth elements).

Other answers are also possible. In this test the number of operations should not exceed $ \lfloor \frac{5}{3} \rfloor + 12 = 1 + 12 = 13 $ .

In the second sample the only available operation is to flip all the elements. This way it is only possible to obtain the arrays 0 1 0 and 1 0 1, but it is impossible to make all elements equal to zero.

## 样例 #1

### 输入

```
5
1 1 0 1 1
```

### 输出

```
YES
2
1 3 5
2 3 4
```

## 样例 #2

### 输入

```
3
0 1 0
```

### 输出

```
NO
```

# 题解

## 作者：「QQ红包」 (赞：3)

## 题意

CF1031E. Triple Flips

[传送门](https://codeforces.com/contest/1031/problem/E)

给你一个长度为$n$的01序列，每次可以选三个距离相同的数反转（0变成1,1变成0），构造一种方案使操作次数$\le \frac{n}{3}+12$。

$n\le 10^5$

## 做法

手玩好题。

手玩了下然后看了下题解，

打暴力发现，当$n \ge 8$的时候都可以构成。

然后想八位八位的构造，发现次数达到了$\frac{5n}{8}$，

因为操作次数是$\frac{n}{3}$级别的，所以感觉前面一部分的每个三位可以一次得到答案。

继续打表发现当$n \ge 11$的时候，前6位可以在2步内构成。

如果再操作一次会在$8$个字符以内，就不一定能构造出解，这样我们就强行保留八位（包括已经变成0的）

最后剩下的$10$步暴力。

## 代码
暴力+打表
```cpp
/*
 * Author: ylx
 * Lang: c++
 * Prog: 1031E
 */
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void qmax(int &x,int y) {if (x<y) x=y;}
void qmin(int &x,int y) {if (x>y) x=y;}
inline int read()
{
	char s;
	int k=0,base=1;
	while ((s=getchar())!='-'&&s!=EOF&&!(isdigit(s)));
	if (s==EOF) exit(0);
	if (s=='-') base=-1,s=getchar();
	while (isdigit(s)) k=k*10+(s^'0'),s=getchar();
	return k*base;
}
inline void write(ll x)
{
	static char cnt,num[20];cnt=0;
	if (!x)
	{
		putchar('0');
		return;
	}
	for (;x;x/=10) num[++cnt]=x%10;
	for (;cnt;putchar(num[cnt--]+48));
}
const int maxm=1<<12;
int dis[maxm];
int Dis[maxm];
int g[maxm][2];
int a[50],n,m;
int c[maxm];
void dfs(int x,int cnt,int now)
{
	if (x==m+1)
	{
		qmin(dis[now],cnt);
		if (dis[now]<Dis[now>>5])
		{
			Dis[now>>5]=dis[now];
			g[now>>5][0]=c[1];
			g[now>>5][1]=c[2];
			if (now==1904) 
			{
				cerr<<(now>>5)<<" "<<cnt<<" "<<c[1]<<" "<<c[2]<<" "<<(c[1]^c[2])<<endl;
				cerr<<g[59][0]<<" "<<g[59][1]<<endl;
			}
		}
		return;
	}
	c[cnt+1]=a[x];
	dfs(x+1,cnt+1,now^a[x]);
	c[cnt+1]=0;
	dfs(x+1,cnt,now);
}
void work()
{
	while (a[m]*2<=n)
	{
		a[m+1]=a[m]*2;
		m++;
	}
}
void Wr(int x)
{
	int len=0;
	while (x)
	{
		a[++len]=x%2;
		x/=2;
	}
	int cnt=0;
	for (int i=len;i>=1;i--)
	{
		if (a[i]==1)
		{
			cnt++;
			printf("%d",i);
			if (cnt!=3) putchar(',');
		}
	}
}
int main()
{
#ifdef ylx
	freopen("1031E.in","r",stdin);
	freopen("1031E.out","w",stdout);
#endif
	n=(1<<11);
	m++;a[m]=7;work();
	m++;a[m]=21;work();
	m++;a[m]=73;work();
	m++;a[m]=273;work();
	m++;a[m]=1057;work();
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(Dis,0x3f3f3f3f,sizeof(Dis));
	dfs(1,0,0);
	n=1<<6;
	printf("{{0,0,0},{0,0,0}},\n");
	for (int i=1;i<n;i++)
	{
		if (Dis[i]==1)
		{
			putchar('{');
			putchar('{');
			Wr(g[i][0]);
			putchar('}');
			putchar(',');
			putchar('{');
			printf("0,0,0");
			putchar('}');
			putchar('}');
			putchar(',');
			putchar('\n');
		} else
		if (Dis[i]==2) 
		{
			putchar('{');
			putchar('{');
			Wr(g[i][0]);
			putchar('}');
			putchar(',');
			putchar('{');
			Wr(g[i][1]);
			putchar('}');
			putchar('}');
			putchar(',');
			putchar('\n');
		}
	}
	return 0;
}
//2018年 10月 23日 星期二 10:51:39 CST
```

代码
```cpp
/*
 * Author: ylx
 * Lang: c++
 * Prog: 1031E
 */
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void qmax(int &x,int y) {if (x<y) x=y;}
void qmin(int &x,int y) {if (x>y) x=y;}
inline int read()
{
	char s;
	int k=0,base=1;
	while ((s=getchar())!='-'&&s!=EOF&&!(isdigit(s)));
	if (s==EOF) exit(0);
	if (s=='-') base=-1,s=getchar();
	while (isdigit(s)) k=k*10+(s^'0'),s=getchar();
	return k*base;
}
inline void write(ll x)
{
	static char cnt,num[20];cnt=0;
	if (!x)
	{
		putchar('0');
		return;
	}
	for (;x;x/=10) num[++cnt]=x%10;
	for (;cnt;putchar(num[cnt--]+48));
}
const int g[64][2][3]=
{{{0,0,0},{0,0,0}},
{{6,5,4},{0,0,0}},
{{7,5,3},{0,0,0}},
{{7,6,5},{0,0,0}},
{{8,5,2},{0,0,0}},
{{8,6,4},{0,0,0}},
{{6,5,4},{8,7,6}},
{{8,7,6},{0,0,0}},
{{9,5,1},{0,0,0}},
{{9,6,3},{0,0,0}},
{{9,7,5},{0,0,0}},
{{6,5,4},{9,7,5}},
{{9,8,7},{7,5,3}},
{{7,6,5},{9,8,7}},
{{9,8,7},{0,0,0}},
{{6,5,4},{9,8,7}},
{{6,5,4},{10,6,2}},
{{10,6,2},{0,0,0}},
{{10,7,4},{0,0,0}},
{{6,5,4},{10,7,4}},
{{6,5,4},{10,8,6}},
{{10,8,6},{0,0,0}},
{{7,6,5},{10,8,6}},
{{7,5,3},{10,8,6}},
{{10,9,8},{8,5,2}},
{{10,9,8},{8,6,4}},
{{11,10,9},{11,7,3}},
{{8,7,6},{10,9,8}},
{{10,9,8},{0,0,0}},
{{6,5,4},{10,9,8}},
{{10,9,8},{7,5,3}},
{{7,6,5},{10,9,8}},
{{6,5,4},{11,6,1}},
{{11,6,1},{0,0,0}},
{{11,7,3},{0,0,0}},
{{6,5,4},{11,7,3}},
{{11,8,5},{0,0,0}},
{{6,5,4},{11,8,5}},
{{8,7,6},{11,6,1}},
{{7,6,5},{11,8,5}},
{{7,5,3},{11,9,7}},
{{7,6,5},{11,9,7}},
{{11,9,7},{0,0,0}},
{{6,5,4},{11,9,7}},
{{9,8,7},{11,7,3}},
{{8,7,6},{11,9,7}},
{{9,7,5},{11,8,5}},
{{9,8,7},{11,6,1}},
{{11,10,9},{9,5,1}},
{{11,10,9},{9,6,3}},
{{11,10,9},{9,7,5}},
{{10,7,4},{11,6,1}},
{{10,8,6},{11,6,1}},
{{11,8,5},{10,6,2}},
{{9,8,7},{11,10,9}},
{{10,8,6},{11,7,3}},
{{11,10,9},{0,0,0}},
{{6,5,4},{11,10,9}},
{{11,10,9},{7,5,3}},
{{7,6,5},{11,10,9}},
{{11,10,9},{8,5,2}},
{{10,9,8},{11,6,1}},
{{10,9,8},{11,7,3}},
{{8,7,6},{11,10,9}}};
const int maxm=1<<11;
const int maxn=1e5+100;
int a[25],n,m,cnt,z[40],u[40];
int b[maxn],S,sum;
vector<int> G;
void insert(int x,int y,int z)
{
	b[x]^=1,b[y]^=1,b[z]^=1;
	G.push_back(x);
	G.push_back(y);
	G.push_back(z);
}
void add(int x)
{
	int len=0;
	while (x)
	{
		z[++len]=x%2;
		x/=2;
	}
	for (int i=1;i<=len;i++) if (z[i]) G.push_back(i);
}
bool flag;
void dfs(int x,int cnt,int now)
{
	if (x==m+1)
	{
		if (now==S)
		{
			int s=0;
			for (int i=1;i<=m;i++) if (u[i]) s++;
			if (s+sum>n/3+12)
			{
				return;
			}
			for (int i=1;i<=m;i++) if (u[i]) add(a[i]);
			flag=true;
			return;
		}
		return;
	}
	u[x]=1;
	dfs(x+1,cnt+1,now^a[x]);
	u[x]=0;
	if (flag) return;
	dfs(x+1,cnt,now);
}
void work()
{
	while (a[m]*2<=(1<<cnt))
	{
		a[m+1]=a[m]*2;
		m++;
	}
}
int merge(int x,int y)
{
	int sum=0;
	for (int i=y;i>=x;i--) 
	{
		sum=(sum<<1)|b[i];
	}
	return sum;
}
void work1()
{
	m++;a[m]=7;work();
	if (21<(1<<cnt)) {m++;a[m]=21;work();}
	if (73<(1<<cnt)) {m++;a[m]=73;work();}
	if (273<(1<<cnt)) {m++;a[m]=273;work();}
	flag=false;
	S=merge(1,cnt);
	sum=G.size()/3;
	if (S) dfs(1,0,0); else flag=true;
	if (flag)
	{
		putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
		S=G.size()/3;
		printf("%d\n",S);
		for (int i=0;i<S;i++)
		{
			printf("%d %d %d\n",G[i*3],G[i*3+1],G[i*3+2]);
		}
	} else
	{
		putchar('N'),putchar('O'),putchar('\n');
	}
}
int main()
{
#ifdef ylx
	freopen("1031E.in","r",stdin);
	freopen("1031E.out","w",stdout);
#endif
	n=read();
	for (int i=1;i<=n;i++) b[i]=read();
	cnt=n;
	int x;
	if (n<8)
	{
		work1();
		return 0;
	}
	while (cnt>10)
	{
		if (cnt-6<8)
		{
			x=merge(cnt-6+1,cnt);
			if (g[x][0][0]!=0) insert(cnt-11+g[x][0][0],cnt-11+g[x][0][1],cnt-11+g[x][0][2]);
			if (g[x][1][0]!=0) insert(cnt-11+g[x][1][0],cnt-11+g[x][1][1],cnt-11+g[x][1][2]);
			cnt=8;
		} else
		{
			x=merge(cnt-6+1,cnt);
			if (g[x][0][0]!=0) insert(cnt-11+g[x][0][0],cnt-11+g[x][0][1],cnt-11+g[x][0][2]);
			if (g[x][1][0]!=0) insert(cnt-11+g[x][1][0],cnt-11+g[x][1][1],cnt-11+g[x][1][2]);
			cnt-=6;
		}
	}
	work1();
	return 0;
}
//2018年 10月 23日 星期二 10:51:39 CST
```


---

## 作者：_Arahc_ (赞：2)

## 题意

给定一个 01 串，每次操作可以选三个下标 $i,j,k$ 满足 $i<j<k,j-i=k-j$，然后将 $i,j,k$ 这三个位置 01 翻转。构造一个操作数不超过 $\left\lfloor\frac{n}{3}\right\rfloor+12$ 的方案，使原序列都是 0，或判定无解。

$n\leq 10^5$。

## 题解

考虑操作数 $\left\lfloor\frac{n}{3}\right\rfloor$ 的意义，即平均每次操作都要做到把三个数变成 0。最后留有 $12$ 个调整用的操作数。而观察打表不难发现，对于 $n\leq 10$ 的情况，可以用不超过 $12$ 步操作还原。也就是说，对于 $n>10$ 的情况，我们可以只管怎么用 $\left\lfloor\frac{n}{3}\right\rfloor$ 的操作数把前面的部分还原了，不需要管最后剩下的这 $10$ 个数。

最简单的肯定是三个一组地考虑（不妨设每组的开头一定是个 1，否则如果是 0，说明这个位置已经还原了，不需要管）：对于 `111` 的情况，将三个 1 一起反转即可。但是不是这种情况的组合，就无法用一次操作完成了。

三个一组无法完成的情况，考虑六个一组，能否用两次操作完成。答案是肯定的。

读到这里的话你应该就能去试试然后手玩六个一组的所有情况了 qwq。值得注意的是，由于六个或三个一组的所有情况我们都有办法应对，而最后 $10$ 个数字我们可以爆搜解决，因此在处理当前六个一组的时候，是可以操作修改后面的格子的，无需考虑影响，只要每个六个一组使用的操作次数不超过两次即可。

下面是六个一组的所有情况的一种可行方案（蓝色方框表示一次操作，红色斜正方形表示一次操作，紫色的表示两此操作都用到了这个位置）：

![一种方案](https://pic1.imgdb.cn/item/636b08f516f2c2beb17b7f28.png)

当然你可以整合其中类似的操作方案，不然分讨 24 种情况还是有点让人自闭的。

顺带提一句最后那些数字怎么办，你把状态全部记下来，把能通过一次操作转化的状态连边，跑一遍最短路即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool Begin;
const int max_n=100005,max_m=1000006,max_s=1052,inf=1000000000000015LL;
inline int read(){
    int x=0;bool w=0;char c=getchar();
    while(c<'0' || c>'9') w|=c=='-',c=getchar();
    while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
struct graph{
    int ct,hd[max_s],to[max_m<<1],nx[max_m<<1],ln[max_m<<1];
    graph(){ct=1;}
    inline void add(int u,int v,int w=0){
        nx[++ct]=hd[u],hd[u]=ct,to[ct]=v,ln[ct]=w;
    }
}e;

int n,a[max_n];

vector< tuple<int,int,int> > ans;

inline void Flip(int x,int y,int z){
    ans.emplace_back(x,y,z);
    a[x]^=1,a[y]^=1,a[z]^=1;
}

bool vis[max_s];
int dis[max_s],fr[max_s];
priority_queue< pair<int,int> > q;

inline void dijs(int st){
    memset(dis,0x3f,sizeof(dis));
    dis[st]=0;
    q.emplace(0,st);
    while(!q.empty()){
        int u=q.top().second;q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=e.hd[u];i;i=e.nx[i]){
            int v=e.to[i];
            if(dis[v]>dis[u]+1){
                dis[v]=dis[u]+1,fr[v]=u;
                q.emplace(-dis[v],v);
            }
        }
    }
}

inline void dfs(int S){
    if(S==0) return;
    int T=fr[S],x[3]={0,0,0};
    for(int i=0,j=0;i<10 && j<3;++i) if(((S>>i)&1)!=((T>>i)&1))
        x[j++]=i;
    ans.emplace_back(x[0]+n-9,x[1]+n-9,x[2]+n-9);
    dfs(T);
}

namespace SmallN{
    inline void dfs(int S){
        if(S==0) return;
        int T=fr[S],x[3]={0,0,0};
        for(int i=0,j=0;i<n && j<3;++i) if(((S>>i)&1)!=((T>>i)&1))
            x[j++]=i+1;
        ans.emplace_back(x[0],x[1],x[2]);
        dfs(T);
    }
    inline void main(){
        int N=(1<<n);
        for(int s=0;s<N;++s)
            for(int i=0;i<n;++i)
                for(int j=i+1;2*j-i<n;++j){
                    int x=i,y=j,z=2*j-i;
                    e.add(s,s^(1<<x)^(1<<y)^(1<<z));
                }
        dijs(0);
        int s=0;
        for(int i=1,j=0;i<=n;++i,++j)
            s|=(a[i]<<j);
        if(dis[s]>inf) return void(puts("NO"));
        dfs(s);
        puts("YES");
        write(ans.size()),putchar('\n');
        for(auto p:ans){
            write(get<0>(p)),putchar(' ');
            write(get<1>(p)),putchar(' ');
            write(get<2>(p)),putchar('\n');
        }
    }
}

bool End;
#define File ""
signed main(){
    // #ifndef ONLINE_JUDGE
    // freopen(File ".in","r",stdin);
    // freopen(File ".out","w",stdout);
    // #endif
    // cerr<<"Memory : "<<(&Begin-&End)/1024.0/1024<<"\n";
    n=read();
    for(int i=1;i<=n;++i)
        a[i]=read();
    if(n<=10) return SmallN::main(),0;
    for(int s=0;s<1024;++s)
        for(int i=0;i<10;++i)
            for(int j=i+1;2*j-i<10;++j){
                int x=i,y=j,z=2*j-i;
                e.add(s,s^(1<<x)^(1<<y)^(1<<z));
            }
    dijs(0);
    for(int i=1;i<=n-10;++i) if(a[i]){
        if(a[i+1] && a[i+2]){
            Flip(i,i+1,i+2);
            continue;
        }
        if(!a[i+1] && !a[i+2]){
            if(!a[i+3] && !a[i+4] && !a[i+5]){
                Flip(i,i+2,i+4),
                Flip(i+2,i+4,i+6);
                continue;
            }
            for(int j=3;j<=5;++j) if(a[i+j]){
                Flip(i,i+j,i+j+j);
                break;
            }
            continue;
        }
        if(!a[i+1]){
            Flip(i,i+2,i+4);
            continue;
        }
        else{
            if(!a[i+3] && !a[i+4] && !a[i+5]){
                Flip(i+1,i+4,i+7),
                Flip(i,i+4,i+8);
                continue;
            }
            if(a[i+3] && a[i+4] && a[i+5]){
                Flip(i+1,i+3,i+5),
                Flip(i,i+4,i+8);
                continue;
            }
            if(a[i+3] && a[i+4]){
                Flip(i+1,i+2,i+3),
                Flip(i,i+2,i+4);
                continue;
            }
            if(a[i+3] && a[i+5]){
                Flip(i,i+3,i+6),
                Flip(i+1,i+5,i+9);
                continue;
            }
            if(a[i+4] && a[i+5]){
                Flip(i,i+4,i+8),
                Flip(i+1,i+5,i+9);
                continue;
            }
            Flip(i,i+1,i+2);
            for(int j=3;j<=5;++j) if(a[i+j]){
                Flip(i+2,i+j,i+2*j-2);
                break;
            }
            continue;
        }
    }
    int s=0;
    for(int i=n-9,j=0;i<=n;++i,++j)
        s|=(a[i]<<j);
    if(dis[s]>inf) return puts("NO"),0;
    dfs(s);
    puts("YES");
    write(ans.size()),putchar('\n');
    for(auto p:ans){
        write(get<0>(p)),putchar(' ');
        write(get<1>(p)),putchar(' ');
        write(get<2>(p)),putchar('\n');
    }
    return 0;
}
```



---

## 作者：happybob (赞：0)

限制很紧，肯定是希望每次至少能删 $3$ 个 $1$，最后剩下的 $12$ 可以爆搜调整。

$3$ 个一组不能一次删完，但是暴搜可以发现每 $6$ 个一组在忽略后面的数时可以 $2$ 次删完，于是前面分组做最后剩下若干个爆搜即可。

---

