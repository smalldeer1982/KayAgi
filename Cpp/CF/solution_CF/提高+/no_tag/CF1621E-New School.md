# New School

## 题目描述

You have decided to open a new school. You have already found $ n $ teachers and $ m $ groups of students. The $ i $ -th group of students consists of $ k_i \geq 2 $ students. You know age of each teacher and each student. The ages of teachers are $ a_1, a_2, \ldots, a_n $ and the ages of students of the $ i $ -th group are $ b_{i, 1}, b_{i, 2}, \ldots, b_{i, k_i} $ .

To start lessons you should assign the teacher to each group of students. Such assignment should satisfy the following requirements:

- To each group exactly one teacher assigned.
- To each teacher at most $ 1 $ group of students assigned.
- The average of students' ages in each group doesn't exceed the age of the teacher assigned to this group.

The average of set $ x_1, x_2, \ldots, x_k $ of $ k $ integers is $ \frac{x_1 + x_2 + \ldots + x_k}{k} $ .

Recently you have heard that one of the students will refuse to study in your school. After this, the size of one group will decrease by $ 1 $ while all other groups will remain unchanged.

You don't know who will refuse to study. For each student determine if you can start lessons in case of his refusal.

Note, that it is not guaranteed that it is possible to start lessons before any refusal.

## 说明/提示

In the first test case there is one group of students with average age $ \frac{25+16+37}{3}=26 $ and one teacher with age $ 30 $ . There exists only one assignment that allows to start lessons.

If the student with age $ 16 $ will refuse to study, the average age of students in this group will become $ \frac{25+37}{2}=31 $ so there won't be any assignment that allows to start lessons.

In the second test case it is impossible to start lessons initially. However, if the $ 3 $ -rd student with age $ 111 $ will refuse to study, the average ages of groups will become $ \frac{4 + 5}{2}=4.5 $ and $ \frac{11+11}{2} = 11 $ correspondingly. Then it is possible to assing the first group to the first teacher and the second group to the third teacher.

## 样例 #1

### 输入

```
2
1 1
30
3
25 16 37
4 2
9 12 12 6
2
4 5
3
111 11 11```

### 输出

```
101
00100```

# 题解

## 作者：Drind (赞：2)

首先我们发现这就是一个二分图完美匹配的模型，考虑使用 hall 定理。因为选择了一个平均数为 $avg_i$ 的学生组后，选中任何 $avg_j\ge avg_i$ 的学生组 $j$ 都不会让可匹配的老师数量变多，所以尽可能的全部选上。此时我们可以得到一个大致思路，就是先对值域建一个数据结构，在 $i$ 的位置上维护所有年龄大于等于 $i$ 的老师数量减去平均数大于等于 $i$ 的学生组数量，这样只要做一次全局 rmq，如果值小于 $0$ 则无解，否则有解。

我们考虑带修，本质上就是给一段区间加一或减一，所以这段区间单独讨论即可。用可以实现区间 rmq 的数据结构即可维护，我写了 st 表。

因为没有规定 $\sum V $，所以要先做离散化。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

int st[20][N];
void build(int n){
	int k=log2(n);
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n-(1<<i)+1;j++){
			st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
		}
	}
}
int query(int l,int r){
	//cout<<l<<" "<<r<<"\n"; //return 1e9; 
	if(l>r) return 1e9;
	int k=log2(r-l+1);
	return min(st[k][l],st[k][r-(1<<k)+1]);
}

int a[N],k[N];
vector<int>b[N];

int lsh[N*5],cnt;

inline void fake_main(){
	int n,m; cin>>n>>m; cnt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]; lsh[++cnt]=a[i];
	}
	for(int i=1;i<=m;i++){
		b[i].clear();
		cin>>k[i]; int tot=0;
		for(int j=1;j<=k[i];j++){
			int tmp; cin>>tmp;
			b[i].push_back(tmp); 
			tot+=tmp;
		}
		tot=(tot+k[i]-1)/k[i];
		
		lsh[++cnt]=tot;
		for(auto j:b[i]){
			int tmp=tot-j; tmp=(tmp+k[i]-1-1)/(k[i]-1);
			lsh[++cnt]=tmp;
		}
	}
	
	sort(lsh+1,lsh+cnt+1); int V=unique(lsh+1,lsh+cnt+1)-lsh-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(lsh+1,lsh+V+1,a[i])-lsh;
		st[0][a[i]]++;
	}
	for(int i=1;i<=m;i++){
		int tot=0;
		for(auto j:b[i]) tot+=j;
		tot=(tot+k[i]-1)/k[i];
		tot=lower_bound(lsh+1,lsh+V+1,tot)-lsh;
		st[0][tot]--;
	}
	
	for(int i=V;i>=1;i--){
		st[0][i]+=st[0][i+1];
	}
	build(V);
	for(int i=1;i<=m;i++){
		int tot=0;
		for(auto j:b[i]) tot+=j;
		int lst=(tot+k[i]-1)/k[i]; lst=lower_bound(lsh+1,lsh+V+1,lst)-lsh;
		for(auto j:b[i]){
			int tmp=tot-j;
			tmp=(tmp+k[i]-1-1)/(k[i]-1);
			tmp=lower_bound(lsh+1,lsh+V+1,tmp)-lsh;
			if(lst==tmp){
				if(query(1,V)<0) cout<<"0";
				else cout<<"1";
			}else if(lst<tmp){
				if(min(query(1,lst),query(tmp+1,V))<0) cout<<"0";
				else if(query(lst+1,tmp)<1) cout<<"0";
				else cout<<"1";
			}else if(tmp<lst){
				if(min(query(1,tmp),query(lst+1,V))<0) cout<<"0";
				else if(query(tmp+1,lst)<-1) cout<<"0";
				else cout<<"1";
			}
		}
	}
	for(int i=1;i<=V;i++) st[0][i]=0;
	cout<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：Sword_K (赞：2)

先考虑学生不会跑的情况。一开始可能会想贪心地匹配，但是感觉不太方便快速修改（其实也能做，就是官方题解方法）。但可以把问题转化：把老师拍到数轴上，每组学生的平均值也拍到数轴上，那么当前状态合法当且仅当对于数轴上的任意整数位置，老师的后缀和不小于学生的后缀和。

转化后显然是对的，那么就考虑修改。

容易发现一次修改相当于把一组学生从一个点移到了另一个点，这两个点间的后缀和会 $+1$ 或 $-1$ （注意边界） 。

如果某个位置老师的后缀和与学生的后缀和的差比 $-1$ 还小 ，那无论怎么改都不行。

如果差存在 $-1$  ，那么当前状态要合法就必须把所有差是 $-1$ 的地方都 $+1$ ；如果是差存在 $0$ ，那么要保证 $-1$ （这里 $-1$ 指修改）的地方不经过这样的地方。前者直接先算出一下至少需要覆盖的区间，判断是否包含，后者就查找一下离左端点最近的 $0$ 和右端点的位置关系即可。

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2300}$
---
### 解题思路：

细节处理不是很简单，最麻烦的地方就是不保证一开始能开学。

基本模型是一个显然的贪心，将所有的学生和老师都按照年龄从大到小的顺序排序，然后依次匹配，如果出现某一组学生的平均年龄超过老师就一定无解。

但是这道题多了一个更改，如果按照上面的思路直接模拟显然会超时，所以考虑从题目的性质出发进行优化。

---

发现每一次只有一组学生变化，所以无论这组学生的平均年龄增加了多少或者减少了多少，对于某一个老师来说，最多也只有一个位置的偏移。

根据这个，考虑记录下学生在没有更改的的情况下与前一位，当前位，后一位按照年龄从大到小排好序的老师的相性情况，如果相性不好就记为 $1$，否则记为 $0$。

然后考虑每一个学生，首先根据一开始记录下来的总和和总数计算出新的平均值并为这个新的平均值用二分查找找到新的位置。

如果新的位置上新的平均数比对应老师的年龄大。那么一定不可行，否则分平均值变大和平均值变小两种情况考虑。

1. 如果平均值变大，新的位置前移，那么旧位置和新位置之间的所有的学生都会和之前一位搭配，其他的位置不受影响，和原来的老师搭配。

2. 反之，新的位置向后移动，旧位置和新位置之间的学生会和后一个老师搭配，其他位置不受影响，需要注意，这里二分查找的位置是因该呆的位置的后一个，需要减一下。

直接用记录下的信息处理出来就行了。

---
### 代码：
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=100005;
struct str{
	int k,sum,id;
	vector <int> v,ans;
	double ave;
	bool operator <(str x){
		return ave>x.ave;
	}
}p[MAXN],y;
int n,m,T,te[MAXN],x,pos[MAXN],pl,ca[MAXN],nx[MAXN],tot;
double nw;
void init(){
	for(int i=1;i<=m;i++)
	p[i].v.clear(),
	p[i].sum=p[i].k=p[i].ave=0,
	p[i].ans.clear();
}
bool cmd(int x,int y){return x>y;}
bool cmd2(str a,str b){return a.id<b.id;}
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d%I64d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%I64d",&te[i]);
		sort(te+1,te+n+1,cmd);
		for(int i=1;i<=m;i++){
			scanf("%I64d",&p[i].k);
			p[i].id=i;
			for(int j=1;j<=p[i].k;j++){
				scanf("%I64d",&x);
				p[i].sum+=x;
				p[i].v.push_back(x);
				p[i].ans.push_back(1);
			}
		}
		for(int i=1;i<=m;i++)p[i].ave=(double)p[i].sum/(double)p[i].k;
		sort(p+1,p+m+1);
		for(int i=2;i<=m;i++){
			if((double)te[i-1]<p[i].ave)pos[i]=1;
			else pos[i]=0;
		}
		for(int i=1;i<=m;i++)pos[i]+=pos[i-1];
		
		for(int i=1;i<=m;i++){
			if((double)te[i]<p[i].ave)ca[i]=1;
			else ca[i]=0;
		}
		for(int i=2;i<=m;i++)ca[i]+=ca[i-1];
		
		for(int i=1;i<m;i++){
			if((double)te[i+1]<p[i].ave)nx[i]=1;
			else nx[i]=0;
		}
		for(int i=1;i<m;i++)nx[i]+=nx[i-1];
		
		for(int i=1;i<=m;i++){
			for(int j=0;j<p[i].k;j++){
				nw=((double)p[i].sum-(double)p[i].v[j])/((double)p[i].k-1);
				y.ave=nw;
				pl=lower_bound(p+1,p+m+1,y)-p;
				
				if(pl==i)if(ca[pl-1]+ca[m]-ca[pl])
				p[i].ans[j]=0;
				
				if(pl>i){
                    pl--;
					if(ca[m]+(pos[pl]-pos[i])-(ca[pl]-ca[i-1]))
					p[i].ans[j]=0;
				}
				
				if(pl<i)if(ca[m]+(nx[i-1]-nx[pl-1])-(ca[i]-ca[pl-1]))
				p[i].ans[j]=0;
				
				if(nw>(double)te[pl])
				p[i].ans[j]=0;
			}
		}
		sort(p+1,p+m+1,cmd2);
		for(int i=1;i<=m;i++){
			for(int j=0;j<p[i].k;j++)
			printf("%d",p[i].ans[j]);
		}
		printf("\n");
		init();
	}
	return 0;
}

```


---

## 作者：DaiRuiChen007 (赞：1)

# CF1621E - New School 题解

## 题目大意

现在给定有 $n$ 个数数组 $a$ 和另外 $m$ 组数（第 $i$ 组数有 $k_i$ 个，称为 $g_i$），我们定义一种“合法匹配”表示：

- 每组数都有且仅有一个 $a$ 里的数与之匹配。
- $a$ 里的每一个数都至多与一组数匹配。
- 每组数 $g_i$ 匹配的数 $a_i$ 的值大于等于这组数的平均值。

现在让你求出对于 $m$ 组数里的每一个数，如果删去，剩下的数能否构成“合法匹配”。

数据范围保证：$1\le m\le n\le 10^5,1<k_i,S\le2\times10^5$ ，（$S=\sum_{i=1}^m k_i$）
。
## 思路分析

首先考虑不删数的情况，贪心地进行匹配，$a_i$ 最大的数匹配平均值最大的一组，可以证明，这种方法是最优的，如果这种匹配都不合法，那么这种情况就是无解的。

接下来考虑删数的情况，显然，在删去 $g_i$ 中的某一个数后，这一组数的平均值会发生改变，其相对位置（排序后第几大）也会改变，假设这组数原来按平均值从大到小排序是第 $h[i]$ 大的，而更新后是第 $d[i]$ 大，此时情况分为三种：

1. $d[i]<h[i]$ 时：

$a_1\sim a_{d[i]-1}$ 不变，和原来的匹配。

$a_{d[i]}$ 和 $g_{h[i]}$ 互相匹配。

$a_{d[i]+1}\sim a_{h[i]-1}$ 和后一个匹配。

$a_{h[i]+1}\sim a_n$ 不变，和原来的匹配。

2. $d[i]=h[i]$ 时：

$a_1\sim a_{d[i]-1}$ 不变，和原来的匹配。

$a_{d[i]}$ 和 $g_{d[i]}$ 互相匹配。

$a_{d[i]+1}\sim a_n$ 不变，和原来的匹配。

3. $d[i]>h[i]$ 时：

$a_1\sim a_{h[i]-1}$ 不变，和原来匹配。

$a_{h[i]}\sim a_{d[i]-1}$ 和前一个匹配。

$a_{d[i]}$ 和 $g_{h[i]}$ 互相匹配。

$a_{d[i]+1}\sim a_n$ 不变，和原来的匹配。

现在问题的关键是如何快速求出 $d[i]$ 和如何快速判断 $a$ 中的某个区间能不能和对应的/前一个/后一个匹配。

显然，求出 $d[i]$ 可以用二分查找在 $\Theta(\log m)$ 的时间内完成。

判断的时候可以用前缀和记录，用三个数组 $pre[i],now[i],nxt[i]$ 分别表示前 $i$ 个位置中有几个 $t[i]$ **不能**与前一个/对应的/后一个匹配。

所以这个算法的时间复杂度是 $\Theta(S\log m)$ 的，可以通过本题。

注意用前缀和记录的时候可能会比较恶心，注意模拟的下标位置。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int MAXN=2e5+1;
struct node {
	double avr;
	int id;
	node() { avr=0.0,id=0; }
	inline friend bool operator <(const node &x,const node &y) {
		return x.avr>y.avr; //按组内平均值排序 
	}
}	s[MAXN];
inline node mp(double avr,int id) {
	node ans;
	ans.avr=avr,ans.id=id;
	return ans;
}
inline bool cmp(const int &x,const int &y) {
	return x>y;
}
vector <int> g[MAXN];
int h[MAXN],t[MAXN],pre[MAXN],now[MAXN],nxt[MAXN],sum[MAXN];
inline void solve() {
	int m,n;
	scanf("%lld%lld",&n,&m);
	for(register int i=1;i<=n;++i) scanf("%lld",&t[i]);
	for(register int i=1;i<=m;++i) {
		int k;
		sum[i]=0;
		scanf("%lld",&k);
		g[i].clear();
		for(register int j=1;j<=k;++j) {
			int input;
			scanf("%lld",&input);
			g[i].push_back(input);
			sum[i]+=input; //sum[i]记录总和 
		}
		s[i].avr=(double)((double)(sum[i])/(double)(k)),s[i].id=i;
	}
	sort(s+1,s+m+1);
	sort(t+1,t+n+1,cmp);
	for(register int i=1;i<=m;++i) {
		if(i<m) nxt[i]=nxt[i-1]+(s[i].avr>t[i+1]);
		if(i>1) pre[i]=pre[i-1]+(s[i].avr>t[i-1]);
		now[i]=now[i-1]+(s[i].avr>t[i]);
		//nxt,pre,now含义如题所述，维护前缀和 
		h[s[i].id]=i;
	}
	for(register int i=1;i<=m;++i) {
		for(register auto x:g[i]) {
			double z=(double)((double)(sum[i]-x)/(double)(g[i].size()-1));
			int d=lower_bound(s+1,s+m+1,mp(z,0))-s;
			//题解式子 
			if(d==h[i]) {
				if(z>t[d]||(now[m]-(now[d]-now[d-1]))) {
					putchar('0');
				} else {
					putchar('1');
				}
			} else if(d>h[i]) {
				--d; 
				if(z>t[d]||(now[m]+((pre[d]-pre[h[i]])-(now[d]-now[h[i]-1])))) {
					putchar('0');
				} else {
					putchar('1');
				}
			} else if(d<h[i]){
				if(z>t[d]||(now[m]+((nxt[h[i]-1]-nxt[d-1])-(now[h[i]]-now[d-1])))) {
					putchar('0');
				} else {
					putchar('1');
				}
			}
		}
	}
	putchar('\n');
	return ;
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve(); //多组数据 
	return 0;
} 
```



---

## 作者：I_am_Accepted (赞：1)

### Preface

赛场上差点调出来 qwq。

### Analysis

显然，只有年长的 $m$ 位教师有用，所以只保留这些教师。 

如果在某一种情况下全体能够上课，则必定将教师和班级按照（平均）年纪分别排序，然后一一对应，也能够上课。

也就是说，我们只要考虑两者有序后是否能上课就行。

设 $a_1\le a_2\le\dots\le a_m$ 为教师年龄，$b_1\le b_2\le\dots\le b_m$ 为班级平均年龄。

能上课当且仅当 $\forall a_i\ge b_i$。

由于每次询问均只 remove 一个人，即改变一个班级 $x$ 的年龄平均值 $b_x$，这时这个班年龄平均值将在非降 $\{b\}$ 序列中重新定位，设为 $y$。

假设 $x>y$（该班级的平均值减小），则老师和班级的对应关系变为：

$$\begin{matrix}
a_1&\ \dots&\ a_{y-1}&\ \color{blue}{a_{y}}&\ \color{blue}{a_{y+1}}&\ \color{blue}{a_{y+2}}&\ \dots&\ \color{green}{a_{x}}&\ a_{x+1}&\ \dots&\ a_m
\\
b_1&\ \dots&\ b_{y-1}&\ \color{green}{b_x'}&\ \color{blue}{b_{y}}&\ \color{blue}{b_{y+1}}&\ \dots&\ \color{blue}{b_{x-1}}&\ b_{x+1}&\ \dots&\ b_m
\end{matrix}$$ 

其中 $b_x'$ 表示班级变化后的平均值。

$x<y$ 时同理。

发现就是中间一部分老师与学生错了 $1$ 位，可以预处理。

$$pre_x=[a_x\ge b_{x-1}]$$

$$now_x=[a_x\ge b_{x}]$$

$$suc_x=[a_x\ge b_{x+1}]$$

当然实际操作中这三个数组要用前缀和。

遍历每一个要退学的学生，计算即可。

时间复杂度 $O(n\log n+\log m \sum k)$，其中 $\log m$ 为二分寻找 $b_x$ 变换后的位置 $y$ 所致。

### Code

非常丑（借指本人），非必要不要看，不过跑得飞快。

[Link](https://codeforces.com/contest/1621/submission/141651719)

---

## 作者：清烛 (赞：0)

## Description
要开办学校。$n$ 个老师，$m$ 组学生。第 $i$ 组学生有 $k_i$ 人。老师的年龄分别为 $a_1, \cdots, a_n$，学生的年龄分别为 $b_{i, 1},\cdots, b_{i, k_i}$。要求安排老师到每组学生，满足

- 每组学生都恰好有一个老师。
- 一个老师最多带一个组。
- 一组内，学生的平均年龄不超过老师的年龄。

对于每个学生，求出若其不来上课，课程能否被安排。$1\le m\le n\le 10^5$，$1\le a_i,b_{i,j}\le 10^5$，$2\le k_i\le 10^5$，$\sum k_i\le 2\times 10^5$。

## Solution

考虑将所有学生组和所有老师降序排序。则有解当且仅当 $\forall 1\le i\le m$ 有 $avr_i\le a_i$，该情况下我们将其一一对应即可。

而当一个学生不来时，其只会影响一个组 $i$ 的平均年龄 $avr_i$。对于每一个学生 $b_{i, x}$，都可以二分找出没有他之后，整组人的新的位置 $j$。这样一来，$[j, i)$ 内的组都会往 $i$ 的方向平移一格。我们需要知道的，就是改变后的局面是否合法。

至于改变之后是否合法，可以记三个前缀和数组（分别维护当前位置，当前位置往左/右平移一格后是否合法）来实现，详见代码。

## Implementation
实现较为恶心。同时，需要避开浮点误差。

```cpp
const int maxn = 2e5 + 5;
using ll = long long;
using pli = pair<ll, int>;
int ok[maxn], ok_suf[maxn], ok_pre[maxn], pos0[maxn];
pair<pli, int> B[maxn];
pli a[maxn];
vector<int> c[maxn];

bool operator>(const pli &a, const pli &b) {return a.first * b.second > b.first * a.second;}

void solve() {
    int n, m; read(n, m);
    FOR(i, 1, n) read(a[i].first), a[i].second = 1;
    FOR(i, 1, m) {
        int k; read(k); ll sum = 0;
        c[i].resize(k);
        FOR(j, 0, k - 1) read(c[i][j]), sum += c[i][j];
        B[i] = make_pair(pli(sum, k), i);
    }
    sort(a + 1, a + n + 1, operator>);
    auto cmp = [](const auto &a, const auto &b) {return a.first > b.first;};
    sort(B + 1, B + m + 1, cmp);
    FOR(i, 1, m) {
        ok[i] = ok[i - 1] + (B[i].first > a[i]);//记录不合法的情况
        ok_pre[i] = ok_pre[i - 1] + (B[i].first > a[i - 1]);//记录不合法的情况
        ok_suf[i] = ok_suf[i - 1] + (B[i].first > a[i + 1]);//记录不合法的情况
        pos0[B[i].second] = i;
    }
    FOR(i, 1, m) {
        for (auto x : c[i]) {
            pli now(B[pos0[i]].first.first - x, B[pos0[i]].first.second - 1);
            int to = lower_bound(B + 1, B + m + 1, make_pair(now, i), cmp) - B;
            if (to > pos0[i])
                putchar((now > a[to - 1] || ok[pos0[i] - 1] + ok_pre[to - 1] - ok_pre[pos0[i]] + ok[m] - ok[to - 1]) ? '0' : '1');
            else putchar((now > a[to] || ok[to - 1] + ok_suf[pos0[i] - 1] - ok_suf[to - 1] + ok[m] - ok[pos0[i]]) ? '0' : '1');
        }
    }
    putchar('\n');
    return;
}

int main() {
    int T; read(T);
    while (T--) solve();
    return output(), 0;
}
```



---

