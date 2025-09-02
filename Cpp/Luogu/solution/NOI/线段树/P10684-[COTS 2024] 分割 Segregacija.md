# [COTS 2024] 分割 Segregacija

## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D2T2。$\texttt{5s,512M}$。

**请不要滥用本题评测。滥用本题评测将被封号。**

## 题目描述


Pero 有一个 $2$ 行 $N$ 列的矩阵，每个格子里有一个红球或蓝球。

Pero 想要重排矩阵中的球，使得所有蓝球位于矩阵的左上侧，所有红球位于右下侧。更为具体地说，重排后，不能存在一个红球位于某个蓝球的上方或左侧。

为此，Pero 可以多次交换相邻的两个球。**两个球是相邻的当且仅当它们所在的格子有公共边。** Pero 想知道达到目标所需的最少交换次数。

此外，Pero 会交换矩阵中的相邻两个球 $Q$ 次，并在每次变更后询问当前矩阵状态所需的最小交换次数。请帮助 Pero，输出初始矩阵下以及每次交换后所需的最小交换次数。

## 说明/提示


#### 样例解释

样例 $1$ 解释：对于初始状态，只需要依次交换 $(1,1),(2,1)$，$(1,3),(1,4)$，$(1,4),(2,4)$ 即可。

#### 数据范围

对于 $100\%$ 的数据，保证 $1\le N\le  10^6$，$0\le Q\le 10^6$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $7$  | $N\le 10$   |
| $2$  | $11$  | 最多只有 $10$ 个 $\texttt{C}$  |
| $3$  | $17$  | $N,Q\le 500$ |
| $4$  | $10$  | $N,Q\le 5\, 000$ |
| $5$  | $13$  | $N\le 100\, 000, Q\le 100$ |
| $6$  | $15$  | $t=2$ |
| $7$  | $27$  | 无额外约束 |



## 样例 #1

### 输入

```
5 2
CPCPC
PCCPC
1 1 4
1 1 2```

### 输出

```
3
4
5```

## 样例 #2

### 输入

```
5 0
CPPCC
PPCCP```

### 输出

```
4```

## 样例 #3

### 输入

```
10 7
CCPPPCCPCP
PPPCCCPCCC
1 2 7
2 1 4
2 1 8
1 1 9
2 1 1
1 2 7
1 1 4```

### 输出

```
8
9
10
10
9
8
7
8```

# 题解

## 作者：cxzvbnm (赞：8)

令 $P$ 为 $0$，$C$ 为 $1$。

显然最终状态形如：

$00....001...1$

$0...011....11$

其中上面的 $0$ 多于下面的 $0$，下面的 $1$ 多于上面的 $1$，从上向下交换显然是不优的。

我们考虑用 $c1,c2$ 表示第一行和第二行的 $0$ 的数量，显然 $c1+c2$ 是一个定值，实际上有 $n$ 种最终状态。

假设终态固定，考虑如何计算最小步数。

达到终态的过程可以分成两个阶段，第一个是将上下两行调整至 $(c1,c2)$，第二部分是将上下两行排序。

对于第二阶段的贡献，计算是简单的，等于顺序对数量，令 $sum$ 为 $0$ 的下标和，$c$ 为 $0$ 的个数：

则答案为 $sum-\frac{c(c+1)}{2}$。

考虑第一阶段：

这一部分的过程是对于每一个需要交换的 $0$ ,先进行一部分左右交换，然后上下交换。

显然上下交换的次数是固定的，考虑左右交换，显然不会交换两个相同的数。

考察 $01$,$10$：

交换前者，等价于将一个 $0$ 的坐标 $+1$，会使得当前答案 $+2$ ；交换后者，等价于将一个 $0$ 的坐标 $-1$，答案不变。

由此可得我们在交换时，应该尽可能先将 $0$ 向左交换，再进行上下交换，也就是说会选择第一行最靠左的 $1$ 进行交换，假设我们要交换 $x$ 个 $0$，则会交换第一行前$x$ 个 $1$。

进一步考虑选择哪一个位置的 $0$ 交换。

越靠右边的 $0$ ，则有越多的 $1$ 他可以无贡献到达，因此我们会选择第二行的后 $x$ 个 $0$ 进行交换。

现在我们可以确定操作的 $0$ 的位置和整体的最终位置，显然在交换的过程中，$0$ 的相对位置不改变是最优的。

于是最优的调整是将第二行后 $x$ 个 $0$,从左到右依次移动到第一行前 $x$ 个 $1$ 的位置上。

现在我们需要计算向右边移动了多少次，考虑计算每一个 $(i,i+1)$ 走了多少次。

记录 $s_{1,i},s_{2,i}$ 分别表示第 $1/2$ 行 $[1,i]$ 中 $0$ 的个数，$s_{i}$ 表示前 $i$ 列的 $0$ 的个数。

首先如果 $i-s_{1,i}\geq x~~||~~s_{2,n}-s_{2,i} \geq x$，$(i,i+1)$ 一定不可能被经过。

然后考虑剩下的情况，$(i,i+1)$ 会被经过，是因为在 $[i+1,n]$ 中，第二行需要移动的 $0$ 没有能够填满所有第一行需要被交换的 $1$ ，导致剩下的 $1$ 需要 $[1,i]$ 去交换，那么经过的次数即是剩下的 $1$ 的个数 $=~x-(i-s_{1,i})-(s_{2,n}-s_{2,i}) = x-s_{2,n}-i+s_{i}$。

注意到 $x = s_{2,n}-c_2$,所以贡献可以化简为 $\max(0,s_i-i-c_2)$。

然后代入条件 $i-s_{1,i}\geq x~~||~~s_{2,n}-s_{2,i} \geq x$ ，整理发现贡献仍然为$0$。

于是 $(i,i+1)$ 的经过次数为 $\max(0,s_i-i-c_2)$。

所以对于 $(c1,c2)$ ，总的贡献为:

$2\sum \max(0,s_i-i-c_2)+s_{2,n}-c_2+sum-\frac{c1(c1+1)}{2}-\frac{c2(c2+1)}{2}$

注意到对于原图进行上下交换只会影响 $s_{2,n}$ ，进行左右交换至多使得一个 $s_i$ 变化 $1$ ，于是考虑使用线段树维护每一个 $(c1,c2)$ 的答案，那么所需要维护的操作就只是区间加和查询区间最小值。

实现时注意 $(c1,c2)$ 的取值范围，有些 $(c1,c2)$ 是不存在的。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const int N = 2e6+555;
const ll inf = 1e18;
ll n,q,sum,s[N],tot[2],c[N],cnt,val[N*4],tag[N*4];
int a[3][N];
void build(int l,int r,int u){
    if(l==r){
        val[u] = c[l]*2-l-1ll*l*(l+1)/2-1ll*(tot[0]-l)*(tot[0]-l+1)/2; 
        return ;
    }
    int mid = (l+r)>>1;
    build(l,mid,u*2),build(mid+1,r,u*2+1);
    val[u] = min(val[u*2],val[u*2+1]);
}
void pushdown(int u){
    if(tag[u]){
        val[u*2] += tag[u],val[u*2+1] += tag[u];
        tag[u*2] += tag[u],tag[u*2+1] += tag[u];
        tag[u] = 0;
    }
}
void upd(int l,int r,int u,int sl,int sr,int w){
    if(sl>r || l>sr) return ;
    if(sl<=l && r<=sr) {
        val[u] += w,tag[u] += w;
        return ;
    } 
    int mid = (l+r)>>1;
    pushdown(u);
    upd(l,mid,u*2,sl,sr,w),upd(mid+1,r,u*2+1,sl,sr,w);
    val[u] = min(val[u*2],val[u*2+1]);
}
ll ask(int l,int r,int u,int sl,int sr){
    if(sl>r || l>sr) return inf;
    if(sl<=l && r<=sr) return val[u];
    pushdown(u);
    int mid = (l+r)>>1;
    return min(ask(l,mid,u*2,sl,sr),ask(mid+1,r,u*2+1,sl,sr));
}
int main(){
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> q;
    for(int i=1;i<=2;i++){
        for(int j=1;j<=n;j++) {
            char x;cin >> x;
            a[i][j] = (x == 'C');
            tot[a[i][j]]++;
        }
    }
    for(int i=1;i<=n;i++){
        if(!a[1][i]) sum += i;
        if(!a[2][i]) sum += i;
    }
    for(int i=1;i<=n;i++) s[i] = (!a[1][i])+(!a[2][i]);
    for(int i=1;i<=n;i++) s[i] += s[i-1];
    for(int i=1;i<=n;i++) if(!a[2][i]) cnt++;
    for(int i=1,w;i<=n;i++){
        if(s[i]<=i) continue;
        c[0] += s[i]-i,c[1] += -1-s[i]+i;
        c[s[i]-i+1] += 1;
    }
    for(int i=1;i<=tot[0];i++) c[i] += c[i-1];
    for(int i=1;i<=tot[0];i++) c[i] += c[i-1];
    build(0,tot[0]/2,1);
    cout << ask(0,tot[0]/2,1,max(0ll,tot[0]-n),cnt)+sum+cnt << '\n';
    for(int i=1;i<=n;i++) s[i] -= i;
    for(int i=1;i<=q;i++){
        int t,x,y,d;
        cin >> t >> x >> y;
        if(t == 1){
            if(a[x][y] == a[x][y+1]) d = 0;
            else if(a[x][y] == 0) d = -1;
            else d = 1;
            if(d == 1){
                if(s[y]>=0) upd(0,tot[0]/2,1,0,s[y],2);
                s[y]++,sum--;
            }else if(d == -1){
                s[y]--,sum++;
                if(s[y]>=0) upd(0,tot[0]/2,1,0,s[y],-2);
            }
            swap(a[x][y],a[x][y+1]);
            cout << ask(0,tot[0]/2,1,max(0ll,tot[0]-n),cnt)+sum+cnt << '\n';
        }else{
            cnt -= (!a[2][y]); 
            swap(a[1][y],a[2][y]);
            cnt += (!a[2][y]);
            cout << ask(0,tot[0]/2,1,max(0ll,tot[0]-n),cnt)+sum+cnt << '\n';
        }
    }
    return 0;
}
```

---

## 作者：Larunatrecy (赞：7)

我们把 `P` 看成 $1$，`C` 看成 $0$。

如果只有一行，那么代价肯定是 $0,1$ 顺序对数量，换个容易计算的描述，设有 $c$ 个 $1$，下标和为 $s$，那么代价就是 $s-\frac{c(c+1)}{2}$。 

有两行的时候，我们一定可以先通过一些操作把第二行的 $1$ 交换到第一行，然后再两行分别按照一行的时候求和。

设最终第一行有 $c_1$ 个 $1$，第二行有 $c_2$ 个 $1$，那么代价就是 移动次数加上 $1$ 的下标和减去 $\frac{c_1(c_1+1)+c_2(c_2+1)}{2}$。

移动次数里，上下移动的次数是确定的，而注意到我们对于一个第二行的 $1$，它一定去找第一行最靠左的 $0$ 填进去不劣，对称的同理。

因此我们一定是把第二行的后缀的一些 $1$ 填到了第一行一些前缀的 $0$ 里。

考虑一个 $1$ 往左移动的时候，因为每步下标减一，所以相当于代价不变还等于原来的坐标，如果往右走，则每次代价加 $2$。

考虑一条 $(i,i+1)$ 被向右跨过的次数，化简一下可以发现是 $\max(0,sum_i-i-c_2)$，其中 $sum_i$ 为前 $i$ 列里两行一共多少个 $1$。

那么我们直接开线段树维护每个 $c_2$ 对应的答案 $ans_{c_2}$，上下交换不影响 $sum_i$，左右交换最多改变一列的 $sum_i$，表现在 $ans$ 上就是区间加减，因此可以直接维护。

复杂度 $O(n\log n)$。

---

## 作者：Rainbow_qwq (赞：5)

假设 `C` 是 `1`，`P` 是 `0`。

枚举第一行最后有多少个 $1$，由于 $1$ 的总个数不变，因此第一/第二行的 $1$ 的个数是确定的。

假设 $y$ 坐标为 $[1,2]$，$x$ 坐标为 $[1,n]$，此时我们想要最小化 移动步数 + 最后所有 $1$ 的 $x$ 坐标之和，答案就是这个值减去 $\frac{c_1(c_1+1)}{2}+\frac{c_2(c_2+1)}{2}$。

上下的移动步数是确定的，只需要最小化向右的移动步数（这些移动步数会增加 $x$ 坐标，每移动一步会有 $2$ 的代价，因为要增大 $x$ 坐标且多移动一次）。

接下来观察一些性质：

- 把一个 $1$ 从上往下调一定不优。
- 我们可以考虑先做若干次向右移动，直到某个时刻上下调整可以使得上下的个数满足要求，然后再上下调整。

什么情况下可以满足要求？若一列有 $2$ 个 $1$，则这列必须在第二行有一个 $1$，也就是有 $2$ 个 $1$ 的列不能超过 $c_2$ 个。

对于一个前缀的若干列，设有 $sum_i$ 个 $1$ 和 $i$ 列，则有 $\max(0,sum_i-i-c_2)$ 个 $1$ 必须向右调，需要花费的代价就是 $\sum 2\times \max(0,sum_i-i-c_2)$。

对于每种 $(c_1,c_2)$ 维护一个 $ans_{c_2}$，交换同一列两个时 $sum_i$ 不改变；交换不同列时只有 $1$ 个 $sum_i$ 会改变至多 $1$，只需要在 $ans$ 上区间加。

用线段树维护 $ans$ 数组，时间复杂度 $O(n+q\log n)$。

```cpp
// what is matter? never mind. 
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2") 
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define ll long long
#define int long long
#define ull unsigned long long
#define SZ(x) ((int)((x).size()))
#define ALL(x) (x).begin(),(x).end()
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 2000045
#define inf 0x3f3f3f3f3f3f3f3f

int n,q,all,L,R;
int a[maxn][3];
char s[maxn];
int sum,c1,c2,b[maxn];

int C2(int x){
	return x*(x+1)/2;
}

int w[maxn];

int mn[maxn<<2],tag[maxn<<2];
void pt(int p,int v){
	tag[p]+=v,mn[p]+=v;
}
void down(int p){
	if(tag[p]) pt(p<<1,tag[p]),pt(p<<1|1,tag[p]),tag[p]=0;
}
void up(int p){
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
void build(int p,int l,int r){
	if(l==r)return mn[p]=w[l],void();
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	up(p);
}
void add(int p,int l,int r,int nl,int nr,int v){
	if(nl>nr)return;
	if(l>=nl&&r<=nr)return pt(p,v);
	int mid=l+r>>1; down(p);
	if(nl<=mid)add(p<<1,l,mid,nl,nr,v);
	if(nr>mid)add(p<<1|1,mid+1,r,nl,nr,v); up(p);
}
int ask(int p,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mn[p];
	int mid=l+r>>1; down(p);
	int res=1e18;
	if(ql<=mid)res=min(res,ask(p<<1,l,mid,ql,qr));
	if(qr>mid)res=min(res,ask(p<<1|1,mid+1,r,ql,qr));
	return res;
}

void swp(int x,int y,int xx,int yy){
	if(a[x][y]==a[xx][yy]) return;
	sum-=a[x][y]*x+a[xx][yy]*xx;
	c1-=(a[x][y] && y==1),c1-=(a[xx][yy] && yy==1);
	swap(a[x][y],a[xx][yy]);
	sum+=a[x][y]*x+a[xx][yy]*xx;
	c1+=(a[x][y] && y==1),c1+=(a[xx][yy] && yy==1);
	c2=all-c1;
	if(x==xx) return;
	if(x>xx) swap(x,xx);
	int lstb=b[x];
	b[x]=b[x-1]+a[x][1]+a[x][2]-1;
	if(b[x]>lstb){
		add(1,L,R,L,b[x]-1,2);
	}
	if(b[x]<lstb){
		add(1,L,R,L,b[x],-2);
	}
}

void prework()
{
//	For(j,1,n)cout<<b[j]<<" "; cout<<" b\n";
//	For(i,1,n) b[i]=b[i-1]+a[i][1]+a[i][2]-1;
	For(i,L,R){
		w[i]=(all-i)-C2(i)-C2(all-i);
		// \sum max(2*(b_i-i),0ll)
	//	For(j,1,n) w[i]+=max(0ll,2*(b[j]-i));
	}
	vi B;
	For(j,1,n) B.pb(b[j]);
	sort(ALL(B));
	int now=0,cnt=0;
	Rep(i,R,L){
		now+=cnt*2;
		while(B.size() && B.back()>=i)
			now+=(B.back()-i)*2,++cnt,B.pop_back();
		w[i]+=now;
	}
	build(1,L,R);
//	For(i,0,L) cout<<w[i]<<" "; cout<<"\n";
}

int getans(){
//	prework();
//	cout<<"sum,c1 "<<sum<<" "<<c1<<"\n";
	int res=inf; //ask(1,0,L,0,min(L,c2));
	res=ask(1,L,R,L,min(R,c2));
//	For(i,L,min(R,c2)) res=min(res,w[i]);
//	cout<<"res "<<res<<"\n";
	res+=sum-c1;
	return res;
}

signed main()
{
//	freopen("b21.in","r",stdin);
//	freopen("my.out","w",stdout);
	n=read(),q=read();
	For(j,1,2){
		scanf("%s",s+1);
		For(i,1,n) a[i][j]=(s[i]=='P'),all+=a[i][j],sum+=a[i][j]*i;
	}
	For(i,1,n)c1+=a[i][1],c2+=a[i][2];
	L=max(0ll,all-n);
	R=(all-(all+1)/2);
	For(i,1,n) b[i]=b[i-1]+a[i][1]+a[i][2]-1;
	prework();
	printf("%lld\n",getans());
	For(i,1,q){
		int op=read(),y=read(),x=read();
		if(op==1) swp(x,y,x+1,y);
		else swp(x,y,x,y+1);
		printf("%lld\n",getans());
	}
	return 0;
}
/*
5 2
CPCPC
PCCPC
1 1 4
1 1 2

10 7
CCPPPCCPCP
PPPCCCPCCC
1 2 7
2 1 4
2 1 8
1 1 9
2 1 1
1 2 7
1 1 4
*/
```

---

## 作者：Genius_Star (赞：1)

### 思路：

显然满足要求的一定是下图的形式：

```
PP...PPC...C
P...PCC...CC
```

即第一行中 $[1, x]$ 是 `P`，第二行中 $[1, y]$ 是 `P`，满足 $x > y$ 且 $x + y$ 等于 `P` 的总数。

此时我们不清楚最终是什么形式，考虑枚举第一行 `P` 的个数 $x$，那么形式就确定了。

考虑操作一定分为两步：

- 使得第一行与第二行分别有 $x, y$ 个 `P`。

- 将每一行的 `P` 换到最前面去。

第二步是简单的，即将 `P` 看作 $0$，`C` 看作 $1$ 后，就是排序操作，需要交换的次数是逆序对数量；设为 `P` 的位置分别是 $x_1, x_2, \cdots, x_k$，容易得到逆序对数为 $\sum\limits_{i = 1}^k (x_i - i) = sum - \frac{k(k + 1)}{2}$。

故第二步的总代价为 $s_1 + s_2 - \frac{x(x + 1) + y(y + 1)}{2}$，其中 $s_1, s_2$ 分别表示每行为 `P` 的下标位置之和。

考虑第一步怎么做，显然是先左右交换，然后再上下交换；上下交换的次数的固定的，即 $|cP_1 - x|$。

左右交换怎么交换？显然不可能交换两个一样的，那么只可能出现 `PC` 与 `CP` 这两种情况要交换：

- 对于第一种情况：会使得这个 `P` 的下标增加 $1$（即第二步的代价增加 $1$），总代价增加 $2$。

- 对于第二种情况：会使得这个 `P` 的下标减少 $1$（即第二步的代价减少 $1$），总代价不变。

所以考虑贪心的尽量是将 `P` 往左边换，所以若我们需要将某一行的 $t$ 个 `P` 换到另外一行的话，一定是这一行的最后 $t$ 个 `P` 换到另外一行的前 $t$ 个 `C` 处（这里就假设是第二行换到第一行了）。

我们需要求一个 `P` 向右交换的次数，直接不好作，考虑拆贡献，分别计算经过 $(i, i + 1)$ 的交换次数：

- 那么只有当 $[1, i]$ 中需要交换到上面 `P` 中有一段后缀需要交换到 $i$ 后面。

- 设 $num_{i, j}(l, r)$ 表示第 $i$ 行 $[l, r]$ 中 $j$ 的数量，显然 $[1, i]$ 已经进行的上下交换次数是 $num_{1, 1}(1, i)$。

- 故 $[i + 1, n]$ 中还未交换的 `C` 的数量是 $t - num_{1, 1}(1, i)$，需要 $[1, i]$ 中跨过的次数是 $t - num_{1, 1}(1, i) - num_{2, 0}(i + 1, n)$，即 $[i + 1, n]$ 中的 $0$ 不够补的数量。

这里 $t = cP_2 - y$，化简一下，经过 $(i, i + 1)$ 的交换次数是（这里 $s_i$ 表示前 $i$ 列 $0$ 的个数）：

$$\max(0, s_i - i - y)$$

故对于一个 $(x, y)$，其的最优答案是：

$$2\sum_{i = 1}^{n - 1} \max(0, s_i - i - y) + cP_2 - y + s_1 + s_2 - \frac{x(x + 1) + y(y + 1)}{2}$$

考虑对于每个 $y$，维护上面这个式子。

怎么维护？先令 $a_i = s_i - i$，那么对于 $y \in [0, a_i]$ 会有 $a_i - y$ 的贡献，即区间加一个公差为 $-1$ 的等差序列。

对于交换操作：

  - 对于上下交换，$s_i$ 不变，只有 $cP_1$ 会变，全局加减即可。

  - 对于左右交换，至多令 $s_i$ 变化 $1$，相当于对于一个区间加减。

线段树维护即可，时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e6 + 10; 
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll more;
int n, q, op, x, y, L, R, cnt, all;
int sum[N], a[2][N];
char s[2][N];
ll d[N];
inline void add(int l, int r, ll v){
	d[l] += v, d[r + 1] -= v;
}
inline void add(int l, int r, int a, ll v){
	if(l > r)
	  return ;
	add(l, l, a), add(r + 1, r + 1, -a);
	add(l + 1, r, v);
	add(r + 1, r + 1, -1ll * (r - l) * v);
//	d[l] += a, d[r + 1] -= a;
//	for(int i = l + 1; i <= r; ++i)
//	  d[i] += v;
//	d[r + 1] -= 1ll * (r - l) * v;
}
namespace Seg{
	struct Node{
		int l, r;
		ll Min, tag;
	}X[N << 2];
	inline void pushup(int k){
		X[k].Min = min(X[k << 1].Min, X[k << 1 | 1].Min);
	}
	inline void add(int k, ll v){
		X[k].Min += v;
		X[k].tag += v;
	}
	inline void push_down(int k){
		if(X[k].tag){
			add(k << 1, X[k].tag);
			add(k << 1 | 1, X[k].tag);
			X[k].tag = 0;
		}
	}
	inline void build(int k, int l, int r){
		X[k].l = l, X[k].r = r;
		if(l == r){
			X[k].Min = (d[l] << 1ll) - l - ((1ll * l * (l + 1) + 1ll * (all - l) * (all - l + 1)) >> 1);
			return ;
		}
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		pushup(k);
	}
	inline ll ask(int k, int l, int r){
		if(X[k].l == l && r == X[k].r)
		  return X[k].Min;
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  return ask(k << 1, l, r);
		else if(l > mid)
		  return ask(k << 1 | 1, l, r);
		else
		  return min(ask(k << 1, l, mid), ask(k << 1 | 1, mid + 1, r));
	}
	inline void update(int k, int l, int r, ll v){
		if(X[k].l == l && r == X[k].r){
			add(k, v);
			return ;
		}
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  update(k << 1, l, r, v);
		else if(l > mid)
		  update(k << 1 | 1, l, r, v);
		else{
			update(k << 1, l, mid, v);
			update(k << 1 | 1, mid + 1, r, v);
		}
		pushup(k);
	}
}
bool End;
int main(){
	open("matrix.in", "matrix.out");
	n = read(), q = read();
	scanf("%s%s", s[0] + 1, s[1] + 1);
	for(int i = 0; i < 2; ++i)
	  for(int j = 1; j <= n; ++j)
	    a[i][j] = (s[i][j] == 'C');
	for(int i = 1; i <= n; ++i){
		if(!a[0][i])
		  ++sum[i], more += i;
		if(!a[1][i])
		  ++sum[i], more += i, ++cnt;
		sum[i] += sum[i - 1];
		add(0, sum[i] - i, sum[i] - i, -1);
	}
	all = sum[n];
	L = max(0, all - n), R = min(cnt, all >> 1);
	for(int i = 1; i <= (all >> 1); ++i)
	  d[i] += d[i - 1];
	for(int i = 1; i <= (all >> 1); ++i)
	  d[i] += d[i - 1];
	for(int i = 1; i <= n; ++i)
	  sum[i] -= i;
	Seg::build(1, 0, all >> 1);
	write(Seg::ask(1, L, R) + more + cnt);
	putchar('\n');
	while(q--){
		op = read(), x = read() - 1, y = read();
		if(op == 1){
			if(a[x][y] == a[x][y + 1]){
				write(Seg::ask(1, L, R) + more + cnt);
				putchar('\n');	
				continue;
			}
			if(!a[x][y]){
				--sum[y];
				++more;
				if(sum[y] >= 0)
				  Seg::update(1, 0, sum[y], -2);		
			}
			else{
				if(sum[y] >= 0)
				  Seg::update(1, 0, sum[y], 2);
				++sum[y];
				--more;
			}
			swap(a[x][y], a[x][y + 1]);
			write(Seg::ask(1, L, R) + more + cnt);
			putchar('\n');	
		}
		else{
			if(!a[x + 1][y] && a[x][y])
			  --cnt;
			if(a[x + 1][y] && !a[x][y])
			  ++cnt;
			swap(a[x + 1][y], a[x][y]);
			R = min(cnt, all >> 1);
			write(Seg::ask(1, L, R) + more + cnt);
			putchar('\n');			
		}
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：1)

把 $\tt P$ 视作 $0$、$\tt C$ 视作 $1$。首先最终的结果肯定是两行的 $0$ 都在前缀。假设两行分别有 $x/y$ 个 $0$，那么还要求 $x\geq y$。

注意到 $x+y$ 恒等于 $0$ 的个数，而这个数量不会变化。所以确定 $x$ 之后 $y$ 也就确定了。

先考虑对确定的 $x,y$ 如何计算最小步数。假设一个格子 $(x,y)$ 的势能是 $x+y$。

首先我们发现我们把左右的 $10$ 或者上下的 $10$ 交换是能接受的。这是因为这一类操作从会让所有 $0$ 位置的势能减少 $1$。而把左右的 $01$ 或者上下的 $01$ 交换是我们尽可能要避免的，这会让 $0$ 位置势能增加 $1$。

假设目前所有 $0$ 位置势能和为 $X$，目标状态势能和为 $Y$。而我们进行了 $C$ 次交换左右、上下的 $01$ 操作。那么答案将会是 $X-Y+2C$。其中 $X,Y$ 是定值。我们目标变成最小化 $C$。

考虑如何最小化 $C$。我们能够证明，我们不会进行交换上下的 $01$ 这样的操作，这是因为目标状态上边的 $0$ 就多。如果你不进行交换上下 $01$ 这一种操作的话 $Y$ 肯定会增加，同时 $C$ 减少。答案必然减小。

其次，我们能够说明，存在最优的操作序列形如：交换了若干左右的 $01$、交换若干上下 $10$、交换若干左右的 $10$。

其中后面两类对 $C$ 没有贡献。只有第一类对 $C$ 有贡献。结束了第一轮操作之后，我们需要剩下两个 $1$ 的列的数量不大于 $y$。

假设 $S_i$ 表示前 $i$ 列有多少个 $0$。那么第 $i$、$i+1$ 列的交换次数至少是 $\max(S_i-i-y,0)$。容易说明我们能取到这个下界。

然后考虑如何快速维护这个变换。用线段树维护每个 $y$ 的答案。$2$ 操作对 $S$ 没有影响，$1$ 操作对 $S$ 的影响是单点加一、减一。对应 $y$ 的答案是区间加、减。容易线段树维护。

---

