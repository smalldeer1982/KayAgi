# [ARC045B] ドキドキデート大作戦高橋君

## 题目描述

# 高桥君的心跳约会大作战

高桥君在读的学校即将进行一次大扫除。学校中有N个教室，分别编号为 $1,2,3, \dots ,N$ 。这些教室排成了一排。

高桥君的学校中共有含高桥君在内的 $M$ 个学生，需要扫除的连续教室区间（称为扫除区间）有 $M$ 个。但是，还没有决定由哪个学生来负责哪个扫除区间。不同的学生负责不同的扫除区间，每个学生必须打扫被分配到的所有教室。 $1$ 个教室可能被多个扫除区间包含。

高桥君突然发现，大扫除当天他正好与女同学有约会。无论怎么样高桥君都不想毁掉这次约会，所以只能把大扫除翘掉了。但是高桥君很在意自己会不会暴露：高桥君负责的教室中如果有任何教室没有被打扫，高桥君就会暴露。

你的任务是：替高桥君找出就算翘掉扫除也不会暴露的所有扫除区间。

另外，这所学校里的学生们都非常勤奋努力，故假定除高桥君外的所有人都不会缺席大扫除。

## 样例 #1

### 输入

```
10 5
1 4
5 5
6 8
9 10
5 6```

### 输出

```
2
2
5```

## 样例 #2

### 输入

```
3 6
1 1
1 1
2 2
2 2
3 3
3 3```

### 输出

```
6
1
2
3
4
5
6```

## 样例 #3

### 输入

```
10 3
1 4
2 6
6 10```

### 输出

```
0```

# 题解

## 作者：紫题 (赞：4)

题意：给出m个区间，求有多少个区间能被其他区间完全覆盖

将所有区间按照左端点排序，以贪心的方法扫一遍，就能找到没有被其他区间完全覆盖的区间了

既然你能找到这题，我相信你能瞬间做出来的

$Code:$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct w{int id,l,r;}e[100010];
bool cmp(w a,w b){return a.l<b.l;}
int a[300010],n,m,cpr,cpr_l,sum;
bool vis[100010];
int main(){
	scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&e[i].l,&e[i].r);
        e[i].id=i;
    }
    sort(e+1,e+m+1,cmp);
    cpr=1,cpr_l=e[1].l;
    for(int i=2;i<=m;i++){
        if(e[i].l>cpr_l) if(!vis[e[cpr].id]){sum++;vis[e[cpr].id]=1;}
        if(e[i].r>e[cpr].r){
            cpr_l=max(cpr_l,e[cpr].r+1);
            cpr=i;
        }
        else cpr_l=max(cpr_l,e[i].r+1);
    }
    if(cpr_l<=e[cpr].r) if(!vis[e[cpr].id]){sum++;vis[e[cpr].id]=1;}
    printf("%d\n",m-sum);
    for(int i=1;i<=m;i++) if(!vis[i]) printf("%d\n",i);
    return 0;
}

```

---

## 作者：朱屹帆 (赞：2)

### AT1504 ドキドキデート大作戦高橋君

>题目大意：给定 $m$ 个区间，求当 $1$ 个区间消失时，它所包含的区间的每一个元素仍被其他区间包含的区间的个数。

其实这一题并不难，由题可以知道，当一个区间满足要求，当且仅当这一个区间的每一个元素至少被两个区间覆盖，由此，我们可以想到将区间内的元素都加 $1$ ，用线段树维护区间加，求区间最小值，若该区间最小值为 $1$ ，则说明该区间内有元素只被这一区间所覆盖，不满足条件，反之，则统计答案。

再看题面，我们又可以发现，该题的区间修改是放在一起的，所以我们又可以想到用差分 $O(1)$ 的修改，在一次求出原序列，再用 $ST$ 表去维护区间最小值即可，本质和线段树是一样的。

另外，这一题的样例三有误，输出应为 ```0``` ，并非无输出，否则会在第三个点答案错误。

#### 输入 #3
```
10 3
1 4
2 6
6 10
```
#### 输出 #3
```
0
```

#### 线段树代码：
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define inf 0x7FFFFFFF
#define LL long long
#define endl '\n'
using namespace std;
long long read(){
	long long q=0,w=1;
	char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){q=q*10+(ch-'0');ch=getchar();}
	return q*w;
} //快读
namespace Seg_tree{ //线段树
	const long long N = 3e5+95;
	struct Node{
		LL l,r,dat;
		LL lazybag;
	}s[N<<3];
	void Build(LL p,LL l,LL r){
		s[p].l=l;s[p].r=r;s[p].dat=0;
		if(l==r)return ;
		LL mid=((l+r)>>1);
		Build(p*2,l,mid);
		Build(p*2+1,mid+1,r);
		return ;
	}
	void Pushdown(LL p){
		if(s[p].l==s[p].r){
			s[p].lazybag=0;
			return ;
		}
		s[p*2].lazybag+=s[p].lazybag;
		s[p*2].dat+=s[p].lazybag;
		s[p*2+1].lazybag+=s[p].lazybag;
		s[p*2+1].dat+=s[p].lazybag;
		s[p].lazybag=0;
		return ;
	}
	void Updata(LL p,LL l,LL r,LL x){
		Pushdown(p);
		if(l<=s[p].l && s[p].r<=r){
			s[p].dat+=x;
			s[p].lazybag+=x;
			return ;
		}
		LL mid=((s[p].l+s[p].r)>>1);
		if(l<=mid)Updata(p*2,l,r,x);
		if(mid<r)Updata(p*2+1,l,r,x);
		s[p].dat=min(s[p*2].dat,s[p*2+1].dat);
		return ;
	}
	LL Query(LL p,LL l,LL r){
		Pushdown(p);
		if(s[p].r<l || r<s[p].l)return inf;
		if(l<=s[p].l && s[p].r<=r)return s[p].dat;
		LL mid=((s[p].l+s[p].r)>>1);
		return min(Query(p*2,l,r),Query(p*2+1,l,r));
	}
}
const long long N = 3e5+95;
long long n,m,l[N],r[N],cnt;
vector<long long>ans;
int main(){
	n=read();m=read();
	Seg_tree::Build(1,1,n); //构建线段树
	for(LL i=1;i<=m;i++){
		l[i]=read();r[i]=read();
		Seg_tree::Updata(1,l[i],r[i],1); //区间修改
	}
	for(LL i=1;i<=m;i++){
		LL step=Seg_tree::Query(1,l[i],r[i]); //区间求最小值
		if(step!=1){ //满足条件
			cnt++;ans.push_back(i);
		}
	}
//	if(cnt==0)return 0; 
	cout<<cnt<<endl; //一定要输出才可以
	for(LL i=0;i<cnt;i++)
		cout<<ans[i]<<endl; //输出所有合法答案
	return 0;
}
```
#### 差分 $+$ ST表代码：
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define inf 0x7FFFFFFF
#define LL long long
#define endl '\n'
using namespace std;
long long read(){
	long long q=0,w=1;
	char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){q=q*10+(ch-'0');ch=getchar();}
	return q*w;
}//快读
const long long N = 3e5+95;
long long n,m,l[N],r[N],cnt;
vector<long long>ans;
long long cha[N],s[N];
struct ST{ //ST表
	long long dp[N][21];
	void Init(LL n){ //预处理
		LL len=log(n)/log(2);
		for(LL i=1;i<=n;i++)dp[i][0]=s[i];
		for(LL i=1;i<=len;i++)
			for(LL j=1;j<=n-(1<<i)+1;j++)
				dp[j][i]=min(dp[j][i-1],dp[j+(1<<(i-1))][i-1]);
		return ;
	}
	LL Ask(LL l,LL r){//查询最小值
		LL len=log((r-l+1))/log(2);
		return min(dp[l][len],dp[r-(1<<len)+1][len]);
	}
}st;
int main(){
	n=read();m=read();
	for(LL i=1;i<=m;i++){
		l[i]=read();r[i]=read();
		cha[l[i]]++;cha[r[i]+1]--; //差分操作
	}
	for(LL i=1;i<=n;i++)s[i]=(s[i-1]+cha[i]); //求出原序列
	st.Init(n); //ST表提前预处理最小值
	for(LL i=1;i<=m;i++){
		if(st.Ask(l[i],r[i])>=2){ //满足条件
			cnt++;ans.push_back(i);
		}
	}
	cout<<cnt<<endl;
	for(LL i=0;i<cnt;i++)
		cout<<ans[i]<<endl; //输出所有合法答案
	return 0;
}
```

---

## 作者：JasonL (赞：2)

看到没有用打标记的就来发题解了

 _AC 1.24s_ 

------------

本题大意是快速查询区间是否覆盖一个**不被其他区间覆盖的教室**，

首先使用区间标记可以快速找到这样的独立的教室。从首到尾扫一遍标记，当统计的覆盖区间个数为1时把教室标记下来。

那么如何查询区间是否覆盖这些教室呢？显然，如果区间左端在教室左边，区间右端在教室右边，必然覆盖该教室。我们如果能将每个位置对应的前一个独立教室位置标记下来，就能在O(1)内确定是否覆盖了。

于是我们在扫标记时，每次当碰到满足条件的教室时将前一个教室的位置更新，并记录在该教室对应的数组位置上。（可以不用bool了）

最后确定区间左端的位置是否大于区间右端指向的前一个教室，将其统计后丢进输出序列里。

时间复杂度O(n+m).

```cpp
#include<iostream>
#include<cstring> 
#include<queue>
using namespace std;
int n,m,room[300100];
struct bet{
	int l,r;
} zone[100100];
queue <int> ansq;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>zone[i].l>>zone[i].r;
		room[zone[i].l]++;
		room[zone[i].r+1]--;
	}
	int cnt=0,pos=0,ans=0;	//查找仅被一个区间覆盖的教室,同时标记该位置对应的前一个满足条件的教室 
	for(int i=1;i<=n;i++){
		cnt+=room[i];
		if(cnt==1)	pos=i;
		room[i]=pos;	//使用完标记后可以循环使用（可回收垃圾） 
	}
	for(int i=1;i<=m;i++)
		if(room[zone[i].r]<zone[i].l)	//是否覆盖前一个教室 
		{
			ans++;ansq.push(i);		//放进输出队列 
		}
	cout<<ans<<endl;
	while(ansq.size()){
		cout<<ansq.front()<<endl;
		ansq.pop();
	}
	return 0;
}
```


---

## 作者：Dilute (赞：2)

## 身败名裂

这么一道题目我竟然还交了两发……

不想写正常解法

于是就极其无聊地写了个线段树

（连我自己都感叹我为什么这么大材小用）

~~（可能就适合我这种头脑简单的无脑选手吧QwQ）~~

显然，我们只需要写一棵资瓷区间修改与区间最小值的线段树就行了

我们首先把每个区间在线段树上都+1

然后我们在查询一个扫除区间是否合法的时候，我们只需将这个区间集体-1，如果这个区间的$\min$值为0，那么代表这个区间不合法，否则则合法QwQ

上代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647
#define lc(a) (a << 1)
#define rc(a) (a << 1 | 1)

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

struct SEG_Tree{
    struct SEG{
        int l;
        int r;
        int min;
        int lazy;
    }t[10000000];

    void push_up(int cur){
        t[cur].min = std::min(t[lc(cur)].min, t[rc(cur)].min);
    }

    void push_down(int cur){
        t[lc(cur)].min += t[cur].lazy;
        t[rc(cur)].min += t[cur].lazy;
        t[lc(cur)].lazy += t[cur].lazy;
        t[rc(cur)].lazy += t[cur].lazy;
        t[cur].lazy = 0;
    }

    void build(int cur, int l, int r){
        t[cur].l = l;
        t[cur].r = r;
        t[cur].lazy = 0;
        t[cur].min = 0;
        if(l == r)
            return ;
        int mid = (l + r) >> 1;
        build(lc(cur), l, mid);
        build(rc(cur), mid + 1, r);
    }

    void modify(int cur, int l, int r, int c){
        // printf("%d ", cur);
        push_down(cur);
        if(t[cur].r < l || t[cur].l > r)
            return ;
        if(t[cur].l >= l && t[cur].r <= r){
            t[cur].min += c;
            t[cur].lazy += c;
            return ;
        }
        modify(lc(cur), l, r, c);
        modify(rc(cur), l, r, c);
        push_up(cur);
    }

    int query(int cur, int l, int r){
        push_down(cur);
        if(t[cur].r < l || t[cur].l > r)
            return INF;
        if(t[cur].l >= l && t[cur].r <= r)
            return t[cur].min;
        return std::min(query(lc(cur), l, r), query(rc(cur), l, r));
    }
}t;

int ans[300010];
int l[300010];
int r[300010];
int cnt = 0;

int main(){
    int n = inp();
    int m = inp();
    for(int i = 1; i <= m; i++){
        l[i] = inp();
        r[i] = inp();
    } 
    t.build(1, 1, n);
    for(int i = 1; i <= m; i++)
        t.modify(1, l[i], r[i], 1);
    for(int i = 1; i <= m; i++){
        t.modify(1, l[i], r[i], -1);
        if(t.query(1, l[i], r[i]) != 0)
            ans[++cnt] = i;
        t.modify(1, l[i], r[i], 1);
    }
    printf("%d\n", cnt);
    for(int i = 1; i <= cnt; i++)
        printf("%d\n", ans[i]);
}
```



---

## 作者：joker_opof_qaq (赞：1)

差分加前缀和。

## 题意简述

给出 $m$ 个区间，求有多少个区间能被其他区间完全覆盖。

先用差分求出这个点被覆盖的次数，再跑两边前缀和，最后统计是否达标，输出就行了。

---

## 作者：Fkxxx (赞：1)

### 题意

给出 $m$ 个区间（$\in{[1,n]}$）。问：有多少个区间被其他区间覆盖。

### 思路

我们可用差分求出某个点被覆盖的次数，再跑**两遍**前缀和，就可以求出某一个区间是否被重复覆盖，统计，并输出。

### ACCODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m , l[100005] , r[100005] , t[100005] , ans , a[300005] ;
signed main(){
    cin >> n >> m ;
    for( int i = 1 ; i <= m ; i ++ ){
        int u , v ;
        cin >> u >> v ;
        a[u] ++ ;
        a[v + 1] -- ;
        l[i] = u ;
        r[i] = v ;
    }
    for( int i = 1 ; i <= n ; i ++ ){
        a[i] += a[i - 1] ;
    }
    for( int i = 1 ; i <= n ; i ++ ){
        a[i] += a[i - 1] ;
    }
    for( int i = 1 ; i <= m ; i ++ ){
        if( a[r[i]] - a[l[i] - 1] >= 2 * ( r[i] - l[i] + 1 ) ){
            t[i] = 1 ;
            ans ++ ;
        }
    }
    cout << ans << '\n' ;
    for( int i = 1 ; i <= m ; i ++ ){
        if( t[i] ){
            cout << i << '\n' ;
        }
    }
    return 0 ;
}
```

---

## 作者：Hagasei (赞：1)

用差分处理出每个教室打扫的人数，那么，“能翘掉”就等价于所有要打扫的教室都有至少两人打扫，即 $\min_{l\le i\le r}a_i\ge2$，所以直接 ST 表就好了

code:

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[300005],lgs[300005];
int l[100005],r[100005];
int st[300005][20];
int n,m,ans=0;
inline int min(int x,int y){return x<y?x:y;}
inline int ask(int x,int y){return min(st[x][lgs[y-x+1]],st[y-(1<<lgs[y-x+1])+1][lgs[y-x+1]]);} 
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		cin>>l[i]>>r[i];
		++a[l[i]],--a[r[i]+1];//差分
	}
	lgs[0]=-1;
	for(int i=1;i<=n;++i)a[i]+=a[i-1],lgs[i]=lgs[i/2]+1,st[i][0]=a[i];
	for(int j=1;j<=19;++j){//ST板板
		for(int i=1;i+(1<<j)-1<=n;++i){
			st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
	for(int i=1;i<=m;++i)ans+=ask(l[i],r[i])>1;cout<<ans<<endl;//输出
	for(int i=1;i<=m;++i){
		if(ask(l[i],r[i])>1){
			cout<<i<<endl;
		}
	}
}
```

---

## 作者：hinin (赞：0)

### 题意

给出 $m$ 个区间，求有多少个区间能被其他区间完全覆盖。

### 思路

关于各区间，检查该区间内的所有教室是否包含在多个区间中。

直接写线段树就可以通过。

做法：先插入原有区间，然后进行查询操作。

### 代码

``` cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "-funroll-all-loops")
#define ll long long 
#define pii pair<int, int>
 
#define y1 gigay 
#define x first 
#define y second 
 
using namespace std;
 
#define repeat_from(i,m,n) for (int i = (m); (i) < (n); ++(i))
#define repeat(i,n) repeat_from(i,0,n)

struct segtree {
	int n;
	vector<int> a;
	vector<int> b;

	explicit segtree(int x) 
	{
		n = x;
		a.resize(x << 2);
		b.resize(x << 2);
	}

	void add(int l, int r, int v) 
	{ add(0, 0, n, l, r, v); }

	void add(int i, int il, int ir, int l, int r, int v) 
	{
		if (l <= il and ir <= r) {
			a[i] += v;
			b[i] += v;
		} else if (ir <= l or r <= il) { ; } 
		else {
			add(i * 2 + 1, il, (il + ir) / 2, l, r, v),
			add(i * 2 + 2, (il + ir) / 2, ir, l, r, v);

			b[i] = a[i] + min(
				query(i * 2 + 1, il, (il + ir) / 2, 0, n),
				query(i * 2 + 2, (il + ir) / 2, ir, 0, n)
			);
		}
	}

	int query(int l, int r) { return query(0, 0, n, l, r); }

	int query(int i, int il, int ir, int l, int r) {
		if (l <= il and ir <= r) { return b[i]; } 
		else if (ir <= l or r <= il) { return 1000000007; } 
		else {
			return a[i] + min(
				query(i * 2 + 1, il, (il + ir) / 2, l, r),
				query(i * 2 + 2, (il + ir) / 2, ir, l, r)
			);
		}
	}
};

int n, m; 
vector<int> s; 
vector<int> t; 

int main() 
{
	ios::sync_with_stdio(false); 

	cin >> n >> m;

	s.resize(m); 
	t.resize(m);
	
	for(int i = 0; i < m; i ++) { cin >> s[i] >> t[i]; }
	
	segtree tree(n);
	for(int i = 0; i < m; i ++) { tree.add(s[i] - 1, t[i], 1); }
	
	vector<int> result;
	for(int i = 0; i < m; i ++) {
		if (2 <= tree.query(s[i] - 1, t[i])) 
		{ result.push_back(i + 1); }
	}
	
	cout << result.size() << endl;
	for (int i : result) { cout << i << endl; }

	return 0;
}
```

---

## 作者：smartdevil (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/AT_arc045_b)

差分与前缀和。

## 题意：

给出 $m$ 个区间，求有多少个区间能被其他区间完全覆盖。

## 思路：

先用差分求出某个点被覆盖的次数，再跑两遍前缀和，求出某个区间是否被再次覆盖，统计一下，然后输出即可。

---

## 作者：RioFutaba (赞：0)

# 题意

给定 $n$ 和 $m$ 和 $m$ 个有可能重叠的 $[l,r]$ 区间（区间最大右端点为 $n$），问有多少个区间能被除它自己以外的区间完全覆盖，输出满足条件的区间数量和编号。

数据范围：$1 \le n \le 300000 $，$1 \le m \le 100000$。
# 思路
首先考虑暴力：开一个数组，初始值为 $0$，将每个输入的区间暴力加上 $1$，然后再暴力统计每个区间内的最小值是否 $>1$（即这个区间的每个点都不只有它自己一个区间覆盖），则这个区间能被其他区间完全覆盖。

但这样的复杂度为 $O(nm)$，需要优化。

可以发现，上述的操作都可以使用线段树，所以可以利用线段树将复杂度降为 $O(m \log_2n )$，可以满足时间复杂度要求。

虽然这个做法用在黄题上似乎很傻，但思维难度较低，是个不错的选择。

代码（为了方便将查询、修改区间的端点定义在全局）：

```cpp
#include <bits/stdc++.h>
using namespace std;

/*线段树部分*/
#define ls id<<1
#define rs id<<1|1
const int maxn=3e5+5,maxm=1e5+5,INF=0x3f3f3f3f;
int n,m,a[maxn],ans[maxn<<2],lz[maxn<<2];
int x,y,z;
void push_up(int id){
	ans[id]=min(ans[ls],ans[rs]);
}//简单的pushup
void build(int l,int r,int id){
	if(l==r){
		ans[id]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls);
	build(mid+1,r,rs);
	push_up(id);
}//简单的建树
void dw(int id,int l,int r,int k){
	lz[id]+=k;
	ans[id]+=k;
}
void down(int id,int l,int r){
	int mid=(l+r)>>1;
	dw(ls,l,mid,lz[id]);
	dw(rs,mid+1,r,lz[id]);
	lz[id]=0;
}//简单的传lazy
void update(int l,int r,int k,int id){
	if(x<=l && r<=y){
		ans[id]+=k;
		lz[id]+=k;//因为这个区间所有数都加上了k，所以最大值也加上k
		return ;
	}
	down(id,l,r);
	int mid=(l+r)>>1;
	if(mid>=x) update(l,mid,k,ls);
	if(y>mid) update(mid+1,r,k,rs);
	push_up(id);//记得pushup
}
int query(int l,int r,int id){
	int ret=INF;//因为是求最小值，所以定义为INF
	if(x<=l && r<=y){
		return ans[id];
	}
	int mid=(l+r)>>1;
	down(id,l,r);
	if(x<=mid) ret=min(ret,query(l,mid,ls));
	if(y>mid) ret=min(ret,query(mid+1,r,rs));
	return ret;
}//简单的求区间最大值

/*主函数部分*/
int ll[maxm],rr[maxm],k;
vector<int> as;
int main(){
	scanf("%d%d",&n,&m);
	build(1,n,1);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);ll[i]=x,rr[i]=y;
		x=ll[i],y=rr[i];update(1,n,1,1);//区间加
	}
	for(int i=1;i<=m;i++){
		x=ll[i],y=rr[i];
		if(query(1,n,1)>1){//统计
			k++;
			as.push_back(i);
		}
	}
	printf("%d\n",k);
	for(auto p:as) printf("%d\n",p);//输出答案
	return 0;
}

```

---

