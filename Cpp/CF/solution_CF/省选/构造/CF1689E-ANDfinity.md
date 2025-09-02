# ANDfinity

## 题目描述

从计算机科学系毕业后， Vlad 被奖与一个由 $n$ 个非负整数组成的数组 $a_1,a_2, \dots , a_n$。他很自然地想到构建一个有 $n$ 个点，编号为 $1,2,\dots,n$ 的图。点 $i$ 和 $j$ 之间有边当且仅当 $a_i\& a_j >0$，其中 $\&$ 表示按位与。

Vlad 希望这张图连通，虽然最初可能不是这样。为了使图连通，他可以对这个数组做下列两种操作：

1. 选择一个元素 $a_i$ 并将它加一。
2. 选择一个元素 $a_i$ 并将它减一（仅能在 $a_i>0$ 时做此操作）。

可以证明存在一个有穷的操作序列使得这张图连通。所以，你能帮 Vlad 找到最少的可能操作数以达成这个目标并给出操作方法吗？

## 样例 #1

### 输入

```
4
5
1 2 3 4 5
2
0 2
2
3 12
4
3 0 0 0```

### 输出

```
0
1 2 3 4 5
2
2 2
1
3 11
3
3 1 1 1```

# 题解

## 作者：dead_X (赞：21)

## 思路
首先先把所有 $0$ 变成 $1$。

然后我们发现答案不大于 $2$，一种具体方式如下：

- 考虑所有 $\text{lowbit}$ 最高的数。
  
- 如果只有一个，将它 $-1$。
  
- 如果不止一个，随便找一个 $+1$，随便找一个 $-1$。
  

于是枚举所有一步操作的情况一一检验即可，时间复杂度 Soft $O(n^2)$，具体看实现。
## 代码
```cpp
// Problem: E. ANDfinity
// Contest: Codeforces - Codeforces Round #798 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1689/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//回家？我没有家可以回，我没有退路。
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[2003],n,ans,x,s;
bool vis[2003];
int fa[2003];
void dfs(int x)
{
	vis[x]=1,++s;
	for(int i=1; i<=n; ++i) 
		if((a[i]&a[x])&&!vis[i])
			dfs(i);
	return ;
}
int L(int x){return x&(-x);}
int find(int x){return fa[x]==x?x:(fa[x]=find(fa[x]));}
bool chk()
{
	for(int i=1; i<=n; ++i) fa[i]=i;
	for(int s=1; s<=536870912; s<<=1)
	{
		int fir=n;
		for(int i=1; fir==n&&i<n; ++i) if(a[i]&s) fir=i;
		int A=find(fir);
		for(int i=fir+1; i<=n; ++i) if(a[i]&s) fa[find(i)]=A;
	}
	for(int i=2; i<=n; ++i) if(find(i)!=find(1)) return 0;
	return 1;
}
signed main()
{
	for(int T=read();T--;)
	{
		n=read(),ans=x=s=0;
		for(int i=1; i<=n; ++i) vis[i]=0;
		for(int i=1; i<=n; ++i)
			(!(a[i]=read()))&&(++ans,a[i]=1),
			x=max(x,L(a[i]));
		dfs(1);
		if(s==n) 
		{
			printf("%d\n",ans);
			for(int i=1; i<=n; ++i) printf("%d ",a[i]);
			puts("");
		}
		else
		{
			int ovo=1;
			for(int i=1; i<=n; ++i)
			{
				//check: --a[i]
				--a[i];
				if(chk()){ovo=0;break;}
				//check: ++a[i]
				++a[i],++a[i];
				if(chk()){ovo=0;break;}
				--a[i];
			}
			if(!ovo)
			{
				printf("%d\n",ans+1);
				for(int i=1; i<=n; ++i) printf("%d ",a[i]);
				puts("");
				continue;
			}
			for(int i=1; i<=n; ++i) 
				if(L(a[i])==x)
				{
					if(ovo) 
						--a[i],ovo=0;
					else
					{
						++a[i];
						break;
					}
				}
			printf("%d\n",ans+2);
			for(int i=1; i<=n; ++i) printf("%d ",a[i]);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：10)

$O(30n)$（$30$ 为二进制位数）暴虐标算，喜提 CF 最优解 15 ms（（（

显然地，我们把 $\{a\}$ 中所有 $0$ 全都 $+1$ 变成 $1$。

接下来我们只考虑无 $0$ 串的答案。

我们设值的 $\text{lowbit}$ 最大的那些元素集合为 $S$。

我们可以保证答案 $\le 2$，证明如下：

* 若 $|S|=1$，则将这个元素 $-1$ 后必然全连通。

* 若 $|S|>1$，则将其中一个 $-1$，另一个 $+1$，必然连通。

（这里比较简略，具体请移步别的题解）

所以，我们得到了算法流程：

1. 先通过枚举每个二进制位来 $O(30n)$ 判断是否已经连通。

2. 否则，我们遍历 $S$ 中的每一个元素，尝试 $+1$ 和 $-1$ 是否能连通。

3. 否则，我们确定答案 $=2$，随便在 $S$ 中一个 $+1$，一个 $-1$ 即可。

再具体一点：

第一步时，我们枚举二进制的每一位，然后并查集合并这一位为 $1$ 的元素。

第二步前半部分，我们判断第一步结束后的并查集数量。若 $=2$，则有可能 $+1$ 后连通。我们判断是否有奇数出现在非 $|S|$ 出现的并查集里即可。

第二步后半部分，由于这个 $S$ 中 $-1$ 的元素能集结所有不在 $S$ 中的元素，我们只要判断这个元素 $-1$ 后是否能连通 $S$ 中其他元素。我们将非 $S$ 元素 $\text{bitwise or}$ 起来，以及 $S$ 中（按下标）前缀与后缀也 $\text{or}$ 起来。然后对于每一个 $S$ 中元素 $-1$ 是否可行就可以 $O(1)$ 判断了，具体看代码。

精简但不可观的代码：

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define N 2022
int n,a[N],ans,f[N],cnt,mx,qwq;
int pre[N],suf[N],pos[N],tot;
inline int low(int x){ return x&(-x); }
inline int gf(int x){ return x==f[x]?x:f[x]=gf(f[x]); }
inline void merge(int x,int y){
	x=gf(x),y=gf(y);
	if(x!=y) cnt--,f[x]=y;
}
void work(){
	int x;
	ans=0;
	For(i,1,n) if(a[i]==0) a[i]=1,ans++;
	cnt=n;
	For(i,1,n) f[i]=i;
	For(j,0,29){
		x=0;
		For(i,1,n) if(a[i]&(1<<j)){
			if(x==0) x=i;
			else merge(x,i);
		}
	}
	if(cnt==1) return ;
	ans++;
	mx=tot=qwq=0;
	For(i,1,n) mx=max(mx,low(a[i]));
	For(i,1,n) if(low(a[i])==mx) pos[++tot]=i; else qwq|=a[i];
	if(cnt==2){
		x=gf(pos[1]);
		For(i,1,n) if(gf(i)!=x && a[i]&1){
			a[pos[1]]++;
			return ;
		}
	}
	if(tot==1){
		a[pos[1]]--;
		return ;
	}
	pre[0]=suf[tot+1]=0;
	For(i,1,tot) pre[i]=pre[i-1]|a[pos[i]];
	Rof(i,tot,1) suf[i]=suf[i+1]|a[pos[i]];
	For(i,1,tot) if((pre[i-1]|suf[i+1])&((a[pos[i]]^mx)|qwq)){
		a[pos[i]]--;
		return ;
	}
	ans++;
	a[pos[2]]++;
	a[pos[1]]--;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		For(i,1,n) scanf("%d",a+i);
		work();
		printf("%d\n",ans);
		For(i,1,n) printf("%d ",a[i]); puts("");
	}
return 0;}
```

---

## 作者：冬天的雨 (赞：9)

昨天教练用这玩意出了模拟赛

考场上剩下三分钟的时候发现了神秘性质切掉了

切完直接冲到机房外开骂：什么诡异性质（


------------

首先我们分析样例

对于第一组样例， ` 1 2 3 4 5 `

我们可以发现它其实本身就是联通的，因此不需要操作

然后看第五组样例， ` 3 0 0 0 `

输出是 ` 3 1 1 1 ` ，说明它把所有的 0 都加了一

那么我们自然可以想到先把所有 0 加一再去判断是否连通


------------


接着看到第二组样例， ` 0 2 `

将 0 变成 1 后只需要将 2 减去一或者将 1 加上一就可以保证连通

第三组样例同理，把 12 减去一即可

一般地，我们可以想到，对于一组起初不连通的数据，可以找出拥有最大的 $\operatorname{lowbit}$ 的数字，将这个数字减一

它减一后所有的低于它的 $\operatorname{lowbit}$ 的数位都会变成 1

这样，因为它的 $\operatorname{lowbit}$ 是最大的，它减一后的数字必然有一位与其它数字中的某一位做与运算后不为 0

举个例子，对于 ` 8 4 2 3 ` ，显然的，8 的 $\operatorname{lowbit}$ 值是最大的

我们让 8 减去一，然后 $ ( 1000 )_2 $ 变成了 $ (111)_2 $

它与 $ 4 = (100)_2$，$ 2 = (10)_2 $，$ 3 = (11)_2 $ 都有共同的一位为 1

整张图便连通了

这样我们就分析完了样例，AC 似乎就在眼前……吗？


------------


然鹅就这样写是会挂的

不妨考虑如下的一组数据 ` 8 8 1 `

如果将第一个 8 减一，数据变为 $(111)_2$，$(1000)_2$，$(1)_2$

这样图是不连通的，如果再将第二个 8 减一就错了

因为我们很容易发现将某个 8 加一就可以变成 $(1001)_2$，$(1000)_2$，$(1)_2$ ，这样图是连通的

所以我们可以得出结论，可以尝试把某个点加一或者减一，然后判断连通性


------------


但是这样还是不完美，考虑下一组数据 `2 4 12` ，也就是 $(10)_2$，$(100)_2$，$(1100)_2$

4 和 12 的 $\operatorname{lowbit}$ 值都是 4

显然的让某个数加一或者让某个数减一都无法保证连通（ 可以自己试一试 ）

所以我们让一个数加一，另一个数减一，数据变为 $(10)_2$，$(11)_2$，$(1101)_2$

这样终于可以保证连通了

然后注意操作数要加上一开始初始化 0 为 1 的操作数



------------

关于如何判断连通性，可以考虑维护一些边，每次找到两个相邻的为 1 的位连边

比如 $(101100)_2$，我们考虑给第一位和第三位，第三位和第四位连双向边

这样只要遍历出边就可以找到所有 “这一位是一的数” 的所有为 1 的数位，再去扫这几位的出边

这样可以一直递归下去打下标记，最后再判断是否连通即可

说起来很艰难，具体见代码

```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#define int long long
#define WR WinterRain
using namespace std;
const int WR=5010,mod=1e9+7;
int t;
int n,ans,a[WR];
int bit[WR/50][WR];
bool flag[WR/50];
int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-') w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=(s<<3)+(s<<1)+ch-48;
        ch=getchar();
    }
    return s*w;
}
void tag(int u){
    if(flag[u]) return;
    flag[u]=true;
    for(int i=1;i<=bit[u][0];i++){
        tag(bit[u][i]);
    }
}
bool judge(){
    int s=0;
    memset(flag,false,sizeof(flag));
    memset(bit,0,sizeof(bit));
    for(int i=1;i<=n;i++){
        if(!a[i]) return false;
        s|=a[i];//存一下出现过的位数
    }
    for(int i=1;i<=n;i++){
        int pre=-1;
        for(int j=0;j<=30;j++){
            if(a[i]&(1<<j)){
                if(pre!=-1){
                    bit[pre][0]++,bit[j][0]++;
                    bit[pre][bit[pre][0]]=j,bit[j][bit[j][0]]=pre;//这里我们用邻接矩阵存出边
                }
                pre=j;
            }
        }
    }
    for(int i=0;i<=30;i++){
        if(s&(1<<i)){
            tag(i);//扫一遍就够了
            break;
        }
    }
    for(int i=0;i<=30;i++){
        if((s&(1<<i))&&!flag[i]) return false;
        //如果发现这一位并不连通但是出现了这一位，那么图就不连通
    }
    return true;
}
int lowbit(int x){
    return x&(-x);
}
signed main(){
    t=read();
    while(t--){
        n=read();
        bool tag=false;
        for(int i=1;i<=n;i++) a[i]=read();
        ans=0;
        for(int i=1;i<=n;i++){
            if(!a[i]) ans++,a[i]++;
        }
        if(judge()){
            printf("%lld\n",ans);
            for(int i=1;i<=n;i++){
                printf("%lld ",a[i]);
            }
            printf("\n");
            continue;
        }
        for(int i=1;i<=n;i++){
            a[i]--;
            if(judge()){
                printf("%lld\n",ans+1);
                for(int j=1;j<=n;j++){
                    printf("%lld ",a[j]);
                }
                printf("\n");
                tag=true;
                break;
            }
            a[i]++;
        }
        if(tag) continue;
        for(int i=1;i<=n;i++){
            a[i]++;
            if(judge()){
                printf("%lld\n",ans+1);
                for(int j=1;j<=n;j++){
                    printf("%lld ",a[j]);
                }
                printf("\n");
                tag=true;
                break;
            }
            a[i]--;
        }
        if(tag) continue;
        int low=0;
        for(int i=1;i<=n;i++) low=max(low,lowbit(a[i]));
        for(int i=1;i<=n;i++){
            if(lowbit(a[i])==low){
                a[i]--;
                break;
            }
        }
        for(int i=1;i<=n;i++){
            if(lowbit(a[i])==low){
                a[i]++;
                break;
            }
        }
        printf("%lld\n",ans+2);
        for(int i=1;i<=n;i++){
            printf("%lld ",a[i]);
        }
        printf("\n");
    }
    return 0;
}
```


---

## 作者：Muel_imj (赞：5)

## CF1689E ANDfinity 题解

[luogu](https://www.luogu.com.cn/problem/CF1689E)

[更差的阅读体验](https://www.cnblogs.com/muel-imj/p/16379149.html)

对于图的连通性，可以用并查集维护（合并成功 $n-1$ 次，或者一个集合大小为 $n$，则整张图已经连通）。

首先有很显然：所有的 $0$ 都要变成 $1$，因为 $0$ 和任何数按位与都是 $0$。

此时如果整张图已经连通，那么直接结束。

不连通的话呢？有个性质：**只通过对偶数的最多两次操作，便一定达成整张图连通**。

那么为了答案最优，对于一次操作，暴力扫就可以。两次操作的构造方式如下。

### 方法与证明：

首先所有奇数肯定在同一个连通块里，因为它们二进制形式的末尾是 $1$。这个连通块内也可能有偶数。

所以**除开包含奇数的连通块，其它零散的连通块肯定全是偶数**。

考虑加一和减一操作对一个偶数二进制形式的影响：

1. 加一则把偶数的末尾的 $0$ 变成 $1$；
2. 减一会把它的 `lowbit` 变成 $0$，后面的都变成 $1$。

可以看到，加一**只会加边不会删边**，而减一加的边可能更多但是**可能删边**。

注意第二条，贪心的想，可以把最大的 `lowbit` 对应的数减一，这样 `lowbit` 小于它的其它数都会与它连通，并且它们都和奇数连通块连通了。此时场上最多两个连通块，并且一个是包含奇数的连通块，另一个是 `lowbit` 全都是最大值的连通块，操作的数和此块可能断绝了联系。

同时可以发现，如果最大的 `lowbit` 只有一个，那么已经连通；如果不含奇数的连通块只有一个，通过加一操作就可以达成连通。这些在之前暴力枚举中已经解决。

如果此时还未整个连通，剩下一个无奇数连通块只要加一，根据前面的讨论，这样**只会加边**，而且它会带着这个连通块和那个奇数连通块连通，那么此时就达成了目标。

一次操作的已经暴力实现，两次操作的这样一定可以构造出来。

于是就证明完了。

丑陋的代码 qwq：
```cpp
#include<bits/stdc++.h>
#define EL puts("Elaina")
#define reg register int
typedef long long ll;
using namespace std;
inline char gc(){
    static char buf[1<<20],*p1,*p2;
    if(p1==p2){p1=buf,p2=buf+fread(buf,1,1<<20,stdin);if(p1==p2)return EOF;}
    return *p1++;
}
inline int read(){
    int x=0,f=1;char ch=gc();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=gc();
    return x;
}
const int maxn=2e3+3;
inline int lowbit(int x){return x&(-x);}
int n,a[maxn],ans,cnt;
struct dsu{
    int fa[maxn],rk[maxn],val[maxn];
    inline void init(int n){
        for(reg i=1;i<=n;++i)fa[i]=i,rk[i]=0,val[i]=a[i];
    }
    inline int find(int x){
        return fa[x]^x?fa[x]=find(fa[x]):x;
    }
    inline bool merge(int x,int y){
        x=find(x),y=find(y);
        if(x==y)return 0;
        if(rk[x]<rk[y])fa[x]=y,rk[y]=max(rk[y],rk[x]+1),val[y]|=val[x];
        else fa[y]=x,rk[x]=max(rk[x],rk[y]+1),val[x]|=val[y];
        return 1;
    }
    inline int value(int x){
        return val[find(x)];
    }
}S;
inline bool link(){
    cnt=0,S.init(n);
    for(reg i=1;i<=n;++i)
        for(reg j=1;j<i;++j)
            if(a[i]&a[j]){
                cnt+=S.merge(i,j);
                if(cnt==n-1)return 1;
            }
    return 0;
}
inline void overdesu(){
    printf("%d\n",ans);
    for(reg i=1;i<=n;++i)
        printf("%d ",a[i]);
    printf("\n");
}
inline void MyDearMomonts(){
    n=read(),ans=0,cnt=0;
    for(reg i=1;i<=n;++i){
        a[i]=read();
        if(!a[i])ans+=++a[i];
    }
    S.init(n);
    if(link()){overdesu();return;}
    for(reg i=1;i<=n;++i){
        a[i]++,ans++;
        if(link()){overdesu();return;}
        a[i]-=2;
        if(link()){overdesu();return;}
        a[i]++,ans--;
    }
    int hib=0;
    for(reg i=1;i<=n;++i)
        hib=max(hib,lowbit(a[i]));
    for(reg i=1;i<=n;++i)
        if(lowbit(a[i])==hib){
            a[i]--,ans++;
            if(link()){overdesu();return;}
            break;
        }
    for(reg i=1;i<=n;++i)
        if(!(S.value(i)&1)){
            a[i]++,ans++,overdesu();
            return;
        }
}
int main(){
    int T=read();
	while(T--)MyDearMomonts();
    return (0^0);
}
```

---

## 作者：hsfzLZH1 (赞：3)

## 题目大意

$t$ 组数据，每组数据给定一个长度为 $n$ 的 **非负** 数列 $a_i$ ，每次操作可以将一个位置上的值增加或减少 1 （不可减至负数）。若 $a_i \& a_j> 0$ 则 $i,j$ 两点间连一条边。求最小操作次数使得 $1,2,\ldots,n$ 全部连通，并输出最终数列。

若有多种方案，输出任意一种即可。

$1\le t\le 1000,2\le n\le 2000,0\le a_i<2^{30}$

## 解题思路

若 $a_i=0$ ，则 $i$ 不可能与任何点连通。所以我们先把所有 0 变成 1 。

对正数数列 $a_i$ ，我们发现我们可以用 **两步** 操作构造出一种可行的方案：先将 `lowbit` **最大** 的一个 $a_i$ 减 1 ，这样直接使该点与其他 `lowbit` 更小的点的连通。但这样可能出现一个问题：可能有其他 `lowbit` 相同的点操作后变得不与该点连通了。这个问题很容易解决，找到另一个 `lowbit` 相同的点，将其增加 1 ，这样恢复了该点原先的连接，所有点都连通了。

于是我们解题的思路变得很简单：判断是否可以零步（原图已经连通），是否可以一步，若都不行就两步。

### 零步

可用 $O(n\log a_i)$ 判断数列 $a_i$ 是否连通：枚举每个二进制位，将该位上有 1 的点连成一个连通块（每个点均与一个点相连），这样最多有 $O(n\log a_i)$ 条边，再判断图是否连通。

### 一步

有两种可能，增加 1 或减少 1 。

减少 1 ：鉴于本题 $n$ 的范围，可以枚举减少的数，再判断是否连通，时间复杂度 $O(n^2\log a_i)$ 。当然应该会有更优的图论做法。

增加 1 ：以上判断唯一考虑不到的就是原先有两个连通块，一个含有奇数一个全为偶数。只需将偶数连通块中的一个数增加 1 即可。

### 两步

方法同上。

总的时间复杂度为 $O(\sum n^2loga_i)$ 。

## 参考代码

这份代码用的是并查集判断是否连通，而且有点丑（

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2010;
int lowbit(int x){return x&(-x);}
int T,n,a[maxn],ans,b[maxn],f[maxn],lst,maxx,t,cur,q[40];
bool tf0,tf1;
int findp(int x){return f[x]?f[x]=findp(f[x]):x;}
void merge(int x,int y){x=findp(x);y=findp(y);if(x!=y)f[x]=y;}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);ans=0;tf0=tf1=false;
		for(int i=1;i<=n;i++){scanf("%d",a+i);if(!a[i])a[i]=1,ans++;{if(a[i]&1)tf1=true;else tf0=true;}}
		for(int i=1;i<=n;i++)f[i]=0;
		for(int i=1;i<=30;i++)//2^(i-1)
		{
			lst=0;
			for(int j=1;j<=n;j++)if(a[j]&(1<<(i-1))){if(lst)merge(lst,j);else lst=j;}
		}
		int cnt=0;
		for(int i=1;i<=n;i++)if(!f[i])cnt++;
		if(cnt==1){printf("%d\n",ans);for(int i=1;i<=n;i++)printf("%d ",a[i]);printf("\n");continue;}
		if(cnt==2){if(tf0&&tf1)
		{
			printf("%d\n",ans+1);
			int mq=0;for(int i=1;i<=n;i++)if(a[i]&1)mq=i;
			for(int i=1;i<=n;i++)if(findp(mq)!=findp(i)){a[i]++;break;}
			for(int i=1;i<=n;i++)printf("%d ",a[i]);printf("\n");
			continue;
		}}
		bool tf=false;
		for(int p=1;p<=n;p++)
		{
			a[p]--;
			for(int i=1;i<=n;i++)f[i]=0;
			for(int i=1;i<=30;i++)//2^(i-1)
			{
				lst=0;
				for(int j=1;j<=n;j++)if(a[j]&(1<<(i-1))){if(lst)merge(lst,j);else lst=j;}
			}
			int cnt=0;
			for(int i=1;i<=n;i++)if(!f[i])cnt++;
			if(cnt==1){tf=true;break;}
			a[p]++;
		}
		if(tf){printf("%d\n",ans+1);for(int i=1;i<=n;i++)printf("%d ",a[i]);printf("\n");continue;}
		maxx=1;t=lowbit(a[1]);
		for(int i=2;i<=n;i++)if(lowbit(a[i])>lowbit(a[maxx]))maxx=i,t=lowbit(a[i]);
		a[maxx]--;
		for(int i=1;i<=n;i++)f[i]=0;
		for(int i=1;i<=30;i++)//2^(i-1)
		{
			lst=0;
			for(int j=1;j<=n;j++)if(a[j]&(1<<(i-1))){if(lst)merge(lst,j);else lst=j;}
		}
		cnt=0;
		for(int i=1;i<=n;i++)if(!f[i])cnt++;
		for(int i=1;i<=n;i++)if(i!=maxx&&lowbit(a[i])==t){a[i]++;break;}
		printf("%d\n",ans+2);for(int i=1;i<=n;i++)printf("%d ",a[i]);printf("\n");continue;
	}
	return 0;
}
```

---

## 作者：AmamiyaYuuko (赞：1)

首先很蠢的是要先将所有的 $0$ 变为 $1$。

然后我们判断一下原图是否连通。

然后我们可以将每个 $a_i$ 进行 $+1 / -1$，判断图是否连通。

如果图还是不连通，那么答案就是 $2$，证明如下：

考虑原图的连通块，所有奇数必定在一个连通块里，剩下的连通块中一定全都是偶数。

我们把一个偶数加 $1$，将它的最后一位变为 $1$，而把一个偶数减 $1$ 则让它的 $\text{lowbit}$ 位变为 $0$，这之后的位都变为 $1$。

我们选出 $\text{lowbit}$ 最大的那一位减 $1$，实际上就让所有奇数和 $\text{lowbit}$ 比它小的数连通了，不难发现这样一定是最优的。

如果把 $\text{lowbit}$ 最大的这个数减 $1$ 后图仍然不连通，说明有多个 $\text{lowbit}$ 相同的数，这些数必然在一个连通块里，任取一个数加 $1$ 就能让这些数和奇数连通。

最后的问题就是如何判断图是否连通，一个很简单的做法是直接枚举点对，用并查集维护连通性，时间复杂度 $O(n^3 \log n)$（只有路径压缩）。看似过不了，没想到 CF 神机直接过了...

---

