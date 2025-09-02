# Different Strokes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_c

高橋くんと青木さんの前に $ N $ 皿の料理が置かれています。 便宜上、これらの料理を料理 $ 1 $、料理 $ 2 $、…、料理 $ N $ と呼びます。

高橋くんが料理 $ i $ を食べると彼は $ A_i $ ポイントの *幸福度* を得ます。 また、青木さんが料理 $ i $ を食べると彼女は $ B_i $ ポイントの幸福度を得ます。

彼らは、高橋くんから始めて交互に、料理を $ 1 $ 皿ずつ選んで食べることを料理が尽きるまで続けます。 ただし、彼らはともに、「最終的に自分が得る幸福度の総和」から「最終的に相手が得る幸福度の総和」を引いた値を最大化するように料理を選びます。

このとき、「最終的に高橋くんが得る幸福度の総和」から「最終的に青木さんが得る幸福度の総和」を引いた値はいくつになるでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ B_i\ \leq\ 10^9 $
- 入力される値はすべて整数である。

### Sample Explanation 1

この例では、二人のどちらも、料理 $ 1 $ を食べると $ 10 $ ポイント、料理 $ 2 $ を食べると $ 20 $ ポイント、料理 $ 3 $ を食べると $ 30 $ ポイントの幸福度を得ます。 この場合、高橋くんと青木さんの「好み」が一致しているため、彼らは毎回残っている料理のうち最も幸福度を多く得られる料理を選びます。よって、最初に高橋くんは料理 $ 3 $ を選び、次に青木さんは料理 $ 2 $ を選び、最後に高橋くんが料理 $ 1 $ を選ぶため、答えは $ (30\ +\ 10)\ -\ 20\ =\ 20 $ です。

### Sample Explanation 2

この例では、高橋くんは料理 $ 1,2,3 $ のいずれを食べても $ 20 $ ポイントの幸福度を得ますが、青木さんは料理 $ 1 $ を食べると $ 10 $ ポイント、料理 $ 2 $ を食べると $ 20 $ ポイント、料理 $ 3 $ を食べると $ 30 $ ポイントの幸福度を得ます。 今回は、青木さんのみに料理の好き嫌いがあるため、彼らは毎回残っている料理のうち青木さんが最も幸福度を多く得られる料理を選びます。よって、最初に高橋くんは料理 $ 3 $ を選び、次に青木さんは料理 $ 2 $ を選び、最後に高橋くんが料理 $ 1 $ を選ぶため、答えは $ (20\ +\ 20)\ -\ 20\ =\ 20 $ です。

### Sample Explanation 3

答えは $ 32 $ ビット整数に収まらない可能性があります。

## 样例 #1

### 输入

```
3
10 10
20 20
30 30```

### 输出

```
20```

## 样例 #2

### 输入

```
3
20 10
20 20
20 30```

### 输出

```
20```

## 样例 #3

### 输入

```
6
1 1000000000
1 1000000000
1 1000000000
1 1000000000
1 1000000000
1 1000000000```

### 输出

```
-2999999997```

# 题解

## 作者：letianJOE (赞：2)

# 题目大意

$n$ 个物品，对于每个物品，高桥取幸福总和加 $a_i$,而青木取幸福总和加 $b_i$，一个物品只能选一次，高桥和青木交替选，求高桥的幸福总和减青木的幸福总和的值最大。

---

# 思路

## 分析

首先，题目很明显要用贪心来做，但是怎么贪呢？这是个好问题。

我思考了许久，直到我看到了数据范围 $1\ \leq\ N\ \leq\ 10^5$ 这个数据范围，你想到了什么基础的贪心会考的做法。

很明显，要用排序，至于怎么排，继续往下看。

首先，假如有两个物品，他就会有一个类似性质一样的东西吧。

如果 $a_i + b_i > a_j + b_j$，那么 $a_i-b_j > a_j - b_i$，那么这一题就很简单了，只需要用结构体排序 $a_i + b_i$ 即可。

---

## 细节

首先，是高桥先选，不是青木。

$a_i$ 和 $b_i$ 都会到 $10^9$,会爆 int，记得开 long long，不然样例都过不去。

---

# CODE

`Talk is cheap.Show me the code. —— Aprendiz`

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,gq,qm; //gq是高桥，qm是青木
struct happines //定义结构体
{
	int a,b;
}happy[100005];
bool cmp(happines x,happines y) //结构体排序
{
	return x.a-x.b>y.a-y.b;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) //输入
		cin>>happy[i].a>>happy[i].b;
	sort(happy+1,happy+n+1,cmp);
	for(int i=1;i<=n;i+=2) //高桥先
		gq+=happy[i].a;
	for(int i=2;i<=n;i+=2)
		qm+=happy[i].b;
	cout<<gq-qm; //输出
	return 0;
}

```


---

## 作者：封禁用户 (赞：1)

本质是个贪心。

题目大意：有 $n$ 盘菜，第 $i$ 盘菜高桥吃了能获得 $a_i$ 幸福感，青木吃了能获得 $b_i$ 幸福感，他俩轮流选菜吃，高桥先吃，求高桥最大幸福感减青木最大幸福感的值。

这种题一看就是贪心吧？大家可以先拿张纸推一推。

经过一番冥想（时间挺长的）我终于发现，以 $(a[i]+b[i])$ 的形式从大到小排序，然后用这个数组不操作轮流计算二人的最大幸福感就能得到最终答案。不信可以去拿样例试试去。

然后就是代码了。因为是双关键字排序，我们就不能直接用数组了，需要一个 $id$ 记录编号”转接“一下，今天我们不用结构体，感兴趣的盆友可以拿结构体去写一写，好的上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[100010], b[100010];
int id[100010]; // 转接id
long long qwqa = 0, qwqb = 0;

bool cmp(int x, int y){ return (a[x] + b[x]) > (a[y] + b[y]); } // (a[i]+b[i])从大到小

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) scanf("%d %d", &a[i], &b[i]), id[i] = i;
    sort(id + 1, id + n + 1, cmp); // 以cmp模式排序
    for (int i = 1; i <= n; i += 2) qwqa += a[id[i]]; // 高桥先吃
    for (int i = 2; i <= n; i += 2) qwqb += b[id[i]]; // 青木后吃
    printf("%lld\n", qwqa - qwqb); // 相减
    return 0; // 这题把我搞饿了，等我交上题解后吃零食摆烂去！qwq
}
```



---

## 作者：sxq9 (赞：1)

我们看一看题面，利用贪心算法，那如何贪心呢？

因为大家都想让差最大，即
$$a_i-b_j>a_j-b_i$$
或
$$b_i-a_j>b_j-a_i$$
那么根据不等式的性质可得
$$a_i+b_i>a_j+b_j$$
考虑使用优先队列。

将 $a_i,b_i,a_i+b_i$ 入队，依次吃即可。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010],c[100010];
bool operator <(pair<int,pair<int,int>>x,pair<int,pair<int,int>>y){
	return x.first>y.first;//因为优先队列默认小根堆，所以要写大于号
}
int main(){
	priority_queue<pair<int,pair<int,int>>>q;
	int n;
	long long s=0,s2=0;
	cin>>n;
	int a,b;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		q.push(make_pair(a+b,make_pair(a,b)));
	}
	pair<int,int>x;
	for(int i=1;i<=n;i++){
		x=q.top().second;q.pop();
		if(i%2==1)s+=x.first;
		else s2+=x.second;
	}
	cout<<s-s2;
	return 0;
}
```
提示：十年 OI 一场空，不开 $long\space long$ 见祖宗。 

---

## 作者：Archy_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_qual_c)

## 题目简述：

有 $n$ 道菜，有 $A$，$B$ 两个人，其中每道菜 $A$ 吃可获得的幸福值为 $Ah_i$，$B$ 吃则获得 $Bh_i$。从 $A$ 开始两人轮流吃，对于菜的顺序没有要求，求 $A$ 最终获得的幸福值减去 $B$ 的最大值。

## 思路:

要求 $A$ 最终获得的幸福值减去 $B$ 的最大值，那么 $A$ 要尽可能大，$B$ 要尽可能小，显然我们需要排序这些值。

怎么排呢？假设我们已经排过序了，高桥先选，则需满足 

$$Ah_i-Bh_j > Bh_i-Ah_j$$

其中 $j=i+1$，表示 $A$ 选择了 $Ah_i$，$B$ 选择 $Bh_j$，要想 $A$ 最大，$B$ 最小，由此我们可得以上等式。例如下情况。
```
20 10
1 10
```
显然 $A$ 选 $20$，下一次 $B$ 选 $10$ 为最优解。

由上不等式，移动得到

$$Ah_i + Bh_i > Ah_j + Bh_j$$

因此按照此不等式排序即可。

## code:
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,A,B;
  
struct node{
	long long Ah,Bh,Ch;//开long long！ 
}a[100005]; 
  
bool cmp(node x,node y){
	return x.Ch>y.Ch;
}
  
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].Ah>>a[i].Bh;
		a[i].Ch=a[i].Ah+a[i].Bh;//Ch记录Ah+Bh
	}
  
	sort(a+1,a+n+1,cmp);//排序
  
	for(int i=1;i<=n;i++){//加答案
		if(i%2==1)A+=a[i].Ah;
		else B+=a[i].Bh;
	}
	cout<<A-B<<"\n"; //要换行
	return 0;
}
```

---

## 作者：_zhx (赞：0)

# AT_nikkei2019_qual_c Different Strokes

## 大致解法

这道题是贪心。

经过思考，我发现：如果以 $a[i]+b[i]$ 的形式从大到小排序，然后用这个数组轮流计算二人获得的最大幸福，再将高桥获得的最大幸福减去青木获得的最大幸福，就能得到最终答案。

### 代码处理

因为是双关键字排序，如果不用结构体，我们就不能直接用数组了，需要一个 $c$ 数组记录编号，这样，就可以起到结构体的作用。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],b[100010],c[100010],l=0,r=0;
//l是高桥，r是青木，c用来记录编号
bool cmp(int x,int y){return a[x]+b[x]>a[y]+b[y];} //排序
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i],&b[i]), c[i]=i;
    sort(c+1,c+n+1,cmp);
    for (int i=1;i<=n;i+=2)
	{
		if(i&1) l+=a[c[i]]; //高桥的最大幸福
		else r+=b[c[i]]; //青木的最大幸福
	}
    printf("%lld\n",l-r);//相减输出
    return 0; 
}
```

---

## 作者：a2410078823 (赞：0)

## 题目大意：
有 $n$ 盘菜，第 $i$ 盘菜高某吃了能获得 $a_i$ 幸福感，青某吃了能获得 $b_i$ 幸福感，他俩轮流选菜吃，高某先吃，求高某最大幸福感减青某最大幸福感的值。
## 思路：
~~挺好一道题，难度还行~~。

我们考虑对于每一个人来说，假设他选的集合是 $S$ ，他要最大化这个东西：

$$ \sum_{i \in S} a[i]- \sum_{i ∉ 1} b[i] $$

如果我们假设 $ B = \sum_{i = 1}^{n} b[i] $ ，那么上式可化为：

$$ ( \sum_{i \in S} a[i] + b[i]) -B $$

因此不管是谁，都应该尽量选择 $a[i]+b[i]$ 大的位置上的数。直接用一个堆维护一下就可了。（~~不过好像可以直接排一下序就可以啦，我似乎傻掉了~~）

注意：是高某先选，不是青某。 $a_i$ 和 $b_i$ 都会到 $10^9$ ,会爆 `int`，记得开 `long long`，不然样例都过不去。


## CODE :
（直接复制粘贴并提交有惊喜）
```cpp
#include<bits/stdc++.h>
#define I using
#define AK namespace
#define IOI std
I AK IOI;

const int N = 1e5 + 7;
int n, a[N], b[N];
long long ans;

struct cmp 
{
    int operator () (const int &x, const int &y) const {
        return a[x] + b[x] < a[y] +b[y]; 
    }
};
priority_queue<int, vector<int>, cmp> q;

int main() 
{
    cin>>n;
    for (int i = 1; i <= n; ++i) cin>>a[i],cin>>b[i], q.push(i);
    for (int i = 1; i <= n; ++i) if (i & 1) ans += a[q.top()], q.pop(); else ans -= b[q.top()], q.pop();
    cout<<ans<<endl;
}

```

---

## 作者：大宝和小宝 (赞：0)

题意：给出 $n$ 种食物，高桥吃下获得 $a_i$ 快乐值，青木吃下获得 $b_i$ 快乐值，两人轮流吃，他们的目标是最大化自己获得的快乐值减去对方获得的快乐值，问最后该值是多少。

思路：已知高桥要最大化答案而青木要最小化答案，考虑全部食物由青木吃下，则 $ans=-(b_1+b_2+.... +b_n)$，但高桥会吃下一些食物，则这时候高桥吃下食物获得的快乐值为 $a_i+b_i$，排序贪心取即可。

---
```c
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int INF = 0x3f3f3f3f;
const double eps = 1e-6;
const int maxn = 1e5 + 10;
const int maxm = 1e6 + 10;
const ll mod =  998244353;

int a[maxn];

int main() {
    int n;
    scanf("%d",&n);
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i] = x + y;
        ans -= y;
    }
    sort(a, a + n);
    int cur = 1;
    for(int i = n - 1; i >= 0; i--) {
        if(cur) ans += a[i];
        cur ^= 1;
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：WOERDESUGX (赞：0)

本蒟蒻又来写题解啦~~话说我为什么一直在说这句话啊~~。

-------------------

### 题目大意

给你 $n$ 个 $a$ 和 $b$，分别表示有 $n$ 份菜，高桥吃了会增加 $a$ 的幸福度，青木吃了会增加 $b$ 的幸福度，高桥先吃青木后吃两人交替进行，他们每次会选择使自己吃了之后最后的幸福度较大的一份菜，求高桥的幸福度减青木的幸福度的最大值。

----------------------

### 题目思路

不难看出这是一个贪心那如何贪呢？

经过我的苦思冥想我明白了，我们假设上一份菜对两人的幸福度加幅和为 $sum_i$，当前菜对两人的幸福度加幅和为 $sum_j$，将他们从大到小排序，易得 $sum_i>sum_j$ 即 $a_i+b_i>a_j+b_j$，由此可知 $a_i-b_j>a_j-b_i$，所以当我们将菜对两人的幸福度加幅和进行从大到小的排序后，则可不用判断下一个。


------------

### $ACcode$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct Node{
	int a,b;
	long long Fool;
}Nt[114514];
bool cmp(Node x,Node y) { return x.Fool>y.Fool; }
long long ansg,ansq;
int main()
{
	scanf("%d",&n); 
	for(int i=1;i<=n;++i) {
		scanf("%d%d",&Nt[i].a,&Nt[i].b);
		Nt[i].Fool=Nt[i].a+Nt[i].b;
	}
	sort(Nt+1,Nt+1+n,cmp);
	for(int i=1;i<=n;++i) {
		if(i&1) ansg+=Nt[i].a;
		else ansq+=Nt[i].b;
	}
	cout<<ansg-ansq<<endl;
	return 0;
}
```


---

