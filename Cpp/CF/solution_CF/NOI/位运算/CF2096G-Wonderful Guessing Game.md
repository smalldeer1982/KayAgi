# Wonderful Guessing Game

## 题目描述

这是一道交互题。

你是千年科学学校的一名自豪的教师。今天，一名叫 Alice 的学生向你发起了一个猜数游戏的挑战。

Alice 心中想着一个 $1$ 到 $n$ 之间的整数，你必须通过向她提出一些查询来猜出这个数。

为了增加难度，她要求你必须先提出所有查询，而她将忽略其中的恰好 $1$ 个查询。

对于每个查询，你需要选择一个由 $1$ 到 $n$ 之间的 $k$ 个不同整数组成的数组，其中 $k$ 是偶数。然后，Alice 会给出以下回应之一：

- $\texttt{L}$：这个数位于数组的前 $\frac{k}{2}$ 个元素中；
- $\texttt{R}$：这个数位于数组的后 $\frac{k}{2}$ 个元素中；
- $\texttt{N}$：这个数不在数组中；
- $\texttt{?}$：这个查询被忽略。

Alice 很没耐心，因此你必须找到一种策略，使得查询次数最少。你能做到吗？

形式化地说，设 $f(n)$ 为确定 Alice 的数字所需的最小查询次数。你需要找到一种恰好使用 $f(n)$ 次查询的策略。

注意，交互器是自适应的，这意味着 Alice 的数字并非一开始就固定，可能会根据你的查询而变化。然而，保证至少存在一个数字与 Alice 的回应一致。

我们可以证明，对于所有满足 $2 \le n \le 2 \cdot 10^5$ 的 $n$，$f(n) \leq 20$。

## 说明/提示

在第一个测试用例中，$n = 3$。我们提出了 $2$ 次查询：$[1, 2]$ 和再次的 $[1, 2]$。

- 对于第一次查询，Alice 的回应是 $\texttt{?}$，表示这次查询被忽略。
- 对于第二次查询，Alice 的回应是 $\texttt{N}$，表示她的数字不在数组 $[1, 2]$ 中。

根据以上信息，我们可以确定 Alice 的数字是 $3$。

可以证明，对于 $n = 3$，所有有效策略至少需要 $2$ 次查询。

在第二个测试用例中，$n = 5$。我们提出了 $3$ 次查询：$[3, 2, 4, 1]$、$[5, 4, 3, 1]$ 和 $[1, 5, 3, 4]$。

- 对于第一次查询，Alice 的回应是 $\texttt{R}$，表示她的数字在数组 $[4, 1]$ 中。
- 对于第二次查询，Alice 的回应是 $\texttt{?}$，表示这次查询被忽略。
- 对于第三次查询，Alice 的回应是 $\texttt{L}$，表示她的数字在数组 $[1, 5]$ 中。

根据以上信息，我们可以确定 Alice 的数字是 $1$。

可以证明，对于 $n = 5$，所有有效策略至少需要 $3$ 次查询。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
3



?N

5




R?L```

### 输出

```
2
2 1 2
2 1 2

3

3
4 3 2 4 1
4 5 4 3 1
4 1 5 3 4

1```

# 题解

## 作者：maxiaomeng (赞：2)

## 分析

我们先不考虑必须先提出所有查询和忽略一个询问这两个条件。

这样一来，题目和小学数学中的找假币问题十分相似。

因此我们可以用类似的做法做：

- 将 $n$ 个数平均分成 $3$ 个区间，从左到右记为 $0$、$1$、$2$ 号区间。

- 如果余下 $1$ 个数，就把这个数归到 $2$ 号区间。例如：$7$ 个数分为 $[1,2]$，$[3,4]$，$[5,7]$ 三个区间。

- 如果余下 $2$ 个数，假设除去两个数后区间长度除以 $3$ 为 $len$，那么划分成：$[1, len]$，$[len+1,2len+1]$，$[2len+2,3len+2]$。例如：$8$ 个数分为 $[1,2]$，$[3,5]$，$[6,8]$ 三个区间。

- 再对 $0$ 和 $1$ 拼起来两个区间进行查询，结果为 `L` 则在 $0$ 号区间，为 `R` 则在 $1$ 号区间，为 `N` 则在 $2$ 号区间。再在对应区间递归询问。

这样子总共 $\lceil \log_3 n\rceil$ 次查询，可以证明这是最小查询次数。

接下来我们考虑加入必须先提出所有查询这个条件。

我们可以根据上面解法，先建出的决策树。每个结点是一个区间，对于结点 $x$ 的区间划分出的 $0$ 号区间，新建一个代表该区间的结点并向它连一条边权为 $0$ 的边，对于结点 $x$ 的区间划分出的 $1$ 号区间，新建一个代表该区间的结点并向它连一条边权为 $1$ 的边，以此类推。

当一个结点区间长度为 $1$ 却没到最大深度（即 $\lceil \log_3 n\rceil$）时，钦定它有一个 $2$ 号区间，这个区间就是它自己。

![](https://cdn.luogu.com.cn/upload/image_hosting/1pv96k89.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/kk01hvad.png)

每一次询问，将每一层的所有 $0$ 区间结点合在一起，$1$、$2$ 号区间也是一样。然后对于每一层，将结合后的 $0$ 区间和结合后的 $1$ 区间拼在一起，询问这个东西。如果是结果为 `L` 则在 $0$ 号区间，为 `R` 则在 $1$ 号区间，为 `N` 则在 $2$​ 号区间。

也就是说，每一层的询问结果相当于一个“跳结点指令”，当跳到该层的结点时，为 `L` 则跳到这个结点的 $0$ 号区间，为 `R` 跳到这个结点的 $1$ 号区间，为 `N` 跳到这个结点的 $2$ 号区间。

在决策树上，按照指令从根往下跳就能知道答案。

最后我们考虑忽略一个查询的条件，这时要再加一个查询，以便能够还原被忽略的查询。

考虑对于每个叶子结点，将根结点到每个叶子结点的边编号加起来对 $3$ 取模。

如果这个模数为 $x$，钦定这个结点放在这次询问的 $x$​​ 号区间。

可以注意到，三种编号有两种数量相同，将数量相同的两个编号映射到 $0,1$ 号区间，另一个映射到 $2$ 号区间，对映射后的查询完再映射回来即可。接着对映射后 $0$ 和 $1$ 两个区间拼起来进行查询，结果为 `L` 则在 $0$ 号区间，为 `R` 则在 $1$ 号区间，为 `N` 则在 $2$ 号区间。

下面需要证明三种编号有两种数量相同。如证明无法理解可跳过。

## 证明

令 $f_{i,j}$ 表示 $n$ 个数的决策树，根结点到每个叶子结点的边编号加起来模 $3$ 余 $j$ 的数个数。则此命题即为：对于任意正整数 $n$ 有 $f_{n,0},f_{n,1},f_{n,2}$ 有两个相等。

（因为 $n>1$，为方便，$n=1$ 时决策树最大深度为 $2$ 而不是 $1$。）

为证明该命题，需要证明一个显然更强的命题：在原命题的基础上，如果 $n \bmod 3=0$，则 $f_{n,0}=f_{n,1}=f_{n,2}$，否则如果 $n \bmod 3=2$ 则 $f_{n,0}+f_{n-1,0}=f_{n,1}+f_{n-1,1}=f_{n,2}+f_{n-1,2}$。

使用数学归纳法。

当 $n=1,2$ 时已成立。当 $n\ge 3$ 时，假设 $1$ 到 $n-1$ 时已成立，则有：

### 当 $n \bmod 3=0$ 时
我们有：
$$
\begin{cases}
f_{n,0}=f_{\lfloor \frac{n}3 \rfloor,0}+f_{\lfloor \frac{n}3 \rfloor,2}+f_{\lfloor \frac{n}3 \rfloor,1} \\
f_{n,1}=f_{\lfloor \frac{n}3 \rfloor,1}+f_{\lfloor \frac{n}3 \rfloor,0}+f_{\lfloor \frac{n}3 \rfloor,2} \\
f_{n,2}=f_{\lfloor \frac{n}3 \rfloor,2}+f_{\lfloor \frac{n}3 \rfloor,1}+f_{\lfloor \frac{n}3 \rfloor,0}
\end{cases}
$$

则 $f_{n,0}=f_{n,1}=f_{n,2}$，命题成立。

### 当 $n \bmod 3=2$ 时

我们有：
$$
\begin{cases}
f_{n,0}=f_{\lfloor \frac{n}3 \rfloor+1,0}+f_{\lfloor \frac{n}3 \rfloor+1,2}+f_{\lfloor \frac{n}3 \rfloor,1}\\
f_{n,1}=f_{\lfloor \frac{n}3 \rfloor+1,1}+f_{\lfloor \frac{n}3 \rfloor+1,0}+f_{\lfloor \frac{n}3 \rfloor,2}\\
f_{n,2}=f_{\lfloor \frac{n}3 \rfloor+1,2}+f_{\lfloor \frac{n}3 \rfloor+1,1}+f_{\lfloor \frac{n}3 \rfloor,0}
\end{cases}
$$
且有：
$$
\begin{cases}
f_{n-1,0}=f_{\lfloor \frac{n}3 \rfloor,0}+f_{\lfloor \frac{n}3 \rfloor,2}+f_{\lfloor \frac{n}3 \rfloor+1,1} \\
f_{n-1,1}=f_{\lfloor \frac{n}3 \rfloor,1}+f_{\lfloor \frac{n}3 \rfloor,0}+f_{\lfloor \frac{n}3 \rfloor+1,2} \\
f_{n-1,2}=f_{\lfloor \frac{n}3 \rfloor,2}+f_{\lfloor \frac{n}3 \rfloor,1}+f_{\lfloor \frac{n}3 \rfloor+1,0} \\
\end{cases}
$$

不妨将 $f_{n,0},f_{n,1},f_{n,2}$ 同时减去一个数，$f_{n-1,0},f_{n-1,1},f_{n-1,2}$ 同时减去一个数。

由式子的对称性，如果 $\lfloor \frac{n}3\rfloor+1 \bmod 3=2$ 则不妨设：
$$
\begin{cases}
f_{\lfloor \frac{n}3 \rfloor,0}=f_{\lfloor \frac{n}3 \rfloor,1}=0,f_{\lfloor \frac{n}3 \rfloor,2}=d \\
f_{\lfloor \frac{n}3 \rfloor+1,0}=f_{\lfloor \frac{n}3 \rfloor+1,1}=0,f_{\lfloor \frac{n}3 \rfloor+1,2}=-d
\end{cases}
$$

则 $f_{n,0}=f_{n,2}=-d,f_{n,2}=d$，$f_{n,0}=f_{n,2}=d,f_{n,2}=-d$，$f_{n,0}+f_{n-1,0}=f_{n,1}+f_{n-1,1}=f_{n,2}+f_{n-1,2}=0$，命题成立。

如果 $\lfloor \frac{n}3\rfloor+1 \bmod 3=1$ 则不妨设:
$$
\begin{cases}
f_{\lfloor \frac{n}3 \rfloor,0}=f_{\lfloor \frac{n}3 \rfloor,1}=0,f_{\lfloor \frac{n}3 \rfloor,2}=0 \\
f_{\lfloor \frac{n}3 \rfloor+1,0}=f_{\lfloor \frac{n}3\rfloor+1,1}=0,f_{\lfloor \frac{n}3 \rfloor+1,2}=d
\end{cases}
$$

$f_{n,0}=f_{n,2}=d,f_{n,2}=0$，$f_{n,0}=f_{n,2}=0,f_{n,2}=d$，$f_{n,0}+f_{n-1,0}=f_{n,1}+f_{n-1,1}=f_{n,2}+f_{n-1,2}=d$，命题成立。

如果 $\lfloor \frac{n}3\rfloor+1 \bmod 3=0$，此情况与$\lfloor \frac{n}3\rfloor+1 \bmod 3=1$ 对称，命题成立。

因此，更强的命题成立，原命题也成立。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define __builtin_popcount __builtin_popcountll
using namespace std;
const int N=200005,M=25;
int n,m,q,cnt,a[M][N],w[N],cw[M],z;
struct node{
	int l,r,son[3];
}tree[N<<2];
void build(int x,int l,int r,int d,int e){
	tree[x].l=l;
	tree[x].r=r;
	for(int i=l;i<=r;i++){
		a[d][i]=e;
	}
	if(d==m)return;
	int len=r-l+1;
	if(len==1){
		tree[x].son[2]=++cnt;
		build(tree[x].son[2],l,l,d+1,2);
		return;
	}
	if(len==2){
		tree[x].son[0]=++cnt;
		tree[x].son[1]=++cnt;
		build(tree[x].son[0],l,l,d+1,0);
		build(tree[x].son[1],r,r,d+1,1);
		return;
	}
	for(int i=0;i<3;i++)tree[x].son[i]=++cnt;
	switch(len%3){
		case 0:{
			int w=len/3;
			build(tree[x].son[0],l,l+w-1,d+1,0);
			build(tree[x].son[1],l+w,r-w,d+1,1);
			build(tree[x].son[2],r-w+1,r,d+1,2);
			break;
		}
		case 1:{
			int w=len/3;
			build(tree[x].son[0],l,l+w-1,d+1,0);
			build(tree[x].son[1],l+w,l+w+w-1,d+1,1);
			build(tree[x].son[2],l+w+w,r,d+1,2);
			break;
		}
		case 2:{
			int w=len/3;
			build(tree[x].son[0],l,l+w,d+1,0);
			build(tree[x].son[1],l+w+1,l+w+w+1,d+1,1);
			build(tree[x].son[2],l+w+w+2,r,d+1,2);
			break;
		}
	}
}
inline int tonum(char c){
	if(c=='L')return 0;
	else if(c=='R')return 1;
	else return 2;
}
inline int skip(string&s){
	int x=1;
	for(int i=1;i<=m;i++){
		x=tree[x].son[tonum(s[i])];
	}
	return tree[x].l;
}
inline void solve(){
	cin>>n;
	cnt=1,m=0;
	for(int i=1;i<=20;i++)for(int j=1;j<=n;j++)a[i][j]=w[j]=0;
	cw[0]=cw[1]=cw[2]=0;
	for(int p=1;p<n;p*=3)++m;
	build(1,1,n,0,0);
	cout<<m+1<<endl;
	for(int i=1;i<=m;i++){
		int c=0;
		for(int j=1;j<=n;j++)if(a[i][j]!=2)++c;
		cout<<c<<' ';
		for(int j=1;j<=n;j++)if(a[i][j]==0)cout<<j<<' ';
		for(int j=1;j<=n;j++)if(a[i][j]==1)cout<<j<<' ';
		for(int j=1;j<=n;j++)(w[j]+=a[i][j])%=3;
		cout<<endl;
	}
	for(int i=1;i<=n;i++)++cw[w[i]];
	if(cw[0]==cw[1])z=0;
	else if(cw[0]==cw[2])z=1;
	else z=2;
	for(int i=1;i<=n;i++)(w[i]+=z)%=3;
	int c=0;
	for(int j=1;j<=n;j++)if(w[j]!=2)++c;
	cout<<c<<' ';
	for(int j=1;j<=n;j++)if(w[j]==0)cout<<j<<' ';
	for(int j=1;j<=n;j++)if(w[j]==1)cout<<j<<' ';
	cout<<endl;
	string s;
	cin>>s;
	s=' '+s;
	int f=0,sum=0,sum2=0;
	for(int i=1;i<=m;i++){
		if(s[i]=='?'){
			f=i;
		}else{
			(sum2+=tonum(s[i]))%=3;
		}
	}
	if(f){
		sum=(tonum(s[m+1])+3-z)%3;
		s[f]="LRN"[(sum+3-sum2)%3];
	}
	cout<<skip(s)<<'\n';
}
signed main(){
	cin>>q;
	while(q--)solve();
    return 0;
}
```

---

## 作者：phigy (赞：0)

题意可以视为给每个数设置一个不同的三进制值，使得删掉任意一个位后依然不存在相同数，要使位数尽可能少，其中本来应该有的额外限制是对任意一个位必须有两个数值相同，但是实际不起作用可以忽略。

由于可以删任意一个位，相当于知道任意 $T-1$ 个位就可以推出来不知道的位，那么这种结构直接用和模 $3$ 余 $0$ 就行了。



```cpp
#include <bits/stdc++.h>

#define i64 long long

const int REN=200000,MAXN=REN+5;

using namespace std;

int pw[18];
int a[MAXN];
int n,mx;
unordered_map<int,int>mp;
void solve(int L,int R,int k)
{
    mx=max(mx,k);
    if(L>=R) {return ;}
    int len=R-L+1;
    int A=(len+1)/3,B=len-2*A;
    for(int i=L;i<L+A;i++) {a[i]+=pw[k]*2;}
    for(int i=L+A;i<L+2*A;i++) {a[i]+=pw[k];}
    solve(L,L+A-1,k+1);
    solve(L+A,L+2*A-1,k+1);
    solve(L+2*A,R,k+1);
}

signed main()
{
    int i,j,k;
    pw[0]=1;for(i=1;i<18;i++) {pw[i]=pw[i-1]*3;}
    int _;cin>>_;
    while(_--)
    {
        cin>>n;
        mx=0;
        mp.clear();
        for(i=1;i<=n;i++) {a[i]=0;}
        solve(1,n,0);
        for(i=1;i<=n;i++)
        {
            int sum=0;
            for(j=0;j<mx;j++)
            {
                sum+=(a[i]/pw[j])%3;
            }
            a[i]+=pw[mx]*((3-sum%3)%3);
            mp[a[i]]=i;
        }
        cout<<mx+1<<'\n';
        for(j=0;j<=mx;j++)
        {
            deque<int>Q;
            for(i=1;i<=n;i++)
            {
                if((a[i]/pw[j])%3==1) {Q.push_front(i);}
                if((a[i]/pw[j])%3==2) {Q.push_back(i);}
            }
            cout<<Q.size()<<' ';
            for(int x:Q) {cout<<x<<' ';}
            cout<<endl;
        }
        int p,x=0;
        for(j=0;j<=mx;j++)
        {
            char c;
            cin>>c;
            if(c=='?') {p=j;}
            if(c=='L') {x+=pw[j];}
            if(c=='R') {x+=pw[j]*2;}
        }
        cout<<(mp[x]|mp[x+pw[p]]|mp[x+2*pw[p]])<<endl;
    }
    return 0;
}
```

---

## 作者：UniGravity (赞：0)

首先考虑弱化。若没有询问被忽略则考虑每次询问直接分成三组，两组大小相等作为询问数组的前后部分，最后一组代表不在数组内。

由于将一个数均分为三组其中至少有两组大小相等因此可以直接分。询问次数 $\lceil\log_3n\rceil$。

考虑将每个点看成位数为 $q$ 的三进制数，则只要不存在两个数相等最后就是可以区分这些数字的。

考虑如果可以忽略一组答案，则对于 $x,y$ 两个数，如果它们的三进制表示只相差一位则回答时可忽略这一位，这样这两个数就无法区分了。

因此我们可以转化题目：需要找出 $n$ 个 $q$ 位三进制数，两两不同的位数量至少为 $2$，问最小的 $q$。

观察发现此时的 $q$ 一定为 $\lceil\log_3n\rceil+1$。考虑多出来的这一位，我们需要让之前三进制下只相差一位的数字在这一位不同。可以想到按之前位数的和模 $3$ 分组，此时之前相差一位的数一定被分到不同的组内。

同时发现分出的这三组一定有至少两组大小相等。最后一次操作只需要询问这两组拼起来即可。

```cpp
const int N=200005;
int n,q,a[N][21];
char tmp[21];int ans[21];

il void sol(int l,int r,int d){
    // cerr<<l<<' '<<r<<'\n';
    if(r-l+1==1)return;
    else if(r-l+1==2)return a[l][d]=1,a[r][d]=2,void();
    int c=(r-l+1)/3;
    if(c*3+2==r-l+1){
        c++;
        forto(i,r-c+1,r)a[i][d]=1;
        forto(i,r-c*2+1,r-c)a[i][d]=2;
        sol(l,r-c*2,d+1),sol(r-c*2+1,r-c,d+1),sol(r-c+1,r,d+1);
    }else{
        forto(i,l,l+c-1)a[i][d]=1;
        forto(i,l+c,l+c*2-1)a[i][d]=2;
        sol(l,l+c-1,d+1),sol(l+c,l+c*2-1,d+1),sol(l+c*2,r,d+1);
    }
}

il void work(){
    scanf("%d",&n);
    int tot=1;q=0;
    while(tot<n)tot*=3,q++;
    forto(i,1,n)forto(j,1,q+1)a[i][j]=0;
    sol(1,n,1);
    vector<int>p1,p2;int c;
    forto(i,1,n){
        c=0;forto(j,1,q)c=(c+a[i][j])%3;
        a[i][q+1]=c;
    }
    forto(i,min(p1.size(),p2.size()),(int)p1.size()-1)a[p1[i]][q+1]=0;
    forto(i,min(p1.size(),p2.size()),(int)p2.size()-1)a[p2[i]][q+1]=0;
    q++,printf("%d\n",q);
    forto(i,1,q){
        p1.clear(),p2.clear();
        forto(j,1,n){
            if(a[j][i]==1)p1.eb(j);
            else if(a[j][i]==2)p2.eb(j);
        }
        printf("%d ",p1.size()+p2.size());
        for(int x:p1)printf("%d ",x);
        for(int x:p2)printf("%d ",x);
        printf("\n");
    }
    fflush(stdout),scanf("%s",tmp+1);
    forto(i,1,q){
        if(tmp[i]=='L')ans[i]=1;else if(tmp[i]=='R')ans[i]=2;
        else if(tmp[i]=='N')ans[i]=0;else ans[i]=-1;
    }
    forto(i,1,n){
        bool f=1;
        forto(j,1,q)if(ans[j]!=-1&&ans[j]!=a[i][j]){f=0;break;}
        if(f){printf("%d\n",i);break;}
    }
    fflush(stdout);
}

signed main(){
    int t;scanf("%d",&t);
    while(t--)work();
    return 0;
}
```

---

## 作者：Down_syndrome (赞：0)

题意很明确了，不加赘述。

## 思路

先不考虑忽略的情况，每次询问有三种回答。所以如果问了 $q$ 次，总共最多有 $3^q$ 种不同不同情况，所以 $3^q\ge n$，再算上忽略的那次，询问下限是 $\lceil\log_3 n\rceil+1$。考虑构造对应的方案。

我们先不考虑忽略的情况，单单使用 $\lceil\log_3 n\rceil$ 次询问。

不难想到用三进制表示每个数字对应的查询情况。令回答 `N` 为 $0$，回答 `L` 为 $1$，回答 `R` 为 $1$。构造一组查询，使得每个数都有对应的三进制查询编码。

例如当 $n=4$ 时，可以有如下查询：

```
2
2 2 3
2 1 3
```

则对应的编码为：

||询问 $1$|询问 $2$|
|:-:|:-:|:-:|
|猜数为 $1$| $0$ | $1$ |
|猜数为 $2$| $1$ | $0$ |
|猜数为 $3$| $2$ | $2$ |
|猜数为 $4$| $0$ | $0$ |

于是我们可以考虑构造上面那个表格。

先想想它要满足什么需求？下面两条：

1. 不能有两个数的编码相同（否则你就判断不出来哪个是那个了），也就是说，不能有完全相同的两行。
2. 每一次查询左右两边的数的个数相同，也就是每一列 $1$ 的个数要与 $2$ 相同。

我们可以一个数一个数构造。先随意构造第一个数的编码，再把第二个数的编码构造为第一个数的编码“取反”——$1$ 变成 $2$，$2$ 变成 $1$，$0$ 不变。这样轮流构造，即可满足 $1$ 的个数和 $2$ 的个数相同的限制。如果 $n$ 是奇数，则加一列全 $0$。

例如 $n=5$ 时，可以有如下构造：

```
2
2 1 2
2 3 4
```

||询问 $1$|询问 $2$|
|:-:|:-:|:-:|
|猜数为 $1$| $1$ | $0$ |
|猜数为 $2$| $2$ | $0$ |
|猜数为 $3$| $0$ | $1$ |
|猜数为 $4$| $0$ | $2$ |
|猜数为 $5$ | $0$ | $0$ |

于是就做完了。

那我们考虑回忽略的情况，那我们就要在上述矩阵中新开一列，并需要满足相似的条件：

1. **任意两行不同的位置至少有两个**，否则恰好忽略那个位置就完了。
2. 也就是每一列 $1$ 的个数要与 $2$ 相同。

相当于我们要加一个满足第 $2$ 个条件的列，使得原来**恰好有一个位置不同的两个数**在这一列中不同。

容易发现，**恰好有一个位置不同的两个数**的编码的数位和模 $3$ 不同，因为它们最多相差 $2$，所以按照和模 $3$ 分类即可。回顾我们上述的构造方案，发现这样能恰好满足第 $2$ 个条件，因为 $1$ 和 $2$ 在模 $3$ 下互为相反数，所以我们“取反”的构造方式能够保证一一对应。

补充一下上面那个例子，这样构造：

```
3
2 1 2
2 3 4
4 1 3 2 4
```

||询问 $1$|询问 $2$| 询问 $3$ |
|:-:|:-:|:-:|:-:|
|猜数为 $1$| $1$ | $0$ | $1$ |
|猜数为 $2$| $2$ | $0$ | $2$ |
|猜数为 $3$| $0$ | $1$ | $1$ |
|猜数为 $4$| $0$ | $2$ | $2$ |
|猜数为 $5$ | $0$ | $0$ | $0$ |

即可。

## code

写的时候可以写 $4$ 进制，应该会好写一点。本人写的有点松弛了，仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int M=2e7+5;
int t,n,m,q,k,cnt,ans,a[N],b[N];
char s[N];
bool vis[M];
bool check(int x){
	for(int i=0;i<q;i++) if(((x>>(i<<1))&3)==3) return false;
	return true;
}
int opt(int x){
	int ans=0,y;
	for(int i=0;i<q;i++){
		y=(x>>(i<<1))&3;
		if(y) ans=ans|((3-y)<<(i<<1));
	}
	return ans;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		m=1;
		q=0;
		while(m<n){
			m*=3;
			q++;
		}
		printf("%d\n",q+1);
		for(int i=1,j=1;i<n;i+=2){
			while(vis[j]||!check(j)) j++;
			a[i]=j;
			a[i+1]=opt(j);
			vis[j]=vis[opt(j)]=1;
		}
		if(n&1) a[n]=0;
		for(int i=0;i<q;i++){
			cnt=0;
			for(int j=1;j<=n;j++){
				b[j]=(a[j]>>(i<<1))&3;
				if(b[j]) cnt++;
			}
			printf("%d ",cnt);
			for(int j=1;j<=n;j++) if(b[j]==1) printf("%d ",j);
			for(int j=1;j<=n;j++) if(b[j]==2) printf("%d ",j);
			printf("\n");
		}
		cnt=0;
		for(int i=1;i<=n;i++){
			b[i]=0;
			for(int j=0;j<q;j++) b[i]+=(a[i]>>(j<<1))&3;
			b[i]%=3;
			a[i]|=b[i]<<(q<<1);
			if(b[i]) cnt++;
		}
		printf("%d ",cnt);
		for(int i=1;i<=n;i++) if(b[i]==1) printf("%d ",i);
		for(int i=1;i<=n;i++) if(b[i]==2) printf("%d ",i);
		printf("\n");
		fflush(stdout);
		scanf("%s",s);
		ans=0;
		for(int i=0;i<=q;i++){
			if(s[i]=='?') k=i;
			if(s[i]=='L') ans|=1<<(i<<1);
			if(s[i]=='R') ans|=2<<(i<<1);
		}
		for(int i=1;i<=n;i++){
			a[i]-=((a[i]>>(k<<1))&3)<<(k<<1);
			if(a[i]==ans) printf("%d\n",i);
		}
		fflush(stdout);
		for(int i=1;i<=1<<(q<<1);i++) vis[i]=0;
	}
	return 0;
}
```

---

