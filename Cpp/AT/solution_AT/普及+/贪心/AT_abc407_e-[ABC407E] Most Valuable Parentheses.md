# [ABC407E] Most Valuable Parentheses

## 题目描述

给你一个长度为 $2N$ 的数列 $A$。

定义一个长度为 $2N$ 的括号序列 $s$ 的得分：

- 对于所有 $s_i=$`)`，$A_i\leftarrow 0$；
- 得分为上述操作后 $A$ 中所有元素之和。

请求出对于一个长为 $2N$ 的合法的括号序列 $s$，它的得分的最大值。一个括号序列是合法的当且仅当它可以通过多次删去子段 `()` 变为空串。

## 说明/提示

**样例解释 1**

在第一组数据中，$s=$`(())()` 的得分为 $400+500+0+0+300+0=1200$。可以证明这是可能获得的最大的分，故答案为 $1200$。

如第二组数据所示，答案可能超出 32 位整数的表示范围。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
2
3
400
500
200
100
300
600
6
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000
1000000000```

### 输出

```
1200
6000000000```

# 题解

## 作者：huhexuan (赞：2)

很容易想歪的题。

最初一眼 dp，状态是很经典的前 $i$ 个，填 $j$ 个左括号，但你很快就会发现这东西没办法压缩，复杂度无法接受。

~~然后就这么被卡到了比赛结束。~~

赛后看题解，感觉自己是个【数据删除】。

我们考虑括号序列的本质。

只要一个序列，满足对于其任意的前缀，都最多有前缀长度除以二个右括号，且对于其本身，有长度的一半的右括号，当然是下取整。

形式化，就是对于任意的 $[1,i]$ 都有右括号数量 $sum$ 满足 $sum \le i \div 2$，且右括号总数量为 $n$。

那么，当右括号的数量很多时，对我们的答案当然是不优的，所以，当右括号超过了我们刚才的范围的话，考虑删去最大的右括号给左括号，大根堆可以维护。

详见代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,a[1000005],ans,n;
priority_queue<int>q;
signed main() 
{
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n;
		for(int i=1;i<=n*2;i++) cin>>a[i],ans+=a[i];
		for(int i=1;i<=n*2;i++)
		{
			q.push(a[i]);
			if(q.size()>i/2) q.pop();
		}
		while(!q.empty()) ans-=q.top(),q.pop();
		cout<<ans<<"\n";
	}
	return 0;
}

---

## 作者：Jenny_yu (赞：2)

对于一个长度为 $len$ 的合法括号序列 $s$，一定有左括弧数等于右括弧数，且对于任何一个满足 $1 \le i \le len$ 的 $i$，前 $i$ 个括弧中左括弧数量一定大于右括弧数。反过来，如果满足这些条件，那么这个括号序列一定合法。

一开始假设所有位置都是右括弧，从 $1$ 到 $2n$ 遍历每一个位置，如果发现从头到位置 $i$ 的右括弧数大于左括弧数，就贪心地找从 $1$ 到 $i$ 中 $a$ 数组对应值最大的那个位置，右括弧变左括弧，当然前提是那个位置是还未变为右括弧的。可以每遍历到一个位置，就把那个位置在 $a$ 数组对应值丢进优先队列。需要的时候取队列头即可。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[400010];
priority_queue<int> q;
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		while(!q.empty())q.pop();
		int n;
		scanf("%lld",&n);
		for(int i = 1; i <= n * 2; i++)scanf("%lld",&a[i]);
		int x = 0,y = 0,ans = 0;
		for(int i = 1; i <= n * 2; i++){
			q.push(a[i]),y++;
			if(y > x)y--,x++,ans += q.top(),q.pop();
		}
		while(x < n)x++,ans += q.top(),q.pop();
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：wenguangxi1 (赞：2)

## 思路
这道题的关键在于这个括号序列在什么情况下列是正确的，可以发现这个序列的每个前缀中的左括号数量都是要大于等于右括号数量的，既然要大于等于那么第一个肯定是左括号，如果想让这个序列继续满足条件那么之后每两个括号就要选一个左括号，此时就会发现每次只能选那些东西，而 $i$ 选小的 $j$ 选大的和 $i$ 选大的 $j$ 选小的是相同的，此时就可以用贪心的做法，每过一个位置就把那个位置的值加入，在选择时就只要选择一个没被选择的最大值即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define endl '\n'
using namespace std;
int n,a[1000001],sg;
void solve(){
	priority_queue<int>pq;
	sg=0;
	cin>>n;
	for(int i=1;i<=n*2;i++)cin>>a[i];
	for(int i=1;i<=n*2;i+=2){
		if(i==1)pq.push(a[i]);
		else{
			pq.push(a[i]);
			pq.push(a[i-1]);
		}
		sg+=pq.top();
		pq.pop();
	}
	cout<<sg<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Your_Name (赞：2)

## 题解
考虑贪心。

发现我们的答案即为 $\sum A$ 减去右括号的 $A_i$ 之和。

前面那个是定值，我们考虑最小化后者。

显然在第 $[1,i]$ 位中最多放 $\lfloor \frac{i}{2}\rfloor$ 个右括号。且如果 $\forall i$ 都满足这个条件且放了 $n$  个右括号，那么一定是一个合法的括号串。

那么我们先假设前面已经放好了，当前要加一个 $i$ 当右括号，并且超出了最多右括号的范围。

那么显然要取 $A_i$ 最大的改成左括号。这样就可以让我们的右括号之和尽可能小。并且因为是减少了前面的括号所以不会让前面超过右括号的数量限制。

又因为我们每次只有超过了限制才改成左括号，所以最后一定会选出 $n$ 个做右括号。

上述反悔过程显然可以直接使用大根堆完成。

完成这个过程之后还在堆中的即为右括号的位置。

代码如下。
## AC_Code
注意开两边空间。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 10;
int T, a[N], ans, n;
priority_queue<int> q;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while(T --){
        cin >> n;
        ans = 0;
        for(int i = 1; i <= n + n; i ++){
            cin >> a[i];
            ans += a[i];
        }
        for(int i = 1; i <= n + n; i ++){
            q.push(a[i]);
            if(q.size() > i / 2)q.pop();
        }
        while(!q.empty()){
            ans -= q.top();
            q.pop();
        }
        cout << ans << '\n';
    }
    return 0;
}
```
_完结撒花。_

---

## 作者：zhoujunchen (赞：1)

贪心题，我们先假设是这样选数的，`()()()()()...`，那么答案就是奇数位的和，删除的是偶数位。

从前往后处理数列时，每遇到一个奇数位 $i$，就可以找一下在位置 $i$ 之前**被删除的数**中是否有比 $a_i$ 还大的数。 

- 如果没有就将 $a_i$ 计入答案。 
 
- 如果有，就记最大被删数字位置为 $j$，将 $a_j$ 记录答案，$a_i$ 删除，括号序列就会发生交换，$j$ 显然是右括号，$i$ 是左括号，交换不破坏括号匹配。

求最大显然使用优先队列。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		int ans=0;
		priority_queue<int> q;//存被删的数字 
		for(int i=1,x;i<=n*2;i++){
			cin>>x;
			if(i%2){
				if(q.size()&&q.top()>x)ans+=q.top(),q.pop(),q.push(x);//删 a[i] 留 a[j] 
				else ans+=x;//计入答案
			}else q.push(x);//删除这个数
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：lyx128 (赞：1)

本题目考虑使用贪心。

我们希望选择 $N$ 个位置作为右括号，使得它们的 $A[i]$ 总和最小。同时，这些位置必须满足正确括号序列的结构要求。

正确括号序列的结构要求：
- 每个右括号 `)` 必须有其对应的左括号 `(` 在其左侧。
- 任意前缀中，右括号的数量不能超过左括号的数量。

为了满足这两个条件，我们可以采用**贪心+优先队列**的策略：

1. 维护一个最大堆：用于保存当前所有可能作为左括号的 $A[i]$ 值。
2. 每次循环处理两个新元素（除了第一次只处理一个）：将它们加入堆中。
3. 弹出堆顶的最大值：将其作为左括号保留，其余的作为右括号。

这种方法确保了：
- 每次循环保留一个左括号，最终保留 $N$ 个左括号。
- 所有未被保留的元素自动成为右括号。
- 通过分组处理和堆维护，确保了括号结构的合法性。

代码实现如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=4e5;
int T;
int n;
int a[N+5];
ll res;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=(n<<1);i++)
			cin>>a[i];
		priority_queue<ll> q;
		res=a[1];
		for(int i=2;i<(n<<1);i+=2){
			q.push(a[i]);
			q.push(a[i+1]);
			res+=q.top();
			q.pop();
		}
		cout<<res<<"\n";
	}
	return 0;
}
```

---

## 作者：dongzirui0817 (赞：1)

## 大意

有一个长度为 $2N$ 的数组 $a$。对于一个长为 $2N$ 的括号序列 $s$，长度为 $2N$ 的 $c$ 数组会用以下方式赋值。

- 对于每一个 $1 \le i \le 2N$ 的 $i$，如果 $s_i$ 是左括号，$c_i \gets 1$，否则 $c_i \gets 0$。

现在，你要构造 $s$，使 $\sum_{i=1}^{2N} c_i \times a_i$ 最大，输出这个最大值。

多测。

- $1 \le \sum n \le 2 \times 10^5$
- $0 \le a_i \le 10^9$

## 思路

设括号序列为 $s$。

显然，左括号有 $N$ 个。那么第 $i$ 个左括号在 $s$ 中所对应的下标最大为 $2i + 1$。这种情况是 $N$ 个 `()` 拼在一起的括号序列。

所以要想收益最大，只需将第 $i$ 个左括号移到 $1$ 至 $2i + 1$ 中 $a_j$ 最大的 $j$ 即可。

但两个左括号不能在同一个下标，所以用 multiset 来维护，选完一个左括号就删掉。

注意到编号大的左括号在 $s$ 里的下标可能会更小，但顺序无所谓，只要选的最大即可。

## 实现

代码不长，但细节多：

- 序列长 $2N$，而 $1 \le N \le 2 \times 10^5$，所以要开到 $4 \times 10^5$。
- 注意测完一组要清空 multiset。
- 注意会爆 int。虽然样例讲了，但不代表没人会忘。
- multiset 删一个数就全删了，所以要给它迭代器。

~~虽然列了这么多，但不代表这些坑着我全踩过。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int T, n;
ll a[400010];
multiset <ll> s;

int main() {
	cin >> T;
	for ( ; T-- ; ) {
		ll ans = 0;
		s.clear();
		scanf("%d", &n);
		for (int i = 1 ; i <= 2 * n ; i++)
			scanf("%lld", &a[i]);
		for (int i = 1 ; i <= 2 * n ; i++) {
			s.insert(a[i]);
			if (i & 1)
				ans += *s.rbegin(), s.erase(s.find(*s.rbegin()));
			// s.erase(s.rbegin()) 会 CE
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc407_e [ABC407E] 最大价值括号 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc407_e)

### 题目大意

一个长度为 $2N$ 的非负整数序列 $A = (A_1,\dots,A_{2N})$。

长度为 $2N$ 的括号序列 $s$ 的得分定义如下：

- 对于 $s$ 的 $i$ 个字符为 `)` 的每个位置 $i$，设置 $A_i$ 为 $0$，然后取 $A$ 中所有元素的和。

求长度为 $2N$ 的正确括号序列的最大可能得分。

给你 $T$ 个测试用例，逐个求解。

正确的括号序列可以通过重复删除等于 `()` 的子串来还原为空字符串的字符串。

### 思路及实现

在正确的括号序列的各种等价定义中，最直观的定义之一是：

- 对于 $1 \leq i \leq 2N$，在 $S_1, \dots, S_{i}$ 中，至少有 $\frac{i}{2}$ 个字符是 `(`。

- 在 $S_1, \dots, S_{2N}$ 中，正好有 $N$ 个字符是 `(`。

以 $\frac{i}{2}$ 为变量，我们可以进一步这样表述：

- 在所有 $1 \leq k \leq N$ 中，$S_1, \dots, S_{2k-1}$ 中至少有 $k$ 个字符是 `(`。

- 在 $S_1, \dots, S_{2N}$ 中，正好有 $N$ 个字符是 `(`。

根据这一定义，我们可以采用以下步骤来构建括号序列：

1. 确定 $S_1 =$ `(`。将这一步视为 $k=1$。

2. 对 $2 \leq k \leq N$ 进行升序排列：

    - 在候选元素集合中添加 ${2k-2}$，${2k-1}$。

    - 从候选集合中选择一个元素 $x$ 并删除它。确定 $S_x = $ `(`。

3. 将未确定的 $N$ 字符设为 `(`。

这个过程确实产生了一个正确的括号序列，而且任何正确的括号序列都可以用这个过程来构造。

可以证明按流程生成的括号序列等于正确的括号序列。

在此，我们可以证明 $S$ 的最终得分可以通过从候选集合中选择元素 $x$ 时，选取最大化 $A_x$ 的元素来最大化。

贪心算法是有效的，因为：

假设当 $k = t$，而 $A_x$ 是最大元素时，我们选择 $A_y < A_x$。

- 如果 $A_x$ 没有选择任何 $k > t$：通过选择 $A_x$ 而不是 $A_y$，并为其他 $k$ 选择相同的元素，程序仍然有效，但 $S$ 的得分增加了。
- 如果在 $k = t' > t$ 中选择 $A_x$：在 $k = t$ 中选择 $A_x$，在 $k = t'$ 中选择 $A_y$，而在其他 $k$ 中选择相同的元素，那么程序仍然有效，但是 $S$ 的得分增加了。

无论如何，都有更好的选择来提高 $S$ 的最终得分。因此，选择 $A_y < A_x$ 替换 $k = t$ 并不是最优的，选择 $A_x$ 才是最优的。

使用优先队列 `priority_queue` 可以简化实现过程。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T, N, X;
vector<ll> A;
ll solve()
{
	ll ans = 0;
	priority_queue<ll, vector<ll> > que;
	for (int i = 0; i <= N - 1; i++)
    {
		if (i == 0)
        {
			que.push(A[i * 2 - 0]);
		}
        else
        {
			que.push(A[i * 2 - 1]);
			que.push(A[i * 2 - 0]);
		}
		ll v = que.top();
		que.pop();
		ans += v;
	}
	return ans;
}
int main()
{
	scanf("%lld", &T);
	while (T--)
    {
        scanf("%lld", &N);
        A.clear();
		for (int i = 1; i <= 2 * N; i++)
            {
                scanf("%lld", &X);
                A.push_back(X);
            }
        printf("%lld\n", solve());
	}
	return 0;
}
```

---

## 作者：I_Love_DS (赞：0)

这种就是你见过就可以切，没见过基本只能坐牢的题。

## 思路

首先，设平衡括号串 $s$ 的长度为 $2n$，那么括号串的性质有：
- $s_1$ 为 `(`，$s_{2n}$ 为 `)`。
- 下标 $1\sim i$ 有至多 $\lfloor\frac i 2\rfloor$ 个 `)`。

也就是第一个必须选，最后一个必须不选。考虑反悔贪心，设当前可以填左括号的下标集合为 $T$。那么读入第一个后，每读入两个，就把这两个下标加入 $T$。

然后每次做决定时，把 $T$ 中权值最大的选掉就可以了，因为根据平衡括号串的性质，这样总能生成一个合法串，而且权值最大。

细节：
1. 开 `long long`。
2. 多测，最后一个即使不选也要读入掉。

## 代码

https://atcoder.jp/contests/abc407/submissions/66153225

---

## 作者：2012_Zhang_ (赞：0)

太板了！太板了！太板了！……~~（此处省略一万个太板了）~~  
这么板的 E 题，居然放在了写完 F 题后写 QWQ。
## 思路解析
首先，想必各位神犇都了解过反悔贪心吧，这题是典型的反悔贪心。  
我们先按最简单的排列方式来，一个左括号和一个右括号交替放置。  
但是在交替过程中，有些左括号却覆盖变成了极小的数，这是我们不愿看到的。  
所以其实完全可以将在他之前最大且比他大的右括号与他交换，这样左括号覆盖的数就尽量的变大了。  
如何实现呢？需要动态存储集合里最大的数。  
这时，大根堆就显现出作用了，将右括号覆盖的数放入大根堆。  
当放置左括号时，如果数比大根堆里最大的数小，就互换。  
最后统计答案时，将总数减去大根堆内所有数即可。  
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e6;
int t,n,a[maxn],cnt,ans;
priority_queue<int>q;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		cnt=0;
		for(int i=1;i<=2*n;i++){
			cin>>a[i];
			ans+=a[i];
			if(cnt) cnt--,q.push(a[i]);
			else if(!q.empty()){
				if(q.top()>a[i]) q.pop(),q.push(a[i]),cnt++;
				else cnt++;
			}
			else cnt++;
		}
		while(!q.empty()) ans-=q.top(),q.pop();
		cout<<ans<<endl;
		ans=0;
	}
	
}

---

## 作者：fanjiayu666 (赞：0)

### 前言

这道题非常水，建议评~~红~~黄（评红怕被揍）。

你不要问我为什么赛时没过。~~因为我没看~~

### 思路

首先我们发现，这玩意可以暴搜啊，然后我们看数据范围肯定过不。

接下来，我们通过瞪眼法，发现总共就只取 $N$ 次，只要是在奇数位上（下标从 $1$ 开始），总是可以取到目前最优的。

- 为什么可以呢？

  我们分情况讨论：
  
  1. 目前最大的数在奇数位上：这种情况始终满足因为不管怎么放，`(` 总是可以在奇数位上（原因不说了，应该没人不会知道吧）。
  2. 目前最大的再偶数位上：有人就会说：“要取到偶数位上的一定要出现 `(())` 的情况，长度小于 $4$ 不炸了。”但是啊小于 $4$ 的偶数只有 $2$ 啊，长度为 $2$ 的合法括号序列只有 `()` 啊！根本轮不到取偶数位的就结束了。有人就又会说：“肯定有反例，只不过长度很长！”但是呢又打脸了，不存在反例，因为要不然就是可以取到，要不然就根本取不了，要不然就是最大的已经过了，所以不存在反例。

所以，经过一通分析后就会发现：这太简单了吧，用 `priority_queue` 维护，写一个在线算法就过了啊。

代码就给一点吧：（怕有人还没听懂）

```cpp
void solve(){
    int n;
    cin>>n;
    vector<int> a(n*2);
    priority_queue<int> q;
    int cnt=0,ans=0;
    for(auto &x:a){//auto 遍历数组
        cin>>x;
        q.push(x);
        if(cnt%2==0){//如果是奇数位的就取，我的下标从 0 开始，下边从 1 开始的要注意。
            ans+=q.top();
            q.pop();//记得一个数只能取一次
        }
    }
    cout<<ans<<"\n";
}
```

### 总结

本题很简单，主要考察瞪眼能力，练手好题。

---

## 作者：zhangbo1000 (赞：0)

一个很经典的结论是，一个序列是合法的括号序列当且仅当：

> 对于它的任何一个前缀，左括号数量不少于右括号，对于它本身，左括号等于右括号。

针对这一转化，不难想出一种括号序列的构造方法：

> 1. 第一个字符肯定是左括号，最后一个肯定是右括号。
> 2. 对于每个长度为 $2i-1$ 的前缀，应当有至少有 $i$ 个左括号，所以我们可以考虑在 $2i-3$ 的构造方案的基础上添一个左括号。
> 3. 把没填的位置填上右括号。

于是本题解法就出来了：$A_1$ 一定贡献答案，$A_{2N}$ 一定不贡献答案，剩余的在上述过程中贪心选择，这一过程可以用优先队列优化为 $O(N\log N)$。

[代码和评测记录。](https://atcoder.jp/contests/abc407/submissions/66148027)

---

