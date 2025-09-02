# Basic Diplomacy

## 题目描述

Aleksey 有 $n$ 个朋友和 $m$ 天假期，每天他会选一个朋友和他一起玩团队游戏。而每天只有特定的朋友能和他玩。如果一个朋友被选了 $\left\lceil\dfrac{m}{2}\right\rceil$ 次，别的朋友就会吃醋。问是否存在一种方案使得没有朋友吃醋。

## 样例 #1

### 输入

```
2
4 6
1 1
2 1 2
3 1 2 3
4 1 2 3 4
2 2 3
1 3
2 2
1 1
1 1```

### 输出

```
YES
1 2 1 1 2 3 
NO```

# 题解

## 作者：灵茶山艾府 (赞：4)

考察出现次数最多的数 $x$。

先判断是否存在构造方案：若只能选 $x$ 的次数超过了 $\lceil\dfrac{m}{2}\rceil$，则必然无解，否则可以按如下方法构造：

若 $x$ 的出现次数超过了 $\lceil\dfrac{m}{2}\rceil$，那么可以选择 $\lceil\dfrac{m}{2}\rceil$ 个 $x$，剩下的数无论怎么选次数都不会超过 $\lceil\dfrac{m}{2}\rceil$。

若 $x$ 的出现次数不足 $\lceil\dfrac{m}{2}\rceil$，由于 $x$ 是出现次数最多的数，故任意一种选法都是符合要求的。

AC 代码：（Golang）

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var T, n, m, k, v int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n, &m)
		ans := make([]int, m)
		one := make([]int, n+1)
		pos := make([][]int, n+1)
		mx := 0
		for i := 0; i < m; i++ {
			Fscan(in, &k)
			for j := 0; j < k; j++ {
				Fscan(in, &v)
				if k == 1 {
					one[v]++
					ans[i] = v
				}
				pos[v] = append(pos[v], i)
				if len(pos[v]) > len(pos[mx]) {
					mx = v
				}
			}
		}
		c := one[mx]
		if c > (m+1)/2 {
			Fprintln(out, "NO")
			continue
		}
		for _, p := range pos[mx] {
			if c == (m+1)/2 {
				break
			}
			if ans[p] == 0 {
				ans[p] = mx
				c++
			}
		}
		for i, ps := range pos {
			if i != mx {
				for _, p := range ps {
					if ans[p] == 0 {
						ans[p] = i
					}
				}
			}
		}
		Fprintln(out, "YES")
		for _, v := range ans {
			Fprint(out, v, " ")
		}
		Fprintln(out)
	}
}
```

---

## 作者：tiger2005 (赞：3)

## 题意：

你要在 $M$ 天中玩一个游戏，每一天你的 $N$ 个朋友中会有几个有空，求出一种方案使得每个人被选到的天数不超过 $\left\lceil\dfrac{m}{2}\right\rceil$ 次，或者判断无解。

## 解法：

首先我们发现题目的要求是超过一半，那么我们只要保证最大的一个不超过就行。取出所有只能选择一个人的天数，并且提前计算这些天数中每个人出现的次数。如果有一个人的出现次数已经超过 $\left\lceil\dfrac{m}{2}\right\rceil$，那么直接输出 `NO`。否则每一次选择一个可以选的就行了。可以证明每次选择可以选的人，一定可以构造出一组解。

因为最强的限制肯定只有 1 到 2 个人（一天三个人的话删掉一个人会更加有可能达到无解的情况），如果是 2 个人的话，又可以证明出 `(1,2)` 最具有杀伤力（只有这个拿出来才可以让每一个人被选择$\left\lceil\dfrac{m}{2}\right\rceil$ 次，其他的都不行）。但是我们可以发现这种情况可以构造出来，所以就一定有解了(?)

所以只需要先统计后暴力。时间复杂度 $O(n+\sum{k_i})$

```cpp
// Problem      : A. Basic Diplomacy
// From         : Codeforces - Codeforces Round #709 (Div. 1, based on Technocup 2021 Final Round)
// URL          : https://codeforces.com/contest/1483/problem/A
// Memory Limit : 512 MB
// Time Limit   : 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
int T,N,M;
vector<vector<int> > A;
int m[100010];
int ans[100010];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&N,&M);
		A.clear();
		for(int i=1;i<=M;i++){
			int len;scanf("%d",&len);
			if(len==1){
				scanf("%d",&len);
				++m[len];ans[i]=len;
				A.push_back(vector<int>{len});
			}
			else{
				vector<int> rd;rd.clear();
				for(int j=0,a;j<len;j++){
					scanf("%d",&a);
					rd.push_back(a);
				}
				A.push_back(rd);
			}
		}
		bool flg=false;
		for(int i=1;i<=N;i++)
			if(m[i]>(M+1)/2)	flg=true;
		if(flg)	printf("NO\n");
		else{
			for(int i=1;i<=M;i++){
				if(A[i-1].size()==1)	continue;
				int p=0;
				while(m[A[i-1][p]]==(M+1)/2)	++p;
				++m[A[i-1][p]];ans[i]=A[i-1][p];
			}
			printf("YES\n");
			for(int i=1;i<=M;i++)	printf("%d ",ans[i]);
			printf("\n");
		}
		for(int i=1;i<=N;i++)	m[i]=0;
		for(int i=1;i<=M;i++)	ans[i]=0;
	}
	return 0;
}
```

---

## 作者：xuezhe (赞：2)

这个长得像个匹配的样子，直接建图跑网络流，场上似乎并没有被卡掉。

建源点 $S$，汇点 $T$，代表每个人的点 $1 \sim n$，代表每一天的点 $n+1 \sim n+m$。

源点向代表每个人的点连容量为 $\lceil \frac{m}{2} \rceil$ 的边，每个人向能玩的天连容量为 $1$ 的边，每一天向汇点连容量为 $1$ 的边。

直接跑个最大流就好了，如果最大流不满 $m$ 则无解，否则通过每条边的流量判断每一天哪个人会出来玩，就可以输出方案了。

```cpp
const int N(400005);
struct LnkNode{
    int v,w,nxt;
}edge[N<<2];
int etot,fst[N],cur[N];
void addedge_(int u,int v,int w){
    ++etot;
    edge[etot].v=v;
    edge[etot].w=w;
    edge[etot].nxt=fst[u];
    fst[u]=etot;
}
void addedge(int u,int v,int w){addedge_(u,v,w),addedge_(v,u,0);}

int _,n,m,c,S,T,to[N];

int d[N],q[N],Head,Tail;
bool bfs(){
    Head=Tail=0;
    memset(d+1,0x3f,c<<2);
    d[q[Tail++]=S]=0;
    while(Head<Tail){
        int x=q[Head++];
        for(int i=fst[x];i;i=edge[i].nxt){
            int &y=edge[i].v,&w=edge[i].w;
            if(w && d[y]>d[x]+1)
                d[q[Tail++]=y]=d[x]+1;
        }
    }
    return d[T]!=0x3f3f3f3f;
}
int dfs(int x,int f){
    if(x==T)
        return f;
    int r=f;
    for(int &i=cur[x];i;i=edge[i].nxt){
        int &y=edge[i].v,&w=edge[i].w;
        if(w && d[y]==d[x]+1){
            int t=dfs(y,min(w,r));
            edge[i].w-=t,edge[i^1].w+=t;
            if(!(r-=t))
                break;
        }
    }
    return f-r;
}

void fakemain(){
    Read(_);
    while(_--){
        Read(n),Read(m);
        etot=1,memset(fst+1,0,(c=n+m+2)<<2);
        S=n+m+1,T=n+m+2;
        for(int i=1;i<=m;++i){
            addedge(n+i,T,1);
            int k,x;
            Read(k);
            while(k--){
                Read(x);
                addedge(x,n+i,1);
            }
        }
        for(int i=1;i<=n;++i)
            addedge(S,i,(m+1)>>1);
        int f,mf=0;
        while(bfs()){
            memcpy(cur+1,fst+1,c<<2);
            while((f=dfs(S,0x7fffffff)))
                mf+=f;
        }
        if(mf==m){
            puts("YES");
            for(int i=1;i<=m;++i){
                for(int j=fst[n+i];j;j=edge[j].nxt){
                    int &y=edge[j].v,&w=edge[j].w;
                    if(w)
                        printf("%d%c",y," \n"[i==m]);
                }
            }
        }else{
            puts("NO");
        }
    }
}
```

---

## 作者：Acfboy (赞：2)

网络流的大佬太强了。~~这不是排序解决问题的吗？~~

洛谷似乎交不了这题，交了三次，cf 上过了洛谷一直 waiting, 所以用 cf 记录证明我过了。 提交记录编号： 110669530。

---
赛时 WA 了两次，写题解纪念。

> $m$ 天， $n$ 个数，每天只有一些数能取，每个数取的次数不能超过 $\lceil \frac{m}{2} \rceil$ 次，有方案输出任意一种，没有方案输出 `NO`

很容易想到一个贪心，就是尽可能先满足出现次数少的，且已经选取次数小于 $\lceil \frac{m}{2} \rceil$ 的，但这样显然是错的。

可以被这样的数据卡掉: 有很多出现次数相等的，但一个是在最后唯一能取的，这样用贪心做就会把有解的情况判成 `NO`。

比如下面这组数据:

```plain
3 5 
1 1
2 1 3
2 1 3
2 1 3
1 3

```

如果你找最小时等号也更新，那么就会因为前面用了三次 $3$ 导致后面没得用而输出 `NO`。

怎么解决这个问题呢？

换一个处理顺序，先满足能取的个数少的再满足能取的多的，因为能取的多的能满足的希望肯定比能取的少的要大，所以这样的顺序只会变得更优而不会变得更差。

考虑怎么实现。

我的做法是写一个结构体，里面有一个 `vector` 用来存每一个可以取的，另用 `id` 记录这一个原来的编号，直接 `sort` 就可以了。这样的时间复杂度是不会有问题的，因为题目中保证了所有的 $k$ 的和不超过 $200000$ , 所以排序中交换所需时间和遍历所需时间段的积不会超过 $2000000$, 以快排的复杂度可以通过。

代码如下。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
const int N = 100005;
int T, n, m, num[N], in[N], x, k, ans[N];
bool flag;
struct twt {
    std::vector<int> a;
    int id;
    bool operator < (twt b) const {
        return a.size() < b.a.size();
    }
} f[N];
int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);

        for(int i = 1; i <= m; i++) f[i].a.clear(), ans[i] = 0;
        for(int i = 1; i <= n; i++) in[i] = 0, num[i] = 0;
        flag = 0;

        for(int i = 1; i <= m; i++) {
            scanf("%d", &k);
            f[i].id = i;
            for(int j = 1; j <= k; j++)
                scanf("%d", &x), f[i].a.push_back(x), num[x] ++;
        }
        std::sort(f+1, f+1+m);
        for(int i = 1; i <= m; i++) {
            int minj = -1, min = m+1;
            for(int j = 0; j < (signed)f[i].a.size(); j++) 
                if(num[f[i].a[j]] < min && in[f[i].a[j]] < (m+1)/2)  {
                    minj = f[i].a[j];
                    min = num[f[i].a[j]];
                }
            if(minj == -1) {flag = 1; break;}
            in[minj] ++;
            ans[f[i].id] = minj;
        }
        if(flag) puts("NO");
        else {
            puts("YES");
            for(int i = 1; i <= m; i++) printf("%d ", ans[i]);
            puts("");
        }
    }
    return 0;
}
```

第二次 WA 的原因我原来 `min` 直接赋值为 `f[i].a[0]`, 但这个实际上可能是不能取的。

---

## 作者：vectorwyx (赞：0)

先随便构造出一种方案（不管它合法不合法，比如说每一天都选第一个输入的朋友），然后试着把它调整为合法的方案。

假设原方案中每位朋友出现次数的最大值为 $x$，出现次数最多的朋友编号为 $y$。如果 $x\le\lceil\frac{m}{2}\rceil$，说明它已经合法，直接输出。

否则，考虑把某些天的选择由 $y$ 调整为其他可供选择的人，如果这些可调整的天数大于等于 $x-\lceil\frac{m}{2}\rceil$，也就是说能通过调整把 $x$ 降至 $\lceil\frac{m}{2}\rceil$，那么就把经过调整使得 $x=\lceil\frac{m}{2}\rceil$ 之后的方案输出。这里有个很关键的性质就是如果在一个方案中某个人出现了恰好 $\lceil\frac{m}{2}\rceil$ 次，那么这个方案必定合法。而如果无法通过调整把 $x$ 降为 $\lceil\frac{m}{2}\rceil$，这表明有超过 $\lceil\frac{m}{2}\rceil$ 天不得不选择同一个人，那么一定不存在合法的方案，输出 `NO`。

代码如下：
```cpp
/*
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<deque>
#include<vector>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e5+5;
int ans[N],rp[N],k[N];
deque<int> f[N];

void work(){
	memset(k,0,sizeof k);
	int n=read(),m=read(),t=(m+1)/2;	
	fo(i,1,m) f[i].clear();
	fo(i,1,n) rp[i]=0;
	fo(i,1,m){
		k[i]=read();
		fo(j,1,k[i]) f[i].push_back(read());
	}
	fo(i,1,m) ans[i]=f[i][0],rp[f[i][0]]++;
	//fo(i,1,m) printf("%d ",ans[i]);puts("");
	//fo(i,1,n) printf("%d ")
	int fl=1,p;
	fo(i,1,n) if(rp[i]>t) fl=0,p=i;
	if(fl){
		puts("YES");
		fo(i,1,m) printf("%d ",ans[i]);
		puts("");
		return;
	}
	fo(i,1,m) if(rp[p]>t&&ans[i]==p&&k[i]>1) ans[i]=f[i][1],rp[p]--,rp[f[i][1]]++;
	fl=1;
	fo(i,1,n) if(rp[i]>t){
		puts("NO");
		return;
	} 
	puts("YES");
	fo(i,1,m) printf("%d ",ans[i]);
	puts("");

	//puts("");
}

int main(){
	int T=read();
	while(T--) work(); 
	return 0;
}
```


---

