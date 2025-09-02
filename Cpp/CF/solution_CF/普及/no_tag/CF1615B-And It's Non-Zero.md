# And It's Non-Zero

## 题目描述

You are given an array consisting of all integers from $ [l, r] $ inclusive. For example, if $ l = 2 $ and $ r = 5 $ , the array would be $ [2, 3, 4, 5] $ . What's the minimum number of elements you can delete to make the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of the array non-zero?

A bitwise AND is a binary operation that takes two equal-length binary representations and performs the AND operation on each pair of the corresponding bits.

## 说明/提示

In the first test case, the array is $ [1, 2] $ . Currently, the bitwise AND is $ 0 $ , as $ 1\ \& \ 2 = 0 $ . However, after deleting $ 1 $ (or $ 2 $ ), the array becomes $ [2] $ (or $ [1] $ ), and the bitwise AND becomes $ 2 $ (or $ 1 $ ). This can be proven to be the optimal, so the answer is $ 1 $ .

In the second test case, the array is $ [2, 3, 4, 5, 6, 7, 8] $ . Currently, the bitwise AND is $ 0 $ . However, after deleting $ 4 $ , $ 5 $ , and $ 8 $ , the array becomes $ [2, 3, 6, 7] $ , and the bitwise AND becomes $ 2 $ . This can be proven to be the optimal, so the answer is $ 3 $ . Note that there may be other ways to delete $ 3 $ elements.

## 样例 #1

### 输入

```
5
1 2
2 8
4 5
1 5
100000 200000```

### 输出

```
1
3
0
2
31072```

# 题解

## 作者：caibet (赞：2)

### 更新日志：

- $\texttt{2022.1.6:}$ 纠正了时间复杂度上的一个错误。

### 题意：

在区间 $[l,r]$ 中，询问要删除几个数才能让其按位与非 $0$。

### 解法：

要让按位与非 $0$，我们就要坚守一个二进制位让它总不为 $0$。

哪个二进制位呢？我们也不知道。那我们只能看看，哪个位被最多的数覆盖。

比如，$l=1,r=5$ 时，$3$ 个二进制位的使用情况如下：

$$
\begin{array}{ll}
\begin{array}{ll}
1\texttt{=}&0&0&1\\
2\texttt{=}&0&1&0\\
3\texttt{=}&0&1&1\\
4\texttt{=}&1&0&0\\
5\texttt{=}&1&0&1\\
\end{array}\\
\rule{70px}{0.7px}\\
\texttt{sum=}&\kern{-54px}2&\kern{-94px}2&\kern{-84px}3
\end{array}
$$

有 $3$ 个数在第 $1$ 位上的位为 $1$。这意味着，我们只要删除其余的 $2$ 个数，就可以保证整个集合的按位与的第 $1$ 位为 $1$。

我们考虑开一个数组 `f[i]` 用于存储第 $i$ 位上为 $1$ 的数的个数。我们从 $l$ 到 $r$ 遍历，把所有数统计一遍。

怎么统计？树状数组内有个东西叫 lowbit，求一个数二进制最后的 $1$ 表示的数。我们每次把当前数减去 $\text{lowbit}(x)$，顺便统计这个 lowbit 所在的数位。最后求出 `f[]` 中的最大值 $\max(f)$，输出 $r-l+1-\max(f)$ 即可。单次时间复杂度在线性对数阶。

目前的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int lim=2e5+1;
int T,l,r,f[19],lg[lim];//log2(200000)=18

template<class T=unsigned> inline T readu(){
	T x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}
 
void bits(int x){
	while(x){
		f[lg[x&-x]]++;//将当前lowbit所在的位数统计
		x^=x&-x;//并去掉这一位
	}
}
int main(){
	T=readu();
	for(int i=2;i<lim;i++) lg[i]=lg[i>>1]+1;//求 log 值，便于后面按位统计
	while(T--){
		memset(f,0,sizeof(f));
		l=readu();r=readu();
		for(int i=l;i<=r;i++){
			bits(i);
		}
		int ans=0;
		for(int i=0;i<19;i++) ans=max(ans,f[i]);//表示 2^i 的位上最多有几个数覆盖
		printf("%d\n",r-l+1-ans);//删掉剩余的数
	}
	return 0;
}
```

高高兴兴提交去，惶惶恐恐 TLE 来。

![](https://s4.ax1x.com/2021/12/25/TUNEJH.gif)

### 优化：

我们看看为什么程序跑得这么慢。

我们对于每一次询问，都从 $l$ 扫到 $r$，并统计一些**静态**信息的和。

区间求静态信息之和，用什么优化？$\textbf{\textsf{前缀和。}}$

于是我们把上述单个数的 `f[]` 看作一个整体，并在最开始维护前缀和 $s_k=\sum\limits_{i=1}^{k}f_i$，之后求和时计算 $s_r-s_{l-1}$ 即可。

于是单次查询就变成了对数阶，[跑得还挺快](https://www.luogu.com.cn/record/list?pid=CF1615B&orderBy=1&status=&page=1)。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define return while(1)
const int lim=2e5+1;
int T,l,r,s[lim][19],lg[lim];

template<class T=unsigned> inline T readu(){
	T x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

void bits(int x){
	int t=x;
	while(x){
		s[t][lg[x&-x]]++;
		x^=x&-x;
	}
}
int main(){
	T=readu();
	s[1][0]=1;
	for(int i=2;i<lim;i++){
		lg[i]=lg[i>>1]+1;
		bits(i);
		for(int j=0;j<19;j++) s[i][j]+=s[i-1][j];//前缀和预处理
	}
	while(T--){
		l=readu();r=readu();
		int ans=0;
		for(int i=0;i<19;i++) ans=max(ans,s[r][i]-s[l-1][i]);//求 l~r 在某一二进制位上为 1 数的最大值
		printf("%d\n",r-l+1-ans);
	}
	return 0;
}
```

---

## 作者：activeO (赞：1)

## 题目大意

[题面](https://www.luogu.com.cn/problem/CF1615B) 说的比较清楚，这里就不说了。

## 思路

按位与就是至少有一位全是 1 才满足。看到这个数据：

$ 1 \leq l \leq r \leq 2 \cdot 10^5 $

于是就可以枚举第 j 为 1，时间复杂度 $ O(\log n) $。

对于每一个 j 去计算第 j 位为 1，且在 $ [l,r] $ 内的数的个数 cnt。

发现每 $ 2^j $ 个连续的数中就有 $ 2^{j-1} $ 个第 j 位为 1，余下的特殊判断一下就行了。

最后的答案取 $ \min n-cnt $。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

int qpow(int x,int y){//其实可以不用快速幂
	int res=1;
	while(y){
		if(y&1) res*=x;
		x*=x;
		y>>=1;
	}
	return res;
}

int calc(int x,int j){//计算第j为为1的数的个数。
	int tmp=qpow(2,j),ans=x/tmp*(tmp/2);
	if((x%tmp)>(tmp/2)) ans+=(x%tmp)-(tmp/2);
	return x-ans;
}

int main(){
	
	int t;
	
	scanf("%d",&t);
	
	while(t--){
		int l,r;
		scanf("%d %d",&l,&r);
		int ans=r;
		for(int j=0;j<=18;j++){// log(r)
			ans=min(ans,calc(r+1,j)-calc(l,j));
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
```


---

## 作者：ArrogHie (赞：1)



------------
要求剩下的数 $AND$ 起来不为 $0$ ，我们只要有任意一位不为 $0$ 就行了，设 $a_i$ 为第 $i$ 位为 $1$ 的数有几个，将这几个数 $AND$ 的值至少是 $2^i$ 。只保留一位不为 $0$ 一定是比保留两位及以上的不为 $0$ 的需要删除的数少，答案即为所有数减去最大的 $a_i$ 

---

## 作者：aaalys (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1615B)
### 思路
要让所有元素按位与的结果不为 $ 0 $，就要让所有元素在二进制的某一位都为 $ 1 $。
### 解法 
所以我们可以枚举每个二进制位，看看有几个 $ 0 $，求出最小值就是答案。
### 目前代码：
[云剪贴板](https://www.luogu.com.cn/paste/ekt5ibpu)。当我提交的时候，发现[提交记录](https://www.luogu.com.cn/record/119395204)，全 T 了。
### 优化
我们先来看看为什么会这样：这个算法的时间复杂度是 $ O(\sum{}r - l + 1) $。对于数据来说，已经到了 $ 2 \times 10^9 $ 量级，当然会 TLE。我们想到：求的其实是多个区间和的最小值。一想到区间和，就想到用到前缀和。所以，我们可以用 $ sum_{i,j} $ 表示 $ 1 \sim i $ 中二进制的第 $ j $ 位上有几个 $ 1 $。先预处理一下，算出前缀和数组，最后计算的时候只需要枚举每一个二进制位，时间复杂度是 $ O(t) $。
### 最终代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int sum[200010][20];//前缀和数组，最大为log(2e5)=18
int main (){
    for (int i = 1; i <= 2e5; i++){
        int a[20] = {};//a[i]表示二进制的第i位
        int t = i , cnt = 0;
        while (t){
            a[++cnt] = t & 1;
            t = t >> 1;
        }
        for (int j = 1; j <= cnt; j ++)sum[i][j] = sum[i-1][j] + a[j];
    }
    int t;
    cin >> t;
    while (t--){
        int l , r;
        cin >> l >> r;
        int mx = 0;
        for (int i = 1; i <= 20; i ++)//枚举每一个二进制位
            mx = max(mx , sum[r][i] - sum[l-1][i]);
        cout << r - l + 1 - mx << endl;//通过0的个数求1的个数
    }
}
```

---

## 作者：houpingze (赞：0)

不难想到我们可以枚举每一位，对于第 $i$ 位，我们求出 **要使数组中的 $\text{and}$ 和的第 $i$ 位为 $1$，需要删除的最小的数字的数量**。

但是每次遍历寻找显然会 T飞 ，我们可以定义 $f_{i,j}$ 表示 **小于等于 $i$ 且第 $j$ 位为 $1$ 的数字的数量**，然后这个 $f$ 就很好求了，用前缀和思想即可。

最后查询的时候答案就是 $\max_{i=0}^{\left\lceil \log{2 \times10^5}\right\rceil} f_{r,i}-f_{l-1,i}$ ，利用的也是前缀和思想，$f_{r,i}-f_{l-1,i}$ 即为上文

> 要使数组中的 $\text{and}$ 和的第 $i$ 位为 $1$，需要删除的最小的数字的数量。

---

## 作者：isjwanglongLuoGU (赞：0)

## 大意
您将获得一个数组，该数组由以下位置的所有整数组成：$[l,r]$。例如，如果  $ l=2 $ 和 $ r=5 $，则数组将是 $ [2,3,4,5] $。可以删除以使数组的按位不为零的最小元素数是多少？
## 思路
先考虑转换成 $ 2 $ 进制。    
再判断 $ 31 $ 个 $ 2 $ 进制位 $ 1 $ 的数量。    
查找其中最容易变成全是 $ 1 $。  

用总数减去即可
但是会TLE

### Tip: 
见代码 

## 优化~~O2~~
因为数据量大。    
可以用 _前缀和_ 寄存。
## 代码~~欢迎复制~~
```cpp
#include<bits/stdc++.h>//卐能头文件 
using namespace std;//std::
#define fau(it,a) for(auto it=(a).begin();it!=(a).end();it++) 
#define f(i,a) for(int i=0;i<(a);i++)
#define fo(i,a,b,c) for(int i=(a);i<(b);i+=(c))
#define f2(i,a,b,c) for(int i=(a);b;c)
#define sz size()
#define siez size
#define lg length()
#define lenght length
#define cg(a) getline(cin,(a)) 
#define pb push_back
inline int input()//慢速快读 
{
    int x=0,f=1;char gc=getchar();
    while(gc>'9'||gc<'0'){if(gc=='-')f=-f;gc=getchar();}
    while(gc<='9'&&gc>='0'){x*=10;x+=(gc-'0');gc=getchar();}
    return f*x;
}
inline int read()//快速快读 
{
    int x=0,f=1;char gc=getchar();
    while(gc<'0'||gc>'9'){if(gc=='-')f=-1;gc=getchar();}
    while(gc>='0'&&gc<='9'){x=(x<<1)+(x<<3)+(gc^48);gc=getchar();}
    return f*x;
}
//void solve()
//{
//	vector<int>v(31,0);
//	int l=read(),r=read();
//	for(int i=l;i<=r;i++)f(j,31)if((i>>j)&1)v[j]++;
//	int mx=-1*inf;
//	f(i,31)mx=max(mx,v[i]);
//	printf("%d\n",(r-l+1)-mx);
//}
//TLE
int pre[200005][31];//前缀和数组 
int solve()//方案解决 
{
	int l=read(),r=read();//左值与右值 
	int mx=0;//统计某一位1数量的最多值 
	f(i,30)mx=max(mx,pre[r][i]-pre[l-1][i]); 
	printf("%d\n",(r-l+1)-mx);//输出删去的最少数量 
}
signed main(void) 
{
	for(int i=1;i<=200000;i++)f(j,31)
	{
		if((1<<j)&i)pre[i][j]++;
		pre[i][j]+=pre[i-1][j];
	}//前缀和 
	int t=input();
	while(t--)solve();//t个点 
	return 0;
}
```

---

## 作者：JerryMao (赞：0)

[传送门](https://codeforces.com/contest/1615/problem/B)

这题是一个贪心。我们只要看每个位上有几个数，然后取最大值，用 $n$ 减去它就行了。

但是这样会超时，可以用前缀和来预处理，	用 $bit_{i,j}$  表示 $1$ 到 $i$ 第 $j$ 位有几个数，就可以A了。~~（但是本蒟蒻还是tle了~~

AC 代码：~~dalao们可以走了~~

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define rep(i,n) for(int i=0;i<n;i++)
#define Rep(i,x,n) for(int i=x;i<n;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define all(v) v.begin(),v.end()
#define itr_ iterator
#define p_b push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fr first
#define sc second
#define m_p make_pair
#define fill(a,b) memset(a,b,sizeof(a))
#define debug(x) cout<<#x<<":"<<x<<endl;
#define setp setprecision
#define over(x) {cout<<x<<endl; return ;}//一堆没用的头
using namespace std;
const ll INF=0x7f7f7f7f;
const ll mod=1000000007;
const ld eps=1e-14;

int bits[200005][20];

void solve(){
	int l,r;
	cin>>l>>r;
	int b[20]={0};
	rep(i,20) b[i]=bits[r][i]-bits[l-1][i];//统计[l,r]区间内每一位的个数
	int ans=INF;
	rep(i,20){
		ans=min(ans,r-l+1-b[i]);
	}
	cout<<ans<<endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	fill(bits,0);
	Rep(i,1,200005){
		int x=i,b=0;
		while(x){
			bits[i][b]=bits[i-1][b]+(x&1);
			b++;
			x>>=1;
		}
	}//预处理
	int T; cin>>T;
	while(T--){
		solve();
	}
	return 0;
}

```


---

## 作者：清烛 (赞：0)

可能还算一道比较巧妙的题。

不难发现我们可以分开每一位考虑。

只要有一位上的数字全是 $1$，那么 and 起来就不为 $0$。那么我们是不是可以考虑枚举某一位，然后将这一位上为 $0$ 的数字删掉，这样子 and 起来后，这一位一定是 $1$，故整体不为 $0$。

预处理一下 $S_{i,j}$ 表示 $[1, n]$ 中第 $j$ 位为 $1$ 的数字的个数，那么答案就是
$$
\min_j\{r - l + 1 - (S_{r, j} - S_{l - 1, j})\}
$$
预处理 $O(N\log N)$，$O(\log N)$ 回答单次询问。

```cpp
const int maxn = 2e5 + 5, maxlog = 19, N = 2e5;
int sum[maxn][maxlog];

int main() {
    int T; read(T);
    FOR(i, 1, N) {
        FOR(j, 0, 18) {
            sum[i][j] = sum[i - 1][j] + ((i >> j) & 1);
        }
    }
    while (T--) {
        int l, r; read(l, r);
        int ans = r - l + 1;
        FOR(j, 0, 18) chkmin(ans, r - l + 1 - (sum[r][j] - sum[l - 1][j]));
        print(ans);
    }
    return output(), 0;
}
```

---

