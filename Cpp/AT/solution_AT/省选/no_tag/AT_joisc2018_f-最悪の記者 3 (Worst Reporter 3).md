# 最悪の記者 3 (Worst Reporter 3)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2018/tasks/joisc2018_f



# 题解

## 作者：Rosaya (赞：1)

### 题意

有 $n+1$ 个人排在坐标轴上，第 $0$ 时刻第 $i(0 \le i \le n)$ 个人的坐标为 $-i$。

对于第 $i(0< i \le n)$ 个人，有一个移动参数 $d_i$。

对于第 $i(i>0)$ 时刻，所有人会以编号顺序移动，记第 $i$ 个人移动前的坐标为 $p_i$，移动后的坐标为 $x_i$。

有以下移动规则：

- 对于第 $0$ 个人，$x_i=p_i+1$。

- 对于第 $i(i>0)$ 个人，若 $x_{i-1}-p_i>d_i$，则 $x_i=x_{i-1}-1$，否则 $x_i=p_i$。

有 $q$ 次询问，每次询问在 $t$ 时刻移动结束之后坐标在 $[l,r]$ 之内的人的个数。

$1 \le n,q \le 5 \times 10^5,1 \le d_i,t,l,r \le 10^9,l \le r$。

### 思路

模拟一些情况，发现对于第 $i$ 个人，一定是每 $f_i$ 个时刻之后移动 $f_i$ 步。

可以归纳证明，假设我们正在考虑第 $i$ 个人，已经求出 $f_{i-1}$，分类讨论。

若 $f_{i-1} \ge d_i$，则由于 $i,i-1$ 之间本身有 $1$ 的距离，所以在 $i-1$ 往前跳一次之后就会超出距离限制，此时 $i$ 应该跳到 $i-1$ 身后，从此保持同步，$f_i=f_{i-1}$。

若 $f_{i-1} < d_i$，则在 $i-1$ 往前跳 $\left\lceil \dfrac{d_i}{f_{i-1}} \right\rceil $ 次之后才会超出距离限制，此时 $i$ 应该跳到 $i-1$ 身后，从此跳跃周期变长，$f_i=\left\lceil \dfrac{d_i}{f_{i-1}} \right\rceil f_{i-1}$。

特别的，$f_0=1$。

不难发现 $f_i$ 要么与 $f_{i-1}$ 相同，要么是后者的倍数。$f_i=f_{i-1}$ 时 $i,i-1$ 行动完全同步，而翻倍最多 $\log 10^9$ 次就会永远 $>\max{d}$，于是我们可以直接维护出连续段，计算答案时暴力访问即可。

总复杂度 $O((n+q)\log 10^9)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,q,ans;
ll d[500005],lt[500005],pos;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;

    d[0]=1;
    for(int i=1;i<=n;i++)
    {
        cin>>d[i];
        if(d[i]<=d[i-1])
            d[i]=d[i-1],lt[i]=lt[i-1];
        else
            d[i]=((d[i]-1)/d[i-1]+1)*d[i-1],lt[i]=i;
    }

    while(q--)
    {
        pos=n,ans=0;

        ll t,l,r;
        cin>>t>>l>>r;

        while(pos>=0)
        {
            ll x=t/d[pos]*d[pos];
            ans+=max(0LL,min(r-x,-lt[pos])-max(l-x,-pos)+1);
            pos=lt[pos]-1;
        }

        cout<<ans<<'\n';
    }

    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2018F 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2018_f)

**题目大意**

> 数轴上有 $n+1$ 个人，编号 $0\sim n$，第 $i$ 个人初始在 $-i$ 上。
>
> 每轮第 $0$ 个人向右移动 $1$，然后对于 $i=1\sim n$，如果其与 $i-1$ 距离 $<d_i$，那么就移动到第 $i-1$ 左边的位置。
>
> $q$ 次询问 $t$ 秒后 $[l,r]$ 内有几个人。
>
> 数据范围：$n,q\le 5\times 10^5$。

**思路分析**

根据数学归纳法可以证明每个人的运动都是具有周期性的，即每隔 $k_i$ 轮动 $k_i$ 步。

然后二分 $t$ 秒后位置 $\le r$ 和 $\le l-1$ 的有几个人即可求出答案。

事实上，注意到 $k_{i-1}\mid k_i$，因此本质不同的 $k_i$ 只有 $\mathcal O(\log V)$ 级别，暴力找对应端点也可以通过。

时间复杂度 $\mathcal O(n+q\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5e5+1;
int d[MAXN],k[MAXN];
signed main() {
	int n,q;
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;++i) scanf("%lld",&d[i]);
	d[0]=k[0]=1;
	for(int i=1;i<=n;++i) k[i]=(d[i]+k[i-1]-1)/k[i-1]*k[i-1];
	auto query=[&](int t,int x) {
		int l=0,r=n,res=-1;
		while(l<=r) {
			int mid=(l+r)>>1;
			if((t/k[mid])*k[mid]-mid>=x) res=mid,l=mid+1;
			else r=mid-1;
		}
		return res+1;
	};
	while(q--) {
		int t,l,r;
		scanf("%lld%lld%lld",&t,&l,&r);
		printf("%lld\n",query(t,l)-query(t,r+1));
	}
	return 0;
}
```



---

## 作者：Graphcity (赞：0)

首先考察选手 1 的移动规律：每 $d_1$ 秒往前走 $d_1$ 步。

然后考察选手 2 的移动规律：当选手 1 的移动步数大于等于 $d_2$ 时，它会立刻走到选手 1 前面一位。也就是说，他每 $kd_1$ 秒往前走 $kd_1$ 步，其中 $k\ge 1$。

以此类推，每位选手都是每 $t$ 秒往前走 $t$ 步。

这样还是不太好处理。但我们发现，下一位选手的跨步距离一定是上一位选手的 $k$ 倍（$k$ 为正整数）。因为 $d_i\le 10^9$，那么 $k$ 至多翻倍 $\log d$ 次，至多只有 $\log d$ 种本质不同的跨步距离。对于每种跨步距离，编号都是一段连续区间。

我们对于每一种跨步距离分别处理每个询问。每个询问可以求出这个距离下所有人前进的步数，进而推算出合法的原始区间。时间复杂度 $O(n\log d)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,d[Maxn+5],fc[Maxn+5][3],ans[Maxn+5];
map<int,vector<int>> v;

inline void Solve(int K)
{
    int l=v[K].front(),r=v[K].back(); l=-l,r=-r,swap(l,r);
    For(i,1,m)
    {
        int t=fc[i][0],ql=fc[i][1],qr=fc[i][2];
        t=(t/K)*K,ql-=t,qr-=t;
        ans[i]+=max(0ll,min(r,qr)-max(l,ql)+1);
    }
}

signed main()
{
    n=read(),m=read();
    For(i,1,n) d[i]=read();
    For(i,1,m) For(j,0,2) fc[i][j]=read();
    v[1].push_back(0);
    for(int i=1,j=1;i<=n;++i) {int t=(d[i]+j-1)/j; j=t*j,v[j].push_back(i);}
    for(auto i:v) Solve(i.first);
    For(i,1,m) printf("%lld\n",ans[i]);
    return 0;
}
```



---

