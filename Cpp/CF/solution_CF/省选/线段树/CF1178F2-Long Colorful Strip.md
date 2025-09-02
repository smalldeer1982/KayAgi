# Long Colorful Strip

## 题目描述

这是 F 题的第二个子任务。F1 和 F2 的区别仅在对于 $m$ 和时间的限制上

有 $n+1$ 种颜色标号从 $0$ 到 $n$，我们有一条全部染成颜色 $0$ 的长为 $m$ 的纸带。

Alice 拿着刷子通过以下的过程来给纸带染色：

我们按照从 $1$ 到 $n$ 的顺序进行染色，进行每次染色时，我们选取一个区间 $[a_i,b_i]$，$0 \le a_i < b_i \le m$，并且这个区间内必定是单种颜色。

染色到最后，纸带上有各种颜色除了颜色 $0$。给出纸带最终的状态，问有多少种不同的染色方案能到达最终状态。输出时结果模 $998244353$。

## 样例 #1

### 输入

```
3 3
1 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2 3
1 2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2 3
2 1 2
```

### 输出

```
0
```

## 样例 #4

### 输入

```
7 7
4 5 1 6 2 3 7
```

### 输出

```
165
```

## 样例 #5

### 输入

```
8 17
1 3 2 2 7 8 2 5 5 4 4 4 1 1 6 1 1
```

### 输出

```
20
```

# 题解

## 作者：AThousandSuns (赞：9)

在我的博客园看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/11422919.html)

说起来，这题好像也不难……

先考虑 F1 怎么做。

~~既然别的方法都不行不如试试~~$f_{i,j}$  表示在刚刚准备开始涂 $[i,j]$ 中最小编号的颜色之前，整个区间是同色的，且最后能做到 $[i,j]$ 变成要求的颜色，且所有连续颜色段要么完全在 $[i,j]$ 内，要么完全在 $[i,j]$ 外的方案数。（有点绕，好好理解一下）

那么先找到区间 $[i,j]$ 中的最小值 $c$，下一步染色的区间 $[l,r]$ 一定要满足 $i\le l\le r\le j$ 且包括 $p_c$，其中 $p_c$ 是 $c$ 出现的位置。

由于染色后，$[l,r]$ 内同色且与不在 $[l,r]$ 内的异色，那么整个带子变成了四块。（图片来源：官方题解）

![](https://codeforc.es/predownloaded/a7/a5/a7a5c89d580aa0dee52d4edffc9d316209f7d736.png)

这是因为，$p_c$ 永远不能被重新染色，就把两边分开了；$[l,r]$ 内和 $[l,r]$ 外的已经不同色，后面也不可能变得同色。

那么这四部分可以单独处理。

就有转移方程：$f_{i,j}=\sum\limits_{l=i}^{p_c}\sum\limits_{r=p_c}^jf[i][l-1]f[l][p_c-1]f[p_c+1][r]f[r+1][j]$。这里由于一些边界原因，不妨设 $f_{i+1,i}=1$。

这是一个 $O(n^4)$ 做法（在 F1 中 $n=m$）。优化的话，发现 $l$ 和 $r$ 在转移中独立。可以重写：$f_{i,j}=(\sum\limits_{l=i}^{p_c}f[i][l-1]f[l][p_c-1])(\sum\limits_{r=p_c}^jf[p_c+1][r]f[r+1][j])$

时间复杂度 $O(n^3)$。还有个大概 $\frac{1}{6}$ 的常数。

接下来看看 F2。

首先这个 $m$ 太大了，无论如何都不能直接区间 DP。

找找性质：

**性质 1：**如果两个方格某个时刻开始不同色，那么它们会一直不同色。反过来，如果两个方格最后同色，那么它们始终同色。

所以，不妨把连续一段相等的压成一个，不影响答案。

**性质 2：**把 $c_i\ne c_{i+1}$ 的 $i$ 叫做转折点。那么一次染色最多增加两个转折点。

所以，压缩后如果 $m>2n$，这一定是不可能做到的，直接输出 $0$。

那么接下来 $m\le 2n$，基本上可以按上面的方法来做。不过要稍微修改一下。

比如考虑序列 2,1,2，答案明显是 $0$。但是我们上面的做法会用 1 把两边分开单独考虑。

为什么会错呢？因为此时两边不独立。

其实解决方法也很简单，每次判一下是不是序列中所有 $c$ 都在这个区间中。如果不是的话，给这个区间染色后不可能做到里面是 $c$，外面也是 $c$。

同时，此时这个区间也分成了不止四段。不过问题不大，前后四段还是通过上面的方法转移，中间几段是一定取满的，直接乘上去就好了。

时间复杂度 $O(n^3+m)$，有个大概 $\frac{4}{3}$ 的常数。在 CF 神机+ 6s 时限下完全不用怕。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=1111,mod=998244353;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,m,m_,a[1111111],lft[maxn],rig[maxn],f[maxn][maxn];
int main(){
	n=read();m_=read();
	while(m_--){
		int x=read();
		if(x!=a[m]) a[++m]=x;
	}
	if(m>2*n) return puts("0"),0;
	MEM(lft,0x3f);
	FOR(i,1,m) lft[a[i]]=min(lft[a[i]],i),rig[a[i]]=max(rig[a[i]],i);
	FOR(i,1,m) if(lft[a[i]]==i && rig[a[i]]==i) f[i][i]=1;
	FOR(i,0,m) f[i+1][i]=1;
	FOR(l,2,m) FOR(i,1,m-l+1){
		int j=i+l-1,mn=i;
		FOR(k,i+1,j) if(a[k]<a[mn]) mn=k;
		int x=lft[a[mn]],y=rig[a[mn]],s1=0,s2=0,pre=0;
		if(x<i || y>j) continue;
		FOR(k,i,x) s1=(s1+1ll*f[i][k-1]*f[k][x-1])%mod;
		FOR(k,y,j) s2=(s2+1ll*f[y+1][k]*f[k+1][j])%mod;
		f[i][j]=1ll*s1*s2%mod;
		FOR(k,i,j) if(a[k]==a[mn]){
			if(pre) f[i][j]=1ll*f[i][j]*f[pre+1][k-1]%mod;
			pre=k;
		}
	}
	printf("%d\n",f[1][m]);
}
```

---

## 作者：xuantianhao (赞：2)

# [Long Colorful Strip](https://www.luogu.com.cn/problem/CF1178F2)

中间如果有那些地方看不懂，可以先去看看前面一道，[这](https://www.luogu.com.cn/blog/242082310xth/cf1178f1-short-colorful-strip-ti-xie)是我的题解。

首先，每一次染色，最多把一整段连续的同色格子，分成了三段。

并且，明显我们可以把连续的同色格子，直接看作一个。

这就意味着，在这么压缩后，有 $m<2n$。

这就意味着 $O(m^3)$ 的复杂度是可以接受的。

还是考虑和前一道题一样的 DP。

但是这题，并非所有的 $f[i,j]$ 都是合法的；只有对于每一种颜色，它所有的格子要么全都在段内，要么全都在段外，这样的 $f[i,j]$ 才是合法的。因为，两个格子只要从什么时候开始颜色不一样了，那它们的颜色也会一直不一样下去。

考虑如何转移。

因为每种颜色都可能出现了不止一次，所以对于一种颜色 $c$，我们有必要记录它出现的最左端 $mn_c$ 与最右端 $mx_c$ 。

则转移时的左右两端仍然可以采取和上一问一模一样的转移方式，即

$$f[i,j]=(\sum\limits_{k=i}^{mn_{mp}}f[i,k-1] \times f[k,mn_{mp}-1]) \times (\sum\limits_{l=mx_{mp}}^jf[mx_{mp}+1,l] \times f[l+1,j])$$

同时，对于区间 $[mn_{mp},mx_{mp}]$ 内的非 $mp$ 的所有连续格子段 $[p_x,q_x]$，我们也都应该计算它们的贡献。

因此我们最终得到的是

$$f[i,j]=(\sum\limits_{k=i}^{mn_{mp}}f[i,k-1] \times f[k,mn_{mp}-1]) \times (\sum\limits_{l=mx_{mp}}^jf[mx_{mp}+1,l] \times f[l+1,j]) \times \prod f[p_x,q_x]$$

复杂度仍是 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353,INF=0x3f3f3f3f;
const int N=1e3+100,M=1e6+100; 
int n,m,a[M],f[N][N],mn[N],mx[N];
signed main(){
    cin>>n>>m;memset(mn,INF,sizeof(mn));
    for(int i=1;i<=m;i++){cin>>a[i];if(a[i]==a[i-1]) i--,m--;}
    if(m>2*n){cout<<"0";return 0;}
    for(int i=1;i<=m;i++) mx[a[i]]=max(mx[a[i]],i),mn[a[i]]=min(mn[a[i]],i);
    for(int i=1;i<=m+1;i++) for(int j=0;j<i;j++) f[i][j]=1;
    for(int l=1;l<=m;l++)
		for(int i=1,j=i+l-1;j<=m;i++,j++){
        	int now=INF,A=0,B=0;
        	for(int k=i;k<=j;k++) now=min(now,a[k]);
        	if(mn[now]<i||mx[now]>j) continue;
        	for(int k=mn[now];k>=i;k--)(A+=(f[i][k-1]*f[k][mn[now]-1]%mod))%=mod;
        	for(int l=mx[now];l<=j;l++)(B+=(f[mx[now]+1][l]*f[l+1][j]%mod))%=mod;
        	f[i][j]=A*B%mod;
        	for(int p=mn[now]+1,q=mn[now];p<mx[now];){
            	while(q<j&&a[q+1]!=now) q++;
            	f[i][j]=f[i][j]*f[p][q]%mod;
            	q++;p=q+1;
        	}
    	}
    cout<<f[1][m];
    return 0;
} 
```


---

## 作者：lfxxx (赞：0)

看到每种颜色染色前染色区域必须是只有一种颜色，可以发现染色区间两两不交，因为对于两个相交区间，靠后染色的那个想要染色前染色区域只有一种颜色就必须在找一个颜色把之前染的颜色全部覆盖掉或者产生新的染色区域交，由于最后每种颜色都出现了所以这是不合法的。

再来考察下最终的序列，不妨令 $L_i,R_i$ 分别表示颜色 $i$ 在最终序列中第一次和最后一次出现的位置，你发现 $L_i,R_i$ 内必须都进行一次颜色 $i$ 的染色，即颜色 $i$ 的染色区间包含了 $L_i,R_i$，接着你会发现 $L_i,R_i$ 也必须不交，不然就会出现两个不同端点 $x,y$ 均都染了颜色 $a,b$ 最后却呈现出不同颜色的情况，显然不合常理。

然后你发现假若 $[L_i,R_i]$ 包含了 $[L_j,R_j]$，则必定要 $i<j$ 不然就会不存在合法染色方案，这是因为 $j$ 如果先染就一定会被 $i$ 的染色覆盖掉。

接着你可以感觉到，$L_i,R_i$ 的包含关系一定程度上指示了真实的染色区间的包含关系，具体而言，假若 $[L_i,R_i]$ 包含了 $[L_j,R_j]$，那么 $i$ 的染色区间必须包含 $j$ 的染色区间，因为假若 $j$ 的染色区间超出了 $[L_i,R_i]$ 就不会出现 $L_i,R_i$ 被染成了颜色 $i$ 的情况，当然这里还需要特判 $L_j,R_j$ 内有最终被染成了小于 $j$ 的颜色，这也是不合法的。

对于 $L_i,R_i$ 不形成包含关系的颜色，其真实的染色区间可能是包含也可能是相离，看上去比较复杂，所以我们先不去管他，先考虑构成包含关系的若干颜色会给我们带来如何的限制。

不妨按照 $L_i,R_i$ 的包含关系建边，这形成了一棵树，你发现这棵树上，一个点的染色区间只受到其父亲以及其若干兄弟的限制，更具体的，对于节点 $u$ 而言，找到 $L_{fa_u},R_{fa_u}$ 中唯一一个包含 $L_u,R_u$ 的不存在颜色 $fa_u$ 的极长段（如果不是唯一会违反 $L_i,R_i$ 内不存在小于 $i$ 的颜色一限制），限制是对于这个极长段内的颜色选出染色区间后不会超出这个极长段并且对于极长段内的颜色会形成最后给出的颜色序列中的关系，也就是我们对于每个这样的极长段算出方案再乘起来即可。

考虑对于一个极长段，其中存在若干颜色，这些颜色的区间是一个对于极长段的划分，仿照前面关于区间不交的证明，我们说明我们的染色区间不会去切割极长段，也就是说一个极长段可以视作一个点，那么变成了 F1 中的问题，这又要怎么做呢。

还是抓住染色区间不交，对于任意一个区间，按染色区间建树会形成一个森林，森林的每个节点是一个区间，每个点的儿子代表的区间是对其本身的区间的一个划分，并且染色方案和森林一一对映，所以考虑直接对森林形态 dp，也就是设计状态 $dp_{l,r},f_{l,r}$ 表示考虑区间 $[l,r]$ 其内形成一棵树与一个森林的方案，$dp_{l,r}$ 的转移考虑树的根代表的染色区间一定是染上区间内最小的颜色，不妨令其在原序列中下标为 $p$，有 $dp_{l,r} = dp_{l,p-1} \times dp_{p+1,r}$，而 $f_{l,r}$ 的转移考虑剥去区间 $[l,r]$ 内最靠后的一棵树的根即可，可以做到 $O(s_i^3)$，其中 $s_i$ 表示这个极长段中的区间数。

区间数对应了颜色数，每个极长段中的颜色显然不交，所以 $\sum s_i = n$，那么 $\sum s_i^3 \leq n^3$，由于前面维护 $L_i,R_i$ 内的最小颜色我用了线段树，所以做到了 $O(n^3 + m \log m)$。


```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
const int maxn = 514;
const int maxm = 1e6+114;
int L[maxn],R[maxn];
vector< pair<int,int> > vec;
int n,m;
vector<int> E[maxn];
int dfs(int u){
    if(E[u].size()==0) return 1;
    int res=1;
    for(int v:E[u]){
        res=res*dfs(v)%mod;
    }
    vector< vector<int> > dp,f;
    dp.resize(E[u].size());
    f.resize(E[u].size());
    for(int i=0;i<dp.size();i++) dp[i].resize(dp.size()),f[i].resize(f.size());
    for(int i=0;i<dp.size();i++) dp[i][i]=1,f[i][i]=1;
    for(int len=2;len<=dp.size();len++){
        for(int l=0;l+len-1<dp.size();l++){
            int r=l+len-1;
            int mi=l;
            for(int k=l;k<r;k++) f[l][r]=(f[l][r]+f[l][k]*dp[k+1][r]%mod)%mod;
            for(int k=l;k<=r;k++) mi=(E[u][k]<E[u][mi]?k:mi);
            if(mi==l) dp[l][r]=f[l+1][r];
            else if(mi==r) dp[l][r]=f[l][r-1];
            else dp[l][r]=f[l][mi-1]*f[mi+1][r]%mod;
            f[l][r]=(f[l][r]+dp[l][r])%mod;
        }
    }
    int chifan=1;
    int lst=0;
    for(int i=1;i<dp.size();i++){
        if(L[E[u][i]]!=R[E[u][i-1]]+1){
            chifan=chifan*f[lst][i-1]%mod;
            lst=i;
        }
    }
    chifan=chifan*f[lst][dp.size()-1]%mod;
    return res*chifan%mod;
}
vector<int> pos[maxn];
int tr[maxm<<2],a[maxm];
void build(int cur,int lt,int rt){
    if(lt==rt){
        tr[cur]=a[lt];
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
    tr[cur]=min(tr[cur<<1],tr[cur<<1|1]);
}
int ask(int cur,int lt,int rt,int l,int r){
    if(rt<l||r<lt) return 1e18;
    if(l<=lt&&rt<=r) return tr[cur];
    int mid=(lt+rt)>>1;
    return min(ask(cur<<1,lt,mid,l,r),ask(cur<<1|1,mid+1,rt,l,r));
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    memset(L,0x3f3f3f3f,sizeof(L));
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        a[i]=x;
        L[x]=min(L[x],i);
        R[x]=max(R[x],i);
        pos[x].push_back(i);
    }
    build(1,1,m);
    for(int i=1;i<=n;i++){
        for(int j=0;j+1<pos[i].size();j++){
            if(ask(1,1,m,pos[i][j],pos[i][j+1])<i){
                cout<<0<<'\n';
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++) vec.push_back(make_pair(L[i],i));
    sort(vec.begin(),vec.end());
    E[0].push_back(vec[0].second);
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(L[vec[i].second]<R[vec[j].second]&&R[vec[i].second]>R[vec[j].second]){
                cout<<0<<'\n';
                return 0;
            }
        }
        bool flag=false;
        for(int j=i-1;j>=0;j--){
            if(R[vec[i].second]<R[vec[j].second]){
                E[vec[j].second].push_back(vec[i].second);
                flag=true;
                if(vec[j].second>vec[i].second){
                    cout<<0<<'\n';
                    return 0;
                }
                break;
            }
        }
        if(flag==false) E[0].push_back(vec[i].second);
    }
    cout<<dfs(0)<<'\n';
    return 0;
}
```

---

## 作者：piggy123 (赞：0)

一个如何想到区间 DP 转移的套路——转树形 DP。

对于区间类型 DP，我们常见的套路是将其转化为一棵树，树上的区间若有祖先关系，则为祖先区间包含后代区间。并且最优结构必然存在这样一棵树，也就是说**区间相交不合法或不优**。

对于这一题，显然相同颜色段缩掉，如果段数 $\gt 2n$ 无解。

我们先将题意抽象化，我们发现题目要求涂色区间是同色，那么就必然存在一个 $i\lt j$ 使得 $[a_i,b_i]$ 包含 $[a_j,b_j]$，且不存在一个区间满足 $i,j$ 相交且互不包含。这自然地形成了一个树状结构。

我们考虑如何转移，容易发现我们需要从小区间转移到大区间，也就是在这棵树上从儿子转移到父亲。那么根据递归结构，我们在处理 $i$ 涂色的时候，颜色比 $i$ **大**的区间都已经转移完毕（因为这里的树显然是小颜色为大颜色祖先），我们需要枚举 $i$ 的状态。

所以我们应该枚举当前最小颜色涂哪一个区间，容易做到 $n^2$ 转移。但是我们注意到选择的区间必然包含最小的和最大的这种颜色。所以转移形如包含 $[p,q]$ 的一段区间，这就拆分成了 $[l,p-1]$ 与 $[q+1,r]$ 两部分，互不干扰，分别计算最后再乘起来即可。复杂度 $\Theta(n^3)$。

---

## 作者：Wind_love (赞：0)

## 思路
本题与上一题类似，使用记忆化搜索实现。

首先，我们可以发现，若有相邻的同色位置，可以把它们认为是一个位置，所以我们先将该序列去重。

设有 $3$ 种颜色，缩减后有方案的序列最长为 $1,2,3,2,1$，目前有正确的染色方案。也就是“小包大”的这种染色形式，有且仅有一个染色方案。

如果让这个序列经过缩减后更长，无论加什么都会导致没有方案，例如 $1,2,1,3,2,1$，所以说经过缩减后，纸带的长度大于等于 $2n$，那么无需搜索直接输出 $0$ 即可，那么需要搜索的情况，纸条最长不会超过 $1000$。

像上一题一样，依旧是找到编号最小的颜色 $p$，让 $p$ 为最小的颜色。在这里分为三个区间：左区间、中区间、右区间，分别设为 $ans1$、$ans2$、$ans3$，答案是 $ans1 \times ans2 \times ans3$，不要忘了取余。
## 代码如下
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
vector<int> v[505];
int n,m,t,a[1005],f[1005][1005];
int dfs(int l,int r){
	if(f[l][r]!=-1)return f[l][r];
	if(l>r)return f[l][r]=1;
	int p=a[l];
	for(int i=l+1;i<=r;i++){
		p=min(p,a[i]);
	}
	if(v[p][0]<l||v[p].back()>r){
		return f[l][r]=0;
	}
	if(l==r){
		return f[l][r]=1;
	}
	int ans1=0,ans2=1,ans3=0;
	int pl=v[p][0];
	for(int i=l;i<=pl;i++){
		ans1=(ans1+dfs(l,i-1)*dfs(i,pl-1)%mod)%mod;
	}
	if(v[p].size()==1)ans2=1;
	else{
		int len=v[p].size();
		for(int i=0;i<len-1;i++){
			ans2=ans2*dfs(v[p][i]+1,v[p][i+1]-1)%mod;
		}
	}
	int pr=v[p].back();
	for(int j=pr;j<=r;j++){
		ans3=(ans3+dfs(pr+1,j)*dfs(j+1,r)%mod)%mod;
	}
	return f[l][r]=ans1*ans2%mod*ans3%mod;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		if(i>2*n){
			cout<<0;
			return 0;
		}
		int t;
		cin>>t;
		if(t==a[i-1]){
			i--,m--;
		}
		else{
			a[i]=t;
			v[t].push_back(i);
		}
	}
	memset(f,-1,sizeof f);
	cout<<dfs(1,m);
	return 0;
}
```
## 尾声
本题是上一题的加强版，上一题的思路对本题有很好的启发作用，所以我们做题时可以通过类似题目的思路来推想思路。

---

## 作者：GeXiaoWei (赞：0)

# CF1178F2 Long Colorful Strip
## 题目解析
看一下数据，若 $n<m$ 时，且 $2\times n$ 小于 $m$ 时，一定无解，直接输出，不输出会运行错误。

直接写太麻烦，用记忆化搜索更加简洁明了，通俗易懂。数据中的 $m$ 的值特别大，一定要想办法优化，否则超时。我们不如就设 $dp_{l,r}$ 表示 $[l,r]$ 区间操作的方案数，找出最小的颜色开始染，若它的下标为 $x$，则问题可分为在区间 $[L,R]$ 寻找一个带有 $x$ 的区间 $[l,r]$，$l$ 在区间 $[L,x]$ 中选择，$R$ 在区间 $[x,R]$ 中选择。随后我们将左区间 $[L,x]$ 分为 $[L,l-1]$ 和 $[l,x-1]$，求出方案数，用小学乘法原理乘起来即可，中区间和右区间同理，依然用乘法原理。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
int n,m,a[1005],dp[1005][1005],t;
vector<int>v[505];
long long dfs(int l,int r){
    if(dp[l][r]!=-1) return dp[l][r];
    if(l>r) return dp[l][r]=1;
    long long a1=0,a2=1,a3=0;
    int p=a[l],p1;
    for(int i=l+1;i<=r;i++) p=min(p,a[i]);
    if(v[p][0]<l||v[p].back()>r) return dp[l][r]=0;
    if(l==r) return dp[l][r]=1;
    p1=v[p][0];
    for(int i=l;i<=p1;i++) a1=(a1+dfs(l,i-1)*dfs(i,p1-1)%mod)%mod;
    if(v[p].size()==1) a2=1;
    else for(int i=0;i<v[p].size()-1;i++) a2=a2*dfs(v[p][i]+1,v[p][i+1]-1)%mod;
    for(int i=v[p].back();i<=r;i++) a3=(a3+dfs(v[p].back()+1,i)*dfs(i+1,r)%mod)%mod;
    return dp[l][r]=a1*a2%mod*a3%mod;
}
int main(){
    scanf("%d %d",&n,&m);memset(dp,-1,sizeof(dp));
    for(int i=1;i<=m;i++){
        if(i>n*2){
            printf("0");
            return 0;
        }
        scanf("%d",&t);
        if(t==a[i-1]) i--,m--;
        else a[i]=t,v[t].push_back(i);
    } 
    printf("%lld",dfs(1,m));
    return 0;
}
```

---

## 作者：TernaryTree (赞：0)

感觉 F1 对 F2 很有启发性。

先考虑排列咋做，$n\le 500$ 直接扔一个高复杂度 dp 上去优化看上去就很对，而且看上去也很区间 dp 的样子。

我们设 $f_{l,r}$ 表示 $[l,r]$ 区间操作的方案数。第一次染色的必定是最小值 $p$，假设出现在 $i$，那么枚举 $l\le l'\le i\le r'\le r$ 的 $(l',r')$ 表示第一次染 $[l',r']$ 这个区间，贡献为 $f_{l,l'-1}f_{l',i-1}f_{i+1,r'}f_{r'+1,r}$（若 $l=r+1$ 则 $f_{l,r}=1$）。这样是四方，但是 $l,r$ 贡献不交，可以拆开，计算 $l$ 那一部分的和与 $r$ 那一部分的和乘起来即可。$\Theta(n^3)$。

扩展到 $m\le 10^6$。一个显然的结论是，我们可以缩连续段。其次，若连续段数 $>2n$ 则一定无解。这是因为增加一个颜色至多增加两个连续段，而 $0$ 的连续段又被保证最终不存在。所以我们把 $m$ 缩到了 $\Theta(n)$，可以套 dp 了。

还有一些细节需要修改，如一个区间可能出现多次最小值之类的。处理方法有：第一，如果一个区间的最小值，在区间外也出现过，那么 $f_{l,r}=0$。第二，假设一个区间最小值在区间内出现位置为 $p_{1},p_2,\dots,p_{k}$，那么贡献应该改为 $f_{l,l'-1}f_{l',p_1-1}f_{p_1+1,p2-1}f_{p_2+1,p_3-1}\dots f_{p_{k-1}+1,p_{k}-1}f_{p_k+1,r'}f_{r'+1,r}$。同样地，一部分是和 $l,r$ 无关的，扔出来算；其余的都同原做法了。

---

## 作者：tXX_F (赞：0)

# Long Colorful Strip

## [传送门](https://www.luogu.com.cn/problem/CF1178F2)

## 解题思路

先将 $c$ 数组去重，将连续的一段相同颜色并做一格，因为连续多格与一格都可以进行一次涂色操作后涂好，并做一格便于处理。相关代码如下：

```cpp
for (int i = 1; i <= m; i++) {
	x = rd();
	if (x != a[len]) {
		a[++len] = x;
	}
}
```

#### 对于 $n=m$ 的情况：

与 Short 版处理方法相同。

#### 对于 $n<m$ 的情况：

* 记录下进过前文所描述的去重操作后数组长度，若大于 $2 \times n$ 则一定无解，输出 $0$，并结束程序（否则会 RE）。
* 在 $\operatorname{dfs}$ 函数中，要进行一些改动。
	* 首先，要记录该区间编号最小的颜色在整个数组中第一次与最后一次出现的位置。若其中一个不在该区间内，则该区间无符合条件的涂色方法。
   * 对于符合条件的区间，进行如下操作（为了便于讲解，先放张图）：
   ![图1](https://cdn.luogu.com.cn/upload/image_hosting/mp0enuoi.png)
   
   		* 对于该区间编号最小颜色第一次出现位置前于最后一次出现后的部分（红色部分），仍然照 Short 版操作：
        
       ```cpp
		for (int i = l; i <= minid; i++) {
			tmp1 = (tmp1 + dfs(l, i - 1) * dfs(i, minidl - 1) % Mod) % Mod;
		}
		for (int i = minid; i <= r; i++) {
			tmp2 = (tmp2 + dfs(minidr + 1, i) * dfs(i + 1, r) % Mod) % Mod;
		}
		tong[l][r] = tmp1 * tmp2 % Mod;
```

      * 对于编号最小颜色出现位置的相隔部分（蓝色部分），继续放入 dfs 函数中处理，根据乘法原理，将它与 $tong_{l,r}$ 相乘，就是该区间的方案数了。相关代码片段：
      
      ```cpp
		for (int i = l; i <= r; i++) {
			if (a[i] == a[minid]) {
				if (top) {
					tong[l][r] = (tong[l][r] * (dfs(top + 1, i - 1) % Mod)) % Mod;
				}
				top = i;
			}
		}
```

* 最后，$tong_{1,len}$ 就是最终总方案数了。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
inline void write(int x) {
	if (x < 0)x = ~x + 1, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
const int Mod = 998244353;
const int Maxn = 2200 + 5, Maxm = 2e6 + 5;
int n, m, a[Maxm];
bool vis[Maxm];
int tong[Maxn][Maxn]/*区块l~r的方案数*/, minid, L[Maxm], R[Maxm];
inline int dfs(int l, int r) {
	if (tong[l][r] != -1) {
		return tong[l][r];
	} else if (l >= r) {
		return tong[l][r] = 1;
	} else {
		int minid = l, tmp1 = 0, tmp2 = 0, top = 0, minidl, minidr;
		for (int i = l; i <= r; i++) {//求当前区块编号最小颜色
			if (a[i] < a[minid]) {
				minid = i;
			}
		}
		minidl = L[a[minid]];
		minidr = R[a[minid]];
		if (!(l <= minidl && r >= minidr) && !(r <  minidl && l > minidr)) {
			return tong[l][r] = 0;
		}
		for (int i = l; i <= minidl; i++) {
			tmp1 = (tmp1 + dfs(l, i - 1) * dfs(i, minidl - 1) % Mod) % Mod;
		}
		for (int i = minidr; i <= r; i++) {
			tmp2 = (tmp2 + dfs(minidr + 1, i) * dfs(i + 1, r) % Mod) % Mod;
		}
		tong[l][r] = tmp1 * tmp2 % Mod;
		for (int i = l; i <= r; i++) {
			if (a[i] == a[minid]) {
				if (top) {
					tong[l][r] = (tong[l][r] * (dfs(top + 1, i - 1) % Mod)) % Mod;
				}
				top = i;
			}
		}
		return tong[l][r];
	}
}
inline void work() {
	memset(tong, -1, sizeof(tong));
	int len = 0, tmp, x;
	n = rd();
	m = rd();
	for (int i = 1; i <= m; i++) {
		x = rd();
		if (x != a[len]) {
			a[++len] = x;
		}
	}
	if (len > 2 * n) {
		cout << 0 << endl;
		return;
	}
	for (int i = 1; i <= len; i++) {
		R[a[i]] = i;
	}
	for (int i = len; i >= 1; i--) {
		L[a[i]] = i;
	}
	for (int i = 1; i <= len; i++) {
		tong[i][i] = L[a[i]] == i && R[a[i]] == i;
	}
	dfs(1, len);
	write(tong[1][len] % Mod);
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	work();
	return 0;
}
```


---

