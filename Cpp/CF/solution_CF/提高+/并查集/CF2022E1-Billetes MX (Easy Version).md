# Billetes MX (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, it is guaranteed that $ q = 0 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 说明/提示

In the first test case of the example, we have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ .

## 样例 #1

### 输入

```
2
3 3 8 0
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
2 5 2 0
1 1 10
1 2 30```

### 输出

```
1
489373567```

# 题解

## 作者：larsr (赞：3)

题目中的信息：对于 $i1,i2,j1,j2$，必须保证 $A_{i1,j1}\oplus A_{i1,j2}\oplus A_{i2,j1}\oplus A_{i2,j2}=0$。那么可以知道 $A_{i1,j1}\oplus A_{i2,j1} =A_{i1,j2}\oplus A_{i2,j2}$，也就是说给定 $a,b$，对于任意值 $k$ 一定可以满足 $A_{a,k}\oplus A_{b,k}$ 是固定的。同理，$A_{k,a}\oplus A_{k,b}$ 也固定。

如果满足了上面这两个条件，题目的要求一定满足。那么一定存在一个序列 $w$ 来表示一个满足条件的 $A$，其中 $A_{i,j}=w_i \oplus w_{j + n}$。可以发现可以表示矩阵 $A$ 的序列 $w$ 总共有 $2^{30}$ 种，因为如果 $w$ 同时异或 $p(0\le p<2^{30})$，矩阵 $A$ 不变。

当给定 $A_{r,c}=v$ 时，那么说明 $w_{r}\oplus w_{c + n}=v$，可以建一个图，将 $r$ 连向 $c+n$，表示如果 $w_r$ 确定了，那么 $w_{c+n}$ 也会确定。连完边后，一个联通块内的值总共 $2^{30}$ 种，设联通块数量为 $s$，那么答案就是 $2^{30^{s-1}}$。当然还要考虑方案为 $0$ 的情况，只要有环的异或不为 $0$，就无合法方案。图可以用并查集维护。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define mod 1000000007
#define N 200010
using namespace std;
ll mul[N], hf;
int n, m, k, q, f[N], fv[N];
int ans;
int getfa(int x)
{
	if(f[x] == x)return x;
	int xx = getfa(f[x]);
	fv[x] = fv[f[x]] ^ fv[x];
	f[x] = xx;
	return xx;
}
void uni(int u, int v, int w)
{
	if(!u || !v)return;
	int xu = u, xv = v;
	u = getfa(u);
	v = getfa(v);
	if(u == v)
	{
		if((fv[xu] ^ fv[xv] ^ w) != 0)hf = 0;
		return;
	}
	f[u] = v;
	fv[u] = w ^ fv[xu] ^ fv[xv];
	ans--;
}
void upd(int x, int y, int v)
{
	uni(x, n + y, v);
}
void slove()
{
	scanf("%d%d%d%d", &n, &m, &k, &q);
	hf = 2e9;
	ans = n + m - 1;
	memset(fv, 0, sizeof fv);
	for(int i = 1; i <= n + m; i++)f[i] = i;
	for(int i = 1; i <= k; i++)
	{
		int r, c, v;
		scanf("%d%d%d", &r, &c, &v);
		upd(r, c, v);
	}
	printf("%lld\n", min(mul[ans], hf));
	for(int i = 1; i <= q; i++)
	{
		int r, c, v;
		scanf("%d%d%d", &r, &c, &v);
		upd(r, c, v);
		printf("%lld\n", min(mul[ans], hf));
	}
}
int main()
{
	ll danw = (1ll << 30) % mod;
	mul[0] = 1;
	for(int i = 1; i <= 2e5; i++)mul[i] = mul[i - 1] * danw % mod;
	int t;
	scanf("%d", &t);
	while(t--)slove();
	return 0;
}

```

---

## 作者：lfxxx (赞：0)

首先二进制拆位。

然后我们考虑从矩形形成的角度看待限制。

题目中描述矩形的方式是选择两行两列。

因此我们就先打表出所有合法矩形，然后选出两行观察，观察到两行要么对应位置相同，要么对应位置相反。

证明考虑如果不满足上述条件就会存在一行 $x,y$ 对应 $x,y \oplus 1$，而这会使得异或起来为 $1$ 不满足条件，满足条件后充分性显然，因此限制等价于任意两行对应相同或者对应相反。

考虑限制转化为任意一行与第一行比较相同或者相反，然后考虑假若确定了第一行，其他行的取值方案。

不难发现假若其他行还没有确定的位置，则有两种填法，否则至多有一种填法。

我们找到所有满足其他填了数的行都有 $1$ 种填法（也即是存在合法填法）的第一行填法。

观察其他行填的数的影响，不难发现，对于其他行中任意两个填的数相同或者不同的位置，第一行这两个位置上的数也要满足相同或者不同。

因此把第一行每个位置拆成 $1,0$ 两种取值，上述限制就可以直接使用扩展域并查集维护。

由于并查集是可以支持动态加边的，所以边填数边求解是简单的。

总时间复杂度 $O(n \log n \log V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
const int maxn = 1e5+114;
int n,m,k,q;
int answer[maxn];
int fa[maxn<<1],vis[maxn<<1];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
int cnt;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int r[maxn],c[maxn],val[maxn];
int R[maxn],C[maxn],Val[maxn];
int fr,e[maxn],col[maxn];
void work(int pos){
    cnt=2*m;
    for(int i=1;i<=m;i++) fa[i*2-1]=i*2-1,vis[i*2-1]=0,fa[i*2]=i*2,vis[i*2]=0;
    fr=n-1;
    for(int i=1;i<=n;i++) e[i]=col[i]=0;
    int res=1;
    for(int i=1;i<=k;i++){
        if(r[i]==1&&vis[found(c[i]*2)]==0){
            cnt-=2;
            vis[found(c[i]*2)]=vis[found(c[i]*2-1)]=1;
        }
        if(e[r[i]]==0){
            e[r[i]]=c[i];
            col[r[i]]=val[i];
            if(r[i]!=1) fr--;
        }else{
            int u=e[r[i]],v=c[i];
            if((val[i]&(1<<pos))==(col[r[i]]&(1<<pos))){
                if(found(u*2-1)!=found(v*2-1)){
                    if(vis[found(u*2-1)]==0||vis[found(v*2-1)]==0) cnt--;
                    vis[found(v*2-1)]=vis[found(u*2-1)]|vis[found(v*2-1)];
                    fa[found(u*2-1)]=found(v*2-1);
                }
                if(found(u*2)!=found(v*2)){
                    if(vis[found(u*2)]==0||vis[found(v*2)]==0) cnt--;
                    vis[found(v*2)]=vis[found(u*2)]|vis[found(v*2)];
                    fa[found(u*2)]=found(v*2);
                }
                if(found(u*2-1)==found(u*2)) res=0;
                if(found(v*2-1)==found(v*2)) res=0;
            }else{
                if(found(u*2-1)!=found(v*2)){
                    if(vis[found(u*2-1)]==0||vis[found(v*2)]==0) cnt--;
                    vis[found(v*2)]=vis[found(u*2-1)]|vis[found(v*2)];
                    fa[found(u*2-1)]=found(v*2);
                }
                if(found(u*2)!=found(v*2-1)){
                    if(vis[found(u*2)]==0||vis[found(v*2-1)]==0) cnt--;
                    vis[found(v*2-1)]=vis[found(u*2)]|vis[found(v*2-1)];
                    fa[found(u*2)]=found(v*2-1);
                }
                if(found(u*2-1)==found(u*2)) res=0;
                if(found(v*2-1)==found(v*2)) res=0;
            }
        }
    }
    answer[0]=answer[0]*qpow(2,cnt/2+fr)%mod*res%mod%mod;
    for(int i=1;i<=q;i++){
        if(R[i]==1&&vis[found(C[i]*2)]==0){
            cnt-=2;
            vis[found(C[i]*2)]=vis[found(C[i]*2-1)]=1;
        }
        if(e[R[i]]==0){
            e[R[i]]=C[i];
            col[R[i]]=Val[i];
            if(R[i]!=1) fr--;
        }else{
            int u=e[R[i]],v=C[i];
            if((Val[i]&(1<<pos))==(col[R[i]]&(1<<pos))){
                if(found(u*2-1)!=found(v*2-1)){
                    if(vis[found(u*2-1)]==0||vis[found(v*2-1)]==0) cnt--;
                    vis[found(v*2-1)]=vis[found(u*2-1)]|vis[found(v*2-1)];
                    fa[found(u*2-1)]=found(v*2-1);
                }
                if(found(u*2)!=found(v*2)){
                    if(vis[found(u*2)]==0||vis[found(v*2)]==0) cnt--;
                    vis[found(v*2)]=vis[found(u*2)]|vis[found(v*2)];
                    fa[found(u*2)]=found(v*2);
                }
                if(found(u*2-1)==found(u*2)) res=0;
                if(found(v*2-1)==found(v*2)) res=0;
            }else{
                if(found(u*2-1)!=found(v*2)){
                    if(vis[found(u*2-1)]==0||vis[found(v*2)]==0) cnt--;
                    vis[found(v*2)]=vis[found(u*2-1)]|vis[found(v*2)];
                    fa[found(u*2-1)]=found(v*2);
                }
                if(found(u*2)!=found(v*2-1)){
                    if(vis[found(u*2)]==0||vis[found(v*2-1)]==0) cnt--;
                    vis[found(v*2-1)]=vis[found(u*2)]|vis[found(v*2-1)];
                    fa[found(u*2)]=found(v*2-1);
                }
                if(found(u*2-1)==found(u*2)) res=0;
                if(found(v*2-1)==found(v*2)) res=0;
            }
        }
        answer[i]=answer[i]*qpow(2,cnt/2+fr)%mod*res%mod%mod;
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m>>k>>q;
        for(int i=0;i<=q;i++) answer[i]=1;
        for(int i=1;i<=k;i++) cin>>r[i]>>c[i]>>val[i];
        for(int i=1;i<=q;i++) cin>>R[i]>>C[i]>>Val[i];
        for(int i=0;i<30;i++) work(i);
        for(int i=0;i<=q;i++) cout<<answer[i]<<'\n';
    }
    return 0;
}
/*
1
2 2 0 2
1 1 0
1 2 0
*/
```

---

