# [ABC260D] Draw Your Cards

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc260/tasks/abc260_d

$ 1 $ から $ N $ が書かれた $ N $ 枚のカードが裏向きで積まれた山札があり、上から $ i $ 枚目のカードには整数 $ P_i $ が書かれています。

この山札を使って、以下の行動を $ N $ ターン繰り返します。

- 山札の一番上のカードを引いて、そこに書かれた整数を $ X $ とする。
- 場に見えている表向きのカードであって書かれた整数が $ X $ 以上であるもののうち、書かれた整数が最小のものの上に、引いたカードを表向きで重ねる。もし場にそのようなカードがなければ、引いたカードをどれにも重ねずに表向きで場に置く。
- その後、表向きのカードが $ K $ 枚重ねられた山が場にあればその山のカードを全て食べる。食べられたカードは全て場から消滅する。

各カードについて、何ターン目に食べられるか、あるいは最後まで食べられないかを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ K\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ P $ は $ (1,2,\dots,N) $ の順列 ( $ (1,2,\dots,N) $ を並べ替えて得られる列 ) である

### Sample Explanation 1

この入力では、 $ P=(3,5,2,1,4),K=2 $ です。 - $ 1 $ ターン目に、 $ 3 $ が書かれたカードが他のカードに重ねられずに表向きで場に置かれます。 - $ 2 $ ターン目に、 $ 5 $ が書かれたカードが他のカードに重ねられずに表向きで場に置かれます。 - $ 3 $ ターン目に、 $ 2 $ が書かれたカードが $ 3 $ が書かれたカードの上に表向きで重ねられます。 - この時点で上から $ 2,3 $ が書かれたカードが表向きで重ねられた山が $ K=2 $ 枚に達したので、両カードは食べられます。 - $ 4 $ ターン目に、 $ 1 $ が書かれたカードが $ 5 $ が書かれたカードの上に表向きで重ねられます。 - この時点で上から $ 1,5 $ が書かれたカードが表向きで重ねられた山が $ K=2 $ 枚に達したので、両カードは食べられます。 - $ 5 $ ターン目に、 $ 4 $ が書かれたカードが他のカードに重ねられずに表向きで場に置かれます。 - $ 4 $ が書かれたカードは、最後まで食べられませんでした。

### Sample Explanation 2

$ K=1 $ である場合、全てのカードは場に置かれたターンに食べられます。

## 样例 #1

### 输入

```
5 2
3 5 2 1 4```

### 输出

```
4
3
3
-1
4```

## 样例 #2

### 输入

```
5 1
1 2 3 4 5```

### 输出

```
1
2
3
4
5```

## 样例 #3

### 输入

```
15 3
3 14 15 9 2 6 5 13 1 7 10 11 8 12 4```

### 输出

```
9
9
9
15
15
6
-1
-1
6
-1
-1
-1
-1
6
15```

# 题解

## 作者：adpitacor (赞：4)

主要的问题在如何模拟那“一些牌堆”上。

其他题解似乎侧重使用数组进行辅助，没有充分发挥 STL 的力量。

**我会 STL！**

最直观的方法是使用 `set` 存储表示牌堆的 `stack<int>`，并实现按栈顶自动排序。这需要手动写一个按栈顶比较栈的仿函数类型 `cmp`：

```
struct cmp{
    using arg_t=const stack<int>&; //避免不必要的参数复制
    bool operator () (arg_T p,arg_T q)const{
        return p.top()<q.top();
    }
};
```

然后定义 `set<stack<int>,cmp>`。

但这比较麻烦。我们可以使用 `map`：定义 `map<int,stack<int>>`，其键值即为栈的栈顶（由程序实现保证）。这么做还有一个好处：在放置新牌时需要在容器上调用 `upper_bound` 找到新牌所属的牌堆，使用 `map` 的话可以**直接将牌的编号**作为参数，而 `set` 要求**以编号构造一个** `stack` 作为参数。

具体模拟流程可以看代码。

不管是用 `set` 还是 `map`，都不免会引发顾虑：考虑往牌堆放置新牌的操作，其对应向容器中的一个栈压入新元素，而这需要将栈取出修改再放回，这会涉及栈的**复制**，导致效率的低下。

直接进行赋值，当然会导致复制。**然而可以避免**。大多数 STL 容器都定义了 `swap` 成员函数，（大多数情况下）可以 $O(1)$ 交换两个容器的内容。也就是说，对于两个相同类型的 STL 容器 `p` 和 `q`，如果需要把 `q` 的内容赋给 `p` 且 `q` 在赋值之后就可以废弃，则可以通过 `p.swap(q)` 进行赋值。（当然，如果你嫌难看，也可以用 `std::swap(p,q)`，在这里两者等价）

于是，对于每张牌，对栈的修改是 $O(1)$ 的，主要耗时 $O(\log{n})$ 在容器上；而每张牌只会被弹出栈 $O(1)$ 次（可能为 $0$）；总时间复杂度 $O(n \log{n})$。

代码：

```
#include<iostream>
#include<stack>
#include<map>
using namespace std;
int n,k,t[200010],top;
std::map<int,stack<int>> mp;
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>top;
        auto it=mp.upper_bound(top);
        if(it!=mp.end()){
            //能找到已有的牌堆，需要将栈搬到 top 处
            mp[top].swap(it->second); //保证修改的复杂度
            mp.erase(it);
        }
        auto &stk=mp[top]; //若没有找到，则这里的 mp[top] 会自动新建空牌堆
        stk.push(top); //在牌堆上放牌
        if(stk.size()==k){
            for(;!stk.empty();stk.pop())t[stk.top()]=i;
            mp.erase(top);
        }
    }
    for(int i=1;i<=n;i++){
        //为零则输出 -1，非零则原样输出
        cout<<t[i]-(!t[i])<<'\n';
    }
    return 0;
}
```

---

## 作者：hjyowl (赞：3)

本题是一道非常烦人的模拟题。

### 题目大意：

题面说的很清楚，不需要再讲了。

### 暴力思路：

定义一个动态数组，里面的元素是一个栈（没错能这么定义），然后根据题意模拟即可，然后超时了十二个点。

代码：

```cpp
// LUOGU_RID: 175370647
#include <bits/stdc++.h>
using namespace std;
int n,m;
const int N = 1000010;
int a[N];
int c[N];
bool die[N];
int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
	memset(c,-1,sizeof c);
	vector<stack<int> >vec;
	int timestamp = 0;
	for (int i = 1; i <= n; i ++ ){
		 ++ timestamp;
		 bool st = 0;
		 int res = 1e9;
		 int k = -1;
		for (int j = 0 ; j < vec.size(); j ++ ){
			if (vec[j].top() > a[i] && vec[j].top() < res && vec[j].size() <= m && !die[j]){
				k = j;
				res = vec[j].top();
				st = 1;
			}
		}
		if (!st || k == -1){
			stack<int>cc;
			cc.push(a[i]);
			vec.push_back(cc);
		//	cout << "new " << vec.size() << endl
			if (m == 1){
				c[a[i]] = timestamp;
				die[vec.size() - 1] = 1;
			}
		}
		else{
			vec[k].push(a[i]);
		//	cout << "add:" << k + 1 << "->" << a[i] << endl;
			if (vec[k].size() == m){
				int t = 0;
				int cnt = 0;
				do{
					cnt ++ ;
					if (cnt == m){
						break;
					}
					t = vec[k].top();
					vec[k].pop();
					c[t] = timestamp;
				}while (cnt <= m);
				c[vec[k].top()] = timestamp;
				die[k] = 1;
			}
		}
	}
	for (int i = 1; i <= n; i ++ ){
		cout << c[i] << endl;
	}
	return 0;
} 
```

### 优化：

发现可以直接二分求出满足条件的堆，所以说我们可以考虑维护堆顶，由于这些数字不同，我们还可以用一个哈希表映射堆顶对应的堆的编号，然后每次直接对于堆顶集合进行二分即可（此处使用容器 set 即可）。

代码：

```cpp
// LUOGU_RID: 175376189
// LUOGU_RID: 175370647
#include <bits/stdc++.h>
using namespace std;
int n,m;
const int N = 1000010;
int a[N];
int c[N];
int tp[N];
bool die[N];
int main(){
	cin >> n >> m;
	set<int>s; 
	map<int,int>mp;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
	memset(c,-1,sizeof c);
	vector<stack<int> >vec;
	int timestamp = 0;
	int d = 0;
	for (int i = 1; i <= n; i ++ ){
		 ++ timestamp;
		 bool st = 0;
		 int res = 1e9;
		 auto it = s.lower_bound(a[i]);
		if (it == s.end()){
			stack<int>cc;
			mp[a[i]] = d ++ ;
			cc.push(a[i]);
			vec.push_back(cc);
			s.insert(a[i]);
			tp[vec.size() - 1] = a[i];
		//	cout << "new " << vec.size() << endl
			if (m == 1){
				c[a[i]] = timestamp;
				die[vec.size() - 1] = 1;
				s.erase(a[i]);
			}
		}
		else{
			int k = mp[*it];
			int d = mp[tp[k]];
			mp[tp[k]] = -1;
			if (s.count(tp[k])){
				s.erase(tp[k]);
			}
			vec[k].push(a[i]);
			s.insert(a[i]);
			tp[k] = a[i];
			mp[a[i]] = d;
		//	cout << "add:" << k + 1 << "->" << a[i] << endl;
			if (vec[k].size() == m){
				int cf = vec[k].top();
				int t = 0;
				int cnt = 0;
				do{
					cnt ++ ;
					if (cnt == m){
						break;
					}
					t = vec[k].top();
					vec[k].pop();
					c[t] = timestamp;
				}while (cnt <= m);
				c[vec[k].top()] = timestamp;
				die[k] = 1;
				s.erase(cf);
			}
		}
	}
	for (int i = 1; i <= n; i ++ ){
		cout << c[i] << endl;
	}
	return 0;
} 
```

---

## 作者：appear_hope (赞：3)

注意：$P$ 序列是全排列，意味着没有重复元素。

用一个 `set` 去维护每个牌堆的牌顶元素（为什么用 `set`，因为 `set` 能够处理第一个 $\ge x$ 的元素），顺便维护数字 $i$ 在第几个牌堆和第 $i$ 个牌堆有多少张卡牌即可。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

set<int> s;
int n, k, tot, a[N], f[N], siz[N], ans[N];

int main(){
  cin >> n >> k;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }
  for(int i = 1; i <= n; i++){
    if(s.empty() || s.lower_bound(a[i]) == s.end()){
      s.insert(a[i]);
      siz[++tot]++;
      f[a[i]] = tot;
    }
    else{
      auto it = s.lower_bound(a[i]);
      int id = f[*it];
      s.erase(it), s.insert(a[i]);
      siz[id]++, f[a[i]] = id;
    }
    int g = f[*s.lower_bound(a[i])];
    if(siz[g] == k){
      ans[g] = i;
      s.erase(s.lower_bound(a[i]));
    }
  }
  for(int i = 1; i <= n; i++){
    cout << (!ans[f[i]] ? -1 : ans[f[i]]) << '\n';
  }
  return 0;
}
```

---

## 作者：_GW_ (赞：3)

## 思路
本题只用考虑堆顶，以及统计答案时需要遍历堆中元素。

于是呢，就只用统计每个堆的堆顶，并用并查集记录每个堆的元素。

但这样依旧会超时，时间复杂度是 $n^2$ 的。

可以使用 set 优化，这样查找时可以使用二分，因为 set 会自动排序。

更新答案时，暴力更新即可。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
//                     答案数组     每个堆的大小 
int num,val,n,m,k,fa[N],res[N],a[N],si[N];
//              并查集数组    输入数组 
set<int> s;
set<int>::iterator x;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		x=s.upper_bound(a[i]);
		int u=*x;
		if(x!=s.end())//无需新开堆 
		{
			s.insert(a[i]);
			s.erase(u);//替换堆顶 
			fa[a[i]]=u;
			si[a[i]]=si[u]+1;//更新 
		}
		else//需要新开堆 
		{
			s.insert(a[i]);
			si[a[i]]=1;//新开堆
		}
		if(si[a[i]]==m)//需要更新答案了 
		{
			s.erase(a[i]);//删除并更新 
			u=a[i];
			for(int j=1;j<=m;j++)
			{
				res[u]=i;
				u=fa[u];
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!res[i]) cout<<-1<<endl;
		else cout<<res[i]<<endl;
	}
	return 0;
}
```


---

## 作者：沉石鱼惊旋 (赞：3)

### 题目翻译

依次摸 $n$ 张卡片，第 $i$ 个卡片上写的 $p_i$，$p_i$ 是 $1$ 到 $n$ 的一个排列。

维护一些牌堆，如果 $p_i$ 大于所有堆顶的牌，那么新开一堆只有 $p_i$。

否则在所有堆顶的牌，找到大于 $p_i$ 最小的一张，把 $p_i$ 放到这个堆的堆顶。

如果这一堆有恰好 $K$ 张牌，把这 $K$ 个牌的数字都标记上当前的时间 $i$，并把这堆删掉。

最后输出每个数字被标记的时间，如果没有被标记过就是 $-1$。

### 题目思路

如果我们真的模拟题意去开栈，肯定会 boom 的。

观察题意可得，所有操作只考虑牌堆顶，且卡片只要进入牌堆就不会变动。

因此我们只需维护牌堆顶即可。但这样时间复杂度仍然很高，我们可以把牌堆顶存入一个 set，每次查询即为 $\mathcal O(\log n)$ 了。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int fa[200005],id,c[200005],d[200005];
bool f[200005];
int ans[200005];
set<int>s;
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(s.size()==0||a[i]>*s.rbegin())
		{
			s.insert(a[i]);
			id++;
			fa[a[i]]=id;
			c[id]=a[i];
			d[id]++;
			if(d[id]==k)
			{
				f[id]=1;
				ans[id]=i;
				s.erase(a[i]);
			}
		}
		else
		{
			auto it=s.upper_bound(a[i]);
			int x=fa[*it];
			if(f[x]==1)
			{
				continue;
			}
			c[x]=a[i];
			d[x]++;
			fa[a[i]]=x;
			s.erase(it);
			s.insert(a[i]);
			if(d[x]==k)
			{
				f[x]=1;
				ans[x]=i;
				s.erase(a[i]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<(ans[fa[i]]==0?-1:ans[fa[i]])<<endl;
	}
	return 0;
}
```



---

## 作者：kczw (赞：2)

# 题意简述
有 $n$ 个数并给定一个 $n$ 的排列，令其为放置数字的顺序。同时给定 $k$ 为放置数字的限制。

放置数字的规则为：

- 数字的放置可以当作栈，堆叠放置。如果某个栈的元素个数等于 $k$，删去此栈及其所有元素

- 每次放置数时，放置在已放置且未删去的栈中某个栈顶比此数大的栈的顶部，放置在栈顶最小的满足条件的栈上。如果不存在，另开一栈。
# 思路
根据题意，可以知道我们需要维护几个东西，包括但不限于：

- 不同的栈
- 栈顶元素查询栈
- 查询栈顶元素最小的比放置数大的

看到要通过栈顶元素查询到栈，所以可以想到 map 套 stack 来维护。

同时，查询的问题也就迎刃而解了，直接使用 `upper_bound()` 函数查找即可。
# 实现
```cpp
#include<iostream>
#include<stack>
#include<map>
using namespace std;
map<int,stack<int>> card;
int n,k,f[200005];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1,a;i<=n;i++){
		scanf("%d",&a);
		auto id=card.upper_bound(a);
		if(id!=card.end()){
			swap(card[a],id->second);
			card.erase(id);
		}auto &stk=card[a];
		stk.push(a);
		if(stk.size()==k){
			while(!stk.empty())f[stk.top()]=i,stk.pop();
			card.erase(a);
		}
	}for(int i=1;i<=n;i++)printf("%d\n",f[i]?f[i]:-1);
	return 0;
}
```

---

## 作者：max666dong123 (赞：2)

## 思路

纯模拟会 [TLE](https://www.luogu.com.cn/paste/o065eibk)，所以代码需要优化，很容易发现我们只需要记录堆顶的元素和它下一个元素就可以了，最后更改堆中的元素时不断 $i=under_i$ 就行了。可是这样还是不行，还是过不了，问题是出在找堆顶上，要一个一个遍历一遍才找得到，所以我们用 ``set`` 来记录堆顶元素，查找用``upper_bound``就行了。

## 代码解析

$under_i$：元素 $i$ 在堆中的下一个元素。

$ans_i$：元素 $i$ 对应的答案。

$cnt_i$：元素 $i$ 为堆顶时堆中的元素。

## 完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
const int N=2e5+10;
int n,k;
int a[N];
int under[N];
int ans[N];
int cnt[N];
set<int>s;
signed main(){
	IOS;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		set<int>::iterator it=s.upper_bound(a[i]);
		int x=*it;
		if(it==s.end()){
			s.insert(a[i]);
			cnt[a[i]]=1;
		}
		else{			
			s.insert(a[i]);
			s.erase(x);
			under[a[i]]=x;
			cnt[a[i]]=cnt[x]+1;

		}		
		if(cnt[a[i]]==k){
			int x=a[i];
			s.erase(a[i]);
			for(int j=1;j<=k;j++){
				ans[x]=i;
				x=under[x];
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<(ans[i]==0?-1:ans[i])<<endl;
	}
	return 0;
}
```

---

## 作者：_shine_ (赞：2)

## 1. 题目大意
依次摸 $n$ 张卡牌，并且维护一些牌堆，如果找到大于 $p_i$ 最小的一张，那就把 $p_i$ 放到这个堆的堆顶，反之就新开一堆，放入 $p_i$。如若牌堆个数等于 $k$，就删去这堆牌。现在问你在 $n$ 步中，每张牌删去的时间
## 2. 思路
最容易想到，考虑本题目中使用暴力。

在每一次枚举没一个数 $p_i$，同时在此，枚举牌堆中的其他数 $p_j$，判断 $p_j$ 是否小于 $p_i$，并且纳入牌堆即可。

### [TLE Code](https://atcoder.jp/contests/abc260/submissions/41266317)

但是注意，在本题中，用此思路会使得本题不通过，思考优化本题，不难发现，在本题目中，如若 $p_i<k$，则不用枚举 $p_i$，因为就所有连着从 $p_i$ 到 $1$，也不可能使得牌堆大小大于 $k$，再交即可通过。
### [AC Code](https://atcoder.jp/contests/abc260/submissions/41266375)
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}
const int maxn=2e5+10;
int n,k,p[maxn];
int ans[maxn];
bool vis[maxn];
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i){
		p[i]=read();
	}
	for(int i=1;i<=n;++i){
		if(vis[p[i]]==0 && p[i]>=k){
			vis[p[i]]=1;
			vector<int>e;
			e.push_back(p[i]);
			int now=k-1,last=p[i],last_time=i;//last_time用来记录时间，last记录牌堆的上一个，now防止牌堆个数大于k
			for(int j=i+1;now>0 && j<=n;++j){
				if(last>p[j] && vis[p[j]]==0){//枚举牌堆中的数
					last=p[j];
					vis[p[j]]=1;
					now--;
					e.push_back(p[j]);
					last_time=j;//更新，记录新的p[j]
				}
			}
			if(now==0){//输出
				for(int j=0;j<e.size();++j){
					ans[e[j]]=last_time;//记录牌堆删除时间
				}
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(ans[i]==0)ans[i]=-1;//为了避免初始化，所以在此判断p[i]是否在牌堆中被删除。
		printf("%d\n",ans[i]);//输出
	}
	return 0;
}
```


---

## 作者：Harrylzh (赞：1)

## 思路

把每堆牌的堆顶放在 set 里模拟即可，如果此牌大于所有元素就新加一堆，否则用这张牌替换之前的顶牌。把同一个牌堆中的所有牌放进一个并查集中，把顶牌设置为根，就可以直接查询顶牌的答案。牌堆中牌的数量也可以用并查集维护，当达到 $k$ 时就将顶牌从 set 中删除。

## 代码

```cpp
#include<iostream>
#include<set>
using namespace std;
int n,k;
set<int> st;
int fath[1000000+5],sz[1000000+5];
int gtf(int i)
{
	return fath[i]==i?i:fath[i]=gtf(fath[i]);
}
void mg(int x,int y)
{
	int fx=gtf(x),fy=gtf(y);
	if(fx!=fy) fath[fx]=fy,sz[fy]+=sz[fx];
}
int sj[1000000+5];
bool uu[1000000+5];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) fath[i]=i,sz[i]=1;
	for(int i=1;i<=n;i++)
	{
		int p;
		cin>>p;
		sj[p]=i;
		if(st.empty())
		{
			st.insert(p);
			if(sz[p]==k)
				{
					uu[p]=1;
					st.erase(p);
				}
		}
		else
		{
			if(st.upper_bound(p)==st.end()) st.insert(p);
			else
			{
				mg(*st.upper_bound(p),p);
				st.erase(st.upper_bound(p));
				st.insert(p);
				if(sz[p]==k)
				{
					uu[p]=1;
					st.erase(p);
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(uu[gtf(i)]==0) cout<<"-1\n";
		else cout<<sj[gtf(i)]<<"\n";
	}
	return 0;
}
```

---

## 作者：__YSC__ (赞：1)

# 题目描述

有 $N$ 张牌，第 $i$ 张牌上写着 $P_i$，从上到下摆在桌上。不断重复以下操作：

- 找到最小的一个堆顶使得堆顶 $\ge P_i$。
- 如果没有这样的牌堆，将它直接放在桌上，新建一个牌堆
- 如果存在一个牌堆中牌数等于 $K$，移除这个牌堆

对于每个 $1\le i \le N$，求它在第几次操作时被移除。如果它没被移除，输出 $-1$。


# 思路

使用 `set` 维护一个牌堆的堆顶、牌数、编号。每次操作时二分求解，并记录所属牌堆，对每个牌堆合并处理即可。

空间复杂度 $O(N)$，时间复杂度 $O(N \log N)$。

## 细节

无。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

int n, k, c[MAXN], ans[MAXN], tot;
set<pair<int, pair<int, int>>> s;

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> k;
  fill(ans + 1, ans + n + 1, -1);
  for(int i = 1, p; i <= n; ++i) {
    cin >> p;
    set<pair<int, pair<int, int>>>::iterator it = s.lower_bound({p, {0, 0}});
    if(it == s.end()) {
      c[p] = ++tot;
      if(k == 1) {
        ans[tot] = i;
      }else {
        s.insert({p, {1, tot}});
      }
    }else {
      c[p] = it->second.second;
      int sz = it->second.first;
      s.erase(it);
      if(sz + 1 == k) {
        ans[c[p]] = i;
      }else {
        s.insert({p, {sz + 1, c[p]}});
      }
    }
  }
  for(int i = 1; i <= n; ++i) {
    cout << ans[c[i]] << "\n";
  }
  return 0;
}

```

---

## 作者：Symbolize (赞：1)

# 算法判别
不难发现，现在还有的堆的堆顶大小是单调的，所以在寻找覆盖在哪个堆上时可以用二分。剩下的就是暴力。

# 如何暴力
1. 首先判断是否需要新开一个堆，因为堆顶单调，直接将此卡牌与最后一个堆的堆顶进行比较，如果它比最后一个堆的堆顶还大，新开一个堆。否则找到最小的大于此卡牌的堆顶，把它覆盖上去。
2. 判断是否已经够消掉了，如果是，则将此堆删除，记录答案，把此堆的后面的所有堆往前移。

# 具体的实现方法
## 变量
1. $id$ 堆的个数。
2. $x_i$ 第 $i$ 个堆的堆顶。
3. $cnt_i$ 写着 $i$ 的卡牌所在的堆在放入这张卡牌后的此堆卡牌数。
4. $pre_i$ 写着 $i$ 的卡牌覆盖在写着哪个数字的卡牌上面。
4. $ans_i$ 写着 $i$ 的卡牌在何时被消掉。
## 局部解析
如果要新开堆：
```cpp
x[++id]=p;//堆个数加1
cnt[p]=1;//第一个元素
tmp=id;//覆盖的堆的编号，方便后面的删除操作
```
如果不新开堆：
```cpp
tmp=upper_bound(x+1,x+id,p)-x;//覆盖的堆的编号，最小的大于此卡牌的堆顶
cnt[p]=cnt[x[tmp]]+1;//个数比上一个多1
pre[p]=x[tmp];//记录覆盖在谁上面
x[tmp]=p;//新的堆顶
```
如果要删除堆：
```cpp
while(p)//记录答案
{
	ans[p]=i;//答案赋值
	p=pre[p];//前一个卡牌
}
rep1(j,tmp,id-1) x[j]=x[j+1];//补上空缺，tmp后面的堆集体前移
--id;//堆个数减1
```
## 完整代码
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e6+10;
using namespace std;
int n,k,p,ans[N],id,x[N],cnt[N],pre[N];
signed main()
{
		memset(ans,-1,sizeof ans);//初始化
		cin>>n>>k;
		rep1(i,1,n)
		{
			cin>>p;
			int tmp;
			if(p>x[id])
			{
				x[++id]=p;//堆个数加1
				cnt[p]=1;//第一个元素
				tmp=id;//覆盖的堆的编号，方便后面的删除操作
			}
			else
			{
				tmp=upper_bound(x+1,x+id,p)-x;//覆盖的堆的编号，最小的大于此卡牌的堆顶
				cnt[p]=cnt[x[tmp]]+1;//个数比上一个多1
				pre[p]=x[tmp];//记录覆盖在谁上面
				x[tmp]=p;//新的堆顶
			}
			if(cnt[p]==k)
			{
				while(p)//记录答案
				{
					ans[p]=i;//答案赋值
					p=pre[p];//前一个卡牌
				}
				rep1(j,tmp,id-1) x[j]=x[j+1];//补上空缺，tmp后面的堆集体前移
				--id;//堆个数减1
			}
		}
		rep1(i,1,n) cout<<ans[i]<<endl;//输出
		return 0;//收场
}
```

---

## 作者：Ivan422 (赞：0)

题目大意：模拟 $n$ 个牌堆，每次有一次插入，先找到第一个堆顶大于等于 $p_i$ 的堆，放到顶部。要是堆大小为 $k$ 就处理掉这个牌堆，并把这个堆里全部数都标上 $i$，最后就把标记输出，要是没有处理过这张牌就输出 $-1$。

首先想到用 `set` 模拟多个牌堆的堆顶，这个数据结构有自动排序，就可以使用内置的二分函数找到对应的牌堆。这里有一个问题，这个数据结构是自动去重的，但是由于题目已经告诉我们牌上的数是一个排列，就算有去重也不会使用。

接下来如何处理牌堆内部呢？我们可以把这题看做多个单项链表，只要长度超了就用链表一个一个删除并标记。手写的链表比较复杂，可以使用一个数组 $ld$ 表示这个牌下面的一张牌，要是位于最底部就为 $0$，还可以方便删除循环的终止。

之后，直接模拟即可。

先找到可以放置的牌堆地址（内置函数的默认返回值）存入 $fd$ 中。要是 $fd$ 为 `set` 的尾部，即没有找到，就得新开一个牌堆了。再使用一个数组 $sz$ 记录牌堆大小，大小等于下面的牌的大小之和加 $1$。要是是新开的牌堆就默认为一张牌，即 $sz_{p_i}=1$。接下来的就是模拟链表操作了，新牌堆不用处理。把 $ld_{p_i}$ 设置为 $fd$ 对应的值，即在链表的头插入 $p_i$。还要注意由于牌堆堆顶的更改，要删除 $fd$。接着，无论如何操作都会放牌，直接把牌加入 `set` 内即可。再是删除，首先是删堆顶，要在 `set` 内处理，接着就是一张一张删除标记了，具体见代码。完成这一串操作后，直接输出答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,k,p[N],ld[N],sz[N],et[N];
set<int>st;
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){cin>>p[i];}
    for(int i=1;i<=n;i++){
        auto fd=st.upper_bound(p[i]);
        if(fd==st.end()){
            sz[p[i]]=1;
        }else{
            sz[p[i]]=sz[*fd]+1;
            ld[p[i]]=*fd;
            st.erase(fd);
        }
        st.insert(p[i]);
        if(sz[p[i]]==k){
            st.erase(p[i]);
            for(int er=p[i];er;er=ld[er])et[er]=i;
        }
    }
    for(int i=1;i<=n;i++){
        if(et[i]==0)cout<<-1<<'\n';
        else cout<<et[i]<<'\n';
    }
    return 0;
}
```

---

## 作者：HEzzz (赞：0)

[题目跳转键](https://www.luogu.com.cn/problem/AT_abc260_d)

前置芝士：集合运用。

## 解析

首先我们看到 $p_i$ 是一个 $1$ 到 $n$ 的全排列，所以 $p_i$ 是互不相同的，这让我们想到了集合。

嗯确实，我们可以用集合去维护牌堆顶的卡片，来快速地二分求出大于 $p_i$ 最小的一张。而对于题目中的放牌操作和删牌操作，我们可以定义，$pre_i$ 表示卡片数字 $i$ 在牌堆中下面一个是什么数字，$cnt_i$ 表示卡片数字 $i$ 在牌堆中下面有多少个数字，类似于链表的思想。有了这些数组，就容易去维护牌堆了。


最后用 $ans_i$ 记录答案即可。

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _antirep(i,a,b) for(int i=(a);i>=(b);--i) 
using namespace std;
typedef long long LL;
typedef double db;
const int N=2e5+5,M=1e5+5;
int n,k,a[N],pre[N],cnt[N],ans[N],tme=1;
set<int>s;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	_rep(i,1,n) cin>>a[i];
	_rep(i,1,n)
	{
		set<int>::iterator it=s.upper_bound(a[i]);
		if(it!=s.end())
		{
			s.insert(a[i]);
			pre[a[i]]=*it;
			cnt[a[i]]=cnt[*it]+1;
			s.erase(*it);
		}
		else
		{
			s.insert(a[i]);
			cnt[a[i]]=1;
		}
		if(cnt[a[i]]==k)
		{
			int x=a[i];
			do
			{
				s.erase(x);
				ans[x]=tme;
				x=pre[x];
			}
			while(x);
		}
		tme++;
	}
	_rep(i,1,n) 
	{
		if(ans[i]==0) cout<<"-1\n";
      //注意没有被删掉是输出-1
		else cout<<ans[i]<<"\n";
	}
	return 0;
}
```

代码时间复杂度 $O(n \log n)$。

---

## 作者：Anby_ (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/AT_abc260_d)。  
### 思路
根据题目进行模拟，由于每一次只对**栈顶元素进行判断**，所以我们可以多开一个数组去维护栈顶元素，判断 $a_i$ 应该放在哪一个栈里，再判断更新后的这个栈是否符合删除的要求。   
但由于直接开数组查找会炸时间，**但是我会 STL**，所以，我们可以用 set 去存储 stack 的栈顶元素，查找就变成了 $O(\log_2{n})$。

### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
stack<int> stk[N];
set<pii> st;
pii tmp;
int n,k,cnt,bomb[N],tot,pos;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>tot;
		auto f=st.upper_bound({tot,0});
		if(f==st.end()) pos=++cnt;
		else tmp=*f,pos=tmp.y,st.erase(tmp);
		stk[pos].push(tot),st.insert({tot,pos});
		if(stk[pos].size()==k){
			while(!stk[pos].empty()) bomb[stk[pos].top()]=i+1,stk[pos].pop();
			st.erase({tot,pos});
		}
	}
	for(int i=1;i<=n;i++) cout<<bomb[i]-1<<endl;
	return 0;
}
```

---

## 作者：Beacon_wolf (赞：0)

## 题目思路
首先思考如何快速找到桌上大于手牌的最小的一张牌。set 里有一个自带的 `lower_bound()`，用来寻找 $\ge $ 某一指定数字的第一个数。它使用起来还是比较方便的，所以我们可以用 set 储存当前桌上可以看到的牌，用数组存储每堆牌堆各有的牌。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
set<int> st; //st里储存每堆牌顶的牌
vector< vector<int> > c(200010); //c里储存每堆牌堆各有的牌 
vector<int> p(200010),ans(200010,-1); //p里储存输入的牌 
int main(){
	cin >> n >> k;
	for(int i = 1;i <= n;i++) cin >> p[i];
	for(int i = 1;i <= n;i++){
		auto itr = st.lower_bound(p[i]);
		if(itr == st.end()){ //所有牌顶上都没有比它小的牌，则自成一个牌堆 
			c[p[i]].push_back(p[i]);
			st.insert(p[i]);
		}else{ //有牌顶上有比它小的牌，则将此张牌放到这堆牌的牌顶 
			int x = *itr;
			c[x].push_back(p[i]);
            swap(c[x],c[p[i]]);
			st.erase(itr);
			st.insert(p[i]);
		} 
		if((int)c[p[i]].size() >= k){ //达到吃掉牌的要求 
			for(auto l : c[p[i]]) ans[l] = i; //储存答案 
			c[p[i]].clear();
			st.erase(p[i]);
		} 
	}
	for(int i = 1;i <= n;i++) cout << ans[i] << endl;
    return 0;
}
```

---

## 作者：yujinning (赞：0)

另一篇题解只提到要用 set，没有标明具体适用方法，来具体说明一下。

## 题意

维护两个操作：

* 添加或删除值 $X$ 作为元素。

* 查找大于值 $X$ 的最小元素。

## 解法

使用 set 维护牌堆顶的牌，vector 维护牌堆。

对于每张卡牌 $X$，依据题意模拟，分两类讨论。

* 若 set 中不存在元素 $K\ge X$ 的，则新开一个空间用于维护 $X$。使用内置函数 lower_bound 判断是否存在元素 $K$ ，时间复杂度 $O(\log_{}{n})$。

**注意若 $k=1$ 时，一个元素在入 set 时就应当出 set，需要特判。**

```cpp
set<int>::iterator it=s.lower_bound(x[i]);
int id=*it;
if(it==s.end()){
    s.insert(x[i]);
    p[x[i]].push_back(x[i]);
    if(k==1){
        s.erase(x[i]);
        ans[x[i]]=i;
    }
}
```

* 若 set 中存在最小的元素 $K\ge X$，则将 $X$ 的牌底 标记为 $K$ 的牌底，判断此时此牌底所在牌堆是否已经满，若满则标记此牌堆的所有牌，并使牌堆顶 $X$ 出 set。

此时的时间复杂度为 $O(\log_{}{n})$，注意到出 set 操作最多共执行 $n$ 遍。

```cpp
else{
    s.erase(id);
    s.insert(x[i]);
    fa[x[i]]=fa[id];
    p[fa[id]].push_back(x[i]);
    int siz=p[fa[id]].size();
    if(siz==k){
        for(int j=0;j<siz;j++) ans[p[fa[id]][j]]=i;
        s.erase(x[i]);
    }
}
```

综上，总的时间复杂度为 $O(n\log_{}{n})$，可以通过该题。

----

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200009;
int n,k,x[N],fa[N],ans[N];
vector<int> p[N];
set<int> s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>x[i],fa[i]=i;
	for(int i=1;i<=n;i++){
		set<int>::iterator it=s.lower_bound(x[i]);
		int id=*it;
		if(it==s.end()){
			s.insert(x[i]);
			p[x[i]].push_back(x[i]);
			if(k==1){
				s.erase(x[i]);
				ans[x[i]]=i;
			}
		}
		else{
			s.erase(id);
			s.insert(x[i]);
			fa[x[i]]=fa[id];
			p[fa[id]].push_back(x[i]);
			int siz=p[fa[id]].size();
			if(siz==k){
				for(int j=0;j<siz;j++) ans[p[fa[id]][j]]=i;
				s.erase(x[i]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(ans[i]!=0) cout<<ans[i];
		else cout<<"-1";
		cout<<endl;
	}
	return 0;
}

```

---

