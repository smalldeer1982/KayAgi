# Berserk Monsters

## 题目描述

Monocarp is playing a computer game (yet again). Guess what is he doing? That's right, killing monsters.

There are $ n $ monsters in a row, numbered from $ 1 $ to $ n $ . The $ i $ -th monster has two parameters: attack value equal to $ a_i $ and defense value equal to $ d_i $ . In order to kill these monsters, Monocarp put a berserk spell on them, so they're attacking each other instead of Monocarp's character.

The fight consists of $ n $ rounds. Every round, the following happens:

- first, every alive monster $ i $ deals $ a_i $ damage to the closest alive monster to the left (if it exists) and the closest alive monster to the right (if it exists);
- then, every alive monster $ j $ which received more than $ d_j $ damage during this round dies. I. e. the $ j $ -th monster dies if and only if its defense value $ d_j $ is strictly less than the total damage it received this round.

For each round, calculate the number of monsters that will die during that round.

## 说明/提示

Explanation for the first test case of the example:

During the first round, the following happens:

- the monster $ 1 $ deals $ 3 $ damage to the monster $ 2 $ ;
- the monster $ 2 $ deals $ 4 $ damage to the monster $ 1 $ and the monster $ 3 $ ;
- the monster $ 3 $ deals $ 7 $ damage to the monster $ 2 $ and the monster $ 4 $ ;
- the monster $ 4 $ deals $ 5 $ damage to the monster $ 3 $ and the monster $ 5 $ ;
- the monster $ 5 $ deals $ 10 $ damage to the monster $ 4 $ ;
- the monster $ 1 $ does not die, since it received $ 4 $ damage and its defense is $ 4 $ ;
- the monster $ 2 $ dies, since it received $ 10 $ damage and its defense is $ 9 $ ;
- the monster $ 3 $ dies, since it received $ 9 $ damage and its defense is $ 1 $ ;
- the monster $ 4 $ does not die, since it received $ 17 $ damage and its defense is $ 18 $ ;
- the monster $ 5 $ dies, since it received $ 5 $ damage and its defense is $ 1 $ .

After the first round, the monsters $ 1 $ and $ 4 $ stay alive.

During the second round, the following happens:

- the monster $ 1 $ deals $ 3 $ damage to the monster $ 4 $ ;
- the monster $ 4 $ deals $ 5 $ damage to the monster $ 1 $ ;
- the monster $ 1 $ dies, since it received $ 5 $ damage and its defense is $ 4 $ ;
- the monster $ 4 $ does not die, since it received $ 3 $ damage and its defense is $ 18 $ .

During the next three rounds, only the $ 4 $ -th monster is alive, so nothing happens.

## 样例 #1

### 输入

```
3
5
3 4 7 5 10
4 9 1 18 1
2
2 1
1 3
4
1 1 2 4
3 3 4 2```

### 输出

```
3 1 0 0 0 
0 0 
1 1 1 0```

# 题解

## 作者：Eraine (赞：15)

编号：CF1922D

tag：链表、均摊分析

提供一个线性做法。

发现每个元素只能被删一次。所以删除操作总次数不超过 $n$，均摊 $\Theta(n)$。

现在的瓶颈在于快速找到待删除的元素。首先有个结论：

假设在某一轮，元素 $x$ 没被删掉，而当前序列的 $L_x$ 和 $R_x$ 也没被删掉（即 $x$ 的前驱和后继也没在这一轮被删掉），那么下一轮 $x$ 不可能成为被删除的点。

解释一下原因。对于每一个元素 $x$ 存在的任何一轮，影响 $x$ 是否能在下一轮存在的影响因素是 $d_x,a_{L_x},a_{R_x}$。$d_x$ 在任何一轮都是不变的，但是 $a_{L_x},a_{R_x}$ 可能会变，因为 $x$ 原来的前驱后继可能被删除。

若在某一轮，元素 $x$ 没被删掉，而当前序列的 $L_x$ 和 $R_x$ 也没被删掉，则说明 $a_{L_x}+a_{R_x}\le d_x$。由于在下一轮 $L_x$ 和 $R_x$ 不变，则 $a_{L_x}+a_{R_x}\le d_x$ 仍成立。所以 $x$ 不可能在下一轮被删。

所以此时我们需要找到的就是每一轮中前驱和后继发生改变的元素。发现不好直接考虑，则反向思考。每一轮被删元素的前驱后继（前提是前驱后继在下一轮仍存在）满足此条件，则可从上一轮被删元素的前驱后缀中判断是否存在本轮被删的元素。

由于被删元素均摊 $\Theta(n)$，每个被删元素最多会生成 $2$ 个在下一轮可能被删元素，所以生成可能被删元素的时间复杂度也是 $\Theta(n)$。

注意第一轮每个元素都可能成为被删元素，所以需要特判。

链表维护当前序列。

$\Theta(n)$。

考场代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,L[N],R[N],a[N],d[N];
vector<int>islst,dellst;
bool vis[N],isout[N];
void add(int u){//将 u 放置可能被删元素集合
	if(u<1||u>n){
		return;
	}
	if(!vis[u]&&!isout[u]){//没被删且仍未加入可能被删集合
		vis[u]=1;
		islst.push_back(u);
	}
}
void del(int u){//链表删除操作
	R[L[u]]=R[u];
	L[R[u]]=L[u];
	add(L[u]);
	add(R[u]);
}
void solve(){
	scanf("%d",&n);
	a[0]=a[n+1]=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		isout[i]=0;//判断每个数是否已经被删
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&d[i]);
	}
	for(int i=1;i<=n+1;i++){//链表初始连边
		L[i]=i-1;
		R[i-1]=i;
	}
	for(int i=1;i<=n;i++){//第一轮特判
		add(i);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<islst.size();j++){//遍历可能被删元素集合
			int x=islst[j];
			vis[x]=0;
			if(d[x]<a[L[x]]+a[R[x]]){
				dellst.push_back(x);//放到确定被删元素集合
			}
		}
                //这里不直接删除的原因是 d[x]<a[L[x]]+a[R[x]] 语句会涉及到之前被删的元素，若直接删除可能会影响后面的判断结果
		islst.clear();
		int cnt=0;
		for(int j=0;j<dellst.size();j++){
			int x=dellst[j];
			isout[x]=1;//已经被删
		}
		for(int j=0;j<dellst.size();j++){
			int x=dellst[j];
			del(x);
			++cnt;
		}
		dellst.clear();
		printf("%d ",cnt);
	}
	printf("\n");
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}
```

各位看官点个赞再走吧 awa

---

## 作者：zjinze (赞：6)

#### 前置知识： 双向链表。

#### 思路：

我们可以先用结构体来建立一个双向链表，如：

```cpp
struct node{
   int pre;
   int nxt;
}v[300010];
```

$v[i].pre$ 表示第 $i$ 个怪物左侧的第一只存活的怪物的编号。

$v[i].nxt$ 表示第 $i$ 个怪物右侧的第一只存活的怪物的编号。

这时，我们定义 $2$ 个集合:$s$ 和 $ss$。

我们先令 $s$ 表示上这一轮攻击中牺牲的怪物，$ss$ 表示上一轮攻击中存活下来的怪物,$flag[i]$ 表示第 $i$ 个怪物是否退场。

初始化：

```cpp
for(int i=1;i<=n;i++){
   ss.insert(i);
   flag[i]=1;
}

```

这里解释一下，$flag[i]$ 的值为 $1$ 时，表示第 $i$ 个怪物还未退场；$ss$ 中应先放进所有元素，因为第一轮攻击时，所有怪物都必须参与。


紧接着，我们枚举每一轮攻击。

第一步：枚举 $ss$ 中的怪物，及上一轮攻击中存活下来的怪物，并判断该怪物会不会被左右两边的怪物攻击而死亡，如果会，我们将这个怪物进行永久标记，表示该怪物已经退场，并将该怪物放进 $s$ 中。

第二步：枚举完后，我们将 $ss$ 清空，并枚举 $s$ 中的怪物，及上一轮攻击中牺牲的怪物。这时，我们将双向链表进行修改：

```cpp
for(set<int>::iterator iter=s.begin();iter!=s.end();++iter){
   v[v[*iter].pre].nxt=v[*iter].nxt;
   v[v[*iter].nxt].pre=v[*iter].pre;
}
```
修改完双向链表后，我们再次跟新 $ss$ 的值。

但这时，我们不难发现如果在这一轮中，第 $x$ 个怪物还没有退场，说明第 $x+1$ 个怪物和第 $x-1$ 个怪物的攻击之和小于等于 $d[x]$。如果第 $x+1$ 个怪物和第 $x-1$ 个怪物在这一轮攻击中都没有退场的话，那么在下一轮攻击中，第 $x$ 个怪物也不会退场。

知道了这些，我们就只需把这一轮攻击中退场的怪物的左侧的怪物和这一轮攻击中退场的怪物的右侧的怪物丢到 $ss$ 里就行了。但是记得，如果这一轮攻击中退场的怪物的左侧的怪物和这一轮攻击中退场的怪物的右侧的怪物已经退场的话，就不要再丢到 $ss$ 里。这样就可以让原本的 $85$ 分蹦到 $100$ 分。

最后呢，我们要把 $s$ 给清空，并重复以上步骤直至枚举完每一轮攻击。

#### code:

```cpp
#include <bits/stdc++.h>
using namespace std;
void write(long long x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
	return;
}
long long read(){
	long long x = 0,f = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9'){
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
int t,n,tot,st,last;
bool flag[300010];
long long a[300010],d[300010];
struct node{
	int pre;
	int nxt;
}v[300010];
set<int>s;
set<int>ss;
set<int>::iterator iter;
signed main(){
	t=read();
	while(t--){
		n=read();
		tot=n;
		last=n;
		for(int i=1;i<=n;i++){
			a[i]=read();
			if(i==1)v[i].pre=-1;
			else v[i].pre=i-1;
			if(i==n)v[i].nxt=-1;
			else v[i].nxt=i+1;
		}
		for(int i=1;i<=n;i++){
			d[i]=read();
			ss.insert(i);
			flag[i]=1;
		}
		for(int k=1;k<=n;k++){
			if(tot!=0 && tot!=1){
				s.clear();
				int temp=st;
				for(iter=ss.begin();iter!=ss.end();++iter){
					if(d[*iter]-a[v[*iter].pre]-a[v[*iter].nxt]<0){
						s.insert(*iter);
						flag[*iter]=0;
					}
				}
				ss.clear();
				for(iter=s.begin();iter!=s.end();++iter){
					v[v[*iter].pre].nxt=v[*iter].nxt;
					v[v[*iter].nxt].pre=v[*iter].pre;
					if(flag[v[*iter].pre])ss.insert(v[*iter].pre);
					if(flag[v[*iter].nxt])ss.insert(v[*iter].nxt);
					tot--;
				}				
			}
			write(last-tot);
			putchar(' ');
			last=tot;
		}
		putchar('\n');
	}
	
	return 0;
}
```




---

## 作者：joe_zxq (赞：6)

# Part 1 题面翻译

$n$ 只怪物排成一排，第 $i$ 只怪物的攻击值是 $a_i$，防御值是 $d_i$。

怪物们将进行 $n$ 轮攻击，每次攻击操作如下：

- 每只活着的怪物将对自己左边和右边最近的**还活着**的怪物进行 $a_i$ 的攻击。
- 对于每只怪物，若它在本轮攻击中收到了**超过** $d_i$ 的攻击，它便会死去。

你需要求出每轮攻击分别有多少只怪物会死去。

# Part 2 解法思路

首先，让我们来设置需要的变量：

- $n$ 表示怪物的数量。

- 数组 $a$ 和 $d$ 分别表示怪物的攻击值和防御值。

- 数组 $l$ 和 $r$ 分别表示怪物左边和右边最近的还活着的怪物下标。
- 数组 $f$ 表示每只怪物是否活着。
- 数据结构 $x$ 和 $y$ 分别表示当前轮结束后所有还活着的怪物下标和当前轮死去的所有怪物下标。由于 set 自带去重功能，这里选择使用 set 存储便可以降低时间复杂度，优化代码。

接着，让我们设计算法过程：

1. 输入数据，并将 $f$ 还有 $l$ 和 $r$ 进行初始化。起初每只妖怪都是活着的，故 $f$ 全部为 $1$，第 $i$ 只怪物左边和右边最近的活着的怪物下标就是 $i-1$ 和 $i+1$。需要注意的细节是，$l_1$ 和 $r_n$ 是没有意义的，此处赋值为 $0$，以免多次出现问题。
2. 进行 $n$ 轮操作。首先，我们枚举每一个 $x$ 中存活的怪物。对于每只怪物 $u$，检查它在当前轮中是否会死，即 $a_{l_u}+a_{r_u}$ 是否超过 $d_u$。若这只怪物会死，就将它的下标放到 $y$ 中，并将 $f_u$ 的值更新为 $0$。接着，我们枚举 $y$ 中当前轮死去的怪物，并更新 $l$ 和 $r$。这时候，由于这只怪物已经死了，那它原先右边的左边变成了它的左边，而它原先左边的右边变成了他的右边。然后我们再看它的左边和右边是否还活着，若是活着，将其插入到 $x$ 中。而我们所求的答案即为每轮操作后 $y$ 的长度。

# Part 3 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, a[300033], d[300033], l[300033], r[300033];
bool f[300033];

void solve() {
	set<ll> x, y;
	cin >> n;
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
		f[i] = 1;
	}
	for (ll i = 1; i <= n; i++) {
		cin >> d[i];
		l[i] = i - 1;
		r[i] = i + 1;
		x.insert(i);
	}
	l[1] = r[n] = 0;
	while (n--) {
		for (ll u : x) {
			if (a[l[u]] + a[r[u]] > d[u]) {
				y.insert(u);
				f[u] = 0;
			}
		}
		cout << (ll)y.size() << " ";
		x.clear();
		for (ll u : y) {
			l[r[u]] = l[u];
			r[l[u]] = r[u];
			if (f[l[u]]) {
				x.insert(l[u]);
			}
			if (f[r[u]]) {
				x.insert(r[u]);
			}
		}
		y.clear();
	}
	cout << endl;
}

int main() {

	ll tc;
	cin >> tc;
	while (tc--) {
		solve();
	}

	return 0;
}
```

---

## 作者：Genius_Star (赞：2)

### 思路：

本题和 [P7912 [CSP-J 2021] 小熊的果篮](https://www.luogu.com.cn/problem/P7912) 思路很像。

直接暴力事件复杂度为 $O(N^2)$，明显不可取。

考虑使用双向链表维护，定义 $l_i$ 表示当前 $i$ 号怪物左边怪物的编号 $r_i$ 表示当前 $i$ 号怪物右边怪物的编号。

初始时：

- 对于 $2 \le i \le n$，则 $l_i=i-1$；$l_1=0$。

- 对于 $1 \le i < n$，则 $r_i=i+1$；$r_n=0$。

考虑将当前或者的怪物存入一个集合中，每次只维护被杀死的怪物，然后对于每一个死亡的怪物更新 $l_{r_i},r_{l_i}$ 的值。

最后再将怪物左边和右边活着的怪物重新放入集合中。（因为每一个怪只和左右两只怪有影响，如果当前回合没死，那就不用考虑）

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=300300;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,sum=0,ans=0;
ll a[N],d[N],l[N],r[N];
bool f[N];
set<ll> v,t;
void solve(){
	v.clear();
	n=read();
	sum=0;
	for(int i=1;i<=n;i++){
		f[i]=1;
		v.insert(i);
		a[i]=read();
		l[i]=i-1;
		r[i]=i+1;
	}
	for(int i=1;i<=n;i++)
	  d[i]=read();
	l[1]=r[n]=0;
	while(sum<n){
		sum++;
		for(auto i:v){
			if(a[l[i]]+a[r[i]]>d[i]){
				t.insert(i);
				f[i]=0;
			}
		}
		write(t.size());
		putchar(' ');
		v.clear();
		for(auto i:t){
			l[r[i]]=l[i];
			r[l[i]]=r[i];
			if(f[l[i]])
			  v.insert(l[i]);
			if(f[r[i]])
			  v.insert(r[i]);
		}
		t.clear();
	}
	putchar('\n');
}
int main(){
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	T=read();
	while(T--)
	  solve();
	return 0;
}
```


---

## 作者：Crazyouth (赞：2)

## 分析

赛时时间少，未 AC。赛后经过大佬 happybob 指导才过了。

如果一个怪死了，受影响的只有它周围的两个怪，因此考虑开两个 set，分别为 $st_1,st_2$，记录着活着的怪与该回合下来将死的怪。第一轮前先把所有 $1\sim n$ 的数加入 $st_1$，把受到伤害大于护盾值的加入 $st_2$。每回合进行的时候，将所有死亡的怪左右的怪（前提是它们活着）加入一个 vector 中，这些怪是受到了影响的怪，若它们受到的伤害大于护盾值，加入 $st_2$。

考虑如何维护 $st_1,st_2$。回合进行的时候，发现如果一连串怪都死了，和它们一个一个死没有区别，所以每死一个怪，将它左右两边（也就是在 $st_1$ 中它的位置的前一个元素与后一个元素）的怪受到的伤害更改，然后在 $st_1$ 中删除自己，这样如果接下来死了一个相邻的怪，它照样可以影响到之前的怪的相邻两边。

综上，最后的答案是 $st_2$ 的大小。

最后，多测不清空，爆零两行泪；清空用 memset，TLE 两行泪。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int a[N],d[N],nd[N];
void solve()
{
	set<int> st1,st2;
	int n;
	cin>>n;
	a[n+1]=0;
	for(int i=1;i<=n;i++) cin>>a[i],st1.insert(i);
	for(int i=1;i<=n;i++) cin>>d[i];
	for(int i=1;i<=n;i++) nd[i]=a[i-1]+a[i+1];
	vector<int> v;
	for(int i=1;i<=n;i++) if(nd[i]>d[i]) st2.insert(i);
	for(int i=1;i<=n;i++)
	{
		v.clear();
		int res=st2.size();
		for(auto&j:st2)
		{
			auto it1=st1.find(j),it2=it1;
			if(it2!=--st1.end()) it2++;
			if(it1!=st1.begin())
			{
				it1--;
				int idx=*it1;
				nd[idx]-=a[j];
				if(j!=*it2) nd[idx]+=a[*it2];
			}
			if(*it2!=j)
			{
				nd[*it2]-=a[j];
				if(*it1!=j)
				nd[*it2]+=a[*it1];
			}
			if(!st2.count(*it1)) v.push_back(*it1);
			if(!st2.count(*it2)) v.push_back(*it2);
			st1.erase(st1.find(j));
		}
		st2.clear();
		for(auto&j:v)
		{
			if(nd[j]>d[j])
			st2.insert(j);
		}
		cout<<res<<' ';
	}
	cout<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
} 

---

## 作者：Zemu_Ooo (赞：1)

赛场上其实没想出来，但后面才想出来这种比较优解。

首先对于每只怪物，需要知道它左边和右边最近的存活怪，存俩数组分别记录每个怪物左侧和右侧最近的怪物的索引即可。存储索引后还需要计算它在每轮中受到的总伤害。这可以通过查看它左侧和右侧最近的存活怪物的攻击力来完成。

在每轮结束时，继续检查每只怪物是否因受到的伤害超过其防御力而死亡。对于每只死去的怪物更新它左右邻居的邻居关系。

为了避免重复检查，用个集合来记录可能需要更新的怪。此外还要个数组来标记已经死亡的怪物避免重复处理。

这种方法下每轮中最多检查所有怪物一次（最坏情况），所以时间复杂度是 $O(n)$。但总体上，由于每个怪物最多只被检查一次，整个算法的时间复杂度是 $O(n)$。蛮好的（


```cpp
#include <iostream>
#include <vector>
#include <set>
using namespace std;

// 计算特定怪物受到的伤害
int get_damage(const vector<int>& a, const vector<int>& l, const vector<int>& r, int id) {
    int damage = 0;
    if (l[id] != -1) damage += a[l[id]];
    if (r[id] != -1) damage += a[r[id]];
    return damage;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
    	cin >> n;
    	vector<int> a(n), d(n), l(n), r(n), ans(n), vis(n);
    	// 读入怪物的攻击力和防御力
    	for (int i = 0; i < n; ++i) cin >> a[i];
    	for (int i = 0; i < n; ++i) cin >> d[i];
    	// 初始化每个怪物的左右邻居
    	for (int i = 0; i < n; ++i) {
        	l[i] = i - 1;
        	r[i] = (i + 1 < n) ? i + 1 : -1;
    	}

    	set<int> update;
    	// 初始状态，确定第一轮会死亡的怪物
    	for (int i = 0; i < n; ++i) {
        	if (get_damage(a, l, r, i) > d[i]) {
            	update.insert(i);
        	}
    	}

    	// 对每一轮进行处理
    	for (int round = 0; round < n; ++round) {
        	vector<int> to_die;
        	// 找出这一轮要死亡的怪物
        	for (int id : update) {
            	if (!vis[id] && get_damage(a, l, r, id) > d[id]) {
                	to_die.push_back(id);
            	}
        	}
        	// 记录这一轮死亡的怪物数量
        	ans[round] = to_die.size();
        	// 更新怪物状态
        	update.clear();
        	for (int id : to_die) {
            	vis[id] = 1;
            	if (l[id] != -1) r[l[id]] = r[id];
            	if (r[id] != -1) l[r[id]] = l[id];
            	if (l[id] != -1) update.insert(l[id]);
            	if (r[id] != -1) update.insert(r[id]);
        	}
    	}

    	// 输出每轮死亡的怪物数量
    	for (int i = 0; i < n; ++i) {
        	cout << ans[i] << " \n"[i == n - 1];
    	}
    }
    return 0;
}
```

---

## 作者：Halberd_Cease (赞：1)

~~明明 E 要抽象很多，为什么赛事 D 比 E 少呢？~~

考虑模拟。纯模拟是 $O(n^2)$ 的，考虑优化。

我们发现，由于一个怪只受左右两只怪的影响，如果一个回合内这个怪左右两个怪都没死，并且两只怪也打不死它，那这只怪就不用考虑。

然后我们最开始枚举所有怪，然后把第一轮死了的怪的左边和右边拿出来在第二轮考虑（显然，只有这些怪的左右两边怪物发生了变化，其它的怪这轮没有死，下一轮也肯定不会死），以此类推，由于一个怪只会死一次，所以被考虑的怪总数量也是线性的，时间复杂度 $O(n)$ 可过。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l[1000010],r[1000010];
int a[1000010],d[1000010];
int dead[1000010];
int t[1000010];
void work()
{
    int n;
    cin>>n;
    vector<int>opt,tmp;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        l[i]=i-1;
        r[i]=i+1;
        dead[i]=0;
        opt.push_back(i);
    }
    for(int i=1;i<=n;i++)
    {
        cin>>d[i];
    }
    d[0]=d[n+1]=1e15;
    a[0]=a[n+1]=0;
    for(int turn=1;turn<=n;turn++)
    {
        int ans=0;
        for(auto x:opt)t[x]=0;
        for(auto x:opt)
        {
            if(dead[x])continue;
            int ll=l[x],rr=r[x];
            if(a[ll]+a[rr]>d[x])
            {
                ans++;
                //cout<<x<<"!!!";
                tmp.push_back(x);
            }
            //cout<<x<<' '<<ll<<' '<<rr<<'\n';
        }
        opt.clear();
        for(auto x:tmp)
        {
            dead[x]=1;
            int ll=l[x],rr=r[x];
            if((!t[ll])&&ll>=1)opt.push_back(ll);
            if((!t[rr])&&rr<=n)opt.push_back(rr);
            t[ll]=t[rr]=1;
            r[ll]=rr;
            l[rr]=ll;
        }
        tmp.clear();
        cout<<ans<<' ';
    }
    cout<<endl;
}
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        work();
    }
}
```

---

## 作者：huangrenheluogu (赞：0)

简单链表。只需要注意到一个性质：每个怪物死亡之后，只有左/右两只怪物在下一轮受到的攻击会有影响。

所以第二轮开始，如果遍历了 $n$ 个怪，那么上一轮至少死了 $\dfrac{n}{2}$ 个怪，这样可以保证复杂度。

复杂度是 $O(n)$ 的，每个怪死后最多只会多遍历两个怪。

可惜我多测数组每清空，WA 了。

看代码的时候发现我调试过程还挺好玩的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5, inf = 2e9 + 5;
int T, n;
struct node{
    int a, d, fro, nxt, id;
}a[N];
vector<int>di;
vector<node>b;
bool vis[N];
inline void solve(){
    for(int i = 1; i <= n; i++){
        //printf("Round %d\n", i);
        for(auto x : b){
            //printf("x %d : defense = %d, fro %d : attack = %d, nxt %d : attack = %d\n", x.id, x.d, x.fro, a[x.fro].a, x.nxt, a[x.nxt].a);
            if(x.d < a[x.fro].a + a[x.nxt].a){
                di.push_back(x.id);
                //printf("x %d : die on Round %d\n", x.id, i);
            }
            vis[x.id] = 0;
        }
        if(di.size() == 0){
            for(int j = i; j <= n; j++) printf("0 ");
            puts("");
            return ;
        }
        printf("%d ", (int)di.size());
        b.clear();
        for(auto x : di){
            a[x].id = 0;
        }
        for(auto x : di){
            a[a[x].fro].nxt = a[x].nxt;
            a[a[x].nxt].fro = a[x].fro;
        }
        for(auto x : di){
            if(a[a[x].fro].id && !vis[a[x].fro]){
                b.push_back(a[a[x].fro]);
                vis[a[x].fro] = 1;
                //printf("%d -> %d\n", x, a[x].fro);
            }
            if(a[a[x].nxt].id && !vis[a[x].nxt]){
                b.push_back(a[a[x].nxt]);
                vis[a[x].nxt] = 1;
                //printf("%d -> %d\n", x, a[x].nxt);
            }
        }
        //for(int i = 1; i <= n; i++) printf("%d : fro = %d, nxt = %d\n", i, a[i].fro, a[i].nxt);
        di.clear();
    }
    puts("");
}
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i].a);
        }
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i].d);
        }
        b.clear();
        for(int i = 1; i <= n; i++) a[i].fro = i - 1, a[i].nxt = i + 1, a[i].id = i;
        a[0].d = a[n + 1].d = inf;
        a[0].a = a[n + 1].a = a[0].id = a[n + 1].id = 0;
        a[0].nxt = 1, a[n + 1].fro = n;
        for(int i = 1; i <= n; i++) b.push_back(a[i]);
        solve();
    }
    return 0;
}
/*
1
2
1 2
1 1
*/
```

---

