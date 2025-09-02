# [ABC252F] Bread

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc252/tasks/abc252_f

長さ $ L $ のパンが $ 1 $ つあり、これを $ N $ 人の子供たちに切り分けます。 $ i $ 番目 $ (1\leq\ i\leq\ N) $ の子供は長さ $ A_i $ のパンを欲しがっています。

そこで、高橋君は次の操作を繰り返して、長さ $ A_1,A_2,\ldots,A_N $ のパンを切り出して配ることにしました。

> 長さ $ k $ のパン $ 1 $ つと $ 1 $ 以上 $ k-1 $ 以下の整数 $ x $ を選ぶ。選んだパンを長さ $ x $ のパンと 長さ $ k-x $ のパンに切り分ける。   
> このとき、$ x $ の値によらずコストが $ k $ かかる。

それぞれの子供に配るパンは長さがちょうど $ A_i $ のパン $ 1 $ つである必要がありますが、誰にも配られずに余るパンがいくつあっても構いません。

このとき、全ての子供たちにパンを配るために必要な最小のコストを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\leq\ 10^9 $
- $ A_1+A_2+\cdots+A_N\leq\ L\leq\ 10^{15} $
- 入力は全て整数

### Sample Explanation 1

高橋君は次のようにしてパンを切り分けて配ることができます。 - 長さ $ 7 $ のパンと整数 $ x=3 $ を選ぶ。パンは長さ $ 3 $ のパンと長さ $ 4 $ のパンに切り分けられる。 (コスト $ 7 $ ) - 長さ $ 3 $ のパンと整数 $ x=1 $ を選ぶ。パンは長さ $ 1 $ のパンと長さ $ 2 $ のパンに切り分けられる。前者を $ 1 $ 番目の子供に配る。 (コスト $ 3 $ ) - 長さ $ 2 $ のパンと整数 $ x=1 $ を選ぶ。パンは長さ $ 1 $ のパン $ 2 $ つに切り分けられる。これを $ 3,5 $ 番目の子供に配る。 (コスト $ 2 $ ) - 長さ $ 4 $ のパンと整数 $ x=2 $ を選ぶ。パンは長さ $ 2 $ のパン $ 2 $ つに切り分けられる。これを $ 2,4 $ 番目の子供に配る。 (コスト $ 4 $ ) このとき、コストは $ 7+3+2+4=16 $ かかり、これが最小です。 また、余るパンはありません。

### Sample Explanation 2

それぞれの子供に配るパンの長さはちょうど $ A_i $ でなければならない事に注意してください。

## 样例 #1

### 输入

```
5 7
1 2 1 2 1```

### 输出

```
16```

## 样例 #2

### 输入

```
3 1000000000000000
1000000000 1000000000 1000000000```

### 输出

```
1000005000000000```

# 题解

## 作者：沉石鱼惊旋 (赞：7)

### 闲话

原题 [P1334 瑞瑞的木板](https://www.luogu.com.cn/problem/P1334)。刚好不久前做过，赛时直接贺了自己的代码过掉的。

### 题目翻译

为方便和瑞瑞的木板联系起来，下文翻译不采用原题中的“面包”而是使用“木板”。

有一根长度为 $L$ 的木板，切成 $n$ 根小木板。第 $i$ 根小木板的长度为 $l_i$，每次切下长度为 $x$ 的小木板需要耗费 $x$ 的体力。允许有剩余，也就是说不保证 $L=\sum_{i=1}^n l_i$。

### 题目思路

本题与瑞瑞的木板唯一区别，即不保证 $L=\sum_{i=1}^n l_i$。为了方便我们贺代码，我们可以自己加一块长度为 $L-\sum_{i=1}^n l_i$ 的木板。这时耗费体力肯定不变。

那么这题就完美的变成了瑞瑞的木板。接下来，我们按照合并果子的贪心思想，每次切最小的即可。详细的贪心证明可以去看 [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) 的题解。


### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	multiset<long long>s;
	long long n,l,ss=0;
	cin>>n>>l;
	for(int i=1;i<=n;i++)
	{
		long long x;
		cin>>x;
		s.insert(x);
		ss+=x;
	}
	if(l-ss!=0)s.insert(l-ss);//插入新的小木板
	long long sum=0;	
	while(s.size()>1)
	{
		long long x=*s.begin();
		s.erase(s.begin());
		long long y=*s.begin();
		s.erase(s.begin());
		s.insert(x+y);
		sum+=x+y;
	}
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：fish_love_cat (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_abc252_f)。

[不理解题意的戳这 ~~（题面可能是错误的？）~~。](https://www.luogu.com.cn/discuss/550624)

[瑞瑞的木板](https://www.luogu.com.cn/problem/P1334)和[合并果子](https://www.luogu.com.cn/problem/P1090)的原题，可以直接贪心。

**贪心证明**：逆向思考，把切断视作合并。如果长的越早合并，代价也就会越大，所以应该让小的先合。因为代价是合并起来的长度之和，所以优先让较小的两段合并，代价也自然被控制到了最小。

**注意：剩余面包也是需要切割的一段！！！**

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long,vector<long long>,greater<long long> >q;//优先队列，原本是从大到小来的，加了一大堆东西让他从小到大来排。
long long ans;
int main(){
    long long n,f;
    cin>>n>>f;
    for(long long i=0;i<n;i++){
        long long s;
        cin>>s;
        f-=s;
        q.push(s);
    }
    if(f!=0){//剩余面包
        q.push(f);
        n++;
    }
    for(long long i=1;i<n;i++){
        long long sum=0;
        sum+=q.top();
        q.pop();
        sum+=q.top();
        q.pop();
        q.push(sum);//把两个之和重新压入队列
        ans+=sum;//统计代价
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：shenbairui (赞：2)

是不是感觉和[合并果子](https://www.luogu.com.cn/problem/P1090)很像？那就考虑倒着来，那肯定会有人问怎么倒着来 : 把切割操作变为合并，题目变为把几个小朋友的面包合成一个大面包。很容易想到贪心，每次合并最小的两块代价为两块长度之和。要是有剩下面包 就把剩下的看成第 0 个小朋友要分到的面包 。

### 上代码吧 ！ （ 请勿复制 ）

```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long,vector<long long>,greater<long long> >q;
long long ans;
int main(){
    long long n,l;
    cin>>n>>l;
    for(long long i=0;i<n;i++){
        long long x;
        cin>>x;
        l-=x;
        q.push(x);
    }
    if(l!=0){
        q.push(l);
        n++;
    }
    for(long long i=1;i<n;i++){
        long long m=0;
        m+=q.top();
        q.pop();
        m+=q.top();
        q.pop();
        q.push(m);
        ans+=m;
    }
    cout<<ans;
    return 0;
}
```


下期见 ！ 拜拜 ！

---

## 作者：GI录像机 (赞：1)

## 题意：

有一块长度为 $L$ 的面包，现在要将其切成 $n$ 块分给 $n$ 个小朋友，第 $i$ 个小朋友需要一块长度为 $a_i$ 的面包，允许剩下一些没有分出去的面包。每次操作可以将一块面包切成任意长度的两块，代价为这块面包的长度。问把面包分出去的最小代价。

## 思路：

是不是感觉和合并果子很像？那就考虑倒着来，把切割操作变为合并，题目变为把几个小朋友的面包合成一个大面包。很容易想到贪心，每次合并最小的两块，代价为两块长度之和。要是有剩下面包呢？不妨~~让自己成为小朋友~~，把剩下的看成第 $0$ 个小朋友要分到的面包。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, x, ans, k, m;
priority_queue<int, vector<int>, greater<int> >q;
signed main() {
	cin >> n >> k;
	m = k;
	for (int i = 1; i <= n; i++) {
		cin >> x, q.push(x);
		m -= x;
	}
	if (m)q.push(m);
	while (q.size() >= 2) {
		int a = q.top();
		q.pop();
		int b = q.top();
		q.pop();
		ans += a + b;
		q.push(a + b);
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：CQ_Bob (赞：0)

## 分析

因为我们在据开面包后，所有面包的长度和是不变的。所以我们考虑将面包的分割和结果想象成线段连成的树，从叶子节点往上推，变成合并面包。

叶子节点是什么？就是每个小朋友所要的面包与最后剩下的面包。而剩下的面包的长度，我们还是根据第一句话的结论来想，不难发现就是面包总长度减去小朋友们需要的面包长度和。

为了使答案最小，我们每次合并的两个面包的长度应该是优先合并最短的两个。因为：若有三个面包 $a,b,c$，$a < b < c$，如果先合并 $a,b$，再将结果与 $c$ 合并，代价是 $(a+b)+((a+b)+c)$，即 $2 \times (a+b)+c$。如果先合并 $a,c$，再将结果与 $b$ 合并，代价是 $(a+c)+((a+c)+b)$，即 $2 \times (a+c)+b$。先合并 $b,c$ 同理。不难发现，第一种的代价是最小的，即从小到大合并必为最优。

维护最小值，我们只需要一个小根堆，因为小根堆内部元素是按不下降，即从小到大排列的。


注：合并之后的面包，只要不是最初的面包（根），就需要加入队列继续合并。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
const int N=1e6+10;
int a[N];
int ans;
signed main()
{
	priority_queue<int,vector<int>,greater<int> > qu;//小根堆
	cin>>n>>k;
	for(int i=1;i<=n;i++) 
		cin>>a[i],qu.push(a[i]),k-=a[i];
	if(k>0) qu.push(k);
	while(qu.size()>=2)//没合并到根就合并
	{
		int ans1=qu.top();qu.pop();//最短的两个面包
		int ans2=qu.top();qu.pop();
		ans+=ans1+ans2;//合并的代价
		qu.push(ans1+ans2);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：wnsyou (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc252_f)

好眼熟啊……

## 题意

有一个长度为 $l$ 的~~扩散性百万甜~~面包要分给 $n$ 个小朋友，第 $i$ 个小朋友想要**一根**长度为 $a_i$ 的面包，保证 $\sum\limits_{1\leqslant i \leqslant n} a_i \leqslant l$，注意是小于等于，即面包可以有剩余。

你可以切面包若干次，每次切面包都需要花费一定力气，每次选择一个长度为 $x$ 的面包，可以将其切成两块长度分别为 $a$ 和 $b$ 的面包，需要满足：$1 \leqslant a,b \leqslant x$ 且 $a + b = x$，花费力气为 $x$。

求满足每个小朋友的愿望最少需要多少力气。

## 思路

正着来做，你并不知道每次该怎么切，所以考虑反着做。

既然是反着做，那么切面包就可以看作是把两个长度分别为 $a$ 和 $b$ 的面包合并成一个长度为 $a + b$ 的面包，耗费力气 $a + b$。

欸，这不就是[合并果子](https://www.luogu.com.cn/problem/P1090)吗？

但是需要注意的是，这里可能还有一个长度为 $l - \sum\limits_{1\leqslant i \leqslant n} a_i$ 的面包，**我们肯定不会去切这块面包**，所以这里必然只是一根，需要注意。

按照合并果子的贪心做法，每次选择两个较小的面包合在一起，计算答案即可。

**记得开`long long`。**

总时间复杂度：$O(n \log n)$。

## 代码

```cpp
#include <iostream>
#include <queue>

using namespace std;
using ll = long long;

int n, x;
ll l, sum, ans, a;
priority_queue<ll, vector<ll>, greater<ll>> pq; // 小根堆维护长度最小的面包

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> l;
  for (int i = 1; i <= n; i++) {
    cin >> x, sum += x, pq.push(x);
  }
  if (sum < l) { // 特殊处理剩下的那一根面包
    pq.push(l - sum);
  }
  while (pq.size() > 1) { // 合并果子，不用多说
    a = pq.top(), pq.pop(), a += pq.top(), pq.pop(), ans += a, pq.push(a);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：_dijkstra_ (赞：0)

整活：[切面包](https://www.luogu.com.cn/problem/AT_abc252_f)变成了[合并果子](https://www.luogu.com.cn/problem/P1090)。

## 思路

与其思考怎样把面包分成小块，不如**逆向思考**：把小块合成大面包。

每次的代价显然就是 $a_i + a_j$。这个时候，我们来看[合并果子](https://www.luogu.com.cn/problem/P1090)，你会发现一模一样！

所以用堆维护即可。惟一不同点在于，如果 $L$ 分完后还有剩余，这一小块也要算上。

---

这里还是说说合并果子的做法：

维护一个小根堆，每次取出最小和次小的元素，合并两个元素并计算收益。

记得开 `long long`。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
int main()
{
	priority_queue <ll, vector <ll>, greater <ll> > q;
	int n;
	ll sum, ans = 0;
	scanf("%d%lld", &n, &sum);
	for (int i = 1; i <= n; i++)
	{
		int x; scanf("%d", &x);
		q.push(x), sum -= x;
	}
	if (sum != 0) q.push(sum);
	while (q.size() != 1) //分面包 -> 合并果子 233333
	{
		ll u = q.top(); q.pop();
		ll v = q.top(); q.pop();
		ans += (u + v), q.push(u + v);
	}
	cout << ans;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Zikake (赞：0)

# 题目意思
给你 $1$ 个面包，长 $L$，有 $n$ 个孩子想要一根长度为 $A_i$ 的面包，耗费的代价也是 $A_i$。现在要把这根面包分给孩子们。

# 思路

这道题还说可以有剩余，于是我们最后可以加一块长度为 $L- {\textstyle \sum_{i=1}^{n}} l_i$ 的面包，再进行合并果子的操作。

# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,L;
int ans;
priority_queue<int,vector<int>,greater<int> >Q;
signed main(){
	cin>>n>>L;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		L-=x;
		Q.push(x);
	}
	if(L)Q.push(L);
	while(Q.size()>=2){
		int x=Q.top();
		Q.pop();
		int y=Q.top();
		Q.pop();
		Q.push(x+y);
		ans+=(x+y);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc252_f)
# 题目描述
一根长度为 $L$ 的线段，需要将线段分成许多段，其中有 $n$ 段的长度为 $A_{1},A_{2},A_{3},\dots,A_{n}$。

其中每一次切割的代价为切割前线段的长度。

同时不保证 $\sum\limits_{i=1}^{n}A_{i}=L$，即可能有剩余。
# 题目分析
### 首先一个结论
每一次切割都切割剩余中最小的。
### 证明
如果长的越早合并，代价也就会越大，所以应该让小的先合。

因为代价是合并起来的长度之和，所以优先让较小的两段合并，代价也最小。
### 所以
我们使用一个小根堆，维护当前最小的两个线段长度，再用一个 $ans$ 记录答案，这道题就完美的做完了。
### 注意
剩下的线段成都也可以视为一根线段，只需要特判一下就可以解决这个 `bug` 了。
# 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
int n,l;
int ans,cnt;
signed main() {
	cin>>n>>l;
	priority_queue<int>q;
	for(int i=0,a;i<n;i++){
        cin>>a;
        cnt+=a;
		q.push(-a);
	}
    if(cnt<l)q.push(cnt-l);
	while(q.size()>1){
		int t1=q.top();
		q.pop();
		int t2=q.top();
		q.pop();
		ans+=-(t1+t2);
		q.push(t1+t2);
	}
    cout<<ans;
}

```

---

## 作者：Symbolize (赞：0)

# 思路
这和 [P1334](https://www.luogu.com.cn/problem/P1334) 没什么区别啊！

首先我们思考一下最终状态，如果面包刚好分完，那么最终状态即为每个小朋友要的面包长度所构成的集合。否则，则会多加入总长度减去所有小孩需求的和的结果一元素。而拆分成每种状态则必定切了一刀，那我们就可以使用合并累加的方法，因为要使答案最小，所以每次取出截止目前的两个最小状态，答案累加这两状态的长度和，再将这一合并后的新状态放入序列之中，那么这个操作就可以使用小根堆来实现。
# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e3+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,L,ans;
priority_queue<int,vector<int>,greater<int> > q;//小根堆 
signed main()
{	
	cin>>n>>L;//输入 
	rep1(i,1,n)
	{
		int x;
		cin>>x;
		q.push(x);//每个小朋友的需求 
		L-=x;
	}
	if(L) q.push(L);//如果没有刚好分完，剩下的一部分也要加入序列之中 
	while(q.size()>1)//元素大于等于2 
	{
		int l=q.top();
		q.pop();
		int r=q.top();
		q.pop();
		ans+=l+r;//答案累加 
		q.push(l+r);//新的状态 
	}
	cout<<ans<<endl;//输出 
	return 0;
}
```

---

## 作者：max666dong123 (赞：0)

## 题意
你有一根长度为 $L$ 的面包，现在你要将它分给 $N$ 个孩子，第 $i$ 个孩子想要一根长度为 $A_i$ 的面包。

对于一根长度为 $k$ 的面包，你可以选择一个在 $1 \sim k-1$ 的整数 $x$，将面包切分成长度为 $x$ 和 $k−x$ 的两部分，这将花费 $x$ 的代价。

第 $i$ 个孩子获得的面包长度**必须**为 $A_i$，但我们允许有面包剩余。

请你花费**最少**的代价，将这根面包分给孩子们。

## 思路

这道题用贪心来解。

我们把题目倒过来想，将 $A_1 \sim A_n $ 的数拼成 $L$，由于 $\sum_{i=1}^n A_i$ 有可能比 $L$ 要小，而第一次拆的时候会花费 $L$ 的代价，而反着想就没有算到。

我们的贪心策略是在所有的面包中找出**最小**的两个数，拼接在一起。

证明：

假设有 $x,y,z$ 三个数，满足 $x<y<z$。一共有三种拼法。

第一种：先拼 $x,y$，花费 $x+y$，再将 $x+y$ 和 $z$ 拼在一起，花费 $(x+y)+z$，总共花费 $(x+y)+(x+y)+z$。

第二，三种同理，可以得到 $(x+z)+(x+z)+y$ 和 $(y+z)+(y+z)+x$ 相减可以得出 $(x+y)+(x+y)+z$ 最小。

得证。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
priority_queue<int,vector<int>,greater<int> >q;
int n,L;
signed main(){
	IOS;
	cin>>n>>L;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		q.push(x);
		L-=x;
	}
	if(L)q.push(L);
	int ans=0;
	while(q.size()>=2){
		int x=q.top();q.pop();
		int y=q.top();q.pop();
		ans=ans+x+y;
		q.push(x+y);
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：_shine_ (赞：0)

### 1. 题目大意
现在有一根长度为 $l$ 的面包，你要分给 $n$ 个孩子，使得每个孩子分到的长度等于 $a_i$，允许有剩余，但是每次分长度为 $x$ 的面包的代价是 $x$，现在问你最小的代价。
### 2. 思路分析
不难发现一个简单的性质：既可以正着分同样也可以反着分，正着来显然不太可能，考虑逆向把分出的面包结合成一块整的面包快，即每次的代价为 $a_i+a_j$，显然使用优先队列维护每次的 $a_i$。

但是，你会发现，在本题中，答案会有错误，因为逆向合并中会留有剩余情况，此时应该判断是否能使得在每个人想要的面包快加起来能把面包分解完，并在没有的情况中加入剩下的那块，因为那块也需要分出来，此时即可通过。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
priority_queue<int,vector<int>,greater<int> >q;
int n,l;
int a[maxn];
int ans=0;
signed main(){
	cin >> n >> l;
	for(int i=1;i<=n;++i){
		cin >> a[i];
		l-=a[i];
		q.push(a[i]);
	}
	if(l!=0){
		q.push(l);
		n++;
	}
	for(int i=2;i<=n;++i){
		int cnt=q.top();
		q.pop();
		cnt+=q.top();
		q.pop();
		q.push(cnt);
		ans+=cnt;
	}
	cout << ans << endl;
	return 0;
}
/*
3 1000000000000000
1000000000 1000000000 1000000000
*/
```


---

