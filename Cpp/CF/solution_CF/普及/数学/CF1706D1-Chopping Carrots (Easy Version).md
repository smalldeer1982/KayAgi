# Chopping Carrots (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

## 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

## 样例 #1

### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3```

### 输出

```
2
0
13
1
4
7
0```

# 题解

## 作者：蒟蒻炒扇贝 (赞：7)

发现值域较小，考虑枚举最小值，由于 $a$ 是单调的，不难发现最小值处于 $[\lfloor \frac{a_1}{k} \rfloor,a_1]$ 这一区间内。

对于我们每次枚举到的最小值 $minn$，需要求解的子问题如下：给定一个序列 $a$，需要求一个序列 $p$，使得对于任意的 $i$，都有 $p_i∈[1,k]$，求 ${\max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - minn}$ 的最小值。发现 $\lfloor \frac{a_i}{p_i} \rfloor$ 是满足单调性的，考虑二分。

我们每次都要保证 $\lfloor \frac{a_i}{p_i} \rfloor$ 尽可能接近 $minn$，又要其尽可能小，根据上述条件二分每一个 $p_i$ 的值即可。

时间复杂度 $\mathop{O(Vn\log k)}$，其中 $V$ 是序列 $a$ 元素的最大值。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,a[3005];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		int ans=2e9;
		for(int mn=a[1]/k;mn<=a[1];mn++)
		{
			int maxn=0,minn=2e9;
			for(int i=1;i<=n;i++)
			{
				int l=1,r=k,p=1;
				while(l<=r)
				{
					int mid=(l+r)/2;
					if(a[i]/mid<mn)r=mid-1;
					else l=mid+1,p=mid;
				}
				maxn=max(maxn,a[i]/p);
				minn=min(minn,a[i]/p);//记录最小值，看看目前我们所枚举的最小值能否被取到 
			}
			if(minn==mn)ans=min(ans,maxn-mn);
		}
		cout<<ans<<endl;
	}
}
```


---

## 作者：tzyt (赞：2)

题目链接[（CF](https://codeforces.com/problemset/problem/1706/D1)，[洛谷）](https://www.luogu.com.cn/problem/CF1706D1) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1706/)中观看。

## 思路

我们尝试设最小的 $\lfloor \frac{a_i}{p_i} \rfloor$ 为 $mn$。那么 $mn \in [0, a_1]$，因为 $p_i$ 最小为 $1$，那 $\lfloor \frac{a_1}{1}\rfloor$ 就是 $a_1$ 了。

在这个的基础上，我们再贪心的尝试让每个 $\lfloor \frac{a_i}{p_i} \rfloor$ 都尽可能的接近 $mn$，这样就可以尽可能的让最大的 $\lfloor \frac{a_i}{p_i} \rfloor$ 更小。

这样我们就可以算出 $p_i$，因为 $\lfloor \frac{a_i}{p_i} \rfloor \ge mn$，所以 $p_i = \lfloor \frac{a_i}{mn} \rfloor$。当然，$p_i$ 不能大于 $k$，并且如果 $mn = 0$，我们就让 $p_i = k$。

然后我们去枚举每个可能的 $mn$，并且计算该情况下的最大的 $\lfloor \frac{a_i}{p_i} \rfloor$，就能得到答案了。思路好像挺简洁，但是真的挺难想的，

## 代码

```cpp
// author: tzyt
#include <bits/stdc++.h>
using namespace std;
#define IINF 0x3f3f3f3f
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int a[n + 1];
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int ans = IINF;
        int mxv = 0;
        for (int mnv = 0; mnv <= a[1]; mnv++) {
            // 枚举 mn
            for (int i = 1; i <= n; i++) {
                int p = min(k, (mnv ? (a[i] / mnv) : k));
                // mnv ? (a[i] / mnv) : k 是因为 mnv 为 0 的情况
                mxv = max(mxv, a[i] / p);
            }
            ans = min(ans, mxv - mnv);
        }
        cout << ans << '\n';
    }
}
```

---

## 作者：Erica_N_Contina (赞：1)

## 思路

### EV

$1 \le n, k \le 3000$，$1 \le a_1 \le a_2 \le \ldots \le a_n \le 3000$，$\sum n \le 3000$。

我们发现 $V$（值域）不大，所以我们可以预处理出来每个数字 $a_i$​ 当 $p∈[1,k] $ 时 $\lfloor\frac{a_i}{p}\rfloor $ 能取到的值，记录在二维 vector $v_i$ 中。然后我们在 $V$ 里面枚举最大值 $maxn$。对于最小值，我们对于每一个 $i$ 都用二分在 $v_i$ 中找到小于等于 $maxn$ 的最大的值 $v_{i,k}$，我们记为 $minn_i$。最后我们在 $minn_i$ 中去最小值就是当前 $maxn$ 对应的 $minn$ 了。

每次枚举 $maxn$ 我们都求出一个最终的 $minn$，然后我们用 $maxn-minn$ 更新答案即可。时间复杂度是 $O(n^2+n\log n)$。对于预处理的 $O(n^2)$，我们可以用数论分块来优化到 $O(n\sqrt n)$。

## 优化

我们要知道我们都预处理的目的是什么——我们还是在 $V$ 中枚举 $maxn$，然后我们要对于每一个 $a_i$ 求小于 $maxn$ 的最大的取值，然后在这些取值中取最小值。那么我们在预处理时只记录对于每一个 $maxn$ 我们 $minn$ 所有取值中的最小值即可。

事实上，这里我们可以在 $V$ 中**枚举 $minn$**，然后求出对于每一个数 $x\in V$，小于它的最大的、$\lfloor\frac{a_i}{p}\rfloor $ 能取到的数是多少。最后我们在枚举 $minn$ 时不断转移当前可以取到的最小的 $maxn$，就可以 $O(1)$ 得到大于 $minn$ 的可以被取到的最小值了。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
const int E=1e6;
const int M=1e9;

#define rd read()
inline int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
inline void write(int out) {
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}


int n,K,m;
int a[N],stk[N],top,T;
map<int,int>cnt;
int ans;
int k,maxn;
int tmp[N],nxt[N];

void solve(){

	for(int i=1;i<=n;i++){
        int tot=0,r=0;
        for(int l=1;l<=min(k,a[i]);l=r+1) {//数论分块
            r=a[i]/(a[i]/l);
            tmp[++tot]=a[i]/l;
        }
        if(k>a[i]) tmp[++tot]=0;//特殊处理k>a_i的情况
        maxn=max(maxn,tmp[tot]);
        tmp[0]=M;
        for(int j=tot;j;j--)nxt[tmp[j]]=max(nxt[tmp[j]],tmp[j-1]);
    }


    ans=M;
    for(int i=0;i<=E;i++){//枚举最小值
        ans=min(ans,maxn-i);
        maxn=max(maxn,nxt[i]);//nxt记录的就是i时能取到的最小的，因此这里取max而不是取min因为要保证可取性
    }
    printf("%d\n",ans);
}

signed main() {
	
	T=rd;
	while(T--){
        memset(nxt,0,sizeof(nxt));
        maxn=0;
        n=rd,k=rd;
        for(int i=1;i<=n;i++)a[i]=rd;
		solve();
	}

	return 0;
}

```




---

## 作者：Leasier (赞：1)

考虑固定最大值 $x$，并对于每个 $x$ 求最大的最小值 $y$。

对于 $a_i$，不难知道当 $p_i \geq \lceil \frac{a_i + 1}{x + 1} \rceil$。由于有限制 $p_i \leq k$ 且让 $p_i$ 取最小值时所求的 $\lfloor \frac{a_i}{p_i} \rfloor$ 一定离 $x$ 最近，所以我们枚举 $x$，先判掉存在 $\lceil \frac{a_i + 1}{x + 1} \rceil > k$ 的情况，继而可以求得 $y = \displaystyle\min_{i = 1}^n \lfloor \frac{a_i}{\lceil \frac{a_i + 1}{x + 1} \rceil} \rfloor$，该 $x$ 的最优答案即为 $x - y$。时间复杂度为 $O(\sum n \max a_i)$。

代码：
```cpp
#include <stdio.h>

int a[3007];

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, k, ans = 0x7fffffff;
		scanf("%d %d", &n, &k);
		for (int j = 1; j <= n; j++){
			scanf("%d", &a[j]);
		}
		for (int j = a[n]; j >= 0; j--){
			int cur_ans = 0;
			bool flag = true;
			for (int x = 1; x <= n; x++){
				int p = a[x] / (j + 1) + 1;
				if (p > k){
					flag = false;
					break;
				}
				cur_ans = max(cur_ans, j - a[x] / p);
			}
			if (!flag) break;
			if (ans > cur_ans) ans = cur_ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：cachejtt (赞：1)

## 题意
给你一个长度为 $n$ 的序列 $a_i$，保证其递增，你需要构造一个序列 $p_i$，保证 $p_i\le k$，你需要使序列的 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$ 最小。

## 思路
由于 $a_i$ 递增，所以最小值一定位于 $\dfrac{a_1}{k}$ 与 $a_1$ 之间。因此枚举最小值，去找它所对应的的最大值并更新答案。

然而我目前做到的这个最小值并不一定能出现，所以在一开始把能出现的最小值全部标记一遍，若当前这个最小值没有出现，则不做它。

做时需要注意整除与精度问题。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
using namespace std;
int t,n,k,a[3005],p,maxa,minans=0x7fffffff,flag,vis[3005];
signed main(){
  std::ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>k;
    rep(i,1,n)cin>>a[i];
    rep(i,1,n)
      rep(p,1,k)vis[a[i]/p]=1;
    minans=0x3f3f3f3f;
    rep(i,a[1]/k,a[1]){
      if(!vis[i])continue;
      maxa=0;
      if(i==0)maxa=a[n]/k;
      else{
        rep(j,1,n){
          p=(int)(a[j]*1.000/i);
          if(p>k)p=k;
          if(a[j]/p>maxa)maxa=a[j]/p;
        }
      }
      if(maxa-i<minans)minans=maxa-i;
      if(minans==0)break;
    }
    cout<<minans<<"\n";
  }
  return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1S94y1Q7zs)

### 2 思路

这里的解法采用困难版本（CF1706D2）的解法。

我们可以发现，根据整除分块的思想，$\lfloor\dfrac{a_i}{p_i}\rfloor$ 的取值最多只有 $\sqrt{a_i}$ 的可能。

所以，我们可以将 $p_i$ 先全部取为 $k$，这样可以得到最小的 $\max_{i=1}^n\{\lfloor\dfrac{a_i}{p_i}\rfloor\}$。

然后，我们使用优先队列，不断调整最小值，同时更新最大值，最终得出答案。

### 3 代码与记录

此代码可以解决困难版本。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define max_n 100000
#define inf 0x3f3f3f3f
int t;
int n;
int k;
int a[max_n+2];
int p[max_n+2];
int w[max_n+2];
struct Q{
	int w,id;
	bool operator<(const Q&a)const{
		return a.w<w;
	}
};
priority_queue<Q>q;
int ansma;
int ansmi;
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1706D2_2.in","r",stdin);
	freopen("CF1706D2_2.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		sort(a+1,a+n+1);
		while(!q.empty())q.pop();
		ansma=-inf;
		ansmi=inf;
		for(int i=1;i<=n;++i){
			p[i]=k;
			w[i]=a[i]/p[i];
			q.push((Q){w[i],i});
			ansma=max(ansma,w[i]);
			ansmi=min(ansmi,w[i]);
		}
		ans=ansma-ansmi;
		while(true){
			int x=q.top().id;
			q.pop();
			ans=min(ans,ansma-w[x]);
			if(ans==0)break;
			++w[x];
			if(p[x]==1)break;
			p[x]=a[x]/w[x];
			w[x]=a[x]/p[x];
			q.push((Q){w[x],x});
			ansma=max(ansma,w[x]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80266054)

By **dengziyue**

---

## 作者：IMIDAZOLE (赞：0)

# [CF1706D1 Chopping Carrots (Easy Version)](https://www.luogu.com.cn/problem/CF1706D1)

## **Solution :**

瞎搞做法。

首先根据整除分块可知，$f(i)=\lfloor \frac{n}{i} \rfloor,i \in[1,n]$ 可得到的不同的数值个数不超过 $2\sqrt n$。

令 $d_i =  \lfloor \frac{a_i}{p_i} \rfloor$，我们可以先 $O(n^2)$ 预处理出 $d_i$ 所有可能的值。

因为序列 $d$ 中的最小值一定不会超过 $a_1$，因此将可能出现的 $d_i$ 的值打个标记，然后枚举序列 $d$ 的最小值，再用 $O(n \log \sqrt n)$ 的时间找出序列 d 的最大值，具体细节可以参考代码，每次更新答案即可。

时间复杂度：大概是 $O(n^2)$ 的吧，因为求解过程中的第一个循环很难跑满……

## **Code:**

```cpp
#include<bits/stdc++.h>
#define LL long long
#define IL inline
using namespace std;
const int N = 3e3 + 10,M = 1e2 + 10,inf = 0x3f3f3f3f;
bool _u;
int T,n,k,a[N],bk[N],p[N][M],len[N];
bool _v;
IL int read() {
	int x = 0,f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')	f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
int main() {
	clock_t st = clock();
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
//	cerr << abs(&_u - &_v) / 1048576.0 << " MB" << endl;
	T = read();
	while(T --) {
		n = read(),k = read();int mx = 0,ans = inf;
		memset(len,0,sizeof(len));
		for(int i = 1;i <= n;i ++)	a[i] = read(),mx = max(mx,a[i]);
		if(k >= mx || n == 1) {printf("0\n");continue;}
		for(int i = 1;i <= n;i ++)
			for(int j = k;j;j --) {
				int x = a[i] / j;
				if(p[i][len[i]] != x)	p[i][++ len[i]] = x,bk[x] = 1;
			}
		for(int i = 1;i <= p[1][len[1]];i ++) {
			if(!bk[i])	continue;
			int mxn = 0;
			for(int j = 1;j <= n;j ++) {
				int k = lower_bound(p[j] + 1,p[j] + len[j] + 1,i) - p[j];
				mxn = max(mxn,p[j][k]);
			}
			ans = min(ans,mxn - i);
			if(!ans)	break;
		}
		printf("%d\n",ans);
	}
//	cerr << (clock() - st) * 1.0 / CLOCKS_PER_SEC << " s" << endl;
	return 0;
}
```

---

## 作者：hgzxwzf (赞：0)

## 解题思路：
### D1:
$n,k\le3000$，直接暴力 $O(n^2)$。

首先预处理出来每个数字 $a_i$ 当 $p\in[1,k]$ 时 $\lfloor \frac{a_i}{p}\rfloor$ 能取到的值。

然后枚举最大值，再用二分找到对于每个 $i$ 的最接近但比枚举到的最大值小的 $\lfloor \frac{a_i}{p}\rfloor$，记为 $w_i$，取所有 $w_i$ 的最小值即可，最后的答案就是最小的最大值减最小值。

#### 代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
using namespace std;

const int N=3000+10;

int a[N],te[N][N];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(te,0,sizeof(te));
		int n,k;
		scanf("%d%d",&n,&k);
		rep(i,1,n) scanf("%d",&a[i]);
		rep(i,1,n)
			per(j,1,k)
				te[i][++te[i][0]]=a[i]/j;
		int ans=1e9;
		rep(i,1,3000)
		{
			bool f=1;
			int mmin=1e9;
			rep(j,1,n)
			{
				int pos=upper_bound(te[j]+1,te[j]+1+te[j][0],i)-te[j]-1;
				if(pos==0) {f=0;break;}
				mmin=min(mmin,te[j][pos]);
			}
			if(f) ans=min(ans,i-mmin);
		}
		printf("%d\n",ans);
	 }
	return 0;
 } 
```
### D2：
$n,k\le100000$，$n^2$ 肯定不太行。

观察到预处理部分可以用数论分块把时间优化到 $O(n\sqrt{n})$。

但如果把所有的 $\lfloor \frac{a_i}{p}\rfloor$ 可能的取值都存下来空间会炸，实际上我们只关心比一个数小的最大数。

对于每个 $i$，首先得到 $\lfloor \frac{a_i}{p}\rfloor$ 可能的取值，记录在 $te$ 中，然后排序，执行：
```cpp
rep(j,1,tot) mx[te[j]]=max(mx[te[j]],te[j+1]);
```
$te_{j+1}$ 就是 $te$ 中比 $tr_j$ 大的最小数，$mx$ 是全局数组。

求答案：
```cpp
rep(i,0,100000)
{
	ans=min(ans,mmax-i);
	mmax=max(mmax,mx[i]);
}
```
首先 $mmax$ 一定大于等于 $i$，因为 $mmax\ge mx_{i-1}$，而 $mx_{i-1}>i-1$，所以 $mmax\ge i$。

其次 $mmax$ 一定是能取到的大于等于 $i$ 的数中最小的。

#### 代码：
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)

using namespace std;

const int N=1e5+10;

void R(int &x)
{
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
}

int a[N],te[N],mx[N];

inline int get(int l,int n)
{
	return n/(n/l);
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(mx,0,sizeof(mx));
		int n,k,mmax=0;
		R(n),R(k);
		rep(i,1,n) R(a[i]);
		rep(i,1,n)
		{
			int tot=0;
			for(int l=1,r=0;l<=min(k,a[i]);l=r+1)
			{
				r=get(l,a[i]);
				te[++tot]=a[i]/l;
			}
			if(k>a[i]) te[++tot]=0;
			reverse(te+1,te+1+tot);
			mmax=max(mmax,te[1]);
			te[tot+1]=1e9;
			rep(j,1,tot) mx[te[j]]=max(mx[te[j]],te[j+1]);
		}
		int ans=1e9;
		rep(i,0,100000)
		{
			ans=min(ans,mmax-i);
			mmax=max(mmax,mx[i]);
		}
		printf("%d\n",ans);
	 }
	return 0;
 } 
```


---

## 作者：11111118m (赞：0)

首先我们要知道，最小值只可能在 $\dfrac{a_1}{k}$ 与 $a_1$ 之间。为什么？有两点。一是整个序列都是递增，$a_1$ 是最小的，又不能变大，二是 $\dfrac{a_1}{k}$ 是所有数中能达到最小的。

# 思路

我们从 $\dfrac{a_1}{k}$ 循环到 $a_1$，用可能的最小值更新答案，最后输出。

因为不是每个我们想要的最小值都能出现，所以我们暴力枚举所有可能的数，复杂度是 $\mathcal{O}(nk)$。

具体怎么更新最小值，是这样的

如果 $\dfrac{a_j}{k}$ 大于等于了枚举的最小值 $i$ 的，那么 $\dfrac{a_j}{k}$ 就是 $a_j$ 能得到最接近 $i$ 的数，所以这时 $maxn=\max(maxn,i-\dfrac{a_j}{k})$。

否则 $maxn=\max(maxn,\lfloor a_j/(\lfloor a_j/i\rfloor)\rfloor-i)$。$\lfloor a_j/i\rfloor$ 是求 $a_j$ 是 $i$ 的几倍，之后的 $\lfloor a_j/(\lfloor a_j/i\rfloor)\rfloor$ 就是求大于等于 $i$ 所能得到最接近 $i$ 的数啦！
# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
template <typename T> inline void read(T &x){
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
const int N = 3e3 + 5; 
int t, n, k, a[N];
bool vis[N];
int main(){
	read(t);
	while (t--){
		read(n), read(k);
		for (int i = 1; i <= n; ++i){
			read(a[i]);
			for (int j = 1; j <= k; ++j) vis[a[i] / j] = 1; //求能出现的数
		}
		if (a[n] < k){puts("0"); continue;} //所有数都小于k时a[i]/k都等于零
		int l = a[1] / k, r = a[1];
		int ans = 0x3f3f3f3f, somans = 0;
		for (int i = l; i <= r; ++i){ //枚举最小值
			if(!vis[i]) continue;
			somans = 0;
			for (int j = 1; j <= n; ++j){
				if (a[j] / k >= i) somans = max(somans, a[j] / k - i);
				else somans = max(somans, a[j] / (a[j] / i) - i);
			}
//			cout << i << "      " << somans << endl;
			ans = min(somans, ans); //更新答案
		}
		printf("%d\n", ans);
	}
}
```
~~这题也太氵了吧~~

---

