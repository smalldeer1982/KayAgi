# Gifts from Grandfather Ahmed

## 题目描述

Grandfather Ahmed's School has $ n+1 $ students. The students are divided into $ k $ classes, and $ s_i $ students study in the $ i $ -th class. So, $ s_1 + s_2 + \ldots + s_k = n+1 $ .

Due to the upcoming April Fools' Day, all students will receive gifts!

Grandfather Ahmed planned to order $ n+1 $ boxes of gifts. Each box can contain one or more gifts. He plans to distribute the boxes between classes so that the following conditions are satisfied:

1. Class number $ i $ receives exactly $ s_i $ boxes (so that each student can open exactly one box).
2. The total number of gifts in the boxes received by the $ i $ -th class should be a multiple of $ s_i $ (it should be possible to equally distribute the gifts among the $ s_i $ students of this class).

Unfortunately, Grandfather Ahmed ordered only $ n $ boxes with gifts, the $ i $ -th of which contains $ a_i $ gifts.

Ahmed has to buy the missing gift box, and the number of gifts in the box should be an integer between $ 1 $ and $ 10^6 $ . Help Ahmed to determine, how many gifts should the missing box contain, and build a suitable distribution of boxes to classes, or report that this is impossible.

## 说明/提示

In the first test, Grandfather Ahmed can buy a box with just $ 1 $ gift. After that, two boxes with $ 7 $ gifts are sent to the first class. $ 7 + 7 = 14 $ is divisible by $ 2 $ . And the second class gets boxes with $ 1, 7, 127 $ gifts. $ 1 + 7 + 127 = 135 $ is evenly divisible by $ 3 $ .

In the second test, the classes have sizes $ 6 $ , $ 1 $ , $ 9 $ , and $ 3 $ . We show that the available boxes are enough to distribute into classes with sizes $ 6 $ , $ 9 $ , $ 3 $ , and in the class with size $ 1 $ , you can buy a box of any size. In class with size $ 6 $ we send boxes with sizes $ 7 $ , $ 1 $ , $ 7 $ , $ 6 $ , $ 5 $ , $ 4 $ . $ 7 + 1 + 7 + 6 + 5 + 4 = 30 $ is divisible by $ 6 $ . In class with size $ 9 $ we send boxes with sizes $ 1 $ , $ 2 $ , $ 3 $ , $ 8 $ , $ 3 $ , $ 2 $ , $ 9 $ , $ 8 $ , $ 9 $ . $ 1 + 2 + 3 + 8 + 3 + 2 + 9 + 8 + 9 = 45 $ is divisible by $ 9 $ . The remaining boxes ( $ 6 $ , $ 5 $ , $ 4 $ ) are sent to the class with size $ 3 $ . $ 6 + 5 + 4 = 15 $ is divisible by $ 3 $ .

## 样例 #1

### 输入

```
4 2
7 7 7 127
2 3```

### 输出

```
1
7 7 
7 127 1```

## 样例 #2

### 输入

```
18 4
1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9
6 1 9 3```

### 输出

```
9
7 1 7 6 5 4 
9 
1 2 3 8 3 2 9 8 9 
6 5 4```

# 题解

## 作者：xujindong_ (赞：1)

这个题的核心结论是 Erdős-Ginzburg-Ziv 定理：对于任意 $2n-1$ 个整数，总可以从中选出 $n$ 个整数使它们的和为 $n$ 的倍数。

引理一：对于任意的 $n,m$，若定理成立，则其也对 $nm$ 成立。

对于 $2nm-1$ 个数，先取出 $n-1$ 个数，此时还剩 $(2m-1)n$ 个数。重复 $2m-1$ 次以下过程：每次加入 $n$ 个数，在 $2n-1$ 个数中取出 $n$ 个数使其和是 $n$ 的倍数。最后会得到 $2m-1$ 组数，每组 $n$ 个，且每组的和为 $n$ 的倍数，取出 $m$ 组使和为 $m$ 的倍数即可。

引理二：定理对所有质数成立。

当众数出现大于等于 $n$ 次，取出 $n$ 个众数即可。

否则，可以将数划分为 $n-1$ 对和一个单独的数，每一对中的数不相同。这个排序后第 $i$ 个和第 $n-i+1$ 个配对即可。先选上每对一个和单独的数，设和模 $n$ 余 $r$，此时相当于有 $n-1$ 个模 $n$ 非 $0$ 的数，分别为每对中选的数和未选数的差，要用这些数凑出任意一个模 $n$ 余 $r$。

考虑构造出一颗树，编号 $0\sim n-1$，边权是这 $n-1$ 个数，且 $0$ 号节点到 $i$ 号节点的距离模 $n$ 为 $i$，最后节点 $r$ 到根的路径即为所求。

考虑从根节点不断扩展，按顺序连边，每次连接树内一点和树外一点，则一定能构造出一种合法方案。假设当前边无法连接，设边权为 $w$，因为 $0$ 在树中，所以 $w$ 在树中。类似地，$2w\bmod n,3w\bmod n,\cdots,kw\bmod n$ 在树中。因为 $n$ 是质数，所以 $kw\bmod n$ 遍历所有点，此时所有点都已加入树中。

对于此题，根据 EGZ 定理，当有至少 $2s_i-1$ 个盒子时一定有解。将 $s_i$ 从小到大处理，每次取 $2s_i-1$ 个盒子构造 EGZ，则除了最大值外都可以满足。设 $f_{i,j,k}$ 为前 $i$ 个取了 $j$ 个余数为 $k$，用一个背包 $O(\frac{n^3}w)$ 求解。最大值用自己准备的盒子调整即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[205],s[205],id[205],pos,ans[205][205],q[205],cnt,temp[205];
bitset<205>f[205][205];
bool cmp(int a,int b){
  return s[a]<s[b];
}
int main(){
  cin>>n>>m;
  for(int i=1;i<=n;i++)cin>>a[i];
  for(int i=1;i<=m;i++)cin>>s[i],id[i]=i;
  sort(id+1,id+m+1,cmp);
  for(int i=1;i<m;i++){
    int t=s[id[i]];
    while(cnt<2*t-1)q[++cnt]=a[++pos];
    for(int x=0;x<2*t;x++)for(int y=0;y<=t;y++)f[x][y].reset();
    f[0][0][0]=1;
    bitset<205>r;
    for(int x=0;x<t;x++)r[x]=1;
    for(int x=1;x<2*t;x++){
      for(int y=0;y<=t;y++)f[x][y]=f[x-1][y];
      for(int y=1;y<=t;y++)f[x][y]|=f[x-1][y-1]<<(q[x]%t)|f[x-1][y-1]>>(t-q[x]%t),f[x][y]&=r;
    }
    int now=0,num=0;
    for(int x=2*t-1,y=t,z=0;x>0;x--){
      if(f[x-1][y][z])temp[++now]=q[x];
      else ans[id[i]][++num]=q[x],y--,z=((z-q[x])%t+t)%t;
    }
    cnt=now,memcpy(q,temp,sizeof(q));
  }
  while(pos<n)q[++cnt]=a[++pos];
  int sum=0;
  for(int i=1;i<=cnt;i++)sum=(sum+q[i])%s[id[m]];
  cout<<s[id[m]]-sum<<'\n',memcpy(ans[id[m]],q,sizeof(ans[id[m]])),ans[id[m]][cnt+1]=s[id[m]]-sum;
  for(int i=1;i<=m;i++)for(int j=1;j<=s[i];j++)cout<<ans[i][j]<<(j==s[i]?'\n':' ');
  return 0;
}
```

对于 EGZ 定理，上面的定理已经天然地给出了一个构造方法。瓶颈在于构造树时快速找一个 $k$ 使 $kw\bmod n$ 在树中且 $(k+1)w\bmod n$ 不在树中。考虑二分。先随便找一个 $k$ 使 $kw\bmod n$ 不在树中作为二分右边界，这可以随便找一个不在树中的点 $q$，$k=qw^{-1}\bmod n$。虽然没有单调性，但在二分过程中可以始终保持左端点在树中，右端点不在树中，最终必能找到合法点。$O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,prime[205],lpf[205],a[205],s[205],q[205],cnt,temp[205],pos;
bool vis[205],f[205];
pair<int,int>id[205];
vector<int>ans[205];
template<typename T>T qpow(T a,T b,T n,T ans=1){
  for(a%=n;b;b>>=1)b&1&&(ans=1ll*ans*a%n),a=1ll*a*a%n;
  return ans;
}
template<typename T>T inv(T a,T b){
  return qpow(a,b-2,b);
}
int prime_init(int n,int prime[],int lpf[],bool a[],int cnt=0){
  lpf[1]=1;
  for(int i=2;i<=n;i++)a[i]=1;
  for(int i=2;i<=n;i++){
    if(a[i])prime[++cnt]=i,lpf[i]=i;
    for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
      a[i*prime[j]]=0,lpf[i*prime[j]]=prime[j];
      if(i%prime[j]==0)break;
    }
  }
  return cnt;
}
void solve(int n,int a[],bool ans[]){
  int cnt[n],f[n],v[n],r=0;
  bool vis[n];
  pair<int,int>id[2*n];
  memset(cnt,0,sizeof(cnt)),memset(vis,0,sizeof(vis)),vis[0]=1;
  for(int i=1;i<2*n;i++)cnt[a[i]%n]++,ans[i]=0,id[i]=make_pair(a[i]%n,i);
  for(int i=0;i<n;i++){
    if(cnt[i]>=n){
      for(int j=1,num=0;num<n;j++)if(a[j]%n==i)ans[j]=1,num++;
      return;
    }
  }
  sort(id+1,id+2*n);
  for(int i=n;i<2*n;i++)r=(r+id[i].first)%n;
  for(int i=1,w,p=1;i<n;i++){
    w=(id[n+i-1].first-id[i].first+n)%n;
    while(vis[p])p++;
    int l=0,r=1ll*p*inv(w,n)%n;
    while(l+1<r){
      int mid=(l+r)>>1;
      if(vis[1ll*mid*w%n])l=mid;
      else r=mid;
    }
    f[1ll*r*w%n]=1ll*l*w%n,v[1ll*r*w%n]=i,vis[1ll*r*w%n]=1; 
  }
  memset(vis,0,sizeof(vis));
  while(r)vis[v[r]]=1,r=f[r];
  for(int i=1;i<n;i++){
    if(vis[i])ans[id[i].second]=1;
    else ans[id[n+i-1].second]=1;
  }
  ans[id[2*n-1].second]=1;
}
void egz(int n,int a[],bool ans[]){
  if(lpf[n]==n){
    solve(n,a,ans);
    return;
  }
  int x=lpf[n],y=n/x,q[2*x],id[2*x],temp1[2*x],temp2[2*x],b[2*y][x],sum[2*y];
  bool f[2*x],g[2*y];
  memset(sum,0,sizeof(sum));
  for(int i=1;i<2*n;i++)ans[i]=0;
  for(int i=1;i<x;i++)q[i]=a[i],id[i]=i;
  for(int i=1,pos=x-1,cnt=x-1;i<2*y;i++){
    while(cnt<2*x-1)q[++cnt]=a[++pos],id[cnt]=pos;
    solve(x,q,f);
    int now=0,num=0;
    for(int j=1;j<=cnt;j++){
      if(f[j])b[i][num++]=id[j],sum[i]+=q[j];
      else temp1[++now]=q[j],temp2[now]=id[j];
    }
    cnt=now;
    for(int j=1;j<=cnt;j++)q[j]=temp1[j],id[j]=temp2[j];
  }
  for(int i=1;i<2*y;i++)sum[i]/=x;
  egz(y,sum,g);
  for(int i=1;i<2*y;i++)if(g[i])for(int j=0;j<x;j++)ans[b[i][j]]=1;
}
int main(){
  cin>>n>>m,prime_init(n+1,prime,lpf,vis);
  for(int i=1;i<=n;i++)cin>>a[i];
  for(int i=1;i<=m;i++)cin>>s[i],id[i]=make_pair(s[i],i);
  sort(id+1,id+m+1);
  for(int i=1;i<m;i++){
    int t=id[i].first;
    while(cnt<2*t-1)q[++cnt]=a[++pos];
    egz(t,q,f);
    int now=0;
    for(int j=1;j<=cnt;j++){
      if(f[j])ans[id[i].second].push_back(q[j]);
      else temp[++now]=q[j];
    }
    cnt=now;
    for(int j=1;j<=cnt;j++)q[j]=temp[j];
  }
  while(pos<n)q[++cnt]=a[++pos];
  int sum=0;
  for(int i=1;i<=cnt;i++)sum=(sum+q[i])%id[m].first,ans[id[m].second].push_back(q[i]);
  cout<<id[m].first-sum<<'\n',ans[id[m].second].push_back(id[m].first-sum);
  for(int i=1;i<=m;i++)for(int j=0;j<s[i];j++)cout<<ans[i][j]<<(j==s[i]-1?'\n':' ');
  return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
被结论题创飞了。

摘自[杂题选做 Part 4. dp](https://www.luogu.com.cn/training/660942)。
## 思路分析
做这题首先需要知道 Erdős-Ginzburg-Ziv 定理，不然完全没法下手。

> Erdős-Ginzburg-Ziv 定理：$n$ 是一个任意的正整数，则在 $2n-1$ 个无限制整数中，必定存在 $n$ 个整数，他们的和是 $n$ 的倍数。

我们不难发现这个 $2n-1$ 是一个下限。

对于 $2n-2$，我们可以考虑构造 $n-1$ 个 $0$ 和 $n-1$ 个 $1$，此时凑不出 $0$ 也凑不出 $n$，所以不是 $n$ 的倍数。

然后我们来考虑怎么证明这个定理。

下面给出一种比较人类智慧的证明方法。

具体思路大概是证明素数情况成立，然后证明具有积性从而覆盖所有正整数。

1. 我们先来考虑 $n$ 为素数的情况。
   
   此时我们不妨设这 $2n-1$ 个数分别为 $a_1,a_2,\dots,a_{2n-1}$，且满足 $0\le a_1\le a_2\le\dots\le a_{2n-1}<n$，这是不失一般性的。

   当 $a_i=a_{i+n-1}(i\le n)$ 时，显然是成立的，因为至少有 $n$ 个相同的数出现，加一块的和一定是 $n$ 的倍数。

   否则我们就有：$\forall a_i\not=a_{i+n-1}(i\le n)$。

   考虑证明一个更强的命题 $\forall w,\exist A\in\{a_1,a_2,\dots,a_{2n-1}\},|A|=n,\sum\limits_{x\in A}x\equiv w\pmod n$。

   也就是说我们可以找到 $n$ 个大小为 $n$ 的集合构成模 $n$ 的完系。

   证明而言我们考虑利用 $\forall a_i\not=a_{i+n-1}(i\le n)$，不妨定义 $S_i=\{a_i,a_{i+n-1}\}(i<n)$，特殊的我们有 $S_n=\{a_{2n-1}\}$。

   再取 $B_i=S_1+S_2+\dots+S_i(i<n)$ 组成的**不可重**集合，也就是模 $n$ 意义下的和集。

   我们会有 $|B_1|=2$（因为 $a_1\not=a_n$）。

   那么其实我们有一个结论是 $|B_i|\ge i+1$。

   证明考虑反证法，不妨假设 $|B_x|\le i$，且 $x$ 为最小的满足这个条件的数。

   那我们有 $|B_{x-1}|>x-1,|B_{x-1}|\le|B_x|\le x$。

   把第一个式子变成 $\le$ 接起来可以得到：$x\le|B_{x-1}|\le|B_x|\le x$。

   那么就有 $|B_{x-1}|=|B_x|=x$。

   我们考虑定义 $C=B_{x-1}+\{a_x\},D=B_{x-1}+\{a_{x+n-1}\}$。

   那么我们有 $x=|B_{x-1}|\le C,D\le |B_x|=x$。

   也就是可以得到 $C=D\pmod n$。

   因为我们有 $\forall a_i\not=a_{i+n-1}(i\le n)$，且对一个模 $n$ 环进行两次位移不同的平移后得到的环肯定是不同的。

   所以我们可以得到当且仅当 $C$ 为模 $n$ 意义下的完系，才可能有 $C=D\pmod n$。

   回忆下上文对于 $x$ 的限制，我们有 $x<n$。

   也就是 $|C|=x<n$，必然不可能是完系。

   也就是上文的假设是错误的，可以得到 $\forall i,|B_i|\ge i+1$。

   注意到 $|B_{n-1}|\ge n$，即为模 $n$ 的完系。

   那么我们定义 $C=B_{n-1}+A_n$，就有 $C$ 亦为模 $n$ 的完系。

   同时根据和集的定义，我们知道 $C$ 中的每一个元素都可以用 $a_{b_1}+a_{b_2}+\dots+a_{b_n},1\le b_i\le 2n-1$ 表示出来。

   也就是说我们可以选出 $n$ 个 $a$ 序列中的数来构成 $C$ 中的任何一个数，即为构成一个模 $n$ 的完系。

   也就是原命题得证。

   通过原命题我们也不难得到当 $n$ 为素数时定理是成立的。

2. 然后我们来证明这个命题是积性的，也就是如果对于 $n$ 成立，对于 $m$ 成立，那么对于 $nm$ 也成立。

   我们不妨设这 $2nm-1$ 个数分别为 $a_1,a_2,\dots,a_{2nm-1}$。

   不妨从中取出 $2n-1$ 个数，那么我们知道对于这 $2n-1$ 个数有一定可以取出 $n$ 个数满足其和为 $n$ 的倍数。

   不失一般性而言，我们不妨设这 $n$ 个数是 $a_1,a_2,\dots,a_n$，则我们有 $n\mid\sum\limits_{i=1}^n a_i$。

   再取出 $a_{n+1},a_{n+2},\dots,a_{3n-1}$ 这 $2n-1$ 个数，同理我们不妨设 $n\mid\sum\limits_{i=n+1}^{2n} a_i$。

   一直这样做下去我们就可以得到：

   $$n\mid\sum\limits_{i=1+kn}^{(k+1)n} a_i(0\le k\le2m-2)$$

   令 $b_{k+1}=\sum\limits_{i=1+kn}^{(k+1)n} a_i(0\le k\le2m-2)$，则有 $\forall n\mid b_i(1\le i\le 2m-1)$。

   这里恰好有 $2m-1$ 个数，所以我们可以从中取出 $m$ 个数满足和为 $m$ 的倍数，不妨设为 $m\mid\sum\limits_{i=1}^m b_i$。

   显然的是由上面的条件我们还有 $n\mid\sum\limits_{i=1}^m b_i$。

   但这样会有一些问题，这样推导出来的是积性不是完全积性。

   当然也非常好解决，我们直接令 $c_i=\frac{b_i}{n}(1\le i\le2m-1)$，再套一步上面的得到 $m\mid\sum\limits_{i=1}^m c_i$，最后把分母 $n$ 同意乘回去就可以得到 $mn|\sum\limits_{i=1}^m b_i$。

   最后再把 $b_i$ 用定义式展开就得到了：$mn|\sum\limits_{i=1}^{nm} a_i$。

   这个显然是满足命题的，所以原命题得证。
3. 最后一步就非常简单了，对于一个任意的正整数 $n$，我们将其质因数分解为 $p_1^{a_1}p_2^{a_2}\dots p_m^{a_m}$。

   首先我们知道对于 $p_1,p_2,\dots p_m$ 命题成立。接着通过 $2.$ 中所证明的取 $n=p_1,m=p_1^i$ 证明 $p^{i+1}$ 成立从而得到 $p_1^{a_1}$ 成立。

   最后再把这些通过 $2.$ 中证明的乘在一起就可以得到对 $n$ 成立了，也就是我们证明了这个定理。

接着回归原题（证明好像是有点长了）。

首先我们根据定理知道，对于一个有着 $s_i$ 个学生的班级，我们只需要 $2s_i-1$ 个盒子就能保证能构造出一个倍数。

感性理解下这个部分，需要 $2s_i-1$ 个盒子能保证构造，但是构造需要消耗 $s_i$ 个盒子，不难发现先满足大的是不优秀的。

那我们按从小到大的顺序来尝试满足，则有 $s_1\le s_2\le\dots\le s_k$，且有 $\sum\limits_{i=1}^k=n+1$。

当我们考虑到 $s_k$ 时，可以用新增的一个盒子直接来满足他。

接下来我们希望证明肯定可以满足剩下的 $s_i$。

极限情况即为 $s_{k-1}$，那么我们希望有 $2s_{k-1}-1>n-\sum\limits_{i=1}^{k-2} s_i$。

右边那个和式不好搞，我们直接由 $\sum\limits_{i=1}^k s_i=n+1$ 把它化掉得到：
$$2s_{k-1}-1>n-(n+1-s_{k-1}-s_k)$$
$$s_{k-1}>s_k$$
这显然是和我们钦定的不降矛盾的。

也就是说对于任意的情况都有解，我们只需要从小到大的满足 $s_1,s_2\dots,s_{k-1}$，最后再多造一个盒子满足 $s_k$ 即可。

接着是如何实现的问题。

我们考虑先枚举目前需要满足的是 $s_i$，然后枚举未用的盒子。

定义 $f_{i,j,k}$ 表示前 $i$ 个数取了 $j$ 个能否得到模意义下的 $k$。

状态转移方程是平凡的就不再赘述，这样的复杂度是 $O(n^3)$。

可以考虑用过 bitset 在转移的时候前后分段断开平移拼接优化，这样就可以做到 $O(\frac{n^3}{\omega})$。

最后构造答案也是平凡的，根据我们的 dp 转移式子倒着跑回去就知道选了哪个数了。

注意记得添加最后一个数来补偿不足的部分。
## 代码
很好写，一遍过了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=200+10,M=2,V=80,mod=1e9+7,INF=1e10;
int n,m,a[N],mp[N];bool f[N][N][N];
pair<int,int>s[N];vector<int>ans[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='?'||c=='<'||c=='='||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int del(int x,int y,int mod){return ((x-y)%mod+mod)%mod;}
inline void solve()
{
	n=read(),m=read();for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) s[i]={read(),i};sort(s+1,s+1+m);
	for(int i=1,w;i<m;i++)
	{
		w=s[i].first;
		for(int j=1;j<=n;j++) for(int k=0;k<=j;k++)
			for(int l=0;l<w;l++) f[j][k][l]=0;
		f[0][0][0]=1;
		for(int j=1;j<=n;j++) for(int k=0;k<=min(w,j);k++)
			for(int l=0;l<w;l++)
			{
				if(f[j-1][k][l]) f[j][k][l]=1;
				if(!mp[j]&&k) f[j][k][l]|=f[j-1][k-1][del(l,a[j],w)];
			}
		for(int j=n,ss=0,tot=w;j>=1&&tot;j--)
		{
			if(mp[j]) continue;
			if(f[j-1][tot-1][del(ss,a[j],w)])
				ans[s[i].second].emplace_back(a[j]),mp[j]=1,ss=del(ss,a[j],w),tot--;
		}
	}int ss=0,id=s[m].second,w=s[m].first;
	for(int i=1;i<=n;i++) if(!mp[i]) ss+=a[i],ans[id].emplace_back(a[i]);
	ss%=w;print(w-ss);put('\n');ans[id].emplace_back(w-ss);
	for(int i=1;i<=m;i++,put('\n')) for(auto x:ans[i]) print(x),put(' ');
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}

```

---

## 作者：ღꦿ࿐ (赞：0)

结论题，算是被 *2500 打爆了。


[EGZ 定理：](https://mathoverflow.net/questions/16721/egz-theorem-erd%C5%91s-ginzburg-ziv) 


对于 $2n-1$ 个数，我们一定能选出 $n$ 个，使得其和是 $n$ 的倍数。

这个定理告诉我们，只要一个班的人数不大于目前没有分配的包数的一半，那么一定存在一种方式使得这个班能够分配到 $s$ 袋和为 $s$ 倍数的糖果。

考虑只让这样的班（人数大于目前没分配的其它班）有一个，最后用自由的那袋去调整，方法是只需要把最大的班放在最后就行了，这样其他班都满足剩余袋数 $\geq 2n-1$ 的。

这样只需要依次满足每个班的需求就行了，这是一个简单 dp，$f_{i,j,k}$ 能否表示前 $i$ 袋，拿了 $j$ 袋，余数为 $k$，复杂度 $O({n^3})$，注意到 dp 值是 boolean 的，所以可以压缩到 $O(\frac {n^3} w)$。

---

## 作者：jasonliujiahua (赞：0)

# CF1798F

[题目传送门](https://www.luogu.com.cn/problem/CF1798F)
## 题意简述：

你有 $n$ 个盒子，第 $i$ 个盒子里面有 $a_i$ 个礼物。你要把盒子送给 $k$ 个班级，第 $i$ 个班级有 $s_i$ 个学生。保证 $\sum_{i=1}^k s_i=n+1$。

你需要再准备一个盒子（里面的礼物数量由你自己决定），使得存在一种划分盒子的方案，让第 $i$ 个班级恰好收到 $s_i$ 个盒子且其中的礼物总数是 $s_i$ 的倍数。

若无解，输出 `-1`。

若有解，第一行输出一个数 $s$，表示需要准备的盒子中的礼物个数（$1\leq s\leq 10^6$）。接下来 $k$ 行，第 $i$ 行输出 $s_i$ 个数，表示给第 $i$ 个班级的每个盒子中的礼物个数。

$1\leq n,k\leq 200$。
## 题目分析：
### Step 1：初步分析
由 EGZ 定理：在 $2n-1$ 个数中一定能选出 $n$ 个数使得他们的和为 $n$ 的倍数。这也就意味着，只要 $s_i$ 小于所有数的一半，就一定能找到答案。那么怎么让所有 $s_i$ 都小于当前剩下数的一半呢？只需要让最大的数在最后一个即可。而题目还给了我们一个自由的数，因此无论如何所有 $s_i$ 都能被满足。
根据以上分析，考虑将 $s$ 从小到大排序（其实只要让最大的数在最有一个即可）。
### Step 2：DP
接下来安心地考虑如何计算答案。由于答案和
1. 选的数的个数（最终为 $s_i$）
2. 选出的所有的数的和模 $s_i$ 的余数

。因此将他们都扔进状态，设 $dp_{j,k,w}$ 表示前 $j$ 个数中选 $k$ 个得到模 $s_i$ 余数为 $w$ 是否可行，有转移方程：
$$dp_{j,k,w}=dp_{j-1,k-1,(w-a[j])\bmod s_i} | dp_{j-1,k,w}$$
我们对每个 $i$ 都跑一遍这个 dp，并取没有被前面选过的数计入答案（因为一定有解）即可。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=210;
int n,m,a[maxn];
bool dp[maxn][maxn][maxn],vis[maxn];
vector<int> ans[maxn];
struct node
{
    int val,id;
}b[maxn];
bool cmp(node x,node y)
{
    return x.val<y.val;
}
void init()
{
    cin>>n>>m; 
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i].val,b[i].id=i;
    sort(b+1,b+m+1,cmp);
}
void DP()
{
    for(int i=1;i<m;i++)
    {
        int x=b[i].val;
        for(int j=1;j<=n;j++)
            for(int k=0;k<=j;k++)
                for(int w=0;w<x;w++)
                    dp[j][k][w]=0;
        dp[0][0][0]=1;
        for(int j=1;j<=n;j++)
        {
            for(int k=0;k<=min(x,j);k++)
            {
                for(int w=0;w<x;w++)
                {
                    if(!vis[j] && k) dp[j][k][w]|=(dp[j-1][k-1][((w-a[j])%x+x)%x]|
                    dp[j-1][k][w]);
                    else dp[j][k][w]|=dp[j-1][k][w];
                }
            }
        }
        int tmp=0,sum=x;
        for(int j=n;j;j--)
        {
            if(vis[j]) continue;
            if(sum==0) break;
            if(dp[j-1][sum-1][((tmp-a[j])%x+x)%x])
            {
                tmp=((tmp-a[j])%x+x)%x;
                sum--;
                ans[b[i].id].push_back(a[j]);
                vis[j]=1;
            }
        }
    }
    int sum=0,x=b[m].val;
    for(int j=1;j<=n;j++)
    {
        if(vis[j]) continue;
        sum=(sum+a[j])%x;
        ans[b[m].id].push_back(a[j]);
    }
    ans[b[m].id].push_back(((x-sum)%x+x)%x+x);
}
void output()
{
    cout<<ans[b[m].id].back()<<endl;
    for(int i=1;i<=m;i++)
    {
        for(int j=0;j<ans[i].size();j++)
            cout<<ans[i][j]<<" ";
        cout<<endl;
    }
}
signed main()
{
    init();
    DP();
    output();
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

结论题，不知道结论被打爆了！！！

EGZ 定理：在 $2n-1$ 个数中一定能选出 $n$ 个数使得他们的和为 $n$ 的倍数。

那么这个题就比较简单了。由于分配是没有顺序限制的，我们钦定 $b_i$ 为升序。

由于 $b_{i+1}>b_i$，所以 $b_i+b_{i+1}>2b_i-1$，因此对于 $i<k$ 的所有 $b_i$ 我们都可以成功分配。而对于最后一个数 $b_k$，我们可以算出剩余的 $a_i$ 的和，然后补上一个数使得它们模 $b_k$ 为 $0$。

那么只需要考虑如何分配。记录尚未被占用的 $a_i$，假设考虑到了 $b_j$，那么我们取前 $2b_j-1$ 个，令 $f_{i,j,k}$ 表示前 $i$ 个数选 $j$ 个，这些数的和模 $b_i$ 为 $k$ 时是否可行。最后的状态就是 $f_{2b_i-1,b_i,0}$。

至于选择的方案，每次转移的时候直接记录以下从哪里来的即可。暴力转移是 $O(b_i^3)$，总复杂度是 $O(\sum {b_i}^3)$。

由于 $\sum b_i=n+1$，所以 ${b_i}^2 \leq (n+1)^2$，所以 $\sum {b_i}^3 \leq \sum b_i(n+1)^2 \leq (n+1)^2\sum b_i=n(n+1)^2$，可以粗略看成 $O(n^3)$。

因此复杂度为 $O(n^3)$，可以通过。

[Code & Submission](https://codeforces.com/contest/1798/submission/224257836)

---

