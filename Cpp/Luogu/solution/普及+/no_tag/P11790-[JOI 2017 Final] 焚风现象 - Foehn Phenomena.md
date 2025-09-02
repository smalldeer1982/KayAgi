# [JOI 2017 Final] 焚风现象 / Foehn Phenomena

## 题目描述

你知道 $N+1$ 个地点的海拔 $A_i$，编号为 $0 \dots N$，有风从 $0$ 吹向 $N$，想让你求出地点 $N$ 的风的温度，保证 $A_0=0$。

规则：
- 如果 $A_i=A_{i+1}$，风的温度不变。
- 如果 $A_i>A_{i+1}$，由于海拔降低，风的温度会上升 $(A_i-A_{i+1})\times T$ 度。
- 如果 $A_i<A_{i+1}$，由于海拔升高，风的温度会下降 $(A_{i+1}-A_i)\times S$ 度。

## 说明/提示

【数据范围与约定】

对于所有数据，均满足：

- $1\le N\le 200000$。
- $1\le Q\le 200000$。
- $1\le S\le 1000000$。
- $1\le T\le 1000000$。
- $-1000000\le A_i\le 1000000(1\le i\le N)$．
- $1\le L_j\le R_j\le N (
1\le j\le Q)$。
- $−1000000\le Xj\le 1000000 (1\le j\le Q)$。

1. Subtask $1$（$30$ pts）：满足 $N,Q \le 2000$。
2. Subtask $1$（$10$ pts）：满足 $S=T$。
3. Subtask $1$（$60$ pts）：无特殊限制。


## 样例 #1

### 输入

```
3 5 1 2
0
4
1
8
1 2 2
1 1 -2
2 3 5
1 2 -1
1 3 5```

### 输出

```
-5
-7
-13
-13
-18```

## 样例 #2

### 输入

```
2 2 5 5
0
6
-1
1 1 4
1 2 8```

### 输出

```
5
-35```

## 样例 #3

### 输入

```
7 8 8 13
0
4
-9
4
-2
3
10
-9
1 4 8
3 5 -2
3 3 9
1 7 4
3 5 -1
5 6 3
4 4 9
6 7 -10```

### 输出

```
277
277
322
290
290
290
290
370```

# 题解

## 作者：Twlight！ (赞：5)

发现做法唐了，回来重新思考。

如果没有修改操作，我们可以直接 $O(n)$ 算出答案，于是我们考虑每次操作会改变什么。

其实影响最终温度的只有相邻两地的相对海拔差，每次给一个区间的海拔加减，这个区间内的相对海拔差是不会变的，只有区间左右两边相邻的海拔差会改变，考虑使用差分数组维护，每次动态更新答案即可。

时间复杂度：$O(n + q)$，注意本题要开 long long。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int ll

const int N = 1000000 + 10;
const int inf = 1e9 + 7;
using namespace std;

inline int read () {
	int x = 0, k = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return (1ll * x * k);
}

int n, q, s, t, ret;
int a[N], b[N]; 

int calc (int x) {
	if (x > 0) return x * t;
	else return x * s;
}

signed main() {
	n = read(), q = read(), s = read(), t = read();
	for (int i = 0; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) b[i] = a[i - 1] - a[i], ret += calc(b[i]);
	for (int i = 1; i <= q; ++i) {
		int l = read(), r = read(), x = read();
		ret -= calc(b[l]), ret -= (r < n) * calc(b[r + 1]);
		b[l] -= x, b[r + 1] += x;
		ret += calc(b[l]), ret += (r < n) * calc(b[r + 1]);
		cout << ret << endl;
	}
	return 0;
}
```

---

## 作者：_xzhdsnh1364 (赞：5)

这题在考试的时候只想着打暴力了，没有想到正解。

# SOLUTION

这题的重点很明显是那一堆变换操作（废话），这道题给人的差分感觉还是比较明显的，因为你中间的改变其实并不能影响总体的差值，只会影响最左边和最右边的右边一个，那这样思路就比较明确了，再开一个变量动态更新即可。

# CODE

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
int n , q;
ll s , t , a[N] , d[N] , l , r , x , now;
ll ans(ll x){//按题意模拟的，因为懒加上的
    if(x > 0)return x * t;
    return x * s;
}
int main(){
	cin >> n >> q >> s >> t;
	for(int i = 0;i <= n;i++)cin >> a[i];
	for(int i = 1;i <= n;i++)d[i] = a[i - 1] - a[i] , now += ans(d[i]);//初始化差分数组
	while(q--){
        cin >> l >> r >> x;
        //去掉原本的贡献
        now -= ans(d[l]);
        if(r < n)now -= ans(d[r + 1]);
        d[l] -= x , d[r + 1] += x;//差分数组变换
        //加上目前的贡献
        now += ans(d[l]);
        if(r < n)now += ans(d[r + 1]);
        cout << now << '\n';
	}
	return 0;
}
```

---

## 作者：Inracle (赞：4)

建议降黄，三倍经验：[1](https://www.luogu.com.cn/problem/P3655)，[2](https://www.luogu.com.cn/problem/AT_joi2017ho_a)。

### 分析

根据题目，每次计算贡献时都根据两个相邻的海拔计算。所以我们可以把原数组处理成**差分数组**。这时就可以发现一个奇妙的性质：每次区间加时只有左端点和右端点 +1 的点差分数组值会改变！

于是先预处理成差分数组并算出初始答案，然后对于每个修改，先删去左右端点的贡献，再修改差分数组，加上左右端点的贡献。你就会发现你过了。

由题意可得，计算贡献时：
设 $B_i=A_i-A_{i-1}$，$X_i$ 为该处的贡献，

- 若 $B_i > 0$，$X_i = - B_i \times S$；
- 若 $B_i \le 0$，$X_i = - B_i \times T$；

注意：当修改右端点为 $N$ 时，**不要**改差分数组和贡献！

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,rp,stdin),p1==p2)?EOF:*p1++)

using namespace std;
const int N=2e5+10;
const int rp=1e6+10;

int n,q,s,t,ans,p[N];
char buf[rp],*p1=buf,*p2=buf;

inline int read() 
{
	int x=0,f=1; char c=0;
    while(!isdigit(c)){if(c=='-') f=-1; c=gc();}
    while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=gc();
    return x*f;
}//快读

signed main()
{
	cin.tie(0)->sync_with_stdio(0);
	n=read(); q=read(); s=read(); t=read(); int l,r,x;
	for(int i=0;i<=n;++i) p[i]=read();
	for(int i=n;i>=1;--i) p[i]-=p[i-1];//转差分数组 
	for(int i=1;i<=n;++i) 
		if(p[i]>0) ans-=p[i]*s;
		else ans-=p[i]*t;//算最初答案
	while(q--)
	{
		l=read(); r=read(); x=read();
		
		if(p[l]>0) ans+=p[l]*s;
		else ans+=p[l]*t;//减左端点原贡献 
		p[l]+=x;//改差分数组 
		if(p[l]>0) ans-=p[l]*s;
		else ans-=p[l]*t;//加左端点现贡献
		
		if(r<n)//防止越界修改而 WA 掉 
		{
			if(p[r+1]>0) ans+=p[r+1]*s;
			else ans+=p[r+1]*t;//减右端点原贡献 
			p[r+1]-=x;//改差分数组 
			if(p[r+1]>0) ans-=p[r+1]*s;
			else ans-=p[r+1]*t;//加右端点现贡献 
		}
		
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Starriverlight (赞：3)

区间修改，在线查询，修改区间内信息不变，非常容易想到线段树吧。（

## 思路

线段树维护序列，每个节点存储 $[l,r]$ 区间内 $a_l,a_r$ 以及风从 $l$ 出发到 $r$ 点风的温度，上传时根据 $a_{mid},a_{mid+1}$ 以及 $mid,r$ 点的温度计算即可。

```cpp
void pushup(int k){
//la:a_l ra:a_r rt:从l到r风的温度
  Tree[k].la=Tree[lx(k)].la,Tree[k].ra=Tree[rx(k)].ra;
  Tree[k].rt=Tree[lx(k)].rt+Tree[rx(k)].rt+(Tree[lx(k)].ra>Tree[rx(k)].la?T*(Tree[lx(k)].ra-Tree[rx(k)].la):-S*(Tree[rx(k)].la-Tree[lx(k)].ra));
}
```

区间修改只需要将包含的区间的 $a_l,a_r$ 修改，并打懒标记即可。时间复杂度 $\mathcal{O}(n+q\log n)$。

~~本作法可以支持区间询问。~~

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define f(i,j,n) for(int i=j;i<=n;i++)
#define F(i,n,j) for(int i=n;i>=j;i--)
#define updmax(a,b) a=max(a,b)
#define updmin(a,b) a=min(a,b)
#define pb push_back
using namespace std;
namespace fsd{
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin),p1==p2)?EOF:*p1++)
	const int MAXSIZE=1<<20;
	char buf[MAXSIZE],*p1,*p2;
	inline int read(){
		int ak=0,ioi=1;char c=gc();
		while(!isdigit(c)){if(c=='-')ioi=-1;c=gc();}
		while(isdigit(c))ak=ak*10+(c^48),c=gc();
		return ak*ioi;
	}
	inline string reads(){
		string o="";
		char p=gc();
		while(p>'z'||p<'a'){p=gc();}
		while(p<='z'&&p>='a'){o+=p;p=gc();}
		return o;
	}
	inline char readc(){
		char p=gc();
		while(!((p<='z'&&p>='a')||(p<='Z'&&p>='A'))){p=gc();}
		return p;
	}
	inline long double readd(){
		long double ak=0;int ioi=1;char c=gc();
		while(!isdigit(c)){if(c=='-')ioi=-1;c=gc();}
		while(isdigit(c))ak*=10,ak+=c-'0',c=gc();
		if(c=='.'){
			c=gc();
			long double q=0.1;
			while(isdigit(c))ak+=(c-'0')*q,q*=0.1,c=gc();
		}
		return ak*ioi;
	}
}
using namespace fsd;
const int N=2e5+10;
int a[N];
int n,Q,S,T;
struct Mst{
	struct abc{
		int lx,rx;
		int la,ra,rt,tg;
	}Tree[N*2];
#define lx(k) Tree[k].lx
#define rx(k) Tree[k].rx
#define mid ((l+r)>>1)
	int cnt=0;
	void build(int &k,int l,int r){
		k=++cnt;
		if(l==r){Tree[k].la=Tree[k].ra=a[l],Tree[k].rt=0;return;}
		build(lx(k),l,mid),build(rx(k),mid+1,r);
		pushup(k);
	}
	void pushup(int k){
		Tree[k].la=Tree[lx(k)].la,Tree[k].ra=Tree[rx(k)].ra;
		Tree[k].rt=Tree[lx(k)].rt+Tree[rx(k)].rt+(Tree[lx(k)].ra>Tree[rx(k)].la?T*(Tree[lx(k)].ra-Tree[rx(k)].la):-S*(Tree[rx(k)].la-Tree[lx(k)].ra));
	}
	void upd(int k,int v){
		Tree[k].la+=v,Tree[k].ra+=v,Tree[k].tg+=v;
	}
	void pushdown(int k){
		if(Tree[k].tg)upd(lx(k),Tree[k].tg),upd(rx(k),Tree[k].tg),Tree[k].tg=0;
	}
	void modify(int k,int L,int R,int v,int l,int r){
		if(L<=l&&r<=R){upd(k,v);return;}
		pushdown(k);
		if(L<=mid)modify(lx(k),L,R,v,l,mid);
		if(R>mid)modify(rx(k),L,R,v,mid+1,r);
		pushup(k);
	}
}_mst;
void gs(){
	n=read(),Q=read(),S=read(),T=read();
	f(i,0,n)a[i]=read();
	int rt;
	_mst.build(rt,0,n);
	f(i,1,Q){
		int l=read(),r=read(),v=read();
		_mst.modify(1,l,r,v,0,n);
		printf("%lld\n",_mst.Tree[1].rt);
	}
}
#define XQZ
signed main(){
#ifndef XQZ
	freopen("kaze.in","r",stdin);
	freopen("kaze.out","w",stdout);
#endif
#ifdef NXD
	int t=0;cin>>t;while(t--)
#endif
		gs();
	return 0;
}
```

---

## 作者：dingxiangqian (赞：2)

首先，根据题目我们可以看出，因为一开始的温度为 $0$，
所以位置 $n$ 的温度 $t_n=(t_1-t_0)+(t_2-t_1  )…(t_{n-1}-t_{n-2})$。也就是前面的温度差之和，结合需要区间修改操作，不难看出这题要用差分。


然后我们会发现，每次修改温度时，修改区间中间部分的温差和剩余部分其实是不变的，只会改变 $l$ 和 $r+1$ 两处的温度差，那么改变后的 $n$ 其实就很好求了，由于其他部分的温差不变，我们只需要减去原来 $l$、$r+1$ 的温度差，再把修改完后两处的新温度差加上就可以得到修改后的 $n$ 了。


好了，方法确定了，可是我们的差分数组该存什么那？

像我这样的蒟蒻第一反应是差分数组直接存温度之后根据输入的地形来修改差分数组。通过原数组来计算温差，并修改原数组，可如果这样的话，原数组的修改就容易导致 TLE 所以还要用差分数组存地形差。

可这样明显是画蛇添足，有地形差就足够我们通过给出的 $S$ 和 $T$ 推出温差了，之前的温差都已经累加进答案里了，也用不到存温差了。

由于每次修改和计算新的结果都是 $O(1)$ 的，所以解决问题的时间复杂度是 $O(n)$ 级别的，对于 $Q\le200000
$ 的范围足够了

那么到这里说的差不多了，上代码。

补一嘴：要看数据范围，估算一下发现累加后温差最大是 $2\times10^5\times({1\times10^{12}}-(-1)\times10^{12})$，会爆 int，要开 long long。


AC code:

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long//把 int 换成long long
int a[200010];
int d[200010];
int n,q,s,t;
int ans;
int cal(int b)//温差计算，带负号是可以把后面的温差处理简化
{
    if(b>0)return -b*s;
    else return -b*t;
}

signed main(){//main()函数不能用long long
	scanf("%lld%lld%lld%lld",&n,&q,&s,&t);
	for(int i=0;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
	    d[i]=a[i]-a[i-1];//一开始的地形差
	    ans+=cal(d[i]);//计算n的初值
	}
	for(int i=1;i<=q;i++)
	{
	    int l,r,c;
	    scanf("%lld%lld%lld",&l,&r,&c);
	    ans-=cal(d[l]);//左侧温差直接改
	    d[l]+=c;
	    ans+=cal(d[l]);//温差影响到n
	    if(r+1<=n)//右侧因为加一要检查越界
	    {
	        ans-=cal(d[r+1]);
	        d[r+1]-=c;
	        ans+=cal(d[r+1]);
	    }
	    printf("%lld\n",ans);
	}

	return 0;
}
```

---

## 作者：huangenning (赞：2)

该题解为本人第一篇题解，如有需改进的地方，请告诉我，谢谢！

### **部分分：**

对于 Subtask $1$：直接暴力即可。

对于 Subtask $2$：$a_n \times s$ 即为答案。

### **正解思路：**
本题频繁性对区间操作，很自然地我们会想到差分。

~~不过这题用不用差分都差不多，只是用差分代码更简洁。~~

由于最多有 $2 \times 10^5$ 天，所以计算每天的时间复杂度必须为 $O(1)$。我们可以想到：必须每次操作维护 $\text{ans}$，而不是完全依赖于差分数组。

对于每次操作的区间起点和终点：
1.  $\text{ans}$ 减去风改变的值。
2.  修改差分数组。
3.  $\text{ans}$ 加上现在风改变的值。

（如果终点小于 $n$ 可以不用处理终点）

所以其实这里差分数组唯一作用就是用更简洁的语言代替 $a_l-a_{l-1}$。

### **代码：**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int NR=200010;
int a[NR];
long long b[NR];
int main()
{
	int n,q,s,t,i;
	cin>>n>>q>>s>>t;
	long long ans=0;
	for(i=0;i<=n;i++)
	{
		cin>>a[i];
		if(i!=0) b[i]=a[i]-a[i-1];
		if(i!=0 && a[i]>a[i-1])	ans+=b[i]*(-s);
		else if(i!=0 && a[i]<a[i-1]) ans+=-b[i]*t; 
	}
	while(q--)
	{
		int l,r,x;
		cin>>l>>r>>x;
		if(b[l]>0) ans-=b[l]*(-s);
		else ans-=-b[l]*t;
		b[l]+=x;
		if(b[l]>0) ans+=b[l]*(-s);
		else ans+=-b[l]*t;
		if(r<n)
		{
			if(b[r+1]>0) ans-=b[r+1]*(-s);
			else ans-=-b[r+1]*t;
			b[r+1]-=x;
			if(b[r+1]>0) ans+=b[r+1]*(-s);
			else ans+=-b[r+1]*t;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
### **注意事项：**
在这里：

```cpp
if(b[l]>0) ans-=b[l]*(-s);
else ans-=-b[l]*t;
b[l]+=x;
```
$b_1$ 可能一开始为正（即 $a_l>a_{l-1}$），但后面可能让 $b_1$ 变为负，所以 $\text{ans}$ 必须先减后加。

---

## 作者：Sunset_afterglow (赞：2)

###### *本题解为蒟蒻而写，大佬勿喷

# 题目大意
每次将 $[l ,r]$ 之间的海拔加上一个 $k$，求操作后表达式 $$\sum_{i=1}^{n}f(i)$$ 的值，其中：
$$f(i)=\begin{cases} -(A_i - A_{i - 1}) \times t& {A_i < A_{i - 1}}\\0 & {A_i = A_{i - 1}}\\-(A_{i - 1} - A_i) \times s& {A_i > A_{i - 1}}\end{cases}$$
# 解题思路
这题在 $[l ,r]$ 加上一个 $k$，其实只有左右两个端点前后的差值发生了改变，直接维护差值，写个函数实现 $f(i)$，暴力修改，此题直接就切掉了，是不是很简单，代码如下。
# 代码部分
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int x = 0 ,f = 1;
	char ch = getchar();
	while('0' > ch || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch & 15);
		ch = getchar();
	}
	return x * f;
}
const int N = 2e5 + 5;
int n ,q ,s ,t ,a[N] ,answer ,val[N];
int f(int st) {
	if(st > n)return 0;
	if(a[st] < 0) return -a[st] * t;
	else return -a[st] * s;
}
signed main() {
	n = read() ,q = read() ,s = read() ,t = read();
	a[0] = read();
	for(int i = 1;i <= n;++ i) val[i] = read() ,a[i] = val[i] - val[i - 1];
	for(int i = 1;i <= n;++ i) answer += f(i);
	for(int j = 1 ,l ,r ,k;j <= q;++ j) {
		l = read() ,r = read() ,k = read();
		answer -= (f(l) + f(r + 1));
		a[l] += k ,a[r + 1] -= k;
		answer += (f(l) + f(r + 1));
		cout << answer << '\n';
	}
	return 0;
}
```
###### 都看完了，点个赞吧 QWQ

---

## 作者：封禁用户 (赞：2)

读完题，我们首先关注的是相邻地点的高度差。可以通过**差分数组**来表示相邻地点的高度差，即 `b[i] = a[i] - a[i + 1]`。然后，温度变化的贡献来自于这些高度差的变化。温度变化取决于高度差的正负，正值时温度上升，负值时温度下降。

每次操作会影响区间 $[L, R]$ 内的某些高度差，这些变化会影响温度的变化。我们只需要关心操作影响的区间两端的相邻高度差，从而计算它们的温度变化。

---

现在考虑具体实现：
1. 首先计算每对相邻地点的海拔差，并根据题目规则计算初始的温度总和。
2. 然后，通过差分数组来维护相邻地点的海拔差，只更新受影响的边界。
3. 每次操作时，只需要更新左右边界的相邻高度差，从而动态更新温度总和。

---

### Code
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    
    int N, Q, S, T;
    cin >> N >> Q >> S >> T;
    
    vector<long long> A(N + 1);
    for (int i = 0; i <= N; ++i) {
        cin >> A[i];
    }
    
    vector<long long> dif(N);
    long long sum = 0;
    
    // 初始化差分数组 dif 和温度总和 sum
    for (int i = 0; i < N; ++i) {
        dif[i] = A[i] - A[i + 1];
        sum += dif[i] > 0 ? dif[i] * T : dif[i] * S;
    }
    
    // 处理每次查询
    for (int q = 0; q < Q; ++q) {
        int L, R, X;
        cin >> L >> R >> X;
        
        // 更新 L 左边的差分
        if (L >= 1) {
            int i = L - 1;
            long long old = dif[i];
            sum -= old > 0 ? old * T : old * S;
            dif[i] -= X;
            long long now = dif[i];
            sum += now > 0 ? now * T : now * S;
        }
        
        // 更新 R 右边的差分
        if (R < N) {
            int i = R;
            long long old = dif[i]; 
            sum -= old > 0 ? old * T : old * S;
            dif[i] += X;
            long long now = dif[i];
            sum += now > 0 ? now * T : now * S;
        }
        
        // 输出当前温度总和
        cout << sum << '\n';
    }
    
    return 0;
}
```

---

## 作者：_luogu_huowenshuo_ (赞：1)

### 解析

一道差分题。

给定 $n$ 个地点，初始海拔 $A_i$，风从地点 $0$ 吹到 $n$，温度随海拔变化：下降 $1$ 米升温 $t$，上升 $1$ 米降温 $S$。有 $Q$ 次地壳运动，每次改变区间 $[L_j, R_j]$ 的海拔 $X_j$。用差分数组 ` d[i] = A[i] - A[i-1]`，计算初始温度 $ans$，每次更新 $d_l$、$d_{r+1}$，重新计算温度变化。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
long long n,q,s,t,a[200005],d[200005],ans;
long long w(long long x)
{
    if(x>0)return (-x*s);
    return (-x*t);
}
int main(){
	cin>>n>>q>>s>>t;
	for(int i=0;i<=n;i++)
	    cin>>a[i];
	for(int i=1;i<=n;i++)
	{
	    d[i]=a[i]-a[i-1];
	    ans+=w(d[i]);
	}
	while(q--)
	{
	    int l,r,x;
	    cin>>l>>r>>x;
	    ans-=w(d[l]);
	    d[l]+=x;
	    ans+=w(d[l]);
	    if(r<n)
	    {
	        ans-=w(d[r+1]);
	        d[r+1]-=x;
	        ans+=w(d[r+1]);
	    }
	    cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：wzy0 (赞：1)

观察题目，发现如果不考虑修改，显然可以 $O(n)$ 求出答案。 \
而答案只与高度差有关，修改又是区间修改，所以可以想到使用差分维护答案。

设 $b_i = a_{i-1} - a_i$，所以修改就变成了：
$$b_{l_i} \gets b_{l_i} - x_i , b_{r_i + 1} \gets b_{r_i + 1} + x_i$$

第 $i$ 点的贡献就变成了：
- 若 $b_i > 0$，则为 $b_i \cdot T$
- 若 $b_i < 0$，则为 $b_i \cdot S$

每次修改我们先去除 $l_i , r_i+1$ 两点带来的贡献； \
然后进行修改，再加回贡献。

这样就实现了时时维护答案，输出即可。 \
时间复杂度 $O(n+q)$，可以通过。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,q,s,t,a[200005],b[200005],z,l,r,x;

long long sz(long long i){
	if(b[i]>0){
		return b[i]*t;
	}else if(b[i]<0){
		return b[i]*s;
	}
	return 0;
}

int main(){
	ios::sync_with_stdio(0);cin.tie();cout.tie();
	cin>>n>>q>>s>>t;x=0;
	for(int i=0;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		b[i]=a[i-1]-a[i];
		z+=sz(i);
	}
	for(int i=1;i<=q;i++){
		cin>>l>>r>>x;
		z-=sz(l),z-=(r<n)*sz(r+1);
		b[l]-=x;b[r+1]+=x;
		z+=sz(l),z+=(r<n)*sz(r+1);
		cout<<z<<'\n';
	}
	return 0;
}
```

---

## 作者：AuCodingFrogHoward (赞：0)

## 算法
区间取加，考虑差分。
### 思路
因为区间操作较多，我们考虑在端点处进行维护。由此建立差分数组 $d$。设原数组为 $a$，则有：$d_i=a_i-a_{i-1}$。
### 复杂度
由于每次操作只在端点维护，故操作时间复杂度 $O(Q)$。

由于读入及预处理线性，故操作时间复杂度 $O(n)$。
### 实现
#### 预处理
在码中由于只维护差值，我们节省空间，弃原数组不用，在输入时改为用 $last$ 与 $now$ 两个变量维护，效果一样，请读者暂停思考片刻。
#### 操作
我们发现操作也是差分形式，所以由前文得，预处理部分先算出初始的魅力值，再于操作中多退少补即可。
### 拓展
差分与前缀和互逆。差分可以用来解决区间修改、单点求值问题。比如在 $[l,r]$ 区间中加上 $k$，可以转化为 $d_l=d_l+k$，再 $d_r+1=d_r+1-k$ 即可。
## 码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long d[200010];
long long n,q,s,t;
long long js(long long n)//多退少补
{
    if(n>0)
		return -s*n;
	else
		return -t*n;
}
int main(){
    long long last=0;
    long long ans=0;
    cin>>n>>q>>s>>t;
    for(int i=0;i<=n;i++)
	{
        long long now; 
        cin>>now;
        d[i]=now-last; 
        last=now;
        ans+=js(d[i]);
    }//预处理
    while(q--)
	{
        long long x,y,z;
        cin>>x>>y>>z;
        ans-=js(d[x]);//操作
        d[x]+=z; 
        ans+=js(d[x]); 
        if(y!=n)
        {
            ans-=js(d[y+1]);
            d[y+1]-=z;
            ans+=js(d[y+1]);
        }
        cout<<ans<<endl;
    }
    return 0;     
}
```
## 杂谈
完结撒花~~~

[望满足要求的大佬们加入敝团！\kel](https://www.luogu.com.cn/team/89818)

---

## 作者：ylch (赞：0)

## Description

给出 $N+1$ 个地点的海拔高度 $A_i$，编号为 $0 \dots N$。风从地点 $0$ 吹向地点 $N$，我们需要计算每次地壳运动后地点 $N$ 的风的温度。温度的变化规则如下：

- 如果 $A_i = A_{i+1}$，风的温度不变。
- 如果 $A_i > A_{i+1}$，由于海拔降低，风的温度会上升 $(A_i - A_{i+1}) \times T$ 度。
- 如果 $A_i < A_{i+1}$，由于海拔升高，风的温度会下降 $(A_{i+1} - A_i) \times S$ 度。

地壳运动会使得一段区间的海拔高度发生变化，我们需要高效地处理这些变化并计算每次变化后的温度。

## Analysis

为了高效处理每次地壳运动后的温度计算，我们可以利用**差分数组**来维护相邻地点之间的海拔差。具体思路如下：

1. **差分数组**：定义差分数组 $D$，其中 $D[i] = A[i+1] - A[i]$。

2. **温度贡献值**：

    对于每个差分值 $D[i]$，根据其正负情况计算温度变化的贡献值：
   - 如果 $D[i] < 0$，表示海拔下降，温度上升，贡献值为 $(-D[i]) \times T$。
   - 如果 $D[i] > 0$，表示海拔上升，温度下降，贡献值为 $(-S) \times D[i]$。


    总温度贡献值为所有差分值的贡献值之和。

3. **处理地壳运动**：

    每次地壳运动会改变一段区间的海拔值，发现在修改时的变化量会从 $l$ 开始，一直延伸直到 $r$，并随着位置后移不断累加。所以差分数组上， 我们只需调整该区间两端点的差分值，并更新温度的总贡献值。

   
   具体来说，对于区间 $[l, r]$，海拔变化 $x$，我们只需更新 $D[l-1]$ 和 $D[r]$：
    - $D[l-1] \leftarrow D[l-1] + x$
    - $D[r] \leftarrow D[r] - x$

    每次更新后，重新计算这两个差分值的贡献值，并更新总温度贡献值。

总时间复杂度为 $O(N + Q)$。

为了方便实现，这里数组下标和题目统一，从 $0$ 开始。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 7;

int n, q, s, t;
ll a[maxn], d[maxn];

// 计算贡献
ll get(int i){
	if(d[i] < 0) return (-d[i]) * t;
	else return (-s) * d[i];
}

void solve()
{
	cin >> n >> q >> s >> t;
	for(int i = 0; i <= n; i ++){ // 注意输入有n+1个数
		cin >> a[i];
	}
	for(int i = 0; i < n; i ++){
		d[i] = a[i + 1] - a[i];
	}
	
	// 计算初始贡献
	ll ans = 0;
	for(int i = 0; i < n; i ++){
		ans += get(i);
	}
	
	// 处理询问
	while(q --){
		int l, r, x; cin >> l >> r >> x;
		
		// 左侧
		if(l - 1 >= 0){ // 注意边界
			ans -= get(l - 1); // 删去旧的贡献
			d[l - 1] += x; // 改差分数组
			ans += get(l - 1); // 加上新的贡献
		}
		
		// 右侧
		if(r < n){
			ans -= get(r);
			d[r] -= x;
			ans += get(r);
		}
		
		cout << ans << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：__Accepted_ZYF__ (赞：0)

考虑维护前缀和。

首先，我们按照题意即可求出初始温度 $tpr$。

接着，在每一次更新后，我们考虑动态维护当前点 $n$ 的温度。

首先是左端点。

我们首先要把原先的温度记录清空，$tpr\to tpr-f(d_l)$，这里 $f(x)$ 表示高度变化的温度贡献。

然后加回去，$tpr\to tpr+f(d_l+x)$。

注意要对 $d_l$ 也修改。

对于右端点操作同理。

注意：当 $r+1>n$，我们修改的前缀和是无法影响 $n$ 温度的，那么不要修改。

最后输出即可。

---

[双倍经验](https://www.luogu.com.cn/problem/AT_joi2017ho_a)。

---


```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
const int N=2e5+10;
int n,Q,S,T,a[N],d[N],L,R,x;
int get(int x){
	if(x<0)return -x*T;
	else return -x*S;
}
signed main(){
	cin>>n>>Q>>S>>T;
	int tpr=0;
	for(int i=0;i<=n;i++){
		cin>>a[i];if(i==0)continue;
		d[i]=a[i]-a[i-1];
		tpr+=get(d[i]);
	}
	while(Q--){
		cin>>L>>R>>x;
		tpr-=get(d[L]);tpr+=get(d[L]+x);
		d[L]+=x;
		if(R+1>n){cout<<tpr<<endl;continue;}
		tpr-=get(d[R+1]);tpr+=get(d[R+1]-x);
		d[R+1]-=x;
		cout<<tpr<<endl;
	}
	return 0;
}
```

---

