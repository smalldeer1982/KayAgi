# Messages

## 题目描述

Monocarp 是 $n$ 个学生的导师。现在有很多条消息，Monocarp 希望第 $i$ 个学生阅读编号为 $m_i$ 的消息。他需要把一些消息置顶，因为学生只会阅读置顶的消息。

学生 $i$ 有一个属性 $k_i$。如果你置顶了 $t$ 条消息，若 $t\le k_i$，该学生会阅读所有置顶消息；否则，该学生会从置顶的 $t$ 条消息中随机选 $k_i$ 条阅读。

你需要求出在使得第 $i$ 名学生阅读到第 $m_i$ 条消息的 $i$ 的数量的期望值最大时，你应该置顶哪些消息。如果有多个答案，输出任意一种。

## 样例 #1

### 输入

```
3
10 1
10 2
5 2```

### 输出

```
2
5 10```

## 样例 #2

### 输入

```
3
10 1
5 2
10 1```

### 输出

```
1
10```

## 样例 #3

### 输入

```
4
1 1
2 2
3 3
4 4```

### 输出

```
3
2 3 4```

## 样例 #4

### 输入

```
3
13 2
42 2
37 2```

### 输出

```
3
42 13 37```

# 题解

## 作者：DaiRuiChen007 (赞：8)

# CF1612E - Messages 题解

## 题目大意

给定 $n$ 名学生，你希望通知第 $i$ 名学生第 $m_i$ 条消息，你可以用置顶其中的 $t$ 条的方式通知他们。

不过每个人有一个懒惰值 $k_i$，他们只会随机阅读 $t$ 条置顶消息中的 $\min(k_i,t)$ 条。

现在请你以某一种置顶消息的方法，使得阅读到对应消息的学生人数尽可能多，输出这种方法即可。

数据范围保证：$k_i\le20,n\le2\times10^5,m_i\le2\times10^5$。

## 思路分析

约定：$w=\max_{i=1}^n m_i\le2\times10^5$，$\mathbb{M}$ 表示所有置顶消息的集合。

分析题意，也就是使得式子 $\sum_{m_i\in\mathbb{M}}\dfrac{\min(k_i,t)}{t}$ 最大化。

先考虑 $t$ 值已知的情况，那么这个时候只需要使得所有被选消息的 $k_i$ 之和最大，显然直接贪心，对于每一个 $m_i$ 的值记录其对应的 $k_i$ 值之和，然后选取 $k_i$ 之和最大的前 $t$ 个即可。

接下来考虑 $t$ 的取值范围，注意到 $\forall i\in[1,n],k_i\le20$ 这个特殊的条件，于是大胆猜想可能成为答案的 $t$ 一定满足 $1\le t\le 20$。

这个结论是正确的，证明如下：


> 证：

>记 $b$ 表示按 $k_i$ 值之和降序排列后的数组，$ans_v$ 表示 $t=v$ 时的最优解。
>$\because \forall i\in[1,n],k_i\le20$

>$\therefore \forall i\in[1,n],\min(k_i,20)=k_i=\min(k_i,21)$

>所以 $t=20$ 时的 $b$ 数组和 $t=21$ 时的 $b$ 数组是完全相同的。

>$\therefore \begin{cases}ans_{20}=\frac{1}{20}\sum_{i=1}^{20}b_i\\ans_{21}=\frac{1}{21}\sum_{i=1}^{21}b_i\end{cases}$

>$\therefore ans_{20}-ans_{21}=\dfrac{1}{21}\left[\dfrac{1}{20}\left(\sum_{i=1}^{20}b_i\right)-b_{21}\right]$

>$\therefore ans_{20}-ans_{21}=\dfrac{1}{420}\sum_{i=1}^{20} \left(b_i-b_{21}\right)$

>$\therefore ans_{20}\ge ans_{21}$

>同理可证 $ans_{21}\ge ans_{22}\ge \dots\ge ans_w$。

>所以最优解一定在 $ans_1\sim ans_{20}$ 之中。

>证毕。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int k[MAXN],m[MAXN];
struct BucketNode {
	//统计每一个m[i]对应的k[i]之和的桶 
	int val,id;
	//val记录k[i]之和的值，id记录m[i]的值 
	inline friend bool operator <(const BucketNode &x,const BucketNode &y) {
		//按k[i]的和降序排序 
		return x.val>y.val;
	}
}	b[MAXN];
inline BucketNode mp(int val,int id) {
	//用val值和id值构造一个BucketNode 
	BucketNode ans;
	ans.val=val,ans.id=id;
	return ans;
}
struct DataNode {
	//记录答案 
	vector <int> vec; //vec记录置顶了哪些 
	double val; //val记录所求期望 
	inline void clear() {
		val=0;vec.clear();
	}
}	ans,tmp; //ans是答案,tmp是临时记录 
signed main() {
	int n;
	scanf("%d",&n);
	for(register int i=1;i<=n;++i) scanf("%d%d",&m[i],&k[i]);
	for(register int t=1;t<=20;++t) {
		//枚举1~20中的每一个t值 
		for(register int i=0;i<MAXN;++i) b[i]=mp(0,i); //初始化 
		for(register int i=1;i<=n;++i) b[m[i]].val+=min(t,k[i]); //放进桶 
		sort(b+1,b+MAXN+1); //排序 
		tmp.clear();
		for(register int i=1;i<=t;++i) {
			//贪心，选和最大的 
			tmp.val+=b[i].val;
			tmp.vec.push_back(b[i].id);
		}
		tmp.val/=t;
		if(tmp.val>ans.val) ans=tmp; //更新答案 
	}
	//输出 
	printf("%d\n",ans.vec.size());
	for(register int i:ans.vec) printf("%d ",i);
	putchar('\n');
	return 0;
}
```



---

## 作者：401rk8 (赞：4)

随便写了写就最优解 rk1 了，水篇题解

---

对于选出的 $t$ 个数 $c_{1},\cdots,c_{t}$，它的期望值为 $\displaystyle\sum_{i=1}^{n}[\exists j,m_{i}=c_{j}]\frac{\min(k_{i},t)}{t}$，不难发现每个数的贡献独立，可以枚举 $t$，用桶统计出每个数的贡献（即 $\sum_{i=1}^{n}[\exists j,m_{i}=c_{j}]\min(k_{i},t)$），取前 $t$ 大。

继续思考，由 $\forall k_{i}\le20$ 得最优解的 $t\le20$  
证明：$t\ge20$ 时 $\min(k_{i},t)=k_{i}$，因此 $t$ 增大时每个数的贡献不变，原来选的数一定还选。记第 $20,21$ 大的贡献为 $f_{20}\ge f_{21}$，$t=i$ 的答案为 $ans_{i}$，则有 $ans_{21}=\frac{20}{21}ans_{20}+\frac{f_{21}}{21}$，由于 $f$ 不增，有 $ans_{21}\le ans_{20}$，$t>21$ 同理。

实现上，找出前 $t$ 大的数不需要 `sort`，`nth_element` 即可。时间复杂度 $O(20n)$

[code](https://codeforces.com/contest/1612/submission/137077516)

---

## 作者：ExplodingKonjac (赞：4)

### [**【原题链接】**](http://topurl.cn/9Jd)

写一种考场想到，但是没写的奇怪的不依赖 $k_i$ 的三分做法。。

## 题目分析

首先发现如果没有确定 $t$ 的话不太好搞，所以我们假设我们已经确定了一个 $t$。

然后我们发现，置顶每种消息对答案的贡献都可以算出来（$\displaystyle E_x=\sum_{m_i=x}\frac{\min(k_i,t)}{t}$），所以我们可以贪心地选取贡献最大的 $t$ 个消息。

然后考虑怎么确定 $t$。

我们发现当 $t$ 增大时，会给更多的学生“创造机遇”，但是分母却变大了。我们知道，一个增长的趋势加上一个减小的趋势，多半是一个有凹凸性的东西。

所以我们可以三分答案。然后。。

![](https://cdn.luogu.com.cn/upload/image_hosting/69nm4m9x.png)

因为这个函数并不是单峰的，只用三分不能通过本题。

这应该是一个常用的 trick：设定一个阈值 $lmt$，当三分时确定的区间长度小于这个阈值时，我们对区间中暴力统计答案，貌似比较难卡 ~~（而且还可以通过 $\sout\text{CSP-S 2021 T1}$）~~。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
省略一百多行的快读快写模板
即下文的qin、qout。
*/

int n,ans[200005],a[200005],b[200005];
double sum[200005];
bool pin[200005],vis[200005];
double check(int t)
{
	vector<int> vec;
	double res=0;
	memset(sum,0,sizeof(sum));
	memset(pin,0,sizeof(pin));
	for(int i=1,j=0;i<=n;i++)
	{
		int x=a[i];
		if(!pin[x])	vec.push_back(x),pin[x]=true;
		sum[x]+=(double)min(b[i],t)/t;
	}
	sort(vec.begin(),vec.end(),[](int x,int y){ return sum[x]>sum[y]; });
	for(int i=0;i<t;i++)
		res+=sum[vec[i]],ans[i+1]=vec[i];
	return res;
}
int main()
{
	int l=1,r=0,lmid,rmid;
	qin>>n;
	for(int i=1;i<=n;i++)
	{
		qin>>a[i]>>b[i];
		if(!vis[a[i]])	vis[a[i]]=true,r++;
	}
	while(r-l>10)
	{
		lmid=l+(r-l)/3,rmid=r-(r-l)/3;
		(check(lmid)>check(rmid))?(r=rmid-1):(l=lmid+1);
	}
	double maxx=check(l),now;
	for(int i=l+1;i<=r;i++)
		if((now=check(i))>maxx)
			l=i,maxx=now;
	check(l);
	qout.writeln(l);
	for(int i=1;i<=l;i++)	qout.writesp(ans[i]);
//	return qout.flush(),0;
}

```


---

## 作者：AFewSuns (赞：4)

### 题目大意

有 $n$ 个人，每个人希望看到第 $m_i$ 条信息。你可以选若干条信息，使得被满足的人数期望尽可能大。

一个人被满足意味着他看到了自己希望看到的消息。

假设你选择了 $t$ 条消息。每个人有一个系数 $k_i$，当 $k_i \geq t$ 时，这个人会看所有的 $t$条消息，否则会等概率地从这 $t$ 条消息选择 $k_i$ 条消息看。

### 题目分析

假设第 $i$ 个人想看到的消息在这 $t$ 条消息中，那么分两种情况：

1. $k_i \geq t$，它的期望是 $1$。

1. $k_i < t$，它的期望是 $\frac{k_i}{t}$（显然）。

忽略掉若干细节，粗略地想一想，要让期望被满足的人数越多，就要让 $\sum{\frac{k_i}{t}}$ 越大。在 $t$ 确定的情况下，也就是要让 $\sum k_i$ 越大。

将每个 $m_i$ 开一个桶，然后把所有 $m_i$ 相同的的 $k_i$ 加起来。因为当 $m_i$ 被选之后，这些人都会被算进答案。将这些数按照 $k_i$ 的和从大到小排序，然后选前 $t$ 个数就行了。

关键来了，第一种情况，$k_i$ 再怎么大，它的期望只可能是 $1$，单纯加起来答案会错。怎么办呢？

观察到 $k_i \leq 20$，可以在 $t \in [1,20]$ 的时候暴力算，额外开一个桶。然后 $t > 20$ 的时候，按照上面的方法进行计算，将得到的期望取最大值即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fr(i,x,y) for(register ll i=(x);i<=(y);i++)
using namespace std;
ll n,m[200020],k[200020],t,ans[200020];
double maxx=0;
struct node{
	ll id,cnt;
}a[200020],b[22][200020];//a为t>20的桶，b为t<=20的桶 
bool cmp(node x,node y){
	return x.cnt>y.cnt;
}
void solve(){
	fr(i,1,min(20ll,n)){//前20暴力计算 
		ll res=0;
		fr(j,1,i) res+=b[i][j].cnt;
		if(maxx<1.0*res/i){//更新答案 
			t=i;
			maxx=1.0*res/i;
		}
	}
	ll res=0;
	fr(i,1,min(20ll,n)) res+=a[i].cnt;
	fr(i,21,n){
		res+=a[i].cnt;
		if(maxx<1.0*res/i){
			t=i;
			maxx=1.0*res/i;
		}
	}
}
int main(){
	scanf("%lld",&n);
	fr(i,1,200000) a[i].id=i;
	fr(i,1,200000) fr(j,1,20) b[j][i].id=i;
	fr(i,1,n){
		scanf("%lld %lld",&m[i],&k[i]);
		a[m[i]].cnt+=k[i];
		fr(j,1,20) b[j][m[i]].cnt+=min(j,k[i]);//将ki加进mi的桶里 
	}
	sort(a+1,a+200001,cmp);
	fr(i,1,20) sort(b[i]+1,b[i]+200001,cmp);
	solve();
	printf("%lld\n",t);
	if(t<=20){//注意判断，t<=20的时候用的是b 
		fr(i,1,t) ans[i]=b[t][i].id;
	}
	else{
		fr(i,1,t) ans[i]=a[i].id;
	}
	fr(i,1,t) printf("%lld ",ans[i]);
}
```

---

## 作者：_RainCappuccino_ (赞：1)

> $\mathtt{TAGS}$：期望，枚举

# First. 答案的范围

贪心地想，对于最终选取的数量 $K$，如果其 $>\max_i^n k_i$，那么所有人都不会一定读到某条消息，那么肯定不优于 $K = \max_i^n k_i$ 的情况。所以 $K \le \max_i^n k_i$。又因为 $k_i \le 20$ 所以 $K \le 20$。

# Second. 枚举

由于 $K$ 很小，不妨考虑枚举 $K$。

对于 $K$，设选取的 $K$ 条消息为 $\{ a_1,a_2,\dots,a_K\}$，那么期望值为：$\sum_{i = 1} ^ K \sum_{j = 1}^{n}\frac{\min(k_j,K)}{K} [m_j = a_i]$。

设每条消息的代价 $val_i$ 为 $ \sum_{j = 1}^{n}\frac{\min(k_j,K)}{K} [m_j =i]$，贪心地想，选取代价大的消息肯定最终期望越大。

那么可以先处理出每条消息的代价，然后取前 $K$ 大的消息即可。

那么，最终取期望最大值最大的 $K$ 为答案即可。

# Tips

1. 处理消息代价的时候，先不 $\div k$，在求完和后再 $\div k$。
2. 处理消息代价，可以枚举每个学生，将其 $\max(K, k_i)$ 的值加在 $val_{m_i}$ 上即可。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
char buf[1 << 23] , * p1 = buf , * p2 = buf , obuf[1 << 23] , * O = obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() {
	int x = 0 , f = 1;char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1;ch = getchar(); }
	while (isdigit(ch)) x = x * 10 + (ch ^ 48) , ch = getchar();
	return x * f;
}
typedef long long ll;
typedef pair<int, int> pi;
const int N = 2e5 + 10;
int n;
vector<int> num[N];
int m[N], k[N];
pi sum[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) {
		cin >> m[i] >> k[i];
		num[m[i]].push_back(k[i]);
	}
	double ans = 0;
	vector<int> res;
	for (int kk = 1; kk <= 20; kk ++) {
		for (int i = 1; i <= 2e5; i ++) {
			sum[i].first = 0, sum[i].second = i;
			for (auto x : num[i]) sum[i].first += min(kk, x);
		}
		sort(sum + 1, sum + 1 + 200000, greater<pi>());
		int cnt = 0;
		for (int i = 1; i <= kk; i ++) {
			cnt += sum[i].first;
		}
		double p = cnt / (kk * 1.0);
//		cout << p << ' ' << cnt << endl;
		if(p > ans) {
			ans = p;
			res.clear();
			for (int i = 1; i <= kk; i ++) {
				res.push_back(sum[i].second);
			}
		}
	}
	cout << res.size() << endl;
	for (auto x : res) cout << x << ' ';
	return 0;
}
```

---

## 作者：bsdsdb (赞：0)

题意：给你序列 $\{m_n\}$ 和 $\{k_n\}(k_i\le 20)$，你需要给出集合 $S$ 以最大化：

$$
f(S):=\sum_{i=1}^{n}
\begin{aligned}\begin{cases}
1,\qquad&m_i\in S\land |S|\le k_i\\
\frac{k_i}{|S|},\qquad&m_i\in S\land |S|>k_i\\
0,\qquad&\text{otherwise}.
\end{cases}\end{aligned}
$$

提示：

1. 答案函数是以 $\sum_{i=1}^{n}$ 的视角定义的，试着将其改成以 $\sum_{i\in S}$ 开头的形式，可以利用 $\sum_{m_j=i}$ 和 $|S|$.
2. 试着通过遍历 $|S|$ 得到一个 $O(n^2\log n)$ 的解法。
3. 当 $|S|\ge\max \{k\}$ 时，往 $S$ 里加入一个元素，答案如何变化？
4. 如何利用以上结论改进算法？

（提示 1 解答）注意到

$$
f(S)=\dfrac{\sum_{i\in S}\sum_{m_j=i}\min(k_j,|S|)}{|S|}\\
$$

简化：

$$
g(x,t):=\sum_{m_j=x}\min(k_j,t)\\
\Rightarrow f(S)=\dfrac{\sum_{i\in S}g(i,|S|)}{|S|}
$$

（提示 2 解答）当我们固定 $|S|=t$ 时，可以对于每个 $i\in\{m\}$ 求出 $g(i,t)$，对这些值进行大到小排序即可求出 $\max_{|S|=t}f(S)$。提示 3 解答）但是可以注意到，当我们知道了 $f(S)$ 时有：

$$
\forall |S|\ge\max\{k\},|S'|=|S|+1,S\subset S',i\le n:\\
g(i,|S'|)\xlongequal{k_j\le|S|\Rightarrow\min(k_j,|S|)=\min(k_j,|S|+1)=\min(k_j,|S'|)}g(i,|S|)\\
\begin{aligned}
\Rightarrow f(S')=&\dfrac{\sum_{i\in S}g(i,|S'|)}{|S'|}\\
=&\dfrac{\sum_{i\in S}g(i,|S|)}{|S|+1}\\
=&f(S)\cdot\dfrac{|S|}{|S|+1}\\
<&f(S)
\end{aligned}
$$

（提示 4 解答）所以我们可以将 $|S|$ 的遍历上界从 $n$ 改为 $\max\{k\}$，算法时间复杂度变为 $\mathcal O(n\max\{k\}\log n)$。

---

