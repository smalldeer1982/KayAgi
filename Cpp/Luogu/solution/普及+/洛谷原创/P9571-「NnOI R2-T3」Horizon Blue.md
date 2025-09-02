# 「NnOI R2-T3」Horizon Blue

## 题目描述

小 C 喜欢在画板上画画。他进行了 $ n $ 次操作，每次操作有如下三种可能：

- ```1 k b``` 代表小 C 绘制了一条解析式为 $ y=kx+b $ 的直线。
- ```2 k b``` 代表小 C 询问你直线 $ y=kx+b $ 与多少条被绘制的直线有**恰好**一个公共点。
- ```3 k b``` 代表小 C 擦除所有与直线 $ y=kx+b $ 有**至少**一个公共点的直线。

**注意：两条重合的直线有无数个交点。**

**注意：询问时重合的直线应分别计算。**

## 说明/提示

**【样例 1 解释】**

第 1 次操作，绘制直线 $ y=x $。

第 2 次操作，绘制直线 $ y=-x $。

第 3 次操作，可以发现直线 $ y=2x+1 $ 与前两条线相交。

第 4 次操作，擦掉所有 $ y=x+3 $ 相交的线，直线 $ y=-x $ 被擦掉。

第 5 次操作，$ y=2x+1 $ 显然与 $ y=x $ 相交。

第 6 次操作，$ y=x+1 $ 与 $ y=x $ 斜率相等，是平行线，不相交。

**【数据范围】**

对于 $ 100\% $ 的数据，$ 1 \le n \le 10^5 $，$ 1 \le |k| \le 10^5 $，$ 0 \le |b| \le 10^5 $。

**提示：本题开启捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c}
\textbf{Subtask} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& n \le 5000 & 27 \r
\textsf2& \vert k\vert,\vert b\vert \le 50 & 21 \r
\textsf3& 无第\ 3\ 类操作 & 13 \r
\textsf4& 第\ i\ 次操作满足\ k=i & 14 \r
\textsf5& 无特殊限制 & 25 \r
\end{array}
$$

在赛后新添加的 hack 测试点将放入 subtask 6。

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
| idea | 船酱魔王 |
| data | 船酱魔王 |
| check | EstasTonne |
| solution | 船酱魔王 |

## 样例 #1

### 输入

```
6
1 1 0
1 -1 0
2 2 1
3 1 3
2 2 1
2 1 1```

### 输出

```
2
1
0```

## 样例 #2

### 输入

```
10
1 1 0
1 1 0
2 1 1
2 1 0
2 2 5
3 1 0
2 2 5
1 2 3
1 3 4
2 3 5```

### 输出

```
0
0
2
0
1```

# 题解

## 作者：NaN_HQJ2007_NaN (赞：15)

观察发现，两条直线有**正好**一个公共点当且仅当 $k$ 不同。

而两条直线有**至少**一个公共点当且仅当 $k$ 不同或 $k,b$ 都相同（重合）。

考虑模拟，用一个 `set` 存当前直线有哪些 $k$，对于每一个 $k$ 用一个 `multiset` 存 $b$。

- 操作 $1$：插入一条直线，正常更新。

- 操作 $2$：输出直线总数减去 $k$ 与询问相同的直线数量。

- 操作 $3$：遍历 `set` 中与 $k$ 不相等的元素，将对应的 `multiset` 清空，再删除与询问直线重合的，更新直线总数。

因为 $k$ 可能为负，所以要将坐标统一加上一个值。

每条直线会只会被加入一次，删除一次，所以总复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,nn=1e5;
multiset<int>st[N];
set<int>s;
vector<int>t;
int n;
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	int tot=0;
	for(int i=1;i<=n;++i){
		int op,k,b;cin>>op>>k>>b;
		if(op==1)st[k+nn].insert(b),s.insert(k+nn),++tot;
		else if(op==2)cout<<tot-st[k+nn].size()<<endl;
		else{
			set<int>::iterator it;t.clear();
			for(it=s.begin();it!=s.end();++it){
				int w=(*it);if(w==k+nn)continue;
				tot-=st[w].size();st[w].clear();t.push_back(w);
			}
			for(int i=0;i<t.size();++i)s.erase(t[i]);
			tot-=st[k+nn].count(b);st[k+nn].erase(b);
		}
	}
  return 0;
}
```


---

## 作者：a1a2a3a4a5 (赞：14)

# 没有思维难度的暴力
## 1. 题意
### 操作1
我们把直线的 $ k $ 和 $ b $ 存在一个 ` vector ` 里，这里的细节下面补充。
### 操作2
初二的应该学过函数和图像，下面是关于这些东西的一点点特性：

- 当 $ k $ 相等的两个直线，他们平行或重合。

- 当 $ k $ 和 $ b $ 都相等的两个直线，他们重合，也就是有很多很多的公共点。

- 在同一个平面内，两条不平行不重合的直线恰好有一个交点。

- 如果 $ b $ 相等，那么当 ` x==0 ` 时，`y==b ` 所以当两个直线的 $ b $ 相等时，必定有一个交点。

所以这里我们只需要把与当前 $ k $ 相同的直线数量都减去就是与当前直线**恰好**有一个交点的直线数量。
然后关于如何找到与当前 $ k $ 相同的直线数量，我用 ` map ` 开了一个桶存着 $ k $ 的数量。

在这里说一下：我代码中的 ` unordered_map ` 可以看成更快的 ` map`，真的很快，有时候可以多过好几个测试点。
### 操作3
“**至少**”说明重合和有一个交点的直线都要删去，我直接用的 ` vector ` 暴力删，只因其他的都不是很会。

这里还要说到 ` vector ` 的单点删除的一个优化。我们普通删除是这样的：
```cpp
a.erase(a.begin+i);
```
下面一种是优化：
```
swap(a.begin()+i,a.back())；
a.pop_back()；
```
这个的原理是把当前要删除的数与最后一位交换，然后删除最后面的数。

~~我不是很清楚他的原理，只知道有点快，上网搜了一下也找不到答案。~~
## 2. 优化
上面的直接写出来已经可以得到惊人的 $ 54 $ 分了！下面是一些小优化，加上就 $ 100 $ 分了！

通过观察，我们发现我们操作 $ 1$、$2 $ 的时间复杂度都很小，所以只要优化操作 $ 3$：
我们在删除的是 $ k $ 不相等的或者是 $ b $ 相等的，之前开了个桶存的 $ b $ 可以判断是否还有相同的 $ b$，桶 $ k $ 可以判断是否还有不同的 $ k$，如果没有了就 ` break`，然后就可以直接 $ 100 $ 分！
## 3. 代码
主食很详细：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,zong;// zong 存的是总共现在有的线段的数量。 
vector<int> zk,zb;// zk 存 k[i] 的值，zb 存 b[i] 的值。 
unordered_map<int,int> tk,tb;// tk 存 k[i] 的数量，tb 存 b[i] 的数量 。 
signed main()
{
	cin>>n;
	for(int i1=1,op,k,b;i1<=n;i1++)
	{
		cin>>op>>k>>b; 
		if(op==1)
			zong++,tk[k]++,tb[b]++,
			zk.push_back(k),zb.push_back(b);
		else if(op==2) cout<<zong-tk[k]<<'\n';
		//总共的线段减去平行和重合的线段，就是恰好有一个交点的线段。 
		else if(op==3)
		{
			if(tk[k]==zong&&tb[b]<=0) continue;//优化 
			for(vector<int>::iterator k1=zk.end()-1,b1=zb.end()-1;k1>=zk.begin();k1--,b1--)
				//迭代器，相当于遍历，主要是快。 
				if(*k1!=k||*b1==b)
				{
					zong--,tk[*k1]--,tb[*b1]--;
					// 把操作 1 那反过来。（毫无思维难度） 
					swap(*k1,zk.back()),zk.pop_back(),
					swap(*b1,zb.back()),zb.pop_back();
					if(tk[k]==zong&&tb[b]<=0) continue;//优化 
				}
		}
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：7)

分析一下三个操作让我们维护什么。

- 操作一是简单的插入。

- 操作二本质上是整体减去斜率为 $k$ 的线段的数量。

- 操作三需要删除所有斜率不为 $k$ 的线段，还有斜率为 $k$ 常数为 $b$ 的线段。

这题是一道 STL 爽题啊！我用了三个 STL 搞定。

首先我们发现统计斜率为 $k$ 的线段，统计斜率为 $k$ 常数为 $b$ 的线段很简单，但是对于操作三的删除特别恶心，那怎么维护呢？

首先我们肯定需要一个 `map`，叫做 $m$，$m_k$ 表示当前斜率为 $k$ 的线段数量，那么操作三我们可以直接清空它，再加入斜率为 $k$ 的线段总数减去斜率为 $k$ 常数为 $b$ 的线段的数量即可。

我们还需要维护斜率为 $k$ 常数为 $b$ 的线段的数量，可以考虑在 `map` 里存二元组，但我发现斜率的数据范围很小，可以直接开 `2e5` 个 `map` 维护不同斜率下 $b$ 的出现次数，这样删除更好写。

对于维护删除我的做法是设了一个集合 $d$ 表示当前不需要清空的斜率，每次读入一个斜率时，如果需要清空我们就清空。

那么对于操作三，我们只需要清空集合再加入 $k$ 即可。

还有一些细节看我代码应该可以看懂。

时间复杂度显然 $\mathcal O(n\log n)$。
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5;
map<LL,LL>ma[N*2+5];
map<LL,LL>m;
set<LL>d;
LL n,op,k,b,cnt;
int main()
{
	cin>>n;
	for(int i=-N;i<=N;i++)d.insert(i);
	while(n--)
	{
		cin>>op>>k>>b;
		if(!d.count(k))
		{
			ma[k+N].clear();
			d.insert(k);
		}
		if(op==1)
		{
			m[k]++;
			ma[k+N][b]++;
			cnt++;
		}
		else if(op==2)
		{
			cout<<cnt-m[k]<<endl;
		}
		else 
		{
			LL t=m[k];
			m.clear();
			d.clear();
			m[k]=t-ma[k+N][b];
			ma[k+N][b]=0;
			cnt=m[k];
			d.insert(k);
		}
	}
}
```

---

## 作者：Thenyu (赞：6)

[原题](https://www.luogu.com.cn/problem/P9571)

[更好的阅读体验](https://www.cnblogs.com/thenyu/articles/17649408.html)

题目给出了三个操作

- ```1 k b``` 代表小 C 绘制了一条解析式为 $ y=kx+b $ 的直线。
- ```2 k b``` 代表小 C 询问你直线 $ y=kx+b $ 与多少条被绘制的直线有**恰好**一个公共点。
- ```3 k b``` 代表小 C 擦除所有与直线 $ y=kx+b $ 有**至少**一个公共点的直线。

学过一次函数的都知道，两条直线如果 $k$ 值不相等，那么这两条直线一定会相交且只有一个公共点。如果 $k$ 值相等且 $b$ 值不相等，那么这两条直线平行，如果 $b$ 值相等，那么重合。

于是对于操作一，我们可以用一个数组累计 $k$ 值相等的直线有多少条，并且累计 $k,b$ 两值相等的直线有多少条（因为有可能存在重合，所以不光要累计 $k$ 值相同的直线的数量，也要累计 $k,b$ 两个值都相同，即相互重合的直线的数量）。顺便也要记录一下 $k,b$ 两个值以及目前画板上存在的直线数量，后面操作要用到。

对于操作二，我们可以将操作一中存下来的画板上存在的直线数量减去当前 $k$ 值的直线的数量，即 $k$ 值与题目给的 $k$ 值不同的直线数量，也就是题目要求的直线 $ y=kx+b $ 与多少条被绘制的直线有**恰好**一个公共点。

对于操作三，直接枚举前面操作一存下的不同的 $k,b$ 值，然后判断 $k$ 值是否相同，不同就抹去，相同就存回这个数组中，最后再抹去重合的直线。

然后这道题就轻松的解决了喏。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
int n,obt,K,B,tmp,k[100005],b[100005],len[N+5],cnt;
map<pair<int,int>,int>c;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d%d",&obt,&K,&B);
		K+=100000;
		if(obt==1)
		{
			++c[{K,B}];//累计k,b两个值相等的直线有多少条
			++len[K];//累计k值相等的直线有多少条 
			if(c[{K,B}]==1)k[++cnt]=K,b[cnt]=B;//记录k,b两个值，方便后面操作三 
			++tmp;//记录画板上已有的直线数量 
		}
		else if(obt==2)printf("%d\n",tmp-len[K]);
		else
		{
			int sum=cnt;
			cnt=0;
			for(int i=1;i<=sum;++i)
			{
				if(k[i]!=K)len[k[i]]=0,c[{k[i],b[i]}]=0;//k值不同的直线就全部抹去 
				else k[++cnt]=k[i],b[cnt]=b[i];//k值相同就存回记录k,b值的数组
			}
			tmp=len[K];//画板上剩下的直线只有为k值的直线数量
			tmp-=c[{K,B}];//也要减去重合的直线，才是最后画板剩下的直线数量
			len[K]-=c[{K,B}];//k值直线数量也要减去重合的直线
			c[{K,B}]=0;//抹去重合的直线 
		}
	}
	return 0;
}
```


---

## 作者：玄学OIER荷蒻 (赞：4)

感觉大家用的基本上是单个 `map`，没有像我这么作死开双重 `map` 卡了几十分钟才过。

先分析题目，第一个操作可以用 `map` 直接增加来实现，普普通通。

第二个是恰好一个，那么只要 $k$ 不相同的都是恰好一个。

第三个操作是擦除至少一个，那么不仅会擦除 $k$ 不相同的，$k$ 相同且 $b$ 也相同的也会擦除。

分析后，人类的智慧开始，考虑开个这个东西（其实没必要）：

`map<int,map<int,int>>`

（注意一下在真正打代码的时候两个 `>` 是要隔开的，不然会编译错误）

第一个操作可以直接加。（这个用法可以直接视为二维数组）

第二个操作可以记录一个 `cnt` 代表大 `map` 里的总大小。

还需要用 `map<int,int>` 记录每一个小 `map` 里的大小。

第三个可以把大 `map` 清空再加上和 $k$ 相等的那个小 `map` 再修改，记录每一个小 `map` 大小的 `map` 也同理，最好再减去 $k$ 和 $b$ 都相等即可。

于是很容易写出一份代码，最后复杂度是 $O(\verb'玄学')$。

快乐的发现，被[卡](https://www.luogu.com.cn/record/121766056)了，TLE 在最后一个点。

分析一会儿以后，最后添加上的 `map` 可能很大，于是我们可以先用 `find` 然后再用左右两个 `erase` 即可。

于是快乐的发现，又被[卡](https://www.luogu.com.cn/record/121771751)了，原因应该是这东西复杂度或者说常数爆炸。

但是我们发现，最后一个点第一次被卡，第二次 A 了！

于是我们考虑分大小考虑：

如果要留的 `map` 大小超过某个值（我第一次随便试了个 $100$ 结果过了）就用第二种方法，否则第一种。

[AC记录](https://www.luogu.com.cn/record/121775586)。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,map<int,int> > mp;
map<int,int> mpk,sz;
int zsz=0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	while (n--){
		int i,k,b;
		cin>>i>>k>>b;
		if (i==1){
			mp[k][b]++;
			sz[k]++;
			zsz++;
		}
		else if (i==2){
			cout<<zsz-sz[k]<<'\n';
		}
		else{
			zsz=sz[k];
			if (mp[k].size()>100){
				map<int,map<int,int> >::iterator iter=mp.find(k);
				mp.erase(mp.begin(),iter);
				iter=mp.find(k);
				iter++;
				mp.erase(iter,mp.end());
			}
			else{
				mpk=mp[k];
				mp.clear();
				mp[k]=mpk;
			}
			zsz-=mp[k][b];
			sz[k]-=mp[k][b];
			int lll=sz[k];
			sz.clear();
			sz[k]=lll;
			mp[k][b]=0;
		}
	}
	return 0;
}
```


---

## 作者：Special_Tony (赞：4)

[题目传送门](/problem/P9571)
# 思路
先发个和题解区其它题解不一样的思路。

这题我们可以定义一个变量 $sum$，代表当前的直线数量。再定义一个 map 变量 $tot$，其中 $tot_i$ 表示题目中的 $k$ 为 $i$ 的直线数量。最后定义一个 map 套 map 变量 $mp$（当然你也可以用 `map <pair <int, int>, int>` 的形式），其中 $mp_{i,j}$ 表示 $k$ 为 $i$ 且 $b$ 为 $j$ 的直线数量。

我们设 $op$ 是问题类型，当 $op=1$ 时，我们只要对 $sum,tot_k,mp_{k,b}$ 分别加上 $1$ 即可。

当 $op=2$ 时，题目要求**恰好**有一个公共点。而要使一条直线恰好与要求的直线只有一个公共点，则要使两条直线是不平行的，即 $k$ 不相等，所以答案就成了 $sum-tot_k$。

当 $op=3$ 时，题目要求**至少**有一个公共点。而要使一条直线至少与要求的直线一个公共点，则要使两条直线是不平行的，或是两条线完全重合，即 $k$ 不相等，或是 $k$ 与 $b$ 都相等，所以我们在更改的时候可以先设一个临时的 map 变量 $temp$，用于存储 $mp_k$，因为只有 $mp_k$ 才可能被保留。而直线总数 $sum$ 变成了 $tot_k-mp_{k,b}$。接着，我们把 $mp$ 和 $tot$ 都清空了，把 $tot_k$ 赋为 $sum$，因为只有 $k$ 相同的才能保留下来。现在，我们把刚才存下来的 $temp$ 赋值到 $mp_k$ 里，并把 $mp_{k,b}$ 赋为 $0$。

但是，提交后你会发现 TLE 在最后一个点了，为什么？因为清空太慢了，要知道，clear 函数可以 $O(n)$ 的！所以我们就干脆不清空了，开 $10^5$ 个 map 套 map，反正只要没用过它就不会占空间。

但是你还是在最后一个点 MLE 了。看来占用的空间还是太多了，说明用的轮数（即 $op=3$ 的次数）太多了，这时候我们考虑不要 clear 了，直接将 $mp_i$ 和 $mp_{i+1}$ 交换即可。这样，就 AC 了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, op, k, b, sum, maxx, now;
map <int, int> tot[100005];
map <int, map <int, int>> mp[100005];
int main () {
	cin >> n;
	while (n --) {
		cin >> op >> k >> b;
		if (op < 2)
			++ tot[now][k], ++ sum, ++ mp[now][k][b];
		else if (op < 3)
			cout << sum - tot[now][k] << '\n';
		else
			++ now, swap (mp[now][k], mp[now - 1][k]), tot[now][k] = sum = tot[now - 1][k] - mp[now][k][b], mp[now][k][b] = 0;
	}
	return 0;
}
```

---

## 作者：_wsq_ (赞：4)

分析题目所给的表达式，可以发现一条直线的斜率仅取决于 $k$，进而得出以下结论：

对于两条直线：

- 若 $k$ 不相等，则这两条直线有且仅有一个交点。

- 若 $k$ 相等，$b$ 不相等，则这两条直线没有交点。

- 若 $k$ 和 $b$ 均相等，则这两条直线有无数个交点（重合）。

根据该结论，可将 3 种操作转变为：

1. 添加一对有序数对 $(k,b)$

2. 输出所有第一个值不等于给定的 $k$ 的有序数对的数量

3. 删除所有第一个值不等于给定的 $k$ 的有序数对和所有两个值分别等于给定的 $k$ 和 $b$ 的有序数对

结合 2 操作和 3 操作的特点，为方便操作，考虑使用 map 套 multiset，map 的所有关键字为所有当前作为有序数对的第一个值存在的值，其对应的值为一个包含所有与其对应的有序数对的第二个值的 multiset（虽然各位 dalao 肯定能写出来更方便的 stl）。

附上 C++ 代码：

```cpp
#include <iostream>
#include <set>
#include <map>
using namespace std;
int main(){
    int n,size=0;//维护当前有多少条线，方便进行 2 操作
    map<int,multiset<int> > m;
    cin>>n;
    for(int i=1;i<=n;i++){
        int op,k,b;
        cin>>op>>k>>b;
        if(op==1){
            if(m.count(k)){
                m[k].insert(b);//已存在，直接添加到 multiset
            }
            else{
                multiset<int> s;
                s.insert(b);
                m[k]=s;//未存在，添加新的关键字
            }
            size++;
        }
        else{
            if(op==2){
                if(m.count(k)){
                    cout<<size-m[k].size()<<endl;
                }
                else{
                    cout<<size<<endl;
                }//直接用总数减去 k 相等的数量即可
            }
            else{
                for(map<int,multiset<int> >::iterator it=m.begin();it!=m.end();){
                    if(it->first==k){
                        size-=it->second.size();
                        it->second.erase(b);//删除该 multiset 里所有与 b 相同的值
                        size+=it->second.size();//对 size 进行维护
                        it++;
                    }
                    else{
                        size-=it->second.size();//对 size 进行维护
                        m.erase(it++);//直接删除关键字
                    }
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：COsm0s (赞：4)

## $\mathcal{Solution}$

我们将三个操作分开来看。

首先设 $mp_{k,b}$ 为 $kx+b$ 这条直线出现了几次，$len_k$ 为斜率为 $k$ 的直线的数量，$cnt$ 为当前所有直线的数量。

+ 对于操作一，直接对 $k,b$ 进行存储，注意此时三个统计变量（数组）都要更新。由于本题可能为负，所以用 `map` 就行了。

+ 对于操作二，“只有一个公共点”即当且仅当两条直线斜率不同，所以答案即为 $cnt-len_k$。

+ 对于操作三，与当前直线“至少有一个公共点”即为两条直线斜率不同或两条直线完全重合，所以暴力清空 $len,mp$ 数组，只留下 $k$ 斜率且 $b≠nowb$ 的直线。

由于每条边只会被清空一次，所以本题复杂度 $\Theta(n\log n)$。

注意，`unordered_map` 内部实现是 `hash`，所以开二维 `unordered_map` 会被卡成 $\Theta(n)$ 的级别，所以直接使用 `map` 即可。

## $\mathcal{Code}$
```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int N = 1e6 + 5, inf = 2e5;
map<int, unordered_map<int, int> > mp;
map<int, int> len;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int n, cnt = 0;
	cin >> n;
	while(n --) {
		int opt, k, b;
		cin >> opt >> k >> b;
		if(opt == 1) mp[k][b] ++, cnt ++, len[k] ++;
		if(opt == 2) cout << cnt - len[k] << '\n';
		if(opt == 3) {
			for(auto it = len.begin(); it != len.end(); it ++) 
				if(it -> first != k) mp.erase(it -> first), cnt -= len[it -> first];
			len.clear();
			cnt -= mp[k][b], len[k] = cnt, mp[k][b] = 0;
		}
	}
	return 0;
}
```


---

## 作者：SJZ2010 (赞：4)

做这题前你需要知道的东西：

- [直线的解析式](https://baike.baidu.com/item/%E7%9B%B4%E7%BA%BF%E8%A7%A3%E6%9E%90%E5%BC%8F/10738726?fr=ge_ala)是什么。

- 两条直线什么时候有一个交点，什么时候有无数个。

这题可以用 `map` 做。`map` 可以快速地删除、修改。

具体做法：

首先定义一个 `map`：

```cpp
std::map< int, std::map< int, int > > lines;
```

这个 `map` 存储什么呢？举个例子：`lines[k][b]` 表示解析式为 $y=kx+b$ 的直线的**数量**。

1. 操作 1

	将 `lines[k][b]` 增加 $1$ 即可。
    
2. 操作 2

	先定义一个整型 $sum$ 表示总共有多少条直线，统计一下斜率为 $k$ 的直线的数量 $cnt$，输出 $sum-cnt$ 即可，注意此时操作 1 时 $sum$ 也要增加 $1$。
    
3. 操作 3

	再定义一个临时的 `map`：
    
   ```cpp
   std::map< int, std::map< int, int > > temp;
   ```
   $temp$ 的其它值不变，$temp_k$ 赋值为 $lines_k$，再将 $lines$ 赋值为 $temp$ 就可以完成删除操作，再将与直线 $y=kx+b$ 重合的直线删去即可。
   
如果你还没明白，可以看看代码：

```cpp
#include <cstdio>
#include <set>
#include <map>

typedef long long ll;

std::map< int, std::map< int, int > > lines;

int n, opt, k, b, sum;

int main(){
	scanf("%d", &n);
	while(n--){
		scanf("%d %d %d", &opt, &k, &b);
		if(opt == 1){
			lines[k][b]++;
			sum++;
		}else if(opt == 2){
			int the_size_of_k(0);//下面是用迭代器遍历 map
			for(auto it=lines[k].begin();it != lines[k].end();it++)//计算斜率为 k 的直线数量
				the_size_of_k += (*it).second;
			printf("%d\n", sum-the_size_of_k);
		}else if(opt == 3){
			int the_size_of_k(0);
			for(auto it=lines[k].begin();it != lines[k].end();it++)
				the_size_of_k += (*it).second;
			sum = the_size_of_k;
			std::map< int, std::map< int, int > > temp;
			temp[k] = lines[k];//先只留下斜率为 k 的
			lines = temp;//让 temp 值留下斜率为 k 的直线后，再赋值回去，达到删除其它直线的效果
			sum -= lines[k][b];
			lines[k].erase(b);//有无数个交点的也要删掉
		}
	}
	return 0;
}
```

	

---

## 作者：One_JuRuo (赞：3)

## 思路

首先分析一下操作 $2,3$。

对于操作 $2$，容易发现如果 $k$ 相等，就只可能是平行或者重合，显然不满足，那么答案就是总剩余直线数减去 $k$ 相同的直线数。

对于操作 $3$，发现只有平行的直线不会被删去，也就是只有 $k$ 相同而 $b$ 不同的直线不会被删去。

如此一来，这道题核心做法就很明显了，但是具体实现有点麻烦。

首先，我想到的是拿个 map 存，但是很快发现这样做，前两个操作还好，但是对于操作 $3$ 的删除，实在是太慢了，会 TLE。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,op,k,b,sum;
map<pair<int,int>,int>m;
map<int,int>m1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d%d",&op,&k,&b);
		if(op==1) m[make_pair(k,b)]++,m1[k]++,sum++;//统计这个k，b出现的次数和k出现的次数以及总直线数
		else if(op==2) printf("%d\n",sum-m1[k]);
		else
		{
			int t=m1[k]-m[make_pair(k,b)];
			m1.clear(),sum=m1[k]=t;//只有同k不同b的能留下来
			for(auto j:m) if(j.first.first!=k||j.first.second==b) m[j.first]=0;//m中存的只能挨个遍历删除了
		}
	}
	return 0;
}
```

已提交，果然 TLE 了两个点，但是一看 subtask 5 也有个点 TLE 了，这代表什么？这代表我们可以用特殊性质~~偷奸耍滑~~多拿一点部分分。

subtask 5 的特殊性质是第 $i$ 此操作 $k=i$。

这样显然没有直线会 $k$ 相同，所以每次删除都必然全部删完，就不用去遍历了。

但是我们怎么直到这个是 subtask 5 的数据了，我们只需要每次判断是否 $k=i$，如果都是的话，就特殊处理，这样的话我们就可以多获得 $14$ 分了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,op,k,b,sum,flag;
map<pair<int,int>,int>m;
map<int,int>m1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d%d",&op,&k,&b),flag=(k==i&&!flag)?0:1;//判断是否满足特殊性质
		if(op==1) m[make_pair(k,b)]++,m1[k]++,sum++;
		else if(op==2) printf("%d\n",sum-m1[k]);
		else
		{
			if(!flag) m.clear(),m1.clear(),sum=0;//满足就特殊处理
			else
			{
				int t=m1[k]-m[make_pair(k,b)];
				m1.clear(),sum=m1[k]=t;
				for(auto j:m) if(j.first.first!=k||j.first.second==b) m[j.first]=0;
			}
		}
	}
	return 0;
}
```

但是最后一个点 TLE 了，这种办法实在是无能为力了，$75$ 分大概就是极限了。

这样的话，我们就需要改改思路了。

显然，这个方法最慢的就是删除了，那么我们可以考虑延迟删除操作，直到每次需要调用或者修改的时候再进行删除。

我们可以用一个数组存它们进行了第几轮的删除操作，再拿个变量储存目前是第几轮删除操作，如果调用这个 $k$ 的数据，就判断记录的是否等于目前的删除操作次数。

这样的话时间复杂度一下子就降下来了，但是还有个问题就是 $k$ 相同 $b$ 相同的直线如何删除。

如果还是用 map 来存的话，一定没办法快速删除，所以我们只能换一种储存方式。

首先想到 multiset，这是一个集合，但是允许相同元素出现，我们只需要直到它的一个功能 erase 就行。

它可以把这个集合所有等于参数的数全部删除，如此一来，我们成功地把时间复杂度降下来了。

~~剩下的，就是敲代码拿下 AC 了！~~

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,op,k,b,num[200005],sum,dfn[200005],cnt;
multiset<int>s[200005];
int main()
{
    scanf("%d",&n);
	while(n--)
	{
        scanf("%d%d%d",&op,&k,&b);
        if(k<0) k+=200001;//因为用了数组，所以需要把负值k板正，只要不重复就好，所以就加成正数好了。
        if(dfn[k]!=cnt) dfn[k]=cnt,num[k]=0,s[k].clear();//判断当前k有没有执行删除操作
		if(op==1) ++num[k],++sum,s[k].insert(b);//记录
		else if(op==2) printf("%d\n",sum-num[k]);
		else dfn[k]=++cnt,num[k]-=s[k].count(b),s[k].erase(b),sum=num[k];//删除
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：3)

线段树可爱。

## 解题思路

记 $f_i$ 表示 $k$ 值为 $i$ 的直线条数，则考虑用线段树维护 $f_i$ 的值。

再额外记录 $book_{i,j}$，用于记录 $k$ 值为 $i$ 且 $b$ 值为 $j$ 的直线条数，因为 $k,b$ 的值可能较大，考虑使用 map 进行维护。

操作 1 可以视为对 $f_k$ 的单点修改，操作时将 $book_{k,b}$ 加 1。

操作 2 可以视为对 $f_{(-\infty,k-1]}$和 $f_{[k+1,-\infty)}$ 的区间查询。

操作 3 可以视为一次对 $f_{(-\infty,k-1]}$和 $f_{[k+1,-\infty)}$ 的区间**覆盖**（因为所有斜率不为 $k$ 的直线全部要清空）以及一次对 $f_k$ 的单点修改。（在删除所有与 $y=kx+b$ 斜率不同而有交点的直线时也要删除所有先前增加的直线 $y=kx+b$，即，使 $f_k$ 减少 $book_{k,b}$ 并将 $book_{k,b}$ 清零）

区间覆盖和修改操作可以使用两个懒标记分别进行维护，而因为 $k$ 的值满足 $1\leq |k| \leq 10^5$，因此每次操作时将 $k$ 增加 $10^5$，区间修改时修改的区间改为 $f_{[0,k-1]}$ 和 $f_{[k+1,2\times 10^5]}$ 即可。（代码中为了防止不必要的问题稍微扩大了这个区间）

一个小细节：因为在对 $f_i$ 进行覆盖时无法及时覆盖 $book_i$ 的值，因此在进行操作 1 和 3 时可以进行判断，如果在查询或修改 $f_i$ 的值时 $f_i=0$，那么可以对 $book_i$ 进行一次 clear，以保证当 $f_i$ 被覆盖后不会调用覆盖前的 $book_{i,j}$。**这也是许多人赛时 54 分的原因，警钟长鸣。**

## 代码

含有双重懒标记的，支持区间覆盖和查询的线段树相信各位都能看懂，就不贴太多注释了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100100;
struct segtree
{
	int l,r,lazy1,lazy2,sum;//lazy1 维护覆盖标记，lazy2 维护修改标记。 
}; 
segtree tree[MAXN*16];
void pushup(long long x)
{
	tree[x].sum=tree[x*2].sum+tree[x*2+1].sum;
	return;
}
void pushdown(long long x)//先处理覆盖操作再处理修改操作。 
{
	if(tree[x].lazy1!=-1)
	{
		tree[x*2].lazy1=tree[x].lazy1;
		tree[x*2].lazy2=0;
		tree[x*2].sum=tree[x].lazy1*(tree[x*2].r-tree[x*2].l+1);
		tree[x*2+1].lazy1=tree[x].lazy1;
		tree[x*2+1].lazy2=0;
		tree[x*2+1].sum=tree[x].lazy1*(tree[x*2+1].r-tree[x*2+1].l+1);
		tree[x].lazy1=-1;
	}
	tree[x*2].lazy2=tree[x].lazy2;
	tree[x*2].sum+=tree[x].lazy2*(tree[x*2].r-tree[x*2].l+1);
	tree[x*2+1].lazy2=tree[x].lazy2;
	tree[x*2+1].sum+=tree[x].lazy2*(tree[x*2+1].r-tree[x*2+1].l+1);
	tree[x].lazy2=0;
	return;
}
void build(long long x,long long l,long long r)
{
	tree[x].l=l;
	tree[x].r=r;
	tree[x].lazy1=-1;
	if(l==r)
	{
		return;
	}
	long long mid=(l+r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	pushup(x);
	return;
}
void update(long long x,long long l,long long r,long long c)
{
	if(tree[x].l==l&&tree[x].r==r)
	{
		tree[x].sum+=c*(r-l+1);
		tree[x].lazy2+=c;
		return;
	}
	long long mid=(tree[x].l+tree[x].r)/2;
	pushdown(x);
	if(l<=mid)
	{
		update(x*2,l,min(mid,r),c);
	}
	if(r>=mid+1)
	{
		update(x*2+1,max(mid+1,l),r,c);
	}
	pushup(x);
	return;
}
void recover(long long x,long long l,long long r,long long c)//新的覆盖操作会覆盖先前的所有操作 
{
	if(tree[x].l==l&&tree[x].r==r)
	{
		tree[x].sum=c*(r-l+1);
		tree[x].lazy1=c;
		tree[x].lazy2=0;
		return;
	}
	long long mid=(tree[x].l+tree[x].r)/2;
	pushdown(x);
	if(l<=mid)
	{
		recover(x*2,l,min(mid,r),c);
	}
	if(r>=mid+1)
	{
		recover(x*2+1,max(mid+1,l),r,c);
	}
	pushup(x);
	return;
}
long long query(long long x,long long l,long long r)
{
	if(tree[x].l==l&&tree[x].r==r)
	{
		return tree[x].sum;
	}
	long long mid=(tree[x].l+tree[x].r)/2,ans=0;
	pushdown(x);
	if(l<=mid)
	{
		ans+=query(x*2,l,min(mid,r));
	}
	if(r>=mid+1)
	{
		ans+=query(x*2+1,max(mid+1,l),r);
	}
	return ans;
}
map<int,int> book[MAXN*2];
int main()
{
	int T,i,j,ta,tb,tc;
	scanf("%d",&T);
	build(1,1,200010);
	while(T--)
	{
		scanf("%d%d%d",&ta,&tb,&tc);
		tb+=100001;
		if(ta==1)
		{
			if(query(1,tb,tb)==0)//记得清空 
			{
				book[tb].clear();
			}
			update(1,tb,tb,1);
			book[tb][tc]++;
		}
		if(ta==3)
		{
			if(query(1,tb,tb)==0)//记得清空 
			{
				book[tb].clear();
			}
			recover(1,1,tb-1,0);
			recover(1,tb+1,200010,0);
			update(1,tb,tb,-book[tb][tc]);
			book[tb][tc]=0;
		}
		if(ta==2)
		{
			printf("%d\n",query(1,1,tb-1)+query(1,tb+1,200010));
		}
	}
	return 0;
}
```

## 闲话

如果您对我的题解有疑问，欢迎再评论区讨论。

如果没有的话也可以评论一句“线段树可爱”以表示对我的支持。

---

## 作者：Aisaka_Taiga (赞：2)

我们开一个 map 来统计线段中 $k,b$ 的出现情况。

然后用结构体来存放直线，准备两个结构体数组，用于删除操作。

对于操作一，我们直接加入，在加入的时候统计一下 $k,b$ 的出现情况。

对于操作二，由于要求恰好一个交点的直线条数，那么我们直接把除了平行以外的所有直线的条数输出即可，也就是下面代码里的 $top-mp1_{k}$。

对于操作三，我们直接遍历当前所有的直线然后把不删的存到另一个结构体数组里面，然后再复制回去，同时重新统计 $k,b$ 的信息即可。

但是这样操作三复杂度太高，考虑到有可能删完当前所有直线信息不变。

我们开一个数组 $vis$，为 $1$ 表示当前斜率也就是 $k$ 值的直线删除过了，$0$ 则是修改过但是没删除过。

我们考虑到每次的 $b$ 可能不同，但是没出现过的 $b$ 的线段要是 $vis_{k}=1$ 也同样没有必要删除，所以最后得到清空的条件为 $vis_{i} \ne 1$ 并且 $mp2_{b}\ne 0$。

由于题目的线段是通过操作一来插入，而且线段少了查询复杂度会变低，所以匀下来是不可能跑到 $O(n^2)$ 的，或许这篇题解以后会被叉掉。

code:

```cpp
#include <bits/stdc++.h>

#define int long long
#define N 1000100
#define endl '\n'

using namespace std;

inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){f=ch!='-';ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return f?x:-x;}

unordered_map<int, int> mp1, mp2;
int n, ans, top, vis[N];
struct sb{int k, b;}e[N], e1[N];

signed main()
{
    n = read();
    for(int i = 1; i <= n; i ++)
    {
        int op = read(), k = read(), b = read();
        if(op == 1)
        {
            e[++ top] = (sb){k, b};
            mp1[k] ++;
            mp2[b] ++;
            vis[k + 100000] = 0;
        }
        if(op == 2) cout << top - mp1[k] << endl;
        if(op == 3)
        {
            if(vis[k + 100000] == 1 && !mp2[b]) continue;
            int top1 = 0, ff = 0;
            for(int i = 1; i <= top; i ++)
                if(e[i].k == k && e[i].b != b)
                    e1[++ top1] = (sb){e[i].k, e[i].b}, ff ++;
            if(ff == top) continue;
            mp1.clear();
            mp2.clear();
            top = top1;
            vis[k + 100000] = 1;
            for(int i = 1; i <= top; i ++) e[i] = e1[i], mp1[e[i].k] ++, mp2[e[i].b] ++;
        }
    }
    return 0;
}
```

---

## 作者：NASFsky (赞：2)

~~这题目名字，音游人狂喜好吧~~  
本题解将根据我的考场心路历程进行解法的讲述。  
## 错解 #1
开题的第一眼，这不简单题吗？只要考虑直线的斜率 $k$ 是否相等就可以判断直线间是否有交点。若 $k$ 不同则必定有交点，用个桶维护一下即可。删除直线时也只需要将 $k$ 值不同的删去即可。  
考场代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum ;
map<int,int>mp;
int main()
{
	scanf("%d",&n);
	for(int i=1,op,k,b;i<=n;i++)
	{
		scanf("%d%d%d",&op,&k,&b);
		if(op==1)
		{
			mp[k]++;
			sum++;
		}
		else if(op==2)printf("%d\n",sum-mp[k]);
		else 
		{
			int res=mp[k];
			mp.clear();
			mp[k]=res;
			sum=mp[k];
		}
	}
}
```
[评测记录](https://www.luogu.com.cn/record/121743177)。喜提 $27$ 分。
## 正解 #1
再回来读了一遍题目，发现操作 $2$ 中的描述为“**恰好**一个公共点”，而操作 $3$ 中为“**至少**一个公共点”。这下发现问题了。因为显然，如果两条直线的 $k$ 和 $b$ 都相同，即这两条直线完全重合时，它们的公共点为无数个，满足“**至少**一个公共点”的限制，而不满足“**恰好**一个公共点”。  
于是我又开了一个桶来维护 $k,b$ 相同的直线个数。  
考场代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum;
map<int,int>mp;
map<pair<int,int>,int>mp1;
int main()
{
	scanf("%d",&n);
	for(int i=1,op,k,b;i<=n;i++)
	{
		scanf("%d%d%d",&op,&k,&b);
		if(op==1)
		{
			mp[k]++;
			mp1[make_pair(k,b)]++;
			sum++;
		}
		else if(op==2)
		{
//			cout<<sum<<" "<<mp[k]<<' '<<mp1[make_pair(k,b)]<<endl;
			printf("%d\n",sum-mp[k]);
		}
		else 
		{
			int res=mp[k]-mp1[make_pair(k,b)];
			mp.clear();
			for(auto t=mp1.begin();t!=mp1.end();t++)
			{
				if(t->first==make_pair(k,b)||t->first.first!=k)t->second=0;
			}
			mp[k]=res;
			sum=mp[k];
		}
	}
}
```
[评测记录](https://www.luogu.com.cn/record/121747174)。喜提 $61$ 分，后两个 Subtask 中的最后一个点都 TLE 了。可恶的捆绑测试！  
不过好在算法的正确性保证了，接下来考虑优化即可。  
## 正解 #2
注意到 Subtask #4 的特殊性质，保证第 $i$ 次操作的 $k=i$，这使得查询时的答案肯定为还存在的直线条数，而每次删除也肯定是将所有直线都删除，可以特判下再拿下 $14$ 分。  
代码略。  
[评测记录](https://www.luogu.com.cn/record/121751889)。此时只挂了一个点却喜提 $75$ 分。  
## 正解 #3
注意到两个 `map` 的时间复杂度都是很大的，显然我们可以想办法去换掉。于是我选择用一个数组去代替我代码中的 $mp$，其中 $mp[k]$ 表示现在斜率为 $k$ 的直线条数。  
关于 $mp1$，我用以下代码进行了替换：
```cpp
struct node{int b,sum;};
vector<node>mp1[2*N];
```
其中 $b$ 即为直线的 $b$，$sum$ 为个数。这样 $mp1[k]$ 就可以保存所有斜率为 $k$ 的直线的 $b$ 值和直线 $y=kx+b$ 的个数。  
但如果每次遍历时都要从 $k=-10^5$ 遍历到 $k=10^5$ 显然会很耗时，所以我又用了一个可变数组 $g$ 来保存现在还存在的 $k$，这样就只用遍历 $g$ 中的数字就行了。  
美化后的考场代码：
```cpp
#include<bits/stdc++.h>
#define N 100000
using namespace std;
int n,sum;
int mp[2*N+200];
vector<int>g;
struct node{int b,sum;};
vector<node>mp1[2*N+200];
namespace in
{
    char buf[1<<25],*p1=buf,*p2=buf;
    inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    template <typename T>inline void read(T& t){
        t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
        while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
    }
    template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
int main()
{
	in::read(n);
	for(int i=1,op,k,b;i<=n;++i)
	{
		in::read(op,k,b);
		if(op==1)
		{
			mp[k+N]++;
			bool flag=0;
			for(int i=0;i<mp1[k+N].size();i++)
			{
				if(mp1[k+N][i].b==b)
				{
					mp1[k+N][i].sum++;
					flag=1;
					break;
				}
			}
			if(!flag)mp1[k+N].push_back({b,1});
			g.push_back(k);
			++sum;
		}
		else if(op==2)printf("%d\n",sum-mp[k+N]);
		else 
		{
			int temp=0;
			for(auto t:mp1[k+N])
			{
				if(t.b==b)
				{
					temp=t.sum;
					break;
				}
			}
			int res=mp[k+N]-temp;
			for(int i:g)mp[i+N]=0;
			for(int i:g)
			{
				if(i!=k)
				{ 
					mp1[i+N].clear();
					continue;
				}
				for(int i=0;i<mp1[k+N].size();i++)
				{
					if(mp1[k+N][i].b==b)
					{
						mp1[k+N][i].sum=0;
						break;
					}
				}
			}
			mp[k+N]=res;
			sum=mp[k+N];
			g.clear();
			g.push_back(k);
		}
	}
}
```
[赛后评测记录](luogu.com.cn/record/121828322)。[赛时评测记录](https://www.luogu.com.cn/record/121774222)。此时喜提 $100$ 分。

---

## 作者：zly2009 (赞：1)

两个一次函数相交有如下两种情况：

1. $k$ 的值不等，总会在一个点相交。
2. 重叠，即 $k$ 和 $b$ 都相等。

所以操作 $2$ 里求恰好有一个公共点的话，则排除完全重叠，也就是求画板上所在的直线的总数量减去 $k$ 与其相等的直线的数量。

操作 $3$ 要求删除所有与其至少一个公共点的直线，则只要相交全部删除。则我们进行遍历，把相交的直线删去，并且画板上直线的总数量也跟着减少。

考虑到 $k$ 和 $b$ 可能为负数，且值较大，无法使用普通数组加偏移量，这里用 `map` 来存储。

代码（86 分）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
	int k,b;
}a[N];
map<int,map<int,int> >mp;
map<int,int>s;
signed main()
{
	int n,c=0;
	cin>>n;
	while(n--){
		int op,k,b;
		scanf("%lld%lld%lld",&op,&k,&b);
		if(op==1){
			c++;
			a[c]={k,b};
			mp[k][b]++;
			s[k]++;
		}
		if(op==2){
			printf("%lld\n",c-s[k]);
		}
		if(op==3){
			for(auto i=mp.begin();i!=mp.end();i++)
				for(auto j=(i->second).begin();j!=(i->second).end();j++){
					if((i->first!=k||i->first==k&&j->first==b)&&j->second>0){
						s[i->first]-=j->second;
						c-=j->second;
						j->second=0;
					}
				}
		}
		//printf("<%lld>\n",c);
	}
}
```

[结果](https://www.luogu.com.cn/record/121753764)发现，**Subtask #4** 一个点超时。但是数据描述**第 $i$ 次操作满足 $k=i$**，所以所有直线的 $k$ **互不相同**，因此全部相交。

所以操作 $1$ 只需累加个数，操作 $2$ 输出个数，操作 $3$ 直接清零即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int k,b;
}a[N];
map<int,map<int,int> >mp;
map<int,int>s;
int a1[N],a2[N],a3[N];
signed main()
{
	int n,c=0;
	cin>>n;
	bool ok=1;
	for(int i=1;i<=n;i++){
		cin>>a1[i]>>a2[i]>>a3[i];
		if(a2[i]!=i)ok=0;
	}
	if(ok){
		int ans=0;
		for(int i=1;i<=n;i++){
			if(a1[i]==1)ans++;
			if(a1[i]==2)cout<<ans<<'\n';
			if(a1[i]==3)ans=0;
		}
		return 0;
	}
	for(int i=1;i<=n;i++){
		int op=a1[i],k=a2[i],b=a3[i];
		if(op==1){
			c++;
			a[c]={k,b};
			mp[k][b]++;
			s[k]++;
		}
		if(op==2)printf("%d\n",c-s[k]);
		if(op==3){
			for(auto i=mp.begin();i!=mp.end();i++)
				for(auto j=(i->second).begin();j!=(i->second).end();j++){
					if((i->first!=k||i->first==k&&j->first==b)&&j->second>0){
						s[i->first]-=j->second;
						c-=j->second;
						j->second=0;
					}
				}
		}
		//printf("<%lld>\n",c);
	}
}
```

---

## 作者：李卓衡001 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9571)

题目大意
-
有 $ n $ 次操作，每次操作有三种可能：

- ```1 k b``` 代表小 C 绘制了一条解析式为 $ y = kx + b $ 的直线。
- ```2 k b``` 代表小 C 询问你直线 $ y = kx + b $ 与多少条被绘制的直线有恰好一个公共点。
- ```3 k b``` 代表小 C 擦除所有与直线 $ y = kx + b $ 有至少一个公共点的直线。

对于每次 ```2 k b``` 操作，输出满足要求的直线数量。

思路
-
开一个 ```set``` 记录当前出现过的 $ k $，再开一个 ```multiset``` 记录每个 $ k $ 对应的 $ b $，再用一个 $ cnt $ 来记录当前的直线个数。

- 对于一个操作一，直接加入直线， $ cnt \gets cnt+1 $。
- 对于一个操作二，直接输出答案，因为与一条直线恰好只有一个公共点的直线一定不与此直线平行或重叠，因此答案为总直线数减去为 $ k $ 的直线数。
- 对于一个操作三，可以发现要删除的直线有两种可能： 要么 $ k1 \ne k2 $，要么 $ k1 = k2 $ 并且 $ b1 = b2 $，最后记得要改变 $ cnt $ 的值。

注：操作三的 $ k1 $ 和 $ k2 $ 分别表示枚举要删除的 $ k $ 和当前输入的 $ k $，为了方便区分才这样写的。

直接做就行了。

注意
-
由于 $ k $ 可能为负，并且 $ k $ 最大为 $ 10^5 $，所以给每个 $ k $ 多加上一个 $ 10^5 $ 就行了。

代码
-
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=200000+10;
int n,cnt=0,top=0,c[maxn];//cnt为直线数量
set<int> s;
multiset<int> a[maxn];
int main()
{
	int k,b,opt;
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&opt,&k,&b); k+=1e5;
		if(opt==1){//加入直线
			s.insert(k); a[k].insert(b); cnt++;
		} else if(opt==2) printf("%d\n",cnt-a[k].size());
		else {//删除直线
			set<int>::iterator it;
			for(it=s.begin();it!=s.end();it++){
				int j=*it;
				if(j!=k){
					cnt-=a[j].size(); a[j].clear(); c[++top]=j;//这里不知道为什么要开一个数组专门记录要删的元素,直接删要RE
				}
			}
			for(int j=1;j<=top;j++) s.erase(c[j]),c[j]=0;
			cnt-=a[k].count(b); a[k].erase(b); top=0;
		}
	}
	return 0;
}
```
补充
-
关于 ```set``` 和 ```multiset```，具体见[这里](https://blog.csdn.net/boke_fengwei/article/details/99239064)。


考试的时候调了一个多小时没调出来，刚刚一看第一篇题解马上发现哪里错了，所以可能和第一篇题解思路很相似，求管理员大大通过。

---

## 作者：shuangmu (赞：1)

[更好的阅读体验](https://www.cnblogs.com/frostwood/p/17643029.html)

~~这个题拿平衡树写是不是小题大做了~~

咳咳咳进入正题。

首先转化一下题意。第一个操作是加入直线，第二个操作就是求所有斜率不等于 $k$ 的直线的数量，第三个操作就是删掉所有斜率不等于 $k$ 的和所有与该直线重合的直线。

感觉这题完全就是 FHQ_Treap 的板子题嘛，重载一下小于号，按 $k$ 为第一关键字，$b$ 为第二关键字来排序，这样，第一个操作直接插入；第二个操作按 $k$ 裂成三部分，所求就是左右两部分的 $siz$ 和；第三个操作的话，首先按照第二个操作分裂一次，扔掉两边；然后再将中间 $k$ 与 $b$ 恰好相同的分裂出来，扔掉，合并剩下的左右两部分。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
const int INF = 0x3f3f3f3f;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch<'0' || ch>'9') {if(ch == '-') f = -1; ch = getchar();}
	while(ch>='0'&&ch<='9') x = x*10+ch-48, ch = getchar();
	return x * f;
}
struct Line{
	int k, b;
	bool operator < (const Line &y) const{
		if(k == y.k){
			return b < y.b;
		}
		return k < y.k;
	}
};

mt19937 getrand(time(0));
struct node{
	int ls, rs, siz;
	int rnd;
	Line val;
};
int root ;
struct FHQ_Treap{
	node tree[N];
	int idx;
	int New(Line tmp){
		++idx;
		tree[idx] = {0, 0, 1, getrand(), tmp};
		return idx;
	}
	void push_up(int x){
		tree[x].siz = tree[tree[x].ls].siz+tree[tree[x].rs].siz+1;
	}
	void split(int pos, int &l, int &r, Line k){
		if(!pos) return l = r = 0, void();
		if(tree[pos].val < k){
			l = pos;
			split(tree[l].rs, tree[l].rs, r, k);
			push_up(l);
		} else{
			r = pos;
			split(tree[r].ls, l, tree[r].ls, k);
			push_up(r);
		}
	}
	int merge(int l, int r){
		if(!l || !r) return l | r;
		if(tree[l].rnd < tree[r].rnd){
			tree[l].rs = merge(tree[l].rs, r);
			push_up(l);
			return l;
		} else{
			tree[r].ls = merge(l, tree[r].ls);
			push_up(r);
			return r;
		}
	}
	void insert(Line tmp){
		int dl, dr;
		split(root, dl, dr, tmp);
		root = merge(dl, merge(New(tmp), dr));
	}
	int query(Line tmp){
		int dl, dr, md;
		split(root, dl, dr, (Line){tmp.k, -INF});//把 b 设为负无穷，以保证 k 相等的只会在右子树。
		split(dr, md, dr, (Line){tmp.k+1, -INF});//和上面类似。
		int ret = tree[dl].siz+tree[dr].siz;
		root = merge(dl, merge(md, dr));
		return ret;
	}
	void erase(Line tmp){
		int dl, dr, md;
		split(root, dl, dr, (Line){tmp.k, -INF});
		split(dr, md, dr, (Line){tmp.k+1, -INF});
		split(md, dl, dr, tmp);//两次分裂，之前分离的两边的子树因为要删去，所以变量可以直接拿来重新使用。
		split(dr, md, dr, (Line){tmp.k, tmp.b+1});
		root = merge(dl, dr);
	}
}s;
int n;
int main(){
	n = read();
	while(n--){
		int op = read(), k = read(), b = read();
		if(op == 1){
			s.insert((Line){k, b});
		} else if(op == 2){
			printf("%d\n",s.query((Line){k, b}));
		} else{
			s.erase((Line){k, b});
		}
	}
	return 0;
}
```

---

## 作者：Kedit2007 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P9571)。

### 思路

首先一个个看操作，分析需要怎样维护数据。

查询操作相当于询问有多少条直线的 $k$ 与询问中的不同，那么我们可以考虑用一个字典存每个 $k$ 对应的直线个数。

对于删除操作，要求删除满足下列条件中任意一个条件的直线 $(k_i, b_i)$：

- $k \neq k_i$；
- $k = k_i$, $b = b_i$。

那么我们可以选择再用一个存下每个 $(k, b)$ 对应的直线共有多少个。

这里我选择了使用 ```map<int, pair<int, map<int, int>>>``` 来存储所有数据，最外层的键代表 $k$，对应的值的第一项代表斜率为 $k$ 的直线条数，第二项的键代表 $b$，对应的值表示 $(k, b)$ 对应的直线条数。同时，再使用一个整数存储目前一共有多少条直线。

那么当添加一条时，我们可以这样处理：

```cpp
int tot; // 总数，下代码同
map<int, pair<int, map<int, int>>> lines; // 如上文，下代码同

tot++;
auto& p = lines[k];
p.first++;
p.second[b]++;
```
处理询问则可以直接输出 ```tot - lines[k].first```。

处理删除操作时，我们按照如下步骤进行：

1. 找到 ```lines[k].second```，即斜率为 $k$ 的直线对应的，存放 $b$ 对应数量的字典。
2. 将 ```lines[k].second[b]``` 赋值为 $0$，即删除所有重合的直线。
3. 删除除了 ```lines[k]``` 以外所有的键值对，即删除所有斜率不同的直线。

实际操作时，步骤 $3$ 显得较为棘手。赛事我选择了用临时变量记录 ```lines[k].second```，接着清空整个 ```lines```，最后加入先前临时记录的 ```lines[k].second```。

这是我最先的代码：

```
auto& p = lines[k];
int cnt = p.first - p.second[b];
tot = cnt;
map<int, int> para = p.second;
para[b] = 0;
lines.clear();
lines[k].first = cnt;
lines[k].second = para;
```

但是交上去后发现超时，让我们分析一下这种方法的时间复杂度。

单次添加操作时间复杂度 $O(\log n)$，单次查询操作时间复杂度 $O(\log n)$，其中 $n$ 均指斜率为 $k$ 的直线条数。这两个操作都不会超时。

当处理移除操作时，由于 ```clear``` 操作复杂度与元素个数成线性关系，其复杂度最差情况是每条直线都被清空一次，完成所有操作的时间复杂度为 $O(n)$，其中 $n$ 是所有直线的条数，不会超时。

那么问题就出现在临时记录字典，由于 ```map``` 的复制构造时间复杂度为 $O(n)$，其中 $n$ 为元素个数，单次操作的时间复杂度就可以达到 $O(n)$，无法通过此题。

那么想要通过此题，我们只需要想个办法让临时记录操作的时间复杂度降为 $O(1)$。这要如何做到呢？

### std::move

在 C++ 11 及以上标准中，提供了一种快速传递一个对象的方式：```std::move```。具体可以参考 [cppreference](https://zh.cppreference.com/w/cpp/utility/move) 上的介绍。

那么我们可以利用这一点，将上文代码中的 ```map<int, int> para = p.second``` 改为 ```map<int, int> para = move(p.second)```，```lines[k].second = para``` 改为 ```lines[k].second = move(para)``` 即可做到在 $O(1)$ 时间内实现临时记录操作。

### 完整代码参考

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main()
{
	int tot = 0;
	map<int, pair<int, map<int, int>>> lines;
	auto add = [&](int k, int b)
	{
		tot++;
		auto& p = lines[k];
		p.first++;
		p.second[b]++;
	};
	
	auto query = [&](int k, int b)
	{
		return tot - lines[k].first; 
	};
	
	auto erase = [&](int k, int b)
	{
		auto& p = lines[k];
		int cnt = p.first - p.second[b];
		tot = cnt;
		map<int, int> para = move(p.second);
		para[b] = 0;
		lines.clear();
		lines[k].first = cnt;
		lines[k].second = move(para);
	};
	
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int opr, k, b;
		cin >> opr >> k >> b;
		if (opr == 1)
		{
			add(k, b);
		}
		else if (opr == 2)
		{
			cout << query(k, b) << '\n';
		}
		else
		{
			erase(k, b);
		}
	}
}
```

---

## 作者：Untitled10032 (赞：0)

## 思路

易得，两条直线恰好有一个公共点，当且仅当两个直线的斜率 $k_1 \neq k_2$。

两条直线至少有一个公共点，当且仅当两个直线的斜率 $k_1 \neq k_2$ 或两个直线的解析式完全相同（即重合）。

所以问题转化为：维护一个可重集合 $S$，进行 $n$ 次操作，每次操作给定一个数对 $(k, b)$，操作可以为：

- 将 $(k, b)$ 加入集合。
- 询问集合$\{(k', b') \in S | k \neq k'\}$ 中的元素个数。
- 将 $S$ 赋值为 $\{(k', b') \in S|k = k', b \neq b'\}$。

维护一个可重集合，可以使用 multiset 解决。但是我赛时用的是 map。所以这里给出 map 的方法。

map 的两个模板参数分别为直线解析式和直线出现次数。

每次询问时，遍历直线解析式中 $k$ 与询问给出的 $k$ 相等的元素，出现次数求和，输出总直线数 - 出现次数和作为答案。

每次删除时，找到直线解析式中 $k$ 与询问给出的 $k$ 相等的元素组成的区间，将区间之外的所有元素删除，之后查找到元素 $(k, b)$，将其删除。需要注意同时维护元素总数。

## 代码

```cpp
#include <iostream>
#include <cassert>
#include <map>

using namespace std;

//直线解析式类
struct Line {
    int k, b;
};
bool operator < (Line x, Line y) {
    if (x.k != y.k)
        return x.k < y.k;
    return x.b < y.b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    map<Line, int> s;
    int tot = 0;
    map<Line, int>::iterator tmp, tmp2;
    while (n--) {
        int opt, k, b;
        cin >> opt >> k >> b;
        int ans = 0;
        switch (opt) {
        case 1:
            tmp = s.find({k, b});
            if (tmp != s.end())
                tmp->second++;
            else
                s.insert({{k, b}, 1});
            tot++;
            break;
        case 2:
            if (s.empty()) {
                cout << "0\n";
                break;
            }
            tmp = s.insert({{k, -100005}, 0}).first;	//插入一个节点，保证其在所有 (k, ...) 的左侧。
            tmp2 = tmp++;	//tmp 即为等于 k 的元素的左界
            s.erase(tmp2);
            for (tmp2 = tmp; tmp2->first.k == k && tmp2 != s.end(); ++tmp2)
                ans += tmp2->second;
            cout << tot - ans << '\n';
            break;
        case 3:
            if (s.empty())
                break;
            tmp = s.insert({{k, -100005}, 0}).first;	//同询问部分注释
            s.erase(s.begin(), tmp);	//将区间左侧部分全部删除
            if (s.empty())
                break;
            tmp = s.insert({{k, 100005}, 0}).first;
            s.erase(tmp, s.end());	//将区间右侧部分全部删除
            tmp = s.find({k, b});
            if (tmp != s.end()) {
                tot -= tmp->second;
                s.erase(tmp);	//将 (k, b) 删除
            }
            tot = 0;
            for (auto i : s)
                tot += i.second;
            break;
        }
    }
    return 0;
}
```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9571)

## 思路

一道非常好的模拟题，利用 multiset 来解决。

读入数据后对负数加一个大数，使其变成正数进行存储和查找的操作。定义一个 vector 数组用来存储当前所有斜率的值方便遍历。之后分类讨论。

- **操作 $1$**：向 multiset 中存入每组 $k$ 与 $b$，之后总计数器与当前斜率 $k$ 分组的计数器同时 $+1$。

- **操作 $2$**：我们知道当斜率相同时，两条直线要么平行，要么重合，都不算进个数。所以我们直接用当前总计数器减去斜率分组 $k$ 计数器，得出剩下可以和当前直线交叉的直线数量，输出就好啦。

- **操作 $3$**：注意这个操作要求和第 $2$ 条**不一样**。这个操作删除直线的时候**还要**删除与当前直线重合的直线（即与当前直线有无数个交点）。删除操作可以很方便地用 STL 库中的 ``find()`` 与 ``erase()`` 函数实现。

- 删掉和当前直线重合的直线时，注意直接 ``erase()`` 的时候一次会删掉所有的与当前斜率 $k$ 相等的直线。所以我们要先 ``find()``，再 ``erase()``，这时候删掉的就是单个直线了。删除时还要将总计数器和当前斜率的计数器 $-1$。之后再对其他斜率的 multiset 进行清空操作并归零计数器。

## 注意事项

- 因为要对负数加上一个数，所以数组开大点。

- 别忘输出换行。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll n){//快写。
	if(n<0){
		n=-n;
		putchar('-');
	}
	if(n>9)print(n/10);
	putchar(n%10+'0');
}
const int N=2e5+10;
int n,op,k,b,cnt,num[N*2];
multiset<int>st[N*2];
vector<int>v;
int main(){
	cin>>n;
	while(n--){
		op=read(),k=read(),b=read();
		if(op==1){
			if(k<0)k+=N;//负数处理。
			st[k].insert(b);
			cnt++;//总计数器 +1。
			num[k]++;//当前斜率计数器 +1。
			v.pb(k);
		}
		if(op==2){
			if(k<0)k+=N;//负数处理。
			print(cnt-num[k]);
			putchar('\n');
		}
		if(op==3){
			if(k<0)k+=N;//负数处理。
			while(1){
				auto p=st[k].find(b);
				if(p==st[k].end())break;//没有重合的了就退出。
				st[k].erase(p);
				cnt--;//别忘减。
				num[k]--;
			}
			for(int i:v){
				if(i<0)i+=N;//负数处理。
				if(i==k)continue;
				st[i].clear();
				cnt-=num[i];//先减再清零。
				num[i]=0;
			}
			v.clear();//别忘清空。
			if(st[k].size())v.pb(k);//没空的还要 push 进去。
		}
	}
	return 0;
}
```

[已 AC](https://www.luogu.com.cn/record/121831801)

---

## 作者：fish_love_cat (赞：0)

**没用的前言：**

这是距离 AK 最近的一次比赛，就差 T4 那么一个测试点啊啊啊……四十分没了啊啊……

---

**必要的前置芝士：**

什么是 [$y=kx+b$](https://baijiahao.baidu.com/s?id=1772474386104429303&wfr=spider&for=pc)？

从这篇文章中，我们可以知道：

>$k$ 和 $b$ 分别代表函数的斜率和截距。

显然的，斜率相同的线互相平行， $k$ 和 $b$ 都相同的线重合。

只要知道这么多就能做啦。

---

**思路：**

用 `map` 存储每条线，查询时输出线段总数减去与该线平行的线数量，删除时把与之平行且不重和的记下，只保留记下的其余删去即可。判断是否重合或平行的条件见前置芝士。

---

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,map<int,int> > mp;//重合线
map<int,int> mapp;//平行线
map<int,int> app;//过渡删除专用存储器
int sum;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,k,b;
        cin>>x>>k>>b;
        if(x==1){//添加
            mapp[k]++;
            sum++;
            mp[k][b]++;
        }else if(x==2){//查询
            cout<<sum-mapp[k]<<endl;
        }else{//删除
            sum=mapp[k]-mp[k][b];
            for(auto it=mp[k].begin();it!=mp[k].end();it++){
                if((it->first)!=b)app[(it->first)]=(it->second);
            }
            mapp.clear();
            mp.clear();
            mapp[k]=sum;
            for(auto it=app.begin();it!=app.end();it++){
                mp[k][(it->first)]=(it->second);
            }
            app.clear();
        }
    }
	return 0;//我的AK啊……
}
```

---

## 作者：wangyishan (赞：0)

# P9571 Horizon Blue 题解

## [题意 Link](https://www.luogu.com.cn/problem/P9571)

小 C 喜欢在画板上画画。他进行了 $ n $ 次操作，每次操作有如下三种可能：

- ```1 k b``` 代表小 C 绘制了一条解析式为 $ y=kx+b $ 的直线。
- ```2 k b``` 代表小 C 询问你直线 $ y=kx+b $ 与多少条被绘制的直线有**恰好**一个公共点。
- ```3 k b``` 代表小 C 擦除所有与直线 $ y=kx+b $ 有**至少**一个公共点的直线。

**注意：两条重合的直线有无数个交点。**

**注意：询问时重合的直线应分别计算。**

## 思路

诈骗题。我们发现两条直线 $y_1=k_1x+b_1$ 和 $y_2=k_2x+b_2$ 之间有这么四种可能（图片由windows计算器绘制）：

1. $k_1=k_2,b_1=b_2$  -> 重合。
2. $k_1=k_2,b_1\neq b_2$ ![](https://cdn.luogu.com.cn/upload/image_hosting/sgk8mynh.png) 此时两直线平行（斜率相等）。
3. $k_1\neq k_2,b_1=b_2$ ![](https://cdn.luogu.com.cn/upload/image_hosting/hpy44zke.png) 此时两直线相交。
4. $k_1\neq k_2,b_1\neq b_2$ ![](https://cdn.luogu.com.cn/upload/image_hosting/puql55w3.png) 此时两直线相交。

我们发现，处理相交情况比较困难，但是平行情况只有一种，比较好判断。所以我们考虑“正难则反”，记录同一斜率下有几条直线，查询的时候用总直线数减去查询的斜率下的直线数即可。

同时，注意删除时是要把**至少**一个公共点的直线删去，所以**重合也要删**！！我们还需要开$2\times10^5$（值域大小）个 `map` 记录同一斜率 $k$ 下截距为 $b$ 的直线条数，删除时把除该斜率的其他所有直线和重合的直线删除即可。

但是这样又给删除带来了一个问题：如果每次删除都清空 `map` ，时间无法忍受。所以我们考虑一个类似线段树 `lazytag` 的方法：开一个 `bitset`数组 $b$，每次插入时把 $b_k$ 置为 $1$，每次清空时清零。如果在插入前或查询前发现 $b_k=0$，就把斜率 $k$ 对应的直线删除即可。这样最多删 $n$ 次 `map`，能过。

细节见代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, suml/*总条数*/, num;
bitset<200010> bit;
int f[200010];
map<int, int> mp[200010];
map<int, int> ls;//离散化数组
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int op, k, b;
    cin >> op >> k >> b;
    k += 100000;b += 100000;//都加到>=0,数组下标不能为负数
    if (!ls[k])//离散化，可做可不做
      ls[k] = ++num;
    int tk = ls[k];
    if (op == 1) {
      if (!bit[tk]) {
        mp[tk].erase(mp[tk].begin(), mp[tk].end());
        f[tk] = 0;
      }
      f[tk]++, suml++;
      mp[tk][b]++;
      bit[tk] = 1;
    } else if (op == 2) {
      if (!bit[tk]) {
        mp[tk].erase(mp[tk].begin(), mp[tk].end());
        f[tk] = 0;
      }
      cout << suml - f[tk] << endl;
    } else {
      if (!bit[tk]) {
        mp[tk].erase(mp[tk].begin(), mp[tk].end());
        f[tk] = 0;
      }
      if (f[tk])
        f[tk] -= mp[tk][b];//删去重合直线
      mp[tk][b] = 0;
      suml = f[tk];
      bit.reset();//全部置0 
      bit[tk] = 1;//斜率为k的直线并没有删除
    }
  }
  return 0;
}
```

---

## 作者：无钩七不改名 (赞：0)

首先我们要明确两个一次函数有一个公共点的条件是斜率 $k$ 不同，两个一次函数重合的条件是完全相同。

那么我们可以用一个动态数组记录出现过的斜率，并对于每个斜率 $k$ 分别用一个可重集 $a_k$ 记录每个斜率为 $k$ 的函数出现过的 $b$ 值，用一个数 $yj$ 记录在画板上的函数数量。

对于每个操作一，在斜率为 $k$ 的集合加入 $b$，并让 $yj$ 增加 $1$。如果加入 $b$ 前该集合为空，则在动态数组里面加入 $k$。

对于每个操作二，我们只需要输出已经在画板上的函数数量（即 $yj$）减去斜率为 $k$ 的函数数量（即可重集 $a_k$ 的大小），即为答案。（因为两条一次函数有一个公共点的条件是斜率 $k$ 不同。）

对于每个操作三，我们可以先遍历动态数组，清空斜率不为 $k$ 的集合，并减去相应的函数数量。然后再清理去斜率为 $k$ 的集合中所有的 $b$，并减去相应的函数数量即可。

需要注意的是 $k$ 和 $b$ 都可能取到负数，这时候访问下标会发生错误，我们可以用把它们都加上 $10^5$ 的方式来解决。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=100005;

int n,yj;
multiset<int> a[N<<1];
vector<int> vc;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	} 
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int main(){
	n=read();
	for(int i(1);i<=n;++i){
		int op=read(),k=read(),b=read();
		k+=100000;b+=100000;
		if(op==1){
			if(a[k].empty())vc.push_back(k);
			a[k].insert(b);++yj;
		}
		else if(op==2)printf("%d\n",yj-a[k].size()/*-a[k].count(b)*/);
		else{
			for(int v:vc){
				if(v!=k){
					yj-=a[v].size();
					a[v].clear();
				}
			}
			yj-=a[k].count(b);
			a[k].erase(b);
			vc.clear();
			if(a[k].size())vc.push_back(k);
		}
		//puts("qwq");
	}
	return 0;
}
```


---

## 作者：Genius_Star (赞：0)

### 思路：

~~有一点儿考数学功底……~~

对于我们每次输入的直线解析式 $y=kx+b$，其中 $k$ 表示直线的斜率，$b$ 是直线与 $y$ 轴的截距。

给出两条直线的直线解析式：$y=k_1x+b_1,y=k_2x+b_2$。

- 如果 $k_1=k_2$ 并且 $b_1 \ne b_2$，那么两直线平行。

- 如果 $k_1=k_2$ 并且 $b_1 = b_2$，那么两直线重合。

- 如果 $k_1 \ne k_2$，那么两直线相交。

那么对于操作 $2$ 就是查询所有直线中 $k$ 值与其不等的个数，我们维护一个变量 $sum$ 表示当前的直线数量，维护一个结构体 $a$，$a_i$ 表示斜率为 $i$ 的直线的数量以及一个 map 容器 $p$，维护着所有斜率为 $i$ 的直线的截距。

那么操作 $2$ 查询的时候，我们只需要输出 $sum$ 减去斜率为 $k$ 的直线数量，操作 $1$ 添加的时候，维护一个向量 $v$，表示当前存在的所有直线的斜率，对于添加操作判断这个斜率的直线是否有过，然后将计数器以及 map 进行累加与标记。

对于操作 $3$，就是将与 $k$ 不等的直线全部清除掉，当然如果有直线与自身重合也要清除掉，则我们遍历 $v$，即当前存在的所有斜率，判断这个值是否重合，以及对于其他与其相交的直线将贡献给清楚掉。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200,M=100000;
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
struct St{
    ll sum;
    map<ll,ll> p;
    void init(){
    	p.clear();
	}
}a[N];
ll n,sum,op,k,b;
vector<ll> v;
void check(ll i,ll k,ll b){
    if(i!=k){
        a[i].init();
        sum-=a[i].sum;
        a[i].sum=0;
    }
	else{
        if(a[i].p[b]){
            a[i].sum-=a[i].p[b];
            sum-=a[i].p[b];
            a[i].p[b]=0;
        }
    }
}
int main(){
    n=read();
    while(n--){
        op=read(),k=read()+M,b=read();
        if(op==1){
            a[k].p[b]++;
            a[k].sum++;
            sum++;
            if(a[k].sum==1) 
			  v.push_back(k);
        }
        else if(op==2){
            write(sum-a[k].sum);
            putchar('\n');
        }
        else{
            for(auto i:v)
              check(i,k,b);
            v.clear();
            v.push_back(k);
        }
    }
    return 0;
}
```


---

## 作者：Ryder00 (赞：0)

## 思路
引理 $1$：两直线斜率 $k$ 相同时，两直线平行或相等。当且仅当截距 $b$ 也相同时，两直线相等。

引理 $2$：两条直线只有平行、相交、相等三种状态。且相交时仅有一个交点。

回到题目，分析可以发现，操作二要求输出当前与询问斜率 $k$ 不相等的直线数量；操作三要求删除与询问同 $k$ 不同 $b$ 以外的所有直线。

容易想到使用 multiset 维护。

注意到斜率可能是负数，全部离散成正数更好维护。

## Code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=5e5+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,cnt,vis[N];
multiset<int> s[N];
vector<int> now;
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int opt,k,b;
        cin>>opt>>k>>b;
        k+=100000;
        if(opt==1){
            s[k].insert(b);
            cnt++;
            if(!vis[k]){
                vis[k]=1;
                now.pb(k);
            }
        }
        else if(opt==2){
            cout<<cnt-(int)s[k].size()<<endl;
        }
        else {
            bool pd=0;
            for(int x:now){
                if(x==k) {
                    pd=1;
                    continue;
                }
                cnt-=(int)s[x].size();
                s[x].clear();
                vis[x]=0;
            }
            now.clear();
            if(pd) now.pb(k),vis[k]=1;
            while(s[k].count(b)) cnt--,s[k].erase(s[k].find(b));
            if((int)s[k].size()==0) now.clear();
        }
        
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // ios::sync_with_stdio(false),cin.tie(0);
    while(T--){
        solve();
    }
    return ~~(0^_^0);
}
```

---

## 作者：251Sec (赞：0)

翻译一下题意：

- 操作一：加一条直线 $y=kx+b$。
- 操作二：查询斜率不等于 $k$ 的直线个数。
- 操作三：删除所有斜率不等于 $k$ 的直线以及斜率等于 $k$ 且截距等于 $b$ 的直线。

不妨在每个时刻维护：

- 所有存在的斜率。
- 对每个 $k,b$ 维护直线 $y=kx+b$ 的条数（使用哈希表）。
- 直线总条数。
- 每个斜率的直线条数。

考虑处理操作：

- 操作一：直接更新上述信息。
- 操作二：答案为直线总条数减去斜率为 $k$ 的直线条数。
- 操作三：枚举所有存在的斜率暴力删除斜率不等于 $k$ 的直线，然后删除斜率等于 $k$ 且截距等于 $b$ 的直线。容易发现所有直线的删除次数之和不超过操作一的次数，因此复杂度均摊正确。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
unordered_map<int, int> li[300005];
vector<int> nz;
int cnt, sz[300005];
int main() {
    scanf("%d", &n);
    while (n--) {
        int op, k, b;
        scanf("%d%d%d", &op, &k, &b);
        k += 100001; b += 100001;
        if (op == 1) {
            cnt++;
            if (!sz[k]) nz.emplace_back(k);
            sz[k]++;
            li[k][b]++;
        }
        else if (op == 2) {
            printf("%d\n", cnt - sz[k]);
        }
        else if (op == 3) {
            for (auto i : nz) {
                if (i != k) {
                    cnt -= sz[i]; sz[i] = 0;
                    li[i].clear();
                }
            }
            nz.clear(); nz.emplace_back(k);
            cnt -= li[k][b]; sz[k] -= li[k][b];
            li[k][b] = 0;
        }
    }
    return 0;
}
```

---

