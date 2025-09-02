# [USACO23DEC] Haybale Distribution G

## 题目描述

Farmer John 正在农场上分发干草堆。

Farmer John 的农场上有 $N$（$1 \le N \le 2\cdot 10^5$）座谷仓，分别位于数轴上的整点 $x_1,\ldots,x_N$（$0 \le x_i \le 10^6$）。Farmer John 正计划将 $N$ 车干草堆运输到整点 $y$（$0 \le y \le 10^6$），然后为每一座谷仓运输一车干草堆。

不幸的是，Farmer John 的运输系统浪费了很多干草堆。具体来说，给出一些 $a_i,b_i$（$1 \le a_i,b_i \le 10^6$），每车干草堆每向左移动一单位距离，$a_i$ 堆干草堆会被浪费；每车干草堆每向右移动一单位距离，$b_i$ 堆干草堆会被浪费。形式化地，一车干草堆从整点 $y$ 运动到位于 $x$ 的谷仓，被浪费的干草堆堆数如下：

$$\begin{cases}a_i\cdot (y-x) & \text{if} \ y>x \\ b_i\cdot(x-y)&\text{if}\ x>y\end{cases}$$

给出 $Q$（$1 \le Q \le 2 \cdot 10^5$）组相互独立的询问，每组询问给出一组 $(a_i,b_i)$ 的值，帮助 Farmer John 计算当按照最佳方案选择 $y$，最少有多少堆干草堆被浪费。

## 说明/提示

### 样例解释 1

样例中第二个询问，最佳方案为选择 $y=2$，被浪费的干草堆数量为 $2(2-1)+2(2-2)+1(3-2)+1(4-2)+1(10-2)=1+0+1+2+8=13$。

### 测试点性质

- 测试点 $2$ 满足 $N,Q \le 10$。
- 测试点 $3$ 满足 $N,Q \le 500$。
- 测试点 $4-6$ 满足 $N,Q \le 5000$。
- 测试点 $7-16$ 没有额外限制。

## 样例 #1

### 输入

```
5
1 4 2 3 10
4
1 1
2 1
1 2
1 4```

### 输出

```
11
13
18
30```

# 题解

## 作者：RDFZchenyy (赞：6)

### 题目概述

给定一个长度为 $n$ 的序列 $\{x_n\}$，有 $Q$ 组询问，每组询问给定常数 $a,b$，请选择最优的 $d$，使得 $\sum\limits_{i=1}^{k} a(y-x_i)+ \sum\limits_{i=k+1}^{n} b(x_i-y)$ 最小，并求出最小值，其中 $k$ 满足 $x_k\le y<x_k+1$。

对于 $100\%$ 的数据，满足 $1\le n,Q\le 2\times 10^5$。

### 思路分析

题解区中已经给出了使用二分/三分的做法，这里给出一种偏数学的做法。

我们观察一组询问。

为了方便讨论，我们设 $p_i$ 为 $x_i$ 对答案的贡献。即当 $x_i\le d$ 时 $p_i=a(y-x_i)$，当 $d<x_i$ 时 $p_i=b(x_i-y)$。

我们考虑先设 $y=1$。接着，对于 $d_0$ 和 $d_0+1$，观察每一个 $p_i$ 的变化量，我们发现所有的满足 $x_i\le d$ 的 $p_i$ 会增加 $a$，所有的满足 $x_i\le d$ 的 $p_i$ 会增加 $a$，所有的满足 $d<x_i$ 的 $p_i$ 会减少 $b$。

这说明，如果 $d$ 从 $d_0$ 变化到 $d_0+1$，那么答案增加 $\Delta= k_0\times a-(n-k_0)\times b$。其中 $k_0$ 是 $d=d_0$ 满足 $x_i\le d$ 的 $i$ 的数量。随着 $d$ 的增加，$k_0$ 增加，$\Delta$ 也从负数单调递增至非负数。所以，答案随 $d$ 的增加而先减少后增加。

为了找到最小的答案，我们只需要找到第一个使 $\Delta\ge0$ 的 $k_1$，这个 $k_1$ 对应的结果即为答案。即我们就是要找到满足 $\Delta= k\times a-(n-k)\times b\ge0$ 的最小的 $k$ 对应的 $d$。

对这个式子进行恒等变形：$\Delta= k\times (a+b)\ge n\times b$。

故最小的满足条件的 $k$ 即 $k_1=\lceil \frac{n\times b}{a+b}\rceil$，同时我们根据 $k_1$ 就可以计算出答案。

请注意，对于每一组询问，需要将时间复杂度降到 $O(1)$，故您应当在读入后预处理**前缀和**。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005

int n,q,u;
long long x[MAXN],sum[MAXN];
long long a,b;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i];
	}	
	sort(x+1,x+n+1);
   
	for(int i=1;i<=n;i++){ // 预处理前缀和
		sum[i]=sum[i-1]+x[i];
	}
   
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>a>>b;
		u=(int)(ceil((long double)b*n/(a+b))); // 为了保证精度如此操作
		cout<<(x[u]*(u)-sum[u])*a+(sum[n]-sum[u]-x[u]*(n-u))*b<<endl;
		// 此处计算答案时带入前缀和
	}
	
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：5)

对于每个位置，求出左边谷仓到其的距离之和 $x$，右边谷仓到其的距离之和 $y$。对于每个 $a$，$b$，答案即为 $\min ax+by$。

距离之和的求法为拆式子，拆分成前缀和以及个数，可以直接 $O(n)$ 求出所有位置的距离。

考虑处理 $ax+by$，因为把 $a$，$b$ 是定值，把$b$ 提出来即为 $b(\frac{a}{b}x+y)$，是一个一次函数。

问题转化为若干个一次函数求一个点最小值，直接维护上凸壳找对应直线即可。

维护上凸壳，对斜率从大到小排序并去重，按与上一条直线相交位置建单调栈即可求出上凸壳。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#include<random>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e6+10;
const int M=1e6;
const int inf=1e18;
int n,m,k,Q,a[N],b[N],f[N],g[N],s1[N],s2[N];
int top,st[N];
double pos[N];
struct node{
	int x,y;
}e[N],E[N];
int cmp(node a,node b){
	if(a.x==b.x)
		return a.y<b.y;
	return a.x>b.x;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++){
		int x=read();
		a[x]++;
		b[x]+=x;
	}
	f[0]=g[0]=0;
	for(int i=0;i<=M;i++){
		if(i){
			f[i]=f[i-1]+a[i];
			g[i]=g[i-1]+b[i];
		}
		else{
			f[i]=a[i];
			g[i]=b[i];
		}
		s1[i]=i*f[i]-g[i];
	}
	f[M+1]=g[M+1]=0;
	for(int i=M;i>=0;i--){
		f[i]=f[i+1]+a[i];
		g[i]=g[i+1]+b[i];
		s2[i]=g[i]-i*f[i];
	}
	for(int i=0;i<=M;i++)
		E[++m]={s1[i],s2[i]};
	sort(E+1,E+m+1,cmp);
	E[0]={-1,inf};
	for(int i=1;i<=m;i++){
		if(E[i].x==E[k].x&&E[i].y>=E[k].y)
			continue;
		e[++k]=E[i];
	}
	for(int i=1;i<=k;i++){
		while(top){
			double x=(E[st[top]].y-E[i].y)*1.0/(E[i].x-E[st[top]].x);
			if(pos[top]>=x){
				top--;
				continue;
			}
			st[++top]=i;
			pos[top]=x;
			break;
		}
		if(!top){
			st[++top]=i;
			pos[top]=0;
		}
	}
	Q=read();
	while(Q--){
		int x=read(),y=read();
		double p=x*1.0/y;
		int l=1,r=top,ans=1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(pos[mid]<=p){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		int anss=inf;
		for(int i=max(ans-5,1ll);i<=min(ans+5,top);i++)
			anss=min(anss,x*e[st[i]].x+y*e[st[i]].y);
		cout<<anss<<'\n';
	}
	return 0;
}

```


---

## 作者：mRXxy0o0 (赞：3)

# 题意

带权货仓选址。

# 分析

原问题不太好做，手玩几组数据，发现不同位置的代价似乎满足某种单调性，函数图像大概是下凹的。

尝试证明一下。假设当前选择点在 $x$，左边有 $i$ 个谷仓，右边有 $n-i$ 个谷仓。考虑 $x$ 移到 $x+1$ 的增量。即 $a\times i-b\times (n-i)$，由于从左到右讨论，所以 $i$ 递增，$(n-i)$ 递减，所以该增量单调不降（有可能移一步 $i$ 不会增加）。因此，把增量小于 $0$ 的部分全部加到选最左边的代价即可。

实现上，可以规避浮点数且代码简单。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int n,m;
ll f[N],g[N],a[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+1+n);
	for(int i=2;i<=n;++i){
		f[i]=f[i-1]+(i-1)*(a[i]-a[i-1]);
	}
	for(int i=n-1;i;--i){
		g[i]=g[i+1]+(n-i)*(a[i+1]-a[i]);
	}
	scanf("%d",&m);
	while(m--){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		int l=1,r=n-1,res=1;
		while(l<=r){
			int mid=l+r>>1;
			if(x*mid-y*(n-mid)<=0) res=mid+1,l=mid+1;
			else r=mid-1;
		}
		printf("%lld\n",f[res]*x+g[res]*y);
	}
	return 0;
}
```


---

## 作者：Pollococido (赞：1)

之前的 AI 题解不行，所以我自己写了。
### 题目大意
Farmer John 在数轴上的 $N$ 座谷仓（$0 \le x_i \le 10^6$）间分发干草堆，每座谷仓需接收一车。  
干草车从整点 $y$（$0 \le y \le 10^6$）出发，向左移动每单位损耗 $a_i$ 堆，向右损耗 $b_i$ 堆。  
损耗计算：
$$
\begin{cases}
a_i\cdot (y-x), & y>x \\
b_i\cdot(x-y), & x>y
\end{cases}
$$
给出 $Q$ 组 $(a_i, b_i)$ 询问，求最优 $y$ 使损耗最小。

由 ChatGPT 精简。
### 大致解法
先搞到函数图，以下是 $a = 3, b = 5$ 的热力图像。
![](https://cdn.luogu.com.cn/upload/image_hosting/jbuz095o.png)，可以看出函数像一个 V 字，那我们就可以通过三分来找到最小值了。
### 具体步骤
1. 先对 $\{x_N\}$ 排序并计算前缀和。
2. 在 $[0, 10^6]$ 三分搜索最好的 $y$。
3. 二分确定 $y$ 在 $\{x_N\}$ 的位置，算损耗。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, q;
int x[200010];
ll sum[200010];
int a, b;

ll calc(int y) {
    int i = upper_bound(x + 1, x + n + 1, y) - x - 1;
    ll left = 1LL * a * (1LL * y * i - sum[i]);
    ll right = 1LL * b * ((sum[n] - sum[i]) - 1LL * y * (n - i));
    return left + right;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + x[i];
    cin >> q;
    while (q--) {
        cin >> a >> b;
        int l = 0, r = 1000000;
        while (r - l > 2) {
            int i = l + (r - l) / 3;
            int j = r - (r - l) / 3;
            if (calc(i) < calc(j)) r = j;
            else l = i;
        }
        ll ans = 0x3f3f3f3f3f3f3f3f;//注意 long long 最大是 8 个 3f
        for (int i = l; i <= r; i++) {
            ans = min(ans, calc(i));
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：cff_0102 (赞：1)

本题为加权后的货舱选址问题。总花费为 $a_i$ 倍的左边所有点到选择的地点的路程之和加上 $b_i$ 倍的右边的所有点到选择的地点的路程之和。不难发现，如果我们将所有询问按 $\frac{b}{a}$ 排序，那么最优决策是单调从左向右的。
 
证明：首先可以发现如果两个询问的 $a$ 和 $b$ 的比值相同，那么这两个询问的最优决策也必定是相同的点。设 $\frac{b_i}{a_i}<\frac{b_j}{a_j}$，那么就可以将 $a_i,a_j$ 都变成 $1$，$b_i,b_j$ 改成原来的 $\frac{b_i}{a_i},\frac{b_j}{a_j}$，则 $b_i<b_j$，不影响最终的决策点。
 
把原题改成从谷仓运一车干草堆到选择的点，考虑一个左决策点 $l$ 和一个右决策点 $r$，先把编号为 $1\sim l$ 的谷仓的干草运到 $l$ 的位置即 $x_{l}$，把编号为 $r\sim n$ 的谷仓的干草运到 $x_{r}$。设 $x_l$ 到 $x_r$ 的距离是 $s_{mid}$，$x_{1}$ 到 $x_{l}$ 的谷仓个数是 $p$，$x_{r}$ 到 $x_{n}$ 的谷仓个数是 $q$。当 $r=l+1$，且最优决策点在这两个之间时，则需要比较把 $l$ 的干草全部运到 $r$ 和把 $r$ 的干草全部运到 $l$ 哪个更划算。如果把 $l$ 的干草全部运到 $r$，花费为 $a\times l\times x_{mid}=p\times x_{mid}$；如果把 $r$ 的干草全部运到 $l$，花费为 $b\times (n-r+1))\times x_{mid}=b\times q\times x_{mid}$。要选择更划算的那个方案，即需要比较 $p$ 和 $b\times q$ 的大小，后者更小则把 $r$ 向左移（这样会增加 $q$ 的大小），否则就把 $l$ 向右移（会增加 $p$ 的大小）。
 
注意到最终的最优决策点的 $p$ 和 $b\times q$ 是相当接近的，且是所有 $(p,q)$ 中 $\frac{b\times q}{p}$ 中最接近 $1$ 的。假设我们求解完了排序后第 $i$ 组 $(1,b_i)$ 的答案的最优决策是 $(p_i,q_i)$，我们知道下一组的 $b_j$ 是大于 $b_i$ 的，也就是，如果保持原来的决策 $(p_i,q_i)$ 不变，此时的 $\frac{b\times q}{p}$ 的分子是增加了的。$p$ 和 $q$ 的和是固定的，要让新的 $\frac{b\times q}{p}$ 更接近 $1$，肯定不能增加 $q$ 减少 $p$，如果可以的话，需要增加 $p$，减少 $q$。因此，新的最优决策不可能在原来的左边。
 
所以按 $\frac{b_i}{a_i}$ 排序后的询问的最优决策是“单调不左”的。把询问离线下来处理即可。
 
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int N=2e5+5;
struct query{
    int a,b,n,ans;
}que[N];
int pos[N];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>pos[i];
    }
    sort(pos+1,pos+1+n);
    int q;cin>>q;
    for(int i=1;i<=q;i++){
        cin>>que[i].a>>que[i].b;
        que[i].n=i;
    }
    sort(que+1,que+1+q,[](query x,query y){
        return x.b*y.a<y.b*x.a;
    });
    int p=1,ls=0,rs=0;
    for(int i=1;i<=n;i++){
        rs+=(pos[i]-pos[1]);
    }
    for(int i=1;i<=q;i++){
        while(p<n&&ls*que[i].a+rs*que[i].b>=(ls+p*(pos[p+1]-pos[p]))*que[i].a+(rs-(n-p)*(pos[p+1]-pos[p]))*que[i].b){
            ls+=p*(pos[p+1]-pos[p]);
            rs-=(n-p)*(pos[p+1]-pos[p]);
            p++;
        }
        que[i].ans=ls*que[i].a+rs*que[i].b;
    }
    sort(que+1,que+1+q,[](query x,query y){
        return x.n<y.n;
    });
    for(int i=1;i<=q;i++){
        cout<<que[i].ans<<endl;
    }
    return 0;
}
```

---

## 作者：Zi_Gao (赞：1)

> 题意：
>
> 给定一条数轴上面有 $n$ 个点，分别在 $x_i$ 的位置。定义数轴上两个点 $x,y$（这里是坐标，不是下标）之间运输成本 $W_{x,y}$ 为。
>
$$
W_{x,y}=
\begin{cases}
a\cdot\left(y-x\right), & x\leq y,\\
b\cdot\left(x-y\right), & x\gt y
\end{cases}
$$
>
> 其中 $a,b$ 为给定常数。现在有 $q$ 次询问每次询问给定一组 $a,b$ 询问互相独立，你要求一个点 $y$（也是坐标，不一定是给定的点上）最小化 $\sum_{i=1}^{n} W_{y,x_i}$。
>
> $n\leq 2\cdot 10^5,1\leq a,b \leq 10^6$

固定一组 $a,b$ 时，定义函数 $f\left(y\right)=\sum_{i=1}^{n} W_{y,x_i}$ 发现这个函数具有单峰性，具体来说两边大，中间小，所以可以三分解决。

关于三分的正确性，若三分有平台，即函数连续相同段，有些时候不能三分解决，但是若平台只出现在峰的顶端可以三分解决，其他地方若也有平台则无法三分解决。这道题的函数的平台只会在峰顶出现。

不太会三分，写的二分（别喷

```cpp
#include<bits/stdc++.h>
#define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

long long a,b,presum[1000100],cnt[1000100];
long long check(int pos){
    return (cnt[pos]*pos-presum[pos])*a+(presum[1000100-1]-presum[pos]-(cnt[1000100-1]-cnt[pos])*pos)*b;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    #endif

    register int i,l,r,mid,x,q;
    register long long res;
    int n=read();

    for(i=1;i<=n;++i){
        x=read()+20;
        presum[x]+=x,cnt[x]+=1;
    }

    for(i=1;i<1000100;++i) presum[i]+=presum[i-1],cnt[i]+=cnt[i-1];

    q=read();
    while(q--){
        a=read();b=read();
        l=15,r=1000030;
        while(l+2<r){
            mid=(l+r)>>1;
            if(check(mid)>check(mid+1))
                l=mid+1;
            else r=mid;
        }
        for(res=0x3f3f3f3f3f3f3f3fll,i=l-5;i<=l+5;++i) res=std::min(res,check(i));
        print(res),putchar('\n');
    }

    #ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    #endif
    return 0;
}
```


---

## 作者：liuhl_weifang (赞：1)

好题耶。

定义 $f(y)$ 表示将所有干草运到点 $y$ 的价值。通过观察，我们发现 $f(y)$ 这个函数是一个**单谷函数**，故考虑使用 **三分** 解决。

怎样 $\Theta(1)$ 求出 $f(y)$ 呢？

$$\begin{cases}a_i\cdot (y-x) & \text{if} \ y>x \\ b_i\cdot(x-y)&\text{if}\ x>y\end{cases}$$

我们发现可以单独计算 $y>x$ 和 $y<x$ 两部分的价值。

设 $g_i$ 表示有多少个编号 $\leq i$ 的谷仓。

设 $k_i$ 表示所有编号 $\leq i$ 的谷仓的编号之和。

$y>x$ 那一部分的价值拆开后就是 $a_i \cdot y-a_i \cdot x$，简单推一下式子可以得出 $y>x$ 这一部分的价值之和为 $g_y \cdot a_i \cdot y - k_y \cdot a_i$。

$y<x$ 那一部分的价值拆开后就是 $b_i \cdot x-b_i \cdot y$，简单推一下式子可以得出 $y<x$ 这一部分的价值之和为 $b_i \cdot (k_{inf}-k_y)-(g_{inf}-g_y) \cdot y \cdot b_i$。

所以这道题就愉快的解决啦！

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
int g[1000010];
int k[1000010];
const int inf = 1000000;

int calc(int a,int b,int y)
{
	int w1 = g[y]*y*a-a*k[y];
	int w2 = b*(k[inf]-k[y])-(g[inf]-g[y])*y*b;
	return w1+w2;
}

signed main()
{
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		int qwq;
		cin >> qwq;
		g[qwq]++;
	}
	for (int i=1;i<=inf;i++)
	{
		k[i] = k[i-1]+g[i]*i;
		g[i] = g[i-1]+g[i];
	}
	cin >> q;
	for (int i=1;i<=q;i++)
	{
		int a,b;
		cin >> a >> b;
		int l=1,r=inf;
		while(l<r)
		{
			int lmid = (l+r)/2;
			int rmid = lmid+1;
			int _x = calc(a,b,lmid);
			int _y = calc(a,b,rmid);
			if(_x>=_y) l = lmid+1;
			else r = rmid-1;
		}
		cout << min(calc(a,b,l),calc(a,b,l-1)) << "\n";
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

我们想一下如果让 $y=y+1$ 对答案的影响。我们令 $dl_i$ 表示所有在 $i$ 左边的仓库到 $i$ 的距离和，$dr_i$ 表示所有在 $i$ 右边的仓库到 $i$ 的距离和。

显然，影响为 $(dl_{i+1}-dl_i)\times a-(dr_i-dr_{i+1})\times b$。很显然，因为 $dl$ 单调递增，$dr$ 单调递减，$a,b$ 恒正，所以影响是单调递增的。

我们同时也能够看出来，$y$ 位置的值是单谷的。因此，当 $(dl_{i+1}-dl_i)\times a-(dr_i-dr_{i+1})\times b$ 接近零的时候可以取到谷。显然这样有点小问题，你只能取到和答案误差不超过 $1$ 的位置。显然，你再枚举一下这个位置左右取最优就行了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, x[200005], m, a, b, dl[1000005], dr[1000005], l, r, mid, anv;
inline bool get(int p) {
	int vad = (dl[p + 1] - dl[p]) * a;
	int vdc = (dr[p] - dr[p + 1]) * b;
	return vad - vdc >= 0;
}
inline int ans(int p) {
	return dl[p] * a + dr[p] * b;
}
signed main() {
	ios::sync_with_stdio(0); cin >> n;
	for (int i = 1; i <= n; ++i) cin >> x[i];
	sort(x + 1, x + n + 1);
	for (int i = 0, cl = 0; i <= 1e6; ++i) {
		if (i)dl[i] = dl[i - 1] + cl;
		while (x[cl + 1] == i) cl++;
	}
	for (int i = 1e6, cr = 0; i >= 0; --i) {
		dr[i] = dr[i + 1] + cr;
		while (x[n - cr] == i) cr++;
	}
	//a->b(a<b)，增加了 (dl[b]-dl[a])*a，减少了(dr[a]-dr[b])*b
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> a >> b; anv = 2e18;
		l = 0, r = 1e6 - 1;
		while (l != r)
			if (get(mid = l + r >> 1))r = mid;
			else l = mid + 1;
		for (int i = -40; i <= 40; ++i)
			if (l + i >= 0 && l + i <= 1e6)
				anv = min(anv, ans(i + l));
		cout << anv << endl;
	}
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意：

给定一些点数轴上的整点 $x_i$ 和 $a,b$，调整 $y$ 并最小化下式：

$$\sum_{i=1}^n \begin{cases}a\cdot (y-x_i) & \text{if} \ y>x_i \\ b\cdot(x_i-y)&\text{if}\ x_i>y\end{cases}$$

### 思路：

不难观察到原式单谷，关键是怎么证。

考虑最优解的点，设其左侧有 $p$ 个谷仓，右侧有 $q$ 个谷仓，自身位置有 $k$ 个谷仓。右移一个单位长度的贡献是 $(p+k)\cdot a-q\cdot b$。左移一个单位长度的贡献是 $(q+k)\cdot b-p\cdot a$。

显然，这两个值必然是正的。

考虑不断向左或向右移动，对于上述两个式子，每次经过谷仓后，第一项的系数会不断增加，第二项的系数会不断下降。即：贡献只会单调上升。

初始化每个位置左右的谷仓距离之和，对于每个点我们可以 $O(1)$ 计算该位置的分数。二分或三分找最低点即可。

复杂度 $O(m+q\log m)$。

### 程序如下：

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=2e5+5,M=1e6+5;
long long n,q,a,b,x[N],pre[M],pos[M];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&x[i]),x[i]++;
	sort(x+1,x+n+1);
	int fr=0,cur=1;
	for(int i=1;i<=x[n];i++){
		pre[i]=pre[i-1]+fr;
		while(x[cur]==i)cur++,fr++;
	}
	fr=0,cur=n;
	for(int i=x[n];i>=1;i--){
		pos[i]=pos[i+1]+fr;
		while(x[cur]==i)cur--,fr++;
	}
	pre[0]=pre[x[n]+1]=1e9;
	pos[0]=pos[x[n]+1]=1e9;
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&a,&b);
		long long l=1,r=x[n],ans;
		while(l<r){
			int mid=(l+r)>>1;
			long long curans=pre[mid]*a+pos[mid]*b;
			long long nxtans=pre[mid+1]*a+pos[mid+1]*b;
			if(nxtans<curans)l=mid+1;
			else r=mid;
		}
		printf("%lld\n",pre[l]*a+pos[l]*b);
	}
	return 0;
}
```

### THE END

USACO 2024 Dec RP++.

---

## 作者：CodingOIer (赞：0)

## P9982 [USACO23DEC] Haybale Distribution G 题解

### 思路分析

首先分析如果我们得到了最优的位置下标为 $w$，我们如何计算出答案。

我们记 $f(i, j)$ 为排序后 $i$ 到 $j$ 这段区间内，所有位置的下标和。

左边的浪费数用乘法分配律拆开以后为 $a \times left$，其中 $left$ 为左边的距离之和，可以用 $left \gets p_w \times w - f(1, w)$ 求得。

右边的同理，易得 $right \gets f(w + 1, n) - p_w \times (n - w)$。

其中的 $w$ 可以用二分求得。

接着，我们可以发现答案是一个 $x <= 0$ 的二次函数。（我也没有什么好的证明，你可以选择用暴力把每一个点位置算一遍，发现中间的最小）

我们就可以开始三分了。

但我不会三分啊？

由于我们需要找出最低点，我们可以用奇奇怪怪的二分来求。

我们先分出一个 $mid$，然后计算 $mid - 1, mid, mid + 1$ 的答案并记为 $r1, r2, r3$。

如果 $r1 \ge r2 \le r3$，退出。

如果 $r1 \le r2 \le r1$，说明最低点在 $mid$ 的左边。

如果 $r1 \ge r2 \ge r3$，说明最低点在 $mid$ 的右边。

但如此裂奇的做法，肯定也要有裂奇的统计答案。

我们在计算 $r1, r2, r3$ 时，分别用其对 $res$ 更新即可。

所以这个裂奇的做法的裂奇的复杂度为 $O(Q \times \log_n \times 3 \times \log_n) \approx 2 \times 10^8$。

### 代码实现
```cpp
#include <algorithm>
#include <cstdio>
#include <tuple>
constexpr int MaxN = 2e5 + 5;
int n, m;
long long res;
long long a, b;
long long min, max;
long long p[MaxN];
long long sum[MaxN];
inline long long query(int s, int t)
{
    return sum[t] - sum[s - 1];
}
inline long long find(long long x)
{
    long long l, r;
    l = 1;
    r = n;
    long long res = 0;
    for (; l <= r;)
    {
        long long mid = (l + r) / 2;
        if (p[mid] <= x)
        {
            res = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return res;
}
inline long long calcOnce(long long x)
{
    if (x < min || x > max)
    {
        return 0x3f3f3f3f3f3f3f3f;
    }
    long long w = find(x);
    long long left = w * x - query(1, w);
    long long right = query(w + 1, n) - (n - w) * x;
    left *= a;
    right *= b;
    return left + right;
}
inline std::tuple<long long, long long, long long> calc(long long x)
{
    long long r1, r2, r3;
    r1 = calcOnce(x - 1);
    r2 = calcOnce(x);
    r3 = calcOnce(x + 1);
    res = std::min(res, r1);
    res = std::min(res, r2);
    res = std::min(res, r3);
    return {r1, r2, r3};
}
inline int read()
{
    int f = 1, x = 0;
    char c = 0;
    for (;;)
    {
        c = getchar();
        if (c == '-')
        {
            f = -1;
        }
        else if ('0' <= c && c <= '9')
        {
            x = c - '0';
            break;
        }
    }
    for (;;)
    {
        c = getchar();
        if ('0' <= c && c <= '9')
        {
            x = x * 10 + c - '0';
        }
        else
        {
            break;
        }
    }
    return f * x;
}
int main()
{
    n = read();
    min = 0x3f3f3f3f3f3f3f3f;
    max = -0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        p[i] = read();
        sum[i] = sum[i - 1] + p[i];
        min = std::min(min, p[i]);
        max = std::max(max, p[i]);
    }
    std::sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + p[i];
    }
    m = read();
    for (int i = 1; i <= m; i++)
    {
        a = read();
        b = read();
        long long l, r;
        l = min;
        r = max;
        res = 0x3f3f3f3f3f3f3f3f;
        for (; l <= r;)
        {
            long long mid = (l + r) / 2;
            long long r1, r2, r3;
            std::tie(r1, r2, r3) = calc(mid);
            if (r1 >= r2 && r2 <= r3)
            {
                break;
            }
            else if (r1 <= r2 && r2 <= r3)
            {
                r = mid - 2;
            }
            else if (r1 >= r2 && r2 >= r3)
            {
                l = mid + 2;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
```

---

## 作者：robertuu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9982)

相对于金组 T3 的位置，难度已经很低了。

首先，我们要弄清楚怎么样在很快的时间内求出选择一个 $y$ 的运输代价，观察式子可以发现，需要分成左侧和右侧两类（自己的位置没有代价，放在哪边都无所谓），而且，答案需要用到 $|x-y|$，因此可以使用前缀和数组 $s$，将代价从 $\sum |x_i-y|$ 转化到 $(l \times y - s_l) + (s_r - r \times y)$，$l$ 和 $r$ 可以通过二分 $y$ 在 $x$ 数组中的位置得到。

因此我们就得到了求代价的函数：
```cpp
long long f(int p,int x,int y)
{
	int t = lower_bound(a+1,a+1+n,p)-a;
	return 1ll*(1ll*(t-1)*p-qzh[t-1])*x + 1ll*(qzh[n]-qzh[t-1]-1ll*(n-t+1)*p)*y;
}
```

（注意，代码中的 $t$ 不是 $l$，由于是利用的 `lower_bound` 函数，$t = l + 1$。）

这个函数的时间复杂度是 $O(\log n)$（当然，是可以优化到 $O(1)$ 的）。

有了这个函数后，再观察题目涉及到的公式，可以看出是一个关于 $y$ 的下凸函数，因此可以直接使用三分法解决问题。

整个算法的复杂度是 $O(Q\log^2n)$，在这道题的限制下已经可以通过（毕竟，$\log_2200000 < 20$）。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001];
long long qzh[200001];
long long f(int p,int x,int y)
{
	int t = lower_bound(a+1,a+1+n,p)-a;
	return 1ll*(1ll*(t-1)*p-qzh[t-1])*x + 1ll*(qzh[n]-qzh[t-1]-1ll*(n-t+1)*p)*y;
}
int main()
{
	int q,x,y;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for(int i = 1;i <= n;i++) qzh[i] = qzh[i-1] + a[i];
	scanf("%d",&q);
	for(int i = 1;i <= q;i++)
	{
		scanf("%d%d",&x,&y);
		int l = 0,r = 1000000,m1,m2;
		while(r-l > 3)
		{
			//cout << l << " " << r << endl;
			m1 = l+(r-l)/3;
			m2 = l+2*(r-l)/3;
			if(f(m1,x,y) < f(m2,x,y)) r = m2;
			else l = m1;
		}
		long long ans = 9e18;
		for(int j = l;j <= r;j++)
			ans = min(ans,f(j,x,y));
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

关于这是金组 T3 这件事

题意：有一些整点 $x_1,x_2,\dots,x_n$ 和常数 $a,b$（均大于 $0$），要选出一个整点 $y$ 使得 $\sum\limits_{i=1}^n[x_i>y]b(x-y)+[x_i<y]a(y-x)$ 最小。多次查询不同 $a,b$。

这个看起来类似于小学奥数，但是注意到这个关于 $y$ 的函数是单谷的，因此直接三分即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll A,B;
int a[200005];
ll q[200005],h[200005];// 前缀和、后缀和
ll chk(ll x){
	int p=upper_bound(a+1,a+n+1,x)-a-1;// 找出分界点位置
	return A*(p*x-q[p])+B*(h[p+1]-(n-p)*x);// 计算值
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)q[i]=q[i-1]+a[i];
	for(int i=n;i;i--)h[i]=h[i+1]+a[i];
	int t;cin>>t;while(t--){
		cin>>A>>B;
		int l=0,r=1000000;
		while(l<r)chk(l+(r-l)/3)>chk(r-(r-l)/3)?l+=(r-l)/3+1:r-=(r-l)/3+1;// 直接三分
		cout<<min(chk(l),chk(r))<<"\n";
	}
	return 0;
}
```

---

## 作者：yuanruiqi (赞：0)

$f_x$ 表示将所有干草集中到 $x$ 的花费，对于任意的 $a,b$，$f$ 都是单谷的。

$f$ 显然有最小值，假设在 $x$ 点取到最小值 $f_x$，设位置不在 $x$ 之前的点有 $k$ 个，则 $kb-(n-k)a=f_{x-1}-f_x\ge 0$，即 $k(a+b)-na\ge 0$，而 $k$ 随着 $x$ 左移不会减小，所以差也不会减小，右半边同理。故得证。

简单三分即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int maxn = 200000 + 10;
constexpr int maxm = 1000000 + 10;
i64 a[maxm], b[maxm];
int n;
i64 p, q;
i64 check(int x)
{
    return q * ((a[maxm - 1] - a[x]) - x * (n - b[x])) + p * (x * b[x - 1] - a[x - 1]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=1;i<=n;++i)
    {
        int x;
        cin >> x;
        ++x;
        a[x] += x;
        ++b[x];
    }
    for (int i=1;i<maxm;++i) a[i] += a[i - 1], b[i] += b[i - 1];
    int m;
    cin >> m;
    while (m--)
    {
        cin >> p >> q;
        int L = 1, R = maxm - 1;
        while (R - L > 1)
        {
            int M0 = L + (R - L + 1) / 3, M1 = R - (R - L + 1) / 3;
            if (check(M0) <= check(M1)) R = M1;
            else L = M0;
        }
        cout << min(check(L), check(R)) << endl;
    }
    return 0;
}
```

---

## 作者：waauto (赞：0)

机房有人用的凸包，隔壁有人用的三分，看了一圈题解也没有人线性，所以写一个线性的题解。

首先你预处理一个前缀和，一个后缀和，然后桶排或者基排一下位置数组。

我们考虑一个决策点，首先决策点显然在坐标上，否则一定可以左右移动更优或者不变。

假设左边有 $k$ 个位置，右边有 $n-k-1$ 个位置，这个位置有一个点。

那么满足:

$$
ka-(n-k)b\le 0
$$

$$
(n-k-1)b-(k+1)a \le 0
$$

稍微整理。

$$
\frac{nb}{a+b} -1\le k\le \frac{nb}{a+b}
$$

然后你发现这样的点也就两个左右，你左右枚举两个就好了。

最后答案是 $a\times(x_k\times k -presum_k)+b\times (lstsum_k-x_k\times k)$。

时间复杂度 $O(n+q)$ 瓶颈在于看你怎么排序。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int qz[N],q[N],hz[N],h[N];
int a[N];int n;
inline int ck(int x,int a,int b){
	return a*qz[x]+b*hz[x];
}
inline int solve(int A,int B){
	int mid=B*n-B;
	mid/=(A+B);
	int now=a[mid];
	int res=1e18;
	for(int s=-2;s<=2;s++){
		if(mid+s>0 and mid+s<n)res=min(res,ck(a[mid+s],A,B));
	}
	return res;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],q[a[i]]++,h[a[i]]++;
	sort(a+1,a+1+n);
	for(int i=1;i<=1e6;i++)q[i]+=q[i-1],qz[i]=q[i-1]+qz[i-1];
	for(int i=1e6;i>=0;i--)h[i]+=h[i+1],hz[i]=hz[i+1]+h[i+1];
	int m;
	cin>>m;
	while(m--){
		int a,b;
		cin>>a>>b;
		cout<<solve(a,b)<<'\n';
	}
	return 0;
}

```

---

