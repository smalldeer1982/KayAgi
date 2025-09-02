# [ABC164F] I hate Matrix Construction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc164/tasks/abc164_f

整数 $ N $ 及び長さ $ N $ の配列 $ S $, $ T $, $ U $, $ V $ が与えられます。 以下の条件を満たすような $ N×N $ の行列 $ a $ をどれか $ 1 $ つ構築してください。

- $ a_{i,j} $ は整数である。
- $ 0\ \leq\ a_{i,j}\ \lt\ 2^{64} $
- $ S_{i}\ =\ 0 $ のとき $ i $ 行目の要素のビットごとの論理積は $ U_{i} $ である。
- $ S_{i}\ =\ 1 $ のとき $ i $ 行目の要素のビットごとの論理和は $ U_{i} $ である。
- $ T_{i}\ =\ 0 $ のとき $ i $ 列目の要素のビットごとの論理積は $ V_{i} $ である。
- $ T_{i}\ =\ 1 $ のとき $ i $ 列目の要素のビットごとの論理和は $ V_{i} $ である。

ただし、条件を満たす行列が存在しない場合もあるかもしれません。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 500 $
- $ 0\ \leq\ S_{i}\ \leq\ 1 $
- $ 0\ \leq\ T_{i}\ \leq\ 1 $
- $ 0\ \leq\ U_{i}\ \lt\ 2^{64} $
- $ 0\ \leq\ V_{i}\ \lt\ 2^{64} $

### Sample Explanation 1

入力例 $ 1 $ では - $ 1 $ 行目の要素のビットごとの論理積が $ 1 $ - $ 2 $ 行目の要素のビットごとの論理和が $ 1 $ - $ 1 $ 列目の要素のビットごとの論理和が $ 1 $ - $ 2 $ 列目の要素のビットごとの論理積が $ 0 $ の条件を満たす行列を見つける必要があります。

## 样例 #1

### 输入

```
2
0 1
1 0
1 1
1 0```

### 输出

```
1 1
1 0```

## 样例 #2

### 输入

```
2
1 1
1 0
15 15
15 11```

### 输出

```
15 11
15 11```

# 题解

## 作者：Loser_King (赞：4)

算是 AT 里码量比较大的题了。（码量接近 2k，虽然感觉不算难，这个难度 2683 是因为赛时都调不完么）

这道题做完以后我也 hate Matrix Construction 了。

## 题意

试构造一个 $n\times n$ 的矩阵满足以下 $2n$ 个限制条件：

- 对于每一行 $i$ /列 $j$，满足其 $n$ 个元素的按位 $\operatorname{and}$ **或者**按位 $\operatorname{or}$ 为给定值 $s_i/t_j$。
  

## 做法

本题做法很多，说一个我想到的。

容易发现答案所有二进制位互不影响，于是把每一位都拆开处理。

此时可以发现限制只有 4 种情况：

1. 当前行/列所有数按位 $\operatorname{and}$ 为 $1$。
  
2. 当前行/列所有数按位 $\operatorname{and}$ 为 $0$。
  
3. 当前行/列所有数按位 $\operatorname{or}$ 为 $1$。
  
4. 当前行/列所有数按位 $\operatorname{or}$ 为 $0$。
  

限制 1 和限制 4 可以确定该行/列所有数，直接填上即可。（1）

如果出现冲突直接输出 `-1`。所以之后需要处理的只有两种限制。

这两种限制都只要当前行/列有一个特定值即可。

如果当前矩阵中存在一格，满足其横纵格子的限制`相同`，则直接填上这种限制对应的数。不难发现这样填一定不劣。（2）

这一步处理完以后，剩下的情况就只有行列未满足的限制完全不同的情况了。

这种情况下我们可以选择像棋盘染色一样 0/1 交替着填，这样也一定不劣。（3/1）

只有当只有一行或者一列的时候可能出现无解的情况，其他用这种填法都可以解决。

剩下如果还有没填的格子，此时所有的限制已经满足，可以随便填。（3/2）

最后综合 64 位结果输出即可。

## 代码

代码里用 $a_{i,j}$ 存储当前状态，$-1/0/1$ 表示没填过，填了 $0$，填了 $1$。

$idx_i$ 和 $idy_j$ 表示当前未满足条件的行/列的标号，用于黑白染色。

upd 和 check 函数用于覆盖和检查矩阵状态。

代码里的标记对应题解里的标记。

AT 目前 cpp 最短解。

```c++
//AT4850[ABC164F] AC Code
//written by Loser_King(159686)
//5.59s(394ms) / 1692B
#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define ERROR cout<<"-1\n",exit(0)
using namespace std;
int const N=505;
typedef unsigned long long ull;
int n,a[N][N],s[N],t[N],p[N],q[N],idx[N],idy[N];
ull b[N][N],u[N],v[N];
void upd(int ax,int ay,int bx,int by,int k){
    FOR(x,ax,bx)FOR(y,ay,by){
        if(~a[x][y]&&a[x][y]^k)ERROR;
        a[x][y]=k;
    }
}
int check(int ax,int ay,int bx,int by,int op,int k){
    int v1=0,v2=1,flg=0;
    FOR(x,ax,bx)FOR(y,ay,by)
        if(~a[x][y])
            v1|=a[x][y],v2&=a[x][y],flg=1;
    return (op?v1:v2)==k&&flg;
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    FOR(i,1,n)cin>>s[i];
    FOR(i,1,n)cin>>t[i];
    FOR(i,1,n)cin>>u[i];
    FOR(i,1,n)cin>>v[i];//input
    FOR(k,0,63){
        memset(a,-1,sizeof a);
        memset(idx,0,sizeof idx);
        memset(idy,0,sizeof idy);
        FOR(i,1,n)p[i]=u[i]>>k&1,q[i]=v[i]>>k&1;//init

        FOR(i,1,n)if(s[i]^p[i])upd(i,1,i,n,p[i]);
        FOR(i,1,n)if(t[i]^q[i])upd(1,i,n,i,q[i]);//part 1

        FOR(x,1,n)FOR(y,1,n)
            if(s[x]==p[x]&&t[y]==q[y]&&s[x]==t[y])
                upd(x,y,x,y,s[x]);//part 2

        int tx=0,ty=0;
        FOR(i,1,n)if(!check(i,1,i,n,s[i],p[i]))idx[i]=++tx;
        FOR(i,1,n)if(!check(1,i,n,i,t[i],q[i]))idy[i]=++ty;
        if(tx||ty){
            FOR(x,1,n)FOR(y,1,n)
                if(!~a[x][y]){
                    if(idx[x]&&idy[y])
                        upd(x,y,x,y,idx[x]+idy[y]&1);
                    else if(idx[x])
                        upd(x,y,x,y,s[x]);
                    else
                        upd(x,y,x,y,t[y]);
                }//part 3(1)
        }else{
            FOR(x,1,n)FOR(y,1,n)
                if(!~a[x][y])
                    upd(x,y,x,y,0);//part 3(2) 
        }

        int flg=1;
        FOR(i,1,n)flg&=check(i,1,i,n,s[i],p[i])&&check(1,i,n,i,t[i],q[i]);
        if(!flg)ERROR;//part 3(1) 

        FOR(x,1,n)FOR(y,1,n)
            b[x][y]|=(ull)a[x][y]<<k;
    }
    for(int x=1;x<=n;x++,cout<<"\n")
        FOR(y,1,n)
            cout<<b[x][y]<<" ";//output
}
```

---

## 作者：shinkuu (赞：2)

**重要难点之一：unsigned long long。**

首先每一位之间独立，拆位变成 $0/1$ 情况问题。

然后先处理按位与 $=1$ 和 按位或 $=0$ 的情况。显然整一行/列都是同一个数。

接着处理剩下的。对于每一行/列，先判断现在已填的数符不符合要求，没有则找有没有和它要求一样的列/行，有则直接在对应位置填数，否则尽量使全部数不填在同一行/列即可，这一部分可以用一个类似双指针的操作完成。

最后再整个检查一遍判断无解。

实现是难点。个人建议可以多使用模块化编程并使用一些有意义的函数名，以此方便调试。

思路很简单，实现也不难。不算缺省源大概 3kb。其中有一半基本是重复的。

code：

```cpp
int n,op1[N],op2[N],f[N][N];
ull e[N],d[N],ans[N][N];
int pd1[N],pd2[N];
bool vis[N][N];
bool check(){
	rep(i,1,n){
		if(!op1[i]){
			int x=1;
			rep(j,1,n){
				x&=f[i][j];
			}
			if(x!=(e[i]&1))
				return false;
		}else{
			int x=0;
			rep(j,1,n){
				x|=f[i][j];
			}
			if(x!=(e[i]&1))
				return false;
		}
	}
	rep(j,1,n){
		if(!op2[j]){
			int x=1;
			rep(i,1,n){
				x&=f[i][j];
			}
			if(x!=(d[j]&1))
				return false;
		}else{
			int x=0;
			rep(i,1,n){
				x|=f[i][j];
			}
			if(x!=(d[j]&1))
				return false;
		}
	}
	return true;
}
void opAll1(){
	rep(i,1,n){
		int x=e[i]&1;
		if(op1[i]^x){
			rep(j,1,n){
				f[i][j]=x;
				vis[i][j]=true;
			}
		}else 
			pd1[i]=x;
	}
}
void opAll2(){
	rep(j,1,n){
		int x=d[j]&1;
		if(op2[j]^x){
			rep(i,1,n){
				f[i][j]=x;
				vis[i][j]=true;
			}
		}else 
			pd2[j]=x;
	}
}
bool findSat1(int i){
	int x=e[i]&1;
	rep(j,1,n){
		int y=d[j]&1;
		if(!vis[i][j]&&x==y){
			vis[i][j]=true;
			f[i][j]=x;
			return true;
		}
	}
	return false;
}
bool findSat2(int j){
	int x=d[j]&1;
	rep(i,1,n){
		int y=e[i]&1;
		if(!vis[i][j]&&x==y){
			vis[i][j]=true;
			f[i][j]=x;
			return true;
		}
	}
	return false;
}
int findLine1(int s,int i){
	int x=e[i]&1;
	rep(j,s+1,n){
		if(!vis[i][j]){
			vis[i][j]=true;
			f[i][j]=x;
			return j;
		}
	}
	return 0;
}
int findLine2(int s,int j){
	int x=d[j]&1;
	rep(i,s+1,n){
		if(!vis[i][j]){
			vis[i][j]=true;
			f[i][j]=x;
			return i;
		}
	}
	return 0;
}
bool checkLine1(int i,int x){
	rep(j,1,n){
		if(vis[i][j]&&f[i][j]==x)
			return true;
	}
	return false;
}
bool checkLine2(int j,int x){
	rep(i,1,n){
		if(vis[i][j]&&f[i][j]==x)
			return true;
	}
	return false;
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%d",&op1[i]);
	}
	rep(i,1,n){
		scanf("%d",&op2[i]);
	}
	rep(i,1,n){
		scanf("%llu",&e[i]);
	}
	rep(i,1,n){
		scanf("%llu",&d[i]);
	}
	ll base=1;
	rep(k,0,63){
		mems(vis,false),mems(f,0);
		mems(pd1,-1),mems(pd2,-1);
		opAll1(),opAll2();
		int lst=0;
		rep(i,1,n){
			int x=e[i]&1;
			if(op1[i]^x||checkLine1(i,x))
				continue;
			if(findSat1(i))
				continue;
			if(lst=findLine1(lst,i))
				continue;
			lst=findLine1(lst,i);
		}
		rep(j,1,n){
			int x=d[j]&1;
			if(op2[j]^x||checkLine2(j,x))
				continue;
			if(findSat2(j))
				continue;
			if(lst=findLine2(lst,j))
				continue;
			lst=findLine2(lst,j);
		}
		if(!check()){
			puts("-1");
			return;
		}
		rep(i,1,n){
			e[i]>>=1;
			d[i]>>=1;
			rep(j,1,n){
				ans[i][j]+=f[i][j]*base;
			}
		}
		base<<=1;
	}
	rep(i,1,n){
		rep(j,1,n){
			printf("%llu ",ans[i][j]);
		}
		puts("");
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Scarlet_Hypoc (赞：2)

提供一个比较简单的做法。

显然这类位运算题每一位是不相关的，将这 $64$ 位拆开考虑。

如果某一行要求 `与为1` 或 `或为0`，那么这一行/列就必须全都是1/0，这个可以先确定好（如果出现冲突，就无解），剩下的没确定的位置暂时放 $-1$。

然后考虑 `与为0` 和 `或为1` 的行列，这等价于：这一行/列至少有一个 $0/1$，把每一个限制记录下来，并且记录那一行/列有多少个 $-1$。

考虑每次找到 $-1$ 数量最少的行/列，然后随便将上面的一个 $-1$ 改成需要的数字即可，不难证明这个贪心是对的。

一定要证明的话，先考虑什么时候无解：限制中 $-1$ 数量最少的行/列中，$-1$ 的数量为 $0$。

然后分两种情况讨论：
1. 假如这个 $-1$ 数量最少的行/列，只有 $1$ 个 $-1$，那么要满足这行/列的限制，就必须往这唯一的一个位置放需要的数字，这是没得选择的。
2. 否则，如果 $-1$ 数量 $>1$，这意味着剩下的所有限制所在的行/列 $-1$ 数量都 $>1$，那么我们随便将一个位置从 $-1$ 变成需要的数字，剩下的限制中至多有一个行/列的 $-1$ 数量会变成 $1$，下面的操作就是不断操作这个 `只有1个-1的行/列`，这样操作下去是显然会找到一种合法方案的（即一定不会出现无解）。

由于需要找数量最少的，所以需要一个数据结构来维护（即`set`），所以时间复杂度稍劣一些：$O(64n^2\log n)$，但事实上好写的同时跑得飞快。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 510

int n,S[maxn],T[maxn];
unsigned long long A[maxn],B[maxn],ans[maxn][maxn];
struct par{
	int type,x,num,res;
	//type=0/1表示是行还是列，x表示行/列编号
	//num表示至少需要出现一次的数字，res表示剩下的-1数量
	bool operator <(const par &B)const
		{return res==B.res?x==B.x?type==B.type?num<B.num:type<B.type:x<B.x:res<B.res;}
};
void solve(int bt){
	static int a[maxn][maxn],line[maxn],col[maxn];
	memset(a,-1,sizeof(a));
	for(int i=1;i<=n;i++)line[i]=col[i]=n;
	auto set_a=[&](int x,int y,int z){
		if(a[x][y]!=-1 && a[x][y]!=z){puts("-1");exit(0);}
		else if(a[x][y]==-1)a[x][y]=z,line[x]--,col[y]--;
	};
	for(int i=1;i<=n;i++){
		if(S[i]!=(A[i]>>bt&1))
			for(int j=1;j<=n;j++)set_a(i,j,!S[i]);
		if(T[i]!=(B[i]>>bt&1))
			for(int j=1;j<=n;j++)set_a(j,i,!T[i]);
	}
	set<par> s;
	for(int i=1;i<=n;i++){
		if(S[i]==(A[i]>>bt&1)){
			bool tf=false;
			for(int j=1;j<=n;j++)if(a[i][j]==S[i]){tf=true;break;}
			if(!tf)s.insert((par){0,i,S[i],line[i]});
		}
		if(T[i]==(B[i]>>bt&1)){
			bool tf=false;
			for(int j=1;j<=n;j++)if(a[j][i]==T[i]){tf=true;break;}
			if(!tf)s.insert((par){1,i,T[i],col[i]});
		}
	}
	#define check if(s.count(c))s.erase(c);else{c.num^=1;if(s.count(c))s.erase(c),c.res--,s.insert(c);}
	//check是看，这行/列放了这个数字后，是否恰好满足了这列/行的限制，如果是就去除这个限制
	while(s.size()){
		par X=*s.begin();s.erase(X);
		if(!X.res){puts("-1"),exit(0);}
		if(!X.type){
			for(int i=1;i<=n;i++)if(a[X.x][i]==-1){
				par c=(par){1,i,X.num,col[i]}; check;
				set_a(X.x,i,X.num); break;
			}
		}else{
			for(int i=1;i<=n;i++)if(a[i][X.x]==-1){
				par c=(par){0,i,X.num,line[i]}; check;
				set_a(i,X.x,X.num); break;
			}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]==1)ans[i][j]|=1ull<<bt;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>S[i];
	for(int i=1;i<=n;i++)cin>>T[i];
	for(int i=1;i<=n;i++)cin>>A[i];
	for(int i=1;i<=n;i++)cin>>B[i];
	for(int i=0;i<64;i++)solve(i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			cout<<ans[i][j]<<' ';
		cout<<"\n";
	}
}
```

---

## 作者：_Yonder_ (赞：1)

我能切紫的构造题？真的假的。

先拆位，把按位与为 $1$，按位或为 $0$ 的处理了，不难发现剩下的图大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/7vjd1v29.png)

其中黑色部分表示该位置填了数字。

然后把黑色部分去掉，剩下的白色部分合在一起，形成一个矩形：

![](https://cdn.luogu.com.cn/upload/image_hosting/az2uhqto.png)

假设这里是 $n$ 行 $m$ 列。

当 $n>1,m>1$，我们只需要 $0,1$ 交替的填即可（棋盘染色）。

当 $n=1$，我们优先处理列，若当前列已满足要求，则把行的处理了。

当 $m=1$，就是把 $n=1$ 的反着来。

最后判断合法（因为 $n=0$ 可能会出现些问题），累加答案即可。

---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4850) & [AtCoder题目页面传送门](https://atcoder.jp/contests/abc164/tasks/abc164_f)

>给定整数$n$和$4$个长度为$n$的序列$a,b,c,d$，其中$a_i,b_i\in\{0,1\}$。要求构造一个$n\times n$的矩阵，满足以下条件：
>- $\forall i\in[1,n]$，如果$a_i=0$，则第$i$行的与和为$c_i$；否则或和为$c_i$；
>- $\forall i\in[1,n]$，如果$b_i=0$，则第$i$列的与和为$d_i$；否则或和为$d_i$。

>或报告无解。

>$n\in[1,500],c_i,d_i\in\left[0,2^{64}\right)$。

这是一个炒鸡毒瘤的分类讨论大题……

首先不难想到的是，各二进制位之间是独立的，不妨拆成$64$位，每位分别处理，最终合并答案。若有任意一位无解，那么最终无解。于是拆成的每个问题中的与和、或和限制都$\in\{0,1\}$了。我们继续沿用字母$a,b,c,d$表示，此时$c_i,d_i\in\{0,1\}$。

接下来考虑怎么处理每个拆成的问题。

显然，每行、每列分别有且仅有一个限制，而且都可以转化为更能直观理解的形式们之一：

1. $a_i/b_i=0,c_i/d_i=1$：第$i$行/列全是$1$；
1. $a_i/b_i=0,c_i/d_i=0$：第$i$行/列至少有一个$0$；
1. $a_i/b_i=1,c_i/d_i=1$：第$i$行/列至少有一个$1$。
1. $a_i/b_i=1,c_i/d_i=0$：第$i$行/列全是$0$；

其中限制$1,4$是“$\forall$限制”，限制$2,3$是“$\exists$限制”。

直接暴力分类讨论。

1. 行、列都存在$\forall$限制：此时显然只能有一种$\forall$限制，否则一定会发生冲突，无解。现在假设只有一种$\forall$限制，那么很容易想到的方案是将所有$\forall$限制填上之后，剩下的格子都填相反的数，这样每行/列要么是$\forall$限制，已满足；要么是$\exists$限制，按照填法此行/列显然一定$0,1$都有，一定满足；
1. 只有行存在$\forall$限制：
   1. 限制$1,4$都存在：容易想到，将所有$\forall$限制都填满，将所有行的$\exists$限制都随便填使得满足，完全没必要在意列的限制，因为这样显然每列一定$0,1$都有，能够满足所有列的$\exists$限制；
   1. $\forall$限制只存在限制$1$：先把所有限制$1$填满再说。现在我们要满足的就是行、列限制$2,3$。其中列限制$3$显然已经全部满足，难点在于列限制$2$。有以下几种情况：
      1. 没有列限制$2$：那么直接把行限制们随便满足一下即可；
      1. 存在行限制$2$：把任一一个行限制$2$填满$0$，此时显然所有列都有$0$了，所以所有列限制$2$都满足了，于是把其他行限制们随便满足一下即可；
      1. 至少存在$2$个行限制$3$：把其中任意$2$个行限制$3$都$1$格填$1$、其他格填$0$，使得填$1$的位置错开，这样也能实现每列都有$0$，剩下的跟情况$2.2.2$类似；
      1. 存在行限制$3$且至多有$n-1$个列限制$2$：将任意一个行限制$3$ $1$格填$1$、其他格填$0$，使得填$1$的位置所在列没有列限制$2$，这样也能满足所有列限制$2$，于是~~再次地~~把其他行限制们随便满足一下即可；
      1. 情况$2.2.1\sim2.2.4$都不满足：无能为力，无解；
   1. $\forall$限制只存在限制$4$：与情况$2.2$类似；
1. 只有列存在$\forall$限制：与情况$2$类似；
1. 不存在$\forall$限制：
   1. $n=1$：有可能无解，乱搞即可；
   1. $n>1$：一定有解，一种可行的方案是：为每行/列挑选一个代表来满足此行/列的限制，第$i$行的代表是$\begin{cases}(i,2)&i=1\\(i,1)&i>1\end{cases}$，第$i$列的代表是$\begin{cases}(1,i)&i=1\\(2,i)&i>1\end{cases}$，这样可以保证代表们两两不重合。
   
时间复杂度$\mathrm O\!\left(n^2\right)$，乘上常数$64$。
   
**The end.**

下面是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
typedef unsigned long long ull;
const int N=500;
int n;
bool a[N+1],b[N+1];
ull c[N+1],d[N+1];
ull ans[N+1][N+1];
void sol(int x){
//	cout<<x<<"\n";
	vector<int> r0,ro0,r1,ro1,c0,co0,c1,co1;//行限制4,2,1,3、列限制4,2,1,3 
	for(int i=1;i<=n;i++){//预处理8个vector 
		if(!a[i]&&!(c[i]&1ull<<x))ro0.pb(i);
		else if(!a[i]&&c[i]&1ull<<x)r1.pb(i);
		else if(a[i]&&!(c[i]&1ull<<x))r0.pb(i);
		else ro1.pb(i);
		if(!b[i]&&!(d[i]&1ull<<x))co0.pb(i); 
		else if(!b[i]&&d[i]&1ull<<x)c1.pb(i);
		else if(b[i]&&!(d[i]&1ull<<x))c0.pb(i);
		else co1.pb(i);
	}
	if((r0.size()||r1.size())&&(c0.size()||c1.size()))//1 
		if(r0.size()&&!r1.size()&&c0.size()&&!c1.size()){
			for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans[i][j]|=1ull<<x;
			for(int i=0;i<r0.size();i++)for(int j=1;j<=n;j++)(ans[r0[i]][j]|=1ull<<x)^=1ull<<x;
			for(int j=0;j<c0.size();j++)for(int i=1;i<=n;i++)(ans[i][c0[j]]|=1ull<<x)^=1ull<<x;
		}
		else if(!r0.size()&&r1.size()&&!c0.size()&&c1.size()){
			for(int i=0;i<r1.size();i++)for(int j=1;j<=n;j++)ans[r1[i]][j]|=1ull<<x;
			for(int j=0;j<c1.size();j++)for(int i=1;i<=n;i++)ans[i][c1[j]]|=1ull<<x;
		}
		else puts("-1"),exit(0);
	else if(r0.size()||r1.size())//2
		if(r0.size()&&r1.size()){//2.1
			for(int i=0;i<r1.size();i++)for(int j=1;j<=n;j++)ans[r1[i]][j]|=1ull<<x;
			for(int i=0;i<ro1.size();i++)ans[ro1[i]][1]|=1ull<<x;
		}
		else if(r0.size())//2.2
			if(!co1.size()||ro1.size())//2.2.1&2.2.2
				for(int i=0;i<ro1.size();i++)for(int j=1;j<=n;j++)ans[ro1[i]][j]|=1ull<<x;
			else if(ro0.size()>=2){//2.2.3
				for(int j=2;j<=n;j++)ans[ro0[0]][j]|=1ull<<x;
				for(int j=1;j<n;j++)ans[ro0[1]][j]|=1ull<<x;
			}
			else if(co1.size()<n&&ro0.size()==1){//2.2.4
				int notin=1,now=0;
				while(now<co1.size()&&co1[now]==notin)notin++,now++;
				for(int j=1;j<=n;j++)if(j!=notin)ans[ro0[0]][j]|=1ull<<x;
			}
			else puts("-1"),exit(0);//2.2.5
		else{//2.3
			for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans[i][j]|=1ull<<x;
			if(!co0.size()||ro0.size())
				for(int i=0;i<ro0.size();i++)for(int j=1;j<=n;j++)ans[ro0[i]][j]^=1ull<<x;
			else if(ro1.size()>=2){
				for(int j=2;j<=n;j++)ans[ro1[0]][j]^=1ull<<x;
				for(int j=1;j<n;j++)ans[ro1[1]][j]^=1ull<<x;
			}
			else if(co0.size()<n&&ro1.size()==1){
				int notin=1,now=0;
				while(now<co0.size()&&co0[now]==notin)notin++,now++;
				for(int j=1;j<=n;j++)if(j!=notin)ans[ro1[0]][j]^=1ull<<x;
			}
			else puts("-1"),exit(0);
		}
	else if(c0.size()||c1.size())//3
		if(c0.size()&&c1.size()){
			for(int j=0;j<c1.size();j++)for(int i=1;i<=n;i++)ans[i][c1[j]]|=1ull<<x;
			for(int j=0;j<co1.size();j++)ans[1][co1[j]]|=1ull<<x;
		}
		else if(c0.size())
			if(!ro1.size()||co1.size())
				for(int j=0;j<co1.size();j++)for(int i=1;i<=n;i++)ans[i][co1[j]]|=1ull<<x;
			else if(co0.size()>=2){
				for(int i=2;i<=n;i++)ans[i][co0[0]]|=1ull<<x;
				for(int i=1;i<n;i++)ans[i][co0[1]]|=1ull<<x;
			}
			else if(ro1.size()<n&&co0.size()==1){
				int notin=1,now=0;
				while(now<ro1.size()&&ro1[now]==notin)notin++,now++;
				for(int i=1;i<=n;i++)if(i!=notin)ans[i][co0[0]]|=1ull<<x;
			}
			else puts("-1"),exit(0);
		else{
			for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans[i][j]|=1ull<<x;
			if(!ro0.size()||co0.size())
				for(int j=0;j<co0.size();j++)for(int i=1;i<=n;i++)ans[i][co0[j]]^=1ull<<x;
			else if(co1.size()>=2){
				for(int i=2;i<=n;i++)ans[i][co1[0]]^=1ull<<x;
				for(int i=1;i<n;i++)ans[i][co1[1]]^=1ull<<x;
			}
			else if(ro0.size()<n&&co1.size()==1){
				int notin=1,now=0;
				while(now<ro0.size()&&ro0[now]==notin)notin++,now++;
				for(int i=1;i<=n;i++)if(i!=notin)ans[i][co1[0]]^=1ull<<x;
			}
			else puts("-1"),exit(0);
		}
	else//4
		if(n==1)//4.1
			if(ro0.size()&&co0.size());
			else if(ro1.size()&&co1.size())ans[1][1]|=1ull<<x;
			else puts("-1"),exit(0);
		else{//4.2
			for(int i=0;i<ro1.size();i++)ans[ro1[i]][ro1[i]==1?2:1]|=1ull<<x;
			for(int j=0;j<co1.size();j++)ans[co1[j]==1?1:2][co1[j]]|=1ull<<x;
		}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++)cin>>d[i];
	for(int i=0;i<64;i++)sol(i);//拆位分别处理 
	for(int i=1;i<=n;i++){for(int j=1;j<=n;j++)cout<<ans[i][j]<<" ";puts("");}
	return 0;
}
```

---

