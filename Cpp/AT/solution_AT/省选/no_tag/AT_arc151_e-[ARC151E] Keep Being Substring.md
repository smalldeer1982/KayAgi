# [ARC151E] Keep Being Substring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc151/tasks/arc151_e

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が与えられます。 また、$ A $ の長さ $ P $ の連続な部分列 $ X\ =\ (X_1,\ X_2,\ \ldots,\ X_P) $ と、$ A $ の長さ $ Q $ の連続な部分列 $ Y\ =\ (Y_1,\ Y_2,\ \ldots,\ Y_Q) $ が与えられます。

$ X $ に対して、下記の $ 4 $ つのいずれかを行うという操作を、好きな回数（ $ 0 $ 回でも良い）だけ行うことができます。

- $ X $ の先頭に任意の整数を $ 1 $ つ追加する。
- $ X $ の先頭の要素を削除する。
- $ X $ の末尾に任意の整数を $ 1 $ つ追加する。
- $ X $ の末尾の要素を削除する。

ただし、各操作の前後において、$ X $ は $ A $ の**空でない**連続な部分列でなければなりません。 $ X $ を $ Y $ と一致させるために行う操作回数の最小値を求めてください。 なお、本問題の制約下において、操作の繰り返しによって $ X $ と $ Y $ を必ず一致させられることが証明できます。

 連続な部分列とは？ 数列 $ X\ =\ (X_1,\ X_2,\ \ldots,\ X_P) $ が数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ の**連続な部分列**であるとは、$ 1\ \leq\ l\ \leq\ N-P+1 $ を満たす整数 $ l $ が存在して、 すべての $ i\ =\ 1,\ 2,\ \ldots,\ P $ について、$ X_i\ =\ A_{l+i-1} $ が成り立つことです。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N $
- $ 1\ \leq\ P,\ Q\ \leq\ N $
- $ (X_1,\ X_2,\ \ldots,\ X_P) $ と $ (Y_1,\ Y_2,\ \ldots,\ Y_Q) $ は、$ (A_1,\ A_2,\ \ldots,\ A_N) $ の連続な部分列
- 入力はすべて整数

### Sample Explanation 1

下記の手順で操作すると、$ X $ が $ A $ の空でない連続な部分列であるという条件を満たしたまま、$ X $ を $ Y $ に一致させることが出来ます。 1. まず、$ X $ の先頭の要素を削除する。その結果、$ X\ =\ (1) $ となる。 2. 次に、$ X $ の末尾に $ 5 $ を追加する。その結果、$ X\ =\ (1,\ 5) $ となる。 3. さらに、$ X $ の 末尾に $ 7 $ を追加する。その結果、$ X\ =\ (1,\ 5,\ 7) $ となり、$ X $ は $ Y $ と一致する。 上記の手順の操作回数は $ 3 $ 回であり、これが考えられる最小の操作回数です。

## 样例 #1

### 输入

```
7
3 1 4 1 5 7 2
2
3 1
3
1 5 7```

### 输出

```
3```

## 样例 #2

### 输入

```
20
2 5 1 2 7 7 4 5 3 7 7 4 5 5 5 4 6 5 6 1
6
1 2 7 7 4 5
7
7 4 5 5 5 4 6```

### 输出

```
7```

# 题解

## 作者：EnofTaiPeople (赞：3)

### Part1 前言
并不是为了这道题学的 $\text{SAM}$，而是学完 $\text{SAM}$ 后回顾比赛时看到了这道题，好像思维就一点，算法就一点，难点在于特判。

### Part2 问题转化
题面中说，要通过加减头字符，使 $X$ 串变成 $Y$ 串，保证任意时刻 $X$ 串**非空**且是 $A$ 的子串。

考虑贪心地将 $X$ 删减变为两串的 $LCS$，即最长公共子串，然后添加字符，于是答案就是 $|X|+|Y|-2|LCS(x,y)|$。

如果没有 $\text{LCS}$，即任意字符都不相同，这种情况可以先将 $\text{X}$ 缩成一个字符，然后不断跳，字符 $x$ 可以跳到 $y$ 当且仅当 $xy$ 或 $yx$ 是 $A$ 串的子串，于是可以对 $A$ 串中相邻字符连边，然后广搜，答案就是 $|X|+|Y|+2dis-2$。

### Part3 广义 SAM 的实现
如何求两个字符串的 $LCS$？考虑将对它们建立广义 $\text{SAM}$，找到长度最大且同时是两个串的子串的状态就是答案。

具体地，每一个状态记录两个 $size$，即 $sizeX(x)$ 和 $sizeY(x)$，我们要找的就是 $\max[sizeX(x)][sizeY(x)]len(x)$。

广义 $\text{SAM}$ 和普通 $\text{SAM}$ 的区别在于会接受多个字符串，于是可以考虑对于所有字符串（本题只有 $X$ 和 $Y$）建立 $\text{Trie}$，这样在每一个 $\text{Trie}$ 节点上插入字符之前，$last$ 都会置于它 $\text{Trie}$ 上父亲的表示节点。

考虑在 $\text{Trie}$ 上广搜，于是可以成功建立广义 $\text{SAM}$：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
namespace fast_io{
    char buf[N+5],*p1,*p2,c,f;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2))?EOF:*p1++
    template<typename _Tp>
        void read(_Tp &x){
            for(c=gc,f=0;c<48;c=gc)if(c=='-')f=!f;
            for(x=0;c>47;x=x*10+(48^c),c=gc);if(f)x=-x;
        }
    template<typename _Tp,typename..._tps>
        void read(_Tp &x,_tps&...y){
            read(x),read(y...);
        }
    char ob[N+35];
    int ot,st[35],_tp;
    void fls(){fwrite(ob,1,ot,stdout),ot=0;}
    template<typename _Tp>
        void write(_Tp x){
            if(x<0)ob[ot++]='-',x=-x;
            for(_tp=0;x>9;st[++_tp]=48^(x%10),x/=10);
            for(ob[ot++]=48^x;_tp;ob[ot++]=st[_tp--]);
            ob[ot++]='\n';
            if(ot>N)fwrite(ob,1,ot,stdout),ot=0;
        }
}using fast_io::read;
using fast_io::write;
vector<int>lk[N];
map<int,int>t[N],tr[N];
int tcnt=1,cnt=1,A,X,Y;
int a[N],b[N],c[N],_ls[N];
int ln[N],sz[N][2],f[N];
int ct[N],g[N],lp,d[N],q[N],l,r;
bitset<N>vs,IC;
void add(int x,int ds){
    if(~d[x])return;
    if(IC[x])printf("%d\n",X+Y+ds+ds-2),exit(0);
    d[q[++r]=x]=ds;
}
int ins(int ls,int p,vector<int>&G){
    int x,y,z,r=t[ls][p];
    ln[x=++cnt]=ln[ls]+1;
    for(int q:G)sz[x][q]=1;
    for(y=ls;y&&!t[y][p];t[y][p]=x,y=f[y]);
    if(!y)f[x]=1;
    else if(ln[y]+1==ln[z=t[y][p]])f[x]=z;
    else{
        ln[r=++cnt]=ln[y]+1,f[r]=f[z],t[r]=t[z];
        while(y&&t[y][p]==z)t[y][p]=r,y=f[y];
        f[x]=f[z]=r;
    }return x;
}
int main(){
    int i,x,y;read(A);
    for(i=1;i<=A;++i)read(a[i]);
    read(X);
    for(i=x=1;i<=X;++i){
        read(y),lk[x].push_back(0);
        if(!tr[x][y])tr[x][y]=++tcnt;
        x=tr[x][b[i]=y];
    }lk[x].push_back(0);
    read(Y);
    for(i=x=1;i<=Y;++i){
        read(y),lk[x].push_back(1);
        if(!tr[x][y])tr[x][y]=++tcnt;
        x=tr[x][c[i]=y];
    }lk[x].push_back(1);
    q[l=r=1]=_ls[1]=1;
    while(l<=r){
        x=q[l++];
        for(auto it:tr[x])
            _ls[q[++r]=it.second]=ins(_ls[x],it.first,lk[it.second]);
    }
    for(x=1;x<=cnt;++x)++ct[ln[x]];
    for(x=1;x<=cnt;++x)ct[x]+=ct[x-1];
    for(x=1;x<=cnt;++x)g[ct[ln[x]]--]=x;
    for(i=cnt;i;--i)if(f[g[i]]){
        sz[f[g[i]]][0]+=sz[g[i]][0];
        sz[f[g[i]]][1]+=sz[g[i]][1];
    }
    for(x=1;x<=cnt;++x)
        if(sz[x][0]&&sz[x][1])
            lp=max(lp,ln[x]);
    if(lp){
        printf("%d\n",X+Y-lp-lp);
        return 0;
    }
    for(x=1;x<=A;++x)d[x]=-1,lk[x].clear();
    for(x=1;x<A;++x){
        lk[a[x]].push_back(a[x+1]);
        lk[a[x+1]].push_back(a[x]);
    }l=1,r=0;
    for(x=1;x<=Y;++x)IC[c[x]]=1;
    for(x=1;x<=X;++x)add(b[x],0);
    while(l<=r){
        x=q[l++];
        for(int y:lk[x])
            add(y,d[x]+1);
    }
    while(1)puts("ATCODER_JUDGE");
    return 0;
}
```

然而，如果你写的是深搜，这样做并不能建出真正意义的广义 $\text{SAM}$，因为在某一棵子树的插入过程中，一个状态后面可能已经有了连续的转移，这时候我们需要新增一个特判，如果已经有了连续的转移，就直接跳一步，而不增加节点：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
namespace fast_io{
    char buf[N+5],*p1,*p2,c,f;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2))?EOF:*p1++
    template<typename _Tp>
        void read(_Tp &x){
            for(c=gc,f=0;c<48;c=gc)if(c=='-')f=!f;
            for(x=0;c>47;x=x*10+(48^c),c=gc);if(f)x=-x;
        }
    template<typename _Tp,typename..._tps>
        void read(_Tp &x,_tps&...y){
            read(x),read(y...);
        }
    char ob[N+35];
    int ot,st[35],_tp;
    void fls(){fwrite(ob,1,ot,stdout),ot=0;}
    template<typename _Tp>
        void write(_Tp x){
            if(x<0)ob[ot++]='-',x=-x;
            for(_tp=0;x>9;st[++_tp]=48^(x%10),x/=10);
            for(ob[ot++]=48^x;_tp;ob[ot++]=st[_tp--]);
            ob[ot++]='\n';
            if(ot>N)fwrite(ob,1,ot,stdout),ot=0;
        }
}using fast_io::read;
using fast_io::write;
vector<int>lk[N];
map<int,int>t[N],tr[N];
int tcnt=1,cnt=1,A,X,Y;
int a[N],b[N],c[N];
int ln[N],sz[N][2],f[N];
int ct[N],g[N],lp,d[N],q[N],l,r;
bitset<N>vs,IC;
void add(int x,int ds){
    if(~d[x])return;
    if(IC[x])printf("%d\n",X+Y+ds+ds-2),exit(0);
    d[q[++r]=x]=ds;
}
int ins(int ls,int p,vector<int>&G){
    int x,y,z,r=t[ls][p];
    if(r&&ln[ls]+1==ln[r]){//已经存在了连续的转移
        for(int q:G)++sz[r][q];
        return r;
    }
    ln[x=++cnt]=ln[ls]+1;
    for(int q:G)sz[x][q]=1;
    for(y=ls;y&&!t[y][p];t[y][p]=x,y=f[y]);
    if(!y)f[x]=1;
    else if(ln[y]+1==ln[z=t[y][p]])f[x]=z;
    else{
        ln[r=++cnt]=ln[y]+1,f[r]=f[z],t[r]=t[z];
        while(y&&t[y][p]==z)t[y][p]=r,y=f[y];
        f[x]=f[z]=r;
    }return x;
}
void dfs(int x,int ls){
    for(auto it:tr[x])
        dfs(it.second,ins(ls,it.first,lk[it.second]));
}
int main(){
    int i,x,y;read(A);
    for(i=1;i<=A;++i)read(a[i]);
    read(X);
    for(i=x=1;i<=X;++i){
        read(y),lk[x].push_back(0);
        if(!tr[x][y])tr[x][y]=++tcnt;
        x=tr[x][b[i]=y];
    }lk[x].push_back(0);
    read(Y);
    for(i=x=1;i<=Y;++i){
        read(y),lk[x].push_back(1);
        if(!tr[x][y])tr[x][y]=++tcnt;
        x=tr[x][c[i]=y];
    }lk[x].push_back(1);
    dfs(1,1);
    for(x=1;x<=cnt;++x)++ct[ln[x]];
    for(x=1;x<=cnt;++x)ct[x]+=ct[x-1];
    for(x=1;x<=cnt;++x)g[ct[ln[x]]--]=x;
    for(i=cnt;i;--i)if(f[g[i]]){
        sz[f[g[i]]][0]+=sz[g[i]][0];
        sz[f[g[i]]][1]+=sz[g[i]][1];
    }
    for(x=1;x<=cnt;++x)
        if(sz[x][0]&&sz[x][1])
            lp=max(lp,ln[x]);
    if(lp){
        printf("%d\n",X+Y-lp-lp);
        return 0;
    }
    for(x=1;x<=A;++x)d[x]=-1,lk[x].clear();
    for(x=1;x<A;++x){
        lk[a[x]].push_back(a[x+1]);
        lk[a[x+1]].push_back(a[x]);
    }l=1,r=0;
    for(x=1;x<=Y;++x)IC[c[x]]=1;
    for(x=1;x<=X;++x)add(b[x],0);
    while(l<=r){
        x=q[l++];
        for(int y:lk[x])
            add(y,d[x]+1);
    }
    while(1)puts("ATCODER_JUDGE");
    return 0;
}
```
### Part4 更简洁的实现方式
每插入完一个字符串后直接将 $last$ 置为 $1$，然后继续插入，这样不需要建立 $\text{Trie}$，效率十分优秀，也十分常用，其实就是从 $\text{Trie}$ 上跳字符转换成了在 $\text{SAM}$ 里特判跳字符，其实效果一样：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
namespace fast_io{
    char buf[N+5],*p1,*p2,c,f;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2))?EOF:*p1++
    template<typename _Tp>
        void read(_Tp &x){
            for(c=gc,f=0;c<48;c=gc)if(c=='-')f=!f;
            for(x=0;c>47;x=x*10+(48^c),c=gc);if(f)x=-x;
        }
    template<typename _Tp,typename..._tps>
        void read(_Tp &x,_tps&...y){
            read(x),read(y...);
        }
    char ob[N+35];
    int ot,st[35],_tp;
    void fls(){fwrite(ob,1,ot,stdout),ot=0;}
    template<typename _Tp>
        void write(_Tp x){
            if(x<0)ob[ot++]='-',x=-x;
            for(_tp=0;x>9;st[++_tp]=48^(x%10),x/=10);
            for(ob[ot++]=48^x;_tp;ob[ot++]=st[_tp--]);
            ob[ot++]='\n';
            if(ot>N)fwrite(ob,1,ot,stdout),ot=0;
        }
}using fast_io::read;
using fast_io::write;
vector<int>lk[N];
map<int,int>t[N];
int tcnt=1,cnt=1,A,X,Y;
int a[N],b[N],c[N],ls;
int ln[N],sz[N][2],f[N];
int ct[N],g[N],lp,d[N],q[N],l,r;
bitset<N>vs,IC;
void add(int x,int ds){
    if(~d[x])return;
    if(IC[x])printf("%d\n",X+Y+ds+ds-2),exit(0);
    d[q[++r]=x]=ds;
}
int ins(int ls,int p,vector<int>&G){
    int x,y,z,r=t[ls][p];
    if(r&&ln[ls]+1==ln[r]){
        for(int q:G)++sz[r][q];
        return r;
    }
    ln[x=++cnt]=ln[ls]+1;
    for(int q:G)sz[x][q]=1;
    for(y=ls;y&&!t[y][p];t[y][p]=x,y=f[y]);
    if(!y)f[x]=1;
    else if(ln[y]+1==ln[z=t[y][p]])f[x]=z;
    else{
        ln[r=++cnt]=ln[y]+1,f[r]=f[z],t[r]=t[z];
        while(y&&t[y][p]==z)t[y][p]=r,y=f[y];
        f[x]=f[z]=r;
    }return x;
}
int main(){
    int i,x,y;read(A);
    for(i=1;i<=A;++i)read(a[i]);
    read(X),ls=1;
    vector<int>_0={0},_1={1};
    for(i=x=1;i<=X;++i)
        read(y),ls=ins(ls,y,_0),b[i]=y;
    read(Y),ls=1;
    for(i=x=1;i<=Y;++i)
        read(y),ls=ins(ls,y,_1),c[i]=y;
    for(x=1;x<=cnt;++x)++ct[ln[x]];
    for(x=1;x<=cnt;++x)ct[x]+=ct[x-1];
    for(x=1;x<=cnt;++x)g[ct[ln[x]]--]=x;
    for(i=cnt;i;--i)if(f[g[i]]){
        sz[f[g[i]]][0]+=sz[g[i]][0];
        sz[f[g[i]]][1]+=sz[g[i]][1];
    }
    for(x=1;x<=cnt;++x)
        if(sz[x][0]&&sz[x][1])
            lp=max(lp,ln[x]);
    if(lp){
        printf("%d\n",X+Y-lp-lp);
        return 0;
    }
    for(x=1;x<=A;++x)d[x]=-1,lk[x].clear();
    for(x=1;x<A;++x){
        lk[a[x]].push_back(a[x+1]);
        lk[a[x+1]].push_back(a[x]);
    }l=1,r=0;
    for(x=1;x<=Y;++x)IC[c[x]]=1;
    for(x=1;x<=X;++x)add(b[x],0);
    while(l<=r){
        x=q[l++];
        for(int y:lk[x])
            add(y,d[x]+1);
    }
    while(1)puts("ATCODER_JUDGE");
    return 0;
}
```
### Part5 后记
当然，大多数广义 $\text{SAM}$ 的题目即使不加此特判也不影响答案，但还是建议养成良好的习惯。

因为我是初学 $\text{SAM}$，有细节错误请多加指证。

---

## 作者：Caiest_Oier (赞：2)

# [AT_arc151_e](https://www.luogu.com.cn/problem/AT_arc151_e)       

如果 X 与 Y 的最长公共子串非空，则最优方案自然就是删到这个最长公共子串后再加过去，显然这是最小的。如果使用哈希求最长公共子串，需要双哈希，否则会被卡。     

否则，X 与 Y 中的字符全部不同，则方案必定是先删到一个字符，然后添加字符，删字符，直到字符变为 Y 中的一个字符。这样是最优的方案的原因也是显然的，中途加入的所有字符都不是 Y 里的字符，它们只是作为转移的工具，必定会被删掉。如果留着它们，反而会阻碍后面的转移，所以转移到了就删除即可。     

建图，点集为字符集，在 $A_i$ 和 $A_{i+1}$ 之间连一条边权为 $2$ 的边，然后从 $X$ 中所有字符作为起点，$Y$ 中所有字符做为终点，跑 bfs 求最短路。最后答案就是 $|X|+|Y|-2+dis$。    

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
#define MOD2 1000000007
#define P 233331
using namespace std;
int n,a[500003],m1,m2,s[500003],t[500003],hss[500003],hst[500003],fsp[500003],lft,rgt,mid,apr1[500003],apr2[500003];
int hss2[500003],hst2[500003],fsp2[500003];
int q[500003],totq,dis[500003];
int getS(int l,int r){return (((hss[r]-hss[l-1]*fsp[r-l+1])%MOD)+MOD)%MOD;}
int getT(int l,int r){return (((hst[r]-hst[l-1]*fsp[r-l+1])%MOD)+MOD)%MOD;}
int getS2(int l,int r){return (((hss2[r]-hss2[l-1]*fsp2[r-l+1])%MOD2)+MOD2)%MOD2;}
int getT2(int l,int r){return (((hst2[r]-hst2[l-1]*fsp2[r-l+1])%MOD2)+MOD2)%MOD2;}
vector<int>E[500003];
int stk1[500003],stk2[500003],tot1,tot2,stk3[500003],tot3;
bool chk(int len){
	tot1=tot2=tot3=0;
	for(int i=1;i+len-1<=m1;i++)stk1[++tot1]=getS(i,i+len-1)*(MOD2+1)+getS2(i,i+len-1);
	for(int i=1;i+len-1<=m2;i++)stk2[++tot2]=getT(i,i+len-1)*(MOD2+1)+getT2(i,i+len-1);
	sort(stk1+1,stk1+tot1+1);
	sort(stk2+1,stk2+tot2+1);
	for(int i=1;i<=tot1;i++){
		int j=i;
		while(j<tot1&&stk1[j+1]==stk1[i])j++;
		stk3[++tot3]=stk1[i];
		i=j;
	}
	for(int i=1;i<=tot2;i++){
		int j=i;
		while(j<tot2&&stk2[j+1]==stk2[i])j++;
		stk3[++tot3]=stk2[i];
		i=j;
	}
	sort(stk3+1,stk3+tot3+1);
	for(int i=1;i<tot3;i++)if(stk3[i]==stk3[i+1])return true;
	return false;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m1;
	for(int i=1;i<=m1;i++)cin>>s[i];
	cin>>m2;
	for(int i=1;i<=m2;i++)cin>>t[i];
	fsp[0]=1;
	for(int i=1;i<500000;i++)fsp[i]=fsp[i-1]*P%MOD;
	for(int i=1;i<=m1;i++)hss[i]=(hss[i-1]*P+s[i])%MOD;
	for(int i=1;i<=m2;i++)hst[i]=(hst[i-1]*P+t[i])%MOD;
	fsp2[0]=1;
	for(int i=1;i<500000;i++)fsp2[i]=fsp2[i-1]*P%MOD2;
	for(int i=1;i<=m1;i++)hss2[i]=(hss2[i-1]*P+s[i])%MOD2;
	for(int i=1;i<=m2;i++)hst2[i]=(hst2[i-1]*P+t[i])%MOD2;
	lft=1;
	rgt=min(m1,m2);
	while(lft<rgt){
		mid=((lft+rgt)>>1)+1;
		if(chk(mid))lft=mid;
		else rgt=mid-1;
	} 
	if(chk(lft)){
		cout<<m1-lft+m2-lft;
		return 0;
	}
	for(int i=1;i<=m1;i++)apr1[s[i]]=1;
	for(int i=1;i<=m2;i++)apr2[t[i]]=1;
	memset(dis,-1,sizeof(dis));
	for(int i=1;i<=n;i++)if(apr1[i])q[++totq]=i,dis[i]=0;
	for(int i=1;i<n;i++){
		E[a[i]].emplace_back(a[i+1]);
		E[a[i+1]].emplace_back(a[i]);
	}
	for(int i=1;i<=totq;i++){
		for(auto j:E[q[i]]){
			if(dis[j]==-1){
				dis[j]=dis[q[i]]+2;
				q[++totq]=j;
				if(apr2[j]){
					cout<<m1-1+dis[j]+m2-1;
					return 0;
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：jijidawang (赞：2)

管理让我用中文句点结束句子。

找到 $\{x\}$ 和 $\{y\}$ 的最长公共子串 $\{S\}$，若 $\{S\}$ 非空那么答案显然就是 $p+q-2|S|$，就是将 $\{x\}$ 先删到 $\{S\}$ 再加回来。

若 $\{S\}$ 为空，贪心地考虑，则一定是把 $\{x\}$ 删成只剩一个数然后用一些操作让它变成 $\{y\}$ 的子串然后加回去。

考虑对于所有 $i$，连边 $a_i\leftrightarrow a_{i+1}$，则问题变成 在 $\{x\}$ 和 $\{y\}$ 中分别选两个点 $u,v$，使它们之间的最短路最小。

这个多源~~汇~~ BFS 即可，于是问题已经被解决了。

复杂度瓶颈在求最长公共子串上，如果使用高级做法可以做到 $\Theta(n)$。

如果只用简单字符串算法可以用二分长度 Hash 判定，可以做到 $\Theta(n\log n)$，足够通过本题了。还有这题卡单 Hash，必须双 Hash 才能过，[Code](https://atcoder.jp/contests/arc151/submissions/36199618)。

---

## 作者：Purslane (赞：1)

# Solution

WC 2024 第一课堂讲的题。纪念一下，并且补上贪心的一些证明。

理论 1：如果题目中 $P$ 和 $Q$ 有非空公共子串，那么我们的策略是：选取所有非空公共子串中最长的那一个（记为 $S$），现将 $P$ 缩成 $S$，再扩展为 $Q$，此时答案是 $|P| + |Q| - 2 |S|$。

证明：很显然，这个过程是合法的。下面证明所有合法的过程所需要的代价都不小于这个值。这是因为，考虑 $P$ 变成 $Q$ 的过程中，没有被修改的那一部分，它显然是 $P$ 和 $Q$ 的公共子串，设长度为 $len$。则 $P$ 中这个“不变部分”的前面和后面的字符都得被删除之后重新加入正确的。这样你至少需要 $|P| + |Q| - 2 len$ 次操作，显然不小于 $|P|+|Q| - 2|S|$。

理论 2：如果 $P$ 和 $Q$ 不存在任何相同的字符，那么最优策略是，把 $P$ 缩成一个字符，然后不断的在序列中利用两次代价变成另外一个字符（就是扩展到相邻的一位，然后删掉原有的部分），直到变成 $Q$ 中的一个字符，然后扩展为 $Q$。

证明：我们依次论述每一步都是必须且最优的。首先，由于 $P$ 和 $Q$ 没有任何交集，所以我们必定要把 $P$ 中每个字母都删掉，那么必定有一个时刻会删成只剩一个。而考虑我们不断找相邻字符有一种“跳跃”的感觉。如果你带着更多的，最终也没有用的字符在“跳跃”，会使你的行动受到限制，不能到达更多位置。所以我们每次都会把冗余的字符全给删掉。这是很合理的。

------

理论 2 的实现只需用非常平凡的最短路就可以了。

那么理论 1 如何找到“最长非空子串”的长度呢？

~~你可以直接建 SAM。~~ 我比较懒，直接二分 + 哈希了。

---

## 作者：tribool4_in (赞：1)

首先观察样例可以发现，如果 $X$ 和 $Y$ 存在公共字符，那么令其最长公共子串为 $S$，那么答案就是 $|X|+|Y|-2|S|$，方法显然就是把 $X$ 先删成 $S$ 再变成 $Y$。

如果不存在公共字符，即 $X$ 中的字符都不在 $Y$ 出现。因此最优方法显然是把 $X$ 删至一个字符 $c$，然后通过这个字符在 $A$ 中变换变成某个 $Y$ 中的字符然后再扩展。具体的，考虑令 $A_i=c$，则可以通过两步将 $c$ 变为 $A_{i-1}$ 或 $A_{i+1}$。于是考虑建图，将“字符”作为点，然后在 $A_i$ 和 $A_{i+1}$ 之间连边（注意是“字符”之间，因此连出来的不是链）。然后将 $X$ 中的字符作为起始点跑一遍 bfs，然后取 $Y$ 中字符的最短距离 $d$，答案就是 $|X|-1+|Y|-1+2d$。

至于求最长公共子串，SAM 经典应用，不过感觉二分+哈希更加优美。单哈希能过。

查询写代码时的精神状态。

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N = 2e5 + 10;
const ull base = 1e9 + 7;
int n, x, y, a[N], p[N], q[N], d[N];
bool vis[N];
ull pw[N], hp[N], hq[N];
vector<int> G[N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    [&]() {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        cin >> x;
        for (int i = 1; i <= x; i++) cin >> p[i];
        cin >> y;
        for (int i = 1; i <= y; i++) cin >> q[i];
        pw[0] = 1;
        for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * base;
        for (int i = 1; i <= x; i++) hp[i] = hp[i - 1] * base + p[i];
        for (int i = 1; i <= y; i++) hq[i] = hq[i - 1] * base + q[i];
    }();
    auto Hsp = [&](int l, int r) -> ull { return hp[r] - hp[l - 1] * pw[r - l + 1]; };
    auto Hsq = [&](int l, int r) -> ull { return hq[r] - hq[l - 1] * pw[r - l + 1]; };
    auto check = [&](int mid) -> bool {
        unordered_set<ull> st;
        for (int i = 1; i + mid - 1 <= x; i++) st.insert(Hsp(i, i + mid - 1));
        for (int i = 1; i + mid - 1 <= y; i++)
            if (st.count(Hsq(i, i + mid - 1))) return 1;
        return 0;
    };
    int lS = [&]() -> int {
        int l = 1, r = min(x, y), ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        return ans;
    }();
    if (lS) {
        cout << x + y - 2 * lS << '\n';
        return 0;
    }
    auto add_edge = [&](int u, int v) { G[u].push_back(v), G[v].push_back(u); };
    [&]() {
        for (int i = 1; i < n; i++) add_edge(a[i], a[i + 1]);
        queue<int> que;
        for (int i = 1; i <= x; i++) que.push(p[i]), d[p[i]] = 0, vis[p[i]] = 1;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto v : G[u]) {
                if (vis[v]) continue;
                d[v] = d[u] + 1, vis[v] = 1;
                que.push(v);
            }
        }
        int minn = d[q[1]];
        for (int i = 2; i <= y; i++) minn = min(minn, d[q[i]]);
        cout << x + y - 2 + minn * 2 << '\n';
    }();
    return 0;
}
```

---

## 作者：Leasier (赞：1)

前置芝士：[SAM](https://oi-wiki.org/string/sam/)

先不考虑非空，不难发现最优方案为：

- 从 $x$ 开始在开头末尾删掉若干数得到 $LCS(x, y)$。
- 从 $LCS(x, y)$ 开始在开头末尾加上若干数得到 $y$。

令 $k = |LCS(x, y)|$，则答案为 $p + q - 2k$。

现在考虑加上非空的限制。在 $k > 0$ 时无影响，现在我们只需要考虑 $k = 0$ 的情况。

我们需要在 $x$ 中选一个数保留，找到 $a$ 中离它最近的 $y$ 中的一个数，然后依次加删得到那个数即可。

次数直接通过 bfs 求出即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <iostream>
#include <map>
#include <queue>
#include <cstdio>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

int lst = 1, id = 1, cnt = 0;
int a[200007], x[200007], len[400007], fa[400007], y[200007], dis[200007], head[200007];
Edge edge[400007];
queue<int> que;
map<int, int> mp[400007];

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		dis[i] = 0x7fffffff;
	}
}

inline void insert(int ch){
	int u = lst, v = lst = ++id;
	len[v] = len[u] + 1;
	while (u != 0 && !mp[u].count(ch)){
		mp[u][ch] = v;
		u = fa[u];
	}
	if (u == 0){
		fa[v] = 1;
		return;
	}
	int w = mp[u][ch];
	if (len[w] == len[u] + 1){
		fa[v] = w;
		return;
	}
	int x = ++id;
	len[x] = len[u] + 1;
	fa[x] = fa[w];
	fa[v] = fa[w] = x;
	mp[x] = mp[w];
	while (!mp[u].count(ch) || mp[u][ch] == w){
		mp[u][ch] = x;
		u = fa[u];
	}
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

int main(){
	int n, p, q, lcs = 0;
	scanf("%d", &n);
	for (register int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &p);
	for (register int i = 1; i <= p; i++){
		scanf("%d", &x[i]);
		insert(x[i]);
	}
	scanf("%d", &q);
	for (register int i = 1, j = 1, k = 0; i <= q; i++){
		scanf("%d", &y[i]);
		if (mp[j].count(y[i])){
			j = mp[j][y[i]];
			k++;
		} else {
			while (j != 0 && !mp[j].count(y[i])) j = fa[j];
			if (j == 0){
				j = 1;
				k = 0;
			} else {
				k = len[j] + 1;
				j = mp[j][y[i]];
			}
		}
		if (lcs < k) lcs = k;
	}
	if (lcs > 0){
		cout << p + q - lcs * 2;
		return 0;
	}
	int min_val = 0x7fffffff;
	init(n);
	for (register int i = 1; i < n; i++){
		int ii = i + 1;
		add_edge(a[i], a[ii]);
		add_edge(a[ii], a[i]);
	}
	for (register int i = 1; i <= p; i++){
		if (dis[x[i]] == 0x7fffffff){
			dis[x[i]] = 0;
			que.push(x[i]);
		}
	}
	while (!que.empty()){
		int cur = que.front(), dis_i = dis[cur] + 1;
		que.pop();
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (dis[x] == 0x7fffffff){
				dis[x] = dis_i;
				que.push(x);
			}
		}
	}
	for (register int i = 1; i <= q; i++){
		min_val = min(min_val, dis[y[i]]);
	}
	cout << p + q + (min_val - 1) * 2;
	return 0;
}
```

---

## 作者：littlez_meow (赞：0)

前置知识：SAM。

[题目指路](https://www.luogu.com.cn/problem/AT_arc151_e)。

## 思路

考虑贪心。我们找出 $X$ 和 $Y$ 的最长公共子串 $T$，将 $X$ 删掉头尾变成 $T$，再加回来 $Y$ 的头尾即可。

此时的答案为 $p+q-2|T|$。

然而，原题中限制了 $X$ 不能删至空。如果 $|T|=0$，就吗，没有办法删。

既然没有非空公共子串，把 $X$ 先删成一个字符肯定是最优的。

然后，每次可以在开头或结尾加一个字符，再把原来的字符删掉，就实现了将 $X$ 中一个字符和另一个字符的转化。只要将 $X$ 中的那一个字符变成 $Y$ 中的一个字符即可。

我们发现，能加的字符只能是在 $A$ 上与原字符相邻的字符。将每个字符建点，$A$ 上相邻字符连边，转化次数就为最短路，多源 bfs 就行。

设最短路长为 $d$，由于每次转化要加一个再删一个，答案为 $p+q+2d-2$。

最后简述一下 SAM 如何求最长公共子串。

我们发现 SAM 上 parent tree 的结构很像 AC 自动机 fail 树。考虑对一个串建 SAM，另一个串丢上去跑匹配。

初始时，当前节点为 $1$，匹配长度为 $0$。

如果当前节点的后继存在当前字符，就走上去，匹配长度加 $1$，当前字符移到下一个。

否则，匹配长度减 $1$，跳到后缀链接指向的点，继续看后继是否存在当前字符。

最长公共子串长度即为匹配长度的最大值。

## 代码

由于本题字符集非常大，存后继需要用 map 或者哈希表。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
using namespace std;
using namespace __gnu_pbds;
const int MAXN=2e5+1;
int n,p,q;
int a[MAXN],x[MAXN],y[MAXN];
int cnt=1,now=1;
int fa[MAXN<<1],len[MAXN<<1];
gp_hash_table<int,int>nxt[MAXN<<1];
inline void add_char(int ch){
	int p=now,np=now=++cnt;
	for(;p&&!nxt[p][ch];p=fa[p]) nxt[p][ch]=np;
	len[np]=len[p]+1;
	if(!p) fa[np]=1;
	else{
		int q=nxt[p][ch];
		if(len[q]==len[p]+1) fa[np]=q;
		else{
			int nq=++cnt;
			fa[nq]=fa[q];
			len[nq]=len[p]+1;
			nxt[nq]=nxt[q];
			fa[np]=fa[q]=nq;
			for(;p&&nxt[p][ch]==q;p=fa[p]) nxt[p][ch]=nq;
		}
	}
	return;
} 
vector<int>g[MAXN];
int dis[MAXN];
inline void bfs(){
	memset(dis,0x3f,sizeof(dis));
	queue<int>qu;
	F(i,1,p) dis[x[i]]=0,qu.push(x[i]);
	while(!qu.empty()){
		int now=qu.front();
		qu.pop();
		for(int i:g[now]){
			if(dis[i]<=dis[now]+1) continue;
			dis[i]=dis[now]+1;
			qu.push(i);
		}
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	F(i,1,n) cin>>a[i];
	cin>>p;
	F(i,1,p) cin>>x[i],add_char(x[i]);
	cin>>q;
	int now(1),l(0),mx(0);
	F(i,1,q){
		cin>>y[i];
		while(1){
			if(nxt[now].find(y[i])!=nxt[now].end()){
				now=nxt[now][y[i]],++l;
				mx=max(mx,l);
				break;
			}
			if(!l) break;
			--l;
			if(l==len[fa[now]]) now=fa[now];
		}
	}
	if(mx) cout<<p+q-2*mx;
	else{
		F(i,1,n-1) g[a[i]].push_back(a[i+1]),g[a[i+1]].push_back(a[i]);
		bfs();
		int d(0x7fffffff);
		F(i,1,q) d=min(d,dis[y[i]]);
		cout<<p+q+2*d-2;
	}
	return 0;
}
```

---

## 作者：Rainy7 (赞：0)

### 前言

更好的阅读体验：[Link](https://www.cnblogs.com/Rainy7/p/solution-at-arc151e.html)。

### 题解

先考虑如果 $X,Y$ 有公共字串的情况。不妨设 $X,Y$ 的最长公共子串为 $S$。

于是显然有一种方法，先将 $X$ 一直删，直到剩下 $S$，然后再添加补成 $Y$，这样操作数是 $|X| + |Y| - 2 |S|$。

求最长公共子串可以用 SA，复杂度 $\mathcal{O}(n \log n)$。

当然也可以不用 SA。考虑哈希，然后二分一个长度，枚举 $X$ 该长度的子串，然后用 `map` 存下 $Y$，匹配即可。复杂度 $\mathcal{O}(n \log^2 n)$。

然后考虑没有公共字串的情况。这意味着 $X,Y$ 没有相同字符。

有一个贪心。

>如果 $X$ 和 $Y$ 没有公共字串，并且 $|X| \ge 2$ 时，优先执行删除操作一定不劣。

根据这个贪心，我们可以一直删 $X$，直到 $|X|=1$，然后再加一个字符。如果依然没有公共串，那么就再删一个字符。

于是当 $X,Y$ 有公共字串的时候，一定是长度为 $1$ 的串。那么有公共串后就变成上面那个问题，答案为 $|X|+|Y|-2$。

然后问题就是最后选哪个字符为公共串。考虑建图，对于 $A$，将相邻的两个点连一条边权为 $1$ 的边。于是问题就是以 $A$ 中所有出现在 $X$ 的字符为起点，以 $A$ 中所有出现在 $Y$ 中的字符为终点，求最短路。直接 bfs 即可。

最短路跑出来的最近的公共字符点中的路径，是要先加进来再删掉的，所以操作数为路径长度的 $2$ 倍。

那么为什么这个贪心是正确的？

因为不存在公共串，所以最开始出现在 $|X|$ 的串中的字符一定是要被删掉的。然后我们会找到一个最近的公共字符的位置 $p$，即使我们先不删除 $p$ 到原先串之间的路径，之后也需要删除到只剩下公共串，也就是位置 $p$。

但是否会出现串到位置 $p$ 之间的字符出现，先被删，再加进来搭路到 $p$，再删掉的情况？可以发现，如果存在这种情况，那么这个操作数一定不是最短路径。

复杂度 $\mathcal{O}(n \log n)$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int N=4e5+5;
struct edge{
	int v,nx;
}e[N<<1];
int n,nb,nc,cnt,a[N],b[N],c[N],s[N],sa[N],height[N],rk[N];
int len,ans,ne,f[N],deep[N];
bool vb[N],vc[N];
queue<int> q;
void SA()
{	static int m=n+1,x[N],y[N],cc[N];
	for(int i=0;i<=max(m,cnt);i++)x[i]=y[i]=cc[i]=0;
	for(int i=1;i<=cnt;i++)x[i]=s[i],cc[x[i]]++;
	for(int i=1;i<=m;i++)cc[i]+=cc[i-1];
	for(int i=cnt;i>=1;i--)sa[cc[x[i]]--]=i;
	for(int k=1;k<=cnt;k<<=1)
	{	int num=0;
		for(int i=cnt-k+1;i<=cnt;i++)y[++num]=i;
		for(int i=1;i<=cnt;i++)
			if(sa[i]>k)y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++)cc[i]=0;
		for(int i=1;i<=cnt;i++)cc[x[i]]++;
		for(int i=2;i<=m;i++)cc[i]+=cc[i-1];
		for(int i=cnt;i>=1;i--)sa[cc[x[y[i]]]--]=y[i],y[i]=0;
		swap(x,y),num=1,x[sa[1]]=1;
		for(int i=2;i<=cnt;i++)
		{	if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])x[sa[i]]=num;
			else x[sa[i]]=++num;
		}
		if(num==cnt)break;
		m=num;
	}
}
void LCP()
{	int k=0;
	for(int i=1;i<=cnt;i++)rk[sa[i]]=i;
	for(int i=1;i<=cnt;i++)
	{	if(rk[i]==1)continue;
		if(k)k--;
		int j=sa[rk[i]-1];
		while(i+k<=cnt&&j+k<=cnt&&s[i+k]==s[j+k])k++;
		height[rk[i]]=k;
	}
}
int solve()
{	int res=0;
	for(int i=2;i<=cnt;i++)
		if((sa[i-1]<=nb&&sa[i]>nb)||(sa[i-1]>nb&&sa[i]<=nb))res=max(res,height[i]);
	return res;
}
void read(int u,int v)
{	e[++ne].v=v;
	e[ne].nx=f[u];
	f[u]=ne;
}
int main()
{	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&nb);
	for(int i=1;i<=nb;i++)
	{	scanf("%d",&b[i]);
		s[++cnt]=b[i],vb[b[i]]=1;
	}
	s[++cnt]=n+1; 
	scanf("%d",&nc);
	for(int i=1;i<=nc;i++)
	{	scanf("%d",&c[i]);
		s[++cnt]=c[i],vc[c[i]]=1;
	}
	SA(),LCP(),len=solve(),ans=n;
	if(len>0){printf("%d\n",nb+nc-(len<<1));return 0;}
	for(int i=1;i<n;i++)read(a[i],a[i+1]),read(a[i+1],a[i]);
	for(int i=1;i<=n;i++)
		if(vb[i])q.push(i),deep[i]=1;
	while(!q.empty())
	{	int u=q.front();q.pop();
		if(vc[u]){ans=deep[u]-1;break;}
		for(int i=f[u];i;i=e[i].nx)
		{	int v=e[i].v;
			if(!deep[v])q.push(v),deep[v]=deep[u]+1;
		}
	}
	printf("%d\n",(ans<<1)+nb+nc-2);
	return 0;
}
```


---

## 作者：OtoriEmu (赞：0)

现在 ARC E 题都得意识到这个特殊的 case 才能做了，可以看出来出题人是故意的，很讨厌。

首先如果两个串有公共的子串，那么我们可以找到最长的那个子串，$s$ 先变成那个子串再变成 $t$，这部分的正确性显然。

接下来是没有公共子串的情况。注意到题目要求 $s$ 时刻是非空的子串，因此缩到 $0$ 是不被允许的。有一个简单的想法是，将 $s$ 缩成一个字符，向 $t$ 中有的字符扩展，扩展到存在公共子串之后删除之前的所有字符。但是这并不优秀，注意到对于一个 $s$，我们可以任选一个原串中出现这个子串的位置扩展，因此这样不太科学。

分析什么时候能选择尽量多的位置扩展，可以发现只有一个字符的时候能扩展的位置是最多的。那么策略是尽量时刻保持只有一个字符，每次选择一个字符扩展并删除先前的字符，直到变成 $t$ 中出现的字符。

注意到可以对相同的字符建虚点，其间权值为 $0$，扩展到相邻的点权值为 $1$，则问题描述成了一个最短路问题，可以用 01-BFS 解决。

当然我怎么写 01-BFS 都是挂的，于是就写了 Dijkstra，哇哈哈！

[评测链接](https://atcoder.jp/contests/arc151/submissions/35839124)。

---

