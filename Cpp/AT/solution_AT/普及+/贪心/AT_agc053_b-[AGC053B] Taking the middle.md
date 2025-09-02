# [AGC053B] Taking the middle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc053/tasks/agc053_b

$ 2N $ 枚のカードがあり、それぞれには $ 1 $ から $ 2N $ までの番号が付いています。カード $ i $ の価値は $ V_i $ です。 高橋君と青木君は以下の手順を $ N $ 回繰り返し、カードを $ N $ 枚ずつに分配します。

- まず、高橋君がまだ選ばれてないカードの中から $ 1 $ 枚選び、自分のものとする。 その後、青木君はまだ選ばれてないカードのうち **番号** が中央値であるものを選び、自分のものとする。

高橋君が最終的に持っているカードの価値の総和として考えられる最大の値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 0\leq\ V_i\leq\ 10^9 $
- $ V_i $ は整数

### Sample Explanation 1

以下のような手順で、高橋君はカード $ 4,5,6 $ を手にすることができます。 - まず、高橋君はカード $ 6 $ を選ぶ。そして、青木君はカード $ 3 $ を選ぶ。 - 次に、高橋君はカード $ 5 $ を選ぶ。そして、青木君はカード $ 2 $ を選ぶ。 - 最後に、高橋君はカード $ 4 $ を選ぶ。そして、青木君はカード $ 1 $ を選ぶ。

## 样例 #1

### 输入

```
3
1 2 3 4 5 6```

### 输出

```
15```

## 样例 #2

### 输入

```
4
1 4 5 8 7 6 3 2```

### 输出

```
20```

# 题解

## 作者：suzhikz (赞：6)

套路的，因为给 Aoki 和 Takahashi 两个人的权值和相同，所以转化为取出中位数的最小值。

第 $i$ 次我们可以取出 $[n-i+1,n+i]$ 中的任意一个值，这样为什么对呢？假设我们做完了 $n$ 次，并给其中 Aoki 取得数打了标记。然后我们只需要去离中间最近的那个值即可。为什么一定对呢？假设我们做完了中间的一个区间，若里面的属于 Aoki 的等于一半，扩展时直接取新扩展的不属于 Aoki 的点即可，若大于一半，则取离中间最近的，这样子中位数一定属于 Aoki。

```cpp
q.push(a[i]);q.push(a[n*2+1-i]);
ans+=a[i];ans+=a[n*2+1-i];
ans-=q.top();q.pop();
```

---

## 作者：ImposterAnYu (赞：1)

将 $2n$ 张牌分为两段（前 $n$ 张一段，后 $n$ 张一段），那么取牌的过程可以看作：

1. 将 $V_1,V_2,...,V_n$ 依次压入栈 $A$ 中，将 $V_{2n},V_{2n - 1},...,V_{n + 1}$ 依次压入栈 $B$ 中。

2. 每轮取牌时，T 可在 $A$ 和 $B$ 中任选一张牌拿走。若 T 取走的牌在 $A$ 中，则 A 会将 $B$ 的栈顶取走；若 T 取走的牌在 $B$ 中，则 A 会将 $A$ 的栈顶取走。

3. 最后的目的是使 T 取出的牌的 $\sum V$ 最大，即使 A 取出的牌的 $\sum V$ 最小（因为 $\sum\limits_{i \in T}V_i + \sum\limits_{i \in A}V_i = \sum V$，即两人取的牌上的数之和为定值）。

（为什么？自己手模一下就可以了qwq）

直接思考 T 怎么取最大似乎并不方便，本着“正难则反”的原则，我们可以考虑 T 怎么取能让 A 取到的最小。

因为 A 每次取的都是栈顶，所以在第 $i$ 轮时，A可以取的牌 $i$ 的区间是 $[n - i + 1,n + i]$（也就是栈 $A$ 和栈 $B$ 的最上边 $i$ 个元素），而且对于 A 满足上述情况的任意一种方案，T 总存在一种取牌方案可以使得 A 取到该种方案。~~但至于为什么我也不会证。~~

听不懂？可以理解为在第 $i$ 轮取牌时，A 可取的牌会多两张，即 $V_{n - i + 1}$ 和 $V_{n + i}$。而且 T 一定有办法让 A 取到 A 还可以取的牌（即在 A 前 $i$ 轮可以取的牌中去掉已经被取走的牌）中的最小的那张。

前面说过了，要让 T 取到的大，就得让 A 取到的小，所以开个小根堆，维护 A 取的牌即可。

```cpp
int main(){
	n = read(),n2 = n << 1;
    for(i = 1; i <= n2; i++){
        a[i] = read();
        ans += a[i];
    }
    for(l = n,r = n + 1; l >= 1; l--,r++){
        q.push(a[l]),q.push(a[r]);
        ans -= q.top();
        q.pop();
    }
    pe(ans);
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：0)

简单题。

动手分析一下，实际上可以将序列拆分成两个长度 $n$ 的序列。原序列中前 $n$ 项倒序排在第一个序列中，后 $n$ 项正序排在第二个序列中。操作等价于每次选择任意一个序列中的一个数，然后删掉另一个序列中最前面的数。最大化代价。

考虑什么选法是合法的，其实只需要对于每一个 $i$，两个序列前 $i$ 项选择的不超过 $i$ 个即可。因为可以选择后面部分的，但是删除只能从最前面开始删，如果选了 $k$ 个那么至少在其位置及之前删掉 $k$ 个。

然后直接反悔贪心，从前往后考虑，将前面已经标记为选择了的删去然后多选一个后面的肯定合法，所以直接将标记选择的放入小根堆中，每枚举一个 $i$ 就加入两个序列当前位上较大的一个，然后判断另一个是否比已经标记选择的最小的数大，如果是，取消标记最小的数，然后标记另一个数。

[submission](https://atcoder.jp/contests/agc053/submissions/60705538)

---

## 作者：Xiphi (赞：0)

提供一个形象化的理解。

发现每次 A 只可能那两种牌，于是就考虑 A 拿了什么牌。想象 A 有一个指针 $p$，初始时摆在中间（$n$ 与 $n+1$ 的中间位置），T 可以指挥它往哪个方向走半步，然后把当前指向的东西删掉，进行 $n$ 次，使得最后剩下的牌最大（也就是删的数的和尽量小）。

考虑用优先队列维护，相当于每次往外扩展一圈，删掉一个最小的（已经扩展到的所有牌中，没被删的且最小的）牌，最后剩下 $n$ 张牌就是最小值。

代码：

```cpp
#include<bits/stdc++.h>
#define _for(i,x,y) for(int i=x;i<=y;++i)
#define _forp(i,x,y,z) for(int i=x;i<=y;i+=z)
#define _rep(i,x,y) for(int i=x;i<y;++i)
using namespace std;
int n,v[400005];
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n;
	_for(i,1,2*n) cin>>v[i];
	long long T=n,ans=0;
	priority_queue<int,vector<int>,greater<int>> pq;
	int l=n,r=n+1;
	while(T--){
		pq.push(v[l]);
		pq.push(v[r]);
		pq.pop();
		l--,r++;
	}
	while(!pq.empty()){
		ans+=pq.top();
		pq.pop();
	}
	cout<<ans;
	return 0;
}





```

---

## 作者：skyskyCCC (赞：0)

## 前言。
不远古 AGC 题选做。貌似是半个贪心。
## 分析。
有 $2n$ 个牌，每人各取 $n$ 张，那么我们考虑将这个 $2n$ 个元素的序列分开来看。我们将它分成两个序列：一个序列是从 $1$ 到 $n$ 元素为止，第二个就是从 $n+1$ 到 $2n$ 元素为止。显然对于每次操作，对手总是取出较多的那个序列的最开头元素。这个主要是因为取中位数。

如果我们定义一组选择是正确的，那么只有对于任意的 $i$ 元素，上文中的两个序列的前 $i$ 个数字中至少有 $i$ 个已经被对手选取了。显然对于前面我们可以知道，所以直接从前往后带悔贪心即可，贪心策略就是每次让对手选出当前最小的没有被选的元素，从而让剩下的中位数所对应的数尽可能大。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;
ll n,a[200005*2];
ll ans,sum;
priority_queue<ll,vector<ll>,greater<ll> > pq;
int main(){
	cin>>n;
    for(int i=1;i<=n*2;i++){
    	cin>>a[i];
    	ans+=a[i];
	}
	sum=n+1;
    for(int i=n;i;i--){
    	pq.push(a[i]);
    	pq.push(a[sum]);
    	ans-=pq.top();
    	pq.pop();
    	sum++;
	}
	cout<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：hellolin (赞：0)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_agc053_b)

[题面(AtCoder)](https://atcoder.jp/contests/agc053/tasks/agc053_b)

AtCoder Problems 评级难度：$\texttt{\color{#337dff}1755}$。

## 思路

不难想到，当现在是第 $i(1\le i\le N)$ 回合时，Aoki 能拿的所有牌编号范围是 $[n-i+1,\ n+i]$。

那么我们有一个想法：Takahashi 把较大的牌拿走，让 Aoki 把较小的牌拿走。

可以用优先队列来实现，大数在队尾小数在队首，让 Aoki 每次把队首的牌拿走，最后队列里剩余的就是 Takahashi 拿牌的最优方案。

时间复杂度为循环乘优先队列操作，不考虑读入为 $O(N\log N)$。

## 代码

``` cpp
#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
#define int long long
const static int N=2e5+1145;
int n,v[N<<1],ans;
priority_queue<int,vector<int>,greater<int>>q;
inline void solve()
{
    cin>>n;
    for(int i=1;i<=(n<<1);i++)cin>>v[i];
    for(int i=1;i<=n;i++)
    {
        q.push(v[n-i+1]);
        q.push(v[n+i]);
        q.pop();
    }
    while(q.size())
    {
        ans+=q.top();
        q.pop();
    }
    cout<<ans<<endl;
}
#undef int
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
```



---

