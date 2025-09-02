# Most socially-distanced subsequence

## 题目描述

给出一个长度为 $n$ 的排列 $P$，你需要找到它的一个子序列 $P_{s_1},P_{s_2},\dots,P_{s_k}$ 满足：
- $|P_{s_1}-P_{s_2}|+|P_{s_2}-P_{s_3}|+\dots+|P_{s_{k-1}}-P_{s_k}|$ 最大。
- 在上式最大的前提下 $k$ 最小。

求这个子序列的最长长度。

## 样例 #1

### 输入

```
2
3
3 2 1
4
1 3 4 2```

### 输出

```
2
3 1 
3
1 4 2```

# 题解

## 作者：Werner_Yin (赞：2)

## 前言
开始以为是 $DP$ ，但一看到这数据范围，感觉$O(n^2)$不现实，至少也是$O(n \log n)$的算法吧，然后就想到了最长上升子序列的$O(n \log n)$做法，把它改成简单一点的贪心做法，就 $ AC$ 了。
## 思路

维护一个数组，代表最优答案，长度为 $len$,初始时长度为 $0$。

在遍历整个序列时（假设此数为 $te$），我们可以看情况考虑该数是要放到答案末尾，还是把末尾删掉换上自己。

于是就有：
```cpp
for(int i=1;i<=n;i++){
	te=re;
	if(len<=1)li[++len]=te;
	else if(abs(te-li[len])+abs(li[len]-li[len-1])<=abs(te-li[len-1]))li[len]=te;
	else li[++len]=te;
}
```
最后处理一下输出就行了。
## 关于正确性
首先， $te$ 放到答案末尾，肯定会有贡献（原题说了：$p_i$ are distinct），所以必须放才有可能达到最优答案。

对于替换，该数是要放到答案末尾，还是把末尾删掉换上自己，和答案前面的数是无关的，只与答案后两个数有关，看情况就可以处理了。

就这样，我们一次次地对最优答案处理，就得最优解了。

## Code $\downarrow$
具体见注释：
```cpp
#include<bits/stdc++.h>
#define re read()
using namespace std;
const int MAXN=1e5+10;
int read(){
	int x=0,sgn=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-') sgn=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	return x*sgn;
}
int main (){
	int T=re;
	while(T--){
		int n,te,li[MAXN],len=0;
		memset(li,0,sizeof(li));
		n=re;
		for(int i=1;i<=n;i++){
			te=re;
			if(len<=1)li[++len]=te;//最优答案至少要有两个数再开始讨论
			else if(abs(te-li[len])+abs(li[len]-li[len-1])<=abs(te-li[len-1]))li[len]=te;
			else li[++len]=te;//讨论放置的位置，是替换最后一个，还是成为新的最后一个
		}
//开始愉快地输出答案吧！
		if(len==0)printf("-1\n");//虽然感觉-1这种情况不太可能出现，但还是处理一下
		else {
			printf("%d\n",len);
			for(int i=1;i<=len;i++) printf("%d ",li[i]);
			printf("\n");
		}
	}
	return 0;
}	
```


---

## 作者：奇米 (赞：1)

# 题解 - $\mathrm{CF1364B}$

### 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF1364B)

### $\mathrm{Sol}$

* 首先我们考虑一个性质，如何才能使得贡献尽量大。画几个图看看

![](https://cdn.luogu.com.cn/upload/image_hosting/tleb1p90.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于第一种一条直线类型的它的实际贡献就是$|c-a|$，而对于第二种它的贡献就为$|a-d|+|d-b|+...|c-e|$。发现能产生贡献的情况就是那种**峰，谷**的情况，于是我们记录这些拐点即可。时间复杂度$O(n)$

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int mo=998244353;
const int N=1e5+5;

int n,m,Q,a[N],b[N],ans;

int main()
{
	Q=read();
	For(q,1,Q)
	{
		n=read();
		For(i,1,n) a[i]=read();
		b[m=1]=1;
		For(i,2,n-1) 
			if((a[i]>a[i-1]&&a[i]>a[i+1])||(a[i]<a[i-1]&&a[i]<a[i+1])) b[++m]=i;
		b[++m]=n;
		printf("%d\n",m);
		For(i,1,m) printf("%d ",a[b[i]]);
		puts("");
	}
	return 0;
}

```


---

## 作者：b6e0_ (赞：1)

[CF题面传送门](https://codeforces.com/contest/1364/problem/B) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1364B) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1364B)

分析题目。发现对于任意$a,b,c$（$a\le b\le c$或$a\ge b\ge c$），$\vert a-b\vert+\vert b-c\vert=\vert a-c\vert$。令两两差的绝对值的和最大的一种情况肯定是全取，但是这种方法可能不是最短的。按照上面的性质，我们可以去掉单调递减或单调递增部分中间的数。即只留开头、所有山峰和山谷、结尾。赛时代码，写的很丑：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010];
int main()
{
	int t,n,i;
	cin>>t;
	while(t--)
	{
		cin>>n;
		vector<int>ans;
		for(i=0;i<n;i++)
			cin>>a[i];
		for(i=1;i<n-1;i++)
			if(a[i]>a[i-1]&&a[i]>a[i+1]||a[i]<a[i-1]&&a[i]<a[i+1])//找山峰和山谷
				ans.push_back(a[i]);
		cout<<2+ans.size()<<endl<<a[0]<<' ';//个数要+2
		for(i=0;i<ans.size();i++)
			cout<<ans[i]<<' ';
		cout<<a[n-1]<<endl;
	}
	return 0;
}
```
时间复杂度为$O(n)$。

---

## 作者：lzy120406 (赞：0)

## [原题](https://codeforces.com/problemset/problem/1364/B)
题目给出一个长度为 $n$ 的排列 $P$，需要找到它的一个子序列 $P_{s_1},P_{s_2},\dots,P_{s_k}$ 满足：
- $|P_{s_1}-P_{s_2}|+|P_{s_2}-P_{s_3}|+\dots+|P_{s_{k-1}}-P_{s_k}|$ 最大。
- 在上式最大的前提下 $k$ 最小。

## 思路
为了使相邻元素的差的绝对值之和最大，子序列应该包含排列中的“**极值点**”，即局部最大值和局部最小值。

这样，子序列中的元素会在排列中“**跳跃**”，从而最大化相邻元素的差的绝对值之和。

子序列的长度 $k$ 最小意味着我们只需要保留这些极值点，而不需要包含其他元素。

所以我们有如下做法：

- 遍历排列 $P$，找到所有的极值点（局部最大值和局部最小值）。
- 将这些极值点按顺序组成子序列。
- 输出子序列的长度和元素。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int p[100005];
void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
	}
	vector<int> seq;
	seq.push_back(p[0]); // 第一个元素一定是极值点
	for (int i = 1; i < n - 1; ++i) {
		// 检查当前元素是否是极值点
		if ((p[i] > p[i - 1] && p[i] > p[i + 1]) || (p[i] < p[i - 1] && p[i] < p[i + 1])) {
			seq.push_back(p[i]);
		}
	}
	seq.push_back(p[n - 1]); // 最后一个元素一定是极值点
	cout << seq.size() << endl;
	for (int num : seq) {
		cout << num << " ";
	}
	cout << endl;
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn) $，本题中 $\sum{n} \leq 10^5 $，可以通过本题。

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1364B)

------------

# 思路：
显然只要保留所有“极值点”就行了。或者说，去掉所有满足 $p_{i-1}$ 小于 $p_i$ 小于 $p_{i+1}$ 或者 $p_{i-1}$ 大于 $p_i$ 大于 $p_{i+1}$ 的 $p_i$。

这是因为如果 $a \le b \le c$ 或者 $a \ge b \ge c$，那么有 $ | a - b | + | b - c | = | a - c |$。反过来也成立。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define repeat(i,a,b) for(int i=(a),_=(b);i<_;i++)
#define repeat_back(i,a,b) for(int i=(b)-1,_=(a);i>=_;i--)
int cansel_sync=(ios::sync_with_stdio(0),cin.tie(0),0);
const int N=200010; typedef long long ll; const int inf=~0u>>2; const ll INF=~0ull>>2;
#define int ll
int n,a[N],ans;
void solve(){
	cin>>n; ans=n;
	repeat(i,0,n)cin>>a[i];
	repeat(i,1,n-1)
	if((a[i-1]-a[i])*(a[i]-a[i+1])>0)
		ans--;
	cout<<ans<<endl;
	cout<<a[0]<<' ';
	repeat(i,1,n-1)
	if((a[i-1]-a[i])*(a[i]-a[i+1])<=0)
		cout<<a[i]<<' ';
	cout<<a[n-1]<<endl;
}
signed main(){
	int T; cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：mxxby (赞：0)

# 题目简介

**[题目传送门](https://www.luogu.com.cn/problem/CF1364B)**

给出 $t$ 组数据，每组数据 $n$ 个数，求出从中选一些数且使选出的数按原位置排序后相邻的两个数的差值总和最小，在满足上述条件下使选出的数数量最少。

# 大致（智）~~若愚~~思路

一道小贪心，对于每个数，我们一开始都选，但是，要判断选前一个数是否还有利益。比如：$1\ 2\ 3$，我们一开始选上$1\ 2$，到 $3$ 时，我们也选，但判断到不选 $2$ 的价值等于（大于同理）选上 $2$的价值，那这个 $2$ 已经没用了，直接弃掉。

# ~~麻袋~~代码

```c++
#include<bits/stdc++.h>
using namespace std;
int t,n,a,s[100010],gs;//s是存储选取的数，可以把数组优化掉但其实比不优化代码更烦（而且也就这么点空间而已）
int main(){
	scanf("%d",&t);//t组数据
	for(int i=1;i<=t;i++){
		scanf("%d",&n);//n个数
		gs=0;//多组数据必备清空（因为s数组跟随gs改变所用范围，所以s数组不必清空）
		for(int j=1;j<=n;j++){
			scanf("%d",&a);//n个数输入（这个数组还是可以省下来的）
			s[++gs]=a;//每个数一开始都选
			if(gs>=3 && abs(s[gs]-s[gs-2])>=abs(s[gs]-s[gs-1])+abs(s[gs-1]-s[gs-2])) s[--gs]=s[gs+1];//判断上一个前辈还有没有贡献价值，没有就送去养老，自己上位
		}
		printf("%d\n",gs);//输出选了几个数
		for(int j=1;j<=gs;j++){
			if(j>1) printf(" ")//防末尾0(习惯了);
			printf("%d",s[j]);//输出
		}
		printf("\n");
	} 
	return 0;//总结全文：数组后浪推前浪，前浪挤到沙滩上，都是后来的占据前面的位置
}

```

~~萌新蒟蒻的第四篇题解一审，求过 qwq。~~

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：

这题没啥好说的，找其绝对值最大，也就是找到每一个山峰山谷。   

这样不仅满足选择的个数最少，并且值最大。

正确性证明：

- 若 $a\le b\le c$ 
- $|a-b|+|b-c|=(b-a)+(c-b)=b-a+c-b=c-a=|a-c|$
- 若 $a\ge b\ge c$
- $|a-b|+|b-c|=(a-b)+(b-c)=a-b+b-c=a-c=|a-c|$

注意：最后一个特判一下。

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e5+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

int t,n;
int a[N];

int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);	
		}
		queue<int>q;
		int f=-1,ans=0;
		for(int i=1;i<n;++i){
			int k=(a[i]>a[i+1]);
			if(k!=f){
				q.push(a[i]);
				++ans;
				f=k;
			}
		}
		q.push(a[n]);
		++ans;
		printf("%d\n",ans);
		while(!q.empty()){
			printf("%d ",q.front());
			q.pop();
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：huayucaiji (赞：0)

~~这个题比 A 简单~~

我们先来看一个单调递增的区间：$a_1,a_2,a_3...a_{k-1},a_k$，满足 $a_1<a_2<a_3<...<a_{k-1}<a_k$。

对于这个区间，如果我们选择了 $a_{b_1},a_{b_2},a_{b_3}...a_{b_{q-1}},a_{b_q}$，其中 $b_1<b_2<b_3<...<b_{q-1}<b_q\leq n$ 此时我们得到的答案为  
$$ans=((a_{b_2}-a_{b_1})+(a_{b_3}-a_{b_2})+...+(a_{b_q}-a_{b_{q-1}}))$$  
$$ans=a_{b_q}-a_{b_1}$$

由此可得：$ans_{max}=a_k-a_1$

单调递减的区间同理。

因此我们只需要找出每一个单调递增和单调递减的区间即可，看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10;

int n,a[maxn],sum[maxn],x;

signed main() {
	int t;
	t=read();
	while(t--) {
		n=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
		}

		int ans=0,last=1,len=2;//last记录分界点
		bool now=a[1]<a[2];//now记录递增还是递减，为1就是递增，0是递减，下同

		for(int i=2;i<=n;i++) {
			if(a[i]<a[i-1]==now) {
				ans+=abs(a[i-1]-a[last]);
				last=i-1;
				now=1-now;//递增递减交换
				len++;
			}
		}

		ans+=abs(a[n]-a[last]);
		cout<<len<<endl; 

		now=a[1]<a[2];

		cout<<a[1]<<" ";
		for(int i=2;i<=n;i++) {
			if(a[i]<a[i-1]==now) {
				printf("%lld ",a[i-1]);
				now=1-now;//递增递减交换
			}
		}
		cout<<a[n]<<endl;//注意一头一尾单独处理~
	}
	return 0;
}
```

---

## 作者：Isshiki_Hugh (赞：0)

乍一看能被唬住，但实际上就是找一个数列的峰谷。

对于某一个单调的区间$a_{i+1},a_{i+2},...,a_{i+k}$必然有$|...|+...+|...| = |a_{i+1}-a_{i+k}|$

那答案就显然了，把峰谷都找出来，然后输出就完事了

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<cstdlib>//rand()
#define rep(i,a,b) for(register int i = (a);i <= (b);++i)
#define per(i,a,b) for(register int i = (a);i >= (b);--i)
typedef long long ll;
typedef unsigned long long ull;
using std::string;using std::cin;using std::cout;

int _,n,a[111111],b[111111];

int main(){
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("in.in", "r", stdin);
    cin >> _;
    while(_--){
        cin >> n;
        rep(i,1,n) cin >> a[i];
        rep(i,0,n) b[i] = 0;
        b[++b[0]] = a[1];
        rep(i,2,n){
            if(a[i] > a[i-1]){
                while(a[i+1] > a[i] && i < n) ++i; 
                b[++b[0]] = a[i];
                continue;
            } else {
                while(a[i+1] < a[i] && i < n) ++i;
                b[++b[0]] = a[i];
                continue;                
            }
        }
        cout << b[0] << "\n";
        rep(i,1,b[0]) cout << b[i] << " ";
        cout << "\n";
    }


    return 0;
}
```

---

## 作者：KellyFrog (赞：0)

全选上一定结果最佳，那么我们只要找出没有贡献的就行了。

考虑$a_{i-1},a_i,a_{i+1}$，如果$a_i$是第二大的数，那么$|a_{i-1}-a_i|+|a_i-a_{i+1}|=|a_{i-1}-a_{i+1}$，这时的$a_i$是没有贡献的。

因为没有一样的，所以我们只要找出上面所说的没有贡献的不输出就好了。

记得把第一个和最后一个选上。

code：
```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 5;

int a[MAXN], n, t;

void Solve() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	vector<int> v;
	v.push_back(a[1]);
	for(int i = 2; i < n; i++) {
		if((a[i - 1] <= a[i] && a[i] <= a[i + 1]) || (a[i - 1] >= a[i] && a[i] >= a[i + 1])) {
			continue;
		}
		v.push_back(a[i]);
	}
	v.push_back(a[n]);
	cout << v.size() << endl;
	for(auto i : v) {
		cout << i  << ' ';
	}
	cout << endl;
}

int main() {
	cin >> t;
	while(t--) {
		Solve();
	}
}
```

---

