# Cook and Porridge

## 题目描述

Finally, lunchtime!

 $ n $ schoolchildren have lined up in a long queue at the cook's tent for porridge. The cook will be serving porridge for $ D $ minutes. The schoolchild standing in the $ i $ -th position in the queue has a priority of $ k_i $ and eats one portion of porridge in $ s_i $ minutes.

At the beginning of each minute of the break, the cook serves the first schoolchild in the queue one portion of porridge, after which the schoolchild goes to eat their portion. If the $ i $ -th schoolchild is served a portion at the beginning of the $ x $ -th minute, then they will return to the queue at the end of the $ (x + s_i) $ -th minute.

When the $ i $ -th schoolchild returns to the queue, the schoolchildren at the end of the queue whose priority is strictly lower than that of the $ i $ -th schoolchild must let them pass. Thus, they will stand in the queue behind the last schoolchild whose priority is not lower than their own. That is, behind the last schoolchild $ j $ with $ k_j \ge k_i $ . If there is no such schoolchild in the queue, the $ i $ -th schoolchild will stand at the front of the queue.

If several schoolchildren return at the same time, they will return to the queue in ascending order of their $ s_i $ .

For example, if $ n = 3 $ , $ D = 3 $ , $ k = [2, 3, 2] $ , and $ s = [2, 1, 3] $ , the serving will occur as follows:

- At the beginning of minute $ 1 $ , the students in the queue are $ [1, 2, 3] $ , and student $ 1 $ is served porridge;
- at the beginning of minute $ 2 $ , the students in the queue are $ [2, 3] $ , and student $ 2 $ is served porridge;
- at the beginning of minute $ 3 $ , the student in the queue is $ [3] $ , and student $ 3 $ is served porridge;
- at the end of minute $ 3 $ , student $ 2 $ returns to the queue, and the queue becomes $ [2] $ ;
- at the end of minute $ 3 $ , student $ 1 $ returns to the queue, and the queue becomes $ [2, 1] $ , as his priority is lower.

Determine the minimum number of minutes after the start of the break that each schoolchild will receive porridge at least once, or report that this will not happen within $ D $ minutes.

## 样例 #1

### 输入

```
7
3 3
2 2
3 1
2 3
5 10
10 3
7 1
11 3
5 1
6 1
5 20
4 2
7 2
8 5
1 5
3 1
5 17
1 3
8 2
8 3
2 2
1 1
5 14
8 2
4 2
1 3
8 3
6 4
1 11
4 5
5 14
8 2
4 2
1 3
8 3
6 4```

### 输出

```
3
-1
12
6
6
1
6```

# 题解

## 作者：FFTotoro (赞：7)

$\color{Red}*2500$ 纯模拟题。没绷住。

你需要的前置知识仅有结构体、重载运算符和 STL 的基本使用。

考虑模拟题目中的操作，建立两个队列 $Q_1$ 与 $Q_2$（前者是普通队列，使用 `std::vector` 模拟，存储开始时的所有学生；后者是优先队列，使用 `std::priority_queue` 模拟，表示后来插队进来的学生）。定义一个“学生”结构体，存储该学生的优先级 $k$、单次吃粥时间 $s$ 与进入 $Q_2$ 的时间 $t$（如果有），按照题目以 $k$ 为第一关键字（递减），$t$ 为第二关键字（递增），$s$ 为第三关键字（递增）。

可以使用一个指针扫 $Q_1$，如果该指针扫到尾了就代表所有学生都领到粥了。按照时间 $0,1,\ldots,D$ 依次模拟，考虑当前领到粥的是 $Q_1$ 中的人还是 $Q_2$ 中的人：如果 $Q_2$ 为空或者 $Q_2$ 中最大的 $k$ 不大于 $Q_1$ 中最大的 $k$，那么 $Q_2$ 没有人能直接插队到队首，$Q_1$ 的队头可以领一份粥；反之亦然。

接着考虑领到粥的人吃完粥的时间，在那个时间把他扔进 $Q_2$ 里面。

因为 $Q_1$ 是按顺序领粥的，所以求 $Q_1$ 中剩余的最大的 $k$ 只需维护原序列的 $k$ 的后缀最大值即可。

注意判断无解情况。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Student{
  int k,s,t;
  Student(){t=0;}
  Student(int k_,int s_,int t_){k=k_,s=s_,t=t_;}
  bool operator <(const Student &x)const{
    return k==x.k?t==x.t?s>x.s:t>x.t:k<x.k;
  } // 注意 std::priority_queue 的排序规则是反着的
};
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,d,p=0,w=-1; cin>>n>>d;
    vector<Student> Q1(n);
    for(auto &[k,s,t]:Q1)cin>>k>>s;
    vector<int> s(n);
    for(int i=n-1;~i;i--)
      s[i]=max(i==n-1?0:s[i+1],Q1[i].k);
    // 维护后缀最大值
    priority_queue<Student> Q2;
    vector<vector<Student> > v(d);
    for(int i=0;i<d&&w<0;i++){
      if(Q2.empty()||Q2.top().k<=s[p]){
        if(int l=i+Q1[p].s;l<d)
          v[l].emplace_back(Q1[p]);
        if(++p==n)w=i+1; // 所有人都吃了
      } // 从 Q1 队头拿人
      else{
        if(int l=i+Q2.top().s;l<d)
          v[l].emplace_back(Q2.top());
        Q2.pop();
      } // 从 Q2 队头拿人
      for(auto [k,s,t]:v[i])
        Q2.emplace(k,s,i);
      // 把吃完粥的人扔进 Q2
    }
    cout<<w<<'\n';
  }
  return 0;
}
```

---

## 作者：Tjqq (赞：5)

提供一个不太需要思维的解法。

考虑维护每一秒的队列状态。因为要在队列中的某个位置插入，用平衡树维护下标即可。

具体实现时，可以开 $ D $ 个 vector 记录在某个时刻要回到队列里的人。

每个时刻开始时，求出平衡树的第一个元素并删除表示他拿到粥离开队列，同时在他回来时间的地方插入他表示他会在那个时间喝完粥回来。

插入会稍微麻烦一点，要在平衡树上找到第一个大于某个值的位置。直接 $\log^2$ 二分[被卡了](https://codeforces.com/contest/1945/submission/252295403)。可以记录一个子树的最大值从根向下查找，这样一次插入是 $\log$。注意细节有点多。

时间复杂度：$O(D\log n)$。

空间复杂度：$O(D+n)$。

### code

```cpp
// Created by fqr & cyx in 2024
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
#define ll long long
#define pii pair<int,int>
#define pb emplace_back
int ff,Ch;
template <typename T> inline void rd(T &x) {
    x=0,ff=1,Ch=getchar();
    while((Ch<'0'||Ch>'9')&&Ch!='-') Ch=getchar();
    if(Ch=='-')Ch=getchar(),ff=-1;
    while(Ch>='0'&&Ch<='9') {
        x=(x<<1)+(x<<3)+Ch-'0';
        Ch=getchar();
    }
    x*=ff;
}
template <typename T, typename ...Args> inline void rd(T &x, Args &...args) {
    rd(x), rd(args...);
}
using namespace std;
mt19937 rnd(time(0));
const int N=1e6+5;
int n,D,cnt;
bool vis[N];
int g[N],d[N];
class FHQ {
public: 
	int rt,idx;
	int ch[N][2],id[N];
	int val[N],pro[N],sz[N],mx[N];
	void clear() {
		for(int i=1; i<=idx; i++)
			ch[i][0]=ch[i][1]=val[i]=mx[i]=sz[i]=0;
		idx=rt=0;
	}
	inline void push_up(int x){
		sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
		mx[x]=max({mx[ch[x][0]],mx[ch[x][1]],val[x]});
	}
	inline int New(int x){
		val[++idx]=g[x];
		mx[idx]=g[x];
		id[idx]=x;
		pro[idx]=rand();
		sz[idx]=1;
		return idx;
	}
	void split(int x,int k,int &ls,int &rs){
		if(!x)return ls=rs=0,void();
		int u=sz[ch[x][0]]+1;
		if(k>=u){
			ls=x;
			split(ch[x][1],k-u,ch[x][1],rs);
		}
		else {
			rs=x;
			split(ch[x][0],k,ls,ch[x][0]);
		}
		push_up(x);
	}
	int merge(int x,int y){
		if(!x||!y) return x|y;
		if(pro[x]<=pro[y]){
			ch[x][1]=merge(ch[x][1],y);
			return push_up(x),x;
		}
		else {
			ch[y][0]=merge(x,ch[y][0]);
			return push_up(y),y;
		}
	}
	inline void ins(int pos,int x){
		int a,b;
		cnt++;
//		cout<<"ins "<<pos<<' '<<x<<'\n';
		split(rt,pos,a,b);
		rt=merge(merge(a,New(x)),b);
	}
	inline void del(int x) {
		int a,b,c;
		cnt--;
		split(rt,x,a,c);
		split(a,x-1,a,b);
		rt=merge(a,c);
	}
	inline int ask(int l,int r) {
		int a,b,c;
		split(rt,r,a,c);
		split(a,l-1,a,b);
//		cout<<"Qeury "<<l<<' '<<r<<'\n';
		int ans=mx[b];
		rt=merge(merge(a,b),c);
		return ans;
	} 
	inline int lst() {
		int x=rt;
		while(ch[x][1]) x=ch[x][1];
		return val[x];
	}
	inline int fst() {
		int x=rt;
		while(ch[x][0]) x=ch[x][0]; 
		return id[x];
	}
	inline int find(int x,int k) {
		if(!x) return 0;
		if(ch[x][0] && mx[ch[x][1]]<k && val[x]<k) 
			return find(ch[x][0],k);
		if(mx[ch[x][1]]<k && val[x]>=k)
			return sz[ch[x][0]]+1;
		return sz[ch[x][0]]+1+find(ch[x][1],k);
	}
	void dfs(int x) {
		if(!x)return ;
		dfs(ch[x][0]);
		printf("%d ",val[x]);
		dfs(ch[x][1]);
	}
	void print(){
		puts("Tree");
		dfs(rt);
		puts("");
	}
} T;
void Solve() {
	cnt=0;
	rd(n),rd(D);
	T.clear(); 
	vector< vector<pii> >v(D+5);
	bool sp=1;
	for(int i=1; i<=n; i++) {
		vis[i]=0;
		rd(g[i]),rd(d[i]);
		T.ins(i-1,i);
	}
	int ans=0;
	for(int ti=1; ti<=D; ti++) {
//		T.print(); 
		if(!cnt) continue;
//		cout<<"nig\n";
		auto x=T.fst();
		T.del(1);
		ans+=(!vis[x]);
//		cout<<"Calc "<<x<<'\n';
		if(ans==n)
			return printf("%d\n",ti),void();
		sort(v[ti].begin(),v[ti].end());
		vis[x]=1;
		if(ti+d[x]<=D)
			v[ti+d[x]].emplace_back(d[x],x);
		for(auto it:v[ti]) {
//			T.print();
			int x=it.second;
			if(T.mx[T.rt]<g[x]) T.ins(0,x);
			else if(T.lst()>=g[x]) T.ins(cnt,x);
			else {
				auto p=T.find(T.rt,g[x]);
				T.ins(p,x);
			}
		}
	}
	puts("-1");
}
signed main() {
#ifdef LOCAL
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
#endif
	int T;
	rd(T);
	while(T--) Solve();
    return 0;
}
/*
1
5 20
4 2
7 2
8 5
1 5
3 1
*/
```

---

## 作者：NATO (赞：3)

赛时憨批做法，没调出来，~~调出来排名可以涨整整 $1$ 名呢~~。

这种垃圾题完全不值 $2500$ 吧。。。

### 思路浅析：

考虑到每分钟最多只有 $1$ 个人吃粥，所以最多就 $D$ 个人吃粥，$D$ 个人返回队列，所以去枚举时间维护整个过程的可行的。

如果最开始这些人是按照优先度排队的，那么这道题用个优先队列维护一下就做完了，但是最开始的时候他们的顺序是按照编号排的，和后面的排队规则相比就是一种无序的状态，我们就需要一种可以支持按照我们想要的顺序进行存储，支持中间插入的数据结构，是什么呢？

平衡树，当然是平衡树。

初始时我们就按照给出的顺序建出平衡树，吃粥出队就找到最左边的节点即对应队列中首个孩子的节点，如果还没吃过粥就更新一下他的最小吃粥时间，删除节点即可。对于当前时间需要插入的节点，考虑我们在平衡树的每个节点都维护一个它子树内的最大优先级，平衡树上二分找到优先级不低于自己的最后的节点的位置，插入在后面即可（二分套平衡树多一只 $\log$，不是很能过）。

实现上考虑用 `vector` 存当前时间需要加入的人，记得按题述顺序插入就没有什么注意点了。。。

时间复杂度由于 $n,D$ 同阶，故为 $O(n\log n)$。

#### 参考代码：

笔者只会写无旋 Treap，所以只能用无旋 Treap 实现：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ls(id)	tr[id].son[0]
#define rs(id)	tr[id].son[1]
#define INF 2147483647
using namespace std;
ll t;
ll cnt,rt,n,d;
ll mt[200005];
ll k[200005],s[200005];
vector<ll>na[300005];
struct tree
{
	ll rd,v,size,son[2],maxn,uid;
	void clear()
	{
		rd=v=size=son[0]=son[1]=maxn=uid=0;
	}
	#define ls(id) tr[id].son[0]
	#define rs(id) tr[id].son[1]
}tr[500005];
void update(ll id)
{
 	tr[id].size=tr[tr[id].son[0]].size+tr[tr[id].son[1]].size+1;
 	tr[id].maxn=max(tr[tr[id].son[0]].maxn,max(tr[id].v,tr[rs(id)].maxn));
}
ll build(ll l,ll r)
{
	if(l>r)return 0;
	ll mid=l+r>>1; 
	++cnt;tr[cnt].clear();
	tr[cnt].rd=rand();
	tr[cnt].v=k[mid];
	ll u=cnt;
	tr[u].son[0]=build(l,mid-1); 
	tr[u].son[1]=build(mid+1,r);
	tr[u].uid=mid;
	update(u);
	return u; 
}
void sp_s(ll id,ll &x,ll &y,ll k)
{
	if(!id){x=y=0;return;}
	if(tr[tr[id].son[0]].size<k)
	{
		x=id;
		sp_s(rs(id),rs(id),y,k-tr[tr[id].son[0]].size-1);
	}
	else
	{
		y=id;
		sp_s(ls(id),x,ls(id),k);
	}
	update(id);
 } 
ll marge(ll x,ll y)
{
	if(!x||!y)	return x+y;
	if(tr[x].rd<tr[y].rd)
	{
		tr[x].son[1]=marge(tr[x].son[1],y);
		update(x);
		return x;
	}
	else
	{
		tr[y].son[0]=marge(x,tr[y].son[0]);
		update(y);
		return y;
	}
}
ll get_ss(ll id,ll val)
{
	if(!id)return 0;
	if(tr[rs(id)].maxn>=val)return tr[ls(id)].size+1+get_ss(rs(id),val);
	if(tr[id].v>=val)return tr[ls(id)].size+1;
	return get_ss(ls(id),val);
}
bool cmp(ll a,ll b)
{
	return s[a]<s[b];
}
ll new_node(ll x)
{
	tr[++cnt].clear();
	tr[cnt].rd=rand();
	tr[cnt].size=1;tr[cnt].maxn=tr[cnt].v=k[x];
	tr[cnt].uid=x;
	return cnt;
}
int main()
{
	srand(time(0));
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		for(ll i=1;i<=cnt;++i)tr[i].clear();
		for(ll i=1;i<=d;++i)na[i].clear();
		cnt=rt=0;
		cin>>n>>d;
		for(ll i=1;i<=n;++i)cin>>k[i]>>s[i],mt[i]=-1;
		rt=build(1,n);
		ll tot=0,maxn=0,ns=n;
		for(ll i=1;i<=d;++i)
		{
			ll x,y;
			if(ns)
			{
			sp_s(rt,x,y,1);
			rt=y;
			if(mt[tr[x].uid]==-1)mt[tr[x].uid]=i,++tot,maxn=max(maxn,i);
			if(s[tr[x].uid]+i<=d)
			na[s[tr[x].uid]+i].push_back(tr[x].uid);--ns;	
			}
			sort(na[i].begin(),na[i].end(),cmp);
			for(auto it:na[i])
			{
				if(tr[rt].maxn<k[it]||!ns)
				rt=marge(new_node(it),rt);
				else
				{
					sp_s(rt,x,y,get_ss(rt,k[it]));
					rt=marge(x,marge(new_node(it),y));
				}
				++ns;
			}
		}
		if(tot==n)cout<<maxn<<'\n';
		else cout<<-1<<'\n';
	}
}
```

---

## 作者：MaxBlazeResFire (赞：0)

暴力模拟 D 次过程，维护一个初始排列，不断从队头出人，出完时结束；然后每在 $x$ 时刻走一个人，就在 $x+s_i$ 处的优先队列中追加这个人。在 $x+s_i$ 结束时把该时刻优先队列的人加入全局优先队列中，和原序列一起比较。取全局优先队列里的人的条件是当前原序列中的 $k$ 最大值严格小于队头。

复杂度 $O(D\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 600005

int n,D,k[MAXN],s[MAXN],maxx[MAXN];

struct node{
	int k,t,s;
	inline bool operator <( node b ) const{
		if( k != b.k ) return k < b.k;
		if( t != b.t ) return t > b.t;
		return s > b.s;
	}
};

priority_queue<node> Q[MAXN],CQ;

inline void solve(){
	scanf("%lld%lld",&n,&D);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld%lld",&k[i],&s[i]);
	for( int i = n ; i >= 1 ; i -- ) maxx[i] = max( maxx[i + 1] , k[i] );
	int visc = 0,flag = 0;
	for( int tim = 1 ; tim <= D ; tim ++ ){
		if( CQ.empty() ){
			visc ++; if( visc >= n ){ printf("%lld\n",tim); flag = 1; break; }
			if( tim + s[visc] <= D ) Q[tim + s[visc]].push( node{ k[visc] , tim + s[visc] , s[visc] } );
		}
		else{
			node u = CQ.top();
			if( maxx[visc + 1] >= u.k ){
				visc ++; if( visc >= n ){ printf("%lld\n",tim); flag = 1; break; }
				if( tim + s[visc] <= D ) Q[tim + s[visc]].push( node{ k[visc] , tim + s[visc] , s[visc] } );
			}
			else{
				CQ.pop();
				if( tim + u.s <= D ) Q[tim + u.s].push( node{ u.k , tim + u.s , u.s } );
			}
		}
		while( !Q[tim].empty() ){
			node u = Q[tim].top(); Q[tim].pop();
			CQ.push( u );
		}
	}
	if( !flag ) puts("-1");
	for( int i = 1 ; i <= D ; i ++ ) while( !Q[i].empty() ) Q[i].pop();
	while( !CQ.empty() ) CQ.pop();
	for( int i = 1 ; i <= n ; i ++ ) maxx[i] = 0;
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

