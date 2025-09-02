# Productive Meeting

## 题目描述

有 $n$ 个人被邀请参加一个即将召开重要会议。在会议中，任意两个人可以社交，相同的两个人可以社交任意次。

$n$ 个人中，每个人都有一个社交能力值，其中第 $i$ 个人的社交能力值是一个非负整数 $a_i$，它表示这个人可以与另一个人社交的次数。

在一个会议中，产生的社交次数越多，这次会议就会被认为越有效。具体地，一个会议的有效程度为这次会议进行时产生的社交次数。

给你序列 $a$，求出一次会议的最大有效程度，要求给出任意一种可以产生这个最大有效程度的方案。

## 说明/提示

$1\leq t\leq 10^3,2\leq n\leq 2\times 10^5$。

另外，保证对于所有测试样例中的 $n,a_i$，其和不超过 $2\times 10^5$。

## 样例 #1

### 输入

```
8
2
2 3
3
1 2 3
4
1 2 3 4
3
0 0 2
2
6 2
3
0 0 2
5
8 2 0 1 1
5
0 1 0 0 6```

### 输出

```
2
1 2
1 2
3
1 3
2 3
2 3
5
1 3
2 4
2 4
3 4
3 4
0
2
1 2
1 2
0
4
1 2
1 5
1 4
1 2
1
5 2```

# 题解

## 作者：EternalHeart1314 (赞：5)

### [题目传送门](https://www.luogu.com.cn/problem/CF1579D)

# 题意

有一个非负整数序列，每一次可选择两个不为零的数，然后都减一，求最多可以操作几次。

# 思路

手玩样例，可以发现，要尽可能地消耗掉最大值，不把最大值消耗掉，最后便会产生浪费。所以可以用最小值去消耗最大值，这样就不会产生浪费。但其它题解好像都是取两个最大值。set 维护即可。

时间复杂度 $O(t(n\log n+V\log n))$，$V$ 为序列里的值的和。

# Code
```
#include<bits/stdc++.h>
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;

const int N(3e5 + 7);
int t, n, x, tot;
PII a, b, c[N];
set<PII > s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t --) {
		s.clear();
		cin >> n;
		tot = 0;
		for(int i(1); i <= n; ++ i) {
			cin >> x;
			if(x) {
				s.insert({x, i});
			}
		}
		while(s.size() > 1) {
			a = *s.begin(), b = *s.rbegin();
			s.erase(s.begin()), s.erase(s.find(b));
			c[++ tot].fi = a.se, c[tot].se = b.se;
			if(-- a.fi) {
				s.insert(a);
			}
			if(-- b.fi) {
				s.insert(b);
			}
		}
		cout << tot << '\n';
		for(int i(1); i <= tot; ++ i) {
			cout << c[i].fi << ' ' << c[i].se << '\n';
		}
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：M_CI (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1579D)

### Part1. 思路

这一题要找到交流次数最多的一组答案，所以理所当然地想到要尽可能的多用交流次数。

所以要尽可能的多匹配还有交流次数的人去交流。

但是如果随便匹配，就会出现这样的情况：

```
1
3
1 2 3
```

这组数据的答案很明显：

```
3
1 3
2 3
2 3
```

假如随便匹配，就可能得到这样的答案：

```
2
1 2
2 3
```

出现这种情况的原因是什么呢？

很容易发现，随便匹配得出的过程中，在前两人已经用完交流次数时，交流次数最多的第 $3$ 个人的交流次数还有 $2$，很明显没有物尽其用，出现了浪费。

所以需要尽量规避这种情况。

然后就会想到让交流次数最多的两人进行交流，来获得最多的交流次数。

这时候就又会有两种不同的想法：

1. 将交流次数最多的两人中交流次数较少的那个人的交流次数用完，再找新的交流次数最多的两人。

2. 将交流次数最多的两人的交流次数各使用 $1$，然后找新的交流次数最多的两人。

如果使用想法一，在下面的数据中就会出错：

```
1
5
5 5 5 5 5
```

正确答案为：

```
12
4 5
2 3
1 5
3 4
1 2
4 5
2 3
1 5
3 4
1 2
4 5
2 3
```

但是用想法一得出的答案是：

```
10
4 5
4 5
4 5
4 5
4 5
2 3
2 3
2 3
2 3
2 3
```

很明显，有一个人的交流次数完全没有使用，完全被浪费。

所以也需要避免出现这种情况。

现在我们便得到了正解：

维护一个大根堆，将所有的有交流次数的人压入队列，当队列中还至少有两个人时，将队首的两人弹出，将他们的交流次数 $-1$，如果还有剩余的交流次数，就再将它们压回队列。

### Part2. 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,ans,a[200010];
pair<int,int> tot[200010];

int main () {
    cin>> t;
    while (t--) {
        cin>> n;
        priority_queue<pair<int,int> > q;
        for (int i=1;i<=n;i++) {
            cin>> a[i];
            if (a[i]>0) q.push ({a[i],i});
        }
        ans=0;
        while (q.size ()>=2) {
            pair<int,int> u=q.top ();
            q.pop ();
            pair<int,int> v=q.top ();
            q.pop ();
            tot[++ans]={min (u.second,v.second),max (u.second,v.second)};
            u.first--;
            v.first--;
            if (u.first) q.push (u);
            if (v.first) q.push (v);
        }
        cout<< ans<< "\n";
        for (int i=1;i<=ans;i++)
            cout<< tot[i].first<< " "<< tot[i].second<< "\n";
    }
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/140691210)

---

## 作者：huyangmu (赞：4)

我们考虑贪心。

因为要使得有效程度最大，所以我们要尽量让社交能力强的人发挥作用，让他们的社交次数最多，才不会浪费。所以每次可以取当前社交能力最强的两个人进行社交。

我们可以用一个大根堆维护，存储每个人的编号和社交能力，那么每次堆顶的两个元素就是当前社交能力最强的两个人，取出这两个元素后进行一次操作，如果操作完后两个人的社交能力还不是 $0$ 就重新放入大根堆，并用一个队列记录二人编号，当堆内元素个数不超过 $1$ 时，就退出循环。

但要注意每次操作把答案和大根堆清空，社交能力为 $0$ 的人不入堆。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR = 2e5 + 5;
int T,n,a[NR],ans;
struct node{
	int x,id;
	bool operator < (const node & a) const{
		return x < a.x;
	}
};
priority_queue<node>q;
queue<int>que;
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n;
		while (!q.empty()) q.pop();
		for (int i = 1;i <= n; ++i)	{
			cin >> a[i];
			if (a[i] == 0) continue;
			q.push(node{a[i],i}); 
		}
		ans = 0;
		while (q.size() > 1){
			node tmp = q.top();
			q.pop();
			node tmp2 = q.top();
			q.pop();
			que.push(tmp.id);
			que.push(tmp2.id);
			++ans;
			--tmp.x,--tmp2.x;
			if (tmp.x != 0) q.push(node{tmp.x,tmp.id});
			if (tmp2.x != 0) q.push(node{tmp2.x,tmp2.id});
		}
		cout << ans << '\n';
		while (!que.empty()){
			int tmp = que.front();
			que.pop();
			cout << tmp << ' ' << que.front() << '\n';
			que.pop();
		}		
	}
	return 0;
} 


---

## 作者：tmp_get_zip_diff (赞：2)

如果我们只考虑交流方案，那么每次取出两个社交能力最大的进行操作即可完成，因为这组数的方差越小，接下来可执行的操作就越大，可以用大根堆或 `multiset` 实现。

现在要求交流总数量且先输出，可以将原来的输出存到动态数组内，随后先输出动态数组大小再将交流方案一个一个输出，可以实现，但是交流总数量最大达到 $n \times A \div 2$（$A$ 为 $a_i$ 的值域），最大为 $2 \times 10^{10}$，既表示要开 `long long`，也意味空间开不下。

考虑优化，假设 $\max\limits_{i=1}^{n}a_i$ 为 $Mx$，剩下 $a_i$ 的和为 $Su$，那么如果 $Mx>Su$，则交流总数量最大必定为 $Su$，否则必定为 $\lfloor \sum\limits_{i=1}^na_i\div2\rfloor$。

那么先求出 $Mx$ 和 $Su$ 输出交流总数量，再一边求方案一边输出即可通过。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long

multiset<pair<int,int> >q;
int n,a[200005],sum,maxi;
vector<pair<int,int> >tmp; 

void Work()
{
	q.clear();
	tmp.clear();
	sum=0,maxi=-5e5;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]!=0)
		{
			q.insert({a[i],i});
			sum+=a[i];
			maxi=max(maxi,a[i]);
		}
	}
	sum-=maxi;
	if(maxi>sum)
		cout<<sum<<"\n";
	else
		cout<<(maxi+sum)/2<<"\n";
	while(q.size()>1)
	{
		auto a1=*prev(q.end());
		q.erase(prev(q.end()));
		auto a2=*prev(q.end());
		q.erase(prev(q.end()));
		cout<<a1.second<<" "<<a2.second<<"\n";
		a1.first--,a2.first--;
		if(a1.first!=0)
			q.insert(a1);
		if(a2.first!=0)
			q.insert(a2);
	}
	return ;
}

signed main()
{
	int t;
	cin>>t;
	while(t--)
		Work();
	return 0;
}
```

---

## 作者：Z_AuTwT (赞：1)

## [原题链接](https://www.luogu.com.cn/problem/CF1579D)

观察题面，求最大的社交次数，发现是最优解问题，先考虑贪心。

**接下来考虑贪心策略：**

因为我们要求最大社交次数，所以尽量不要浪费社交次数，就可以达到最优。

而在这里，最容易产生浪费的就是社交能力值最大的，因为如果其他的都消掉了，那么能力值最大的就会产生许多浪费。

由上，我们可以得到一个结论，就是必须先消最大的。

但是，另一个问题又来了，该用哪个和最大的消呢？

继续往深处想，如果当前的最大被消下去了，那么下一个会成为最大的是那个呢？

答案就是第二大的，所以我们只要用最大的与次大的消，就可以最大化次数。

## 实现方法：

在这里，我用了一个优先队列来动态维护最大值。

还有一个点就是，我们消的时候要一次一次消，因为有可能消了一次之后有新的数顶替了最大值或次大值。

## 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int cun[200010][2];//存下方案
int main(){
	int t;
	cin>>t;
	while(t--){
		priority_queue<pair<int,int> > que;//建立优先对列
		int n,cnt=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			int a;
			cin>>a;
			if(a) que.push(make_pair(a,i));//入队
		}
		while(que.size()>1){
			cnt++;
			pair<int,int> x=que.top();//取最大值
			que.pop();
			pair<int,int> y=que.top();//取次大值
			que.pop();
			x.first--;//消
			y.first--;
			cun[cnt][0]=x.second;//存储
			cun[cnt][1]=y.second;
			if(x.first) que.push(x);//重新入队
			if(y.first) que.push(y);
		}
		cout<<cnt<<"\n";
		for(int i=1;i<=cnt;i++) cout<<cun[i][0]<<" "<<cun[i][1]<<"\n";
	}
}
```

---

## 作者：_GW_ (赞：1)

## 题意
给你一个长为 $n$ 的数组 $a$，让 $a$ 中任意两个元素各减一可以获得 1 的价值，求最大价值。

## 思路
明显的贪心。

每次拎出两个最大的各减一，然后记录一下下标，不就行了？

值得注意的是，要用优先队列优化，不然会超时。

再次审题，发现还要输出具体方案，怎么办？

很简单，我们把优先队列的类型转成 pair，first 存剩余的社交能力值，second 存下标。

每次删减就存入一次下标，直接 AC！

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=114514*2;
int a[N],b[N],c[N],T,num,val,n,m,ans;
priority_queue<pair<int,int> > q;
vector<int> v1,v2;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;ans=0;v1.clear(),v2.clear();
		while(q.size()) q.pop();
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i])q.push({a[i],i});
		}
		while(q.size()>=2)
		{
			pair<int,int> x,y;
			x=q.top();q.pop();
			y=q.top();q.pop();
			ans++;x.first--;y.first--;
			v1.push_back(x.second);v2.push_back(y.second);
			if(x.first>0) q.push(x);
			if(y.first>0) q.push(y);
		}
		cout<<ans<<endl;
		for(int i=0;i<ans;i++) cout<<v1[i]<<" "<<v2[i]<<endl;
	}
	return 0;
}
```


---

## 作者：一铭君一 (赞：1)

# CF1579D 题解

考场写挂这题结果上头了，痛失 E2。

赛后重构了代码，一次就过掉了，再看看代码难度几乎没有。赛时写挂可能是因为太着急了吧。

## 题目翻译

给你 $n$ 个数，每次操作从这 $n$ 个数种挑出 2 个大于 0 的数，对这两个数分别 -1。

求最大的可能的操作次数。

## Solution

一旦我们选不出 2 个大于 0 的数，就只能结束操作。

于是一个简单的贪心思路：每次选择最大和次大，使它们 -1。

考虑反证法：

* 如果不选择最大和次大而是选择其它的数 -1，那么这些被减的数一定比选择最大和次大 -1 更接近 0。
	
    一旦一个数字被减到 0，那么它在之后的决策中就不可以被选，而选不出 2 个大于 0 的数，就意味着必须结束选择。

	由于我们要最大化选择次数，所以我们希望能选出 2 个大于 0 的数的次数尽可能的多，也就是使得可以被选择的数的数量尽可能多。
    
    而选择非最大、次大的数会导致可以选择的数的数量更快的减小，故选择最大、次大两个数一定不会更劣。

	综上，每次贪心的选择最大、次大两个数是正确的。

现在考虑怎么维护最大、次大。

注意到数据范围： $\sum a_{T,i}\leq 2\times 10^5$。也就是说，我们在一个数据点里的所有测试用例中最多执行 $10^5$ 次操作。

所以对于单组测试用例，只要把其包含的所有的 $a_i$ 扔到堆里，每次取 2 次堆顶，把这两个取出来的数 -1，然后再扔回堆里就可以了。

上面说过，这个操作最多执行 $10^5$ 次，故总时间复杂度 $O(n\log n)$ ，这里的 $n=\sum a_{T,i}$。

## Code

```cpp
int T;
int n;
struct PEO{
  int a,num;
}p;
inline bool operator < (PEO a,PEO b){
  return a.a<b.a;
}
std::priority_queue<PEO>Q;
std::vector<int>a1,a2;

void init(){
  a1.clear(),a2.clear();
  while(Q.size()) Q.pop();
  read_int(n);
  for(int i=1;i<=n;++i){
    read_int(p.a),p.num=i;
    if(p.a>0) Q.push(p);
  }
}

signed main(){
  read_int(T);
  while(T--){
    init();
    int sum=0;
    while(Q.size()>=2){
      PEO a=Q.top();
      Q.pop();
      PEO b=Q.top();
      Q.pop();
      a.a--,b.a--;
      a1.push_back(a.num);
      a2.push_back(b.num);
      sum++;
      if(a.a>0) Q.push(a);
      if(b.a>0) Q.push(b);
    }
    print_int(sum,'\n');
    for(int i=0;i<a1.size();++i)
      print_int(a1[i],' '),print_int(a2[i]);
  }
  return 0;
}
```

---

## 作者：Zhangikun (赞：0)

## 思路
想要讨论的次数最多，就需要尽可能地把每个人的交流次数用掉。

如果随便将两人配对，那么就有可能会出现以下情况：

数据为下：
```
4
1 2 3 4
```
如果随便配，我们先选择一个个来。
- 1 号和 2 号配，1 号变成 0，2 号变成 1。
- 然后，2 号和 3 号配，2 号变成 0，3 号变成 2。
- 最后，3 号将全部的机会花在 4 号身上，结束。

总次数：$1+1+2=4$。

现实却是：$5$。

那么问题出在哪呢？

其实 4 号和 3 号配完后， 4 号的机会还有 $2$ 次，但是已经没有人可以找他了，所以白白浪费了。

~~浪费是可耻的~~为了不浪费，所以我们要让两个最强的人进行配对，即可将每个人的实力发挥到极致。
### 综上所述
考虑贪心，用优先队列。
## 准备工作
题目要求不仅输出最多的次数，而且要输出每次是哪两个人，所以打包成结构体丢进队列里去就行了。

那么怎么排序呢？
手把手教你写重载运算符：
```cpp
  friend bool operator<(ikun x,ikun y)//重载运算符"<"的定义
  {
    return x.x<y.x;
  }
```
也可以这样：
```cpp
  bool operator<(const ikun y)const//重载运算符"<"的定义
  {
    return x<y.x;
  }
```
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct ikun
{
  int x,id;
  friend bool operator<(ikun x,ikun y)
  {
    return x.x<y.x;
  }
};
int n,sum;
bool cmp(pair<int,int>x,pair<int,int>y)
{
  return x.first!=y.first?x.first<y.first:x.second<y.second;
}
void help()
{
  sum=0;
  vector<pair<int,int>>v;
  priority_queue<ikun>q;
  cin>>n;
  for(int i=1,x;i<=n;i++)
  {
    cin>>x;
    q.push({x,i});
  }
  while(q.top().x)//必须保证最大的元素不是0
  {
    ikun x=q.top(),y;
    q.pop();
    y=q.top();
    q.pop();
    if(y.x==0||x.x==0)break;
    v.push_back({min(y.id,x.id),max(y.id,x.id)});
    sum++;
    q.push({x.x-1,x.id});
    q.push({y.x-1,y.id});
  }
  cout<<sum<<"\n";
  sort(v.begin(),v.end(),cmp);
  for(int i=0;i<v.size();i++)
  {
    cout<<v[i].first<<" "<<v[i].second<<"\n";
  }
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  for(cin>>t;t--;)
  {
    help();
  }
  return 1145141919810;
}
```


---

