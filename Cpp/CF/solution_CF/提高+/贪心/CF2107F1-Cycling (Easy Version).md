# Cycling (Easy Version)

## 题目描述

> 这是此问题的简单版本，和其他版本的区别是此版本中 $n\le 5000$，且你不需要对每个前缀都求解。

Leo 骑车去见他的女朋友。在 Leo 的前面有 $n$ 名骑手，从前往后排在第 $i$ 名的骑手的灵活度为 $a_i$。

Leo 将要加速超过前面的所有骑手，他可以执行以下两种操作：
- 当他在骑手 $i$ 后面，骑手 $i+1$ 前面（或 $i=n$）时，付出 $a_i$ 的代价超过骑手 $i$，之后他将在骑手 $i$ 前面，骑手 $i-1$ 后面（如果 $i>1$）；
- 使用他的超级力量交换 $a_i$ 和 $a_j$，代价为 $\vert i-j\vert$。

请你找出超过所有 $n$ 名骑手的最小代价。

## 说明/提示

**样例解释**

第一组数据中，一组操作如下所示：
- 交换 $a_2$ 和 $a_3$，之后 $a=(1,4,2)$，代价为 $1$；
- 超过第 $3$ 名骑手，代价为 $2$；
- 交换 $a_1$ 和 $a_2$，$a=(4,1,2)$，代价为 $1$；
- 超过第 $2$ 名骑手，代价为 $1$；
- 交换 $a_1$ 和 $a_2$，$a=(1,4,2)$，代价为 $1$；
- 超过第 $1$ 名骑手，代价为 $1$。

总代价为 $7$。可以证明这是最小的代价。

第二组数据中如果一直执行“超过”操作，花费为 $4$。可以证明这是最小的代价。

By chenxi2009

## 样例 #1

### 输入

```
4
3
1 2 4
4
1 1 1 1
2
1 2
4
4 1 3 2```

### 输出

```
7
4
3
8```

# 题解

## 作者：ax_by_c (赞：7)

前面错完了不知道在干什么，最后半小时的时候才过 C，还好有这道题不然就掉大分了。

喜报：好像是第一次写斜率优化。

这个交换显然可以写成相邻交换的形式，不难发现最终的过程一定是将序列分段，每段一直选择一个人。

于是考虑 DP，设 $f_i$ 为从最后面骑到第 $i$ 个人前面的最小代价，初始 $f_{n+1}=0$，转移枚举上一段终点和选择的人可得 $f_{i}=\min_{i\le x<j}f_j+2j-i-x-2+(j-i)a_x$。

这里本来应该有一些观察的，但是我不想思考了。考虑斜率优化，推导可知当 $x<y$ 且 $(j-i)a_x-x>(j-i)a_y-y$ 时 $\frac{a_x-a_y}{x-y}<\frac{1}{j-i}$，于是维护上凸壳即可，转移点也是单调的，时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll llinf=3e18;
const int N=5e3+5;
int n,stk[N],top;
ll a[N],f[N];
double cal(int x,int y){
	return (double)(a[x]-a[y])/(double)(x-y);
}
void slv(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%lld",&a[i]);
	rep(i,1,n)f[i]=llinf;
	f[n+1]=0;
	per(i,n,1){
		top=0;
		int mxp=1;
		rep(j,i+1,n+1){
			while(top>=2&&cal(stk[top-1],j-1)<=cal(stk[top-1],stk[top]))top--;
			stk[++top]=j-1;
            mxp=min(mxp,top);
			while(mxp<top&&cal(stk[mxp],stk[mxp+1])<1.0/(double)(j-i))mxp++;
            while(mxp>1&&cal(stk[mxp-1],stk[mxp])>=1.0/(double)(j-i))mxp--;
			f[i]=min(f[i],f[j]+j*2-2-i-stk[mxp]+a[stk[mxp]]*j-a[stk[mxp]]*i);
		}
	}
	printf("%lld\n",f[1]);
}
void main(){
	int T=1;
	// int csid=0;scanf("%d",&csid);
    scanf("%d",&T);
    while(T--)slv();
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Eous (赞：6)

我们设 $dp_i$ 表示跳到了 $i$ 后面还要多少代价才能跳到最前。初始有 $dp_0 = 0$。转移时考虑最后一个区间 $[j + 1,i]$。我们发现最优策略是把 $[j + 1,i]$ 里的最小值拿过来一直超，代价为 $(i - pos) + (i - j - 1) + val \times (i - j)$，分别表示把最小值掏过来，最小值跟着走，超最小值的总代价。于是我们拥有 $O(n^2)$ dp，可以通过简单版。

```cpp
#include<bits/extc++.h>
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const int maxn = 1e6 + 5;
int n;
int a[maxn],dp[maxn];
void solve()
{
    scanf("%lld",&n);
    for (int i = 1; i <= n; i++)
        scanf("%lld",a + i);
    memset(dp,0x3f,sizeof(int) * (n + 5));
    dp[0] = 0;// 初始化
    for (int i = 1; i <= n; i++)
    {
        int x = inf,pos = 0;
        for (int j = i - 1; ~j; j--)
        {
            if (a[j + 1] < x)
                x = a[j + 1],pos = j + 1;// 求最小值
            dp[i] = min(dp[i],dp[j] + i - j - 1 + i - pos + (i - j) * x);// dp 转移
        }
    }
    printf("%lld\n",dp[n]);
}
signed main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：3)

怎么全是 dp 啊。

如果不考虑和前面的交换的话，即只能在 $[i,n]$ 内部交换。那么容易发现 $a_i=\min\limits_{j=i}^n\{a_j\}$，归纳易证。

那么我们令后缀 $\min$ 为 $suf_i$，答案即为 $\sum\limits(suf_i+[suf_i\ne a_i])$。

考虑和前面交换的话，容易发现只会交换一次，具体证明如下：

显然 $a_i\le suf_{i'}$ 时一定不优。

不妨反证。我们令同时存在 $i\leftrightarrow i',j\leftrightarrow j'(i<j)$，如果 $i'>j'$ 的话那么此时 $a_j$ 必须比 $a_i$ 小，否则 $j\leftrightarrow j'$ 就是没有意义的，然后容易发现 $j'\leftrightarrow i'$ 更优；如果 $i'<j'$ 的话，那么显然 $a_i<a_j$，如果它们有交的话显然可以用上面的方法找到更优策略，如果没有交的话，你进行 $i\leftrightarrow j'$ 一定是不劣的，因为 $a_i<a_j$ 所以就算多算了 $[suf_k\ne a_k]$ 的贡献但是前面的 $suf_k$ 是会减少的，所以贡献一定不增。

因此最多有一次交换。

显然 $i\leftrightarrow i'$ 之后只有 $suf_j<a_i$ 的位置会发生变化，因为 $suf$ 显然有单调性所以可以二分。因此我们求出初始答案，维护一下前缀和就行了，加上的贡献都是 $a_i+1$。

---

## 作者：快斗游鹿 (赞：1)

直接考虑最终的花费数组 $c_1,c_2\dots c_n$ 长啥样，显然的结论是 $c_1\ge c_2\ge \dots \ge c_n$，为什么呢？考虑如果 $c_i<c_{i+1}$，花费 $1$ 的代价把 $c_i$ 换到 $i+1$ 上肯定不劣。

还可以发现除了从 $i$ 换到 $i+1$ 的情况，从前面换到后面肯定不优，因为这样换最后 $c_i$ 肯定不会单调不升。所以只需要考虑从后缀里换数字，而如果要换肯定是换最近的，这个容易直接维护。

有了上述观察，可以设 $f_{i,j}$ 表示当前超过了 $i$ 个人，目前花费 $c_i=j$ 的最小代价，$j$ 需要离散化。考虑转移，如果新的 $c_i<c_{i-1}$，假设从 $j$ 变为 $k$，那么我们会从最近的 $k$ 换过来，设最近的位置在 $p$。为了避免后效性，我们让 $f_{i-1,j}$ 直接转移给 $f_{p,k}$，因为 $[i,p]$ 中的花费肯定都为 $k$，否则肯定可以换一个更好的数字给 $i$。转移代价是 $2\times(p-i)+k(p-i+1)$。如果 $c_i=c_{i-1}$，直接判第 $i$ 位的数字是否为 $j$ 即可，即 $f_{i-1,j}+j+[a_i\neq j]\to f_{i,j}$，因为如果这个数字被换过，我们肯定不会再考虑这种转移。

直接转移总时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <math.h>
#include <cstdio>
#define int long long
using namespace std;
const int inf=1e18;
struct Mod{
    int m,p;
    void init(int pp){m=((__int128)1<<64)/pp;p=pp;}
    int operator ()(int x){
        return x-((__int128(x)*m)>>64)*p;//0~2mod-1
    }
}mo;
bool M1;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=5e3+5;
int n,a[N],f[N][N],b[N],len;
int mi[N];
queue<int>pos[N];
int getlsh(int x){
	return lower_bound(b+1,b+1+len,x)-b;
}
void ckmi(int &x,int y){x=min(x,y);}
void solve(){len=0;
	n=read();for(int i=1;i<=n;i++)a[i]=read(),b[++len]=a[i];
	sort(b+1,b+1+len);len=unique(b+1,b+1+len)-b-1;
	reverse(a+1,a+1+n);
	for(int i=1;i<=len;i++)while(!pos[i].empty())pos[i].pop();
	for(int i=1;i<=n;i++)pos[getlsh(a[i])].push(i);
//	for(int i=1;i<=n;i++)cout<<getlsh(a[i])<<" ";
//	cout<<'\n';
	for(int i=0;i<=n;i++){
		for(int j=1;j<=len+1;j++)f[i][j]=mi[j]=inf;
	}
	f[0][len+1]=0;
	for(int j=1;j<=len+1;j++)mi[j]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=len;j++){
			while(!pos[j].empty()&&pos[j].front()<i)pos[j].pop();
			ckmi(f[i][j],f[i-1][j]+b[j]+(a[i]!=b[j]));
			if(!pos[j].empty()){
				int p=pos[j].front();
				ckmi(f[p][j],mi[j+1]+2*(p-i)+(p-i+1)*b[j]);
			}
		}
		mi[len+1]=inf;
		for(int j=len;j>=1;j--)mi[j]=f[i][j];
		for(int j=len-1;j>=1;j--)ckmi(mi[j],mi[j+1]);
	}
	/*for(int i=1;i<=n;i++){
		for(int j=1;j<=len;j++)cout<<f[i][j]<<" ";
		cout<<'\n';
	}*/
	cout<<mi[1]<<'\n';
	//cout<<'\n';
}
bool M2;
signed main(){
	freopen("data.in","r",stdin);
	//ios::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	int T;T=read();while(T--)solve(); 
	cerr<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC<<"ms"<<endl;
	cerr<<"Memory:"<<abs(&M1-&M2)/1024/1024<<"MB"<<endl;
	return 0;
}

```

---

## 作者：Chen_Johnny (赞：1)

# CF2107F1 Cycling (Easy Version) 题解
## 思路
让我们尝试找出最优策略。我们希望在 “超越” 操作中使用较小的值，并且会利用 “交换” 操作来降低超越的成本。

假设 $p$ 是最小值元素的第一个位置。我们应该以 $a_p$ 的成本超越第 $1,2,\cdots,p$ 位自行车手，将第 $p$ 位依次交换到第一位。这是因为所有的 $a_i$（其中 $1 \leqslant i < p$）都大于等于 $a_p + 1$，所以交换加超越的操作不会更糟糕。显然，如果我们使用 $a_q$（$q > p$），由于超越成本不会更差，使用 p 在交换方面成本更低。

现在，我们也可以在后缀中使用 $a_p$ 进行超越操作。也就是说，存在某个 $q \leqslant p$，使得我们用 $a_p$ 超越第 $1,2,\cdots,q$ 位自行车手。

这样就把问题简化为子问题 $a_{q + 1, n}$，因此我们可以使用动态规划！但为什么 $a_{q + 1, n}$ 这个子问题和数组的其余部分是相互独立的呢？

假设我们选取了某个 $a_i$（$i \leqslant q$）用于后缀 $a_{q + 1, n}$ 的交换操作，但我们可以重新安排交换顺序，先让第 $p$ 位到达第 $q$ 位，然后用第 $p$ 位进行后缀交换。这样不会增加额外的交换次数，甚至可能降低成本。

设 $dp_i$ 是后缀 $a_{i, n}$ 的最优解。然后，我们计算 $p$，即 $a_{i, n}$ 中最小值的位置，遍历分割索引 $j$，使得我们将第 $p$ 位移动到第 $j$ 位，并用于第 
$1,2,\cdots,j$ 位的交换操作，计算得到的值为 $dp_{j + 1} + a _p \times (j - i) + S$，其中 $S$ 表示总的交换次数（$S = 2 \times (j - p) + (p - i - 1)$）。

这样，我们就可以在 $O(n^2)$ 的时间复杂度内解决这个问题。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f, N = 5e3 + 10;
ll n, k, a [N], dp [N] [N], ans = 0;
int main () {
    int T; cin >> T;
    while (T --) {
        ll n; cin >> n;
        for (int i = 0; i <= n; i ++)
            for (int j = 0; j <= n; j ++)
                dp [i] [j] = INF;
        for (int i = 0; i < n; i ++)
            cin >> a [i];
        for (int i = 0; i < n; i ++)
            dp [n - 1] [i] = a [i] + n - i - 1;
        for (int i = n - 1; i > 0; i --)
            for (int j = 0; j < n; j ++) {
                if (dp [i] [j] >= INF) continue;
                dp [i - 1] [j] = min (dp [i - 1] [j], dp [i] [j] + a [j] + 1);
                if (i - 1 < j)
                    dp [i - 1] [i - 1] = min (dp [i] [j] + a [i-1], dp [i - 1] [i - 1]);
            }
        ans = INF;
        for (int i = 0; i < n; i ++)
            ans = min (ans, dp [0] [i]);
        cout << ans << '\n';
    }
    return 0;
}
```

---

