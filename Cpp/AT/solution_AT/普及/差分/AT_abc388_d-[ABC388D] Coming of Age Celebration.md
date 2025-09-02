# [ABC388D] Coming of Age Celebration

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc388/tasks/abc388_d

ある星には $ N $ 人の宇宙人がおり、全員未成年です。

$ i $ 人目の宇宙人は現在 $ A_i $ 個の石を所持しており、ちょうど $ i $ 年後に成人します。

この星では誰かが成人するとき、石を $ 1 $ 個以上所持している**成人**全員が、成人する宇宙人に成人祝いとして石を $ 1 $ 個渡します。

$ N $ 年後に各宇宙人が所持している石の個数を求めてください。

ただし、今後新たな宇宙人は産まれないものとします。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 5\ \times\ 10^5 $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ i $ 人目の宇宙人が持っている石の個数を $ C_i $ で表します。 はじめ $ (C_1,\ C_2,\ C_3,\ C_4)\ =\ (5,\ 0,\ 9,\ 3) $ です。 $ 1 $ 年後には $ (C_1,\ C_2,\ C_3,\ C_4)\ =\ (5,\ 0,\ 9,\ 3) $ となります。 $ 2 $ 年後には $ (C_1,\ C_2,\ C_3,\ C_4)\ =\ (4,\ 1,\ 9,\ 3) $ となります。 $ 3 $ 年後には $ (C_1,\ C_2,\ C_3,\ C_4)\ =\ (3,\ 0,\ 11,\ 3) $ となります。 $ 4 $ 年後には $ (C_1,\ C_2,\ C_3,\ C_4)\ =\ (2,\ 0,\ 10,\ 5) $ となります。

## 样例 #1

### 输入

```
4
5 0 9 3```

### 输出

```
2 0 10 5```

## 样例 #2

### 输入

```
5
4 6 7 2 5```

### 输出

```
0 4 7 4 9```

## 样例 #3

### 输入

```
10
2 9 1 2 0 4 6 7 1 5```

### 输出

```
0 2 0 0 0 4 7 10 4 10```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc388_d)

### 思路

可以使用**优先队列**解决此题。

不难考虑到暴力思路：当遍历到 $i$ 时，将前 $i-1$ 个不为 $0$ 的数都减 $1$，并将不为 $0$ 的数字个数加在 $A_i$ 上。

然后发现，假设 $A_i$ 足够大，第 $i$ 位要送出的石头个数为 $A_i-N+i$。然后考虑 $A_i$ 不够大的情况，最终 $A_i=0$，并且它为后面数的贡献会减小。

考虑优先队列进行优化。每一次将贡献为 $0$ 的外星人全部弹掉，剩下的外星人都能为当前位做贡献，$A_i$ 直接加上容器的大小，然后再将 $A_i$ 放入队列中。

最终答案有可能为 $0$，故输出 $\max(0,A_i-N+i)$。

由于使用了优先队列，时间复杂度为 $\mathcal{O}(N\log N)$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=5e5+10;
int a[N];
struct node{
	int x,id;
	friend bool operator<(const node cmp_x,const node cmp_y){
		return cmp_x.x>cmp_y.x;
	}
};priority_queue<node>pq;
signed main(){
	int n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=n;++i){
		a[i]+=pq.size();
		while(!pq.empty()&&pq.top().x-i<=0)
			pq.pop();
		if(a[i])
			pq.push({a[i]+i,i});
	}
	for(int i=1;i<=n;++i)
		printf("%lld ",max(0ll,a[i]-n+i));
	printf("\n");
	return 0;
}
```

---

## 作者：H_dream (赞：8)

注：2024.1.16 修改了一些表达上的错误
# 题目大意
有 $N$ 个外星人，一开始他们有 $A_i$ 个石头,第 $i$ 个外星人经过 $i$ 年后成年，同时得到其他**已经成年**的外星人**每人一个石头**，且每个人**最少有 $0$ 个石头**。求 $N$ 年后每个外星人的石头数量。

# 思路
## 暴力
我们按照年份从 $1 \sim n$ 遍历一次，当一个外星人成年时，对前面的人的石头数进行更新，时间复杂度：$O(n^2)$。
## 正解
通过前面的暴力，我们发现每次更新前面的石头时，除了已经没有石头的人之外，每人都需要减少一个石头，这里是重复的，有没有更好的办法呢？

我们逆向思维一下，一个人成年后会先得到前面的人的石头，再给后面的人每人一个石头，假设我们已经求出这个人得到石头后的数量，记为 $x$，则第 $i$ 个人最终的石头数 $ans = \max(0,x-(n-i))$。

进一步思考，当 $x \ge n-i$ 时，意味着这个人有足够的石头给后面所有人；而当 $x < n-i$ 时，意味着这个人只能给他后面 $x$ 个人石头。并且这个区间连续，于是我们可以先给下一个做一个标记，等到遍历时，再加上，这也就是我们常说的差分。
## 实现
先构造好差分数组 $b$ ，第一种情况下，直接将 $b_{i+1}$ 加上一即可，而第二种情况下，还需要将 $b_{i+x+1}$ 减去一。
# 代码参考

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+10;
int n,a[N],b[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
  for(int i=1;i<=n;++i) b[i]=a[i]-a[i-1];//构造差分数组
	for(int i=1;i<=n;++i){
		a[i]=b[i]+a[i-1];//先拿走前面的人的石头
		int ans=a[i]-n+i;//减去给后面的人的石头
		b[i+1]++;
		if(ans<0){
			b[i+a[i]+1]--;
			cout<<0<<' ';
		}
		else cout<<ans<<' ';
	}
	return 0;
}
```

---

## 作者：xyx404 (赞：4)

## 思路：
模拟。

定义一个变量 $give$ 表示现在可以给珠子的人数，再定义一个数组 $R$，$R_i$ 表示有多少人只能给到第 $i$ 个人。

每一个成年的人在自己还要珠子的时候必须要给刚刚成年的人一个珠子，所以第 $i$ 个人要给 $n-i$ 个珠子，可以得到 $give$ 个珠子，如果第 $i$ 个人的数量加上之前成年的人给他的数量不够给后面所有的刚成年的，那么计算他能给到第几个人，更新 $R$ 数组，并让 $give$ 加一还要记得把 $A_i$ 修改为 $0$；如果够那么 $A_i$ 就等于他加上 $give$ 后给减去他成年后还有多少个未成年的数量，$give$ 也要加一。

更新完第 $i$ 个人后让 $give$ 减去只能给到第 $i$ 个人的数量，也就是 $R_i$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
LL T=1;
LL n;
LL a[int(5*1e5+10)];
LL R[int(5*1e5+10)];
int main(){
//	cin>>T;
	while(T--){
		cin>>n;
		int give=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			
//			cout<<give<<"\n";
			if(a[i]-(n-i)+give<0){
				R[a[i]+give+i]++;
				a[i]=0;
			}
			else{
				a[i]=a[i]-(n-i)+give;
			}
			give++;
			give-=R[i];
			cout<<a[i]<<" ";
		}
		
	}
	return 0;
}


```

---

## 作者：StormWhip (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc388_d)  
## 思路
从前往后依次考虑第 $i$ 个外星人宝石的流向：
- 它可能会收到排在其前面的成年外星人送出的宝石，但这一步在之前已经处理过了，因为是从前往后处理的。
- 它可能会将自己的宝石送给排在其后面的即将成年的外星人。
  
因此我们只需要处理送宝石的部分。不难发现，一个成年外星人会将其所有的宝石**尽可能多地**送给排在其后面的外星人。所以：
- 如果一个外星人的宝石足够送给其后面的每一个外星人，那么它就会这样做，并将剩下的留给自己。
- 如果不够分给每一个，那么它将无所保留地把自己的宝石全部分给后面地外星人，直到分完为止。

不难发现我们只需要处理单点和区间修改，并在最后查询的操作。赛时使用**分块**实现。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,M=1e3+5;
int n,a[N],ans[N];
int len,tot,L[M],R[M],lazy[M],bel[N];
void Build()
{
	len=sqrt(n);
	tot=n/len;
	if(n%len!=0) tot++;
	for(int i=1;i<=tot;i++) L[i]=(i-1)*len+1,R[i]=i*len;
	R[tot]=n;
	for(int i=1;i<=n;i++) bel[i]=(i-1)/len+1;
}
void Update(int l,int r)
{
	if(l>r) return;
	int x=bel[l],y=bel[r];
	if(x==y)
	{
		for(int i=l;i<=r;i++) ans[i]++;
		return;
	}
	for(int i=l;i<=R[x];i++) ans[i]++;
	for(int i=x+1;i<y;i++) lazy[i]++;
	for(int i=L[y];i<=r;i++) ans[i]++;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	Build();
	for(int i=1;i<=n;i++)
	{
		ans[i]+=a[i];
		if(i==n) break;
		if(ans[i]+lazy[bel[i]]>=n-i)
		{			
			Update(i+1,n);
			ans[i]-=(n-i);
		}
		else
		{
			Update(i+1,i+ans[i]+lazy[bel[i]]);
			ans[i]=-lazy[bel[i]];
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]+lazy[bel[i]]<<" ";
	return 0;	
}
```

---

## 作者：FlowerAccepted (赞：3)

## 解题思路

这道题使用了差分的技巧。

  显然，每个外星人都只会向后面的外星人给石头，而且是在得到石头后；从前往后给，没有石头就不给了。 

注意到，第 $1$ 个外星人~~很可怜~~，没人给他石头，所以可以从他开始分配石头。

但给每一个外星人都一个一个加石头效率太低了，所以我们可以使用差分来优化。而这样计算每个外星人给出石头前拥有的石头又是一项很大的工程。于是我们在计算差分的同时计算差分的前缀和。

具体的，定义三个数组 $a$，$diff$ 和 $sum$，输入到 $a_i$ 的同时令 $diff_i \gets a_i - a_{i - 1}$

在计算第 $i$ 个外星人的结余时先借用 $a$ 数组存储这个外星人给出石头前、得到石头后的石头数，以备后用。具体的，令 $a_i \gets sum_{i - 1} + diff_i$。

然后计算这个外星人要给出多少石头。他最多要给出 $(n - i)$ 块石头，但取不取到这个值取决于他有没有足够的石头，如果没有，那么他就只能给出 $a_i$ 颗石头。综合来看，这个外星人要给出 $\min(n - i, a_i)$ 块石头。

在差分数组 $diff$ 上操作这个外星人的剩余石头数 $diff_i \gets diff_i - \min(n - i, a_i)$，但要维护后面的石头值不变，所以 $diff_{i + 1} \gets diff_{i + 1} + \min(n - i, a_i)$。

又要使第 $i + 1 \sim i + 1 + \min(n - i, a_i)$ 个外星人的石头数统统加上 $1$，我们再将 $diff_{i + 1} \gets diff_{i + 1} + 1$，$diff_{i + 1 + \min(n - i, a_i)} \gets diff_{i + 1 + \min(n - i, a_i)} - 1$。

最后计算这个外星人现在拥有的石头数，存在 $sum$ 数组里，$sum_i \gets sum_{i - 1} + diff_i$，核心代码就写完啦！

整合一下，就是

$$
\forall \space 1 \le i \le N, \\
\begin{aligned}
a_i &\gets sum_{i - 1} + diff_i, \\
diff_{i + 1} &\gets diff_{i + 1} + \min(n - i, a_i) + 1, \\
diff_{i + 1 + \min(n - i, a_i)} &\gets diff_{i + 1 + \min(n - i, a_i)} - 1, \\
diff_i &\gets diff_i - \min(n - i, a_i), \\
sum_i &\gets sum_{i - 1} + diff_i.
\end{aligned}
$$

写成代码，就是

```cpp
for (int i = 1; i <= n; i ++) {
    a[i] = sum[i - 1] + diff[i];
    diff[i + 1] += min(a[i], n - i) + 1;
    diff[i + min(a[i], n - i) + 1] --;
    diff[i] -= min(a[i], n - i);
    sum[i] = sum[i - 1] + diff[i];
}
```

最后依次输出 $sum$ 数组的每一项即可。

## 代码呈现

$\small\text{\color{#ff0000}{作者提示：}}$ 本代码使用了递归形式，如果不喜欢可以自己改一改。注意循环从小到大。

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int a[500005], diff[500005], sum[500005];

void dfs(int x, int n) {
    if (x == 1) {
        diff[x + 1] += min(a[x], n - x) + 1;
        diff[x + min(a[x], n - x) + 1] --;
        diff[x] -= min(a[x], n - x);
        sum[x] = a[x] = diff[x];
        return;
    }
    dfs(x - 1, n);
    a[x] = sum[x - 1] + diff[x];
    diff[x + 1] += min(a[x], n - x) + 1;
    diff[x + min(a[x], n - x) + 1] --;
    diff[x] -= min(a[x], n - x);
    sum[x] = sum[x - 1] + diff[x];
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        diff[i] = a[i] - a[i - 1];
    }
    dfs(n, n);
    for (int i = 1; i <= n; i ++) {
        cout << sum[i] << ' ';
    }
    return 0;
}

```

好吧好吧，还是附上一个迭代代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int a[500005], diff[500005], sum[500005];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        diff[i] = a[i] - a[i - 1];
    }
    for (int i = 1; i <= n; i ++) {
        a[i] = sum[i - 1] + diff[i];
        diff[i + 1] += min(a[i], n - i) + 1;
        diff[i + min(a[i], n - i) + 1] --;
        diff[i] -= min(a[i], n - i);
        sum[i] = sum[i - 1] + diff[i];
    }
    for (int i = 1; i <= n; i ++) {
        cout << sum[i] << ' ';
    }
    return 0;
}

```

至此，本题 Accepted。

## 复杂度分析

虽然是递归，但只会被调用 $N$ 次，所以算法的时间复杂度是 $O(N)$。

---

## 作者：HuangBarry (赞：3)

因为第 $i$ 个人成年肯定比后面的人快，所以第 $i$ 个人肯定要在石头量不为 $0$ 的情况下依次往后每人给 $1$ 块石头，所以我们可以直接给每个人减去 $\min(n-i,a_i)$ 块石头，然后给后面第 $i+1$ 个人到第 $i+\min(n-i,a_i)$ 个人每天一块石头。

这是单点查询区间修改？我们想到可以用线段树来做。

代码如下：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#include<atcoder/all>
#define stl_priority_queue std::priority_queue
#define pbds_priority_queue __gnu_pbds::priority_queue
#define to_string std::to_string
#define endl '\n'
#define Endl cout<<endl
#define Made return
#define by 0
#define Barry +0
#define Freopen(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace atcoder;
using uint=unsigned int;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
#define ls rt<<1
#define rs rt<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
int n,a[(int)5e5+55],sum0=0;
ll tr[4*((int)5e5+44)],lazy[4*((int)5e5+44)];
void push_up(int rt){
	tr[rt]=tr[ls]+tr[rs];
	return;
}
void push_down(int rt,int l,int r){
    if(lazy[rt]){
    	int mid=l+r>>1;
   		lazy[ls]+=lazy[rt];
		lazy[rs]+=lazy[rt];
    	tr[ls]+=lazy[rt]*(mid-l+1);
		tr[rs]+=lazy[rt]*(r-mid);
		lazy[rt]=0;
	}
	return;
}
void build(int rt,int l,int r){
	if(l==r){
		tr[rt]=a[l];
		return;
	}
	int mid=l+r>>1;
	build(lson);
	build(rson);
	push_up(rt);
}
ll ask(int rt,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr)
		return tr[rt];
    int mid=l+r>>1;
    push_down(rt,l,r);
    if(qr<=mid)
		return ask(lson,ql,qr);
    else if(mid<ql)
		return ask(rson,ql,qr);
	else
    	return ask(lson,ql,qr)+ask(rson,ql,qr);
}
void change(int rt,int l,int r,int ql,int qr,int k){
    if(ql<=l&&r<=qr){
        lazy[rt]+=k;
        tr[rt]+=k*(r-l+1);
        return;
    }
    int mid=l+r>>1;
    push_down(rt,l,r);
    if(ql<=mid)
		change(lson,ql,qr,k);
    if(mid<qr)
		change(rson,ql,qr,k);
    push_up(rt);
}
int main(){
    //Freopen("filename");
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=n;i++){
        int c=ask(1,1,n,i,i);
        change(1,1,n,i,i,-min(n-i,c));
        if(i!=n)//最后一个人不需要给任何人石头
            change(1,1,n,i+1,i+min(n-i,c),1);
    }
    for(int i=1;i<=n;i++)
        cout<<ask(1,1,n,i,i)<<" ";
    Endl;
    Made by Barry;
}
```

是不是觉得码量很大？

这时候 AtCoder 有个自己的神器，叫 Atcoder Library（ACL）。

里面有很多整合在一起的数据结构（还有其它的），比如线段树，带懒惰标记的线段树等等。

这时候我们就可以直接使用 ACL 中的 `lazy_segtree` 完成此题。

ACL 食用教程：[链接](https://www.luogu.com.cn/article/ukllc2l7)。

代码如下：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#include<atcoder/all>
#define stl_priority_queue std::priority_queue
#define pbds_priority_queue __gnu_pbds::priority_queue
#define to_string std::to_string
#define endl '\n'
#define Endl cout<<endl
#define Made return
#define by 0
#define Barry +0
#define Freopen(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace atcoder;
using uint=unsigned int;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
struct S{
    int sum,len;
    S(int _sum=0,int _len=1){
        sum=_sum;
        len=_len;
    }
};
int n;
S op(S l,S r){return S(l.sum+r.sum,l.len+r.len);}
S e(){return S(0,1);}
S mapping(ll f,S x){return S(x.sum+f*x.len,x.len);}
ll composition(ll l,ll r){return l+r;}
ll id(){return 0;}
int main(){
    //Freopen("filename");
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    vector<S>a(n+1,S());
    for(int i=0;i<n;i++)
        cin>>a[i].sum;
    lazy_segtree<S,op,e,ll,mapping,composition,id>Segtree(a);
    for(int i=0;i<n;i++){
        int x=Segtree.get(i).sum;
        Segtree.apply(i,-min(n-i-1,x));
        if(i!=n-1)//最后一个人不需要给任何人石头
            Segtree.apply(i+1,i+1+min(n-i-1,x),1);//自己写的包括r点，但lazy_segtree不包括r，所以r要+1
    }
    for(int i=0;i<n;i++)
        cout<<Segtree.get(i).sum<<" ";
    Endl;
    Made by Barry;
}
```

---

## 作者：yueyan_WZF (赞：2)

首先看这道题，其实这就是一道差分。

给石头肯定是给靠近自己的，那么不就是把自己后面的一段连续区间加一，此时我们就可以用差分来表示出每个新成年收到的前面给的石头。


```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n;
int a[1000004];
int sum[1000004]; //差分数组
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int SUM=0; //表示前面的成年给的石头
	for(int i=1;i<=n;i++){
		SUM+=sum[i-1]; //差分累加
		a[i]+=SUM; //收到前面的石头
		if(a[i]!=0){
			sum[i]+=1; //后面的可以拿到石头 
			sum[min(n,i+a[i])]--; //在 min(n,i+a[i]) 时石头不够了，就不发了，所以差分数组减去
		} 
		a[i]-=min(n-i,a[i]);  //减去发给后面的石头
		cout<<a[i]<<" "; 
	}
}
```

---

## 作者：_qumingnan_ (赞：1)

[题目跳楼机](https://www.luogu.com.cn/problem/AT_abc388_d)

# 正片开始

## 阅读理解：

有 $n$ 个外星人，第 $i$ 个外星人有 $a_i$ 个石头，他们会按照编号的顺序依次成年（编号最小的最先成年）。当他们成年时，已经成年且石头数量大于 $0$ 的外星人会给这个外星人 $1$ 块石头。

## 思路：

可以发现，第 $i$ 个外星人在获得石头后，他可以给编号在 $i+1\sim\min(n,i+a_i)$ 的范围内的外星人石头，我们就可以使用**优先队列**来储存第 $i$ 个外星人最多可以给到第几个外星人石头，如果队头的编号小于当前编号，那就弹出队头，接着再给 $a_i$ 加上队列长度，也就是他获得的石头，再把 $\min(n,i+a_i)$ 加入队列，最后将 $a_i$ 的值改为 $\max(a_i-(n-i),0)$，然后一直重复这个过程就可以了。

## 代码实现：

由于本蒟蒻不会拼从小到大排序的优先队列的英文，所以只能写默人的从大到小排序的优先队列。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[500005];
priority_queue<int>q;//优先队列 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		while(!q.empty()&&q.top()>n-i)q.pop();//如果 q 是从小到大排，那就应该是 while(!q.empty()&&q.top()<i)q.pop();
		a[i]+=q.size(); 
		int mi=min(n,i+a[i]);
		q.push(n-mi);//如果 q 是从小到大排，那就应该是 q.push(mi);
		a[i]=max(a[i]-(n-i),0);
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
	return 0;
}
```

---

## 作者：Carey2012 (赞：1)

## 传送门
> [传送门](/problem/AT_abc388_d)
## 思路
使用优先队列，记录第 $i$ 个人成年时，前面 $i-1$ 个大人中有几个没石头的大人，最后往里面塞入 $a_i+(i-1)+(i-t)$。\
其中 $a_i+(i-1)+(i-t)$ 是指第 $i$ 个人的至少拥有 $1$ 个石头的时长，\
$(i-1)$ 是指第 $i$ 个人前 $i-1$ 年的石头没有改变，\
$t$ 指的是前 $i-1$ 个人中有几个人的石头数为 $0$，\
$(i-t)$ 是指第 $i$ 个人前 $i-1$ 个人中，有几个至少拥有 $1$ 个石头。
## data & [AC_link](https://atcoder.jp/contests/abc388/submissions/61593496)
```CPP
//#pragma GCC optimize(2)
#include<bits/stdc++.h>
//#define gets(S) fgets(S,sizeof(S),stdin);
//#define a first
//#define c second
using namespace std;
const int MAX=5e5+10,mod=1e9+7;
typedef long long ll;
typedef pair<int,int> pii;
int n;
int a[MAX];
int ans[MAX],t=0;
priority_queue<int,vector<int>,greater<int>> zero;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){scanf("%d",a+i);}
	for(int i=1;i<=n;i++){
		while(!zero.empty() && zero.top()-i<0){zero.pop();t++;}
		ans[i]=max(0,a[i]+((i-1)-(n-i))-t);
		zero.push(a[i]+(i-1)+(i-t));
	}for(int i=1;i<=n;i++){printf("%d ",ans[i]);}
	return 0;
}
```

---

## 作者：_xxxxx_ (赞：1)

不需要用这么长的 DS，优先队列就能解决了。

我们在读题后可以发现，如果我已经成年且没有石子了，那我以后就都不会分石头给其他人。而同时，用完石子的人有先后顺序，我们尝试用优先队列（用小根堆）存下前面所有成年人的石子数量。

然后发现我们不能很方便的处理给石子出来的问题，可以将操作分开，先处理拿到多少石子，在计算送多少石子给后面的人。

给后面的人的石子数量明显是 $n-i$ 个，而拿到的石子数量就是我优先队列的长度。

处理出队，我们知道，一个人会在没有石子的时候停下来，那么在我们的优先队列中时，队头是最小的先出队。对于送了多少石子，我们可以每次让 $a_i+i$ 入队，判断时减去 $i$ 看是否剩余，这样操作可以抵消掉多减去的 $i$，可以整体计算减小时间复杂度。

时间复杂度 $O(n \log n)$，码量还是挺小的。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10;
int n, a[N];
priority_queue<int, vector<int>, greater<int> > q;// 小根堆
signed main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++)
    {
        //这里计算 i 拿到了多少石子
        a[i] += (q.size());
        q.push(a[i] + i);
        while(q.size())
        {
            int u = q.top();
            if(u - i <= 0) q.pop();
            else break; //下一个一定不可能
        }
    }
    for(int i = 1; i <= n; i++) cout << max(0ll, a[i] - (n - i)) << " ";//送给后面的人
    return 0;
}
```

---

## 作者：xyin (赞：1)

Update：补了一下和正解思考方向的差异。

赛时往差分那方面想了想，觉得需要动脑子，又准备写线段树，觉得有点麻烦，最后就写了无脑的平衡树，我用的 fhq 实现。

究其根本，没有用差分、树状数组或线段树的原因是：正解应该是用当前这个点更新后面的，而我想的却是用前面的更新当前这个点，相对来说实现更复杂一点。

每次按权值把平衡树分裂成两部分，一部分 $\le 0$，一部分 $\ge 1$，对于前者我们不进行操作，对于后者打上 tag 标记区间 $-1$ 即可。由于操作后两部分的值域依然无交，可以直接使用无交合并，最后为了统计答案，我们遍历一遍平衡树下放标记即可，总时间复杂度为 $O(n\log n)$ 的。

这里给出代码可以参考一下，对比其它做法真的是又臭又长。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define pb push_back
#define pp pop_back
#define mk make_pair
#define pai pair<int,int>
#define fi first
#define se second
// #define ls rt<<1
// #define rs rt<<1|1
using namespace std;
const int maxn=5e5+5;
const int INF=1e18;
const int base=100411;
const int Mod=1e9+0411;
int read(int x=0,bool f=1,char c=0){
    while (!isdigit(c=getchar())) f=c^45;
    while (isdigit(c))
        x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?x:-x;
}
int n,a[maxn],rt,tot,ans[maxn];
struct Node{
    int ls,rs,pri,val,siz,id,tag;
}tr[maxn];
int New(int k,int id){
    return tr[++tot]=Node{0,0,rand(),k,1,id,0},tot;
}
void push_down(int p){
    if (!tr[p].tag) return void();
    int t=tr[p].tag;tr[p].tag=0;
    if (tr[p].ls) tr[tr[p].ls].val+=t,tr[tr[p].ls].tag+=t;
    if (tr[p].rs) tr[tr[p].rs].val+=t,tr[tr[p].rs].tag+=t;
}
void push_up(int p){
    tr[p].siz=tr[tr[p].ls].siz+tr[tr[p].rs].siz+1;
}
void split(int p,int &x,int &y,int k){
    if (!p) return x=y=0,void();push_down(p);
    if (tr[p].val>k) y=p,split(tr[p].ls,x,tr[p].ls,k);
    else x=p,split(tr[p].rs,tr[p].rs,y,k);push_up(p);
}
int merge(int x,int y){
    if (!x||!y) return x|y;
    push_down(x);push_down(y);
    if (tr[x].pri>tr[y].pri){
        tr[x].rs=merge(tr[x].rs,y);
        return push_up(x),x;
    }
    else{
        tr[y].ls=merge(x,tr[y].ls);
        return push_up(y),y;
    }
}
void insert(int id,int k){
    int x,y;split(rt,x,y,k);
    rt=merge(x,merge(New(k,id),y));
}
void get(int p){
    if (!p) return void();
    push_down(p);
    // cout<<p<<"  "<<tr[p].val<<endl;
    ans[tr[p].id]=tr[p].val;
    get(tr[p].ls);get(tr[p].rs);
}
signed main(){
    n=read();
    for (int i=1;i<=n;i++)
        a[i]=read();
    for (int i=1;i<=n;i++){
        int x,y,t=0;split(rt,x,y,0);
        // cout<<y<<endl;
        if (y) t=tr[y].siz,tr[y].val--,tr[y].tag--;
        rt=merge(x,y);
        // cout<<t<<endl;
        insert(i,a[i]+t);
    }
    get(rt);
    for (int i=1;i<=n;i++)
        printf("%lld ",ans[i]);
    cout<<endl;
}
```

---

## 作者：liluhexuan (赞：1)

~~考试时以为是正解，没想到有比这还优的~~

容易发现每个外星人都是先多次获得别人的石子，在获得石子期间不会送出石子；之后再连续送出石子，且在送出石子期间不会再获得石子。所以我们可以把他转换成这样：每个外星人在成年后会给**从前到后**给后面每一个外星人送一块石头，直到自己的石头用尽或者后面所有的外星人都获得石头（注意每个人在之前获得的石头也要算上）。所以这就是一个区间修改，单点查询的题目，所以可以用树状数组（用线段树也可以，但线段树复杂又慢）。

```cpp
#include<iostream>
using namespace std;
const int N=5e5+10;
int d[N],n,a[N];
int lowbit(int x){ //树状数组模板
	return x&-x;
}
void add(int x,int k){
	while(x<=n){
		d[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x){
	int sum=0;
	while(x){
		sum+=d[x];
		x-=lowbit(x);
	}
	return sum;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		add(i,a[i]),add(i+1,-a[i]); //初始化
	}
	for(int i=1;i<=n;i++){
		int x=query(i); //目前一个外星人获得的石头数
		if(x>=n-i){ //石头足够给后面所有外星人分一个
			add(i,i-n),add(i+1,n-i); //减去分走的
			add(i+1,1); //后面所有外星人增加一个石头
		}
		else{ //石头不够
			add(i,-x),add(i+1,x); //用完所有石头
			add(i+1,1),add(i+x+1,-1); //给能获得石头的外星人分一块
		}	
	}
	for(int i=1;i<=n;i++)
		cout<<query(i)<<' '; //输出
	return 0;
}
```

~~[最后无耻的推广一下](https://www.luogu.com.cn/article/oddsckf8)~~

---

## 作者：Ybll_ (赞：1)

### 闲话：赛时没想出正解，想了个线段树……

# 题意：
$n$ 个人，第 $i$ 个人将会在 $i$ 年后成年，每当有人成年时，手上还有石头的成年人会送一个石头给刚成年的人，问 $n$ 年后，每人个有几个石头。
# 思路：
设 $j$ 为 $tree$ 中 $a_i$ 当前的值，接下来，这个点要给后面 $\min(n,i+j)$ 个人每个人送一个石头，然后给自己减去送出去的石头，可以理解为给 $[i+1,\min(n,i+j)]$ 这个区间每个数 $+1$，给 $[i,i]$ 这个区间每个数减去 $\min(n-i,j)$。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int l,r,lazy,sum;
}tree[2500010];
int n,m,a[500010];
void build(int id,int l,int r)
{
	tree[id].l=l;
	tree[id].r=r;
	if(l==r)
	{
		tree[id].sum=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
	tree[id].sum=tree[id*2].sum+tree[id*2+1].sum;
}
void down(int id)
{
	tree[id*2].lazy+=tree[id].lazy;
	tree[id*2].sum+=(tree[id*2].r-tree[id*2].l+1)*tree[id].lazy;
	tree[id*2+1].lazy+=tree[id].lazy;
	tree[id*2+1].sum+=(tree[id*2+1].r-tree[id*2+1].l+1)*tree[id].lazy;
	tree[id].lazy=0;
}
void update(int id,int l,int r,int v)
{
	if(tree[id].l>r||tree[id].r<l)return;
	if(tree[id].l>=l&&tree[id].r<=r)
	{
		tree[id].lazy+=v;
		tree[id].sum+=(tree[id].r-tree[id].l+1)*v;
		return;
	}
	if(tree[id].lazy>0)down(id);
	update(id*2,l,r,v);
	update(id*2+1,l,r,v);
	tree[id].sum=tree[id*2].sum+tree[id*2+1].sum;
}
int query(int id,int l,int r)
{
	if(tree[id].l>r||tree[id].r<l)return 0;
	if(tree[id].l>=l&&tree[id].r<=r)return tree[id].sum;
	if(tree[id].lazy>0)down(id);
	return query(id*2,l,r)+query(id*2+1,l,r);
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		int j=query(1,i,i);
		update(1,i+1,min(n,i+j),1);
		update(1,i,i,-min(n-i,j));
	}
	for(int i=1;i<=n;i++)
	{
		cout<<query(1,i,i)<<" ";
	}
	return 0;
}
```

---

## 作者：15805856563fqm (赞：1)

考虑差分。

定义一个变量 $p$，表示这个数的状态，查询到它时便累加到 $a_i$，然后给前面未成年一颗石头，然后把后面的要给的一颗石头减掉，最后输出即可。

code:

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[1000002],p,t,h[1000001];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		p+=h[i];
		a[i]+=p;
		int t=min(a[i],n-i);
		a[i]-=t;
		h[i+1]++;
		h[i+1+t]--;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<' ';
	}
}
```

---

## 作者：_IceCream_ (赞：1)

# Content

在某个星球上，有 $N$ 个外星人，他们都是未成年人。

其中 $i$ 个外星人目前拥有 $A_i$ 块石头，并将在 $i$ 年后成为成年人。

当这个星球上有人成年时，每个至少拥有一块宝石的成年人都会向刚刚成年的外星人赠送一块宝石作为贺礼。

求 $N$ 年后每个外星人将拥有多少块石头。

假设未来不会有新的外星人诞生。

# Solution

如果 $A_i$ 足够大，那么我们可以直接模拟 $O(n)$。

但是显然不可能。那么我们假设他足够大，他所收到的宝石个数就是 $i - 1$，需要给予其他人的宝石是 $n - i$ 个。

如果有负数，那么他所给予其他人的宝石个数就需要减少。显然是从第 $n$ 位往前 $-A_i$ 个都需要减 $1$。

这样子问题就变成了区修 + 单查，直接上差分即可。

```cpp
// 假设所有人都可以有全部的收入和支出
for (int i = 1; i <= n; ++i) {
	a[i] += i - 1;
	a[i] -= n - i;
}

for (int i = 1; i <= n; ++i) {
	sum += tot[i]; // i 自己也会被前面的影响
	a[i] += sum;
	if (a[i] < 0) {
		tot[n + a[i] + 1]--; // 差分
		a[i] = 0;
	}
}
```

怎么保证第 $i$ 个不会影响到前面的数？

一开始 $A_i + 2i - n - 1$，显然最小值为 $1 - n$，$i = 1, A_i = 0$ 时取到。

那么 $n + A_i + 1 = 2 \ge 1$，那么最小值都大于 $i$ 了，显然不会有影响到前面的数的可能。

---

## 作者：zzwdsj (赞：1)

### 题目大意

有 $n$ 个外星人，全是未成年。第 $i$ 个外星人在 $i$ 年后成年，有 $a_i$ 块石头。

每个外星人成年后，每个已经成年并且至少有 $1$ 块石头的外星人都会给这个外星人 $1$ 块石头。

求 $n$ 年后每个外星人有多少块石头。

### 思路

直接模拟。设外星人 $i$ 从其他外星人那获得的 $t_i$ 颗石头。

- 给石头：第 $i$ 个外星人会给后面的 $a_i$ 个外星人一块石头，即让 $t_i,t_i+1,...,t_i+a_i$ 增加 $1$。并让自己石头数量变为 $\max(0,a_i-(n-i))$。
- 接受石头：让自己的石头数量增加 $t_i$。

可以发现这是一个区修单差操作，使用线段树或差分维护。

### code

线段树（复杂度 $O(n\log n)$）。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
using namespace std;
#define mid ((l+r)/2)
template<class T,int N>
class tree
{
	T v[N<<4],la[N<<4];
	public:
	void updata(int x,int y,T d,int l=1,int r=N,int rt=1)
	{
		if(y<l||x>r||l>r)return;
		v[rt]+=d*(min(r,y)-max(l,x)+1);
		if(x<=l&&r<=y)return la[rt]+=d,void();
		updata(x,y,d,l,mid,rt*2),updata(x,y,d,mid+1,r,rt*2+1);
	}
	T getans(int x,int y,int l=1,int r=N,int rt=1)
	{
		if(r<x||l>x)return 0;
		if(x<=l&&r<=y)return v[rt];
		return getans(x,y,l,mid,rt*2)+getans(x,y,mid+1,r,rt*2+1)+la[rt]*(min(r,y)-max(l,x)+1);
	}
};
tree<int,500005>t;
int n,a[500005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		a[i]=max(0,a[i]+t.getans(i,i));
		t.updata(i+1,min(500001,i+a[i]),1);
		cout<<max(0,a[i]-n+i)<<" ";
	}
	return 0;
}
```

差分（复杂度 $O(n)$）。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
using namespace std;
int n,a[500005],b[500005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1,sum=0;i<=n;i++)
	{
		sum+=b[i];
		a[i]=a[i]+sum;
		sum++,b[min(n+1,i+a[i])+1]--;
		cout<<max(0,a[i]-n+i)<<" ";
	}
	return 0;
}
```

---

## 作者：long_long__int (赞：0)

赛时乱搞，搞过了……

# 题目解法

第 $i$ 个外星人要送 $n-i$ 颗宝石，如果 $a_i+$ **前面的外星人送给他的宝石** $<n-i$，那么这个外星人送不起从第 $i+a_i+$ 前面的外星人送给他的宝石到结束所有外星人的宝石。用 $c_i$ 来存从 $1\sim i$ 之间送不起第 $i$ 个外星人的外星人数目。

描述的不太好，具体见代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[500500];
int c[500500];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		a[i]-=c[i-1];
		a[i]+=i-1;//接受宝石
		c[i]+=c[i-1];
		if(a[i]<(n-i)){//送不起
			c[i+a[i]]++;
			a[i]=0;
		}else{//送得起，送出去
			a[i]-=(n-i);
		}
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：ljk8886 (赞：0)

## 题目分析
考虑用优先队列。

观察题目发现，第 $i$ 个外星人成年后，要给后面 $n - i$ 个外星人每人一个石头，当然如果他自己没有石头就不用给。所以我们可以建一个小根堆，让石头少编号小的外星人排在前面，因为编号越小说明他要给的石头就越多。

一开始，我们先把第一个外星人入队，因为他不会收到石头要给后面每一个外星人石头，所以他最终的石头个数就是 $\max(a_1 - (n - 1), 0)$。接下来，如果队首的外星人石头没了，就把他出队。此时队里的外星人都要给今年要成年的外星人石头，所以当前外星人会获得队里外星人个数的石头，然后再把当前外星人入队，当前外星人最终的石头个数同理，就是 $\max(a_i - (n - i), 0)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define ft first
#define sd second
#define endl '\n'
#define pb push_back
#define md make_pair
#define gc() getchar()
#define pc(ch) putchar(ch)
#define umap unordered_map
#define pque priority_queue
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 bint;
typedef pair<int, int> pii;
typedef pair<pii, int> pi1;
typedef pair<pii, pii> pi2;
const ll INF = 0x3f3f3f3f;
inline ll read()
{
	ll res = 0, f = 1;
	char ch = gc();
	while (ch < '0' || ch > '9') f = (ch == '-' ? -1 : f), ch = gc();
	while (ch >= '0' && ch <= '9') res = (res << 1) + (res << 3) + (ch ^ 48), ch = gc();
	return res * f;
}
inline void write(ll x)
{
	if (x < 0) x = -x, pc('-');
	if (x > 9) write(x / 10);
	pc(x % 10 + '0');
}
inline void writech(ll x, char ch) { write(x), pc(ch); }
const int N = 5e5 + 5;
ll a[N];
struct node {
	int i;
	bool operator < (const node &cmp) const { return a[i] + i > a[cmp.i] + cmp.i; } // 重载运算符 
};
pque<node> q; // 小根堆 
int main()
{
	int n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	q.push(node{1});
	writech(max(a[1] - (n - 1), 0ll), ' ');
	for (int i = 2; i <= n; i++)
	{
		while (!q.empty() && a[q.top().i] - (i - q.top().i) < 0) q.pop(); // 没有石头的外星人出队 
		a[i] += q.size(); // 加上队里外星人个数 
		q.push(node{i}); // 入队 
		writech(max(a[i] - (n - i), 0ll), ' '); // 答案 
	}
	return 0;
}
```

---

## 作者：rzm120412 (赞：0)

#### 题目大意：

在某个星球上，有 $N$ 名外星人，他们都是未成年人。

其中 $i$ 个外星人目前拥有 $A_i$ 颗宝石，并将在 $i$ 年后成为成年人。

当这个星球上有人成年时，每个至少拥有一块宝石的成年人都会向刚刚成年的外星人赠送一块宝石作为贺礼。

求 $N$ 年后每个外星人将拥有多少块石头。

假设未来不会有新的外星人出生。

#### 分析：

我们发现每名外星人，有接受和赠送两种操作。赠送石头肯定是给靠近自己的，那么就是把自己后面的一段连续区间加一，此时我们就可以用差分来表示出每个刚刚成年的外星人收到的前面的石头。

#### 代码：


```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,a[500005],c[500005];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int sum=0;
	for(int i=1;i<=n;i++) {
		sum+=c[i];
		a[i]=a[i]+sum;
		sum++;
		c[min(n+1,i+a[i])+1]--;
		cout<<max(0,a[i]-n+i)<<" ";//注意！！！ 
	}
	return 0;
}
```

---

## 作者：QAQ2012 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc388_d)

## 思路

先预处理操作每个人在经过 $n$ 年所得到的石子与送走的石子。

但是我们能发现会出现负数，我们发现从**末尾减去这个负数的绝对值加一之后就不能用了**，那只需要将位置存到优先队列里，在下一个人处理的时候判断是否能给就行了。

## 代码


```cpp
#include<bits/stdc++.h>

using namespace std;
int a[500005],n,idx=0;
priority_queue<int> q;
int main(){
	cin>>n;
	for(int i = 1 ; i <= n ; i++){
		cin>>a[i];
	}
	for(int i = 1 ; i <= n ; i++){
		a[i]+=i-1;
		while(!q.empty()&&-q.top()==i){//如果当前这个都不能用了，后面的就更不能用了
			idx++;
			q.pop();
		}
		a[i]-=idx;
		a[i]-=(n-i);
		if(a[i]<0){
			q.push(-(n+a[i]+1));//负数存储就不用写小根堆了
		}
	}
	for(int i = 1 ; i <= n ; i++){
		if(a[i]<0){
			cout<<0<<" "; 
		}
		else{
			cout<<a[i]<<" ";
		}
		
	}
	return 0;
}


```

---

## 作者：Tiger_Rory (赞：0)

主要算法：树状数组。

主要思路：依题意得，每个外星人最后的宝石数是前面的送他的（即额外获得的宝石），加上他自己的，再减去他要送给后面外星人的，那么加上额外获得宝石这一过程为单点查询，送宝石这一过程为区间修改，用树状数组实现即可。

代码实现如下。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,a[500005],tree[500005]; 
int lowbit(int x) {
    return x&(-x); 
}
void upd(int x, int y) {
    while(x<=n)tree[x]+=y,x+=lowbit(x);
} //区间修改
int query(int x) {
    int ans=0; 
    while(x>0)ans+=tree[x],x-=lowbit(x); 
    return ans; 
} //查询
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>n; for(int i=1;i<=n;i++) {
        cin>>a[i];  
    }
    for(int j=1;j<=n;j++) {
        if(j==1&&a[j]!=0) {
            upd(j+1,1); 
            upd(min(n,j+a[j])+1,-1); 
            a[j]-=min(n-j,a[j]); 
        }
        else {
            a[j]=a[j]+query(j); 
            if(a[j]!=0) {
                upd(j+1,1); 
                upd(min(n,j+a[j])+1,-1); 
                a[j]-=min(n-j,a[j]); 
            }
        }
        cout<<a[j]<<' '; 
    }cout<<'\n'; 
	return 0;
}
```

---

## 作者：opzc35 (赞：0)

[=>题目传送门<=](https://www.luogu.com.cn/problem/AT_abc388_d)
## 题目大意

有 $N$ 个外星人，每个外星人最开始有 $A_i$ 个石头。

第 $i$ 个外星人会在 $i$ 年后成年。每一年，有石头的外星人都会给成年的外星人一颗石头。

请你求出第 $i$ 个外星人 $N$ 年之后的石头剩余数量。

## 题目分析

我们可以按时间线枚举年份。考虑到每个外星人只会成年一次，所以每个外星人到了第 $i$ 年后就不会在获得更多的石头了。

我们考虑使用某种高级数据结构对于后面的所有外星人进行 区间修改 操作，把能够给与石头的外星人都把石头更新了。

鉴于树状数组查询和修改复杂度均为 $O(\log n)$，并且常数小。所以我们考虑使用树状数组。

## 代码

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
#define int long long
using namespace std;
int n,a[500005],t[500005];
void update(int x,int k){
	for(;x<=n;x+=lowbit(x))t[x]+=k;
}
int query(int x){
	int ans=0;
	for(;x;x-=lowbit(x))ans+=t[x];
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		update(i,a[i]-a[i-1]);
	}
	for(int i=1;i<=n;i++){
		int x=i+1;
		int y=min(n,i+query(i));
		if(x>y){
			cout<<query(i)<<endl;
			continue;
		}
		update(x,1);
		update(y+1,-1);
		update(i,-(y-x+1));
		update(i+1,y-x+1);
		cout<<query(i)<<" ";
	}
	return 0;
}
```
## 提示

某些外星人可能没有足够的经济实力，给不了其他外星人石头，需要特殊判断。

---

## 作者：player_1_Z (赞：0)

### 先来理解题目
[atcoder 原题](https://atcoder.jp/contests/abc388/tasks/abc388_d)

### 思路
首先这题暴力会超时。于是我们想到一个 $O (n)$ 的方法。首先明白第 $i$ 个外星人在成年后会给 $(i+1) \sim (\min(a[i],n))$ 所以可以建一个差分数组 $q$（[差分](https://blog.csdn.net/qq_63055790/article/details/135585037)），让 $q_i$ 存 $i$ 在成年后获得的金币数。接着用 $i$ 遍历 $1 \sim n$，对于每个 $i$ 先让 $a_i$ 加上 $q_i$，然后让 $a_i$ 把石子分到后面去，并输出剩余石子。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500005],q[500005],s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		q[i]+=q[i-1];//石子传过来 
		a[i]+=q[i];//拿石子 
		if(a[i]>=n-i) q[i+1]+=1,q[n+1]-=1,a[i]-=n-i;//石子够多,差分,a[i]为剩余 
		else if(a[i]>0) q[i+1]+=1,q[i+a[i]+1]-=1,a[i]=0;//石子不够,差分,a[i]全分了 
		cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个长度为 $N$ 的序列 $A$，现经历 $N$ 秒，第 $i$ 秒 $A_i$ 会加上 $A_1,A_2,\cdots,A_{i-1}$ 中在这一秒非零的个数，并在之后每一秒 $A_i$ 都会减一直到 $A_i=0$，问经历完 $N$ 秒后的序列，数据范围 $N\le 5\times 10^5$。

## 解题思路

考虑对于每个 $A_i$ 一步步进行操作。首先，若 $A_1,A_2,\cdots,A_{i-1}$ 在这一秒为零的个数为 $X$，那么 $A_i\leftarrow A_i+i-X-1$。接着考虑之后每一秒减一，易得在 $A_i+i+1$ 这一秒及之后 $A_i$ 会变为 $0$，同时需满足 $A_i+i+1>0$ 且 $A_i+i+1\le N$，于是便可用树状数组维护 $X$。最后经历了 $N$ 秒后，$A_i\leftarrow\max(A_i-N+i,0)$，更新 $A_i$ 即可，时间复杂度 $O(N\log N)$。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
#define lowbit(x) x&-x
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,x,t[500001];
void add(ll x, ll y) {while(x<=n) t[x]+=y, x+=lowbit(x);}
ll find(ll x) {ll res=0; while(x>0) res+=t[x], x-=lowbit(x); return res;}

int main()
{
    n=read();

    for(R int i=1; i<=n; ++i)
    {
        x=read()+i-find(i)-1;
        if(x+i>-1 && x+i<n) add(x+i+1,1);
        x=max(x-n+i,0ll); write(x); spc;
    }

    return 0;
}
```

---

## 作者：_anll_ (赞：0)

## 思路
差分数组即可。

我们维护一个 $tot$ 表示当前要加多少数，每次先拿 $dif_i$ 更新 $tot$，再拿 $tot$ 更新当前数。

具体地，我们考虑当前 $a_i$ 要为后面的数贡献 $an$ 为多少。显然为 $\min(n-i,num_i)$。直接将当前 $num_i$ 减去 $an$ 输出即可。对于差分数组，$dif_{i+1}$ 处 $+1$，若 $i+an+1\le n$，则在 $dif_{i+an+1}$ 处 $-1$。时间复杂度 $O(n)$。

## 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e6+5;
int n,k,num[N],dif[N];
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;int x=0;
	for(int i=1;i<=n;i++) cin>>num[i];
	for(int i=1;i<=n;i++){
		x+=dif[i];
		num[i]+=x;dif[i+1]+=1;
		if(n-i>num[i]){
			dif[i+num[i]+1]-=1;
			cout<<"0 ";
		}
		else cout<<num[i]-(n-i)<<" ";
	}
	return 0;
}
```

---

## 作者：sjh0626 (赞：0)

## 题意概括
有 $N$ 个外星人，一开始他们有 $a_i$ 个石头，第 $i$ 个外星人经过 $i$ 年后成年，同时得到其他已经成年的外星人每人一个石头，且每个人最少有 $0$ 个石头。

求 $N$ 年后每个外星人的石头数量。
## 思路分析
因为我们注意到这就是区间修改、单点修改和单点查询的板子，我们可以用线段树来处理。

AtCoder 有一个万能库，所以我们可以使用万能库。

使用教程详见[此](https://www.luogu.com.cn/article/xxa80t4t)。
## 代码解析
```cpp
#include<bits/stdc++.h>
#include<atcoder/lazysegtree>
#define sjh0626s return
#define code 0
#define ll long long
using namespace std;
namespace FastIO{
	#ifdef ONLINE_JUDGE
		const int maxn=1<<20;
		char _in[1<<20],_out[1<<20],*_p1=_in,*_p2=_in,*_p3=_out;
		#define getchar() (_p1==_p2&&(_p2=(_p1=_in)+fread(_in,1,maxn,stdin),_p1==_p2)?EOF:*_p1++)
		#define flush() (fwrite(_out,1,_p3-_out,stdout))
		#define putchar(x) (_p3==_out+maxn&&(flush(),_p3=_out),*_p3++=(x))
		class Flush{public:~Flush(){flush();}}_;
	#endif
	class FastInput{
		public:
			template<typename T>
			inline T read(){
				T x=0,f=1;char ch=getchar();
				while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
				while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
				return x*f;
			}
			inline char read(char &x){do{x=getchar();}while(isspace(x));return x;}
			inline void read(char *x){static char ch;read(ch);do{*(x++)=ch;}while(!isspace(ch=getchar())&&~ch);}
			inline void read(string &x){static char ch;read(ch),x.clear();do{x+=ch;}while(!isspace(ch=getchar())&&~ch);}
			template<typename T>FastInput &operator>>(T &x){x=read<T>();return *this;}
	};
	class FastOut {
		public:
			template<typename T>
			inline void write(T x){
				if(x<0){putchar('-'),write<T>(0-x);return;}
				static T sta[300];
				int top=0;
				do{sta[top++]=x%10,x/=10;}while(x);
				while(top)putchar(sta[--top]+48);
			}
			inline char write(const char &x){return putchar(x);}
			template<typename T>inline void write(T *x){while(*x)putchar(*(x++));}
			inline void write(const string &x){for(int i=0,len=x.length();i<len;++i)putchar(x[i]);}
			template<typename T>FastOut &operator<<(T x){write(x);return *this;}
	};
}
FastIO::FastInput qin;
FastIO::FastOut qout;
ll n;
struct tag{
	ll sum;
	int len;
	tag(ll x=0,int y=1){sum=x,len=y;}
};
vector<tag>a(600010,tag());
tag mapping(ll f,tag s) {return tag(s.sum+f*s.len,s.len);}
tag mergetag(tag x,tag y) {return tag(x.sum+y.sum,x.len+y.len);}
tag nom(){return tag(0,1);}ll p(){return 0;}
ll mergef(ll x,ll y){return x+y;}
int main(){
	qin>>n;
	for(int i=0;i<n;i++){
		qin>>a[i].sum;
	} 
	atcoder::lazy_segtree<tag,mergetag,nom,ll,mapping,mergef,p>segtree(a);
	for(int i=0;i<n;i++){
		ll v=segtree.get(i).sum;
		segtree.apply(i,-min(n-1-i,v));
		if(i==n-1)continue;
		segtree.apply(i+1,i+1+min(n-i-1,v),1);
	}
	for(int i=0;i<n;i++){
		qout<<segtree.get(i).sum<<" ";
	}
	sjh0626s code;
}
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
$i$ 这个人会往后从 $i+1$ 连续发宝石，直到到没有宝石或者发到 $n$ 为止，是一个区间加单点查问题。但是查询是按顺序查，区间加也不会影响 $i$ 前面的数，所以可用差分代替树状数组。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+10;
int n,x,a[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>x;
		a[i]+=a[i-1],a[i]+=x,a[i+1]-=x,++a[i+1];
		if(a[i]<n-i) --a[i+a[i]+1],cout<<"0 ";
		else cout<<a[i]-n+i<<' ';
	}
    return 0;
}
```

---

## 作者：DoubleQLzn (赞：0)

我们可以用差分来维护过程。如果说 $a_i$ 可以给后面所有人发完，那么 $a_i$ 减去后面人的个数，同时给 $a_{l+1}$ 到 $a_N$ 加 $1$；否则如果 $a_i$ 不为 $0$，给 $a_{l+1}$ 到 $a_{l+a_i}$ 改为 $0$。由于区间操作不影响之前的元素，可以用差分维护。

### Code 

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[500005],f[500005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i];
	int last = 1,s = 0;
	for (int i = 1;i <= n;i++)
	{
		if (!f[i])
		{
			int k = lower_bound(a + last,a + n + 1,a[i] * 2) - a;
			if (k >= last && k > i && k <= n)
			{
				f[k]++;
				s++;
				last++;
			}
			else break;
		}
	}
	cout << s;
	return 0;
}
```

---

## 作者：jinhangdong (赞：0)

第 $i$ 个人成年后一共需要给 $n-i$ 个石头，当然如果不够越后面成年的就分不到石头。

我们用线段树维护。

到这个人成年后，以后还要分 $n-i$ 个石头，如果不够那就变成 $0$，然后分了几个石头，就然后面若干个人的石头加 $1$。
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e6+5;
int n,a[N];
int tree[N],tag[N];
void lazy(int l,int r,int now,int k)
{
	tree[now]+=k*(r-l+1);
	tag[now]+=k;
}
void push_up(int now)
{
	tree[now]=tree[now*2]+tree[now*2+1];
}
void push_down(int l,int r,int now)
{
	int mid=(l+r)/2;
	lazy(l,mid,now*2,tag[now]);
	lazy(mid+1,r,now*2+1,tag[now]);
	tag[now]=0;
}
void build(int l,int r,int now)
{
	if(l==r)
	{
		tree[now]=a[l];
		return; 
	}
	int mid=(l+r)/2;
	build(l,mid,now*2);
	build(mid+1,r,now*2+1);
	push_up(now);
}
void update(int l,int r,int nl,int nr,int now,int k)
{
	if(nl<=l&&r<=nr)
	{
		tree[now]+=(r-l+1)*k;
		tag[now]+=k;
		return;
	}
	push_down(l,r,now);
	int mid=(l+r)/2;
	if(mid>=nl) update(l,mid,nl,nr,now*2,k);
	if(mid<nr) update(mid+1,r,nl,nr,now*2+1,k);
	push_up(now);
}
int query(int l,int r,int nl,int nr,int now)
{
	int ans=0;
	if(nl<=l&&r<=nr) return tree[now];
	push_down(l,r,now);
	int mid=(l+r)/2;
	if(mid>=nl) ans+=query(l,mid,nl,nr,now*2);
	if(mid<nr) ans+=query(mid+1,r,nl,nr,now*2+1);
	return ans;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	build(1,n,1);
	for(int i=1;i<=n;++i)
	{
		int t=min(query(1,n,i,i,1),n-i);//计算这个人以后要分几块石头。
		update(1,n,i,i,1,-t);//既然分了自己就要减少
		if(i+1<=n) update(1,n,i+1,i+t,1,1);//然后往后分
		printf("%lld ",query(1,n,i,i,1));//分完就可以计算出答案了
	}
	return 0;
}
```

---

