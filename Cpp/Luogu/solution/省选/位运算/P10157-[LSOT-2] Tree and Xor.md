# [LSOT-2] Tree and Xor

## 题目描述

给定 $n$，你需要构造一棵 $n$ 个点的以 $1$ 为根的有根树，满足 $\bigoplus\limits_{i=1}^ndegree(i)=0$ 且 $fa_2 \sim fa_n$ 的字典序最小。其中，$\oplus$ 表示异或运算。

其中 $degree(i)$ 表示与点 $i$ 相连的点数，$fa_i$ 表示点 $i$ 的父节点且 $fa_i < i$。

你需要输出 $\sum\limits_{i=2}^ni \times fa_i$，若无解则输出 $-1$。

## 说明/提示

**「本题采用捆绑测试」**

- $\texttt{Subtask 1(5 pts)：}n \leq 7$。
- $\texttt{Subtask 2(10 pts)：} n \leq 20$。
- $\texttt{Subtask 3(20 pts)：}\sum n \leq 2000$。
- $\texttt{Subtask 4(15 pts)：}n = 2^k-1$，其中 $k$ 是自然数。
- $\texttt{Subtask 5(50 pts)：}$无特殊限制。

对于所有数据，$1\le T\le 10^6$，$2 \leq n \leq 10^{9}$。

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
2
-1```

# 题解

## 作者：sidekick257 (赞：7)

### update on 2023.2.15 感谢 @lalaouye 指出错误

无解当且仅当 $n=3$。

不难发现树高最多三层，接下来给出证明：

在第二层没接满的时候显然接到第三层不如接到第二层，在第二层满的时候第二层的点数一定可以加一而不是连到第三层，因为答案至少是 $\lfloor\frac{n}{2}\rfloor$（设 $k=\lfloor\frac{n}{2}\rfloor$，如果 $n$ 是偶数则 $1$ 下面接 $k$ 个，$2$ 下面接 $k-1$ 个，如果是奇数则考虑 $k$ 的奇偶性，如果是奇数则 $2$ 下面接 $k-2$ 个点，$3$ 和 $4$ 下面接 $1$ 个，是偶数则 $1$ 下面接 $k+1$ 个点，$2$ 下面接 $k-1$ 个点
）。

接下来考虑第二层有 $k$ 的点所需要的最少的总点数。

显然最优情况是对于 $k$ 的每一个二进制上是 $1$ 的位 $x$，都存在一个第二层的点下面接了 $2^x-1$ 个点，即 $2k-\text{count}(k)$，这样就可以轻易找到对于输入的 $n$ 第二层接了多少个点了。

接下来我们会发现我们会有最优构造完了之后剩下的点，我们可以花 $1$ 的代价把最优构造中每一个第二层中的点转接到一个接了点的的点下面，我们选择将他接到 $2$ 号点下面。

因为我们接的点的数量都是互不相同的二进制上的某一位，所以转接是不会冲突的，而为什么是最优因为如果用两个一样的来抵消一定是没有这样转接有优的，因为用两个一样的只有一半可以接到 $2$ 下面。

最后如果剩下来一个点可以直接接到 $2$ 下面不会冲突。

（PS：据说存在转成 $2n-2$ 个点的序列的做法，但是我不会证。）

---

## 作者：xieziheng (赞：2)

这是个只靠找规律的题解。

赛时 T2 做了有点久，这题没来得及把所有规律找完。

首先有一个可以轻松跑 $n\leq 100000$ 的爆搜方法，可以用来找规律。不过为了写出这个爆搜，可能要先写点更暴力的的找规。

以下记一个点的度数为父亲序列中其出现次数,记为 $d_i$。

首先显然所有的点的度数单调不增，且和为 $n-1$。这么直接爆搜应该就有 $15$ 分。注意到有度数的点只有 $\mathcal{O}(\log n)$ 个，可以设个界，记为 $m$。这样差不多可以跑 $n\leq 200$。

注意到 $n=2^k-1$ 时有序列恒为 $\frac n 2,\frac n 2 -2,1,1$ 可以获得 $15$ 分。

然后是一些常用剪枝，就是

- 搜的时候从大到小枚举，找到就不找了。

- 根据单调性、和为 $n-1$ 确定一下上下界。

再次注意到 $\frac n 2 \leq d+1 \leq \mathcal{O}(\frac n 2+\log n)$，可以粗略的把上界估计为 $\frac n 2 +3$，下界 $\frac n 2 -1$，然后 $\frac n 4 \leq d_2 \leq \frac n 2 -1$，且一般情况 $d_2 \geq 2^{k-1}-1$，$2^k<n$。

然后发现后面都形如 $2^k-1$。

这样就能跑 $n\leq 10^5$ 了。

然后需要一些比较困难的观察，就是发现 $d_1=\max_{k} {2\times k-\operatorname{popcount}(k)} <n$。然后后面的是 $n-k$ 的二进制拼凑，每一位还都减一。且 $d_2$ 把后面的 $d_3,\cdots,d_{n+1-2\times k+\operatorname{popcount}(k)}$ 都吃了。这是对的，就做完了。

```cpp

#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef long long ll;
const ll mod=998244353;
il int pc(int x){
    int s=0;
    while(x) ++s,x-=(x&-x);
    return s;
}
il int len(int x){
    int s=0;
    while(x) ++s,x>>=1;
    return s;
}
il int ccc(int x){return (x&-x)==x;}
const int N=50,inf=1e9;
int T,n,m,k,a[N],s[N],ck,l[N],r[N],pw[N];ll ans;
void dfs(int x,int sum){
    if(ck) return ;
    if(x>m){
        int y=(n-m)&1;for(int i=1;i<=m;++i) y^=(a[i]+(i>1));
        if(!y){
            ck=1;for(int i=1;i<=m;++i) s[i]=a[i];
        }
        return ;
    }
    int v=min(r[x],min(a[x-1],n-1-sum)),u=max(l[x],(n-1-sum)/(m-x+1));
    if((m-x+1ll)*u+1ll*sum<n-1) ++u;
    if(x<3){
        for(int i=v;i>=u;--i)
            a[x]=i,dfs(x+1,sum+i),a[x]=0;
    }
    else{
        int vv=upper_bound(pw,pw+31,v)-pw-1,uu=lower_bound(pw,pw+31,u)-pw;
        for(int i=vv;i>=uu;--i) a[x]=pw[i],dfs(x+1,sum+pw[i]);
    }
}
il void init(){
    pw[0]=1;
    for(int i=1;i<31;++i) pw[i]=pw[i-1]*2;
    for(int i=0;i<31;++i) --pw[i];
}
il int calc(){
    int ret=a[1];
    for(int i=2;i<=m;++i) ret^=(a[i]+1);
    ret^=(n-m)&1;
    return ret;
}
il int get(int x,int k){
    vector<int> f;
    while(x) {
        f.push_back(x%10);
        x/=10;
    }
    reverse(f.begin(),f.end());
    return f[k-1];
}
int b[N],m1;
int x,y,z;
int main(){
    scanf("%d",&T);init();int tt;
    while(T--){
        ++tt;
        scanf("%d",&n),ans=0ll;if(n==2) {puts("2");continue;}if(n==3){puts("-1");continue;}
        if(ccc(n+1)){
            s[1]=(n>>1),s[2]=(n>>1)-2,s[3]=s[4]=1,x=2;
            for(int i=1;i<=4;++i)
                ans+=((2ll*x+s[i]-1ll)*s[i]/2ll)*i,x+=s[i];
            printf("%lld\n",ans%mod);continue;
        }
        k=n/2,m=1;while(2*(k+1)-pc(k+1)<n) ++k;
        a[1]=k;
        for(int i=30;i;--i) if((k>>i)&1) a[++m]=(1<<i)-1;
        x=2*k-pc(k);
        if(x<n-1) a[2]+=n-1-x;
        for(int i=3;i<=min(m,n-x+1);++i) {
            y=a[i],a[2]+=y,a[i]=0;
        }
        m1=0;
        for(int i=1;i<=m;++i) if(a[i]) b[++m1]=a[i];
        m=m1;for(int i=1;i<=m;++i) a[i]=b[i];
        x=2;
        for(int i=1;i<=m;++i) ans+=((2ll*x+a[i]-1ll)*a[i]/2ll)*i,x+=a[i];
        
        printf("%lld\n",ans%mod);if(calc()) puts("*");
    }
    return 0;
}
```

---

## 作者：王熙文 (赞：2)

被精神污染到了。

## 思路

一眼不可做，所以先打表看看。

打表可以发现，$1$ 的度数（记作 $m$）永远 $\ge \lfloor \dfrac{n}{2}\rfloor$（记作 $k$），而且不会超过 $k+\mathcal O(\log n)$。还可以发现，树的层数不超过 $3$。

考虑证明 $m \ge k$。可以通过构造 $m=k$ 的解来证明。如果 $n$ 是偶数或 $k$ 是偶数，在 $1$ 下面接 $k$ 个点，再在 $2$ 下面接 $k-1+(n \bmod 2)$ 个点；否则，在 $1$ 下面接 $k$ 个点，再在 $2$ 下面接 $k-2$ 个点，在 $3$ 和 $4$ 下面各接一个点。容易证明这是对的。

再证明树的层数不超过 $3$。考虑将一个层数大于等于 $3$ 的节点的儿子们都接到一个层数为 $2$ 的叶子的节点下，这样度数的集合不变，而且字典序会更小。接下来只需要证明一定存在一个层数为 $2$ 的叶子了。因为 $m \ge k$，所以层数大于等于 $3$ 的点 $\le k$，因此如果不是所有的点层数都是 $3$，则一定有一个层数为 $2$ 的点为叶子。

因为 $m$ 的范围很小（下面会证明），所以考虑枚举 $m$。考虑形式化问题。设层数为 $2$ 的 $m$ 个点的子树大小为 $a_1,a_2,\cdots,a_m$，那么要求一个字典序最大的 $a$ 使得 $\forall i,a_i \ge 1;\sum a = n-1;\oplus a = m \oplus ((n-m-1) \bmod2)$。第二个限制是因为每个 $a_i$ 也是 $i$ 这个点的度数，后面的 $n-m-1$ 是叶子节点的个数。记 $x=m \oplus ((n-m-1) \bmod2)$。

因为有 $a_i \ge 1$ 比较难受，所以考虑将 $a$ 的限制改为：$\sum a = n-m-1;\oplus (a+1)=x$。这时候可以发现，$n-m-1$ 与 $x$ 的值比较接近。可以发现，$a_i$ 有值的位置至少有 $need=2\lfloor \dfrac{x}{2}\rfloor-(n-m-1)$ 个。这是因为，对于 $x$ 的二进制上除了最后一位的 $1$，都至少需要总和来贡献。而总和不够，于是就需要异或中给的 $1$。需要多少 $1$ 就是多少有值的位置。然后，容易证明，当 $m \not=k$ 时，$need >0$。这样，我们可以先特判掉 $m= k$，以防一些细节，然后在 $need>0$ 的条件下做。

当选择 $need$ 个有值的位置时，它要求这些值加 $1$ 的二进制中的 $1$ 是 $x$ 的子集且互不相交，因为如果相交了异或值就会减少。这样 $need$ 满足要求的一个条件是 $need \le \text{popcount}(2\lfloor \dfrac{x}{2}\rfloor)$。根据这个条件，可以证明 $m$ 的范围。当 $m$ 大于 $k$ 太多（$\mathcal O(\log n)$），$need$ 一定大于 $\log n$ 就不满足这个条件了。还有一个比较显然的条件是 $need \le m$。最后一个条件是对于最低位，这么异或出来的值与 $x$ 的最低位相同。我们惊奇地发现，这个条件一定满足！这个条件等价于，度数的异或和是偶数。因为度数的总和为 $2(n-1)$，所以度数为奇数的个数为偶数，就一定满足了这个条件。根据这个条件，我们还可以发现，不可能有比 $need$ 大的有值的位置。因为 $need$ 越小越满足，而且根据下面的构造可知这种构造的字典序最大。另外，如果想要通过制造值加 $1$ 的二进制中的 $1$ 位置的重复使得字典序更大也不行，因为在这种构造下，每加两个有值的位置就会产生一个位置的重复，不优。

接下来考虑构造，对于这 $need$ 个有值的位置，显然要让第一个位置越大越好。那么如果 $x$ 除了最低位的 $1$ 有 $tot$ 位，则前 $tot-need+1$ 位都给第一位位置，剩下的位给剩下的位置。这样就构造好了。

下面捋一下思路。枚举 $m$，计算出 $need$，检查是否满足上述的两个条件。如果满足，则求出 $x$ 的所有位并按照上述方法构造。注意如果前面没求出答案，使用 $m=k$ 的构造。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int n;
inline int get_sum(int l,int r)
{
	return (l+r)*(r-l+1)/2%mod;
}
int tot,a[35];
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	int t; cin>>t; while(t--)
	{
		cin>>n;
		if(n==3) { cout<<-1<<'\n'; continue; }
		int ans=-1;
		for(int m=min(n-1,n/2+15); m>=n/2+1; --m)
		{
			int x=m^((n-m-1)%2),xx=2*(x/2),ppct=__builtin_popcount(xx);
			int need=xx-(n-1-m);
			if(need<=m && need<=ppct)
			{
				tot=0;
				for(int i=30; i>=1; --i)
				{
					if(xx>>i&1) a[++tot]=(1<<i);
				}
				ans=get_sum(2,m+1)%mod;
				int sum=0;
				for(int i=1; i<=tot-need+1; ++i) sum+=a[i];
				int lst=m+1;
				for(int i=1; i<=need; ++i)
				{
					int cnt=(i==1?sum:a[tot-need+i])-1;
					ans=(ans+get_sum(lst+1,lst+cnt)*(i+1))%mod;
					lst+=cnt;
				}
				break;
			}
		}
		if(ans==-1)
		{
			if(n%2==0 || n/2%2==0) ans=(get_sum(2,n/2+1)+get_sum(n/2+2,n)*2)%mod;
			else ans=(get_sum(2,n/2+1)+get_sum(n/2+2,n-2)*2+(n-1)*3+n*4)%mod;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

神秘构造题。

首先考虑将问题转化，我们只需要求 $(\deg_1,\deg_2,\cdots,\deg_n)$ 的字典序最大值，其中满足：

1. $\deg_i \ge 1$；
2. $\sum_{i=1}^n \deg_i = 2n-2$；
3. $\bigoplus_{i=1}^n \deg_i = 0$。

这样确定了每个节点儿子的个数，每个节点贪心选编号最小且还有接口的节点当做父亲即可。

显然有 $\deg_1 \ge \deg_2 \ge \cdots \ge \deg_n = 1$，因为他们的结构高度对称。

首先考虑计算 $\deg_1$ 的最大值。

考虑 $\bigoplus_{i=2}^n \deg_i = \deg_1$，那么只考虑 $\deg_i \ge 1$ 的限制，$\sum_{i=2}^n \deg_i$ 最小是多少？

容易发现，最优情况下是把 $\deg_1$ 进行**二进制拆分**，将 $\deg_{2,3,\cdots,n}$ 中前几个赋为二的幂次，后几个赋为 $1$ 即可，得到 $\sum_{i=1}^n \deg_i \ge 2 \deg_1 + n - 1 - \text{popcount}(\deg_1)$。

考察函数 $f(x) = x - \text{popcount}(x)$，则需要满足 $f(2\deg_1) \le n-1$。显然 $f(x)$ 是单调不降的（$f(x+1)-f(x)$ 是 $x$ 和 $1$ 相加在二进制位下的进位次数）因此可以二分找到最大的 $\deg_1$。

考虑在我们刚才找到的一组 $\deg$ 的基础上略加调整，使 $\sum_{i=1}^n \deg_i = 2n-2$。容易发现，我们可以选择将一个二的幂次变为 $1$，而将原值加在 $\deg_2$ 上，这样 $\sum_{i=1}^n \deg_i$ 会整体加 $1$。

重复此过程直到 $\sum_{i=1}^n \deg_i = 2n-2$ 就行了吗？

~~第一次提交的时候我猜测 $2^k-1$ 型无解，然后交了一发，发现只有 $50$ 分，还是最后一个 $\rm Subtask$~~

对于大多数情况确实如此，因为这的确是 $\deg_2$ 能取到的最大值了，对 $\deg_3$、$\deg_4$ 都是如此（这里不是特别严谨，偏感性理解。$\deg_2$ 如果要大于这个值，会引起 $\sum \deg_i$ 的剧烈增加。）

打表发现，当 $n=2^k-1$ 时，最后得到了 $(2^{k-1}-1,2^{k-1}-1,1,1,\cdots,1)$，求和得到 $\sum \deg = 2^{k}-5$。（通过上面对 $\deg_1$ 的分析发现，如果调整到最后无法达到 $2n-2$ 的目标，必须有 $\text{popcount}(n+1)=1$，这和我们打表的结果不谋而合！）

手动模拟一下，发现你可以调整为 $(2^{k-1}-1,2^{k-1}-2,2,2,1,1,\cdots,1)$，这肯定是最优的……（但是对 $n=3$ 不成立，它无解！）

复杂度：$O(T \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MOD=998244353;
int T,n;
int f(int a) {return a*2-__builtin_popcountll(a);}
int bfind(int n) {
	int ans=-1,l=1,r=2000000000;
	while(l<=r) {
		int mid=l+r>>1;
		if(f(mid)<=n-1) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int sum(int l,int r) {
	int v1=(r-l+1),v2=l+r;
	if(v1%2==0) v1/=2;
	else v2/=2;
	v1%=MOD,v2%=MOD;
	return v1*v2%MOD;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		if(((n+1)&(-n-1))==n+1)	{
			if(n==3||n==1) {cout<<-1<<'\n';continue ;}
			int ans=sum(2,(n+1)/2)+2*sum((n+1)/2+1,n-2)+3*(n-1)+4*n;
			cout<<(ans%MOD)<<'\n';
			continue ;
		}
		int deg1=bfind(n);
		vector<int> pos,ans;
		int rst=(n+n-2)-(2*deg1+n-1-__builtin_popcount(deg1));
		roff(i,30,0) if(deg1&(1ll<<i)) pos.push_back(i);
		int ad=0;
		ffor(i,0,rst) ad+=(1ll<<pos[i]);
		ans.push_back(ad);
		ffor(i,rst+1,pos.size()-1) ans.push_back(1<<pos[i]);
		int res=0,tot=1,psl=1;
		res=sum(2,deg1+1),tot+=deg1;
		for(auto id:ans) ++psl,res=(res+psl*sum(tot+1,tot+id-1))%MOD,tot+=id-1;
		cout<<res<<'\n';
	}
	return 0;
}
```

---

